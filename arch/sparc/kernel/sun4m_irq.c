<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sun4m irq support
 *
 *  djhr: Hacked out of irq.c पूर्णांकo a CPU dependent version.
 *
 *  Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 *  Copyright (C) 1995 Miguel de Icaza (miguel@nuclecu.unam.mx)
 *  Copyright (C) 1995 Pete A. Zaitcev (zaitcev@yahoo.com)
 *  Copyright (C) 1996 Dave Redman (djhr@tadpole.co.uk)
 */

#समावेश <linux/slab.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/cacheflush.h>

#समावेश "irq.h"
#समावेश "kernel.h"

/* Sample sun4m IRQ layout:
 *
 * 0x22 - Power
 * 0x24 - ESP SCSI
 * 0x26 - Lance ethernet
 * 0x2b - Floppy
 * 0x2c - Zilog uart
 * 0x32 - SBUS level 0
 * 0x33 - Parallel port, SBUS level 1
 * 0x35 - SBUS level 2
 * 0x37 - SBUS level 3
 * 0x39 - Audio, Graphics card, SBUS level 4
 * 0x3b - SBUS level 5
 * 0x3d - SBUS level 6
 *
 * Each पूर्णांकerrupt source has a mask bit in the पूर्णांकerrupt रेजिस्टरs.
 * When the mask bit is set, this blocks पूर्णांकerrupt deliver.  So you
 * clear the bit to enable the पूर्णांकerrupt.
 *
 * Interrupts numbered less than 0x10 are software triggered पूर्णांकerrupts
 * and unused by Linux.
 *
 * Interrupt level assignment on sun4m:
 *
 *	level		source
 * ------------------------------------------------------------
 *	  1		softपूर्णांक-1
 *	  2		softपूर्णांक-2, VME/SBUS level 1
 *	  3		softपूर्णांक-3, VME/SBUS level 2
 *	  4		softपूर्णांक-4, onboard SCSI
 *	  5		softपूर्णांक-5, VME/SBUS level 3
 *	  6		softपूर्णांक-6, onboard ETHERNET
 *	  7		softपूर्णांक-7, VME/SBUS level 4
 *	  8		softपूर्णांक-8, onboard VIDEO
 *	  9		softपूर्णांक-9, VME/SBUS level 5, Module Interrupt
 *	 10		softपूर्णांक-10, प्रणाली counter/समयr
 *	 11		softपूर्णांक-11, VME/SBUS level 6, Floppy
 *	 12		softपूर्णांक-12, Keyboard/Mouse, Serial
 *	 13		softपूर्णांक-13, VME/SBUS level 7, ISDN Audio
 *	 14		softपूर्णांक-14, per-processor counter/समयr
 *	 15		softपूर्णांक-15, Asynchronous Errors (broadcast)
 *
 * Each पूर्णांकerrupt source is masked distinctly in the sun4m पूर्णांकerrupt
 * रेजिस्टरs.  The PIL level alone is thereक्रमe ambiguous, since multiple
 * पूर्णांकerrupt sources map to a single PIL.
 *
 * This ambiguity is resolved in the 'intr' property क्रम device nodes
 * in the OF device tree.  Each 'intr' property entry is composed of
 * two 32-bit words.  The first word is the IRQ priority value, which
 * is what we're पूर्णांकersted in.  The second word is the IRQ vector, which
 * is unused.
 *
 * The low 4 bits of the IRQ priority indicate the PIL, and the upper
 * 4 bits indicate onboard vs. SBUS leveled vs. VME leveled.  0x20
 * means onboard, 0x30 means SBUS leveled, and 0x40 means VME leveled.
 *
 * For example, an 'intr' IRQ priority value of 0x24 is onboard SCSI
 * whereas a value of 0x33 is SBUS level 2.  Here are some sample
 * 'intr' property IRQ priority values from ss4, ss5, ss10, ss20, and
 * Tadpole S3 GX प्रणालीs.
 *
 * esp:		0x24	onboard ESP SCSI
 * le:		0x26	onboard Lance ETHERNET
 * p9100:	0x32	SBUS level 1 P9100 video
 * bpp:		0x33	SBUS level 2 BPP parallel port device
 * DBRI:	0x39	SBUS level 5 DBRI ISDN audio
 * SUNW,leo:	0x39	SBUS level 5 LEO video
 * pcmcia:	0x3b	SBUS level 6 PCMCIA controller
 * uctrl:	0x3b	SBUS level 6 UCTRL device
 * modem:	0x3d	SBUS level 7 MODEM
 * zs:		0x2c	onboard keyboard/mouse/serial
 * floppy:	0x2b	onboard Floppy
 * घातer:	0x22	onboard घातer device (XXX unknown mask bit XXX)
 */


