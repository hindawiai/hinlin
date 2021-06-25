<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * c67x00.h: Cypress C67X00 USB रेजिस्टर and field definitions
 *
 * Copyright (C) 2006-2008 Barco N.V.
 *    Derived from the Cypress cy7c67200/300 ezusb linux driver and
 *    based on multiple host controller drivers inside the linux kernel.
 */

#अगर_अघोषित _USB_C67X00_H
#घोषणा _USB_C67X00_H

#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/completion.h>
#समावेश <linux/mutex.h>

/* ---------------------------------------------------------------------
 * Cypress C67x00 रेजिस्टर definitions
 */

/* Hardware Revision Register */
#घोषणा HW_REV_REG		0xC004

/* General USB रेजिस्टरs */
/* ===================== */

/* USB Control Register */
#घोषणा USB_CTL_REG(x)		((x) ? 0xC0AA : 0xC08A)

#घोषणा LOW_SPEED_PORT(x)	((x) ? 0x0800 : 0x0400)
#घोषणा HOST_MODE		0x0200
#घोषणा PORT_RES_EN(x)		((x) ? 0x0100 : 0x0080)
#घोषणा SOF_EOP_EN(x)		((x) ? 0x0002 : 0x0001)

/* USB status रेजिस्टर - Notice it has dअगरferent content in hcd/udc mode */
#घोषणा USB_STAT_REG(x)		((x) ? 0xC0B0 : 0xC090)

#घोषणा EP0_IRQ_FLG		0x0001
#घोषणा EP1_IRQ_FLG		0x0002
#घोषणा EP2_IRQ_FLG		0x0004
#घोषणा EP3_IRQ_FLG		0x0008
#घोषणा EP4_IRQ_FLG		0x0010
#घोषणा EP5_IRQ_FLG		0x0020
#घोषणा EP6_IRQ_FLG		0x0040
#घोषणा EP7_IRQ_FLG		0x0080
#घोषणा RESET_IRQ_FLG		0x0100
#घोषणा SOF_EOP_IRQ_FLG		0x0200
#घोषणा ID_IRQ_FLG		0x4000
#घोषणा VBUS_IRQ_FLG		0x8000

/* USB Host only रेजिस्टरs */
/* ======================= */

/* Host n Control Register */
#घोषणा HOST_CTL_REG(x)		((x) ? 0xC0A0 : 0xC080)

#घोषणा PREAMBLE_EN		0x0080	/* Preamble enable */
#घोषणा SEQ_SEL			0x0040	/* Data Toggle Sequence Bit Select */
#घोषणा ISO_EN			0x0010	/* Isochronous enable  */
#घोषणा ARM_EN			0x0001	/* Arm operation */

/* Host n Interrupt Enable Register */
#घोषणा HOST_IRQ_EN_REG(x)	((x) ? 0xC0AC : 0xC08C)

#घोषणा SOF_EOP_IRQ_EN		0x0200	/* SOF/EOP Interrupt Enable  */
#घोषणा SOF_EOP_TMOUT_IRQ_EN	0x0800	/* SOF/EOP Timeout Interrupt Enable  */
#घोषणा ID_IRQ_EN		0x4000	/* ID पूर्णांकerrupt enable */
#घोषणा VBUS_IRQ_EN		0x8000	/* VBUS पूर्णांकerrupt enable */
#घोषणा DONE_IRQ_EN		0x0001	/* Done Interrupt Enable  */

/* USB status रेजिस्टर */
#घोषणा HOST_STAT_MASK		0x02FD
#घोषणा PORT_CONNECT_CHANGE(x)	((x) ? 0x0020 : 0x0010)
#घोषणा PORT_SE0_STATUS(x)	((x) ? 0x0008 : 0x0004)

/* Host Frame Register */
#घोषणा HOST_FRAME_REG(x)	((x) ? 0xC0B6 : 0xC096)

#घोषणा HOST_FRAME_MASK		0x07FF

/* USB Peripheral only रेजिस्टरs */
/* ============================= */

/* Device n Port Sel reg */
#घोषणा DEVICE_N_PORT_SEL(x)	((x) ? 0xC0A4 : 0xC084)

/* Device n Interrupt Enable Register */
#घोषणा DEVICE_N_IRQ_EN_REG(x)	((x) ? 0xC0AC : 0xC08C)

#घोषणा DEVICE_N_ENDPOINT_N_CTL_REG(dev, ep)	((dev)  		\
						 ? (0x0280 + (ep << 4)) \
						 : (0x0200 + (ep << 4)))
#घोषणा DEVICE_N_ENDPOINT_N_STAT_REG(dev, ep)	((dev)			\
						 ? (0x0286 + (ep << 4)) \
						 : (0x0206 + (ep << 4)))

#घोषणा DEVICE_N_ADDRESS(dev)	((dev) ? (0xC0AE) : (0xC08E))

/* HPI रेजिस्टरs */
/* ============= */

