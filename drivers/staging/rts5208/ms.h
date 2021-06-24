<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Wei WANG (wei_wang@realsil.com.cn)
 *   Micky Ching (micky_ching@realsil.com.cn)
 */

#अगर_अघोषित __REALTEK_RTSX_MS_H
#घोषणा __REALTEK_RTSX_MS_H

#घोषणा MS_DELAY_WRITE

#घोषणा	MS_MAX_RETRY_COUNT	3

#घोषणा	MS_EXTRA_SIZE		0x9

#घोषणा	WRT_PRTCT		0x01

/* Error Code */
#घोषणा	MS_NO_ERROR				0x00
#घोषणा	MS_CRC16_ERROR				0x80
#घोषणा	MS_TO_ERROR				0x40
#घोषणा	MS_NO_CARD				0x20
#घोषणा	MS_NO_MEMORY				0x10
#घोषणा	MS_CMD_NK				0x08
#घोषणा	MS_FLASH_READ_ERROR			0x04
#घोषणा	MS_FLASH_WRITE_ERROR			0x02
#घोषणा	MS_BREQ_ERROR				0x01
#घोषणा	MS_NOT_FOUND				0x03

/* Transfer Protocol Command */
#घोषणा READ_PAGE_DATA				0x02
#घोषणा READ_REG				0x04
#घोषणा	GET_INT					0x07
#घोषणा WRITE_PAGE_DATA				0x0D
#घोषणा WRITE_REG				0x0B
#घोषणा SET_RW_REG_ADRS				0x08
#घोषणा SET_CMD					0x0E

#घोषणा	PRO_READ_LONG_DATA			0x02
#घोषणा	PRO_READ_SHORT_DATA			0x03
#घोषणा PRO_READ_REG				0x04
#घोषणा	PRO_READ_QUAD_DATA			0x05
#घोषणा PRO_GET_INT				0x07
#घोषणा	PRO_WRITE_LONG_DATA			0x0D
#घोषणा	PRO_WRITE_SHORT_DATA			0x0C
#घोषणा	PRO_WRITE_QUAD_DATA			0x0A
#घोषणा PRO_WRITE_REG				0x0B
#घोषणा PRO_SET_RW_REG_ADRS			0x08
#घोषणा PRO_SET_CMD				0x0E
#घोषणा PRO_EX_SET_CMD				0x09

#अगर_घोषित SUPPORT_MAGIC_GATE

#घोषणा MG_GET_ID		0x40
#घोषणा MG_SET_LID		0x41
#घोषणा MG_GET_LEKB		0x42
#घोषणा MG_SET_RD		0x43
#घोषणा MG_MAKE_RMS		0x44
#घोषणा MG_MAKE_KSE		0x45
#घोषणा MG_SET_IBD		0x46
#घोषणा MG_GET_IBD		0x47

#पूर्ण_अगर

#अगर_घोषित XC_POWERCLASS
#घोषणा XC_CHG_POWER		0x16
#पूर्ण_अगर

#घोषणा BLOCK_READ	0xAA
#घोषणा	BLOCK_WRITE	0x55
#घोषणा BLOCK_END	0x33
#घोषणा BLOCK_ERASE	0x99
#घोषणा FLASH_STOP	0xCC

#घोषणा SLEEP		0x5A
#घोषणा CLEAR_BUF	0xC3
#घोषणा MS_RESET	0x3C

#घोषणा PRO_READ_DATA		0x20
#घोषणा	PRO_WRITE_DATA		0x21
#घोषणा PRO_READ_ATRB		0x24
#घोषणा PRO_STOP		0x25
#घोषणा PRO_ERASE		0x26
#घोषणा	PRO_READ_2K_DATA	0x27
#घोषणा	PRO_WRITE_2K_DATA	0x28

#घोषणा PRO_FORMAT		0x10
#घोषणा PRO_SLEEP		0x11

#घोषणा INT_REG			0x01
#घोषणा STATUS_REG0		0x02
#घोषणा STATUS_REG1		0x03

#घोषणा SYSTEM_PARAM		0x10
#घोषणा BLOCK_ADRS		0x11
#घोषणा CMD_PARM		0x14
#घोषणा PAGE_ADRS		0x15

#घोषणा OVERWRITE_FLAG		0x16
#घोषणा MANAGEMEN_FLAG		0x17
#घोषणा LOGICAL_ADRS		0x18
#घोषणा RESERVE_AREA		0x1A

#घोषणा PRO_INT_REG		0x01
#घोषणा PRO_STATUS_REG		0x02
#घोषणा PRO_TYPE_REG		0x04
#घोषणा PRO_IF_mode_REG		0x05
#घोषणा PRO_CATEGORY_REG	0x06
#घोषणा PRO_CLASS_REG		0x07

#घोषणा PRO_SYSTEM_PARAM		0x10
#घोषणा PRO_DATA_COUNT1		0x11
#घोषणा PRO_DATA_COUNT0		0x12
#घोषणा PRO_DATA_ADDR3		0x13
#घोषणा PRO_DATA_ADDR2		0x14
#घोषणा PRO_DATA_ADDR1		0x15
#घोषणा PRO_DATA_ADDR0		0x16

