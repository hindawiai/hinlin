<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Adding PCI-E MSI support क्रम PPC4XX SoCs.
 *
 * Copyright (c) 2010, Applied Micro Circuits Corporation
 * Authors:	Tirumala R Marri <पंचांगarri@apm.com>
 *		Feng Kan <fkan@apm.com>
 */

#समावेश <linux/irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/dcr.h>
#समावेश <यंत्र/dcr-regs.h>
#समावेश <यंत्र/msi_biपंचांगap.h>

#घोषणा PEIH_TERMADH	0x00
#घोषणा PEIH_TERMADL	0x08
#घोषणा PEIH_MSIED	0x10
#घोषणा PEIH_MSIMK	0x18
#घोषणा PEIH_MSIASS	0x20
#घोषणा PEIH_FLUSH0	0x30
#घोषणा PEIH_FLUSH1	0x38
#घोषणा PEIH_CNTRST	0x48

अटल पूर्णांक msi_irqs;

काष्ठा ppc4xx_msi अणु
	u32 msi_addr_lo;
	u32 msi_addr_hi;
	व्योम __iomem *msi_regs;
	पूर्णांक *msi_virqs;
	काष्ठा msi_biपंचांगap biपंचांगap;
	काष्ठा device_node *msi_dev;
पूर्ण;

अटल काष्ठा ppc4xx_msi ppc4xx_msi;

अटल पूर्णांक ppc4xx_msi_init_allocator(काष्ठा platक्रमm_device *dev,
		काष्ठा ppc4xx_msi *msi_data)
अणु
	पूर्णांक err;

	err = msi_biपंचांगap_alloc(&msi_data->biपंचांगap, msi_irqs,
			      dev->dev.of_node);
	अगर (err)
		वापस err;

	err = msi_biपंचांगap_reserve_dt_hwirqs(&msi_data->biपंचांगap);
	अगर (err < 0) अणु
		msi_biपंचांगap_मुक्त(&msi_data->biपंचांगap);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ppc4xx_setup_msi_irqs(काष्ठा pci_dev *dev, पूर्णांक nvec, पूर्णांक type)
अणु
	पूर्णांक पूर्णांक_no = -ENOMEM;
	अचिन्हित पूर्णांक virq;
	काष्ठा msi_msg msg;
	काष्ठा msi_desc *entry;
	काष्ठा ppc4xx_msi *msi_data = &ppc4xx_msi;

	dev_dbg(&dev->dev, "PCIE-MSI:%s called. vec %x type %d\n",
		__func__, nvec, type);
	अगर (type == PCI_CAP_ID_MSIX)
		pr_debug("ppc4xx msi: MSI-X untested, trying anyway.\n");

	msi_data->msi_virqs = kदो_स्मृति_array(msi_irqs, माप(पूर्णांक), GFP_KERNEL);
	अगर (!msi_data->msi_virqs)
		वापस -ENOMEM;

	क्रम_each_pci_msi_entry(entry, dev) अणु
		पूर्णांक_no = msi_biपंचांगap_alloc_hwirqs(&msi_data->biपंचांगap, 1);
		अगर (पूर्णांक_no >= 0)
			अवरोध;
		अगर (पूर्णांक_no < 0) अणु
			pr_debug("%s: fail allocating msi interrupt\n",
					__func__);
		पूर्ण
		virq = irq_of_parse_and_map(msi_data->msi_dev, पूर्णांक_no);
		अगर (!virq) अणु
			dev_err(&dev->dev, "%s: fail mapping irq\n", __func__);
			msi_biपंचांगap_मुक्त_hwirqs(&msi_data->biपंचांगap, पूर्णांक_no, 1);
			वापस -ENOSPC;
		पूर्ण
		dev_dbg(&dev->dev, "%s: virq = %d\n", __func__, virq);

		/* Setup msi address space */
		msg.address_hi = msi_data->msi_addr_hi;
		msg.address_lo = msi_data->msi_addr_lo;

		irq_set_msi_desc(virq, entry);
		msg.data = पूर्णांक_no;
		pci_ग_लिखो_msi_msg(virq, &msg);
	पूर्ण
	वापस 0;
पूर्ण

व्योम ppc4xx_tearकरोwn_msi_irqs(काष्ठा pci_dev *dev)
अणु
	काष्ठा msi_desc *entry;
	काष्ठा ppc4xx_msi *msi_data = &ppc4xx_msi;
	irq_hw_number_t hwirq;

	dev_dbg(&dev->dev, "PCIE-MSI: tearing down msi irqs\n");

	क्रम_each_pci_msi_entry(entry, dev) अणु
		अगर (!entry->irq)
			जारी;
		hwirq = virq_to_hw(entry->irq);
		irq_set_msi_desc(entry->irq, शून्य);
		irq_dispose_mapping(entry->irq);
		msi_biपंचांगap_मुक्त_hwirqs(&msi_data->biपंचांगap, hwirq, 1);
	पूर्ण
पूर्ण

अटल पूर्णांक ppc4xx_setup_pcieh_hw(काष्ठा platक्रमm_device *dev,
				 काष्ठा resource res, काष्ठा ppc4xx_msi *msi)
