<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/mach-ixp4xx/common-pci.c 
 *
 * IXP4XX PCI routines क्रम all platक्रमms
 *
 * Maपूर्णांकainer: Deepak Saxena <dsaxena@plनिकासy.net>
 *
 * Copyright (C) 2002 Intel Corporation.
 * Copyright (C) 2003 Greg Ungerer <gerg@snapgear.com>
 * Copyright (C) 2003-2004 MontaVista Software, Inc.
 */

#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/export.h>
#समावेश <यंत्र/dma-mapping.h>

#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/sizes.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश <mach/hardware.h>


/*
 * IXP4xx PCI पढ़ो function is dependent on whether we are 
 * running A0 or B0 (AppleGate) silicon.
 */
पूर्णांक (*ixp4xx_pci_पढ़ो)(u32 addr, u32 cmd, u32* data);

/*
 * Base address क्रम PCI रेजिस्टर region
 */
अचिन्हित दीर्घ ixp4xx_pci_reg_base = 0;

/*
 * PCI cfg an I/O routines are करोne by programming a 
 * command/byte enable रेजिस्टर, and then पढ़ो/writing
 * the data from a data रेजिस्टर. We need to ensure
 * these transactions are atomic or we will end up
 * with corrupt data on the bus or in a driver.
 */
अटल DEFINE_RAW_SPINLOCK(ixp4xx_pci_lock);

/*
 * Read from PCI config space
 */
अटल व्योम crp_पढ़ो(u32 ad_cbe, u32 *data)
अणु
	अचिन्हित दीर्घ flags;
	raw_spin_lock_irqsave(&ixp4xx_pci_lock, flags);
	*PCI_CRP_AD_CBE = ad_cbe;
	*data = *PCI_CRP_RDATA;
	raw_spin_unlock_irqrestore(&ixp4xx_pci_lock, flags);
पूर्ण

/*
 * Write to PCI config space
 */
अटल व्योम crp_ग_लिखो(u32 ad_cbe, u32 data)
अणु 
	अचिन्हित दीर्घ flags;
	raw_spin_lock_irqsave(&ixp4xx_pci_lock, flags);
	*PCI_CRP_AD_CBE = CRP_AD_CBE_WRITE | ad_cbe;
	*PCI_CRP_WDATA = data;
	raw_spin_unlock_irqrestore(&ixp4xx_pci_lock, flags);
पूर्ण

अटल अंतरभूत पूर्णांक check_master_पात(व्योम)
अणु
	/* check Master Abort bit after access */
	अचिन्हित दीर्घ isr = *PCI_ISR;

	अगर (isr & PCI_ISR_PFE) अणु
		/* make sure the Master Abort bit is reset */    
		*PCI_ISR = PCI_ISR_PFE;
		pr_debug("%s failed\n", __func__);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ixp4xx_pci_पढ़ो_errata(u32 addr, u32 cmd, u32* data)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = 0;
	पूर्णांक i;

	raw_spin_lock_irqsave(&ixp4xx_pci_lock, flags);

	*PCI_NP_AD = addr;

	/* 
	 * PCI workaround  - only works अगर NP PCI space पढ़ोs have 
	 * no side effects!!! Read 8 बार. last one will be good.
	 */
	क्रम (i = 0; i < 8; i++) अणु
		*PCI_NP_CBE = cmd;
		*data = *PCI_NP_RDATA;
		*data = *PCI_NP_RDATA;
	पूर्ण

	अगर(check_master_पात())
		retval = 1;

	raw_spin_unlock_irqrestore(&ixp4xx_pci_lock, flags);
	वापस retval;
पूर्ण

पूर्णांक ixp4xx_pci_पढ़ो_no_errata(u32 addr, u32 cmd, u32* data)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = 0;

	raw_spin_lock_irqsave(&ixp4xx_pci_lock, flags);

	*PCI_NP_AD = addr;

	/* set up and execute the पढ़ो */    
	*PCI_NP_CBE = cmd;

	/* the result of the पढ़ो is now in NP_RDATA */
	*data = *PCI_NP_RDATA; 

	अगर(check_master_पात())
		retval = 1;

	raw_spin_unlock_irqrestore(&ixp4xx_pci_lock, flags);
	वापस retval;
