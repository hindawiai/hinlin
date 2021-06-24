<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Analog Devices Generic AXI ADC IP core
 * Link: https://wiki.analog.com/resources/fpga/करोcs/axi_adc_ip
 *
 * Copyright 2012-2020 Analog Devices Inc.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/buffer-dmaengine.h>

#समावेश <linux/fpga/adi-axi-common.h>
#समावेश <linux/iio/adc/adi-axi-adc.h>

/*
 * Register definitions:
 *   https://wiki.analog.com/resources/fpga/करोcs/axi_adc_ip#रेजिस्टर_map
 */

/* ADC controls */

#घोषणा ADI_AXI_REG_RSTN			0x0040
#घोषणा   ADI_AXI_REG_RSTN_CE_N			BIT(2)
#घोषणा   ADI_AXI_REG_RSTN_MMCM_RSTN		BIT(1)
#घोषणा   ADI_AXI_REG_RSTN_RSTN			BIT(0)

/* ADC Channel controls */

#घोषणा ADI_AXI_REG_CHAN_CTRL(c)		(0x0400 + (c) * 0x40)
#घोषणा   ADI_AXI_REG_CHAN_CTRL_LB_OWR		BIT(11)
#घोषणा   ADI_AXI_REG_CHAN_CTRL_PN_SEL_OWR	BIT(10)
#घोषणा   ADI_AXI_REG_CHAN_CTRL_IQCOR_EN	BIT(9)
#घोषणा   ADI_AXI_REG_CHAN_CTRL_DCFILT_EN	BIT(8)
#घोषणा   ADI_AXI_REG_CHAN_CTRL_FMT_SIGNEXT	BIT(6)
#घोषणा   ADI_AXI_REG_CHAN_CTRL_FMT_TYPE	BIT(5)
#घोषणा   ADI_AXI_REG_CHAN_CTRL_FMT_EN		BIT(4)
#घोषणा   ADI_AXI_REG_CHAN_CTRL_PN_TYPE_OWR	BIT(1)
#घोषणा   ADI_AXI_REG_CHAN_CTRL_ENABLE		BIT(0)

#घोषणा ADI_AXI_REG_CHAN_CTRL_DEFAULTS		\
	(ADI_AXI_REG_CHAN_CTRL_FMT_SIGNEXT |	\
	 ADI_AXI_REG_CHAN_CTRL_FMT_EN |		\
	 ADI_AXI_REG_CHAN_CTRL_ENABLE)

काष्ठा adi_axi_adc_core_info अणु
	अचिन्हित पूर्णांक				version;
पूर्ण;

काष्ठा adi_axi_adc_state अणु
	काष्ठा mutex				lock;

	काष्ठा adi_axi_adc_client		*client;
	व्योम __iomem				*regs;
पूर्ण;

काष्ठा adi_axi_adc_client अणु
	काष्ठा list_head			entry;
	काष्ठा adi_axi_adc_conv			conv;
	काष्ठा adi_axi_adc_state		*state;
	काष्ठा device				*dev;
	स्थिर काष्ठा adi_axi_adc_core_info	*info;
पूर्ण;

अटल LIST_HEAD(रेजिस्टरed_clients);
अटल DEFINE_MUTEX(रेजिस्टरed_clients_lock);

अटल काष्ठा adi_axi_adc_client *conv_to_client(काष्ठा adi_axi_adc_conv *conv)
अणु
	वापस container_of(conv, काष्ठा adi_axi_adc_client, conv);
पूर्ण

व्योम *adi_axi_adc_conv_priv(काष्ठा adi_axi_adc_conv *conv)
अणु
	काष्ठा adi_axi_adc_client *cl = conv_to_client(conv);

	वापस (अक्षर *)cl + ALIGN(माप(काष्ठा adi_axi_adc_client), IIO_ALIGN);
पूर्ण
EXPORT_SYMBOL_GPL(adi_axi_adc_conv_priv);

अटल व्योम adi_axi_adc_ग_लिखो(काष्ठा adi_axi_adc_state *st,
			      अचिन्हित पूर्णांक reg,
			      अचिन्हित पूर्णांक val)
अणु
	ioग_लिखो32(val, st->regs + reg);
पूर्ण

अटल अचिन्हित पूर्णांक adi_axi_adc_पढ़ो(काष्ठा adi_axi_adc_state *st,
				     अचिन्हित पूर्णांक reg)
