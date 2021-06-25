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
#घोषणा Sgl_firstword(value) Sall(value)
#घोषणा Sgl_secondword(value) dummy_location
#घोषणा Sgl_thirdword(value) dummy_location
#घोषणा Sgl_fourthword(value) dummy_location

#घोषणा Sgl_sign(object) Ssign(object)
#घोषणा Sgl_exponent(object) Sexponent(object)
#घोषणा Sgl_signexponent(object) Ssignexponent(object)
#घोषणा Sgl_mantissa(object) Smantissa(object)
#घोषणा Sgl_exponenपंचांगantissa(object) Sexponenपंचांगantissa(object)
#घोषणा Sgl_all(object) Sall(object)

/* sgl_and_signs ANDs the sign bits of each argument and माला_दो the result
 * पूर्णांकo the first argument. sgl_or_signs ors those same sign bits */
#घोषणा Sgl_and_signs( src1dst, src2)		\
    Sall(src1dst) = (Sall(src2)|~((अचिन्हित पूर्णांक)1<<31)) & Sall(src1dst)
#घोषणा Sgl_or_signs( src1dst, src2)		\
    Sall(src1dst) = (Sall(src2)&((अचिन्हित पूर्णांक)1<<31)) | Sall(src1dst)

/* The hidden bit is always the low bit of the exponent */
#घोषणा Sgl_clear_exponent_set_hidden(srcdst) Deposit_sexponent(srcdst,1)
#घोषणा Sgl_clear_signexponent_set_hidden(srcdst) \
    Deposit_ssignexponent(srcdst,1)
#घोषणा Sgl_clear_sign(srcdst) Sall(srcdst) &= ~((अचिन्हित पूर्णांक)1<<31)
#घोषणा Sgl_clear_signexponent(srcdst) Sall(srcdst) &= 0x007fffff

/* varamount must be less than 32 क्रम the next three functions */
#घोषणा Sgl_rightshअगरt(srcdst, varamount)	\
    Sall(srcdst) >>= varamount
#घोषणा Sgl_leftshअगरt(srcdst, varamount)	\
    Sall(srcdst) <<= varamount
#घोषणा Sgl_rightshअगरt_exponenपंचांगantissa(srcdst, varamount) \
    Sall(srcdst) = \
	(Sexponenपंचांगantissa(srcdst) >> varamount) | \
	(Sall(srcdst) & ((अचिन्हित पूर्णांक)1<<31))

#घोषणा Sgl_leftshअगरtby1_withextent(left,right,result) \
    Shअगरtद्विगुन(Sall(left),Extall(right),31,Sall(result))
    
#घोषणा Sgl_rightshअगरtby1_withextent(left,right,dst)		\
    Shअगरtद्विगुन(Sall(left),Extall(right),1,Extall(right))
#घोषणा Sgl_arithrightshअगरtby1(srcdst)	\
    Sall(srcdst) = (पूर्णांक)Sall(srcdst) >> 1
    
/* Sign extend the sign bit with an पूर्णांकeger destination */
#घोषणा Sgl_signextendedsign(value) Sचिन्हितsign(value)

#घोषणा Sgl_isone_hidden(sgl_value) (Shidden(sgl_value))
#घोषणा Sgl_increment(sgl_value) Sall(sgl_value) += 1
#घोषणा Sgl_increment_mantissa(sgl_value) \
    Deposit_smantissa(sgl_value,sgl_value+1)
#घोषणा Sgl_decrement(sgl_value) Sall(sgl_value) -= 1

#घोषणा Sgl_isone_sign(sgl_value) (Is_ssign(sgl_value)!=0)
#घोषणा Sgl_isone_hiddenoverflow(sgl_value) \
    (Is_shiddenoverflow(sgl_value)!=0)
#घोषणा Sgl_isone_lowmantissa(sgl_value) (Is_slow(sgl_value)!=0)
#घोषणा Sgl_isone_संकेतing(sgl_value) (Is_sसंकेतing(sgl_value)!=0)
#घोषणा Sgl_is_संकेतingnan(sgl_value) (Sसंकेतingnan(sgl_value)==0x1ff)
#घोषणा Sgl_isnotzero(sgl_value) (Sall(sgl_value)!=0)
#घोषणा Sgl_isnotzero_hiddenhigh7mantissa(sgl_value) \
    (Shiddenhigh7mantissa(sgl_value)!=0)
