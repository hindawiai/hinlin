<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Linux/PA-RISC Project (http://www.parisc-linux.org/)
 *
 * Floating-poपूर्णांक emulation code
 *  Copyright (C) 2001 Hewlett-Packard (Paul Bame) <bame@debian.org>
 */
#अगर_घोषित __NO_PA_HDRS
    PA header file -- करो not include this header file क्रम non-PA builds.
#पूर्ण_अगर

/* 32-bit word grabbing functions */
#घोषणा Dbl_firstword(value) Dallp1(value)
#घोषणा Dbl_secondword(value) Dallp2(value)
#घोषणा Dbl_thirdword(value) dummy_location
#घोषणा Dbl_fourthword(value) dummy_location

#घोषणा Dbl_sign(object) Dsign(object)
#घोषणा Dbl_exponent(object) Dexponent(object)
#घोषणा Dbl_signexponent(object) Dsignexponent(object)
#घोषणा Dbl_mantissap1(object) Dmantissap1(object)
#घोषणा Dbl_mantissap2(object) Dmantissap2(object)
#घोषणा Dbl_exponenपंचांगantissap1(object) Dexponenपंचांगantissap1(object)
#घोषणा Dbl_allp1(object) Dallp1(object)
#घोषणा Dbl_allp2(object) Dallp2(object)

/* dbl_and_signs ANDs the sign bits of each argument and माला_दो the result
 * पूर्णांकo the first argument. dbl_or_signs ors those same sign bits */
#घोषणा Dbl_and_signs( src1dst, src2)		\
    Dallp1(src1dst) = (Dallp1(src2)|~((अचिन्हित पूर्णांक)1<<31)) & Dallp1(src1dst)
#घोषणा Dbl_or_signs( src1dst, src2)		\
    Dallp1(src1dst) = (Dallp1(src2)&((अचिन्हित पूर्णांक)1<<31)) | Dallp1(src1dst)

/* The hidden bit is always the low bit of the exponent */
#घोषणा Dbl_clear_exponent_set_hidden(srcdst) Deposit_dexponent(srcdst,1)
#घोषणा Dbl_clear_signexponent_set_hidden(srcdst) \
    Deposit_dsignexponent(srcdst,1)
#घोषणा Dbl_clear_sign(srcdst) Dallp1(srcdst) &= ~((अचिन्हित पूर्णांक)1<<31)
#घोषणा Dbl_clear_signexponent(srcdst) \
    Dallp1(srcdst) &= Dmantissap1((अचिन्हित पूर्णांक)-1)

/* Exponent field क्रम द्विगुनs has alपढ़ोy been cleared and may be
 * included in the shअगरt.  Here we need to generate two द्विगुन width
 * variable shअगरts.  The insignअगरicant bits can be ignored.
 *      MTSAR f(varamount)
 *      VSHD	srcdst.high,srcdst.low => srcdst.low
 *	VSHD	0,srcdst.high => srcdst.high 
 * This is very dअगरficult to model with C expressions since the shअगरt amount
 * could exceed 32.  */
/* varamount must be less than 64 */
#घोषणा Dbl_rightshअगरt(srcdstA, srcdstB, varamount)			\
    अणुअगर((varamount) >= 32) अणु						\
        Dallp2(srcdstB) = Dallp1(srcdstA) >> (varamount-32);		\
        Dallp1(srcdstA)=0;						\
    पूर्ण									\
    अन्यथा अगर(varamount > 0) अणु						\
	Variable_shअगरt_द्विगुन(Dallp1(srcdstA), Dallp2(srcdstB), 	\
	  (varamount), Dallp2(srcdstB));				\
	Dallp1(srcdstA) >>= varamount;					\
    पूर्ण पूर्ण
/* varamount must be less than 64 */
#घोषणा Dbl_rightshअगरt_exponenपंचांगantissa(srcdstA, srcdstB, varamount)	\
    अणुअगर((varamount) >= 32) अणु						\
        Dallp2(srcdstB) = Dexponenपंचांगantissap1(srcdstA) >> (varamount-32); \
	Dallp1(srcdstA) &= ((अचिन्हित पूर्णांक)1<<31);  /* clear expmant field */ \
    पूर्ण									\
    अन्यथा अगर(varamount > 0) अणु						\
	Variable_shअगरt_द्विगुन(Dexponenपंचांगantissap1(srcdstA), Dallp2(srcdstB), \
	(varamount), Dallp2(srcdstB));					\
	Deposit_dexponenपंचांगantissap1(srcdstA,				\
	    (Dexponenपंचांगantissap1(srcdstA)>>varamount));			\
    पूर्ण पूर्ण
/* varamount must be less than 64 */
#घोषणा Dbl_leftshअगरt(srcdstA, srcdstB, varamount)			\
    अणुअगर((varamount) >= 32) अणु						\
	Dallp1(srcdstA) = Dallp2(srcdstB) << (varamount-32);		\
	Dallp2(srcdstB)=0;						\
    पूर्ण									\
    अन्यथा अणु								\
	अगर ((varamount) > 0) अणु						\
	    Dallp1(srcdstA) = (Dallp1(srcdstA) << (varamount)) |	\
		(Dallp2(srcdstB) >> (32-(varamount)));			\
	    Dallp2(srcdstB) <<= varamount;				\
	पूर्ण								\
    पूर्ण पूर्ण
#घोषणा Dbl_leftshअगरtby1_withextent(lefta,leftb,right,resulta,resultb)	\
    Shअगरtद्विगुन(Dallp1(lefta), Dallp2(leftb), 31, Dallp1(resulta));	\
    Shअगरtद्विगुन(Dallp2(leftb), Extall(right), 31, Dallp2(resultb)) 
    
#घोषणा Dbl_rightshअगरtby1_withextent(leftb,right,dst)		\
    Extall(dst) = (Dallp2(leftb) << 31) | ((अचिन्हित पूर्णांक)Extall(right) >> 1) | \
		  Extlow(right)

#घोषणा Dbl_arithrightshअगरtby1(srcdstA,srcdstB)			\
    Shअगरtद्विगुन(Dallp1(srcdstA),Dallp2(srcdstB),1,Dallp2(srcdstB));\
    Dallp1(srcdstA) = (पूर्णांक)Dallp1(srcdstA) >> 1
   
/* Sign extend the sign bit with an पूर्णांकeger destination */
#घोषणा Dbl_signextendedsign(value)  Dचिन्हितsign(value)

#घोषणा Dbl_isone_hidden(dbl_value) (Is_dhidden(dbl_value)!=0)
/* Singles and द्विगुनs may include the sign and exponent fields.  The
 * hidden bit and the hidden overflow must be included. */
#घोषणा Dbl_increment(dbl_valueA,dbl_valueB) \
    अगर( (Dallp2(dbl_valueB) += 1) == 0 )  Dallp1(dbl_valueA) += 1
#घोषणा Dbl_increment_mantissa(dbl_valueA,dbl_valueB) \
    अगर( (Dmantissap2(dbl_valueB) += 1) == 0 )  \
    Deposit_dmantissap1(dbl_valueA,dbl_valueA+1)
#घोषणा Dbl_decrement(dbl_valueA,dbl_valueB) \
    अगर( Dallp2(dbl_valueB) == 0 )  Dallp1(dbl_valueA) -= 1; \
    Dallp2(dbl_valueB) -= 1

#घोषणा Dbl_isone_sign(dbl_value) (Is_dsign(dbl_value)!=0)
#घोषणा Dbl_isone_hiddenoverflow(dbl_value) (Is_dhiddenoverflow(dbl_value)!=0)
#घोषणा Dbl_isone_lowmantissap1(dbl_valueA) (Is_dlowp1(dbl_valueA)!=0)
#घोषणा Dbl_isone_lowmantissap2(dbl_valueB) (Is_dlowp2(dbl_valueB)!=0)
#घोषणा Dbl_isone_संकेतing(dbl_value) (Is_dसंकेतing(dbl_value)!=0)
#घोषणा Dbl_is_संकेतingnan(dbl_value) (Dसंकेतingnan(dbl_value)==0xfff)
#घोषणा Dbl_isnotzero(dbl_valueA,dbl_valueB) \
    (Dallp1(dbl_valueA) || Dallp2(dbl_valueB))
#घोषणा Dbl_isnotzero_hiddenhigh7mantissa(dbl_value) \
    (Dhiddenhigh7mantissa(dbl_value)!=0)
#घोषणा Dbl_isnotzero_exponent(dbl_value) (Dexponent(dbl_value)!=0)
#घोषणा Dbl_isnotzero_mantissa(dbl_valueA,dbl_valueB) \
    (Dmantissap1(dbl_valueA) || Dmantissap2(dbl_valueB))
#घोषणा Dbl_isnotzero_mantissap1(dbl_valueA) (Dmantissap1(dbl_valueA)!=0)
#घोषणा Dbl_isnotzero_mantissap2(dbl_valueB) (Dmantissap2(dbl_valueB)!=0)
#घोषणा Dbl_isnotzero_exponenपंचांगantissa(dbl_valueA,dbl_valueB) \
    (Dexponenपंचांगantissap1(dbl_valueA) || Dmantissap2(dbl_valueB))
#घोषणा Dbl_isnotzero_low4p2(dbl_value) (Dlow4p2(dbl_value)!=0)
#घोषणा Dbl_iszero(dbl_valueA,dbl_valueB) (Dallp1(dbl_valueA)==0 && \
    Dallp2(dbl_valueB)==0)
