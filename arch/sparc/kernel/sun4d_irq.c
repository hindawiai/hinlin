<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SS1000/SC2000 पूर्णांकerrupt handling.
 *
 *  Copyright (C) 1997,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 *  Heavily based on arch/sparc/kernel/irq.c.
 */

#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>

#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/sbi.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/oplib.h>

#समावेश "kernel.h"
#समावेश "irq.h"

/* Sun4d पूर्णांकerrupts fall roughly पूर्णांकo two categories.  SBUS and
 * cpu local.  CPU local पूर्णांकerrupts cover the समयr पूर्णांकerrupts
 * and whatnot, and we encode those as normal PILs between
 * 0 and 15.
 * SBUS पूर्णांकerrupts are encodes as a combination of board, level and slot.
 */

काष्ठा sun4d_handler_data अणु
	अचिन्हित पूर्णांक cpuid;    /* target cpu */
	अचिन्हित पूर्णांक real_irq; /* पूर्णांकerrupt level */
पूर्ण;


अटल अचिन्हित पूर्णांक sun4d_encode_irq(पूर्णांक board, पूर्णांक lvl, पूर्णांक slot)
अणु
	वापस (board + 1) << 5 | (lvl << 2) | slot;
पूर्ण

काष्ठा sun4d_समयr_regs अणु
	u32	l10_समयr_limit;
	u32	l10_cur_countx;
	u32	l10_limit_noclear;
	u32	ctrl;
	u32	l10_cur_count;
पूर्ण;

अटल काष्ठा sun4d_समयr_regs __iomem *sun4d_समयrs;

#घोषणा SUN4D_TIMER_IRQ        10

/* Specअगरy which cpu handle पूर्णांकerrupts from which board.
 * Index is board - value is cpu.
 */
अटल अचिन्हित अक्षर board_to_cpu[32];

अटल पूर्णांक pil_to_sbus[] = अणु
	0,
	0,
	1,
	2,
	0,
	3,
	0,
	4,
	0,
	5,
	0,
	6,
	0,
	7,
	0,
	0,
पूर्ण;

/* Exported क्रम sun4d_smp.c */
DEFINE_SPINLOCK(sun4d_imsk_lock);

/* SBUS पूर्णांकerrupts are encoded पूर्णांकegers including the board number
 * (plus one), the SBUS level, and the SBUS slot number.  Sun4D
 * IRQ dispatch is करोne by:
 *
 * 1) Reading the BW local पूर्णांकerrupt table in order to get the bus
 *    पूर्णांकerrupt mask.
 *
 *    This table is indexed by SBUS पूर्णांकerrupt level which can be
 *    derived from the PIL we got पूर्णांकerrupted on.
 *
 * 2) For each bus showing पूर्णांकerrupt pending from #1, पढ़ो the
 *    SBI पूर्णांकerrupt state रेजिस्टर.  This will indicate which slots
 *    have पूर्णांकerrupts pending क्रम that SBUS पूर्णांकerrupt level.
 *
 * 3) Call the genreric IRQ support.
 */
