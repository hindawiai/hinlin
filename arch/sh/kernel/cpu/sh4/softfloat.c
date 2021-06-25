<शैली गुरु>
/*
 * Floating poपूर्णांक emulation support क्रम subnormalised numbers on SH4
 * architecture This file is derived from the SoftFloat IEC/IEEE
 * Floating-poपूर्णांक Arithmetic Package, Release 2 the original license of
 * which is reproduced below.
 *
 * ========================================================================
 *
 * This C source file is part of the SoftFloat IEC/IEEE Floating-poपूर्णांक
 * Arithmetic Package, Release 2.
 *
 * Written by John R. Hauser.  This work was made possible in part by the
 * International Computer Science Institute, located at Suite 600, 1947 Center
 * Street, Berkeley, Calअगरornia 94704.  Funding was partially provided by the
 * National Science Foundation under grant MIP-9311980.  The original version
 * of this code was written as part of a project to build a fixed-poपूर्णांक vector
 * processor in collaboration with the University of Calअगरornia at Berkeley,
 * overseen by Profs. Nelson Morgan and John Wawrzynek.  More inक्रमmation
 * is available through the web page `http://HTTP.CS.Berkeley.EDU/~jhauser/
 * arithmetic/softभग्न.सपंचांगl'.
 *
 * THIS SOFTWARE IS DISTRIBUTED AS IS, FOR FREE.  Although reasonable efक्रमt
 * has been made to aव्योम it, THIS SOFTWARE MAY CONTAIN FAULTS THAT WILL AT
 * TIMES RESULT IN INCORRECT BEHAVIOR.  USE OF THIS SOFTWARE IS RESTRICTED TO
 * PERSONS AND ORGANIZATIONS WHO CAN AND WILL TAKE FULL RESPONSIBILITY FOR ANY
 * AND ALL LOSSES, COSTS, OR OTHER PROBLEMS ARISING FROM ITS USE.
 *
 * Derivative works are acceptable, even क्रम commercial purposes, so दीर्घ as
 * (1) they include prominent notice that the work is derivative, and (2) they
 * include prominent notice akin to these three paragraphs क्रम those parts of
 * this code that are retained.
 *
 * ========================================================================
 *
 * SH4 modअगरications by Ismail Dhaoui <ismail.dhaoui@st.com>
 * and Kamel Khelअगरi <kamel.khelअगरi@st.com>
 */
#समावेश <linux/kernel.h>
#समावेश <cpu/fpu.h>
#समावेश <यंत्र/भाग64.h>

#घोषणा LIT64( a ) a##LL

प्रकार अक्षर flag;
प्रकार अचिन्हित अक्षर uपूर्णांक8;
प्रकार चिन्हित अक्षर पूर्णांक8;
प्रकार पूर्णांक uपूर्णांक16;
प्रकार पूर्णांक पूर्णांक16;
प्रकार अचिन्हित पूर्णांक uपूर्णांक32;
प्रकार चिन्हित पूर्णांक पूर्णांक32;

प्रकार अचिन्हित दीर्घ दीर्घ पूर्णांक bits64;
प्रकार चिन्हित दीर्घ दीर्घ पूर्णांक sbits64;

प्रकार अचिन्हित अक्षर bits8;
प्रकार चिन्हित अक्षर sbits8;
प्रकार अचिन्हित लघु पूर्णांक bits16;
प्रकार चिन्हित लघु पूर्णांक sbits16;
प्रकार अचिन्हित पूर्णांक bits32;
प्रकार चिन्हित पूर्णांक sbits32;

प्रकार अचिन्हित दीर्घ दीर्घ पूर्णांक uपूर्णांक64;
प्रकार चिन्हित दीर्घ दीर्घ पूर्णांक पूर्णांक64;

प्रकार अचिन्हित दीर्घ पूर्णांक भग्न32;
प्रकार अचिन्हित दीर्घ दीर्घ भग्न64;

बाह्य व्योम भग्न_उठाओ(अचिन्हित पूर्णांक flags);	/* in fpu.c */
बाह्य पूर्णांक भग्न_rounding_mode(व्योम);	/* in fpu.c */

