<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap1/mcbsp.c
 *
 * Copyright (C) 2008 Instituto Nokia de Tecnologia
 * Contact: Eduarकरो Valentin <eduarकरो.valentin@indt.org.br>
 *
 * Multichannel mode not supported.
 */
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <linux/omap-dma.h>
#समावेश <mach/mux.h>
#समावेश "soc.h"
#समावेश <linux/platक्रमm_data/asoc-ti-mcbsp.h>

#समावेश <mach/irqs.h>

#समावेश "iomap.h"

#घोषणा DPS_RSTCT2_PER_EN	(1 << 0)
#घोषणा DSP_RSTCT2_WD_PER_EN	(1 << 1)

अटल पूर्णांक dsp_use;
अटल काष्ठा clk *api_clk;
अटल काष्ठा clk *dsp_clk;
अटल काष्ठा platक्रमm_device **omap_mcbsp_devices;

अटल व्योम omap1_mcbsp_request(अचिन्हित पूर्णांक id)
अणु
	/*
	 * On 1510, 1610 and 1710, McBSP1 and McBSP3
	 * are DSP खुला peripherals.
	 */
	अगर (id == 0 || id == 2) अणु
		अगर (dsp_use++ == 0) अणु
			api_clk = clk_get(शून्य, "api_ck");
			dsp_clk = clk_get(शून्य, "dsp_ck");
			अगर (!IS_ERR(api_clk) && !IS_ERR(dsp_clk)) अणु
				clk_enable(api_clk);
				clk_enable(dsp_clk);

				/*
				 * DSP बाह्यal peripheral reset
				 * FIXME: This should be moved to dsp code
				 */
				__raw_ग_लिखोw(__raw_पढ़ोw(DSP_RSTCT2) | DPS_RSTCT2_PER_EN |
						DSP_RSTCT2_WD_PER_EN, DSP_RSTCT2);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम omap1_mcbsp_मुक्त(अचिन्हित पूर्णांक id)
अणु
	अगर (id == 0 || id == 2) अणु
		अगर (--dsp_use == 0) अणु
			अगर (!IS_ERR(api_clk)) अणु
				clk_disable(api_clk);
				clk_put(api_clk);
			पूर्ण
			अगर (!IS_ERR(dsp_clk)) अणु
				clk_disable(dsp_clk);
				clk_put(dsp_clk);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा omap_mcbsp_ops omap1_mcbsp_ops = अणु
	.request	= omap1_mcbsp_request,
	.मुक्त		= omap1_mcbsp_मुक्त,
पूर्ण;

#घोषणा OMAP7XX_MCBSP1_BASE	0xfffb1000
#घोषणा OMAP7XX_MCBSP2_BASE	0xfffb1800

#घोषणा OMAP1510_MCBSP1_BASE	0xe1011800
#घोषणा OMAP1510_MCBSP2_BASE	0xfffb1000
#घोषणा OMAP1510_MCBSP3_BASE	0xe1017000

#घोषणा OMAP1610_MCBSP1_BASE	0xe1011800
#घोषणा OMAP1610_MCBSP2_BASE	0xfffb1000
#घोषणा OMAP1610_MCBSP3_BASE	0xe1017000

