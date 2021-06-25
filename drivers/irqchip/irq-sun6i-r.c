<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * The R_INTC in Allwinner A31 and newer SoCs manages several types of
 * पूर्णांकerrupts, as shown below:
 *
 *             NMI IRQ                सूचीECT IRQs           MUXED IRQs
 *              bit 0                  bits 1-15^           bits 19-31
 *
 *   +---------+                      +---------+    +---------+  +---------+
 *   | NMI Pad |                      |  IRQ d  |    |  IRQ m  |  | IRQ m+7 |
 *   +---------+                      +---------+    +---------+  +---------+
 *        |                             |     |         |    |      |    |
 *        |                             |     |         |    |......|    |
 * +------V------+ +------------+       |     |         | +--V------V--+ |
 * |   Invert/   | | Write 1 to |       |     |         | |  AND with  | |
 * | Edge Detect | | PENDING[0] |       |     |         | |  MUX[m/8]  | |
 * +-------------+ +------------+       |     |         | +------------+ |
 *            |       |                 |     |         |       |        |
 *         +--V-------V--+           +--V--+  |      +--V--+    |     +--V--+
 *         | Set    Reset|           | GIC |  |      | GIC |    |     | GIC |
 *         |    Latch    |           | SPI |  |      | SPI |... |  ...| SPI |
 *         +-------------+           | N+d |  |      |  m  |    |     | m+7 |
 *             |     |               +-----+  |      +-----+    |     +-----+
 *             |     |                        |                 |
 *     +-------V-+ +-V----------+   +---------V--+     +--------V--------+
 *     | GIC SPI | |  AND with  |   |  AND with  |     |    AND with     |
 *     | N (=32) | |  ENABLE[0] |   |  ENABLE[d] |     |  ENABLE[19+m/8] |
 *     +---------+ +------------+   +------------+     +-----------------+
 *                        |                |                    |
 *                 +------V-----+   +------V-----+     +--------V--------+
 *                 |    Read    |   |    Read    |     |     Read        |
 *                 | PENDING[0] |   | PENDING[d] |     | PENDING[19+m/8] |
 *                 +------------+   +------------+     +-----------------+
 *
 * ^ bits 16-18 are direct IRQs क्रम peripherals with banked पूर्णांकerrupts, such as
 *   the MSGBOX. These IRQs करो not map to any GIC SPI.
 *
 * The H6 variant adds two more (banked) direct IRQs and implements the full
 * set of 128 mux bits. This requires a second set of top-level रेजिस्टरs.
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/syscore_ops.h>

#समावेश <dt-bindings/पूर्णांकerrupt-controller/arm-gic.h>

#घोषणा SUN6I_NMI_CTRL			(0x0c)
#घोषणा SUN6I_IRQ_PENDING(n)		(0x10 + 4 * (n))
#घोषणा SUN6I_IRQ_ENABLE(n)		(0x40 + 4 * (n))
#घोषणा SUN6I_MUX_ENABLE(n)		(0xc0 + 4 * (n))

#घोषणा SUN6I_NMI_SRC_TYPE_LEVEL_LOW	0
#घोषणा SUN6I_NMI_SRC_TYPE_EDGE_FALLING	1
#घोषणा SUN6I_NMI_SRC_TYPE_LEVEL_HIGH	2
#घोषणा SUN6I_NMI_SRC_TYPE_EDGE_RISING	3

#घोषणा SUN6I_NMI_BIT			BIT(0)

#घोषणा SUN6I_NMI_NEEDS_ACK		((व्योम *)1)

#घोषणा SUN6I_NR_TOP_LEVEL_IRQS		64
#घोषणा SUN6I_NR_सूचीECT_IRQS		16
#घोषणा SUN6I_NR_MUX_BITS		128

काष्ठा sun6i_r_पूर्णांकc_variant अणु
	u32		first_mux_irq;
	u32		nr_mux_irqs;
	u32		mux_valid[BITS_TO_U32(SUN6I_NR_MUX_BITS)];
पूर्ण;

अटल व्योम __iomem *base;
अटल irq_hw_number_t nmi_hwirq;
अटल DECLARE_BITMAP(wake_irq_enabled, SUN6I_NR_TOP_LEVEL_IRQS);
अटल DECLARE_BITMAP(wake_mux_enabled, SUN6I_NR_MUX_BITS);
अटल DECLARE_BITMAP(wake_mux_valid, SUN6I_NR_MUX_BITS);

