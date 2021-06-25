<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Robert Jarzmik <robert.jarzmik@मुक्त.fr>
 */

#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/idr.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <sound/ac97/codec.h>
#समावेश <sound/ac97/controller.h>
#समावेश <sound/ac97/regs.h>

#समावेश "ac97_core.h"

/*
 * Protects ac97_controllers and each ac97_controller काष्ठाure.
 */
अटल DEFINE_MUTEX(ac97_controllers_mutex);
अटल DEFINE_IDR(ac97_adapter_idr);
अटल LIST_HEAD(ac97_controllers);

अटल काष्ठा bus_type ac97_bus_type;

अटल अंतरभूत काष्ठा ac97_controller*
to_ac97_controller(काष्ठा device *ac97_adapter)
अणु
	वापस container_of(ac97_adapter, काष्ठा ac97_controller, adap);
पूर्ण

अटल पूर्णांक ac97_unbound_ctrl_ग_लिखो(काष्ठा ac97_controller *adrv, पूर्णांक slot,
		     अचिन्हित लघु reg, अचिन्हित लघु val)
अणु
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक ac97_unbound_ctrl_पढ़ो(काष्ठा ac97_controller *adrv, पूर्णांक slot,
				  अचिन्हित लघु reg)
अणु
	वापस -ENODEV;
पूर्ण

अटल स्थिर काष्ठा ac97_controller_ops ac97_unbound_ctrl_ops = अणु
	.ग_लिखो = ac97_unbound_ctrl_ग_लिखो,
	.पढ़ो = ac97_unbound_ctrl_पढ़ो,
पूर्ण;

अटल काष्ठा ac97_controller ac97_unbound_ctrl = अणु
	.ops = &ac97_unbound_ctrl_ops,
पूर्ण;

अटल काष्ठा ac97_codec_device *
ac97_codec_find(काष्ठा ac97_controller *ac97_ctrl, अचिन्हित पूर्णांक codec_num)
अणु
	अगर (codec_num >= AC97_BUS_MAX_CODECS)
		वापस ERR_PTR(-EINVAL);

	वापस ac97_ctrl->codecs[codec_num];
पूर्ण

अटल काष्ठा device_node *
ac97_of_get_child_device(काष्ठा ac97_controller *ac97_ctrl, पूर्णांक idx,
			 अचिन्हित पूर्णांक venकरोr_id)
अणु
	काष्ठा device_node *node;
	u32 reg;
	अक्षर compat[] = "ac97,0000,0000";

	snम_लिखो(compat, माप(compat), "ac97,%04x,%04x",
		 venकरोr_id >> 16, venकरोr_id & 0xffff);

	क्रम_each_child_of_node(ac97_ctrl->parent->of_node, node) अणु
		अगर ((idx != of_property_पढ़ो_u32(node, "reg", &reg)) ||
		    !of_device_is_compatible(node, compat))
			जारी;
		वापस node;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम ac97_codec_release(काष्ठा device *dev)
अणु
	काष्ठा ac97_codec_device *adev;
	काष्ठा ac97_controller *ac97_ctrl;

	adev = to_ac97_device(dev);
	ac97_ctrl = adev->ac97_ctrl;
	ac97_ctrl->codecs[adev->num] = शून्य;
	of_node_put(dev->of_node);
	kमुक्त(adev);
पूर्ण

अटल पूर्णांक ac97_codec_add(काष्ठा ac97_controller *ac97_ctrl, पूर्णांक idx,
		   अचिन्हित पूर्णांक venकरोr_id)
