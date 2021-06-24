<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*	Copyright (C) 2009 - 2010 Ivo van Doorn <IvDoorn@gmail.com>
 *	Copyright (C) 2009 Alban Browaeys <prahal@yahoo.com>
 *	Copyright (C) 2009 Felix Fietkau <nbd@खोलोwrt.org>
 *	Copyright (C) 2009 Luis Correia <luis.f.correia@gmail.com>
 *	Copyright (C) 2009 Mattias Nissler <mattias.nissler@gmx.de>
 *	Copyright (C) 2009 Mark Asselstine <asselsm@gmail.com>
 *	Copyright (C) 2009 Xose Vazquez Perez <xose.vazquez@gmail.com>
 *	Copyright (C) 2009 Bart Zolnierkiewicz <bzolnier@gmail.com>
 *	<http://rt2x00.serialmonkey.com>
 */

/*	Module: rt2800soc
 *	Abstract: rt2800 WiSoC specअगरic routines.
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "rt2x00.h"
#समावेश "rt2x00mmio.h"
#समावेश "rt2x00soc.h"
#समावेश "rt2800.h"
#समावेश "rt2800lib.h"
#समावेश "rt2800mmio.h"

/* Allow hardware encryption to be disabled. */
अटल bool modparam_nohwcrypt;
module_param_named(nohwcrypt, modparam_nohwcrypt, bool, 0444);
MODULE_PARM_DESC(nohwcrypt, "Disable hardware encryption.");

अटल bool rt2800soc_hwcrypt_disabled(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस modparam_nohwcrypt;
पूर्ण

अटल व्योम rt2800soc_disable_radio(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg;

	rt2800_disable_radio(rt2x00dev);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PWR_PIN_CFG, 0);

	reg = 0;
	अगर (rt2x00_rt(rt2x00dev, RT3883))
		rt2x00_set_field32(&reg, TX_PIN_CFG_RFTR_EN, 1);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PIN_CFG, reg);
पूर्ण

अटल पूर्णांक rt2800soc_set_device_state(काष्ठा rt2x00_dev *rt2x00dev,
				      क्रमागत dev_state state)
अणु
	पूर्णांक retval = 0;

	चयन (state) अणु
	हाल STATE_RADIO_ON:
		retval = rt2800mmio_enable_radio(rt2x00dev);
		अवरोध;

	हाल STATE_RADIO_OFF:
		rt2800soc_disable_radio(rt2x00dev);
		अवरोध;

	हाल STATE_RADIO_IRQ_ON:
	हाल STATE_RADIO_IRQ_OFF:
		rt2800mmio_toggle_irq(rt2x00dev, state);
		अवरोध;

	हाल STATE_DEEP_SLEEP:
	हाल STATE_SLEEP:
	हाल STATE_STANDBY:
	हाल STATE_AWAKE:
		/* These states are not supported, but करोn't report an error */
		retval = 0;
		अवरोध;

	शेष:
		retval = -ENOTSUPP;
		अवरोध;
	पूर्ण

	अगर (unlikely(retval))
		rt2x00_err(rt2x00dev, "Device failed to enter state %d (%d)\n",
			   state, retval);

	वापस retval;
पूर्ण

