<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * H8S पूर्णांकerrupt controller driver
 *
 * Copyright 2015 Yoshinori Sato <ysato@users.sourceक्रमge.jp>
 */

#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <यंत्र/पन.स>

अटल व्योम *पूर्णांकc_baseaddr;
#घोषणा IPRA (पूर्णांकc_baseaddr)

अटल स्थिर अचिन्हित अक्षर ipr_table[] = अणु
	0x03, 0x02, 0x01, 0x00, 0x13, 0x12, 0x11, 0x10, /* 16 - 23 */
	0x23, 0x22, 0x21, 0x20, 0x33, 0x32, 0x31, 0x30, /* 24 - 31 */
	0x43, 0x42, 0x41, 0x40, 0x53, 0x53, 0x52, 0x52, /* 32 - 39 */
	0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, /* 40 - 47 */
	0x50, 0x50, 0x50, 0x50, 0x63, 0x63, 0x63, 0x63, /* 48 - 55 */
	0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0x62, /* 56 - 63 */
	0x61, 0x61, 0x61, 0x61, 0x60, 0x60, 0x60, 0x60, /* 64 - 71 */
	0x73, 0x73, 0x73, 0x73, 0x72, 0x72, 0x72, 0x72, /* 72 - 79 */
	0x71, 0x71, 0x71, 0x71, 0x70, 0x83, 0x82, 0x81, /* 80 - 87 */
	0x80, 0x80, 0x80, 0x80, 0x93, 0x93, 0x93, 0x93, /* 88 - 95 */
	0x92, 0x92, 0x92, 0x92, 0x91, 0x91, 0x91, 0x91, /* 96 - 103 */
	0x90, 0x90, 0x90, 0x90, 0xa3, 0xa3, 0xa3, 0xa3, /* 104 - 111 */
	0xa2, 0xa2, 0xa2, 0xa2, 0xa1, 0xa1, 0xa1, 0xa1, /* 112 - 119 */
	0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, /* 120 - 127 */
पूर्ण;

अटल व्योम h8s_disable_irq(काष्ठा irq_data *data)
अणु
	पूर्णांक pos;
	व्योम __iomem *addr;
	अचिन्हित लघु pri;
	पूर्णांक irq = data->irq;

	addr = IPRA + ((ipr_table[irq - 16] & 0xf0) >> 3);
	pos = (ipr_table[irq - 16] & 0x0f) * 4;
	pri = ~(0x000f << pos);
	pri &= पढ़ोw(addr);
	ग_लिखोw(pri, addr);
पूर्ण

अटल व्योम h8s_enable_irq(काष्ठा irq_data *data)
अणु
	पूर्णांक pos;
	व्योम __iomem *addr;
	अचिन्हित लघु pri;
	पूर्णांक irq = data->irq;

	addr = IPRA + ((ipr_table[irq - 16] & 0xf0) >> 3);
	pos = (ipr_table[irq - 16] & 0x0f) * 4;
	pri = ~(0x000f << pos);
	pri &= पढ़ोw(addr);
	pri |= 1 << pos;
	ग_लिखोw(pri, addr);
पूर्ण

काष्ठा irq_chip h8s_irq_chip = अणु
	.name		= "H8S-INTC",
	.irq_enable	= h8s_enable_irq,
	.irq_disable	= h8s_disable_irq,
पूर्ण;

अटल __init पूर्णांक irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			  irq_hw_number_t hw_irq_num)
अणु
       irq_set_chip_and_handler(virq, &h8s_irq_chip, handle_simple_irq);

       वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops irq_ops = अणु
       .map    = irq_map,
       .xlate  = irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल पूर्णांक __init h8s_पूर्णांकc_of_init(काष्ठा device_node *पूर्णांकc,
				   काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	पूर्णांक n;

	पूर्णांकc_baseaddr = of_iomap(पूर्णांकc, 0);
	BUG_ON(!पूर्णांकc_baseaddr);

	/* All पूर्णांकerrupt priority is 0 (disable) */
	/* IPRA to IPRK */
	क्रम (n = 0; n <= 'k' - 'a'; n++)
		ग_लिखोw(0x0000, IPRA + (n * 2));

	करोमुख्य = irq_करोमुख्य_add_linear(पूर्णांकc, NR_IRQS, &irq_ops, शून्य);
	BUG_ON(!करोमुख्य);
	irq_set_शेष_host(करोमुख्य);
	वापस 0;
पूर्ण

IRQCHIP_DECLARE(h8s_पूर्णांकc, "renesas,h8s-intc", h8s_पूर्णांकc_of_init);
