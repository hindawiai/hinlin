<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014 Hauke Mehrtens <hauke@hauke-m.de>
 * Copyright (C) 2015 Broadcom Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci-ecam.h>
#समावेश <linux/msi.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/mbus.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqchip/arm-gic-v3.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/phy.h>

#समावेश "pcie-iproc.h"

#घोषणा EP_PERST_SOURCE_SELECT_SHIFT	2
#घोषणा EP_PERST_SOURCE_SELECT		BIT(EP_PERST_SOURCE_SELECT_SHIFT)
#घोषणा EP_MODE_SURVIVE_PERST_SHIFT	1
#घोषणा EP_MODE_SURVIVE_PERST		BIT(EP_MODE_SURVIVE_PERST_SHIFT)
#घोषणा RC_PCIE_RST_OUTPUT_SHIFT	0
#घोषणा RC_PCIE_RST_OUTPUT		BIT(RC_PCIE_RST_OUTPUT_SHIFT)
#घोषणा PAXC_RESET_MASK			0x7f

#घोषणा GIC_V3_CFG_SHIFT		0
#घोषणा GIC_V3_CFG			BIT(GIC_V3_CFG_SHIFT)

#घोषणा MSI_ENABLE_CFG_SHIFT		0
#घोषणा MSI_ENABLE_CFG			BIT(MSI_ENABLE_CFG_SHIFT)

#घोषणा CFG_IND_ADDR_MASK		0x00001ffc

#घोषणा CFG_ADDR_REG_NUM_MASK		0x00000ffc
#घोषणा CFG_ADDR_CFG_TYPE_1		1

#घोषणा SYS_RC_INTX_MASK		0xf

#घोषणा PCIE_PHYLINKUP_SHIFT		3
#घोषणा PCIE_PHYLINKUP			BIT(PCIE_PHYLINKUP_SHIFT)
#घोषणा PCIE_DL_ACTIVE_SHIFT		2
#घोषणा PCIE_DL_ACTIVE			BIT(PCIE_DL_ACTIVE_SHIFT)

#घोषणा APB_ERR_EN_SHIFT		0
#घोषणा APB_ERR_EN			BIT(APB_ERR_EN_SHIFT)

#घोषणा CFG_RD_SUCCESS			0
#घोषणा CFG_RD_UR			1
#घोषणा CFG_RD_CRS			2
#घोषणा CFG_RD_CA			3
#घोषणा CFG_RETRY_STATUS		0xffff0001
#घोषणा CFG_RETRY_STATUS_TIMEOUT_US	500000 /* 500 milliseconds */

/* derive the क्रमागत index of the outbound/inbound mapping रेजिस्टरs */
#घोषणा MAP_REG(base_reg, index)	((base_reg) + (index) * 2)

/*
 * Maximum number of outbound mapping winकरोw sizes that can be supported by any
 * OARR/OMAP mapping pair
 */
#घोषणा MAX_NUM_OB_WINDOW_SIZES		4

#घोषणा OARR_VALID_SHIFT		0
#घोषणा OARR_VALID			BIT(OARR_VALID_SHIFT)
#घोषणा OARR_SIZE_CFG_SHIFT		1

/*
 * Maximum number of inbound mapping region sizes that can be supported by an
 * IARR
 */
#घोषणा MAX_NUM_IB_REGION_SIZES		9

#घोषणा IMAP_VALID_SHIFT		0
#घोषणा IMAP_VALID			BIT(IMAP_VALID_SHIFT)

#घोषणा IPROC_PCI_PM_CAP		0x48
#घोषणा IPROC_PCI_PM_CAP_MASK		0xffff
#घोषणा IPROC_PCI_EXP_CAP		0xac

#घोषणा IPROC_PCIE_REG_INVALID		0xffff

/**
 * iProc PCIe outbound mapping controller specअगरic parameters
 *
 * @winकरोw_sizes: list of supported outbound mapping winकरोw sizes in MB
 * @nr_sizes: number of supported outbound mapping winकरोw sizes
 */
काष्ठा iproc_pcie_ob_map अणु
	resource_माप_प्रकार winकरोw_sizes[MAX_NUM_OB_WINDOW_SIZES];
	अचिन्हित पूर्णांक nr_sizes;
पूर्ण;

अटल स्थिर काष्ठा iproc_pcie_ob_map paxb_ob_map[] = अणु
	अणु
		/* OARR0/OMAP0 */
		.winकरोw_sizes = अणु 128, 256 पूर्ण,
		.nr_sizes = 2,
	पूर्ण,
	अणु
		/* OARR1/OMAP1 */
		.winकरोw_sizes = अणु 128, 256 पूर्ण,
		.nr_sizes = 2,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iproc_pcie_ob_map paxb_v2_ob_map[] = अणु
	अणु
		/* OARR0/OMAP0 */
		.winकरोw_sizes = अणु 128, 256 पूर्ण,
		.nr_sizes = 2,
	पूर्ण,
	अणु
		/* OARR1/OMAP1 */
		.winकरोw_sizes = अणु 128, 256 पूर्ण,
		.nr_sizes = 2,
	पूर्ण,
	अणु
		/* OARR2/OMAP2 */
		.winकरोw_sizes = अणु 128, 256, 512, 1024 पूर्ण,
		.nr_sizes = 4,
	पूर्ण,
	अणु
		/* OARR3/OMAP3 */
		.winकरोw_sizes = अणु 128, 256, 512, 1024 पूर्ण,
		.nr_sizes = 4,
	पूर्ण,
पूर्ण;

/**
 * iProc PCIe inbound mapping type
 */
क्रमागत iproc_pcie_ib_map_type अणु
	/* क्रम DDR memory */
	IPROC_PCIE_IB_MAP_MEM = 0,

	/* क्रम device I/O memory */
	IPROC_PCIE_IB_MAP_IO,

	/* invalid or unused */
	IPROC_PCIE_IB_MAP_INVALID
पूर्ण;

/**
 * iProc PCIe inbound mapping controller specअगरic parameters
 *
 * @type: inbound mapping region type
 * @size_unit: inbound mapping region size unit, could be SZ_1K, SZ_1M, or
 * SZ_1G
 * @region_sizes: list of supported inbound mapping region sizes in KB, MB, or
 * GB, depending on the size unit
 * @nr_sizes: number of supported inbound mapping region sizes
 * @nr_winकरोws: number of supported inbound mapping winकरोws क्रम the region
 * @imap_addr_offset: रेजिस्टर offset between the upper and lower 32-bit
 * IMAP address रेजिस्टरs
 * @imap_winकरोw_offset: रेजिस्टर offset between each IMAP winकरोw
 */
काष्ठा iproc_pcie_ib_map अणु
	क्रमागत iproc_pcie_ib_map_type type;
	अचिन्हित पूर्णांक size_unit;
	resource_माप_प्रकार region_sizes[MAX_NUM_IB_REGION_SIZES];
	अचिन्हित पूर्णांक nr_sizes;
	अचिन्हित पूर्णांक nr_winकरोws;
	u16 imap_addr_offset;
	u16 imap_winकरोw_offset;
पूर्ण;

अटल स्थिर काष्ठा iproc_pcie_ib_map paxb_v2_ib_map[] = अणु
	अणु
		/* IARR0/IMAP0 */
		.type = IPROC_PCIE_IB_MAP_IO,
		.size_unit = SZ_1K,
		.region_sizes = अणु 32 पूर्ण,
		.nr_sizes = 1,
		.nr_winकरोws = 8,
		.imap_addr_offset = 0x40,
		.imap_winकरोw_offset = 0x4,
	पूर्ण,
	अणु
		/* IARR1/IMAP1 */
		.type = IPROC_PCIE_IB_MAP_MEM,
		.size_unit = SZ_1M,
		.region_sizes = अणु 8 पूर्ण,
		.nr_sizes = 1,
		.nr_winकरोws = 8,
		.imap_addr_offset = 0x4,
		.imap_winकरोw_offset = 0x8,

	पूर्ण,
	अणु
		/* IARR2/IMAP2 */
		.type = IPROC_PCIE_IB_MAP_MEM,
		.size_unit = SZ_1M,
		.region_sizes = अणु 64, 128, 256, 512, 1024, 2048, 4096, 8192,
				  16384 पूर्ण,
		.nr_sizes = 9,
		.nr_winकरोws = 1,
		.imap_addr_offset = 0x4,
		.imap_winकरोw_offset = 0x8,
	पूर्ण,
	अणु
		/* IARR3/IMAP3 */
		.type = IPROC_PCIE_IB_MAP_MEM,
		.size_unit = SZ_1G,
		.region_sizes = अणु 1, 2, 4, 8, 16, 32 पूर्ण,
		.nr_sizes = 6,
		.nr_winकरोws = 8,
		.imap_addr_offset = 0x4,
		.imap_winकरोw_offset = 0x8,
	पूर्ण,
	अणु
		/* IARR4/IMAP4 */
		.type = IPROC_PCIE_IB_MAP_MEM,
		.size_unit = SZ_1G,
		.region_sizes = अणु 32, 64, 128, 256, 512 पूर्ण,
		.nr_sizes = 5,
		.nr_winकरोws = 8,
		.imap_addr_offset = 0x4,
		.imap_winकरोw_offset = 0x8,
	पूर्ण,
