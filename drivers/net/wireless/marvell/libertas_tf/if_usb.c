<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2008, cozybit Inc.
 *  Copyright (C) 2003-2006, Marvell International Ltd.
 */
#घोषणा DRV_NAME "lbtf_usb"

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "libertas_tf.h"
#समावेश "if_usb.h"

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#घोषणा INSANEDEBUG	0
#घोषणा lbtf_deb_usb2(...) करो अणु अगर (INSANEDEBUG) lbtf_deb_usbd(__VA_ARGS__); पूर्ण जबतक (0)

#घोषणा MESSAGE_HEADER_LEN	4

अटल अक्षर *lbtf_fw_name = "lbtf_usb.bin";
module_param_named(fw_name, lbtf_fw_name, अक्षरp, 0644);

MODULE_FIRMWARE("lbtf_usb.bin");

अटल स्थिर काष्ठा usb_device_id अगर_usb_table[] = अणु
	/* Enter the device signature inside */
	अणु USB_DEVICE(0x1286, 0x2001) पूर्ण,
	अणु USB_DEVICE(0x05a3, 0x8388) पूर्ण,
	अणुपूर्ण	/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, अगर_usb_table);

अटल व्योम अगर_usb_receive(काष्ठा urb *urb);
अटल व्योम अगर_usb_receive_fwload(काष्ठा urb *urb);
अटल पूर्णांक अगर_usb_prog_firmware(काष्ठा lbtf_निजी *priv);
अटल पूर्णांक अगर_usb_host_to_card(काष्ठा lbtf_निजी *priv, uपूर्णांक8_t type,
			       uपूर्णांक8_t *payload, uपूर्णांक16_t nb);
अटल पूर्णांक usb_tx_block(काष्ठा अगर_usb_card *cardp, uपूर्णांक8_t *payload,
			uपूर्णांक16_t nb, u8 data);
अटल व्योम अगर_usb_मुक्त(काष्ठा अगर_usb_card *cardp);
अटल पूर्णांक अगर_usb_submit_rx_urb(काष्ठा अगर_usb_card *cardp);
अटल पूर्णांक अगर_usb_reset_device(काष्ठा lbtf_निजी *priv);

/**
 *  अगर_usb_wrike_bulk_callback -  call back to handle URB status
 *
 *  @urb:		poपूर्णांकer to urb काष्ठाure
 */
अटल व्योम अगर_usb_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	अगर (urb->status != 0) अणु
		/* prपूर्णांक the failure status number क्रम debug */
		pr_info("URB in failure status: %d\n", urb->status);
	पूर्ण अन्यथा अणु
		lbtf_deb_usb2(&urb->dev->dev, "URB status is successful\n");
		lbtf_deb_usb2(&urb->dev->dev, "Actual length transmitted %d\n",
			     urb->actual_length);
	पूर्ण
पूर्ण

/**
 *  अगर_usb_मुक्त - मुक्त tx/rx urb, skb and rx buffer
 *
 *  @cardp:	poपूर्णांकer अगर_usb_card
 */
अटल व्योम अगर_usb_मुक्त(काष्ठा अगर_usb_card *cardp)
अणु
	lbtf_deb_enter(LBTF_DEB_USB);

	/* Unlink tx & rx urb */
	usb_समाप्त_urb(cardp->tx_urb);
	usb_समाप्त_urb(cardp->rx_urb);
	usb_समाप्त_urb(cardp->cmd_urb);

	usb_मुक्त_urb(cardp->tx_urb);
	cardp->tx_urb = शून्य;

	usb_मुक्त_urb(cardp->rx_urb);
	cardp->rx_urb = शून्य;

	usb_मुक्त_urb(cardp->cmd_urb);
	cardp->cmd_urb = शून्य;

	kमुक्त(cardp->ep_out_buf);
	cardp->ep_out_buf = शून्य;

	lbtf_deb_leave(LBTF_DEB_USB);
पूर्ण

अटल व्योम अगर_usb_setup_firmware(काष्ठा lbtf_निजी *priv)
अणु
	काष्ठा अगर_usb_card *cardp = priv->card;
	काष्ठा cmd_ds_set_boot2_ver b2_cmd;

	lbtf_deb_enter(LBTF_DEB_USB);

	अगर_usb_submit_rx_urb(cardp);
	b2_cmd.hdr.size = cpu_to_le16(माप(b2_cmd));
	b2_cmd.action = 0;
	b2_cmd.version = cardp->boot2_version;

	अगर (lbtf_cmd_with_response(priv, CMD_SET_BOOT2_VER, &b2_cmd))
		lbtf_deb_usb("Setting boot2 version failed\n");

	lbtf_deb_leave(LBTF_DEB_USB);
