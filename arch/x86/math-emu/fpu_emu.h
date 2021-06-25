<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*---------------------------------------------------------------------------+
 |  fpu_emu.h                                                                |
 |                                                                           |
 | Copyright (C) 1992,1993,1994,1997                                         |
 |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |
 |                       Australia.  E-mail   billm@suburbia.net             |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#अगर_अघोषित _FPU_EMU_H_
#घोषणा _FPU_EMU_H_

/*
 * Define PECULIAR_486 to get a बंदr approximation to 80486 behaviour,
 * rather than behaviour which appears to be cleaner.
 * This is a matter of opinion: क्रम all I know, the 80486 may simply
 * be complying with the IEEE spec. Maybe one day I'll get to see the
 * spec...
 */
#घोषणा PECULIAR_486

#अगर_घोषित __ASSEMBLY__
#समावेश "fpu_asm.h"
#घोषणा	Const(x)	$##x
#अन्यथा
#घोषणा	Const(x)	x
#पूर्ण_अगर

#घोषणा EXP_BIAS	Const(0)
#घोषणा EXP_OVER	Const(0x4000)	/* smallest invalid large exponent */
#घोषणा	EXP_UNDER	Const(-0x3fff)	/* largest invalid small exponent */
#घोषणा EXP_WAY_UNDER   Const(-0x6000)	/* Below the smallest denormal, but
					   still a 16 bit nr. */
#घोषणा EXP_Infinity    EXP_OVER
#घोषणा EXP_NaN         EXP_OVER

#घोषणा EXTENDED_Ebias Const(0x3fff)
#घोषणा EXTENDED_Emin (-0x3ffe)	/* smallest valid exponent */

#घोषणा SIGN_POS	Const(0)
#घोषणा SIGN_NEG	Const(0x80)

#घोषणा SIGN_Positive	Const(0)
#घोषणा SIGN_Negative	Const(0x8000)

/* Keep the order TAG_Valid, TAG_Zero, TW_Denormal */
/* The following fold to 2 (Special) in the Tag Word */
#घोषणा TW_Denormal     Const(4)	/* De-normal */
#घोषणा TW_Infinity	Const(5)	/* + or - infinity */
#घोषणा	TW_NaN		Const(6)	/* Not a Number */
#घोषणा	TW_Unsupported	Const(7)	/* Not supported by an 80486 */

#घोषणा TAG_Valid	Const(0)	/* valid */
#घोषणा TAG_Zero	Const(1)	/* zero */
#घोषणा TAG_Special	Const(2)	/* De-normal, + or - infinity,
					   or Not a Number */
#घोषणा TAG_Empty	Const(3)	/* empty */
#घोषणा TAG_Error	Const(0x80)	/* probably need to पात */

#घोषणा LOADED_DATA	Const(10101)	/* Special st() number to identअगरy
					   loaded data (not on stack). */

/* A few flags (must be >= 0x10). */
#घोषणा REV             0x10
#घोषणा DEST_RM         0x20
#घोषणा LOADED          0x40

#घोषणा FPU_Exception   Const(0x80000000)	/* Added to tag वापसs. */

#अगर_अघोषित __ASSEMBLY__

#समावेश "fpu_system.h"

#समावेश <uapi/यंत्र/sigcontext.h>	/* क्रम काष्ठा _fpstate */
#समावेश <यंत्र/math_emu.h>
#समावेश <linux/linkage.h>

/*
#घोषणा RE_ENTRANT_CHECKING
 */

#अगर_घोषित RE_ENTRANT_CHECKING
बाह्य u_अक्षर emulating;
#  define RE_ENTRANT_CHECK_OFF emulating = 0
#  define RE_ENTRANT_CHECK_ON emulating = 1
#अन्यथा
#  define RE_ENTRANT_CHECK_OFF
#  define RE_ENTRANT_CHECK_ON
#पूर्ण_अगर /* RE_ENTRANT_CHECKING */

