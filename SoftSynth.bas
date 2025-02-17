'-----------------------------------------------------------------------------------------------------------------------
' Simple sample-based software synthesizer
' Copyright (c) 2023 Samuel Gomes
'-----------------------------------------------------------------------------------------------------------------------

$IF SOFTSYNTH_BAS = UNDEFINED THEN
    $LET SOFTSYNTH_BAS = TRUE

    '$INCLUDE:'SoftSynth.bi'

    '-------------------------------------------------------------------------------------------------------------------
    ' Small test code for debugging the library
    '-------------------------------------------------------------------------------------------------------------------
    '$CONSOLE

    'IF SoftSynth_Initialize THEN
    '    PRINT __SoftSynth.soundHandle
    '    PRINT __SoftSynth.soundBufferFrames
    '    PRINT __SoftSynth.soundBufferSamples
    '    PRINT __SoftSynth.soundBufferBytes

    '    SoftSynth_SetTotalVoices 4

    '    DIM rawSound AS STRING: rawSound = LoadFile("../../../../Downloads/TEST.raw")
    '    SoftSynth_LoadSound 0, rawSound, SoftSynth_BytesToFrames(LEN(rawSound), SIZE_OF_BYTE, 1), SIZE_OF_BYTE, 1

    '    SoftSynth_SetVoiceFrequency 1, 11025

    '    DIM k AS LONG
    '    DO
    '        k = _KEYHIT

    '        IF k = 32 THEN SoftSynth_PlayVoice 1, 0, 0, SOFTSYNTH_VOICE_PLAY_FORWARD, 0, SoftSynth_BytesToFrames(LEN(rawSound), SIZE_OF_BYTE, 1) - 1
    '        IF k = 19200 THEN SoftSynth_SetVoiceBalance 1, SoftSynth_GetVoiceBalance(1) - 0.01!
    '        IF k = 19712 THEN SoftSynth_SetVoiceBalance 1, SoftSynth_GetVoiceBalance(1) + 0.01!

    '        IF SoftSynth_GetBufferedSoundTime < SOFTSYNTH_SOUND_BUFFER_TIME_DEFAULT THEN SoftSynth_Update 1024

    '        LOCATE 10, 1
    '        PRINT USING "Balance: ###.###"; SoftSynth_GetVoiceBalance(1)

    '        _LIMIT 60
    '    LOOP UNTIL k = 27

    '    SoftSynth_Finalize
    'END IF

    'END

    'FUNCTION LoadFile$ (path AS STRING)
    '    IF _FILEEXISTS(path) THEN
    '        DIM AS LONG fh: fh = FREEFILE
    '        OPEN path FOR BINARY ACCESS READ AS fh
    '        LoadFile = INPUT$(LOF(fh), fh)
    '        CLOSE fh
    '    END IF
    'END FUNCTION
    '-------------------------------------------------------------------------------------------------------------------

    ' Initializes the softsynth and allocates all required resources
    FUNCTION SoftSynth_Initialize%%
        SHARED __SoftSynth AS __SoftSynthType
        SHARED __SoftSynth_SoundBuffer() AS SINGLE

        IF SoftSynth_IsInitialized THEN
            SoftSynth_Initialize = TRUE
            EXIT FUNCTION
        END IF

        ' Allocate a QB64 sound pipe
        __SoftSynth.soundHandle = _SNDOPENRAW
        IF __SoftSynth.soundHandle < 1 THEN EXIT FUNCTION

        IF NOT __SoftSynth_Initialize(_SNDRATE) THEN
            _SNDCLOSE __SoftSynth.soundHandle
            EXIT FUNCTION
        END IF

        ' Allocate a 40 ms mixer buffer and ensure we round down to power of 2
        ' Power of 2 above is required by most FFT functions
        __SoftSynth.soundBufferFrames = RoundLongDownToPowerOf2(_SNDRATE * SOFTSYNTH_SOUND_BUFFER_TIME_DEFAULT * SOFTSYNTH_SOUND_BUFFER_TIME_DEFAULT) ' buffer frames
        __SoftSynth.soundBufferSamples = __SoftSynth.soundBufferFrames * SOFTSYNTH_SOUND_BUFFER_CHANNELS ' buffer samples
        __SoftSynth.soundBufferBytes = __SoftSynth.soundBufferSamples * SOFTSYNTH_SOUND_BUFFER_SAMPLE_SIZE ' buffer bytes
        REDIM __SoftSynth_SoundBuffer(0 TO __SoftSynth.soundBufferSamples - 1) AS SINGLE ' stereo interleaved buffer

        SoftSynth_Initialize = TRUE
    END FUNCTION


    ' Close the mixer - free all allocated resources
    SUB SoftSynth_Finalize
        SHARED __SoftSynth AS __SoftSynthType

        IF SoftSynth_IsInitialized THEN
            _SNDRAWDONE __SoftSynth.soundHandle ' Sumbit whatever is remaining in the raw buffer for playback
            _SNDCLOSE __SoftSynth.soundHandle ' Close QB64 sound pipe
            __SoftSynth_Finalize ' call the C side finalizer
        END IF
    END SUB


    ' This should be called by code using the mixer at regular intervals
    SUB SoftSynth_Update (frames AS _UNSIGNED LONG)
        $CHECKING:OFF
        SHARED __SoftSynth AS __SoftSynthType
        SHARED __SoftSynth_SoundBuffer() AS SINGLE

        __SoftSynth.soundBufferFrames = frames ' buffer frames
        __SoftSynth.soundBufferSamples = __SoftSynth.soundBufferFrames * SOFTSYNTH_SOUND_BUFFER_CHANNELS ' buffer samples
        __SoftSynth.soundBufferBytes = __SoftSynth.soundBufferSamples * SOFTSYNTH_SOUND_BUFFER_SAMPLE_SIZE ' buffer bytes
        REDIM __SoftSynth_SoundBuffer(0 TO __SoftSynth.soundBufferSamples - 1) AS SINGLE ' stereo interleaved buffer

        ' Render some samples to the buffer
        __SoftSynth_Update __SoftSynth_SoundBuffer(0), frames

        ' Feed the samples to the QB64 sound pipe
        DIM i AS _UNSIGNED LONG
        DO WHILE i < __SoftSynth.soundBufferSamples
            ' Feed the samples to the QB64 sound pipe
            _SNDRAW __SoftSynth_SoundBuffer(i), __SoftSynth_SoundBuffer(i + 1), __SoftSynth.soundHandle
            i = i + SOFTSYNTH_SOUND_BUFFER_CHANNELS
        LOOP
        $CHECKING:ON
    END SUB


    ' Returns the amount of buffered sample time remaining to be played
    FUNCTION SoftSynth_GetBufferedSoundTime#
        $CHECKING:OFF
        SHARED __SoftSynth AS __SoftSynthType

        SoftSynth_GetBufferedSoundTime = _SNDRAWLEN(__SoftSynth.soundHandle)
        $CHECKING:ON
    END FUNCTION

$END IF
