<शैली गुरु>
/*
 * Broadcom specअगरic AMBA
 * PCI Core in hosपंचांगode
 *
 * Copyright 2005 - 2011, Broadcom Corporation
 * Copyright 2006, 2007, Michael Buesch <m@bues.ch>
 * Copyright 2011, 2012, Hauke Mehrtens <hauke@hauke-m.de>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "bcma_private.h"
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/bcma/bcma.h>
#समावेश <यंत्र/paccess.h>

/* Probe a 32bit value on the bus and catch bus exceptions.
 * Returns nonzero on a bus exception.
 * This is MIPS specअगरic */
#घोषणा mips_busprobe32(val, addr)	get_dbe((val), ((u32 *)(addr)))

/* Assume one-hot slot wiring */
#घोषणा BCMA_PCI_SLOT_MAX	16
#घोषणा	PCI_CONFIG_SPACE_SIZE	256

bool bcma_core_pci_is_in_hosपंचांगode(काष्ठा bcma_drv_pci *pc)
अणु
	काष्ठा bcma_bus *bus = pc->core->bus;
	u16 chipid_top;
	u32 पंचांगp;

	chipid_top = (bus->chipinfo.id & 0xFF00);
	अगर (chipid_top != 0x4700 &&
	    chipid_top != 0x5300)
		वापस false;

	bcma_core_enable(pc->core, 0);

	वापस !mips_busprobe32(पंचांगp, pc->core->io_addr);
पूर्ण

अटल u32 bcma_pcie_पढ़ो_config(काष्ठा bcma_drv_pci *pc, u32 address)
अणु
	pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_CONFIG_ADDR, address);
	pcicore_पढ़ो32(pc, BCMA_CORE_PCI_CONFIG_ADDR);
	वापस pcicore_पढ़ो32(pc, BCMA_CORE_PCI_CONFIG_DATA);
पूर्ण

अटल व्योम bcma_pcie_ग_लिखो_config(काष्ठा bcma_drv_pci *pc, u32 address,
				   u32 data)
अणु
	pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_CONFIG_ADDR, address);
	pcicore_पढ़ो32(pc, BCMA_CORE_PCI_CONFIG_ADDR);
	pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_CONFIG_DATA, data);
पूर्ण

अटल u32 bcma_get_cfgspace_addr(काष्ठा bcma_drv_pci *pc, अचिन्हित पूर्णांक dev,
			     अचिन्हित पूर्णांक func, अचिन्हित पूर्णांक off)
अणु
	u32 addr = 0;

	/* Issue config commands only when the data link is up (atleast
	 * one बाह्यal pcie device is present).
	 */
	अगर (dev >= 2 || !(bcma_pcie_पढ़ो(pc, BCMA_CORE_PCI_DLLP_LSREG)
			  & BCMA_CORE_PCI_DLLP_LSREG_LINKUP))
		जाओ out;

	/* Type 0 transaction */
	/* Slide the PCI winकरोw to the appropriate slot */
	pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_SBTOPCI1, BCMA_CORE_PCI_SBTOPCI_CFG0);
	/* Calculate the address */
	addr = pc->host_controller->host_cfg_addr;
	addr |= (dev << BCMA_CORE_PCI_CFG_SLOT_SHIFT);
	addr |= (func << BCMA_CORE_PCI_CFG_FUN_SHIFT);
	addr |= (off & ~3);

out:
	वापस addr;
पूर्ण

अटल पूर्णांक bcma_extpci_पढ़ो_config(काष्ठा bcma_drv_pci *pc, अचिन्हित पूर्णांक dev,
				  अचिन्हित पूर्णांक func, अचिन्हित पूर्णांक off,
				  व्योम *buf, पूर्णांक len)
