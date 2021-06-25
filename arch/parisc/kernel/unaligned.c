<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *    Unaligned memory access handler
 *
 *    Copyright (C) 2001 Ranकरोlph Chung <tausq@debian.org>
 *    Signअगरicantly tweaked by LaMont Jones <lamont@debian.org>
 */

#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/debug.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/ratelimit.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/hardirq.h>
#समावेश <यंत्र/traps.h>

/* #घोषणा DEBUG_UNALIGNED 1 */

#अगर_घोषित DEBUG_UNALIGNED
#घोषणा DPRINTF(fmt, args...) करो अणु prपूर्णांकk(KERN_DEBUG "%s:%d:%s ", __खाता__, __LINE__, __func__ ); prपूर्णांकk(KERN_DEBUG fmt, ##args ); पूर्ण जबतक (0)
#अन्यथा
#घोषणा DPRINTF(fmt, args...)
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
#घोषणा RFMT "%016lx"
#अन्यथा
#घोषणा RFMT "%08lx"
#पूर्ण_अगर

#घोषणा FIXUP_BRANCH(lbl) \
	"\tldil L%%" #lbl ", %%r1\n"			\
	"\tldo R%%" #lbl "(%%r1), %%r1\n"		\
	"\tbv,n %%r0(%%r1)\n"
/* If you use FIXUP_BRANCH, then you must list this clobber */
#घोषणा FIXUP_BRANCH_CLOBBER "r1"

/* 1111 1100 0000 0000 0001 0011 1100 0000 */
#घोषणा OPCODE1(a,b,c)	((a)<<26|(b)<<12|(c)<<6) 
#घोषणा OPCODE2(a,b)	((a)<<26|(b)<<1)
#घोषणा OPCODE3(a,b)	((a)<<26|(b)<<2)
#घोषणा OPCODE4(a)	((a)<<26)
#घोषणा OPCODE1_MASK	OPCODE1(0x3f,1,0xf)
#घोषणा OPCODE2_MASK 	OPCODE2(0x3f,1)
#घोषणा OPCODE3_MASK	OPCODE3(0x3f,1)
#घोषणा OPCODE4_MASK    OPCODE4(0x3f)

/* skip LDB - never unaligned (index) */
#घोषणा OPCODE_LDH_I	OPCODE1(0x03,0,0x1)
#घोषणा OPCODE_LDW_I	OPCODE1(0x03,0,0x2)
#घोषणा OPCODE_LDD_I	OPCODE1(0x03,0,0x3)
#घोषणा OPCODE_LDDA_I	OPCODE1(0x03,0,0x4)
#घोषणा OPCODE_LDCD_I	OPCODE1(0x03,0,0x5)
#घोषणा OPCODE_LDWA_I	OPCODE1(0x03,0,0x6)
#घोषणा OPCODE_LDCW_I	OPCODE1(0x03,0,0x7)
/* skip LDB - never unaligned (लघु) */
#घोषणा OPCODE_LDH_S	OPCODE1(0x03,1,0x1)
#घोषणा OPCODE_LDW_S	OPCODE1(0x03,1,0x2)
#घोषणा OPCODE_LDD_S	OPCODE1(0x03,1,0x3)
#घोषणा OPCODE_LDDA_S	OPCODE1(0x03,1,0x4)
#घोषणा OPCODE_LDCD_S	OPCODE1(0x03,1,0x5)
#घोषणा OPCODE_LDWA_S	OPCODE1(0x03,1,0x6)
#घोषणा OPCODE_LDCW_S	OPCODE1(0x03,1,0x7)
/* skip STB - never unaligned */
#घोषणा OPCODE_STH	OPCODE1(0x03,1,0x9)
#घोषणा OPCODE_STW	OPCODE1(0x03,1,0xa)
#घोषणा OPCODE_STD	OPCODE1(0x03,1,0xb)
/* skip STBY - never unaligned */
/* skip STDBY - never unaligned */
#घोषणा OPCODE_STWA	OPCODE1(0x03,1,0xe)
#घोषणा OPCODE_STDA	OPCODE1(0x03,1,0xf)

