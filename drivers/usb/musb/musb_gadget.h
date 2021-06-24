<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * MUSB OTG driver peripheral defines
 *
 * Copyright 2005 Mentor Graphics Corporation
 * Copyright (C) 2005-2006 by Texas Instruments
 * Copyright (C) 2006-2007 Nokia Corporation
 */

#अगर_अघोषित __MUSB_GADGET_H
#घोषणा __MUSB_GADGET_H

#समावेश <linux/list.h>

#अगर IS_ENABLED(CONFIG_USB_MUSB_GADGET) || IS_ENABLED(CONFIG_USB_MUSB_DUAL_ROLE)
बाह्य irqवापस_t musb_g_ep0_irq(काष्ठा musb *);
बाह्य व्योम musb_g_tx(काष्ठा musb *, u8);
बाह्य व्योम musb_g_rx(काष्ठा musb *, u8);
बाह्य व्योम musb_g_reset(काष्ठा musb *);
बाह्य व्योम musb_g_suspend(काष्ठा musb *);
बाह्य व्योम musb_g_resume(काष्ठा musb *);
बाह्य व्योम musb_g_wakeup(काष्ठा musb *);
बाह्य व्योम musb_g_disconnect(काष्ठा musb *);
बाह्य व्योम musb_gadget_cleanup(काष्ठा musb *);
बाह्य पूर्णांक musb_gadget_setup(काष्ठा musb *);

#अन्यथा
अटल अंतरभूत irqवापस_t musb_g_ep0_irq(काष्ठा musb *musb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम musb_g_tx(काष्ठा musb *musb, u8 epnum)	अणुपूर्ण
अटल अंतरभूत व्योम musb_g_rx(काष्ठा musb *musb, u8 epnum)	अणुपूर्ण
अटल अंतरभूत व्योम musb_g_reset(काष्ठा musb *musb)		अणुपूर्ण
अटल अंतरभूत व्योम musb_g_suspend(काष्ठा musb *musb)		अणुपूर्ण
अटल अंतरभूत व्योम musb_g_resume(काष्ठा musb *musb)		अणुपूर्ण
अटल अंतरभूत व्योम musb_g_wakeup(काष्ठा musb *musb)		अणुपूर्ण
अटल अंतरभूत व्योम musb_g_disconnect(काष्ठा musb *musb)		अणुपूर्ण
अटल अंतरभूत व्योम musb_gadget_cleanup(काष्ठा musb *musb)	अणुपूर्ण
अटल अंतरभूत पूर्णांक musb_gadget_setup(काष्ठा musb *musb)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

क्रमागत buffer_map_state अणु
	UN_MAPPED = 0,
	PRE_MAPPED,
	MUSB_MAPPED
पूर्ण;

काष्ठा musb_request अणु
	काष्ठा usb_request	request;
	काष्ठा list_head	list;
	काष्ठा musb_ep		*ep;
	काष्ठा musb		*musb;
	u8 tx;			/* endpoपूर्णांक direction */
	u8 epnum;
	क्रमागत buffer_map_state map_state;
पूर्ण;

#घोषणा to_musb_request(r)	container_of((r), काष्ठा musb_request, request)

बाह्य काष्ठा usb_request *
musb_alloc_request(काष्ठा usb_ep *ep, gfp_t gfp_flags);
बाह्य व्योम musb_मुक्त_request(काष्ठा usb_ep *ep, काष्ठा usb_request *req);


/*
 * काष्ठा musb_ep - peripheral side view of endpoपूर्णांक rx or tx side
 */
काष्ठा musb_ep अणु
	/* stuff towards the head is basically ग_लिखो-once. */
	काष्ठा usb_ep			end_poपूर्णांक;
	अक्षर				name[12];
	काष्ठा musb_hw_ep		*hw_ep;
	काष्ठा musb			*musb;
	u8				current_epnum;

	/* ... when enabled/disabled ... */
	u8				type;
	u8				is_in;
	u16				packet_sz;
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor	*desc;
	काष्ठा dma_channel		*dma;

	/* later things are modअगरied based on usage */
	काष्ठा list_head		req_list;

	u8				wedged;

	/* true अगर lock must be dropped but req_list may not be advanced */
	u8				busy;

	u8				hb_mult;
पूर्ण;

#घोषणा to_musb_ep(ep)	container_of((ep), काष्ठा musb_ep, end_poपूर्णांक)

अटल अंतरभूत काष्ठा musb_request *next_request(काष्ठा musb_ep *ep)
अणु
	काष्ठा list_head	*queue = &ep->req_list;

	अगर (list_empty(queue))
		वापस शून्य;
	वापस container_of(queue->next, काष्ठा musb_request, list);
पूर्ण

बाह्य स्थिर काष्ठा usb_ep_ops musb_g_ep0_ops;

बाह्य व्योम musb_g_giveback(काष्ठा musb_ep *, काष्ठा usb_request *, पूर्णांक);

बाह्य व्योम musb_ep_restart(काष्ठा musb *, काष्ठा musb_request *);

#पूर्ण_अगर		/* __MUSB_GADGET_H */