#घोषणा Sgl_isnotzero_low4(sgl_value) (Slow4(sgl_value)!=0)
#घोषणा Sgl_isnotzero_exponent(sgl_value) (Sexponent(sgl_value)!=0)
#घोषणा Sgl_isnotzero_mantissa(sgl_value) (Smantissa(sgl_value)!=0)
#घोषणा Sgl_isnotzero_exponenपंचांगantissa(sgl_value) \
    (Sexponenपंचांगantissa(sgl_value)!=0)
#घोषणा Sgl_iszero(sgl_value) (Sall(sgl_value)==0)
#घोषणा Sgl_iszero_संकेतing(sgl_value) (Is_sसंकेतing(sgl_value)==0)
#घोषणा Sgl_iszero_hidden(sgl_value) (Is_shidden(sgl_value)==0)
#घोषणा Sgl_iszero_hiddenoverflow(sgl_value) \
    (Is_shiddenoverflow(sgl_value)==0)
#घोषणा Sgl_iszero_hiddenhigh3mantissa(sgl_value) \
    (Shiddenhigh3mantissa(sgl_value)==0)
#घोषणा Sgl_iszero_hiddenhigh7mantissa(sgl_value) \
    (Shiddenhigh7mantissa(sgl_value)==0)
#घोषणा Sgl_iszero_sign(sgl_value) (Is_ssign(sgl_value)==0)
#घोषणा Sgl_iszero_exponent(sgl_value) (Sexponent(sgl_value)==0)
#घोषणा Sgl_iszero_mantissa(sgl_value) (Smantissa(sgl_value)==0)
#घोषणा Sgl_iszero_exponenपंचांगantissa(sgl_value) \
    (Sexponenपंचांगantissa(sgl_value)==0)
#घोषणा Sgl_isinfinity_exponent(sgl_value) 		\
    (Sgl_exponent(sgl_value)==SGL_अनन्त_EXPONENT)
#घोषणा Sgl_isnotinfinity_exponent(sgl_value) 		\
    (Sgl_exponent(sgl_value)!=SGL_अनन्त_EXPONENT)
#घोषणा Sgl_isinfinity(sgl_value)			\
    (Sgl_exponent(sgl_value)==SGL_अनन्त_EXPONENT &&	\
    Sgl_mantissa(sgl_value)==0)
#घोषणा Sgl_isnan(sgl_value)				\
    (Sgl_exponent(sgl_value)==SGL_अनन्त_EXPONENT &&	\
    Sgl_mantissa(sgl_value)!=0)
#घोषणा Sgl_isnotnan(sgl_value)				\
    (Sgl_exponent(sgl_value)!=SGL_अनन्त_EXPONENT ||	\
    Sgl_mantissa(sgl_value)==0)
#घोषणा Sgl_islessthan(sgl_op1,sgl_op2)			\
    (Sall(sgl_op1) < Sall(sgl_op2))
#घोषणा Sgl_isgreaterthan(sgl_op1,sgl_op2)		\
    (Sall(sgl_op1) > Sall(sgl_op2))
#घोषणा Sgl_isnotlessthan(sgl_op1,sgl_op2)		\
    (Sall(sgl_op1) >= Sall(sgl_op2))
#घोषणा Sgl_isequal(sgl_op1,sgl_op2)			\
    (Sall(sgl_op1) == Sall(sgl_op2))

#घोषणा Sgl_leftshअगरtby8(sgl_value) \
    Sall(sgl_value) <<= 8
#घोषणा Sgl_leftshअगरtby4(sgl_value) \
    Sall(sgl_value) <<= 4
#घोषणा Sgl_leftshअगरtby3(sgl_value) \
    Sall(sgl_value) <<= 3
#घोषणा Sgl_leftshअगरtby2(sgl_value) \
    Sall(sgl_value) <<= 2
#घोषणा Sgl_leftshअगरtby1(sgl_value) \
    Sall(sgl_value) <<= 1
#घोषणा Sgl_rightshअगरtby1(sgl_value) \
    Sall(sgl_value) >>= 1
#घोषणा Sgl_rightshअगरtby4(sgl_value) \
    Sall(sgl_value) >>= 4
#घोषणा Sgl_rightshअगरtby8(sgl_value) \
    Sall(sgl_value) >>= 8
    
