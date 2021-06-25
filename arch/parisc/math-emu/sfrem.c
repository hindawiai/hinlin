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
 *	@(#)	pa/spmath/sfrem.c		$Revision: 1.1 $
 *
 *  Purpose:
 *	Single Precision Floating-poपूर्णांक Reमुख्यder
 *
 *  External Interfaces:
 *	sgl_frem(srcptr1,srcptr2,dstptr,status)
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
 *  Single Precision Floating-poपूर्णांक Reमुख्यder
 */

पूर्णांक
sgl_frem (sgl_भग्नing_poपूर्णांक * srcptr1, sgl_भग्नing_poपूर्णांक * srcptr2,
	  sgl_भग्नing_poपूर्णांक * dstptr, अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर अचिन्हित पूर्णांक opnd1, opnd2, result;
	रेजिस्टर पूर्णांक opnd1_exponent, opnd2_exponent, dest_exponent, stepcount;
	रेजिस्टर boolean roundup = FALSE;

	opnd1 = *srcptr1;
	opnd2 = *srcptr2;
	/*
	 * check first opeअक्रम क्रम NaN's or infinity
	 */
	अगर ((opnd1_exponent = Sgl_exponent(opnd1)) == SGL_अनन्त_EXPONENT) अणु
		अगर (Sgl_iszero_mantissa(opnd1)) अणु
			अगर (Sgl_isnotnan(opnd2)) अणु
				/* invalid since first opeअक्रम is infinity */
				अगर (Is_invalidtrap_enabled()) 
                                	वापस(INVALIDEXCEPTION);
                                Set_invalidflag();
                                Sgl_makequietnan(result);
				*dstptr = result;
				वापस(NOEXCEPTION);
			पूर्ण
		पूर्ण
		अन्यथा अणु
                	/*
                 	 * is NaN; संकेतing or quiet?
                 	 */
                	अगर (Sgl_isone_संकेतing(opnd1)) अणु
                        	/* trap अगर INVALIDTRAP enabled */
                        	अगर (Is_invalidtrap_enabled()) 
                            		वापस(INVALIDEXCEPTION);
                        	/* make NaN quiet */
                        	Set_invalidflag();
                        	Sgl_set_quiet(opnd1);
                	पूर्ण
			/* 
			 * is second opeअक्रम a संकेतing NaN? 
			 */
			अन्यथा अगर (Sgl_is_संकेतingnan(opnd2)) अणु
                        	/* trap अगर INVALIDTRAP enabled */
                        	अगर (Is_invalidtrap_enabled()) 
                            		वापस(INVALIDEXCEPTION);
                        	/* make NaN quiet */
                        	Set_invalidflag();
                        	Sgl_set_quiet(opnd2);
                		*dstptr = opnd2;
                		वापस(NOEXCEPTION);
			पूर्ण
                	/*
                 	 * वापस quiet NaN
                 	 */
                	*dstptr = opnd1;
                	वापस(NOEXCEPTION);
		पूर्ण
	पूर्ण 
	/*
	 * check second opeअक्रम क्रम NaN's or infinity
	 */
	अगर ((opnd2_exponent = Sgl_exponent(opnd2)) == SGL_अनन्त_EXPONENT) अणु
		अगर (Sgl_iszero_mantissa(opnd2)) अणु
			/*
			 * वापस first opeअक्रम
			 */
                	*dstptr = opnd1;
			वापस(NOEXCEPTION);
		पूर्ण
                /*
                 * is NaN; संकेतing or quiet?
                 */
                अगर (Sgl_isone_संकेतing(opnd2)) अणु
                        /* trap अगर INVALIDTRAP enabled */
                        अगर (Is_invalidtrap_enabled()) वापस(INVALIDEXCEPTION);
                        /* make NaN quiet */
                        Set_invalidflag();
                        Sgl_set_quiet(opnd2);
                पूर्ण
                /*
                 * वापस quiet NaN
                 */
                *dstptr = opnd2;
                वापस(NOEXCEPTION);
	पूर्ण
	/*
	 * check second opeअक्रम क्रम zero
	 */
	अगर (Sgl_iszero_exponenपंचांगantissa(opnd2)) अणु
		/* invalid since second opeअक्रम is zero */
		अगर (Is_invalidtrap_enabled()) वापस(INVALIDEXCEPTION);
                Set_invalidflag();
                Sgl_makequietnan(result);
		*dstptr = result;
		वापस(NOEXCEPTION);
	पूर्ण

	/* 
	 * get sign of result
	 */
	result = opnd1;  

	/* 
	 * check क्रम denormalized opeअक्रमs
	 */
	अगर (opnd1_exponent == 0) अणु
		/* check क्रम zero */
		अगर (Sgl_iszero_mantissa(opnd1)) अणु
			*dstptr = opnd1;
			वापस(NOEXCEPTION);
		पूर्ण
		/* normalize, then जारी */
		opnd1_exponent = 1;
		Sgl_normalize(opnd1,opnd1_exponent);
	पूर्ण
	अन्यथा अणु
		Sgl_clear_signexponent_set_hidden(opnd1);
	पूर्ण
	अगर (opnd2_exponent == 0) अणु
		/* normalize, then जारी */
		opnd2_exponent = 1;
		Sgl_normalize(opnd2,opnd2_exponent);
	पूर्ण
	अन्यथा अणु
		Sgl_clear_signexponent_set_hidden(opnd2);
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
		अगर (stepcount == -1 && Sgl_isgreaterthan(opnd1,opnd2)) अणु
			Sgl_all(result) = ~Sgl_all(result);   /* set sign */
			/* align opnd2 with opnd1 */
			Sgl_leftshअगरtby1(opnd2); 
			Sgl_subtract(opnd2,opnd1,opnd2);
			/* now normalize */
                	जबतक (Sgl_iszero_hidden(opnd2)) अणु
                        	Sgl_leftshअगरtby1(opnd2);
                        	dest_exponent--;
			पूर्ण
			Sgl_set_exponenपंचांगantissa(result,opnd2);
			जाओ testक्रमunderflow;
		पूर्ण
		/*
		 * opnd1/opnd2 <= 1/2
		 *
		 * In this हाल n will round to zero, so 
		 *    r = opnd1
		 */
		Sgl_set_exponenपंचांगantissa(result,opnd1);
		dest_exponent = opnd1_exponent;
		जाओ testक्रमunderflow;
	पूर्ण

	/*
	 * Generate result
	 *
	 * Do iterative subtract until reमुख्यder is less than opeअक्रम 2.
	 */
	जबतक (stepcount-- > 0 && Sgl_all(opnd1)) अणु
		अगर (Sgl_isnotlessthan(opnd1,opnd2))
			Sgl_subtract(opnd1,opnd2,opnd1);
		Sgl_leftshअगरtby1(opnd1);
	पूर्ण
	/*
	 * Do last subtract, then determine which way to round अगर reमुख्यder 
	 * is exactly 1/2 of opnd2 
	 */
	अगर (Sgl_isnotlessthan(opnd1,opnd2)) अणु
		Sgl_subtract(opnd1,opnd2,opnd1);
		roundup = TRUE;
	पूर्ण
	अगर (stepcount > 0 || Sgl_iszero(opnd1)) अणु
		/* भागision is exact, reमुख्यder is zero */
		Sgl_setzero_exponenपंचांगantissa(result);
		*dstptr = result;
		वापस(NOEXCEPTION);
	पूर्ण

	/* 
	 * Check क्रम हालs where opnd1/opnd2 < n 
	 *
	 * In this हाल the result's sign will be opposite that of
	 * opnd1.  The mantissa also needs some correction.
	 */
	Sgl_leftshअगरtby1(opnd1);
	अगर (Sgl_isgreaterthan(opnd1,opnd2)) अणु
		Sgl_invert_sign(result);
		Sgl_subtract((opnd2<<1),opnd1,opnd1);
	पूर्ण
	/* check क्रम reमुख्यder being exactly 1/2 of opnd2 */
	अन्यथा अगर (Sgl_isequal(opnd1,opnd2) && roundup) अणु 
		Sgl_invert_sign(result);
	पूर्ण

	/* normalize result's mantissa */
        जबतक (Sgl_iszero_hidden(opnd1)) अणु
                dest_exponent--;
                Sgl_leftshअगरtby1(opnd1);
        पूर्ण
	Sgl_set_exponenपंचांगantissa(result,opnd1);

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
                        Sgl_setwrapped_exponent(result,dest_exponent,unfl);
			*dstptr = result;
			/* frem is always exact */
			वापस(UNDERFLOWEXCEPTION);
                पूर्ण
                /*
                 * denormalize result or set to चिन्हित zero
                 */
                अगर (dest_exponent >= (1 - SGL_P)) अणु
			Sgl_rightshअगरt_exponenपंचांगantissa(result,1-dest_exponent);
                पूर्ण
                अन्यथा अणु
			Sgl_setzero_exponenपंचांगantissa(result);
		पूर्ण
	पूर्ण
	अन्यथा Sgl_set_exponent(result,dest_exponent);
	*dstptr = result;
	वापस(NOEXCEPTION);
पूर्ण
