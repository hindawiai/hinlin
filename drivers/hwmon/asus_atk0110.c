<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007-2009 Luca Tettamanti <kronos.it@gmail.com>
 *
 * See COPYING in the top level directory of the kernel tree.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/debugfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/dmi.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/err.h>
#समावेश <linux/acpi.h>

#घोषणा ATK_HID "ATK0110"

अटल bool new_अगर;
module_param(new_अगर, bool, 0);
MODULE_PARM_DESC(new_अगर, "Override detection heuristic and force the use of the new ATK0110 interface");

अटल स्थिर काष्ठा dmi_प्रणाली_id __initस्थिर atk_क्रमce_new_अगर[] = अणु
	अणु
		/* Old पूर्णांकerface has broken MCH temp monitoring */
		.ident = "Asus Sabertooth X58",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "SABERTOOTH X58")
		पूर्ण
	पूर्ण, अणु
		/* Old पूर्णांकerface पढ़ोs the same sensor क्रम fan0 and fan1 */
		.ident = "Asus M5A78L",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "M5A78L")
		पूर्ण
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/*
 * Minimum समय between पढ़ोings, enक्रमced in order to aव्योम
 * hogging the CPU.
 */
#घोषणा CACHE_TIME		HZ

#घोषणा BOARD_ID		"MBIF"
#घोषणा METHOD_ENUMERATE	"GGRP"
#घोषणा METHOD_READ		"GITM"
#घोषणा METHOD_WRITE		"SITM"
#घोषणा METHOD_OLD_READ_TMP	"RTMP"
#घोषणा METHOD_OLD_READ_VLT	"RVLT"
#घोषणा METHOD_OLD_READ_FAN	"RFAN"
#घोषणा METHOD_OLD_ENUM_TMP	"TSIF"
#घोषणा METHOD_OLD_ENUM_VLT	"VSIF"
#घोषणा METHOD_OLD_ENUM_FAN	"FSIF"

#घोषणा ATK_MUX_HWMON		0x00000006ULL
#घोषणा ATK_MUX_MGMT		0x00000011ULL

#घोषणा ATK_CLASS_MASK		0xff000000ULL
#घोषणा ATK_CLASS_FREQ_CTL	0x03000000ULL
#घोषणा ATK_CLASS_FAN_CTL	0x04000000ULL
#घोषणा ATK_CLASS_HWMON		0x06000000ULL
#घोषणा ATK_CLASS_MGMT		0x11000000ULL

#घोषणा ATK_TYPE_MASK		0x00ff0000ULL
#घोषणा HWMON_TYPE_VOLT		0x00020000ULL
#घोषणा HWMON_TYPE_TEMP		0x00030000ULL
#घोषणा HWMON_TYPE_FAN		0x00040000ULL

#घोषणा ATK_ELEMENT_ID_MASK	0x0000ffffULL

#घोषणा ATK_EC_ID		0x11060004ULL

क्रमागत atk_pack_member अणु
	HWMON_PACK_FLAGS,
	HWMON_PACK_NAME,
	HWMON_PACK_LIMIT1,
	HWMON_PACK_LIMIT2,
	HWMON_PACK_ENABLE
पूर्ण;

/* New package क्रमmat */
#घोषणा _HWMON_NEW_PACK_SIZE	7
#घोषणा _HWMON_NEW_PACK_FLAGS	0
#घोषणा _HWMON_NEW_PACK_NAME	1
#घोषणा _HWMON_NEW_PACK_UNK1	2
#घोषणा _HWMON_NEW_PACK_UNK2	3
#घोषणा _HWMON_NEW_PACK_LIMIT1	4
#घोषणा _HWMON_NEW_PACK_LIMIT2	5
#घोषणा _HWMON_NEW_PACK_ENABLE	6

/* Old package क्रमmat */
#घोषणा _HWMON_OLD_PACK_SIZE	5
#घोषणा _HWMON_OLD_PACK_FLAGS	0
#घोषणा _HWMON_OLD_PACK_NAME	1
#घोषणा _HWMON_OLD_PACK_LIMIT1	2
#घोषणा _HWMON_OLD_PACK_LIMIT2	3
#घोषणा _HWMON_OLD_PACK_ENABLE	4


काष्ठा atk_data अणु
	काष्ठा device *hwmon_dev;
	acpi_handle atk_handle;
	काष्ठा acpi_device *acpi_dev;

	bool old_पूर्णांकerface;

	/* old पूर्णांकerface */
	acpi_handle rपंचांगp_handle;
	acpi_handle rvlt_handle;
	acpi_handle rfan_handle;
	/* new पूर्णांकerface */
	acpi_handle क्रमागतerate_handle;
	acpi_handle पढ़ो_handle;
	acpi_handle ग_लिखो_handle;

	bool disable_ec;

	पूर्णांक voltage_count;
	पूर्णांक temperature_count;
	पूर्णांक fan_count;
	काष्ठा list_head sensor_list;
	काष्ठा attribute_group attr_group;
	स्थिर काष्ठा attribute_group *attr_groups[2];

	काष्ठा अणु
		काष्ठा dentry *root;
		u32 id;
	पूर्ण debugfs;
पूर्ण;


प्रकार sमाप_प्रकार (*sysfs_show_func)(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf);

अटल स्थिर काष्ठा acpi_device_id atk_ids[] = अणु
	अणुATK_HID, 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, atk_ids);

#घोषणा ATTR_NAME_SIZE 16 /* Worst हाल is "tempN_input" */

काष्ठा atk_sensor_data अणु
	काष्ठा list_head list;
	काष्ठा atk_data *data;
	काष्ठा device_attribute label_attr;
	काष्ठा device_attribute input_attr;
	काष्ठा device_attribute limit1_attr;
	काष्ठा device_attribute limit2_attr;
	अक्षर label_attr_name[ATTR_NAME_SIZE];
	अक्षर input_attr_name[ATTR_NAME_SIZE];
	अक्षर limit1_attr_name[ATTR_NAME_SIZE];
	अक्षर limit2_attr_name[ATTR_NAME_SIZE];
	u64 id;
	u64 type;
	u64 limit1;
	u64 limit2;
	u64 cached_value;
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */
	bool is_valid;
	अक्षर स्थिर *acpi_name;
पूर्ण;

