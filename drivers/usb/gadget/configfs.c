<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/configfs.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/nls.h>
#समावेश <linux/usb/composite.h>
#समावेश <linux/usb/gadget_configfs.h>
#समावेश "configfs.h"
#समावेश "u_f.h"
#समावेश "u_os_desc.h"

पूर्णांक check_user_usb_string(स्थिर अक्षर *name,
		काष्ठा usb_gadget_strings *stringtab_dev)
अणु
	u16 num;
	पूर्णांक ret;

	ret = kstrtou16(name, 0, &num);
	अगर (ret)
		वापस ret;

	अगर (!usb_validate_langid(num))
		वापस -EINVAL;

	stringtab_dev->language = num;
	वापस 0;
पूर्ण

#घोषणा MAX_NAME_LEN	40
#घोषणा MAX_USB_STRING_LANGS 2

अटल स्थिर काष्ठा usb_descriptor_header *otg_desc[2];

काष्ठा gadget_info अणु
	काष्ठा config_group group;
	काष्ठा config_group functions_group;
	काष्ठा config_group configs_group;
	काष्ठा config_group strings_group;
	काष्ठा config_group os_desc_group;

	काष्ठा mutex lock;
	काष्ठा usb_gadget_strings *gstrings[MAX_USB_STRING_LANGS + 1];
	काष्ठा list_head string_list;
	काष्ठा list_head available_func;

	काष्ठा usb_composite_driver composite;
	काष्ठा usb_composite_dev cdev;
	bool use_os_desc;
	अक्षर b_venकरोr_code;
	अक्षर qw_sign[OS_STRING_QW_SIGN_LEN];
	spinlock_t spinlock;
	bool unbind;
पूर्ण;

अटल अंतरभूत काष्ठा gadget_info *to_gadget_info(काष्ठा config_item *item)
अणु
	 वापस container_of(to_config_group(item), काष्ठा gadget_info, group);
पूर्ण

काष्ठा config_usb_cfg अणु
	काष्ठा config_group group;
	काष्ठा config_group strings_group;
	काष्ठा list_head string_list;
	काष्ठा usb_configuration c;
	काष्ठा list_head func_list;
	काष्ठा usb_gadget_strings *gstrings[MAX_USB_STRING_LANGS + 1];
पूर्ण;

अटल अंतरभूत काष्ठा config_usb_cfg *to_config_usb_cfg(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा config_usb_cfg,
			group);
पूर्ण

काष्ठा gadget_strings अणु
	काष्ठा usb_gadget_strings stringtab_dev;
	काष्ठा usb_string strings[USB_GADGET_FIRST_AVAIL_IDX];
	अक्षर *manufacturer;
	अक्षर *product;
	अक्षर *serialnumber;

	काष्ठा config_group group;
	काष्ठा list_head list;
पूर्ण;

काष्ठा os_desc अणु
	काष्ठा config_group group;
पूर्ण;

काष्ठा gadget_config_name अणु
	काष्ठा usb_gadget_strings stringtab_dev;
	काष्ठा usb_string strings;
	अक्षर *configuration;

	काष्ठा config_group group;
	काष्ठा list_head list;
पूर्ण;

#घोषणा USB_MAX_STRING_WITH_शून्य_LEN	(USB_MAX_STRING_LEN+1)

अटल पूर्णांक usb_string_copy(स्थिर अक्षर *s, अक्षर **s_copy)
अणु
	पूर्णांक ret;
	अक्षर *str;
	अक्षर *copy = *s_copy;
	ret = म_माप(s);
	अगर (ret > USB_MAX_STRING_LEN)
		वापस -EOVERFLOW;

	अगर (copy) अणु
		str = copy;
	पूर्ण अन्यथा अणु
		str = kदो_स्मृति(USB_MAX_STRING_WITH_शून्य_LEN, GFP_KERNEL);
		अगर (!str)
			वापस -ENOMEM;
	पूर्ण
	म_नकल(str, s);
	अगर (str[ret - 1] == '\n')
		str[ret - 1] = '\0';
	*s_copy = str;
	वापस 0;
पूर्ण

#घोषणा GI_DEVICE_DESC_SIMPLE_R_u8(__name)	\
अटल sमाप_प्रकार gadget_dev_desc_##__name##_show(काष्ठा config_item *item, \
			अक्षर *page)	\
अणु	\
	वापस प्र_लिखो(page, "0x%02x\n", \
		to_gadget_info(item)->cdev.desc.__name); \
पूर्ण

#घोषणा GI_DEVICE_DESC_SIMPLE_R_u16(__name)	\
अटल sमाप_प्रकार gadget_dev_desc_##__name##_show(काष्ठा config_item *item, \
			अक्षर *page)	\
अणु	\
	वापस प्र_लिखो(page, "0x%04x\n", \
		le16_to_cpup(&to_gadget_info(item)->cdev.desc.__name)); \
पूर्ण


#घोषणा GI_DEVICE_DESC_SIMPLE_W_u8(_name)		\
अटल sमाप_प्रकार gadget_dev_desc_##_name##_store(काष्ठा config_item *item, \
		स्थिर अक्षर *page, माप_प्रकार len)		\
अणु							\
	u8 val;						\
	पूर्णांक ret;					\
	ret = kstrtou8(page, 0, &val);			\
	अगर (ret)					\
		वापस ret;				\
	to_gadget_info(item)->cdev.desc._name = val;	\
	वापस len;					\
पूर्ण

#घोषणा GI_DEVICE_DESC_SIMPLE_W_u16(_name)	\
अटल sमाप_प्रकार gadget_dev_desc_##_name##_store(काष्ठा config_item *item, \
		स्थिर अक्षर *page, माप_प्रकार len)		\
अणु							\
	u16 val;					\
	पूर्णांक ret;					\
	ret = kstrtou16(page, 0, &val);			\
	अगर (ret)					\
		वापस ret;				\
	to_gadget_info(item)->cdev.desc._name = cpu_to_le16p(&val);	\
	वापस len;					\
पूर्ण

#घोषणा GI_DEVICE_DESC_SIMPLE_RW(_name, _type)	\
	GI_DEVICE_DESC_SIMPLE_R_##_type(_name)	\
	GI_DEVICE_DESC_SIMPLE_W_##_type(_name)

GI_DEVICE_DESC_SIMPLE_R_u16(bcdUSB);
GI_DEVICE_DESC_SIMPLE_RW(bDeviceClass, u8);
GI_DEVICE_DESC_SIMPLE_RW(bDeviceSubClass, u8);
GI_DEVICE_DESC_SIMPLE_RW(bDeviceProtocol, u8);
GI_DEVICE_DESC_SIMPLE_RW(bMaxPacketSize0, u8);
GI_DEVICE_DESC_SIMPLE_RW(idVenकरोr, u16);
GI_DEVICE_DESC_SIMPLE_RW(idProduct, u16);
GI_DEVICE_DESC_SIMPLE_R_u16(bcdDevice);

अटल sमाप_प्रकार is_valid_bcd(u16 bcd_val)
अणु
	अगर ((bcd_val & 0xf) > 9)
		वापस -EINVAL;
	अगर (((bcd_val >> 4) & 0xf) > 9)
		वापस -EINVAL;
	अगर (((bcd_val >> 8) & 0xf) > 9)
		वापस -EINVAL;
	अगर (((bcd_val >> 12) & 0xf) > 9)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार gadget_dev_desc_bcdDevice_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार len)
अणु
	u16 bcdDevice;
	पूर्णांक ret;

	ret = kstrtou16(page, 0, &bcdDevice);
	अगर (ret)
		वापस ret;
	ret = is_valid_bcd(bcdDevice);
	अगर (ret)
		वापस ret;

	to_gadget_info(item)->cdev.desc.bcdDevice = cpu_to_le16(bcdDevice);
	वापस len;
