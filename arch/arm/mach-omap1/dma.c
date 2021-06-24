<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP1/OMAP7xx - specअगरic DMA driver
 *
 * Copyright (C) 2003 - 2008 Nokia Corporation
 * Author: Juha Yrjथघlथअ <juha.yrjola@nokia.com>
 * DMA channel linking क्रम 1610 by Samuel Ortiz <samuel.ortiz@nokia.com>
 * Graphics DMA and LCD DMA graphics tranक्रमmations
 * by Imre Deak <imre.deak@nokia.com>
 * OMAP2/3 support Copyright (C) 2004-2007 Texas Instruments, Inc.
 * Some functions based on earlier dma-omap.c Copyright (C) 2001 RidgeRun, Inc.
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - https://www.ti.com/
 * Converted DMA library पूर्णांकo platक्रमm driver
 *                   - G, Manjunath Kondaiah <manjugk@ti.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/omap-dma.h>
#समावेश <mach/tc.h>

#समावेश "soc.h"

#घोषणा OMAP1_DMA_BASE			(0xfffed800)

अटल u32 enable_1510_mode;

अटल स्थिर काष्ठा omap_dma_reg reg_map[] = अणु
	[GCR]		= अणु 0x0400, 0x00, OMAP_DMA_REG_16BIT पूर्ण,
	[GSCR]		= अणु 0x0404, 0x00, OMAP_DMA_REG_16BIT पूर्ण,
	[GRST1]		= अणु 0x0408, 0x00, OMAP_DMA_REG_16BIT पूर्ण,
	[HW_ID]		= अणु 0x0442, 0x00, OMAP_DMA_REG_16BIT पूर्ण,
	[PCH2_ID]	= अणु 0x0444, 0x00, OMAP_DMA_REG_16BIT पूर्ण,
	[PCH0_ID]	= अणु 0x0446, 0x00, OMAP_DMA_REG_16BIT पूर्ण,
	[PCH1_ID]	= अणु 0x0448, 0x00, OMAP_DMA_REG_16BIT पूर्ण,
	[PCHG_ID]	= अणु 0x044a, 0x00, OMAP_DMA_REG_16BIT पूर्ण,
	[PCHD_ID]	= अणु 0x044c, 0x00, OMAP_DMA_REG_16BIT पूर्ण,
	[CAPS_0]	= अणु 0x044e, 0x00, OMAP_DMA_REG_2X16BIT पूर्ण,
	[CAPS_1]	= अणु 0x0452, 0x00, OMAP_DMA_REG_2X16BIT पूर्ण,
	[CAPS_2]	= अणु 0x0456, 0x00, OMAP_DMA_REG_16BIT पूर्ण,
	[CAPS_3]	= अणु 0x0458, 0x00, OMAP_DMA_REG_16BIT पूर्ण,
	[CAPS_4]	= अणु 0x045a, 0x00, OMAP_DMA_REG_16BIT पूर्ण,
	[PCH2_SR]	= अणु 0x0460, 0x00, OMAP_DMA_REG_16BIT पूर्ण,
	[PCH0_SR]	= अणु 0x0480, 0x00, OMAP_DMA_REG_16BIT पूर्ण,
	[PCH1_SR]	= अणु 0x0482, 0x00, OMAP_DMA_REG_16BIT पूर्ण,
	[PCHD_SR]	= अणु 0x04c0, 0x00, OMAP_DMA_REG_16BIT पूर्ण,

	/* Common Registers */
	[CSDP]		= अणु 0x0000, 0x40, OMAP_DMA_REG_16BIT पूर्ण,
	[CCR]		= अणु 0x0002, 0x40, OMAP_DMA_REG_16BIT पूर्ण,
	[CICR]		= अणु 0x0004, 0x40, OMAP_DMA_REG_16BIT पूर्ण,
	[CSR]		= अणु 0x0006, 0x40, OMAP_DMA_REG_16BIT पूर्ण,
	[CEN]		= अणु 0x0010, 0x40, OMAP_DMA_REG_16BIT पूर्ण,
	[CFN]		= अणु 0x0012, 0x40, OMAP_DMA_REG_16BIT पूर्ण,
	[CSFI]		= अणु 0x0014, 0x40, OMAP_DMA_REG_16BIT पूर्ण,
	[CSEI]		= अणु 0x0016, 0x40, OMAP_DMA_REG_16BIT पूर्ण,
	[CPC]		= अणु 0x0018, 0x40, OMAP_DMA_REG_16BIT पूर्ण,	/* 15xx only */
	[CSAC]		= अणु 0x0018, 0x40, OMAP_DMA_REG_16BIT पूर्ण,
	[CDAC]		= अणु 0x001a, 0x40, OMAP_DMA_REG_16BIT पूर्ण,
	[CDEI]		= अणु 0x001c, 0x40, OMAP_DMA_REG_16BIT पूर्ण,
	[CDFI]		= अणु 0x001e, 0x40, OMAP_DMA_REG_16BIT पूर्ण,
	[CLNK_CTRL]	= अणु 0x0028, 0x40, OMAP_DMA_REG_16BIT पूर्ण,

	/* Channel specअगरic रेजिस्टर offsets */
	[CSSA]		= अणु 0x0008, 0x40, OMAP_DMA_REG_2X16BIT पूर्ण,
	[CDSA]		= अणु 0x000c, 0x40, OMAP_DMA_REG_2X16BIT पूर्ण,
	[COLOR]		= अणु 0x0020, 0x40, OMAP_DMA_REG_2X16BIT पूर्ण,
	[CCR2]		= अणु 0x0024, 0x40, OMAP_DMA_REG_16BIT पूर्ण,
	[LCH_CTRL]	= अणु 0x002a, 0x40, OMAP_DMA_REG_16BIT पूर्ण,
