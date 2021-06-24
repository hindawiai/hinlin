<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Mellanox hotplug driver
 *
 * Copyright (C) 2016-2020 Mellanox Technologies
 */

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_data/mlxreg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/string_helpers.h>
#समावेश <linux/regmap.h>
#समावेश <linux/workqueue.h>

/* Offset of event and mask रेजिस्टरs from status रेजिस्टर. */
#घोषणा MLXREG_HOTPLUG_EVENT_OFF	1
#घोषणा MLXREG_HOTPLUG_MASK_OFF		2
#घोषणा MLXREG_HOTPLUG_AGGR_MASK_OFF	1

/* ASIC good health mask. */
#घोषणा MLXREG_HOTPLUG_GOOD_HEALTH_MASK	0x02

#घोषणा MLXREG_HOTPLUG_ATTRS_MAX	24
#घोषणा MLXREG_HOTPLUG_NOT_ASSERT	3

/**
 * काष्ठा mlxreg_hotplug_priv_data - platक्रमm निजी data:
 * @irq: platक्रमm device पूर्णांकerrupt number;
 * @dev: basic device;
 * @pdev: platक्रमm device;
 * @plat: platक्रमm data;
 * @regmap: रेजिस्टर map handle;
 * @dwork_irq: delayed work ढाँचा;
 * @lock: spin lock;
 * @hwmon: hwmon device;
 * @mlxreg_hotplug_attr: sysfs attributes array;
 * @mlxreg_hotplug_dev_attr: sysfs sensor device attribute array;
 * @group: sysfs attribute group;
 * @groups: list of sysfs attribute group क्रम hwmon registration;
 * @cell: location of top aggregation पूर्णांकerrupt रेजिस्टर;
 * @mask: top aggregation पूर्णांकerrupt common mask;
 * @aggr_cache: last value of aggregation रेजिस्टर status;
 * @after_probe: flag indication probing completion;
 * @not_निश्चितed: number of entries in workqueue with no संकेत निश्चितion;
 */
काष्ठा mlxreg_hotplug_priv_data अणु
	पूर्णांक irq;
	काष्ठा device *dev;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा mlxreg_hotplug_platक्रमm_data *plat;
	काष्ठा regmap *regmap;
	काष्ठा delayed_work dwork_irq;
	spinlock_t lock; /* sync with पूर्णांकerrupt */
	काष्ठा device *hwmon;
	काष्ठा attribute *mlxreg_hotplug_attr[MLXREG_HOTPLUG_ATTRS_MAX + 1];
	काष्ठा sensor_device_attribute_2
			mlxreg_hotplug_dev_attr[MLXREG_HOTPLUG_ATTRS_MAX];
	काष्ठा attribute_group group;
	स्थिर काष्ठा attribute_group *groups[2];
	u32 cell;
	u32 mask;
	u32 aggr_cache;
	bool after_probe;
	u8 not_निश्चितed;
पूर्ण;

/* Environment variables array क्रम udev. */
अटल अक्षर *mlxreg_hotplug_udev_envp[] = अणु शून्य, शून्य पूर्ण;

अटल पूर्णांक
mlxreg_hotplug_udev_event_send(काष्ठा kobject *kobj,
			       काष्ठा mlxreg_core_data *data, bool action)
अणु
	अक्षर event_str[MLXREG_CORE_LABEL_MAX_SIZE + 2];
	अक्षर label[MLXREG_CORE_LABEL_MAX_SIZE] = अणु 0 पूर्ण;

	mlxreg_hotplug_udev_envp[0] = event_str;
	string_upper(label, data->label);
	snम_लिखो(event_str, MLXREG_CORE_LABEL_MAX_SIZE, "%s=%d", label, !!action);

	वापस kobject_uevent_env(kobj, KOBJ_CHANGE, mlxreg_hotplug_udev_envp);
पूर्ण

अटल पूर्णांक mlxreg_hotplug_device_create(काष्ठा mlxreg_hotplug_priv_data *priv,
					काष्ठा mlxreg_core_data *data)
