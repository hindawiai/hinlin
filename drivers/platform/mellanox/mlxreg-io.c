<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Mellanox रेजिस्टर access driver
 *
 * Copyright (C) 2018 Mellanox Technologies
 * Copyright (C) 2018 Vadim Pasternak <vadimp@mellanox.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_data/mlxreg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

/* Attribute parameters. */
#घोषणा MLXREG_IO_ATT_SIZE	10
#घोषणा MLXREG_IO_ATT_NUM	48

/**
 * काष्ठा mlxreg_io_priv_data - driver's निजी data:
 *
 * @pdev: platक्रमm device;
 * @pdata: platक्रमm data;
 * @hwmon: hwmon device;
 * @mlxreg_io_attr: sysfs attributes array;
 * @mlxreg_io_dev_attr: sysfs sensor device attribute array;
 * @group: sysfs attribute group;
 * @groups: list of sysfs attribute group क्रम hwmon registration;
 * @regsize: size of a रेजिस्टर value;
 */
काष्ठा mlxreg_io_priv_data अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा mlxreg_core_platक्रमm_data *pdata;
	काष्ठा device *hwmon;
	काष्ठा attribute *mlxreg_io_attr[MLXREG_IO_ATT_NUM + 1];
	काष्ठा sensor_device_attribute mlxreg_io_dev_attr[MLXREG_IO_ATT_NUM];
	काष्ठा attribute_group group;
	स्थिर काष्ठा attribute_group *groups[2];
	पूर्णांक regsize;
पूर्ण;

अटल पूर्णांक
mlxreg_io_get_reg(व्योम *regmap, काष्ठा mlxreg_core_data *data, u32 in_val,
		  bool rw_flag, पूर्णांक regsize, u32 *regval)
अणु
	पूर्णांक i, val, ret;

	ret = regmap_पढ़ो(regmap, data->reg, regval);
	अगर (ret)
		जाओ access_error;

	/*
	 * There are four kinds of attributes: single bit, full रेजिस्टर's
	 * bits, bit sequence, bits in few रेजिस्टरs For the first kind field
	 * mask indicates which bits are not related and field bit is set zero.
	 * For the second kind field mask is set to zero and field bit is set
	 * with all bits one. No special handling क्रम such kind of attributes -
	 * pass value as is. For the third kind, the field mask indicates which
	 * bits are related and the field bit is set to the first bit number
	 * (from 1 to 32) is the bit sequence. For the fourth kind - the number
	 * of रेजिस्टरs which should be पढ़ो क्रम getting an attribute are
	 * specअगरied through 'data->regnum' field.
	 */
	अगर (!data->bit) अणु
		/* Single bit. */
		अगर (rw_flag) अणु
			/* For show: expose effective bit value as 0 or 1. */
			*regval = !!(*regval & ~data->mask);
		पूर्ण अन्यथा अणु
			/* For store: set effective bit value. */
			*regval &= data->mask;
			अगर (in_val)
				*regval |= ~data->mask;
		पूर्ण
	पूर्ण अन्यथा अगर (data->mask) अणु
		/* Bit sequence. */
		अगर (rw_flag) अणु
			/* For show: mask and shअगरt right. */
			*regval = ror32(*regval & data->mask, (data->bit - 1));
		पूर्ण अन्यथा अणु
			/* For store: shअगरt to the position and mask. */
			in_val = rol32(in_val, data->bit - 1) & data->mask;
			/* Clear relevant bits and set them to new value. */
			*regval = (*regval & ~data->mask) | in_val;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Some attributes could occupied few रेजिस्टरs in हाल regmap
		 * bit size is 8 or 16. Compose such attributes from 'regnum'
		 * रेजिस्टरs. Such attributes contain पढ़ो-only data.
		 */
		क्रम (i = 1; i < data->regnum; i++) अणु
			ret = regmap_पढ़ो(regmap, data->reg + i, &val);
			अगर (ret)
				जाओ access_error;

			*regval |= rol32(val, regsize * i);
		पूर्ण
	पूर्ण

access_error:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
mlxreg_io_attr_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    अक्षर *buf)
अणु
	काष्ठा mlxreg_io_priv_data *priv = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	काष्ठा mlxreg_core_data *data = priv->pdata->data + index;
	u32 regval = 0;
	पूर्णांक ret;

	ret = mlxreg_io_get_reg(priv->pdata->regmap, data, 0, true,
				priv->regsize, &regval);
	अगर (ret)
		जाओ access_error;

	वापस प्र_लिखो(buf, "%u\n", regval);