पूर्ण

अटल व्योम अगर_usb_fw_समयo(काष्ठा समयr_list *t)
अणु
	काष्ठा अगर_usb_card *cardp = from_समयr(cardp, t, fw_समयout);

	lbtf_deb_enter(LBTF_DEB_USB);
	अगर (!cardp->fwdnlकरोver) अणु
		/* Download समयd out */
		cardp->priv->surpriseहटाओd = 1;
		pr_err("Download timed out\n");
	पूर्ण अन्यथा अणु
		lbtf_deb_usb("Download complete, no event. Assuming success\n");
	पूर्ण
	wake_up(&cardp->fw_wq);
	lbtf_deb_leave(LBTF_DEB_USB);
पूर्ण

अटल स्थिर काष्ठा lbtf_ops अगर_usb_ops = अणु
	.hw_host_to_card = अगर_usb_host_to_card,
	.hw_prog_firmware = अगर_usb_prog_firmware,
	.hw_reset_device = अगर_usb_reset_device,
पूर्ण;

/**
 *  अगर_usb_probe - sets the configuration values
 *
 *  @पूर्णांकf:	USB पूर्णांकerface काष्ठाure
 *  @id:	poपूर्णांकer to usb_device_id
 *
 *  Returns: 0 on success, error code on failure
 */
अटल पूर्णांक अगर_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा lbtf_निजी *priv;
	काष्ठा अगर_usb_card *cardp;
	पूर्णांक i;

	lbtf_deb_enter(LBTF_DEB_USB);
	udev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	cardp = kzalloc(माप(काष्ठा अगर_usb_card), GFP_KERNEL);
	अगर (!cardp)
		जाओ error;

	समयr_setup(&cardp->fw_समयout, अगर_usb_fw_समयo, 0);
	init_रुकोqueue_head(&cardp->fw_wq);

	cardp->udev = udev;
	अगरace_desc = पूर्णांकf->cur_altsetting;

	lbtf_deb_usbd(&udev->dev, "bcdUSB = 0x%X bDeviceClass = 0x%X"
		     " bDeviceSubClass = 0x%X, bDeviceProtocol = 0x%X\n",
		     le16_to_cpu(udev->descriptor.bcdUSB),
		     udev->descriptor.bDeviceClass,
		     udev->descriptor.bDeviceSubClass,
		     udev->descriptor.bDeviceProtocol);

	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; ++i) अणु
		endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[i].desc;
		अगर (usb_endpoपूर्णांक_is_bulk_in(endpoपूर्णांक)) अणु
			cardp->ep_in_size =
				le16_to_cpu(endpoपूर्णांक->wMaxPacketSize);
			cardp->ep_in = usb_endpoपूर्णांक_num(endpoपूर्णांक);

			lbtf_deb_usbd(&udev->dev, "in_endpoint = %d\n",
				cardp->ep_in);
			lbtf_deb_usbd(&udev->dev, "Bulk in size is %d\n",
				cardp->ep_in_size);
		पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_is_bulk_out(endpoपूर्णांक)) अणु
			cardp->ep_out_size =
				le16_to_cpu(endpoपूर्णांक->wMaxPacketSize);
			cardp->ep_out = usb_endpoपूर्णांक_num(endpoपूर्णांक);

			lbtf_deb_usbd(&udev->dev, "out_endpoint = %d\n",
				cardp->ep_out);
			lbtf_deb_usbd(&udev->dev, "Bulk out size is %d\n",
				cardp->ep_out_size);
		पूर्ण
	पूर्ण
	अगर (!cardp->ep_out_size || !cardp->ep_in_size) अणु
		lbtf_deb_usbd(&udev->dev, "Endpoints not found\n");
		/* Endpoपूर्णांकs not found */
		जाओ dealloc;
	पूर्ण

	cardp->rx_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!cardp->rx_urb)
		जाओ dealloc;

	cardp->tx_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!cardp->tx_urb)
		जाओ dealloc;

	cardp->cmd_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!cardp->cmd_urb)
		जाओ dealloc;

	cardp->ep_out_buf = kदो_स्मृति(MRVDRV_ETH_TX_PACKET_BUFFER_SIZE,
				    GFP_KERNEL);
	अगर (!cardp->ep_out_buf) अणु
		lbtf_deb_usbd(&udev->dev, "Could not allocate buffer\n");
		जाओ dealloc;
	पूर्ण

	cardp->boot2_version = udev->descriptor.bcdDevice;
	priv = lbtf_add_card(cardp, &udev->dev, &अगर_usb_ops);
	अगर (!priv)
		जाओ dealloc;

	usb_get_dev(udev);
	usb_set_पूर्णांकfdata(पूर्णांकf, cardp);

	वापस 0;

