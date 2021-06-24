<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2005 Marc Kleine-Budde, Pengutronix
 * Copyright (C) 2006 Andrey Volkov, Varma Electronics
 * Copyright (C) 2008-2009 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/can.h>
#समावेश <linux/can/can-ml.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/skb.h>
#समावेश <linux/can/led.h>
#समावेश <linux/of.h>

#घोषणा MOD_DESC "CAN device driver interface"

MODULE_DESCRIPTION(MOD_DESC);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Wolfgang Grandegger <wg@grandegger.com>");

अटल व्योम can_update_state_error_stats(काष्ठा net_device *dev,
					 क्रमागत can_state new_state)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);

	अगर (new_state <= priv->state)
		वापस;

	चयन (new_state) अणु
	हाल CAN_STATE_ERROR_WARNING:
		priv->can_stats.error_warning++;
		अवरोध;
	हाल CAN_STATE_ERROR_PASSIVE:
		priv->can_stats.error_passive++;
		अवरोध;
	हाल CAN_STATE_BUS_OFF:
		priv->can_stats.bus_off++;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक can_tx_state_to_frame(काष्ठा net_device *dev, क्रमागत can_state state)
अणु
	चयन (state) अणु
	हाल CAN_STATE_ERROR_ACTIVE:
		वापस CAN_ERR_CRTL_ACTIVE;
	हाल CAN_STATE_ERROR_WARNING:
		वापस CAN_ERR_CRTL_TX_WARNING;
	हाल CAN_STATE_ERROR_PASSIVE:
		वापस CAN_ERR_CRTL_TX_PASSIVE;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक can_rx_state_to_frame(काष्ठा net_device *dev, क्रमागत can_state state)
अणु
	चयन (state) अणु
	हाल CAN_STATE_ERROR_ACTIVE:
		वापस CAN_ERR_CRTL_ACTIVE;
	हाल CAN_STATE_ERROR_WARNING:
		वापस CAN_ERR_CRTL_RX_WARNING;
	हाल CAN_STATE_ERROR_PASSIVE:
		वापस CAN_ERR_CRTL_RX_PASSIVE;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

स्थिर अक्षर *can_get_state_str(स्थिर क्रमागत can_state state)
अणु
	चयन (state) अणु
	हाल CAN_STATE_ERROR_ACTIVE:
		वापस "Error Active";
	हाल CAN_STATE_ERROR_WARNING:
		वापस "Error Warning";
	हाल CAN_STATE_ERROR_PASSIVE:
		वापस "Error Passive";
	हाल CAN_STATE_BUS_OFF:
		वापस "Bus Off";
	हाल CAN_STATE_STOPPED:
		वापस "Stopped";
	हाल CAN_STATE_SLEEPING:
		वापस "Sleeping";
	शेष:
		वापस "<unknown>";
	पूर्ण

	वापस "<unknown>";
पूर्ण
EXPORT_SYMBOL_GPL(can_get_state_str);

व्योम can_change_state(काष्ठा net_device *dev, काष्ठा can_frame *cf,
		      क्रमागत can_state tx_state, क्रमागत can_state rx_state)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);
	क्रमागत can_state new_state = max(tx_state, rx_state);

	अगर (unlikely(new_state == priv->state)) अणु
		netdev_warn(dev, "%s: oops, state did not change", __func__);
		वापस;
	पूर्ण

	netdev_dbg(dev, "Controller changed from %s State (%d) into %s State (%d).\n",
		   can_get_state_str(priv->state), priv->state,
		   can_get_state_str(new_state), new_state);

	can_update_state_error_stats(dev, new_state);
	priv->state = new_state;

	अगर (!cf)
		वापस;

	अगर (unlikely(new_state == CAN_STATE_BUS_OFF)) अणु
		cf->can_id |= CAN_ERR_BUSOFF;
		वापस;
	पूर्ण

	cf->can_id |= CAN_ERR_CRTL;
	cf->data[1] |= tx_state >= rx_state ?
		       can_tx_state_to_frame(dev, tx_state) : 0;
	cf->data[1] |= tx_state <= rx_state ?
		       can_rx_state_to_frame(dev, rx_state) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(can_change_state);

/* CAN device restart क्रम bus-off recovery */
अटल व्योम can_restart(काष्ठा net_device *dev)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *cf;
	पूर्णांक err;

	BUG_ON(netअगर_carrier_ok(dev));

	/* No synchronization needed because the device is bus-off and
	 * no messages can come in or go out.
	 */
	can_flush_echo_skb(dev);

	/* send restart message upstream */
	skb = alloc_can_err_skb(dev, &cf);
	अगर (!skb)
		जाओ restart;

	cf->can_id |= CAN_ERR_RESTARTED;

	stats->rx_packets++;
	stats->rx_bytes += cf->len;

	netअगर_rx_ni(skb);

restart:
	netdev_dbg(dev, "restarted\n");
	priv->can_stats.restarts++;

	/* Now restart the device */
	err = priv->करो_set_mode(dev, CAN_MODE_START);

	netअगर_carrier_on(dev);
	अगर (err)
		netdev_err(dev, "Error %d during restart", err);