/*
 * Return buffer क्रमmat:
 * [0-3] "value" is valid flag
 * [4-7] value
 * [8- ] unknown stuff on newer mobos
 */
काष्ठा atk_acpi_ret_buffer अणु
	u32 flags;
	u32 value;
	u8 data[];
पूर्ण;

/* Input buffer used क्रम GITM and SITM methods */
काष्ठा atk_acpi_input_buf अणु
	u32 id;
	u32 param1;
	u32 param2;
पूर्ण;

अटल पूर्णांक atk_add(काष्ठा acpi_device *device);
अटल पूर्णांक atk_हटाओ(काष्ठा acpi_device *device);
अटल व्योम atk_prपूर्णांक_sensor(काष्ठा atk_data *data, जोड़ acpi_object *obj);
अटल पूर्णांक atk_पढ़ो_value(काष्ठा atk_sensor_data *sensor, u64 *value);

अटल काष्ठा acpi_driver atk_driver = अणु
	.name	= ATK_HID,
	.class	= "hwmon",
	.ids	= atk_ids,
	.ops	= अणु
		.add	= atk_add,
		.हटाओ	= atk_हटाओ,
	पूर्ण,
पूर्ण;

#घोषणा input_to_atk_sensor(attr) \
	container_of(attr, काष्ठा atk_sensor_data, input_attr)

#घोषणा label_to_atk_sensor(attr) \
	container_of(attr, काष्ठा atk_sensor_data, label_attr)

#घोषणा limit1_to_atk_sensor(attr) \
	container_of(attr, काष्ठा atk_sensor_data, limit1_attr)

#घोषणा limit2_to_atk_sensor(attr) \
	container_of(attr, काष्ठा atk_sensor_data, limit2_attr)

अटल sमाप_प्रकार atk_input_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा atk_sensor_data *s = input_to_atk_sensor(attr);
	u64 value;
	पूर्णांक err;

	err = atk_पढ़ो_value(s, &value);
	अगर (err)
		वापस err;

	अगर (s->type == HWMON_TYPE_TEMP)
		/* ACPI वापसs decidegree */
		value *= 100;

	वापस प्र_लिखो(buf, "%llu\n", value);
पूर्ण

अटल sमाप_प्रकार atk_label_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा atk_sensor_data *s = label_to_atk_sensor(attr);

	वापस प्र_लिखो(buf, "%s\n", s->acpi_name);
पूर्ण

अटल sमाप_प्रकार atk_limit1_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा atk_sensor_data *s = limit1_to_atk_sensor(attr);
	u64 value = s->limit1;

	अगर (s->type == HWMON_TYPE_TEMP)
		value *= 100;

	वापस प्र_लिखो(buf, "%lld\n", value);
पूर्ण

अटल sमाप_प्रकार atk_limit2_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा atk_sensor_data *s = limit2_to_atk_sensor(attr);
	u64 value = s->limit2;

	अगर (s->type == HWMON_TYPE_TEMP)
		value *= 100;

	वापस प्र_लिखो(buf, "%lld\n", value);
पूर्ण

अटल व्योम atk_init_attribute(काष्ठा device_attribute *attr, अक्षर *name,
		sysfs_show_func show)
अणु
	sysfs_attr_init(&attr->attr);
	attr->attr.name = name;
	attr->attr.mode = 0444;
	attr->show = show;
	attr->store = शून्य;
पूर्ण


अटल जोड़ acpi_object *atk_get_pack_member(काष्ठा atk_data *data,
						जोड़ acpi_object *pack,
						क्रमागत atk_pack_member m)
अणु
	bool old_अगर = data->old_पूर्णांकerface;
	पूर्णांक offset;

	चयन (m) अणु
	हाल HWMON_PACK_FLAGS:
		offset = old_अगर ? _HWMON_OLD_PACK_FLAGS : _HWMON_NEW_PACK_FLAGS;
		अवरोध;
	हाल HWMON_PACK_NAME:
		offset = old_अगर ? _HWMON_OLD_PACK_NAME : _HWMON_NEW_PACK_NAME;
		अवरोध;
	हाल HWMON_PACK_LIMIT1:
		offset = old_अगर ? _HWMON_OLD_PACK_LIMIT1 :
				  _HWMON_NEW_PACK_LIMIT1;
		अवरोध;
	हाल HWMON_PACK_LIMIT2:
		offset = old_अगर ? _HWMON_OLD_PACK_LIMIT2 :
				  _HWMON_NEW_PACK_LIMIT2;
		अवरोध;
	हाल HWMON_PACK_ENABLE:
		offset = old_अगर ? _HWMON_OLD_PACK_ENABLE :
				  _HWMON_NEW_PACK_ENABLE;
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण

	वापस &pack->package.elements[offset];
पूर्ण


/*
 * New package क्रमmat is:
 * - flag (पूर्णांक)
 *	class - used क्रम de-muxing the request to the correct GITn
 *	type (volt, temp, fan)
 *	sensor id |
 *	sensor id - used क्रम de-muxing the request _inside_ the GITn
 * - name (str)
 * - unknown (पूर्णांक)
 * - unknown (पूर्णांक)
 * - limit1 (पूर्णांक)
 * - limit2 (पूर्णांक)
 * - enable (पूर्णांक)
 *
 * The old package has the same क्रमmat but it's missing the two unknown fields.
 */
अटल पूर्णांक validate_hwmon_pack(काष्ठा atk_data *data, जोड़ acpi_object *obj)
अणु
	काष्ठा device *dev = &data->acpi_dev->dev;
	जोड़ acpi_object *पंचांगp;
	bool old_अगर = data->old_पूर्णांकerface;
	पूर्णांक स्थिर expected_size = old_अगर ? _HWMON_OLD_PACK_SIZE :
					   _HWMON_NEW_PACK_SIZE;

	अगर (obj->type != ACPI_TYPE_PACKAGE) अणु
		dev_warn(dev, "Invalid type: %d\n", obj->type);
		वापस -EINVAL;
	पूर्ण

	अगर (obj->package.count != expected_size) अणु
		dev_warn(dev, "Invalid package size: %d, expected: %d\n",
				obj->package.count, expected_size);
		वापस -EINVAL;
	पूर्ण

	पंचांगp = atk_get_pack_member(data, obj, HWMON_PACK_FLAGS);
	अगर (पंचांगp->type != ACPI_TYPE_INTEGER) अणु
		dev_warn(dev, "Invalid type (flag): %d\n", पंचांगp->type);
		वापस -EINVAL;
	पूर्ण

	पंचांगp = atk_get_pack_member(data, obj, HWMON_PACK_NAME);
	अगर (पंचांगp->type != ACPI_TYPE_STRING) अणु
		dev_warn(dev, "Invalid type (name): %d\n", पंचांगp->type);
		वापस -EINVAL;
	पूर्ण

	/* Don't check... we don't know what they're useful क्रम anyway */