#घोषणा OPCODE_FLDWX	OPCODE1(0x09,0,0x0)
#घोषणा OPCODE_FLDWXR	OPCODE1(0x09,0,0x1)
#घोषणा OPCODE_FSTWX	OPCODE1(0x09,0,0x8)
#घोषणा OPCODE_FSTWXR	OPCODE1(0x09,0,0x9)
#घोषणा OPCODE_FLDWS	OPCODE1(0x09,1,0x0)
#घोषणा OPCODE_FLDWSR	OPCODE1(0x09,1,0x1)
#घोषणा OPCODE_FSTWS	OPCODE1(0x09,1,0x8)
#घोषणा OPCODE_FSTWSR	OPCODE1(0x09,1,0x9)
#घोषणा OPCODE_FLDDX	OPCODE1(0x0b,0,0x0)
#घोषणा OPCODE_FSTDX	OPCODE1(0x0b,0,0x8)
#घोषणा OPCODE_FLDDS	OPCODE1(0x0b,1,0x0)
#घोषणा OPCODE_FSTDS	OPCODE1(0x0b,1,0x8)

#घोषणा OPCODE_LDD_L	OPCODE2(0x14,0)
#घोषणा OPCODE_FLDD_L	OPCODE2(0x14,1)
#घोषणा OPCODE_STD_L	OPCODE2(0x1c,0)
#घोषणा OPCODE_FSTD_L	OPCODE2(0x1c,1)

#घोषणा OPCODE_LDW_M	OPCODE3(0x17,1)
#घोषणा OPCODE_FLDW_L	OPCODE3(0x17,0)
#घोषणा OPCODE_FSTW_L	OPCODE3(0x1f,0)
#घोषणा OPCODE_STW_M	OPCODE3(0x1f,1)

#घोषणा OPCODE_LDH_L    OPCODE4(0x11)
#घोषणा OPCODE_LDW_L    OPCODE4(0x12)
#घोषणा OPCODE_LDWM     OPCODE4(0x13)
#घोषणा OPCODE_STH_L    OPCODE4(0x19)
#घोषणा OPCODE_STW_L    OPCODE4(0x1A)
#घोषणा OPCODE_STWM     OPCODE4(0x1B)

#घोषणा MAJOR_OP(i) (((i)>>26)&0x3f)
#घोषणा R1(i) (((i)>>21)&0x1f)
#घोषणा R2(i) (((i)>>16)&0x1f)
#घोषणा R3(i) ((i)&0x1f)
#घोषणा FR3(i) ((((i)<<1)&0x1f)|(((i)>>6)&1))
#घोषणा IM(i,n) (((i)>>1&((1<<(n-1))-1))|((i)&1?((0-1L)<<(n-1)):0))
#घोषणा IM5_2(i) IM((i)>>16,5)
#घोषणा IM5_3(i) IM((i),5)
#घोषणा IM14(i) IM((i),14)

#घोषणा ERR_NOTHANDLED	-1
#घोषणा ERR_PAGEFAULT	-2

पूर्णांक unaligned_enabled __पढ़ो_mostly = 1;

अटल पूर्णांक emulate_ldh(काष्ठा pt_regs *regs, पूर्णांक toreg)
अणु
	अचिन्हित दीर्घ saddr = regs->ior;
	अचिन्हित दीर्घ val = 0;
	पूर्णांक ret;

	DPRINTF("load " RFMT ":" RFMT " to r%d for 2 bytes\n", 
		regs->isr, regs->ior, toreg);

	__यंत्र__ __अस्थिर__  (
"	mtsp	%4, %%sr1\n"
"1:	ldbs	0(%%sr1,%3), %%r20\n"
"2:	ldbs	1(%%sr1,%3), %0\n"
"	depw	%%r20, 23, 24, %0\n"
"	copy	%%r0, %1\n"
"3:	\n"
"	.section .fixup,\"ax\"\n"
"4:	ldi	-2, %1\n"
	FIXUP_BRANCH(3b)
"	.previous\n"
	ASM_EXCEPTIONTABLE_ENTRY(1b, 4b)
	ASM_EXCEPTIONTABLE_ENTRY(2b, 4b)
	: "=r" (val), "=r" (ret)
	: "0" (val), "r" (saddr), "r" (regs->isr)
	: "r20", FIXUP_BRANCH_CLOBBER );

	DPRINTF("val = 0x" RFMT "\n", val);

	अगर (toreg)
		regs->gr[toreg] = val;

	वापस ret;
