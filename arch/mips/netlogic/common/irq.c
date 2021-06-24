<शैली गुरु>
/*
 * Copyright 2003-2011 NetLogic Microप्रणालीs, Inc. (NetLogic). All rights
 * reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the NetLogic
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY NETLOGIC ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL NETLOGIC OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/linkage.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>

#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/संकेत.स>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/thपढ़ो_info.h>

#समावेश <यंत्र/netlogic/mips-extns.h>
#समावेश <यंत्र/netlogic/पूर्णांकerrupt.h>
#समावेश <यंत्र/netlogic/haldefs.h>
#समावेश <यंत्र/netlogic/common.h>

#अगर defined(CONFIG_CPU_XLP)
#समावेश <यंत्र/netlogic/xlp-hal/iomap.h>
#समावेश <यंत्र/netlogic/xlp-hal/xlp.h>
#समावेश <यंत्र/netlogic/xlp-hal/pic.h>
#या_अगर defined(CONFIG_CPU_XLR)
#समावेश <यंत्र/netlogic/xlr/iomap.h>
#समावेश <यंत्र/netlogic/xlr/pic.h>
#समावेश <यंत्र/netlogic/xlr/fmn.h>
#अन्यथा
#त्रुटि "Unknown CPU"
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
#घोषणा SMP_IRQ_MASK	((1ULL << IRQ_IPI_SMP_FUNCTION) | \
				 (1ULL << IRQ_IPI_SMP_RESCHEDULE))
#अन्यथा
#घोषणा SMP_IRQ_MASK	0
#पूर्ण_अगर
#घोषणा PERCPU_IRQ_MASK (SMP_IRQ_MASK | (1ull << IRQ_TIMER) | \
				(1ull << IRQ_FMN))

काष्ठा nlm_pic_irq अणु
	व्योम	(*extra_ack)(काष्ठा irq_data *);
	काष्ठा	nlm_soc_info *node;
	पूर्णांक	picirq;
	पूर्णांक	irt;
	पूर्णांक	flags;
पूर्ण;

अटल व्योम xlp_pic_enable(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा nlm_pic_irq *pd = irq_data_get_irq_chip_data(d);

	BUG_ON(!pd);
	spin_lock_irqsave(&pd->node->piघड़ी, flags);
	nlm_pic_enable_irt(pd->node->picbase, pd->irt);
	spin_unlock_irqrestore(&pd->node->piघड़ी, flags);
पूर्ण

अटल व्योम xlp_pic_disable(काष्ठा irq_data *d)
अणु
	काष्ठा nlm_pic_irq *pd = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ flags;

	BUG_ON(!pd);
	spin_lock_irqsave(&pd->node->piघड़ी, flags);
	nlm_pic_disable_irt(pd->node->picbase, pd->irt);
	spin_unlock_irqrestore(&pd->node->piघड़ी, flags);
पूर्ण

अटल व्योम xlp_pic_mask_ack(काष्ठा irq_data *d)
अणु
	काष्ठा nlm_pic_irq *pd = irq_data_get_irq_chip_data(d);

	clear_c0_eimr(pd->picirq);
	ack_c0_eirr(pd->picirq);
पूर्ण

अटल व्योम xlp_pic_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा nlm_pic_irq *pd = irq_data_get_irq_chip_data(d);

	BUG_ON(!pd);

	अगर (pd->extra_ack)
		pd->extra_ack(d);

	/* re-enable the पूर्णांकr on this cpu */
	set_c0_eimr(pd->picirq);

	/* Ack is a single ग_लिखो, no need to lock */
	nlm_pic_ack(pd->node->picbase, pd->irt);
पूर्ण

अटल काष्ठा irq_chip xlp_pic = अणु
	.name		= "XLP-PIC",
	.irq_enable	= xlp_pic_enable,
	.irq_disable	= xlp_pic_disable,
	.irq_mask_ack	= xlp_pic_mask_ack,
	.irq_unmask	= xlp_pic_unmask,
पूर्ण;

अटल व्योम cpuपूर्णांकr_disable(काष्ठा irq_data *d)
अणु
	clear_c0_eimr(d->irq);
पूर्ण

अटल व्योम cpuपूर्णांकr_enable(काष्ठा irq_data *d)
अणु
	set_c0_eimr(d->irq);