#घोषणा Sgl_ismagnitudeless(signlessleft,signlessright)			\
/*  अचिन्हित पूर्णांक signlessleft, signlessright; */			\
      (signlessleft < signlessright)  
    

#घोषणा Sgl_copytoपूर्णांक_exponenपंचांगantissa(source,dest)     \
    dest = Sexponenपंचांगantissa(source)

/* A quiet NaN has the high mantissa bit clear and at least on other (in this
 * हाल the adjacent bit) bit set. */
#घोषणा Sgl_set_quiet(sgl_value) Deposit_shigh2mantissa(sgl_value,1)
#घोषणा Sgl_set_exponent(sgl_value,exp) Deposit_sexponent(sgl_value,exp)

#घोषणा Sgl_set_mantissa(dest,value) Deposit_smantissa(dest,value)
#घोषणा Sgl_set_exponenपंचांगantissa(dest,value) \
    Deposit_sexponenपंचांगantissa(dest,value)

/*  An infinity is represented with the max exponent and a zero mantissa */
#घोषणा Sgl_setinfinity_exponent(sgl_value) \
    Deposit_sexponent(sgl_value,SGL_अनन्त_EXPONENT)
#घोषणा Sgl_setinfinity_exponenपंचांगantissa(sgl_value)	\
    Deposit_sexponenपंचांगantissa(sgl_value, \
	(SGL_अनन्त_EXPONENT << (32-(1+SGL_EXP_LENGTH))))
#घोषणा Sgl_setinfinitypositive(sgl_value)		\
    Sall(sgl_value) = (SGL_अनन्त_EXPONENT << (32-(1+SGL_EXP_LENGTH)))
#घोषणा Sgl_setinfinitynegative(sgl_value)		\
    Sall(sgl_value) = (SGL_अनन्त_EXPONENT << (32-(1+SGL_EXP_LENGTH))) \
    | ((अचिन्हित पूर्णांक)1<<31)
#घोषणा Sgl_setinfinity(sgl_value,sign)					\
    Sall(sgl_value) = (SGL_अनन्त_EXPONENT << (32-(1+SGL_EXP_LENGTH))) | \
     ((अचिन्हित पूर्णांक)sign << 31)
#घोषणा Sgl_sethigh4bits(sgl_value, extsign)  \
    Deposit_shigh4(sgl_value,extsign)
#घोषणा Sgl_set_sign(sgl_value,sign) Deposit_ssign(sgl_value,sign)
#घोषणा Sgl_invert_sign(sgl_value)  \
    Deposit_ssign(sgl_value,~Ssign(sgl_value))
#घोषणा Sgl_setone_sign(sgl_value) Deposit_ssign(sgl_value,1)
#घोषणा Sgl_setone_lowmantissa(sgl_value) Deposit_slow(sgl_value,1)
#घोषणा Sgl_setzero_sign(sgl_value)  Sall(sgl_value) &= 0x7fffffff
#घोषणा Sgl_setzero_exponent(sgl_value) Sall(sgl_value) &= 0x807fffff
#घोषणा Sgl_setzero_mantissa(sgl_value) Sall(sgl_value) &= 0xff800000
#घोषणा Sgl_setzero_exponenपंचांगantissa(sgl_value)  Sall(sgl_value) &= 0x80000000
#घोषणा Sgl_setzero(sgl_value) Sall(sgl_value) = 0
#घोषणा Sgl_setnegativezero(sgl_value) Sall(sgl_value) = (अचिन्हित पूर्णांक)1 << 31

/* Use following macro क्रम both overflow & underflow conditions */
#घोषणा ovfl -
#घोषणा unfl +
#घोषणा Sgl_setwrapped_exponent(sgl_value,exponent,op) \
    Deposit_sexponent(sgl_value,(exponent op SGL_WRAP))

#घोषणा Sgl_setlargestpositive(sgl_value) 				\
    Sall(sgl_value) = ((SGL_EMAX+SGL_BIAS) << (32-(1+SGL_EXP_LENGTH)))	\
                      | ((1<<(32-(1+SGL_EXP_LENGTH))) - 1 )
