<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2003 - 2014 Intel Corporation. All rights reserved.
 * Copyright (C) 2019 Intel Corporation
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/


#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <net/mac80211.h>
#समावेश <linux/etherdevice.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "iwl-io.h"
#समावेश "iwl-trans.h"
#समावेश "iwl-modparams.h"
#समावेश "dev.h"
#समावेश "agn.h"

/* Throughput		OFF समय(ms)	ON समय (ms)
 *	>300			25		25
 *	>200 to 300		40		40
 *	>100 to 200		55		55
 *	>70 to 100		65		65
 *	>50 to 70		75		75
 *	>20 to 50		85		85
 *	>10 to 20		95		95
 *	>5 to 10		110		110
 *	>1 to 5			130		130
 *	>0 to 1			167		167
 *	<=0					SOLID ON
 */
अटल स्थिर काष्ठा ieee80211_tpt_blink iwl_blink[] = अणु
	अणु .throughput = 0, .blink_समय = 334 पूर्ण,
	अणु .throughput = 1 * 1024 - 1, .blink_समय = 260 पूर्ण,
	अणु .throughput = 5 * 1024 - 1, .blink_समय = 220 पूर्ण,
	अणु .throughput = 10 * 1024 - 1, .blink_समय = 190 पूर्ण,
	अणु .throughput = 20 * 1024 - 1, .blink_समय = 170 पूर्ण,
	अणु .throughput = 50 * 1024 - 1, .blink_समय = 150 पूर्ण,
	अणु .throughput = 70 * 1024 - 1, .blink_समय = 130 पूर्ण,
	अणु .throughput = 100 * 1024 - 1, .blink_समय = 110 पूर्ण,
	अणु .throughput = 200 * 1024 - 1, .blink_समय = 80 पूर्ण,
	अणु .throughput = 300 * 1024 - 1, .blink_समय = 50 पूर्ण,
पूर्ण;

/* Set led रेजिस्टर off */
व्योम iwlagn_led_enable(काष्ठा iwl_priv *priv)
अणु
	iwl_ग_लिखो32(priv->trans, CSR_LED_REG, CSR_LED_REG_TURN_ON);
पूर्ण

/*
 * Adjust led blink rate to compensate on a MAC Clock dअगरference on every HW
 * Led blink rate analysis showed an average deviation of 20% on 5000 series
 * and up.
 * Need to compensate on the led on/off समय per HW according to the deviation
 * to achieve the desired led frequency
 * The calculation is: (100-averageDeviation)/100 * blinkTime
 * For code efficiency the calculation will be:
 *     compensation = (100 - averageDeviation) * 64 / 100
 *     NewBlinkTime = (compensation * BlinkTime) / 64
 */
अटल अंतरभूत u8 iwl_blink_compensation(काष्ठा iwl_priv *priv,
				    u8 समय, u16 compensation)
अणु
	अगर (!compensation) अणु
		IWL_ERR(priv, "undefined blink compensation: "
			"use pre-defined blinking time\n");
		वापस समय;
	पूर्ण

	वापस (u8)((समय * compensation) >> 6);
पूर्ण

अटल पूर्णांक iwl_send_led_cmd(काष्ठा iwl_priv *priv, काष्ठा iwl_led_cmd *led_cmd)
अणु
	काष्ठा iwl_host_cmd cmd = अणु
		.id = REPLY_LEDS_CMD,
		.len = अणु माप(काष्ठा iwl_led_cmd), पूर्ण,
		.data = अणु led_cmd, पूर्ण,
		.flags = CMD_ASYNC,
	पूर्ण;
	u32 reg;

	reg = iwl_पढ़ो32(priv->trans, CSR_LED_REG);
	अगर (reg != (reg & CSR_LED_BSM_CTRL_MSK))
		iwl_ग_लिखो32(priv->trans, CSR_LED_REG,
			    reg & CSR_LED_BSM_CTRL_MSK);

	वापस iwl_dvm_send_cmd(priv, &cmd);
पूर्ण

