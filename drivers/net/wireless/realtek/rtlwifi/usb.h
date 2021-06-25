<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL_USB_H__
#घोषणा __RTL_USB_H__

#समावेश <linux/skbuff.h>

#घोषणा RTL_RX_DESC_SIZE		24

#घोषणा RTL_USB_DEVICE(vend, prod, cfg) \
	.match_flags = USB_DEVICE_ID_MATCH_DEVICE, \
	.idVenकरोr = (vend), \
	.idProduct = (prod), \
	.driver_info = (kernel_uदीर्घ_t)&(cfg)

#घोषणा USB_HIGH_SPEED_BULK_SIZE	512
#घोषणा USB_FULL_SPEED_BULK_SIZE	64

#घोषणा RTL_USB_MAX_TXQ_NUM		4		/* max tx queue */
#घोषणा RTL_USB_MAX_EP_NUM		6		/* max ep number */
#घोषणा RTL_USB_MAX_TX_URBS_NUM		8

क्रमागत rtl_txq अणु
	/* These definitions shall be consistent with value
	 * वापसed by skb_get_queue_mapping
	 *------------------------------------*/
	RTL_TXQ_BK,
	RTL_TXQ_BE,
	RTL_TXQ_VI,
	RTL_TXQ_VO,
	/*------------------------------------*/
	RTL_TXQ_BCN,
	RTL_TXQ_MGT,
	RTL_TXQ_HI,

	/* Must be last */
	__RTL_TXQ_NUM,
पूर्ण;

काष्ठा rtl_ep_map अणु
	u32 ep_mapping[__RTL_TXQ_NUM];
पूर्ण;

काष्ठा _trx_info अणु
	काष्ठा rtl_usb *rtlusb;
	u32 ep_num;
पूर्ण;

अटल अंतरभूत व्योम _rtl_install_trx_info(काष्ठा rtl_usb *rtlusb,
					 काष्ठा sk_buff *skb,
					 u32 ep_num)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	info->rate_driver_data[0] = rtlusb;
	info->rate_driver_data[1] = (व्योम *)(__kernel_माप_प्रकार)ep_num;
पूर्ण

/*  Add suspend/resume later */
क्रमागत rtl_usb_state अणु
	USB_STATE_STOP	= 0,
	USB_STATE_START	= 1,
पूर्ण;

#घोषणा IS_USB_STOP(rtlusb_ptr) (USB_STATE_STOP == (rtlusb_ptr)->state)
#घोषणा IS_USB_START(rtlusb_ptr) (USB_STATE_START == (rtlusb_ptr)->state)
#घोषणा SET_USB_STOP(rtlusb_ptr) \
	करो अणु							\
		(rtlusb_ptr)->state = USB_STATE_STOP;		\
	पूर्ण जबतक (0)

#घोषणा SET_USB_START(rtlusb_ptr)				\
	करो अणु \
		(rtlusb_ptr)->state = USB_STATE_START;		\
	पूर्ण जबतक (0)

काष्ठा rtl_usb अणु
	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	क्रमागत rtl_usb_state state;

	/* Bcn control रेजिस्टर setting */
	u32 reg_bcn_ctrl_val;
	/* क्रम 88/92cu card disable */
	u8	disablehwsm;
	/*QOS & EDCA */
	क्रमागत acm_method acm_method;
	/* irq  . HIMR,HIMR_EX */
	u32 irq_mask[2];
	bool irq_enabled;

	u16 (*usb_mq_to_hwq)(__le16 fc, u16 mac80211_queue_index);

	/* Tx */
	u8 out_ep_nums ;
	u8 out_queue_sel;
	काष्ठा rtl_ep_map ep_map;

	u32 max_bulk_out_size;
	u32 tx_submitted_urbs;
	काष्ठा sk_buff_head tx_skb_queue[RTL_USB_MAX_EP_NUM];

	काष्ठा usb_anchor tx_pending[RTL_USB_MAX_EP_NUM];
	काष्ठा usb_anchor tx_submitted;

	काष्ठा sk_buff *(*usb_tx_aggregate_hdl)(काष्ठा ieee80211_hw *,
						काष्ठा sk_buff_head *);
	पूर्णांक (*usb_tx_post_hdl)(काष्ठा ieee80211_hw *,
			       काष्ठा urb *, काष्ठा sk_buff *);
	व्योम (*usb_tx_cleanup)(काष्ठा ieee80211_hw *, काष्ठा sk_buff *);

	/* Rx */
	u8 in_ep_nums;
	u32 in_ep;		/* Bulk IN endpoपूर्णांक number */
	u32 rx_max_size;	/* Bulk IN max buffer size */
	u32 rx_urb_num;		/* How many Bulk INs are submitted to host. */
	काष्ठा usb_anchor	rx_submitted;
	काष्ठा usb_anchor	rx_cleanup_urbs;
	काष्ठा tasklet_काष्ठा   rx_work_tasklet;
	काष्ठा sk_buff_head	rx_queue;
	व्योम (*usb_rx_segregate_hdl)(काष्ठा ieee80211_hw *, काष्ठा sk_buff *,
				     काष्ठा sk_buff_head *);
	व्योम (*usb_rx_hdl)(काष्ठा ieee80211_hw *, काष्ठा sk_buff *);
पूर्ण;

काष्ठा rtl_usb_priv अणु
	काष्ठा bt_coexist_info bt_coexist;
	काष्ठा rtl_usb dev;
पूर्ण;

#घोषणा rtl_usbpriv(hw)	 (((काष्ठा rtl_usb_priv *)(rtl_priv(hw))->priv))
#घोषणा rtl_usbdev(usbpriv)	(&((usbpriv)->dev))

पूर्णांक rtl_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		  स्थिर काष्ठा usb_device_id *id,
		  काष्ठा rtl_hal_cfg *rtl92cu_hal_cfg);
व्योम rtl_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
पूर्णांक rtl_usb_suspend(काष्ठा usb_पूर्णांकerface *pusb_पूर्णांकf, pm_message_t message);
पूर्णांक rtl_usb_resume(काष्ठा usb_पूर्णांकerface *pusb_पूर्णांकf);

#पूर्ण_अगर