अणु
	पूर्णांक err = -EINVAL;
	u32 addr, val;
	व्योम __iomem *mmio = 0;

	WARN_ON(!pc->hosपंचांगode);
	अगर (unlikely(len != 1 && len != 2 && len != 4))
		जाओ out;
	अगर (dev == 0) अणु
		/* we support only two functions on device 0 */
		अगर (func > 1)
			जाओ out;

		/* accesses to config रेजिस्टरs with offsets >= 256
		 * requires indirect access.
		 */
		अगर (off >= PCI_CONFIG_SPACE_SIZE) अणु
			addr = (func << 12);
			addr |= (off & 0x0FFC);
			val = bcma_pcie_पढ़ो_config(pc, addr);
		पूर्ण अन्यथा अणु
			addr = BCMA_CORE_PCI_PCICFG0;
			addr |= (func << 8);
			addr |= (off & 0xFC);
			val = pcicore_पढ़ो32(pc, addr);
		पूर्ण
	पूर्ण अन्यथा अणु
		addr = bcma_get_cfgspace_addr(pc, dev, func, off);
		अगर (unlikely(!addr))
			जाओ out;
		err = -ENOMEM;
		mmio = ioremap(addr, माप(val));
		अगर (!mmio)
			जाओ out;

		अगर (mips_busprobe32(val, mmio)) अणु
			val = 0xFFFFFFFF;
			जाओ unmap;
		पूर्ण
	पूर्ण
	val >>= (8 * (off & 3));

	चयन (len) अणु
	हाल 1:
		*((u8 *)buf) = (u8)val;
		अवरोध;
	हाल 2:
		*((u16 *)buf) = (u16)val;
		अवरोध;
	हाल 4:
		*((u32 *)buf) = (u32)val;
		अवरोध;
	पूर्ण
	err = 0;
unmap:
	अगर (mmio)
		iounmap(mmio);
out:
	वापस err;
पूर्ण

अटल पूर्णांक bcma_extpci_ग_लिखो_config(काष्ठा bcma_drv_pci *pc, अचिन्हित पूर्णांक dev,
				   अचिन्हित पूर्णांक func, अचिन्हित पूर्णांक off,
				   स्थिर व्योम *buf, पूर्णांक len)
अणु
	पूर्णांक err = -EINVAL;
	u32 addr, val;
	व्योम __iomem *mmio = 0;
	u16 chipid = pc->core->bus->chipinfo.id;

	WARN_ON(!pc->hosपंचांगode);
	अगर (unlikely(len != 1 && len != 2 && len != 4))
		जाओ out;
	अगर (dev == 0) अणु
		/* we support only two functions on device 0 */
		अगर (func > 1)
			जाओ out;

		/* accesses to config रेजिस्टरs with offsets >= 256
		 * requires indirect access.
		 */
		अगर (off >= PCI_CONFIG_SPACE_SIZE) अणु
			addr = (func << 12);
			addr |= (off & 0x0FFC);
			val = bcma_pcie_पढ़ो_config(pc, addr);
		पूर्ण अन्यथा अणु
			addr = BCMA_CORE_PCI_PCICFG0;
			addr |= (func << 8);
			addr |= (off & 0xFC);
			val = pcicore_पढ़ो32(pc, addr);
		पूर्ण
	पूर्ण अन्यथा अणु
		addr = bcma_get_cfgspace_addr(pc, dev, func, off);
		अगर (unlikely(!addr))
			जाओ out;
		err = -ENOMEM;
		mmio = ioremap(addr, माप(val));
		अगर (!mmio)
			जाओ out;

		अगर (mips_busprobe32(val, mmio)) अणु
			val = 0xFFFFFFFF;
			जाओ unmap;
		पूर्ण
	पूर्ण

	चयन (len) अणु
	हाल 1:
		val &= ~(0xFF << (8 * (off & 3)));
		val |= *((स्थिर u8 *)buf) << (8 * (off & 3));
		अवरोध;
	हाल 2:
		val &= ~(0xFFFF << (8 * (off & 3)));
		val |= *((स्थिर u16 *)buf) << (8 * (off & 3));
		अवरोध;
	हाल 4:
		val = *((स्थिर u32 *)buf);
		अवरोध;
	पूर्ण
	अगर (dev == 0) अणु
		/* accesses to config रेजिस्टरs with offsets >= 256
		 * requires indirect access.
		 */
		अगर (off >= PCI_CONFIG_SPACE_SIZE)
			bcma_pcie_ग_लिखो_config(pc, addr, val);
		अन्यथा
			pcicore_ग_लिखो32(pc, addr, val);
	पूर्ण अन्यथा अणु
		ग_लिखोl(val, mmio);

		अगर (chipid == BCMA_CHIP_ID_BCM4716 ||
		    chipid == BCMA_CHIP_ID_BCM4748)
			पढ़ोl(mmio);
	पूर्ण

	err = 0;
