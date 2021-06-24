<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mmconfig.c - Low-level direct PCI config space access via MMCONFIG
 *
 * This is an 64bit optimized version that always keeps the full mmconfig
 * space mapped. This allows lockless config space operation.
 */

#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/acpi.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/rcupdate.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/pci_x86.h>

#घोषणा PREFIX "PCI: "

अटल अक्षर __iomem *pci_dev_base(अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक devfn)
अणु
	काष्ठा pci_mmcfg_region *cfg = pci_mmconfig_lookup(seg, bus);

	अगर (cfg && cfg->virt)
		वापस cfg->virt + (PCI_MMCFG_BUS_OFFSET(bus) | (devfn << 12));
	वापस शून्य;
पूर्ण

अटल पूर्णांक pci_mmcfg_पढ़ो(अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक bus,
			  अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len, u32 *value)
अणु
	अक्षर __iomem *addr;

	/* Why करो we have this when nobody checks it. How about a BUG()!? -AK */
	अगर (unlikely((bus > 255) || (devfn > 255) || (reg > 4095))) अणु
err:		*value = -1;
		वापस -EINVAL;
	पूर्ण

	rcu_पढ़ो_lock();
	addr = pci_dev_base(seg, bus, devfn);
	अगर (!addr) अणु
		rcu_पढ़ो_unlock();
		जाओ err;
	पूर्ण

	चयन (len) अणु
	हाल 1:
		*value = mmio_config_पढ़ोb(addr + reg);
		अवरोध;
	हाल 2:
		*value = mmio_config_पढ़ोw(addr + reg);
		अवरोध;
	हाल 4:
		*value = mmio_config_पढ़ोl(addr + reg);
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक pci_mmcfg_ग_लिखो(अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक bus,
			   अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len, u32 value)
अणु
	अक्षर __iomem *addr;

	/* Why करो we have this when nobody checks it. How about a BUG()!? -AK */
	अगर (unlikely((bus > 255) || (devfn > 255) || (reg > 4095)))
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	addr = pci_dev_base(seg, bus, devfn);
	अगर (!addr) अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण

	चयन (len) अणु
	हाल 1:
		mmio_config_ग_लिखोb(addr + reg, value);
		अवरोध;
	हाल 2:
		mmio_config_ग_लिखोw(addr + reg, value);
		अवरोध;
	हाल 4:
		mmio_config_ग_लिखोl(addr + reg, value);
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

स्थिर काष्ठा pci_raw_ops pci_mmcfg = अणु
	.पढ़ो =		pci_mmcfg_पढ़ो,
	.ग_लिखो =	pci_mmcfg_ग_लिखो,
पूर्ण;

अटल व्योम __iomem *mcfg_ioremap(काष्ठा pci_mmcfg_region *cfg)
अणु
	व्योम __iomem *addr;
	u64 start, size;
	पूर्णांक num_buses;

	start = cfg->address + PCI_MMCFG_BUS_OFFSET(cfg->start_bus);
	num_buses = cfg->end_bus - cfg->start_bus + 1;
	size = PCI_MMCFG_BUS_OFFSET(num_buses);
	addr = ioremap(start, size);
	अगर (addr)
		addr -= PCI_MMCFG_BUS_OFFSET(cfg->start_bus);
	वापस addr;
पूर्ण

पूर्णांक __init pci_mmcfg_arch_init(व्योम)
अणु
	काष्ठा pci_mmcfg_region *cfg;

	list_क्रम_each_entry(cfg, &pci_mmcfg_list, list)
		अगर (pci_mmcfg_arch_map(cfg)) अणु
			pci_mmcfg_arch_मुक्त();
			वापस 0;
		पूर्ण

	raw_pci_ext_ops = &pci_mmcfg;

	वापस 1;
पूर्ण

व्योम __init pci_mmcfg_arch_मुक्त(व्योम)
अणु
	काष्ठा pci_mmcfg_region *cfg;

	list_क्रम_each_entry(cfg, &pci_mmcfg_list, list)
		pci_mmcfg_arch_unmap(cfg);
पूर्ण

पूर्णांक pci_mmcfg_arch_map(काष्ठा pci_mmcfg_region *cfg)
अणु
	cfg->virt = mcfg_ioremap(cfg);
	अगर (!cfg->virt) अणु
		pr_err(PREFIX "can't map MMCONFIG at %pR\n", &cfg->res);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम pci_mmcfg_arch_unmap(काष्ठा pci_mmcfg_region *cfg)
अणु
	अगर (cfg && cfg->virt) अणु
		iounmap(cfg->virt + PCI_MMCFG_BUS_OFFSET(cfg->start_bus));
		cfg->virt = शून्य;
	पूर्ण
पूर्ण
