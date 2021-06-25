<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Bus error event handling code क्रम प्रणालीs equipped with ECC
 *	handling logic, i.e. DECstation/DECप्रणाली 5000/200 (KN02),
 *	5000/240 (KN03), 5000/260 (KN05) and DECप्रणाली 5900 (KN03),
 *	5900/260 (KN05) प्रणालीs.
 *
 *	Copyright (c) 2003, 2005  Maciej W. Rozycki
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-type.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/traps.h>

#समावेश <यंत्र/dec/ecc.h>
#समावेश <यंत्र/dec/kn02.h>
#समावेश <यंत्र/dec/kn03.h>
#समावेश <यंत्र/dec/kn05.h>

अटल अस्थिर u32 *kn0x_erraddr;
अटल अस्थिर u32 *kn0x_chksyn;

अटल अंतरभूत व्योम dec_ecc_be_ack(व्योम)
अणु
	*kn0x_erraddr = 0;			/* any ग_लिखो clears the IRQ */
	iob();
पूर्ण

अटल पूर्णांक dec_ecc_be_backend(काष्ठा pt_regs *regs, पूर्णांक is_fixup, पूर्णांक invoker)
अणु
	अटल स्थिर अक्षर excstr[] = "exception";
	अटल स्थिर अक्षर पूर्णांकstr[] = "interrupt";
	अटल स्थिर अक्षर cpustr[] = "CPU";
	अटल स्थिर अक्षर dmastr[] = "DMA";
	अटल स्थिर अक्षर पढ़ोstr[] = "read";
	अटल स्थिर अक्षर mपढ़ोstr[] = "memory read";
	अटल स्थिर अक्षर ग_लिखोstr[] = "write";
	अटल स्थिर अक्षर mwritstr[] = "partial memory write";
	अटल स्थिर अक्षर बारtr[] = "timeout";
	अटल स्थिर अक्षर overstr[] = "overrun";
	अटल स्थिर अक्षर eccstr[] = "ECC error";

	स्थिर अक्षर *kind, *agent, *cycle, *event;
	स्थिर अक्षर *status = "", *xbit = "", *fmt = "";
	अचिन्हित दीर्घ address;
	u16 syn = 0, sngl;

	पूर्णांक i = 0;

	u32 erraddr = *kn0x_erraddr;
	u32 chksyn = *kn0x_chksyn;
	पूर्णांक action = MIPS_BE_FATAL;

	/* For non-ECC ack ASAP, so that any subsequent errors get caught. */
	अगर ((erraddr & (KN0X_EAR_VALID | KN0X_EAR_ECCERR)) == KN0X_EAR_VALID)
		dec_ecc_be_ack();

	kind = invoker ? पूर्णांकstr : excstr;

	अगर (!(erraddr & KN0X_EAR_VALID)) अणु
		/* No idea what happened. */
		prपूर्णांकk(KERN_ALERT "Unidentified bus error %s\n", kind);
		वापस action;
	पूर्ण

	agent = (erraddr & KN0X_EAR_CPU) ? cpustr : dmastr;

	अगर (erraddr & KN0X_EAR_ECCERR) अणु
		/* An ECC error on a CPU or DMA transaction. */
		cycle = (erraddr & KN0X_EAR_WRITE) ? mwritstr : mपढ़ोstr;
		event = eccstr;
	पूर्ण अन्यथा अणु
		/* A CPU समयout or a DMA overrun. */
		cycle = (erraddr & KN0X_EAR_WRITE) ? ग_लिखोstr : पढ़ोstr;
		event = (erraddr & KN0X_EAR_CPU) ? बारtr : overstr;
	पूर्ण

	address = erraddr & KN0X_EAR_ADDRESS;
	/* For ECC errors on पढ़ोs adjust क्रम MT pipelining. */
	अगर ((erraddr & (KN0X_EAR_WRITE | KN0X_EAR_ECCERR)) == KN0X_EAR_ECCERR)
		address = (address & ~0xfffLL) | ((address - 5) & 0xfffLL);
	address <<= 2;

	/* Only CPU errors are fixable. */
	अगर (erraddr & KN0X_EAR_CPU && is_fixup)
		action = MIPS_BE_FIXUP;

	अगर (erraddr & KN0X_EAR_ECCERR) अणु
		अटल स्थिर u8 data_sbit[32] = अणु
			0x4f, 0x4a, 0x52, 0x54, 0x57, 0x58, 0x5b, 0x5d,
			0x23, 0x25, 0x26, 0x29, 0x2a, 0x2c, 0x31, 0x34,
			0x0e, 0x0b, 0x13, 0x15, 0x16, 0x19, 0x1a, 0x1c,
			0x62, 0x64, 0x67, 0x68, 0x6b, 0x6d, 0x70, 0x75,
		पूर्ण;
		अटल स्थिर u8 data_mbit[25] = अणु
			0x07, 0x0d, 0x1f,
			0x2f, 0x32, 0x37, 0x38, 0x3b, 0x3d, 0x3e,
			0x43, 0x45, 0x46, 0x49, 0x4c, 0x51, 0x5e,
			0x61, 0x6e, 0x73, 0x76, 0x79, 0x7a, 0x7c, 0x7f,
		पूर्ण;
		अटल स्थिर अक्षर sbestr[] = "corrected single";
		अटल स्थिर अक्षर dbestr[] = "uncorrectable double";
		अटल स्थिर अक्षर mbestr[] = "uncorrectable multiple";

		अगर (!(address & 0x4))
			syn = chksyn;			/* Low bank. */
		अन्यथा
			syn = chksyn >> 16;		/* High bank. */

		अगर (!(syn & KN0X_ESR_VLDLO)) अणु
			/* Ack now, no reग_लिखो will happen. */
			dec_ecc_be_ack();

			fmt = KERN_ALERT "%s" "invalid\n";
		पूर्ण अन्यथा अणु
			sngl = syn & KN0X_ESR_SNGLO;
			syn &= KN0X_ESR_SYNLO;

			/*
			 * Multibit errors may be tagged incorrectly;
			 * check the syndrome explicitly.
			 */
			क्रम (i = 0; i < 25; i++)
				अगर (syn == data_mbit[i])
					अवरोध;

			अगर (i < 25) अणु
				status = mbestr;
			पूर्ण अन्यथा अगर (!sngl) अणु
				status = dbestr;
			पूर्ण अन्यथा अणु
				अस्थिर u32 *ptr =
					(व्योम *)CKSEG1ADDR(address);

				*ptr = *ptr;		/* Reग_लिखो. */
				iob();

				status = sbestr;
				action = MIPS_BE_DISCARD;
			पूर्ण

			/* Ack now, now we've rewritten (or not). */
			dec_ecc_be_ack();

			अगर (syn && syn == (syn & -syn)) अणु
				अगर (syn == 0x01) अणु
					fmt = KERN_ALERT "%s"
					      "%#04x -- %s bit error "
					      "at check bit C%s\n";
					xbit = "X";
				पूर्ण अन्यथा अणु
					fmt = KERN_ALERT "%s"
					      "%#04x -- %s bit error "
					      "at check bit C%s%u\n";
				पूर्ण
				i = syn >> 2;
			पूर्ण अन्यथा अणु
				क्रम (i = 0; i < 32; i++)
					अगर (syn == data_sbit[i])
						अवरोध;
				अगर (i < 32)
					fmt = KERN_ALERT "%s"
					      "%#04x -- %s bit error "
					      "at data bit D%s%u\n";
				अन्यथा
					fmt = KERN_ALERT "%s"
					      "%#04x -- %s bit error\n";
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (action != MIPS_BE_FIXUP)
		prपूर्णांकk(KERN_ALERT "Bus error %s: %s %s %s at %#010lx\n",
			kind, agent, cycle, event, address);

	अगर (action != MIPS_BE_FIXUP && erraddr & KN0X_EAR_ECCERR)
		prपूर्णांकk(fmt, "  ECC syndrome ", syn, status, xbit, i);

	वापस action;
