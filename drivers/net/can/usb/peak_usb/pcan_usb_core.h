<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * CAN driver क्रम PEAK System USB adapters
 * Derived from the PCAN project file driver/src/pcan_usb_core.c
 *
 * Copyright (C) 2003-2010 PEAK System-Technik GmbH
 * Copyright (C) 2010-2012 Stephane Grosjean <s.grosjean@peak-प्रणाली.com>
 *
 * Many thanks to Klaus Hitschler <klaus.hitschler@gmx.de>
 */
#अगर_अघोषित PCAN_USB_CORE_H
#घोषणा PCAN_USB_CORE_H

/* PEAK-System venकरोr id. */
#घोषणा PCAN_USB_VENDOR_ID		0x0c72

/* supported device ids. */
#घोषणा PCAN_USB_PRODUCT_ID		0x000c
#घोषणा PCAN_USBPRO_PRODUCT_ID		0x000d
#घोषणा PCAN_USBPROFD_PRODUCT_ID	0x0011
#घोषणा PCAN_USBFD_PRODUCT_ID		0x0012
#घोषणा PCAN_USBCHIP_PRODUCT_ID		0x0013
#घोषणा PCAN_USBX6_PRODUCT_ID		0x0014

#घोषणा PCAN_USB_DRIVER_NAME		"peak_usb"

/* number of urbs that are submitted क्रम rx/tx per channel */
#घोषणा PCAN_USB_MAX_RX_URBS		4
#घोषणा PCAN_USB_MAX_TX_URBS		10

/* usb adapters maximum channels per usb पूर्णांकerface */
#घोषणा PCAN_USB_MAX_CHANNEL		2

/* maximum length of the usb commands sent to/received from the devices */
#घोषणा PCAN_USB_MAX_CMD_LEN		32

काष्ठा peak_usb_device;

/* PEAK-System USB adapter descriptor */
काष्ठा peak_usb_adapter अणु
	अक्षर *name;
	u32 device_id;
	u32 ctrlmode_supported;
	काष्ठा can_घड़ी घड़ी;
	स्थिर काष्ठा can_bittiming_स्थिर * स्थिर bittiming_स्थिर;
	स्थिर काष्ठा can_bittiming_स्थिर * स्थिर data_bittiming_स्थिर;
	अचिन्हित पूर्णांक ctrl_count;

	स्थिर काष्ठा ethtool_ops *ethtool_ops;

	पूर्णांक (*पूर्णांकf_probe)(काष्ठा usb_पूर्णांकerface *पूर्णांकf);

	पूर्णांक (*dev_init)(काष्ठा peak_usb_device *dev);
	व्योम (*dev_निकास)(काष्ठा peak_usb_device *dev);
	व्योम (*dev_मुक्त)(काष्ठा peak_usb_device *dev);
	पूर्णांक (*dev_खोलो)(काष्ठा peak_usb_device *dev);
	पूर्णांक (*dev_बंद)(काष्ठा peak_usb_device *dev);
	पूर्णांक (*dev_set_bittiming)(काष्ठा peak_usb_device *dev,
					काष्ठा can_bittiming *bt);
	पूर्णांक (*dev_set_data_bittiming)(काष्ठा peak_usb_device *dev,
				      काष्ठा can_bittiming *bt);
	पूर्णांक (*dev_set_bus)(काष्ठा peak_usb_device *dev, u8 onoff);
	पूर्णांक (*dev_get_device_id)(काष्ठा peak_usb_device *dev, u32 *device_id);
	पूर्णांक (*dev_decode_buf)(काष्ठा peak_usb_device *dev, काष्ठा urb *urb);
	पूर्णांक (*dev_encode_msg)(काष्ठा peak_usb_device *dev, काष्ठा sk_buff *skb,
					u8 *obuf, माप_प्रकार *size);
	पूर्णांक (*dev_start)(काष्ठा peak_usb_device *dev);
	पूर्णांक (*dev_stop)(काष्ठा peak_usb_device *dev);
	पूर्णांक (*dev_restart_async)(काष्ठा peak_usb_device *dev, काष्ठा urb *urb,
					u8 *buf);
	पूर्णांक (*करो_get_berr_counter)(स्थिर काष्ठा net_device *netdev,
				   काष्ठा can_berr_counter *bec);
	u8 ep_msg_in;
	u8 ep_msg_out[PCAN_USB_MAX_CHANNEL];
	u8 ts_used_bits;
	u8 us_per_ts_shअगरt;
	u32 us_per_ts_scale;

	पूर्णांक rx_buffer_size;
	पूर्णांक tx_buffer_size;
	पूर्णांक माप_dev_निजी;