पूर्ण

अटल व्योम cpuपूर्णांकr_ack(काष्ठा irq_data *d)
अणु
	ack_c0_eirr(d->irq);
पूर्ण

/*
 * Chip definition क्रम CPU originated पूर्णांकerrupts(समयr, msg) and
 * IPIs
 */
काष्ठा irq_chip nlm_cpu_पूर्णांकr = अणु
	.name		= "XLP-CPU-INTR",
	.irq_enable	= cpuपूर्णांकr_enable,
	.irq_disable	= cpuपूर्णांकr_disable,
	.irq_mask	= cpuपूर्णांकr_disable,
	.irq_ack	= cpuपूर्णांकr_ack,
	.irq_eoi	= cpuपूर्णांकr_enable,
पूर्ण;

अटल व्योम __init nlm_init_percpu_irqs(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PIC_IRT_FIRST_IRQ; i++)
		irq_set_chip_and_handler(i, &nlm_cpu_पूर्णांकr, handle_percpu_irq);
#अगर_घोषित CONFIG_SMP
	irq_set_chip_and_handler(IRQ_IPI_SMP_FUNCTION, &nlm_cpu_पूर्णांकr,
			 nlm_smp_function_ipi_handler);
	irq_set_chip_and_handler(IRQ_IPI_SMP_RESCHEDULE, &nlm_cpu_पूर्णांकr,
			 nlm_smp_resched_ipi_handler);
#पूर्ण_अगर
पूर्ण


व्योम nlm_setup_pic_irq(पूर्णांक node, पूर्णांक picirq, पूर्णांक irq, पूर्णांक irt)
अणु
	काष्ठा nlm_pic_irq *pic_data;
	पूर्णांक xirq;

	xirq = nlm_irq_to_xirq(node, irq);
	pic_data = kzalloc(माप(*pic_data), GFP_KERNEL);
	BUG_ON(pic_data == शून्य);
	pic_data->irt = irt;
	pic_data->picirq = picirq;
	pic_data->node = nlm_get_node(node);
	irq_set_chip_and_handler(xirq, &xlp_pic, handle_level_irq);
	irq_set_chip_data(xirq, pic_data);
पूर्ण

व्योम nlm_set_pic_extra_ack(पूर्णांक node, पूर्णांक irq, व्योम (*xack)(काष्ठा irq_data *))
अणु
	काष्ठा nlm_pic_irq *pic_data;
	पूर्णांक xirq;

	xirq = nlm_irq_to_xirq(node, irq);
	pic_data = irq_get_chip_data(xirq);
	अगर (WARN_ON(!pic_data))
		वापस;
	pic_data->extra_ack = xack;
पूर्ण

अटल व्योम nlm_init_node_irqs(पूर्णांक node)
अणु
	काष्ठा nlm_soc_info *nodep;
	पूर्णांक i, irt;

	pr_info("Init IRQ for node %d\n", node);
	nodep = nlm_get_node(node);
	nodep->irqmask = PERCPU_IRQ_MASK;
	क्रम (i = PIC_IRT_FIRST_IRQ; i <= PIC_IRT_LAST_IRQ; i++) अणु
		irt = nlm_irq_to_irt(i);
		अगर (irt == -1)		/* unused irq */
			जारी;
		nodep->irqmask |= 1ull << i;
		अगर (irt == -2)		/* not a direct PIC irq */
			जारी;

		nlm_pic_init_irt(nodep->picbase, irt, i,
				node * nlm_thपढ़ोs_per_node(), 0);
		nlm_setup_pic_irq(node, i, i, irt);
	पूर्ण
पूर्ण

व्योम nlm_smp_irq_init(पूर्णांक hwtid)
अणु
	पूर्णांक cpu, node;

	cpu = hwtid % nlm_thपढ़ोs_per_node();
	node = hwtid / nlm_thपढ़ोs_per_node();

	अगर (cpu == 0 && node != 0)
		nlm_init_node_irqs(node);
	ग_लिखो_c0_eimr(nlm_get_node(node)->irqmask);
पूर्ण

