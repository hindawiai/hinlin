<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*---------------------------------------------------------------------------+
 |  errors.c                                                                 |
 |                                                                           |
 |  The error handling functions क्रम wm-FPU-emu                              |
 |                                                                           |
 | Copyright (C) 1992,1993,1994,1996                                         |
 |                  W. Metzenthen, 22 Parker St, Ormond, Vic 3163, Australia |
 |                  E-mail   billm@jacobi.maths.monash.edu.au                |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------+
 | Note:                                                                     |
 |    The file contains code which accesses user memory.                     |
 |    Emulator अटल data may change when user memory is accessed, due to   |
 |    other processes using the emulator जबतक swapping is in progress.      |
 +---------------------------------------------------------------------------*/

#समावेश <linux/संकेत.स>

#समावेश <linux/uaccess.h>

#समावेश "fpu_emu.h"
#समावेश "fpu_system.h"
#समावेश "exception.h"
#समावेश "status_w.h"
#समावेश "control_w.h"
#समावेश "reg_constant.h"
#समावेश "version.h"

/* */
#अघोषित PRINT_MESSAGES
/* */

#अगर 0
व्योम Un_impl(व्योम)
अणु
	u_अक्षर byte1, FPU_modrm;
	अचिन्हित दीर्घ address = FPU_ORIG_EIP;

	RE_ENTRANT_CHECK_OFF;
	/* No need to check access_ok(), we have previously fetched these bytes. */
	prपूर्णांकk("Unimplemented FPU Opcode at eip=%p : ", (व्योम __user *)address);
	अगर (FPU_CS == __USER_CS) अणु
		जबतक (1) अणु
			FPU_get_user(byte1, (u_अक्षर __user *) address);
			अगर ((byte1 & 0xf8) == 0xd8)
				अवरोध;
			prपूर्णांकk("[%02x]", byte1);
			address++;
		पूर्ण
		prपूर्णांकk("%02x ", byte1);
		FPU_get_user(FPU_modrm, 1 + (u_अक्षर __user *) address);

		अगर (FPU_modrm >= 0300)
			prपूर्णांकk("%02x (%02x+%d)\n", FPU_modrm, FPU_modrm & 0xf8,
			       FPU_modrm & 7);
		अन्यथा
			prपूर्णांकk("/%d\n", (FPU_modrm >> 3) & 7);
	पूर्ण अन्यथा अणु
		prपूर्णांकk("cs selector = %04x\n", FPU_CS);
	पूर्ण

	RE_ENTRANT_CHECK_ON;

	EXCEPTION(EX_Invalid);

पूर्ण
#पूर्ण_अगर /*  0  */

/*
   Called क्रम opcodes which are illegal and which are known to result in a
   संक_अवैध with a real 80486.
   */
व्योम FPU_illegal(व्योम)
अणु
	math_पात(FPU_info, संक_अवैध);
पूर्ण

व्योम FPU_prपूर्णांकall(व्योम)
अणु
	पूर्णांक i;
	अटल स्थिर अक्षर *tag_desc[] = अणु "Valid", "Zero", "ERROR", "Empty",
		"DeNorm", "Inf", "NaN"
	पूर्ण;
	u_अक्षर byte1, FPU_modrm;
	अचिन्हित दीर्घ address = FPU_ORIG_EIP;

	RE_ENTRANT_CHECK_OFF;
	/* No need to check access_ok(), we have previously fetched these bytes. */
	prपूर्णांकk("At %p:", (व्योम *)address);
	अगर (FPU_CS == __USER_CS) अणु
#घोषणा MAX_PRINTED_BYTES 20
		क्रम (i = 0; i < MAX_PRINTED_BYTES; i++) अणु
			FPU_get_user(byte1, (u_अक्षर __user *) address);
			अगर ((byte1 & 0xf8) == 0xd8) अणु
				prपूर्णांकk(" %02x", byte1);
				अवरोध;
			पूर्ण
			prपूर्णांकk(" [%02x]", byte1);
			address++;
		पूर्ण
		अगर (i == MAX_PRINTED_BYTES)
			prपूर्णांकk(" [more..]\n");
		अन्यथा अणु
			FPU_get_user(FPU_modrm, 1 + (u_अक्षर __user *) address);

			अगर (FPU_modrm >= 0300)
				prपूर्णांकk(" %02x (%02x+%d)\n", FPU_modrm,
				       FPU_modrm & 0xf8, FPU_modrm & 7);
			अन्यथा
				prपूर्णांकk(" /%d, mod=%d rm=%d\n",
				       (FPU_modrm >> 3) & 7,
				       (FPU_modrm >> 6) & 3, FPU_modrm & 7);
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk("%04x\n", FPU_CS);
	पूर्ण

	partial_status = status_word();

