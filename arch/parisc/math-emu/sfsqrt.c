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
 *	@(#)	pa/spmath/sfवर्ग_मूल.c		$Revision: 1.1 $
 *
 *  Purpose:
 *	Single Floating-poपूर्णांक Square Root
 *
 *  External Interfaces:
 *	sgl_fवर्ग_मूल(srcptr,nullptr,dstptr,status)
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

/*
 *  Single Floating-poपूर्णांक Square Root
 */

/*ARGSUSED*/
अचिन्हित पूर्णांक
sgl_fवर्ग_मूल(
    sgl_भग्नing_poपूर्णांक *srcptr,
    अचिन्हित पूर्णांक *nullptr,
    sgl_भग्नing_poपूर्णांक *dstptr,
    अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर अचिन्हित पूर्णांक src, result;
	रेजिस्टर पूर्णांक src_exponent;
	रेजिस्टर अचिन्हित पूर्णांक newbit, sum;
	रेजिस्टर boolean guardbit = FALSE, even_exponent;

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
                 * Return quiet NaN or positive infinity.
		 *  Fall through to negative test अगर negative infinity.
                 */
		अगर (Sgl_iszero_sign(src) || Sgl_isnotzero_mantissa(src)) अणु
                	*dstptr = src;
                	वापस(NOEXCEPTION);
		पूर्ण
        पूर्ण

        /*
         * check क्रम zero source opeअक्रम
         */
	अगर (Sgl_iszero_exponenपंचांगantissa(src)) अणु
		*dstptr = src;
		वापस(NOEXCEPTION);
	पूर्ण

        /*
         * check क्रम negative source opeअक्रम 
         */
	अगर (Sgl_isone_sign(src)) अणु
		/* trap अगर INVALIDTRAP enabled */
		अगर (Is_invalidtrap_enabled()) वापस(INVALIDEXCEPTION);
		/* make NaN quiet */
		Set_invalidflag();
		Sgl_makequietnan(src);
		*dstptr = src;
		वापस(NOEXCEPTION);
	पूर्ण

	/*
	 * Generate result
	 */
	अगर (src_exponent > 0) अणु
		even_exponent = Sgl_hidden(src);
		Sgl_clear_signexponent_set_hidden(src);
	पूर्ण
	अन्यथा अणु
		/* normalize opeअक्रम */
		Sgl_clear_signexponent(src);
		src_exponent++;
		Sgl_normalize(src,src_exponent);
		even_exponent = src_exponent & 1;
	पूर्ण
	अगर (even_exponent) अणु
		/* exponent is even */
		/* Add comment here.  Explain why odd exponent needs correction */
		Sgl_leftshअगरtby1(src);
	पूर्ण
	/*
	 * Add comment here.  Explain following algorithm.
	 * 
	 * Trust me, it works.
	 *
	 */
	Sgl_setzero(result);
	newbit = 1 << SGL_P;
	जबतक (newbit && Sgl_isnotzero(src)) अणु
		Sgl_addition(result,newbit,sum);
		अगर(sum <= Sgl_all(src)) अणु
			/* update result */
			Sgl_addition(result,(newbit<<1),result);
			Sgl_subtract(src,sum,src);
		पूर्ण
		Sgl_rightshअगरtby1(newbit);
		Sgl_leftshअगरtby1(src);
	पूर्ण
	/* correct exponent क्रम pre-shअगरt */
	अगर (even_exponent) अणु
		Sgl_rightshअगरtby1(result);
	पूर्ण

	/* check क्रम inexact */
	अगर (Sgl_isnotzero(src)) अणु
		अगर (!even_exponent && Sgl_islessthan(result,src)) 
			Sgl_increment(result);
		guardbit = Sgl_lowmantissa(result);
		Sgl_rightshअगरtby1(result);

		/*  now round result  */
		चयन (Rounding_mode()) अणु
		हाल ROUNDPLUS:
		     Sgl_increment(result);
		     अवरोध;
		हाल ROUNDNEAREST:
		     /* stickybit is always true, so guardbit 
		      * is enough to determine rounding */
		     अगर (guardbit) अणु
			Sgl_increment(result);
		     पूर्ण
		     अवरोध;
		पूर्ण
		/* increment result exponent by 1 अगर mantissa overflowed */
		अगर (Sgl_isone_hiddenoverflow(result)) src_exponent+=2;

		अगर (Is_inexacttrap_enabled()) अणु
			Sgl_set_exponent(result,
			 ((src_exponent-SGL_BIAS)>>1)+SGL_BIAS);
			*dstptr = result;
			वापस(INEXACTEXCEPTION);
		पूर्ण
		अन्यथा Set_inexactflag();
	पूर्ण
	अन्यथा अणु
		Sgl_rightshअगरtby1(result);
	पूर्ण
	Sgl_set_exponent(result,((src_exponent-SGL_BIAS)>>1)+SGL_BIAS);
	*dstptr = result;
	वापस(NOEXCEPTION);
पूर्ण
