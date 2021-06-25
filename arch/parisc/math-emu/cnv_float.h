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

/*
 * Some more स्थिरants
 */
#घोषणा SGL_FX_MAX_EXP 30
#घोषणा DBL_FX_MAX_EXP 62
#घोषणा QUAD_FX_MAX_EXP 126

#घोषणा Dपूर्णांकp1(object) (object)
#घोषणा Dपूर्णांकp2(object) (object)

#घोषणा Duपूर्णांकp1(object) (object)
#घोषणा Duपूर्णांकp2(object) (object)

#घोषणा Qपूर्णांकp0(object) (object)
#घोषणा Qपूर्णांकp1(object) (object)
#घोषणा Qपूर्णांकp2(object) (object)
#घोषणा Qपूर्णांकp3(object) (object)


/*
 * These macros will be used specअगरically by the convert inकाष्ठाions.
 *
 *
 * Single क्रमmat macros
 */

#घोषणा Sgl_to_dbl_exponent(src_exponent,dest)			\
    Deposit_dexponent(dest,src_exponent+(DBL_BIAS-SGL_BIAS))

#घोषणा Sgl_to_dbl_mantissa(src_mantissa,destA,destB)	\
    Deposit_dmantissap1(destA,src_mantissa>>3);		\
    Dmantissap2(destB) = src_mantissa << 29

#घोषणा Sgl_isinexact_to_fix(sgl_value,exponent)	\
    ((exponent < (SGL_P - 1)) ?				\
     (Sall(sgl_value) << (SGL_EXP_LENGTH + 1 + exponent)) : FALSE)

#घोषणा Int_isinexact_to_sgl(पूर्णांक_value)	((पूर्णांक_value << 33 - SGL_EXP_LENGTH) != 0)

#घोषणा Sgl_roundnearest_from_पूर्णांक(पूर्णांक_value,sgl_value)			\
    अगर (पूर्णांक_value & 1<<(SGL_EXP_LENGTH - 2))   /* round bit */		\
	अगर (((पूर्णांक_value << 34 - SGL_EXP_LENGTH) != 0) || Slow(sgl_value)) \
		Sall(sgl_value)++

#घोषणा Dपूर्णांक_isinexact_to_sgl(dपूर्णांक_valueA,dपूर्णांक_valueB)		\
    (((Dपूर्णांकp1(dपूर्णांक_valueA) << 33 - SGL_EXP_LENGTH) != 0) || Dपूर्णांकp2(dपूर्णांक_valueB))

#घोषणा Sgl_roundnearest_from_dपूर्णांक(dपूर्णांक_valueA,dपूर्णांक_valueB,sgl_value)	\
    अगर (Dपूर्णांकp1(dपूर्णांक_valueA) & 1<<(SGL_EXP_LENGTH - 2)) 			\
	अगर (((Dपूर्णांकp1(dपूर्णांक_valueA) << 34 - SGL_EXP_LENGTH) != 0) ||	\
    	Dपूर्णांकp2(dपूर्णांक_valueB) || Slow(sgl_value)) Sall(sgl_value)++

#घोषणा Dपूर्णांक_isinexact_to_dbl(dपूर्णांक_value) 	\
    (Dपूर्णांकp2(dपूर्णांक_value) << 33 - DBL_EXP_LENGTH)

#घोषणा Dbl_roundnearest_from_dपूर्णांक(dपूर्णांक_opndB,dbl_opndA,dbl_opndB) 	\
    अगर (Dपूर्णांकp2(dपूर्णांक_opndB) & 1<<(DBL_EXP_LENGTH - 2))			\
       अगर ((Dपूर्णांकp2(dपूर्णांक_opndB) << 34 - DBL_EXP_LENGTH) || Dlowp2(dbl_opndB))  \
          अगर ((++Dallp2(dbl_opndB))==0) Dallp1(dbl_opndA)++

#घोषणा Sgl_isone_roundbit(sgl_value,exponent)			\
    ((Sall(sgl_value) << (SGL_EXP_LENGTH + 1 + exponent)) >> 31)

#घोषणा Sgl_isone_stickybit(sgl_value,exponent)		\
    (exponent < (SGL_P - 2) ?				\
     Sall(sgl_value) << (SGL_EXP_LENGTH + 2 + exponent) : FALSE)


