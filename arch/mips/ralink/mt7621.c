<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2015 Nikolay Martynov <mar.kolya@gmail.com>
 * Copyright (C) 2015 John Crispin <john@phrozen.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/smp-ops.h>
#समावेश <यंत्र/mips-cps.h>
#समावेश <यंत्र/mach-ralink/ralink_regs.h>
#समावेश <यंत्र/mach-ralink/mt7621.h>

#समावेश <pinmux.h>

#समावेश "common.h"

#घोषणा MT7621_GPIO_MODE_UART1		1
#घोषणा MT7621_GPIO_MODE_I2C		2
#घोषणा MT7621_GPIO_MODE_UART3_MASK	0x3
#घोषणा MT7621_GPIO_MODE_UART3_SHIFT	3
#घोषणा MT7621_GPIO_MODE_UART3_GPIO	1
#घोषणा MT7621_GPIO_MODE_UART2_MASK	0x3
#घोषणा MT7621_GPIO_MODE_UART2_SHIFT	5
#घोषणा MT7621_GPIO_MODE_UART2_GPIO	1
#घोषणा MT7621_GPIO_MODE_JTAG		7
#घोषणा MT7621_GPIO_MODE_WDT_MASK	0x3
#घोषणा MT7621_GPIO_MODE_WDT_SHIFT	8
#घोषणा MT7621_GPIO_MODE_WDT_GPIO	1
#घोषणा MT7621_GPIO_MODE_PCIE_RST	0
#घोषणा MT7621_GPIO_MODE_PCIE_REF	2
#घोषणा MT7621_GPIO_MODE_PCIE_MASK	0x3
#घोषणा MT7621_GPIO_MODE_PCIE_SHIFT	10
#घोषणा MT7621_GPIO_MODE_PCIE_GPIO	1
#घोषणा MT7621_GPIO_MODE_MDIO_MASK	0x3
#घोषणा MT7621_GPIO_MODE_MDIO_SHIFT	12
#घोषणा MT7621_GPIO_MODE_MDIO_GPIO	1
#घोषणा MT7621_GPIO_MODE_RGMII1		14
#घोषणा MT7621_GPIO_MODE_RGMII2		15
#घोषणा MT7621_GPIO_MODE_SPI_MASK	0x3
#घोषणा MT7621_GPIO_MODE_SPI_SHIFT	16
#घोषणा MT7621_GPIO_MODE_SPI_GPIO	1
#घोषणा MT7621_GPIO_MODE_SDHCI_MASK	0x3
#घोषणा MT7621_GPIO_MODE_SDHCI_SHIFT	18
#घोषणा MT7621_GPIO_MODE_SDHCI_GPIO	1

अटल व्योम *detect_magic __initdata = detect_memory_region;

अटल काष्ठा rt2880_pmx_func uart1_grp[] =  अणु FUNC("uart1", 0, 1, 2) पूर्ण;
अटल काष्ठा rt2880_pmx_func i2c_grp[] =  अणु FUNC("i2c", 0, 3, 2) पूर्ण;
अटल काष्ठा rt2880_pmx_func uart3_grp[] = अणु
	FUNC("uart3", 0, 5, 4),
	FUNC("i2s", 2, 5, 4),
	FUNC("spdif3", 3, 5, 4),
पूर्ण;
अटल काष्ठा rt2880_pmx_func uart2_grp[] = अणु
	FUNC("uart2", 0, 9, 4),
	FUNC("pcm", 2, 9, 4),
	FUNC("spdif2", 3, 9, 4),
पूर्ण;
अटल काष्ठा rt2880_pmx_func jtag_grp[] = अणु FUNC("jtag", 0, 13, 5) पूर्ण;
अटल काष्ठा rt2880_pmx_func wdt_grp[] = अणु
	FUNC("wdt rst", 0, 18, 1),
	FUNC("wdt refclk", 2, 18, 1),
पूर्ण;
अटल काष्ठा rt2880_pmx_func pcie_rst_grp[] = अणु
	FUNC("pcie rst", MT7621_GPIO_MODE_PCIE_RST, 19, 1),
	FUNC("pcie refclk", MT7621_GPIO_MODE_PCIE_REF, 19, 1)
