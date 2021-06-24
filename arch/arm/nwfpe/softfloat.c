<शैली गुरु>
/*
===============================================================================

This C source file is part of the SoftFloat IEC/IEEE Floating-poपूर्णांक
Arithmetic Package, Release 2.

Written by John R. Hauser.  This work was made possible in part by the
International Computer Science Institute, located at Suite 600, 1947 Center
Street, Berkeley, Calअगरornia 94704.  Funding was partially provided by the
National Science Foundation under grant MIP-9311980.  The original version
of this code was written as part of a project to build a fixed-poपूर्णांक vector
processor in collaboration with the University of Calअगरornia at Berkeley,
overseen by Profs. Nelson Morgan and John Wawrzynek.  More inक्रमmation
is available through the web page
http://www.jhauser.us/arithmetic/SoftFloat-2b/SoftFloat-source.txt

THIS SOFTWARE IS DISTRIBUTED AS IS, FOR FREE.  Although reasonable efक्रमt
has been made to aव्योम it, THIS SOFTWARE MAY CONTAIN FAULTS THAT WILL AT
TIMES RESULT IN INCORRECT BEHAVIOR.  USE OF THIS SOFTWARE IS RESTRICTED TO
PERSONS AND ORGANIZATIONS WHO CAN AND WILL TAKE FULL RESPONSIBILITY FOR ANY
AND ALL LOSSES, COSTS, OR OTHER PROBLEMS ARISING FROM ITS USE.

Derivative works are acceptable, even क्रम commercial purposes, so दीर्घ as
(1) they include prominent notice that the work is derivative, and (2) they
include prominent notice akin to these three paragraphs क्रम those parts of
this code that are retained.

===============================================================================
*/

#समावेश <यंत्र/भाग64.h>

#समावेश "fpa11.h"
//#समावेश "milieu.h"
//#समावेश "softfloat.h"

/*
-------------------------------------------------------------------------------
Primitive arithmetic functions, including multi-word arithmetic, and
भागision and square root approximations.  (Can be specialized to target अगर
desired.)
-------------------------------------------------------------------------------
*/
#समावेश "softfloat-macros"

/*
-------------------------------------------------------------------------------
Functions and definitions to determine:  (1) whether tininess क्रम underflow
is detected beक्रमe or after rounding by शेष, (2) what (अगर anything)
happens when exceptions are उठाओd, (3) how संकेतing NaNs are distinguished
from quiet NaNs, (4) the शेष generated quiet NaNs, and (5) how NaNs
are propagated from function inमाला_दो to output.  These details are target-
specअगरic.
-------------------------------------------------------------------------------
*/
#समावेश "softfloat-specialize"

/*
-------------------------------------------------------------------------------
Takes a 64-bit fixed-poपूर्णांक value `असलZ' with binary poपूर्णांक between bits 6
and 7, and वापसs the properly rounded 32-bit पूर्णांकeger corresponding to the
input.  If `zSign' is nonzero, the input is negated beक्रमe being converted
to an पूर्णांकeger.  Bit 63 of `असलZ' must be zero.  Ordinarily, the fixed-poपूर्णांक
input is simply rounded to an पूर्णांकeger, with the inexact exception उठाओd अगर
the input cannot be represented exactly as an पूर्णांकeger.  If the fixed-poपूर्णांक
input is too large, however, the invalid exception is उठाओd and the largest
positive or negative पूर्णांकeger is वापसed.
-------------------------------------------------------------------------------
*/
अटल पूर्णांक32 roundAndPackInt32( काष्ठा roundingData *roundData, flag zSign, bits64 असलZ )
अणु
    पूर्णांक8 roundingMode;
    flag roundNearestEven;
    पूर्णांक8 roundIncrement, roundBits;
    पूर्णांक32 z;

    roundingMode = roundData->mode;
    roundNearestEven = ( roundingMode == भग्न_round_nearest_even );
    roundIncrement = 0x40;
    अगर ( ! roundNearestEven ) अणु
        अगर ( roundingMode == भग्न_round_to_zero ) अणु
            roundIncrement = 0;
        पूर्ण
        अन्यथा अणु
            roundIncrement = 0x7F;
            अगर ( zSign ) अणु
                अगर ( roundingMode == भग्न_round_up ) roundIncrement = 0;
            पूर्ण
            अन्यथा अणु
                अगर ( roundingMode == भग्न_round_करोwn ) roundIncrement = 0;
            पूर्ण
        पूर्ण
    पूर्ण
    roundBits = असलZ & 0x7F;
    असलZ = ( असलZ + roundIncrement )>>7;
    असलZ &= ~ ( ( ( roundBits ^ 0x40 ) == 0 ) & roundNearestEven );
    z = असलZ;
    अगर ( zSign ) z = - z;
    अगर ( ( असलZ>>32 ) || ( z && ( ( z < 0 ) ^ zSign ) ) ) अणु
        roundData->exception |= भग्न_flag_invalid;
        वापस zSign ? 0x80000000 : 0x7FFFFFFF;
    पूर्ण
    अगर ( roundBits ) roundData->exception |= भग्न_flag_inexact;
    वापस z;

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the fraction bits of the single-precision भग्नing-poपूर्णांक value `a'.
-------------------------------------------------------------------------------
*/
INLINE bits32 extractFloat32Frac( भग्न32 a )
अणु

    वापस a & 0x007FFFFF;

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the exponent bits of the single-precision भग्नing-poपूर्णांक value `a'.
-------------------------------------------------------------------------------
*/
INLINE पूर्णांक16 extractFloat32Exp( भग्न32 a )
अणु

    वापस ( a>>23 ) & 0xFF;

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the sign bit of the single-precision भग्नing-poपूर्णांक value `a'.
-------------------------------------------------------------------------------
*/
#अगर 0	/* in softभग्न.स */
INLINE flag extractFloat32Sign( भग्न32 a )
अणु

    वापस a>>31;

पूर्ण
#पूर्ण_अगर

/*
-------------------------------------------------------------------------------
Normalizes the subnormal single-precision भग्नing-poपूर्णांक value represented
by the denormalized signअगरicand `aSig'.  The normalized exponent and
signअगरicand are stored at the locations poपूर्णांकed to by `zExpPtr' and
`zSigPtr', respectively.
-------------------------------------------------------------------------------
*/
अटल व्योम
 normalizeFloat32Subnormal( bits32 aSig, पूर्णांक16 *zExpPtr, bits32 *zSigPtr )
अणु
    पूर्णांक8 shअगरtCount;

    shअगरtCount = countLeadingZeros32( aSig ) - 8;
    *zSigPtr = aSig<<shअगरtCount;
    *zExpPtr = 1 - shअगरtCount;

पूर्ण

/*
-------------------------------------------------------------------------------
Packs the sign `zSign', exponent `zExp', and significand `zSig' पूर्णांकo a
single-precision भग्नing-poपूर्णांक value, वापसing the result.  After being
shअगरted पूर्णांकo the proper positions, the three fields are simply added
together to क्रमm the result.  This means that any पूर्णांकeger portion of `zSig'
will be added पूर्णांकo the exponent.  Since a properly normalized signअगरicand
will have an पूर्णांकeger portion equal to 1, the `zExp' input should be 1 less
than the desired result exponent whenever `zSig' is a complete, normalized
signअगरicand.
-------------------------------------------------------------------------------
*/
INLINE भग्न32 packFloat32( flag zSign, पूर्णांक16 zExp, bits32 zSig )
अणु
#अगर 0
   भग्न32 f;
   __यंत्र__("@ packFloat32				\न\
   	    mov %0, %1, asl #31				\न\
   	    orr %0, %2, asl #23				\न\
   	    orr %0, %3"
   	    : /* no outमाला_दो */
   	    : "g" (f), "g" (zSign), "g" (zExp), "g" (zSig)
   	    : "cc");
   वापस f;
#अन्यथा
    वापस ( ( (bits32) zSign )<<31 ) + ( ( (bits32) zExp )<<23 ) + zSig;
#पूर्ण_अगर 
पूर्ण

/*
-------------------------------------------------------------------------------
Takes an असलtract भग्नing-poपूर्णांक value having sign `zSign', exponent `zExp',
and signअगरicand `zSig', and वापसs the proper single-precision भग्नing-
poपूर्णांक value corresponding to the असलtract input.  Ordinarily, the असलtract
value is simply rounded and packed पूर्णांकo the single-precision क्रमmat, with
the inexact exception उठाओd अगर the असलtract input cannot be represented
exactly.  If the असलtract value is too large, however, the overflow and
inexact exceptions are उठाओd and an infinity or maximal finite value is
वापसed.  If the असलtract value is too small, the input value is rounded to
a subnormal number, and the underflow and inexact exceptions are उठाओd अगर
the असलtract input cannot be represented exactly as a subnormal single-
precision भग्नing-poपूर्णांक number.
    The input signअगरicand `zSig' has its binary poपूर्णांक between bits 30
and 29, which is 7 bits to the left of the usual location.  This shअगरted
signअगरicand must be normalized or smaller.  If `zSig' is not normalized,
`zExp' must be 0; in that हाल, the result वापसed is a subnormal number,
and it must not require rounding.  In the usual हाल that `zSig' is
normalized, `zExp' must be 1 less than the ``true'' भग्नing-poपूर्णांक exponent.
The handling of underflow and overflow follows the IEC/IEEE Standard क्रम
Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
अटल भग्न32 roundAndPackFloat32( काष्ठा roundingData *roundData, flag zSign, पूर्णांक16 zExp, bits32 zSig )
अणु
    पूर्णांक8 roundingMode;
    flag roundNearestEven;
    पूर्णांक8 roundIncrement, roundBits;
    flag isTiny;

    roundingMode = roundData->mode;
    roundNearestEven = ( roundingMode == भग्न_round_nearest_even );
    roundIncrement = 0x40;
    अगर ( ! roundNearestEven ) अणु
        अगर ( roundingMode == भग्न_round_to_zero ) अणु
            roundIncrement = 0;
        पूर्ण
        अन्यथा अणु
            roundIncrement = 0x7F;
            अगर ( zSign ) अणु
                अगर ( roundingMode == भग्न_round_up ) roundIncrement = 0;
            पूर्ण
            अन्यथा अणु
                अगर ( roundingMode == भग्न_round_करोwn ) roundIncrement = 0;
            पूर्ण
        पूर्ण
    पूर्ण
    roundBits = zSig & 0x7F;
    अगर ( 0xFD <= (bits16) zExp ) अणु
        अगर (    ( 0xFD < zExp )
             || (    ( zExp == 0xFD )
                  && ( (sbits32) ( zSig + roundIncrement ) < 0 ) )
           ) अणु
            roundData->exception |= भग्न_flag_overflow | भग्न_flag_inexact;
            वापस packFloat32( zSign, 0xFF, 0 ) - ( roundIncrement == 0 );
        पूर्ण
        अगर ( zExp < 0 ) अणु
            isTiny =
                   ( भग्न_detect_tininess == भग्न_tininess_beक्रमe_rounding )
                || ( zExp < -1 )
                || ( zSig + roundIncrement < 0x80000000 );
            shअगरt32RightJamming( zSig, - zExp, &zSig );
            zExp = 0;
            roundBits = zSig & 0x7F;
            अगर ( isTiny && roundBits ) roundData->exception |= भग्न_flag_underflow;
        पूर्ण
    पूर्ण
    अगर ( roundBits ) roundData->exception |= भग्न_flag_inexact;
    zSig = ( zSig + roundIncrement )>>7;
    zSig &= ~ ( ( ( roundBits ^ 0x40 ) == 0 ) & roundNearestEven );
    अगर ( zSig == 0 ) zExp = 0;
    वापस packFloat32( zSign, zExp, zSig );

पूर्ण

/*
-------------------------------------------------------------------------------
Takes an असलtract भग्नing-poपूर्णांक value having sign `zSign', exponent `zExp',
and signअगरicand `zSig', and वापसs the proper single-precision भग्नing-
poपूर्णांक value corresponding to the असलtract input.  This routine is just like
`roundAndPackFloat32' except that `zSig' करोes not have to be normalized in
any way.  In all हालs, `zExp' must be 1 less than the ``true'' भग्नing-
poपूर्णांक exponent.
-------------------------------------------------------------------------------
*/
अटल भग्न32
 normalizeRoundAndPackFloat32( काष्ठा roundingData *roundData, flag zSign, पूर्णांक16 zExp, bits32 zSig )
अणु
    पूर्णांक8 shअगरtCount;

    shअगरtCount = countLeadingZeros32( zSig ) - 1;
    वापस roundAndPackFloat32( roundData, zSign, zExp - shअगरtCount, zSig<<shअगरtCount );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the fraction bits of the द्विगुन-precision भग्नing-poपूर्णांक value `a'.
-------------------------------------------------------------------------------
*/
INLINE bits64 extractFloat64Frac( भग्न64 a )
अणु

    वापस a & LIT64( 0x000FFFFFFFFFFFFF );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the exponent bits of the द्विगुन-precision भग्नing-poपूर्णांक value `a'.
-------------------------------------------------------------------------------
*/
INLINE पूर्णांक16 extractFloat64Exp( भग्न64 a )
अणु

    वापस ( a>>52 ) & 0x7FF;

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the sign bit of the द्विगुन-precision भग्नing-poपूर्णांक value `a'.
-------------------------------------------------------------------------------
*/
#अगर 0	/* in softभग्न.स */
INLINE flag extractFloat64Sign( भग्न64 a )
अणु

    वापस a>>63;

पूर्ण
#पूर्ण_अगर

/*
-------------------------------------------------------------------------------
Normalizes the subnormal द्विगुन-precision भग्नing-poपूर्णांक value represented
by the denormalized signअगरicand `aSig'.  The normalized exponent and
signअगरicand are stored at the locations poपूर्णांकed to by `zExpPtr' and
`zSigPtr', respectively.
-------------------------------------------------------------------------------
*/
अटल व्योम
 normalizeFloat64Subnormal( bits64 aSig, पूर्णांक16 *zExpPtr, bits64 *zSigPtr )
अणु
    पूर्णांक8 shअगरtCount;

    shअगरtCount = countLeadingZeros64( aSig ) - 11;
    *zSigPtr = aSig<<shअगरtCount;
    *zExpPtr = 1 - shअगरtCount;

पूर्ण

/*
-------------------------------------------------------------------------------
Packs the sign `zSign', exponent `zExp', and significand `zSig' पूर्णांकo a
द्विगुन-precision भग्नing-poपूर्णांक value, वापसing the result.  After being
shअगरted पूर्णांकo the proper positions, the three fields are simply added
together to क्रमm the result.  This means that any पूर्णांकeger portion of `zSig'
will be added पूर्णांकo the exponent.  Since a properly normalized signअगरicand
will have an पूर्णांकeger portion equal to 1, the `zExp' input should be 1 less
than the desired result exponent whenever `zSig' is a complete, normalized
signअगरicand.
-------------------------------------------------------------------------------
*/
INLINE भग्न64 packFloat64( flag zSign, पूर्णांक16 zExp, bits64 zSig )
अणु

    वापस ( ( (bits64) zSign )<<63 ) + ( ( (bits64) zExp )<<52 ) + zSig;

पूर्ण

/*
-------------------------------------------------------------------------------
Takes an असलtract भग्नing-poपूर्णांक value having sign `zSign', exponent `zExp',
and signअगरicand `zSig', and वापसs the proper द्विगुन-precision भग्नing-
poपूर्णांक value corresponding to the असलtract input.  Ordinarily, the असलtract
value is simply rounded and packed पूर्णांकo the द्विगुन-precision क्रमmat, with
the inexact exception उठाओd अगर the असलtract input cannot be represented
exactly.  If the असलtract value is too large, however, the overflow and
inexact exceptions are उठाओd and an infinity or maximal finite value is
वापसed.  If the असलtract value is too small, the input value is rounded to
a subnormal number, and the underflow and inexact exceptions are उठाओd अगर
the असलtract input cannot be represented exactly as a subnormal द्विगुन-
precision भग्नing-poपूर्णांक number.
    The input signअगरicand `zSig' has its binary poपूर्णांक between bits 62
and 61, which is 10 bits to the left of the usual location.  This shअगरted
signअगरicand must be normalized or smaller.  If `zSig' is not normalized,
`zExp' must be 0; in that हाल, the result वापसed is a subnormal number,
and it must not require rounding.  In the usual हाल that `zSig' is
normalized, `zExp' must be 1 less than the ``true'' भग्नing-poपूर्णांक exponent.
The handling of underflow and overflow follows the IEC/IEEE Standard क्रम
Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
अटल भग्न64 roundAndPackFloat64( काष्ठा roundingData *roundData, flag zSign, पूर्णांक16 zExp, bits64 zSig )
अणु
    पूर्णांक8 roundingMode;
    flag roundNearestEven;
    पूर्णांक16 roundIncrement, roundBits;
    flag isTiny;

    roundingMode = roundData->mode;
    roundNearestEven = ( roundingMode == भग्न_round_nearest_even );
    roundIncrement = 0x200;
    अगर ( ! roundNearestEven ) अणु
        अगर ( roundingMode == भग्न_round_to_zero ) अणु
            roundIncrement = 0;
        पूर्ण
        अन्यथा अणु
            roundIncrement = 0x3FF;
            अगर ( zSign ) अणु
                अगर ( roundingMode == भग्न_round_up ) roundIncrement = 0;
            पूर्ण
            अन्यथा अणु
                अगर ( roundingMode == भग्न_round_करोwn ) roundIncrement = 0;
            पूर्ण
        पूर्ण
    पूर्ण
    roundBits = zSig & 0x3FF;
    अगर ( 0x7FD <= (bits16) zExp ) अणु
        अगर (    ( 0x7FD < zExp )
             || (    ( zExp == 0x7FD )
                  && ( (sbits64) ( zSig + roundIncrement ) < 0 ) )
           ) अणु
            //रेजिस्टर पूर्णांक lr = __builtin_वापस_address(0);
            //prपूर्णांकk("roundAndPackFloat64 called from 0x%08x\n",lr);
            roundData->exception |= भग्न_flag_overflow | भग्न_flag_inexact;
            वापस packFloat64( zSign, 0x7FF, 0 ) - ( roundIncrement == 0 );
        पूर्ण
        अगर ( zExp < 0 ) अणु
            isTiny =
                   ( भग्न_detect_tininess == भग्न_tininess_beक्रमe_rounding )
                || ( zExp < -1 )
                || ( zSig + roundIncrement < LIT64( 0x8000000000000000 ) );
            shअगरt64RightJamming( zSig, - zExp, &zSig );
            zExp = 0;
            roundBits = zSig & 0x3FF;
            अगर ( isTiny && roundBits ) roundData->exception |= भग्न_flag_underflow;
        पूर्ण
    पूर्ण
    अगर ( roundBits ) roundData->exception |= भग्न_flag_inexact;
    zSig = ( zSig + roundIncrement )>>10;
    zSig &= ~ ( ( ( roundBits ^ 0x200 ) == 0 ) & roundNearestEven );
    अगर ( zSig == 0 ) zExp = 0;
    वापस packFloat64( zSign, zExp, zSig );

पूर्ण

/*
-------------------------------------------------------------------------------
Takes an असलtract भग्नing-poपूर्णांक value having sign `zSign', exponent `zExp',
and signअगरicand `zSig', and वापसs the proper द्विगुन-precision भग्नing-
poपूर्णांक value corresponding to the असलtract input.  This routine is just like
`roundAndPackFloat64' except that `zSig' करोes not have to be normalized in
any way.  In all हालs, `zExp' must be 1 less than the ``true'' भग्नing-
poपूर्णांक exponent.
-------------------------------------------------------------------------------
*/
अटल भग्न64
 normalizeRoundAndPackFloat64( काष्ठा roundingData *roundData, flag zSign, पूर्णांक16 zExp, bits64 zSig )
