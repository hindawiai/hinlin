<शैली गुरु>
/*
 * Copyright (c) 2008-2009 Atheros Communications Inc.
 * Copyright (c) 2009 Gabor Juhos <juhosg@खोलोwrt.org>
 * Copyright (c) 2009 Imre Kaloz <kaloz@खोलोwrt.org>
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

#समावेश <linux/module.h>
#समावेश <linux/nl80211.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/etherdevice.h>
#समावेश <ath25_platक्रमm.h>
#समावेश "ath5k.h"
#समावेश "debug.h"
#समावेश "base.h"
#समावेश "reg.h"

/* वापस bus cachesize in 4B word units */
अटल व्योम ath5k_ahb_पढ़ो_cachesize(काष्ठा ath_common *common, पूर्णांक *csz)
अणु
	*csz = L1_CACHE_BYTES >> 2;
पूर्ण

अटल bool
ath5k_ahb_eeprom_पढ़ो(काष्ठा ath_common *common, u32 off, u16 *data)
अणु
	काष्ठा ath5k_hw *ah = common->priv;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(ah->dev);
	काष्ठा ar231x_board_config *bcfg = dev_get_platdata(&pdev->dev);
	u16 *eeprom, *eeprom_end;

	eeprom = (u16 *) bcfg->radio;
	eeprom_end = ((व्योम *) bcfg->config) + BOARD_CONFIG_BUFSZ;

	eeprom += off;
	अगर (eeprom > eeprom_end)
		वापस false;

	*data = *eeprom;
	वापस true;
पूर्ण

पूर्णांक ath5k_hw_पढ़ो_srev(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(ah->dev);
	काष्ठा ar231x_board_config *bcfg = dev_get_platdata(&pdev->dev);
	ah->ah_mac_srev = bcfg->devid;
	वापस 0;
पूर्ण

अटल पूर्णांक ath5k_ahb_eeprom_पढ़ो_mac(काष्ठा ath5k_hw *ah, u8 *mac)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(ah->dev);
	काष्ठा ar231x_board_config *bcfg = dev_get_platdata(&pdev->dev);
	u8 *cfg_mac;

	अगर (to_platक्रमm_device(ah->dev)->id == 0)
		cfg_mac = bcfg->config->wlan0_mac;
	अन्यथा
		cfg_mac = bcfg->config->wlan1_mac;

	स_नकल(mac, cfg_mac, ETH_ALEN);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ath_bus_ops ath_ahb_bus_ops = अणु
	.ath_bus_type = ATH_AHB,
	.पढ़ो_cachesize = ath5k_ahb_पढ़ो_cachesize,
	.eeprom_पढ़ो = ath5k_ahb_eeprom_पढ़ो,
	.eeprom_पढ़ो_mac = ath5k_ahb_eeprom_पढ़ो_mac,
पूर्ण;

/*Initialization*/
अटल पूर्णांक ath_ahb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ar231x_board_config *bcfg = dev_get_platdata(&pdev->dev);
	काष्ठा ath5k_hw *ah;
	काष्ठा ieee80211_hw *hw;
	काष्ठा resource *res;
	व्योम __iomem *mem;
	पूर्णांक irq;
	पूर्णांक ret = 0;
	u32 reg;

	अगर (!dev_get_platdata(&pdev->dev)) अणु
		dev_err(&pdev->dev, "no platform data specified\n");
		ret = -EINVAL;
		जाओ err_out;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "no memory resource found\n");
		ret = -ENXIO;
		जाओ err_out;
	पूर्ण

	mem = ioremap(res->start, resource_size(res));
	अगर (mem == शून्य) अणु
		dev_err(&pdev->dev, "ioremap failed\n");
		ret = -ENOMEM;
		जाओ err_out;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "no IRQ resource found\n");
		ret = -ENXIO;
		जाओ err_iounmap;
	पूर्ण

	irq = res->start;

	hw = ieee80211_alloc_hw(माप(काष्ठा ath5k_hw), &ath5k_hw_ops);
	अगर (hw == शून्य) अणु
		dev_err(&pdev->dev, "no memory for ieee80211_hw\n");
		ret = -ENOMEM;
		जाओ err_iounmap;
	पूर्ण

	ah = hw->priv;
	ah->hw = hw;
	ah->dev = &pdev->dev;
	ah->iobase = mem;
	ah->irq = irq;
	ah->devid = bcfg->devid;

	अगर (bcfg->devid >= AR5K_SREV_AR2315_R6) अणु
		/* Enable WMAC AHB arbitration */
		reg = ioपढ़ो32((व्योम __iomem *) AR5K_AR2315_AHB_ARB_CTL);
		reg |= AR5K_AR2315_AHB_ARB_CTL_WLAN;
		ioग_लिखो32(reg, (व्योम __iomem *) AR5K_AR2315_AHB_ARB_CTL);

		/* Enable global WMAC swapping */
		reg = ioपढ़ो32((व्योम __iomem *) AR5K_AR2315_BYTESWAP);
		reg |= AR5K_AR2315_BYTESWAP_WMAC;
		ioग_लिखो32(reg, (व्योम __iomem *) AR5K_AR2315_BYTESWAP);
	पूर्ण अन्यथा अणु
		/* Enable WMAC DMA access (assuming 5312 or 231x*/
		/* TODO: check other platक्रमms */
		reg = ioपढ़ो32((व्योम __iomem *) AR5K_AR5312_ENABLE);
		अगर (to_platक्रमm_device(ah->dev)->id == 0)
			reg |= AR5K_AR5312_ENABLE_WLAN0;
		अन्यथा
			reg |= AR5K_AR5312_ENABLE_WLAN1;
		ioग_लिखो32(reg, (व्योम __iomem *) AR5K_AR5312_ENABLE);

		/*
		 * On a dual-band AR5312, the multiband radio is only
		 * used as pass-through. Disable 2 GHz support in the
		 * driver क्रम it
		 */
		अगर (to_platक्रमm_device(ah->dev)->id == 0 &&
		    (bcfg->config->flags & (BD_WLAN0 | BD_WLAN1)) ==
		     (BD_WLAN1 | BD_WLAN0))
			ah->ah_capabilities.cap_needs_2GHz_ovr = true;
		अन्यथा
			ah->ah_capabilities.cap_needs_2GHz_ovr = false;
	पूर्ण

	ret = ath5k_init_ah(ah, &ath_ahb_bus_ops);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "failed to attach device, err=%d\n", ret);
		ret = -ENODEV;
		जाओ err_मुक्त_hw;
	पूर्ण

	platक्रमm_set_drvdata(pdev, hw);

	वापस 0;

 err_मुक्त_hw:
	ieee80211_मुक्त_hw(hw);
 err_iounmap:
        iounmap(mem);
 err_out:
	वापस ret;
