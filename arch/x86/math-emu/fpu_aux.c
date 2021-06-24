<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*---------------------------------------------------------------------------+
 |  fpu_aux.c                                                                |
 |                                                                           |
 | Code to implement some of the FPU auxiliary inकाष्ठाions.                 |
 |                                                                           |
 | Copyright (C) 1992,1993,1994,1997                                         |
 |                  W. Metzenthen, 22 Parker St, Ormond, Vic 3163, Australia |
 |                  E-mail   billm@suburbia.net                              |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#समावेश "fpu_system.h"
#समावेश "exception.h"
#समावेश "fpu_emu.h"
#समावेश "status_w.h"
#समावेश "control_w.h"

अटल व्योम fnop(व्योम)
अणु
पूर्ण

अटल व्योम fclex(व्योम)
अणु
	partial_status &=
	    ~(SW_Backward | SW_Summary | SW_Stack_Fault | SW_Precision |
	      SW_Underflow | SW_Overflow | SW_Zero_Div | SW_Denorm_Op |
	      SW_Invalid);
	no_ip_update = 1;
पूर्ण

/* Needs to be बाह्यally visible */
व्योम fpstate_init_soft(काष्ठा swregs_state *soft)
अणु
	काष्ठा address *oaddr, *iaddr;
	स_रखो(soft, 0, माप(*soft));
	soft->cwd = 0x037f;
	soft->swd = 0;
	soft->ftop = 0;	/* We करोn't keep top in the status word पूर्णांकernally. */
	soft->twd = 0xffff;
	/* The behaviour is dअगरferent from that detailed in
	   Section 15.1.6 of the Intel manual */
	oaddr = (काष्ठा address *)&soft->foo;
	oaddr->offset = 0;
	oaddr->selector = 0;
	iaddr = (काष्ठा address *)&soft->fip;
	iaddr->offset = 0;
	iaddr->selector = 0;
	iaddr->opcode = 0;
	soft->no_update = 1;
पूर्ण

व्योम finit(व्योम)
अणु
	fpstate_init_soft(&current->thपढ़ो.fpu.state.soft);
पूर्ण

/*
 * These are nops on the i387..
 */
#घोषणा feni fnop
#घोषणा fdisi fnop
#घोषणा fsetpm fnop

अटल FUNC स्थिर finit_table[] = अणु
	feni, fdisi, fclex, finit,
	fsetpm, FPU_illegal, FPU_illegal, FPU_illegal
पूर्ण;

व्योम finit_(व्योम)
अणु
	(finit_table[FPU_rm]) ();
पूर्ण

अटल व्योम fstsw_ax(व्योम)
अणु
	*(लघु *)&FPU_EAX = status_word();
	no_ip_update = 1;
पूर्ण

अटल FUNC स्थिर fstsw_table[] = अणु
	fstsw_ax, FPU_illegal, FPU_illegal, FPU_illegal,
	FPU_illegal, FPU_illegal, FPU_illegal, FPU_illegal
पूर्ण;

व्योम fstsw_(व्योम)
अणु
	(fstsw_table[FPU_rm]) ();
पूर्ण

अटल FUNC स्थिर fp_nop_table[] = अणु
	fnop, FPU_illegal, FPU_illegal, FPU_illegal,
	FPU_illegal, FPU_illegal, FPU_illegal, FPU_illegal
पूर्ण;

व्योम fp_nop(व्योम)
अणु
	(fp_nop_table[FPU_rm]) ();
पूर्ण

व्योम fld_i_(व्योम)
अणु
	FPU_REG *st_new_ptr;
	पूर्णांक i;
	u_अक्षर tag;

	अगर (STACK_OVERFLOW) अणु
		FPU_stack_overflow();
		वापस;
	पूर्ण

	/* fld st(i) */
	i = FPU_rm;
	अगर (NOT_EMPTY(i)) अणु
		reg_copy(&st(i), st_new_ptr);
		tag = FPU_gettagi(i);
		push();
		FPU_settag0(tag);
	पूर्ण अन्यथा अणु
		अगर (control_word & CW_Invalid) अणु
			/* The masked response */
			FPU_stack_underflow();
		पूर्ण अन्यथा
			EXCEPTION(EX_StackUnder);
	पूर्ण

पूर्ण

