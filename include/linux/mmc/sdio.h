<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  include/linux/mmc/sdपन.स
 *
 *  Copyright 2006-2007 Pierre Ossman
 */

#अगर_अघोषित LINUX_MMC_SDIO_H
#घोषणा LINUX_MMC_SDIO_H

/* SDIO commands                         type  argument     response */
#घोषणा SD_IO_SEND_OP_COND          5 /* bcr  [23:0] OCR         R4  */
#घोषणा SD_IO_RW_सूचीECT            52 /* ac   [31:0] See below   R5  */
#घोषणा SD_IO_RW_EXTENDED          53 /* adtc [31:0] See below   R5  */

/*
 * SD_IO_RW_सूचीECT argument क्रमmat:
 *
 *      [31] R/W flag
 *      [30:28] Function number
 *      [27] RAW flag
 *      [25:9] Register address
 *      [7:0] Data
 */

/*
 * SD_IO_RW_EXTENDED argument क्रमmat:
 *
 *      [31] R/W flag
 *      [30:28] Function number
 *      [27] Block mode
 *      [26] Increment address
 *      [25:9] Register address
 *      [8:0] Byte/block count
 */

#घोषणा R4_18V_PRESENT (1<<24)
#घोषणा R4_MEMORY_PRESENT (1 << 27)

/*
  SDIO status in R5
  Type
	e : error bit
	s : status bit
	r : detected and set क्रम the actual command response
	x : detected and set during command execution. the host must poll
            the card by sending status command in order to पढ़ो these bits.
  Clear condition
	a : according to the card state
	b : always related to the previous command. Reception of
            a valid command will clear it (with a delay of one command)
	c : clear by पढ़ो
 */

#घोषणा R5_COM_CRC_ERROR	(1 << 15)	/* er, b */
#घोषणा R5_ILLEGAL_COMMAND	(1 << 14)	/* er, b */
#घोषणा R5_ERROR		(1 << 11)	/* erx, c */
#घोषणा R5_FUNCTION_NUMBER	(1 << 9)	/* er, c */
#घोषणा R5_OUT_OF_RANGE		(1 << 8)	/* er, c */
#घोषणा R5_STATUS(x)		(x & 0xCB00)
#घोषणा R5_IO_CURRENT_STATE(x)	((x & 0x3000) >> 12) /* s, b */

/*
 * Card Common Control Registers (CCCR)
 */

#घोषणा SDIO_CCCR_CCCR		0x00

#घोषणा  SDIO_CCCR_REV_1_00	0	/* CCCR/FBR Version 1.00 */
#घोषणा  SDIO_CCCR_REV_1_10	1	/* CCCR/FBR Version 1.10 */
#घोषणा  SDIO_CCCR_REV_1_20	2	/* CCCR/FBR Version 1.20 */
#घोषणा  SDIO_CCCR_REV_3_00	3	/* CCCR/FBR Version 3.00 */

#घोषणा  SDIO_SDIO_REV_1_00	0	/* SDIO Spec Version 1.00 */
#घोषणा  SDIO_SDIO_REV_1_10	1	/* SDIO Spec Version 1.10 */
#घोषणा  SDIO_SDIO_REV_1_20	2	/* SDIO Spec Version 1.20 */
#घोषणा  SDIO_SDIO_REV_2_00	3	/* SDIO Spec Version 2.00 */
#घोषणा  SDIO_SDIO_REV_3_00	4	/* SDIO Spec Version 3.00 */

#घोषणा SDIO_CCCR_SD		0x01

#घोषणा  SDIO_SD_REV_1_01	0	/* SD Physical Spec Version 1.01 */
#घोषणा  SDIO_SD_REV_1_10	1	/* SD Physical Spec Version 1.10 */
#घोषणा  SDIO_SD_REV_2_00	2	/* SD Physical Spec Version 2.00 */
#घोषणा  SDIO_SD_REV_3_00	3	/* SD Physical Spec Version 3.00 */

#घोषणा SDIO_CCCR_IOEx		0x02
#घोषणा SDIO_CCCR_IORx		0x03

#घोषणा SDIO_CCCR_IENx		0x04	/* Function/Master Interrupt Enable */
#घोषणा SDIO_CCCR_INTx		0x05	/* Function Interrupt Pending */

#घोषणा SDIO_CCCR_ABORT		0x06	/* function पात/card reset */

#घोषणा SDIO_CCCR_IF		0x07	/* bus पूर्णांकerface controls */

#घोषणा  SDIO_BUS_WIDTH_MASK	0x03	/* data bus width setting */
#घोषणा  SDIO_BUS_WIDTH_1BIT	0x00
#घोषणा  SDIO_BUS_WIDTH_RESERVED 0x01
#घोषणा  SDIO_BUS_WIDTH_4BIT	0x02
#घोषणा  SDIO_BUS_ECSI		0x20	/* Enable continuous SPI पूर्णांकerrupt */
#घोषणा  SDIO_BUS_SCSI		0x40	/* Support continuous SPI पूर्णांकerrupt */

#घोषणा  SDIO_BUS_ASYNC_INT	0x20

#घोषणा  SDIO_BUS_CD_DISABLE     0x80	/* disable pull-up on DAT3 (pin 1) */

#घोषणा SDIO_CCCR_CAPS		0x08