/* 
 * Double क्रमmat macros
 */

#घोषणा Dbl_to_sgl_exponent(src_exponent,dest)			\
    dest = src_exponent + (SGL_BIAS - DBL_BIAS)

#घोषणा Dbl_to_sgl_mantissa(srcA,srcB,dest,inexact,guard,sticky,odd)	\
    Shअगरtद्विगुन(Dmantissap1(srcA),Dmantissap2(srcB),29,dest); 	\
    guard = Dbit3p2(srcB);					\
    sticky = Dallp2(srcB)<<4;					\
    inexact = guard | sticky;					\
    odd = Dbit2p2(srcB)

#घोषणा Dbl_to_sgl_denormalized(srcA,srcB,exp,dest,inexact,guard,sticky,odd,tiny) \
    Deposit_dexponent(srcA,1);						\
    tiny = TRUE;							\
    अगर (exp >= -2) अणु							\
	अगर (exp == 0) अणु							\
	    inexact = Dallp2(srcB) << 3;				\
	    guard = inexact >> 31;					\
	    sticky = inexact << 1;					\
	    Shअगरtद्विगुन(Dmantissap1(srcA),Dmantissap2(srcB),29,dest);	\
	    odd = dest << 31;						\
	    अगर (inexact) अणु						\
		चयन(Rounding_mode()) अणु				\
		    हाल ROUNDPLUS:					\
			अगर (Dbl_iszero_sign(srcA)) अणु			\
			    dest++;					\
			    अगर (Sgl_isone_hidden(dest))	\
				tiny = FALSE;				\
			    dest--;					\
			पूर्ण						\
			अवरोध;						\
		    हाल ROUNDMINUS:					\
			अगर (Dbl_isone_sign(srcA)) अणु			\
			    dest++;					\
			    अगर (Sgl_isone_hidden(dest))	\
				tiny = FALSE;				\
			    dest--;					\
			पूर्ण						\
			अवरोध;						\
		    हाल ROUNDNEAREST:					\
			अगर (guard && (sticky || odd)) अणु			\
			    dest++;					\
			    अगर (Sgl_isone_hidden(dest))	\
				tiny = FALSE;				\
			    dest--;					\
			पूर्ण						\
			अवरोध;						\
		पूर्ण							\
	    पूर्ण								\
		/* shअगरt right by one to get correct result */		\
		guard = odd;						\
		sticky = inexact;					\
		inexact |= guard;					\
		dest >>= 1;						\
    		Deposit_dsign(srcA,0);					\
    	        Shअगरtद्विगुन(Dallp1(srcA),Dallp2(srcB),30,dest);		\
	        odd = dest << 31;					\
	पूर्ण								\
	अन्यथा अणु								\
    	    inexact = Dallp2(srcB) << (2 + exp);			\
    	    guard = inexact >> 31;					\
    	    sticky = inexact << 1; 					\
    	    Deposit_dsign(srcA,0);					\
    	    अगर (exp == -2) dest = Dallp1(srcA);				\
    	    अन्यथा Variable_shअगरt_द्विगुन(Dallp1(srcA),Dallp2(srcB),30-exp,dest); \
    	    odd = dest << 31;						\
	पूर्ण								\
    पूर्ण									\
    अन्यथा अणु								\
    	Deposit_dsign(srcA,0);						\
    	अगर (exp > (1 - SGL_P)) अणु					\
    	    dest = Dallp1(srcA) >> (- 2 - exp);				\
    	    inexact = Dallp1(srcA) << (34 + exp);			\
    	    guard = inexact >> 31;					\
    	    sticky = (inexact << 1) | Dallp2(srcB);			\
    	    inexact |= Dallp2(srcB); 					\
    	    odd = dest << 31;						\
    	पूर्ण								\
    	अन्यथा अणु								\
    	    dest = 0;							\
    	    inexact = Dallp1(srcA) | Dallp2(srcB);			\
    	    अगर (exp == (1 - SGL_P)) अणु					\
    	    	guard = Dhidden(srcA);					\
    	    	sticky = Dmantissap1(srcA) | Dallp2(srcB); 		\
    	    पूर्ण								\
    	    अन्यथा अणु							\
    	    	guard = 0;						\
    	    	sticky = inexact;					\
    	    पूर्ण								\
    	    odd = 0;							\
    	पूर्ण								\
    पूर्ण									\
    exp = 0

