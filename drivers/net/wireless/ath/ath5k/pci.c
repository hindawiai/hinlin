<शैली गुरु>
/*
 * Copyright (c) 2008-2009 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/nl80211.h>
#समावेश <linux/pci.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/module.h>
#समावेश "../ath.h"
#समावेश "ath5k.h"
#समावेश "debug.h"
#समावेश "base.h"
#समावेश "reg.h"

/* Known PCI ids */
अटल स्थिर काष्ठा pci_device_id ath5k_pci_id_table[] = अणु
	अणु PCI_VDEVICE(ATHEROS, 0x0207) पूर्ण, /* 5210 early */
	अणु PCI_VDEVICE(ATHEROS, 0x0007) पूर्ण, /* 5210 */
	अणु PCI_VDEVICE(ATHEROS, 0x0011) पूर्ण, /* 5311 - this is on AHB bus !*/
	अणु PCI_VDEVICE(ATHEROS, 0x0012) पूर्ण, /* 5211 */
	अणु PCI_VDEVICE(ATHEROS, 0x0013) पूर्ण, /* 5212 */
	अणु PCI_VDEVICE(3COM_2,  0x0013) पूर्ण, /* 3com 5212 */
	अणु PCI_VDEVICE(3COM,    0x0013) पूर्ण, /* 3com 3CRDAG675 5212 */
	अणु PCI_VDEVICE(ATHEROS, 0x1014) पूर्ण, /* IBM minipci 5212 */
	अणु PCI_VDEVICE(ATHEROS, 0x0014) पूर्ण, /* 5212 compatible */
	अणु PCI_VDEVICE(ATHEROS, 0x0015) पूर्ण, /* 5212 compatible */
	अणु PCI_VDEVICE(ATHEROS, 0x0016) पूर्ण, /* 5212 compatible */
	अणु PCI_VDEVICE(ATHEROS, 0x0017) पूर्ण, /* 5212 compatible */
	अणु PCI_VDEVICE(ATHEROS, 0x0018) पूर्ण, /* 5212 compatible */
	अणु PCI_VDEVICE(ATHEROS, 0x0019) पूर्ण, /* 5212 compatible */
	अणु PCI_VDEVICE(ATHEROS, 0x001a) पूर्ण, /* 2413 Grअगरfin-lite */
	अणु PCI_VDEVICE(ATHEROS, 0x001b) पूर्ण, /* 5413 Eagle */
	अणु PCI_VDEVICE(ATHEROS, 0x001c) पूर्ण, /* PCI-E cards */
	अणु PCI_VDEVICE(ATHEROS, 0x001d) पूर्ण, /* 2417 Nala */
	अणु PCI_VDEVICE(ATHEROS, 0xff1b) पूर्ण, /* AR5BXB63 */
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ath5k_pci_id_table);

/* वापस bus cachesize in 4B word units */
अटल व्योम ath5k_pci_पढ़ो_cachesize(काष्ठा ath_common *common, पूर्णांक *csz)
अणु
	काष्ठा ath5k_hw *ah = (काष्ठा ath5k_hw *) common->priv;
	u8 u8पंचांगp;

	pci_पढ़ो_config_byte(ah->pdev, PCI_CACHE_LINE_SIZE, &u8पंचांगp);
	*csz = (पूर्णांक)u8पंचांगp;

	/*
	 * This check was put in to aव्योम "unpleasant" consequences अगर
	 * the bootrom has not fully initialized all PCI devices.
	 * Someबार the cache line size रेजिस्टर is not set
	 */

	अगर (*csz == 0)
		*csz = L1_CACHE_BYTES >> 2;   /* Use the शेष size */
पूर्ण

/*
 * Read from eeprom
 */