पूर्ण

अटल पूर्णांक emulate_ldw(काष्ठा pt_regs *regs, पूर्णांक toreg, पूर्णांक flop)
अणु
	अचिन्हित दीर्घ saddr = regs->ior;
	अचिन्हित दीर्घ val = 0;
	पूर्णांक ret;

	DPRINTF("load " RFMT ":" RFMT " to r%d for 4 bytes\n", 
		regs->isr, regs->ior, toreg);

	__यंत्र__ __अस्थिर__  (
"	zdep	%3,28,2,%%r19\n"		/* r19=(ofs&3)*8 */
"	mtsp	%4, %%sr1\n"
"	depw	%%r0,31,2,%3\n"
"1:	ldw	0(%%sr1,%3),%0\n"
"2:	ldw	4(%%sr1,%3),%%r20\n"
"	subi	32,%%r19,%%r19\n"
"	mtctl	%%r19,11\n"
"	vshd	%0,%%r20,%0\n"
"	copy	%%r0, %1\n"
"3:	\n"
"	.section .fixup,\"ax\"\n"
"4:	ldi	-2, %1\n"
	FIXUP_BRANCH(3b)
"	.previous\n"
	ASM_EXCEPTIONTABLE_ENTRY(1b, 4b)
	ASM_EXCEPTIONTABLE_ENTRY(2b, 4b)
	: "=r" (val), "=r" (ret)
	: "0" (val), "r" (saddr), "r" (regs->isr)
	: "r19", "r20", FIXUP_BRANCH_CLOBBER );

	DPRINTF("val = 0x" RFMT "\n", val);

	अगर (flop)
		((__u32*)(regs->fr))[toreg] = val;
	अन्यथा अगर (toreg)
		regs->gr[toreg] = val;

	वापस ret;
पूर्ण
अटल पूर्णांक emulate_ldd(काष्ठा pt_regs *regs, पूर्णांक toreg, पूर्णांक flop)
अणु
	अचिन्हित दीर्घ saddr = regs->ior;
	__u64 val = 0;
	पूर्णांक ret;

	DPRINTF("load " RFMT ":" RFMT " to r%d for 8 bytes\n", 
		regs->isr, regs->ior, toreg);
#अगर_घोषित CONFIG_PA20

#अगर_अघोषित CONFIG_64BIT
	अगर (!flop)
		वापस -1;
#पूर्ण_अगर
	__यंत्र__ __अस्थिर__  (
"	depd,z	%3,60,3,%%r19\n"		/* r19=(ofs&7)*8 */
"	mtsp	%4, %%sr1\n"
"	depd	%%r0,63,3,%3\n"
"1:	ldd	0(%%sr1,%3),%0\n"
"2:	ldd	8(%%sr1,%3),%%r20\n"
"	subi	64,%%r19,%%r19\n"
"	mtsar	%%r19\n"
"	shrpd	%0,%%r20,%%sar,%0\n"
"	copy	%%r0, %1\n"
"3:	\n"
"	.section .fixup,\"ax\"\n"
"4:	ldi	-2, %1\n"
	FIXUP_BRANCH(3b)
"	.previous\n"
	ASM_EXCEPTIONTABLE_ENTRY(1b,4b)
	ASM_EXCEPTIONTABLE_ENTRY(2b,4b)
	: "=r" (val), "=r" (ret)
	: "0" (val), "r" (saddr), "r" (regs->isr)
	: "r19", "r20", FIXUP_BRANCH_CLOBBER );
