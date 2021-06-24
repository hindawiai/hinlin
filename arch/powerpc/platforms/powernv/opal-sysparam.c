<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerNV प्रणाली parameter code
 *
 * Copyright (C) 2013 IBM
 */

#समावेश <linux/kobject.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/gfp.h>
#समावेश <linux/स्थिति.स>
#समावेश <यंत्र/opal.h>

#घोषणा MAX_PARAM_DATA_LEN	64

अटल DEFINE_MUTEX(opal_sysparam_mutex);
अटल काष्ठा kobject *sysparam_kobj;
अटल व्योम *param_data_buf;

काष्ठा param_attr अणु
	काष्ठा list_head list;
	u32 param_id;
	u32 param_size;
	काष्ठा kobj_attribute kobj_attr;
पूर्ण;

अटल sमाप_प्रकार opal_get_sys_param(u32 param_id, u32 length, व्योम *buffer)
अणु
	काष्ठा opal_msg msg;
	sमाप_प्रकार ret;
	पूर्णांक token;

	token = opal_async_get_token_पूर्णांकerruptible();
	अगर (token < 0) अणु
		अगर (token != -ERESTARTSYS)
			pr_err("%s: Couldn't get the token, returning\n",
					__func__);
		ret = token;
		जाओ out;
	पूर्ण

	ret = opal_get_param(token, param_id, (u64)buffer, length);
	अगर (ret != OPAL_ASYNC_COMPLETION) अणु
		ret = opal_error_code(ret);
		जाओ out_token;
	पूर्ण

	ret = opal_async_रुको_response(token, &msg);
	अगर (ret) अणु
		pr_err("%s: Failed to wait for the async response, %zd\n",
				__func__, ret);
		जाओ out_token;
	पूर्ण

	ret = opal_error_code(opal_get_async_rc(msg));

out_token:
	opal_async_release_token(token);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक opal_set_sys_param(u32 param_id, u32 length, व्योम *buffer)
अणु
	काष्ठा opal_msg msg;
	पूर्णांक ret, token;

	token = opal_async_get_token_पूर्णांकerruptible();
	अगर (token < 0) अणु
		अगर (token != -ERESTARTSYS)
			pr_err("%s: Couldn't get the token, returning\n",
					__func__);
		ret = token;
		जाओ out;
	पूर्ण

	ret = opal_set_param(token, param_id, (u64)buffer, length);

	अगर (ret != OPAL_ASYNC_COMPLETION) अणु
		ret = opal_error_code(ret);
		जाओ out_token;
	पूर्ण

	ret = opal_async_रुको_response(token, &msg);
	अगर (ret) अणु
		pr_err("%s: Failed to wait for the async response, %d\n",
				__func__, ret);
		जाओ out_token;
	पूर्ण

	ret = opal_error_code(opal_get_async_rc(msg));

out_token:
	opal_async_release_token(token);
out:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार sys_param_show(काष्ठा kobject *kobj,
		काष्ठा kobj_attribute *kobj_attr, अक्षर *buf)
अणु
	काष्ठा param_attr *attr = container_of(kobj_attr, काष्ठा param_attr,
			kobj_attr);
	sमाप_प्रकार ret;

	mutex_lock(&opal_sysparam_mutex);
	ret = opal_get_sys_param(attr->param_id, attr->param_size,
			param_data_buf);
	अगर (ret)
		जाओ out;

	स_नकल(buf, param_data_buf, attr->param_size);

	ret = attr->param_size;