#घोषणा Dbl_isinexact_to_fix(dbl_valueA,dbl_valueB,exponent)		\
    (exponent < (DBL_P-33) ? 						\
     Dallp2(dbl_valueB) || Dallp1(dbl_valueA) << (DBL_EXP_LENGTH+1+exponent) : \
     (exponent < (DBL_P-1) ? Dallp2(dbl_valueB) << (exponent + (33-DBL_P)) :   \
      FALSE))

#घोषणा Dbl_isoverflow_to_पूर्णांक(exponent,dbl_valueA,dbl_valueB)		\
    ((exponent > SGL_FX_MAX_EXP + 1) || Dsign(dbl_valueA)==0 ||		\
     Dmantissap1(dbl_valueA)!=0 || (Dallp2(dbl_valueB)>>21)!=0 ) 

#घोषणा Dbl_isone_roundbit(dbl_valueA,dbl_valueB,exponent)              \
    ((exponent < (DBL_P - 33) ?						\
      Dallp1(dbl_valueA) >> ((30 - DBL_EXP_LENGTH) - exponent) :	\
      Dallp2(dbl_valueB) >> ((DBL_P - 2) - exponent)) & 1)

#घोषणा Dbl_isone_stickybit(dbl_valueA,dbl_valueB,exponent)		\
    (exponent < (DBL_P-34) ? 						\
     (Dallp2(dbl_valueB) || Dallp1(dbl_valueA)<<(DBL_EXP_LENGTH+2+exponent)) : \
     (exponent<(DBL_P-2) ? (Dallp2(dbl_valueB) << (exponent + (34-DBL_P))) : \
      FALSE))


/* Int macros */

#घोषणा Int_from_sgl_mantissa(sgl_value,exponent)	\
    Sall(sgl_value) = 				\
    	(अचिन्हित)(Sall(sgl_value) << SGL_EXP_LENGTH)>>(31 - exponent)

#घोषणा Int_from_dbl_mantissa(dbl_valueA,dbl_valueB,exponent)	\
    Shअगरtद्विगुन(Dallp1(dbl_valueA),Dallp2(dbl_valueB),22,Dallp1(dbl_valueA)); \
    अगर (exponent < 31) Dallp1(dbl_valueA) >>= 30 - exponent;	\
    अन्यथा Dallp1(dbl_valueA) <<= 1

#घोषणा Int_negate(पूर्णांक_value) पूर्णांक_value = -पूर्णांक_value


/* Dपूर्णांक macros */

#घोषणा Dपूर्णांक_from_sgl_mantissa(sgl_value,exponent,dresultA,dresultB)	\
    अणुSall(sgl_value) <<= SGL_EXP_LENGTH;  /*  left-justअगरy  */		\
    अगर (exponent <= 31) अणु						\
    	Dपूर्णांकp1(dresultA) = 0;						\
    	Dपूर्णांकp2(dresultB) = (अचिन्हित)Sall(sgl_value) >> (31 - exponent); \
    पूर्ण									\
    अन्यथा अणु								\
    	Dपूर्णांकp1(dresultA) = Sall(sgl_value) >> (63 - exponent);		\
    	Dपूर्णांकp2(dresultB) = Sall(sgl_value) << (exponent - 31);		\
    पूर्णपूर्ण


