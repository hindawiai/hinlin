<शैली गुरु>
/*
 * Copyright (C) 2016 Marvell
 *
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#घोषणा pr_fmt(fmt) "GIC-ODMI: " fmt

#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <dt-bindings/पूर्णांकerrupt-controller/arm-gic.h>

#घोषणा GICP_ODMIN_SET			0x40
#घोषणा   GICP_ODMI_INT_NUM_SHIFT	12
#घोषणा GICP_ODMIN_GM_EP_R0		0x110
#घोषणा GICP_ODMIN_GM_EP_R1		0x114
#घोषणा GICP_ODMIN_GM_EA_R0		0x108
#घोषणा GICP_ODMIN_GM_EA_R1		0x118

/*
 * We करोn't support the group events, so we simply have 8 पूर्णांकerrupts
 * per frame.
 */
#घोषणा NODMIS_SHIFT		3
#घोषणा NODMIS_PER_FRAME	(1 << NODMIS_SHIFT)
#घोषणा NODMIS_MASK		(NODMIS_PER_FRAME - 1)

काष्ठा odmi_data अणु
	काष्ठा resource res;
	व्योम __iomem *base;
	अचिन्हित पूर्णांक spi_base;
पूर्ण;

अटल काष्ठा odmi_data *odmis;
अटल अचिन्हित दीर्घ *odmis_bm;
अटल अचिन्हित पूर्णांक odmis_count;

/* Protects odmis_bm */
अटल DEFINE_SPINLOCK(odmis_bm_lock);

अटल व्योम odmi_compose_msi_msg(काष्ठा irq_data *d, काष्ठा msi_msg *msg)
अणु
	काष्ठा odmi_data *odmi;
	phys_addr_t addr;
	अचिन्हित पूर्णांक odmin;

	अगर (WARN_ON(d->hwirq >= odmis_count * NODMIS_PER_FRAME))
		वापस;

	odmi = &odmis[d->hwirq >> NODMIS_SHIFT];
	odmin = d->hwirq & NODMIS_MASK;

	addr = odmi->res.start + GICP_ODMIN_SET;

	msg->address_hi = upper_32_bits(addr);
	msg->address_lo = lower_32_bits(addr);
	msg->data = odmin << GICP_ODMI_INT_NUM_SHIFT;
पूर्ण

अटल काष्ठा irq_chip odmi_irq_chip = अणु
	.name			= "ODMI",
	.irq_mask		= irq_chip_mask_parent,
	.irq_unmask		= irq_chip_unmask_parent,
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_set_affinity	= irq_chip_set_affinity_parent,
	.irq_compose_msi_msg	= odmi_compose_msi_msg,
पूर्ण;

अटल पूर्णांक odmi_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				 अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	काष्ठा odmi_data *odmi = शून्य;
	काष्ठा irq_fwspec fwspec;
	काष्ठा irq_data *d;
	अचिन्हित पूर्णांक hwirq, odmin;
	पूर्णांक ret;

	spin_lock(&odmis_bm_lock);
	hwirq = find_first_zero_bit(odmis_bm, NODMIS_PER_FRAME * odmis_count);
	अगर (hwirq >= NODMIS_PER_FRAME * odmis_count) अणु
		spin_unlock(&odmis_bm_lock);
		वापस -ENOSPC;
	पूर्ण

	__set_bit(hwirq, odmis_bm);
	spin_unlock(&odmis_bm_lock);

	odmi = &odmis[hwirq >> NODMIS_SHIFT];
	odmin = hwirq & NODMIS_MASK;

	fwspec.fwnode = करोमुख्य->parent->fwnode;
	fwspec.param_count = 3;
	fwspec.param[0] = GIC_SPI;
	fwspec.param[1] = odmi->spi_base - 32 + odmin;
	fwspec.param[2] = IRQ_TYPE_EDGE_RISING;

	ret = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, 1, &fwspec);
	अगर (ret) अणु
		pr_err("Cannot allocate parent IRQ\n");
		spin_lock(&odmis_bm_lock);
		__clear_bit(odmin, odmis_bm);
		spin_unlock(&odmis_bm_lock);
		वापस ret;
	पूर्ण

	/* Configure the पूर्णांकerrupt line to be edge */
	d = irq_करोमुख्य_get_irq_data(करोमुख्य->parent, virq);
	d->chip->irq_set_type(d, IRQ_TYPE_EDGE_RISING);

	irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq, hwirq,
				      &odmi_irq_chip, शून्य);

	वापस 0;
