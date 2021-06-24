<शैली गुरु>
/*
 * USB Orinoco driver
 *
 * Copyright (c) 2003 Manuel Estrada Sainz
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License
 * at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License क्रम the specअगरic language governing rights and
 * limitations under the License.
 *
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU General Public License version 2 (the "GPL"), in
 * which हाल the provisions of the GPL are applicable instead of the
 * above.  If you wish to allow the use of your version of this file
 * only under the terms of the GPL and not to allow others to use your
 * version of this file under the MPL, indicate your decision by
 * deleting the provisions above and replace them with the notice and
 * other provisions required by the GPL.  If you करो not delete the
 * provisions above, a recipient may use your version of this file
 * under either the MPL or the GPL.
 *
 * Queueing code based on linux-wlan-ng 0.2.1-pre5
 *
 * Copyright (C) 1999 AbsoluteValue Systems, Inc.  All Rights Reserved.
 *
 *	The license is the same as above.
 *
 * Initialy based on USB Skeleton driver - 0.7
 *
 * Copyright (c) 2001 Greg Kroah-Harपंचांगan (greg@kroah.com)
 *
 *	This program is मुक्त software; you can redistribute it and/or
 *	modअगरy it under the terms of the GNU General Public License as
 *	published by the Free Software Foundation; either version 2 of
 *	the License, or (at your option) any later version.
 *
 * NOTE: The original USB Skeleton driver is GPL, but all that code is
 * gone so MPL/GPL applies.
 */

#घोषणा DRIVER_NAME "orinoco_usb"
#घोषणा PFX DRIVER_NAME ": "

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/usb.h>
#समावेश <linux/समयr.h>

#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/wireless.h>
#समावेश <linux/firmware.h>
#समावेश <linux/refcount.h>

#समावेश "mic.h"
#समावेश "orinoco.h"

#अगर_अघोषित URB_ASYNC_UNLINK
#घोषणा URB_ASYNC_UNLINK 0
#पूर्ण_अगर

काष्ठा header_काष्ठा अणु
	/* 802.3 */
	u8 dest[ETH_ALEN];
	u8 src[ETH_ALEN];
	__be16 len;
	/* 802.2 */
	u8 dsap;
	u8 ssap;
	u8 ctrl;
	/* SNAP */
	u8 oui[3];
	__be16 ethertype;
पूर्ण __packed;

काष्ठा ez_usb_fw अणु
	u16 size;
	स्थिर u8 *code;
पूर्ण;

अटल काष्ठा ez_usb_fw firmware = अणु
	.size = 0,
	.code = शून्य,
पूर्ण;

/* Debugging macros */
#अघोषित err
#घोषणा err(क्रमmat, arg...) \
	करो अणु prपूर्णांकk(KERN_ERR PFX क्रमmat "\n", ## arg); पूर्ण जबतक (0)

MODULE_FIRMWARE("orinoco_ezusb_fw");

/*
 * Under some conditions, the card माला_लो stuck and stops paying attention
 * to the world (i.e. data communication stalls) until we करो something to
 * it.  Sending an INQ_TALLIES command seems to be enough and should be
 * harmless otherwise.  This behaviour has been observed when using the
 * driver on a प्रणालीimager client during installation.  In the past a
 * समयr was used to send INQ_TALLIES commands when there was no other
 * activity, but it was troublesome and was हटाओd.
 */

#घोषणा USB_COMPAQ_VENDOR_ID     0x049f /* Compaq Computer Corp. */
#घोषणा USB_COMPAQ_WL215_ID      0x001f /* Compaq WL215 USB Adapter */
#घोषणा USB_COMPAQ_W200_ID       0x0076 /* Compaq W200 USB Adapter */
#घोषणा USB_HP_WL215_ID          0x0082 /* Compaq WL215 USB Adapter */

#घोषणा USB_MELCO_VENDOR_ID      0x0411
#घोषणा USB_BUFFALO_L11_ID       0x0006 /* BUFFALO WLI-USB-L11 */
#घोषणा USB_BUFFALO_L11G_WR_ID   0x000B /* BUFFALO WLI-USB-L11G-WR */
#घोषणा USB_BUFFALO_L11G_ID      0x000D /* BUFFALO WLI-USB-L11G */

#घोषणा USB_LUCENT_VENDOR_ID     0x047E /* Lucent Technologies */
#घोषणा USB_LUCENT_ORINOCO_ID    0x0300 /* Lucent/Agere Orinoco USB Client */

#घोषणा USB_AVAYA8_VENDOR_ID     0x0D98
#घोषणा USB_AVAYAE_VENDOR_ID     0x0D9E
#घोषणा USB_AVAYA_WIRELESS_ID    0x0300 /* Avaya Wireless USB Card */

#घोषणा USB_AGERE_VENDOR_ID      0x0D4E /* Agere Systems */
#घोषणा USB_AGERE_MODEL0801_ID   0x1000 /* Wireless USB Card Model 0801 */
#घोषणा USB_AGERE_MODEL0802_ID   0x1001 /* Wireless USB Card Model 0802 */
#घोषणा USB_AGERE_REBRANDED_ID   0x047A /* WLAN USB Card */

#घोषणा USB_ELSA_VENDOR_ID       0x05CC
#घोषणा USB_ELSA_AIRLANCER_ID    0x3100 /* ELSA AirLancer USB-11 */

#घोषणा USB_LEGEND_VENDOR_ID     0x0E7C
#घोषणा USB_LEGEND_JOYNET_ID     0x0300 /* Joynet WLAN USB Card */

#घोषणा USB_SAMSUNG_VENDOR_ID    0x04E8
#घोषणा USB_SAMSUNG_SEW2001U1_ID 0x5002 /* Samsung SEW-2001u Card */
#घोषणा USB_SAMSUNG_SEW2001U2_ID 0x5B11 /* Samsung SEW-2001u Card */
#घोषणा USB_SAMSUNG_SEW2003U_ID  0x7011 /* Samsung SEW-2003U Card */

#घोषणा USB_IGATE_VENDOR_ID      0x0681
#घोषणा USB_IGATE_IGATE_11M_ID   0x0012 /* I-GATE 11M USB Card */

#घोषणा USB_FUJITSU_VENDOR_ID    0x0BF8
#घोषणा USB_FUJITSU_E1100_ID     0x1002 /* connect2AIR WLAN E-1100 USB */

#घोषणा USB_2WIRE_VENDOR_ID      0x1630
#घोषणा USB_2WIRE_WIRELESS_ID    0xff81 /* 2Wire Wireless USB adapter */


#घोषणा EZUSB_REQUEST_FW_TRANS		0xA0
#घोषणा EZUSB_REQUEST_TRIGGER		0xAA
#घोषणा EZUSB_REQUEST_TRIG_AC		0xAC
#घोषणा EZUSB_CPUCS_REG			0x7F92

#घोषणा EZUSB_RID_TX			0x0700
#घोषणा EZUSB_RID_RX			0x0701
#घोषणा EZUSB_RID_INIT1			0x0702
#घोषणा EZUSB_RID_ACK			0x0710
#घोषणा EZUSB_RID_READ_PDA		0x0800
#घोषणा EZUSB_RID_PROG_INIT		0x0852
#घोषणा EZUSB_RID_PROG_SET_ADDR		0x0853
#घोषणा EZUSB_RID_PROG_BYTES		0x0854
#घोषणा EZUSB_RID_PROG_END		0x0855
#घोषणा EZUSB_RID_DOCMD			0x0860

/* Recognize info frames */
#घोषणा EZUSB_IS_INFO(id)		((id >= 0xF000) && (id <= 0xF2FF))

#घोषणा EZUSB_MAGIC			0x0210

#घोषणा EZUSB_FRAME_DATA		1
#घोषणा EZUSB_FRAME_CONTROL		2

#घोषणा DEF_TIMEOUT			(3 * HZ)

#घोषणा BULK_BUF_SIZE			2048

#घोषणा MAX_DL_SIZE (BULK_BUF_SIZE - माप(काष्ठा ezusb_packet))

#घोषणा FW_BUF_SIZE			64
#घोषणा FW_VAR_OFFSET_PTR		0x359
#घोषणा FW_VAR_VALUE			0
#घोषणा FW_HOLE_START			0x100
#घोषणा FW_HOLE_END			0x300

काष्ठा ezusb_packet अणु
	__le16 magic;		/* 0x0210 */
	u8 req_reply_count;
	u8 ans_reply_count;
	__le16 frame_type;	/* 0x01 क्रम data frames, 0x02 otherwise */
	__le16 size;		/* transport size */
	__le16 crc;		/* CRC up to here */
	__le16 hermes_len;
	__le16 hermes_rid;
	u8 data[];
पूर्ण __packed;

/* Table of devices that work or may work with this driver */
अटल स्थिर काष्ठा usb_device_id ezusb_table[] = अणु
	अणुUSB_DEVICE(USB_COMPAQ_VENDOR_ID, USB_COMPAQ_WL215_ID)पूर्ण,
	अणुUSB_DEVICE(USB_COMPAQ_VENDOR_ID, USB_HP_WL215_ID)पूर्ण,
	अणुUSB_DEVICE(USB_COMPAQ_VENDOR_ID, USB_COMPAQ_W200_ID)पूर्ण,
	अणुUSB_DEVICE(USB_MELCO_VENDOR_ID, USB_BUFFALO_L11_ID)पूर्ण,
	अणुUSB_DEVICE(USB_MELCO_VENDOR_ID, USB_BUFFALO_L11G_WR_ID)पूर्ण,
	अणुUSB_DEVICE(USB_MELCO_VENDOR_ID, USB_BUFFALO_L11G_ID)पूर्ण,
	अणुUSB_DEVICE(USB_LUCENT_VENDOR_ID, USB_LUCENT_ORINOCO_ID)पूर्ण,
	अणुUSB_DEVICE(USB_AVAYA8_VENDOR_ID, USB_AVAYA_WIRELESS_ID)पूर्ण,
	अणुUSB_DEVICE(USB_AVAYAE_VENDOR_ID, USB_AVAYA_WIRELESS_ID)पूर्ण,
	अणुUSB_DEVICE(USB_AGERE_VENDOR_ID, USB_AGERE_MODEL0801_ID)पूर्ण,
	अणुUSB_DEVICE(USB_AGERE_VENDOR_ID, USB_AGERE_MODEL0802_ID)पूर्ण,
	अणुUSB_DEVICE(USB_ELSA_VENDOR_ID, USB_ELSA_AIRLANCER_ID)पूर्ण,
	अणुUSB_DEVICE(USB_LEGEND_VENDOR_ID, USB_LEGEND_JOYNET_ID)पूर्ण,
	अणुUSB_DEVICE_VER(USB_SAMSUNG_VENDOR_ID, USB_SAMSUNG_SEW2001U1_ID,
			0, 0)पूर्ण,
	अणुUSB_DEVICE(USB_SAMSUNG_VENDOR_ID, USB_SAMSUNG_SEW2001U2_ID)पूर्ण,
	अणुUSB_DEVICE(USB_SAMSUNG_VENDOR_ID, USB_SAMSUNG_SEW2003U_ID)पूर्ण,
	अणुUSB_DEVICE(USB_IGATE_VENDOR_ID, USB_IGATE_IGATE_11M_ID)पूर्ण,
	अणुUSB_DEVICE(USB_FUJITSU_VENDOR_ID, USB_FUJITSU_E1100_ID)पूर्ण,
	अणुUSB_DEVICE(USB_2WIRE_VENDOR_ID, USB_2WIRE_WIRELESS_ID)पूर्ण,
	अणुUSB_DEVICE(USB_AGERE_VENDOR_ID, USB_AGERE_REBRANDED_ID)पूर्ण,
	अणुपूर्ण			/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, ezusb_table);