bits64 extractFloat64Frac(भग्न64 a);
flag extractFloat64Sign(भग्न64 a);
पूर्णांक16 extractFloat64Exp(भग्न64 a);
पूर्णांक16 extractFloat32Exp(भग्न32 a);
flag extractFloat32Sign(भग्न32 a);
bits32 extractFloat32Frac(भग्न32 a);
भग्न64 packFloat64(flag zSign, पूर्णांक16 zExp, bits64 zSig);
व्योम shअगरt64RightJamming(bits64 a, पूर्णांक16 count, bits64 * zPtr);
भग्न32 packFloat32(flag zSign, पूर्णांक16 zExp, bits32 zSig);
व्योम shअगरt32RightJamming(bits32 a, पूर्णांक16 count, bits32 * zPtr);
भग्न64 भग्न64_sub(भग्न64 a, भग्न64 b);
भग्न32 भग्न32_sub(भग्न32 a, भग्न32 b);
भग्न32 भग्न32_add(भग्न32 a, भग्न32 b);
भग्न64 भग्न64_add(भग्न64 a, भग्न64 b);
भग्न64 भग्न64_भाग(भग्न64 a, भग्न64 b);
भग्न32 भग्न32_भाग(भग्न32 a, भग्न32 b);
भग्न32 भग्न32_mul(भग्न32 a, भग्न32 b);
भग्न64 भग्न64_mul(भग्न64 a, भग्न64 b);
भग्न32 भग्न64_to_भग्न32(भग्न64 a);
व्योम add128(bits64 a0, bits64 a1, bits64 b0, bits64 b1, bits64 * z0Ptr,
		   bits64 * z1Ptr);
व्योम sub128(bits64 a0, bits64 a1, bits64 b0, bits64 b1, bits64 * z0Ptr,
		   bits64 * z1Ptr);
व्योम mul64To128(bits64 a, bits64 b, bits64 * z0Ptr, bits64 * z1Ptr);

अटल पूर्णांक8 countLeadingZeros32(bits32 a);
अटल पूर्णांक8 countLeadingZeros64(bits64 a);
अटल भग्न64 normalizeRoundAndPackFloat64(flag zSign, पूर्णांक16 zExp,
					    bits64 zSig);
अटल भग्न64 subFloat64Sigs(भग्न64 a, भग्न64 b, flag zSign);
अटल भग्न64 addFloat64Sigs(भग्न64 a, भग्न64 b, flag zSign);
अटल भग्न32 roundAndPackFloat32(flag zSign, पूर्णांक16 zExp, bits32 zSig);
अटल भग्न32 normalizeRoundAndPackFloat32(flag zSign, पूर्णांक16 zExp,
					    bits32 zSig);
अटल भग्न64 roundAndPackFloat64(flag zSign, पूर्णांक16 zExp, bits64 zSig);
अटल भग्न32 subFloat32Sigs(भग्न32 a, भग्न32 b, flag zSign);
अटल भग्न32 addFloat32Sigs(भग्न32 a, भग्न32 b, flag zSign);
अटल व्योम normalizeFloat64Subnormal(bits64 aSig, पूर्णांक16 * zExpPtr,
				      bits64 * zSigPtr);
अटल bits64 estimateDiv128To64(bits64 a0, bits64 a1, bits64 b);
अटल व्योम normalizeFloat32Subnormal(bits32 aSig, पूर्णांक16 * zExpPtr,
				      bits32 * zSigPtr);

bits64 extractFloat64Frac(भग्न64 a)
अणु
	वापस a & LIT64(0x000FFFFFFFFFFFFF);
पूर्ण

flag extractFloat64Sign(भग्न64 a)
अणु
	वापस a >> 63;
पूर्ण

पूर्णांक16 extractFloat64Exp(भग्न64 a)
अणु
	वापस (a >> 52) & 0x7FF;
पूर्ण

पूर्णांक16 extractFloat32Exp(भग्न32 a)
अणु
	वापस (a >> 23) & 0xFF;
पूर्ण

flag extractFloat32Sign(भग्न32 a)
अणु
	वापस a >> 31;
पूर्ण

bits32 extractFloat32Frac(भग्न32 a)
अणु
	वापस a & 0x007FFFFF;
पूर्ण

भग्न64 packFloat64(flag zSign, पूर्णांक16 zExp, bits64 zSig)
अणु
	वापस (((bits64) zSign) << 63) + (((bits64) zExp) << 52) + zSig;
पूर्ण

व्योम shअगरt64RightJamming(bits64 a, पूर्णांक16 count, bits64 * zPtr)
अणु
	bits64 z;

	अगर (count == 0) अणु
		z = a;
	पूर्ण अन्यथा अगर (count < 64) अणु
		z = (a >> count) | ((a << ((-count) & 63)) != 0);
	पूर्ण अन्यथा अणु
		z = (a != 0);
	पूर्ण
	*zPtr = z;
पूर्ण

अटल पूर्णांक8 countLeadingZeros32(bits32 a)
अणु
	अटल स्थिर पूर्णांक8 countLeadingZerosHigh[] = अणु
		8, 7, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	पूर्ण;
	पूर्णांक8 shअगरtCount;

	shअगरtCount = 0;
	अगर (a < 0x10000) अणु
		shअगरtCount += 16;
		a <<= 16;
	पूर्ण
	अगर (a < 0x1000000) अणु
		shअगरtCount += 8;
		a <<= 8;
	पूर्ण
	shअगरtCount += countLeadingZerosHigh[a >> 24];
	वापस shअगरtCount;

पूर्ण

