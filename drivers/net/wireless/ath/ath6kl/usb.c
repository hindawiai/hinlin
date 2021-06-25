<शैली गुरु>
/*
 * Copyright (c) 2007-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2012 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/module.h>
#समावेश <linux/usb.h>

#समावेश "debug.h"
#समावेश "core.h"

/* स्थिरants */
#घोषणा TX_URB_COUNT            32
#घोषणा RX_URB_COUNT            32
#घोषणा ATH6KL_USB_RX_BUFFER_SIZE  4096

/* tx/rx pipes क्रम usb */
क्रमागत ATH6KL_USB_PIPE_ID अणु
	ATH6KL_USB_PIPE_TX_CTRL = 0,
	ATH6KL_USB_PIPE_TX_DATA_LP,
	ATH6KL_USB_PIPE_TX_DATA_MP,
	ATH6KL_USB_PIPE_TX_DATA_HP,
	ATH6KL_USB_PIPE_RX_CTRL,
	ATH6KL_USB_PIPE_RX_DATA,
	ATH6KL_USB_PIPE_RX_DATA2,
	ATH6KL_USB_PIPE_RX_INT,
	ATH6KL_USB_PIPE_MAX
पूर्ण;

#घोषणा ATH6KL_USB_PIPE_INVALID ATH6KL_USB_PIPE_MAX

काष्ठा ath6kl_usb_pipe अणु
	काष्ठा list_head urb_list_head;
	काष्ठा usb_anchor urb_submitted;
	u32 urb_alloc;
	u32 urb_cnt;
	u32 urb_cnt_thresh;
	अचिन्हित पूर्णांक usb_pipe_handle;
	u32 flags;
	u8 ep_address;
	u8 logical_pipe_num;
	काष्ठा ath6kl_usb *ar_usb;
	u16 max_packet_size;
	काष्ठा work_काष्ठा io_complete_work;
	काष्ठा sk_buff_head io_comp_queue;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_desc;
पूर्ण;

#घोषणा ATH6KL_USB_PIPE_FLAG_TX    (1 << 0)

/* usb device object */
काष्ठा ath6kl_usb अणु
	/* protects pipe->urb_list_head and  pipe->urb_cnt */
	spinlock_t cs_lock;

	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	काष्ठा ath6kl_usb_pipe pipes[ATH6KL_USB_PIPE_MAX];
	u8 *diag_cmd_buffer;
	u8 *diag_resp_buffer;
	काष्ठा ath6kl *ar;
पूर्ण;

/* usb urb object */
काष्ठा ath6kl_urb_context अणु
	काष्ठा list_head link;
	काष्ठा ath6kl_usb_pipe *pipe;
	काष्ठा sk_buff *skb;
	काष्ठा ath6kl *ar;
पूर्ण;

/* USB endpoपूर्णांक definitions */
#घोषणा ATH6KL_USB_EP_ADDR_APP_CTRL_IN          0x81
#घोषणा ATH6KL_USB_EP_ADDR_APP_DATA_IN          0x82
#घोषणा ATH6KL_USB_EP_ADDR_APP_DATA2_IN         0x83
#घोषणा ATH6KL_USB_EP_ADDR_APP_INT_IN           0x84

#घोषणा ATH6KL_USB_EP_ADDR_APP_CTRL_OUT         0x01
#घोषणा ATH6KL_USB_EP_ADDR_APP_DATA_LP_OUT      0x02
#घोषणा ATH6KL_USB_EP_ADDR_APP_DATA_MP_OUT      0x03
#घोषणा ATH6KL_USB_EP_ADDR_APP_DATA_HP_OUT      0x04

/* diagnostic command defnitions */
#घोषणा ATH6KL_USB_CONTROL_REQ_SEND_BMI_CMD        1
#घोषणा ATH6KL_USB_CONTROL_REQ_RECV_BMI_RESP       2
#घोषणा ATH6KL_USB_CONTROL_REQ_DIAG_CMD            3
#घोषणा ATH6KL_USB_CONTROL_REQ_DIAG_RESP           4

#घोषणा ATH6KL_USB_CTRL_DIAG_CC_READ               0
#घोषणा ATH6KL_USB_CTRL_DIAG_CC_WRITE              1

काष्ठा ath6kl_usb_ctrl_diag_cmd_ग_लिखो अणु
	__le32 cmd;
	__le32 address;
	__le32 value;
	__le32 _pad[1];
पूर्ण __packed;

काष्ठा ath6kl_usb_ctrl_diag_cmd_पढ़ो अणु
	__le32 cmd;
	__le32 address;
पूर्ण __packed;

काष्ठा ath6kl_usb_ctrl_diag_resp_पढ़ो अणु
	__le32 value;
पूर्ण __packed;

/* function declarations */
अटल व्योम ath6kl_usb_recv_complete(काष्ठा urb *urb);

#घोषणा ATH6KL_USB_IS_BULK_EP(attr) (((attr) & 3) == 0x02)
#घोषणा ATH6KL_USB_IS_INT_EP(attr)  (((attr) & 3) == 0x03)
#घोषणा ATH6KL_USB_IS_ISOC_EP(attr)  (((attr) & 3) == 0x01)
#घोषणा ATH6KL_USB_IS_सूची_IN(addr)  ((addr) & 0x80)

/* pipe/urb operations */
अटल काष्ठा ath6kl_urb_context *
ath6kl_usb_alloc_urb_from_pipe(काष्ठा ath6kl_usb_pipe *pipe)
अणु
	काष्ठा ath6kl_urb_context *urb_context = शून्य;
	अचिन्हित दीर्घ flags;

	/* bail अगर this pipe is not initialized */
	अगर (!pipe->ar_usb)
		वापस शून्य;

	spin_lock_irqsave(&pipe->ar_usb->cs_lock, flags);
	अगर (!list_empty(&pipe->urb_list_head)) अणु
		urb_context =
		    list_first_entry(&pipe->urb_list_head,
				     काष्ठा ath6kl_urb_context, link);
		list_del(&urb_context->link);
		pipe->urb_cnt--;
	पूर्ण
	spin_unlock_irqrestore(&pipe->ar_usb->cs_lock, flags);

	वापस urb_context;
पूर्ण

अटल व्योम ath6kl_usb_मुक्त_urb_to_pipe(काष्ठा ath6kl_usb_pipe *pipe,
					काष्ठा ath6kl_urb_context *urb_context)
