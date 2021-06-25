<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2015 Karol Kosik <karo9@पूर्णांकeria.eu>
 * Copyright (C) 2015-2016 Samsung Electronics
 *               Igor Kotrasinski <i.kotrasinsk@samsung.com>
 *               Krzysztof Opasiak <k.opasiak@samsung.com>
 */

#अगर_अघोषित __USBIP_VUDC_H
#घोषणा __USBIP_VUDC_H

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/समय.स>
#समावेश <linux/sysfs.h>

#समावेश "usbip_common.h"

#घोषणा GADGET_NAME "usbip-vudc"

काष्ठा vep अणु
	काष्ठा usb_ep ep;
	अचिन्हित type:2; /* type, as USB_ENDPOINT_XFER_* */
	अक्षर name[8];	/* space क्रम ep name */

	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc;
	काष्ठा usb_gadget *gadget;
	काष्ठा list_head req_queue; /* Request queue */
	अचिन्हित halted:1;
	अचिन्हित wedged:1;
	अचिन्हित alपढ़ोy_seen:1;
	अचिन्हित setup_stage:1;
पूर्ण;

काष्ठा vrequest अणु
	काष्ठा usb_request req;
	काष्ठा vudc *udc;
	काष्ठा list_head req_entry; /* Request queue */
पूर्ण;

काष्ठा urbp अणु
	काष्ठा urb *urb;
	काष्ठा vep *ep;
	काष्ठा list_head urb_entry; /* urb queue */
	अचिन्हित दीर्घ seqnum;
	अचिन्हित type:2; /* क्रम tx, since ep type can change after */
	अचिन्हित new:1;
पूर्ण;

काष्ठा v_unlink अणु
	अचिन्हित दीर्घ seqnum;
	__u32 status;
पूर्ण;

क्रमागत tx_type अणु
	TX_UNLINK,
	TX_SUBMIT,
पूर्ण;

काष्ठा tx_item अणु
	काष्ठा list_head tx_entry;
	क्रमागत tx_type type;
	जोड़ अणु
		काष्ठा urbp *s;
		काष्ठा v_unlink *u;
	पूर्ण;
पूर्ण;

क्रमागत tr_state अणु
	VUDC_TR_RUNNING,
	VUDC_TR_IDLE,
	VUDC_TR_STOPPED,
पूर्ण;

काष्ठा transfer_समयr अणु
	काष्ठा समयr_list समयr;
	क्रमागत tr_state state;
	अचिन्हित दीर्घ frame_start;
	पूर्णांक frame_limit;
पूर्ण;

काष्ठा vudc अणु
	काष्ठा usb_gadget gadget;
	काष्ठा usb_gadget_driver *driver;
	काष्ठा platक्रमm_device *pdev;

	काष्ठा usb_device_descriptor dev_desc;

	काष्ठा usbip_device ud;
	काष्ठा transfer_समयr tr_समयr;
	काष्ठा बारpec64 start_समय;

	काष्ठा list_head urb_queue;

	spinlock_t lock_tx;
	काष्ठा list_head tx_queue;
	रुको_queue_head_t tx_रुकोq;

	spinlock_t lock;
	काष्ठा vep *ep;
	पूर्णांक address;
	u16 devstatus;

	अचिन्हित pullup:1;
	अचिन्हित connected:1;
	अचिन्हित desc_cached:1;
पूर्ण;

काष्ठा vudc_device अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा list_head dev_entry;
पूर्ण;

बाह्य स्थिर काष्ठा attribute_group *vudc_groups[];

/* visible everywhere */

अटल अंतरभूत काष्ठा vep *to_vep(काष्ठा usb_ep *_ep)
अणु
	वापस container_of(_ep, काष्ठा vep, ep);
पूर्ण

अटल अंतरभूत काष्ठा vrequest *to_vrequest(
	काष्ठा usb_request *_req)
अणु
	वापस container_of(_req, काष्ठा vrequest, req);
पूर्ण

अटल अंतरभूत काष्ठा vudc *usb_gadget_to_vudc(
	काष्ठा usb_gadget *_gadget)
अणु
	वापस container_of(_gadget, काष्ठा vudc, gadget);
पूर्ण

अटल अंतरभूत काष्ठा vudc *ep_to_vudc(काष्ठा vep *ep)
अणु
	वापस container_of(ep->gadget, काष्ठा vudc, gadget);
पूर्ण

/* vudc_sysfs.c */

पूर्णांक get_gadget_descs(काष्ठा vudc *udc);

/* vudc_tx.c */

पूर्णांक v_tx_loop(व्योम *data);
व्योम v_enqueue_ret_unlink(काष्ठा vudc *udc, __u32 seqnum, __u32 status);
व्योम v_enqueue_ret_submit(काष्ठा vudc *udc, काष्ठा urbp *urb_p);

/* vudc_rx.c */

पूर्णांक v_rx_loop(व्योम *data);

/* vudc_transfer.c */

व्योम v_init_समयr(काष्ठा vudc *udc);
व्योम v_start_समयr(काष्ठा vudc *udc);
व्योम v_kick_समयr(काष्ठा vudc *udc, अचिन्हित दीर्घ समय);
व्योम v_stop_समयr(काष्ठा vudc *udc);

/* vudc_dev.c */

काष्ठा urbp *alloc_urbp(व्योम);
व्योम मुक्त_urbp_and_urb(काष्ठा urbp *urb_p);

काष्ठा vep *vudc_find_endpoपूर्णांक(काष्ठा vudc *udc, u8 address);

काष्ठा vudc_device *alloc_vudc_device(पूर्णांक devid);
व्योम put_vudc_device(काष्ठा vudc_device *udc_dev);

पूर्णांक vudc_probe(काष्ठा platक्रमm_device *pdev);
पूर्णांक vudc_हटाओ(काष्ठा platक्रमm_device *pdev);

#पूर्ण_अगर /* __USBIP_VUDC_H */