अटल पूर्णांक8 countLeadingZeros64(bits64 a)
अणु
	पूर्णांक8 shअगरtCount;

	shअगरtCount = 0;
	अगर (a < ((bits64) 1) << 32) अणु
		shअगरtCount += 32;
	पूर्ण अन्यथा अणु
		a >>= 32;
	पूर्ण
	shअगरtCount += countLeadingZeros32(a);
	वापस shअगरtCount;

पूर्ण

अटल भग्न64 normalizeRoundAndPackFloat64(flag zSign, पूर्णांक16 zExp, bits64 zSig)
अणु
	पूर्णांक8 shअगरtCount;

	shअगरtCount = countLeadingZeros64(zSig) - 1;
	वापस roundAndPackFloat64(zSign, zExp - shअगरtCount,
				   zSig << shअगरtCount);

पूर्ण

अटल भग्न64 subFloat64Sigs(भग्न64 a, भग्न64 b, flag zSign)
अणु
	पूर्णांक16 aExp, bExp, zExp;
	bits64 aSig, bSig, zSig;
	पूर्णांक16 expDअगरf;

	aSig = extractFloat64Frac(a);
	aExp = extractFloat64Exp(a);
	bSig = extractFloat64Frac(b);
	bExp = extractFloat64Exp(b);
	expDअगरf = aExp - bExp;
	aSig <<= 10;
	bSig <<= 10;
	अगर (0 < expDअगरf)
		जाओ aExpBigger;
	अगर (expDअगरf < 0)
		जाओ bExpBigger;
	अगर (aExp == 0) अणु
		aExp = 1;
		bExp = 1;
	पूर्ण
	अगर (bSig < aSig)
		जाओ aBigger;
	अगर (aSig < bSig)
		जाओ bBigger;
	वापस packFloat64(भग्न_rounding_mode() == FPSCR_RM_ZERO, 0, 0);
      bExpBigger:
	अगर (bExp == 0x7FF) अणु
		वापस packFloat64(zSign ^ 1, 0x7FF, 0);
	पूर्ण
	अगर (aExp == 0) अणु
		++expDअगरf;
	पूर्ण अन्यथा अणु
		aSig |= LIT64(0x4000000000000000);
	पूर्ण
	shअगरt64RightJamming(aSig, -expDअगरf, &aSig);
	bSig |= LIT64(0x4000000000000000);
      bBigger:
	zSig = bSig - aSig;
	zExp = bExp;
	zSign ^= 1;
	जाओ normalizeRoundAndPack;
      aExpBigger:
	अगर (aExp == 0x7FF) अणु
		वापस a;
	पूर्ण
	अगर (bExp == 0) अणु
		--expDअगरf;
	पूर्ण अन्यथा अणु
		bSig |= LIT64(0x4000000000000000);
	पूर्ण
	shअगरt64RightJamming(bSig, expDअगरf, &bSig);
	aSig |= LIT64(0x4000000000000000);
      aBigger:
	zSig = aSig - bSig;
	zExp = aExp;
      normalizeRoundAndPack:
	--zExp;
	वापस normalizeRoundAndPackFloat64(zSign, zExp, zSig);

पूर्ण
अटल भग्न64 addFloat64Sigs(भग्न64 a, भग्न64 b, flag zSign)
अणु
	पूर्णांक16 aExp, bExp, zExp;
	bits64 aSig, bSig, zSig;
	पूर्णांक16 expDअगरf;

	aSig = extractFloat64Frac(a);
	aExp = extractFloat64Exp(a);
	bSig = extractFloat64Frac(b);
	bExp = extractFloat64Exp(b);
	expDअगरf = aExp - bExp;
	aSig <<= 9;
	bSig <<= 9;
	अगर (0 < expDअगरf) अणु
		अगर (aExp == 0x7FF) अणु
			वापस a;
		पूर्ण
		अगर (bExp == 0) अणु
			--expDअगरf;
		पूर्ण अन्यथा अणु
			bSig |= LIT64(0x2000000000000000);
		पूर्ण
		shअगरt64RightJamming(bSig, expDअगरf, &bSig);
		zExp = aExp;
	पूर्ण अन्यथा अगर (expDअगरf < 0) अणु
		अगर (bExp == 0x7FF) अणु
			वापस packFloat64(zSign, 0x7FF, 0);
		पूर्ण
		अगर (aExp == 0) अणु
			++expDअगरf;
		पूर्ण अन्यथा अणु
			aSig |= LIT64(0x2000000000000000);
		पूर्ण
		shअगरt64RightJamming(aSig, -expDअगरf, &aSig);
		zExp = bExp;
	पूर्ण अन्यथा अणु
		अगर (aExp == 0x7FF) अणु
			वापस a;
		पूर्ण
		अगर (aExp == 0)
			वापस packFloat64(zSign, 0, (aSig + bSig) >> 9);
		zSig = LIT64(0x4000000000000000) + aSig + bSig;
		zExp = aExp;
		जाओ roundAndPack;
	पूर्ण
	aSig |= LIT64(0x2000000000000000);
	zSig = (aSig + bSig) << 1;
	--zExp;
	अगर ((sbits64) zSig < 0) अणु
		zSig = aSig + bSig;
		++zExp;
	पूर्ण
      roundAndPack:
	वापस roundAndPackFloat64(zSign, zExp, zSig);