अटल व्योम sun6i_r_पूर्णांकc_ack_nmi(व्योम)
अणु
	ग_लिखोl_relaxed(SUN6I_NMI_BIT, base + SUN6I_IRQ_PENDING(0));
पूर्ण

अटल व्योम sun6i_r_पूर्णांकc_nmi_ack(काष्ठा irq_data *data)
अणु
	अगर (irqd_get_trigger_type(data) & IRQ_TYPE_EDGE_BOTH)
		sun6i_r_पूर्णांकc_ack_nmi();
	अन्यथा
		data->chip_data = SUN6I_NMI_NEEDS_ACK;
पूर्ण

अटल व्योम sun6i_r_पूर्णांकc_nmi_eoi(काष्ठा irq_data *data)
अणु
	/* For oneshot IRQs, delay the ack until the IRQ is unmasked. */
	अगर (data->chip_data == SUN6I_NMI_NEEDS_ACK && !irqd_irq_masked(data)) अणु
		data->chip_data = शून्य;
		sun6i_r_पूर्णांकc_ack_nmi();
	पूर्ण

	irq_chip_eoi_parent(data);
पूर्ण

अटल व्योम sun6i_r_पूर्णांकc_nmi_unmask(काष्ठा irq_data *data)
अणु
	अगर (data->chip_data == SUN6I_NMI_NEEDS_ACK) अणु
		data->chip_data = शून्य;
		sun6i_r_पूर्णांकc_ack_nmi();
	पूर्ण

	irq_chip_unmask_parent(data);
पूर्ण

अटल पूर्णांक sun6i_r_पूर्णांकc_nmi_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	u32 nmi_src_type;

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		nmi_src_type = SUN6I_NMI_SRC_TYPE_EDGE_RISING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		nmi_src_type = SUN6I_NMI_SRC_TYPE_EDGE_FALLING;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		nmi_src_type = SUN6I_NMI_SRC_TYPE_LEVEL_HIGH;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		nmi_src_type = SUN6I_NMI_SRC_TYPE_LEVEL_LOW;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl_relaxed(nmi_src_type, base + SUN6I_NMI_CTRL);

	/*
	 * The "External NMI" GIC input connects to a latch inside R_INTC, not
	 * directly to the pin. So the GIC trigger type करोes not depend on the
	 * NMI pin trigger type.
	 */
	वापस irq_chip_set_type_parent(data, IRQ_TYPE_LEVEL_HIGH);
पूर्ण

अटल पूर्णांक sun6i_r_पूर्णांकc_nmi_set_irqchip_state(काष्ठा irq_data *data,
					      क्रमागत irqchip_irq_state which,
					      bool state)
अणु
	अगर (which == IRQCHIP_STATE_PENDING && !state)
		sun6i_r_पूर्णांकc_ack_nmi();

	वापस irq_chip_set_parent_state(data, which, state);
पूर्ण

अटल पूर्णांक sun6i_r_पूर्णांकc_irq_set_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक on)
अणु
	अचिन्हित दीर्घ offset_from_nmi = data->hwirq - nmi_hwirq;

	अगर (offset_from_nmi < SUN6I_NR_सूचीECT_IRQS)
		assign_bit(offset_from_nmi, wake_irq_enabled, on);
	अन्यथा अगर (test_bit(data->hwirq, wake_mux_valid))
		assign_bit(data->hwirq, wake_mux_enabled, on);
	अन्यथा
		/* Not wakeup capable. */
		वापस -EPERM;

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip sun6i_r_पूर्णांकc_nmi_chip = अणु
	.name			= "sun6i-r-intc",
	.irq_ack		= sun6i_r_पूर्णांकc_nmi_ack,
	.irq_mask		= irq_chip_mask_parent,
	.irq_unmask		= sun6i_r_पूर्णांकc_nmi_unmask,
	.irq_eoi		= sun6i_r_पूर्णांकc_nmi_eoi,
	.irq_set_affinity	= irq_chip_set_affinity_parent,
	.irq_set_type		= sun6i_r_पूर्णांकc_nmi_set_type,
	.irq_set_irqchip_state	= sun6i_r_पूर्णांकc_nmi_set_irqchip_state,
	.irq_set_wake		= sun6i_r_पूर्णांकc_irq_set_wake,
	.flags			= IRQCHIP_SET_TYPE_MASKED,
पूर्ण;

अटल काष्ठा irq_chip sun6i_r_पूर्णांकc_wakeup_chip = अणु
	.name			= "sun6i-r-intc",
	.irq_mask		= irq_chip_mask_parent,
	.irq_unmask		= irq_chip_unmask_parent,
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_set_affinity	= irq_chip_set_affinity_parent,
	.irq_set_type		= irq_chip_set_type_parent,
	.irq_set_wake		= sun6i_r_पूर्णांकc_irq_set_wake,
	.flags			= IRQCHIP_SET_TYPE_MASKED,
