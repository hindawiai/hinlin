<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम NXP PN533 NFC Chip - USB transport layer
 *
 * Copyright (C) 2011 Instituto Nokia de Tecnologia
 * Copyright (C) 2012-2013 Tieto Poland
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/nfc.h>
#समावेश <linux/netdevice.h>
#समावेश <net/nfc/nfc.h>
#समावेश "pn533.h"

#घोषणा VERSION "0.1"

#घोषणा PN533_VENDOR_ID 0x4CC
#घोषणा PN533_PRODUCT_ID 0x2533

#घोषणा SCM_VENDOR_ID 0x4E6
#घोषणा SCL3711_PRODUCT_ID 0x5591

#घोषणा SONY_VENDOR_ID         0x054c
#घोषणा PASORI_PRODUCT_ID      0x02e1

#घोषणा ACS_VENDOR_ID 0x072f
#घोषणा ACR122U_PRODUCT_ID 0x2200

अटल स्थिर काष्ठा usb_device_id pn533_usb_table[] = अणु
	अणु USB_DEVICE(PN533_VENDOR_ID, PN533_PRODUCT_ID),
	  .driver_info = PN533_DEVICE_STD पूर्ण,
	अणु USB_DEVICE(SCM_VENDOR_ID, SCL3711_PRODUCT_ID),
	  .driver_info = PN533_DEVICE_STD पूर्ण,
	अणु USB_DEVICE(SONY_VENDOR_ID, PASORI_PRODUCT_ID),
	  .driver_info = PN533_DEVICE_PASORI पूर्ण,
	अणु USB_DEVICE(ACS_VENDOR_ID, ACR122U_PRODUCT_ID),
	  .driver_info = PN533_DEVICE_ACR122U पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, pn533_usb_table);

काष्ठा pn533_usb_phy अणु
	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;

	काष्ठा urb *out_urb;
	काष्ठा urb *in_urb;

	काष्ठा urb *ack_urb;
	u8 *ack_buffer;

	काष्ठा pn533 *priv;
पूर्ण;

अटल व्योम pn533_recv_response(काष्ठा urb *urb)
अणु
	काष्ठा pn533_usb_phy *phy = urb->context;
	काष्ठा sk_buff *skb = शून्य;

	अगर (!urb->status) अणु
		skb = alloc_skb(urb->actual_length, GFP_ATOMIC);
		अगर (!skb) अणु
			nfc_err(&phy->udev->dev, "failed to alloc memory\n");
		पूर्ण अन्यथा अणु
			skb_put_data(skb, urb->transfer_buffer,
				     urb->actual_length);
		पूर्ण
	पूर्ण

	pn533_recv_frame(phy->priv, skb, urb->status);
पूर्ण

अटल पूर्णांक pn533_submit_urb_क्रम_response(काष्ठा pn533_usb_phy *phy, gfp_t flags)
अणु
	phy->in_urb->complete = pn533_recv_response;

	वापस usb_submit_urb(phy->in_urb, flags);
पूर्ण

अटल व्योम pn533_recv_ack(काष्ठा urb *urb)
अणु
	काष्ठा pn533_usb_phy *phy = urb->context;
	काष्ठा pn533 *priv = phy->priv;
	काष्ठा pn533_cmd *cmd = priv->cmd;
	काष्ठा pn533_std_frame *in_frame;
	पूर्णांक rc;

	cmd->status = urb->status;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध; /* success */
	हाल -ECONNRESET:
	हाल -ENOENT:
		dev_dbg(&phy->udev->dev,
			"The urb has been stopped (status %d)\n",
			urb->status);
		जाओ sched_wq;
	हाल -ESHUTDOWN:
	शेष:
		nfc_err(&phy->udev->dev,
			"Urb failure (status %d)\n", urb->status);
		जाओ sched_wq;
	पूर्ण

	in_frame = phy->in_urb->transfer_buffer;

	अगर (!pn533_rx_frame_is_ack(in_frame)) अणु
		nfc_err(&phy->udev->dev, "Received an invalid ack\n");
		cmd->status = -EIO;
		जाओ sched_wq;
	पूर्ण

	rc = pn533_submit_urb_क्रम_response(phy, GFP_ATOMIC);
	अगर (rc) अणु
		nfc_err(&phy->udev->dev,
			"usb_submit_urb failed with result %d\n", rc);
		cmd->status = rc;
		जाओ sched_wq;
	पूर्ण

	वापस;

