<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ARC ARConnect (MultiCore IP) support (क्रमmerly known as MCIP)
 *
 * Copyright (C) 2013 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/smp.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/spinlock.h>
#समावेश <soc/arc/mcip.h>
#समावेश <यंत्र/irqflags-arcv2.h>
#समावेश <यंत्र/setup.h>

अटल DEFINE_RAW_SPINLOCK(mcip_lock);

#अगर_घोषित CONFIG_SMP

अटल अक्षर smp_cpuinfo_buf[128];

/*
 * Set mask to halt GFRC अगर any online core in SMP cluster is halted.
 * Only works क्रम ARC HS v3.0+, on earlier versions has no effect.
 */
अटल व्योम mcip_update_gfrc_halt_mask(पूर्णांक cpu)
अणु
	काष्ठा bcr_generic gfrc;
	अचिन्हित दीर्घ flags;
	u32 gfrc_halt_mask;

	READ_BCR(ARC_REG_GFRC_BUILD, gfrc);

	/*
	 * CMD_GFRC_SET_CORE and CMD_GFRC_READ_CORE commands were added in
	 * GFRC 0x3 version.
	 */
	अगर (gfrc.ver < 0x3)
		वापस;

	raw_spin_lock_irqsave(&mcip_lock, flags);

	__mcip_cmd(CMD_GFRC_READ_CORE, 0);
	gfrc_halt_mask = पढ़ो_aux_reg(ARC_REG_MCIP_READBACK);
	gfrc_halt_mask |= BIT(cpu);
	__mcip_cmd_data(CMD_GFRC_SET_CORE, 0, gfrc_halt_mask);

	raw_spin_unlock_irqrestore(&mcip_lock, flags);
पूर्ण

अटल व्योम mcip_update_debug_halt_mask(पूर्णांक cpu)
अणु
	u32 mcip_mask = 0;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&mcip_lock, flags);

	/*
	 * mcip_mask is same क्रम CMD_DEBUG_SET_SELECT and CMD_DEBUG_SET_MASK
	 * commands. So पढ़ो it once instead of पढ़ोing both CMD_DEBUG_READ_MASK
	 * and CMD_DEBUG_READ_SELECT.
	 */
	__mcip_cmd(CMD_DEBUG_READ_SELECT, 0);
	mcip_mask = पढ़ो_aux_reg(ARC_REG_MCIP_READBACK);

	mcip_mask |= BIT(cpu);

	__mcip_cmd_data(CMD_DEBUG_SET_SELECT, 0, mcip_mask);
	/*
	 * Parameter specअगरied halt cause:
	 * STATUS32[H]/actionpoपूर्णांक/अवरोधpoपूर्णांक/self-halt
	 * We choose all of them (0xF).
	 */
	__mcip_cmd_data(CMD_DEBUG_SET_MASK, 0xF, mcip_mask);

	raw_spin_unlock_irqrestore(&mcip_lock, flags);
पूर्ण

अटल व्योम mcip_setup_per_cpu(पूर्णांक cpu)
अणु
	काष्ठा mcip_bcr mp;

	READ_BCR(ARC_REG_MCIP_BCR, mp);

	smp_ipi_irq_setup(cpu, IPI_IRQ);
	smp_ipi_irq_setup(cpu, SOFTIRQ_IRQ);

	/* Update GFRC halt mask as new CPU came online */
	अगर (mp.gfrc)
		mcip_update_gfrc_halt_mask(cpu);

	/* Update MCIP debug mask as new CPU came online */
	अगर (mp.dbg)
		mcip_update_debug_halt_mask(cpu);
पूर्ण

