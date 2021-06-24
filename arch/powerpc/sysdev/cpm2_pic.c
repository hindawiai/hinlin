<शैली गुरु>
/*
 * Platक्रमm inक्रमmation definitions.
 *
 * Copied from arch/ppc/syslib/cpm2_pic.c with minor subsequent updates
 * to make in work in arch/घातerpc/. Original (c) beदीर्घs to Dan Malek.
 *
 * Author:  Vitaly Bordug <vbordug@ru.mvista.com>
 *
 * 1999-2001 (c) Dan Malek <dan@embeddedalley.com>
 * 2006 (c) MontaVista Software, Inc.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

/* The CPM2 पूर्णांकernal पूर्णांकerrupt controller.  It is usually
 * the only पूर्णांकerrupt controller.
 * There are two 32-bit रेजिस्टरs (high/low) क्रम up to 64
 * possible पूर्णांकerrupts.
 *
 * Now, the fun starts.....Interrupt Numbers DO NOT MAP
 * in a simple arithmetic fashion to mask or pending रेजिस्टरs.
 * That is, पूर्णांकerrupt 4 करोes not map to bit position 4.
 * We create two tables, indexed by vector number, to indicate
 * which रेजिस्टर to use and which bit in the रेजिस्टर to use.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/sched.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/irq.h>

#समावेश <यंत्र/immap_cpm2.h>
#समावेश <यंत्र/mpc8260.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/fs_pd.h>

#समावेश "cpm2_pic.h"

/* External IRQS */
#घोषणा CPM2_IRQ_EXT1		19
#घोषणा CPM2_IRQ_EXT7		25

/* Port C IRQS */
#घोषणा CPM2_IRQ_PORTC15	48
#घोषणा CPM2_IRQ_PORTC0		63

अटल पूर्णांकctl_cpm2_t __iomem *cpm2_पूर्णांकctl;

अटल काष्ठा irq_करोमुख्य *cpm2_pic_host;
अटल अचिन्हित दीर्घ ppc_cached_irq_mask[2]; /* 2 32-bit रेजिस्टरs */

अटल स्थिर u_अक्षर irq_to_siureg[] = अणु
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
पूर्ण;

/* bit numbers करो not match the करोcs, these are precomputed so the bit क्रम
 * a given irq is (1 << irq_to_siubit[irq]) */
अटल स्थिर u_अक्षर irq_to_siubit[] = अणु
	 0, 15, 14, 13, 12, 11, 10,  9,
	 8,  7,  6,  5,  4,  3,  2,  1,
	 2,  1,  0, 14, 13, 12, 11, 10,
	 9,  8,  7,  6,  5,  4,  3,  0,
	31, 30, 29, 28, 27, 26, 25, 24,
	23, 22, 21, 20, 19, 18, 17, 16,
	16, 17, 18, 19, 20, 21, 22, 23,
	24, 25, 26, 27, 28, 29, 30, 31,
पूर्ण;

अटल व्योम cpm2_mask_irq(काष्ठा irq_data *d)
अणु
	पूर्णांक	bit, word;
	अचिन्हित पूर्णांक irq_nr = irqd_to_hwirq(d);

	bit = irq_to_siubit[irq_nr];
	word = irq_to_siureg[irq_nr];

	ppc_cached_irq_mask[word] &= ~(1 << bit);
	out_be32(&cpm2_पूर्णांकctl->ic_simrh + word, ppc_cached_irq_mask[word]);
पूर्ण

अटल व्योम cpm2_unmask_irq(काष्ठा irq_data *d)
अणु
	पूर्णांक	bit, word;
	अचिन्हित पूर्णांक irq_nr = irqd_to_hwirq(d);

	bit = irq_to_siubit[irq_nr];
	word = irq_to_siureg[irq_nr];

	ppc_cached_irq_mask[word] |= 1 << bit;
	out_be32(&cpm2_पूर्णांकctl->ic_simrh + word, ppc_cached_irq_mask[word]);
पूर्ण

अटल व्योम cpm2_ack(काष्ठा irq_data *d)
अणु
	पूर्णांक	bit, word;
	अचिन्हित पूर्णांक irq_nr = irqd_to_hwirq(d);

	bit = irq_to_siubit[irq_nr];
	word = irq_to_siureg[irq_nr];

	out_be32(&cpm2_पूर्णांकctl->ic_sipnrh + word, 1 << bit);
पूर्ण

अटल व्योम cpm2_end_irq(काष्ठा irq_data *d)
अणु
	पूर्णांक	bit, word;
	अचिन्हित पूर्णांक irq_nr = irqd_to_hwirq(d);

	bit = irq_to_siubit[irq_nr];
	word = irq_to_siureg[irq_nr];

	ppc_cached_irq_mask[word] |= 1 << bit;
	out_be32(&cpm2_पूर्णांकctl->ic_simrh + word, ppc_cached_irq_mask[word]);

	/*
	 * Work around large numbers of spurious IRQs on PowerPC 82xx
	 * प्रणालीs.
	 */
	mb();
पूर्ण

