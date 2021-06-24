<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2004 Fetron GmbH
 *
 * S3C2410 SPI रेजिस्टर definition
 */

#अगर_अघोषित __SPI_S3C2410_H
#घोषणा __SPI_S3C2410_H

#घोषणा S3C2410_SPCON		(0x00)

#घोषणा S3C2410_SPCON_SMOD_DMA	(2 << 5)	/* DMA mode */
#घोषणा S3C2410_SPCON_SMOD_INT	(1 << 5)	/* पूर्णांकerrupt mode */
#घोषणा S3C2410_SPCON_SMOD_POLL	(0 << 5)	/* polling mode */
#घोषणा S3C2410_SPCON_ENSCK	(1 << 4)	/* Enable SCK */
#घोषणा S3C2410_SPCON_MSTR	(1 << 3)	/* Master:1, Slave:0 select */
#घोषणा S3C2410_SPCON_CPOL_HIGH	(1 << 2)	/* Clock polarity select */
#घोषणा S3C2410_SPCON_CPOL_LOW	(0 << 2)	/* Clock polarity select */

#घोषणा S3C2410_SPCON_CPHA_FMTB	(1 << 1)	/* Clock Phase Select */
#घोषणा S3C2410_SPCON_CPHA_FMTA	(0 << 1)	/* Clock Phase Select */

#घोषणा S3C2410_SPSTA		(0x04)

#घोषणा S3C2410_SPSTA_DCOL	(1 << 2)	/* Data Collision Error */
#घोषणा S3C2410_SPSTA_MULD	(1 << 1)	/* Multi Master Error */
#घोषणा S3C2410_SPSTA_READY	(1 << 0)	/* Data Tx/Rx पढ़ोy */
#घोषणा S3C2412_SPSTA_READY_ORG	(1 << 3)

#घोषणा S3C2410_SPPIN		(0x08)

#घोषणा S3C2410_SPPIN_ENMUL	(1 << 2)	/* Multi Master Error detect */
#घोषणा S3C2410_SPPIN_RESERVED	(1 << 1)
#घोषणा S3C2410_SPPIN_KEEP	(1 << 0)	/* Master Out keep */

#घोषणा S3C2410_SPPRE		(0x0C)
#घोषणा S3C2410_SPTDAT		(0x10)
#घोषणा S3C2410_SPRDAT		(0x14)

#पूर्ण_अगर /* __SPI_S3C2410_H */