अटल व्योम mcip_ipi_send(पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ipi_was_pending;

	/* ARConnect can only send IPI to others */
	अगर (unlikely(cpu == raw_smp_processor_id())) अणु
		arc_softirq_trigger(SOFTIRQ_IRQ);
		वापस;
	पूर्ण

	raw_spin_lock_irqsave(&mcip_lock, flags);

	/*
	 * If receiver alपढ़ोy has a pending पूर्णांकerrupt, elide sending this one.
	 * Linux cross core calling works well with concurrent IPIs
	 * coalesced पूर्णांकo one
	 * see arch/arc/kernel/smp.c: ipi_send_msg_one()
	 */
	__mcip_cmd(CMD_INTRPT_READ_STATUS, cpu);
	ipi_was_pending = पढ़ो_aux_reg(ARC_REG_MCIP_READBACK);
	अगर (!ipi_was_pending)
		__mcip_cmd(CMD_INTRPT_GENERATE_IRQ, cpu);

	raw_spin_unlock_irqrestore(&mcip_lock, flags);
पूर्ण

अटल व्योम mcip_ipi_clear(पूर्णांक irq)
अणु
	अचिन्हित पूर्णांक cpu, c;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(irq == SOFTIRQ_IRQ)) अणु
		arc_softirq_clear(irq);
		वापस;
	पूर्ण

	raw_spin_lock_irqsave(&mcip_lock, flags);

	/* Who sent the IPI */
	__mcip_cmd(CMD_INTRPT_CHECK_SOURCE, 0);

	cpu = पढ़ो_aux_reg(ARC_REG_MCIP_READBACK);	/* 1,2,4,8... */

	/*
	 * In rare हाल, multiple concurrent IPIs sent to same target can
	 * possibly be coalesced by MCIP पूर्णांकo 1 निश्चितed IRQ, so @cpus can be
	 * "vectored" (multiple bits sets) as opposed to typical single bit
	 */
	करो अणु
		c = __ffs(cpu);			/* 0,1,2,3 */
		__mcip_cmd(CMD_INTRPT_GENERATE_ACK, c);
		cpu &= ~(1U << c);
	पूर्ण जबतक (cpu);

	raw_spin_unlock_irqrestore(&mcip_lock, flags);
पूर्ण

अटल व्योम mcip_probe_n_setup(व्योम)
अणु
	काष्ठा mcip_bcr mp;

	READ_BCR(ARC_REG_MCIP_BCR, mp);

	प्र_लिखो(smp_cpuinfo_buf,
		"Extn [SMP]\t: ARConnect (v%d): %d cores with %s%s%s%s\n",
		mp.ver, mp.num_cores,
		IS_AVAIL1(mp.ipi, "IPI "),
		IS_AVAIL1(mp.idu, "IDU "),
		IS_AVAIL1(mp.dbg, "DEBUG "),
		IS_AVAIL1(mp.gfrc, "GFRC"));

	cpuinfo_arc700[0].extn.gfrc = mp.gfrc;
पूर्ण

काष्ठा plat_smp_ops plat_smp_ops = अणु
	.info		= smp_cpuinfo_buf,
	.init_early_smp	= mcip_probe_n_setup,
	.init_per_cpu	= mcip_setup_per_cpu,
	.ipi_send	= mcip_ipi_send,
	.ipi_clear	= mcip_ipi_clear,
पूर्ण;

#पूर्ण_अगर

/***************************************************************************
 * ARCv2 Interrupt Distribution Unit (IDU)
 *
 * Connects बाह्यal "COMMON" IRQs to core पूर्णांकc, providing:
 *  -dynamic routing (IRQ affinity)
 *  -load balancing (Round Robin पूर्णांकerrupt distribution)
 *  -1:N distribution
 *
 * It physically resides in the MCIP hw block
 */

#समावेश <linux/irqchip.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>

/*
 * Set the DEST क्रम @cmn_irq to @cpu_mask (1 bit per core)
 */
अटल व्योम idu_set_dest(अचिन्हित पूर्णांक cmn_irq, अचिन्हित पूर्णांक cpu_mask)
अणु
	__mcip_cmd_data(CMD_IDU_SET_DEST, cmn_irq, cpu_mask);
पूर्ण

अटल व्योम idu_set_mode(अचिन्हित पूर्णांक cmn_irq, bool set_lvl, अचिन्हित पूर्णांक lvl,
			 bool set_distr, अचिन्हित पूर्णांक distr)