पूर्ण

अटल पूर्णांक ath_ahb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ar231x_board_config *bcfg = dev_get_platdata(&pdev->dev);
	काष्ठा ieee80211_hw *hw = platक्रमm_get_drvdata(pdev);
	काष्ठा ath5k_hw *ah;
	u32 reg;

	अगर (!hw)
		वापस 0;

	ah = hw->priv;

	अगर (bcfg->devid >= AR5K_SREV_AR2315_R6) अणु
		/* Disable WMAC AHB arbitration */
		reg = ioपढ़ो32((व्योम __iomem *) AR5K_AR2315_AHB_ARB_CTL);
		reg &= ~AR5K_AR2315_AHB_ARB_CTL_WLAN;
		ioग_लिखो32(reg, (व्योम __iomem *) AR5K_AR2315_AHB_ARB_CTL);
	पूर्ण अन्यथा अणु
		/*Stop DMA access */
		reg = ioपढ़ो32((व्योम __iomem *) AR5K_AR5312_ENABLE);
		अगर (to_platक्रमm_device(ah->dev)->id == 0)
			reg &= ~AR5K_AR5312_ENABLE_WLAN0;
		अन्यथा
			reg &= ~AR5K_AR5312_ENABLE_WLAN1;
		ioग_लिखो32(reg, (व्योम __iomem *) AR5K_AR5312_ENABLE);
	पूर्ण

	ath5k_deinit_ah(ah);
	iounmap(ah->iobase);
	ieee80211_मुक्त_hw(hw);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ath_ahb_driver = अणु
	.probe      = ath_ahb_probe,
	.हटाओ     = ath_ahb_हटाओ,
	.driver		= अणु
		.name	= "ar231x-wmac",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ath_ahb_driver);