पूर्ण;

/*
 * iProc PCIe host रेजिस्टरs
 */
क्रमागत iproc_pcie_reg अणु
	/* घड़ी/reset संकेत control */
	IPROC_PCIE_CLK_CTRL = 0,

	/*
	 * To allow MSI to be steered to an बाह्यal MSI controller (e.g., ARM
	 * GICv3 ITS)
	 */
	IPROC_PCIE_MSI_GIC_MODE,

	/*
	 * IPROC_PCIE_MSI_BASE_ADDR and IPROC_PCIE_MSI_WINDOW_SIZE define the
	 * winकरोw where the MSI posted ग_लिखोs are written, क्रम the ग_लिखोs to be
	 * पूर्णांकerpreted as MSI ग_लिखोs.
	 */
	IPROC_PCIE_MSI_BASE_ADDR,
	IPROC_PCIE_MSI_WINDOW_SIZE,

	/*
	 * To hold the address of the रेजिस्टर where the MSI ग_लिखोs are
	 * programed.  When ARM GICv3 ITS is used, this should be programmed
	 * with the address of the GITS_TRANSLATER रेजिस्टर.
	 */
	IPROC_PCIE_MSI_ADDR_LO,
	IPROC_PCIE_MSI_ADDR_HI,

	/* enable MSI */
	IPROC_PCIE_MSI_EN_CFG,

	/* allow access to root complex configuration space */
	IPROC_PCIE_CFG_IND_ADDR,
	IPROC_PCIE_CFG_IND_DATA,

	/* allow access to device configuration space */
	IPROC_PCIE_CFG_ADDR,
	IPROC_PCIE_CFG_DATA,

	/* enable INTx */
	IPROC_PCIE_INTX_EN,

	/* outbound address mapping */
	IPROC_PCIE_OARR0,
	IPROC_PCIE_OMAP0,
	IPROC_PCIE_OARR1,
	IPROC_PCIE_OMAP1,
	IPROC_PCIE_OARR2,
	IPROC_PCIE_OMAP2,
	IPROC_PCIE_OARR3,
	IPROC_PCIE_OMAP3,

	/* inbound address mapping */
	IPROC_PCIE_IARR0,
	IPROC_PCIE_IMAP0,
	IPROC_PCIE_IARR1,
	IPROC_PCIE_IMAP1,
	IPROC_PCIE_IARR2,
	IPROC_PCIE_IMAP2,
	IPROC_PCIE_IARR3,
	IPROC_PCIE_IMAP3,
	IPROC_PCIE_IARR4,
	IPROC_PCIE_IMAP4,

	/* config पढ़ो status */
	IPROC_PCIE_CFG_RD_STATUS,

	/* link status */
	IPROC_PCIE_LINK_STATUS,

	/* enable APB error क्रम unsupported requests */
	IPROC_PCIE_APB_ERR_EN,

	/* total number of core रेजिस्टरs */
	IPROC_PCIE_MAX_NUM_REG,
पूर्ण;

/* iProc PCIe PAXB BCMA रेजिस्टरs */
अटल स्थिर u16 iproc_pcie_reg_paxb_bcma[IPROC_PCIE_MAX_NUM_REG] = अणु
	[IPROC_PCIE_CLK_CTRL]		= 0x000,
	[IPROC_PCIE_CFG_IND_ADDR]	= 0x120,
	[IPROC_PCIE_CFG_IND_DATA]	= 0x124,
	[IPROC_PCIE_CFG_ADDR]		= 0x1f8,
	[IPROC_PCIE_CFG_DATA]		= 0x1fc,
	[IPROC_PCIE_INTX_EN]		= 0x330,
	[IPROC_PCIE_LINK_STATUS]	= 0xf0c,
पूर्ण;

/* iProc PCIe PAXB रेजिस्टरs */
अटल स्थिर u16 iproc_pcie_reg_paxb[IPROC_PCIE_MAX_NUM_REG] = अणु
	[IPROC_PCIE_CLK_CTRL]		= 0x000,
	[IPROC_PCIE_CFG_IND_ADDR]	= 0x120,
	[IPROC_PCIE_CFG_IND_DATA]	= 0x124,
	[IPROC_PCIE_CFG_ADDR]		= 0x1f8,
	[IPROC_PCIE_CFG_DATA]		= 0x1fc,
	[IPROC_PCIE_INTX_EN]		= 0x330,
	[IPROC_PCIE_OARR0]		= 0xd20,
	[IPROC_PCIE_OMAP0]		= 0xd40,
	[IPROC_PCIE_OARR1]		= 0xd28,
	[IPROC_PCIE_OMAP1]		= 0xd48,
	[IPROC_PCIE_LINK_STATUS]	= 0xf0c,
	[IPROC_PCIE_APB_ERR_EN]		= 0xf40,
पूर्ण;

/* iProc PCIe PAXB v2 रेजिस्टरs */
अटल स्थिर u16 iproc_pcie_reg_paxb_v2[IPROC_PCIE_MAX_NUM_REG] = अणु
	[IPROC_PCIE_CLK_CTRL]		= 0x000,
	[IPROC_PCIE_CFG_IND_ADDR]	= 0x120,
	[IPROC_PCIE_CFG_IND_DATA]	= 0x124,
	[IPROC_PCIE_CFG_ADDR]		= 0x1f8,
	[IPROC_PCIE_CFG_DATA]		= 0x1fc,
	[IPROC_PCIE_INTX_EN]		= 0x330,
	[IPROC_PCIE_OARR0]		= 0xd20,
	[IPROC_PCIE_OMAP0]		= 0xd40,
	[IPROC_PCIE_OARR1]		= 0xd28,
	[IPROC_PCIE_OMAP1]		= 0xd48,
	[IPROC_PCIE_OARR2]		= 0xd60,
	[IPROC_PCIE_OMAP2]		= 0xd68,
	[IPROC_PCIE_OARR3]		= 0xdf0,
	[IPROC_PCIE_OMAP3]		= 0xdf8,
	[IPROC_PCIE_IARR0]		= 0xd00,
	[IPROC_PCIE_IMAP0]		= 0xc00,
	[IPROC_PCIE_IARR1]		= 0xd08,
	[IPROC_PCIE_IMAP1]		= 0xd70,
	[IPROC_PCIE_IARR2]		= 0xd10,
	[IPROC_PCIE_IMAP2]		= 0xcc0,
	[IPROC_PCIE_IARR3]		= 0xe00,
	[IPROC_PCIE_IMAP3]		= 0xe08,
	[IPROC_PCIE_IARR4]		= 0xe68,
	[IPROC_PCIE_IMAP4]		= 0xe70,
	[IPROC_PCIE_CFG_RD_STATUS]	= 0xee0,
	[IPROC_PCIE_LINK_STATUS]	= 0xf0c,
	[IPROC_PCIE_APB_ERR_EN]		= 0xf40,
पूर्ण;

/* iProc PCIe PAXC v1 रेजिस्टरs */
अटल स्थिर u16 iproc_pcie_reg_paxc[IPROC_PCIE_MAX_NUM_REG] = अणु
	[IPROC_PCIE_CLK_CTRL]		= 0x000,
	[IPROC_PCIE_CFG_IND_ADDR]	= 0x1f0,
	[IPROC_PCIE_CFG_IND_DATA]	= 0x1f4,
	[IPROC_PCIE_CFG_ADDR]		= 0x1f8,
	[IPROC_PCIE_CFG_DATA]		= 0x1fc,
पूर्ण;

