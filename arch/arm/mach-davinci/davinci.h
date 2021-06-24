<शैली गुरु>
/*
 * This file contains the processor specअगरic definitions
 * of the TI DM644x, DM355, DM365, and DM646x.
 *
 * Copyright (C) 2011 Texas Instruments Incorporated
 * Copyright (c) 2007 Deep Root Systems, LLC
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */
#अगर_अघोषित __DAVINCI_H
#घोषणा __DAVINCI_H

#समावेश <linux/clk.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/davinci_emac.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/platक्रमm_data/davinci_asp.h>
#समावेश <linux/platक्रमm_data/edma.h>
#समावेश <linux/platक्रमm_data/keyscan-davinci.h>
#समावेश <mach/hardware.h>

#समावेश <media/davinci/vpfe_capture.h>
#समावेश <media/davinci/vpअगर_types.h>
#समावेश <media/davinci/vpss.h>
#समावेश <media/davinci/vpbe_types.h>
#समावेश <media/davinci/vpbe_venc.h>
#समावेश <media/davinci/vpbe.h>
#समावेश <media/davinci/vpbe_osd.h>

#घोषणा DAVINCI_PLL1_BASE		0x01c40800
#घोषणा DAVINCI_PLL2_BASE		0x01c40c00
#घोषणा DAVINCI_PWR_SLEEP_CNTRL_BASE	0x01c41000

#घोषणा DAVINCI_SYSTEM_MODULE_BASE	0x01c40000
#घोषणा SYSMOD_VDAC_CONFIG		0x2c
#घोषणा SYSMOD_VIDCLKCTL		0x38
#घोषणा SYSMOD_VPSS_CLKCTL		0x44
#घोषणा SYSMOD_VDD3P3VPWDN		0x48
#घोषणा SYSMOD_VSCLKDIS			0x6c
#घोषणा SYSMOD_PUPDCTL1			0x7c

/* VPSS CLKCTL bit definitions */
#घोषणा VPSS_MUXSEL_EXTCLK_ENABLE	BIT(1)
#घोषणा VPSS_VENCCLKEN_ENABLE		BIT(3)
#घोषणा VPSS_DACCLKEN_ENABLE		BIT(4)
#घोषणा VPSS_PLLC2SYSCLK5_ENABLE	BIT(5)

बाह्य व्योम __iomem *davinci_sysmod_base;
#घोषणा DAVINCI_SYSMOD_VIRT(x)	(davinci_sysmod_base + (x))
व्योम davinci_map_sysmod(व्योम);

#घोषणा DAVINCI_GPIO_BASE 0x01C67000
पूर्णांक davinci_gpio_रेजिस्टर(काष्ठा resource *res, पूर्णांक size, व्योम *pdata);

#घोषणा DAVINCI_TIMER0_BASE		(IO_PHYS + 0x21400)
#घोषणा DAVINCI_WDOG_BASE		(IO_PHYS + 0x21C00)

/* DM355 base addresses */
#घोषणा DM355_ASYNC_EMIF_CONTROL_BASE	0x01e10000
#घोषणा DM355_ASYNC_EMIF_DATA_CE0_BASE	0x02000000

#घोषणा ASP1_TX_EVT_EN	1
#घोषणा ASP1_RX_EVT_EN	2

/* DM365 base addresses */
#घोषणा DM365_ASYNC_EMIF_CONTROL_BASE	0x01d10000
#घोषणा DM365_ASYNC_EMIF_DATA_CE0_BASE	0x02000000
#घोषणा DM365_ASYNC_EMIF_DATA_CE1_BASE	0x04000000

/* DM644x base addresses */
#घोषणा DM644X_ASYNC_EMIF_CONTROL_BASE	0x01e00000
#घोषणा DM644X_ASYNC_EMIF_DATA_CE0_BASE 0x02000000
#घोषणा DM644X_ASYNC_EMIF_DATA_CE1_BASE 0x04000000
#घोषणा DM644X_ASYNC_EMIF_DATA_CE2_BASE 0x06000000
#घोषणा DM644X_ASYNC_EMIF_DATA_CE3_BASE 0x08000000

/* DM646x base addresses */
#घोषणा DM646X_ASYNC_EMIF_CONTROL_BASE	0x20008000
#घोषणा DM646X_ASYNC_EMIF_CS2_SPACE_BASE 0x42000000

पूर्णांक davinci_init_wdt(व्योम);

/* DM355 function declarations */
व्योम dm355_init(व्योम);
व्योम dm355_init_समय(व्योम);
व्योम dm355_init_irq(व्योम);
व्योम dm355_रेजिस्टर_घड़ीs(व्योम);
व्योम dm355_init_spi0(अचिन्हित chipselect_mask,
		स्थिर काष्ठा spi_board_info *info, अचिन्हित len);
व्योम dm355_init_asp1(u32 evt_enable);
पूर्णांक dm355_init_video(काष्ठा vpfe_config *, काष्ठा vpbe_config *);
पूर्णांक dm355_gpio_रेजिस्टर(व्योम);

/* DM365 function declarations */
व्योम dm365_init(व्योम);
व्योम dm365_init_irq(व्योम);
व्योम dm365_init_समय(व्योम);
व्योम dm365_रेजिस्टर_घड़ीs(व्योम);
व्योम dm365_init_asp(व्योम);
व्योम dm365_init_vc(व्योम);
व्योम dm365_init_ks(काष्ठा davinci_ks_platक्रमm_data *pdata);
व्योम dm365_init_rtc(व्योम);
व्योम dm365_init_spi0(अचिन्हित chipselect_mask,
			स्थिर काष्ठा spi_board_info *info, अचिन्हित len);
पूर्णांक dm365_init_video(काष्ठा vpfe_config *, काष्ठा vpbe_config *);
पूर्णांक dm365_gpio_रेजिस्टर(व्योम);

/* DM644x function declarations */
व्योम dm644x_init(व्योम);
व्योम dm644x_init_irq(व्योम);
व्योम dm644x_init_devices(व्योम);
व्योम dm644x_init_समय(व्योम);
व्योम dm644x_रेजिस्टर_घड़ीs(व्योम);
व्योम dm644x_init_asp(व्योम);
पूर्णांक dm644x_init_video(काष्ठा vpfe_config *, काष्ठा vpbe_config *);
पूर्णांक dm644x_gpio_रेजिस्टर(व्योम);

/* DM646x function declarations */
व्योम dm646x_init(व्योम);
व्योम dm646x_init_irq(व्योम);
व्योम dm646x_init_समय(अचिन्हित दीर्घ ref_clk_rate, अचिन्हित दीर्घ aux_clkin_rate);
व्योम dm646x_रेजिस्टर_घड़ीs(व्योम);
व्योम dm646x_init_mcasp0(काष्ठा snd_platक्रमm_data *pdata);
व्योम dm646x_init_mcasp1(काष्ठा snd_platक्रमm_data *pdata);
पूर्णांक dm646x_init_edma(काष्ठा edma_rsv_info *rsv);
व्योम dm646x_video_init(व्योम);
व्योम dm646x_setup_vpअगर(काष्ठा vpअगर_display_config *,
		       काष्ठा vpअगर_capture_config *);
पूर्णांक dm646x_gpio_रेजिस्टर(व्योम);

बाह्य काष्ठा platक्रमm_device dm365_serial_device[];
बाह्य काष्ठा platक्रमm_device dm355_serial_device[];
बाह्य काष्ठा platक्रमm_device dm644x_serial_device[];
बाह्य काष्ठा platक्रमm_device dm646x_serial_device[];
#पूर्ण_अगर /*__DAVINCI_H */