sched_wq:
	queue_work(priv->wq, &priv->cmd_complete_work);
पूर्ण

अटल पूर्णांक pn533_submit_urb_क्रम_ack(काष्ठा pn533_usb_phy *phy, gfp_t flags)
अणु
	phy->in_urb->complete = pn533_recv_ack;

	वापस usb_submit_urb(phy->in_urb, flags);
पूर्ण

अटल पूर्णांक pn533_usb_send_ack(काष्ठा pn533 *dev, gfp_t flags)
अणु
	काष्ठा pn533_usb_phy *phy = dev->phy;
	अटल स्थिर u8 ack[6] = अणु0x00, 0x00, 0xff, 0x00, 0xff, 0x00पूर्ण;
	/* spec 7.1.1.3:  Preamble, SoPC (2), ACK Code (2), Postamble */

	अगर (!phy->ack_buffer) अणु
		phy->ack_buffer = kmemdup(ack, माप(ack), flags);
		अगर (!phy->ack_buffer)
			वापस -ENOMEM;
	पूर्ण

	phy->ack_urb->transfer_buffer = phy->ack_buffer;
	phy->ack_urb->transfer_buffer_length = माप(ack);
	वापस usb_submit_urb(phy->ack_urb, flags);
पूर्ण

अटल पूर्णांक pn533_usb_send_frame(काष्ठा pn533 *dev,
				काष्ठा sk_buff *out)
अणु
	काष्ठा pn533_usb_phy *phy = dev->phy;
	पूर्णांक rc;

	अगर (phy->priv == शून्य)
		phy->priv = dev;

	phy->out_urb->transfer_buffer = out->data;
	phy->out_urb->transfer_buffer_length = out->len;

	prपूर्णांक_hex_dump_debug("PN533 TX: ", DUMP_PREFIX_NONE, 16, 1,
			     out->data, out->len, false);

	rc = usb_submit_urb(phy->out_urb, GFP_KERNEL);
	अगर (rc)
		वापस rc;

	अगर (dev->protocol_type == PN533_PROTO_REQ_RESP) अणु
		/* request क्रम response क्रम sent packet directly */
		rc = pn533_submit_urb_क्रम_response(phy, GFP_KERNEL);
		अगर (rc)
			जाओ error;
	पूर्ण अन्यथा अगर (dev->protocol_type == PN533_PROTO_REQ_ACK_RESP) अणु
		/* request क्रम ACK अगर that's the हाल */
		rc = pn533_submit_urb_क्रम_ack(phy, GFP_KERNEL);
		अगर (rc)
			जाओ error;
	पूर्ण

	वापस 0;

error:
	usb_unlink_urb(phy->out_urb);
	वापस rc;
पूर्ण

अटल व्योम pn533_usb_पात_cmd(काष्ठा pn533 *dev, gfp_t flags)
अणु
	काष्ठा pn533_usb_phy *phy = dev->phy;

	/* ACR122U करोes not support any command which पातs last
	 * issued command i.e. as ACK क्रम standard PN533. Additionally,
	 * it behaves stange, sending broken or incorrect responses,
	 * when we cancel urb beक्रमe the chip will send response.
	 */
	अगर (dev->device_type == PN533_DEVICE_ACR122U)
		वापस;

	/* An ack will cancel the last issued command */
	pn533_usb_send_ack(dev, flags);

	/* cancel the urb request */
	usb_समाप्त_urb(phy->in_urb);
पूर्ण

