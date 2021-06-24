<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Copyright (C) 2009 - 2010 Ivo van Doorn <IvDoorn@gmail.com>
	Copyright (C) 2009 Alban Browaeys <prahal@yahoo.com>
	Copyright (C) 2009 Felix Fietkau <nbd@खोलोwrt.org>
	Copyright (C) 2009 Luis Correia <luis.f.correia@gmail.com>
	Copyright (C) 2009 Mattias Nissler <mattias.nissler@gmx.de>
	Copyright (C) 2009 Mark Asselstine <asselsm@gmail.com>
	Copyright (C) 2009 Xose Vazquez Perez <xose.vazquez@gmail.com>
	Copyright (C) 2009 Bart Zolnierkiewicz <bzolnier@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2800pci
	Abstract: rt2800pci device specअगरic routines.
	Supported chipsets: RT2800E & RT2800ED.
 */

#समावेश <linux/delay.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/eeprom_93cx6.h>

#समावेश "rt2x00.h"
#समावेश "rt2x00mmio.h"
#समावेश "rt2x00pci.h"
#समावेश "rt2800lib.h"
#समावेश "rt2800mmio.h"
#समावेश "rt2800.h"
#समावेश "rt2800pci.h"

/*
 * Allow hardware encryption to be disabled.
 */
अटल bool modparam_nohwcrypt = false;
module_param_named(nohwcrypt, modparam_nohwcrypt, bool, 0444);
MODULE_PARM_DESC(nohwcrypt, "Disable hardware encryption.");

अटल bool rt2800pci_hwcrypt_disabled(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस modparam_nohwcrypt;
पूर्ण

अटल व्योम rt2800pci_mcu_status(काष्ठा rt2x00_dev *rt2x00dev, स्थिर u8 token)
अणु
	अचिन्हित पूर्णांक i;
	u32 reg;

	/*
	 * SOC devices करोn't support MCU requests.
	 */
	अगर (rt2x00_is_soc(rt2x00dev))
		वापस;

	क्रम (i = 0; i < 200; i++) अणु
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, H2M_MAILBOX_CID);

		अगर ((rt2x00_get_field32(reg, H2M_MAILBOX_CID_CMD0) == token) ||
		    (rt2x00_get_field32(reg, H2M_MAILBOX_CID_CMD1) == token) ||
		    (rt2x00_get_field32(reg, H2M_MAILBOX_CID_CMD2) == token) ||
		    (rt2x00_get_field32(reg, H2M_MAILBOX_CID_CMD3) == token))
			अवरोध;

		udelay(REGISTER_BUSY_DELAY);
	पूर्ण

	अगर (i == 200)
		rt2x00_err(rt2x00dev, "MCU request failed, no response from hardware\n");

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, H2M_MAILBOX_STATUS, ~0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, H2M_MAILBOX_CID, ~0);
पूर्ण

अटल व्योम rt2800pci_eepromरेजिस्टर_पढ़ो(काष्ठा eeprom_93cx6 *eeprom)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = eeprom->data;
	u32 reg;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, E2PROM_CSR);

	eeprom->reg_data_in = !!rt2x00_get_field32(reg, E2PROM_CSR_DATA_IN);
	eeprom->reg_data_out = !!rt2x00_get_field32(reg, E2PROM_CSR_DATA_OUT);
	eeprom->reg_data_घड़ी =
	    !!rt2x00_get_field32(reg, E2PROM_CSR_DATA_CLOCK);
	eeprom->reg_chip_select =
	    !!rt2x00_get_field32(reg, E2PROM_CSR_CHIP_SELECT);
पूर्ण

अटल व्योम rt2800pci_eepromरेजिस्टर_ग_लिखो(काष्ठा eeprom_93cx6 *eeprom)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = eeprom->data;
	u32 reg = 0;

	rt2x00_set_field32(&reg, E2PROM_CSR_DATA_IN, !!eeprom->reg_data_in);
	rt2x00_set_field32(&reg, E2PROM_CSR_DATA_OUT, !!eeprom->reg_data_out);
	rt2x00_set_field32(&reg, E2PROM_CSR_DATA_CLOCK,
			   !!eeprom->reg_data_घड़ी);
	rt2x00_set_field32(&reg, E2PROM_CSR_CHIP_SELECT,
			   !!eeprom->reg_chip_select);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, E2PROM_CSR, reg);
पूर्ण