पूर्ण

पूर्णांक ixp4xx_pci_ग_लिखो(u32 addr, u32 cmd, u32 data)
अणु    
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = 0;

	raw_spin_lock_irqsave(&ixp4xx_pci_lock, flags);

	*PCI_NP_AD = addr;

	/* set up the ग_लिखो */
	*PCI_NP_CBE = cmd;

	/* execute the ग_लिखो by writing to NP_WDATA */
	*PCI_NP_WDATA = data;

	अगर(check_master_पात())
		retval = 1;

	raw_spin_unlock_irqrestore(&ixp4xx_pci_lock, flags);
	वापस retval;
पूर्ण

अटल u32 ixp4xx_config_addr(u8 bus_num, u16 devfn, पूर्णांक where)
अणु
	u32 addr;
	अगर (!bus_num) अणु
		/* type 0 */
		addr = BIT(32-PCI_SLOT(devfn)) | ((PCI_FUNC(devfn)) << 8) | 
		    (where & ~3);	
	पूर्ण अन्यथा अणु
		/* type 1 */
		addr = (bus_num << 16) | ((PCI_SLOT(devfn)) << 11) | 
			((PCI_FUNC(devfn)) << 8) | (where & ~3) | 1;
	पूर्ण
	वापस addr;
पूर्ण

/*
 * Mask table, bits to mask क्रम quantity of size 1, 2 or 4 bytes.
 * 0 and 3 are not valid indexes...
 */
अटल u32 bytemask[] = अणु
	/*0*/	0,
	/*1*/	0xff,
	/*2*/	0xffff,
	/*3*/	0,
	/*4*/	0xffffffff,
पूर्ण;

अटल u32 local_byte_lane_enable_bits(u32 n, पूर्णांक size)
अणु
	अगर (size == 1)
		वापस (0xf & ~BIT(n)) << CRP_AD_CBE_BESL;
	अगर (size == 2)
		वापस (0xf & ~(BIT(n) | BIT(n+1))) << CRP_AD_CBE_BESL;
	अगर (size == 4)
		वापस 0;
	वापस 0xffffffff;
पूर्ण

अटल पूर्णांक local_पढ़ो_config(पूर्णांक where, पूर्णांक size, u32 *value)
अणु 
	u32 n, data;
	pr_debug("local_read_config from %d size %d\n", where, size);
	n = where % 4;
	crp_पढ़ो(where & ~3, &data);
	*value = (data >> (8*n)) & bytemask[size];
	pr_debug("local_read_config read %#x\n", *value);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक local_ग_लिखो_config(पूर्णांक where, पूर्णांक size, u32 value)
अणु
	u32 n, byte_enables, data;
	pr_debug("local_write_config %#x to %d size %d\n", value, where, size);
	n = where % 4;
	byte_enables = local_byte_lane_enable_bits(n, size);
	अगर (byte_enables == 0xffffffff)
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	data = value << (8*n);
	crp_ग_लिखो((where & ~3) | byte_enables, data);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल u32 byte_lane_enable_bits(u32 n, पूर्णांक size)
अणु
	अगर (size == 1)
		वापस (0xf & ~BIT(n)) << 4;
	अगर (size == 2)
		वापस (0xf & ~(BIT(n) | BIT(n+1))) << 4;
	अगर (size == 4)
		वापस 0;
	वापस 0xffffffff;
पूर्ण

अटल पूर्णांक ixp4xx_pci_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where, पूर्णांक size, u32 *value)
अणु
	u32 n, byte_enables, addr, data;
	u8 bus_num = bus->number;

	pr_debug("read_config from %d size %d dev %d:%d:%d\n", where, size,
		bus_num, PCI_SLOT(devfn), PCI_FUNC(devfn));

	*value = 0xffffffff;
	n = where % 4;
	byte_enables = byte_lane_enable_bits(n, size);
	अगर (byte_enables == 0xffffffff)
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	addr = ixp4xx_config_addr(bus_num, devfn, where);
	अगर (ixp4xx_pci_पढ़ो(addr, byte_enables | NP_CMD_CONFIGREAD, &data))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	*value = (data >> (8*n)) & bytemask[size];
	pr_debug("read_config_byte read %#x\n", *value);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक ixp4xx_pci_ग_लिखो_config(काष्ठा pci_bus *bus,  अचिन्हित पूर्णांक devfn, पूर्णांक where, पूर्णांक size, u32 value)
