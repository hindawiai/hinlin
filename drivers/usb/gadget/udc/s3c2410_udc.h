<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * linux/drivers/usb/gadget/s3c2410_udc.h
 * Samsung on-chip full speed USB device controllers
 *
 * Copyright (C) 2004-2007 Herbert Pथघtzl - Arnaud Patard
 *	Additional cleanups by Ben Dooks <ben-linux@fluff.org>
 */

#अगर_अघोषित _S3C2410_UDC_H
#घोषणा _S3C2410_UDC_H

काष्ठा s3c2410_ep अणु
	काष्ठा list_head		queue;
	अचिन्हित दीर्घ			last_io;	/* jअगरfies बारtamp */
	काष्ठा usb_gadget		*gadget;
	काष्ठा s3c2410_udc		*dev;
	काष्ठा usb_ep			ep;
	u8				num;

	अचिन्हित लघु			fअगरo_size;
	u8				bEndpoपूर्णांकAddress;
	u8				bmAttributes;

	अचिन्हित			halted : 1;
	अचिन्हित			alपढ़ोy_seen : 1;
	अचिन्हित			setup_stage : 1;
पूर्ण;


/* Warning : ep0 has a fअगरo of 16 bytes */
/* Don't try to set 32 or 64            */
/* also testusb 14 fails  wit 16 but is */
/* fine with 8                          */
#घोषणा EP0_FIFO_SIZE		 8
#घोषणा EP_FIFO_SIZE		64
#घोषणा DEFAULT_POWER_STATE	0x00

#घोषणा S3C2440_EP_FIFO_SIZE	128

अटल स्थिर अक्षर ep0name [] = "ep0";

अटल स्थिर अक्षर *स्थिर ep_name[] = अणु
	ep0name,                                /* everyone has ep0 */
	/* s3c2410 four bidirectional bulk endpoपूर्णांकs */
	"ep1-bulk", "ep2-bulk", "ep3-bulk", "ep4-bulk",
पूर्ण;

#घोषणा S3C2410_ENDPOINTS       ARRAY_SIZE(ep_name)

काष्ठा s3c2410_request अणु
	काष्ठा list_head		queue;		/* ep's requests */
	काष्ठा usb_request		req;
पूर्ण;

क्रमागत ep0_state अणु
        EP0_IDLE,
        EP0_IN_DATA_PHASE,
        EP0_OUT_DATA_PHASE,
        EP0_END_XFER,
        EP0_STALL,
पूर्ण;

अटल स्थिर अक्षर *ep0states[]= अणु
        "EP0_IDLE",
        "EP0_IN_DATA_PHASE",
        "EP0_OUT_DATA_PHASE",
        "EP0_END_XFER",
        "EP0_STALL",
पूर्ण;

काष्ठा s3c2410_udc अणु
	spinlock_t			lock;

	काष्ठा s3c2410_ep		ep[S3C2410_ENDPOINTS];
	पूर्णांक				address;
	काष्ठा usb_gadget		gadget;
	काष्ठा usb_gadget_driver	*driver;
	काष्ठा s3c2410_request		fअगरo_req;
	u8				fअगरo_buf[EP_FIFO_SIZE];
	u16				devstatus;

	u32				port_status;
	पूर्णांक				ep0state;

	अचिन्हित			got_irq : 1;

	अचिन्हित			req_std : 1;
	अचिन्हित			req_config : 1;
	अचिन्हित			req_pending : 1;
	u8				vbus;
	काष्ठा dentry			*regs_info;
	पूर्णांक				irq;
पूर्ण;
#घोषणा to_s3c2410(g)	(container_of((g), काष्ठा s3c2410_udc, gadget))

#पूर्ण_अगर
