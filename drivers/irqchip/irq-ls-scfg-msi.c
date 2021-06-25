<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Freescale SCFG MSI(-X) support
 *
 * Copyright (C) 2016 Freescale Semiconductor.
 *
 * Author: Minghuan Lian <Minghuan.Lian@nxp.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/msi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/dma-iommu.h>

#घोषणा MSI_IRQS_PER_MSIR	32
#घोषणा MSI_MSIR_OFFSET		4

#घोषणा MSI_LS1043V1_1_IRQS_PER_MSIR	8
#घोषणा MSI_LS1043V1_1_MSIR_OFFSET	0x10

काष्ठा ls_scfg_msi_cfg अणु
	u32 ibs_shअगरt; /* Shअगरt of पूर्णांकerrupt bit select */
	u32 msir_irqs; /* The irq number per MSIR */
	u32 msir_base; /* The base address of MSIR */
पूर्ण;

काष्ठा ls_scfg_msir अणु
	काष्ठा ls_scfg_msi *msi_data;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक gic_irq;
	अचिन्हित पूर्णांक bit_start;
	अचिन्हित पूर्णांक bit_end;
	अचिन्हित पूर्णांक srs; /* Shared पूर्णांकerrupt रेजिस्टर select */
	व्योम __iomem *reg;
पूर्ण;

काष्ठा ls_scfg_msi अणु
	spinlock_t		lock;
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा irq_करोमुख्य	*parent;
	काष्ठा irq_करोमुख्य	*msi_करोमुख्य;
	व्योम __iomem		*regs;
	phys_addr_t		msiir_addr;
	काष्ठा ls_scfg_msi_cfg	*cfg;
	u32			msir_num;
	काष्ठा ls_scfg_msir	*msir;
	u32			irqs_num;
	अचिन्हित दीर्घ		*used;
पूर्ण;

अटल काष्ठा irq_chip ls_scfg_msi_irq_chip = अणु
	.name = "MSI",
	.irq_mask	= pci_msi_mask_irq,
	.irq_unmask	= pci_msi_unmask_irq,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info ls_scfg_msi_करोमुख्य_info = अणु
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS |
		   MSI_FLAG_USE_DEF_CHIP_OPS |
		   MSI_FLAG_PCI_MSIX),
	.chip	= &ls_scfg_msi_irq_chip,
पूर्ण;

अटल पूर्णांक msi_affinity_flag = 1;

अटल पूर्णांक __init early_parse_ls_scfg_msi(अक्षर *p)
अणु
	अगर (p && म_भेदन(p, "no-affinity", 11) == 0)
		msi_affinity_flag = 0;
	अन्यथा
		msi_affinity_flag = 1;

	वापस 0;
पूर्ण
early_param("lsmsi", early_parse_ls_scfg_msi);

अटल व्योम ls_scfg_msi_compose_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	काष्ठा ls_scfg_msi *msi_data = irq_data_get_irq_chip_data(data);

	msg->address_hi = upper_32_bits(msi_data->msiir_addr);
	msg->address_lo = lower_32_bits(msi_data->msiir_addr);
	msg->data = data->hwirq;

	अगर (msi_affinity_flag) अणु
		स्थिर काष्ठा cpumask *mask;

		mask = irq_data_get_effective_affinity_mask(data);
		msg->data |= cpumask_first(mask);
	पूर्ण

	iommu_dma_compose_msi_msg(irq_data_get_msi_desc(data), msg);
पूर्ण

