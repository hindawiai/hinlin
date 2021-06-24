<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __USBHID_H
#घोषणा __USBHID_H

/*
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2001 Vojtech Pavlik
 *  Copyright (c) 2006 Jiri Kosina
 */

/*
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/समयr.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/input.h>

/*  API provided by hid-core.c क्रम USB HID drivers */
व्योम usbhid_init_reports(काष्ठा hid_device *hid);
काष्ठा usb_पूर्णांकerface *usbhid_find_पूर्णांकerface(पूर्णांक minor);

/* iofl flags */
#घोषणा HID_CTRL_RUNNING	1
#घोषणा HID_OUT_RUNNING		2
#घोषणा HID_IN_RUNNING		3
#घोषणा HID_RESET_PENDING	4
#घोषणा HID_SUSPENDED		5
#घोषणा HID_CLEAR_HALT		6
#घोषणा HID_DISCONNECTED	7
#घोषणा HID_STARTED		8
#घोषणा HID_KEYS_PRESSED	10
#घोषणा HID_NO_BANDWIDTH	11
#घोषणा HID_RESUME_RUNNING	12
/*
 * The device is खोलोed, meaning there is a client that is पूर्णांकerested
 * in data coming from the device.
 */
#घोषणा HID_OPENED		13
/*
 * We are polling input endpoपूर्णांक by [re]submitting IN URB, because
 * either HID device is खोलोed or ALWAYS POLL quirk is set क्रम the
 * device.
 */
#घोषणा HID_IN_POLLING		14

/*
 * USB-specअगरic HID काष्ठा, to be poपूर्णांकed to
 * from काष्ठा hid_device->driver_data
 */

काष्ठा usbhid_device अणु
	काष्ठा hid_device *hid;						/* poपूर्णांकer to corresponding HID dev */

	काष्ठा usb_पूर्णांकerface *पूर्णांकf;                                     /* USB पूर्णांकerface */
	पूर्णांक अगरnum;                                                      /* USB पूर्णांकerface number */

	अचिन्हित पूर्णांक bufsize;                                           /* URB buffer size */

	काष्ठा urb *urbin;                                              /* Input URB */
	अक्षर *inbuf;                                                    /* Input buffer */
	dma_addr_t inbuf_dma;                                           /* Input buffer dma */

	काष्ठा urb *urbctrl;                                            /* Control URB */
	काष्ठा usb_ctrlrequest *cr;                                     /* Control request काष्ठा */
	काष्ठा hid_control_fअगरo ctrl[HID_CONTROL_FIFO_SIZE];  		/* Control fअगरo */
	अचिन्हित अक्षर ctrlhead, ctrltail;                               /* Control fअगरo head & tail */
	अक्षर *ctrlbuf;                                                  /* Control buffer */
	dma_addr_t ctrlbuf_dma;                                         /* Control buffer dma */
	अचिन्हित दीर्घ last_ctrl;						/* record of last output क्रम समयouts */

	काष्ठा urb *urbout;                                             /* Output URB */
	काष्ठा hid_output_fअगरo out[HID_CONTROL_FIFO_SIZE];              /* Output pipe fअगरo */
	अचिन्हित अक्षर outhead, outtail;                                 /* Output pipe fअगरo head & tail */
	अक्षर *outbuf;                                                   /* Output buffer */
	dma_addr_t outbuf_dma;                                          /* Output buffer dma */
	अचिन्हित दीर्घ last_out;							/* record of last output क्रम समयouts */

	काष्ठा mutex mutex;						/* start/stop/खोलो/बंद */
	spinlock_t lock;						/* fअगरo spinlock */
	अचिन्हित दीर्घ iofl;                                             /* I/O flags (CTRL_RUNNING, OUT_RUNNING) */
	काष्ठा समयr_list io_retry;                                     /* Retry समयr */
	अचिन्हित दीर्घ stop_retry;                                       /* Time to give up, in jअगरfies */
	अचिन्हित पूर्णांक retry_delay;                                       /* Delay length in ms */
	काष्ठा work_काष्ठा reset_work;                                  /* Task context क्रम resets */
	रुको_queue_head_t रुको;						/* For sleeping */
पूर्ण;

#घोषणा	hid_to_usb_dev(hid_dev) \
	to_usb_device(hid_dev->dev.parent->parent)

#पूर्ण_अगर

