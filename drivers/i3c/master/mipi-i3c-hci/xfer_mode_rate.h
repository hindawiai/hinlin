<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause */
/*
 * Copyright (c) 2020, MIPI Alliance, Inc.
 *
 * Author: Nicolas Pitre <npitre@baylibre.com>
 *
 * Transfer Mode/Rate Table definitions as found in extended capability
 * sections 0x04 and 0x08.
 * This applies starting from I3C HCI v2.0.
 */

#अगर_अघोषित XFER_MODE_RATE_H
#घोषणा XFER_MODE_RATE_H

/*
 * Master Transfer Mode Table Fixed Indexes.
 *
 * Indexes 0x0 and 0x8 are mandatory. Availability क्रम the rest must be
 * obtained from the mode table in the extended capability area.
 * Presence and definitions क्रम indexes beyond these ones may vary.
 */
#घोषणा XFERMODE_IDX_I3C_SDR		0x00	/* I3C SDR Mode */
#घोषणा XFERMODE_IDX_I3C_HDR_DDR	0x01	/* I3C HDR-DDR Mode */
#घोषणा XFERMODE_IDX_I3C_HDR_T		0x02	/* I3C HDR-Ternary Mode */
#घोषणा XFERMODE_IDX_I3C_HDR_BT		0x03	/* I3C HDR-BT Mode */
#घोषणा XFERMODE_IDX_I2C		0x08	/* Legacy I2C Mode */

/*
 * Transfer Mode Table Entry Bits Definitions
 */
#घोषणा XFERMODE_VALID_XFER_ADD_FUNC	GENMASK(21, 16)
#घोषणा XFERMODE_ML_DATA_XFER_CODING	GENMASK(15, 11)
#घोषणा XFERMODE_ML_ADDL_LANES		GENMASK(10, 8)
#घोषणा XFERMODE_SUPPORTED		BIT(7)
#घोषणा XFERMODE_MODE			GENMASK(3, 0)

/*
 * Master Data Transfer Rate Selector Values.
 *
 * These are the values to be used in the command descriptor XFER_RATE field
 * and found in the RATE_ID field below.
 * The I3C_SDR0, I3C_SDR1, I3C_SDR2, I3C_SDR3, I3C_SDR4 and I2C_FM rates
 * are required, everything अन्यथा is optional and discoverable in the
 * Data Transfer Rate Table. Indicated are typical rates. The actual
 * rates may vary slightly and are also specअगरied in the Data Transfer
 * Rate Table.
 */
#घोषणा XFERRATE_I3C_SDR0		0x00	/* 12.5 MHz */
#घोषणा XFERRATE_I3C_SDR1		0x01	/* 8 MHz */
#घोषणा XFERRATE_I3C_SDR2		0x02	/* 6 MHz */
#घोषणा XFERRATE_I3C_SDR3		0x03	/* 4 MHz */
#घोषणा XFERRATE_I3C_SDR4		0x04	/* 2 MHz */
#घोषणा XFERRATE_I3C_SDR_FM_FMP		0x05	/* 400 KHz / 1 MHz */
#घोषणा XFERRATE_I3C_SDR_USER6		0x06	/* User Defined */
#घोषणा XFERRATE_I3C_SDR_USER7		0x07	/* User Defined */

#घोषणा XFERRATE_I2C_FM			0x00	/* 400 KHz */
#घोषणा XFERRATE_I2C_FMP		0x01	/* 1 MHz */
#घोषणा XFERRATE_I2C_USER2		0x02	/* User Defined */
#घोषणा XFERRATE_I2C_USER3		0x03	/* User Defined */
#घोषणा XFERRATE_I2C_USER4		0x04	/* User Defined */
#घोषणा XFERRATE_I2C_USER5		0x05	/* User Defined */
#घोषणा XFERRATE_I2C_USER6		0x06	/* User Defined */
#घोषणा XFERRATE_I2C_USER7		0x07	/* User Defined */

/*
 * Master Data Transfer Rate Table Mode ID values.
 */
#घोषणा XFERRATE_MODE_I3C		0x00
#घोषणा XFERRATE_MODE_I2C		0x08

/*
 * Master Data Transfer Rate Table Entry Bits Definitions
 */
#घोषणा XFERRATE_MODE_ID		GENMASK(31, 28)
#घोषणा XFERRATE_RATE_ID		GENMASK(22, 20)
#घोषणा XFERRATE_ACTUAL_RATE_KHZ	GENMASK(19, 0)

#पूर्ण_अगर
