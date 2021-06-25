<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2010 John Crispin <john@phrozen.org>
 */

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <lantiq_soc.h>

#समावेश "pci-lantiq.h"

#घोषणा LTQ_PCI_CFG_BUSNUM_SHF 16
#घोषणा LTQ_PCI_CFG_DEVNUM_SHF 11
#घोषणा LTQ_PCI_CFG_FUNNUM_SHF 8

#घोषणा PCI_ACCESS_READ	 0
#घोषणा PCI_ACCESS_WRITE 1

अटल पूर्णांक ltq_pci_config_access(अचिन्हित अक्षर access_type, काष्ठा pci_bus *bus,
	अचिन्हित पूर्णांक devfn, अचिन्हित पूर्णांक where, u32 *data)
अणु
	अचिन्हित दीर्घ cfg_base;
	अचिन्हित दीर्घ flags;
	u32 temp;

	/* we support slot from 0 to 15 dev_fn & 0x68 (AD29) is the
	   SoC itself */
	अगर ((bus->number != 0) || ((devfn & 0xf8) > 0x78)
		|| ((devfn & 0xf8) == 0) || ((devfn & 0xf8) == 0x68))
		वापस 1;

	spin_lock_irqsave(&ebu_lock, flags);

	cfg_base = (अचिन्हित दीर्घ) ltq_pci_mapped_cfg;
	cfg_base |= (bus->number << LTQ_PCI_CFG_BUSNUM_SHF) | (devfn <<
			LTQ_PCI_CFG_FUNNUM_SHF) | (where & ~0x3);

	/* Perक्रमm access */
	अगर (access_type == PCI_ACCESS_WRITE) अणु
		ltq_w32(swab32(*data), ((u32 *)cfg_base));
	पूर्ण अन्यथा अणु
		*data = ltq_r32(((u32 *)(cfg_base)));
		*data = swab32(*data);
	पूर्ण
	wmb();

	/* clean possible Master पात */
	cfg_base = (अचिन्हित दीर्घ) ltq_pci_mapped_cfg;
	cfg_base |= (0x0 << LTQ_PCI_CFG_FUNNUM_SHF) + 4;
	temp = ltq_r32(((u32 *)(cfg_base)));
	temp = swab32(temp);
	cfg_base = (अचिन्हित दीर्घ) ltq_pci_mapped_cfg;
	cfg_base |= (0x68 << LTQ_PCI_CFG_FUNNUM_SHF) + 4;
	ltq_w32(temp, ((u32 *)cfg_base));

	spin_unlock_irqrestore(&ebu_lock, flags);

	अगर (((*data) == 0xffffffff) && (access_type == PCI_ACCESS_READ))
		वापस 1;

	वापस 0;
पूर्ण

पूर्णांक ltq_pci_पढ़ो_config_dword(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
	पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	u32 data = 0;

	अगर (ltq_pci_config_access(PCI_ACCESS_READ, bus, devfn, where, &data))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (size == 1)
		*val = (data >> ((where & 3) << 3)) & 0xff;
	अन्यथा अगर (size == 2)
		*val = (data >> ((where & 3) << 3)) & 0xffff;
	अन्यथा
		*val = data;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

पूर्णांक ltq_pci_ग_लिखो_config_dword(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
	पूर्णांक where, पूर्णांक size, u32 val)
अणु
	u32 data = 0;

	अगर (size == 4) अणु
		data = val;
	पूर्ण अन्यथा अणु
		अगर (ltq_pci_config_access(PCI_ACCESS_READ, bus,
				devfn, where, &data))
			वापस PCIBIOS_DEVICE_NOT_FOUND;

		अगर (size == 1)
			data = (data & ~(0xff << ((where & 3) << 3))) |
				(val << ((where & 3) << 3));
		अन्यथा अगर (size == 2)
			data = (data & ~(0xffff << ((where & 3) << 3))) |
				(val << ((where & 3) << 3));
	पूर्ण

	अगर (ltq_pci_config_access(PCI_ACCESS_WRITE, bus, devfn, where, &data))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण
