<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Single-step support.
 *
 * Copyright (C) 2004 Paul Mackerras <paulus@au.ibm.com>, IBM
 */
#समावेश <linux/kernel.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/prefetch.h>
#समावेश <यंत्र/sstep.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cpu_has_feature.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/disassemble.h>

बाह्य अक्षर प्रणाली_call_common[];
बाह्य अक्षर प्रणाली_call_vectored_emulate[];

#अगर_घोषित CONFIG_PPC64
/* Bits in SRR1 that are copied from MSR */
#घोषणा MSR_MASK	0xffffffff87c0ffffUL
#अन्यथा
#घोषणा MSR_MASK	0x87c0ffff
#पूर्ण_अगर

/* Bits in XER */
#घोषणा XER_SO		0x80000000U
#घोषणा XER_OV		0x40000000U
#घोषणा XER_CA		0x20000000U
#घोषणा XER_OV32	0x00080000U
#घोषणा XER_CA32	0x00040000U

#अगर_घोषित CONFIG_VSX
#घोषणा VSX_REGISTER_XTP(rd)   ((((rd) & 1) << 5) | ((rd) & 0xfe))
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_FPU
/*
 * Functions in ldstfp.S
 */
बाह्य व्योम get_fpr(पूर्णांक rn, द्विगुन *p);
बाह्य व्योम put_fpr(पूर्णांक rn, स्थिर द्विगुन *p);
बाह्य व्योम get_vr(पूर्णांक rn, __vector128 *p);
बाह्य व्योम put_vr(पूर्णांक rn, __vector128 *p);
बाह्य व्योम load_vsrn(पूर्णांक vsr, स्थिर व्योम *p);
बाह्य व्योम store_vsrn(पूर्णांक vsr, व्योम *p);
बाह्य व्योम conv_sp_to_dp(स्थिर भग्न *sp, द्विगुन *dp);
बाह्य व्योम conv_dp_to_sp(स्थिर द्विगुन *dp, भग्न *sp);
#पूर्ण_अगर

#अगर_घोषित __घातerpc64__
/*
 * Functions in quad.S
 */
बाह्य पूर्णांक करो_lq(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ *regs);
बाह्य पूर्णांक करो_stq(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ val0, अचिन्हित दीर्घ val1);
बाह्य पूर्णांक करो_lqarx(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ *regs);
बाह्य पूर्णांक करो_stqcx(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ val0, अचिन्हित दीर्घ val1,
		    अचिन्हित पूर्णांक *crp);
#पूर्ण_अगर

#अगर_घोषित __LITTLE_ENDIAN__
#घोषणा IS_LE	1
#घोषणा IS_BE	0
#अन्यथा
#घोषणा IS_LE	0
#घोषणा IS_BE	1
#पूर्ण_अगर

/*
 * Emulate the truncation of 64 bit values in 32-bit mode.
 */
अटल nokprobe_अंतरभूत अचिन्हित दीर्घ truncate_अगर_32bit(अचिन्हित दीर्घ msr,
							अचिन्हित दीर्घ val)
अणु
#अगर_घोषित __घातerpc64__
	अगर ((msr & MSR_64BIT) == 0)
		val &= 0xffffffffUL;
#पूर्ण_अगर
	वापस val;
पूर्ण

/*
 * Determine whether a conditional branch inकाष्ठाion would branch.
 */
अटल nokprobe_अंतरभूत पूर्णांक branch_taken(अचिन्हित पूर्णांक instr,
					स्थिर काष्ठा pt_regs *regs,
					काष्ठा inकाष्ठाion_op *op)
अणु
	अचिन्हित पूर्णांक bo = (instr >> 21) & 0x1f;
	अचिन्हित पूर्णांक bi;

	अगर ((bo & 4) == 0) अणु
		/* decrement counter */
		op->type |= DECCTR;
		अगर (((bo >> 1) & 1) ^ (regs->ctr == 1))
			वापस 0;
	पूर्ण
	अगर ((bo & 0x10) == 0) अणु
		/* check bit from CR */
		bi = (instr >> 16) & 0x1f;
		अगर (((regs->ccr >> (31 - bi)) & 1) != ((bo >> 3) & 1))
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल nokprobe_अंतरभूत दीर्घ address_ok(काष्ठा pt_regs *regs,
				       अचिन्हित दीर्घ ea, पूर्णांक nb)
अणु
	अगर (!user_mode(regs))
		वापस 1;
	अगर (__access_ok(ea, nb))
		वापस 1;
	अगर (__access_ok(ea, 1))
		/* Access overlaps the end of the user region */
		regs->dar = TASK_SIZE_MAX - 1;
	अन्यथा
		regs->dar = ea;
	वापस 0;
पूर्ण

/*
 * Calculate effective address क्रम a D-क्रमm inकाष्ठाion
 */
अटल nokprobe_अंतरभूत अचिन्हित दीर्घ dक्रमm_ea(अचिन्हित पूर्णांक instr,
					      स्थिर काष्ठा pt_regs *regs)
अणु
	पूर्णांक ra;
	अचिन्हित दीर्घ ea;

	ra = (instr >> 16) & 0x1f;
	ea = (चिन्हित लघु) instr;		/* sign-extend */
	अगर (ra)
		ea += regs->gpr[ra];

	वापस ea;
पूर्ण

#अगर_घोषित __घातerpc64__
/*
 * Calculate effective address क्रम a DS-क्रमm inकाष्ठाion
 */
अटल nokprobe_अंतरभूत अचिन्हित दीर्घ dsक्रमm_ea(अचिन्हित पूर्णांक instr,
					       स्थिर काष्ठा pt_regs *regs)
अणु
	पूर्णांक ra;
	अचिन्हित दीर्घ ea;

	ra = (instr >> 16) & 0x1f;
	ea = (चिन्हित लघु) (instr & ~3);	/* sign-extend */
	अगर (ra)
		ea += regs->gpr[ra];

	वापस ea;
पूर्ण

/*
 * Calculate effective address क्रम a DQ-क्रमm inकाष्ठाion
 */
अटल nokprobe_अंतरभूत अचिन्हित दीर्घ dqक्रमm_ea(अचिन्हित पूर्णांक instr,
					       स्थिर काष्ठा pt_regs *regs)
अणु
	पूर्णांक ra;
	अचिन्हित दीर्घ ea;

	ra = (instr >> 16) & 0x1f;
	ea = (चिन्हित लघु) (instr & ~0xf);	/* sign-extend */
	अगर (ra)
		ea += regs->gpr[ra];

	वापस ea;
पूर्ण
#पूर्ण_अगर /* __घातerpc64 */

/*
 * Calculate effective address क्रम an X-क्रमm inकाष्ठाion
 */
अटल nokprobe_अंतरभूत अचिन्हित दीर्घ xक्रमm_ea(अचिन्हित पूर्णांक instr,
					      स्थिर काष्ठा pt_regs *regs)
अणु
	पूर्णांक ra, rb;
	अचिन्हित दीर्घ ea;

	ra = (instr >> 16) & 0x1f;
	rb = (instr >> 11) & 0x1f;
	ea = regs->gpr[rb];
	अगर (ra)
		ea += regs->gpr[ra];

	वापस ea;
पूर्ण

/*
 * Calculate effective address क्रम a MLS:D-क्रमm / 8LS:D-क्रमm
 * prefixed inकाष्ठाion
 */
अटल nokprobe_अंतरभूत अचिन्हित दीर्घ mlsd_8lsd_ea(अचिन्हित पूर्णांक instr,
						  अचिन्हित पूर्णांक suffix,
						  स्थिर काष्ठा pt_regs *regs)
अणु
	पूर्णांक ra, prefix_r;
	अचिन्हित पूर्णांक  dd;
	अचिन्हित दीर्घ ea, d0, d1, d;

	prefix_r = GET_PREFIX_R(instr);
	ra = GET_PREFIX_RA(suffix);

	d0 = instr & 0x3ffff;
	d1 = suffix & 0xffff;
	d = (d0 << 16) | d1;

	/*
	 * sign extend a 34 bit number
	 */
	dd = (अचिन्हित पूर्णांक)(d >> 2);
	ea = (चिन्हित पूर्णांक)dd;
	ea = (ea << 2) | (d & 0x3);

	अगर (!prefix_r && ra)
		ea += regs->gpr[ra];
	अन्यथा अगर (!prefix_r && !ra)
		; /* Leave ea as is */
	अन्यथा अगर (prefix_r)
		ea += regs->nip;

	/*
	 * (prefix_r && ra) is an invalid क्रमm. Should alपढ़ोy be
	 * checked क्रम by caller!
	 */

	वापस ea;
पूर्ण

/*
 * Return the largest घातer of 2, not greater than माप(अचिन्हित दीर्घ),
 * such that x is a multiple of it.
 */
अटल nokprobe_अंतरभूत अचिन्हित दीर्घ max_align(अचिन्हित दीर्घ x)
अणु
	x |= माप(अचिन्हित दीर्घ);
	वापस x & -x;		/* isolates righपंचांगost bit */
पूर्ण

अटल nokprobe_अंतरभूत अचिन्हित दीर्घ byterev_2(अचिन्हित दीर्घ x)
अणु
	वापस ((x >> 8) & 0xff) | ((x & 0xff) << 8);
पूर्ण

अटल nokprobe_अंतरभूत अचिन्हित दीर्घ byterev_4(अचिन्हित दीर्घ x)
अणु
	वापस ((x >> 24) & 0xff) | ((x >> 8) & 0xff00) |
		((x & 0xff00) << 8) | ((x & 0xff) << 24);
पूर्ण

#अगर_घोषित __घातerpc64__
अटल nokprobe_अंतरभूत अचिन्हित दीर्घ byterev_8(अचिन्हित दीर्घ x)
अणु
	वापस (byterev_4(x) << 32) | byterev_4(x >> 32);
पूर्ण
#पूर्ण_अगर

अटल nokprobe_अंतरभूत व्योम करो_byte_reverse(व्योम *ptr, पूर्णांक nb)
अणु
	चयन (nb) अणु
	हाल 2:
		*(u16 *)ptr = byterev_2(*(u16 *)ptr);
		अवरोध;
	हाल 4:
		*(u32 *)ptr = byterev_4(*(u32 *)ptr);
		अवरोध;
#अगर_घोषित __घातerpc64__
	हाल 8:
		*(अचिन्हित दीर्घ *)ptr = byterev_8(*(अचिन्हित दीर्घ *)ptr);
		अवरोध;
	हाल 16: अणु
		अचिन्हित दीर्घ *up = (अचिन्हित दीर्घ *)ptr;
		अचिन्हित दीर्घ पंचांगp;
		पंचांगp = byterev_8(up[0]);
		up[0] = byterev_8(up[1]);
		up[1] = पंचांगp;
		अवरोध;
	पूर्ण
	हाल 32: अणु
		अचिन्हित दीर्घ *up = (अचिन्हित दीर्घ *)ptr;
		अचिन्हित दीर्घ पंचांगp;

		पंचांगp = byterev_8(up[0]);
		up[0] = byterev_8(up[3]);
		up[3] = पंचांगp;
		पंचांगp = byterev_8(up[2]);
		up[2] = byterev_8(up[1]);
		up[1] = पंचांगp;
		अवरोध;
	पूर्ण

#पूर्ण_अगर
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण
पूर्ण

अटल nokprobe_अंतरभूत पूर्णांक पढ़ो_mem_aligned(अचिन्हित दीर्घ *dest,
					    अचिन्हित दीर्घ ea, पूर्णांक nb,
					    काष्ठा pt_regs *regs)
अणु
	पूर्णांक err = 0;
	अचिन्हित दीर्घ x = 0;

	चयन (nb) अणु
	हाल 1:
		err = __get_user(x, (अचिन्हित अक्षर __user *) ea);
		अवरोध;
	हाल 2:
		err = __get_user(x, (अचिन्हित लघु __user *) ea);
		अवरोध;
	हाल 4:
		err = __get_user(x, (अचिन्हित पूर्णांक __user *) ea);
		अवरोध;
#अगर_घोषित __घातerpc64__
	हाल 8:
		err = __get_user(x, (अचिन्हित दीर्घ __user *) ea);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
	अगर (!err)
		*dest = x;
	अन्यथा
		regs->dar = ea;
	वापस err;
पूर्ण

/*
 * Copy from userspace to a buffer, using the largest possible
 * aligned accesses, up to माप(दीर्घ).
 */
अटल nokprobe_अंतरभूत पूर्णांक copy_mem_in(u8 *dest, अचिन्हित दीर्घ ea, पूर्णांक nb,
				       काष्ठा pt_regs *regs)
अणु
	पूर्णांक err = 0;
	पूर्णांक c;

	क्रम (; nb > 0; nb -= c) अणु
		c = max_align(ea);
		अगर (c > nb)
			c = max_align(nb);
		चयन (c) अणु
		हाल 1:
			err = __get_user(*dest, (अचिन्हित अक्षर __user *) ea);
			अवरोध;
		हाल 2:
			err = __get_user(*(u16 *)dest,
					 (अचिन्हित लघु __user *) ea);
			अवरोध;
		हाल 4:
			err = __get_user(*(u32 *)dest,
					 (अचिन्हित पूर्णांक __user *) ea);
			अवरोध;
#अगर_घोषित __घातerpc64__
		हाल 8:
			err = __get_user(*(अचिन्हित दीर्घ *)dest,
					 (अचिन्हित दीर्घ __user *) ea);
			अवरोध;
#पूर्ण_अगर
		पूर्ण
		अगर (err) अणु
			regs->dar = ea;
			वापस err;
		पूर्ण
		dest += c;
		ea += c;
	पूर्ण
	वापस 0;
पूर्ण

अटल nokprobe_अंतरभूत पूर्णांक पढ़ो_mem_unaligned(अचिन्हित दीर्घ *dest,
					      अचिन्हित दीर्घ ea, पूर्णांक nb,
					      काष्ठा pt_regs *regs)
अणु
	जोड़ अणु
		अचिन्हित दीर्घ ul;
		u8 b[माप(अचिन्हित दीर्घ)];
	पूर्ण u;
	पूर्णांक i;
	पूर्णांक err;

	u.ul = 0;
	i = IS_BE ? माप(अचिन्हित दीर्घ) - nb : 0;
	err = copy_mem_in(&u.b[i], ea, nb, regs);
	अगर (!err)
		*dest = u.ul;
	वापस err;
पूर्ण

/*
 * Read memory at address ea क्रम nb bytes, वापस 0 क्रम success
 * or -EFAULT अगर an error occurred.  N.B. nb must be 1, 2, 4 or 8.
 * If nb < माप(दीर्घ), the result is right-justअगरied on BE प्रणालीs.
 */
अटल पूर्णांक पढ़ो_mem(अचिन्हित दीर्घ *dest, अचिन्हित दीर्घ ea, पूर्णांक nb,
			      काष्ठा pt_regs *regs)
अणु
	अगर (!address_ok(regs, ea, nb))
		वापस -EFAULT;
	अगर ((ea & (nb - 1)) == 0)
		वापस पढ़ो_mem_aligned(dest, ea, nb, regs);
	वापस पढ़ो_mem_unaligned(dest, ea, nb, regs);
पूर्ण
NOKPROBE_SYMBOL(पढ़ो_mem);

अटल nokprobe_अंतरभूत पूर्णांक ग_लिखो_mem_aligned(अचिन्हित दीर्घ val,
					     अचिन्हित दीर्घ ea, पूर्णांक nb,
					     काष्ठा pt_regs *regs)
अणु
	पूर्णांक err = 0;

	चयन (nb) अणु
	हाल 1:
		err = __put_user(val, (अचिन्हित अक्षर __user *) ea);
		अवरोध;
	हाल 2:
		err = __put_user(val, (अचिन्हित लघु __user *) ea);
		अवरोध;
	हाल 4:
		err = __put_user(val, (अचिन्हित पूर्णांक __user *) ea);
		अवरोध;
#अगर_घोषित __घातerpc64__
	हाल 8:
		err = __put_user(val, (अचिन्हित दीर्घ __user *) ea);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
	अगर (err)
		regs->dar = ea;
	वापस err;
पूर्ण

/*
 * Copy from a buffer to userspace, using the largest possible
 * aligned accesses, up to माप(दीर्घ).
 */