/* Structure to hold all of our device specअगरic stuff */
काष्ठा ezusb_priv अणु
	काष्ठा usb_device *udev;
	काष्ठा net_device *dev;
	काष्ठा mutex mtx;
	spinlock_t req_lock;
	काष्ठा list_head req_pending;
	काष्ठा list_head req_active;
	spinlock_t reply_count_lock;
	u16 hermes_reg_fake[0x40];
	u8 *bap_buf;
	काष्ठा urb *पढ़ो_urb;
	पूर्णांक पढ़ो_pipe;
	पूर्णांक ग_लिखो_pipe;
	u8 reply_count;
पूर्ण;

क्रमागत ezusb_state अणु
	EZUSB_CTX_START,
	EZUSB_CTX_QUEUED,
	EZUSB_CTX_REQ_SUBMITTED,
	EZUSB_CTX_REQ_COMPLETE,
	EZUSB_CTX_RESP_RECEIVED,
	EZUSB_CTX_REQ_TIMEOUT,
	EZUSB_CTX_REQ_FAILED,
	EZUSB_CTX_RESP_TIMEOUT,
	EZUSB_CTX_REQSUBMIT_FAIL,
	EZUSB_CTX_COMPLETE,
पूर्ण;

काष्ठा request_context अणु
	काष्ठा list_head list;
	refcount_t refcount;
	काष्ठा completion करोne;	/* Signals that CTX is dead */
	पूर्णांक समाप्तed;
	काष्ठा urb *outurb;	/* OUT क्रम req pkt */
	काष्ठा ezusb_priv *upriv;
	काष्ठा ezusb_packet *buf;
	पूर्णांक buf_length;
	काष्ठा समयr_list समयr;	/* Timeout handling */
	क्रमागत ezusb_state state;	/* Current state */
	/* the RID that we will रुको क्रम */
	u16 out_rid;
	u16 in_rid;
पूर्ण;


/* Forward declarations */
अटल व्योम ezusb_ctx_complete(काष्ठा request_context *ctx);
अटल व्योम ezusb_req_queue_run(काष्ठा ezusb_priv *upriv);
अटल व्योम ezusb_bulk_in_callback(काष्ठा urb *urb);

अटल अंतरभूत u8 ezusb_reply_inc(u8 count)
अणु
	अगर (count < 0x7F)
		वापस count + 1;
	अन्यथा
		वापस 1;
पूर्ण

अटल व्योम ezusb_request_context_put(काष्ठा request_context *ctx)
अणु
	अगर (!refcount_dec_and_test(&ctx->refcount))
		वापस;

	WARN_ON(!ctx->करोne.करोne);
	BUG_ON(ctx->outurb->status == -EINPROGRESS);
	BUG_ON(समयr_pending(&ctx->समयr));
	usb_मुक्त_urb(ctx->outurb);
	kमुक्त(ctx->buf);
	kमुक्त(ctx);
पूर्ण

अटल अंतरभूत व्योम ezusb_mod_समयr(काष्ठा ezusb_priv *upriv,
				   काष्ठा समयr_list *समयr,
				   अचिन्हित दीर्घ expire)
अणु
	अगर (!upriv->udev)
		वापस;
	mod_समयr(समयr, expire);
पूर्ण

अटल व्योम ezusb_request_समयrfn(काष्ठा समयr_list *t)
अणु
	काष्ठा request_context *ctx = from_समयr(ctx, t, समयr);

	ctx->outurb->transfer_flags |= URB_ASYNC_UNLINK;
	अगर (usb_unlink_urb(ctx->outurb) == -EINPROGRESS) अणु
		ctx->state = EZUSB_CTX_REQ_TIMEOUT;
	पूर्ण अन्यथा अणु
		ctx->state = EZUSB_CTX_RESP_TIMEOUT;
		dev_dbg(&ctx->outurb->dev->dev, "couldn't unlink\n");
		refcount_inc(&ctx->refcount);
		ctx->समाप्तed = 1;
		ezusb_ctx_complete(ctx);
		ezusb_request_context_put(ctx);
	पूर्ण
पूर्ण;

अटल काष्ठा request_context *ezusb_alloc_ctx(काष्ठा ezusb_priv *upriv,
					       u16 out_rid, u16 in_rid)
अणु
	काष्ठा request_context *ctx;

	ctx = kzalloc(माप(*ctx), GFP_ATOMIC);
	अगर (!ctx)
		वापस शून्य;

	ctx->buf = kदो_स्मृति(BULK_BUF_SIZE, GFP_ATOMIC);
	अगर (!ctx->buf) अणु
		kमुक्त(ctx);
		वापस शून्य;
	पूर्ण
	ctx->outurb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!ctx->outurb) अणु
		kमुक्त(ctx->buf);
		kमुक्त(ctx);
		वापस शून्य;
	पूर्ण

	ctx->upriv = upriv;
	ctx->state = EZUSB_CTX_START;
	ctx->out_rid = out_rid;
	ctx->in_rid = in_rid;

	refcount_set(&ctx->refcount, 1);
	init_completion(&ctx->करोne);

	समयr_setup(&ctx->समयr, ezusb_request_समयrfn, 0);
	वापस ctx;
पूर्ण