#अगर 0
	पंचांगp = &obj->package.elements[HWMON_PACK_UNK1];
	अगर (पंचांगp->type != ACPI_TYPE_INTEGER) अणु
		dev_warn(dev, "Invalid type (unk1): %d\n", पंचांगp->type);
		वापस -EINVAL;
	पूर्ण

	पंचांगp = &obj->package.elements[HWMON_PACK_UNK2];
	अगर (पंचांगp->type != ACPI_TYPE_INTEGER) अणु
		dev_warn(dev, "Invalid type (unk2): %d\n", पंचांगp->type);
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर

	पंचांगp = atk_get_pack_member(data, obj, HWMON_PACK_LIMIT1);
	अगर (पंचांगp->type != ACPI_TYPE_INTEGER) अणु
		dev_warn(dev, "Invalid type (limit1): %d\n", पंचांगp->type);
		वापस -EINVAL;
	पूर्ण

	पंचांगp = atk_get_pack_member(data, obj, HWMON_PACK_LIMIT2);
	अगर (पंचांगp->type != ACPI_TYPE_INTEGER) अणु
		dev_warn(dev, "Invalid type (limit2): %d\n", पंचांगp->type);
		वापस -EINVAL;
	पूर्ण

	पंचांगp = atk_get_pack_member(data, obj, HWMON_PACK_ENABLE);
	अगर (पंचांगp->type != ACPI_TYPE_INTEGER) अणु
		dev_warn(dev, "Invalid type (enable): %d\n", पंचांगp->type);
		वापस -EINVAL;
	पूर्ण

	atk_prपूर्णांक_sensor(data, obj);

	वापस 0;
पूर्ण

#अगर_घोषित DEBUG
अटल अक्षर स्थिर *atk_sensor_type(जोड़ acpi_object *flags)
अणु
	u64 type = flags->पूर्णांकeger.value & ATK_TYPE_MASK;
	अक्षर स्थिर *what;

	चयन (type) अणु
	हाल HWMON_TYPE_VOLT:
		what = "voltage";
		अवरोध;
	हाल HWMON_TYPE_TEMP:
		what = "temperature";
		अवरोध;
	हाल HWMON_TYPE_FAN:
		what = "fan";
		अवरोध;
	शेष:
		what = "unknown";
		अवरोध;
	पूर्ण

	वापस what;
पूर्ण
#पूर्ण_अगर

अटल व्योम atk_prपूर्णांक_sensor(काष्ठा atk_data *data, जोड़ acpi_object *obj)
अणु
#अगर_घोषित DEBUG
	काष्ठा device *dev = &data->acpi_dev->dev;
	जोड़ acpi_object *flags;
	जोड़ acpi_object *name;
	जोड़ acpi_object *limit1;
	जोड़ acpi_object *limit2;
	जोड़ acpi_object *enable;
	अक्षर स्थिर *what;

	flags = atk_get_pack_member(data, obj, HWMON_PACK_FLAGS);
	name = atk_get_pack_member(data, obj, HWMON_PACK_NAME);
	limit1 = atk_get_pack_member(data, obj, HWMON_PACK_LIMIT1);
	limit2 = atk_get_pack_member(data, obj, HWMON_PACK_LIMIT2);
	enable = atk_get_pack_member(data, obj, HWMON_PACK_ENABLE);

	what = atk_sensor_type(flags);

	dev_dbg(dev, "%s: %#llx %s [%llu-%llu] %s\n", what,
			flags->पूर्णांकeger.value,
			name->string.poपूर्णांकer,
			limit1->पूर्णांकeger.value, limit2->पूर्णांकeger.value,
			enable->पूर्णांकeger.value ? "enabled" : "disabled");
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक atk_पढ़ो_value_old(काष्ठा atk_sensor_data *sensor, u64 *value)
अणु
	काष्ठा atk_data *data = sensor->data;
	काष्ठा device *dev = &data->acpi_dev->dev;
	काष्ठा acpi_object_list params;
	जोड़ acpi_object id;
	acpi_status status;
	acpi_handle method;

	चयन (sensor->type) अणु
	हाल HWMON_TYPE_VOLT:
		method = data->rvlt_handle;
		अवरोध;
	हाल HWMON_TYPE_TEMP:
		method = data->rपंचांगp_handle;
		अवरोध;
	हाल HWMON_TYPE_FAN:
		method = data->rfan_handle;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	id.type = ACPI_TYPE_INTEGER;
	id.पूर्णांकeger.value = sensor->id;

	params.count = 1;
	params.poपूर्णांकer = &id;

	status = acpi_evaluate_पूर्णांकeger(method, शून्य, &params, value);
	अगर (status != AE_OK) अणु
		dev_warn(dev, "%s: ACPI exception: %s\n", __func__,
				acpi_क्रमmat_exception(status));
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल जोड़ acpi_object *atk_ggrp(काष्ठा atk_data *data, u16 mux)
अणु
	काष्ठा device *dev = &data->acpi_dev->dev;
	काष्ठा acpi_buffer buf;
	acpi_status ret;
	काष्ठा acpi_object_list params;
	जोड़ acpi_object id;
	जोड़ acpi_object *pack;

	id.type = ACPI_TYPE_INTEGER;
	id.पूर्णांकeger.value = mux;
	params.count = 1;
	params.poपूर्णांकer = &id;

	buf.length = ACPI_ALLOCATE_BUFFER;
	ret = acpi_evaluate_object(data->क्रमागतerate_handle, शून्य, &params, &buf);
	अगर (ret != AE_OK) अणु
		dev_err(dev, "GGRP[%#x] ACPI exception: %s\n", mux,
				acpi_क्रमmat_exception(ret));
		वापस ERR_PTR(-EIO);
	पूर्ण
	pack = buf.poपूर्णांकer;
	अगर (pack->type != ACPI_TYPE_PACKAGE) अणु
		/* Execution was successful, but the id was not found */
		ACPI_FREE(pack);
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	अगर (pack->package.count < 1) अणु
		dev_err(dev, "GGRP[%#x] package is too small\n", mux);
		ACPI_FREE(pack);
		वापस ERR_PTR(-EIO);
	पूर्ण
	वापस pack;