पूर्ण

अटल व्योम can_restart_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा can_priv *priv = container_of(dwork, काष्ठा can_priv,
					     restart_work);

	can_restart(priv->dev);
पूर्ण

पूर्णांक can_restart_now(काष्ठा net_device *dev)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);

	/* A manual restart is only permitted अगर स्वतःmatic restart is
	 * disabled and the device is in the bus-off state
	 */
	अगर (priv->restart_ms)
		वापस -EINVAL;
	अगर (priv->state != CAN_STATE_BUS_OFF)
		वापस -EBUSY;

	cancel_delayed_work_sync(&priv->restart_work);
	can_restart(dev);

	वापस 0;
पूर्ण

/* CAN bus-off
 *
 * This functions should be called when the device goes bus-off to
 * tell the netअगर layer that no more packets can be sent or received.
 * If enabled, a समयr is started to trigger bus-off recovery.
 */
व्योम can_bus_off(काष्ठा net_device *dev)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);

	अगर (priv->restart_ms)
		netdev_info(dev, "bus-off, scheduling restart in %d ms\n",
			    priv->restart_ms);
	अन्यथा
		netdev_info(dev, "bus-off\n");

	netअगर_carrier_off(dev);

	अगर (priv->restart_ms)
		schedule_delayed_work(&priv->restart_work,
				      msecs_to_jअगरfies(priv->restart_ms));
पूर्ण
EXPORT_SYMBOL_GPL(can_bus_off);

व्योम can_setup(काष्ठा net_device *dev)
अणु
	dev->type = ARPHRD_CAN;
	dev->mtu = CAN_MTU;
	dev->hard_header_len = 0;
	dev->addr_len = 0;
	dev->tx_queue_len = 10;

	/* New-style flags. */
	dev->flags = IFF_NOARP;
	dev->features = NETIF_F_HW_CSUM;
पूर्ण

/* Allocate and setup space क्रम the CAN network device */
काष्ठा net_device *alloc_candev_mqs(पूर्णांक माप_priv, अचिन्हित पूर्णांक echo_skb_max,
				    अचिन्हित पूर्णांक txqs, अचिन्हित पूर्णांक rxqs)
अणु
	काष्ठा can_ml_priv *can_ml;
	काष्ठा net_device *dev;
	काष्ठा can_priv *priv;
	पूर्णांक size;

	/* We put the driver's priv, the CAN mid layer priv and the
	 * echo skb पूर्णांकo the netdevice's priv. The memory layout क्रम
	 * the netdev_priv is like this:
	 *
	 * +-------------------------+
	 * | driver's priv           |
	 * +-------------------------+
	 * | काष्ठा can_ml_priv      |
	 * +-------------------------+
	 * | array of काष्ठा sk_buff |
	 * +-------------------------+
	 */

	size = ALIGN(माप_priv, NETDEV_ALIGN) + माप(काष्ठा can_ml_priv);

	अगर (echo_skb_max)
		size = ALIGN(size, माप(काष्ठा sk_buff *)) +
			echo_skb_max * माप(काष्ठा sk_buff *);

	dev = alloc_netdev_mqs(size, "can%d", NET_NAME_UNKNOWN, can_setup,
			       txqs, rxqs);
	अगर (!dev)
		वापस शून्य;

	priv = netdev_priv(dev);
	priv->dev = dev;

	can_ml = (व्योम *)priv + ALIGN(माप_priv, NETDEV_ALIGN);
	can_set_ml_priv(dev, can_ml);

	अगर (echo_skb_max) अणु
		priv->echo_skb_max = echo_skb_max;
		priv->echo_skb = (व्योम *)priv +
			(size - echo_skb_max * माप(काष्ठा sk_buff *));
	पूर्ण

	priv->state = CAN_STATE_STOPPED;

	INIT_DELAYED_WORK(&priv->restart_work, can_restart_work);

	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(alloc_candev_mqs);

/* Free space of the CAN network device */
व्योम मुक्त_candev(काष्ठा net_device *dev)
अणु
	मुक्त_netdev(dev);
पूर्ण
EXPORT_SYMBOL_GPL(मुक्त_candev);

/* changing MTU and control mode क्रम CAN/CANFD devices */
पूर्णांक can_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);

	/* Do not allow changing the MTU जबतक running */
	अगर (dev->flags & IFF_UP)
		वापस -EBUSY;

	/* allow change of MTU according to the CANFD ability of the device */
	चयन (new_mtu) अणु
	हाल CAN_MTU:
		/* 'CANFD-only' controllers can not चयन to CAN_MTU */
		अगर (priv->ctrlmode_अटल & CAN_CTRLMODE_FD)
			वापस -EINVAL;

		priv->ctrlmode &= ~CAN_CTRLMODE_FD;
		अवरोध;

	हाल CANFD_MTU:
		/* check क्रम potential CANFD ability */
		अगर (!(priv->ctrlmode_supported & CAN_CTRLMODE_FD) &&
		    !(priv->ctrlmode_अटल & CAN_CTRLMODE_FD))
			वापस -EINVAL;

		priv->ctrlmode |= CAN_CTRLMODE_FD;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	dev->mtu = new_mtu;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(can_change_mtu);

