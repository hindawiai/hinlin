<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip.h>
#समावेश <यंत्र/irq.h>

#घोषणा NR_EXCEPTIONS	16

काष्ठा bcr_irq_arcv2 अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक pad:3, firq:1, prio:4, exts:8, irqs:8, ver:8;
#अन्यथा
	अचिन्हित पूर्णांक ver:8, irqs:8, exts:8, prio:4, firq:1, pad:3;
#पूर्ण_अगर
पूर्ण;

/*
 * Early Hardware specअगरic Interrupt setup
 * -Called very early (start_kernel -> setup_arch -> setup_processor)
 * -Platक्रमm Independent (must क्रम any ARC Core)
 * -Needed क्रम each CPU (hence not foldable पूर्णांकo init_IRQ)
 */
व्योम arc_init_IRQ(व्योम)
अणु
	अचिन्हित पूर्णांक पंचांगp, irq_prio, i;
	काष्ठा bcr_irq_arcv2 irq_bcr;

	काष्ठा aux_irq_ctrl अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
		अचिन्हित पूर्णांक res3:18, save_idx_regs:1, res2:1,
			     save_u_to_u:1, save_lp_regs:1, save_blink:1,
			     res:4, save_nr_gpr_pairs:5;
#अन्यथा
		अचिन्हित पूर्णांक save_nr_gpr_pairs:5, res:4,
			     save_blink:1, save_lp_regs:1, save_u_to_u:1,
			     res2:1, save_idx_regs:1, res3:18;
#पूर्ण_अगर
	पूर्ण ictrl;

	*(अचिन्हित पूर्णांक *)&ictrl = 0;

#अगर_अघोषित CONFIG_ARC_IRQ_NO_AUTOSAVE
	ictrl.save_nr_gpr_pairs = 6;	/* r0 to r11 (r12 saved manually) */
	ictrl.save_blink = 1;
	ictrl.save_lp_regs = 1;		/* LP_COUNT, LP_START, LP_END */
	ictrl.save_u_to_u = 0;		/* user ctxt saved on kernel stack */
	ictrl.save_idx_regs = 1;	/* JLI, LDI, EI */
#पूर्ण_अगर

	WRITE_AUX(AUX_IRQ_CTRL, ictrl);

	/*
	 * ARCv2 core पूर्णांकc provides multiple पूर्णांकerrupt priorities (upto 16).
	 * Typical builds though have only two levels (0-high, 1-low)
	 * Linux by शेष uses lower prio 1 क्रम most irqs, reserving 0 क्रम
	 * NMI style पूर्णांकerrupts in future (say perf)
	 */

	READ_BCR(ARC_REG_IRQ_BCR, irq_bcr);

	irq_prio = irq_bcr.prio;	/* Encoded as N-1 क्रम N levels */
	pr_info("archs-intc\t: %d priority levels (default %d)%s\n",
		irq_prio + 1, ARCV2_IRQ_DEF_PRIO,
		irq_bcr.firq ? " FIRQ (not used)":"");

	/*
	 * Set a शेष priority क्रम all available पूर्णांकerrupts to prevent
	 * चयनing of रेजिस्टर banks अगर Fast IRQ and multiple रेजिस्टर banks
	 * are supported by CPU.
	 * Also disable निजी-per-core IRQ lines so faulty बाह्यal HW won't
	 * trigger पूर्णांकerrupt that kernel is not पढ़ोy to handle.
	 */
	क्रम (i = NR_EXCEPTIONS; i < irq_bcr.irqs + NR_EXCEPTIONS; i++) अणु
		ग_लिखो_aux_reg(AUX_IRQ_SELECT, i);
		ग_लिखो_aux_reg(AUX_IRQ_PRIORITY, ARCV2_IRQ_DEF_PRIO);

		/*
		 * Only mask cpu निजी IRQs here.
		 * "common" पूर्णांकerrupts are masked at IDU, otherwise it would
		 * need to be unmasked at each cpu, with IPIs
		 */
		अगर (i < FIRST_EXT_IRQ)
			ग_लिखो_aux_reg(AUX_IRQ_ENABLE, 0);
	पूर्ण

	/* setup status32, करोn't enable intr yet as kernel doesn't want */
	पंचांगp = पढ़ो_aux_reg(ARC_REG_STATUS32);
	पंचांगp |= ARCV2_IRQ_DEF_PRIO << 1;
	पंचांगp &= ~STATUS_IE_MASK;
	यंत्र अस्थिर("kflag %0	\n"::"r"(पंचांगp));