अणु
	काष्ठा mlxreg_core_hotplug_platक्रमm_data *pdata;
	काष्ठा i2c_client *client;

	/* Notअगरy user by sending hwmon uevent. */
	mlxreg_hotplug_udev_event_send(&priv->hwmon->kobj, data, true);

	/*
	 * Return अगर adapter number is negative. It could be in हाल hotplug
	 * event is not associated with hotplug device.
	 */
	अगर (data->hpdev.nr < 0)
		वापस 0;

	pdata = dev_get_platdata(&priv->pdev->dev);
	data->hpdev.adapter = i2c_get_adapter(data->hpdev.nr +
					      pdata->shअगरt_nr);
	अगर (!data->hpdev.adapter) अणु
		dev_err(priv->dev, "Failed to get adapter for bus %d\n",
			data->hpdev.nr + pdata->shअगरt_nr);
		वापस -EFAULT;
	पूर्ण

	client = i2c_new_client_device(data->hpdev.adapter,
				       data->hpdev.brdinfo);
	अगर (IS_ERR(client)) अणु
		dev_err(priv->dev, "Failed to create client %s at bus %d at addr 0x%02x\n",
			data->hpdev.brdinfo->type, data->hpdev.nr +
			pdata->shअगरt_nr, data->hpdev.brdinfo->addr);

		i2c_put_adapter(data->hpdev.adapter);
		data->hpdev.adapter = शून्य;
		वापस PTR_ERR(client);
	पूर्ण

	data->hpdev.client = client;

	वापस 0;
पूर्ण

अटल व्योम
mlxreg_hotplug_device_destroy(काष्ठा mlxreg_hotplug_priv_data *priv,
			      काष्ठा mlxreg_core_data *data)
अणु
	/* Notअगरy user by sending hwmon uevent. */
	mlxreg_hotplug_udev_event_send(&priv->hwmon->kobj, data, false);

	अगर (data->hpdev.client) अणु
		i2c_unरेजिस्टर_device(data->hpdev.client);
		data->hpdev.client = शून्य;
	पूर्ण

	अगर (data->hpdev.adapter) अणु
		i2c_put_adapter(data->hpdev.adapter);
		data->hpdev.adapter = शून्य;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार mlxreg_hotplug_attr_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा mlxreg_hotplug_priv_data *priv = dev_get_drvdata(dev);
	काष्ठा mlxreg_core_hotplug_platक्रमm_data *pdata;
	पूर्णांक index = to_sensor_dev_attr_2(attr)->index;
	पूर्णांक nr = to_sensor_dev_attr_2(attr)->nr;
	काष्ठा mlxreg_core_item *item;
	काष्ठा mlxreg_core_data *data;
	u32 regval;
	पूर्णांक ret;

	pdata = dev_get_platdata(&priv->pdev->dev);
	item = pdata->items + nr;
	data = item->data + index;

	ret = regmap_पढ़ो(priv->regmap, data->reg, &regval);
	अगर (ret)
		वापस ret;

	अगर (item->health) अणु
		regval &= data->mask;
	पूर्ण अन्यथा अणु
		/* Bit = 0 : functional अगर item->inversed is true. */
		अगर (item->inversed)
			regval = !(regval & data->mask);
		अन्यथा
			regval = !!(regval & data->mask);
	पूर्ण

	वापस प्र_लिखो(buf, "%u\n", regval);
पूर्ण

#घोषणा PRIV_ATTR(i) priv->mlxreg_hotplug_attr[i]
#घोषणा PRIV_DEV_ATTR(i) priv->mlxreg_hotplug_dev_attr[i]