#घोषणा  SDIO_CCCR_CAP_SDC	0x01	/* can करो CMD52 जबतक data transfer */
#घोषणा  SDIO_CCCR_CAP_SMB	0x02	/* can करो multi-block xfers (CMD53) */
#घोषणा  SDIO_CCCR_CAP_SRW	0x04	/* supports पढ़ो-रुको protocol */
#घोषणा  SDIO_CCCR_CAP_SBS	0x08	/* supports suspend/resume */
#घोषणा  SDIO_CCCR_CAP_S4MI	0x10	/* पूर्णांकerrupt during 4-bit CMD53 */
#घोषणा  SDIO_CCCR_CAP_E4MI	0x20	/* enable पूर्णांकs during 4-bit CMD53 */
#घोषणा  SDIO_CCCR_CAP_LSC	0x40	/* low speed card */
#घोषणा  SDIO_CCCR_CAP_4BLS	0x80	/* 4 bit low speed card */

#घोषणा SDIO_CCCR_CIS		0x09	/* common CIS poपूर्णांकer (3 bytes) */

/* Following 4 regs are valid only अगर SBS is set */
#घोषणा SDIO_CCCR_SUSPEND	0x0c
#घोषणा SDIO_CCCR_SELx		0x0d
#घोषणा SDIO_CCCR_EXECx		0x0e
#घोषणा SDIO_CCCR_READYx	0x0f

#घोषणा SDIO_CCCR_BLKSIZE	0x10

#घोषणा SDIO_CCCR_POWER		0x12

#घोषणा  SDIO_POWER_SMPC	0x01	/* Supports Master Power Control */
#घोषणा  SDIO_POWER_EMPC	0x02	/* Enable Master Power Control */

#घोषणा SDIO_CCCR_SPEED		0x13

#घोषणा  SDIO_SPEED_SHS		0x01	/* Supports High-Speed mode */
#घोषणा  SDIO_SPEED_BSS_SHIFT	1
#घोषणा  SDIO_SPEED_BSS_MASK	(7<<SDIO_SPEED_BSS_SHIFT)
#घोषणा  SDIO_SPEED_SDR12	(0<<SDIO_SPEED_BSS_SHIFT)
#घोषणा  SDIO_SPEED_SDR25	(1<<SDIO_SPEED_BSS_SHIFT)
#घोषणा  SDIO_SPEED_SDR50	(2<<SDIO_SPEED_BSS_SHIFT)
#घोषणा  SDIO_SPEED_SDR104	(3<<SDIO_SPEED_BSS_SHIFT)
#घोषणा  SDIO_SPEED_DDR50	(4<<SDIO_SPEED_BSS_SHIFT)
#घोषणा  SDIO_SPEED_EHS		SDIO_SPEED_SDR25	/* Enable High-Speed */

#घोषणा SDIO_CCCR_UHS		0x14
#घोषणा  SDIO_UHS_SDR50		0x01
#घोषणा  SDIO_UHS_SDR104	0x02
#घोषणा  SDIO_UHS_DDR50		0x04

#घोषणा SDIO_CCCR_DRIVE_STRENGTH 0x15
#घोषणा  SDIO_SDTx_MASK		0x07
#घोषणा  SDIO_DRIVE_SDTA	(1<<0)
#घोषणा  SDIO_DRIVE_SDTC	(1<<1)
#घोषणा  SDIO_DRIVE_SDTD	(1<<2)
#घोषणा  SDIO_DRIVE_DTSx_MASK	0x03
#घोषणा  SDIO_DRIVE_DTSx_SHIFT	4
#घोषणा  SDIO_DTSx_SET_TYPE_B	(0 << SDIO_DRIVE_DTSx_SHIFT)
#घोषणा  SDIO_DTSx_SET_TYPE_A	(1 << SDIO_DRIVE_DTSx_SHIFT)
#घोषणा  SDIO_DTSx_SET_TYPE_C	(2 << SDIO_DRIVE_DTSx_SHIFT)
#घोषणा  SDIO_DTSx_SET_TYPE_D	(3 << SDIO_DRIVE_DTSx_SHIFT)
/*
 * Function Basic Registers (FBR)
 */

#घोषणा SDIO_FBR_BASE(f)	((f) * 0x100) /* base of function f's FBRs */

#घोषणा SDIO_FBR_STD_IF		0x00

#घोषणा  SDIO_FBR_SUPPORTS_CSA	0x40	/* supports Code Storage Area */
#घोषणा  SDIO_FBR_ENABLE_CSA	0x80	/* enable Code Storage Area */

#घोषणा SDIO_FBR_STD_IF_EXT	0x01

#घोषणा SDIO_FBR_POWER		0x02

#घोषणा  SDIO_FBR_POWER_SPS	0x01	/* Supports Power Selection */
#घोषणा  SDIO_FBR_POWER_EPS	0x02	/* Enable (low) Power Selection */

#घोषणा SDIO_FBR_CIS		0x09	/* CIS poपूर्णांकer (3 bytes) */


#घोषणा SDIO_FBR_CSA		0x0C	/* CSA poपूर्णांकer (3 bytes) */

#घोषणा SDIO_FBR_CSA_DATA	0x0F

#घोषणा SDIO_FBR_BLKSIZE	0x10	/* block size (2 bytes) */

#पूर्ण_अगर /* LINUX_MMC_SDIO_H */
