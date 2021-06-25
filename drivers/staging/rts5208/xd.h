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

#अगर_अघोषित __REALTEK_RTSX_XD_H
#घोषणा __REALTEK_RTSX_XD_H

#घोषणा	XD_DELAY_WRITE

/* Error Codes */
#घोषणा	XD_NO_ERROR			0x00
#घोषणा	XD_NO_MEMORY			0x80
#घोषणा	XD_PRG_ERROR			0x40
#घोषणा	XD_NO_CARD			0x20
#घोषणा	XD_READ_FAIL			0x10
#घोषणा	XD_ERASE_FAIL			0x08
#घोषणा	XD_WRITE_FAIL			0x04
#घोषणा	XD_ECC_ERROR			0x02
#घोषणा	XD_TO_ERROR			0x01

/* XD Commands */
#घोषणा	READ1_1				0x00
#घोषणा	READ1_2				0x01
#घोषणा	READ2				0x50
#घोषणा READ_ID				0x90
#घोषणा RESET				0xff
#घोषणा PAGE_PRG_1			0x80
#घोषणा PAGE_PRG_2			0x10
#घोषणा	BLK_ERASE_1			0x60
#घोषणा	BLK_ERASE_2			0xD0
#घोषणा READ_STS			0x70
#घोषणा READ_XD_ID			0x9A
#घोषणा	COPY_BACK_512			0x8A
#घोषणा	COPY_BACK_2K			0x85
#घोषणा	READ1_1_2			0x30
#घोषणा	READ1_1_3			0x35
#घोषणा	CHG_DAT_OUT_1			0x05
#घोषणा RDM_DAT_OUT_1			0x05
#घोषणा	CHG_DAT_OUT_2			0xE0
#घोषणा RDM_DAT_OUT_2			0xE0
#घोषणा	CHG_DAT_OUT_2			0xE0
#घोषणा	CHG_DAT_IN_1			0x85
#घोषणा	CACHE_PRG			0x15

/* Redundant Area Related */
#घोषणा XD_EXTRA_SIZE			0x10
#घोषणा XD_2K_EXTRA_SIZE		0x40

#घोषणा	NOT_WRITE_PROTECTED		0x80
#घोषणा	READY_STATE			0x40
#घोषणा	PROGRAM_ERROR			0x01
#घोषणा	PROGRAM_ERROR_N_1		0x02
#घोषणा	INTERNAL_READY			0x20
#घोषणा	READY_FLAG			0x5F

#घोषणा	XD_8M_X8_512			0xE6
#घोषणा	XD_16M_X8_512			0x73
#घोषणा	XD_32M_X8_512			0x75
#घोषणा	XD_64M_X8_512			0x76
#घोषणा	XD_128M_X8_512			0x79
#घोषणा	XD_256M_X8_512			0x71
#घोषणा	XD_128M_X8_2048			0xF1
#घोषणा	XD_256M_X8_2048			0xDA
#घोषणा	XD_512M_X8			0xDC
#घोषणा	XD_128M_X16_2048		0xC1
#घोषणा	XD_4M_X8_512_1			0xE3
#घोषणा	XD_4M_X8_512_2			0xE5
#घोषणा	XD_1G_X8_512			0xD3
#घोषणा	XD_2G_X8_512			0xD5

#घोषणा	XD_ID_CODE			0xB5

#घोषणा	VENDOR_BLOCK			0xEFFF
#घोषणा	CIS_BLOCK			0xDFFF

#घोषणा	BLK_NOT_FOUND			0xFFFFFFFF

#घोषणा	NO_NEW_BLK			0xFFFFFFFF

#घोषणा	PAGE_CORRECTABLE		0x0
#घोषणा	PAGE_NOTCORRECTABLE		0x1

#घोषणा	NO_OFFSET			0x0
#घोषणा	WITH_OFFSET			0x1

#घोषणा	SECT_PER_PAGE			4
#घोषणा	XD_ADDR_MODE_2C			XD_ADDR_MODE_2A

#घोषणा ZONE0_BAD_BLOCK			23
#घोषणा NOT_ZONE0_BAD_BLOCK		24

#घोषणा	XD_RW_ADDR			0x01
#घोषणा	XD_ERASE_ADDR			0x02

#घोषणा	XD_PAGE_512(xd_card)		\
करो अणु					\
	(xd_card)->block_shअगरt = 5;	\
	(xd_card)->page_off = 0x1F;	\
पूर्ण जबतक (0)

