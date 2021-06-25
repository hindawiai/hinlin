<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2008 Ilya Yanok, Emcraft Systems
 */

#समावेश <linux/irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पन.स>

/*
 * The FPGA supports 9 पूर्णांकerrupt sources, which can be routed to 3
 * पूर्णांकerrupt request lines of the MPIC. The line to be used can be
 * specअगरied through the third cell of FDT property  "interrupts".
 */

#घोषणा SOCRATES_FPGA_NUM_IRQS	9

#घोषणा FPGA_PIC_IRQCFG		(0x0)
#घोषणा FPGA_PIC_IRQMASK(n)	(0x4 + 0x4 * (n))

#घोषणा SOCRATES_FPGA_IRQ_MASK	((1 << SOCRATES_FPGA_NUM_IRQS) - 1)

काष्ठा socrates_fpga_irq_info अणु
	अचिन्हित पूर्णांक irq_line;
	पूर्णांक type;
पूर्ण;

/*
 * Interrupt routing and type table
 *
 * IRQ_TYPE_NONE means the पूर्णांकerrupt type is configurable,
 * otherwise it's fixed to the specअगरied value.
 */
अटल काष्ठा socrates_fpga_irq_info fpga_irqs[SOCRATES_FPGA_NUM_IRQS] = अणु
	[0] = अणु0, IRQ_TYPE_NONEपूर्ण,
	[1] = अणु0, IRQ_TYPE_LEVEL_HIGHपूर्ण,
	[2] = अणु0, IRQ_TYPE_LEVEL_LOWपूर्ण,
	[3] = अणु0, IRQ_TYPE_NONEपूर्ण,
	[4] = अणु0, IRQ_TYPE_NONEपूर्ण,
	[5] = अणु0, IRQ_TYPE_NONEपूर्ण,
	[6] = अणु0, IRQ_TYPE_NONEपूर्ण,
	[7] = अणु0, IRQ_TYPE_NONEपूर्ण,
	[8] = अणु0, IRQ_TYPE_LEVEL_HIGHपूर्ण,
पूर्ण;

अटल DEFINE_RAW_SPINLOCK(socrates_fpga_pic_lock);

अटल व्योम __iomem *socrates_fpga_pic_iobase;
अटल काष्ठा irq_करोमुख्य *socrates_fpga_pic_irq_host;
अटल अचिन्हित पूर्णांक socrates_fpga_irqs[3];

अटल अंतरभूत uपूर्णांक32_t socrates_fpga_pic_पढ़ो(पूर्णांक reg)
अणु
	वापस in_be32(socrates_fpga_pic_iobase + reg);
पूर्ण

अटल अंतरभूत व्योम socrates_fpga_pic_ग_लिखो(पूर्णांक reg, uपूर्णांक32_t val)
अणु
	out_be32(socrates_fpga_pic_iobase + reg, val);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक socrates_fpga_pic_get_irq(अचिन्हित पूर्णांक irq)
अणु
	uपूर्णांक32_t cause;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/* Check irq line routed to the MPIC */
	क्रम (i = 0; i < 3; i++) अणु
		अगर (irq == socrates_fpga_irqs[i])
			अवरोध;
	पूर्ण
	अगर (i == 3)
		वापस 0;

	raw_spin_lock_irqsave(&socrates_fpga_pic_lock, flags);
	cause = socrates_fpga_pic_पढ़ो(FPGA_PIC_IRQMASK(i));
	raw_spin_unlock_irqrestore(&socrates_fpga_pic_lock, flags);
	क्रम (i = SOCRATES_FPGA_NUM_IRQS - 1; i >= 0; i--) अणु
		अगर (cause >> (i + 16))
			अवरोध;
	पूर्ण
	वापस irq_linear_revmap(socrates_fpga_pic_irq_host,
			(irq_hw_number_t)i);
पूर्ण

अटल व्योम socrates_fpga_pic_cascade(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);
	अचिन्हित पूर्णांक cascade_irq;

	/*
	 * See अगर we actually have an पूर्णांकerrupt, call generic handling code अगर
	 * we करो.
	 */
	cascade_irq = socrates_fpga_pic_get_irq(irq);

	अगर (cascade_irq)
		generic_handle_irq(cascade_irq);
	chip->irq_eoi(&desc->irq_data);
पूर्ण