अटल nokprobe_अंतरभूत पूर्णांक copy_mem_out(u8 *dest, अचिन्हित दीर्घ ea, पूर्णांक nb,
					काष्ठा pt_regs *regs)
अणु
	पूर्णांक err = 0;
	पूर्णांक c;

	क्रम (; nb > 0; nb -= c) अणु
		c = max_align(ea);
		अगर (c > nb)
			c = max_align(nb);
		चयन (c) अणु
		हाल 1:
			err = __put_user(*dest, (अचिन्हित अक्षर __user *) ea);
			अवरोध;
		हाल 2:
			err = __put_user(*(u16 *)dest,
					 (अचिन्हित लघु __user *) ea);
			अवरोध;
		हाल 4:
			err = __put_user(*(u32 *)dest,
					 (अचिन्हित पूर्णांक __user *) ea);
			अवरोध;
#अगर_घोषित __घातerpc64__
		हाल 8:
			err = __put_user(*(अचिन्हित दीर्घ *)dest,
					 (अचिन्हित दीर्घ __user *) ea);
			अवरोध;
#पूर्ण_अगर
		पूर्ण
		अगर (err) अणु
			regs->dar = ea;
			वापस err;
		पूर्ण
		dest += c;
		ea += c;
	पूर्ण
	वापस 0;
पूर्ण

अटल nokprobe_अंतरभूत पूर्णांक ग_लिखो_mem_unaligned(अचिन्हित दीर्घ val,
					       अचिन्हित दीर्घ ea, पूर्णांक nb,
					       काष्ठा pt_regs *regs)
अणु
	जोड़ अणु
		अचिन्हित दीर्घ ul;
		u8 b[माप(अचिन्हित दीर्घ)];
	पूर्ण u;
	पूर्णांक i;

	u.ul = val;
	i = IS_BE ? माप(अचिन्हित दीर्घ) - nb : 0;
	वापस copy_mem_out(&u.b[i], ea, nb, regs);
पूर्ण

/*
 * Write memory at address ea क्रम nb bytes, वापस 0 क्रम success
 * or -EFAULT अगर an error occurred.  N.B. nb must be 1, 2, 4 or 8.
 */
अटल पूर्णांक ग_लिखो_mem(अचिन्हित दीर्घ val, अचिन्हित दीर्घ ea, पूर्णांक nb,
			       काष्ठा pt_regs *regs)
अणु
	अगर (!address_ok(regs, ea, nb))
		वापस -EFAULT;
	अगर ((ea & (nb - 1)) == 0)
		वापस ग_लिखो_mem_aligned(val, ea, nb, regs);
	वापस ग_लिखो_mem_unaligned(val, ea, nb, regs);
पूर्ण
NOKPROBE_SYMBOL(ग_लिखो_mem);

#अगर_घोषित CONFIG_PPC_FPU
/*
 * These access either the real FP रेजिस्टर or the image in the
 * thपढ़ो_काष्ठा, depending on regs->msr & MSR_FP.
 */
अटल पूर्णांक करो_fp_load(काष्ठा inकाष्ठाion_op *op, अचिन्हित दीर्घ ea,
		      काष्ठा pt_regs *regs, bool cross_endian)
अणु
	पूर्णांक err, rn, nb;
	जोड़ अणु
		पूर्णांक i;
		अचिन्हित पूर्णांक u;
		भग्न f;
		द्विगुन d[2];
		अचिन्हित दीर्घ l[2];
		u8 b[2 * माप(द्विगुन)];
	पूर्ण u;

	nb = GETSIZE(op->type);
	अगर (!address_ok(regs, ea, nb))
		वापस -EFAULT;
	rn = op->reg;
	err = copy_mem_in(u.b, ea, nb, regs);
	अगर (err)
		वापस err;
	अगर (unlikely(cross_endian)) अणु
		करो_byte_reverse(u.b, min(nb, 8));
		अगर (nb == 16)
			करो_byte_reverse(&u.b[8], 8);
	पूर्ण
	preempt_disable();
	अगर (nb == 4) अणु
		अगर (op->type & FPCONV)
			conv_sp_to_dp(&u.f, &u.d[0]);
		अन्यथा अगर (op->type & SIGNEXT)
			u.l[0] = u.i;
		अन्यथा
			u.l[0] = u.u;
	पूर्ण
	अगर (regs->msr & MSR_FP)
		put_fpr(rn, &u.d[0]);
	अन्यथा
		current->thपढ़ो.TS_FPR(rn) = u.l[0];
	अगर (nb == 16) अणु
		/* lfdp */
		rn |= 1;
		अगर (regs->msr & MSR_FP)
			put_fpr(rn, &u.d[1]);
		अन्यथा
			current->thपढ़ो.TS_FPR(rn) = u.l[1];
	पूर्ण
	preempt_enable();
	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(करो_fp_load);

अटल पूर्णांक करो_fp_store(काष्ठा inकाष्ठाion_op *op, अचिन्हित दीर्घ ea,
		       काष्ठा pt_regs *regs, bool cross_endian)
अणु
	पूर्णांक rn, nb;
	जोड़ अणु
		अचिन्हित पूर्णांक u;
		भग्न f;
		द्विगुन d[2];
		अचिन्हित दीर्घ l[2];
		u8 b[2 * माप(द्विगुन)];
	पूर्ण u;

	nb = GETSIZE(op->type);
	अगर (!address_ok(regs, ea, nb))
		वापस -EFAULT;
	rn = op->reg;
	preempt_disable();
	अगर (regs->msr & MSR_FP)
		get_fpr(rn, &u.d[0]);
	अन्यथा
		u.l[0] = current->thपढ़ो.TS_FPR(rn);
	अगर (nb == 4) अणु
		अगर (op->type & FPCONV)
			conv_dp_to_sp(&u.d[0], &u.f);
		अन्यथा
			u.u = u.l[0];
	पूर्ण
	अगर (nb == 16) अणु
		rn |= 1;
		अगर (regs->msr & MSR_FP)
			get_fpr(rn, &u.d[1]);
		अन्यथा
			u.l[1] = current->thपढ़ो.TS_FPR(rn);
	पूर्ण
	preempt_enable();
	अगर (unlikely(cross_endian)) अणु
		करो_byte_reverse(u.b, min(nb, 8));
		अगर (nb == 16)
			करो_byte_reverse(&u.b[8], 8);
	पूर्ण
	वापस copy_mem_out(u.b, ea, nb, regs);
पूर्ण
NOKPROBE_SYMBOL(करो_fp_store);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ALTIVEC
/* For Altivec/VMX, no need to worry about alignment */
अटल nokprobe_अंतरभूत पूर्णांक करो_vec_load(पूर्णांक rn, अचिन्हित दीर्घ ea,
				       पूर्णांक size, काष्ठा pt_regs *regs,
				       bool cross_endian)
अणु
	पूर्णांक err;
	जोड़ अणु
		__vector128 v;
		u8 b[माप(__vector128)];
	पूर्ण u = अणुपूर्ण;

	अगर (!address_ok(regs, ea & ~0xfUL, 16))
		वापस -EFAULT;
	/* align to multiple of size */
	ea &= ~(size - 1);
	err = copy_mem_in(&u.b[ea & 0xf], ea, size, regs);
	अगर (err)
		वापस err;
	अगर (unlikely(cross_endian))
		करो_byte_reverse(&u.b[ea & 0xf], size);
	preempt_disable();
	अगर (regs->msr & MSR_VEC)
		put_vr(rn, &u.v);
	अन्यथा
		current->thपढ़ो.vr_state.vr[rn] = u.v;
	preempt_enable();
	वापस 0;
पूर्ण

अटल nokprobe_अंतरभूत पूर्णांक करो_vec_store(पूर्णांक rn, अचिन्हित दीर्घ ea,
					पूर्णांक size, काष्ठा pt_regs *regs,
					bool cross_endian)
अणु
	जोड़ अणु
		__vector128 v;
		u8 b[माप(__vector128)];
	पूर्ण u;

	अगर (!address_ok(regs, ea & ~0xfUL, 16))
		वापस -EFAULT;
	/* align to multiple of size */
	ea &= ~(size - 1);

	preempt_disable();
	अगर (regs->msr & MSR_VEC)
		get_vr(rn, &u.v);
	अन्यथा
		u.v = current->thपढ़ो.vr_state.vr[rn];
	preempt_enable();
	अगर (unlikely(cross_endian))
		करो_byte_reverse(&u.b[ea & 0xf], size);
	वापस copy_mem_out(&u.b[ea & 0xf], ea, size, regs);
पूर्ण
#पूर्ण_अगर /* CONFIG_ALTIVEC */

#अगर_घोषित __घातerpc64__
अटल nokprobe_अंतरभूत पूर्णांक emulate_lq(काष्ठा pt_regs *regs, अचिन्हित दीर्घ ea,
				      पूर्णांक reg, bool cross_endian)
अणु
	पूर्णांक err;

	अगर (!address_ok(regs, ea, 16))
		वापस -EFAULT;
	/* अगर aligned, should be atomic */
	अगर ((ea & 0xf) == 0) अणु
		err = करो_lq(ea, &regs->gpr[reg]);
	पूर्ण अन्यथा अणु
		err = पढ़ो_mem(&regs->gpr[reg + IS_LE], ea, 8, regs);
		अगर (!err)
			err = पढ़ो_mem(&regs->gpr[reg + IS_BE], ea + 8, 8, regs);
	पूर्ण
	अगर (!err && unlikely(cross_endian))
		करो_byte_reverse(&regs->gpr[reg], 16);
	वापस err;
पूर्ण

अटल nokprobe_अंतरभूत पूर्णांक emulate_stq(काष्ठा pt_regs *regs, अचिन्हित दीर्घ ea,
				       पूर्णांक reg, bool cross_endian)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ vals[2];

	अगर (!address_ok(regs, ea, 16))
		वापस -EFAULT;
	vals[0] = regs->gpr[reg];
	vals[1] = regs->gpr[reg + 1];
	अगर (unlikely(cross_endian))
		करो_byte_reverse(vals, 16);

	/* अगर aligned, should be atomic */
	अगर ((ea & 0xf) == 0)
		वापस करो_stq(ea, vals[0], vals[1]);

	err = ग_लिखो_mem(vals[IS_LE], ea, 8, regs);
	अगर (!err)
		err = ग_लिखो_mem(vals[IS_BE], ea + 8, 8, regs);
	वापस err;
पूर्ण
#पूर्ण_अगर /* __घातerpc64 */

#अगर_घोषित CONFIG_VSX
व्योम emulate_vsx_load(काष्ठा inकाष्ठाion_op *op, जोड़ vsx_reg *reg,
		      स्थिर व्योम *mem, bool rev)
अणु
	पूर्णांक size, पढ़ो_size;
	पूर्णांक i, j;
	स्थिर अचिन्हित पूर्णांक *wp;
	स्थिर अचिन्हित लघु *hp;
	स्थिर अचिन्हित अक्षर *bp;

	size = GETSIZE(op->type);
	reg->d[0] = reg->d[1] = 0;

	चयन (op->element_size) अणु
	हाल 32:
		/* [p]lxvp[x] */
	हाल 16:
		/* whole vector; lxv[x] or lxvl[l] */
		अगर (size == 0)
			अवरोध;
		स_नकल(reg, mem, size);
		अगर (IS_LE && (op->vsx_flags & VSX_LDLEFT))
			rev = !rev;
		अगर (rev)
			करो_byte_reverse(reg, size);
		अवरोध;
	हाल 8:
		/* scalar loads, lxvd2x, lxvdsx */
		पढ़ो_size = (size >= 8) ? 8 : size;
		i = IS_LE ? 8 : 8 - पढ़ो_size;
		स_नकल(&reg->b[i], mem, पढ़ो_size);
		अगर (rev)
			करो_byte_reverse(&reg->b[i], 8);
		अगर (size < 8) अणु
			अगर (op->type & SIGNEXT) अणु
				/* size == 4 is the only हाल here */
				reg->d[IS_LE] = (चिन्हित पूर्णांक) reg->d[IS_LE];
			पूर्ण अन्यथा अगर (op->vsx_flags & VSX_FPCONV) अणु
				preempt_disable();
				conv_sp_to_dp(&reg->fp[1 + IS_LE],
					      &reg->dp[IS_LE]);
				preempt_enable();
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (size == 16) अणु
				अचिन्हित दीर्घ v = *(अचिन्हित दीर्घ *)(mem + 8);
				reg->d[IS_BE] = !rev ? v : byterev_8(v);
			पूर्ण अन्यथा अगर (op->vsx_flags & VSX_SPLAT)
				reg->d[IS_BE] = reg->d[IS_LE];
		पूर्ण
		अवरोध;
	हाल 4:
		/* lxvw4x, lxvwsx */
		wp = mem;
		क्रम (j = 0; j < size / 4; ++j) अणु
			i = IS_LE ? 3 - j : j;
			reg->w[i] = !rev ? *wp++ : byterev_4(*wp++);
		पूर्ण
		अगर (op->vsx_flags & VSX_SPLAT) अणु
			u32 val = reg->w[IS_LE ? 3 : 0];
			क्रम (; j < 4; ++j) अणु
				i = IS_LE ? 3 - j : j;
				reg->w[i] = val;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल 2:
		/* lxvh8x */
		hp = mem;
		क्रम (j = 0; j < size / 2; ++j) अणु
			i = IS_LE ? 7 - j : j;
			reg->h[i] = !rev ? *hp++ : byterev_2(*hp++);
		पूर्ण
		अवरोध;
	हाल 1:
		/* lxvb16x */
		bp = mem;
		क्रम (j = 0; j < size; ++j) अणु
			i = IS_LE ? 15 - j : j;
			reg->b[i] = *bp++;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(emulate_vsx_load);
NOKPROBE_SYMBOL(emulate_vsx_load);

व्योम emulate_vsx_store(काष्ठा inकाष्ठाion_op *op, स्थिर जोड़ vsx_reg *reg,
		       व्योम *mem, bool rev)
अणु
	पूर्णांक size, ग_लिखो_size;
	पूर्णांक i, j;
	जोड़ vsx_reg buf;
	अचिन्हित पूर्णांक *wp;
	अचिन्हित लघु *hp;
	अचिन्हित अक्षर *bp;

	size = GETSIZE(op->type);

	चयन (op->element_size) अणु
	हाल 32:
		/* [p]stxvp[x] */
		अगर (size == 0)
			अवरोध;
		अगर (rev) अणु
			/* reverse 32 bytes */
			जोड़ vsx_reg buf32[2];
			buf32[0].d[0] = byterev_8(reg[1].d[1]);
			buf32[0].d[1] = byterev_8(reg[1].d[0]);
			buf32[1].d[0] = byterev_8(reg[0].d[1]);
			buf32[1].d[1] = byterev_8(reg[0].d[0]);
			स_नकल(mem, buf32, size);
		पूर्ण अन्यथा अणु
			स_नकल(mem, reg, size);
		पूर्ण
		अवरोध;
	हाल 16:
		/* stxv, stxvx, stxvl, stxvll */
		अगर (size == 0)
			अवरोध;
		अगर (IS_LE && (op->vsx_flags & VSX_LDLEFT))
			rev = !rev;
		अगर (rev) अणु
			/* reverse 16 bytes */
			buf.d[0] = byterev_8(reg->d[1]);
			buf.d[1] = byterev_8(reg->d[0]);
			reg = &buf;
		पूर्ण
		स_नकल(mem, reg, size);
		अवरोध;
	हाल 8:
		/* scalar stores, stxvd2x */
		ग_लिखो_size = (size >= 8) ? 8 : size;
		i = IS_LE ? 8 : 8 - ग_लिखो_size;
		अगर (size < 8 && op->vsx_flags & VSX_FPCONV) अणु
			buf.d[0] = buf.d[1] = 0;
			preempt_disable();
			conv_dp_to_sp(&reg->dp[IS_LE], &buf.fp[1 + IS_LE]);
			preempt_enable();
			reg = &buf;
		पूर्ण
		स_नकल(mem, &reg->b[i], ग_लिखो_size);
		अगर (size == 16)
			स_नकल(mem + 8, &reg->d[IS_BE], 8);
		अगर (unlikely(rev)) अणु
			करो_byte_reverse(mem, ग_लिखो_size);
			अगर (size == 16)
				करो_byte_reverse(mem + 8, 8);
		पूर्ण
		अवरोध;
	हाल 4:
		/* stxvw4x */
		wp = mem;
		क्रम (j = 0; j < size / 4; ++j) अणु
			i = IS_LE ? 3 - j : j;
			*wp++ = !rev ? reg->w[i] : byterev_4(reg->w[i]);
		पूर्ण
		अवरोध;
	हाल 2:
		/* stxvh8x */
		hp = mem;
		क्रम (j = 0; j < size / 2; ++j) अणु
			i = IS_LE ? 7 - j : j;
			*hp++ = !rev ? reg->h[i] : byterev_2(reg->h[i]);
		पूर्ण
		अवरोध;
	हाल 1:
		/* stvxb16x */
		bp = mem;
		क्रम (j = 0; j < size; ++j) अणु
			i = IS_LE ? 15 - j : j;
			*bp++ = reg->b[i];
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(emulate_vsx_store);
NOKPROBE_SYMBOL(emulate_vsx_store);

