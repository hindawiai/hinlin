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
 *	@(#)	pa/spmath/fcnvff.c		$Revision: 1.1 $
 *
 *  Purpose:
 *	Single Floating-poपूर्णांक to Double Floating-poपूर्णांक
 *	Double Floating-poपूर्णांक to Single Floating-poपूर्णांक
 *
 *  External Interfaces:
 *	dbl_to_sgl_fcnvff(srcptr,nullptr,dstptr,status)
 *	sgl_to_dbl_fcnvff(srcptr,nullptr,dstptr,status)
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
 *  Single Floating-poपूर्णांक to Double Floating-poपूर्णांक 
 */
/*ARGSUSED*/
पूर्णांक
sgl_to_dbl_fcnvff(
	    sgl_भग्नing_poपूर्णांक *srcptr,
	    अचिन्हित पूर्णांक *nullptr,
	    dbl_भग्नing_poपूर्णांक *dstptr,
	    अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर अचिन्हित पूर्णांक src, resultp1, resultp2;
	रेजिस्टर पूर्णांक src_exponent;

	src = *srcptr;
	src_exponent = Sgl_exponent(src);
	Dbl_allp1(resultp1) = Sgl_all(src);  /* set sign of result */
	/* 
 	 * Test क्रम NaN or infinity
 	 */
	अगर (src_exponent == SGL_अनन्त_EXPONENT) अणु
		/*
		 * determine अगर NaN or infinity
		 */
		अगर (Sgl_iszero_mantissa(src)) अणु
			/*
			 * is infinity; want to वापस द्विगुन infinity
			 */
			Dbl_setinfinity_exponenपंचांगantissa(resultp1,resultp2);
			Dbl_copytoptr(resultp1,resultp2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
		अन्यथा अणु
			/* 
			 * is NaN; संकेतing or quiet?
			 */
			अगर (Sgl_isone_संकेतing(src)) अणु
				/* trap अगर INVALIDTRAP enabled */
				अगर (Is_invalidtrap_enabled())
					वापस(INVALIDEXCEPTION);
				/* make NaN quiet */
				अन्यथा अणु
					Set_invalidflag();
					Sgl_set_quiet(src);
				पूर्ण
			पूर्ण
			/* 
			 * NaN is quiet, वापस as द्विगुन NaN 
			 */
			Dbl_setinfinity_exponent(resultp1);
			Sgl_to_dbl_mantissa(src,resultp1,resultp2);
			Dbl_copytoptr(resultp1,resultp2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
	पूर्ण
	/* 
 	 * Test क्रम zero or denormalized
 	 */
	अगर (src_exponent == 0) अणु
		/*
		 * determine अगर zero or denormalized
		 */
		अगर (Sgl_isnotzero_mantissa(src)) अणु
			/*
			 * is denormalized; want to normalize
			 */
			Sgl_clear_signexponent(src);
			Sgl_leftshअगरtby1(src);
			Sgl_normalize(src,src_exponent);
			Sgl_to_dbl_exponent(src_exponent,resultp1);
			Sgl_to_dbl_mantissa(src,resultp1,resultp2);
		पूर्ण
		अन्यथा अणु
			Dbl_setzero_exponenपंचांगantissa(resultp1,resultp2);
		पूर्ण
		Dbl_copytoptr(resultp1,resultp2,dstptr);
		वापस(NOEXCEPTION);
	पूर्ण
	/*
	 * No special हालs, just complete the conversion
	 */
	Sgl_to_dbl_exponent(src_exponent, resultp1);
	Sgl_to_dbl_mantissa(Sgl_mantissa(src), resultp1,resultp2);
	Dbl_copytoptr(resultp1,resultp2,dstptr);
	वापस(NOEXCEPTION);
पूर्ण

/*
 *  Double Floating-poपूर्णांक to Single Floating-poपूर्णांक 
 */
/*ARGSUSED*/
पूर्णांक
dbl_to_sgl_fcnvff(
		    dbl_भग्नing_poपूर्णांक *srcptr,
		    अचिन्हित पूर्णांक *nullptr,
		    sgl_भग्नing_poपूर्णांक *dstptr,
		    अचिन्हित पूर्णांक *status)
अणु
        रेजिस्टर अचिन्हित पूर्णांक srcp1, srcp2, result;
        रेजिस्टर पूर्णांक src_exponent, dest_exponent, dest_mantissa;
        रेजिस्टर boolean inexact = FALSE, guardbit = FALSE, stickybit = FALSE;
	रेजिस्टर boolean lsb_odd = FALSE;
	boolean is_tiny = FALSE;

	Dbl_copyfromptr(srcptr,srcp1,srcp2);
        src_exponent = Dbl_exponent(srcp1);
	Sgl_all(result) = Dbl_allp1(srcp1);  /* set sign of result */
        /* 
         * Test क्रम NaN or infinity
         */
        अगर (src_exponent == DBL_अनन्त_EXPONENT) अणु
                /*
                 * determine अगर NaN or infinity
                 */
                अगर (Dbl_iszero_mantissa(srcp1,srcp2)) अणु
                        /*
                         * is infinity; want to वापस single infinity
                         */
                        Sgl_setinfinity_exponenपंचांगantissa(result);
                        *dstptr = result;
                        वापस(NOEXCEPTION);
                पूर्ण
                /* 
                 * is NaN; संकेतing or quiet?
                 */
                अगर (Dbl_isone_संकेतing(srcp1)) अणु
                        /* trap अगर INVALIDTRAP enabled */
                        अगर (Is_invalidtrap_enabled()) वापस(INVALIDEXCEPTION);
                        अन्यथा अणु
				Set_invalidflag();
                        	/* make NaN quiet */
                        	Dbl_set_quiet(srcp1);
			पूर्ण
                पूर्ण
                /* 
                 * NaN is quiet, वापस as single NaN 
                 */
                Sgl_setinfinity_exponent(result);
		Sgl_set_mantissa(result,Dallp1(srcp1)<<3 | Dallp2(srcp2)>>29);
		अगर (Sgl_iszero_mantissa(result)) Sgl_set_quiet(result);
                *dstptr = result;
                वापस(NOEXCEPTION);
        पूर्ण
        /*
         * Generate result
         */
        Dbl_to_sgl_exponent(src_exponent,dest_exponent);
	अगर (dest_exponent > 0) अणु
        	Dbl_to_sgl_mantissa(srcp1,srcp2,dest_mantissa,inexact,guardbit, 
		stickybit,lsb_odd);
	पूर्ण
	अन्यथा अणु
		अगर (Dbl_iszero_exponenपंचांगantissa(srcp1,srcp2))अणु
			Sgl_setzero_exponenपंचांगantissa(result);
			*dstptr = result;
			वापस(NOEXCEPTION);
		पूर्ण
                अगर (Is_underflowtrap_enabled()) अणु
			Dbl_to_sgl_mantissa(srcp1,srcp2,dest_mantissa,inexact,
			guardbit,stickybit,lsb_odd);
                पूर्ण
		अन्यथा अणु
			/* compute result, determine inexact info,
			 * and set Underflowflag अगर appropriate
			 */
			Dbl_to_sgl_denormalized(srcp1,srcp2,dest_exponent,
			dest_mantissa,inexact,guardbit,stickybit,lsb_odd,
			is_tiny);
		पूर्ण
	पूर्ण
        /* 
         * Now round result अगर not exact
         */
        अगर (inexact) अणु
                चयन (Rounding_mode()) अणु
                        हाल ROUNDPLUS: 
                                अगर (Sgl_iszero_sign(result)) dest_mantissa++;
                                अवरोध;
                        हाल ROUNDMINUS: 
                                अगर (Sgl_isone_sign(result)) dest_mantissa++;
                                अवरोध;
                        हाल ROUNDNEAREST:
                                अगर (guardbit) अणु
                                   अगर (stickybit || lsb_odd) dest_mantissa++;
                                   पूर्ण
                पूर्ण
        पूर्ण
        Sgl_set_exponenपंचांगantissa(result,dest_mantissa);

        /*
         * check क्रम mantissa overflow after rounding
         */
        अगर ((dest_exponent>0 || Is_underflowtrap_enabled()) && 
	    Sgl_isone_hidden(result)) dest_exponent++;

        /* 
         * Test क्रम overflow
         */
        अगर (dest_exponent >= SGL_अनन्त_EXPONENT) अणु
                /* trap अगर OVERFLOWTRAP enabled */
                अगर (Is_overflowtrap_enabled()) अणु
                        /* 
                         * Check क्रम gross overflow
                         */
                        अगर (dest_exponent >= SGL_अनन्त_EXPONENT+SGL_WRAP) 
                        	वापस(UNIMPLEMENTEDEXCEPTION);
                        
                        /*
                         * Adjust bias of result
                         */
			Sgl_setwrapped_exponent(result,dest_exponent,ovfl);
			*dstptr = result;
			अगर (inexact) 
			    अगर (Is_inexacttrap_enabled())
				वापस(OVERFLOWEXCEPTION|INEXACTEXCEPTION);
			    अन्यथा Set_inexactflag();
                        वापस(OVERFLOWEXCEPTION);
                पूर्ण
                Set_overflowflag();
		inexact = TRUE;
		/* set result to infinity or largest number */
		Sgl_setoverflow(result);
        पूर्ण
        /* 
         * Test क्रम underflow
         */
        अन्यथा अगर (dest_exponent <= 0) अणु
                /* trap अगर UNDERFLOWTRAP enabled */
                अगर (Is_underflowtrap_enabled()) अणु
                        /* 
                         * Check क्रम gross underflow
                         */
                        अगर (dest_exponent <= -(SGL_WRAP))
                        	वापस(UNIMPLEMENTEDEXCEPTION);
                        /*
                         * Adjust bias of result
                         */
			Sgl_setwrapped_exponent(result,dest_exponent,unfl);
			*dstptr = result;
			अगर (inexact) 
			    अगर (Is_inexacttrap_enabled())
				वापस(UNDERFLOWEXCEPTION|INEXACTEXCEPTION);
			    अन्यथा Set_inexactflag();
                        वापस(UNDERFLOWEXCEPTION);
                पूर्ण
                 /* 
                  * result is denormalized or चिन्हित zero
                  */
               अगर (inexact && is_tiny) Set_underflowflag();

        पूर्ण
	अन्यथा Sgl_set_exponent(result,dest_exponent);
	*dstptr = result;
        /* 
         * Trap अगर inexact trap is enabled
         */
        अगर (inexact)
        	अगर (Is_inexacttrap_enabled()) वापस(INEXACTEXCEPTION);
        	अन्यथा Set_inexactflag();
        वापस(NOEXCEPTION);
पूर्ण