यंत्रlinkage व्योम plat_irq_dispatch(व्योम)
अणु
	uपूर्णांक64_t eirr;
	पूर्णांक i, node;

	node = nlm_nodeid();
	eirr = पढ़ो_c0_eirr_and_eimr();
	अगर (eirr == 0)
		वापस;

	i = __ffs64(eirr);
	/* per-CPU IRQs करोn't need translation */
	अगर (i < PIC_IRQ_BASE) अणु
		करो_IRQ(i);
		वापस;
	पूर्ण

#अगर defined(CONFIG_PCI_MSI) && defined(CONFIG_CPU_XLP)
	/* PCI पूर्णांकerrupts need a second level dispatch क्रम MSI bits */
	अगर (i >= PIC_PCIE_LINK_MSI_IRQ(0) && i <= PIC_PCIE_LINK_MSI_IRQ(3)) अणु
		nlm_dispatch_msi(node, i);
		वापस;
	पूर्ण
	अगर (i >= PIC_PCIE_MSIX_IRQ(0) && i <= PIC_PCIE_MSIX_IRQ(3)) अणु
		nlm_dispatch_msix(node, i);
		वापस;
	पूर्ण

#पूर्ण_अगर
	/* top level irq handling */
	करो_IRQ(nlm_irq_to_xirq(node, i));
पूर्ण

#अगर_घोषित CONFIG_CPU_XLP
अटल पूर्णांक __init xlp_of_pic_init(काष्ठा device_node *node,
					काष्ठा device_node *parent)
अणु
	स्थिर पूर्णांक n_picirqs = PIC_IRT_LAST_IRQ - PIC_IRQ_BASE + 1;
	काष्ठा irq_करोमुख्य *xlp_pic_करोमुख्य;
	काष्ठा resource res;
	पूर्णांक socid, ret, bus;

	/* we need a hack to get the PIC's SoC chip id */
	ret = of_address_to_resource(node, 0, &res);
	अगर (ret < 0) अणु
		pr_err("PIC %pOFn: reg property not found!\n", node);
		वापस -EINVAL;
	पूर्ण

	अगर (cpu_is_xlp9xx()) अणु
		bus = (res.start >> 20) & 0xf;
		क्रम (socid = 0; socid < NLM_NR_NODES; socid++) अणु
			अगर (!nlm_node_present(socid))
				जारी;
			अगर (nlm_get_node(socid)->socbus == bus)
				अवरोध;
		पूर्ण
		अगर (socid == NLM_NR_NODES) अणु
			pr_err("PIC %pOFn: Node mapping for bus %d not found!\n",
					node, bus);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		socid = (res.start >> 18) & 0x3;
		अगर (!nlm_node_present(socid)) अणु
			pr_err("PIC %pOFn: node %d does not exist!\n",
							node, socid);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!nlm_node_present(socid)) अणु
		pr_err("PIC %pOFn: node %d does not exist!\n", node, socid);
		वापस -EINVAL;
	पूर्ण

	xlp_pic_करोमुख्य = irq_करोमुख्य_add_legacy(node, n_picirqs,
		nlm_irq_to_xirq(socid, PIC_IRQ_BASE), PIC_IRQ_BASE,
		&irq_करोमुख्य_simple_ops, शून्य);
	अगर (xlp_pic_करोमुख्य == शून्य) अणु
		pr_err("PIC %pOFn: Creating legacy domain failed!\n", node);
		वापस -EINVAL;
	पूर्ण
	pr_info("Node %d: IRQ domain created for PIC@%pR\n", socid, &res);
	वापस 0;
पूर्ण

अटल काष्ठा of_device_id __initdata xlp_pic_irq_ids[] = अणु
	अणु .compatible = "netlogic,xlp-pic", .data = xlp_of_pic_init पूर्ण,
	अणुपूर्ण,
पूर्ण;
#पूर्ण_अगर

व्योम __init arch_init_irq(व्योम)
अणु
	/* Initialize the irq descriptors */
	nlm_init_percpu_irqs();
	nlm_init_node_irqs(0);
	ग_लिखो_c0_eimr(nlm_current_node()->irqmask);
#अगर defined(CONFIG_CPU_XLR)
	nlm_setup_fmn_irq();
#पूर्ण_अगर
#अगर_घोषित CONFIG_CPU_XLP
	of_irq_init(xlp_pic_irq_ids);
#पूर्ण_अगर
पूर्ण
