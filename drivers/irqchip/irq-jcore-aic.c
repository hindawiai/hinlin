<शैली गुरु>
/*
 * J-Core SoC AIC driver
 *
 * Copyright (C) 2015-2016 Smart Energy Instruments, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/cpu.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#घोषणा JCORE_AIC_MAX_HWIRQ	127
#घोषणा JCORE_AIC1_MIN_HWIRQ	16
#घोषणा JCORE_AIC2_MIN_HWIRQ	64

#घोषणा JCORE_AIC1_INTPRI_REG	8

अटल काष्ठा irq_chip jcore_aic;

/*
 * The J-Core AIC1 and AIC2 are cpu-local पूर्णांकerrupt controllers and करो
 * not distinguish or use distinct irq number ranges क्रम per-cpu event
 * पूर्णांकerrupts (समयr, IPI). Since inक्रमmation to determine whether a
 * particular irq number should be treated as per-cpu is not available
 * at mapping समय, we use a wrapper handler function which chooses
 * the right handler at runसमय based on whether IRQF_PERCPU was used
 * when requesting the irq.
 */

अटल व्योम handle_jcore_irq(काष्ठा irq_desc *desc)
अणु
	अगर (irqd_is_per_cpu(irq_desc_get_irq_data(desc)))
		handle_percpu_irq(desc);
	अन्यथा
		handle_simple_irq(desc);
पूर्ण

अटल पूर्णांक jcore_aic_irqकरोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
				   irq_hw_number_t hwirq)
अणु
	काष्ठा irq_chip *aic = d->host_data;

	irq_set_chip_and_handler(irq, aic, handle_jcore_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops jcore_aic_irqकरोमुख्य_ops = अणु
	.map = jcore_aic_irqकरोमुख्य_map,
	.xlate = irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल व्योम noop(काष्ठा irq_data *data)
अणु
पूर्ण

अटल पूर्णांक __init aic_irq_of_init(काष्ठा device_node *node,
				  काष्ठा device_node *parent)
अणु
	अचिन्हित min_irq = JCORE_AIC2_MIN_HWIRQ;
	अचिन्हित करोm_sz = JCORE_AIC_MAX_HWIRQ+1;
	काष्ठा irq_करोमुख्य *करोमुख्य;

	pr_info("Initializing J-Core AIC\n");

	/* AIC1 needs priority initialization to receive पूर्णांकerrupts. */
	अगर (of_device_is_compatible(node, "jcore,aic1")) अणु
		अचिन्हित cpu;

		क्रम_each_present_cpu(cpu) अणु
			व्योम __iomem *base = of_iomap(node, cpu);

			अगर (!base) अणु
				pr_err("Unable to map AIC for cpu %u\n", cpu);
				वापस -ENOMEM;
			पूर्ण
			__raw_ग_लिखोl(0xffffffff, base + JCORE_AIC1_INTPRI_REG);
			iounmap(base);
		पूर्ण
		min_irq = JCORE_AIC1_MIN_HWIRQ;
	पूर्ण

	/*
	 * The irq chip framework requires either mask/unmask or enable/disable
	 * function poपूर्णांकers to be provided, but the hardware करोes not have any
	 * such mechanism; the only पूर्णांकerrupt masking is at the cpu level and
	 * it affects all पूर्णांकerrupts. We provide dummy mask/unmask. The hardware
	 * handles all पूर्णांकerrupt control and clears pending status when the cpu
	 * accepts the पूर्णांकerrupt.
	 */
	jcore_aic.irq_mask = noop;
	jcore_aic.irq_unmask = noop;
	jcore_aic.name = "AIC";

	करोमुख्य = irq_करोमुख्य_add_legacy(node, करोm_sz - min_irq, min_irq, min_irq,
				       &jcore_aic_irqकरोमुख्य_ops,
				       &jcore_aic);
	अगर (!करोमुख्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

IRQCHIP_DECLARE(jcore_aic2, "jcore,aic2", aic_irq_of_init);
IRQCHIP_DECLARE(jcore_aic1, "jcore,aic1", aic_irq_of_init);