#घोषणा FWAIT_OPCODE 0x9b
#घोषणा OP_SIZE_PREFIX 0x66
#घोषणा ADDR_SIZE_PREFIX 0x67
#घोषणा PREFIX_CS 0x2e
#घोषणा PREFIX_DS 0x3e
#घोषणा PREFIX_ES 0x26
#घोषणा PREFIX_SS 0x36
#घोषणा PREFIX_FS 0x64
#घोषणा PREFIX_GS 0x65
#घोषणा PREFIX_REPE 0xf3
#घोषणा PREFIX_REPNE 0xf2
#घोषणा PREFIX_LOCK 0xf0
#घोषणा PREFIX_CS_ 1
#घोषणा PREFIX_DS_ 2
#घोषणा PREFIX_ES_ 3
#घोषणा PREFIX_FS_ 4
#घोषणा PREFIX_GS_ 5
#घोषणा PREFIX_SS_ 6
#घोषणा PREFIX_DEFAULT 7

काष्ठा address अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक selector:16;
	अचिन्हित पूर्णांक opcode:11;
	अचिन्हित पूर्णांक empty:5;
पूर्ण;
काष्ठा fpu__reg अणु
	अचिन्हित sigl;
	अचिन्हित sigh;
	लघु exp;
पूर्ण;

प्रकार व्योम (*FUNC) (व्योम);
प्रकार काष्ठा fpu__reg FPU_REG;
प्रकार व्योम (*FUNC_ST0) (FPU_REG *st0_ptr, u_अक्षर st0_tag);
प्रकार काष्ठा अणु
	u_अक्षर address_size, opeअक्रम_size, segment;
पूर्ण overrides;
/* This काष्ठाure is 32 bits: */
प्रकार काष्ठा अणु
	overrides override;
	u_अक्षर शेष_mode;
पूर्ण fpu_addr_modes;
/* PROTECTED has a restricted meaning in the emulator; it is used
   to संकेत that the emulator needs to करो special things to ensure
   that protection is respected in a segmented model. */
#घोषणा PROTECTED 4
#घोषणा SIXTEEN   1		/* We rely upon this being 1 (true) */
#घोषणा VM86      SIXTEEN
#घोषणा PM16      (SIXTEEN | PROTECTED)
#घोषणा SEG32     PROTECTED
बाह्य u_अक्षर स्थिर data_sizes_16[32];

#घोषणा रेजिस्टर_base ((u_अक्षर *) रेजिस्टरs )
#घोषणा fpu_रेजिस्टर(x)  ( * ((FPU_REG *)( रेजिस्टर_base + 10 * (x & 7) )) )
#घोषणा	st(x)      ( * ((FPU_REG *)( रेजिस्टर_base + 10 * ((top+x) & 7) )) )

#घोषणा	STACK_OVERFLOW	(FPU_stackoverflow(&st_new_ptr))
#घोषणा	NOT_EMPTY(i)	(!FPU_empty_i(i))

#घोषणा	NOT_EMPTY_ST0	(st0_tag ^ TAG_Empty)

#घोषणा poppop() अणु FPU_pop(); FPU_pop(); पूर्ण

/* push() करोes not affect the tags */
#घोषणा push()	अणु top--; पूर्ण

#घोषणा signbyte(a) (((u_अक्षर *)(a))[9])
#घोषणा माला_लोign(a) (signbyte(a) & 0x80)
#घोषणा setsign(a,b) अणु अगर ((b) != 0) signbyte(a) |= 0x80; अन्यथा signbyte(a) &= 0x7f; पूर्ण
#घोषणा copysign(a,b) अणु अगर (माला_लोign(a)) signbyte(b) |= 0x80; \
                        अन्यथा signbyte(b) &= 0x7f; पूर्ण
#घोषणा changesign(a) अणु signbyte(a) ^= 0x80; पूर्ण
#घोषणा setpositive(a) अणु signbyte(a) &= 0x7f; पूर्ण
#घोषणा setnegative(a) अणु signbyte(a) |= 0x80; पूर्ण
#घोषणा signpositive(a) ( (signbyte(a) & 0x80) == 0 )
#घोषणा signnegative(a) (signbyte(a) & 0x80)