अटल व्योम sun4d_sbus_handler_irq(पूर्णांक sbusl)
अणु
	अचिन्हित पूर्णांक bus_mask;
	अचिन्हित पूर्णांक sbino, slot;
	अचिन्हित पूर्णांक sbil;

	bus_mask = bw_get_पूर्णांकr_mask(sbusl) & 0x3ffff;
	bw_clear_पूर्णांकr_mask(sbusl, bus_mask);

	sbil = (sbusl << 2);
	/* Loop क्रम each pending SBI */
	क्रम (sbino = 0; bus_mask; sbino++, bus_mask >>= 1) अणु
		अचिन्हित पूर्णांक idx, mask;

		अगर (!(bus_mask & 1))
			जारी;
		/* XXX This seems to ACK the irq twice.  acquire_sbi()
		 * XXX uses swap, thereक्रमe this ग_लिखोs 0xf << sbil,
		 * XXX then later release_sbi() will ग_लिखो the inभागidual
		 * XXX bits which were set again.
		 */
		mask = acquire_sbi(SBI2DEVID(sbino), 0xf << sbil);
		mask &= (0xf << sbil);

		/* Loop क्रम each pending SBI slot */
		slot = (1 << sbil);
		क्रम (idx = 0; mask != 0; idx++, slot <<= 1) अणु
			अचिन्हित पूर्णांक pil;
			काष्ठा irq_bucket *p;

			अगर (!(mask & slot))
				जारी;

			mask &= ~slot;
			pil = sun4d_encode_irq(sbino, sbusl, idx);

			p = irq_map[pil];
			जबतक (p) अणु
				काष्ठा irq_bucket *next;

				next = p->next;
				generic_handle_irq(p->irq);
				p = next;
			पूर्ण
			release_sbi(SBI2DEVID(sbino), slot);
		पूर्ण
	पूर्ण
पूर्ण