#घोषणा Sgl_setlargestnegative(sgl_value)				\
    Sall(sgl_value) = ((SGL_EMAX+SGL_BIAS) << (32-(1+SGL_EXP_LENGTH)))	\
                      | ((1<<(32-(1+SGL_EXP_LENGTH))) - 1 )		\
		      | ((अचिन्हित पूर्णांक)1<<31)

#घोषणा Sgl_setnegativeinfinity(sgl_value)	\
    Sall(sgl_value) = 				\
    ((1<<SGL_EXP_LENGTH) | SGL_अनन्त_EXPONENT) << (32-(1+SGL_EXP_LENGTH))
#घोषणा Sgl_setlargest(sgl_value,sign) 					\
    Sall(sgl_value) = (अचिन्हित पूर्णांक)sign << 31 |			\
        (((SGL_EMAX+SGL_BIAS) << (32-(1+SGL_EXP_LENGTH)))		\
	  | ((1 << (32-(1+SGL_EXP_LENGTH))) - 1 ))
#घोषणा Sgl_setlargest_exponenपंचांगantissa(sgl_value)			\
    Sall(sgl_value) = Sall(sgl_value) & ((अचिन्हित पूर्णांक)1<<31) |		\
        (((SGL_EMAX+SGL_BIAS) << (32-(1+SGL_EXP_LENGTH)))		\
	  | ((1 << (32-(1+SGL_EXP_LENGTH))) - 1 ))

/* The high bit is always zero so arithmetic or logical shअगरts will work. */
#घोषणा Sgl_right_align(srcdst,shअगरt,extent)				\
    /* sgl_भग्नing_poपूर्णांक srcdst; पूर्णांक shअगरt; extension extent */	\
    अगर (shअगरt < 32) अणु							\
	Extall(extent) = Sall(srcdst) << (32-(shअगरt));			\
    	Sall(srcdst) >>= shअगरt;						\
    पूर्ण									\
    अन्यथा अणु								\
	Extall(extent) = Sall(srcdst);					\
	Sall(srcdst) = 0;						\
    पूर्ण
#घोषणा Sgl_hiddenhigh3mantissa(sgl_value) Shiddenhigh3mantissa(sgl_value)
#घोषणा Sgl_hidden(sgl_value) Shidden(sgl_value)
#घोषणा Sgl_lowmantissa(sgl_value) Slow(sgl_value)

/* The left argument is never smaller than the right argument */
#घोषणा Sgl_subtract(sgl_left,sgl_right,sgl_result) \
    Sall(sgl_result) = Sall(sgl_left) - Sall(sgl_right)

/* Subtract right augmented with extension from left augmented with zeros and
 * store पूर्णांकo result and extension. */
#घोषणा Sgl_subtract_withextension(left,right,extent,result)		\
    /* sgl_भग्नing_poपूर्णांक left,right,result; extension extent */	\
  Sgl_subtract(left,right,result);					\
  अगर((Extall(extent) = 0-Extall(extent)))				\
      Sall(result) = Sall(result)-1

#घोषणा Sgl_addition(sgl_left,sgl_right,sgl_result) \
    Sall(sgl_result) = Sall(sgl_left) + Sall(sgl_right)

#घोषणा Sgl_xortoपूर्णांकp1(left,right,result)			\
    result = Sall(left) XOR Sall(right);

#घोषणा Sgl_xorfromपूर्णांकp1(left,right,result)			\
    Sall(result) = left XOR Sall(right)

/* Need to Initialize */
#घोषणा Sgl_makequietnan(dest)						\
    Sall(dest) = ((SGL_EMAX+SGL_BIAS)+1)<< (32-(1+SGL_EXP_LENGTH))	\
                 | (1<<(32-(1+SGL_EXP_LENGTH+2)))
#घोषणा Sgl_makeसंकेतingnan(dest)					\
    Sall(dest) = ((SGL_EMAX+SGL_BIAS)+1)<< (32-(1+SGL_EXP_LENGTH))	\
                 | (1<<(32-(1+SGL_EXP_LENGTH+1)))

#घोषणा Sgl_normalize(sgl_opnd,exponent)			\
	जबतक(Sgl_iszero_hiddenhigh7mantissa(sgl_opnd)) अणु	\
		Sgl_leftshअगरtby8(sgl_opnd);			\
		exponent -= 8;					\
	पूर्ण							\
	अगर(Sgl_iszero_hiddenhigh3mantissa(sgl_opnd)) अणु		\
		Sgl_leftshअगरtby4(sgl_opnd);			\
		exponent -= 4;					\
	पूर्ण							\
	जबतक(Sgl_iszero_hidden(sgl_opnd)) अणु			\
		Sgl_leftshअगरtby1(sgl_opnd);			\
		exponent -= 1;					\
	पूर्ण