अणु
	काष्ठा ac97_codec_device *codec;
	पूर्णांक ret;

	codec = kzalloc(माप(*codec), GFP_KERNEL);
	अगर (!codec)
		वापस -ENOMEM;
	ac97_ctrl->codecs[idx] = codec;
	codec->venकरोr_id = venकरोr_id;
	codec->dev.release = ac97_codec_release;
	codec->dev.bus = &ac97_bus_type;
	codec->dev.parent = &ac97_ctrl->adap;
	codec->num = idx;
	codec->ac97_ctrl = ac97_ctrl;

	device_initialize(&codec->dev);
	dev_set_name(&codec->dev, "%s:%u", dev_name(ac97_ctrl->parent), idx);
	codec->dev.of_node = ac97_of_get_child_device(ac97_ctrl, idx,
						      venकरोr_id);

	ret = device_add(&codec->dev);
	अगर (ret) अणु
		put_device(&codec->dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अचिन्हित पूर्णांक snd_ac97_bus_scan_one(काष्ठा ac97_controller *adrv,
				   अचिन्हित पूर्णांक codec_num)
अणु
	अचिन्हित लघु vid1, vid2;
	पूर्णांक ret;

	ret = adrv->ops->पढ़ो(adrv, codec_num, AC97_VENDOR_ID1);
	vid1 = (ret & 0xffff);
	अगर (ret < 0)
		वापस 0;

	ret = adrv->ops->पढ़ो(adrv, codec_num, AC97_VENDOR_ID2);
	vid2 = (ret & 0xffff);
	अगर (ret < 0)
		वापस 0;

	dev_dbg(&adrv->adap, "%s(codec_num=%u): vendor_id=0x%08x\n",
		__func__, codec_num, AC97_ID(vid1, vid2));
	वापस AC97_ID(vid1, vid2);
पूर्ण

अटल पूर्णांक ac97_bus_scan(काष्ठा ac97_controller *ac97_ctrl)
अणु
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक venकरोr_id;

	क्रम (i = 0; i < AC97_BUS_MAX_CODECS; i++) अणु
		अगर (ac97_codec_find(ac97_ctrl, i))
			जारी;
		अगर (!(ac97_ctrl->slots_available & BIT(i)))
			जारी;
		venकरोr_id = snd_ac97_bus_scan_one(ac97_ctrl, i);
		अगर (!venकरोr_id)
			जारी;

		ret = ac97_codec_add(ac97_ctrl, i, venकरोr_id);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ac97_bus_reset(काष्ठा ac97_controller *ac97_ctrl)
अणु
	ac97_ctrl->ops->reset(ac97_ctrl);

	वापस 0;
पूर्ण

/**
 * snd_ac97_codec_driver_रेजिस्टर - रेजिस्टर an AC97 codec driver
 * @dev: AC97 driver codec to रेजिस्टर
 *
 * Register an AC97 codec driver to the ac97 bus driver, aka. the AC97 digital
 * controller.
 *
 * Returns 0 on success or error code
 */
पूर्णांक snd_ac97_codec_driver_रेजिस्टर(काष्ठा ac97_codec_driver *drv)
अणु
	drv->driver.bus = &ac97_bus_type;
	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(snd_ac97_codec_driver_रेजिस्टर);

/**
 * snd_ac97_codec_driver_unरेजिस्टर - unरेजिस्टर an AC97 codec driver
 * @dev: AC97 codec driver to unरेजिस्टर
 *
 * Unरेजिस्टर a previously रेजिस्टरed ac97 codec driver.
 */
व्योम snd_ac97_codec_driver_unरेजिस्टर(काष्ठा ac97_codec_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(snd_ac97_codec_driver_unरेजिस्टर);

/**
 * snd_ac97_codec_get_platdata - get platक्रमm_data
 * @adev: the ac97 codec device
 *
 * For legacy platक्रमms, in order to have platक्रमm_data in codec drivers
 * available, जबतक ac97 device are स्वतः-created upon probe, this retrieves the
 * platdata which was setup on ac97 controller registration.
 *
 * Returns the platक्रमm data poपूर्णांकer
 */
व्योम *snd_ac97_codec_get_platdata(स्थिर काष्ठा ac97_codec_device *adev)
अणु
	काष्ठा ac97_controller *ac97_ctrl = adev->ac97_ctrl;

	वापस ac97_ctrl->codecs_pdata[adev->num];
पूर्ण
EXPORT_SYMBOL_GPL(snd_ac97_codec_get_platdata);

अटल व्योम ac97_ctrl_codecs_unरेजिस्टर(काष्ठा ac97_controller *ac97_ctrl)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < AC97_BUS_MAX_CODECS; i++)
		अगर (ac97_ctrl->codecs[i]) अणु
			ac97_ctrl->codecs[i]->ac97_ctrl = &ac97_unbound_ctrl;
			device_unरेजिस्टर(&ac97_ctrl->codecs[i]->dev);
		पूर्ण
पूर्ण

अटल sमाप_प्रकार cold_reset_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार len)
अणु
	काष्ठा ac97_controller *ac97_ctrl;

	mutex_lock(&ac97_controllers_mutex);
	ac97_ctrl = to_ac97_controller(dev);
	ac97_ctrl->ops->reset(ac97_ctrl);
	mutex_unlock(&ac97_controllers_mutex);
	वापस len;
पूर्ण
अटल DEVICE_ATTR_WO(cold_reset);

अटल sमाप_प्रकार warm_reset_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार len)
अणु
	काष्ठा ac97_controller *ac97_ctrl;

	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&ac97_controllers_mutex);
	ac97_ctrl = to_ac97_controller(dev);
	ac97_ctrl->ops->warm_reset(ac97_ctrl);
	mutex_unlock(&ac97_controllers_mutex);
	वापस len;
पूर्ण
अटल DEVICE_ATTR_WO(warm_reset);