अटल nokprobe_अंतरभूत पूर्णांक करो_vsx_load(काष्ठा inकाष्ठाion_op *op,
				       अचिन्हित दीर्घ ea, काष्ठा pt_regs *regs,
				       bool cross_endian)
अणु
	पूर्णांक reg = op->reg;
	पूर्णांक i, j, nr_vsx_regs;
	u8 mem[32];
	जोड़ vsx_reg buf[2];
	पूर्णांक size = GETSIZE(op->type);

	अगर (!address_ok(regs, ea, size) || copy_mem_in(mem, ea, size, regs))
		वापस -EFAULT;

	nr_vsx_regs = max(1ul, size / माप(__vector128));
	emulate_vsx_load(op, buf, mem, cross_endian);
	preempt_disable();
	अगर (reg < 32) अणु
		/* FP regs + extensions */
		अगर (regs->msr & MSR_FP) अणु
			क्रम (i = 0; i < nr_vsx_regs; i++) अणु
				j = IS_LE ? nr_vsx_regs - i - 1 : i;
				load_vsrn(reg + i, &buf[j].v);
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < nr_vsx_regs; i++) अणु
				j = IS_LE ? nr_vsx_regs - i - 1 : i;
				current->thपढ़ो.fp_state.fpr[reg + i][0] = buf[j].d[0];
				current->thपढ़ो.fp_state.fpr[reg + i][1] = buf[j].d[1];
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (regs->msr & MSR_VEC) अणु
			क्रम (i = 0; i < nr_vsx_regs; i++) अणु
				j = IS_LE ? nr_vsx_regs - i - 1 : i;
				load_vsrn(reg + i, &buf[j].v);
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < nr_vsx_regs; i++) अणु
				j = IS_LE ? nr_vsx_regs - i - 1 : i;
				current->thपढ़ो.vr_state.vr[reg - 32 + i] = buf[j].v;
			पूर्ण
		पूर्ण
	पूर्ण
	preempt_enable();
	वापस 0;
पूर्ण

अटल nokprobe_अंतरभूत पूर्णांक करो_vsx_store(काष्ठा inकाष्ठाion_op *op,
					अचिन्हित दीर्घ ea, काष्ठा pt_regs *regs,
					bool cross_endian)
अणु
	पूर्णांक reg = op->reg;
	पूर्णांक i, j, nr_vsx_regs;
	u8 mem[32];
	जोड़ vsx_reg buf[2];
	पूर्णांक size = GETSIZE(op->type);

	अगर (!address_ok(regs, ea, size))
		वापस -EFAULT;

	nr_vsx_regs = max(1ul, size / माप(__vector128));
	preempt_disable();
	अगर (reg < 32) अणु
		/* FP regs + extensions */
		अगर (regs->msr & MSR_FP) अणु
			क्रम (i = 0; i < nr_vsx_regs; i++) अणु
				j = IS_LE ? nr_vsx_regs - i - 1 : i;
				store_vsrn(reg + i, &buf[j].v);
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < nr_vsx_regs; i++) अणु
				j = IS_LE ? nr_vsx_regs - i - 1 : i;
				buf[j].d[0] = current->thपढ़ो.fp_state.fpr[reg + i][0];
				buf[j].d[1] = current->thपढ़ो.fp_state.fpr[reg + i][1];
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (regs->msr & MSR_VEC) अणु
			क्रम (i = 0; i < nr_vsx_regs; i++) अणु
				j = IS_LE ? nr_vsx_regs - i - 1 : i;
				store_vsrn(reg + i, &buf[j].v);
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < nr_vsx_regs; i++) अणु
				j = IS_LE ? nr_vsx_regs - i - 1 : i;
				buf[j].v = current->thपढ़ो.vr_state.vr[reg - 32 + i];
			पूर्ण
		पूर्ण
	पूर्ण
	preempt_enable();
	emulate_vsx_store(op, buf, mem, cross_endian);
	वापस  copy_mem_out(mem, ea, size, regs);
पूर्ण
#पूर्ण_अगर /* CONFIG_VSX */

पूर्णांक emulate_dcbz(अचिन्हित दीर्घ ea, काष्ठा pt_regs *regs)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ i, size;

#अगर_घोषित __घातerpc64__
	size = ppc64_caches.l1d.block_size;
	अगर (!(regs->msr & MSR_64BIT))
		ea &= 0xffffffffUL;
#अन्यथा
	size = L1_CACHE_BYTES;
#पूर्ण_अगर
	ea &= ~(size - 1);
	अगर (!address_ok(regs, ea, size))
		वापस -EFAULT;
	क्रम (i = 0; i < size; i += माप(दीर्घ)) अणु
		err = __put_user(0, (अचिन्हित दीर्घ __user *) (ea + i));
		अगर (err) अणु
			regs->dar = ea;
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(emulate_dcbz);

#घोषणा __put_user_यंत्रx(x, addr, err, op, cr)		\
	__यंत्र__ __अस्थिर__(				\
		"1:	" op " %2,0,%3\n"		\
		"	mfcr	%1\n"			\
		"2:\n"					\
		".section .fixup,\"ax\"\n"		\
		"3:	li	%0,%4\n"		\
		"	b	2b\n"			\
		".previous\n"				\
		EX_TABLE(1b, 3b)			\
		: "=r" (err), "=r" (cr)			\
		: "r" (x), "r" (addr), "i" (-EFAULT), "0" (err))

#घोषणा __get_user_यंत्रx(x, addr, err, op)		\
	__यंत्र__ __अस्थिर__(				\
		"1:	"op" %1,0,%2\n"			\
		"2:\n"					\
		".section .fixup,\"ax\"\n"		\
		"3:	li	%0,%3\n"		\
		"	b	2b\n"			\
		".previous\n"				\
		EX_TABLE(1b, 3b)			\
		: "=r" (err), "=r" (x)			\
		: "r" (addr), "i" (-EFAULT), "0" (err))

#घोषणा __cacheop_user_यंत्रx(addr, err, op)		\
	__यंत्र__ __अस्थिर__(				\
		"1:	"op" 0,%1\n"			\
		"2:\n"					\
		".section .fixup,\"ax\"\n"		\
		"3:	li	%0,%3\n"		\
		"	b	2b\n"			\
		".previous\n"				\
		EX_TABLE(1b, 3b)			\
		: "=r" (err)				\
		: "r" (addr), "i" (-EFAULT), "0" (err))

अटल nokprobe_अंतरभूत व्योम set_cr0(स्थिर काष्ठा pt_regs *regs,
				    काष्ठा inकाष्ठाion_op *op)
अणु
	दीर्घ val = op->val;

	op->type |= SETCC;
	op->ccval = (regs->ccr & 0x0fffffff) | ((regs->xer >> 3) & 0x10000000);
#अगर_घोषित __घातerpc64__
	अगर (!(regs->msr & MSR_64BIT))
		val = (पूर्णांक) val;
#पूर्ण_अगर
	अगर (val < 0)
		op->ccval |= 0x80000000;
	अन्यथा अगर (val > 0)
		op->ccval |= 0x40000000;
	अन्यथा
		op->ccval |= 0x20000000;
पूर्ण

अटल nokprobe_अंतरभूत व्योम set_ca32(काष्ठा inकाष्ठाion_op *op, bool val)
अणु
	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		अगर (val)
			op->xerval |= XER_CA32;
		अन्यथा
			op->xerval &= ~XER_CA32;
	पूर्ण
पूर्ण

अटल nokprobe_अंतरभूत व्योम add_with_carry(स्थिर काष्ठा pt_regs *regs,
				     काष्ठा inकाष्ठाion_op *op, पूर्णांक rd,
				     अचिन्हित दीर्घ val1, अचिन्हित दीर्घ val2,
				     अचिन्हित दीर्घ carry_in)
अणु
	अचिन्हित दीर्घ val = val1 + val2;

	अगर (carry_in)
		++val;
	op->type = COMPUTE + SETREG + SETXER;
	op->reg = rd;
	op->val = val;
#अगर_घोषित __घातerpc64__
	अगर (!(regs->msr & MSR_64BIT)) अणु
		val = (अचिन्हित पूर्णांक) val;
		val1 = (अचिन्हित पूर्णांक) val1;
	पूर्ण
#पूर्ण_अगर
	op->xerval = regs->xer;
	अगर (val < val1 || (carry_in && val == val1))
		op->xerval |= XER_CA;
	अन्यथा
		op->xerval &= ~XER_CA;

	set_ca32(op, (अचिन्हित पूर्णांक)val < (अचिन्हित पूर्णांक)val1 ||
			(carry_in && (अचिन्हित पूर्णांक)val == (अचिन्हित पूर्णांक)val1));
पूर्ण

अटल nokprobe_अंतरभूत व्योम करो_cmp_चिन्हित(स्थिर काष्ठा pt_regs *regs,
					  काष्ठा inकाष्ठाion_op *op,
					  दीर्घ v1, दीर्घ v2, पूर्णांक crfld)
अणु
	अचिन्हित पूर्णांक crval, shअगरt;

	op->type = COMPUTE + SETCC;
	crval = (regs->xer >> 31) & 1;		/* get SO bit */
	अगर (v1 < v2)
		crval |= 8;
	अन्यथा अगर (v1 > v2)
		crval |= 4;
	अन्यथा
		crval |= 2;
	shअगरt = (7 - crfld) * 4;
	op->ccval = (regs->ccr & ~(0xf << shअगरt)) | (crval << shअगरt);
पूर्ण

अटल nokprobe_अंतरभूत व्योम करो_cmp_अचिन्हित(स्थिर काष्ठा pt_regs *regs,
					    काष्ठा inकाष्ठाion_op *op,
					    अचिन्हित दीर्घ v1,
					    अचिन्हित दीर्घ v2, पूर्णांक crfld)
अणु
	अचिन्हित पूर्णांक crval, shअगरt;

	op->type = COMPUTE + SETCC;
	crval = (regs->xer >> 31) & 1;		/* get SO bit */
	अगर (v1 < v2)
		crval |= 8;
	अन्यथा अगर (v1 > v2)
		crval |= 4;
	अन्यथा
		crval |= 2;
	shअगरt = (7 - crfld) * 4;
	op->ccval = (regs->ccr & ~(0xf << shअगरt)) | (crval << shअगरt);
पूर्ण

अटल nokprobe_अंतरभूत व्योम करो_cmpb(स्थिर काष्ठा pt_regs *regs,
				    काष्ठा inकाष्ठाion_op *op,
				    अचिन्हित दीर्घ v1, अचिन्हित दीर्घ v2)
अणु
	अचिन्हित दीर्घ दीर्घ out_val, mask;
	पूर्णांक i;

	out_val = 0;
	क्रम (i = 0; i < 8; i++) अणु
		mask = 0xffUL << (i * 8);
		अगर ((v1 & mask) == (v2 & mask))
			out_val |= mask;
	पूर्ण
	op->val = out_val;
पूर्ण

/*
 * The size parameter is used to adjust the equivalent popcnt inकाष्ठाion.
 * popcntb = 8, popcntw = 32, popcntd = 64
 */
अटल nokprobe_अंतरभूत व्योम करो_popcnt(स्थिर काष्ठा pt_regs *regs,
				      काष्ठा inकाष्ठाion_op *op,
				      अचिन्हित दीर्घ v1, पूर्णांक size)
अणु
	अचिन्हित दीर्घ दीर्घ out = v1;

	out -= (out >> 1) & 0x5555555555555555ULL;
	out = (0x3333333333333333ULL & out) +
	      (0x3333333333333333ULL & (out >> 2));
	out = (out + (out >> 4)) & 0x0f0f0f0f0f0f0f0fULL;

	अगर (size == 8) अणु	/* popcntb */
		op->val = out;
		वापस;
	पूर्ण
	out += out >> 8;
	out += out >> 16;
	अगर (size == 32) अणु	/* popcntw */
		op->val = out & 0x0000003f0000003fULL;
		वापस;
	पूर्ण

	out = (out + (out >> 32)) & 0x7f;
	op->val = out;	/* popcntd */
पूर्ण

#अगर_घोषित CONFIG_PPC64
अटल nokprobe_अंतरभूत व्योम करो_bpermd(स्थिर काष्ठा pt_regs *regs,
				      काष्ठा inकाष्ठाion_op *op,
				      अचिन्हित दीर्घ v1, अचिन्हित दीर्घ v2)
अणु
	अचिन्हित अक्षर perm, idx;
	अचिन्हित पूर्णांक i;

	perm = 0;
	क्रम (i = 0; i < 8; i++) अणु
		idx = (v1 >> (i * 8)) & 0xff;
		अगर (idx < 64)
			अगर (v2 & PPC_BIT(idx))
				perm |= 1 << i;
	पूर्ण
	op->val = perm;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC64 */
/*
 * The size parameter adjusts the equivalent prty inकाष्ठाion.
 * prtyw = 32, prtyd = 64
 */
अटल nokprobe_अंतरभूत व्योम करो_prty(स्थिर काष्ठा pt_regs *regs,
				    काष्ठा inकाष्ठाion_op *op,
				    अचिन्हित दीर्घ v, पूर्णांक size)
अणु
	अचिन्हित दीर्घ दीर्घ res = v ^ (v >> 8);

	res ^= res >> 16;
	अगर (size == 32) अणु		/* prtyw */
		op->val = res & 0x0000000100000001ULL;
		वापस;
	पूर्ण

	res ^= res >> 32;
	op->val = res & 1;	/*prtyd */
पूर्ण

अटल nokprobe_अंतरभूत पूर्णांक trap_compare(दीर्घ v1, दीर्घ v2)
अणु
	पूर्णांक ret = 0;

	अगर (v1 < v2)
		ret |= 0x10;
	अन्यथा अगर (v1 > v2)
		ret |= 0x08;
	अन्यथा
		ret |= 0x04;
	अगर ((अचिन्हित दीर्घ)v1 < (अचिन्हित दीर्घ)v2)
		ret |= 0x02;
	अन्यथा अगर ((अचिन्हित दीर्घ)v1 > (अचिन्हित दीर्घ)v2)
		ret |= 0x01;
	वापस ret;
पूर्ण

/*
 * Elements of 32-bit rotate and mask inकाष्ठाions.
 */
#घोषणा MASK32(mb, me)	((0xffffffffUL >> (mb)) + \
			 ((चिन्हित दीर्घ)-0x80000000L >> (me)) + ((me) >= (mb)))
#अगर_घोषित __घातerpc64__
#घोषणा MASK64_L(mb)	(~0UL >> (mb))
#घोषणा MASK64_R(me)	((चिन्हित दीर्घ)-0x8000000000000000L >> (me))
#घोषणा MASK64(mb, me)	(MASK64_L(mb) + MASK64_R(me) + ((me) >= (mb)))
#घोषणा DATA32(x)	(((x) & 0xffffffffUL) | (((x) & 0xffffffffUL) << 32))
#अन्यथा
#घोषणा DATA32(x)	(x)
#पूर्ण_अगर
#घोषणा ROTATE(x, n)	((n) ? (((x) << (n)) | ((x) >> (8 * माप(दीर्घ) - (n)))) : (x))

