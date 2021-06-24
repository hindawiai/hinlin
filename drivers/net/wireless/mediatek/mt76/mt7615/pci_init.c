<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2019 MediaTek Inc.
 *
 * Author: Roy Luo <royluo@google.com>
 *         Ryder Lee <ryder.lee@mediatek.com>
 *         Felix Fietkau <nbd@nbd.name>
 *         Lorenzo Bianconi <lorenzo@kernel.org>
 */

#समावेश <linux/etherdevice.h>
#समावेश "mt7615.h"
#समावेश "mac.h"
#समावेश "eeprom.h"

अटल व्योम mt7615_pci_init_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7615_dev *dev = container_of(work, काष्ठा mt7615_dev,
					      mcu_work);
	पूर्णांक i, ret;

	ret = mt7615_mcu_init(dev);
	क्रम (i = 0; (ret == -EAGAIN) && (i < 10); i++) अणु
		msleep(200);
		ret = mt7615_mcu_init(dev);
	पूर्ण

	अगर (ret)
		वापस;

	mt7615_init_work(dev);
	अगर (dev->dbdc_support)
		mt7615_रेजिस्टर_ext_phy(dev);
पूर्ण

अटल पूर्णांक mt7615_init_hardware(काष्ठा mt7615_dev *dev)
अणु
	u32 addr = mt7615_reg_map(dev, MT_EFUSE_BASE);
	पूर्णांक ret, idx;

	mt76_wr(dev, MT_INT_SOURCE_CSR, ~0);

	INIT_WORK(&dev->mcu_work, mt7615_pci_init_work);
	ret = mt7615_eeprom_init(dev, addr);
	अगर (ret < 0)
		वापस ret;

	अगर (is_mt7663(&dev->mt76)) अणु
		/* Reset RGU */
		mt76_clear(dev, MT_MCU_CIRQ_IRQ_SEL(4), BIT(1));
		mt76_set(dev, MT_MCU_CIRQ_IRQ_SEL(4), BIT(1));
	पूर्ण

	ret = mt7615_dma_init(dev);
	अगर (ret)
		वापस ret;

	set_bit(MT76_STATE_INITIALIZED, &dev->mphy.state);

	/* Beacon and mgmt frames should occupy wcid 0 */
	idx = mt76_wcid_alloc(dev->mt76.wcid_mask, MT7615_WTBL_STA - 1);
	अगर (idx)
		वापस -ENOSPC;

	dev->mt76.global_wcid.idx = idx;
	dev->mt76.global_wcid.hw_key_idx = -1;
	rcu_assign_poपूर्णांकer(dev->mt76.wcid[idx], &dev->mt76.global_wcid);

	वापस 0;
पूर्ण

अटल व्योम
mt7615_led_set_config(काष्ठा led_classdev *led_cdev,
		      u8 delay_on, u8 delay_off)
अणु
	काष्ठा mt7615_dev *dev;
	काष्ठा mt76_dev *mt76;
	u32 val, addr;

	mt76 = container_of(led_cdev, काष्ठा mt76_dev, led_cdev);
	dev = container_of(mt76, काष्ठा mt7615_dev, mt76);

	अगर (!mt76_connac_pm_ref(&dev->mphy, &dev->pm))
		वापस;

	val = FIELD_PREP(MT_LED_STATUS_DURATION, 0xffff) |
	      FIELD_PREP(MT_LED_STATUS_OFF, delay_off) |
	      FIELD_PREP(MT_LED_STATUS_ON, delay_on);

	addr = mt7615_reg_map(dev, MT_LED_STATUS_0(mt76->led_pin));
	mt76_wr(dev, addr, val);
	addr = mt7615_reg_map(dev, MT_LED_STATUS_1(mt76->led_pin));
	mt76_wr(dev, addr, val);

	val = MT_LED_CTRL_REPLAY(mt76->led_pin) |
	      MT_LED_CTRL_KICK(mt76->led_pin);
	अगर (mt76->led_al)
		val |= MT_LED_CTRL_POLARITY(mt76->led_pin);
	addr = mt7615_reg_map(dev, MT_LED_CTRL);
	mt76_wr(dev, addr, val);

	mt76_connac_pm_unref(&dev->pm);
पूर्ण

अटल पूर्णांक
mt7615_led_set_blink(काष्ठा led_classdev *led_cdev,
		     अचिन्हित दीर्घ *delay_on,
		     अचिन्हित दीर्घ *delay_off)
अणु
	u8 delta_on, delta_off;

	delta_off = max_t(u8, *delay_off / 10, 1);
	delta_on = max_t(u8, *delay_on / 10, 1);

	mt7615_led_set_config(led_cdev, delta_on, delta_off);

	वापस 0;
पूर्ण

अटल व्योम
mt7615_led_set_brightness(काष्ठा led_classdev *led_cdev,
			  क्रमागत led_brightness brightness)
अणु
	अगर (!brightness)
		mt7615_led_set_config(led_cdev, 0, 0xff);
	अन्यथा
		mt7615_led_set_config(led_cdev, 0xff, 0);
पूर्ण

पूर्णांक mt7615_रेजिस्टर_device(काष्ठा mt7615_dev *dev)
अणु
	पूर्णांक ret;

	mt7615_init_device(dev);
	INIT_WORK(&dev->reset_work, mt7615_mac_reset_work);

	/* init led callbacks */
	अगर (IS_ENABLED(CONFIG_MT76_LEDS)) अणु
		dev->mt76.led_cdev.brightness_set = mt7615_led_set_brightness;
		dev->mt76.led_cdev.blink_set = mt7615_led_set_blink;
	पूर्ण

	ret = mt7622_wmac_init(dev);
	अगर (ret)
		वापस ret;

	ret = mt7615_init_hardware(dev);
	अगर (ret)
		वापस ret;

	ret = mt76_रेजिस्टर_device(&dev->mt76, true, mt7615_rates,
				   ARRAY_SIZE(mt7615_rates));
	अगर (ret)
		वापस ret;

	ieee80211_queue_work(mt76_hw(dev), &dev->mcu_work);
	mt7615_init_txघातer(dev, &dev->mphy.sband_2g.sband);
	mt7615_init_txघातer(dev, &dev->mphy.sband_5g.sband);

	वापस mt7615_init_debugfs(dev);
पूर्ण

व्योम mt7615_unरेजिस्टर_device(काष्ठा mt7615_dev *dev)
अणु
	bool mcu_running;

	mcu_running = mt7615_रुको_क्रम_mcu_init(dev);

	mt7615_unरेजिस्टर_ext_phy(dev);
	mt76_unरेजिस्टर_device(&dev->mt76);
	अगर (mcu_running)
		mt7615_mcu_निकास(dev);

	mt7615_tx_token_put(dev);
	mt7615_dma_cleanup(dev);
	tasklet_disable(&dev->irq_tasklet);

	mt76_मुक्त_device(&dev->mt76);
पूर्ण