अटल काष्ठा attribute *ac97_controller_device_attrs[] = अणु
	&dev_attr_cold_reset.attr,
	&dev_attr_warm_reset.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ac97_adapter_attr_group = अणु
	.name	= "ac97_operations",
	.attrs	= ac97_controller_device_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *ac97_adapter_groups[] = अणु
	&ac97_adapter_attr_group,
	शून्य,
पूर्ण;

अटल व्योम ac97_del_adapter(काष्ठा ac97_controller *ac97_ctrl)
अणु
	mutex_lock(&ac97_controllers_mutex);
	ac97_ctrl_codecs_unरेजिस्टर(ac97_ctrl);
	list_del(&ac97_ctrl->controllers);
	mutex_unlock(&ac97_controllers_mutex);

	device_unरेजिस्टर(&ac97_ctrl->adap);
पूर्ण

अटल व्योम ac97_adapter_release(काष्ठा device *dev)
अणु
	काष्ठा ac97_controller *ac97_ctrl;

	ac97_ctrl = to_ac97_controller(dev);
	idr_हटाओ(&ac97_adapter_idr, ac97_ctrl->nr);
	dev_dbg(&ac97_ctrl->adap, "adapter unregistered by %s\n",
		dev_name(ac97_ctrl->parent));
पूर्ण

अटल स्थिर काष्ठा device_type ac97_adapter_type = अणु
	.groups		= ac97_adapter_groups,
	.release	= ac97_adapter_release,
पूर्ण;

अटल पूर्णांक ac97_add_adapter(काष्ठा ac97_controller *ac97_ctrl)
अणु
	पूर्णांक ret;

	mutex_lock(&ac97_controllers_mutex);
	ret = idr_alloc(&ac97_adapter_idr, ac97_ctrl, 0, 0, GFP_KERNEL);
	ac97_ctrl->nr = ret;
	अगर (ret >= 0) अणु
		dev_set_name(&ac97_ctrl->adap, "ac97-%d", ret);
		ac97_ctrl->adap.type = &ac97_adapter_type;
		ac97_ctrl->adap.parent = ac97_ctrl->parent;
		ret = device_रेजिस्टर(&ac97_ctrl->adap);
		अगर (ret)
			put_device(&ac97_ctrl->adap);
	पूर्ण
	अगर (!ret)
		list_add(&ac97_ctrl->controllers, &ac97_controllers);
	mutex_unlock(&ac97_controllers_mutex);

	अगर (!ret)
		dev_dbg(&ac97_ctrl->adap, "adapter registered by %s\n",
			dev_name(ac97_ctrl->parent));
	वापस ret;
पूर्ण

/**
 * snd_ac97_controller_रेजिस्टर - रेजिस्टर an ac97 controller
 * @ops: the ac97 bus operations
 * @dev: the device providing the ac97 DC function
 * @slots_available: mask of the ac97 codecs that can be scanned and probed
 *                   bit0 => codec 0, bit1 => codec 1 ... bit 3 => codec 3
 *
 * Register a digital controller which can control up to 4 ac97 codecs. This is
 * the controller side of the AC97 AC-link, जबतक the slave side are the codecs.
 *
 * Returns a valid controller upon success, negative poपूर्णांकer value upon error
 */
काष्ठा ac97_controller *snd_ac97_controller_रेजिस्टर(
	स्थिर काष्ठा ac97_controller_ops *ops, काष्ठा device *dev,
	अचिन्हित लघु slots_available, व्योम **codecs_pdata)
अणु
	काष्ठा ac97_controller *ac97_ctrl;
	पूर्णांक ret, i;

	ac97_ctrl = kzalloc(माप(*ac97_ctrl), GFP_KERNEL);
	अगर (!ac97_ctrl)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < AC97_BUS_MAX_CODECS && codecs_pdata; i++)
		ac97_ctrl->codecs_pdata[i] = codecs_pdata[i];

	ac97_ctrl->ops = ops;
	ac97_ctrl->slots_available = slots_available;
	ac97_ctrl->parent = dev;
	ret = ac97_add_adapter(ac97_ctrl);

	अगर (ret)
		जाओ err;
	ac97_bus_reset(ac97_ctrl);
	ac97_bus_scan(ac97_ctrl);

	वापस ac97_ctrl;
err:
	kमुक्त(ac97_ctrl);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_ac97_controller_रेजिस्टर);

/**
 * snd_ac97_controller_unरेजिस्टर - unरेजिस्टर an ac97 controller
 * @ac97_ctrl: the device previously provided to ac97_controller_रेजिस्टर()
 *
 */
व्योम snd_ac97_controller_unरेजिस्टर(काष्ठा ac97_controller *ac97_ctrl)
अणु
	ac97_del_adapter(ac97_ctrl);