अणु
	अचिन्हित दीर्घ flags;

	/* bail अगर this pipe is not initialized */
	अगर (!pipe->ar_usb)
		वापस;

	spin_lock_irqsave(&pipe->ar_usb->cs_lock, flags);
	pipe->urb_cnt++;

	list_add(&urb_context->link, &pipe->urb_list_head);
	spin_unlock_irqrestore(&pipe->ar_usb->cs_lock, flags);
पूर्ण

अटल व्योम ath6kl_usb_cleanup_recv_urb(काष्ठा ath6kl_urb_context *urb_context)
अणु
	dev_kमुक्त_skb(urb_context->skb);
	urb_context->skb = शून्य;

	ath6kl_usb_मुक्त_urb_to_pipe(urb_context->pipe, urb_context);
पूर्ण

अटल अंतरभूत काष्ठा ath6kl_usb *ath6kl_usb_priv(काष्ठा ath6kl *ar)
अणु
	वापस ar->hअगर_priv;
पूर्ण

/* pipe resource allocation/cleanup */
अटल पूर्णांक ath6kl_usb_alloc_pipe_resources(काष्ठा ath6kl_usb_pipe *pipe,
					   पूर्णांक urb_cnt)
अणु
	काष्ठा ath6kl_urb_context *urb_context;
	पूर्णांक status = 0, i;

	INIT_LIST_HEAD(&pipe->urb_list_head);
	init_usb_anchor(&pipe->urb_submitted);

	क्रम (i = 0; i < urb_cnt; i++) अणु
		urb_context = kzalloc(माप(काष्ठा ath6kl_urb_context),
				      GFP_KERNEL);
		अगर (urb_context == शून्य) अणु
			status = -ENOMEM;
			जाओ fail_alloc_pipe_resources;
		पूर्ण

		urb_context->pipe = pipe;

		/*
		 * we are only allocate the urb contexts here, the actual URB
		 * is allocated from the kernel as needed to करो a transaction
		 */
		pipe->urb_alloc++;
		ath6kl_usb_मुक्त_urb_to_pipe(pipe, urb_context);
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_USB,
		   "ath6kl usb: alloc resources lpipe:%d hpipe:0x%X urbs:%d\n",
		   pipe->logical_pipe_num, pipe->usb_pipe_handle,
		   pipe->urb_alloc);

fail_alloc_pipe_resources:
	वापस status;
पूर्ण

अटल व्योम ath6kl_usb_मुक्त_pipe_resources(काष्ठा ath6kl_usb_pipe *pipe)
अणु
	काष्ठा ath6kl_urb_context *urb_context;

	अगर (pipe->ar_usb == शून्य) अणु
		/* nothing allocated क्रम this pipe */
		वापस;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_USB,
		   "ath6kl usb: free resources lpipe:%d"
		   "hpipe:0x%X urbs:%d avail:%d\n",
		   pipe->logical_pipe_num, pipe->usb_pipe_handle,
		   pipe->urb_alloc, pipe->urb_cnt);

	अगर (pipe->urb_alloc != pipe->urb_cnt) अणु
		ath6kl_dbg(ATH6KL_DBG_USB,
			   "ath6kl usb: urb leak! lpipe:%d"
			   "hpipe:0x%X urbs:%d avail:%d\n",
			   pipe->logical_pipe_num, pipe->usb_pipe_handle,
			   pipe->urb_alloc, pipe->urb_cnt);
	पूर्ण

	जबतक (true) अणु
		urb_context = ath6kl_usb_alloc_urb_from_pipe(pipe);
		अगर (urb_context == शून्य)
			अवरोध;
		kमुक्त(urb_context);
	पूर्ण
पूर्ण

अटल व्योम ath6kl_usb_cleanup_pipe_resources(काष्ठा ath6kl_usb *ar_usb)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ATH6KL_USB_PIPE_MAX; i++)
		ath6kl_usb_मुक्त_pipe_resources(&ar_usb->pipes[i]);
पूर्ण

अटल u8 ath6kl_usb_get_logical_pipe_num(काष्ठा ath6kl_usb *ar_usb,
					  u8 ep_address, पूर्णांक *urb_count)
अणु
	u8 pipe_num = ATH6KL_USB_PIPE_INVALID;

	चयन (ep_address) अणु
	हाल ATH6KL_USB_EP_ADDR_APP_CTRL_IN:
		pipe_num = ATH6KL_USB_PIPE_RX_CTRL;
		*urb_count = RX_URB_COUNT;
		अवरोध;
	हाल ATH6KL_USB_EP_ADDR_APP_DATA_IN:
		pipe_num = ATH6KL_USB_PIPE_RX_DATA;
		*urb_count = RX_URB_COUNT;
		अवरोध;
	हाल ATH6KL_USB_EP_ADDR_APP_INT_IN:
		pipe_num = ATH6KL_USB_PIPE_RX_INT;
		*urb_count = RX_URB_COUNT;
		अवरोध;
	हाल ATH6KL_USB_EP_ADDR_APP_DATA2_IN:
		pipe_num = ATH6KL_USB_PIPE_RX_DATA2;
		*urb_count = RX_URB_COUNT;
		अवरोध;
	हाल ATH6KL_USB_EP_ADDR_APP_CTRL_OUT:
		pipe_num = ATH6KL_USB_PIPE_TX_CTRL;
		*urb_count = TX_URB_COUNT;
		अवरोध;
	हाल ATH6KL_USB_EP_ADDR_APP_DATA_LP_OUT:
		pipe_num = ATH6KL_USB_PIPE_TX_DATA_LP;
		*urb_count = TX_URB_COUNT;
		अवरोध;
	हाल ATH6KL_USB_EP_ADDR_APP_DATA_MP_OUT:
		pipe_num = ATH6KL_USB_PIPE_TX_DATA_MP;
		*urb_count = TX_URB_COUNT;
		अवरोध;
	हाल ATH6KL_USB_EP_ADDR_APP_DATA_HP_OUT:
		pipe_num = ATH6KL_USB_PIPE_TX_DATA_HP;
		*urb_count = TX_URB_COUNT;
		अवरोध;
	शेष:
		/* note: there may be endpoपूर्णांकs not currently used */
		अवरोध;
	पूर्ण

	वापस pipe_num;
पूर्ण