#घोषणा Dbl_iszero_allp1(dbl_value) (Dallp1(dbl_value)==0)
#घोषणा Dbl_iszero_allp2(dbl_value) (Dallp2(dbl_value)==0)
#घोषणा Dbl_iszero_hidden(dbl_value) (Is_dhidden(dbl_value)==0)
#घोषणा Dbl_iszero_hiddenoverflow(dbl_value) (Is_dhiddenoverflow(dbl_value)==0)
#घोषणा Dbl_iszero_hiddenhigh3mantissa(dbl_value) \
    (Dhiddenhigh3mantissa(dbl_value)==0)
#घोषणा Dbl_iszero_hiddenhigh7mantissa(dbl_value) \
    (Dhiddenhigh7mantissa(dbl_value)==0)
#घोषणा Dbl_iszero_sign(dbl_value) (Is_dsign(dbl_value)==0)
#घोषणा Dbl_iszero_exponent(dbl_value) (Dexponent(dbl_value)==0)
#घोषणा Dbl_iszero_mantissa(dbl_valueA,dbl_valueB) \
    (Dmantissap1(dbl_valueA)==0 && Dmantissap2(dbl_valueB)==0)
#घोषणा Dbl_iszero_exponenपंचांगantissa(dbl_valueA,dbl_valueB) \
    (Dexponenपंचांगantissap1(dbl_valueA)==0 && Dmantissap2(dbl_valueB)==0)
#घोषणा Dbl_isinfinity_exponent(dbl_value)		\
    (Dexponent(dbl_value)==DBL_अनन्त_EXPONENT)
#घोषणा Dbl_isnotinfinity_exponent(dbl_value)		\
    (Dexponent(dbl_value)!=DBL_अनन्त_EXPONENT)
#घोषणा Dbl_isinfinity(dbl_valueA,dbl_valueB)			\
    (Dexponent(dbl_valueA)==DBL_अनन्त_EXPONENT &&	\
    Dmantissap1(dbl_valueA)==0 && Dmantissap2(dbl_valueB)==0)
#घोषणा Dbl_isnan(dbl_valueA,dbl_valueB)		\
    (Dexponent(dbl_valueA)==DBL_अनन्त_EXPONENT &&	\
    (Dmantissap1(dbl_valueA)!=0 || Dmantissap2(dbl_valueB)!=0))
#घोषणा Dbl_isnotnan(dbl_valueA,dbl_valueB)		\
    (Dexponent(dbl_valueA)!=DBL_अनन्त_EXPONENT ||	\
    (Dmantissap1(dbl_valueA)==0 && Dmantissap2(dbl_valueB)==0))

#घोषणा Dbl_islessthan(dbl_op1a,dbl_op1b,dbl_op2a,dbl_op2b)	\
    (Dallp1(dbl_op1a) < Dallp1(dbl_op2a) ||			\
     (Dallp1(dbl_op1a) == Dallp1(dbl_op2a) &&			\
      Dallp2(dbl_op1b) < Dallp2(dbl_op2b)))
#घोषणा Dbl_isgreaterthan(dbl_op1a,dbl_op1b,dbl_op2a,dbl_op2b)	\
    (Dallp1(dbl_op1a) > Dallp1(dbl_op2a) ||			\
     (Dallp1(dbl_op1a) == Dallp1(dbl_op2a) &&			\
      Dallp2(dbl_op1b) > Dallp2(dbl_op2b)))
#घोषणा Dbl_isnotlessthan(dbl_op1a,dbl_op1b,dbl_op2a,dbl_op2b)	\
    (Dallp1(dbl_op1a) > Dallp1(dbl_op2a) ||			\
     (Dallp1(dbl_op1a) == Dallp1(dbl_op2a) &&			\
      Dallp2(dbl_op1b) >= Dallp2(dbl_op2b)))
#घोषणा Dbl_isnotgreaterthan(dbl_op1a,dbl_op1b,dbl_op2a,dbl_op2b) \
    (Dallp1(dbl_op1a) < Dallp1(dbl_op2a) ||			\
     (Dallp1(dbl_op1a) == Dallp1(dbl_op2a) &&			\
      Dallp2(dbl_op1b) <= Dallp2(dbl_op2b)))
#घोषणा Dbl_isequal(dbl_op1a,dbl_op1b,dbl_op2a,dbl_op2b)	\
     ((Dallp1(dbl_op1a) == Dallp1(dbl_op2a)) &&			\
      (Dallp2(dbl_op1b) == Dallp2(dbl_op2b)))

#घोषणा Dbl_leftshअगरtby8(dbl_valueA,dbl_valueB) \
    Shअगरtद्विगुन(Dallp1(dbl_valueA),Dallp2(dbl_valueB),24,Dallp1(dbl_valueA)); \
    Dallp2(dbl_valueB) <<= 8
#घोषणा Dbl_leftshअगरtby7(dbl_valueA,dbl_valueB) \
    Shअगरtद्विगुन(Dallp1(dbl_valueA),Dallp2(dbl_valueB),25,Dallp1(dbl_valueA)); \
    Dallp2(dbl_valueB) <<= 7