पूर्ण

अटल जोड़ acpi_object *atk_giपंचांग(काष्ठा atk_data *data, u64 id)
अणु
	काष्ठा device *dev = &data->acpi_dev->dev;
	काष्ठा atk_acpi_input_buf buf;
	जोड़ acpi_object पंचांगp;
	काष्ठा acpi_object_list params;
	काष्ठा acpi_buffer ret;
	जोड़ acpi_object *obj;
	acpi_status status;

	buf.id = id;
	buf.param1 = 0;
	buf.param2 = 0;

	पंचांगp.type = ACPI_TYPE_BUFFER;
	पंचांगp.buffer.poपूर्णांकer = (u8 *)&buf;
	पंचांगp.buffer.length = माप(buf);

	params.count = 1;
	params.poपूर्णांकer = (व्योम *)&पंचांगp;

	ret.length = ACPI_ALLOCATE_BUFFER;
	status = acpi_evaluate_object_typed(data->पढ़ो_handle, शून्य, &params,
			&ret, ACPI_TYPE_BUFFER);
	अगर (status != AE_OK) अणु
		dev_warn(dev, "GITM[%#llx] ACPI exception: %s\n", id,
				acpi_क्रमmat_exception(status));
		वापस ERR_PTR(-EIO);
	पूर्ण
	obj = ret.poपूर्णांकer;

	/* Sanity check */
	अगर (obj->buffer.length < 8) अणु
		dev_warn(dev, "Unexpected ASBF length: %u\n",
				obj->buffer.length);
		ACPI_FREE(obj);
		वापस ERR_PTR(-EIO);
	पूर्ण
	वापस obj;
पूर्ण

अटल जोड़ acpi_object *atk_siपंचांग(काष्ठा atk_data *data,
		काष्ठा atk_acpi_input_buf *buf)
अणु
	काष्ठा device *dev = &data->acpi_dev->dev;
	काष्ठा acpi_object_list params;
	जोड़ acpi_object पंचांगp;
	काष्ठा acpi_buffer ret;
	जोड़ acpi_object *obj;
	acpi_status status;

	पंचांगp.type = ACPI_TYPE_BUFFER;
	पंचांगp.buffer.poपूर्णांकer = (u8 *)buf;
	पंचांगp.buffer.length = माप(*buf);

	params.count = 1;
	params.poपूर्णांकer = &पंचांगp;

	ret.length = ACPI_ALLOCATE_BUFFER;
	status = acpi_evaluate_object_typed(data->ग_लिखो_handle, शून्य, &params,
			&ret, ACPI_TYPE_BUFFER);
	अगर (status != AE_OK) अणु
		dev_warn(dev, "SITM[%#x] ACPI exception: %s\n", buf->id,
				acpi_क्रमmat_exception(status));
		वापस ERR_PTR(-EIO);
	पूर्ण
	obj = ret.poपूर्णांकer;

	/* Sanity check */
	अगर (obj->buffer.length < 8) अणु
		dev_warn(dev, "Unexpected ASBF length: %u\n",
				obj->buffer.length);
		ACPI_FREE(obj);
		वापस ERR_PTR(-EIO);
	पूर्ण
	वापस obj;
पूर्ण

अटल पूर्णांक atk_पढ़ो_value_new(काष्ठा atk_sensor_data *sensor, u64 *value)
अणु
	काष्ठा atk_data *data = sensor->data;
	काष्ठा device *dev = &data->acpi_dev->dev;
	जोड़ acpi_object *obj;
	काष्ठा atk_acpi_ret_buffer *buf;
	पूर्णांक err = 0;

	obj = atk_giपंचांग(data, sensor->id);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	buf = (काष्ठा atk_acpi_ret_buffer *)obj->buffer.poपूर्णांकer;
	अगर (buf->flags == 0) अणु
		/*
		 * The पढ़ोing is not valid, possible causes:
		 * - sensor failure
		 * - क्रमागतeration was FUBAR (and we didn't notice)
		 */
		dev_warn(dev, "Read failed, sensor = %#llx\n", sensor->id);
		err = -EIO;
		जाओ out;
	पूर्ण

	*value = buf->value;
out:
	ACPI_FREE(obj);
	वापस err;
पूर्ण

अटल पूर्णांक atk_पढ़ो_value(काष्ठा atk_sensor_data *sensor, u64 *value)
अणु
	पूर्णांक err;

	अगर (!sensor->is_valid ||
	    समय_after(jअगरfies, sensor->last_updated + CACHE_TIME)) अणु
		अगर (sensor->data->old_पूर्णांकerface)
			err = atk_पढ़ो_value_old(sensor, value);
		अन्यथा
			err = atk_पढ़ो_value_new(sensor, value);

		अगर (err)
			वापस err;

		sensor->is_valid = true;
		sensor->last_updated = jअगरfies;
		sensor->cached_value = *value;
	पूर्ण अन्यथा अणु
		*value = sensor->cached_value;
		err = 0;
	पूर्ण

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक atk_debugfs_giपंचांग_get(व्योम *p, u64 *val)
अणु
	काष्ठा atk_data *data = p;
	जोड़ acpi_object *ret;
	काष्ठा atk_acpi_ret_buffer *buf;
	पूर्णांक err = 0;

	अगर (!data->पढ़ो_handle)
		वापस -ENODEV;

	अगर (!data->debugfs.id)
		वापस -EINVAL;

	ret = atk_giपंचांग(data, data->debugfs.id);
	अगर (IS_ERR(ret))
		वापस PTR_ERR(ret);

	buf = (काष्ठा atk_acpi_ret_buffer *)ret->buffer.poपूर्णांकer;
	अगर (buf->flags)
		*val = buf->value;
	अन्यथा
		err = -EIO;

	ACPI_FREE(ret);
	वापस err;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(atk_debugfs_giपंचांग, atk_debugfs_giपंचांग_get, शून्य,
			 "0x%08llx\n");