पूर्ण

भग्न32 packFloat32(flag zSign, पूर्णांक16 zExp, bits32 zSig)
अणु
	वापस (((bits32) zSign) << 31) + (((bits32) zExp) << 23) + zSig;
पूर्ण

व्योम shअगरt32RightJamming(bits32 a, पूर्णांक16 count, bits32 * zPtr)
अणु
	bits32 z;
	अगर (count == 0) अणु
		z = a;
	पूर्ण अन्यथा अगर (count < 32) अणु
		z = (a >> count) | ((a << ((-count) & 31)) != 0);
	पूर्ण अन्यथा अणु
		z = (a != 0);
	पूर्ण
	*zPtr = z;
पूर्ण

अटल भग्न32 roundAndPackFloat32(flag zSign, पूर्णांक16 zExp, bits32 zSig)
अणु
	flag roundNearestEven;
	पूर्णांक8 roundIncrement, roundBits;
	flag isTiny;

	/* SH4 has only 2 rounding modes - round to nearest and round to zero */
	roundNearestEven = (भग्न_rounding_mode() == FPSCR_RM_NEAREST);
	roundIncrement = 0x40;
	अगर (!roundNearestEven) अणु
		roundIncrement = 0;
	पूर्ण
	roundBits = zSig & 0x7F;
	अगर (0xFD <= (bits16) zExp) अणु
		अगर ((0xFD < zExp)
		    || ((zExp == 0xFD)
			&& ((sbits32) (zSig + roundIncrement) < 0))
		    ) अणु
			भग्न_उठाओ(FPSCR_CAUSE_OVERFLOW | FPSCR_CAUSE_INEXACT);
			वापस packFloat32(zSign, 0xFF,
					   0) - (roundIncrement == 0);
		पूर्ण
		अगर (zExp < 0) अणु
			isTiny = (zExp < -1)
			    || (zSig + roundIncrement < 0x80000000);
			shअगरt32RightJamming(zSig, -zExp, &zSig);
			zExp = 0;
			roundBits = zSig & 0x7F;
			अगर (isTiny && roundBits)
				भग्न_उठाओ(FPSCR_CAUSE_UNDERFLOW);
		पूर्ण
	पूर्ण
	अगर (roundBits)
		भग्न_उठाओ(FPSCR_CAUSE_INEXACT);
	zSig = (zSig + roundIncrement) >> 7;
	zSig &= ~(((roundBits ^ 0x40) == 0) & roundNearestEven);
	अगर (zSig == 0)
		zExp = 0;
	वापस packFloat32(zSign, zExp, zSig);

पूर्ण

अटल भग्न32 normalizeRoundAndPackFloat32(flag zSign, पूर्णांक16 zExp, bits32 zSig)
अणु
	पूर्णांक8 shअगरtCount;

	shअगरtCount = countLeadingZeros32(zSig) - 1;
	वापस roundAndPackFloat32(zSign, zExp - shअगरtCount,
				   zSig << shअगरtCount);
पूर्ण

अटल भग्न64 roundAndPackFloat64(flag zSign, पूर्णांक16 zExp, bits64 zSig)
अणु
	flag roundNearestEven;
	पूर्णांक16 roundIncrement, roundBits;
	flag isTiny;

	/* SH4 has only 2 rounding modes - round to nearest and round to zero */
	roundNearestEven = (भग्न_rounding_mode() == FPSCR_RM_NEAREST);
	roundIncrement = 0x200;
	अगर (!roundNearestEven) अणु
		roundIncrement = 0;
	पूर्ण
	roundBits = zSig & 0x3FF;
	अगर (0x7FD <= (bits16) zExp) अणु
		अगर ((0x7FD < zExp)
		    || ((zExp == 0x7FD)
			&& ((sbits64) (zSig + roundIncrement) < 0))
		    ) अणु
			भग्न_उठाओ(FPSCR_CAUSE_OVERFLOW | FPSCR_CAUSE_INEXACT);
			वापस packFloat64(zSign, 0x7FF,
					   0) - (roundIncrement == 0);
		पूर्ण
		अगर (zExp < 0) अणु
			isTiny = (zExp < -1)
			    || (zSig + roundIncrement <
				LIT64(0x8000000000000000));
			shअगरt64RightJamming(zSig, -zExp, &zSig);
			zExp = 0;
			roundBits = zSig & 0x3FF;
			अगर (isTiny && roundBits)
				भग्न_उठाओ(FPSCR_CAUSE_UNDERFLOW);
		पूर्ण
	पूर्ण
	अगर (roundBits)
		भग्न_उठाओ(FPSCR_CAUSE_INEXACT);
	zSig = (zSig + roundIncrement) >> 10;
	zSig &= ~(((roundBits ^ 0x200) == 0) & roundNearestEven);
	अगर (zSig == 0)
		zExp = 0;
	वापस packFloat64(zSign, zExp, zSig);