#अगर_घोषित DEBUGGING
	अगर (partial_status & SW_Backward)
		prपूर्णांकk("SW: backward compatibility\n");
	अगर (partial_status & SW_C3)
		prपूर्णांकk("SW: condition bit 3\n");
	अगर (partial_status & SW_C2)
		prपूर्णांकk("SW: condition bit 2\n");
	अगर (partial_status & SW_C1)
		prपूर्णांकk("SW: condition bit 1\n");
	अगर (partial_status & SW_C0)
		prपूर्णांकk("SW: condition bit 0\n");
	अगर (partial_status & SW_Summary)
		prपूर्णांकk("SW: exception summary\n");
	अगर (partial_status & SW_Stack_Fault)
		prपूर्णांकk("SW: stack fault\n");
	अगर (partial_status & SW_Precision)
		prपूर्णांकk("SW: loss of precision\n");
	अगर (partial_status & SW_Underflow)
		prपूर्णांकk("SW: underflow\n");
	अगर (partial_status & SW_Overflow)
		prपूर्णांकk("SW: overflow\n");
	अगर (partial_status & SW_Zero_Div)
		prपूर्णांकk("SW: divide by zero\n");
	अगर (partial_status & SW_Denorm_Op)
		prपूर्णांकk("SW: denormalized operand\n");
	अगर (partial_status & SW_Invalid)
		prपूर्णांकk("SW: invalid operation\n");
#पूर्ण_अगर /* DEBUGGING */

	prपूर्णांकk(" SW: b=%d st=%d es=%d sf=%d cc=%d%d%d%d ef=%d%d%d%d%d%d\n", partial_status & 0x8000 ? 1 : 0,	/* busy */
	       (partial_status & 0x3800) >> 11,	/* stack top poपूर्णांकer */
	       partial_status & 0x80 ? 1 : 0,	/* Error summary status */
	       partial_status & 0x40 ? 1 : 0,	/* Stack flag */
	       partial_status & SW_C3 ? 1 : 0, partial_status & SW_C2 ? 1 : 0,	/* cc */
	       partial_status & SW_C1 ? 1 : 0, partial_status & SW_C0 ? 1 : 0,	/* cc */
	       partial_status & SW_Precision ? 1 : 0,
	       partial_status & SW_Underflow ? 1 : 0,
	       partial_status & SW_Overflow ? 1 : 0,
	       partial_status & SW_Zero_Div ? 1 : 0,
	       partial_status & SW_Denorm_Op ? 1 : 0,
	       partial_status & SW_Invalid ? 1 : 0);

	prपूर्णांकk(" CW: ic=%d rc=%d%d pc=%d%d iem=%d     ef=%d%d%d%d%d%d\n",
	       control_word & 0x1000 ? 1 : 0,
	       (control_word & 0x800) >> 11, (control_word & 0x400) >> 10,
	       (control_word & 0x200) >> 9, (control_word & 0x100) >> 8,
	       control_word & 0x80 ? 1 : 0,
	       control_word & SW_Precision ? 1 : 0,
	       control_word & SW_Underflow ? 1 : 0,
	       control_word & SW_Overflow ? 1 : 0,
	       control_word & SW_Zero_Div ? 1 : 0,
	       control_word & SW_Denorm_Op ? 1 : 0,
	       control_word & SW_Invalid ? 1 : 0);

	क्रम (i = 0; i < 8; i++) अणु
		FPU_REG *r = &st(i);
		u_अक्षर tagi = FPU_gettagi(i);

		चयन (tagi) अणु
		हाल TAG_Empty:
			जारी;
		हाल TAG_Zero:
		हाल TAG_Special:
			/* Update tagi क्रम the prपूर्णांकk below */
			tagi = FPU_Special(r);
			fallthrough;
		हाल TAG_Valid:
			prपूर्णांकk("st(%d)  %c .%04lx %04lx %04lx %04lx e%+-6d ", i,
			       माला_लोign(r) ? '-' : '+',
			       (दीर्घ)(r->sigh >> 16),
			       (दीर्घ)(r->sigh & 0xFFFF),
			       (दीर्घ)(r->sigl >> 16),
			       (दीर्घ)(r->sigl & 0xFFFF),
			       exponent(r) - EXP_BIAS + 1);
			अवरोध;
		शेष:
			prपूर्णांकk("Whoops! Error in errors.c: tag%d is %d ", i,
			       tagi);
			जारी;
		पूर्ण
		prपूर्णांकk("%s\n", tag_desc[(पूर्णांक)(अचिन्हित)tagi]);
	पूर्ण

	RE_ENTRANT_CHECK_ON;