पूर्ण
EXPORT_SYMBOL_GPL(snd_ac97_controller_unरेजिस्टर);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ac97_pm_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा ac97_codec_device *codec = to_ac97_device(dev);
	पूर्णांक ret = pm_generic_runसमय_suspend(dev);

	अगर (ret == 0 && dev->driver) अणु
		अगर (pm_runसमय_is_irq_safe(dev))
			clk_disable(codec->clk);
		अन्यथा
			clk_disable_unprepare(codec->clk);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ac97_pm_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा ac97_codec_device *codec = to_ac97_device(dev);
	पूर्णांक ret;

	अगर (dev->driver) अणु
		अगर (pm_runसमय_is_irq_safe(dev))
			ret = clk_enable(codec->clk);
		अन्यथा
			ret = clk_prepare_enable(codec->clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस pm_generic_runसमय_resume(dev);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops ac97_pm = अणु
	.suspend	= pm_generic_suspend,
	.resume		= pm_generic_resume,
	.मुक्तze		= pm_generic_मुक्तze,
	.thaw		= pm_generic_thaw,
	.घातeroff	= pm_generic_घातeroff,
	.restore	= pm_generic_restore,
	SET_RUNTIME_PM_OPS(
		ac97_pm_runसमय_suspend,
		ac97_pm_runसमय_resume,
		शून्य)
पूर्ण;

अटल पूर्णांक ac97_get_enable_clk(काष्ठा ac97_codec_device *adev)
अणु
	पूर्णांक ret;

	adev->clk = clk_get(&adev->dev, "ac97_clk");
	अगर (IS_ERR(adev->clk))
		वापस PTR_ERR(adev->clk);

	ret = clk_prepare_enable(adev->clk);
	अगर (ret)
		clk_put(adev->clk);

	वापस ret;
पूर्ण

अटल व्योम ac97_put_disable_clk(काष्ठा ac97_codec_device *adev)
अणु
	clk_disable_unprepare(adev->clk);
	clk_put(adev->clk);
पूर्ण

अटल sमाप_प्रकार venकरोr_id_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ac97_codec_device *codec = to_ac97_device(dev);

	वापस प्र_लिखो(buf, "%08x", codec->venकरोr_id);
पूर्ण
DEVICE_ATTR_RO(venकरोr_id);

अटल काष्ठा attribute *ac97_dev_attrs[] = अणु
	&dev_attr_venकरोr_id.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ac97_dev);

अटल पूर्णांक ac97_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा ac97_codec_device *adev = to_ac97_device(dev);
	काष्ठा ac97_codec_driver *adrv = to_ac97_driver(drv);
	स्थिर काष्ठा ac97_id *id = adrv->id_table;
	पूर्णांक i = 0;

	अगर (adev->venकरोr_id == 0x0 || adev->venकरोr_id == 0xffffffff)
		वापस false;

	करो अणु
		अगर (ac97_ids_match(id[i].id, adev->venकरोr_id, id[i].mask))
			वापस true;
	पूर्ण जबतक (id[i++].id);

	वापस false;
पूर्ण

अटल पूर्णांक ac97_bus_probe(काष्ठा device *dev)
अणु
	काष्ठा ac97_codec_device *adev = to_ac97_device(dev);
	काष्ठा ac97_codec_driver *adrv = to_ac97_driver(dev->driver);
	पूर्णांक ret;

	ret = ac97_get_enable_clk(adev);
	अगर (ret)
		वापस ret;

	pm_runसमय_get_noresume(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	ret = adrv->probe(adev);
	अगर (ret == 0)
		वापस 0;

	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_put_noidle(dev);
	ac97_put_disable_clk(adev);

	वापस ret;
पूर्ण

अटल पूर्णांक ac97_bus_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा ac97_codec_device *adev = to_ac97_device(dev);
	काष्ठा ac97_codec_driver *adrv = to_ac97_driver(dev->driver);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0)
		वापस ret;

	ret = adrv->हटाओ(adev);
	pm_runसमय_put_noidle(dev);
	अगर (ret == 0)
		ac97_put_disable_clk(adev);

	pm_runसमय_disable(dev);

	वापस ret;
पूर्ण

अटल काष्ठा bus_type ac97_bus_type = अणु
	.name		= "ac97bus",
	.dev_groups	= ac97_dev_groups,
	.match		= ac97_bus_match,
	.pm		= &ac97_pm,
	.probe		= ac97_bus_probe,
	.हटाओ		= ac97_bus_हटाओ,
पूर्ण;

अटल पूर्णांक __init ac97_bus_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&ac97_bus_type);
पूर्ण
subsys_initcall(ac97_bus_init);

अटल व्योम __निकास ac97_bus_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&ac97_bus_type);
पूर्ण
module_निकास(ac97_bus_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Robert Jarzmik <robert.jarzmik@free.fr>");