अटल bool
ath5k_pci_eeprom_पढ़ो(काष्ठा ath_common *common, u32 offset, u16 *data)
अणु
	काष्ठा ath5k_hw *ah = (काष्ठा ath5k_hw *) common->ah;
	u32 status, समयout;

	/*
	 * Initialize EEPROM access
	 */
	अगर (ah->ah_version == AR5K_AR5210) अणु
		AR5K_REG_ENABLE_BITS(ah, AR5K_PCICFG, AR5K_PCICFG_EEAE);
		(व्योम)ath5k_hw_reg_पढ़ो(ah, AR5K_EEPROM_BASE + (4 * offset));
	पूर्ण अन्यथा अणु
		ath5k_hw_reg_ग_लिखो(ah, offset, AR5K_EEPROM_BASE);
		AR5K_REG_ENABLE_BITS(ah, AR5K_EEPROM_CMD,
				AR5K_EEPROM_CMD_READ);
	पूर्ण

	क्रम (समयout = AR5K_TUNE_REGISTER_TIMEOUT; समयout > 0; समयout--) अणु
		status = ath5k_hw_reg_पढ़ो(ah, AR5K_EEPROM_STATUS);
		अगर (status & AR5K_EEPROM_STAT_RDDONE) अणु
			अगर (status & AR5K_EEPROM_STAT_RDERR)
				वापस false;
			*data = (u16)(ath5k_hw_reg_पढ़ो(ah, AR5K_EEPROM_DATA) &
					0xffff);
			वापस true;
		पूर्ण
		usleep_range(15, 20);
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक ath5k_hw_पढ़ो_srev(काष्ठा ath5k_hw *ah)
अणु
	ah->ah_mac_srev = ath5k_hw_reg_पढ़ो(ah, AR5K_SREV);
	वापस 0;
पूर्ण

/*
 * Read the MAC address from eeprom or platक्रमm_data
 */
अटल पूर्णांक ath5k_pci_eeprom_पढ़ो_mac(काष्ठा ath5k_hw *ah, u8 *mac)
अणु
	u8 mac_d[ETH_ALEN] = अणुपूर्ण;
	u32 total, offset;
	u16 data;
	पूर्णांक octet;

	AR5K_EEPROM_READ(0x20, data);

	क्रम (offset = 0x1f, octet = 0, total = 0; offset >= 0x1d; offset--) अणु
		AR5K_EEPROM_READ(offset, data);

		total += data;
		mac_d[octet + 1] = data & 0xff;
		mac_d[octet] = data >> 8;
		octet += 2;
	पूर्ण

	अगर (!total || total == 3 * 0xffff)
		वापस -EINVAL;

	स_नकल(mac, mac_d, ETH_ALEN);

	वापस 0;
पूर्ण


/* Common ath_bus_opts काष्ठाure */
अटल स्थिर काष्ठा ath_bus_ops ath_pci_bus_ops = अणु
	.ath_bus_type = ATH_PCI,
	.पढ़ो_cachesize = ath5k_pci_पढ़ो_cachesize,
	.eeprom_पढ़ो = ath5k_pci_eeprom_पढ़ो,
	.eeprom_पढ़ो_mac = ath5k_pci_eeprom_पढ़ो_mac,
पूर्ण;

/********************\
* PCI Initialization *
\********************/

अटल पूर्णांक
ath5k_pci_probe(काष्ठा pci_dev *pdev,
		स्थिर काष्ठा pci_device_id *id)