unmap:
	अगर (mmio)
		iounmap(mmio);
out:
	वापस err;
पूर्ण

अटल पूर्णांक bcma_core_pci_hosपंचांगode_पढ़ो_config(काष्ठा pci_bus *bus,
					      अचिन्हित पूर्णांक devfn,
					      पूर्णांक reg, पूर्णांक size, u32 *val)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;
	काष्ठा bcma_drv_pci *pc;
	काष्ठा bcma_drv_pci_host *pc_host;

	pc_host = container_of(bus->ops, काष्ठा bcma_drv_pci_host, pci_ops);
	pc = pc_host->pdev;

	spin_lock_irqsave(&pc_host->cfgspace_lock, flags);
	err = bcma_extpci_पढ़ो_config(pc, PCI_SLOT(devfn),
				     PCI_FUNC(devfn), reg, val, size);
	spin_unlock_irqrestore(&pc_host->cfgspace_lock, flags);

	वापस err ? PCIBIOS_DEVICE_NOT_FOUND : PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक bcma_core_pci_hosपंचांगode_ग_लिखो_config(काष्ठा pci_bus *bus,
					       अचिन्हित पूर्णांक devfn,
					       पूर्णांक reg, पूर्णांक size, u32 val)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;
	काष्ठा bcma_drv_pci *pc;
	काष्ठा bcma_drv_pci_host *pc_host;

	pc_host = container_of(bus->ops, काष्ठा bcma_drv_pci_host, pci_ops);
	pc = pc_host->pdev;

	spin_lock_irqsave(&pc_host->cfgspace_lock, flags);
	err = bcma_extpci_ग_लिखो_config(pc, PCI_SLOT(devfn),
				      PCI_FUNC(devfn), reg, &val, size);
	spin_unlock_irqrestore(&pc_host->cfgspace_lock, flags);

	वापस err ? PCIBIOS_DEVICE_NOT_FOUND : PCIBIOS_SUCCESSFUL;
पूर्ण

/* वापस cap_offset अगर requested capability exists in the PCI config space */
अटल u8 bcma_find_pci_capability(काष्ठा bcma_drv_pci *pc, अचिन्हित पूर्णांक dev,
				   अचिन्हित पूर्णांक func, u8 req_cap_id,
				   अचिन्हित अक्षर *buf, u32 *buflen)