#घोषणा Sgl_setoverflow(sgl_opnd)				\
	/* set result to infinity or largest number */		\
	चयन (Rounding_mode()) अणु				\
		हाल ROUNDPLUS:					\
			अगर (Sgl_isone_sign(sgl_opnd)) अणु		\
				Sgl_setlargestnegative(sgl_opnd); \
			पूर्ण					\
			अन्यथा अणु					\
				Sgl_setinfinitypositive(sgl_opnd); \
			पूर्ण					\
			अवरोध;					\
		हाल ROUNDMINUS:				\
			अगर (Sgl_iszero_sign(sgl_opnd)) अणु	\
				Sgl_setlargestpositive(sgl_opnd); \
			पूर्ण					\
			अन्यथा अणु					\
				Sgl_setinfinitynegative(sgl_opnd); \
			पूर्ण					\
			अवरोध;					\
		हाल ROUNDNEAREST:				\
			Sgl_setinfinity_exponenपंचांगantissa(sgl_opnd); \
			अवरोध;					\
		हाल ROUNDZERO:					\
			Sgl_setlargest_exponenपंचांगantissa(sgl_opnd); \
	पूर्ण

#घोषणा Sgl_denormalize(opnd,exponent,guard,sticky,inexact)		\
	Sgl_clear_signexponent_set_hidden(opnd);			\
	अगर (exponent >= (1 - SGL_P)) अणु					\
		guard = (Sall(opnd) >> -exponent) & 1;			\
		अगर (exponent < 0) sticky |= Sall(opnd) << (32+exponent); \
		inexact = guard | sticky;				\
		Sall(opnd) >>= (1-exponent);				\
	पूर्ण								\
	अन्यथा अणु								\
		guard = 0;						\
		sticky |= Sall(opnd);					\
		inexact = sticky;					\
		Sgl_setzero(opnd);					\
	पूर्ण

/* 
 * The fused multiply add inकाष्ठाions requires a single extended क्रमmat,
 * with 48 bits of mantissa.
 */
#घोषणा SGLEXT_THRESHOLD 48

#घोषणा Sglext_setzero(valA,valB)	\
    Sextallp1(valA) = 0; Sextallp2(valB) = 0

#घोषणा Sglext_isnotzero_mantissap2(valB) (Sextallp2(valB)!=0)
#घोषणा Sglext_isone_lowp1(val) (Sextlowp1(val)!=0)
#घोषणा Sglext_isone_highp2(val) (Sexthighp2(val)!=0)
#घोषणा Sglext_isnotzero_low31p2(val) (Sextlow31p2(val)!=0)
#घोषणा Sglext_iszero(valA,valB) (Sextallp1(valA)==0 && Sextallp2(valB)==0)

#घोषणा Sgl_copytoptr(src,destptr) *destptr = src
#घोषणा Sgl_copyfromptr(srcptr,dest) dest = *srcptr
#घोषणा Sglext_copy(srca,srcb,desta,destb) \
    Sextallp1(desta) = Sextallp1(srca);	\
    Sextallp2(destb) = Sextallp2(srcb)
#घोषणा Sgl_copyto_sglext(src1,dest1,dest2) \
	Sextallp1(dest1) = Sall(src1); Sextallp2(dest2) = 0

#घोषणा Sglext_swap_lower(leftp2,rightp2)  \
    Sextallp2(leftp2)  = Sextallp2(leftp2) XOR Sextallp2(rightp2);  \
    Sextallp2(rightp2) = Sextallp2(leftp2) XOR Sextallp2(rightp2);  \
    Sextallp2(leftp2)  = Sextallp2(leftp2) XOR Sextallp2(rightp2)

#घोषणा Sglext_setone_lowmantissap2(value) Deposit_dlowp2(value,1)

