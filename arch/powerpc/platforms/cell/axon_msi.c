<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2007, Michael Ellerman, IBM Corporation.
 */


#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/msi.h>
#समावेश <linux/export.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/dcr.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/prom.h>

#समावेश "cell.h"

/*
 * MSIC रेजिस्टरs, specअगरied as offsets from dcr_base
 */
#घोषणा MSIC_CTRL_REG	0x0

/* Base Address रेजिस्टरs specअगरy FIFO location in BE memory */
#घोषणा MSIC_BASE_ADDR_HI_REG	0x3
#घोषणा MSIC_BASE_ADDR_LO_REG	0x4

/* Hold the पढ़ो/ग_लिखो offsets पूर्णांकo the FIFO */
#घोषणा MSIC_READ_OFFSET_REG	0x5
#घोषणा MSIC_WRITE_OFFSET_REG	0x6


/* MSIC control रेजिस्टर flags */
#घोषणा MSIC_CTRL_ENABLE		0x0001
#घोषणा MSIC_CTRL_FIFO_FULL_ENABLE	0x0002
#घोषणा MSIC_CTRL_IRQ_ENABLE		0x0008
#घोषणा MSIC_CTRL_FULL_STOP_ENABLE	0x0010

/*
 * The MSIC can be configured to use a FIFO of 32KB, 64KB, 128KB or 256KB.
 * Currently we're using a 64KB FIFO size.
 */
#घोषणा MSIC_FIFO_SIZE_SHIFT	16
#घोषणा MSIC_FIFO_SIZE_BYTES	(1 << MSIC_FIFO_SIZE_SHIFT)

/*
 * To configure the FIFO size as (1 << n) bytes, we ग_लिखो (n - 15) पूर्णांकo bits
 * 8-9 of the MSIC control reg.
 */
#घोषणा MSIC_CTRL_FIFO_SIZE	(((MSIC_FIFO_SIZE_SHIFT - 15) << 8) & 0x300)

/*
 * We need to mask the पढ़ो/ग_लिखो offsets to make sure they stay within
 * the bounds of the FIFO. Also they should always be 16-byte aligned.
 */
#घोषणा MSIC_FIFO_SIZE_MASK	((MSIC_FIFO_SIZE_BYTES - 1) & ~0xFu)

/* Each entry in the FIFO is 16 bytes, the first 4 bytes hold the irq # */
#घोषणा MSIC_FIFO_ENTRY_SIZE	0x10


काष्ठा axon_msic अणु
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
	__le32 *fअगरo_virt;
	dma_addr_t fअगरo_phys;
	dcr_host_t dcr_host;
	u32 पढ़ो_offset;
#अगर_घोषित DEBUG
	u32 __iomem *trigger;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित DEBUG
व्योम axon_msi_debug_setup(काष्ठा device_node *dn, काष्ठा axon_msic *msic);
#अन्यथा
अटल अंतरभूत व्योम axon_msi_debug_setup(काष्ठा device_node *dn,
					काष्ठा axon_msic *msic) अणु पूर्ण
#पूर्ण_अगर


अटल व्योम msic_dcr_ग_लिखो(काष्ठा axon_msic *msic, अचिन्हित पूर्णांक dcr_n, u32 val)
अणु
	pr_devel("axon_msi: dcr_write(0x%x, 0x%x)\n", val, dcr_n);

	dcr_ग_लिखो(msic->dcr_host, dcr_n, val);
पूर्ण