पूर्ण;

अटल काष्ठा resource res[] __initdata = अणु
	[0] = अणु
		.start	= OMAP1_DMA_BASE,
		.end	= OMAP1_DMA_BASE + SZ_2K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.name   = "0",
		.start  = INT_DMA_CH0_6,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		.name   = "1",
		.start  = INT_DMA_CH1_7,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
	[3] = अणु
		.name   = "2",
		.start  = INT_DMA_CH2_8,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
	[4] = अणु
		.name   = "3",
		.start  = INT_DMA_CH3,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
	[5] = अणु
		.name   = "4",
		.start  = INT_DMA_CH4,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
	[6] = अणु
		.name   = "5",
		.start  = INT_DMA_CH5,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
	/* Handled in lcd_dma.c */
	[7] = अणु
		.name   = "6",
		.start  = INT_1610_DMA_CH6,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
	/* irq's क्रम omap16xx and omap7xx */
	[8] = अणु
		.name   = "7",
		.start  = INT_1610_DMA_CH7,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
	[9] = अणु
		.name   = "8",
		.start  = INT_1610_DMA_CH8,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
	[10] = अणु
		.name  = "9",
		.start = INT_1610_DMA_CH9,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	[11] = अणु
		.name  = "10",
		.start = INT_1610_DMA_CH10,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	[12] = अणु
		.name  = "11",
		.start = INT_1610_DMA_CH11,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	[13] = अणु
		.name  = "12",
		.start = INT_1610_DMA_CH12,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	[14] = अणु
		.name  = "13",
		.start = INT_1610_DMA_CH13,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	[15] = अणु
		.name  = "14",
		.start = INT_1610_DMA_CH14,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	[16] = अणु
		.name  = "15",
		.start = INT_1610_DMA_CH15,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	[17] = अणु
		.name  = "16",
		.start = INT_DMA_LCD,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल व्योम __iomem *dma_base;
अटल अंतरभूत व्योम dma_ग_लिखो(u32 val, पूर्णांक reg, पूर्णांक lch)
अणु
	व्योम __iomem *addr = dma_base;

	addr += reg_map[reg].offset;
	addr += reg_map[reg].stride * lch;

	__raw_ग_लिखोw(val, addr);
	अगर (reg_map[reg].type == OMAP_DMA_REG_2X16BIT)
		__raw_ग_लिखोw(val >> 16, addr + 2);
पूर्ण

अटल अंतरभूत u32 dma_पढ़ो(पूर्णांक reg, पूर्णांक lch)
अणु
	व्योम __iomem *addr = dma_base;
	uपूर्णांक32_t val;

	addr += reg_map[reg].offset;
	addr += reg_map[reg].stride * lch;

	val = __raw_पढ़ोw(addr);
	अगर (reg_map[reg].type == OMAP_DMA_REG_2X16BIT)
		val |= __raw_पढ़ोw(addr + 2) << 16;

	वापस val;
पूर्ण

अटल व्योम omap1_clear_lch_regs(पूर्णांक lch)
अणु
	पूर्णांक i;

	क्रम (i = CPC; i <= COLOR; i += 1)
		dma_ग_लिखो(0, i, lch);
पूर्ण

अटल व्योम omap1_clear_dma(पूर्णांक lch)
अणु
	u32 l;

	l = dma_पढ़ो(CCR, lch);
	l &= ~OMAP_DMA_CCR_EN;
	dma_ग_लिखो(l, CCR, lch);

	/* Clear pending पूर्णांकerrupts */
	l = dma_पढ़ो(CSR, lch);
पूर्ण