अटल व्योम ezusb_ctx_complete(काष्ठा request_context *ctx)
अणु
	काष्ठा ezusb_priv *upriv = ctx->upriv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&upriv->req_lock, flags);

	list_del_init(&ctx->list);
	अगर (upriv->udev) अणु
		spin_unlock_irqrestore(&upriv->req_lock, flags);
		ezusb_req_queue_run(upriv);
		spin_lock_irqsave(&upriv->req_lock, flags);
	पूर्ण

	चयन (ctx->state) अणु
	हाल EZUSB_CTX_COMPLETE:
	हाल EZUSB_CTX_REQSUBMIT_FAIL:
	हाल EZUSB_CTX_REQ_FAILED:
	हाल EZUSB_CTX_REQ_TIMEOUT:
	हाल EZUSB_CTX_RESP_TIMEOUT:
		spin_unlock_irqrestore(&upriv->req_lock, flags);

		अगर ((ctx->out_rid == EZUSB_RID_TX) && upriv->dev) अणु
			काष्ठा net_device *dev = upriv->dev;
			काष्ठा net_device_stats *stats = &dev->stats;

			अगर (ctx->state != EZUSB_CTX_COMPLETE)
				stats->tx_errors++;
			अन्यथा
				stats->tx_packets++;

			netअगर_wake_queue(dev);
		पूर्ण
		complete_all(&ctx->करोne);
		ezusb_request_context_put(ctx);
		अवरोध;

	शेष:
		spin_unlock_irqrestore(&upriv->req_lock, flags);
		अगर (!upriv->udev) अणु
			/* This is normal, as all request contexts get flushed
			 * when the device is disconnected */
			err("Called, CTX not terminating, but device gone");
			complete_all(&ctx->करोne);
			ezusb_request_context_put(ctx);
			अवरोध;
		पूर्ण

		err("Called, CTX not in terminating state.");
		/* Things are really bad अगर this happens. Just leak
		 * the CTX because it may still be linked to the
		 * queue or the OUT urb may still be active.
		 * Just leaking at least prevents an Oops or Panic.
		 */
		अवरोध;
	पूर्ण
पूर्ण

/*
 * ezusb_req_queue_run:
 * Description:
 *	Note: Only one active CTX at any one समय, because there's no
 *	other (reliable) way to match the response URB to the correct
 *	CTX.
 */
अटल व्योम ezusb_req_queue_run(काष्ठा ezusb_priv *upriv)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा request_context *ctx;
	पूर्णांक result;

	spin_lock_irqsave(&upriv->req_lock, flags);

	अगर (!list_empty(&upriv->req_active))
		जाओ unlock;

	अगर (list_empty(&upriv->req_pending))
		जाओ unlock;

	ctx =
	    list_entry(upriv->req_pending.next, काष्ठा request_context,
		       list);

	अगर (!ctx->upriv->udev)
		जाओ unlock;

	/* We need to split this off to aव्योम a race condition */
	list_move_tail(&ctx->list, &upriv->req_active);

	अगर (ctx->state == EZUSB_CTX_QUEUED) अणु
		refcount_inc(&ctx->refcount);
		result = usb_submit_urb(ctx->outurb, GFP_ATOMIC);
		अगर (result) अणु
			ctx->state = EZUSB_CTX_REQSUBMIT_FAIL;

			spin_unlock_irqrestore(&upriv->req_lock, flags);

			err("Fatal, failed to submit command urb."
			    " error=%d\n", result);

			ezusb_ctx_complete(ctx);
			ezusb_request_context_put(ctx);
			जाओ करोne;
		पूर्ण

		ctx->state = EZUSB_CTX_REQ_SUBMITTED;
		ezusb_mod_समयr(ctx->upriv, &ctx->समयr,
				jअगरfies + DEF_TIMEOUT);
	पूर्ण

 unlock:
	spin_unlock_irqrestore(&upriv->req_lock, flags);

 करोne:
	वापस;
पूर्ण

अटल व्योम ezusb_req_enqueue_run(काष्ठा ezusb_priv *upriv,
				  काष्ठा request_context *ctx)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&upriv->req_lock, flags);

	अगर (!ctx->upriv->udev) अणु
		spin_unlock_irqrestore(&upriv->req_lock, flags);
		जाओ करोne;
	पूर्ण
	refcount_inc(&ctx->refcount);
	list_add_tail(&ctx->list, &upriv->req_pending);
	spin_unlock_irqrestore(&upriv->req_lock, flags);

	ctx->state = EZUSB_CTX_QUEUED;
	ezusb_req_queue_run(upriv);

 करोne:
	वापस;
पूर्ण

अटल व्योम ezusb_request_out_callback(काष्ठा urb *urb)
अणु
	अचिन्हित दीर्घ flags;
	क्रमागत ezusb_state state;
	काष्ठा request_context *ctx = urb->context;
	काष्ठा ezusb_priv *upriv = ctx->upriv;

	spin_lock_irqsave(&upriv->req_lock, flags);

	del_समयr(&ctx->समयr);

	अगर (ctx->समाप्तed) अणु
		spin_unlock_irqrestore(&upriv->req_lock, flags);
		pr_warn("interrupt called with dead ctx\n");
		जाओ out;
	पूर्ण

	state = ctx->state;

	अगर (urb->status == 0) अणु
		चयन (state) अणु
		हाल EZUSB_CTX_REQ_SUBMITTED:
			अगर (ctx->in_rid) अणु
				ctx->state = EZUSB_CTX_REQ_COMPLETE;
				/* reply URB still pending */
				ezusb_mod_समयr(upriv, &ctx->समयr,
						jअगरfies + DEF_TIMEOUT);
				spin_unlock_irqrestore(&upriv->req_lock,
						       flags);
				अवरोध;
			पूर्ण
			fallthrough;
		हाल EZUSB_CTX_RESP_RECEIVED:
			/* IN alपढ़ोy received beक्रमe this OUT-ACK */
			ctx->state = EZUSB_CTX_COMPLETE;
			spin_unlock_irqrestore(&upriv->req_lock, flags);
			ezusb_ctx_complete(ctx);
			अवरोध;

		शेष:
			spin_unlock_irqrestore(&upriv->req_lock, flags);
			err("Unexpected state(0x%x, %d) in OUT URB",
			    state, urb->status);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* If someone cancels the OUT URB then its status
		 * should be either -ECONNRESET or -ENOENT.
		 */
		चयन (state) अणु
		हाल EZUSB_CTX_REQ_SUBMITTED:
		हाल EZUSB_CTX_RESP_RECEIVED:
			ctx->state = EZUSB_CTX_REQ_FAILED;
			fallthrough;

		हाल EZUSB_CTX_REQ_FAILED:
		हाल EZUSB_CTX_REQ_TIMEOUT:
			spin_unlock_irqrestore(&upriv->req_lock, flags);

			ezusb_ctx_complete(ctx);
			अवरोध;

		शेष:
			spin_unlock_irqrestore(&upriv->req_lock, flags);

			err("Unexpected state(0x%x, %d) in OUT URB",
			    state, urb->status);
			अवरोध;
		पूर्ण
	पूर्ण
 out:
	ezusb_request_context_put(ctx);
पूर्ण

अटल व्योम ezusb_request_in_callback(काष्ठा ezusb_priv *upriv,
				      काष्ठा urb *urb)
अणु
	काष्ठा ezusb_packet *ans = urb->transfer_buffer;
	काष्ठा request_context *ctx = शून्य;
	क्रमागत ezusb_state state;
	अचिन्हित दीर्घ flags;

	/* Find the CTX on the active queue that requested this URB */
	spin_lock_irqsave(&upriv->req_lock, flags);
	अगर (upriv->udev) अणु
		काष्ठा list_head *item;

		list_क्रम_each(item, &upriv->req_active) अणु
			काष्ठा request_context *c;
			पूर्णांक reply_count;

			c = list_entry(item, काष्ठा request_context, list);
			reply_count =
			    ezusb_reply_inc(c->buf->req_reply_count);
			अगर ((ans->ans_reply_count == reply_count)
			    && (le16_to_cpu(ans->hermes_rid) == c->in_rid)) अणु
				ctx = c;
				अवरोध;
			पूर्ण
			netdev_dbg(upriv->dev, "Skipped (0x%x/0x%x) (%d/%d)\n",
				   le16_to_cpu(ans->hermes_rid), c->in_rid,
				   ans->ans_reply_count, reply_count);
		पूर्ण
	पूर्ण

	अगर (ctx == शून्य) अणु
		spin_unlock_irqrestore(&upriv->req_lock, flags);
		err("%s: got unexpected RID: 0x%04X", __func__,
		    le16_to_cpu(ans->hermes_rid));
		ezusb_req_queue_run(upriv);
		वापस;
	पूर्ण

	/* The data we want is in the in buffer, exchange */
	urb->transfer_buffer = ctx->buf;
	ctx->buf = (व्योम *) ans;
	ctx->buf_length = urb->actual_length;

	state = ctx->state;
	चयन (state) अणु
	हाल EZUSB_CTX_REQ_SUBMITTED:
		/* We have received our response URB beक्रमe
		 * our request has been acknowledged. Do NOT
		 * destroy our CTX yet, because our OUT URB
		 * is still alive ...
		 */
		ctx->state = EZUSB_CTX_RESP_RECEIVED;
		spin_unlock_irqrestore(&upriv->req_lock, flags);

		/* Let the machine जारी running. */
		अवरोध;

	हाल EZUSB_CTX_REQ_COMPLETE:
		/* This is the usual path: our request
		 * has alपढ़ोy been acknowledged, and
		 * we have now received the reply.
		 */
		ctx->state = EZUSB_CTX_COMPLETE;

		/* Stop the पूर्णांकimer */
		del_समयr(&ctx->समयr);
		spin_unlock_irqrestore(&upriv->req_lock, flags);

		/* Call the completion handler */
		ezusb_ctx_complete(ctx);
		अवरोध;

	शेष:
		spin_unlock_irqrestore(&upriv->req_lock, flags);

		pr_warn("Matched IN URB, unexpected context state(0x%x)\n",
			state);
		/* Throw this CTX away and try submitting another */
		del_समयr(&ctx->समयr);
		ctx->outurb->transfer_flags |= URB_ASYNC_UNLINK;
		usb_unlink_urb(ctx->outurb);
		ezusb_req_queue_run(upriv);
		अवरोध;
	पूर्ण			/* चयन */