/* iProc PCIe PAXC v2 रेजिस्टरs */
अटल स्थिर u16 iproc_pcie_reg_paxc_v2[IPROC_PCIE_MAX_NUM_REG] = अणु
	[IPROC_PCIE_MSI_GIC_MODE]	= 0x050,
	[IPROC_PCIE_MSI_BASE_ADDR]	= 0x074,
	[IPROC_PCIE_MSI_WINDOW_SIZE]	= 0x078,
	[IPROC_PCIE_MSI_ADDR_LO]	= 0x07c,
	[IPROC_PCIE_MSI_ADDR_HI]	= 0x080,
	[IPROC_PCIE_MSI_EN_CFG]		= 0x09c,
	[IPROC_PCIE_CFG_IND_ADDR]	= 0x1f0,
	[IPROC_PCIE_CFG_IND_DATA]	= 0x1f4,
	[IPROC_PCIE_CFG_ADDR]		= 0x1f8,
	[IPROC_PCIE_CFG_DATA]		= 0x1fc,
पूर्ण;

/*
 * List of device IDs of controllers that have corrupted capability list that
 * require SW fixup
 */
अटल स्थिर u16 iproc_pcie_corrupt_cap_did[] = अणु
	0x16cd,
	0x16f0,
	0xd802,
	0xd804
पूर्ण;

अटल अंतरभूत काष्ठा iproc_pcie *iproc_data(काष्ठा pci_bus *bus)
अणु
	काष्ठा iproc_pcie *pcie = bus->sysdata;
	वापस pcie;
पूर्ण

अटल अंतरभूत bool iproc_pcie_reg_is_invalid(u16 reg_offset)
अणु
	वापस !!(reg_offset == IPROC_PCIE_REG_INVALID);
पूर्ण

अटल अंतरभूत u16 iproc_pcie_reg_offset(काष्ठा iproc_pcie *pcie,
					क्रमागत iproc_pcie_reg reg)
अणु
	वापस pcie->reg_offsets[reg];
पूर्ण

अटल अंतरभूत u32 iproc_pcie_पढ़ो_reg(काष्ठा iproc_pcie *pcie,
				      क्रमागत iproc_pcie_reg reg)
अणु
	u16 offset = iproc_pcie_reg_offset(pcie, reg);

	अगर (iproc_pcie_reg_is_invalid(offset))
		वापस 0;

	वापस पढ़ोl(pcie->base + offset);
पूर्ण

अटल अंतरभूत व्योम iproc_pcie_ग_लिखो_reg(काष्ठा iproc_pcie *pcie,
					क्रमागत iproc_pcie_reg reg, u32 val)
अणु
	u16 offset = iproc_pcie_reg_offset(pcie, reg);

	अगर (iproc_pcie_reg_is_invalid(offset))
		वापस;

	ग_लिखोl(val, pcie->base + offset);
पूर्ण

/**
 * APB error क्रमwarding can be disabled during access of configuration
 * रेजिस्टरs of the endpoपूर्णांक device, to prevent unsupported requests
 * (typically seen during क्रमागतeration with multi-function devices) from
 * triggering a प्रणाली exception.
 */
अटल अंतरभूत व्योम iproc_pcie_apb_err_disable(काष्ठा pci_bus *bus,
					      bool disable)
अणु
	काष्ठा iproc_pcie *pcie = iproc_data(bus);
	u32 val;

	अगर (bus->number && pcie->has_apb_err_disable) अणु
		val = iproc_pcie_पढ़ो_reg(pcie, IPROC_PCIE_APB_ERR_EN);
		अगर (disable)
			val &= ~APB_ERR_EN;
		अन्यथा
			val |= APB_ERR_EN;
		iproc_pcie_ग_लिखो_reg(pcie, IPROC_PCIE_APB_ERR_EN, val);
	पूर्ण
पूर्ण

अटल व्योम __iomem *iproc_pcie_map_ep_cfg_reg(काष्ठा iproc_pcie *pcie,
					       अचिन्हित पूर्णांक busno,
					       अचिन्हित पूर्णांक devfn,
					       पूर्णांक where)
अणु
	u16 offset;
	u32 val;

	/* EP device access */
	val = ALIGN_DOWN(PCIE_ECAM_OFFSET(busno, devfn, where), 4) |
		CFG_ADDR_CFG_TYPE_1;

	iproc_pcie_ग_लिखो_reg(pcie, IPROC_PCIE_CFG_ADDR, val);
	offset = iproc_pcie_reg_offset(pcie, IPROC_PCIE_CFG_DATA);

	अगर (iproc_pcie_reg_is_invalid(offset))
		वापस शून्य;

	वापस (pcie->base + offset);
पूर्ण

अटल अचिन्हित पूर्णांक iproc_pcie_cfg_retry(काष्ठा iproc_pcie *pcie,
					 व्योम __iomem *cfg_data_p)
अणु
	पूर्णांक समयout = CFG_RETRY_STATUS_TIMEOUT_US;
	अचिन्हित पूर्णांक data;
	u32 status;

	/*
	 * As per PCIe spec r3.1, sec 2.3.2, CRS Software Visibility only
	 * affects config पढ़ोs of the Venकरोr ID.  For config ग_लिखोs or any
	 * other config पढ़ोs, the Root may स्वतःmatically reissue the
	 * configuration request again as a new request.
	 *
	 * For config पढ़ोs, this hardware वापसs CFG_RETRY_STATUS data
	 * when it receives a CRS completion, regardless of the address of
	 * the पढ़ो or the CRS Software Visibility Enable bit.  As a
	 * partial workaround क्रम this, we retry in software any पढ़ो that
	 * वापसs CFG_RETRY_STATUS.
	 *
	 * Note that a non-Venकरोr ID config रेजिस्टर may have a value of
	 * CFG_RETRY_STATUS.  If we पढ़ो that, we can't distinguish it from
	 * a CRS completion, so we will incorrectly retry the पढ़ो and
	 * eventually वापस the wrong data (0xffffffff).
	 */
	data = पढ़ोl(cfg_data_p);
	जबतक (data == CFG_RETRY_STATUS && समयout--) अणु
		/*
		 * CRS state is set in CFG_RD status रेजिस्टर
		 * This will handle the हाल where CFG_RETRY_STATUS is
		 * valid config data.
		 */
		status = iproc_pcie_पढ़ो_reg(pcie, IPROC_PCIE_CFG_RD_STATUS);
		अगर (status != CFG_RD_CRS)
			वापस data;

		udelay(1);
		data = पढ़ोl(cfg_data_p);
	पूर्ण

	अगर (data == CFG_RETRY_STATUS)
		data = 0xffffffff;

	वापस data;
पूर्ण

अटल व्योम iproc_pcie_fix_cap(काष्ठा iproc_pcie *pcie, पूर्णांक where, u32 *val)
अणु
	u32 i, dev_id;

	चयन (where & ~0x3) अणु
	हाल PCI_VENDOR_ID:
		dev_id = *val >> 16;

		/*
		 * Activate fixup क्रम those controllers that have corrupted
		 * capability list रेजिस्टरs
		 */
		क्रम (i = 0; i < ARRAY_SIZE(iproc_pcie_corrupt_cap_did); i++)
			अगर (dev_id == iproc_pcie_corrupt_cap_did[i])
				pcie->fix_paxc_cap = true;
		अवरोध;

	हाल IPROC_PCI_PM_CAP:
		अगर (pcie->fix_paxc_cap) अणु
			/* advertise PM, क्रमce next capability to PCIe */
			*val &= ~IPROC_PCI_PM_CAP_MASK;
			*val |= IPROC_PCI_EXP_CAP << 8 | PCI_CAP_ID_PM;
		पूर्ण
		अवरोध;

	हाल IPROC_PCI_EXP_CAP:
		अगर (pcie->fix_paxc_cap) अणु
			/* advertise root port, version 2, terminate here */
			*val = (PCI_EXP_TYPE_ROOT_PORT << 4 | 2) << 16 |
				PCI_CAP_ID_EXP;
		पूर्ण
		अवरोध;

	हाल IPROC_PCI_EXP_CAP + PCI_EXP_RTCTL:
		/* Don't advertise CRS SV support */
		*val &= ~(PCI_EXP_RTCAP_CRSVIS << 16);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक iproc_pcie_config_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				  पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	काष्ठा iproc_pcie *pcie = iproc_data(bus);
	अचिन्हित पूर्णांक busno = bus->number;
	व्योम __iomem *cfg_data_p;
	अचिन्हित पूर्णांक data;
	पूर्णांक ret;

	/* root complex access */
	अगर (busno == 0) अणु
		ret = pci_generic_config_पढ़ो32(bus, devfn, where, size, val);
		अगर (ret == PCIBIOS_SUCCESSFUL)
			iproc_pcie_fix_cap(pcie, where, val);

		वापस ret;
	पूर्ण

	cfg_data_p = iproc_pcie_map_ep_cfg_reg(pcie, busno, devfn, where);

	अगर (!cfg_data_p)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	data = iproc_pcie_cfg_retry(pcie, cfg_data_p);

	*val = data;
	अगर (size <= 2)
		*val = (data >> (8 * (where & 3))) & ((1 << (size * 8)) - 1);

	/*
	 * For PAXC and PAXCv2, the total number of PFs that one can क्रमागतerate
	 * depends on the firmware configuration. Unक्रमtunately, due to an ASIC
	 * bug, unconfigured PFs cannot be properly hidden from the root
	 * complex. As a result, ग_लिखो access to these PFs will cause bus lock
	 * up on the embedded processor
	 *
	 * Since all unconfigured PFs are left with an incorrect, staled device
	 * ID of 0x168e (PCI_DEVICE_ID_NX2_57810), we try to catch those access
	 * early here and reject them all
	 */