पूर्ण

अटल व्योम arcv2_irq_mask(काष्ठा irq_data *data)
अणु
	ग_लिखो_aux_reg(AUX_IRQ_SELECT, data->hwirq);
	ग_लिखो_aux_reg(AUX_IRQ_ENABLE, 0);
पूर्ण

अटल व्योम arcv2_irq_unmask(काष्ठा irq_data *data)
अणु
	ग_लिखो_aux_reg(AUX_IRQ_SELECT, data->hwirq);
	ग_लिखो_aux_reg(AUX_IRQ_ENABLE, 1);
पूर्ण

व्योम arcv2_irq_enable(काष्ठा irq_data *data)
अणु
	/* set शेष priority */
	ग_लिखो_aux_reg(AUX_IRQ_SELECT, data->hwirq);
	ग_लिखो_aux_reg(AUX_IRQ_PRIORITY, ARCV2_IRQ_DEF_PRIO);

	/*
	 * hw स्वतः enables (linux unmask) all by शेष
	 * So no need to करो IRQ_ENABLE here
	 * XXX: However OSCI LAN need it
	 */
	ग_लिखो_aux_reg(AUX_IRQ_ENABLE, 1);
पूर्ण

अटल काष्ठा irq_chip arcv2_irq_chip = अणु
	.name           = "ARCv2 core Intc",
	.irq_mask	= arcv2_irq_mask,
	.irq_unmask	= arcv2_irq_unmask,
	.irq_enable	= arcv2_irq_enable
पूर्ण;

अटल पूर्णांक arcv2_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
			 irq_hw_number_t hw)
अणु
	/*
	 * core पूर्णांकc IRQs [16, 23]:
	 * Statically asचिन्हित always निजी-per-core (Timers, WDT, IPI, PCT)
	 */
	अगर (hw < FIRST_EXT_IRQ) अणु
		/*
		 * A subsequent request_percpu_irq() fails अगर percpu_devid is
		 * not set. That in turns sets NOAUTOEN, meaning each core needs
		 * to call enable_percpu_irq()
		 */
		irq_set_percpu_devid(irq);
		irq_set_chip_and_handler(irq, &arcv2_irq_chip, handle_percpu_irq);
	पूर्ण अन्यथा अणु
		irq_set_chip_and_handler(irq, &arcv2_irq_chip, handle_level_irq);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops arcv2_irq_ops = अणु
	.xlate = irq_करोमुख्य_xlate_onecell,
	.map = arcv2_irq_map,
पूर्ण;


अटल पूर्णांक __init
init_onchip_IRQ(काष्ठा device_node *पूर्णांकc, काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *root_करोमुख्य;
	काष्ठा bcr_irq_arcv2 irq_bcr;
	अचिन्हित पूर्णांक nr_cpu_irqs;

	READ_BCR(ARC_REG_IRQ_BCR, irq_bcr);
	nr_cpu_irqs = irq_bcr.irqs + NR_EXCEPTIONS;

	अगर (parent)
		panic("DeviceTree incore intc not a root irq controller\n");

	root_करोमुख्य = irq_करोमुख्य_add_linear(पूर्णांकc, nr_cpu_irqs, &arcv2_irq_ops, शून्य);
	अगर (!root_करोमुख्य)
		panic("root irq domain not avail\n");

	/*
	 * Needed क्रम primary करोमुख्य lookup to succeed
	 * This is a primary irqchip, and can never have a parent
	 */
	irq_set_शेष_host(root_करोमुख्य);

#अगर_घोषित CONFIG_SMP
	irq_create_mapping(root_करोमुख्य, IPI_IRQ);
#पूर्ण_अगर
	irq_create_mapping(root_करोमुख्य, SOFTIRQ_IRQ);

	वापस 0;
पूर्ण

IRQCHIP_DECLARE(arc_पूर्णांकc, "snps,archs-intc", init_onchip_IRQ);
