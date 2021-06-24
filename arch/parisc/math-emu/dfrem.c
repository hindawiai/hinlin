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
 *	@(#)	pa/spmath/dfrem.c		$Revision: 1.1 $
 *
 *  Purpose:
 *	Double Precision Floating-poपूर्णांक Reमुख्यder
 *
 *  External Interfaces:
 *	dbl_frem(srcptr1,srcptr2,dstptr,status)
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
 *  Double Precision Floating-poपूर्णांक Reमुख्यder
 */

पूर्णांक
dbl_frem (dbl_भग्नing_poपूर्णांक * srcptr1, dbl_भग्नing_poपूर्णांक * srcptr2,
	  dbl_भग्नing_poपूर्णांक * dstptr, अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर अचिन्हित पूर्णांक opnd1p1, opnd1p2, opnd2p1, opnd2p2;
	रेजिस्टर अचिन्हित पूर्णांक resultp1, resultp2;
	रेजिस्टर पूर्णांक opnd1_exponent, opnd2_exponent, dest_exponent, stepcount;
	रेजिस्टर boolean roundup = FALSE;

	Dbl_copyfromptr(srcptr1,opnd1p1,opnd1p2);
	Dbl_copyfromptr(srcptr2,opnd2p1,opnd2p2);
	/*
	 * check first opeअक्रम क्रम NaN's or infinity
	 */
	अगर ((opnd1_exponent = Dbl_exponent(opnd1p1)) == DBL_अनन्त_EXPONENT) अणु
		अगर (Dbl_iszero_mantissa(opnd1p1,opnd1p2)) अणु
			अगर (Dbl_isnotnan(opnd2p1,opnd2p2)) अणु
				/* invalid since first opeअक्रम is infinity */
				अगर (Is_invalidtrap_enabled()) 
                                	वापस(INVALIDEXCEPTION);
                                Set_invalidflag();
                                Dbl_makequietnan(resultp1,resultp2);
				Dbl_copytoptr(resultp1,resultp2,dstptr);
				वापस(NOEXCEPTION);
			पूर्ण
		पूर्ण
		अन्यथा अणु
                	/*
                 	 * is NaN; संकेतing or quiet?
                 	 */
                	अगर (Dbl_isone_संकेतing(opnd1p1)) अणु
                        	/* trap अगर INVALIDTRAP enabled */
                        	अगर (Is_invalidtrap_enabled()) 
                            		वापस(INVALIDEXCEPTION);
                        	/* make NaN quiet */
                        	Set_invalidflag();
                        	Dbl_set_quiet(opnd1p1);
                	पूर्ण
			/* 
			 * is second opeअक्रम a संकेतing NaN? 
			 */
			अन्यथा अगर (Dbl_is_संकेतingnan(opnd2p1)) अणु
                        	/* trap अगर INVALIDTRAP enabled */
                        	अगर (Is_invalidtrap_enabled()) 
                            		वापस(INVALIDEXCEPTION);
                        	/* make NaN quiet */
                        	Set_invalidflag();
                        	Dbl_set_quiet(opnd2p1);
				Dbl_copytoptr(opnd2p1,opnd2p2,dstptr);
                		वापस(NOEXCEPTION);
			पूर्ण
                	/*
                 	 * वापस quiet NaN
                 	 */
			Dbl_copytoptr(opnd1p1,opnd1p2,dstptr);
                	वापस(NOEXCEPTION);
		पूर्ण
	पूर्ण 
	/*
	 * check second opeअक्रम क्रम NaN's or infinity
	 */
	अगर ((opnd2_exponent = Dbl_exponent(opnd2p1)) == DBL_अनन्त_EXPONENT) अणु
		अगर (Dbl_iszero_mantissa(opnd2p1,opnd2p2)) अणु
			/*
			 * वापस first opeअक्रम
			 */
			Dbl_copytoptr(opnd1p1,opnd1p2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
                /*
                 * is NaN; संकेतing or quiet?
                 */
                अगर (Dbl_isone_संकेतing(opnd2p1)) अणु
                        /* trap अगर INVALIDTRAP enabled */
                        अगर (Is_invalidtrap_enabled()) वापस(INVALIDEXCEPTION);
                        /* make NaN quiet */
                        Set_invalidflag();
                        Dbl_set_quiet(opnd2p1);
                पूर्ण
                /*
                 * वापस quiet NaN
                 */
		Dbl_copytoptr(opnd2p1,opnd2p2,dstptr);
                वापस(NOEXCEPTION);
	पूर्ण
	/*
	 * check second opeअक्रम क्रम zero
	 */
	अगर (Dbl_iszero_exponenपंचांगantissa(opnd2p1,opnd2p2)) अणु
		/* invalid since second opeअक्रम is zero */
		अगर (Is_invalidtrap_enabled()) वापस(INVALIDEXCEPTION);
                Set_invalidflag();
                Dbl_makequietnan(resultp1,resultp2);
		Dbl_copytoptr(resultp1,resultp2,dstptr);
		वापस(NOEXCEPTION);
	पूर्ण

	/* 
	 * get sign of result
	 */
	resultp1 = opnd1p1;  

	/* 
	 * check क्रम denormalized opeअक्रमs
	 */
	अगर (opnd1_exponent == 0) अणु
		/* check क्रम zero */
		अगर (Dbl_iszero_mantissa(opnd1p1,opnd1p2)) अणु
			Dbl_copytoptr(opnd1p1,opnd1p2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
		/* normalize, then जारी */
		opnd1_exponent = 1;
		Dbl_normalize(opnd1p1,opnd1p2,opnd1_exponent);
	पूर्ण
	अन्यथा अणु
		Dbl_clear_signexponent_set_hidden(opnd1p1);
	पूर्ण
	अगर (opnd2_exponent == 0) अणु
		/* normalize, then जारी */
		opnd2_exponent = 1;
		Dbl_normalize(opnd2p1,opnd2p2,opnd2_exponent);
	पूर्ण
	अन्यथा अणु
		Dbl_clear_signexponent_set_hidden(opnd2p1);
	पूर्ण

	/* find result exponent and भागide step loop count */
	dest_exponent = opnd2_exponent - 1;
	stepcount = opnd1_exponent - opnd2_exponent;

	/*
	 * check क्रम opnd1/opnd2 < 1
	 */
	अगर (stepcount < 0) अणु
		/*
		 * check क्रम opnd1/opnd2 > 1/2
		 *
		 * In this हाल n will round to 1, so 
		 *    r = opnd1 - opnd2 
		 */
		अगर (stepcount == -1 && 
		    Dbl_isgreaterthan(opnd1p1,opnd1p2,opnd2p1,opnd2p2)) अणु
			/* set sign */
			Dbl_allp1(resultp1) = ~Dbl_allp1(resultp1);
			/* align opnd2 with opnd1 */
			Dbl_leftshअगरtby1(opnd2p1,opnd2p2); 
			Dbl_subtract(opnd2p1,opnd2p2,opnd1p1,opnd1p2,
			 opnd2p1,opnd2p2);
			/* now normalize */
                	जबतक (Dbl_iszero_hidden(opnd2p1)) अणु
                        	Dbl_leftshअगरtby1(opnd2p1,opnd2p2);
                        	dest_exponent--;
			पूर्ण
			Dbl_set_exponenपंचांगantissa(resultp1,resultp2,opnd2p1,opnd2p2);
			जाओ testक्रमunderflow;
		पूर्ण
		/*
		 * opnd1/opnd2 <= 1/2
		 *
		 * In this हाल n will round to zero, so 
		 *    r = opnd1
		 */
		Dbl_set_exponenपंचांगantissa(resultp1,resultp2,opnd1p1,opnd1p2);
		dest_exponent = opnd1_exponent;
		जाओ testक्रमunderflow;
	पूर्ण

	/*
	 * Generate result
	 *
	 * Do iterative subtract until reमुख्यder is less than opeअक्रम 2.
	 */
	जबतक (stepcount-- > 0 && (Dbl_allp1(opnd1p1) || Dbl_allp2(opnd1p2))) अणु
		अगर (Dbl_isnotlessthan(opnd1p1,opnd1p2,opnd2p1,opnd2p2)) अणु
			Dbl_subtract(opnd1p1,opnd1p2,opnd2p1,opnd2p2,opnd1p1,opnd1p2);
		पूर्ण
		Dbl_leftshअगरtby1(opnd1p1,opnd1p2);
	पूर्ण
	/*
	 * Do last subtract, then determine which way to round अगर reमुख्यder 
	 * is exactly 1/2 of opnd2 
	 */
	अगर (Dbl_isnotlessthan(opnd1p1,opnd1p2,opnd2p1,opnd2p2)) अणु
		Dbl_subtract(opnd1p1,opnd1p2,opnd2p1,opnd2p2,opnd1p1,opnd1p2);
		roundup = TRUE;
	पूर्ण
	अगर (stepcount > 0 || Dbl_iszero(opnd1p1,opnd1p2)) अणु
		/* भागision is exact, reमुख्यder is zero */
		Dbl_setzero_exponenपंचांगantissa(resultp1,resultp2);
		Dbl_copytoptr(resultp1,resultp2,dstptr);
		वापस(NOEXCEPTION);
	पूर्ण

	/* 
	 * Check क्रम हालs where opnd1/opnd2 < n 
	 *
	 * In this हाल the result's sign will be opposite that of
	 * opnd1.  The mantissa also needs some correction.
	 */
	Dbl_leftshअगरtby1(opnd1p1,opnd1p2);
	अगर (Dbl_isgreaterthan(opnd1p1,opnd1p2,opnd2p1,opnd2p2)) अणु
		Dbl_invert_sign(resultp1);
		Dbl_leftshअगरtby1(opnd2p1,opnd2p2);
		Dbl_subtract(opnd2p1,opnd2p2,opnd1p1,opnd1p2,opnd1p1,opnd1p2);
	पूर्ण
	/* check क्रम reमुख्यder being exactly 1/2 of opnd2 */
	अन्यथा अगर (Dbl_isequal(opnd1p1,opnd1p2,opnd2p1,opnd2p2) && roundup) अणु 
		Dbl_invert_sign(resultp1);
	पूर्ण

	/* normalize result's mantissa */
        जबतक (Dbl_iszero_hidden(opnd1p1)) अणु
                dest_exponent--;
                Dbl_leftshअगरtby1(opnd1p1,opnd1p2);
        पूर्ण
	Dbl_set_exponenपंचांगantissa(resultp1,resultp2,opnd1p1,opnd1p2);

        /* 
         * Test क्रम underflow
         */
    testक्रमunderflow:
	अगर (dest_exponent <= 0) अणु
                /* trap अगर UNDERFLOWTRAP enabled */
                अगर (Is_underflowtrap_enabled()) अणु
                        /*
                         * Adjust bias of result
                         */
                        Dbl_setwrapped_exponent(resultp1,dest_exponent,unfl);
			/* frem is always exact */
			Dbl_copytoptr(resultp1,resultp2,dstptr);
			वापस(UNDERFLOWEXCEPTION);
                पूर्ण
                /*
                 * denormalize result or set to चिन्हित zero
                 */
                अगर (dest_exponent >= (1 - DBL_P)) अणु
			Dbl_rightshअगरt_exponenपंचांगantissa(resultp1,resultp2,
			 1-dest_exponent);
                पूर्ण
                अन्यथा अणु
			Dbl_setzero_exponenपंचांगantissa(resultp1,resultp2);
		पूर्ण
	पूर्ण
	अन्यथा Dbl_set_exponent(resultp1,dest_exponent);
	Dbl_copytoptr(resultp1,resultp2,dstptr);
	वापस(NOEXCEPTION);
पूर्ण
