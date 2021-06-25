<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  R-Car THS/TSC thermal sensor driver
 *
 * Copyright (C) 2012 Renesas Solutions Corp.
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reboot.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/thermal.h>

#समावेश "thermal_hwmon.h"

#घोषणा IDLE_INTERVAL	5000

#घोषणा COMMON_STR	0x00
#घोषणा COMMON_ENR	0x04
#घोषणा COMMON_INTMSK	0x0c

#घोषणा REG_POSNEG	0x20
#घोषणा REG_FILONOFF	0x28
#घोषणा REG_THSCR	0x2c
#घोषणा REG_THSSR	0x30
#घोषणा REG_INTCTRL	0x34

/* THSCR */
#घोषणा CPCTL	(1 << 12)

/* THSSR */
#घोषणा CTEMP	0x3f

काष्ठा rcar_thermal_common अणु
	व्योम __iomem *base;
	काष्ठा device *dev;
	काष्ठा list_head head;
	spinlock_t lock;
पूर्ण;

काष्ठा rcar_thermal_chip अणु
	अचिन्हित पूर्णांक use_of_thermal : 1;
	अचिन्हित पूर्णांक has_filonoff : 1;
	अचिन्हित पूर्णांक irq_per_ch : 1;
	अचिन्हित पूर्णांक needs_suspend_resume : 1;
	अचिन्हित पूर्णांक nirqs;
	अचिन्हित पूर्णांक ctemp_bands;
पूर्ण;

अटल स्थिर काष्ठा rcar_thermal_chip rcar_thermal = अणु
	.use_of_thermal = 0,
	.has_filonoff = 1,
	.irq_per_ch = 0,
	.needs_suspend_resume = 0,
	.nirqs = 1,
	.ctemp_bands = 1,
पूर्ण;

अटल स्थिर काष्ठा rcar_thermal_chip rcar_gen2_thermal = अणु
	.use_of_thermal = 1,
	.has_filonoff = 1,
	.irq_per_ch = 0,
	.needs_suspend_resume = 0,
	.nirqs = 1,
	.ctemp_bands = 1,
पूर्ण;

अटल स्थिर काष्ठा rcar_thermal_chip rcar_gen3_thermal = अणु
	.use_of_thermal = 1,
	.has_filonoff = 0,
	.irq_per_ch = 1,
	.needs_suspend_resume = 1,
	/*
	 * The Gen3 chip has 3 पूर्णांकerrupts, but this driver uses only 2
	 * पूर्णांकerrupts to detect a temperature change, rise or fall.
	 */
	.nirqs = 2,
	.ctemp_bands = 2,
पूर्ण;

काष्ठा rcar_thermal_priv अणु
	व्योम __iomem *base;
	काष्ठा rcar_thermal_common *common;
	काष्ठा thermal_zone_device *zone;
	स्थिर काष्ठा rcar_thermal_chip *chip;
	काष्ठा delayed_work work;
	काष्ठा mutex lock;
	काष्ठा list_head list;
	पूर्णांक id;
पूर्ण;

#घोषणा rcar_thermal_क्रम_each_priv(pos, common)	\
	list_क्रम_each_entry(pos, &common->head, list)

#घोषणा MCELSIUS(temp)			((temp) * 1000)
#घोषणा rcar_zone_to_priv(zone)		((zone)->devdata)
#घोषणा rcar_priv_to_dev(priv)		((priv)->common->dev)
#घोषणा rcar_has_irq_support(priv)	((priv)->common->base)
#घोषणा rcar_id_to_shअगरt(priv)		((priv)->id * 8)

अटल स्थिर काष्ठा of_device_id rcar_thermal_dt_ids[] = अणु
	अणु
		.compatible = "renesas,rcar-thermal",
		.data = &rcar_thermal,
	पूर्ण,
	अणु
		.compatible = "renesas,rcar-gen2-thermal",
		 .data = &rcar_gen2_thermal,
	पूर्ण,
	अणु
		.compatible = "renesas,thermal-r8a774c0",
		.data = &rcar_gen3_thermal,
	पूर्ण,
	अणु
		.compatible = "renesas,thermal-r8a77970",
		.data = &rcar_gen3_thermal,
	पूर्ण,
	अणु
		.compatible = "renesas,thermal-r8a77990",
		.data = &rcar_gen3_thermal,
	पूर्ण,
	अणु
		.compatible = "renesas,thermal-r8a77995",
		.data = &rcar_gen3_thermal,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rcar_thermal_dt_ids);