अटल पूर्णांक atk_acpi_prपूर्णांक(अक्षर *buf, माप_प्रकार sz, जोड़ acpi_object *obj)
अणु
	पूर्णांक ret = 0;

	चयन (obj->type) अणु
	हाल ACPI_TYPE_INTEGER:
		ret = snम_लिखो(buf, sz, "0x%08llx\n", obj->पूर्णांकeger.value);
		अवरोध;
	हाल ACPI_TYPE_STRING:
		ret = snम_लिखो(buf, sz, "%s\n", obj->string.poपूर्णांकer);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम atk_pack_prपूर्णांक(अक्षर *buf, माप_प्रकार sz, जोड़ acpi_object *pack)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < pack->package.count; i++) अणु
		जोड़ acpi_object *obj = &pack->package.elements[i];

		ret = atk_acpi_prपूर्णांक(buf, sz, obj);
		अगर (ret >= sz)
			अवरोध;
		buf += ret;
		sz -= ret;
	पूर्ण
पूर्ण

अटल पूर्णांक atk_debugfs_ggrp_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा atk_data *data = inode->i_निजी;
	अक्षर *buf = शून्य;
	जोड़ acpi_object *ret;
	u8 cls;
	पूर्णांक i;

	अगर (!data->क्रमागतerate_handle)
		वापस -ENODEV;
	अगर (!data->debugfs.id)
		वापस -EINVAL;

	cls = (data->debugfs.id & 0xff000000) >> 24;
	ret = atk_ggrp(data, cls);
	अगर (IS_ERR(ret))
		वापस PTR_ERR(ret);

	क्रम (i = 0; i < ret->package.count; i++) अणु
		जोड़ acpi_object *pack = &ret->package.elements[i];
		जोड़ acpi_object *id;

		अगर (pack->type != ACPI_TYPE_PACKAGE)
			जारी;
		अगर (!pack->package.count)
			जारी;
		id = &pack->package.elements[0];
		अगर (id->पूर्णांकeger.value == data->debugfs.id) अणु
			/* Prपूर्णांक the package */
			buf = kzalloc(512, GFP_KERNEL);
			अगर (!buf) अणु
				ACPI_FREE(ret);
				वापस -ENOMEM;
			पूर्ण
			atk_pack_prपूर्णांक(buf, 512, pack);
			अवरोध;
		पूर्ण
	पूर्ण
	ACPI_FREE(ret);

	अगर (!buf)
		वापस -EINVAL;

	file->निजी_data = buf;

	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल sमाप_प्रकार atk_debugfs_ggrp_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
		माप_प्रकार count, loff_t *pos)
अणु
	अक्षर *str = file->निजी_data;
	माप_प्रकार len = म_माप(str);

	वापस simple_पढ़ो_from_buffer(buf, count, pos, str, len);
पूर्ण

अटल पूर्णांक atk_debugfs_ggrp_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	kमुक्त(file->निजी_data);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations atk_debugfs_ggrp_fops = अणु
	.पढ़ो		= atk_debugfs_ggrp_पढ़ो,
	.खोलो		= atk_debugfs_ggrp_खोलो,
	.release	= atk_debugfs_ggrp_release,
	.llseek		= no_llseek,
पूर्ण;

अटल व्योम atk_debugfs_init(काष्ठा atk_data *data)
अणु
	काष्ठा dentry *d;

	data->debugfs.id = 0;

	d = debugfs_create_dir("asus_atk0110", शून्य);

	debugfs_create_x32("id", 0600, d, &data->debugfs.id);
	debugfs_create_file_unsafe("gitm", 0400, d, data, &atk_debugfs_giपंचांग);
	debugfs_create_file("ggrp", 0400, d, data, &atk_debugfs_ggrp_fops);

	data->debugfs.root = d;
पूर्ण

अटल व्योम atk_debugfs_cleanup(काष्ठा atk_data *data)
अणु
	debugfs_हटाओ_recursive(data->debugfs.root);
पूर्ण

#अन्यथा /* CONFIG_DEBUG_FS */

अटल व्योम atk_debugfs_init(काष्ठा atk_data *data)
अणु
पूर्ण

अटल व्योम atk_debugfs_cleanup(काष्ठा atk_data *data)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक atk_add_sensor(काष्ठा atk_data *data, जोड़ acpi_object *obj)
अणु
	काष्ठा device *dev = &data->acpi_dev->dev;
	जोड़ acpi_object *flags;
	जोड़ acpi_object *name;
	जोड़ acpi_object *limit1;
	जोड़ acpi_object *limit2;
	जोड़ acpi_object *enable;
	काष्ठा atk_sensor_data *sensor;
	अक्षर स्थिर *base_name;
	अक्षर स्थिर *limit1_name;
	अक्षर स्थिर *limit2_name;
	u64 type;
	पूर्णांक err;
	पूर्णांक *num;
	पूर्णांक start;

	अगर (obj->type != ACPI_TYPE_PACKAGE) अणु
		/* wft is this? */
		dev_warn(dev, "Unknown type for ACPI object: (%d)\n",
				obj->type);
		वापस -EINVAL;
	पूर्ण

	err = validate_hwmon_pack(data, obj);
	अगर (err)
		वापस err;

	/* Ok, we have a valid hwmon package */
	type = atk_get_pack_member(data, obj, HWMON_PACK_FLAGS)->पूर्णांकeger.value
	       & ATK_TYPE_MASK;

	चयन (type) अणु
	हाल HWMON_TYPE_VOLT:
		base_name = "in";
		limit1_name = "min";
		limit2_name = "max";
		num = &data->voltage_count;
		start = 0;
		अवरोध;
	हाल HWMON_TYPE_TEMP:
		base_name = "temp";
		limit1_name = "max";
		limit2_name = "crit";
		num = &data->temperature_count;
		start = 1;
		अवरोध;
	हाल HWMON_TYPE_FAN:
		base_name = "fan";
		limit1_name = "min";
		limit2_name = "max";
		num = &data->fan_count;
		start = 1;
		अवरोध;
	शेष:
		dev_warn(dev, "Unknown sensor type: %#llx\n", type);
		वापस -EINVAL;
	पूर्ण

	enable = atk_get_pack_member(data, obj, HWMON_PACK_ENABLE);
	अगर (!enable->पूर्णांकeger.value)
		/* sensor is disabled */
		वापस 0;

	flags = atk_get_pack_member(data, obj, HWMON_PACK_FLAGS);
	name = atk_get_pack_member(data, obj, HWMON_PACK_NAME);
	limit1 = atk_get_pack_member(data, obj, HWMON_PACK_LIMIT1);
	limit2 = atk_get_pack_member(data, obj, HWMON_PACK_LIMIT2);

	sensor = devm_kzalloc(dev, माप(*sensor), GFP_KERNEL);
	अगर (!sensor)
		वापस -ENOMEM;

	sensor->acpi_name = devm_kstrdup(dev, name->string.poपूर्णांकer, GFP_KERNEL);
	अगर (!sensor->acpi_name)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&sensor->list);
	sensor->type = type;
	sensor->data = data;
	sensor->id = flags->पूर्णांकeger.value;
	sensor->limit1 = limit1->पूर्णांकeger.value;
	अगर (data->old_पूर्णांकerface)
		sensor->limit2 = limit2->पूर्णांकeger.value;
	अन्यथा
		/* The upper limit is expressed as delta from lower limit */
		sensor->limit2 = sensor->limit1 + limit2->पूर्णांकeger.value;

	snम_लिखो(sensor->input_attr_name, ATTR_NAME_SIZE,
			"%s%d_input", base_name, start + *num);
	atk_init_attribute(&sensor->input_attr,
			sensor->input_attr_name,
			atk_input_show);

	snम_लिखो(sensor->label_attr_name, ATTR_NAME_SIZE,
			"%s%d_label", base_name, start + *num);
	atk_init_attribute(&sensor->label_attr,
			sensor->label_attr_name,
			atk_label_show);

	snम_लिखो(sensor->limit1_attr_name, ATTR_NAME_SIZE,
			"%s%d_%s", base_name, start + *num, limit1_name);
	atk_init_attribute(&sensor->limit1_attr,
			sensor->limit1_attr_name,
			atk_limit1_show);

	snम_लिखो(sensor->limit2_attr_name, ATTR_NAME_SIZE,
			"%s%d_%s", base_name, start + *num, limit2_name);
	atk_init_attribute(&sensor->limit2_attr,
			sensor->limit2_attr_name,
			atk_limit2_show);

	list_add(&sensor->list, &data->sensor_list);
	(*num)++;

	वापस 1;