अणु
	u8 cap_id;
	u8 cap_ptr = 0;
	u32 bufsize;
	u8 byte_val;

	/* check क्रम Header type 0 */
	bcma_extpci_पढ़ो_config(pc, dev, func, PCI_HEADER_TYPE, &byte_val,
				माप(u8));
	अगर ((byte_val & 0x7F) != PCI_HEADER_TYPE_NORMAL)
		वापस cap_ptr;

	/* check अगर the capability poपूर्णांकer field exists */
	bcma_extpci_पढ़ो_config(pc, dev, func, PCI_STATUS, &byte_val,
				माप(u8));
	अगर (!(byte_val & PCI_STATUS_CAP_LIST))
		वापस cap_ptr;

	/* check अगर the capability poपूर्णांकer is 0x00 */
	bcma_extpci_पढ़ो_config(pc, dev, func, PCI_CAPABILITY_LIST, &cap_ptr,
				माप(u8));
	अगर (cap_ptr == 0x00)
		वापस cap_ptr;

	/* loop thr'u the capability list and see अगर the requested capabilty
	 * exists */
	bcma_extpci_पढ़ो_config(pc, dev, func, cap_ptr, &cap_id, माप(u8));
	जबतक (cap_id != req_cap_id) अणु
		bcma_extpci_पढ़ो_config(pc, dev, func, cap_ptr + 1, &cap_ptr,
					माप(u8));
		अगर (cap_ptr == 0x00)
			वापस cap_ptr;
		bcma_extpci_पढ़ो_config(pc, dev, func, cap_ptr, &cap_id,
					माप(u8));
	पूर्ण

	/* found the caller requested capability */
	अगर ((buf != शून्य) && (buflen != शून्य)) अणु
		u8 cap_data;

		bufsize = *buflen;
		अगर (!bufsize)
			वापस cap_ptr;

		*buflen = 0;

		/* copy the cpability data excluding cap ID and next ptr */
		cap_data = cap_ptr + 2;
		अगर ((bufsize + cap_data)  > PCI_CONFIG_SPACE_SIZE)
			bufsize = PCI_CONFIG_SPACE_SIZE - cap_data;
		*buflen = bufsize;
		जबतक (bufsize--) अणु
			bcma_extpci_पढ़ो_config(pc, dev, func, cap_data, buf,
						माप(u8));
			cap_data++;
			buf++;
		पूर्ण
	पूर्ण

	वापस cap_ptr;
पूर्ण

/* If the root port is capable of वापसing Config Request
 * Retry Status (CRS) Completion Status to software then
 * enable the feature.
 */
अटल व्योम bcma_core_pci_enable_crs(काष्ठा bcma_drv_pci *pc)
अणु
	काष्ठा bcma_bus *bus = pc->core->bus;
	u8 cap_ptr, root_ctrl, root_cap, dev;
	u16 val16;
	पूर्णांक i;

	cap_ptr = bcma_find_pci_capability(pc, 0, 0, PCI_CAP_ID_EXP, शून्य,
					   शून्य);
	root_cap = cap_ptr + PCI_EXP_RTCAP;
	bcma_extpci_पढ़ो_config(pc, 0, 0, root_cap, &val16, माप(u16));
	अगर (val16 & BCMA_CORE_PCI_RC_CRS_VISIBILITY) अणु
		/* Enable CRS software visibility */
		root_ctrl = cap_ptr + PCI_EXP_RTCTL;
		val16 = PCI_EXP_RTCTL_CRSSVE;
		bcma_extpci_पढ़ो_config(pc, 0, 0, root_ctrl, &val16,
					माप(u16));

		/* Initiate a configuration request to पढ़ो the venकरोr id
		 * field of the device function's config space header after
		 * 100 ms रुको समय from the end of Reset. If the device is
		 * not करोne with its पूर्णांकernal initialization, it must at
		 * least वापस a completion TLP, with a completion status
		 * of "Configuration Request Retry Status (CRS)". The root
		 * complex must complete the request to the host by वापसing
		 * a पढ़ो-data value of 0001h क्रम the Venकरोr ID field and
		 * all 1s क्रम any additional bytes included in the request.
		 * Poll using the config पढ़ोs क्रम max रुको समय of 1 sec or
		 * until we receive the successful completion status. Repeat
		 * the procedure क्रम all the devices.
		 */
		क्रम (dev = 1; dev < BCMA_PCI_SLOT_MAX; dev++) अणु
			क्रम (i = 0; i < 100000; i++) अणु
				bcma_extpci_पढ़ो_config(pc, dev, 0,
							PCI_VENDOR_ID, &val16,
							माप(val16));
				अगर (val16 != 0x1)
					अवरोध;
				udelay(10);
			पूर्ण
			अगर (val16 == 0x1)
				bcma_err(bus, "PCI: Broken device in slot %d\n",
					 dev);
		पूर्ण
	पूर्ण
पूर्ण