अणु
	वापस ioपढ़ो32(st->regs + reg);
पूर्ण

अटल पूर्णांक adi_axi_adc_config_dma_buffer(काष्ठा device *dev,
					 काष्ठा iio_dev *indio_dev)
अणु
	स्थिर अक्षर *dma_name;

	अगर (!device_property_present(dev, "dmas"))
		वापस 0;

	अगर (device_property_पढ़ो_string(dev, "dma-names", &dma_name))
		dma_name = "rx";

	वापस devm_iio_dmaengine_buffer_setup(indio_dev->dev.parent,
					       indio_dev, dma_name);
पूर्ण

अटल पूर्णांक adi_axi_adc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा adi_axi_adc_state *st = iio_priv(indio_dev);
	काष्ठा adi_axi_adc_conv *conv = &st->client->conv;

	अगर (!conv->पढ़ो_raw)
		वापस -EOPNOTSUPP;

	वापस conv->पढ़ो_raw(conv, chan, val, val2, mask);
पूर्ण

अटल पूर्णांक adi_axi_adc_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
				 काष्ठा iio_chan_spec स्थिर *chan,
				 पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा adi_axi_adc_state *st = iio_priv(indio_dev);
	काष्ठा adi_axi_adc_conv *conv = &st->client->conv;

	अगर (!conv->ग_लिखो_raw)
		वापस -EOPNOTSUPP;

	वापस conv->ग_लिखो_raw(conv, chan, val, val2, mask);
पूर्ण

अटल पूर्णांक adi_axi_adc_update_scan_mode(काष्ठा iio_dev *indio_dev,
					स्थिर अचिन्हित दीर्घ *scan_mask)
अणु
	काष्ठा adi_axi_adc_state *st = iio_priv(indio_dev);
	काष्ठा adi_axi_adc_conv *conv = &st->client->conv;
	अचिन्हित पूर्णांक i, ctrl;

	क्रम (i = 0; i < conv->chip_info->num_channels; i++) अणु
		ctrl = adi_axi_adc_पढ़ो(st, ADI_AXI_REG_CHAN_CTRL(i));

		अगर (test_bit(i, scan_mask))
			ctrl |= ADI_AXI_REG_CHAN_CTRL_ENABLE;
		अन्यथा
			ctrl &= ~ADI_AXI_REG_CHAN_CTRL_ENABLE;

		adi_axi_adc_ग_लिखो(st, ADI_AXI_REG_CHAN_CTRL(i), ctrl);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा adi_axi_adc_conv *adi_axi_adc_conv_रेजिस्टर(काष्ठा device *dev,
							  माप_प्रकार माप_priv)
अणु
	काष्ठा adi_axi_adc_client *cl;
	माप_प्रकार alloc_size;

	alloc_size = ALIGN(माप(काष्ठा adi_axi_adc_client), IIO_ALIGN);
	अगर (माप_priv)
		alloc_size += ALIGN(माप_priv, IIO_ALIGN);

	cl = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!cl)
		वापस ERR_PTR(-ENOMEM);

	mutex_lock(&रेजिस्टरed_clients_lock);

	cl->dev = get_device(dev);

	list_add_tail(&cl->entry, &रेजिस्टरed_clients);

	mutex_unlock(&रेजिस्टरed_clients_lock);

	वापस &cl->conv;
पूर्ण

अटल व्योम adi_axi_adc_conv_unरेजिस्टर(काष्ठा adi_axi_adc_conv *conv)
अणु
	काष्ठा adi_axi_adc_client *cl = conv_to_client(conv);

	mutex_lock(&रेजिस्टरed_clients_lock);

	list_del(&cl->entry);
	put_device(cl->dev);

	mutex_unlock(&रेजिस्टरed_clients_lock);

	kमुक्त(cl);
पूर्ण

अटल व्योम devm_adi_axi_adc_conv_release(काष्ठा device *dev, व्योम *res)
अणु
	adi_axi_adc_conv_unरेजिस्टर(*(काष्ठा adi_axi_adc_conv **)res);
पूर्ण

काष्ठा adi_axi_adc_conv *devm_adi_axi_adc_conv_रेजिस्टर(काष्ठा device *dev,
							माप_प्रकार माप_priv)
