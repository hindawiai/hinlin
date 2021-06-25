<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_BCMA_H_
#घोषणा LINUX_BCMA_H_

#समावेश <linux/pci.h>
#समावेश <linux/mod_devicetable.h>

#समावेश <linux/bcma/bcma_driver_arm_c9.h>
#समावेश <linux/bcma/bcma_driver_chipcommon.h>
#समावेश <linux/bcma/bcma_driver_pci.h>
#समावेश <linux/bcma/bcma_driver_pcie2.h>
#समावेश <linux/bcma/bcma_driver_mips.h>
#समावेश <linux/bcma/bcma_driver_gmac_cmn.h>
#समावेश <linux/ssb/ssb.h> /* SPROM sharing */

#समावेश <linux/bcma/bcma_regs.h>

काष्ठा bcma_device;
काष्ठा bcma_bus;

क्रमागत bcma_hosttype अणु
	BCMA_HOSTTYPE_PCI,
	BCMA_HOSTTYPE_SDIO,
	BCMA_HOSTTYPE_SOC,
पूर्ण;

काष्ठा bcma_chipinfo अणु
	u16 id;
	u8 rev;
	u8 pkg;
पूर्ण;

काष्ठा bcma_boardinfo अणु
	u16 venकरोr;
	u16 type;
पूर्ण;

क्रमागत bcma_clkmode अणु
	BCMA_CLKMODE_FAST,
	BCMA_CLKMODE_DYNAMIC,
पूर्ण;

काष्ठा bcma_host_ops अणु
	u8 (*पढ़ो8)(काष्ठा bcma_device *core, u16 offset);
	u16 (*पढ़ो16)(काष्ठा bcma_device *core, u16 offset);
	u32 (*पढ़ो32)(काष्ठा bcma_device *core, u16 offset);
	व्योम (*ग_लिखो8)(काष्ठा bcma_device *core, u16 offset, u8 value);
	व्योम (*ग_लिखो16)(काष्ठा bcma_device *core, u16 offset, u16 value);
	व्योम (*ग_लिखो32)(काष्ठा bcma_device *core, u16 offset, u32 value);
#अगर_घोषित CONFIG_BCMA_BLOCKIO
	व्योम (*block_पढ़ो)(काष्ठा bcma_device *core, व्योम *buffer,
			   माप_प्रकार count, u16 offset, u8 reg_width);
	व्योम (*block_ग_लिखो)(काष्ठा bcma_device *core, स्थिर व्योम *buffer,
			    माप_प्रकार count, u16 offset, u8 reg_width);
#पूर्ण_अगर
	/* Agent ops */
	u32 (*aपढ़ो32)(काष्ठा bcma_device *core, u16 offset);
	व्योम (*aग_लिखो32)(काष्ठा bcma_device *core, u16 offset, u32 value);
पूर्ण;

/* Core manufacturers */
#घोषणा BCMA_MANUF_ARM			0x43B
#घोषणा BCMA_MANUF_MIPS			0x4A7
#घोषणा BCMA_MANUF_BCM			0x4BF

/* Core class values. */
#घोषणा BCMA_CL_SIM			0x0
#घोषणा BCMA_CL_EROM			0x1
#घोषणा BCMA_CL_CORESIGHT		0x9
#घोषणा BCMA_CL_VERIF			0xB
#घोषणा BCMA_CL_OPTIMO			0xD
#घोषणा BCMA_CL_GEN			0xE
#घोषणा BCMA_CL_PRIMECELL		0xF

