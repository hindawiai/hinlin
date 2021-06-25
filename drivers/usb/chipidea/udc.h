<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * udc.h - ChipIdea UDC काष्ठाures
 *
 * Copyright (C) 2008 Chipidea - MIPS Technologies, Inc. All rights reserved.
 *
 * Author: David Lopo
 */

#अगर_अघोषित __DRIVERS_USB_CHIPIDEA_UDC_H
#घोषणा __DRIVERS_USB_CHIPIDEA_UDC_H

#समावेश <linux/list.h>

#घोषणा CTRL_PAYLOAD_MAX   64
#घोषणा RX        0  /* similar to USB_सूची_OUT but can be used as an index */
#घोषणा TX        1  /* similar to USB_सूची_IN  but can be used as an index */

/* DMA layout of transfer descriptors */
काष्ठा ci_hw_td अणु
	/* 0 */
	__le32 next;
#घोषणा TD_TERMINATE          BIT(0)
#घोषणा TD_ADDR_MASK          (0xFFFFFFEUL << 5)
	/* 1 */
	__le32 token;
#घोषणा TD_STATUS             (0x00FFUL <<  0)
#घोषणा TD_STATUS_TR_ERR      BIT(3)
#घोषणा TD_STATUS_DT_ERR      BIT(5)
#घोषणा TD_STATUS_HALTED      BIT(6)
#घोषणा TD_STATUS_ACTIVE      BIT(7)
#घोषणा TD_MULTO              (0x0003UL << 10)
#घोषणा TD_IOC                BIT(15)
#घोषणा TD_TOTAL_BYTES        (0x7FFFUL << 16)
	/* 2 */
	__le32 page[5];
#घोषणा TD_CURR_OFFSET        (0x0FFFUL <<  0)
#घोषणा TD_FRAME_NUM          (0x07FFUL <<  0)
#घोषणा TD_RESERVED_MASK      (0x0FFFUL <<  0)
पूर्ण __attribute__ ((packed, aligned(4)));

/* DMA layout of queue heads */
काष्ठा ci_hw_qh अणु
	/* 0 */
	__le32 cap;
#घोषणा QH_IOS                BIT(15)
#घोषणा QH_MAX_PKT            (0x07FFUL << 16)
#घोषणा QH_ZLT                BIT(29)
#घोषणा QH_MULT               (0x0003UL << 30)
#घोषणा QH_ISO_MULT(x)		((x >> 11) & 0x03)
	/* 1 */
	__le32 curr;
	/* 2 - 8 */
	काष्ठा ci_hw_td		td;
	/* 9 */
	__le32 RESERVED;
	काष्ठा usb_ctrlrequest   setup;
पूर्ण __attribute__ ((packed, aligned(4)));

काष्ठा td_node अणु
	काष्ठा list_head	td;
	dma_addr_t		dma;
	काष्ठा ci_hw_td		*ptr;
	पूर्णांक			td_reमुख्यing_size;
पूर्ण;

/**
 * काष्ठा ci_hw_req - usb request representation
 * @req: request काष्ठाure क्रम gadget drivers
 * @queue: link to QH list
 * @tds: link to TD list
 */
काष्ठा ci_hw_req अणु
	काष्ठा usb_request	req;
	काष्ठा list_head	queue;
	काष्ठा list_head	tds;
पूर्ण;

#अगर_घोषित CONFIG_USB_CHIPIDEA_UDC

पूर्णांक ci_hdrc_gadget_init(काष्ठा ci_hdrc *ci);
व्योम ci_hdrc_gadget_destroy(काष्ठा ci_hdrc *ci);

#अन्यथा

अटल अंतरभूत पूर्णांक ci_hdrc_gadget_init(काष्ठा ci_hdrc *ci)
अणु
	वापस -ENXIO;
पूर्ण

अटल अंतरभूत व्योम ci_hdrc_gadget_destroy(काष्ठा ci_hdrc *ci)
अणु

पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* __DRIVERS_USB_CHIPIDEA_UDC_H */
