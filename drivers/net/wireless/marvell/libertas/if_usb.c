<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file contains functions used in USB पूर्णांकerface module.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/olpc-ec.h>

#अगर_घोषित CONFIG_OLPC
#समावेश <यंत्र/olpc.h>
#पूर्ण_अगर

#घोषणा DRV_NAME "usb8xxx"

#समावेश "host.h"
#समावेश "decl.h"
#समावेश "defs.h"
#समावेश "dev.h"
#समावेश "cmd.h"
#समावेश "if_usb.h"

#घोषणा INSANEDEBUG	0
#घोषणा lbs_deb_usb2(...) करो अणु अगर (INSANEDEBUG) lbs_deb_usbd(__VA_ARGS__); पूर्ण जबतक (0)

#घोषणा MESSAGE_HEADER_LEN	4

MODULE_FIRMWARE("libertas/usb8388_v9.bin");
MODULE_FIRMWARE("libertas/usb8388_v5.bin");
MODULE_FIRMWARE("libertas/usb8388.bin");
MODULE_FIRMWARE("libertas/usb8682.bin");
MODULE_FIRMWARE("usb8388.bin");

क्रमागत अणु
	MODEL_UNKNOWN = 0x0,
	MODEL_8388 = 0x1,
	MODEL_8682 = 0x2
पूर्ण;

/* table of firmware file names */
अटल स्थिर काष्ठा lbs_fw_table fw_table[] = अणु
	अणु MODEL_8388, "libertas/usb8388_olpc.bin", शून्य पूर्ण,
	अणु MODEL_8388, "libertas/usb8388_v9.bin", शून्य पूर्ण,
	अणु MODEL_8388, "libertas/usb8388_v5.bin", शून्य पूर्ण,
	अणु MODEL_8388, "libertas/usb8388.bin", शून्य पूर्ण,
	अणु MODEL_8388, "usb8388.bin", शून्य पूर्ण,
	अणु MODEL_8682, "libertas/usb8682.bin", शून्य पूर्ण,
	अणु 0, शून्य, शून्य पूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_device_id अगर_usb_table[] = अणु
	/* Enter the device signature inside */
	अणु USB_DEVICE(0x1286, 0x2001), .driver_info = MODEL_8388 पूर्ण,
	अणु USB_DEVICE(0x05a3, 0x8388), .driver_info = MODEL_8388 पूर्ण,
	अणुपूर्ण	/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, अगर_usb_table);

अटल व्योम अगर_usb_receive(काष्ठा urb *urb);
अटल व्योम अगर_usb_receive_fwload(काष्ठा urb *urb);
अटल व्योम अगर_usb_prog_firmware(काष्ठा lbs_निजी *priv, पूर्णांक ret,
				 स्थिर काष्ठा firmware *fw,
				 स्थिर काष्ठा firmware *unused);
अटल पूर्णांक अगर_usb_host_to_card(काष्ठा lbs_निजी *priv, uपूर्णांक8_t type,
			       uपूर्णांक8_t *payload, uपूर्णांक16_t nb);
अटल पूर्णांक usb_tx_block(काष्ठा अगर_usb_card *cardp, uपूर्णांक8_t *payload,
			uपूर्णांक16_t nb);
अटल व्योम अगर_usb_मुक्त(काष्ठा अगर_usb_card *cardp);
अटल पूर्णांक अगर_usb_submit_rx_urb(काष्ठा अगर_usb_card *cardp);
अटल पूर्णांक अगर_usb_reset_device(काष्ठा अगर_usb_card *cardp);

/**
 * अगर_usb_ग_लिखो_bulk_callback - callback function to handle the status
 * of the URB
 * @urb:	poपूर्णांकer to &urb काष्ठाure
 * वापसs:	N/A
 */
अटल व्योम अगर_usb_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा अगर_usb_card *cardp = (काष्ठा अगर_usb_card *) urb->context;

	/* handle the transmission complete validations */

	अगर (urb->status == 0) अणु
		काष्ठा lbs_निजी *priv = cardp->priv;

		lbs_deb_usb2(&urb->dev->dev, "URB status is successful\n");
		lbs_deb_usb2(&urb->dev->dev, "Actual length transmitted %d\n",
			     urb->actual_length);

		/* Boot commands such as UPDATE_FW and UPDATE_BOOT2 are not
		 * passed up to the lbs level.
		 */
		अगर (priv && priv->dnld_sent != DNLD_BOOTCMD_SENT)
			lbs_host_to_card_करोne(priv);
	पूर्ण अन्यथा अणु
		/* prपूर्णांक the failure status number क्रम debug */
		pr_info("URB in failure status: %d\n", urb->status);
	पूर्ण
पूर्ण

/**
 * अगर_usb_मुक्त - मुक्त tx/rx urb, skb and rx buffer
 * @cardp:	poपूर्णांकer to &अगर_usb_card
 * वापसs:	N/A
 */