व्योम bcma_core_pci_hosपंचांगode_init(काष्ठा bcma_drv_pci *pc)
अणु
	काष्ठा bcma_bus *bus = pc->core->bus;
	काष्ठा bcma_drv_pci_host *pc_host;
	u32 पंचांगp;
	u32 pci_membase_1G;
	अचिन्हित दीर्घ io_map_base;

	bcma_info(bus, "PCIEcore in host mode found\n");

	अगर (bus->sprom.boardflags_lo & BCMA_CORE_PCI_BFL_NOPCI) अणु
		bcma_info(bus, "This PCIE core is disabled and not working\n");
		वापस;
	पूर्ण

	pc_host = kzalloc(माप(*pc_host), GFP_KERNEL);
	अगर (!pc_host)  अणु
		bcma_err(bus, "can not allocate memory");
		वापस;
	पूर्ण

	spin_lock_init(&pc_host->cfgspace_lock);

	pc->host_controller = pc_host;
	pc_host->pci_controller.io_resource = &pc_host->io_resource;
	pc_host->pci_controller.mem_resource = &pc_host->mem_resource;
	pc_host->pci_controller.pci_ops = &pc_host->pci_ops;
	pc_host->pdev = pc;

	pci_membase_1G = BCMA_SOC_PCI_DMA;
	pc_host->host_cfg_addr = BCMA_SOC_PCI_CFG;

	pc_host->pci_ops.पढ़ो = bcma_core_pci_hosपंचांगode_पढ़ो_config;
	pc_host->pci_ops.ग_लिखो = bcma_core_pci_hosपंचांगode_ग_लिखो_config;

	pc_host->mem_resource.name = "BCMA PCIcore external memory";
	pc_host->mem_resource.start = BCMA_SOC_PCI_DMA;
	pc_host->mem_resource.end = BCMA_SOC_PCI_DMA + BCMA_SOC_PCI_DMA_SZ - 1;
	pc_host->mem_resource.flags = IORESOURCE_MEM | IORESOURCE_PCI_FIXED;

	pc_host->io_resource.name = "BCMA PCIcore external I/O";
	pc_host->io_resource.start = 0x100;
	pc_host->io_resource.end = 0x7FF;
	pc_host->io_resource.flags = IORESOURCE_IO | IORESOURCE_PCI_FIXED;

	/* Reset RC */
	usleep_range(3000, 5000);
	pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_CTL, BCMA_CORE_PCI_CTL_RST_OE);
	msleep(50);
	pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_CTL, BCMA_CORE_PCI_CTL_RST |
			BCMA_CORE_PCI_CTL_RST_OE);

	/* 64 MB I/O access winकरोw. On 4716, use
	 * sbtopcie0 to access the device रेजिस्टरs. We
	 * can't use address match 2 (1 GB winकरोw) region
	 * as mips can't generate 64-bit address on the
	 * backplane.
	 */
	अगर (bus->chipinfo.id == BCMA_CHIP_ID_BCM4716 ||
	    bus->chipinfo.id == BCMA_CHIP_ID_BCM4748) अणु
		pc_host->mem_resource.start = BCMA_SOC_PCI_MEM;
		pc_host->mem_resource.end = BCMA_SOC_PCI_MEM +
					    BCMA_SOC_PCI_MEM_SZ - 1;
		pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_SBTOPCI0,
				BCMA_CORE_PCI_SBTOPCI_MEM | BCMA_SOC_PCI_MEM);
	पूर्ण अन्यथा अगर (bus->chipinfo.id == BCMA_CHIP_ID_BCM4706) अणु
		पंचांगp = BCMA_CORE_PCI_SBTOPCI_MEM;
		पंचांगp |= BCMA_CORE_PCI_SBTOPCI_PREF;
		पंचांगp |= BCMA_CORE_PCI_SBTOPCI_BURST;
		अगर (pc->core->core_unit == 0) अणु
			pc_host->mem_resource.start = BCMA_SOC_PCI_MEM;
			pc_host->mem_resource.end = BCMA_SOC_PCI_MEM +
						    BCMA_SOC_PCI_MEM_SZ - 1;
			pc_host->io_resource.start = 0x100;
			pc_host->io_resource.end = 0x47F;
			pci_membase_1G = BCMA_SOC_PCIE_DMA_H32;
			pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_SBTOPCI0,
					पंचांगp | BCMA_SOC_PCI_MEM);
		पूर्ण अन्यथा अगर (pc->core->core_unit == 1) अणु
			pc_host->mem_resource.start = BCMA_SOC_PCI1_MEM;
			pc_host->mem_resource.end = BCMA_SOC_PCI1_MEM +
						    BCMA_SOC_PCI_MEM_SZ - 1;
			pc_host->io_resource.start = 0x480;
			pc_host->io_resource.end = 0x7FF;
			pci_membase_1G = BCMA_SOC_PCIE1_DMA_H32;
			pc_host->host_cfg_addr = BCMA_SOC_PCI1_CFG;
			pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_SBTOPCI0,
					पंचांगp | BCMA_SOC_PCI1_MEM);
		पूर्ण
	पूर्ण अन्यथा
		pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_SBTOPCI0,
				BCMA_CORE_PCI_SBTOPCI_IO);

	/* 64 MB configuration access winकरोw */
	pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_SBTOPCI1, BCMA_CORE_PCI_SBTOPCI_CFG0);

	/* 1 GB memory access winकरोw */
	pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_SBTOPCI2,
			BCMA_CORE_PCI_SBTOPCI_MEM | pci_membase_1G);


	/* As per PCI Express Base Spec 1.1 we need to रुको क्रम
	 * at least 100 ms from the end of a reset (cold/warm/hot)
	 * beक्रमe issuing configuration requests to PCI Express
	 * devices.
	 */
	msleep(100);

	bcma_core_pci_enable_crs(pc);

	अगर (bus->chipinfo.id == BCMA_CHIP_ID_BCM4706 ||
	    bus->chipinfo.id == BCMA_CHIP_ID_BCM4716) अणु
		u16 val16;
		bcma_extpci_पढ़ो_config(pc, 0, 0, BCMA_CORE_PCI_CFG_DEVCTRL,
					&val16, माप(val16));
		val16 |= (2 << 5);	/* Max payload size of 512 */
		val16 |= (2 << 12);	/* MRRS 512 */
		bcma_extpci_ग_लिखो_config(pc, 0, 0, BCMA_CORE_PCI_CFG_DEVCTRL,
					 &val16, माप(val16));
	पूर्ण

	/* Enable PCI bridge BAR0 memory & master access */
	पंचांगp = PCI_COMMAND_MASTER | PCI_COMMAND_MEMORY;
	bcma_extpci_ग_लिखो_config(pc, 0, 0, PCI_COMMAND, &पंचांगp, माप(पंचांगp));

	/* Enable PCI पूर्णांकerrupts */
	pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_IMASK, BCMA_CORE_PCI_IMASK_INTA);

	/* Ok, पढ़ोy to run, रेजिस्टर it to the प्रणाली.
	 * The following needs change, अगर we want to port hosपंचांगode
	 * to non-MIPS platक्रमm. */
	io_map_base = (अचिन्हित दीर्घ)ioremap(pc_host->mem_resource.start,
						     resource_size(&pc_host->mem_resource));
	pc_host->pci_controller.io_map_base = io_map_base;
	set_io_port_base(pc_host->pci_controller.io_map_base);
	/* Give some समय to the PCI controller to configure itself with the new
	 * values. Not रुकोing at this poपूर्णांक causes crashes of the machine. */
	usleep_range(10000, 15000);
	रेजिस्टर_pci_controller(&pc_host->pci_controller);
	वापस;