अणु
	व्योम __iomem *mem;
	काष्ठा ath5k_hw *ah;
	काष्ठा ieee80211_hw *hw;
	पूर्णांक ret;
	u8 csz;

	/*
	 * L0s needs to be disabled on all ath5k cards.
	 *
	 * For distributions shipping with CONFIG_PCIEASPM (this will be enabled
	 * by शेष in the future in 2.6.36) this will also mean both L1 and
	 * L0s will be disabled when a pre 1.1 PCIe device is detected. We करो
	 * know L1 works correctly even क्रम all ath5k pre 1.1 PCIe devices
	 * though but cannot currently undue the effect of a blacklist, क्रम
	 * details you can पढ़ो pcie_aspm_sanity_check() and see how it adjusts
	 * the device link capability.
	 *
	 * It may be possible in the future to implement some PCI API to allow
	 * drivers to override blacklists क्रम pre 1.1 PCIe but क्रम now it is
	 * best to accept that both L0s and L1 will be disabled completely क्रम
	 * distributions shipping with CONFIG_PCIEASPM rather than having this
	 * issue present. Motivation क्रम adding this new API will be to help
	 * with घातer consumption क्रम some of these devices.
	 */
	pci_disable_link_state(pdev, PCIE_LINK_STATE_L0S);

	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "can't enable device\n");
		जाओ err;
	पूर्ण

	/* XXX 32-bit addressing only */
	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(&pdev->dev, "32-bit DMA not available\n");
		जाओ err_dis;
	पूर्ण

	/*
	 * Cache line size is used to size and align various
	 * काष्ठाures used to communicate with the hardware.
	 */
	pci_पढ़ो_config_byte(pdev, PCI_CACHE_LINE_SIZE, &csz);
	अगर (csz == 0) अणु
		/*
		 * Linux 2.4.18 (at least) ग_लिखोs the cache line size
		 * रेजिस्टर as a 16-bit wide रेजिस्टर which is wrong.
		 * We must have this setup properly क्रम rx buffer
		 * DMA to work so क्रमce a reasonable value here अगर it
		 * comes up zero.
		 */
		csz = L1_CACHE_BYTES >> 2;
		pci_ग_लिखो_config_byte(pdev, PCI_CACHE_LINE_SIZE, csz);
	पूर्ण
	/*
	 * The शेष setting of latency समयr yields poor results,
	 * set it to the value used by other प्रणालीs.  It may be worth
	 * tweaking this setting more.
	 */
	pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, 0xa8);

	/* Enable bus mastering */
	pci_set_master(pdev);

	/*
	 * Disable the RETRY_TIMEOUT रेजिस्टर (0x41) to keep
	 * PCI Tx retries from पूर्णांकerfering with C3 CPU state.
	 */
	pci_ग_लिखो_config_byte(pdev, 0x41, 0);

	ret = pci_request_region(pdev, 0, "ath5k");
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot reserve PCI memory region\n");
		जाओ err_dis;
	पूर्ण

	mem = pci_iomap(pdev, 0, 0);
	अगर (!mem) अणु
		dev_err(&pdev->dev, "cannot remap PCI memory region\n");
		ret = -EIO;
		जाओ err_reg;
	पूर्ण

	/*
	 * Allocate hw (mac80211 मुख्य काष्ठा)
	 * and hw->priv (driver निजी data)
	 */
	hw = ieee80211_alloc_hw(माप(*ah), &ath5k_hw_ops);
	अगर (hw == शून्य) अणु
		dev_err(&pdev->dev, "cannot allocate ieee80211_hw\n");
		ret = -ENOMEM;
		जाओ err_map;
	पूर्ण

	dev_info(&pdev->dev, "registered as '%s'\n", wiphy_name(hw->wiphy));

	ah = hw->priv;
	ah->hw = hw;
	ah->pdev = pdev;
	ah->dev = &pdev->dev;
	ah->irq = pdev->irq;
	ah->devid = id->device;
	ah->iobase = mem; /* So we can unmap it on detach */

	/* Initialize */
	ret = ath5k_init_ah(ah, &ath_pci_bus_ops);
	अगर (ret)
		जाओ err_मुक्त;

	/* Set निजी data */
	pci_set_drvdata(pdev, hw);

	वापस 0;
err_मुक्त:
	ieee80211_मुक्त_hw(hw);
err_map:
	pci_iounmap(pdev, mem);
err_reg:
	pci_release_region(pdev, 0);
err_dis:
	pci_disable_device(pdev);
err:
	वापस ret;
पूर्ण

अटल व्योम
ath5k_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ieee80211_hw *hw = pci_get_drvdata(pdev);
	काष्ठा ath5k_hw *ah = hw->priv;

	ath5k_deinit_ah(ah);
	pci_iounmap(pdev, ah->iobase);
	pci_release_region(pdev, 0);
	pci_disable_device(pdev);
	ieee80211_मुक्त_hw(hw);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ath5k_pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा ieee80211_hw *hw = dev_get_drvdata(dev);
	काष्ठा ath5k_hw *ah = hw->priv;

	ath5k_led_off(ah);
	वापस 0;
पूर्ण

अटल पूर्णांक ath5k_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा ieee80211_hw *hw = pci_get_drvdata(pdev);
	काष्ठा ath5k_hw *ah = hw->priv;

	/*
	 * Suspend/Resume resets the PCI configuration space, so we have to
	 * re-disable the RETRY_TIMEOUT रेजिस्टर (0x41) to keep
	 * PCI Tx retries from पूर्णांकerfering with C3 CPU state
	 */
	pci_ग_लिखो_config_byte(pdev, 0x41, 0);

	ath5k_led_enable(ah);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ath5k_pm_ops, ath5k_pci_suspend, ath5k_pci_resume);
#घोषणा ATH5K_PM_OPS	(&ath5k_pm_ops)
#अन्यथा
#घोषणा ATH5K_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा pci_driver ath5k_pci_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= ath5k_pci_id_table,
	.probe		= ath5k_pci_probe,
	.हटाओ		= ath5k_pci_हटाओ,
	.driver.pm	= ATH5K_PM_OPS,
पूर्ण;

module_pci_driver(ath5k_pci_driver);