अटल व्योम अगर_usb_मुक्त(काष्ठा अगर_usb_card *cardp)
अणु
	/* Unlink tx & rx urb */
	usb_समाप्त_urb(cardp->tx_urb);
	usb_समाप्त_urb(cardp->rx_urb);

	usb_मुक्त_urb(cardp->tx_urb);
	cardp->tx_urb = शून्य;

	usb_मुक्त_urb(cardp->rx_urb);
	cardp->rx_urb = शून्य;

	kमुक्त(cardp->ep_out_buf);
	cardp->ep_out_buf = शून्य;
पूर्ण

अटल व्योम अगर_usb_setup_firmware(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा अगर_usb_card *cardp = priv->card;
	काष्ठा cmd_ds_set_boot2_ver b2_cmd;
	काष्ठा cmd_ds_802_11_fw_wake_method wake_method;

	b2_cmd.hdr.size = cpu_to_le16(माप(b2_cmd));
	b2_cmd.action = 0;
	b2_cmd.version = cardp->boot2_version;

	अगर (lbs_cmd_with_response(priv, CMD_SET_BOOT2_VER, &b2_cmd))
		lbs_deb_usb("Setting boot2 version failed\n");

	priv->wol_gpio = 2; /* Wake via GPIO2... */
	priv->wol_gap = 20; /* ... after 20ms    */
	lbs_host_sleep_cfg(priv, EHS_WAKE_ON_UNICAST_DATA,
			(काष्ठा wol_config *) शून्य);

	wake_method.hdr.size = cpu_to_le16(माप(wake_method));
	wake_method.action = cpu_to_le16(CMD_ACT_GET);
	अगर (lbs_cmd_with_response(priv, CMD_802_11_FW_WAKE_METHOD, &wake_method)) अणु
		netdev_info(priv->dev, "Firmware does not seem to support PS mode\n");
		priv->fwcapinfo &= ~FW_CAPINFO_PS;
	पूर्ण अन्यथा अणु
		अगर (le16_to_cpu(wake_method.method) == CMD_WAKE_METHOD_COMMAND_INT) अणु
			lbs_deb_usb("Firmware seems to support PS with wake-via-command\n");
		पूर्ण अन्यथा अणु
			/* The versions which boot up this way करोn't seem to
			   work even अगर we set it to the command पूर्णांकerrupt */
			priv->fwcapinfo &= ~FW_CAPINFO_PS;
			netdev_info(priv->dev,
				    "Firmware doesn't wake via command interrupt; disabling PS mode\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम अगर_usb_fw_समयo(काष्ठा समयr_list *t)
अणु
	काष्ठा अगर_usb_card *cardp = from_समयr(cardp, t, fw_समयout);

	अगर (cardp->fwdnlकरोver) अणु
		lbs_deb_usb("Download complete, no event. Assuming success\n");
	पूर्ण अन्यथा अणु
		pr_err("Download timed out\n");
		cardp->surprise_हटाओd = 1;
	पूर्ण
	wake_up(&cardp->fw_wq);
पूर्ण

#अगर_घोषित CONFIG_OLPC
अटल व्योम अगर_usb_reset_olpc_card(काष्ठा lbs_निजी *priv)
अणु
	prपूर्णांकk(KERN_CRIT "Resetting OLPC wireless via EC...\n");
	olpc_ec_cmd(0x25, शून्य, 0, शून्य, 0);
पूर्ण
#पूर्ण_अगर

/**
 * अगर_usb_probe - sets the configuration values
 * @पूर्णांकf:	&usb_पूर्णांकerface poपूर्णांकer
 * @id:	poपूर्णांकer to usb_device_id
 * वापसs:	0 on success, error code on failure
 */
अटल पूर्णांक अगर_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा lbs_निजी *priv;
	काष्ठा अगर_usb_card *cardp;
	पूर्णांक r = -ENOMEM;
	पूर्णांक i;

	udev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	cardp = kzalloc(माप(काष्ठा अगर_usb_card), GFP_KERNEL);
	अगर (!cardp)
		जाओ error;

	समयr_setup(&cardp->fw_समयout, अगर_usb_fw_समयo, 0);
	init_रुकोqueue_head(&cardp->fw_wq);

	cardp->udev = udev;
	cardp->model = (uपूर्णांक32_t) id->driver_info;
	अगरace_desc = पूर्णांकf->cur_altsetting;

	lbs_deb_usbd(&udev->dev, "bcdUSB = 0x%X bDeviceClass = 0x%X"
		     " bDeviceSubClass = 0x%X, bDeviceProtocol = 0x%X\n",
		     le16_to_cpu(udev->descriptor.bcdUSB),
		     udev->descriptor.bDeviceClass,
		     udev->descriptor.bDeviceSubClass,
		     udev->descriptor.bDeviceProtocol);

	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; ++i) अणु
		endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[i].desc;
		अगर (usb_endpoपूर्णांक_is_bulk_in(endpoपूर्णांक)) अणु
			cardp->ep_in_size = le16_to_cpu(endpoपूर्णांक->wMaxPacketSize);
			cardp->ep_in = usb_endpoपूर्णांक_num(endpoपूर्णांक);

			lbs_deb_usbd(&udev->dev, "in_endpoint = %d\n", cardp->ep_in);
			lbs_deb_usbd(&udev->dev, "Bulk in size is %d\n", cardp->ep_in_size);

		पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_is_bulk_out(endpoपूर्णांक)) अणु
			cardp->ep_out_size = le16_to_cpu(endpoपूर्णांक->wMaxPacketSize);
			cardp->ep_out = usb_endpoपूर्णांक_num(endpoपूर्णांक);

			lbs_deb_usbd(&udev->dev, "out_endpoint = %d\n", cardp->ep_out);
			lbs_deb_usbd(&udev->dev, "Bulk out size is %d\n", cardp->ep_out_size);
		पूर्ण
	पूर्ण
	अगर (!cardp->ep_out_size || !cardp->ep_in_size) अणु
		lbs_deb_usbd(&udev->dev, "Endpoints not found\n");
		जाओ dealloc;
	पूर्ण
	अगर (!(cardp->rx_urb = usb_alloc_urb(0, GFP_KERNEL))) अणु
		lbs_deb_usbd(&udev->dev, "Rx URB allocation failed\n");
		जाओ dealloc;
	पूर्ण
	अगर (!(cardp->tx_urb = usb_alloc_urb(0, GFP_KERNEL))) अणु
		lbs_deb_usbd(&udev->dev, "Tx URB allocation failed\n");
		जाओ dealloc;
	पूर्ण
	cardp->ep_out_buf = kदो_स्मृति(MRVDRV_ETH_TX_PACKET_BUFFER_SIZE, GFP_KERNEL);
	अगर (!cardp->ep_out_buf) अणु
		lbs_deb_usbd(&udev->dev, "Could not allocate buffer\n");
		जाओ dealloc;
	पूर्ण

	priv = lbs_add_card(cardp, &पूर्णांकf->dev);
	अगर (IS_ERR(priv)) अणु
		r = PTR_ERR(priv);
		जाओ err_add_card;
	पूर्ण

	cardp->priv = priv;

	priv->hw_host_to_card = अगर_usb_host_to_card;
	priv->enter_deep_sleep = शून्य;
	priv->निकास_deep_sleep = शून्य;
	priv->reset_deep_sleep_wakeup = शून्य;
	priv->is_polling = false;
