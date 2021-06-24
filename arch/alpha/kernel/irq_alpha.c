<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Alpha specअगरic irq code.
 */

#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/module.h>

#समावेश <यंत्र/machvec.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/perf_event.h>
#समावेश <यंत्र/mce.h>

#समावेश "proto.h"
#समावेश "irq_impl.h"

/* Hack minimum IPL during पूर्णांकerrupt processing क्रम broken hardware.  */
#अगर_घोषित CONFIG_ALPHA_BROKEN_IRQ_MASK
पूर्णांक __min_ipl;
EXPORT_SYMBOL(__min_ipl);
#पूर्ण_अगर

/*
 * Perक्रमmance counter hook.  A module can override this to
 * करो something useful.
 */
अटल व्योम
dummy_perf(अचिन्हित दीर्घ vector, काष्ठा pt_regs *regs)
अणु
	irq_err_count++;
	prपूर्णांकk(KERN_CRIT "Performance counter interrupt!\n");
पूर्ण

व्योम (*perf_irq)(अचिन्हित दीर्घ, काष्ठा pt_regs *) = dummy_perf;
EXPORT_SYMBOL(perf_irq);

/*
 * The मुख्य पूर्णांकerrupt entry poपूर्णांक.
 */

यंत्रlinkage व्योम 
करो_entInt(अचिन्हित दीर्घ type, अचिन्हित दीर्घ vector,
	  अचिन्हित दीर्घ la_ptr, काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *old_regs;

	/*
	 * Disable पूर्णांकerrupts during IRQ handling.
	 * Note that there is no matching local_irq_enable() due to
	 * severe problems with RTI at IPL0 and some MILO PALcode
	 * (namely LX164).
	 */
	local_irq_disable();
	चयन (type) अणु
	हाल 0:
#अगर_घोषित CONFIG_SMP
		handle_ipi(regs);
		वापस;
#अन्यथा
		irq_err_count++;
		prपूर्णांकk(KERN_CRIT "Interprocessor interrupt? "
		       "You must be kidding!\n");
#पूर्ण_अगर
		अवरोध;
	हाल 1:
		old_regs = set_irq_regs(regs);
		handle_irq(RTC_IRQ);
		set_irq_regs(old_regs);
		वापस;
	हाल 2:
		old_regs = set_irq_regs(regs);
		alpha_mv.machine_check(vector, la_ptr);
		set_irq_regs(old_regs);
		वापस;
	हाल 3:
		old_regs = set_irq_regs(regs);
		alpha_mv.device_पूर्णांकerrupt(vector);
		set_irq_regs(old_regs);
		वापस;
	हाल 4:
		perf_irq(la_ptr, regs);
		वापस;
	शेष:
		prपूर्णांकk(KERN_CRIT "Hardware intr %ld %lx? Huh?\n",
		       type, vector);
	पूर्ण
	prपूर्णांकk(KERN_CRIT "PC = %016lx PS=%04lx\n", regs->pc, regs->ps);
पूर्ण

व्योम __init
common_init_isa_dma(व्योम)
अणु
	outb(0, DMA1_RESET_REG);
	outb(0, DMA2_RESET_REG);
	outb(0, DMA1_CLR_MASK_REG);
	outb(0, DMA2_CLR_MASK_REG);
पूर्ण

व्योम __init
init_IRQ(व्योम)
अणु
	/* Just in हाल the platक्रमm init_irq() causes पूर्णांकerrupts/mchecks
	   (as is the हाल with RAWHIDE, at least).  */
	wrent(entInt, 0);

	alpha_mv.init_irq();
पूर्ण

/*
 * machine error checks
 */
#घोषणा MCHK_K_TPERR           0x0080
#घोषणा MCHK_K_TCPERR          0x0082
#घोषणा MCHK_K_HERR            0x0084
#घोषणा MCHK_K_ECC_C           0x0086
#घोषणा MCHK_K_ECC_NC          0x0088
#घोषणा MCHK_K_OS_BUGCHECK     0x008A
#घोषणा MCHK_K_PAL_BUGCHECK    0x0090

#अगर_अघोषित CONFIG_SMP
काष्ठा mcheck_info __mcheck_info;
#पूर्ण_अगर

व्योम
process_mcheck_info(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr,
		    स्थिर अक्षर *machine, पूर्णांक expected)
अणु
	काष्ठा el_common *mchk_header;
	स्थिर अक्षर *reason;

	/*
	 * See अगर the machine check is due to a badaddr() and अगर so,
	 * ignore it.
	 */

#अगर_घोषित CONFIG_VERBOSE_MCHECK
	अगर (alpha_verbose_mcheck > 1) अणु
		prपूर्णांकk(KERN_CRIT "%s machine check %s\n", machine,
		       expected ? "expected." : "NOT expected!!!");
	पूर्ण
#पूर्ण_अगर

	अगर (expected) अणु
		पूर्णांक cpu = smp_processor_id();
		mcheck_expected(cpu) = 0;
		mcheck_taken(cpu) = 1;
		वापस;
	पूर्ण

	mchk_header = (काष्ठा el_common *)la_ptr;

	prपूर्णांकk(KERN_CRIT "%s machine check: vector=0x%lx pc=0x%lx code=0x%x\n",
	       machine, vector, get_irq_regs()->pc, mchk_header->code);

	चयन (mchk_header->code) अणु
	/* Machine check reasons.  Defined according to PALcode sources.  */
	हाल 0x80: reason = "tag parity error"; अवरोध;
	हाल 0x82: reason = "tag control parity error"; अवरोध;
	हाल 0x84: reason = "generic hard error"; अवरोध;
	हाल 0x86: reason = "correctable ECC error"; अवरोध;
	हाल 0x88: reason = "uncorrectable ECC error"; अवरोध;
	हाल 0x8A: reason = "OS-specific PAL bugcheck"; अवरोध;
	हाल 0x90: reason = "callsys in kernel mode"; अवरोध;
	हाल 0x96: reason = "i-cache read retryable error"; अवरोध;
	हाल 0x98: reason = "processor detected hard error"; अवरोध;
	
	/* System specअगरic (these are क्रम Alcor, at least): */
	हाल 0x202: reason = "system detected hard error"; अवरोध;
	हाल 0x203: reason = "system detected uncorrectable ECC error"; अवरोध;
	हाल 0x204: reason = "SIO SERR occurred on PCI bus"; अवरोध;
	हाल 0x205: reason = "parity error detected by core logic"; अवरोध;
	हाल 0x206: reason = "SIO IOCHK occurred on ISA bus"; अवरोध;
	हाल 0x207: reason = "non-existent memory error"; अवरोध;
	हाल 0x208: reason = "MCHK_K_DCSR"; अवरोध;
	हाल 0x209: reason = "PCI SERR detected"; अवरोध;
	हाल 0x20b: reason = "PCI data parity error detected"; अवरोध;
	हाल 0x20d: reason = "PCI address parity error detected"; अवरोध;
	हाल 0x20f: reason = "PCI master abort error"; अवरोध;
	हाल 0x211: reason = "PCI target abort error"; अवरोध;
	हाल 0x213: reason = "scatter/gather PTE invalid error"; अवरोध;
	हाल 0x215: reason = "flash ROM write error"; अवरोध;
	हाल 0x217: reason = "IOA timeout detected"; अवरोध;
	हाल 0x219: reason = "IOCHK#, EISA add-in board parity or other catastrophic error"; अवरोध;
	हाल 0x21b: reason = "EISA fail-safe timer timeout"; अवरोध;
	हाल 0x21d: reason = "EISA bus time-out"; अवरोध;
	हाल 0x21f: reason = "EISA software generated NMI"; अवरोध;
	हाल 0x221: reason = "unexpected ev5 IRQ[3] interrupt"; अवरोध;
	शेष: reason = "unknown"; अवरोध;
	पूर्ण

	prपूर्णांकk(KERN_CRIT "machine check type: %s%s\n",
	       reason, mchk_header->retry ? " (retryable)" : "");

	dik_show_regs(get_irq_regs(), शून्य);

#अगर_घोषित CONFIG_VERBOSE_MCHECK
	अगर (alpha_verbose_mcheck > 1) अणु
		/* Dump the logout area to give all info.  */
		अचिन्हित दीर्घ *ptr = (अचिन्हित दीर्घ *)la_ptr;
		दीर्घ i;
		क्रम (i = 0; i < mchk_header->size / माप(दीर्घ); i += 2) अणु
			prपूर्णांकk(KERN_CRIT "   +%8lx %016lx %016lx\n",
			       i*माप(दीर्घ), ptr[i], ptr[i+1]);
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_VERBOSE_MCHECK */
पूर्ण

/*
 * The special RTC पूर्णांकerrupt type.  The पूर्णांकerrupt itself was
 * processed by PALcode, and comes in via entInt vector 1.
 */
व्योम __init
init_rtc_irq(irq_handler_t handler)
अणु
	irq_set_chip_and_handler_name(RTC_IRQ, &dummy_irq_chip,
				      handle_percpu_irq, "RTC");
	अगर (!handler)
		handler = rtc_समयr_पूर्णांकerrupt;
	अगर (request_irq(RTC_IRQ, handler, 0, "timer", शून्य))
		pr_err("Failed to register timer interrupt\n");
पूर्ण