/* Core-ID values. */
#घोषणा BCMA_CORE_OOB_ROUTER		0x367	/* Out of band */
#घोषणा BCMA_CORE_4706_CHIPCOMMON	0x500
#घोषणा BCMA_CORE_NS_PCIEG2		0x501
#घोषणा BCMA_CORE_NS_DMA		0x502
#घोषणा BCMA_CORE_NS_SDIO3		0x503
#घोषणा BCMA_CORE_NS_USB20		0x504
#घोषणा BCMA_CORE_NS_USB30		0x505
#घोषणा BCMA_CORE_NS_A9JTAG		0x506
#घोषणा BCMA_CORE_NS_DDR23		0x507
#घोषणा BCMA_CORE_NS_ROM		0x508
#घोषणा BCMA_CORE_NS_न_अंकD		0x509
#घोषणा BCMA_CORE_NS_QSPI		0x50A
#घोषणा BCMA_CORE_NS_CHIPCOMMON_B	0x50B
#घोषणा BCMA_CORE_4706_SOC_RAM		0x50E
#घोषणा BCMA_CORE_ARMCA9		0x510
#घोषणा BCMA_CORE_4706_MAC_GBIT		0x52D
#घोषणा BCMA_CORE_AMEMC			0x52E	/* DDR1/2 memory controller core */
#घोषणा BCMA_CORE_ALTA			0x534	/* I2S core */
#घोषणा BCMA_CORE_4706_MAC_GBIT_COMMON	0x5DC
#घोषणा BCMA_CORE_DDR23_PHY		0x5DD
#घोषणा BCMA_CORE_INVALID		0x700
#घोषणा BCMA_CORE_CHIPCOMMON		0x800
#घोषणा BCMA_CORE_ILINE20		0x801
#घोषणा BCMA_CORE_SRAM			0x802
#घोषणा BCMA_CORE_SDRAM			0x803
#घोषणा BCMA_CORE_PCI			0x804
#घोषणा BCMA_CORE_MIPS			0x805
#घोषणा BCMA_CORE_ETHERNET		0x806
#घोषणा BCMA_CORE_V90			0x807
#घोषणा BCMA_CORE_USB11_HOSTDEV		0x808
#घोषणा BCMA_CORE_ADSL			0x809
#घोषणा BCMA_CORE_ILINE100		0x80A
#घोषणा BCMA_CORE_IPSEC			0x80B
#घोषणा BCMA_CORE_UTOPIA		0x80C
#घोषणा BCMA_CORE_PCMCIA		0x80D
#घोषणा BCMA_CORE_INTERNAL_MEM		0x80E
#घोषणा BCMA_CORE_MEMC_SDRAM		0x80F
#घोषणा BCMA_CORE_OFDM			0x810
#घोषणा BCMA_CORE_EXTIF			0x811
#घोषणा BCMA_CORE_80211			0x812
#घोषणा BCMA_CORE_PHY_A			0x813
#घोषणा BCMA_CORE_PHY_B			0x814
#घोषणा BCMA_CORE_PHY_G			0x815
#घोषणा BCMA_CORE_MIPS_3302		0x816
#घोषणा BCMA_CORE_USB11_HOST		0x817
#घोषणा BCMA_CORE_USB11_DEV		0x818
#घोषणा BCMA_CORE_USB20_HOST		0x819
#घोषणा BCMA_CORE_USB20_DEV		0x81A
#घोषणा BCMA_CORE_SDIO_HOST		0x81B
#घोषणा BCMA_CORE_ROBOSWITCH		0x81C
#घोषणा BCMA_CORE_PARA_ATA		0x81D
#घोषणा BCMA_CORE_SATA_XORDMA		0x81E
#घोषणा BCMA_CORE_ETHERNET_GBIT		0x81F
#घोषणा BCMA_CORE_PCIE			0x820
#घोषणा BCMA_CORE_PHY_N			0x821
#घोषणा BCMA_CORE_SRAM_CTL		0x822
#घोषणा BCMA_CORE_MINI_MACPHY		0x823
#घोषणा BCMA_CORE_ARM_1176		0x824
#घोषणा BCMA_CORE_ARM_7TDMI		0x825
#घोषणा BCMA_CORE_PHY_LP		0x826
#घोषणा BCMA_CORE_PMU			0x827
#घोषणा BCMA_CORE_PHY_SSN		0x828
#घोषणा BCMA_CORE_SDIO_DEV		0x829
#घोषणा BCMA_CORE_ARM_CM3		0x82A
#घोषणा BCMA_CORE_PHY_HT		0x82B
#घोषणा BCMA_CORE_MIPS_74K		0x82C
#घोषणा BCMA_CORE_MAC_GBIT		0x82D
#घोषणा BCMA_CORE_DDR12_MEM_CTL		0x82E
#घोषणा BCMA_CORE_PCIE_RC		0x82F	/* PCIe Root Complex */
#घोषणा BCMA_CORE_OCP_OCP_BRIDGE	0x830
#घोषणा BCMA_CORE_SHARED_COMMON		0x831
#घोषणा BCMA_CORE_OCP_AHB_BRIDGE	0x832
#घोषणा BCMA_CORE_SPI_HOST		0x833
#घोषणा BCMA_CORE_I2S			0x834
#घोषणा BCMA_CORE_SDR_DDR1_MEM_CTL	0x835	/* SDR/DDR1 memory controller core */
#घोषणा BCMA_CORE_SHIM			0x837	/* SHIM component in ubus/6362 */
#घोषणा BCMA_CORE_PHY_AC		0x83B
#घोषणा BCMA_CORE_PCIE2			0x83C	/* PCI Express Gen2 */
#घोषणा BCMA_CORE_USB30_DEV		0x83D
#घोषणा BCMA_CORE_ARM_CR4		0x83E
#घोषणा BCMA_CORE_GCI			0x840
#घोषणा BCMA_CORE_CMEM			0x846	/* CNDS DDR2/3 memory controller */
#घोषणा BCMA_CORE_ARM_CA7		0x847
#घोषणा BCMA_CORE_SYS_MEM		0x849
#घोषणा BCMA_CORE_DEFAULT		0xFFF

