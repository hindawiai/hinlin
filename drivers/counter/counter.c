<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic Counter पूर्णांकerface
 * Copyright (C) 2018 William Breathitt Gray
 */
#समावेश <linux/counter.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/fs.h>
#समावेश <linux/gfp.h>
#समावेश <linux/idr.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>

स्थिर अक्षर *स्थिर counter_count_direction_str[2] = अणु
	[COUNTER_COUNT_सूचीECTION_FORWARD] = "forward",
	[COUNTER_COUNT_सूचीECTION_BACKWARD] = "backward"
पूर्ण;
EXPORT_SYMBOL_GPL(counter_count_direction_str);

स्थिर अक्षर *स्थिर counter_count_mode_str[4] = अणु
	[COUNTER_COUNT_MODE_NORMAL] = "normal",
	[COUNTER_COUNT_MODE_RANGE_LIMIT] = "range limit",
	[COUNTER_COUNT_MODE_NON_RECYCLE] = "non-recycle",
	[COUNTER_COUNT_MODE_MODULO_N] = "modulo-n"
पूर्ण;
EXPORT_SYMBOL_GPL(counter_count_mode_str);

sमाप_प्रकार counter_संकेत_क्रमागत_पढ़ो(काष्ठा counter_device *counter,
				 काष्ठा counter_संकेत *संकेत, व्योम *priv,
				 अक्षर *buf)
अणु
	स्थिर काष्ठा counter_संकेत_क्रमागत_ext *स्थिर e = priv;
	पूर्णांक err;
	माप_प्रकार index;

	अगर (!e->get)
		वापस -EINVAL;

	err = e->get(counter, संकेत, &index);
	अगर (err)
		वापस err;

	अगर (index >= e->num_items)
		वापस -EINVAL;

	वापस प्र_लिखो(buf, "%s\n", e->items[index]);
पूर्ण
EXPORT_SYMBOL_GPL(counter_संकेत_क्रमागत_पढ़ो);

