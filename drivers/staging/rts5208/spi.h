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

#अगर_अघोषित __REALTEK_RTSX_SPI_H
#घोषणा __REALTEK_RTSX_SPI_H

/* SPI operation error */
#घोषणा SPI_NO_ERR		0x00
#घोषणा SPI_HW_ERR		0x01
#घोषणा SPI_INVALID_COMMAND	0x02
#घोषणा SPI_READ_ERR		0x03
#घोषणा SPI_WRITE_ERR		0x04
#घोषणा SPI_ERASE_ERR		0x05
#घोषणा SPI_BUSY_ERR		0x06

/* Serial flash inकाष्ठाion */
#घोषणा SPI_READ		0x03
#घोषणा SPI_FAST_READ		0x0B
#घोषणा SPI_WREN		0x06
#घोषणा SPI_WRDI		0x04
#घोषणा SPI_RDSR		0x05

#घोषणा SF_PAGE_LEN		256

#घोषणा BYTE_PROGRAM		0
#घोषणा AAI_PROGRAM		1
#घोषणा PAGE_PROGRAM		2

#घोषणा PAGE_ERASE		0
#घोषणा CHIP_ERASE		1

पूर्णांक spi_erase_eeprom_chip(काष्ठा rtsx_chip *chip);
पूर्णांक spi_erase_eeprom_byte(काष्ठा rtsx_chip *chip, u16 addr);
पूर्णांक spi_पढ़ो_eeprom(काष्ठा rtsx_chip *chip, u16 addr, u8 *val);
पूर्णांक spi_ग_लिखो_eeprom(काष्ठा rtsx_chip *chip, u16 addr, u8 val);
पूर्णांक spi_get_status(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);
पूर्णांक spi_set_parameter(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);
पूर्णांक spi_पढ़ो_flash_id(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);
पूर्णांक spi_पढ़ो_flash(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);
पूर्णांक spi_ग_लिखो_flash(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);
पूर्णांक spi_erase_flash(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);
पूर्णांक spi_ग_लिखो_flash_status(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);

#पूर्ण_अगर  /* __REALTEK_RTSX_SPI_H */