#अन्यथा
    अणु
	अचिन्हित दीर्घ valh=0,vall=0;
	__यंत्र__ __अस्थिर__  (
"	zdep	%5,29,2,%%r19\n"		/* r19=(ofs&3)*8 */
"	mtsp	%6, %%sr1\n"
"	dep	%%r0,31,2,%5\n"
"1:	ldw	0(%%sr1,%5),%0\n"
"2:	ldw	4(%%sr1,%5),%1\n"
"3:	ldw	8(%%sr1,%5),%%r20\n"
"	subi	32,%%r19,%%r19\n"
"	mtsar	%%r19\n"
"	vshd	%0,%1,%0\n"
"	vshd	%1,%%r20,%1\n"
"	copy	%%r0, %2\n"
"4:	\n"
"	.section .fixup,\"ax\"\n"
"5:	ldi	-2, %2\n"
	FIXUP_BRANCH(4b)
"	.previous\n"
	ASM_EXCEPTIONTABLE_ENTRY(1b,5b)
	ASM_EXCEPTIONTABLE_ENTRY(2b,5b)
	ASM_EXCEPTIONTABLE_ENTRY(3b,5b)
	: "=r" (valh), "=r" (vall), "=r" (ret)
	: "0" (valh), "1" (vall), "r" (saddr), "r" (regs->isr)
	: "r19", "r20", FIXUP_BRANCH_CLOBBER );
	val=((__u64)valh<<32)|(__u64)vall;
    पूर्ण
#पूर्ण_अगर

	DPRINTF("val = 0x%llx\n", val);

	अगर (flop)
		regs->fr[toreg] = val;
	अन्यथा अगर (toreg)
		regs->gr[toreg] = val;

	वापस ret;
पूर्ण

अटल पूर्णांक emulate_sth(काष्ठा pt_regs *regs, पूर्णांक frreg)
अणु
	अचिन्हित दीर्घ val = regs->gr[frreg];
	पूर्णांक ret;

	अगर (!frreg)
		val = 0;

	DPRINTF("store r%d (0x" RFMT ") to " RFMT ":" RFMT " for 2 bytes\n", frreg, 
		val, regs->isr, regs->ior);

	__यंत्र__ __अस्थिर__ (
"	mtsp %3, %%sr1\n"
"	extrw,u %1, 23, 8, %%r19\n"
"1:	stb %1, 1(%%sr1, %2)\n"
"2:	stb %%r19, 0(%%sr1, %2)\n"
"	copy	%%r0, %0\n"
"3:	\n"
"	.section .fixup,\"ax\"\n"
"4:	ldi	-2, %0\n"
	FIXUP_BRANCH(3b)
"	.previous\n"
	ASM_EXCEPTIONTABLE_ENTRY(1b,4b)
	ASM_EXCEPTIONTABLE_ENTRY(2b,4b)
	: "=r" (ret)
	: "r" (val), "r" (regs->ior), "r" (regs->isr)
	: "r19", FIXUP_BRANCH_CLOBBER );

	वापस ret;
पूर्ण

अटल पूर्णांक emulate_stw(काष्ठा pt_regs *regs, पूर्णांक frreg, पूर्णांक flop)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	अगर (flop)
		val = ((__u32*)(regs->fr))[frreg];
	अन्यथा अगर (frreg)
		val = regs->gr[frreg];
	अन्यथा
		val = 0;

	DPRINTF("store r%d (0x" RFMT ") to " RFMT ":" RFMT " for 4 bytes\n", frreg, 
		val, regs->isr, regs->ior);


	__यंत्र__ __अस्थिर__ (
"	mtsp %3, %%sr1\n"
"	zdep	%2, 28, 2, %%r19\n"
"	dep	%%r0, 31, 2, %2\n"
"	mtsar	%%r19\n"
"	depwi,z	-2, %%sar, 32, %%r19\n"
"1:	ldw	0(%%sr1,%2),%%r20\n"
"2:	ldw	4(%%sr1,%2),%%r21\n"
"	vshd	%%r0, %1, %%r22\n"
"	vshd	%1, %%r0, %%r1\n"
"	and	%%r20, %%r19, %%r20\n"
"	andcm	%%r21, %%r19, %%r21\n"
"	or	%%r22, %%r20, %%r20\n"
"	or	%%r1, %%r21, %%r21\n"
"	stw	%%r20,0(%%sr1,%2)\n"
"	stw	%%r21,4(%%sr1,%2)\n"
"	copy	%%r0, %0\n"
"3:	\n"
"	.section .fixup,\"ax\"\n"
"4:	ldi	-2, %0\n"
	FIXUP_BRANCH(3b)
"	.previous\n"
	ASM_EXCEPTIONTABLE_ENTRY(1b,4b)
	ASM_EXCEPTIONTABLE_ENTRY(2b,4b)
	: "=r" (ret)
	: "r" (val), "r" (regs->ior), "r" (regs->isr)
	: "r19", "r20", "r21", "r22", "r1", FIXUP_BRANCH_CLOBBER );

	वापस 0;
