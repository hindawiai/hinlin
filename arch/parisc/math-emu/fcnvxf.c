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
 *	@(#)	pa/spmath/fcnvxf.c		$Revision: 1.1 $
 *
 *  Purpose:
 *	Single Fixed-poपूर्णांक to Single Floating-poपूर्णांक
 *	Single Fixed-poपूर्णांक to Double Floating-poपूर्णांक 
 *	Double Fixed-poपूर्णांक to Single Floating-poपूर्णांक 
 *	Double Fixed-poपूर्णांक to Double Floating-poपूर्णांक 
 *
 *  External Interfaces:
 *	dbl_to_dbl_fcnvxf(srcptr,nullptr,dstptr,status)
 *	dbl_to_sgl_fcnvxf(srcptr,nullptr,dstptr,status)
 *	sgl_to_dbl_fcnvxf(srcptr,nullptr,dstptr,status)
 *	sgl_to_sgl_fcnvxf(srcptr,nullptr,dstptr,status)
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

/*
 *  Convert single fixed-poपूर्णांक to single भग्नing-poपूर्णांक क्रमmat
 */

पूर्णांक
sgl_to_sgl_fcnvxf(
		    पूर्णांक *srcptr,
		    अचिन्हित पूर्णांक *nullptr,
		    sgl_भग्नing_poपूर्णांक *dstptr,
		    अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर पूर्णांक src, dst_exponent;
	रेजिस्टर अचिन्हित पूर्णांक result = 0;

	src = *srcptr;
	/* 
	 * set sign bit of result and get magnitude of source 
	 */
	अगर (src < 0) अणु
		Sgl_setone_sign(result);  
		Int_negate(src);
	पूर्ण
	अन्यथा अणु
		Sgl_setzero_sign(result);
        	/* Check क्रम zero */ 
        	अगर (src == 0) अणु 
                	Sgl_setzero(result); 
			*dstptr = result;
                	वापस(NOEXCEPTION); 
        	पूर्ण 
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
	/*  left justअगरy source, with msb at bit position 1  */
	अगर (dst_exponent >= 0) src <<= dst_exponent;
	अन्यथा src = 1 << 30;
	Sgl_set_mantissa(result, src >> (SGL_EXP_LENGTH-1));
	Sgl_set_exponent(result, 30+SGL_BIAS - dst_exponent);

	/* check क्रम inexact */
	अगर (Int_isinexact_to_sgl(src)) अणु
		चयन (Rounding_mode()) अणु
			हाल ROUNDPLUS: 
				अगर (Sgl_iszero_sign(result)) 
					Sgl_increment(result);
				अवरोध;
			हाल ROUNDMINUS: 
				अगर (Sgl_isone_sign(result)) 
					Sgl_increment(result);
				अवरोध;
			हाल ROUNDNEAREST:
				Sgl_roundnearest_from_पूर्णांक(src,result);
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
 *  Single Fixed-poपूर्णांक to Double Floating-poपूर्णांक 
 */

पूर्णांक
sgl_to_dbl_fcnvxf(
		    पूर्णांक *srcptr,
		    अचिन्हित पूर्णांक *nullptr,
		    dbl_भग्नing_poपूर्णांक *dstptr,
		    अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर पूर्णांक src, dst_exponent;
	रेजिस्टर अचिन्हित पूर्णांक resultp1 = 0, resultp2 = 0;

	src = *srcptr;
	/* 
	 * set sign bit of result and get magnitude of source 
	 */
	अगर (src < 0) अणु
		Dbl_setone_sign(resultp1);  
		Int_negate(src);
	पूर्ण
	अन्यथा अणु
		Dbl_setzero_sign(resultp1);
        	/* Check क्रम zero */
        	अगर (src == 0) अणु
                	Dbl_setzero(resultp1,resultp2);
                	Dbl_copytoptr(resultp1,resultp2,dstptr);
                	वापस(NOEXCEPTION);
        	पूर्ण
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
	/*  left justअगरy source, with msb at bit position 1  */
	अगर (dst_exponent >= 0) src <<= dst_exponent;
	अन्यथा src = 1 << 30;
	Dbl_set_mantissap1(resultp1, src >> DBL_EXP_LENGTH - 1);
	Dbl_set_mantissap2(resultp2, src << (33-DBL_EXP_LENGTH));
	Dbl_set_exponent(resultp1, (30+DBL_BIAS) - dst_exponent);
	Dbl_copytoptr(resultp1,resultp2,dstptr);
	वापस(NOEXCEPTION);
पूर्ण

/*
 *  Double Fixed-poपूर्णांक to Single Floating-poपूर्णांक 
 */

पूर्णांक
dbl_to_sgl_fcnvxf(
			dbl_पूर्णांकeger *srcptr,
			अचिन्हित पूर्णांक *nullptr,
			sgl_भग्नing_poपूर्णांक *dstptr,
			अचिन्हित पूर्णांक *status)
अणु
	पूर्णांक dst_exponent, srcp1;
	अचिन्हित पूर्णांक result = 0, srcp2;

	Dपूर्णांक_copyfromptr(srcptr,srcp1,srcp2);
	/* 
	 * set sign bit of result and get magnitude of source 
	 */
	अगर (srcp1 < 0) अणु
		Sgl_setone_sign(result);  
		Dपूर्णांक_negate(srcp1,srcp2);
	पूर्ण
	अन्यथा अणु
		Sgl_setzero_sign(result);
        	/* Check क्रम zero */
        	अगर (srcp1 == 0 && srcp2 == 0) अणु
                	Sgl_setzero(result);
                	*dstptr = result;
                	वापस(NOEXCEPTION);
		पूर्ण
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
		/*  left justअगरy source, with msb at bit position 1  */
		अगर (dst_exponent >= 0) अणु
			srcp1 = srcp2 << dst_exponent;    
			srcp2 = 0;
		पूर्ण
		अन्यथा अणु
			srcp1 = srcp2 >> 1;
			srcp2 <<= 31; 
		पूर्ण
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
		/*  left justअगरy source, with msb at bit position 1  */
		अगर (dst_exponent > 0) अणु
			Variable_shअगरt_द्विगुन(srcp1,srcp2,(32-dst_exponent),
			 srcp1); 
			srcp2 <<= dst_exponent;
		पूर्ण
		/*
		 * If dst_exponent = 0, we करोn't need to shअगरt anything.
		 * If dst_exponent = -1, src = - 2**63 so we won't need to 
		 * shअगरt srcp2.
		 */
		अन्यथा srcp1 >>= -(dst_exponent);
	पूर्ण
	Sgl_set_mantissa(result, srcp1 >> SGL_EXP_LENGTH - 1);
	Sgl_set_exponent(result, (62+SGL_BIAS) - dst_exponent);

	/* check क्रम inexact */
	अगर (Dपूर्णांक_isinexact_to_sgl(srcp1,srcp2)) अणु
		चयन (Rounding_mode()) अणु
			हाल ROUNDPLUS: 
				अगर (Sgl_iszero_sign(result)) 
					Sgl_increment(result);
				अवरोध;
			हाल ROUNDMINUS: 
				अगर (Sgl_isone_sign(result)) 
					Sgl_increment(result);
				अवरोध;
			हाल ROUNDNEAREST:
				Sgl_roundnearest_from_dपूर्णांक(srcp1,srcp2,result);
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
 *  Double Fixed-poपूर्णांक to Double Floating-poपूर्णांक 
 */

पूर्णांक
dbl_to_dbl_fcnvxf(
		    dbl_पूर्णांकeger *srcptr,
		    अचिन्हित पूर्णांक *nullptr,
		    dbl_भग्नing_poपूर्णांक *dstptr,
		    अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर पूर्णांक srcp1, dst_exponent;
	रेजिस्टर अचिन्हित पूर्णांक srcp2, resultp1 = 0, resultp2 = 0;

	Dपूर्णांक_copyfromptr(srcptr,srcp1,srcp2);
	/* 
	 * set sign bit of result and get magnitude of source 
	 */
	अगर (srcp1 < 0) अणु
		Dbl_setone_sign(resultp1);
		Dपूर्णांक_negate(srcp1,srcp2);
	पूर्ण
	अन्यथा अणु
		Dbl_setzero_sign(resultp1);
        	/* Check क्रम zero */
        	अगर (srcp1 == 0 && srcp2 ==0) अणु
                	Dbl_setzero(resultp1,resultp2);
                	Dbl_copytoptr(resultp1,resultp2,dstptr);
                	वापस(NOEXCEPTION);
		पूर्ण
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
		/*  left justअगरy source, with msb at bit position 1  */
		अगर (dst_exponent >= 0) अणु
			srcp1 = srcp2 << dst_exponent;    
			srcp2 = 0;
		पूर्ण
		अन्यथा अणु
			srcp1 = srcp2 >> 1;
			srcp2 <<= 31;
		पूर्ण
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
		/*  left justअगरy source, with msb at bit position 1  */
		अगर (dst_exponent > 0) अणु
			Variable_shअगरt_द्विगुन(srcp1,srcp2,(32-dst_exponent),
			 srcp1); 
			srcp2 <<= dst_exponent;
		पूर्ण
		/*
		 * If dst_exponent = 0, we करोn't need to shअगरt anything.
		 * If dst_exponent = -1, src = - 2**63 so we won't need to 
		 * shअगरt srcp2.
		 */
		अन्यथा srcp1 >>= -(dst_exponent);
	पूर्ण
	Dbl_set_mantissap1(resultp1, srcp1 >> (DBL_EXP_LENGTH-1));
	Shअगरtद्विगुन(srcp1,srcp2,DBL_EXP_LENGTH-1,resultp2);
	Dbl_set_exponent(resultp1, (62+DBL_BIAS) - dst_exponent);

	/* check क्रम inexact */
	अगर (Dपूर्णांक_isinexact_to_dbl(srcp2)) अणु
		चयन (Rounding_mode()) अणु
			हाल ROUNDPLUS: 
				अगर (Dbl_iszero_sign(resultp1)) अणु
					Dbl_increment(resultp1,resultp2);
				पूर्ण
				अवरोध;
			हाल ROUNDMINUS: 
				अगर (Dbl_isone_sign(resultp1)) अणु
					Dbl_increment(resultp1,resultp2);
				पूर्ण
				अवरोध;
			हाल ROUNDNEAREST:
				Dbl_roundnearest_from_dपूर्णांक(srcp2,resultp1,
				resultp2);
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
