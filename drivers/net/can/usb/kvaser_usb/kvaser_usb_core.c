<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Parts of this driver are based on the following:
 *  - Kvaser linux leaf driver (version 4.78)
 *  - CAN driver क्रम esd CAN-USB/2
 *  - Kvaser linux usbcanII driver (version 5.3)
 *  - Kvaser linux mhydra driver (version 5.24)
 *
 * Copyright (C) 2002-2018 KVASER AB, Sweden. All rights reserved.
 * Copyright (C) 2010 Matthias Fuchs <matthias.fuchs@esd.eu>, esd gmbh
 * Copyright (C) 2012 Olivier Sobrie <olivier@sobrie.be>
 * Copyright (C) 2015 Valeo S.A.
 */

#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अगर.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/usb.h>

#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>
#समावेश <linux/can/netlink.h>

#समावेश "kvaser_usb.h"

/* Kvaser USB venकरोr id. */
#घोषणा KVASER_VENDOR_ID			0x0bfd

/* Kvaser Leaf USB devices product ids */
#घोषणा USB_LEAF_DEVEL_PRODUCT_ID		10
#घोषणा USB_LEAF_LITE_PRODUCT_ID		11
#घोषणा USB_LEAF_PRO_PRODUCT_ID			12
#घोषणा USB_LEAF_SPRO_PRODUCT_ID		14
#घोषणा USB_LEAF_PRO_LS_PRODUCT_ID		15
#घोषणा USB_LEAF_PRO_SWC_PRODUCT_ID		16
#घोषणा USB_LEAF_PRO_LIN_PRODUCT_ID		17
#घोषणा USB_LEAF_SPRO_LS_PRODUCT_ID		18
#घोषणा USB_LEAF_SPRO_SWC_PRODUCT_ID		19
#घोषणा USB_MEMO2_DEVEL_PRODUCT_ID		22
#घोषणा USB_MEMO2_HSHS_PRODUCT_ID		23
#घोषणा USB_UPRO_HSHS_PRODUCT_ID		24
#घोषणा USB_LEAF_LITE_GI_PRODUCT_ID		25
#घोषणा USB_LEAF_PRO_OBDII_PRODUCT_ID		26
#घोषणा USB_MEMO2_HSLS_PRODUCT_ID		27
#घोषणा USB_LEAF_LITE_CH_PRODUCT_ID		28
#घोषणा USB_BLACKBIRD_SPRO_PRODUCT_ID		29
#घोषणा USB_OEM_MERCURY_PRODUCT_ID		34
#घोषणा USB_OEM_LEAF_PRODUCT_ID			35
#घोषणा USB_CAN_R_PRODUCT_ID			39
#घोषणा USB_LEAF_LITE_V2_PRODUCT_ID		288
#घोषणा USB_MINI_PCIE_HS_PRODUCT_ID		289
#घोषणा USB_LEAF_LIGHT_HS_V2_OEM_PRODUCT_ID	290
#घोषणा USB_USBCAN_LIGHT_2HS_PRODUCT_ID		291
#घोषणा USB_MINI_PCIE_2HS_PRODUCT_ID		292
#घोषणा USB_USBCAN_R_V2_PRODUCT_ID		294
#घोषणा USB_LEAF_LIGHT_R_V2_PRODUCT_ID		295
#घोषणा USB_LEAF_LIGHT_HS_V2_OEM2_PRODUCT_ID	296
#घोषणा USB_LEAF_PRODUCT_ID_END \
	USB_LEAF_LIGHT_HS_V2_OEM2_PRODUCT_ID

/* Kvaser USBCan-II devices product ids */
#घोषणा USB_USBCAN_REVB_PRODUCT_ID		2
#घोषणा USB_VCI2_PRODUCT_ID			3
#घोषणा USB_USBCAN2_PRODUCT_ID			4
#घोषणा USB_MEMORATOR_PRODUCT_ID		5