/* HPI Status रेजिस्टर */
#घोषणा SOFEOP_FLG(x)		(1 << ((x) ? 12 : 10))
#घोषणा SIEMSG_FLG(x)		(1 << (4 + (x)))
#घोषणा RESET_FLG(x)		((x) ? 0x0200 : 0x0002)
#घोषणा DONE_FLG(x)		(1 << (2 + (x)))
#घोषणा RESUME_FLG(x)		(1 << (6 + (x)))
#घोषणा MBX_OUT_FLG		0x0001	/* Message out available */
#घोषणा MBX_IN_FLG		0x0100
#घोषणा ID_FLG			0x4000
#घोषणा VBUS_FLG		0x8000

/* Interrupt routing रेजिस्टर */
#घोषणा HPI_IRQ_ROUTING_REG	0x0142

#घोषणा HPI_SWAP_ENABLE(x)	((x) ? 0x0100 : 0x0001)
#घोषणा RESET_TO_HPI_ENABLE(x)	((x) ? 0x0200 : 0x0002)
#घोषणा DONE_TO_HPI_ENABLE(x)	((x) ? 0x0008 : 0x0004)
#घोषणा RESUME_TO_HPI_ENABLE(x)	((x) ? 0x0080 : 0x0040)
#घोषणा SOFEOP_TO_HPI_EN(x)	((x) ? 0x2000 : 0x0800)
#घोषणा SOFEOP_TO_CPU_EN(x)	((x) ? 0x1000 : 0x0400)
#घोषणा ID_TO_HPI_ENABLE	0x4000
#घोषणा VBUS_TO_HPI_ENABLE	0x8000

/* SIE msg रेजिस्टरs */
#घोषणा SIEMSG_REG(x)		((x) ? 0x0148 : 0x0144)

#घोषणा HUSB_TDListDone		0x1000

#घोषणा SUSB_EP0_MSG		0x0001
#घोषणा SUSB_EP1_MSG		0x0002
#घोषणा SUSB_EP2_MSG		0x0004
#घोषणा SUSB_EP3_MSG		0x0008
#घोषणा SUSB_EP4_MSG		0x0010
#घोषणा SUSB_EP5_MSG		0x0020
#घोषणा SUSB_EP6_MSG		0x0040
#घोषणा SUSB_EP7_MSG		0x0080
#घोषणा SUSB_RST_MSG		0x0100
#घोषणा SUSB_SOF_MSG		0x0200
#घोषणा SUSB_CFG_MSG		0x0400
#घोषणा SUSB_SUS_MSG		0x0800
#घोषणा SUSB_ID_MSG	       	0x4000
#घोषणा SUSB_VBUS_MSG		0x8000

/* BIOS पूर्णांकerrupt routines */

#घोषणा SUSBx_RECEIVE_INT(x)	((x) ? 97 : 81)
#घोषणा SUSBx_SEND_INT(x)	((x) ? 96 : 80)

#घोषणा SUSBx_DEV_DESC_VEC(x)	((x) ? 0x00D4 : 0x00B4)
#घोषणा SUSBx_CONF_DESC_VEC(x)	((x) ? 0x00D6 : 0x00B6)
#घोषणा SUSBx_STRING_DESC_VEC(x) ((x) ? 0x00D8 : 0x00B8)

#घोषणा CY_HCD_BUF_ADDR		0x500	/* Base address क्रम host */
#घोषणा SIE_TD_SIZE		0x200	/* size of the td list */
#घोषणा SIE_TD_BUF_SIZE		0x400	/* size of the data buffer */

#घोषणा SIE_TD_OFFSET(host)	((host) ? (SIE_TD_SIZE+SIE_TD_BUF_SIZE) : 0)
#घोषणा SIE_BUF_OFFSET(host)	(SIE_TD_OFFSET(host) + SIE_TD_SIZE)

/* Base address of HCD + 2 x TD_SIZE + 2 x TD_BUF_SIZE */
#घोषणा CY_UDC_REQ_HEADER_BASE	0x1100
/* 8- byte request headers क्रम IN/OUT transfers */
#घोषणा CY_UDC_REQ_HEADER_SIZE	8

#घोषणा CY_UDC_REQ_HEADER_ADDR(ep_num)	(CY_UDC_REQ_HEADER_BASE + \
					 ((ep_num) * CY_UDC_REQ_HEADER_SIZE))
#घोषणा CY_UDC_DESC_BASE_ADDRESS	(CY_UDC_REQ_HEADER_ADDR(8))

#घोषणा CY_UDC_BIOS_REPLACE_BASE	0x1800
#घोषणा CY_UDC_REQ_BUFFER_BASE		0x2000
#घोषणा CY_UDC_REQ_BUFFER_SIZE		0x0400
#घोषणा CY_UDC_REQ_BUFFER_ADDR(ep_num)	(CY_UDC_REQ_BUFFER_BASE + \
					 ((ep_num) * CY_UDC_REQ_BUFFER_SIZE))