#घोषणा Dbl_leftshअगरtby4(dbl_valueA,dbl_valueB) \
    Shअगरtद्विगुन(Dallp1(dbl_valueA),Dallp2(dbl_valueB),28,Dallp1(dbl_valueA)); \
    Dallp2(dbl_valueB) <<= 4
#घोषणा Dbl_leftshअगरtby3(dbl_valueA,dbl_valueB) \
    Shअगरtद्विगुन(Dallp1(dbl_valueA),Dallp2(dbl_valueB),29,Dallp1(dbl_valueA)); \
    Dallp2(dbl_valueB) <<= 3
#घोषणा Dbl_leftshअगरtby2(dbl_valueA,dbl_valueB) \
    Shअगरtद्विगुन(Dallp1(dbl_valueA),Dallp2(dbl_valueB),30,Dallp1(dbl_valueA)); \
    Dallp2(dbl_valueB) <<= 2
#घोषणा Dbl_leftshअगरtby1(dbl_valueA,dbl_valueB) \
    Shअगरtद्विगुन(Dallp1(dbl_valueA),Dallp2(dbl_valueB),31,Dallp1(dbl_valueA)); \
    Dallp2(dbl_valueB) <<= 1

#घोषणा Dbl_rightshअगरtby8(dbl_valueA,dbl_valueB) \
    Shअगरtद्विगुन(Dallp1(dbl_valueA),Dallp2(dbl_valueB),8,Dallp2(dbl_valueB)); \
    Dallp1(dbl_valueA) >>= 8
#घोषणा Dbl_rightshअगरtby4(dbl_valueA,dbl_valueB) \
    Shअगरtद्विगुन(Dallp1(dbl_valueA),Dallp2(dbl_valueB),4,Dallp2(dbl_valueB)); \
    Dallp1(dbl_valueA) >>= 4
#घोषणा Dbl_rightshअगरtby2(dbl_valueA,dbl_valueB) \
    Shअगरtद्विगुन(Dallp1(dbl_valueA),Dallp2(dbl_valueB),2,Dallp2(dbl_valueB)); \
    Dallp1(dbl_valueA) >>= 2
#घोषणा Dbl_rightshअगरtby1(dbl_valueA,dbl_valueB) \
    Shअगरtद्विगुन(Dallp1(dbl_valueA),Dallp2(dbl_valueB),1,Dallp2(dbl_valueB)); \
    Dallp1(dbl_valueA) >>= 1
    
/* This magnitude comparison uses the signless first words and
 * the regular part2 words.  The comparison is graphically:
 *
 *       1st greater?  -------------
 *                                 |
 *       1st less?-----------------+---------
 *                                 |        |
 *       2nd greater or equal----->|        |
 *                               False     True
 */
#घोषणा Dbl_ismagnitudeless(leftB,rightB,signlessleft,signlessright)	\
      ((signlessleft <= signlessright) &&				\
       ( (signlessleft < signlessright) || (Dallp2(leftB)<Dallp2(rightB)) ))
    
#घोषणा Dbl_copytoपूर्णांक_exponenपंचांगantissap1(src,dest) \
    dest = Dexponenपंचांगantissap1(src)

/* A quiet NaN has the high mantissa bit clear and at least on other (in this
 * हाल the adjacent bit) bit set. */
#घोषणा Dbl_set_quiet(dbl_value) Deposit_dhigh2mantissa(dbl_value,1)
#घोषणा Dbl_set_exponent(dbl_value, exp) Deposit_dexponent(dbl_value,exp)

#घोषणा Dbl_set_mantissa(desta,destb,valuea,valueb)	\
    Deposit_dmantissap1(desta,valuea);			\
    Dmantissap2(destb) = Dmantissap2(valueb)
#घोषणा Dbl_set_mantissap1(desta,valuea)		\
    Deposit_dmantissap1(desta,valuea)
#घोषणा Dbl_set_mantissap2(destb,valueb)		\
    Dmantissap2(destb) = Dmantissap2(valueb)

#घोषणा Dbl_set_exponenपंचांगantissa(desta,destb,valuea,valueb)	\
    Deposit_dexponenपंचांगantissap1(desta,valuea);			\
    Dmantissap2(destb) = Dmantissap2(valueb)
#घोषणा Dbl_set_exponenपंचांगantissap1(dest,value)			\
    Deposit_dexponenपंचांगantissap1(dest,value)

#घोषणा Dbl_copyfromptr(src,desta,destb) \
    Dallp1(desta) = src->wd0;		\
    Dallp2(destb) = src->wd1 
#घोषणा Dbl_copytoptr(srca,srcb,dest)	\
    dest->wd0 = Dallp1(srca);		\
    dest->wd1 = Dallp2(srcb)

/*  An infinity is represented with the max exponent and a zero mantissa */
#घोषणा Dbl_setinfinity_exponent(dbl_value) \
    Deposit_dexponent(dbl_value,DBL_अनन्त_EXPONENT)
#घोषणा Dbl_setinfinity_exponenपंचांगantissa(dbl_valueA,dbl_valueB)	\
    Deposit_dexponenपंचांगantissap1(dbl_valueA, 			\
    (DBL_अनन्त_EXPONENT << (32-(1+DBL_EXP_LENGTH))));	\
    Dmantissap2(dbl_valueB) = 0
#घोषणा Dbl_setinfinitypositive(dbl_valueA,dbl_valueB)		\
    Dallp1(dbl_valueA) 						\
        = (DBL_अनन्त_EXPONENT << (32-(1+DBL_EXP_LENGTH)));	\
    Dmantissap2(dbl_valueB) = 0
#घोषणा Dbl_setinfinitynegative(dbl_valueA,dbl_valueB)		\
    Dallp1(dbl_valueA) = ((अचिन्हित पूर्णांक)1<<31) |		\
         (DBL_अनन्त_EXPONENT << (32-(1+DBL_EXP_LENGTH)));	\
    Dmantissap2(dbl_valueB) = 0
#घोषणा Dbl_setinfinity(dbl_valueA,dbl_valueB,sign)		\
    Dallp1(dbl_valueA) = ((अचिन्हित पूर्णांक)sign << 31) | 		\
	(DBL_अनन्त_EXPONENT << (32-(1+DBL_EXP_LENGTH)));	\
    Dmantissap2(dbl_valueB) = 0

#घोषणा Dbl_sethigh4bits(dbl_value, extsign) Deposit_dhigh4p1(dbl_value,extsign)
#घोषणा Dbl_set_sign(dbl_value,sign) Deposit_dsign(dbl_value,sign)
#घोषणा Dbl_invert_sign(dbl_value) Deposit_dsign(dbl_value,~Dsign(dbl_value))
#घोषणा Dbl_setone_sign(dbl_value) Deposit_dsign(dbl_value,1)
#घोषणा Dbl_setone_lowmantissap2(dbl_value) Deposit_dlowp2(dbl_value,1)
#घोषणा Dbl_setzero_sign(dbl_value) Dallp1(dbl_value) &= 0x7fffffff
#घोषणा Dbl_setzero_exponent(dbl_value) 		\
    Dallp1(dbl_value) &= 0x800fffff
#घोषणा Dbl_setzero_mantissa(dbl_valueA,dbl_valueB)	\
    Dallp1(dbl_valueA) &= 0xfff00000; 			\
    Dallp2(dbl_valueB) = 0