पूर्ण

/* Early PCI fixup क्रम a device on the PCI-core bridge. */
अटल व्योम bcma_core_pci_fixup_pcibridge(काष्ठा pci_dev *dev)
अणु
	अगर (dev->bus->ops->पढ़ो != bcma_core_pci_hosपंचांगode_पढ़ो_config) अणु
		/* This is not a device on the PCI-core bridge. */
		वापस;
	पूर्ण
	अगर (PCI_SLOT(dev->devfn) != 0)
		वापस;

	pr_info("PCI: Fixing up bridge %s\n", pci_name(dev));

	/* Enable PCI bridge bus mastering and memory space */
	pci_set_master(dev);
	अगर (pcibios_enable_device(dev, ~0) < 0) अणु
		pr_err("PCI: BCMA bridge enable failed\n");
		वापस;
	पूर्ण

	/* Enable PCI bridge BAR1 prefetch and burst */
	pci_ग_लिखो_config_dword(dev, BCMA_PCI_BAR1_CONTROL, 3);
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_ANY_ID, PCI_ANY_ID, bcma_core_pci_fixup_pcibridge);

/* Early PCI fixup क्रम all PCI-cores to set the correct memory address. */
अटल व्योम bcma_core_pci_fixup_addresses(काष्ठा pci_dev *dev)
अणु
	काष्ठा resource *res;
	पूर्णांक pos, err;

	अगर (dev->bus->ops->पढ़ो != bcma_core_pci_hosपंचांगode_पढ़ो_config) अणु
		/* This is not a device on the PCI-core bridge. */
		वापस;
	पूर्ण
	अगर (PCI_SLOT(dev->devfn) == 0)
		वापस;

	pr_info("PCI: Fixing up addresses %s\n", pci_name(dev));

	क्रम (pos = 0; pos < 6; pos++) अणु
		res = &dev->resource[pos];
		अगर (res->flags & (IORESOURCE_IO | IORESOURCE_MEM)) अणु
			err = pci_assign_resource(dev, pos);
			अगर (err)
				pr_err("PCI: Problem fixing up the addresses on %s\n",
				       pci_name(dev));
		पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_ANY_ID, PCI_ANY_ID, bcma_core_pci_fixup_addresses);

