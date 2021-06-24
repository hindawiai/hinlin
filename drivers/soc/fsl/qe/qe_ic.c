<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/sysdev/qe_lib/qe_ic.c
 *
 * Copyright (C) 2006 Freescale Semiconductor, Inc.  All rights reserved.
 *
 * Author: Li Yang <leoli@मुक्तscale.com>
 * Based on code from Shlomi Gridish <gridish@मुक्तscale.com>
 *
 * QUICC ENGINE Interrupt Controller
 */

#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/irq.h>
#समावेश <linux/reboot.h>
#समावेश <linux/slab.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/sched.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/device.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <soc/fsl/qe/qe.h>

#घोषणा NR_QE_IC_INTS		64

/* QE IC रेजिस्टरs offset */
#घोषणा QEIC_CICR		0x00
#घोषणा QEIC_CIVEC		0x04
#घोषणा QEIC_CIPXCC		0x10
#घोषणा QEIC_CIPYCC		0x14
#घोषणा QEIC_CIPWCC		0x18
#घोषणा QEIC_CIPZCC		0x1c
#घोषणा QEIC_CIMR		0x20
#घोषणा QEIC_CRIMR		0x24
#घोषणा QEIC_CIPRTA		0x30
#घोषणा QEIC_CIPRTB		0x34
#घोषणा QEIC_CHIVEC		0x60

काष्ठा qe_ic अणु
	/* Control रेजिस्टरs offset */
	__be32 __iomem *regs;

	/* The remapper क्रम this QEIC */
	काष्ठा irq_करोमुख्य *irqhost;

	/* The "linux" controller काष्ठा */
	काष्ठा irq_chip hc_irq;

	/* VIRQ numbers of QE high/low irqs */
	अचिन्हित पूर्णांक virq_high;
	अचिन्हित पूर्णांक virq_low;
पूर्ण;

/*
 * QE पूर्णांकerrupt controller पूर्णांकernal काष्ठाure
 */
काष्ठा qe_ic_info अणु
	/* Location of this source at the QIMR रेजिस्टर */
	u32	mask;

	/* Mask रेजिस्टर offset */
	u32	mask_reg;

	/*
	 * For grouped पूर्णांकerrupts sources - the पूर्णांकerrupt code as
	 * appears at the group priority रेजिस्टर
	 */
	u8	pri_code;

	/* Group priority रेजिस्टर offset */
	u32	pri_reg;
पूर्ण;

अटल DEFINE_RAW_SPINLOCK(qe_ic_lock);