पूर्ण

अटल भग्न32 subFloat32Sigs(भग्न32 a, भग्न32 b, flag zSign)
अणु
	पूर्णांक16 aExp, bExp, zExp;
	bits32 aSig, bSig, zSig;
	पूर्णांक16 expDअगरf;

	aSig = extractFloat32Frac(a);
	aExp = extractFloat32Exp(a);
	bSig = extractFloat32Frac(b);
	bExp = extractFloat32Exp(b);
	expDअगरf = aExp - bExp;
	aSig <<= 7;
	bSig <<= 7;
	अगर (0 < expDअगरf)
		जाओ aExpBigger;
	अगर (expDअगरf < 0)
		जाओ bExpBigger;
	अगर (aExp == 0) अणु
		aExp = 1;
		bExp = 1;
	पूर्ण
	अगर (bSig < aSig)
		जाओ aBigger;
	अगर (aSig < bSig)
		जाओ bBigger;
	वापस packFloat32(भग्न_rounding_mode() == FPSCR_RM_ZERO, 0, 0);
      bExpBigger:
	अगर (bExp == 0xFF) अणु
		वापस packFloat32(zSign ^ 1, 0xFF, 0);
	पूर्ण
	अगर (aExp == 0) अणु
		++expDअगरf;
	पूर्ण अन्यथा अणु
		aSig |= 0x40000000;
	पूर्ण
	shअगरt32RightJamming(aSig, -expDअगरf, &aSig);
	bSig |= 0x40000000;
      bBigger:
	zSig = bSig - aSig;
	zExp = bExp;
	zSign ^= 1;
	जाओ normalizeRoundAndPack;
      aExpBigger:
	अगर (aExp == 0xFF) अणु
		वापस a;
	पूर्ण
	अगर (bExp == 0) अणु
		--expDअगरf;
	पूर्ण अन्यथा अणु
		bSig |= 0x40000000;
	पूर्ण
	shअगरt32RightJamming(bSig, expDअगरf, &bSig);
	aSig |= 0x40000000;
      aBigger:
	zSig = aSig - bSig;
	zExp = aExp;
      normalizeRoundAndPack:
	--zExp;
	वापस normalizeRoundAndPackFloat32(zSign, zExp, zSig);

पूर्ण

अटल भग्न32 addFloat32Sigs(भग्न32 a, भग्न32 b, flag zSign)
अणु
	पूर्णांक16 aExp, bExp, zExp;
	bits32 aSig, bSig, zSig;
	पूर्णांक16 expDअगरf;

	aSig = extractFloat32Frac(a);
	aExp = extractFloat32Exp(a);
	bSig = extractFloat32Frac(b);
	bExp = extractFloat32Exp(b);
	expDअगरf = aExp - bExp;
	aSig <<= 6;
	bSig <<= 6;
	अगर (0 < expDअगरf) अणु
		अगर (aExp == 0xFF) अणु
			वापस a;
		पूर्ण
		अगर (bExp == 0) अणु
			--expDअगरf;
		पूर्ण अन्यथा अणु
			bSig |= 0x20000000;
		पूर्ण
		shअगरt32RightJamming(bSig, expDअगरf, &bSig);
		zExp = aExp;
	पूर्ण अन्यथा अगर (expDअगरf < 0) अणु
		अगर (bExp == 0xFF) अणु
			वापस packFloat32(zSign, 0xFF, 0);
		पूर्ण
		अगर (aExp == 0) अणु
			++expDअगरf;
		पूर्ण अन्यथा अणु
			aSig |= 0x20000000;
		पूर्ण
		shअगरt32RightJamming(aSig, -expDअगरf, &aSig);
		zExp = bExp;
	पूर्ण अन्यथा अणु
		अगर (aExp == 0xFF) अणु
			वापस a;
		पूर्ण
		अगर (aExp == 0)
			वापस packFloat32(zSign, 0, (aSig + bSig) >> 6);
		zSig = 0x40000000 + aSig + bSig;
		zExp = aExp;
		जाओ roundAndPack;
	पूर्ण
	aSig |= 0x20000000;
	zSig = (aSig + bSig) << 1;
	--zExp;
	अगर ((sbits32) zSig < 0) अणु
		zSig = aSig + bSig;
		++zExp;
	पूर्ण
      roundAndPack:
	वापस roundAndPackFloat32(zSign, zExp, zSig);

पूर्ण

