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
 *	@(#)	pa/spmath/dfmpy.c		$Revision: 1.1 $
 *
 *  Purpose:
 *	Double Precision Floating-poपूर्णांक Multiply
 *
 *  External Interfaces:
 *	dbl_fmpy(srcptr1,srcptr2,dstptr,status)
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
 *  Double Precision Floating-poपूर्णांक Multiply
 */

पूर्णांक
dbl_fmpy(
	    dbl_भग्नing_poपूर्णांक *srcptr1,
	    dbl_भग्नing_poपूर्णांक *srcptr2,
	    dbl_भग्नing_poपूर्णांक *dstptr,
	    अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर अचिन्हित पूर्णांक opnd1p1, opnd1p2, opnd2p1, opnd2p2;
	रेजिस्टर अचिन्हित पूर्णांक opnd3p1, opnd3p2, resultp1, resultp2;
	रेजिस्टर पूर्णांक dest_exponent, count;
	रेजिस्टर boolean inexact = FALSE, guardbit = FALSE, stickybit = FALSE;
	boolean is_tiny;

	Dbl_copyfromptr(srcptr1,opnd1p1,opnd1p2);
	Dbl_copyfromptr(srcptr2,opnd2p1,opnd2p2);

	/* 
	 * set sign bit of result 
	 */
	अगर (Dbl_sign(opnd1p1) ^ Dbl_sign(opnd2p1)) 
		Dbl_setnegativezerop1(resultp1); 
	अन्यथा Dbl_setzerop1(resultp1);
	/*
	 * check first opeअक्रम क्रम NaN's or infinity
	 */
	अगर (Dbl_isinfinity_exponent(opnd1p1)) अणु
		अगर (Dbl_iszero_mantissa(opnd1p1,opnd1p2)) अणु
			अगर (Dbl_isnotnan(opnd2p1,opnd2p2)) अणु
				अगर (Dbl_iszero_exponenपंचांगantissa(opnd2p1,opnd2p2)) अणु
					/* 
					 * invalid since opeअक्रमs are infinity 
					 * and zero 
					 */
					अगर (Is_invalidtrap_enabled())
                                		वापस(INVALIDEXCEPTION);
                                	Set_invalidflag();
                                	Dbl_makequietnan(resultp1,resultp2);
					Dbl_copytoptr(resultp1,resultp2,dstptr);
					वापस(NOEXCEPTION);
				पूर्ण
				/*
			 	 * वापस infinity
			 	 */
				Dbl_setinfinity_exponenपंचांगantissa(resultp1,resultp2);
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
	अगर (Dbl_isinfinity_exponent(opnd2p1)) अणु
		अगर (Dbl_iszero_mantissa(opnd2p1,opnd2p2)) अणु
			अगर (Dbl_iszero_exponenपंचांगantissa(opnd1p1,opnd1p2)) अणु
				/* invalid since opeअक्रमs are zero & infinity */
				अगर (Is_invalidtrap_enabled())
                                	वापस(INVALIDEXCEPTION);
                                Set_invalidflag();
                                Dbl_makequietnan(opnd2p1,opnd2p2);
				Dbl_copytoptr(opnd2p1,opnd2p2,dstptr);
				वापस(NOEXCEPTION);
			पूर्ण
			/*
			 * वापस infinity
			 */
			Dbl_setinfinity_exponenपंचांगantissa(resultp1,resultp2);
			Dbl_copytoptr(resultp1,resultp2,dstptr);
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
	 * Generate exponent 
	 */
	dest_exponent = Dbl_exponent(opnd1p1) + Dbl_exponent(opnd2p1) -DBL_BIAS;

	/*
	 * Generate mantissa
	 */
	अगर (Dbl_isnotzero_exponent(opnd1p1)) अणु
		/* set hidden bit */
		Dbl_clear_signexponent_set_hidden(opnd1p1);
	पूर्ण
	अन्यथा अणु
		/* check क्रम zero */
		अगर (Dbl_iszero_mantissa(opnd1p1,opnd1p2)) अणु
			Dbl_setzero_exponenपंचांगantissa(resultp1,resultp2);
			Dbl_copytoptr(resultp1,resultp2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
                /* is denormalized, adjust exponent */
                Dbl_clear_signexponent(opnd1p1);
                Dbl_leftshअगरtby1(opnd1p1,opnd1p2);
		Dbl_normalize(opnd1p1,opnd1p2,dest_exponent);
	पूर्ण
	/* opnd2 needs to have hidden bit set with msb in hidden bit */
	अगर (Dbl_isnotzero_exponent(opnd2p1)) अणु
		Dbl_clear_signexponent_set_hidden(opnd2p1);
	पूर्ण
	अन्यथा अणु
		/* check क्रम zero */
		अगर (Dbl_iszero_mantissa(opnd2p1,opnd2p2)) अणु
			Dbl_setzero_exponenपंचांगantissa(resultp1,resultp2);
			Dbl_copytoptr(resultp1,resultp2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
                /* is denormalized; want to normalize */
                Dbl_clear_signexponent(opnd2p1);
                Dbl_leftshअगरtby1(opnd2p1,opnd2p2);
		Dbl_normalize(opnd2p1,opnd2p2,dest_exponent);
	पूर्ण

	/* Multiply two source mantissas together */

	/* make room क्रम guard bits */
	Dbl_leftshअगरtby7(opnd2p1,opnd2p2);
	Dbl_setzero(opnd3p1,opnd3p2);
        /* 
         * Four bits at a समय are inspected in each loop, and a 
         * simple shअगरt and add multiply algorithm is used. 
         */ 
	क्रम (count=1;count<=DBL_P;count+=4) अणु
		stickybit |= Dlow4p2(opnd3p2);
		Dbl_rightshअगरtby4(opnd3p1,opnd3p2);
		अगर (Dbit28p2(opnd1p2)) अणु
	 		/* Twoword_add should be an ADDC followed by an ADD. */
                        Twoword_add(opnd3p1, opnd3p2, opnd2p1<<3 | opnd2p2>>29, 
				    opnd2p2<<3);
		पूर्ण
		अगर (Dbit29p2(opnd1p2)) अणु
                        Twoword_add(opnd3p1, opnd3p2, opnd2p1<<2 | opnd2p2>>30, 
				    opnd2p2<<2);
		पूर्ण
		अगर (Dbit30p2(opnd1p2)) अणु
                        Twoword_add(opnd3p1, opnd3p2, opnd2p1<<1 | opnd2p2>>31,
				    opnd2p2<<1);
		पूर्ण
		अगर (Dbit31p2(opnd1p2)) अणु
                        Twoword_add(opnd3p1, opnd3p2, opnd2p1, opnd2p2);
		पूर्ण
		Dbl_rightshअगरtby4(opnd1p1,opnd1p2);
	पूर्ण
	अगर (Dbit3p1(opnd3p1)==0) अणु
		Dbl_leftshअगरtby1(opnd3p1,opnd3p2);
	पूर्ण
	अन्यथा अणु
		/* result mantissa >= 2. */
		dest_exponent++;
	पूर्ण
	/* check क्रम denormalized result */
	जबतक (Dbit3p1(opnd3p1)==0) अणु
		Dbl_leftshअगरtby1(opnd3p1,opnd3p2);
		dest_exponent--;
	पूर्ण
	/*
	 * check क्रम guard, sticky and inexact bits 
	 */
	stickybit |= Dallp2(opnd3p2) << 25;
	guardbit = (Dallp2(opnd3p2) << 24) >> 31;
	inexact = guardbit | stickybit;

	/* align result mantissa */
	Dbl_rightshअगरtby8(opnd3p1,opnd3p2);

	/* 
	 * round result 
	 */
	अगर (inexact && (dest_exponent>0 || Is_underflowtrap_enabled())) अणु
		Dbl_clear_signexponent(opnd3p1);
		चयन (Rounding_mode()) अणु
			हाल ROUNDPLUS: 
				अगर (Dbl_iszero_sign(resultp1)) 
					Dbl_increment(opnd3p1,opnd3p2);
				अवरोध;
			हाल ROUNDMINUS: 
				अगर (Dbl_isone_sign(resultp1)) 
					Dbl_increment(opnd3p1,opnd3p2);
				अवरोध;
			हाल ROUNDNEAREST:
				अगर (guardbit) अणु
			   	अगर (stickybit || Dbl_isone_lowmantissap2(opnd3p2))
			      	Dbl_increment(opnd3p1,opnd3p2);
				पूर्ण
		पूर्ण
		अगर (Dbl_isone_hidden(opnd3p1)) dest_exponent++;
	पूर्ण
	Dbl_set_mantissa(resultp1,resultp2,opnd3p1,opnd3p2);

        /* 
         * Test क्रम overflow
         */
	अगर (dest_exponent >= DBL_अनन्त_EXPONENT) अणु
                /* trap अगर OVERFLOWTRAP enabled */
                अगर (Is_overflowtrap_enabled()) अणु
                        /*
                         * Adjust bias of result
                         */
			Dbl_setwrapped_exponent(resultp1,dest_exponent,ovfl);
			Dbl_copytoptr(resultp1,resultp2,dstptr);
			अगर (inexact) 
			    अगर (Is_inexacttrap_enabled())
				वापस (OVERFLOWEXCEPTION | INEXACTEXCEPTION);
			    अन्यथा Set_inexactflag();
			वापस (OVERFLOWEXCEPTION);
                पूर्ण
		inexact = TRUE;
		Set_overflowflag();
                /* set result to infinity or largest number */
		Dbl_setoverflow(resultp1,resultp2);
	पूर्ण
        /* 
         * Test क्रम underflow
         */
	अन्यथा अगर (dest_exponent <= 0) अणु
                /* trap अगर UNDERFLOWTRAP enabled */
                अगर (Is_underflowtrap_enabled()) अणु
                        /*
                         * Adjust bias of result
                         */
			Dbl_setwrapped_exponent(resultp1,dest_exponent,unfl);
			Dbl_copytoptr(resultp1,resultp2,dstptr);
			अगर (inexact) 
			    अगर (Is_inexacttrap_enabled())
				वापस (UNDERFLOWEXCEPTION | INEXACTEXCEPTION);
			    अन्यथा Set_inexactflag();
			वापस (UNDERFLOWEXCEPTION);
                पूर्ण

		/* Determine अगर should set underflow flag */
		is_tiny = TRUE;
		अगर (dest_exponent == 0 && inexact) अणु
			चयन (Rounding_mode()) अणु
			हाल ROUNDPLUS: 
				अगर (Dbl_iszero_sign(resultp1)) अणु
					Dbl_increment(opnd3p1,opnd3p2);
					अगर (Dbl_isone_hiddenoverflow(opnd3p1))
                			    is_tiny = FALSE;
					Dbl_decrement(opnd3p1,opnd3p2);
				पूर्ण
				अवरोध;
			हाल ROUNDMINUS: 
				अगर (Dbl_isone_sign(resultp1)) अणु
					Dbl_increment(opnd3p1,opnd3p2);
					अगर (Dbl_isone_hiddenoverflow(opnd3p1))
                			    is_tiny = FALSE;
					Dbl_decrement(opnd3p1,opnd3p2);
				पूर्ण
				अवरोध;
			हाल ROUNDNEAREST:
				अगर (guardbit && (stickybit || 
				    Dbl_isone_lowmantissap2(opnd3p2))) अणु
				      	Dbl_increment(opnd3p1,opnd3p2);
					अगर (Dbl_isone_hiddenoverflow(opnd3p1))
                			    is_tiny = FALSE;
					Dbl_decrement(opnd3p1,opnd3p2);
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * denormalize result or set to चिन्हित zero
		 */
		stickybit = inexact;
		Dbl_denormalize(opnd3p1,opnd3p2,dest_exponent,guardbit,
		 stickybit,inexact);

		/* वापस zero or smallest number */
		अगर (inexact) अणु
			चयन (Rounding_mode()) अणु
			हाल ROUNDPLUS: 
				अगर (Dbl_iszero_sign(resultp1)) अणु
					Dbl_increment(opnd3p1,opnd3p2);
				पूर्ण
				अवरोध;
			हाल ROUNDMINUS: 
				अगर (Dbl_isone_sign(resultp1)) अणु
					Dbl_increment(opnd3p1,opnd3p2);
				पूर्ण
				अवरोध;
			हाल ROUNDNEAREST:
				अगर (guardbit && (stickybit || 
				    Dbl_isone_lowmantissap2(opnd3p2))) अणु
			      		Dbl_increment(opnd3p1,opnd3p2);
				पूर्ण
				अवरोध;
			पूर्ण
                	अगर (is_tiny) Set_underflowflag();
		पूर्ण
		Dbl_set_exponenपंचांगantissa(resultp1,resultp2,opnd3p1,opnd3p2);
	पूर्ण
	अन्यथा Dbl_set_exponent(resultp1,dest_exponent);
	/* check क्रम inexact */
	Dbl_copytoptr(resultp1,resultp2,dstptr);
	अगर (inexact) अणु
		अगर (Is_inexacttrap_enabled()) वापस(INEXACTEXCEPTION);
		अन्यथा Set_inexactflag();
	पूर्ण
	वापस(NOEXCEPTION);
पूर्ण