/* ---------------------------------------------------------------------
 * Driver data काष्ठाures
 */

काष्ठा c67x00_device;

/**
 * काष्ठा c67x00_sie - Common data associated with a SIE
 * @lock: lock to protect this काष्ठा and the associated chip रेजिस्टरs
 * @निजी_data: subdriver dependent data
 * @irq: subdriver dependent irq handler, set शून्य when not used
 * @dev: link to common driver काष्ठाure
 * @sie_num: SIE number on chip, starting from 0
 * @mode: SIE mode (host/peripheral/otg/not used)
 */
काष्ठा c67x00_sie अणु
	/* Entries to be used by the subdrivers */
	spinlock_t lock;	/* protect this काष्ठाure */
	व्योम *निजी_data;
	व्योम (*irq) (काष्ठा c67x00_sie *sie, u16 पूर्णांक_status, u16 msg);

	/* Read only: */
	काष्ठा c67x00_device *dev;
	पूर्णांक sie_num;
	पूर्णांक mode;
पूर्ण;

#घोषणा sie_dev(s)	(&(s)->dev->pdev->dev)

/**
 * काष्ठा c67x00_lcp
 */
काष्ठा c67x00_lcp अणु
	/* Internal use only */
	काष्ठा mutex mutex;
	काष्ठा completion msg_received;
	u16 last_msg;
पूर्ण;

/*
 * काष्ठा c67x00_hpi
 */
काष्ठा c67x00_hpi अणु
	व्योम __iomem *base;
	पूर्णांक regstep;
	spinlock_t lock;
	काष्ठा c67x00_lcp lcp;
पूर्ण;

#घोषणा C67X00_SIES	2
#घोषणा C67X00_PORTS	2

/**
 * काष्ठा c67x00_device - Common data associated with a c67x00 instance
 * @hpi: hpi addresses
 * @sie: array of sie's on this chip
 * @pdev: platक्रमm device of instance
 * @pdata: configuration provided by the platक्रमm
 */
काष्ठा c67x00_device अणु
	काष्ठा c67x00_hpi hpi;
	काष्ठा c67x00_sie sie[C67X00_SIES];
	काष्ठा platक्रमm_device *pdev;
	काष्ठा c67x00_platक्रमm_data *pdata;
पूर्ण;

/* ---------------------------------------------------------------------
 * Low level पूर्णांकerface functions
 */

/* Host Port Interface (HPI) functions */
u16 c67x00_ll_hpi_status(काष्ठा c67x00_device *dev);
व्योम c67x00_ll_hpi_reg_init(काष्ठा c67x00_device *dev);
व्योम c67x00_ll_hpi_enable_sofeop(काष्ठा c67x00_sie *sie);
व्योम c67x00_ll_hpi_disable_sofeop(काष्ठा c67x00_sie *sie);

/* General functions */
u16 c67x00_ll_fetch_siemsg(काष्ठा c67x00_device *dev, पूर्णांक sie_num);
u16 c67x00_ll_get_usb_ctl(काष्ठा c67x00_sie *sie);
व्योम c67x00_ll_usb_clear_status(काष्ठा c67x00_sie *sie, u16 bits);
u16 c67x00_ll_usb_get_status(काष्ठा c67x00_sie *sie);
व्योम c67x00_ll_ग_लिखो_mem_le16(काष्ठा c67x00_device *dev, u16 addr,
			      व्योम *data, पूर्णांक len);
व्योम c67x00_ll_पढ़ो_mem_le16(काष्ठा c67x00_device *dev, u16 addr,
			     व्योम *data, पूर्णांक len);

/* Host specअगरic functions */
व्योम c67x00_ll_set_husb_eot(काष्ठा c67x00_device *dev, u16 value);
व्योम c67x00_ll_husb_reset(काष्ठा c67x00_sie *sie, पूर्णांक port);
व्योम c67x00_ll_husb_set_current_td(काष्ठा c67x00_sie *sie, u16 addr);
u16 c67x00_ll_husb_get_current_td(काष्ठा c67x00_sie *sie);
u16 c67x00_ll_husb_get_frame(काष्ठा c67x00_sie *sie);
व्योम c67x00_ll_husb_init_host_port(काष्ठा c67x00_sie *sie);
व्योम c67x00_ll_husb_reset_port(काष्ठा c67x00_sie *sie, पूर्णांक port);

/* Called by c67x00_irq to handle lcp पूर्णांकerrupts */
व्योम c67x00_ll_irq(काष्ठा c67x00_device *dev, u16 पूर्णांक_status);

/* Setup and tearकरोwn */
व्योम c67x00_ll_init(काष्ठा c67x00_device *dev);
व्योम c67x00_ll_release(काष्ठा c67x00_device *dev);
पूर्णांक c67x00_ll_reset(काष्ठा c67x00_device *dev);

#पूर्ण_अगर				/* _USB_C67X00_H */