अटल पूर्णांक mlxreg_hotplug_attr_init(काष्ठा mlxreg_hotplug_priv_data *priv)
अणु
	काष्ठा mlxreg_core_hotplug_platक्रमm_data *pdata;
	काष्ठा mlxreg_core_item *item;
	काष्ठा mlxreg_core_data *data;
	अचिन्हित दीर्घ mask;
	u32 regval;
	पूर्णांक num_attrs = 0, id = 0, i, j, k, ret;

	pdata = dev_get_platdata(&priv->pdev->dev);
	item = pdata->items;

	/* Go over all kinds of items - psu, pwr, fan. */
	क्रम (i = 0; i < pdata->counter; i++, item++) अणु
		अगर (item->capability) अणु
			/*
			 * Read group capability रेजिस्टर to get actual number
			 * of पूर्णांकerrupt capable components and set group mask
			 * accordingly.
			 */
			ret = regmap_पढ़ो(priv->regmap, item->capability,
					  &regval);
			अगर (ret)
				वापस ret;

			item->mask = GENMASK((regval & item->mask) - 1, 0);
		पूर्ण

		data = item->data;

		/* Go over all unmasked units within item. */
		mask = item->mask;
		k = 0;
		क्रम_each_set_bit(j, &mask, item->count) अणु
			अगर (data->capability) अणु
				/*
				 * Read capability रेजिस्टर and skip non
				 * relevant attributes.
				 */
				ret = regmap_पढ़ो(priv->regmap,
						  data->capability, &regval);
				अगर (ret)
					वापस ret;
				अगर (!(regval & data->bit)) अणु
					data++;
					जारी;
				पूर्ण
			पूर्ण
			PRIV_ATTR(id) = &PRIV_DEV_ATTR(id).dev_attr.attr;
			PRIV_ATTR(id)->name = devm_kaप्र_लिखो(&priv->pdev->dev,
							     GFP_KERNEL,
							     data->label);

			अगर (!PRIV_ATTR(id)->name) अणु
				dev_err(priv->dev, "Memory allocation failed for attr %d.\n",
					id);
				वापस -ENOMEM;
			पूर्ण

			PRIV_DEV_ATTR(id).dev_attr.attr.name =
							PRIV_ATTR(id)->name;
			PRIV_DEV_ATTR(id).dev_attr.attr.mode = 0444;
			PRIV_DEV_ATTR(id).dev_attr.show =
						mlxreg_hotplug_attr_show;
			PRIV_DEV_ATTR(id).nr = i;
			PRIV_DEV_ATTR(id).index = k;
			sysfs_attr_init(&PRIV_DEV_ATTR(id).dev_attr.attr);
			data++;
			id++;
			k++;
		पूर्ण
		num_attrs += k;
	पूर्ण

	priv->group.attrs = devm_kसुस्मृति(&priv->pdev->dev,
					 num_attrs,
					 माप(काष्ठा attribute *),
					 GFP_KERNEL);
	अगर (!priv->group.attrs)
		वापस -ENOMEM;

	priv->group.attrs = priv->mlxreg_hotplug_attr;
	priv->groups[0] = &priv->group;
	priv->groups[1] = शून्य;

	वापस 0;
पूर्ण

अटल व्योम
mlxreg_hotplug_work_helper(काष्ठा mlxreg_hotplug_priv_data *priv,
			   काष्ठा mlxreg_core_item *item)
