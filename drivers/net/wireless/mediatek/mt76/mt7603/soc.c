<शैली गुरु>
// SPDX-License-Identअगरier: ISC

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "mt7603.h"

अटल पूर्णांक
mt76_wmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mt7603_dev *dev;
	व्योम __iomem *mem_base;
	काष्ठा mt76_dev *mdev;
	पूर्णांक irq;
	पूर्णांक ret;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	mem_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mem_base))
		वापस PTR_ERR(mem_base);

	mdev = mt76_alloc_device(&pdev->dev, माप(*dev), &mt7603_ops,
				 &mt7603_drv_ops);
	अगर (!mdev)
		वापस -ENOMEM;

	dev = container_of(mdev, काष्ठा mt7603_dev, mt76);
	mt76_mmio_init(mdev, mem_base);

	mdev->rev = (mt76_rr(dev, MT_HW_CHIPID) << 16) |
		    (mt76_rr(dev, MT_HW_REV) & 0xff);
	dev_info(mdev->dev, "ASIC revision: %04x\n", mdev->rev);

	mt76_wr(dev, MT_INT_MASK_CSR, 0);

	ret = devm_request_irq(mdev->dev, irq, mt7603_irq_handler,
			       IRQF_SHARED, KBUILD_MODNAME, dev);
	अगर (ret)
		जाओ error;

	ret = mt7603_रेजिस्टर_device(dev);
	अगर (ret)
		जाओ error;

	वापस 0;
error:
	ieee80211_मुक्त_hw(mt76_hw(dev));
	वापस ret;
पूर्ण

अटल पूर्णांक
mt76_wmac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mt76_dev *mdev = platक्रमm_get_drvdata(pdev);
	काष्ठा mt7603_dev *dev = container_of(mdev, काष्ठा mt7603_dev, mt76);

	mt7603_unरेजिस्टर_device(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_wmac_match[] = अणु
	अणु .compatible = "mediatek,mt7628-wmac" पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, of_wmac_match);
MODULE_FIRMWARE(MT7628_FIRMWARE_E1);
MODULE_FIRMWARE(MT7628_FIRMWARE_E2);

काष्ठा platक्रमm_driver mt76_wmac_driver = अणु
	.probe		= mt76_wmac_probe,
	.हटाओ		= mt76_wmac_हटाओ,
	.driver = अणु
		.name = "mt76_wmac",
		.of_match_table = of_wmac_match,
	पूर्ण,
पूर्ण;