access_error:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
mlxreg_io_attr_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा mlxreg_io_priv_data *priv = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	काष्ठा mlxreg_core_data *data = priv->pdata->data + index;
	u32 input_val, regval;
	पूर्णांक ret;

	अगर (len > MLXREG_IO_ATT_SIZE)
		वापस -EINVAL;

	/* Convert buffer to input value. */
	ret = kstrtou32(buf, len, &input_val);
	अगर (ret)
		वापस ret;

	ret = mlxreg_io_get_reg(priv->pdata->regmap, data, input_val, false,
				priv->regsize, &regval);
	अगर (ret)
		जाओ access_error;

	ret = regmap_ग_लिखो(priv->pdata->regmap, data->reg, regval);
	अगर (ret)
		जाओ access_error;

	वापस len;

access_error:
	dev_err(&priv->pdev->dev, "Bus access error\n");
	वापस ret;
पूर्ण

अटल काष्ठा device_attribute mlxreg_io_devattr_rw = अणु
	.show	= mlxreg_io_attr_show,
	.store	= mlxreg_io_attr_store,
पूर्ण;

अटल पूर्णांक mlxreg_io_attr_init(काष्ठा mlxreg_io_priv_data *priv)
अणु
	पूर्णांक i;

	priv->group.attrs = devm_kसुस्मृति(&priv->pdev->dev,
					 priv->pdata->counter,
					 माप(काष्ठा attribute *),
					 GFP_KERNEL);
	अगर (!priv->group.attrs)
		वापस -ENOMEM;

	क्रम (i = 0; i < priv->pdata->counter; i++) अणु
		priv->mlxreg_io_attr[i] =
				&priv->mlxreg_io_dev_attr[i].dev_attr.attr;
		स_नकल(&priv->mlxreg_io_dev_attr[i].dev_attr,
		       &mlxreg_io_devattr_rw, माप(काष्ठा device_attribute));

		/* Set attribute name as a label. */
		priv->mlxreg_io_attr[i]->name =
				devm_kaप्र_लिखो(&priv->pdev->dev, GFP_KERNEL,
					       priv->pdata->data[i].label);

		अगर (!priv->mlxreg_io_attr[i]->name) अणु
			dev_err(&priv->pdev->dev, "Memory allocation failed for sysfs attribute %d.\n",
				i + 1);
			वापस -ENOMEM;
		पूर्ण

		priv->mlxreg_io_dev_attr[i].dev_attr.attr.mode =
						priv->pdata->data[i].mode;
		priv->mlxreg_io_dev_attr[i].dev_attr.attr.name =
					priv->mlxreg_io_attr[i]->name;
		priv->mlxreg_io_dev_attr[i].index = i;
		sysfs_attr_init(&priv->mlxreg_io_dev_attr[i].dev_attr.attr);
	पूर्ण

	priv->group.attrs = priv->mlxreg_io_attr;
	priv->groups[0] = &priv->group;
	priv->groups[1] = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक mlxreg_io_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mlxreg_io_priv_data *priv;
	पूर्णांक err;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->pdata = dev_get_platdata(&pdev->dev);
	अगर (!priv->pdata) अणु
		dev_err(&pdev->dev, "Failed to get platform data.\n");
		वापस -EINVAL;
	पूर्ण

	priv->pdev = pdev;
	priv->regsize = regmap_get_val_bytes(priv->pdata->regmap);
	अगर (priv->regsize < 0)
		वापस priv->regsize;

	err = mlxreg_io_attr_init(priv);
	अगर (err) अणु
		dev_err(&priv->pdev->dev, "Failed to allocate attributes: %d\n",
			err);
		वापस err;
	पूर्ण

	priv->hwmon = devm_hwmon_device_रेजिस्टर_with_groups(&pdev->dev,
							     "mlxreg_io",
							      priv,
							      priv->groups);
	अगर (IS_ERR(priv->hwmon)) अणु
		dev_err(&pdev->dev, "Failed to register hwmon device %ld\n",
			PTR_ERR(priv->hwmon));
		वापस PTR_ERR(priv->hwmon);
	पूर्ण

	dev_set_drvdata(&pdev->dev, priv);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mlxreg_io_driver = अणु
	.driver = अणु
	    .name = "mlxreg-io",
	पूर्ण,
	.probe = mlxreg_io_probe,
पूर्ण;

module_platक्रमm_driver(mlxreg_io_driver);

MODULE_AUTHOR("Vadim Pasternak <vadimp@mellanox.com>");
MODULE_DESCRIPTION("Mellanox regmap I/O access driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:mlxreg-io");