/* Code in entry.S needs to get at these रेजिस्टर mappings.  */
काष्ठा sun4m_irq_percpu __iomem *sun4m_irq_percpu[SUN4M_NCPUS];
काष्ठा sun4m_irq_global __iomem *sun4m_irq_global;

काष्ठा sun4m_handler_data अणु
	bool    percpu;
	दीर्घ    mask;
पूर्ण;

/* Dave Redman (djhr@tadpole.co.uk)
 * The sun4m पूर्णांकerrupt रेजिस्टरs.
 */
#घोषणा SUN4M_INT_ENABLE	0x80000000
#घोषणा SUN4M_INT_E14		0x00000080
#घोषणा SUN4M_INT_E10		0x00080000

#घोषणा	SUN4M_INT_MASKALL	0x80000000	  /* mask all पूर्णांकerrupts */
#घोषणा	SUN4M_INT_MODULE_ERR	0x40000000	  /* module error */
#घोषणा	SUN4M_INT_M2S_WRITE_ERR	0x20000000	  /* ग_लिखो buffer error */
#घोषणा	SUN4M_INT_ECC_ERR	0x10000000	  /* ecc memory error */
#घोषणा	SUN4M_INT_VME_ERR	0x08000000	  /* vme async error */
#घोषणा	SUN4M_INT_FLOPPY	0x00400000	  /* floppy disk */
#घोषणा	SUN4M_INT_MODULE	0x00200000	  /* module पूर्णांकerrupt */
#घोषणा	SUN4M_INT_VIDEO		0x00100000	  /* onboard video */
#घोषणा	SUN4M_INT_REALTIME	0x00080000	  /* प्रणाली समयr */
#घोषणा	SUN4M_INT_SCSI		0x00040000	  /* onboard scsi */
#घोषणा	SUN4M_INT_AUDIO		0x00020000	  /* audio/isdn */
#घोषणा	SUN4M_INT_ETHERNET	0x00010000	  /* onboard ethernet */
#घोषणा	SUN4M_INT_SERIAL	0x00008000	  /* serial ports */
#घोषणा	SUN4M_INT_KBDMS		0x00004000	  /* keyboard/mouse */
#घोषणा	SUN4M_INT_SBUSBITS	0x00003F80	  /* sbus पूर्णांक bits */
#घोषणा	SUN4M_INT_VMEBITS	0x0000007F	  /* vme पूर्णांक bits */

#घोषणा	SUN4M_INT_ERROR		(SUN4M_INT_MODULE_ERR |    \
				 SUN4M_INT_M2S_WRITE_ERR | \
				 SUN4M_INT_ECC_ERR |       \
				 SUN4M_INT_VME_ERR)

#घोषणा SUN4M_INT_SBUS(x)	(1 << (x+7))
#घोषणा SUN4M_INT_VME(x)	(1 << (x))

/* Interrupt levels used by OBP */
#घोषणा	OBP_INT_LEVEL_SOFT	0x10
#घोषणा	OBP_INT_LEVEL_ONBOARD	0x20
#घोषणा	OBP_INT_LEVEL_SBUS	0x30
#घोषणा	OBP_INT_LEVEL_VME	0x40

#घोषणा SUN4M_TIMER_IRQ         (OBP_INT_LEVEL_ONBOARD | 10)
#घोषणा SUN4M_PROखाता_IRQ       (OBP_INT_LEVEL_ONBOARD | 14)

