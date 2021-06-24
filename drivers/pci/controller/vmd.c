<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Volume Management Device driver
 * Copyright (c) 2015, Intel Corporation.
 */

#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/msi.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci-ecam.h>
#समावेश <linux/srcu.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rcupdate.h>

#समावेश <यंत्र/irqकरोमुख्य.h>
#समावेश <यंत्र/device.h>
#समावेश <यंत्र/msi.h>

#घोषणा VMD_CFGBAR	0
#घोषणा VMD_MEMBAR1	2
#घोषणा VMD_MEMBAR2	4

#घोषणा PCI_REG_VMCAP		0x40
#घोषणा BUS_RESTRICT_CAP(vmcap)	(vmcap & 0x1)
#घोषणा PCI_REG_VMCONFIG	0x44
#घोषणा BUS_RESTRICT_CFG(vmcfg)	((vmcfg >> 8) & 0x3)
#घोषणा VMCONFIG_MSI_REMAP	0x2
#घोषणा PCI_REG_VMLOCK		0x70
#घोषणा MB2_SHADOW_EN(vmlock)	(vmlock & 0x2)

#घोषणा MB2_SHADOW_OFFSET	0x2000
#घोषणा MB2_SHADOW_SIZE		16

क्रमागत vmd_features अणु
	/*
	 * Device may contain रेजिस्टरs which hपूर्णांक the physical location of the
	 * membars, in order to allow proper address translation during
	 * resource assignment to enable guest भवization
	 */
	VMD_FEAT_HAS_MEMBAR_SHADOW		= (1 << 0),

	/*
	 * Device may provide root port configuration inक्रमmation which limits
	 * bus numbering
	 */
	VMD_FEAT_HAS_BUS_RESTRICTIONS		= (1 << 1),

	/*
	 * Device contains physical location shaकरोw रेजिस्टरs in
	 * venकरोr-specअगरic capability space
	 */
	VMD_FEAT_HAS_MEMBAR_SHADOW_VSCAP	= (1 << 2),

	/*
	 * Device may use MSI-X vector 0 क्रम software triggering and will not
	 * be used क्रम MSI remapping
	 */
	VMD_FEAT_OFFSET_FIRST_VECTOR		= (1 << 3),

	/*
	 * Device can bypass remapping MSI-X transactions पूर्णांकo its MSI-X table,
	 * aव्योमing the requirement of a VMD MSI करोमुख्य क्रम child device
	 * पूर्णांकerrupt handling.
	 */
	VMD_FEAT_CAN_BYPASS_MSI_REMAP		= (1 << 4),
पूर्ण;

/*
 * Lock क्रम manipulating VMD IRQ lists.
 */
अटल DEFINE_RAW_SPINLOCK(list_lock);

/**
 * काष्ठा vmd_irq - निजी data to map driver IRQ to the VMD shared vector
 * @node:	list item क्रम parent traversal.
 * @irq:	back poपूर्णांकer to parent.
 * @enabled:	true अगर driver enabled IRQ
 * @virq:	the भव IRQ value provided to the requesting driver.
 *
 * Every MSI/MSI-X IRQ requested क्रम a device in a VMD करोमुख्य will be mapped to
 * a VMD IRQ using this काष्ठाure.
 */
काष्ठा vmd_irq अणु
	काष्ठा list_head	node;
	काष्ठा vmd_irq_list	*irq;
	bool			enabled;
	अचिन्हित पूर्णांक		virq;
पूर्ण;

/**
 * काष्ठा vmd_irq_list - list of driver requested IRQs mapping to a VMD vector
 * @irq_list:	the list of irq's the VMD one demuxes to.
 * @srcu:	SRCU काष्ठा क्रम local synchronization.
 * @count:	number of child IRQs asचिन्हित to this vector; used to track
 *		sharing.
 */
काष्ठा vmd_irq_list अणु
	काष्ठा list_head	irq_list;
	काष्ठा srcu_काष्ठा	srcu;
	अचिन्हित पूर्णांक		count;
पूर्ण;

काष्ठा vmd_dev अणु
	काष्ठा pci_dev		*dev;

	spinlock_t		cfg_lock;
	व्योम __iomem		*cfgbar;

	पूर्णांक msix_count;
	काष्ठा vmd_irq_list	*irqs;

	काष्ठा pci_sysdata	sysdata;
	काष्ठा resource		resources[3];
	काष्ठा irq_करोमुख्य	*irq_करोमुख्य;
	काष्ठा pci_bus		*bus;
	u8			busn_start;
	u8			first_vec;