#अगर defined(CONFIG_ARCH_OMAP730) || defined(CONFIG_ARCH_OMAP850)
काष्ठा resource omap7xx_mcbsp_res[][6] = अणु
	अणु
		अणु
			.start = OMAP7XX_MCBSP1_BASE,
			.end   = OMAP7XX_MCBSP1_BASE + SZ_256,
			.flags = IORESOURCE_MEM,
		पूर्ण,
		अणु
			.name  = "rx",
			.start = INT_7XX_McBSP1RX,
			.flags = IORESOURCE_IRQ,
		पूर्ण,
		अणु
			.name  = "tx",
			.start = INT_7XX_McBSP1TX,
			.flags = IORESOURCE_IRQ,
		पूर्ण,
		अणु
			.name  = "rx",
			.start = 9,
			.flags = IORESOURCE_DMA,
		पूर्ण,
		अणु
			.name  = "tx",
			.start = 8,
			.flags = IORESOURCE_DMA,
		पूर्ण,
	पूर्ण,
	अणु
		अणु
			.start = OMAP7XX_MCBSP2_BASE,
			.end   = OMAP7XX_MCBSP2_BASE + SZ_256,
			.flags = IORESOURCE_MEM,
		पूर्ण,
		अणु
			.name  = "rx",
			.start = INT_7XX_McBSP2RX,
			.flags = IORESOURCE_IRQ,
		पूर्ण,
		अणु
			.name  = "tx",
			.start = INT_7XX_McBSP2TX,
			.flags = IORESOURCE_IRQ,
		पूर्ण,
		अणु
			.name  = "rx",
			.start = 11,
			.flags = IORESOURCE_DMA,
		पूर्ण,
		अणु
			.name  = "tx",
			.start = 10,
			.flags = IORESOURCE_DMA,
		पूर्ण,
	पूर्ण,
पूर्ण;

#घोषणा omap7xx_mcbsp_res_0		omap7xx_mcbsp_res[0]

अटल काष्ठा omap_mcbsp_platक्रमm_data omap7xx_mcbsp_pdata[] = अणु
	अणु
		.ops		= &omap1_mcbsp_ops,
	पूर्ण,
	अणु
		.ops		= &omap1_mcbsp_ops,
	पूर्ण,
पूर्ण;
#घोषणा OMAP7XX_MCBSP_RES_SZ		ARRAY_SIZE(omap7xx_mcbsp_res[1])
#घोषणा OMAP7XX_MCBSP_COUNT		ARRAY_SIZE(omap7xx_mcbsp_res)
#अन्यथा
#घोषणा omap7xx_mcbsp_res_0		शून्य
#घोषणा omap7xx_mcbsp_pdata		शून्य
#घोषणा OMAP7XX_MCBSP_RES_SZ		0
#घोषणा OMAP7XX_MCBSP_COUNT		0
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP15XX
काष्ठा resource omap15xx_mcbsp_res[][6] = अणु
	अणु
		अणु
			.start = OMAP1510_MCBSP1_BASE,
			.end   = OMAP1510_MCBSP1_BASE + SZ_256,
			.flags = IORESOURCE_MEM,
		पूर्ण,
		अणु
			.name  = "rx",
			.start = INT_McBSP1RX,
			.flags = IORESOURCE_IRQ,
		पूर्ण,
		अणु
			.name  = "tx",
			.start = INT_McBSP1TX,
			.flags = IORESOURCE_IRQ,
		पूर्ण,
		अणु
			.name  = "rx",
			.start = 9,
			.flags = IORESOURCE_DMA,
		पूर्ण,
		अणु
			.name  = "tx",
			.start = 8,
			.flags = IORESOURCE_DMA,
		पूर्ण,
	पूर्ण,
	अणु
		अणु
			.start = OMAP1510_MCBSP2_BASE,
			.end   = OMAP1510_MCBSP2_BASE + SZ_256,
			.flags = IORESOURCE_MEM,
		पूर्ण,
		अणु
			.name  = "rx",
			.start = INT_1510_SPI_RX,
			.flags = IORESOURCE_IRQ,
		पूर्ण,
		अणु
			.name  = "tx",
			.start = INT_1510_SPI_TX,
			.flags = IORESOURCE_IRQ,
		पूर्ण,
		अणु
			.name  = "rx",
			.start = 17,
			.flags = IORESOURCE_DMA,
		पूर्ण,
		अणु
			.name  = "tx",
			.start = 16,
			.flags = IORESOURCE_DMA,
		पूर्ण,
	पूर्ण,
	अणु
		अणु
			.start = OMAP1510_MCBSP3_BASE,
			.end   = OMAP1510_MCBSP3_BASE + SZ_256,
			.flags = IORESOURCE_MEM,
		पूर्ण,
		अणु
			.name  = "rx",
			.start = INT_McBSP3RX,
			.flags = IORESOURCE_IRQ,
		पूर्ण,
		अणु
			.name  = "tx",
			.start = INT_McBSP3TX,
			.flags = IORESOURCE_IRQ,
		पूर्ण,
		अणु
			.name  = "rx",
			.start = 11,
			.flags = IORESOURCE_DMA,
		पूर्ण,
		अणु
			.name  = "tx",
			.start = 10,
			.flags = IORESOURCE_DMA,
		पूर्ण,
	पूर्ण,