#घोषणा Dbl_setzero_mantissap1(dbl_value) Dallp1(dbl_value) &= 0xfff00000
#घोषणा Dbl_setzero_mantissap2(dbl_value) Dallp2(dbl_value) = 0
#घोषणा Dbl_setzero_exponenपंचांगantissa(dbl_valueA,dbl_valueB)	\
    Dallp1(dbl_valueA) &= 0x80000000;		\
    Dallp2(dbl_valueB) = 0
#घोषणा Dbl_setzero_exponenपंचांगantissap1(dbl_valueA)	\
    Dallp1(dbl_valueA) &= 0x80000000
#घोषणा Dbl_setzero(dbl_valueA,dbl_valueB) \
    Dallp1(dbl_valueA) = 0; Dallp2(dbl_valueB) = 0
#घोषणा Dbl_setzerop1(dbl_value) Dallp1(dbl_value) = 0
#घोषणा Dbl_setzerop2(dbl_value) Dallp2(dbl_value) = 0
#घोषणा Dbl_setnegativezero(dbl_value) \
    Dallp1(dbl_value) = (अचिन्हित पूर्णांक)1 << 31; Dallp2(dbl_value) = 0
#घोषणा Dbl_setnegativezerop1(dbl_value) Dallp1(dbl_value) = (अचिन्हित पूर्णांक)1<<31

/* Use the following macro क्रम both overflow & underflow conditions */
#घोषणा ovfl -
#घोषणा unfl +
#घोषणा Dbl_setwrapped_exponent(dbl_value,exponent,op) \
    Deposit_dexponent(dbl_value,(exponent op DBL_WRAP))

#घोषणा Dbl_setlargestpositive(dbl_valueA,dbl_valueB) 			\
    Dallp1(dbl_valueA) = ((DBL_EMAX+DBL_BIAS) << (32-(1+DBL_EXP_LENGTH))) \
			| ((1<<(32-(1+DBL_EXP_LENGTH))) - 1 );		\
    Dallp2(dbl_valueB) = 0xFFFFFFFF
#घोषणा Dbl_setlargestnegative(dbl_valueA,dbl_valueB) 			\
    Dallp1(dbl_valueA) = ((DBL_EMAX+DBL_BIAS) << (32-(1+DBL_EXP_LENGTH))) \
			| ((1<<(32-(1+DBL_EXP_LENGTH))) - 1 )		\
			| ((अचिन्हित पूर्णांक)1<<31);			\
    Dallp2(dbl_valueB) = 0xFFFFFFFF
#घोषणा Dbl_setlargest_exponenपंचांगantissa(dbl_valueA,dbl_valueB)		\
    Deposit_dexponenपंचांगantissap1(dbl_valueA,				\
	(((DBL_EMAX+DBL_BIAS) << (32-(1+DBL_EXP_LENGTH)))		\
			| ((1<<(32-(1+DBL_EXP_LENGTH))) - 1 )));	\
    Dallp2(dbl_valueB) = 0xFFFFFFFF

#घोषणा Dbl_setnegativeinfinity(dbl_valueA,dbl_valueB) 			\
    Dallp1(dbl_valueA) = ((1<<DBL_EXP_LENGTH) | DBL_अनन्त_EXPONENT) 	\
			 << (32-(1+DBL_EXP_LENGTH)) ; 			\
    Dallp2(dbl_valueB) = 0
#घोषणा Dbl_setlargest(dbl_valueA,dbl_valueB,sign)			\
    Dallp1(dbl_valueA) = ((अचिन्हित पूर्णांक)sign << 31) |			\
         ((DBL_EMAX+DBL_BIAS) << (32-(1+DBL_EXP_LENGTH))) |	 	\
	 ((1 << (32-(1+DBL_EXP_LENGTH))) - 1 );				\
    Dallp2(dbl_valueB) = 0xFFFFFFFF
    

/* The high bit is always zero so arithmetic or logical shअगरts will work. */
#घोषणा Dbl_right_align(srcdstA,srcdstB,shअगरt,extent)			\
    अगर( shअगरt >= 32 ) 							\
	अणु								\
	/* Big shअगरt requires examining the portion shअगरt off 		\
	the end to properly set inexact.  */				\
	अगर(shअगरt < 64)							\
	    अणु								\
	    अगर(shअगरt > 32)						\
		अणु							\
	        Variable_shअगरt_द्विगुन(Dallp1(srcdstA),Dallp2(srcdstB),	\
		 shअगरt-32, Extall(extent));				\
	        अगर(Dallp2(srcdstB) << 64 - (shअगरt)) Ext_setone_low(extent); \
	        पूर्ण							\
	    अन्यथा Extall(extent) = Dallp2(srcdstB);			\
	    Dallp2(srcdstB) = Dallp1(srcdstA) >> (shअगरt - 32);		\
	    पूर्ण								\
	अन्यथा								\
	    अणु								\
	    Extall(extent) = Dallp1(srcdstA);				\
	    अगर(Dallp2(srcdstB)) Ext_setone_low(extent);			\
	    Dallp2(srcdstB) = 0;					\
	    पूर्ण								\
	Dallp1(srcdstA) = 0;						\
	पूर्ण								\
    अन्यथा								\
	अणु								\
	/* Small alignment is simpler.  Extension is easily set. */	\
	अगर (shअगरt > 0)							\
	    अणु								\
	    Extall(extent) = Dallp2(srcdstB) << 32 - (shअगरt);		\
	    Variable_shअगरt_द्विगुन(Dallp1(srcdstA),Dallp2(srcdstB),shअगरt, \
	     Dallp2(srcdstB));						\
	    Dallp1(srcdstA) >>= shअगरt;					\
	    पूर्ण								\
	अन्यथा Extall(extent) = 0;					\
	पूर्ण

/* 
 * Here we need to shअगरt the result right to correct क्रम an overshअगरt
 * (due to the exponent becoming negative) during normalization.
 */
#घोषणा Dbl_fix_overshअगरt(srcdstA,srcdstB,shअगरt,extent)			\
	    Extall(extent) = Dallp2(srcdstB) << 32 - (shअगरt);		\
	    Dallp2(srcdstB) = (Dallp1(srcdstA) << 32 - (shअगरt)) |	\
		(Dallp2(srcdstB) >> (shअगरt));				\
	    Dallp1(srcdstA) = Dallp1(srcdstA) >> shअगरt

#घोषणा Dbl_hiddenhigh3mantissa(dbl_value) Dhiddenhigh3mantissa(dbl_value)
#घोषणा Dbl_hidden(dbl_value) Dhidden(dbl_value)
#घोषणा Dbl_lowmantissap2(dbl_value) Dlowp2(dbl_value)

/* The left argument is never smaller than the right argument */
#घोषणा Dbl_subtract(lefta,leftb,righta,rightb,resulta,resultb)			\
    अगर( Dallp2(rightb) > Dallp2(leftb) ) Dallp1(lefta)--;	\
    Dallp2(resultb) = Dallp2(leftb) - Dallp2(rightb);		\
    Dallp1(resulta) = Dallp1(lefta) - Dallp1(righta)

/* Subtract right augmented with extension from left augmented with zeros and
 * store पूर्णांकo result and extension. */