/* Kvaser Minihydra USB devices product ids */
#घोषणा USB_BLACKBIRD_V2_PRODUCT_ID		258
#घोषणा USB_MEMO_PRO_5HS_PRODUCT_ID		260
#घोषणा USB_USBCAN_PRO_5HS_PRODUCT_ID		261
#घोषणा USB_USBCAN_LIGHT_4HS_PRODUCT_ID		262
#घोषणा USB_LEAF_PRO_HS_V2_PRODUCT_ID		263
#घोषणा USB_USBCAN_PRO_2HS_V2_PRODUCT_ID	264
#घोषणा USB_MEMO_2HS_PRODUCT_ID			265
#घोषणा USB_MEMO_PRO_2HS_V2_PRODUCT_ID		266
#घोषणा USB_HYBRID_CANLIN_PRODUCT_ID		267
#घोषणा USB_ATI_USBCAN_PRO_2HS_V2_PRODUCT_ID	268
#घोषणा USB_ATI_MEMO_PRO_2HS_V2_PRODUCT_ID	269
#घोषणा USB_HYBRID_PRO_CANLIN_PRODUCT_ID	270
#घोषणा USB_U100_PRODUCT_ID			273
#घोषणा USB_U100P_PRODUCT_ID			274
#घोषणा USB_U100S_PRODUCT_ID			275
#घोषणा USB_USBCAN_PRO_4HS_PRODUCT_ID		276
#घोषणा USB_HYDRA_PRODUCT_ID_END \
	USB_USBCAN_PRO_4HS_PRODUCT_ID

अटल अंतरभूत bool kvaser_is_leaf(स्थिर काष्ठा usb_device_id *id)
अणु
	वापस (id->idProduct >= USB_LEAF_DEVEL_PRODUCT_ID &&
		id->idProduct <= USB_CAN_R_PRODUCT_ID) ||
		(id->idProduct >= USB_LEAF_LITE_V2_PRODUCT_ID &&
		 id->idProduct <= USB_LEAF_PRODUCT_ID_END);
पूर्ण

अटल अंतरभूत bool kvaser_is_usbcan(स्थिर काष्ठा usb_device_id *id)
अणु
	वापस id->idProduct >= USB_USBCAN_REVB_PRODUCT_ID &&
	       id->idProduct <= USB_MEMORATOR_PRODUCT_ID;
पूर्ण

अटल अंतरभूत bool kvaser_is_hydra(स्थिर काष्ठा usb_device_id *id)
अणु
	वापस id->idProduct >= USB_BLACKBIRD_V2_PRODUCT_ID &&
	       id->idProduct <= USB_HYDRA_PRODUCT_ID_END;
पूर्ण