अटल अचिन्हित दीर्घ sun4m_imask[0x50] = अणु
	/* 0x00 - SMP */
	0,  SUN4M_SOFT_INT(1),
	SUN4M_SOFT_INT(2),  SUN4M_SOFT_INT(3),
	SUN4M_SOFT_INT(4),  SUN4M_SOFT_INT(5),
	SUN4M_SOFT_INT(6),  SUN4M_SOFT_INT(7),
	SUN4M_SOFT_INT(8),  SUN4M_SOFT_INT(9),
	SUN4M_SOFT_INT(10), SUN4M_SOFT_INT(11),
	SUN4M_SOFT_INT(12), SUN4M_SOFT_INT(13),
	SUN4M_SOFT_INT(14), SUN4M_SOFT_INT(15),
	/* 0x10 - soft */
	0,  SUN4M_SOFT_INT(1),
	SUN4M_SOFT_INT(2),  SUN4M_SOFT_INT(3),
	SUN4M_SOFT_INT(4),  SUN4M_SOFT_INT(5),
	SUN4M_SOFT_INT(6),  SUN4M_SOFT_INT(7),
	SUN4M_SOFT_INT(8),  SUN4M_SOFT_INT(9),
	SUN4M_SOFT_INT(10), SUN4M_SOFT_INT(11),
	SUN4M_SOFT_INT(12), SUN4M_SOFT_INT(13),
	SUN4M_SOFT_INT(14), SUN4M_SOFT_INT(15),
	/* 0x20 - onboard */
	0, 0, 0, 0,
	SUN4M_INT_SCSI,  0, SUN4M_INT_ETHERNET, 0,
	SUN4M_INT_VIDEO, SUN4M_INT_MODULE,
	SUN4M_INT_REALTIME, SUN4M_INT_FLOPPY,
	(SUN4M_INT_SERIAL | SUN4M_INT_KBDMS),
	SUN4M_INT_AUDIO, SUN4M_INT_E14, SUN4M_INT_MODULE_ERR,
	/* 0x30 - sbus */
	0, 0, SUN4M_INT_SBUS(0), SUN4M_INT_SBUS(1),
	0, SUN4M_INT_SBUS(2), 0, SUN4M_INT_SBUS(3),
	0, SUN4M_INT_SBUS(4), 0, SUN4M_INT_SBUS(5),
	0, SUN4M_INT_SBUS(6), 0, 0,
	/* 0x40 - vme */
	0, 0, SUN4M_INT_VME(0), SUN4M_INT_VME(1),
	0, SUN4M_INT_VME(2), 0, SUN4M_INT_VME(3),
	0, SUN4M_INT_VME(4), 0, SUN4M_INT_VME(5),
	0, SUN4M_INT_VME(6), 0, 0
पूर्ण;

अटल व्योम sun4m_mask_irq(काष्ठा irq_data *data)
अणु
	काष्ठा sun4m_handler_data *handler_data;
	पूर्णांक cpu = smp_processor_id();

	handler_data = irq_data_get_irq_handler_data(data);
	अगर (handler_data->mask) अणु
		अचिन्हित दीर्घ flags;

		local_irq_save(flags);
		अगर (handler_data->percpu) अणु
			sbus_ग_लिखोl(handler_data->mask, &sun4m_irq_percpu[cpu]->set);
		पूर्ण अन्यथा अणु
			sbus_ग_लिखोl(handler_data->mask, &sun4m_irq_global->mask_set);
		पूर्ण
		local_irq_restore(flags);
	पूर्ण
पूर्ण

अटल व्योम sun4m_unmask_irq(काष्ठा irq_data *data)
अणु
	काष्ठा sun4m_handler_data *handler_data;
	पूर्णांक cpu = smp_processor_id();

	handler_data = irq_data_get_irq_handler_data(data);
	अगर (handler_data->mask) अणु
		अचिन्हित दीर्घ flags;

		local_irq_save(flags);
		अगर (handler_data->percpu) अणु
			sbus_ग_लिखोl(handler_data->mask, &sun4m_irq_percpu[cpu]->clear);
		पूर्ण अन्यथा अणु
			sbus_ग_लिखोl(handler_data->mask, &sun4m_irq_global->mask_clear);
		पूर्ण
		local_irq_restore(flags);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक sun4m_startup_irq(काष्ठा irq_data *data)
अणु
	irq_link(data->irq);
	sun4m_unmask_irq(data);
	वापस 0;
पूर्ण

अटल व्योम sun4m_shutकरोwn_irq(काष्ठा irq_data *data)
अणु
	sun4m_mask_irq(data);
	irq_unlink(data->irq);
पूर्ण

अटल काष्ठा irq_chip sun4m_irq = अणु
	.name		= "sun4m",
	.irq_startup	= sun4m_startup_irq,
	.irq_shutकरोwn	= sun4m_shutकरोwn_irq,
	.irq_mask	= sun4m_mask_irq,
	.irq_unmask	= sun4m_unmask_irq,
पूर्ण;


अटल अचिन्हित पूर्णांक sun4m_build_device_irq(काष्ठा platक्रमm_device *op,
					   अचिन्हित पूर्णांक real_irq)