व्योम sun4d_handler_irq(अचिन्हित पूर्णांक pil, काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *old_regs;
	/* SBUS IRQ level (1 - 7) */
	पूर्णांक sbusl = pil_to_sbus[pil];

	/* FIXME: Is this necessary?? */
	cc_get_ipen();

	cc_set_iclr(1 << pil);

#अगर_घोषित CONFIG_SMP
	/*
	 * Check IPI data काष्ठाures after IRQ has been cleared. Hard and Soft
	 * IRQ can happen at the same समय, so both हालs are always handled.
	 */
	अगर (pil == SUN4D_IPI_IRQ)
		sun4d_ipi_पूर्णांकerrupt();
#पूर्ण_अगर

	old_regs = set_irq_regs(regs);
	irq_enter();
	अगर (sbusl == 0) अणु
		/* cpu पूर्णांकerrupt */
		काष्ठा irq_bucket *p;

		p = irq_map[pil];
		जबतक (p) अणु
			काष्ठा irq_bucket *next;

			next = p->next;
			generic_handle_irq(p->irq);
			p = next;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* SBUS पूर्णांकerrupt */
		sun4d_sbus_handler_irq(sbusl);
	पूर्ण
	irq_निकास();
	set_irq_regs(old_regs);
पूर्ण


अटल व्योम sun4d_mask_irq(काष्ठा irq_data *data)
अणु
	काष्ठा sun4d_handler_data *handler_data = irq_data_get_irq_handler_data(data);
	अचिन्हित पूर्णांक real_irq;
#अगर_घोषित CONFIG_SMP
	पूर्णांक cpuid = handler_data->cpuid;
	अचिन्हित दीर्घ flags;
#पूर्ण_अगर
	real_irq = handler_data->real_irq;
#अगर_घोषित CONFIG_SMP
	spin_lock_irqsave(&sun4d_imsk_lock, flags);
	cc_set_imsk_other(cpuid, cc_get_imsk_other(cpuid) | (1 << real_irq));
	spin_unlock_irqrestore(&sun4d_imsk_lock, flags);
#अन्यथा
	cc_set_imsk(cc_get_imsk() | (1 << real_irq));
#पूर्ण_अगर
पूर्ण

अटल व्योम sun4d_unmask_irq(काष्ठा irq_data *data)
अणु
	काष्ठा sun4d_handler_data *handler_data = irq_data_get_irq_handler_data(data);
	अचिन्हित पूर्णांक real_irq;
#अगर_घोषित CONFIG_SMP
	पूर्णांक cpuid = handler_data->cpuid;
	अचिन्हित दीर्घ flags;
#पूर्ण_अगर
	real_irq = handler_data->real_irq;

#अगर_घोषित CONFIG_SMP
	spin_lock_irqsave(&sun4d_imsk_lock, flags);
	cc_set_imsk_other(cpuid, cc_get_imsk_other(cpuid) & ~(1 << real_irq));
	spin_unlock_irqrestore(&sun4d_imsk_lock, flags);
#अन्यथा
	cc_set_imsk(cc_get_imsk() & ~(1 << real_irq));
#पूर्ण_अगर
पूर्ण

अटल अचिन्हित पूर्णांक sun4d_startup_irq(काष्ठा irq_data *data)
अणु
	irq_link(data->irq);
	sun4d_unmask_irq(data);
	वापस 0;
पूर्ण

अटल व्योम sun4d_shutकरोwn_irq(काष्ठा irq_data *data)
अणु
	sun4d_mask_irq(data);
	irq_unlink(data->irq);
पूर्ण

अटल काष्ठा irq_chip sun4d_irq = अणु
	.name		= "sun4d",
	.irq_startup	= sun4d_startup_irq,
	.irq_shutकरोwn	= sun4d_shutकरोwn_irq,
	.irq_unmask	= sun4d_unmask_irq,
	.irq_mask	= sun4d_mask_irq,
पूर्ण;

#अगर_घोषित CONFIG_SMP
/* Setup IRQ distribution scheme. */
व्योम __init sun4d_distribute_irqs(व्योम)
अणु
	काष्ठा device_node *dp;

	पूर्णांक cpuid = cpu_logical_map(1);

	अगर (cpuid == -1)
		cpuid = cpu_logical_map(0);
	क्रम_each_node_by_name(dp, "sbi") अणु
		पूर्णांक devid = of_getपूर्णांकprop_शेष(dp, "device-id", 0);
		पूर्णांक board = of_getपूर्णांकprop_शेष(dp, "board#", 0);
		board_to_cpu[board] = cpuid;
		set_sbi_tid(devid, cpuid << 3);
	पूर्ण
	prपूर्णांकk(KERN_ERR "All sbus IRQs directed to CPU%d\n", cpuid);
पूर्ण
#पूर्ण_अगर

अटल व्योम sun4d_clear_घड़ी_irq(व्योम)
अणु
	sbus_पढ़ोl(&sun4d_समयrs->l10_समयr_limit);
पूर्ण

अटल व्योम sun4d_load_profile_irq(पूर्णांक cpu, अचिन्हित पूर्णांक limit)
अणु
	अचिन्हित पूर्णांक value = limit ? समयr_value(limit) : 0;
	bw_set_prof_limit(cpu, value);
पूर्ण

अटल व्योम __init sun4d_load_profile_irqs(व्योम)
अणु
	पूर्णांक cpu = 0, mid;

	जबतक (!cpu_find_by_instance(cpu, शून्य, &mid)) अणु
		sun4d_load_profile_irq(mid >> 3, 0);
		cpu++;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक _sun4d_build_device_irq(अचिन्हित पूर्णांक real_irq,
                                            अचिन्हित पूर्णांक pil,
                                            अचिन्हित पूर्णांक board)
अणु
	काष्ठा sun4d_handler_data *handler_data;
	अचिन्हित पूर्णांक irq;

	irq = irq_alloc(real_irq, pil);
	अगर (irq == 0) अणु
		prom_म_लिखो("IRQ: allocate for %d %d %d failed\n",
			real_irq, pil, board);
		जाओ err_out;
	पूर्ण

	handler_data = irq_get_handler_data(irq);
	अगर (unlikely(handler_data))
		जाओ err_out;

	handler_data = kzalloc(माप(काष्ठा sun4d_handler_data), GFP_ATOMIC);
	अगर (unlikely(!handler_data)) अणु
		prom_म_लिखो("IRQ: kzalloc(sun4d_handler_data) failed.\n");
		prom_halt();
	पूर्ण
	handler_data->cpuid    = board_to_cpu[board];
	handler_data->real_irq = real_irq;
	irq_set_chip_and_handler_name(irq, &sun4d_irq,
	                              handle_level_irq, "level");
	irq_set_handler_data(irq, handler_data);

err_out:
	वापस irq;
पूर्ण



अटल अचिन्हित पूर्णांक sun4d_build_device_irq(काष्ठा platक्रमm_device *op,
                                           अचिन्हित पूर्णांक real_irq)
अणु
	काष्ठा device_node *dp = op->dev.of_node;
	काष्ठा device_node *board_parent, *bus = dp->parent;
	अक्षर *bus_connection;
	स्थिर काष्ठा linux_prom_रेजिस्टरs *regs;
	अचिन्हित पूर्णांक pil;
	अचिन्हित पूर्णांक irq;
	पूर्णांक board, slot;
	पूर्णांक sbusl;

	irq = real_irq;
	जबतक (bus) अणु
		अगर (of_node_name_eq(bus, "sbi")) अणु
			bus_connection = "io-unit";
			अवरोध;
		पूर्ण

		अगर (of_node_name_eq(bus, "bootbus")) अणु
			bus_connection = "cpu-unit";
			अवरोध;
		पूर्ण

		bus = bus->parent;
	पूर्ण
	अगर (!bus)
		जाओ err_out;

	regs = of_get_property(dp, "reg", शून्य);
	अगर (!regs)
		जाओ err_out;

	slot = regs->which_io;

	/*
	 * If Bus nodes parent is not io-unit/cpu-unit or the io-unit/cpu-unit
	 * lacks a "board#" property, something is very wrong.
	 */
	अगर (!of_node_name_eq(bus->parent, bus_connection)) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Error, parent is not %s.\n",
			bus, bus_connection);
		जाओ err_out;
	पूर्ण
	board_parent = bus->parent;
	board = of_getपूर्णांकprop_शेष(board_parent, "board#", -1);
	अगर (board == -1) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Error, lacks board# property.\n",
			board_parent);
		जाओ err_out;
	पूर्ण

	sbusl = pil_to_sbus[real_irq];
	अगर (sbusl)
		pil = sun4d_encode_irq(board, sbusl, slot);
	अन्यथा
		pil = real_irq;

	irq = _sun4d_build_device_irq(real_irq, pil, board);
