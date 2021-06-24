<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AR71xx Reset Controller Driver
 * Author: Alban Bedel
 *
 * Copyright (C) 2015 Alban Bedel <albeu@मुक्त.fr>
 */

#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/reboot.h>

काष्ठा ath79_reset अणु
	काष्ठा reset_controller_dev rcdev;
	काष्ठा notअगरier_block restart_nb;
	व्योम __iomem *base;
	spinlock_t lock;
पूर्ण;

#घोषणा FULL_CHIP_RESET 24

अटल पूर्णांक ath79_reset_update(काष्ठा reset_controller_dev *rcdev,
			अचिन्हित दीर्घ id, bool निश्चित)
अणु
	काष्ठा ath79_reset *ath79_reset =
		container_of(rcdev, काष्ठा ath79_reset, rcdev);
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&ath79_reset->lock, flags);
	val = पढ़ोl(ath79_reset->base);
	अगर (निश्चित)
		val |= BIT(id);
	अन्यथा
		val &= ~BIT(id);
	ग_लिखोl(val, ath79_reset->base);
	spin_unlock_irqrestore(&ath79_reset->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ath79_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			अचिन्हित दीर्घ id)
अणु
	वापस ath79_reset_update(rcdev, id, true);
पूर्ण

अटल पूर्णांक ath79_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	वापस ath79_reset_update(rcdev, id, false);
पूर्ण

अटल पूर्णांक ath79_reset_status(काष्ठा reset_controller_dev *rcdev,
			अचिन्हित दीर्घ id)
अणु
	काष्ठा ath79_reset *ath79_reset =
		container_of(rcdev, काष्ठा ath79_reset, rcdev);
	u32 val;

	val = पढ़ोl(ath79_reset->base);

	वापस !!(val & BIT(id));
पूर्ण

अटल स्थिर काष्ठा reset_control_ops ath79_reset_ops = अणु
	.निश्चित = ath79_reset_निश्चित,
	.deनिश्चित = ath79_reset_deनिश्चित,
	.status = ath79_reset_status,
पूर्ण;

अटल पूर्णांक ath79_reset_restart_handler(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा ath79_reset *ath79_reset =
		container_of(nb, काष्ठा ath79_reset, restart_nb);

	ath79_reset_निश्चित(&ath79_reset->rcdev, FULL_CHIP_RESET);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक ath79_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ath79_reset *ath79_reset;
	काष्ठा resource *res;
	पूर्णांक err;

	ath79_reset = devm_kzalloc(&pdev->dev,
				माप(*ath79_reset), GFP_KERNEL);
	अगर (!ath79_reset)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ath79_reset);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ath79_reset->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(ath79_reset->base))
		वापस PTR_ERR(ath79_reset->base);

	spin_lock_init(&ath79_reset->lock);
	ath79_reset->rcdev.ops = &ath79_reset_ops;
	ath79_reset->rcdev.owner = THIS_MODULE;
	ath79_reset->rcdev.of_node = pdev->dev.of_node;
	ath79_reset->rcdev.of_reset_n_cells = 1;
	ath79_reset->rcdev.nr_resets = 32;

	err = devm_reset_controller_रेजिस्टर(&pdev->dev, &ath79_reset->rcdev);
	अगर (err)
		वापस err;

	ath79_reset->restart_nb.notअगरier_call = ath79_reset_restart_handler;
	ath79_reset->restart_nb.priority = 128;

	err = रेजिस्टर_restart_handler(&ath79_reset->restart_nb);
	अगर (err)
		dev_warn(&pdev->dev, "Failed to register restart handler\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ath79_reset_dt_ids[] = अणु
	अणु .compatible = "qca,ar7100-reset", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver ath79_reset_driver = अणु
	.probe	= ath79_reset_probe,
	.driver = अणु
		.name			= "ath79-reset",
		.of_match_table		= ath79_reset_dt_ids,
		.suppress_bind_attrs	= true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(ath79_reset_driver);
