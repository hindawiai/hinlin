<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* linux/drivers/spi/spi_s3c24xx_fiq.h
 *
 * Copyright 2009 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C24XX SPI - FIQ pseuकरो-DMA transfer support
*/

#अगर_अघोषित __LINUX_SPI_S3C24XX_FIQ_H
#घोषणा __LINUX_SPI_S3C24XX_FIQ_H __खाता__

/* We have R8 through R13 to play with */

#अगर_घोषित __ASSEMBLY__
#घोषणा __REG_NR(x)     r##x
#अन्यथा

बाह्य काष्ठा spi_fiq_code s3c24xx_spi_fiq_txrx;
बाह्य काष्ठा spi_fiq_code s3c24xx_spi_fiq_tx;
बाह्य काष्ठा spi_fiq_code s3c24xx_spi_fiq_rx;

#घोषणा __REG_NR(x)     (x)
#पूर्ण_अगर

#घोषणा fiq_rspi	__REG_NR(8)
#घोषणा fiq_rपंचांगp	__REG_NR(9)
#घोषणा fiq_rrx		__REG_NR(10)
#घोषणा fiq_rtx		__REG_NR(11)
#घोषणा fiq_rcount	__REG_NR(12)
#घोषणा fiq_rirq	__REG_NR(13)

#पूर्ण_अगर /* __LINUX_SPI_S3C24XX_FIQ_H */