अटल व्योम socrates_fpga_pic_ack(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक irq_line, hwirq = irqd_to_hwirq(d);
	uपूर्णांक32_t mask;

	irq_line = fpga_irqs[hwirq].irq_line;
	raw_spin_lock_irqsave(&socrates_fpga_pic_lock, flags);
	mask = socrates_fpga_pic_पढ़ो(FPGA_PIC_IRQMASK(irq_line))
		& SOCRATES_FPGA_IRQ_MASK;
	mask |= (1 << (hwirq + 16));
	socrates_fpga_pic_ग_लिखो(FPGA_PIC_IRQMASK(irq_line), mask);
	raw_spin_unlock_irqrestore(&socrates_fpga_pic_lock, flags);
पूर्ण

अटल व्योम socrates_fpga_pic_mask(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक hwirq = irqd_to_hwirq(d);
	पूर्णांक irq_line;
	u32 mask;

	irq_line = fpga_irqs[hwirq].irq_line;
	raw_spin_lock_irqsave(&socrates_fpga_pic_lock, flags);
	mask = socrates_fpga_pic_पढ़ो(FPGA_PIC_IRQMASK(irq_line))
		& SOCRATES_FPGA_IRQ_MASK;
	mask &= ~(1 << hwirq);
	socrates_fpga_pic_ग_लिखो(FPGA_PIC_IRQMASK(irq_line), mask);
	raw_spin_unlock_irqrestore(&socrates_fpga_pic_lock, flags);
पूर्ण

अटल व्योम socrates_fpga_pic_mask_ack(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक hwirq = irqd_to_hwirq(d);
	पूर्णांक irq_line;
	u32 mask;

	irq_line = fpga_irqs[hwirq].irq_line;
	raw_spin_lock_irqsave(&socrates_fpga_pic_lock, flags);
	mask = socrates_fpga_pic_पढ़ो(FPGA_PIC_IRQMASK(irq_line))
		& SOCRATES_FPGA_IRQ_MASK;
	mask &= ~(1 << hwirq);
	mask |= (1 << (hwirq + 16));
	socrates_fpga_pic_ग_लिखो(FPGA_PIC_IRQMASK(irq_line), mask);
	raw_spin_unlock_irqrestore(&socrates_fpga_pic_lock, flags);
पूर्ण

अटल व्योम socrates_fpga_pic_unmask(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक hwirq = irqd_to_hwirq(d);
	पूर्णांक irq_line;
	u32 mask;

	irq_line = fpga_irqs[hwirq].irq_line;
	raw_spin_lock_irqsave(&socrates_fpga_pic_lock, flags);
	mask = socrates_fpga_pic_पढ़ो(FPGA_PIC_IRQMASK(irq_line))
		& SOCRATES_FPGA_IRQ_MASK;
	mask |= (1 << hwirq);
	socrates_fpga_pic_ग_लिखो(FPGA_PIC_IRQMASK(irq_line), mask);
	raw_spin_unlock_irqrestore(&socrates_fpga_pic_lock, flags);
पूर्ण

अटल व्योम socrates_fpga_pic_eoi(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक hwirq = irqd_to_hwirq(d);
	पूर्णांक irq_line;
	u32 mask;

	irq_line = fpga_irqs[hwirq].irq_line;
	raw_spin_lock_irqsave(&socrates_fpga_pic_lock, flags);
	mask = socrates_fpga_pic_पढ़ो(FPGA_PIC_IRQMASK(irq_line))
		& SOCRATES_FPGA_IRQ_MASK;
	mask |= (1 << (hwirq + 16));
	socrates_fpga_pic_ग_लिखो(FPGA_PIC_IRQMASK(irq_line), mask);
	raw_spin_unlock_irqrestore(&socrates_fpga_pic_lock, flags);
पूर्ण

अटल पूर्णांक socrates_fpga_pic_set_type(काष्ठा irq_data *d,
		अचिन्हित पूर्णांक flow_type)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक hwirq = irqd_to_hwirq(d);
	पूर्णांक polarity;
	u32 mask;

	अगर (fpga_irqs[hwirq].type != IRQ_TYPE_NONE)
		वापस -EINVAL;

	चयन (flow_type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_LEVEL_HIGH:
		polarity = 1;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		polarity = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	raw_spin_lock_irqsave(&socrates_fpga_pic_lock, flags);
	mask = socrates_fpga_pic_पढ़ो(FPGA_PIC_IRQCFG);
	अगर (polarity)
		mask |= (1 << hwirq);
	अन्यथा
		mask &= ~(1 << hwirq);
	socrates_fpga_pic_ग_लिखो(FPGA_PIC_IRQCFG, mask);
	raw_spin_unlock_irqrestore(&socrates_fpga_pic_lock, flags);
	वापस 0;
पूर्ण

अटल काष्ठा irq_chip socrates_fpga_pic_chip = अणु
	.name		= "FPGA-PIC",
	.irq_ack	= socrates_fpga_pic_ack,
	.irq_mask	= socrates_fpga_pic_mask,
	.irq_mask_ack	= socrates_fpga_pic_mask_ack,
	.irq_unmask	= socrates_fpga_pic_unmask,
	.irq_eoi	= socrates_fpga_pic_eoi,
	.irq_set_type	= socrates_fpga_pic_set_type,
पूर्ण;

अटल पूर्णांक socrates_fpga_pic_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
		irq_hw_number_t hwirq)
अणु
	/* All पूर्णांकerrupts are LEVEL sensitive */
	irq_set_status_flags(virq, IRQ_LEVEL);
	irq_set_chip_and_handler(virq, &socrates_fpga_pic_chip,
				 handle_fasteoi_irq);

	वापस 0;
पूर्ण

अटल पूर्णांक socrates_fpga_pic_host_xlate(काष्ठा irq_करोमुख्य *h,
		काष्ठा device_node *ct,	स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
		irq_hw_number_t *out_hwirq, अचिन्हित पूर्णांक *out_flags)
अणु
	काष्ठा socrates_fpga_irq_info *fpga_irq = &fpga_irqs[पूर्णांकspec[0]];

	*out_hwirq = पूर्णांकspec[0];
	अगर  (fpga_irq->type == IRQ_TYPE_NONE) अणु
		/* type is configurable */
		अगर (पूर्णांकspec[1] != IRQ_TYPE_LEVEL_LOW &&
		    पूर्णांकspec[1] != IRQ_TYPE_LEVEL_HIGH) अणु
			pr_warn("FPGA PIC: invalid irq type, setting default active low\n");
			*out_flags = IRQ_TYPE_LEVEL_LOW;
		पूर्ण अन्यथा अणु
			*out_flags = पूर्णांकspec[1];
		पूर्ण
	पूर्ण अन्यथा अणु
		/* type is fixed */
		*out_flags = fpga_irq->type;
	पूर्ण

	/* Use specअगरied पूर्णांकerrupt routing */
	अगर (पूर्णांकspec[2] <= 2)
		fpga_irq->irq_line = पूर्णांकspec[2];
	अन्यथा
		pr_warn("FPGA PIC: invalid irq routing\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops socrates_fpga_pic_host_ops = अणु
	.map    = socrates_fpga_pic_host_map,
	.xlate  = socrates_fpga_pic_host_xlate,
पूर्ण;

व्योम socrates_fpga_pic_init(काष्ठा device_node *pic)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/* Setup an irq_करोमुख्य काष्ठाure */
	socrates_fpga_pic_irq_host = irq_करोमुख्य_add_linear(pic,
		    SOCRATES_FPGA_NUM_IRQS, &socrates_fpga_pic_host_ops, शून्य);
	अगर (socrates_fpga_pic_irq_host == शून्य) अणु
		pr_err("FPGA PIC: Unable to allocate host\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i < 3; i++) अणु
		socrates_fpga_irqs[i] = irq_of_parse_and_map(pic, i);
		अगर (!socrates_fpga_irqs[i]) अणु
			pr_warn("FPGA PIC: can't get irq%d\n", i);
			जारी;
		पूर्ण
		irq_set_chained_handler(socrates_fpga_irqs[i],
					socrates_fpga_pic_cascade);
	पूर्ण

	socrates_fpga_pic_iobase = of_iomap(pic, 0);

	raw_spin_lock_irqsave(&socrates_fpga_pic_lock, flags);
	socrates_fpga_pic_ग_लिखो(FPGA_PIC_IRQMASK(0),
			SOCRATES_FPGA_IRQ_MASK << 16);
	socrates_fpga_pic_ग_लिखो(FPGA_PIC_IRQMASK(1),
			SOCRATES_FPGA_IRQ_MASK << 16);
	socrates_fpga_pic_ग_लिखो(FPGA_PIC_IRQMASK(2),
			SOCRATES_FPGA_IRQ_MASK << 16);
	raw_spin_unlock_irqrestore(&socrates_fpga_pic_lock, flags);

	pr_info("FPGA PIC: Setting up Socrates FPGA PIC\n");
पूर्ण
