<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2006 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C2410 - SPI Controller platक्रमm_device info
*/

#अगर_अघोषित __LINUX_SPI_S3C24XX_H
#घोषणा __LINUX_SPI_S3C24XX_H __खाता__

काष्ठा s3c2410_spi_info अणु
	पूर्णांक			 pin_cs;	/* simple gpio cs */
	अचिन्हित पूर्णांक		 num_cs;	/* total chipselects */
	पूर्णांक			 bus_num;       /* bus number to use. */

	अचिन्हित पूर्णांक		 use_fiq:1;	/* use fiq */

	व्योम (*gpio_setup)(काष्ठा s3c2410_spi_info *spi, पूर्णांक enable);
	व्योम (*set_cs)(काष्ठा s3c2410_spi_info *spi, पूर्णांक cs, पूर्णांक pol);
पूर्ण;

बाह्य पूर्णांक s3c24xx_set_fiq(अचिन्हित पूर्णांक irq, u32 *ack_ptr, bool on);

#पूर्ण_अगर /* __LINUX_SPI_S3C24XX_H */