अणु
	काष्ठा mlxreg_core_data *data;
	अचिन्हित दीर्घ निश्चितed;
	u32 regval, bit;
	पूर्णांक ret;

	/*
	 * Validate अगर item related to received संकेत type is valid.
	 * It should never happen, excepted the situation when some
	 * piece of hardware is broken. In such situation just produce
	 * error message and वापस. Caller must जारी to handle the
	 * संकेतs from other devices अगर any.
	 */
	अगर (unlikely(!item)) अणु
		dev_err(priv->dev, "False signal: at offset:mask 0x%02x:0x%02x.\n",
			item->reg, item->mask);

		वापस;
	पूर्ण

	/* Mask event. */
	ret = regmap_ग_लिखो(priv->regmap, item->reg + MLXREG_HOTPLUG_MASK_OFF,
			   0);
	अगर (ret)
		जाओ out;

	/* Read status. */
	ret = regmap_पढ़ो(priv->regmap, item->reg, &regval);
	अगर (ret)
		जाओ out;

	/* Set निश्चितed bits and save last status. */
	regval &= item->mask;
	निश्चितed = item->cache ^ regval;
	item->cache = regval;

	क्रम_each_set_bit(bit, &निश्चितed, 8) अणु
		data = item->data + bit;
		अगर (regval & BIT(bit)) अणु
			अगर (item->inversed)
				mlxreg_hotplug_device_destroy(priv, data);
			अन्यथा
				mlxreg_hotplug_device_create(priv, data);
		पूर्ण अन्यथा अणु
			अगर (item->inversed)
				mlxreg_hotplug_device_create(priv, data);
			अन्यथा
				mlxreg_hotplug_device_destroy(priv, data);
		पूर्ण
	पूर्ण

	/* Acknowledge event. */
	ret = regmap_ग_लिखो(priv->regmap, item->reg + MLXREG_HOTPLUG_EVENT_OFF,
			   0);
	अगर (ret)
		जाओ out;

	/* Unmask event. */
	ret = regmap_ग_लिखो(priv->regmap, item->reg + MLXREG_HOTPLUG_MASK_OFF,
			   item->mask);

 out:
	अगर (ret)
		dev_err(priv->dev, "Failed to complete workqueue.\n");
पूर्ण

अटल व्योम
mlxreg_hotplug_health_work_helper(काष्ठा mlxreg_hotplug_priv_data *priv,
				  काष्ठा mlxreg_core_item *item)
अणु
	काष्ठा mlxreg_core_data *data = item->data;
	u32 regval;
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < item->count; i++, data++) अणु
		/* Mask event. */
		ret = regmap_ग_लिखो(priv->regmap, data->reg +
				   MLXREG_HOTPLUG_MASK_OFF, 0);
		अगर (ret)
			जाओ out;

		/* Read status. */
		ret = regmap_पढ़ो(priv->regmap, data->reg, &regval);
		अगर (ret)
			जाओ out;

		regval &= data->mask;

		अगर (item->cache == regval)
			जाओ ack_event;

		/*
		 * ASIC health indication is provided through two bits. Bits
		 * value 0x2 indicates that ASIC reached the good health, value
		 * 0x0 indicates ASIC the bad health or करोrmant state and value
		 * 0x3 indicates the booting state. During ASIC reset it should
		 * pass the following states: करोrmant -> booting -> good.
		 */
		अगर (regval == MLXREG_HOTPLUG_GOOD_HEALTH_MASK) अणु
			अगर (!data->attached) अणु
				/*
				 * ASIC is in steady state. Connect associated
				 * device, अगर configured.
				 */
				mlxreg_hotplug_device_create(priv, data);
				data->attached = true;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (data->attached) अणु
				/*
				 * ASIC health is failed after ASIC has been
				 * in steady state. Disconnect associated
				 * device, अगर it has been connected.
				 */
				mlxreg_hotplug_device_destroy(priv, data);
				data->attached = false;
				data->health_cntr = 0;
			पूर्ण
		पूर्ण
		item->cache = regval;
ack_event:
		/* Acknowledge event. */
		ret = regmap_ग_लिखो(priv->regmap, data->reg +
				   MLXREG_HOTPLUG_EVENT_OFF, 0);
		अगर (ret)
			जाओ out;

		/* Unmask event. */
		ret = regmap_ग_लिखो(priv->regmap, data->reg +
				   MLXREG_HOTPLUG_MASK_OFF, data->mask);
		अगर (ret)
			जाओ out;
	पूर्ण

 out:
	अगर (ret)
		dev_err(priv->dev, "Failed to complete workqueue.\n");
पूर्ण