sमाप_प्रकार counter_संकेत_क्रमागत_ग_लिखो(काष्ठा counter_device *counter,
				  काष्ठा counter_संकेत *संकेत, व्योम *priv,
				  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	स्थिर काष्ठा counter_संकेत_क्रमागत_ext *स्थिर e = priv;
	sमाप_प्रकार index;
	पूर्णांक err;

	अगर (!e->set)
		वापस -EINVAL;

	index = __sysfs_match_string(e->items, e->num_items, buf);
	अगर (index < 0)
		वापस index;

	err = e->set(counter, संकेत, index);
	अगर (err)
		वापस err;

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(counter_संकेत_क्रमागत_ग_लिखो);

sमाप_प्रकार counter_संकेत_क्रमागत_available_पढ़ो(काष्ठा counter_device *counter,
					   काष्ठा counter_संकेत *संकेत,
					   व्योम *priv, अक्षर *buf)
अणु
	स्थिर काष्ठा counter_संकेत_क्रमागत_ext *स्थिर e = priv;
	माप_प्रकार i;
	माप_प्रकार len = 0;

	अगर (!e->num_items)
		वापस 0;

	क्रम (i = 0; i < e->num_items; i++)
		len += प्र_लिखो(buf + len, "%s\n", e->items[i]);

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(counter_संकेत_क्रमागत_available_पढ़ो);

sमाप_प्रकार counter_count_क्रमागत_पढ़ो(काष्ठा counter_device *counter,
				काष्ठा counter_count *count, व्योम *priv,
				अक्षर *buf)
अणु
	स्थिर काष्ठा counter_count_क्रमागत_ext *स्थिर e = priv;
	पूर्णांक err;
	माप_प्रकार index;

	अगर (!e->get)
		वापस -EINVAL;

	err = e->get(counter, count, &index);
	अगर (err)
		वापस err;

	अगर (index >= e->num_items)
		वापस -EINVAL;

	वापस प्र_लिखो(buf, "%s\n", e->items[index]);
पूर्ण
EXPORT_SYMBOL_GPL(counter_count_क्रमागत_पढ़ो);

sमाप_प्रकार counter_count_क्रमागत_ग_लिखो(काष्ठा counter_device *counter,
				 काष्ठा counter_count *count, व्योम *priv,
				 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	स्थिर काष्ठा counter_count_क्रमागत_ext *स्थिर e = priv;
	sमाप_प्रकार index;
	पूर्णांक err;

	अगर (!e->set)
		वापस -EINVAL;

	index = __sysfs_match_string(e->items, e->num_items, buf);
	अगर (index < 0)
		वापस index;

	err = e->set(counter, count, index);
	अगर (err)
		वापस err;

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(counter_count_क्रमागत_ग_लिखो);

sमाप_प्रकार counter_count_क्रमागत_available_पढ़ो(काष्ठा counter_device *counter,
					  काष्ठा counter_count *count,
					  व्योम *priv, अक्षर *buf)
अणु
	स्थिर काष्ठा counter_count_क्रमागत_ext *स्थिर e = priv;
	माप_प्रकार i;
	माप_प्रकार len = 0;

	अगर (!e->num_items)
		वापस 0;

	क्रम (i = 0; i < e->num_items; i++)
		len += प्र_लिखो(buf + len, "%s\n", e->items[i]);

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(counter_count_क्रमागत_available_पढ़ो);

sमाप_प्रकार counter_device_क्रमागत_पढ़ो(काष्ठा counter_device *counter, व्योम *priv,
				 अक्षर *buf)
अणु
	स्थिर काष्ठा counter_device_क्रमागत_ext *स्थिर e = priv;
	पूर्णांक err;
	माप_प्रकार index;

	अगर (!e->get)
		वापस -EINVAL;

	err = e->get(counter, &index);
	अगर (err)
		वापस err;

	अगर (index >= e->num_items)
		वापस -EINVAL;

	वापस प्र_लिखो(buf, "%s\n", e->items[index]);
पूर्ण
EXPORT_SYMBOL_GPL(counter_device_क्रमागत_पढ़ो);

sमाप_प्रकार counter_device_क्रमागत_ग_लिखो(काष्ठा counter_device *counter, व्योम *priv,
				  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	स्थिर काष्ठा counter_device_क्रमागत_ext *स्थिर e = priv;
	sमाप_प्रकार index;
	पूर्णांक err;

	अगर (!e->set)
		वापस -EINVAL;

	index = __sysfs_match_string(e->items, e->num_items, buf);
	अगर (index < 0)
		वापस index;

	err = e->set(counter, index);
	अगर (err)
		वापस err;

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(counter_device_क्रमागत_ग_लिखो);

sमाप_प्रकार counter_device_क्रमागत_available_पढ़ो(काष्ठा counter_device *counter,
					   व्योम *priv, अक्षर *buf)
अणु
	स्थिर काष्ठा counter_device_क्रमागत_ext *स्थिर e = priv;
	माप_प्रकार i;
	माप_प्रकार len = 0;

	अगर (!e->num_items)
		वापस 0;

	क्रम (i = 0; i < e->num_items; i++)
		len += प्र_लिखो(buf + len, "%s\n", e->items[i]);

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(counter_device_क्रमागत_available_पढ़ो);

काष्ठा counter_attr_parm अणु
	काष्ठा counter_device_attr_group *group;
	स्थिर अक्षर *prefix;
	स्थिर अक्षर *name;
	sमाप_प्रकार (*show)(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार len);
	व्योम *component;
पूर्ण;

काष्ठा counter_device_attr अणु
	काष्ठा device_attribute dev_attr;
	काष्ठा list_head l;
	व्योम *component;
पूर्ण;

अटल पूर्णांक counter_attribute_create(स्थिर काष्ठा counter_attr_parm *स्थिर parm)
अणु
	काष्ठा counter_device_attr *counter_attr;
	काष्ठा device_attribute *dev_attr;
	पूर्णांक err;
	काष्ठा list_head *स्थिर attr_list = &parm->group->attr_list;

	/* Allocate a Counter device attribute */
	counter_attr = kzalloc(माप(*counter_attr), GFP_KERNEL);
	अगर (!counter_attr)
		वापस -ENOMEM;
	dev_attr = &counter_attr->dev_attr;

	sysfs_attr_init(&dev_attr->attr);

	/* Configure device attribute */
	dev_attr->attr.name = kaप्र_लिखो(GFP_KERNEL, "%s%s", parm->prefix,
					parm->name);
	अगर (!dev_attr->attr.name) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_counter_attr;
	पूर्ण
	अगर (parm->show) अणु
		dev_attr->attr.mode |= 0444;
		dev_attr->show = parm->show;
	पूर्ण
	अगर (parm->store) अणु
		dev_attr->attr.mode |= 0200;
		dev_attr->store = parm->store;
	पूर्ण

	/* Store associated Counter component with attribute */
	counter_attr->component = parm->component;

	/* Keep track of the attribute क्रम later cleanup */
	list_add(&counter_attr->l, attr_list);
	parm->group->num_attr++;

	वापस 0;

err_मुक्त_counter_attr:
	kमुक्त(counter_attr);
	वापस err;
पूर्ण

#घोषणा to_counter_attr(_dev_attr) \
	container_of(_dev_attr, काष्ठा counter_device_attr, dev_attr)

काष्ठा counter_संकेत_unit अणु
	काष्ठा counter_संकेत *संकेत;
पूर्ण;

अटल स्थिर अक्षर *स्थिर counter_संकेत_value_str[] = अणु
	[COUNTER_SIGNAL_LOW] = "low",
	[COUNTER_SIGNAL_HIGH] = "high"
पूर्ण;

अटल sमाप_प्रकार counter_संकेत_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा counter_device *स्थिर counter = dev_get_drvdata(dev);
	स्थिर काष्ठा counter_device_attr *स्थिर devattr = to_counter_attr(attr);
	स्थिर काष्ठा counter_संकेत_unit *स्थिर component = devattr->component;
	काष्ठा counter_संकेत *स्थिर संकेत = component->संकेत;
	पूर्णांक err;
	क्रमागत counter_संकेत_value val;

	err = counter->ops->संकेत_पढ़ो(counter, संकेत, &val);
	अगर (err)
		वापस err;

	वापस प्र_लिखो(buf, "%s\n", counter_संकेत_value_str[val]);
पूर्ण

काष्ठा counter_name_unit अणु
	स्थिर अक्षर *name;
पूर्ण;

अटल sमाप_प्रकार counter_device_attr_name_show(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	स्थिर काष्ठा counter_name_unit *स्थिर comp = to_counter_attr(attr)->component;

	वापस प्र_लिखो(buf, "%s\n", comp->name);
पूर्ण

अटल पूर्णांक counter_name_attribute_create(
	काष्ठा counter_device_attr_group *स्थिर group,
	स्थिर अक्षर *स्थिर name)
अणु
	काष्ठा counter_name_unit *name_comp;
	काष्ठा counter_attr_parm parm;
	पूर्णांक err;

	/* Skip अगर no name */
	अगर (!name)
		वापस 0;

	/* Allocate name attribute component */
	name_comp = kदो_स्मृति(माप(*name_comp), GFP_KERNEL);
	अगर (!name_comp)
		वापस -ENOMEM;
	name_comp->name = name;

	/* Allocate Signal name attribute */
	parm.group = group;
	parm.prefix = "";
	parm.name = "name";
	parm.show = counter_device_attr_name_show;
	parm.store = शून्य;
	parm.component = name_comp;
	err = counter_attribute_create(&parm);
	अगर (err)
		जाओ err_मुक्त_name_comp;

	वापस 0;

err_मुक्त_name_comp:
	kमुक्त(name_comp);
	वापस err;
पूर्ण

काष्ठा counter_संकेत_ext_unit अणु
	काष्ठा counter_संकेत *संकेत;
	स्थिर काष्ठा counter_संकेत_ext *ext;
पूर्ण;

अटल sमाप_प्रकार counter_संकेत_ext_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	स्थिर काष्ठा counter_device_attr *स्थिर devattr = to_counter_attr(attr);
	स्थिर काष्ठा counter_संकेत_ext_unit *स्थिर comp = devattr->component;
	स्थिर काष्ठा counter_संकेत_ext *स्थिर ext = comp->ext;

	वापस ext->पढ़ो(dev_get_drvdata(dev), comp->संकेत, ext->priv, buf);
पूर्ण

अटल sमाप_प्रकार counter_संकेत_ext_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	स्थिर काष्ठा counter_device_attr *स्थिर devattr = to_counter_attr(attr);
	स्थिर काष्ठा counter_संकेत_ext_unit *स्थिर comp = devattr->component;
	स्थिर काष्ठा counter_संकेत_ext *स्थिर ext = comp->ext;

	वापस ext->ग_लिखो(dev_get_drvdata(dev), comp->संकेत, ext->priv, buf,
		len);
पूर्ण

अटल व्योम counter_device_attr_list_मुक्त(काष्ठा list_head *attr_list)
अणु
	काष्ठा counter_device_attr *p, *n;

	list_क्रम_each_entry_safe(p, n, attr_list, l) अणु
		/* मुक्त attribute name and associated component memory */
		kमुक्त(p->dev_attr.attr.name);
		kमुक्त(p->component);
		list_del(&p->l);
		kमुक्त(p);
	पूर्ण
पूर्ण

अटल पूर्णांक counter_संकेत_ext_रेजिस्टर(
	काष्ठा counter_device_attr_group *स्थिर group,
	काष्ठा counter_संकेत *स्थिर संकेत)
अणु
	स्थिर माप_प्रकार num_ext = संकेत->num_ext;
	माप_प्रकार i;
	स्थिर काष्ठा counter_संकेत_ext *ext;
	काष्ठा counter_संकेत_ext_unit *संकेत_ext_comp;
	काष्ठा counter_attr_parm parm;
	पूर्णांक err;

	/* Create an attribute क्रम each extension */
	क्रम (i = 0 ; i < num_ext; i++) अणु
		ext = संकेत->ext + i;

		/* Allocate संकेत_ext attribute component */
		संकेत_ext_comp = kदो_स्मृति(माप(*संकेत_ext_comp), GFP_KERNEL);
		अगर (!संकेत_ext_comp) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_attr_list;
		पूर्ण
		संकेत_ext_comp->संकेत = संकेत;
		संकेत_ext_comp->ext = ext;

		/* Allocate a Counter device attribute */
		parm.group = group;
		parm.prefix = "";
		parm.name = ext->name;
		parm.show = (ext->पढ़ो) ? counter_संकेत_ext_show : शून्य;
		parm.store = (ext->ग_लिखो) ? counter_संकेत_ext_store : शून्य;
		parm.component = संकेत_ext_comp;
		err = counter_attribute_create(&parm);
		अगर (err) अणु
			kमुक्त(संकेत_ext_comp);
			जाओ err_मुक्त_attr_list;
		पूर्ण
	पूर्ण

	वापस 0;

err_मुक्त_attr_list:
	counter_device_attr_list_मुक्त(&group->attr_list);
	वापस err;
पूर्ण

अटल पूर्णांक counter_संकेत_attributes_create(
	काष्ठा counter_device_attr_group *स्थिर group,
	स्थिर काष्ठा counter_device *स्थिर counter,
	काष्ठा counter_संकेत *स्थिर संकेत)
अणु
	काष्ठा counter_संकेत_unit *संकेत_comp;
	काष्ठा counter_attr_parm parm;
	पूर्णांक err;

	/* Allocate Signal attribute component */
	संकेत_comp = kदो_स्मृति(माप(*संकेत_comp), GFP_KERNEL);
	अगर (!संकेत_comp)
		वापस -ENOMEM;
	संकेत_comp->संकेत = संकेत;

	/* Create मुख्य Signal attribute */
	parm.group = group;
	parm.prefix = "";
	parm.name = "signal";
	parm.show = (counter->ops->संकेत_पढ़ो) ? counter_संकेत_show : शून्य;
	parm.store = शून्य;
	parm.component = संकेत_comp;
	err = counter_attribute_create(&parm);
	अगर (err) अणु
		kमुक्त(संकेत_comp);
		वापस err;
	पूर्ण

	/* Create Signal name attribute */
	err = counter_name_attribute_create(group, संकेत->name);
	अगर (err)
		जाओ err_मुक्त_attr_list;

	/* Register Signal extension attributes */
	err = counter_संकेत_ext_रेजिस्टर(group, संकेत);
	अगर (err)
		जाओ err_मुक्त_attr_list;

	वापस 0;

err_मुक्त_attr_list:
	counter_device_attr_list_मुक्त(&group->attr_list);
	वापस err;
पूर्ण

अटल पूर्णांक counter_संकेतs_रेजिस्टर(
	काष्ठा counter_device_attr_group *स्थिर groups_list,
	स्थिर काष्ठा counter_device *स्थिर counter)
अणु
	स्थिर माप_प्रकार num_संकेतs = counter->num_संकेतs;
	माप_प्रकार i;
	काष्ठा counter_संकेत *संकेत;
	स्थिर अक्षर *name;
	पूर्णांक err;

	/* Register each Signal */
	क्रम (i = 0; i < num_संकेतs; i++) अणु
		संकेत = counter->संकेतs + i;

		/* Generate Signal attribute directory name */
		name = kaप्र_लिखो(GFP_KERNEL, "signal%d", संकेत->id);
		अगर (!name) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_attr_groups;
		पूर्ण
		groups_list[i].attr_group.name = name;

		/* Create all attributes associated with Signal */
		err = counter_संकेत_attributes_create(groups_list + i, counter,
						       संकेत);
		अगर (err)
			जाओ err_मुक्त_attr_groups;
	पूर्ण

	वापस 0;

err_मुक्त_attr_groups:
	करो अणु
		kमुक्त(groups_list[i].attr_group.name);
		counter_device_attr_list_मुक्त(&groups_list[i].attr_list);
	पूर्ण जबतक (i--);
	वापस err;
पूर्ण

अटल स्थिर अक्षर *स्थिर counter_synapse_action_str[] = अणु
	[COUNTER_SYNAPSE_ACTION_NONE] = "none",
	[COUNTER_SYNAPSE_ACTION_RISING_EDGE] = "rising edge",
	[COUNTER_SYNAPSE_ACTION_FALLING_EDGE] = "falling edge",
	[COUNTER_SYNAPSE_ACTION_BOTH_EDGES] = "both edges"
पूर्ण;

काष्ठा counter_action_unit अणु
	काष्ठा counter_synapse *synapse;
	काष्ठा counter_count *count;
पूर्ण;

अटल sमाप_प्रकार counter_action_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	स्थिर काष्ठा counter_device_attr *स्थिर devattr = to_counter_attr(attr);
	पूर्णांक err;
	काष्ठा counter_device *स्थिर counter = dev_get_drvdata(dev);
	स्थिर काष्ठा counter_action_unit *स्थिर component = devattr->component;
	काष्ठा counter_count *स्थिर count = component->count;
	काष्ठा counter_synapse *स्थिर synapse = component->synapse;
	माप_प्रकार action_index;
	क्रमागत counter_synapse_action action;

	err = counter->ops->action_get(counter, count, synapse, &action_index);
	अगर (err)
		वापस err;

	synapse->action = action_index;

	action = synapse->actions_list[action_index];
	वापस प्र_लिखो(buf, "%s\n", counter_synapse_action_str[action]);
पूर्ण

अटल sमाप_प्रकार counter_action_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	स्थिर काष्ठा counter_device_attr *स्थिर devattr = to_counter_attr(attr);
	स्थिर काष्ठा counter_action_unit *स्थिर component = devattr->component;
	काष्ठा counter_synapse *स्थिर synapse = component->synapse;
	माप_प्रकार action_index;
	स्थिर माप_प्रकार num_actions = synapse->num_actions;
	क्रमागत counter_synapse_action action;
	पूर्णांक err;
	काष्ठा counter_device *स्थिर counter = dev_get_drvdata(dev);
	काष्ठा counter_count *स्थिर count = component->count;

	/* Find requested action mode */
	क्रम (action_index = 0; action_index < num_actions; action_index++) अणु
		action = synapse->actions_list[action_index];
		अगर (sysfs_streq(buf, counter_synapse_action_str[action]))
			अवरोध;
	पूर्ण
	/* If requested action mode not found */
	अगर (action_index >= num_actions)
		वापस -EINVAL;

	err = counter->ops->action_set(counter, count, synapse, action_index);
	अगर (err)
		वापस err;

	synapse->action = action_index;

	वापस len;
पूर्ण

काष्ठा counter_action_avail_unit अणु
	स्थिर क्रमागत counter_synapse_action *actions_list;
	माप_प्रकार num_actions;
पूर्ण;

अटल sमाप_प्रकार counter_synapse_action_available_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	स्थिर काष्ठा counter_device_attr *स्थिर devattr = to_counter_attr(attr);
	स्थिर काष्ठा counter_action_avail_unit *स्थिर component = devattr->component;
	माप_प्रकार i;
	क्रमागत counter_synapse_action action;
	sमाप_प्रकार len = 0;

	क्रम (i = 0; i < component->num_actions; i++) अणु
		action = component->actions_list[i];
		len += प्र_लिखो(buf + len, "%s\n",
			       counter_synapse_action_str[action]);
	पूर्ण

	वापस len;
पूर्ण

अटल पूर्णांक counter_synapses_रेजिस्टर(
	काष्ठा counter_device_attr_group *स्थिर group,
	स्थिर काष्ठा counter_device *स्थिर counter,
	काष्ठा counter_count *स्थिर count, स्थिर अक्षर *स्थिर count_attr_name)
अणु
	माप_प्रकार i;
	काष्ठा counter_synapse *synapse;
	स्थिर अक्षर *prefix;
	काष्ठा counter_action_unit *action_comp;
	काष्ठा counter_attr_parm parm;
	पूर्णांक err;
	काष्ठा counter_action_avail_unit *avail_comp;

	/* Register each Synapse */
	क्रम (i = 0; i < count->num_synapses; i++) अणु
		synapse = count->synapses + i;

		/* Generate attribute prefix */
		prefix = kaप्र_लिखो(GFP_KERNEL, "signal%d_",
				   synapse->संकेत->id);
		अगर (!prefix) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_attr_list;
		पूर्ण

		/* Allocate action attribute component */
		action_comp = kदो_स्मृति(माप(*action_comp), GFP_KERNEL);
		अगर (!action_comp) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_prefix;
		पूर्ण
		action_comp->synapse = synapse;
		action_comp->count = count;

		/* Create action attribute */
		parm.group = group;
		parm.prefix = prefix;
		parm.name = "action";
		parm.show = (counter->ops->action_get) ? counter_action_show : शून्य;
		parm.store = (counter->ops->action_set) ? counter_action_store : शून्य;
		parm.component = action_comp;
		err = counter_attribute_create(&parm);
		अगर (err) अणु
			kमुक्त(action_comp);
			जाओ err_मुक्त_prefix;
		पूर्ण

		/* Allocate action available attribute component */
		avail_comp = kदो_स्मृति(माप(*avail_comp), GFP_KERNEL);
		अगर (!avail_comp) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_prefix;
		पूर्ण
		avail_comp->actions_list = synapse->actions_list;
		avail_comp->num_actions = synapse->num_actions;

		/* Create action_available attribute */
		parm.group = group;
		parm.prefix = prefix;
		parm.name = "action_available";
		parm.show = counter_synapse_action_available_show;
		parm.store = शून्य;
		parm.component = avail_comp;
		err = counter_attribute_create(&parm);
		अगर (err) अणु
			kमुक्त(avail_comp);
			जाओ err_मुक्त_prefix;
		पूर्ण

		kमुक्त(prefix);
	पूर्ण

	वापस 0;

err_मुक्त_prefix:
	kमुक्त(prefix);
err_मुक्त_attr_list:
	counter_device_attr_list_मुक्त(&group->attr_list);
	वापस err;
पूर्ण

काष्ठा counter_count_unit अणु
	काष्ठा counter_count *count;
पूर्ण;

अटल sमाप_प्रकार counter_count_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा counter_device *स्थिर counter = dev_get_drvdata(dev);
	स्थिर काष्ठा counter_device_attr *स्थिर devattr = to_counter_attr(attr);
	स्थिर काष्ठा counter_count_unit *स्थिर component = devattr->component;
	काष्ठा counter_count *स्थिर count = component->count;
	पूर्णांक err;
	अचिन्हित दीर्घ val;

	err = counter->ops->count_पढ़ो(counter, count, &val);
	अगर (err)
		वापस err;

	वापस प्र_लिखो(buf, "%lu\n", val);
पूर्ण

अटल sमाप_प्रकार counter_count_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा counter_device *स्थिर counter = dev_get_drvdata(dev);
	स्थिर काष्ठा counter_device_attr *स्थिर devattr = to_counter_attr(attr);
	स्थिर काष्ठा counter_count_unit *स्थिर component = devattr->component;
	काष्ठा counter_count *स्थिर count = component->count;
	पूर्णांक err;
	अचिन्हित दीर्घ val;

	err = kम_से_अदीर्घ(buf, 0, &val);
	अगर (err)
		वापस err;

	err = counter->ops->count_ग_लिखो(counter, count, val);
	अगर (err)
		वापस err;

	वापस len;
पूर्ण

अटल स्थिर अक्षर *स्थिर counter_count_function_str[] = अणु
	[COUNTER_COUNT_FUNCTION_INCREASE] = "increase",
	[COUNTER_COUNT_FUNCTION_DECREASE] = "decrease",
	[COUNTER_COUNT_FUNCTION_PULSE_सूचीECTION] = "pulse-direction",
	[COUNTER_COUNT_FUNCTION_QUADRATURE_X1_A] = "quadrature x1 a",
	[COUNTER_COUNT_FUNCTION_QUADRATURE_X1_B] = "quadrature x1 b",
	[COUNTER_COUNT_FUNCTION_QUADRATURE_X2_A] = "quadrature x2 a",
	[COUNTER_COUNT_FUNCTION_QUADRATURE_X2_B] = "quadrature x2 b",
	[COUNTER_COUNT_FUNCTION_QUADRATURE_X4] = "quadrature x4"
पूर्ण;

अटल sमाप_प्रकार counter_function_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक err;
	काष्ठा counter_device *स्थिर counter = dev_get_drvdata(dev);
	स्थिर काष्ठा counter_device_attr *स्थिर devattr = to_counter_attr(attr);
	स्थिर काष्ठा counter_count_unit *स्थिर component = devattr->component;
	काष्ठा counter_count *स्थिर count = component->count;
	माप_प्रकार func_index;
	क्रमागत counter_count_function function;

	err = counter->ops->function_get(counter, count, &func_index);
	अगर (err)
		वापस err;

	count->function = func_index;

	function = count->functions_list[func_index];
	वापस प्र_लिखो(buf, "%s\n", counter_count_function_str[function]);
पूर्ण

अटल sमाप_प्रकार counter_function_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	स्थिर काष्ठा counter_device_attr *स्थिर devattr = to_counter_attr(attr);
	स्थिर काष्ठा counter_count_unit *स्थिर component = devattr->component;
	काष्ठा counter_count *स्थिर count = component->count;
	स्थिर माप_प्रकार num_functions = count->num_functions;
	माप_प्रकार func_index;
	क्रमागत counter_count_function function;
	पूर्णांक err;
	काष्ठा counter_device *स्थिर counter = dev_get_drvdata(dev);

	/* Find requested Count function mode */
	क्रम (func_index = 0; func_index < num_functions; func_index++) अणु
		function = count->functions_list[func_index];
		अगर (sysfs_streq(buf, counter_count_function_str[function]))
			अवरोध;
	पूर्ण
	/* Return error अगर requested Count function mode not found */
	अगर (func_index >= num_functions)
		वापस -EINVAL;

	err = counter->ops->function_set(counter, count, func_index);
	अगर (err)
		वापस err;

	count->function = func_index;

	वापस len;
पूर्ण

काष्ठा counter_count_ext_unit अणु
	काष्ठा counter_count *count;
	स्थिर काष्ठा counter_count_ext *ext;
पूर्ण;

अटल sमाप_प्रकार counter_count_ext_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	स्थिर काष्ठा counter_device_attr *स्थिर devattr = to_counter_attr(attr);
	स्थिर काष्ठा counter_count_ext_unit *स्थिर comp = devattr->component;
	स्थिर काष्ठा counter_count_ext *स्थिर ext = comp->ext;

	वापस ext->पढ़ो(dev_get_drvdata(dev), comp->count, ext->priv, buf);
पूर्ण

अटल sमाप_प्रकार counter_count_ext_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	स्थिर काष्ठा counter_device_attr *स्थिर devattr = to_counter_attr(attr);
	स्थिर काष्ठा counter_count_ext_unit *स्थिर comp = devattr->component;
	स्थिर काष्ठा counter_count_ext *स्थिर ext = comp->ext;

	वापस ext->ग_लिखो(dev_get_drvdata(dev), comp->count, ext->priv, buf,
		len);
पूर्ण

अटल पूर्णांक counter_count_ext_रेजिस्टर(
	काष्ठा counter_device_attr_group *स्थिर group,
	काष्ठा counter_count *स्थिर count)
अणु
	माप_प्रकार i;
	स्थिर काष्ठा counter_count_ext *ext;
	काष्ठा counter_count_ext_unit *count_ext_comp;
	काष्ठा counter_attr_parm parm;
	पूर्णांक err;

	/* Create an attribute क्रम each extension */
	क्रम (i = 0 ; i < count->num_ext; i++) अणु
		ext = count->ext + i;

		/* Allocate count_ext attribute component */
		count_ext_comp = kदो_स्मृति(माप(*count_ext_comp), GFP_KERNEL);
		अगर (!count_ext_comp) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_attr_list;
		पूर्ण
		count_ext_comp->count = count;
		count_ext_comp->ext = ext;

		/* Allocate count_ext attribute */
		parm.group = group;
		parm.prefix = "";
		parm.name = ext->name;
		parm.show = (ext->पढ़ो) ? counter_count_ext_show : शून्य;
		parm.store = (ext->ग_लिखो) ? counter_count_ext_store : शून्य;
		parm.component = count_ext_comp;
		err = counter_attribute_create(&parm);
		अगर (err) अणु
			kमुक्त(count_ext_comp);
			जाओ err_मुक्त_attr_list;
		पूर्ण
	पूर्ण

	वापस 0;

err_मुक्त_attr_list:
	counter_device_attr_list_मुक्त(&group->attr_list);
	वापस err;
पूर्ण

काष्ठा counter_func_avail_unit अणु
	स्थिर क्रमागत counter_count_function *functions_list;
	माप_प्रकार num_functions;
पूर्ण;

अटल sमाप_प्रकार counter_count_function_available_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	स्थिर काष्ठा counter_device_attr *स्थिर devattr = to_counter_attr(attr);
	स्थिर काष्ठा counter_func_avail_unit *स्थिर component = devattr->component;
	स्थिर क्रमागत counter_count_function *स्थिर func_list = component->functions_list;
	स्थिर माप_प्रकार num_functions = component->num_functions;
	माप_प्रकार i;
	क्रमागत counter_count_function function;
	sमाप_प्रकार len = 0;

	क्रम (i = 0; i < num_functions; i++) अणु
		function = func_list[i];
		len += प्र_लिखो(buf + len, "%s\n",
			       counter_count_function_str[function]);
	पूर्ण

	वापस len;
पूर्ण

अटल पूर्णांक counter_count_attributes_create(
	काष्ठा counter_device_attr_group *स्थिर group,
	स्थिर काष्ठा counter_device *स्थिर counter,
	काष्ठा counter_count *स्थिर count)
अणु
	काष्ठा counter_count_unit *count_comp;
	काष्ठा counter_attr_parm parm;
	पूर्णांक err;
	काष्ठा counter_count_unit *func_comp;
	काष्ठा counter_func_avail_unit *avail_comp;

	/* Allocate count attribute component */
	count_comp = kदो_स्मृति(माप(*count_comp), GFP_KERNEL);
	अगर (!count_comp)
		वापस -ENOMEM;
	count_comp->count = count;

	/* Create मुख्य Count attribute */
	parm.group = group;
	parm.prefix = "";
	parm.name = "count";
	parm.show = (counter->ops->count_पढ़ो) ? counter_count_show : शून्य;
	parm.store = (counter->ops->count_ग_लिखो) ? counter_count_store : शून्य;
	parm.component = count_comp;
	err = counter_attribute_create(&parm);
	अगर (err) अणु
		kमुक्त(count_comp);
		वापस err;
	पूर्ण

	/* Allocate function attribute component */
	func_comp = kदो_स्मृति(माप(*func_comp), GFP_KERNEL);
	अगर (!func_comp) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_attr_list;
	पूर्ण
	func_comp->count = count;

	/* Create Count function attribute */
	parm.group = group;
	parm.prefix = "";
	parm.name = "function";
	parm.show = (counter->ops->function_get) ? counter_function_show : शून्य;
	parm.store = (counter->ops->function_set) ? counter_function_store : शून्य;
	parm.component = func_comp;
	err = counter_attribute_create(&parm);
	अगर (err) अणु
		kमुक्त(func_comp);
		जाओ err_मुक्त_attr_list;
	पूर्ण

	/* Allocate function available attribute component */
	avail_comp = kदो_स्मृति(माप(*avail_comp), GFP_KERNEL);
	अगर (!avail_comp) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_attr_list;
	पूर्ण
	avail_comp->functions_list = count->functions_list;
	avail_comp->num_functions = count->num_functions;

	/* Create Count function_available attribute */
	parm.group = group;
	parm.prefix = "";
	parm.name = "function_available";
	parm.show = counter_count_function_available_show;
	parm.store = शून्य;
	parm.component = avail_comp;
	err = counter_attribute_create(&parm);
	अगर (err) अणु
		kमुक्त(avail_comp);
		जाओ err_मुक्त_attr_list;
	पूर्ण

	/* Create Count name attribute */
	err = counter_name_attribute_create(group, count->name);
	अगर (err)
		जाओ err_मुक्त_attr_list;

	/* Register Count extension attributes */
	err = counter_count_ext_रेजिस्टर(group, count);
	अगर (err)
		जाओ err_मुक्त_attr_list;

	वापस 0;

err_मुक्त_attr_list:
	counter_device_attr_list_मुक्त(&group->attr_list);
	वापस err;
पूर्ण

अटल पूर्णांक counter_counts_रेजिस्टर(
	काष्ठा counter_device_attr_group *स्थिर groups_list,
	स्थिर काष्ठा counter_device *स्थिर counter)
अणु
	माप_प्रकार i;
	काष्ठा counter_count *count;
	स्थिर अक्षर *name;
	पूर्णांक err;

	/* Register each Count */
	क्रम (i = 0; i < counter->num_counts; i++) अणु
		count = counter->counts + i;

		/* Generate Count attribute directory name */
		name = kaप्र_लिखो(GFP_KERNEL, "count%d", count->id);
		अगर (!name) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_attr_groups;
		पूर्ण
		groups_list[i].attr_group.name = name;

		/* Register the Synapses associated with each Count */
		err = counter_synapses_रेजिस्टर(groups_list + i, counter, count,
						name);
		अगर (err)
			जाओ err_मुक्त_attr_groups;

		/* Create all attributes associated with Count */
		err = counter_count_attributes_create(groups_list + i, counter,
						      count);
		अगर (err)
			जाओ err_मुक्त_attr_groups;
	पूर्ण

	वापस 0;

err_मुक्त_attr_groups:
	करो अणु
		kमुक्त(groups_list[i].attr_group.name);
		counter_device_attr_list_मुक्त(&groups_list[i].attr_list);
	पूर्ण जबतक (i--);
	वापस err;
पूर्ण

काष्ठा counter_size_unit अणु
	माप_प्रकार size;
पूर्ण;

अटल sमाप_प्रकार counter_device_attr_size_show(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	स्थिर काष्ठा counter_size_unit *स्थिर comp = to_counter_attr(attr)->component;

	वापस प्र_लिखो(buf, "%zu\n", comp->size);
पूर्ण

अटल पूर्णांक counter_size_attribute_create(
	काष्ठा counter_device_attr_group *स्थिर group,
	स्थिर माप_प्रकार size, स्थिर अक्षर *स्थिर name)
अणु
	काष्ठा counter_size_unit *size_comp;
	काष्ठा counter_attr_parm parm;
	पूर्णांक err;

	/* Allocate size attribute component */
	size_comp = kदो_स्मृति(माप(*size_comp), GFP_KERNEL);
	अगर (!size_comp)
		वापस -ENOMEM;
	size_comp->size = size;

	parm.group = group;
	parm.prefix = "";
	parm.name = name;
	parm.show = counter_device_attr_size_show;
	parm.store = शून्य;
	parm.component = size_comp;
	err = counter_attribute_create(&parm);
	अगर (err)
		जाओ err_मुक्त_size_comp;

	वापस 0;

err_मुक्त_size_comp:
	kमुक्त(size_comp);
	वापस err;
पूर्ण

काष्ठा counter_ext_unit अणु
	स्थिर काष्ठा counter_device_ext *ext;
पूर्ण;

अटल sमाप_प्रकार counter_device_ext_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	स्थिर काष्ठा counter_device_attr *स्थिर devattr = to_counter_attr(attr);
	स्थिर काष्ठा counter_ext_unit *स्थिर component = devattr->component;
	स्थिर काष्ठा counter_device_ext *स्थिर ext = component->ext;

	वापस ext->पढ़ो(dev_get_drvdata(dev), ext->priv, buf);
पूर्ण

अटल sमाप_प्रकार counter_device_ext_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	स्थिर काष्ठा counter_device_attr *स्थिर devattr = to_counter_attr(attr);
	स्थिर काष्ठा counter_ext_unit *स्थिर component = devattr->component;
	स्थिर काष्ठा counter_device_ext *स्थिर ext = component->ext;

	वापस ext->ग_लिखो(dev_get_drvdata(dev), ext->priv, buf, len);
पूर्ण

अटल पूर्णांक counter_device_ext_रेजिस्टर(
	काष्ठा counter_device_attr_group *स्थिर group,
	काष्ठा counter_device *स्थिर counter)
अणु
	माप_प्रकार i;
	काष्ठा counter_ext_unit *ext_comp;
	काष्ठा counter_attr_parm parm;
	पूर्णांक err;

	/* Create an attribute क्रम each extension */
	क्रम (i = 0 ; i < counter->num_ext; i++) अणु
		/* Allocate extension attribute component */
		ext_comp = kदो_स्मृति(माप(*ext_comp), GFP_KERNEL);
		अगर (!ext_comp) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_attr_list;
		पूर्ण

		ext_comp->ext = counter->ext + i;

		/* Allocate extension attribute */
		parm.group = group;
		parm.prefix = "";
		parm.name = counter->ext[i].name;
		parm.show = (counter->ext[i].पढ़ो) ? counter_device_ext_show : शून्य;
		parm.store = (counter->ext[i].ग_लिखो) ? counter_device_ext_store : शून्य;
		parm.component = ext_comp;
		err = counter_attribute_create(&parm);
		अगर (err) अणु
			kमुक्त(ext_comp);
			जाओ err_मुक्त_attr_list;
		पूर्ण
	पूर्ण

	वापस 0;

err_मुक्त_attr_list:
	counter_device_attr_list_मुक्त(&group->attr_list);
	वापस err;
पूर्ण

अटल पूर्णांक counter_global_attr_रेजिस्टर(
	काष्ठा counter_device_attr_group *स्थिर group,
	काष्ठा counter_device *स्थिर counter)
अणु
	पूर्णांक err;

	/* Create name attribute */
	err = counter_name_attribute_create(group, counter->name);
	अगर (err)
		वापस err;

	/* Create num_counts attribute */
	err = counter_size_attribute_create(group, counter->num_counts,
					    "num_counts");
	अगर (err)
		जाओ err_मुक्त_attr_list;

	/* Create num_संकेतs attribute */
	err = counter_size_attribute_create(group, counter->num_संकेतs,
					    "num_signals");
	अगर (err)
		जाओ err_मुक्त_attr_list;

	/* Register Counter device extension attributes */
	err = counter_device_ext_रेजिस्टर(group, counter);
	अगर (err)
		जाओ err_मुक्त_attr_list;

	वापस 0;

err_मुक्त_attr_list:
	counter_device_attr_list_मुक्त(&group->attr_list);
	वापस err;
पूर्ण

अटल व्योम counter_device_groups_list_मुक्त(
	काष्ठा counter_device_attr_group *स्थिर groups_list,
	स्थिर माप_प्रकार num_groups)
अणु
	काष्ठा counter_device_attr_group *group;
	माप_प्रकार i;

	/* loop through all attribute groups (संकेतs, counts, global, etc.) */
	क्रम (i = 0; i < num_groups; i++) अणु
		group = groups_list + i;

		/* मुक्त all attribute group and associated attributes memory */
		kमुक्त(group->attr_group.name);
		kमुक्त(group->attr_group.attrs);
		counter_device_attr_list_मुक्त(&group->attr_list);
	पूर्ण

	kमुक्त(groups_list);
पूर्ण

अटल पूर्णांक counter_device_groups_list_prepare(
	काष्ठा counter_device *स्थिर counter)
अणु
	स्थिर माप_प्रकार total_num_groups =
		counter->num_संकेतs + counter->num_counts + 1;
	काष्ठा counter_device_attr_group *groups_list;
	माप_प्रकार i;
	पूर्णांक err;
	माप_प्रकार num_groups = 0;

	/* Allocate space क्रम attribute groups (संकेतs, counts, and ext) */
	groups_list = kसुस्मृति(total_num_groups, माप(*groups_list),
			      GFP_KERNEL);
	अगर (!groups_list)
		वापस -ENOMEM;

	/* Initialize attribute lists */
	क्रम (i = 0; i < total_num_groups; i++)
		INIT_LIST_HEAD(&groups_list[i].attr_list);

	/* Register Signals */
	err = counter_संकेतs_रेजिस्टर(groups_list, counter);
	अगर (err)
		जाओ err_मुक्त_groups_list;
	num_groups += counter->num_संकेतs;

	/* Register Counts and respective Synapses */
	err = counter_counts_रेजिस्टर(groups_list + num_groups, counter);
	अगर (err)
		जाओ err_मुक्त_groups_list;
	num_groups += counter->num_counts;

	/* Register Counter global attributes */
	err = counter_global_attr_रेजिस्टर(groups_list + num_groups, counter);
	अगर (err)
		जाओ err_मुक्त_groups_list;
	num_groups++;

	/* Store groups_list in device_state */
	counter->device_state->groups_list = groups_list;
	counter->device_state->num_groups = num_groups;

	वापस 0;

err_मुक्त_groups_list:
	counter_device_groups_list_मुक्त(groups_list, num_groups);
	वापस err;
पूर्ण

अटल पूर्णांक counter_device_groups_prepare(
	काष्ठा counter_device_state *स्थिर device_state)
अणु
	माप_प्रकार i, j;
	काष्ठा counter_device_attr_group *group;
	पूर्णांक err;
	काष्ठा counter_device_attr *p;

	/* Allocate attribute groups क्रम association with device */
	device_state->groups = kसुस्मृति(device_state->num_groups + 1,
				       माप(*device_state->groups),
				       GFP_KERNEL);
	अगर (!device_state->groups)
		वापस -ENOMEM;

	/* Prepare each group of attributes क्रम association */
	क्रम (i = 0; i < device_state->num_groups; i++) अणु
		group = device_state->groups_list + i;

		/* Allocate space क्रम attribute poपूर्णांकers in attribute group */
		group->attr_group.attrs = kसुस्मृति(group->num_attr + 1,
			माप(*group->attr_group.attrs), GFP_KERNEL);
		अगर (!group->attr_group.attrs) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_groups;
		पूर्ण

		/* Add attribute poपूर्णांकers to attribute group */
		j = 0;
		list_क्रम_each_entry(p, &group->attr_list, l)
			group->attr_group.attrs[j++] = &p->dev_attr.attr;

		/* Group attributes in attribute group */
		device_state->groups[i] = &group->attr_group;
	पूर्ण
	/* Associate attributes with device */
	device_state->dev.groups = device_state->groups;

	वापस 0;

err_मुक्त_groups:
	करो अणु
		group = device_state->groups_list + i;
		kमुक्त(group->attr_group.attrs);
		group->attr_group.attrs = शून्य;
	पूर्ण जबतक (i--);
	kमुक्त(device_state->groups);
	वापस err;
पूर्ण

/* Provides a unique ID क्रम each counter device */
अटल DEFINE_IDA(counter_ida);

अटल व्योम counter_device_release(काष्ठा device *dev)
अणु
	काष्ठा counter_device *स्थिर counter = dev_get_drvdata(dev);
	काष्ठा counter_device_state *स्थिर device_state = counter->device_state;

	kमुक्त(device_state->groups);
	counter_device_groups_list_मुक्त(device_state->groups_list,
					device_state->num_groups);
	ida_simple_हटाओ(&counter_ida, device_state->id);
	kमुक्त(device_state);
पूर्ण

अटल काष्ठा device_type counter_device_type = अणु
	.name = "counter_device",
	.release = counter_device_release
पूर्ण;

अटल काष्ठा bus_type counter_bus_type = अणु
	.name = "counter"
पूर्ण;

/**
 * counter_रेजिस्टर - रेजिस्टर Counter to the प्रणाली
 * @counter:	poपूर्णांकer to Counter to रेजिस्टर
 *
 * This function रेजिस्टरs a Counter to the प्रणाली. A sysfs "counter" directory
 * will be created and populated with sysfs attributes correlating with the
 * Counter Signals, Synapses, and Counts respectively.
 */
पूर्णांक counter_रेजिस्टर(काष्ठा counter_device *स्थिर counter)
अणु
	काष्ठा counter_device_state *device_state;
	पूर्णांक err;

	/* Allocate पूर्णांकernal state container क्रम Counter device */
	device_state = kzalloc(माप(*device_state), GFP_KERNEL);
	अगर (!device_state)
		वापस -ENOMEM;
	counter->device_state = device_state;

	/* Acquire unique ID */
	device_state->id = ida_simple_get(&counter_ida, 0, 0, GFP_KERNEL);
	अगर (device_state->id < 0) अणु
		err = device_state->id;
		जाओ err_मुक्त_device_state;
	पूर्ण

	/* Configure device काष्ठाure क्रम Counter */
	device_state->dev.type = &counter_device_type;
	device_state->dev.bus = &counter_bus_type;
	अगर (counter->parent) अणु
		device_state->dev.parent = counter->parent;
		device_state->dev.of_node = counter->parent->of_node;
	पूर्ण
	dev_set_name(&device_state->dev, "counter%d", device_state->id);
	device_initialize(&device_state->dev);
	dev_set_drvdata(&device_state->dev, counter);

	/* Prepare device attributes */
	err = counter_device_groups_list_prepare(counter);
	अगर (err)
		जाओ err_मुक्त_id;

	/* Organize device attributes to groups and match to device */
	err = counter_device_groups_prepare(device_state);
	अगर (err)
		जाओ err_मुक्त_groups_list;

	/* Add device to प्रणाली */
	err = device_add(&device_state->dev);
	अगर (err)
		जाओ err_मुक्त_groups;

	वापस 0;

err_मुक्त_groups:
	kमुक्त(device_state->groups);
err_मुक्त_groups_list:
	counter_device_groups_list_मुक्त(device_state->groups_list,
					device_state->num_groups);
err_मुक्त_id:
	ida_simple_हटाओ(&counter_ida, device_state->id);
err_मुक्त_device_state:
	kमुक्त(device_state);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(counter_रेजिस्टर);

/**
 * counter_unरेजिस्टर - unरेजिस्टर Counter from the प्रणाली
 * @counter:	poपूर्णांकer to Counter to unरेजिस्टर
 *
 * The Counter is unरेजिस्टरed from the प्रणाली; all allocated memory is मुक्तd.
 */
व्योम counter_unरेजिस्टर(काष्ठा counter_device *स्थिर counter)
अणु
	अगर (counter)
		device_del(&counter->device_state->dev);
पूर्ण
EXPORT_SYMBOL_GPL(counter_unरेजिस्टर);

अटल व्योम devm_counter_unreg(काष्ठा device *dev, व्योम *res)
अणु
	counter_unरेजिस्टर(*(काष्ठा counter_device **)res);
पूर्ण

/**
 * devm_counter_रेजिस्टर - Resource-managed counter_रेजिस्टर
 * @dev:	device to allocate counter_device क्रम
 * @counter:	poपूर्णांकer to Counter to रेजिस्टर
 *
 * Managed counter_रेजिस्टर. The Counter रेजिस्टरed with this function is
 * स्वतःmatically unरेजिस्टरed on driver detach. This function calls
 * counter_रेजिस्टर पूर्णांकernally. Refer to that function क्रम more inक्रमmation.
 *
 * If an Counter रेजिस्टरed with this function needs to be unरेजिस्टरed
 * separately, devm_counter_unरेजिस्टर must be used.
 *
 * RETURNS:
 * 0 on success, negative error number on failure.
 */
पूर्णांक devm_counter_रेजिस्टर(काष्ठा device *dev,
			  काष्ठा counter_device *स्थिर counter)
अणु
	काष्ठा counter_device **ptr;
	पूर्णांक ret;

	ptr = devres_alloc(devm_counter_unreg, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	ret = counter_रेजिस्टर(counter);
	अगर (!ret) अणु
		*ptr = counter;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_counter_रेजिस्टर);

अटल पूर्णांक devm_counter_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा counter_device **r = res;

	अगर (!r || !*r) अणु
		WARN_ON(!r || !*r);
		वापस 0;
	पूर्ण

	वापस *r == data;
पूर्ण

/**
 * devm_counter_unरेजिस्टर - Resource-managed counter_unरेजिस्टर
 * @dev:	device this counter_device beदीर्घs to
 * @counter:	poपूर्णांकer to Counter associated with the device
 *
 * Unरेजिस्टर Counter रेजिस्टरed with devm_counter_रेजिस्टर.
 */
व्योम devm_counter_unरेजिस्टर(काष्ठा device *dev,
			     काष्ठा counter_device *स्थिर counter)
अणु
	पूर्णांक rc;

	rc = devres_release(dev, devm_counter_unreg, devm_counter_match,
			    counter);
	WARN_ON(rc);
पूर्ण
EXPORT_SYMBOL_GPL(devm_counter_unरेजिस्टर);

अटल पूर्णांक __init counter_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&counter_bus_type);
पूर्ण

अटल व्योम __निकास counter_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&counter_bus_type);
पूर्ण

subsys_initcall(counter_init);
module_निकास(counter_निकास);

MODULE_AUTHOR("William Breathitt Gray <vilhelm.gray@gmail.com>");
MODULE_DESCRIPTION("Generic Counter interface");
MODULE_LICENSE("GPL v2");