dealloc:
	अगर_usb_मुक्त(cardp);
error:
lbtf_deb_leave(LBTF_DEB_MAIN);
	वापस -ENOMEM;
पूर्ण

/**
 *  अगर_usb_disconnect -  मुक्त resource and cleanup
 *
 *  @पूर्णांकf:	USB पूर्णांकerface काष्ठाure
 */
अटल व्योम अगर_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा अगर_usb_card *cardp = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा lbtf_निजी *priv = cardp->priv;

	lbtf_deb_enter(LBTF_DEB_MAIN);

	अगर (priv) अणु
		अगर_usb_reset_device(priv);
		lbtf_हटाओ_card(priv);
	पूर्ण

	/* Unlink and मुक्त urb */
	अगर_usb_मुक्त(cardp);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	usb_put_dev(पूर्णांकerface_to_usbdev(पूर्णांकf));

	lbtf_deb_leave(LBTF_DEB_MAIN);
पूर्ण

/**
 *  अगर_usb_send_fw_pkt -  This function करोwnloads the FW
 *
 *  @cardp:	poपूर्णांकer अगर_usb_card
 *
 *  Returns: 0
 */
अटल पूर्णांक अगर_usb_send_fw_pkt(काष्ठा अगर_usb_card *cardp)
अणु
	काष्ठा fwdata *fwdata = cardp->ep_out_buf;
	u8 *firmware = (u8 *) cardp->fw->data;

	lbtf_deb_enter(LBTF_DEB_FW);

	/* If we got a CRC failure on the last block, back
	   up and retry it */
	अगर (!cardp->CRC_OK) अणु
		cardp->totalbytes = cardp->fwlastblksent;
		cardp->fwseqnum--;
	पूर्ण

	lbtf_deb_usb2(&cardp->udev->dev, "totalbytes = %d\n",
		     cardp->totalbytes);

	/* काष्ठा fwdata (which we sent to the card) has an
	   extra __le32 field in between the header and the data,
	   which is not in the काष्ठा fwheader in the actual
	   firmware binary. Insert the seqnum in the middle... */
	स_नकल(&fwdata->hdr, &firmware[cardp->totalbytes],
	       माप(काष्ठा fwheader));

	cardp->fwlastblksent = cardp->totalbytes;
	cardp->totalbytes += माप(काष्ठा fwheader);

	स_नकल(fwdata->data, &firmware[cardp->totalbytes],
	       le32_to_cpu(fwdata->hdr.datalength));

	lbtf_deb_usb2(&cardp->udev->dev, "Data length = %d\n",
		     le32_to_cpu(fwdata->hdr.datalength));

	fwdata->seqnum = cpu_to_le32(++cardp->fwseqnum);
	cardp->totalbytes += le32_to_cpu(fwdata->hdr.datalength);

	usb_tx_block(cardp, cardp->ep_out_buf, माप(काष्ठा fwdata) +
		     le32_to_cpu(fwdata->hdr.datalength), 0);

	अगर (fwdata->hdr.dnldcmd == cpu_to_le32(FW_HAS_DATA_TO_RECV)) अणु
		lbtf_deb_usb2(&cardp->udev->dev, "There are data to follow\n");
		lbtf_deb_usb2(&cardp->udev->dev,
			"seqnum = %d totalbytes = %d\n",
			cardp->fwseqnum, cardp->totalbytes);
	पूर्ण अन्यथा अगर (fwdata->hdr.dnldcmd == cpu_to_le32(FW_HAS_LAST_BLOCK)) अणु
		lbtf_deb_usb2(&cardp->udev->dev,
			"Host has finished FW downloading\n");
		lbtf_deb_usb2(&cardp->udev->dev, "Downloading FW JUMP BLOCK\n");

		/* Host has finished FW करोwnloading
		 * Donwloading FW JUMP BLOCK
		 */
		cardp->fwfinalblk = 1;
	पूर्ण

	lbtf_deb_usb2(&cardp->udev->dev, "Firmware download done; size %d\n",
		     cardp->totalbytes);

	lbtf_deb_leave(LBTF_DEB_FW);
	वापस 0;
पूर्ण