अटल पूर्णांक ath6kl_usb_setup_pipe_resources(काष्ठा ath6kl_usb *ar_usb)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface = ar_usb->पूर्णांकerface;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc = पूर्णांकerface->cur_altsetting;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा ath6kl_usb_pipe *pipe;
	पूर्णांक i, urbcount, status = 0;
	u8 pipe_num;

	ath6kl_dbg(ATH6KL_DBG_USB, "setting up USB Pipes using interface\n");

	/* walk descriptors and setup pipes */
	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; ++i) अणु
		endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[i].desc;

		अगर (ATH6KL_USB_IS_BULK_EP(endpoपूर्णांक->bmAttributes)) अणु
			ath6kl_dbg(ATH6KL_DBG_USB,
				   "%s Bulk Ep:0x%2.2X maxpktsz:%d\n",
				   ATH6KL_USB_IS_सूची_IN
				   (endpoपूर्णांक->bEndpoपूर्णांकAddress) ?
				   "RX" : "TX", endpoपूर्णांक->bEndpoपूर्णांकAddress,
				   le16_to_cpu(endpoपूर्णांक->wMaxPacketSize));
		पूर्ण अन्यथा अगर (ATH6KL_USB_IS_INT_EP(endpoपूर्णांक->bmAttributes)) अणु
			ath6kl_dbg(ATH6KL_DBG_USB,
				   "%s Int Ep:0x%2.2X maxpktsz:%d interval:%d\n",
				   ATH6KL_USB_IS_सूची_IN
				   (endpoपूर्णांक->bEndpoपूर्णांकAddress) ?
				   "RX" : "TX", endpoपूर्णांक->bEndpoपूर्णांकAddress,
				   le16_to_cpu(endpoपूर्णांक->wMaxPacketSize),
				   endpoपूर्णांक->bInterval);
		पूर्ण अन्यथा अगर (ATH6KL_USB_IS_ISOC_EP(endpoपूर्णांक->bmAttributes)) अणु
			/* TODO क्रम ISO */
			ath6kl_dbg(ATH6KL_DBG_USB,
				   "%s ISOC Ep:0x%2.2X maxpktsz:%d interval:%d\n",
				   ATH6KL_USB_IS_सूची_IN
				   (endpoपूर्णांक->bEndpoपूर्णांकAddress) ?
				   "RX" : "TX", endpoपूर्णांक->bEndpoपूर्णांकAddress,
				   le16_to_cpu(endpoपूर्णांक->wMaxPacketSize),
				   endpoपूर्णांक->bInterval);
		पूर्ण
		urbcount = 0;

		pipe_num =
		    ath6kl_usb_get_logical_pipe_num(ar_usb,
						    endpoपूर्णांक->bEndpoपूर्णांकAddress,
						    &urbcount);
		अगर (pipe_num == ATH6KL_USB_PIPE_INVALID)
			जारी;

		pipe = &ar_usb->pipes[pipe_num];
		अगर (pipe->ar_usb != शून्य) अणु
			/* hmmm..pipe was alपढ़ोy setup */
			जारी;
		पूर्ण

		pipe->ar_usb = ar_usb;
		pipe->logical_pipe_num = pipe_num;
		pipe->ep_address = endpoपूर्णांक->bEndpoपूर्णांकAddress;
		pipe->max_packet_size = le16_to_cpu(endpoपूर्णांक->wMaxPacketSize);

		अगर (ATH6KL_USB_IS_BULK_EP(endpoपूर्णांक->bmAttributes)) अणु
			अगर (ATH6KL_USB_IS_सूची_IN(pipe->ep_address)) अणु
				pipe->usb_pipe_handle =
				    usb_rcvbulkpipe(ar_usb->udev,
						    pipe->ep_address);
			पूर्ण अन्यथा अणु
				pipe->usb_pipe_handle =
				    usb_sndbulkpipe(ar_usb->udev,
						    pipe->ep_address);
			पूर्ण
		पूर्ण अन्यथा अगर (ATH6KL_USB_IS_INT_EP(endpoपूर्णांक->bmAttributes)) अणु
			अगर (ATH6KL_USB_IS_सूची_IN(pipe->ep_address)) अणु
				pipe->usb_pipe_handle =
				    usb_rcvपूर्णांकpipe(ar_usb->udev,
						   pipe->ep_address);
			पूर्ण अन्यथा अणु
				pipe->usb_pipe_handle =
				    usb_sndपूर्णांकpipe(ar_usb->udev,
						   pipe->ep_address);
			पूर्ण
		पूर्ण अन्यथा अगर (ATH6KL_USB_IS_ISOC_EP(endpoपूर्णांक->bmAttributes)) अणु
			/* TODO क्रम ISO */
			अगर (ATH6KL_USB_IS_सूची_IN(pipe->ep_address)) अणु
				pipe->usb_pipe_handle =
				    usb_rcvisocpipe(ar_usb->udev,
						    pipe->ep_address);
			पूर्ण अन्यथा अणु
				pipe->usb_pipe_handle =
				    usb_sndisocpipe(ar_usb->udev,
						    pipe->ep_address);
			पूर्ण
		पूर्ण

		pipe->ep_desc = endpoपूर्णांक;

		अगर (!ATH6KL_USB_IS_सूची_IN(pipe->ep_address))
			pipe->flags |= ATH6KL_USB_PIPE_FLAG_TX;

		status = ath6kl_usb_alloc_pipe_resources(pipe, urbcount);
		अगर (status != 0)
			अवरोध;
	पूर्ण

	वापस status;
पूर्ण

/* pipe operations */
अटल व्योम ath6kl_usb_post_recv_transfers(काष्ठा ath6kl_usb_pipe *recv_pipe,
					   पूर्णांक buffer_length)
