<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SDHCI driver क्रम Synopsys DWC_MSHC controller
 *
 * Copyright (C) 2018 Synopsys, Inc. (www.synopsys.com)
 *
 * Authors:
 *	Prabu Thangamuthu <prabu.t@synopsys.com>
 *	Manjunath M B <manjumb@synopsys.com>
 */

#समावेश "sdhci.h"
#समावेश "sdhci-pci.h"

#घोषणा SDHCI_VENDOR_PTR_R	0xE8

/* Synopsys venकरोr specअगरic रेजिस्टरs */
#घोषणा SDHC_GPIO_OUT		0x34
#घोषणा SDHC_AT_CTRL_R		0x40
#घोषणा SDHC_SW_TUNE_EN		0x00000010

/* MMCM DRP */
#घोषणा SDHC_MMCM_DIV_REG	0x1020
#घोषणा DIV_REG_100_MHZ		0x1145
#घोषणा DIV_REG_200_MHZ		0x1083
#घोषणा SDHC_MMCM_CLKFBOUT	0x1024
#घोषणा CLKFBOUT_100_MHZ	0x0000
#घोषणा CLKFBOUT_200_MHZ	0x0080
#घोषणा SDHC_CCLK_MMCM_RST	0x00000001

अटल व्योम sdhci_snps_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	u16 clk;
	u32 reg, venकरोr_ptr;

	venकरोr_ptr = sdhci_पढ़ोw(host, SDHCI_VENDOR_PTR_R);

	/* Disable software managed rx tuning */
	reg = sdhci_पढ़ोl(host, (SDHC_AT_CTRL_R + venकरोr_ptr));
	reg &= ~SDHC_SW_TUNE_EN;
	sdhci_ग_लिखोl(host, reg, (SDHC_AT_CTRL_R + venकरोr_ptr));

	अगर (घड़ी <= 52000000) अणु
		sdhci_set_घड़ी(host, घड़ी);
	पूर्ण अन्यथा अणु
		/* Assert reset to MMCM */
		reg = sdhci_पढ़ोl(host, (SDHC_GPIO_OUT + venकरोr_ptr));
		reg |= SDHC_CCLK_MMCM_RST;
		sdhci_ग_लिखोl(host, reg, (SDHC_GPIO_OUT + venकरोr_ptr));

		/* Configure MMCM */
		अगर (घड़ी == 100000000) अणु
			sdhci_ग_लिखोl(host, DIV_REG_100_MHZ, SDHC_MMCM_DIV_REG);
			sdhci_ग_लिखोl(host, CLKFBOUT_100_MHZ,
					SDHC_MMCM_CLKFBOUT);
		पूर्ण अन्यथा अणु
			sdhci_ग_लिखोl(host, DIV_REG_200_MHZ, SDHC_MMCM_DIV_REG);
			sdhci_ग_लिखोl(host, CLKFBOUT_200_MHZ,
					SDHC_MMCM_CLKFBOUT);
		पूर्ण

		/* De-निश्चित reset to MMCM */
		reg = sdhci_पढ़ोl(host, (SDHC_GPIO_OUT + venकरोr_ptr));
		reg &= ~SDHC_CCLK_MMCM_RST;
		sdhci_ग_लिखोl(host, reg, (SDHC_GPIO_OUT + venकरोr_ptr));

		/* Enable घड़ी */
		clk = SDHCI_PROG_CLOCK_MODE | SDHCI_CLOCK_INT_EN |
			SDHCI_CLOCK_CARD_EN;
		sdhci_ग_लिखोw(host, clk, SDHCI_CLOCK_CONTROL);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा sdhci_ops sdhci_snps_ops = अणु
	.set_घड़ी	= sdhci_snps_set_घड़ी,
	.enable_dma	= sdhci_pci_enable_dma,
	.set_bus_width	= sdhci_set_bus_width,
	.reset		= sdhci_reset,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
पूर्ण;

स्थिर काष्ठा sdhci_pci_fixes sdhci_snps = अणु
	.ops		= &sdhci_snps_ops,
पूर्ण;