पूर्ण
अटल पूर्णांक emulate_std(काष्ठा pt_regs *regs, पूर्णांक frreg, पूर्णांक flop)
अणु
	__u64 val;
	पूर्णांक ret;

	अगर (flop)
		val = regs->fr[frreg];
	अन्यथा अगर (frreg)
		val = regs->gr[frreg];
	अन्यथा
		val = 0;

	DPRINTF("store r%d (0x%016llx) to " RFMT ":" RFMT " for 8 bytes\n", frreg, 
		val,  regs->isr, regs->ior);

#अगर_घोषित CONFIG_PA20
#अगर_अघोषित CONFIG_64BIT
	अगर (!flop)
		वापस -1;
#पूर्ण_अगर
	__यंत्र__ __अस्थिर__ (
"	mtsp %3, %%sr1\n"
"	depd,z	%2, 60, 3, %%r19\n"
"	depd	%%r0, 63, 3, %2\n"
"	mtsar	%%r19\n"
"	depdi,z	-2, %%sar, 64, %%r19\n"
"1:	ldd	0(%%sr1,%2),%%r20\n"
"2:	ldd	8(%%sr1,%2),%%r21\n"
"	shrpd	%%r0, %1, %%sar, %%r22\n"
"	shrpd	%1, %%r0, %%sar, %%r1\n"
"	and	%%r20, %%r19, %%r20\n"
"	andcm	%%r21, %%r19, %%r21\n"
"	or	%%r22, %%r20, %%r20\n"
"	or	%%r1, %%r21, %%r21\n"
"3:	std	%%r20,0(%%sr1,%2)\n"
"4:	std	%%r21,8(%%sr1,%2)\n"
"	copy	%%r0, %0\n"
"5:	\n"
"	.section .fixup,\"ax\"\n"
"6:	ldi	-2, %0\n"
	FIXUP_BRANCH(5b)
"	.previous\n"
	ASM_EXCEPTIONTABLE_ENTRY(1b,6b)
	ASM_EXCEPTIONTABLE_ENTRY(2b,6b)
	ASM_EXCEPTIONTABLE_ENTRY(3b,6b)
	ASM_EXCEPTIONTABLE_ENTRY(4b,6b)
	: "=r" (ret)
	: "r" (val), "r" (regs->ior), "r" (regs->isr)
	: "r19", "r20", "r21", "r22", "r1", FIXUP_BRANCH_CLOBBER );