पूर्ण;

अटल अंतरभूत काष्ठा vmd_dev *vmd_from_bus(काष्ठा pci_bus *bus)
अणु
	वापस container_of(bus->sysdata, काष्ठा vmd_dev, sysdata);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक index_from_irqs(काष्ठा vmd_dev *vmd,
					   काष्ठा vmd_irq_list *irqs)
अणु
	वापस irqs - vmd->irqs;
पूर्ण

/*
 * Drivers managing a device in a VMD करोमुख्य allocate their own IRQs as beक्रमe,
 * but the MSI entry क्रम the hardware it's driving will be programmed with a
 * destination ID क्रम the VMD MSI-X table.  The VMD muxes पूर्णांकerrupts in its
 * करोमुख्य पूर्णांकo one of its own, and the VMD driver de-muxes these क्रम the
 * handlers sharing that VMD IRQ.  The vmd irq_करोमुख्य provides the operations
 * and irq_chip to set this up.
 */
अटल व्योम vmd_compose_msi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	काष्ठा vmd_irq *vmdirq = data->chip_data;
	काष्ठा vmd_irq_list *irq = vmdirq->irq;
	काष्ठा vmd_dev *vmd = irq_data_get_irq_handler_data(data);

	स_रखो(msg, 0, माप(*msg));
	msg->address_hi = X86_MSI_BASE_ADDRESS_HIGH;
	msg->arch_addr_lo.base_address = X86_MSI_BASE_ADDRESS_LOW;
	msg->arch_addr_lo.destid_0_7 = index_from_irqs(vmd, irq);
पूर्ण

/*
 * We rely on MSI_FLAG_USE_DEF_CHIP_OPS to set the IRQ mask/unmask ops.
 */
अटल व्योम vmd_irq_enable(काष्ठा irq_data *data)
अणु
	काष्ठा vmd_irq *vmdirq = data->chip_data;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&list_lock, flags);
	WARN_ON(vmdirq->enabled);
	list_add_tail_rcu(&vmdirq->node, &vmdirq->irq->irq_list);
	vmdirq->enabled = true;
	raw_spin_unlock_irqrestore(&list_lock, flags);

	data->chip->irq_unmask(data);
पूर्ण

अटल व्योम vmd_irq_disable(काष्ठा irq_data *data)
अणु
	काष्ठा vmd_irq *vmdirq = data->chip_data;
	अचिन्हित दीर्घ flags;

	data->chip->irq_mask(data);

	raw_spin_lock_irqsave(&list_lock, flags);
	अगर (vmdirq->enabled) अणु
		list_del_rcu(&vmdirq->node);
		vmdirq->enabled = false;
	पूर्ण
	raw_spin_unlock_irqrestore(&list_lock, flags);
पूर्ण

/*
 * XXX: Stubbed until we develop acceptable way to not create conflicts with
 * other devices sharing the same vector.
 */
अटल पूर्णांक vmd_irq_set_affinity(काष्ठा irq_data *data,
				स्थिर काष्ठा cpumask *dest, bool क्रमce)
अणु
	वापस -EINVAL;
पूर्ण

अटल काष्ठा irq_chip vmd_msi_controller = अणु
	.name			= "VMD-MSI",
	.irq_enable		= vmd_irq_enable,
	.irq_disable		= vmd_irq_disable,
	.irq_compose_msi_msg	= vmd_compose_msi_msg,
	.irq_set_affinity	= vmd_irq_set_affinity,
पूर्ण;

अटल irq_hw_number_t vmd_get_hwirq(काष्ठा msi_करोमुख्य_info *info,
				     msi_alloc_info_t *arg)
अणु
	वापस 0;
पूर्ण

/*
 * XXX: We can be even smarter selecting the best IRQ once we solve the
 * affinity problem.
 */