#घोषणा DEVICE_ID_MASK     0xffff0000
#घोषणा DEVICE_ID_SHIFT    16
	अगर (pcie->rej_unconfig_pf &&
	    (where & CFG_ADDR_REG_NUM_MASK) == PCI_VENDOR_ID)
		अगर ((*val & DEVICE_ID_MASK) ==
		    (PCI_DEVICE_ID_NX2_57810 << DEVICE_ID_SHIFT))
			वापस PCIBIOS_FUNC_NOT_SUPPORTED;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

/**
 * Note access to the configuration रेजिस्टरs are रक्षित at the higher layer
 * by 'pci_lock' in drivers/pci/access.c
 */
अटल व्योम __iomem *iproc_pcie_map_cfg_bus(काष्ठा iproc_pcie *pcie,
					    पूर्णांक busno, अचिन्हित पूर्णांक devfn,
					    पूर्णांक where)
अणु
	u16 offset;

	/* root complex access */
	अगर (busno == 0) अणु
		अगर (PCIE_ECAM_DEVFN(devfn) > 0)
			वापस शून्य;

		iproc_pcie_ग_लिखो_reg(pcie, IPROC_PCIE_CFG_IND_ADDR,
				     where & CFG_IND_ADDR_MASK);
		offset = iproc_pcie_reg_offset(pcie, IPROC_PCIE_CFG_IND_DATA);
		अगर (iproc_pcie_reg_is_invalid(offset))
			वापस शून्य;
		अन्यथा
			वापस (pcie->base + offset);
	पूर्ण

	वापस iproc_pcie_map_ep_cfg_reg(pcie, busno, devfn, where);
पूर्ण

अटल व्योम __iomem *iproc_pcie_bus_map_cfg_bus(काष्ठा pci_bus *bus,
						अचिन्हित पूर्णांक devfn,
						पूर्णांक where)
अणु
	वापस iproc_pcie_map_cfg_bus(iproc_data(bus), bus->number, devfn,
				      where);
पूर्ण

अटल पूर्णांक iproc_pci_raw_config_पढ़ो32(काष्ठा iproc_pcie *pcie,
				       अचिन्हित पूर्णांक devfn, पूर्णांक where,
				       पूर्णांक size, u32 *val)
अणु
	व्योम __iomem *addr;

	addr = iproc_pcie_map_cfg_bus(pcie, 0, devfn, where & ~0x3);
	अगर (!addr) अणु
		*val = ~0;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	*val = पढ़ोl(addr);

	अगर (size <= 2)
		*val = (*val >> (8 * (where & 3))) & ((1 << (size * 8)) - 1);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक iproc_pci_raw_config_ग_लिखो32(काष्ठा iproc_pcie *pcie,
					अचिन्हित पूर्णांक devfn, पूर्णांक where,
					पूर्णांक size, u32 val)
अणु
	व्योम __iomem *addr;
	u32 mask, पंचांगp;

	addr = iproc_pcie_map_cfg_bus(pcie, 0, devfn, where & ~0x3);
	अगर (!addr)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (size == 4) अणु
		ग_लिखोl(val, addr);
		वापस PCIBIOS_SUCCESSFUL;
	पूर्ण

	mask = ~(((1 << (size * 8)) - 1) << ((where & 0x3) * 8));
	पंचांगp = पढ़ोl(addr) & mask;
	पंचांगp |= val << ((where & 0x3) * 8);
	ग_लिखोl(पंचांगp, addr);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक iproc_pcie_config_पढ़ो32(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				    पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	पूर्णांक ret;
	काष्ठा iproc_pcie *pcie = iproc_data(bus);

	iproc_pcie_apb_err_disable(bus, true);
	अगर (pcie->iproc_cfg_पढ़ो)
		ret = iproc_pcie_config_पढ़ो(bus, devfn, where, size, val);
	अन्यथा
		ret = pci_generic_config_पढ़ो32(bus, devfn, where, size, val);
	iproc_pcie_apb_err_disable(bus, false);

	वापस ret;
पूर्ण

अटल पूर्णांक iproc_pcie_config_ग_लिखो32(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				     पूर्णांक where, पूर्णांक size, u32 val)
अणु
	पूर्णांक ret;

	iproc_pcie_apb_err_disable(bus, true);
	ret = pci_generic_config_ग_लिखो32(bus, devfn, where, size, val);
	iproc_pcie_apb_err_disable(bus, false);

	वापस ret;
पूर्ण

अटल काष्ठा pci_ops iproc_pcie_ops = अणु
	.map_bus = iproc_pcie_bus_map_cfg_bus,
	.पढ़ो = iproc_pcie_config_पढ़ो32,
	.ग_लिखो = iproc_pcie_config_ग_लिखो32,
पूर्ण;

अटल व्योम iproc_pcie_perst_ctrl(काष्ठा iproc_pcie *pcie, bool निश्चित)
अणु
	u32 val;

	/*
	 * PAXC and the पूर्णांकernal emulated endpoपूर्णांक device करोwnstream should not
	 * be reset.  If firmware has been loaded on the endpoपूर्णांक device at an
	 * earlier boot stage, reset here causes issues.
	 */
	अगर (pcie->ep_is_पूर्णांकernal)
		वापस;

	अगर (निश्चित) अणु
		val = iproc_pcie_पढ़ो_reg(pcie, IPROC_PCIE_CLK_CTRL);
		val &= ~EP_PERST_SOURCE_SELECT & ~EP_MODE_SURVIVE_PERST &
			~RC_PCIE_RST_OUTPUT;
		iproc_pcie_ग_लिखो_reg(pcie, IPROC_PCIE_CLK_CTRL, val);
		udelay(250);
	पूर्ण अन्यथा अणु
		val = iproc_pcie_पढ़ो_reg(pcie, IPROC_PCIE_CLK_CTRL);
		val |= RC_PCIE_RST_OUTPUT;
		iproc_pcie_ग_लिखो_reg(pcie, IPROC_PCIE_CLK_CTRL, val);
		msleep(100);
	पूर्ण
पूर्ण

पूर्णांक iproc_pcie_shutकरोwn(काष्ठा iproc_pcie *pcie)
अणु
	iproc_pcie_perst_ctrl(pcie, true);
	msleep(500);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iproc_pcie_shutकरोwn);