/* Set led pattern command */
अटल पूर्णांक iwl_led_cmd(काष्ठा iwl_priv *priv,
		       अचिन्हित दीर्घ on,
		       अचिन्हित दीर्घ off)
अणु
	काष्ठा iwl_led_cmd led_cmd = अणु
		.id = IWL_LED_LINK,
		.पूर्णांकerval = IWL_DEF_LED_INTRVL
	पूर्ण;
	पूर्णांक ret;

	अगर (!test_bit(STATUS_READY, &priv->status))
		वापस -EBUSY;

	अगर (priv->blink_on == on && priv->blink_off == off)
		वापस 0;

	अगर (off == 0) अणु
		/* led is SOLID_ON */
		on = IWL_LED_SOLID;
	पूर्ण

	led_cmd.on = iwl_blink_compensation(priv, on,
				priv->trans->trans_cfg->base_params->led_compensation);
	led_cmd.off = iwl_blink_compensation(priv, off,
				priv->trans->trans_cfg->base_params->led_compensation);

	ret = iwl_send_led_cmd(priv, &led_cmd);
	अगर (!ret) अणु
		priv->blink_on = on;
		priv->blink_off = off;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम iwl_led_brightness_set(काष्ठा led_classdev *led_cdev,
				   क्रमागत led_brightness brightness)
अणु
	काष्ठा iwl_priv *priv = container_of(led_cdev, काष्ठा iwl_priv, led);
	अचिन्हित दीर्घ on = 0;
	अचिन्हित दीर्घ off = 0;

	अगर (brightness > 0)
		on = IWL_LED_SOLID;
	अन्यथा
		off = IWL_LED_SOLID;

	iwl_led_cmd(priv, on, off);
पूर्ण

अटल पूर्णांक iwl_led_blink_set(काष्ठा led_classdev *led_cdev,
			     अचिन्हित दीर्घ *delay_on,
			     अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा iwl_priv *priv = container_of(led_cdev, काष्ठा iwl_priv, led);

	वापस iwl_led_cmd(priv, *delay_on, *delay_off);
पूर्ण

व्योम iwl_leds_init(काष्ठा iwl_priv *priv)
अणु
	पूर्णांक mode = iwlwअगरi_mod_params.led_mode;
	पूर्णांक ret;

	अगर (mode == IWL_LED_DISABLE) अणु
		IWL_INFO(priv, "Led disabled\n");
		वापस;
	पूर्ण
	अगर (mode == IWL_LED_DEFAULT)
		mode = priv->cfg->led_mode;

	priv->led.name = kaप्र_लिखो(GFP_KERNEL, "%s-led",
				   wiphy_name(priv->hw->wiphy));
	अगर (!priv->led.name)
		वापस;

	priv->led.brightness_set = iwl_led_brightness_set;
	priv->led.blink_set = iwl_led_blink_set;
	priv->led.max_brightness = 1;

	चयन (mode) अणु
	हाल IWL_LED_DEFAULT:
		WARN_ON(1);
		अवरोध;
	हाल IWL_LED_BLINK:
		priv->led.शेष_trigger =
			ieee80211_create_tpt_led_trigger(priv->hw,
					IEEE80211_TPT_LEDTRIG_FL_CONNECTED,
					iwl_blink, ARRAY_SIZE(iwl_blink));
		अवरोध;
	हाल IWL_LED_RF_STATE:
		priv->led.शेष_trigger =
			ieee80211_get_radio_led_name(priv->hw);
		अवरोध;
	पूर्ण

	ret = led_classdev_रेजिस्टर(priv->trans->dev, &priv->led);
	अगर (ret) अणु
		kमुक्त(priv->led.name);
		वापस;
	पूर्ण

	priv->led_रेजिस्टरed = true;
पूर्ण

व्योम iwl_leds_निकास(काष्ठा iwl_priv *priv)
अणु
	अगर (!priv->led_रेजिस्टरed)
		वापस;

	led_classdev_unरेजिस्टर(&priv->led);
	kमुक्त(priv->led.name);
पूर्ण