अटल पूर्णांक rt2800pci_पढ़ो_eeprom_pci(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा eeprom_93cx6 eeprom;
	u32 reg;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, E2PROM_CSR);

	eeprom.data = rt2x00dev;
	eeprom.रेजिस्टर_पढ़ो = rt2800pci_eepromरेजिस्टर_पढ़ो;
	eeprom.रेजिस्टर_ग_लिखो = rt2800pci_eepromरेजिस्टर_ग_लिखो;
	चयन (rt2x00_get_field32(reg, E2PROM_CSR_TYPE))
	अणु
	हाल 0:
		eeprom.width = PCI_EEPROM_WIDTH_93C46;
		अवरोध;
	हाल 1:
		eeprom.width = PCI_EEPROM_WIDTH_93C66;
		अवरोध;
	शेष:
		eeprom.width = PCI_EEPROM_WIDTH_93C86;
		अवरोध;
	पूर्ण
	eeprom.reg_data_in = 0;
	eeprom.reg_data_out = 0;
	eeprom.reg_data_घड़ी = 0;
	eeprom.reg_chip_select = 0;

	eeprom_93cx6_multiपढ़ो(&eeprom, EEPROM_BASE, rt2x00dev->eeprom,
			       EEPROM_SIZE / माप(u16));

	वापस 0;
पूर्ण

अटल पूर्णांक rt2800pci_efuse_detect(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस rt2800_efuse_detect(rt2x00dev);
पूर्ण

अटल अंतरभूत पूर्णांक rt2800pci_पढ़ो_eeprom_efuse(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस rt2800_पढ़ो_eeprom_efuse(rt2x00dev);
पूर्ण

/*
 * Firmware functions
 */
अटल अक्षर *rt2800pci_get_firmware_name(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	/*
	 * Chip rt3290 use specअगरic 4KB firmware named rt3290.bin.
	 */
	अगर (rt2x00_rt(rt2x00dev, RT3290))
		वापस FIRMWARE_RT3290;
	अन्यथा
		वापस FIRMWARE_RT2860;
पूर्ण

अटल पूर्णांक rt2800pci_ग_लिखो_firmware(काष्ठा rt2x00_dev *rt2x00dev,
				    स्थिर u8 *data, स्थिर माप_प्रकार len)
अणु
	u32 reg;

	/*
	 * enable Host program ram ग_लिखो selection
	 */
	reg = 0;
	rt2x00_set_field32(&reg, PBF_SYS_CTRL_HOST_RAM_WRITE, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PBF_SYS_CTRL, reg);

	/*
	 * Write firmware to device.
	 */
	rt2x00mmio_रेजिस्टर_multiग_लिखो(rt2x00dev, FIRMWARE_IMAGE_BASE,
				       data, len);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PBF_SYS_CTRL, 0x00000);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PBF_SYS_CTRL, 0x00001);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, H2M_BBP_AGENT, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, H2M_MAILBOX_CSR, 0);

	वापस 0;
पूर्ण

/*
 * Device state चयन handlers.
 */
अटल पूर्णांक rt2800pci_enable_radio(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	पूर्णांक retval;

	retval = rt2800mmio_enable_radio(rt2x00dev);
	अगर (retval)
		वापस retval;

	/* After resume MCU_BOOT_SIGNAL will trash these. */
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, H2M_MAILBOX_STATUS, ~0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, H2M_MAILBOX_CID, ~0);

	rt2800_mcu_request(rt2x00dev, MCU_SLEEP, TOKEN_RADIO_OFF, 0xff, 0x02);
	rt2800pci_mcu_status(rt2x00dev, TOKEN_RADIO_OFF);

	rt2800_mcu_request(rt2x00dev, MCU_WAKEUP, TOKEN_WAKEUP, 0, 0);
	rt2800pci_mcu_status(rt2x00dev, TOKEN_WAKEUP);

	वापस retval;
पूर्ण

अटल पूर्णांक rt2800pci_set_state(काष्ठा rt2x00_dev *rt2x00dev,
			       क्रमागत dev_state state)
अणु
	अगर (state == STATE_AWAKE) अणु
		rt2800_mcu_request(rt2x00dev, MCU_WAKEUP, TOKEN_WAKEUP,
				   0, 0x02);
		rt2800pci_mcu_status(rt2x00dev, TOKEN_WAKEUP);
	पूर्ण अन्यथा अगर (state == STATE_SLEEP) अणु
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, H2M_MAILBOX_STATUS,
					  0xffffffff);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, H2M_MAILBOX_CID,
					  0xffffffff);
		rt2800_mcu_request(rt2x00dev, MCU_SLEEP, TOKEN_SLEEP,
				   0xff, 0x01);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt2800pci_set_device_state(काष्ठा rt2x00_dev *rt2x00dev,
				      क्रमागत dev_state state)