अणु
	काष्ठा sun4m_handler_data *handler_data;
	अचिन्हित पूर्णांक irq;
	अचिन्हित पूर्णांक pil;

	अगर (real_irq >= OBP_INT_LEVEL_VME) अणु
		prom_म_लिखो("Bogus sun4m IRQ %u\n", real_irq);
		prom_halt();
	पूर्ण
	pil = (real_irq & 0xf);
	irq = irq_alloc(real_irq, pil);

	अगर (irq == 0)
		जाओ out;

	handler_data = irq_get_handler_data(irq);
	अगर (unlikely(handler_data))
		जाओ out;

	handler_data = kzalloc(माप(काष्ठा sun4m_handler_data), GFP_ATOMIC);
	अगर (unlikely(!handler_data)) अणु
		prom_म_लिखो("IRQ: kzalloc(sun4m_handler_data) failed.\n");
		prom_halt();
	पूर्ण

	handler_data->mask = sun4m_imask[real_irq];
	handler_data->percpu = real_irq < OBP_INT_LEVEL_ONBOARD;
	irq_set_chip_and_handler_name(irq, &sun4m_irq,
	                              handle_level_irq, "level");
	irq_set_handler_data(irq, handler_data);

out:
	वापस irq;
पूर्ण

काष्ठा sun4m_समयr_percpu अणु
	u32		l14_limit;
	u32		l14_count;
	u32		l14_limit_noclear;
	u32		user_समयr_start_stop;
पूर्ण;

अटल काष्ठा sun4m_समयr_percpu __iomem *समयrs_percpu[SUN4M_NCPUS];

काष्ठा sun4m_समयr_global अणु
	u32		l10_limit;
	u32		l10_count;
	u32		l10_limit_noclear;
	u32		reserved;
	u32		समयr_config;
पूर्ण;

अटल काष्ठा sun4m_समयr_global __iomem *समयrs_global;

अटल व्योम sun4m_clear_घड़ी_irq(व्योम)
अणु
	sbus_पढ़ोl(&समयrs_global->l10_limit);
पूर्ण