#अन्यथा
    अणु
	अचिन्हित दीर्घ valh=(val>>32),vall=(val&0xffffffffl);
	__यंत्र__ __अस्थिर__ (
"	mtsp	%4, %%sr1\n"
"	zdep	%2, 29, 2, %%r19\n"
"	dep	%%r0, 31, 2, %2\n"
"	mtsar	%%r19\n"
"	zvdepi	-2, 32, %%r19\n"
"1:	ldw	0(%%sr1,%3),%%r20\n"
"2:	ldw	8(%%sr1,%3),%%r21\n"
"	vshd	%1, %2, %%r1\n"
"	vshd	%%r0, %1, %1\n"
"	vshd	%2, %%r0, %2\n"
"	and	%%r20, %%r19, %%r20\n"
"	andcm	%%r21, %%r19, %%r21\n"
"	or	%1, %%r20, %1\n"
"	or	%2, %%r21, %2\n"
"3:	stw	%1,0(%%sr1,%1)\n"
"4:	stw	%%r1,4(%%sr1,%3)\n"
"5:	stw	%2,8(%%sr1,%3)\n"
"	copy	%%r0, %0\n"
"6:	\n"
"	.section .fixup,\"ax\"\n"
"7:	ldi	-2, %0\n"
	FIXUP_BRANCH(6b)
"	.previous\n"
	ASM_EXCEPTIONTABLE_ENTRY(1b,7b)
	ASM_EXCEPTIONTABLE_ENTRY(2b,7b)
	ASM_EXCEPTIONTABLE_ENTRY(3b,7b)
	ASM_EXCEPTIONTABLE_ENTRY(4b,7b)
	ASM_EXCEPTIONTABLE_ENTRY(5b,7b)
	: "=r" (ret)
	: "r" (valh), "r" (vall), "r" (regs->ior), "r" (regs->isr)
	: "r19", "r20", "r21", "r1", FIXUP_BRANCH_CLOBBER );
    पूर्ण
#पूर्ण_अगर

	वापस ret;
पूर्ण

व्योम handle_unaligned(काष्ठा pt_regs *regs)
अणु
	अटल DEFINE_RATELIMIT_STATE(ratelimit, 5 * HZ, 5);
	अचिन्हित दीर्घ newbase = R1(regs->iir)?regs->gr[R1(regs->iir)]:0;
	पूर्णांक modअगरy = 0;
	पूर्णांक ret = ERR_NOTHANDLED;
	रेजिस्टर पूर्णांक flop=0;	/* true अगर this is a flop */

	__inc_irq_stat(irq_unaligned_count);

	/* log a message with pacing */
	अगर (user_mode(regs)) अणु
		अगर (current->thपढ़ो.flags & PARISC_UAC_SIGBUS) अणु
			जाओ क्रमce_sigbus;
		पूर्ण

		अगर (!(current->thपढ़ो.flags & PARISC_UAC_NOPRINT) &&
			__ratelimit(&ratelimit)) अणु
			अक्षर buf[256];
			प्र_लिखो(buf, "%s(%d): unaligned access to 0x" RFMT " at ip=0x" RFMT "\n",
				current->comm, task_pid_nr(current), regs->ior, regs->iaoq[0]);
			prपूर्णांकk(KERN_WARNING "%s", buf);
#अगर_घोषित DEBUG_UNALIGNED
			show_regs(regs);