अटल पूर्णांक अगर_usb_reset_device(काष्ठा lbtf_निजी *priv)
अणु
	काष्ठा अगर_usb_card *cardp = priv->card;
	काष्ठा cmd_ds_802_11_reset *cmd = cardp->ep_out_buf + 4;
	पूर्णांक ret;

	lbtf_deb_enter(LBTF_DEB_USB);

	*(__le32 *)cardp->ep_out_buf = cpu_to_le32(CMD_TYPE_REQUEST);

	cmd->hdr.command = cpu_to_le16(CMD_802_11_RESET);
	cmd->hdr.size = cpu_to_le16(माप(काष्ठा cmd_ds_802_11_reset));
	cmd->hdr.result = cpu_to_le16(0);
	cmd->hdr.seqnum = cpu_to_le16(0x5a5a);
	cmd->action = cpu_to_le16(CMD_ACT_HALT);
	usb_tx_block(cardp, cardp->ep_out_buf,
		     4 + माप(काष्ठा cmd_ds_802_11_reset), 0);

	msleep(100);
	ret = usb_reset_device(cardp->udev);
	msleep(100);

	lbtf_deb_leave_args(LBTF_DEB_USB, "ret %d", ret);

	वापस ret;
पूर्ण

/**
 *  usb_tx_block - transfer data to the device
 *
 *  @cardp:	poपूर्णांकer अगर_usb_card
 *  @payload:	poपूर्णांकer to payload data
 *  @nb:	data length
 *  @data:	non-zero क्रम data, zero क्रम commands
 *
 *  Returns: 0 on success, nonzero otherwise.
 */
अटल पूर्णांक usb_tx_block(काष्ठा अगर_usb_card *cardp, uपूर्णांक8_t *payload,
			uपूर्णांक16_t nb, u8 data)
अणु
	पूर्णांक ret = -1;
	काष्ठा urb *urb;

	lbtf_deb_enter(LBTF_DEB_USB);
	/* check अगर device is हटाओd */
	अगर (cardp->priv->surpriseहटाओd) अणु
		lbtf_deb_usbd(&cardp->udev->dev, "Device removed\n");
		जाओ tx_ret;
	पूर्ण

	अगर (data)
		urb = cardp->tx_urb;
	अन्यथा
		urb = cardp->cmd_urb;

	usb_fill_bulk_urb(urb, cardp->udev,
			  usb_sndbulkpipe(cardp->udev,
					  cardp->ep_out),
			  payload, nb, अगर_usb_ग_लिखो_bulk_callback, cardp);

	urb->transfer_flags |= URB_ZERO_PACKET;

	अगर (usb_submit_urb(urb, GFP_ATOMIC)) अणु
		lbtf_deb_usbd(&cardp->udev->dev,
			"usb_submit_urb failed: %d\n", ret);
		जाओ tx_ret;
	पूर्ण

	lbtf_deb_usb2(&cardp->udev->dev, "usb_submit_urb success\n");

	ret = 0;

tx_ret:
	lbtf_deb_leave(LBTF_DEB_USB);
	वापस ret;
पूर्ण

अटल पूर्णांक __अगर_usb_submit_rx_urb(काष्ठा अगर_usb_card *cardp,
				  व्योम (*callbackfn)(काष्ठा urb *urb))
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक ret = -1;

	lbtf_deb_enter(LBTF_DEB_USB);

	skb = dev_alloc_skb(MRVDRV_ETH_RX_PACKET_BUFFER_SIZE);
	अगर (!skb) अणु
		pr_err("No free skb\n");
		lbtf_deb_leave(LBTF_DEB_USB);
		वापस -1;
	पूर्ण

	cardp->rx_skb = skb;

	/* Fill the receive configuration URB and initialise the Rx call back */
	usb_fill_bulk_urb(cardp->rx_urb, cardp->udev,
			  usb_rcvbulkpipe(cardp->udev, cardp->ep_in),
			  skb_tail_poपूर्णांकer(skb),
			  MRVDRV_ETH_RX_PACKET_BUFFER_SIZE, callbackfn, cardp);

	lbtf_deb_usb2(&cardp->udev->dev, "Pointer for rx_urb %p\n",
		cardp->rx_urb);
	ret = usb_submit_urb(cardp->rx_urb, GFP_ATOMIC);
	अगर (ret) अणु
		lbtf_deb_usbd(&cardp->udev->dev,
			"Submit Rx URB failed: %d\n", ret);
		kमुक्त_skb(skb);
		cardp->rx_skb = शून्य;
		lbtf_deb_leave(LBTF_DEB_USB);
		वापस -1;
	पूर्ण अन्यथा अणु
		lbtf_deb_usb2(&cardp->udev->dev, "Submit Rx URB success\n");
		lbtf_deb_leave(LBTF_DEB_USB);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक अगर_usb_submit_rx_urb_fwload(काष्ठा अगर_usb_card *cardp)
अणु
	वापस __अगर_usb_submit_rx_urb(cardp, &अगर_usb_receive_fwload);
पूर्ण

