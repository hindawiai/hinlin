<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित KVASER_USB_H
#घोषणा KVASER_USB_H

/* Kvaser USB CAN करोngles are भागided पूर्णांकo three major platक्रमms:
 * - Hydra: Running firmware labeled as 'mhydra'
 * - Leaf: Based on Renesas M32C or Freescale i.MX28, running firmware labeled
 *         as 'filo'
 * - UsbcanII: Based on Renesas M16C, running firmware labeled as 'helios'
 */

#समावेश <linux/completion.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/usb.h>

#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>

#घोषणा KVASER_USB_MAX_RX_URBS			4
#घोषणा KVASER_USB_MAX_TX_URBS			128
#घोषणा KVASER_USB_TIMEOUT			1000 /* msecs */
#घोषणा KVASER_USB_RX_BUFFER_SIZE		3072
#घोषणा KVASER_USB_MAX_NET_DEVICES		5

/* USB devices features */
#घोषणा KVASER_USB_HAS_SILENT_MODE		BIT(0)
#घोषणा KVASER_USB_HAS_TXRX_ERRORS		BIT(1)

/* Device capabilities */
#घोषणा KVASER_USB_CAP_BERR_CAP			0x01
#घोषणा KVASER_USB_CAP_EXT_CAP			0x02
#घोषणा KVASER_USB_HYDRA_CAP_EXT_CMD		0x04

काष्ठा kvaser_usb_dev_cfg;

क्रमागत kvaser_usb_leaf_family अणु
	KVASER_LEAF,
	KVASER_USBCAN,
पूर्ण;

#घोषणा KVASER_USB_HYDRA_MAX_CMD_LEN		128
काष्ठा kvaser_usb_dev_card_data_hydra अणु
	u8 channel_to_he[KVASER_USB_MAX_NET_DEVICES];
	u8 sysdbg_he;
	spinlock_t transid_lock; /* lock क्रम transid */
	u16 transid;
	/* lock क्रम usb_rx_leftover and usb_rx_leftover_len */
	spinlock_t usb_rx_leftover_lock;
	u8 usb_rx_leftover[KVASER_USB_HYDRA_MAX_CMD_LEN];
	u8 usb_rx_leftover_len;
पूर्ण;
काष्ठा kvaser_usb_dev_card_data अणु
	u32 ctrlmode_supported;
	u32 capabilities;
	जोड़ अणु
		काष्ठा अणु
			क्रमागत kvaser_usb_leaf_family family;
		पूर्ण leaf;
		काष्ठा kvaser_usb_dev_card_data_hydra hydra;
	पूर्ण;
पूर्ण;

/* Context क्रम an outstanding, not yet ACKed, transmission */
काष्ठा kvaser_usb_tx_urb_context अणु
	काष्ठा kvaser_usb_net_priv *priv;
	u32 echo_index;
	पूर्णांक dlc;
पूर्ण;

काष्ठा kvaser_usb अणु
	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा kvaser_usb_net_priv *nets[KVASER_USB_MAX_NET_DEVICES];
	स्थिर काष्ठा kvaser_usb_dev_ops *ops;
	स्थिर काष्ठा kvaser_usb_dev_cfg *cfg;

	काष्ठा usb_endpoपूर्णांक_descriptor *bulk_in, *bulk_out;
	काष्ठा usb_anchor rx_submitted;

	/* @max_tx_urbs: Firmware-reported maximum number of outstanding,
	 * not yet ACKed, transmissions on this device. This value is
	 * also used as a sentinel क्रम marking मुक्त tx contexts.
	 */
	u32 fw_version;
	अचिन्हित पूर्णांक nchannels;
	अचिन्हित पूर्णांक max_tx_urbs;
	काष्ठा kvaser_usb_dev_card_data card_data;

	bool rxinitकरोne;
	व्योम *rxbuf[KVASER_USB_MAX_RX_URBS];
	dma_addr_t rxbuf_dma[KVASER_USB_MAX_RX_URBS];
पूर्ण;

काष्ठा kvaser_usb_net_priv अणु
	काष्ठा can_priv can;
	काष्ठा can_berr_counter bec;

	काष्ठा kvaser_usb *dev;
	काष्ठा net_device *netdev;
	पूर्णांक channel;

	काष्ठा completion start_comp, stop_comp, flush_comp;
	काष्ठा usb_anchor tx_submitted;

	spinlock_t tx_contexts_lock; /* lock क्रम active_tx_contexts */
	पूर्णांक active_tx_contexts;
	काष्ठा kvaser_usb_tx_urb_context tx_contexts[];
पूर्ण;