/* This function is called when करोing a pci_enable_device().
 * We must first check अगर the device is a device on the PCI-core bridge. */
पूर्णांक bcma_core_pci_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	काष्ठा bcma_drv_pci_host *pc_host;
	पूर्णांक पढ़ोrq;

	अगर (dev->bus->ops->पढ़ो != bcma_core_pci_hosपंचांगode_पढ़ो_config) अणु
		/* This is not a device on the PCI-core bridge. */
		वापस -ENODEV;
	पूर्ण
	pc_host = container_of(dev->bus->ops, काष्ठा bcma_drv_pci_host,
			       pci_ops);

	pr_info("PCI: Fixing up device %s\n", pci_name(dev));

	/* Fix up पूर्णांकerrupt lines */
	dev->irq = bcma_core_irq(pc_host->pdev->core, 0);
	pci_ग_लिखो_config_byte(dev, PCI_INTERRUPT_LINE, dev->irq);

	पढ़ोrq = pcie_get_पढ़ोrq(dev);
	अगर (पढ़ोrq > 128) अणु
		pr_info("change PCIe max read request size from %i to 128\n", पढ़ोrq);
		pcie_set_पढ़ोrq(dev, 128);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(bcma_core_pci_plat_dev_init);

/* PCI device IRQ mapping. */
पूर्णांक bcma_core_pci_pcibios_map_irq(स्थिर काष्ठा pci_dev *dev)
अणु
	काष्ठा bcma_drv_pci_host *pc_host;

	अगर (dev->bus->ops->पढ़ो != bcma_core_pci_hosपंचांगode_पढ़ो_config) अणु
		/* This is not a device on the PCI-core bridge. */
		वापस -ENODEV;
	पूर्ण

	pc_host = container_of(dev->bus->ops, काष्ठा bcma_drv_pci_host,
			       pci_ops);
	वापस bcma_core_irq(pc_host->pdev->core, 0);
पूर्ण
EXPORT_SYMBOL(bcma_core_pci_pcibios_map_irq);