अणु
    पूर्णांक8 shअगरtCount;

    shअगरtCount = countLeadingZeros64( zSig ) - 1;
    वापस roundAndPackFloat64( roundData, zSign, zExp - shअगरtCount, zSig<<shअगरtCount );

पूर्ण

#अगर_घोषित FLOATX80

/*
-------------------------------------------------------------------------------
Returns the fraction bits of the extended द्विगुन-precision भग्नing-poपूर्णांक
value `a'.
-------------------------------------------------------------------------------
*/
INLINE bits64 extractFloatx80Frac( भग्नx80 a )
अणु

    वापस a.low;

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the exponent bits of the extended द्विगुन-precision भग्नing-poपूर्णांक
value `a'.
-------------------------------------------------------------------------------
*/
INLINE पूर्णांक32 extractFloatx80Exp( भग्नx80 a )
अणु

    वापस a.high & 0x7FFF;

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the sign bit of the extended द्विगुन-precision भग्नing-poपूर्णांक value
`a'.
-------------------------------------------------------------------------------
*/
INLINE flag extractFloatx80Sign( भग्नx80 a )
अणु

    वापस a.high>>15;

पूर्ण

/*
-------------------------------------------------------------------------------
Normalizes the subnormal extended द्विगुन-precision भग्नing-poपूर्णांक value
represented by the denormalized signअगरicand `aSig'.  The normalized exponent
and signअगरicand are stored at the locations poपूर्णांकed to by `zExpPtr' and
`zSigPtr', respectively.
-------------------------------------------------------------------------------
*/
अटल व्योम
 normalizeFloatx80Subnormal( bits64 aSig, पूर्णांक32 *zExpPtr, bits64 *zSigPtr )
अणु
    पूर्णांक8 shअगरtCount;

    shअगरtCount = countLeadingZeros64( aSig );
    *zSigPtr = aSig<<shअगरtCount;
    *zExpPtr = 1 - shअगरtCount;

पूर्ण

/*
-------------------------------------------------------------------------------
Packs the sign `zSign', exponent `zExp', and significand `zSig' पूर्णांकo an
extended द्विगुन-precision भग्नing-poपूर्णांक value, वापसing the result.
-------------------------------------------------------------------------------
*/
INLINE भग्नx80 packFloatx80( flag zSign, पूर्णांक32 zExp, bits64 zSig )
अणु
    भग्नx80 z;

    z.low = zSig;
    z.high = ( ( (bits16) zSign )<<15 ) + zExp;
    z.__padding = 0;
    वापस z;

पूर्ण

/*
-------------------------------------------------------------------------------
Takes an असलtract भग्नing-poपूर्णांक value having sign `zSign', exponent `zExp',
and extended signअगरicand क्रमmed by the concatenation of `zSig0' and `zSig1',
and वापसs the proper extended द्विगुन-precision भग्नing-poपूर्णांक value
corresponding to the असलtract input.  Ordinarily, the असलtract value is
rounded and packed पूर्णांकo the extended द्विगुन-precision क्रमmat, with the
inexact exception उठाओd अगर the असलtract input cannot be represented
exactly.  If the असलtract value is too large, however, the overflow and
inexact exceptions are उठाओd and an infinity or maximal finite value is
वापसed.  If the असलtract value is too small, the input value is rounded to
a subnormal number, and the underflow and inexact exceptions are उठाओd अगर
the असलtract input cannot be represented exactly as a subnormal extended
द्विगुन-precision भग्नing-poपूर्णांक number.
    If `roundingPrecision' is 32 or 64, the result is rounded to the same
number of bits as single or द्विगुन precision, respectively.  Otherwise, the
result is rounded to the full precision of the extended द्विगुन-precision
क्रमmat.
    The input signअगरicand must be normalized or smaller.  If the input
signअगरicand is not normalized, `zExp' must be 0; in that हाल, the result
वापसed is a subnormal number, and it must not require rounding.  The
handling of underflow and overflow follows the IEC/IEEE Standard क्रम Binary
Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
अटल भग्नx80
 roundAndPackFloatx80(
     काष्ठा roundingData *roundData, flag zSign, पूर्णांक32 zExp, bits64 zSig0, bits64 zSig1
 )
अणु
    पूर्णांक8 roundingMode, roundingPrecision;
    flag roundNearestEven, increment, isTiny;
    पूर्णांक64 roundIncrement, roundMask, roundBits;

    roundingMode = roundData->mode;
    roundingPrecision = roundData->precision;
    roundNearestEven = ( roundingMode == भग्न_round_nearest_even );
    अगर ( roundingPrecision == 80 ) जाओ precision80;
    अगर ( roundingPrecision == 64 ) अणु
        roundIncrement = LIT64( 0x0000000000000400 );
        roundMask = LIT64( 0x00000000000007FF );
    पूर्ण
    अन्यथा अगर ( roundingPrecision == 32 ) अणु
        roundIncrement = LIT64( 0x0000008000000000 );
        roundMask = LIT64( 0x000000FFFFFFFFFF );
    पूर्ण
    अन्यथा अणु
        जाओ precision80;
    पूर्ण
    zSig0 |= ( zSig1 != 0 );
    अगर ( ! roundNearestEven ) अणु
        अगर ( roundingMode == भग्न_round_to_zero ) अणु
            roundIncrement = 0;
        पूर्ण
        अन्यथा अणु
            roundIncrement = roundMask;
            अगर ( zSign ) अणु
                अगर ( roundingMode == भग्न_round_up ) roundIncrement = 0;
            पूर्ण
            अन्यथा अणु
                अगर ( roundingMode == भग्न_round_करोwn ) roundIncrement = 0;
            पूर्ण
        पूर्ण
    पूर्ण
    roundBits = zSig0 & roundMask;
    अगर ( 0x7FFD <= (bits32) ( zExp - 1 ) ) अणु
        अगर (    ( 0x7FFE < zExp )
             || ( ( zExp == 0x7FFE ) && ( zSig0 + roundIncrement < zSig0 ) )
           ) अणु
            जाओ overflow;
        पूर्ण
        अगर ( zExp <= 0 ) अणु
            isTiny =
                   ( भग्न_detect_tininess == भग्न_tininess_beक्रमe_rounding )
                || ( zExp < 0 )
                || ( zSig0 <= zSig0 + roundIncrement );
            shअगरt64RightJamming( zSig0, 1 - zExp, &zSig0 );
            zExp = 0;
            roundBits = zSig0 & roundMask;
            अगर ( isTiny && roundBits ) roundData->exception |= भग्न_flag_underflow;
            अगर ( roundBits ) roundData->exception |= भग्न_flag_inexact;
            zSig0 += roundIncrement;
            अगर ( (sbits64) zSig0 < 0 ) zExp = 1;
            roundIncrement = roundMask + 1;
            अगर ( roundNearestEven && ( roundBits<<1 == roundIncrement ) ) अणु
                roundMask |= roundIncrement;
            पूर्ण
            zSig0 &= ~ roundMask;
            वापस packFloatx80( zSign, zExp, zSig0 );
        पूर्ण
    पूर्ण
    अगर ( roundBits ) roundData->exception |= भग्न_flag_inexact;
    zSig0 += roundIncrement;
    अगर ( zSig0 < roundIncrement ) अणु
        ++zExp;
        zSig0 = LIT64( 0x8000000000000000 );
    पूर्ण
    roundIncrement = roundMask + 1;
    अगर ( roundNearestEven && ( roundBits<<1 == roundIncrement ) ) अणु
        roundMask |= roundIncrement;
    पूर्ण
    zSig0 &= ~ roundMask;
    अगर ( zSig0 == 0 ) zExp = 0;
    वापस packFloatx80( zSign, zExp, zSig0 );
 precision80:
    increment = ( (sbits64) zSig1 < 0 );
    अगर ( ! roundNearestEven ) अणु
        अगर ( roundingMode == भग्न_round_to_zero ) अणु
            increment = 0;
        पूर्ण
        अन्यथा अणु
            अगर ( zSign ) अणु
                increment = ( roundingMode == भग्न_round_करोwn ) && zSig1;
            पूर्ण
            अन्यथा अणु
                increment = ( roundingMode == भग्न_round_up ) && zSig1;
            पूर्ण
        पूर्ण
    पूर्ण
    अगर ( 0x7FFD <= (bits32) ( zExp - 1 ) ) अणु
        अगर (    ( 0x7FFE < zExp )
             || (    ( zExp == 0x7FFE )
                  && ( zSig0 == LIT64( 0xFFFFFFFFFFFFFFFF ) )
                  && increment
                )
           ) अणु
            roundMask = 0;
 overflow:
            roundData->exception |= भग्न_flag_overflow | भग्न_flag_inexact;
            अगर (    ( roundingMode == भग्न_round_to_zero )
                 || ( zSign && ( roundingMode == भग्न_round_up ) )
                 || ( ! zSign && ( roundingMode == भग्न_round_करोwn ) )
               ) अणु
                वापस packFloatx80( zSign, 0x7FFE, ~ roundMask );
            पूर्ण
            वापस packFloatx80( zSign, 0x7FFF, LIT64( 0x8000000000000000 ) );
        पूर्ण
        अगर ( zExp <= 0 ) अणु
            isTiny =
                   ( भग्न_detect_tininess == भग्न_tininess_beक्रमe_rounding )
                || ( zExp < 0 )
                || ! increment
                || ( zSig0 < LIT64( 0xFFFFFFFFFFFFFFFF ) );
            shअगरt64ExtraRightJamming( zSig0, zSig1, 1 - zExp, &zSig0, &zSig1 );
            zExp = 0;
            अगर ( isTiny && zSig1 ) roundData->exception |= भग्न_flag_underflow;
            अगर ( zSig1 ) roundData->exception |= भग्न_flag_inexact;
            अगर ( roundNearestEven ) अणु
                increment = ( (sbits64) zSig1 < 0 );
            पूर्ण
            अन्यथा अणु
                अगर ( zSign ) अणु
                    increment = ( roundingMode == भग्न_round_करोwn ) && zSig1;
                पूर्ण
                अन्यथा अणु
                    increment = ( roundingMode == भग्न_round_up ) && zSig1;
                पूर्ण
            पूर्ण
            अगर ( increment ) अणु
                ++zSig0;
                zSig0 &= ~ ( ( zSig1 + zSig1 == 0 ) & roundNearestEven );
                अगर ( (sbits64) zSig0 < 0 ) zExp = 1;
            पूर्ण
            वापस packFloatx80( zSign, zExp, zSig0 );
        पूर्ण
    पूर्ण
    अगर ( zSig1 ) roundData->exception |= भग्न_flag_inexact;
    अगर ( increment ) अणु
        ++zSig0;
        अगर ( zSig0 == 0 ) अणु
            ++zExp;
            zSig0 = LIT64( 0x8000000000000000 );
        पूर्ण
        अन्यथा अणु
            zSig0 &= ~ ( ( zSig1 + zSig1 == 0 ) & roundNearestEven );
        पूर्ण
    पूर्ण
    अन्यथा अणु
        अगर ( zSig0 == 0 ) zExp = 0;
    पूर्ण
    
    वापस packFloatx80( zSign, zExp, zSig0 );
पूर्ण

/*
-------------------------------------------------------------------------------
Takes an असलtract भग्नing-poपूर्णांक value having sign `zSign', exponent
`zExp', and significand formed by the concatenation of `zSig0' and `zSig1',
and वापसs the proper extended द्विगुन-precision भग्नing-poपूर्णांक value
corresponding to the असलtract input.  This routine is just like
`roundAndPackFloatx80' except that the input signअगरicand करोes not have to be
normalized.
-------------------------------------------------------------------------------
*/
अटल भग्नx80
 normalizeRoundAndPackFloatx80(
     काष्ठा roundingData *roundData, flag zSign, पूर्णांक32 zExp, bits64 zSig0, bits64 zSig1
 )
अणु
    पूर्णांक8 shअगरtCount;

    अगर ( zSig0 == 0 ) अणु
        zSig0 = zSig1;
        zSig1 = 0;
        zExp -= 64;
    पूर्ण
    shअगरtCount = countLeadingZeros64( zSig0 );
    लघुShअगरt128Left( zSig0, zSig1, shअगरtCount, &zSig0, &zSig1 );
    zExp -= shअगरtCount;
    वापस
        roundAndPackFloatx80( roundData, zSign, zExp, zSig0, zSig1 );

पूर्ण

#पूर्ण_अगर

/*
-------------------------------------------------------------------------------
Returns the result of converting the 32-bit two's complement integer `a' to
the single-precision भग्नing-poपूर्णांक क्रमmat.  The conversion is perक्रमmed
according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्न32 पूर्णांक32_to_भग्न32(काष्ठा roundingData *roundData, पूर्णांक32 a)
अणु
    flag zSign;

    अगर ( a == 0 ) वापस 0;
    अगर ( a == 0x80000000 ) वापस packFloat32( 1, 0x9E, 0 );
    zSign = ( a < 0 );
    वापस normalizeRoundAndPackFloat32( roundData, zSign, 0x9C, zSign ? - a : a );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of converting the 32-bit two's complement integer `a' to
the द्विगुन-precision भग्नing-poपूर्णांक क्रमmat.  The conversion is perक्रमmed
according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्न64 पूर्णांक32_to_भग्न64( पूर्णांक32 a )
अणु
    flag aSign;
    uपूर्णांक32 असलA;
    पूर्णांक8 shअगरtCount;
    bits64 zSig;

    अगर ( a == 0 ) वापस 0;
    aSign = ( a < 0 );
    असलA = aSign ? - a : a;
    shअगरtCount = countLeadingZeros32( असलA ) + 21;
    zSig = असलA;
    वापस packFloat64( aSign, 0x432 - shअगरtCount, zSig<<shअगरtCount );

पूर्ण

#अगर_घोषित FLOATX80

/*
-------------------------------------------------------------------------------
Returns the result of converting the 32-bit two's complement integer `a'
to the extended द्विगुन-precision भग्नing-poपूर्णांक क्रमmat.  The conversion
is perक्रमmed according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक
Arithmetic.
-------------------------------------------------------------------------------
*/
भग्नx80 पूर्णांक32_to_भग्नx80( पूर्णांक32 a )
अणु
    flag zSign;
    uपूर्णांक32 असलA;
    पूर्णांक8 shअगरtCount;
    bits64 zSig;

    अगर ( a == 0 ) वापस packFloatx80( 0, 0, 0 );
    zSign = ( a < 0 );
    असलA = zSign ? - a : a;
    shअगरtCount = countLeadingZeros32( असलA ) + 32;
    zSig = असलA;
    वापस packFloatx80( zSign, 0x403E - shअगरtCount, zSig<<shअगरtCount );

पूर्ण

#पूर्ण_अगर

/*
-------------------------------------------------------------------------------
Returns the result of converting the single-precision भग्नing-poपूर्णांक value
`a' to the 32-bit two's complement पूर्णांकeger क्रमmat.  The conversion is
perक्रमmed according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक
Arithmetic---which means in particular that the conversion is rounded
according to the current rounding mode.  If `a' is a NaN, the largest
positive पूर्णांकeger is वापसed.  Otherwise, अगर the conversion overflows, the
largest पूर्णांकeger with the same sign as `a' is वापसed.
-------------------------------------------------------------------------------
*/
पूर्णांक32 भग्न32_to_पूर्णांक32( काष्ठा roundingData *roundData, भग्न32 a )
अणु
    flag aSign;
    पूर्णांक16 aExp, shअगरtCount;
    bits32 aSig;
    bits64 zSig;

    aSig = extractFloat32Frac( a );
    aExp = extractFloat32Exp( a );
    aSign = extractFloat32Sign( a );
    अगर ( ( aExp == 0x7FF ) && aSig ) aSign = 0;
    अगर ( aExp ) aSig |= 0x00800000;
    shअगरtCount = 0xAF - aExp;
    zSig = aSig;
    zSig <<= 32;
    अगर ( 0 < shअगरtCount ) shअगरt64RightJamming( zSig, shअगरtCount, &zSig );
    वापस roundAndPackInt32( roundData, aSign, zSig );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of converting the single-precision भग्नing-poपूर्णांक value