#घोषणा BCMA_MAX_NR_CORES		16
#घोषणा BCMA_CORE_SIZE			0x1000

/* Chip IDs of PCIe devices */
#घोषणा BCMA_CHIP_ID_BCM4313	0x4313
#घोषणा BCMA_CHIP_ID_BCM43142	43142
#घोषणा BCMA_CHIP_ID_BCM43131	43131
#घोषणा BCMA_CHIP_ID_BCM43217	43217
#घोषणा BCMA_CHIP_ID_BCM43222	43222
#घोषणा BCMA_CHIP_ID_BCM43224	43224
#घोषणा  BCMA_PKG_ID_BCM43224_FAB_CSM	0x8
#घोषणा  BCMA_PKG_ID_BCM43224_FAB_SMIC	0xa
#घोषणा BCMA_CHIP_ID_BCM43225	43225
#घोषणा BCMA_CHIP_ID_BCM43227	43227
#घोषणा BCMA_CHIP_ID_BCM43228	43228
#घोषणा BCMA_CHIP_ID_BCM43421	43421
#घोषणा BCMA_CHIP_ID_BCM43428	43428
#घोषणा BCMA_CHIP_ID_BCM43431	43431
#घोषणा BCMA_CHIP_ID_BCM43460	43460
#घोषणा BCMA_CHIP_ID_BCM4331	0x4331
#घोषणा BCMA_CHIP_ID_BCM6362	0x6362
#घोषणा BCMA_CHIP_ID_BCM4360	0x4360
#घोषणा BCMA_CHIP_ID_BCM4352	0x4352

/* Chip IDs of SoCs */
#घोषणा BCMA_CHIP_ID_BCM4706	0x5300
#घोषणा  BCMA_PKG_ID_BCM4706L	1
#घोषणा BCMA_CHIP_ID_BCM4716	0x4716
#घोषणा  BCMA_PKG_ID_BCM4716	8
#घोषणा  BCMA_PKG_ID_BCM4717	9
#घोषणा  BCMA_PKG_ID_BCM4718	10
#घोषणा BCMA_CHIP_ID_BCM47162	47162
#घोषणा BCMA_CHIP_ID_BCM4748	0x4748
#घोषणा BCMA_CHIP_ID_BCM4749	0x4749
#घोषणा BCMA_CHIP_ID_BCM5356	0x5356
#घोषणा BCMA_CHIP_ID_BCM5357	0x5357
#घोषणा  BCMA_PKG_ID_BCM5358	9
#घोषणा  BCMA_PKG_ID_BCM47186	10
#घोषणा  BCMA_PKG_ID_BCM5357	11
#घोषणा BCMA_CHIP_ID_BCM53572	53572
#घोषणा  BCMA_PKG_ID_BCM47188	9
#घोषणा BCMA_CHIP_ID_BCM4707	53010
#घोषणा  BCMA_PKG_ID_BCM4707	1
#घोषणा  BCMA_PKG_ID_BCM4708	2
#घोषणा  BCMA_PKG_ID_BCM4709	0
#घोषणा BCMA_CHIP_ID_BCM47094	53030
#घोषणा BCMA_CHIP_ID_BCM53018	53018
#घोषणा BCMA_CHIP_ID_BCM53573	53573
#घोषणा  BCMA_PKG_ID_BCM53573	0
#घोषणा  BCMA_PKG_ID_BCM47189	1