अणु
	स्थिर u32 *msi_data;
	स्थिर u32 *msi_mask;
	स्थिर u32 *sdr_addr;
	dma_addr_t msi_phys;
	व्योम *msi_virt;
	पूर्णांक err;

	sdr_addr = of_get_property(dev->dev.of_node, "sdr-base", शून्य);
	अगर (!sdr_addr)
		वापस -EINVAL;

	msi_data = of_get_property(dev->dev.of_node, "msi-data", शून्य);
	अगर (!msi_data)
		वापस -EINVAL;

	msi_mask = of_get_property(dev->dev.of_node, "msi-mask", शून्य);
	अगर (!msi_mask)
		वापस -EINVAL;

	msi->msi_dev = of_find_node_by_name(शून्य, "ppc4xx-msi");
	अगर (!msi->msi_dev)
		वापस -ENODEV;

	msi->msi_regs = of_iomap(msi->msi_dev, 0);
	अगर (!msi->msi_regs) अणु
		dev_err(&dev->dev, "of_iomap failed\n");
		err = -ENOMEM;
		जाओ node_put;
	पूर्ण
	dev_dbg(&dev->dev, "PCIE-MSI: msi register mapped 0x%x 0x%x\n",
		(u32) (msi->msi_regs + PEIH_TERMADH), (u32) (msi->msi_regs));

	msi_virt = dma_alloc_coherent(&dev->dev, 64, &msi_phys, GFP_KERNEL);
	अगर (!msi_virt) अणु
		err = -ENOMEM;
		जाओ iounmap;
	पूर्ण
	msi->msi_addr_hi = upper_32_bits(msi_phys);
	msi->msi_addr_lo = lower_32_bits(msi_phys & 0xffffffff);
	dev_dbg(&dev->dev, "PCIE-MSI: msi address high 0x%x, low 0x%x\n",
		msi->msi_addr_hi, msi->msi_addr_lo);

	mtdcri(SDR0, *sdr_addr, upper_32_bits(res.start));	/*HIGH addr */
	mtdcri(SDR0, *sdr_addr + 1, lower_32_bits(res.start));	/* Low addr */

	/* Progam the Interrupt handler Termination addr रेजिस्टरs */
	out_be32(msi->msi_regs + PEIH_TERMADH, msi->msi_addr_hi);
	out_be32(msi->msi_regs + PEIH_TERMADL, msi->msi_addr_lo);

	/* Program MSI Expected data and Mask bits */
	out_be32(msi->msi_regs + PEIH_MSIED, *msi_data);
	out_be32(msi->msi_regs + PEIH_MSIMK, *msi_mask);

	dma_मुक्त_coherent(&dev->dev, 64, msi_virt, msi_phys);

	वापस 0;

iounmap:
	iounmap(msi->msi_regs);
node_put:
	of_node_put(msi->msi_dev);
	वापस err;
पूर्ण

अटल पूर्णांक ppc4xx_of_msi_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा ppc4xx_msi *msi = dev->dev.platक्रमm_data;
	पूर्णांक i;
	पूर्णांक virq;

	क्रम (i = 0; i < msi_irqs; i++) अणु
		virq = msi->msi_virqs[i];
		अगर (virq)
			irq_dispose_mapping(virq);
	पूर्ण

	अगर (msi->biपंचांगap.biपंचांगap)
		msi_biपंचांगap_मुक्त(&msi->biपंचांगap);
	iounmap(msi->msi_regs);
	of_node_put(msi->msi_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ppc4xx_msi_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा ppc4xx_msi *msi;
	काष्ठा resource res;
	पूर्णांक err = 0;
	काष्ठा pci_controller *phb;

	dev_dbg(&dev->dev, "PCIE-MSI: Setting up MSI support...\n");

	msi = devm_kzalloc(&dev->dev, माप(*msi), GFP_KERNEL);
	अगर (!msi)
		वापस -ENOMEM;
	dev->dev.platक्रमm_data = msi;

	/* Get MSI ranges */
	err = of_address_to_resource(dev->dev.of_node, 0, &res);
	अगर (err) अणु
		dev_err(&dev->dev, "%pOF resource error!\n", dev->dev.of_node);
		वापस err;
	पूर्ण

	msi_irqs = of_irq_count(dev->dev.of_node);
	अगर (!msi_irqs)
		वापस -ENODEV;

	err = ppc4xx_setup_pcieh_hw(dev, res, msi);
	अगर (err)
		वापस err;

	err = ppc4xx_msi_init_allocator(dev, msi);
	अगर (err) अणु
		dev_err(&dev->dev, "Error allocating MSI bitmap\n");
		जाओ error_out;
	पूर्ण
	ppc4xx_msi = *msi;

	list_क्रम_each_entry(phb, &hose_list, list_node) अणु
		phb->controller_ops.setup_msi_irqs = ppc4xx_setup_msi_irqs;
		phb->controller_ops.tearकरोwn_msi_irqs = ppc4xx_tearकरोwn_msi_irqs;
	पूर्ण
	वापस 0;

error_out:
	ppc4xx_of_msi_हटाओ(dev);
	वापस err;
पूर्ण
अटल स्थिर काष्ठा of_device_id ppc4xx_msi_ids[] = अणु
	अणु
		.compatible = "amcc,ppc4xx-msi",
	पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल काष्ठा platक्रमm_driver ppc4xx_msi_driver = अणु
	.probe = ppc4xx_msi_probe,
	.हटाओ = ppc4xx_of_msi_हटाओ,
	.driver = अणु
		   .name = "ppc4xx-msi",
		   .of_match_table = ppc4xx_msi_ids,
		   पूर्ण,

पूर्ण;

अटल __init पूर्णांक ppc4xx_msi_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&ppc4xx_msi_driver);
पूर्ण

subsys_initcall(ppc4xx_msi_init);
