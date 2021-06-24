<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  linux/drivers/net/wireless/libertas/अगर_sdपन.स
 *
 *  Copyright 2007 Pierre Ossman
 */

#अगर_अघोषित _LBS_IF_SDIO_H
#घोषणा _LBS_IF_SDIO_H

#घोषणा IF_SDIO_IOPORT		0x00

#घोषणा IF_SDIO_H_INT_MASK	0x04
#घोषणा   IF_SDIO_H_INT_OFLOW	0x08
#घोषणा   IF_SDIO_H_INT_UFLOW	0x04
#घोषणा   IF_SDIO_H_INT_DNLD	0x02
#घोषणा   IF_SDIO_H_INT_UPLD	0x01

#घोषणा IF_SDIO_H_INT_STATUS	0x05
#घोषणा IF_SDIO_H_INT_RSR	0x06
#घोषणा IF_SDIO_H_INT_STATUS2	0x07

#घोषणा IF_SDIO_RD_BASE		0x10

#घोषणा IF_SDIO_STATUS		0x20
#घोषणा   IF_SDIO_IO_RDY	0x08
#घोषणा   IF_SDIO_CIS_RDY	0x04
#घोषणा   IF_SDIO_UL_RDY	0x02
#घोषणा   IF_SDIO_DL_RDY	0x01

#घोषणा IF_SDIO_C_INT_MASK	0x24
#घोषणा IF_SDIO_C_INT_STATUS	0x28
#घोषणा IF_SDIO_C_INT_RSR	0x2C

#घोषणा IF_SDIO_SCRATCH		0x34
#घोषणा IF_SDIO_SCRATCH_OLD	0x80fe
#घोषणा IF_SDIO_FW_STATUS	0x40
#घोषणा   IF_SDIO_FIRMWARE_OK	0xfedc

#घोषणा IF_SDIO_RX_LEN		0x42
#घोषणा IF_SDIO_RX_UNIT		0x43

#घोषणा IF_SDIO_EVENT           0x80fc

#घोषणा IF_SDIO_BLOCK_SIZE	256
#घोषणा CONFIGURATION_REG               0x03
#घोषणा HOST_POWER_UP                   (0x1U << 1)
#पूर्ण_अगर
