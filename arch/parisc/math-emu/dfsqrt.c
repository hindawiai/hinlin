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
 *	@(#)	pa/spmath/dfवर्ग_मूल.c		$Revision: 1.1 $
 *
 *  Purpose:
 *	Double Floating-poपूर्णांक Square Root
 *
 *  External Interfaces:
 *	dbl_fवर्ग_मूल(srcptr,nullptr,dstptr,status)
 *
 *  Internal Interfaces:
 *
 *  Theory:
 *	<<please update with a overview of the operation of this file>>
 *
 * END_DESC
*/


#समावेश "float.h"
#समावेश "dbl_float.h"

/*
 *  Double Floating-poपूर्णांक Square Root
 */

/*ARGSUSED*/
अचिन्हित पूर्णांक
dbl_fवर्ग_मूल(
	    dbl_भग्नing_poपूर्णांक *srcptr,
	    अचिन्हित पूर्णांक *nullptr,
	    dbl_भग्नing_poपूर्णांक *dstptr,
	    अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर अचिन्हित पूर्णांक srcp1, srcp2, resultp1, resultp2;
	रेजिस्टर अचिन्हित पूर्णांक newbitp1, newbitp2, sump1, sump2;
	रेजिस्टर पूर्णांक src_exponent;
	रेजिस्टर boolean guardbit = FALSE, even_exponent;

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
                 * Return quiet NaN or positive infinity.
		 *  Fall through to negative test अगर negative infinity.
                 */
		अगर (Dbl_iszero_sign(srcp1) || 
		    Dbl_isnotzero_mantissa(srcp1,srcp2)) अणु
                	Dbl_copytoptr(srcp1,srcp2,dstptr);
                	वापस(NOEXCEPTION);
		पूर्ण
        पूर्ण

        /*
         * check क्रम zero source opeअक्रम
         */
	अगर (Dbl_iszero_exponenपंचांगantissa(srcp1,srcp2)) अणु
		Dbl_copytoptr(srcp1,srcp2,dstptr);
		वापस(NOEXCEPTION);
	पूर्ण

        /*
         * check क्रम negative source opeअक्रम 
         */
	अगर (Dbl_isone_sign(srcp1)) अणु
		/* trap अगर INVALIDTRAP enabled */
		अगर (Is_invalidtrap_enabled()) वापस(INVALIDEXCEPTION);
		/* make NaN quiet */
		Set_invalidflag();
		Dbl_makequietnan(srcp1,srcp2);
		Dbl_copytoptr(srcp1,srcp2,dstptr);
		वापस(NOEXCEPTION);
	पूर्ण

	/*
	 * Generate result
	 */
	अगर (src_exponent > 0) अणु
		even_exponent = Dbl_hidden(srcp1);
		Dbl_clear_signexponent_set_hidden(srcp1);
	पूर्ण
	अन्यथा अणु
		/* normalize opeअक्रम */
		Dbl_clear_signexponent(srcp1);
		src_exponent++;
		Dbl_normalize(srcp1,srcp2,src_exponent);
		even_exponent = src_exponent & 1;
	पूर्ण
	अगर (even_exponent) अणु
		/* exponent is even */
		/* Add comment here.  Explain why odd exponent needs correction */
		Dbl_leftshअगरtby1(srcp1,srcp2);
	पूर्ण
	/*
	 * Add comment here.  Explain following algorithm.
	 * 
	 * Trust me, it works.
	 *
	 */
	Dbl_setzero(resultp1,resultp2);
	Dbl_allp1(newbitp1) = 1 << (DBL_P - 32);
	Dbl_setzero_mantissap2(newbitp2);
	जबतक (Dbl_isnotzero(newbitp1,newbitp2) && Dbl_isnotzero(srcp1,srcp2)) अणु
		Dbl_addition(resultp1,resultp2,newbitp1,newbitp2,sump1,sump2);
		अगर(Dbl_isnotgreaterthan(sump1,sump2,srcp1,srcp2)) अणु
			Dbl_leftshअगरtby1(newbitp1,newbitp2);
			/* update result */
			Dbl_addition(resultp1,resultp2,newbitp1,newbitp2,
			 resultp1,resultp2);  
			Dbl_subtract(srcp1,srcp2,sump1,sump2,srcp1,srcp2);
			Dbl_rightshअगरtby2(newbitp1,newbitp2);
		पूर्ण
		अन्यथा अणु
			Dbl_rightshअगरtby1(newbitp1,newbitp2);
		पूर्ण
		Dbl_leftshअगरtby1(srcp1,srcp2);
	पूर्ण
	/* correct exponent क्रम pre-shअगरt */
	अगर (even_exponent) अणु
		Dbl_rightshअगरtby1(resultp1,resultp2);
	पूर्ण

	/* check क्रम inexact */
	अगर (Dbl_isnotzero(srcp1,srcp2)) अणु
		अगर (!even_exponent && Dbl_islessthan(resultp1,resultp2,srcp1,srcp2)) अणु
			Dbl_increment(resultp1,resultp2);
		पूर्ण
		guardbit = Dbl_lowmantissap2(resultp2);
		Dbl_rightshअगरtby1(resultp1,resultp2);

		/*  now round result  */
		चयन (Rounding_mode()) अणु
		हाल ROUNDPLUS:
		     Dbl_increment(resultp1,resultp2);
		     अवरोध;
		हाल ROUNDNEAREST:
		     /* stickybit is always true, so guardbit 
		      * is enough to determine rounding */
		     अगर (guardbit) अणु
			    Dbl_increment(resultp1,resultp2);
		     पूर्ण
		     अवरोध;
		पूर्ण
		/* increment result exponent by 1 अगर mantissa overflowed */
		अगर (Dbl_isone_hiddenoverflow(resultp1)) src_exponent+=2;

		अगर (Is_inexacttrap_enabled()) अणु
			Dbl_set_exponent(resultp1,
			 ((src_exponent-DBL_BIAS)>>1)+DBL_BIAS);
			Dbl_copytoptr(resultp1,resultp2,dstptr);
			वापस(INEXACTEXCEPTION);
		पूर्ण
		अन्यथा Set_inexactflag();
	पूर्ण
	अन्यथा अणु
		Dbl_rightshअगरtby1(resultp1,resultp2);
	पूर्ण
	Dbl_set_exponent(resultp1,((src_exponent-DBL_BIAS)>>1)+DBL_BIAS);
	Dbl_copytoptr(resultp1,resultp2,dstptr);
	वापस(NOEXCEPTION);
पूर्ण