पूर्ण

पूर्णांक dec_ecc_be_handler(काष्ठा pt_regs *regs, पूर्णांक is_fixup)
अणु
	वापस dec_ecc_be_backend(regs, is_fixup, 0);
पूर्ण

irqवापस_t dec_ecc_be_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pt_regs *regs = get_irq_regs();

	पूर्णांक action = dec_ecc_be_backend(regs, 0, 1);

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


/*
 * Initialization dअगरfers a bit between KN02 and KN03/KN05, so we
 * need two variants.  Once set up, all प्रणालीs can be handled the
 * same way.
 */
अटल अंतरभूत व्योम dec_kn02_be_init(व्योम)
अणु
	अस्थिर u32 *csr = (व्योम *)CKSEG1ADDR(KN02_SLOT_BASE + KN02_CSR);

	kn0x_erraddr = (व्योम *)CKSEG1ADDR(KN02_SLOT_BASE + KN02_ERRADDR);
	kn0x_chksyn = (व्योम *)CKSEG1ADDR(KN02_SLOT_BASE + KN02_CHKSYN);

	/* Preset ग_लिखो-only bits of the Control Register cache. */
	cached_kn02_csr = *csr | KN02_CSR_LEDS;

	/* Set normal ECC detection and generation. */
	cached_kn02_csr &= ~(KN02_CSR_DIAGCHK | KN02_CSR_DIAGGEN);
	/* Enable ECC correction. */
	cached_kn02_csr |= KN02_CSR_CORRECT;
	*csr = cached_kn02_csr;
	iob();
पूर्ण

अटल अंतरभूत व्योम dec_kn03_be_init(व्योम)
अणु
	अस्थिर u32 *mcr = (व्योम *)CKSEG1ADDR(KN03_SLOT_BASE + IOASIC_MCR);
	अस्थिर u32 *mbcs = (व्योम *)CKSEG1ADDR(KN4K_SLOT_BASE + KN4K_MB_CSR);

	kn0x_erraddr = (व्योम *)CKSEG1ADDR(KN03_SLOT_BASE + IOASIC_ERRADDR);
	kn0x_chksyn = (व्योम *)CKSEG1ADDR(KN03_SLOT_BASE + IOASIC_CHKSYN);

	/*
	 * Set normal ECC detection and generation, enable ECC correction.
	 * For KN05 we also need to make sure EE (?) is enabled in the MB.
	 * Otherwise DBE/IBE exceptions would be masked but bus error
	 * पूर्णांकerrupts would still arrive, resulting in an inevitable crash
	 * अगर get_dbe() triggers one.
	 */
	*mcr = (*mcr & ~(KN03_MCR_DIAGCHK | KN03_MCR_DIAGGEN)) |
	       KN03_MCR_CORRECT;
	अगर (current_cpu_type() == CPU_R4400SC)
		*mbcs |= KN4K_MB_CSR_EE;
	fast_iob();
पूर्ण

व्योम __init dec_ecc_be_init(व्योम)
अणु
	अगर (mips_machtype == MACH_DS5000_200)
		dec_kn02_be_init();
	अन्यथा
		dec_kn03_be_init();

	/* Clear any leftover errors from the firmware. */
	dec_ecc_be_ack();
पूर्ण
