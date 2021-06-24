<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 1999, 2000, 2004  MIPS Technologies, Inc.
 *	All rights reserved.
 *	Authors: Carsten Langgaard <carstenl@mips.com>
 *		 Maciej W. Rozycki <macro@mips.com>
 *
 * MIPS boards specअगरic PCI support.
 */
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>

#समावेश <यंत्र/mips-boards/bonito64.h>

#घोषणा PCI_ACCESS_READ	 0
#घोषणा PCI_ACCESS_WRITE 1

#घोषणा CFG_SPACE_REG(offset) (व्योम *)CKSEG1ADDR(_pcictrl_bonito_pcicfg + (offset))
#घोषणा ID_SEL_BEGIN 10
#घोषणा MAX_DEV_NUM (31 - ID_SEL_BEGIN)


अटल पूर्णांक bonito64_pcibios_config_access(अचिन्हित अक्षर access_type,
				      काष्ठा pci_bus *bus,
				      अचिन्हित पूर्णांक devfn, पूर्णांक where,
				      u32 * data)
अणु
	u32 busnum = bus->number;
	u32 addr, type;
	u32 dummy;
	व्योम *addrp;
	पूर्णांक device = PCI_SLOT(devfn);
	पूर्णांक function = PCI_FUNC(devfn);
	पूर्णांक reg = where & ~3;

	अगर (busnum == 0) अणु
		/* Type 0 configuration क्रम onboard PCI bus */
		अगर (device > MAX_DEV_NUM)
			वापस -1;

		addr = (1 << (device + ID_SEL_BEGIN)) | (function << 8) | reg;
		type = 0;
	पूर्ण अन्यथा अणु
		/* Type 1 configuration क्रम offboard PCI bus */
		addr = (busnum << 16) | (device << 11) | (function << 8) | reg;
		type = 0x10000;
	पूर्ण

	/* Clear पातs */
	BONITO_PCICMD |= BONITO_PCICMD_MABORT_CLR | BONITO_PCICMD_MTABORT_CLR;

	BONITO_PCIMAP_CFG = (addr >> 16) | type;

	/* Flush Bonito रेजिस्टर block */
	dummy = BONITO_PCIMAP_CFG;
	mmiowb();

	addrp = CFG_SPACE_REG(addr & 0xffff);
	अगर (access_type == PCI_ACCESS_WRITE) अणु
		ग_लिखोl(cpu_to_le32(*data), addrp);
		/* Wait till करोne */
		जबतक (BONITO_PCIMSTAT & 0xF);
	पूर्ण अन्यथा अणु
		*data = le32_to_cpu(पढ़ोl(addrp));
	पूर्ण

	/* Detect Master/Target पात */
	अगर (BONITO_PCICMD & (BONITO_PCICMD_MABORT_CLR |
			     BONITO_PCICMD_MTABORT_CLR)) अणु
		/* Error occurred */

		/* Clear bits */
		BONITO_PCICMD |= (BONITO_PCICMD_MABORT_CLR |
				  BONITO_PCICMD_MTABORT_CLR);

		वापस -1;
	पूर्ण

	वापस 0;

पूर्ण


/*
 * We can't address 8 and 16 bit words directly.  Instead we have to
 * पढ़ो/ग_लिखो a 32bit word and mask/modअगरy the data we actually want.
 */
अटल पूर्णांक bonito64_pcibios_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			     पूर्णांक where, पूर्णांक size, u32 * val)
अणु
	u32 data = 0;

	अगर ((size == 2) && (where & 1))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	अन्यथा अगर ((size == 4) && (where & 3))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	अगर (bonito64_pcibios_config_access(PCI_ACCESS_READ, bus, devfn, where,
				       &data))
		वापस -1;

	अगर (size == 1)
		*val = (data >> ((where & 3) << 3)) & 0xff;
	अन्यथा अगर (size == 2)
		*val = (data >> ((where & 3) << 3)) & 0xffff;
	अन्यथा
		*val = data;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक bonito64_pcibios_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			      पूर्णांक where, पूर्णांक size, u32 val)
अणु
	u32 data = 0;

	अगर ((size == 2) && (where & 1))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	अन्यथा अगर ((size == 4) && (where & 3))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	अगर (size == 4)
		data = val;
	अन्यथा अणु
		अगर (bonito64_pcibios_config_access(PCI_ACCESS_READ, bus, devfn,
					       where, &data))
			वापस -1;

		अगर (size == 1)
			data = (data & ~(0xff << ((where & 3) << 3))) |
				(val << ((where & 3) << 3));
		अन्यथा अगर (size == 2)
			data = (data & ~(0xffff << ((where & 3) << 3))) |
				(val << ((where & 3) << 3));
	पूर्ण

	अगर (bonito64_pcibios_config_access(PCI_ACCESS_WRITE, bus, devfn, where,
				       &data))
		वापस -1;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops bonito64_pci_ops = अणु
	.पढ़ो = bonito64_pcibios_पढ़ो,
	.ग_लिखो = bonito64_pcibios_ग_लिखो
पूर्ण;