/*
 * Decode an inकाष्ठाion, and वापस inक्रमmation about it in *op
 * without changing *regs.
 * Integer arithmetic and logical inकाष्ठाions, branches, and barrier
 * inकाष्ठाions can be emulated just using the inक्रमmation in *op.
 *
 * Return value is 1 अगर the inकाष्ठाion can be emulated just by
 * updating *regs with the inक्रमmation in *op, -1 अगर we need the
 * GPRs but *regs करोesn't contain the full रेजिस्टर set, or 0
 * otherwise.
 */
पूर्णांक analyse_instr(काष्ठा inकाष्ठाion_op *op, स्थिर काष्ठा pt_regs *regs,
		  काष्ठा ppc_inst instr)
अणु
#अगर_घोषित CONFIG_PPC64
	अचिन्हित पूर्णांक suffixopcode, prefixtype, prefix_r;
#पूर्ण_अगर
	अचिन्हित पूर्णांक opcode, ra, rb, rc, rd, spr, u;
	अचिन्हित दीर्घ पूर्णांक imm;
	अचिन्हित दीर्घ पूर्णांक val, val2;
	अचिन्हित पूर्णांक mb, me, sh;
	अचिन्हित पूर्णांक word, suffix;
	दीर्घ ival;

	word = ppc_inst_val(instr);
	suffix = ppc_inst_suffix(instr);

	op->type = COMPUTE;

	opcode = ppc_inst_primary_opcode(instr);
	चयन (opcode) अणु
	हाल 16:	/* bc */
		op->type = BRANCH;
		imm = (चिन्हित लघु)(word & 0xfffc);
		अगर ((word & 2) == 0)
			imm += regs->nip;
		op->val = truncate_अगर_32bit(regs->msr, imm);
		अगर (word & 1)
			op->type |= SETLK;
		अगर (branch_taken(word, regs, op))
			op->type |= BRTAKEN;
		वापस 1;
#अगर_घोषित CONFIG_PPC64
	हाल 17:	/* sc */
		अगर ((word & 0xfe2) == 2)
			op->type = SYSCALL;
		अन्यथा अगर (IS_ENABLED(CONFIG_PPC_BOOK3S_64) &&
				(word & 0xfe3) == 1) अणु	/* scv */
			op->type = SYSCALL_VECTORED_0;
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
		पूर्ण अन्यथा
			op->type = UNKNOWN;
		वापस 0;
#पूर्ण_अगर
	हाल 18:	/* b */
		op->type = BRANCH | BRTAKEN;
		imm = word & 0x03fffffc;
		अगर (imm & 0x02000000)
			imm -= 0x04000000;
		अगर ((word & 2) == 0)
			imm += regs->nip;
		op->val = truncate_अगर_32bit(regs->msr, imm);
		अगर (word & 1)
			op->type |= SETLK;
		वापस 1;
	हाल 19:
		चयन ((word >> 1) & 0x3ff) अणु
		हाल 0:		/* mcrf */
			op->type = COMPUTE + SETCC;
			rd = 7 - ((word >> 23) & 0x7);
			ra = 7 - ((word >> 18) & 0x7);
			rd *= 4;
			ra *= 4;
			val = (regs->ccr >> ra) & 0xf;
			op->ccval = (regs->ccr & ~(0xfUL << rd)) | (val << rd);
			वापस 1;

		हाल 16:	/* bclr */
		हाल 528:	/* bcctr */
			op->type = BRANCH;
			imm = (word & 0x400)? regs->ctr: regs->link;
			op->val = truncate_अगर_32bit(regs->msr, imm);
			अगर (word & 1)
				op->type |= SETLK;
			अगर (branch_taken(word, regs, op))
				op->type |= BRTAKEN;
			वापस 1;

		हाल 18:	/* rfid, scary */
			अगर (regs->msr & MSR_PR)
				जाओ priv;
			op->type = RFI;
			वापस 0;

		हाल 150:	/* isync */
			op->type = BARRIER | BARRIER_ISYNC;
			वापस 1;

		हाल 33:	/* crnor */
		हाल 129:	/* cअक्रमc */
		हाल 193:	/* crxor */
		हाल 225:	/* crnand */
		हाल 257:	/* cअक्रम */
		हाल 289:	/* creqv */
		हाल 417:	/* crorc */
		हाल 449:	/* cror */
			op->type = COMPUTE + SETCC;
			ra = (word >> 16) & 0x1f;
			rb = (word >> 11) & 0x1f;
			rd = (word >> 21) & 0x1f;
			ra = (regs->ccr >> (31 - ra)) & 1;
			rb = (regs->ccr >> (31 - rb)) & 1;
			val = (word >> (6 + ra * 2 + rb)) & 1;
			op->ccval = (regs->ccr & ~(1UL << (31 - rd))) |
				(val << (31 - rd));
			वापस 1;
		पूर्ण
		अवरोध;
	हाल 31:
		चयन ((word >> 1) & 0x3ff) अणु
		हाल 598:	/* sync */
			op->type = BARRIER + BARRIER_SYNC;
#अगर_घोषित __घातerpc64__
			चयन ((word >> 21) & 3) अणु
			हाल 1:		/* lwsync */
				op->type = BARRIER + BARRIER_LWSYNC;
				अवरोध;
			हाल 2:		/* ptesync */
				op->type = BARRIER + BARRIER_PTESYNC;
				अवरोध;
			पूर्ण
#पूर्ण_अगर
			वापस 1;

		हाल 854:	/* eieio */
			op->type = BARRIER + BARRIER_EIEIO;
			वापस 1;
		पूर्ण
		अवरोध;
	पूर्ण

	rd = (word >> 21) & 0x1f;
	ra = (word >> 16) & 0x1f;
	rb = (word >> 11) & 0x1f;
	rc = (word >> 6) & 0x1f;

	चयन (opcode) अणु
#अगर_घोषित __घातerpc64__
	हाल 1:
		अगर (!cpu_has_feature(CPU_FTR_ARCH_31))
			जाओ unknown_opcode;

		prefix_r = GET_PREFIX_R(word);
		ra = GET_PREFIX_RA(suffix);
		rd = (suffix >> 21) & 0x1f;
		op->reg = rd;
		op->val = regs->gpr[rd];
		suffixopcode = get_op(suffix);
		prefixtype = (word >> 24) & 0x3;
		चयन (prefixtype) अणु
		हाल 2:
			अगर (prefix_r && ra)
				वापस 0;
			चयन (suffixopcode) अणु
			हाल 14:	/* paddi */
				op->type = COMPUTE | PREFIXED;
				op->val = mlsd_8lsd_ea(word, suffix, regs);
				जाओ compute_करोne;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल 2:		/* tdi */
		अगर (rd & trap_compare(regs->gpr[ra], (लघु) word))
			जाओ trap;
		वापस 1;
#पूर्ण_अगर
	हाल 3:		/* twi */
		अगर (rd & trap_compare((पूर्णांक)regs->gpr[ra], (लघु) word))
			जाओ trap;
		वापस 1;

#अगर_घोषित __घातerpc64__
	हाल 4:
		/*
		 * There are very many inकाष्ठाions with this primary opcode
		 * पूर्णांकroduced in the ISA as early as v2.03. However, the ones
		 * we currently emulate were all पूर्णांकroduced with ISA 3.0
		 */
		अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
			जाओ unknown_opcode;

		चयन (word & 0x3f) अणु
		हाल 48:	/* maddhd */
			यंत्र अस्थिर(PPC_MADDHD(%0, %1, %2, %3) :
				     "=r" (op->val) : "r" (regs->gpr[ra]),
				     "r" (regs->gpr[rb]), "r" (regs->gpr[rc]));
			जाओ compute_करोne;

		हाल 49:	/* maddhdu */
			यंत्र अस्थिर(PPC_MADDHDU(%0, %1, %2, %3) :
				     "=r" (op->val) : "r" (regs->gpr[ra]),
				     "r" (regs->gpr[rb]), "r" (regs->gpr[rc]));
			जाओ compute_करोne;

		हाल 51:	/* maddld */
			यंत्र अस्थिर(PPC_MADDLD(%0, %1, %2, %3) :
				     "=r" (op->val) : "r" (regs->gpr[ra]),
				     "r" (regs->gpr[rb]), "r" (regs->gpr[rc]));
			जाओ compute_करोne;
		पूर्ण

		/*
		 * There are other inकाष्ठाions from ISA 3.0 with the same
		 * primary opcode which करो not have emulation support yet.
		 */
		जाओ unknown_opcode;
#पूर्ण_अगर

	हाल 7:		/* mulli */
		op->val = regs->gpr[ra] * (लघु) word;
		जाओ compute_करोne;

	हाल 8:		/* subfic */
		imm = (लघु) word;
		add_with_carry(regs, op, rd, ~regs->gpr[ra], imm, 1);
		वापस 1;

	हाल 10:	/* cmpli */
		imm = (अचिन्हित लघु) word;
		val = regs->gpr[ra];
#अगर_घोषित __घातerpc64__
		अगर ((rd & 1) == 0)
			val = (अचिन्हित पूर्णांक) val;
#पूर्ण_अगर
		करो_cmp_अचिन्हित(regs, op, val, imm, rd >> 2);
		वापस 1;

	हाल 11:	/* cmpi */
		imm = (लघु) word;
		val = regs->gpr[ra];
#अगर_घोषित __घातerpc64__
		अगर ((rd & 1) == 0)
			val = (पूर्णांक) val;
#पूर्ण_अगर
		करो_cmp_चिन्हित(regs, op, val, imm, rd >> 2);
		वापस 1;

	हाल 12:	/* addic */
		imm = (लघु) word;
		add_with_carry(regs, op, rd, regs->gpr[ra], imm, 0);
		वापस 1;

	हाल 13:	/* addic. */
		imm = (लघु) word;
		add_with_carry(regs, op, rd, regs->gpr[ra], imm, 0);
		set_cr0(regs, op);
		वापस 1;

	हाल 14:	/* addi */
		imm = (लघु) word;
		अगर (ra)
			imm += regs->gpr[ra];
		op->val = imm;
		जाओ compute_करोne;

	हाल 15:	/* addis */
		imm = ((लघु) word) << 16;
		अगर (ra)
			imm += regs->gpr[ra];
		op->val = imm;
		जाओ compute_करोne;

	हाल 19:
		अगर (((word >> 1) & 0x1f) == 2) अणु
			/* addpcis */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			imm = (लघु) (word & 0xffc1);	/* d0 + d2 fields */
			imm |= (word >> 15) & 0x3e;	/* d1 field */
			op->val = regs->nip + (imm << 16) + 4;
			जाओ compute_करोne;
		पूर्ण
		op->type = UNKNOWN;
		वापस 0;

	हाल 20:	/* rlwimi */
		mb = (word >> 6) & 0x1f;
		me = (word >> 1) & 0x1f;
		val = DATA32(regs->gpr[rd]);
		imm = MASK32(mb, me);
		op->val = (regs->gpr[ra] & ~imm) | (ROTATE(val, rb) & imm);
		जाओ logical_करोne;

	हाल 21:	/* rlwinm */
		mb = (word >> 6) & 0x1f;
		me = (word >> 1) & 0x1f;
		val = DATA32(regs->gpr[rd]);
		op->val = ROTATE(val, rb) & MASK32(mb, me);
		जाओ logical_करोne;

	हाल 23:	/* rlwnm */
		mb = (word >> 6) & 0x1f;
		me = (word >> 1) & 0x1f;
		rb = regs->gpr[rb] & 0x1f;
		val = DATA32(regs->gpr[rd]);
		op->val = ROTATE(val, rb) & MASK32(mb, me);
		जाओ logical_करोne;

	हाल 24:	/* ori */
		op->val = regs->gpr[rd] | (अचिन्हित लघु) word;
		जाओ logical_करोne_nocc;

	हाल 25:	/* oris */
		imm = (अचिन्हित लघु) word;
		op->val = regs->gpr[rd] | (imm << 16);
		जाओ logical_करोne_nocc;

	हाल 26:	/* xori */
		op->val = regs->gpr[rd] ^ (अचिन्हित लघु) word;
		जाओ logical_करोne_nocc;

	हाल 27:	/* xoris */
		imm = (अचिन्हित लघु) word;
		op->val = regs->gpr[rd] ^ (imm << 16);
		जाओ logical_करोne_nocc;

	हाल 28:	/* andi. */
		op->val = regs->gpr[rd] & (अचिन्हित लघु) word;
		set_cr0(regs, op);
		जाओ logical_करोne_nocc;

	हाल 29:	/* andis. */
		imm = (अचिन्हित लघु) word;
		op->val = regs->gpr[rd] & (imm << 16);
		set_cr0(regs, op);
		जाओ logical_करोne_nocc;

#अगर_घोषित __घातerpc64__
	हाल 30:	/* rld* */
		mb = ((word >> 6) & 0x1f) | (word & 0x20);
		val = regs->gpr[rd];
		अगर ((word & 0x10) == 0) अणु
			sh = rb | ((word & 2) << 4);
			val = ROTATE(val, sh);
			चयन ((word >> 2) & 3) अणु
			हाल 0:		/* rldicl */
				val &= MASK64_L(mb);
				अवरोध;
			हाल 1:		/* rldicr */
				val &= MASK64_R(mb);
				अवरोध;
			हाल 2:		/* rldic */
				val &= MASK64(mb, 63 - sh);
				अवरोध;
			हाल 3:		/* rldimi */
				imm = MASK64(mb, 63 - sh);
				val = (regs->gpr[ra] & ~imm) |
					(val & imm);
			पूर्ण
			op->val = val;
			जाओ logical_करोne;
		पूर्ण अन्यथा अणु
			sh = regs->gpr[rb] & 0x3f;
			val = ROTATE(val, sh);
			चयन ((word >> 1) & 7) अणु
			हाल 0:		/* rldcl */
				op->val = val & MASK64_L(mb);
				जाओ logical_करोne;
			हाल 1:		/* rldcr */
				op->val = val & MASK64_R(mb);
				जाओ logical_करोne;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		op->type = UNKNOWN;	/* illegal inकाष्ठाion */
		वापस 0;

	हाल 31:
		/* isel occupies 32 minor opcodes */
		अगर (((word >> 1) & 0x1f) == 15) अणु
			mb = (word >> 6) & 0x1f; /* bc field */
			val = (regs->ccr >> (31 - mb)) & 1;
			val2 = (ra) ? regs->gpr[ra] : 0;

			op->val = (val) ? val2 : regs->gpr[rb];
			जाओ compute_करोne;
		पूर्ण

		चयन ((word >> 1) & 0x3ff) अणु
		हाल 4:		/* tw */
			अगर (rd == 0x1f ||
			    (rd & trap_compare((पूर्णांक)regs->gpr[ra],
					       (पूर्णांक)regs->gpr[rb])))
				जाओ trap;
			वापस 1;
#अगर_घोषित __घातerpc64__
		हाल 68:	/* td */
			अगर (rd & trap_compare(regs->gpr[ra], regs->gpr[rb]))
				जाओ trap;
			वापस 1;
#पूर्ण_अगर
		हाल 83:	/* mfmsr */
			अगर (regs->msr & MSR_PR)
				जाओ priv;
			op->type = MFMSR;
			op->reg = rd;
			वापस 0;
		हाल 146:	/* mपंचांगsr */
			अगर (regs->msr & MSR_PR)
				जाओ priv;
			op->type = MTMSR;
			op->reg = rd;
			op->val = 0xffffffff & ~(MSR_ME | MSR_LE);
			वापस 0;
#अगर_घोषित CONFIG_PPC64
		हाल 178:	/* mपंचांगsrd */
			अगर (regs->msr & MSR_PR)
				जाओ priv;
			op->type = MTMSR;
			op->reg = rd;
			/* only MSR_EE and MSR_RI get changed अगर bit 15 set */
			/* mपंचांगsrd करोesn't change MSR_HV, MSR_ME or MSR_LE */
			imm = (word & 0x10000)? 0x8002: 0xefffffffffffeffeUL;
			op->val = imm;
			वापस 0;
#पूर्ण_अगर

		हाल 19:	/* mfcr */
			imm = 0xffffffffUL;
			अगर ((word >> 20) & 1) अणु
				imm = 0xf0000000UL;
				क्रम (sh = 0; sh < 8; ++sh) अणु
					अगर (word & (0x80000 >> sh))
						अवरोध;
					imm >>= 4;
				पूर्ण
			पूर्ण
			op->val = regs->ccr & imm;
			जाओ compute_करोne;

		हाल 144:	/* mtcrf */
			op->type = COMPUTE + SETCC;
			imm = 0xf0000000UL;
			val = regs->gpr[rd];
			op->ccval = regs->ccr;
			क्रम (sh = 0; sh < 8; ++sh) अणु
				अगर (word & (0x80000 >> sh))
					op->ccval = (op->ccval & ~imm) |
						(val & imm);
				imm >>= 4;
			पूर्ण
			वापस 1;

		हाल 339:	/* mfspr */
			spr = ((word >> 16) & 0x1f) | ((word >> 6) & 0x3e0);
			op->type = MFSPR;
			op->reg = rd;
			op->spr = spr;
			अगर (spr == SPRN_XER || spr == SPRN_LR ||
			    spr == SPRN_CTR)
				वापस 1;
			वापस 0;

		हाल 467:	/* mtspr */
			spr = ((word >> 16) & 0x1f) | ((word >> 6) & 0x3e0);
			op->type = MTSPR;
			op->val = regs->gpr[rd];
			op->spr = spr;
			अगर (spr == SPRN_XER || spr == SPRN_LR ||
			    spr == SPRN_CTR)
				वापस 1;
			वापस 0;

/*
 * Compare inकाष्ठाions
 */
		हाल 0:	/* cmp */
			val = regs->gpr[ra];
			val2 = regs->gpr[rb];
#अगर_घोषित __घातerpc64__
			अगर ((rd & 1) == 0) अणु
				/* word (32-bit) compare */
				val = (पूर्णांक) val;
				val2 = (पूर्णांक) val2;
			पूर्ण
#पूर्ण_अगर
			करो_cmp_चिन्हित(regs, op, val, val2, rd >> 2);
			वापस 1;

		हाल 32:	/* cmpl */
			val = regs->gpr[ra];
			val2 = regs->gpr[rb];
#अगर_घोषित __घातerpc64__
			अगर ((rd & 1) == 0) अणु
				/* word (32-bit) compare */
				val = (अचिन्हित पूर्णांक) val;
				val2 = (अचिन्हित पूर्णांक) val2;
			पूर्ण
#पूर्ण_अगर
			करो_cmp_अचिन्हित(regs, op, val, val2, rd >> 2);
			वापस 1;

		हाल 508: /* cmpb */
			करो_cmpb(regs, op, regs->gpr[rd], regs->gpr[rb]);
			जाओ logical_करोne_nocc;

/*
 * Arithmetic inकाष्ठाions
 */
		हाल 8:	/* subfc */
			add_with_carry(regs, op, rd, ~regs->gpr[ra],
				       regs->gpr[rb], 1);
			जाओ arith_करोne;
#अगर_घोषित __घातerpc64__
		हाल 9:	/* mulhdu */
			यंत्र("mulhdu %0,%1,%2" : "=r" (op->val) :
			    "r" (regs->gpr[ra]), "r" (regs->gpr[rb]));
			जाओ arith_करोne;
#पूर्ण_अगर
		हाल 10:	/* addc */
			add_with_carry(regs, op, rd, regs->gpr[ra],
				       regs->gpr[rb], 0);
			जाओ arith_करोne;

		हाल 11:	/* mulhwu */
			यंत्र("mulhwu %0,%1,%2" : "=r" (op->val) :
			    "r" (regs->gpr[ra]), "r" (regs->gpr[rb]));
			जाओ arith_करोne;

		हाल 40:	/* subf */
			op->val = regs->gpr[rb] - regs->gpr[ra];
			जाओ arith_करोne;
#अगर_घोषित __घातerpc64__
		हाल 73:	/* mulhd */
			यंत्र("mulhd %0,%1,%2" : "=r" (op->val) :
			    "r" (regs->gpr[ra]), "r" (regs->gpr[rb]));
			जाओ arith_करोne;
#पूर्ण_अगर
		हाल 75:	/* mulhw */
			यंत्र("mulhw %0,%1,%2" : "=r" (op->val) :
			    "r" (regs->gpr[ra]), "r" (regs->gpr[rb]));
			जाओ arith_करोne;

		हाल 104:	/* neg */
			op->val = -regs->gpr[ra];
			जाओ arith_करोne;

		हाल 136:	/* subfe */
			add_with_carry(regs, op, rd, ~regs->gpr[ra],
				       regs->gpr[rb], regs->xer & XER_CA);
			जाओ arith_करोne;

		हाल 138:	/* adde */
			add_with_carry(regs, op, rd, regs->gpr[ra],
				       regs->gpr[rb], regs->xer & XER_CA);
			जाओ arith_करोne;

		हाल 200:	/* subfze */
			add_with_carry(regs, op, rd, ~regs->gpr[ra], 0L,
				       regs->xer & XER_CA);
			जाओ arith_करोne;

		हाल 202:	/* addze */
			add_with_carry(regs, op, rd, regs->gpr[ra], 0L,
				       regs->xer & XER_CA);
			जाओ arith_करोne;

		हाल 232:	/* subfme */
			add_with_carry(regs, op, rd, ~regs->gpr[ra], -1L,
				       regs->xer & XER_CA);
			जाओ arith_करोne;
#अगर_घोषित __घातerpc64__
		हाल 233:	/* mulld */
			op->val = regs->gpr[ra] * regs->gpr[rb];
			जाओ arith_करोne;
#पूर्ण_अगर
		हाल 234:	/* addme */
			add_with_carry(regs, op, rd, regs->gpr[ra], -1L,
				       regs->xer & XER_CA);
			जाओ arith_करोne;

		हाल 235:	/* mullw */
			op->val = (दीर्घ)(पूर्णांक) regs->gpr[ra] *
				(पूर्णांक) regs->gpr[rb];

			जाओ arith_करोne;
#अगर_घोषित __घातerpc64__
		हाल 265:	/* modud */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->val = regs->gpr[ra] % regs->gpr[rb];
			जाओ compute_करोne;
#पूर्ण_अगर
		हाल 266:	/* add */
			op->val = regs->gpr[ra] + regs->gpr[rb];
			जाओ arith_करोne;

		हाल 267:	/* moduw */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->val = (अचिन्हित पूर्णांक) regs->gpr[ra] %
				(अचिन्हित पूर्णांक) regs->gpr[rb];
			जाओ compute_करोne;
#अगर_घोषित __घातerpc64__
		हाल 457:	/* भागdu */
			op->val = regs->gpr[ra] / regs->gpr[rb];
			जाओ arith_करोne;
#पूर्ण_अगर
		हाल 459:	/* भागwu */
			op->val = (अचिन्हित पूर्णांक) regs->gpr[ra] /
				(अचिन्हित पूर्णांक) regs->gpr[rb];
			जाओ arith_करोne;
#अगर_घोषित __घातerpc64__
		हाल 489:	/* भागd */
			op->val = (दीर्घ पूर्णांक) regs->gpr[ra] /
				(दीर्घ पूर्णांक) regs->gpr[rb];
			जाओ arith_करोne;
#पूर्ण_अगर
		हाल 491:	/* भागw */
			op->val = (पूर्णांक) regs->gpr[ra] /
				(पूर्णांक) regs->gpr[rb];
			जाओ arith_करोne;
#अगर_घोषित __घातerpc64__
		हाल 425:	/* भागde[.] */
			यंत्र अस्थिर(PPC_DIVDE(%0, %1, %2) :
				"=r" (op->val) : "r" (regs->gpr[ra]),
				"r" (regs->gpr[rb]));
			जाओ arith_करोne;
		हाल 393:	/* भागdeu[.] */
			यंत्र अस्थिर(PPC_DIVDEU(%0, %1, %2) :
				"=r" (op->val) : "r" (regs->gpr[ra]),
				"r" (regs->gpr[rb]));
			जाओ arith_करोne;
#पूर्ण_अगर
		हाल 755:	/* darn */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			चयन (ra & 0x3) अणु
			हाल 0:
				/* 32-bit conditioned */
				यंत्र अस्थिर(PPC_DARN(%0, 0) : "=r" (op->val));
				जाओ compute_करोne;

			हाल 1:
				/* 64-bit conditioned */
				यंत्र अस्थिर(PPC_DARN(%0, 1) : "=r" (op->val));
				जाओ compute_करोne;

			हाल 2:
				/* 64-bit raw */
				यंत्र अस्थिर(PPC_DARN(%0, 2) : "=r" (op->val));
				जाओ compute_करोne;
			पूर्ण

			जाओ unknown_opcode;
#अगर_घोषित __घातerpc64__
		हाल 777:	/* modsd */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->val = (दीर्घ पूर्णांक) regs->gpr[ra] %
				(दीर्घ पूर्णांक) regs->gpr[rb];
			जाओ compute_करोne;
#पूर्ण_अगर
		हाल 779:	/* modsw */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->val = (पूर्णांक) regs->gpr[ra] %
				(पूर्णांक) regs->gpr[rb];
			जाओ compute_करोne;


/*
 * Logical inकाष्ठाions
 */
		हाल 26:	/* cntlzw */
			val = (अचिन्हित पूर्णांक) regs->gpr[rd];
			op->val = ( val ? __builtin_clz(val) : 32 );
			जाओ logical_करोne;
#अगर_घोषित __घातerpc64__
		हाल 58:	/* cntlzd */
			val = regs->gpr[rd];
			op->val = ( val ? __builtin_clzl(val) : 64 );
			जाओ logical_करोne;
#पूर्ण_अगर
		हाल 28:	/* and */
			op->val = regs->gpr[rd] & regs->gpr[rb];
			जाओ logical_करोne;

		हाल 60:	/* andc */
			op->val = regs->gpr[rd] & ~regs->gpr[rb];
			जाओ logical_करोne;

		हाल 122:	/* popcntb */
			करो_popcnt(regs, op, regs->gpr[rd], 8);
			जाओ logical_करोne_nocc;

		हाल 124:	/* nor */
			op->val = ~(regs->gpr[rd] | regs->gpr[rb]);
			जाओ logical_करोne;

		हाल 154:	/* prtyw */
			करो_prty(regs, op, regs->gpr[rd], 32);
			जाओ logical_करोne_nocc;

		हाल 186:	/* prtyd */
			करो_prty(regs, op, regs->gpr[rd], 64);
			जाओ logical_करोne_nocc;
#अगर_घोषित CONFIG_PPC64
		हाल 252:	/* bpermd */
			करो_bpermd(regs, op, regs->gpr[rd], regs->gpr[rb]);
			जाओ logical_करोne_nocc;
#पूर्ण_अगर
		हाल 284:	/* xor */
			op->val = ~(regs->gpr[rd] ^ regs->gpr[rb]);
			जाओ logical_करोne;

		हाल 316:	/* xor */
			op->val = regs->gpr[rd] ^ regs->gpr[rb];
			जाओ logical_करोne;

		हाल 378:	/* popcntw */
			करो_popcnt(regs, op, regs->gpr[rd], 32);
			जाओ logical_करोne_nocc;

		हाल 412:	/* orc */
			op->val = regs->gpr[rd] | ~regs->gpr[rb];
			जाओ logical_करोne;

		हाल 444:	/* or */
			op->val = regs->gpr[rd] | regs->gpr[rb];
			जाओ logical_करोne;

		हाल 476:	/* nand */
			op->val = ~(regs->gpr[rd] & regs->gpr[rb]);
			जाओ logical_करोne;
#अगर_घोषित CONFIG_PPC64
		हाल 506:	/* popcntd */
			करो_popcnt(regs, op, regs->gpr[rd], 64);
			जाओ logical_करोne_nocc;
#पूर्ण_अगर
		हाल 538:	/* cnttzw */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			val = (अचिन्हित पूर्णांक) regs->gpr[rd];
			op->val = (val ? __builtin_ctz(val) : 32);
			जाओ logical_करोne;
#अगर_घोषित __घातerpc64__
		हाल 570:	/* cnttzd */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			val = regs->gpr[rd];
			op->val = (val ? __builtin_ctzl(val) : 64);
			जाओ logical_करोne;
#पूर्ण_अगर
		हाल 922:	/* extsh */
			op->val = (चिन्हित लघु) regs->gpr[rd];
			जाओ logical_करोne;

		हाल 954:	/* extsb */
			op->val = (चिन्हित अक्षर) regs->gpr[rd];
			जाओ logical_करोne;
#अगर_घोषित __घातerpc64__
		हाल 986:	/* extsw */
			op->val = (चिन्हित पूर्णांक) regs->gpr[rd];
			जाओ logical_करोne;
#पूर्ण_अगर

/*
 * Shअगरt inकाष्ठाions
 */
		हाल 24:	/* slw */
			sh = regs->gpr[rb] & 0x3f;
			अगर (sh < 32)
				op->val = (regs->gpr[rd] << sh) & 0xffffffffUL;
			अन्यथा
				op->val = 0;
			जाओ logical_करोne;

		हाल 536:	/* srw */
			sh = regs->gpr[rb] & 0x3f;
			अगर (sh < 32)
				op->val = (regs->gpr[rd] & 0xffffffffUL) >> sh;
			अन्यथा
				op->val = 0;
			जाओ logical_करोne;

		हाल 792:	/* sraw */
			op->type = COMPUTE + SETREG + SETXER;
			sh = regs->gpr[rb] & 0x3f;
			ival = (चिन्हित पूर्णांक) regs->gpr[rd];
			op->val = ival >> (sh < 32 ? sh : 31);
			op->xerval = regs->xer;
			अगर (ival < 0 && (sh >= 32 || (ival & ((1ul << sh) - 1)) != 0))
				op->xerval |= XER_CA;
			अन्यथा
				op->xerval &= ~XER_CA;
			set_ca32(op, op->xerval & XER_CA);
			जाओ logical_करोne;

		हाल 824:	/* srawi */
			op->type = COMPUTE + SETREG + SETXER;
			sh = rb;
			ival = (चिन्हित पूर्णांक) regs->gpr[rd];
			op->val = ival >> sh;
			op->xerval = regs->xer;
			अगर (ival < 0 && (ival & ((1ul << sh) - 1)) != 0)
				op->xerval |= XER_CA;
			अन्यथा
				op->xerval &= ~XER_CA;
			set_ca32(op, op->xerval & XER_CA);
			जाओ logical_करोne;

#अगर_घोषित __घातerpc64__
		हाल 27:	/* sld */
			sh = regs->gpr[rb] & 0x7f;
			अगर (sh < 64)
				op->val = regs->gpr[rd] << sh;
			अन्यथा
				op->val = 0;
			जाओ logical_करोne;

		हाल 539:	/* srd */
			sh = regs->gpr[rb] & 0x7f;
			अगर (sh < 64)
				op->val = regs->gpr[rd] >> sh;
			अन्यथा
				op->val = 0;
			जाओ logical_करोne;

		हाल 794:	/* srad */
			op->type = COMPUTE + SETREG + SETXER;
			sh = regs->gpr[rb] & 0x7f;
			ival = (चिन्हित दीर्घ पूर्णांक) regs->gpr[rd];
			op->val = ival >> (sh < 64 ? sh : 63);
			op->xerval = regs->xer;
			अगर (ival < 0 && (sh >= 64 || (ival & ((1ul << sh) - 1)) != 0))
				op->xerval |= XER_CA;
			अन्यथा
				op->xerval &= ~XER_CA;
			set_ca32(op, op->xerval & XER_CA);
			जाओ logical_करोne;

		हाल 826:	/* sradi with sh_5 = 0 */
		हाल 827:	/* sradi with sh_5 = 1 */
			op->type = COMPUTE + SETREG + SETXER;
			sh = rb | ((word & 2) << 4);
			ival = (चिन्हित दीर्घ पूर्णांक) regs->gpr[rd];
			op->val = ival >> sh;
			op->xerval = regs->xer;
			अगर (ival < 0 && (ival & ((1ul << sh) - 1)) != 0)
				op->xerval |= XER_CA;
			अन्यथा
				op->xerval &= ~XER_CA;
			set_ca32(op, op->xerval & XER_CA);
			जाओ logical_करोne;

		हाल 890:	/* extswsli with sh_5 = 0 */
		हाल 891:	/* extswsli with sh_5 = 1 */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->type = COMPUTE + SETREG;
			sh = rb | ((word & 2) << 4);
			val = (चिन्हित पूर्णांक) regs->gpr[rd];
			अगर (sh)
				op->val = ROTATE(val, sh) & MASK64(0, 63 - sh);
			अन्यथा
				op->val = val;
			जाओ logical_करोne;