अणु
	काष्ठा ath6kl_urb_context *urb_context;
	काष्ठा urb *urb;
	पूर्णांक usb_status;

	जबतक (true) अणु
		urb_context = ath6kl_usb_alloc_urb_from_pipe(recv_pipe);
		अगर (urb_context == शून्य)
			अवरोध;

		urb_context->skb = dev_alloc_skb(buffer_length);
		अगर (urb_context->skb == शून्य)
			जाओ err_cleanup_urb;

		urb = usb_alloc_urb(0, GFP_ATOMIC);
		अगर (urb == शून्य)
			जाओ err_cleanup_urb;

		usb_fill_bulk_urb(urb,
				  recv_pipe->ar_usb->udev,
				  recv_pipe->usb_pipe_handle,
				  urb_context->skb->data,
				  buffer_length,
				  ath6kl_usb_recv_complete, urb_context);

		ath6kl_dbg(ATH6KL_DBG_USB_BULK,
			   "ath6kl usb: bulk recv submit:%d, 0x%X (ep:0x%2.2X), %d bytes buf:0x%p\n",
			   recv_pipe->logical_pipe_num,
			   recv_pipe->usb_pipe_handle, recv_pipe->ep_address,
			   buffer_length, urb_context->skb);

		usb_anchor_urb(urb, &recv_pipe->urb_submitted);
		usb_status = usb_submit_urb(urb, GFP_ATOMIC);

		अगर (usb_status) अणु
			ath6kl_dbg(ATH6KL_DBG_USB_BULK,
				   "ath6kl usb : usb bulk recv failed %d\n",
				   usb_status);
			usb_unanchor_urb(urb);
			usb_मुक्त_urb(urb);
			जाओ err_cleanup_urb;
		पूर्ण
		usb_मुक्त_urb(urb);
	पूर्ण
	वापस;

err_cleanup_urb:
	ath6kl_usb_cleanup_recv_urb(urb_context);
	वापस;
पूर्ण

अटल व्योम ath6kl_usb_flush_all(काष्ठा ath6kl_usb *ar_usb)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ATH6KL_USB_PIPE_MAX; i++) अणु
		अगर (ar_usb->pipes[i].ar_usb != शून्य)
			usb_समाप्त_anchored_urbs(&ar_usb->pipes[i].urb_submitted);
	पूर्ण

	/*
	 * Flushing any pending I/O may schedule work this call will block
	 * until all scheduled work runs to completion.
	 */
	flush_scheduled_work();
पूर्ण

अटल व्योम ath6kl_usb_start_recv_pipes(काष्ठा ath6kl_usb *ar_usb)
अणु
	/*
	 * note: control pipe is no दीर्घer used
	 * ar_usb->pipes[ATH6KL_USB_PIPE_RX_CTRL].urb_cnt_thresh =
	 *      ar_usb->pipes[ATH6KL_USB_PIPE_RX_CTRL].urb_alloc/2;
	 * ath6kl_usb_post_recv_transfers(&ar_usb->
	 *		pipes[ATH6KL_USB_PIPE_RX_CTRL],
	 *		ATH6KL_USB_RX_BUFFER_SIZE);
	 */

	ar_usb->pipes[ATH6KL_USB_PIPE_RX_DATA].urb_cnt_thresh = 1;

	ath6kl_usb_post_recv_transfers(&ar_usb->pipes[ATH6KL_USB_PIPE_RX_DATA],
				       ATH6KL_USB_RX_BUFFER_SIZE);
पूर्ण

/* hअगर usb rx/tx completion functions */
अटल व्योम ath6kl_usb_recv_complete(काष्ठा urb *urb)
अणु
	काष्ठा ath6kl_urb_context *urb_context = urb->context;
	काष्ठा ath6kl_usb_pipe *pipe = urb_context->pipe;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक status = 0;

	ath6kl_dbg(ATH6KL_DBG_USB_BULK,
		   "%s: recv pipe: %d, stat:%d, len:%d urb:0x%p\n", __func__,
		   pipe->logical_pipe_num, urb->status, urb->actual_length,
		   urb);

	अगर (urb->status != 0) अणु
		status = -EIO;
		चयन (urb->status) अणु
		हाल -ECONNRESET:
		हाल -ENOENT:
		हाल -ESHUTDOWN:
			/*
			 * no need to spew these errors when device
			 * हटाओd or urb समाप्तed due to driver shutकरोwn
			 */
			status = -ECANCELED;
			अवरोध;
		शेष:
			ath6kl_dbg(ATH6KL_DBG_USB_BULK,
				   "%s recv pipe: %d (ep:0x%2.2X), failed:%d\n",
				   __func__, pipe->logical_pipe_num,
				   pipe->ep_address, urb->status);
			अवरोध;
		पूर्ण
		जाओ cleanup_recv_urb;
	पूर्ण

	अगर (urb->actual_length == 0)
		जाओ cleanup_recv_urb;

	skb = urb_context->skb;

	/* we are going to pass it up */
	urb_context->skb = शून्य;
	skb_put(skb, urb->actual_length);

	/* note: queue implements a lock */
	skb_queue_tail(&pipe->io_comp_queue, skb);
	schedule_work(&pipe->io_complete_work);

cleanup_recv_urb:
	ath6kl_usb_cleanup_recv_urb(urb_context);

	अगर (status == 0 &&
	    pipe->urb_cnt >= pipe->urb_cnt_thresh) अणु
		/* our मुक्त urbs are piling up, post more transfers */
		ath6kl_usb_post_recv_transfers(pipe, ATH6KL_USB_RX_BUFFER_SIZE);
	पूर्ण
पूर्ण

अटल व्योम ath6kl_usb_usb_transmit_complete(काष्ठा urb *urb)
अणु
	काष्ठा ath6kl_urb_context *urb_context = urb->context;
	काष्ठा ath6kl_usb_pipe *pipe = urb_context->pipe;
	काष्ठा sk_buff *skb;

	ath6kl_dbg(ATH6KL_DBG_USB_BULK,
		   "%s: pipe: %d, stat:%d, len:%d\n",
		   __func__, pipe->logical_pipe_num, urb->status,
		   urb->actual_length);

	अगर (urb->status != 0) अणु
		ath6kl_dbg(ATH6KL_DBG_USB_BULK,
			   "%s:  pipe: %d, failed:%d\n",
			   __func__, pipe->logical_pipe_num, urb->status);
	पूर्ण

	skb = urb_context->skb;
	urb_context->skb = शून्य;
	ath6kl_usb_मुक्त_urb_to_pipe(urb_context->pipe, urb_context);

	/* note: queue implements a lock */
	skb_queue_tail(&pipe->io_comp_queue, skb);
	schedule_work(&pipe->io_complete_work);
पूर्ण