#पूर्ण_अगर		
		पूर्ण

		अगर (!unaligned_enabled)
			जाओ क्रमce_sigbus;
	पूर्ण

	/* handle modअगरication - OK, it's ugly, see the inकाष्ठाion manual */
	चयन (MAJOR_OP(regs->iir))
	अणु
	हाल 0x03:
	हाल 0x09:
	हाल 0x0b:
		अगर (regs->iir&0x20)
		अणु
			modअगरy = 1;
			अगर (regs->iir&0x1000)		/* लघु loads */
				अगर (regs->iir&0x200)
					newbase += IM5_3(regs->iir);
				अन्यथा
					newbase += IM5_2(regs->iir);
			अन्यथा अगर (regs->iir&0x2000)	/* scaled indexed */
			अणु
				पूर्णांक shअगरt=0;
				चयन (regs->iir & OPCODE1_MASK)
				अणु
				हाल OPCODE_LDH_I:
					shअगरt= 1; अवरोध;
				हाल OPCODE_LDW_I:
					shअगरt= 2; अवरोध;
				हाल OPCODE_LDD_I:
				हाल OPCODE_LDDA_I:
					shअगरt= 3; अवरोध;
				पूर्ण
				newbase += (R2(regs->iir)?regs->gr[R2(regs->iir)]:0)<<shअगरt;
			पूर्ण अन्यथा				/* simple indexed */
				newbase += (R2(regs->iir)?regs->gr[R2(regs->iir)]:0);
		पूर्ण
		अवरोध;
	हाल 0x13:
	हाल 0x1b:
		modअगरy = 1;
		newbase += IM14(regs->iir);
		अवरोध;
	हाल 0x14:
	हाल 0x1c:
		अगर (regs->iir&8)
		अणु
			modअगरy = 1;
			newbase += IM14(regs->iir&~0xe);
		पूर्ण
		अवरोध;
	हाल 0x16:
	हाल 0x1e:
		modअगरy = 1;
		newbase += IM14(regs->iir&6);
		अवरोध;
	हाल 0x17:
	हाल 0x1f:
		अगर (regs->iir&4)
		अणु
			modअगरy = 1;
			newbase += IM14(regs->iir&~4);
		पूर्ण
		अवरोध;
	पूर्ण

	/* TODO: make this cleaner... */
	चयन (regs->iir & OPCODE1_MASK)
	अणु
	हाल OPCODE_LDH_I:
	हाल OPCODE_LDH_S:
		ret = emulate_ldh(regs, R3(regs->iir));
		अवरोध;

	हाल OPCODE_LDW_I:
	हाल OPCODE_LDWA_I:
	हाल OPCODE_LDW_S:
	हाल OPCODE_LDWA_S:
		ret = emulate_ldw(regs, R3(regs->iir),0);
		अवरोध;

	हाल OPCODE_STH:
		ret = emulate_sth(regs, R2(regs->iir));
		अवरोध;

	हाल OPCODE_STW:
	हाल OPCODE_STWA:
		ret = emulate_stw(regs, R2(regs->iir),0);
		अवरोध;

#अगर_घोषित CONFIG_PA20
	हाल OPCODE_LDD_I:
	हाल OPCODE_LDDA_I:
	हाल OPCODE_LDD_S:
	हाल OPCODE_LDDA_S:
		ret = emulate_ldd(regs, R3(regs->iir),0);
		अवरोध;

	हाल OPCODE_STD:
	हाल OPCODE_STDA:
		ret = emulate_std(regs, R2(regs->iir),0);
		अवरोध;
#पूर्ण_अगर

	हाल OPCODE_FLDWX:
	हाल OPCODE_FLDWS:
	हाल OPCODE_FLDWXR:
	हाल OPCODE_FLDWSR:
		flop=1;
		ret = emulate_ldw(regs,FR3(regs->iir),1);
		अवरोध;

	हाल OPCODE_FLDDX:
	हाल OPCODE_FLDDS:
		flop=1;
		ret = emulate_ldd(regs,R3(regs->iir),1);
		अवरोध;

	हाल OPCODE_FSTWX:
	हाल OPCODE_FSTWS:
	हाल OPCODE_FSTWXR:
	हाल OPCODE_FSTWSR:
		flop=1;
		ret = emulate_stw(regs,FR3(regs->iir),1);
		अवरोध;

	हाल OPCODE_FSTDX:
	हाल OPCODE_FSTDS:
		flop=1;
		ret = emulate_std(regs,R3(regs->iir),1);
		अवरोध;

	हाल OPCODE_LDCD_I:
	हाल OPCODE_LDCW_I:
	हाल OPCODE_LDCD_S:
	हाल OPCODE_LDCW_S:
		ret = ERR_NOTHANDLED;	/* "undefined", but lets समाप्त them. */
		अवरोध;
	पूर्ण
