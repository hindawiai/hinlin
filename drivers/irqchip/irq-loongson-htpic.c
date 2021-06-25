<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2020, Jiaxun Yang <jiaxun.yang@flygoat.com>
 *  Loongson HTPIC IRQ support
 */

#समावेश <linux/init.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/syscore_ops.h>

#समावेश <यंत्र/i8259.h>

#घोषणा HTPIC_MAX_PARENT_IRQ	4
#घोषणा HTINT_NUM_VECTORS	8
#घोषणा HTINT_EN_OFF		0x20

काष्ठा loongson_htpic अणु
	व्योम __iomem *base;
	काष्ठा irq_करोमुख्य *करोमुख्य;
पूर्ण;

अटल काष्ठा loongson_htpic *htpic;

अटल व्योम htpic_irq_dispatch(काष्ठा irq_desc *desc)
अणु
	काष्ठा loongson_htpic *priv = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	uपूर्णांक32_t pending;

	chained_irq_enter(chip, desc);
	pending = पढ़ोl(priv->base);
	/* Ack all IRQs at once, otherwise IRQ flood might happen */
	ग_लिखोl(pending, priv->base);

	अगर (!pending)
		spurious_पूर्णांकerrupt();

	जबतक (pending) अणु
		पूर्णांक bit = __ffs(pending);

		अगर (unlikely(bit > 15)) अणु
			spurious_पूर्णांकerrupt();
			अवरोध;
		पूर्ण

		generic_handle_irq(irq_linear_revmap(priv->करोमुख्य, bit));
		pending &= ~BIT(bit);
	पूर्ण
	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम htpic_reg_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < HTINT_NUM_VECTORS; i++) अणु
		/* Disable all HT Vectors */
		ग_लिखोl(0x0, htpic->base + HTINT_EN_OFF + i * 0x4);
		/* Read back to क्रमce ग_लिखो */
		(व्योम) पढ़ोl(htpic->base + i * 0x4);
		/* Ack all possible pending IRQs */
		ग_लिखोl(GENMASK(31, 0), htpic->base + i * 0x4);
	पूर्ण

	/* Enable 16 vectors क्रम PIC */
	ग_लिखोl(0xffff, htpic->base + HTINT_EN_OFF);
पूर्ण

अटल व्योम htpic_resume(व्योम)
अणु
	htpic_reg_init();
पूर्ण

काष्ठा syscore_ops htpic_syscore_ops = अणु
	.resume		= htpic_resume,
पूर्ण;

अटल पूर्णांक __init htpic_of_init(काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	अचिन्हित पूर्णांक parent_irq[4];
	पूर्णांक i, err;
	पूर्णांक num_parents = 0;

	अगर (htpic) अणु
		pr_err("loongson-htpic: Only one HTPIC is allowed in the system\n");
		वापस -ENODEV;
	पूर्ण

	htpic = kzalloc(माप(*htpic), GFP_KERNEL);
	अगर (!htpic)
		वापस -ENOMEM;

	htpic->base = of_iomap(node, 0);
	अगर (!htpic->base) अणु
		err = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	htpic->करोमुख्य = __init_i8259_irqs(node);
	अगर (!htpic->करोमुख्य) अणु
		pr_err("loongson-htpic: Failed to initialize i8259 IRQs\n");
		err = -ENOMEM;
		जाओ out_iounmap;
	पूर्ण

	/* Interrupt may come from any of the 4 पूर्णांकerrupt line */
	क्रम (i = 0; i < HTPIC_MAX_PARENT_IRQ; i++) अणु
		parent_irq[i] = irq_of_parse_and_map(node, i);
		अगर (parent_irq[i] <= 0)
			अवरोध;

		num_parents++;
	पूर्ण

	अगर (!num_parents) अणु
		pr_err("loongson-htpic: Failed to get parent irqs\n");
		err = -ENODEV;
		जाओ out_हटाओ_करोमुख्य;
	पूर्ण

	htpic_reg_init();

	क्रम (i = 0; i < num_parents; i++) अणु
		irq_set_chained_handler_and_data(parent_irq[i],
						htpic_irq_dispatch, htpic);
	पूर्ण

	रेजिस्टर_syscore_ops(&htpic_syscore_ops);

	वापस 0;

out_हटाओ_करोमुख्य:
	irq_करोमुख्य_हटाओ(htpic->करोमुख्य);
out_iounmap:
	iounmap(htpic->base);
out_मुक्त:
	kमुक्त(htpic);
	वापस err;
पूर्ण

IRQCHIP_DECLARE(loongson_htpic, "loongson,htpic-1.0", htpic_of_init);