अटल काष्ठा qe_ic_info qe_ic_info[] = अणु
	[1] = अणु
	       .mask = 0x00008000,
	       .mask_reg = QEIC_CIMR,
	       .pri_code = 0,
	       .pri_reg = QEIC_CIPWCC,
	       पूर्ण,
	[2] = अणु
	       .mask = 0x00004000,
	       .mask_reg = QEIC_CIMR,
	       .pri_code = 1,
	       .pri_reg = QEIC_CIPWCC,
	       पूर्ण,
	[3] = अणु
	       .mask = 0x00002000,
	       .mask_reg = QEIC_CIMR,
	       .pri_code = 2,
	       .pri_reg = QEIC_CIPWCC,
	       पूर्ण,
	[10] = अणु
		.mask = 0x00000040,
		.mask_reg = QEIC_CIMR,
		.pri_code = 1,
		.pri_reg = QEIC_CIPZCC,
		पूर्ण,
	[11] = अणु
		.mask = 0x00000020,
		.mask_reg = QEIC_CIMR,
		.pri_code = 2,
		.pri_reg = QEIC_CIPZCC,
		पूर्ण,
	[12] = अणु
		.mask = 0x00000010,
		.mask_reg = QEIC_CIMR,
		.pri_code = 3,
		.pri_reg = QEIC_CIPZCC,
		पूर्ण,
	[13] = अणु
		.mask = 0x00000008,
		.mask_reg = QEIC_CIMR,
		.pri_code = 4,
		.pri_reg = QEIC_CIPZCC,
		पूर्ण,
	[14] = अणु
		.mask = 0x00000004,
		.mask_reg = QEIC_CIMR,
		.pri_code = 5,
		.pri_reg = QEIC_CIPZCC,
		पूर्ण,
	[15] = अणु
		.mask = 0x00000002,
		.mask_reg = QEIC_CIMR,
		.pri_code = 6,
		.pri_reg = QEIC_CIPZCC,
		पूर्ण,
	[20] = अणु
		.mask = 0x10000000,
		.mask_reg = QEIC_CRIMR,
		.pri_code = 3,
		.pri_reg = QEIC_CIPRTA,
		पूर्ण,
	[25] = अणु
		.mask = 0x00800000,
		.mask_reg = QEIC_CRIMR,
		.pri_code = 0,
		.pri_reg = QEIC_CIPRTB,
		पूर्ण,
	[26] = अणु
		.mask = 0x00400000,
		.mask_reg = QEIC_CRIMR,
		.pri_code = 1,
		.pri_reg = QEIC_CIPRTB,
		पूर्ण,
	[27] = अणु
		.mask = 0x00200000,
		.mask_reg = QEIC_CRIMR,
		.pri_code = 2,
		.pri_reg = QEIC_CIPRTB,
		पूर्ण,
	[28] = अणु
		.mask = 0x00100000,
		.mask_reg = QEIC_CRIMR,
		.pri_code = 3,
		.pri_reg = QEIC_CIPRTB,
		पूर्ण,
	[32] = अणु
		.mask = 0x80000000,
		.mask_reg = QEIC_CIMR,
		.pri_code = 0,
		.pri_reg = QEIC_CIPXCC,
		पूर्ण,
	[33] = अणु
		.mask = 0x40000000,
		.mask_reg = QEIC_CIMR,
		.pri_code = 1,
		.pri_reg = QEIC_CIPXCC,
		पूर्ण,
	[34] = अणु
		.mask = 0x20000000,
		.mask_reg = QEIC_CIMR,
		.pri_code = 2,
		.pri_reg = QEIC_CIPXCC,
		पूर्ण,
	[35] = अणु
		.mask = 0x10000000,
		.mask_reg = QEIC_CIMR,
		.pri_code = 3,
		.pri_reg = QEIC_CIPXCC,
		पूर्ण,
	[36] = अणु
		.mask = 0x08000000,
		.mask_reg = QEIC_CIMR,
		.pri_code = 4,
		.pri_reg = QEIC_CIPXCC,
		पूर्ण,
	[40] = अणु
		.mask = 0x00800000,
		.mask_reg = QEIC_CIMR,
		.pri_code = 0,
		.pri_reg = QEIC_CIPYCC,
		पूर्ण,
	[41] = अणु
		.mask = 0x00400000,
		.mask_reg = QEIC_CIMR,
		.pri_code = 1,
		.pri_reg = QEIC_CIPYCC,
		पूर्ण,
	[42] = अणु
		.mask = 0x00200000,
		.mask_reg = QEIC_CIMR,
		.pri_code = 2,
		.pri_reg = QEIC_CIPYCC,
		पूर्ण,
	[43] = अणु
		.mask = 0x00100000,
		.mask_reg = QEIC_CIMR,
		.pri_code = 3,
		.pri_reg = QEIC_CIPYCC,
		पूर्ण,
पूर्ण;

अटल अंतरभूत u32 qe_ic_पढ़ो(__be32  __iomem *base, अचिन्हित पूर्णांक reg)
अणु
	वापस ioपढ़ो32be(base + (reg >> 2));
पूर्ण

अटल अंतरभूत व्योम qe_ic_ग_लिखो(__be32  __iomem *base, अचिन्हित पूर्णांक reg,
			       u32 value)
अणु
	ioग_लिखो32be(value, base + (reg >> 2));
पूर्ण

अटल अंतरभूत काष्ठा qe_ic *qe_ic_from_irq(अचिन्हित पूर्णांक virq)
अणु
	वापस irq_get_chip_data(virq);
पूर्ण

अटल अंतरभूत काष्ठा qe_ic *qe_ic_from_irq_data(काष्ठा irq_data *d)
अणु
	वापस irq_data_get_irq_chip_data(d);
पूर्ण

अटल व्योम qe_ic_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा qe_ic *qe_ic = qe_ic_from_irq_data(d);
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);
	अचिन्हित दीर्घ flags;
	u32 temp;

	raw_spin_lock_irqsave(&qe_ic_lock, flags);

	temp = qe_ic_पढ़ो(qe_ic->regs, qe_ic_info[src].mask_reg);
	qe_ic_ग_लिखो(qe_ic->regs, qe_ic_info[src].mask_reg,
		    temp | qe_ic_info[src].mask);

	raw_spin_unlock_irqrestore(&qe_ic_lock, flags);