#घोषणा Dbl_subtract_withextension(lefta,leftb,righta,rightb,extent,resulta,resultb)	\
    Dbl_subtract(lefta,leftb,righta,rightb,resulta,resultb);		\
    अगर( (Extall(extent) = 0-Extall(extent)) )				\
        अणु								\
        अगर((Dallp2(resultb)--) == 0) Dallp1(resulta)--;			\
        पूर्ण

#घोषणा Dbl_addition(lefta,leftb,righta,rightb,resulta,resultb)		\
    /* If the sum of the low words is less than either source, then	\
     * an overflow पूर्णांकo the next word occurred. */			\
    Dallp1(resulta) = Dallp1(lefta) + Dallp1(righta);			\
    अगर((Dallp2(resultb) = Dallp2(leftb) + Dallp2(rightb)) < Dallp2(rightb)) \
	Dallp1(resulta)++

#घोषणा Dbl_xortoपूर्णांकp1(left,right,result)			\
    result = Dallp1(left) XOR Dallp1(right)

#घोषणा Dbl_xorfromपूर्णांकp1(left,right,result)			\
    Dallp1(result) = left XOR Dallp1(right)

#घोषणा Dbl_swap_lower(left,right)				\
    Dallp2(left)  = Dallp2(left) XOR Dallp2(right);		\
    Dallp2(right) = Dallp2(left) XOR Dallp2(right);		\
    Dallp2(left)  = Dallp2(left) XOR Dallp2(right)

/* Need to Initialize */
#घोषणा Dbl_makequietnan(desta,destb)					\
    Dallp1(desta) = ((DBL_EMAX+DBL_BIAS)+1)<< (32-(1+DBL_EXP_LENGTH))	\
                 | (1<<(32-(1+DBL_EXP_LENGTH+2)));			\
    Dallp2(destb) = 0
#घोषणा Dbl_makeसंकेतingnan(desta,destb)				\
    Dallp1(desta) = ((DBL_EMAX+DBL_BIAS)+1)<< (32-(1+DBL_EXP_LENGTH))	\
                 | (1<<(32-(1+DBL_EXP_LENGTH+1)));			\
    Dallp2(destb) = 0

#घोषणा Dbl_normalize(dbl_opndA,dbl_opndB,exponent)			\
	जबतक(Dbl_iszero_hiddenhigh7mantissa(dbl_opndA)) अणु		\
		Dbl_leftshअगरtby8(dbl_opndA,dbl_opndB);			\
		exponent -= 8;						\
	पूर्ण								\
	अगर(Dbl_iszero_hiddenhigh3mantissa(dbl_opndA)) अणु			\
		Dbl_leftshअगरtby4(dbl_opndA,dbl_opndB);			\
		exponent -= 4;						\
	पूर्ण								\
	जबतक(Dbl_iszero_hidden(dbl_opndA)) अणु				\
		Dbl_leftshअगरtby1(dbl_opndA,dbl_opndB);			\
		exponent -= 1;						\
	पूर्ण

#घोषणा Twoword_add(src1dstA,src1dstB,src2A,src2B)		\
	/* 							\
	 * want this macro to generate:				\
	 *	ADD	src1dstB,src2B,src1dstB;		\
	 *	ADDC	src1dstA,src2A,src1dstA;		\
	 */							\
	अगर ((src1dstB) + (src2B) < (src1dstB)) Dallp1(src1dstA)++; \
	Dallp1(src1dstA) += (src2A);				\
	Dallp2(src1dstB) += (src2B)

#घोषणा Twoword_subtract(src1dstA,src1dstB,src2A,src2B)		\
	/* 							\
	 * want this macro to generate:				\
	 *	SUB	src1dstB,src2B,src1dstB;		\
	 *	SUBB	src1dstA,src2A,src1dstA;		\
	 */							\
	अगर ((src1dstB) < (src2B)) Dallp1(src1dstA)--;		\
	Dallp1(src1dstA) -= (src2A);				\
	Dallp2(src1dstB) -= (src2B)

#घोषणा Dbl_setoverflow(resultA,resultB)				\
	/* set result to infinity or largest number */			\
	चयन (Rounding_mode()) अणु					\
		हाल ROUNDPLUS:						\
			अगर (Dbl_isone_sign(resultA)) अणु			\
				Dbl_setlargestnegative(resultA,resultB); \
			पूर्ण						\
			अन्यथा अणु						\
				Dbl_setinfinitypositive(resultA,resultB); \
			पूर्ण						\
			अवरोध;						\
		हाल ROUNDMINUS:					\
			अगर (Dbl_iszero_sign(resultA)) अणु			\
				Dbl_setlargestpositive(resultA,resultB); \
			पूर्ण						\
			अन्यथा अणु						\
				Dbl_setinfinitynegative(resultA,resultB); \
			पूर्ण						\
			अवरोध;						\
		हाल ROUNDNEAREST:					\
			Dbl_setinfinity_exponenपंचांगantissa(resultA,resultB); \
			अवरोध;						\
		हाल ROUNDZERO:						\
			Dbl_setlargest_exponenपंचांगantissa(resultA,resultB); \
	पूर्ण

#घोषणा Dbl_denormalize(opndp1,opndp2,exponent,guard,sticky,inexact)	\
    Dbl_clear_signexponent_set_hidden(opndp1);				\
    अगर (exponent >= (1-DBL_P)) अणु					\
	अगर (exponent >= -31) अणु						\
	    guard = (Dallp2(opndp2) >> -exponent) & 1;			\
	    अगर (exponent < 0) sticky |= Dallp2(opndp2) << (32+exponent); \
	    अगर (exponent > -31) अणु					\
		Variable_shअगरt_द्विगुन(opndp1,opndp2,1-exponent,opndp2);	\
		Dallp1(opndp1) >>= 1-exponent;				\
	    पूर्ण								\
	    अन्यथा अणु							\
		Dallp2(opndp2) = Dallp1(opndp1);			\
		Dbl_setzerop1(opndp1);					\
	    पूर्ण								\
	पूर्ण								\
	अन्यथा अणु								\
	    guard = (Dallp1(opndp1) >> -32-exponent) & 1;		\
	    अगर (exponent == -32) sticky |= Dallp2(opndp2);		\
	    अन्यथा sticky |= (Dallp2(opndp2) | Dallp1(opndp1) << 64+exponent); \
	    Dallp2(opndp2) = Dallp1(opndp1) >> -31-exponent;		\
	    Dbl_setzerop1(opndp1);					\
	पूर्ण								\
	inexact = guard | sticky;					\
    पूर्ण									\
    अन्यथा अणु								\
	guard = 0;							\
	sticky |= (Dallp1(opndp1) | Dallp2(opndp2));			\
	Dbl_setzero(opndp1,opndp2);					\
	inexact = sticky;						\
    पूर्ण

/* 
 * The fused multiply add inकाष्ठाions requires a द्विगुन extended क्रमmat,
 * with 106 bits of mantissa.
 */
#घोषणा DBLEXT_THRESHOLD 106

#घोषणा Dblext_setzero(valA,valB,valC,valD)	\
    Dextallp1(valA) = 0; Dextallp2(valB) = 0;	\
    Dextallp3(valC) = 0; Dextallp4(valD) = 0