/* The high bit is always zero so arithmetic or logical shअगरts will work. */
#घोषणा Sglext_right_align(srcdstA,srcdstB,shअगरt) \
  अणुपूर्णांक shअगरtamt, sticky;						\
    shअगरtamt = shअगरt % 32;						\
    sticky = 0;								\
    चयन (shअगरt/32) अणु							\
     हाल 0: अगर (shअगरtamt > 0) अणु					\
	        sticky = Sextallp2(srcdstB) << 32 - (shअगरtamt);		\
                Variable_shअगरt_द्विगुन(Sextallp1(srcdstA),		\
		 Sextallp2(srcdstB),shअगरtamt,Sextallp2(srcdstB));	\
	        Sextallp1(srcdstA) >>= shअगरtamt;			\
	     पूर्ण								\
	     अवरोध;							\
     हाल 1: अगर (shअगरtamt > 0) अणु					\
	        sticky = (Sextallp1(srcdstA) << 32 - (shअगरtamt)) |	\
			 Sextallp2(srcdstB);				\
	     पूर्ण								\
	     अन्यथा अणु							\
		sticky = Sextallp2(srcdstB);				\
	     पूर्ण								\
	     Sextallp2(srcdstB) = Sextallp1(srcdstA) >> shअगरtamt;	\
	     Sextallp1(srcdstA) = 0;					\
	     अवरोध;							\
    पूर्ण									\
    अगर (sticky) Sglext_setone_lowmantissap2(srcdstB);			\
  पूर्ण

/* The left argument is never smaller than the right argument */
#घोषणा Sglext_subtract(lefta,leftb,righta,rightb,resulta,resultb) \
    अगर( Sextallp2(rightb) > Sextallp2(leftb) ) Sextallp1(lefta)--; \
    Sextallp2(resultb) = Sextallp2(leftb) - Sextallp2(rightb);	\
    Sextallp1(resulta) = Sextallp1(lefta) - Sextallp1(righta)

#घोषणा Sglext_addition(lefta,leftb,righta,rightb,resulta,resultb) \
    /* If the sum of the low words is less than either source, then \
     * an overflow पूर्णांकo the next word occurred. */ \
    अगर ((Sextallp2(resultb) = Sextallp2(leftb)+Sextallp2(rightb)) < \
        Sextallp2(rightb)) \
	    Sextallp1(resulta) = Sextallp1(lefta)+Sextallp1(righta)+1; \
    अन्यथा Sextallp1(resulta) = Sextallp1(lefta)+Sextallp1(righta)


#घोषणा Sglext_arithrightshअगरtby1(srcdstA,srcdstB)	\
    Shअगरtद्विगुन(Sextallp1(srcdstA),Sextallp2(srcdstB),1,Sextallp2(srcdstB)); \
    Sextallp1(srcdstA) = (पूर्णांक)Sextallp1(srcdstA) >> 1
   
#घोषणा Sglext_leftshअगरtby8(valA,valB) \
    Shअगरtद्विगुन(Sextallp1(valA),Sextallp2(valB),24,Sextallp1(valA)); \
    Sextallp2(valB) <<= 8
#घोषणा Sglext_leftshअगरtby4(valA,valB) \
    Shअगरtद्विगुन(Sextallp1(valA),Sextallp2(valB),28,Sextallp1(valA)); \
    Sextallp2(valB) <<= 4
#घोषणा Sglext_leftshअगरtby3(valA,valB) \
    Shअगरtद्विगुन(Sextallp1(valA),Sextallp2(valB),29,Sextallp1(valA)); \
    Sextallp2(valB) <<= 3
#घोषणा Sglext_leftshअगरtby2(valA,valB) \
    Shअगरtद्विगुन(Sextallp1(valA),Sextallp2(valB),30,Sextallp1(valA)); \
    Sextallp2(valB) <<= 2
#घोषणा Sglext_leftshअगरtby1(valA,valB) \
    Shअगरtद्विगुन(Sextallp1(valA),Sextallp2(valB),31,Sextallp1(valA)); \
    Sextallp2(valB) <<= 1

#घोषणा Sglext_rightshअगरtby4(valueA,valueB) \
    Shअगरtद्विगुन(Sextallp1(valueA),Sextallp2(valueB),4,Sextallp2(valueB)); \
    Sextallp1(valueA) >>= 4
#घोषणा Sglext_rightshअगरtby3(valueA,valueB) \
    Shअगरtद्विगुन(Sextallp1(valueA),Sextallp2(valueB),3,Sextallp2(valueB)); \
    Sextallp1(valueA) >>= 3
