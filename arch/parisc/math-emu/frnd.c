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
 *  Purpose:
 *	Single Floating-poपूर्णांक Round to Integer
 *	Double Floating-poपूर्णांक Round to Integer
 *	Quad Floating-poपूर्णांक Round to Integer (वापसs unimplemented)
 *
 *  External Interfaces:
 *	dbl_frnd(srcptr,nullptr,dstptr,status)
 *	sgl_frnd(srcptr,nullptr,dstptr,status)
 *
 * END_DESC
*/


#समावेश "float.h"
#समावेश "sgl_float.h"
#समावेश "dbl_float.h"
#समावेश "cnv_float.h"

/*
 *  Single Floating-poपूर्णांक Round to Integer
 */

/*ARGSUSED*/
पूर्णांक
sgl_frnd(sgl_भग्नing_poपूर्णांक *srcptr,
	अचिन्हित पूर्णांक *nullptr,
	sgl_भग्नing_poपूर्णांक *dstptr,
	अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर अचिन्हित पूर्णांक src, result;
	रेजिस्टर पूर्णांक src_exponent;
	रेजिस्टर boolean inexact = FALSE;

	src = *srcptr;
        /*
         * check source opeअक्रम क्रम NaN or infinity
         */
        अगर ((src_exponent = Sgl_exponent(src)) == SGL_अनन्त_EXPONENT) अणु
                /*
                 * is संकेतing NaN?
                 */
                अगर (Sgl_isone_संकेतing(src)) अणु
                        /* trap अगर INVALIDTRAP enabled */
                        अगर (Is_invalidtrap_enabled()) वापस(INVALIDEXCEPTION);
                        /* make NaN quiet */
                        Set_invalidflag();
                        Sgl_set_quiet(src);
                पूर्ण
                /*
                 * वापस quiet NaN or infinity
                 */
                *dstptr = src;
                वापस(NOEXCEPTION);
        पूर्ण
	/* 
	 * Need to round?
	 */
	अगर ((src_exponent -= SGL_BIAS) >= SGL_P - 1) अणु
		*dstptr = src;
		वापस(NOEXCEPTION);
	पूर्ण
	/*
	 * Generate result
	 */
	अगर (src_exponent >= 0) अणु
		Sgl_clear_exponent_set_hidden(src);
		result = src;
		Sgl_rightshअगरt(result,(SGL_P-1) - (src_exponent));
		/* check क्रम inexact */
		अगर (Sgl_isinexact_to_fix(src,src_exponent)) अणु
			inexact = TRUE;
			/*  round result  */
			चयन (Rounding_mode()) अणु
			हाल ROUNDPLUS:
			     अगर (Sgl_iszero_sign(src)) Sgl_increment(result);
			     अवरोध;
			हाल ROUNDMINUS:
			     अगर (Sgl_isone_sign(src)) Sgl_increment(result);
			     अवरोध;
			हाल ROUNDNEAREST:
			     अगर (Sgl_isone_roundbit(src,src_exponent))
			        अगर (Sgl_isone_stickybit(src,src_exponent) 
				|| (Sgl_isone_lowmantissa(result))) 
					Sgl_increment(result);
			पूर्ण 
		पूर्ण
		Sgl_leftshअगरt(result,(SGL_P-1) - (src_exponent));
		अगर (Sgl_isone_hiddenoverflow(result)) 
			Sgl_set_exponent(result,src_exponent + (SGL_BIAS+1));
		अन्यथा Sgl_set_exponent(result,src_exponent + SGL_BIAS);
	पूर्ण
	अन्यथा अणु
		result = src;  		/* set sign */
		Sgl_setzero_exponenपंचांगantissa(result);
		/* check क्रम inexact */
		अगर (Sgl_isnotzero_exponenपंचांगantissa(src)) अणु
			inexact = TRUE;
			/*  round result  */
			चयन (Rounding_mode()) अणु
			हाल ROUNDPLUS:
			     अगर (Sgl_iszero_sign(src)) 
				Sgl_set_exponent(result,SGL_BIAS);
			     अवरोध;
			हाल ROUNDMINUS:
			     अगर (Sgl_isone_sign(src)) 
				Sgl_set_exponent(result,SGL_BIAS);
			     अवरोध;
			हाल ROUNDNEAREST:
			     अगर (src_exponent == -1)
			        अगर (Sgl_isnotzero_mantissa(src))
				   Sgl_set_exponent(result,SGL_BIAS);
			पूर्ण 
		पूर्ण
	पूर्ण
	*dstptr = result;
	अगर (inexact) अणु
		अगर (Is_inexacttrap_enabled()) वापस(INEXACTEXCEPTION);
		अन्यथा Set_inexactflag();
	पूर्ण
	वापस(NOEXCEPTION);
पूर्ण 

/*
 *  Double Floating-poपूर्णांक Round to Integer
 */

/*ARGSUSED*/
पूर्णांक
dbl_frnd(
	dbl_भग्नing_poपूर्णांक *srcptr,
	अचिन्हित पूर्णांक *nullptr,
	dbl_भग्नing_poपूर्णांक *dstptr,
	अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर अचिन्हित पूर्णांक srcp1, srcp2, resultp1, resultp2;
	रेजिस्टर पूर्णांक src_exponent;
	रेजिस्टर boolean inexact = FALSE;

	Dbl_copyfromptr(srcptr,srcp1,srcp2);
        /*
         * check source opeअक्रम क्रम NaN or infinity
         */
        अगर ((src_exponent = Dbl_exponent(srcp1)) == DBL_अनन्त_EXPONENT) अणु
                /*
                 * is संकेतing NaN?
                 */
                अगर (Dbl_isone_संकेतing(srcp1)) अणु
                        /* trap अगर INVALIDTRAP enabled */
                        अगर (Is_invalidtrap_enabled()) वापस(INVALIDEXCEPTION);
                        /* make NaN quiet */
                        Set_invalidflag();
                        Dbl_set_quiet(srcp1);
                पूर्ण
                /*
                 * वापस quiet NaN or infinity
                 */
                Dbl_copytoptr(srcp1,srcp2,dstptr);
                वापस(NOEXCEPTION);
        पूर्ण
	/* 
	 * Need to round?
	 */
	अगर ((src_exponent -= DBL_BIAS) >= DBL_P - 1) अणु
		Dbl_copytoptr(srcp1,srcp2,dstptr);
		वापस(NOEXCEPTION);
	पूर्ण
	/*
	 * Generate result
	 */
	अगर (src_exponent >= 0) अणु
		Dbl_clear_exponent_set_hidden(srcp1);
		resultp1 = srcp1;
		resultp2 = srcp2;
		Dbl_rightshअगरt(resultp1,resultp2,(DBL_P-1) - (src_exponent));
		/* check क्रम inexact */
		अगर (Dbl_isinexact_to_fix(srcp1,srcp2,src_exponent)) अणु
			inexact = TRUE;
			/*  round result  */
			चयन (Rounding_mode()) अणु
			हाल ROUNDPLUS:
			     अगर (Dbl_iszero_sign(srcp1)) 
				Dbl_increment(resultp1,resultp2);
			     अवरोध;
			हाल ROUNDMINUS:
			     अगर (Dbl_isone_sign(srcp1)) 
				Dbl_increment(resultp1,resultp2);
			     अवरोध;
			हाल ROUNDNEAREST:
			     अगर (Dbl_isone_roundbit(srcp1,srcp2,src_exponent))
			      अगर (Dbl_isone_stickybit(srcp1,srcp2,src_exponent) 
				  || (Dbl_isone_lowmantissap2(resultp2))) 
					Dbl_increment(resultp1,resultp2);
			पूर्ण 
		पूर्ण
		Dbl_leftshअगरt(resultp1,resultp2,(DBL_P-1) - (src_exponent));
		अगर (Dbl_isone_hiddenoverflow(resultp1))
			Dbl_set_exponent(resultp1,src_exponent + (DBL_BIAS+1));
		अन्यथा Dbl_set_exponent(resultp1,src_exponent + DBL_BIAS);
	पूर्ण
	अन्यथा अणु
		resultp1 = srcp1;  /* set sign */
		Dbl_setzero_exponenपंचांगantissa(resultp1,resultp2);
		/* check क्रम inexact */
		अगर (Dbl_isnotzero_exponenपंचांगantissa(srcp1,srcp2)) अणु
			inexact = TRUE;
			/*  round result  */
			चयन (Rounding_mode()) अणु
			हाल ROUNDPLUS:
			     अगर (Dbl_iszero_sign(srcp1)) 
				Dbl_set_exponent(resultp1,DBL_BIAS);
			     अवरोध;
			हाल ROUNDMINUS:
			     अगर (Dbl_isone_sign(srcp1)) 
				Dbl_set_exponent(resultp1,DBL_BIAS);
			     अवरोध;
			हाल ROUNDNEAREST:
			     अगर (src_exponent == -1)
			        अगर (Dbl_isnotzero_mantissa(srcp1,srcp2))
				   Dbl_set_exponent(resultp1,DBL_BIAS);
			पूर्ण 
		पूर्ण
	पूर्ण
	Dbl_copytoptr(resultp1,resultp2,dstptr);
	अगर (inexact) अणु
		अगर (Is_inexacttrap_enabled()) वापस(INEXACTEXCEPTION);
		अन्यथा Set_inexactflag();
	पूर्ण
	वापस(NOEXCEPTION);
पूर्ण