err_out:
	वापस irq;
पूर्ण

अटल अचिन्हित पूर्णांक sun4d_build_समयr_irq(अचिन्हित पूर्णांक board,
                                          अचिन्हित पूर्णांक real_irq)
अणु
	वापस _sun4d_build_device_irq(real_irq, real_irq, board);
पूर्ण


अटल व्योम __init sun4d_fixup_trap_table(व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	अचिन्हित दीर्घ flags;
	काष्ठा tt_entry *trap_table = &sparc_ttable[SP_TRAP_IRQ1 + (14 - 1)];

	/* Adjust so that we jump directly to smp4d_ticker */
	lvl14_save[2] += smp4d_ticker - real_irq_entry;

	/* For SMP we use the level 14 ticker, however the bootup code
	 * has copied the firmware's level 14 vector into the boot cpu's
	 * trap table, we must fix this now or we get squashed.
	 */
	local_irq_save(flags);
	patchme_maybe_smp_msg[0] = 0x01000000; /* NOP out the branch */
	trap_table->inst_one = lvl14_save[0];
	trap_table->inst_two = lvl14_save[1];
	trap_table->inst_three = lvl14_save[2];
	trap_table->inst_four = lvl14_save[3];
	local_ops->cache_all();
	local_irq_restore(flags);
#पूर्ण_अगर
पूर्ण

अटल व्योम __init sun4d_init_समयrs(व्योम)
अणु
	काष्ठा device_node *dp;
	काष्ठा resource res;
	अचिन्हित पूर्णांक irq;
	स्थिर u32 *reg;
	पूर्णांक err;
	पूर्णांक board;

	dp = of_find_node_by_name(शून्य, "cpu-unit");
	अगर (!dp) अणु
		prom_म_लिखो("sun4d_init_timers: Unable to find cpu-unit\n");
		prom_halt();
	पूर्ण

	/* Which cpu-unit we use is arbitrary, we can view the bootbus समयr
	 * रेजिस्टरs via any cpu's mapping.  The first 'reg' property is the
	 * bootbus.
	 */
	reg = of_get_property(dp, "reg", शून्य);
	अगर (!reg) अणु
		prom_म_लिखो("sun4d_init_timers: No reg property\n");
		prom_halt();
	पूर्ण

	board = of_getपूर्णांकprop_शेष(dp, "board#", -1);
	अगर (board == -1) अणु
		prom_म_लिखो("sun4d_init_timers: No board# property on cpu-unit\n");
		prom_halt();
	पूर्ण

	of_node_put(dp);

	res.start = reg[1];
	res.end = reg[2] - 1;
	res.flags = reg[0] & 0xff;
	sun4d_समयrs = of_ioremap(&res, BW_TIMER_LIMIT,
				  माप(काष्ठा sun4d_समयr_regs), "user timer");
	अगर (!sun4d_समयrs) अणु
		prom_म_लिखो("sun4d_init_timers: Can't map timer regs\n");
		prom_halt();
	पूर्ण

#अगर_घोषित CONFIG_SMP
	sparc_config.cs_period = SBUS_CLOCK_RATE * 2;  /* 2 seconds */
#अन्यथा
	sparc_config.cs_period = SBUS_CLOCK_RATE / HZ; /* 1/HZ sec  */
	sparc_config.features |= FEAT_L10_CLOCKEVENT;
#पूर्ण_अगर
	sparc_config.features |= FEAT_L10_CLOCKSOURCE;
	sbus_ग_लिखोl(समयr_value(sparc_config.cs_period),
		    &sun4d_समयrs->l10_समयr_limit);

	master_l10_counter = &sun4d_समयrs->l10_cur_count;

	irq = sun4d_build_समयr_irq(board, SUN4D_TIMER_IRQ);
	err = request_irq(irq, समयr_पूर्णांकerrupt, IRQF_TIMER, "timer", शून्य);
	अगर (err) अणु
		prom_म_लिखो("sun4d_init_timers: request_irq() failed with %d\n",
		             err);
		prom_halt();
	पूर्ण
	sun4d_load_profile_irqs();
	sun4d_fixup_trap_table();
पूर्ण

व्योम __init sun4d_init_sbi_irq(व्योम)
अणु
	काष्ठा device_node *dp;
	पूर्णांक target_cpu;

	target_cpu = boot_cpu_id;
	क्रम_each_node_by_name(dp, "sbi") अणु
		पूर्णांक devid = of_getपूर्णांकprop_शेष(dp, "device-id", 0);
		पूर्णांक board = of_getपूर्णांकprop_शेष(dp, "board#", 0);
		अचिन्हित पूर्णांक mask;

		set_sbi_tid(devid, target_cpu << 3);
		board_to_cpu[board] = target_cpu;

		/* Get rid of pending irqs from PROM */
		mask = acquire_sbi(devid, 0xffffffff);
		अगर (mask) अणु
			prपूर्णांकk(KERN_ERR "Clearing pending IRQs %08x on SBI %d\n",
			       mask, board);
			release_sbi(devid, mask);
		पूर्ण
	पूर्ण
पूर्ण

व्योम __init sun4d_init_IRQ(व्योम)
अणु
	local_irq_disable();

	sparc_config.init_समयrs      = sun4d_init_समयrs;
	sparc_config.build_device_irq = sun4d_build_device_irq;
	sparc_config.घड़ी_rate       = SBUS_CLOCK_RATE;
	sparc_config.clear_घड़ी_irq  = sun4d_clear_घड़ी_irq;
	sparc_config.load_profile_irq = sun4d_load_profile_irq;

	/* Cannot enable पूर्णांकerrupts until OBP ticker is disabled. */
पूर्ण
