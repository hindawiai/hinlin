<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 1999, 2000, 2004  MIPS Technologies, Inc.
 *	All rights reserved.
 *	Authors: Carsten Langgaard <carstenl@mips.com>
 *		 Maciej W. Rozycki <macro@mips.com>
 *
 * Copyright (C) 2009 Lemote Inc.
 * Author: Wu Zhangjin <wuzhangjin@gmail.com>
 */
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>

#समावेश <loongson.h>

#अगर_घोषित CONFIG_CS5536
#समावेश <cs5536/cs5536_pci.h>
#समावेश <cs5536/cs5536.h>
#पूर्ण_अगर

#घोषणा PCI_ACCESS_READ	 0
#घोषणा PCI_ACCESS_WRITE 1

#घोषणा CFG_SPACE_REG(offset) \
	(व्योम *)CKSEG1ADDR(LOONGSON_PCICFG_BASE | (offset))
#घोषणा ID_SEL_BEGIN 11
#घोषणा MAX_DEV_NUM (31 - ID_SEL_BEGIN)


अटल पूर्णांक loongson_pcibios_config_access(अचिन्हित अक्षर access_type,
				      काष्ठा pci_bus *bus,
				      अचिन्हित पूर्णांक devfn, पूर्णांक where,
				      u32 *data)
अणु
	u32 busnum = bus->number;
	u32 addr, type;
	u32 dummy;
	व्योम *addrp;
	पूर्णांक device = PCI_SLOT(devfn);
	पूर्णांक function = PCI_FUNC(devfn);
	पूर्णांक reg = where & ~3;

	अगर (busnum == 0) अणु
		/* board-specअगरic part,currently,only fuloong2f,yeeloong2f
		 * use CS5536, fuloong2e use via686b, gdium has no
		 * south bridge
		 */
#अगर_घोषित CONFIG_CS5536
		/* cs5536_pci_conf_पढ़ो4/ग_लिखो4() will call _rdmsr/_wrmsr() to
		 * access the regsters PCI_MSR_ADDR, PCI_MSR_DATA_LO,
		 * PCI_MSR_DATA_HI, which is bigger than PCI_MSR_CTRL, so, it
		 * will not go this branch, but the others. so, no calling dead
		 * loop here.
		 */
		अगर ((PCI_IDSEL_CS5536 == device) && (reg < PCI_MSR_CTRL)) अणु
			चयन (access_type) अणु
			हाल PCI_ACCESS_READ:
				*data = cs5536_pci_conf_पढ़ो4(function, reg);
				अवरोध;
			हाल PCI_ACCESS_WRITE:
				cs5536_pci_conf_ग_लिखो4(function, reg, *data);
				अवरोध;
			पूर्ण
			वापस 0;
		पूर्ण
#पूर्ण_अगर
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
	LOONGSON_PCICMD |= LOONGSON_PCICMD_MABORT_CLR | \
				LOONGSON_PCICMD_MTABORT_CLR;

	LOONGSON_PCIMAP_CFG = (addr >> 16) | type;

	/* Flush Bonito रेजिस्टर block */
	dummy = LOONGSON_PCIMAP_CFG;
	mmiowb();

	addrp = CFG_SPACE_REG(addr & 0xffff);
	अगर (access_type == PCI_ACCESS_WRITE)
		ग_लिखोl(cpu_to_le32(*data), addrp);
	अन्यथा
		*data = le32_to_cpu(पढ़ोl(addrp));

	/* Detect Master/Target पात */
	अगर (LOONGSON_PCICMD & (LOONGSON_PCICMD_MABORT_CLR |
			     LOONGSON_PCICMD_MTABORT_CLR)) अणु
		/* Error occurred */

		/* Clear bits */
		LOONGSON_PCICMD |= (LOONGSON_PCICMD_MABORT_CLR |
				  LOONGSON_PCICMD_MTABORT_CLR);

		वापस -1;
	पूर्ण

	वापस 0;

पूर्ण


/*
 * We can't address 8 and 16 bit words directly.  Instead we have to
 * पढ़ो/ग_लिखो a 32bit word and mask/modअगरy the data we actually want.
 */
अटल पूर्णांक loongson_pcibios_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			     पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	u32 data = 0;

	अगर ((size == 2) && (where & 1))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	अन्यथा अगर ((size == 4) && (where & 3))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	अगर (loongson_pcibios_config_access(PCI_ACCESS_READ, bus, devfn, where,
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

अटल पूर्णांक loongson_pcibios_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
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
		अगर (loongson_pcibios_config_access(PCI_ACCESS_READ, bus, devfn,
					where, &data))
			वापस -1;

		अगर (size == 1)
			data = (data & ~(0xff << ((where & 3) << 3))) |
				(val << ((where & 3) << 3));
		अन्यथा अगर (size == 2)
			data = (data & ~(0xffff << ((where & 3) << 3))) |
				(val << ((where & 3) << 3));
	पूर्ण

	अगर (loongson_pcibios_config_access(PCI_ACCESS_WRITE, bus, devfn, where,
				       &data))
		वापस -1;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops loongson_pci_ops = अणु
	.पढ़ो = loongson_pcibios_पढ़ो,
	.ग_लिखो = loongson_pcibios_ग_लिखो
पूर्ण;

#अगर_घोषित CONFIG_CS5536
DEFINE_RAW_SPINLOCK(msr_lock);

व्योम _rdmsr(u32 msr, u32 *hi, u32 *lo)
अणु
	काष्ठा pci_bus bus = अणु
		.number = PCI_BUS_CS5536
	पूर्ण;
	u32 devfn = PCI_DEVFN(PCI_IDSEL_CS5536, 0);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&msr_lock, flags);
	loongson_pcibios_ग_लिखो(&bus, devfn, PCI_MSR_ADDR, 4, msr);
	loongson_pcibios_पढ़ो(&bus, devfn, PCI_MSR_DATA_LO, 4, lo);
	loongson_pcibios_पढ़ो(&bus, devfn, PCI_MSR_DATA_HI, 4, hi);
	raw_spin_unlock_irqrestore(&msr_lock, flags);
पूर्ण
EXPORT_SYMBOL(_rdmsr);

व्योम _wrmsr(u32 msr, u32 hi, u32 lo)
अणु
	काष्ठा pci_bus bus = अणु
		.number = PCI_BUS_CS5536
	पूर्ण;
	u32 devfn = PCI_DEVFN(PCI_IDSEL_CS5536, 0);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&msr_lock, flags);
	loongson_pcibios_ग_लिखो(&bus, devfn, PCI_MSR_ADDR, 4, msr);
	loongson_pcibios_ग_लिखो(&bus, devfn, PCI_MSR_DATA_LO, 4, lo);
	loongson_pcibios_ग_लिखो(&bus, devfn, PCI_MSR_DATA_HI, 4, hi);
	raw_spin_unlock_irqrestore(&msr_lock, flags);
पूर्ण
EXPORT_SYMBOL(_wrmsr);
#पूर्ण_अगर
