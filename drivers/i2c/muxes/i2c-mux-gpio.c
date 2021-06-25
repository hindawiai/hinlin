<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2C multiplexer using GPIO API
 *
 * Peter Korsgaard <peter.korsgaard@barco.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/i2c-mux.h>
#समावेश <linux/platक्रमm_data/i2c-mux-gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/bits.h>
#समावेश <linux/gpio/consumer.h>
/* FIXME: stop poking around inside gpiolib */
#समावेश "../../gpio/gpiolib.h"

काष्ठा gpiomux अणु
	काष्ठा i2c_mux_gpio_platक्रमm_data data;
	पूर्णांक ngpios;
	काष्ठा gpio_desc **gpios;
पूर्ण;

अटल व्योम i2c_mux_gpio_set(स्थिर काष्ठा gpiomux *mux, अचिन्हित val)
अणु
	DECLARE_BITMAP(values, BITS_PER_TYPE(val));

	values[0] = val;

	gpiod_set_array_value_cansleep(mux->ngpios, mux->gpios, शून्य, values);
पूर्ण

अटल पूर्णांक i2c_mux_gpio_select(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा gpiomux *mux = i2c_mux_priv(muxc);

	i2c_mux_gpio_set(mux, chan);

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_mux_gpio_deselect(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा gpiomux *mux = i2c_mux_priv(muxc);

	i2c_mux_gpio_set(mux, mux->data.idle);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI

अटल पूर्णांक i2c_mux_gpio_get_acpi_adr(काष्ठा device *dev,
				     काष्ठा fwnode_handle *fwdev,
				     अचिन्हित पूर्णांक *adr)

अणु
	अचिन्हित दीर्घ दीर्घ adr64;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(ACPI_HANDLE_FWNODE(fwdev),
				       METHOD_NAME__ADR,
				       शून्य, &adr64);

	अगर (!ACPI_SUCCESS(status)) अणु
		dev_err(dev, "Cannot get address\n");
		वापस -EINVAL;
	पूर्ण

	*adr = adr64;
	अगर (*adr != adr64) अणु
		dev_err(dev, "Address out of range\n");
		वापस -दुस्फल;
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा

अटल पूर्णांक i2c_mux_gpio_get_acpi_adr(काष्ठा device *dev,
				     काष्ठा fwnode_handle *fwdev,
				     अचिन्हित पूर्णांक *adr)
अणु
	वापस -EINVAL;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक i2c_mux_gpio_probe_fw(काष्ठा gpiomux *mux,
				 काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *adapter_np;
	काष्ठा i2c_adapter *adapter = शून्य;
	काष्ठा fwnode_handle *child;
	अचिन्हित *values;
	पूर्णांक rc, i = 0;

	अगर (is_of_node(dev->fwnode)) अणु
		अगर (!np)
			वापस -ENODEV;

		adapter_np = of_parse_phandle(np, "i2c-parent", 0);
		अगर (!adapter_np) अणु
			dev_err(&pdev->dev, "Cannot parse i2c-parent\n");
			वापस -ENODEV;
		पूर्ण
		adapter = of_find_i2c_adapter_by_node(adapter_np);
		of_node_put(adapter_np);

	पूर्ण अन्यथा अगर (is_acpi_node(dev->fwnode)) अणु
		/*
		 * In ACPI land the mux should be a direct child of the i2c
		 * bus it muxes.
		 */
		acpi_handle dev_handle = ACPI_HANDLE(dev->parent);

		adapter = i2c_acpi_find_adapter_by_handle(dev_handle);
	पूर्ण

	अगर (!adapter)
		वापस -EPROBE_DEFER;

	mux->data.parent = i2c_adapter_id(adapter);
	put_device(&adapter->dev);

	mux->data.n_values = device_get_child_node_count(dev);
	values = devm_kसुस्मृति(dev,
			      mux->data.n_values, माप(*mux->data.values),
			      GFP_KERNEL);
	अगर (!values) अणु
		dev_err(dev, "Cannot allocate values array");
		वापस -ENOMEM;
	पूर्ण

	device_क्रम_each_child_node(dev, child) अणु
		अगर (is_of_node(child)) अणु
			fwnode_property_पढ़ो_u32(child, "reg", values + i);

		पूर्ण अन्यथा अगर (is_acpi_node(child)) अणु
			rc = i2c_mux_gpio_get_acpi_adr(dev, child, values + i);
			अगर (rc)
				वापस rc;
		पूर्ण

		i++;
	पूर्ण
	mux->data.values = values;

	अगर (fwnode_property_पढ़ो_u32(dev->fwnode, "idle-state", &mux->data.idle))
		mux->data.idle = I2C_MUX_GPIO_NO_IDLE;

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_mux_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_mux_core *muxc;
	काष्ठा gpiomux *mux;
	काष्ठा i2c_adapter *parent;
	काष्ठा i2c_adapter *root;
	अचिन्हित initial_state;
	पूर्णांक i, ngpios, ret;

	mux = devm_kzalloc(&pdev->dev, माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस -ENOMEM;

	अगर (!dev_get_platdata(&pdev->dev)) अणु
		ret = i2c_mux_gpio_probe_fw(mux, pdev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		स_नकल(&mux->data, dev_get_platdata(&pdev->dev),
			माप(mux->data));
	पूर्ण

	ngpios = gpiod_count(&pdev->dev, "mux");
	अगर (ngpios <= 0) अणु
		dev_err(&pdev->dev, "no valid gpios provided\n");
		वापस ngpios ?: -EINVAL;
	पूर्ण
	mux->ngpios = ngpios;

	parent = i2c_get_adapter(mux->data.parent);
	अगर (!parent)
		वापस -EPROBE_DEFER;

	muxc = i2c_mux_alloc(parent, &pdev->dev, mux->data.n_values,
			     ngpios * माप(*mux->gpios), 0,
			     i2c_mux_gpio_select, शून्य);
	अगर (!muxc) अणु
		ret = -ENOMEM;
		जाओ alloc_failed;
	पूर्ण
	mux->gpios = muxc->priv;
	muxc->priv = mux;

	platक्रमm_set_drvdata(pdev, muxc);

	root = i2c_root_adapter(&parent->dev);

	muxc->mux_locked = true;

	अगर (mux->data.idle != I2C_MUX_GPIO_NO_IDLE) अणु
		initial_state = mux->data.idle;
		muxc->deselect = i2c_mux_gpio_deselect;
	पूर्ण अन्यथा अणु
		initial_state = mux->data.values[0];
	पूर्ण

	क्रम (i = 0; i < ngpios; i++) अणु
		काष्ठा device *gpio_dev;
		काष्ठा gpio_desc *gpiod;
		क्रमागत gpiod_flags flag;

		अगर (initial_state & BIT(i))
			flag = GPIOD_OUT_HIGH;
		अन्यथा
			flag = GPIOD_OUT_LOW;
		gpiod = devm_gpiod_get_index(&pdev->dev, "mux", i, flag);
		अगर (IS_ERR(gpiod)) अणु
			ret = PTR_ERR(gpiod);
			जाओ alloc_failed;
		पूर्ण

		mux->gpios[i] = gpiod;

		अगर (!muxc->mux_locked)
			जारी;

		/* FIXME: find a proper way to access the GPIO device */
		gpio_dev = &gpiod->gdev->dev;
		muxc->mux_locked = i2c_root_adapter(gpio_dev) == root;
	पूर्ण

	अगर (muxc->mux_locked)
		dev_info(&pdev->dev, "mux-locked i2c mux\n");

	क्रम (i = 0; i < mux->data.n_values; i++) अणु
		u32 nr = mux->data.base_nr ? (mux->data.base_nr + i) : 0;
		अचिन्हित पूर्णांक class = mux->data.classes ? mux->data.classes[i] : 0;

		ret = i2c_mux_add_adapter(muxc, nr, mux->data.values[i], class);
		अगर (ret)
			जाओ add_adapter_failed;
	पूर्ण

	dev_info(&pdev->dev, "%d port mux on %s adapter\n",
		 mux->data.n_values, parent->name);

	वापस 0;

add_adapter_failed:
	i2c_mux_del_adapters(muxc);
alloc_failed:
	i2c_put_adapter(parent);

	वापस ret;
पूर्ण

अटल पूर्णांक i2c_mux_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_mux_core *muxc = platक्रमm_get_drvdata(pdev);

	i2c_mux_del_adapters(muxc);
	i2c_put_adapter(muxc->parent);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id i2c_mux_gpio_of_match[] = अणु
	अणु .compatible = "i2c-mux-gpio", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, i2c_mux_gpio_of_match);

अटल काष्ठा platक्रमm_driver i2c_mux_gpio_driver = अणु
	.probe	= i2c_mux_gpio_probe,
	.हटाओ	= i2c_mux_gpio_हटाओ,
	.driver	= अणु
		.name	= "i2c-mux-gpio",
		.of_match_table = i2c_mux_gpio_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(i2c_mux_gpio_driver);

MODULE_DESCRIPTION("GPIO-based I2C multiplexer driver");
MODULE_AUTHOR("Peter Korsgaard <peter.korsgaard@barco.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:i2c-mux-gpio");
