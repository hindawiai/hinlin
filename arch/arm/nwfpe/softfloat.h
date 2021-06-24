<शैली गुरु>

/*
===============================================================================

This C header file is part of the SoftFloat IEC/IEEE Floating-poपूर्णांक
Arithmetic Package, Release 2.

Written by John R. Hauser.  This work was made possible in part by the
International Computer Science Institute, located at Suite 600, 1947 Center
Street, Berkeley, Calअगरornia 94704.  Funding was partially provided by the
National Science Foundation under grant MIP-9311980.  The original version
of this code was written as part of a project to build a fixed-poपूर्णांक vector
processor in collaboration with the University of Calअगरornia at Berkeley,
overseen by Profs. Nelson Morgan and John Wawrzynek.  More inक्रमmation
is available through the Web page
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

#अगर_अघोषित __SOFTFLOAT_H__
#घोषणा __SOFTFLOAT_H__


/*
-------------------------------------------------------------------------------
The macro `FLOATX80' must be defined to enable the extended द्विगुन-precision
भग्नing-poपूर्णांक क्रमmat `भग्नx80'.  If this macro is not defined, the
`भग्नx80' type will not be defined, and none of the functions that either
input or output the `भग्नx80' type will be defined.
-------------------------------------------------------------------------------
*/
#अगर_घोषित CONFIG_FPE_NWFPE_XP
#घोषणा FLOATX80
#पूर्ण_अगर

/*
-------------------------------------------------------------------------------
Software IEC/IEEE भग्नing-poपूर्णांक types.
-------------------------------------------------------------------------------
*/
प्रकार u32 भग्न32;
प्रकार u64 भग्न64;
प्रकार काष्ठा अणु
#अगर_घोषित __ARMEB__
    u16 __padding;
    u16 high;
#अन्यथा
    u16 high;
    u16 __padding;
#पूर्ण_अगर
    u64 low;
पूर्ण  __attribute__ ((packed,aligned(4))) भग्नx80;

/*
-------------------------------------------------------------------------------
Software IEC/IEEE भग्नing-poपूर्णांक underflow tininess-detection mode.
-------------------------------------------------------------------------------
*/
बाह्य चिन्हित अक्षर भग्न_detect_tininess;
क्रमागत अणु
    भग्न_tininess_after_rounding  = 0,
    भग्न_tininess_beक्रमe_rounding = 1
पूर्ण;

/*
-------------------------------------------------------------------------------
Software IEC/IEEE भग्नing-poपूर्णांक rounding mode.
-------------------------------------------------------------------------------
*/
//बाह्य पूर्णांक8 भग्न_rounding_mode;
क्रमागत अणु
    भग्न_round_nearest_even = 0,
    भग्न_round_to_zero      = 1,
    भग्न_round_करोwn         = 2,
    भग्न_round_up           = 3
पूर्ण;

/*
-------------------------------------------------------------------------------
Software IEC/IEEE भग्नing-poपूर्णांक exception flags.
-------------------------------------------------------------------------------
क्रमागत अणु
    भग्न_flag_inexact   =  1,
    भग्न_flag_underflow =  2,
    भग्न_flag_overflow  =  4,
    भग्न_flag_भागbyzero =  8,
    भग्न_flag_invalid   = 16
पूर्ण;

ScottB: November 4, 1998
Changed the क्रमागतeration to match the bit order in the FPA11.
*/

क्रमागत अणु
    भग्न_flag_invalid   =  1,
    भग्न_flag_भागbyzero =  2,
    भग्न_flag_overflow  =  4,
    भग्न_flag_underflow =  8,
    भग्न_flag_inexact   = 16
पूर्ण;

/*
-------------------------------------------------------------------------------
Routine to उठाओ any or all of the software IEC/IEEE भग्नing-poपूर्णांक
exception flags.
-------------------------------------------------------------------------------
*/
व्योम भग्न_उठाओ( चिन्हित अक्षर );

/*
-------------------------------------------------------------------------------
Software IEC/IEEE पूर्णांकeger-to-भग्नing-poपूर्णांक conversion routines.
-------------------------------------------------------------------------------
*/
भग्न32 पूर्णांक32_to_भग्न32( काष्ठा roundingData *, चिन्हित पूर्णांक );
भग्न64 पूर्णांक32_to_भग्न64( चिन्हित पूर्णांक );
#अगर_घोषित FLOATX80
भग्नx80 पूर्णांक32_to_भग्नx80( चिन्हित पूर्णांक );
#पूर्ण_अगर