पूर्ण

अटल व्योम odmi_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
				 अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);

	अगर (d->hwirq >= odmis_count * NODMIS_PER_FRAME) अणु
		pr_err("Failed to teardown msi. Invalid hwirq %lu\n", d->hwirq);
		वापस;
	पूर्ण

	irq_करोमुख्य_मुक्त_irqs_parent(करोमुख्य, virq, nr_irqs);

	/* Actually मुक्त the MSI */
	spin_lock(&odmis_bm_lock);
	__clear_bit(d->hwirq, odmis_bm);
	spin_unlock(&odmis_bm_lock);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops odmi_करोमुख्य_ops = अणु
	.alloc	= odmi_irq_करोमुख्य_alloc,
	.मुक्त	= odmi_irq_करोमुख्य_मुक्त,
पूर्ण;

अटल काष्ठा irq_chip odmi_msi_irq_chip = अणु
	.name	= "ODMI",
पूर्ण;

अटल काष्ठा msi_करोमुख्य_ops odmi_msi_ops = अणु
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info odmi_msi_करोमुख्य_info = अणु
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS),
	.ops	= &odmi_msi_ops,
	.chip	= &odmi_msi_irq_chip,
पूर्ण;

अटल पूर्णांक __init mvebu_odmi_init(काष्ठा device_node *node,
				  काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *inner_करोमुख्य, *plat_करोमुख्य;
	पूर्णांक ret, i;

	अगर (of_property_पढ़ो_u32(node, "marvell,odmi-frames", &odmis_count))
		वापस -EINVAL;

	odmis = kसुस्मृति(odmis_count, माप(काष्ठा odmi_data), GFP_KERNEL);
	अगर (!odmis)
		वापस -ENOMEM;

	odmis_bm = kसुस्मृति(BITS_TO_LONGS(odmis_count * NODMIS_PER_FRAME),
			   माप(दीर्घ), GFP_KERNEL);
	अगर (!odmis_bm) अणु
		ret = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	क्रम (i = 0; i < odmis_count; i++) अणु
		काष्ठा odmi_data *odmi = &odmis[i];

		ret = of_address_to_resource(node, i, &odmi->res);
		अगर (ret)
			जाओ err_unmap;

		odmi->base = of_io_request_and_map(node, i, "odmi");
		अगर (IS_ERR(odmi->base)) अणु
			ret = PTR_ERR(odmi->base);
			जाओ err_unmap;
		पूर्ण

		अगर (of_property_पढ़ो_u32_index(node, "marvell,spi-base",
					       i, &odmi->spi_base)) अणु
			ret = -EINVAL;
			जाओ err_unmap;
		पूर्ण
	पूर्ण

	inner_करोमुख्य = irq_करोमुख्य_create_linear(of_node_to_fwnode(node),
						odmis_count * NODMIS_PER_FRAME,
						&odmi_करोमुख्य_ops, शून्य);
	अगर (!inner_करोमुख्य) अणु
		ret = -ENOMEM;
		जाओ err_unmap;
	पूर्ण

	inner_करोमुख्य->parent = irq_find_host(parent);

	plat_करोमुख्य = platक्रमm_msi_create_irq_करोमुख्य(of_node_to_fwnode(node),
						     &odmi_msi_करोमुख्य_info,
						     inner_करोमुख्य);
	अगर (!plat_करोमुख्य) अणु
		ret = -ENOMEM;
		जाओ err_हटाओ_inner;
	पूर्ण

	वापस 0;

err_हटाओ_inner:
	irq_करोमुख्य_हटाओ(inner_करोमुख्य);
err_unmap:
	क्रम (i = 0; i < odmis_count; i++) अणु
		काष्ठा odmi_data *odmi = &odmis[i];

		अगर (odmi->base && !IS_ERR(odmi->base))
			iounmap(odmis[i].base);
	पूर्ण
	kमुक्त(odmis_bm);
err_alloc:
	kमुक्त(odmis);
	वापस ret;
पूर्ण

IRQCHIP_DECLARE(mvebu_odmi, "marvell,odmi-controller", mvebu_odmi_init);
