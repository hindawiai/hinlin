<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * MUSB OTG driver host defines
 *
 * Copyright 2005 Mentor Graphics Corporation
 * Copyright (C) 2005-2006 by Texas Instruments
 * Copyright (C) 2006-2007 Nokia Corporation
 */

#अगर_अघोषित _MUSB_HOST_H
#घोषणा _MUSB_HOST_H

#समावेश <linux/scatterlist.h>

/* stored in "usb_host_endpoint.hcpriv" क्रम scheduled endpoपूर्णांकs */
काष्ठा musb_qh अणु
	काष्ठा usb_host_endpoपूर्णांक *hep;		/* usbcore info */
	काष्ठा usb_device	*dev;
	काष्ठा musb_hw_ep	*hw_ep;		/* current binding */

	काष्ठा list_head	ring;		/* of musb_qh */
	/* काष्ठा musb_qh		*next; */	/* क्रम periodic tree */
	u8			mux;		/* qh multiplexed to hw_ep */

	अचिन्हित		offset;		/* in urb->transfer_buffer */
	अचिन्हित		segsize;	/* current xfer fragment */

	u8			type_reg;	/* अणुrx,txपूर्ण type रेजिस्टर */
	u8			पूर्णांकv_reg;	/* अणुrx,txपूर्ण पूर्णांकerval रेजिस्टर */
	u8			addr_reg;	/* device address रेजिस्टर */
	u8			h_addr_reg;	/* hub address रेजिस्टर */
	u8			h_port_reg;	/* hub port रेजिस्टर */

	u8			is_पढ़ोy;	/* safe to modअगरy hw_ep */
	u8			type;		/* XFERTYPE_* */
	u8			epnum;
	u8			hb_mult;	/* high bandwidth pkts per uf */
	u16			maxpacket;
	u16			frame;		/* क्रम periodic schedule */
	अचिन्हित		iso_idx;	/* in urb->iso_frame_desc[] */
	काष्ठा sg_mapping_iter sg_miter;	/* क्रम highmem in PIO mode */
	bool			use_sg;		/* to track urb using sglist */
पूर्ण;

/* map from control or bulk queue head to the first qh on that ring */
अटल अंतरभूत काष्ठा musb_qh *first_qh(काष्ठा list_head *q)
अणु
	अगर (list_empty(q))
		वापस शून्य;
	वापस list_entry(q->next, काष्ठा musb_qh, ring);
पूर्ण


#अगर IS_ENABLED(CONFIG_USB_MUSB_HOST) || IS_ENABLED(CONFIG_USB_MUSB_DUAL_ROLE)
बाह्य काष्ठा musb *hcd_to_musb(काष्ठा usb_hcd *);
बाह्य irqवापस_t musb_h_ep0_irq(काष्ठा musb *);
बाह्य पूर्णांक musb_host_alloc(काष्ठा musb *);
बाह्य पूर्णांक musb_host_setup(काष्ठा musb *, पूर्णांक);
बाह्य व्योम musb_host_cleanup(काष्ठा musb *);
बाह्य व्योम musb_host_tx(काष्ठा musb *, u8);
बाह्य व्योम musb_host_rx(काष्ठा musb *, u8);
बाह्य व्योम musb_root_disconnect(काष्ठा musb *musb);
बाह्य व्योम musb_host_मुक्त(काष्ठा musb *);
बाह्य व्योम musb_host_cleanup(काष्ठा musb *);
बाह्य व्योम musb_host_tx(काष्ठा musb *, u8);
बाह्य व्योम musb_host_rx(काष्ठा musb *, u8);
बाह्य व्योम musb_root_disconnect(काष्ठा musb *musb);
बाह्य व्योम musb_host_resume_root_hub(काष्ठा musb *musb);
बाह्य व्योम musb_host_poke_root_hub(काष्ठा musb *musb);
बाह्य पूर्णांक musb_port_suspend(काष्ठा musb *musb, bool करो_suspend);
बाह्य व्योम musb_port_reset(काष्ठा musb *musb, bool करो_reset);
बाह्य व्योम musb_host_finish_resume(काष्ठा work_काष्ठा *work);
#अन्यथा
अटल अंतरभूत काष्ठा musb *hcd_to_musb(काष्ठा usb_hcd *hcd)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत irqवापस_t musb_h_ep0_irq(काष्ठा musb *musb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक musb_host_alloc(काष्ठा musb *musb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक musb_host_setup(काष्ठा musb *musb, पूर्णांक घातer_budget)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम musb_host_cleanup(काष्ठा musb *musb)		अणुपूर्ण
अटल अंतरभूत व्योम musb_host_मुक्त(काष्ठा musb *musb)		अणुपूर्ण
अटल अंतरभूत व्योम musb_host_tx(काष्ठा musb *musb, u8 epnum)	अणुपूर्ण
अटल अंतरभूत व्योम musb_host_rx(काष्ठा musb *musb, u8 epnum)	अणुपूर्ण
अटल अंतरभूत व्योम musb_root_disconnect(काष्ठा musb *musb)	अणुपूर्ण
अटल अंतरभूत व्योम musb_host_resume_root_hub(काष्ठा musb *musb)	अणुपूर्ण
अटल अंतरभूत व्योम musb_host_poke_root_hub(काष्ठा musb *musb)	अणुपूर्ण
अटल अंतरभूत पूर्णांक musb_port_suspend(काष्ठा musb *musb, bool करो_suspend)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम musb_port_reset(काष्ठा musb *musb, bool करो_reset) अणुपूर्ण
अटल अंतरभूत व्योम musb_host_finish_resume(काष्ठा work_काष्ठा *work) अणुपूर्ण
#पूर्ण_अगर

काष्ठा usb_hcd;

बाह्य पूर्णांक musb_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf);
बाह्य पूर्णांक musb_hub_control(काष्ठा usb_hcd *hcd,
			u16 typeReq, u16 wValue, u16 wIndex,
			अक्षर *buf, u16 wLength);

अटल अंतरभूत काष्ठा urb *next_urb(काष्ठा musb_qh *qh)
अणु
	काष्ठा list_head	*queue;

	अगर (!qh)
		वापस शून्य;
	queue = &qh->hep->urb_list;
	अगर (list_empty(queue))
		वापस शून्य;
	वापस list_entry(queue->next, काष्ठा urb, urb_list);
पूर्ण

#पूर्ण_अगर				/* _MUSB_HOST_H */
