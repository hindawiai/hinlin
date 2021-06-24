<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * BCM6345 Reset Controller Driver
 *
 * Copyright (C) 2020 थlvaro Fernथँndez Rojas <noltari@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>

#घोषणा BCM6345_RESET_NUM		32
#घोषणा BCM6345_RESET_SLEEP_MIN_US	10000
#घोषणा BCM6345_RESET_SLEEP_MAX_US	20000

काष्ठा bcm6345_reset अणु
	काष्ठा reset_controller_dev rcdev;
	व्योम __iomem *base;
	spinlock_t lock;
पूर्ण;

अटल अंतरभूत काष्ठा bcm6345_reset *
to_bcm6345_reset(काष्ठा reset_controller_dev *rcdev)
अणु
	वापस container_of(rcdev, काष्ठा bcm6345_reset, rcdev);
पूर्ण

अटल पूर्णांक bcm6345_reset_update(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id, bool निश्चित)
अणु
	काष्ठा bcm6345_reset *bcm6345_reset = to_bcm6345_reset(rcdev);
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t val;

	spin_lock_irqsave(&bcm6345_reset->lock, flags);
	val = __raw_पढ़ोl(bcm6345_reset->base);
	अगर (निश्चित)
		val &= ~BIT(id);
	अन्यथा
		val |= BIT(id);
	__raw_ग_लिखोl(val, bcm6345_reset->base);
	spin_unlock_irqrestore(&bcm6345_reset->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm6345_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	वापस bcm6345_reset_update(rcdev, id, true);
पूर्ण

अटल पूर्णांक bcm6345_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				  अचिन्हित दीर्घ id)
अणु
	वापस bcm6345_reset_update(rcdev, id, false);
पूर्ण

अटल पूर्णांक bcm6345_reset_reset(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id)
अणु
	bcm6345_reset_update(rcdev, id, true);
	usleep_range(BCM6345_RESET_SLEEP_MIN_US,
		     BCM6345_RESET_SLEEP_MAX_US);

	bcm6345_reset_update(rcdev, id, false);
	/*
	 * Ensure component is taken out reset state by sleeping also after
	 * deनिश्चितing the reset. Otherwise, the component may not be पढ़ोy
	 * क्रम operation.
	 */
	usleep_range(BCM6345_RESET_SLEEP_MIN_US,
		     BCM6345_RESET_SLEEP_MAX_US);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm6345_reset_status(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	काष्ठा bcm6345_reset *bcm6345_reset = to_bcm6345_reset(rcdev);

	वापस !(__raw_पढ़ोl(bcm6345_reset->base) & BIT(id));
पूर्ण

अटल काष्ठा reset_control_ops bcm6345_reset_ops = अणु
	.निश्चित = bcm6345_reset_निश्चित,
	.deनिश्चित = bcm6345_reset_deनिश्चित,
	.reset = bcm6345_reset_reset,
	.status = bcm6345_reset_status,
पूर्ण;

अटल पूर्णांक bcm6345_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm6345_reset *bcm6345_reset;

	bcm6345_reset = devm_kzalloc(&pdev->dev,
				     माप(*bcm6345_reset), GFP_KERNEL);
	अगर (!bcm6345_reset)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, bcm6345_reset);

	bcm6345_reset->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(bcm6345_reset->base))
		वापस PTR_ERR(bcm6345_reset->base);

	spin_lock_init(&bcm6345_reset->lock);
	bcm6345_reset->rcdev.ops = &bcm6345_reset_ops;
	bcm6345_reset->rcdev.owner = THIS_MODULE;
	bcm6345_reset->rcdev.of_node = pdev->dev.of_node;
	bcm6345_reset->rcdev.of_reset_n_cells = 1;
	bcm6345_reset->rcdev.nr_resets = BCM6345_RESET_NUM;

	वापस devm_reset_controller_रेजिस्टर(&pdev->dev,
					      &bcm6345_reset->rcdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm6345_reset_of_match[] = अणु
	अणु .compatible = "brcm,bcm6345-reset" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver bcm6345_reset_driver = अणु
	.probe = bcm6345_reset_probe,
	.driver	= अणु
		.name = "bcm6345-reset",
		.of_match_table = bcm6345_reset_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(bcm6345_reset_driver);