/* Board types (on PCI usually equals to the subप्रणाली dev id) */
/* BCM4313 */
#घोषणा BCMA_BOARD_TYPE_BCM94313BU	0X050F
#घोषणा BCMA_BOARD_TYPE_BCM94313HM	0X0510
#घोषणा BCMA_BOARD_TYPE_BCM94313EPA	0X0511
#घोषणा BCMA_BOARD_TYPE_BCM94313HMG	0X051C
/* BCM4716 */
#घोषणा BCMA_BOARD_TYPE_BCM94716NR2	0X04CD
/* BCM43224 */
#घोषणा BCMA_BOARD_TYPE_BCM943224X21	0X056E
#घोषणा BCMA_BOARD_TYPE_BCM943224X21_FCC	0X00D1
#घोषणा BCMA_BOARD_TYPE_BCM943224X21B	0X00E9
#घोषणा BCMA_BOARD_TYPE_BCM943224M93	0X008B
#घोषणा BCMA_BOARD_TYPE_BCM943224M93A	0X0090
#घोषणा BCMA_BOARD_TYPE_BCM943224X16	0X0093
#घोषणा BCMA_BOARD_TYPE_BCM94322X9	0X008D
#घोषणा BCMA_BOARD_TYPE_BCM94322M35E	0X008E
/* BCM43228 */
#घोषणा BCMA_BOARD_TYPE_BCM943228BU8	0X0540
#घोषणा BCMA_BOARD_TYPE_BCM943228BU9	0X0541
#घोषणा BCMA_BOARD_TYPE_BCM943228BU	0X0542
#घोषणा BCMA_BOARD_TYPE_BCM943227HM4L	0X0543
#घोषणा BCMA_BOARD_TYPE_BCM943227HMB	0X0544
#घोषणा BCMA_BOARD_TYPE_BCM943228HM4L	0X0545
#घोषणा BCMA_BOARD_TYPE_BCM943228SD	0X0573
/* BCM4331 */
#घोषणा BCMA_BOARD_TYPE_BCM94331X19	0X00D6
#घोषणा BCMA_BOARD_TYPE_BCM94331X28	0X00E4
#घोषणा BCMA_BOARD_TYPE_BCM94331X28B	0X010E
#घोषणा BCMA_BOARD_TYPE_BCM94331PCIEBT3AX	0X00E4
#घोषणा BCMA_BOARD_TYPE_BCM94331X12_2G	0X00EC
#घोषणा BCMA_BOARD_TYPE_BCM94331X12_5G	0X00ED
#घोषणा BCMA_BOARD_TYPE_BCM94331X29B	0X00EF
#घोषणा BCMA_BOARD_TYPE_BCM94331CSAX	0X00EF
#घोषणा BCMA_BOARD_TYPE_BCM94331X19C	0X00F5
#घोषणा BCMA_BOARD_TYPE_BCM94331X33	0X00F4
#घोषणा BCMA_BOARD_TYPE_BCM94331BU	0X0523
#घोषणा BCMA_BOARD_TYPE_BCM94331S9BU	0X0524
#घोषणा BCMA_BOARD_TYPE_BCM94331MC	0X0525
#घोषणा BCMA_BOARD_TYPE_BCM94331MCI	0X0526
#घोषणा BCMA_BOARD_TYPE_BCM94331PCIEBT4	0X0527
#घोषणा BCMA_BOARD_TYPE_BCM94331HM	0X0574
#घोषणा BCMA_BOARD_TYPE_BCM94331PCIEDUAL	0X059B
#घोषणा BCMA_BOARD_TYPE_BCM94331MCH5	0X05A9
#घोषणा BCMA_BOARD_TYPE_BCM94331CS	0X05C6
#घोषणा BCMA_BOARD_TYPE_BCM94331CD	0X05DA
/* BCM53572 */
#घोषणा BCMA_BOARD_TYPE_BCM953572BU	0X058D
#घोषणा BCMA_BOARD_TYPE_BCM953572NR2	0X058E
#घोषणा BCMA_BOARD_TYPE_BCM947188NR2	0X058F
#घोषणा BCMA_BOARD_TYPE_BCM953572SDRNR2	0X0590
/* BCM43142 */
#घोषणा BCMA_BOARD_TYPE_BCM943142HM	0X05E0

