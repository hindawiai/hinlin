<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2012, Fabio Baltieri <fabio.baltieri@gmail.com>
 * Copyright 2012, Kurt Van Dijck <kurt.van.dijck@eia.be>
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/can/dev.h>

#समावेश <linux/can/led.h>

अटल अचिन्हित दीर्घ led_delay = 50;
module_param(led_delay, uदीर्घ, 0644);
MODULE_PARM_DESC(led_delay,
		"blink delay time for activity leds (msecs, default: 50).");

/* Trigger a LED event in response to a CAN device event */
व्योम can_led_event(काष्ठा net_device *netdev, क्रमागत can_led_event event)
अणु
	काष्ठा can_priv *priv = netdev_priv(netdev);

	चयन (event) अणु
	हाल CAN_LED_EVENT_OPEN:
		led_trigger_event(priv->tx_led_trig, LED_FULL);
		led_trigger_event(priv->rx_led_trig, LED_FULL);
		led_trigger_event(priv->rxtx_led_trig, LED_FULL);
		अवरोध;
	हाल CAN_LED_EVENT_STOP:
		led_trigger_event(priv->tx_led_trig, LED_OFF);
		led_trigger_event(priv->rx_led_trig, LED_OFF);
		led_trigger_event(priv->rxtx_led_trig, LED_OFF);
		अवरोध;
	हाल CAN_LED_EVENT_TX:
		अगर (led_delay) अणु
			led_trigger_blink_oneshot(priv->tx_led_trig,
						  &led_delay, &led_delay, 1);
			led_trigger_blink_oneshot(priv->rxtx_led_trig,
						  &led_delay, &led_delay, 1);
		पूर्ण
		अवरोध;
	हाल CAN_LED_EVENT_RX:
		अगर (led_delay) अणु
			led_trigger_blink_oneshot(priv->rx_led_trig,
						  &led_delay, &led_delay, 1);
			led_trigger_blink_oneshot(priv->rxtx_led_trig,
						  &led_delay, &led_delay, 1);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(can_led_event);

अटल व्योम can_led_release(काष्ठा device *gendev, व्योम *res)
अणु
	काष्ठा can_priv *priv = netdev_priv(to_net_dev(gendev));

	led_trigger_unरेजिस्टर_simple(priv->tx_led_trig);
	led_trigger_unरेजिस्टर_simple(priv->rx_led_trig);
	led_trigger_unरेजिस्टर_simple(priv->rxtx_led_trig);
पूर्ण

/* Register CAN LED triggers क्रम a CAN device
 *
 * This is normally called from a driver's probe function
 */
व्योम devm_can_led_init(काष्ठा net_device *netdev)
अणु
	काष्ठा can_priv *priv = netdev_priv(netdev);
	व्योम *res;

	res = devres_alloc(can_led_release, 0, GFP_KERNEL);
	अगर (!res) अणु
		netdev_err(netdev, "cannot register LED triggers\n");
		वापस;
	पूर्ण

	snम_लिखो(priv->tx_led_trig_name, माप(priv->tx_led_trig_name),
		 "%s-tx", netdev->name);
	snम_लिखो(priv->rx_led_trig_name, माप(priv->rx_led_trig_name),
		 "%s-rx", netdev->name);
	snम_लिखो(priv->rxtx_led_trig_name, माप(priv->rxtx_led_trig_name),
		 "%s-rxtx", netdev->name);

	led_trigger_रेजिस्टर_simple(priv->tx_led_trig_name,
				    &priv->tx_led_trig);
	led_trigger_रेजिस्टर_simple(priv->rx_led_trig_name,
				    &priv->rx_led_trig);
	led_trigger_रेजिस्टर_simple(priv->rxtx_led_trig_name,
				    &priv->rxtx_led_trig);

	devres_add(&netdev->dev, res);
पूर्ण
EXPORT_SYMBOL_GPL(devm_can_led_init);

/* NETDEV नाम notअगरier to नाम the associated led triggers too */
अटल पूर्णांक can_led_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ msg,
			    व्योम *ptr)
अणु
	काष्ठा net_device *netdev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा can_priv *priv = safe_candev_priv(netdev);
	अक्षर name[CAN_LED_NAME_SZ];

	अगर (!priv)
		वापस NOTIFY_DONE;

	अगर (!priv->tx_led_trig || !priv->rx_led_trig || !priv->rxtx_led_trig)
		वापस NOTIFY_DONE;

	अगर (msg == NETDEV_CHANGENAME) अणु
		snम_लिखो(name, माप(name), "%s-tx", netdev->name);
		led_trigger_नाम_अटल(name, priv->tx_led_trig);

		snम_लिखो(name, माप(name), "%s-rx", netdev->name);
		led_trigger_नाम_अटल(name, priv->rx_led_trig);

		snम_लिखो(name, माप(name), "%s-rxtx", netdev->name);
		led_trigger_नाम_अटल(name, priv->rxtx_led_trig);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

/* notअगरier block क्रम netdevice event */
अटल काष्ठा notअगरier_block can_netdev_notअगरier __पढ़ो_mostly = अणु
	.notअगरier_call = can_led_notअगरier,
पूर्ण;

पूर्णांक __init can_led_notअगरier_init(व्योम)
अणु
	वापस रेजिस्टर_netdevice_notअगरier(&can_netdev_notअगरier);
पूर्ण

व्योम __निकास can_led_notअगरier_निकास(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&can_netdev_notअगरier);
पूर्ण