`a' to the 32-bit two's complement पूर्णांकeger क्रमmat.  The conversion is
perक्रमmed according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक
Arithmetic, except that the conversion is always rounded toward zero.  If
`a' is a NaN, the largest positive पूर्णांकeger is वापसed.  Otherwise, अगर the
conversion overflows, the largest पूर्णांकeger with the same sign as `a' is
वापसed.
-------------------------------------------------------------------------------
*/
पूर्णांक32 भग्न32_to_पूर्णांक32_round_to_zero( भग्न32 a )
अणु
    flag aSign;
    पूर्णांक16 aExp, shअगरtCount;
    bits32 aSig;
    पूर्णांक32 z;

    aSig = extractFloat32Frac( a );
    aExp = extractFloat32Exp( a );
    aSign = extractFloat32Sign( a );
    shअगरtCount = aExp - 0x9E;
    अगर ( 0 <= shअगरtCount ) अणु
        अगर ( a == 0xCF000000 ) वापस 0x80000000;
        भग्न_उठाओ( भग्न_flag_invalid );
        अगर ( ! aSign || ( ( aExp == 0xFF ) && aSig ) ) वापस 0x7FFFFFFF;
        वापस 0x80000000;
    पूर्ण
    अन्यथा अगर ( aExp <= 0x7E ) अणु
        अगर ( aExp | aSig ) भग्न_उठाओ( भग्न_flag_inexact );
        वापस 0;
    पूर्ण
    aSig = ( aSig | 0x00800000 )<<8;
    z = aSig>>( - shअगरtCount );
    अगर ( (bits32) ( aSig<<( shअगरtCount & 31 ) ) ) अणु
        भग्न_उठाओ( भग्न_flag_inexact );
    पूर्ण
    वापस aSign ? - z : z;

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of converting the single-precision भग्नing-poपूर्णांक value
`a' to the द्विगुन-precision भग्नing-poपूर्णांक क्रमmat.  The conversion is
perक्रमmed according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक
Arithmetic.
-------------------------------------------------------------------------------
*/
भग्न64 भग्न32_to_भग्न64( भग्न32 a )
अणु
    flag aSign;
    पूर्णांक16 aExp;
    bits32 aSig;

    aSig = extractFloat32Frac( a );
    aExp = extractFloat32Exp( a );
    aSign = extractFloat32Sign( a );
    अगर ( aExp == 0xFF ) अणु
        अगर ( aSig ) वापस commonNaNToFloat64( भग्न32ToCommonNaN( a ) );
        वापस packFloat64( aSign, 0x7FF, 0 );
    पूर्ण
    अगर ( aExp == 0 ) अणु
        अगर ( aSig == 0 ) वापस packFloat64( aSign, 0, 0 );
        normalizeFloat32Subnormal( aSig, &aExp, &aSig );
        --aExp;
    पूर्ण
    वापस packFloat64( aSign, aExp + 0x380, ( (bits64) aSig )<<29 );

पूर्ण

#अगर_घोषित FLOATX80

/*
-------------------------------------------------------------------------------
Returns the result of converting the single-precision भग्नing-poपूर्णांक value
`a' to the extended द्विगुन-precision भग्नing-poपूर्णांक क्रमmat.  The conversion
is perक्रमmed according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक
Arithmetic.
-------------------------------------------------------------------------------
*/
भग्नx80 भग्न32_to_भग्नx80( भग्न32 a )
अणु
    flag aSign;
    पूर्णांक16 aExp;
    bits32 aSig;

    aSig = extractFloat32Frac( a );
    aExp = extractFloat32Exp( a );
    aSign = extractFloat32Sign( a );
    अगर ( aExp == 0xFF ) अणु
        अगर ( aSig ) वापस commonNaNToFloatx80( भग्न32ToCommonNaN( a ) );
        वापस packFloatx80( aSign, 0x7FFF, LIT64( 0x8000000000000000 ) );
    पूर्ण
    अगर ( aExp == 0 ) अणु
        अगर ( aSig == 0 ) वापस packFloatx80( aSign, 0, 0 );
        normalizeFloat32Subnormal( aSig, &aExp, &aSig );
    पूर्ण
    aSig |= 0x00800000;
    वापस packFloatx80( aSign, aExp + 0x3F80, ( (bits64) aSig )<<40 );

पूर्ण

#पूर्ण_अगर