अटल स्थिर काष्ठा usb_device_id kvaser_usb_table[] = अणु
	/* Leaf USB product IDs */
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_LEAF_DEVEL_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_LEAF_LITE_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_LEAF_PRO_PRODUCT_ID),
		.driver_info = KVASER_USB_HAS_TXRX_ERRORS |
			       KVASER_USB_HAS_SILENT_MODE पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_LEAF_SPRO_PRODUCT_ID),
		.driver_info = KVASER_USB_HAS_TXRX_ERRORS |
			       KVASER_USB_HAS_SILENT_MODE पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_LEAF_PRO_LS_PRODUCT_ID),
		.driver_info = KVASER_USB_HAS_TXRX_ERRORS |
			       KVASER_USB_HAS_SILENT_MODE पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_LEAF_PRO_SWC_PRODUCT_ID),
		.driver_info = KVASER_USB_HAS_TXRX_ERRORS |
			       KVASER_USB_HAS_SILENT_MODE पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_LEAF_PRO_LIN_PRODUCT_ID),
		.driver_info = KVASER_USB_HAS_TXRX_ERRORS |
			       KVASER_USB_HAS_SILENT_MODE पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_LEAF_SPRO_LS_PRODUCT_ID),
		.driver_info = KVASER_USB_HAS_TXRX_ERRORS |
			       KVASER_USB_HAS_SILENT_MODE पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_LEAF_SPRO_SWC_PRODUCT_ID),
		.driver_info = KVASER_USB_HAS_TXRX_ERRORS |
			       KVASER_USB_HAS_SILENT_MODE पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_MEMO2_DEVEL_PRODUCT_ID),
		.driver_info = KVASER_USB_HAS_TXRX_ERRORS |
			       KVASER_USB_HAS_SILENT_MODE पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_MEMO2_HSHS_PRODUCT_ID),
		.driver_info = KVASER_USB_HAS_TXRX_ERRORS |
			       KVASER_USB_HAS_SILENT_MODE पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_UPRO_HSHS_PRODUCT_ID),
		.driver_info = KVASER_USB_HAS_TXRX_ERRORS पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_LEAF_LITE_GI_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_LEAF_PRO_OBDII_PRODUCT_ID),
		.driver_info = KVASER_USB_HAS_TXRX_ERRORS |
			       KVASER_USB_HAS_SILENT_MODE पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_MEMO2_HSLS_PRODUCT_ID),
		.driver_info = KVASER_USB_HAS_TXRX_ERRORS पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_LEAF_LITE_CH_PRODUCT_ID),
		.driver_info = KVASER_USB_HAS_TXRX_ERRORS पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_BLACKBIRD_SPRO_PRODUCT_ID),
		.driver_info = KVASER_USB_HAS_TXRX_ERRORS पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_OEM_MERCURY_PRODUCT_ID),
		.driver_info = KVASER_USB_HAS_TXRX_ERRORS पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_OEM_LEAF_PRODUCT_ID),
		.driver_info = KVASER_USB_HAS_TXRX_ERRORS पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_CAN_R_PRODUCT_ID),
		.driver_info = KVASER_USB_HAS_TXRX_ERRORS पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_LEAF_LITE_V2_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_MINI_PCIE_HS_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_LEAF_LIGHT_HS_V2_OEM_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_USBCAN_LIGHT_2HS_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_MINI_PCIE_2HS_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_USBCAN_R_V2_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_LEAF_LIGHT_R_V2_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_LEAF_LIGHT_HS_V2_OEM2_PRODUCT_ID) पूर्ण,

	/* USBCANII USB product IDs */
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_USBCAN2_PRODUCT_ID),
		.driver_info = KVASER_USB_HAS_TXRX_ERRORS पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_USBCAN_REVB_PRODUCT_ID),
		.driver_info = KVASER_USB_HAS_TXRX_ERRORS पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_MEMORATOR_PRODUCT_ID),
		.driver_info = KVASER_USB_HAS_TXRX_ERRORS पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_VCI2_PRODUCT_ID),
		.driver_info = KVASER_USB_HAS_TXRX_ERRORS पूर्ण,

	/* Minihydra USB product IDs */
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_BLACKBIRD_V2_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_MEMO_PRO_5HS_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_USBCAN_PRO_5HS_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_USBCAN_LIGHT_4HS_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_LEAF_PRO_HS_V2_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_USBCAN_PRO_2HS_V2_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_MEMO_2HS_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_MEMO_PRO_2HS_V2_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_HYBRID_CANLIN_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_ATI_USBCAN_PRO_2HS_V2_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_ATI_MEMO_PRO_2HS_V2_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_HYBRID_PRO_CANLIN_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_U100_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_U100P_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_U100S_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KVASER_VENDOR_ID, USB_USBCAN_PRO_4HS_PRODUCT_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, kvaser_usb_table);

पूर्णांक kvaser_usb_send_cmd(स्थिर काष्ठा kvaser_usb *dev, व्योम *cmd, पूर्णांक len)
अणु
	पूर्णांक actual_len; /* Not used */

	वापस usb_bulk_msg(dev->udev,
			    usb_sndbulkpipe(dev->udev,
					    dev->bulk_out->bEndpoपूर्णांकAddress),
			    cmd, len, &actual_len, KVASER_USB_TIMEOUT);
पूर्ण

पूर्णांक kvaser_usb_recv_cmd(स्थिर काष्ठा kvaser_usb *dev, व्योम *cmd, पूर्णांक len,
			पूर्णांक *actual_len)
अणु
	वापस usb_bulk_msg(dev->udev,
			    usb_rcvbulkpipe(dev->udev,
					    dev->bulk_in->bEndpoपूर्णांकAddress),
			    cmd, len, actual_len, KVASER_USB_TIMEOUT);
पूर्ण

अटल व्योम kvaser_usb_send_cmd_callback(काष्ठा urb *urb)
अणु
	काष्ठा net_device *netdev = urb->context;

	kमुक्त(urb->transfer_buffer);

	अगर (urb->status)
		netdev_warn(netdev, "urb status received: %d\n", urb->status);