/* ACR122 specअगरic काष्ठाs and functions */

/* ACS ACR122 pn533 frame definitions */
#घोषणा PN533_ACR122_TX_FRAME_HEADER_LEN (माप(काष्ठा pn533_acr122_tx_frame) \
					  + 2)
#घोषणा PN533_ACR122_TX_FRAME_TAIL_LEN 0
#घोषणा PN533_ACR122_RX_FRAME_HEADER_LEN (माप(काष्ठा pn533_acr122_rx_frame) \
					  + 2)
#घोषणा PN533_ACR122_RX_FRAME_TAIL_LEN 2
#घोषणा PN533_ACR122_FRAME_MAX_PAYLOAD_LEN PN533_STD_FRAME_MAX_PAYLOAD_LEN

/* CCID messages types */
#घोषणा PN533_ACR122_PC_TO_RDR_ICCPOWERON 0x62
#घोषणा PN533_ACR122_PC_TO_RDR_ESCAPE 0x6B

#घोषणा PN533_ACR122_RDR_TO_PC_ESCAPE 0x83


काष्ठा pn533_acr122_ccid_hdr अणु
	u8 type;
	u32 datalen;
	u8 slot;
	u8 seq;

	/*
	 * 3 msg specअगरic bytes or status, error and 1 specअगरic
	 * byte क्रम reposnse msg
	 */
	u8 params[3];
	u8 data[]; /* payload */
पूर्ण __packed;

काष्ठा pn533_acr122_apdu_hdr अणु
	u8 class;
	u8 ins;
	u8 p1;
	u8 p2;
पूर्ण __packed;

काष्ठा pn533_acr122_tx_frame अणु
	काष्ठा pn533_acr122_ccid_hdr ccid;
	काष्ठा pn533_acr122_apdu_hdr apdu;
	u8 datalen;
	u8 data[]; /* pn533 frame: TFI ... */
पूर्ण __packed;

काष्ठा pn533_acr122_rx_frame अणु
	काष्ठा pn533_acr122_ccid_hdr ccid;
	u8 data[]; /* pn533 frame : TFI ... */
पूर्ण __packed;

अटल व्योम pn533_acr122_tx_frame_init(व्योम *_frame, u8 cmd_code)
अणु
	काष्ठा pn533_acr122_tx_frame *frame = _frame;

	frame->ccid.type = PN533_ACR122_PC_TO_RDR_ESCAPE;
	/* माप(apdu_hdr) + माप(datalen) */
	frame->ccid.datalen = माप(frame->apdu) + 1;
	frame->ccid.slot = 0;
	frame->ccid.seq = 0;
	frame->ccid.params[0] = 0;
	frame->ccid.params[1] = 0;
	frame->ccid.params[2] = 0;

	frame->data[0] = PN533_STD_FRAME_सूची_OUT;
	frame->data[1] = cmd_code;
	frame->datalen = 2;  /* data[0] + data[1] */

	frame->apdu.class = 0xFF;
	frame->apdu.ins = 0;
	frame->apdu.p1 = 0;
	frame->apdu.p2 = 0;
पूर्ण

अटल व्योम pn533_acr122_tx_frame_finish(व्योम *_frame)
अणु
	काष्ठा pn533_acr122_tx_frame *frame = _frame;

	frame->ccid.datalen += frame->datalen;
पूर्ण

अटल व्योम pn533_acr122_tx_update_payload_len(व्योम *_frame, पूर्णांक len)
अणु
	काष्ठा pn533_acr122_tx_frame *frame = _frame;

	frame->datalen += len;
पूर्ण

अटल bool pn533_acr122_is_rx_frame_valid(व्योम *_frame, काष्ठा pn533 *dev)
अणु
	काष्ठा pn533_acr122_rx_frame *frame = _frame;

	अगर (frame->ccid.type != 0x83)
		वापस false;

	अगर (!frame->ccid.datalen)
		वापस false;

	अगर (frame->data[frame->ccid.datalen - 2] == 0x63)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक pn533_acr122_rx_frame_size(व्योम *frame)
