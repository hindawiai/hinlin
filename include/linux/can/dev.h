<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/can/dev.h
 *
 * Definitions क्रम the CAN network device driver पूर्णांकerface
 *
 * Copyright (C) 2006 Andrey Volkov <avolkov@varma-el.com>
 *               Varma Electronics Oy
 *
 * Copyright (C) 2008 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 *
 */

#अगर_अघोषित _CAN_DEV_H
#घोषणा _CAN_DEV_H

#समावेश <linux/can.h>
#समावेश <linux/can/bittiming.h>
#समावेश <linux/can/error.h>
#समावेश <linux/can/led.h>
#समावेश <linux/can/length.h>
#समावेश <linux/can/netlink.h>
#समावेश <linux/can/skb.h>
#समावेश <linux/netdevice.h>

/*
 * CAN mode
 */
क्रमागत can_mode अणु
	CAN_MODE_STOP = 0,
	CAN_MODE_START,
	CAN_MODE_SLEEP
पूर्ण;

/*
 * CAN common निजी data
 */
काष्ठा can_priv अणु
	काष्ठा net_device *dev;
	काष्ठा can_device_stats can_stats;

	स्थिर काष्ठा can_bittiming_स्थिर *bittiming_स्थिर,
		*data_bittiming_स्थिर;
	काष्ठा can_bittiming bittiming, data_bittiming;
	स्थिर काष्ठा can_tdc_स्थिर *tdc_स्थिर;
	काष्ठा can_tdc tdc;

	अचिन्हित पूर्णांक bitrate_स्थिर_cnt;
	स्थिर u32 *bitrate_स्थिर;
	स्थिर u32 *data_bitrate_स्थिर;
	अचिन्हित पूर्णांक data_bitrate_स्थिर_cnt;
	u32 bitrate_max;
	काष्ठा can_घड़ी घड़ी;

	अचिन्हित पूर्णांक termination_स्थिर_cnt;
	स्थिर u16 *termination_स्थिर;
	u16 termination;

	क्रमागत can_state state;

	/* CAN controller features - see include/uapi/linux/can/netlink.h */
	u32 ctrlmode;		/* current options setting */
	u32 ctrlmode_supported;	/* options that can be modअगरied by netlink */
	u32 ctrlmode_अटल;	/* अटल enabled options क्रम driver/hardware */

	पूर्णांक restart_ms;
	काष्ठा delayed_work restart_work;

	पूर्णांक (*करो_set_bittiming)(काष्ठा net_device *dev);
	पूर्णांक (*करो_set_data_bittiming)(काष्ठा net_device *dev);
	पूर्णांक (*करो_set_mode)(काष्ठा net_device *dev, क्रमागत can_mode mode);
	पूर्णांक (*करो_set_termination)(काष्ठा net_device *dev, u16 term);
	पूर्णांक (*करो_get_state)(स्थिर काष्ठा net_device *dev,
			    क्रमागत can_state *state);
	पूर्णांक (*करो_get_berr_counter)(स्थिर काष्ठा net_device *dev,
				   काष्ठा can_berr_counter *bec);

	अचिन्हित पूर्णांक echo_skb_max;
	काष्ठा sk_buff **echo_skb;

#अगर_घोषित CONFIG_CAN_LEDS
	काष्ठा led_trigger *tx_led_trig;
	अक्षर tx_led_trig_name[CAN_LED_NAME_SZ];
	काष्ठा led_trigger *rx_led_trig;
	अक्षर rx_led_trig_name[CAN_LED_NAME_SZ];
	काष्ठा led_trigger *rxtx_led_trig;
	अक्षर rxtx_led_trig_name[CAN_LED_NAME_SZ];
#पूर्ण_अगर
पूर्ण;


/* helper to define अटल CAN controller features at device creation समय */
अटल अंतरभूत व्योम can_set_अटल_ctrlmode(काष्ठा net_device *dev,
					   u32 अटल_mode)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);

	/* alloc_candev() succeeded => netdev_priv() is valid at this poपूर्णांक */
	priv->ctrlmode = अटल_mode;
	priv->ctrlmode_अटल = अटल_mode;

	/* override MTU which was set by शेष in can_setup()? */
	अगर (अटल_mode & CAN_CTRLMODE_FD)
		dev->mtu = CANFD_MTU;
पूर्ण

व्योम can_setup(काष्ठा net_device *dev);

काष्ठा net_device *alloc_candev_mqs(पूर्णांक माप_priv, अचिन्हित पूर्णांक echo_skb_max,
				    अचिन्हित पूर्णांक txqs, अचिन्हित पूर्णांक rxqs);
#घोषणा alloc_candev(माप_priv, echo_skb_max) \
	alloc_candev_mqs(माप_priv, echo_skb_max, 1, 1)
#घोषणा alloc_candev_mq(माप_priv, echo_skb_max, count) \
	alloc_candev_mqs(माप_priv, echo_skb_max, count, count)
व्योम मुक्त_candev(काष्ठा net_device *dev);

/* a candev safe wrapper around netdev_priv */
काष्ठा can_priv *safe_candev_priv(काष्ठा net_device *dev);

पूर्णांक खोलो_candev(काष्ठा net_device *dev);
व्योम बंद_candev(काष्ठा net_device *dev);
पूर्णांक can_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu);

पूर्णांक रेजिस्टर_candev(काष्ठा net_device *dev);
व्योम unरेजिस्टर_candev(काष्ठा net_device *dev);

पूर्णांक can_restart_now(काष्ठा net_device *dev);
व्योम can_bus_off(काष्ठा net_device *dev);

स्थिर अक्षर *can_get_state_str(स्थिर क्रमागत can_state state);
व्योम can_change_state(काष्ठा net_device *dev, काष्ठा can_frame *cf,
		      क्रमागत can_state tx_state, क्रमागत can_state rx_state);

#अगर_घोषित CONFIG_OF
व्योम of_can_transceiver(काष्ठा net_device *dev);
#अन्यथा
अटल अंतरभूत व्योम of_can_transceiver(काष्ठा net_device *dev) अणु पूर्ण
#पूर्ण_अगर

बाह्य काष्ठा rtnl_link_ops can_link_ops;
पूर्णांक can_netlink_रेजिस्टर(व्योम);
व्योम can_netlink_unरेजिस्टर(व्योम);

#पूर्ण_अगर /* !_CAN_DEV_H */