#अगर_घोषित CONFIG_PA20
	चयन (regs->iir & OPCODE2_MASK)
	अणु
	हाल OPCODE_FLDD_L:
		flop=1;
		ret = emulate_ldd(regs,R2(regs->iir),1);
		अवरोध;
	हाल OPCODE_FSTD_L:
		flop=1;
		ret = emulate_std(regs, R2(regs->iir),1);
		अवरोध;
	हाल OPCODE_LDD_L:
		ret = emulate_ldd(regs, R2(regs->iir),0);
		अवरोध;
	हाल OPCODE_STD_L:
		ret = emulate_std(regs, R2(regs->iir),0);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	चयन (regs->iir & OPCODE3_MASK)
	अणु
	हाल OPCODE_FLDW_L:
		flop=1;
		ret = emulate_ldw(regs, R2(regs->iir),0);
		अवरोध;
	हाल OPCODE_LDW_M:
		ret = emulate_ldw(regs, R2(regs->iir),1);
		अवरोध;

	हाल OPCODE_FSTW_L:
		flop=1;
		ret = emulate_stw(regs, R2(regs->iir),1);
		अवरोध;
	हाल OPCODE_STW_M:
		ret = emulate_stw(regs, R2(regs->iir),0);
		अवरोध;
	पूर्ण
	चयन (regs->iir & OPCODE4_MASK)
	अणु
	हाल OPCODE_LDH_L:
		ret = emulate_ldh(regs, R2(regs->iir));
		अवरोध;
	हाल OPCODE_LDW_L:
	हाल OPCODE_LDWM:
		ret = emulate_ldw(regs, R2(regs->iir),0);
		अवरोध;
	हाल OPCODE_STH_L:
		ret = emulate_sth(regs, R2(regs->iir));
		अवरोध;
	हाल OPCODE_STW_L:
	हाल OPCODE_STWM:
		ret = emulate_stw(regs, R2(regs->iir),0);
		अवरोध;
	पूर्ण

	अगर (ret == 0 && modअगरy && R1(regs->iir))
		regs->gr[R1(regs->iir)] = newbase;


	अगर (ret == ERR_NOTHANDLED)
		prपूर्णांकk(KERN_CRIT "Not-handled unaligned insn 0x%08lx\n", regs->iir);

	DPRINTF("ret = %d\n", ret);

	अगर (ret)
	अणु
		/*
		 * The unaligned handler failed.
		 * If we were called by __get_user() or __put_user() jump
		 * to it's exception fixup handler instead of crashing.
		 */
		अगर (!user_mode(regs) && fixup_exception(regs))
			वापस;

		prपूर्णांकk(KERN_CRIT "Unaligned handler failed, ret = %d\n", ret);
		die_अगर_kernel("Unaligned data reference", regs, 28);

		अगर (ret == ERR_PAGEFAULT)
		अणु
			क्रमce_sig_fault(संक_अंश, SEGV_MAPERR,
					(व्योम __user *)regs->ior);
		पूर्ण
		अन्यथा
		अणु
क्रमce_sigbus:
			/* couldn't handle it ... */
			क्रमce_sig_fault(SIGBUS, BUS_ADRALN,
					(व्योम __user *)regs->ior);
		पूर्ण
		
		वापस;
	पूर्ण

	/* अन्यथा we handled it, let lअगरe go on. */
	regs->gr[0]|=PSW_N;
पूर्ण

/*
 * NB: check_unaligned() is only used क्रम PCXS processors right
 * now, so we only check क्रम PA1.1 encodings at this poपूर्णांक.
 */

पूर्णांक
check_unaligned(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ align_mask;

	/* Get alignment mask */

	align_mask = 0UL;
	चयन (regs->iir & OPCODE1_MASK) अणु

	हाल OPCODE_LDH_I:
	हाल OPCODE_LDH_S:
	हाल OPCODE_STH:
		align_mask = 1UL;
		अवरोध;

	हाल OPCODE_LDW_I:
	हाल OPCODE_LDWA_I:
	हाल OPCODE_LDW_S:
	हाल OPCODE_LDWA_S:
	हाल OPCODE_STW:
	हाल OPCODE_STWA:
		align_mask = 3UL;
		अवरोध;

	शेष:
		चयन (regs->iir & OPCODE4_MASK) अणु
		हाल OPCODE_LDH_L:
		हाल OPCODE_STH_L:
			align_mask = 1UL;
			अवरोध;
		हाल OPCODE_LDW_L:
		हाल OPCODE_LDWM:
		हाल OPCODE_STW_L:
		हाल OPCODE_STWM:
			align_mask = 3UL;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस (पूर्णांक)(regs->ior & align_mask);
पूर्ण