अटल पूर्णांक अगर_usb_submit_rx_urb(काष्ठा अगर_usb_card *cardp)
अणु
	वापस __अगर_usb_submit_rx_urb(cardp, &अगर_usb_receive);
पूर्ण

अटल व्योम अगर_usb_receive_fwload(काष्ठा urb *urb)
अणु
	काष्ठा अगर_usb_card *cardp = urb->context;
	काष्ठा sk_buff *skb = cardp->rx_skb;
	काष्ठा fwsyncheader *syncfwheader;
	काष्ठा bootcmdresp bcmdresp;

	lbtf_deb_enter(LBTF_DEB_USB);
	अगर (urb->status) अणु
		lbtf_deb_usbd(&cardp->udev->dev,
			     "URB status is failed during fw load\n");
		kमुक्त_skb(skb);
		lbtf_deb_leave(LBTF_DEB_USB);
		वापस;
	पूर्ण

	अगर (cardp->fwdnlकरोver) अणु
		__le32 *पंचांगp = (__le32 *)(skb->data);

		अगर (पंचांगp[0] == cpu_to_le32(CMD_TYPE_INDICATION) &&
		    पंचांगp[1] == cpu_to_le32(MACREG_INT_CODE_FIRMWARE_READY)) अणु
			/* Firmware पढ़ोy event received */
			pr_info("Firmware ready event received\n");
			wake_up(&cardp->fw_wq);
		पूर्ण अन्यथा अणु
			lbtf_deb_usb("Waiting for confirmation; got %x %x\n",
				    le32_to_cpu(पंचांगp[0]), le32_to_cpu(पंचांगp[1]));
			अगर_usb_submit_rx_urb_fwload(cardp);
		पूर्ण
		kमुक्त_skb(skb);
		lbtf_deb_leave(LBTF_DEB_USB);
		वापस;
	पूर्ण
	अगर (cardp->bootcmdresp <= 0) अणु
		स_नकल(&bcmdresp, skb->data, माप(bcmdresp));

		अगर (le16_to_cpu(cardp->udev->descriptor.bcdDevice) < 0x3106) अणु
			kमुक्त_skb(skb);
			अगर_usb_submit_rx_urb_fwload(cardp);
			cardp->bootcmdresp = 1;
			/* Received valid boot command response */
			lbtf_deb_usbd(&cardp->udev->dev,
				     "Received valid boot command response\n");
			lbtf_deb_leave(LBTF_DEB_USB);
			वापस;
		पूर्ण
		अगर (bcmdresp.magic != cpu_to_le32(BOOT_CMD_MAGIC_NUMBER)) अणु
			अगर (bcmdresp.magic == cpu_to_le32(CMD_TYPE_REQUEST) ||
			    bcmdresp.magic == cpu_to_le32(CMD_TYPE_DATA) ||
			    bcmdresp.magic == cpu_to_le32(CMD_TYPE_INDICATION)) अणु
				अगर (!cardp->bootcmdresp)
					pr_info("Firmware already seems alive; resetting\n");
				cardp->bootcmdresp = -1;
			पूर्ण अन्यथा अणु
				pr_info("boot cmd response wrong magic number (0x%x)\n",
					    le32_to_cpu(bcmdresp.magic));
			पूर्ण
		पूर्ण अन्यथा अगर (bcmdresp.cmd != BOOT_CMD_FW_BY_USB) अणु
			pr_info("boot cmd response cmd_tag error (%d)\n",
				bcmdresp.cmd);
		पूर्ण अन्यथा अगर (bcmdresp.result != BOOT_CMD_RESP_OK) अणु
			pr_info("boot cmd response result error (%d)\n",
				bcmdresp.result);
		पूर्ण अन्यथा अणु
			cardp->bootcmdresp = 1;
			lbtf_deb_usbd(&cardp->udev->dev,
				"Received valid boot command response\n");
		पूर्ण

		kमुक्त_skb(skb);
		अगर_usb_submit_rx_urb_fwload(cardp);
		lbtf_deb_leave(LBTF_DEB_USB);
		वापस;
	पूर्ण

	syncfwheader = kmemdup(skb->data, माप(काष्ठा fwsyncheader),
			       GFP_ATOMIC);
	अगर (!syncfwheader) अणु
		lbtf_deb_usbd(&cardp->udev->dev,
			"Failure to allocate syncfwheader\n");
		kमुक्त_skb(skb);
		lbtf_deb_leave(LBTF_DEB_USB);
		वापस;
	पूर्ण

	अगर (!syncfwheader->cmd) अणु
		lbtf_deb_usb2(&cardp->udev->dev,
			"FW received Blk with correct CRC\n");
		lbtf_deb_usb2(&cardp->udev->dev,
			"FW received Blk seqnum = %d\n",
			le32_to_cpu(syncfwheader->seqnum));
		cardp->CRC_OK = 1;
	पूर्ण अन्यथा अणु
		lbtf_deb_usbd(&cardp->udev->dev,
			"FW received Blk with CRC error\n");
		cardp->CRC_OK = 0;
	पूर्ण

	kमुक्त_skb(skb);

	/* reschedule समयr क्रम 200ms hence */
	mod_समयr(&cardp->fw_समयout, jअगरfies + (HZ/5));

	अगर (cardp->fwfinalblk) अणु
		cardp->fwdnlकरोver = 1;
		जाओ निकास;
	पूर्ण

	अगर_usb_send_fw_pkt(cardp);

 निकास:
	अगर_usb_submit_rx_urb_fwload(cardp);

	kमुक्त(syncfwheader);

	lbtf_deb_leave(LBTF_DEB_USB);