पूर्ण

पूर्णांक kvaser_usb_send_cmd_async(काष्ठा kvaser_usb_net_priv *priv, व्योम *cmd,
			      पूर्णांक len)
अणु
	काष्ठा kvaser_usb *dev = priv->dev;
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा urb *urb;
	पूर्णांक err;

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb)
		वापस -ENOMEM;

	usb_fill_bulk_urb(urb, dev->udev,
			  usb_sndbulkpipe(dev->udev,
					  dev->bulk_out->bEndpoपूर्णांकAddress),
			  cmd, len, kvaser_usb_send_cmd_callback, netdev);
	usb_anchor_urb(urb, &priv->tx_submitted);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err) अणु
		netdev_err(netdev, "Error transmitting URB\n");
		usb_unanchor_urb(urb);
	पूर्ण
	usb_मुक्त_urb(urb);

	वापस 0;
पूर्ण

पूर्णांक kvaser_usb_can_rx_over_error(काष्ठा net_device *netdev)
अणु
	काष्ठा net_device_stats *stats = &netdev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;

	stats->rx_over_errors++;
	stats->rx_errors++;

	skb = alloc_can_err_skb(netdev, &cf);
	अगर (!skb) अणु
		stats->rx_dropped++;
		netdev_warn(netdev, "No memory left for err_skb\n");
		वापस -ENOMEM;
	पूर्ण

	cf->can_id |= CAN_ERR_CRTL;
	cf->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;

	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_rx(skb);

	वापस 0;
पूर्ण

अटल व्योम kvaser_usb_पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा kvaser_usb *dev = urb->context;
	पूर्णांक err;
	अचिन्हित पूर्णांक i;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध;
	हाल -ENOENT:
	हाल -EPIPE:
	हाल -EPROTO:
	हाल -ESHUTDOWN:
		वापस;
	शेष:
		dev_info(&dev->पूर्णांकf->dev, "Rx URB aborted (%d)\n", urb->status);
		जाओ resubmit_urb;
	पूर्ण

	dev->ops->dev_पढ़ो_bulk_callback(dev, urb->transfer_buffer,
					 urb->actual_length);

resubmit_urb:
	usb_fill_bulk_urb(urb, dev->udev,
			  usb_rcvbulkpipe(dev->udev,
					  dev->bulk_in->bEndpoपूर्णांकAddress),
			  urb->transfer_buffer, KVASER_USB_RX_BUFFER_SIZE,
			  kvaser_usb_पढ़ो_bulk_callback, dev);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err == -ENODEV) अणु
		क्रम (i = 0; i < dev->nchannels; i++) अणु
			अगर (!dev->nets[i])
				जारी;

			netअगर_device_detach(dev->nets[i]->netdev);
		पूर्ण
	पूर्ण अन्यथा अगर (err) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"Failed resubmitting read bulk urb: %d\n", err);
	पूर्ण
पूर्ण