#घोषणा Dblext_isnotzero_mantissap3(valC) (Dextallp3(valC)!=0)
#घोषणा Dblext_isnotzero_mantissap4(valD) (Dextallp3(valD)!=0)
#घोषणा Dblext_isone_lowp2(val) (Dextlowp2(val)!=0)
#घोषणा Dblext_isone_highp3(val) (Dexthighp3(val)!=0)
#घोषणा Dblext_isnotzero_low31p3(val) (Dextlow31p3(val)!=0)
#घोषणा Dblext_iszero(valA,valB,valC,valD) (Dextallp1(valA)==0 && \
    Dextallp2(valB)==0 && Dextallp3(valC)==0 && Dextallp4(valD)==0)

#घोषणा Dblext_copy(srca,srcb,srcc,srcd,desta,destb,destc,destd) \
    Dextallp1(desta) = Dextallp4(srca);	\
    Dextallp2(destb) = Dextallp4(srcb);	\
    Dextallp3(destc) = Dextallp4(srcc);	\
    Dextallp4(destd) = Dextallp4(srcd)

#घोषणा Dblext_swap_lower(leftp2,leftp3,leftp4,rightp2,rightp3,rightp4)  \
    Dextallp2(leftp2)  = Dextallp2(leftp2) XOR Dextallp2(rightp2);  \
    Dextallp2(rightp2) = Dextallp2(leftp2) XOR Dextallp2(rightp2);  \
    Dextallp2(leftp2)  = Dextallp2(leftp2) XOR Dextallp2(rightp2);  \
    Dextallp3(leftp3)  = Dextallp3(leftp3) XOR Dextallp3(rightp3);  \
    Dextallp3(rightp3) = Dextallp3(leftp3) XOR Dextallp3(rightp3);  \
    Dextallp3(leftp3)  = Dextallp3(leftp3) XOR Dextallp3(rightp3);  \
    Dextallp4(leftp4)  = Dextallp4(leftp4) XOR Dextallp4(rightp4);  \
    Dextallp4(rightp4) = Dextallp4(leftp4) XOR Dextallp4(rightp4);  \
    Dextallp4(leftp4)  = Dextallp4(leftp4) XOR Dextallp4(rightp4)

#घोषणा Dblext_setone_lowmantissap4(dbl_value) Deposit_dextlowp4(dbl_value,1)

/* The high bit is always zero so arithmetic or logical shअगरts will work. */
#घोषणा Dblext_right_align(srcdstA,srcdstB,srcdstC,srcdstD,shअगरt) \
  अणुपूर्णांक shअगरtamt, sticky;						\
    shअगरtamt = shअगरt % 32;						\
    sticky = 0;								\
    चयन (shअगरt/32) अणु							\
     हाल 0: अगर (shअगरtamt > 0) अणु					\
	        sticky = Dextallp4(srcdstD) << 32 - (shअगरtamt); 	\
                Variable_shअगरt_द्विगुन(Dextallp3(srcdstC),		\
		 Dextallp4(srcdstD),shअगरtamt,Dextallp4(srcdstD));	\
                Variable_shअगरt_द्विगुन(Dextallp2(srcdstB),		\
		 Dextallp3(srcdstC),shअगरtamt,Dextallp3(srcdstC));	\
                Variable_shअगरt_द्विगुन(Dextallp1(srcdstA),		\
		 Dextallp2(srcdstB),shअगरtamt,Dextallp2(srcdstB));	\
	        Dextallp1(srcdstA) >>= shअगरtamt;			\
	     पूर्ण								\
	     अवरोध;							\
     हाल 1: अगर (shअगरtamt > 0) अणु					\
                sticky = (Dextallp3(srcdstC) << 31 - shअगरtamt) |	\
			 Dextallp4(srcdstD);				\
                Variable_shअगरt_द्विगुन(Dextallp2(srcdstB),		\
		 Dextallp3(srcdstC),shअगरtamt,Dextallp4(srcdstD));	\
                Variable_shअगरt_द्विगुन(Dextallp1(srcdstA),		\
		 Dextallp2(srcdstB),shअगरtamt,Dextallp3(srcdstC));	\
	     पूर्ण								\
	     अन्यथा अणु							\
		sticky = Dextallp4(srcdstD);				\
		Dextallp4(srcdstD) = Dextallp3(srcdstC);		\
		Dextallp3(srcdstC) = Dextallp2(srcdstB);		\
	     पूर्ण								\
	     Dextallp2(srcdstB) = Dextallp1(srcdstA) >> shअगरtamt;	\
	     Dextallp1(srcdstA) = 0;					\
	     अवरोध;							\
     हाल 2: अगर (shअगरtamt > 0) अणु					\
                sticky = (Dextallp2(srcdstB) << 31 - shअगरtamt) |	\
			 Dextallp3(srcdstC) | Dextallp4(srcdstD);	\
                Variable_shअगरt_द्विगुन(Dextallp1(srcdstA),		\
		 Dextallp2(srcdstB),shअगरtamt,Dextallp4(srcdstD));	\
	     पूर्ण								\
	     अन्यथा अणु							\
		sticky = Dextallp3(srcdstC) | Dextallp4(srcdstD);	\
		Dextallp4(srcdstD) = Dextallp2(srcdstB);		\
	     पूर्ण								\
	     Dextallp3(srcdstC) = Dextallp1(srcdstA) >> shअगरtamt;	\
	     Dextallp1(srcdstA) = Dextallp2(srcdstB) = 0;		\
	     अवरोध;							\
     हाल 3: अगर (shअगरtamt > 0) अणु					\
                sticky = (Dextallp1(srcdstA) << 31 - shअगरtamt) |	\
			 Dextallp2(srcdstB) | Dextallp3(srcdstC) |	\
			 Dextallp4(srcdstD);				\
	     पूर्ण								\
	     अन्यथा अणु							\
		sticky = Dextallp2(srcdstB) | Dextallp3(srcdstC) |	\
		    Dextallp4(srcdstD);					\
	     पूर्ण								\
	     Dextallp4(srcdstD) = Dextallp1(srcdstA) >> shअगरtamt;	\
	     Dextallp1(srcdstA) = Dextallp2(srcdstB) = 0;		\
	     Dextallp3(srcdstC) = 0;					\
	     अवरोध;							\
    पूर्ण									\
    अगर (sticky) Dblext_setone_lowmantissap4(srcdstD);			\
  पूर्ण

/* The left argument is never smaller than the right argument */
#घोषणा Dblext_subtract(lefta,leftb,leftc,leftd,righta,rightb,rightc,rightd,resulta,resultb,resultc,resultd) \
    अगर( Dextallp4(rightd) > Dextallp4(leftd) ) 			\
	अगर( (Dextallp3(leftc)--) == 0)				\
	    अगर( (Dextallp2(leftb)--) == 0) Dextallp1(lefta)--;	\
    Dextallp4(resultd) = Dextallp4(leftd) - Dextallp4(rightd);	\
    अगर( Dextallp3(rightc) > Dextallp3(leftc) ) 			\
        अगर( (Dextallp2(leftb)--) == 0) Dextallp1(lefta)--;	\
    Dextallp3(resultc) = Dextallp3(leftc) - Dextallp3(rightc);	\
    अगर( Dextallp2(rightb) > Dextallp2(leftb) ) Dextallp1(lefta)--; \
    Dextallp2(resultb) = Dextallp2(leftb) - Dextallp2(rightb);	\
    Dextallp1(resulta) = Dextallp1(lefta) - Dextallp1(righta)