पूर्ण

अटल काष्ठा अणु
	पूर्णांक type;
	स्थिर अक्षर *name;
पूर्ण exception_names[] = अणु
	अणु
	EX_StackOver, "stack overflow"पूर्ण, अणु
	EX_StackUnder, "stack underflow"पूर्ण, अणु
	EX_Precision, "loss of precision"पूर्ण, अणु
	EX_Underflow, "underflow"पूर्ण, अणु
	EX_Overflow, "overflow"पूर्ण, अणु
	EX_ZeroDiv, "divide by zero"पूर्ण, अणु
	EX_Denormal, "denormalized operand"पूर्ण, अणु
	EX_Invalid, "invalid operation"पूर्ण, अणु
	EX_INTERNAL, "INTERNAL BUG in " FPU_VERSIONपूर्ण, अणु
	0, शून्यपूर्ण
पूर्ण;

/*
 EX_INTERNAL is always given with a code which indicates where the
 error was detected.

 Internal error types:
       0x14   in fpu_etc.c
       0x1nn  in a *.c file:
              0x101  in reg_add_sub.c
              0x102  in reg_mul.c
              0x104  in poly_atan.c
              0x105  in reg_mul.c
              0x107  in fpu_trig.c
	      0x108  in reg_compare.c
	      0x109  in reg_compare.c
	      0x110  in reg_add_sub.c
	      0x111  in fpe_entry.c
	      0x112  in fpu_trig.c
	      0x113  in errors.c
	      0x115  in fpu_trig.c
	      0x116  in fpu_trig.c
	      0x117  in fpu_trig.c
	      0x118  in fpu_trig.c
	      0x119  in fpu_trig.c
	      0x120  in poly_atan.c
	      0x121  in reg_compare.c
	      0x122  in reg_compare.c
	      0x123  in reg_compare.c
	      0x125  in fpu_trig.c
	      0x126  in fpu_entry.c
	      0x127  in poly_2xm1.c
	      0x128  in fpu_entry.c
	      0x129  in fpu_entry.c
	      0x130  in get_address.c
	      0x131  in get_address.c
	      0x132  in get_address.c
	      0x133  in get_address.c
	      0x140  in load_store.c
	      0x141  in load_store.c
              0x150  in poly_sin.c
              0x151  in poly_sin.c
	      0x160  in reg_ld_str.c
	      0x161  in reg_ld_str.c
	      0x162  in reg_ld_str.c
	      0x163  in reg_ld_str.c
	      0x164  in reg_ld_str.c
	      0x170  in fpu_tags.c
	      0x171  in fpu_tags.c
	      0x172  in fpu_tags.c
	      0x180  in reg_convert.c
       0x2nn  in an *.S file:
              0x201  in reg_u_add.S
              0x202  in reg_u_भाग.S
              0x203  in reg_u_भाग.S
              0x204  in reg_u_भाग.S
              0x205  in reg_u_mul.S
              0x206  in reg_u_sub.S
              0x207  in wm_वर्ग_मूल.S
	      0x208  in reg_भाग.S
              0x209  in reg_u_sub.S
              0x210  in reg_u_sub.S
              0x211  in reg_u_sub.S
              0x212  in reg_u_sub.S
	      0x213  in wm_वर्ग_मूल.S
	      0x214  in wm_वर्ग_मूल.S
	      0x215  in wm_वर्ग_मूल.S
	      0x220  in reg_norm.S
	      0x221  in reg_norm.S
	      0x230  in reg_round.S
	      0x231  in reg_round.S
	      0x232  in reg_round.S
	      0x233  in reg_round.S
	      0x234  in reg_round.S
	      0x235  in reg_round.S
	      0x236  in reg_round.S
	      0x240  in भाग_Xsig.S
	      0x241  in भाग_Xsig.S
	      0x242  in भाग_Xsig.S
 */