अटल पूर्णांक kvaser_usb_setup_rx_urbs(काष्ठा kvaser_usb *dev)
अणु
	पूर्णांक i, err = 0;

	अगर (dev->rxinitकरोne)
		वापस 0;

	क्रम (i = 0; i < KVASER_USB_MAX_RX_URBS; i++) अणु
		काष्ठा urb *urb = शून्य;
		u8 *buf = शून्य;
		dma_addr_t buf_dma;

		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		buf = usb_alloc_coherent(dev->udev, KVASER_USB_RX_BUFFER_SIZE,
					 GFP_KERNEL, &buf_dma);
		अगर (!buf) अणु
			dev_warn(&dev->पूर्णांकf->dev,
				 "No memory left for USB buffer\n");
			usb_मुक्त_urb(urb);
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		usb_fill_bulk_urb(urb, dev->udev,
				  usb_rcvbulkpipe
					(dev->udev,
					 dev->bulk_in->bEndpoपूर्णांकAddress),
				  buf, KVASER_USB_RX_BUFFER_SIZE,
				  kvaser_usb_पढ़ो_bulk_callback, dev);
		urb->transfer_dma = buf_dma;
		urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		usb_anchor_urb(urb, &dev->rx_submitted);

		err = usb_submit_urb(urb, GFP_KERNEL);
		अगर (err) अणु
			usb_unanchor_urb(urb);
			usb_मुक्त_coherent(dev->udev,
					  KVASER_USB_RX_BUFFER_SIZE, buf,
					  buf_dma);
			usb_मुक्त_urb(urb);
			अवरोध;
		पूर्ण

		dev->rxbuf[i] = buf;
		dev->rxbuf_dma[i] = buf_dma;

		usb_मुक्त_urb(urb);
	पूर्ण

	अगर (i == 0) अणु
		dev_warn(&dev->पूर्णांकf->dev, "Cannot setup read URBs, error %d\n",
			 err);
		वापस err;
	पूर्ण अन्यथा अगर (i < KVASER_USB_MAX_RX_URBS) अणु
		dev_warn(&dev->पूर्णांकf->dev, "RX performances may be slow\n");
	पूर्ण

	dev->rxinitकरोne = true;

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_usb_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा kvaser_usb_net_priv *priv = netdev_priv(netdev);
	काष्ठा kvaser_usb *dev = priv->dev;
	पूर्णांक err;

	err = खोलो_candev(netdev);
	अगर (err)
		वापस err;

	err = kvaser_usb_setup_rx_urbs(dev);
	अगर (err)
		जाओ error;

	err = dev->ops->dev_set_opt_mode(priv);
	अगर (err)
		जाओ error;

	err = dev->ops->dev_start_chip(priv);
	अगर (err) अणु
		netdev_warn(netdev, "Cannot start device, error %d\n", err);
		जाओ error;
	पूर्ण

	priv->can.state = CAN_STATE_ERROR_ACTIVE;

	वापस 0;

error:
	बंद_candev(netdev);
	वापस err;
पूर्ण

अटल व्योम kvaser_usb_reset_tx_urb_contexts(काष्ठा kvaser_usb_net_priv *priv)
अणु
	पूर्णांक i, max_tx_urbs;

	max_tx_urbs = priv->dev->max_tx_urbs;

	priv->active_tx_contexts = 0;
	क्रम (i = 0; i < max_tx_urbs; i++)
		priv->tx_contexts[i].echo_index = max_tx_urbs;
पूर्ण

/* This method might sleep. Do not call it in the atomic context
 * of URB completions.
 */
अटल व्योम kvaser_usb_unlink_tx_urbs(काष्ठा kvaser_usb_net_priv *priv)
अणु
	usb_समाप्त_anchored_urbs(&priv->tx_submitted);
	kvaser_usb_reset_tx_urb_contexts(priv);
पूर्ण

अटल व्योम kvaser_usb_unlink_all_urbs(काष्ठा kvaser_usb *dev)
अणु
	पूर्णांक i;

	usb_समाप्त_anchored_urbs(&dev->rx_submitted);

	क्रम (i = 0; i < KVASER_USB_MAX_RX_URBS; i++)
		usb_मुक्त_coherent(dev->udev, KVASER_USB_RX_BUFFER_SIZE,
				  dev->rxbuf[i], dev->rxbuf_dma[i]);

	क्रम (i = 0; i < dev->nchannels; i++) अणु
		काष्ठा kvaser_usb_net_priv *priv = dev->nets[i];

		अगर (priv)
			kvaser_usb_unlink_tx_urbs(priv);
	पूर्ण
पूर्ण

अटल पूर्णांक kvaser_usb_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा kvaser_usb_net_priv *priv = netdev_priv(netdev);
	काष्ठा kvaser_usb *dev = priv->dev;
	पूर्णांक err;

	netअगर_stop_queue(netdev);

	err = dev->ops->dev_flush_queue(priv);
	अगर (err)
		netdev_warn(netdev, "Cannot flush queue, error %d\n", err);

	अगर (dev->ops->dev_reset_chip) अणु
		err = dev->ops->dev_reset_chip(dev, priv->channel);
		अगर (err)
			netdev_warn(netdev, "Cannot reset card, error %d\n",
				    err);
	पूर्ण

	err = dev->ops->dev_stop_chip(priv);
	अगर (err)
		netdev_warn(netdev, "Cannot stop device, error %d\n", err);

	/* reset tx contexts */
	kvaser_usb_unlink_tx_urbs(priv);

	priv->can.state = CAN_STATE_STOPPED;
	बंद_candev(priv->netdev);

	वापस 0;
