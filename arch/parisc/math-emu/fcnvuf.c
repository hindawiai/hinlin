<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux/PA-RISC Project (http://www.parisc-linux.org/)
 *
 * Floating-poपूर्णांक emulation code
 *  Copyright (C) 2001 Hewlett-Packard (Paul Bame) <bame@debian.org>
 */
/*
 * BEGIN_DESC
 *
 *  File:
 *	@(#)	pa/spmath/fcnvuf.c		$Revision: 1.1 $
 *
 *  Purpose:
 *	Fixed poपूर्णांक to Floating-poपूर्णांक Converts
 *
 *  External Interfaces:
 *	dbl_to_dbl_fcnvuf(srcptr,nullptr,dstptr,status)
 *	dbl_to_sgl_fcnvuf(srcptr,nullptr,dstptr,status)
 *	sgl_to_dbl_fcnvuf(srcptr,nullptr,dstptr,status)
 *	sgl_to_sgl_fcnvuf(srcptr,nullptr,dstptr,status)
 *
 *  Internal Interfaces:
 *
 *  Theory:
 *	<<please update with a overview of the operation of this file>>
 *
 * END_DESC
*/


#समावेश "float.h"
#समावेश "sgl_float.h"
#समावेश "dbl_float.h"
#समावेश "cnv_float.h"

/************************************************************************
 *  Fixed poपूर्णांक to Floating-poपूर्णांक Converts				*
 ************************************************************************/

/*
 *  Convert Single Unचिन्हित Fixed to Single Floating-poपूर्णांक क्रमmat
 */

पूर्णांक
sgl_to_sgl_fcnvuf(
			अचिन्हित पूर्णांक *srcptr,
			अचिन्हित पूर्णांक *nullptr,
			sgl_भग्नing_poपूर्णांक *dstptr,
			अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर अचिन्हित पूर्णांक src, result = 0;
	रेजिस्टर पूर्णांक dst_exponent;

	src = *srcptr;

	/* Check क्रम zero */ 
	अगर (src == 0) अणु 
	       	Sgl_setzero(result); 
		*dstptr = result;
	       	वापस(NOEXCEPTION); 
	पूर्ण 
	/*
	 * Generate exponent and normalized mantissa
	 */
	dst_exponent = 16;    /* initialize क्रम normalization */
	/*
	 * Check word क्रम most signअगरicant bit set.  Returns
	 * a value in dst_exponent indicating the bit position,
	 * between -1 and 30.
	 */
	Find_ms_one_bit(src,dst_exponent);
	/*  left justअगरy source, with msb at bit position 0  */
	src <<= dst_exponent+1;
	Sgl_set_mantissa(result, src >> SGL_EXP_LENGTH);
	Sgl_set_exponent(result, 30+SGL_BIAS - dst_exponent);

	/* check क्रम inexact */
	अगर (Suपूर्णांक_isinexact_to_sgl(src)) अणु
		चयन (Rounding_mode()) अणु
			हाल ROUNDPLUS: 
				Sgl_increment(result);
				अवरोध;
			हाल ROUNDMINUS: /* never negative */
				अवरोध;
			हाल ROUNDNEAREST:
				Sgl_roundnearest_from_suपूर्णांक(src,result);
				अवरोध;
		पूर्ण
		अगर (Is_inexacttrap_enabled()) अणु
			*dstptr = result;
			वापस(INEXACTEXCEPTION);
		पूर्ण
		अन्यथा Set_inexactflag();
	पूर्ण
	*dstptr = result;
	वापस(NOEXCEPTION);
पूर्ण

/*
 *  Single Unचिन्हित Fixed to Double Floating-poपूर्णांक 
 */

पूर्णांक
sgl_to_dbl_fcnvuf(
			अचिन्हित पूर्णांक *srcptr,
			अचिन्हित पूर्णांक *nullptr,
			dbl_भग्नing_poपूर्णांक *dstptr,
			अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर पूर्णांक dst_exponent;
	रेजिस्टर अचिन्हित पूर्णांक src, resultp1 = 0, resultp2 = 0;

	src = *srcptr;

	/* Check क्रम zero */
	अगर (src == 0) अणु
	       	Dbl_setzero(resultp1,resultp2);
	       	Dbl_copytoptr(resultp1,resultp2,dstptr);
	       	वापस(NOEXCEPTION);
	पूर्ण
	/*
	 * Generate exponent and normalized mantissa
	 */
	dst_exponent = 16;    /* initialize क्रम normalization */
	/*
	 * Check word क्रम most signअगरicant bit set.  Returns
	 * a value in dst_exponent indicating the bit position,
	 * between -1 and 30.
	 */
	Find_ms_one_bit(src,dst_exponent);
	/*  left justअगरy source, with msb at bit position 0  */
	src <<= dst_exponent+1;
	Dbl_set_mantissap1(resultp1, src >> DBL_EXP_LENGTH);
	Dbl_set_mantissap2(resultp2, src << (32-DBL_EXP_LENGTH));
	Dbl_set_exponent(resultp1, (30+DBL_BIAS) - dst_exponent);
	Dbl_copytoptr(resultp1,resultp2,dstptr);
	वापस(NOEXCEPTION);
पूर्ण

/*
 *  Double Unचिन्हित Fixed to Single Floating-poपूर्णांक 
 */

पूर्णांक
dbl_to_sgl_fcnvuf(
			dbl_अचिन्हित *srcptr,
			अचिन्हित पूर्णांक *nullptr,
			sgl_भग्नing_poपूर्णांक *dstptr,
			अचिन्हित पूर्णांक *status)
अणु
	पूर्णांक dst_exponent;
	अचिन्हित पूर्णांक srcp1, srcp2, result = 0;

	Duपूर्णांक_copyfromptr(srcptr,srcp1,srcp2);

	/* Check क्रम zero */
	अगर (srcp1 == 0 && srcp2 == 0) अणु
	       	Sgl_setzero(result);
	       	*dstptr = result;
	       	वापस(NOEXCEPTION);
	पूर्ण
	/*
	 * Generate exponent and normalized mantissa
	 */
	dst_exponent = 16;    /* initialize क्रम normalization */
	अगर (srcp1 == 0) अणु
		/*
		 * Check word क्रम most signअगरicant bit set.  Returns
		 * a value in dst_exponent indicating the bit position,
		 * between -1 and 30.
		 */
		Find_ms_one_bit(srcp2,dst_exponent);
		/*  left justअगरy source, with msb at bit position 0  */
		srcp1 = srcp2 << dst_exponent+1;    
		srcp2 = 0;
		/*
		 *  since msb set is in second word, need to 
		 *  adjust bit position count
		 */
		dst_exponent += 32;
	पूर्ण
	अन्यथा अणु
		/*
		 * Check word क्रम most signअगरicant bit set.  Returns
		 * a value in dst_exponent indicating the bit position,
		 * between -1 and 30.
		 *
		 */
		Find_ms_one_bit(srcp1,dst_exponent);
		/*  left justअगरy source, with msb at bit position 0  */
		अगर (dst_exponent >= 0) अणु
			Variable_shअगरt_द्विगुन(srcp1,srcp2,(31-dst_exponent),
			 srcp1); 
			srcp2 <<= dst_exponent+1;
		पूर्ण
	पूर्ण
	Sgl_set_mantissa(result, srcp1 >> SGL_EXP_LENGTH);
	Sgl_set_exponent(result, (62+SGL_BIAS) - dst_exponent);

	/* check क्रम inexact */
	अगर (Duपूर्णांक_isinexact_to_sgl(srcp1,srcp2)) अणु
		चयन (Rounding_mode()) अणु
			हाल ROUNDPLUS: 
				Sgl_increment(result);
				अवरोध;
			हाल ROUNDMINUS: /* never negative */
				अवरोध;
			हाल ROUNDNEAREST:
				Sgl_roundnearest_from_duपूर्णांक(srcp1,srcp2,result);
				अवरोध;
		पूर्ण
		अगर (Is_inexacttrap_enabled()) अणु
			*dstptr = result;
			वापस(INEXACTEXCEPTION);
		पूर्ण
		अन्यथा Set_inexactflag();
	पूर्ण
	*dstptr = result;
	वापस(NOEXCEPTION);
पूर्ण

/*
 *  Double Unचिन्हित Fixed to Double Floating-poपूर्णांक 
 */

पूर्णांक
dbl_to_dbl_fcnvuf(
		    dbl_अचिन्हित *srcptr,
		    अचिन्हित पूर्णांक *nullptr,
		    dbl_भग्नing_poपूर्णांक *dstptr,
		    अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर पूर्णांक dst_exponent;
	रेजिस्टर अचिन्हित पूर्णांक srcp1, srcp2, resultp1 = 0, resultp2 = 0;

	Duपूर्णांक_copyfromptr(srcptr,srcp1,srcp2);

	/* Check क्रम zero */
	अगर (srcp1 == 0 && srcp2 ==0) अणु
	       	Dbl_setzero(resultp1,resultp2);
	       	Dbl_copytoptr(resultp1,resultp2,dstptr);
	       	वापस(NOEXCEPTION);
	पूर्ण
	/*
	 * Generate exponent and normalized mantissa
	 */
	dst_exponent = 16;    /* initialize क्रम normalization */
	अगर (srcp1 == 0) अणु
		/*
		 * Check word क्रम most signअगरicant bit set.  Returns
		 * a value in dst_exponent indicating the bit position,
		 * between -1 and 30.
		 */
		Find_ms_one_bit(srcp2,dst_exponent);
		/*  left justअगरy source, with msb at bit position 0  */
		srcp1 = srcp2 << dst_exponent+1;
		srcp2 = 0;
		/*
		 *  since msb set is in second word, need to 
		 *  adjust bit position count
		 */
		dst_exponent += 32;
	पूर्ण
	अन्यथा अणु
		/*
		 * Check word क्रम most signअगरicant bit set.  Returns
		 * a value in dst_exponent indicating the bit position,
		 * between -1 and 30.
		 */
		Find_ms_one_bit(srcp1,dst_exponent);
		/*  left justअगरy source, with msb at bit position 0  */
		अगर (dst_exponent >= 0) अणु
			Variable_shअगरt_द्विगुन(srcp1,srcp2,(31-dst_exponent),
			 srcp1); 
			srcp2 <<= dst_exponent+1;
		पूर्ण
	पूर्ण
	Dbl_set_mantissap1(resultp1, srcp1 >> DBL_EXP_LENGTH);
	Shअगरtद्विगुन(srcp1,srcp2,DBL_EXP_LENGTH,resultp2);
	Dbl_set_exponent(resultp1, (62+DBL_BIAS) - dst_exponent);

	/* check क्रम inexact */
	अगर (Duपूर्णांक_isinexact_to_dbl(srcp2)) अणु
		चयन (Rounding_mode()) अणु
			हाल ROUNDPLUS: 
				Dbl_increment(resultp1,resultp2);
				अवरोध;
			हाल ROUNDMINUS: /* never negative */
				अवरोध;
			हाल ROUNDNEAREST:
				Dbl_roundnearest_from_duपूर्णांक(srcp2,resultp1,
				resultp2);
				अवरोध;
		पूर्ण
		अगर (Is_inexacttrap_enabled()) अणु
			Dbl_copytoptr(resultp1,resultp2,dstptr);
			वापस(INEXACTEXCEPTION);
		पूर्ण
		अन्यथा Set_inexactflag();
	पूर्ण
	Dbl_copytoptr(resultp1,resultp2,dstptr);
	वापस(NOEXCEPTION);
पूर्ण