पूर्ण;

अटल पूर्णांक sun6i_r_पूर्णांकc_करोमुख्य_translate(काष्ठा irq_करोमुख्य *करोमुख्य,
					 काष्ठा irq_fwspec *fwspec,
					 अचिन्हित दीर्घ *hwirq,
					 अचिन्हित पूर्णांक *type)
अणु
	/* Accept the old two-cell binding क्रम the NMI only. */
	अगर (fwspec->param_count == 2 && fwspec->param[0] == 0) अणु
		*hwirq = nmi_hwirq;
		*type  = fwspec->param[1] & IRQ_TYPE_SENSE_MASK;
		वापस 0;
	पूर्ण

	/* Otherwise this binding should match the GIC SPI binding. */
	अगर (fwspec->param_count < 3)
		वापस -EINVAL;
	अगर (fwspec->param[0] != GIC_SPI)
		वापस -EINVAL;

	*hwirq = fwspec->param[1];
	*type  = fwspec->param[2] & IRQ_TYPE_SENSE_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक sun6i_r_पूर्णांकc_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
				     अचिन्हित पूर्णांक virq,
				     अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	काष्ठा irq_fwspec *fwspec = arg;
	काष्ठा irq_fwspec gic_fwspec;
	अचिन्हित दीर्घ hwirq;
	अचिन्हित पूर्णांक type;
	पूर्णांक i, ret;

	ret = sun6i_r_पूर्णांकc_करोमुख्य_translate(करोमुख्य, fwspec, &hwirq, &type);
	अगर (ret)
		वापस ret;
	अगर (hwirq + nr_irqs > SUN6I_NR_MUX_BITS)
		वापस -EINVAL;

	/* Conकाष्ठा a GIC-compatible fwspec from this fwspec. */
	gic_fwspec = (काष्ठा irq_fwspec) अणु
		.fwnode      = करोमुख्य->parent->fwnode,
		.param_count = 3,
		.param       = अणु GIC_SPI, hwirq, type पूर्ण,
	पूर्ण;

	ret = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, nr_irqs, &gic_fwspec);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < nr_irqs; ++i, ++hwirq, ++virq) अणु
		अगर (hwirq == nmi_hwirq) अणु
			irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq, hwirq,
						      &sun6i_r_पूर्णांकc_nmi_chip, 0);
			irq_set_handler(virq, handle_fasteoi_ack_irq);
		पूर्ण अन्यथा अणु
			irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq, hwirq,
						      &sun6i_r_पूर्णांकc_wakeup_chip, 0);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops sun6i_r_पूर्णांकc_करोमुख्य_ops = अणु
	.translate	= sun6i_r_पूर्णांकc_करोमुख्य_translate,
	.alloc		= sun6i_r_पूर्णांकc_करोमुख्य_alloc,
	.मुक्त		= irq_करोमुख्य_मुक्त_irqs_common,
पूर्ण;

अटल पूर्णांक sun6i_r_पूर्णांकc_suspend(व्योम)
अणु
	u32 buf[BITS_TO_U32(max(SUN6I_NR_TOP_LEVEL_IRQS, SUN6I_NR_MUX_BITS))];
	पूर्णांक i;

	/* Wake IRQs are enabled during प्रणाली sleep and shutकरोwn. */
	biपंचांगap_to_arr32(buf, wake_irq_enabled, SUN6I_NR_TOP_LEVEL_IRQS);
	क्रम (i = 0; i < BITS_TO_U32(SUN6I_NR_TOP_LEVEL_IRQS); ++i)
		ग_लिखोl_relaxed(buf[i], base + SUN6I_IRQ_ENABLE(i));
	biपंचांगap_to_arr32(buf, wake_mux_enabled, SUN6I_NR_MUX_BITS);
	क्रम (i = 0; i < BITS_TO_U32(SUN6I_NR_MUX_BITS); ++i)
		ग_लिखोl_relaxed(buf[i], base + SUN6I_MUX_ENABLE(i));

	वापस 0;
पूर्ण

अटल व्योम sun6i_r_पूर्णांकc_resume(व्योम)
अणु
	पूर्णांक i;

	/* Only the NMI is relevant during normal operation. */
	ग_लिखोl_relaxed(SUN6I_NMI_BIT, base + SUN6I_IRQ_ENABLE(0));
	क्रम (i = 1; i < BITS_TO_U32(SUN6I_NR_TOP_LEVEL_IRQS); ++i)
		ग_लिखोl_relaxed(0, base + SUN6I_IRQ_ENABLE(i));
