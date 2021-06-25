<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2014 - 2020 Intel Corporation */
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/seq_file.h>
#समावेश "adf_accel_devices.h"
#समावेश "adf_cfg.h"
#समावेश "adf_common_drv.h"

अटल DEFINE_MUTEX(qat_cfg_पढ़ो_lock);

अटल व्योम *qat_dev_cfg_start(काष्ठा seq_file *sfile, loff_t *pos)
अणु
	काष्ठा adf_cfg_device_data *dev_cfg = sfile->निजी;

	mutex_lock(&qat_cfg_पढ़ो_lock);
	वापस seq_list_start(&dev_cfg->sec_list, *pos);
पूर्ण

अटल पूर्णांक qat_dev_cfg_show(काष्ठा seq_file *sfile, व्योम *v)
अणु
	काष्ठा list_head *list;
	काष्ठा adf_cfg_section *sec =
				list_entry(v, काष्ठा adf_cfg_section, list);

	seq_म_लिखो(sfile, "[%s]\n", sec->name);
	list_क्रम_each(list, &sec->param_head) अणु
		काष्ठा adf_cfg_key_val *ptr =
			list_entry(list, काष्ठा adf_cfg_key_val, list);
		seq_म_लिखो(sfile, "%s = %s\n", ptr->key, ptr->val);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम *qat_dev_cfg_next(काष्ठा seq_file *sfile, व्योम *v, loff_t *pos)
अणु
	काष्ठा adf_cfg_device_data *dev_cfg = sfile->निजी;

	वापस seq_list_next(v, &dev_cfg->sec_list, pos);
पूर्ण

अटल व्योम qat_dev_cfg_stop(काष्ठा seq_file *sfile, व्योम *v)
अणु
	mutex_unlock(&qat_cfg_पढ़ो_lock);
पूर्ण

अटल स्थिर काष्ठा seq_operations qat_dev_cfg_sops = अणु
	.start = qat_dev_cfg_start,
	.next = qat_dev_cfg_next,
	.stop = qat_dev_cfg_stop,
	.show = qat_dev_cfg_show
पूर्ण;

DEFINE_SEQ_ATTRIBUTE(qat_dev_cfg);

/**
 * adf_cfg_dev_add() - Create an acceleration device configuration table.
 * @accel_dev:  Poपूर्णांकer to acceleration device.
 *
 * Function creates a configuration table क्रम the given acceleration device.
 * The table stores device specअगरic config values.
 * To be used by QAT device specअगरic drivers.
 *
 * Return: 0 on success, error code otherwise.
 */