#घोषणा Dblext_addition(lefta,leftb,leftc,leftd,righta,rightb,rightc,rightd,resulta,resultb,resultc,resultd) \
    /* If the sum of the low words is less than either source, then \
     * an overflow पूर्णांकo the next word occurred. */ \
    अगर ((Dextallp4(resultd) = Dextallp4(leftd)+Dextallp4(rightd)) < \
	Dextallp4(rightd)) \
	अगर((Dextallp3(resultc) = Dextallp3(leftc)+Dextallp3(rightc)+1) <= \
	    Dextallp3(rightc)) \
	    अगर((Dextallp2(resultb) = Dextallp2(leftb)+Dextallp2(rightb)+1) \
	        <= Dextallp2(rightb))  \
		    Dextallp1(resulta) = Dextallp1(lefta)+Dextallp1(righta)+1; \
	    अन्यथा Dextallp1(resulta) = Dextallp1(lefta)+Dextallp1(righta); \
	अन्यथा \
	    अगर ((Dextallp2(resultb) = Dextallp2(leftb)+Dextallp2(rightb)) < \
	        Dextallp2(rightb)) \
		    Dextallp1(resulta) = Dextallp1(lefta)+Dextallp1(righta)+1; \
	    अन्यथा Dextallp1(resulta) = Dextallp1(lefta)+Dextallp1(righta); \
    अन्यथा \
	अगर ((Dextallp3(resultc) = Dextallp3(leftc)+Dextallp3(rightc)) < \
	    Dextallp3(rightc))  \
	    अगर ((Dextallp2(resultb) = Dextallp2(leftb)+Dextallp2(rightb)+1) \
	        <= Dextallp2(rightb)) \
		    Dextallp1(resulta) = Dextallp1(lefta)+Dextallp1(righta)+1; \
	    अन्यथा Dextallp1(resulta) = Dextallp1(lefta)+Dextallp1(righta); \
	अन्यथा \
	    अगर ((Dextallp2(resultb) = Dextallp2(leftb)+Dextallp2(rightb)) < \
	        Dextallp2(rightb)) \
		    Dextallp1(resulta) = Dextallp1(lefta)+Dextallp1(righta)+1; \
	    अन्यथा Dextallp1(resulta) = Dextallp1(lefta)+Dextallp1(righta)


#घोषणा Dblext_arithrightshअगरtby1(srcdstA,srcdstB,srcdstC,srcdstD)	\
    Shअगरtद्विगुन(Dextallp3(srcdstC),Dextallp4(srcdstD),1,Dextallp4(srcdstD)); \
    Shअगरtद्विगुन(Dextallp2(srcdstB),Dextallp3(srcdstC),1,Dextallp3(srcdstC)); \
    Shअगरtद्विगुन(Dextallp1(srcdstA),Dextallp2(srcdstB),1,Dextallp2(srcdstB)); \
    Dextallp1(srcdstA) = (पूर्णांक)Dextallp1(srcdstA) >> 1
   
#घोषणा Dblext_leftshअगरtby8(valA,valB,valC,valD) \
    Shअगरtद्विगुन(Dextallp1(valA),Dextallp2(valB),24,Dextallp1(valA)); \
    Shअगरtद्विगुन(Dextallp2(valB),Dextallp3(valC),24,Dextallp2(valB)); \
    Shअगरtद्विगुन(Dextallp3(valC),Dextallp4(valD),24,Dextallp3(valC)); \
    Dextallp4(valD) <<= 8
#घोषणा Dblext_leftshअगरtby4(valA,valB,valC,valD) \
    Shअगरtद्विगुन(Dextallp1(valA),Dextallp2(valB),28,Dextallp1(valA)); \
    Shअगरtद्विगुन(Dextallp2(valB),Dextallp3(valC),28,Dextallp2(valB)); \
    Shअगरtद्विगुन(Dextallp3(valC),Dextallp4(valD),28,Dextallp3(valC)); \
    Dextallp4(valD) <<= 4
#घोषणा Dblext_leftshअगरtby3(valA,valB,valC,valD) \
    Shअगरtद्विगुन(Dextallp1(valA),Dextallp2(valB),29,Dextallp1(valA)); \
    Shअगरtद्विगुन(Dextallp2(valB),Dextallp3(valC),29,Dextallp2(valB)); \
    Shअगरtद्विगुन(Dextallp3(valC),Dextallp4(valD),29,Dextallp3(valC)); \
    Dextallp4(valD) <<= 3
#घोषणा Dblext_leftshअगरtby2(valA,valB,valC,valD) \
    Shअगरtद्विगुन(Dextallp1(valA),Dextallp2(valB),30,Dextallp1(valA)); \
    Shअगरtद्विगुन(Dextallp2(valB),Dextallp3(valC),30,Dextallp2(valB)); \
    Shअगरtद्विगुन(Dextallp3(valC),Dextallp4(valD),30,Dextallp3(valC)); \
    Dextallp4(valD) <<= 2
#घोषणा Dblext_leftshअगरtby1(valA,valB,valC,valD) \
    Shअगरtद्विगुन(Dextallp1(valA),Dextallp2(valB),31,Dextallp1(valA)); \
    Shअगरtद्विगुन(Dextallp2(valB),Dextallp3(valC),31,Dextallp2(valB)); \
    Shअगरtद्विगुन(Dextallp3(valC),Dextallp4(valD),31,Dextallp3(valC)); \
    Dextallp4(valD) <<= 1

#घोषणा Dblext_rightshअगरtby4(valueA,valueB,valueC,valueD) \
    Shअगरtद्विगुन(Dextallp3(valueC),Dextallp4(valueD),4,Dextallp4(valueD)); \
    Shअगरtद्विगुन(Dextallp2(valueB),Dextallp3(valueC),4,Dextallp3(valueC)); \
    Shअगरtद्विगुन(Dextallp1(valueA),Dextallp2(valueB),4,Dextallp2(valueB)); \
    Dextallp1(valueA) >>= 4
#घोषणा Dblext_rightshअगरtby1(valueA,valueB,valueC,valueD) \
    Shअगरtद्विगुन(Dextallp3(valueC),Dextallp4(valueD),1,Dextallp4(valueD)); \
    Shअगरtद्विगुन(Dextallp2(valueB),Dextallp3(valueC),1,Dextallp3(valueC)); \
    Shअगरtद्विगुन(Dextallp1(valueA),Dextallp2(valueB),1,Dextallp2(valueB)); \
    Dextallp1(valueA) >>= 1

#घोषणा Dblext_xortoपूर्णांकp1(left,right,result) Dbl_xortoपूर्णांकp1(left,right,result)

#घोषणा Dblext_xorfromपूर्णांकp1(left,right,result) \
	Dbl_xorfromपूर्णांकp1(left,right,result)

#घोषणा Dblext_copytoपूर्णांक_exponenपंचांगantissap1(src,dest) \
	Dbl_copytoपूर्णांक_exponenपंचांगantissap1(src,dest)

#घोषणा Dblext_ismagnitudeless(leftB,rightB,signlessleft,signlessright) \
	Dbl_ismagnitudeless(leftB,rightB,signlessleft,signlessright)

#घोषणा Dbl_copyto_dblext(src1,src2,dest1,dest2,dest3,dest4) \
	Dextallp1(dest1) = Dallp1(src1); Dextallp2(dest2) = Dallp2(src2); \
	Dextallp3(dest3) = 0; Dextallp4(dest4) = 0

