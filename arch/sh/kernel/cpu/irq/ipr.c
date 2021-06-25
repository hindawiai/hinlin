<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Interrupt handling क्रम IPR-based IRQ.
 *
 * Copyright (C) 1999  Niibe Yutaka & Takeshi Yaegashi
 * Copyright (C) 2000  Kazumoto Kojima
 * Copyright (C) 2003  Takashi Kusuda <kusuda-takashi@hitachi-ul.co.jp>
 * Copyright (C) 2006  Paul Mundt
 *
 * Supported प्रणाली:
 *	On-chip supporting modules (TMU, RTC, etc.).
 *	On-chip supporting modules क्रम SH7709/SH7709A/SH7729.
 *	Hitachi SolutionEngine बाह्यal I/O:
 *		MS7709SE01, MS7709ASE01, and MS7750SE01
 */
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/topology.h>

अटल अंतरभूत काष्ठा ipr_desc *get_ipr_desc(काष्ठा irq_data *data)
अणु
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(data);
	वापस container_of(chip, काष्ठा ipr_desc, chip);
पूर्ण

अटल व्योम disable_ipr_irq(काष्ठा irq_data *data)
अणु
	काष्ठा ipr_data *p = irq_data_get_irq_chip_data(data);
	अचिन्हित दीर्घ addr = get_ipr_desc(data)->ipr_offsets[p->ipr_idx];
	/* Set the priority in IPR to 0 */
	__raw_ग_लिखोw(__raw_पढ़ोw(addr) & (0xffff ^ (0xf << p->shअगरt)), addr);
	(व्योम)__raw_पढ़ोw(addr);	/* Read back to flush ग_लिखो posting */
पूर्ण

अटल व्योम enable_ipr_irq(काष्ठा irq_data *data)
अणु
	काष्ठा ipr_data *p = irq_data_get_irq_chip_data(data);
	अचिन्हित दीर्घ addr = get_ipr_desc(data)->ipr_offsets[p->ipr_idx];
	/* Set priority in IPR back to original value */
	__raw_ग_लिखोw(__raw_पढ़ोw(addr) | (p->priority << p->shअगरt), addr);
पूर्ण

/*
 * The shअगरt value is now the number of bits to shअगरt, not the number of
 * bits/4. This is to make it easier to पढ़ो the value directly from the
 * datasheets. The IPR address is calculated using the ipr_offset table.
 */
व्योम रेजिस्टर_ipr_controller(काष्ठा ipr_desc *desc)
अणु
	पूर्णांक i;

	desc->chip.irq_mask = disable_ipr_irq;
	desc->chip.irq_unmask = enable_ipr_irq;

	क्रम (i = 0; i < desc->nr_irqs; i++) अणु
		काष्ठा ipr_data *p = desc->ipr_data + i;
		पूर्णांक res;

		BUG_ON(p->ipr_idx >= desc->nr_offsets);
		BUG_ON(!desc->ipr_offsets[p->ipr_idx]);

		res = irq_alloc_desc_at(p->irq, numa_node_id());
		अगर (unlikely(res != p->irq && res != -EEXIST)) अणु
			prपूर्णांकk(KERN_INFO "can not get irq_desc for %d\n",
			       p->irq);
			जारी;
		पूर्ण

		disable_irq_nosync(p->irq);
		irq_set_chip_and_handler_name(p->irq, &desc->chip,
					      handle_level_irq, "level");
		irq_set_chip_data(p->irq, p);
		disable_ipr_irq(irq_get_irq_data(p->irq));
	पूर्ण
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_ipr_controller);