अणु
	u32 n, byte_enables, addr, data;
	u8 bus_num = bus->number;

	pr_debug("write_config_byte %#x to %d size %d dev %d:%d:%d\n", value, where,
		size, bus_num, PCI_SLOT(devfn), PCI_FUNC(devfn));

	n = where % 4;
	byte_enables = byte_lane_enable_bits(n, size);
	अगर (byte_enables == 0xffffffff)
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	addr = ixp4xx_config_addr(bus_num, devfn, where);
	data = value << (8*n);
	अगर (ixp4xx_pci_ग_लिखो(addr, byte_enables | NP_CMD_CONFIGWRITE, data))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops ixp4xx_ops = अणु
	.पढ़ो =  ixp4xx_pci_पढ़ो_config,
	.ग_लिखो = ixp4xx_pci_ग_लिखो_config,
पूर्ण;

/*
 * PCI पात handler
 */
अटल पूर्णांक पात_handler(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr, काष्ठा pt_regs *regs)
अणु
	u32 isr, status;

	isr = *PCI_ISR;
	local_पढ़ो_config(PCI_STATUS, 2, &status);
	pr_debug("PCI: abort_handler addr = %#lx, isr = %#x, "
		"status = %#x\n", addr, isr, status);

	/* make sure the Master Abort bit is reset */    
	*PCI_ISR = PCI_ISR_PFE;
	status |= PCI_STATUS_REC_MASTER_ABORT;
	local_ग_लिखो_config(PCI_STATUS, 2, status);

	/*
	 * If it was an imprecise पात, then we need to correct the
	 * वापस address to be _after_ the inकाष्ठाion.
	 */
	अगर (fsr & (1 << 10))
		regs->ARM_pc += 4;

	वापस 0;
पूर्ण

व्योम __init ixp4xx_pci_preinit(व्योम)
अणु
	अचिन्हित दीर्घ cpuid = पढ़ो_cpuid_id();

#अगर_घोषित CONFIG_IXP4XX_INसूचीECT_PCI
	pcibios_min_mem = 0x10000000; /* 1 GB of indirect PCI MMIO space */
#अन्यथा
	pcibios_min_mem = 0x48000000; /* 64 MB of PCI MMIO space */