#पूर्ण_अगर /* __घातerpc64__ */

/*
 * Cache inकाष्ठाions
 */
		हाल 54:	/* dcbst */
			op->type = MKOP(CACHEOP, DCBST, 0);
			op->ea = xक्रमm_ea(word, regs);
			वापस 0;

		हाल 86:	/* dcbf */
			op->type = MKOP(CACHEOP, DCBF, 0);
			op->ea = xक्रमm_ea(word, regs);
			वापस 0;

		हाल 246:	/* dcbtst */
			op->type = MKOP(CACHEOP, DCBTST, 0);
			op->ea = xक्रमm_ea(word, regs);
			op->reg = rd;
			वापस 0;

		हाल 278:	/* dcbt */
			op->type = MKOP(CACHEOP, DCBTST, 0);
			op->ea = xक्रमm_ea(word, regs);
			op->reg = rd;
			वापस 0;

		हाल 982:	/* icbi */
			op->type = MKOP(CACHEOP, ICBI, 0);
			op->ea = xक्रमm_ea(word, regs);
			वापस 0;

		हाल 1014:	/* dcbz */
			op->type = MKOP(CACHEOP, DCBZ, 0);
			op->ea = xक्रमm_ea(word, regs);
			वापस 0;
		पूर्ण
		अवरोध;
	पूर्ण

/*
 * Loads and stores.
 */
	op->type = UNKNOWN;
	op->update_reg = ra;
	op->reg = rd;
	op->val = regs->gpr[rd];
	u = (word >> 20) & UPDATE;
	op->vsx_flags = 0;

	चयन (opcode) अणु
	हाल 31:
		u = word & UPDATE;
		op->ea = xक्रमm_ea(word, regs);
		चयन ((word >> 1) & 0x3ff) अणु
		हाल 20:	/* lwarx */
			op->type = MKOP(LARX, 0, 4);
			अवरोध;

		हाल 150:	/* stwcx. */
			op->type = MKOP(STCX, 0, 4);
			अवरोध;

#अगर_घोषित __घातerpc64__
		हाल 84:	/* ldarx */
			op->type = MKOP(LARX, 0, 8);
			अवरोध;

		हाल 214:	/* stdcx. */
			op->type = MKOP(STCX, 0, 8);
			अवरोध;

		हाल 52:	/* lbarx */
			op->type = MKOP(LARX, 0, 1);
			अवरोध;

		हाल 694:	/* stbcx. */
			op->type = MKOP(STCX, 0, 1);
			अवरोध;

		हाल 116:	/* lharx */
			op->type = MKOP(LARX, 0, 2);
			अवरोध;

		हाल 726:	/* sthcx. */
			op->type = MKOP(STCX, 0, 2);
			अवरोध;

		हाल 276:	/* lqarx */
			अगर (!((rd & 1) || rd == ra || rd == rb))
				op->type = MKOP(LARX, 0, 16);
			अवरोध;

		हाल 182:	/* stqcx. */
			अगर (!(rd & 1))
				op->type = MKOP(STCX, 0, 16);
			अवरोध;
#पूर्ण_अगर

		हाल 23:	/* lwzx */
		हाल 55:	/* lwzux */
			op->type = MKOP(LOAD, u, 4);
			अवरोध;

		हाल 87:	/* lbzx */
		हाल 119:	/* lbzux */
			op->type = MKOP(LOAD, u, 1);
			अवरोध;

#अगर_घोषित CONFIG_ALTIVEC
		/*
		 * Note: क्रम the load/store vector element inकाष्ठाions,
		 * bits of the EA say which field of the VMX रेजिस्टर to use.
		 */
		हाल 7:		/* lvebx */
			op->type = MKOP(LOAD_VMX, 0, 1);
			op->element_size = 1;
			अवरोध;

		हाल 39:	/* lvehx */
			op->type = MKOP(LOAD_VMX, 0, 2);
			op->element_size = 2;
			अवरोध;

		हाल 71:	/* lvewx */
			op->type = MKOP(LOAD_VMX, 0, 4);
			op->element_size = 4;
			अवरोध;

		हाल 103:	/* lvx */
		हाल 359:	/* lvxl */
			op->type = MKOP(LOAD_VMX, 0, 16);
			op->element_size = 16;
			अवरोध;

		हाल 135:	/* stvebx */
			op->type = MKOP(STORE_VMX, 0, 1);
			op->element_size = 1;
			अवरोध;

		हाल 167:	/* stvehx */
			op->type = MKOP(STORE_VMX, 0, 2);
			op->element_size = 2;
			अवरोध;

		हाल 199:	/* stvewx */
			op->type = MKOP(STORE_VMX, 0, 4);
			op->element_size = 4;
			अवरोध;

		हाल 231:	/* stvx */
		हाल 487:	/* stvxl */
			op->type = MKOP(STORE_VMX, 0, 16);
			अवरोध;
#पूर्ण_अगर /* CONFIG_ALTIVEC */

#अगर_घोषित __घातerpc64__
		हाल 21:	/* ldx */
		हाल 53:	/* ldux */
			op->type = MKOP(LOAD, u, 8);
			अवरोध;

		हाल 149:	/* stdx */
		हाल 181:	/* stdux */
			op->type = MKOP(STORE, u, 8);
			अवरोध;
#पूर्ण_अगर

		हाल 151:	/* stwx */
		हाल 183:	/* stwux */
			op->type = MKOP(STORE, u, 4);
			अवरोध;

		हाल 215:	/* stbx */
		हाल 247:	/* stbux */
			op->type = MKOP(STORE, u, 1);
			अवरोध;

		हाल 279:	/* lhzx */
		हाल 311:	/* lhzux */
			op->type = MKOP(LOAD, u, 2);
			अवरोध;

#अगर_घोषित __घातerpc64__
		हाल 341:	/* lwax */
		हाल 373:	/* lwaux */
			op->type = MKOP(LOAD, SIGNEXT | u, 4);
			अवरोध;
#पूर्ण_अगर

		हाल 343:	/* lhax */
		हाल 375:	/* lhaux */
			op->type = MKOP(LOAD, SIGNEXT | u, 2);
			अवरोध;

		हाल 407:	/* sthx */
		हाल 439:	/* sthux */
			op->type = MKOP(STORE, u, 2);
			अवरोध;

#अगर_घोषित __घातerpc64__
		हाल 532:	/* ldbrx */
			op->type = MKOP(LOAD, BYTEREV, 8);
			अवरोध;

#पूर्ण_अगर
		हाल 533:	/* lswx */
			op->type = MKOP(LOAD_MULTI, 0, regs->xer & 0x7f);
			अवरोध;

		हाल 534:	/* lwbrx */
			op->type = MKOP(LOAD, BYTEREV, 4);
			अवरोध;

		हाल 597:	/* lswi */
			अगर (rb == 0)
				rb = 32;	/* # bytes to load */
			op->type = MKOP(LOAD_MULTI, 0, rb);
			op->ea = ra ? regs->gpr[ra] : 0;
			अवरोध;

#अगर_घोषित CONFIG_PPC_FPU
		हाल 535:	/* lfsx */
		हाल 567:	/* lfsux */
			op->type = MKOP(LOAD_FP, u | FPCONV, 4);
			अवरोध;

		हाल 599:	/* lfdx */
		हाल 631:	/* lfdux */
			op->type = MKOP(LOAD_FP, u, 8);
			अवरोध;

		हाल 663:	/* stfsx */
		हाल 695:	/* stfsux */
			op->type = MKOP(STORE_FP, u | FPCONV, 4);
			अवरोध;

		हाल 727:	/* stfdx */
		हाल 759:	/* stfdux */
			op->type = MKOP(STORE_FP, u, 8);
			अवरोध;

#अगर_घोषित __घातerpc64__
		हाल 791:	/* lfdpx */
			op->type = MKOP(LOAD_FP, 0, 16);
			अवरोध;

		हाल 855:	/* lfiwax */
			op->type = MKOP(LOAD_FP, SIGNEXT, 4);
			अवरोध;

		हाल 887:	/* lfiwzx */
			op->type = MKOP(LOAD_FP, 0, 4);
			अवरोध;

		हाल 919:	/* stfdpx */
			op->type = MKOP(STORE_FP, 0, 16);
			अवरोध;

		हाल 983:	/* stfiwx */
			op->type = MKOP(STORE_FP, 0, 4);
			अवरोध;
#पूर्ण_अगर /* __घातerpc64 */
#पूर्ण_अगर /* CONFIG_PPC_FPU */

#अगर_घोषित __घातerpc64__
		हाल 660:	/* stdbrx */
			op->type = MKOP(STORE, BYTEREV, 8);
			op->val = byterev_8(regs->gpr[rd]);
			अवरोध;

#पूर्ण_अगर
		हाल 661:	/* stswx */
			op->type = MKOP(STORE_MULTI, 0, regs->xer & 0x7f);
			अवरोध;

		हाल 662:	/* stwbrx */
			op->type = MKOP(STORE, BYTEREV, 4);
			op->val = byterev_4(regs->gpr[rd]);
			अवरोध;

		हाल 725:	/* stswi */
			अगर (rb == 0)
				rb = 32;	/* # bytes to store */
			op->type = MKOP(STORE_MULTI, 0, rb);
			op->ea = ra ? regs->gpr[ra] : 0;
			अवरोध;

		हाल 790:	/* lhbrx */
			op->type = MKOP(LOAD, BYTEREV, 2);
			अवरोध;

		हाल 918:	/* sthbrx */
			op->type = MKOP(STORE, BYTEREV, 2);
			op->val = byterev_2(regs->gpr[rd]);
			अवरोध;

#अगर_घोषित CONFIG_VSX
		हाल 12:	/* lxsiwzx */
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(LOAD_VSX, 0, 4);
			op->element_size = 8;
			अवरोध;

		हाल 76:	/* lxsiwax */
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(LOAD_VSX, SIGNEXT, 4);
			op->element_size = 8;
			अवरोध;

		हाल 140:	/* stxsiwx */
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(STORE_VSX, 0, 4);
			op->element_size = 8;
			अवरोध;

		हाल 268:	/* lxvx */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(LOAD_VSX, 0, 16);
			op->element_size = 16;
			op->vsx_flags = VSX_CHECK_VEC;
			अवरोध;

		हाल 269:	/* lxvl */
		हाल 301: अणु	/* lxvll */
			पूर्णांक nb;
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->reg = rd | ((word & 1) << 5);
			op->ea = ra ? regs->gpr[ra] : 0;
			nb = regs->gpr[rb] & 0xff;
			अगर (nb > 16)
				nb = 16;
			op->type = MKOP(LOAD_VSX, 0, nb);
			op->element_size = 16;
			op->vsx_flags = ((word & 0x20) ? VSX_LDLEFT : 0) |
				VSX_CHECK_VEC;
			अवरोध;
		पूर्ण
		हाल 332:	/* lxvdsx */
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(LOAD_VSX, 0, 8);
			op->element_size = 8;
			op->vsx_flags = VSX_SPLAT;
			अवरोध;

		हाल 333:       /* lxvpx */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_31))
				जाओ unknown_opcode;
			op->reg = VSX_REGISTER_XTP(rd);
			op->type = MKOP(LOAD_VSX, 0, 32);
			op->element_size = 32;
			अवरोध;

		हाल 364:	/* lxvwsx */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(LOAD_VSX, 0, 4);
			op->element_size = 4;
			op->vsx_flags = VSX_SPLAT | VSX_CHECK_VEC;
			अवरोध;

		हाल 396:	/* stxvx */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(STORE_VSX, 0, 16);
			op->element_size = 16;
			op->vsx_flags = VSX_CHECK_VEC;
			अवरोध;

		हाल 397:	/* stxvl */
		हाल 429: अणु	/* stxvll */
			पूर्णांक nb;
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->reg = rd | ((word & 1) << 5);
			op->ea = ra ? regs->gpr[ra] : 0;
			nb = regs->gpr[rb] & 0xff;
			अगर (nb > 16)
				nb = 16;
			op->type = MKOP(STORE_VSX, 0, nb);
			op->element_size = 16;
			op->vsx_flags = ((word & 0x20) ? VSX_LDLEFT : 0) |
				VSX_CHECK_VEC;
			अवरोध;
		पूर्ण
		हाल 461:       /* stxvpx */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_31))
				जाओ unknown_opcode;
			op->reg = VSX_REGISTER_XTP(rd);
			op->type = MKOP(STORE_VSX, 0, 32);
			op->element_size = 32;
			अवरोध;
		हाल 524:	/* lxsspx */
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(LOAD_VSX, 0, 4);
			op->element_size = 8;
			op->vsx_flags = VSX_FPCONV;
			अवरोध;

		हाल 588:	/* lxsdx */
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(LOAD_VSX, 0, 8);
			op->element_size = 8;
			अवरोध;

		हाल 652:	/* stxsspx */
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(STORE_VSX, 0, 4);
			op->element_size = 8;
			op->vsx_flags = VSX_FPCONV;
			अवरोध;

		हाल 716:	/* stxsdx */
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(STORE_VSX, 0, 8);
			op->element_size = 8;
			अवरोध;

		हाल 780:	/* lxvw4x */
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(LOAD_VSX, 0, 16);
			op->element_size = 4;
			अवरोध;

		हाल 781:	/* lxsibzx */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(LOAD_VSX, 0, 1);
			op->element_size = 8;
			op->vsx_flags = VSX_CHECK_VEC;
			अवरोध;

		हाल 812:	/* lxvh8x */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(LOAD_VSX, 0, 16);
			op->element_size = 2;
			op->vsx_flags = VSX_CHECK_VEC;
			अवरोध;

		हाल 813:	/* lxsihzx */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(LOAD_VSX, 0, 2);
			op->element_size = 8;
			op->vsx_flags = VSX_CHECK_VEC;
			अवरोध;

		हाल 844:	/* lxvd2x */
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(LOAD_VSX, 0, 16);
			op->element_size = 8;
			अवरोध;

		हाल 876:	/* lxvb16x */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(LOAD_VSX, 0, 16);
			op->element_size = 1;
			op->vsx_flags = VSX_CHECK_VEC;
			अवरोध;

		हाल 908:	/* stxvw4x */
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(STORE_VSX, 0, 16);
			op->element_size = 4;
			अवरोध;

		हाल 909:	/* stxsibx */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(STORE_VSX, 0, 1);
			op->element_size = 8;
			op->vsx_flags = VSX_CHECK_VEC;
			अवरोध;

		हाल 940:	/* stxvh8x */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(STORE_VSX, 0, 16);
			op->element_size = 2;
			op->vsx_flags = VSX_CHECK_VEC;
			अवरोध;

		हाल 941:	/* stxsihx */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(STORE_VSX, 0, 2);
			op->element_size = 8;
			op->vsx_flags = VSX_CHECK_VEC;
			अवरोध;

		हाल 972:	/* stxvd2x */
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(STORE_VSX, 0, 16);
			op->element_size = 8;
			अवरोध;

		हाल 1004:	/* stxvb16x */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->reg = rd | ((word & 1) << 5);
			op->type = MKOP(STORE_VSX, 0, 16);
			op->element_size = 1;
			op->vsx_flags = VSX_CHECK_VEC;
			अवरोध;