पूर्ण

अटल व्योम kvaser_usb_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा kvaser_usb_tx_urb_context *context = urb->context;
	काष्ठा kvaser_usb_net_priv *priv;
	काष्ठा net_device *netdev;

	अगर (WARN_ON(!context))
		वापस;

	priv = context->priv;
	netdev = priv->netdev;

	kमुक्त(urb->transfer_buffer);

	अगर (!netअगर_device_present(netdev))
		वापस;

	अगर (urb->status)
		netdev_info(netdev, "Tx URB aborted (%d)\n", urb->status);
पूर्ण

अटल netdev_tx_t kvaser_usb_start_xmit(काष्ठा sk_buff *skb,
					 काष्ठा net_device *netdev)
अणु
	काष्ठा kvaser_usb_net_priv *priv = netdev_priv(netdev);
	काष्ठा kvaser_usb *dev = priv->dev;
	काष्ठा net_device_stats *stats = &netdev->stats;
	काष्ठा kvaser_usb_tx_urb_context *context = शून्य;
	काष्ठा urb *urb;
	व्योम *buf;
	पूर्णांक cmd_len = 0;
	पूर्णांक err, ret = NETDEV_TX_OK;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;

	अगर (can_dropped_invalid_skb(netdev, skb))
		वापस NETDEV_TX_OK;

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb) अणु
		stats->tx_dropped++;
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	spin_lock_irqsave(&priv->tx_contexts_lock, flags);
	क्रम (i = 0; i < dev->max_tx_urbs; i++) अणु
		अगर (priv->tx_contexts[i].echo_index == dev->max_tx_urbs) अणु
			context = &priv->tx_contexts[i];

			context->echo_index = i;
			++priv->active_tx_contexts;
			अगर (priv->active_tx_contexts >= (पूर्णांक)dev->max_tx_urbs)
				netअगर_stop_queue(netdev);

			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&priv->tx_contexts_lock, flags);

	/* This should never happen; it implies a flow control bug */
	अगर (!context) अणु
		netdev_warn(netdev, "cannot find free context\n");

		ret = NETDEV_TX_BUSY;
		जाओ मुक्तurb;
	पूर्ण

	buf = dev->ops->dev_frame_to_cmd(priv, skb, &context->dlc, &cmd_len,
					 context->echo_index);
	अगर (!buf) अणु
		stats->tx_dropped++;
		dev_kमुक्त_skb(skb);
		spin_lock_irqsave(&priv->tx_contexts_lock, flags);

		context->echo_index = dev->max_tx_urbs;
		--priv->active_tx_contexts;
		netअगर_wake_queue(netdev);

		spin_unlock_irqrestore(&priv->tx_contexts_lock, flags);
		जाओ मुक्तurb;
	पूर्ण

	context->priv = priv;

	can_put_echo_skb(skb, netdev, context->echo_index, 0);

	usb_fill_bulk_urb(urb, dev->udev,
			  usb_sndbulkpipe(dev->udev,
					  dev->bulk_out->bEndpoपूर्णांकAddress),
			  buf, cmd_len, kvaser_usb_ग_लिखो_bulk_callback,
			  context);
	usb_anchor_urb(urb, &priv->tx_submitted);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (unlikely(err)) अणु
		spin_lock_irqsave(&priv->tx_contexts_lock, flags);

		can_मुक्त_echo_skb(netdev, context->echo_index, शून्य);
		context->echo_index = dev->max_tx_urbs;
		--priv->active_tx_contexts;
		netअगर_wake_queue(netdev);

		spin_unlock_irqrestore(&priv->tx_contexts_lock, flags);

		usb_unanchor_urb(urb);
		kमुक्त(buf);

		stats->tx_dropped++;

		अगर (err == -ENODEV)
			netअगर_device_detach(netdev);
		अन्यथा
			netdev_warn(netdev, "Failed tx_urb %d\n", err);

		जाओ मुक्तurb;
	पूर्ण

	ret = NETDEV_TX_OK;

