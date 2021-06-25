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
 *	@(#)	pa/spmath/sfभाग.c		$Revision: 1.1 $
 *
 *  Purpose:
 *	Single Precision Floating-poपूर्णांक Divide
 *
 *  External Interfaces:
 *	sgl_fभाग(srcptr1,srcptr2,dstptr,status)
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
 *  Single Precision Floating-poपूर्णांक Divide
 */

पूर्णांक
sgl_fभाग (sgl_भग्नing_poपूर्णांक * srcptr1, sgl_भग्नing_poपूर्णांक * srcptr2,
	  sgl_भग्नing_poपूर्णांक * dstptr, अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर अचिन्हित पूर्णांक opnd1, opnd2, opnd3, result;
	रेजिस्टर पूर्णांक dest_exponent, count;
	रेजिस्टर boolean inexact = FALSE, guardbit = FALSE, stickybit = FALSE;
	boolean is_tiny;

	opnd1 = *srcptr1;
	opnd2 = *srcptr2;
	/* 
	 * set sign bit of result 
	 */
	अगर (Sgl_sign(opnd1) ^ Sgl_sign(opnd2)) Sgl_setnegativezero(result);  
	अन्यथा Sgl_setzero(result);
	/*
	 * check first opeअक्रम क्रम NaN's or infinity
	 */
	अगर (Sgl_isinfinity_exponent(opnd1)) अणु
		अगर (Sgl_iszero_mantissa(opnd1)) अणु
			अगर (Sgl_isnotnan(opnd2)) अणु
				अगर (Sgl_isinfinity(opnd2)) अणु
					/* 
					 * invalid since both opeअक्रमs 
					 * are infinity 
					 */
					अगर (Is_invalidtrap_enabled()) 
                                		वापस(INVALIDEXCEPTION);
                                	Set_invalidflag();
                                	Sgl_makequietnan(result);
					*dstptr = result;
					वापस(NOEXCEPTION);
				पूर्ण
				/*
			 	 * वापस infinity
			 	 */
				Sgl_setinfinity_exponenपंचांगantissa(result);
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
	अगर (Sgl_isinfinity_exponent(opnd2)) अणु
		अगर (Sgl_iszero_mantissa(opnd2)) अणु
			/*
			 * वापस zero
			 */
			Sgl_setzero_exponenपंचांगantissa(result);
			*dstptr = result;
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
	 * check क्रम भागision by zero
	 */
	अगर (Sgl_iszero_exponenपंचांगantissa(opnd2)) अणु
		अगर (Sgl_iszero_exponenपंचांगantissa(opnd1)) अणु
			/* invalid since both opeअक्रमs are zero */
			अगर (Is_invalidtrap_enabled()) वापस(INVALIDEXCEPTION);
                        Set_invalidflag();
                        Sgl_makequietnan(result);
			*dstptr = result;
			वापस(NOEXCEPTION);
		पूर्ण
		अगर (Is_भागisionbyzerotrap_enabled())
                        वापस(DIVISIONBYZEROEXCEPTION);
                Set_भागisionbyzeroflag();
                Sgl_setinfinity_exponenपंचांगantissa(result);
		*dstptr = result;
		वापस(NOEXCEPTION);
	पूर्ण
	/*
	 * Generate exponent 
	 */
	dest_exponent = Sgl_exponent(opnd1) - Sgl_exponent(opnd2) + SGL_BIAS;

	/*
	 * Generate mantissa
	 */
	अगर (Sgl_isnotzero_exponent(opnd1)) अणु
		/* set hidden bit */
		Sgl_clear_signexponent_set_hidden(opnd1);
	पूर्ण
	अन्यथा अणु
		/* check क्रम zero */
		अगर (Sgl_iszero_mantissa(opnd1)) अणु
			Sgl_setzero_exponenपंचांगantissa(result);
			*dstptr = result;
			वापस(NOEXCEPTION);
		पूर्ण
                /* is denormalized; want to normalize */
                Sgl_clear_signexponent(opnd1);
                Sgl_leftshअगरtby1(opnd1);
		Sgl_normalize(opnd1,dest_exponent);
	पूर्ण
	/* opnd2 needs to have hidden bit set with msb in hidden bit */
	अगर (Sgl_isnotzero_exponent(opnd2)) अणु
		Sgl_clear_signexponent_set_hidden(opnd2);
	पूर्ण
	अन्यथा अणु
                /* is denormalized; want to normalize */
                Sgl_clear_signexponent(opnd2);
                Sgl_leftshअगरtby1(opnd2);
		जबतक(Sgl_iszero_hiddenhigh7mantissa(opnd2)) अणु
			Sgl_leftshअगरtby8(opnd2);
			dest_exponent += 8;
		पूर्ण
		अगर(Sgl_iszero_hiddenhigh3mantissa(opnd2)) अणु
			Sgl_leftshअगरtby4(opnd2);
			dest_exponent += 4;
		पूर्ण
		जबतक(Sgl_iszero_hidden(opnd2)) अणु
			Sgl_leftshअगरtby1(opnd2);
			dest_exponent += 1;
		पूर्ण
	पूर्ण

	/* Divide the source mantissas */

	/*
	 * A non_restoring भागide algorithm is used.
	 */
	Sgl_subtract(opnd1,opnd2,opnd1);
	Sgl_setzero(opnd3);
	क्रम (count=1;count<=SGL_P && Sgl_all(opnd1);count++) अणु
		Sgl_leftshअगरtby1(opnd1);
		Sgl_leftshअगरtby1(opnd3);
		अगर (Sgl_iszero_sign(opnd1)) अणु
			Sgl_setone_lowmantissa(opnd3);
			Sgl_subtract(opnd1,opnd2,opnd1);
		पूर्ण
		अन्यथा Sgl_addition(opnd1,opnd2,opnd1);
	पूर्ण
	अगर (count <= SGL_P) अणु
		Sgl_leftshअगरtby1(opnd3);
		Sgl_setone_lowmantissa(opnd3);
		Sgl_leftshअगरt(opnd3,SGL_P-count);
		अगर (Sgl_iszero_hidden(opnd3)) अणु
			Sgl_leftshअगरtby1(opnd3);
			dest_exponent--;
		पूर्ण
	पूर्ण
	अन्यथा अणु
		अगर (Sgl_iszero_hidden(opnd3)) अणु
			/* need to get one more bit of result */
			Sgl_leftshअगरtby1(opnd1);
			Sgl_leftshअगरtby1(opnd3);
			अगर (Sgl_iszero_sign(opnd1)) अणु
				Sgl_setone_lowmantissa(opnd3);
				Sgl_subtract(opnd1,opnd2,opnd1);
			पूर्ण
			अन्यथा Sgl_addition(opnd1,opnd2,opnd1);
			dest_exponent--;
		पूर्ण
		अगर (Sgl_iszero_sign(opnd1)) guardbit = TRUE;
		stickybit = Sgl_all(opnd1);
	पूर्ण
	inexact = guardbit | stickybit;

	/* 
	 * round result 
	 */
	अगर (inexact && (dest_exponent > 0 || Is_underflowtrap_enabled())) अणु
		Sgl_clear_signexponent(opnd3);
		चयन (Rounding_mode()) अणु
			हाल ROUNDPLUS: 
				अगर (Sgl_iszero_sign(result)) 
					Sgl_increment_mantissa(opnd3);
				अवरोध;
			हाल ROUNDMINUS: 
				अगर (Sgl_isone_sign(result)) 
					Sgl_increment_mantissa(opnd3);
				अवरोध;
			हाल ROUNDNEAREST:
				अगर (guardbit) अणु
			   	अगर (stickybit || Sgl_isone_lowmantissa(opnd3))
			      	    Sgl_increment_mantissa(opnd3);
				पूर्ण
		पूर्ण
		अगर (Sgl_isone_hidden(opnd3)) dest_exponent++;
	पूर्ण
	Sgl_set_mantissa(result,opnd3);

        /* 
         * Test क्रम overflow
         */
	अगर (dest_exponent >= SGL_अनन्त_EXPONENT) अणु
                /* trap अगर OVERFLOWTRAP enabled */
                अगर (Is_overflowtrap_enabled()) अणु
                        /*
                         * Adjust bias of result
                         */
                        Sgl_setwrapped_exponent(result,dest_exponent,ovfl);
                        *dstptr = result;
                        अगर (inexact) 
                            अगर (Is_inexacttrap_enabled())
                                वापस(OVERFLOWEXCEPTION | INEXACTEXCEPTION);
                            अन्यथा Set_inexactflag();
                        वापस(OVERFLOWEXCEPTION);
                पूर्ण
		Set_overflowflag();
                /* set result to infinity or largest number */
		Sgl_setoverflow(result);
		inexact = TRUE;
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
                        Sgl_setwrapped_exponent(result,dest_exponent,unfl);
                        *dstptr = result;
                        अगर (inexact) 
                            अगर (Is_inexacttrap_enabled())
                                वापस(UNDERFLOWEXCEPTION | INEXACTEXCEPTION);
                            अन्यथा Set_inexactflag();
                        वापस(UNDERFLOWEXCEPTION);
                पूर्ण

		/* Determine अगर should set underflow flag */
		is_tiny = TRUE;
		अगर (dest_exponent == 0 && inexact) अणु
			चयन (Rounding_mode()) अणु
			हाल ROUNDPLUS: 
				अगर (Sgl_iszero_sign(result)) अणु
					Sgl_increment(opnd3);
					अगर (Sgl_isone_hiddenoverflow(opnd3))
                			    is_tiny = FALSE;
					Sgl_decrement(opnd3);
				पूर्ण
				अवरोध;
			हाल ROUNDMINUS: 
				अगर (Sgl_isone_sign(result)) अणु
					Sgl_increment(opnd3);
					अगर (Sgl_isone_hiddenoverflow(opnd3))
                			    is_tiny = FALSE;
					Sgl_decrement(opnd3);
				पूर्ण
				अवरोध;
			हाल ROUNDNEAREST:
				अगर (guardbit && (stickybit || 
				    Sgl_isone_lowmantissa(opnd3))) अणु
				      	Sgl_increment(opnd3);
					अगर (Sgl_isone_hiddenoverflow(opnd3))
                			    is_tiny = FALSE;
					Sgl_decrement(opnd3);
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण

                /*
                 * denormalize result or set to चिन्हित zero
                 */
		stickybit = inexact;
		Sgl_denormalize(opnd3,dest_exponent,guardbit,stickybit,inexact);

		/* वापस rounded number */ 
		अगर (inexact) अणु
			चयन (Rounding_mode()) अणु
			हाल ROUNDPLUS:
				अगर (Sgl_iszero_sign(result)) अणु
					Sgl_increment(opnd3);
				पूर्ण
				अवरोध;
			हाल ROUNDMINUS: 
				अगर (Sgl_isone_sign(result))  अणु
					Sgl_increment(opnd3);
				पूर्ण
				अवरोध;
			हाल ROUNDNEAREST:
				अगर (guardbit && (stickybit || 
				    Sgl_isone_lowmantissa(opnd3))) अणु
			      		Sgl_increment(opnd3);
				पूर्ण
				अवरोध;
			पूर्ण
                	अगर (is_tiny) Set_underflowflag();
                पूर्ण
		Sgl_set_exponenपंचांगantissa(result,opnd3);
	पूर्ण
	अन्यथा Sgl_set_exponent(result,dest_exponent);
	*dstptr = result;
	/* check क्रम inexact */
	अगर (inexact) अणु
		अगर (Is_inexacttrap_enabled()) वापस(INEXACTEXCEPTION);
		अन्यथा  Set_inexactflag();
	पूर्ण
	वापस(NOEXCEPTION);
पूर्ण