#घोषणा Dपूर्णांक_from_dbl_mantissa(dbl_valueA,dbl_valueB,exponent,destA,destB) \
    अणुअगर (exponent < 32) अणु						\
    	Dपूर्णांकp1(destA) = 0;						\
    	अगर (exponent <= 20)						\
    	    Dपूर्णांकp2(destB) = Dallp1(dbl_valueA) >> 20-exponent;		\
    	अन्यथा Variable_shअगरt_द्विगुन(Dallp1(dbl_valueA),Dallp2(dbl_valueB), \
	     52-exponent,Dपूर्णांकp2(destB));					\
    पूर्ण									\
    अन्यथा अणु								\
    	अगर (exponent <= 52) अणु						\
    	    Dपूर्णांकp1(destA) = Dallp1(dbl_valueA) >> 52-exponent;		\
	    अगर (exponent == 52) Dपूर्णांकp2(destB) = Dallp2(dbl_valueB);	\
	    अन्यथा Variable_shअगरt_द्विगुन(Dallp1(dbl_valueA),Dallp2(dbl_valueB), \
	    52-exponent,Dपूर्णांकp2(destB));					\
        पूर्ण								\
    	अन्यथा अणु								\
    	    Variable_shअगरt_द्विगुन(Dallp1(dbl_valueA),Dallp2(dbl_valueB), \
	    84-exponent,Dपूर्णांकp1(destA));					\
    	    Dपूर्णांकp2(destB) = Dallp2(dbl_valueB) << exponent-52;		\
    	पूर्ण								\
    पूर्णपूर्ण

#घोषणा Dपूर्णांक_setzero(dresultA,dresultB) 	\
    Dपूर्णांकp1(dresultA) = 0; 	\
    Dपूर्णांकp2(dresultB) = 0

#घोषणा Dपूर्णांक_setone_sign(dresultA,dresultB)		\
    Dपूर्णांकp1(dresultA) = ~Dपूर्णांकp1(dresultA);		\
    अगर ((Dपूर्णांकp2(dresultB) = -Dपूर्णांकp2(dresultB)) == 0) Dपूर्णांकp1(dresultA)++

#घोषणा Dपूर्णांक_set_minपूर्णांक(dresultA,dresultB)		\
    Dपूर्णांकp1(dresultA) = (अचिन्हित पूर्णांक)1<<31;		\
    Dपूर्णांकp2(dresultB) = 0

#घोषणा Dपूर्णांक_isone_lowp2(dresultB)  (Dपूर्णांकp2(dresultB) & 01)

#घोषणा Dपूर्णांक_increment(dresultA,dresultB) 		\
    अगर ((++Dपूर्णांकp2(dresultB))==0) Dपूर्णांकp1(dresultA)++

#घोषणा Dपूर्णांक_decrement(dresultA,dresultB) 		\
    अगर ((Dपूर्णांकp2(dresultB)--)==0) Dपूर्णांकp1(dresultA)--

#घोषणा Dपूर्णांक_negate(dresultA,dresultB)			\
    Dपूर्णांकp1(dresultA) = ~Dपूर्णांकp1(dresultA);		\
    अगर ((Dपूर्णांकp2(dresultB) = -Dपूर्णांकp2(dresultB))==0) Dपूर्णांकp1(dresultA)++

#घोषणा Dपूर्णांक_copyfromptr(src,destA,destB) \
     Dपूर्णांकp1(destA) = src->wd0;		\
     Dपूर्णांकp2(destB) = src->wd1
#घोषणा Dपूर्णांक_copytoptr(srcA,srcB,dest)	\
    dest->wd0 = Dपूर्णांकp1(srcA);		\
    dest->wd1 = Dपूर्णांकp2(srcB)


/* other macros  */

#घोषणा Find_ms_one_bit(value, position)	\
    अणु						\
	पूर्णांक var;				\
	क्रम (var=8; var >=1; var >>= 1) अणु	\
	    अगर (value >> 32 - position)		\
		position -= var;		\
		अन्यथा position += var;		\
	पूर्ण					\
	अगर ((value >> 32 - position) == 0)	\
	    position--;				\
	अन्यथा position -= 2;			\
    पूर्ण


/*
 * Unचिन्हित पूर्णांक macros
 */
#घोषणा Duपूर्णांक_copyfromptr(src,destA,destB) \
    Dपूर्णांक_copyfromptr(src,destA,destB)
#घोषणा Duपूर्णांक_copytoptr(srcA,srcB,dest)	\
    Dपूर्णांक_copytoptr(srcA,srcB,dest)

#घोषणा Suपूर्णांक_isinexact_to_sgl(पूर्णांक_value) \
    (पूर्णांक_value << 32 - SGL_EXP_LENGTH)