पूर्ण

प्रकार व्योम (*ezusb_ctx_रुको)(काष्ठा ezusb_priv *, काष्ठा request_context *);

अटल व्योम ezusb_req_ctx_रुको_compl(काष्ठा ezusb_priv *upriv,
				     काष्ठा request_context *ctx)
अणु
	चयन (ctx->state) अणु
	हाल EZUSB_CTX_QUEUED:
	हाल EZUSB_CTX_REQ_SUBMITTED:
	हाल EZUSB_CTX_REQ_COMPLETE:
	हाल EZUSB_CTX_RESP_RECEIVED:
		रुको_क्रम_completion(&ctx->करोne);
		अवरोध;
	शेष:
		/* Done or failed - nothing to रुको क्रम */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ezusb_req_ctx_रुको_poll(काष्ठा ezusb_priv *upriv,
				    काष्ठा request_context *ctx)
अणु
	पूर्णांक msecs;

	चयन (ctx->state) अणु
	हाल EZUSB_CTX_QUEUED:
	हाल EZUSB_CTX_REQ_SUBMITTED:
	हाल EZUSB_CTX_REQ_COMPLETE:
	हाल EZUSB_CTX_RESP_RECEIVED:
		/* If we get called from a समयr or with our lock acquired, then
		 * we can't wait for the completion and have to poll. This won't
		 * happen अगर the USB controller completes the URB requests in
		 * BH.
		 */
		msecs = DEF_TIMEOUT * (1000 / HZ);

		जबतक (!try_रुको_क्रम_completion(&ctx->करोne) && msecs--)
			udelay(1000);
		अवरोध;
	शेष:
		/* Done or failed - nothing to रुको क्रम */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ezusb_req_ctx_रुको_skip(काष्ठा ezusb_priv *upriv,
				    काष्ठा request_context *ctx)
अणु
	WARN(1, "Shouldn't be invoked for in_rid\n");
पूर्ण

अटल अंतरभूत u16 build_crc(काष्ठा ezusb_packet *data)
अणु
	u16 crc = 0;
	u8 *bytes = (u8 *)data;
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++)
		crc = (crc << 1) + bytes[i];

	वापस crc;
पूर्ण

/*
 * ezusb_fill_req:
 *
 * अगर data == शून्य and length > 0 the data is assumed to be alपढ़ोy in
 * the target buffer and only the header is filled.
 *
 */
अटल पूर्णांक ezusb_fill_req(काष्ठा ezusb_packet *req, u16 length, u16 rid,
			  स्थिर व्योम *data, u16 frame_type, u8 reply_count)
अणु
	पूर्णांक total_size = माप(*req) + length;

	BUG_ON(total_size > BULK_BUF_SIZE);

	req->magic = cpu_to_le16(EZUSB_MAGIC);
	req->req_reply_count = reply_count;
	req->ans_reply_count = 0;
	req->frame_type = cpu_to_le16(frame_type);
	req->size = cpu_to_le16(length + 4);
	req->crc = cpu_to_le16(build_crc(req));
	req->hermes_len = cpu_to_le16(HERMES_BYTES_TO_RECLEN(length));
	req->hermes_rid = cpu_to_le16(rid);
	अगर (data)
		स_नकल(req->data, data, length);
	वापस total_size;
पूर्ण

अटल पूर्णांक ezusb_submit_in_urb(काष्ठा ezusb_priv *upriv)
अणु
	पूर्णांक retval = 0;
	व्योम *cur_buf = upriv->पढ़ो_urb->transfer_buffer;

	अगर (upriv->पढ़ो_urb->status == -EINPROGRESS) अणु
		netdev_dbg(upriv->dev, "urb busy, not resubmiting\n");
		retval = -EBUSY;
		जाओ निकास;
	पूर्ण
	usb_fill_bulk_urb(upriv->पढ़ो_urb, upriv->udev, upriv->पढ़ो_pipe,
			  cur_buf, BULK_BUF_SIZE,
			  ezusb_bulk_in_callback, upriv);
	upriv->पढ़ो_urb->transfer_flags = 0;
	retval = usb_submit_urb(upriv->पढ़ो_urb, GFP_ATOMIC);
	अगर (retval)
		err("%s submit failed %d", __func__, retval);

 निकास:
	वापस retval;
पूर्ण

अटल अंतरभूत पूर्णांक ezusb_8051_cpucs(काष्ठा ezusb_priv *upriv, पूर्णांक reset)
अणु
	पूर्णांक ret;
	u8 *res_val = शून्य;

	अगर (!upriv->udev) अणु
		err("%s: !upriv->udev", __func__);
		वापस -EFAULT;
	पूर्ण

	res_val = kदो_स्मृति(माप(*res_val), GFP_KERNEL);

	अगर (!res_val)
		वापस -ENOMEM;

	*res_val = reset;	/* aव्योम argument promotion */

	ret =  usb_control_msg(upriv->udev,
			       usb_sndctrlpipe(upriv->udev, 0),
			       EZUSB_REQUEST_FW_TRANS,
			       USB_TYPE_VENDOR | USB_RECIP_DEVICE |
			       USB_सूची_OUT, EZUSB_CPUCS_REG, 0, res_val,
			       माप(*res_val), DEF_TIMEOUT);

	kमुक्त(res_val);

	वापस ret;
पूर्ण

अटल पूर्णांक ezusb_firmware_करोwnload(काष्ठा ezusb_priv *upriv,
				   काष्ठा ez_usb_fw *fw)
अणु
	u8 *fw_buffer;
	पूर्णांक retval, addr;
	पूर्णांक variant_offset;

	fw_buffer = kदो_स्मृति(FW_BUF_SIZE, GFP_KERNEL);
	अगर (!fw_buffer) अणु
		prपूर्णांकk(KERN_ERR PFX "Out of memory for firmware buffer.\n");
		वापस -ENOMEM;
	पूर्ण
	/*
	 * This byte is 1 and should be replaced with 0.  The offset is
	 * 0x10AD in version 0.0.6.  The byte in question should follow
	 * the end of the code poपूर्णांकed to by the jump in the beginning
	 * of the firmware.  Also, it is पढ़ो by code located at 0x358.
	 */
	variant_offset = be16_to_cpup((__be16 *) &fw->code[FW_VAR_OFFSET_PTR]);
	अगर (variant_offset >= fw->size) अणु
		prपूर्णांकk(KERN_ERR PFX "Invalid firmware variant offset: "
		       "0x%04x\n", variant_offset);
		retval = -EINVAL;
		जाओ fail;
	पूर्ण

	retval = ezusb_8051_cpucs(upriv, 1);
	अगर (retval < 0)
		जाओ fail;
	क्रम (addr = 0; addr < fw->size; addr += FW_BUF_SIZE) अणु
		/* 0x100-0x300 should be left alone, it contains card
		 * specअगरic data, like USB क्रमागतeration inक्रमmation */
		अगर ((addr >= FW_HOLE_START) && (addr < FW_HOLE_END))
			जारी;

		स_नकल(fw_buffer, &fw->code[addr], FW_BUF_SIZE);
		अगर (variant_offset >= addr &&
		    variant_offset < addr + FW_BUF_SIZE) अणु
			netdev_dbg(upriv->dev,
				   "Patching card_variant byte at 0x%04X\n",
				   variant_offset);
			fw_buffer[variant_offset - addr] = FW_VAR_VALUE;
		पूर्ण
		retval = usb_control_msg(upriv->udev,
					 usb_sndctrlpipe(upriv->udev, 0),
					 EZUSB_REQUEST_FW_TRANS,
					 USB_TYPE_VENDOR | USB_RECIP_DEVICE
					 | USB_सूची_OUT,
					 addr, 0x0,
					 fw_buffer, FW_BUF_SIZE,
					 DEF_TIMEOUT);

		अगर (retval < 0)
			जाओ fail;
	पूर्ण
	retval = ezusb_8051_cpucs(upriv, 0);
	अगर (retval < 0)
		जाओ fail;

	जाओ निकास;
 fail:
	prपूर्णांकk(KERN_ERR PFX "Firmware download failed, error %d\n",
	       retval);
 निकास:
	kमुक्त(fw_buffer);
	वापस retval;
पूर्ण