काष्ठा bcma_device अणु
	काष्ठा bcma_bus *bus;
	काष्ठा bcma_device_id id;

	काष्ठा device dev;
	काष्ठा device *dma_dev;

	अचिन्हित पूर्णांक irq;
	bool dev_रेजिस्टरed;

	u8 core_index;
	u8 core_unit;

	u32 addr;
	u32 addr_s[8];
	u32 wrap;

	व्योम __iomem *io_addr;
	व्योम __iomem *io_wrap;

	व्योम *drvdata;
	काष्ठा list_head list;
पूर्ण;

अटल अंतरभूत व्योम *bcma_get_drvdata(काष्ठा bcma_device *core)
अणु
	वापस core->drvdata;
पूर्ण
अटल अंतरभूत व्योम bcma_set_drvdata(काष्ठा bcma_device *core, व्योम *drvdata)
अणु
	core->drvdata = drvdata;
पूर्ण

काष्ठा bcma_driver अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा bcma_device_id *id_table;

	पूर्णांक (*probe)(काष्ठा bcma_device *dev);
	व्योम (*हटाओ)(काष्ठा bcma_device *dev);
	पूर्णांक (*suspend)(काष्ठा bcma_device *dev);
	पूर्णांक (*resume)(काष्ठा bcma_device *dev);
	व्योम (*shutकरोwn)(काष्ठा bcma_device *dev);

	काष्ठा device_driver drv;
पूर्ण;
बाह्य
पूर्णांक __bcma_driver_रेजिस्टर(काष्ठा bcma_driver *drv, काष्ठा module *owner);
#घोषणा bcma_driver_रेजिस्टर(drv) \
	__bcma_driver_रेजिस्टर(drv, THIS_MODULE)

बाह्य व्योम bcma_driver_unरेजिस्टर(काष्ठा bcma_driver *drv);

/* module_bcma_driver() - Helper macro क्रम drivers that करोn't करो
 * anything special in module init/निकास.  This eliminates a lot of
 * boilerplate.  Each module may only use this macro once, and
 * calling it replaces module_init() and module_निकास()
 */
#घोषणा module_bcma_driver(__bcma_driver) \
	module_driver(__bcma_driver, bcma_driver_रेजिस्टर, \
			bcma_driver_unरेजिस्टर)

/* Set a fallback SPROM.
 * See kकरोc at the function definition क्रम complete करोcumentation. */
बाह्य पूर्णांक bcma_arch_रेजिस्टर_fallback_sprom(
		पूर्णांक (*sprom_callback)(काष्ठा bcma_bus *bus,
		काष्ठा ssb_sprom *out));