अणु
	काष्ठा pn533_acr122_rx_frame *f = frame;

	/* f->ccid.datalen alपढ़ोy includes tail length */
	वापस माप(काष्ठा pn533_acr122_rx_frame) + f->ccid.datalen;
पूर्ण

अटल u8 pn533_acr122_get_cmd_code(व्योम *frame)
अणु
	काष्ठा pn533_acr122_rx_frame *f = frame;

	वापस PN533_FRAME_CMD(f);
पूर्ण

अटल काष्ठा pn533_frame_ops pn533_acr122_frame_ops = अणु
	.tx_frame_init = pn533_acr122_tx_frame_init,
	.tx_frame_finish = pn533_acr122_tx_frame_finish,
	.tx_update_payload_len = pn533_acr122_tx_update_payload_len,
	.tx_header_len = PN533_ACR122_TX_FRAME_HEADER_LEN,
	.tx_tail_len = PN533_ACR122_TX_FRAME_TAIL_LEN,

	.rx_is_frame_valid = pn533_acr122_is_rx_frame_valid,
	.rx_header_len = PN533_ACR122_RX_FRAME_HEADER_LEN,
	.rx_tail_len = PN533_ACR122_RX_FRAME_TAIL_LEN,
	.rx_frame_size = pn533_acr122_rx_frame_size,

	.max_payload_len = PN533_ACR122_FRAME_MAX_PAYLOAD_LEN,
	.get_cmd_code = pn533_acr122_get_cmd_code,
पूर्ण;

काष्ठा pn533_acr122_घातeron_rdr_arg अणु
	पूर्णांक rc;
	काष्ठा completion करोne;
पूर्ण;

अटल व्योम pn533_acr122_घातeron_rdr_resp(काष्ठा urb *urb)
अणु
	काष्ठा pn533_acr122_घातeron_rdr_arg *arg = urb->context;

	dev_dbg(&urb->dev->dev, "%s\n", __func__);

	prपूर्णांक_hex_dump_debug("ACR122 RX: ", DUMP_PREFIX_NONE, 16, 1,
		       urb->transfer_buffer, urb->transfer_buffer_length,
		       false);

	arg->rc = urb->status;
	complete(&arg->करोne);
पूर्ण

