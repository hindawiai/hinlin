<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerNV OPAL Power-Shअगरt-Ratio पूर्णांकerface
 *
 * Copyright 2017 IBM Corp.
 */

#घोषणा pr_fmt(fmt)     "opal-psr: " fmt

#समावेश <linux/of.h>
#समावेश <linux/kobject.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/opal.h>

अटल DEFINE_MUTEX(psr_mutex);

अटल काष्ठा kobject *psr_kobj;

अटल काष्ठा psr_attr अणु
	u32 handle;
	काष्ठा kobj_attribute attr;
पूर्ण *psr_attrs;

अटल sमाप_प्रकार psr_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा psr_attr *psr_attr = container_of(attr, काष्ठा psr_attr, attr);
	काष्ठा opal_msg msg;
	पूर्णांक psr, ret, token;

	token = opal_async_get_token_पूर्णांकerruptible();
	अगर (token < 0) अणु
		pr_devel("Failed to get token\n");
		वापस token;
	पूर्ण

	ret = mutex_lock_पूर्णांकerruptible(&psr_mutex);
	अगर (ret)
		जाओ out_token;

	ret = opal_get_घातer_shअगरt_ratio(psr_attr->handle, token,
					    (u32 *)__pa(&psr));
	चयन (ret) अणु
	हाल OPAL_ASYNC_COMPLETION:
		ret = opal_async_रुको_response(token, &msg);
		अगर (ret) अणु
			pr_devel("Failed to wait for the async response\n");
			ret = -EIO;
			जाओ out;
		पूर्ण
		ret = opal_error_code(opal_get_async_rc(msg));
		अगर (!ret) अणु
			ret = प्र_लिखो(buf, "%u\n", be32_to_cpu(psr));
			अगर (ret < 0)
				ret = -EIO;
		पूर्ण
		अवरोध;
	हाल OPAL_SUCCESS:
		ret = प्र_लिखो(buf, "%u\n", be32_to_cpu(psr));
		अगर (ret < 0)
			ret = -EIO;
		अवरोध;
	शेष:
		ret = opal_error_code(ret);
	पूर्ण

out:
	mutex_unlock(&psr_mutex);
out_token:
	opal_async_release_token(token);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार psr_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा psr_attr *psr_attr = container_of(attr, काष्ठा psr_attr, attr);
	काष्ठा opal_msg msg;
	पूर्णांक psr, ret, token;

	ret = kstrtoपूर्णांक(buf, 0, &psr);
	अगर (ret)
		वापस ret;

	token = opal_async_get_token_पूर्णांकerruptible();
	अगर (token < 0) अणु
		pr_devel("Failed to get token\n");
		वापस token;
	पूर्ण

	ret = mutex_lock_पूर्णांकerruptible(&psr_mutex);
	अगर (ret)
		जाओ out_token;

	ret = opal_set_घातer_shअगरt_ratio(psr_attr->handle, token, psr);
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
	mutex_unlock(&psr_mutex);
out_token:
	opal_async_release_token(token);
	वापस ret;
पूर्ण

व्योम __init opal_psr_init(व्योम)
अणु
	काष्ठा device_node *psr, *node;
	पूर्णांक i = 0;

	psr = of_find_compatible_node(शून्य, शून्य,
				      "ibm,opal-power-shift-ratio");
	अगर (!psr) अणु
		pr_devel("Power-shift-ratio node not found\n");
		वापस;
	पूर्ण

	psr_attrs = kसुस्मृति(of_get_child_count(psr), माप(*psr_attrs),
			    GFP_KERNEL);
	अगर (!psr_attrs)
		वापस;

	psr_kobj = kobject_create_and_add("psr", opal_kobj);
	अगर (!psr_kobj) अणु
		pr_warn("Failed to create psr kobject\n");
		जाओ out;
	पूर्ण

	क्रम_each_child_of_node(psr, node) अणु
		अगर (of_property_पढ़ो_u32(node, "handle",
					 &psr_attrs[i].handle))
			जाओ out_kobj;

		sysfs_attr_init(&psr_attrs[i].attr.attr);
		अगर (of_property_पढ़ो_string(node, "label",
					    &psr_attrs[i].attr.attr.name))
			जाओ out_kobj;
		psr_attrs[i].attr.attr.mode = 0664;
		psr_attrs[i].attr.show = psr_show;
		psr_attrs[i].attr.store = psr_store;
		अगर (sysfs_create_file(psr_kobj, &psr_attrs[i].attr.attr)) अणु
			pr_devel("Failed to create psr sysfs file %s\n",
				 psr_attrs[i].attr.attr.name);
			जाओ out_kobj;
		पूर्ण
		i++;
	पूर्ण

	वापस;
out_kobj:
	kobject_put(psr_kobj);
out:
	kमुक्त(psr_attrs);
पूर्ण