#पूर्ण_अगर
	/*
	 * Determine which PCI पढ़ो method to use.
	 * Rev 0 IXP425 requires workaround.
	 */
	अगर (!(cpuid & 0xf) && cpu_is_ixp42x()) अणु
		prपूर्णांकk("PCI: IXP42x A0 silicon detected - "
			"PCI Non-Prefetch Workaround Enabled\n");
		ixp4xx_pci_पढ़ो = ixp4xx_pci_पढ़ो_errata;
	पूर्ण अन्यथा
		ixp4xx_pci_पढ़ो = ixp4xx_pci_पढ़ो_no_errata;


	/* hook in our fault handler क्रम PCI errors */
	hook_fault_code(16+6, पात_handler, SIGBUS, 0,
			"imprecise external abort");

	pr_debug("setup PCI-AHB(inbound) and AHB-PCI(outbound) address mappings\n");

	/*
	 * We use identity AHB->PCI address translation
	 * in the 0x48000000 to 0x4bffffff address space
	 */
	*PCI_PCIMEMBASE = 0x48494A4B;

	/*
	 * We also use identity PCI->AHB address translation
	 * in 4 16MB BARs that begin at the physical memory start
	 */
	*PCI_AHBMEMBASE = (PHYS_OFFSET & 0xFF000000) +
		((PHYS_OFFSET & 0xFF000000) >> 8) +
		((PHYS_OFFSET & 0xFF000000) >> 16) +
		((PHYS_OFFSET & 0xFF000000) >> 24) +
		0x00010203;

	अगर (*PCI_CSR & PCI_CSR_HOST) अणु
		prपूर्णांकk("PCI: IXP4xx is host\n");

		pr_debug("setup BARs in controller\n");

		/*
		 * We configure the PCI inbound memory winकरोws to be
		 * 1:1 mapped to SDRAM
		 */
		local_ग_लिखो_config(PCI_BASE_ADDRESS_0, 4, PHYS_OFFSET);
		local_ग_लिखो_config(PCI_BASE_ADDRESS_1, 4, PHYS_OFFSET + SZ_16M);
		local_ग_लिखो_config(PCI_BASE_ADDRESS_2, 4, PHYS_OFFSET + SZ_32M);
		local_ग_लिखो_config(PCI_BASE_ADDRESS_3, 4,
					PHYS_OFFSET + SZ_32M + SZ_16M);

		/*
		 * Enable CSR winकरोw at 64 MiB to allow PCI masters
		 * to जारी prefetching past 64 MiB boundary.
		 */
		local_ग_लिखो_config(PCI_BASE_ADDRESS_4, 4, PHYS_OFFSET + SZ_64M);

		/*
		 * Enable the IO winकरोw to be way up high, at 0xfffffc00
		 */
		local_ग_लिखो_config(PCI_BASE_ADDRESS_5, 4, 0xfffffc01);
		local_ग_लिखो_config(0x40, 4, 0x000080FF); /* No TRDY समय limit */
	पूर्ण अन्यथा अणु
		prपूर्णांकk("PCI: IXP4xx is target - No bus scan performed\n");
	पूर्ण

	prपूर्णांकk("PCI: IXP4xx Using %s access for memory space\n",
#अगर_अघोषित CONFIG_IXP4XX_INसूचीECT_PCI
			"direct"
#अन्यथा
			"indirect"
#पूर्ण_अगर
		);

	pr_debug("clear error bits in ISR\n");
	*PCI_ISR = PCI_ISR_PSE | PCI_ISR_PFE | PCI_ISR_PPE | PCI_ISR_AHBE;

	/*
	 * Set Initialize Complete in PCI Control Register: allow IXP4XX to
	 * respond to PCI configuration cycles. Specअगरy that the AHB bus is
	 * operating in big endian mode. Set up byte lane swapping between 
	 * little-endian PCI and the big-endian AHB bus 
	 */
#अगर_घोषित __ARMEB__
	*PCI_CSR = PCI_CSR_IC | PCI_CSR_ABE | PCI_CSR_PDS | PCI_CSR_ADS;
#अन्यथा
	*PCI_CSR = PCI_CSR_IC | PCI_CSR_ABE;
#पूर्ण_अगर

	pr_debug("DONE\n");
पूर्ण

पूर्णांक ixp4xx_setup(पूर्णांक nr, काष्ठा pci_sys_data *sys)
अणु
	काष्ठा resource *res;

	अगर (nr >= 1)
		वापस 0;

	res = kसुस्मृति(2, माप(*res), GFP_KERNEL);
	अगर (res == शून्य) अणु
		/* 
		 * If we're out of memory this early, something is wrong,
		 * so we might as well catch it here.
		 */
		panic("PCI: unable to allocate resources?\n");
	पूर्ण

	local_ग_लिखो_config(PCI_COMMAND, 2, PCI_COMMAND_MASTER | PCI_COMMAND_MEMORY);

	res[0].name = "PCI I/O Space";
	res[0].start = 0x00000000;
	res[0].end = 0x0000ffff;
	res[0].flags = IORESOURCE_IO;

	res[1].name = "PCI Memory Space";
	res[1].start = PCIBIOS_MIN_MEM;
	res[1].end = PCIBIOS_MAX_MEM;
	res[1].flags = IORESOURCE_MEM;

	request_resource(&ioport_resource, &res[0]);
	request_resource(&iomem_resource, &res[1]);

	pci_add_resource_offset(&sys->resources, &res[0], sys->io_offset);
	pci_add_resource_offset(&sys->resources, &res[1], sys->mem_offset);

	वापस 1;
पूर्ण

EXPORT_SYMBOL(ixp4xx_pci_पढ़ो);
EXPORT_SYMBOL(ixp4xx_pci_ग_लिखो);