अटल पूर्णांक pn533_acr122_घातeron_rdr(काष्ठा pn533_usb_phy *phy)
अणु
	/* Power on th पढ़ोer (CCID cmd) */
	u8 cmd[10] = अणुPN533_ACR122_PC_TO_RDR_ICCPOWERON,
		      0, 0, 0, 0, 0, 0, 3, 0, 0पूर्ण;
	अक्षर *buffer;
	पूर्णांक transferred;
	पूर्णांक rc;
	व्योम *cntx;
	काष्ठा pn533_acr122_घातeron_rdr_arg arg;

	dev_dbg(&phy->udev->dev, "%s\n", __func__);

	buffer = kmemdup(cmd, माप(cmd), GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	init_completion(&arg.करोne);
	cntx = phy->in_urb->context;  /* backup context */

	phy->in_urb->complete = pn533_acr122_घातeron_rdr_resp;
	phy->in_urb->context = &arg;

	prपूर्णांक_hex_dump_debug("ACR122 TX: ", DUMP_PREFIX_NONE, 16, 1,
		       cmd, माप(cmd), false);

	rc = usb_bulk_msg(phy->udev, phy->out_urb->pipe, buffer, माप(cmd),
			  &transferred, 5000);
	kमुक्त(buffer);
	अगर (rc || (transferred != माप(cmd))) अणु
		nfc_err(&phy->udev->dev,
			"Reader power on cmd error %d\n", rc);
		वापस rc;
	पूर्ण

	rc =  usb_submit_urb(phy->in_urb, GFP_KERNEL);
	अगर (rc) अणु
		nfc_err(&phy->udev->dev,
			"Can't submit reader poweron cmd response %d\n", rc);
		वापस rc;
	पूर्ण

	रुको_क्रम_completion(&arg.करोne);
	phy->in_urb->context = cntx; /* restore context */

	वापस arg.rc;
पूर्ण

अटल व्योम pn533_send_complete(काष्ठा urb *urb)
अणु
	काष्ठा pn533_usb_phy *phy = urb->context;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध; /* success */
	हाल -ECONNRESET:
	हाल -ENOENT:
		dev_dbg(&phy->udev->dev,
			"The urb has been stopped (status %d)\n",
			urb->status);
		अवरोध;
	हाल -ESHUTDOWN:
	शेष:
		nfc_err(&phy->udev->dev,
			"Urb failure (status %d)\n",
			urb->status);
	पूर्ण
पूर्ण

अटल काष्ठा pn533_phy_ops usb_phy_ops = अणु
	.send_frame = pn533_usb_send_frame,
	.send_ack = pn533_usb_send_ack,
	.पात_cmd = pn533_usb_पात_cmd,
पूर्ण;

अटल पूर्णांक pn533_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा pn533 *priv;
	काष्ठा pn533_usb_phy *phy;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	पूर्णांक in_endpoपूर्णांक = 0;
	पूर्णांक out_endpoपूर्णांक = 0;
	पूर्णांक rc = -ENOMEM;
	पूर्णांक i;
	u32 protocols;
	क्रमागत pn533_protocol_type protocol_type = PN533_PROTO_REQ_ACK_RESP;
	काष्ठा pn533_frame_ops *fops = शून्य;
	अचिन्हित अक्षर *in_buf;
	पूर्णांक in_buf_len = PN533_EXT_FRAME_HEADER_LEN +
			 PN533_STD_FRAME_MAX_PAYLOAD_LEN +
			 PN533_STD_FRAME_TAIL_LEN;

	phy = devm_kzalloc(&पूर्णांकerface->dev, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	in_buf = kzalloc(in_buf_len, GFP_KERNEL);
	अगर (!in_buf)
		वापस -ENOMEM;

	phy->udev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));
	phy->पूर्णांकerface = पूर्णांकerface;

	अगरace_desc = पूर्णांकerface->cur_altsetting;
	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; ++i) अणु
		endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[i].desc;

		अगर (!in_endpoपूर्णांक && usb_endpoपूर्णांक_is_bulk_in(endpoपूर्णांक))
			in_endpoपूर्णांक = endpoपूर्णांक->bEndpoपूर्णांकAddress;

		अगर (!out_endpoपूर्णांक && usb_endpoपूर्णांक_is_bulk_out(endpoपूर्णांक))
			out_endpoपूर्णांक = endpoपूर्णांक->bEndpoपूर्णांकAddress;
	पूर्ण

	अगर (!in_endpoपूर्णांक || !out_endpoपूर्णांक) अणु
		nfc_err(&पूर्णांकerface->dev,
			"Could not find bulk-in or bulk-out endpoint\n");
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	phy->in_urb = usb_alloc_urb(0, GFP_KERNEL);
	phy->out_urb = usb_alloc_urb(0, GFP_KERNEL);
	phy->ack_urb = usb_alloc_urb(0, GFP_KERNEL);

	अगर (!phy->in_urb || !phy->out_urb || !phy->ack_urb)
		जाओ error;

	usb_fill_bulk_urb(phy->in_urb, phy->udev,
			  usb_rcvbulkpipe(phy->udev, in_endpoपूर्णांक),
			  in_buf, in_buf_len, शून्य, phy);

	usb_fill_bulk_urb(phy->out_urb, phy->udev,
			  usb_sndbulkpipe(phy->udev, out_endpoपूर्णांक),
			  शून्य, 0, pn533_send_complete, phy);
	usb_fill_bulk_urb(phy->ack_urb, phy->udev,
			  usb_sndbulkpipe(phy->udev, out_endpoपूर्णांक),
			  शून्य, 0, pn533_send_complete, phy);

	चयन (id->driver_info) अणु
	हाल PN533_DEVICE_STD:
		protocols = PN533_ALL_PROTOCOLS;
		अवरोध;

	हाल PN533_DEVICE_PASORI:
		protocols = PN533_NO_TYPE_B_PROTOCOLS;
		अवरोध;

	हाल PN533_DEVICE_ACR122U:
		protocols = PN533_NO_TYPE_B_PROTOCOLS;
		fops = &pn533_acr122_frame_ops;
		protocol_type = PN533_PROTO_REQ_RESP;

		rc = pn533_acr122_घातeron_rdr(phy);
		अगर (rc < 0) अणु
			nfc_err(&पूर्णांकerface->dev,
				"Couldn't poweron the reader (error %d)\n", rc);
			जाओ error;
		पूर्ण
		अवरोध;

	शेष:
		nfc_err(&पूर्णांकerface->dev, "Unknown device type %lu\n",
			id->driver_info);
		rc = -EINVAL;
		जाओ error;
	पूर्ण

	priv = pn53x_common_init(id->driver_info, protocol_type,
					phy, &usb_phy_ops, fops,
					&phy->udev->dev);

	अगर (IS_ERR(priv)) अणु
		rc = PTR_ERR(priv);
		जाओ error;
	पूर्ण

	phy->priv = priv;

	rc = pn533_finalize_setup(priv);
	अगर (rc)
		जाओ err_clean;

	usb_set_पूर्णांकfdata(पूर्णांकerface, phy);
	rc = pn53x_रेजिस्टर_nfc(priv, protocols, &पूर्णांकerface->dev);
	अगर (rc)
		जाओ err_clean;

	वापस 0;

