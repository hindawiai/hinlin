<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Copyright (C) 2016 National Instruments Corp.
 */
#अगर_अघोषित __PHY_LED_TRIGGERS
#घोषणा __PHY_LED_TRIGGERS

काष्ठा phy_device;

#अगर_घोषित CONFIG_LED_TRIGGER_PHY

#समावेश <linux/leds.h>
#समावेश <linux/phy.h>

#घोषणा PHY_LED_TRIGGER_SPEED_SUFFIX_SIZE	11

#घोषणा PHY_LINK_LED_TRIGGER_NAME_SIZE (MII_BUS_ID_SIZE + \
				       माप_field(काष्ठा mdio_device, addr)+\
				       PHY_LED_TRIGGER_SPEED_SUFFIX_SIZE)

काष्ठा phy_led_trigger अणु
	काष्ठा led_trigger trigger;
	अक्षर name[PHY_LINK_LED_TRIGGER_NAME_SIZE];
	अचिन्हित पूर्णांक speed;
पूर्ण;


बाह्य पूर्णांक phy_led_triggers_रेजिस्टर(काष्ठा phy_device *phy);
बाह्य व्योम phy_led_triggers_unरेजिस्टर(काष्ठा phy_device *phy);
बाह्य व्योम phy_led_trigger_change_speed(काष्ठा phy_device *phy);

#अन्यथा

अटल अंतरभूत पूर्णांक phy_led_triggers_रेजिस्टर(काष्ठा phy_device *phy)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम phy_led_triggers_unरेजिस्टर(काष्ठा phy_device *phy) अणु पूर्ण
अटल अंतरभूत व्योम phy_led_trigger_change_speed(काष्ठा phy_device *phy) अणु पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