/*
 *		basic functions
 */
#घोषणा rcar_thermal_common_पढ़ो(c, r) \
	_rcar_thermal_common_पढ़ो(c, COMMON_ ##r)
अटल u32 _rcar_thermal_common_पढ़ो(काष्ठा rcar_thermal_common *common,
				     u32 reg)
अणु
	वापस ioपढ़ो32(common->base + reg);
पूर्ण

#घोषणा rcar_thermal_common_ग_लिखो(c, r, d) \
	_rcar_thermal_common_ग_लिखो(c, COMMON_ ##r, d)
अटल व्योम _rcar_thermal_common_ग_लिखो(काष्ठा rcar_thermal_common *common,
				       u32 reg, u32 data)
अणु
	ioग_लिखो32(data, common->base + reg);
पूर्ण

#घोषणा rcar_thermal_common_bset(c, r, m, d) \
	_rcar_thermal_common_bset(c, COMMON_ ##r, m, d)
अटल व्योम _rcar_thermal_common_bset(काष्ठा rcar_thermal_common *common,
				      u32 reg, u32 mask, u32 data)
अणु
	u32 val;

	val = ioपढ़ो32(common->base + reg);
	val &= ~mask;
	val |= (data & mask);
	ioग_लिखो32(val, common->base + reg);
पूर्ण

#घोषणा rcar_thermal_पढ़ो(p, r) _rcar_thermal_पढ़ो(p, REG_ ##r)
अटल u32 _rcar_thermal_पढ़ो(काष्ठा rcar_thermal_priv *priv, u32 reg)
अणु
	वापस ioपढ़ो32(priv->base + reg);
पूर्ण

#घोषणा rcar_thermal_ग_लिखो(p, r, d) _rcar_thermal_ग_लिखो(p, REG_ ##r, d)
अटल व्योम _rcar_thermal_ग_लिखो(काष्ठा rcar_thermal_priv *priv,
				u32 reg, u32 data)
अणु
	ioग_लिखो32(data, priv->base + reg);
पूर्ण

#घोषणा rcar_thermal_bset(p, r, m, d) _rcar_thermal_bset(p, REG_ ##r, m, d)
अटल व्योम _rcar_thermal_bset(काष्ठा rcar_thermal_priv *priv, u32 reg,
			       u32 mask, u32 data)
अणु
	u32 val;

	val = ioपढ़ो32(priv->base + reg);
	val &= ~mask;
	val |= (data & mask);
	ioग_लिखो32(val, priv->base + reg);
पूर्ण

/*
 *		zone device functions
 */
अटल पूर्णांक rcar_thermal_update_temp(काष्ठा rcar_thermal_priv *priv)
अणु
	काष्ठा device *dev = rcar_priv_to_dev(priv);
	पूर्णांक old, new, ctemp = -EINVAL;
	अचिन्हित पूर्णांक i;

	mutex_lock(&priv->lock);

	/*
	 * TSC decides a value of CPTAP स्वतःmatically,
	 * and this is the conditions which validate पूर्णांकerrupt.
	 */
	rcar_thermal_bset(priv, THSCR, CPCTL, CPCTL);

	old = ~0;
	क्रम (i = 0; i < 128; i++) अणु
		/*
		 * we need to रुको 300us after changing comparator offset
		 * to get stable temperature.
		 * see "Usage Notes" on datasheet
		 */
		usleep_range(300, 400);

		new = rcar_thermal_पढ़ो(priv, THSSR) & CTEMP;
		अगर (new == old) अणु
			ctemp = new;
			अवरोध;
		पूर्ण
		old = new;
	पूर्ण

	अगर (ctemp < 0) अणु
		dev_err(dev, "thermal sensor was broken\n");
		जाओ err_out_unlock;
	पूर्ण

	/*
	 * enable IRQ
	 */
	अगर (rcar_has_irq_support(priv)) अणु
		अगर (priv->chip->has_filonoff)
			rcar_thermal_ग_लिखो(priv, FILONOFF, 0);

		/* enable Rising/Falling edge पूर्णांकerrupt */
		rcar_thermal_ग_लिखो(priv, POSNEG,  0x1);
		rcar_thermal_ग_लिखो(priv, INTCTRL, (((ctemp - 0) << 8) |
						   ((ctemp - 1) << 0)));
	पूर्ण

err_out_unlock:
	mutex_unlock(&priv->lock);

	वापस ctemp;
पूर्ण

अटल पूर्णांक rcar_thermal_get_current_temp(काष्ठा rcar_thermal_priv *priv,
					 पूर्णांक *temp)
अणु
	पूर्णांक ctemp;

	ctemp = rcar_thermal_update_temp(priv);
	अगर (ctemp < 0)
		वापस ctemp;

	/* Guaranteed operating range is -45C to 125C. */

	अगर (priv->chip->ctemp_bands == 1)
		*temp = MCELSIUS((ctemp * 5) - 65);
	अन्यथा अगर (ctemp < 24)
		*temp = MCELSIUS(((ctemp * 55) - 720) / 10);
	अन्यथा
		*temp = MCELSIUS((ctemp * 5) - 60);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_thermal_of_get_temp(व्योम *data, पूर्णांक *temp)
अणु
	काष्ठा rcar_thermal_priv *priv = data;

	वापस rcar_thermal_get_current_temp(priv, temp);
पूर्ण

अटल पूर्णांक rcar_thermal_get_temp(काष्ठा thermal_zone_device *zone, पूर्णांक *temp)
अणु
	काष्ठा rcar_thermal_priv *priv = rcar_zone_to_priv(zone);

	वापस rcar_thermal_get_current_temp(priv, temp);
पूर्ण

अटल पूर्णांक rcar_thermal_get_trip_type(काष्ठा thermal_zone_device *zone,
				      पूर्णांक trip, क्रमागत thermal_trip_type *type)
अणु
	काष्ठा rcar_thermal_priv *priv = rcar_zone_to_priv(zone);
	काष्ठा device *dev = rcar_priv_to_dev(priv);

	/* see rcar_thermal_get_temp() */
	चयन (trip) अणु
	हाल 0: /* +90 <= temp */
		*type = THERMAL_TRIP_CRITICAL;
		अवरोध;
	शेष:
		dev_err(dev, "rcar driver trip error\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_thermal_get_trip_temp(काष्ठा thermal_zone_device *zone,
				      पूर्णांक trip, पूर्णांक *temp)
अणु
	काष्ठा rcar_thermal_priv *priv = rcar_zone_to_priv(zone);
	काष्ठा device *dev = rcar_priv_to_dev(priv);

	/* see rcar_thermal_get_temp() */
	चयन (trip) अणु
	हाल 0: /* +90 <= temp */
		*temp = MCELSIUS(90);
		अवरोध;
	शेष:
		dev_err(dev, "rcar driver trip error\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops rcar_thermal_zone_of_ops = अणु
	.get_temp	= rcar_thermal_of_get_temp,
पूर्ण;

अटल काष्ठा thermal_zone_device_ops rcar_thermal_zone_ops = अणु
	.get_temp	= rcar_thermal_get_temp,
	.get_trip_type	= rcar_thermal_get_trip_type,
	.get_trip_temp	= rcar_thermal_get_trip_temp,
पूर्ण;

/*
 *		पूर्णांकerrupt
 */
#घोषणा rcar_thermal_irq_enable(p)	_rcar_thermal_irq_ctrl(p, 1)
#घोषणा rcar_thermal_irq_disable(p)	_rcar_thermal_irq_ctrl(p, 0)
अटल व्योम _rcar_thermal_irq_ctrl(काष्ठा rcar_thermal_priv *priv, पूर्णांक enable)
अणु
	काष्ठा rcar_thermal_common *common = priv->common;
	अचिन्हित दीर्घ flags;
	u32 mask = 0x3 << rcar_id_to_shअगरt(priv); /* enable Rising/Falling */

	अगर (!rcar_has_irq_support(priv))
		वापस;

	spin_lock_irqsave(&common->lock, flags);

	rcar_thermal_common_bset(common, INTMSK, mask, enable ? 0 : mask);

	spin_unlock_irqrestore(&common->lock, flags);
पूर्ण

अटल व्योम rcar_thermal_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rcar_thermal_priv *priv;
	पूर्णांक ret;

	priv = container_of(work, काष्ठा rcar_thermal_priv, work.work);

	ret = rcar_thermal_update_temp(priv);
	अगर (ret < 0)
		वापस;

	rcar_thermal_irq_enable(priv);

	thermal_zone_device_update(priv->zone, THERMAL_EVENT_UNSPECIFIED);
पूर्ण

अटल u32 rcar_thermal_had_changed(काष्ठा rcar_thermal_priv *priv, u32 status)
अणु
	काष्ठा device *dev = rcar_priv_to_dev(priv);

	status = (status >> rcar_id_to_shअगरt(priv)) & 0x3;

	अगर (status) अणु
		dev_dbg(dev, "thermal%d %s%s\n",
			priv->id,
			(status & 0x2) ? "Rising " : "",
			(status & 0x1) ? "Falling" : "");
	पूर्ण

	वापस status;
पूर्ण

अटल irqवापस_t rcar_thermal_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rcar_thermal_common *common = data;
	काष्ठा rcar_thermal_priv *priv;
	u32 status, mask;

	spin_lock(&common->lock);

	mask	= rcar_thermal_common_पढ़ो(common, INTMSK);
	status	= rcar_thermal_common_पढ़ो(common, STR);
	rcar_thermal_common_ग_लिखो(common, STR, 0x000F0F0F & mask);

	spin_unlock(&common->lock);

	status = status & ~mask;

	/*
	 * check the status
	 */
	rcar_thermal_क्रम_each_priv(priv, common) अणु
		अगर (rcar_thermal_had_changed(priv, status)) अणु
			rcar_thermal_irq_disable(priv);
			queue_delayed_work(प्रणाली_मुक्तzable_wq, &priv->work,
					   msecs_to_jअगरfies(300));
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 *		platक्रमm functions
 */
अटल पूर्णांक rcar_thermal_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_thermal_common *common = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rcar_thermal_priv *priv;

	rcar_thermal_क्रम_each_priv(priv, common) अणु
		rcar_thermal_irq_disable(priv);
		cancel_delayed_work_sync(&priv->work);
		अगर (priv->chip->use_of_thermal)
			thermal_हटाओ_hwmon_sysfs(priv->zone);
		अन्यथा
			thermal_zone_device_unरेजिस्टर(priv->zone);
	पूर्ण

	pm_runसमय_put(dev);
	pm_runसमय_disable(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_thermal_common *common;
	काष्ठा rcar_thermal_priv *priv;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res, *irq;
	स्थिर काष्ठा rcar_thermal_chip *chip = of_device_get_match_data(dev);
	पूर्णांक mres = 0;
	पूर्णांक i;
	पूर्णांक ret = -ENODEV;
	पूर्णांक idle = IDLE_INTERVAL;
	u32 enr_bits = 0;

	common = devm_kzalloc(dev, माप(*common), GFP_KERNEL);
	अगर (!common)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, common);

	INIT_LIST_HEAD(&common->head);
	spin_lock_init(&common->lock);
	common->dev = dev;

	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);

	क्रम (i = 0; i < chip->nirqs; i++) अणु
		irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, i);
		अगर (!irq)
			जारी;
		अगर (!common->base) अणु
			/*
			 * platक्रमm has IRQ support.
			 * Then, driver uses common रेजिस्टरs
			 * rcar_has_irq_support() will be enabled
			 */
			res = platक्रमm_get_resource(pdev, IORESOURCE_MEM,
						    mres++);
			common->base = devm_ioremap_resource(dev, res);
			अगर (IS_ERR(common->base)) अणु
				ret = PTR_ERR(common->base);
				जाओ error_unरेजिस्टर;
			पूर्ण

			idle = 0; /* polling delay is not needed */
		पूर्ण

		ret = devm_request_irq(dev, irq->start, rcar_thermal_irq,
				       IRQF_SHARED, dev_name(dev), common);
		अगर (ret) अणु
			dev_err(dev, "irq request failed\n ");
			जाओ error_unरेजिस्टर;
		पूर्ण

		/* update ENR bits */
		अगर (chip->irq_per_ch)
			enr_bits |= 1 << i;
	पूर्ण

	क्रम (i = 0;; i++) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, mres++);
		अगर (!res)
			अवरोध;

		priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
		अगर (!priv) अणु
			ret = -ENOMEM;
			जाओ error_unरेजिस्टर;
		पूर्ण

		priv->base = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(priv->base)) अणु
			ret = PTR_ERR(priv->base);
			जाओ error_unरेजिस्टर;
		पूर्ण

		priv->common = common;
		priv->id = i;
		priv->chip = chip;
		mutex_init(&priv->lock);
		INIT_LIST_HEAD(&priv->list);
		INIT_DELAYED_WORK(&priv->work, rcar_thermal_work);
		ret = rcar_thermal_update_temp(priv);
		अगर (ret < 0)
			जाओ error_unरेजिस्टर;

		अगर (chip->use_of_thermal) अणु
			priv->zone = devm_thermal_zone_of_sensor_रेजिस्टर(
						dev, i, priv,
						&rcar_thermal_zone_of_ops);
		पूर्ण अन्यथा अणु
			priv->zone = thermal_zone_device_रेजिस्टर(
						"rcar_thermal",
						1, 0, priv,
						&rcar_thermal_zone_ops, शून्य, 0,
						idle);

			ret = thermal_zone_device_enable(priv->zone);
			अगर (ret) अणु
				thermal_zone_device_unरेजिस्टर(priv->zone);
				priv->zone = ERR_PTR(ret);
			पूर्ण
		पूर्ण
		अगर (IS_ERR(priv->zone)) अणु
			dev_err(dev, "can't register thermal zone\n");
			ret = PTR_ERR(priv->zone);
			priv->zone = शून्य;
			जाओ error_unरेजिस्टर;
		पूर्ण

		अगर (chip->use_of_thermal) अणु
			/*
			 * thermal_zone करोesn't enable hwmon as शेष,
			 * but, enable it here to keep compatible
			 */
			priv->zone->tzp->no_hwmon = false;
			ret = thermal_add_hwmon_sysfs(priv->zone);
			अगर (ret)
				जाओ error_unरेजिस्टर;
		पूर्ण

		rcar_thermal_irq_enable(priv);

		list_move_tail(&priv->list, &common->head);

		/* update ENR bits */
		अगर (!chip->irq_per_ch)
			enr_bits |= 3 << (i * 8);
	पूर्ण

	अगर (common->base && enr_bits)
		rcar_thermal_common_ग_लिखो(common, ENR, enr_bits);

	dev_info(dev, "%d sensor probed\n", i);

	वापस 0;