#घोषणा Dblext_set_sign(dbl_value,sign)  Dbl_set_sign(dbl_value,sign)  
#घोषणा Dblext_clear_signexponent_set_hidden(srcdst) \
	Dbl_clear_signexponent_set_hidden(srcdst) 
#घोषणा Dblext_clear_signexponent(srcdst) Dbl_clear_signexponent(srcdst) 
#घोषणा Dblext_clear_sign(srcdst) Dbl_clear_sign(srcdst) 
#घोषणा Dblext_isone_hidden(dbl_value) Dbl_isone_hidden(dbl_value) 

/*
 * The Fourword_add() macro assumes that पूर्णांकegers are 4 bytes in size.
 * It will अवरोध अगर this is not the हाल.
 */

#घोषणा Fourword_add(src1dstA,src1dstB,src1dstC,src1dstD,src2A,src2B,src2C,src2D) \
	/* 								\
	 * want this macro to generate:					\
	 *	ADD	src1dstD,src2D,src1dstD;			\
	 *	ADDC	src1dstC,src2C,src1dstC;			\
	 *	ADDC	src1dstB,src2B,src1dstB;			\
	 *	ADDC	src1dstA,src2A,src1dstA;			\
	 */								\
	अगर ((अचिन्हित पूर्णांक)(src1dstD += (src2D)) < (अचिन्हित पूर्णांक)(src2D)) अणु \
	   अगर ((अचिन्हित पूर्णांक)(src1dstC += (src2C) + 1) <=		\
	       (अचिन्हित पूर्णांक)(src2C)) अणु					\
	     अगर ((अचिन्हित पूर्णांक)(src1dstB += (src2B) + 1) <=		\
		 (अचिन्हित पूर्णांक)(src2B)) src1dstA++;			\
	   पूर्ण								\
	   अन्यथा अगर ((अचिन्हित पूर्णांक)(src1dstB += (src2B)) < 		\
		    (अचिन्हित पूर्णांक)(src2B)) src1dstA++;			\
	पूर्ण								\
	अन्यथा अणु								\
	   अगर ((अचिन्हित पूर्णांक)(src1dstC += (src2C)) <			\
	       (अचिन्हित पूर्णांक)(src2C)) अणु					\
	      अगर ((अचिन्हित पूर्णांक)(src1dstB += (src2B) + 1) <=		\
		  (अचिन्हित पूर्णांक)(src2B)) src1dstA++;			\
	   पूर्ण								\
	   अन्यथा अगर ((अचिन्हित पूर्णांक)(src1dstB += (src2B)) <		\
		    (अचिन्हित पूर्णांक)(src2B)) src1dstA++;			\
	पूर्ण								\
	src1dstA += (src2A)

#घोषणा Dblext_denormalize(opndp1,opndp2,opndp3,opndp4,exponent,is_tiny) \
  अणुपूर्णांक shअगरtamt, sticky;						\
    is_tiny = TRUE;							\
    अगर (exponent == 0 && (Dextallp3(opndp3) || Dextallp4(opndp4))) अणु	\
	चयन (Rounding_mode()) अणु					\
	हाल ROUNDPLUS:							\
		अगर (Dbl_iszero_sign(opndp1)) अणु				\
			Dbl_increment(opndp1,opndp2);			\
			अगर (Dbl_isone_hiddenoverflow(opndp1))		\
				is_tiny = FALSE;			\
			Dbl_decrement(opndp1,opndp2);			\
		पूर्ण							\
		अवरोध;							\
	हाल ROUNDMINUS:						\
		अगर (Dbl_isone_sign(opndp1)) अणु				\
			Dbl_increment(opndp1,opndp2);			\
			अगर (Dbl_isone_hiddenoverflow(opndp1))		\
				is_tiny = FALSE;			\
			Dbl_decrement(opndp1,opndp2);			\
		पूर्ण							\
		अवरोध;							\
	हाल ROUNDNEAREST:						\
		अगर (Dblext_isone_highp3(opndp3) &&			\
		    (Dblext_isone_lowp2(opndp2) || 			\
		     Dblext_isnotzero_low31p3(opndp3)))	अणु		\
			Dbl_increment(opndp1,opndp2);			\
			अगर (Dbl_isone_hiddenoverflow(opndp1))		\
				is_tiny = FALSE;			\
			Dbl_decrement(opndp1,opndp2);			\
		पूर्ण							\
		अवरोध;							\
	पूर्ण								\
    पूर्ण									\
    Dblext_clear_signexponent_set_hidden(opndp1);			\
    अगर (exponent >= (1-QUAD_P)) अणु					\
	shअगरtamt = (1-exponent) % 32;					\
	चयन((1-exponent)/32) अणु					\
	  हाल 0: sticky = Dextallp4(opndp4) << 32-(shअगरtamt);		\
		  Variableshअगरtद्विगुन(opndp3,opndp4,shअगरtamt,opndp4);	\
		  Variableshअगरtद्विगुन(opndp2,opndp3,shअगरtamt,opndp3);	\
		  Variableshअगरtद्विगुन(opndp1,opndp2,shअगरtamt,opndp2);	\
		  Dextallp1(opndp1) >>= shअगरtamt;			\
		  अवरोध;						\
	  हाल 1: sticky = (Dextallp3(opndp3) << 32-(shअगरtamt)) | 	\
			   Dextallp4(opndp4);				\
		  Variableshअगरtद्विगुन(opndp2,opndp3,shअगरtamt,opndp4);	\
		  Variableshअगरtद्विगुन(opndp1,opndp2,shअगरtamt,opndp3);	\
		  Dextallp2(opndp2) = Dextallp1(opndp1) >> shअगरtamt;	\
		  Dextallp1(opndp1) = 0;				\
		  अवरोध;						\
	  हाल 2: sticky = (Dextallp2(opndp2) << 32-(shअगरtamt)) |	\
			    Dextallp3(opndp3) | Dextallp4(opndp4);	\
		  Variableshअगरtद्विगुन(opndp1,opndp2,shअगरtamt,opndp4);	\
		  Dextallp3(opndp3) = Dextallp1(opndp1) >> shअगरtamt;	\
		  Dextallp1(opndp1) = Dextallp2(opndp2) = 0;		\
		  अवरोध;						\
	  हाल 3: sticky = (Dextallp1(opndp1) << 32-(shअगरtamt)) |	\
		  	Dextallp2(opndp2) | Dextallp3(opndp3) | 	\
			Dextallp4(opndp4);				\
		  Dextallp4(opndp4) = Dextallp1(opndp1) >> shअगरtamt;	\
		  Dextallp1(opndp1) = Dextallp2(opndp2) = 0;		\
		  Dextallp3(opndp3) = 0;				\
		  अवरोध;						\
	पूर्ण								\
    पूर्ण									\
    अन्यथा अणु								\
	sticky = Dextallp1(opndp1) | Dextallp2(opndp2) |		\
		 Dextallp3(opndp3) | Dextallp4(opndp4);			\
	Dblext_setzero(opndp1,opndp2,opndp3,opndp4);			\
    पूर्ण									\
    अगर (sticky) Dblext_setone_lowmantissap4(opndp4);			\
    exponent = 0;							\
  पूर्ण