अटल काष्ठा vmd_irq_list *vmd_next_irq(काष्ठा vmd_dev *vmd, काष्ठा msi_desc *desc)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i, best;

	अगर (vmd->msix_count == 1 + vmd->first_vec)
		वापस &vmd->irqs[vmd->first_vec];

	/*
	 * White list क्रम fast-पूर्णांकerrupt handlers. All others will share the
	 * "slow" पूर्णांकerrupt vector.
	 */
	चयन (msi_desc_to_pci_dev(desc)->class) अणु
	हाल PCI_CLASS_STORAGE_EXPRESS:
		अवरोध;
	शेष:
		वापस &vmd->irqs[vmd->first_vec];
	पूर्ण

	raw_spin_lock_irqsave(&list_lock, flags);
	best = vmd->first_vec + 1;
	क्रम (i = best; i < vmd->msix_count; i++)
		अगर (vmd->irqs[i].count < vmd->irqs[best].count)
			best = i;
	vmd->irqs[best].count++;
	raw_spin_unlock_irqrestore(&list_lock, flags);

	वापस &vmd->irqs[best];
पूर्ण

अटल पूर्णांक vmd_msi_init(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा msi_करोमुख्य_info *info,
			अचिन्हित पूर्णांक virq, irq_hw_number_t hwirq,
			msi_alloc_info_t *arg)
अणु
	काष्ठा msi_desc *desc = arg->desc;
	काष्ठा vmd_dev *vmd = vmd_from_bus(msi_desc_to_pci_dev(desc)->bus);
	काष्ठा vmd_irq *vmdirq = kzalloc(माप(*vmdirq), GFP_KERNEL);
	अचिन्हित पूर्णांक index, vector;

	अगर (!vmdirq)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&vmdirq->node);
	vmdirq->irq = vmd_next_irq(vmd, desc);
	vmdirq->virq = virq;
	index = index_from_irqs(vmd, vmdirq->irq);
	vector = pci_irq_vector(vmd->dev, index);

	irq_करोमुख्य_set_info(करोमुख्य, virq, vector, info->chip, vmdirq,
			    handle_untracked_irq, vmd, शून्य);
	वापस 0;
पूर्ण

अटल व्योम vmd_msi_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
			काष्ठा msi_करोमुख्य_info *info, अचिन्हित पूर्णांक virq)
अणु
	काष्ठा vmd_irq *vmdirq = irq_get_chip_data(virq);
	अचिन्हित दीर्घ flags;

	synchronize_srcu(&vmdirq->irq->srcu);

	/* XXX: Potential optimization to rebalance */
	raw_spin_lock_irqsave(&list_lock, flags);
	vmdirq->irq->count--;
	raw_spin_unlock_irqrestore(&list_lock, flags);

	kमुक्त(vmdirq);
पूर्ण

अटल पूर्णांक vmd_msi_prepare(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा device *dev,
			   पूर्णांक nvec, msi_alloc_info_t *arg)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा vmd_dev *vmd = vmd_from_bus(pdev->bus);

	अगर (nvec > vmd->msix_count)
		वापस vmd->msix_count;

	स_रखो(arg, 0, माप(*arg));
	वापस 0;
पूर्ण

अटल व्योम vmd_set_desc(msi_alloc_info_t *arg, काष्ठा msi_desc *desc)
अणु
	arg->desc = desc;
पूर्ण

अटल काष्ठा msi_करोमुख्य_ops vmd_msi_करोमुख्य_ops = अणु
	.get_hwirq	= vmd_get_hwirq,
	.msi_init	= vmd_msi_init,
	.msi_मुक्त	= vmd_msi_मुक्त,
	.msi_prepare	= vmd_msi_prepare,
	.set_desc	= vmd_set_desc,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info vmd_msi_करोमुख्य_info = अणु
	.flags		= MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
			  MSI_FLAG_PCI_MSIX,
	.ops		= &vmd_msi_करोमुख्य_ops,
	.chip		= &vmd_msi_controller,
पूर्ण;

अटल व्योम vmd_set_msi_remapping(काष्ठा vmd_dev *vmd, bool enable)
अणु
	u16 reg;

	pci_पढ़ो_config_word(vmd->dev, PCI_REG_VMCONFIG, &reg);
	reg = enable ? (reg & ~VMCONFIG_MSI_REMAP) :
		       (reg | VMCONFIG_MSI_REMAP);
	pci_ग_लिखो_config_word(vmd->dev, PCI_REG_VMCONFIG, reg);
पूर्ण

