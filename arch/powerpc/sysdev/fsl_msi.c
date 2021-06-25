<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007-2011 Freescale Semiconductor, Inc.
 *
 * Author: Tony Li <tony.li@मुक्तscale.com>
 *	   Jason Jin <Jason.jin@मुक्तscale.com>
 *
 * The hwirq alloc and मुक्त code reuse from sysdev/mpic_msi.c
 */
#समावेश <linux/irq.h>
#समावेश <linux/msi.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/seq_file.h>
#समावेश <sysdev/fsl_soc.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/fsl_hcalls.h>

#समावेश "fsl_msi.h"
#समावेश "fsl_pci.h"

#घोषणा MSIIR_OFFSET_MASK	0xfffff
#घोषणा MSIIR_IBS_SHIFT		0
#घोषणा MSIIR_SRS_SHIFT		5
#घोषणा MSIIR1_IBS_SHIFT	4
#घोषणा MSIIR1_SRS_SHIFT	0
#घोषणा MSI_SRS_MASK		0xf
#घोषणा MSI_IBS_MASK		0x1f

#घोषणा msi_hwirq(msi, msir_index, पूर्णांकr_index) \
		((msir_index) << (msi)->srs_shअगरt | \
		 ((पूर्णांकr_index) << (msi)->ibs_shअगरt))

अटल LIST_HEAD(msi_head);

काष्ठा fsl_msi_feature अणु
	u32 fsl_pic_ip;
	u32 msiir_offset; /* Offset of MSIIR, relative to start of MSIR bank */
पूर्ण;

काष्ठा fsl_msi_cascade_data अणु
	काष्ठा fsl_msi *msi_data;
	पूर्णांक index;
	पूर्णांक virq;
पूर्ण;

अटल अंतरभूत u32 fsl_msi_पढ़ो(u32 __iomem *base, अचिन्हित पूर्णांक reg)
अणु
	वापस in_be32(base + (reg >> 2));
पूर्ण

/*
 * We करो not need this actually. The MSIR रेजिस्टर has been पढ़ो once
 * in the cascade पूर्णांकerrupt. So, this MSI पूर्णांकerrupt has been acked
*/
अटल व्योम fsl_msi_end_irq(काष्ठा irq_data *d)
अणु
पूर्ण

अटल व्योम fsl_msi_prपूर्णांक_chip(काष्ठा irq_data *irqd, काष्ठा seq_file *p)
अणु
	काष्ठा fsl_msi *msi_data = irqd->करोमुख्य->host_data;
	irq_hw_number_t hwirq = irqd_to_hwirq(irqd);
	पूर्णांक cascade_virq, srs;

	srs = (hwirq >> msi_data->srs_shअगरt) & MSI_SRS_MASK;
	cascade_virq = msi_data->cascade_array[srs]->virq;

	seq_म_लिखो(p, " fsl-msi-%d", cascade_virq);
पूर्ण


अटल काष्ठा irq_chip fsl_msi_chip = अणु
	.irq_mask	= pci_msi_mask_irq,
	.irq_unmask	= pci_msi_unmask_irq,
	.irq_ack	= fsl_msi_end_irq,
	.irq_prपूर्णांक_chip = fsl_msi_prपूर्णांक_chip,
पूर्ण;

अटल पूर्णांक fsl_msi_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
				irq_hw_number_t hw)