यंत्रlinkage __visible व्योम FPU_exception(पूर्णांक n)
अणु
	पूर्णांक i, पूर्णांक_type;

	पूर्णांक_type = 0;		/* Needed only to stop compiler warnings */
	अगर (n & EX_INTERNAL) अणु
		पूर्णांक_type = n - EX_INTERNAL;
		n = EX_INTERNAL;
		/* Set lots of exception bits! */
		partial_status |= (SW_Exc_Mask | SW_Summary | SW_Backward);
	पूर्ण अन्यथा अणु
		/* Extract only the bits which we use to set the status word */
		n &= (SW_Exc_Mask);
		/* Set the corresponding exception bit */
		partial_status |= n;
		/* Set summary bits अगरf exception isn't masked */
		अगर (partial_status & ~control_word & CW_Exceptions)
			partial_status |= (SW_Summary | SW_Backward);
		अगर (n & (SW_Stack_Fault | EX_Precision)) अणु
			अगर (!(n & SW_C1))
				/* This bit distinguishes over- from underflow क्रम a stack fault,
				   and roundup from round-करोwn क्रम precision loss. */
				partial_status &= ~SW_C1;
		पूर्ण
	पूर्ण

	RE_ENTRANT_CHECK_OFF;
	अगर ((~control_word & n & CW_Exceptions) || (n == EX_INTERNAL)) अणु
		/* Get a name string क्रम error reporting */
		क्रम (i = 0; exception_names[i].type; i++)
			अगर ((exception_names[i].type & n) ==
			    exception_names[i].type)
				अवरोध;

		अगर (exception_names[i].type) अणु
#अगर_घोषित PRINT_MESSAGES
			prपूर्णांकk("FP Exception: %s!\n", exception_names[i].name);
#पूर्ण_अगर /* PRINT_MESSAGES */
		पूर्ण अन्यथा
			prपूर्णांकk("FPU emulator: Unknown Exception: 0x%04x!\n", n);

		अगर (n == EX_INTERNAL) अणु
			prपूर्णांकk("FPU emulator: Internal error type 0x%04x\n",
			       पूर्णांक_type);
			FPU_prपूर्णांकall();
		पूर्ण
#अगर_घोषित PRINT_MESSAGES
		अन्यथा
			FPU_prपूर्णांकall();
#पूर्ण_अगर /* PRINT_MESSAGES */

		/*
		 * The 80486 generates an पूर्णांकerrupt on the next non-control FPU
		 * inकाष्ठाion. So we need some means of flagging it.
		 * We use the ES (Error Summary) bit क्रम this.
		 */
	पूर्ण
	RE_ENTRANT_CHECK_ON;

#अगर_घोषित __DEBUG__
	math_पात(FPU_info, संक_भ_त्रुटि);
#पूर्ण_अगर /* __DEBUG__ */

पूर्ण

/* Real operation attempted on a NaN. */
/* Returns < 0 अगर the exception is unmasked */
पूर्णांक real_1op_NaN(FPU_REG *a)
अणु
	पूर्णांक संकेतling, isNaN;

	isNaN = (exponent(a) == EXP_OVER) && (a->sigh & 0x80000000);

	/* The शेष result क्रम the हाल of two "equal" NaNs (signs may
	   dअगरfer) is chosen to reproduce 80486 behaviour */
	संकेतling = isNaN && !(a->sigh & 0x40000000);

	अगर (!संकेतling) अणु
		अगर (!isNaN) अणु	/* pseuकरो-NaN, or other unsupported? */
			अगर (control_word & CW_Invalid) अणु
				/* Masked response */
				reg_copy(&CONST_QNaN, a);
			पूर्ण
			EXCEPTION(EX_Invalid);
			वापस (!(control_word & CW_Invalid) ? FPU_Exception :
				0) | TAG_Special;
		पूर्ण
		वापस TAG_Special;
	पूर्ण

	अगर (control_word & CW_Invalid) अणु
		/* The masked response */
		अगर (!(a->sigh & 0x80000000)) अणु	/* pseuकरो-NaN ? */
			reg_copy(&CONST_QNaN, a);
		पूर्ण
		/* ensure a Quiet NaN */
		a->sigh |= 0x40000000;
	पूर्ण

	EXCEPTION(EX_Invalid);

	वापस (!(control_word & CW_Invalid) ? FPU_Exception : 0) | TAG_Special;
पूर्ण

/* Real operation attempted on two opeअक्रमs, one a NaN. */
/* Returns < 0 अगर the exception is unmasked */
पूर्णांक real_2op_NaN(FPU_REG स्थिर *b, u_अक्षर tagb,
		 पूर्णांक deststnr, FPU_REG स्थिर *शेषNaN)