अणु
	जोड़ अणु
		अचिन्हित पूर्णांक word;
		काष्ठा अणु
			अचिन्हित पूर्णांक distr:2, pad:2, lvl:1, pad2:27;
		पूर्ण;
	पूर्ण data;

	data.word = __mcip_cmd_पढ़ो(CMD_IDU_READ_MODE, cmn_irq);
	अगर (set_distr)
		data.distr = distr;
	अगर (set_lvl)
		data.lvl = lvl;
	__mcip_cmd_data(CMD_IDU_SET_MODE, cmn_irq, data.word);
पूर्ण

अटल व्योम idu_irq_mask_raw(irq_hw_number_t hwirq)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&mcip_lock, flags);
	__mcip_cmd_data(CMD_IDU_SET_MASK, hwirq, 1);
	raw_spin_unlock_irqrestore(&mcip_lock, flags);
पूर्ण

अटल व्योम idu_irq_mask(काष्ठा irq_data *data)
अणु
	idu_irq_mask_raw(data->hwirq);
पूर्ण

अटल व्योम idu_irq_unmask(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&mcip_lock, flags);
	__mcip_cmd_data(CMD_IDU_SET_MASK, data->hwirq, 0);
	raw_spin_unlock_irqrestore(&mcip_lock, flags);
पूर्ण

अटल व्योम idu_irq_ack(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&mcip_lock, flags);
	__mcip_cmd(CMD_IDU_ACK_CIRQ, data->hwirq);
	raw_spin_unlock_irqrestore(&mcip_lock, flags);
पूर्ण

अटल व्योम idu_irq_mask_ack(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&mcip_lock, flags);
	__mcip_cmd_data(CMD_IDU_SET_MASK, data->hwirq, 1);
	__mcip_cmd(CMD_IDU_ACK_CIRQ, data->hwirq);
	raw_spin_unlock_irqrestore(&mcip_lock, flags);
पूर्ण

अटल पूर्णांक
idu_irq_set_affinity(काष्ठा irq_data *data, स्थिर काष्ठा cpumask *cpumask,
		     bool क्रमce)