व्योम fxch_i(व्योम)
अणु
	/* fxch st(i) */
	FPU_REG t;
	पूर्णांक i = FPU_rm;
	FPU_REG *st0_ptr = &st(0), *sti_ptr = &st(i);
	दीर्घ tag_word = fpu_tag_word;
	पूर्णांक regnr = top & 7, regnri = ((regnr + i) & 7);
	u_अक्षर st0_tag = (tag_word >> (regnr * 2)) & 3;
	u_अक्षर sti_tag = (tag_word >> (regnri * 2)) & 3;

	अगर (st0_tag == TAG_Empty) अणु
		अगर (sti_tag == TAG_Empty) अणु
			FPU_stack_underflow();
			FPU_stack_underflow_i(i);
			वापस;
		पूर्ण
		अगर (control_word & CW_Invalid) अणु
			/* Masked response */
			FPU_copy_to_reg0(sti_ptr, sti_tag);
		पूर्ण
		FPU_stack_underflow_i(i);
		वापस;
	पूर्ण
	अगर (sti_tag == TAG_Empty) अणु
		अगर (control_word & CW_Invalid) अणु
			/* Masked response */
			FPU_copy_to_regi(st0_ptr, st0_tag, i);
		पूर्ण
		FPU_stack_underflow();
		वापस;
	पूर्ण
	clear_C1();

	reg_copy(st0_ptr, &t);
	reg_copy(sti_ptr, st0_ptr);
	reg_copy(&t, sti_ptr);

	tag_word &= ~(3 << (regnr * 2)) & ~(3 << (regnri * 2));
	tag_word |= (sti_tag << (regnr * 2)) | (st0_tag << (regnri * 2));
	fpu_tag_word = tag_word;
पूर्ण

अटल व्योम fcmovCC(व्योम)
अणु
	/* fcmovCC st(i) */
	पूर्णांक i = FPU_rm;
	FPU_REG *st0_ptr = &st(0);
	FPU_REG *sti_ptr = &st(i);
	दीर्घ tag_word = fpu_tag_word;
	पूर्णांक regnr = top & 7;
	पूर्णांक regnri = (top + i) & 7;
	u_अक्षर sti_tag = (tag_word >> (regnri * 2)) & 3;

	अगर (sti_tag == TAG_Empty) अणु
		FPU_stack_underflow();
		clear_C1();
		वापस;
	पूर्ण
	reg_copy(sti_ptr, st0_ptr);
	tag_word &= ~(3 << (regnr * 2));
	tag_word |= (sti_tag << (regnr * 2));
	fpu_tag_word = tag_word;
पूर्ण

व्योम fcmovb(व्योम)
अणु
	अगर (FPU_EFLAGS & X86_EFLAGS_CF)
		fcmovCC();
पूर्ण

व्योम fcmove(व्योम)
अणु
	अगर (FPU_EFLAGS & X86_EFLAGS_ZF)
		fcmovCC();
पूर्ण

व्योम fcmovbe(व्योम)
अणु
	अगर (FPU_EFLAGS & (X86_EFLAGS_CF|X86_EFLAGS_ZF))
		fcmovCC();
पूर्ण

व्योम fcmovu(व्योम)
अणु
	अगर (FPU_EFLAGS & X86_EFLAGS_PF)
		fcmovCC();
पूर्ण

व्योम fcmovnb(व्योम)
अणु
	अगर (!(FPU_EFLAGS & X86_EFLAGS_CF))
		fcmovCC();
पूर्ण

व्योम fcmovne(व्योम)
अणु
	अगर (!(FPU_EFLAGS & X86_EFLAGS_ZF))
		fcmovCC();
पूर्ण

व्योम fcmovnbe(व्योम)
अणु
	अगर (!(FPU_EFLAGS & (X86_EFLAGS_CF|X86_EFLAGS_ZF)))
		fcmovCC();
पूर्ण

व्योम fcmovnu(व्योम)
अणु
	अगर (!(FPU_EFLAGS & X86_EFLAGS_PF))
		fcmovCC();
पूर्ण

व्योम fमुक्त_(व्योम)
अणु
	/* fमुक्त st(i) */
	FPU_settagi(FPU_rm, TAG_Empty);
पूर्ण

व्योम fमुक्तp(व्योम)
अणु
	/* fमुक्त st(i) + pop - unofficial code */
	FPU_settagi(FPU_rm, TAG_Empty);
	FPU_pop();
पूर्ण

व्योम fst_i_(व्योम)
अणु
	/* fst st(i) */
	FPU_copy_to_regi(&st(0), FPU_gettag0(), FPU_rm);
पूर्ण

व्योम fstp_i(व्योम)
अणु
	/* fstp st(i) */
	FPU_copy_to_regi(&st(0), FPU_gettag0(), FPU_rm);
	FPU_pop();
पूर्ण
