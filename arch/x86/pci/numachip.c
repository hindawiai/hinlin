<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Numascale NumaConnect-specअगरic PCI code
 *
 * Copyright (C) 2012 Numascale AS. All rights reserved.
 *
 * Send feedback to <support@numascale.com>
 *
 * PCI accessor functions derived from mmconfig_64.c
 *
 */

#समावेश <linux/pci.h>
#समावेश <यंत्र/pci_x86.h>

अटल u8 limit __पढ़ो_mostly;

अटल अंतरभूत अक्षर __iomem *pci_dev_base(अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक devfn)
अणु
	काष्ठा pci_mmcfg_region *cfg = pci_mmconfig_lookup(seg, bus);

	अगर (cfg && cfg->virt)
		वापस cfg->virt + (PCI_MMCFG_BUS_OFFSET(bus) | (devfn << 12));
	वापस शून्य;
पूर्ण

अटल पूर्णांक pci_mmcfg_पढ़ो_numachip(अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक bus,
			  अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len, u32 *value)
अणु
	अक्षर __iomem *addr;

	/* Why करो we have this when nobody checks it. How about a BUG()!? -AK */
	अगर (unlikely((bus > 255) || (devfn > 255) || (reg > 4095))) अणु
err:		*value = -1;
		वापस -EINVAL;
	पूर्ण

	/* Ensure AMD Northbridges करोn't decode पढ़ोs to other devices */
	अगर (unlikely(bus == 0 && devfn >= limit)) अणु
		*value = -1;
		वापस 0;
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

अटल पूर्णांक pci_mmcfg_ग_लिखो_numachip(अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक bus,
			   अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len, u32 value)
अणु
	अक्षर __iomem *addr;

	/* Why करो we have this when nobody checks it. How about a BUG()!? -AK */
	अगर (unlikely((bus > 255) || (devfn > 255) || (reg > 4095)))
		वापस -EINVAL;

	/* Ensure AMD Northbridges करोn't decode ग_लिखोs to other devices */
	अगर (unlikely(bus == 0 && devfn >= limit))
		वापस 0;

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

अटल स्थिर काष्ठा pci_raw_ops pci_mmcfg_numachip = अणु
	.पढ़ो = pci_mmcfg_पढ़ो_numachip,
	.ग_लिखो = pci_mmcfg_ग_लिखो_numachip,
पूर्ण;

पूर्णांक __init pci_numachip_init(व्योम)
अणु
	पूर्णांक ret = 0;
	u32 val;

	/* For remote I/O, restrict bus 0 access to the actual number of AMD
	   Northbridges, which starts at device number 0x18 */
	ret = raw_pci_पढ़ो(0, 0, PCI_DEVFN(0x18, 0), 0x60, माप(val), &val);
	अगर (ret)
		जाओ out;

	/* HyperTransport fabric size in bits 6:4 */
	limit = PCI_DEVFN(0x18 + ((val >> 4) & 7) + 1, 0);

	/* Use NumaChip PCI accessors क्रम non-extended and extended access */
	raw_pci_ops = raw_pci_ext_ops = &pci_mmcfg_numachip;
out:
	वापस ret;
पूर्ण