#अगर_घोषित CONFIG_OLPC
	अगर (machine_is_olpc())
		priv->reset_card = अगर_usb_reset_olpc_card;
#पूर्ण_अगर

	cardp->boot2_version = udev->descriptor.bcdDevice;

	usb_get_dev(udev);
	usb_set_पूर्णांकfdata(पूर्णांकf, cardp);

	r = lbs_get_firmware_async(priv, &udev->dev, cardp->model,
				   fw_table, अगर_usb_prog_firmware);
	अगर (r)
		जाओ err_get_fw;

	वापस 0;

err_get_fw:
	lbs_हटाओ_card(priv);
err_add_card:
	अगर_usb_reset_device(cardp);
dealloc:
	अगर_usb_मुक्त(cardp);

error:
	वापस r;
पूर्ण

/**
 * अगर_usb_disconnect - मुक्त resource and cleanup
 * @पूर्णांकf:	USB पूर्णांकerface काष्ठाure
 * वापसs:	N/A
 */
अटल व्योम अगर_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा अगर_usb_card *cardp = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा lbs_निजी *priv = cardp->priv;

	cardp->surprise_हटाओd = 1;

	अगर (priv) अणु
		lbs_stop_card(priv);
		lbs_हटाओ_card(priv);
	पूर्ण

	/* Unlink and मुक्त urb */
	अगर_usb_मुक्त(cardp);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	usb_put_dev(पूर्णांकerface_to_usbdev(पूर्णांकf));
पूर्ण

/**
 * अगर_usb_send_fw_pkt - करोwnload FW
 * @cardp:	poपूर्णांकer to &काष्ठा अगर_usb_card
 * वापसs:	0
 */