अटल पूर्णांक vmd_create_irq_करोमुख्य(काष्ठा vmd_dev *vmd)
अणु
	काष्ठा fwnode_handle *fn;

	fn = irq_करोमुख्य_alloc_named_id_fwnode("VMD-MSI", vmd->sysdata.करोमुख्य);
	अगर (!fn)
		वापस -ENODEV;

	vmd->irq_करोमुख्य = pci_msi_create_irq_करोमुख्य(fn, &vmd_msi_करोमुख्य_info, शून्य);
	अगर (!vmd->irq_करोमुख्य) अणु
		irq_करोमुख्य_मुक्त_fwnode(fn);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vmd_हटाओ_irq_करोमुख्य(काष्ठा vmd_dev *vmd)
अणु
	/*
	 * Some production BIOS won't enable remapping between soft reboots.
	 * Ensure remapping is restored beक्रमe unloading the driver.
	 */
	अगर (!vmd->msix_count)
		vmd_set_msi_remapping(vmd, true);

	अगर (vmd->irq_करोमुख्य) अणु
		काष्ठा fwnode_handle *fn = vmd->irq_करोमुख्य->fwnode;

		irq_करोमुख्य_हटाओ(vmd->irq_करोमुख्य);
		irq_करोमुख्य_मुक्त_fwnode(fn);
	पूर्ण
पूर्ण

अटल व्योम __iomem *vmd_cfg_addr(काष्ठा vmd_dev *vmd, काष्ठा pci_bus *bus,
				  अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len)
अणु
	अचिन्हित पूर्णांक busnr_ecam = bus->number - vmd->busn_start;
	u32 offset = PCIE_ECAM_OFFSET(busnr_ecam, devfn, reg);

	अगर (offset + len >= resource_size(&vmd->dev->resource[VMD_CFGBAR]))
		वापस शून्य;

	वापस vmd->cfgbar + offset;
पूर्ण

/*
 * CPU may deadlock अगर config space is not serialized on some versions of this
 * hardware, so all config space access is करोne under a spinlock.
 */
अटल पूर्णांक vmd_pci_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक reg,
			पूर्णांक len, u32 *value)
अणु
	काष्ठा vmd_dev *vmd = vmd_from_bus(bus);
	व्योम __iomem *addr = vmd_cfg_addr(vmd, bus, devfn, reg, len);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!addr)
		वापस -EFAULT;

	spin_lock_irqsave(&vmd->cfg_lock, flags);
	चयन (len) अणु
	हाल 1:
		*value = पढ़ोb(addr);
		अवरोध;
	हाल 2:
		*value = पढ़ोw(addr);
		अवरोध;
	हाल 4:
		*value = पढ़ोl(addr);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&vmd->cfg_lock, flags);
	वापस ret;
पूर्ण

/*
 * VMD h/w converts non-posted config ग_लिखोs to posted memory ग_लिखोs. The
 * पढ़ो-back in this function क्रमces the completion so it वापसs only after
 * the config space was written, as expected.
 */
अटल पूर्णांक vmd_pci_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक reg,
			 पूर्णांक len, u32 value)
अणु
	काष्ठा vmd_dev *vmd = vmd_from_bus(bus);
	व्योम __iomem *addr = vmd_cfg_addr(vmd, bus, devfn, reg, len);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!addr)
		वापस -EFAULT;

	spin_lock_irqsave(&vmd->cfg_lock, flags);
	चयन (len) अणु
	हाल 1:
		ग_लिखोb(value, addr);
		पढ़ोb(addr);
		अवरोध;
	हाल 2:
		ग_लिखोw(value, addr);
		पढ़ोw(addr);
		अवरोध;
	हाल 4:
		ग_लिखोl(value, addr);
		पढ़ोl(addr);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&vmd->cfg_lock, flags);
	वापस ret;
पूर्ण

अटल काष्ठा pci_ops vmd_ops = अणु
	.पढ़ो		= vmd_pci_पढ़ो,
	.ग_लिखो		= vmd_pci_ग_लिखो,
पूर्ण;

अटल व्योम vmd_attach_resources(काष्ठा vmd_dev *vmd)
अणु
	vmd->dev->resource[VMD_MEMBAR1].child = &vmd->resources[1];
	vmd->dev->resource[VMD_MEMBAR2].child = &vmd->resources[2];
पूर्ण