व्योम sun4m_nmi(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ afsr, afar, si;

	prपूर्णांकk(KERN_ERR "Aieee: sun4m NMI received!\n");
	/* XXX HyperSparc hack XXX */
	__यंत्र__ __अस्थिर__("mov 0x500, %%g1\n\t"
			     "lda [%%g1] 0x4, %0\n\t"
			     "mov 0x600, %%g1\n\t"
			     "lda [%%g1] 0x4, %1\n\t" :
			     "=r" (afsr), "=r" (afar));
	prपूर्णांकk(KERN_ERR "afsr=%08lx afar=%08lx\n", afsr, afar);
	si = sbus_पढ़ोl(&sun4m_irq_global->pending);
	prपूर्णांकk(KERN_ERR "si=%08lx\n", si);
	अगर (si & SUN4M_INT_MODULE_ERR)
		prपूर्णांकk(KERN_ERR "Module async error\n");
	अगर (si & SUN4M_INT_M2S_WRITE_ERR)
		prपूर्णांकk(KERN_ERR "MBus/SBus async error\n");
	अगर (si & SUN4M_INT_ECC_ERR)
		prपूर्णांकk(KERN_ERR "ECC memory error\n");
	अगर (si & SUN4M_INT_VME_ERR)
		prपूर्णांकk(KERN_ERR "VME async error\n");
	prपूर्णांकk(KERN_ERR "you lose buddy boy...\n");
	show_regs(regs);
	prom_halt();
पूर्ण

व्योम sun4m_unmask_profile_irq(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	sbus_ग_लिखोl(sun4m_imask[SUN4M_PROखाता_IRQ], &sun4m_irq_global->mask_clear);
	local_irq_restore(flags);
पूर्ण

व्योम sun4m_clear_profile_irq(पूर्णांक cpu)
अणु
	sbus_पढ़ोl(&समयrs_percpu[cpu]->l14_limit);
पूर्ण

अटल व्योम sun4m_load_profile_irq(पूर्णांक cpu, अचिन्हित पूर्णांक limit)
अणु
	अचिन्हित पूर्णांक value = limit ? समयr_value(limit) : 0;
	sbus_ग_लिखोl(value, &समयrs_percpu[cpu]->l14_limit);
पूर्ण

अटल व्योम __init sun4m_init_समयrs(व्योम)
अणु
	काष्ठा device_node *dp = of_find_node_by_name(शून्य, "counter");
	पूर्णांक i, err, len, num_cpu_समयrs;
	अचिन्हित पूर्णांक irq;
	स्थिर u32 *addr;

	अगर (!dp) अणु
		prपूर्णांकk(KERN_ERR "sun4m_init_timers: No 'counter' node.\n");
		वापस;
	पूर्ण

	addr = of_get_property(dp, "address", &len);
	of_node_put(dp);
	अगर (!addr) अणु
		prपूर्णांकk(KERN_ERR "sun4m_init_timers: No 'address' prop.\n");
		वापस;
	पूर्ण

	num_cpu_समयrs = (len / माप(u32)) - 1;
	क्रम (i = 0; i < num_cpu_समयrs; i++) अणु
		समयrs_percpu[i] = (व्योम __iomem *)
			(अचिन्हित दीर्घ) addr[i];
	पूर्ण
	समयrs_global = (व्योम __iomem *)
		(अचिन्हित दीर्घ) addr[num_cpu_समयrs];

	/* Every per-cpu समयr works in समयr mode */
	sbus_ग_लिखोl(0x00000000, &समयrs_global->समयr_config);

#अगर_घोषित CONFIG_SMP
	sparc_config.cs_period = SBUS_CLOCK_RATE * 2;  /* 2 seconds */
	sparc_config.features |= FEAT_L14_ONESHOT;
#अन्यथा
	sparc_config.cs_period = SBUS_CLOCK_RATE / HZ; /* 1/HZ sec  */
	sparc_config.features |= FEAT_L10_CLOCKEVENT;
#पूर्ण_अगर
	sparc_config.features |= FEAT_L10_CLOCKSOURCE;
	sbus_ग_लिखोl(समयr_value(sparc_config.cs_period),
	            &समयrs_global->l10_limit);

	master_l10_counter = &समयrs_global->l10_count;

	irq = sun4m_build_device_irq(शून्य, SUN4M_TIMER_IRQ);

	err = request_irq(irq, समयr_पूर्णांकerrupt, IRQF_TIMER, "timer", शून्य);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "sun4m_init_timers: Register IRQ error %d.\n",
			err);
		वापस;
	पूर्ण

	क्रम (i = 0; i < num_cpu_समयrs; i++)
		sbus_ग_लिखोl(0, &समयrs_percpu[i]->l14_limit);
	अगर (num_cpu_समयrs == 4)
		sbus_ग_लिखोl(SUN4M_INT_E14, &sun4m_irq_global->mask_set);

#अगर_घोषित CONFIG_SMP
	अणु
		अचिन्हित दीर्घ flags;
		काष्ठा tt_entry *trap_table = &sparc_ttable[SP_TRAP_IRQ1 + (14 - 1)];

		/* For SMP we use the level 14 ticker, however the bootup code
		 * has copied the firmware's level 14 vector into the boot cpu's
		 * trap table, we must fix this now or we get squashed.
		 */
		local_irq_save(flags);
		trap_table->inst_one = lvl14_save[0];
		trap_table->inst_two = lvl14_save[1];
		trap_table->inst_three = lvl14_save[2];
		trap_table->inst_four = lvl14_save[3];
		local_ops->cache_all();
		local_irq_restore(flags);
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम __init sun4m_init_IRQ(व्योम)
अणु
	काष्ठा device_node *dp = of_find_node_by_name(शून्य, "interrupt");
	पूर्णांक len, i, mid, num_cpu_iregs;
	स्थिर u32 *addr;

	अगर (!dp) अणु
		prपूर्णांकk(KERN_ERR "sun4m_init_IRQ: No 'interrupt' node.\n");
		वापस;
	पूर्ण

	addr = of_get_property(dp, "address", &len);
	of_node_put(dp);
	अगर (!addr) अणु
		prपूर्णांकk(KERN_ERR "sun4m_init_IRQ: No 'address' prop.\n");
		वापस;
	पूर्ण

	num_cpu_iregs = (len / माप(u32)) - 1;
	क्रम (i = 0; i < num_cpu_iregs; i++) अणु
		sun4m_irq_percpu[i] = (व्योम __iomem *)
			(अचिन्हित दीर्घ) addr[i];
	पूर्ण
	sun4m_irq_global = (व्योम __iomem *)
		(अचिन्हित दीर्घ) addr[num_cpu_iregs];

	local_irq_disable();

	sbus_ग_लिखोl(~SUN4M_INT_MASKALL, &sun4m_irq_global->mask_set);
	क्रम (i = 0; !cpu_find_by_instance(i, शून्य, &mid); i++)
		sbus_ग_लिखोl(~0x17fff, &sun4m_irq_percpu[mid]->clear);

	अगर (num_cpu_iregs == 4)
		sbus_ग_लिखोl(0, &sun4m_irq_global->पूर्णांकerrupt_target);

	sparc_config.init_समयrs      = sun4m_init_समयrs;
	sparc_config.build_device_irq = sun4m_build_device_irq;
	sparc_config.घड़ी_rate       = SBUS_CLOCK_RATE;
	sparc_config.clear_घड़ी_irq  = sun4m_clear_घड़ी_irq;
	sparc_config.load_profile_irq = sun4m_load_profile_irq;


	/* Cannot enable पूर्णांकerrupts until OBP ticker is disabled. */
पूर्ण