पूर्णांक adf_cfg_dev_add(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_cfg_device_data *dev_cfg_data;

	dev_cfg_data = kzalloc(माप(*dev_cfg_data), GFP_KERNEL);
	अगर (!dev_cfg_data)
		वापस -ENOMEM;
	INIT_LIST_HEAD(&dev_cfg_data->sec_list);
	init_rwsem(&dev_cfg_data->lock);
	accel_dev->cfg = dev_cfg_data;

	/* accel_dev->debugfs_dir should always be non-शून्य here */
	dev_cfg_data->debug = debugfs_create_file("dev_cfg", S_IRUSR,
						  accel_dev->debugfs_dir,
						  dev_cfg_data,
						  &qat_dev_cfg_fops);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(adf_cfg_dev_add);

अटल व्योम adf_cfg_section_del_all(काष्ठा list_head *head);

व्योम adf_cfg_del_all(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_cfg_device_data *dev_cfg_data = accel_dev->cfg;

	करोwn_ग_लिखो(&dev_cfg_data->lock);
	adf_cfg_section_del_all(&dev_cfg_data->sec_list);
	up_ग_लिखो(&dev_cfg_data->lock);
	clear_bit(ADF_STATUS_CONFIGURED, &accel_dev->status);
पूर्ण

/**
 * adf_cfg_dev_हटाओ() - Clears acceleration device configuration table.
 * @accel_dev:  Poपूर्णांकer to acceleration device.
 *
 * Function हटाओs configuration table from the given acceleration device
 * and मुक्तs all allocated memory.
 * To be used by QAT device specअगरic drivers.
 *
 * Return: व्योम
 */
व्योम adf_cfg_dev_हटाओ(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_cfg_device_data *dev_cfg_data = accel_dev->cfg;

	अगर (!dev_cfg_data)
		वापस;

	करोwn_ग_लिखो(&dev_cfg_data->lock);
	adf_cfg_section_del_all(&dev_cfg_data->sec_list);
	up_ग_लिखो(&dev_cfg_data->lock);
	debugfs_हटाओ(dev_cfg_data->debug);
	kमुक्त(dev_cfg_data);
	accel_dev->cfg = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(adf_cfg_dev_हटाओ);

अटल व्योम adf_cfg_keyval_add(काष्ठा adf_cfg_key_val *new,
			       काष्ठा adf_cfg_section *sec)
अणु
	list_add_tail(&new->list, &sec->param_head);
पूर्ण

अटल व्योम adf_cfg_keyval_del_all(काष्ठा list_head *head)
अणु
	काष्ठा list_head *list_ptr, *पंचांगp;

	list_क्रम_each_prev_safe(list_ptr, पंचांगp, head) अणु
		काष्ठा adf_cfg_key_val *ptr =
			list_entry(list_ptr, काष्ठा adf_cfg_key_val, list);
		list_del(list_ptr);
		kमुक्त(ptr);
	पूर्ण
पूर्ण

अटल व्योम adf_cfg_section_del_all(काष्ठा list_head *head)
अणु
	काष्ठा adf_cfg_section *ptr;
	काष्ठा list_head *list, *पंचांगp;

	list_क्रम_each_prev_safe(list, पंचांगp, head) अणु
		ptr = list_entry(list, काष्ठा adf_cfg_section, list);
		adf_cfg_keyval_del_all(&ptr->param_head);
		list_del(list);
		kमुक्त(ptr);
	पूर्ण
पूर्ण

अटल काष्ठा adf_cfg_key_val *adf_cfg_key_value_find(काष्ठा adf_cfg_section *s,
						      स्थिर अक्षर *key)
अणु
	काष्ठा list_head *list;

	list_क्रम_each(list, &s->param_head) अणु
		काष्ठा adf_cfg_key_val *ptr =
			list_entry(list, काष्ठा adf_cfg_key_val, list);
		अगर (!म_भेद(ptr->key, key))
			वापस ptr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा adf_cfg_section *adf_cfg_sec_find(काष्ठा adf_accel_dev *accel_dev,
						स्थिर अक्षर *sec_name)
अणु
	काष्ठा adf_cfg_device_data *cfg = accel_dev->cfg;
	काष्ठा list_head *list;

	list_क्रम_each(list, &cfg->sec_list) अणु
		काष्ठा adf_cfg_section *ptr =
			list_entry(list, काष्ठा adf_cfg_section, list);
		अगर (!म_भेद(ptr->name, sec_name))
			वापस ptr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक adf_cfg_key_val_get(काष्ठा adf_accel_dev *accel_dev,
			       स्थिर अक्षर *sec_name,
			       स्थिर अक्षर *key_name,
			       अक्षर *val)
अणु
	काष्ठा adf_cfg_section *sec = adf_cfg_sec_find(accel_dev, sec_name);
	काष्ठा adf_cfg_key_val *keyval = शून्य;

	अगर (sec)
		keyval = adf_cfg_key_value_find(sec, key_name);
	अगर (keyval) अणु
		स_नकल(val, keyval->val, ADF_CFG_MAX_VAL_LEN_IN_BYTES);
		वापस 0;
	पूर्ण
	वापस -ENODATA;
पूर्ण

/**
 * adf_cfg_add_key_value_param() - Add key-value config entry to config table.
 * @accel_dev:  Poपूर्णांकer to acceleration device.
 * @section_name: Name of the section where the param will be added
 * @key: The key string
 * @val: Value pain क्रम the given @key
 * @type: Type - string, पूर्णांक or address
 *
 * Function adds configuration key - value entry in the appropriate section
 * in the given acceleration device
 * To be used by QAT device specअगरic drivers.
 *
 * Return: 0 on success, error code otherwise.
 */
पूर्णांक adf_cfg_add_key_value_param(काष्ठा adf_accel_dev *accel_dev,
				स्थिर अक्षर *section_name,
				स्थिर अक्षर *key, स्थिर व्योम *val,
				क्रमागत adf_cfg_val_type type)
अणु
	काष्ठा adf_cfg_device_data *cfg = accel_dev->cfg;
	काष्ठा adf_cfg_key_val *key_val;
	काष्ठा adf_cfg_section *section = adf_cfg_sec_find(accel_dev,
							   section_name);
	अगर (!section)
		वापस -EFAULT;

	key_val = kzalloc(माप(*key_val), GFP_KERNEL);
	अगर (!key_val)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&key_val->list);
	strlcpy(key_val->key, key, माप(key_val->key));

	अगर (type == ADF_DEC) अणु
		snम_लिखो(key_val->val, ADF_CFG_MAX_VAL_LEN_IN_BYTES,
			 "%ld", (*((दीर्घ *)val)));
	पूर्ण अन्यथा अगर (type == ADF_STR) अणु
		strlcpy(key_val->val, (अक्षर *)val, माप(key_val->val));
	पूर्ण अन्यथा अगर (type == ADF_HEX) अणु
		snम_लिखो(key_val->val, ADF_CFG_MAX_VAL_LEN_IN_BYTES,
			 "0x%lx", (अचिन्हित दीर्घ)val);
	पूर्ण अन्यथा अणु
		dev_err(&GET_DEV(accel_dev), "Unknown type given.\n");
		kमुक्त(key_val);
		वापस -EINVAL;
	पूर्ण
	key_val->type = type;
	करोwn_ग_लिखो(&cfg->lock);
	adf_cfg_keyval_add(key_val, section);
	up_ग_लिखो(&cfg->lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(adf_cfg_add_key_value_param);

/**
 * adf_cfg_section_add() - Add config section entry to config table.
 * @accel_dev:  Poपूर्णांकer to acceleration device.
 * @name: Name of the section
 *
 * Function adds configuration section where key - value entries
 * will be stored.
 * To be used by QAT device specअगरic drivers.
 *
 * Return: 0 on success, error code otherwise.
 */
पूर्णांक adf_cfg_section_add(काष्ठा adf_accel_dev *accel_dev, स्थिर अक्षर *name)
अणु
	काष्ठा adf_cfg_device_data *cfg = accel_dev->cfg;
	काष्ठा adf_cfg_section *sec = adf_cfg_sec_find(accel_dev, name);

	अगर (sec)
		वापस 0;

	sec = kzalloc(माप(*sec), GFP_KERNEL);
	अगर (!sec)
		वापस -ENOMEM;

	strlcpy(sec->name, name, माप(sec->name));
	INIT_LIST_HEAD(&sec->param_head);
	करोwn_ग_लिखो(&cfg->lock);
	list_add_tail(&sec->list, &cfg->sec_list);
	up_ग_लिखो(&cfg->lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(adf_cfg_section_add);

पूर्णांक adf_cfg_get_param_value(काष्ठा adf_accel_dev *accel_dev,
			    स्थिर अक्षर *section, स्थिर अक्षर *name,
			    अक्षर *value)
अणु
	काष्ठा adf_cfg_device_data *cfg = accel_dev->cfg;
	पूर्णांक ret;

	करोwn_पढ़ो(&cfg->lock);
	ret = adf_cfg_key_val_get(accel_dev, section, name, value);
	up_पढ़ो(&cfg->lock);
	वापस ret;
पूर्ण
