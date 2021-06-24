<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Freescale DSPI controller driver
 *
 * Copyright (c) 2017 Angelo Dureghello <angelo@sysam.it>
 */

#अगर_अघोषित SPI_FSL_DSPI_HEADER_H
#घोषणा SPI_FSL_DSPI_HEADER_H

/**
 * काष्ठा fsl_dspi_platक्रमm_data - platक्रमm data क्रम the Freescale DSPI driver
 * @bus_num: board specअगरic identअगरier क्रम this DSPI driver.
 * @cs_num: number of chip selects supported by this DSPI driver.
 */
काष्ठा fsl_dspi_platक्रमm_data अणु
	u32 cs_num;
	u32 bus_num;
	u32 sck_cs_delay;
	u32 cs_sck_delay;
पूर्ण;

#पूर्ण_अगर /* SPI_FSL_DSPI_HEADER_H */