भग्न64 भग्न64_sub(भग्न64 a, भग्न64 b)
अणु
	flag aSign, bSign;

	aSign = extractFloat64Sign(a);
	bSign = extractFloat64Sign(b);
	अगर (aSign == bSign) अणु
		वापस subFloat64Sigs(a, b, aSign);
	पूर्ण अन्यथा अणु
		वापस addFloat64Sigs(a, b, aSign);
	पूर्ण

पूर्ण

भग्न32 भग्न32_sub(भग्न32 a, भग्न32 b)
अणु
	flag aSign, bSign;

	aSign = extractFloat32Sign(a);
	bSign = extractFloat32Sign(b);
	अगर (aSign == bSign) अणु
		वापस subFloat32Sigs(a, b, aSign);
	पूर्ण अन्यथा अणु
		वापस addFloat32Sigs(a, b, aSign);
	पूर्ण

पूर्ण

भग्न32 भग्न32_add(भग्न32 a, भग्न32 b)
अणु
	flag aSign, bSign;

	aSign = extractFloat32Sign(a);
	bSign = extractFloat32Sign(b);
	अगर (aSign == bSign) अणु
		वापस addFloat32Sigs(a, b, aSign);
	पूर्ण अन्यथा अणु
		वापस subFloat32Sigs(a, b, aSign);
	पूर्ण

पूर्ण

भग्न64 भग्न64_add(भग्न64 a, भग्न64 b)
अणु
	flag aSign, bSign;

	aSign = extractFloat64Sign(a);
	bSign = extractFloat64Sign(b);
	अगर (aSign == bSign) अणु
		वापस addFloat64Sigs(a, b, aSign);
	पूर्ण अन्यथा अणु
		वापस subFloat64Sigs(a, b, aSign);
	पूर्ण
पूर्ण

अटल व्योम
normalizeFloat64Subnormal(bits64 aSig, पूर्णांक16 * zExpPtr, bits64 * zSigPtr)
अणु
	पूर्णांक8 shअगरtCount;

	shअगरtCount = countLeadingZeros64(aSig) - 11;
	*zSigPtr = aSig << shअगरtCount;
	*zExpPtr = 1 - shअगरtCount;
पूर्ण

व्योम add128(bits64 a0, bits64 a1, bits64 b0, bits64 b1, bits64 * z0Ptr,
		   bits64 * z1Ptr)
अणु
	bits64 z1;

	z1 = a1 + b1;
	*z1Ptr = z1;
	*z0Ptr = a0 + b0 + (z1 < a1);
पूर्ण

व्योम
sub128(bits64 a0, bits64 a1, bits64 b0, bits64 b1, bits64 * z0Ptr,
       bits64 * z1Ptr)
अणु
	*z1Ptr = a1 - b1;
	*z0Ptr = a0 - b0 - (a1 < b1);
पूर्ण

अटल bits64 estimateDiv128To64(bits64 a0, bits64 a1, bits64 b)
अणु
	bits64 b0, b1;
	bits64 rem0, rem1, term0, term1;
	bits64 z, पंचांगp;
	अगर (b <= a0)
		वापस LIT64(0xFFFFFFFFFFFFFFFF);
	b0 = b >> 32;
	पंचांगp = a0;
	करो_भाग(पंचांगp, b0);

	z = (b0 << 32 <= a0) ? LIT64(0xFFFFFFFF00000000) : पंचांगp << 32;
	mul64To128(b, z, &term0, &term1);
	sub128(a0, a1, term0, term1, &rem0, &rem1);
	जबतक (((sbits64) rem0) < 0) अणु
		z -= LIT64(0x100000000);
		b1 = b << 32;
		add128(rem0, rem1, b0, b1, &rem0, &rem1);
	पूर्ण
	rem0 = (rem0 << 32) | (rem1 >> 32);
	पंचांगp = rem0;
	करो_भाग(पंचांगp, b0);
	z |= (b0 << 32 <= rem0) ? 0xFFFFFFFF : पंचांगp;
	वापस z;
पूर्ण

व्योम mul64To128(bits64 a, bits64 b, bits64 * z0Ptr, bits64 * z1Ptr)
अणु
	bits32 aHigh, aLow, bHigh, bLow;
	bits64 z0, zMiddleA, zMiddleB, z1;

	aLow = a;
	aHigh = a >> 32;
	bLow = b;
	bHigh = b >> 32;
	z1 = ((bits64) aLow) * bLow;
	zMiddleA = ((bits64) aLow) * bHigh;
	zMiddleB = ((bits64) aHigh) * bLow;
	z0 = ((bits64) aHigh) * bHigh;
	zMiddleA += zMiddleB;
	z0 += (((bits64) (zMiddleA < zMiddleB)) << 32) + (zMiddleA >> 32);
	zMiddleA <<= 32;
	z1 += zMiddleA;
	z0 += (z1 < zMiddleA);
	*z1Ptr = z1;
	*z0Ptr = z0;