काष्ठा bcma_bus अणु
	काष्ठा device *dev;

	/* The MMIO area. */
	व्योम __iomem *mmio;

	स्थिर काष्ठा bcma_host_ops *ops;

	क्रमागत bcma_hosttype hosttype;
	bool host_is_pcie2; /* Used क्रम BCMA_HOSTTYPE_PCI only */
	काष्ठा pci_dev *host_pci; /* PCI bus poपूर्णांकer (BCMA_HOSTTYPE_PCI only) */

	काष्ठा bcma_chipinfo chipinfo;

	काष्ठा bcma_boardinfo boardinfo;

	काष्ठा bcma_device *mapped_core;
	काष्ठा list_head cores;
	u8 nr_cores;
	u8 num;

	काष्ठा bcma_drv_cc drv_cc;
	काष्ठा bcma_drv_cc_b drv_cc_b;
	काष्ठा bcma_drv_pci drv_pci[2];
	काष्ठा bcma_drv_pcie2 drv_pcie2;
	काष्ठा bcma_drv_mips drv_mips;
	काष्ठा bcma_drv_gmac_cmn drv_gmac_cmn;

	/* We decided to share SPROM काष्ठा with SSB as दीर्घ as we करो not need
	 * any hacks क्रम BCMA. This simplअगरies drivers code. */
	काष्ठा ssb_sprom sprom;
पूर्ण;

अटल अंतरभूत u32 bcma_पढ़ो8(काष्ठा bcma_device *core, u16 offset)
अणु
	वापस core->bus->ops->पढ़ो8(core, offset);
पूर्ण
अटल अंतरभूत u32 bcma_पढ़ो16(काष्ठा bcma_device *core, u16 offset)
अणु
	वापस core->bus->ops->पढ़ो16(core, offset);
पूर्ण
अटल अंतरभूत u32 bcma_पढ़ो32(काष्ठा bcma_device *core, u16 offset)
अणु
	वापस core->bus->ops->पढ़ो32(core, offset);
पूर्ण
अटल अंतरभूत
व्योम bcma_ग_लिखो8(काष्ठा bcma_device *core, u16 offset, u32 value)
अणु
	core->bus->ops->ग_लिखो8(core, offset, value);
पूर्ण
अटल अंतरभूत
व्योम bcma_ग_लिखो16(काष्ठा bcma_device *core, u16 offset, u32 value)
अणु
	core->bus->ops->ग_लिखो16(core, offset, value);
पूर्ण
अटल अंतरभूत
व्योम bcma_ग_लिखो32(काष्ठा bcma_device *core, u16 offset, u32 value)
अणु
	core->bus->ops->ग_लिखो32(core, offset, value);
पूर्ण
#अगर_घोषित CONFIG_BCMA_BLOCKIO
अटल अंतरभूत व्योम bcma_block_पढ़ो(काष्ठा bcma_device *core, व्योम *buffer,
				   माप_प्रकार count, u16 offset, u8 reg_width)
अणु
	core->bus->ops->block_पढ़ो(core, buffer, count, offset, reg_width);
पूर्ण
अटल अंतरभूत व्योम bcma_block_ग_लिखो(काष्ठा bcma_device *core,
				    स्थिर व्योम *buffer, माप_प्रकार count,
				    u16 offset, u8 reg_width)
अणु
	core->bus->ops->block_ग_लिखो(core, buffer, count, offset, reg_width);
पूर्ण
#पूर्ण_अगर
अटल अंतरभूत u32 bcma_aपढ़ो32(काष्ठा bcma_device *core, u16 offset)
अणु
	वापस core->bus->ops->aपढ़ो32(core, offset);
पूर्ण
अटल अंतरभूत
व्योम bcma_aग_लिखो32(काष्ठा bcma_device *core, u16 offset, u32 value)
अणु
	core->bus->ops->aग_लिखो32(core, offset, value);
पूर्ण

अटल अंतरभूत व्योम bcma_mask32(काष्ठा bcma_device *cc, u16 offset, u32 mask)
अणु
	bcma_ग_लिखो32(cc, offset, bcma_पढ़ो32(cc, offset) & mask);
पूर्ण
अटल अंतरभूत व्योम bcma_set32(काष्ठा bcma_device *cc, u16 offset, u32 set)
अणु
	bcma_ग_लिखो32(cc, offset, bcma_पढ़ो32(cc, offset) | set);