/*
-------------------------------------------------------------------------------
Rounds the single-precision भग्नing-poपूर्णांक value `a' to an पूर्णांकeger, and
वापसs the result as a single-precision भग्नing-poपूर्णांक value.  The
operation is perक्रमmed according to the IEC/IEEE Standard क्रम Binary
Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्न32 भग्न32_round_to_पूर्णांक( काष्ठा roundingData *roundData, भग्न32 a )
अणु
    flag aSign;
    पूर्णांक16 aExp;
    bits32 lastBitMask, roundBitsMask;
    पूर्णांक8 roundingMode;
    भग्न32 z;

    aExp = extractFloat32Exp( a );
    अगर ( 0x96 <= aExp ) अणु
        अगर ( ( aExp == 0xFF ) && extractFloat32Frac( a ) ) अणु
            वापस propagateFloat32NaN( a, a );
        पूर्ण
        वापस a;
    पूर्ण
    roundingMode = roundData->mode;
    अगर ( aExp <= 0x7E ) अणु
        अगर ( (bits32) ( a<<1 ) == 0 ) वापस a;
        roundData->exception |= भग्न_flag_inexact;
        aSign = extractFloat32Sign( a );
        चयन ( roundingMode ) अणु
         हाल भग्न_round_nearest_even:
            अगर ( ( aExp == 0x7E ) && extractFloat32Frac( a ) ) अणु
                वापस packFloat32( aSign, 0x7F, 0 );
            पूर्ण
            अवरोध;
         हाल भग्न_round_करोwn:
            वापस aSign ? 0xBF800000 : 0;
         हाल भग्न_round_up:
            वापस aSign ? 0x80000000 : 0x3F800000;
        पूर्ण
        वापस packFloat32( aSign, 0, 0 );
    पूर्ण
    lastBitMask = 1;
    lastBitMask <<= 0x96 - aExp;
    roundBitsMask = lastBitMask - 1;
    z = a;
    अगर ( roundingMode == भग्न_round_nearest_even ) अणु
        z += lastBitMask>>1;
        अगर ( ( z & roundBitsMask ) == 0 ) z &= ~ lastBitMask;
    पूर्ण
    अन्यथा अगर ( roundingMode != भग्न_round_to_zero ) अणु
        अगर ( extractFloat32Sign( z ) ^ ( roundingMode == भग्न_round_up ) ) अणु
            z += roundBitsMask;
        पूर्ण
    पूर्ण
    z &= ~ roundBitsMask;
    अगर ( z != a ) roundData->exception |= भग्न_flag_inexact;
    वापस z;

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of adding the असलolute values of the single-precision
भग्नing-poपूर्णांक values `a' and `b'.  If `zSign' is true, the sum is negated
beक्रमe being वापसed.  `zSign' is ignored अगर the result is a NaN.  The
addition is perक्रमmed according to the IEC/IEEE Standard क्रम Binary
Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
अटल भग्न32 addFloat32Sigs( काष्ठा roundingData *roundData, भग्न32 a, भग्न32 b, flag zSign )
अणु
    पूर्णांक16 aExp, bExp, zExp;
    bits32 aSig, bSig, zSig;
    पूर्णांक16 expDअगरf;

    aSig = extractFloat32Frac( a );
    aExp = extractFloat32Exp( a );
    bSig = extractFloat32Frac( b );
    bExp = extractFloat32Exp( b );
    expDअगरf = aExp - bExp;
    aSig <<= 6;
    bSig <<= 6;
    अगर ( 0 < expDअगरf ) अणु
        अगर ( aExp == 0xFF ) अणु
            अगर ( aSig ) वापस propagateFloat32NaN( a, b );
            वापस a;
        पूर्ण
        अगर ( bExp == 0 ) अणु
            --expDअगरf;
        पूर्ण
        अन्यथा अणु
            bSig |= 0x20000000;
        पूर्ण
        shअगरt32RightJamming( bSig, expDअगरf, &bSig );
        zExp = aExp;
    पूर्ण
    अन्यथा अगर ( expDअगरf < 0 ) अणु
        अगर ( bExp == 0xFF ) अणु
            अगर ( bSig ) वापस propagateFloat32NaN( a, b );
            वापस packFloat32( zSign, 0xFF, 0 );
        पूर्ण
        अगर ( aExp == 0 ) अणु
            ++expDअगरf;
        पूर्ण
        अन्यथा अणु
            aSig |= 0x20000000;
        पूर्ण
        shअगरt32RightJamming( aSig, - expDअगरf, &aSig );
        zExp = bExp;
    पूर्ण
    अन्यथा अणु
        अगर ( aExp == 0xFF ) अणु
            अगर ( aSig | bSig ) वापस propagateFloat32NaN( a, b );
            वापस a;
        पूर्ण
        अगर ( aExp == 0 ) वापस packFloat32( zSign, 0, ( aSig + bSig )>>6 );
        zSig = 0x40000000 + aSig + bSig;
        zExp = aExp;
        जाओ roundAndPack;
    पूर्ण
    aSig |= 0x20000000;
    zSig = ( aSig + bSig )<<1;
    --zExp;
    अगर ( (sbits32) zSig < 0 ) अणु
        zSig = aSig + bSig;
        ++zExp;
    पूर्ण
 roundAndPack:
    वापस roundAndPackFloat32( roundData, zSign, zExp, zSig );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of subtracting the असलolute values of the single-
precision भग्नing-poपूर्णांक values `a' and `b'.  If `zSign' is true, the
dअगरference is negated beक्रमe being वापसed.  `zSign' is ignored अगर the
result is a NaN.  The subtraction is perक्रमmed according to the IEC/IEEE
Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
अटल भग्न32 subFloat32Sigs( काष्ठा roundingData *roundData, भग्न32 a, भग्न32 b, flag zSign )
अणु
    पूर्णांक16 aExp, bExp, zExp;
    bits32 aSig, bSig, zSig;
    पूर्णांक16 expDअगरf;

    aSig = extractFloat32Frac( a );
    aExp = extractFloat32Exp( a );
    bSig = extractFloat32Frac( b );
    bExp = extractFloat32Exp( b );
    expDअगरf = aExp - bExp;
    aSig <<= 7;
    bSig <<= 7;
    अगर ( 0 < expDअगरf ) जाओ aExpBigger;
    अगर ( expDअगरf < 0 ) जाओ bExpBigger;
    अगर ( aExp == 0xFF ) अणु
        अगर ( aSig | bSig ) वापस propagateFloat32NaN( a, b );
        roundData->exception |= भग्न_flag_invalid;
        वापस भग्न32_शेष_nan;
    पूर्ण
    अगर ( aExp == 0 ) अणु
        aExp = 1;
        bExp = 1;
    पूर्ण
    अगर ( bSig < aSig ) जाओ aBigger;
    अगर ( aSig < bSig ) जाओ bBigger;
    वापस packFloat32( roundData->mode == भग्न_round_करोwn, 0, 0 );
 bExpBigger:
    अगर ( bExp == 0xFF ) अणु
        अगर ( bSig ) वापस propagateFloat32NaN( a, b );
        वापस packFloat32( zSign ^ 1, 0xFF, 0 );
    पूर्ण
    अगर ( aExp == 0 ) अणु
        ++expDअगरf;
    पूर्ण
    अन्यथा अणु
        aSig |= 0x40000000;
    पूर्ण
    shअगरt32RightJamming( aSig, - expDअगरf, &aSig );
    bSig |= 0x40000000;
 bBigger:
    zSig = bSig - aSig;
    zExp = bExp;
    zSign ^= 1;
    जाओ normalizeRoundAndPack;
 aExpBigger:
    अगर ( aExp == 0xFF ) अणु
        अगर ( aSig ) वापस propagateFloat32NaN( a, b );
        वापस a;
    पूर्ण
    अगर ( bExp == 0 ) अणु
        --expDअगरf;
    पूर्ण
    अन्यथा अणु
        bSig |= 0x40000000;
    पूर्ण
    shअगरt32RightJamming( bSig, expDअगरf, &bSig );
    aSig |= 0x40000000;
 aBigger:
    zSig = aSig - bSig;
    zExp = aExp;
 normalizeRoundAndPack:
    --zExp;
    वापस normalizeRoundAndPackFloat32( roundData, zSign, zExp, zSig );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of adding the single-precision भग्नing-poपूर्णांक values `a'
and `b'.  The operation is perक्रमmed according to the IEC/IEEE Standard क्रम
Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्न32 भग्न32_add( काष्ठा roundingData *roundData, भग्न32 a, भग्न32 b )
अणु
    flag aSign, bSign;

    aSign = extractFloat32Sign( a );
    bSign = extractFloat32Sign( b );
    अगर ( aSign == bSign ) अणु
        वापस addFloat32Sigs( roundData, a, b, aSign );
    पूर्ण
    अन्यथा अणु
        वापस subFloat32Sigs( roundData, a, b, aSign );
    पूर्ण

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of subtracting the single-precision भग्नing-poपूर्णांक values
`a' and `b'.  The operation is perक्रमmed according to the IEC/IEEE Standard
क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्न32 भग्न32_sub( काष्ठा roundingData *roundData, भग्न32 a, भग्न32 b )
अणु
    flag aSign, bSign;

    aSign = extractFloat32Sign( a );
    bSign = extractFloat32Sign( b );
    अगर ( aSign == bSign ) अणु
        वापस subFloat32Sigs( roundData, a, b, aSign );
    पूर्ण
    अन्यथा अणु
        वापस addFloat32Sigs( roundData, a, b, aSign );
    पूर्ण

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of multiplying the single-precision भग्नing-poपूर्णांक values
`a' and `b'.  The operation is perक्रमmed according to the IEC/IEEE Standard
क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्न32 भग्न32_mul( काष्ठा roundingData *roundData, भग्न32 a, भग्न32 b )
अणु
    flag aSign, bSign, zSign;
    पूर्णांक16 aExp, bExp, zExp;
    bits32 aSig, bSig;
    bits64 zSig64;
    bits32 zSig;

    aSig = extractFloat32Frac( a );
    aExp = extractFloat32Exp( a );
    aSign = extractFloat32Sign( a );
    bSig = extractFloat32Frac( b );
    bExp = extractFloat32Exp( b );
    bSign = extractFloat32Sign( b );
    zSign = aSign ^ bSign;
    अगर ( aExp == 0xFF ) अणु
        अगर ( aSig || ( ( bExp == 0xFF ) && bSig ) ) अणु
            वापस propagateFloat32NaN( a, b );
        पूर्ण
        अगर ( ( bExp | bSig ) == 0 ) अणु
            roundData->exception |= भग्न_flag_invalid;
            वापस भग्न32_शेष_nan;
        पूर्ण
        वापस packFloat32( zSign, 0xFF, 0 );
    पूर्ण
    अगर ( bExp == 0xFF ) अणु
        अगर ( bSig ) वापस propagateFloat32NaN( a, b );
        अगर ( ( aExp | aSig ) == 0 ) अणु
            roundData->exception |= भग्न_flag_invalid;
            वापस भग्न32_शेष_nan;
        पूर्ण
        वापस packFloat32( zSign, 0xFF, 0 );
    पूर्ण
    अगर ( aExp == 0 ) अणु
        अगर ( aSig == 0 ) वापस packFloat32( zSign, 0, 0 );
        normalizeFloat32Subnormal( aSig, &aExp, &aSig );
    पूर्ण
    अगर ( bExp == 0 ) अणु
        अगर ( bSig == 0 ) वापस packFloat32( zSign, 0, 0 );
        normalizeFloat32Subnormal( bSig, &bExp, &bSig );
    पूर्ण
    zExp = aExp + bExp - 0x7F;
    aSig = ( aSig | 0x00800000 )<<7;
    bSig = ( bSig | 0x00800000 )<<8;
    shअगरt64RightJamming( ( (bits64) aSig ) * bSig, 32, &zSig64 );
    zSig = zSig64;
    अगर ( 0 <= (sbits32) ( zSig<<1 ) ) अणु
        zSig <<= 1;
        --zExp;
    पूर्ण
    वापस roundAndPackFloat32( roundData, zSign, zExp, zSig );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of भागiding the single-precision भग्नing-poपूर्णांक value `a'
by the corresponding value `b'.  The operation is perक्रमmed according to the
IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्न32 भग्न32_भाग( काष्ठा roundingData *roundData, भग्न32 a, भग्न32 b )
अणु
    flag aSign, bSign, zSign;
    पूर्णांक16 aExp, bExp, zExp;
    bits32 aSig, bSig, zSig;

    aSig = extractFloat32Frac( a );
    aExp = extractFloat32Exp( a );
    aSign = extractFloat32Sign( a );
    bSig = extractFloat32Frac( b );
    bExp = extractFloat32Exp( b );
    bSign = extractFloat32Sign( b );
    zSign = aSign ^ bSign;
    अगर ( aExp == 0xFF ) अणु
        अगर ( aSig ) वापस propagateFloat32NaN( a, b );
        अगर ( bExp == 0xFF ) अणु
            अगर ( bSig ) वापस propagateFloat32NaN( a, b );
            roundData->exception |= भग्न_flag_invalid;
            वापस भग्न32_शेष_nan;
        पूर्ण
        वापस packFloat32( zSign, 0xFF, 0 );
    पूर्ण
    अगर ( bExp == 0xFF ) अणु
        अगर ( bSig ) वापस propagateFloat32NaN( a, b );
        वापस packFloat32( zSign, 0, 0 );
    पूर्ण
    अगर ( bExp == 0 ) अणु
        अगर ( bSig == 0 ) अणु
            अगर ( ( aExp | aSig ) == 0 ) अणु
                roundData->exception |= भग्न_flag_invalid;
                वापस भग्न32_शेष_nan;
            पूर्ण
            roundData->exception |= भग्न_flag_भागbyzero;
            वापस packFloat32( zSign, 0xFF, 0 );
        पूर्ण
        normalizeFloat32Subnormal( bSig, &bExp, &bSig );
    पूर्ण
    अगर ( aExp == 0 ) अणु
        अगर ( aSig == 0 ) वापस packFloat32( zSign, 0, 0 );
        normalizeFloat32Subnormal( aSig, &aExp, &aSig );
    पूर्ण
    zExp = aExp - bExp + 0x7D;
    aSig = ( aSig | 0x00800000 )<<7;
    bSig = ( bSig | 0x00800000 )<<8;
    अगर ( bSig <= ( aSig + aSig ) ) अणु
        aSig >>= 1;
        ++zExp;
    पूर्ण
    अणु
        bits64 पंचांगp = ( (bits64) aSig )<<32;
        करो_भाग( पंचांगp, bSig );
        zSig = पंचांगp;
    पूर्ण
    अगर ( ( zSig & 0x3F ) == 0 ) अणु
        zSig |= ( ( (bits64) bSig ) * zSig != ( (bits64) aSig )<<32 );
    पूर्ण
    वापस roundAndPackFloat32( roundData, zSign, zExp, zSig );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the reमुख्यder of the single-precision भग्नing-poपूर्णांक value `a'
with respect to the corresponding value `b'.  The operation is perक्रमmed
according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्न32 भग्न32_rem( काष्ठा roundingData *roundData, भग्न32 a, भग्न32 b )
अणु
    flag aSign, bSign, zSign;
    पूर्णांक16 aExp, bExp, expDअगरf;
    bits32 aSig, bSig;
    bits32 q;
    bits64 aSig64, bSig64, q64;
    bits32 alternateASig;
    sbits32 sigMean;

    aSig = extractFloat32Frac( a );
    aExp = extractFloat32Exp( a );
    aSign = extractFloat32Sign( a );
    bSig = extractFloat32Frac( b );
    bExp = extractFloat32Exp( b );
    bSign = extractFloat32Sign( b );
    अगर ( aExp == 0xFF ) अणु
        अगर ( aSig || ( ( bExp == 0xFF ) && bSig ) ) अणु
            वापस propagateFloat32NaN( a, b );
        पूर्ण
        roundData->exception |= भग्न_flag_invalid;
        वापस भग्न32_शेष_nan;
    पूर्ण
    अगर ( bExp == 0xFF ) अणु
        अगर ( bSig ) वापस propagateFloat32NaN( a, b );
        वापस a;
    पूर्ण
    अगर ( bExp == 0 ) अणु
        अगर ( bSig == 0 ) अणु
            roundData->exception |= भग्न_flag_invalid;
            वापस भग्न32_शेष_nan;
        पूर्ण
        normalizeFloat32Subnormal( bSig, &bExp, &bSig );
    पूर्ण
    अगर ( aExp == 0 ) अणु
        अगर ( aSig == 0 ) वापस a;
        normalizeFloat32Subnormal( aSig, &aExp, &aSig );
    पूर्ण
    expDअगरf = aExp - bExp;
    aSig |= 0x00800000;
    bSig |= 0x00800000;
    अगर ( expDअगरf < 32 ) अणु
        aSig <<= 8;
        bSig <<= 8;
        अगर ( expDअगरf < 0 ) अणु
            अगर ( expDअगरf < -1 ) वापस a;
            aSig >>= 1;
        पूर्ण
        q = ( bSig <= aSig );
        अगर ( q ) aSig -= bSig;
        अगर ( 0 < expDअगरf ) अणु
            bits64 पंचांगp = ( (bits64) aSig )<<32;
            करो_भाग( पंचांगp, bSig );
            q = पंचांगp;
            q >>= 32 - expDअगरf;
            bSig >>= 2;
            aSig = ( ( aSig>>1 )<<( expDअगरf - 1 ) ) - bSig * q;
        पूर्ण
        अन्यथा अणु
            aSig >>= 2;
            bSig >>= 2;
        पूर्ण
    पूर्ण
    अन्यथा अणु
        अगर ( bSig <= aSig ) aSig -= bSig;
        aSig64 = ( (bits64) aSig )<<40;
        bSig64 = ( (bits64) bSig )<<40;
        expDअगरf -= 64;
        जबतक ( 0 < expDअगरf ) अणु
            q64 = estimateDiv128To64( aSig64, 0, bSig64 );
            q64 = ( 2 < q64 ) ? q64 - 2 : 0;
            aSig64 = - ( ( bSig * q64 )<<38 );
            expDअगरf -= 62;
        पूर्ण
        expDअगरf += 64;
        q64 = estimateDiv128To64( aSig64, 0, bSig64 );
        q64 = ( 2 < q64 ) ? q64 - 2 : 0;
        q = q64>>( 64 - expDअगरf );
        bSig <<= 6;
        aSig = ( ( aSig64>>33 )<<( expDअगरf - 1 ) ) - bSig * q;
    पूर्ण
    करो अणु
        alternateASig = aSig;
        ++q;
        aSig -= bSig;
    पूर्ण जबतक ( 0 <= (sbits32) aSig );
    sigMean = aSig + alternateASig;
    अगर ( ( sigMean < 0 ) || ( ( sigMean == 0 ) && ( q & 1 ) ) ) अणु
        aSig = alternateASig;
    पूर्ण
    zSign = ( (sbits32) aSig < 0 );
    अगर ( zSign ) aSig = - aSig;
    वापस normalizeRoundAndPackFloat32( roundData, aSign ^ zSign, bExp, aSig );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the square root of the single-precision भग्नing-poपूर्णांक value `a'.
The operation is perक्रमmed according to the IEC/IEEE Standard क्रम Binary
Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्न32 भग्न32_वर्ग_मूल( काष्ठा roundingData *roundData, भग्न32 a )
अणु
    flag aSign;
    पूर्णांक16 aExp, zExp;
    bits32 aSig, zSig;
    bits64 rem, term;

    aSig = extractFloat32Frac( a );
    aExp = extractFloat32Exp( a );
    aSign = extractFloat32Sign( a );
    अगर ( aExp == 0xFF ) अणु
        अगर ( aSig ) वापस propagateFloat32NaN( a, 0 );
        अगर ( ! aSign ) वापस a;
        roundData->exception |= भग्न_flag_invalid;
        वापस भग्न32_शेष_nan;
    पूर्ण
    अगर ( aSign ) अणु
        अगर ( ( aExp | aSig ) == 0 ) वापस a;
        roundData->exception |= भग्न_flag_invalid;
        वापस भग्न32_शेष_nan;
    पूर्ण
    अगर ( aExp == 0 ) अणु
        अगर ( aSig == 0 ) वापस 0;
        normalizeFloat32Subnormal( aSig, &aExp, &aSig );
    पूर्ण
    zExp = ( ( aExp - 0x7F )>>1 ) + 0x7E;
    aSig = ( aSig | 0x00800000 )<<8;
    zSig = estimateSqrt32( aExp, aSig ) + 2;
    अगर ( ( zSig & 0x7F ) <= 5 ) अणु
        अगर ( zSig < 2 ) अणु
            zSig = 0xFFFFFFFF;
        पूर्ण
        अन्यथा अणु
            aSig >>= aExp & 1;
            term = ( (bits64) zSig ) * zSig;
            rem = ( ( (bits64) aSig )<<32 ) - term;
            जबतक ( (sbits64) rem < 0 ) अणु
                --zSig;
                rem += ( ( (bits64) zSig )<<1 ) | 1;
            पूर्ण
            zSig |= ( rem != 0 );
        पूर्ण
    पूर्ण
    shअगरt32RightJamming( zSig, 1, &zSig );
    वापस roundAndPackFloat32( roundData, 0, zExp, zSig );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns 1 अगर the single-precision भग्नing-poपूर्णांक value `a' is equal to the
corresponding value `b', and 0 otherwise.  The comparison is perक्रमmed
according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
flag भग्न32_eq( भग्न32 a, भग्न32 b )
अणु

    अगर (    ( ( extractFloat32Exp( a ) == 0xFF ) && extractFloat32Frac( a ) )
         || ( ( extractFloat32Exp( b ) == 0xFF ) && extractFloat32Frac( b ) )
       ) अणु
        अगर ( भग्न32_is_संकेतing_nan( a ) || भग्न32_is_संकेतing_nan( b ) ) अणु
            भग्न_उठाओ( भग्न_flag_invalid );
        पूर्ण
        वापस 0;
    पूर्ण
    वापस ( a == b ) || ( (bits32) ( ( a | b )<<1 ) == 0 );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns 1 अगर the single-precision भग्नing-poपूर्णांक value `a' is less than or
equal to the corresponding value `b', and 0 otherwise.  The comparison is
perक्रमmed according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक
Arithmetic.
-------------------------------------------------------------------------------
*/
flag भग्न32_le( भग्न32 a, भग्न32 b )
अणु
    flag aSign, bSign;

    अगर (    ( ( extractFloat32Exp( a ) == 0xFF ) && extractFloat32Frac( a ) )
         || ( ( extractFloat32Exp( b ) == 0xFF ) && extractFloat32Frac( b ) )
       ) अणु
        भग्न_उठाओ( भग्न_flag_invalid );
        वापस 0;
    पूर्ण
    aSign = extractFloat32Sign( a );
    bSign = extractFloat32Sign( b );
    अगर ( aSign != bSign ) वापस aSign || ( (bits32) ( ( a | b )<<1 ) == 0 );
    वापस ( a == b ) || ( aSign ^ ( a < b ) );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns 1 अगर the single-precision भग्नing-poपूर्णांक value `a' is less than
the corresponding value `b', and 0 otherwise.  The comparison is perक्रमmed
according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
flag भग्न32_lt( भग्न32 a, भग्न32 b )
अणु
    flag aSign, bSign;

    अगर (    ( ( extractFloat32Exp( a ) == 0xFF ) && extractFloat32Frac( a ) )
         || ( ( extractFloat32Exp( b ) == 0xFF ) && extractFloat32Frac( b ) )
       ) अणु
        भग्न_उठाओ( भग्न_flag_invalid );
        वापस 0;
    पूर्ण
    aSign = extractFloat32Sign( a );
    bSign = extractFloat32Sign( b );
    अगर ( aSign != bSign ) वापस aSign && ( (bits32) ( ( a | b )<<1 ) != 0 );
    वापस ( a != b ) && ( aSign ^ ( a < b ) );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns 1 अगर the single-precision भग्नing-poपूर्णांक value `a' is equal to the
corresponding value `b', and 0 otherwise.  The invalid exception is उठाओd
अगर either opeअक्रम is a NaN.  Otherwise, the comparison is perक्रमmed
according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
flag भग्न32_eq_संकेतing( भग्न32 a, भग्न32 b )
अणु

    अगर (    ( ( extractFloat32Exp( a ) == 0xFF ) && extractFloat32Frac( a ) )
         || ( ( extractFloat32Exp( b ) == 0xFF ) && extractFloat32Frac( b ) )
       ) अणु
        भग्न_उठाओ( भग्न_flag_invalid );
        वापस 0;
    पूर्ण
    वापस ( a == b ) || ( (bits32) ( ( a | b )<<1 ) == 0 );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns 1 अगर the single-precision भग्नing-poपूर्णांक value `a' is less than or
equal to the corresponding value `b', and 0 otherwise.  Quiet NaNs करो not
cause an exception.  Otherwise, the comparison is perक्रमmed according to the
IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
flag भग्न32_le_quiet( भग्न32 a, भग्न32 b )
अणु
    flag aSign, bSign;
    //पूर्णांक16 aExp, bExp;

    अगर (    ( ( extractFloat32Exp( a ) == 0xFF ) && extractFloat32Frac( a ) )
         || ( ( extractFloat32Exp( b ) == 0xFF ) && extractFloat32Frac( b ) )
       ) अणु
        /* Do nothing, even अगर NaN as we're quiet */
        वापस 0;
    पूर्ण
    aSign = extractFloat32Sign( a );
    bSign = extractFloat32Sign( b );
    अगर ( aSign != bSign ) वापस aSign || ( (bits32) ( ( a | b )<<1 ) == 0 );
    वापस ( a == b ) || ( aSign ^ ( a < b ) );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns 1 अगर the single-precision भग्नing-poपूर्णांक value `a' is less than
the corresponding value `b', and 0 otherwise.  Quiet NaNs करो not cause an
exception.  Otherwise, the comparison is perक्रमmed according to the IEC/IEEE
Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
flag भग्न32_lt_quiet( भग्न32 a, भग्न32 b )
अणु
    flag aSign, bSign;

    अगर (    ( ( extractFloat32Exp( a ) == 0xFF ) && extractFloat32Frac( a ) )
         || ( ( extractFloat32Exp( b ) == 0xFF ) && extractFloat32Frac( b ) )
       ) अणु
        /* Do nothing, even अगर NaN as we're quiet */
        वापस 0;
    पूर्ण
    aSign = extractFloat32Sign( a );
    bSign = extractFloat32Sign( b );
    अगर ( aSign != bSign ) वापस aSign && ( (bits32) ( ( a | b )<<1 ) != 0 );
    वापस ( a != b ) && ( aSign ^ ( a < b ) );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of converting the द्विगुन-precision भग्नing-poपूर्णांक value
`a' to the 32-bit two's complement पूर्णांकeger क्रमmat.  The conversion is
perक्रमmed according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक
Arithmetic---which means in particular that the conversion is rounded
according to the current rounding mode.  If `a' is a NaN, the largest
positive पूर्णांकeger is वापसed.  Otherwise, अगर the conversion overflows, the
largest पूर्णांकeger with the same sign as `a' is वापसed.
-------------------------------------------------------------------------------
*/
पूर्णांक32 भग्न64_to_पूर्णांक32( काष्ठा roundingData *roundData, भग्न64 a )
अणु
    flag aSign;
    पूर्णांक16 aExp, shअगरtCount;
    bits64 aSig;

    aSig = extractFloat64Frac( a );
    aExp = extractFloat64Exp( a );
    aSign = extractFloat64Sign( a );
    अगर ( ( aExp == 0x7FF ) && aSig ) aSign = 0;
    अगर ( aExp ) aSig |= LIT64( 0x0010000000000000 );
    shअगरtCount = 0x42C - aExp;
    अगर ( 0 < shअगरtCount ) shअगरt64RightJamming( aSig, shअगरtCount, &aSig );
    वापस roundAndPackInt32( roundData, aSign, aSig );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of converting the द्विगुन-precision भग्नing-poपूर्णांक value
`a' to the 32-bit two's complement पूर्णांकeger क्रमmat.  The conversion is
perक्रमmed according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक
Arithmetic, except that the conversion is always rounded toward zero.  If
`a' is a NaN, the largest positive पूर्णांकeger is वापसed.  Otherwise, अगर the
conversion overflows, the largest पूर्णांकeger with the same sign as `a' is
वापसed.
-------------------------------------------------------------------------------
*/
पूर्णांक32 भग्न64_to_पूर्णांक32_round_to_zero( भग्न64 a )
अणु
    flag aSign;
    पूर्णांक16 aExp, shअगरtCount;
    bits64 aSig, savedASig;
    पूर्णांक32 z;

    aSig = extractFloat64Frac( a );
    aExp = extractFloat64Exp( a );
    aSign = extractFloat64Sign( a );
    shअगरtCount = 0x433 - aExp;
    अगर ( shअगरtCount < 21 ) अणु
        अगर ( ( aExp == 0x7FF ) && aSig ) aSign = 0;
        जाओ invalid;
    पूर्ण
    अन्यथा अगर ( 52 < shअगरtCount ) अणु
        अगर ( aExp || aSig ) भग्न_उठाओ( भग्न_flag_inexact );
        वापस 0;
    पूर्ण
    aSig |= LIT64( 0x0010000000000000 );
    savedASig = aSig;
    aSig >>= shअगरtCount;
    z = aSig;
    अगर ( aSign ) z = - z;
    अगर ( ( z < 0 ) ^ aSign ) अणु
 invalid:
        भग्न_उठाओ( भग्न_flag_invalid );
        वापस aSign ? 0x80000000 : 0x7FFFFFFF;
    पूर्ण
    अगर ( ( aSig<<shअगरtCount ) != savedASig ) अणु
        भग्न_उठाओ( भग्न_flag_inexact );
    पूर्ण
    वापस z;

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of converting the द्विगुन-precision भग्नing-poपूर्णांक value
`a' to the 32-bit two's complement अचिन्हित पूर्णांकeger क्रमmat.  The conversion
is perक्रमmed according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक
Arithmetic---which means in particular that the conversion is rounded
according to the current rounding mode.  If `a' is a NaN, the largest
positive पूर्णांकeger is वापसed.  Otherwise, अगर the conversion overflows, the
largest positive पूर्णांकeger is वापसed.
-------------------------------------------------------------------------------
*/
पूर्णांक32 भग्न64_to_uपूर्णांक32( काष्ठा roundingData *roundData, भग्न64 a )
अणु
    flag aSign;
    पूर्णांक16 aExp, shअगरtCount;
    bits64 aSig;

    aSig = extractFloat64Frac( a );
    aExp = extractFloat64Exp( a );
    aSign = 0; //extractFloat64Sign( a );
    //अगर ( ( aExp == 0x7FF ) && aSig ) aSign = 0;
    अगर ( aExp ) aSig |= LIT64( 0x0010000000000000 );
    shअगरtCount = 0x42C - aExp;
    अगर ( 0 < shअगरtCount ) shअगरt64RightJamming( aSig, shअगरtCount, &aSig );
    वापस roundAndPackInt32( roundData, aSign, aSig );
पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of converting the द्विगुन-precision भग्नing-poपूर्णांक value
`a' to the 32-bit two's complement पूर्णांकeger क्रमmat.  The conversion is
perक्रमmed according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक
Arithmetic, except that the conversion is always rounded toward zero.  If
`a' is a NaN, the largest positive पूर्णांकeger is वापसed.  Otherwise, अगर the
conversion overflows, the largest positive पूर्णांकeger is वापसed.
-------------------------------------------------------------------------------
*/
पूर्णांक32 भग्न64_to_uपूर्णांक32_round_to_zero( भग्न64 a )
अणु
    flag aSign;
    पूर्णांक16 aExp, shअगरtCount;
    bits64 aSig, savedASig;
    पूर्णांक32 z;

    aSig = extractFloat64Frac( a );
    aExp = extractFloat64Exp( a );
    aSign = extractFloat64Sign( a );
    shअगरtCount = 0x433 - aExp;
    अगर ( shअगरtCount < 21 ) अणु
        अगर ( ( aExp == 0x7FF ) && aSig ) aSign = 0;
        जाओ invalid;
    पूर्ण
    अन्यथा अगर ( 52 < shअगरtCount ) अणु
        अगर ( aExp || aSig ) भग्न_उठाओ( भग्न_flag_inexact );
        वापस 0;
    पूर्ण
    aSig |= LIT64( 0x0010000000000000 );
    savedASig = aSig;
    aSig >>= shअगरtCount;
    z = aSig;
    अगर ( aSign ) z = - z;
    अगर ( ( z < 0 ) ^ aSign ) अणु
 invalid:
        भग्न_उठाओ( भग्न_flag_invalid );
        वापस aSign ? 0x80000000 : 0x7FFFFFFF;
    पूर्ण
    अगर ( ( aSig<<shअगरtCount ) != savedASig ) अणु
        भग्न_उठाओ( भग्न_flag_inexact );
    पूर्ण
    वापस z;
पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of converting the द्विगुन-precision भग्नing-poपूर्णांक value
`a' to the single-precision भग्नing-poपूर्णांक क्रमmat.  The conversion is
perक्रमmed according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक
Arithmetic.
-------------------------------------------------------------------------------
*/
भग्न32 भग्न64_to_भग्न32( काष्ठा roundingData *roundData, भग्न64 a )
अणु
    flag aSign;
    पूर्णांक16 aExp;
    bits64 aSig;
    bits32 zSig;

    aSig = extractFloat64Frac( a );
    aExp = extractFloat64Exp( a );
    aSign = extractFloat64Sign( a );
    अगर ( aExp == 0x7FF ) अणु
        अगर ( aSig ) वापस commonNaNToFloat32( भग्न64ToCommonNaN( a ) );
        वापस packFloat32( aSign, 0xFF, 0 );
    पूर्ण
    shअगरt64RightJamming( aSig, 22, &aSig );
    zSig = aSig;
    अगर ( aExp || zSig ) अणु
        zSig |= 0x40000000;
        aExp -= 0x381;
    पूर्ण
    वापस roundAndPackFloat32( roundData, aSign, aExp, zSig );

पूर्ण

#अगर_घोषित FLOATX80

/*
-------------------------------------------------------------------------------
Returns the result of converting the द्विगुन-precision भग्नing-poपूर्णांक value
`a' to the extended द्विगुन-precision भग्नing-poपूर्णांक क्रमmat.  The conversion
is perक्रमmed according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक
Arithmetic.
-------------------------------------------------------------------------------
*/
भग्नx80 भग्न64_to_भग्नx80( भग्न64 a )
अणु
    flag aSign;
    पूर्णांक16 aExp;
    bits64 aSig;

    aSig = extractFloat64Frac( a );
    aExp = extractFloat64Exp( a );
    aSign = extractFloat64Sign( a );
    अगर ( aExp == 0x7FF ) अणु
        अगर ( aSig ) वापस commonNaNToFloatx80( भग्न64ToCommonNaN( a ) );
        वापस packFloatx80( aSign, 0x7FFF, LIT64( 0x8000000000000000 ) );
    पूर्ण
    अगर ( aExp == 0 ) अणु
        अगर ( aSig == 0 ) वापस packFloatx80( aSign, 0, 0 );
        normalizeFloat64Subnormal( aSig, &aExp, &aSig );
    पूर्ण
    वापस
        packFloatx80(
            aSign, aExp + 0x3C00, ( aSig | LIT64( 0x0010000000000000 ) )<<11 );

पूर्ण

#पूर्ण_अगर