पूर्ण

अटल पूर्णांक atk_क्रमागतerate_old_hwmon(काष्ठा atk_data *data)
अणु
	काष्ठा device *dev = &data->acpi_dev->dev;
	काष्ठा acpi_buffer buf;
	जोड़ acpi_object *pack;
	acpi_status status;
	पूर्णांक i, ret;
	पूर्णांक count = 0;

	/* Voltages */
	buf.length = ACPI_ALLOCATE_BUFFER;
	status = acpi_evaluate_object_typed(data->atk_handle,
			METHOD_OLD_ENUM_VLT, शून्य, &buf, ACPI_TYPE_PACKAGE);
	अगर (status != AE_OK) अणु
		dev_warn(dev, METHOD_OLD_ENUM_VLT ": ACPI exception: %s\n",
				acpi_क्रमmat_exception(status));

		वापस -ENODEV;
	पूर्ण

	pack = buf.poपूर्णांकer;
	क्रम (i = 1; i < pack->package.count; i++) अणु
		जोड़ acpi_object *obj = &pack->package.elements[i];

		ret = atk_add_sensor(data, obj);
		अगर (ret > 0)
			count++;
	पूर्ण
	ACPI_FREE(buf.poपूर्णांकer);

	/* Temperatures */
	buf.length = ACPI_ALLOCATE_BUFFER;
	status = acpi_evaluate_object_typed(data->atk_handle,
			METHOD_OLD_ENUM_TMP, शून्य, &buf, ACPI_TYPE_PACKAGE);
	अगर (status != AE_OK) अणु
		dev_warn(dev, METHOD_OLD_ENUM_TMP ": ACPI exception: %s\n",
				acpi_क्रमmat_exception(status));

		वापस -ENODEV;
	पूर्ण

	pack = buf.poपूर्णांकer;
	क्रम (i = 1; i < pack->package.count; i++) अणु
		जोड़ acpi_object *obj = &pack->package.elements[i];

		ret = atk_add_sensor(data, obj);
		अगर (ret > 0)
			count++;
	पूर्ण
	ACPI_FREE(buf.poपूर्णांकer);

	/* Fans */
	buf.length = ACPI_ALLOCATE_BUFFER;
	status = acpi_evaluate_object_typed(data->atk_handle,
			METHOD_OLD_ENUM_FAN, शून्य, &buf, ACPI_TYPE_PACKAGE);
	अगर (status != AE_OK) अणु
		dev_warn(dev, METHOD_OLD_ENUM_FAN ": ACPI exception: %s\n",
				acpi_क्रमmat_exception(status));

		वापस -ENODEV;
	पूर्ण

	pack = buf.poपूर्णांकer;
	क्रम (i = 1; i < pack->package.count; i++) अणु
		जोड़ acpi_object *obj = &pack->package.elements[i];

		ret = atk_add_sensor(data, obj);
		अगर (ret > 0)
			count++;
	पूर्ण
	ACPI_FREE(buf.poपूर्णांकer);

	वापस count;
पूर्ण

अटल पूर्णांक atk_ec_present(काष्ठा atk_data *data)
अणु
	काष्ठा device *dev = &data->acpi_dev->dev;
	जोड़ acpi_object *pack;
	जोड़ acpi_object *ec;
	पूर्णांक ret;
	पूर्णांक i;

	pack = atk_ggrp(data, ATK_MUX_MGMT);
	अगर (IS_ERR(pack)) अणु
		अगर (PTR_ERR(pack) == -ENOENT) अणु
			/* The MGMT class करोes not exists - that's ok */
			dev_dbg(dev, "Class %#llx not found\n", ATK_MUX_MGMT);
			वापस 0;
		पूर्ण
		वापस PTR_ERR(pack);
	पूर्ण

	/* Search the EC */
	ec = शून्य;
	क्रम (i = 0; i < pack->package.count; i++) अणु
		जोड़ acpi_object *obj = &pack->package.elements[i];
		जोड़ acpi_object *id;

		अगर (obj->type != ACPI_TYPE_PACKAGE)
			जारी;

		id = &obj->package.elements[0];
		अगर (id->type != ACPI_TYPE_INTEGER)
			जारी;

		अगर (id->पूर्णांकeger.value == ATK_EC_ID) अणु
			ec = obj;
			अवरोध;
		पूर्ण
	पूर्ण

	ret = (ec != शून्य);
	अगर (!ret)
		/* The प्रणाली has no EC */
		dev_dbg(dev, "EC not found\n");

	ACPI_FREE(pack);
	वापस ret;