पूर्ण

#घोषणा MRVDRV_MIN_PKT_LEN	30

अटल अंतरभूत व्योम process_cmdtypedata(पूर्णांक recvlength, काष्ठा sk_buff *skb,
				       काष्ठा अगर_usb_card *cardp,
				       काष्ठा lbtf_निजी *priv)
अणु
	अगर (recvlength > MRVDRV_ETH_RX_PACKET_BUFFER_SIZE + MESSAGE_HEADER_LEN
	    || recvlength < MRVDRV_MIN_PKT_LEN) अणु
		lbtf_deb_usbd(&cardp->udev->dev, "Packet length is Invalid\n");
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	skb_put(skb, recvlength);
	skb_pull(skb, MESSAGE_HEADER_LEN);
	lbtf_rx(priv, skb);
पूर्ण

अटल अंतरभूत व्योम process_cmdrequest(पूर्णांक recvlength, uपूर्णांक8_t *recvbuff,
				      काष्ठा sk_buff *skb,
				      काष्ठा अगर_usb_card *cardp,
				      काष्ठा lbtf_निजी *priv)
अणु
	अचिन्हित दीर्घ flags;

	अगर (recvlength < MESSAGE_HEADER_LEN ||
	    recvlength > LBS_CMD_BUFFER_SIZE) अणु
		lbtf_deb_usbd(&cardp->udev->dev,
			     "The receive buffer is invalid: %d\n", recvlength);
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	spin_lock_irqsave(&priv->driver_lock, flags);
	स_नकल(priv->cmd_resp_buff, recvbuff + MESSAGE_HEADER_LEN,
	       recvlength - MESSAGE_HEADER_LEN);
	kमुक्त_skb(skb);
	lbtf_cmd_response_rx(priv);
	spin_unlock_irqrestore(&priv->driver_lock, flags);
पूर्ण

/**
 *  अगर_usb_receive - पढ़ो data received from the device.
 *
 *  @urb:		poपूर्णांकer to काष्ठा urb
 */
अटल व्योम अगर_usb_receive(काष्ठा urb *urb)
अणु
	काष्ठा अगर_usb_card *cardp = urb->context;
	काष्ठा sk_buff *skb = cardp->rx_skb;
	काष्ठा lbtf_निजी *priv = cardp->priv;
	पूर्णांक recvlength = urb->actual_length;
	uपूर्णांक8_t *recvbuff = शून्य;
	uपूर्णांक32_t recvtype = 0;
	__le32 *pkt = (__le32 *) skb->data;

	lbtf_deb_enter(LBTF_DEB_USB);

	अगर (recvlength) अणु
		अगर (urb->status) अणु
			lbtf_deb_usbd(&cardp->udev->dev, "RX URB failed: %d\n",
				     urb->status);
			kमुक्त_skb(skb);
			जाओ setup_क्रम_next;
		पूर्ण

		recvbuff = skb->data;
		recvtype = le32_to_cpu(pkt[0]);
		lbtf_deb_usbd(&cardp->udev->dev,
			    "Recv length = 0x%x, Recv type = 0x%X\n",
			    recvlength, recvtype);
	पूर्ण अन्यथा अगर (urb->status) अणु
		kमुक्त_skb(skb);
		lbtf_deb_leave(LBTF_DEB_USB);
		वापस;
	पूर्ण

	चयन (recvtype) अणु
	हाल CMD_TYPE_DATA:
		process_cmdtypedata(recvlength, skb, cardp, priv);
		अवरोध;

	हाल CMD_TYPE_REQUEST:
		process_cmdrequest(recvlength, recvbuff, skb, cardp, priv);
		अवरोध;

	हाल CMD_TYPE_INDICATION:
	अणु
		/* Event cause handling */
		u32 event_cause = le32_to_cpu(pkt[1]);
		lbtf_deb_usbd(&cardp->udev->dev, "**EVENT** 0x%X\n",
			event_cause);

		/* Icky unकरोcumented magic special हाल */
		अगर (event_cause & 0xffff0000) अणु
			u16 पंचांगp;
			u8 retrycnt;
			u8 failure;

			पंचांगp = event_cause >> 16;
			retrycnt = पंचांगp & 0x00ff;
			failure = (पंचांगp & 0xff00) >> 8;
			lbtf_send_tx_feedback(priv, retrycnt, failure);
		पूर्ण अन्यथा अगर (event_cause == LBTF_EVENT_BCN_SENT)
			lbtf_bcn_sent(priv);
		अन्यथा
			lbtf_deb_usbd(&cardp->udev->dev,
			       "Unsupported notification %d received\n",
			       event_cause);
		kमुक्त_skb(skb);
		अवरोध;
	पूर्ण
	शेष:
		lbtf_deb_usbd(&cardp->udev->dev,
			"libertastf: unknown command type 0x%X\n", recvtype);
		kमुक्त_skb(skb);
		अवरोध;
	पूर्ण