पूर्ण

अटल व्योम qe_ic_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा qe_ic *qe_ic = qe_ic_from_irq_data(d);
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);
	अचिन्हित दीर्घ flags;
	u32 temp;

	raw_spin_lock_irqsave(&qe_ic_lock, flags);

	temp = qe_ic_पढ़ो(qe_ic->regs, qe_ic_info[src].mask_reg);
	qe_ic_ग_लिखो(qe_ic->regs, qe_ic_info[src].mask_reg,
		    temp & ~qe_ic_info[src].mask);

	/* Flush the above ग_लिखो beक्रमe enabling पूर्णांकerrupts; otherwise,
	 * spurious पूर्णांकerrupts will someबार happen.  To be 100% sure
	 * that the ग_लिखो has reached the device beक्रमe पूर्णांकerrupts are
	 * enabled, the mask रेजिस्टर would have to be पढ़ो back; however,
	 * this is not required क्रम correctness, only to aव्योम wasting
	 * समय on a large number of spurious पूर्णांकerrupts.  In testing,
	 * a sync reduced the observed spurious पूर्णांकerrupts to zero.
	 */
	mb();

	raw_spin_unlock_irqrestore(&qe_ic_lock, flags);
पूर्ण

अटल काष्ठा irq_chip qe_ic_irq_chip = अणु
	.name = "QEIC",
	.irq_unmask = qe_ic_unmask_irq,
	.irq_mask = qe_ic_mask_irq,
	.irq_mask_ack = qe_ic_mask_irq,
पूर्ण;

अटल पूर्णांक qe_ic_host_match(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *node,
			    क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	/* Exact match, unless qe_ic node is शून्य */
	काष्ठा device_node *of_node = irq_करोमुख्य_get_of_node(h);
	वापस of_node == शून्य || of_node == node;
पूर्ण

अटल पूर्णांक qe_ic_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			  irq_hw_number_t hw)
अणु
	काष्ठा qe_ic *qe_ic = h->host_data;
	काष्ठा irq_chip *chip;

	अगर (hw >= ARRAY_SIZE(qe_ic_info)) अणु
		pr_err("%s: Invalid hw irq number for QEIC\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (qe_ic_info[hw].mask == 0) अणु
		prपूर्णांकk(KERN_ERR "Can't map reserved IRQ\n");
		वापस -EINVAL;
	पूर्ण
	/* Default chip */
	chip = &qe_ic->hc_irq;

	irq_set_chip_data(virq, qe_ic);
	irq_set_status_flags(virq, IRQ_LEVEL);

	irq_set_chip_and_handler(virq, chip, handle_level_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops qe_ic_host_ops = अणु
	.match = qe_ic_host_match,
	.map = qe_ic_host_map,
	.xlate = irq_करोमुख्य_xlate_onetwocell,
पूर्ण;

/* Return an पूर्णांकerrupt vector or 0 अगर no पूर्णांकerrupt is pending. */
अटल अचिन्हित पूर्णांक qe_ic_get_low_irq(काष्ठा qe_ic *qe_ic)
अणु
	पूर्णांक irq;

	BUG_ON(qe_ic == शून्य);

	/* get the पूर्णांकerrupt source vector. */
	irq = qe_ic_पढ़ो(qe_ic->regs, QEIC_CIVEC) >> 26;

	अगर (irq == 0)
		वापस 0;

	वापस irq_linear_revmap(qe_ic->irqhost, irq);
पूर्ण

/* Return an पूर्णांकerrupt vector or 0 अगर no पूर्णांकerrupt is pending. */
अटल अचिन्हित पूर्णांक qe_ic_get_high_irq(काष्ठा qe_ic *qe_ic)
अणु
	पूर्णांक irq;

	BUG_ON(qe_ic == शून्य);

	/* get the पूर्णांकerrupt source vector. */
	irq = qe_ic_पढ़ो(qe_ic->regs, QEIC_CHIVEC) >> 26;

	अगर (irq == 0)
		वापस 0;

	वापस irq_linear_revmap(qe_ic->irqhost, irq);
पूर्ण

अटल व्योम qe_ic_cascade_low(काष्ठा irq_desc *desc)
अणु
	काष्ठा qe_ic *qe_ic = irq_desc_get_handler_data(desc);
	अचिन्हित पूर्णांक cascade_irq = qe_ic_get_low_irq(qe_ic);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);

	अगर (cascade_irq != 0)
		generic_handle_irq(cascade_irq);

	अगर (chip->irq_eoi)
		chip->irq_eoi(&desc->irq_data);
पूर्ण

अटल व्योम qe_ic_cascade_high(काष्ठा irq_desc *desc)
अणु
	काष्ठा qe_ic *qe_ic = irq_desc_get_handler_data(desc);
	अचिन्हित पूर्णांक cascade_irq = qe_ic_get_high_irq(qe_ic);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);

	अगर (cascade_irq != 0)
		generic_handle_irq(cascade_irq);

	अगर (chip->irq_eoi)
		chip->irq_eoi(&desc->irq_data);