पूर्ण

अटल व्योम normalizeFloat32Subnormal(bits32 aSig, पूर्णांक16 * zExpPtr,
				      bits32 * zSigPtr)
अणु
	पूर्णांक8 shअगरtCount;

	shअगरtCount = countLeadingZeros32(aSig) - 8;
	*zSigPtr = aSig << shअगरtCount;
	*zExpPtr = 1 - shअगरtCount;

पूर्ण

भग्न64 भग्न64_भाग(भग्न64 a, भग्न64 b)
अणु
	flag aSign, bSign, zSign;
	पूर्णांक16 aExp, bExp, zExp;
	bits64 aSig, bSig, zSig;
	bits64 rem0, rem1;
	bits64 term0, term1;

	aSig = extractFloat64Frac(a);
	aExp = extractFloat64Exp(a);
	aSign = extractFloat64Sign(a);
	bSig = extractFloat64Frac(b);
	bExp = extractFloat64Exp(b);
	bSign = extractFloat64Sign(b);
	zSign = aSign ^ bSign;
	अगर (aExp == 0x7FF) अणु
		अगर (bExp == 0x7FF) अणु
		पूर्ण
		वापस packFloat64(zSign, 0x7FF, 0);
	पूर्ण
	अगर (bExp == 0x7FF) अणु
		वापस packFloat64(zSign, 0, 0);
	पूर्ण
	अगर (bExp == 0) अणु
		अगर (bSig == 0) अणु
			अगर ((aExp | aSig) == 0) अणु
				भग्न_उठाओ(FPSCR_CAUSE_INVALID);
			पूर्ण
			वापस packFloat64(zSign, 0x7FF, 0);
		पूर्ण
		normalizeFloat64Subnormal(bSig, &bExp, &bSig);
	पूर्ण
	अगर (aExp == 0) अणु
		अगर (aSig == 0)
			वापस packFloat64(zSign, 0, 0);
		normalizeFloat64Subnormal(aSig, &aExp, &aSig);
	पूर्ण
	zExp = aExp - bExp + 0x3FD;
	aSig = (aSig | LIT64(0x0010000000000000)) << 10;
	bSig = (bSig | LIT64(0x0010000000000000)) << 11;
	अगर (bSig <= (aSig + aSig)) अणु
		aSig >>= 1;
		++zExp;
	पूर्ण
	zSig = estimateDiv128To64(aSig, 0, bSig);
	अगर ((zSig & 0x1FF) <= 2) अणु
		mul64To128(bSig, zSig, &term0, &term1);
		sub128(aSig, 0, term0, term1, &rem0, &rem1);
		जबतक ((sbits64) rem0 < 0) अणु
			--zSig;
			add128(rem0, rem1, 0, bSig, &rem0, &rem1);
		पूर्ण
		zSig |= (rem1 != 0);
	पूर्ण
	वापस roundAndPackFloat64(zSign, zExp, zSig);

पूर्ण

भग्न32 भग्न32_भाग(भग्न32 a, भग्न32 b)
अणु
	flag aSign, bSign, zSign;
	पूर्णांक16 aExp, bExp, zExp;
	bits32 aSig, bSig;
	uपूर्णांक64_t zSig;

	aSig = extractFloat32Frac(a);
	aExp = extractFloat32Exp(a);
	aSign = extractFloat32Sign(a);
	bSig = extractFloat32Frac(b);
	bExp = extractFloat32Exp(b);
	bSign = extractFloat32Sign(b);
	zSign = aSign ^ bSign;
	अगर (aExp == 0xFF) अणु
		अगर (bExp == 0xFF) अणु
		पूर्ण
		वापस packFloat32(zSign, 0xFF, 0);
	पूर्ण
	अगर (bExp == 0xFF) अणु
		वापस packFloat32(zSign, 0, 0);
	पूर्ण
	अगर (bExp == 0) अणु
		अगर (bSig == 0) अणु
			वापस packFloat32(zSign, 0xFF, 0);
		पूर्ण
		normalizeFloat32Subnormal(bSig, &bExp, &bSig);
	पूर्ण
	अगर (aExp == 0) अणु
		अगर (aSig == 0)
			वापस packFloat32(zSign, 0, 0);
		normalizeFloat32Subnormal(aSig, &aExp, &aSig);
	पूर्ण
	zExp = aExp - bExp + 0x7D;
	aSig = (aSig | 0x00800000) << 7;
	bSig = (bSig | 0x00800000) << 8;
	अगर (bSig <= (aSig + aSig)) अणु
		aSig >>= 1;
		++zExp;
	पूर्ण
	zSig = (((bits64) aSig) << 32);
	करो_भाग(zSig, bSig);

	अगर ((zSig & 0x3F) == 0) अणु
		zSig |= (((bits64) bSig) * zSig != ((bits64) aSig) << 32);
	पूर्ण
	वापस roundAndPackFloat32(zSign, zExp, (bits32)zSig);

