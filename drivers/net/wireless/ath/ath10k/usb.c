<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2007-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2012,2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2016-2017 Erik Stromdahl <erik.stromdahl@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/usb.h>

#समावेश "debug.h"
#समावेश "core.h"
#समावेश "bmi.h"
#समावेश "hif.h"
#समावेश "htc.h"
#समावेश "usb.h"

अटल व्योम ath10k_usb_post_recv_transfers(काष्ठा ath10k *ar,
					   काष्ठा ath10k_usb_pipe *recv_pipe);

/* अंतरभूतd helper functions */

अटल अंतरभूत क्रमागत ath10k_htc_ep_id
eid_from_htc_hdr(काष्ठा ath10k_htc_hdr *htc_hdr)
अणु
	वापस (क्रमागत ath10k_htc_ep_id)htc_hdr->eid;
पूर्ण

अटल अंतरभूत bool is_trailer_only_msg(काष्ठा ath10k_htc_hdr *htc_hdr)
अणु
	वापस __le16_to_cpu(htc_hdr->len) == htc_hdr->trailer_len;
पूर्ण

/* pipe/urb operations */
अटल काष्ठा ath10k_urb_context *
ath10k_usb_alloc_urb_from_pipe(काष्ठा ath10k_usb_pipe *pipe)
अणु
	काष्ठा ath10k_urb_context *urb_context = शून्य;
	अचिन्हित दीर्घ flags;

	/* bail अगर this pipe is not initialized */
	अगर (!pipe->ar_usb)
		वापस शून्य;

	spin_lock_irqsave(&pipe->ar_usb->cs_lock, flags);
	अगर (!list_empty(&pipe->urb_list_head)) अणु
		urb_context = list_first_entry(&pipe->urb_list_head,
					       काष्ठा ath10k_urb_context, link);
		list_del(&urb_context->link);
		pipe->urb_cnt--;
	पूर्ण
	spin_unlock_irqrestore(&pipe->ar_usb->cs_lock, flags);

	वापस urb_context;
पूर्ण

अटल व्योम ath10k_usb_मुक्त_urb_to_pipe(काष्ठा ath10k_usb_pipe *pipe,
					काष्ठा ath10k_urb_context *urb_context)
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

अटल व्योम ath10k_usb_cleanup_recv_urb(काष्ठा ath10k_urb_context *urb_context)
अणु
	dev_kमुक्त_skb(urb_context->skb);
	urb_context->skb = शून्य;

	ath10k_usb_मुक्त_urb_to_pipe(urb_context->pipe, urb_context);
पूर्ण

अटल व्योम ath10k_usb_मुक्त_pipe_resources(काष्ठा ath10k *ar,
					   काष्ठा ath10k_usb_pipe *pipe)
अणु
	काष्ठा ath10k_urb_context *urb_context;

	अगर (!pipe->ar_usb) अणु
		/* nothing allocated क्रम this pipe */
		वापस;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_USB,
		   "usb free resources lpipe %d hpipe 0x%x urbs %d avail %d\n",
		   pipe->logical_pipe_num, pipe->usb_pipe_handle,
		   pipe->urb_alloc, pipe->urb_cnt);

	अगर (pipe->urb_alloc != pipe->urb_cnt) अणु
		ath10k_dbg(ar, ATH10K_DBG_USB,
			   "usb urb leak lpipe %d hpipe 0x%x urbs %d avail %d\n",
			   pipe->logical_pipe_num, pipe->usb_pipe_handle,
			   pipe->urb_alloc, pipe->urb_cnt);
	पूर्ण

	क्रम (;;) अणु
		urb_context = ath10k_usb_alloc_urb_from_pipe(pipe);

		अगर (!urb_context)
			अवरोध;

		kमुक्त(urb_context);
	पूर्ण
पूर्ण

