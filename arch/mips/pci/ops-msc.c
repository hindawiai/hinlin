<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 1999, 2000, 2004, 2005	 MIPS Technologies, Inc.
 *    All rights reserved.
 *    Authors: Carsten Langgaard <carstenl@mips.com>
 *	       Maciej W. Rozycki <macro@mips.com>
 * Copyright (C) 2005 Ralf Baechle (ralf@linux-mips.org)
 *
 * MIPS boards specअगरic PCI support.
 */
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>

#समावेश <यंत्र/mips-boards/msc01_pci.h>

#घोषणा PCI_ACCESS_READ	 0
#घोषणा PCI_ACCESS_WRITE 1

/*
 *  PCI configuration cycle AD bus definition
 */
/* Type 0 */
#घोषणा PCI_CFG_TYPE0_REG_SHF		0
#घोषणा PCI_CFG_TYPE0_FUNC_SHF		8

/* Type 1 */
#घोषणा PCI_CFG_TYPE1_REG_SHF		0
#घोषणा PCI_CFG_TYPE1_FUNC_SHF		8
#घोषणा PCI_CFG_TYPE1_DEV_SHF		11
#घोषणा PCI_CFG_TYPE1_BUS_SHF		16

अटल पूर्णांक msc_pcibios_config_access(अचिन्हित अक्षर access_type,
	काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where, u32 * data)
अणु
	अचिन्हित अक्षर busnum = bus->number;
	u32 पूर्णांकr;

	/* Clear status रेजिस्टर bits. */
	MSC_WRITE(MSC01_PCI_INTSTAT,
		  (MSC01_PCI_INTCFG_MA_BIT | MSC01_PCI_INTCFG_TA_BIT));

	MSC_WRITE(MSC01_PCI_CFGADDR,
		  ((busnum << MSC01_PCI_CFGADDR_BNUM_SHF) |
		   (PCI_SLOT(devfn) << MSC01_PCI_CFGADDR_DNUM_SHF) |
		   (PCI_FUNC(devfn) << MSC01_PCI_CFGADDR_FNUM_SHF) |
		   ((where / 4) << MSC01_PCI_CFGADDR_RNUM_SHF)));

	/* Perक्रमm access */
	अगर (access_type == PCI_ACCESS_WRITE)
		MSC_WRITE(MSC01_PCI_CFGDATA, *data);
	अन्यथा
		MSC_READ(MSC01_PCI_CFGDATA, *data);

	/* Detect Master/Target पात */
	MSC_READ(MSC01_PCI_INTSTAT, पूर्णांकr);
	अगर (पूर्णांकr & (MSC01_PCI_INTCFG_MA_BIT | MSC01_PCI_INTCFG_TA_BIT)) अणु
		/* Error occurred */

		/* Clear bits */
		MSC_WRITE(MSC01_PCI_INTSTAT,
			  (MSC01_PCI_INTCFG_MA_BIT | MSC01_PCI_INTCFG_TA_BIT));

		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण


/*
 * We can't address 8 and 16 bit words directly.  Instead we have to
 * पढ़ो/ग_लिखो a 32bit word and mask/modअगरy the data we actually want.
 */
अटल पूर्णांक msc_pcibios_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			     पूर्णांक where, पूर्णांक size, u32 * val)
अणु
	u32 data = 0;

	अगर ((size == 2) && (where & 1))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	अन्यथा अगर ((size == 4) && (where & 3))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	अगर (msc_pcibios_config_access(PCI_ACCESS_READ, bus, devfn, where,
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

अटल पूर्णांक msc_pcibios_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
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
		अगर (msc_pcibios_config_access(PCI_ACCESS_READ, bus, devfn,
					      where, &data))
			वापस -1;

		अगर (size == 1)
			data = (data & ~(0xff << ((where & 3) << 3))) |
				(val << ((where & 3) << 3));
		अन्यथा अगर (size == 2)
			data = (data & ~(0xffff << ((where & 3) << 3))) |
				(val << ((where & 3) << 3));
	पूर्ण

	अगर (msc_pcibios_config_access(PCI_ACCESS_WRITE, bus, devfn, where,
				       &data))
		वापस -1;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops msc_pci_ops = अणु
	.पढ़ो = msc_pcibios_पढ़ो,
	.ग_लिखो = msc_pcibios_ग_लिखो
पूर्ण;
