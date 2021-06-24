<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2019 Intel Corporation
 * Copyright (C) 2017 Intel Deutschland GmbH
 */
#समावेश <linux/leds.h>
#समावेश "iwl-io.h"
#समावेश "iwl-csr.h"
#समावेश "mvm.h"

अटल व्योम iwl_mvm_send_led_fw_cmd(काष्ठा iwl_mvm *mvm, bool on)
अणु
	काष्ठा iwl_led_cmd led_cmd = अणु
		.status = cpu_to_le32(on),
	पूर्ण;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = WIDE_ID(LONG_GROUP, LEDS_CMD),
		.len = अणु माप(led_cmd), पूर्ण,
		.data = अणु &led_cmd, पूर्ण,
		.flags = CMD_ASYNC,
	पूर्ण;
	पूर्णांक err;

	अगर (!iwl_mvm_firmware_running(mvm))
		वापस;

	err = iwl_mvm_send_cmd(mvm, &cmd);

	अगर (err)
		IWL_WARN(mvm, "LED command failed: %d\n", err);
पूर्ण

अटल व्योम iwl_mvm_led_set(काष्ठा iwl_mvm *mvm, bool on)
अणु
	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_LED_CMD_SUPPORT)) अणु
		iwl_mvm_send_led_fw_cmd(mvm, on);
		वापस;
	पूर्ण

	iwl_ग_लिखो32(mvm->trans, CSR_LED_REG,
		    on ? CSR_LED_REG_TURN_ON : CSR_LED_REG_TURN_OFF);
पूर्ण

अटल व्योम iwl_led_brightness_set(काष्ठा led_classdev *led_cdev,
				   क्रमागत led_brightness brightness)
अणु
	काष्ठा iwl_mvm *mvm = container_of(led_cdev, काष्ठा iwl_mvm, led);

	iwl_mvm_led_set(mvm, brightness > 0);
पूर्ण

पूर्णांक iwl_mvm_leds_init(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक mode = iwlwअगरi_mod_params.led_mode;
	पूर्णांक ret;

	चयन (mode) अणु
	हाल IWL_LED_BLINK:
		IWL_ERR(mvm, "Blink led mode not supported, used default\n");
		fallthrough;
	हाल IWL_LED_DEFAULT:
	हाल IWL_LED_RF_STATE:
		mode = IWL_LED_RF_STATE;
		अवरोध;
	हाल IWL_LED_DISABLE:
		IWL_INFO(mvm, "Led disabled\n");
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mvm->led.name = kaप्र_लिखो(GFP_KERNEL, "%s-led",
				   wiphy_name(mvm->hw->wiphy));
	अगर (!mvm->led.name)
		वापस -ENOMEM;

	mvm->led.brightness_set = iwl_led_brightness_set;
	mvm->led.max_brightness = 1;

	अगर (mode == IWL_LED_RF_STATE)
		mvm->led.शेष_trigger =
			ieee80211_get_radio_led_name(mvm->hw);

	ret = led_classdev_रेजिस्टर(mvm->trans->dev, &mvm->led);
	अगर (ret) अणु
		kमुक्त(mvm->led.name);
		IWL_INFO(mvm, "Failed to enable led\n");
		वापस ret;
	पूर्ण

	mvm->init_status |= IWL_MVM_INIT_STATUS_LEDS_INIT_COMPLETE;
	वापस 0;
पूर्ण

व्योम iwl_mvm_leds_sync(काष्ठा iwl_mvm *mvm)
अणु
	अगर (!(mvm->init_status & IWL_MVM_INIT_STATUS_LEDS_INIT_COMPLETE))
		वापस;

	/*
	 * अगर we control through the रेजिस्टर, we're करोing it
	 * even when the firmware isn't up, so no need to sync
	 */
	अगर (mvm->trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_8000)
		वापस;

	iwl_mvm_led_set(mvm, mvm->led.brightness > 0);
पूर्ण

व्योम iwl_mvm_leds_निकास(काष्ठा iwl_mvm *mvm)
अणु
	अगर (!(mvm->init_status & IWL_MVM_INIT_STATUS_LEDS_INIT_COMPLETE))
		वापस;

	led_classdev_unरेजिस्टर(&mvm->led);
	kमुक्त(mvm->led.name);
	mvm->init_status &= ~IWL_MVM_INIT_STATUS_LEDS_INIT_COMPLETE;
पूर्ण