अणु
	काष्ठा adi_axi_adc_conv **ptr, *conv;

	ptr = devres_alloc(devm_adi_axi_adc_conv_release, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	conv = adi_axi_adc_conv_रेजिस्टर(dev, माप_priv);
	अगर (IS_ERR(conv)) अणु
		devres_मुक्त(ptr);
		वापस ERR_CAST(conv);
	पूर्ण

	*ptr = conv;
	devres_add(dev, ptr);

	वापस conv;
पूर्ण
EXPORT_SYMBOL_GPL(devm_adi_axi_adc_conv_रेजिस्टर);

अटल sमाप_प्रकार in_voltage_scale_available_show(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा adi_axi_adc_state *st = iio_priv(indio_dev);
	काष्ठा adi_axi_adc_conv *conv = &st->client->conv;
	माप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < conv->chip_info->num_scales; i++) अणु
		स्थिर अचिन्हित पूर्णांक *s = conv->chip_info->scale_table[i];

		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
				 "%u.%06u ", s[0], s[1]);
	पूर्ण
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR_RO(in_voltage_scale_available, 0);

क्रमागत अणु
	ADI_AXI_ATTR_SCALE_AVAIL,
पूर्ण;

#घोषणा ADI_AXI_ATTR(_en_, _file_)			\
	[ADI_AXI_ATTR_##_en_] = &iio_dev_attr_##_file_.dev_attr.attr

अटल काष्ठा attribute *adi_axi_adc_attributes[] = अणु
	ADI_AXI_ATTR(SCALE_AVAIL, in_voltage_scale_available),
	शून्य
पूर्ण;

अटल umode_t axi_adc_attr_is_visible(काष्ठा kobject *kobj,
				       काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा adi_axi_adc_state *st = iio_priv(indio_dev);
	काष्ठा adi_axi_adc_conv *conv = &st->client->conv;

	चयन (n) अणु
	हाल ADI_AXI_ATTR_SCALE_AVAIL:
		अगर (!conv->chip_info->num_scales)
			वापस 0;
		वापस attr->mode;
	शेष:
		वापस attr->mode;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा attribute_group adi_axi_adc_attribute_group = अणु
	.attrs = adi_axi_adc_attributes,
	.is_visible = axi_adc_attr_is_visible,
पूर्ण;

अटल स्थिर काष्ठा iio_info adi_axi_adc_info = अणु
	.पढ़ो_raw = &adi_axi_adc_पढ़ो_raw,
	.ग_लिखो_raw = &adi_axi_adc_ग_लिखो_raw,
	.attrs = &adi_axi_adc_attribute_group,
	.update_scan_mode = &adi_axi_adc_update_scan_mode,
पूर्ण;

अटल स्थिर काष्ठा adi_axi_adc_core_info adi_axi_adc_10_0_a_info = अणु
	.version = ADI_AXI_PCORE_VER(10, 0, 'a'),
पूर्ण;

अटल काष्ठा adi_axi_adc_client *adi_axi_adc_attach_client(काष्ठा device *dev)
अणु
	स्थिर काष्ठा adi_axi_adc_core_info *info;
	काष्ठा adi_axi_adc_client *cl;
	काष्ठा device_node *cln;

	info = of_device_get_match_data(dev);
	अगर (!info)
		वापस ERR_PTR(-ENODEV);

	cln = of_parse_phandle(dev->of_node, "adi,adc-dev", 0);
	अगर (!cln) अणु
		dev_err(dev, "No 'adi,adc-dev' node defined\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	mutex_lock(&रेजिस्टरed_clients_lock);

	list_क्रम_each_entry(cl, &रेजिस्टरed_clients, entry) अणु
		अगर (!cl->dev)
			जारी;

		अगर (cl->dev->of_node != cln)
			जारी;

		अगर (!try_module_get(cl->dev->driver->owner)) अणु
			mutex_unlock(&रेजिस्टरed_clients_lock);
			वापस ERR_PTR(-ENODEV);
		पूर्ण

		get_device(cl->dev);
		cl->info = info;
		mutex_unlock(&रेजिस्टरed_clients_lock);
		वापस cl;
	पूर्ण

	mutex_unlock(&रेजिस्टरed_clients_lock);

	वापस ERR_PTR(-EPROBE_DEFER);
पूर्ण

अटल पूर्णांक adi_axi_adc_setup_channels(काष्ठा device *dev,
				      काष्ठा adi_axi_adc_state *st)
अणु
	काष्ठा adi_axi_adc_conv *conv = &st->client->conv;
	पूर्णांक i, ret;

	अगर (conv->preenable_setup) अणु
		ret = conv->preenable_setup(conv);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < conv->chip_info->num_channels; i++) अणु
		adi_axi_adc_ग_लिखो(st, ADI_AXI_REG_CHAN_CTRL(i),
				  ADI_AXI_REG_CHAN_CTRL_DEFAULTS);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम axi_adc_reset(काष्ठा adi_axi_adc_state *st)
अणु
	adi_axi_adc_ग_लिखो(st, ADI_AXI_REG_RSTN, 0);
	mdelay(10);
	adi_axi_adc_ग_लिखो(st, ADI_AXI_REG_RSTN, ADI_AXI_REG_RSTN_MMCM_RSTN);
	mdelay(10);
	adi_axi_adc_ग_लिखो(st, ADI_AXI_REG_RSTN,
			  ADI_AXI_REG_RSTN_RSTN | ADI_AXI_REG_RSTN_MMCM_RSTN);
पूर्ण

अटल व्योम adi_axi_adc_cleanup(व्योम *data)
अणु
	काष्ठा adi_axi_adc_client *cl = data;

	put_device(cl->dev);
	module_put(cl->dev->driver->owner);
पूर्ण

अटल पूर्णांक adi_axi_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा adi_axi_adc_conv *conv;
	काष्ठा iio_dev *indio_dev;
	काष्ठा adi_axi_adc_client *cl;
	काष्ठा adi_axi_adc_state *st;
	अचिन्हित पूर्णांक ver;
	पूर्णांक ret;

	cl = adi_axi_adc_attach_client(&pdev->dev);
	अगर (IS_ERR(cl))
		वापस PTR_ERR(cl);

	ret = devm_add_action_or_reset(&pdev->dev, adi_axi_adc_cleanup, cl);
	अगर (ret)
		वापस ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*st));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	st->client = cl;
	cl->state = st;
	mutex_init(&st->lock);

	st->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(st->regs))
		वापस PTR_ERR(st->regs);

	conv = &st->client->conv;

	axi_adc_reset(st);

	ver = adi_axi_adc_पढ़ो(st, ADI_AXI_REG_VERSION);

	अगर (cl->info->version > ver) अणु
		dev_err(&pdev->dev,
			"IP core version is too old. Expected %d.%.2d.%c, Reported %d.%.2d.%c\n",
			ADI_AXI_PCORE_VER_MAJOR(cl->info->version),
			ADI_AXI_PCORE_VER_MINOR(cl->info->version),
			ADI_AXI_PCORE_VER_PATCH(cl->info->version),
			ADI_AXI_PCORE_VER_MAJOR(ver),
			ADI_AXI_PCORE_VER_MINOR(ver),
			ADI_AXI_PCORE_VER_PATCH(ver));
		वापस -ENODEV;
	पूर्ण

	indio_dev->info = &adi_axi_adc_info;
	indio_dev->name = "adi-axi-adc";
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->num_channels = conv->chip_info->num_channels;
	indio_dev->channels = conv->chip_info->channels;

	ret = adi_axi_adc_config_dma_buffer(&pdev->dev, indio_dev);
	अगर (ret)
		वापस ret;

	ret = adi_axi_adc_setup_channels(&pdev->dev, st);
	अगर (ret)
		वापस ret;

	ret = devm_iio_device_रेजिस्टर(&pdev->dev, indio_dev);
	अगर (ret)
		वापस ret;

	dev_info(&pdev->dev, "AXI ADC IP core (%d.%.2d.%c) probed\n",
		 ADI_AXI_PCORE_VER_MAJOR(ver),
		 ADI_AXI_PCORE_VER_MINOR(ver),
		 ADI_AXI_PCORE_VER_PATCH(ver));

	वापस 0;
पूर्ण

/* Match table क्रम of_platक्रमm binding */
अटल स्थिर काष्ठा of_device_id adi_axi_adc_of_match[] = अणु
	अणु .compatible = "adi,axi-adc-10.0.a", .data = &adi_axi_adc_10_0_a_info पूर्ण,
	अणु /* end of list */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adi_axi_adc_of_match);

अटल काष्ठा platक्रमm_driver adi_axi_adc_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = adi_axi_adc_of_match,
	पूर्ण,
	.probe = adi_axi_adc_probe,
पूर्ण;
module_platक्रमm_driver(adi_axi_adc_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices Generic AXI ADC IP core driver");
MODULE_LICENSE("GPL v2");