/*
-------------------------------------------------------------------------------
Rounds the द्विगुन-precision भग्नing-poपूर्णांक value `a' to an पूर्णांकeger, and
वापसs the result as a द्विगुन-precision भग्नing-poपूर्णांक value.  The
operation is perक्रमmed according to the IEC/IEEE Standard क्रम Binary
Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्न64 भग्न64_round_to_पूर्णांक( काष्ठा roundingData *roundData, भग्न64 a )
अणु
    flag aSign;
    पूर्णांक16 aExp;
    bits64 lastBitMask, roundBitsMask;
    पूर्णांक8 roundingMode;
    भग्न64 z;

    aExp = extractFloat64Exp( a );
    अगर ( 0x433 <= aExp ) अणु
        अगर ( ( aExp == 0x7FF ) && extractFloat64Frac( a ) ) अणु
            वापस propagateFloat64NaN( a, a );
        पूर्ण
        वापस a;
    पूर्ण
    अगर ( aExp <= 0x3FE ) अणु
        अगर ( (bits64) ( a<<1 ) == 0 ) वापस a;
        roundData->exception |= भग्न_flag_inexact;
        aSign = extractFloat64Sign( a );
        चयन ( roundData->mode ) अणु
         हाल भग्न_round_nearest_even:
            अगर ( ( aExp == 0x3FE ) && extractFloat64Frac( a ) ) अणु
                वापस packFloat64( aSign, 0x3FF, 0 );
            पूर्ण
            अवरोध;
         हाल भग्न_round_करोwn:
            वापस aSign ? LIT64( 0xBFF0000000000000 ) : 0;
         हाल भग्न_round_up:
            वापस
            aSign ? LIT64( 0x8000000000000000 ) : LIT64( 0x3FF0000000000000 );
        पूर्ण
        वापस packFloat64( aSign, 0, 0 );
    पूर्ण
    lastBitMask = 1;
    lastBitMask <<= 0x433 - aExp;
    roundBitsMask = lastBitMask - 1;
    z = a;
    roundingMode = roundData->mode;
    अगर ( roundingMode == भग्न_round_nearest_even ) अणु
        z += lastBitMask>>1;
        अगर ( ( z & roundBitsMask ) == 0 ) z &= ~ lastBitMask;
    पूर्ण
    अन्यथा अगर ( roundingMode != भग्न_round_to_zero ) अणु
        अगर ( extractFloat64Sign( z ) ^ ( roundingMode == भग्न_round_up ) ) अणु
            z += roundBitsMask;
        पूर्ण
    पूर्ण
    z &= ~ roundBitsMask;
    अगर ( z != a ) roundData->exception |= भग्न_flag_inexact;
    वापस z;

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of adding the असलolute values of the द्विगुन-precision
भग्नing-poपूर्णांक values `a' and `b'.  If `zSign' is true, the sum is negated
beक्रमe being वापसed.  `zSign' is ignored अगर the result is a NaN.  The
addition is perक्रमmed according to the IEC/IEEE Standard क्रम Binary
Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
अटल भग्न64 addFloat64Sigs( काष्ठा roundingData *roundData, भग्न64 a, भग्न64 b, flag zSign )
अणु
    पूर्णांक16 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig;
    पूर्णांक16 expDअगरf;

    aSig = extractFloat64Frac( a );
    aExp = extractFloat64Exp( a );
    bSig = extractFloat64Frac( b );
    bExp = extractFloat64Exp( b );
    expDअगरf = aExp - bExp;
    aSig <<= 9;
    bSig <<= 9;
    अगर ( 0 < expDअगरf ) अणु
        अगर ( aExp == 0x7FF ) अणु
            अगर ( aSig ) वापस propagateFloat64NaN( a, b );
            वापस a;
        पूर्ण
        अगर ( bExp == 0 ) अणु
            --expDअगरf;
        पूर्ण
        अन्यथा अणु
            bSig |= LIT64( 0x2000000000000000 );
        पूर्ण
        shअगरt64RightJamming( bSig, expDअगरf, &bSig );
        zExp = aExp;
    पूर्ण
    अन्यथा अगर ( expDअगरf < 0 ) अणु
        अगर ( bExp == 0x7FF ) अणु
            अगर ( bSig ) वापस propagateFloat64NaN( a, b );
            वापस packFloat64( zSign, 0x7FF, 0 );
        पूर्ण
        अगर ( aExp == 0 ) अणु
            ++expDअगरf;
        पूर्ण
        अन्यथा अणु
            aSig |= LIT64( 0x2000000000000000 );
        पूर्ण
        shअगरt64RightJamming( aSig, - expDअगरf, &aSig );
        zExp = bExp;
    पूर्ण
    अन्यथा अणु
        अगर ( aExp == 0x7FF ) अणु
            अगर ( aSig | bSig ) वापस propagateFloat64NaN( a, b );
            वापस a;
        पूर्ण
        अगर ( aExp == 0 ) वापस packFloat64( zSign, 0, ( aSig + bSig )>>9 );
        zSig = LIT64( 0x4000000000000000 ) + aSig + bSig;
        zExp = aExp;
        जाओ roundAndPack;
    पूर्ण
    aSig |= LIT64( 0x2000000000000000 );
    zSig = ( aSig + bSig )<<1;
    --zExp;
    अगर ( (sbits64) zSig < 0 ) अणु
        zSig = aSig + bSig;
        ++zExp;
    पूर्ण
 roundAndPack:
    वापस roundAndPackFloat64( roundData, zSign, zExp, zSig );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of subtracting the असलolute values of the द्विगुन-
precision भग्नing-poपूर्णांक values `a' and `b'.  If `zSign' is true, the
dअगरference is negated beक्रमe being वापसed.  `zSign' is ignored अगर the
result is a NaN.  The subtraction is perक्रमmed according to the IEC/IEEE
Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
अटल भग्न64 subFloat64Sigs( काष्ठा roundingData *roundData, भग्न64 a, भग्न64 b, flag zSign )
अणु
    पूर्णांक16 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig;
    पूर्णांक16 expDअगरf;

    aSig = extractFloat64Frac( a );
    aExp = extractFloat64Exp( a );
    bSig = extractFloat64Frac( b );
    bExp = extractFloat64Exp( b );
    expDअगरf = aExp - bExp;
    aSig <<= 10;
    bSig <<= 10;
    अगर ( 0 < expDअगरf ) जाओ aExpBigger;
    अगर ( expDअगरf < 0 ) जाओ bExpBigger;
    अगर ( aExp == 0x7FF ) अणु
        अगर ( aSig | bSig ) वापस propagateFloat64NaN( a, b );
        roundData->exception |= भग्न_flag_invalid;
        वापस भग्न64_शेष_nan;
    पूर्ण
    अगर ( aExp == 0 ) अणु
        aExp = 1;
        bExp = 1;
    पूर्ण
    अगर ( bSig < aSig ) जाओ aBigger;
    अगर ( aSig < bSig ) जाओ bBigger;
    वापस packFloat64( roundData->mode == भग्न_round_करोwn, 0, 0 );
 bExpBigger:
    अगर ( bExp == 0x7FF ) अणु
        अगर ( bSig ) वापस propagateFloat64NaN( a, b );
        वापस packFloat64( zSign ^ 1, 0x7FF, 0 );
    पूर्ण
    अगर ( aExp == 0 ) अणु
        ++expDअगरf;
    पूर्ण
    अन्यथा अणु
        aSig |= LIT64( 0x4000000000000000 );
    पूर्ण
    shअगरt64RightJamming( aSig, - expDअगरf, &aSig );
    bSig |= LIT64( 0x4000000000000000 );
 bBigger:
    zSig = bSig - aSig;
    zExp = bExp;
    zSign ^= 1;
    जाओ normalizeRoundAndPack;
 aExpBigger:
    अगर ( aExp == 0x7FF ) अणु
        अगर ( aSig ) वापस propagateFloat64NaN( a, b );
        वापस a;
    पूर्ण
    अगर ( bExp == 0 ) अणु
        --expDअगरf;
    पूर्ण
    अन्यथा अणु
        bSig |= LIT64( 0x4000000000000000 );
    पूर्ण
    shअगरt64RightJamming( bSig, expDअगरf, &bSig );
    aSig |= LIT64( 0x4000000000000000 );
 aBigger:
    zSig = aSig - bSig;
    zExp = aExp;
 normalizeRoundAndPack:
    --zExp;
    वापस normalizeRoundAndPackFloat64( roundData, zSign, zExp, zSig );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of adding the द्विगुन-precision भग्नing-poपूर्णांक values `a'
and `b'.  The operation is perक्रमmed according to the IEC/IEEE Standard क्रम
Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्न64 भग्न64_add( काष्ठा roundingData *roundData, भग्न64 a, भग्न64 b )
अणु
    flag aSign, bSign;

    aSign = extractFloat64Sign( a );
    bSign = extractFloat64Sign( b );
    अगर ( aSign == bSign ) अणु
        वापस addFloat64Sigs( roundData, a, b, aSign );
    पूर्ण
    अन्यथा अणु
        वापस subFloat64Sigs( roundData, a, b, aSign );
    पूर्ण

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of subtracting the द्विगुन-precision भग्नing-poपूर्णांक values
`a' and `b'.  The operation is perक्रमmed according to the IEC/IEEE Standard
क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्न64 भग्न64_sub( काष्ठा roundingData *roundData, भग्न64 a, भग्न64 b )
अणु
    flag aSign, bSign;

    aSign = extractFloat64Sign( a );
    bSign = extractFloat64Sign( b );
    अगर ( aSign == bSign ) अणु
        वापस subFloat64Sigs( roundData, a, b, aSign );
    पूर्ण
    अन्यथा अणु
        वापस addFloat64Sigs( roundData, a, b, aSign );
    पूर्ण

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of multiplying the द्विगुन-precision भग्नing-poपूर्णांक values
`a' and `b'.  The operation is perक्रमmed according to the IEC/IEEE Standard
क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्न64 भग्न64_mul( काष्ठा roundingData *roundData, भग्न64 a, भग्न64 b )
अणु
    flag aSign, bSign, zSign;
    पूर्णांक16 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig0, zSig1;

    aSig = extractFloat64Frac( a );
    aExp = extractFloat64Exp( a );
    aSign = extractFloat64Sign( a );
    bSig = extractFloat64Frac( b );
    bExp = extractFloat64Exp( b );
    bSign = extractFloat64Sign( b );
    zSign = aSign ^ bSign;
    अगर ( aExp == 0x7FF ) अणु
        अगर ( aSig || ( ( bExp == 0x7FF ) && bSig ) ) अणु
            वापस propagateFloat64NaN( a, b );
        पूर्ण
        अगर ( ( bExp | bSig ) == 0 ) अणु
            roundData->exception |= भग्न_flag_invalid;
            वापस भग्न64_शेष_nan;
        पूर्ण
        वापस packFloat64( zSign, 0x7FF, 0 );
    पूर्ण
    अगर ( bExp == 0x7FF ) अणु
        अगर ( bSig ) वापस propagateFloat64NaN( a, b );
        अगर ( ( aExp | aSig ) == 0 ) अणु
            roundData->exception |= भग्न_flag_invalid;
            वापस भग्न64_शेष_nan;
        पूर्ण
        वापस packFloat64( zSign, 0x7FF, 0 );
    पूर्ण
    अगर ( aExp == 0 ) अणु
        अगर ( aSig == 0 ) वापस packFloat64( zSign, 0, 0 );
        normalizeFloat64Subnormal( aSig, &aExp, &aSig );
    पूर्ण
    अगर ( bExp == 0 ) अणु
        अगर ( bSig == 0 ) वापस packFloat64( zSign, 0, 0 );
        normalizeFloat64Subnormal( bSig, &bExp, &bSig );
    पूर्ण
    zExp = aExp + bExp - 0x3FF;
    aSig = ( aSig | LIT64( 0x0010000000000000 ) )<<10;
    bSig = ( bSig | LIT64( 0x0010000000000000 ) )<<11;
    mul64To128( aSig, bSig, &zSig0, &zSig1 );
    zSig0 |= ( zSig1 != 0 );
    अगर ( 0 <= (sbits64) ( zSig0<<1 ) ) अणु
        zSig0 <<= 1;
        --zExp;
    पूर्ण
    वापस roundAndPackFloat64( roundData, zSign, zExp, zSig0 );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of भागiding the द्विगुन-precision भग्नing-poपूर्णांक value `a'
by the corresponding value `b'.  The operation is perक्रमmed according to
the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्न64 भग्न64_भाग( काष्ठा roundingData *roundData, भग्न64 a, भग्न64 b )
अणु
    flag aSign, bSign, zSign;
    पूर्णांक16 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig;
    bits64 rem0, rem1;
    bits64 term0, term1;

    aSig = extractFloat64Frac( a );
    aExp = extractFloat64Exp( a );
    aSign = extractFloat64Sign( a );
    bSig = extractFloat64Frac( b );
    bExp = extractFloat64Exp( b );
    bSign = extractFloat64Sign( b );
    zSign = aSign ^ bSign;
    अगर ( aExp == 0x7FF ) अणु
        अगर ( aSig ) वापस propagateFloat64NaN( a, b );
        अगर ( bExp == 0x7FF ) अणु
            अगर ( bSig ) वापस propagateFloat64NaN( a, b );
            roundData->exception |= भग्न_flag_invalid;
            वापस भग्न64_शेष_nan;
        पूर्ण
        वापस packFloat64( zSign, 0x7FF, 0 );
    पूर्ण
    अगर ( bExp == 0x7FF ) अणु
        अगर ( bSig ) वापस propagateFloat64NaN( a, b );
        वापस packFloat64( zSign, 0, 0 );
    पूर्ण
    अगर ( bExp == 0 ) अणु
        अगर ( bSig == 0 ) अणु
            अगर ( ( aExp | aSig ) == 0 ) अणु
                roundData->exception |= भग्न_flag_invalid;
                वापस भग्न64_शेष_nan;
            पूर्ण
            roundData->exception |= भग्न_flag_भागbyzero;
            वापस packFloat64( zSign, 0x7FF, 0 );
        पूर्ण
        normalizeFloat64Subnormal( bSig, &bExp, &bSig );
    पूर्ण
    अगर ( aExp == 0 ) अणु
        अगर ( aSig == 0 ) वापस packFloat64( zSign, 0, 0 );
        normalizeFloat64Subnormal( aSig, &aExp, &aSig );
    पूर्ण
    zExp = aExp - bExp + 0x3FD;
    aSig = ( aSig | LIT64( 0x0010000000000000 ) )<<10;
    bSig = ( bSig | LIT64( 0x0010000000000000 ) )<<11;
    अगर ( bSig <= ( aSig + aSig ) ) अणु
        aSig >>= 1;
        ++zExp;
    पूर्ण
    zSig = estimateDiv128To64( aSig, 0, bSig );
    अगर ( ( zSig & 0x1FF ) <= 2 ) अणु
        mul64To128( bSig, zSig, &term0, &term1 );
        sub128( aSig, 0, term0, term1, &rem0, &rem1 );
        जबतक ( (sbits64) rem0 < 0 ) अणु
            --zSig;
            add128( rem0, rem1, 0, bSig, &rem0, &rem1 );
        पूर्ण
        zSig |= ( rem1 != 0 );
    पूर्ण
    वापस roundAndPackFloat64( roundData, zSign, zExp, zSig );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the reमुख्यder of the द्विगुन-precision भग्नing-poपूर्णांक value `a'
with respect to the corresponding value `b'.  The operation is perक्रमmed
according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्न64 भग्न64_rem( काष्ठा roundingData *roundData, भग्न64 a, भग्न64 b )
अणु
    flag aSign, bSign, zSign;
    पूर्णांक16 aExp, bExp, expDअगरf;
    bits64 aSig, bSig;
    bits64 q, alternateASig;
    sbits64 sigMean;

    aSig = extractFloat64Frac( a );
    aExp = extractFloat64Exp( a );
    aSign = extractFloat64Sign( a );
    bSig = extractFloat64Frac( b );
    bExp = extractFloat64Exp( b );
    bSign = extractFloat64Sign( b );
    अगर ( aExp == 0x7FF ) अणु
        अगर ( aSig || ( ( bExp == 0x7FF ) && bSig ) ) अणु
            वापस propagateFloat64NaN( a, b );
        पूर्ण
        roundData->exception |= भग्न_flag_invalid;
        वापस भग्न64_शेष_nan;
    पूर्ण
    अगर ( bExp == 0x7FF ) अणु
        अगर ( bSig ) वापस propagateFloat64NaN( a, b );
        वापस a;
    पूर्ण
    अगर ( bExp == 0 ) अणु
        अगर ( bSig == 0 ) अणु
            roundData->exception |= भग्न_flag_invalid;
            वापस भग्न64_शेष_nan;
        पूर्ण
        normalizeFloat64Subnormal( bSig, &bExp, &bSig );
    पूर्ण
    अगर ( aExp == 0 ) अणु
        अगर ( aSig == 0 ) वापस a;
        normalizeFloat64Subnormal( aSig, &aExp, &aSig );
    पूर्ण
    expDअगरf = aExp - bExp;
    aSig = ( aSig | LIT64( 0x0010000000000000 ) )<<11;
    bSig = ( bSig | LIT64( 0x0010000000000000 ) )<<11;
    अगर ( expDअगरf < 0 ) अणु
        अगर ( expDअगरf < -1 ) वापस a;
        aSig >>= 1;
    पूर्ण
    q = ( bSig <= aSig );
    अगर ( q ) aSig -= bSig;
    expDअगरf -= 64;
    जबतक ( 0 < expDअगरf ) अणु
        q = estimateDiv128To64( aSig, 0, bSig );
        q = ( 2 < q ) ? q - 2 : 0;
        aSig = - ( ( bSig>>2 ) * q );
        expDअगरf -= 62;
    पूर्ण
    expDअगरf += 64;
    अगर ( 0 < expDअगरf ) अणु
        q = estimateDiv128To64( aSig, 0, bSig );
        q = ( 2 < q ) ? q - 2 : 0;
        q >>= 64 - expDअगरf;
        bSig >>= 2;
        aSig = ( ( aSig>>1 )<<( expDअगरf - 1 ) ) - bSig * q;
    पूर्ण
    अन्यथा अणु
        aSig >>= 2;
        bSig >>= 2;
    पूर्ण
    करो अणु
        alternateASig = aSig;
        ++q;
        aSig -= bSig;
    पूर्ण जबतक ( 0 <= (sbits64) aSig );
    sigMean = aSig + alternateASig;
    अगर ( ( sigMean < 0 ) || ( ( sigMean == 0 ) && ( q & 1 ) ) ) अणु
        aSig = alternateASig;
    पूर्ण
    zSign = ( (sbits64) aSig < 0 );
    अगर ( zSign ) aSig = - aSig;
    वापस normalizeRoundAndPackFloat64( roundData, aSign ^ zSign, bExp, aSig );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the square root of the द्विगुन-precision भग्नing-poपूर्णांक value `a'.
The operation is perक्रमmed according to the IEC/IEEE Standard क्रम Binary
Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्न64 भग्न64_वर्ग_मूल( काष्ठा roundingData *roundData, भग्न64 a )
अणु
    flag aSign;
    पूर्णांक16 aExp, zExp;
    bits64 aSig, zSig;
    bits64 rem0, rem1, term0, term1; //, shअगरtedRem;
    //भग्न64 z;

    aSig = extractFloat64Frac( a );
    aExp = extractFloat64Exp( a );
    aSign = extractFloat64Sign( a );
    अगर ( aExp == 0x7FF ) अणु
        अगर ( aSig ) वापस propagateFloat64NaN( a, a );
        अगर ( ! aSign ) वापस a;
        roundData->exception |= भग्न_flag_invalid;
        वापस भग्न64_शेष_nan;
    पूर्ण
    अगर ( aSign ) अणु
        अगर ( ( aExp | aSig ) == 0 ) वापस a;
        roundData->exception |= भग्न_flag_invalid;
        वापस भग्न64_शेष_nan;
    पूर्ण
    अगर ( aExp == 0 ) अणु
        अगर ( aSig == 0 ) वापस 0;
        normalizeFloat64Subnormal( aSig, &aExp, &aSig );
    पूर्ण
    zExp = ( ( aExp - 0x3FF )>>1 ) + 0x3FE;
    aSig |= LIT64( 0x0010000000000000 );
    zSig = estimateSqrt32( aExp, aSig>>21 );
    zSig <<= 31;
    aSig <<= 9 - ( aExp & 1 );
    zSig = estimateDiv128To64( aSig, 0, zSig ) + zSig + 2;
    अगर ( ( zSig & 0x3FF ) <= 5 ) अणु
        अगर ( zSig < 2 ) अणु
            zSig = LIT64( 0xFFFFFFFFFFFFFFFF );
        पूर्ण
        अन्यथा अणु
            aSig <<= 2;
            mul64To128( zSig, zSig, &term0, &term1 );
            sub128( aSig, 0, term0, term1, &rem0, &rem1 );
            जबतक ( (sbits64) rem0 < 0 ) अणु
                --zSig;
                लघुShअगरt128Left( 0, zSig, 1, &term0, &term1 );
                term1 |= 1;
                add128( rem0, rem1, term0, term1, &rem0, &rem1 );
            पूर्ण
            zSig |= ( ( rem0 | rem1 ) != 0 );
        पूर्ण
    पूर्ण
    shअगरt64RightJamming( zSig, 1, &zSig );
    वापस roundAndPackFloat64( roundData, 0, zExp, zSig );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns 1 अगर the द्विगुन-precision भग्नing-poपूर्णांक value `a' is equal to the
corresponding value `b', and 0 otherwise.  The comparison is perक्रमmed
according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
flag भग्न64_eq( भग्न64 a, भग्न64 b )
अणु

    अगर (    ( ( extractFloat64Exp( a ) == 0x7FF ) && extractFloat64Frac( a ) )
         || ( ( extractFloat64Exp( b ) == 0x7FF ) && extractFloat64Frac( b ) )
       ) अणु
        अगर ( भग्न64_is_संकेतing_nan( a ) || भग्न64_is_संकेतing_nan( b ) ) अणु
            भग्न_उठाओ( भग्न_flag_invalid );
        पूर्ण
        वापस 0;
    पूर्ण
    वापस ( a == b ) || ( (bits64) ( ( a | b )<<1 ) == 0 );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns 1 अगर the द्विगुन-precision भग्नing-poपूर्णांक value `a' is less than or
equal to the corresponding value `b', and 0 otherwise.  The comparison is
perक्रमmed according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक
Arithmetic.
-------------------------------------------------------------------------------
*/
flag भग्न64_le( भग्न64 a, भग्न64 b )
अणु
    flag aSign, bSign;

    अगर (    ( ( extractFloat64Exp( a ) == 0x7FF ) && extractFloat64Frac( a ) )
         || ( ( extractFloat64Exp( b ) == 0x7FF ) && extractFloat64Frac( b ) )
       ) अणु
        भग्न_उठाओ( भग्न_flag_invalid );
        वापस 0;
    पूर्ण
    aSign = extractFloat64Sign( a );
    bSign = extractFloat64Sign( b );
    अगर ( aSign != bSign ) वापस aSign || ( (bits64) ( ( a | b )<<1 ) == 0 );
    वापस ( a == b ) || ( aSign ^ ( a < b ) );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns 1 अगर the द्विगुन-precision भग्नing-poपूर्णांक value `a' is less than
the corresponding value `b', and 0 otherwise.  The comparison is perक्रमmed
according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
flag भग्न64_lt( भग्न64 a, भग्न64 b )
अणु
    flag aSign, bSign;

    अगर (    ( ( extractFloat64Exp( a ) == 0x7FF ) && extractFloat64Frac( a ) )
         || ( ( extractFloat64Exp( b ) == 0x7FF ) && extractFloat64Frac( b ) )
       ) अणु
        भग्न_उठाओ( भग्न_flag_invalid );
        वापस 0;
    पूर्ण
    aSign = extractFloat64Sign( a );
    bSign = extractFloat64Sign( b );
    अगर ( aSign != bSign ) वापस aSign && ( (bits64) ( ( a | b )<<1 ) != 0 );
    वापस ( a != b ) && ( aSign ^ ( a < b ) );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns 1 अगर the द्विगुन-precision भग्नing-poपूर्णांक value `a' is equal to the
corresponding value `b', and 0 otherwise.  The invalid exception is उठाओd
अगर either opeअक्रम is a NaN.  Otherwise, the comparison is perक्रमmed
according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
flag भग्न64_eq_संकेतing( भग्न64 a, भग्न64 b )
अणु

    अगर (    ( ( extractFloat64Exp( a ) == 0x7FF ) && extractFloat64Frac( a ) )
         || ( ( extractFloat64Exp( b ) == 0x7FF ) && extractFloat64Frac( b ) )
       ) अणु
        भग्न_उठाओ( भग्न_flag_invalid );
        वापस 0;
    पूर्ण
    वापस ( a == b ) || ( (bits64) ( ( a | b )<<1 ) == 0 );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns 1 अगर the द्विगुन-precision भग्नing-poपूर्णांक value `a' is less than or
equal to the corresponding value `b', and 0 otherwise.  Quiet NaNs करो not
cause an exception.  Otherwise, the comparison is perक्रमmed according to the
IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
flag भग्न64_le_quiet( भग्न64 a, भग्न64 b )
अणु
    flag aSign, bSign;
    //पूर्णांक16 aExp, bExp;

    अगर (    ( ( extractFloat64Exp( a ) == 0x7FF ) && extractFloat64Frac( a ) )
         || ( ( extractFloat64Exp( b ) == 0x7FF ) && extractFloat64Frac( b ) )
       ) अणु
        /* Do nothing, even अगर NaN as we're quiet */
        वापस 0;
    पूर्ण
    aSign = extractFloat64Sign( a );
    bSign = extractFloat64Sign( b );
    अगर ( aSign != bSign ) वापस aSign || ( (bits64) ( ( a | b )<<1 ) == 0 );
    वापस ( a == b ) || ( aSign ^ ( a < b ) );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns 1 अगर the द्विगुन-precision भग्नing-poपूर्णांक value `a' is less than
the corresponding value `b', and 0 otherwise.  Quiet NaNs करो not cause an
exception.  Otherwise, the comparison is perक्रमmed according to the IEC/IEEE
Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
flag भग्न64_lt_quiet( भग्न64 a, भग्न64 b )
अणु
    flag aSign, bSign;

    अगर (    ( ( extractFloat64Exp( a ) == 0x7FF ) && extractFloat64Frac( a ) )
         || ( ( extractFloat64Exp( b ) == 0x7FF ) && extractFloat64Frac( b ) )
       ) अणु
        /* Do nothing, even अगर NaN as we're quiet */
        वापस 0;
    पूर्ण
    aSign = extractFloat64Sign( a );
    bSign = extractFloat64Sign( b );
    अगर ( aSign != bSign ) वापस aSign && ( (bits64) ( ( a | b )<<1 ) != 0 );
    वापस ( a != b ) && ( aSign ^ ( a < b ) );

पूर्ण

#अगर_घोषित FLOATX80

/*
-------------------------------------------------------------------------------
Returns the result of converting the extended द्विगुन-precision भग्नing-
poपूर्णांक value `a' to the 32-bit two's complement पूर्णांकeger क्रमmat.  The
conversion is perक्रमmed according to the IEC/IEEE Standard क्रम Binary
Floating-poपूर्णांक Arithmetic---which means in particular that the conversion
is rounded according to the current rounding mode.  If `a' is a NaN, the
largest positive पूर्णांकeger is वापसed.  Otherwise, अगर the conversion
overflows, the largest पूर्णांकeger with the same sign as `a' is वापसed.
-------------------------------------------------------------------------------
*/
पूर्णांक32 भग्नx80_to_पूर्णांक32( काष्ठा roundingData *roundData, भग्नx80 a )
अणु
    flag aSign;
    पूर्णांक32 aExp, shअगरtCount;
    bits64 aSig;

    aSig = extractFloatx80Frac( a );
    aExp = extractFloatx80Exp( a );
    aSign = extractFloatx80Sign( a );
    अगर ( ( aExp == 0x7FFF ) && (bits64) ( aSig<<1 ) ) aSign = 0;
    shअगरtCount = 0x4037 - aExp;
    अगर ( shअगरtCount <= 0 ) shअगरtCount = 1;
    shअगरt64RightJamming( aSig, shअगरtCount, &aSig );
    वापस roundAndPackInt32( roundData, aSign, aSig );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of converting the extended द्विगुन-precision भग्नing-