मुक्तurb:
	usb_मुक्त_urb(urb);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा net_device_ops kvaser_usb_netdev_ops = अणु
	.nकरो_खोलो = kvaser_usb_खोलो,
	.nकरो_stop = kvaser_usb_बंद,
	.nकरो_start_xmit = kvaser_usb_start_xmit,
	.nकरो_change_mtu = can_change_mtu,
पूर्ण;

अटल व्योम kvaser_usb_हटाओ_पूर्णांकerfaces(काष्ठा kvaser_usb *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dev->nchannels; i++) अणु
		अगर (!dev->nets[i])
			जारी;

		unरेजिस्टर_candev(dev->nets[i]->netdev);
	पूर्ण

	kvaser_usb_unlink_all_urbs(dev);

	क्रम (i = 0; i < dev->nchannels; i++) अणु
		अगर (!dev->nets[i])
			जारी;

		मुक्त_candev(dev->nets[i]->netdev);
	पूर्ण
पूर्ण

अटल पूर्णांक kvaser_usb_init_one(काष्ठा kvaser_usb *dev,
			       स्थिर काष्ठा usb_device_id *id, पूर्णांक channel)
अणु
	काष्ठा net_device *netdev;
	काष्ठा kvaser_usb_net_priv *priv;
	पूर्णांक err;

	अगर (dev->ops->dev_reset_chip) अणु
		err = dev->ops->dev_reset_chip(dev, channel);
		अगर (err)
			वापस err;
	पूर्ण

	netdev = alloc_candev(काष्ठा_size(priv, tx_contexts, dev->max_tx_urbs),
			      dev->max_tx_urbs);
	अगर (!netdev) अणु
		dev_err(&dev->पूर्णांकf->dev, "Cannot alloc candev\n");
		वापस -ENOMEM;
	पूर्ण

	priv = netdev_priv(netdev);

	init_usb_anchor(&priv->tx_submitted);
	init_completion(&priv->start_comp);
	init_completion(&priv->stop_comp);
	priv->can.ctrlmode_supported = 0;

	priv->dev = dev;
	priv->netdev = netdev;
	priv->channel = channel;

	spin_lock_init(&priv->tx_contexts_lock);
	kvaser_usb_reset_tx_urb_contexts(priv);

	priv->can.state = CAN_STATE_STOPPED;
	priv->can.घड़ी.freq = dev->cfg->घड़ी.freq;
	priv->can.bittiming_स्थिर = dev->cfg->bittiming_स्थिर;
	priv->can.करो_set_bittiming = dev->ops->dev_set_bittiming;
	priv->can.करो_set_mode = dev->ops->dev_set_mode;
	अगर ((id->driver_info & KVASER_USB_HAS_TXRX_ERRORS) ||
	    (priv->dev->card_data.capabilities & KVASER_USB_CAP_BERR_CAP))
		priv->can.करो_get_berr_counter = dev->ops->dev_get_berr_counter;
	अगर (id->driver_info & KVASER_USB_HAS_SILENT_MODE)
		priv->can.ctrlmode_supported |= CAN_CTRLMODE_LISTENONLY;

	priv->can.ctrlmode_supported |= dev->card_data.ctrlmode_supported;

	अगर (priv->can.ctrlmode_supported & CAN_CTRLMODE_FD) अणु
		priv->can.data_bittiming_स्थिर = dev->cfg->data_bittiming_स्थिर;
		priv->can.करो_set_data_bittiming =
					dev->ops->dev_set_data_bittiming;
	पूर्ण

	netdev->flags |= IFF_ECHO;

	netdev->netdev_ops = &kvaser_usb_netdev_ops;

	SET_NETDEV_DEV(netdev, &dev->पूर्णांकf->dev);
	netdev->dev_id = channel;

	dev->nets[channel] = priv;

	err = रेजिस्टर_candev(netdev);
	अगर (err) अणु
		dev_err(&dev->पूर्णांकf->dev, "Failed to register CAN device\n");
		मुक्त_candev(netdev);
		dev->nets[channel] = शून्य;
		वापस err;
	पूर्ण

	netdev_dbg(netdev, "device registered\n");

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			    स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा kvaser_usb *dev;
	पूर्णांक err;
	पूर्णांक i;

	dev = devm_kzalloc(&पूर्णांकf->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	अगर (kvaser_is_leaf(id)) अणु
		dev->card_data.leaf.family = KVASER_LEAF;
		dev->ops = &kvaser_usb_leaf_dev_ops;
	पूर्ण अन्यथा अगर (kvaser_is_usbcan(id)) अणु
		dev->card_data.leaf.family = KVASER_USBCAN;
		dev->ops = &kvaser_usb_leaf_dev_ops;
	पूर्ण अन्यथा अगर (kvaser_is_hydra(id)) अणु
		dev->ops = &kvaser_usb_hydra_dev_ops;
	पूर्ण अन्यथा अणु
		dev_err(&पूर्णांकf->dev,
			"Product ID (%d) is not a supported Kvaser USB device\n",
			id->idProduct);
		वापस -ENODEV;
	पूर्ण

	dev->पूर्णांकf = पूर्णांकf;

	err = dev->ops->dev_setup_endpoपूर्णांकs(dev);
	अगर (err) अणु
		dev_err(&पूर्णांकf->dev, "Cannot get usb endpoint(s)");
		वापस err;
	पूर्ण

	dev->udev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	init_usb_anchor(&dev->rx_submitted);

	usb_set_पूर्णांकfdata(पूर्णांकf, dev);

	dev->card_data.ctrlmode_supported = 0;
	dev->card_data.capabilities = 0;
	err = dev->ops->dev_init_card(dev);
	अगर (err) अणु
		dev_err(&पूर्णांकf->dev,
			"Failed to initialize card, error %d\n", err);
		वापस err;
	पूर्ण

	err = dev->ops->dev_get_software_info(dev);
	अगर (err) अणु
		dev_err(&पूर्णांकf->dev,
			"Cannot get software info, error %d\n", err);
		वापस err;
	पूर्ण

	अगर (dev->ops->dev_get_software_details) अणु
		err = dev->ops->dev_get_software_details(dev);
		अगर (err) अणु
			dev_err(&पूर्णांकf->dev,
				"Cannot get software details, error %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (WARN_ON(!dev->cfg))
		वापस -ENODEV;

	dev_dbg(&पूर्णांकf->dev, "Firmware version: %d.%d.%d\n",
		((dev->fw_version >> 24) & 0xff),
		((dev->fw_version >> 16) & 0xff),
		(dev->fw_version & 0xffff));

	dev_dbg(&पूर्णांकf->dev, "Max outstanding tx = %d URBs\n", dev->max_tx_urbs);

	err = dev->ops->dev_get_card_info(dev);
	अगर (err) अणु
		dev_err(&पूर्णांकf->dev, "Cannot get card info, error %d\n", err);
		वापस err;
	पूर्ण

	अगर (dev->ops->dev_get_capabilities) अणु
		err = dev->ops->dev_get_capabilities(dev);
		अगर (err) अणु
			dev_err(&पूर्णांकf->dev,
				"Cannot get capabilities, error %d\n", err);
			kvaser_usb_हटाओ_पूर्णांकerfaces(dev);
			वापस err;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < dev->nchannels; i++) अणु
		err = kvaser_usb_init_one(dev, id, i);
		अगर (err) अणु
			kvaser_usb_हटाओ_पूर्णांकerfaces(dev);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम kvaser_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा kvaser_usb *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	अगर (!dev)
		वापस;

	kvaser_usb_हटाओ_पूर्णांकerfaces(dev);
पूर्ण

अटल काष्ठा usb_driver kvaser_usb_driver = अणु
	.name = "kvaser_usb",
	.probe = kvaser_usb_probe,
	.disconnect = kvaser_usb_disconnect,
	.id_table = kvaser_usb_table,
पूर्ण;

module_usb_driver(kvaser_usb_driver);

MODULE_AUTHOR("Olivier Sobrie <olivier@sobrie.be>");
MODULE_AUTHOR("Kvaser AB <support@kvaser.com>");
MODULE_DESCRIPTION("CAN driver for Kvaser CAN/USB devices");
MODULE_LICENSE("GPL v2");
