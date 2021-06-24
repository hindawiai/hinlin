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
 *	@(#)	pa/spmath/fcnvfx.c		$Revision: 1.1 $
 *
 *  Purpose:
 *	Single Floating-poपूर्णांक to Single Fixed-poपूर्णांक
 *	Single Floating-poपूर्णांक to Double Fixed-poपूर्णांक 
 *	Double Floating-poपूर्णांक to Single Fixed-poपूर्णांक 
 *	Double Floating-poपूर्णांक to Double Fixed-poपूर्णांक 
 *
 *  External Interfaces:
 *	dbl_to_dbl_fcnvfx(srcptr,nullptr,dstptr,status)
 *	dbl_to_sgl_fcnvfx(srcptr,nullptr,dstptr,status)
 *	sgl_to_dbl_fcnvfx(srcptr,nullptr,dstptr,status)
 *	sgl_to_sgl_fcnvfx(srcptr,nullptr,dstptr,status)
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
 *  Single Floating-poपूर्णांक to Single Fixed-poपूर्णांक 
 */
/*ARGSUSED*/
पूर्णांक
sgl_to_sgl_fcnvfx(
		    sgl_भग्नing_poपूर्णांक *srcptr,
		    sgl_भग्नing_poपूर्णांक *nullptr,
		    पूर्णांक *dstptr,
		    sgl_भग्नing_poपूर्णांक *status)
अणु
	रेजिस्टर अचिन्हित पूर्णांक src, temp;
	रेजिस्टर पूर्णांक src_exponent, result;
	रेजिस्टर boolean inexact = FALSE;

	src = *srcptr;
	src_exponent = Sgl_exponent(src) - SGL_BIAS;

	/* 
	 * Test क्रम overflow
	 */
	अगर (src_exponent > SGL_FX_MAX_EXP) अणु
		/* check क्रम MININT */
		अगर ((src_exponent > SGL_FX_MAX_EXP + 1) || 
		Sgl_isnotzero_mantissa(src) || Sgl_iszero_sign(src)) अणु
                        अगर (Sgl_iszero_sign(src)) result = 0x7fffffff;
                        अन्यथा result = 0x80000000; 

	                अगर (Is_invalidtrap_enabled()) अणु
                            वापस(INVALIDEXCEPTION);
                        पूर्ण
                        Set_invalidflag();
			*dstptr = result;
			वापस(NOEXCEPTION);
       		पूर्ण
	पूर्ण
	/*
	 * Generate result
	 */
	अगर (src_exponent >= 0) अणु
		temp = src;
		Sgl_clear_signexponent_set_hidden(temp);
		Int_from_sgl_mantissa(temp,src_exponent);
		अगर (Sgl_isone_sign(src))  result = -Sgl_all(temp);
		अन्यथा result = Sgl_all(temp);

		/* check क्रम inexact */
		अगर (Sgl_isinexact_to_fix(src,src_exponent)) अणु
			inexact = TRUE;
			/*  round result  */
			चयन (Rounding_mode()) अणु
			हाल ROUNDPLUS:
			     अगर (Sgl_iszero_sign(src)) result++;
			     अवरोध;
			हाल ROUNDMINUS:
			     अगर (Sgl_isone_sign(src)) result--;
			     अवरोध;
			हाल ROUNDNEAREST:
			     अगर (Sgl_isone_roundbit(src,src_exponent)) अणु
			        अगर (Sgl_isone_stickybit(src,src_exponent) 
				|| (Sgl_isone_lowmantissa(temp)))
			           अगर (Sgl_iszero_sign(src)) result++;
			           अन्यथा result--;
			     पूर्ण
			पूर्ण 
		पूर्ण
	पूर्ण
	अन्यथा अणु
		result = 0;

		/* check क्रम inexact */
		अगर (Sgl_isnotzero_exponenपंचांगantissa(src)) अणु
			inexact = TRUE;
			/*  round result  */
			चयन (Rounding_mode()) अणु
			हाल ROUNDPLUS:
			     अगर (Sgl_iszero_sign(src)) result++;
			     अवरोध;
			हाल ROUNDMINUS:
			     अगर (Sgl_isone_sign(src)) result--;
			     अवरोध;
			हाल ROUNDNEAREST:
			     अगर (src_exponent == -1)
			        अगर (Sgl_isnotzero_mantissa(src))
			           अगर (Sgl_iszero_sign(src)) result++;
			           अन्यथा result--;
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
 *  Single Floating-poपूर्णांक to Double Fixed-poपूर्णांक 
 */
/*ARGSUSED*/
पूर्णांक
sgl_to_dbl_fcnvfx(
		sgl_भग्नing_poपूर्णांक *srcptr,
		अचिन्हित पूर्णांक *nullptr,
		dbl_पूर्णांकeger *dstptr,
		अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर पूर्णांक src_exponent, resultp1;
	रेजिस्टर अचिन्हित पूर्णांक src, temp, resultp2;
	रेजिस्टर boolean inexact = FALSE;

	src = *srcptr;
	src_exponent = Sgl_exponent(src) - SGL_BIAS;

	/* 
	 * Test क्रम overflow
	 */
	अगर (src_exponent > DBL_FX_MAX_EXP) अणु
		/* check क्रम MININT */
		अगर ((src_exponent > DBL_FX_MAX_EXP + 1) || 
		Sgl_isnotzero_mantissa(src) || Sgl_iszero_sign(src)) अणु
                        अगर (Sgl_iszero_sign(src)) अणु
                              resultp1 = 0x7fffffff;
			      resultp2 = 0xffffffff;
			पूर्ण
                        अन्यथा अणु
			    resultp1 = 0x80000000; 
			    resultp2 = 0;
			पूर्ण
	                अगर (Is_invalidtrap_enabled()) अणु
                            वापस(INVALIDEXCEPTION);
                        पूर्ण
                        Set_invalidflag();
    		        Dपूर्णांक_copytoptr(resultp1,resultp2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
		Dपूर्णांक_set_minपूर्णांक(resultp1,resultp2);
		Dपूर्णांक_copytoptr(resultp1,resultp2,dstptr);
		वापस(NOEXCEPTION);
	पूर्ण
	/*
	 * Generate result
	 */
	अगर (src_exponent >= 0) अणु
		temp = src;
		Sgl_clear_signexponent_set_hidden(temp);
		Dपूर्णांक_from_sgl_mantissa(temp,src_exponent,resultp1,resultp2);
		अगर (Sgl_isone_sign(src)) अणु
			Dपूर्णांक_setone_sign(resultp1,resultp2);
		पूर्ण

		/* check क्रम inexact */
		अगर (Sgl_isinexact_to_fix(src,src_exponent)) अणु
			inexact = TRUE;
                        /*  round result  */
                        चयन (Rounding_mode()) अणु
                        हाल ROUNDPLUS:
                             अगर (Sgl_iszero_sign(src)) अणु
				Dपूर्णांक_increment(resultp1,resultp2);
			     पूर्ण
                             अवरोध;
                        हाल ROUNDMINUS:
                             अगर (Sgl_isone_sign(src)) अणु
				Dपूर्णांक_decrement(resultp1,resultp2);
			     पूर्ण
                             अवरोध;
                        हाल ROUNDNEAREST:
                             अगर (Sgl_isone_roundbit(src,src_exponent))
                                अगर (Sgl_isone_stickybit(src,src_exponent) || 
				(Dपूर्णांक_isone_lowp2(resultp2)))
				   अगर (Sgl_iszero_sign(src)) अणु
				      Dपूर्णांक_increment(resultp1,resultp2);
				   पूर्ण
                                   अन्यथा अणु
				      Dपूर्णांक_decrement(resultp1,resultp2);
				   पूर्ण
                        पूर्ण
                पूर्ण
        पूर्ण
	अन्यथा अणु
		Dपूर्णांक_setzero(resultp1,resultp2);

		/* check क्रम inexact */
		अगर (Sgl_isnotzero_exponenपंचांगantissa(src)) अणु
			inexact = TRUE;
                        /*  round result  */
                        चयन (Rounding_mode()) अणु
                        हाल ROUNDPLUS:
                             अगर (Sgl_iszero_sign(src)) अणु
				Dपूर्णांक_increment(resultp1,resultp2);
			     पूर्ण
                             अवरोध;
                        हाल ROUNDMINUS:
                             अगर (Sgl_isone_sign(src)) अणु
				Dपूर्णांक_decrement(resultp1,resultp2);
			     पूर्ण
                             अवरोध;
                        हाल ROUNDNEAREST:
                             अगर (src_exponent == -1)
                                अगर (Sgl_isnotzero_mantissa(src))
                                   अगर (Sgl_iszero_sign(src)) अणु
				      Dपूर्णांक_increment(resultp1,resultp2);
				   पूर्ण
                                   अन्यथा अणु
				      Dपूर्णांक_decrement(resultp1,resultp2);
				   पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	Dपूर्णांक_copytoptr(resultp1,resultp2,dstptr);
	अगर (inexact) अणु
		अगर (Is_inexacttrap_enabled()) वापस(INEXACTEXCEPTION);
		अन्यथा Set_inexactflag();
	पूर्ण
	वापस(NOEXCEPTION);
पूर्ण

/*
 *  Double Floating-poपूर्णांक to Single Fixed-poपूर्णांक 
 */
/*ARGSUSED*/
पूर्णांक
dbl_to_sgl_fcnvfx(
		    dbl_भग्नing_poपूर्णांक *srcptr,
		    अचिन्हित पूर्णांक *nullptr,
		    पूर्णांक *dstptr,
		    अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर अचिन्हित पूर्णांक srcp1,srcp2, tempp1,tempp2;
	रेजिस्टर पूर्णांक src_exponent, result;
	रेजिस्टर boolean inexact = FALSE;

	Dbl_copyfromptr(srcptr,srcp1,srcp2);
	src_exponent = Dbl_exponent(srcp1) - DBL_BIAS;

	/* 
	 * Test क्रम overflow
	 */
	अगर (src_exponent > SGL_FX_MAX_EXP) अणु
		/* check क्रम MININT */
		अगर (Dbl_isoverflow_to_पूर्णांक(src_exponent,srcp1,srcp2)) अणु
                        अगर (Dbl_iszero_sign(srcp1)) result = 0x7fffffff;
                        अन्यथा result = 0x80000000; 

	                अगर (Is_invalidtrap_enabled()) अणु
                            वापस(INVALIDEXCEPTION);
                        पूर्ण
                        Set_invalidflag();
			*dstptr = result;
			वापस(NOEXCEPTION);
		पूर्ण
	पूर्ण
	/*
	 * Generate result
	 */
	अगर (src_exponent >= 0) अणु
		tempp1 = srcp1;
		tempp2 = srcp2;
		Dbl_clear_signexponent_set_hidden(tempp1);
		Int_from_dbl_mantissa(tempp1,tempp2,src_exponent);
		अगर (Dbl_isone_sign(srcp1) && (src_exponent <= SGL_FX_MAX_EXP))
			result = -Dbl_allp1(tempp1);
		अन्यथा result = Dbl_allp1(tempp1);

		/* check क्रम inexact */
		अगर (Dbl_isinexact_to_fix(srcp1,srcp2,src_exponent)) अणु
                        inexact = TRUE;
                        /*  round result  */
                        चयन (Rounding_mode()) अणु
                        हाल ROUNDPLUS:
                             अगर (Dbl_iszero_sign(srcp1)) result++;
                             अवरोध;
                        हाल ROUNDMINUS:
                             अगर (Dbl_isone_sign(srcp1)) result--;
                             अवरोध;
                        हाल ROUNDNEAREST:
                             अगर (Dbl_isone_roundbit(srcp1,srcp2,src_exponent))
                                अगर (Dbl_isone_stickybit(srcp1,srcp2,src_exponent) || 
				(Dbl_isone_lowmantissap1(tempp1)))
                                   अगर (Dbl_iszero_sign(srcp1)) result++;
                                   अन्यथा result--;
                        पूर्ण 
			/* check क्रम overflow */
			अगर ((Dbl_iszero_sign(srcp1) && result < 0) ||
			    (Dbl_isone_sign(srcp1) && result > 0)) अणु
			        
                          अगर (Dbl_iszero_sign(srcp1)) result = 0x7fffffff;
                          अन्यथा result = 0x80000000; 

	                  अगर (Is_invalidtrap_enabled()) अणु
                            वापस(INVALIDEXCEPTION);
                          पूर्ण
                          Set_invalidflag();
			  *dstptr = result;
			  वापस(NOEXCEPTION);
			पूर्ण
                पूर्ण
	पूर्ण
	अन्यथा अणु
		result = 0;

		/* check क्रम inexact */
		अगर (Dbl_isnotzero_exponenपंचांगantissa(srcp1,srcp2)) अणु
                        inexact = TRUE;
                        /*  round result  */
                        चयन (Rounding_mode()) अणु
                        हाल ROUNDPLUS:
                             अगर (Dbl_iszero_sign(srcp1)) result++;
                             अवरोध;
                        हाल ROUNDMINUS:
                             अगर (Dbl_isone_sign(srcp1)) result--;
                             अवरोध;
                        हाल ROUNDNEAREST:
                             अगर (src_exponent == -1)
                                अगर (Dbl_isnotzero_mantissa(srcp1,srcp2))
                                   अगर (Dbl_iszero_sign(srcp1)) result++;
                                   अन्यथा result--;
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
 *  Double Floating-poपूर्णांक to Double Fixed-poपूर्णांक 
 */
/*ARGSUSED*/
पूर्णांक
dbl_to_dbl_fcnvfx(
		    dbl_भग्नing_poपूर्णांक *srcptr,
		    अचिन्हित पूर्णांक *nullptr,
		    dbl_पूर्णांकeger *dstptr,
		    अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर पूर्णांक src_exponent, resultp1;
	रेजिस्टर अचिन्हित पूर्णांक srcp1, srcp2, tempp1, tempp2, resultp2;
	रेजिस्टर boolean inexact = FALSE;

	Dbl_copyfromptr(srcptr,srcp1,srcp2);
	src_exponent = Dbl_exponent(srcp1) - DBL_BIAS;

	/* 
	 * Test क्रम overflow
	 */
	अगर (src_exponent > DBL_FX_MAX_EXP) अणु
		/* check क्रम MININT */
		अगर ((src_exponent > DBL_FX_MAX_EXP + 1) || 
		Dbl_isnotzero_mantissa(srcp1,srcp2) || Dbl_iszero_sign(srcp1)) अणु
                        अगर (Dbl_iszero_sign(srcp1)) अणु
                              resultp1 = 0x7fffffff;
			      resultp2 = 0xffffffff;
			पूर्ण
                        अन्यथा अणु
			    resultp1 = 0x80000000; 
			    resultp2 = 0;
			पूर्ण
	                अगर (Is_invalidtrap_enabled()) अणु
                            वापस(INVALIDEXCEPTION);
                        पूर्ण
                        Set_invalidflag();
    		        Dपूर्णांक_copytoptr(resultp1,resultp2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
	पूर्ण
 
	/*
	 * Generate result
	 */
	अगर (src_exponent >= 0) अणु
		tempp1 = srcp1;
		tempp2 = srcp2;
		Dbl_clear_signexponent_set_hidden(tempp1);
		Dपूर्णांक_from_dbl_mantissa(tempp1,tempp2,src_exponent,resultp1,
		resultp2);
		अगर (Dbl_isone_sign(srcp1)) अणु
			Dपूर्णांक_setone_sign(resultp1,resultp2);
		पूर्ण

		/* check क्रम inexact */
		अगर (Dbl_isinexact_to_fix(srcp1,srcp2,src_exponent)) अणु
                        inexact = TRUE;
                        /*  round result  */
                        चयन (Rounding_mode()) अणु
                        हाल ROUNDPLUS:
                             अगर (Dbl_iszero_sign(srcp1)) अणु
				Dपूर्णांक_increment(resultp1,resultp2);
			     पूर्ण
                             अवरोध;
                        हाल ROUNDMINUS:
                             अगर (Dbl_isone_sign(srcp1)) अणु
				Dपूर्णांक_decrement(resultp1,resultp2);
			     पूर्ण
                             अवरोध;
                        हाल ROUNDNEAREST:
                             अगर (Dbl_isone_roundbit(srcp1,srcp2,src_exponent))
                                अगर (Dbl_isone_stickybit(srcp1,srcp2,src_exponent) || 
				(Dपूर्णांक_isone_lowp2(resultp2)))
                                   अगर (Dbl_iszero_sign(srcp1)) अणु
				      Dपूर्णांक_increment(resultp1,resultp2);
				   पूर्ण
                                   अन्यथा अणु
				      Dपूर्णांक_decrement(resultp1,resultp2);
				   पूर्ण
                        पूर्ण 
                पूर्ण
	पूर्ण
	अन्यथा अणु
		Dपूर्णांक_setzero(resultp1,resultp2);

		/* check क्रम inexact */
		अगर (Dbl_isnotzero_exponenपंचांगantissa(srcp1,srcp2)) अणु
                        inexact = TRUE;
                        /*  round result  */
                        चयन (Rounding_mode()) अणु
                        हाल ROUNDPLUS:
                             अगर (Dbl_iszero_sign(srcp1)) अणु
				Dपूर्णांक_increment(resultp1,resultp2);
			     पूर्ण
                             अवरोध;
                        हाल ROUNDMINUS:
                             अगर (Dbl_isone_sign(srcp1)) अणु
				Dपूर्णांक_decrement(resultp1,resultp2);
			     पूर्ण
                             अवरोध;
                        हाल ROUNDNEAREST:
                             अगर (src_exponent == -1)
                                अगर (Dbl_isnotzero_mantissa(srcp1,srcp2))
                                   अगर (Dbl_iszero_sign(srcp1)) अणु
				      Dपूर्णांक_increment(resultp1,resultp2);
				   पूर्ण
                                   अन्यथा अणु
				      Dपूर्णांक_decrement(resultp1,resultp2);
				   पूर्ण
			पूर्ण
                पूर्ण
	पूर्ण
	Dपूर्णांक_copytoptr(resultp1,resultp2,dstptr);
        अगर (inexact) अणु
                अगर (Is_inexacttrap_enabled()) वापस(INEXACTEXCEPTION);
        	अन्यथा Set_inexactflag();
        पूर्ण
	वापस(NOEXCEPTION);
पूर्ण