poपूर्णांक value `a' to the 32-bit two's complement पूर्णांकeger क्रमmat.  The
conversion is perक्रमmed according to the IEC/IEEE Standard क्रम Binary
Floating-poपूर्णांक Arithmetic, except that the conversion is always rounded
toward zero.  If `a' is a NaN, the largest positive पूर्णांकeger is वापसed.
Otherwise, अगर the conversion overflows, the largest पूर्णांकeger with the same
sign as `a' is वापसed.
-------------------------------------------------------------------------------
*/
पूर्णांक32 भग्नx80_to_पूर्णांक32_round_to_zero( भग्नx80 a )
अणु
    flag aSign;
    पूर्णांक32 aExp, shअगरtCount;
    bits64 aSig, savedASig;
    पूर्णांक32 z;

    aSig = extractFloatx80Frac( a );
    aExp = extractFloatx80Exp( a );
    aSign = extractFloatx80Sign( a );
    shअगरtCount = 0x403E - aExp;
    अगर ( shअगरtCount < 32 ) अणु
        अगर ( ( aExp == 0x7FFF ) && (bits64) ( aSig<<1 ) ) aSign = 0;
        जाओ invalid;
    पूर्ण
    अन्यथा अगर ( 63 < shअगरtCount ) अणु
        अगर ( aExp || aSig ) भग्न_उठाओ( भग्न_flag_inexact );
        वापस 0;
    पूर्ण
    savedASig = aSig;
    aSig >>= shअगरtCount;
    z = aSig;
    अगर ( aSign ) z = - z;
    अगर ( ( z < 0 ) ^ aSign ) अणु
 invalid:
        भग्न_उठाओ( भग्न_flag_invalid );
        वापस aSign ? 0x80000000 : 0x7FFFFFFF;
    पूर्ण
    अगर ( ( aSig<<shअगरtCount ) != savedASig ) अणु
        भग्न_उठाओ( भग्न_flag_inexact );
    पूर्ण
    वापस z;

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of converting the extended द्विगुन-precision भग्नing-
poपूर्णांक value `a' to the single-precision भग्नing-poपूर्णांक क्रमmat.  The
conversion is perक्रमmed according to the IEC/IEEE Standard क्रम Binary
Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्न32 भग्नx80_to_भग्न32( काष्ठा roundingData *roundData, भग्नx80 a )
अणु
    flag aSign;
    पूर्णांक32 aExp;
    bits64 aSig;

    aSig = extractFloatx80Frac( a );
    aExp = extractFloatx80Exp( a );
    aSign = extractFloatx80Sign( a );
    अगर ( aExp == 0x7FFF ) अणु
        अगर ( (bits64) ( aSig<<1 ) ) अणु
            वापस commonNaNToFloat32( भग्नx80ToCommonNaN( a ) );
        पूर्ण
        वापस packFloat32( aSign, 0xFF, 0 );
    पूर्ण
    shअगरt64RightJamming( aSig, 33, &aSig );
    अगर ( aExp || aSig ) aExp -= 0x3F81;
    वापस roundAndPackFloat32( roundData, aSign, aExp, aSig );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of converting the extended द्विगुन-precision भग्नing-
poपूर्णांक value `a' to the द्विगुन-precision भग्नing-poपूर्णांक क्रमmat.  The
conversion is perक्रमmed according to the IEC/IEEE Standard क्रम Binary
Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्न64 भग्नx80_to_भग्न64( काष्ठा roundingData *roundData, भग्नx80 a )
अणु
    flag aSign;
    पूर्णांक32 aExp;
    bits64 aSig, zSig;

    aSig = extractFloatx80Frac( a );
    aExp = extractFloatx80Exp( a );
    aSign = extractFloatx80Sign( a );
    अगर ( aExp == 0x7FFF ) अणु
        अगर ( (bits64) ( aSig<<1 ) ) अणु
            वापस commonNaNToFloat64( भग्नx80ToCommonNaN( a ) );
        पूर्ण
        वापस packFloat64( aSign, 0x7FF, 0 );
    पूर्ण
    shअगरt64RightJamming( aSig, 1, &zSig );
    अगर ( aExp || aSig ) aExp -= 0x3C01;
    वापस roundAndPackFloat64( roundData, aSign, aExp, zSig );

पूर्ण

/*
-------------------------------------------------------------------------------
Rounds the extended द्विगुन-precision भग्नing-poपूर्णांक value `a' to an पूर्णांकeger,
and वापसs the result as an extended quadruple-precision भग्नing-poपूर्णांक
value.  The operation is perक्रमmed according to the IEC/IEEE Standard क्रम
Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्नx80 भग्नx80_round_to_पूर्णांक( काष्ठा roundingData *roundData, भग्नx80 a )
अणु
    flag aSign;
    पूर्णांक32 aExp;
    bits64 lastBitMask, roundBitsMask;
    पूर्णांक8 roundingMode;
    भग्नx80 z;

    aExp = extractFloatx80Exp( a );
    अगर ( 0x403E <= aExp ) अणु
        अगर ( ( aExp == 0x7FFF ) && (bits64) ( extractFloatx80Frac( a )<<1 ) ) अणु
            वापस propagateFloatx80NaN( a, a );
        पूर्ण
        वापस a;
    पूर्ण
    अगर ( aExp <= 0x3FFE ) अणु
        अगर (    ( aExp == 0 )
             && ( (bits64) ( extractFloatx80Frac( a )<<1 ) == 0 ) ) अणु
            वापस a;
        पूर्ण
        roundData->exception |= भग्न_flag_inexact;
        aSign = extractFloatx80Sign( a );
        चयन ( roundData->mode ) अणु
         हाल भग्न_round_nearest_even:
            अगर ( ( aExp == 0x3FFE ) && (bits64) ( extractFloatx80Frac( a )<<1 )
               ) अणु
                वापस
                    packFloatx80( aSign, 0x3FFF, LIT64( 0x8000000000000000 ) );
            पूर्ण
            अवरोध;
         हाल भग्न_round_करोwn:
            वापस
                  aSign ?
                      packFloatx80( 1, 0x3FFF, LIT64( 0x8000000000000000 ) )
                : packFloatx80( 0, 0, 0 );
         हाल भग्न_round_up:
            वापस
                  aSign ? packFloatx80( 1, 0, 0 )
                : packFloatx80( 0, 0x3FFF, LIT64( 0x8000000000000000 ) );
        पूर्ण
        वापस packFloatx80( aSign, 0, 0 );
    पूर्ण
    lastBitMask = 1;
    lastBitMask <<= 0x403E - aExp;
    roundBitsMask = lastBitMask - 1;
    z = a;
    roundingMode = roundData->mode;
    अगर ( roundingMode == भग्न_round_nearest_even ) अणु
        z.low += lastBitMask>>1;
        अगर ( ( z.low & roundBitsMask ) == 0 ) z.low &= ~ lastBitMask;
    पूर्ण
    अन्यथा अगर ( roundingMode != भग्न_round_to_zero ) अणु
        अगर ( extractFloatx80Sign( z ) ^ ( roundingMode == भग्न_round_up ) ) अणु
            z.low += roundBitsMask;
        पूर्ण
    पूर्ण
    z.low &= ~ roundBitsMask;
    अगर ( z.low == 0 ) अणु
        ++z.high;
        z.low = LIT64( 0x8000000000000000 );
    पूर्ण
    अगर ( z.low != a.low ) roundData->exception |= भग्न_flag_inexact;
    वापस z;

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of adding the असलolute values of the extended द्विगुन-
precision भग्नing-poपूर्णांक values `a' and `b'.  If `zSign' is true, the sum is
negated beक्रमe being वापसed.  `zSign' is ignored अगर the result is a NaN.
The addition is perक्रमmed according to the IEC/IEEE Standard क्रम Binary
Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
अटल भग्नx80 addFloatx80Sigs( काष्ठा roundingData *roundData, भग्नx80 a, भग्नx80 b, flag zSign )
अणु
    पूर्णांक32 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig0, zSig1;
    पूर्णांक32 expDअगरf;

    aSig = extractFloatx80Frac( a );
    aExp = extractFloatx80Exp( a );
    bSig = extractFloatx80Frac( b );
    bExp = extractFloatx80Exp( b );
    expDअगरf = aExp - bExp;
    अगर ( 0 < expDअगरf ) अणु
        अगर ( aExp == 0x7FFF ) अणु
            अगर ( (bits64) ( aSig<<1 ) ) वापस propagateFloatx80NaN( a, b );
            वापस a;
        पूर्ण
        अगर ( bExp == 0 ) --expDअगरf;
        shअगरt64ExtraRightJamming( bSig, 0, expDअगरf, &bSig, &zSig1 );
        zExp = aExp;
    पूर्ण
    अन्यथा अगर ( expDअगरf < 0 ) अणु
        अगर ( bExp == 0x7FFF ) अणु
            अगर ( (bits64) ( bSig<<1 ) ) वापस propagateFloatx80NaN( a, b );
            वापस packFloatx80( zSign, 0x7FFF, LIT64( 0x8000000000000000 ) );
        पूर्ण
        अगर ( aExp == 0 ) ++expDअगरf;
        shअगरt64ExtraRightJamming( aSig, 0, - expDअगरf, &aSig, &zSig1 );
        zExp = bExp;
    पूर्ण
    अन्यथा अणु
        अगर ( aExp == 0x7FFF ) अणु
            अगर ( (bits64) ( ( aSig | bSig )<<1 ) ) अणु
                वापस propagateFloatx80NaN( a, b );
            पूर्ण
            वापस a;
        पूर्ण
        zSig1 = 0;
        zSig0 = aSig + bSig;
        अगर ( aExp == 0 ) अणु
            normalizeFloatx80Subnormal( zSig0, &zExp, &zSig0 );
            जाओ roundAndPack;
        पूर्ण
        zExp = aExp;
        जाओ shअगरtRight1;
    पूर्ण
    
    zSig0 = aSig + bSig;

    अगर ( (sbits64) zSig0 < 0 ) जाओ roundAndPack; 
 shअगरtRight1:
    shअगरt64ExtraRightJamming( zSig0, zSig1, 1, &zSig0, &zSig1 );
    zSig0 |= LIT64( 0x8000000000000000 );
    ++zExp;
 roundAndPack:
    वापस
        roundAndPackFloatx80(
            roundData, zSign, zExp, zSig0, zSig1 );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of subtracting the असलolute values of the extended
द्विगुन-precision भग्नing-poपूर्णांक values `a' and `b'.  If `zSign' is true,
the dअगरference is negated beक्रमe being वापसed.  `zSign' is ignored अगर the
result is a NaN.  The subtraction is perक्रमmed according to the IEC/IEEE
Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
अटल भग्नx80 subFloatx80Sigs( काष्ठा roundingData *roundData, भग्नx80 a, भग्नx80 b, flag zSign )
अणु
    पूर्णांक32 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig0, zSig1;
    पूर्णांक32 expDअगरf;
    भग्नx80 z;

    aSig = extractFloatx80Frac( a );
    aExp = extractFloatx80Exp( a );
    bSig = extractFloatx80Frac( b );
    bExp = extractFloatx80Exp( b );
    expDअगरf = aExp - bExp;
    अगर ( 0 < expDअगरf ) जाओ aExpBigger;
    अगर ( expDअगरf < 0 ) जाओ bExpBigger;
    अगर ( aExp == 0x7FFF ) अणु
        अगर ( (bits64) ( ( aSig | bSig )<<1 ) ) अणु
            वापस propagateFloatx80NaN( a, b );
        पूर्ण
        roundData->exception |= भग्न_flag_invalid;
        z.low = भग्नx80_शेष_nan_low;
        z.high = भग्नx80_शेष_nan_high;
        z.__padding = 0;
        वापस z;
    पूर्ण
    अगर ( aExp == 0 ) अणु
        aExp = 1;
        bExp = 1;
    पूर्ण
    zSig1 = 0;
    अगर ( bSig < aSig ) जाओ aBigger;
    अगर ( aSig < bSig ) जाओ bBigger;
    वापस packFloatx80( roundData->mode == भग्न_round_करोwn, 0, 0 );
 bExpBigger:
    अगर ( bExp == 0x7FFF ) अणु
        अगर ( (bits64) ( bSig<<1 ) ) वापस propagateFloatx80NaN( a, b );
        वापस packFloatx80( zSign ^ 1, 0x7FFF, LIT64( 0x8000000000000000 ) );
    पूर्ण
    अगर ( aExp == 0 ) ++expDअगरf;
    shअगरt128RightJamming( aSig, 0, - expDअगरf, &aSig, &zSig1 );
 bBigger:
    sub128( bSig, 0, aSig, zSig1, &zSig0, &zSig1 );
    zExp = bExp;
    zSign ^= 1;
    जाओ normalizeRoundAndPack;
 aExpBigger:
    अगर ( aExp == 0x7FFF ) अणु
        अगर ( (bits64) ( aSig<<1 ) ) वापस propagateFloatx80NaN( a, b );
        वापस a;
    पूर्ण
    अगर ( bExp == 0 ) --expDअगरf;
    shअगरt128RightJamming( bSig, 0, expDअगरf, &bSig, &zSig1 );
 aBigger:
    sub128( aSig, 0, bSig, zSig1, &zSig0, &zSig1 );
    zExp = aExp;
 normalizeRoundAndPack:
    वापस
        normalizeRoundAndPackFloatx80(
            roundData, zSign, zExp, zSig0, zSig1 );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of adding the extended द्विगुन-precision भग्नing-poपूर्णांक
values `a' and `b'.  The operation is perक्रमmed according to the IEC/IEEE
Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्नx80 भग्नx80_add( काष्ठा roundingData *roundData, भग्नx80 a, भग्नx80 b )
अणु
    flag aSign, bSign;
    
    aSign = extractFloatx80Sign( a );
    bSign = extractFloatx80Sign( b );
    अगर ( aSign == bSign ) अणु
        वापस addFloatx80Sigs( roundData, a, b, aSign );
    पूर्ण
    अन्यथा अणु
        वापस subFloatx80Sigs( roundData, a, b, aSign );
    पूर्ण
    
पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of subtracting the extended द्विगुन-precision भग्नing-
poपूर्णांक values `a' and `b'.  The operation is perक्रमmed according to the
IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्नx80 भग्नx80_sub( काष्ठा roundingData *roundData, भग्नx80 a, भग्नx80 b )
अणु
    flag aSign, bSign;

    aSign = extractFloatx80Sign( a );
    bSign = extractFloatx80Sign( b );
    अगर ( aSign == bSign ) अणु
        वापस subFloatx80Sigs( roundData, a, b, aSign );
    पूर्ण
    अन्यथा अणु
        वापस addFloatx80Sigs( roundData, a, b, aSign );
    पूर्ण

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of multiplying the extended द्विगुन-precision भग्नing-
poपूर्णांक values `a' and `b'.  The operation is perक्रमmed according to the
IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्नx80 भग्नx80_mul( काष्ठा roundingData *roundData, भग्नx80 a, भग्नx80 b )
अणु
    flag aSign, bSign, zSign;
    पूर्णांक32 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig0, zSig1;
    भग्नx80 z;

    aSig = extractFloatx80Frac( a );
    aExp = extractFloatx80Exp( a );
    aSign = extractFloatx80Sign( a );
    bSig = extractFloatx80Frac( b );
    bExp = extractFloatx80Exp( b );
    bSign = extractFloatx80Sign( b );
    zSign = aSign ^ bSign;
    अगर ( aExp == 0x7FFF ) अणु
        अगर (    (bits64) ( aSig<<1 )
             || ( ( bExp == 0x7FFF ) && (bits64) ( bSig<<1 ) ) ) अणु
            वापस propagateFloatx80NaN( a, b );
        पूर्ण
        अगर ( ( bExp | bSig ) == 0 ) जाओ invalid;
        वापस packFloatx80( zSign, 0x7FFF, LIT64( 0x8000000000000000 ) );
    पूर्ण
    अगर ( bExp == 0x7FFF ) अणु
        अगर ( (bits64) ( bSig<<1 ) ) वापस propagateFloatx80NaN( a, b );
        अगर ( ( aExp | aSig ) == 0 ) अणु
 invalid:
            roundData->exception |= भग्न_flag_invalid;
            z.low = भग्नx80_शेष_nan_low;
            z.high = भग्नx80_शेष_nan_high;
            z.__padding = 0;
            वापस z;
        पूर्ण
        वापस packFloatx80( zSign, 0x7FFF, LIT64( 0x8000000000000000 ) );
    पूर्ण
    अगर ( aExp == 0 ) अणु
        अगर ( aSig == 0 ) वापस packFloatx80( zSign, 0, 0 );
        normalizeFloatx80Subnormal( aSig, &aExp, &aSig );
    पूर्ण
    अगर ( bExp == 0 ) अणु
        अगर ( bSig == 0 ) वापस packFloatx80( zSign, 0, 0 );
        normalizeFloatx80Subnormal( bSig, &bExp, &bSig );
    पूर्ण
    zExp = aExp + bExp - 0x3FFE;
    mul64To128( aSig, bSig, &zSig0, &zSig1 );
    अगर ( 0 < (sbits64) zSig0 ) अणु
        लघुShअगरt128Left( zSig0, zSig1, 1, &zSig0, &zSig1 );
        --zExp;
    पूर्ण
    वापस
        roundAndPackFloatx80(
            roundData, zSign, zExp, zSig0, zSig1 );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the result of भागiding the extended द्विगुन-precision भग्नing-poपूर्णांक