पूर्ण

अटल व्योम sun6i_r_पूर्णांकc_shutकरोwn(व्योम)
अणु
	sun6i_r_पूर्णांकc_suspend();
पूर्ण

अटल काष्ठा syscore_ops sun6i_r_पूर्णांकc_syscore_ops = अणु
	.suspend	= sun6i_r_पूर्णांकc_suspend,
	.resume		= sun6i_r_पूर्णांकc_resume,
	.shutकरोwn	= sun6i_r_पूर्णांकc_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init sun6i_r_पूर्णांकc_init(काष्ठा device_node *node,
				    काष्ठा device_node *parent,
				    स्थिर काष्ठा sun6i_r_पूर्णांकc_variant *v)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य, *parent_करोमुख्य;
	काष्ठा of_phandle_args nmi_parent;
	पूर्णांक ret;

	/* Extract the NMI hwirq number from the OF node. */
	ret = of_irq_parse_one(node, 0, &nmi_parent);
	अगर (ret)
		वापस ret;
	अगर (nmi_parent.args_count < 3 ||
	    nmi_parent.args[0] != GIC_SPI ||
	    nmi_parent.args[2] != IRQ_TYPE_LEVEL_HIGH)
		वापस -EINVAL;
	nmi_hwirq = nmi_parent.args[1];

	biपंचांगap_set(wake_irq_enabled, v->first_mux_irq, v->nr_mux_irqs);
	biपंचांगap_from_arr32(wake_mux_valid, v->mux_valid, SUN6I_NR_MUX_BITS);

	parent_करोमुख्य = irq_find_host(parent);
	अगर (!parent_करोमुख्य) अणु
		pr_err("%pOF: Failed to obtain parent domain\n", node);
		वापस -ENXIO;
	पूर्ण

	base = of_io_request_and_map(node, 0, शून्य);
	अगर (IS_ERR(base)) अणु
		pr_err("%pOF: Failed to map MMIO region\n", node);
		वापस PTR_ERR(base);
	पूर्ण

	करोमुख्य = irq_करोमुख्य_add_hierarchy(parent_करोमुख्य, 0, 0, node,
					  &sun6i_r_पूर्णांकc_करोमुख्य_ops, शून्य);
	अगर (!करोमुख्य) अणु
		pr_err("%pOF: Failed to allocate domain\n", node);
		iounmap(base);
		वापस -ENOMEM;
	पूर्ण

	रेजिस्टर_syscore_ops(&sun6i_r_पूर्णांकc_syscore_ops);

	sun6i_r_पूर्णांकc_ack_nmi();
	sun6i_r_पूर्णांकc_resume();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sun6i_r_पूर्णांकc_variant sun6i_a31_r_पूर्णांकc_variant __initस्थिर = अणु
	.first_mux_irq	= 19,
	.nr_mux_irqs	= 13,
	.mux_valid	= अणु 0xffffffff, 0xfff80000, 0xffffffff, 0x0000000f पूर्ण,
पूर्ण;

अटल पूर्णांक __init sun6i_a31_r_पूर्णांकc_init(काष्ठा device_node *node,
					काष्ठा device_node *parent)
अणु
	वापस sun6i_r_पूर्णांकc_init(node, parent, &sun6i_a31_r_पूर्णांकc_variant);
पूर्ण
IRQCHIP_DECLARE(sun6i_a31_r_पूर्णांकc, "allwinner,sun6i-a31-r-intc", sun6i_a31_r_पूर्णांकc_init);

अटल स्थिर काष्ठा sun6i_r_पूर्णांकc_variant sun50i_h6_r_पूर्णांकc_variant __initस्थिर = अणु
	.first_mux_irq	= 21,
	.nr_mux_irqs	= 16,
	.mux_valid	= अणु 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff पूर्ण,
पूर्ण;

अटल पूर्णांक __init sun50i_h6_r_पूर्णांकc_init(काष्ठा device_node *node,
					काष्ठा device_node *parent)
अणु
	वापस sun6i_r_पूर्णांकc_init(node, parent, &sun50i_h6_r_पूर्णांकc_variant);
पूर्ण
IRQCHIP_DECLARE(sun50i_h6_r_पूर्णांकc, "allwinner,sun50i-h6-r-intc", sun50i_h6_r_पूर्णांकc_init);