अटल पूर्णांक ls_scfg_msi_set_affinity(काष्ठा irq_data *irq_data,
				    स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	काष्ठा ls_scfg_msi *msi_data = irq_data_get_irq_chip_data(irq_data);
	u32 cpu;

	अगर (!msi_affinity_flag)
		वापस -EINVAL;

	अगर (!क्रमce)
		cpu = cpumask_any_and(mask, cpu_online_mask);
	अन्यथा
		cpu = cpumask_first(mask);

	अगर (cpu >= msi_data->msir_num)
		वापस -EINVAL;

	अगर (msi_data->msir[cpu].gic_irq <= 0) अणु
		pr_warn("cannot bind the irq to cpu%d\n", cpu);
		वापस -EINVAL;
	पूर्ण

	irq_data_update_effective_affinity(irq_data, cpumask_of(cpu));

	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल काष्ठा irq_chip ls_scfg_msi_parent_chip = अणु
	.name			= "SCFG",
	.irq_compose_msi_msg	= ls_scfg_msi_compose_msg,
	.irq_set_affinity	= ls_scfg_msi_set_affinity,
पूर्ण;

अटल पूर्णांक ls_scfg_msi_करोमुख्य_irq_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
					अचिन्हित पूर्णांक virq,
					अचिन्हित पूर्णांक nr_irqs,
					व्योम *args)
अणु
	msi_alloc_info_t *info = args;
	काष्ठा ls_scfg_msi *msi_data = करोमुख्य->host_data;
	पूर्णांक pos, err = 0;

	WARN_ON(nr_irqs != 1);

	spin_lock(&msi_data->lock);
	pos = find_first_zero_bit(msi_data->used, msi_data->irqs_num);
	अगर (pos < msi_data->irqs_num)
		__set_bit(pos, msi_data->used);
	अन्यथा
		err = -ENOSPC;
	spin_unlock(&msi_data->lock);

	अगर (err)
		वापस err;

	err = iommu_dma_prepare_msi(info->desc, msi_data->msiir_addr);
	अगर (err)
		वापस err;

	irq_करोमुख्य_set_info(करोमुख्य, virq, pos,
			    &ls_scfg_msi_parent_chip, msi_data,
			    handle_simple_irq, शून्य, शून्य);

	वापस 0;
पूर्ण

अटल व्योम ls_scfg_msi_करोमुख्य_irq_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
				   अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	काष्ठा ls_scfg_msi *msi_data = irq_data_get_irq_chip_data(d);
	पूर्णांक pos;

	pos = d->hwirq;
	अगर (pos < 0 || pos >= msi_data->irqs_num) अणु
		pr_err("failed to teardown msi. Invalid hwirq %d\n", pos);
		वापस;
	पूर्ण

	spin_lock(&msi_data->lock);
	__clear_bit(pos, msi_data->used);
	spin_unlock(&msi_data->lock);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops ls_scfg_msi_करोमुख्य_ops = अणु
	.alloc	= ls_scfg_msi_करोमुख्य_irq_alloc,
	.मुक्त	= ls_scfg_msi_करोमुख्य_irq_मुक्त,
पूर्ण;

अटल व्योम ls_scfg_msi_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा ls_scfg_msir *msir = irq_desc_get_handler_data(desc);
	काष्ठा ls_scfg_msi *msi_data = msir->msi_data;
	अचिन्हित दीर्घ val;
	पूर्णांक pos, size, virq, hwirq;

	chained_irq_enter(irq_desc_get_chip(desc), desc);

	val = ioपढ़ो32be(msir->reg);

	pos = msir->bit_start;
	size = msir->bit_end + 1;

	क्रम_each_set_bit_from(pos, &val, size) अणु
		hwirq = ((msir->bit_end - pos) << msi_data->cfg->ibs_shअगरt) |
			msir->srs;
		virq = irq_find_mapping(msi_data->parent, hwirq);
		अगर (virq)
			generic_handle_irq(virq);
	पूर्ण

	chained_irq_निकास(irq_desc_get_chip(desc), desc);
पूर्ण