पूर्ण

भग्न32 भग्न32_mul(भग्न32 a, भग्न32 b)
अणु
	अक्षर aSign, bSign, zSign;
	पूर्णांक aExp, bExp, zExp;
	अचिन्हित पूर्णांक aSig, bSig;
	अचिन्हित दीर्घ दीर्घ zSig64;
	अचिन्हित पूर्णांक zSig;

	aSig = extractFloat32Frac(a);
	aExp = extractFloat32Exp(a);
	aSign = extractFloat32Sign(a);
	bSig = extractFloat32Frac(b);
	bExp = extractFloat32Exp(b);
	bSign = extractFloat32Sign(b);
	zSign = aSign ^ bSign;
	अगर (aExp == 0) अणु
		अगर (aSig == 0)
			वापस packFloat32(zSign, 0, 0);
		normalizeFloat32Subnormal(aSig, &aExp, &aSig);
	पूर्ण
	अगर (bExp == 0) अणु
		अगर (bSig == 0)
			वापस packFloat32(zSign, 0, 0);
		normalizeFloat32Subnormal(bSig, &bExp, &bSig);
	पूर्ण
	अगर ((bExp == 0xff && bSig == 0) || (aExp == 0xff && aSig == 0))
		वापस roundAndPackFloat32(zSign, 0xff, 0);

	zExp = aExp + bExp - 0x7F;
	aSig = (aSig | 0x00800000) << 7;
	bSig = (bSig | 0x00800000) << 8;
	shअगरt64RightJamming(((अचिन्हित दीर्घ दीर्घ)aSig) * bSig, 32, &zSig64);
	zSig = zSig64;
	अगर (0 <= (चिन्हित पूर्णांक)(zSig << 1)) अणु
		zSig <<= 1;
		--zExp;
	पूर्ण
	वापस roundAndPackFloat32(zSign, zExp, zSig);

पूर्ण

भग्न64 भग्न64_mul(भग्न64 a, भग्न64 b)
अणु
	अक्षर aSign, bSign, zSign;
	पूर्णांक aExp, bExp, zExp;
	अचिन्हित दीर्घ दीर्घ पूर्णांक aSig, bSig, zSig0, zSig1;

	aSig = extractFloat64Frac(a);
	aExp = extractFloat64Exp(a);
	aSign = extractFloat64Sign(a);
	bSig = extractFloat64Frac(b);
	bExp = extractFloat64Exp(b);
	bSign = extractFloat64Sign(b);
	zSign = aSign ^ bSign;

	अगर (aExp == 0) अणु
		अगर (aSig == 0)
			वापस packFloat64(zSign, 0, 0);
		normalizeFloat64Subnormal(aSig, &aExp, &aSig);
	पूर्ण
	अगर (bExp == 0) अणु
		अगर (bSig == 0)
			वापस packFloat64(zSign, 0, 0);
		normalizeFloat64Subnormal(bSig, &bExp, &bSig);
	पूर्ण
	अगर ((aExp == 0x7ff && aSig == 0) || (bExp == 0x7ff && bSig == 0))
		वापस roundAndPackFloat64(zSign, 0x7ff, 0);

	zExp = aExp + bExp - 0x3FF;
	aSig = (aSig | 0x0010000000000000LL) << 10;
	bSig = (bSig | 0x0010000000000000LL) << 11;
	mul64To128(aSig, bSig, &zSig0, &zSig1);
	zSig0 |= (zSig1 != 0);
	अगर (0 <= (चिन्हित दीर्घ दीर्घ पूर्णांक)(zSig0 << 1)) अणु
		zSig0 <<= 1;
		--zExp;
	पूर्ण
	वापस roundAndPackFloat64(zSign, zExp, zSig0);
पूर्ण

/*
 * -------------------------------------------------------------------------------
 *  Returns the result of converting the द्विगुन-precision भग्नing-poपूर्णांक value
 *  `a' to the single-precision भग्नing-poपूर्णांक क्रमmat.  The conversion is
 *  perक्रमmed according to the IEC/IEEE Standard क्रम Binary Floating-poपूर्णांक
 *  Arithmetic.
 *  -------------------------------------------------------------------------------
 *  */
भग्न32 भग्न64_to_भग्न32(भग्न64 a)
अणु
    flag aSign;
    पूर्णांक16 aExp;
    bits64 aSig;
    bits32 zSig;

    aSig = extractFloat64Frac( a );
    aExp = extractFloat64Exp( a );
    aSign = extractFloat64Sign( a );

    shअगरt64RightJamming( aSig, 22, &aSig );
    zSig = aSig;
    अगर ( aExp || zSig ) अणु
        zSig |= 0x40000000;
        aExp -= 0x381;
    पूर्ण
    वापस roundAndPackFloat32(aSign, aExp, zSig);
पूर्ण