पूर्ण;

बाह्य स्थिर काष्ठा peak_usb_adapter pcan_usb;
बाह्य स्थिर काष्ठा peak_usb_adapter pcan_usb_pro;
बाह्य स्थिर काष्ठा peak_usb_adapter pcan_usb_fd;
बाह्य स्थिर काष्ठा peak_usb_adapter pcan_usb_chip;
बाह्य स्थिर काष्ठा peak_usb_adapter pcan_usb_pro_fd;
बाह्य स्थिर काष्ठा peak_usb_adapter pcan_usb_x6;

काष्ठा peak_समय_ref अणु
	kसमय_प्रकार tv_host_0, tv_host;
	u32 ts_dev_1, ts_dev_2;
	u64 ts_total;
	u32 tick_count;
	स्थिर काष्ठा peak_usb_adapter *adapter;
पूर्ण;

काष्ठा peak_tx_urb_context अणु
	काष्ठा peak_usb_device *dev;
	u32 echo_index;
	u8 data_len;
	काष्ठा urb *urb;
पूर्ण;

#घोषणा PCAN_USB_STATE_CONNECTED	0x00000001
#घोषणा PCAN_USB_STATE_STARTED		0x00000002

/* PEAK-System USB device */
काष्ठा peak_usb_device अणु
	काष्ठा can_priv can;
	स्थिर काष्ठा peak_usb_adapter *adapter;
	अचिन्हित पूर्णांक ctrl_idx;
	u32 state;

	काष्ठा usb_device *udev;
	काष्ठा net_device *netdev;

	atomic_t active_tx_urbs;
	काष्ठा usb_anchor tx_submitted;
	काष्ठा peak_tx_urb_context tx_contexts[PCAN_USB_MAX_TX_URBS];

	u8 *cmd_buf;
	काष्ठा usb_anchor rx_submitted;

	u32 device_number;
	u8 device_rev;

	u8 ep_msg_in;
	u8 ep_msg_out;

	काष्ठा peak_usb_device *prev_siblings;
	काष्ठा peak_usb_device *next_siblings;
पूर्ण;

व्योम pcan_dump_mem(अक्षर *prompt, व्योम *p, पूर्णांक l);

/* common बारtamp management */
व्योम peak_usb_init_समय_ref(काष्ठा peak_समय_ref *समय_ref,
			    स्थिर काष्ठा peak_usb_adapter *adapter);
व्योम peak_usb_update_ts_now(काष्ठा peak_समय_ref *समय_ref, u32 ts_now);
व्योम peak_usb_set_ts_now(काष्ठा peak_समय_ref *समय_ref, u32 ts_now);
व्योम peak_usb_get_ts_समय(काष्ठा peak_समय_ref *समय_ref, u32 ts, kसमय_प्रकार *tv);
पूर्णांक peak_usb_netअगर_rx(काष्ठा sk_buff *skb,
		      काष्ठा peak_समय_ref *समय_ref, u32 ts_low);
व्योम peak_usb_async_complete(काष्ठा urb *urb);
व्योम peak_usb_restart_complete(काष्ठा peak_usb_device *dev);

#पूर्ण_अगर