अटल व्योम omap1_show_dma_caps(व्योम)
अणु
	अगर (enable_1510_mode) अणु
		prपूर्णांकk(KERN_INFO "DMA support for OMAP15xx initialized\n");
	पूर्ण अन्यथा अणु
		u16 w;
		prपूर्णांकk(KERN_INFO "OMAP DMA hardware version %d\n",
							dma_पढ़ो(HW_ID, 0));
		prपूर्णांकk(KERN_INFO "DMA capabilities: %08x:%08x:%04x:%04x:%04x\n",
			dma_पढ़ो(CAPS_0, 0), dma_पढ़ो(CAPS_1, 0),
			dma_पढ़ो(CAPS_2, 0), dma_पढ़ो(CAPS_3, 0),
			dma_पढ़ो(CAPS_4, 0));

		/* Disable OMAP 3.0/3.1 compatibility mode. */
		w = dma_पढ़ो(GSCR, 0);
		w |= 1 << 3;
		dma_ग_लिखो(w, GSCR, 0);
	पूर्ण
पूर्ण

अटल अचिन्हित configure_dma_errata(व्योम)
अणु
	अचिन्हित errata = 0;

	/*
	 * Erratum 3.2/3.3: someबार 0 is वापसed अगर CSAC/CDAC is
	 * पढ़ो beक्रमe the DMA controller finished disabling the channel.
	 */
	अगर (!cpu_is_omap15xx())
		SET_DMA_ERRATA(DMA_ERRATA_3_3);

	वापस errata;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_info omap_dma_dev_info = अणु
	.name = "omap-dma-engine",
	.id = -1,
	.dma_mask = DMA_BIT_MASK(32),
	.res = res,
	.num_res = 1,
पूर्ण;

/* OMAP730, OMAP850 */
अटल स्थिर काष्ठा dma_slave_map omap7xx_sdma_map[] = अणु
	अणु "omap-mcbsp.1", "tx", SDMA_FILTER_PARAM(8) पूर्ण,
	अणु "omap-mcbsp.1", "rx", SDMA_FILTER_PARAM(9) पूर्ण,
	अणु "omap-mcbsp.2", "tx", SDMA_FILTER_PARAM(10) पूर्ण,
	अणु "omap-mcbsp.2", "rx", SDMA_FILTER_PARAM(11) पूर्ण,
	अणु "mmci-omap.0", "tx", SDMA_FILTER_PARAM(21) पूर्ण,
	अणु "mmci-omap.0", "rx", SDMA_FILTER_PARAM(22) पूर्ण,
	अणु "omap_udc", "rx0", SDMA_FILTER_PARAM(26) पूर्ण,
	अणु "omap_udc", "rx1", SDMA_FILTER_PARAM(27) पूर्ण,
	अणु "omap_udc", "rx2", SDMA_FILTER_PARAM(28) पूर्ण,
	अणु "omap_udc", "tx0", SDMA_FILTER_PARAM(29) पूर्ण,
	अणु "omap_udc", "tx1", SDMA_FILTER_PARAM(30) पूर्ण,
	अणु "omap_udc", "tx2", SDMA_FILTER_PARAM(31) पूर्ण,
पूर्ण;

/* OMAP1510, OMAP1610*/
अटल स्थिर काष्ठा dma_slave_map omap1xxx_sdma_map[] = अणु
	अणु "omap-mcbsp.1", "tx", SDMA_FILTER_PARAM(8) पूर्ण,
	अणु "omap-mcbsp.1", "rx", SDMA_FILTER_PARAM(9) पूर्ण,
	अणु "omap-mcbsp.3", "tx", SDMA_FILTER_PARAM(10) पूर्ण,
	अणु "omap-mcbsp.3", "rx", SDMA_FILTER_PARAM(11) पूर्ण,
	अणु "omap-mcbsp.2", "tx", SDMA_FILTER_PARAM(16) पूर्ण,
	अणु "omap-mcbsp.2", "rx", SDMA_FILTER_PARAM(17) पूर्ण,
	अणु "mmci-omap.0", "tx", SDMA_FILTER_PARAM(21) पूर्ण,
	अणु "mmci-omap.0", "rx", SDMA_FILTER_PARAM(22) पूर्ण,
	अणु "omap_udc", "rx0", SDMA_FILTER_PARAM(26) पूर्ण,
	अणु "omap_udc", "rx1", SDMA_FILTER_PARAM(27) पूर्ण,
	अणु "omap_udc", "rx2", SDMA_FILTER_PARAM(28) पूर्ण,
	अणु "omap_udc", "tx0", SDMA_FILTER_PARAM(29) पूर्ण,
	अणु "omap_udc", "tx1", SDMA_FILTER_PARAM(30) पूर्ण,
	अणु "omap_udc", "tx2", SDMA_FILTER_PARAM(31) पूर्ण,
	अणु "mmci-omap.1", "tx", SDMA_FILTER_PARAM(54) पूर्ण,
	अणु "mmci-omap.1", "rx", SDMA_FILTER_PARAM(55) पूर्ण,
