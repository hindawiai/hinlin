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
 *	@(#)	pa/spmath/dfadd.c		$Revision: 1.1 $
 *
 *  Purpose:
 *	Double_add: add two द्विगुन precision values.
 *
 *  External Interfaces:
 *	dbl_fadd(leftptr, rightptr, dstptr, status)
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
 * Double_add: add two द्विगुन precision values.
 */
dbl_fadd(
    dbl_भग्नing_poपूर्णांक *leftptr,
    dbl_भग्नing_poपूर्णांक *rightptr,
    dbl_भग्नing_poपूर्णांक *dstptr,
    अचिन्हित पूर्णांक *status)
अणु
    रेजिस्टर अचिन्हित पूर्णांक signless_upper_left, signless_upper_right, save;
    रेजिस्टर अचिन्हित पूर्णांक leftp1, leftp2, rightp1, rightp2, extent;
    रेजिस्टर अचिन्हित पूर्णांक resultp1 = 0, resultp2 = 0;
    
    रेजिस्टर पूर्णांक result_exponent, right_exponent, dअगरf_exponent;
    रेजिस्टर पूर्णांक sign_save, jumpsize;
    रेजिस्टर boolean inexact = FALSE;
    रेजिस्टर boolean underflowtrap;
        
    /* Create local copies of the numbers */
    Dbl_copyfromptr(leftptr,leftp1,leftp2);
    Dbl_copyfromptr(rightptr,rightp1,rightp2);

    /* A zero "save" helps discover equal opeअक्रमs (क्रम later),  *
     * and is used in swapping opeअक्रमs (अगर needed).             */
    Dbl_xortoपूर्णांकp1(leftp1,rightp1,/*to*/save);

    /*
     * check first opeअक्रम क्रम NaN's or infinity
     */
    अगर ((result_exponent = Dbl_exponent(leftp1)) == DBL_अनन्त_EXPONENT)
	अणु
	अगर (Dbl_iszero_mantissa(leftp1,leftp2)) 
	    अणु
	    अगर (Dbl_isnotnan(rightp1,rightp2)) 
		अणु
		अगर (Dbl_isinfinity(rightp1,rightp2) && save!=0) 
		    अणु
		    /* 
		     * invalid since opeअक्रमs are opposite चिन्हित infinity's
		     */
		    अगर (Is_invalidtrap_enabled()) वापस(INVALIDEXCEPTION);
                    Set_invalidflag();
                    Dbl_makequietnan(resultp1,resultp2);
		    Dbl_copytoptr(resultp1,resultp2,dstptr);
		    वापस(NOEXCEPTION);
		    पूर्ण
		/*
	 	 * वापस infinity
	 	 */
		Dbl_copytoptr(leftp1,leftp2,dstptr);
		वापस(NOEXCEPTION);
		पूर्ण
	    पूर्ण
	अन्यथा 
	    अणु
            /*
             * is NaN; संकेतing or quiet?
             */
            अगर (Dbl_isone_संकेतing(leftp1)) 
		अणु
               	/* trap अगर INVALIDTRAP enabled */
		अगर (Is_invalidtrap_enabled()) वापस(INVALIDEXCEPTION);
        	/* make NaN quiet */
        	Set_invalidflag();
        	Dbl_set_quiet(leftp1);
        	पूर्ण
	    /* 
	     * is second opeअक्रम a संकेतing NaN? 
	     */
	    अन्यथा अगर (Dbl_is_संकेतingnan(rightp1)) 
		अणु
        	/* trap अगर INVALIDTRAP enabled */
               	अगर (Is_invalidtrap_enabled()) वापस(INVALIDEXCEPTION);
		/* make NaN quiet */
		Set_invalidflag();
		Dbl_set_quiet(rightp1);
		Dbl_copytoptr(rightp1,rightp2,dstptr);
		वापस(NOEXCEPTION);
		पूर्ण
	    /*
 	     * वापस quiet NaN
 	     */
	    Dbl_copytoptr(leftp1,leftp2,dstptr);
 	    वापस(NOEXCEPTION);
	    पूर्ण
	पूर्ण /* End left NaN or Infinity processing */
    /*
     * check second opeअक्रम क्रम NaN's or infinity
     */
    अगर (Dbl_isinfinity_exponent(rightp1)) 
	अणु
	अगर (Dbl_iszero_mantissa(rightp1,rightp2)) 
	    अणु
	    /* वापस infinity */
	    Dbl_copytoptr(rightp1,rightp2,dstptr);
	    वापस(NOEXCEPTION);
	    पूर्ण
        /*
         * is NaN; संकेतing or quiet?
         */
        अगर (Dbl_isone_संकेतing(rightp1)) 
	    अणु
            /* trap अगर INVALIDTRAP enabled */
	    अगर (Is_invalidtrap_enabled()) वापस(INVALIDEXCEPTION);
	    /* make NaN quiet */
	    Set_invalidflag();
	    Dbl_set_quiet(rightp1);
	    पूर्ण
	/*
	 * वापस quiet NaN
 	 */
	Dbl_copytoptr(rightp1,rightp2,dstptr);
	वापस(NOEXCEPTION);
    	पूर्ण /* End right NaN or Infinity processing */

    /* Invariant: Must be dealing with finite numbers */

    /* Compare opeअक्रमs by removing the sign */
    Dbl_copytoपूर्णांक_exponenपंचांगantissap1(leftp1,signless_upper_left);
    Dbl_copytoपूर्णांक_exponenपंचांगantissap1(rightp1,signless_upper_right);

    /* sign dअगरference selects add or sub operation. */
    अगर(Dbl_ismagnitudeless(leftp2,rightp2,signless_upper_left,signless_upper_right))
	अणु
	/* Set the left opeअक्रम to the larger one by XOR swap *
	 *  First finish the first word using "save"          */
	Dbl_xorfromपूर्णांकp1(save,rightp1,/*to*/rightp1);
	Dbl_xorfromपूर्णांकp1(save,leftp1,/*to*/leftp1);
     	Dbl_swap_lower(leftp2,rightp2);
	result_exponent = Dbl_exponent(leftp1);
	पूर्ण
    /* Invariant:  left is not smaller than right. */ 

    अगर((right_exponent = Dbl_exponent(rightp1)) == 0)
        अणु
	/* Denormalized opeअक्रमs.  First look क्रम zeroes */
	अगर(Dbl_iszero_mantissa(rightp1,rightp2)) 
	    अणु
	    /* right is zero */
	    अगर(Dbl_iszero_exponenपंचांगantissa(leftp1,leftp2))
		अणु
		/* Both opeअक्रमs are zeros */
		अगर(Is_rounding_mode(ROUNDMINUS))
		    अणु
		    Dbl_or_signs(leftp1,/*with*/rightp1);
		    पूर्ण
		अन्यथा
		    अणु
		    Dbl_and_signs(leftp1,/*with*/rightp1);
		    पूर्ण
		पूर्ण
	    अन्यथा 
		अणु
		/* Left is not a zero and must be the result.  Trapped
		 * underflows are संकेतed अगर left is denormalized.  Result
		 * is always exact. */
		अगर( (result_exponent == 0) && Is_underflowtrap_enabled() )
		    अणु
		    /* need to normalize results mantissa */
	    	    sign_save = Dbl_signextendedsign(leftp1);
		    Dbl_leftshअगरtby1(leftp1,leftp2);
		    Dbl_normalize(leftp1,leftp2,result_exponent);
		    Dbl_set_sign(leftp1,/*using*/sign_save);
                    Dbl_setwrapped_exponent(leftp1,result_exponent,unfl);
		    Dbl_copytoptr(leftp1,leftp2,dstptr);
		    /* inexact = FALSE */
		    वापस(UNDERFLOWEXCEPTION);
		    पूर्ण
		पूर्ण
	    Dbl_copytoptr(leftp1,leftp2,dstptr);
	    वापस(NOEXCEPTION);
	    पूर्ण

	/* Neither are zeroes */
	Dbl_clear_sign(rightp1);	/* Exponent is alपढ़ोy cleared */
	अगर(result_exponent == 0 )
	    अणु
	    /* Both opeअक्रमs are denormalized.  The result must be exact
	     * and is simply calculated.  A sum could become normalized and a
	     * dअगरference could cancel to a true zero. */
	    अगर( (/*चिन्हित*/पूर्णांक) save < 0 )
		अणु
		Dbl_subtract(leftp1,leftp2,/*minus*/rightp1,rightp2,
		/*पूर्णांकo*/resultp1,resultp2);
		अगर(Dbl_iszero_mantissa(resultp1,resultp2))
		    अणु
		    अगर(Is_rounding_mode(ROUNDMINUS))
			अणु
			Dbl_setone_sign(resultp1);
			पूर्ण
		    अन्यथा
			अणु
			Dbl_setzero_sign(resultp1);
			पूर्ण
		    Dbl_copytoptr(resultp1,resultp2,dstptr);
		    वापस(NOEXCEPTION);
		    पूर्ण
		पूर्ण
	    अन्यथा
		अणु
		Dbl_addition(leftp1,leftp2,rightp1,rightp2,
		/*पूर्णांकo*/resultp1,resultp2);
		अगर(Dbl_isone_hidden(resultp1))
		    अणु
		    Dbl_copytoptr(resultp1,resultp2,dstptr);
		    वापस(NOEXCEPTION);
		    पूर्ण
		पूर्ण
	    अगर(Is_underflowtrap_enabled())
		अणु
		/* need to normalize result */
	    	sign_save = Dbl_signextendedsign(resultp1);
		Dbl_leftshअगरtby1(resultp1,resultp2);
		Dbl_normalize(resultp1,resultp2,result_exponent);
		Dbl_set_sign(resultp1,/*using*/sign_save);
                Dbl_setwrapped_exponent(resultp1,result_exponent,unfl);
	        Dbl_copytoptr(resultp1,resultp2,dstptr);
		/* inexact = FALSE */
	        वापस(UNDERFLOWEXCEPTION);
		पूर्ण
	    Dbl_copytoptr(resultp1,resultp2,dstptr);
	    वापस(NOEXCEPTION);
	    पूर्ण
	right_exponent = 1;	/* Set exponent to reflect dअगरferent bias
				 * with denomalized numbers. */
	पूर्ण
    अन्यथा
	अणु
	Dbl_clear_signexponent_set_hidden(rightp1);
	पूर्ण
    Dbl_clear_exponent_set_hidden(leftp1);
    dअगरf_exponent = result_exponent - right_exponent;

    /* 
     * Special हाल alignment of opeअक्रमs that would क्रमce alignment 
     * beyond the extent of the extension.  A further optimization
     * could special हाल this but only reduces the path length क्रम this
     * infrequent हाल.
     */
    अगर(dअगरf_exponent > DBL_THRESHOLD)
	अणु
	dअगरf_exponent = DBL_THRESHOLD;
	पूर्ण
    
    /* Align right opeअक्रम by shअगरting to right */
    Dbl_right_align(/*opeअक्रम*/rightp1,rightp2,/*shअगरted by*/dअगरf_exponent,
    /*and lower to*/extent);

    /* Treat sum and dअगरference of the opeअक्रमs separately. */
    अगर( (/*चिन्हित*/पूर्णांक) save < 0 )
	अणु
	/*
	 * Dअगरference of the two opeअक्रमs.  Their can be no overflow.  A
	 * borrow can occur out of the hidden bit and क्रमce a post
	 * normalization phase.
	 */
	Dbl_subtract_withextension(leftp1,leftp2,/*minus*/rightp1,rightp2,
	/*with*/extent,/*पूर्णांकo*/resultp1,resultp2);
	अगर(Dbl_iszero_hidden(resultp1))
	    अणु
	    /* Handle normalization */
	    /* A straight क्रमward algorithm would now shअगरt the result
	     * and extension left until the hidden bit becomes one.  Not
	     * all of the extension bits need participate in the shअगरt.
	     * Only the two most signअगरicant bits (round and guard) are
	     * needed.  If only a single shअगरt is needed then the guard
	     * bit becomes a signअगरicant low order bit and the extension
	     * must participate in the rounding.  If more than a single 
	     * shअगरt is needed, then all bits to the right of the guard 
	     * bit are zeros, and the guard bit may or may not be zero. */
	    sign_save = Dbl_signextendedsign(resultp1);
            Dbl_leftshअगरtby1_withextent(resultp1,resultp2,extent,resultp1,resultp2);

            /* Need to check क्रम a zero result.  The sign and exponent
	     * fields have alपढ़ोy been zeroed.  The more efficient test
	     * of the full object can be used.
	     */
    	    अगर(Dbl_iszero(resultp1,resultp2))
		/* Must have been "x-x" or "x+(-x)". */
		अणु
		अगर(Is_rounding_mode(ROUNDMINUS)) Dbl_setone_sign(resultp1);
		Dbl_copytoptr(resultp1,resultp2,dstptr);
		वापस(NOEXCEPTION);
		पूर्ण
	    result_exponent--;
	    /* Look to see अगर normalization is finished. */
	    अगर(Dbl_isone_hidden(resultp1))
		अणु
		अगर(result_exponent==0)
		    अणु
		    /* Denormalized, exponent should be zero.  Left opeअक्रम *
		     * was normalized, so extent (guard, round) was zero    */
		    जाओ underflow;
		    पूर्ण
		अन्यथा
		    अणु
		    /* No further normalization is needed. */
		    Dbl_set_sign(resultp1,/*using*/sign_save);
	    	    Ext_leftshअगरtby1(extent);
		    जाओ round;
		    पूर्ण
		पूर्ण

	    /* Check क्रम denormalized, exponent should be zero.  Left    *
	     * opeअक्रम was normalized, so extent (guard, round) was zero */
	    अगर(!(underflowtrap = Is_underflowtrap_enabled()) &&
	       result_exponent==0) जाओ underflow;

	    /* Shअगरt extension to complete one bit of normalization and
	     * update exponent. */
	    Ext_leftshअगरtby1(extent);

	    /* Discover first one bit to determine shअगरt amount.  Use a
	     * modअगरied binary search.  We have alपढ़ोy shअगरted the result
	     * one position right and still not found a one so the reमुख्यder
	     * of the extension must be zero and simplअगरies rounding. */
	    /* Scan bytes */
	    जबतक(Dbl_iszero_hiddenhigh7mantissa(resultp1))
		अणु
		Dbl_leftshअगरtby8(resultp1,resultp2);
		अगर((result_exponent -= 8) <= 0  && !underflowtrap)
		    जाओ underflow;
		पूर्ण
	    /* Now narrow it करोwn to the nibble */
	    अगर(Dbl_iszero_hiddenhigh3mantissa(resultp1))
		अणु
		/* The lower nibble contains the normalizing one */
		Dbl_leftshअगरtby4(resultp1,resultp2);
		अगर((result_exponent -= 4) <= 0 && !underflowtrap)
		    जाओ underflow;
		पूर्ण
	    /* Select हाल were first bit is set (alपढ़ोy normalized)
	     * otherwise select the proper shअगरt. */
	    अगर((jumpsize = Dbl_hiddenhigh3mantissa(resultp1)) > 7)
		अणु
		/* Alपढ़ोy normalized */
		अगर(result_exponent <= 0) जाओ underflow;
		Dbl_set_sign(resultp1,/*using*/sign_save);
		Dbl_set_exponent(resultp1,/*using*/result_exponent);
		Dbl_copytoptr(resultp1,resultp2,dstptr);
		वापस(NOEXCEPTION);
		पूर्ण
	    Dbl_sethigh4bits(resultp1,/*using*/sign_save);
	    चयन(jumpsize) 
		अणु
		हाल 1:
		    अणु
		    Dbl_leftshअगरtby3(resultp1,resultp2);
		    result_exponent -= 3;
		    अवरोध;
		    पूर्ण
		हाल 2:
		हाल 3:
		    अणु
		    Dbl_leftshअगरtby2(resultp1,resultp2);
		    result_exponent -= 2;
		    अवरोध;
		    पूर्ण
		हाल 4:
		हाल 5:
		हाल 6:
		हाल 7:
		    अणु
		    Dbl_leftshअगरtby1(resultp1,resultp2);
		    result_exponent -= 1;
		    अवरोध;
		    पूर्ण
		पूर्ण
	    अगर(result_exponent > 0) 
		अणु
		Dbl_set_exponent(resultp1,/*using*/result_exponent);
		Dbl_copytoptr(resultp1,resultp2,dstptr);
		वापस(NOEXCEPTION); 	/* Sign bit is alपढ़ोy set */
		पूर्ण
	    /* Fixup potential underflows */
	  underflow:
	    अगर(Is_underflowtrap_enabled())
		अणु
		Dbl_set_sign(resultp1,sign_save);
                Dbl_setwrapped_exponent(resultp1,result_exponent,unfl);
		Dbl_copytoptr(resultp1,resultp2,dstptr);
		/* inexact = FALSE */
		वापस(UNDERFLOWEXCEPTION);
		पूर्ण
	    /* 
	     * Since we cannot get an inexact denormalized result,
	     * we can now वापस.
	     */
	    Dbl_fix_overshअगरt(resultp1,resultp2,(1-result_exponent),extent);
	    Dbl_clear_signexponent(resultp1);
	    Dbl_set_sign(resultp1,sign_save);
	    Dbl_copytoptr(resultp1,resultp2,dstptr);
	    वापस(NOEXCEPTION);
	    पूर्ण /* end अगर(hidden...)... */
	/* Fall through and round */
	पूर्ण /* end अगर(save < 0)... */
    अन्यथा 
	अणु
	/* Add magnitudes */
	Dbl_addition(leftp1,leftp2,rightp1,rightp2,/*to*/resultp1,resultp2);
	अगर(Dbl_isone_hiddenoverflow(resultp1))
	    अणु
	    /* Prenormalization required. */
	    Dbl_rightshअगरtby1_withextent(resultp2,extent,extent);
	    Dbl_arithrightshअगरtby1(resultp1,resultp2);
	    result_exponent++;
	    पूर्ण /* end अगर hiddenoverflow... */
	पूर्ण /* end अन्यथा ...add magnitudes... */
    
    /* Round the result.  If the extension is all zeros,then the result is
     * exact.  Otherwise round in the correct direction.  No underflow is
     * possible. If a postnormalization is necessary, then the mantissa is
     * all zeros so no shअगरt is needed. */
  round:
    अगर(Ext_isnotzero(extent))
	अणु
	inexact = TRUE;
	चयन(Rounding_mode())
	    अणु
	    हाल ROUNDNEAREST: /* The शेष. */
	    अगर(Ext_isone_sign(extent))
		अणु
		/* at least 1/2 ulp */
		अगर(Ext_isnotzero_lower(extent)  ||
		  Dbl_isone_lowmantissap2(resultp2))
		    अणु
		    /* either exactly half way and odd or more than 1/2ulp */
		    Dbl_increment(resultp1,resultp2);
		    पूर्ण
		पूर्ण
	    अवरोध;

	    हाल ROUNDPLUS:
	    अगर(Dbl_iszero_sign(resultp1))
		अणु
		/* Round up positive results */
		Dbl_increment(resultp1,resultp2);
		पूर्ण
	    अवरोध;
	    
	    हाल ROUNDMINUS:
	    अगर(Dbl_isone_sign(resultp1))
		अणु
		/* Round करोwn negative results */
		Dbl_increment(resultp1,resultp2);
		पूर्ण
	    
	    हाल ROUNDZERO:;
	    /* truncate is simple */
	    पूर्ण /* end चयन... */
	अगर(Dbl_isone_hiddenoverflow(resultp1)) result_exponent++;
	पूर्ण
    अगर(result_exponent == DBL_अनन्त_EXPONENT)
        अणु
        /* Overflow */
        अगर(Is_overflowtrap_enabled())
	    अणु
	    Dbl_setwrapped_exponent(resultp1,result_exponent,ovfl);
	    Dbl_copytoptr(resultp1,resultp2,dstptr);
	    अगर (inexact)
		अगर (Is_inexacttrap_enabled())
			वापस(OVERFLOWEXCEPTION | INEXACTEXCEPTION);
		अन्यथा Set_inexactflag();
	    वापस(OVERFLOWEXCEPTION);
	    पूर्ण
        अन्यथा
	    अणु
	    inexact = TRUE;
	    Set_overflowflag();
	    Dbl_setoverflow(resultp1,resultp2);
	    पूर्ण
	पूर्ण
    अन्यथा Dbl_set_exponent(resultp1,result_exponent);
    Dbl_copytoptr(resultp1,resultp2,dstptr);
    अगर(inexact) 
	अगर(Is_inexacttrap_enabled())
	    वापस(INEXACTEXCEPTION);
	अन्यथा Set_inexactflag();
    वापस(NOEXCEPTION);
पूर्ण