/**
 * काष्ठा kvaser_usb_dev_ops - Device specअगरic functions
 * @dev_set_mode:		used क्रम can.करो_set_mode
 * @dev_set_bittiming:		used क्रम can.करो_set_bittiming
 * @dev_set_data_bittiming:	used क्रम can.करो_set_data_bittiming
 * @dev_get_berr_counter:	used क्रम can.करो_get_berr_counter
 *
 * @dev_setup_endpoपूर्णांकs:	setup USB in and out endpoपूर्णांकs
 * @dev_init_card:		initialize card
 * @dev_get_software_info:	get software info
 * @dev_get_software_details:	get software details
 * @dev_get_card_info:		get card info
 * @dev_get_capabilities:	discover device capabilities
 *
 * @dev_set_opt_mode:		set ctrlmod
 * @dev_start_chip:		start the CAN controller
 * @dev_stop_chip:		stop the CAN controller
 * @dev_reset_chip:		reset the CAN controller
 * @dev_flush_queue:		flush outstanding CAN messages
 * @dev_पढ़ो_bulk_callback:	handle incoming commands
 * @dev_frame_to_cmd:		translate काष्ठा can_frame पूर्णांकo device command
 */
काष्ठा kvaser_usb_dev_ops अणु
	पूर्णांक (*dev_set_mode)(काष्ठा net_device *netdev, क्रमागत can_mode mode);
	पूर्णांक (*dev_set_bittiming)(काष्ठा net_device *netdev);
	पूर्णांक (*dev_set_data_bittiming)(काष्ठा net_device *netdev);
	पूर्णांक (*dev_get_berr_counter)(स्थिर काष्ठा net_device *netdev,
				    काष्ठा can_berr_counter *bec);
	पूर्णांक (*dev_setup_endpoपूर्णांकs)(काष्ठा kvaser_usb *dev);
	पूर्णांक (*dev_init_card)(काष्ठा kvaser_usb *dev);
	पूर्णांक (*dev_get_software_info)(काष्ठा kvaser_usb *dev);
	पूर्णांक (*dev_get_software_details)(काष्ठा kvaser_usb *dev);
	पूर्णांक (*dev_get_card_info)(काष्ठा kvaser_usb *dev);
	पूर्णांक (*dev_get_capabilities)(काष्ठा kvaser_usb *dev);
	पूर्णांक (*dev_set_opt_mode)(स्थिर काष्ठा kvaser_usb_net_priv *priv);
	पूर्णांक (*dev_start_chip)(काष्ठा kvaser_usb_net_priv *priv);
	पूर्णांक (*dev_stop_chip)(काष्ठा kvaser_usb_net_priv *priv);
	पूर्णांक (*dev_reset_chip)(काष्ठा kvaser_usb *dev, पूर्णांक channel);
	पूर्णांक (*dev_flush_queue)(काष्ठा kvaser_usb_net_priv *priv);
	व्योम (*dev_पढ़ो_bulk_callback)(काष्ठा kvaser_usb *dev, व्योम *buf,
				       पूर्णांक len);
	व्योम *(*dev_frame_to_cmd)(स्थिर काष्ठा kvaser_usb_net_priv *priv,
				  स्थिर काष्ठा sk_buff *skb, पूर्णांक *frame_len,
				  पूर्णांक *cmd_len, u16 transid);
पूर्ण;

काष्ठा kvaser_usb_dev_cfg अणु
	स्थिर काष्ठा can_घड़ी घड़ी;
	स्थिर अचिन्हित पूर्णांक बारtamp_freq;
	स्थिर काष्ठा can_bittiming_स्थिर * स्थिर bittiming_स्थिर;
	स्थिर काष्ठा can_bittiming_स्थिर * स्थिर data_bittiming_स्थिर;
पूर्ण;

बाह्य स्थिर काष्ठा kvaser_usb_dev_ops kvaser_usb_hydra_dev_ops;
बाह्य स्थिर काष्ठा kvaser_usb_dev_ops kvaser_usb_leaf_dev_ops;

पूर्णांक kvaser_usb_recv_cmd(स्थिर काष्ठा kvaser_usb *dev, व्योम *cmd, पूर्णांक len,
			पूर्णांक *actual_len);

पूर्णांक kvaser_usb_send_cmd(स्थिर काष्ठा kvaser_usb *dev, व्योम *cmd, पूर्णांक len);

पूर्णांक kvaser_usb_send_cmd_async(काष्ठा kvaser_usb_net_priv *priv, व्योम *cmd,
			      पूर्णांक len);

पूर्णांक kvaser_usb_can_rx_over_error(काष्ठा net_device *netdev);
#पूर्ण_अगर /* KVASER_USB_H */