अटल व्योम ath6kl_usb_io_comp_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath6kl_usb_pipe *pipe = container_of(work,
						    काष्ठा ath6kl_usb_pipe,
						    io_complete_work);
	काष्ठा ath6kl_usb *ar_usb;
	काष्ठा sk_buff *skb;

	ar_usb = pipe->ar_usb;

	जबतक ((skb = skb_dequeue(&pipe->io_comp_queue))) अणु
		अगर (pipe->flags & ATH6KL_USB_PIPE_FLAG_TX) अणु
			ath6kl_dbg(ATH6KL_DBG_USB_BULK,
				   "ath6kl usb xmit callback buf:0x%p\n", skb);
			ath6kl_core_tx_complete(ar_usb->ar, skb);
		पूर्ण अन्यथा अणु
			ath6kl_dbg(ATH6KL_DBG_USB_BULK,
				   "ath6kl usb recv callback buf:0x%p\n", skb);
			ath6kl_core_rx_complete(ar_usb->ar, skb,
						pipe->logical_pipe_num);
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा ATH6KL_USB_MAX_DIAG_CMD (माप(काष्ठा ath6kl_usb_ctrl_diag_cmd_ग_लिखो))
#घोषणा ATH6KL_USB_MAX_DIAG_RESP (माप(काष्ठा ath6kl_usb_ctrl_diag_resp_पढ़ो))

अटल व्योम ath6kl_usb_destroy(काष्ठा ath6kl_usb *ar_usb)
अणु
	ath6kl_usb_flush_all(ar_usb);

	ath6kl_usb_cleanup_pipe_resources(ar_usb);

	usb_set_पूर्णांकfdata(ar_usb->पूर्णांकerface, शून्य);

	kमुक्त(ar_usb->diag_cmd_buffer);
	kमुक्त(ar_usb->diag_resp_buffer);

	kमुक्त(ar_usb);
पूर्ण

