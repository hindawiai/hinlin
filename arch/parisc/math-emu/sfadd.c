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
 *	@(#)	pa/spmath/sfadd.c		$Revision: 1.1 $
 *
 *  Purpose:
 *	Single_add: add two single precision values.
 *
 *  External Interfaces:
 *	sgl_fadd(leftptr, rightptr, dstptr, status)
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
 * Single_add: add two single precision values.
 */
पूर्णांक
sgl_fadd(
    sgl_भग्नing_poपूर्णांक *leftptr,
    sgl_भग्नing_poपूर्णांक *rightptr,
    sgl_भग्नing_poपूर्णांक *dstptr,
    अचिन्हित पूर्णांक *status)
    अणु
    रेजिस्टर अचिन्हित पूर्णांक left, right, result, extent;
    रेजिस्टर अचिन्हित पूर्णांक signless_upper_left, signless_upper_right, save;
    
    
    रेजिस्टर पूर्णांक result_exponent, right_exponent, dअगरf_exponent;
    रेजिस्टर पूर्णांक sign_save, jumpsize;
    रेजिस्टर boolean inexact = FALSE;
    रेजिस्टर boolean underflowtrap;
        
    /* Create local copies of the numbers */
    left = *leftptr;
    right = *rightptr;

    /* A zero "save" helps discover equal opeअक्रमs (क्रम later),  *
     * and is used in swapping opeअक्रमs (अगर needed).             */
    Sgl_xortoपूर्णांकp1(left,right,/*to*/save);

    /*
     * check first opeअक्रम क्रम NaN's or infinity
     */
    अगर ((result_exponent = Sgl_exponent(left)) == SGL_अनन्त_EXPONENT)
	अणु
	अगर (Sgl_iszero_mantissa(left)) 
	    अणु
	    अगर (Sgl_isnotnan(right)) 
		अणु
		अगर (Sgl_isinfinity(right) && save!=0) 
		    अणु
		    /* 
		     * invalid since opeअक्रमs are opposite चिन्हित infinity's
		     */
		    अगर (Is_invalidtrap_enabled()) वापस(INVALIDEXCEPTION);
                    Set_invalidflag();
                    Sgl_makequietnan(result);
		    *dstptr = result;
		    वापस(NOEXCEPTION);
		    पूर्ण
		/*
	 	 * वापस infinity
	 	 */
		*dstptr = left;
		वापस(NOEXCEPTION);
		पूर्ण
	    पूर्ण
	अन्यथा 
	    अणु
            /*
             * is NaN; संकेतing or quiet?
             */
            अगर (Sgl_isone_संकेतing(left)) 
		अणु
               	/* trap अगर INVALIDTRAP enabled */
		अगर (Is_invalidtrap_enabled()) वापस(INVALIDEXCEPTION);
        	/* make NaN quiet */
        	Set_invalidflag();
        	Sgl_set_quiet(left);
        	पूर्ण
	    /* 
	     * is second opeअक्रम a संकेतing NaN? 
	     */
	    अन्यथा अगर (Sgl_is_संकेतingnan(right)) 
		अणु
        	/* trap अगर INVALIDTRAP enabled */
               	अगर (Is_invalidtrap_enabled()) वापस(INVALIDEXCEPTION);
		/* make NaN quiet */
		Set_invalidflag();
		Sgl_set_quiet(right);
		*dstptr = right;
		वापस(NOEXCEPTION);
		पूर्ण
	    /*
 	     * वापस quiet NaN
 	     */
 	    *dstptr = left;
 	    वापस(NOEXCEPTION);
	    पूर्ण
	पूर्ण /* End left NaN or Infinity processing */
    /*
     * check second opeअक्रम क्रम NaN's or infinity
     */
    अगर (Sgl_isinfinity_exponent(right)) 
	अणु
	अगर (Sgl_iszero_mantissa(right)) 
	    अणु
	    /* वापस infinity */
	    *dstptr = right;
	    वापस(NOEXCEPTION);
	    पूर्ण
        /*
         * is NaN; संकेतing or quiet?
         */
        अगर (Sgl_isone_संकेतing(right)) 
	    अणु
            /* trap अगर INVALIDTRAP enabled */
	    अगर (Is_invalidtrap_enabled()) वापस(INVALIDEXCEPTION);
	    /* make NaN quiet */
	    Set_invalidflag();
	    Sgl_set_quiet(right);
	    पूर्ण
	/*
	 * वापस quiet NaN
 	 */
	*dstptr = right;
	वापस(NOEXCEPTION);
    	पूर्ण /* End right NaN or Infinity processing */

    /* Invariant: Must be dealing with finite numbers */

    /* Compare opeअक्रमs by removing the sign */
    Sgl_copytoपूर्णांक_exponenपंचांगantissa(left,signless_upper_left);
    Sgl_copytoपूर्णांक_exponenपंचांगantissa(right,signless_upper_right);

    /* sign dअगरference selects add or sub operation. */
    अगर(Sgl_ismagnitudeless(signless_upper_left,signless_upper_right))
	अणु
	/* Set the left opeअक्रम to the larger one by XOR swap *
	 *  First finish the first word using "save"          */
	Sgl_xorfromपूर्णांकp1(save,right,/*to*/right);
	Sgl_xorfromपूर्णांकp1(save,left,/*to*/left);
	result_exponent = Sgl_exponent(left);
	पूर्ण
    /* Invariant:  left is not smaller than right. */ 

    अगर((right_exponent = Sgl_exponent(right)) == 0)
        अणु
	/* Denormalized opeअक्रमs.  First look क्रम zeroes */
	अगर(Sgl_iszero_mantissa(right)) 
	    अणु
	    /* right is zero */
	    अगर(Sgl_iszero_exponenपंचांगantissa(left))
		अणु
		/* Both opeअक्रमs are zeros */
		अगर(Is_rounding_mode(ROUNDMINUS))
		    अणु
		    Sgl_or_signs(left,/*with*/right);
		    पूर्ण
		अन्यथा
		    अणु
		    Sgl_and_signs(left,/*with*/right);
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
	    	    sign_save = Sgl_signextendedsign(left);
		    Sgl_leftshअगरtby1(left);
		    Sgl_normalize(left,result_exponent);
		    Sgl_set_sign(left,/*using*/sign_save);
		    Sgl_setwrapped_exponent(left,result_exponent,unfl);
		    *dstptr = left;
		    वापस(UNDERFLOWEXCEPTION);
		    पूर्ण
		पूर्ण
	    *dstptr = left;
	    वापस(NOEXCEPTION);
	    पूर्ण

	/* Neither are zeroes */
	Sgl_clear_sign(right);	/* Exponent is alपढ़ोy cleared */
	अगर(result_exponent == 0 )
	    अणु
	    /* Both opeअक्रमs are denormalized.  The result must be exact
	     * and is simply calculated.  A sum could become normalized and a
	     * dअगरference could cancel to a true zero. */
	    अगर( (/*चिन्हित*/पूर्णांक) save < 0 )
		अणु
		Sgl_subtract(left,/*minus*/right,/*पूर्णांकo*/result);
		अगर(Sgl_iszero_mantissa(result))
		    अणु
		    अगर(Is_rounding_mode(ROUNDMINUS))
			अणु
			Sgl_setone_sign(result);
			पूर्ण
		    अन्यथा
			अणु
			Sgl_setzero_sign(result);
			पूर्ण
		    *dstptr = result;
		    वापस(NOEXCEPTION);
		    पूर्ण
		पूर्ण
	    अन्यथा
		अणु
		Sgl_addition(left,right,/*पूर्णांकo*/result);
		अगर(Sgl_isone_hidden(result))
		    अणु
		    *dstptr = result;
		    वापस(NOEXCEPTION);
		    पूर्ण
		पूर्ण
	    अगर(Is_underflowtrap_enabled())
		अणु
		/* need to normalize result */
	    	sign_save = Sgl_signextendedsign(result);
		Sgl_leftshअगरtby1(result);
		Sgl_normalize(result,result_exponent);
		Sgl_set_sign(result,/*using*/sign_save);
                Sgl_setwrapped_exponent(result,result_exponent,unfl);
		*dstptr = result;
		वापस(UNDERFLOWEXCEPTION);
		पूर्ण
	    *dstptr = result;
	    वापस(NOEXCEPTION);
	    पूर्ण
	right_exponent = 1;	/* Set exponent to reflect dअगरferent bias
				 * with denomalized numbers. */
	पूर्ण
    अन्यथा
	अणु
	Sgl_clear_signexponent_set_hidden(right);
	पूर्ण
    Sgl_clear_exponent_set_hidden(left);
    dअगरf_exponent = result_exponent - right_exponent;

    /* 
     * Special हाल alignment of opeअक्रमs that would क्रमce alignment 
     * beyond the extent of the extension.  A further optimization
     * could special हाल this but only reduces the path length क्रम this
     * infrequent हाल.
     */
    अगर(dअगरf_exponent > SGL_THRESHOLD)
	अणु
	dअगरf_exponent = SGL_THRESHOLD;
	पूर्ण
    
    /* Align right opeअक्रम by shअगरting to right */
    Sgl_right_align(/*opeअक्रम*/right,/*shअगरted by*/dअगरf_exponent,
     /*and lower to*/extent);

    /* Treat sum and dअगरference of the opeअक्रमs separately. */
    अगर( (/*चिन्हित*/पूर्णांक) save < 0 )
	अणु
	/*
	 * Dअगरference of the two opeअक्रमs.  Their can be no overflow.  A
	 * borrow can occur out of the hidden bit and क्रमce a post
	 * normalization phase.
	 */
	Sgl_subtract_withextension(left,/*minus*/right,/*with*/extent,/*पूर्णांकo*/result);
	अगर(Sgl_iszero_hidden(result))
	    अणु
	    /* Handle normalization */
	    /* A straightक्रमward algorithm would now shअगरt the result
	     * and extension left until the hidden bit becomes one.  Not
	     * all of the extension bits need participate in the shअगरt.
	     * Only the two most signअगरicant bits (round and guard) are
	     * needed.  If only a single shअगरt is needed then the guard
	     * bit becomes a signअगरicant low order bit and the extension
	     * must participate in the rounding.  If more than a single 
	     * shअगरt is needed, then all bits to the right of the guard 
	     * bit are zeros, and the guard bit may or may not be zero. */
	    sign_save = Sgl_signextendedsign(result);
            Sgl_leftshअगरtby1_withextent(result,extent,result);

            /* Need to check क्रम a zero result.  The sign and exponent
	     * fields have alपढ़ोy been zeroed.  The more efficient test
	     * of the full object can be used.
	     */
    	    अगर(Sgl_iszero(result))
		/* Must have been "x-x" or "x+(-x)". */
		अणु
		अगर(Is_rounding_mode(ROUNDMINUS)) Sgl_setone_sign(result);
		*dstptr = result;
		वापस(NOEXCEPTION);
		पूर्ण
	    result_exponent--;
	    /* Look to see अगर normalization is finished. */
	    अगर(Sgl_isone_hidden(result))
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
		    Sgl_set_sign(result,/*using*/sign_save);
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
	    जबतक(Sgl_iszero_hiddenhigh7mantissa(result))
		अणु
		Sgl_leftshअगरtby8(result);
		अगर((result_exponent -= 8) <= 0  && !underflowtrap)
		    जाओ underflow;
		पूर्ण
	    /* Now narrow it करोwn to the nibble */
	    अगर(Sgl_iszero_hiddenhigh3mantissa(result))
		अणु
		/* The lower nibble contains the normalizing one */
		Sgl_leftshअगरtby4(result);
		अगर((result_exponent -= 4) <= 0 && !underflowtrap)
		    जाओ underflow;
		पूर्ण
	    /* Select हाल were first bit is set (alपढ़ोy normalized)
	     * otherwise select the proper shअगरt. */
	    अगर((jumpsize = Sgl_hiddenhigh3mantissa(result)) > 7)
		अणु
		/* Alपढ़ोy normalized */
		अगर(result_exponent <= 0) जाओ underflow;
		Sgl_set_sign(result,/*using*/sign_save);
		Sgl_set_exponent(result,/*using*/result_exponent);
		*dstptr = result;
		वापस(NOEXCEPTION);
		पूर्ण
	    Sgl_sethigh4bits(result,/*using*/sign_save);
	    चयन(jumpsize) 
		अणु
		हाल 1:
		    अणु
		    Sgl_leftshअगरtby3(result);
		    result_exponent -= 3;
		    अवरोध;
		    पूर्ण
		हाल 2:
		हाल 3:
		    अणु
		    Sgl_leftshअगरtby2(result);
		    result_exponent -= 2;
		    अवरोध;
		    पूर्ण
		हाल 4:
		हाल 5:
		हाल 6:
		हाल 7:
		    अणु
		    Sgl_leftshअगरtby1(result);
		    result_exponent -= 1;
		    अवरोध;
		    पूर्ण
		पूर्ण
	    अगर(result_exponent > 0) 
		अणु
		Sgl_set_exponent(result,/*using*/result_exponent);
		*dstptr = result;
		वापस(NOEXCEPTION); /* Sign bit is alपढ़ोy set */
		पूर्ण
	    /* Fixup potential underflows */
	  underflow:
	    अगर(Is_underflowtrap_enabled())
		अणु
		Sgl_set_sign(result,sign_save);
                Sgl_setwrapped_exponent(result,result_exponent,unfl);
		*dstptr = result;
		/* inexact = FALSE; */
		वापस(UNDERFLOWEXCEPTION);
		पूर्ण
	    /* 
	     * Since we cannot get an inexact denormalized result,
	     * we can now वापस.
	     */
	    Sgl_right_align(result,/*by*/(1-result_exponent),extent);
	    Sgl_clear_signexponent(result);
	    Sgl_set_sign(result,sign_save);
	    *dstptr = result;
	    वापस(NOEXCEPTION);
	    पूर्ण /* end अगर(hidden...)... */
	/* Fall through and round */
	पूर्ण /* end अगर(save < 0)... */
    अन्यथा 
	अणु
	/* Add magnitudes */
	Sgl_addition(left,right,/*to*/result);
	अगर(Sgl_isone_hiddenoverflow(result))
	    अणु
	    /* Prenormalization required. */
	    Sgl_rightshअगरtby1_withextent(result,extent,extent);
	    Sgl_arithrightshअगरtby1(result);
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
		  Sgl_isone_lowmantissa(result))
		    अणु
		    /* either exactly half way and odd or more than 1/2ulp */
		    Sgl_increment(result);
		    पूर्ण
		पूर्ण
	    अवरोध;

	    हाल ROUNDPLUS:
	    अगर(Sgl_iszero_sign(result))
		अणु
		/* Round up positive results */
		Sgl_increment(result);
		पूर्ण
	    अवरोध;
	    
	    हाल ROUNDMINUS:
	    अगर(Sgl_isone_sign(result))
		अणु
		/* Round करोwn negative results */
		Sgl_increment(result);
		पूर्ण
	    
	    हाल ROUNDZERO:;
	    /* truncate is simple */
	    पूर्ण /* end चयन... */
	अगर(Sgl_isone_hiddenoverflow(result)) result_exponent++;
	पूर्ण
    अगर(result_exponent == SGL_अनन्त_EXPONENT)
        अणु
        /* Overflow */
        अगर(Is_overflowtrap_enabled())
	    अणु
	    Sgl_setwrapped_exponent(result,result_exponent,ovfl);
	    *dstptr = result;
	    अगर (inexact)
		अगर (Is_inexacttrap_enabled())
		    वापस(OVERFLOWEXCEPTION | INEXACTEXCEPTION);
		अन्यथा Set_inexactflag();
	    वापस(OVERFLOWEXCEPTION);
	    पूर्ण
        अन्यथा
	    अणु
	    Set_overflowflag();
	    inexact = TRUE;
	    Sgl_setoverflow(result);
	    पूर्ण
	पूर्ण
    अन्यथा Sgl_set_exponent(result,result_exponent);
    *dstptr = result;
    अगर(inexact) 
	अगर(Is_inexacttrap_enabled()) वापस(INEXACTEXCEPTION);
	अन्यथा Set_inexactflag();
    वापस(NOEXCEPTION);
    पूर्ण
