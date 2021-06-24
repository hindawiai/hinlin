<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * S3C24XX DMA handling
 *
 * Copyright (c) 2013 Heiko Stuebner <heiko@sntech.de>
 */

/* Helper to encode the source selection स्थिरraपूर्णांकs क्रम early s3c socs. */
#घोषणा S3C24XX_DMA_CHANREQ(src, chan)	((BIT(3) | src) << chan * 4)

क्रमागत s3c24xx_dma_bus अणु
	S3C24XX_DMA_APB,
	S3C24XX_DMA_AHB,
पूर्ण;

/**
 * @bus: on which bus करोes the peripheral reside - AHB or APB.
 * @handshake: is a handshake with the peripheral necessary
 * @chansel: channel selection inक्रमmation, depending on variant; reqsel क्रम
 *	     s3c2443 and later and channel-selection map क्रम earlier SoCs
 *	     see CHANSEL करोc in s3c2443-dma.c
 */
काष्ठा s3c24xx_dma_channel अणु
	क्रमागत s3c24xx_dma_bus bus;
	bool handshake;
	u16 chansel;
पूर्ण;

काष्ठा dma_slave_map;

/**
 * काष्ठा s3c24xx_dma_platdata - platक्रमm specअगरic settings
 * @num_phy_channels: number of physical channels
 * @channels: array of भव channel descriptions
 * @num_channels: number of भव channels
 * @slave_map: dma slave map matching table
 * @slavecnt: number of elements in slave_map
 */
काष्ठा s3c24xx_dma_platdata अणु
	पूर्णांक num_phy_channels;
	काष्ठा s3c24xx_dma_channel *channels;
	पूर्णांक num_channels;
	स्थिर काष्ठा dma_slave_map *slave_map;
	पूर्णांक slavecnt;
पूर्ण;

काष्ठा dma_chan;
bool s3c24xx_dma_filter(काष्ठा dma_chan *chan, व्योम *param);
