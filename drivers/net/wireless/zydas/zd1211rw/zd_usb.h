<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* ZD1211 USB-WLAN driver क्रम Linux
 *
 * Copyright (C) 2005-2007 Ulrich Kunitz <kune@deine-taler.de>
 * Copyright (C) 2006-2007 Daniel Drake <dsd@gentoo.org>
 */

#अगर_अघोषित _ZD_USB_H
#घोषणा _ZD_USB_H

#समावेश <linux/completion.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/usb.h>

#समावेश "zd_def.h"

#घोषणा ZD_USB_TX_HIGH  5
#घोषणा ZD_USB_TX_LOW   2

#घोषणा ZD_TX_TIMEOUT		(HZ * 5)
#घोषणा ZD_TX_WATCHDOG_INTERVAL	round_jअगरfies_relative(HZ)
#घोषणा ZD_RX_IDLE_INTERVAL	round_jअगरfies_relative(30 * HZ)

क्रमागत devicetype अणु
	DEVICE_ZD1211  = 0,
	DEVICE_ZD1211B = 1,
	DEVICE_INSTALLER = 2,
पूर्ण;

क्रमागत endpoपूर्णांकs अणु
	EP_CTRL	    = 0,
	EP_DATA_OUT = 1,
	EP_DATA_IN  = 2,
	EP_INT_IN   = 3,
	EP_REGS_OUT = 4,
पूर्ण;

क्रमागत अणु
	USB_MAX_TRANSFER_SIZE		= 4096, /* bytes */
	/* FIXME: The original driver uses this value. We have to check,
	 * whether the MAX_TRANSFER_SIZE is sufficient and this needs only be
	 * used अगर one combined frame is split over two USB transactions.
	 */
	USB_MAX_RX_SIZE			= 4800, /* bytes */
	USB_MAX_IOWRITE16_COUNT		= 15,
	USB_MAX_IOWRITE32_COUNT		= USB_MAX_IOWRITE16_COUNT/2,
	USB_MAX_IOREAD16_COUNT		= 15,
	USB_MAX_IOREAD32_COUNT		= USB_MAX_IOREAD16_COUNT/2,
	USB_MIN_RFWRITE_BIT_COUNT	= 16,
	USB_MAX_RFWRITE_BIT_COUNT	= 28,
	USB_MAX_EP_INT_BUFFER		= 64,
	USB_ZD1211B_BCD_DEVICE		= 0x4810,
पूर्ण;

क्रमागत control_requests अणु
	USB_REQ_WRITE_REGS		= 0x21,
	USB_REQ_READ_REGS		= 0x22,
	USB_REQ_WRITE_RF		= 0x23,
	USB_REQ_PROG_FLASH		= 0x24,
	USB_REQ_EEPROM_START		= 0x0128, /* ? request is a byte */
	USB_REQ_EEPROM_MID		= 0x28,
	USB_REQ_EEPROM_END		= 0x0228, /* ? request is a byte */
	USB_REQ_FIRMWARE_DOWNLOAD	= 0x30,
	USB_REQ_FIRMWARE_CONFIRM	= 0x31,
	USB_REQ_FIRMWARE_READ_DATA	= 0x32,
पूर्ण;

काष्ठा usb_req_पढ़ो_regs अणु
	__le16 id;
	__le16 addr[];
पूर्ण __packed;

काष्ठा reg_data अणु
	__le16 addr;
	__le16 value;
पूर्ण __packed;

काष्ठा usb_req_ग_लिखो_regs अणु
	__le16 id;
	काष्ठा reg_data reg_ग_लिखोs[];
पूर्ण __packed;

क्रमागत अणु
	RF_IF_LE = 0x02,
	RF_CLK   = 0x04,
	RF_DATA	 = 0x08,
पूर्ण;

काष्ठा usb_req_rख_डालो अणु
	__le16 id;
	__le16 value;
	/* 1: 3683a */
	/* 2: other (शेष) */
	__le16 bits;
	/* RF2595: 24 */
	__le16 bit_values[];
	/* (ZD_CR203 & ~(RF_IF_LE | RF_CLK | RF_DATA)) | (bit ? RF_DATA : 0) */
पूर्ण __packed;

/* USB पूर्णांकerrupt */

