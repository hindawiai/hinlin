<शैली गुरु>
/*
 * Broadcom specअगरic AMBA
 * Bus scanning
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "scan.h"
#समावेश "bcma_private.h"

#समावेश <linux/bcma/bcma.h>
#समावेश <linux/bcma/bcma_regs.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>

काष्ठा bcma_device_id_name अणु
	u16 id;
	स्थिर अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा bcma_device_id_name bcma_arm_device_names[] = अणु
	अणु BCMA_CORE_4706_MAC_GBIT_COMMON, "BCM4706 GBit MAC Common" पूर्ण,
	अणु BCMA_CORE_ARM_1176, "ARM 1176" पूर्ण,
	अणु BCMA_CORE_ARM_7TDMI, "ARM 7TDMI" पूर्ण,
	अणु BCMA_CORE_ARM_CM3, "ARM CM3" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bcma_device_id_name bcma_bcm_device_names[] = अणु
	अणु BCMA_CORE_OOB_ROUTER, "OOB Router" पूर्ण,
	अणु BCMA_CORE_4706_CHIPCOMMON, "BCM4706 ChipCommon" पूर्ण,
	अणु BCMA_CORE_4706_SOC_RAM, "BCM4706 SOC RAM" पूर्ण,
	अणु BCMA_CORE_4706_MAC_GBIT, "BCM4706 GBit MAC" पूर्ण,
	अणु BCMA_CORE_NS_PCIEG2, "PCIe Gen 2" पूर्ण,
	अणु BCMA_CORE_NS_DMA, "DMA" पूर्ण,
	अणु BCMA_CORE_NS_SDIO3, "SDIO3" पूर्ण,
	अणु BCMA_CORE_NS_USB20, "USB 2.0" पूर्ण,
	अणु BCMA_CORE_NS_USB30, "USB 3.0" पूर्ण,
	अणु BCMA_CORE_NS_A9JTAG, "ARM Cortex A9 JTAG" पूर्ण,
	अणु BCMA_CORE_NS_DDR23, "Denali DDR2/DDR3 memory controller" पूर्ण,
	अणु BCMA_CORE_NS_ROM, "ROM" पूर्ण,
	अणु BCMA_CORE_NS_न_अंकD, "NAND flash controller" पूर्ण,
	अणु BCMA_CORE_NS_QSPI, "SPI flash controller" पूर्ण,
	अणु BCMA_CORE_NS_CHIPCOMMON_B, "Chipcommon B" पूर्ण,
	अणु BCMA_CORE_ARMCA9, "ARM Cortex A9 core (ihost)" पूर्ण,
	अणु BCMA_CORE_AMEMC, "AMEMC (DDR)" पूर्ण,
	अणु BCMA_CORE_ALTA, "ALTA (I2S)" पूर्ण,
	अणु BCMA_CORE_INVALID, "Invalid" पूर्ण,
	अणु BCMA_CORE_CHIPCOMMON, "ChipCommon" पूर्ण,
	अणु BCMA_CORE_ILINE20, "ILine 20" पूर्ण,
	अणु BCMA_CORE_SRAM, "SRAM" पूर्ण,
	अणु BCMA_CORE_SDRAM, "SDRAM" पूर्ण,
	अणु BCMA_CORE_PCI, "PCI" पूर्ण,
	अणु BCMA_CORE_ETHERNET, "Fast Ethernet" पूर्ण,
	अणु BCMA_CORE_V90, "V90" पूर्ण,
	अणु BCMA_CORE_USB11_HOSTDEV, "USB 1.1 Hostdev" पूर्ण,
	अणु BCMA_CORE_ADSL, "ADSL" पूर्ण,
	अणु BCMA_CORE_ILINE100, "ILine 100" पूर्ण,
	अणु BCMA_CORE_IPSEC, "IPSEC" पूर्ण,
	अणु BCMA_CORE_UTOPIA, "UTOPIA" पूर्ण,
	अणु BCMA_CORE_PCMCIA, "PCMCIA" पूर्ण,
	अणु BCMA_CORE_INTERNAL_MEM, "Internal Memory" पूर्ण,
	अणु BCMA_CORE_MEMC_SDRAM, "MEMC SDRAM" पूर्ण,
	अणु BCMA_CORE_OFDM, "OFDM" पूर्ण,
	अणु BCMA_CORE_EXTIF, "EXTIF" पूर्ण,
	अणु BCMA_CORE_80211, "IEEE 802.11" पूर्ण,
	अणु BCMA_CORE_PHY_A, "PHY A" पूर्ण,
	अणु BCMA_CORE_PHY_B, "PHY B" पूर्ण,
	अणु BCMA_CORE_PHY_G, "PHY G" पूर्ण,
	अणु BCMA_CORE_USB11_HOST, "USB 1.1 Host" पूर्ण,
	अणु BCMA_CORE_USB11_DEV, "USB 1.1 Device" पूर्ण,
	अणु BCMA_CORE_USB20_HOST, "USB 2.0 Host" पूर्ण,
	अणु BCMA_CORE_USB20_DEV, "USB 2.0 Device" पूर्ण,
	अणु BCMA_CORE_SDIO_HOST, "SDIO Host" पूर्ण,
	अणु BCMA_CORE_ROBOSWITCH, "Roboswitch" पूर्ण,
	अणु BCMA_CORE_PARA_ATA, "PATA" पूर्ण,
	अणु BCMA_CORE_SATA_XORDMA, "SATA XOR-DMA" पूर्ण,
	अणु BCMA_CORE_ETHERNET_GBIT, "GBit Ethernet" पूर्ण,
	अणु BCMA_CORE_PCIE, "PCIe" पूर्ण,
	अणु BCMA_CORE_PHY_N, "PHY N" पूर्ण,
	अणु BCMA_CORE_SRAM_CTL, "SRAM Controller" पूर्ण,
	अणु BCMA_CORE_MINI_MACPHY, "Mini MACPHY" पूर्ण,
	अणु BCMA_CORE_PHY_LP, "PHY LP" पूर्ण,
	अणु BCMA_CORE_PMU, "PMU" पूर्ण,
	अणु BCMA_CORE_PHY_SSN, "PHY SSN" पूर्ण,
	अणु BCMA_CORE_SDIO_DEV, "SDIO Device" पूर्ण,
	अणु BCMA_CORE_PHY_HT, "PHY HT" पूर्ण,
	अणु BCMA_CORE_MAC_GBIT, "GBit MAC" पूर्ण,
	अणु BCMA_CORE_DDR12_MEM_CTL, "DDR1/DDR2 Memory Controller" पूर्ण,
	अणु BCMA_CORE_PCIE_RC, "PCIe Root Complex" पूर्ण,
	अणु BCMA_CORE_OCP_OCP_BRIDGE, "OCP to OCP Bridge" पूर्ण,
	अणु BCMA_CORE_SHARED_COMMON, "Common Shared" पूर्ण,
	अणु BCMA_CORE_OCP_AHB_BRIDGE, "OCP to AHB Bridge" पूर्ण,
	अणु BCMA_CORE_SPI_HOST, "SPI Host" पूर्ण,
	अणु BCMA_CORE_I2S, "I2S" पूर्ण,
	अणु BCMA_CORE_SDR_DDR1_MEM_CTL, "SDR/DDR1 Memory Controller" पूर्ण,
	अणु BCMA_CORE_SHIM, "SHIM" पूर्ण,
	अणु BCMA_CORE_PCIE2, "PCIe Gen2" पूर्ण,
	अणु BCMA_CORE_ARM_CR4, "ARM CR4" पूर्ण,
	अणु BCMA_CORE_GCI, "GCI" पूर्ण,
	अणु BCMA_CORE_CMEM, "CNDS DDR2/3 memory controller" पूर्ण,
	अणु BCMA_CORE_ARM_CA7, "ARM CA7" पूर्ण,
	अणु BCMA_CORE_DEFAULT, "Default" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bcma_device_id_name bcma_mips_device_names[] = अणु
	अणु BCMA_CORE_MIPS, "MIPS" पूर्ण,
	अणु BCMA_CORE_MIPS_3302, "MIPS 3302" पूर्ण,
	अणु BCMA_CORE_MIPS_74K, "MIPS 74K" पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *bcma_device_name(स्थिर काष्ठा bcma_device_id *id)
अणु
	स्थिर काष्ठा bcma_device_id_name *names;
	पूर्णांक size, i;

	/* search manufacturer specअगरic names */
	चयन (id->manuf) अणु
	हाल BCMA_MANUF_ARM:
		names = bcma_arm_device_names;
		size = ARRAY_SIZE(bcma_arm_device_names);
		अवरोध;
	हाल BCMA_MANUF_BCM:
		names = bcma_bcm_device_names;
		size = ARRAY_SIZE(bcma_bcm_device_names);
		अवरोध;
	हाल BCMA_MANUF_MIPS:
		names = bcma_mips_device_names;
		size = ARRAY_SIZE(bcma_mips_device_names);
		अवरोध;
	शेष:
		वापस "UNKNOWN";
	पूर्ण

	क्रम (i = 0; i < size; i++) अणु
		अगर (names[i].id == id->id)
			वापस names[i].name;
	पूर्ण

	वापस "UNKNOWN";