पूर्ण

अटल पूर्णांक atk_ec_enabled(काष्ठा atk_data *data)
अणु
	काष्ठा device *dev = &data->acpi_dev->dev;
	जोड़ acpi_object *obj;
	काष्ठा atk_acpi_ret_buffer *buf;
	पूर्णांक err;

	obj = atk_giपंचांग(data, ATK_EC_ID);
	अगर (IS_ERR(obj)) अणु
		dev_err(dev, "Unable to query EC status\n");
		वापस PTR_ERR(obj);
	पूर्ण
	buf = (काष्ठा atk_acpi_ret_buffer *)obj->buffer.poपूर्णांकer;

	अगर (buf->flags == 0) अणु
		dev_err(dev, "Unable to query EC status\n");
		err = -EIO;
	पूर्ण अन्यथा अणु
		err = (buf->value != 0);
		dev_dbg(dev, "EC is %sabled\n",
				err ? "en" : "dis");
	पूर्ण

	ACPI_FREE(obj);
	वापस err;
पूर्ण

अटल पूर्णांक atk_ec_ctl(काष्ठा atk_data *data, पूर्णांक enable)
अणु
	काष्ठा device *dev = &data->acpi_dev->dev;
	जोड़ acpi_object *obj;
	काष्ठा atk_acpi_input_buf siपंचांग;
	काष्ठा atk_acpi_ret_buffer *ec_ret;
	पूर्णांक err = 0;

	siपंचांग.id = ATK_EC_ID;
	siपंचांग.param1 = enable;
	siपंचांग.param2 = 0;

	obj = atk_siपंचांग(data, &siपंचांग);
	अगर (IS_ERR(obj)) अणु
		dev_err(dev, "Failed to %sable the EC\n",
				enable ? "en" : "dis");
		वापस PTR_ERR(obj);
	पूर्ण
	ec_ret = (काष्ठा atk_acpi_ret_buffer *)obj->buffer.poपूर्णांकer;
	अगर (ec_ret->flags == 0) अणु
		dev_err(dev, "Failed to %sable the EC\n",
				enable ? "en" : "dis");
		err = -EIO;
	पूर्ण अन्यथा अणु
		dev_info(dev, "EC %sabled\n",
				enable ? "en" : "dis");
	पूर्ण

	ACPI_FREE(obj);
	वापस err;
पूर्ण

अटल पूर्णांक atk_क्रमागतerate_new_hwmon(काष्ठा atk_data *data)
अणु
	काष्ठा device *dev = &data->acpi_dev->dev;
	जोड़ acpi_object *pack;
	पूर्णांक err;
	पूर्णांक i;

	err = atk_ec_present(data);
	अगर (err < 0)
		वापस err;
	अगर (err) अणु
		err = atk_ec_enabled(data);
		अगर (err < 0)
			वापस err;
		/* If the EC was disabled we will disable it again on unload */
		data->disable_ec = err;

		err = atk_ec_ctl(data, 1);
		अगर (err) अणु
			data->disable_ec = false;
			वापस err;
		पूर्ण
	पूर्ण

	dev_dbg(dev, "Enumerating hwmon sensors\n");

	pack = atk_ggrp(data, ATK_MUX_HWMON);
	अगर (IS_ERR(pack))
		वापस PTR_ERR(pack);

	क्रम (i = 0; i < pack->package.count; i++) अणु
		जोड़ acpi_object *obj = &pack->package.elements[i];

		atk_add_sensor(data, obj);
	पूर्ण

	err = data->voltage_count + data->temperature_count + data->fan_count;

	ACPI_FREE(pack);
	वापस err;
पूर्ण

अटल पूर्णांक atk_init_attribute_groups(काष्ठा atk_data *data)
अणु
	काष्ठा device *dev = &data->acpi_dev->dev;
	काष्ठा atk_sensor_data *s;
	काष्ठा attribute **attrs;
	पूर्णांक i = 0;
	पूर्णांक len = (data->voltage_count + data->temperature_count
			+ data->fan_count) * 4 + 1;

	attrs = devm_kसुस्मृति(dev, len, माप(काष्ठा attribute *), GFP_KERNEL);
	अगर (!attrs)
		वापस -ENOMEM;

	list_क्रम_each_entry(s, &data->sensor_list, list) अणु
		attrs[i++] = &s->input_attr.attr;
		attrs[i++] = &s->label_attr.attr;
		attrs[i++] = &s->limit1_attr.attr;
		attrs[i++] = &s->limit2_attr.attr;
	पूर्ण

	data->attr_group.attrs = attrs;
	data->attr_groups[0] = &data->attr_group;

	वापस 0;
पूर्ण

अटल पूर्णांक atk_रेजिस्टर_hwmon(काष्ठा atk_data *data)
अणु
	काष्ठा device *dev = &data->acpi_dev->dev;

	dev_dbg(dev, "registering hwmon device\n");
	data->hwmon_dev = hwmon_device_रेजिस्टर_with_groups(dev, "atk0110",
							    data,
							    data->attr_groups);

	वापस PTR_ERR_OR_ZERO(data->hwmon_dev);
पूर्ण

