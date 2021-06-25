<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IBM PowerNV platक्रमm sensors क्रम temperature/fan/voltage/घातer
 * Copyright (C) 2014 IBM
 */

#घोषणा DRVNAME		"ibmpowernv"
#घोषणा pr_fmt(fmt)	DRVNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/opal.h>
#समावेश <linux/err.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/smp.h>

#घोषणा MAX_ATTR_LEN	32
#घोषणा MAX_LABEL_LEN	64

/* Sensor suffix name from DT */
#घोषणा DT_FAULT_ATTR_SUFFIX		"faulted"
#घोषणा DT_DATA_ATTR_SUFFIX		"data"
#घोषणा DT_THRESHOLD_ATTR_SUFFIX	"thrs"

/*
 * Enumerates all the types of sensors in the POWERNV platक्रमm and करोes index
 * पूर्णांकo 'struct sensor_group'
 */
क्रमागत sensors अणु
	FAN,
	TEMP,
	POWER_SUPPLY,
	POWER_INPUT,
	CURRENT,
	ENERGY,
	MAX_SENSOR_TYPE,
पूर्ण;

#घोषणा INVALID_INDEX (-1U)

/*
 * 'compatible' string properties क्रम sensor types as defined in old
 * PowerNV firmware (skiboot). These are ordered as 'enum sensors'.
 */
अटल स्थिर अक्षर * स्थिर legacy_compatibles[] = अणु
	"ibm,opal-sensor-cooling-fan",
	"ibm,opal-sensor-amb-temp",
	"ibm,opal-sensor-power-supply",
	"ibm,opal-sensor-power"
पूर्ण;

अटल काष्ठा sensor_group अणु
	स्थिर अक्षर *name; /* matches property 'sensor-type' */
	काष्ठा attribute_group group;
	u32 attr_count;
	u32 hwmon_index;
पूर्ण sensor_groups[] = अणु
	अणु "fan"   पूर्ण,
	अणु "temp"  पूर्ण,
	अणु "in"    पूर्ण,
	अणु "power" पूर्ण,
	अणु "curr"  पूर्ण,
	अणु "energy" पूर्ण,
पूर्ण;

काष्ठा sensor_data अणु
	u32 id; /* An opaque id of the firmware क्रम each sensor */
	u32 hwmon_index;
	u32 opal_index;
	क्रमागत sensors type;
	अक्षर label[MAX_LABEL_LEN];
	अक्षर name[MAX_ATTR_LEN];
	काष्ठा device_attribute dev_attr;
	काष्ठा sensor_group_data *sgrp_data;
पूर्ण;

काष्ठा sensor_group_data अणु
	काष्ठा mutex mutex;
	u32 gid;
	bool enable;
पूर्ण;

काष्ठा platक्रमm_data अणु
	स्थिर काष्ठा attribute_group *attr_groups[MAX_SENSOR_TYPE + 1];
	काष्ठा sensor_group_data *sgrp_data;
	u32 sensors_count; /* Total count of sensors from each group */
	u32 nr_sensor_groups; /* Total number of sensor groups */
पूर्ण;

अटल sमाप_प्रकार show_sensor(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			   अक्षर *buf)
अणु
	काष्ठा sensor_data *sdata = container_of(devattr, काष्ठा sensor_data,
						 dev_attr);
	sमाप_प्रकार ret;
	u64 x;

	अगर (sdata->sgrp_data && !sdata->sgrp_data->enable)
		वापस -ENODATA;

	ret =  opal_get_sensor_data_u64(sdata->id, &x);

	अगर (ret)
		वापस ret;

	/* Convert temperature to milli-degrees */
	अगर (sdata->type == TEMP)
		x *= 1000;
	/* Convert घातer to micro-watts */
	अन्यथा अगर (sdata->type == POWER_INPUT)
		x *= 1000000;

	वापस प्र_लिखो(buf, "%llu\n", x);
पूर्ण

