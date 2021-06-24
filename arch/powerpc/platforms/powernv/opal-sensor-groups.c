<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerNV OPAL Sensor-groups पूर्णांकerface
 *
 * Copyright 2017 IBM Corp.
 */

#घोषणा pr_fmt(fmt)     "opal-sensor-groups: " fmt

#समावेश <linux/of.h>
#समावेश <linux/kobject.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/opal.h>

अटल DEFINE_MUTEX(sg_mutex);

अटल काष्ठा kobject *sg_kobj;

काष्ठा sg_attr अणु
	u32 handle;
	काष्ठा kobj_attribute attr;
पूर्ण;

अटल काष्ठा sensor_group अणु
	अक्षर name[20];
	काष्ठा attribute_group sg;
	काष्ठा sg_attr *sgattrs;
पूर्ण *sgs;

पूर्णांक sensor_group_enable(u32 handle, bool enable)
अणु
	काष्ठा opal_msg msg;
	पूर्णांक token, ret;

	token = opal_async_get_token_पूर्णांकerruptible();
	अगर (token < 0)
		वापस token;

	ret = opal_sensor_group_enable(handle, token, enable);
	अगर (ret == OPAL_ASYNC_COMPLETION) अणु
		ret = opal_async_रुको_response(token, &msg);
		अगर (ret) अणु
			pr_devel("Failed to wait for the async response\n");
			ret = -EIO;
			जाओ out;
		पूर्ण
		ret = opal_error_code(opal_get_async_rc(msg));
	पूर्ण अन्यथा अणु
		ret = opal_error_code(ret);
	पूर्ण

out:
	opal_async_release_token(token);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sensor_group_enable);

अटल sमाप_प्रकार sg_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sg_attr *sattr = container_of(attr, काष्ठा sg_attr, attr);
	काष्ठा opal_msg msg;
	u32 data;
	पूर्णांक ret, token;

	ret = kstrtoपूर्णांक(buf, 0, &data);
	अगर (ret)
		वापस ret;

	अगर (data != 1)
		वापस -EINVAL;

	token = opal_async_get_token_पूर्णांकerruptible();
	अगर (token < 0) अणु
		pr_devel("Failed to get token\n");
		वापस token;
	पूर्ण

	ret = mutex_lock_पूर्णांकerruptible(&sg_mutex);
	अगर (ret)
		जाओ out_token;

	ret = opal_sensor_group_clear(sattr->handle, token);
	चयन (ret) अणु
	हाल OPAL_ASYNC_COMPLETION:
		ret = opal_async_रुको_response(token, &msg);
		अगर (ret) अणु
			pr_devel("Failed to wait for the async response\n");
			ret = -EIO;
			जाओ out;
		पूर्ण
		ret = opal_error_code(opal_get_async_rc(msg));
		अगर (!ret)
			ret = count;
		अवरोध;
	हाल OPAL_SUCCESS:
		ret = count;
		अवरोध;
	शेष:
		ret = opal_error_code(ret);
	पूर्ण

out:
	mutex_unlock(&sg_mutex);
out_token:
	opal_async_release_token(token);
	वापस ret;
पूर्ण

अटल काष्ठा sg_ops_info अणु
	पूर्णांक opal_no;
	स्थिर अक्षर *attr_name;
	sमाप_प्रकार (*store)(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count);
पूर्ण ops_info[] = अणु
	अणु OPAL_SENSOR_GROUP_CLEAR, "clear", sg_store पूर्ण,
पूर्ण;

अटल व्योम add_attr(पूर्णांक handle, काष्ठा sg_attr *attr, पूर्णांक index)
अणु
	attr->handle = handle;
	sysfs_attr_init(&attr->attr.attr);
	attr->attr.attr.name = ops_info[index].attr_name;
	attr->attr.attr.mode = 0220;
	attr->attr.store = ops_info[index].store;
पूर्ण

अटल पूर्णांक add_attr_group(स्थिर __be32 *ops, पूर्णांक len, काष्ठा sensor_group *sg,
			   u32 handle)