अटल पूर्णांक ezusb_access_ltv(काष्ठा ezusb_priv *upriv,
			    काष्ठा request_context *ctx,
			    u16 length, स्थिर व्योम *data, u16 frame_type,
			    व्योम *ans_buff, अचिन्हित ans_size, u16 *ans_length,
			    ezusb_ctx_रुको ezusb_ctx_रुको_func)
अणु
	पूर्णांक req_size;
	पूर्णांक retval = 0;
	क्रमागत ezusb_state state;

	अगर (!upriv->udev) अणु
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण

	अगर (upriv->पढ़ो_urb->status != -EINPROGRESS)
		err("%s: in urb not pending", __func__);

	/* protect upriv->reply_count, guarantee sequential numbers */
	spin_lock_bh(&upriv->reply_count_lock);
	req_size = ezusb_fill_req(ctx->buf, length, ctx->out_rid, data,
				  frame_type, upriv->reply_count);
	usb_fill_bulk_urb(ctx->outurb, upriv->udev, upriv->ग_लिखो_pipe,
			  ctx->buf, req_size,
			  ezusb_request_out_callback, ctx);

	अगर (ctx->in_rid)
		upriv->reply_count = ezusb_reply_inc(upriv->reply_count);

	ezusb_req_enqueue_run(upriv, ctx);

	spin_unlock_bh(&upriv->reply_count_lock);

	अगर (ctx->in_rid)
		ezusb_ctx_रुको_func(upriv, ctx);

	state = ctx->state;
	चयन (state) अणु
	हाल EZUSB_CTX_COMPLETE:
		retval = ctx->outurb->status;
		अवरोध;

	हाल EZUSB_CTX_QUEUED:
	हाल EZUSB_CTX_REQ_SUBMITTED:
		अगर (!ctx->in_rid)
			अवरोध;
		fallthrough;
	शेष:
		err("%s: Unexpected context state %d", __func__,
		    state);
		fallthrough;
	हाल EZUSB_CTX_REQ_TIMEOUT:
	हाल EZUSB_CTX_REQ_FAILED:
	हाल EZUSB_CTX_RESP_TIMEOUT:
	हाल EZUSB_CTX_REQSUBMIT_FAIL:
		prपूर्णांकk(KERN_ERR PFX "Access failed, resetting (state %d,"
		       " reply_count %d)\n", state, upriv->reply_count);
		upriv->reply_count = 0;
		अगर (state == EZUSB_CTX_REQ_TIMEOUT
		    || state == EZUSB_CTX_RESP_TIMEOUT) अणु
			prपूर्णांकk(KERN_ERR PFX "ctx timed out\n");
			retval = -ETIMEDOUT;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR PFX "ctx failed\n");
			retval = -EFAULT;
		पूर्ण
		जाओ निकास;
	पूर्ण
	अगर (ctx->in_rid) अणु
		काष्ठा ezusb_packet *ans = ctx->buf;
		अचिन्हित exp_len;

		अगर (ans->hermes_len != 0)
			exp_len = le16_to_cpu(ans->hermes_len) * 2 + 12;
		अन्यथा
			exp_len = 14;

		अगर (exp_len != ctx->buf_length) अणु
			err("%s: length mismatch for RID 0x%04x: "
			    "expected %d, got %d", __func__,
			    ctx->in_rid, exp_len, ctx->buf_length);
			retval = -EIO;
			जाओ निकास;
		पूर्ण

		अगर (ans_buff)
			स_नकल(ans_buff, ans->data, min(exp_len, ans_size));
		अगर (ans_length)
			*ans_length = le16_to_cpu(ans->hermes_len);
	पूर्ण
 निकास:
	ezusb_request_context_put(ctx);
	वापस retval;
पूर्ण

अटल पूर्णांक __ezusb_ग_लिखो_ltv(काष्ठा hermes *hw, पूर्णांक bap, u16 rid,
			   u16 length, स्थिर व्योम *data,
			   ezusb_ctx_रुको ezusb_ctx_रुको_func)
अणु
	काष्ठा ezusb_priv *upriv = hw->priv;
	u16 frame_type;
	काष्ठा request_context *ctx;

	अगर (length == 0)
		वापस -EINVAL;

	length = HERMES_RECLEN_TO_BYTES(length);

	/* On memory mapped devices HERMES_RID_CNFGROUPADDRESSES can be
	 * set to be empty, but the USB bridge करोesn't like it */
	अगर (length == 0)
		वापस 0;

	ctx = ezusb_alloc_ctx(upriv, rid, EZUSB_RID_ACK);
	अगर (!ctx)
		वापस -ENOMEM;

	अगर (rid == EZUSB_RID_TX)
		frame_type = EZUSB_FRAME_DATA;
	अन्यथा
		frame_type = EZUSB_FRAME_CONTROL;

	वापस ezusb_access_ltv(upriv, ctx, length, data, frame_type,
				शून्य, 0, शून्य, ezusb_ctx_रुको_func);
पूर्ण

अटल पूर्णांक ezusb_ग_लिखो_ltv(काष्ठा hermes *hw, पूर्णांक bap, u16 rid,
			   u16 length, स्थिर व्योम *data)
अणु
	वापस __ezusb_ग_लिखो_ltv(hw, bap, rid, length, data,
				 ezusb_req_ctx_रुको_poll);
पूर्ण

अटल पूर्णांक __ezusb_पढ़ो_ltv(काष्ठा hermes *hw, पूर्णांक bap, u16 rid,
			    अचिन्हित bufsize, u16 *length, व्योम *buf,
			    ezusb_ctx_रुको ezusb_ctx_रुको_func)

अणु
	काष्ठा ezusb_priv *upriv = hw->priv;
	काष्ठा request_context *ctx;

	अगर (bufsize % 2)
		वापस -EINVAL;

	ctx = ezusb_alloc_ctx(upriv, rid, rid);
	अगर (!ctx)
		वापस -ENOMEM;

	वापस ezusb_access_ltv(upriv, ctx, 0, शून्य, EZUSB_FRAME_CONTROL,
				buf, bufsize, length, ezusb_req_ctx_रुको_poll);
पूर्ण

अटल पूर्णांक ezusb_पढ़ो_ltv(काष्ठा hermes *hw, पूर्णांक bap, u16 rid,
			    अचिन्हित bufsize, u16 *length, व्योम *buf)
अणु
	वापस __ezusb_पढ़ो_ltv(hw, bap, rid, bufsize, length, buf,
				ezusb_req_ctx_रुको_poll);
पूर्ण

अटल पूर्णांक ezusb_पढ़ो_ltv_preempt(काष्ठा hermes *hw, पूर्णांक bap, u16 rid,
				  अचिन्हित bufsize, u16 *length, व्योम *buf)
अणु
	वापस __ezusb_पढ़ो_ltv(hw, bap, rid, bufsize, length, buf,
				ezusb_req_ctx_रुको_compl);
पूर्ण

अटल पूर्णांक ezusb_करोicmd_रुको(काष्ठा hermes *hw, u16 cmd, u16 parm0, u16 parm1,
			     u16 parm2, काष्ठा hermes_response *resp)
अणु
	WARN_ON_ONCE(1);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __ezusb_करोcmd_रुको(काष्ठा hermes *hw, u16 cmd, u16 parm0,
			    काष्ठा hermes_response *resp,
			    ezusb_ctx_रुको ezusb_ctx_रुको_func)
अणु
	काष्ठा ezusb_priv *upriv = hw->priv;
	काष्ठा request_context *ctx;

	__le16 data[4] = अणु
		cpu_to_le16(cmd),
		cpu_to_le16(parm0),
		0,
		0,
	पूर्ण;
	netdev_dbg(upriv->dev, "0x%04X, parm0 0x%04X\n", cmd, parm0);
	ctx = ezusb_alloc_ctx(upriv, EZUSB_RID_DOCMD, EZUSB_RID_ACK);
	अगर (!ctx)
		वापस -ENOMEM;

	वापस ezusb_access_ltv(upriv, ctx, माप(data), &data,
				EZUSB_FRAME_CONTROL, शून्य, 0, शून्य,
				ezusb_ctx_रुको_func);
पूर्ण

अटल पूर्णांक ezusb_करोcmd_रुको(काष्ठा hermes *hw, u16 cmd, u16 parm0,
			    काष्ठा hermes_response *resp)
अणु
	वापस __ezusb_करोcmd_रुको(hw, cmd, parm0, resp, ezusb_req_ctx_रुको_poll);
पूर्ण

अटल पूर्णांक ezusb_bap_pपढ़ो(काष्ठा hermes *hw, पूर्णांक bap,
			   व्योम *buf, पूर्णांक len, u16 id, u16 offset)