error_unरेजिस्टर:
	rcar_thermal_हटाओ(pdev);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rcar_thermal_suspend(काष्ठा device *dev)
अणु
	काष्ठा rcar_thermal_common *common = dev_get_drvdata(dev);
	काष्ठा rcar_thermal_priv *priv = list_first_entry(&common->head,
							  typeof(*priv), list);

	अगर (priv->chip->needs_suspend_resume) अणु
		rcar_thermal_common_ग_लिखो(common, ENR, 0);
		rcar_thermal_irq_disable(priv);
		rcar_thermal_bset(priv, THSCR, CPCTL, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_thermal_resume(काष्ठा device *dev)
अणु
	काष्ठा rcar_thermal_common *common = dev_get_drvdata(dev);
	काष्ठा rcar_thermal_priv *priv = list_first_entry(&common->head,
							  typeof(*priv), list);
	पूर्णांक ret;

	अगर (priv->chip->needs_suspend_resume) अणु
		ret = rcar_thermal_update_temp(priv);
		अगर (ret < 0)
			वापस ret;
		rcar_thermal_irq_enable(priv);
		rcar_thermal_common_ग_लिखो(common, ENR, 0x03);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(rcar_thermal_pm_ops, rcar_thermal_suspend,
			 rcar_thermal_resume);

अटल काष्ठा platक्रमm_driver rcar_thermal_driver = अणु
	.driver	= अणु
		.name	= "rcar_thermal",
		.pm = &rcar_thermal_pm_ops,
		.of_match_table = rcar_thermal_dt_ids,
	पूर्ण,
	.probe		= rcar_thermal_probe,
	.हटाओ		= rcar_thermal_हटाओ,
पूर्ण;
module_platक्रमm_driver(rcar_thermal_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("R-Car THS/TSC thermal sensor driver");
MODULE_AUTHOR("Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>");