#घोषणा Sglext_rightshअगरtby1(valueA,valueB) \
    Shअगरtद्विगुन(Sextallp1(valueA),Sextallp2(valueB),1,Sextallp2(valueB)); \
    Sextallp1(valueA) >>= 1

#घोषणा Sglext_xortoपूर्णांकp1(left,right,result) Sgl_xortoपूर्णांकp1(left,right,result)
#घोषणा Sglext_xorfromपूर्णांकp1(left,right,result) \
	Sgl_xorfromपूर्णांकp1(left,right,result)
#घोषणा Sglext_copytoपूर्णांक_exponenपंचांगantissa(src,dest) \
	Sgl_copytoपूर्णांक_exponenपंचांगantissa(src,dest)
#घोषणा Sglext_ismagnitudeless(signlessleft,signlessright) \
	Sgl_ismagnitudeless(signlessleft,signlessright)

#घोषणा Sglext_set_sign(dbl_value,sign)  Sgl_set_sign(dbl_value,sign)  
#घोषणा Sglext_clear_signexponent_set_hidden(srcdst) \
	Sgl_clear_signexponent_set_hidden(srcdst) 
#घोषणा Sglext_clear_signexponent(srcdst) Sgl_clear_signexponent(srcdst) 
#घोषणा Sglext_clear_sign(srcdst) Sgl_clear_sign(srcdst) 
#घोषणा Sglext_isone_hidden(dbl_value) Sgl_isone_hidden(dbl_value) 

#घोषणा Sglext_denormalize(opndp1,opndp2,exponent,is_tiny)		\
  अणुपूर्णांक sticky;								\
    is_tiny = TRUE;							\
    अगर (exponent == 0 && Sextallp2(opndp2)) अणु				\
	चयन (Rounding_mode()) अणु					\
	हाल ROUNDPLUS:							\
		अगर (Sgl_iszero_sign(opndp1))				\
			अगर (Sgl_isone_hiddenoverflow(opndp1 + 1))	\
				is_tiny = FALSE;			\
		अवरोध;							\
	हाल ROUNDMINUS:						\
		अगर (Sgl_isone_sign(opndp1)) अणु				\
			अगर (Sgl_isone_hiddenoverflow(opndp1 + 1))	\
				is_tiny = FALSE;			\
		पूर्ण							\
		अवरोध;							\
	हाल ROUNDNEAREST:						\
		अगर (Sglext_isone_highp2(opndp2) &&			\
		    (Sglext_isone_lowp1(opndp1) || 			\
		     Sglext_isnotzero_low31p2(opndp2)))			\
			अगर (Sgl_isone_hiddenoverflow(opndp1 + 1))	\
				is_tiny = FALSE;			\
		अवरोध;							\
	पूर्ण								\
    पूर्ण									\
    Sglext_clear_signexponent_set_hidden(opndp1);			\
    अगर (exponent >= (1-DBL_P)) अणु					\
	अगर (exponent >= -31) अणु						\
	    अगर (exponent > -31) अणु					\
		sticky = Sextallp2(opndp2) << 31+exponent;		\
		Variable_shअगरt_द्विगुन(opndp1,opndp2,1-exponent,opndp2);	\
		Sextallp1(opndp1) >>= 1-exponent;			\
	    पूर्ण								\
	    अन्यथा अणु							\
		sticky = Sextallp2(opndp2);				\
		Sextallp2(opndp2) = Sextallp1(opndp1);			\
		Sextallp1(opndp1) = 0;					\
	    पूर्ण								\
	पूर्ण								\
	अन्यथा अणु								\
	    sticky = (Sextallp1(opndp1) << 31+exponent) | 		\
		     Sextallp2(opndp2);					\
	    Sextallp2(opndp2) = Sextallp1(opndp1) >> -31-exponent;	\
	    Sextallp1(opndp1) = 0;					\
	पूर्ण								\
    पूर्ण									\
    अन्यथा अणु								\
	sticky = Sextallp1(opndp1) | Sextallp2(opndp2);			\
	Sglext_setzero(opndp1,opndp2);					\
    पूर्ण									\
    अगर (sticky) Sglext_setone_lowmantissap2(opndp2);			\
    exponent = 0;							\
  पूर्ण