अणु
	FPU_REG *dest = &st(deststnr);
	FPU_REG स्थिर *a = dest;
	u_अक्षर taga = FPU_gettagi(deststnr);
	FPU_REG स्थिर *x;
	पूर्णांक संकेतling, unsupported;

	अगर (taga == TAG_Special)
		taga = FPU_Special(a);
	अगर (tagb == TAG_Special)
		tagb = FPU_Special(b);

	/* TW_NaN is also used क्रम unsupported data types. */
	unsupported = ((taga == TW_NaN)
		       && !((exponent(a) == EXP_OVER)
			    && (a->sigh & 0x80000000)))
	    || ((tagb == TW_NaN)
		&& !((exponent(b) == EXP_OVER) && (b->sigh & 0x80000000)));
	अगर (unsupported) अणु
		अगर (control_word & CW_Invalid) अणु
			/* Masked response */
			FPU_copy_to_regi(&CONST_QNaN, TAG_Special, deststnr);
		पूर्ण
		EXCEPTION(EX_Invalid);
		वापस (!(control_word & CW_Invalid) ? FPU_Exception : 0) |
		    TAG_Special;
	पूर्ण

	अगर (taga == TW_NaN) अणु
		x = a;
		अगर (tagb == TW_NaN) अणु
			संकेतling = !(a->sigh & b->sigh & 0x40000000);
			अगर (signअगरicand(b) > signअगरicand(a))
				x = b;
			अन्यथा अगर (signअगरicand(b) == signअगरicand(a)) अणु
				/* The शेष result क्रम the हाल of two "equal" NaNs (signs may
				   dअगरfer) is chosen to reproduce 80486 behaviour */
				x = शेषNaN;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* वापस the quiet version of the NaN in a */
			संकेतling = !(a->sigh & 0x40000000);
		पूर्ण
	पूर्ण अन्यथा
#अगर_घोषित PARANOID
	अगर (tagb == TW_NaN)
#पूर्ण_अगर /* PARANOID */
	अणु
		संकेतling = !(b->sigh & 0x40000000);
		x = b;
	पूर्ण
#अगर_घोषित PARANOID
	अन्यथा अणु
		संकेतling = 0;
		EXCEPTION(EX_INTERNAL | 0x113);
		x = &CONST_QNaN;
	पूर्ण
#पूर्ण_अगर /* PARANOID */

	अगर ((!संकेतling) || (control_word & CW_Invalid)) अणु
		अगर (!x)
			x = b;

		अगर (!(x->sigh & 0x80000000))	/* pseuकरो-NaN ? */
			x = &CONST_QNaN;

		FPU_copy_to_regi(x, TAG_Special, deststnr);

		अगर (!संकेतling)
			वापस TAG_Special;

		/* ensure a Quiet NaN */
		dest->sigh |= 0x40000000;
	पूर्ण

	EXCEPTION(EX_Invalid);

	वापस (!(control_word & CW_Invalid) ? FPU_Exception : 0) | TAG_Special;
पूर्ण

/* Invalid arith operation on Valid रेजिस्टरs */
/* Returns < 0 अगर the exception is unmasked */
यंत्रlinkage __visible पूर्णांक arith_invalid(पूर्णांक deststnr)
अणु

	EXCEPTION(EX_Invalid);

	अगर (control_word & CW_Invalid) अणु
		/* The masked response */
		FPU_copy_to_regi(&CONST_QNaN, TAG_Special, deststnr);
	पूर्ण

	वापस (!(control_word & CW_Invalid) ? FPU_Exception : 0) | TAG_Valid;

पूर्ण

/* Divide a finite number by zero */
यंत्रlinkage __visible पूर्णांक FPU_भागide_by_zero(पूर्णांक deststnr, u_अक्षर sign)
अणु
	FPU_REG *dest = &st(deststnr);
	पूर्णांक tag = TAG_Valid;

	अगर (control_word & CW_ZeroDiv) अणु
		/* The masked response */
		FPU_copy_to_regi(&CONST_INF, TAG_Special, deststnr);
		setsign(dest, sign);
		tag = TAG_Special;
	पूर्ण

	EXCEPTION(EX_ZeroDiv);

	वापस (!(control_word & CW_ZeroDiv) ? FPU_Exception : 0) | tag;

पूर्ण

/* This may be called often, so keep it lean */
पूर्णांक set_precision_flag(पूर्णांक flags)
अणु
	अगर (control_word & CW_Precision) अणु
		partial_status &= ~(SW_C1 & flags);
		partial_status |= flags;	/* The masked response */
		वापस 0;
	पूर्ण अन्यथा अणु
		EXCEPTION(flags);
		वापस 1;
	पूर्ण
