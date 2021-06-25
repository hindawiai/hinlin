<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/se/7724/irq.c
 *
 * Copyright (C) 2009 Renesas Solutions Corp.
 *
 * Kuninori Morimoto <morimoto.kuninori@renesas.com>
 *
 * Based on  linux/arch/sh/boards/se/7722/irq.c
 * Copyright (C) 2007  Nobuhiro Iwamatsu
 *
 * Hitachi UL SolutionEngine 7724 Support.
 */
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/export.h>
#समावेश <linux/topology.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <mach-se/mach/se7724.h>

काष्ठा fpga_irq अणु
	अचिन्हित दीर्घ  sraddr;
	अचिन्हित दीर्घ  mraddr;
	अचिन्हित लघु mask;
	अचिन्हित पूर्णांक   base;
पूर्ण;

अटल अचिन्हित पूर्णांक fpga2irq(अचिन्हित पूर्णांक irq)
अणु
	अगर (irq >= IRQ0_BASE &&
	    irq <= IRQ0_END)
		वापस IRQ0_IRQ;
	अन्यथा अगर (irq >= IRQ1_BASE &&
		 irq <= IRQ1_END)
		वापस IRQ1_IRQ;
	अन्यथा
		वापस IRQ2_IRQ;
पूर्ण

अटल काष्ठा fpga_irq get_fpga_irq(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा fpga_irq set;

	चयन (irq) अणु
	हाल IRQ0_IRQ:
		set.sraddr = IRQ0_SR;
		set.mraddr = IRQ0_MR;
		set.mask   = IRQ0_MASK;
		set.base   = IRQ0_BASE;
		अवरोध;
	हाल IRQ1_IRQ:
		set.sraddr = IRQ1_SR;
		set.mraddr = IRQ1_MR;
		set.mask   = IRQ1_MASK;
		set.base   = IRQ1_BASE;
		अवरोध;
	शेष:
		set.sraddr = IRQ2_SR;
		set.mraddr = IRQ2_MR;
		set.mask   = IRQ2_MASK;
		set.base   = IRQ2_BASE;
		अवरोध;
	पूर्ण

	वापस set;
पूर्ण

अटल व्योम disable_se7724_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;
	काष्ठा fpga_irq set = get_fpga_irq(fpga2irq(irq));
	अचिन्हित पूर्णांक bit = irq - set.base;
	__raw_ग_लिखोw(__raw_पढ़ोw(set.mraddr) | 0x0001 << bit, set.mraddr);
पूर्ण

अटल व्योम enable_se7724_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;
	काष्ठा fpga_irq set = get_fpga_irq(fpga2irq(irq));
	अचिन्हित पूर्णांक bit = irq - set.base;
	__raw_ग_लिखोw(__raw_पढ़ोw(set.mraddr) & ~(0x0001 << bit), set.mraddr);
पूर्ण

अटल काष्ठा irq_chip se7724_irq_chip __पढ़ो_mostly = अणु
	.name		= "SE7724-FPGA",
	.irq_mask	= disable_se7724_irq,
	.irq_unmask	= enable_se7724_irq,
पूर्ण;

अटल व्योम se7724_irq_demux(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);
	काष्ठा fpga_irq set = get_fpga_irq(irq);
	अचिन्हित लघु पूर्णांकv = __raw_पढ़ोw(set.sraddr);
	अचिन्हित पूर्णांक ext_irq = set.base;

	पूर्णांकv &= set.mask;

	क्रम (; पूर्णांकv; पूर्णांकv >>= 1, ext_irq++) अणु
		अगर (!(पूर्णांकv & 1))
			जारी;

		generic_handle_irq(ext_irq);
	पूर्ण
पूर्ण

/*
 * Initialize IRQ setting
 */
व्योम __init init_se7724_IRQ(व्योम)
अणु
	पूर्णांक irq_base, i;

	__raw_ग_लिखोw(0xffff, IRQ0_MR);  /* mask all */
	__raw_ग_लिखोw(0xffff, IRQ1_MR);  /* mask all */
	__raw_ग_लिखोw(0xffff, IRQ2_MR);  /* mask all */
	__raw_ग_लिखोw(0x0000, IRQ0_SR);  /* clear irq */
	__raw_ग_लिखोw(0x0000, IRQ1_SR);  /* clear irq */
	__raw_ग_लिखोw(0x0000, IRQ2_SR);  /* clear irq */
	__raw_ग_लिखोw(0x002a, IRQ_MODE); /* set irq type */

	irq_base = irq_alloc_descs(SE7724_FPGA_IRQ_BASE, SE7724_FPGA_IRQ_BASE,
				   SE7724_FPGA_IRQ_NR, numa_node_id());
	अगर (IS_ERR_VALUE(irq_base)) अणु
		pr_err("%s: failed hooking irqs for FPGA\n", __func__);
		वापस;
	पूर्ण

	क्रम (i = 0; i < SE7724_FPGA_IRQ_NR; i++)
		irq_set_chip_and_handler_name(irq_base + i, &se7724_irq_chip,
					      handle_level_irq, "level");

	irq_set_chained_handler(IRQ0_IRQ, se7724_irq_demux);
	irq_set_irq_type(IRQ0_IRQ, IRQ_TYPE_LEVEL_LOW);

	irq_set_chained_handler(IRQ1_IRQ, se7724_irq_demux);
	irq_set_irq_type(IRQ1_IRQ, IRQ_TYPE_LEVEL_LOW);

	irq_set_chained_handler(IRQ2_IRQ, se7724_irq_demux);
	irq_set_irq_type(IRQ2_IRQ, IRQ_TYPE_LEVEL_LOW);
पूर्ण