अटल पूर्णांक iproc_pcie_check_link(काष्ठा iproc_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	u32 hdr_type, link_ctrl, link_status, class, val;
	bool link_is_active = false;

	/*
	 * PAXC connects to emulated endpoपूर्णांक devices directly and करोes not
	 * have a Serdes.  Thereक्रमe skip the link detection logic here.
	 */
	अगर (pcie->ep_is_पूर्णांकernal)
		वापस 0;

	val = iproc_pcie_पढ़ो_reg(pcie, IPROC_PCIE_LINK_STATUS);
	अगर (!(val & PCIE_PHYLINKUP) || !(val & PCIE_DL_ACTIVE)) अणु
		dev_err(dev, "PHY or data link is INACTIVE!\n");
		वापस -ENODEV;
	पूर्ण

	/* make sure we are not in EP mode */
	iproc_pci_raw_config_पढ़ो32(pcie, 0, PCI_HEADER_TYPE, 1, &hdr_type);
	अगर ((hdr_type & 0x7f) != PCI_HEADER_TYPE_BRIDGE) अणु
		dev_err(dev, "in EP mode, hdr=%#02x\n", hdr_type);
		वापस -EFAULT;
	पूर्ण

	/* क्रमce class to PCI_CLASS_BRIDGE_PCI (0x0604) */
#घोषणा PCI_BRIDGE_CTRL_REG_OFFSET	0x43c
#घोषणा PCI_CLASS_BRIDGE_MASK		0xffff00
#घोषणा PCI_CLASS_BRIDGE_SHIFT		8
	iproc_pci_raw_config_पढ़ो32(pcie, 0, PCI_BRIDGE_CTRL_REG_OFFSET,
				    4, &class);
	class &= ~PCI_CLASS_BRIDGE_MASK;
	class |= (PCI_CLASS_BRIDGE_PCI << PCI_CLASS_BRIDGE_SHIFT);
	iproc_pci_raw_config_ग_लिखो32(pcie, 0, PCI_BRIDGE_CTRL_REG_OFFSET,
				     4, class);

	/* check link status to see अगर link is active */
	iproc_pci_raw_config_पढ़ो32(pcie, 0, IPROC_PCI_EXP_CAP + PCI_EXP_LNKSTA,
				    2, &link_status);
	अगर (link_status & PCI_EXP_LNKSTA_NLW)
		link_is_active = true;

	अगर (!link_is_active) अणु
		/* try GEN 1 link speed */
#घोषणा PCI_TARGET_LINK_SPEED_MASK	0xf
#घोषणा PCI_TARGET_LINK_SPEED_GEN2	0x2
#घोषणा PCI_TARGET_LINK_SPEED_GEN1	0x1
		iproc_pci_raw_config_पढ़ो32(pcie, 0,
					    IPROC_PCI_EXP_CAP + PCI_EXP_LNKCTL2,
					    4, &link_ctrl);
		अगर ((link_ctrl & PCI_TARGET_LINK_SPEED_MASK) ==
		    PCI_TARGET_LINK_SPEED_GEN2) अणु
			link_ctrl &= ~PCI_TARGET_LINK_SPEED_MASK;
			link_ctrl |= PCI_TARGET_LINK_SPEED_GEN1;
			iproc_pci_raw_config_ग_लिखो32(pcie, 0,
					IPROC_PCI_EXP_CAP + PCI_EXP_LNKCTL2,
					4, link_ctrl);
			msleep(100);

			iproc_pci_raw_config_पढ़ो32(pcie, 0,
					IPROC_PCI_EXP_CAP + PCI_EXP_LNKSTA,
					2, &link_status);
			अगर (link_status & PCI_EXP_LNKSTA_NLW)
				link_is_active = true;
		पूर्ण
	पूर्ण

	dev_info(dev, "link: %s\n", link_is_active ? "UP" : "DOWN");

	वापस link_is_active ? 0 : -ENODEV;
पूर्ण

अटल व्योम iproc_pcie_enable(काष्ठा iproc_pcie *pcie)
अणु
	iproc_pcie_ग_लिखो_reg(pcie, IPROC_PCIE_INTX_EN, SYS_RC_INTX_MASK);
पूर्ण

अटल अंतरभूत bool iproc_pcie_ob_is_valid(काष्ठा iproc_pcie *pcie,
					  पूर्णांक winकरोw_idx)
अणु
	u32 val;

	val = iproc_pcie_पढ़ो_reg(pcie, MAP_REG(IPROC_PCIE_OARR0, winकरोw_idx));

	वापस !!(val & OARR_VALID);
पूर्ण

अटल अंतरभूत पूर्णांक iproc_pcie_ob_ग_लिखो(काष्ठा iproc_pcie *pcie, पूर्णांक winकरोw_idx,
				      पूर्णांक size_idx, u64 axi_addr, u64 pci_addr)
अणु
	काष्ठा device *dev = pcie->dev;
	u16 oarr_offset, omap_offset;

	/*
	 * Derive the OARR/OMAP offset from the first pair (OARR0/OMAP0) based
	 * on winकरोw index.
	 */
	oarr_offset = iproc_pcie_reg_offset(pcie, MAP_REG(IPROC_PCIE_OARR0,
							  winकरोw_idx));
	omap_offset = iproc_pcie_reg_offset(pcie, MAP_REG(IPROC_PCIE_OMAP0,
							  winकरोw_idx));
	अगर (iproc_pcie_reg_is_invalid(oarr_offset) ||
	    iproc_pcie_reg_is_invalid(omap_offset))
		वापस -EINVAL;

	/*
	 * Program the OARR रेजिस्टरs.  The upper 32-bit OARR रेजिस्टर is
	 * always right after the lower 32-bit OARR रेजिस्टर.
	 */
	ग_लिखोl(lower_32_bits(axi_addr) | (size_idx << OARR_SIZE_CFG_SHIFT) |
	       OARR_VALID, pcie->base + oarr_offset);
	ग_लिखोl(upper_32_bits(axi_addr), pcie->base + oarr_offset + 4);

	/* now program the OMAP रेजिस्टरs */
	ग_लिखोl(lower_32_bits(pci_addr), pcie->base + omap_offset);
	ग_लिखोl(upper_32_bits(pci_addr), pcie->base + omap_offset + 4);

	dev_dbg(dev, "ob window [%d]: offset 0x%x axi %pap pci %pap\n",
		winकरोw_idx, oarr_offset, &axi_addr, &pci_addr);
	dev_dbg(dev, "oarr lo 0x%x oarr hi 0x%x\n",
		पढ़ोl(pcie->base + oarr_offset),
		पढ़ोl(pcie->base + oarr_offset + 4));
	dev_dbg(dev, "omap lo 0x%x omap hi 0x%x\n",
		पढ़ोl(pcie->base + omap_offset),
		पढ़ोl(pcie->base + omap_offset + 4));

	वापस 0;
पूर्ण

/**
 * Some iProc SoCs require the SW to configure the outbound address mapping
 *
 * Outbound address translation:
 *
 * iproc_pcie_address = axi_address - axi_offset
 * OARR = iproc_pcie_address
 * OMAP = pci_addr
 *
 * axi_addr -> iproc_pcie_address -> OARR -> OMAP -> pci_address
 */
अटल पूर्णांक iproc_pcie_setup_ob(काष्ठा iproc_pcie *pcie, u64 axi_addr,
			       u64 pci_addr, resource_माप_प्रकार size)
अणु
	काष्ठा iproc_pcie_ob *ob = &pcie->ob;
	काष्ठा device *dev = pcie->dev;
	पूर्णांक ret = -EINVAL, winकरोw_idx, size_idx;

	अगर (axi_addr < ob->axi_offset) अणु
		dev_err(dev, "axi address %pap less than offset %pap\n",
			&axi_addr, &ob->axi_offset);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Translate the AXI address to the पूर्णांकernal address used by the iProc
	 * PCIe core beक्रमe programming the OARR
	 */
	axi_addr -= ob->axi_offset;

	/* iterate through all OARR/OMAP mapping winकरोws */
	क्रम (winकरोw_idx = ob->nr_winकरोws - 1; winकरोw_idx >= 0; winकरोw_idx--) अणु
		स्थिर काष्ठा iproc_pcie_ob_map *ob_map =
			&pcie->ob_map[winकरोw_idx];

		/*
		 * If current outbound winकरोw is alपढ़ोy in use, move on to the
		 * next one.
		 */
		अगर (iproc_pcie_ob_is_valid(pcie, winकरोw_idx))
			जारी;

		/*
		 * Iterate through all supported winकरोw sizes within the
		 * OARR/OMAP pair to find a match.  Go through the winकरोw sizes
		 * in a descending order.
		 */
		क्रम (size_idx = ob_map->nr_sizes - 1; size_idx >= 0;
		     size_idx--) अणु
			resource_माप_प्रकार winकरोw_size =
				ob_map->winकरोw_sizes[size_idx] * SZ_1M;

			/*
			 * Keep iterating until we reach the last winकरोw and
			 * with the minimal winकरोw size at index zero. In this
			 * हाल, we take a compromise by mapping it using the
			 * minimum winकरोw size that can be supported
			 */
			अगर (size < winकरोw_size) अणु
				अगर (size_idx > 0 || winकरोw_idx > 0)
					जारी;

				/*
				 * For the corner हाल of reaching the minimal
				 * winकरोw size that can be supported on the
				 * last winकरोw
				 */
				axi_addr = ALIGN_DOWN(axi_addr, winकरोw_size);
				pci_addr = ALIGN_DOWN(pci_addr, winकरोw_size);
				size = winकरोw_size;
			पूर्ण

			अगर (!IS_ALIGNED(axi_addr, winकरोw_size) ||
			    !IS_ALIGNED(pci_addr, winकरोw_size)) अणु
				dev_err(dev,
					"axi %pap or pci %pap not aligned\n",
					&axi_addr, &pci_addr);
				वापस -EINVAL;
			पूर्ण

			/*
			 * Match found!  Program both OARR and OMAP and mark
			 * them as a valid entry.
			 */
			ret = iproc_pcie_ob_ग_लिखो(pcie, winकरोw_idx, size_idx,
						  axi_addr, pci_addr);
			अगर (ret)
				जाओ err_ob;

			size -= winकरोw_size;
			अगर (size == 0)
				वापस 0;

			/*
			 * If we are here, we are करोne with the current winकरोw,
			 * but not yet finished all mappings.  Need to move on
			 * to the next winकरोw.
			 */
			axi_addr += winकरोw_size;
			pci_addr += winकरोw_size;
			अवरोध;
		पूर्ण
	पूर्ण

err_ob:
	dev_err(dev, "unable to configure outbound mapping\n");
	dev_err(dev,
		"axi %pap, axi offset %pap, pci %pap, res size %pap\n",
		&axi_addr, &ob->axi_offset, &pci_addr, &size);

	वापस ret;
पूर्ण

अटल पूर्णांक iproc_pcie_map_ranges(काष्ठा iproc_pcie *pcie,
				 काष्ठा list_head *resources)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा resource_entry *winकरोw;
	पूर्णांक ret;

	resource_list_क्रम_each_entry(winकरोw, resources) अणु
		काष्ठा resource *res = winकरोw->res;
		u64 res_type = resource_type(res);

		चयन (res_type) अणु
		हाल IORESOURCE_IO:
		हाल IORESOURCE_BUS:
			अवरोध;
		हाल IORESOURCE_MEM:
			ret = iproc_pcie_setup_ob(pcie, res->start,
						  res->start - winकरोw->offset,
						  resource_size(res));
			अगर (ret)
				वापस ret;
			अवरोध;
		शेष:
			dev_err(dev, "invalid resource %pR\n", res);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत bool iproc_pcie_ib_is_in_use(काष्ठा iproc_pcie *pcie,
					   पूर्णांक region_idx)
अणु
	स्थिर काष्ठा iproc_pcie_ib_map *ib_map = &pcie->ib_map[region_idx];
	u32 val;

	val = iproc_pcie_पढ़ो_reg(pcie, MAP_REG(IPROC_PCIE_IARR0, region_idx));

	वापस !!(val & (BIT(ib_map->nr_sizes) - 1));
पूर्ण

अटल अंतरभूत bool iproc_pcie_ib_check_type(स्थिर काष्ठा iproc_pcie_ib_map *ib_map,
					    क्रमागत iproc_pcie_ib_map_type type)
अणु
	वापस !!(ib_map->type == type);
पूर्ण

अटल पूर्णांक iproc_pcie_ib_ग_लिखो(काष्ठा iproc_pcie *pcie, पूर्णांक region_idx,
			       पूर्णांक size_idx, पूर्णांक nr_winकरोws, u64 axi_addr,
			       u64 pci_addr, resource_माप_प्रकार size)
अणु
	काष्ठा device *dev = pcie->dev;
	स्थिर काष्ठा iproc_pcie_ib_map *ib_map = &pcie->ib_map[region_idx];
	u16 iarr_offset, imap_offset;
	u32 val;
	पूर्णांक winकरोw_idx;

	iarr_offset = iproc_pcie_reg_offset(pcie,
				MAP_REG(IPROC_PCIE_IARR0, region_idx));
	imap_offset = iproc_pcie_reg_offset(pcie,
				MAP_REG(IPROC_PCIE_IMAP0, region_idx));
	अगर (iproc_pcie_reg_is_invalid(iarr_offset) ||
	    iproc_pcie_reg_is_invalid(imap_offset))
		वापस -EINVAL;

	dev_dbg(dev, "ib region [%d]: offset 0x%x axi %pap pci %pap\n",
		region_idx, iarr_offset, &axi_addr, &pci_addr);

	/*
	 * Program the IARR रेजिस्टरs.  The upper 32-bit IARR रेजिस्टर is
	 * always right after the lower 32-bit IARR रेजिस्टर.
	 */
	ग_लिखोl(lower_32_bits(pci_addr) | BIT(size_idx),
	       pcie->base + iarr_offset);
	ग_लिखोl(upper_32_bits(pci_addr), pcie->base + iarr_offset + 4);

	dev_dbg(dev, "iarr lo 0x%x iarr hi 0x%x\n",
		पढ़ोl(pcie->base + iarr_offset),
		पढ़ोl(pcie->base + iarr_offset + 4));

	/*
	 * Now program the IMAP रेजिस्टरs.  Each IARR region may have one or
	 * more IMAP winकरोws.
	 */
	size >>= ilog2(nr_winकरोws);
	क्रम (winकरोw_idx = 0; winकरोw_idx < nr_winकरोws; winकरोw_idx++) अणु
		val = पढ़ोl(pcie->base + imap_offset);
		val |= lower_32_bits(axi_addr) | IMAP_VALID;
		ग_लिखोl(val, pcie->base + imap_offset);
		ग_लिखोl(upper_32_bits(axi_addr),
		       pcie->base + imap_offset + ib_map->imap_addr_offset);

		dev_dbg(dev, "imap window [%d] lo 0x%x hi 0x%x\n",
			winकरोw_idx, पढ़ोl(pcie->base + imap_offset),
			पढ़ोl(pcie->base + imap_offset +
			      ib_map->imap_addr_offset));

		imap_offset += ib_map->imap_winकरोw_offset;
		axi_addr += size;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iproc_pcie_setup_ib(काष्ठा iproc_pcie *pcie,
			       काष्ठा resource_entry *entry,
			       क्रमागत iproc_pcie_ib_map_type type)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा iproc_pcie_ib *ib = &pcie->ib;
	पूर्णांक ret;
	अचिन्हित पूर्णांक region_idx, size_idx;
	u64 axi_addr = entry->res->start;
	u64 pci_addr = entry->res->start - entry->offset;
	resource_माप_प्रकार size = resource_size(entry->res);

	/* iterate through all IARR mapping regions */
	क्रम (region_idx = 0; region_idx < ib->nr_regions; region_idx++) अणु
		स्थिर काष्ठा iproc_pcie_ib_map *ib_map =
			&pcie->ib_map[region_idx];

		/*
		 * If current inbound region is alपढ़ोy in use or not a
		 * compatible type, move on to the next.
		 */
		अगर (iproc_pcie_ib_is_in_use(pcie, region_idx) ||
		    !iproc_pcie_ib_check_type(ib_map, type))
			जारी;

		/* iterate through all supported region sizes to find a match */
		क्रम (size_idx = 0; size_idx < ib_map->nr_sizes; size_idx++) अणु
			resource_माप_प्रकार region_size =
			ib_map->region_sizes[size_idx] * ib_map->size_unit;

			अगर (size != region_size)
				जारी;

			अगर (!IS_ALIGNED(axi_addr, region_size) ||
			    !IS_ALIGNED(pci_addr, region_size)) अणु
				dev_err(dev,
					"axi %pap or pci %pap not aligned\n",
					&axi_addr, &pci_addr);
				वापस -EINVAL;
			पूर्ण

			/* Match found!  Program IARR and all IMAP winकरोws. */
			ret = iproc_pcie_ib_ग_लिखो(pcie, region_idx, size_idx,
						  ib_map->nr_winकरोws, axi_addr,
						  pci_addr, size);
			अगर (ret)
				जाओ err_ib;
			अन्यथा
				वापस 0;

		पूर्ण
	पूर्ण
	ret = -EINVAL;

err_ib:
	dev_err(dev, "unable to configure inbound mapping\n");
	dev_err(dev, "axi %pap, pci %pap, res size %pap\n",
		&axi_addr, &pci_addr, &size);

	वापस ret;
पूर्ण

अटल पूर्णांक iproc_pcie_map_dma_ranges(काष्ठा iproc_pcie *pcie)
अणु
	काष्ठा pci_host_bridge *host = pci_host_bridge_from_priv(pcie);
	काष्ठा resource_entry *entry;
	पूर्णांक ret = 0;

	resource_list_क्रम_each_entry(entry, &host->dma_ranges) अणु
		/* Each range entry corresponds to an inbound mapping region */
		ret = iproc_pcie_setup_ib(pcie, entry, IPROC_PCIE_IB_MAP_MEM);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम iproc_pcie_invalidate_mapping(काष्ठा iproc_pcie *pcie)
अणु
	काष्ठा iproc_pcie_ib *ib = &pcie->ib;
	काष्ठा iproc_pcie_ob *ob = &pcie->ob;
	पूर्णांक idx;

	अगर (pcie->ep_is_पूर्णांकernal)
		वापस;

	अगर (pcie->need_ob_cfg) अणु
		/* iterate through all OARR mapping regions */
		क्रम (idx = ob->nr_winकरोws - 1; idx >= 0; idx--) अणु
			iproc_pcie_ग_लिखो_reg(pcie,
					     MAP_REG(IPROC_PCIE_OARR0, idx), 0);
		पूर्ण
	पूर्ण

	अगर (pcie->need_ib_cfg) अणु
		/* iterate through all IARR mapping regions */
		क्रम (idx = 0; idx < ib->nr_regions; idx++) अणु
			iproc_pcie_ग_लिखो_reg(pcie,
					     MAP_REG(IPROC_PCIE_IARR0, idx), 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक iproce_pcie_get_msi(काष्ठा iproc_pcie *pcie,
			       काष्ठा device_node *msi_node,
			       u64 *msi_addr)
अणु
	काष्ठा device *dev = pcie->dev;
	पूर्णांक ret;
	काष्ठा resource res;

	/*
	 * Check अगर 'msi-map' poपूर्णांकs to ARM GICv3 ITS, which is the only
	 * supported बाह्यal MSI controller that requires steering.
	 */
	अगर (!of_device_is_compatible(msi_node, "arm,gic-v3-its")) अणु
		dev_err(dev, "unable to find compatible MSI controller\n");
		वापस -ENODEV;
	पूर्ण

	/* derive GITS_TRANSLATER address from GICv3 */
	ret = of_address_to_resource(msi_node, 0, &res);
	अगर (ret < 0) अणु
		dev_err(dev, "unable to obtain MSI controller resources\n");
		वापस ret;
	पूर्ण

	*msi_addr = res.start + GITS_TRANSLATER;
	वापस 0;
पूर्ण

अटल पूर्णांक iproc_pcie_paxb_v2_msi_steer(काष्ठा iproc_pcie *pcie, u64 msi_addr)
अणु
	पूर्णांक ret;
	काष्ठा resource_entry entry;

	स_रखो(&entry, 0, माप(entry));
	entry.res = &entry.__res;

	msi_addr &= ~(SZ_32K - 1);
	entry.res->start = msi_addr;
	entry.res->end = msi_addr + SZ_32K - 1;

	ret = iproc_pcie_setup_ib(pcie, &entry, IPROC_PCIE_IB_MAP_IO);
	वापस ret;
पूर्ण

अटल व्योम iproc_pcie_paxc_v2_msi_steer(काष्ठा iproc_pcie *pcie, u64 msi_addr,
					 bool enable)
अणु
	u32 val;

	अगर (!enable) अणु
		/*
		 * Disable PAXC MSI steering. All ग_लिखो transfers will be
		 * treated as non-MSI transfers
		 */
		val = iproc_pcie_पढ़ो_reg(pcie, IPROC_PCIE_MSI_EN_CFG);
		val &= ~MSI_ENABLE_CFG;
		iproc_pcie_ग_लिखो_reg(pcie, IPROC_PCIE_MSI_EN_CFG, val);
		वापस;
	पूर्ण

	/*
	 * Program bits [43:13] of address of GITS_TRANSLATER रेजिस्टर पूर्णांकo
	 * bits [30:0] of the MSI base address रेजिस्टर.  In fact, in all iProc
	 * based SoCs, all I/O रेजिस्टर bases are well below the 32-bit
	 * boundary, so we can safely assume bits [43:32] are always zeros.
	 */
	iproc_pcie_ग_लिखो_reg(pcie, IPROC_PCIE_MSI_BASE_ADDR,
			     (u32)(msi_addr >> 13));

	/* use a शेष 8K winकरोw size */
	iproc_pcie_ग_लिखो_reg(pcie, IPROC_PCIE_MSI_WINDOW_SIZE, 0);

	/* steering MSI to GICv3 ITS */
	val = iproc_pcie_पढ़ो_reg(pcie, IPROC_PCIE_MSI_GIC_MODE);
	val |= GIC_V3_CFG;
	iproc_pcie_ग_लिखो_reg(pcie, IPROC_PCIE_MSI_GIC_MODE, val);

	/*
	 * Program bits [43:2] of address of GITS_TRANSLATER रेजिस्टर पूर्णांकo the
	 * iProc MSI address रेजिस्टरs.
	 */
	msi_addr >>= 2;
	iproc_pcie_ग_लिखो_reg(pcie, IPROC_PCIE_MSI_ADDR_HI,
			     upper_32_bits(msi_addr));
	iproc_pcie_ग_लिखो_reg(pcie, IPROC_PCIE_MSI_ADDR_LO,
			     lower_32_bits(msi_addr));

	/* enable MSI */
	val = iproc_pcie_पढ़ो_reg(pcie, IPROC_PCIE_MSI_EN_CFG);
	val |= MSI_ENABLE_CFG;
	iproc_pcie_ग_लिखो_reg(pcie, IPROC_PCIE_MSI_EN_CFG, val);
पूर्ण

अटल पूर्णांक iproc_pcie_msi_steer(काष्ठा iproc_pcie *pcie,
				काष्ठा device_node *msi_node)
अणु
	काष्ठा device *dev = pcie->dev;
	पूर्णांक ret;
	u64 msi_addr;

	ret = iproce_pcie_get_msi(pcie, msi_node, &msi_addr);
	अगर (ret < 0) अणु
		dev_err(dev, "msi steering failed\n");
		वापस ret;
	पूर्ण

	चयन (pcie->type) अणु
	हाल IPROC_PCIE_PAXB_V2:
		ret = iproc_pcie_paxb_v2_msi_steer(pcie, msi_addr);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल IPROC_PCIE_PAXC_V2:
		iproc_pcie_paxc_v2_msi_steer(pcie, msi_addr, true);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iproc_pcie_msi_enable(काष्ठा iproc_pcie *pcie)
अणु
	काष्ठा device_node *msi_node;
	पूर्णांक ret;

	/*
	 * Either the "msi-parent" or the "msi-map" phandle needs to exist
	 * क्रम us to obtain the MSI node.
	 */

	msi_node = of_parse_phandle(pcie->dev->of_node, "msi-parent", 0);
	अगर (!msi_node) अणु
		स्थिर __be32 *msi_map = शून्य;
		पूर्णांक len;
		u32 phandle;

		msi_map = of_get_property(pcie->dev->of_node, "msi-map", &len);
		अगर (!msi_map)
			वापस -ENODEV;

		phandle = be32_to_cpup(msi_map + 1);
		msi_node = of_find_node_by_phandle(phandle);
		अगर (!msi_node)
			वापस -ENODEV;
	पूर्ण

	/*
	 * Certain revisions of the iProc PCIe controller require additional
	 * configurations to steer the MSI ग_लिखोs towards an बाह्यal MSI
	 * controller.
	 */
	अगर (pcie->need_msi_steer) अणु
		ret = iproc_pcie_msi_steer(pcie, msi_node);
		अगर (ret)
			जाओ out_put_node;
	पूर्ण

	/*
	 * If another MSI controller is being used, the call below should fail
	 * but that is okay
	 */
	ret = iproc_msi_init(pcie, msi_node);

out_put_node:
	of_node_put(msi_node);
	वापस ret;
पूर्ण

अटल व्योम iproc_pcie_msi_disable(काष्ठा iproc_pcie *pcie)
अणु
	iproc_msi_निकास(pcie);
पूर्ण

अटल पूर्णांक iproc_pcie_rev_init(काष्ठा iproc_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	अचिन्हित पूर्णांक reg_idx;
	स्थिर u16 *regs;

	चयन (pcie->type) अणु
	हाल IPROC_PCIE_PAXB_BCMA:
		regs = iproc_pcie_reg_paxb_bcma;
		अवरोध;
	हाल IPROC_PCIE_PAXB:
		regs = iproc_pcie_reg_paxb;
		pcie->has_apb_err_disable = true;
		अगर (pcie->need_ob_cfg) अणु
			pcie->ob_map = paxb_ob_map;
			pcie->ob.nr_winकरोws = ARRAY_SIZE(paxb_ob_map);
		पूर्ण
		अवरोध;
	हाल IPROC_PCIE_PAXB_V2:
		regs = iproc_pcie_reg_paxb_v2;
		pcie->iproc_cfg_पढ़ो = true;
		pcie->has_apb_err_disable = true;
		अगर (pcie->need_ob_cfg) अणु
			pcie->ob_map = paxb_v2_ob_map;
			pcie->ob.nr_winकरोws = ARRAY_SIZE(paxb_v2_ob_map);
		पूर्ण
		pcie->ib.nr_regions = ARRAY_SIZE(paxb_v2_ib_map);
		pcie->ib_map = paxb_v2_ib_map;
		pcie->need_msi_steer = true;
		dev_warn(dev, "reads of config registers that contain %#x return incorrect data\n",
			 CFG_RETRY_STATUS);
		अवरोध;
	हाल IPROC_PCIE_PAXC:
		regs = iproc_pcie_reg_paxc;
		pcie->ep_is_पूर्णांकernal = true;
		pcie->iproc_cfg_पढ़ो = true;
		pcie->rej_unconfig_pf = true;
		अवरोध;
	हाल IPROC_PCIE_PAXC_V2:
		regs = iproc_pcie_reg_paxc_v2;
		pcie->ep_is_पूर्णांकernal = true;
		pcie->iproc_cfg_पढ़ो = true;
		pcie->rej_unconfig_pf = true;
		pcie->need_msi_steer = true;
		अवरोध;
	शेष:
		dev_err(dev, "incompatible iProc PCIe interface\n");
		वापस -EINVAL;
	पूर्ण

	pcie->reg_offsets = devm_kसुस्मृति(dev, IPROC_PCIE_MAX_NUM_REG,
					 माप(*pcie->reg_offsets),
					 GFP_KERNEL);
	अगर (!pcie->reg_offsets)
		वापस -ENOMEM;

	/* go through the रेजिस्टर table and populate all valid रेजिस्टरs */
	pcie->reg_offsets[0] = (pcie->type == IPROC_PCIE_PAXC_V2) ?
		IPROC_PCIE_REG_INVALID : regs[0];
	क्रम (reg_idx = 1; reg_idx < IPROC_PCIE_MAX_NUM_REG; reg_idx++)
		pcie->reg_offsets[reg_idx] = regs[reg_idx] ?
			regs[reg_idx] : IPROC_PCIE_REG_INVALID;

	वापस 0;
पूर्ण

पूर्णांक iproc_pcie_setup(काष्ठा iproc_pcie *pcie, काष्ठा list_head *res)
अणु
	काष्ठा device *dev;
	पूर्णांक ret;
	काष्ठा pci_dev *pdev;
	काष्ठा pci_host_bridge *host = pci_host_bridge_from_priv(pcie);

	dev = pcie->dev;

	ret = iproc_pcie_rev_init(pcie);
	अगर (ret) अणु
		dev_err(dev, "unable to initialize controller parameters\n");
		वापस ret;
	पूर्ण

	ret = phy_init(pcie->phy);
	अगर (ret) अणु
		dev_err(dev, "unable to initialize PCIe PHY\n");
		वापस ret;
	पूर्ण

	ret = phy_घातer_on(pcie->phy);
	अगर (ret) अणु
		dev_err(dev, "unable to power on PCIe PHY\n");
		जाओ err_निकास_phy;
	पूर्ण

	iproc_pcie_perst_ctrl(pcie, true);
	iproc_pcie_perst_ctrl(pcie, false);

	iproc_pcie_invalidate_mapping(pcie);

	अगर (pcie->need_ob_cfg) अणु
		ret = iproc_pcie_map_ranges(pcie, res);
		अगर (ret) अणु
			dev_err(dev, "map failed\n");
			जाओ err_घातer_off_phy;
		पूर्ण
	पूर्ण

	अगर (pcie->need_ib_cfg) अणु
		ret = iproc_pcie_map_dma_ranges(pcie);
		अगर (ret && ret != -ENOENT)
			जाओ err_घातer_off_phy;
	पूर्ण

	ret = iproc_pcie_check_link(pcie);
	अगर (ret) अणु
		dev_err(dev, "no PCIe EP device detected\n");
		जाओ err_घातer_off_phy;
	पूर्ण

	iproc_pcie_enable(pcie);

	अगर (IS_ENABLED(CONFIG_PCI_MSI))
		अगर (iproc_pcie_msi_enable(pcie))
			dev_info(dev, "not using iProc MSI\n");

	host->ops = &iproc_pcie_ops;
	host->sysdata = pcie;
	host->map_irq = pcie->map_irq;

	ret = pci_host_probe(host);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to scan host: %d\n", ret);
		जाओ err_घातer_off_phy;
	पूर्ण

	क्रम_each_pci_bridge(pdev, host->bus) अणु
		अगर (pci_pcie_type(pdev) == PCI_EXP_TYPE_ROOT_PORT)
			pcie_prपूर्णांक_link_status(pdev);
	पूर्ण

	वापस 0;

err_घातer_off_phy:
	phy_घातer_off(pcie->phy);
err_निकास_phy:
	phy_निकास(pcie->phy);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(iproc_pcie_setup);

पूर्णांक iproc_pcie_हटाओ(काष्ठा iproc_pcie *pcie)
अणु
	काष्ठा pci_host_bridge *host = pci_host_bridge_from_priv(pcie);

	pci_stop_root_bus(host->bus);
	pci_हटाओ_root_bus(host->bus);

	iproc_pcie_msi_disable(pcie);

	phy_घातer_off(pcie->phy);
	phy_निकास(pcie->phy);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(iproc_pcie_हटाओ);

/*
 * The MSI parsing logic in certain revisions of Broadcom PAXC based root
 * complex करोes not work and needs to be disabled
 */
अटल व्योम quirk_paxc_disable_msi_parsing(काष्ठा pci_dev *pdev)
अणु
	काष्ठा iproc_pcie *pcie = iproc_data(pdev->bus);

	अगर (pdev->hdr_type == PCI_HEADER_TYPE_BRIDGE)
		iproc_pcie_paxc_v2_msi_steer(pcie, 0, false);
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_BROADCOM, 0x16f0,
			quirk_paxc_disable_msi_parsing);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_BROADCOM, 0xd802,
			quirk_paxc_disable_msi_parsing);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_BROADCOM, 0xd804,
			quirk_paxc_disable_msi_parsing);