err_clean:
	pn53x_common_clean(priv);
error:
	usb_समाप्त_urb(phy->in_urb);
	usb_समाप्त_urb(phy->out_urb);
	usb_समाप्त_urb(phy->ack_urb);

	usb_मुक्त_urb(phy->in_urb);
	usb_मुक्त_urb(phy->out_urb);
	usb_मुक्त_urb(phy->ack_urb);
	usb_put_dev(phy->udev);
	kमुक्त(in_buf);
	kमुक्त(phy->ack_buffer);

	वापस rc;
पूर्ण

अटल व्योम pn533_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा pn533_usb_phy *phy = usb_get_पूर्णांकfdata(पूर्णांकerface);

	अगर (!phy)
		वापस;

	pn53x_unरेजिस्टर_nfc(phy->priv);
	pn53x_common_clean(phy->priv);

	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	usb_समाप्त_urb(phy->in_urb);
	usb_समाप्त_urb(phy->out_urb);
	usb_समाप्त_urb(phy->ack_urb);

	kमुक्त(phy->in_urb->transfer_buffer);
	usb_मुक्त_urb(phy->in_urb);
	usb_मुक्त_urb(phy->out_urb);
	usb_मुक्त_urb(phy->ack_urb);
	kमुक्त(phy->ack_buffer);

	nfc_info(&पूर्णांकerface->dev, "NXP PN533 NFC device disconnected\n");
पूर्ण

अटल काष्ठा usb_driver pn533_usb_driver = अणु
	.name =		"pn533_usb",
	.probe =	pn533_usb_probe,
	.disconnect =	pn533_usb_disconnect,
	.id_table =	pn533_usb_table,
पूर्ण;

module_usb_driver(pn533_usb_driver);

MODULE_AUTHOR("Lauro Ramos Venancio <lauro.venancio@openbossa.org>");
MODULE_AUTHOR("Aloisio Almeida Jr <aloisio.almeida@openbossa.org>");
MODULE_AUTHOR("Waldemar Rymarkiewicz <waldemar.rymarkiewicz@tieto.com>");
MODULE_DESCRIPTION("PN533 USB driver ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