अटल पूर्णांक cpm2_set_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);
	अचिन्हित पूर्णांक vold, vnew, edibit;

	/* Port C पूर्णांकerrupts are either IRQ_TYPE_EDGE_FALLING or
	 * IRQ_TYPE_EDGE_BOTH (शेष).  All others are IRQ_TYPE_EDGE_FALLING
	 * or IRQ_TYPE_LEVEL_LOW (शेष)
	 */
	अगर (src >= CPM2_IRQ_PORTC15 && src <= CPM2_IRQ_PORTC0) अणु
		अगर (flow_type == IRQ_TYPE_NONE)
			flow_type = IRQ_TYPE_EDGE_BOTH;

		अगर (flow_type != IRQ_TYPE_EDGE_BOTH &&
		    flow_type != IRQ_TYPE_EDGE_FALLING)
			जाओ err_sense;
	पूर्ण अन्यथा अणु
		अगर (flow_type == IRQ_TYPE_NONE)
			flow_type = IRQ_TYPE_LEVEL_LOW;

		अगर (flow_type & (IRQ_TYPE_EDGE_RISING | IRQ_TYPE_LEVEL_HIGH))
			जाओ err_sense;
	पूर्ण

	irqd_set_trigger_type(d, flow_type);
	अगर (flow_type & IRQ_TYPE_LEVEL_LOW)
		irq_set_handler_locked(d, handle_level_irq);
	अन्यथा
		irq_set_handler_locked(d, handle_edge_irq);

	/* पूर्णांकernal IRQ senses are LEVEL_LOW
	 * EXT IRQ and Port C IRQ senses are programmable
	 */
	अगर (src >= CPM2_IRQ_EXT1 && src <= CPM2_IRQ_EXT7)
			edibit = (14 - (src - CPM2_IRQ_EXT1));
	अन्यथा
		अगर (src >= CPM2_IRQ_PORTC15 && src <= CPM2_IRQ_PORTC0)
			edibit = (31 - (CPM2_IRQ_PORTC0 - src));
		अन्यथा
			वापस (flow_type & IRQ_TYPE_LEVEL_LOW) ?
				IRQ_SET_MASK_OK_NOCOPY : -EINVAL;

	vold = in_be32(&cpm2_पूर्णांकctl->ic_siexr);

	अगर ((flow_type & IRQ_TYPE_SENSE_MASK) == IRQ_TYPE_EDGE_FALLING)
		vnew = vold | (1 << edibit);
	अन्यथा
		vnew = vold & ~(1 << edibit);

	अगर (vold != vnew)
		out_be32(&cpm2_पूर्णांकctl->ic_siexr, vnew);
	वापस IRQ_SET_MASK_OK_NOCOPY;

err_sense:
	pr_err("CPM2 PIC: sense type 0x%x not supported\n", flow_type);
	वापस -EINVAL;
पूर्ण

अटल काष्ठा irq_chip cpm2_pic = अणु
	.name = "CPM2 SIU",
	.irq_mask = cpm2_mask_irq,
	.irq_unmask = cpm2_unmask_irq,
	.irq_ack = cpm2_ack,
	.irq_eoi = cpm2_end_irq,
	.irq_set_type = cpm2_set_irq_type,
	.flags = IRQCHIP_EOI_IF_HANDLED,
पूर्ण;

अचिन्हित पूर्णांक cpm2_get_irq(व्योम)
अणु
	पूर्णांक irq;
	अचिन्हित दीर्घ bits;

       /* For CPM2, पढ़ो the SIVEC रेजिस्टर and shअगरt the bits करोwn
         * to get the irq number.         */
        bits = in_be32(&cpm2_पूर्णांकctl->ic_sivec);
        irq = bits >> 26;

	अगर (irq == 0)
		वापस(-1);
	वापस irq_linear_revmap(cpm2_pic_host, irq);
पूर्ण

अटल पूर्णांक cpm2_pic_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			  irq_hw_number_t hw)
अणु
	pr_debug("cpm2_pic_host_map(%d, 0x%lx)\n", virq, hw);

	irq_set_status_flags(virq, IRQ_LEVEL);
	irq_set_chip_and_handler(virq, &cpm2_pic, handle_level_irq);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops cpm2_pic_host_ops = अणु
	.map = cpm2_pic_host_map,
	.xlate = irq_करोमुख्य_xlate_onetwocell,
पूर्ण;

व्योम cpm2_pic_init(काष्ठा device_node *node)
अणु
	पूर्णांक i;

	cpm2_पूर्णांकctl = cpm2_map(im_पूर्णांकctl);

	/* Clear the CPM IRQ controller, in हाल it has any bits set
	 * from the bootloader
	 */

	/* Mask out everything */

	out_be32(&cpm2_पूर्णांकctl->ic_simrh, 0x00000000);
	out_be32(&cpm2_पूर्णांकctl->ic_simrl, 0x00000000);

	wmb();

	/* Ack everything */
	out_be32(&cpm2_पूर्णांकctl->ic_sipnrh, 0xffffffff);
	out_be32(&cpm2_पूर्णांकctl->ic_sipnrl, 0xffffffff);
	wmb();

	/* Dummy पढ़ो of the vector */
	i = in_be32(&cpm2_पूर्णांकctl->ic_sivec);
	rmb();

	/* Initialize the शेष पूर्णांकerrupt mapping priorities,
	 * in हाल the boot rom changed something on us.
	 */
	out_be16(&cpm2_पूर्णांकctl->ic_sicr, 0);
	out_be32(&cpm2_पूर्णांकctl->ic_scprrh, 0x05309770);
	out_be32(&cpm2_पूर्णांकctl->ic_scprrl, 0x05309770);

	/* create a legacy host */
	cpm2_pic_host = irq_करोमुख्य_add_linear(node, 64, &cpm2_pic_host_ops, शून्य);
	अगर (cpm2_pic_host == शून्य) अणु
		prपूर्णांकk(KERN_ERR "CPM2 PIC: failed to allocate irq host!\n");
		वापस;
	पूर्ण
पूर्ण