पूर्ण;
अटल काष्ठा rt2880_pmx_func mdio_grp[] = अणु FUNC("mdio", 0, 20, 2) पूर्ण;
अटल काष्ठा rt2880_pmx_func rgmii2_grp[] = अणु FUNC("rgmii2", 0, 22, 12) पूर्ण;
अटल काष्ठा rt2880_pmx_func spi_grp[] = अणु
	FUNC("spi", 0, 34, 7),
	FUNC("nand1", 2, 34, 7),
पूर्ण;
अटल काष्ठा rt2880_pmx_func sdhci_grp[] = अणु
	FUNC("sdhci", 0, 41, 8),
	FUNC("nand2", 2, 41, 8),
पूर्ण;
अटल काष्ठा rt2880_pmx_func rgmii1_grp[] = अणु FUNC("rgmii1", 0, 49, 12) पूर्ण;

अटल काष्ठा rt2880_pmx_group mt7621_pinmux_data[] = अणु
	GRP("uart1", uart1_grp, 1, MT7621_GPIO_MODE_UART1),
	GRP("i2c", i2c_grp, 1, MT7621_GPIO_MODE_I2C),
	GRP_G("uart3", uart3_grp, MT7621_GPIO_MODE_UART3_MASK,
		MT7621_GPIO_MODE_UART3_GPIO, MT7621_GPIO_MODE_UART3_SHIFT),
	GRP_G("uart2", uart2_grp, MT7621_GPIO_MODE_UART2_MASK,
		MT7621_GPIO_MODE_UART2_GPIO, MT7621_GPIO_MODE_UART2_SHIFT),
	GRP("jtag", jtag_grp, 1, MT7621_GPIO_MODE_JTAG),
	GRP_G("wdt", wdt_grp, MT7621_GPIO_MODE_WDT_MASK,
		MT7621_GPIO_MODE_WDT_GPIO, MT7621_GPIO_MODE_WDT_SHIFT),
	GRP_G("pcie", pcie_rst_grp, MT7621_GPIO_MODE_PCIE_MASK,
		MT7621_GPIO_MODE_PCIE_GPIO, MT7621_GPIO_MODE_PCIE_SHIFT),
	GRP_G("mdio", mdio_grp, MT7621_GPIO_MODE_MDIO_MASK,
		MT7621_GPIO_MODE_MDIO_GPIO, MT7621_GPIO_MODE_MDIO_SHIFT),
	GRP("rgmii2", rgmii2_grp, 1, MT7621_GPIO_MODE_RGMII2),
	GRP_G("spi", spi_grp, MT7621_GPIO_MODE_SPI_MASK,
		MT7621_GPIO_MODE_SPI_GPIO, MT7621_GPIO_MODE_SPI_SHIFT),
	GRP_G("sdhci", sdhci_grp, MT7621_GPIO_MODE_SDHCI_MASK,
		MT7621_GPIO_MODE_SDHCI_GPIO, MT7621_GPIO_MODE_SDHCI_SHIFT),
	GRP("rgmii1", rgmii1_grp, 1, MT7621_GPIO_MODE_RGMII1),
	अणु 0 पूर्ण
पूर्ण;

phys_addr_t mips_cpc_शेष_phys_base(व्योम)
अणु
	panic("Cannot detect cpc address");
पूर्ण

अटल व्योम __init mt7621_memory_detect(व्योम)
अणु
	व्योम *dm = &detect_magic;
	phys_addr_t size;

	क्रम (size = 32 * SZ_1M; size < 256 * SZ_1M; size <<= 1) अणु
		अगर (!__builtin_स_भेद(dm, dm + size, माप(detect_magic)))
			अवरोध;
	पूर्ण

	अगर ((size == 256 * SZ_1M) &&
	    (CPHYSADDR(dm + size) < MT7621_LOWMEM_MAX_SIZE) &&
	    __builtin_स_भेद(dm, dm + size, माप(detect_magic))) अणु
		memblock_add(MT7621_LOWMEM_BASE, MT7621_LOWMEM_MAX_SIZE);
		memblock_add(MT7621_HIGHMEM_BASE, MT7621_HIGHMEM_SIZE);
	पूर्ण अन्यथा अणु
		memblock_add(MT7621_LOWMEM_BASE, size);
	पूर्ण