क्रमागत usb_पूर्णांक_id अणु
	USB_INT_TYPE			= 0x01,
	USB_INT_ID_REGS			= 0x90,
	USB_INT_ID_RETRY_FAILED		= 0xa0,
पूर्ण;

क्रमागत usb_पूर्णांक_flags अणु
	USB_INT_READ_REGS_EN		= 0x01,
पूर्ण;

काष्ठा usb_पूर्णांक_header अणु
	u8 type;	/* must always be 1 */
	u8 id;
पूर्ण __packed;

काष्ठा usb_पूर्णांक_regs अणु
	काष्ठा usb_पूर्णांक_header hdr;
	काष्ठा reg_data regs[];
पूर्ण __packed;

काष्ठा usb_पूर्णांक_retry_fail अणु
	काष्ठा usb_पूर्णांक_header hdr;
	u8 new_rate;
	u8 _dummy;
	u8 addr[ETH_ALEN];
	u8 ibss_wakeup_dest;
पूर्ण __packed;

काष्ठा पढ़ो_regs_पूर्णांक अणु
	काष्ठा completion completion;
	काष्ठा usb_req_पढ़ो_regs *req;
	अचिन्हित पूर्णांक req_count;
	/* Stores the USB पूर्णांक काष्ठाure and contains the USB address of the
	 * first requested रेजिस्टर beक्रमe request.
	 */
	u8 buffer[USB_MAX_EP_INT_BUFFER];
	पूर्णांक length;
	__le16 cr_पूर्णांक_addr;
पूर्ण;

काष्ठा zd_ioreq16 अणु
	zd_addr_t addr;
	u16 value;
पूर्ण;

काष्ठा zd_ioreq32 अणु
	zd_addr_t addr;
	u32 value;
पूर्ण;

काष्ठा zd_usb_पूर्णांकerrupt अणु
	काष्ठा पढ़ो_regs_पूर्णांक पढ़ो_regs;
	spinlock_t lock;
	काष्ठा urb *urb;
	व्योम *buffer;
	dma_addr_t buffer_dma;
	पूर्णांक पूर्णांकerval;
	atomic_t पढ़ो_regs_enabled;
	u8 पढ़ो_regs_पूर्णांक_overridden:1;
पूर्ण;

अटल अंतरभूत काष्ठा usb_पूर्णांक_regs *get_पढ़ो_regs(काष्ठा zd_usb_पूर्णांकerrupt *पूर्णांकr)
अणु
	वापस (काष्ठा usb_पूर्णांक_regs *)पूर्णांकr->पढ़ो_regs.buffer;
पूर्ण

#घोषणा RX_URBS_COUNT 5

काष्ठा zd_usb_rx अणु
	spinlock_t lock;
	काष्ठा mutex setup_mutex;
	काष्ठा delayed_work idle_work;
	काष्ठा tasklet_काष्ठा reset_समयr_tasklet;
	u8 fragment[2 * USB_MAX_RX_SIZE];
	अचिन्हित पूर्णांक fragment_length;
	अचिन्हित पूर्णांक usb_packet_size;
	काष्ठा urb **urbs;
	पूर्णांक urbs_count;
पूर्ण;

/**
 * काष्ठा zd_usb_tx - काष्ठाure used क्रम transmitting frames
 * @enabled: atomic enabled flag, indicates whether tx is enabled
 * @lock: lock क्रम transmission
 * @submitted: anchor क्रम URBs sent to device
 * @submitted_urbs: atomic पूर्णांकeger that counts the URBs having sent to the
 *	device, which haven't been completed
 * @stopped: indicates whether higher level tx queues are stopped
 */
काष्ठा zd_usb_tx अणु
	atomic_t enabled;
	spinlock_t lock;
	काष्ठा delayed_work watchकरोg_work;
	काष्ठा sk_buff_head submitted_skbs;
	काष्ठा usb_anchor submitted;
	पूर्णांक submitted_urbs;
	u8 stopped:1, watchकरोg_enabled:1;
पूर्ण;

/* Contains the usb parts. The काष्ठाure करोesn't require a lock because पूर्णांकf
 * will not be changed after initialization.
 */