अटल व्योम vmd_detach_resources(काष्ठा vmd_dev *vmd)
अणु
	vmd->dev->resource[VMD_MEMBAR1].child = शून्य;
	vmd->dev->resource[VMD_MEMBAR2].child = शून्य;
पूर्ण

/*
 * VMD करोमुख्यs start at 0x10000 to not clash with ACPI _SEG करोमुख्यs.
 * Per ACPI r6.0, sec 6.5.6,  _SEG वापसs an पूर्णांकeger, of which the lower
 * 16 bits are the PCI Segment Group (करोमुख्य) number.  Other bits are
 * currently reserved.
 */
अटल पूर्णांक vmd_find_मुक्त_करोमुख्य(व्योम)
अणु
	पूर्णांक करोमुख्य = 0xffff;
	काष्ठा pci_bus *bus = शून्य;

	जबतक ((bus = pci_find_next_bus(bus)) != शून्य)
		करोमुख्य = max_t(पूर्णांक, करोमुख्य, pci_करोमुख्य_nr(bus));
	वापस करोमुख्य + 1;
पूर्ण

अटल पूर्णांक vmd_get_phys_offsets(काष्ठा vmd_dev *vmd, bool native_hपूर्णांक,
				resource_माप_प्रकार *offset1,
				resource_माप_प्रकार *offset2)