अणु
	काष्ठा fsl_msi *msi_data = h->host_data;
	काष्ठा irq_chip *chip = &fsl_msi_chip;

	irq_set_status_flags(virq, IRQ_TYPE_EDGE_FALLING);

	irq_set_chip_data(virq, msi_data);
	irq_set_chip_and_handler(virq, chip, handle_edge_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops fsl_msi_host_ops = अणु
	.map = fsl_msi_host_map,
पूर्ण;

अटल पूर्णांक fsl_msi_init_allocator(काष्ठा fsl_msi *msi_data)
अणु
	पूर्णांक rc, hwirq;

	rc = msi_biपंचांगap_alloc(&msi_data->biपंचांगap, NR_MSI_IRQS_MAX,
			      irq_करोमुख्य_get_of_node(msi_data->irqhost));
	अगर (rc)
		वापस rc;

	/*
	 * Reserve all the hwirqs
	 * The available hwirqs will be released in fsl_msi_setup_hwirq()
	 */
	क्रम (hwirq = 0; hwirq < NR_MSI_IRQS_MAX; hwirq++)
		msi_biपंचांगap_reserve_hwirq(&msi_data->biपंचांगap, hwirq);

	वापस 0;
पूर्ण

अटल व्योम fsl_tearकरोwn_msi_irqs(काष्ठा pci_dev *pdev)
अणु
	काष्ठा msi_desc *entry;
	काष्ठा fsl_msi *msi_data;
	irq_hw_number_t hwirq;

	क्रम_each_pci_msi_entry(entry, pdev) अणु
		अगर (!entry->irq)
			जारी;
		hwirq = virq_to_hw(entry->irq);
		msi_data = irq_get_chip_data(entry->irq);
		irq_set_msi_desc(entry->irq, शून्य);
		irq_dispose_mapping(entry->irq);
		msi_biपंचांगap_मुक्त_hwirqs(&msi_data->biपंचांगap, hwirq, 1);
	पूर्ण

	वापस;
पूर्ण

अटल व्योम fsl_compose_msi_msg(काष्ठा pci_dev *pdev, पूर्णांक hwirq,
				काष्ठा msi_msg *msg,
				काष्ठा fsl_msi *fsl_msi_data)
अणु
	काष्ठा fsl_msi *msi_data = fsl_msi_data;
	काष्ठा pci_controller *hose = pci_bus_to_host(pdev->bus);
	u64 address; /* Physical address of the MSIIR */
	पूर्णांक len;
	स्थिर __be64 *reg;

	/* If the msi-address-64 property exists, then use it */
	reg = of_get_property(hose->dn, "msi-address-64", &len);
	अगर (reg && (len == माप(u64)))
		address = be64_to_cpup(reg);
	अन्यथा
		address = fsl_pci_immrbar_base(hose) + msi_data->msiir_offset;

	msg->address_lo = lower_32_bits(address);
	msg->address_hi = upper_32_bits(address);

	/*
	 * MPIC version 2.0 has erratum PIC1. It causes
	 * that neither MSI nor MSI-X can work fine.
	 * This is a workaround to allow MSI-X to function
	 * properly. It only works क्रम MSI-X, we prevent
	 * MSI on buggy chips in fsl_setup_msi_irqs().
	 */
	अगर (msi_data->feature & MSI_HW_ERRATA_ENDIAN)
		msg->data = __swab32(hwirq);
	अन्यथा
		msg->data = hwirq;

	pr_debug("%s: allocated srs: %d, ibs: %d\n", __func__,
		 (hwirq >> msi_data->srs_shअगरt) & MSI_SRS_MASK,
		 (hwirq >> msi_data->ibs_shअगरt) & MSI_IBS_MASK);
पूर्ण

अटल पूर्णांक fsl_setup_msi_irqs(काष्ठा pci_dev *pdev, पूर्णांक nvec, पूर्णांक type)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(pdev->bus);
	काष्ठा device_node *np;
	phandle phandle = 0;
	पूर्णांक rc, hwirq = -ENOMEM;
	अचिन्हित पूर्णांक virq;
	काष्ठा msi_desc *entry;
	काष्ठा msi_msg msg;
	काष्ठा fsl_msi *msi_data;

	अगर (type == PCI_CAP_ID_MSI) अणु
		/*
		 * MPIC version 2.0 has erratum PIC1. For now MSI
		 * could not work. So check to prevent MSI from
		 * being used on the board with this erratum.
		 */
		list_क्रम_each_entry(msi_data, &msi_head, list)
			अगर (msi_data->feature & MSI_HW_ERRATA_ENDIAN)
				वापस -EINVAL;
	पूर्ण

	/*
	 * If the PCI node has an fsl,msi property, then we need to use it
	 * to find the specअगरic MSI.
	 */
	np = of_parse_phandle(hose->dn, "fsl,msi", 0);
	अगर (np) अणु
		अगर (of_device_is_compatible(np, "fsl,mpic-msi") ||
		    of_device_is_compatible(np, "fsl,vmpic-msi") ||
		    of_device_is_compatible(np, "fsl,vmpic-msi-v4.3"))
			phandle = np->phandle;
		अन्यथा अणु
			dev_err(&pdev->dev,
				"node %pOF has an invalid fsl,msi phandle %u\n",
				hose->dn, np->phandle);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	क्रम_each_pci_msi_entry(entry, pdev) अणु
		/*
		 * Loop over all the MSI devices until we find one that has an
		 * available पूर्णांकerrupt.
		 */
		list_क्रम_each_entry(msi_data, &msi_head, list) अणु
			/*
			 * If the PCI node has an fsl,msi property, then we
			 * restrict our search to the corresponding MSI node.
			 * The simplest way is to skip over MSI nodes with the
			 * wrong phandle. Under the Freescale hypervisor, this
			 * has the additional benefit of skipping over MSI
			 * nodes that are not mapped in the PAMU.
			 */
			अगर (phandle && (phandle != msi_data->phandle))
				जारी;

			hwirq = msi_biपंचांगap_alloc_hwirqs(&msi_data->biपंचांगap, 1);
			अगर (hwirq >= 0)
				अवरोध;
		पूर्ण

		अगर (hwirq < 0) अणु
			rc = hwirq;
			dev_err(&pdev->dev, "could not allocate MSI interrupt\n");
			जाओ out_मुक्त;
		पूर्ण

		virq = irq_create_mapping(msi_data->irqhost, hwirq);

		अगर (!virq) अणु
			dev_err(&pdev->dev, "fail mapping hwirq %i\n", hwirq);
			msi_biपंचांगap_मुक्त_hwirqs(&msi_data->biपंचांगap, hwirq, 1);
			rc = -ENOSPC;
			जाओ out_मुक्त;
		पूर्ण
		/* chip_data is msi_data via host->hostdata in host->map() */
		irq_set_msi_desc(virq, entry);

		fsl_compose_msi_msg(pdev, hwirq, &msg, msi_data);
		pci_ग_लिखो_msi_msg(virq, &msg);
	पूर्ण
	वापस 0;

out_मुक्त:
	/* मुक्त by the caller of this function */
	वापस rc;
पूर्ण

अटल irqवापस_t fsl_msi_cascade(पूर्णांक irq, व्योम *data)
अणु
	अचिन्हित पूर्णांक cascade_irq;
	काष्ठा fsl_msi *msi_data;
	पूर्णांक msir_index = -1;
	u32 msir_value = 0;
	u32 पूर्णांकr_index;
	u32 have_shअगरt = 0;
	काष्ठा fsl_msi_cascade_data *cascade_data = data;
	irqवापस_t ret = IRQ_NONE;

	msi_data = cascade_data->msi_data;

	msir_index = cascade_data->index;

	अगर (msir_index >= NR_MSI_REG_MAX)
		cascade_irq = 0;

	चयन (msi_data->feature & FSL_PIC_IP_MASK) अणु
	हाल FSL_PIC_IP_MPIC:
		msir_value = fsl_msi_पढ़ो(msi_data->msi_regs,
			msir_index * 0x10);
		अवरोध;
	हाल FSL_PIC_IP_IPIC:
		msir_value = fsl_msi_पढ़ो(msi_data->msi_regs, msir_index * 0x4);
		अवरोध;
#अगर_घोषित CONFIG_EPAPR_PARAVIRT
	हाल FSL_PIC_IP_VMPIC: अणु
		अचिन्हित पूर्णांक ret;
		ret = fh_vmpic_get_msir(virq_to_hw(irq), &msir_value);
		अगर (ret) अणु
			pr_err("fsl-msi: fh_vmpic_get_msir() failed for "
			       "irq %u (ret=%u)\n", irq, ret);
			msir_value = 0;
		पूर्ण
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	पूर्ण

	जबतक (msir_value) अणु
		पूर्णांकr_index = ffs(msir_value) - 1;

		cascade_irq = irq_linear_revmap(msi_data->irqhost,
				msi_hwirq(msi_data, msir_index,
					  पूर्णांकr_index + have_shअगरt));
		अगर (cascade_irq) अणु
			generic_handle_irq(cascade_irq);
			ret = IRQ_HANDLED;
		पूर्ण
		have_shअगरt += पूर्णांकr_index + 1;
		msir_value = msir_value >> (पूर्णांकr_index + 1);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fsl_of_msi_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा fsl_msi *msi = platक्रमm_get_drvdata(ofdev);
	पूर्णांक virq, i;

	अगर (msi->list.prev != शून्य)
		list_del(&msi->list);
	क्रम (i = 0; i < NR_MSI_REG_MAX; i++) अणु
		अगर (msi->cascade_array[i]) अणु
			virq = msi->cascade_array[i]->virq;

			BUG_ON(!virq);

			मुक्त_irq(virq, msi->cascade_array[i]);
			kमुक्त(msi->cascade_array[i]);
			irq_dispose_mapping(virq);
		पूर्ण
	पूर्ण
	अगर (msi->biपंचांगap.biपंचांगap)
		msi_biपंचांगap_मुक्त(&msi->biपंचांगap);
	अगर ((msi->feature & FSL_PIC_IP_MASK) != FSL_PIC_IP_VMPIC)
		iounmap(msi->msi_regs);
	kमुक्त(msi);

	वापस 0;
पूर्ण

अटल काष्ठा lock_class_key fsl_msi_irq_class;
अटल काष्ठा lock_class_key fsl_msi_irq_request_class;

अटल पूर्णांक fsl_msi_setup_hwirq(काष्ठा fsl_msi *msi, काष्ठा platक्रमm_device *dev,
			       पूर्णांक offset, पूर्णांक irq_index)
अणु
	काष्ठा fsl_msi_cascade_data *cascade_data = शून्य;
	पूर्णांक virt_msir, i, ret;

	virt_msir = irq_of_parse_and_map(dev->dev.of_node, irq_index);
	अगर (!virt_msir) अणु
		dev_err(&dev->dev, "%s: Cannot translate IRQ index %d\n",
			__func__, irq_index);
		वापस 0;
	पूर्ण

	cascade_data = kzalloc(माप(काष्ठा fsl_msi_cascade_data), GFP_KERNEL);
	अगर (!cascade_data) अणु
		dev_err(&dev->dev, "No memory for MSI cascade data\n");
		वापस -ENOMEM;
	पूर्ण
	irq_set_lockdep_class(virt_msir, &fsl_msi_irq_class,
			      &fsl_msi_irq_request_class);
	cascade_data->index = offset;
	cascade_data->msi_data = msi;
	cascade_data->virq = virt_msir;
	msi->cascade_array[irq_index] = cascade_data;

	ret = request_irq(virt_msir, fsl_msi_cascade, IRQF_NO_THREAD,
			  "fsl-msi-cascade", cascade_data);
	अगर (ret) अणु
		dev_err(&dev->dev, "failed to request_irq(%d), ret = %d\n",
			virt_msir, ret);
		वापस ret;
	पूर्ण

	/* Release the hwirqs corresponding to this MSI रेजिस्टर */
	क्रम (i = 0; i < IRQS_PER_MSI_REG; i++)
		msi_biपंचांगap_मुक्त_hwirqs(&msi->biपंचांगap,
				       msi_hwirq(msi, offset, i), 1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fsl_of_msi_ids[];
अटल पूर्णांक fsl_of_msi_probe(काष्ठा platक्रमm_device *dev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा fsl_msi *msi;
	काष्ठा resource res, msiir;
	पूर्णांक err, i, j, irq_index, count;
	स्थिर u32 *p;
	स्थिर काष्ठा fsl_msi_feature *features;
	पूर्णांक len;
	u32 offset;
	काष्ठा pci_controller *phb;

	match = of_match_device(fsl_of_msi_ids, &dev->dev);
	अगर (!match)
		वापस -EINVAL;
	features = match->data;

	prपूर्णांकk(KERN_DEBUG "Setting up Freescale MSI support\n");

	msi = kzalloc(माप(काष्ठा fsl_msi), GFP_KERNEL);
	अगर (!msi) अणु
		dev_err(&dev->dev, "No memory for MSI structure\n");
		वापस -ENOMEM;
	पूर्ण
	platक्रमm_set_drvdata(dev, msi);

	msi->irqhost = irq_करोमुख्य_add_linear(dev->dev.of_node,
				      NR_MSI_IRQS_MAX, &fsl_msi_host_ops, msi);

	अगर (msi->irqhost == शून्य) अणु
		dev_err(&dev->dev, "No memory for MSI irqhost\n");
		err = -ENOMEM;
		जाओ error_out;
	पूर्ण

	/*
	 * Under the Freescale hypervisor, the msi nodes करोn't have a 'reg'
	 * property.  Instead, we use hypercalls to access the MSI.
	 */
	अगर ((features->fsl_pic_ip & FSL_PIC_IP_MASK) != FSL_PIC_IP_VMPIC) अणु
		err = of_address_to_resource(dev->dev.of_node, 0, &res);
		अगर (err) अणु
			dev_err(&dev->dev, "invalid resource for node %pOF\n",
				dev->dev.of_node);
			जाओ error_out;
		पूर्ण

		msi->msi_regs = ioremap(res.start, resource_size(&res));
		अगर (!msi->msi_regs) अणु
			err = -ENOMEM;
			dev_err(&dev->dev, "could not map node %pOF\n",
				dev->dev.of_node);
			जाओ error_out;
		पूर्ण
		msi->msiir_offset =
			features->msiir_offset + (res.start & 0xfffff);

		/*
		 * First पढ़ो the MSIIR/MSIIR1 offset from dts
		 * On failure use the hardcode MSIIR offset
		 */
		अगर (of_address_to_resource(dev->dev.of_node, 1, &msiir))
			msi->msiir_offset = features->msiir_offset +
					    (res.start & MSIIR_OFFSET_MASK);
		अन्यथा
			msi->msiir_offset = msiir.start & MSIIR_OFFSET_MASK;
	पूर्ण

	msi->feature = features->fsl_pic_ip;

	/* For erratum PIC1 on MPIC version 2.0*/
	अगर ((features->fsl_pic_ip & FSL_PIC_IP_MASK) == FSL_PIC_IP_MPIC
			&& (fsl_mpic_primary_get_version() == 0x0200))
		msi->feature |= MSI_HW_ERRATA_ENDIAN;

	/*
	 * Remember the phandle, so that we can match with any PCI nodes
	 * that have an "fsl,msi" property.
	 */
	msi->phandle = dev->dev.of_node->phandle;

	err = fsl_msi_init_allocator(msi);
	अगर (err) अणु
		dev_err(&dev->dev, "Error allocating MSI bitmap\n");
		जाओ error_out;
	पूर्ण

	p = of_get_property(dev->dev.of_node, "msi-available-ranges", &len);

	अगर (of_device_is_compatible(dev->dev.of_node, "fsl,mpic-msi-v4.3") ||
	    of_device_is_compatible(dev->dev.of_node, "fsl,vmpic-msi-v4.3")) अणु
		msi->srs_shअगरt = MSIIR1_SRS_SHIFT;
		msi->ibs_shअगरt = MSIIR1_IBS_SHIFT;
		अगर (p)
			dev_warn(&dev->dev, "%s: dose not support msi-available-ranges property\n",
				__func__);

		क्रम (irq_index = 0; irq_index < NR_MSI_REG_MSIIR1;
		     irq_index++) अणु
			err = fsl_msi_setup_hwirq(msi, dev,
						  irq_index, irq_index);
			अगर (err)
				जाओ error_out;
		पूर्ण
	पूर्ण अन्यथा अणु
		अटल स्थिर u32 all_avail[] =
			अणु 0, NR_MSI_REG_MSIIR * IRQS_PER_MSI_REG पूर्ण;

		msi->srs_shअगरt = MSIIR_SRS_SHIFT;
		msi->ibs_shअगरt = MSIIR_IBS_SHIFT;

		अगर (p && len % (2 * माप(u32)) != 0) अणु
			dev_err(&dev->dev, "%s: Malformed msi-available-ranges property\n",
				__func__);
			err = -EINVAL;
			जाओ error_out;
		पूर्ण

		अगर (!p) अणु
			p = all_avail;
			len = माप(all_avail);
		पूर्ण

		क्रम (irq_index = 0, i = 0; i < len / (2 * माप(u32)); i++) अणु
			अगर (p[i * 2] % IRQS_PER_MSI_REG ||
			    p[i * 2 + 1] % IRQS_PER_MSI_REG) अणु
				pr_warn("%s: %pOF: msi available range of %u at %u is not IRQ-aligned\n",
				       __func__, dev->dev.of_node,
				       p[i * 2 + 1], p[i * 2]);
				err = -EINVAL;
				जाओ error_out;
			पूर्ण

			offset = p[i * 2] / IRQS_PER_MSI_REG;
			count = p[i * 2 + 1] / IRQS_PER_MSI_REG;

			क्रम (j = 0; j < count; j++, irq_index++) अणु
				err = fsl_msi_setup_hwirq(msi, dev, offset + j,
							  irq_index);
				अगर (err)
					जाओ error_out;
			पूर्ण
		पूर्ण
	पूर्ण

	list_add_tail(&msi->list, &msi_head);

	/*
	 * Apply the MSI ops to all the controllers.
	 * It करोesn't hurt to reassign the same ops,
	 * but bail out अगर we find another MSI driver.
	 */
	list_क्रम_each_entry(phb, &hose_list, list_node) अणु
		अगर (!phb->controller_ops.setup_msi_irqs) अणु
			phb->controller_ops.setup_msi_irqs = fsl_setup_msi_irqs;
			phb->controller_ops.tearकरोwn_msi_irqs = fsl_tearकरोwn_msi_irqs;
		पूर्ण अन्यथा अगर (phb->controller_ops.setup_msi_irqs != fsl_setup_msi_irqs) अणु
			dev_err(&dev->dev, "Different MSI driver already installed!\n");
			err = -ENODEV;
			जाओ error_out;
		पूर्ण
	पूर्ण
	वापस 0;
error_out:
	fsl_of_msi_हटाओ(dev);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा fsl_msi_feature mpic_msi_feature = अणु
	.fsl_pic_ip = FSL_PIC_IP_MPIC,
	.msiir_offset = 0x140,
पूर्ण;

अटल स्थिर काष्ठा fsl_msi_feature ipic_msi_feature = अणु
	.fsl_pic_ip = FSL_PIC_IP_IPIC,
	.msiir_offset = 0x38,
पूर्ण;

अटल स्थिर काष्ठा fsl_msi_feature vmpic_msi_feature = अणु
	.fsl_pic_ip = FSL_PIC_IP_VMPIC,
	.msiir_offset = 0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id fsl_of_msi_ids[] = अणु
	अणु
		.compatible = "fsl,mpic-msi",
		.data = &mpic_msi_feature,
	पूर्ण,
	अणु
		.compatible = "fsl,mpic-msi-v4.3",
		.data = &mpic_msi_feature,
	पूर्ण,
	अणु
		.compatible = "fsl,ipic-msi",
		.data = &ipic_msi_feature,
	पूर्ण,
#अगर_घोषित CONFIG_EPAPR_PARAVIRT
	अणु
		.compatible = "fsl,vmpic-msi",
		.data = &vmpic_msi_feature,
	पूर्ण,
	अणु
		.compatible = "fsl,vmpic-msi-v4.3",
		.data = &vmpic_msi_feature,
	पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver fsl_of_msi_driver = अणु
	.driver = अणु
		.name = "fsl-msi",
		.of_match_table = fsl_of_msi_ids,
	पूर्ण,
	.probe = fsl_of_msi_probe,
	.हटाओ = fsl_of_msi_हटाओ,
पूर्ण;

अटल __init पूर्णांक fsl_of_msi_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&fsl_of_msi_driver);
पूर्ण

subsys_initcall(fsl_of_msi_init);