/*
-------------------------------------------------------------------------------
Software IEC/IEEE single-precision conversion routines.
-------------------------------------------------------------------------------
*/
चिन्हित पूर्णांक भग्न32_to_पूर्णांक32( काष्ठा roundingData *, भग्न32 );
चिन्हित पूर्णांक भग्न32_to_पूर्णांक32_round_to_zero( भग्न32 );
भग्न64 भग्न32_to_भग्न64( भग्न32 );
#अगर_घोषित FLOATX80
भग्नx80 भग्न32_to_भग्नx80( भग्न32 );
#पूर्ण_अगर

/*
-------------------------------------------------------------------------------
Software IEC/IEEE single-precision operations.
-------------------------------------------------------------------------------
*/
भग्न32 भग्न32_round_to_पूर्णांक( काष्ठा roundingData*, भग्न32 );
भग्न32 भग्न32_add( काष्ठा roundingData *, भग्न32, भग्न32 );
भग्न32 भग्न32_sub( काष्ठा roundingData *, भग्न32, भग्न32 );
भग्न32 भग्न32_mul( काष्ठा roundingData *, भग्न32, भग्न32 );
भग्न32 भग्न32_भाग( काष्ठा roundingData *, भग्न32, भग्न32 );
भग्न32 भग्न32_rem( काष्ठा roundingData *, भग्न32, भग्न32 );
भग्न32 भग्न32_वर्ग_मूल( काष्ठा roundingData*, भग्न32 );
अक्षर भग्न32_eq( भग्न32, भग्न32 );
अक्षर भग्न32_le( भग्न32, भग्न32 );
अक्षर भग्न32_lt( भग्न32, भग्न32 );
अक्षर भग्न32_eq_संकेतing( भग्न32, भग्न32 );
अक्षर भग्न32_le_quiet( भग्न32, भग्न32 );
अक्षर भग्न32_lt_quiet( भग्न32, भग्न32 );
अक्षर भग्न32_is_संकेतing_nan( भग्न32 );

/*
-------------------------------------------------------------------------------
Software IEC/IEEE द्विगुन-precision conversion routines.
-------------------------------------------------------------------------------
*/
चिन्हित पूर्णांक भग्न64_to_पूर्णांक32( काष्ठा roundingData *, भग्न64 );
चिन्हित पूर्णांक भग्न64_to_पूर्णांक32_round_to_zero( भग्न64 );
भग्न32 भग्न64_to_भग्न32( काष्ठा roundingData *, भग्न64 );
#अगर_घोषित FLOATX80
भग्नx80 भग्न64_to_भग्नx80( भग्न64 );
#पूर्ण_अगर

/*
-------------------------------------------------------------------------------
Software IEC/IEEE द्विगुन-precision operations.
-------------------------------------------------------------------------------
*/
भग्न64 भग्न64_round_to_पूर्णांक( काष्ठा roundingData *, भग्न64 );
भग्न64 भग्न64_add( काष्ठा roundingData *, भग्न64, भग्न64 );
भग्न64 भग्न64_sub( काष्ठा roundingData *, भग्न64, भग्न64 );
भग्न64 भग्न64_mul( काष्ठा roundingData *, भग्न64, भग्न64 );
भग्न64 भग्न64_भाग( काष्ठा roundingData *, भग्न64, भग्न64 );
भग्न64 भग्न64_rem( काष्ठा roundingData *, भग्न64, भग्न64 );
भग्न64 भग्न64_वर्ग_मूल( काष्ठा roundingData *, भग्न64 );
अक्षर भग्न64_eq( भग्न64, भग्न64 );
अक्षर भग्न64_le( भग्न64, भग्न64 );
अक्षर भग्न64_lt( भग्न64, भग्न64 );
अक्षर भग्न64_eq_संकेतing( भग्न64, भग्न64 );
अक्षर भग्न64_le_quiet( भग्न64, भग्न64 );
अक्षर भग्न64_lt_quiet( भग्न64, भग्न64 );
अक्षर भग्न64_is_संकेतing_nan( भग्न64 );

