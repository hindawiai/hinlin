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
 *	@(#)	pa/spmath/fcnvfut.c		$Revision: 1.1 $
 *
 *  Purpose:
 *	Floating-poपूर्णांक to Unचिन्हित Fixed-poपूर्णांक Converts with Truncation
 *
 *  External Interfaces:
 *	dbl_to_dbl_fcnvfut(srcptr,nullptr,dstptr,status)
 *	dbl_to_sgl_fcnvfut(srcptr,nullptr,dstptr,status)
 *	sgl_to_dbl_fcnvfut(srcptr,nullptr,dstptr,status)
 *	sgl_to_sgl_fcnvfut(srcptr,nullptr,dstptr,status)
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
 *  Floating-poपूर्णांक to Unचिन्हित Fixed-poपूर्णांक Converts with Truncation	*
 ************************************************************************/

/*
 *  Convert single भग्नing-poपूर्णांक to single fixed-poपूर्णांक क्रमmat
 *  with truncated result
 */
/*ARGSUSED*/
पूर्णांक
sgl_to_sgl_fcnvfut (sgl_भग्नing_poपूर्णांक * srcptr, अचिन्हित पूर्णांक *nullptr,
		    अचिन्हित पूर्णांक *dstptr, अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर अचिन्हित पूर्णांक src, result;
	रेजिस्टर पूर्णांक src_exponent;

	src = *srcptr;
	src_exponent = Sgl_exponent(src) - SGL_BIAS;

	/* 
	 * Test क्रम overflow
	 */
	अगर (src_exponent > SGL_FX_MAX_EXP + 1) अणु
		अगर (Sgl_isone_sign(src)) अणु
			result = 0;
		पूर्ण अन्यथा अणु
			result = 0xffffffff;
		पूर्ण
		अगर (Is_invalidtrap_enabled()) अणु
			वापस(INVALIDEXCEPTION);
		पूर्ण
		Set_invalidflag();
		*dstptr = result;
		वापस(NOEXCEPTION);
	पूर्ण
	/*
	 * Generate result
	 */
	अगर (src_exponent >= 0) अणु
		/* 
		 * Check sign.
		 * If negative, trap unimplemented.
		 */
		अगर (Sgl_isone_sign(src)) अणु
			result = 0;
			अगर (Is_invalidtrap_enabled()) अणु
				वापस(INVALIDEXCEPTION);
			पूर्ण
			Set_invalidflag();
			*dstptr = result;
			वापस(NOEXCEPTION);
		पूर्ण
		Sgl_clear_signexponent_set_hidden(src);
		Suपूर्णांक_from_sgl_mantissa(src,src_exponent,result);
		*dstptr = result;

		/* check क्रम inexact */
		अगर (Sgl_isinexact_to_अचिन्हित(src,src_exponent)) अणु
			अगर (Is_inexacttrap_enabled()) वापस(INEXACTEXCEPTION);
			अन्यथा Set_inexactflag();
		पूर्ण
	पूर्ण
	अन्यथा अणु
		*dstptr = 0;

		/* check क्रम inexact */
		अगर (Sgl_isnotzero_exponenपंचांगantissa(src)) अणु
			अगर (Is_inexacttrap_enabled()) वापस(INEXACTEXCEPTION);
			अन्यथा Set_inexactflag();
		पूर्ण
	पूर्ण
	वापस(NOEXCEPTION);
पूर्ण

/*
 *  Single Floating-poपूर्णांक to Double Unचिन्हित Fixed 
 */
/*ARGSUSED*/
पूर्णांक
sgl_to_dbl_fcnvfut (sgl_भग्नing_poपूर्णांक * srcptr, अचिन्हित पूर्णांक *nullptr,
		    dbl_अचिन्हित * dstptr, अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर पूर्णांक src_exponent;
	रेजिस्टर अचिन्हित पूर्णांक src, resultp1, resultp2;

	src = *srcptr;
	src_exponent = Sgl_exponent(src) - SGL_BIAS;

	/* 
	 * Test क्रम overflow
	 */
	अगर (src_exponent > DBL_FX_MAX_EXP + 1) अणु
		अगर (Sgl_isone_sign(src)) अणु
			resultp1 = resultp2 = 0;
		पूर्ण अन्यथा अणु
			resultp1 = resultp2 = 0xffffffff;
		पूर्ण
		अगर (Is_invalidtrap_enabled()) अणु
			वापस(INVALIDEXCEPTION);
		पूर्ण
		Set_invalidflag();
    		Duपूर्णांक_copytoptr(resultp1,resultp2,dstptr);
		वापस(NOEXCEPTION);
	पूर्ण
	/*
	 * Generate result
	 */
	अगर (src_exponent >= 0) अणु
		/* 
		 * Check sign.
		 * If negative, trap unimplemented.
		 */
		अगर (Sgl_isone_sign(src)) अणु
			resultp1 = resultp2 = 0;
			अगर (Is_invalidtrap_enabled()) अणु
				वापस(INVALIDEXCEPTION);
			पूर्ण
			Set_invalidflag();
    			Duपूर्णांक_copytoptr(resultp1,resultp2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
		Sgl_clear_signexponent_set_hidden(src);
		Duपूर्णांक_from_sgl_mantissa(src,src_exponent,resultp1,resultp2);
		Duपूर्णांक_copytoptr(resultp1,resultp2,dstptr);

		/* check क्रम inexact */
		अगर (Sgl_isinexact_to_अचिन्हित(src,src_exponent)) अणु
			अगर (Is_inexacttrap_enabled()) वापस(INEXACTEXCEPTION);
			अन्यथा Set_inexactflag();
		पूर्ण
	पूर्ण
	अन्यथा अणु
		Duपूर्णांक_setzero(resultp1,resultp2);
		Duपूर्णांक_copytoptr(resultp1,resultp2,dstptr);

		/* check क्रम inexact */
		अगर (Sgl_isnotzero_exponenपंचांगantissa(src)) अणु
			अगर (Is_inexacttrap_enabled()) वापस(INEXACTEXCEPTION);
			अन्यथा Set_inexactflag();
		पूर्ण
	पूर्ण
	वापस(NOEXCEPTION);
पूर्ण

/*
 *  Double Floating-poपूर्णांक to Single Unचिन्हित Fixed 
 */
/*ARGSUSED*/
पूर्णांक
dbl_to_sgl_fcnvfut (dbl_भग्नing_poपूर्णांक * srcptr, अचिन्हित पूर्णांक *nullptr,
		    अचिन्हित पूर्णांक *dstptr, अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर अचिन्हित पूर्णांक srcp1, srcp2, result;
	रेजिस्टर पूर्णांक src_exponent;

	Dbl_copyfromptr(srcptr,srcp1,srcp2);
	src_exponent = Dbl_exponent(srcp1) - DBL_BIAS;

	/* 
	 * Test क्रम overflow
	 */
	अगर (src_exponent > SGL_FX_MAX_EXP + 1) अणु
		अगर (Dbl_isone_sign(srcp1)) अणु
			result = 0;
		पूर्ण अन्यथा अणु
			result = 0xffffffff;
		पूर्ण
		अगर (Is_invalidtrap_enabled()) अणु
			वापस(INVALIDEXCEPTION);
		पूर्ण
		Set_invalidflag();
		*dstptr = result;
		वापस(NOEXCEPTION);
	पूर्ण
	/*
	 * Generate result
	 */
	अगर (src_exponent >= 0) अणु
		/* 
		 * Check sign.
		 * If negative, trap unimplemented.
		 */
		अगर (Dbl_isone_sign(srcp1)) अणु
			result = 0;
			अगर (Is_invalidtrap_enabled()) अणु
				वापस(INVALIDEXCEPTION);
			पूर्ण
			Set_invalidflag();
			*dstptr = result;
			वापस(NOEXCEPTION);
		पूर्ण
		Dbl_clear_signexponent_set_hidden(srcp1);
		Suपूर्णांक_from_dbl_mantissa(srcp1,srcp2,src_exponent,result);
		*dstptr = result;

		/* check क्रम inexact */
		अगर (Dbl_isinexact_to_अचिन्हित(srcp1,srcp2,src_exponent)) अणु
			अगर (Is_inexacttrap_enabled()) वापस(INEXACTEXCEPTION);
			अन्यथा Set_inexactflag();
		पूर्ण
	पूर्ण
	अन्यथा अणु
		*dstptr = 0;

		/* check क्रम inexact */
		अगर (Dbl_isnotzero_exponenपंचांगantissa(srcp1,srcp2)) अणु
			अगर (Is_inexacttrap_enabled()) वापस(INEXACTEXCEPTION);
			अन्यथा Set_inexactflag();
		पूर्ण
	पूर्ण
	वापस(NOEXCEPTION);
पूर्ण

/*
 *  Double Floating-poपूर्णांक to Double Unचिन्हित Fixed 
 */
/*ARGSUSED*/
पूर्णांक
dbl_to_dbl_fcnvfut (dbl_भग्नing_poपूर्णांक * srcptr, अचिन्हित पूर्णांक *nullptr,
		    dbl_अचिन्हित * dstptr, अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर पूर्णांक src_exponent;
	रेजिस्टर अचिन्हित पूर्णांक srcp1, srcp2, resultp1, resultp2;

	Dbl_copyfromptr(srcptr,srcp1,srcp2);
	src_exponent = Dbl_exponent(srcp1) - DBL_BIAS;

	/* 
	 * Test क्रम overflow
	 */
	अगर (src_exponent > DBL_FX_MAX_EXP + 1) अणु
		अगर (Dbl_isone_sign(srcp1)) अणु
			resultp1 = resultp2 = 0;
		पूर्ण अन्यथा अणु
			resultp1 = resultp2 = 0xffffffff;
		पूर्ण
		अगर (Is_invalidtrap_enabled()) अणु
			वापस(INVALIDEXCEPTION);
		पूर्ण
		Set_invalidflag();
    		Duपूर्णांक_copytoptr(resultp1,resultp2,dstptr);
		वापस(NOEXCEPTION);
	पूर्ण
	/*
	 * Generate result
	 */
	अगर (src_exponent >= 0) अणु
		/* 
		 * Check sign.
		 * If negative, trap unimplemented.
		 */
		अगर (Dbl_isone_sign(srcp1)) अणु
			resultp1 = resultp2 = 0;
			अगर (Is_invalidtrap_enabled()) अणु
				वापस(INVALIDEXCEPTION);
			पूर्ण
			Set_invalidflag();
    			Duपूर्णांक_copytoptr(resultp1,resultp2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
		Dbl_clear_signexponent_set_hidden(srcp1);
		Duपूर्णांक_from_dbl_mantissa(srcp1,srcp2,src_exponent,
		  resultp1,resultp2);
		Duपूर्णांक_copytoptr(resultp1,resultp2,dstptr);

		/* check क्रम inexact */
		अगर (Dbl_isinexact_to_अचिन्हित(srcp1,srcp2,src_exponent)) अणु
			अगर (Is_inexacttrap_enabled()) वापस(INEXACTEXCEPTION);
			अन्यथा Set_inexactflag();
		पूर्ण
	पूर्ण
	अन्यथा अणु
		Duपूर्णांक_setzero(resultp1,resultp2);
		Duपूर्णांक_copytoptr(resultp1,resultp2,dstptr);

		/* check क्रम inexact */
		अगर (Dbl_isnotzero_exponenपंचांगantissa(srcp1,srcp2)) अणु
			अगर (Is_inexacttrap_enabled()) वापस(INEXACTEXCEPTION);
			अन्यथा Set_inexactflag();
		पूर्ण
	पूर्ण
	वापस(NOEXCEPTION);
पूर्ण