अटल काष्ठा ath6kl_usb *ath6kl_usb_create(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा ath6kl_usb *ar_usb;
	काष्ठा ath6kl_usb_pipe *pipe;
	पूर्णांक status = 0;
	पूर्णांक i;

	ar_usb = kzalloc(माप(काष्ठा ath6kl_usb), GFP_KERNEL);
	अगर (ar_usb == शून्य)
		जाओ fail_ath6kl_usb_create;

	usb_set_पूर्णांकfdata(पूर्णांकerface, ar_usb);
	spin_lock_init(&(ar_usb->cs_lock));
	ar_usb->udev = dev;
	ar_usb->पूर्णांकerface = पूर्णांकerface;

	क्रम (i = 0; i < ATH6KL_USB_PIPE_MAX; i++) अणु
		pipe = &ar_usb->pipes[i];
		INIT_WORK(&pipe->io_complete_work,
			  ath6kl_usb_io_comp_work);
		skb_queue_head_init(&pipe->io_comp_queue);
	पूर्ण

	ar_usb->diag_cmd_buffer = kzalloc(ATH6KL_USB_MAX_DIAG_CMD, GFP_KERNEL);
	अगर (ar_usb->diag_cmd_buffer == शून्य) अणु
		status = -ENOMEM;
		जाओ fail_ath6kl_usb_create;
	पूर्ण

	ar_usb->diag_resp_buffer = kzalloc(ATH6KL_USB_MAX_DIAG_RESP,
					   GFP_KERNEL);
	अगर (ar_usb->diag_resp_buffer == शून्य) अणु
		status = -ENOMEM;
		जाओ fail_ath6kl_usb_create;
	पूर्ण

	status = ath6kl_usb_setup_pipe_resources(ar_usb);

fail_ath6kl_usb_create:
	अगर (status != 0) अणु
		ath6kl_usb_destroy(ar_usb);
		ar_usb = शून्य;
	पूर्ण
	वापस ar_usb;
पूर्ण

अटल व्योम ath6kl_usb_device_detached(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा ath6kl_usb *ar_usb;

	ar_usb = usb_get_पूर्णांकfdata(पूर्णांकerface);
	अगर (ar_usb == शून्य)
		वापस;

	ath6kl_stop_txrx(ar_usb->ar);

	/* Delay to रुको क्रम the target to reboot */
	mdelay(20);
	ath6kl_core_cleanup(ar_usb->ar);
	ath6kl_usb_destroy(ar_usb);
पूर्ण

/* exported hअगर usb APIs क्रम htc pipe */
अटल व्योम hअगर_start(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_usb *device = ath6kl_usb_priv(ar);
	पूर्णांक i;

	ath6kl_usb_start_recv_pipes(device);

	/* set the TX resource avail threshold क्रम each TX pipe */
	क्रम (i = ATH6KL_USB_PIPE_TX_CTRL;
	     i <= ATH6KL_USB_PIPE_TX_DATA_HP; i++) अणु
		device->pipes[i].urb_cnt_thresh =
		    device->pipes[i].urb_alloc / 2;
	पूर्ण
पूर्ण

अटल पूर्णांक ath6kl_usb_send(काष्ठा ath6kl *ar, u8 PipeID,
			   काष्ठा sk_buff *hdr_skb, काष्ठा sk_buff *skb)
अणु
	काष्ठा ath6kl_usb *device = ath6kl_usb_priv(ar);
	काष्ठा ath6kl_usb_pipe *pipe = &device->pipes[PipeID];
	काष्ठा ath6kl_urb_context *urb_context;
	पूर्णांक usb_status, status = 0;
	काष्ठा urb *urb;
	u8 *data;
	u32 len;

	ath6kl_dbg(ATH6KL_DBG_USB_BULK, "+%s pipe : %d, buf:0x%p\n",
		   __func__, PipeID, skb);

	urb_context = ath6kl_usb_alloc_urb_from_pipe(pipe);

	अगर (urb_context == शून्य) अणु
		/*
		 * TODO: it is possible to run out of urbs अगर
		 * 2 endpoपूर्णांकs map to the same pipe ID
		 */
		ath6kl_dbg(ATH6KL_DBG_USB_BULK,
			   "%s pipe:%d no urbs left. URB Cnt : %d\n",
			   __func__, PipeID, pipe->urb_cnt);
		status = -ENOMEM;
		जाओ fail_hअगर_send;
	पूर्ण

	urb_context->skb = skb;

	data = skb->data;
	len = skb->len;

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (urb == शून्य) अणु
		status = -ENOMEM;
		ath6kl_usb_मुक्त_urb_to_pipe(urb_context->pipe,
					    urb_context);
		जाओ fail_hअगर_send;
	पूर्ण

	usb_fill_bulk_urb(urb,
			  device->udev,
			  pipe->usb_pipe_handle,
			  data,
			  len,
			  ath6kl_usb_usb_transmit_complete, urb_context);

	अगर ((len % pipe->max_packet_size) == 0) अणु
		/* hit a max packet boundary on this pipe */
		urb->transfer_flags |= URB_ZERO_PACKET;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_USB_BULK,
		   "athusb bulk send submit:%d, 0x%X (ep:0x%2.2X), %d bytes\n",
		   pipe->logical_pipe_num, pipe->usb_pipe_handle,
		   pipe->ep_address, len);

	usb_anchor_urb(urb, &pipe->urb_submitted);
	usb_status = usb_submit_urb(urb, GFP_ATOMIC);

	अगर (usb_status) अणु
		ath6kl_dbg(ATH6KL_DBG_USB_BULK,
			   "ath6kl usb : usb bulk transmit failed %d\n",
			   usb_status);
		usb_unanchor_urb(urb);
		ath6kl_usb_मुक्त_urb_to_pipe(urb_context->pipe,
					    urb_context);
		status = -EINVAL;
	पूर्ण
	usb_मुक्त_urb(urb);

fail_hअगर_send:
	वापस status;
पूर्ण

अटल व्योम hअगर_stop(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_usb *device = ath6kl_usb_priv(ar);

	ath6kl_usb_flush_all(device);
पूर्ण

अटल व्योम ath6kl_usb_get_शेष_pipe(काष्ठा ath6kl *ar,
					u8 *ul_pipe, u8 *dl_pipe)
अणु
	*ul_pipe = ATH6KL_USB_PIPE_TX_CTRL;
	*dl_pipe = ATH6KL_USB_PIPE_RX_CTRL;
पूर्ण

अटल पूर्णांक ath6kl_usb_map_service_pipe(काष्ठा ath6kl *ar, u16 svc_id,
				       u8 *ul_pipe, u8 *dl_pipe)
अणु
	पूर्णांक status = 0;

	चयन (svc_id) अणु
	हाल HTC_CTRL_RSVD_SVC:
	हाल WMI_CONTROL_SVC:
		*ul_pipe = ATH6KL_USB_PIPE_TX_CTRL;
		/* due to large control packets, shअगरt to data pipe */
		*dl_pipe = ATH6KL_USB_PIPE_RX_DATA;
		अवरोध;
	हाल WMI_DATA_BE_SVC:
	हाल WMI_DATA_BK_SVC:
		*ul_pipe = ATH6KL_USB_PIPE_TX_DATA_LP;
		/*
		* Disable rxdata2 directly, it will be enabled
		* अगर FW enable rxdata2
		*/
		*dl_pipe = ATH6KL_USB_PIPE_RX_DATA;
		अवरोध;
	हाल WMI_DATA_VI_SVC:

		अगर (test_bit(ATH6KL_FW_CAPABILITY_MAP_LP_ENDPOINT,
			     ar->fw_capabilities))
			*ul_pipe = ATH6KL_USB_PIPE_TX_DATA_LP;
		अन्यथा
			*ul_pipe = ATH6KL_USB_PIPE_TX_DATA_MP;
		/*
		* Disable rxdata2 directly, it will be enabled
		* अगर FW enable rxdata2
		*/
		*dl_pipe = ATH6KL_USB_PIPE_RX_DATA;
		अवरोध;
	हाल WMI_DATA_VO_SVC:

		अगर (test_bit(ATH6KL_FW_CAPABILITY_MAP_LP_ENDPOINT,
			     ar->fw_capabilities))
			*ul_pipe = ATH6KL_USB_PIPE_TX_DATA_LP;
		अन्यथा
			*ul_pipe = ATH6KL_USB_PIPE_TX_DATA_MP;
		/*
		* Disable rxdata2 directly, it will be enabled
		* अगर FW enable rxdata2
		*/
		*dl_pipe = ATH6KL_USB_PIPE_RX_DATA;
		अवरोध;
	शेष:
		status = -EPERM;
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण

अटल u16 ath6kl_usb_get_मुक्त_queue_number(काष्ठा ath6kl *ar, u8 pipe_id)
अणु
	काष्ठा ath6kl_usb *device = ath6kl_usb_priv(ar);

	वापस device->pipes[pipe_id].urb_cnt;
पूर्ण

अटल व्योम hअगर_detach_htc(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_usb *device = ath6kl_usb_priv(ar);

	ath6kl_usb_flush_all(device);
पूर्ण

अटल पूर्णांक ath6kl_usb_submit_ctrl_out(काष्ठा ath6kl_usb *ar_usb,
				   u8 req, u16 value, u16 index, व्योम *data,
				   u32 size)
अणु
	u8 *buf = शून्य;
	पूर्णांक ret;

	अगर (size > 0) अणु
		buf = kmemdup(data, size, GFP_KERNEL);
		अगर (buf == शून्य)
			वापस -ENOMEM;
	पूर्ण

	/* note: अगर successful वापसs number of bytes transfered */
	ret = usb_control_msg(ar_usb->udev,
			      usb_sndctrlpipe(ar_usb->udev, 0),
			      req,
			      USB_सूची_OUT | USB_TYPE_VENDOR |
			      USB_RECIP_DEVICE, value, index, buf,
			      size, 1000);

	अगर (ret < 0) अणु
		ath6kl_warn("Failed to submit usb control message: %d\n", ret);
		kमुक्त(buf);
		वापस ret;
	पूर्ण

	kमुक्त(buf);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_usb_submit_ctrl_in(काष्ठा ath6kl_usb *ar_usb,
				  u8 req, u16 value, u16 index, व्योम *data,
				  u32 size)
अणु
	u8 *buf = शून्य;
	पूर्णांक ret;

	अगर (size > 0) अणु
		buf = kदो_स्मृति(size, GFP_KERNEL);
		अगर (buf == शून्य)
			वापस -ENOMEM;
	पूर्ण

	/* note: अगर successful वापसs number of bytes transfered */
	ret = usb_control_msg(ar_usb->udev,
				 usb_rcvctrlpipe(ar_usb->udev, 0),
				 req,
				 USB_सूची_IN | USB_TYPE_VENDOR |
				 USB_RECIP_DEVICE, value, index, buf,
				 size, 2 * HZ);

	अगर (ret < 0) अणु
		ath6kl_warn("Failed to read usb control message: %d\n", ret);
		kमुक्त(buf);
		वापस ret;
	पूर्ण

	स_नकल((u8 *) data, buf, size);

	kमुक्त(buf);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_usb_ctrl_msg_exchange(काष्ठा ath6kl_usb *ar_usb,
				     u8 req_val, u8 *req_buf, u32 req_len,
				     u8 resp_val, u8 *resp_buf, u32 *resp_len)
अणु
	पूर्णांक ret;

	/* send command */
	ret = ath6kl_usb_submit_ctrl_out(ar_usb, req_val, 0, 0,
					 req_buf, req_len);

	अगर (ret != 0)
		वापस ret;

	अगर (resp_buf == शून्य) अणु
		/* no expected response */
		वापस ret;
	पूर्ण

	/* get response */
	ret = ath6kl_usb_submit_ctrl_in(ar_usb, resp_val, 0, 0,
					resp_buf, *resp_len);

	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_usb_diag_पढ़ो32(काष्ठा ath6kl *ar, u32 address, u32 *data)
अणु
	काष्ठा ath6kl_usb *ar_usb = ar->hअगर_priv;
	काष्ठा ath6kl_usb_ctrl_diag_resp_पढ़ो *resp;
	काष्ठा ath6kl_usb_ctrl_diag_cmd_पढ़ो *cmd;
	u32 resp_len;
	पूर्णांक ret;

	cmd = (काष्ठा ath6kl_usb_ctrl_diag_cmd_पढ़ो *) ar_usb->diag_cmd_buffer;

	स_रखो(cmd, 0, माप(*cmd));
	cmd->cmd = ATH6KL_USB_CTRL_DIAG_CC_READ;
	cmd->address = cpu_to_le32(address);
	resp_len = माप(*resp);

	ret = ath6kl_usb_ctrl_msg_exchange(ar_usb,
				ATH6KL_USB_CONTROL_REQ_DIAG_CMD,
				(u8 *) cmd,
				माप(काष्ठा ath6kl_usb_ctrl_diag_cmd_ग_लिखो),
				ATH6KL_USB_CONTROL_REQ_DIAG_RESP,
				ar_usb->diag_resp_buffer, &resp_len);

	अगर (ret) अणु
		ath6kl_warn("diag read32 failed: %d\n", ret);
		वापस ret;
	पूर्ण

	resp = (काष्ठा ath6kl_usb_ctrl_diag_resp_पढ़ो *)
		ar_usb->diag_resp_buffer;

	*data = le32_to_cpu(resp->value);

	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_usb_diag_ग_लिखो32(काष्ठा ath6kl *ar, u32 address, __le32 data)
अणु
	काष्ठा ath6kl_usb *ar_usb = ar->hअगर_priv;
	काष्ठा ath6kl_usb_ctrl_diag_cmd_ग_लिखो *cmd;
	पूर्णांक ret;

	cmd = (काष्ठा ath6kl_usb_ctrl_diag_cmd_ग_लिखो *) ar_usb->diag_cmd_buffer;

	स_रखो(cmd, 0, माप(काष्ठा ath6kl_usb_ctrl_diag_cmd_ग_लिखो));
	cmd->cmd = cpu_to_le32(ATH6KL_USB_CTRL_DIAG_CC_WRITE);
	cmd->address = cpu_to_le32(address);
	cmd->value = data;

	ret = ath6kl_usb_ctrl_msg_exchange(ar_usb,
					   ATH6KL_USB_CONTROL_REQ_DIAG_CMD,
					   (u8 *) cmd,
					   माप(*cmd),
					   0, शून्य, शून्य);
	अगर (ret) अणु
		ath6kl_warn("diag_write32 failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_usb_bmi_पढ़ो(काष्ठा ath6kl *ar, u8 *buf, u32 len)
अणु
	काष्ठा ath6kl_usb *ar_usb = ar->hअगर_priv;
	पूर्णांक ret;

	/* get response */
	ret = ath6kl_usb_submit_ctrl_in(ar_usb,
					ATH6KL_USB_CONTROL_REQ_RECV_BMI_RESP,
					0, 0, buf, len);
	अगर (ret) अणु
		ath6kl_err("Unable to read the bmi data from the device: %d\n",
			   ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_usb_bmi_ग_लिखो(काष्ठा ath6kl *ar, u8 *buf, u32 len)
अणु
	काष्ठा ath6kl_usb *ar_usb = ar->hअगर_priv;
	पूर्णांक ret;

	/* send command */
	ret = ath6kl_usb_submit_ctrl_out(ar_usb,
					 ATH6KL_USB_CONTROL_REQ_SEND_BMI_CMD,
					 0, 0, buf, len);
	अगर (ret) अणु
		ath6kl_err("unable to send the bmi data to the device: %d\n",
			   ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_usb_घातer_on(काष्ठा ath6kl *ar)
अणु
	hअगर_start(ar);
	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_usb_घातer_off(काष्ठा ath6kl *ar)
अणु
	hअगर_detach_htc(ar);
	वापस 0;
पूर्ण

अटल व्योम ath6kl_usb_stop(काष्ठा ath6kl *ar)
अणु
	hअगर_stop(ar);
पूर्ण

अटल व्योम ath6kl_usb_cleanup_scatter(काष्ठा ath6kl *ar)
अणु
	/*
	 * USB करोesn't support it. Just वापस.
	 */
	वापस;
पूर्ण

अटल पूर्णांक ath6kl_usb_suspend(काष्ठा ath6kl *ar, काष्ठा cfg80211_wowlan *wow)
अणु
	/*
	 * cfg80211 suspend/WOW currently not supported क्रम USB.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_usb_resume(काष्ठा ath6kl *ar)
अणु
	/*
	 * cfg80211 resume currently not supported क्रम USB.
	 */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ath6kl_hअगर_ops ath6kl_usb_ops = अणु
	.diag_पढ़ो32 = ath6kl_usb_diag_पढ़ो32,
	.diag_ग_लिखो32 = ath6kl_usb_diag_ग_लिखो32,
	.bmi_पढ़ो = ath6kl_usb_bmi_पढ़ो,
	.bmi_ग_लिखो = ath6kl_usb_bmi_ग_लिखो,
	.घातer_on = ath6kl_usb_घातer_on,
	.घातer_off = ath6kl_usb_घातer_off,
	.stop = ath6kl_usb_stop,
	.pipe_send = ath6kl_usb_send,
	.pipe_get_शेष = ath6kl_usb_get_शेष_pipe,
	.pipe_map_service = ath6kl_usb_map_service_pipe,
	.pipe_get_मुक्त_queue_number = ath6kl_usb_get_मुक्त_queue_number,
	.cleanup_scatter = ath6kl_usb_cleanup_scatter,
	.suspend = ath6kl_usb_suspend,
	.resume = ath6kl_usb_resume,
पूर्ण;

/* ath6kl usb driver रेजिस्टरed functions */
अटल पूर्णांक ath6kl_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			    स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा ath6kl *ar;
	काष्ठा ath6kl_usb *ar_usb = शून्य;
	पूर्णांक venकरोr_id, product_id;
	पूर्णांक ret = 0;

	usb_get_dev(dev);

	venकरोr_id = le16_to_cpu(dev->descriptor.idVenकरोr);
	product_id = le16_to_cpu(dev->descriptor.idProduct);

	ath6kl_dbg(ATH6KL_DBG_USB, "vendor_id = %04x\n", venकरोr_id);
	ath6kl_dbg(ATH6KL_DBG_USB, "product_id = %04x\n", product_id);

	अगर (पूर्णांकerface->cur_altsetting)
		ath6kl_dbg(ATH6KL_DBG_USB, "USB Interface %d\n",
			   पूर्णांकerface->cur_altsetting->desc.bInterfaceNumber);


	अगर (dev->speed == USB_SPEED_HIGH)
		ath6kl_dbg(ATH6KL_DBG_USB, "USB 2.0 Host\n");
	अन्यथा
		ath6kl_dbg(ATH6KL_DBG_USB, "USB 1.1 Host\n");

	ar_usb = ath6kl_usb_create(पूर्णांकerface);

	अगर (ar_usb == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_usb_put;
	पूर्ण

	ar = ath6kl_core_create(&ar_usb->udev->dev);
	अगर (ar == शून्य) अणु
		ath6kl_err("Failed to alloc ath6kl core\n");
		ret = -ENOMEM;
		जाओ err_usb_destroy;
	पूर्ण

	ar->hअगर_priv = ar_usb;
	ar->hअगर_type = ATH6KL_HIF_TYPE_USB;
	ar->hअगर_ops = &ath6kl_usb_ops;
	ar->mbox_info.block_size = 16;
	ar->bmi.max_data_size = 252;

	ar_usb->ar = ar;

	ret = ath6kl_core_init(ar, ATH6KL_HTC_TYPE_PIPE);
	अगर (ret) अणु
		ath6kl_err("Failed to init ath6kl core: %d\n", ret);
		जाओ err_core_मुक्त;
	पूर्ण

	वापस ret;

err_core_मुक्त:
	ath6kl_core_destroy(ar);
err_usb_destroy:
	ath6kl_usb_destroy(ar_usb);
err_usb_put:
	usb_put_dev(dev);

	वापस ret;
पूर्ण

अटल व्योम ath6kl_usb_हटाओ(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	usb_put_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));
	ath6kl_usb_device_detached(पूर्णांकerface);
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक ath6kl_usb_pm_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			      pm_message_t message)
अणु
	काष्ठा ath6kl_usb *device;
	device = usb_get_पूर्णांकfdata(पूर्णांकerface);

	ath6kl_usb_flush_all(device);
	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_usb_pm_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा ath6kl_usb *device;
	device = usb_get_पूर्णांकfdata(पूर्णांकerface);

	ath6kl_usb_post_recv_transfers(&device->pipes[ATH6KL_USB_PIPE_RX_DATA],
				       ATH6KL_USB_RX_BUFFER_SIZE);
	ath6kl_usb_post_recv_transfers(&device->pipes[ATH6KL_USB_PIPE_RX_DATA2],
				       ATH6KL_USB_RX_BUFFER_SIZE);

	वापस 0;
पूर्ण

#अन्यथा

#घोषणा ath6kl_usb_pm_suspend शून्य
#घोषणा ath6kl_usb_pm_resume शून्य

#पूर्ण_अगर

/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id ath6kl_usb_ids[] = अणु
	अणुUSB_DEVICE(0x0cf3, 0x9375)पूर्ण,
	अणुUSB_DEVICE(0x0cf3, 0x9374)पूर्ण,
	अणु /* Terminating entry */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(usb, ath6kl_usb_ids);

अटल काष्ठा usb_driver ath6kl_usb_driver = अणु
	.name = "ath6kl_usb",
	.probe = ath6kl_usb_probe,
	.suspend = ath6kl_usb_pm_suspend,
	.resume = ath6kl_usb_pm_resume,
	.disconnect = ath6kl_usb_हटाओ,
	.id_table = ath6kl_usb_ids,
	.supports_स्वतःsuspend = true,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(ath6kl_usb_driver);

MODULE_AUTHOR("Atheros Communications, Inc.");
MODULE_DESCRIPTION("Driver support for Atheros AR600x USB devices");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_FIRMWARE(AR6004_HW_1_0_FIRMWARE_खाता);
MODULE_FIRMWARE(AR6004_HW_1_0_BOARD_DATA_खाता);
MODULE_FIRMWARE(AR6004_HW_1_0_DEFAULT_BOARD_DATA_खाता);
MODULE_FIRMWARE(AR6004_HW_1_1_FIRMWARE_खाता);
MODULE_FIRMWARE(AR6004_HW_1_1_BOARD_DATA_खाता);
MODULE_FIRMWARE(AR6004_HW_1_1_DEFAULT_BOARD_DATA_खाता);
MODULE_FIRMWARE(AR6004_HW_1_2_FIRMWARE_खाता);
MODULE_FIRMWARE(AR6004_HW_1_2_BOARD_DATA_खाता);
MODULE_FIRMWARE(AR6004_HW_1_2_DEFAULT_BOARD_DATA_खाता);
MODULE_FIRMWARE(AR6004_HW_1_3_FW_सूची "/" AR6004_HW_1_3_FIRMWARE_खाता);
MODULE_FIRMWARE(AR6004_HW_1_3_BOARD_DATA_खाता);
MODULE_FIRMWARE(AR6004_HW_1_3_DEFAULT_BOARD_DATA_खाता);