पूर्ण;

#घोषणा omap15xx_mcbsp_res_0		omap15xx_mcbsp_res[0]

अटल काष्ठा omap_mcbsp_platक्रमm_data omap15xx_mcbsp_pdata[] = अणु
	अणु
		.ops		= &omap1_mcbsp_ops,
	पूर्ण,
	अणु
		.ops		= &omap1_mcbsp_ops,
	पूर्ण,
	अणु
		.ops		= &omap1_mcbsp_ops,
	पूर्ण,
पूर्ण;
#घोषणा OMAP15XX_MCBSP_RES_SZ		ARRAY_SIZE(omap15xx_mcbsp_res[1])
#घोषणा OMAP15XX_MCBSP_COUNT		ARRAY_SIZE(omap15xx_mcbsp_res)
#अन्यथा
#घोषणा omap15xx_mcbsp_res_0		शून्य
#घोषणा omap15xx_mcbsp_pdata		शून्य
#घोषणा OMAP15XX_MCBSP_RES_SZ		0
#घोषणा OMAP15XX_MCBSP_COUNT		0
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP16XX
काष्ठा resource omap16xx_mcbsp_res[][6] = अणु
	अणु
		अणु
			.start = OMAP1610_MCBSP1_BASE,
			.end   = OMAP1610_MCBSP1_BASE + SZ_256,
			.flags = IORESOURCE_MEM,
		पूर्ण,
		अणु
			.name  = "rx",
			.start = INT_McBSP1RX,
			.flags = IORESOURCE_IRQ,
		पूर्ण,
		अणु
			.name  = "tx",
			.start = INT_McBSP1TX,
			.flags = IORESOURCE_IRQ,
		पूर्ण,
		अणु
			.name  = "rx",
			.start = 9,
			.flags = IORESOURCE_DMA,
		पूर्ण,
		अणु
			.name  = "tx",
			.start = 8,
			.flags = IORESOURCE_DMA,
		पूर्ण,
	पूर्ण,
	अणु
		अणु
			.start = OMAP1610_MCBSP2_BASE,
			.end   = OMAP1610_MCBSP2_BASE + SZ_256,
			.flags = IORESOURCE_MEM,
		पूर्ण,
		अणु
			.name  = "rx",
			.start = INT_1610_McBSP2_RX,
			.flags = IORESOURCE_IRQ,
		पूर्ण,
		अणु
			.name  = "tx",
			.start = INT_1610_McBSP2_TX,
			.flags = IORESOURCE_IRQ,
		पूर्ण,
		अणु
			.name  = "rx",
			.start = 17,
			.flags = IORESOURCE_DMA,
		पूर्ण,
		अणु
			.name  = "tx",
			.start = 16,
			.flags = IORESOURCE_DMA,
		पूर्ण,
	पूर्ण,
	अणु
		अणु
			.start = OMAP1610_MCBSP3_BASE,
			.end   = OMAP1610_MCBSP3_BASE + SZ_256,
			.flags = IORESOURCE_MEM,
		पूर्ण,
		अणु
			.name  = "rx",
			.start = INT_McBSP3RX,
			.flags = IORESOURCE_IRQ,
		पूर्ण,
		अणु
			.name  = "tx",
			.start = INT_McBSP3TX,
			.flags = IORESOURCE_IRQ,
		पूर्ण,
		अणु
			.name  = "rx",
			.start = 11,
			.flags = IORESOURCE_DMA,
		पूर्ण,
		अणु
			.name  = "tx",
			.start = 10,
			.flags = IORESOURCE_DMA,
		पूर्ण,
	पूर्ण,