पूर्ण

अटल u32 bcma_scan_पढ़ो32(काष्ठा bcma_bus *bus, u8 current_coreidx,
		       u16 offset)
अणु
	वापस पढ़ोl(bus->mmio + offset);
पूर्ण

अटल व्योम bcma_scan_चयन_core(काष्ठा bcma_bus *bus, u32 addr)
अणु
	अगर (bus->hosttype == BCMA_HOSTTYPE_PCI)
		pci_ग_लिखो_config_dword(bus->host_pci, BCMA_PCI_BAR0_WIN,
				       addr);
पूर्ण

अटल u32 bcma_erom_get_ent(काष्ठा bcma_bus *bus, u32 __iomem **eromptr)
अणु
	u32 ent = पढ़ोl(*eromptr);
	(*eromptr)++;
	वापस ent;
पूर्ण

अटल व्योम bcma_erom_push_ent(u32 __iomem **eromptr)
अणु
	(*eromptr)--;
पूर्ण

अटल s32 bcma_erom_get_ci(काष्ठा bcma_bus *bus, u32 __iomem **eromptr)
अणु
	u32 ent = bcma_erom_get_ent(bus, eromptr);
	अगर (!(ent & SCAN_ER_VALID))
		वापस -ENOENT;
	अगर ((ent & SCAN_ER_TAG) != SCAN_ER_TAG_CI)
		वापस -ENOENT;
	वापस ent;