#घोषणा	XD_SET_BAD_NEWBLK(xd_card)	((xd_card)->multi_flag |= 0x01)
#घोषणा	XD_CLR_BAD_NEWBLK(xd_card)	((xd_card)->multi_flag &= ~0x01)
#घोषणा	XD_CHK_BAD_NEWBLK(xd_card)	((xd_card)->multi_flag & 0x01)

#घोषणा	XD_SET_BAD_OLDBLK(xd_card)	((xd_card)->multi_flag |= 0x02)
#घोषणा	XD_CLR_BAD_OLDBLK(xd_card)	((xd_card)->multi_flag &= ~0x02)
#घोषणा	XD_CHK_BAD_OLDBLK(xd_card)	((xd_card)->multi_flag & 0x02)

#घोषणा	XD_SET_MBR_FAIL(xd_card)	((xd_card)->multi_flag |= 0x04)
#घोषणा	XD_CLR_MBR_FAIL(xd_card)	((xd_card)->multi_flag &= ~0x04)
#घोषणा	XD_CHK_MBR_FAIL(xd_card)	((xd_card)->multi_flag & 0x04)

#घोषणा	XD_SET_ECC_FLD_ERR(xd_card)	((xd_card)->multi_flag |= 0x08)
#घोषणा	XD_CLR_ECC_FLD_ERR(xd_card)	((xd_card)->multi_flag &= ~0x08)
#घोषणा	XD_CHK_ECC_FLD_ERR(xd_card)	((xd_card)->multi_flag & 0x08)

#घोषणा	XD_SET_4MB(xd_card)		((xd_card)->multi_flag |= 0x10)
#घोषणा	XD_CLR_4MB(xd_card)		((xd_card)->multi_flag &= ~0x10)
#घोषणा	XD_CHK_4MB(xd_card)		((xd_card)->multi_flag & 0x10)

#घोषणा	XD_SET_ECC_ERR(xd_card)		((xd_card)->multi_flag |= 0x40)
#घोषणा	XD_CLR_ECC_ERR(xd_card)		((xd_card)->multi_flag &= ~0x40)
#घोषणा	XD_CHK_ECC_ERR(xd_card)		((xd_card)->multi_flag & 0x40)

#घोषणा PAGE_STATUS		0
#घोषणा BLOCK_STATUS		1
#घोषणा BLOCK_ADDR1_L		2
#घोषणा BLOCK_ADDR1_H		3
#घोषणा BLOCK_ADDR2_L		4
#घोषणा BLOCK_ADDR2_H		5
#घोषणा RESERVED0		6
#घोषणा RESERVED1		7
#घोषणा RESERVED2		8
#घोषणा RESERVED3		9
#घोषणा PARITY			10

#घोषणा	CIS0_0			0
#घोषणा	CIS0_1			1
#घोषणा	CIS0_2			2
#घोषणा	CIS0_3			3
#घोषणा	CIS0_4			4
#घोषणा	CIS0_5			5
#घोषणा	CIS0_6			6
#घोषणा	CIS0_7			7
#घोषणा	CIS0_8			8
#घोषणा	CIS0_9			9
#घोषणा	CIS1_0			256
#घोषणा	CIS1_1			(256 + 1)
#घोषणा	CIS1_2			(256 + 2)
#घोषणा	CIS1_3			(256 + 3)
#घोषणा	CIS1_4			(256 + 4)
#घोषणा	CIS1_5			(256 + 5)
#घोषणा	CIS1_6			(256 + 6)
#घोषणा	CIS1_7			(256 + 7)
#घोषणा	CIS1_8			(256 + 8)
#घोषणा	CIS1_9			(256 + 9)

पूर्णांक reset_xd_card(काष्ठा rtsx_chip *chip);
#अगर_घोषित XD_DELAY_WRITE
पूर्णांक xd_delay_ग_लिखो(काष्ठा rtsx_chip *chip);
#पूर्ण_अगर
पूर्णांक xd_rw(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip,
	  u32 start_sector, u16 sector_cnt);
व्योम xd_मुक्त_l2p_tbl(काष्ठा rtsx_chip *chip);
व्योम xd_cleanup_work(काष्ठा rtsx_chip *chip);
पूर्णांक xd_घातer_off_card3v3(काष्ठा rtsx_chip *chip);
पूर्णांक release_xd_card(काष्ठा rtsx_chip *chip);

#पूर्ण_अगर  /* __REALTEK_RTSX_XD_H */