#घोषणा Sgl_roundnearest_from_suपूर्णांक(suपूर्णांक_value,sgl_value)		\
    अगर (suपूर्णांक_value & 1<<(SGL_EXP_LENGTH - 1))   /* round bit */	\
    	अगर ((suपूर्णांक_value << 33 - SGL_EXP_LENGTH) || Slow(sgl_value))	\
		Sall(sgl_value)++

#घोषणा Duपूर्णांक_isinexact_to_sgl(duपूर्णांक_valueA,duपूर्णांक_valueB)	\
    ((Duपूर्णांकp1(duपूर्णांक_valueA) << 32 - SGL_EXP_LENGTH) || Duपूर्णांकp2(duपूर्णांक_valueB))

#घोषणा Sgl_roundnearest_from_duपूर्णांक(duपूर्णांक_valueA,duपूर्णांक_valueB,sgl_value) \
    अगर (Duपूर्णांकp1(duपूर्णांक_valueA) & 1<<(SGL_EXP_LENGTH - 1))		\
    	अगर ((Duपूर्णांकp1(duपूर्णांक_valueA) << 33 - SGL_EXP_LENGTH) ||		\
    	Duपूर्णांकp2(duपूर्णांक_valueB) || Slow(sgl_value)) Sall(sgl_value)++

#घोषणा Duपूर्णांक_isinexact_to_dbl(duपूर्णांक_value) 	\
    (Duपूर्णांकp2(duपूर्णांक_value) << 32 - DBL_EXP_LENGTH)

#घोषणा Dbl_roundnearest_from_duपूर्णांक(duपूर्णांक_opndB,dbl_opndA,dbl_opndB) 	\
    अगर (Duपूर्णांकp2(duपूर्णांक_opndB) & 1<<(DBL_EXP_LENGTH - 1))			\
       अगर ((Duपूर्णांकp2(duपूर्णांक_opndB) << 33 - DBL_EXP_LENGTH) || Dlowp2(dbl_opndB)) \
          अगर ((++Dallp2(dbl_opndB))==0) Dallp1(dbl_opndA)++

#घोषणा Suपूर्णांक_from_sgl_mantissa(src,exponent,result)	\
    Sall(result) = (अचिन्हित)(Sall(src) << SGL_EXP_LENGTH)>>(31 - exponent)

#घोषणा Sgl_isinexact_to_अचिन्हित(sgl_value,exponent)	\
    Sgl_isinexact_to_fix(sgl_value,exponent)

#घोषणा Duपूर्णांक_from_sgl_mantissa(sgl_value,exponent,dresultA,dresultB)	\
  अणुअचिन्हित पूर्णांक val = Sall(sgl_value) << SGL_EXP_LENGTH;		\
    अगर (exponent <= 31) अणु						\
	Dपूर्णांकp1(dresultA) = 0;						\
	Dपूर्णांकp2(dresultB) = val >> (31 - exponent);			\
    पूर्ण									\
    अन्यथा अणु								\
	Dपूर्णांकp1(dresultA) = val >> (63 - exponent);			\
	Dपूर्णांकp2(dresultB) = exponent <= 62 ? val << (exponent - 31) : 0;	\
    पूर्ण									\
  पूर्ण

#घोषणा Duपूर्णांक_setzero(dresultA,dresultB) 	\
    Dपूर्णांक_setzero(dresultA,dresultB)

#घोषणा Duपूर्णांक_increment(dresultA,dresultB) Dपूर्णांक_increment(dresultA,dresultB) 

#घोषणा Duपूर्णांक_isone_lowp2(dresultB)  Dपूर्णांक_isone_lowp2(dresultB)

#घोषणा Suपूर्णांक_from_dbl_mantissa(srcA,srcB,exponent,dest) \
    Shअगरtद्विगुन(Dallp1(srcA),Dallp2(srcB),21,dest); \
    dest = (अचिन्हित)dest >> 31 - exponent

#घोषणा Dbl_isinexact_to_अचिन्हित(dbl_valueA,dbl_valueB,exponent) \
    Dbl_isinexact_to_fix(dbl_valueA,dbl_valueB,exponent)

#घोषणा Duपूर्णांक_from_dbl_mantissa(dbl_valueA,dbl_valueB,exponent,destA,destB) \
    Dपूर्णांक_from_dbl_mantissa(dbl_valueA,dbl_valueB,exponent,destA,destB) 