setup_क्रम_next:
	अगर_usb_submit_rx_urb(cardp);
	lbtf_deb_leave(LBTF_DEB_USB);
पूर्ण

/**
 *  अगर_usb_host_to_card -  Download data to the device
 *
 *  @priv:		poपूर्णांकer to काष्ठा lbtf_निजी काष्ठाure
 *  @type:		type of data
 *  @payload:		poपूर्णांकer to payload buffer
 *  @nb:		number of bytes
 *
 *  Returns: 0 on success, nonzero otherwise
 */
अटल पूर्णांक अगर_usb_host_to_card(काष्ठा lbtf_निजी *priv, uपूर्णांक8_t type,
			       uपूर्णांक8_t *payload, uपूर्णांक16_t nb)
अणु
	काष्ठा अगर_usb_card *cardp = priv->card;
	u8 data = 0;

	lbtf_deb_usbd(&cardp->udev->dev, "*** type = %u\n", type);
	lbtf_deb_usbd(&cardp->udev->dev, "size after = %d\n", nb);

	अगर (type == MVMS_CMD) अणु
		*(__le32 *)cardp->ep_out_buf = cpu_to_le32(CMD_TYPE_REQUEST);
	पूर्ण अन्यथा अणु
		*(__le32 *)cardp->ep_out_buf = cpu_to_le32(CMD_TYPE_DATA);
		data = 1;
	पूर्ण

	स_नकल((cardp->ep_out_buf + MESSAGE_HEADER_LEN), payload, nb);

	वापस usb_tx_block(cardp, cardp->ep_out_buf, nb + MESSAGE_HEADER_LEN,
			    data);
पूर्ण

/**
 *  अगर_usb_issue_boot_command - Issue boot command to Boot2.
 *
 *  @cardp:	poपूर्णांकer अगर_usb_card
 *  @ivalue:   1 boots from FW by USB-Download, 2 boots from FW in EEPROM.
 *
 *  Returns: 0
 */
अटल पूर्णांक अगर_usb_issue_boot_command(काष्ठा अगर_usb_card *cardp, पूर्णांक ivalue)
अणु
	काष्ठा bootcmd *bootcmd = cardp->ep_out_buf;

	/* Prepare command */
	bootcmd->magic = cpu_to_le32(BOOT_CMD_MAGIC_NUMBER);
	bootcmd->cmd = ivalue;
	स_रखो(bootcmd->pad, 0, माप(bootcmd->pad));

	/* Issue command */
	usb_tx_block(cardp, cardp->ep_out_buf, माप(*bootcmd), 0);

	वापस 0;
पूर्ण


/**
 *  check_fwfile_क्रमmat - Check the validity of Boot2/FW image.
 *
 *  @data:	poपूर्णांकer to image
 *  @totlen:	image length
 *
 *  Returns: 0 अगर the image is valid, nonzero otherwise.
 */