पूर्ण

अटल bool bcma_erom_is_end(काष्ठा bcma_bus *bus, u32 __iomem **eromptr)
अणु
	u32 ent = bcma_erom_get_ent(bus, eromptr);
	bcma_erom_push_ent(eromptr);
	वापस (ent == (SCAN_ER_TAG_END | SCAN_ER_VALID));
पूर्ण

अटल bool bcma_erom_is_bridge(काष्ठा bcma_bus *bus, u32 __iomem **eromptr)
अणु
	u32 ent = bcma_erom_get_ent(bus, eromptr);
	bcma_erom_push_ent(eromptr);
	वापस (((ent & SCAN_ER_VALID)) &&
		((ent & SCAN_ER_TAGX) == SCAN_ER_TAG_ADDR) &&
		((ent & SCAN_ADDR_TYPE) == SCAN_ADDR_TYPE_BRIDGE));
पूर्ण

अटल व्योम bcma_erom_skip_component(काष्ठा bcma_bus *bus, u32 __iomem **eromptr)
अणु
	u32 ent;
	जबतक (1) अणु
		ent = bcma_erom_get_ent(bus, eromptr);
		अगर ((ent & SCAN_ER_VALID) &&
		    ((ent & SCAN_ER_TAG) == SCAN_ER_TAG_CI))
			अवरोध;
		अगर (ent == (SCAN_ER_TAG_END | SCAN_ER_VALID))
			अवरोध;
	पूर्ण
	bcma_erom_push_ent(eromptr);
पूर्ण

अटल s32 bcma_erom_get_mst_port(काष्ठा bcma_bus *bus, u32 __iomem **eromptr)
अणु
	u32 ent = bcma_erom_get_ent(bus, eromptr);
	अगर (!(ent & SCAN_ER_VALID))
		वापस -ENOENT;
	अगर ((ent & SCAN_ER_TAG) != SCAN_ER_TAG_MP)
		वापस -ENOENT;
	वापस ent;
पूर्ण

अटल u32 bcma_erom_get_addr_desc(काष्ठा bcma_bus *bus, u32 __iomem **eromptr,
				  u32 type, u8 port)
