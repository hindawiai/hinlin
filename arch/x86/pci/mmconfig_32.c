<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004 Matthew Wilcox <matthew@wil.cx>
 * Copyright (C) 2004 Intel Corp.
 */

/*
 * mmconfig.c - Low-level direct PCI config space access via MMCONFIG
 */

#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/rcupdate.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/pci_x86.h>

/* Assume प्रणालीs with more busses have correct MCFG */
#घोषणा mmcfg_virt_addr ((व्योम __iomem *) fix_to_virt(FIX_PCIE_MCFG))

/* The base address of the last MMCONFIG device accessed */
अटल u32 mmcfg_last_accessed_device;
अटल पूर्णांक mmcfg_last_accessed_cpu;

/*
 * Functions क्रम accessing PCI configuration space with MMCONFIG accesses
 */
अटल u32 get_base_addr(अचिन्हित पूर्णांक seg, पूर्णांक bus, अचिन्हित devfn)
अणु
	काष्ठा pci_mmcfg_region *cfg = pci_mmconfig_lookup(seg, bus);

	अगर (cfg)
		वापस cfg->address;
	वापस 0;
पूर्ण

/*
 * This is always called under pci_config_lock
 */
अटल व्योम pci_exp_set_dev_base(अचिन्हित पूर्णांक base, पूर्णांक bus, पूर्णांक devfn)
अणु
	u32 dev_base = base | PCI_MMCFG_BUS_OFFSET(bus) | (devfn << 12);
	पूर्णांक cpu = smp_processor_id();
	अगर (dev_base != mmcfg_last_accessed_device ||
	    cpu != mmcfg_last_accessed_cpu) अणु
		mmcfg_last_accessed_device = dev_base;
		mmcfg_last_accessed_cpu = cpu;
		set_fixmap_nocache(FIX_PCIE_MCFG, dev_base);
	पूर्ण
पूर्ण

अटल पूर्णांक pci_mmcfg_पढ़ो(अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक bus,
			  अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len, u32 *value)
अणु
	अचिन्हित दीर्घ flags;
	u32 base;

	अगर ((bus > 255) || (devfn > 255) || (reg > 4095)) अणु
err:		*value = -1;
		वापस -EINVAL;
	पूर्ण

	rcu_पढ़ो_lock();
	base = get_base_addr(seg, bus, devfn);
	अगर (!base) अणु
		rcu_पढ़ो_unlock();
		जाओ err;
	पूर्ण

	raw_spin_lock_irqsave(&pci_config_lock, flags);

	pci_exp_set_dev_base(base, bus, devfn);

	चयन (len) अणु
	हाल 1:
		*value = mmio_config_पढ़ोb(mmcfg_virt_addr + reg);
		अवरोध;
	हाल 2:
		*value = mmio_config_पढ़ोw(mmcfg_virt_addr + reg);
		अवरोध;
	हाल 4:
		*value = mmio_config_पढ़ोl(mmcfg_virt_addr + reg);
		अवरोध;
	पूर्ण
	raw_spin_unlock_irqrestore(&pci_config_lock, flags);
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक pci_mmcfg_ग_लिखो(अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक bus,
			   अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 base;

	अगर ((bus > 255) || (devfn > 255) || (reg > 4095))
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	base = get_base_addr(seg, bus, devfn);
	अगर (!base) अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण

	raw_spin_lock_irqsave(&pci_config_lock, flags);

	pci_exp_set_dev_base(base, bus, devfn);

	चयन (len) अणु
	हाल 1:
		mmio_config_ग_लिखोb(mmcfg_virt_addr + reg, value);
		अवरोध;
	हाल 2:
		mmio_config_ग_लिखोw(mmcfg_virt_addr + reg, value);
		अवरोध;
	हाल 4:
		mmio_config_ग_लिखोl(mmcfg_virt_addr + reg, value);
		अवरोध;
	पूर्ण
	raw_spin_unlock_irqrestore(&pci_config_lock, flags);
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

स्थिर काष्ठा pci_raw_ops pci_mmcfg = अणु
	.पढ़ो =		pci_mmcfg_पढ़ो,
	.ग_लिखो =	pci_mmcfg_ग_लिखो,
पूर्ण;

पूर्णांक __init pci_mmcfg_arch_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "PCI: Using MMCONFIG for extended config space\n");
	raw_pci_ext_ops = &pci_mmcfg;
	वापस 1;
पूर्ण

व्योम __init pci_mmcfg_arch_मुक्त(व्योम)
अणु
पूर्ण

पूर्णांक pci_mmcfg_arch_map(काष्ठा pci_mmcfg_region *cfg)
अणु
	वापस 0;
पूर्ण

व्योम pci_mmcfg_arch_unmap(काष्ठा pci_mmcfg_region *cfg)
अणु
	अचिन्हित दीर्घ flags;

	/* Invalidate the cached mmcfg map entry. */
	raw_spin_lock_irqsave(&pci_config_lock, flags);
	mmcfg_last_accessed_device = 0;
	raw_spin_unlock_irqrestore(&pci_config_lock, flags);
पूर्ण