#अगर_घोषित FLOATX80

/*
-------------------------------------------------------------------------------
Software IEC/IEEE extended द्विगुन-precision conversion routines.
-------------------------------------------------------------------------------
*/
चिन्हित पूर्णांक भग्नx80_to_पूर्णांक32( काष्ठा roundingData *, भग्नx80 );
चिन्हित पूर्णांक भग्नx80_to_पूर्णांक32_round_to_zero( भग्नx80 );
भग्न32 भग्नx80_to_भग्न32( काष्ठा roundingData *, भग्नx80 );
भग्न64 भग्नx80_to_भग्न64( काष्ठा roundingData *, भग्नx80 );

/*
-------------------------------------------------------------------------------
Software IEC/IEEE extended द्विगुन-precision operations.
-------------------------------------------------------------------------------
*/
भग्नx80 भग्नx80_round_to_पूर्णांक( काष्ठा roundingData *, भग्नx80 );
भग्नx80 भग्नx80_add( काष्ठा roundingData *, भग्नx80, भग्नx80 );
भग्नx80 भग्नx80_sub( काष्ठा roundingData *, भग्नx80, भग्नx80 );
भग्नx80 भग्नx80_mul( काष्ठा roundingData *, भग्नx80, भग्नx80 );
भग्नx80 भग्नx80_भाग( काष्ठा roundingData *, भग्नx80, भग्नx80 );
भग्नx80 भग्नx80_rem( काष्ठा roundingData *, भग्नx80, भग्नx80 );
भग्नx80 भग्नx80_वर्ग_मूल( काष्ठा roundingData *, भग्नx80 );
अक्षर भग्नx80_eq( भग्नx80, भग्नx80 );
अक्षर भग्नx80_le( भग्नx80, भग्नx80 );
अक्षर भग्नx80_lt( भग्नx80, भग्नx80 );
अक्षर भग्नx80_eq_संकेतing( भग्नx80, भग्नx80 );
अक्षर भग्नx80_le_quiet( भग्नx80, भग्नx80 );
अक्षर भग्नx80_lt_quiet( भग्नx80, भग्नx80 );
अक्षर भग्नx80_is_संकेतing_nan( भग्नx80 );

बाह्य flag भग्नx80_is_nan(भग्नx80);

#पूर्ण_अगर

अटल अंतरभूत flag extractFloat32Sign(भग्न32 a)
अणु
	वापस a >> 31;
पूर्ण

अटल अंतरभूत flag भग्न32_eq_nocheck(भग्न32 a, भग्न32 b)
अणु
	वापस (a == b) || ((bits32) ((a | b) << 1) == 0);
पूर्ण

अटल अंतरभूत flag भग्न32_lt_nocheck(भग्न32 a, भग्न32 b)
अणु
	flag aSign, bSign;

	aSign = extractFloat32Sign(a);
	bSign = extractFloat32Sign(b);
	अगर (aSign != bSign)
		वापस aSign && ((bits32) ((a | b) << 1) != 0);
	वापस (a != b) && (aSign ^ (a < b));
पूर्ण

अटल अंतरभूत flag extractFloat64Sign(भग्न64 a)
अणु
	वापस a >> 63;
पूर्ण

अटल अंतरभूत flag भग्न64_eq_nocheck(भग्न64 a, भग्न64 b)
अणु
	वापस (a == b) || ((bits64) ((a | b) << 1) == 0);
पूर्ण

अटल अंतरभूत flag भग्न64_lt_nocheck(भग्न64 a, भग्न64 b)
अणु
	flag aSign, bSign;

	aSign = extractFloat64Sign(a);
	bSign = extractFloat64Sign(b);
	अगर (aSign != bSign)
		वापस aSign && ((bits64) ((a | b) << 1) != 0);
	वापस (a != b) && (aSign ^ (a < b));
पूर्ण

बाह्य flag भग्न32_is_nan( भग्न32 a );
बाह्य flag भग्न64_is_nan( भग्न64 a );

बाह्य पूर्णांक32 भग्न64_to_uपूर्णांक32( काष्ठा roundingData *roundData, भग्न64 a );
बाह्य पूर्णांक32 भग्न64_to_uपूर्णांक32_round_to_zero( भग्न64 a );

#पूर्ण_अगर
