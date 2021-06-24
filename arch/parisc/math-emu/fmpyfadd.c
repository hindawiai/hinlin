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
 *	@(#)	pa/spmath/fmpyfadd.c		$Revision: 1.1 $
 *
 *  Purpose:
 *	Double Floating-poपूर्णांक Multiply Fused Add
 *	Double Floating-poपूर्णांक Multiply Negate Fused Add
 *	Single Floating-poपूर्णांक Multiply Fused Add
 *	Single Floating-poपूर्णांक Multiply Negate Fused Add
 *
 *  External Interfaces:
 *	dbl_fmpyfadd(src1ptr,src2ptr,src3ptr,status,dstptr)
 *	dbl_fmpynfadd(src1ptr,src2ptr,src3ptr,status,dstptr)
 *	sgl_fmpyfadd(src1ptr,src2ptr,src3ptr,status,dstptr)
 *	sgl_fmpynfadd(src1ptr,src2ptr,src3ptr,status,dstptr)
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


/*
 *  Double Floating-poपूर्णांक Multiply Fused Add
 */

पूर्णांक
dbl_fmpyfadd(
	    dbl_भग्नing_poपूर्णांक *src1ptr,
	    dbl_भग्नing_poपूर्णांक *src2ptr,
	    dbl_भग्नing_poपूर्णांक *src3ptr,
	    अचिन्हित पूर्णांक *status,
	    dbl_भग्नing_poपूर्णांक *dstptr)
अणु
	अचिन्हित पूर्णांक opnd1p1, opnd1p2, opnd2p1, opnd2p2, opnd3p1, opnd3p2;
	रेजिस्टर अचिन्हित पूर्णांक पंचांगpresp1, पंचांगpresp2, पंचांगpresp3, पंचांगpresp4;
	अचिन्हित पूर्णांक rightp1, rightp2, rightp3, rightp4;
	अचिन्हित पूर्णांक resultp1, resultp2 = 0, resultp3 = 0, resultp4 = 0;
	रेजिस्टर पूर्णांक mpy_exponent, add_exponent, count;
	boolean inexact = FALSE, is_tiny = FALSE;

	अचिन्हित पूर्णांक signlessleft1, signlessright1, save;
	रेजिस्टर पूर्णांक result_exponent, dअगरf_exponent;
	पूर्णांक sign_save, jumpsize;
	
	Dbl_copyfromptr(src1ptr,opnd1p1,opnd1p2);
	Dbl_copyfromptr(src2ptr,opnd2p1,opnd2p2);
	Dbl_copyfromptr(src3ptr,opnd3p1,opnd3p2);

	/* 
	 * set sign bit of result of multiply
	 */
	अगर (Dbl_sign(opnd1p1) ^ Dbl_sign(opnd2p1)) 
		Dbl_setnegativezerop1(resultp1); 
	अन्यथा Dbl_setzerop1(resultp1);

	/*
	 * Generate multiply exponent 
	 */
	mpy_exponent = Dbl_exponent(opnd1p1) + Dbl_exponent(opnd2p1) - DBL_BIAS;

	/*
	 * check first opeअक्रम क्रम NaN's or infinity
	 */
	अगर (Dbl_isinfinity_exponent(opnd1p1)) अणु
		अगर (Dbl_iszero_mantissa(opnd1p1,opnd1p2)) अणु
			अगर (Dbl_isnotnan(opnd2p1,opnd2p2) &&
			    Dbl_isnotnan(opnd3p1,opnd3p2)) अणु
				अगर (Dbl_iszero_exponenपंचांगantissa(opnd2p1,opnd2p2)) अणु
					/* 
					 * invalid since opeअक्रमs are infinity 
					 * and zero 
					 */
					अगर (Is_invalidtrap_enabled())
						वापस(OPC_2E_INVALIDEXCEPTION);
					Set_invalidflag();
					Dbl_makequietnan(resultp1,resultp2);
					Dbl_copytoptr(resultp1,resultp2,dstptr);
					वापस(NOEXCEPTION);
				पूर्ण
				/*
				 * Check third opeअक्रम क्रम infinity with a
				 *  sign opposite of the multiply result
				 */
				अगर (Dbl_isinfinity(opnd3p1,opnd3p2) &&
				    (Dbl_sign(resultp1) ^ Dbl_sign(opnd3p1))) अणु
					/* 
					 * invalid since attempting a magnitude
					 * subtraction of infinities
					 */
					अगर (Is_invalidtrap_enabled())
						वापस(OPC_2E_INVALIDEXCEPTION);
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
			    		वापस(OPC_2E_INVALIDEXCEPTION);
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
			    		वापस(OPC_2E_INVALIDEXCEPTION);
				/* make NaN quiet */
				Set_invalidflag();
				Dbl_set_quiet(opnd2p1);
				Dbl_copytoptr(opnd2p1,opnd2p2,dstptr);
				वापस(NOEXCEPTION);
			पूर्ण
			/* 
			 * is third opeअक्रम a संकेतing NaN? 
			 */
			अन्यथा अगर (Dbl_is_संकेतingnan(opnd3p1)) अणु
				/* trap अगर INVALIDTRAP enabled */
				अगर (Is_invalidtrap_enabled())
			    		वापस(OPC_2E_INVALIDEXCEPTION);
				/* make NaN quiet */
				Set_invalidflag();
				Dbl_set_quiet(opnd3p1);
				Dbl_copytoptr(opnd3p1,opnd3p2,dstptr);
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
			अगर (Dbl_isnotnan(opnd3p1,opnd3p2)) अणु
				अगर (Dbl_iszero_exponenपंचांगantissa(opnd1p1,opnd1p2)) अणु
					/* 
					 * invalid since multiply opeअक्रमs are
					 * zero & infinity
					 */
					अगर (Is_invalidtrap_enabled())
						वापस(OPC_2E_INVALIDEXCEPTION);
					Set_invalidflag();
					Dbl_makequietnan(opnd2p1,opnd2p2);
					Dbl_copytoptr(opnd2p1,opnd2p2,dstptr);
					वापस(NOEXCEPTION);
				पूर्ण

				/*
				 * Check third opeअक्रम क्रम infinity with a
				 *  sign opposite of the multiply result
				 */
				अगर (Dbl_isinfinity(opnd3p1,opnd3p2) &&
				    (Dbl_sign(resultp1) ^ Dbl_sign(opnd3p1))) अणु
					/* 
					 * invalid since attempting a magnitude
					 * subtraction of infinities
					 */
					अगर (Is_invalidtrap_enabled())
				       		वापस(OPC_2E_INVALIDEXCEPTION);
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
			अगर (Dbl_isone_संकेतing(opnd2p1)) अणु
				/* trap अगर INVALIDTRAP enabled */
				अगर (Is_invalidtrap_enabled())
					वापस(OPC_2E_INVALIDEXCEPTION);
				/* make NaN quiet */
				Set_invalidflag();
				Dbl_set_quiet(opnd2p1);
			पूर्ण
			/* 
			 * is third opeअक्रम a संकेतing NaN? 
			 */
			अन्यथा अगर (Dbl_is_संकेतingnan(opnd3p1)) अणु
			       	/* trap अगर INVALIDTRAP enabled */
			       	अगर (Is_invalidtrap_enabled())
				   		वापस(OPC_2E_INVALIDEXCEPTION);
			       	/* make NaN quiet */
			       	Set_invalidflag();
			       	Dbl_set_quiet(opnd3p1);
				Dbl_copytoptr(opnd3p1,opnd3p2,dstptr);
		       		वापस(NOEXCEPTION);
			पूर्ण
			/*
			 * वापस quiet NaN
			 */
			Dbl_copytoptr(opnd2p1,opnd2p2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
	पूर्ण

	/*
	 * check third opeअक्रम क्रम NaN's or infinity
	 */
	अगर (Dbl_isinfinity_exponent(opnd3p1)) अणु
		अगर (Dbl_iszero_mantissa(opnd3p1,opnd3p2)) अणु
			/* वापस infinity */
			Dbl_copytoptr(opnd3p1,opnd3p2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण अन्यथा अणु
			/*
			 * is NaN; संकेतing or quiet?
			 */
			अगर (Dbl_isone_संकेतing(opnd3p1)) अणु
				/* trap अगर INVALIDTRAP enabled */
				अगर (Is_invalidtrap_enabled())
					वापस(OPC_2E_INVALIDEXCEPTION);
				/* make NaN quiet */
				Set_invalidflag();
				Dbl_set_quiet(opnd3p1);
			पूर्ण
			/*
			 * वापस quiet NaN
 			 */
			Dbl_copytoptr(opnd3p1,opnd3p2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
    	पूर्ण

	/*
	 * Generate multiply mantissa
	 */
	अगर (Dbl_isnotzero_exponent(opnd1p1)) अणु
		/* set hidden bit */
		Dbl_clear_signexponent_set_hidden(opnd1p1);
	पूर्ण
	अन्यथा अणु
		/* check क्रम zero */
		अगर (Dbl_iszero_mantissa(opnd1p1,opnd1p2)) अणु
			/*
			 * Perक्रमm the add opnd3 with zero here.
			 */
			अगर (Dbl_iszero_exponenपंचांगantissa(opnd3p1,opnd3p2)) अणु
				अगर (Is_rounding_mode(ROUNDMINUS)) अणु
					Dbl_or_signs(opnd3p1,resultp1);
				पूर्ण अन्यथा अणु
					Dbl_and_signs(opnd3p1,resultp1);
				पूर्ण
			पूर्ण
			/*
			 * Now let's check क्रम trapped underflow हाल.
			 */
			अन्यथा अगर (Dbl_iszero_exponent(opnd3p1) &&
			         Is_underflowtrap_enabled()) अणु
                    		/* need to normalize results mantissa */
                    		sign_save = Dbl_signextendedsign(opnd3p1);
				result_exponent = 0;
                    		Dbl_leftshअगरtby1(opnd3p1,opnd3p2);
                    		Dbl_normalize(opnd3p1,opnd3p2,result_exponent);
                    		Dbl_set_sign(opnd3p1,/*using*/sign_save);
                    		Dbl_setwrapped_exponent(opnd3p1,result_exponent,
							unfl);
                    		Dbl_copytoptr(opnd3p1,opnd3p2,dstptr);
                    		/* inexact = FALSE */
                    		वापस(OPC_2E_UNDERFLOWEXCEPTION);
			पूर्ण
			Dbl_copytoptr(opnd3p1,opnd3p2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
		/* is denormalized, adjust exponent */
		Dbl_clear_signexponent(opnd1p1);
		Dbl_leftshअगरtby1(opnd1p1,opnd1p2);
		Dbl_normalize(opnd1p1,opnd1p2,mpy_exponent);
	पूर्ण
	/* opnd2 needs to have hidden bit set with msb in hidden bit */
	अगर (Dbl_isnotzero_exponent(opnd2p1)) अणु
		Dbl_clear_signexponent_set_hidden(opnd2p1);
	पूर्ण
	अन्यथा अणु
		/* check क्रम zero */
		अगर (Dbl_iszero_mantissa(opnd2p1,opnd2p2)) अणु
			/*
			 * Perक्रमm the add opnd3 with zero here.
			 */
			अगर (Dbl_iszero_exponenपंचांगantissa(opnd3p1,opnd3p2)) अणु
				अगर (Is_rounding_mode(ROUNDMINUS)) अणु
					Dbl_or_signs(opnd3p1,resultp1);
				पूर्ण अन्यथा अणु
					Dbl_and_signs(opnd3p1,resultp1);
				पूर्ण
			पूर्ण
			/*
			 * Now let's check क्रम trapped underflow हाल.
			 */
			अन्यथा अगर (Dbl_iszero_exponent(opnd3p1) &&
			    Is_underflowtrap_enabled()) अणु
                    		/* need to normalize results mantissa */
                    		sign_save = Dbl_signextendedsign(opnd3p1);
				result_exponent = 0;
                    		Dbl_leftshअगरtby1(opnd3p1,opnd3p2);
                    		Dbl_normalize(opnd3p1,opnd3p2,result_exponent);
                    		Dbl_set_sign(opnd3p1,/*using*/sign_save);
                    		Dbl_setwrapped_exponent(opnd3p1,result_exponent,
							unfl);
                    		Dbl_copytoptr(opnd3p1,opnd3p2,dstptr);
                    		/* inexact = FALSE */
				वापस(OPC_2E_UNDERFLOWEXCEPTION);
			पूर्ण
			Dbl_copytoptr(opnd3p1,opnd3p2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
		/* is denormalized; want to normalize */
		Dbl_clear_signexponent(opnd2p1);
		Dbl_leftshअगरtby1(opnd2p1,opnd2p2);
		Dbl_normalize(opnd2p1,opnd2p2,mpy_exponent);
	पूर्ण

	/* Multiply the first two source mantissas together */

	/* 
	 * The पूर्णांकermediate result will be kept in पंचांगpres,
	 * which needs enough room क्रम 106 bits of mantissa,
	 * so lets call it a Double extended.
	 */
	Dblext_setzero(पंचांगpresp1,पंचांगpresp2,पंचांगpresp3,पंचांगpresp4);

	/* 
	 * Four bits at a समय are inspected in each loop, and a 
	 * simple shअगरt and add multiply algorithm is used. 
	 */ 
	क्रम (count = DBL_P-1; count >= 0; count -= 4) अणु
		Dblext_rightshअगरtby4(पंचांगpresp1,पंचांगpresp2,पंचांगpresp3,पंचांगpresp4);
		अगर (Dbit28p2(opnd1p2)) अणु
	 		/* Fourword_add should be an ADD followed by 3 ADDC's */
			Fourword_add(पंचांगpresp1, पंचांगpresp2, पंचांगpresp3, पंचांगpresp4, 
			 opnd2p1<<3 | opnd2p2>>29, opnd2p2<<3, 0, 0);
		पूर्ण
		अगर (Dbit29p2(opnd1p2)) अणु
			Fourword_add(पंचांगpresp1, पंचांगpresp2, पंचांगpresp3, पंचांगpresp4,
			 opnd2p1<<2 | opnd2p2>>30, opnd2p2<<2, 0, 0);
		पूर्ण
		अगर (Dbit30p2(opnd1p2)) अणु
			Fourword_add(पंचांगpresp1, पंचांगpresp2, पंचांगpresp3, पंचांगpresp4,
			 opnd2p1<<1 | opnd2p2>>31, opnd2p2<<1, 0, 0);
		पूर्ण
		अगर (Dbit31p2(opnd1p2)) अणु
			Fourword_add(पंचांगpresp1, पंचांगpresp2, पंचांगpresp3, पंचांगpresp4,
			 opnd2p1, opnd2p2, 0, 0);
		पूर्ण
		Dbl_rightshअगरtby4(opnd1p1,opnd1p2);
	पूर्ण
	अगर (Is_dexthiddenoverflow(पंचांगpresp1)) अणु
		/* result mantissa >= 2 (mantissa overflow) */
		mpy_exponent++;
		Dblext_rightshअगरtby1(पंचांगpresp1,पंचांगpresp2,पंचांगpresp3,पंचांगpresp4);
	पूर्ण

	/*
	 * Restore the sign of the mpy result which was saved in resultp1.
	 * The exponent will जारी to be kept in mpy_exponent.
	 */
	Dblext_set_sign(पंचांगpresp1,Dbl_sign(resultp1));

	/* 
	 * No rounding is required, since the result of the multiply
	 * is exact in the extended क्रमmat.
	 */

	/*
	 * Now we are पढ़ोy to perक्रमm the add portion of the operation.
	 *
	 * The exponents need to be kept as पूर्णांकegers क्रम now, since the
	 * multiply result might not fit पूर्णांकo the exponent field.  We
	 * can't overflow or underflow because of this yet, since the
	 * add could bring the final result back पूर्णांकo range.
	 */
	add_exponent = Dbl_exponent(opnd3p1);

	/*
	 * Check क्रम denormalized or zero add opeअक्रम.
	 */
	अगर (add_exponent == 0) अणु
		/* check क्रम zero */
		अगर (Dbl_iszero_mantissa(opnd3p1,opnd3p2)) अणु
			/* right is zero */
			/* Left can't be zero and must be result.
			 *
			 * The final result is now in पंचांगpres and mpy_exponent,
			 * and needs to be rounded and squeezed back पूर्णांकo
			 * द्विगुन precision क्रमmat from द्विगुन extended.
			 */
			result_exponent = mpy_exponent;
			Dblext_copy(पंचांगpresp1,पंचांगpresp2,पंचांगpresp3,पंचांगpresp4,
				resultp1,resultp2,resultp3,resultp4);
			sign_save = Dbl_signextendedsign(resultp1);/*save sign*/
			जाओ round;
		पूर्ण

		/* 
		 * Neither are zeroes.  
		 * Adjust exponent and normalize add opeअक्रम.
		 */
		sign_save = Dbl_signextendedsign(opnd3p1);	/* save sign */
		Dbl_clear_signexponent(opnd3p1);
		Dbl_leftshअगरtby1(opnd3p1,opnd3p2);
		Dbl_normalize(opnd3p1,opnd3p2,add_exponent);
		Dbl_set_sign(opnd3p1,sign_save);	/* restore sign */
	पूर्ण अन्यथा अणु
		Dbl_clear_exponent_set_hidden(opnd3p1);
	पूर्ण
	/*
	 * Copy opnd3 to the द्विगुन extended variable called right.
	 */
	Dbl_copyto_dblext(opnd3p1,opnd3p2,rightp1,rightp2,rightp3,rightp4);

	/*
	 * A zero "save" helps discover equal opeअक्रमs (क्रम later),
	 * and is used in swapping opeअक्रमs (अगर needed).
	 */
	Dblext_xortoपूर्णांकp1(पंचांगpresp1,rightp1,/*to*/save);

	/*
	 * Compare magnitude of opeअक्रमs.
	 */
	Dblext_copytoपूर्णांक_exponenपंचांगantissap1(पंचांगpresp1,signlessleft1);
	Dblext_copytoपूर्णांक_exponenपंचांगantissap1(rightp1,signlessright1);
	अगर (mpy_exponent < add_exponent || mpy_exponent == add_exponent &&
	    Dblext_ismagnitudeless(पंचांगpresp2,rightp2,signlessleft1,signlessright1))अणु
		/*
		 * Set the left opeअक्रम to the larger one by XOR swap.
		 * First finish the first word "save".
		 */
		Dblext_xorfromपूर्णांकp1(save,rightp1,/*to*/rightp1);
		Dblext_xorfromपूर्णांकp1(save,पंचांगpresp1,/*to*/पंचांगpresp1);
		Dblext_swap_lower(पंचांगpresp2,पंचांगpresp3,पंचांगpresp4,
			rightp2,rightp3,rightp4);
		/* also setup exponents used in rest of routine */
		dअगरf_exponent = add_exponent - mpy_exponent;
		result_exponent = add_exponent;
	पूर्ण अन्यथा अणु
		/* also setup exponents used in rest of routine */
		dअगरf_exponent = mpy_exponent - add_exponent;
		result_exponent = mpy_exponent;
	पूर्ण
	/* Invariant: left is not smaller than right. */

	/*
	 * Special हाल alignment of opeअक्रमs that would क्रमce alignment
	 * beyond the extent of the extension.  A further optimization
	 * could special हाल this but only reduces the path length क्रम
	 * this infrequent हाल.
	 */
	अगर (dअगरf_exponent > DBLEXT_THRESHOLD) अणु
		dअगरf_exponent = DBLEXT_THRESHOLD;
	पूर्ण

	/* Align right opeअक्रम by shअगरting it to the right */
	Dblext_clear_sign(rightp1);
	Dblext_right_align(rightp1,rightp2,rightp3,rightp4,
		/*shअगरted by*/dअगरf_exponent);
	
	/* Treat sum and dअगरference of the opeअक्रमs separately. */
	अगर ((पूर्णांक)save < 0) अणु
		/*
		 * Dअगरference of the two opeअक्रमs.  Overflow can occur अगर the
		 * multiply overflowed.  A borrow can occur out of the hidden
		 * bit and क्रमce a post normalization phase.
		 */
		Dblext_subtract(पंचांगpresp1,पंचांगpresp2,पंचांगpresp3,पंचांगpresp4,
			rightp1,rightp2,rightp3,rightp4,
			resultp1,resultp2,resultp3,resultp4);
		sign_save = Dbl_signextendedsign(resultp1);
		अगर (Dbl_iszero_hidden(resultp1)) अणु
			/* Handle normalization */
		/* A straightक्रमward algorithm would now shअगरt the
		 * result and extension left until the hidden bit
		 * becomes one.  Not all of the extension bits need
		 * participate in the shअगरt.  Only the two most 
		 * signअगरicant bits (round and guard) are needed.
		 * If only a single shअगरt is needed then the guard
		 * bit becomes a signअगरicant low order bit and the
		 * extension must participate in the rounding.
		 * If more than a single shअगरt is needed, then all
		 * bits to the right of the guard bit are zeros, 
		 * and the guard bit may or may not be zero. */
			Dblext_leftshअगरtby1(resultp1,resultp2,resultp3,
				resultp4);

			/* Need to check क्रम a zero result.  The sign and
			 * exponent fields have alपढ़ोy been zeroed.  The more
			 * efficient test of the full object can be used.
			 */
			 अगर(Dblext_iszero(resultp1,resultp2,resultp3,resultp4))अणु
				/* Must have been "x-x" or "x+(-x)". */
				अगर (Is_rounding_mode(ROUNDMINUS))
					Dbl_setone_sign(resultp1);
				Dbl_copytoptr(resultp1,resultp2,dstptr);
				वापस(NOEXCEPTION);
			पूर्ण
			result_exponent--;

			/* Look to see अगर normalization is finished. */
			अगर (Dbl_isone_hidden(resultp1)) अणु
				/* No further normalization is needed */
				जाओ round;
			पूर्ण

			/* Discover first one bit to determine shअगरt amount.
			 * Use a modअगरied binary search.  We have alपढ़ोy
			 * shअगरted the result one position right and still
			 * not found a one so the reमुख्यder of the extension
			 * must be zero and simplअगरies rounding. */
			/* Scan bytes */
			जबतक (Dbl_iszero_hiddenhigh7mantissa(resultp1)) अणु
				Dblext_leftshअगरtby8(resultp1,resultp2,resultp3,resultp4);
				result_exponent -= 8;
			पूर्ण
			/* Now narrow it करोwn to the nibble */
			अगर (Dbl_iszero_hiddenhigh3mantissa(resultp1)) अणु
				/* The lower nibble contains the
				 * normalizing one */
				Dblext_leftshअगरtby4(resultp1,resultp2,resultp3,resultp4);
				result_exponent -= 4;
			पूर्ण
			/* Select हाल where first bit is set (alपढ़ोy
			 * normalized) otherwise select the proper shअगरt. */
			jumpsize = Dbl_hiddenhigh3mantissa(resultp1);
			अगर (jumpsize <= 7) चयन(jumpsize) अणु
			हाल 1:
				Dblext_leftshअगरtby3(resultp1,resultp2,resultp3,
					resultp4);
				result_exponent -= 3;
				अवरोध;
			हाल 2:
			हाल 3:
				Dblext_leftshअगरtby2(resultp1,resultp2,resultp3,
					resultp4);
				result_exponent -= 2;
				अवरोध;
			हाल 4:
			हाल 5:
			हाल 6:
			हाल 7:
				Dblext_leftshअगरtby1(resultp1,resultp2,resultp3,
					resultp4);
				result_exponent -= 1;
				अवरोध;
			पूर्ण
		पूर्ण /* end अगर (hidden...)... */
	/* Fall through and round */
	पूर्ण /* end अगर (save < 0)... */
	अन्यथा अणु
		/* Add magnitudes */
		Dblext_addition(पंचांगpresp1,पंचांगpresp2,पंचांगpresp3,पंचांगpresp4,
			rightp1,rightp2,rightp3,rightp4,
			/*to*/resultp1,resultp2,resultp3,resultp4);
		sign_save = Dbl_signextendedsign(resultp1);
		अगर (Dbl_isone_hiddenoverflow(resultp1)) अणु
	    		/* Prenormalization required. */
	    		Dblext_arithrightshअगरtby1(resultp1,resultp2,resultp3,
				resultp4);
	    		result_exponent++;
		पूर्ण /* end अगर hiddenoverflow... */
	पूर्ण /* end अन्यथा ...add magnitudes... */

	/* Round the result.  If the extension and lower two words are
	 * all zeros, then the result is exact.  Otherwise round in the
	 * correct direction.  Underflow is possible. If a postnormalization
	 * is necessary, then the mantissa is all zeros so no shअगरt is needed.
	 */
  round:
	अगर (result_exponent <= 0 && !Is_underflowtrap_enabled()) अणु
		Dblext_denormalize(resultp1,resultp2,resultp3,resultp4,
			result_exponent,is_tiny);
	पूर्ण
	Dbl_set_sign(resultp1,/*using*/sign_save);
	अगर (Dblext_isnotzero_mantissap3(resultp3) || 
	    Dblext_isnotzero_mantissap4(resultp4)) अणु
		inexact = TRUE;
		चयन(Rounding_mode()) अणु
		हाल ROUNDNEAREST: /* The शेष. */
			अगर (Dblext_isone_highp3(resultp3)) अणु
				/* at least 1/2 ulp */
				अगर (Dblext_isnotzero_low31p3(resultp3) ||
				    Dblext_isnotzero_mantissap4(resultp4) ||
				    Dblext_isone_lowp2(resultp2)) अणु
					/* either exactly half way and odd or
					 * more than 1/2ulp */
					Dbl_increment(resultp1,resultp2);
				पूर्ण
			पूर्ण
	    		अवरोध;

		हाल ROUNDPLUS:
	    		अगर (Dbl_iszero_sign(resultp1)) अणु
				/* Round up positive results */
				Dbl_increment(resultp1,resultp2);
			पूर्ण
			अवरोध;
	    
		हाल ROUNDMINUS:
	    		अगर (Dbl_isone_sign(resultp1)) अणु
				/* Round करोwn negative results */
				Dbl_increment(resultp1,resultp2);
			पूर्ण
	    
		हाल ROUNDZERO:;
			/* truncate is simple */
		पूर्ण /* end चयन... */
		अगर (Dbl_isone_hiddenoverflow(resultp1)) result_exponent++;
	पूर्ण
	अगर (result_exponent >= DBL_अनन्त_EXPONENT) अणु
                /* trap अगर OVERFLOWTRAP enabled */
                अगर (Is_overflowtrap_enabled()) अणु
                        /*
                         * Adjust bias of result
                         */
                        Dbl_setwrapped_exponent(resultp1,result_exponent,ovfl);
                        Dbl_copytoptr(resultp1,resultp2,dstptr);
                        अगर (inexact)
                            अगर (Is_inexacttrap_enabled())
                                वापस (OPC_2E_OVERFLOWEXCEPTION |
					OPC_2E_INEXACTEXCEPTION);
                            अन्यथा Set_inexactflag();
                        वापस (OPC_2E_OVERFLOWEXCEPTION);
                पूर्ण
                inexact = TRUE;
                Set_overflowflag();
                /* set result to infinity or largest number */
                Dbl_setoverflow(resultp1,resultp2);

	पूर्ण अन्यथा अगर (result_exponent <= 0) अणु	/* underflow हाल */
		अगर (Is_underflowtrap_enabled()) अणु
                        /*
                         * Adjust bias of result
                         */
                	Dbl_setwrapped_exponent(resultp1,result_exponent,unfl);
			Dbl_copytoptr(resultp1,resultp2,dstptr);
                        अगर (inexact)
                            अगर (Is_inexacttrap_enabled())
                                वापस (OPC_2E_UNDERFLOWEXCEPTION |
					OPC_2E_INEXACTEXCEPTION);
                            अन्यथा Set_inexactflag();
	    		वापस(OPC_2E_UNDERFLOWEXCEPTION);
		पूर्ण
		अन्यथा अगर (inexact && is_tiny) Set_underflowflag();
	पूर्ण
	अन्यथा Dbl_set_exponent(resultp1,result_exponent);
	Dbl_copytoptr(resultp1,resultp2,dstptr);
	अगर (inexact) 
		अगर (Is_inexacttrap_enabled()) वापस(OPC_2E_INEXACTEXCEPTION);
		अन्यथा Set_inexactflag();
    	वापस(NOEXCEPTION);
पूर्ण

/*
 *  Double Floating-poपूर्णांक Multiply Negate Fused Add
 */

dbl_fmpynfadd(src1ptr,src2ptr,src3ptr,status,dstptr)

dbl_भग्नing_poपूर्णांक *src1ptr, *src2ptr, *src3ptr, *dstptr;
अचिन्हित पूर्णांक *status;
अणु
	अचिन्हित पूर्णांक opnd1p1, opnd1p2, opnd2p1, opnd2p2, opnd3p1, opnd3p2;
	रेजिस्टर अचिन्हित पूर्णांक पंचांगpresp1, पंचांगpresp2, पंचांगpresp3, पंचांगpresp4;
	अचिन्हित पूर्णांक rightp1, rightp2, rightp3, rightp4;
	अचिन्हित पूर्णांक resultp1, resultp2 = 0, resultp3 = 0, resultp4 = 0;
	रेजिस्टर पूर्णांक mpy_exponent, add_exponent, count;
	boolean inexact = FALSE, is_tiny = FALSE;

	अचिन्हित पूर्णांक signlessleft1, signlessright1, save;
	रेजिस्टर पूर्णांक result_exponent, dअगरf_exponent;
	पूर्णांक sign_save, jumpsize;
	
	Dbl_copyfromptr(src1ptr,opnd1p1,opnd1p2);
	Dbl_copyfromptr(src2ptr,opnd2p1,opnd2p2);
	Dbl_copyfromptr(src3ptr,opnd3p1,opnd3p2);

	/* 
	 * set sign bit of result of multiply
	 */
	अगर (Dbl_sign(opnd1p1) ^ Dbl_sign(opnd2p1)) 
		Dbl_setzerop1(resultp1);
	अन्यथा
		Dbl_setnegativezerop1(resultp1); 

	/*
	 * Generate multiply exponent 
	 */
	mpy_exponent = Dbl_exponent(opnd1p1) + Dbl_exponent(opnd2p1) - DBL_BIAS;

	/*
	 * check first opeअक्रम क्रम NaN's or infinity
	 */
	अगर (Dbl_isinfinity_exponent(opnd1p1)) अणु
		अगर (Dbl_iszero_mantissa(opnd1p1,opnd1p2)) अणु
			अगर (Dbl_isnotnan(opnd2p1,opnd2p2) &&
			    Dbl_isnotnan(opnd3p1,opnd3p2)) अणु
				अगर (Dbl_iszero_exponenपंचांगantissa(opnd2p1,opnd2p2)) अणु
					/* 
					 * invalid since opeअक्रमs are infinity 
					 * and zero 
					 */
					अगर (Is_invalidtrap_enabled())
						वापस(OPC_2E_INVALIDEXCEPTION);
					Set_invalidflag();
					Dbl_makequietnan(resultp1,resultp2);
					Dbl_copytoptr(resultp1,resultp2,dstptr);
					वापस(NOEXCEPTION);
				पूर्ण
				/*
				 * Check third opeअक्रम क्रम infinity with a
				 *  sign opposite of the multiply result
				 */
				अगर (Dbl_isinfinity(opnd3p1,opnd3p2) &&
				    (Dbl_sign(resultp1) ^ Dbl_sign(opnd3p1))) अणु
					/* 
					 * invalid since attempting a magnitude
					 * subtraction of infinities
					 */
					अगर (Is_invalidtrap_enabled())
						वापस(OPC_2E_INVALIDEXCEPTION);
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
			    		वापस(OPC_2E_INVALIDEXCEPTION);
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
			    		वापस(OPC_2E_INVALIDEXCEPTION);
				/* make NaN quiet */
				Set_invalidflag();
				Dbl_set_quiet(opnd2p1);
				Dbl_copytoptr(opnd2p1,opnd2p2,dstptr);
				वापस(NOEXCEPTION);
			पूर्ण
			/* 
			 * is third opeअक्रम a संकेतing NaN? 
			 */
			अन्यथा अगर (Dbl_is_संकेतingnan(opnd3p1)) अणु
				/* trap अगर INVALIDTRAP enabled */
				अगर (Is_invalidtrap_enabled())
			    		वापस(OPC_2E_INVALIDEXCEPTION);
				/* make NaN quiet */
				Set_invalidflag();
				Dbl_set_quiet(opnd3p1);
				Dbl_copytoptr(opnd3p1,opnd3p2,dstptr);
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
			अगर (Dbl_isnotnan(opnd3p1,opnd3p2)) अणु
				अगर (Dbl_iszero_exponenपंचांगantissa(opnd1p1,opnd1p2)) अणु
					/* 
					 * invalid since multiply opeअक्रमs are
					 * zero & infinity
					 */
					अगर (Is_invalidtrap_enabled())
						वापस(OPC_2E_INVALIDEXCEPTION);
					Set_invalidflag();
					Dbl_makequietnan(opnd2p1,opnd2p2);
					Dbl_copytoptr(opnd2p1,opnd2p2,dstptr);
					वापस(NOEXCEPTION);
				पूर्ण

				/*
				 * Check third opeअक्रम क्रम infinity with a
				 *  sign opposite of the multiply result
				 */
				अगर (Dbl_isinfinity(opnd3p1,opnd3p2) &&
				    (Dbl_sign(resultp1) ^ Dbl_sign(opnd3p1))) अणु
					/* 
					 * invalid since attempting a magnitude
					 * subtraction of infinities
					 */
					अगर (Is_invalidtrap_enabled())
				       		वापस(OPC_2E_INVALIDEXCEPTION);
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
			अगर (Dbl_isone_संकेतing(opnd2p1)) अणु
				/* trap अगर INVALIDTRAP enabled */
				अगर (Is_invalidtrap_enabled())
					वापस(OPC_2E_INVALIDEXCEPTION);
				/* make NaN quiet */
				Set_invalidflag();
				Dbl_set_quiet(opnd2p1);
			पूर्ण
			/* 
			 * is third opeअक्रम a संकेतing NaN? 
			 */
			अन्यथा अगर (Dbl_is_संकेतingnan(opnd3p1)) अणु
			       	/* trap अगर INVALIDTRAP enabled */
			       	अगर (Is_invalidtrap_enabled())
				   		वापस(OPC_2E_INVALIDEXCEPTION);
			       	/* make NaN quiet */
			       	Set_invalidflag();
			       	Dbl_set_quiet(opnd3p1);
				Dbl_copytoptr(opnd3p1,opnd3p2,dstptr);
		       		वापस(NOEXCEPTION);
			पूर्ण
			/*
			 * वापस quiet NaN
			 */
			Dbl_copytoptr(opnd2p1,opnd2p2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
	पूर्ण

	/*
	 * check third opeअक्रम क्रम NaN's or infinity
	 */
	अगर (Dbl_isinfinity_exponent(opnd3p1)) अणु
		अगर (Dbl_iszero_mantissa(opnd3p1,opnd3p2)) अणु
			/* वापस infinity */
			Dbl_copytoptr(opnd3p1,opnd3p2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण अन्यथा अणु
			/*
			 * is NaN; संकेतing or quiet?
			 */
			अगर (Dbl_isone_संकेतing(opnd3p1)) अणु
				/* trap अगर INVALIDTRAP enabled */
				अगर (Is_invalidtrap_enabled())
					वापस(OPC_2E_INVALIDEXCEPTION);
				/* make NaN quiet */
				Set_invalidflag();
				Dbl_set_quiet(opnd3p1);
			पूर्ण
			/*
			 * वापस quiet NaN
 			 */
			Dbl_copytoptr(opnd3p1,opnd3p2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
    	पूर्ण

	/*
	 * Generate multiply mantissa
	 */
	अगर (Dbl_isnotzero_exponent(opnd1p1)) अणु
		/* set hidden bit */
		Dbl_clear_signexponent_set_hidden(opnd1p1);
	पूर्ण
	अन्यथा अणु
		/* check क्रम zero */
		अगर (Dbl_iszero_mantissa(opnd1p1,opnd1p2)) अणु
			/*
			 * Perक्रमm the add opnd3 with zero here.
			 */
			अगर (Dbl_iszero_exponenपंचांगantissa(opnd3p1,opnd3p2)) अणु
				अगर (Is_rounding_mode(ROUNDMINUS)) अणु
					Dbl_or_signs(opnd3p1,resultp1);
				पूर्ण अन्यथा अणु
					Dbl_and_signs(opnd3p1,resultp1);
				पूर्ण
			पूर्ण
			/*
			 * Now let's check क्रम trapped underflow हाल.
			 */
			अन्यथा अगर (Dbl_iszero_exponent(opnd3p1) &&
			         Is_underflowtrap_enabled()) अणु
                    		/* need to normalize results mantissa */
                    		sign_save = Dbl_signextendedsign(opnd3p1);
				result_exponent = 0;
                    		Dbl_leftshअगरtby1(opnd3p1,opnd3p2);
                    		Dbl_normalize(opnd3p1,opnd3p2,result_exponent);
                    		Dbl_set_sign(opnd3p1,/*using*/sign_save);
                    		Dbl_setwrapped_exponent(opnd3p1,result_exponent,
							unfl);
                    		Dbl_copytoptr(opnd3p1,opnd3p2,dstptr);
                    		/* inexact = FALSE */
                    		वापस(OPC_2E_UNDERFLOWEXCEPTION);
			पूर्ण
			Dbl_copytoptr(opnd3p1,opnd3p2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
		/* is denormalized, adjust exponent */
		Dbl_clear_signexponent(opnd1p1);
		Dbl_leftshअगरtby1(opnd1p1,opnd1p2);
		Dbl_normalize(opnd1p1,opnd1p2,mpy_exponent);
	पूर्ण
	/* opnd2 needs to have hidden bit set with msb in hidden bit */
	अगर (Dbl_isnotzero_exponent(opnd2p1)) अणु
		Dbl_clear_signexponent_set_hidden(opnd2p1);
	पूर्ण
	अन्यथा अणु
		/* check क्रम zero */
		अगर (Dbl_iszero_mantissa(opnd2p1,opnd2p2)) अणु
			/*
			 * Perक्रमm the add opnd3 with zero here.
			 */
			अगर (Dbl_iszero_exponenपंचांगantissa(opnd3p1,opnd3p2)) अणु
				अगर (Is_rounding_mode(ROUNDMINUS)) अणु
					Dbl_or_signs(opnd3p1,resultp1);
				पूर्ण अन्यथा अणु
					Dbl_and_signs(opnd3p1,resultp1);
				पूर्ण
			पूर्ण
			/*
			 * Now let's check क्रम trapped underflow हाल.
			 */
			अन्यथा अगर (Dbl_iszero_exponent(opnd3p1) &&
			    Is_underflowtrap_enabled()) अणु
                    		/* need to normalize results mantissa */
                    		sign_save = Dbl_signextendedsign(opnd3p1);
				result_exponent = 0;
                    		Dbl_leftshअगरtby1(opnd3p1,opnd3p2);
                    		Dbl_normalize(opnd3p1,opnd3p2,result_exponent);
                    		Dbl_set_sign(opnd3p1,/*using*/sign_save);
                    		Dbl_setwrapped_exponent(opnd3p1,result_exponent,
							unfl);
                    		Dbl_copytoptr(opnd3p1,opnd3p2,dstptr);
                    		/* inexact = FALSE */
                    		वापस(OPC_2E_UNDERFLOWEXCEPTION);
			पूर्ण
			Dbl_copytoptr(opnd3p1,opnd3p2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
		/* is denormalized; want to normalize */
		Dbl_clear_signexponent(opnd2p1);
		Dbl_leftshअगरtby1(opnd2p1,opnd2p2);
		Dbl_normalize(opnd2p1,opnd2p2,mpy_exponent);
	पूर्ण

	/* Multiply the first two source mantissas together */

	/* 
	 * The पूर्णांकermediate result will be kept in पंचांगpres,
	 * which needs enough room क्रम 106 bits of mantissa,
	 * so lets call it a Double extended.
	 */
	Dblext_setzero(पंचांगpresp1,पंचांगpresp2,पंचांगpresp3,पंचांगpresp4);

	/* 
	 * Four bits at a समय are inspected in each loop, and a 
	 * simple shअगरt and add multiply algorithm is used. 
	 */ 
	क्रम (count = DBL_P-1; count >= 0; count -= 4) अणु
		Dblext_rightshअगरtby4(पंचांगpresp1,पंचांगpresp2,पंचांगpresp3,पंचांगpresp4);
		अगर (Dbit28p2(opnd1p2)) अणु
	 		/* Fourword_add should be an ADD followed by 3 ADDC's */
			Fourword_add(पंचांगpresp1, पंचांगpresp2, पंचांगpresp3, पंचांगpresp4, 
			 opnd2p1<<3 | opnd2p2>>29, opnd2p2<<3, 0, 0);
		पूर्ण
		अगर (Dbit29p2(opnd1p2)) अणु
			Fourword_add(पंचांगpresp1, पंचांगpresp2, पंचांगpresp3, पंचांगpresp4,
			 opnd2p1<<2 | opnd2p2>>30, opnd2p2<<2, 0, 0);
		पूर्ण
		अगर (Dbit30p2(opnd1p2)) अणु
			Fourword_add(पंचांगpresp1, पंचांगpresp2, पंचांगpresp3, पंचांगpresp4,
			 opnd2p1<<1 | opnd2p2>>31, opnd2p2<<1, 0, 0);
		पूर्ण
		अगर (Dbit31p2(opnd1p2)) अणु
			Fourword_add(पंचांगpresp1, पंचांगpresp2, पंचांगpresp3, पंचांगpresp4,
			 opnd2p1, opnd2p2, 0, 0);
		पूर्ण
		Dbl_rightshअगरtby4(opnd1p1,opnd1p2);
	पूर्ण
	अगर (Is_dexthiddenoverflow(पंचांगpresp1)) अणु
		/* result mantissa >= 2 (mantissa overflow) */
		mpy_exponent++;
		Dblext_rightshअगरtby1(पंचांगpresp1,पंचांगpresp2,पंचांगpresp3,पंचांगpresp4);
	पूर्ण

	/*
	 * Restore the sign of the mpy result which was saved in resultp1.
	 * The exponent will जारी to be kept in mpy_exponent.
	 */
	Dblext_set_sign(पंचांगpresp1,Dbl_sign(resultp1));

	/* 
	 * No rounding is required, since the result of the multiply
	 * is exact in the extended क्रमmat.
	 */

	/*
	 * Now we are पढ़ोy to perक्रमm the add portion of the operation.
	 *
	 * The exponents need to be kept as पूर्णांकegers क्रम now, since the
	 * multiply result might not fit पूर्णांकo the exponent field.  We
	 * can't overflow or underflow because of this yet, since the
	 * add could bring the final result back पूर्णांकo range.
	 */
	add_exponent = Dbl_exponent(opnd3p1);

	/*
	 * Check क्रम denormalized or zero add opeअक्रम.
	 */
	अगर (add_exponent == 0) अणु
		/* check क्रम zero */
		अगर (Dbl_iszero_mantissa(opnd3p1,opnd3p2)) अणु
			/* right is zero */
			/* Left can't be zero and must be result.
			 *
			 * The final result is now in पंचांगpres and mpy_exponent,
			 * and needs to be rounded and squeezed back पूर्णांकo
			 * द्विगुन precision क्रमmat from द्विगुन extended.
			 */
			result_exponent = mpy_exponent;
			Dblext_copy(पंचांगpresp1,पंचांगpresp2,पंचांगpresp3,पंचांगpresp4,
				resultp1,resultp2,resultp3,resultp4);
			sign_save = Dbl_signextendedsign(resultp1);/*save sign*/
			जाओ round;
		पूर्ण

		/* 
		 * Neither are zeroes.  
		 * Adjust exponent and normalize add opeअक्रम.
		 */
		sign_save = Dbl_signextendedsign(opnd3p1);	/* save sign */
		Dbl_clear_signexponent(opnd3p1);
		Dbl_leftshअगरtby1(opnd3p1,opnd3p2);
		Dbl_normalize(opnd3p1,opnd3p2,add_exponent);
		Dbl_set_sign(opnd3p1,sign_save);	/* restore sign */
	पूर्ण अन्यथा अणु
		Dbl_clear_exponent_set_hidden(opnd3p1);
	पूर्ण
	/*
	 * Copy opnd3 to the द्विगुन extended variable called right.
	 */
	Dbl_copyto_dblext(opnd3p1,opnd3p2,rightp1,rightp2,rightp3,rightp4);

	/*
	 * A zero "save" helps discover equal opeअक्रमs (क्रम later),
	 * and is used in swapping opeअक्रमs (अगर needed).
	 */
	Dblext_xortoपूर्णांकp1(पंचांगpresp1,rightp1,/*to*/save);

	/*
	 * Compare magnitude of opeअक्रमs.
	 */
	Dblext_copytoपूर्णांक_exponenपंचांगantissap1(पंचांगpresp1,signlessleft1);
	Dblext_copytoपूर्णांक_exponenपंचांगantissap1(rightp1,signlessright1);
	अगर (mpy_exponent < add_exponent || mpy_exponent == add_exponent &&
	    Dblext_ismagnitudeless(पंचांगpresp2,rightp2,signlessleft1,signlessright1))अणु
		/*
		 * Set the left opeअक्रम to the larger one by XOR swap.
		 * First finish the first word "save".
		 */
		Dblext_xorfromपूर्णांकp1(save,rightp1,/*to*/rightp1);
		Dblext_xorfromपूर्णांकp1(save,पंचांगpresp1,/*to*/पंचांगpresp1);
		Dblext_swap_lower(पंचांगpresp2,पंचांगpresp3,पंचांगpresp4,
			rightp2,rightp3,rightp4);
		/* also setup exponents used in rest of routine */
		dअगरf_exponent = add_exponent - mpy_exponent;
		result_exponent = add_exponent;
	पूर्ण अन्यथा अणु
		/* also setup exponents used in rest of routine */
		dअगरf_exponent = mpy_exponent - add_exponent;
		result_exponent = mpy_exponent;
	पूर्ण
	/* Invariant: left is not smaller than right. */

	/*
	 * Special हाल alignment of opeअक्रमs that would क्रमce alignment
	 * beyond the extent of the extension.  A further optimization
	 * could special हाल this but only reduces the path length क्रम
	 * this infrequent हाल.
	 */
	अगर (dअगरf_exponent > DBLEXT_THRESHOLD) अणु
		dअगरf_exponent = DBLEXT_THRESHOLD;
	पूर्ण

	/* Align right opeअक्रम by shअगरting it to the right */
	Dblext_clear_sign(rightp1);
	Dblext_right_align(rightp1,rightp2,rightp3,rightp4,
		/*shअगरted by*/dअगरf_exponent);
	
	/* Treat sum and dअगरference of the opeअक्रमs separately. */
	अगर ((पूर्णांक)save < 0) अणु
		/*
		 * Dअगरference of the two opeअक्रमs.  Overflow can occur अगर the
		 * multiply overflowed.  A borrow can occur out of the hidden
		 * bit and क्रमce a post normalization phase.
		 */
		Dblext_subtract(पंचांगpresp1,पंचांगpresp2,पंचांगpresp3,पंचांगpresp4,
			rightp1,rightp2,rightp3,rightp4,
			resultp1,resultp2,resultp3,resultp4);
		sign_save = Dbl_signextendedsign(resultp1);
		अगर (Dbl_iszero_hidden(resultp1)) अणु
			/* Handle normalization */
		/* A straightक्रमward algorithm would now shअगरt the
		 * result and extension left until the hidden bit
		 * becomes one.  Not all of the extension bits need
		 * participate in the shअगरt.  Only the two most 
		 * signअगरicant bits (round and guard) are needed.
		 * If only a single shअगरt is needed then the guard
		 * bit becomes a signअगरicant low order bit and the
		 * extension must participate in the rounding.
		 * If more than a single shअगरt is needed, then all
		 * bits to the right of the guard bit are zeros, 
		 * and the guard bit may or may not be zero. */
			Dblext_leftshअगरtby1(resultp1,resultp2,resultp3,
				resultp4);

			/* Need to check क्रम a zero result.  The sign and
			 * exponent fields have alपढ़ोy been zeroed.  The more
			 * efficient test of the full object can be used.
			 */
			 अगर (Dblext_iszero(resultp1,resultp2,resultp3,resultp4)) अणु
				/* Must have been "x-x" or "x+(-x)". */
				अगर (Is_rounding_mode(ROUNDMINUS))
					Dbl_setone_sign(resultp1);
				Dbl_copytoptr(resultp1,resultp2,dstptr);
				वापस(NOEXCEPTION);
			पूर्ण
			result_exponent--;

			/* Look to see अगर normalization is finished. */
			अगर (Dbl_isone_hidden(resultp1)) अणु
				/* No further normalization is needed */
				जाओ round;
			पूर्ण

			/* Discover first one bit to determine shअगरt amount.
			 * Use a modअगरied binary search.  We have alपढ़ोy
			 * shअगरted the result one position right and still
			 * not found a one so the reमुख्यder of the extension
			 * must be zero and simplअगरies rounding. */
			/* Scan bytes */
			जबतक (Dbl_iszero_hiddenhigh7mantissa(resultp1)) अणु
				Dblext_leftshअगरtby8(resultp1,resultp2,resultp3,resultp4);
				result_exponent -= 8;
			पूर्ण
			/* Now narrow it करोwn to the nibble */
			अगर (Dbl_iszero_hiddenhigh3mantissa(resultp1)) अणु
				/* The lower nibble contains the
				 * normalizing one */
				Dblext_leftshअगरtby4(resultp1,resultp2,resultp3,resultp4);
				result_exponent -= 4;
			पूर्ण
			/* Select हाल where first bit is set (alपढ़ोy
			 * normalized) otherwise select the proper shअगरt. */
			jumpsize = Dbl_hiddenhigh3mantissa(resultp1);
			अगर (jumpsize <= 7) चयन(jumpsize) अणु
			हाल 1:
				Dblext_leftshअगरtby3(resultp1,resultp2,resultp3,
					resultp4);
				result_exponent -= 3;
				अवरोध;
			हाल 2:
			हाल 3:
				Dblext_leftshअगरtby2(resultp1,resultp2,resultp3,
					resultp4);
				result_exponent -= 2;
				अवरोध;
			हाल 4:
			हाल 5:
			हाल 6:
			हाल 7:
				Dblext_leftshअगरtby1(resultp1,resultp2,resultp3,
					resultp4);
				result_exponent -= 1;
				अवरोध;
			पूर्ण
		पूर्ण /* end अगर (hidden...)... */
	/* Fall through and round */
	पूर्ण /* end अगर (save < 0)... */
	अन्यथा अणु
		/* Add magnitudes */
		Dblext_addition(पंचांगpresp1,पंचांगpresp2,पंचांगpresp3,पंचांगpresp4,
			rightp1,rightp2,rightp3,rightp4,
			/*to*/resultp1,resultp2,resultp3,resultp4);
		sign_save = Dbl_signextendedsign(resultp1);
		अगर (Dbl_isone_hiddenoverflow(resultp1)) अणु
	    		/* Prenormalization required. */
	    		Dblext_arithrightshअगरtby1(resultp1,resultp2,resultp3,
				resultp4);
	    		result_exponent++;
		पूर्ण /* end अगर hiddenoverflow... */
	पूर्ण /* end अन्यथा ...add magnitudes... */

	/* Round the result.  If the extension and lower two words are
	 * all zeros, then the result is exact.  Otherwise round in the
	 * correct direction.  Underflow is possible. If a postnormalization
	 * is necessary, then the mantissa is all zeros so no shअगरt is needed.
	 */
  round:
	अगर (result_exponent <= 0 && !Is_underflowtrap_enabled()) अणु
		Dblext_denormalize(resultp1,resultp2,resultp3,resultp4,
			result_exponent,is_tiny);
	पूर्ण
	Dbl_set_sign(resultp1,/*using*/sign_save);
	अगर (Dblext_isnotzero_mantissap3(resultp3) || 
	    Dblext_isnotzero_mantissap4(resultp4)) अणु
		inexact = TRUE;
		चयन(Rounding_mode()) अणु
		हाल ROUNDNEAREST: /* The शेष. */
			अगर (Dblext_isone_highp3(resultp3)) अणु
				/* at least 1/2 ulp */
				अगर (Dblext_isnotzero_low31p3(resultp3) ||
				    Dblext_isnotzero_mantissap4(resultp4) ||
				    Dblext_isone_lowp2(resultp2)) अणु
					/* either exactly half way and odd or
					 * more than 1/2ulp */
					Dbl_increment(resultp1,resultp2);
				पूर्ण
			पूर्ण
	    		अवरोध;

		हाल ROUNDPLUS:
	    		अगर (Dbl_iszero_sign(resultp1)) अणु
				/* Round up positive results */
				Dbl_increment(resultp1,resultp2);
			पूर्ण
			अवरोध;
	    
		हाल ROUNDMINUS:
	    		अगर (Dbl_isone_sign(resultp1)) अणु
				/* Round करोwn negative results */
				Dbl_increment(resultp1,resultp2);
			पूर्ण
	    
		हाल ROUNDZERO:;
			/* truncate is simple */
		पूर्ण /* end चयन... */
		अगर (Dbl_isone_hiddenoverflow(resultp1)) result_exponent++;
	पूर्ण
	अगर (result_exponent >= DBL_अनन्त_EXPONENT) अणु
		/* Overflow */
		अगर (Is_overflowtrap_enabled()) अणु
                        /*
                         * Adjust bias of result
                         */
                        Dbl_setwrapped_exponent(resultp1,result_exponent,ovfl);
                        Dbl_copytoptr(resultp1,resultp2,dstptr);
                        अगर (inexact)
                            अगर (Is_inexacttrap_enabled())
                                वापस (OPC_2E_OVERFLOWEXCEPTION |
					OPC_2E_INEXACTEXCEPTION);
                            अन्यथा Set_inexactflag();
                        वापस (OPC_2E_OVERFLOWEXCEPTION);
		पूर्ण
		inexact = TRUE;
		Set_overflowflag();
		Dbl_setoverflow(resultp1,resultp2);
	पूर्ण अन्यथा अगर (result_exponent <= 0) अणु	/* underflow हाल */
		अगर (Is_underflowtrap_enabled()) अणु
                        /*
                         * Adjust bias of result
                         */
                	Dbl_setwrapped_exponent(resultp1,result_exponent,unfl);
			Dbl_copytoptr(resultp1,resultp2,dstptr);
                        अगर (inexact)
                            अगर (Is_inexacttrap_enabled())
                                वापस (OPC_2E_UNDERFLOWEXCEPTION |
					OPC_2E_INEXACTEXCEPTION);
                            अन्यथा Set_inexactflag();
	    		वापस(OPC_2E_UNDERFLOWEXCEPTION);
		पूर्ण
		अन्यथा अगर (inexact && is_tiny) Set_underflowflag();
	पूर्ण
	अन्यथा Dbl_set_exponent(resultp1,result_exponent);
	Dbl_copytoptr(resultp1,resultp2,dstptr);
	अगर (inexact) 
		अगर (Is_inexacttrap_enabled()) वापस(OPC_2E_INEXACTEXCEPTION);
		अन्यथा Set_inexactflag();
    	वापस(NOEXCEPTION);
पूर्ण

/*
 *  Single Floating-poपूर्णांक Multiply Fused Add
 */

sgl_fmpyfadd(src1ptr,src2ptr,src3ptr,status,dstptr)

sgl_भग्नing_poपूर्णांक *src1ptr, *src2ptr, *src3ptr, *dstptr;
अचिन्हित पूर्णांक *status;
अणु
	अचिन्हित पूर्णांक opnd1, opnd2, opnd3;
	रेजिस्टर अचिन्हित पूर्णांक पंचांगpresp1, पंचांगpresp2;
	अचिन्हित पूर्णांक rightp1, rightp2;
	अचिन्हित पूर्णांक resultp1, resultp2 = 0;
	रेजिस्टर पूर्णांक mpy_exponent, add_exponent, count;
	boolean inexact = FALSE, is_tiny = FALSE;

	अचिन्हित पूर्णांक signlessleft1, signlessright1, save;
	रेजिस्टर पूर्णांक result_exponent, dअगरf_exponent;
	पूर्णांक sign_save, jumpsize;
	
	Sgl_copyfromptr(src1ptr,opnd1);
	Sgl_copyfromptr(src2ptr,opnd2);
	Sgl_copyfromptr(src3ptr,opnd3);

	/* 
	 * set sign bit of result of multiply
	 */
	अगर (Sgl_sign(opnd1) ^ Sgl_sign(opnd2)) 
		Sgl_setnegativezero(resultp1); 
	अन्यथा Sgl_setzero(resultp1);

	/*
	 * Generate multiply exponent 
	 */
	mpy_exponent = Sgl_exponent(opnd1) + Sgl_exponent(opnd2) - SGL_BIAS;

	/*
	 * check first opeअक्रम क्रम NaN's or infinity
	 */
	अगर (Sgl_isinfinity_exponent(opnd1)) अणु
		अगर (Sgl_iszero_mantissa(opnd1)) अणु
			अगर (Sgl_isnotnan(opnd2) && Sgl_isnotnan(opnd3)) अणु
				अगर (Sgl_iszero_exponenपंचांगantissa(opnd2)) अणु
					/* 
					 * invalid since opeअक्रमs are infinity 
					 * and zero 
					 */
					अगर (Is_invalidtrap_enabled())
						वापस(OPC_2E_INVALIDEXCEPTION);
					Set_invalidflag();
					Sgl_makequietnan(resultp1);
					Sgl_copytoptr(resultp1,dstptr);
					वापस(NOEXCEPTION);
				पूर्ण
				/*
				 * Check third opeअक्रम क्रम infinity with a
				 *  sign opposite of the multiply result
				 */
				अगर (Sgl_isinfinity(opnd3) &&
				    (Sgl_sign(resultp1) ^ Sgl_sign(opnd3))) अणु
					/* 
					 * invalid since attempting a magnitude
					 * subtraction of infinities
					 */
					अगर (Is_invalidtrap_enabled())
						वापस(OPC_2E_INVALIDEXCEPTION);
					Set_invalidflag();
					Sgl_makequietnan(resultp1);
					Sgl_copytoptr(resultp1,dstptr);
					वापस(NOEXCEPTION);
				पूर्ण

				/*
			 	 * वापस infinity
			 	 */
				Sgl_setinfinity_exponenपंचांगantissa(resultp1);
				Sgl_copytoptr(resultp1,dstptr);
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
			    		वापस(OPC_2E_INVALIDEXCEPTION);
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
			    		वापस(OPC_2E_INVALIDEXCEPTION);
				/* make NaN quiet */
				Set_invalidflag();
				Sgl_set_quiet(opnd2);
				Sgl_copytoptr(opnd2,dstptr);
				वापस(NOEXCEPTION);
			पूर्ण
			/* 
			 * is third opeअक्रम a संकेतing NaN? 
			 */
			अन्यथा अगर (Sgl_is_संकेतingnan(opnd3)) अणु
				/* trap अगर INVALIDTRAP enabled */
				अगर (Is_invalidtrap_enabled())
			    		वापस(OPC_2E_INVALIDEXCEPTION);
				/* make NaN quiet */
				Set_invalidflag();
				Sgl_set_quiet(opnd3);
				Sgl_copytoptr(opnd3,dstptr);
				वापस(NOEXCEPTION);
			पूर्ण
			/*
		 	 * वापस quiet NaN
		 	 */
			Sgl_copytoptr(opnd1,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
	पूर्ण

	/*
	 * check second opeअक्रम क्रम NaN's or infinity
	 */
	अगर (Sgl_isinfinity_exponent(opnd2)) अणु
		अगर (Sgl_iszero_mantissa(opnd2)) अणु
			अगर (Sgl_isnotnan(opnd3)) अणु
				अगर (Sgl_iszero_exponenपंचांगantissa(opnd1)) अणु
					/* 
					 * invalid since multiply opeअक्रमs are
					 * zero & infinity
					 */
					अगर (Is_invalidtrap_enabled())
						वापस(OPC_2E_INVALIDEXCEPTION);
					Set_invalidflag();
					Sgl_makequietnan(opnd2);
					Sgl_copytoptr(opnd2,dstptr);
					वापस(NOEXCEPTION);
				पूर्ण

				/*
				 * Check third opeअक्रम क्रम infinity with a
				 *  sign opposite of the multiply result
				 */
				अगर (Sgl_isinfinity(opnd3) &&
				    (Sgl_sign(resultp1) ^ Sgl_sign(opnd3))) अणु
					/* 
					 * invalid since attempting a magnitude
					 * subtraction of infinities
					 */
					अगर (Is_invalidtrap_enabled())
				       		वापस(OPC_2E_INVALIDEXCEPTION);
				       	Set_invalidflag();
				       	Sgl_makequietnan(resultp1);
					Sgl_copytoptr(resultp1,dstptr);
					वापस(NOEXCEPTION);
				पूर्ण

				/*
				 * वापस infinity
				 */
				Sgl_setinfinity_exponenपंचांगantissa(resultp1);
				Sgl_copytoptr(resultp1,dstptr);
				वापस(NOEXCEPTION);
			पूर्ण
		पूर्ण
		अन्यथा अणु
			/*
			 * is NaN; संकेतing or quiet?
			 */
			अगर (Sgl_isone_संकेतing(opnd2)) अणु
				/* trap अगर INVALIDTRAP enabled */
				अगर (Is_invalidtrap_enabled())
					वापस(OPC_2E_INVALIDEXCEPTION);
				/* make NaN quiet */
				Set_invalidflag();
				Sgl_set_quiet(opnd2);
			पूर्ण
			/* 
			 * is third opeअक्रम a संकेतing NaN? 
			 */
			अन्यथा अगर (Sgl_is_संकेतingnan(opnd3)) अणु
			       	/* trap अगर INVALIDTRAP enabled */
			       	अगर (Is_invalidtrap_enabled())
				   		वापस(OPC_2E_INVALIDEXCEPTION);
			       	/* make NaN quiet */
			       	Set_invalidflag();
			       	Sgl_set_quiet(opnd3);
				Sgl_copytoptr(opnd3,dstptr);
		       		वापस(NOEXCEPTION);
			पूर्ण
			/*
			 * वापस quiet NaN
			 */
			Sgl_copytoptr(opnd2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
	पूर्ण

	/*
	 * check third opeअक्रम क्रम NaN's or infinity
	 */
	अगर (Sgl_isinfinity_exponent(opnd3)) अणु
		अगर (Sgl_iszero_mantissa(opnd3)) अणु
			/* वापस infinity */
			Sgl_copytoptr(opnd3,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण अन्यथा अणु
			/*
			 * is NaN; संकेतing or quiet?
			 */
			अगर (Sgl_isone_संकेतing(opnd3)) अणु
				/* trap अगर INVALIDTRAP enabled */
				अगर (Is_invalidtrap_enabled())
					वापस(OPC_2E_INVALIDEXCEPTION);
				/* make NaN quiet */
				Set_invalidflag();
				Sgl_set_quiet(opnd3);
			पूर्ण
			/*
			 * वापस quiet NaN
 			 */
			Sgl_copytoptr(opnd3,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
    	पूर्ण

	/*
	 * Generate multiply mantissa
	 */
	अगर (Sgl_isnotzero_exponent(opnd1)) अणु
		/* set hidden bit */
		Sgl_clear_signexponent_set_hidden(opnd1);
	पूर्ण
	अन्यथा अणु
		/* check क्रम zero */
		अगर (Sgl_iszero_mantissa(opnd1)) अणु
			/*
			 * Perक्रमm the add opnd3 with zero here.
			 */
			अगर (Sgl_iszero_exponenपंचांगantissa(opnd3)) अणु
				अगर (Is_rounding_mode(ROUNDMINUS)) अणु
					Sgl_or_signs(opnd3,resultp1);
				पूर्ण अन्यथा अणु
					Sgl_and_signs(opnd3,resultp1);
				पूर्ण
			पूर्ण
			/*
			 * Now let's check क्रम trapped underflow हाल.
			 */
			अन्यथा अगर (Sgl_iszero_exponent(opnd3) &&
			         Is_underflowtrap_enabled()) अणु
                    		/* need to normalize results mantissa */
                    		sign_save = Sgl_signextendedsign(opnd3);
				result_exponent = 0;
                    		Sgl_leftshअगरtby1(opnd3);
                    		Sgl_normalize(opnd3,result_exponent);
                    		Sgl_set_sign(opnd3,/*using*/sign_save);
                    		Sgl_setwrapped_exponent(opnd3,result_exponent,
							unfl);
                    		Sgl_copytoptr(opnd3,dstptr);
                    		/* inexact = FALSE */
                    		वापस(OPC_2E_UNDERFLOWEXCEPTION);
			पूर्ण
			Sgl_copytoptr(opnd3,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
		/* is denormalized, adjust exponent */
		Sgl_clear_signexponent(opnd1);
		Sgl_leftshअगरtby1(opnd1);
		Sgl_normalize(opnd1,mpy_exponent);
	पूर्ण
	/* opnd2 needs to have hidden bit set with msb in hidden bit */
	अगर (Sgl_isnotzero_exponent(opnd2)) अणु
		Sgl_clear_signexponent_set_hidden(opnd2);
	पूर्ण
	अन्यथा अणु
		/* check क्रम zero */
		अगर (Sgl_iszero_mantissa(opnd2)) अणु
			/*
			 * Perक्रमm the add opnd3 with zero here.
			 */
			अगर (Sgl_iszero_exponenपंचांगantissa(opnd3)) अणु
				अगर (Is_rounding_mode(ROUNDMINUS)) अणु
					Sgl_or_signs(opnd3,resultp1);
				पूर्ण अन्यथा अणु
					Sgl_and_signs(opnd3,resultp1);
				पूर्ण
			पूर्ण
			/*
			 * Now let's check क्रम trapped underflow हाल.
			 */
			अन्यथा अगर (Sgl_iszero_exponent(opnd3) &&
			    Is_underflowtrap_enabled()) अणु
                    		/* need to normalize results mantissa */
                    		sign_save = Sgl_signextendedsign(opnd3);
				result_exponent = 0;
                    		Sgl_leftshअगरtby1(opnd3);
                    		Sgl_normalize(opnd3,result_exponent);
                    		Sgl_set_sign(opnd3,/*using*/sign_save);
                    		Sgl_setwrapped_exponent(opnd3,result_exponent,
							unfl);
                    		Sgl_copytoptr(opnd3,dstptr);
                    		/* inexact = FALSE */
                    		वापस(OPC_2E_UNDERFLOWEXCEPTION);
			पूर्ण
			Sgl_copytoptr(opnd3,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
		/* is denormalized; want to normalize */
		Sgl_clear_signexponent(opnd2);
		Sgl_leftshअगरtby1(opnd2);
		Sgl_normalize(opnd2,mpy_exponent);
	पूर्ण

	/* Multiply the first two source mantissas together */

	/* 
	 * The पूर्णांकermediate result will be kept in पंचांगpres,
	 * which needs enough room क्रम 106 bits of mantissa,
	 * so lets call it a Double extended.
	 */
	Sglext_setzero(पंचांगpresp1,पंचांगpresp2);

	/* 
	 * Four bits at a समय are inspected in each loop, and a 
	 * simple shअगरt and add multiply algorithm is used. 
	 */ 
	क्रम (count = SGL_P-1; count >= 0; count -= 4) अणु
		Sglext_rightshअगरtby4(पंचांगpresp1,पंचांगpresp2);
		अगर (Sbit28(opnd1)) अणु
	 		/* Twoword_add should be an ADD followed by 2 ADDC's */
			Twoword_add(पंचांगpresp1, पंचांगpresp2, opnd2<<3, 0);
		पूर्ण
		अगर (Sbit29(opnd1)) अणु
			Twoword_add(पंचांगpresp1, पंचांगpresp2, opnd2<<2, 0);
		पूर्ण
		अगर (Sbit30(opnd1)) अणु
			Twoword_add(पंचांगpresp1, पंचांगpresp2, opnd2<<1, 0);
		पूर्ण
		अगर (Sbit31(opnd1)) अणु
			Twoword_add(पंचांगpresp1, पंचांगpresp2, opnd2, 0);
		पूर्ण
		Sgl_rightshअगरtby4(opnd1);
	पूर्ण
	अगर (Is_sexthiddenoverflow(पंचांगpresp1)) अणु
		/* result mantissa >= 2 (mantissa overflow) */
		mpy_exponent++;
		Sglext_rightshअगरtby4(पंचांगpresp1,पंचांगpresp2);
	पूर्ण अन्यथा अणु
		Sglext_rightshअगरtby3(पंचांगpresp1,पंचांगpresp2);
	पूर्ण

	/*
	 * Restore the sign of the mpy result which was saved in resultp1.
	 * The exponent will जारी to be kept in mpy_exponent.
	 */
	Sglext_set_sign(पंचांगpresp1,Sgl_sign(resultp1));

	/* 
	 * No rounding is required, since the result of the multiply
	 * is exact in the extended क्रमmat.
	 */

	/*
	 * Now we are पढ़ोy to perक्रमm the add portion of the operation.
	 *
	 * The exponents need to be kept as पूर्णांकegers क्रम now, since the
	 * multiply result might not fit पूर्णांकo the exponent field.  We
	 * can't overflow or underflow because of this yet, since the
	 * add could bring the final result back पूर्णांकo range.
	 */
	add_exponent = Sgl_exponent(opnd3);

	/*
	 * Check क्रम denormalized or zero add opeअक्रम.
	 */
	अगर (add_exponent == 0) अणु
		/* check क्रम zero */
		अगर (Sgl_iszero_mantissa(opnd3)) अणु
			/* right is zero */
			/* Left can't be zero and must be result.
			 *
			 * The final result is now in पंचांगpres and mpy_exponent,
			 * and needs to be rounded and squeezed back पूर्णांकo
			 * द्विगुन precision क्रमmat from द्विगुन extended.
			 */
			result_exponent = mpy_exponent;
			Sglext_copy(पंचांगpresp1,पंचांगpresp2,resultp1,resultp2);
			sign_save = Sgl_signextendedsign(resultp1);/*save sign*/
			जाओ round;
		पूर्ण

		/* 
		 * Neither are zeroes.  
		 * Adjust exponent and normalize add opeअक्रम.
		 */
		sign_save = Sgl_signextendedsign(opnd3);	/* save sign */
		Sgl_clear_signexponent(opnd3);
		Sgl_leftshअगरtby1(opnd3);
		Sgl_normalize(opnd3,add_exponent);
		Sgl_set_sign(opnd3,sign_save);		/* restore sign */
	पूर्ण अन्यथा अणु
		Sgl_clear_exponent_set_hidden(opnd3);
	पूर्ण
	/*
	 * Copy opnd3 to the द्विगुन extended variable called right.
	 */
	Sgl_copyto_sglext(opnd3,rightp1,rightp2);

	/*
	 * A zero "save" helps discover equal opeअक्रमs (क्रम later),
	 * and is used in swapping opeअक्रमs (अगर needed).
	 */
	Sglext_xortoपूर्णांकp1(पंचांगpresp1,rightp1,/*to*/save);

	/*
	 * Compare magnitude of opeअक्रमs.
	 */
	Sglext_copytoपूर्णांक_exponenपंचांगantissa(पंचांगpresp1,signlessleft1);
	Sglext_copytoपूर्णांक_exponenपंचांगantissa(rightp1,signlessright1);
	अगर (mpy_exponent < add_exponent || mpy_exponent == add_exponent &&
	    Sglext_ismagnitudeless(signlessleft1,signlessright1)) अणु
		/*
		 * Set the left opeअक्रम to the larger one by XOR swap.
		 * First finish the first word "save".
		 */
		Sglext_xorfromपूर्णांकp1(save,rightp1,/*to*/rightp1);
		Sglext_xorfromपूर्णांकp1(save,पंचांगpresp1,/*to*/पंचांगpresp1);
		Sglext_swap_lower(पंचांगpresp2,rightp2);
		/* also setup exponents used in rest of routine */
		dअगरf_exponent = add_exponent - mpy_exponent;
		result_exponent = add_exponent;
	पूर्ण अन्यथा अणु
		/* also setup exponents used in rest of routine */
		dअगरf_exponent = mpy_exponent - add_exponent;
		result_exponent = mpy_exponent;
	पूर्ण
	/* Invariant: left is not smaller than right. */

	/*
	 * Special हाल alignment of opeअक्रमs that would क्रमce alignment
	 * beyond the extent of the extension.  A further optimization
	 * could special हाल this but only reduces the path length क्रम
	 * this infrequent हाल.
	 */
	अगर (dअगरf_exponent > SGLEXT_THRESHOLD) अणु
		dअगरf_exponent = SGLEXT_THRESHOLD;
	पूर्ण

	/* Align right opeअक्रम by shअगरting it to the right */
	Sglext_clear_sign(rightp1);
	Sglext_right_align(rightp1,rightp2,/*shअगरted by*/dअगरf_exponent);
	
	/* Treat sum and dअगरference of the opeअक्रमs separately. */
	अगर ((पूर्णांक)save < 0) अणु
		/*
		 * Dअगरference of the two opeअक्रमs.  Overflow can occur अगर the
		 * multiply overflowed.  A borrow can occur out of the hidden
		 * bit and क्रमce a post normalization phase.
		 */
		Sglext_subtract(पंचांगpresp1,पंचांगpresp2, rightp1,rightp2,
			resultp1,resultp2);
		sign_save = Sgl_signextendedsign(resultp1);
		अगर (Sgl_iszero_hidden(resultp1)) अणु
			/* Handle normalization */
		/* A straightक्रमward algorithm would now shअगरt the
		 * result and extension left until the hidden bit
		 * becomes one.  Not all of the extension bits need
		 * participate in the shअगरt.  Only the two most 
		 * signअगरicant bits (round and guard) are needed.
		 * If only a single shअगरt is needed then the guard
		 * bit becomes a signअगरicant low order bit and the
		 * extension must participate in the rounding.
		 * If more than a single shअगरt is needed, then all
		 * bits to the right of the guard bit are zeros, 
		 * and the guard bit may or may not be zero. */
			Sglext_leftshअगरtby1(resultp1,resultp2);

			/* Need to check क्रम a zero result.  The sign and
			 * exponent fields have alपढ़ोy been zeroed.  The more
			 * efficient test of the full object can be used.
			 */
			 अगर (Sglext_iszero(resultp1,resultp2)) अणु
				/* Must have been "x-x" or "x+(-x)". */
				अगर (Is_rounding_mode(ROUNDMINUS))
					Sgl_setone_sign(resultp1);
				Sgl_copytoptr(resultp1,dstptr);
				वापस(NOEXCEPTION);
			पूर्ण
			result_exponent--;

			/* Look to see अगर normalization is finished. */
			अगर (Sgl_isone_hidden(resultp1)) अणु
				/* No further normalization is needed */
				जाओ round;
			पूर्ण

			/* Discover first one bit to determine shअगरt amount.
			 * Use a modअगरied binary search.  We have alपढ़ोy
			 * shअगरted the result one position right and still
			 * not found a one so the reमुख्यder of the extension
			 * must be zero and simplअगरies rounding. */
			/* Scan bytes */
			जबतक (Sgl_iszero_hiddenhigh7mantissa(resultp1)) अणु
				Sglext_leftshअगरtby8(resultp1,resultp2);
				result_exponent -= 8;
			पूर्ण
			/* Now narrow it करोwn to the nibble */
			अगर (Sgl_iszero_hiddenhigh3mantissa(resultp1)) अणु
				/* The lower nibble contains the
				 * normalizing one */
				Sglext_leftshअगरtby4(resultp1,resultp2);
				result_exponent -= 4;
			पूर्ण
			/* Select हाल where first bit is set (alपढ़ोy
			 * normalized) otherwise select the proper shअगरt. */
			jumpsize = Sgl_hiddenhigh3mantissa(resultp1);
			अगर (jumpsize <= 7) चयन(jumpsize) अणु
			हाल 1:
				Sglext_leftshअगरtby3(resultp1,resultp2);
				result_exponent -= 3;
				अवरोध;
			हाल 2:
			हाल 3:
				Sglext_leftshअगरtby2(resultp1,resultp2);
				result_exponent -= 2;
				अवरोध;
			हाल 4:
			हाल 5:
			हाल 6:
			हाल 7:
				Sglext_leftshअगरtby1(resultp1,resultp2);
				result_exponent -= 1;
				अवरोध;
			पूर्ण
		पूर्ण /* end अगर (hidden...)... */
	/* Fall through and round */
	पूर्ण /* end अगर (save < 0)... */
	अन्यथा अणु
		/* Add magnitudes */
		Sglext_addition(पंचांगpresp1,पंचांगpresp2,
			rightp1,rightp2, /*to*/resultp1,resultp2);
		sign_save = Sgl_signextendedsign(resultp1);
		अगर (Sgl_isone_hiddenoverflow(resultp1)) अणु
	    		/* Prenormalization required. */
	    		Sglext_arithrightshअगरtby1(resultp1,resultp2);
	    		result_exponent++;
		पूर्ण /* end अगर hiddenoverflow... */
	पूर्ण /* end अन्यथा ...add magnitudes... */

	/* Round the result.  If the extension and lower two words are
	 * all zeros, then the result is exact.  Otherwise round in the
	 * correct direction.  Underflow is possible. If a postnormalization
	 * is necessary, then the mantissa is all zeros so no shअगरt is needed.
	 */
  round:
	अगर (result_exponent <= 0 && !Is_underflowtrap_enabled()) अणु
		Sglext_denormalize(resultp1,resultp2,result_exponent,is_tiny);
	पूर्ण
	Sgl_set_sign(resultp1,/*using*/sign_save);
	अगर (Sglext_isnotzero_mantissap2(resultp2)) अणु
		inexact = TRUE;
		चयन(Rounding_mode()) अणु
		हाल ROUNDNEAREST: /* The शेष. */
			अगर (Sglext_isone_highp2(resultp2)) अणु
				/* at least 1/2 ulp */
				अगर (Sglext_isnotzero_low31p2(resultp2) ||
				    Sglext_isone_lowp1(resultp1)) अणु
					/* either exactly half way and odd or
					 * more than 1/2ulp */
					Sgl_increment(resultp1);
				पूर्ण
			पूर्ण
	    		अवरोध;

		हाल ROUNDPLUS:
	    		अगर (Sgl_iszero_sign(resultp1)) अणु
				/* Round up positive results */
				Sgl_increment(resultp1);
			पूर्ण
			अवरोध;
	    
		हाल ROUNDMINUS:
	    		अगर (Sgl_isone_sign(resultp1)) अणु
				/* Round करोwn negative results */
				Sgl_increment(resultp1);
			पूर्ण
	    
		हाल ROUNDZERO:;
			/* truncate is simple */
		पूर्ण /* end चयन... */
		अगर (Sgl_isone_hiddenoverflow(resultp1)) result_exponent++;
	पूर्ण
	अगर (result_exponent >= SGL_अनन्त_EXPONENT) अणु
		/* Overflow */
		अगर (Is_overflowtrap_enabled()) अणु
                        /*
                         * Adjust bias of result
                         */
                        Sgl_setwrapped_exponent(resultp1,result_exponent,ovfl);
                        Sgl_copytoptr(resultp1,dstptr);
                        अगर (inexact)
                            अगर (Is_inexacttrap_enabled())
                                वापस (OPC_2E_OVERFLOWEXCEPTION |
					OPC_2E_INEXACTEXCEPTION);
                            अन्यथा Set_inexactflag();
                        वापस (OPC_2E_OVERFLOWEXCEPTION);
		पूर्ण
		inexact = TRUE;
		Set_overflowflag();
		Sgl_setoverflow(resultp1);
	पूर्ण अन्यथा अगर (result_exponent <= 0) अणु	/* underflow हाल */
		अगर (Is_underflowtrap_enabled()) अणु
                        /*
                         * Adjust bias of result
                         */
                	Sgl_setwrapped_exponent(resultp1,result_exponent,unfl);
			Sgl_copytoptr(resultp1,dstptr);
                        अगर (inexact)
                            अगर (Is_inexacttrap_enabled())
                                वापस (OPC_2E_UNDERFLOWEXCEPTION |
					OPC_2E_INEXACTEXCEPTION);
                            अन्यथा Set_inexactflag();
	    		वापस(OPC_2E_UNDERFLOWEXCEPTION);
		पूर्ण
		अन्यथा अगर (inexact && is_tiny) Set_underflowflag();
	पूर्ण
	अन्यथा Sgl_set_exponent(resultp1,result_exponent);
	Sgl_copytoptr(resultp1,dstptr);
	अगर (inexact) 
		अगर (Is_inexacttrap_enabled()) वापस(OPC_2E_INEXACTEXCEPTION);
		अन्यथा Set_inexactflag();
    	वापस(NOEXCEPTION);
पूर्ण

/*
 *  Single Floating-poपूर्णांक Multiply Negate Fused Add
 */

sgl_fmpynfadd(src1ptr,src2ptr,src3ptr,status,dstptr)

sgl_भग्नing_poपूर्णांक *src1ptr, *src2ptr, *src3ptr, *dstptr;
अचिन्हित पूर्णांक *status;
अणु
	अचिन्हित पूर्णांक opnd1, opnd2, opnd3;
	रेजिस्टर अचिन्हित पूर्णांक पंचांगpresp1, पंचांगpresp2;
	अचिन्हित पूर्णांक rightp1, rightp2;
	अचिन्हित पूर्णांक resultp1, resultp2 = 0;
	रेजिस्टर पूर्णांक mpy_exponent, add_exponent, count;
	boolean inexact = FALSE, is_tiny = FALSE;

	अचिन्हित पूर्णांक signlessleft1, signlessright1, save;
	रेजिस्टर पूर्णांक result_exponent, dअगरf_exponent;
	पूर्णांक sign_save, jumpsize;
	
	Sgl_copyfromptr(src1ptr,opnd1);
	Sgl_copyfromptr(src2ptr,opnd2);
	Sgl_copyfromptr(src3ptr,opnd3);

	/* 
	 * set sign bit of result of multiply
	 */
	अगर (Sgl_sign(opnd1) ^ Sgl_sign(opnd2)) 
		Sgl_setzero(resultp1);
	अन्यथा 
		Sgl_setnegativezero(resultp1); 

	/*
	 * Generate multiply exponent 
	 */
	mpy_exponent = Sgl_exponent(opnd1) + Sgl_exponent(opnd2) - SGL_BIAS;

	/*
	 * check first opeअक्रम क्रम NaN's or infinity
	 */
	अगर (Sgl_isinfinity_exponent(opnd1)) अणु
		अगर (Sgl_iszero_mantissa(opnd1)) अणु
			अगर (Sgl_isnotnan(opnd2) && Sgl_isnotnan(opnd3)) अणु
				अगर (Sgl_iszero_exponenपंचांगantissa(opnd2)) अणु
					/* 
					 * invalid since opeअक्रमs are infinity 
					 * and zero 
					 */
					अगर (Is_invalidtrap_enabled())
						वापस(OPC_2E_INVALIDEXCEPTION);
					Set_invalidflag();
					Sgl_makequietnan(resultp1);
					Sgl_copytoptr(resultp1,dstptr);
					वापस(NOEXCEPTION);
				पूर्ण
				/*
				 * Check third opeअक्रम क्रम infinity with a
				 *  sign opposite of the multiply result
				 */
				अगर (Sgl_isinfinity(opnd3) &&
				    (Sgl_sign(resultp1) ^ Sgl_sign(opnd3))) अणु
					/* 
					 * invalid since attempting a magnitude
					 * subtraction of infinities
					 */
					अगर (Is_invalidtrap_enabled())
						वापस(OPC_2E_INVALIDEXCEPTION);
					Set_invalidflag();
					Sgl_makequietnan(resultp1);
					Sgl_copytoptr(resultp1,dstptr);
					वापस(NOEXCEPTION);
				पूर्ण

				/*
			 	 * वापस infinity
			 	 */
				Sgl_setinfinity_exponenपंचांगantissa(resultp1);
				Sgl_copytoptr(resultp1,dstptr);
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
			    		वापस(OPC_2E_INVALIDEXCEPTION);
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
			    		वापस(OPC_2E_INVALIDEXCEPTION);
				/* make NaN quiet */
				Set_invalidflag();
				Sgl_set_quiet(opnd2);
				Sgl_copytoptr(opnd2,dstptr);
				वापस(NOEXCEPTION);
			पूर्ण
			/* 
			 * is third opeअक्रम a संकेतing NaN? 
			 */
			अन्यथा अगर (Sgl_is_संकेतingnan(opnd3)) अणु
				/* trap अगर INVALIDTRAP enabled */
				अगर (Is_invalidtrap_enabled())
			    		वापस(OPC_2E_INVALIDEXCEPTION);
				/* make NaN quiet */
				Set_invalidflag();
				Sgl_set_quiet(opnd3);
				Sgl_copytoptr(opnd3,dstptr);
				वापस(NOEXCEPTION);
			पूर्ण
			/*
		 	 * वापस quiet NaN
		 	 */
			Sgl_copytoptr(opnd1,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
	पूर्ण

	/*
	 * check second opeअक्रम क्रम NaN's or infinity
	 */
	अगर (Sgl_isinfinity_exponent(opnd2)) अणु
		अगर (Sgl_iszero_mantissa(opnd2)) अणु
			अगर (Sgl_isnotnan(opnd3)) अणु
				अगर (Sgl_iszero_exponenपंचांगantissa(opnd1)) अणु
					/* 
					 * invalid since multiply opeअक्रमs are
					 * zero & infinity
					 */
					अगर (Is_invalidtrap_enabled())
						वापस(OPC_2E_INVALIDEXCEPTION);
					Set_invalidflag();
					Sgl_makequietnan(opnd2);
					Sgl_copytoptr(opnd2,dstptr);
					वापस(NOEXCEPTION);
				पूर्ण

				/*
				 * Check third opeअक्रम क्रम infinity with a
				 *  sign opposite of the multiply result
				 */
				अगर (Sgl_isinfinity(opnd3) &&
				    (Sgl_sign(resultp1) ^ Sgl_sign(opnd3))) अणु
					/* 
					 * invalid since attempting a magnitude
					 * subtraction of infinities
					 */
					अगर (Is_invalidtrap_enabled())
				       		वापस(OPC_2E_INVALIDEXCEPTION);
				       	Set_invalidflag();
				       	Sgl_makequietnan(resultp1);
					Sgl_copytoptr(resultp1,dstptr);
					वापस(NOEXCEPTION);
				पूर्ण

				/*
				 * वापस infinity
				 */
				Sgl_setinfinity_exponenपंचांगantissa(resultp1);
				Sgl_copytoptr(resultp1,dstptr);
				वापस(NOEXCEPTION);
			पूर्ण
		पूर्ण
		अन्यथा अणु
			/*
			 * is NaN; संकेतing or quiet?
			 */
			अगर (Sgl_isone_संकेतing(opnd2)) अणु
				/* trap अगर INVALIDTRAP enabled */
				अगर (Is_invalidtrap_enabled())
					वापस(OPC_2E_INVALIDEXCEPTION);
				/* make NaN quiet */
				Set_invalidflag();
				Sgl_set_quiet(opnd2);
			पूर्ण
			/* 
			 * is third opeअक्रम a संकेतing NaN? 
			 */
			अन्यथा अगर (Sgl_is_संकेतingnan(opnd3)) अणु
			       	/* trap अगर INVALIDTRAP enabled */
			       	अगर (Is_invalidtrap_enabled())
				   		वापस(OPC_2E_INVALIDEXCEPTION);
			       	/* make NaN quiet */
			       	Set_invalidflag();
			       	Sgl_set_quiet(opnd3);
				Sgl_copytoptr(opnd3,dstptr);
		       		वापस(NOEXCEPTION);
			पूर्ण
			/*
			 * वापस quiet NaN
			 */
			Sgl_copytoptr(opnd2,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
	पूर्ण

	/*
	 * check third opeअक्रम क्रम NaN's or infinity
	 */
	अगर (Sgl_isinfinity_exponent(opnd3)) अणु
		अगर (Sgl_iszero_mantissa(opnd3)) अणु
			/* वापस infinity */
			Sgl_copytoptr(opnd3,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण अन्यथा अणु
			/*
			 * is NaN; संकेतing or quiet?
			 */
			अगर (Sgl_isone_संकेतing(opnd3)) अणु
				/* trap अगर INVALIDTRAP enabled */
				अगर (Is_invalidtrap_enabled())
					वापस(OPC_2E_INVALIDEXCEPTION);
				/* make NaN quiet */
				Set_invalidflag();
				Sgl_set_quiet(opnd3);
			पूर्ण
			/*
			 * वापस quiet NaN
 			 */
			Sgl_copytoptr(opnd3,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
    	पूर्ण

	/*
	 * Generate multiply mantissa
	 */
	अगर (Sgl_isnotzero_exponent(opnd1)) अणु
		/* set hidden bit */
		Sgl_clear_signexponent_set_hidden(opnd1);
	पूर्ण
	अन्यथा अणु
		/* check क्रम zero */
		अगर (Sgl_iszero_mantissa(opnd1)) अणु
			/*
			 * Perक्रमm the add opnd3 with zero here.
			 */
			अगर (Sgl_iszero_exponenपंचांगantissa(opnd3)) अणु
				अगर (Is_rounding_mode(ROUNDMINUS)) अणु
					Sgl_or_signs(opnd3,resultp1);
				पूर्ण अन्यथा अणु
					Sgl_and_signs(opnd3,resultp1);
				पूर्ण
			पूर्ण
			/*
			 * Now let's check क्रम trapped underflow हाल.
			 */
			अन्यथा अगर (Sgl_iszero_exponent(opnd3) &&
			         Is_underflowtrap_enabled()) अणु
                    		/* need to normalize results mantissa */
                    		sign_save = Sgl_signextendedsign(opnd3);
				result_exponent = 0;
                    		Sgl_leftshअगरtby1(opnd3);
                    		Sgl_normalize(opnd3,result_exponent);
                    		Sgl_set_sign(opnd3,/*using*/sign_save);
                    		Sgl_setwrapped_exponent(opnd3,result_exponent,
							unfl);
                    		Sgl_copytoptr(opnd3,dstptr);
                    		/* inexact = FALSE */
                    		वापस(OPC_2E_UNDERFLOWEXCEPTION);
			पूर्ण
			Sgl_copytoptr(opnd3,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
		/* is denormalized, adjust exponent */
		Sgl_clear_signexponent(opnd1);
		Sgl_leftshअगरtby1(opnd1);
		Sgl_normalize(opnd1,mpy_exponent);
	पूर्ण
	/* opnd2 needs to have hidden bit set with msb in hidden bit */
	अगर (Sgl_isnotzero_exponent(opnd2)) अणु
		Sgl_clear_signexponent_set_hidden(opnd2);
	पूर्ण
	अन्यथा अणु
		/* check क्रम zero */
		अगर (Sgl_iszero_mantissa(opnd2)) अणु
			/*
			 * Perक्रमm the add opnd3 with zero here.
			 */
			अगर (Sgl_iszero_exponenपंचांगantissa(opnd3)) अणु
				अगर (Is_rounding_mode(ROUNDMINUS)) अणु
					Sgl_or_signs(opnd3,resultp1);
				पूर्ण अन्यथा अणु
					Sgl_and_signs(opnd3,resultp1);
				पूर्ण
			पूर्ण
			/*
			 * Now let's check क्रम trapped underflow हाल.
			 */
			अन्यथा अगर (Sgl_iszero_exponent(opnd3) &&
			    Is_underflowtrap_enabled()) अणु
                    		/* need to normalize results mantissa */
                    		sign_save = Sgl_signextendedsign(opnd3);
				result_exponent = 0;
                    		Sgl_leftshअगरtby1(opnd3);
                    		Sgl_normalize(opnd3,result_exponent);
                    		Sgl_set_sign(opnd3,/*using*/sign_save);
                    		Sgl_setwrapped_exponent(opnd3,result_exponent,
							unfl);
                    		Sgl_copytoptr(opnd3,dstptr);
                    		/* inexact = FALSE */
                    		वापस(OPC_2E_UNDERFLOWEXCEPTION);
			पूर्ण
			Sgl_copytoptr(opnd3,dstptr);
			वापस(NOEXCEPTION);
		पूर्ण
		/* is denormalized; want to normalize */
		Sgl_clear_signexponent(opnd2);
		Sgl_leftshअगरtby1(opnd2);
		Sgl_normalize(opnd2,mpy_exponent);
	पूर्ण

	/* Multiply the first two source mantissas together */

	/* 
	 * The पूर्णांकermediate result will be kept in पंचांगpres,
	 * which needs enough room क्रम 106 bits of mantissa,
	 * so lets call it a Double extended.
	 */
	Sglext_setzero(पंचांगpresp1,पंचांगpresp2);

	/* 
	 * Four bits at a समय are inspected in each loop, and a 
	 * simple shअगरt and add multiply algorithm is used. 
	 */ 
	क्रम (count = SGL_P-1; count >= 0; count -= 4) अणु
		Sglext_rightshअगरtby4(पंचांगpresp1,पंचांगpresp2);
		अगर (Sbit28(opnd1)) अणु
	 		/* Twoword_add should be an ADD followed by 2 ADDC's */
			Twoword_add(पंचांगpresp1, पंचांगpresp2, opnd2<<3, 0);
		पूर्ण
		अगर (Sbit29(opnd1)) अणु
			Twoword_add(पंचांगpresp1, पंचांगpresp2, opnd2<<2, 0);
		पूर्ण
		अगर (Sbit30(opnd1)) अणु
			Twoword_add(पंचांगpresp1, पंचांगpresp2, opnd2<<1, 0);
		पूर्ण
		अगर (Sbit31(opnd1)) अणु
			Twoword_add(पंचांगpresp1, पंचांगpresp2, opnd2, 0);
		पूर्ण
		Sgl_rightshअगरtby4(opnd1);
	पूर्ण
	अगर (Is_sexthiddenoverflow(पंचांगpresp1)) अणु
		/* result mantissa >= 2 (mantissa overflow) */
		mpy_exponent++;
		Sglext_rightshअगरtby4(पंचांगpresp1,पंचांगpresp2);
	पूर्ण अन्यथा अणु
		Sglext_rightshअगरtby3(पंचांगpresp1,पंचांगpresp2);
	पूर्ण

	/*
	 * Restore the sign of the mpy result which was saved in resultp1.
	 * The exponent will जारी to be kept in mpy_exponent.
	 */
	Sglext_set_sign(पंचांगpresp1,Sgl_sign(resultp1));

	/* 
	 * No rounding is required, since the result of the multiply
	 * is exact in the extended क्रमmat.
	 */

	/*
	 * Now we are पढ़ोy to perक्रमm the add portion of the operation.
	 *
	 * The exponents need to be kept as पूर्णांकegers क्रम now, since the
	 * multiply result might not fit पूर्णांकo the exponent field.  We
	 * can't overflow or underflow because of this yet, since the
	 * add could bring the final result back पूर्णांकo range.
	 */
	add_exponent = Sgl_exponent(opnd3);

	/*
	 * Check क्रम denormalized or zero add opeअक्रम.
	 */
	अगर (add_exponent == 0) अणु
		/* check क्रम zero */
		अगर (Sgl_iszero_mantissa(opnd3)) अणु
			/* right is zero */
			/* Left can't be zero and must be result.
			 *
			 * The final result is now in पंचांगpres and mpy_exponent,
			 * and needs to be rounded and squeezed back पूर्णांकo
			 * द्विगुन precision क्रमmat from द्विगुन extended.
			 */
			result_exponent = mpy_exponent;
			Sglext_copy(पंचांगpresp1,पंचांगpresp2,resultp1,resultp2);
			sign_save = Sgl_signextendedsign(resultp1);/*save sign*/
			जाओ round;
		पूर्ण

		/* 
		 * Neither are zeroes.  
		 * Adjust exponent and normalize add opeअक्रम.
		 */
		sign_save = Sgl_signextendedsign(opnd3);	/* save sign */
		Sgl_clear_signexponent(opnd3);
		Sgl_leftshअगरtby1(opnd3);
		Sgl_normalize(opnd3,add_exponent);
		Sgl_set_sign(opnd3,sign_save);		/* restore sign */
	पूर्ण अन्यथा अणु
		Sgl_clear_exponent_set_hidden(opnd3);
	पूर्ण
	/*
	 * Copy opnd3 to the द्विगुन extended variable called right.
	 */
	Sgl_copyto_sglext(opnd3,rightp1,rightp2);

	/*
	 * A zero "save" helps discover equal opeअक्रमs (क्रम later),
	 * and is used in swapping opeअक्रमs (अगर needed).
	 */
	Sglext_xortoपूर्णांकp1(पंचांगpresp1,rightp1,/*to*/save);

	/*
	 * Compare magnitude of opeअक्रमs.
	 */
	Sglext_copytoपूर्णांक_exponenपंचांगantissa(पंचांगpresp1,signlessleft1);
	Sglext_copytoपूर्णांक_exponenपंचांगantissa(rightp1,signlessright1);
	अगर (mpy_exponent < add_exponent || mpy_exponent == add_exponent &&
	    Sglext_ismagnitudeless(signlessleft1,signlessright1)) अणु
		/*
		 * Set the left opeअक्रम to the larger one by XOR swap.
		 * First finish the first word "save".
		 */
		Sglext_xorfromपूर्णांकp1(save,rightp1,/*to*/rightp1);
		Sglext_xorfromपूर्णांकp1(save,पंचांगpresp1,/*to*/पंचांगpresp1);
		Sglext_swap_lower(पंचांगpresp2,rightp2);
		/* also setup exponents used in rest of routine */
		dअगरf_exponent = add_exponent - mpy_exponent;
		result_exponent = add_exponent;
	पूर्ण अन्यथा अणु
		/* also setup exponents used in rest of routine */
		dअगरf_exponent = mpy_exponent - add_exponent;
		result_exponent = mpy_exponent;
	पूर्ण
	/* Invariant: left is not smaller than right. */

	/*
	 * Special हाल alignment of opeअक्रमs that would क्रमce alignment
	 * beyond the extent of the extension.  A further optimization
	 * could special हाल this but only reduces the path length क्रम
	 * this infrequent हाल.
	 */
	अगर (dअगरf_exponent > SGLEXT_THRESHOLD) अणु
		dअगरf_exponent = SGLEXT_THRESHOLD;
	पूर्ण

	/* Align right opeअक्रम by shअगरting it to the right */
	Sglext_clear_sign(rightp1);
	Sglext_right_align(rightp1,rightp2,/*shअगरted by*/dअगरf_exponent);
	
	/* Treat sum and dअगरference of the opeअक्रमs separately. */
	अगर ((पूर्णांक)save < 0) अणु
		/*
		 * Dअगरference of the two opeअक्रमs.  Overflow can occur अगर the
		 * multiply overflowed.  A borrow can occur out of the hidden
		 * bit and क्रमce a post normalization phase.
		 */
		Sglext_subtract(पंचांगpresp1,पंचांगpresp2, rightp1,rightp2,
			resultp1,resultp2);
		sign_save = Sgl_signextendedsign(resultp1);
		अगर (Sgl_iszero_hidden(resultp1)) अणु
			/* Handle normalization */
		/* A straightक्रमward algorithm would now shअगरt the
		 * result and extension left until the hidden bit
		 * becomes one.  Not all of the extension bits need
		 * participate in the shअगरt.  Only the two most 
		 * signअगरicant bits (round and guard) are needed.
		 * If only a single shअगरt is needed then the guard
		 * bit becomes a signअगरicant low order bit and the
		 * extension must participate in the rounding.
		 * If more than a single shअगरt is needed, then all
		 * bits to the right of the guard bit are zeros, 
		 * and the guard bit may or may not be zero. */
			Sglext_leftshअगरtby1(resultp1,resultp2);

			/* Need to check क्रम a zero result.  The sign and
			 * exponent fields have alपढ़ोy been zeroed.  The more
			 * efficient test of the full object can be used.
			 */
			 अगर (Sglext_iszero(resultp1,resultp2)) अणु
				/* Must have been "x-x" or "x+(-x)". */
				अगर (Is_rounding_mode(ROUNDMINUS))
					Sgl_setone_sign(resultp1);
				Sgl_copytoptr(resultp1,dstptr);
				वापस(NOEXCEPTION);
			पूर्ण
			result_exponent--;

			/* Look to see अगर normalization is finished. */
			अगर (Sgl_isone_hidden(resultp1)) अणु
				/* No further normalization is needed */
				जाओ round;
			पूर्ण

			/* Discover first one bit to determine shअगरt amount.
			 * Use a modअगरied binary search.  We have alपढ़ोy
			 * shअगरted the result one position right and still
			 * not found a one so the reमुख्यder of the extension
			 * must be zero and simplअगरies rounding. */
			/* Scan bytes */
			जबतक (Sgl_iszero_hiddenhigh7mantissa(resultp1)) अणु
				Sglext_leftshअगरtby8(resultp1,resultp2);
				result_exponent -= 8;
			पूर्ण
			/* Now narrow it करोwn to the nibble */
			अगर (Sgl_iszero_hiddenhigh3mantissa(resultp1)) अणु
				/* The lower nibble contains the
				 * normalizing one */
				Sglext_leftshअगरtby4(resultp1,resultp2);
				result_exponent -= 4;
			पूर्ण
			/* Select हाल where first bit is set (alपढ़ोy
			 * normalized) otherwise select the proper shअगरt. */
			jumpsize = Sgl_hiddenhigh3mantissa(resultp1);
			अगर (jumpsize <= 7) चयन(jumpsize) अणु
			हाल 1:
				Sglext_leftshअगरtby3(resultp1,resultp2);
				result_exponent -= 3;
				अवरोध;
			हाल 2:
			हाल 3:
				Sglext_leftshअगरtby2(resultp1,resultp2);
				result_exponent -= 2;
				अवरोध;
			हाल 4:
			हाल 5:
			हाल 6:
			हाल 7:
				Sglext_leftshअगरtby1(resultp1,resultp2);
				result_exponent -= 1;
				अवरोध;
			पूर्ण
		पूर्ण /* end अगर (hidden...)... */
	/* Fall through and round */
	पूर्ण /* end अगर (save < 0)... */
	अन्यथा अणु
		/* Add magnitudes */
		Sglext_addition(पंचांगpresp1,पंचांगpresp2,
			rightp1,rightp2, /*to*/resultp1,resultp2);
		sign_save = Sgl_signextendedsign(resultp1);
		अगर (Sgl_isone_hiddenoverflow(resultp1)) अणु
	    		/* Prenormalization required. */
	    		Sglext_arithrightshअगरtby1(resultp1,resultp2);
	    		result_exponent++;
		पूर्ण /* end अगर hiddenoverflow... */
	पूर्ण /* end अन्यथा ...add magnitudes... */

	/* Round the result.  If the extension and lower two words are
	 * all zeros, then the result is exact.  Otherwise round in the
	 * correct direction.  Underflow is possible. If a postnormalization
	 * is necessary, then the mantissa is all zeros so no shअगरt is needed.
	 */
  round:
	अगर (result_exponent <= 0 && !Is_underflowtrap_enabled()) अणु
		Sglext_denormalize(resultp1,resultp2,result_exponent,is_tiny);
	पूर्ण
	Sgl_set_sign(resultp1,/*using*/sign_save);
	अगर (Sglext_isnotzero_mantissap2(resultp2)) अणु
		inexact = TRUE;
		चयन(Rounding_mode()) अणु
		हाल ROUNDNEAREST: /* The शेष. */
			अगर (Sglext_isone_highp2(resultp2)) अणु
				/* at least 1/2 ulp */
				अगर (Sglext_isnotzero_low31p2(resultp2) ||
				    Sglext_isone_lowp1(resultp1)) अणु
					/* either exactly half way and odd or
					 * more than 1/2ulp */
					Sgl_increment(resultp1);
				पूर्ण
			पूर्ण
	    		अवरोध;

		हाल ROUNDPLUS:
	    		अगर (Sgl_iszero_sign(resultp1)) अणु
				/* Round up positive results */
				Sgl_increment(resultp1);
			पूर्ण
			अवरोध;
	    
		हाल ROUNDMINUS:
	    		अगर (Sgl_isone_sign(resultp1)) अणु
				/* Round करोwn negative results */
				Sgl_increment(resultp1);
			पूर्ण
	    
		हाल ROUNDZERO:;
			/* truncate is simple */
		पूर्ण /* end चयन... */
		अगर (Sgl_isone_hiddenoverflow(resultp1)) result_exponent++;
	पूर्ण
	अगर (result_exponent >= SGL_अनन्त_EXPONENT) अणु
		/* Overflow */
		अगर (Is_overflowtrap_enabled()) अणु
                        /*
                         * Adjust bias of result
                         */
                        Sgl_setwrapped_exponent(resultp1,result_exponent,ovfl);
                        Sgl_copytoptr(resultp1,dstptr);
                        अगर (inexact)
                            अगर (Is_inexacttrap_enabled())
                                वापस (OPC_2E_OVERFLOWEXCEPTION |
					OPC_2E_INEXACTEXCEPTION);
                            अन्यथा Set_inexactflag();
                        वापस (OPC_2E_OVERFLOWEXCEPTION);
		पूर्ण
		inexact = TRUE;
		Set_overflowflag();
		Sgl_setoverflow(resultp1);
	पूर्ण अन्यथा अगर (result_exponent <= 0) अणु	/* underflow हाल */
		अगर (Is_underflowtrap_enabled()) अणु
                        /*
                         * Adjust bias of result
                         */
                	Sgl_setwrapped_exponent(resultp1,result_exponent,unfl);
			Sgl_copytoptr(resultp1,dstptr);
                        अगर (inexact)
                            अगर (Is_inexacttrap_enabled())
                                वापस (OPC_2E_UNDERFLOWEXCEPTION |
					OPC_2E_INEXACTEXCEPTION);
                            अन्यथा Set_inexactflag();
	    		वापस(OPC_2E_UNDERFLOWEXCEPTION);
		पूर्ण
		अन्यथा अगर (inexact && is_tiny) Set_underflowflag();
	पूर्ण
	अन्यथा Sgl_set_exponent(resultp1,result_exponent);
	Sgl_copytoptr(resultp1,dstptr);
	अगर (inexact) 
		अगर (Is_inexacttrap_enabled()) वापस(OPC_2E_INEXACTEXCEPTION);
		अन्यथा Set_inexactflag();
    	वापस(NOEXCEPTION);
पूर्ण