अटल व्योम quirk_paxc_bridge(काष्ठा pci_dev *pdev)
अणु
	/*
	 * The PCI config space is shared with the PAXC root port and the first
	 * Ethernet device.  So, we need to workaround this by telling the PCI
	 * code that the bridge is not an Ethernet device.
	 */
	अगर (pdev->hdr_type == PCI_HEADER_TYPE_BRIDGE)
		pdev->class = PCI_CLASS_BRIDGE_PCI << 8;

	/*
	 * MPSS is not being set properly (as it is currently 0).  This is
	 * because that area of the PCI config space is hard coded to zero, and
	 * is not modअगरiable by firmware.  Set this to 2 (e.g., 512 byte MPS)
	 * so that the MPS can be set to the real max value.
	 */
	pdev->pcie_mpss = 2;
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_BROADCOM, 0x16cd, quirk_paxc_bridge);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_BROADCOM, 0x16f0, quirk_paxc_bridge);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_BROADCOM, 0xd750, quirk_paxc_bridge);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_BROADCOM, 0xd802, quirk_paxc_bridge);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_BROADCOM, 0xd804, quirk_paxc_bridge);

MODULE_AUTHOR("Ray Jui <rjui@broadcom.com>");
MODULE_DESCRIPTION("Broadcom iPROC PCIe common driver");
MODULE_LICENSE("GPL v2");