अटल अंतरभूत व्योम reg_copy(FPU_REG स्थिर *x, FPU_REG *y)
अणु
	*(लघु *)&(y->exp) = *(स्थिर लघु *)&(x->exp);
	*(दीर्घ दीर्घ *)&(y->sigl) = *(स्थिर दीर्घ दीर्घ *)&(x->sigl);
पूर्ण

#घोषणा exponent(x)  (((*(लघु *)&((x)->exp)) & 0x7fff) - EXTENDED_Ebias)
#घोषणा setexponentpos(x,y) अणु (*(लघु *)&((x)->exp)) = \
  ((y) + EXTENDED_Ebias) & 0x7fff; पूर्ण
#घोषणा exponent16(x)         (*(लघु *)&((x)->exp))
#घोषणा setexponent16(x,y)  अणु (*(लघु *)&((x)->exp)) = (u16)(y); पूर्ण
#घोषणा addexponent(x,y)    अणु (*(लघु *)&((x)->exp)) += (y); पूर्ण
#घोषणा stdexp(x)           अणु (*(लघु *)&((x)->exp)) += EXTENDED_Ebias; पूर्ण

#घोषणा isdenormal(ptr)   (exponent(ptr) == EXP_BIAS+EXP_UNDER)

#घोषणा signअगरicand(x) ( ((अचिन्हित दीर्घ दीर्घ *)&((x)->sigl))[0] )

/*----- Prototypes क्रम functions written in assembler -----*/
/* बाह्य व्योम reg_move(FPU_REG *a, FPU_REG *b); */

यंत्रlinkage पूर्णांक FPU_normalize(FPU_REG *x);
यंत्रlinkage पूर्णांक FPU_normalize_nuo(FPU_REG *x);
यंत्रlinkage पूर्णांक FPU_u_sub(FPU_REG स्थिर *arg1, FPU_REG स्थिर *arg2,
			 FPU_REG * answ, अचिन्हित पूर्णांक control_w, u_अक्षर sign,
			 पूर्णांक expa, पूर्णांक expb);
यंत्रlinkage पूर्णांक FPU_u_mul(FPU_REG स्थिर *arg1, FPU_REG स्थिर *arg2,
			 FPU_REG * answ, अचिन्हित पूर्णांक control_w, u_अक्षर sign,
			 पूर्णांक expon);
यंत्रlinkage पूर्णांक FPU_u_भाग(FPU_REG स्थिर *arg1, FPU_REG स्थिर *arg2,
			 FPU_REG * answ, अचिन्हित पूर्णांक control_w, u_अक्षर sign);
यंत्रlinkage पूर्णांक FPU_u_add(FPU_REG स्थिर *arg1, FPU_REG स्थिर *arg2,
			 FPU_REG * answ, अचिन्हित पूर्णांक control_w, u_अक्षर sign,
			 पूर्णांक expa, पूर्णांक expb);
यंत्रlinkage पूर्णांक wm_वर्ग_मूल(FPU_REG *n, पूर्णांक dummy1, पूर्णांक dummy2,
		       अचिन्हित पूर्णांक control_w, u_अक्षर sign);
यंत्रlinkage अचिन्हित FPU_shrx(व्योम *l, अचिन्हित x);
यंत्रlinkage अचिन्हित FPU_shrxs(व्योम *v, अचिन्हित x);
यंत्रlinkage अचिन्हित दीर्घ FPU_भाग_small(अचिन्हित दीर्घ दीर्घ *x, अचिन्हित दीर्घ y);
यंत्रlinkage पूर्णांक FPU_round(FPU_REG *arg, अचिन्हित पूर्णांक extent, पूर्णांक dummy,
			 अचिन्हित पूर्णांक control_w, u_अक्षर sign);

#अगर_अघोषित MAKING_PROTO
#समावेश "fpu_proto.h"
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _FPU_EMU_H_ */