#पूर्ण_अगर /* CONFIG_VSX */
		पूर्ण
		अवरोध;

	हाल 32:	/* lwz */
	हाल 33:	/* lwzu */
		op->type = MKOP(LOAD, u, 4);
		op->ea = dक्रमm_ea(word, regs);
		अवरोध;

	हाल 34:	/* lbz */
	हाल 35:	/* lbzu */
		op->type = MKOP(LOAD, u, 1);
		op->ea = dक्रमm_ea(word, regs);
		अवरोध;

	हाल 36:	/* stw */
	हाल 37:	/* stwu */
		op->type = MKOP(STORE, u, 4);
		op->ea = dक्रमm_ea(word, regs);
		अवरोध;

	हाल 38:	/* stb */
	हाल 39:	/* stbu */
		op->type = MKOP(STORE, u, 1);
		op->ea = dक्रमm_ea(word, regs);
		अवरोध;

	हाल 40:	/* lhz */
	हाल 41:	/* lhzu */
		op->type = MKOP(LOAD, u, 2);
		op->ea = dक्रमm_ea(word, regs);
		अवरोध;

	हाल 42:	/* lha */
	हाल 43:	/* lhau */
		op->type = MKOP(LOAD, SIGNEXT | u, 2);
		op->ea = dक्रमm_ea(word, regs);
		अवरोध;

	हाल 44:	/* sth */
	हाल 45:	/* sthu */
		op->type = MKOP(STORE, u, 2);
		op->ea = dक्रमm_ea(word, regs);
		अवरोध;

	हाल 46:	/* lmw */
		अगर (ra >= rd)
			अवरोध;		/* invalid क्रमm, ra in range to load */
		op->type = MKOP(LOAD_MULTI, 0, 4 * (32 - rd));
		op->ea = dक्रमm_ea(word, regs);
		अवरोध;

	हाल 47:	/* sपंचांगw */
		op->type = MKOP(STORE_MULTI, 0, 4 * (32 - rd));
		op->ea = dक्रमm_ea(word, regs);
		अवरोध;

#अगर_घोषित CONFIG_PPC_FPU
	हाल 48:	/* lfs */
	हाल 49:	/* lfsu */
		op->type = MKOP(LOAD_FP, u | FPCONV, 4);
		op->ea = dक्रमm_ea(word, regs);
		अवरोध;

	हाल 50:	/* lfd */
	हाल 51:	/* lfdu */
		op->type = MKOP(LOAD_FP, u, 8);
		op->ea = dक्रमm_ea(word, regs);
		अवरोध;

	हाल 52:	/* stfs */
	हाल 53:	/* stfsu */
		op->type = MKOP(STORE_FP, u | FPCONV, 4);
		op->ea = dक्रमm_ea(word, regs);
		अवरोध;

	हाल 54:	/* stfd */
	हाल 55:	/* stfdu */
		op->type = MKOP(STORE_FP, u, 8);
		op->ea = dक्रमm_ea(word, regs);
		अवरोध;
#पूर्ण_अगर

#अगर_घोषित __घातerpc64__
	हाल 56:	/* lq */
		अगर (!((rd & 1) || (rd == ra)))
			op->type = MKOP(LOAD, 0, 16);
		op->ea = dqक्रमm_ea(word, regs);
		अवरोध;
#पूर्ण_अगर

#अगर_घोषित CONFIG_VSX
	हाल 57:	/* lfdp, lxsd, lxssp */
		op->ea = dsक्रमm_ea(word, regs);
		चयन (word & 3) अणु
		हाल 0:		/* lfdp */
			अगर (rd & 1)
				अवरोध;		/* reg must be even */
			op->type = MKOP(LOAD_FP, 0, 16);
			अवरोध;
		हाल 2:		/* lxsd */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->reg = rd + 32;
			op->type = MKOP(LOAD_VSX, 0, 8);
			op->element_size = 8;
			op->vsx_flags = VSX_CHECK_VEC;
			अवरोध;
		हाल 3:		/* lxssp */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->reg = rd + 32;
			op->type = MKOP(LOAD_VSX, 0, 4);
			op->element_size = 8;
			op->vsx_flags = VSX_FPCONV | VSX_CHECK_VEC;
			अवरोध;
		पूर्ण
		अवरोध;
#पूर्ण_अगर /* CONFIG_VSX */

#अगर_घोषित __घातerpc64__
	हाल 58:	/* ld[u], lwa */
		op->ea = dsक्रमm_ea(word, regs);
		चयन (word & 3) अणु
		हाल 0:		/* ld */
			op->type = MKOP(LOAD, 0, 8);
			अवरोध;
		हाल 1:		/* ldu */
			op->type = MKOP(LOAD, UPDATE, 8);
			अवरोध;
		हाल 2:		/* lwa */
			op->type = MKOP(LOAD, SIGNEXT, 4);
			अवरोध;
		पूर्ण
		अवरोध;
#पूर्ण_अगर

#अगर_घोषित CONFIG_VSX
	हाल 6:
		अगर (!cpu_has_feature(CPU_FTR_ARCH_31))
			जाओ unknown_opcode;
		op->ea = dqक्रमm_ea(word, regs);
		op->reg = VSX_REGISTER_XTP(rd);
		op->element_size = 32;
		चयन (word & 0xf) अणु
		हाल 0:         /* lxvp */
			op->type = MKOP(LOAD_VSX, 0, 32);
			अवरोध;
		हाल 1:         /* stxvp */
			op->type = MKOP(STORE_VSX, 0, 32);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 61:	/* stfdp, lxv, stxsd, stxssp, stxv */
		चयन (word & 7) अणु
		हाल 0:		/* stfdp with LSB of DS field = 0 */
		हाल 4:		/* stfdp with LSB of DS field = 1 */
			op->ea = dsक्रमm_ea(word, regs);
			op->type = MKOP(STORE_FP, 0, 16);
			अवरोध;

		हाल 1:		/* lxv */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->ea = dqक्रमm_ea(word, regs);
			अगर (word & 8)
				op->reg = rd + 32;
			op->type = MKOP(LOAD_VSX, 0, 16);
			op->element_size = 16;
			op->vsx_flags = VSX_CHECK_VEC;
			अवरोध;

		हाल 2:		/* stxsd with LSB of DS field = 0 */
		हाल 6:		/* stxsd with LSB of DS field = 1 */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->ea = dsक्रमm_ea(word, regs);
			op->reg = rd + 32;
			op->type = MKOP(STORE_VSX, 0, 8);
			op->element_size = 8;
			op->vsx_flags = VSX_CHECK_VEC;
			अवरोध;

		हाल 3:		/* stxssp with LSB of DS field = 0 */
		हाल 7:		/* stxssp with LSB of DS field = 1 */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->ea = dsक्रमm_ea(word, regs);
			op->reg = rd + 32;
			op->type = MKOP(STORE_VSX, 0, 4);
			op->element_size = 8;
			op->vsx_flags = VSX_FPCONV | VSX_CHECK_VEC;
			अवरोध;

		हाल 5:		/* stxv */
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				जाओ unknown_opcode;
			op->ea = dqक्रमm_ea(word, regs);
			अगर (word & 8)
				op->reg = rd + 32;
			op->type = MKOP(STORE_VSX, 0, 16);
			op->element_size = 16;
			op->vsx_flags = VSX_CHECK_VEC;
			अवरोध;
		पूर्ण
		अवरोध;
#पूर्ण_अगर /* CONFIG_VSX */

#अगर_घोषित __घातerpc64__
	हाल 62:	/* std[u] */
		op->ea = dsक्रमm_ea(word, regs);
		चयन (word & 3) अणु
		हाल 0:		/* std */
			op->type = MKOP(STORE, 0, 8);
			अवरोध;
		हाल 1:		/* stdu */
			op->type = MKOP(STORE, UPDATE, 8);
			अवरोध;
		हाल 2:		/* stq */
			अगर (!(rd & 1))
				op->type = MKOP(STORE, 0, 16);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 1: /* Prefixed inकाष्ठाions */
		अगर (!cpu_has_feature(CPU_FTR_ARCH_31))
			जाओ unknown_opcode;

		prefix_r = GET_PREFIX_R(word);
		ra = GET_PREFIX_RA(suffix);
		op->update_reg = ra;
		rd = (suffix >> 21) & 0x1f;
		op->reg = rd;
		op->val = regs->gpr[rd];

		suffixopcode = get_op(suffix);
		prefixtype = (word >> 24) & 0x3;
		चयन (prefixtype) अणु
		हाल 0: /* Type 00  Eight-Byte Load/Store */
			अगर (prefix_r && ra)
				अवरोध;
			op->ea = mlsd_8lsd_ea(word, suffix, regs);
			चयन (suffixopcode) अणु
			हाल 41:	/* plwa */
				op->type = MKOP(LOAD, PREFIXED | SIGNEXT, 4);
				अवरोध;
#अगर_घोषित CONFIG_VSX
			हाल 42:        /* plxsd */
				op->reg = rd + 32;
				op->type = MKOP(LOAD_VSX, PREFIXED, 8);
				op->element_size = 8;
				op->vsx_flags = VSX_CHECK_VEC;
				अवरोध;
			हाल 43:	/* plxssp */
				op->reg = rd + 32;
				op->type = MKOP(LOAD_VSX, PREFIXED, 4);
				op->element_size = 8;
				op->vsx_flags = VSX_FPCONV | VSX_CHECK_VEC;
				अवरोध;
			हाल 46:	/* pstxsd */
				op->reg = rd + 32;
				op->type = MKOP(STORE_VSX, PREFIXED, 8);
				op->element_size = 8;
				op->vsx_flags = VSX_CHECK_VEC;
				अवरोध;
			हाल 47:	/* pstxssp */
				op->reg = rd + 32;
				op->type = MKOP(STORE_VSX, PREFIXED, 4);
				op->element_size = 8;
				op->vsx_flags = VSX_FPCONV | VSX_CHECK_VEC;
				अवरोध;
			हाल 51:	/* plxv1 */
				op->reg += 32;
				fallthrough;
			हाल 50:	/* plxv0 */
				op->type = MKOP(LOAD_VSX, PREFIXED, 16);
				op->element_size = 16;
				op->vsx_flags = VSX_CHECK_VEC;
				अवरोध;
			हाल 55:	/* pstxv1 */
				op->reg = rd + 32;
				fallthrough;
			हाल 54:	/* pstxv0 */
				op->type = MKOP(STORE_VSX, PREFIXED, 16);
				op->element_size = 16;
				op->vsx_flags = VSX_CHECK_VEC;
				अवरोध;
#पूर्ण_अगर /* CONFIG_VSX */
			हाल 56:        /* plq */
				op->type = MKOP(LOAD, PREFIXED, 16);
				अवरोध;
			हाल 57:	/* pld */
				op->type = MKOP(LOAD, PREFIXED, 8);
				अवरोध;
#अगर_घोषित CONFIG_VSX
			हाल 58:        /* plxvp */
				op->reg = VSX_REGISTER_XTP(rd);
				op->type = MKOP(LOAD_VSX, PREFIXED, 32);
				op->element_size = 32;
				अवरोध;
#पूर्ण_अगर /* CONFIG_VSX */
			हाल 60:        /* pstq */
				op->type = MKOP(STORE, PREFIXED, 16);
				अवरोध;
			हाल 61:	/* pstd */
				op->type = MKOP(STORE, PREFIXED, 8);
				अवरोध;
#अगर_घोषित CONFIG_VSX
			हाल 62:        /* pstxvp */
				op->reg = VSX_REGISTER_XTP(rd);
				op->type = MKOP(STORE_VSX, PREFIXED, 32);
				op->element_size = 32;
				अवरोध;
#पूर्ण_अगर /* CONFIG_VSX */
			पूर्ण
			अवरोध;
		हाल 1: /* Type 01 Eight-Byte Register-to-Register */
			अवरोध;
		हाल 2: /* Type 10 Modअगरied Load/Store */
			अगर (prefix_r && ra)
				अवरोध;
			op->ea = mlsd_8lsd_ea(word, suffix, regs);
			चयन (suffixopcode) अणु
			हाल 32:	/* plwz */
				op->type = MKOP(LOAD, PREFIXED, 4);
				अवरोध;
			हाल 34:	/* plbz */
				op->type = MKOP(LOAD, PREFIXED, 1);
				अवरोध;
			हाल 36:	/* pstw */
				op->type = MKOP(STORE, PREFIXED, 4);
				अवरोध;
			हाल 38:	/* pstb */
				op->type = MKOP(STORE, PREFIXED, 1);
				अवरोध;
			हाल 40:	/* plhz */
				op->type = MKOP(LOAD, PREFIXED, 2);
				अवरोध;
			हाल 42:	/* plha */
				op->type = MKOP(LOAD, PREFIXED | SIGNEXT, 2);
				अवरोध;
			हाल 44:	/* psth */
				op->type = MKOP(STORE, PREFIXED, 2);
				अवरोध;
			हाल 48:        /* plfs */
				op->type = MKOP(LOAD_FP, PREFIXED | FPCONV, 4);
				अवरोध;
			हाल 50:        /* plfd */
				op->type = MKOP(LOAD_FP, PREFIXED, 8);
				अवरोध;
			हाल 52:        /* pstfs */
				op->type = MKOP(STORE_FP, PREFIXED | FPCONV, 4);
				अवरोध;
			हाल 54:        /* pstfd */
				op->type = MKOP(STORE_FP, PREFIXED, 8);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 3: /* Type 11 Modअगरied Register-to-Register */
			अवरोध;
		पूर्ण
#पूर्ण_अगर /* __घातerpc64__ */

	पूर्ण

	अगर (OP_IS_LOAD_STORE(op->type) && (op->type & UPDATE)) अणु
		चयन (GETTYPE(op->type)) अणु
		हाल LOAD:
			अगर (ra == rd)
				जाओ unknown_opcode;
			fallthrough;
		हाल STORE:
		हाल LOAD_FP:
		हाल STORE_FP:
			अगर (ra == 0)
				जाओ unknown_opcode;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_VSX
	अगर ((GETTYPE(op->type) == LOAD_VSX ||
	     GETTYPE(op->type) == STORE_VSX) &&
	    !cpu_has_feature(CPU_FTR_VSX)) अणु
		वापस -1;
	पूर्ण
#पूर्ण_अगर /* CONFIG_VSX */

	वापस 0;

 unknown_opcode:
	op->type = UNKNOWN;
	वापस 0;

 logical_करोne:
	अगर (word & 1)
		set_cr0(regs, op);
 logical_करोne_nocc:
	op->reg = ra;
	op->type |= SETREG;
	वापस 1;

 arith_करोne:
	अगर (word & 1)
		set_cr0(regs, op);
 compute_करोne:
	op->reg = rd;
	op->type |= SETREG;
	वापस 1;

 priv:
	op->type = INTERRUPT | 0x700;
	op->val = SRR1_PROGPRIV;
	वापस 0;

 trap:
	op->type = INTERRUPT | 0x700;
	op->val = SRR1_PROGTRAP;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(analyse_instr);
NOKPROBE_SYMBOL(analyse_instr);

/*
 * For PPC32 we always use stwu with r1 to change the stack poपूर्णांकer.
 * So this emulated store may corrupt the exception frame, now we
 * have to provide the exception frame trampoline, which is pushed
 * below the kprobed function stack. So we only update gpr[1] but
 * करोn't emulate the real store operation. We will करो real store
 * operation safely in exception वापस code by checking this flag.
 */
अटल nokprobe_अंतरभूत पूर्णांक handle_stack_update(अचिन्हित दीर्घ ea, काष्ठा pt_regs *regs)
अणु
	/*
	 * Check अगर we alपढ़ोy set since that means we'll
	 * lose the previous value.
	 */
	WARN_ON(test_thपढ़ो_flag(TIF_EMULATE_STACK_STORE));
	set_thपढ़ो_flag(TIF_EMULATE_STACK_STORE);
	वापस 0;
पूर्ण