अणु
	काष्ठा ezusb_priv *upriv = hw->priv;
	काष्ठा ezusb_packet *ans = (व्योम *) upriv->पढ़ो_urb->transfer_buffer;
	पूर्णांक actual_length = upriv->पढ़ो_urb->actual_length;

	अगर (id == EZUSB_RID_RX) अणु
		अगर ((माप(*ans) + offset + len) > actual_length) अणु
			prपूर्णांकk(KERN_ERR PFX "BAP read beyond buffer end "
			       "in rx frame\n");
			वापस -EINVAL;
		पूर्ण
		स_नकल(buf, ans->data + offset, len);
		वापस 0;
	पूर्ण

	अगर (EZUSB_IS_INFO(id)) अणु
		/* Include 4 bytes क्रम length/type */
		अगर ((माप(*ans) + offset + len - 4) > actual_length) अणु
			prपूर्णांकk(KERN_ERR PFX "BAP read beyond buffer end "
			       "in info frame\n");
			वापस -EFAULT;
		पूर्ण
		स_नकल(buf, ans->data + offset - 4, len);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR PFX "Unexpected fid 0x%04x\n", id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ezusb_पढ़ो_pda(काष्ठा hermes *hw, __le16 *pda,
			  u32 pda_addr, u16 pda_len)
अणु
	काष्ठा ezusb_priv *upriv = hw->priv;
	काष्ठा request_context *ctx;
	__le16 data[] = अणु
		cpu_to_le16(pda_addr & 0xffff),
		cpu_to_le16(pda_len - 4)
	पूर्ण;
	ctx = ezusb_alloc_ctx(upriv, EZUSB_RID_READ_PDA, EZUSB_RID_READ_PDA);
	अगर (!ctx)
		वापस -ENOMEM;

	/* wl_lkm करोes not include PDA size in the PDA area.
	 * We will pad the inक्रमmation पूर्णांकo pda, so other routines
	 * करोn't have to be modअगरied */
	pda[0] = cpu_to_le16(pda_len - 2);
	/* Includes CFG_PROD_DATA but not itself */
	pda[1] = cpu_to_le16(0x0800); /* CFG_PROD_DATA */

	वापस ezusb_access_ltv(upriv, ctx, माप(data), &data,
				EZUSB_FRAME_CONTROL, &pda[2], pda_len - 4,
				शून्य, ezusb_req_ctx_रुको_compl);
पूर्ण

अटल पूर्णांक ezusb_program_init(काष्ठा hermes *hw, u32 entry_poपूर्णांक)
अणु
	काष्ठा ezusb_priv *upriv = hw->priv;
	काष्ठा request_context *ctx;
	__le32 data = cpu_to_le32(entry_poपूर्णांक);

	ctx = ezusb_alloc_ctx(upriv, EZUSB_RID_PROG_INIT, EZUSB_RID_ACK);
	अगर (!ctx)
		वापस -ENOMEM;

	वापस ezusb_access_ltv(upriv, ctx, माप(data), &data,
				EZUSB_FRAME_CONTROL, शून्य, 0, शून्य,
				ezusb_req_ctx_रुको_compl);
पूर्ण

अटल पूर्णांक ezusb_program_end(काष्ठा hermes *hw)
अणु
	काष्ठा ezusb_priv *upriv = hw->priv;
	काष्ठा request_context *ctx;

	ctx = ezusb_alloc_ctx(upriv, EZUSB_RID_PROG_END, EZUSB_RID_ACK);
	अगर (!ctx)
		वापस -ENOMEM;

	वापस ezusb_access_ltv(upriv, ctx, 0, शून्य,
				EZUSB_FRAME_CONTROL, शून्य, 0, शून्य,
				ezusb_req_ctx_रुको_compl);
पूर्ण

अटल पूर्णांक ezusb_program_bytes(काष्ठा hermes *hw, स्थिर अक्षर *buf,
			       u32 addr, u32 len)
अणु
	काष्ठा ezusb_priv *upriv = hw->priv;
	काष्ठा request_context *ctx;
	__le32 data = cpu_to_le32(addr);
	पूर्णांक err;

	ctx = ezusb_alloc_ctx(upriv, EZUSB_RID_PROG_SET_ADDR, EZUSB_RID_ACK);
	अगर (!ctx)
		वापस -ENOMEM;

	err = ezusb_access_ltv(upriv, ctx, माप(data), &data,
			       EZUSB_FRAME_CONTROL, शून्य, 0, शून्य,
			       ezusb_req_ctx_रुको_compl);
	अगर (err)
		वापस err;

	ctx = ezusb_alloc_ctx(upriv, EZUSB_RID_PROG_BYTES, EZUSB_RID_ACK);
	अगर (!ctx)
		वापस -ENOMEM;

	वापस ezusb_access_ltv(upriv, ctx, len, buf,
				EZUSB_FRAME_CONTROL, शून्य, 0, शून्य,
				ezusb_req_ctx_रुको_compl);
पूर्ण

अटल पूर्णांक ezusb_program(काष्ठा hermes *hw, स्थिर अक्षर *buf,
			 u32 addr, u32 len)
अणु
	u32 ch_addr;
	u32 ch_len;
	पूर्णांक err = 0;

	/* We can only send 2048 bytes out of the bulk xmit at a समय,
	 * so we have to split any programming पूर्णांकo chunks of <2048
	 * bytes. */

	ch_len = (len < MAX_DL_SIZE) ? len : MAX_DL_SIZE;
	ch_addr = addr;

	जबतक (ch_addr < (addr + len)) अणु
		pr_debug("Programming subblock of length %d "
			 "to address 0x%08x. Data @ %p\n",
			 ch_len, ch_addr, &buf[ch_addr - addr]);

		err = ezusb_program_bytes(hw, &buf[ch_addr - addr],
					  ch_addr, ch_len);
		अगर (err)
			अवरोध;

		ch_addr += ch_len;
		ch_len = ((addr + len - ch_addr) < MAX_DL_SIZE) ?
			(addr + len - ch_addr) : MAX_DL_SIZE;
	पूर्ण

	वापस err;
पूर्ण

अटल netdev_tx_t ezusb_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा ezusb_priv *upriv = priv->card;
	u8 mic[MICHAEL_MIC_LEN + 1];
	पूर्णांक err = 0;
	पूर्णांक tx_control;
	अचिन्हित दीर्घ flags;
	काष्ठा request_context *ctx;
	u8 *buf;
	पूर्णांक tx_size;

	अगर (!netअगर_running(dev)) अणु
		prपूर्णांकk(KERN_ERR "%s: Tx on stopped device!\n",
		       dev->name);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (netअगर_queue_stopped(dev)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: Tx while transmitter busy!\n",
		       dev->name);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (orinoco_lock(priv, &flags) != 0) अणु
		prपूर्णांकk(KERN_ERR
		       "%s: ezusb_xmit() called while hw_unavailable\n",
		       dev->name);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (!netअगर_carrier_ok(dev) ||
	    (priv->iw_mode == NL80211_IFTYPE_MONITOR)) अणु
		/* Oops, the firmware hasn't established a connection,
		   silently drop the packet (this seems to be the
		   safest approach). */
		जाओ drop;
	पूर्ण

	/* Check packet length */
	अगर (skb->len < ETH_HLEN)
		जाओ drop;

	tx_control = 0;

	err = orinoco_process_xmit_skb(skb, dev, priv, &tx_control,
				       &mic[0]);
	अगर (err)
		जाओ drop;

	ctx = ezusb_alloc_ctx(upriv, EZUSB_RID_TX, 0);
	अगर (!ctx)
		जाओ drop;

	स_रखो(ctx->buf, 0, BULK_BUF_SIZE);
	buf = ctx->buf->data;

	अणु
		__le16 *tx_cntl = (__le16 *)buf;
		*tx_cntl = cpu_to_le16(tx_control);
		buf += माप(*tx_cntl);
	पूर्ण

	स_नकल(buf, skb->data, skb->len);
	buf += skb->len;

	अगर (tx_control & HERMES_TXCTRL_MIC) अणु
		u8 *m = mic;
		/* Mic has been offset so it can be copied to an even
		 * address. We're copying eveything anyway, so we
		 * करोn't need to copy that first byte. */
		अगर (skb->len % 2)
			m++;
		स_नकल(buf, m, MICHAEL_MIC_LEN);
		buf += MICHAEL_MIC_LEN;
	पूर्ण

	/* Finally, we actually initiate the send */
	netअगर_stop_queue(dev);

	/* The card may behave better अगर we send evenly sized usb transfers */
	tx_size = ALIGN(buf - ctx->buf->data, 2);

	err = ezusb_access_ltv(upriv, ctx, tx_size, शून्य,
			       EZUSB_FRAME_DATA, शून्य, 0, शून्य,
			       ezusb_req_ctx_रुको_skip);

	अगर (err) अणु
		netअगर_start_queue(dev);
		अगर (net_ratelimit())
			prपूर्णांकk(KERN_ERR "%s: Error %d transmitting packet\n",
				dev->name, err);
		जाओ busy;
	पूर्ण

	netअगर_trans_update(dev);
	stats->tx_bytes += skb->len;
	जाओ ok;

 drop:
	stats->tx_errors++;
	stats->tx_dropped++;

 ok:
	orinoco_unlock(priv, &flags);
	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;

 busy:
	orinoco_unlock(priv, &flags);
	वापस NETDEV_TX_BUSY;