#घोषणा PRO_TPC_PARM		0x17
#घोषणा PRO_CMD_PARM		0x18

#घोषणा	INT_REG_CED		0x80
#घोषणा	INT_REG_ERR		0x40
#घोषणा	INT_REG_BREQ		0x20
#घोषणा	INT_REG_CMDNK		0x01

#घोषणा	BLOCK_BOOT		0xC0
#घोषणा	BLOCK_OK		0x80
#घोषणा	PAGE_OK			0x60
#घोषणा	DATA_COMPL		0x10

#घोषणा	NOT_BOOT_BLOCK		0x4
#घोषणा	NOT_TRANSLATION_TABLE	0x8

#घोषणा	HEADER_ID0		PPBUF_BASE2
#घोषणा	HEADER_ID1		(PPBUF_BASE2 + 1)
#घोषणा	DISABLED_BLOCK0		(PPBUF_BASE2 + 0x170 + 4)
#घोषणा	DISABLED_BLOCK1		(PPBUF_BASE2 + 0x170 + 5)
#घोषणा	DISABLED_BLOCK2		(PPBUF_BASE2 + 0x170 + 6)
#घोषणा	DISABLED_BLOCK3		(PPBUF_BASE2 + 0x170 + 7)
#घोषणा	BLOCK_SIZE_0		(PPBUF_BASE2 + 0x1a0 + 2)
#घोषणा	BLOCK_SIZE_1		(PPBUF_BASE2 + 0x1a0 + 3)
#घोषणा	BLOCK_COUNT_0		(PPBUF_BASE2 + 0x1a0 + 4)
#घोषणा	BLOCK_COUNT_1		(PPBUF_BASE2 + 0x1a0 + 5)
#घोषणा	EBLOCK_COUNT_0		(PPBUF_BASE2 + 0x1a0 + 6)
#घोषणा	EBLOCK_COUNT_1		(PPBUF_BASE2 + 0x1a0 + 7)
#घोषणा	PAGE_SIZE_0		(PPBUF_BASE2 + 0x1a0 + 8)
#घोषणा	PAGE_SIZE_1		(PPBUF_BASE2 + 0x1a0 + 9)

#घोषणा MS_device_type		(PPBUF_BASE2 + 0x1D8)

#घोषणा MS_4bit_support		(PPBUF_BASE2 + 0x1D3)

#घोषणा set_PS_NG	1
#घोषणा set_PS_error	0

#घोषणा	PARALLEL_8BIT_IF	0x40
#घोषणा	PARALLEL_4BIT_IF	0x00
#घोषणा	SERIAL_IF		0x80

#घोषणा BUF_FULL	0x10
#घोषणा BUF_EMPTY	0x20

#घोषणा	MEDIA_BUSY	0x80
#घोषणा	FLASH_BUSY	0x40
#घोषणा	DATA_ERROR	0x20
#घोषणा	STS_UCDT	0x10
#घोषणा	EXTRA_ERROR	0x08
#घोषणा	STS_UCEX	0x04
#घोषणा	FLAG_ERROR	0x02
#घोषणा	STS_UCFG	0x01

#घोषणा MS_SHORT_DATA_LEN	32

#घोषणा FORMAT_SUCCESS		0
#घोषणा FORMAT_FAIL		1
#घोषणा FORMAT_IN_PROGRESS	2

#घोषणा	MS_SET_BAD_BLOCK_FLG(ms_card)	((ms_card)->multi_flag |= 0x80)
#घोषणा MS_CLR_BAD_BLOCK_FLG(ms_card)	((ms_card)->multi_flag &= 0x7F)
#घोषणा MS_TST_BAD_BLOCK_FLG(ms_card)	((ms_card)->multi_flag & 0x80)

व्योम mspro_polling_क्रमmat_status(काष्ठा rtsx_chip *chip);

व्योम mspro_stop_seq_mode(काष्ठा rtsx_chip *chip);
पूर्णांक reset_ms_card(काष्ठा rtsx_chip *chip);
पूर्णांक ms_rw(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip,
	  u32 start_sector, u16 sector_cnt);
पूर्णांक mspro_क्रमmat(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip,
		 पूर्णांक लघु_data_len, bool quick_क्रमmat);
व्योम ms_मुक्त_l2p_tbl(काष्ठा rtsx_chip *chip);
व्योम ms_cleanup_work(काष्ठा rtsx_chip *chip);
पूर्णांक ms_घातer_off_card3v3(काष्ठा rtsx_chip *chip);
पूर्णांक release_ms_card(काष्ठा rtsx_chip *chip);
#अगर_घोषित MS_DELAY_WRITE
पूर्णांक ms_delay_ग_लिखो(काष्ठा rtsx_chip *chip);
#पूर्ण_अगर

#अगर_घोषित SUPPORT_MAGIC_GATE
पूर्णांक mg_set_leaf_id(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);
पूर्णांक mg_get_local_EKB(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);
पूर्णांक mg_chg(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);
पूर्णांक mg_get_rsp_chg(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);
पूर्णांक mg_rsp(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);
पूर्णांक mg_get_ICV(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);
पूर्णांक mg_set_ICV(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);
#पूर्ण_अगर

#पूर्ण_अगर  /* __REALTEK_RTSX_MS_H */