अणु
	u32 addrl;
	u32 size;

	u32 ent = bcma_erom_get_ent(bus, eromptr);
	अगर ((!(ent & SCAN_ER_VALID)) ||
	    ((ent & SCAN_ER_TAGX) != SCAN_ER_TAG_ADDR) ||
	    ((ent & SCAN_ADDR_TYPE) != type) ||
	    (((ent & SCAN_ADDR_PORT) >> SCAN_ADDR_PORT_SHIFT) != port)) अणु
		bcma_erom_push_ent(eromptr);
		वापस (u32)-EINVAL;
	पूर्ण

	addrl = ent & SCAN_ADDR_ADDR;
	अगर (ent & SCAN_ADDR_AG32)
		bcma_erom_get_ent(bus, eromptr);

	अगर ((ent & SCAN_ADDR_SZ) == SCAN_ADDR_SZ_SZD) अणु
		size = bcma_erom_get_ent(bus, eromptr);
		अगर (size & SCAN_SIZE_SG32)
			bcma_erom_get_ent(bus, eromptr);
	पूर्ण

	वापस addrl;
पूर्ण

अटल काष्ठा bcma_device *bcma_find_core_by_index(काष्ठा bcma_bus *bus,
						   u16 index)
अणु
	काष्ठा bcma_device *core;

	list_क्रम_each_entry(core, &bus->cores, list) अणु
		अगर (core->core_index == index)
			वापस core;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा bcma_device *bcma_find_core_reverse(काष्ठा bcma_bus *bus, u16 coreid)
अणु
	काष्ठा bcma_device *core;

	list_क्रम_each_entry_reverse(core, &bus->cores, list) अणु
		अगर (core->id.id == coreid)
			वापस core;
	पूर्ण
	वापस शून्य;
पूर्ण

#घोषणा IS_ERR_VALUE_U32(x) ((x) >= (u32)-MAX_ERRNO)

अटल पूर्णांक bcma_get_next_core(काष्ठा bcma_bus *bus, u32 __iomem **eromptr,
			      काष्ठा bcma_device_id *match, पूर्णांक core_num,
			      काष्ठा bcma_device *core)
