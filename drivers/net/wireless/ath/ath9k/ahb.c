<शैली गुरु>
/*
 * Copyright (c) 2008-2011 Atheros Communications Inc.
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

#समावेश <linux/nl80211.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश "ath9k.h"

अटल स्थिर काष्ठा platक्रमm_device_id ath9k_platक्रमm_id_table[] = अणु
	अणु
		.name = "ath9k",
		.driver_data = AR5416_AR9100_DEVID,
	पूर्ण,
	अणु
		.name = "ar933x_wmac",
		.driver_data = AR9300_DEVID_AR9330,
	पूर्ण,
	अणु
		.name = "ar934x_wmac",
		.driver_data = AR9300_DEVID_AR9340,
	पूर्ण,
	अणु
		.name = "qca955x_wmac",
		.driver_data = AR9300_DEVID_QCA955X,
	पूर्ण,
	अणु
		.name = "qca953x_wmac",
		.driver_data = AR9300_DEVID_AR953X,
	पूर्ण,
	अणु
		.name = "qca956x_wmac",
		.driver_data = AR9300_DEVID_QCA956X,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

/* वापस bus cachesize in 4B word units */
अटल व्योम ath_ahb_पढ़ो_cachesize(काष्ठा ath_common *common, पूर्णांक *csz)
अणु
	*csz = L1_CACHE_BYTES >> 2;
पूर्ण

अटल bool ath_ahb_eeprom_पढ़ो(काष्ठा ath_common *common, u32 off, u16 *data)
अणु
	ath_err(common, "%s: eeprom data has to be provided externally\n",
		__func__);
	वापस false;
पूर्ण

अटल स्थिर काष्ठा ath_bus_ops ath_ahb_bus_ops  = अणु
	.ath_bus_type = ATH_AHB,
	.पढ़ो_cachesize = ath_ahb_पढ़ो_cachesize,
	.eeprom_पढ़ो = ath_ahb_eeprom_पढ़ो,
पूर्ण;

अटल पूर्णांक ath_ahb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	व्योम __iomem *mem;
	काष्ठा ath_softc *sc;
	काष्ठा ieee80211_hw *hw;
	काष्ठा resource *res;
	स्थिर काष्ठा platक्रमm_device_id *id = platक्रमm_get_device_id(pdev);
	पूर्णांक irq;
	पूर्णांक ret = 0;
	काष्ठा ath_hw *ah;
	अक्षर hw_name[64];

	अगर (!dev_get_platdata(&pdev->dev)) अणु
		dev_err(&pdev->dev, "no platform data specified\n");
		वापस -EINVAL;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "no memory resource found\n");
		वापस -ENXIO;
	पूर्ण

	mem = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	अगर (mem == शून्य) अणु
		dev_err(&pdev->dev, "ioremap failed\n");
		वापस -ENOMEM;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "no IRQ resource found\n");
		वापस -ENXIO;
	पूर्ण

	irq = res->start;

	ath9k_fill_chanctx_ops();
	hw = ieee80211_alloc_hw(माप(काष्ठा ath_softc), &ath9k_ops);
	अगर (hw == शून्य) अणु
		dev_err(&pdev->dev, "no memory for ieee80211_hw\n");
		वापस -ENOMEM;
	पूर्ण

	SET_IEEE80211_DEV(hw, &pdev->dev);
	platक्रमm_set_drvdata(pdev, hw);

	sc = hw->priv;
	sc->hw = hw;
	sc->dev = &pdev->dev;
	sc->mem = mem;
	sc->irq = irq;

	ret = request_irq(irq, ath_isr, IRQF_SHARED, "ath9k", sc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "request_irq failed\n");
		जाओ err_मुक्त_hw;
	पूर्ण

	ret = ath9k_init_device(id->driver_data, sc, &ath_ahb_bus_ops);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to initialize device\n");
		जाओ err_irq;
	पूर्ण

	ah = sc->sc_ah;
	ath9k_hw_name(ah, hw_name, माप(hw_name));
	wiphy_info(hw->wiphy, "%s mem=0x%lx, irq=%d\n",
		   hw_name, (अचिन्हित दीर्घ)mem, irq);

	वापस 0;

 err_irq:
	मुक्त_irq(irq, sc);
 err_मुक्त_hw:
	ieee80211_मुक्त_hw(hw);
	वापस ret;
पूर्ण

अटल पूर्णांक ath_ahb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ieee80211_hw *hw = platक्रमm_get_drvdata(pdev);

	अगर (hw) अणु
		काष्ठा ath_softc *sc = hw->priv;

		ath9k_deinit_device(sc);
		मुक्त_irq(sc->irq, sc);
		ieee80211_मुक्त_hw(sc->hw);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ath_ahb_driver = अणु
	.probe      = ath_ahb_probe,
	.हटाओ     = ath_ahb_हटाओ,
	.driver		= अणु
		.name	= "ath9k",
	पूर्ण,
	.id_table    = ath9k_platक्रमm_id_table,
पूर्ण;

MODULE_DEVICE_TABLE(platक्रमm, ath9k_platक्रमm_id_table);

पूर्णांक ath_ahb_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&ath_ahb_driver);
पूर्ण

व्योम ath_ahb_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ath_ahb_driver);
पूर्ण