अटल पूर्णांक rt2800soc_पढ़ो_eeprom(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	व्योम __iomem *base_addr = ioremap(0x1F040000, EEPROM_SIZE);

	अगर (!base_addr)
		वापस -ENOMEM;

	स_नकल_fromio(rt2x00dev->eeprom, base_addr, EEPROM_SIZE);

	iounmap(base_addr);
	वापस 0;
पूर्ण

/* Firmware functions */
अटल अक्षर *rt2800soc_get_firmware_name(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	WARN_ON_ONCE(1);
	वापस शून्य;
पूर्ण

अटल पूर्णांक rt2800soc_load_firmware(काष्ठा rt2x00_dev *rt2x00dev,
				   स्थिर u8 *data, स्थिर माप_प्रकार len)
अणु
	WARN_ON_ONCE(1);
	वापस 0;
पूर्ण

अटल पूर्णांक rt2800soc_check_firmware(काष्ठा rt2x00_dev *rt2x00dev,
				    स्थिर u8 *data, स्थिर माप_प्रकार len)
अणु
	WARN_ON_ONCE(1);
	वापस 0;
पूर्ण

अटल पूर्णांक rt2800soc_ग_लिखो_firmware(काष्ठा rt2x00_dev *rt2x00dev,
				    स्थिर u8 *data, स्थिर माप_प्रकार len)
अणु
	WARN_ON_ONCE(1);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops rt2800soc_mac80211_ops = अणु
	.tx			= rt2x00mac_tx,
	.start			= rt2x00mac_start,
	.stop			= rt2x00mac_stop,
	.add_पूर्णांकerface		= rt2x00mac_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= rt2x00mac_हटाओ_पूर्णांकerface,
	.config			= rt2x00mac_config,
	.configure_filter	= rt2x00mac_configure_filter,
	.set_key		= rt2x00mac_set_key,
	.sw_scan_start		= rt2x00mac_sw_scan_start,
	.sw_scan_complete	= rt2x00mac_sw_scan_complete,
	.get_stats		= rt2x00mac_get_stats,
	.get_key_seq		= rt2800_get_key_seq,
	.set_rts_threshold	= rt2800_set_rts_threshold,
	.sta_add		= rt2800_sta_add,
	.sta_हटाओ		= rt2800_sta_हटाओ,
	.bss_info_changed	= rt2x00mac_bss_info_changed,
	.conf_tx		= rt2800_conf_tx,
	.get_tsf		= rt2800_get_tsf,
	.rfसमाप्त_poll		= rt2x00mac_rfसमाप्त_poll,
	.ampdu_action		= rt2800_ampdu_action,
	.flush			= rt2x00mac_flush,
	.get_survey		= rt2800_get_survey,
	.get_ringparam		= rt2x00mac_get_ringparam,
	.tx_frames_pending	= rt2x00mac_tx_frames_pending,
	.reconfig_complete	= rt2x00mac_reconfig_complete,
पूर्ण;

अटल स्थिर काष्ठा rt2800_ops rt2800soc_rt2800_ops = अणु
	.रेजिस्टर_पढ़ो		= rt2x00mmio_रेजिस्टर_पढ़ो,
	.रेजिस्टर_पढ़ो_lock	= rt2x00mmio_रेजिस्टर_पढ़ो, /* same क्रम SoCs */
	.रेजिस्टर_ग_लिखो		= rt2x00mmio_रेजिस्टर_ग_लिखो,
	.रेजिस्टर_ग_लिखो_lock	= rt2x00mmio_रेजिस्टर_ग_लिखो, /* same क्रम SoCs */
	.रेजिस्टर_multiपढ़ो	= rt2x00mmio_रेजिस्टर_multiपढ़ो,
	.रेजिस्टर_multiग_लिखो	= rt2x00mmio_रेजिस्टर_multiग_लिखो,
	.regbusy_पढ़ो		= rt2x00mmio_regbusy_पढ़ो,
	.पढ़ो_eeprom		= rt2800soc_पढ़ो_eeprom,
	.hwcrypt_disabled	= rt2800soc_hwcrypt_disabled,
	.drv_ग_लिखो_firmware	= rt2800soc_ग_लिखो_firmware,
	.drv_init_रेजिस्टरs	= rt2800mmio_init_रेजिस्टरs,
	.drv_get_txwi		= rt2800mmio_get_txwi,
	.drv_get_dma_करोne	= rt2800mmio_get_dma_करोne,
पूर्ण;

अटल स्थिर काष्ठा rt2x00lib_ops rt2800soc_rt2x00_ops = अणु
	.irq_handler		= rt2800mmio_पूर्णांकerrupt,
	.txstatus_tasklet	= rt2800mmio_txstatus_tasklet,
	.pretbtt_tasklet	= rt2800mmio_pretbtt_tasklet,
	.tbtt_tasklet		= rt2800mmio_tbtt_tasklet,
	.rxकरोne_tasklet		= rt2800mmio_rxकरोne_tasklet,
	.स्वतःwake_tasklet	= rt2800mmio_स्वतःwake_tasklet,
	.probe_hw		= rt2800mmio_probe_hw,
	.get_firmware_name	= rt2800soc_get_firmware_name,
	.check_firmware		= rt2800soc_check_firmware,
	.load_firmware		= rt2800soc_load_firmware,
	.initialize		= rt2x00mmio_initialize,
	.uninitialize		= rt2x00mmio_uninitialize,
	.get_entry_state	= rt2800mmio_get_entry_state,
	.clear_entry		= rt2800mmio_clear_entry,
	.set_device_state	= rt2800soc_set_device_state,
	.rfसमाप्त_poll		= rt2800_rfसमाप्त_poll,
	.link_stats		= rt2800_link_stats,
	.reset_tuner		= rt2800_reset_tuner,
	.link_tuner		= rt2800_link_tuner,
	.gain_calibration	= rt2800_gain_calibration,
	.vco_calibration	= rt2800_vco_calibration,
	.watchकरोg		= rt2800_watchकरोg,
	.start_queue		= rt2800mmio_start_queue,
	.kick_queue		= rt2800mmio_kick_queue,
	.stop_queue		= rt2800mmio_stop_queue,
	.flush_queue		= rt2800mmio_flush_queue,
	.ग_लिखो_tx_desc		= rt2800mmio_ग_लिखो_tx_desc,
	.ग_लिखो_tx_data		= rt2800_ग_लिखो_tx_data,
	.ग_लिखो_beacon		= rt2800_ग_लिखो_beacon,
	.clear_beacon		= rt2800_clear_beacon,
	.fill_rxकरोne		= rt2800mmio_fill_rxकरोne,
	.config_shared_key	= rt2800_config_shared_key,
	.config_pairwise_key	= rt2800_config_pairwise_key,
	.config_filter		= rt2800_config_filter,
	.config_पूर्णांकf		= rt2800_config_पूर्णांकf,
	.config_erp		= rt2800_config_erp,
	.config_ant		= rt2800_config_ant,
	.config			= rt2800_config,
	.pre_reset_hw		= rt2800_pre_reset_hw,
पूर्ण;

अटल स्थिर काष्ठा rt2x00_ops rt2800soc_ops = अणु
	.name			= KBUILD_MODNAME,
	.drv_data_size		= माप(काष्ठा rt2800_drv_data),
	.max_ap_पूर्णांकf		= 8,
	.eeprom_size		= EEPROM_SIZE,
	.rf_size		= RF_SIZE,
	.tx_queues		= NUM_TX_QUEUES,
	.queue_init		= rt2800mmio_queue_init,
	.lib			= &rt2800soc_rt2x00_ops,
	.drv			= &rt2800soc_rt2800_ops,
	.hw			= &rt2800soc_mac80211_ops,
#अगर_घोषित CONFIG_RT2X00_LIB_DEBUGFS
	.debugfs		= &rt2800_rt2x00debug,
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_DEBUGFS */
पूर्ण;

अटल पूर्णांक rt2800soc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस rt2x00soc_probe(pdev, &rt2800soc_ops);
पूर्ण

अटल काष्ठा platक्रमm_driver rt2800soc_driver = अणु
	.driver		= अणु
		.name		= "rt2800_wmac",
		.mod_name	= KBUILD_MODNAME,
	पूर्ण,
	.probe		= rt2800soc_probe,
	.हटाओ		= rt2x00soc_हटाओ,
	.suspend	= rt2x00soc_suspend,
	.resume		= rt2x00soc_resume,
पूर्ण;

module_platक्रमm_driver(rt2800soc_driver);

MODULE_AUTHOR(DRV_PROJECT);
MODULE_VERSION(DRV_VERSION);
MODULE_DESCRIPTION("Ralink WiSoC Wireless LAN driver.");
MODULE_LICENSE("GPL");