पूर्ण;

#घोषणा omap16xx_mcbsp_res_0		omap16xx_mcbsp_res[0]

अटल काष्ठा omap_mcbsp_platक्रमm_data omap16xx_mcbsp_pdata[] = अणु
	अणु
		.ops		= &omap1_mcbsp_ops,
	पूर्ण,
	अणु
		.ops		= &omap1_mcbsp_ops,
	पूर्ण,
	अणु
		.ops		= &omap1_mcbsp_ops,
	पूर्ण,
पूर्ण;
#घोषणा OMAP16XX_MCBSP_RES_SZ		ARRAY_SIZE(omap16xx_mcbsp_res[1])
#घोषणा OMAP16XX_MCBSP_COUNT		ARRAY_SIZE(omap16xx_mcbsp_res)
#अन्यथा
#घोषणा omap16xx_mcbsp_res_0		शून्य
#घोषणा omap16xx_mcbsp_pdata		शून्य
#घोषणा OMAP16XX_MCBSP_RES_SZ		0
#घोषणा OMAP16XX_MCBSP_COUNT		0
#पूर्ण_अगर

अटल व्योम omap_mcbsp_रेजिस्टर_board_cfg(काष्ठा resource *res, पूर्णांक res_count,
			काष्ठा omap_mcbsp_platक्रमm_data *config, पूर्णांक size)
अणु
	पूर्णांक i;

	omap_mcbsp_devices = kसुस्मृति(size, माप(काष्ठा platक्रमm_device *),
				     GFP_KERNEL);
	अगर (!omap_mcbsp_devices) अणु
		prपूर्णांकk(KERN_ERR "Could not register McBSP devices\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i < size; i++) अणु
		काष्ठा platक्रमm_device *new_mcbsp;
		पूर्णांक ret;

		new_mcbsp = platक्रमm_device_alloc("omap-mcbsp", i + 1);
		अगर (!new_mcbsp)
			जारी;
		platक्रमm_device_add_resources(new_mcbsp, &res[i * res_count],
					res_count);
		config[i].reg_size = 2;
		config[i].reg_step = 2;
		new_mcbsp->dev.platक्रमm_data = &config[i];
		ret = platक्रमm_device_add(new_mcbsp);
		अगर (ret) अणु
			platक्रमm_device_put(new_mcbsp);
			जारी;
		पूर्ण
		omap_mcbsp_devices[i] = new_mcbsp;
	पूर्ण
पूर्ण

अटल पूर्णांक __init omap1_mcbsp_init(व्योम)
अणु
	अगर (!cpu_class_is_omap1())
		वापस -ENODEV;

	अगर (cpu_is_omap7xx())
		omap_mcbsp_रेजिस्टर_board_cfg(omap7xx_mcbsp_res_0,
					OMAP7XX_MCBSP_RES_SZ,
					omap7xx_mcbsp_pdata,
					OMAP7XX_MCBSP_COUNT);

	अगर (cpu_is_omap15xx())
		omap_mcbsp_रेजिस्टर_board_cfg(omap15xx_mcbsp_res_0,
					OMAP15XX_MCBSP_RES_SZ,
					omap15xx_mcbsp_pdata,
					OMAP15XX_MCBSP_COUNT);

	अगर (cpu_is_omap16xx())
		omap_mcbsp_रेजिस्टर_board_cfg(omap16xx_mcbsp_res_0,
					OMAP16XX_MCBSP_RES_SZ,
					omap16xx_mcbsp_pdata,
					OMAP16XX_MCBSP_COUNT);

	वापस 0;
पूर्ण

arch_initcall(omap1_mcbsp_init);