अणु
	पूर्णांक i, j;
	पूर्णांक count = 0;

	क्रम (i = 0; i < len; i++)
		क्रम (j = 0; j < ARRAY_SIZE(ops_info); j++)
			अगर (be32_to_cpu(ops[i]) == ops_info[j].opal_no) अणु
				add_attr(handle, &sg->sgattrs[count], j);
				sg->sg.attrs[count] =
					&sg->sgattrs[count].attr.attr;
				count++;
			पूर्ण

	वापस sysfs_create_group(sg_kobj, &sg->sg);
पूर्ण

अटल पूर्णांक get_nr_attrs(स्थिर __be32 *ops, पूर्णांक len)
अणु
	पूर्णांक i, j;
	पूर्णांक nr_attrs = 0;

	क्रम (i = 0; i < len; i++)
		क्रम (j = 0; j < ARRAY_SIZE(ops_info); j++)
			अगर (be32_to_cpu(ops[i]) == ops_info[j].opal_no)
				nr_attrs++;

	वापस nr_attrs;
पूर्ण

व्योम __init opal_sensor_groups_init(व्योम)
अणु
	काष्ठा device_node *sg, *node;
	पूर्णांक i = 0;

	sg = of_find_compatible_node(शून्य, शून्य, "ibm,opal-sensor-group");
	अगर (!sg) अणु
		pr_devel("Sensor groups node not found\n");
		वापस;
	पूर्ण

	sgs = kसुस्मृति(of_get_child_count(sg), माप(*sgs), GFP_KERNEL);
	अगर (!sgs)
		वापस;

	sg_kobj = kobject_create_and_add("sensor_groups", opal_kobj);
	अगर (!sg_kobj) अणु
		pr_warn("Failed to create sensor group kobject\n");
		जाओ out_sgs;
	पूर्ण

	क्रम_each_child_of_node(sg, node) अणु
		स्थिर __be32 *ops;
		u32 sgid, len, nr_attrs, chipid;

		ops = of_get_property(node, "ops", &len);
		अगर (!ops)
			जारी;

		nr_attrs = get_nr_attrs(ops, len);
		अगर (!nr_attrs)
			जारी;

		sgs[i].sgattrs = kसुस्मृति(nr_attrs, माप(*sgs[i].sgattrs),
					 GFP_KERNEL);
		अगर (!sgs[i].sgattrs)
			जाओ out_sgs_sgattrs;

		sgs[i].sg.attrs = kसुस्मृति(nr_attrs + 1,
					  माप(*sgs[i].sg.attrs),
					  GFP_KERNEL);

		अगर (!sgs[i].sg.attrs) अणु
			kमुक्त(sgs[i].sgattrs);
			जाओ out_sgs_sgattrs;
		पूर्ण

		अगर (of_property_पढ़ो_u32(node, "sensor-group-id", &sgid)) अणु
			pr_warn("sensor-group-id property not found\n");
			जाओ out_sgs_sgattrs;
		पूर्ण

		अगर (!of_property_पढ़ो_u32(node, "ibm,chip-id", &chipid))
			प्र_लिखो(sgs[i].name, "%pOFn%d", node, chipid);
		अन्यथा
			प्र_लिखो(sgs[i].name, "%pOFn", node);

		sgs[i].sg.name = sgs[i].name;
		अगर (add_attr_group(ops, len, &sgs[i], sgid)) अणु
			pr_warn("Failed to create sensor attribute group %s\n",
				sgs[i].sg.name);
			जाओ out_sgs_sgattrs;
		पूर्ण
		i++;
	पूर्ण

	वापस;

out_sgs_sgattrs:
	जबतक (--i >= 0) अणु
		kमुक्त(sgs[i].sgattrs);
		kमुक्त(sgs[i].sg.attrs);
	पूर्ण
	kobject_put(sg_kobj);
out_sgs:
	kमुक्त(sgs);
पूर्ण