पूर्ण
अटल अंतरभूत व्योम bcma_maskset32(काष्ठा bcma_device *cc,
				  u16 offset, u32 mask, u32 set)
अणु
	bcma_ग_लिखो32(cc, offset, (bcma_पढ़ो32(cc, offset) & mask) | set);
पूर्ण
अटल अंतरभूत व्योम bcma_mask16(काष्ठा bcma_device *cc, u16 offset, u16 mask)
अणु
	bcma_ग_लिखो16(cc, offset, bcma_पढ़ो16(cc, offset) & mask);
पूर्ण
अटल अंतरभूत व्योम bcma_set16(काष्ठा bcma_device *cc, u16 offset, u16 set)
अणु
	bcma_ग_लिखो16(cc, offset, bcma_पढ़ो16(cc, offset) | set);
पूर्ण
अटल अंतरभूत व्योम bcma_maskset16(काष्ठा bcma_device *cc,
				  u16 offset, u16 mask, u16 set)
अणु
	bcma_ग_लिखो16(cc, offset, (bcma_पढ़ो16(cc, offset) & mask) | set);
पूर्ण

बाह्य काष्ठा bcma_device *bcma_find_core_unit(काष्ठा bcma_bus *bus, u16 coreid,
					       u8 unit);
अटल अंतरभूत काष्ठा bcma_device *bcma_find_core(काष्ठा bcma_bus *bus,
						 u16 coreid)
अणु
	वापस bcma_find_core_unit(bus, coreid, 0);
पूर्ण

#अगर_घोषित CONFIG_BCMA_HOST_PCI
बाह्य व्योम bcma_host_pci_up(काष्ठा bcma_bus *bus);
बाह्य व्योम bcma_host_pci_करोwn(काष्ठा bcma_bus *bus);
बाह्य पूर्णांक bcma_host_pci_irq_ctl(काष्ठा bcma_bus *bus,
				 काष्ठा bcma_device *core, bool enable);
#अन्यथा
अटल अंतरभूत व्योम bcma_host_pci_up(काष्ठा bcma_bus *bus)
अणु
पूर्ण
अटल अंतरभूत व्योम bcma_host_pci_करोwn(काष्ठा bcma_bus *bus)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक bcma_host_pci_irq_ctl(काष्ठा bcma_bus *bus,
					काष्ठा bcma_device *core, bool enable)
अणु
	अगर (bus->hosttype == BCMA_HOSTTYPE_PCI)
		वापस -ENOTSUPP;
	वापस 0;
पूर्ण
#पूर्ण_अगर

बाह्य bool bcma_core_is_enabled(काष्ठा bcma_device *core);
बाह्य व्योम bcma_core_disable(काष्ठा bcma_device *core, u32 flags);
बाह्य पूर्णांक bcma_core_enable(काष्ठा bcma_device *core, u32 flags);
बाह्य व्योम bcma_core_set_घड़ीmode(काष्ठा bcma_device *core,
				    क्रमागत bcma_clkmode clkmode);
बाह्य व्योम bcma_core_pll_ctl(काष्ठा bcma_device *core, u32 req, u32 status,
			      bool on);
बाह्य u32 bcma_chipco_pll_पढ़ो(काष्ठा bcma_drv_cc *cc, u32 offset);
#घोषणा BCMA_DMA_TRANSLATION_MASK	0xC0000000
#घोषणा  BCMA_DMA_TRANSLATION_NONE	0x00000000
#घोषणा  BCMA_DMA_TRANSLATION_DMA32_CMT	0x40000000 /* Client Mode Translation क्रम 32-bit DMA */
#घोषणा  BCMA_DMA_TRANSLATION_DMA64_CMT	0x80000000 /* Client Mode Translation क्रम 64-bit DMA */
बाह्य u32 bcma_core_dma_translation(काष्ठा bcma_device *core);

बाह्य अचिन्हित पूर्णांक bcma_core_irq(काष्ठा bcma_device *core, पूर्णांक num);

#पूर्ण_अगर /* LINUX_BCMA_H_ */