/*
 * mlxreg_hotplug_work_handler - perक्रमms traversing of device पूर्णांकerrupt
 * रेजिस्टरs according to the below hierarchy schema:
 *
 *				Aggregation रेजिस्टरs (status/mask)
 * PSU रेजिस्टरs:		*---*
 * *-----------------*		|   |
 * |status/event/mask|----->    | * |
 * *-----------------*		|   |
 * Power रेजिस्टरs:		|   |
 * *-----------------*		|   |
 * |status/event/mask|----->    | * |
 * *-----------------*		|   |
 * FAN रेजिस्टरs:		|   |--> CPU
 * *-----------------*		|   |
 * |status/event/mask|----->    | * |
 * *-----------------*		|   |
 * ASIC रेजिस्टरs:		|   |
 * *-----------------*		|   |
 * |status/event/mask|----->    | * |
 * *-----------------*		|   |
 *				*---*
 *
 * In हाल some प्रणाली changed are detected: FAN in/out, PSU in/out, घातer
 * cable attached/detached, ASIC health good/bad, relevant device is created
 * or destroyed.
 */
अटल व्योम mlxreg_hotplug_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxreg_core_hotplug_platक्रमm_data *pdata;
	काष्ठा mlxreg_hotplug_priv_data *priv;
	काष्ठा mlxreg_core_item *item;
	u32 regval, aggr_निश्चितed;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, ret;

	priv = container_of(work, काष्ठा mlxreg_hotplug_priv_data,
			    dwork_irq.work);
	pdata = dev_get_platdata(&priv->pdev->dev);
	item = pdata->items;

	/* Mask aggregation event. */
	ret = regmap_ग_लिखो(priv->regmap, pdata->cell +
			   MLXREG_HOTPLUG_AGGR_MASK_OFF, 0);
	अगर (ret < 0)
		जाओ out;

	/* Read aggregation status. */
	ret = regmap_पढ़ो(priv->regmap, pdata->cell, &regval);
	अगर (ret)
		जाओ out;

	regval &= pdata->mask;
	aggr_निश्चितed = priv->aggr_cache ^ regval;
	priv->aggr_cache = regval;

	/*
	 * Handler is invoked, but no निश्चितion is detected at top aggregation
	 * status level. Set aggr_निश्चितed to mask value to allow handler extra
	 * run over all relevant संकेतs to recover any missed संकेत.
	 */
	अगर (priv->not_निश्चितed == MLXREG_HOTPLUG_NOT_ASSERT) अणु
		priv->not_निश्चितed = 0;
		aggr_निश्चितed = pdata->mask;
	पूर्ण
	अगर (!aggr_निश्चितed)
		जाओ unmask_event;

	/* Handle topology and health configuration changes. */
	क्रम (i = 0; i < pdata->counter; i++, item++) अणु
		अगर (aggr_निश्चितed & item->aggr_mask) अणु
			अगर (item->health)
				mlxreg_hotplug_health_work_helper(priv, item);
			अन्यथा
				mlxreg_hotplug_work_helper(priv, item);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);

	/*
	 * It is possible, that some संकेतs have been inserted, जबतक
	 * पूर्णांकerrupt has been masked by mlxreg_hotplug_work_handler. In this
	 * हाल such संकेतs will be missed. In order to handle these संकेतs
	 * delayed work is canceled and work task re-scheduled क्रम immediate
	 * execution. It allows to handle missed संकेतs, अगर any. In other हाल
	 * work handler just validates that no new संकेतs have been received
	 * during masking.
	 */
	cancel_delayed_work(&priv->dwork_irq);
	schedule_delayed_work(&priv->dwork_irq, 0);

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस;

unmask_event:
	priv->not_निश्चितed++;
	/* Unmask aggregation event (no need acknowledge). */
	ret = regmap_ग_लिखो(priv->regmap, pdata->cell +
			   MLXREG_HOTPLUG_AGGR_MASK_OFF, pdata->mask);

 out:
	अगर (ret)
		dev_err(priv->dev, "Failed to complete workqueue.\n");
पूर्ण