पूर्ण

अटल sमाप_प्रकार gadget_dev_desc_bcdUSB_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार len)
अणु
	u16 bcdUSB;
	पूर्णांक ret;

	ret = kstrtou16(page, 0, &bcdUSB);
	अगर (ret)
		वापस ret;
	ret = is_valid_bcd(bcdUSB);
	अगर (ret)
		वापस ret;

	to_gadget_info(item)->cdev.desc.bcdUSB = cpu_to_le16(bcdUSB);
	वापस len;
पूर्ण

अटल sमाप_प्रकार gadget_dev_desc_UDC_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा gadget_info *gi = to_gadget_info(item);
	अक्षर *udc_name;
	पूर्णांक ret;

	mutex_lock(&gi->lock);
	udc_name = gi->composite.gadget_driver.udc_name;
	ret = प्र_लिखो(page, "%s\n", udc_name ?: "");
	mutex_unlock(&gi->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक unरेजिस्टर_gadget(काष्ठा gadget_info *gi)
अणु
	पूर्णांक ret;

	अगर (!gi->composite.gadget_driver.udc_name)
		वापस -ENODEV;

	ret = usb_gadget_unरेजिस्टर_driver(&gi->composite.gadget_driver);
	अगर (ret)
		वापस ret;
	kमुक्त(gi->composite.gadget_driver.udc_name);
	gi->composite.gadget_driver.udc_name = शून्य;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार gadget_dev_desc_UDC_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा gadget_info *gi = to_gadget_info(item);
	अक्षर *name;
	पूर्णांक ret;

	अगर (म_माप(page) < len)
		वापस -EOVERFLOW;

	name = kstrdup(page, GFP_KERNEL);
	अगर (!name)
		वापस -ENOMEM;
	अगर (name[len - 1] == '\n')
		name[len - 1] = '\0';

	mutex_lock(&gi->lock);

	अगर (!म_माप(name)) अणु
		ret = unरेजिस्टर_gadget(gi);
		अगर (ret)
			जाओ err;
		kमुक्त(name);
	पूर्ण अन्यथा अणु
		अगर (gi->composite.gadget_driver.udc_name) अणु
			ret = -EBUSY;
			जाओ err;
		पूर्ण
		gi->composite.gadget_driver.udc_name = name;
		ret = usb_gadget_probe_driver(&gi->composite.gadget_driver);
		अगर (ret) अणु
			gi->composite.gadget_driver.udc_name = शून्य;
			जाओ err;
		पूर्ण
	पूर्ण
	mutex_unlock(&gi->lock);
	वापस len;
err:
	kमुक्त(name);
	mutex_unlock(&gi->lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार gadget_dev_desc_max_speed_show(काष्ठा config_item *item,
					      अक्षर *page)
अणु
	क्रमागत usb_device_speed speed = to_gadget_info(item)->composite.max_speed;

	वापस प्र_लिखो(page, "%s\n", usb_speed_string(speed));
पूर्ण

अटल sमाप_प्रकार gadget_dev_desc_max_speed_store(काष्ठा config_item *item,
					       स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा gadget_info *gi = to_gadget_info(item);

	mutex_lock(&gi->lock);

	/* Prevent changing of max_speed after the driver is binded */
	अगर (gi->composite.gadget_driver.udc_name)
		जाओ err;

	अगर (म_भेदन(page, "super-speed-plus", 16) == 0)
		gi->composite.max_speed = USB_SPEED_SUPER_PLUS;
	अन्यथा अगर (म_भेदन(page, "super-speed", 11) == 0)
		gi->composite.max_speed = USB_SPEED_SUPER;
	अन्यथा अगर (म_भेदन(page, "high-speed", 10) == 0)
		gi->composite.max_speed = USB_SPEED_HIGH;
	अन्यथा अगर (म_भेदन(page, "full-speed", 10) == 0)
		gi->composite.max_speed = USB_SPEED_FULL;
	अन्यथा अगर (म_भेदन(page, "low-speed", 9) == 0)
		gi->composite.max_speed = USB_SPEED_LOW;
	अन्यथा
		जाओ err;

	gi->composite.gadget_driver.max_speed = gi->composite.max_speed;

	mutex_unlock(&gi->lock);
	वापस len;
err:
	mutex_unlock(&gi->lock);
	वापस -EINVAL;
पूर्ण

CONFIGFS_ATTR(gadget_dev_desc_, bDeviceClass);
CONFIGFS_ATTR(gadget_dev_desc_, bDeviceSubClass);
CONFIGFS_ATTR(gadget_dev_desc_, bDeviceProtocol);
CONFIGFS_ATTR(gadget_dev_desc_, bMaxPacketSize0);
CONFIGFS_ATTR(gadget_dev_desc_, idVenकरोr);
CONFIGFS_ATTR(gadget_dev_desc_, idProduct);
CONFIGFS_ATTR(gadget_dev_desc_, bcdDevice);
CONFIGFS_ATTR(gadget_dev_desc_, bcdUSB);
CONFIGFS_ATTR(gadget_dev_desc_, UDC);
CONFIGFS_ATTR(gadget_dev_desc_, max_speed);

अटल काष्ठा configfs_attribute *gadget_root_attrs[] = अणु
	&gadget_dev_desc_attr_bDeviceClass,
	&gadget_dev_desc_attr_bDeviceSubClass,
	&gadget_dev_desc_attr_bDeviceProtocol,
	&gadget_dev_desc_attr_bMaxPacketSize0,
	&gadget_dev_desc_attr_idVenकरोr,
	&gadget_dev_desc_attr_idProduct,
	&gadget_dev_desc_attr_bcdDevice,
	&gadget_dev_desc_attr_bcdUSB,
	&gadget_dev_desc_attr_UDC,
	&gadget_dev_desc_attr_max_speed,
	शून्य,
पूर्ण;

अटल अंतरभूत काष्ठा gadget_strings *to_gadget_strings(काष्ठा config_item *item)
अणु
	 वापस container_of(to_config_group(item), काष्ठा gadget_strings,
			 group);
पूर्ण

अटल अंतरभूत काष्ठा gadget_config_name *to_gadget_config_name(
		काष्ठा config_item *item)
अणु
	 वापस container_of(to_config_group(item), काष्ठा gadget_config_name,
			 group);
पूर्ण

अटल अंतरभूत काष्ठा usb_function_instance *to_usb_function_instance(
		काष्ठा config_item *item)
अणु
	 वापस container_of(to_config_group(item),
			 काष्ठा usb_function_instance, group);
पूर्ण

अटल व्योम gadget_info_attr_release(काष्ठा config_item *item)
अणु
	काष्ठा gadget_info *gi = to_gadget_info(item);

	WARN_ON(!list_empty(&gi->cdev.configs));
	WARN_ON(!list_empty(&gi->string_list));
	WARN_ON(!list_empty(&gi->available_func));
	kमुक्त(gi->composite.gadget_driver.function);
	kमुक्त(gi);
पूर्ण

अटल काष्ठा configfs_item_operations gadget_root_item_ops = अणु
	.release                = gadget_info_attr_release,
पूर्ण;

अटल व्योम gadget_config_attr_release(काष्ठा config_item *item)
अणु
	काष्ठा config_usb_cfg *cfg = to_config_usb_cfg(item);

	WARN_ON(!list_empty(&cfg->c.functions));
	list_del(&cfg->c.list);
	kमुक्त(cfg->c.label);
	kमुक्त(cfg);
पूर्ण

अटल पूर्णांक config_usb_cfg_link(
	काष्ठा config_item *usb_cfg_ci,
	काष्ठा config_item *usb_func_ci)
अणु
	काष्ठा config_usb_cfg *cfg = to_config_usb_cfg(usb_cfg_ci);
	काष्ठा usb_composite_dev *cdev = cfg->c.cdev;
	काष्ठा gadget_info *gi = container_of(cdev, काष्ठा gadget_info, cdev);

	काष्ठा config_group *group = to_config_group(usb_func_ci);
	काष्ठा usb_function_instance *fi = container_of(group,
			काष्ठा usb_function_instance, group);
	काष्ठा usb_function_instance *a_fi;
	काष्ठा usb_function *f;
	पूर्णांक ret;

	mutex_lock(&gi->lock);
	/*
	 * Make sure this function is from within our _this_ gadget and not
	 * from another gadget or a अक्रमom directory.
	 * Also a function instance can only be linked once.
	 */
	list_क्रम_each_entry(a_fi, &gi->available_func, cfs_list) अणु
		अगर (a_fi == fi)
			अवरोध;
	पूर्ण
	अगर (a_fi != fi) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	list_क्रम_each_entry(f, &cfg->func_list, list) अणु
		अगर (f->fi == fi) अणु
			ret = -EEXIST;
			जाओ out;
		पूर्ण
	पूर्ण

	f = usb_get_function(fi);
	अगर (IS_ERR(f)) अणु
		ret = PTR_ERR(f);
		जाओ out;
	पूर्ण

	/* stash the function until we bind it to the gadget */
	list_add_tail(&f->list, &cfg->func_list);
	ret = 0;
out:
	mutex_unlock(&gi->lock);
	वापस ret;
पूर्ण

अटल व्योम config_usb_cfg_unlink(
	काष्ठा config_item *usb_cfg_ci,
	काष्ठा config_item *usb_func_ci)
अणु
	काष्ठा config_usb_cfg *cfg = to_config_usb_cfg(usb_cfg_ci);
	काष्ठा usb_composite_dev *cdev = cfg->c.cdev;
	काष्ठा gadget_info *gi = container_of(cdev, काष्ठा gadget_info, cdev);

	काष्ठा config_group *group = to_config_group(usb_func_ci);
	काष्ठा usb_function_instance *fi = container_of(group,
			काष्ठा usb_function_instance, group);
	काष्ठा usb_function *f;

	/*
	 * ideally I would like to क्रमbid to unlink functions जबतक a gadget is
	 * bound to an UDC. Since this isn't possible at the moment, we simply
	 * क्रमce an unbind, the function is available here and then we can
	 * हटाओ the function.
	 */
	mutex_lock(&gi->lock);
	अगर (gi->composite.gadget_driver.udc_name)
		unरेजिस्टर_gadget(gi);
	WARN_ON(gi->composite.gadget_driver.udc_name);

	list_क्रम_each_entry(f, &cfg->func_list, list) अणु
		अगर (f->fi == fi) अणु
			list_del(&f->list);
			usb_put_function(f);
			mutex_unlock(&gi->lock);
			वापस;
		पूर्ण
	पूर्ण
	mutex_unlock(&gi->lock);
	WARN(1, "Unable to locate function to unbind\n");
पूर्ण

अटल काष्ठा configfs_item_operations gadget_config_item_ops = अणु
	.release                = gadget_config_attr_release,
	.allow_link             = config_usb_cfg_link,
	.drop_link              = config_usb_cfg_unlink,
पूर्ण;


अटल sमाप_प्रकार gadget_config_desc_MaxPower_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", to_config_usb_cfg(item)->c.MaxPower);
पूर्ण

अटल sमाप_प्रकार gadget_config_desc_MaxPower_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार len)
अणु
	u16 val;
	पूर्णांक ret;
	ret = kstrtou16(page, 0, &val);
	अगर (ret)
		वापस ret;
	अगर (DIV_ROUND_UP(val, 8) > 0xff)
		वापस -दुस्फल;
	to_config_usb_cfg(item)->c.MaxPower = val;
	वापस len;
पूर्ण

अटल sमाप_प्रकार gadget_config_desc_bmAttributes_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस प्र_लिखो(page, "0x%02x\n",
		to_config_usb_cfg(item)->c.bmAttributes);
पूर्ण

अटल sमाप_प्रकार gadget_config_desc_bmAttributes_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार len)
अणु
	u8 val;
	पूर्णांक ret;
	ret = kstrtou8(page, 0, &val);
	अगर (ret)
		वापस ret;
	अगर (!(val & USB_CONFIG_ATT_ONE))
		वापस -EINVAL;
	अगर (val & ~(USB_CONFIG_ATT_ONE | USB_CONFIG_ATT_SELFPOWER |
				USB_CONFIG_ATT_WAKEUP))
		वापस -EINVAL;
	to_config_usb_cfg(item)->c.bmAttributes = val;
	वापस len;
पूर्ण

CONFIGFS_ATTR(gadget_config_desc_, MaxPower);
CONFIGFS_ATTR(gadget_config_desc_, bmAttributes);

अटल काष्ठा configfs_attribute *gadget_config_attrs[] = अणु
	&gadget_config_desc_attr_MaxPower,
	&gadget_config_desc_attr_bmAttributes,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type gadget_config_type = अणु
	.ct_item_ops	= &gadget_config_item_ops,
	.ct_attrs	= gadget_config_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा config_item_type gadget_root_type = अणु
	.ct_item_ops	= &gadget_root_item_ops,
	.ct_attrs	= gadget_root_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल व्योम composite_init_dev(काष्ठा usb_composite_dev *cdev)
अणु
	spin_lock_init(&cdev->lock);
	INIT_LIST_HEAD(&cdev->configs);
	INIT_LIST_HEAD(&cdev->gstrings);
पूर्ण

अटल काष्ठा config_group *function_make(
		काष्ठा config_group *group,
		स्थिर अक्षर *name)
अणु
	काष्ठा gadget_info *gi;
	काष्ठा usb_function_instance *fi;
	अक्षर buf[MAX_NAME_LEN];
	अक्षर *func_name;
	अक्षर *instance_name;
	पूर्णांक ret;

	ret = snम_लिखो(buf, MAX_NAME_LEN, "%s", name);
	अगर (ret >= MAX_NAME_LEN)
		वापस ERR_PTR(-ENAMETOOLONG);

	func_name = buf;
	instance_name = म_अक्षर(func_name, '.');
	अगर (!instance_name) अणु
		pr_err("Unable to locate . in FUNC.INSTANCE\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	*instance_name = '\0';
	instance_name++;

	fi = usb_get_function_instance(func_name);
	अगर (IS_ERR(fi))
		वापस ERR_CAST(fi);

	ret = config_item_set_name(&fi->group.cg_item, "%s", name);
	अगर (ret) अणु
		usb_put_function_instance(fi);
		वापस ERR_PTR(ret);
	पूर्ण
	अगर (fi->set_inst_name) अणु
		ret = fi->set_inst_name(fi, instance_name);
		अगर (ret) अणु
			usb_put_function_instance(fi);
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण

	gi = container_of(group, काष्ठा gadget_info, functions_group);

	mutex_lock(&gi->lock);
	list_add_tail(&fi->cfs_list, &gi->available_func);
	mutex_unlock(&gi->lock);
	वापस &fi->group;
पूर्ण

अटल व्योम function_drop(
		काष्ठा config_group *group,
		काष्ठा config_item *item)
अणु
	काष्ठा usb_function_instance *fi = to_usb_function_instance(item);
	काष्ठा gadget_info *gi;

	gi = container_of(group, काष्ठा gadget_info, functions_group);

	mutex_lock(&gi->lock);
	list_del(&fi->cfs_list);
	mutex_unlock(&gi->lock);
	config_item_put(item);
पूर्ण

अटल काष्ठा configfs_group_operations functions_ops = अणु
	.make_group     = &function_make,
	.drop_item      = &function_drop,
पूर्ण;

अटल स्थिर काष्ठा config_item_type functions_type = अणु
	.ct_group_ops   = &functions_ops,
	.ct_owner       = THIS_MODULE,
पूर्ण;

GS_STRINGS_RW(gadget_config_name, configuration);

अटल काष्ठा configfs_attribute *gadget_config_name_langid_attrs[] = अणु
	&gadget_config_name_attr_configuration,
	शून्य,
पूर्ण;

अटल व्योम gadget_config_name_attr_release(काष्ठा config_item *item)
अणु
	काष्ठा gadget_config_name *cn = to_gadget_config_name(item);

	kमुक्त(cn->configuration);

	list_del(&cn->list);
	kमुक्त(cn);
पूर्ण

USB_CONFIG_STRING_RW_OPS(gadget_config_name);
USB_CONFIG_STRINGS_LANG(gadget_config_name, config_usb_cfg);

अटल काष्ठा config_group *config_desc_make(
		काष्ठा config_group *group,
		स्थिर अक्षर *name)
अणु
	काष्ठा gadget_info *gi;
	काष्ठा config_usb_cfg *cfg;
	अक्षर buf[MAX_NAME_LEN];
	अक्षर *num_str;
	u8 num;
	पूर्णांक ret;

	gi = container_of(group, काष्ठा gadget_info, configs_group);
	ret = snम_लिखो(buf, MAX_NAME_LEN, "%s", name);
	अगर (ret >= MAX_NAME_LEN)
		वापस ERR_PTR(-ENAMETOOLONG);

	num_str = म_अक्षर(buf, '.');
	अगर (!num_str) अणु
		pr_err("Unable to locate . in name.bConfigurationValue\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	*num_str = '\0';
	num_str++;

	अगर (!म_माप(buf))
		वापस ERR_PTR(-EINVAL);

	ret = kstrtou8(num_str, 0, &num);
	अगर (ret)
		वापस ERR_PTR(ret);

	cfg = kzalloc(माप(*cfg), GFP_KERNEL);
	अगर (!cfg)
		वापस ERR_PTR(-ENOMEM);
	cfg->c.label = kstrdup(buf, GFP_KERNEL);
	अगर (!cfg->c.label) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	cfg->c.bConfigurationValue = num;
	cfg->c.MaxPower = CONFIG_USB_GADGET_VBUS_DRAW;
	cfg->c.bmAttributes = USB_CONFIG_ATT_ONE;
	INIT_LIST_HEAD(&cfg->string_list);
	INIT_LIST_HEAD(&cfg->func_list);

	config_group_init_type_name(&cfg->group, name,
				&gadget_config_type);

	config_group_init_type_name(&cfg->strings_group, "strings",
			&gadget_config_name_strings_type);
	configfs_add_शेष_group(&cfg->strings_group, &cfg->group);

	ret = usb_add_config_only(&gi->cdev, &cfg->c);
	अगर (ret)
		जाओ err;

	वापस &cfg->group;
err:
	kमुक्त(cfg->c.label);
	kमुक्त(cfg);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम config_desc_drop(
		काष्ठा config_group *group,
		काष्ठा config_item *item)
अणु
	config_item_put(item);
पूर्ण

अटल काष्ठा configfs_group_operations config_desc_ops = अणु
	.make_group     = &config_desc_make,
	.drop_item      = &config_desc_drop,
पूर्ण;

अटल स्थिर काष्ठा config_item_type config_desc_type = अणु
	.ct_group_ops   = &config_desc_ops,
	.ct_owner       = THIS_MODULE,
पूर्ण;

GS_STRINGS_RW(gadget_strings, manufacturer);
GS_STRINGS_RW(gadget_strings, product);
GS_STRINGS_RW(gadget_strings, serialnumber);

अटल काष्ठा configfs_attribute *gadget_strings_langid_attrs[] = अणु
	&gadget_strings_attr_manufacturer,
	&gadget_strings_attr_product,
	&gadget_strings_attr_serialnumber,
	शून्य,
पूर्ण;

अटल व्योम gadget_strings_attr_release(काष्ठा config_item *item)
अणु
	काष्ठा gadget_strings *gs = to_gadget_strings(item);

	kमुक्त(gs->manufacturer);
	kमुक्त(gs->product);
	kमुक्त(gs->serialnumber);

	list_del(&gs->list);
	kमुक्त(gs);
पूर्ण

USB_CONFIG_STRING_RW_OPS(gadget_strings);
USB_CONFIG_STRINGS_LANG(gadget_strings, gadget_info);

अटल अंतरभूत काष्ठा os_desc *to_os_desc(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा os_desc, group);
पूर्ण

अटल अंतरभूत काष्ठा gadget_info *os_desc_item_to_gadget_info(
		काष्ठा config_item *item)
अणु
	वापस to_gadget_info(to_os_desc(item)->group.cg_item.ci_parent);
पूर्ण

अटल sमाप_प्रकार os_desc_use_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n",
			os_desc_item_to_gadget_info(item)->use_os_desc);
पूर्ण

अटल sमाप_प्रकार os_desc_use_store(काष्ठा config_item *item, स्थिर अक्षर *page,
				 माप_प्रकार len)
अणु
	काष्ठा gadget_info *gi = os_desc_item_to_gadget_info(item);
	पूर्णांक ret;
	bool use;

	mutex_lock(&gi->lock);
	ret = strtobool(page, &use);
	अगर (!ret) अणु
		gi->use_os_desc = use;
		ret = len;
	पूर्ण
	mutex_unlock(&gi->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार os_desc_b_venकरोr_code_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "0x%02x\n",
			os_desc_item_to_gadget_info(item)->b_venकरोr_code);
पूर्ण

अटल sमाप_प्रकार os_desc_b_venकरोr_code_store(काष्ठा config_item *item,
					   स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा gadget_info *gi = os_desc_item_to_gadget_info(item);
	पूर्णांक ret;
	u8 b_venकरोr_code;

	mutex_lock(&gi->lock);
	ret = kstrtou8(page, 0, &b_venकरोr_code);
	अगर (!ret) अणु
		gi->b_venकरोr_code = b_venकरोr_code;
		ret = len;
	पूर्ण
	mutex_unlock(&gi->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार os_desc_qw_sign_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा gadget_info *gi = os_desc_item_to_gadget_info(item);
	पूर्णांक res;

	res = utf16s_to_utf8s((ब_अक्षर_प्रकार *) gi->qw_sign, OS_STRING_QW_SIGN_LEN,
			      UTF16_LITTLE_ENDIAN, page, PAGE_SIZE - 1);
	page[res++] = '\n';

	वापस res;
पूर्ण

अटल sमाप_प्रकार os_desc_qw_sign_store(काष्ठा config_item *item, स्थिर अक्षर *page,
				     माप_प्रकार len)
अणु
	काष्ठा gadget_info *gi = os_desc_item_to_gadget_info(item);
	पूर्णांक res, l;

	l = min((पूर्णांक)len, OS_STRING_QW_SIGN_LEN >> 1);
	अगर (page[l - 1] == '\n')
		--l;

	mutex_lock(&gi->lock);
	res = utf8s_to_utf16s(page, l,
			      UTF16_LITTLE_ENDIAN, (ब_अक्षर_प्रकार *) gi->qw_sign,
			      OS_STRING_QW_SIGN_LEN);
	अगर (res > 0)
		res = len;
	mutex_unlock(&gi->lock);

	वापस res;
पूर्ण

CONFIGFS_ATTR(os_desc_, use);
CONFIGFS_ATTR(os_desc_, b_venकरोr_code);
CONFIGFS_ATTR(os_desc_, qw_sign);

अटल काष्ठा configfs_attribute *os_desc_attrs[] = अणु
	&os_desc_attr_use,
	&os_desc_attr_b_venकरोr_code,
	&os_desc_attr_qw_sign,
	शून्य,
पूर्ण;

अटल व्योम os_desc_attr_release(काष्ठा config_item *item)
अणु
	काष्ठा os_desc *os_desc = to_os_desc(item);
	kमुक्त(os_desc);
पूर्ण

अटल पूर्णांक os_desc_link(काष्ठा config_item *os_desc_ci,
			काष्ठा config_item *usb_cfg_ci)
अणु
	काष्ठा gadget_info *gi = container_of(to_config_group(os_desc_ci),
					काष्ठा gadget_info, os_desc_group);
	काष्ठा usb_composite_dev *cdev = &gi->cdev;
	काष्ठा config_usb_cfg *c_target =
		container_of(to_config_group(usb_cfg_ci),
			     काष्ठा config_usb_cfg, group);
	काष्ठा usb_configuration *c;
	पूर्णांक ret;

	mutex_lock(&gi->lock);
	list_क्रम_each_entry(c, &cdev->configs, list) अणु
		अगर (c == &c_target->c)
			अवरोध;
	पूर्ण
	अगर (c != &c_target->c) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (cdev->os_desc_config) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	cdev->os_desc_config = &c_target->c;
	ret = 0;

out:
	mutex_unlock(&gi->lock);
	वापस ret;
पूर्ण

अटल व्योम os_desc_unlink(काष्ठा config_item *os_desc_ci,
			  काष्ठा config_item *usb_cfg_ci)
अणु
	काष्ठा gadget_info *gi = container_of(to_config_group(os_desc_ci),
					काष्ठा gadget_info, os_desc_group);
	काष्ठा usb_composite_dev *cdev = &gi->cdev;

	mutex_lock(&gi->lock);
	अगर (gi->composite.gadget_driver.udc_name)
		unरेजिस्टर_gadget(gi);
	cdev->os_desc_config = शून्य;
	WARN_ON(gi->composite.gadget_driver.udc_name);
	mutex_unlock(&gi->lock);
पूर्ण

अटल काष्ठा configfs_item_operations os_desc_ops = अणु
	.release                = os_desc_attr_release,
	.allow_link		= os_desc_link,
	.drop_link		= os_desc_unlink,
पूर्ण;

अटल काष्ठा config_item_type os_desc_type = अणु
	.ct_item_ops	= &os_desc_ops,
	.ct_attrs	= os_desc_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल अंतरभूत काष्ठा usb_os_desc_ext_prop
*to_usb_os_desc_ext_prop(काष्ठा config_item *item)
अणु
	वापस container_of(item, काष्ठा usb_os_desc_ext_prop, item);
पूर्ण

अटल sमाप_प्रकार ext_prop_type_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n", to_usb_os_desc_ext_prop(item)->type);
पूर्ण

अटल sमाप_प्रकार ext_prop_type_store(काष्ठा config_item *item,
				   स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा usb_os_desc_ext_prop *ext_prop = to_usb_os_desc_ext_prop(item);
	काष्ठा usb_os_desc *desc = to_usb_os_desc(ext_prop->item.ci_parent);
	u8 type;
	पूर्णांक ret;

	अगर (desc->opts_mutex)
		mutex_lock(desc->opts_mutex);
	ret = kstrtou8(page, 0, &type);
	अगर (ret)
		जाओ end;
	अगर (type < USB_EXT_PROP_UNICODE || type > USB_EXT_PROP_UNICODE_MULTI) अणु
		ret = -EINVAL;
		जाओ end;
	पूर्ण

	अगर ((ext_prop->type == USB_EXT_PROP_BINARY ||
	    ext_prop->type == USB_EXT_PROP_LE32 ||
	    ext_prop->type == USB_EXT_PROP_BE32) &&
	    (type == USB_EXT_PROP_UNICODE ||
	    type == USB_EXT_PROP_UNICODE_ENV ||
	    type == USB_EXT_PROP_UNICODE_LINK))
		ext_prop->data_len <<= 1;
	अन्यथा अगर ((ext_prop->type == USB_EXT_PROP_UNICODE ||
		   ext_prop->type == USB_EXT_PROP_UNICODE_ENV ||
		   ext_prop->type == USB_EXT_PROP_UNICODE_LINK) &&
		   (type == USB_EXT_PROP_BINARY ||
		   type == USB_EXT_PROP_LE32 ||
		   type == USB_EXT_PROP_BE32))
		ext_prop->data_len >>= 1;
	ext_prop->type = type;
	ret = len;

end:
	अगर (desc->opts_mutex)
		mutex_unlock(desc->opts_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ext_prop_data_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा usb_os_desc_ext_prop *ext_prop = to_usb_os_desc_ext_prop(item);
	पूर्णांक len = ext_prop->data_len;

	अगर (ext_prop->type == USB_EXT_PROP_UNICODE ||
	    ext_prop->type == USB_EXT_PROP_UNICODE_ENV ||
	    ext_prop->type == USB_EXT_PROP_UNICODE_LINK)
		len >>= 1;
	स_नकल(page, ext_prop->data, len);

	वापस len;
पूर्ण

अटल sमाप_प्रकार ext_prop_data_store(काष्ठा config_item *item,
				   स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा usb_os_desc_ext_prop *ext_prop = to_usb_os_desc_ext_prop(item);
	काष्ठा usb_os_desc *desc = to_usb_os_desc(ext_prop->item.ci_parent);
	अक्षर *new_data;
	माप_प्रकार ret_len = len;

	अगर (page[len - 1] == '\n' || page[len - 1] == '\0')
		--len;
	new_data = kmemdup(page, len, GFP_KERNEL);
	अगर (!new_data)
		वापस -ENOMEM;

	अगर (desc->opts_mutex)
		mutex_lock(desc->opts_mutex);
	kमुक्त(ext_prop->data);
	ext_prop->data = new_data;
	desc->ext_prop_len -= ext_prop->data_len;
	ext_prop->data_len = len;
	desc->ext_prop_len += ext_prop->data_len;
	अगर (ext_prop->type == USB_EXT_PROP_UNICODE ||
	    ext_prop->type == USB_EXT_PROP_UNICODE_ENV ||
	    ext_prop->type == USB_EXT_PROP_UNICODE_LINK) अणु
		desc->ext_prop_len -= ext_prop->data_len;
		ext_prop->data_len <<= 1;
		ext_prop->data_len += 2;
		desc->ext_prop_len += ext_prop->data_len;
	पूर्ण
	अगर (desc->opts_mutex)
		mutex_unlock(desc->opts_mutex);
	वापस ret_len;
पूर्ण

CONFIGFS_ATTR(ext_prop_, type);
CONFIGFS_ATTR(ext_prop_, data);

अटल काष्ठा configfs_attribute *ext_prop_attrs[] = अणु
	&ext_prop_attr_type,
	&ext_prop_attr_data,
	शून्य,
पूर्ण;

अटल व्योम usb_os_desc_ext_prop_release(काष्ठा config_item *item)
अणु
	काष्ठा usb_os_desc_ext_prop *ext_prop = to_usb_os_desc_ext_prop(item);

	kमुक्त(ext_prop); /* मुक्तs a whole chunk */
पूर्ण

अटल काष्ठा configfs_item_operations ext_prop_ops = अणु
	.release		= usb_os_desc_ext_prop_release,
पूर्ण;

अटल काष्ठा config_item *ext_prop_make(
		काष्ठा config_group *group,
		स्थिर अक्षर *name)
अणु
	काष्ठा usb_os_desc_ext_prop *ext_prop;
	काष्ठा config_item_type *ext_prop_type;
	काष्ठा usb_os_desc *desc;
	अक्षर *vlabuf;

	vla_group(data_chunk);
	vla_item(data_chunk, काष्ठा usb_os_desc_ext_prop, ext_prop, 1);
	vla_item(data_chunk, काष्ठा config_item_type, ext_prop_type, 1);

	vlabuf = kzalloc(vla_group_size(data_chunk), GFP_KERNEL);
	अगर (!vlabuf)
		वापस ERR_PTR(-ENOMEM);

	ext_prop = vla_ptr(vlabuf, data_chunk, ext_prop);
	ext_prop_type = vla_ptr(vlabuf, data_chunk, ext_prop_type);

	desc = container_of(group, काष्ठा usb_os_desc, group);
	ext_prop_type->ct_item_ops = &ext_prop_ops;
	ext_prop_type->ct_attrs = ext_prop_attrs;
	ext_prop_type->ct_owner = desc->owner;

	config_item_init_type_name(&ext_prop->item, name, ext_prop_type);

	ext_prop->name = kstrdup(name, GFP_KERNEL);
	अगर (!ext_prop->name) अणु
		kमुक्त(vlabuf);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	desc->ext_prop_len += 14;
	ext_prop->name_len = 2 * म_माप(ext_prop->name) + 2;
	अगर (desc->opts_mutex)
		mutex_lock(desc->opts_mutex);
	desc->ext_prop_len += ext_prop->name_len;
	list_add_tail(&ext_prop->entry, &desc->ext_prop);
	++desc->ext_prop_count;
	अगर (desc->opts_mutex)
		mutex_unlock(desc->opts_mutex);

	वापस &ext_prop->item;
पूर्ण

अटल व्योम ext_prop_drop(काष्ठा config_group *group, काष्ठा config_item *item)
अणु
	काष्ठा usb_os_desc_ext_prop *ext_prop = to_usb_os_desc_ext_prop(item);
	काष्ठा usb_os_desc *desc = to_usb_os_desc(&group->cg_item);

	अगर (desc->opts_mutex)
		mutex_lock(desc->opts_mutex);
	list_del(&ext_prop->entry);
	--desc->ext_prop_count;
	kमुक्त(ext_prop->name);
	desc->ext_prop_len -= (ext_prop->name_len + ext_prop->data_len + 14);
	अगर (desc->opts_mutex)
		mutex_unlock(desc->opts_mutex);
	config_item_put(item);
पूर्ण

अटल काष्ठा configfs_group_operations पूर्णांकerf_grp_ops = अणु
	.make_item	= &ext_prop_make,
	.drop_item	= &ext_prop_drop,
पूर्ण;

अटल sमाप_प्रकार पूर्णांकerf_grp_compatible_id_show(काष्ठा config_item *item,
					     अक्षर *page)
अणु
	स_नकल(page, to_usb_os_desc(item)->ext_compat_id, 8);
	वापस 8;
पूर्ण

अटल sमाप_प्रकार पूर्णांकerf_grp_compatible_id_store(काष्ठा config_item *item,
					      स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा usb_os_desc *desc = to_usb_os_desc(item);
	पूर्णांक l;

	l = min_t(पूर्णांक, 8, len);
	अगर (page[l - 1] == '\n')
		--l;
	अगर (desc->opts_mutex)
		mutex_lock(desc->opts_mutex);
	स_नकल(desc->ext_compat_id, page, l);

	अगर (desc->opts_mutex)
		mutex_unlock(desc->opts_mutex);

	वापस len;
पूर्ण

अटल sमाप_प्रकार पूर्णांकerf_grp_sub_compatible_id_show(काष्ठा config_item *item,
						 अक्षर *page)
अणु
	स_नकल(page, to_usb_os_desc(item)->ext_compat_id + 8, 8);
	वापस 8;
पूर्ण

अटल sमाप_प्रकार पूर्णांकerf_grp_sub_compatible_id_store(काष्ठा config_item *item,
						  स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा usb_os_desc *desc = to_usb_os_desc(item);
	पूर्णांक l;

	l = min_t(पूर्णांक, 8, len);
	अगर (page[l - 1] == '\n')
		--l;
	अगर (desc->opts_mutex)
		mutex_lock(desc->opts_mutex);
	स_नकल(desc->ext_compat_id + 8, page, l);

	अगर (desc->opts_mutex)
		mutex_unlock(desc->opts_mutex);

	वापस len;
पूर्ण

CONFIGFS_ATTR(पूर्णांकerf_grp_, compatible_id);
CONFIGFS_ATTR(पूर्णांकerf_grp_, sub_compatible_id);

अटल काष्ठा configfs_attribute *पूर्णांकerf_grp_attrs[] = अणु
	&पूर्णांकerf_grp_attr_compatible_id,
	&पूर्णांकerf_grp_attr_sub_compatible_id,
	शून्य
पूर्ण;

काष्ठा config_group *usb_os_desc_prepare_पूर्णांकerf_dir(
		काष्ठा config_group *parent,
		पूर्णांक n_पूर्णांकerf,
		काष्ठा usb_os_desc **desc,
		अक्षर **names,
		काष्ठा module *owner)
अणु
	काष्ठा config_group *os_desc_group;
	काष्ठा config_item_type *os_desc_type, *पूर्णांकerface_type;

	vla_group(data_chunk);
	vla_item(data_chunk, काष्ठा config_group, os_desc_group, 1);
	vla_item(data_chunk, काष्ठा config_item_type, os_desc_type, 1);
	vla_item(data_chunk, काष्ठा config_item_type, पूर्णांकerface_type, 1);

	अक्षर *vlabuf = kzalloc(vla_group_size(data_chunk), GFP_KERNEL);
	अगर (!vlabuf)
		वापस ERR_PTR(-ENOMEM);

	os_desc_group = vla_ptr(vlabuf, data_chunk, os_desc_group);
	os_desc_type = vla_ptr(vlabuf, data_chunk, os_desc_type);
	पूर्णांकerface_type = vla_ptr(vlabuf, data_chunk, पूर्णांकerface_type);

	os_desc_type->ct_owner = owner;
	config_group_init_type_name(os_desc_group, "os_desc", os_desc_type);
	configfs_add_शेष_group(os_desc_group, parent);

	पूर्णांकerface_type->ct_group_ops = &पूर्णांकerf_grp_ops;
	पूर्णांकerface_type->ct_attrs = पूर्णांकerf_grp_attrs;
	पूर्णांकerface_type->ct_owner = owner;

	जबतक (n_पूर्णांकerf--) अणु
		काष्ठा usb_os_desc *d;

		d = desc[n_पूर्णांकerf];
		d->owner = owner;
		config_group_init_type_name(&d->group, "", पूर्णांकerface_type);
		config_item_set_name(&d->group.cg_item, "interface.%s",
				     names[n_पूर्णांकerf]);
		configfs_add_शेष_group(&d->group, os_desc_group);
	पूर्ण

	वापस os_desc_group;
पूर्ण
EXPORT_SYMBOL(usb_os_desc_prepare_पूर्णांकerf_dir);

अटल पूर्णांक configfs_करो_nothing(काष्ठा usb_composite_dev *cdev)
अणु
	WARN_ON(1);
	वापस -EINVAL;
पूर्ण

पूर्णांक composite_dev_prepare(काष्ठा usb_composite_driver *composite,
		काष्ठा usb_composite_dev *dev);

पूर्णांक composite_os_desc_req_prepare(काष्ठा usb_composite_dev *cdev,
				  काष्ठा usb_ep *ep0);

अटल व्योम purge_configs_funcs(काष्ठा gadget_info *gi)
अणु
	काष्ठा usb_configuration	*c;

	list_क्रम_each_entry(c, &gi->cdev.configs, list) अणु
		काष्ठा usb_function *f, *पंचांगp;
		काष्ठा config_usb_cfg *cfg;

		cfg = container_of(c, काष्ठा config_usb_cfg, c);

		list_क्रम_each_entry_safe_reverse(f, पंचांगp, &c->functions, list) अणु

			list_move(&f->list, &cfg->func_list);
			अगर (f->unbind) अणु
				dev_dbg(&gi->cdev.gadget->dev,
					"unbind function '%s'/%p\n",
					f->name, f);
				f->unbind(c, f);
			पूर्ण
		पूर्ण
		c->next_पूर्णांकerface_id = 0;
		स_रखो(c->पूर्णांकerface, 0, माप(c->पूर्णांकerface));
		c->superspeed_plus = 0;
		c->superspeed = 0;
		c->highspeed = 0;
		c->fullspeed = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक configfs_composite_bind(काष्ठा usb_gadget *gadget,
		काष्ठा usb_gadget_driver *gdriver)
अणु
	काष्ठा usb_composite_driver     *composite = to_cdriver(gdriver);
	काष्ठा gadget_info		*gi = container_of(composite,
						काष्ठा gadget_info, composite);
	काष्ठा usb_composite_dev	*cdev = &gi->cdev;
	काष्ठा usb_configuration	*c;
	काष्ठा usb_string		*s;
	अचिन्हित			i;
	पूर्णांक				ret;

	/* the gi->lock is hold by the caller */
	gi->unbind = 0;
	cdev->gadget = gadget;
	set_gadget_data(gadget, cdev);
	ret = composite_dev_prepare(composite, cdev);
	अगर (ret)
		वापस ret;
	/* and now the gadget bind */
	ret = -EINVAL;

	अगर (list_empty(&gi->cdev.configs)) अणु
		pr_err("Need at least one configuration in %s.\n",
				gi->composite.name);
		जाओ err_comp_cleanup;
	पूर्ण


	list_क्रम_each_entry(c, &gi->cdev.configs, list) अणु
		काष्ठा config_usb_cfg *cfg;

		cfg = container_of(c, काष्ठा config_usb_cfg, c);
		अगर (list_empty(&cfg->func_list)) अणु
			pr_err("Config %s/%d of %s needs at least one function.\n",
			      c->label, c->bConfigurationValue,
			      gi->composite.name);
			जाओ err_comp_cleanup;
		पूर्ण
	पूर्ण

	/* init all strings */
	अगर (!list_empty(&gi->string_list)) अणु
		काष्ठा gadget_strings *gs;

		i = 0;
		list_क्रम_each_entry(gs, &gi->string_list, list) अणु

			gi->gstrings[i] = &gs->stringtab_dev;
			gs->stringtab_dev.strings = gs->strings;
			gs->strings[USB_GADGET_MANUFACTURER_IDX].s =
				gs->manufacturer;
			gs->strings[USB_GADGET_PRODUCT_IDX].s = gs->product;
			gs->strings[USB_GADGET_SERIAL_IDX].s = gs->serialnumber;
			i++;
		पूर्ण
		gi->gstrings[i] = शून्य;
		s = usb_gstrings_attach(&gi->cdev, gi->gstrings,
				USB_GADGET_FIRST_AVAIL_IDX);
		अगर (IS_ERR(s)) अणु
			ret = PTR_ERR(s);
			जाओ err_comp_cleanup;
		पूर्ण

		gi->cdev.desc.iManufacturer = s[USB_GADGET_MANUFACTURER_IDX].id;
		gi->cdev.desc.iProduct = s[USB_GADGET_PRODUCT_IDX].id;
		gi->cdev.desc.iSerialNumber = s[USB_GADGET_SERIAL_IDX].id;
	पूर्ण

	अगर (gi->use_os_desc) अणु
		cdev->use_os_string = true;
		cdev->b_venकरोr_code = gi->b_venकरोr_code;
		स_नकल(cdev->qw_sign, gi->qw_sign, OS_STRING_QW_SIGN_LEN);
	पूर्ण

	अगर (gadget_is_otg(gadget) && !otg_desc[0]) अणु
		काष्ठा usb_descriptor_header *usb_desc;

		usb_desc = usb_otg_descriptor_alloc(gadget);
		अगर (!usb_desc) अणु
			ret = -ENOMEM;
			जाओ err_comp_cleanup;
		पूर्ण
		usb_otg_descriptor_init(gadget, usb_desc);
		otg_desc[0] = usb_desc;
		otg_desc[1] = शून्य;
	पूर्ण

	/* Go through all configs, attach all functions */
	list_क्रम_each_entry(c, &gi->cdev.configs, list) अणु
		काष्ठा config_usb_cfg *cfg;
		काष्ठा usb_function *f;
		काष्ठा usb_function *पंचांगp;
		काष्ठा gadget_config_name *cn;

		अगर (gadget_is_otg(gadget))
			c->descriptors = otg_desc;

		cfg = container_of(c, काष्ठा config_usb_cfg, c);
		अगर (!list_empty(&cfg->string_list)) अणु
			i = 0;
			list_क्रम_each_entry(cn, &cfg->string_list, list) अणु
				cfg->gstrings[i] = &cn->stringtab_dev;
				cn->stringtab_dev.strings = &cn->strings;
				cn->strings.s = cn->configuration;
				i++;
			पूर्ण
			cfg->gstrings[i] = शून्य;
			s = usb_gstrings_attach(&gi->cdev, cfg->gstrings, 1);
			अगर (IS_ERR(s)) अणु
				ret = PTR_ERR(s);
				जाओ err_comp_cleanup;
			पूर्ण
			c->iConfiguration = s[0].id;
		पूर्ण

		list_क्रम_each_entry_safe(f, पंचांगp, &cfg->func_list, list) अणु
			list_del(&f->list);
			ret = usb_add_function(c, f);
			अगर (ret) अणु
				list_add(&f->list, &cfg->func_list);
				जाओ err_purge_funcs;
			पूर्ण
		पूर्ण
		usb_ep_स्वतःconfig_reset(cdev->gadget);
	पूर्ण
	अगर (cdev->use_os_string) अणु
		ret = composite_os_desc_req_prepare(cdev, gadget->ep0);
		अगर (ret)
			जाओ err_purge_funcs;
	पूर्ण

	usb_ep_स्वतःconfig_reset(cdev->gadget);
	वापस 0;

err_purge_funcs:
	purge_configs_funcs(gi);
err_comp_cleanup:
	composite_dev_cleanup(cdev);
	वापस ret;
पूर्ण

अटल व्योम configfs_composite_unbind(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा usb_composite_dev	*cdev;
	काष्ठा gadget_info		*gi;
	अचिन्हित दीर्घ flags;

	/* the gi->lock is hold by the caller */

	cdev = get_gadget_data(gadget);
	gi = container_of(cdev, काष्ठा gadget_info, cdev);
	spin_lock_irqsave(&gi->spinlock, flags);
	gi->unbind = 1;
	spin_unlock_irqrestore(&gi->spinlock, flags);

	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;
	purge_configs_funcs(gi);
	composite_dev_cleanup(cdev);
	usb_ep_स्वतःconfig_reset(cdev->gadget);
	spin_lock_irqsave(&gi->spinlock, flags);
	cdev->gadget = शून्य;
	set_gadget_data(gadget, शून्य);
	spin_unlock_irqrestore(&gi->spinlock, flags);
पूर्ण

अटल पूर्णांक configfs_composite_setup(काष्ठा usb_gadget *gadget,
		स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा usb_composite_dev *cdev;
	काष्ठा gadget_info *gi;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	cdev = get_gadget_data(gadget);
	अगर (!cdev)
		वापस 0;

	gi = container_of(cdev, काष्ठा gadget_info, cdev);
	spin_lock_irqsave(&gi->spinlock, flags);
	cdev = get_gadget_data(gadget);
	अगर (!cdev || gi->unbind) अणु
		spin_unlock_irqrestore(&gi->spinlock, flags);
		वापस 0;
	पूर्ण

	ret = composite_setup(gadget, ctrl);
	spin_unlock_irqrestore(&gi->spinlock, flags);
	वापस ret;
पूर्ण

अटल व्योम configfs_composite_disconnect(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा usb_composite_dev *cdev;
	काष्ठा gadget_info *gi;
	अचिन्हित दीर्घ flags;

	cdev = get_gadget_data(gadget);
	अगर (!cdev)
		वापस;

	gi = container_of(cdev, काष्ठा gadget_info, cdev);
	spin_lock_irqsave(&gi->spinlock, flags);
	cdev = get_gadget_data(gadget);
	अगर (!cdev || gi->unbind) अणु
		spin_unlock_irqrestore(&gi->spinlock, flags);
		वापस;
	पूर्ण

	composite_disconnect(gadget);
	spin_unlock_irqrestore(&gi->spinlock, flags);
पूर्ण

अटल व्योम configfs_composite_reset(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा usb_composite_dev *cdev;
	काष्ठा gadget_info *gi;
	अचिन्हित दीर्घ flags;

	cdev = get_gadget_data(gadget);
	अगर (!cdev)
		वापस;

	gi = container_of(cdev, काष्ठा gadget_info, cdev);
	spin_lock_irqsave(&gi->spinlock, flags);
	cdev = get_gadget_data(gadget);
	अगर (!cdev || gi->unbind) अणु
		spin_unlock_irqrestore(&gi->spinlock, flags);
		वापस;
	पूर्ण

	composite_reset(gadget);
	spin_unlock_irqrestore(&gi->spinlock, flags);
पूर्ण

अटल व्योम configfs_composite_suspend(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा usb_composite_dev *cdev;
	काष्ठा gadget_info *gi;
	अचिन्हित दीर्घ flags;

	cdev = get_gadget_data(gadget);
	अगर (!cdev)
		वापस;

	gi = container_of(cdev, काष्ठा gadget_info, cdev);
	spin_lock_irqsave(&gi->spinlock, flags);
	cdev = get_gadget_data(gadget);
	अगर (!cdev || gi->unbind) अणु
		spin_unlock_irqrestore(&gi->spinlock, flags);
		वापस;
	पूर्ण

	composite_suspend(gadget);
	spin_unlock_irqrestore(&gi->spinlock, flags);
पूर्ण

अटल व्योम configfs_composite_resume(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा usb_composite_dev *cdev;
	काष्ठा gadget_info *gi;
	अचिन्हित दीर्घ flags;

	cdev = get_gadget_data(gadget);
	अगर (!cdev)
		वापस;

	gi = container_of(cdev, काष्ठा gadget_info, cdev);
	spin_lock_irqsave(&gi->spinlock, flags);
	cdev = get_gadget_data(gadget);
	अगर (!cdev || gi->unbind) अणु
		spin_unlock_irqrestore(&gi->spinlock, flags);
		वापस;
	पूर्ण

	composite_resume(gadget);
	spin_unlock_irqrestore(&gi->spinlock, flags);
पूर्ण

अटल स्थिर काष्ठा usb_gadget_driver configfs_driver_ढाँचा = अणु
	.bind           = configfs_composite_bind,
	.unbind         = configfs_composite_unbind,

	.setup          = configfs_composite_setup,
	.reset          = configfs_composite_reset,
	.disconnect     = configfs_composite_disconnect,

	.suspend	= configfs_composite_suspend,
	.resume		= configfs_composite_resume,

	.max_speed	= USB_SPEED_SUPER_PLUS,
	.driver = अणु
		.owner          = THIS_MODULE,
		.name		= "configfs-gadget",
	पूर्ण,
	.match_existing_only = 1,
पूर्ण;

अटल काष्ठा config_group *gadमाला_लो_make(
		काष्ठा config_group *group,
		स्थिर अक्षर *name)
अणु
	काष्ठा gadget_info *gi;

	gi = kzalloc(माप(*gi), GFP_KERNEL);
	अगर (!gi)
		वापस ERR_PTR(-ENOMEM);

	config_group_init_type_name(&gi->group, name, &gadget_root_type);

	config_group_init_type_name(&gi->functions_group, "functions",
			&functions_type);
	configfs_add_शेष_group(&gi->functions_group, &gi->group);

	config_group_init_type_name(&gi->configs_group, "configs",
			&config_desc_type);
	configfs_add_शेष_group(&gi->configs_group, &gi->group);

	config_group_init_type_name(&gi->strings_group, "strings",
			&gadget_strings_strings_type);
	configfs_add_शेष_group(&gi->strings_group, &gi->group);

	config_group_init_type_name(&gi->os_desc_group, "os_desc",
			&os_desc_type);
	configfs_add_शेष_group(&gi->os_desc_group, &gi->group);

	gi->composite.bind = configfs_करो_nothing;
	gi->composite.unbind = configfs_करो_nothing;
	gi->composite.suspend = शून्य;
	gi->composite.resume = शून्य;
	gi->composite.max_speed = USB_SPEED_SUPER_PLUS;

	spin_lock_init(&gi->spinlock);
	mutex_init(&gi->lock);
	INIT_LIST_HEAD(&gi->string_list);
	INIT_LIST_HEAD(&gi->available_func);

	composite_init_dev(&gi->cdev);
	gi->cdev.desc.bLength = USB_DT_DEVICE_SIZE;
	gi->cdev.desc.bDescriptorType = USB_DT_DEVICE;
	gi->cdev.desc.bcdDevice = cpu_to_le16(get_शेष_bcdDevice());

	gi->composite.gadget_driver = configfs_driver_ढाँचा;

	gi->composite.gadget_driver.function = kstrdup(name, GFP_KERNEL);
	gi->composite.name = gi->composite.gadget_driver.function;

	अगर (!gi->composite.gadget_driver.function)
		जाओ err;

	वापस &gi->group;
err:
	kमुक्त(gi);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल व्योम gadमाला_लो_drop(काष्ठा config_group *group, काष्ठा config_item *item)
अणु
	config_item_put(item);
पूर्ण

अटल काष्ठा configfs_group_operations gadमाला_लो_ops = अणु
	.make_group     = &gadमाला_लो_make,
	.drop_item      = &gadमाला_लो_drop,
पूर्ण;

अटल स्थिर काष्ठा config_item_type gadमाला_लो_type = अणु
	.ct_group_ops   = &gadमाला_लो_ops,
	.ct_owner       = THIS_MODULE,
पूर्ण;

अटल काष्ठा configfs_subप्रणाली gadget_subsys = अणु
	.su_group = अणु
		.cg_item = अणु
			.ci_namebuf = "usb_gadget",
			.ci_type = &gadमाला_लो_type,
		पूर्ण,
	पूर्ण,
	.su_mutex = __MUTEX_INITIALIZER(gadget_subsys.su_mutex),
पूर्ण;

व्योम unरेजिस्टर_gadget_item(काष्ठा config_item *item)
अणु
	काष्ठा gadget_info *gi = to_gadget_info(item);

	mutex_lock(&gi->lock);
	unरेजिस्टर_gadget(gi);
	mutex_unlock(&gi->lock);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_gadget_item);

अटल पूर्णांक __init gadget_cfs_init(व्योम)
अणु
	पूर्णांक ret;

	config_group_init(&gadget_subsys.su_group);

	ret = configfs_रेजिस्टर_subप्रणाली(&gadget_subsys);
	वापस ret;
पूर्ण
module_init(gadget_cfs_init);

अटल व्योम __निकास gadget_cfs_निकास(व्योम)
अणु
	configfs_unरेजिस्टर_subप्रणाली(&gadget_subsys);
पूर्ण
module_निकास(gadget_cfs_निकास);