पूर्ण;

अटल काष्ठा omap_प्रणाली_dma_plat_info dma_plat_info __initdata = अणु
	.reg_map	= reg_map,
	.channel_stride	= 0x40,
	.show_dma_caps	= omap1_show_dma_caps,
	.clear_lch_regs	= omap1_clear_lch_regs,
	.clear_dma	= omap1_clear_dma,
	.dma_ग_लिखो	= dma_ग_लिखो,
	.dma_पढ़ो	= dma_पढ़ो,
पूर्ण;

अटल पूर्णांक __init omap1_प्रणाली_dma_init(व्योम)
अणु
	काष्ठा omap_प्रणाली_dma_plat_info	p;
	काष्ठा omap_dma_dev_attr		*d;
	काष्ठा platक्रमm_device			*pdev, *dma_pdev;
	पूर्णांक ret;

	pdev = platक्रमm_device_alloc("omap_dma_system", 0);
	अगर (!pdev) अणु
		pr_err("%s: Unable to device alloc for dma\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	dma_base = ioremap(res[0].start, resource_size(&res[0]));
	अगर (!dma_base) अणु
		pr_err("%s: Unable to ioremap\n", __func__);
		ret = -ENODEV;
		जाओ निकास_device_put;
	पूर्ण

	ret = platक्रमm_device_add_resources(pdev, res, ARRAY_SIZE(res));
	अगर (ret) अणु
		dev_err(&pdev->dev, "%s: Unable to add resources for %s%d\n",
			__func__, pdev->name, pdev->id);
		जाओ निकास_iounmap;
	पूर्ण

	d = kzalloc(माप(*d), GFP_KERNEL);
	अगर (!d) अणु
		ret = -ENOMEM;
		जाओ निकास_iounmap;
	पूर्ण

	/* Valid attributes क्रम omap1 plus processors */
	अगर (cpu_is_omap15xx())
		d->dev_caps = ENABLE_1510_MODE;
	enable_1510_mode = d->dev_caps & ENABLE_1510_MODE;

	अगर (cpu_is_omap16xx())
		d->dev_caps = ENABLE_16XX_MODE;

	d->dev_caps		|= SRC_PORT;
	d->dev_caps		|= DST_PORT;
	d->dev_caps		|= SRC_INDEX;
	d->dev_caps		|= DST_INDEX;
	d->dev_caps		|= IS_BURST_ONLY4;
	d->dev_caps		|= CLEAR_CSR_ON_READ;
	d->dev_caps		|= IS_WORD_16;

	/* available logical channels */
	अगर (cpu_is_omap15xx()) अणु
		d->lch_count = 9;
	पूर्ण अन्यथा अणु
		अगर (d->dev_caps & ENABLE_1510_MODE)
			d->lch_count = 9;
		अन्यथा
			d->lch_count = 16;
	पूर्ण

	p = dma_plat_info;
	p.dma_attr = d;
	p.errata = configure_dma_errata();

	अगर (cpu_is_omap7xx()) अणु
		p.slave_map = omap7xx_sdma_map;
		p.slavecnt = ARRAY_SIZE(omap7xx_sdma_map);
	पूर्ण अन्यथा अणु
		p.slave_map = omap1xxx_sdma_map;
		p.slavecnt = ARRAY_SIZE(omap1xxx_sdma_map);
	पूर्ण

	ret = platक्रमm_device_add_data(pdev, &p, माप(p));
	अगर (ret) अणु
		dev_err(&pdev->dev, "%s: Unable to add resources for %s%d\n",
			__func__, pdev->name, pdev->id);
		जाओ निकास_release_d;
	पूर्ण

	ret = platक्रमm_device_add(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "%s: Unable to add resources for %s%d\n",
			__func__, pdev->name, pdev->id);
		जाओ निकास_release_d;
	पूर्ण

	dma_pdev = platक्रमm_device_रेजिस्टर_full(&omap_dma_dev_info);
	अगर (IS_ERR(dma_pdev)) अणु
		ret = PTR_ERR(dma_pdev);
		जाओ निकास_release_pdev;
	पूर्ण

	वापस ret;

निकास_release_pdev:
	platक्रमm_device_del(pdev);
निकास_release_d:
	kमुक्त(d);
निकास_iounmap:
	iounmap(dma_base);
निकास_device_put:
	platक्रमm_device_put(pdev);

	वापस ret;
पूर्ण
arch_initcall(omap1_प्रणाली_dma_init);
