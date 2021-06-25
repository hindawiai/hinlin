<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2012, Fabio Baltieri <fabio.baltieri@gmail.com>
 */

#अगर_अघोषित _CAN_LED_H
#घोषणा _CAN_LED_H

#समावेश <linux/अगर.h>
#समावेश <linux/leds.h>
#समावेश <linux/netdevice.h>

क्रमागत can_led_event अणु
	CAN_LED_EVENT_OPEN,
	CAN_LED_EVENT_STOP,
	CAN_LED_EVENT_TX,
	CAN_LED_EVENT_RX,
पूर्ण;

#अगर_घोषित CONFIG_CAN_LEDS

/* keep space क्रम पूर्णांकerface name + "-tx"/"-rx"/"-rxtx"
 * suffix and null terminator
 */
#घोषणा CAN_LED_NAME_SZ (IFNAMSIZ + 6)

व्योम can_led_event(काष्ठा net_device *netdev, क्रमागत can_led_event event);
व्योम devm_can_led_init(काष्ठा net_device *netdev);
पूर्णांक __init can_led_notअगरier_init(व्योम);
व्योम __निकास can_led_notअगरier_निकास(व्योम);

#अन्यथा

अटल अंतरभूत व्योम can_led_event(काष्ठा net_device *netdev,
				 क्रमागत can_led_event event)
अणु
पूर्ण
अटल अंतरभूत व्योम devm_can_led_init(काष्ठा net_device *netdev)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक can_led_notअगरier_init(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम can_led_notअगरier_निकास(व्योम)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* !_CAN_LED_H */