अणु
	u32 पंचांगp;
	u8 i, j, k;
	s32 cia, cib;
	u8 ports[2], wrappers[2];

	/* get CIs */
	cia = bcma_erom_get_ci(bus, eromptr);
	अगर (cia < 0) अणु
		bcma_erom_push_ent(eromptr);
		अगर (bcma_erom_is_end(bus, eromptr))
			वापस -ESPIPE;
		वापस -EILSEQ;
	पूर्ण
	cib = bcma_erom_get_ci(bus, eromptr);
	अगर (cib < 0)
		वापस -EILSEQ;

	/* parse CIs */
	core->id.class = (cia & SCAN_CIA_CLASS) >> SCAN_CIA_CLASS_SHIFT;
	core->id.id = (cia & SCAN_CIA_ID) >> SCAN_CIA_ID_SHIFT;
	core->id.manuf = (cia & SCAN_CIA_MANUF) >> SCAN_CIA_MANUF_SHIFT;
	ports[0] = (cib & SCAN_CIB_NMP) >> SCAN_CIB_NMP_SHIFT;
	ports[1] = (cib & SCAN_CIB_NSP) >> SCAN_CIB_NSP_SHIFT;
	wrappers[0] = (cib & SCAN_CIB_NMW) >> SCAN_CIB_NMW_SHIFT;
	wrappers[1] = (cib & SCAN_CIB_NSW) >> SCAN_CIB_NSW_SHIFT;
	core->id.rev = (cib & SCAN_CIB_REV) >> SCAN_CIB_REV_SHIFT;

	अगर (((core->id.manuf == BCMA_MANUF_ARM) &&
	     (core->id.id == 0xFFF)) ||
	    (ports[1] == 0)) अणु
		bcma_erom_skip_component(bus, eromptr);
		वापस -ENXIO;
	पूर्ण

	/* check अगर component is a core at all */
	अगर (wrappers[0] + wrappers[1] == 0) अणु
		/* Some specअगरic cores करोn't need wrappers */
		चयन (core->id.id) अणु
		हाल BCMA_CORE_4706_MAC_GBIT_COMMON:
		हाल BCMA_CORE_NS_CHIPCOMMON_B:
		हाल BCMA_CORE_PMU:
		हाल BCMA_CORE_GCI:
		/* Not used yet: हाल BCMA_CORE_OOB_ROUTER: */
			अवरोध;
		शेष:
			bcma_erom_skip_component(bus, eromptr);
			वापस -ENXIO;
		पूर्ण
	पूर्ण

	अगर (bcma_erom_is_bridge(bus, eromptr)) अणु
		bcma_erom_skip_component(bus, eromptr);
		वापस -ENXIO;
	पूर्ण

	अगर (bcma_find_core_by_index(bus, core_num)) अणु
		bcma_erom_skip_component(bus, eromptr);
		वापस -ENODEV;
	पूर्ण

	अगर (match && ((match->manuf != BCMA_ANY_MANUF &&
	      match->manuf != core->id.manuf) ||
	     (match->id != BCMA_ANY_ID && match->id != core->id.id) ||
	     (match->rev != BCMA_ANY_REV && match->rev != core->id.rev) ||
	     (match->class != BCMA_ANY_CLASS && match->class != core->id.class)
	    )) अणु
		bcma_erom_skip_component(bus, eromptr);
		वापस -ENODEV;
	पूर्ण

	/* get & parse master ports */
	क्रम (i = 0; i < ports[0]; i++) अणु
		s32 mst_port_d = bcma_erom_get_mst_port(bus, eromptr);
		अगर (mst_port_d < 0)
			वापस -EILSEQ;
	पूर्ण

	/* First Slave Address Descriptor should be port 0:
	 * the मुख्य रेजिस्टर space क्रम the core
	 */
	पंचांगp = bcma_erom_get_addr_desc(bus, eromptr, SCAN_ADDR_TYPE_SLAVE, 0);
	अगर (पंचांगp == 0 || IS_ERR_VALUE_U32(पंचांगp)) अणु
		/* Try again to see अगर it is a bridge */
		पंचांगp = bcma_erom_get_addr_desc(bus, eromptr,
					      SCAN_ADDR_TYPE_BRIDGE, 0);
		अगर (पंचांगp == 0 || IS_ERR_VALUE_U32(पंचांगp)) अणु
			वापस -EILSEQ;
		पूर्ण अन्यथा अणु
			bcma_info(bus, "Bridge found\n");
			वापस -ENXIO;
		पूर्ण
	पूर्ण
	core->addr = पंचांगp;

	/* get & parse slave ports */
	k = 0;
	क्रम (i = 0; i < ports[1]; i++) अणु
		क्रम (j = 0; ; j++) अणु
			पंचांगp = bcma_erom_get_addr_desc(bus, eromptr,
				SCAN_ADDR_TYPE_SLAVE, i);
			अगर (IS_ERR_VALUE_U32(पंचांगp)) अणु
				/* no more entries क्रम port _i_ */
				/* pr_debug("erom: slave port %d "
				 * "has %d descriptors\n", i, j); */
				अवरोध;
			पूर्ण अन्यथा अगर (k < ARRAY_SIZE(core->addr_s)) अणु
				core->addr_s[k] = पंचांगp;
				k++;
			पूर्ण
		पूर्ण
	पूर्ण

	/* get & parse master wrappers */
	क्रम (i = 0; i < wrappers[0]; i++) अणु
		क्रम (j = 0; ; j++) अणु
			पंचांगp = bcma_erom_get_addr_desc(bus, eromptr,
				SCAN_ADDR_TYPE_MWRAP, i);
			अगर (IS_ERR_VALUE_U32(पंचांगp)) अणु
				/* no more entries क्रम port _i_ */
				/* pr_debug("erom: master wrapper %d "
				 * "has %d descriptors\n", i, j); */
				अवरोध;
			पूर्ण अन्यथा अणु
				अगर (i == 0 && j == 0)
					core->wrap = पंचांगp;
			पूर्ण
		पूर्ण
	पूर्ण

	/* get & parse slave wrappers */
	क्रम (i = 0; i < wrappers[1]; i++) अणु
		u8 hack = (ports[1] == 1) ? 0 : 1;
		क्रम (j = 0; ; j++) अणु
			पंचांगp = bcma_erom_get_addr_desc(bus, eromptr,
				SCAN_ADDR_TYPE_SWRAP, i + hack);
			अगर (IS_ERR_VALUE_U32(पंचांगp)) अणु
				/* no more entries क्रम port _i_ */
				/* pr_debug("erom: master wrapper %d "
				 * has %d descriptors\न", i, j); */
				अवरोध;
			पूर्ण अन्यथा अणु
				अगर (wrappers[0] == 0 && !i && !j)
					core->wrap = पंचांगp;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (bus->hosttype == BCMA_HOSTTYPE_SOC) अणु
		core->io_addr = ioremap(core->addr, BCMA_CORE_SIZE);
		अगर (!core->io_addr)
			वापस -ENOMEM;
		अगर (core->wrap) अणु
			core->io_wrap = ioremap(core->wrap,
							BCMA_CORE_SIZE);
			अगर (!core->io_wrap) अणु
				iounmap(core->io_addr);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम bcma_detect_chip(काष्ठा bcma_bus *bus)
