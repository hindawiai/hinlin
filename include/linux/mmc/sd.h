<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  include/linux/mmc/sd.h
 *
 *  Copyright (C) 2005-2007 Pierre Ossman, All Rights Reserved.
 */

#अगर_अघोषित LINUX_MMC_SD_H
#घोषणा LINUX_MMC_SD_H

/* SD commands                           type  argument     response */
  /* class 0 */
/* This is basically the same command as क्रम MMC with some quirks. */
#घोषणा SD_SEND_RELATIVE_ADDR     3   /* bcr                     R6  */
#घोषणा SD_SEND_IF_COND           8   /* bcr  [11:0] See below   R7  */
#घोषणा SD_SWITCH_VOLTAGE         11  /* ac                      R1  */

  /* class 10 */
#घोषणा SD_SWITCH                 6   /* adtc [31:0] See below   R1  */

  /* class 5 */
#घोषणा SD_ERASE_WR_BLK_START    32   /* ac   [31:0] data addr   R1  */
#घोषणा SD_ERASE_WR_BLK_END      33   /* ac   [31:0] data addr   R1  */

  /* Application commands */
#घोषणा SD_APP_SET_BUS_WIDTH      6   /* ac   [1:0] bus width    R1  */
#घोषणा SD_APP_SD_STATUS         13   /* adtc                    R1  */
#घोषणा SD_APP_SEND_NUM_WR_BLKS  22   /* adtc                    R1  */
#घोषणा SD_APP_OP_COND           41   /* bcr  [31:0] OCR         R3  */
#घोषणा SD_APP_SEND_SCR          51   /* adtc                    R1  */

/* OCR bit definitions */
#घोषणा SD_OCR_S18R		(1 << 24)    /* 1.8V चयनing request */
#घोषणा SD_ROCR_S18A		SD_OCR_S18R  /* 1.8V चयनing accepted by card */
#घोषणा SD_OCR_XPC		(1 << 28)    /* SDXC घातer control */
#घोषणा SD_OCR_CCS		(1 << 30)    /* Card Capacity Status */

/*
 * SD_SWITCH argument क्रमmat:
 *
 *      [31] Check (0) or चयन (1)
 *      [30:24] Reserved (0)
 *      [23:20] Function group 6
 *      [19:16] Function group 5
 *      [15:12] Function group 4
 *      [11:8] Function group 3
 *      [7:4] Function group 2
 *      [3:0] Function group 1
 */

/*
 * SD_SEND_IF_COND argument क्रमmat:
 *
 *	[31:12] Reserved (0)
 *	[11:8] Host Voltage Supply Flags
 *	[7:0] Check Pattern (0xAA)
 */

/*
 * SCR field definitions
 */

#घोषणा SCR_SPEC_VER_0		0	/* Implements प्रणाली specअगरication 1.0 - 1.01 */
#घोषणा SCR_SPEC_VER_1		1	/* Implements प्रणाली specअगरication 1.10 */
#घोषणा SCR_SPEC_VER_2		2	/* Implements प्रणाली specअगरication 2.00-3.0X */

/*
 * SD bus widths
 */
#घोषणा SD_BUS_WIDTH_1		0
#घोषणा SD_BUS_WIDTH_4		2

/*
 * SD_SWITCH mode
 */
#घोषणा SD_SWITCH_CHECK		0
#घोषणा SD_SWITCH_SET		1

/*
 * SD_SWITCH function groups
 */
#घोषणा SD_SWITCH_GRP_ACCESS	0

/*
 * SD_SWITCH access modes
 */
#घोषणा SD_SWITCH_ACCESS_DEF	0
#घोषणा SD_SWITCH_ACCESS_HS	1

/*
 * Erase/discard
 */
#घोषणा SD_ERASE_ARG			0x00000000
#घोषणा SD_DISCARD_ARG			0x00000001

#पूर्ण_अगर /* LINUX_MMC_SD_H */
