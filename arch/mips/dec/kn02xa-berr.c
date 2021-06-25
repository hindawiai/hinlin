<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Bus error event handling code क्रम 5000-series प्रणालीs equipped
 *	with parity error detection logic, i.e. DECstation/DECप्रणाली
 *	5000/120, /125, /133 (KN02-BA), 5000/150 (KN04-BA) and Personal
 *	DECstation/DECप्रणाली 5000/20, /25, /33 (KN02-CA), 5000/50
 *	(KN04-CA) प्रणालीs.
 *
 *	Copyright (c) 2005  Maciej W. Rozycki
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/cpu-type.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/traps.h>

#समावेश <यंत्र/dec/kn02ca.h>
#समावेश <यंत्र/dec/kn02xa.h>
#समावेश <यंत्र/dec/kn05.h>

अटल अंतरभूत व्योम dec_kn02xa_be_ack(व्योम)
अणु
	अस्थिर u32 *mer = (व्योम *)CKSEG1ADDR(KN02XA_MER);
	अस्थिर u32 *mem_पूर्णांकr = (व्योम *)CKSEG1ADDR(KN02XA_MEM_INTR);

	*mer = KN02CA_MER_INTR;		/* Clear errors; keep the ARC IRQ. */
	*mem_पूर्णांकr = 0;			/* Any ग_लिखो clears the bus IRQ. */
	iob();
पूर्ण

अटल पूर्णांक dec_kn02xa_be_backend(काष्ठा pt_regs *regs, पूर्णांक is_fixup,
				 पूर्णांक invoker)
अणु
	अस्थिर u32 *kn02xa_mer = (व्योम *)CKSEG1ADDR(KN02XA_MER);
	अस्थिर u32 *kn02xa_ear = (व्योम *)CKSEG1ADDR(KN02XA_EAR);

	अटल स्थिर अक्षर excstr[] = "exception";
	अटल स्थिर अक्षर पूर्णांकstr[] = "interrupt";
	अटल स्थिर अक्षर cpustr[] = "CPU";
	अटल स्थिर अक्षर mपढ़ोstr[] = "memory read";
	अटल स्थिर अक्षर पढ़ोstr[] = "read";
	अटल स्थिर अक्षर ग_लिखोstr[] = "write";
	अटल स्थिर अक्षर बारtr[] = "timeout";
	अटल स्थिर अक्षर paritystr[] = "parity error";
	अटल स्थिर अक्षर lanestat[][4] = अणु " OK", "BAD" पूर्ण;

	स्थिर अक्षर *kind, *agent, *cycle, *event;
	अचिन्हित दीर्घ address;

	u32 mer = *kn02xa_mer;
	u32 ear = *kn02xa_ear;
	पूर्णांक action = MIPS_BE_FATAL;

	/* Ack ASAP, so that any subsequent errors get caught. */
	dec_kn02xa_be_ack();

	kind = invoker ? पूर्णांकstr : excstr;

	/* No DMA errors? */
	agent = cpustr;

	address = ear & KN02XA_EAR_ADDRESS;

	/* Low 256MB is decoded as memory, high -- as TC. */
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

	अगर (action != MIPS_BE_FIXUP && address < 0x10000000)
		prपूर्णांकk(KERN_ALERT "  Byte lane status %#3x -- "
		       "#3: %s, #2: %s, #1: %s, #0: %s\n",
		       (mer & KN02XA_MER_BYTERR) >> 8,
		       lanestat[(mer & KN02XA_MER_BYTERR_3) != 0],
		       lanestat[(mer & KN02XA_MER_BYTERR_2) != 0],
		       lanestat[(mer & KN02XA_MER_BYTERR_1) != 0],
		       lanestat[(mer & KN02XA_MER_BYTERR_0) != 0]);

	वापस action;
पूर्ण

पूर्णांक dec_kn02xa_be_handler(काष्ठा pt_regs *regs, पूर्णांक is_fixup)
अणु
	वापस dec_kn02xa_be_backend(regs, is_fixup, 0);
पूर्ण

irqवापस_t dec_kn02xa_be_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pt_regs *regs = get_irq_regs();
	पूर्णांक action = dec_kn02xa_be_backend(regs, 0, 1);

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


व्योम __init dec_kn02xa_be_init(व्योम)
अणु
	अस्थिर u32 *mbcs = (व्योम *)CKSEG1ADDR(KN4K_SLOT_BASE + KN4K_MB_CSR);

	/* For KN04 we need to make sure EE (?) is enabled in the MB.  */
	अगर (current_cpu_type() == CPU_R4000SC)
		*mbcs |= KN4K_MB_CSR_EE;
	fast_iob();

	/* Clear any leftover errors from the firmware. */
	dec_kn02xa_be_ack();
पूर्ण