अटल व्योम axon_msi_cascade(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा axon_msic *msic = irq_desc_get_handler_data(desc);
	u32 ग_लिखो_offset, msi;
	पूर्णांक idx;
	पूर्णांक retry = 0;

	ग_लिखो_offset = dcr_पढ़ो(msic->dcr_host, MSIC_WRITE_OFFSET_REG);
	pr_devel("axon_msi: original write_offset 0x%x\n", ग_लिखो_offset);

	/* ग_लिखो_offset करोesn't wrap properly, so we have to mask it */
	ग_लिखो_offset &= MSIC_FIFO_SIZE_MASK;

	जबतक (msic->पढ़ो_offset != ग_लिखो_offset && retry < 100) अणु
		idx  = msic->पढ़ो_offset / माप(__le32);
		msi  = le32_to_cpu(msic->fअगरo_virt[idx]);
		msi &= 0xFFFF;

		pr_devel("axon_msi: woff %x roff %x msi %x\n",
			  ग_लिखो_offset, msic->पढ़ो_offset, msi);

		अगर (msi < nr_irqs && irq_get_chip_data(msi) == msic) अणु
			generic_handle_irq(msi);
			msic->fअगरo_virt[idx] = cpu_to_le32(0xffffffff);
		पूर्ण अन्यथा अणु
			/*
			 * Reading the MSIC_WRITE_OFFSET_REG करोes not
			 * reliably flush the outstanding DMA to the
			 * FIFO buffer. Here we were पढ़ोing stale
			 * data, so we need to retry.
			 */
			udelay(1);
			retry++;
			pr_devel("axon_msi: invalid irq 0x%x!\n", msi);
			जारी;
		पूर्ण

		अगर (retry) अणु
			pr_devel("axon_msi: late irq 0x%x, retry %d\n",
				 msi, retry);
			retry = 0;
		पूर्ण

		msic->पढ़ो_offset += MSIC_FIFO_ENTRY_SIZE;
		msic->पढ़ो_offset &= MSIC_FIFO_SIZE_MASK;
	पूर्ण

	अगर (retry) अणु
		prपूर्णांकk(KERN_WARNING "axon_msi: irq timed out\n");

		msic->पढ़ो_offset += MSIC_FIFO_ENTRY_SIZE;
		msic->पढ़ो_offset &= MSIC_FIFO_SIZE_MASK;
	पूर्ण

	chip->irq_eoi(&desc->irq_data);
पूर्ण

अटल काष्ठा axon_msic *find_msi_translator(काष्ठा pci_dev *dev)
अणु
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
	काष्ठा device_node *dn, *पंचांगp;
	स्थिर phandle *ph;
	काष्ठा axon_msic *msic = शून्य;

	dn = of_node_get(pci_device_to_OF_node(dev));
	अगर (!dn) अणु
		dev_dbg(&dev->dev, "axon_msi: no pci_dn found\n");
		वापस शून्य;
	पूर्ण

	क्रम (; dn; dn = of_get_next_parent(dn)) अणु
		ph = of_get_property(dn, "msi-translator", शून्य);
		अगर (ph)
			अवरोध;
	पूर्ण

	अगर (!ph) अणु
		dev_dbg(&dev->dev,
			"axon_msi: no msi-translator property found\n");
		जाओ out_error;
	पूर्ण

	पंचांगp = dn;
	dn = of_find_node_by_phandle(*ph);
	of_node_put(पंचांगp);
	अगर (!dn) अणु
		dev_dbg(&dev->dev,
			"axon_msi: msi-translator doesn't point to a node\n");
		जाओ out_error;
	पूर्ण

	irq_करोमुख्य = irq_find_host(dn);
	अगर (!irq_करोमुख्य) अणु
		dev_dbg(&dev->dev, "axon_msi: no irq_domain found for node %pOF\n",
			dn);
		जाओ out_error;
	पूर्ण

	msic = irq_करोमुख्य->host_data;

out_error:
	of_node_put(dn);

	वापस msic;
पूर्ण

अटल पूर्णांक setup_msi_msg_address(काष्ठा pci_dev *dev, काष्ठा msi_msg *msg)
अणु
	काष्ठा device_node *dn;
	काष्ठा msi_desc *entry;
	पूर्णांक len;
	स्थिर u32 *prop;

	dn = of_node_get(pci_device_to_OF_node(dev));
	अगर (!dn) अणु
		dev_dbg(&dev->dev, "axon_msi: no pci_dn found\n");
		वापस -ENODEV;
	पूर्ण

	entry = first_pci_msi_entry(dev);

	क्रम (; dn; dn = of_get_next_parent(dn)) अणु
		अगर (entry->msi_attrib.is_64) अणु
			prop = of_get_property(dn, "msi-address-64", &len);
			अगर (prop)
				अवरोध;
		पूर्ण

		prop = of_get_property(dn, "msi-address-32", &len);
		अगर (prop)
			अवरोध;
	पूर्ण

	अगर (!prop) अणु
		dev_dbg(&dev->dev,
			"axon_msi: no msi-address-(32|64) properties found\n");
		वापस -ENOENT;
	पूर्ण

	चयन (len) अणु
	हाल 8:
		msg->address_hi = prop[0];
		msg->address_lo = prop[1];
		अवरोध;
	हाल 4:
		msg->address_hi = 0;
		msg->address_lo = prop[0];
		अवरोध;
	शेष:
		dev_dbg(&dev->dev,
			"axon_msi: malformed msi-address-(32|64) property\n");
		of_node_put(dn);
		वापस -EINVAL;
	पूर्ण

	of_node_put(dn);

	वापस 0;
पूर्ण

अटल पूर्णांक axon_msi_setup_msi_irqs(काष्ठा pci_dev *dev, पूर्णांक nvec, पूर्णांक type)
अणु
	अचिन्हित पूर्णांक virq, rc;
	काष्ठा msi_desc *entry;
	काष्ठा msi_msg msg;
	काष्ठा axon_msic *msic;

	msic = find_msi_translator(dev);
	अगर (!msic)
		वापस -ENODEV;

	rc = setup_msi_msg_address(dev, &msg);
	अगर (rc)
		वापस rc;

	क्रम_each_pci_msi_entry(entry, dev) अणु
		virq = irq_create_direct_mapping(msic->irq_करोमुख्य);
		अगर (!virq) अणु
			dev_warn(&dev->dev,
				 "axon_msi: virq allocation failed!\n");
			वापस -1;
		पूर्ण
		dev_dbg(&dev->dev, "axon_msi: allocated virq 0x%x\n", virq);

		irq_set_msi_desc(virq, entry);
		msg.data = virq;
		pci_ग_लिखो_msi_msg(virq, &msg);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम axon_msi_tearकरोwn_msi_irqs(काष्ठा pci_dev *dev)
अणु
	काष्ठा msi_desc *entry;

	dev_dbg(&dev->dev, "axon_msi: tearing down msi irqs\n");

	क्रम_each_pci_msi_entry(entry, dev) अणु
		अगर (!entry->irq)
			जारी;

		irq_set_msi_desc(entry->irq, शून्य);
		irq_dispose_mapping(entry->irq);
	पूर्ण
पूर्ण

अटल काष्ठा irq_chip msic_irq_chip = अणु
	.irq_mask	= pci_msi_mask_irq,
	.irq_unmask	= pci_msi_unmask_irq,
	.irq_shutकरोwn	= pci_msi_mask_irq,
	.name		= "AXON-MSI",
पूर्ण;

अटल पूर्णांक msic_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			 irq_hw_number_t hw)
अणु
	irq_set_chip_data(virq, h->host_data);
	irq_set_chip_and_handler(virq, &msic_irq_chip, handle_simple_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops msic_host_ops = अणु
	.map	= msic_host_map,
पूर्ण;

अटल व्योम axon_msi_shutकरोwn(काष्ठा platक्रमm_device *device)
अणु
	काष्ठा axon_msic *msic = dev_get_drvdata(&device->dev);
	u32 पंचांगp;

	pr_devel("axon_msi: disabling %pOF\n",
		 irq_करोमुख्य_get_of_node(msic->irq_करोमुख्य));
	पंचांगp  = dcr_पढ़ो(msic->dcr_host, MSIC_CTRL_REG);
	पंचांगp &= ~MSIC_CTRL_ENABLE & ~MSIC_CTRL_IRQ_ENABLE;
	msic_dcr_ग_लिखो(msic, MSIC_CTRL_REG, पंचांगp);
पूर्ण

अटल पूर्णांक axon_msi_probe(काष्ठा platक्रमm_device *device)
अणु
	काष्ठा device_node *dn = device->dev.of_node;
	काष्ठा axon_msic *msic;
	अचिन्हित पूर्णांक virq;
	पूर्णांक dcr_base, dcr_len;

	pr_devel("axon_msi: setting up dn %pOF\n", dn);

	msic = kzalloc(माप(*msic), GFP_KERNEL);
	अगर (!msic) अणु
		prपूर्णांकk(KERN_ERR "axon_msi: couldn't allocate msic for %pOF\n",
		       dn);
		जाओ out;
	पूर्ण

	dcr_base = dcr_resource_start(dn, 0);
	dcr_len = dcr_resource_len(dn, 0);

	अगर (dcr_base == 0 || dcr_len == 0) अणु
		prपूर्णांकk(KERN_ERR
		       "axon_msi: couldn't parse dcr properties on %pOF\n",
			dn);
		जाओ out_मुक्त_msic;
	पूर्ण

	msic->dcr_host = dcr_map(dn, dcr_base, dcr_len);
	अगर (!DCR_MAP_OK(msic->dcr_host)) अणु
		prपूर्णांकk(KERN_ERR "axon_msi: dcr_map failed for %pOF\n",
		       dn);
		जाओ out_मुक्त_msic;
	पूर्ण

	msic->fअगरo_virt = dma_alloc_coherent(&device->dev, MSIC_FIFO_SIZE_BYTES,
					     &msic->fअगरo_phys, GFP_KERNEL);
	अगर (!msic->fअगरo_virt) अणु
		prपूर्णांकk(KERN_ERR "axon_msi: couldn't allocate fifo for %pOF\n",
		       dn);
		जाओ out_मुक्त_msic;
	पूर्ण

	virq = irq_of_parse_and_map(dn, 0);
	अगर (!virq) अणु
		prपूर्णांकk(KERN_ERR "axon_msi: irq parse and map failed for %pOF\n",
		       dn);
		जाओ out_मुक्त_fअगरo;
	पूर्ण
	स_रखो(msic->fअगरo_virt, 0xff, MSIC_FIFO_SIZE_BYTES);

	/* We rely on being able to stash a virq in a u16, so limit irqs to < 65536 */
	msic->irq_करोमुख्य = irq_करोमुख्य_add_nomap(dn, 65536, &msic_host_ops, msic);
	अगर (!msic->irq_करोमुख्य) अणु
		prपूर्णांकk(KERN_ERR "axon_msi: couldn't allocate irq_domain for %pOF\n",
		       dn);
		जाओ out_मुक्त_fअगरo;
	पूर्ण

	irq_set_handler_data(virq, msic);
	irq_set_chained_handler(virq, axon_msi_cascade);
	pr_devel("axon_msi: irq 0x%x setup for axon_msi\n", virq);

	/* Enable the MSIC hardware */
	msic_dcr_ग_लिखो(msic, MSIC_BASE_ADDR_HI_REG, msic->fअगरo_phys >> 32);
	msic_dcr_ग_लिखो(msic, MSIC_BASE_ADDR_LO_REG,
				  msic->fअगरo_phys & 0xFFFFFFFF);
	msic_dcr_ग_लिखो(msic, MSIC_CTRL_REG,
			MSIC_CTRL_IRQ_ENABLE | MSIC_CTRL_ENABLE |
			MSIC_CTRL_FIFO_SIZE);

	msic->पढ़ो_offset = dcr_पढ़ो(msic->dcr_host, MSIC_WRITE_OFFSET_REG)
				& MSIC_FIFO_SIZE_MASK;

	dev_set_drvdata(&device->dev, msic);

	cell_pci_controller_ops.setup_msi_irqs = axon_msi_setup_msi_irqs;
	cell_pci_controller_ops.tearकरोwn_msi_irqs = axon_msi_tearकरोwn_msi_irqs;

	axon_msi_debug_setup(dn, msic);

	prपूर्णांकk(KERN_DEBUG "axon_msi: setup MSIC on %pOF\n", dn);

	वापस 0;

out_मुक्त_fअगरo:
	dma_मुक्त_coherent(&device->dev, MSIC_FIFO_SIZE_BYTES, msic->fअगरo_virt,
			  msic->fअगरo_phys);
out_मुक्त_msic:
	kमुक्त(msic);
out:

	वापस -1;
पूर्ण

अटल स्थिर काष्ठा of_device_id axon_msi_device_id[] = अणु
	अणु
		.compatible	= "ibm,axon-msic"
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver axon_msi_driver = अणु
	.probe		= axon_msi_probe,
	.shutकरोwn	= axon_msi_shutकरोwn,
	.driver = अणु
		.name = "axon-msi",
		.of_match_table = axon_msi_device_id,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init axon_msi_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&axon_msi_driver);