out:
	mutex_unlock(&opal_sysparam_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार sys_param_store(काष्ठा kobject *kobj,
		काष्ठा kobj_attribute *kobj_attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा param_attr *attr = container_of(kobj_attr, काष्ठा param_attr,
			kobj_attr);
	sमाप_प्रकार ret;

        /* MAX_PARAM_DATA_LEN is माप(param_data_buf) */
        अगर (count > MAX_PARAM_DATA_LEN)
                count = MAX_PARAM_DATA_LEN;

	mutex_lock(&opal_sysparam_mutex);
	स_नकल(param_data_buf, buf, count);
	ret = opal_set_sys_param(attr->param_id, attr->param_size,
			param_data_buf);
	mutex_unlock(&opal_sysparam_mutex);
	अगर (!ret)
		ret = count;
	वापस ret;
पूर्ण

व्योम __init opal_sys_param_init(व्योम)
अणु
	काष्ठा device_node *sysparam;
	काष्ठा param_attr *attr;
	u32 *id, *size;
	पूर्णांक count, i;
	u8 *perm;

	अगर (!opal_kobj) अणु
		pr_warn("SYSPARAM: opal kobject is not available\n");
		जाओ out;
	पूर्ण

	/* Some प्रणालीs करो not use sysparams; this is not an error */
	sysparam = of_find_node_by_path("/ibm,opal/sysparams");
	अगर (!sysparam)
		जाओ out;

	अगर (!of_device_is_compatible(sysparam, "ibm,opal-sysparams")) अणु
		pr_err("SYSPARAM: Opal sysparam node not compatible\n");
		जाओ out_node_put;
	पूर्ण

	sysparam_kobj = kobject_create_and_add("sysparams", opal_kobj);
	अगर (!sysparam_kobj) अणु
		pr_err("SYSPARAM: Failed to create sysparam kobject\n");
		जाओ out_node_put;
	पूर्ण

	/* Allocate big enough buffer क्रम any get/set transactions */
	param_data_buf = kzalloc(MAX_PARAM_DATA_LEN, GFP_KERNEL);
	अगर (!param_data_buf) अणु
		pr_err("SYSPARAM: Failed to allocate memory for param data "
				"buf\n");
		जाओ out_kobj_put;
	पूर्ण

	/* Number of parameters exposed through DT */
	count = of_property_count_strings(sysparam, "param-name");
	अगर (count < 0) अणु
		pr_err("SYSPARAM: No string found of property param-name in "
				"the node %pOFn\n", sysparam);
		जाओ out_param_buf;
	पूर्ण

	id = kसुस्मृति(count, माप(*id), GFP_KERNEL);
	अगर (!id) अणु
		pr_err("SYSPARAM: Failed to allocate memory to read parameter "
				"id\n");
		जाओ out_param_buf;
	पूर्ण

	size = kसुस्मृति(count, माप(*size), GFP_KERNEL);
	अगर (!size) अणु
		pr_err("SYSPARAM: Failed to allocate memory to read parameter "
				"size\n");
		जाओ out_मुक्त_id;
	पूर्ण

	perm = kसुस्मृति(count, माप(*perm), GFP_KERNEL);
	अगर (!perm) अणु
		pr_err("SYSPARAM: Failed to allocate memory to read supported "
				"action on the parameter");
		जाओ out_मुक्त_size;
	पूर्ण

	अगर (of_property_पढ़ो_u32_array(sysparam, "param-id", id, count)) अणु
		pr_err("SYSPARAM: Missing property param-id in the DT\n");
		जाओ out_मुक्त_perm;
	पूर्ण

	अगर (of_property_पढ़ो_u32_array(sysparam, "param-len", size, count)) अणु
		pr_err("SYSPARAM: Missing property param-len in the DT\n");
		जाओ out_मुक्त_perm;
	पूर्ण


	अगर (of_property_पढ़ो_u8_array(sysparam, "param-perm", perm, count)) अणु
		pr_err("SYSPARAM: Missing property param-perm in the DT\n");
		जाओ out_मुक्त_perm;
	पूर्ण

	attr = kसुस्मृति(count, माप(*attr), GFP_KERNEL);
	अगर (!attr) अणु
		pr_err("SYSPARAM: Failed to allocate memory for parameter "
				"attributes\n");
		जाओ out_मुक्त_perm;
	पूर्ण

	/* For each of the parameters, populate the parameter attributes */
	क्रम (i = 0; i < count; i++) अणु
		अगर (size[i] > MAX_PARAM_DATA_LEN) अणु
			pr_warn("SYSPARAM: Not creating parameter %d as size "
				"exceeds buffer length\n", i);
			जारी;
		पूर्ण

		sysfs_attr_init(&attr[i].kobj_attr.attr);
		attr[i].param_id = id[i];
		attr[i].param_size = size[i];
		अगर (of_property_पढ़ो_string_index(sysparam, "param-name", i,
				&attr[i].kobj_attr.attr.name))
			जारी;

		/* If the parameter is पढ़ो-only or पढ़ो-ग_लिखो */
		चयन (perm[i] & 3) अणु
		हाल OPAL_SYSPARAM_READ:
			attr[i].kobj_attr.attr.mode = 0444;
			अवरोध;
		हाल OPAL_SYSPARAM_WRITE:
			attr[i].kobj_attr.attr.mode = 0200;
			अवरोध;
		हाल OPAL_SYSPARAM_RW:
			attr[i].kobj_attr.attr.mode = 0644;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		attr[i].kobj_attr.show = sys_param_show;
		attr[i].kobj_attr.store = sys_param_store;

		अगर (sysfs_create_file(sysparam_kobj, &attr[i].kobj_attr.attr)) अणु
			pr_err("SYSPARAM: Failed to create sysfs file %s\n",
					attr[i].kobj_attr.attr.name);
			जाओ out_मुक्त_attr;
		पूर्ण
	पूर्ण

	kमुक्त(perm);
	kमुक्त(size);
	kमुक्त(id);
	of_node_put(sysparam);
	वापस;

out_मुक्त_attr:
	kमुक्त(attr);
out_मुक्त_perm:
	kमुक्त(perm);
out_मुक्त_size:
	kमुक्त(size);
out_मुक्त_id:
	kमुक्त(id);
out_param_buf:
	kमुक्त(param_data_buf);
out_kobj_put:
	kobject_put(sysparam_kobj);
out_node_put:
	of_node_put(sysparam);
out:
	वापस;
पूर्ण
