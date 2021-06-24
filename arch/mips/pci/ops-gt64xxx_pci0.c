<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 1999, 2000, 2004  MIPS Technologies, Inc.
 *	All rights reserved.
 *	Authors: Carsten Langgaard <carstenl@mips.com>
 *		 Maciej W. Rozycki <macro@mips.com>
 */
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>

#समावेश <यंत्र/gt64120.h>

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

अटल पूर्णांक gt64xxx_pci0_pcibios_config_access(अचिन्हित अक्षर access_type,
		काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where, u32 * data)
अणु
	अचिन्हित अक्षर busnum = bus->number;
	u32 पूर्णांकr;

	अगर ((busnum == 0) && (devfn >= PCI_DEVFN(31, 0)))
		वापस -1;	/* Because of a bug in the galileo (क्रम slot 31). */

	/* Clear cause रेजिस्टर bits */
	GT_WRITE(GT_INTRCAUSE_OFS, ~(GT_INTRCAUSE_MASABORT0_BIT |
				     GT_INTRCAUSE_TARABORT0_BIT));

	/* Setup address */
	GT_WRITE(GT_PCI0_CFGADDR_OFS,
		 (busnum << GT_PCI0_CFGADDR_BUSNUM_SHF) |
		 (devfn << GT_PCI0_CFGADDR_FUNCTNUM_SHF) |
		 ((where / 4) << GT_PCI0_CFGADDR_REGNUM_SHF) |
		 GT_PCI0_CFGADDR_CONFIGEN_BIT);

	अगर (access_type == PCI_ACCESS_WRITE) अणु
		अगर (busnum == 0 && PCI_SLOT(devfn) == 0) अणु
			/*
			 * The Galileo प्रणाली controller is acting
			 * dअगरferently than other devices.
			 */
			GT_WRITE(GT_PCI0_CFGDATA_OFS, *data);
		पूर्ण अन्यथा
			__GT_WRITE(GT_PCI0_CFGDATA_OFS, *data);
	पूर्ण अन्यथा अणु
		अगर (busnum == 0 && PCI_SLOT(devfn) == 0) अणु
			/*
			 * The Galileo प्रणाली controller is acting
			 * dअगरferently than other devices.
			 */
			*data = GT_READ(GT_PCI0_CFGDATA_OFS);
		पूर्ण अन्यथा
			*data = __GT_READ(GT_PCI0_CFGDATA_OFS);
	पूर्ण

	/* Check क्रम master or target पात */
	पूर्णांकr = GT_READ(GT_INTRCAUSE_OFS);

	अगर (पूर्णांकr & (GT_INTRCAUSE_MASABORT0_BIT | GT_INTRCAUSE_TARABORT0_BIT)) अणु
		/* Error occurred */

		/* Clear bits */
		GT_WRITE(GT_INTRCAUSE_OFS, ~(GT_INTRCAUSE_MASABORT0_BIT |
					     GT_INTRCAUSE_TARABORT0_BIT));

		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण


/*
 * We can't address 8 and 16 bit words directly.  Instead we have to
 * पढ़ो/ग_लिखो a 32bit word and mask/modअगरy the data we actually want.
 */
अटल पूर्णांक gt64xxx_pci0_pcibios_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
		पूर्णांक where, पूर्णांक size, u32 * val)
अणु
	u32 data = 0;

	अगर (gt64xxx_pci0_pcibios_config_access(PCI_ACCESS_READ, bus, devfn,
					       where, &data))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (size == 1)
		*val = (data >> ((where & 3) << 3)) & 0xff;
	अन्यथा अगर (size == 2)
		*val = (data >> ((where & 3) << 3)) & 0xffff;
	अन्यथा
		*val = data;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक gt64xxx_pci0_pcibios_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
		पूर्णांक where, पूर्णांक size, u32 val)
अणु
	u32 data = 0;

	अगर (size == 4)
		data = val;
	अन्यथा अणु
		अगर (gt64xxx_pci0_pcibios_config_access(PCI_ACCESS_READ, bus,
						       devfn, where, &data))
			वापस PCIBIOS_DEVICE_NOT_FOUND;

		अगर (size == 1)
			data = (data & ~(0xff << ((where & 3) << 3))) |
				(val << ((where & 3) << 3));
		अन्यथा अगर (size == 2)
			data = (data & ~(0xffff << ((where & 3) << 3))) |
				(val << ((where & 3) << 3));
	पूर्ण

	अगर (gt64xxx_pci0_pcibios_config_access(PCI_ACCESS_WRITE, bus, devfn,
					       where, &data))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops gt64xxx_pci0_ops = अणु
	.पढ़ो	= gt64xxx_pci0_pcibios_पढ़ो,
	.ग_लिखो	= gt64xxx_pci0_pcibios_ग_लिखो
पूर्ण;