अटल पूर्णांक check_fwfile_क्रमmat(स्थिर u8 *data, u32 totlen)
अणु
	u32 bincmd, निकास;
	u32 blksize, offset, len;
	पूर्णांक ret;

	ret = 1;
	निकास = len = 0;

	करो अणु
		काष्ठा fwheader *fwh = (व्योम *) data;

		bincmd = le32_to_cpu(fwh->dnldcmd);
		blksize = le32_to_cpu(fwh->datalength);
		चयन (bincmd) अणु
		हाल FW_HAS_DATA_TO_RECV:
			offset = माप(काष्ठा fwheader) + blksize;
			data += offset;
			len += offset;
			अगर (len >= totlen)
				निकास = 1;
			अवरोध;
		हाल FW_HAS_LAST_BLOCK:
			निकास = 1;
			ret = 0;
			अवरोध;
		शेष:
			निकास = 1;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (!निकास);

	अगर (ret)
		pr_err("firmware file format check FAIL\n");
	अन्यथा
		lbtf_deb_fw("firmware file format check PASS\n");

	वापस ret;
पूर्ण


अटल पूर्णांक अगर_usb_prog_firmware(काष्ठा lbtf_निजी *priv)
अणु
	काष्ठा अगर_usb_card *cardp = priv->card;
	पूर्णांक i = 0;
	अटल पूर्णांक reset_count = 10;
	पूर्णांक ret = 0;

	lbtf_deb_enter(LBTF_DEB_USB);

	cardp->priv = priv;

	kernel_param_lock(THIS_MODULE);
	ret = request_firmware(&cardp->fw, lbtf_fw_name, &cardp->udev->dev);
	अगर (ret < 0) अणु
		pr_err("request_firmware() failed with %#x\n", ret);
		pr_err("firmware %s not found\n", lbtf_fw_name);
		kernel_param_unlock(THIS_MODULE);
		जाओ करोne;
	पूर्ण
	kernel_param_unlock(THIS_MODULE);

	अगर (check_fwfile_क्रमmat(cardp->fw->data, cardp->fw->size))
		जाओ release_fw;

restart:
	अगर (अगर_usb_submit_rx_urb_fwload(cardp) < 0) अणु
		lbtf_deb_usbd(&cardp->udev->dev, "URB submission is failed\n");
		ret = -1;
		जाओ release_fw;
	पूर्ण

	cardp->bootcmdresp = 0;
	करो अणु
		पूर्णांक j = 0;
		i++;
		/* Issue Boot command = 1, Boot from Download-FW */
		अगर_usb_issue_boot_command(cardp, BOOT_CMD_FW_BY_USB);
		/* रुको क्रम command response */
		करो अणु
			j++;
			msleep_पूर्णांकerruptible(100);
		पूर्ण जबतक (cardp->bootcmdresp == 0 && j < 10);
	पूर्ण जबतक (cardp->bootcmdresp == 0 && i < 5);

	अगर (cardp->bootcmdresp <= 0) अणु
		अगर (--reset_count >= 0) अणु
			अगर_usb_reset_device(priv);
			जाओ restart;
		पूर्ण
		वापस -1;
	पूर्ण

	i = 0;

	cardp->totalbytes = 0;
	cardp->fwlastblksent = 0;
	cardp->CRC_OK = 1;
	cardp->fwdnlकरोver = 0;
	cardp->fwseqnum = -1;
	cardp->totalbytes = 0;
	cardp->fwfinalblk = 0;

	/* Send the first firmware packet... */
	अगर_usb_send_fw_pkt(cardp);

	/* ... and रुको क्रम the process to complete */
	रुको_event_पूर्णांकerruptible(cardp->fw_wq, cardp->priv->surpriseहटाओd ||
					       cardp->fwdnlकरोver);

	del_समयr_sync(&cardp->fw_समयout);
	usb_समाप्त_urb(cardp->rx_urb);

	अगर (!cardp->fwdnlकरोver) अणु
		pr_info("failed to load fw, resetting device!\n");
		अगर (--reset_count >= 0) अणु
			अगर_usb_reset_device(priv);
			जाओ restart;
		पूर्ण

		pr_info("FW download failure, time = %d ms\n", i * 100);
		ret = -1;
		जाओ release_fw;
	पूर्ण

 release_fw:
	release_firmware(cardp->fw);
	cardp->fw = शून्य;

	अगर_usb_setup_firmware(cardp->priv);

 करोne:
	lbtf_deb_leave_args(LBTF_DEB_USB, "ret %d", ret);
	वापस ret;
पूर्ण


#घोषणा अगर_usb_suspend शून्य
#घोषणा अगर_usb_resume शून्य

अटल काष्ठा usb_driver अगर_usb_driver = अणु
	.name = DRV_NAME,
	.probe = अगर_usb_probe,
	.disconnect = अगर_usb_disconnect,
	.id_table = अगर_usb_table,
	.suspend = अगर_usb_suspend,
	.resume = अगर_usb_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(अगर_usb_driver);

MODULE_DESCRIPTION("8388 USB WLAN Thinfirm Driver");
MODULE_AUTHOR("Cozybit Inc.");
MODULE_LICENSE("GPL");