पूर्ण
subsys_initcall(axon_msi_init);


#अगर_घोषित DEBUG
अटल पूर्णांक msic_set(व्योम *data, u64 val)
अणु
	काष्ठा axon_msic *msic = data;
	out_le32(msic->trigger, val);
	वापस 0;
पूर्ण

अटल पूर्णांक msic_get(व्योम *data, u64 *val)
अणु
	*val = 0;
	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(fops_msic, msic_get, msic_set, "%llu\n");

व्योम axon_msi_debug_setup(काष्ठा device_node *dn, काष्ठा axon_msic *msic)
अणु
	अक्षर name[8];
	u64 addr;

	addr = of_translate_address(dn, of_get_property(dn, "reg", शून्य));
	अगर (addr == OF_BAD_ADDR) अणु
		pr_devel("axon_msi: couldn't translate reg property\n");
		वापस;
	पूर्ण

	msic->trigger = ioremap(addr, 0x4);
	अगर (!msic->trigger) अणु
		pr_devel("axon_msi: ioremap failed\n");
		वापस;
	पूर्ण

	snम_लिखो(name, माप(name), "msic_%d", of_node_to_nid(dn));

	debugfs_create_file(name, 0600, घातerpc_debugfs_root, msic, &fops_msic);
पूर्ण
#पूर्ण_अगर /* DEBUG */