अटल पूर्णांक mlxreg_hotplug_set_irq(काष्ठा mlxreg_hotplug_priv_data *priv)
अणु
	काष्ठा mlxreg_core_hotplug_platक्रमm_data *pdata;
	काष्ठा mlxreg_core_item *item;
	काष्ठा mlxreg_core_data *data;
	u32 regval;
	पूर्णांक i, j, ret;

	pdata = dev_get_platdata(&priv->pdev->dev);
	item = pdata->items;

	क्रम (i = 0; i < pdata->counter; i++, item++) अणु
		/* Clear group presense event. */
		ret = regmap_ग_लिखो(priv->regmap, item->reg +
				   MLXREG_HOTPLUG_EVENT_OFF, 0);
		अगर (ret)
			जाओ out;

		/*
		 * Verअगरy अगर hardware configuration requires to disable
		 * पूर्णांकerrupt capability क्रम some of components.
		 */
		data = item->data;
		क्रम (j = 0; j < item->count; j++, data++) अणु
			/* Verअगरy अगर the attribute has capability रेजिस्टर. */
			अगर (data->capability) अणु
				/* Read capability रेजिस्टर. */
				ret = regmap_पढ़ो(priv->regmap,
						  data->capability, &regval);
				अगर (ret)
					जाओ out;

				अगर (!(regval & data->bit))
					item->mask &= ~BIT(j);
			पूर्ण
		पूर्ण

		/* Set group initial status as mask and unmask group event. */
		अगर (item->inversed) अणु
			item->cache = item->mask;
			ret = regmap_ग_लिखो(priv->regmap, item->reg +
					   MLXREG_HOTPLUG_MASK_OFF,
					   item->mask);
			अगर (ret)
				जाओ out;
		पूर्ण
	पूर्ण

	/* Keep aggregation initial status as zero and unmask events. */
	ret = regmap_ग_लिखो(priv->regmap, pdata->cell +
			   MLXREG_HOTPLUG_AGGR_MASK_OFF, pdata->mask);
	अगर (ret)
		जाओ out;

	/* Keep low aggregation initial status as zero and unmask events. */
	अगर (pdata->cell_low) अणु
		ret = regmap_ग_लिखो(priv->regmap, pdata->cell_low +
				   MLXREG_HOTPLUG_AGGR_MASK_OFF,
				   pdata->mask_low);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* Invoke work handler क्रम initializing hot plug devices setting. */
	mlxreg_hotplug_work_handler(&priv->dwork_irq.work);

 out:
	अगर (ret)
		dev_err(priv->dev, "Failed to set interrupts.\n");
	enable_irq(priv->irq);
	वापस ret;
पूर्ण

अटल व्योम mlxreg_hotplug_unset_irq(काष्ठा mlxreg_hotplug_priv_data *priv)
अणु
	काष्ठा mlxreg_core_hotplug_platक्रमm_data *pdata;
	काष्ठा mlxreg_core_item *item;
	काष्ठा mlxreg_core_data *data;
	पूर्णांक count, i, j;

	pdata = dev_get_platdata(&priv->pdev->dev);
	item = pdata->items;
	disable_irq(priv->irq);
	cancel_delayed_work_sync(&priv->dwork_irq);

	/* Mask low aggregation event, अगर defined. */
	अगर (pdata->cell_low)
		regmap_ग_लिखो(priv->regmap, pdata->cell_low +
			     MLXREG_HOTPLUG_AGGR_MASK_OFF, 0);

	/* Mask aggregation event. */
	regmap_ग_लिखो(priv->regmap, pdata->cell + MLXREG_HOTPLUG_AGGR_MASK_OFF,
		     0);

	/* Clear topology configurations. */
	क्रम (i = 0; i < pdata->counter; i++, item++) अणु
		data = item->data;
		/* Mask group presense event. */
		regmap_ग_लिखो(priv->regmap, data->reg + MLXREG_HOTPLUG_MASK_OFF,
			     0);
		/* Clear group presense event. */
		regmap_ग_लिखो(priv->regmap, data->reg +
			     MLXREG_HOTPLUG_EVENT_OFF, 0);

		/* Remove all the attached devices in group. */
		count = item->count;
		क्रम (j = 0; j < count; j++, data++)
			mlxreg_hotplug_device_destroy(priv, data);
	पूर्ण