अटल sमाप_प्रकार show_enable(काष्ठा device *dev,
			   काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_data *sdata = container_of(devattr, काष्ठा sensor_data,
						 dev_attr);

	वापस प्र_लिखो(buf, "%u\n", sdata->sgrp_data->enable);
पूर्ण

अटल sमाप_प्रकार store_enable(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_data *sdata = container_of(devattr, काष्ठा sensor_data,
						 dev_attr);
	काष्ठा sensor_group_data *sgrp_data = sdata->sgrp_data;
	पूर्णांक ret;
	bool data;

	ret = kstrtobool(buf, &data);
	अगर (ret)
		वापस ret;

	ret = mutex_lock_पूर्णांकerruptible(&sgrp_data->mutex);
	अगर (ret)
		वापस ret;

	अगर (data != sgrp_data->enable) अणु
		ret =  sensor_group_enable(sgrp_data->gid, data);
		अगर (!ret)
			sgrp_data->enable = data;
	पूर्ण

	अगर (!ret)
		ret = count;

	mutex_unlock(&sgrp_data->mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार show_label(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			  अक्षर *buf)
अणु
	काष्ठा sensor_data *sdata = container_of(devattr, काष्ठा sensor_data,
						 dev_attr);

	वापस प्र_लिखो(buf, "%s\n", sdata->label);
पूर्ण

अटल पूर्णांक get_logical_cpu(पूर्णांक hwcpu)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		अगर (get_hard_smp_processor_id(cpu) == hwcpu)
			वापस cpu;

	वापस -ENOENT;
पूर्ण

अटल व्योम make_sensor_label(काष्ठा device_node *np,
			      काष्ठा sensor_data *sdata, स्थिर अक्षर *label)
अणु
	u32 id;
	माप_प्रकार n;

	n = scnम_लिखो(sdata->label, माप(sdata->label), "%s", label);

	/*
	 * Core temp pretty prपूर्णांक
	 */
	अगर (!of_property_पढ़ो_u32(np, "ibm,pir", &id)) अणु
		पूर्णांक cpuid = get_logical_cpu(id);

		अगर (cpuid >= 0)
			/*
			 * The digital thermal sensors are associated
			 * with a core.
			 */
			n += scnम_लिखो(sdata->label + n,
				      माप(sdata->label) - n, " %d",
				      cpuid);
		अन्यथा
			n += scnम_लिखो(sdata->label + n,
				      माप(sdata->label) - n, " phy%d", id);
	पूर्ण

	/*
	 * Membuffer pretty prपूर्णांक
	 */
	अगर (!of_property_पढ़ो_u32(np, "ibm,chip-id", &id))
		n += scnम_लिखो(sdata->label + n, माप(sdata->label) - n,
			      " %d", id & 0xffff);
पूर्ण

अटल पूर्णांक get_sensor_index_attr(स्थिर अक्षर *name, u32 *index, अक्षर *attr)
अणु
	अक्षर *hash_pos = म_अक्षर(name, '#');
	अक्षर buf[8] = अणु 0 पूर्ण;
	अक्षर *dash_pos;
	u32 copy_len;
	पूर्णांक err;

	अगर (!hash_pos)
		वापस -EINVAL;

	dash_pos = म_अक्षर(hash_pos, '-');
	अगर (!dash_pos)
		वापस -EINVAL;

	copy_len = dash_pos - hash_pos - 1;
	अगर (copy_len >= माप(buf))
		वापस -EINVAL;

	म_नकलन(buf, hash_pos + 1, copy_len);

	err = kstrtou32(buf, 10, index);
	अगर (err)
		वापस err;

	strscpy(attr, dash_pos + 1, MAX_ATTR_LEN);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *convert_opal_attr_name(क्रमागत sensors type,
					  स्थिर अक्षर *opal_attr)
अणु
	स्थिर अक्षर *attr_name = शून्य;

	अगर (!म_भेद(opal_attr, DT_FAULT_ATTR_SUFFIX)) अणु
		attr_name = "fault";
	पूर्ण अन्यथा अगर (!म_भेद(opal_attr, DT_DATA_ATTR_SUFFIX)) अणु
		attr_name = "input";
	पूर्ण अन्यथा अगर (!म_भेद(opal_attr, DT_THRESHOLD_ATTR_SUFFIX)) अणु
		अगर (type == TEMP)
			attr_name = "max";
		अन्यथा अगर (type == FAN)
			attr_name = "min";
	पूर्ण

	वापस attr_name;
पूर्ण

/*
 * This function translates the DT node name पूर्णांकo the 'hwmon' attribute name.
 * IBMPOWERNV device node appear like cooling-fan#2-data, amb-temp#1-thrs etc.
 * which need to be mapped as fan2_input, temp1_max respectively beक्रमe
 * populating them inside hwmon device class.
 */
अटल स्थिर अक्षर *parse_opal_node_name(स्थिर अक्षर *node_name,
					क्रमागत sensors type, u32 *index)
अणु
	अक्षर attr_suffix[MAX_ATTR_LEN];
	स्थिर अक्षर *attr_name;
	पूर्णांक err;

	err = get_sensor_index_attr(node_name, index, attr_suffix);
	अगर (err)
		वापस ERR_PTR(err);

	attr_name = convert_opal_attr_name(type, attr_suffix);
	अगर (!attr_name)
		वापस ERR_PTR(-ENOENT);

	वापस attr_name;
पूर्ण

अटल पूर्णांक get_sensor_type(काष्ठा device_node *np)
अणु
	क्रमागत sensors type;
	स्थिर अक्षर *str;

	क्रम (type = 0; type < ARRAY_SIZE(legacy_compatibles); type++) अणु
		अगर (of_device_is_compatible(np, legacy_compatibles[type]))
			वापस type;
	पूर्ण

	/*
	 * Let's check अगर we have a newer device tree
	 */
	अगर (!of_device_is_compatible(np, "ibm,opal-sensor"))
		वापस MAX_SENSOR_TYPE;

	अगर (of_property_पढ़ो_string(np, "sensor-type", &str))
		वापस MAX_SENSOR_TYPE;

	क्रम (type = 0; type < MAX_SENSOR_TYPE; type++)
		अगर (!म_भेद(str, sensor_groups[type].name))
			वापस type;

	वापस MAX_SENSOR_TYPE;
पूर्ण

अटल u32 get_sensor_hwmon_index(काष्ठा sensor_data *sdata,
				  काष्ठा sensor_data *sdata_table, पूर्णांक count)
अणु
	पूर्णांक i;

	/*
	 * We करोn't use the OPAL index on newer device trees
	 */
	अगर (sdata->opal_index != INVALID_INDEX) अणु
		क्रम (i = 0; i < count; i++)
			अगर (sdata_table[i].opal_index == sdata->opal_index &&
			    sdata_table[i].type == sdata->type)
				वापस sdata_table[i].hwmon_index;
	पूर्ण
	वापस ++sensor_groups[sdata->type].hwmon_index;
पूर्ण

अटल पूर्णांक init_sensor_group_data(काष्ठा platक्रमm_device *pdev,
				  काष्ठा platक्रमm_data *pdata)
अणु
	काष्ठा sensor_group_data *sgrp_data;
	काष्ठा device_node *groups, *sgrp;
	पूर्णांक count = 0, ret = 0;
	क्रमागत sensors type;

	groups = of_find_compatible_node(शून्य, शून्य, "ibm,opal-sensor-group");
	अगर (!groups)
		वापस ret;

	क्रम_each_child_of_node(groups, sgrp) अणु
		type = get_sensor_type(sgrp);
		अगर (type != MAX_SENSOR_TYPE)
			pdata->nr_sensor_groups++;
	पूर्ण

	अगर (!pdata->nr_sensor_groups)
		जाओ out;

	sgrp_data = devm_kसुस्मृति(&pdev->dev, pdata->nr_sensor_groups,
				 माप(*sgrp_data), GFP_KERNEL);
	अगर (!sgrp_data) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम_each_child_of_node(groups, sgrp) अणु
		u32 gid;

		type = get_sensor_type(sgrp);
		अगर (type == MAX_SENSOR_TYPE)
			जारी;

		अगर (of_property_पढ़ो_u32(sgrp, "sensor-group-id", &gid))
			जारी;

		अगर (of_count_phandle_with_args(sgrp, "sensors", शून्य) <= 0)
			जारी;

		sensor_groups[type].attr_count++;
		sgrp_data[count].gid = gid;
		mutex_init(&sgrp_data[count].mutex);
		sgrp_data[count++].enable = false;
	पूर्ण

	pdata->sgrp_data = sgrp_data;
out:
	of_node_put(groups);
	वापस ret;
पूर्ण

अटल काष्ठा sensor_group_data *get_sensor_group(काष्ठा platक्रमm_data *pdata,
						  काष्ठा device_node *node,
						  क्रमागत sensors gtype)
अणु
	काष्ठा sensor_group_data *sgrp_data = pdata->sgrp_data;
	काष्ठा device_node *groups, *sgrp;

	groups = of_find_compatible_node(शून्य, शून्य, "ibm,opal-sensor-group");
	अगर (!groups)
		वापस शून्य;

	क्रम_each_child_of_node(groups, sgrp) अणु
		काष्ठा of_phandle_iterator it;
		u32 gid;
		पूर्णांक rc, i;
		क्रमागत sensors type;

		type = get_sensor_type(sgrp);
		अगर (type != gtype)
			जारी;

		अगर (of_property_पढ़ो_u32(sgrp, "sensor-group-id", &gid))
			जारी;

		of_क्रम_each_phandle(&it, rc, sgrp, "sensors", शून्य, 0)
			अगर (it.phandle == node->phandle) अणु
				of_node_put(it.node);
				अवरोध;
			पूर्ण

		अगर (rc)
			जारी;

		क्रम (i = 0; i < pdata->nr_sensor_groups; i++)
			अगर (gid == sgrp_data[i].gid) अणु
				of_node_put(sgrp);
				of_node_put(groups);
				वापस &sgrp_data[i];
			पूर्ण
	पूर्ण

	of_node_put(groups);
	वापस शून्य;
पूर्ण

अटल पूर्णांक populate_attr_groups(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा platक्रमm_data *pdata = platक्रमm_get_drvdata(pdev);
	स्थिर काष्ठा attribute_group **pgroups = pdata->attr_groups;
	काष्ठा device_node *opal, *np;
	क्रमागत sensors type;
	पूर्णांक ret;

	ret = init_sensor_group_data(pdev, pdata);
	अगर (ret)
		वापस ret;

	opal = of_find_node_by_path("/ibm,opal/sensors");
	क्रम_each_child_of_node(opal, np) अणु
		स्थिर अक्षर *label;

		type = get_sensor_type(np);
		अगर (type == MAX_SENSOR_TYPE)
			जारी;

		sensor_groups[type].attr_count++;

		/*
		 * add attributes क्रम labels, min and max
		 */
		अगर (!of_property_पढ़ो_string(np, "label", &label))
			sensor_groups[type].attr_count++;
		अगर (of_find_property(np, "sensor-data-min", शून्य))
			sensor_groups[type].attr_count++;
		अगर (of_find_property(np, "sensor-data-max", शून्य))
			sensor_groups[type].attr_count++;
	पूर्ण

	of_node_put(opal);

	क्रम (type = 0; type < MAX_SENSOR_TYPE; type++) अणु
		sensor_groups[type].group.attrs = devm_kसुस्मृति(&pdev->dev,
					sensor_groups[type].attr_count + 1,
					माप(काष्ठा attribute *),
					GFP_KERNEL);
		अगर (!sensor_groups[type].group.attrs)
			वापस -ENOMEM;

		pgroups[type] = &sensor_groups[type].group;
		pdata->sensors_count += sensor_groups[type].attr_count;
		sensor_groups[type].attr_count = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम create_hwmon_attr(काष्ठा sensor_data *sdata, स्थिर अक्षर *attr_name,
			      sमाप_प्रकार (*show)(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf),
			    sमाप_प्रकार (*store)(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     स्थिर अक्षर *buf, माप_प्रकार count))
अणु
	snम_लिखो(sdata->name, MAX_ATTR_LEN, "%s%d_%s",
		 sensor_groups[sdata->type].name, sdata->hwmon_index,
		 attr_name);

	sysfs_attr_init(&sdata->dev_attr.attr);
	sdata->dev_attr.attr.name = sdata->name;
	sdata->dev_attr.show = show;
	अगर (store) अणु
		sdata->dev_attr.store = store;
		sdata->dev_attr.attr.mode = 0664;
	पूर्ण अन्यथा अणु
		sdata->dev_attr.attr.mode = 0444;
	पूर्ण
पूर्ण

अटल व्योम populate_sensor(काष्ठा sensor_data *sdata, पूर्णांक od, पूर्णांक hd, पूर्णांक sid,
			    स्थिर अक्षर *attr_name, क्रमागत sensors type,
			    स्थिर काष्ठा attribute_group *pgroup,
			    काष्ठा sensor_group_data *sgrp_data,
			    sमाप_प्रकार (*show)(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf),
			    sमाप_प्रकार (*store)(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     स्थिर अक्षर *buf, माप_प्रकार count))
अणु
	sdata->id = sid;
	sdata->type = type;
	sdata->opal_index = od;
	sdata->hwmon_index = hd;
	create_hwmon_attr(sdata, attr_name, show, store);
	pgroup->attrs[sensor_groups[type].attr_count++] = &sdata->dev_attr.attr;
	sdata->sgrp_data = sgrp_data;
पूर्ण

अटल अक्षर *get_max_attr(क्रमागत sensors type)
अणु
	चयन (type) अणु
	हाल POWER_INPUT:
		वापस "input_highest";
	शेष:
		वापस "highest";
	पूर्ण
पूर्ण

अटल अक्षर *get_min_attr(क्रमागत sensors type)
अणु
	चयन (type) अणु
	हाल POWER_INPUT:
		वापस "input_lowest";
	शेष:
		वापस "lowest";
	पूर्ण
पूर्ण

/*
 * Iterate through the device tree क्रम each child of 'sensors' node, create
 * a sysfs attribute file, the file is named by translating the DT node name
 * to the name required by the higher 'hwmon' driver like fan1_input, temp1_max
 * etc..
 */
अटल पूर्णांक create_device_attrs(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा platक्रमm_data *pdata = platक्रमm_get_drvdata(pdev);
	स्थिर काष्ठा attribute_group **pgroups = pdata->attr_groups;
	काष्ठा device_node *opal, *np;
	काष्ठा sensor_data *sdata;
	u32 count = 0;
	u32 group_attr_id[MAX_SENSOR_TYPE] = अणु0पूर्ण;

	sdata = devm_kसुस्मृति(&pdev->dev,
			     pdata->sensors_count, माप(*sdata),
			     GFP_KERNEL);
	अगर (!sdata)
		वापस -ENOMEM;

	opal = of_find_node_by_path("/ibm,opal/sensors");
	क्रम_each_child_of_node(opal, np) अणु
		काष्ठा sensor_group_data *sgrp_data;
		स्थिर अक्षर *attr_name;
		u32 opal_index, hw_id;
		u32 sensor_id;
		स्थिर अक्षर *label;
		क्रमागत sensors type;

		type = get_sensor_type(np);
		अगर (type == MAX_SENSOR_TYPE)
			जारी;

		/*
		 * Newer device trees use a "sensor-data" property
		 * name क्रम input.
		 */
		अगर (of_property_पढ़ो_u32(np, "sensor-id", &sensor_id) &&
		    of_property_पढ़ो_u32(np, "sensor-data", &sensor_id)) अणु
			dev_info(&pdev->dev,
				 "'sensor-id' missing in the node '%pOFn'\n",
				 np);
			जारी;
		पूर्ण

		sdata[count].id = sensor_id;
		sdata[count].type = type;

		/*
		 * If we can not parse the node name, it means we are
		 * running on a newer device tree. We can just क्रमget
		 * about the OPAL index and use a defaut value क्रम the
		 * hwmon attribute name
		 */
		attr_name = parse_opal_node_name(np->name, type, &opal_index);
		अगर (IS_ERR(attr_name)) अणु
			attr_name = "input";
			opal_index = INVALID_INDEX;
		पूर्ण

		hw_id = get_sensor_hwmon_index(&sdata[count], sdata, count);
		sgrp_data = get_sensor_group(pdata, np, type);
		populate_sensor(&sdata[count], opal_index, hw_id, sensor_id,
				attr_name, type, pgroups[type], sgrp_data,
				show_sensor, शून्य);
		count++;

		अगर (!of_property_पढ़ो_string(np, "label", &label)) अणु
			/*
			 * For the label attribute, we can reuse the
			 * "properties" of the previous "input"
			 * attribute. They are related to the same
			 * sensor.
			 */

			make_sensor_label(np, &sdata[count], label);
			populate_sensor(&sdata[count], opal_index, hw_id,
					sensor_id, "label", type, pgroups[type],
					शून्य, show_label, शून्य);
			count++;
		पूर्ण

		अगर (!of_property_पढ़ो_u32(np, "sensor-data-max", &sensor_id)) अणु
			attr_name = get_max_attr(type);
			populate_sensor(&sdata[count], opal_index, hw_id,
					sensor_id, attr_name, type,
					pgroups[type], sgrp_data, show_sensor,
					शून्य);
			count++;
		पूर्ण

		अगर (!of_property_पढ़ो_u32(np, "sensor-data-min", &sensor_id)) अणु
			attr_name = get_min_attr(type);
			populate_sensor(&sdata[count], opal_index, hw_id,
					sensor_id, attr_name, type,
					pgroups[type], sgrp_data, show_sensor,
					शून्य);
			count++;
		पूर्ण

		अगर (sgrp_data && !sgrp_data->enable) अणु
			sgrp_data->enable = true;
			hw_id = ++group_attr_id[type];
			populate_sensor(&sdata[count], opal_index, hw_id,
					sgrp_data->gid, "enable", type,
					pgroups[type], sgrp_data, show_enable,
					store_enable);
			count++;
		पूर्ण
	पूर्ण

	of_node_put(opal);
	वापस 0;
पूर्ण

अटल पूर्णांक ibmघातernv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा platक्रमm_data *pdata;
	काष्ठा device *hwmon_dev;
	पूर्णांक err;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, pdata);
	pdata->sensors_count = 0;
	pdata->nr_sensor_groups = 0;
	err = populate_attr_groups(pdev);
	अगर (err)
		वापस err;

	/* Create sysfs attribute data क्रम each sensor found in the DT */
	err = create_device_attrs(pdev);
	अगर (err)
		वापस err;

	/* Finally, रेजिस्टर with hwmon */
	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&pdev->dev, DRVNAME,
							   pdata,
							   pdata->attr_groups);

	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id opal_sensor_driver_ids[] = अणु
	अणु
		.name = "opal-sensor",
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, opal_sensor_driver_ids);

अटल स्थिर काष्ठा of_device_id opal_sensor_match[] = अणु
	अणु .compatible	= "ibm,opal-sensor" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, opal_sensor_match);

अटल काष्ठा platक्रमm_driver ibmघातernv_driver = अणु
	.probe		= ibmघातernv_probe,
	.id_table	= opal_sensor_driver_ids,
	.driver		= अणु
		.name	= DRVNAME,
		.of_match_table	= opal_sensor_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ibmघातernv_driver);

MODULE_AUTHOR("Neelesh Gupta <neelegup@linux.vnet.ibm.com>");
MODULE_DESCRIPTION("IBM POWERNV platform sensors");
MODULE_LICENSE("GPL");