अणु
	काष्ठा pci_dev *dev = vmd->dev;
	u64 phys1, phys2;

	अगर (native_hपूर्णांक) अणु
		u32 vmlock;
		पूर्णांक ret;

		ret = pci_पढ़ो_config_dword(dev, PCI_REG_VMLOCK, &vmlock);
		अगर (ret || vmlock == ~0)
			वापस -ENODEV;

		अगर (MB2_SHADOW_EN(vmlock)) अणु
			व्योम __iomem *membar2;

			membar2 = pci_iomap(dev, VMD_MEMBAR2, 0);
			अगर (!membar2)
				वापस -ENOMEM;
			phys1 = पढ़ोq(membar2 + MB2_SHADOW_OFFSET);
			phys2 = पढ़ोq(membar2 + MB2_SHADOW_OFFSET + 8);
			pci_iounmap(dev, membar2);
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण अन्यथा अणु
		/* Hypervisor-Emulated Venकरोr-Specअगरic Capability */
		पूर्णांक pos = pci_find_capability(dev, PCI_CAP_ID_VNDR);
		u32 reg, regu;

		pci_पढ़ो_config_dword(dev, pos + 4, &reg);

		/* "SHDW" */
		अगर (pos && reg == 0x53484457) अणु
			pci_पढ़ो_config_dword(dev, pos + 8, &reg);
			pci_पढ़ो_config_dword(dev, pos + 12, &regu);
			phys1 = (u64) regu << 32 | reg;

			pci_पढ़ो_config_dword(dev, pos + 16, &reg);
			pci_पढ़ो_config_dword(dev, pos + 20, &regu);
			phys2 = (u64) regu << 32 | reg;
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण

	*offset1 = dev->resource[VMD_MEMBAR1].start -
			(phys1 & PCI_BASE_ADDRESS_MEM_MASK);
	*offset2 = dev->resource[VMD_MEMBAR2].start -
			(phys2 & PCI_BASE_ADDRESS_MEM_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक vmd_get_bus_number_start(काष्ठा vmd_dev *vmd)
अणु
	काष्ठा pci_dev *dev = vmd->dev;
	u16 reg;

	pci_पढ़ो_config_word(dev, PCI_REG_VMCAP, &reg);
	अगर (BUS_RESTRICT_CAP(reg)) अणु
		pci_पढ़ो_config_word(dev, PCI_REG_VMCONFIG, &reg);

		चयन (BUS_RESTRICT_CFG(reg)) अणु
		हाल 0:
			vmd->busn_start = 0;
			अवरोध;
		हाल 1:
			vmd->busn_start = 128;
			अवरोध;
		हाल 2:
			vmd->busn_start = 224;
			अवरोध;
		शेष:
			pci_err(dev, "Unknown Bus Offset Setting (%d)\n",
				BUS_RESTRICT_CFG(reg));
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t vmd_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा vmd_irq_list *irqs = data;
	काष्ठा vmd_irq *vmdirq;
	पूर्णांक idx;

	idx = srcu_पढ़ो_lock(&irqs->srcu);
	list_क्रम_each_entry_rcu(vmdirq, &irqs->irq_list, node)
		generic_handle_irq(vmdirq->virq);
	srcu_पढ़ो_unlock(&irqs->srcu, idx);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक vmd_alloc_irqs(काष्ठा vmd_dev *vmd)
अणु
	काष्ठा pci_dev *dev = vmd->dev;
	पूर्णांक i, err;

	vmd->msix_count = pci_msix_vec_count(dev);
	अगर (vmd->msix_count < 0)
		वापस -ENODEV;

	vmd->msix_count = pci_alloc_irq_vectors(dev, vmd->first_vec + 1,
						vmd->msix_count, PCI_IRQ_MSIX);
	अगर (vmd->msix_count < 0)
		वापस vmd->msix_count;

	vmd->irqs = devm_kसुस्मृति(&dev->dev, vmd->msix_count, माप(*vmd->irqs),
				 GFP_KERNEL);
	अगर (!vmd->irqs)
		वापस -ENOMEM;

	क्रम (i = 0; i < vmd->msix_count; i++) अणु
		err = init_srcu_काष्ठा(&vmd->irqs[i].srcu);
		अगर (err)
			वापस err;

		INIT_LIST_HEAD(&vmd->irqs[i].irq_list);
		err = devm_request_irq(&dev->dev, pci_irq_vector(dev, i),
				       vmd_irq, IRQF_NO_THREAD,
				       "vmd", &vmd->irqs[i]);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vmd_enable_करोमुख्य(काष्ठा vmd_dev *vmd, अचिन्हित दीर्घ features)
अणु
	काष्ठा pci_sysdata *sd = &vmd->sysdata;
	काष्ठा resource *res;
	u32 upper_bits;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(resources);
	resource_माप_प्रकार offset[2] = अणु0पूर्ण;
	resource_माप_प्रकार membar2_offset = 0x2000;
	काष्ठा pci_bus *child;
	पूर्णांक ret;

	/*
	 * Shaकरोw रेजिस्टरs may exist in certain VMD device ids which allow
	 * guests to correctly assign host physical addresses to the root ports
	 * and child devices. These रेजिस्टरs will either वापस the host value
	 * or 0, depending on an enable bit in the VMD device.
	 */
	अगर (features & VMD_FEAT_HAS_MEMBAR_SHADOW) अणु
		membar2_offset = MB2_SHADOW_OFFSET + MB2_SHADOW_SIZE;
		ret = vmd_get_phys_offsets(vmd, true, &offset[0], &offset[1]);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (features & VMD_FEAT_HAS_MEMBAR_SHADOW_VSCAP) अणु
		ret = vmd_get_phys_offsets(vmd, false, &offset[0], &offset[1]);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * Certain VMD devices may have a root port configuration option which
	 * limits the bus range to between 0-127, 128-255, or 224-255
	 */
	अगर (features & VMD_FEAT_HAS_BUS_RESTRICTIONS) अणु
		ret = vmd_get_bus_number_start(vmd);
		अगर (ret)
			वापस ret;
	पूर्ण

	res = &vmd->dev->resource[VMD_CFGBAR];
	vmd->resources[0] = (काष्ठा resource) अणु
		.name  = "VMD CFGBAR",
		.start = vmd->busn_start,
		.end   = vmd->busn_start + (resource_size(res) >> 20) - 1,
		.flags = IORESOURCE_BUS | IORESOURCE_PCI_FIXED,
	पूर्ण;

	/*
	 * If the winकरोw is below 4GB, clear IORESOURCE_MEM_64 so we can
	 * put 32-bit resources in the winकरोw.
	 *
	 * There's no hardware reason why a 64-bit window *couldn't*
	 * contain a 32-bit resource, but pbus_size_mem() computes the
	 * bridge winकरोw size assuming a 64-bit winकरोw will contain no
	 * 32-bit resources.  __pci_assign_resource() enक्रमces that
	 * artअगरicial restriction to make sure everything will fit.
	 *
	 * The only way we could use a 64-bit non-prefetchable MEMBAR is
	 * अगर its address is <4GB so that we can convert it to a 32-bit
	 * resource.  To be visible to the host OS, all VMD endpoपूर्णांकs must
	 * be initially configured by platक्रमm BIOS, which includes setting
	 * up these resources.  We can assume the device is configured
	 * according to the platक्रमm needs.
	 */
	res = &vmd->dev->resource[VMD_MEMBAR1];
	upper_bits = upper_32_bits(res->end);
	flags = res->flags & ~IORESOURCE_SIZEALIGN;
	अगर (!upper_bits)
		flags &= ~IORESOURCE_MEM_64;
	vmd->resources[1] = (काष्ठा resource) अणु
		.name  = "VMD MEMBAR1",
		.start = res->start,
		.end   = res->end,
		.flags = flags,
		.parent = res,
	पूर्ण;

	res = &vmd->dev->resource[VMD_MEMBAR2];
	upper_bits = upper_32_bits(res->end);
	flags = res->flags & ~IORESOURCE_SIZEALIGN;
	अगर (!upper_bits)
		flags &= ~IORESOURCE_MEM_64;
	vmd->resources[2] = (काष्ठा resource) अणु
		.name  = "VMD MEMBAR2",
		.start = res->start + membar2_offset,
		.end   = res->end,
		.flags = flags,
		.parent = res,
	पूर्ण;

	sd->vmd_dev = vmd->dev;
	sd->करोमुख्य = vmd_find_मुक्त_करोमुख्य();
	अगर (sd->करोमुख्य < 0)
		वापस sd->करोमुख्य;

	sd->node = pcibus_to_node(vmd->dev->bus);

	/*
	 * Currently MSI remapping must be enabled in guest passthrough mode
	 * due to some missing पूर्णांकerrupt remapping plumbing. This is probably
	 * acceptable because the guest is usually CPU-limited and MSI
	 * remapping करोesn't become a perक्रमmance bottleneck.
	 */
	अगर (!(features & VMD_FEAT_CAN_BYPASS_MSI_REMAP) ||
	    offset[0] || offset[1]) अणु
		ret = vmd_alloc_irqs(vmd);
		अगर (ret)
			वापस ret;

		vmd_set_msi_remapping(vmd, true);

		ret = vmd_create_irq_करोमुख्य(vmd);
		अगर (ret)
			वापस ret;

		/*
		 * Override the IRQ करोमुख्य bus token so the करोमुख्य can be
		 * distinguished from a regular PCI/MSI करोमुख्य.
		 */
		irq_करोमुख्य_update_bus_token(vmd->irq_करोमुख्य, DOMAIN_BUS_VMD_MSI);
	पूर्ण अन्यथा अणु
		vmd_set_msi_remapping(vmd, false);
	पूर्ण

	pci_add_resource(&resources, &vmd->resources[0]);
	pci_add_resource_offset(&resources, &vmd->resources[1], offset[0]);
	pci_add_resource_offset(&resources, &vmd->resources[2], offset[1]);

	vmd->bus = pci_create_root_bus(&vmd->dev->dev, vmd->busn_start,
				       &vmd_ops, sd, &resources);
	अगर (!vmd->bus) अणु
		pci_मुक्त_resource_list(&resources);
		vmd_हटाओ_irq_करोमुख्य(vmd);
		वापस -ENODEV;
	पूर्ण

	vmd_attach_resources(vmd);
	अगर (vmd->irq_करोमुख्य)
		dev_set_msi_करोमुख्य(&vmd->bus->dev, vmd->irq_करोमुख्य);

	pci_scan_child_bus(vmd->bus);
	pci_assign_unasचिन्हित_bus_resources(vmd->bus);

	/*
	 * VMD root buses are भव and करोn't वापस true on pci_is_pcie()
	 * and will fail pcie_bus_configure_settings() early. It can instead be
	 * run on each of the real root ports.
	 */
	list_क्रम_each_entry(child, &vmd->bus->children, node)
		pcie_bus_configure_settings(child);

	pci_bus_add_devices(vmd->bus);

	WARN(sysfs_create_link(&vmd->dev->dev.kobj, &vmd->bus->dev.kobj,
			       "domain"), "Can't create symlink to domain\n");
	वापस 0;
पूर्ण

अटल पूर्णांक vmd_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	अचिन्हित दीर्घ features = (अचिन्हित दीर्घ) id->driver_data;
	काष्ठा vmd_dev *vmd;
	पूर्णांक err;

	अगर (resource_size(&dev->resource[VMD_CFGBAR]) < (1 << 20))
		वापस -ENOMEM;

	vmd = devm_kzalloc(&dev->dev, माप(*vmd), GFP_KERNEL);
	अगर (!vmd)
		वापस -ENOMEM;

	vmd->dev = dev;
	err = pcim_enable_device(dev);
	अगर (err < 0)
		वापस err;

	vmd->cfgbar = pcim_iomap(dev, VMD_CFGBAR, 0);
	अगर (!vmd->cfgbar)
		वापस -ENOMEM;

	pci_set_master(dev);
	अगर (dma_set_mask_and_coherent(&dev->dev, DMA_BIT_MASK(64)) &&
	    dma_set_mask_and_coherent(&dev->dev, DMA_BIT_MASK(32)))
		वापस -ENODEV;

	अगर (features & VMD_FEAT_OFFSET_FIRST_VECTOR)
		vmd->first_vec = 1;

	spin_lock_init(&vmd->cfg_lock);
	pci_set_drvdata(dev, vmd);
	err = vmd_enable_करोमुख्य(vmd, features);
	अगर (err)
		वापस err;

	dev_info(&vmd->dev->dev, "Bound to PCI domain %04x\n",
		 vmd->sysdata.करोमुख्य);
	वापस 0;
पूर्ण

अटल व्योम vmd_cleanup_srcu(काष्ठा vmd_dev *vmd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < vmd->msix_count; i++)
		cleanup_srcu_काष्ठा(&vmd->irqs[i].srcu);
पूर्ण

अटल व्योम vmd_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा vmd_dev *vmd = pci_get_drvdata(dev);

	sysfs_हटाओ_link(&vmd->dev->dev.kobj, "domain");
	pci_stop_root_bus(vmd->bus);
	pci_हटाओ_root_bus(vmd->bus);
	vmd_cleanup_srcu(vmd);
	vmd_detach_resources(vmd);
	vmd_हटाओ_irq_करोमुख्य(vmd);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक vmd_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा vmd_dev *vmd = pci_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < vmd->msix_count; i++)
		devm_मुक्त_irq(dev, pci_irq_vector(pdev, i), &vmd->irqs[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक vmd_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा vmd_dev *vmd = pci_get_drvdata(pdev);
	पूर्णांक err, i;

	क्रम (i = 0; i < vmd->msix_count; i++) अणु
		err = devm_request_irq(dev, pci_irq_vector(pdev, i),
				       vmd_irq, IRQF_NO_THREAD,
				       "vmd", &vmd->irqs[i]);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर
अटल SIMPLE_DEV_PM_OPS(vmd_dev_pm_ops, vmd_suspend, vmd_resume);

अटल स्थिर काष्ठा pci_device_id vmd_ids[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_VMD_201D),
		.driver_data = VMD_FEAT_HAS_MEMBAR_SHADOW_VSCAP,पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_VMD_28C0),
		.driver_data = VMD_FEAT_HAS_MEMBAR_SHADOW |
				VMD_FEAT_HAS_BUS_RESTRICTIONS |
				VMD_FEAT_CAN_BYPASS_MSI_REMAP,पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x467f),
		.driver_data = VMD_FEAT_HAS_MEMBAR_SHADOW_VSCAP |
				VMD_FEAT_HAS_BUS_RESTRICTIONS |
				VMD_FEAT_OFFSET_FIRST_VECTOR,पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x4c3d),
		.driver_data = VMD_FEAT_HAS_MEMBAR_SHADOW_VSCAP |
				VMD_FEAT_HAS_BUS_RESTRICTIONS |
				VMD_FEAT_OFFSET_FIRST_VECTOR,पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_VMD_9A0B),
		.driver_data = VMD_FEAT_HAS_MEMBAR_SHADOW_VSCAP |
				VMD_FEAT_HAS_BUS_RESTRICTIONS |
				VMD_FEAT_OFFSET_FIRST_VECTOR,पूर्ण,
	अणु0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, vmd_ids);

अटल काष्ठा pci_driver vmd_drv = अणु
	.name		= "vmd",
	.id_table	= vmd_ids,
	.probe		= vmd_probe,
	.हटाओ		= vmd_हटाओ,
	.driver		= अणु
		.pm	= &vmd_dev_pm_ops,
	पूर्ण,
पूर्ण;
module_pci_driver(vmd_drv);

MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
MODULE_VERSION("0.6");