अणु
	अचिन्हित दीर्घ flags;
	cpumask_t online;
	अचिन्हित पूर्णांक destination_bits;
	अचिन्हित पूर्णांक distribution_mode;

	/* errout अगर no online cpu per @cpumask */
	अगर (!cpumask_and(&online, cpumask, cpu_online_mask))
		वापस -EINVAL;

	raw_spin_lock_irqsave(&mcip_lock, flags);

	destination_bits = cpumask_bits(&online)[0];
	idu_set_dest(data->hwirq, destination_bits);

	अगर (ffs(destination_bits) == fls(destination_bits))
		distribution_mode = IDU_M_DISTRI_DEST;
	अन्यथा
		distribution_mode = IDU_M_DISTRI_RR;

	idu_set_mode(data->hwirq, false, 0, true, distribution_mode);

	raw_spin_unlock_irqrestore(&mcip_lock, flags);

	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल पूर्णांक idu_irq_set_type(काष्ठा irq_data *data, u32 type)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * ARCv2 IDU HW करोes not support inverse polarity, so these are the
	 * only पूर्णांकerrupt types supported.
	 */
	अगर (type & ~(IRQ_TYPE_EDGE_RISING | IRQ_TYPE_LEVEL_HIGH))
		वापस -EINVAL;

	raw_spin_lock_irqsave(&mcip_lock, flags);

	idu_set_mode(data->hwirq, true,
		     type & IRQ_TYPE_EDGE_RISING ? IDU_M_TRIG_EDGE :
						   IDU_M_TRIG_LEVEL,
		     false, 0);

	raw_spin_unlock_irqrestore(&mcip_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम idu_irq_enable(काष्ठा irq_data *data)
अणु
	/*
	 * By शेष send all common पूर्णांकerrupts to all available online CPUs.
	 * The affinity of common पूर्णांकerrupts in IDU must be set manually since
	 * in some हालs the kernel will not call irq_set_affinity() by itself:
	 *   1. When the kernel is not configured with support of SMP.
	 *   2. When the kernel is configured with support of SMP but upper
	 *      पूर्णांकerrupt controllers करोes not support setting of the affinity
	 *      and cannot propagate it to IDU.
	 */
	idu_irq_set_affinity(data, cpu_online_mask, false);
	idu_irq_unmask(data);
पूर्ण

अटल काष्ठा irq_chip idu_irq_chip = अणु
	.name			= "MCIP IDU Intc",
	.irq_mask		= idu_irq_mask,
	.irq_unmask		= idu_irq_unmask,
	.irq_ack		= idu_irq_ack,
	.irq_mask_ack		= idu_irq_mask_ack,
	.irq_enable		= idu_irq_enable,
	.irq_set_type		= idu_irq_set_type,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity       = idu_irq_set_affinity,
#पूर्ण_अगर

पूर्ण;

अटल व्योम idu_cascade_isr(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_करोमुख्य *idu_करोमुख्य = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *core_chip = irq_desc_get_chip(desc);
	irq_hw_number_t core_hwirq = irqd_to_hwirq(irq_desc_get_irq_data(desc));
	irq_hw_number_t idu_hwirq = core_hwirq - FIRST_EXT_IRQ;

	chained_irq_enter(core_chip, desc);
	generic_handle_irq(irq_find_mapping(idu_करोमुख्य, idu_hwirq));
	chained_irq_निकास(core_chip, desc);
पूर्ण

अटल पूर्णांक idu_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq, irq_hw_number_t hwirq)
अणु
	irq_set_chip_and_handler(virq, &idu_irq_chip, handle_level_irq);
	irq_set_status_flags(virq, IRQ_MOVE_PCNTXT);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops idu_irq_ops = अणु
	.xlate	= irq_करोमुख्य_xlate_onetwocell,
	.map	= idu_irq_map,
पूर्ण;

/*
 * [16, 23]: Statically asचिन्हित always निजी-per-core (Timers, WDT, IPI)
 * [24, 23+C]: If C > 0 then "C" common IRQs
 * [24+C, N]: Not अटलally asचिन्हित, निजी-per-core
 */


अटल पूर्णांक __init
idu_of_init(काष्ठा device_node *पूर्णांकc, काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	पूर्णांक nr_irqs;
	पूर्णांक i, virq;
	काष्ठा mcip_bcr mp;
	काष्ठा mcip_idu_bcr idu_bcr;

	READ_BCR(ARC_REG_MCIP_BCR, mp);

	अगर (!mp.idu)
		panic("IDU not detected, but DeviceTree using it");

	READ_BCR(ARC_REG_MCIP_IDU_BCR, idu_bcr);
	nr_irqs = mcip_idu_bcr_to_nr_irqs(idu_bcr);

	pr_info("MCIP: IDU supports %u common irqs\n", nr_irqs);

	करोमुख्य = irq_करोमुख्य_add_linear(पूर्णांकc, nr_irqs, &idu_irq_ops, शून्य);

	/* Parent पूर्णांकerrupts (core-पूर्णांकc) are alपढ़ोy mapped */

	क्रम (i = 0; i < nr_irqs; i++) अणु
		/* Mask all common पूर्णांकerrupts by शेष */
		idu_irq_mask_raw(i);

		/*
		 * Return parent uplink IRQs (towards core पूर्णांकc) 24,25,.....
		 * this step has been करोne beक्रमe alपढ़ोy
		 * however we need it to get the parent virq and set IDU handler
		 * as first level isr
		 */
		virq = irq_create_mapping(शून्य, i + FIRST_EXT_IRQ);
		BUG_ON(!virq);
		irq_set_chained_handler_and_data(virq, idu_cascade_isr, करोमुख्य);
	पूर्ण

	__mcip_cmd(CMD_IDU_ENABLE, 0);

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(arcv2_idu_पूर्णांकc, "snps,archs-idu-intc", idu_of_init);
