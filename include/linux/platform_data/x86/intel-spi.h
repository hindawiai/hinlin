<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Intel PCH/PCU SPI flash driver.
 *
 * Copyright (C) 2016, Intel Corporation
 * Author: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#अगर_अघोषित INTEL_SPI_PDATA_H
#घोषणा INTEL_SPI_PDATA_H

क्रमागत पूर्णांकel_spi_type अणु
	INTEL_SPI_BYT = 1,
	INTEL_SPI_LPT,
	INTEL_SPI_BXT,
	INTEL_SPI_CNL,
पूर्ण;

/**
 * काष्ठा पूर्णांकel_spi_boardinfo - Board specअगरic data क्रम Intel SPI driver
 * @type: Type which this controller is compatible with
 * @ग_लिखोable: The chip is ग_लिखोable
 */
काष्ठा पूर्णांकel_spi_boardinfo अणु
	क्रमागत पूर्णांकel_spi_type type;
	bool ग_लिखोable;
पूर्ण;

#पूर्ण_अगर /* INTEL_SPI_PDATA_H */
