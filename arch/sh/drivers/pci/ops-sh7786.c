<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic SH7786 PCI-Express operations.
 *
 *  Copyright (C) 2009 - 2010  Paul Mundt
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश "pcie-sh7786.h"

क्रमागत अणु
	PCI_ACCESS_READ,
	PCI_ACCESS_WRITE,
पूर्ण;

अटल पूर्णांक sh7786_pcie_config_access(अचिन्हित अक्षर access_type,
		काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where, u32 *data)
अणु
	काष्ठा pci_channel *chan = bus->sysdata;
	पूर्णांक dev, func, type, reg;

	dev = PCI_SLOT(devfn);
	func = PCI_FUNC(devfn);
	type = !!bus->parent;
	reg = where & ~3;

	अगर (bus->number > 255 || dev > 31 || func > 7)
		वापस PCIBIOS_FUNC_NOT_SUPPORTED;

	/*
	 * While each channel has its own memory-mapped extended config
	 * space, it's generally only accessible when in endpoपूर्णांक mode.
	 * When in root complex mode, the controller is unable to target
	 * itself with either type 0 or type 1 accesses, and indeed, any
	 * controller initiated target transfer to its own config space
	 * result in a completer पात.
	 *
	 * Each channel effectively only supports a single device, but as
	 * the same channel <-> device access works क्रम any PCI_SLOT()
	 * value, we cheat a bit here and bind the controller's config
	 * space to devfn 0 in order to enable self-क्रमागतeration. In this
	 * हाल the regular PAR/PDR path is sidelined and the mangled
	 * config access itself is initiated as a SuperHyway transaction.
	 */
	अगर (pci_is_root_bus(bus)) अणु
		अगर (dev == 0) अणु
			अगर (access_type == PCI_ACCESS_READ)
				*data = pci_पढ़ो_reg(chan, PCI_REG(reg));
			अन्यथा
				pci_ग_लिखो_reg(chan, *data, PCI_REG(reg));

			वापस PCIBIOS_SUCCESSFUL;
		पूर्ण अन्यथा अगर (dev > 1)
			वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	/* Clear errors */
	pci_ग_लिखो_reg(chan, pci_पढ़ो_reg(chan, SH4A_PCIEERRFR), SH4A_PCIEERRFR);

	/* Set the PIO address */
	pci_ग_लिखो_reg(chan, (bus->number << 24) | (dev << 19) |
				(func << 16) | reg, SH4A_PCIEPAR);

	/* Enable the configuration access */
	pci_ग_लिखो_reg(chan, (1 << 31) | (type << 8), SH4A_PCIEPCTLR);

	/* Check क्रम errors */
	अगर (pci_पढ़ो_reg(chan, SH4A_PCIEERRFR) & 0x10)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	/* Check क्रम master and target पातs */
	अगर (pci_पढ़ो_reg(chan, SH4A_PCIEPCICONF1) & ((1 << 29) | (1 << 28)))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (access_type == PCI_ACCESS_READ)
		*data = pci_पढ़ो_reg(chan, SH4A_PCIEPDR);
	अन्यथा
		pci_ग_लिखो_reg(chan, *data, SH4A_PCIEPDR);

	/* Disable the configuration access */
	pci_ग_लिखो_reg(chan, 0, SH4A_PCIEPCTLR);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक sh7786_pcie_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			    पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	u32 data;

        अगर ((size == 2) && (where & 1))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	अन्यथा अगर ((size == 4) && (where & 3))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	raw_spin_lock_irqsave(&pci_config_lock, flags);
	ret = sh7786_pcie_config_access(PCI_ACCESS_READ, bus,
					devfn, where, &data);
	अगर (ret != PCIBIOS_SUCCESSFUL) अणु
		*val = 0xffffffff;
		जाओ out;
	पूर्ण

	अगर (size == 1)
		*val = (data >> ((where & 3) << 3)) & 0xff;
	अन्यथा अगर (size == 2)
		*val = (data >> ((where & 2) << 3)) & 0xffff;
	अन्यथा
		*val = data;

	dev_dbg(&bus->dev, "pcie-config-read: bus=%3d devfn=0x%04x "
		"where=0x%04x size=%d val=0x%08lx\n", bus->number,
		devfn, where, size, (अचिन्हित दीर्घ)*val);

out:
	raw_spin_unlock_irqrestore(&pci_config_lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक sh7786_pcie_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			     पूर्णांक where, पूर्णांक size, u32 val)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक shअगरt, ret;
	u32 data;

        अगर ((size == 2) && (where & 1))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	अन्यथा अगर ((size == 4) && (where & 3))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	raw_spin_lock_irqsave(&pci_config_lock, flags);
	ret = sh7786_pcie_config_access(PCI_ACCESS_READ, bus,
					devfn, where, &data);
	अगर (ret != PCIBIOS_SUCCESSFUL)
		जाओ out;

	dev_dbg(&bus->dev, "pcie-config-write: bus=%3d devfn=0x%04x "
		"where=0x%04x size=%d val=%08lx\n", bus->number,
		devfn, where, size, (अचिन्हित दीर्घ)val);

	अगर (size == 1) अणु
		shअगरt = (where & 3) << 3;
		data &= ~(0xff << shअगरt);
		data |= ((val & 0xff) << shअगरt);
	पूर्ण अन्यथा अगर (size == 2) अणु
		shअगरt = (where & 2) << 3;
		data &= ~(0xffff << shअगरt);
		data |= ((val & 0xffff) << shअगरt);
	पूर्ण अन्यथा
		data = val;

	ret = sh7786_pcie_config_access(PCI_ACCESS_WRITE, bus,
					devfn, where, &data);
out:
	raw_spin_unlock_irqrestore(&pci_config_lock, flags);
	वापस ret;
पूर्ण

काष्ठा pci_ops sh7786_pci_ops = अणु
	.पढ़ो	= sh7786_pcie_पढ़ो,
	.ग_लिखो	= sh7786_pcie_ग_लिखो,
पूर्ण;