अटल पूर्णांक ls_scfg_msi_करोमुख्यs_init(काष्ठा ls_scfg_msi *msi_data)
अणु
	/* Initialize MSI करोमुख्य parent */
	msi_data->parent = irq_करोमुख्य_add_linear(शून्य,
						 msi_data->irqs_num,
						 &ls_scfg_msi_करोमुख्य_ops,
						 msi_data);
	अगर (!msi_data->parent) अणु
		dev_err(&msi_data->pdev->dev, "failed to create IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण

	msi_data->msi_करोमुख्य = pci_msi_create_irq_करोमुख्य(
				of_node_to_fwnode(msi_data->pdev->dev.of_node),
				&ls_scfg_msi_करोमुख्य_info,
				msi_data->parent);
	अगर (!msi_data->msi_करोमुख्य) अणु
		dev_err(&msi_data->pdev->dev, "failed to create MSI domain\n");
		irq_करोमुख्य_हटाओ(msi_data->parent);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ls_scfg_msi_setup_hwirq(काष्ठा ls_scfg_msi *msi_data, पूर्णांक index)
अणु
	काष्ठा ls_scfg_msir *msir;
	पूर्णांक virq, i, hwirq;

	virq = platक्रमm_get_irq(msi_data->pdev, index);
	अगर (virq <= 0)
		वापस -ENODEV;

	msir = &msi_data->msir[index];
	msir->index = index;
	msir->msi_data = msi_data;
	msir->gic_irq = virq;
	msir->reg = msi_data->regs + msi_data->cfg->msir_base + 4 * index;

	अगर (msi_data->cfg->msir_irqs == MSI_LS1043V1_1_IRQS_PER_MSIR) अणु
		msir->bit_start = 32 - ((msir->index + 1) *
				  MSI_LS1043V1_1_IRQS_PER_MSIR);
		msir->bit_end = msir->bit_start +
				MSI_LS1043V1_1_IRQS_PER_MSIR - 1;
	पूर्ण अन्यथा अणु
		msir->bit_start = 0;
		msir->bit_end = msi_data->cfg->msir_irqs - 1;
	पूर्ण

	irq_set_chained_handler_and_data(msir->gic_irq,
					 ls_scfg_msi_irq_handler,
					 msir);

	अगर (msi_affinity_flag) अणु
		/* Associate MSIR पूर्णांकerrupt to the cpu */
		irq_set_affinity(msir->gic_irq, get_cpu_mask(index));
		msir->srs = 0; /* This value is determined by the CPU */
	पूर्ण अन्यथा
		msir->srs = index;

	/* Release the hwirqs corresponding to this MSIR */
	अगर (!msi_affinity_flag || msir->index == 0) अणु
		क्रम (i = 0; i < msi_data->cfg->msir_irqs; i++) अणु
			hwirq = i << msi_data->cfg->ibs_shअगरt | msir->index;
			biपंचांगap_clear(msi_data->used, hwirq, 1);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ls_scfg_msi_tearकरोwn_hwirq(काष्ठा ls_scfg_msir *msir)
अणु
	काष्ठा ls_scfg_msi *msi_data = msir->msi_data;
	पूर्णांक i, hwirq;

	अगर (msir->gic_irq > 0)
		irq_set_chained_handler_and_data(msir->gic_irq, शून्य, शून्य);

	क्रम (i = 0; i < msi_data->cfg->msir_irqs; i++) अणु
		hwirq = i << msi_data->cfg->ibs_shअगरt | msir->index;
		biपंचांगap_set(msi_data->used, hwirq, 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा ls_scfg_msi_cfg ls1021_msi_cfg = अणु
	.ibs_shअगरt = 3,
	.msir_irqs = MSI_IRQS_PER_MSIR,
	.msir_base = MSI_MSIR_OFFSET,
पूर्ण;

अटल काष्ठा ls_scfg_msi_cfg ls1046_msi_cfg = अणु
	.ibs_shअगरt = 2,
	.msir_irqs = MSI_IRQS_PER_MSIR,
	.msir_base = MSI_MSIR_OFFSET,
पूर्ण;

अटल काष्ठा ls_scfg_msi_cfg ls1043_v1_1_msi_cfg = अणु
	.ibs_shअगरt = 2,
	.msir_irqs = MSI_LS1043V1_1_IRQS_PER_MSIR,
	.msir_base = MSI_LS1043V1_1_MSIR_OFFSET,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ls_scfg_msi_id[] = अणु
	/* The following two misspelled compatibles are obsolete */
	अणु .compatible = "fsl,1s1021a-msi", .data = &ls1021_msi_cfgपूर्ण,
	अणु .compatible = "fsl,1s1043a-msi", .data = &ls1021_msi_cfgपूर्ण,

	अणु .compatible = "fsl,ls1012a-msi", .data = &ls1021_msi_cfg पूर्ण,
	अणु .compatible = "fsl,ls1021a-msi", .data = &ls1021_msi_cfg पूर्ण,
	अणु .compatible = "fsl,ls1043a-msi", .data = &ls1021_msi_cfg पूर्ण,
	अणु .compatible = "fsl,ls1043a-v1.1-msi", .data = &ls1043_v1_1_msi_cfg पूर्ण,
	अणु .compatible = "fsl,ls1046a-msi", .data = &ls1046_msi_cfg पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ls_scfg_msi_id);

अटल पूर्णांक ls_scfg_msi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा ls_scfg_msi *msi_data;
	काष्ठा resource *res;
	पूर्णांक i, ret;

	match = of_match_device(ls_scfg_msi_id, &pdev->dev);
	अगर (!match)
		वापस -ENODEV;

	msi_data = devm_kzalloc(&pdev->dev, माप(*msi_data), GFP_KERNEL);
	अगर (!msi_data)
		वापस -ENOMEM;

	msi_data->cfg = (काष्ठा ls_scfg_msi_cfg *) match->data;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	msi_data->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(msi_data->regs)) अणु
		dev_err(&pdev->dev, "failed to initialize 'regs'\n");
		वापस PTR_ERR(msi_data->regs);
	पूर्ण
	msi_data->msiir_addr = res->start;

	msi_data->pdev = pdev;
	spin_lock_init(&msi_data->lock);

	msi_data->irqs_num = MSI_IRQS_PER_MSIR *
			     (1 << msi_data->cfg->ibs_shअगरt);
	msi_data->used = devm_kसुस्मृति(&pdev->dev,
				    BITS_TO_LONGS(msi_data->irqs_num),
				    माप(*msi_data->used),
				    GFP_KERNEL);
	अगर (!msi_data->used)
		वापस -ENOMEM;
	/*
	 * Reserve all the hwirqs
	 * The available hwirqs will be released in ls1_msi_setup_hwirq()
	 */
	biपंचांगap_set(msi_data->used, 0, msi_data->irqs_num);

	msi_data->msir_num = of_irq_count(pdev->dev.of_node);

	अगर (msi_affinity_flag) अणु
		u32 cpu_num;

		cpu_num = num_possible_cpus();
		अगर (msi_data->msir_num >= cpu_num)
			msi_data->msir_num = cpu_num;
		अन्यथा
			msi_affinity_flag = 0;
	पूर्ण

	msi_data->msir = devm_kसुस्मृति(&pdev->dev, msi_data->msir_num,
				      माप(*msi_data->msir),
				      GFP_KERNEL);
	अगर (!msi_data->msir)
		वापस -ENOMEM;

	क्रम (i = 0; i < msi_data->msir_num; i++)
		ls_scfg_msi_setup_hwirq(msi_data, i);

	ret = ls_scfg_msi_करोमुख्यs_init(msi_data);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, msi_data);

	वापस 0;
पूर्ण

अटल पूर्णांक ls_scfg_msi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ls_scfg_msi *msi_data = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < msi_data->msir_num; i++)
		ls_scfg_msi_tearकरोwn_hwirq(&msi_data->msir[i]);

	irq_करोमुख्य_हटाओ(msi_data->msi_करोमुख्य);
	irq_करोमुख्य_हटाओ(msi_data->parent);

	platक्रमm_set_drvdata(pdev, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ls_scfg_msi_driver = अणु
	.driver = अणु
		.name = "ls-scfg-msi",
		.of_match_table = ls_scfg_msi_id,
	पूर्ण,
	.probe = ls_scfg_msi_probe,
	.हटाओ = ls_scfg_msi_हटाओ,
पूर्ण;

module_platक्रमm_driver(ls_scfg_msi_driver);

MODULE_AUTHOR("Minghuan Lian <Minghuan.Lian@nxp.com>");
MODULE_DESCRIPTION("Freescale Layerscape SCFG MSI controller driver");
MODULE_LICENSE("GPL v2");
