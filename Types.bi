'-----------------------------------------------------------------------------------------------------------------------
' Variable type support, size and limits
' Copyright (c) 2023 Samuel Gomes
'-----------------------------------------------------------------------------------------------------------------------

$IF TYPES_BI = UNDEFINED THEN
    $LET TYPES_BI = TRUE

    '$INCLUDE:'Common.bi'

    CONST FALSE = 0, TRUE = NOT FALSE
    CONST NULL = 0
    CONST EMPTY_STRING = ""

    CONST SIZE_OF_BYTE = 1
    CONST SIZE_OF_INTEGER = 2
    CONST SIZE_OF_LONG = 4
    CONST SIZE_OF_INTEGER64 = 8
    CONST SIZE_OF_SINGLE = 4
    CONST SIZE_OF_DOUBLE = 8
    CONST SIZE_OF_FLOAT = 32
    $IF 32BIT THEN
            CONST SIZE_OF_OFFSET = 4
    $ELSE
        CONST SIZE_OF_OFFSET = 8
    $END IF

    CONST SINGLE_EPSILON! = 1.19209289550781250000000000000000000E-7
    CONST DOUBLE_EPSILON# = 2.22044604925031308084726333618164062E-16

    CONST CHARACTER_BITS = 8
    CONST BIT_MIN = -1`, BIT_MAX = 0`
    CONST UBIT_MIN = 0~`, UBIT_MAX = 1~`
    CONST BYTE_MIN = -128%%, BYTE_MAX = 127%%
    CONST UBYTE_MIN = 0~%%, UBYTE_MAX = 255~%%
    CONST INTEGER_MIN = -32768%, INTEGER_MAX = 32767%
    CONST UINTEGER_MIN = 0~%, UINTEGER_MAX = 65535~%
    CONST LONG_MIN = -2147483648&, LONG_MAX = 2147483647&
    CONST ULONG_MIN = 0~&, ULONG_MAX = 4294967295~&
    CONST INTEGER64_MIN = -9223372036854775808&&, INTEGER64_MAX = 9223372036854775807&&
    CONST UINTEGER64_MIN = 0~&&, UINTEGER64_MAX = 18446744073709551615~&&
    CONST SINGLE_MIN! = 1.17549435082228750796873653722224568E-38, SINGLE_MAX! = 3.40282346638528859811704183484516925E+38
    CONST DOUBLE_MIN# = 2.22507385850720138309023271733240406E-308, DOUBLE_MAX# = 1.79769313486231570814527423731704357E+308
    CONST FLOAT_MIN## = -1.18E-4932, FLOAT_MAX## = 1.18E+4932
    $IF 32BIT THEN
            CONST OFFSET_MIN = -2147483648&, OFFSET_MAX = 2147483647&
            CONST UOFFSET_MIN = 0~&, UOFFSET_MAX = 4294967295~&
    $ELSE
        CONST OFFSET_MIN = -9223372036854775808&&, OFFSET_MAX = 9223372036854775807&&
        CONST UOFFSET_MIN = 0~&&, UOFFSET_MAX = 18446744073709551615~&&
    $END IF

    ' QB <> C BOOL interop
    DECLARE LIBRARY "Types"
        FUNCTION ToQBBool%% ALIAS "TO_QB_BOOL" (BYVAL x AS LONG)
        FUNCTION ToCBool%% ALIAS "TO_C_BOOL" (BYVAL x AS LONG)
        FUNCTION LNot& ALIAS "TO_L_NOT" (BYVAL x AS LONG)
    END DECLARE

    '-------------------------------------------------------------------------------------------------------------------
    ' Test code for debugging the library
    '-------------------------------------------------------------------------------------------------------------------
    '$DEBUG
    '$CONSOLE:ONLY

    'PRINT ToQBBool(1)
    'PRINT ToQBBool(0)
    'PRINT ToQBBool(-1)
    'PRINT ToCBool(1)
    'PRINT ToCBool(0)
    'PRINT ToCBool(-1)
    'PRINT LNot(1)
    'PRINT LNot(0)
    'PRINT LNot(-1)

    'END
    '-------------------------------------------------------------------------------------------------------------------

$END IF