/* Common खोलो function when the device माला_लो खोलोed.
 *
 * This function should be called in the खोलो function of the device
 * driver.
 */
पूर्णांक खोलो_candev(काष्ठा net_device *dev)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);

	अगर (!priv->bittiming.bitrate) अणु
		netdev_err(dev, "bit-timing not yet defined\n");
		वापस -EINVAL;
	पूर्ण

	/* For CAN FD the data bitrate has to be >= the arbitration bitrate */
	अगर ((priv->ctrlmode & CAN_CTRLMODE_FD) &&
	    (!priv->data_bittiming.bitrate ||
	     priv->data_bittiming.bitrate < priv->bittiming.bitrate)) अणु
		netdev_err(dev, "incorrect/missing data bit-timing\n");
		वापस -EINVAL;
	पूर्ण

	/* Switch carrier on अगर device was stopped जबतक in bus-off state */
	अगर (!netअगर_carrier_ok(dev))
		netअगर_carrier_on(dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(खोलो_candev);

#अगर_घोषित CONFIG_OF
/* Common function that can be used to understand the limitation of
 * a transceiver when it provides no means to determine these limitations
 * at runसमय.
 */
व्योम of_can_transceiver(काष्ठा net_device *dev)
अणु
	काष्ठा device_node *dn;
	काष्ठा can_priv *priv = netdev_priv(dev);
	काष्ठा device_node *np = dev->dev.parent->of_node;
	पूर्णांक ret;

	dn = of_get_child_by_name(np, "can-transceiver");
	अगर (!dn)
		वापस;

	ret = of_property_पढ़ो_u32(dn, "max-bitrate", &priv->bitrate_max);
	of_node_put(dn);
	अगर ((ret && ret != -EINVAL) || (!ret && !priv->bitrate_max))
		netdev_warn(dev, "Invalid value for transceiver max bitrate. Ignoring bitrate limit.\n");
पूर्ण
EXPORT_SYMBOL_GPL(of_can_transceiver);
#पूर्ण_अगर

/* Common बंद function क्रम cleanup beक्रमe the device माला_लो बंदd.
 *
 * This function should be called in the बंद function of the device
 * driver.
 */
व्योम बंद_candev(काष्ठा net_device *dev)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);

	cancel_delayed_work_sync(&priv->restart_work);
	can_flush_echo_skb(dev);
पूर्ण
EXPORT_SYMBOL_GPL(बंद_candev);

/* Register the CAN network device */
पूर्णांक रेजिस्टर_candev(काष्ठा net_device *dev)
अणु
	काष्ठा can_priv *priv = netdev_priv(dev);

	/* Ensure termination_स्थिर, termination_स्थिर_cnt and
	 * करो_set_termination consistency. All must be either set or
	 * unset.
	 */
	अगर ((!priv->termination_स्थिर != !priv->termination_स्थिर_cnt) ||
	    (!priv->termination_स्थिर != !priv->करो_set_termination))
		वापस -EINVAL;

	अगर (!priv->bitrate_स्थिर != !priv->bitrate_स्थिर_cnt)
		वापस -EINVAL;

	अगर (!priv->data_bitrate_स्थिर != !priv->data_bitrate_स्थिर_cnt)
		वापस -EINVAL;

	dev->rtnl_link_ops = &can_link_ops;
	netअगर_carrier_off(dev);

	वापस रेजिस्टर_netdev(dev);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_candev);

/* Unरेजिस्टर the CAN network device */
व्योम unरेजिस्टर_candev(काष्ठा net_device *dev)
अणु
	unरेजिस्टर_netdev(dev);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_candev);

/* Test अगर a network device is a candev based device
 * and वापस the can_priv* अगर so.
 */
काष्ठा can_priv *safe_candev_priv(काष्ठा net_device *dev)
अणु
	अगर (dev->type != ARPHRD_CAN || dev->rtnl_link_ops != &can_link_ops)
		वापस शून्य;

	वापस netdev_priv(dev);
पूर्ण
EXPORT_SYMBOL_GPL(safe_candev_priv);

अटल __init पूर्णांक can_dev_init(व्योम)
अणु
	पूर्णांक err;

	can_led_notअगरier_init();

	err = can_netlink_रेजिस्टर();
	अगर (!err)
		pr_info(MOD_DESC "\n");

	वापस err;
पूर्ण
module_init(can_dev_init);

अटल __निकास व्योम can_dev_निकास(व्योम)
अणु
	can_netlink_unरेजिस्टर();

	can_led_notअगरier_निकास();
पूर्ण
module_निकास(can_dev_निकास);

MODULE_ALIAS_RTNL_LINK("can");