पूर्ण

अटल व्योम qe_ic_cascade_muxed_mpic(काष्ठा irq_desc *desc)
अणु
	काष्ठा qe_ic *qe_ic = irq_desc_get_handler_data(desc);
	अचिन्हित पूर्णांक cascade_irq;
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);

	cascade_irq = qe_ic_get_high_irq(qe_ic);
	अगर (cascade_irq == 0)
		cascade_irq = qe_ic_get_low_irq(qe_ic);

	अगर (cascade_irq != 0)
		generic_handle_irq(cascade_irq);

	chip->irq_eoi(&desc->irq_data);
पूर्ण

अटल व्योम __init qe_ic_init(काष्ठा device_node *node)
अणु
	व्योम (*low_handler)(काष्ठा irq_desc *desc);
	व्योम (*high_handler)(काष्ठा irq_desc *desc);
	काष्ठा qe_ic *qe_ic;
	काष्ठा resource res;
	u32 ret;

	ret = of_address_to_resource(node, 0, &res);
	अगर (ret)
		वापस;

	qe_ic = kzalloc(माप(*qe_ic), GFP_KERNEL);
	अगर (qe_ic == शून्य)
		वापस;

	qe_ic->irqhost = irq_करोमुख्य_add_linear(node, NR_QE_IC_INTS,
					       &qe_ic_host_ops, qe_ic);
	अगर (qe_ic->irqhost == शून्य) अणु
		kमुक्त(qe_ic);
		वापस;
	पूर्ण

	qe_ic->regs = ioremap(res.start, resource_size(&res));

	qe_ic->hc_irq = qe_ic_irq_chip;

	qe_ic->virq_high = irq_of_parse_and_map(node, 0);
	qe_ic->virq_low = irq_of_parse_and_map(node, 1);

	अगर (!qe_ic->virq_low) अणु
		prपूर्णांकk(KERN_ERR "Failed to map QE_IC low IRQ\n");
		kमुक्त(qe_ic);
		वापस;
	पूर्ण
	अगर (qe_ic->virq_high != qe_ic->virq_low) अणु
		low_handler = qe_ic_cascade_low;
		high_handler = qe_ic_cascade_high;
	पूर्ण अन्यथा अणु
		low_handler = qe_ic_cascade_muxed_mpic;
		high_handler = शून्य;
	पूर्ण

	qe_ic_ग_लिखो(qe_ic->regs, QEIC_CICR, 0);

	irq_set_handler_data(qe_ic->virq_low, qe_ic);
	irq_set_chained_handler(qe_ic->virq_low, low_handler);

	अगर (qe_ic->virq_high && qe_ic->virq_high != qe_ic->virq_low) अणु
		irq_set_handler_data(qe_ic->virq_high, qe_ic);
		irq_set_chained_handler(qe_ic->virq_high, high_handler);
	पूर्ण
पूर्ण

अटल पूर्णांक __init qe_ic_of_init(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,qe-ic");
	अगर (!np) अणु
		np = of_find_node_by_type(शून्य, "qeic");
		अगर (!np)
			वापस -ENODEV;
	पूर्ण
	qe_ic_init(np);
	of_node_put(np);
	वापस 0;
पूर्ण
subsys_initcall(qe_ic_of_init);
