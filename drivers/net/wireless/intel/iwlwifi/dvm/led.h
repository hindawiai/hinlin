<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************
 *
 * Copyright(c) 2003 - 2014 Intel Corporation. All rights reserved.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#अगर_अघोषित __iwl_leds_h__
#घोषणा __iwl_leds_h__


काष्ठा iwl_priv;

#घोषणा IWL_LED_SOLID 11
#घोषणा IWL_DEF_LED_INTRVL cpu_to_le32(1000)

#घोषणा IWL_LED_ACTIVITY       (0<<1)
#घोषणा IWL_LED_LINK           (1<<1)

#अगर_घोषित CONFIG_IWLWIFI_LEDS
व्योम iwlagn_led_enable(काष्ठा iwl_priv *priv);
व्योम iwl_leds_init(काष्ठा iwl_priv *priv);
व्योम iwl_leds_निकास(काष्ठा iwl_priv *priv);
#अन्यथा
अटल अंतरभूत व्योम iwlagn_led_enable(काष्ठा iwl_priv *priv)
अणु
पूर्ण
अटल अंतरभूत व्योम iwl_leds_init(काष्ठा iwl_priv *priv)
अणु
पूर्ण
अटल अंतरभूत व्योम iwl_leds_निकास(काष्ठा iwl_priv *priv)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __iwl_leds_h__ */