अटल पूर्णांक अगर_usb_send_fw_pkt(काष्ठा अगर_usb_card *cardp)
अणु
	काष्ठा fwdata *fwdata = cardp->ep_out_buf;
	स्थिर uपूर्णांक8_t *firmware = cardp->fw->data;

	/* If we got a CRC failure on the last block, back
	   up and retry it */
	अगर (!cardp->CRC_OK) अणु
		cardp->totalbytes = cardp->fwlastblksent;
		cardp->fwseqnum--;
	पूर्ण

	lbs_deb_usb2(&cardp->udev->dev, "totalbytes = %d\n",
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

	lbs_deb_usb2(&cardp->udev->dev, "Data length = %d\n",
		     le32_to_cpu(fwdata->hdr.datalength));

	fwdata->seqnum = cpu_to_le32(++cardp->fwseqnum);
	cardp->totalbytes += le32_to_cpu(fwdata->hdr.datalength);

	usb_tx_block(cardp, cardp->ep_out_buf, माप(काष्ठा fwdata) +
		     le32_to_cpu(fwdata->hdr.datalength));

	अगर (fwdata->hdr.dnldcmd == cpu_to_le32(FW_HAS_DATA_TO_RECV)) अणु
		lbs_deb_usb2(&cardp->udev->dev, "There are data to follow\n");
		lbs_deb_usb2(&cardp->udev->dev, "seqnum = %d totalbytes = %d\n",
			     cardp->fwseqnum, cardp->totalbytes);
	पूर्ण अन्यथा अगर (fwdata->hdr.dnldcmd == cpu_to_le32(FW_HAS_LAST_BLOCK)) अणु
		lbs_deb_usb2(&cardp->udev->dev, "Host has finished FW downloading\n");
		lbs_deb_usb2(&cardp->udev->dev, "Downloading FW JUMP BLOCK\n");

		cardp->fwfinalblk = 1;
	पूर्ण

	lbs_deb_usb2(&cardp->udev->dev, "Firmware download done; size %d\n",
		     cardp->totalbytes);

	वापस 0;
पूर्ण

अटल पूर्णांक अगर_usb_reset_device(काष्ठा अगर_usb_card *cardp)
अणु
	काष्ठा cmd_header *cmd = cardp->ep_out_buf + 4;
	पूर्णांक ret;

	*(__le32 *)cardp->ep_out_buf = cpu_to_le32(CMD_TYPE_REQUEST);

	cmd->command = cpu_to_le16(CMD_802_11_RESET);
	cmd->size = cpu_to_le16(माप(cmd));
	cmd->result = cpu_to_le16(0);
	cmd->seqnum = cpu_to_le16(0x5a5a);
	usb_tx_block(cardp, cardp->ep_out_buf, 4 + माप(काष्ठा cmd_header));

	msleep(100);
	ret = usb_reset_device(cardp->udev);
	msleep(100);

#अगर_घोषित CONFIG_OLPC
	अगर (ret && machine_is_olpc())
		अगर_usb_reset_olpc_card(शून्य);
#पूर्ण_अगर

	वापस ret;
पूर्ण

/**
 *  usb_tx_block - transfer the data to the device
 *  @cardp: 	poपूर्णांकer to &काष्ठा अगर_usb_card
 *  @payload:	poपूर्णांकer to payload data
 *  @nb:	data length
 *  वापसs:	0 क्रम success or negative error code
 */
अटल पूर्णांक usb_tx_block(काष्ठा अगर_usb_card *cardp, uपूर्णांक8_t *payload, uपूर्णांक16_t nb)
अणु
	पूर्णांक ret;

	/* check अगर device is हटाओd */
	अगर (cardp->surprise_हटाओd) अणु
		lbs_deb_usbd(&cardp->udev->dev, "Device removed\n");
		ret = -ENODEV;
		जाओ tx_ret;
	पूर्ण

	usb_fill_bulk_urb(cardp->tx_urb, cardp->udev,
			  usb_sndbulkpipe(cardp->udev,
					  cardp->ep_out),
			  payload, nb, अगर_usb_ग_लिखो_bulk_callback, cardp);

	cardp->tx_urb->transfer_flags |= URB_ZERO_PACKET;

	अगर ((ret = usb_submit_urb(cardp->tx_urb, GFP_ATOMIC))) अणु
		lbs_deb_usbd(&cardp->udev->dev, "usb_submit_urb failed: %d\n", ret);
	पूर्ण अन्यथा अणु
		lbs_deb_usb2(&cardp->udev->dev, "usb_submit_urb success\n");
		ret = 0;
	पूर्ण

tx_ret:
	वापस ret;
पूर्ण

अटल पूर्णांक __अगर_usb_submit_rx_urb(काष्ठा अगर_usb_card *cardp,
				  व्योम (*callbackfn)(काष्ठा urb *urb))
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक ret = -1;

	अगर (!(skb = dev_alloc_skb(MRVDRV_ETH_RX_PACKET_BUFFER_SIZE))) अणु
		pr_err("No free skb\n");
		जाओ rx_ret;
	पूर्ण

	cardp->rx_skb = skb;

	/* Fill the receive configuration URB and initialise the Rx call back */
	usb_fill_bulk_urb(cardp->rx_urb, cardp->udev,
			  usb_rcvbulkpipe(cardp->udev, cardp->ep_in),
			  skb->data + IPFIELD_ALIGN_OFFSET,
			  MRVDRV_ETH_RX_PACKET_BUFFER_SIZE, callbackfn,
			  cardp);

	lbs_deb_usb2(&cardp->udev->dev, "Pointer for rx_urb %p\n", cardp->rx_urb);
	अगर ((ret = usb_submit_urb(cardp->rx_urb, GFP_ATOMIC))) अणु
		lbs_deb_usbd(&cardp->udev->dev, "Submit Rx URB failed: %d\n", ret);
		kमुक्त_skb(skb);
		cardp->rx_skb = शून्य;
		ret = -1;
	पूर्ण अन्यथा अणु
		lbs_deb_usb2(&cardp->udev->dev, "Submit Rx URB success\n");
		ret = 0;
	पूर्ण

rx_ret:
	वापस ret;
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
	काष्ठा bootcmdresp bootcmdresp;

	अगर (urb->status) अणु
		lbs_deb_usbd(&cardp->udev->dev,
			     "URB status is failed during fw load\n");
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	अगर (cardp->fwdnlकरोver) अणु
		__le32 *पंचांगp = (__le32 *)(skb->data + IPFIELD_ALIGN_OFFSET);

		अगर (पंचांगp[0] == cpu_to_le32(CMD_TYPE_INDICATION) &&
		    पंचांगp[1] == cpu_to_le32(MACREG_INT_CODE_FIRMWARE_READY)) अणु
			pr_info("Firmware ready event received\n");
			wake_up(&cardp->fw_wq);
		पूर्ण अन्यथा अणु
			lbs_deb_usb("Waiting for confirmation; got %x %x\n",
				    le32_to_cpu(पंचांगp[0]), le32_to_cpu(पंचांगp[1]));
			अगर_usb_submit_rx_urb_fwload(cardp);
		पूर्ण
		kमुक्त_skb(skb);
		वापस;
	पूर्ण
	अगर (cardp->bootcmdresp <= 0) अणु
		स_नकल (&bootcmdresp, skb->data + IPFIELD_ALIGN_OFFSET,
			माप(bootcmdresp));

		अगर (le16_to_cpu(cardp->udev->descriptor.bcdDevice) < 0x3106) अणु
			kमुक्त_skb(skb);
			अगर_usb_submit_rx_urb_fwload(cardp);
			cardp->bootcmdresp = BOOT_CMD_RESP_OK;
			lbs_deb_usbd(&cardp->udev->dev,
				     "Received valid boot command response\n");
			वापस;
		पूर्ण
		अगर (bootcmdresp.magic != cpu_to_le32(BOOT_CMD_MAGIC_NUMBER)) अणु
			अगर (bootcmdresp.magic == cpu_to_le32(CMD_TYPE_REQUEST) ||
			    bootcmdresp.magic == cpu_to_le32(CMD_TYPE_DATA) ||
			    bootcmdresp.magic == cpu_to_le32(CMD_TYPE_INDICATION)) अणु
				अगर (!cardp->bootcmdresp)
					pr_info("Firmware already seems alive; resetting\n");
				cardp->bootcmdresp = -1;
			पूर्ण अन्यथा अणु
				pr_info("boot cmd response wrong magic number (0x%x)\n",
					    le32_to_cpu(bootcmdresp.magic));
			पूर्ण
		पूर्ण अन्यथा अगर ((bootcmdresp.cmd != BOOT_CMD_FW_BY_USB) &&
			   (bootcmdresp.cmd != BOOT_CMD_UPDATE_FW) &&
			   (bootcmdresp.cmd != BOOT_CMD_UPDATE_BOOT2)) अणु
			pr_info("boot cmd response cmd_tag error (%d)\n",
				bootcmdresp.cmd);
		पूर्ण अन्यथा अगर (bootcmdresp.result != BOOT_CMD_RESP_OK) अणु
			pr_info("boot cmd response result error (%d)\n",
				bootcmdresp.result);
		पूर्ण अन्यथा अणु
			cardp->bootcmdresp = 1;
			lbs_deb_usbd(&cardp->udev->dev,
				     "Received valid boot command response\n");
		पूर्ण
		kमुक्त_skb(skb);
		अगर_usb_submit_rx_urb_fwload(cardp);
		वापस;
	पूर्ण

	syncfwheader = kmemdup(skb->data + IPFIELD_ALIGN_OFFSET,
			       माप(काष्ठा fwsyncheader), GFP_ATOMIC);
	अगर (!syncfwheader) अणु
		lbs_deb_usbd(&cardp->udev->dev, "Failure to allocate syncfwheader\n");
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	अगर (!syncfwheader->cmd) अणु
		lbs_deb_usb2(&cardp->udev->dev, "FW received Blk with correct CRC\n");
		lbs_deb_usb2(&cardp->udev->dev, "FW received Blk seqnum = %d\n",
			     le32_to_cpu(syncfwheader->seqnum));
		cardp->CRC_OK = 1;
	पूर्ण अन्यथा अणु
		lbs_deb_usbd(&cardp->udev->dev, "FW received Blk with CRC error\n");
		cardp->CRC_OK = 0;
	पूर्ण

	kमुक्त_skb(skb);

	/* Give device 5s to either ग_लिखो firmware to its RAM or eeprom */
	mod_समयr(&cardp->fw_समयout, jअगरfies + (HZ*5));

	अगर (cardp->fwfinalblk) अणु
		cardp->fwdnlकरोver = 1;
		जाओ निकास;
	पूर्ण

	अगर_usb_send_fw_pkt(cardp);

 निकास:
	अगर_usb_submit_rx_urb_fwload(cardp);

	kमुक्त(syncfwheader);
पूर्ण

#घोषणा MRVDRV_MIN_PKT_LEN	30

अटल अंतरभूत व्योम process_cmdtypedata(पूर्णांक recvlength, काष्ठा sk_buff *skb,
				       काष्ठा अगर_usb_card *cardp,
				       काष्ठा lbs_निजी *priv)
अणु
	अगर (recvlength > MRVDRV_ETH_RX_PACKET_BUFFER_SIZE + MESSAGE_HEADER_LEN
	    || recvlength < MRVDRV_MIN_PKT_LEN) अणु
		lbs_deb_usbd(&cardp->udev->dev, "Packet length is Invalid\n");
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	skb_reserve(skb, IPFIELD_ALIGN_OFFSET);
	skb_put(skb, recvlength);
	skb_pull(skb, MESSAGE_HEADER_LEN);

	lbs_process_rxed_packet(priv, skb);
पूर्ण

अटल अंतरभूत व्योम process_cmdrequest(पूर्णांक recvlength, uपूर्णांक8_t *recvbuff,
				      काष्ठा sk_buff *skb,
				      काष्ठा अगर_usb_card *cardp,
				      काष्ठा lbs_निजी *priv)
अणु
	अचिन्हित दीर्घ flags;
	u8 i;

	अगर (recvlength > LBS_CMD_BUFFER_SIZE) अणु
		lbs_deb_usbd(&cardp->udev->dev,
			     "The receive buffer is too large\n");
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	spin_lock_irqsave(&priv->driver_lock, flags);

	i = (priv->resp_idx == 0) ? 1 : 0;
	BUG_ON(priv->resp_len[i]);
	priv->resp_len[i] = (recvlength - MESSAGE_HEADER_LEN);
	स_नकल(priv->resp_buf[i], recvbuff + MESSAGE_HEADER_LEN,
		priv->resp_len[i]);
	kमुक्त_skb(skb);
	lbs_notअगरy_command_response(priv, i);

	spin_unlock_irqrestore(&priv->driver_lock, flags);

	lbs_deb_usbd(&cardp->udev->dev,
		    "Wake up main thread to handle cmd response\n");
पूर्ण

/**
 *  अगर_usb_receive - पढ़ो the packet पूर्णांकo the upload buffer,
 *  wake up the मुख्य thपढ़ो and initialise the Rx callack
 *
 *  @urb:	poपूर्णांकer to &काष्ठा urb
 *  वापसs:	N/A
 */
अटल व्योम अगर_usb_receive(काष्ठा urb *urb)
अणु
	काष्ठा अगर_usb_card *cardp = urb->context;
	काष्ठा sk_buff *skb = cardp->rx_skb;
	काष्ठा lbs_निजी *priv = cardp->priv;
	पूर्णांक recvlength = urb->actual_length;
	uपूर्णांक8_t *recvbuff = शून्य;
	uपूर्णांक32_t recvtype = 0;
	__le32 *pkt = (__le32 *)(skb->data + IPFIELD_ALIGN_OFFSET);
	uपूर्णांक32_t event;

	अगर (recvlength) अणु
		अगर (urb->status) अणु
			lbs_deb_usbd(&cardp->udev->dev, "RX URB failed: %d\n",
				     urb->status);
			kमुक्त_skb(skb);
			जाओ setup_क्रम_next;
		पूर्ण

		recvbuff = skb->data + IPFIELD_ALIGN_OFFSET;
		recvtype = le32_to_cpu(pkt[0]);
		lbs_deb_usbd(&cardp->udev->dev,
			    "Recv length = 0x%x, Recv type = 0x%X\n",
			    recvlength, recvtype);
	पूर्ण अन्यथा अगर (urb->status) अणु
		kमुक्त_skb(skb);
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
		/* Event handling */
		event = le32_to_cpu(pkt[1]);
		lbs_deb_usbd(&cardp->udev->dev, "**EVENT** 0x%X\n", event);
		kमुक्त_skb(skb);

		/* Icky unकरोcumented magic special हाल */
		अगर (event & 0xffff0000) अणु
			u32 trycount = (event & 0xffff0000) >> 16;

			lbs_send_tx_feedback(priv, trycount);
		पूर्ण अन्यथा
			lbs_queue_event(priv, event & 0xFF);
		अवरोध;

	शेष:
		lbs_deb_usbd(&cardp->udev->dev, "Unknown command type 0x%X\n",
			     recvtype);
		kमुक्त_skb(skb);
		अवरोध;
	पूर्ण

setup_क्रम_next:
	अगर_usb_submit_rx_urb(cardp);
पूर्ण

/**
 *  अगर_usb_host_to_card - करोwnloads data to FW
 *  @priv:	poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 *  @type:	type of data
 *  @payload:	poपूर्णांकer to data buffer
 *  @nb:	number of bytes
 *  वापसs:	0 क्रम success or negative error code
 */
अटल पूर्णांक अगर_usb_host_to_card(काष्ठा lbs_निजी *priv, uपूर्णांक8_t type,
			       uपूर्णांक8_t *payload, uपूर्णांक16_t nb)
अणु
	काष्ठा अगर_usb_card *cardp = priv->card;

	lbs_deb_usbd(&cardp->udev->dev,"*** type = %u\n", type);
	lbs_deb_usbd(&cardp->udev->dev,"size after = %d\n", nb);

	अगर (type == MVMS_CMD) अणु
		*(__le32 *)cardp->ep_out_buf = cpu_to_le32(CMD_TYPE_REQUEST);
		priv->dnld_sent = DNLD_CMD_SENT;
	पूर्ण अन्यथा अणु
		*(__le32 *)cardp->ep_out_buf = cpu_to_le32(CMD_TYPE_DATA);
		priv->dnld_sent = DNLD_DATA_SENT;
	पूर्ण

	स_नकल((cardp->ep_out_buf + MESSAGE_HEADER_LEN), payload, nb);

	वापस usb_tx_block(cardp, cardp->ep_out_buf, nb + MESSAGE_HEADER_LEN);
पूर्ण

/**
 *  अगर_usb_issue_boot_command - issues Boot command to the Boot2 code
 *  @cardp:	poपूर्णांकer to &अगर_usb_card
 *  @ivalue:	1:Boot from FW by USB-Download
 *		2:Boot from FW in EEPROM
 *  वापसs:	0 क्रम success or negative error code
 */
अटल पूर्णांक अगर_usb_issue_boot_command(काष्ठा अगर_usb_card *cardp, पूर्णांक ivalue)
अणु
	काष्ठा bootcmd *bootcmd = cardp->ep_out_buf;

	/* Prepare command */
	bootcmd->magic = cpu_to_le32(BOOT_CMD_MAGIC_NUMBER);
	bootcmd->cmd = ivalue;
	स_रखो(bootcmd->pad, 0, माप(bootcmd->pad));

	/* Issue command */
	usb_tx_block(cardp, cardp->ep_out_buf, माप(*bootcmd));

	वापस 0;
पूर्ण


/**
 *  check_fwfile_क्रमmat - check the validity of Boot2/FW image
 *
 *  @data:	poपूर्णांकer to image
 *  @totlen:	image length
 *  वापसs:     0 (good) or 1 (failure)
 */
अटल पूर्णांक check_fwfile_क्रमmat(स्थिर uपूर्णांक8_t *data, uपूर्णांक32_t totlen)
अणु
	uपूर्णांक32_t bincmd, निकास;
	uपूर्णांक32_t blksize, offset, len;
	पूर्णांक ret;

	ret = 1;
	निकास = len = 0;

	करो अणु
		काष्ठा fwheader *fwh = (व्योम *)data;

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
		lbs_deb_fw("firmware file format check PASS\n");

	वापस ret;
पूर्ण

अटल व्योम अगर_usb_prog_firmware(काष्ठा lbs_निजी *priv, पूर्णांक ret,
				 स्थिर काष्ठा firmware *fw,
				 स्थिर काष्ठा firmware *unused)
अणु
	काष्ठा अगर_usb_card *cardp = priv->card;
	पूर्णांक i = 0;
	अटल पूर्णांक reset_count = 10;

	अगर (ret) अणु
		pr_err("failed to find firmware (%d)\n", ret);
		जाओ करोne;
	पूर्ण

	cardp->fw = fw;
	अगर (check_fwfile_क्रमmat(cardp->fw->data, cardp->fw->size)) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	/* Cancel any pending usb business */
	usb_समाप्त_urb(cardp->rx_urb);
	usb_समाप्त_urb(cardp->tx_urb);

	cardp->fwlastblksent = 0;
	cardp->fwdnlकरोver = 0;
	cardp->totalbytes = 0;
	cardp->fwfinalblk = 0;
	cardp->bootcmdresp = 0;

restart:
	अगर (अगर_usb_submit_rx_urb_fwload(cardp) < 0) अणु
		lbs_deb_usbd(&cardp->udev->dev, "URB submission is failed\n");
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	cardp->bootcmdresp = 0;
	करो अणु
		पूर्णांक j = 0;
		i++;
		अगर_usb_issue_boot_command(cardp, BOOT_CMD_FW_BY_USB);
		/* रुको क्रम command response */
		करो अणु
			j++;
			msleep_पूर्णांकerruptible(100);
		पूर्ण जबतक (cardp->bootcmdresp == 0 && j < 10);
	पूर्ण जबतक (cardp->bootcmdresp == 0 && i < 5);

	अगर (cardp->bootcmdresp == BOOT_CMD_RESP_NOT_SUPPORTED) अणु
		/* Return to normal operation */
		ret = -EOPNOTSUPP;
		usb_समाप्त_urb(cardp->rx_urb);
		usb_समाप्त_urb(cardp->tx_urb);
		अगर (अगर_usb_submit_rx_urb(cardp) < 0)
			ret = -EIO;
		जाओ करोne;
	पूर्ण अन्यथा अगर (cardp->bootcmdresp <= 0) अणु
		अगर (--reset_count >= 0) अणु
			अगर_usb_reset_device(cardp);
			जाओ restart;
		पूर्ण
		ret = -EIO;
		जाओ करोne;
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
	रुको_event_पूर्णांकerruptible(cardp->fw_wq, cardp->surprise_हटाओd || cardp->fwdnlकरोver);

	del_समयr_sync(&cardp->fw_समयout);
	usb_समाप्त_urb(cardp->rx_urb);

	अगर (!cardp->fwdnlकरोver) अणु
		pr_info("failed to load fw, resetting device!\n");
		अगर (--reset_count >= 0) अणु
			अगर_usb_reset_device(cardp);
			जाओ restart;
		पूर्ण

		pr_info("FW download failure, time = %d ms\n", i * 100);
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	cardp->priv->fw_पढ़ोy = 1;
	अगर_usb_submit_rx_urb(cardp);

	अगर (lbs_start_card(priv))
		जाओ करोne;

	अगर_usb_setup_firmware(priv);

	/*
	 * EHS_REMOVE_WAKEUP is not supported on all versions of the firmware.
	 */
	priv->wol_criteria = EHS_REMOVE_WAKEUP;
	अगर (lbs_host_sleep_cfg(priv, priv->wol_criteria, शून्य))
		priv->ehs_हटाओ_supported = false;

 करोne:
	cardp->fw = शून्य;
पूर्ण


#अगर_घोषित CONFIG_PM
अटल पूर्णांक अगर_usb_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा अगर_usb_card *cardp = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा lbs_निजी *priv = cardp->priv;
	पूर्णांक ret;

	अगर (priv->psstate != PS_STATE_FULL_POWER) अणु
		ret = -1;
		जाओ out;
	पूर्ण

#अगर_घोषित CONFIG_OLPC
	अगर (machine_is_olpc()) अणु
		अगर (priv->wol_criteria == EHS_REMOVE_WAKEUP)
			olpc_ec_wakeup_clear(EC_SCI_SRC_WLAN);
		अन्यथा
			olpc_ec_wakeup_set(EC_SCI_SRC_WLAN);
	पूर्ण
#पूर्ण_अगर

	ret = lbs_suspend(priv);
	अगर (ret)
		जाओ out;

	/* Unlink tx & rx urb */
	usb_समाप्त_urb(cardp->tx_urb);
	usb_समाप्त_urb(cardp->rx_urb);

 out:
	वापस ret;
पूर्ण

अटल पूर्णांक अगर_usb_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा अगर_usb_card *cardp = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा lbs_निजी *priv = cardp->priv;

	अगर_usb_submit_rx_urb(cardp);

	lbs_resume(priv);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा अगर_usb_suspend शून्य
#घोषणा अगर_usb_resume शून्य
#पूर्ण_अगर

अटल काष्ठा usb_driver अगर_usb_driver = अणु
	.name = DRV_NAME,
	.probe = अगर_usb_probe,
	.disconnect = अगर_usb_disconnect,
	.id_table = अगर_usb_table,
	.suspend = अगर_usb_suspend,
	.resume = अगर_usb_resume,
	.reset_resume = अगर_usb_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(अगर_usb_driver);

MODULE_DESCRIPTION("8388 USB WLAN Driver");
MODULE_AUTHOR("Marvell International Ltd. and Red Hat, Inc.");
MODULE_LICENSE("GPL");