अटल व्योम ath10k_usb_cleanup_pipe_resources(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_usb *ar_usb = ath10k_usb_priv(ar);
	पूर्णांक i;

	क्रम (i = 0; i < ATH10K_USB_PIPE_MAX; i++)
		ath10k_usb_मुक्त_pipe_resources(ar, &ar_usb->pipes[i]);
पूर्ण

/* hअगर usb rx/tx completion functions */

अटल व्योम ath10k_usb_recv_complete(काष्ठा urb *urb)
अणु
	काष्ठा ath10k_urb_context *urb_context = urb->context;
	काष्ठा ath10k_usb_pipe *pipe = urb_context->pipe;
	काष्ठा ath10k *ar = pipe->ar_usb->ar;
	काष्ठा sk_buff *skb;
	पूर्णांक status = 0;

	ath10k_dbg(ar, ATH10K_DBG_USB_BULK,
		   "usb recv pipe %d stat %d len %d urb 0x%pK\n",
		   pipe->logical_pipe_num, urb->status, urb->actual_length,
		   urb);

	अगर (urb->status != 0) अणु
		status = -EIO;
		चयन (urb->status) अणु
		हाल -ECONNRESET:
		हाल -ENOENT:
		हाल -ESHUTDOWN:
			/* no need to spew these errors when device
			 * हटाओd or urb समाप्तed due to driver shutकरोwn
			 */
			status = -ECANCELED;
			अवरोध;
		शेष:
			ath10k_dbg(ar, ATH10K_DBG_USB_BULK,
				   "usb recv pipe %d ep 0x%2.2x failed: %d\n",
				   pipe->logical_pipe_num,
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
	ath10k_usb_cleanup_recv_urb(urb_context);

	अगर (status == 0 &&
	    pipe->urb_cnt >= pipe->urb_cnt_thresh) अणु
		/* our मुक्त urbs are piling up, post more transfers */
		ath10k_usb_post_recv_transfers(ar, pipe);
	पूर्ण
पूर्ण

अटल व्योम ath10k_usb_transmit_complete(काष्ठा urb *urb)
अणु
	काष्ठा ath10k_urb_context *urb_context = urb->context;
	काष्ठा ath10k_usb_pipe *pipe = urb_context->pipe;
	काष्ठा ath10k *ar = pipe->ar_usb->ar;
	काष्ठा sk_buff *skb;

	अगर (urb->status != 0) अणु
		ath10k_dbg(ar, ATH10K_DBG_USB_BULK,
			   "pipe: %d, failed:%d\n",
			   pipe->logical_pipe_num, urb->status);
	पूर्ण

	skb = urb_context->skb;
	urb_context->skb = शून्य;
	ath10k_usb_मुक्त_urb_to_pipe(urb_context->pipe, urb_context);

	/* note: queue implements a lock */
	skb_queue_tail(&pipe->io_comp_queue, skb);
	schedule_work(&pipe->io_complete_work);
पूर्ण

/* pipe operations */
अटल व्योम ath10k_usb_post_recv_transfers(काष्ठा ath10k *ar,
					   काष्ठा ath10k_usb_pipe *recv_pipe)
अणु
	काष्ठा ath10k_urb_context *urb_context;
	काष्ठा urb *urb;
	पूर्णांक usb_status;

	क्रम (;;) अणु
		urb_context = ath10k_usb_alloc_urb_from_pipe(recv_pipe);
		अगर (!urb_context)
			अवरोध;

		urb_context->skb = dev_alloc_skb(ATH10K_USB_RX_BUFFER_SIZE);
		अगर (!urb_context->skb)
			जाओ err;

		urb = usb_alloc_urb(0, GFP_ATOMIC);
		अगर (!urb)
			जाओ err;

		usb_fill_bulk_urb(urb,
				  recv_pipe->ar_usb->udev,
				  recv_pipe->usb_pipe_handle,
				  urb_context->skb->data,
				  ATH10K_USB_RX_BUFFER_SIZE,
				  ath10k_usb_recv_complete, urb_context);

		ath10k_dbg(ar, ATH10K_DBG_USB_BULK,
			   "usb bulk recv submit %d 0x%x ep 0x%2.2x len %d buf 0x%pK\n",
			   recv_pipe->logical_pipe_num,
			   recv_pipe->usb_pipe_handle, recv_pipe->ep_address,
			   ATH10K_USB_RX_BUFFER_SIZE, urb_context->skb);

		usb_anchor_urb(urb, &recv_pipe->urb_submitted);
		usb_status = usb_submit_urb(urb, GFP_ATOMIC);

		अगर (usb_status) अणु
			ath10k_dbg(ar, ATH10K_DBG_USB_BULK,
				   "usb bulk recv failed: %d\n",
				   usb_status);
			usb_unanchor_urb(urb);
			usb_मुक्त_urb(urb);
			जाओ err;
		पूर्ण
		usb_मुक्त_urb(urb);
	पूर्ण

	वापस;

err:
	ath10k_usb_cleanup_recv_urb(urb_context);
पूर्ण

अटल व्योम ath10k_usb_flush_all(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_usb *ar_usb = ath10k_usb_priv(ar);
	पूर्णांक i;

	क्रम (i = 0; i < ATH10K_USB_PIPE_MAX; i++) अणु
		अगर (ar_usb->pipes[i].ar_usb) अणु
			usb_समाप्त_anchored_urbs(&ar_usb->pipes[i].urb_submitted);
			cancel_work_sync(&ar_usb->pipes[i].io_complete_work);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ath10k_usb_start_recv_pipes(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_usb *ar_usb = ath10k_usb_priv(ar);

	ar_usb->pipes[ATH10K_USB_PIPE_RX_DATA].urb_cnt_thresh = 1;

	ath10k_usb_post_recv_transfers(ar,
				       &ar_usb->pipes[ATH10K_USB_PIPE_RX_DATA]);
पूर्ण

अटल व्योम ath10k_usb_tx_complete(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा ath10k_htc_hdr *htc_hdr;
	काष्ठा ath10k_htc_ep *ep;

	htc_hdr = (काष्ठा ath10k_htc_hdr *)skb->data;
	ep = &ar->htc.endpoपूर्णांक[htc_hdr->eid];
	ath10k_htc_notअगरy_tx_completion(ep, skb);
	/* The TX complete handler now owns the skb... */
पूर्ण

अटल व्योम ath10k_usb_rx_complete(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा ath10k_htc *htc = &ar->htc;
	काष्ठा ath10k_htc_hdr *htc_hdr;
	क्रमागत ath10k_htc_ep_id eid;
	काष्ठा ath10k_htc_ep *ep;
	u16 payload_len;
	u8 *trailer;
	पूर्णांक ret;

	htc_hdr = (काष्ठा ath10k_htc_hdr *)skb->data;
	eid = eid_from_htc_hdr(htc_hdr);
	ep = &ar->htc.endpoपूर्णांक[eid];

	अगर (ep->service_id == 0) अणु
		ath10k_warn(ar, "ep %d is not connected\n", eid);
		जाओ out_मुक्त_skb;
	पूर्ण

	payload_len = le16_to_cpu(htc_hdr->len);
	अगर (!payload_len) अणु
		ath10k_warn(ar, "zero length frame received, firmware crashed?\n");
		जाओ out_मुक्त_skb;
	पूर्ण

	अगर (payload_len < htc_hdr->trailer_len) अणु
		ath10k_warn(ar, "malformed frame received, firmware crashed?\n");
		जाओ out_मुक्त_skb;
	पूर्ण

	अगर (htc_hdr->flags & ATH10K_HTC_FLAG_TRAILER_PRESENT) अणु
		trailer = skb->data + माप(*htc_hdr) + payload_len -
			  htc_hdr->trailer_len;

		ret = ath10k_htc_process_trailer(htc,
						 trailer,
						 htc_hdr->trailer_len,
						 eid,
						 शून्य,
						 शून्य);
		अगर (ret)
			जाओ out_मुक्त_skb;

		अगर (is_trailer_only_msg(htc_hdr))
			जाओ out_मुक्त_skb;

		/* strip off the trailer from the skb since it should not
		 * be passed on to upper layers
		 */
		skb_trim(skb, skb->len - htc_hdr->trailer_len);
	पूर्ण

	skb_pull(skb, माप(*htc_hdr));
	ep->ep_ops.ep_rx_complete(ar, skb);
	/* The RX complete handler now owns the skb... */

	वापस;

out_मुक्त_skb:
	dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम ath10k_usb_io_comp_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath10k_usb_pipe *pipe = container_of(work,
						    काष्ठा ath10k_usb_pipe,
						    io_complete_work);
	काष्ठा ath10k *ar = pipe->ar_usb->ar;
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(&pipe->io_comp_queue))) अणु
		अगर (pipe->flags & ATH10K_USB_PIPE_FLAG_TX)
			ath10k_usb_tx_complete(ar, skb);
		अन्यथा
			ath10k_usb_rx_complete(ar, skb);
	पूर्ण
पूर्ण

#घोषणा ATH10K_USB_MAX_DIAG_CMD (माप(काष्ठा ath10k_usb_ctrl_diag_cmd_ग_लिखो))
#घोषणा ATH10K_USB_MAX_DIAG_RESP (माप(काष्ठा ath10k_usb_ctrl_diag_resp_पढ़ो))

अटल व्योम ath10k_usb_destroy(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_usb *ar_usb = ath10k_usb_priv(ar);

	ath10k_usb_flush_all(ar);
	ath10k_usb_cleanup_pipe_resources(ar);
	usb_set_पूर्णांकfdata(ar_usb->पूर्णांकerface, शून्य);

	kमुक्त(ar_usb->diag_cmd_buffer);
	kमुक्त(ar_usb->diag_resp_buffer);
पूर्ण

अटल पूर्णांक ath10k_usb_hअगर_start(काष्ठा ath10k *ar)
अणु
	पूर्णांक i;
	काष्ठा ath10k_usb *ar_usb = ath10k_usb_priv(ar);

	ath10k_usb_start_recv_pipes(ar);

	/* set the TX resource avail threshold क्रम each TX pipe */
	क्रम (i = ATH10K_USB_PIPE_TX_CTRL;
	     i <= ATH10K_USB_PIPE_TX_DATA_HP; i++) अणु
		ar_usb->pipes[i].urb_cnt_thresh =
		    ar_usb->pipes[i].urb_alloc / 2;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_usb_hअगर_tx_sg(काष्ठा ath10k *ar, u8 pipe_id,
				काष्ठा ath10k_hअगर_sg_item *items, पूर्णांक n_items)
अणु
	काष्ठा ath10k_usb *ar_usb = ath10k_usb_priv(ar);
	काष्ठा ath10k_usb_pipe *pipe = &ar_usb->pipes[pipe_id];
	काष्ठा ath10k_urb_context *urb_context;
	काष्ठा sk_buff *skb;
	काष्ठा urb *urb;
	पूर्णांक ret, i;

	क्रम (i = 0; i < n_items; i++) अणु
		urb_context = ath10k_usb_alloc_urb_from_pipe(pipe);
		अगर (!urb_context) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		skb = items[i].transfer_context;
		urb_context->skb = skb;

		urb = usb_alloc_urb(0, GFP_ATOMIC);
		अगर (!urb) अणु
			ret = -ENOMEM;
			जाओ err_मुक्त_urb_to_pipe;
		पूर्ण

		usb_fill_bulk_urb(urb,
				  ar_usb->udev,
				  pipe->usb_pipe_handle,
				  skb->data,
				  skb->len,
				  ath10k_usb_transmit_complete, urb_context);

		अगर (!(skb->len % pipe->max_packet_size)) अणु
			/* hit a max packet boundary on this pipe */
			urb->transfer_flags |= URB_ZERO_PACKET;
		पूर्ण

		usb_anchor_urb(urb, &pipe->urb_submitted);
		ret = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (ret) अणु
			ath10k_dbg(ar, ATH10K_DBG_USB_BULK,
				   "usb bulk transmit failed: %d\n", ret);
			usb_unanchor_urb(urb);
			usb_मुक्त_urb(urb);
			ret = -EINVAL;
			जाओ err_मुक्त_urb_to_pipe;
		पूर्ण

		usb_मुक्त_urb(urb);
	पूर्ण

	वापस 0;

err_मुक्त_urb_to_pipe:
	ath10k_usb_मुक्त_urb_to_pipe(urb_context->pipe, urb_context);
err:
	वापस ret;
पूर्ण

अटल व्योम ath10k_usb_hअगर_stop(काष्ठा ath10k *ar)
अणु
	ath10k_usb_flush_all(ar);
पूर्ण

अटल u16 ath10k_usb_hअगर_get_मुक्त_queue_number(काष्ठा ath10k *ar, u8 pipe_id)
अणु
	काष्ठा ath10k_usb *ar_usb = ath10k_usb_priv(ar);

	वापस ar_usb->pipes[pipe_id].urb_cnt;
पूर्ण

अटल पूर्णांक ath10k_usb_submit_ctrl_out(काष्ठा ath10k *ar,
				      u8 req, u16 value, u16 index, व्योम *data,
				      u32 size)
अणु
	काष्ठा ath10k_usb *ar_usb = ath10k_usb_priv(ar);
	u8 *buf = शून्य;
	पूर्णांक ret;

	अगर (size > 0) अणु
		buf = kmemdup(data, size, GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;
	पूर्ण

	/* note: अगर successful वापसs number of bytes transferred */
	ret = usb_control_msg(ar_usb->udev,
			      usb_sndctrlpipe(ar_usb->udev, 0),
			      req,
			      USB_सूची_OUT | USB_TYPE_VENDOR |
			      USB_RECIP_DEVICE, value, index, buf,
			      size, 1000);

	अगर (ret < 0) अणु
		ath10k_warn(ar, "Failed to submit usb control message: %d\n",
			    ret);
		kमुक्त(buf);
		वापस ret;
	पूर्ण

	kमुक्त(buf);

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_usb_submit_ctrl_in(काष्ठा ath10k *ar,
				     u8 req, u16 value, u16 index, व्योम *data,
				     u32 size)
अणु
	काष्ठा ath10k_usb *ar_usb = ath10k_usb_priv(ar);
	u8 *buf = शून्य;
	पूर्णांक ret;

	अगर (size > 0) अणु
		buf = kदो_स्मृति(size, GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;
	पूर्ण

	/* note: अगर successful वापसs number of bytes transferred */
	ret = usb_control_msg(ar_usb->udev,
			      usb_rcvctrlpipe(ar_usb->udev, 0),
			      req,
			      USB_सूची_IN | USB_TYPE_VENDOR |
			      USB_RECIP_DEVICE, value, index, buf,
			      size, 2 * HZ);

	अगर (ret < 0) अणु
		ath10k_warn(ar, "Failed to read usb control message: %d\n",
			    ret);
		kमुक्त(buf);
		वापस ret;
	पूर्ण

	स_नकल((u8 *)data, buf, size);

	kमुक्त(buf);

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_usb_ctrl_msg_exchange(काष्ठा ath10k *ar,
					u8 req_val, u8 *req_buf, u32 req_len,
					u8 resp_val, u8 *resp_buf,
					u32 *resp_len)
अणु
	पूर्णांक ret;

	/* send command */
	ret = ath10k_usb_submit_ctrl_out(ar, req_val, 0, 0,
					 req_buf, req_len);
	अगर (ret)
		जाओ err;

	/* get response */
	अगर (resp_buf) अणु
		ret = ath10k_usb_submit_ctrl_in(ar, resp_val, 0, 0,
						resp_buf, *resp_len);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_usb_hअगर_diag_पढ़ो(काष्ठा ath10k *ar, u32 address, व्योम *buf,
				    माप_प्रकार buf_len)
अणु
	काष्ठा ath10k_usb *ar_usb = ath10k_usb_priv(ar);
	काष्ठा ath10k_usb_ctrl_diag_cmd_पढ़ो *cmd;
	u32 resp_len;
	पूर्णांक ret;

	अगर (buf_len < माप(काष्ठा ath10k_usb_ctrl_diag_resp_पढ़ो))
		वापस -EINVAL;

	cmd = (काष्ठा ath10k_usb_ctrl_diag_cmd_पढ़ो *)ar_usb->diag_cmd_buffer;
	स_रखो(cmd, 0, माप(*cmd));
	cmd->cmd = ATH10K_USB_CTRL_DIAG_CC_READ;
	cmd->address = cpu_to_le32(address);
	resp_len = माप(काष्ठा ath10k_usb_ctrl_diag_resp_पढ़ो);

	ret = ath10k_usb_ctrl_msg_exchange(ar,
					   ATH10K_USB_CONTROL_REQ_DIAG_CMD,
					   (u8 *)cmd,
					   माप(*cmd),
					   ATH10K_USB_CONTROL_REQ_DIAG_RESP,
					   ar_usb->diag_resp_buffer, &resp_len);
	अगर (ret)
		वापस ret;

	अगर (resp_len != माप(काष्ठा ath10k_usb_ctrl_diag_resp_पढ़ो))
		वापस -EMSGSIZE;

	स_नकल(buf, ar_usb->diag_resp_buffer,
	       माप(काष्ठा ath10k_usb_ctrl_diag_resp_पढ़ो));

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_usb_hअगर_diag_ग_लिखो(काष्ठा ath10k *ar, u32 address,
				     स्थिर व्योम *data, पूर्णांक nbytes)
अणु
	काष्ठा ath10k_usb *ar_usb = ath10k_usb_priv(ar);
	काष्ठा ath10k_usb_ctrl_diag_cmd_ग_लिखो *cmd;
	पूर्णांक ret;

	अगर (nbytes != माप(cmd->value))
		वापस -EINVAL;

	cmd = (काष्ठा ath10k_usb_ctrl_diag_cmd_ग_लिखो *)ar_usb->diag_cmd_buffer;
	स_रखो(cmd, 0, माप(*cmd));
	cmd->cmd = cpu_to_le32(ATH10K_USB_CTRL_DIAG_CC_WRITE);
	cmd->address = cpu_to_le32(address);
	स_नकल(&cmd->value, data, nbytes);

	ret = ath10k_usb_ctrl_msg_exchange(ar,
					   ATH10K_USB_CONTROL_REQ_DIAG_CMD,
					   (u8 *)cmd,
					   माप(*cmd),
					   0, शून्य, शून्य);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_usb_bmi_exchange_msg(काष्ठा ath10k *ar,
				       व्योम *req, u32 req_len,
				       व्योम *resp, u32 *resp_len)
अणु
	पूर्णांक ret;

	अगर (req) अणु
		ret = ath10k_usb_submit_ctrl_out(ar,
						 ATH10K_USB_CONTROL_REQ_SEND_BMI_CMD,
						 0, 0, req, req_len);
		अगर (ret) अणु
			ath10k_warn(ar,
				    "unable to send the bmi data to the device: %d\n",
				    ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (resp) अणु
		ret = ath10k_usb_submit_ctrl_in(ar,
						ATH10K_USB_CONTROL_REQ_RECV_BMI_RESP,
						0, 0, resp, *resp_len);
		अगर (ret) अणु
			ath10k_warn(ar,
				    "Unable to read the bmi data from the device: %d\n",
				    ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath10k_usb_hअगर_get_शेष_pipe(काष्ठा ath10k *ar,
					    u8 *ul_pipe, u8 *dl_pipe)
अणु
	*ul_pipe = ATH10K_USB_PIPE_TX_CTRL;
	*dl_pipe = ATH10K_USB_PIPE_RX_CTRL;
पूर्ण

अटल पूर्णांक ath10k_usb_hअगर_map_service_to_pipe(काष्ठा ath10k *ar, u16 svc_id,
					      u8 *ul_pipe, u8 *dl_pipe)
अणु
	चयन (svc_id) अणु
	हाल ATH10K_HTC_SVC_ID_RSVD_CTRL:
	हाल ATH10K_HTC_SVC_ID_WMI_CONTROL:
		*ul_pipe = ATH10K_USB_PIPE_TX_CTRL;
		/* due to large control packets, shअगरt to data pipe */
		*dl_pipe = ATH10K_USB_PIPE_RX_DATA;
		अवरोध;
	हाल ATH10K_HTC_SVC_ID_HTT_DATA_MSG:
		*ul_pipe = ATH10K_USB_PIPE_TX_DATA_LP;
		/* Disable rxdata2 directly, it will be enabled
		 * अगर FW enable rxdata2
		 */
		*dl_pipe = ATH10K_USB_PIPE_RX_DATA;
		अवरोध;
	शेष:
		वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_usb_hअगर_घातer_up(काष्ठा ath10k *ar,
				   क्रमागत ath10k_firmware_mode fw_mode)
अणु
	वापस 0;
पूर्ण

अटल व्योम ath10k_usb_hअगर_घातer_करोwn(काष्ठा ath10k *ar)
अणु
	ath10k_usb_flush_all(ar);
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक ath10k_usb_hअगर_suspend(काष्ठा ath10k *ar)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक ath10k_usb_hअगर_resume(काष्ठा ath10k *ar)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा ath10k_hअगर_ops ath10k_usb_hअगर_ops = अणु
	.tx_sg			= ath10k_usb_hअगर_tx_sg,
	.diag_पढ़ो		= ath10k_usb_hअगर_diag_पढ़ो,
	.diag_ग_लिखो		= ath10k_usb_hअगर_diag_ग_लिखो,
	.exchange_bmi_msg	= ath10k_usb_bmi_exchange_msg,
	.start			= ath10k_usb_hअगर_start,
	.stop			= ath10k_usb_hअगर_stop,
	.map_service_to_pipe	= ath10k_usb_hअगर_map_service_to_pipe,
	.get_शेष_pipe	= ath10k_usb_hअगर_get_शेष_pipe,
	.get_मुक्त_queue_number	= ath10k_usb_hअगर_get_मुक्त_queue_number,
	.घातer_up		= ath10k_usb_hअगर_घातer_up,
	.घातer_करोwn		= ath10k_usb_hअगर_घातer_करोwn,
#अगर_घोषित CONFIG_PM
	.suspend		= ath10k_usb_hअगर_suspend,
	.resume			= ath10k_usb_hअगर_resume,
#पूर्ण_अगर
पूर्ण;

अटल u8 ath10k_usb_get_logical_pipe_num(u8 ep_address, पूर्णांक *urb_count)
अणु
	u8 pipe_num = ATH10K_USB_PIPE_INVALID;

	चयन (ep_address) अणु
	हाल ATH10K_USB_EP_ADDR_APP_CTRL_IN:
		pipe_num = ATH10K_USB_PIPE_RX_CTRL;
		*urb_count = RX_URB_COUNT;
		अवरोध;
	हाल ATH10K_USB_EP_ADDR_APP_DATA_IN:
		pipe_num = ATH10K_USB_PIPE_RX_DATA;
		*urb_count = RX_URB_COUNT;
		अवरोध;
	हाल ATH10K_USB_EP_ADDR_APP_INT_IN:
		pipe_num = ATH10K_USB_PIPE_RX_INT;
		*urb_count = RX_URB_COUNT;
		अवरोध;
	हाल ATH10K_USB_EP_ADDR_APP_DATA2_IN:
		pipe_num = ATH10K_USB_PIPE_RX_DATA2;
		*urb_count = RX_URB_COUNT;
		अवरोध;
	हाल ATH10K_USB_EP_ADDR_APP_CTRL_OUT:
		pipe_num = ATH10K_USB_PIPE_TX_CTRL;
		*urb_count = TX_URB_COUNT;
		अवरोध;
	हाल ATH10K_USB_EP_ADDR_APP_DATA_LP_OUT:
		pipe_num = ATH10K_USB_PIPE_TX_DATA_LP;
		*urb_count = TX_URB_COUNT;
		अवरोध;
	हाल ATH10K_USB_EP_ADDR_APP_DATA_MP_OUT:
		pipe_num = ATH10K_USB_PIPE_TX_DATA_MP;
		*urb_count = TX_URB_COUNT;
		अवरोध;
	हाल ATH10K_USB_EP_ADDR_APP_DATA_HP_OUT:
		pipe_num = ATH10K_USB_PIPE_TX_DATA_HP;
		*urb_count = TX_URB_COUNT;
		अवरोध;
	शेष:
		/* note: there may be endpoपूर्णांकs not currently used */
		अवरोध;
	पूर्ण

	वापस pipe_num;
पूर्ण

अटल पूर्णांक ath10k_usb_alloc_pipe_resources(काष्ठा ath10k *ar,
					   काष्ठा ath10k_usb_pipe *pipe,
					   पूर्णांक urb_cnt)
अणु
	काष्ठा ath10k_urb_context *urb_context;
	पूर्णांक i;

	INIT_LIST_HEAD(&pipe->urb_list_head);
	init_usb_anchor(&pipe->urb_submitted);

	क्रम (i = 0; i < urb_cnt; i++) अणु
		urb_context = kzalloc(माप(*urb_context), GFP_KERNEL);
		अगर (!urb_context)
			वापस -ENOMEM;

		urb_context->pipe = pipe;

		/* we are only allocate the urb contexts here, the actual URB
		 * is allocated from the kernel as needed to करो a transaction
		 */
		pipe->urb_alloc++;
		ath10k_usb_मुक्त_urb_to_pipe(pipe, urb_context);
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_USB,
		   "usb alloc resources lpipe %d hpipe 0x%x urbs %d\n",
		   pipe->logical_pipe_num, pipe->usb_pipe_handle,
		   pipe->urb_alloc);

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_usb_setup_pipe_resources(काष्ठा ath10k *ar,
					   काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा ath10k_usb *ar_usb = ath10k_usb_priv(ar);
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc = पूर्णांकerface->cur_altsetting;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा ath10k_usb_pipe *pipe;
	पूर्णांक ret, i, urbcount;
	u8 pipe_num;

	ath10k_dbg(ar, ATH10K_DBG_USB, "usb setting up pipes using interface\n");

	/* walk descriptors and setup pipes */
	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; ++i) अणु
		endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[i].desc;

		अगर (ATH10K_USB_IS_BULK_EP(endpoपूर्णांक->bmAttributes)) अणु
			ath10k_dbg(ar, ATH10K_DBG_USB,
				   "usb %s bulk ep 0x%2.2x maxpktsz %d\n",
				   ATH10K_USB_IS_सूची_IN
				   (endpoपूर्णांक->bEndpoपूर्णांकAddress) ?
				   "rx" : "tx", endpoपूर्णांक->bEndpoपूर्णांकAddress,
				   le16_to_cpu(endpoपूर्णांक->wMaxPacketSize));
		पूर्ण अन्यथा अगर (ATH10K_USB_IS_INT_EP(endpoपूर्णांक->bmAttributes)) अणु
			ath10k_dbg(ar, ATH10K_DBG_USB,
				   "usb %s int ep 0x%2.2x maxpktsz %d interval %d\n",
				   ATH10K_USB_IS_सूची_IN
				   (endpoपूर्णांक->bEndpoपूर्णांकAddress) ?
				   "rx" : "tx", endpoपूर्णांक->bEndpoपूर्णांकAddress,
				   le16_to_cpu(endpoपूर्णांक->wMaxPacketSize),
				   endpoपूर्णांक->bInterval);
		पूर्ण अन्यथा अगर (ATH10K_USB_IS_ISOC_EP(endpoपूर्णांक->bmAttributes)) अणु
			/* TODO क्रम ISO */
			ath10k_dbg(ar, ATH10K_DBG_USB,
				   "usb %s isoc ep 0x%2.2x maxpktsz %d interval %d\n",
				   ATH10K_USB_IS_सूची_IN
				   (endpoपूर्णांक->bEndpoपूर्णांकAddress) ?
				   "rx" : "tx", endpoपूर्णांक->bEndpoपूर्णांकAddress,
				   le16_to_cpu(endpoपूर्णांक->wMaxPacketSize),
				   endpoपूर्णांक->bInterval);
		पूर्ण
		urbcount = 0;

		pipe_num =
		    ath10k_usb_get_logical_pipe_num(endpoपूर्णांक->bEndpoपूर्णांकAddress,
						    &urbcount);
		अगर (pipe_num == ATH10K_USB_PIPE_INVALID)
			जारी;

		pipe = &ar_usb->pipes[pipe_num];
		अगर (pipe->ar_usb)
			/* hmmm..pipe was alपढ़ोy setup */
			जारी;

		pipe->ar_usb = ar_usb;
		pipe->logical_pipe_num = pipe_num;
		pipe->ep_address = endpoपूर्णांक->bEndpoपूर्णांकAddress;
		pipe->max_packet_size = le16_to_cpu(endpoपूर्णांक->wMaxPacketSize);

		अगर (ATH10K_USB_IS_BULK_EP(endpoपूर्णांक->bmAttributes)) अणु
			अगर (ATH10K_USB_IS_सूची_IN(pipe->ep_address)) अणु
				pipe->usb_pipe_handle =
				    usb_rcvbulkpipe(ar_usb->udev,
						    pipe->ep_address);
			पूर्ण अन्यथा अणु
				pipe->usb_pipe_handle =
				    usb_sndbulkpipe(ar_usb->udev,
						    pipe->ep_address);
			पूर्ण
		पूर्ण अन्यथा अगर (ATH10K_USB_IS_INT_EP(endpoपूर्णांक->bmAttributes)) अणु
			अगर (ATH10K_USB_IS_सूची_IN(pipe->ep_address)) अणु
				pipe->usb_pipe_handle =
				    usb_rcvपूर्णांकpipe(ar_usb->udev,
						   pipe->ep_address);
			पूर्ण अन्यथा अणु
				pipe->usb_pipe_handle =
				    usb_sndपूर्णांकpipe(ar_usb->udev,
						   pipe->ep_address);
			पूर्ण
		पूर्ण अन्यथा अगर (ATH10K_USB_IS_ISOC_EP(endpoपूर्णांक->bmAttributes)) अणु
			/* TODO क्रम ISO */
			अगर (ATH10K_USB_IS_सूची_IN(pipe->ep_address)) अणु
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

		अगर (!ATH10K_USB_IS_सूची_IN(pipe->ep_address))
			pipe->flags |= ATH10K_USB_PIPE_FLAG_TX;

		ret = ath10k_usb_alloc_pipe_resources(ar, pipe, urbcount);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_usb_create(काष्ठा ath10k *ar,
			     काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा ath10k_usb *ar_usb = ath10k_usb_priv(ar);
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा ath10k_usb_pipe *pipe;
	पूर्णांक ret, i;

	usb_set_पूर्णांकfdata(पूर्णांकerface, ar_usb);
	spin_lock_init(&ar_usb->cs_lock);
	ar_usb->udev = dev;
	ar_usb->पूर्णांकerface = पूर्णांकerface;

	क्रम (i = 0; i < ATH10K_USB_PIPE_MAX; i++) अणु
		pipe = &ar_usb->pipes[i];
		INIT_WORK(&pipe->io_complete_work,
			  ath10k_usb_io_comp_work);
		skb_queue_head_init(&pipe->io_comp_queue);
	पूर्ण

	ar_usb->diag_cmd_buffer = kzalloc(ATH10K_USB_MAX_DIAG_CMD, GFP_KERNEL);
	अगर (!ar_usb->diag_cmd_buffer) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ar_usb->diag_resp_buffer = kzalloc(ATH10K_USB_MAX_DIAG_RESP,
					   GFP_KERNEL);
	अगर (!ar_usb->diag_resp_buffer) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = ath10k_usb_setup_pipe_resources(ar, पूर्णांकerface);
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	ath10k_usb_destroy(ar);
	वापस ret;
पूर्ण

/* ath10k usb driver रेजिस्टरed functions */
अटल पूर्णांक ath10k_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			    स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा ath10k *ar;
	काष्ठा ath10k_usb *ar_usb;
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	पूर्णांक ret, venकरोr_id, product_id;
	क्रमागत ath10k_hw_rev hw_rev;
	काष्ठा ath10k_bus_params bus_params = अणुपूर्ण;

	/* Assumption: All USB based chipsets (so far) are QCA9377 based.
	 * If there will be newer chipsets that करोes not use the hw reg
	 * setup as defined in qca6174_regs and qca6174_values, this
	 * assumption is no दीर्घer valid and hw_rev must be setup dअगरferently
	 * depending on chipset.
	 */
	hw_rev = ATH10K_HW_QCA9377;

	ar = ath10k_core_create(माप(*ar_usb), &dev->dev, ATH10K_BUS_USB,
				hw_rev, &ath10k_usb_hअगर_ops);
	अगर (!ar) अणु
		dev_err(&dev->dev, "failed to allocate core\n");
		वापस -ENOMEM;
	पूर्ण

	usb_get_dev(dev);
	venकरोr_id = le16_to_cpu(dev->descriptor.idVenकरोr);
	product_id = le16_to_cpu(dev->descriptor.idProduct);

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "usb new func vendor 0x%04x product 0x%04x\n",
		   venकरोr_id, product_id);

	ar_usb = ath10k_usb_priv(ar);
	ret = ath10k_usb_create(ar, पूर्णांकerface);
	अगर (ret)
		जाओ err;
	ar_usb->ar = ar;

	ar->dev_id = product_id;
	ar->id.venकरोr = venकरोr_id;
	ar->id.device = product_id;

	bus_params.dev_type = ATH10K_DEV_TYPE_HL;
	/* TODO: करोn't know yet how to get chip_id with USB */
	bus_params.chip_id = 0;
	ret = ath10k_core_रेजिस्टर(ar, &bus_params);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to register driver core: %d\n", ret);
		जाओ err_usb_destroy;
	पूर्ण

	/* TODO: हटाओ this once USB support is fully implemented */
	ath10k_warn(ar, "Warning: ath10k USB support is incomplete, don't expect anything to work!\n");

	वापस 0;

err_usb_destroy:
	ath10k_usb_destroy(ar);

err:
	ath10k_core_destroy(ar);

	usb_put_dev(dev);

	वापस ret;
पूर्ण

अटल व्योम ath10k_usb_हटाओ(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा ath10k_usb *ar_usb;

	ar_usb = usb_get_पूर्णांकfdata(पूर्णांकerface);
	अगर (!ar_usb)
		वापस;

	ath10k_core_unरेजिस्टर(ar_usb->ar);
	ath10k_usb_destroy(ar_usb->ar);
	usb_put_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));
	ath10k_core_destroy(ar_usb->ar);
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक ath10k_usb_pm_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
				 pm_message_t message)
अणु
	काष्ठा ath10k_usb *ar_usb = usb_get_पूर्णांकfdata(पूर्णांकerface);

	ath10k_usb_flush_all(ar_usb->ar);
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_usb_pm_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा ath10k_usb *ar_usb = usb_get_पूर्णांकfdata(पूर्णांकerface);
	काष्ठा ath10k *ar = ar_usb->ar;

	ath10k_usb_post_recv_transfers(ar,
				       &ar_usb->pipes[ATH10K_USB_PIPE_RX_DATA]);

	वापस 0;
पूर्ण

#अन्यथा

#घोषणा ath10k_usb_pm_suspend शून्य
#घोषणा ath10k_usb_pm_resume शून्य

#पूर्ण_अगर

/* table of devices that work with this driver */
अटल काष्ठा usb_device_id ath10k_usb_ids[] = अणु
	अणुUSB_DEVICE(0x13b1, 0x0042)पूर्ण, /* Linksys WUSB6100M */
	अणु /* Terminating entry */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(usb, ath10k_usb_ids);

अटल काष्ठा usb_driver ath10k_usb_driver = अणु
	.name = "ath10k_usb",
	.probe = ath10k_usb_probe,
	.suspend = ath10k_usb_pm_suspend,
	.resume = ath10k_usb_pm_resume,
	.disconnect = ath10k_usb_हटाओ,
	.id_table = ath10k_usb_ids,
	.supports_स्वतःsuspend = true,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(ath10k_usb_driver);

MODULE_AUTHOR("Atheros Communications, Inc.");
MODULE_DESCRIPTION("Driver support for Qualcomm Atheros 802.11ac WLAN USB devices");
MODULE_LICENSE("Dual BSD/GPL");