अटल nokprobe_अंतरभूत व्योम करो_signext(अचिन्हित दीर्घ *valp, पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 2:
		*valp = (चिन्हित लघु) *valp;
		अवरोध;
	हाल 4:
		*valp = (चिन्हित पूर्णांक) *valp;
		अवरोध;
	पूर्ण
पूर्ण

अटल nokprobe_अंतरभूत व्योम करो_byterev(अचिन्हित दीर्घ *valp, पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 2:
		*valp = byterev_2(*valp);
		अवरोध;
	हाल 4:
		*valp = byterev_4(*valp);
		अवरोध;
#अगर_घोषित __घातerpc64__
	हाल 8:
		*valp = byterev_8(*valp);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण

/*
 * Emulate an inकाष्ठाion that can be executed just by updating
 * fields in *regs.
 */
व्योम emulate_update_regs(काष्ठा pt_regs *regs, काष्ठा inकाष्ठाion_op *op)
अणु
	अचिन्हित दीर्घ next_pc;

	next_pc = truncate_अगर_32bit(regs->msr, regs->nip + GETLENGTH(op->type));
	चयन (GETTYPE(op->type)) अणु
	हाल COMPUTE:
		अगर (op->type & SETREG)
			regs->gpr[op->reg] = op->val;
		अगर (op->type & SETCC)
			regs->ccr = op->ccval;
		अगर (op->type & SETXER)
			regs->xer = op->xerval;
		अवरोध;

	हाल BRANCH:
		अगर (op->type & SETLK)
			regs->link = next_pc;
		अगर (op->type & BRTAKEN)
			next_pc = op->val;
		अगर (op->type & DECCTR)
			--regs->ctr;
		अवरोध;

	हाल BARRIER:
		चयन (op->type & BARRIER_MASK) अणु
		हाल BARRIER_SYNC:
			mb();
			अवरोध;
		हाल BARRIER_ISYNC:
			isync();
			अवरोध;
		हाल BARRIER_EIEIO:
			eieio();
			अवरोध;
		हाल BARRIER_LWSYNC:
			यंत्र अस्थिर("lwsync" : : : "memory");
			अवरोध;
		हाल BARRIER_PTESYNC:
			यंत्र अस्थिर("ptesync" : : : "memory");
			अवरोध;
		पूर्ण
		अवरोध;

	हाल MFSPR:
		चयन (op->spr) अणु
		हाल SPRN_XER:
			regs->gpr[op->reg] = regs->xer & 0xffffffffUL;
			अवरोध;
		हाल SPRN_LR:
			regs->gpr[op->reg] = regs->link;
			अवरोध;
		हाल SPRN_CTR:
			regs->gpr[op->reg] = regs->ctr;
			अवरोध;
		शेष:
			WARN_ON_ONCE(1);
		पूर्ण
		अवरोध;

	हाल MTSPR:
		चयन (op->spr) अणु
		हाल SPRN_XER:
			regs->xer = op->val & 0xffffffffUL;
			अवरोध;
		हाल SPRN_LR:
			regs->link = op->val;
			अवरोध;
		हाल SPRN_CTR:
			regs->ctr = op->val;
			अवरोध;
		शेष:
			WARN_ON_ONCE(1);
		पूर्ण
		अवरोध;

	शेष:
		WARN_ON_ONCE(1);
	पूर्ण
	regs->nip = next_pc;
पूर्ण
NOKPROBE_SYMBOL(emulate_update_regs);

/*
 * Emulate a previously-analysed load or store inकाष्ठाion.
 * Return values are:
 * 0 = inकाष्ठाion emulated successfully
 * -EFAULT = address out of range or access faulted (regs->dar
 *	     contains the faulting address)
 * -EACCES = misaligned access, inकाष्ठाion requires alignment
 * -EINVAL = unknown operation in *op
 */
पूर्णांक emulate_loadstore(काष्ठा pt_regs *regs, काष्ठा inकाष्ठाion_op *op)
अणु
	पूर्णांक err, size, type;
	पूर्णांक i, rd, nb;
	अचिन्हित पूर्णांक cr;
	अचिन्हित दीर्घ val;
	अचिन्हित दीर्घ ea;
	bool cross_endian;

	err = 0;
	size = GETSIZE(op->type);
	type = GETTYPE(op->type);
	cross_endian = (regs->msr & MSR_LE) != (MSR_KERNEL & MSR_LE);
	ea = truncate_अगर_32bit(regs->msr, op->ea);

	चयन (type) अणु
	हाल LARX:
		अगर (ea & (size - 1))
			वापस -EACCES;		/* can't handle misaligned */
		अगर (!address_ok(regs, ea, size))
			वापस -EFAULT;
		err = 0;
		val = 0;
		चयन (size) अणु
#अगर_घोषित __घातerpc64__
		हाल 1:
			__get_user_यंत्रx(val, ea, err, "lbarx");
			अवरोध;
		हाल 2:
			__get_user_यंत्रx(val, ea, err, "lharx");
			अवरोध;
#पूर्ण_अगर
		हाल 4:
			__get_user_यंत्रx(val, ea, err, "lwarx");
			अवरोध;
#अगर_घोषित __घातerpc64__
		हाल 8:
			__get_user_यंत्रx(val, ea, err, "ldarx");
			अवरोध;
		हाल 16:
			err = करो_lqarx(ea, &regs->gpr[op->reg]);
			अवरोध;
#पूर्ण_अगर
		शेष:
			वापस -EINVAL;
		पूर्ण
		अगर (err) अणु
			regs->dar = ea;
			अवरोध;
		पूर्ण
		अगर (size < 16)
			regs->gpr[op->reg] = val;
		अवरोध;

	हाल STCX:
		अगर (ea & (size - 1))
			वापस -EACCES;		/* can't handle misaligned */
		अगर (!address_ok(regs, ea, size))
			वापस -EFAULT;
		err = 0;
		चयन (size) अणु
#अगर_घोषित __घातerpc64__
		हाल 1:
			__put_user_यंत्रx(op->val, ea, err, "stbcx.", cr);
			अवरोध;
		हाल 2:
			__put_user_यंत्रx(op->val, ea, err, "stbcx.", cr);
			अवरोध;
#पूर्ण_अगर
		हाल 4:
			__put_user_यंत्रx(op->val, ea, err, "stwcx.", cr);
			अवरोध;
#अगर_घोषित __घातerpc64__
		हाल 8:
			__put_user_यंत्रx(op->val, ea, err, "stdcx.", cr);
			अवरोध;
		हाल 16:
			err = करो_stqcx(ea, regs->gpr[op->reg],
				       regs->gpr[op->reg + 1], &cr);
			अवरोध;
#पूर्ण_अगर
		शेष:
			वापस -EINVAL;
		पूर्ण
		अगर (!err)
			regs->ccr = (regs->ccr & 0x0fffffff) |
				(cr & 0xe0000000) |
				((regs->xer >> 3) & 0x10000000);
		अन्यथा
			regs->dar = ea;
		अवरोध;

	हाल LOAD:
#अगर_घोषित __घातerpc64__
		अगर (size == 16) अणु
			err = emulate_lq(regs, ea, op->reg, cross_endian);
			अवरोध;
		पूर्ण
#पूर्ण_अगर
		err = पढ़ो_mem(&regs->gpr[op->reg], ea, size, regs);
		अगर (!err) अणु
			अगर (op->type & SIGNEXT)
				करो_signext(&regs->gpr[op->reg], size);
			अगर ((op->type & BYTEREV) == (cross_endian ? 0 : BYTEREV))
				करो_byterev(&regs->gpr[op->reg], size);
		पूर्ण
		अवरोध;

#अगर_घोषित CONFIG_PPC_FPU
	हाल LOAD_FP:
		/*
		 * If the inकाष्ठाion is in userspace, we can emulate it even
		 * अगर the VMX state is not live, because we have the state
		 * stored in the thपढ़ो_काष्ठा.  If the inकाष्ठाion is in
		 * the kernel, we must not touch the state in the thपढ़ो_काष्ठा.
		 */
		अगर (!(regs->msr & MSR_PR) && !(regs->msr & MSR_FP))
			वापस 0;
		err = करो_fp_load(op, ea, regs, cross_endian);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ALTIVEC
	हाल LOAD_VMX:
		अगर (!(regs->msr & MSR_PR) && !(regs->msr & MSR_VEC))
			वापस 0;
		err = करो_vec_load(op->reg, ea, size, regs, cross_endian);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_VSX
	हाल LOAD_VSX: अणु
		अचिन्हित दीर्घ msrbit = MSR_VSX;

		/*
		 * Some VSX inकाष्ठाions check the MSR_VEC bit rather than MSR_VSX
		 * when the target of the inकाष्ठाion is a vector रेजिस्टर.
		 */
		अगर (op->reg >= 32 && (op->vsx_flags & VSX_CHECK_VEC))
			msrbit = MSR_VEC;
		अगर (!(regs->msr & MSR_PR) && !(regs->msr & msrbit))
			वापस 0;
		err = करो_vsx_load(op, ea, regs, cross_endian);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	हाल LOAD_MULTI:
		अगर (!address_ok(regs, ea, size))
			वापस -EFAULT;
		rd = op->reg;
		क्रम (i = 0; i < size; i += 4) अणु
			अचिन्हित पूर्णांक v32 = 0;

			nb = size - i;
			अगर (nb > 4)
				nb = 4;
			err = copy_mem_in((u8 *) &v32, ea, nb, regs);
			अगर (err)
				अवरोध;
			अगर (unlikely(cross_endian))
				v32 = byterev_4(v32);
			regs->gpr[rd] = v32;
			ea += 4;
			/* reg number wraps from 31 to 0 क्रम lsw[ix] */
			rd = (rd + 1) & 0x1f;
		पूर्ण
		अवरोध;

	हाल STORE:
#अगर_घोषित __घातerpc64__
		अगर (size == 16) अणु
			err = emulate_stq(regs, ea, op->reg, cross_endian);
			अवरोध;
		पूर्ण
#पूर्ण_अगर
		अगर ((op->type & UPDATE) && size == माप(दीर्घ) &&
		    op->reg == 1 && op->update_reg == 1 &&
		    !(regs->msr & MSR_PR) &&
		    ea >= regs->gpr[1] - STACK_INT_FRAME_SIZE) अणु
			err = handle_stack_update(ea, regs);
			अवरोध;
		पूर्ण
		अगर (unlikely(cross_endian))
			करो_byterev(&op->val, size);
		err = ग_लिखो_mem(op->val, ea, size, regs);
		अवरोध;

#अगर_घोषित CONFIG_PPC_FPU
	हाल STORE_FP:
		अगर (!(regs->msr & MSR_PR) && !(regs->msr & MSR_FP))
			वापस 0;
		err = करो_fp_store(op, ea, regs, cross_endian);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ALTIVEC
	हाल STORE_VMX:
		अगर (!(regs->msr & MSR_PR) && !(regs->msr & MSR_VEC))
			वापस 0;
		err = करो_vec_store(op->reg, ea, size, regs, cross_endian);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_VSX
	हाल STORE_VSX: अणु
		अचिन्हित दीर्घ msrbit = MSR_VSX;

		/*
		 * Some VSX inकाष्ठाions check the MSR_VEC bit rather than MSR_VSX
		 * when the target of the inकाष्ठाion is a vector रेजिस्टर.
		 */
		अगर (op->reg >= 32 && (op->vsx_flags & VSX_CHECK_VEC))
			msrbit = MSR_VEC;
		अगर (!(regs->msr & MSR_PR) && !(regs->msr & msrbit))
			वापस 0;
		err = करो_vsx_store(op, ea, regs, cross_endian);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	हाल STORE_MULTI:
		अगर (!address_ok(regs, ea, size))
			वापस -EFAULT;
		rd = op->reg;
		क्रम (i = 0; i < size; i += 4) अणु
			अचिन्हित पूर्णांक v32 = regs->gpr[rd];

			nb = size - i;
			अगर (nb > 4)
				nb = 4;
			अगर (unlikely(cross_endian))
				v32 = byterev_4(v32);
			err = copy_mem_out((u8 *) &v32, ea, nb, regs);
			अगर (err)
				अवरोध;
			ea += 4;
			/* reg number wraps from 31 to 0 क्रम stsw[ix] */
			rd = (rd + 1) & 0x1f;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (err)
		वापस err;

	अगर (op->type & UPDATE)
		regs->gpr[op->update_reg] = op->ea;

	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(emulate_loadstore);

/*
 * Emulate inकाष्ठाions that cause a transfer of control,
 * loads and stores, and a few other inकाष्ठाions.
 * Returns 1 अगर the step was emulated, 0 अगर not,
 * or -1 अगर the inकाष्ठाion is one that should not be stepped,
 * such as an rfid, or a mपंचांगsrd that would clear MSR_RI.
 */
पूर्णांक emulate_step(काष्ठा pt_regs *regs, काष्ठा ppc_inst instr)
अणु
	काष्ठा inकाष्ठाion_op op;
	पूर्णांक r, err, type;
	अचिन्हित दीर्घ val;
	अचिन्हित दीर्घ ea;

	r = analyse_instr(&op, regs, instr);
	अगर (r < 0)
		वापस r;
	अगर (r > 0) अणु
		emulate_update_regs(regs, &op);
		वापस 1;
	पूर्ण

	err = 0;
	type = GETTYPE(op.type);

	अगर (OP_IS_LOAD_STORE(type)) अणु
		err = emulate_loadstore(regs, &op);
		अगर (err)
			वापस 0;
		जाओ instr_करोne;
	पूर्ण

	चयन (type) अणु
	हाल CACHEOP:
		ea = truncate_अगर_32bit(regs->msr, op.ea);
		अगर (!address_ok(regs, ea, 8))
			वापस 0;
		चयन (op.type & CACHEOP_MASK) अणु
		हाल DCBST:
			__cacheop_user_यंत्रx(ea, err, "dcbst");
			अवरोध;
		हाल DCBF:
			__cacheop_user_यंत्रx(ea, err, "dcbf");
			अवरोध;
		हाल DCBTST:
			अगर (op.reg == 0)
				prefetchw((व्योम *) ea);
			अवरोध;
		हाल DCBT:
			अगर (op.reg == 0)
				prefetch((व्योम *) ea);
			अवरोध;
		हाल ICBI:
			__cacheop_user_यंत्रx(ea, err, "icbi");
			अवरोध;
		हाल DCBZ:
			err = emulate_dcbz(ea, regs);
			अवरोध;
		पूर्ण
		अगर (err) अणु
			regs->dar = ea;
			वापस 0;
		पूर्ण
		जाओ instr_करोne;

	हाल MFMSR:
		regs->gpr[op.reg] = regs->msr & MSR_MASK;
		जाओ instr_करोne;

	हाल MTMSR:
		val = regs->gpr[op.reg];
		अगर ((val & MSR_RI) == 0)
			/* can't step mपंचांगsr[d] that would clear MSR_RI */
			वापस -1;
		/* here op.val is the mask of bits to change */
		regs->msr = (regs->msr & ~op.val) | (val & op.val);
		जाओ instr_करोne;

#अगर_घोषित CONFIG_PPC64
	हाल SYSCALL:	/* sc */
		/*
		 * N.B. this uses knowledge about how the syscall
		 * entry code works.  If that is changed, this will
		 * need to be changed also.
		 */
		अगर (IS_ENABLED(CONFIG_PPC_FAST_ENDIAN_SWITCH) &&
				cpu_has_feature(CPU_FTR_REAL_LE) &&
				regs->gpr[0] == 0x1ebe) अणु
			regs->msr ^= MSR_LE;
			जाओ instr_करोne;
		पूर्ण
		regs->gpr[9] = regs->gpr[13];
		regs->gpr[10] = MSR_KERNEL;
		regs->gpr[11] = regs->nip + 4;
		regs->gpr[12] = regs->msr & MSR_MASK;
		regs->gpr[13] = (अचिन्हित दीर्घ) get_paca();
		regs->nip = (अचिन्हित दीर्घ) &प्रणाली_call_common;
		regs->msr = MSR_KERNEL;
		वापस 1;

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	हाल SYSCALL_VECTORED_0:	/* scv 0 */
		regs->gpr[9] = regs->gpr[13];
		regs->gpr[10] = MSR_KERNEL;
		regs->gpr[11] = regs->nip + 4;
		regs->gpr[12] = regs->msr & MSR_MASK;
		regs->gpr[13] = (अचिन्हित दीर्घ) get_paca();
		regs->nip = (अचिन्हित दीर्घ) &प्रणाली_call_vectored_emulate;
		regs->msr = MSR_KERNEL;
		वापस 1;
#पूर्ण_अगर

	हाल RFI:
		वापस -1;
#पूर्ण_अगर
	पूर्ण
	वापस 0;

 instr_करोne:
	regs->nip = truncate_अगर_32bit(regs->msr, regs->nip + GETLENGTH(op.type));
	वापस 1;
पूर्ण
NOKPROBE_SYMBOL(emulate_step);
