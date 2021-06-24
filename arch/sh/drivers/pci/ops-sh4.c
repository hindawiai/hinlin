<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic SH-4 / SH-4A PCIC operations (SH7751, SH7780).
 *
 * Copyright (C) 2002 - 2009  Paul Mundt
 */
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/addrspace.h>
#समावेश "pci-sh4.h"

/*
 * Direct access to PCI hardware...
 */
#घोषणा CONFIG_CMD(bus, devfn, where) \
	(0x80000000 | (bus->number << 16) | (devfn << 8) | (where & ~3))

/*
 * Functions क्रम accessing PCI configuration space with type 1 accesses
 */
अटल पूर्णांक sh4_pci_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			   पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	काष्ठा pci_channel *chan = bus->sysdata;
	अचिन्हित दीर्घ flags;
	u32 data;

	/*
	 * PCIPDR may only be accessed as 32 bit words,
	 * so we must करो byte alignment by hand
	 */
	raw_spin_lock_irqsave(&pci_config_lock, flags);
	pci_ग_लिखो_reg(chan, CONFIG_CMD(bus, devfn, where), SH4_PCIPAR);
	data = pci_पढ़ो_reg(chan, SH4_PCIPDR);
	raw_spin_unlock_irqrestore(&pci_config_lock, flags);

	चयन (size) अणु
	हाल 1:
		*val = (data >> ((where & 3) << 3)) & 0xff;
		अवरोध;
	हाल 2:
		*val = (data >> ((where & 2) << 3)) & 0xffff;
		अवरोध;
	हाल 4:
		*val = data;
		अवरोध;
	शेष:
		वापस PCIBIOS_FUNC_NOT_SUPPORTED;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

/*
 * Since SH4 only करोes 32bit access we'll have to करो a पढ़ो,
 * mask,ग_लिखो operation.
 * We'll allow an odd byte offset, though it should be illegal.
 */
अटल पूर्णांक sh4_pci_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			 पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा pci_channel *chan = bus->sysdata;
	अचिन्हित दीर्घ flags;
	पूर्णांक shअगरt;
	u32 data;

	raw_spin_lock_irqsave(&pci_config_lock, flags);
	pci_ग_लिखो_reg(chan, CONFIG_CMD(bus, devfn, where), SH4_PCIPAR);
	data = pci_पढ़ो_reg(chan, SH4_PCIPDR);
	raw_spin_unlock_irqrestore(&pci_config_lock, flags);

	चयन (size) अणु
	हाल 1:
		shअगरt = (where & 3) << 3;
		data &= ~(0xff << shअगरt);
		data |= ((val & 0xff) << shअगरt);
		अवरोध;
	हाल 2:
		shअगरt = (where & 2) << 3;
		data &= ~(0xffff << shअगरt);
		data |= ((val & 0xffff) << shअगरt);
		अवरोध;
	हाल 4:
		data = val;
		अवरोध;
	शेष:
		वापस PCIBIOS_FUNC_NOT_SUPPORTED;
	पूर्ण

	pci_ग_लिखो_reg(chan, data, SH4_PCIPDR);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops sh4_pci_ops = अणु
	.पढ़ो		= sh4_pci_पढ़ो,
	.ग_लिखो		= sh4_pci_ग_लिखो,
पूर्ण;

पूर्णांक __attribute__((weak)) pci_fixup_pcic(काष्ठा pci_channel *chan)
अणु
	/* Nothing to करो. */
	वापस 0;
पूर्ण
