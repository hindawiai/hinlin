<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 */

#अगर_अघोषित __MT7601U_USB_H
#घोषणा __MT7601U_USB_H

#समावेश "mt7601u.h"

#घोषणा MT7601U_FIRMWARE	"mt7601u.bin"

#घोषणा MT_VEND_REQ_MAX_RETRY	10
#घोषणा MT_VEND_REQ_TOUT_MS	300

#घोषणा MT_VEND_DEV_MODE_RESET	1

#घोषणा MT_VEND_BUF		माप(__le32)

क्रमागत mt_venकरोr_req अणु
	MT_VEND_DEV_MODE = 1,
	MT_VEND_WRITE = 2,
	MT_VEND_MULTI_READ = 7,
	MT_VEND_WRITE_FCE = 0x42,
पूर्ण;

क्रमागत mt_usb_ep_in अणु
	MT_EP_IN_PKT_RX,
	MT_EP_IN_CMD_RESP,
	__MT_EP_IN_MAX,
पूर्ण;

क्रमागत mt_usb_ep_out अणु
	MT_EP_OUT_INBAND_CMD,
	MT_EP_OUT_AC_BK,
	MT_EP_OUT_AC_BE,
	MT_EP_OUT_AC_VI,
	MT_EP_OUT_AC_VO,
	MT_EP_OUT_HCCA,
	__MT_EP_OUT_MAX,
पूर्ण;

अटल अंतरभूत काष्ठा usb_device *mt7601u_to_usb_dev(काष्ठा mt7601u_dev *mt7601u)
अणु
	वापस पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(mt7601u->dev));
पूर्ण

अटल अंतरभूत bool mt7601u_urb_has_error(काष्ठा urb *urb)
अणु
	वापस urb->status &&
		urb->status != -ENOENT &&
		urb->status != -ECONNRESET &&
		urb->status != -ESHUTDOWN;
पूर्ण

bool mt7601u_usb_alloc_buf(काष्ठा mt7601u_dev *dev, माप_प्रकार len,
			   काष्ठा mt7601u_dma_buf *buf);
व्योम mt7601u_usb_मुक्त_buf(काष्ठा mt7601u_dev *dev, काष्ठा mt7601u_dma_buf *buf);
पूर्णांक mt7601u_usb_submit_buf(काष्ठा mt7601u_dev *dev, पूर्णांक dir, पूर्णांक ep_idx,
			   काष्ठा mt7601u_dma_buf *buf, gfp_t gfp,
			   usb_complete_t complete_fn, व्योम *context);
व्योम mt7601u_complete_urb(काष्ठा urb *urb);

पूर्णांक mt7601u_venकरोr_request(काष्ठा mt7601u_dev *dev, स्थिर u8 req,
			   स्थिर u8 direction, स्थिर u16 val, स्थिर u16 offset,
			   व्योम *buf, स्थिर माप_प्रकार buflen);
व्योम mt7601u_venकरोr_reset(काष्ठा mt7601u_dev *dev);
पूर्णांक mt7601u_venकरोr_single_wr(काष्ठा mt7601u_dev *dev, स्थिर u8 req,
			     स्थिर u16 offset, स्थिर u32 val);

#पूर्ण_अगर