पूर्ण

अटल पूर्णांक ezusb_allocate(काष्ठा hermes *hw, u16 size, u16 *fid)
अणु
	*fid = EZUSB_RID_TX;
	वापस 0;
पूर्ण


अटल पूर्णांक ezusb_hard_reset(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा ezusb_priv *upriv = priv->card;
	पूर्णांक retval = ezusb_8051_cpucs(upriv, 1);

	अगर (retval < 0) अणु
		err("Failed to reset");
		वापस retval;
	पूर्ण

	retval = ezusb_8051_cpucs(upriv, 0);
	अगर (retval < 0) अणु
		err("Failed to unreset");
		वापस retval;
	पूर्ण

	netdev_dbg(upriv->dev, "sending control message\n");
	retval = usb_control_msg(upriv->udev,
				 usb_sndctrlpipe(upriv->udev, 0),
				 EZUSB_REQUEST_TRIGGER,
				 USB_TYPE_VENDOR | USB_RECIP_DEVICE |
				 USB_सूची_OUT, 0x0, 0x0, शून्य, 0,
				 DEF_TIMEOUT);
	अगर (retval < 0) अणु
		err("EZUSB_REQUEST_TRIGGER failed retval %d", retval);
		वापस retval;
	पूर्ण
#अगर 0
	dbg("Sending EZUSB_REQUEST_TRIG_AC");
	retval = usb_control_msg(upriv->udev,
				 usb_sndctrlpipe(upriv->udev, 0),
				 EZUSB_REQUEST_TRIG_AC,
				 USB_TYPE_VENDOR | USB_RECIP_DEVICE |
				 USB_सूची_OUT, 0x00FA, 0x0, शून्य, 0,
				 DEF_TIMEOUT);
	अगर (retval < 0) अणु
		err("EZUSB_REQUEST_TRIG_AC failed retval %d", retval);
		वापस retval;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण


अटल पूर्णांक ezusb_init(काष्ठा hermes *hw)
अणु
	काष्ठा ezusb_priv *upriv = hw->priv;
	पूर्णांक retval;

	अगर (!upriv)
		वापस -EINVAL;

	upriv->reply_count = 0;
	/* Write the MAGIC number on the simulated रेजिस्टरs to keep
	 * orinoco.c happy */
	hermes_ग_लिखो_regn(hw, SWSUPPORT0, HERMES_MAGIC);
	hermes_ग_लिखो_regn(hw, RXFID, EZUSB_RID_RX);

	usb_समाप्त_urb(upriv->पढ़ो_urb);
	ezusb_submit_in_urb(upriv);

	retval = __ezusb_ग_लिखो_ltv(hw, 0, EZUSB_RID_INIT1,
				 HERMES_BYTES_TO_RECLEN(2), "\x10\x00",
				 ezusb_req_ctx_रुको_compl);
	अगर (retval < 0) अणु
		prपूर्णांकk(KERN_ERR PFX "EZUSB_RID_INIT1 error %d\n", retval);
		वापस retval;
	पूर्ण

	retval = __ezusb_करोcmd_रुको(hw, HERMES_CMD_INIT, 0, शून्य,
				    ezusb_req_ctx_रुको_compl);
	अगर (retval < 0) अणु
		prपूर्णांकk(KERN_ERR PFX "HERMES_CMD_INIT error %d\n", retval);
		वापस retval;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ezusb_bulk_in_callback(काष्ठा urb *urb)
अणु
	काष्ठा ezusb_priv *upriv = (काष्ठा ezusb_priv *) urb->context;
	काष्ठा ezusb_packet *ans = urb->transfer_buffer;
	u16 crc;
	u16 hermes_rid;

	अगर (upriv->udev == शून्य)
		वापस;

	अगर (urb->status == -ETIMEDOUT) अणु
		/* When a device माला_लो unplugged we get this every समय
		 * we resubmit, flooding the logs.  Since we करोn't use
		 * USB समयouts, it shouldn't happen any other समय*/
		pr_warn("%s: urb timed out, not resubmitting\n", __func__);
		वापस;
	पूर्ण
	अगर (urb->status == -ECONNABORTED) अणु
		pr_warn("%s: connection abort, resubmitting urb\n",
			__func__);
		जाओ resubmit;
	पूर्ण
	अगर ((urb->status == -EILSEQ)
	    || (urb->status == -ENOENT)
	    || (urb->status == -ECONNRESET)) अणु
		netdev_dbg(upriv->dev, "status %d, not resubmiting\n",
			   urb->status);
		वापस;
	पूर्ण
	अगर (urb->status)
		netdev_dbg(upriv->dev, "status: %d length: %d\n",
			   urb->status, urb->actual_length);
	अगर (urb->actual_length < माप(*ans)) अणु
		err("%s: short read, ignoring", __func__);
		जाओ resubmit;
	पूर्ण
	crc = build_crc(ans);
	अगर (le16_to_cpu(ans->crc) != crc) अणु
		err("CRC error, ignoring packet");
		जाओ resubmit;
	पूर्ण

	hermes_rid = le16_to_cpu(ans->hermes_rid);
	अगर ((hermes_rid != EZUSB_RID_RX) && !EZUSB_IS_INFO(hermes_rid)) अणु
		ezusb_request_in_callback(upriv, urb);
	पूर्ण अन्यथा अगर (upriv->dev) अणु
		काष्ठा net_device *dev = upriv->dev;
		काष्ठा orinoco_निजी *priv = ndev_priv(dev);
		काष्ठा hermes *hw = &priv->hw;

		अगर (hermes_rid == EZUSB_RID_RX) अणु
			__orinoco_ev_rx(dev, hw);
		पूर्ण अन्यथा अणु
			hermes_ग_लिखो_regn(hw, INFOFID,
					  le16_to_cpu(ans->hermes_rid));
			__orinoco_ev_info(dev, hw);
		पूर्ण
	पूर्ण

 resubmit:
	अगर (upriv->udev)
		ezusb_submit_in_urb(upriv);
पूर्ण

अटल अंतरभूत व्योम ezusb_delete(काष्ठा ezusb_priv *upriv)
अणु
	काष्ठा list_head *item;
	काष्ठा list_head *पंचांगp_item;
	अचिन्हित दीर्घ flags;

	BUG_ON(!upriv);

	mutex_lock(&upriv->mtx);

	upriv->udev = शून्य;	/* No समयr will be rearmed from here */

	usb_समाप्त_urb(upriv->पढ़ो_urb);

	spin_lock_irqsave(&upriv->req_lock, flags);
	list_क्रम_each_safe(item, पंचांगp_item, &upriv->req_active) अणु
		काष्ठा request_context *ctx;
		पूर्णांक err;

		ctx = list_entry(item, काष्ठा request_context, list);
		refcount_inc(&ctx->refcount);

		ctx->outurb->transfer_flags |= URB_ASYNC_UNLINK;
		err = usb_unlink_urb(ctx->outurb);

		spin_unlock_irqrestore(&upriv->req_lock, flags);
		अगर (err == -EINPROGRESS)
			रुको_क्रम_completion(&ctx->करोne);

		del_समयr_sync(&ctx->समयr);
		/* FIXME: there is an slight chance क्रम the irq handler to
		 * be running */
		अगर (!list_empty(&ctx->list))
			ezusb_ctx_complete(ctx);

		ezusb_request_context_put(ctx);
		spin_lock_irqsave(&upriv->req_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&upriv->req_lock, flags);

	list_क्रम_each_safe(item, पंचांगp_item, &upriv->req_pending)
	    ezusb_ctx_complete(list_entry(item,
					  काष्ठा request_context, list));

	अगर (upriv->पढ़ो_urb && upriv->पढ़ो_urb->status == -EINPROGRESS)
		prपूर्णांकk(KERN_ERR PFX "Some URB in progress\n");

	mutex_unlock(&upriv->mtx);

	अगर (upriv->पढ़ो_urb) अणु
		kमुक्त(upriv->पढ़ो_urb->transfer_buffer);
		usb_मुक्त_urb(upriv->पढ़ो_urb);
	पूर्ण
	kमुक्त(upriv->bap_buf);
	अगर (upriv->dev) अणु
		काष्ठा orinoco_निजी *priv = ndev_priv(upriv->dev);
		orinoco_अगर_del(priv);
		wiphy_unरेजिस्टर(priv_to_wiphy(upriv));
		मुक्त_orinocodev(priv);
	पूर्ण
पूर्ण

अटल व्योम ezusb_lock_irqsave(spinlock_t *lock,
			       अचिन्हित दीर्घ *flags) __acquires(lock)
अणु
	spin_lock_bh(lock);
पूर्ण

अटल व्योम ezusb_unlock_irqrestore(spinlock_t *lock,
				    अचिन्हित दीर्घ *flags) __releases(lock)
अणु
	spin_unlock_bh(lock);
पूर्ण

अटल व्योम ezusb_lock_irq(spinlock_t *lock) __acquires(lock)
अणु
	spin_lock_bh(lock);
पूर्ण

अटल व्योम ezusb_unlock_irq(spinlock_t *lock) __releases(lock)
अणु
	spin_unlock_bh(lock);
पूर्ण

अटल स्थिर काष्ठा hermes_ops ezusb_ops = अणु
	.init = ezusb_init,
	.cmd_रुको = ezusb_करोcmd_रुको,
	.init_cmd_रुको = ezusb_करोicmd_रुको,
	.allocate = ezusb_allocate,
	.पढ़ो_ltv = ezusb_पढ़ो_ltv,
	.पढ़ो_ltv_pr = ezusb_पढ़ो_ltv_preempt,
	.ग_लिखो_ltv = ezusb_ग_लिखो_ltv,
	.bap_pपढ़ो = ezusb_bap_pपढ़ो,
	.पढ़ो_pda = ezusb_पढ़ो_pda,
	.program_init = ezusb_program_init,
	.program_end = ezusb_program_end,
	.program = ezusb_program,
	.lock_irqsave = ezusb_lock_irqsave,
	.unlock_irqrestore = ezusb_unlock_irqrestore,
	.lock_irq = ezusb_lock_irq,
	.unlock_irq = ezusb_unlock_irq,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops ezusb_netdev_ops = अणु
	.nकरो_खोलो		= orinoco_खोलो,
	.nकरो_stop		= orinoco_stop,
	.nकरो_start_xmit		= ezusb_xmit,
	.nकरो_set_rx_mode	= orinoco_set_multicast_list,
	.nकरो_change_mtu		= orinoco_change_mtu,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_tx_समयout		= orinoco_tx_समयout,
पूर्ण;

अटल पूर्णांक ezusb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		       स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा orinoco_निजी *priv;
	काष्ठा hermes *hw;
	काष्ठा ezusb_priv *upriv = शून्य;
	काष्ठा usb_पूर्णांकerface_descriptor *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep;
	स्थिर काष्ठा firmware *fw_entry = शून्य;
	पूर्णांक retval = 0;
	पूर्णांक i;

	priv = alloc_orinocodev(माप(*upriv), &udev->dev,
				ezusb_hard_reset, शून्य);
	अगर (!priv) अणु
		err("Couldn't allocate orinocodev");
		retval = -ENOMEM;
		जाओ निकास;
	पूर्ण

	hw = &priv->hw;

	upriv = priv->card;

	mutex_init(&upriv->mtx);
	spin_lock_init(&upriv->reply_count_lock);

	spin_lock_init(&upriv->req_lock);
	INIT_LIST_HEAD(&upriv->req_pending);
	INIT_LIST_HEAD(&upriv->req_active);

	upriv->udev = udev;

	hw->iobase = (व्योम __क्रमce __iomem *) &upriv->hermes_reg_fake;
	hw->reg_spacing = HERMES_16BIT_REGSPACING;
	hw->priv = upriv;
	hw->ops = &ezusb_ops;

	/* set up the endpoपूर्णांक inक्रमmation */
	/* check out the endpoपूर्णांकs */

	अगरace_desc = &पूर्णांकerface->cur_altsetting->desc;
	क्रम (i = 0; i < अगरace_desc->bNumEndpoपूर्णांकs; ++i) अणु
		ep = &पूर्णांकerface->cur_altsetting->endpoपूर्णांक[i].desc;

		अगर (usb_endpoपूर्णांक_is_bulk_in(ep)) अणु
			/* we found a bulk in endpoपूर्णांक */
			अगर (upriv->पढ़ो_urb != शून्य) अणु
				pr_warn("Found a second bulk in ep, ignored\n");
				जारी;
			पूर्ण

			upriv->पढ़ो_urb = usb_alloc_urb(0, GFP_KERNEL);
			अगर (!upriv->पढ़ो_urb)
				जाओ error;
			अगर (le16_to_cpu(ep->wMaxPacketSize) != 64)
				pr_warn("bulk in: wMaxPacketSize!= 64\n");
			अगर (ep->bEndpoपूर्णांकAddress != (2 | USB_सूची_IN))
				pr_warn("bulk in: bEndpointAddress: %d\n",
					ep->bEndpoपूर्णांकAddress);
			upriv->पढ़ो_pipe = usb_rcvbulkpipe(udev,
							 ep->
							 bEndpoपूर्णांकAddress);
			upriv->पढ़ो_urb->transfer_buffer =
			    kदो_स्मृति(BULK_BUF_SIZE, GFP_KERNEL);
			अगर (!upriv->पढ़ो_urb->transfer_buffer) अणु
				err("Couldn't allocate IN buffer");
				जाओ error;
			पूर्ण
		पूर्ण

		अगर (usb_endpoपूर्णांक_is_bulk_out(ep)) अणु
			/* we found a bulk out endpoपूर्णांक */
			अगर (upriv->bap_buf != शून्य) अणु
				pr_warn("Found a second bulk out ep, ignored\n");
				जारी;
			पूर्ण

			अगर (le16_to_cpu(ep->wMaxPacketSize) != 64)
				pr_warn("bulk out: wMaxPacketSize != 64\n");
			अगर (ep->bEndpoपूर्णांकAddress != 2)
				pr_warn("bulk out: bEndpointAddress: %d\n",
					ep->bEndpoपूर्णांकAddress);
			upriv->ग_लिखो_pipe = usb_sndbulkpipe(udev,
							  ep->
							  bEndpoपूर्णांकAddress);
			upriv->bap_buf = kदो_स्मृति(BULK_BUF_SIZE, GFP_KERNEL);
			अगर (!upriv->bap_buf) अणु
				err("Couldn't allocate bulk_out_buffer");
				जाओ error;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!upriv->bap_buf || !upriv->पढ़ो_urb) अणु
		err("Didn't find the required bulk endpoints");
		जाओ error;
	पूर्ण

	अगर (request_firmware(&fw_entry, "orinoco_ezusb_fw",
			     &पूर्णांकerface->dev) == 0) अणु
		firmware.size = fw_entry->size;
		firmware.code = fw_entry->data;
	पूर्ण
	अगर (firmware.size && firmware.code) अणु
		अगर (ezusb_firmware_करोwnload(upriv, &firmware) < 0)
			जाओ error;
	पूर्ण अन्यथा अणु
		err("No firmware to download");
		जाओ error;
	पूर्ण

	अगर (ezusb_hard_reset(priv) < 0) अणु
		err("Cannot reset the device");
		जाओ error;
	पूर्ण

	/* If the firmware is alपढ़ोy करोwnloaded orinoco.c will call
	 * ezusb_init but अगर the firmware is not alपढ़ोy there, that will make
	 * the kernel very unstable, so we try initializing here and quit in
	 * हाल of error */
	अगर (ezusb_init(hw) < 0) अणु
		err("Couldn't initialize the device");
		err("Firmware may not be downloaded or may be wrong.");
		जाओ error;
	पूर्ण

	/* Initialise the मुख्य driver */
	अगर (orinoco_init(priv) != 0) अणु
		err("orinoco_init() failed\n");
		जाओ error;
	पूर्ण

	अगर (orinoco_अगर_add(priv, 0, 0, &ezusb_netdev_ops) != 0) अणु
		upriv->dev = शून्य;
		err("%s: orinoco_if_add() failed", __func__);
		wiphy_unरेजिस्टर(priv_to_wiphy(priv));
		जाओ error;
	पूर्ण
	upriv->dev = priv->ndev;

	जाओ निकास;

 error:
	ezusb_delete(upriv);
	अगर (upriv->dev) अणु
		/* upriv->dev was 0, so ezusb_delete() didn't मुक्त it */
		मुक्त_orinocodev(priv);
	पूर्ण
	upriv = शून्य;
	retval = -EFAULT;
 निकास:
	अगर (fw_entry) अणु
		firmware.code = शून्य;
		firmware.size = 0;
		release_firmware(fw_entry);
	पूर्ण
	usb_set_पूर्णांकfdata(पूर्णांकerface, upriv);
	वापस retval;
पूर्ण


अटल व्योम ezusb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ezusb_priv *upriv = usb_get_पूर्णांकfdata(पूर्णांकf);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	ezusb_delete(upriv);
	prपूर्णांकk(KERN_INFO PFX "Disconnected\n");
पूर्ण


/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver orinoco_driver = अणु
	.name = DRIVER_NAME,
	.probe = ezusb_probe,
	.disconnect = ezusb_disconnect,
	.id_table = ezusb_table,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(orinoco_driver);

MODULE_AUTHOR("Manuel Estrada Sainz");
MODULE_DESCRIPTION("Driver for Orinoco wireless LAN cards using EZUSB bridge");
MODULE_LICENSE("Dual MPL/GPL");