पूर्ण

व्योम __init ralink_of_remap(व्योम)
अणु
	rt_sysc_membase = plat_of_remap_node("mediatek,mt7621-sysc");
	rt_memc_membase = plat_of_remap_node("mediatek,mt7621-memc");

	अगर (!rt_sysc_membase || !rt_memc_membase)
		panic("Failed to remap core resources");
पूर्ण

अटल व्योम soc_dev_init(काष्ठा ralink_soc_info *soc_info, u32 rev)
अणु
	काष्ठा soc_device *soc_dev;
	काष्ठा soc_device_attribute *soc_dev_attr;

	soc_dev_attr = kzalloc(माप(*soc_dev_attr), GFP_KERNEL);
	अगर (!soc_dev_attr)
		वापस;

	soc_dev_attr->soc_id = "mt7621";
	soc_dev_attr->family = "Ralink";

	अगर (((rev >> CHIP_REV_VER_SHIFT) & CHIP_REV_VER_MASK) == 1 &&
	    (rev & CHIP_REV_ECO_MASK) == 1)
		soc_dev_attr->revision = "E2";
	अन्यथा
		soc_dev_attr->revision = "E1";

	soc_dev_attr->data = soc_info;

	soc_dev = soc_device_रेजिस्टर(soc_dev_attr);
	अगर (IS_ERR(soc_dev)) अणु
		kमुक्त(soc_dev_attr);
		वापस;
	पूर्ण
पूर्ण

व्योम __init prom_soc_init(काष्ठा ralink_soc_info *soc_info)
अणु
	व्योम __iomem *sysc = (व्योम __iomem *) KSEG1ADDR(MT7621_SYSC_BASE);
	अचिन्हित अक्षर *name = शून्य;
	u32 n0;
	u32 n1;
	u32 rev;

	/* Early detection of CMP support */
	mips_cm_probe();
	mips_cpc_probe();

	अगर (mips_cps_numiocu(0)) अणु
		/*
		 * mips_cm_probe() wipes out bootloader
		 * config क्रम CM regions and we have to configure them
		 * again. This SoC cannot talk to pamlbus devices
		 * witout proper iocu region set up.
		 *
		 * FIXME: it would be better to करो this with values
		 * from DT, but we need this very early because
		 * without this we cannot talk to pretty much anything
		 * including serial.
		 */
		ग_लिखो_gcr_reg0_base(MT7621_PALMBUS_BASE);
		ग_लिखो_gcr_reg0_mask(~MT7621_PALMBUS_SIZE |
				    CM_GCR_REGn_MASK_CMTGT_IOCU0);
		__sync();
	पूर्ण

	n0 = __raw_पढ़ोl(sysc + SYSC_REG_CHIP_NAME0);
	n1 = __raw_पढ़ोl(sysc + SYSC_REG_CHIP_NAME1);

	अगर (n0 == MT7621_CHIP_NAME0 && n1 == MT7621_CHIP_NAME1) अणु
		name = "MT7621";
		soc_info->compatible = "mediatek,mt7621-soc";
	पूर्ण अन्यथा अणु
		panic("mt7621: unknown SoC, n0:%08x n1:%08x\n", n0, n1);
	पूर्ण
	ralink_soc = MT762X_SOC_MT7621AT;
	rev = __raw_पढ़ोl(sysc + SYSC_REG_CHIP_REV);

	snम_लिखो(soc_info->sys_type, RAMIPS_SYS_TYPE_LEN,
		"MediaTek %s ver:%u eco:%u",
		name,
		(rev >> CHIP_REV_VER_SHIFT) & CHIP_REV_VER_MASK,
		(rev & CHIP_REV_ECO_MASK));

	soc_info->mem_detect = mt7621_memory_detect;
	rt2880_pinmux_data = mt7621_pinmux_data;

	soc_dev_init(soc_info, rev);

	अगर (!रेजिस्टर_cps_smp_ops())
		वापस;
	अगर (!रेजिस्टर_cmp_smp_ops())
		वापस;
	अगर (!रेजिस्टर_vsmp_smp_ops())
		वापस;
पूर्ण
