<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Bus error event handling code क्रम DECstation/DECप्रणाली 3100
 *	and 2100 (KN01) प्रणालीs equipped with parity error detection
 *	logic.
 *
 *	Copyright (c) 2005  Maciej W. Rozycki
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/inst.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/traps.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/dec/kn01.h>


/* CP0 hazard aव्योमance. */
#घोषणा BARRIER				\
	__यंत्र__ __अस्थिर__(		\
		".set	push\n\t"	\
		".set	noreorder\n\t"	\
		"nop\n\t"		\
		".set	pop\n\t")

/*
 * Bits 7:0 of the Control Register are ग_लिखो-only -- the
 * corresponding bits of the Status Register have a dअगरferent
 * meaning.  Hence we use a cache.  It speeds up things a bit
 * as well.
 *
 * There is no शेष value -- it has to be initialized.
 */
u16 cached_kn01_csr;
अटल DEFINE_RAW_SPINLOCK(kn01_lock);


अटल अंतरभूत व्योम dec_kn01_be_ack(व्योम)
अणु
	अस्थिर u16 *csr = (व्योम *)CKSEG1ADDR(KN01_SLOT_BASE + KN01_CSR);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&kn01_lock, flags);

	*csr = cached_kn01_csr | KN01_CSR_MEMERR;	/* Clear bus IRQ. */
	iob();

	raw_spin_unlock_irqrestore(&kn01_lock, flags);
पूर्ण

अटल पूर्णांक dec_kn01_be_backend(काष्ठा pt_regs *regs, पूर्णांक is_fixup, पूर्णांक invoker)
अणु
	अस्थिर u32 *kn01_erraddr = (व्योम *)CKSEG1ADDR(KN01_SLOT_BASE +
							KN01_ERRADDR);

	अटल स्थिर अक्षर excstr[] = "exception";
	अटल स्थिर अक्षर पूर्णांकstr[] = "interrupt";
	अटल स्थिर अक्षर cpustr[] = "CPU";
	अटल स्थिर अक्षर mपढ़ोstr[] = "memory read";
	अटल स्थिर अक्षर पढ़ोstr[] = "read";
	अटल स्थिर अक्षर ग_लिखोstr[] = "write";
	अटल स्थिर अक्षर बारtr[] = "timeout";
	अटल स्थिर अक्षर paritystr[] = "parity error";

	पूर्णांक data = regs->cp0_cause & 4;
	अचिन्हित पूर्णांक __user *pc = (अचिन्हित पूर्णांक __user *)regs->cp0_epc +
				  ((regs->cp0_cause & CAUSEF_BD) != 0);
	जोड़ mips_inकाष्ठाion insn;
	अचिन्हित दीर्घ entrylo, offset;
	दीर्घ asid, entryhi, vaddr;

	स्थिर अक्षर *kind, *agent, *cycle, *event;
	अचिन्हित दीर्घ address;

	u32 erraddr = *kn01_erraddr;
	पूर्णांक action = MIPS_BE_FATAL;

	/* Ack ASAP, so that any subsequent errors get caught. */
	dec_kn01_be_ack();

	kind = invoker ? पूर्णांकstr : excstr;

	agent = cpustr;

	अगर (invoker)
		address = erraddr;
	अन्यथा अणु
		/* Bloody hardware करोesn't record the address क्रम पढ़ोs... */
		अगर (data) अणु
			/* This never faults. */
			__get_user(insn.word, pc);
			vaddr = regs->regs[insn.i_क्रमmat.rs] +
				insn.i_क्रमmat.simmediate;
		पूर्ण अन्यथा
			vaddr = (दीर्घ)pc;
		अगर (KSEGX(vaddr) == CKSEG0 || KSEGX(vaddr) == CKSEG1)
			address = CPHYSADDR(vaddr);
		अन्यथा अणु
			/* Peek at what physical address the CPU used. */
			asid = पढ़ो_c0_entryhi();
			entryhi = asid & (PAGE_SIZE - 1);
			entryhi |= vaddr & ~(PAGE_SIZE - 1);
			ग_लिखो_c0_entryhi(entryhi);
			BARRIER;
			tlb_probe();
			/* No need to check क्रम presence. */
			tlb_पढ़ो();
			entrylo = पढ़ो_c0_entrylo0();
			ग_लिखो_c0_entryhi(asid);
			offset = vaddr & (PAGE_SIZE - 1);
			address = (entrylo & ~(PAGE_SIZE - 1)) | offset;
		पूर्ण
	पूर्ण

	/* Treat low 256MB as memory, high -- as I/O. */
	अगर (address < 0x10000000) अणु
		cycle = mपढ़ोstr;
		event = paritystr;
	पूर्ण अन्यथा अणु
		cycle = invoker ? ग_लिखोstr : पढ़ोstr;
		event = बारtr;
	पूर्ण

	अगर (is_fixup)
		action = MIPS_BE_FIXUP;

	अगर (action != MIPS_BE_FIXUP)
		prपूर्णांकk(KERN_ALERT "Bus error %s: %s %s %s at %#010lx\n",
			kind, agent, cycle, event, address);

	वापस action;
पूर्ण

पूर्णांक dec_kn01_be_handler(काष्ठा pt_regs *regs, पूर्णांक is_fixup)
अणु
	वापस dec_kn01_be_backend(regs, is_fixup, 0);
पूर्ण

irqवापस_t dec_kn01_be_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अस्थिर u16 *csr = (व्योम *)CKSEG1ADDR(KN01_SLOT_BASE + KN01_CSR);
	काष्ठा pt_regs *regs = get_irq_regs();
	पूर्णांक action;

	अगर (!(*csr & KN01_CSR_MEMERR))
		वापस IRQ_NONE;		/* Must have been video. */

	action = dec_kn01_be_backend(regs, 0, 1);

	अगर (action == MIPS_BE_DISCARD)
		वापस IRQ_HANDLED;

	/*
	 * FIXME: Find the affected processes and समाप्त them, otherwise
	 * we must die.
	 *
	 * The पूर्णांकerrupt is asynchronously delivered thus EPC and RA
	 * may be irrelevant, but are prपूर्णांकed क्रम a reference.
	 */
	prपूर्णांकk(KERN_ALERT "Fatal bus interrupt, epc == %08lx, ra == %08lx\n",
	       regs->cp0_epc, regs->regs[31]);
	die("Unrecoverable bus error", regs);
पूर्ण


व्योम __init dec_kn01_be_init(व्योम)
अणु
	अस्थिर u16 *csr = (व्योम *)CKSEG1ADDR(KN01_SLOT_BASE + KN01_CSR);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&kn01_lock, flags);

	/* Preset ग_लिखो-only bits of the Control Register cache. */
	cached_kn01_csr = *csr;
	cached_kn01_csr &= KN01_CSR_STATUS | KN01_CSR_PARDIS | KN01_CSR_TXDIS;
	cached_kn01_csr |= KN01_CSR_LEDS;

	/* Enable parity error detection. */
	cached_kn01_csr &= ~KN01_CSR_PARDIS;
	*csr = cached_kn01_csr;
	iob();

	raw_spin_unlock_irqrestore(&kn01_lock, flags);

	/* Clear any leftover errors from the firmware. */
	dec_kn01_be_ack();
पूर्ण
