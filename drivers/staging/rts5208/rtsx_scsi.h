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

#अगर_अघोषित __REALTEK_RTSX_SCSI_H
#घोषणा __REALTEK_RTSX_SCSI_H

#समावेश "rtsx.h"
#समावेश "rtsx_chip.h"

#घोषणा MS_SP_CMND		0xFA
#घोषणा MS_FORMAT		0xA0
#घोषणा GET_MS_INFORMATION	0xB0

#घोषणा VENDOR_CMND		0xF0

#घोषणा READ_STATUS		0x09

#घोषणा READ_EEPROM		0x04
#घोषणा WRITE_EEPROM		0x05
#घोषणा READ_MEM		0x0D
#घोषणा WRITE_MEM		0x0E
#घोषणा GET_BUS_WIDTH		0x13
#घोषणा GET_SD_CSD		0x14
#घोषणा TOGGLE_GPIO		0x15
#घोषणा TRACE_MSG		0x18

#घोषणा SCSI_APP_CMD		0x10

#घोषणा PP_READ10		0x1A
#घोषणा PP_WRITE10		0x0A
#घोषणा READ_HOST_REG		0x1D
#घोषणा WRITE_HOST_REG		0x0D
#घोषणा SET_VAR			0x05
#घोषणा GET_VAR			0x15
#घोषणा DMA_READ		0x16
#घोषणा DMA_WRITE		0x06
#घोषणा GET_DEV_STATUS		0x10
#घोषणा SET_CHIP_MODE		0x27
#घोषणा SUIT_CMD		0xE0
#घोषणा WRITE_PHY		0x07
#घोषणा READ_PHY		0x17
#घोषणा WRITE_EEPROM2		0x03
#घोषणा READ_EEPROM2		0x13
#घोषणा ERASE_EEPROM2		0x23
#घोषणा WRITE_EFUSE		0x04
#घोषणा READ_EFUSE		0x14
#घोषणा WRITE_CFG		0x0E
#घोषणा READ_CFG		0x1E

#घोषणा SPI_VENDOR_COMMAND		0x1C

#घोषणा	SCSI_SPI_GETSTATUS		0x00
#घोषणा	SCSI_SPI_SETPARAMETER		0x01
#घोषणा	SCSI_SPI_READFALSHID		0x02
#घोषणा	SCSI_SPI_READFLASH		0x03
#घोषणा	SCSI_SPI_WRITEFLASH		0x04
#घोषणा	SCSI_SPI_WRITEFLASHSTATUS	0x05
#घोषणा	SCSI_SPI_ERASEFLASH		0x06

#घोषणा INIT_BATCHCMD		0x41
#घोषणा ADD_BATCHCMD		0x42
#घोषणा SEND_BATCHCMD		0x43
#घोषणा GET_BATCHRSP		0x44

#घोषणा CHIP_NORMALMODE		0x00
#घोषणा CHIP_DEBUGMODE		0x01

/* SD Pass Through Command Extension */
#घोषणा SD_PASS_THRU_MODE	0xD0
#घोषणा SD_EXECUTE_NO_DATA	0xD1
#घोषणा SD_EXECUTE_READ		0xD2
#घोषणा SD_EXECUTE_WRITE	0xD3
#घोषणा SD_GET_RSP		0xD4
#घोषणा SD_HW_RST		0xD6

#अगर_घोषित SUPPORT_MAGIC_GATE
#घोषणा CMD_MSPRO_MG_RKEY	0xA4   /* Report Key Command */
#घोषणा CMD_MSPRO_MG_SKEY	0xA3   /* Send Key Command */

/* CBWCB field: key class */
#घोषणा KC_MG_R_PRO		0xBE   /* MG-R PRO*/

/* CBWCB field: key क्रमmat */
#घोषणा KF_SET_LEAF_ID		0x31   /* Set Leaf ID */
#घोषणा KF_GET_LOC_EKB		0x32   /* Get Local EKB */
#घोषणा KF_CHG_HOST		0x33   /* Challenge (host) */
#घोषणा KF_RSP_CHG		0x34   /* Response and Challenge (device)  */
#घोषणा KF_RSP_HOST		0x35   /* Response (host) */
#घोषणा KF_GET_ICV		0x36   /* Get ICV */
#घोषणा KF_SET_ICV		0x37   /* SSet ICV */
#पूर्ण_अगर

/* Sense type */
#घोषणा	SENSE_TYPE_NO_SENSE				0
#घोषणा	SENSE_TYPE_MEDIA_CHANGE				1
#घोषणा	SENSE_TYPE_MEDIA_NOT_PRESENT			2
#घोषणा	SENSE_TYPE_MEDIA_LBA_OVER_RANGE			3
#घोषणा	SENSE_TYPE_MEDIA_LUN_NOT_SUPPORT		4
#घोषणा	SENSE_TYPE_MEDIA_WRITE_PROTECT			5
#घोषणा	SENSE_TYPE_MEDIA_INVALID_CMD_FIELD		6
#घोषणा	SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR		7
#घोषणा	SENSE_TYPE_MEDIA_WRITE_ERR			8
#घोषणा SENSE_TYPE_FORMAT_IN_PROGRESS			9
#घोषणा SENSE_TYPE_FORMAT_CMD_FAILED			10
#अगर_घोषित SUPPORT_MAGIC_GATE
#घोषणा SENSE_TYPE_MG_KEY_FAIL_NOT_ESTAB		0x0b
#घोषणा SENSE_TYPE_MG_KEY_FAIL_NOT_AUTHEN		0x0c
#घोषणा SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM		0x0d
#घोषणा SENSE_TYPE_MG_WRITE_ERR				0x0e
#पूर्ण_अगर
#अगर_घोषित SUPPORT_SD_LOCK
/* FOR Locked SD card*/
#घोषणा SENSE_TYPE_MEDIA_READ_FORBIDDEN			0x10
#पूर्ण_अगर

व्योम scsi_show_command(काष्ठा rtsx_chip *chip);
व्योम set_sense_type(काष्ठा rtsx_chip *chip, अचिन्हित पूर्णांक lun, पूर्णांक sense_type);
व्योम set_sense_data(काष्ठा rtsx_chip *chip, अचिन्हित पूर्णांक lun, u8 err_code,
		    u8 sense_key, u32 info, u8 asc, u8 ascq,
		    u8 sns_key_info0, u16 sns_key_info1);
पूर्णांक rtsx_scsi_handler(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);

#पूर्ण_अगर   /* __REALTEK_RTSX_SCSI_H */
