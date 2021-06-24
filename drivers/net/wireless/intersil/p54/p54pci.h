<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित P54PCI_H
#घोषणा P54PCI_H
#समावेश <linux/पूर्णांकerrupt.h>

/*
 * Defines क्रम PCI based mac80211 Prism54 driver
 *
 * Copyright (c) 2006, Michael Wu <flamingice@sourmilk.net>
 *
 * Based on the islsm (sofपंचांगac prism54) driver, which is:
 * Copyright 2004-2006 Jean-Baptiste Note <jbnote@gmail.com>, et al.
 */

/* Device Interrupt रेजिस्टर bits */
#घोषणा ISL38XX_DEV_INT_RESET                   0x0001
#घोषणा ISL38XX_DEV_INT_UPDATE                  0x0002
#घोषणा ISL38XX_DEV_INT_WAKEUP                  0x0008
#घोषणा ISL38XX_DEV_INT_SLEEP                   0x0010
#घोषणा ISL38XX_DEV_INT_ABORT                   0x0020
/* these two only used in USB */
#घोषणा ISL38XX_DEV_INT_DATA                    0x0040
#घोषणा ISL38XX_DEV_INT_MGMT                    0x0080

#घोषणा ISL38XX_DEV_INT_PCIUART_CTS             0x4000
#घोषणा ISL38XX_DEV_INT_PCIUART_DR              0x8000

/* Interrupt Identअगरication/Acknowledge/Enable रेजिस्टर bits */
#घोषणा ISL38XX_INT_IDENT_UPDATE		0x0002
#घोषणा ISL38XX_INT_IDENT_INIT			0x0004
#घोषणा ISL38XX_INT_IDENT_WAKEUP		0x0008
#घोषणा ISL38XX_INT_IDENT_SLEEP			0x0010
#घोषणा ISL38XX_INT_IDENT_PCIUART_CTS		0x4000
#घोषणा ISL38XX_INT_IDENT_PCIUART_DR		0x8000

/* Control/Status रेजिस्टर bits */
#घोषणा ISL38XX_CTRL_STAT_SLEEPMODE		0x00000200
#घोषणा ISL38XX_CTRL_STAT_CLKRUN		0x00800000
#घोषणा ISL38XX_CTRL_STAT_RESET			0x10000000
#घोषणा ISL38XX_CTRL_STAT_RAMBOOT		0x20000000
#घोषणा ISL38XX_CTRL_STAT_STARTHALTED		0x40000000
#घोषणा ISL38XX_CTRL_STAT_HOST_OVERRIDE		0x80000000

काष्ठा p54p_csr अणु
	__le32 dev_पूर्णांक;
	u8 unused_1[12];
	__le32 पूर्णांक_ident;
	__le32 पूर्णांक_ack;
	__le32 पूर्णांक_enable;
	u8 unused_2[4];
	जोड़ अणु
		__le32 ring_control_base;
		__le32 gen_purp_com[2];
	पूर्ण;
	u8 unused_3[8];
	__le32 direct_mem_base;
	u8 unused_4[44];
	__le32 dma_addr;
	__le32 dma_len;
	__le32 dma_ctrl;
	u8 unused_5[12];
	__le32 ctrl_stat;
	u8 unused_6[1924];
	u8 cardbus_cis[0x800];
	u8 direct_mem_win[0x1000];
पूर्ण __packed;

/* usb backend only needs the रेजिस्टर defines above */
#अगर_अघोषित P54USB_H
काष्ठा p54p_desc अणु
	__le32 host_addr;
	__le32 device_addr;
	__le16 len;
	__le16 flags;
पूर्ण __packed;

काष्ठा p54p_ring_control अणु
	__le32 host_idx[4];
	__le32 device_idx[4];
	काष्ठा p54p_desc rx_data[8];
	काष्ठा p54p_desc tx_data[32];
	काष्ठा p54p_desc rx_mgmt[4];
	काष्ठा p54p_desc tx_mgmt[4];
पूर्ण __packed;

#घोषणा P54P_READ(r) (__क्रमce __le32)__raw_पढ़ोl(&priv->map->r)
#घोषणा P54P_WRITE(r, val) __raw_ग_लिखोl((__क्रमce u32)(__le32)(val), &priv->map->r)

काष्ठा p54p_priv अणु
	काष्ठा p54_common common;
	काष्ठा pci_dev *pdev;
	काष्ठा p54p_csr __iomem *map;
	काष्ठा tasklet_काष्ठा tasklet;
	स्थिर काष्ठा firmware *firmware;
	spinlock_t lock;
	काष्ठा p54p_ring_control *ring_control;
	dma_addr_t ring_control_dma;
	u32 rx_idx_data, tx_idx_data;
	u32 rx_idx_mgmt, tx_idx_mgmt;
	काष्ठा sk_buff *rx_buf_data[8];
	काष्ठा sk_buff *rx_buf_mgmt[4];
	काष्ठा sk_buff *tx_buf_data[32];
	काष्ठा sk_buff *tx_buf_mgmt[4];
	काष्ठा completion boot_comp;
	काष्ठा completion fw_loaded;
पूर्ण;

#पूर्ण_अगर /* P54USB_H */
#पूर्ण_अगर /* P54PCI_H */
