<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * Copyright (C) 2009 Samsung Electronics Ltd.
 *	Jaswinder Singh <jassi.brar@samsung.com>
 */

#अगर_अघोषित __SPI_S3C64XX_H
#घोषणा __SPI_S3C64XX_H

#समावेश <linux/dmaengine.h>

काष्ठा platक्रमm_device;

/**
 * काष्ठा s3c64xx_spi_csinfo - ChipSelect description
 * @fb_delay: Slave specअगरic feedback delay.
 *            Refer to FB_CLK_SEL रेजिस्टर definition in SPI chapter.
 * @line: Custom 'identity' of the CS line.
 *
 * This is per SPI-Slave Chipselect inक्रमmation.
 * Allocate and initialize one in machine init code and make the
 * spi_board_info.controller_data poपूर्णांक to it.
 */
काष्ठा s3c64xx_spi_csinfo अणु
	u8 fb_delay;
	अचिन्हित line;
पूर्ण;

/**
 * काष्ठा s3c64xx_spi_info - SPI Controller defining काष्ठाure
 * @src_clk_nr: Clock source index क्रम the CLK_CFG[SPI_CLKSEL] field.
 * @num_cs: Number of CS this controller emulates.
 * @cfg_gpio: Configure pins क्रम this SPI controller.
 */
काष्ठा s3c64xx_spi_info अणु
	पूर्णांक src_clk_nr;
	पूर्णांक num_cs;
	bool no_cs;
	पूर्णांक (*cfg_gpio)(व्योम);
पूर्ण;

/**
 * s3c64xx_spi_set_platdata - SPI Controller configure callback by the board
 *				initialization code.
 * @cfg_gpio: Poपूर्णांकer to gpio setup function.
 * @src_clk_nr: Clock the SPI controller is to use to generate SPI घड़ीs.
 * @num_cs: Number of elements in the 'cs' array.
 *
 * Call this from machine init code क्रम each SPI Controller that
 * has some chips attached to it.
 */
बाह्य व्योम s3c64xx_spi0_set_platdata(पूर्णांक (*cfg_gpio)(व्योम), पूर्णांक src_clk_nr,
						पूर्णांक num_cs);
बाह्य व्योम s3c64xx_spi1_set_platdata(पूर्णांक (*cfg_gpio)(व्योम), पूर्णांक src_clk_nr,
						पूर्णांक num_cs);
बाह्य व्योम s3c64xx_spi2_set_platdata(पूर्णांक (*cfg_gpio)(व्योम), पूर्णांक src_clk_nr,
						पूर्णांक num_cs);

/* defined by architecture to configure gpio */
बाह्य पूर्णांक s3c64xx_spi0_cfg_gpio(व्योम);
बाह्य पूर्णांक s3c64xx_spi1_cfg_gpio(व्योम);
बाह्य पूर्णांक s3c64xx_spi2_cfg_gpio(व्योम);

बाह्य काष्ठा s3c64xx_spi_info s3c64xx_spi0_pdata;
बाह्य काष्ठा s3c64xx_spi_info s3c64xx_spi1_pdata;
बाह्य काष्ठा s3c64xx_spi_info s3c64xx_spi2_pdata;
#पूर्ण_अगर /*__SPI_S3C64XX_H */
