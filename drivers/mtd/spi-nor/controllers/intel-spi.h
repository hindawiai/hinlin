<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Intel PCH/PCU SPI flash driver.
 *
 * Copyright (C) 2016, Intel Corporation
 * Author: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#अगर_अघोषित INTEL_SPI_H
#घोषणा INTEL_SPI_H

#समावेश <linux/platक्रमm_data/x86/पूर्णांकel-spi.h>

काष्ठा पूर्णांकel_spi;
काष्ठा resource;

काष्ठा पूर्णांकel_spi *पूर्णांकel_spi_probe(काष्ठा device *dev,
	काष्ठा resource *mem, स्थिर काष्ठा पूर्णांकel_spi_boardinfo *info);
पूर्णांक पूर्णांकel_spi_हटाओ(काष्ठा पूर्णांकel_spi *ispi);

#पूर्ण_अगर /* INTEL_SPI_H */