अटल पूर्णांक atk_probe_अगर(काष्ठा atk_data *data)
अणु
	काष्ठा device *dev = &data->acpi_dev->dev;
	acpi_handle ret;
	acpi_status status;
	पूर्णांक err = 0;

	/* RTMP: पढ़ो temperature */
	status = acpi_get_handle(data->atk_handle, METHOD_OLD_READ_TMP, &ret);
	अगर (ACPI_SUCCESS(status))
		data->rपंचांगp_handle = ret;
	अन्यथा
		dev_dbg(dev, "method " METHOD_OLD_READ_TMP " not found: %s\n",
				acpi_क्रमmat_exception(status));

	/* RVLT: पढ़ो voltage */
	status = acpi_get_handle(data->atk_handle, METHOD_OLD_READ_VLT, &ret);
	अगर (ACPI_SUCCESS(status))
		data->rvlt_handle = ret;
	अन्यथा
		dev_dbg(dev, "method " METHOD_OLD_READ_VLT " not found: %s\n",
				acpi_क्रमmat_exception(status));

	/* RFAN: पढ़ो fan status */
	status = acpi_get_handle(data->atk_handle, METHOD_OLD_READ_FAN, &ret);
	अगर (ACPI_SUCCESS(status))
		data->rfan_handle = ret;
	अन्यथा
		dev_dbg(dev, "method " METHOD_OLD_READ_FAN " not found: %s\n",
				acpi_क्रमmat_exception(status));

	/* Enumeration */
	status = acpi_get_handle(data->atk_handle, METHOD_ENUMERATE, &ret);
	अगर (ACPI_SUCCESS(status))
		data->क्रमागतerate_handle = ret;
	अन्यथा
		dev_dbg(dev, "method " METHOD_ENUMERATE " not found: %s\n",
				acpi_क्रमmat_exception(status));

	/* De-multiplexer (पढ़ो) */
	status = acpi_get_handle(data->atk_handle, METHOD_READ, &ret);
	अगर (ACPI_SUCCESS(status))
		data->पढ़ो_handle = ret;
	अन्यथा
		dev_dbg(dev, "method " METHOD_READ " not found: %s\n",
				acpi_क्रमmat_exception(status));

	/* De-multiplexer (ग_लिखो) */
	status = acpi_get_handle(data->atk_handle, METHOD_WRITE, &ret);
	अगर (ACPI_SUCCESS(status))
		data->ग_लिखो_handle = ret;
	अन्यथा
		dev_dbg(dev, "method " METHOD_WRITE " not found: %s\n",
				 acpi_क्रमmat_exception(status));

	/*
	 * Check क्रम hwmon methods: first check "old" style methods; note that
	 * both may be present: in this हाल we stick to the old पूर्णांकerface;
	 * analysis of multiple DSDTs indicates that when both पूर्णांकerfaces
	 * are present the new one (GGRP/GITM) is not functional.
	 */
	अगर (new_अगर)
		dev_info(dev, "Overriding interface detection\n");
	अगर (data->rपंचांगp_handle &&
			data->rvlt_handle && data->rfan_handle && !new_अगर)
		data->old_पूर्णांकerface = true;
	अन्यथा अगर (data->क्रमागतerate_handle && data->पढ़ो_handle &&
			data->ग_लिखो_handle)
		data->old_पूर्णांकerface = false;
	अन्यथा
		err = -ENODEV;

	वापस err;
पूर्ण

अटल पूर्णांक atk_add(काष्ठा acpi_device *device)
अणु
	acpi_status ret;
	पूर्णांक err;
	काष्ठा acpi_buffer buf;
	जोड़ acpi_object *obj;
	काष्ठा atk_data *data;

	dev_dbg(&device->dev, "adding...\n");

	data = devm_kzalloc(&device->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->acpi_dev = device;
	data->atk_handle = device->handle;
	INIT_LIST_HEAD(&data->sensor_list);
	data->disable_ec = false;

	buf.length = ACPI_ALLOCATE_BUFFER;
	ret = acpi_evaluate_object_typed(data->atk_handle, BOARD_ID, शून्य,
			&buf, ACPI_TYPE_PACKAGE);
	अगर (ret != AE_OK) अणु
		dev_dbg(&device->dev, "atk: method MBIF not found\n");
	पूर्ण अन्यथा अणु
		obj = buf.poपूर्णांकer;
		अगर (obj->package.count >= 2) अणु
			जोड़ acpi_object *id = &obj->package.elements[1];
			अगर (id->type == ACPI_TYPE_STRING)
				dev_dbg(&device->dev, "board ID = %s\n",
					id->string.poपूर्णांकer);
		पूर्ण
		ACPI_FREE(buf.poपूर्णांकer);
	पूर्ण

	err = atk_probe_अगर(data);
	अगर (err) अणु
		dev_err(&device->dev, "No usable hwmon interface detected\n");
		जाओ out;
	पूर्ण

	अगर (data->old_पूर्णांकerface) अणु
		dev_dbg(&device->dev, "Using old hwmon interface\n");
		err = atk_क्रमागतerate_old_hwmon(data);
	पूर्ण अन्यथा अणु
		dev_dbg(&device->dev, "Using new hwmon interface\n");
		err = atk_क्रमागतerate_new_hwmon(data);
	पूर्ण
	अगर (err < 0)
		जाओ out;
	अगर (err == 0) अणु
		dev_info(&device->dev,
			 "No usable sensor detected, bailing out\n");
		err = -ENODEV;
		जाओ out;
	पूर्ण

	err = atk_init_attribute_groups(data);
	अगर (err)
		जाओ out;
	err = atk_रेजिस्टर_hwmon(data);
	अगर (err)
		जाओ out;

	atk_debugfs_init(data);

	device->driver_data = data;
	वापस 0;
out:
	अगर (data->disable_ec)
		atk_ec_ctl(data, 0);
	वापस err;
पूर्ण

अटल पूर्णांक atk_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा atk_data *data = device->driver_data;
	dev_dbg(&device->dev, "removing...\n");

	device->driver_data = शून्य;

	atk_debugfs_cleanup(data);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);

	अगर (data->disable_ec) अणु
		अगर (atk_ec_ctl(data, 0))
			dev_err(&device->dev, "Failed to disable EC\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init atk0110_init(व्योम)
अणु
	पूर्णांक ret;

	/* Make sure it's safe to access the device through ACPI */
	अगर (!acpi_resources_are_enक्रमced()) अणु
		pr_err("Resources not safely usable due to acpi_enforce_resources kernel parameter\n");
		वापस -EBUSY;
	पूर्ण

	अगर (dmi_check_प्रणाली(atk_क्रमce_new_अगर))
		new_अगर = true;

	ret = acpi_bus_रेजिस्टर_driver(&atk_driver);
	अगर (ret)
		pr_info("acpi_bus_register_driver failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम __निकास atk0110_निकास(व्योम)
अणु
	acpi_bus_unरेजिस्टर_driver(&atk_driver);
पूर्ण

module_init(atk0110_init);
module_निकास(atk0110_निकास);

MODULE_LICENSE("GPL");