अणु
	s32 पंचांगp;
	काष्ठा bcma_chipinfo *chipinfo = &(bus->chipinfo);
	अक्षर chip_id[8];

	bcma_scan_चयन_core(bus, BCMA_ADDR_BASE);

	पंचांगp = bcma_scan_पढ़ो32(bus, 0, BCMA_CC_ID);
	chipinfo->id = (पंचांगp & BCMA_CC_ID_ID) >> BCMA_CC_ID_ID_SHIFT;
	chipinfo->rev = (पंचांगp & BCMA_CC_ID_REV) >> BCMA_CC_ID_REV_SHIFT;
	chipinfo->pkg = (पंचांगp & BCMA_CC_ID_PKG) >> BCMA_CC_ID_PKG_SHIFT;

	snम_लिखो(chip_id, ARRAY_SIZE(chip_id),
		 (chipinfo->id > 0x9999) ? "%d" : "0x%04X", chipinfo->id);
	bcma_info(bus, "Found chip with id %s, rev 0x%02X and package 0x%02X\n",
		  chip_id, chipinfo->rev, chipinfo->pkg);
पूर्ण

पूर्णांक bcma_bus_scan(काष्ठा bcma_bus *bus)
अणु
	u32 erombase;
	u32 __iomem *eromptr, *eromend;

	पूर्णांक err, core_num = 0;

	/* Skip अगर bus was alपढ़ोy scanned (e.g. during early रेजिस्टर) */
	अगर (bus->nr_cores)
		वापस 0;

	erombase = bcma_scan_पढ़ो32(bus, 0, BCMA_CC_EROM);
	अगर (bus->hosttype == BCMA_HOSTTYPE_SOC) अणु
		eromptr = ioremap(erombase, BCMA_CORE_SIZE);
		अगर (!eromptr)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		eromptr = bus->mmio;
	पूर्ण

	eromend = eromptr + BCMA_CORE_SIZE / माप(u32);

	bcma_scan_चयन_core(bus, erombase);

	जबतक (eromptr < eromend) अणु
		काष्ठा bcma_device *other_core;
		काष्ठा bcma_device *core = kzalloc(माप(*core), GFP_KERNEL);
		अगर (!core) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		INIT_LIST_HEAD(&core->list);
		core->bus = bus;

		err = bcma_get_next_core(bus, &eromptr, शून्य, core_num, core);
		अगर (err < 0) अणु
			kमुक्त(core);
			अगर (err == -ENODEV) अणु
				core_num++;
				जारी;
			पूर्ण अन्यथा अगर (err == -ENXIO) अणु
				जारी;
			पूर्ण अन्यथा अगर (err == -ESPIPE) अणु
				अवरोध;
			पूर्ण
			जाओ out;
		पूर्ण

		core->core_index = core_num++;
		bus->nr_cores++;
		other_core = bcma_find_core_reverse(bus, core->id.id);
		core->core_unit = (other_core == शून्य) ? 0 : other_core->core_unit + 1;
		bcma_prepare_core(bus, core);

		bcma_info(bus, "Core %d found: %s (manuf 0x%03X, id 0x%03X, rev 0x%02X, class 0x%X)\n",
			  core->core_index, bcma_device_name(&core->id),
			  core->id.manuf, core->id.id, core->id.rev,
			  core->id.class);

		list_add_tail(&core->list, &bus->cores);
	पूर्ण

	err = 0;
out:
	अगर (bus->hosttype == BCMA_HOSTTYPE_SOC)
		iounmap(eromptr);

	वापस err;
पूर्ण
