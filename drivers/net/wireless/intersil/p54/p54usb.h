<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित P54USB_H
#घोषणा P54USB_H

/*
 * Defines क्रम USB based mac80211 Prism54 driver
 *
 * Copyright (c) 2006, Michael Wu <flamingice@sourmilk.net>
 *
 * Based on the islsm (sofपंचांगac prism54) driver, which is:
 * Copyright 2004-2006 Jean-Baptiste Note <jbnote@gmail.com>, et al.
 */

/* क्रम isl3886 रेजिस्टर definitions used on ver 1 devices */
#समावेश "p54pci.h"
#समावेश <linux/usb/net2280.h>

/* pci */
#घोषणा NET2280_BASE		0x10000000
#घोषणा NET2280_BASE2		0x20000000

/* gpio */
#घोषणा P54U_BRG_POWER_UP	(1 << GPIO0_DATA)
#घोषणा P54U_BRG_POWER_DOWN	(1 << GPIO1_DATA)

/* devinit */
#घोषणा NET2280_CLK_4Mhz	(15 << LOCAL_CLOCK_FREQUENCY)
#घोषणा NET2280_CLK_30Mhz	(2 << LOCAL_CLOCK_FREQUENCY)
#घोषणा NET2280_CLK_60Mhz	(1 << LOCAL_CLOCK_FREQUENCY)
#घोषणा NET2280_CLK_STOP	(0 << LOCAL_CLOCK_FREQUENCY)
#घोषणा NET2280_PCI_ENABLE	(1 << PCI_ENABLE)
#घोषणा NET2280_PCI_SOFT_RESET	(1 << PCI_SOFT_RESET)

/* endpoपूर्णांकs */
#घोषणा NET2280_CLEAR_NAK_OUT_PACKETS_MODE	(1 << CLEAR_NAK_OUT_PACKETS_MODE)
#घोषणा NET2280_FIFO_FLUSH			(1 << FIFO_FLUSH)

/* irq */
#घोषणा NET2280_USB_INTERRUPT_ENABLE		(1 << USB_INTERRUPT_ENABLE)
#घोषणा NET2280_PCI_INTA_INTERRUPT		(1 << PCI_INTA_INTERRUPT)
#घोषणा NET2280_PCI_INTA_INTERRUPT_ENABLE	(1 << PCI_INTA_INTERRUPT_ENABLE)

/* रेजिस्टरs */
#घोषणा NET2280_DEVINIT		0x00
#घोषणा NET2280_USBIRQENB1	0x24
#घोषणा NET2280_IRQSTAT1	0x2c
#घोषणा NET2280_FIFOCTL         0x38
#घोषणा NET2280_GPIOCTL		0x50
#घोषणा NET2280_RELNUM		0x88
#घोषणा NET2280_EPA_RSP		0x324
#घोषणा NET2280_EPA_STAT	0x32c
#घोषणा NET2280_EPB_STAT	0x34c
#घोषणा NET2280_EPC_RSP		0x364
#घोषणा NET2280_EPC_STAT	0x36c
#घोषणा NET2280_EPD_STAT	0x38c

#घोषणा NET2280_EPA_CFG     0x320
#घोषणा NET2280_EPB_CFG     0x340
#घोषणा NET2280_EPC_CFG     0x360
#घोषणा NET2280_EPD_CFG     0x380
#घोषणा NET2280_EPE_CFG     0x3A0
#घोषणा NET2280_EPF_CFG     0x3C0
#घोषणा P54U_DEV_BASE 0x40000000

काष्ठा net2280_tx_hdr अणु
	__le32 device_addr;
	__le16 len;
	__le16 follower;	/* ? */
	u8 padding[8];
पूर्ण __packed;

काष्ठा lm87_tx_hdr अणु
	__le32 device_addr;
	__le32 chksum;
पूर्ण __packed;

/* Some flags क्रम the isl hardware रेजिस्टरs controlling DMA inside the
 * chip */
#घोषणा ISL38XX_DMA_STATUS_DONE			0x00000001
#घोषणा ISL38XX_DMA_STATUS_READY		0x00000002
#घोषणा NET2280_EPA_FIFO_PCI_ADDR		0x20000000
#घोषणा ISL38XX_DMA_MASTER_CONTROL_TRIGGER	0x00000004

क्रमागत net2280_op_type अणु
	NET2280_BRG_U32		= 0x001F,
	NET2280_BRG_CFG_U32	= 0x000F,
	NET2280_BRG_CFG_U16	= 0x0003,
	NET2280_DEV_U32		= 0x080F,
	NET2280_DEV_CFG_U32	= 0x088F,
	NET2280_DEV_CFG_U16	= 0x0883
पूर्ण;

काष्ठा net2280_reg_ग_लिखो अणु
	__le16 port;
	__le32 addr;
	__le32 val;
पूर्ण __packed;

काष्ठा net2280_reg_पढ़ो अणु
	__le16 port;
	__le32 addr;
पूर्ण __packed;

#घोषणा P54U_FW_BLOCK 2048

#घोषणा X2_SIGNATURE "x2  "
#घोषणा X2_SIGNATURE_SIZE 4

काष्ठा x2_header अणु
	u8 signature[X2_SIGNATURE_SIZE];
	__le32 fw_load_addr;
	__le32 fw_length;
	__le32 crc;
पूर्ण __packed;

/* pipes 3 and 4 are not used by the driver */
#घोषणा P54U_PIPE_NUMBER 9

क्रमागत p54u_pipe_addr अणु
        P54U_PIPE_DATA = 0x01,
        P54U_PIPE_MGMT = 0x02,
        P54U_PIPE_3 = 0x03,
        P54U_PIPE_4 = 0x04,
        P54U_PIPE_BRG = 0x0d,
        P54U_PIPE_DEV = 0x0e,
        P54U_PIPE_INT = 0x0f
पूर्ण;

काष्ठा p54u_rx_info अणु
	काष्ठा urb *urb;
	काष्ठा ieee80211_hw *dev;
पूर्ण;

क्रमागत p54u_hw_type अणु
	P54U_INVALID_HW,
	P54U_NET2280,
	P54U_3887,

	/* keep last */
	__NUM_P54U_HWTYPES,
पूर्ण;

काष्ठा p54u_priv अणु
	काष्ठा p54_common common;
	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	पूर्णांक (*upload_fw)(काष्ठा ieee80211_hw *dev);

	क्रमागत p54u_hw_type hw_type;
	spinlock_t lock;
	काष्ठा sk_buff_head rx_queue;
	काष्ठा usb_anchor submitted;
	स्थिर काष्ठा firmware *fw;

	/* asynchronous firmware callback */
	काष्ठा completion fw_रुको_load;
पूर्ण;

#पूर्ण_अगर /* P54USB_H */