काष्ठा zd_usb अणु
	काष्ठा zd_usb_पूर्णांकerrupt पूर्णांकr;
	काष्ठा zd_usb_rx rx;
	काष्ठा zd_usb_tx tx;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_anchor submitted_cmds;
	काष्ठा urb *urb_async_रुकोing;
	पूर्णांक cmd_error;
	u8 req_buf[64]; /* zd_usb_ioग_लिखो16v needs 62 bytes */
	u8 is_zd1211b:1, initialized:1, was_running:1, in_async:1;
पूर्ण;

#घोषणा zd_usb_dev(usb) (&usb->पूर्णांकf->dev)

अटल अंतरभूत काष्ठा usb_device *zd_usb_to_usbdev(काष्ठा zd_usb *usb)
अणु
	वापस पूर्णांकerface_to_usbdev(usb->पूर्णांकf);
पूर्ण

अटल अंतरभूत काष्ठा ieee80211_hw *zd_पूर्णांकf_to_hw(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस usb_get_पूर्णांकfdata(पूर्णांकf);
पूर्ण

अटल अंतरभूत काष्ठा ieee80211_hw *zd_usb_to_hw(काष्ठा zd_usb *usb)
अणु
	वापस zd_पूर्णांकf_to_hw(usb->पूर्णांकf);
पूर्ण

व्योम zd_usb_init(काष्ठा zd_usb *usb, काष्ठा ieee80211_hw *hw,
	         काष्ठा usb_पूर्णांकerface *पूर्णांकf);
पूर्णांक zd_usb_init_hw(काष्ठा zd_usb *usb);
व्योम zd_usb_clear(काष्ठा zd_usb *usb);

पूर्णांक zd_usb_scnprपूर्णांक_id(काष्ठा zd_usb *usb, अक्षर *buffer, माप_प्रकार size);

व्योम zd_tx_watchकरोg_enable(काष्ठा zd_usb *usb);
व्योम zd_tx_watchकरोg_disable(काष्ठा zd_usb *usb);

पूर्णांक zd_usb_enable_पूर्णांक(काष्ठा zd_usb *usb);
व्योम zd_usb_disable_पूर्णांक(काष्ठा zd_usb *usb);

पूर्णांक zd_usb_enable_rx(काष्ठा zd_usb *usb);
व्योम zd_usb_disable_rx(काष्ठा zd_usb *usb);

व्योम zd_usb_reset_rx_idle_समयr(काष्ठा zd_usb *usb);

व्योम zd_usb_enable_tx(काष्ठा zd_usb *usb);
व्योम zd_usb_disable_tx(काष्ठा zd_usb *usb);

पूर्णांक zd_usb_tx(काष्ठा zd_usb *usb, काष्ठा sk_buff *skb);

पूर्णांक zd_usb_ioपढ़ो16v(काष्ठा zd_usb *usb, u16 *values,
	         स्थिर zd_addr_t *addresses, अचिन्हित पूर्णांक count);

अटल अंतरभूत पूर्णांक zd_usb_ioपढ़ो16(काष्ठा zd_usb *usb, u16 *value,
	                      स्थिर zd_addr_t addr)
अणु
	वापस zd_usb_ioपढ़ो16v(usb, value, &addr, 1);
पूर्ण

व्योम zd_usb_ioग_लिखो16v_async_start(काष्ठा zd_usb *usb);
पूर्णांक zd_usb_ioग_लिखो16v_async_end(काष्ठा zd_usb *usb, अचिन्हित पूर्णांक समयout);
पूर्णांक zd_usb_ioग_लिखो16v_async(काष्ठा zd_usb *usb, स्थिर काष्ठा zd_ioreq16 *ioreqs,
			    अचिन्हित पूर्णांक count);
पूर्णांक zd_usb_ioग_लिखो16v(काष्ठा zd_usb *usb, स्थिर काष्ठा zd_ioreq16 *ioreqs,
	              अचिन्हित पूर्णांक count);

पूर्णांक zd_usb_rख_डालो(काष्ठा zd_usb *usb, u32 value, u8 bits);

पूर्णांक zd_usb_पढ़ो_fw(काष्ठा zd_usb *usb, zd_addr_t addr, u8 *data, u16 len);

बाह्य काष्ठा workqueue_काष्ठा *zd_workqueue;

#पूर्ण_अगर /* _ZD_USB_H */
