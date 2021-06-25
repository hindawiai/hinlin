<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2012 Heiko Stuebner <heiko@sntech.de>
 */

#अगर_अघोषित __PLAT_S3C_SPI_CORE_S3C24XX_H
#घोषणा __PLAT_S3C_SPI_CORE_S3C24XX_H

/* These functions are only क्रम use with the core support code, such as
 * the cpu specअगरic initialisation code
 */

/* re-define device name depending on support. */
अटल अंतरभूत व्योम s3c24xx_spi_setname(अक्षर *name)
अणु
#अगर_घोषित CONFIG_S3C64XX_DEV_SPI0
	s3c64xx_device_spi0.name = name;
#पूर्ण_अगर
#अगर_घोषित CONFIG_S3C64XX_DEV_SPI1
	s3c64xx_device_spi1.name = name;
#पूर्ण_अगर
#अगर_घोषित CONFIG_S3C64XX_DEV_SPI2
	s3c64xx_device_spi2.name = name;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* __PLAT_S3C_SPI_CORE_S3C24XX_H */