पूर्ण

/* This may be called often, so keep it lean */
यंत्रlinkage __visible व्योम set_precision_flag_up(व्योम)
अणु
	अगर (control_word & CW_Precision)
		partial_status |= (SW_Precision | SW_C1);	/* The masked response */
	अन्यथा
		EXCEPTION(EX_Precision | SW_C1);
पूर्ण

/* This may be called often, so keep it lean */
यंत्रlinkage __visible व्योम set_precision_flag_करोwn(व्योम)
अणु
	अगर (control_word & CW_Precision) अणु	/* The masked response */
		partial_status &= ~SW_C1;
		partial_status |= SW_Precision;
	पूर्ण अन्यथा
		EXCEPTION(EX_Precision);
पूर्ण

यंत्रlinkage __visible पूर्णांक denormal_opeअक्रम(व्योम)
अणु
	अगर (control_word & CW_Denormal) अणु	/* The masked response */
		partial_status |= SW_Denorm_Op;
		वापस TAG_Special;
	पूर्ण अन्यथा अणु
		EXCEPTION(EX_Denormal);
		वापस TAG_Special | FPU_Exception;
	पूर्ण
पूर्ण

यंत्रlinkage __visible पूर्णांक arith_overflow(FPU_REG *dest)
अणु
	पूर्णांक tag = TAG_Valid;

	अगर (control_word & CW_Overflow) अणु
		/* The masked response */
/* ###### The response here depends upon the rounding mode */
		reg_copy(&CONST_INF, dest);
		tag = TAG_Special;
	पूर्ण अन्यथा अणु
		/* Subtract the magic number from the exponent */
		addexponent(dest, (-3 * (1 << 13)));
	पूर्ण

	EXCEPTION(EX_Overflow);
	अगर (control_word & CW_Overflow) अणु
		/* The overflow exception is masked. */
		/* By definition, precision is lost.
		   The roundup bit (C1) is also set because we have
		   "rounded" upwards to Infinity. */
		EXCEPTION(EX_Precision | SW_C1);
		वापस tag;
	पूर्ण

	वापस tag;

पूर्ण

यंत्रlinkage __visible पूर्णांक arith_underflow(FPU_REG *dest)
अणु
	पूर्णांक tag = TAG_Valid;

	अगर (control_word & CW_Underflow) अणु
		/* The masked response */
		अगर (exponent16(dest) <= EXP_UNDER - 63) अणु
			reg_copy(&CONST_Z, dest);
			partial_status &= ~SW_C1;	/* Round करोwn. */
			tag = TAG_Zero;
		पूर्ण अन्यथा अणु
			stdexp(dest);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Add the magic number to the exponent. */
		addexponent(dest, (3 * (1 << 13)) + EXTENDED_Ebias);
	पूर्ण

	EXCEPTION(EX_Underflow);
	अगर (control_word & CW_Underflow) अणु
		/* The underflow exception is masked. */
		EXCEPTION(EX_Precision);
		वापस tag;
	पूर्ण

	वापस tag;

पूर्ण

व्योम FPU_stack_overflow(व्योम)
अणु

	अगर (control_word & CW_Invalid) अणु
		/* The masked response */
		top--;
		FPU_copy_to_reg0(&CONST_QNaN, TAG_Special);
	पूर्ण

	EXCEPTION(EX_StackOver);

	वापस;

पूर्ण

व्योम FPU_stack_underflow(व्योम)
अणु

	अगर (control_word & CW_Invalid) अणु
		/* The masked response */
		FPU_copy_to_reg0(&CONST_QNaN, TAG_Special);
	पूर्ण

	EXCEPTION(EX_StackUnder);

	वापस;

पूर्ण

व्योम FPU_stack_underflow_i(पूर्णांक i)
अणु

	अगर (control_word & CW_Invalid) अणु
		/* The masked response */
		FPU_copy_to_regi(&CONST_QNaN, TAG_Special, i);
	पूर्ण

	EXCEPTION(EX_StackUnder);

	वापस;

पूर्ण

व्योम FPU_stack_underflow_pop(पूर्णांक i)
अणु

	अगर (control_word & CW_Invalid) अणु
		/* The masked response */
		FPU_copy_to_regi(&CONST_QNaN, TAG_Special, i);
		FPU_pop();
	पूर्ण

	EXCEPTION(EX_StackUnder);

	वापस;

पूर्ण