पूर्ण

अटल irqवापस_t mlxreg_hotplug_irq_handler(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा mlxreg_hotplug_priv_data *priv;

	priv = (काष्ठा mlxreg_hotplug_priv_data *)dev;

	/* Schedule work task क्रम immediate execution.*/
	schedule_delayed_work(&priv->dwork_irq, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mlxreg_hotplug_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mlxreg_core_hotplug_platक्रमm_data *pdata;
	काष्ठा mlxreg_hotplug_priv_data *priv;
	काष्ठा i2c_adapter *deferred_adap;
	पूर्णांक err;

	pdata = dev_get_platdata(&pdev->dev);
	अगर (!pdata) अणु
		dev_err(&pdev->dev, "Failed to get platform data.\n");
		वापस -EINVAL;
	पूर्ण

	/* Defer probing अगर the necessary adapter is not configured yet. */
	deferred_adap = i2c_get_adapter(pdata->deferred_nr);
	अगर (!deferred_adap)
		वापस -EPROBE_DEFER;
	i2c_put_adapter(deferred_adap);

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	अगर (pdata->irq) अणु
		priv->irq = pdata->irq;
	पूर्ण अन्यथा अणु
		priv->irq = platक्रमm_get_irq(pdev, 0);
		अगर (priv->irq < 0)
			वापस priv->irq;
	पूर्ण

	priv->regmap = pdata->regmap;
	priv->dev = pdev->dev.parent;
	priv->pdev = pdev;

	err = devm_request_irq(&pdev->dev, priv->irq,
			       mlxreg_hotplug_irq_handler, IRQF_TRIGGER_FALLING
			       | IRQF_SHARED, "mlxreg-hotplug", priv);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to request irq: %d\n", err);
		वापस err;
	पूर्ण

	disable_irq(priv->irq);
	spin_lock_init(&priv->lock);
	INIT_DELAYED_WORK(&priv->dwork_irq, mlxreg_hotplug_work_handler);
	dev_set_drvdata(&pdev->dev, priv);

	err = mlxreg_hotplug_attr_init(priv);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to allocate attributes: %d\n",
			err);
		वापस err;
	पूर्ण

	priv->hwmon = devm_hwmon_device_रेजिस्टर_with_groups(&pdev->dev,
					"mlxreg_hotplug", priv, priv->groups);
	अगर (IS_ERR(priv->hwmon)) अणु
		dev_err(&pdev->dev, "Failed to register hwmon device %ld\n",
			PTR_ERR(priv->hwmon));
		वापस PTR_ERR(priv->hwmon);
	पूर्ण

	/* Perक्रमm initial पूर्णांकerrupts setup. */
	mlxreg_hotplug_set_irq(priv);
	priv->after_probe = true;

	वापस 0;
पूर्ण

अटल पूर्णांक mlxreg_hotplug_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mlxreg_hotplug_priv_data *priv = dev_get_drvdata(&pdev->dev);

	/* Clean पूर्णांकerrupts setup. */
	mlxreg_hotplug_unset_irq(priv);
	devm_मुक्त_irq(&pdev->dev, priv->irq, priv);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mlxreg_hotplug_driver = अणु
	.driver = अणु
		.name = "mlxreg-hotplug",
	पूर्ण,
	.probe = mlxreg_hotplug_probe,
	.हटाओ = mlxreg_hotplug_हटाओ,
पूर्ण;

module_platक्रमm_driver(mlxreg_hotplug_driver);

MODULE_AUTHOR("Vadim Pasternak <vadimp@mellanox.com>");
MODULE_DESCRIPTION("Mellanox regmap hotplug platform driver");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS("platform:mlxreg-hotplug");