value `a' by the corresponding value `b'.  The operation is perक्रमmed
according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्नx80 भग्नx80_भाग( काष्ठा roundingData *roundData, भग्नx80 a, भग्नx80 b )
अणु
    flag aSign, bSign, zSign;
    पूर्णांक32 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig0, zSig1;
    bits64 rem0, rem1, rem2, term0, term1, term2;
    भग्नx80 z;

    aSig = extractFloatx80Frac( a );
    aExp = extractFloatx80Exp( a );
    aSign = extractFloatx80Sign( a );
    bSig = extractFloatx80Frac( b );
    bExp = extractFloatx80Exp( b );
    bSign = extractFloatx80Sign( b );
    zSign = aSign ^ bSign;
    अगर ( aExp == 0x7FFF ) अणु
        अगर ( (bits64) ( aSig<<1 ) ) वापस propagateFloatx80NaN( a, b );
        अगर ( bExp == 0x7FFF ) अणु
            अगर ( (bits64) ( bSig<<1 ) ) वापस propagateFloatx80NaN( a, b );
            जाओ invalid;
        पूर्ण
        वापस packFloatx80( zSign, 0x7FFF, LIT64( 0x8000000000000000 ) );
    पूर्ण
    अगर ( bExp == 0x7FFF ) अणु
        अगर ( (bits64) ( bSig<<1 ) ) वापस propagateFloatx80NaN( a, b );
        वापस packFloatx80( zSign, 0, 0 );
    पूर्ण
    अगर ( bExp == 0 ) अणु
        अगर ( bSig == 0 ) अणु
            अगर ( ( aExp | aSig ) == 0 ) अणु
 invalid:
                roundData->exception |= भग्न_flag_invalid;
                z.low = भग्नx80_शेष_nan_low;
                z.high = भग्नx80_शेष_nan_high;
                z.__padding = 0;
                वापस z;
            पूर्ण
            roundData->exception |= भग्न_flag_भागbyzero;
            वापस packFloatx80( zSign, 0x7FFF, LIT64( 0x8000000000000000 ) );
        पूर्ण
        normalizeFloatx80Subnormal( bSig, &bExp, &bSig );
    पूर्ण
    अगर ( aExp == 0 ) अणु
        अगर ( aSig == 0 ) वापस packFloatx80( zSign, 0, 0 );
        normalizeFloatx80Subnormal( aSig, &aExp, &aSig );
    पूर्ण
    zExp = aExp - bExp + 0x3FFE;
    rem1 = 0;
    अगर ( bSig <= aSig ) अणु
        shअगरt128Right( aSig, 0, 1, &aSig, &rem1 );
        ++zExp;
    पूर्ण
    zSig0 = estimateDiv128To64( aSig, rem1, bSig );
    mul64To128( bSig, zSig0, &term0, &term1 );
    sub128( aSig, rem1, term0, term1, &rem0, &rem1 );
    जबतक ( (sbits64) rem0 < 0 ) अणु
        --zSig0;
        add128( rem0, rem1, 0, bSig, &rem0, &rem1 );
    पूर्ण
    zSig1 = estimateDiv128To64( rem1, 0, bSig );
    अगर ( (bits64) ( zSig1<<1 ) <= 8 ) अणु
        mul64To128( bSig, zSig1, &term1, &term2 );
        sub128( rem1, 0, term1, term2, &rem1, &rem2 );
        जबतक ( (sbits64) rem1 < 0 ) अणु
            --zSig1;
            add128( rem1, rem2, 0, bSig, &rem1, &rem2 );
        पूर्ण
        zSig1 |= ( ( rem1 | rem2 ) != 0 );
    पूर्ण
    वापस
        roundAndPackFloatx80(
            roundData, zSign, zExp, zSig0, zSig1 );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the reमुख्यder of the extended द्विगुन-precision भग्नing-poपूर्णांक value
`a' with respect to the corresponding value `b'.  The operation is perक्रमmed
according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्नx80 भग्नx80_rem( काष्ठा roundingData *roundData, भग्नx80 a, भग्नx80 b )
अणु
    flag aSign, bSign, zSign;
    पूर्णांक32 aExp, bExp, expDअगरf;
    bits64 aSig0, aSig1, bSig;
    bits64 q, term0, term1, alternateASig0, alternateASig1;
    भग्नx80 z;

    aSig0 = extractFloatx80Frac( a );
    aExp = extractFloatx80Exp( a );
    aSign = extractFloatx80Sign( a );
    bSig = extractFloatx80Frac( b );
    bExp = extractFloatx80Exp( b );
    bSign = extractFloatx80Sign( b );
    अगर ( aExp == 0x7FFF ) अणु
        अगर (    (bits64) ( aSig0<<1 )
             || ( ( bExp == 0x7FFF ) && (bits64) ( bSig<<1 ) ) ) अणु
            वापस propagateFloatx80NaN( a, b );
        पूर्ण
        जाओ invalid;
    पूर्ण
    अगर ( bExp == 0x7FFF ) अणु
        अगर ( (bits64) ( bSig<<1 ) ) वापस propagateFloatx80NaN( a, b );
        वापस a;
    पूर्ण
    अगर ( bExp == 0 ) अणु
        अगर ( bSig == 0 ) अणु
 invalid:
            roundData->exception |= भग्न_flag_invalid;
            z.low = भग्नx80_शेष_nan_low;
            z.high = भग्नx80_शेष_nan_high;
            z.__padding = 0;
            वापस z;
        पूर्ण
        normalizeFloatx80Subnormal( bSig, &bExp, &bSig );
    पूर्ण
    अगर ( aExp == 0 ) अणु
        अगर ( (bits64) ( aSig0<<1 ) == 0 ) वापस a;
        normalizeFloatx80Subnormal( aSig0, &aExp, &aSig0 );
    पूर्ण
    bSig |= LIT64( 0x8000000000000000 );
    zSign = aSign;
    expDअगरf = aExp - bExp;
    aSig1 = 0;
    अगर ( expDअगरf < 0 ) अणु
        अगर ( expDअगरf < -1 ) वापस a;
        shअगरt128Right( aSig0, 0, 1, &aSig0, &aSig1 );
        expDअगरf = 0;
    पूर्ण
    q = ( bSig <= aSig0 );
    अगर ( q ) aSig0 -= bSig;
    expDअगरf -= 64;
    जबतक ( 0 < expDअगरf ) अणु
        q = estimateDiv128To64( aSig0, aSig1, bSig );
        q = ( 2 < q ) ? q - 2 : 0;
        mul64To128( bSig, q, &term0, &term1 );
        sub128( aSig0, aSig1, term0, term1, &aSig0, &aSig1 );
        लघुShअगरt128Left( aSig0, aSig1, 62, &aSig0, &aSig1 );
        expDअगरf -= 62;
    पूर्ण
    expDअगरf += 64;
    अगर ( 0 < expDअगरf ) अणु
        q = estimateDiv128To64( aSig0, aSig1, bSig );
        q = ( 2 < q ) ? q - 2 : 0;
        q >>= 64 - expDअगरf;
        mul64To128( bSig, q<<( 64 - expDअगरf ), &term0, &term1 );
        sub128( aSig0, aSig1, term0, term1, &aSig0, &aSig1 );
        लघुShअगरt128Left( 0, bSig, 64 - expDअगरf, &term0, &term1 );
        जबतक ( le128( term0, term1, aSig0, aSig1 ) ) अणु
            ++q;
            sub128( aSig0, aSig1, term0, term1, &aSig0, &aSig1 );
        पूर्ण
    पूर्ण
    अन्यथा अणु
        term1 = 0;
        term0 = bSig;
    पूर्ण
    sub128( term0, term1, aSig0, aSig1, &alternateASig0, &alternateASig1 );
    अगर (    lt128( alternateASig0, alternateASig1, aSig0, aSig1 )
         || (    eq128( alternateASig0, alternateASig1, aSig0, aSig1 )
              && ( q & 1 ) )
       ) अणु
        aSig0 = alternateASig0;
        aSig1 = alternateASig1;
        zSign = ! zSign;
    पूर्ण

    वापस
        normalizeRoundAndPackFloatx80(
            roundData, zSign, bExp + expDअगरf, aSig0, aSig1 );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns the square root of the extended द्विगुन-precision भग्नing-poपूर्णांक
value `a'.  The operation is perक्रमmed according to the IEC/IEEE Standard
क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
भग्नx80 भग्नx80_वर्ग_मूल( काष्ठा roundingData *roundData, भग्नx80 a )
अणु
    flag aSign;
    पूर्णांक32 aExp, zExp;
    bits64 aSig0, aSig1, zSig0, zSig1;
    bits64 rem0, rem1, rem2, rem3, term0, term1, term2, term3;
    bits64 shअगरtedRem0, shअगरtedRem1;
    भग्नx80 z;

    aSig0 = extractFloatx80Frac( a );
    aExp = extractFloatx80Exp( a );
    aSign = extractFloatx80Sign( a );
    अगर ( aExp == 0x7FFF ) अणु
        अगर ( (bits64) ( aSig0<<1 ) ) वापस propagateFloatx80NaN( a, a );
        अगर ( ! aSign ) वापस a;
        जाओ invalid;
    पूर्ण
    अगर ( aSign ) अणु
        अगर ( ( aExp | aSig0 ) == 0 ) वापस a;
 invalid:
        roundData->exception |= भग्न_flag_invalid;
        z.low = भग्नx80_शेष_nan_low;
        z.high = भग्नx80_शेष_nan_high;
        z.__padding = 0;
        वापस z;
    पूर्ण
    अगर ( aExp == 0 ) अणु
        अगर ( aSig0 == 0 ) वापस packFloatx80( 0, 0, 0 );
        normalizeFloatx80Subnormal( aSig0, &aExp, &aSig0 );
    पूर्ण
    zExp = ( ( aExp - 0x3FFF )>>1 ) + 0x3FFF;
    zSig0 = estimateSqrt32( aExp, aSig0>>32 );
    zSig0 <<= 31;
    aSig1 = 0;
    shअगरt128Right( aSig0, 0, ( aExp & 1 ) + 2, &aSig0, &aSig1 );
    zSig0 = estimateDiv128To64( aSig0, aSig1, zSig0 ) + zSig0 + 4;
    अगर ( 0 <= (sbits64) zSig0 ) zSig0 = LIT64( 0xFFFFFFFFFFFFFFFF );
    लघुShअगरt128Left( aSig0, aSig1, 2, &aSig0, &aSig1 );
    mul64To128( zSig0, zSig0, &term0, &term1 );
    sub128( aSig0, aSig1, term0, term1, &rem0, &rem1 );
    जबतक ( (sbits64) rem0 < 0 ) अणु
        --zSig0;
        लघुShअगरt128Left( 0, zSig0, 1, &term0, &term1 );
        term1 |= 1;
        add128( rem0, rem1, term0, term1, &rem0, &rem1 );
    पूर्ण
    लघुShअगरt128Left( rem0, rem1, 63, &shअगरtedRem0, &shअगरtedRem1 );
    zSig1 = estimateDiv128To64( shअगरtedRem0, shअगरtedRem1, zSig0 );
    अगर ( (bits64) ( zSig1<<1 ) <= 10 ) अणु
        अगर ( zSig1 == 0 ) zSig1 = 1;
        mul64To128( zSig0, zSig1, &term1, &term2 );
        लघुShअगरt128Left( term1, term2, 1, &term1, &term2 );
        sub128( rem1, 0, term1, term2, &rem1, &rem2 );
        mul64To128( zSig1, zSig1, &term2, &term3 );
        sub192( rem1, rem2, 0, 0, term2, term3, &rem1, &rem2, &rem3 );
        जबतक ( (sbits64) rem1 < 0 ) अणु
            --zSig1;
            लघुShअगरt192Left( 0, zSig0, zSig1, 1, &term1, &term2, &term3 );
            term3 |= 1;
            add192(
                rem1, rem2, rem3, term1, term2, term3, &rem1, &rem2, &rem3 );
        पूर्ण
        zSig1 |= ( ( rem1 | rem2 | rem3 ) != 0 );
    पूर्ण
    वापस
        roundAndPackFloatx80(
            roundData, 0, zExp, zSig0, zSig1 );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns 1 अगर the extended द्विगुन-precision भग्नing-poपूर्णांक value `a' is
equal to the corresponding value `b', and 0 otherwise.  The comparison is
perक्रमmed according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक
Arithmetic.
-------------------------------------------------------------------------------
*/
flag भग्नx80_eq( भग्नx80 a, भग्नx80 b )
अणु

    अगर (    (    ( extractFloatx80Exp( a ) == 0x7FFF )
              && (bits64) ( extractFloatx80Frac( a )<<1 ) )
         || (    ( extractFloatx80Exp( b ) == 0x7FFF )
              && (bits64) ( extractFloatx80Frac( b )<<1 ) )
       ) अणु
        अगर (    भग्नx80_is_संकेतing_nan( a )
             || भग्नx80_is_संकेतing_nan( b ) ) अणु
            भग्न_उठाओ( भग्न_flag_invalid );
        पूर्ण
        वापस 0;
    पूर्ण
    वापस
           ( a.low == b.low )
        && (    ( a.high == b.high )
             || (    ( a.low == 0 )
                  && ( (bits16) ( ( a.high | b.high )<<1 ) == 0 ) )
           );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns 1 अगर the extended द्विगुन-precision भग्नing-poपूर्णांक value `a' is
less than or equal to the corresponding value `b', and 0 otherwise.  The
comparison is perक्रमmed according to the IEC/IEEE Standard क्रम Binary
Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
flag भग्नx80_le( भग्नx80 a, भग्नx80 b )
अणु
    flag aSign, bSign;

    अगर (    (    ( extractFloatx80Exp( a ) == 0x7FFF )
              && (bits64) ( extractFloatx80Frac( a )<<1 ) )
         || (    ( extractFloatx80Exp( b ) == 0x7FFF )
              && (bits64) ( extractFloatx80Frac( b )<<1 ) )
       ) अणु
        भग्न_उठाओ( भग्न_flag_invalid );
        वापस 0;
    पूर्ण
    aSign = extractFloatx80Sign( a );
    bSign = extractFloatx80Sign( b );
    अगर ( aSign != bSign ) अणु
        वापस
               aSign
            || (    ( ( (bits16) ( ( a.high | b.high )<<1 ) ) | a.low | b.low )
                 == 0 );
    पूर्ण
    वापस
          aSign ? le128( b.high, b.low, a.high, a.low )
        : le128( a.high, a.low, b.high, b.low );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns 1 अगर the extended द्विगुन-precision भग्नing-poपूर्णांक value `a' is
less than the corresponding value `b', and 0 otherwise.  The comparison
is perक्रमmed according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक
Arithmetic.
-------------------------------------------------------------------------------
*/
flag भग्नx80_lt( भग्नx80 a, भग्नx80 b )
अणु
    flag aSign, bSign;

    अगर (    (    ( extractFloatx80Exp( a ) == 0x7FFF )
              && (bits64) ( extractFloatx80Frac( a )<<1 ) )
         || (    ( extractFloatx80Exp( b ) == 0x7FFF )
              && (bits64) ( extractFloatx80Frac( b )<<1 ) )
       ) अणु
        भग्न_उठाओ( भग्न_flag_invalid );
        वापस 0;
    पूर्ण
    aSign = extractFloatx80Sign( a );
    bSign = extractFloatx80Sign( b );
    अगर ( aSign != bSign ) अणु
        वापस
               aSign
            && (    ( ( (bits16) ( ( a.high | b.high )<<1 ) ) | a.low | b.low )
                 != 0 );
    पूर्ण
    वापस
          aSign ? lt128( b.high, b.low, a.high, a.low )
        : lt128( a.high, a.low, b.high, b.low );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns 1 अगर the extended द्विगुन-precision भग्नing-poपूर्णांक value `a' is equal
to the corresponding value `b', and 0 otherwise.  The invalid exception is
उठाओd अगर either opeअक्रम is a NaN.  Otherwise, the comparison is perक्रमmed
according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
flag भग्नx80_eq_संकेतing( भग्नx80 a, भग्नx80 b )
अणु

    अगर (    (    ( extractFloatx80Exp( a ) == 0x7FFF )
              && (bits64) ( extractFloatx80Frac( a )<<1 ) )
         || (    ( extractFloatx80Exp( b ) == 0x7FFF )
              && (bits64) ( extractFloatx80Frac( b )<<1 ) )
       ) अणु
        भग्न_उठाओ( भग्न_flag_invalid );
        वापस 0;
    पूर्ण
    वापस
           ( a.low == b.low )
        && (    ( a.high == b.high )
             || (    ( a.low == 0 )
                  && ( (bits16) ( ( a.high | b.high )<<1 ) == 0 ) )
           );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns 1 अगर the extended द्विगुन-precision भग्नing-poपूर्णांक value `a' is less
than or equal to the corresponding value `b', and 0 otherwise.  Quiet NaNs
करो not cause an exception.  Otherwise, the comparison is perक्रमmed according
to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
flag भग्नx80_le_quiet( भग्नx80 a, भग्नx80 b )
अणु
    flag aSign, bSign;

    अगर (    (    ( extractFloatx80Exp( a ) == 0x7FFF )
              && (bits64) ( extractFloatx80Frac( a )<<1 ) )
         || (    ( extractFloatx80Exp( b ) == 0x7FFF )
              && (bits64) ( extractFloatx80Frac( b )<<1 ) )
       ) अणु
        /* Do nothing, even अगर NaN as we're quiet */
        वापस 0;
    पूर्ण
    aSign = extractFloatx80Sign( a );
    bSign = extractFloatx80Sign( b );
    अगर ( aSign != bSign ) अणु
        वापस
               aSign
            || (    ( ( (bits16) ( ( a.high | b.high )<<1 ) ) | a.low | b.low )
                 == 0 );
    पूर्ण
    वापस
          aSign ? le128( b.high, b.low, a.high, a.low )
        : le128( a.high, a.low, b.high, b.low );

पूर्ण

/*
-------------------------------------------------------------------------------
Returns 1 अगर the extended द्विगुन-precision भग्नing-poपूर्णांक value `a' is less
than the corresponding value `b', and 0 otherwise.  Quiet NaNs करो not cause
an exception.  Otherwise, the comparison is perक्रमmed according to the
IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक Arithmetic.
-------------------------------------------------------------------------------
*/
flag भग्नx80_lt_quiet( भग्नx80 a, भग्नx80 b )
अणु
    flag aSign, bSign;

    अगर (    (    ( extractFloatx80Exp( a ) == 0x7FFF )
              && (bits64) ( extractFloatx80Frac( a )<<1 ) )
         || (    ( extractFloatx80Exp( b ) == 0x7FFF )
              && (bits64) ( extractFloatx80Frac( b )<<1 ) )
       ) अणु
        /* Do nothing, even अगर NaN as we're quiet */
        वापस 0;
    पूर्ण
    aSign = extractFloatx80Sign( a );
    bSign = extractFloatx80Sign( b );
    अगर ( aSign != bSign ) अणु
        वापस
               aSign
            && (    ( ( (bits16) ( ( a.high | b.high )<<1 ) ) | a.low | b.low )
                 != 0 );
    पूर्ण
    वापस
          aSign ? lt128( b.high, b.low, a.high, a.low )
        : lt128( a.high, a.low, b.high, b.low );

पूर्ण

#पूर्ण_अगर