अणु
	पूर्णांक retval = 0;

	चयन (state) अणु
	हाल STATE_RADIO_ON:
		retval = rt2800pci_enable_radio(rt2x00dev);
		अवरोध;
	हाल STATE_RADIO_OFF:
		/*
		 * After the radio has been disabled, the device should
		 * be put to sleep क्रम घातersaving.
		 */
		rt2800pci_set_state(rt2x00dev, STATE_SLEEP);
		अवरोध;
	हाल STATE_RADIO_IRQ_ON:
	हाल STATE_RADIO_IRQ_OFF:
		rt2800mmio_toggle_irq(rt2x00dev, state);
		अवरोध;
	हाल STATE_DEEP_SLEEP:
	हाल STATE_SLEEP:
	हाल STATE_STANDBY:
	हाल STATE_AWAKE:
		retval = rt2800pci_set_state(rt2x00dev, state);
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

/*
 * Device probe functions.
 */
अटल पूर्णांक rt2800pci_पढ़ो_eeprom(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	पूर्णांक retval;

	अगर (rt2800pci_efuse_detect(rt2x00dev))
		retval = rt2800pci_पढ़ो_eeprom_efuse(rt2x00dev);
	अन्यथा
		retval = rt2800pci_पढ़ो_eeprom_pci(rt2x00dev);

	वापस retval;
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops rt2800pci_mac80211_ops = अणु
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

अटल स्थिर काष्ठा rt2800_ops rt2800pci_rt2800_ops = अणु
	.रेजिस्टर_पढ़ो		= rt2x00mmio_रेजिस्टर_पढ़ो,
	.रेजिस्टर_पढ़ो_lock	= rt2x00mmio_रेजिस्टर_पढ़ो, /* same क्रम PCI */
	.रेजिस्टर_ग_लिखो		= rt2x00mmio_रेजिस्टर_ग_लिखो,
	.रेजिस्टर_ग_लिखो_lock	= rt2x00mmio_रेजिस्टर_ग_लिखो, /* same क्रम PCI */
	.रेजिस्टर_multiपढ़ो	= rt2x00mmio_रेजिस्टर_multiपढ़ो,
	.रेजिस्टर_multiग_लिखो	= rt2x00mmio_रेजिस्टर_multiग_लिखो,
	.regbusy_पढ़ो		= rt2x00mmio_regbusy_पढ़ो,
	.पढ़ो_eeprom		= rt2800pci_पढ़ो_eeprom,
	.hwcrypt_disabled	= rt2800pci_hwcrypt_disabled,
	.drv_ग_लिखो_firmware	= rt2800pci_ग_लिखो_firmware,
	.drv_init_रेजिस्टरs	= rt2800mmio_init_रेजिस्टरs,
	.drv_get_txwi		= rt2800mmio_get_txwi,
	.drv_get_dma_करोne	= rt2800mmio_get_dma_करोne,
पूर्ण;

अटल स्थिर काष्ठा rt2x00lib_ops rt2800pci_rt2x00_ops = अणु
	.irq_handler		= rt2800mmio_पूर्णांकerrupt,
	.txstatus_tasklet	= rt2800mmio_txstatus_tasklet,
	.pretbtt_tasklet	= rt2800mmio_pretbtt_tasklet,
	.tbtt_tasklet		= rt2800mmio_tbtt_tasklet,
	.rxकरोne_tasklet		= rt2800mmio_rxकरोne_tasklet,
	.स्वतःwake_tasklet	= rt2800mmio_स्वतःwake_tasklet,
	.probe_hw		= rt2800mmio_probe_hw,
	.get_firmware_name	= rt2800pci_get_firmware_name,
	.check_firmware		= rt2800_check_firmware,
	.load_firmware		= rt2800_load_firmware,
	.initialize		= rt2x00mmio_initialize,
	.uninitialize		= rt2x00mmio_uninitialize,
	.get_entry_state	= rt2800mmio_get_entry_state,
	.clear_entry		= rt2800mmio_clear_entry,
	.set_device_state	= rt2800pci_set_device_state,
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

अटल स्थिर काष्ठा rt2x00_ops rt2800pci_ops = अणु
	.name			= KBUILD_MODNAME,
	.drv_data_size		= माप(काष्ठा rt2800_drv_data),
	.max_ap_पूर्णांकf		= 8,
	.eeprom_size		= EEPROM_SIZE,
	.rf_size		= RF_SIZE,
	.tx_queues		= NUM_TX_QUEUES,
	.queue_init		= rt2800mmio_queue_init,
	.lib			= &rt2800pci_rt2x00_ops,
	.drv			= &rt2800pci_rt2800_ops,
	.hw			= &rt2800pci_mac80211_ops,
#अगर_घोषित CONFIG_RT2X00_LIB_DEBUGFS
	.debugfs		= &rt2800_rt2x00debug,
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_DEBUGFS */
पूर्ण;

/*
 * RT2800pci module inक्रमmation.
 */
अटल स्थिर काष्ठा pci_device_id rt2800pci_device_table[] = अणु
	अणु PCI_DEVICE(0x1814, 0x0601) पूर्ण,
	अणु PCI_DEVICE(0x1814, 0x0681) पूर्ण,
	अणु PCI_DEVICE(0x1814, 0x0701) पूर्ण,
	अणु PCI_DEVICE(0x1814, 0x0781) पूर्ण,
	अणु PCI_DEVICE(0x1814, 0x3090) पूर्ण,
	अणु PCI_DEVICE(0x1814, 0x3091) पूर्ण,
	अणु PCI_DEVICE(0x1814, 0x3092) पूर्ण,
	अणु PCI_DEVICE(0x1432, 0x7708) पूर्ण,
	अणु PCI_DEVICE(0x1432, 0x7727) पूर्ण,
	अणु PCI_DEVICE(0x1432, 0x7728) पूर्ण,
	अणु PCI_DEVICE(0x1432, 0x7738) पूर्ण,
	अणु PCI_DEVICE(0x1432, 0x7748) पूर्ण,
	अणु PCI_DEVICE(0x1432, 0x7758) पूर्ण,
	अणु PCI_DEVICE(0x1432, 0x7768) पूर्ण,
	अणु PCI_DEVICE(0x1462, 0x891a) पूर्ण,
	अणु PCI_DEVICE(0x1a3b, 0x1059) पूर्ण,
#अगर_घोषित CONFIG_RT2800PCI_RT3290
	अणु PCI_DEVICE(0x1814, 0x3290) पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_RT2800PCI_RT33XX
	अणु PCI_DEVICE(0x1814, 0x3390) पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_RT2800PCI_RT35XX
	अणु PCI_DEVICE(0x1432, 0x7711) पूर्ण,
	अणु PCI_DEVICE(0x1432, 0x7722) पूर्ण,
	अणु PCI_DEVICE(0x1814, 0x3060) पूर्ण,
	अणु PCI_DEVICE(0x1814, 0x3062) पूर्ण,
	अणु PCI_DEVICE(0x1814, 0x3562) पूर्ण,
	अणु PCI_DEVICE(0x1814, 0x3592) पूर्ण,
	अणु PCI_DEVICE(0x1814, 0x3593) पूर्ण,
	अणु PCI_DEVICE(0x1814, 0x359f) पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_RT2800PCI_RT53XX
	अणु PCI_DEVICE(0x1814, 0x5360) पूर्ण,
	अणु PCI_DEVICE(0x1814, 0x5362) पूर्ण,
	अणु PCI_DEVICE(0x1814, 0x5390) पूर्ण,
	अणु PCI_DEVICE(0x1814, 0x5392) पूर्ण,
	अणु PCI_DEVICE(0x1814, 0x539a) पूर्ण,
	अणु PCI_DEVICE(0x1814, 0x539b) पूर्ण,
	अणु PCI_DEVICE(0x1814, 0x539f) पूर्ण,
#पूर्ण_अगर
	अणु 0, पूर्ण
पूर्ण;

MODULE_AUTHOR(DRV_PROJECT);
MODULE_VERSION(DRV_VERSION);
MODULE_DESCRIPTION("Ralink RT2800 PCI & PCMCIA Wireless LAN driver.");
MODULE_FIRMWARE(FIRMWARE_RT2860);
MODULE_DEVICE_TABLE(pci, rt2800pci_device_table);
MODULE_LICENSE("GPL");

अटल पूर्णांक rt2800pci_probe(काष्ठा pci_dev *pci_dev,
			   स्थिर काष्ठा pci_device_id *id)
अणु
	वापस rt2x00pci_probe(pci_dev, &rt2800pci_ops);
पूर्ण

अटल काष्ठा pci_driver rt2800pci_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= rt2800pci_device_table,
	.probe		= rt2800pci_probe,
	.हटाओ		= rt2x00pci_हटाओ,
	.driver.pm	= &rt2x00pci_pm_ops,
पूर्ण;

module_pci_driver(rt2800pci_driver);
