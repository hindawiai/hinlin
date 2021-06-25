<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerNV OPAL Powercap पूर्णांकerface
 *
 * Copyright 2017 IBM Corp.
 */

#घोषणा pr_fmt(fmt)     "opal-powercap: " fmt

#समावेश <linux/of.h>
#समावेश <linux/kobject.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/opal.h>

अटल DEFINE_MUTEX(घातercap_mutex);

अटल काष्ठा kobject *घातercap_kobj;

काष्ठा घातercap_attr अणु
	u32 handle;
	काष्ठा kobj_attribute attr;
पूर्ण;

अटल काष्ठा pcap अणु
	काष्ठा attribute_group pg;
	काष्ठा घातercap_attr *pattrs;
पूर्ण *pcaps;

अटल sमाप_प्रकार घातercap_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा घातercap_attr *pcap_attr = container_of(attr,
						काष्ठा घातercap_attr, attr);
	काष्ठा opal_msg msg;
	u32 pcap;
	पूर्णांक ret, token;

	token = opal_async_get_token_पूर्णांकerruptible();
	अगर (token < 0) अणु
		pr_devel("Failed to get token\n");
		वापस token;
	पूर्ण

	ret = mutex_lock_पूर्णांकerruptible(&घातercap_mutex);
	अगर (ret)
		जाओ out_token;

	ret = opal_get_घातercap(pcap_attr->handle, token, (u32 *)__pa(&pcap));
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
			ret = प्र_लिखो(buf, "%u\n", be32_to_cpu(pcap));
			अगर (ret < 0)
				ret = -EIO;
		पूर्ण
		अवरोध;
	हाल OPAL_SUCCESS:
		ret = प्र_लिखो(buf, "%u\n", be32_to_cpu(pcap));
		अगर (ret < 0)
			ret = -EIO;
		अवरोध;
	शेष:
		ret = opal_error_code(ret);
	पूर्ण

out:
	mutex_unlock(&घातercap_mutex);
out_token:
	opal_async_release_token(token);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार घातercap_store(काष्ठा kobject *kobj,
			      काष्ठा kobj_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	काष्ठा घातercap_attr *pcap_attr = container_of(attr,
						काष्ठा घातercap_attr, attr);
	काष्ठा opal_msg msg;
	u32 pcap;
	पूर्णांक ret, token;

	ret = kstrtoपूर्णांक(buf, 0, &pcap);
	अगर (ret)
		वापस ret;

	token = opal_async_get_token_पूर्णांकerruptible();
	अगर (token < 0) अणु
		pr_devel("Failed to get token\n");
		वापस token;
	पूर्ण

	ret = mutex_lock_पूर्णांकerruptible(&घातercap_mutex);
	अगर (ret)
		जाओ out_token;

	ret = opal_set_घातercap(pcap_attr->handle, token, pcap);
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
	mutex_unlock(&घातercap_mutex);
out_token:
	opal_async_release_token(token);
	वापस ret;
पूर्ण

अटल व्योम घातercap_add_attr(पूर्णांक handle, स्थिर अक्षर *name,
			      काष्ठा घातercap_attr *attr)
अणु
	attr->handle = handle;
	sysfs_attr_init(&attr->attr.attr);
	attr->attr.attr.name = name;
	attr->attr.attr.mode = 0444;
	attr->attr.show = घातercap_show;
पूर्ण

व्योम __init opal_घातercap_init(व्योम)
अणु
	काष्ठा device_node *घातercap, *node;
	पूर्णांक i = 0;

	घातercap = of_find_compatible_node(शून्य, शून्य, "ibm,opal-powercap");
	अगर (!घातercap) अणु
		pr_devel("Powercap node not found\n");
		वापस;
	पूर्ण

	pcaps = kसुस्मृति(of_get_child_count(घातercap), माप(*pcaps),
			GFP_KERNEL);
	अगर (!pcaps)
		वापस;

	घातercap_kobj = kobject_create_and_add("powercap", opal_kobj);
	अगर (!घातercap_kobj) अणु
		pr_warn("Failed to create powercap kobject\n");
		जाओ out_pcaps;
	पूर्ण

	i = 0;
	क्रम_each_child_of_node(घातercap, node) अणु
		u32 cur, min, max;
		पूर्णांक j = 0;
		bool has_cur = false, has_min = false, has_max = false;

		अगर (!of_property_पढ़ो_u32(node, "powercap-min", &min)) अणु
			j++;
			has_min = true;
		पूर्ण

		अगर (!of_property_पढ़ो_u32(node, "powercap-max", &max)) अणु
			j++;
			has_max = true;
		पूर्ण

		अगर (!of_property_पढ़ो_u32(node, "powercap-current", &cur)) अणु
			j++;
			has_cur = true;
		पूर्ण

		pcaps[i].pattrs = kसुस्मृति(j, माप(काष्ठा घातercap_attr),
					  GFP_KERNEL);
		अगर (!pcaps[i].pattrs)
			जाओ out_pcaps_pattrs;

		pcaps[i].pg.attrs = kसुस्मृति(j + 1, माप(काष्ठा attribute *),
					    GFP_KERNEL);
		अगर (!pcaps[i].pg.attrs) अणु
			kमुक्त(pcaps[i].pattrs);
			जाओ out_pcaps_pattrs;
		पूर्ण

		j = 0;
		pcaps[i].pg.name = kaप्र_लिखो(GFP_KERNEL, "%pOFn", node);
		अगर (has_min) अणु
			घातercap_add_attr(min, "powercap-min",
					  &pcaps[i].pattrs[j]);
			pcaps[i].pg.attrs[j] = &pcaps[i].pattrs[j].attr.attr;
			j++;
		पूर्ण

		अगर (has_max) अणु
			घातercap_add_attr(max, "powercap-max",
					  &pcaps[i].pattrs[j]);
			pcaps[i].pg.attrs[j] = &pcaps[i].pattrs[j].attr.attr;
			j++;
		पूर्ण

		अगर (has_cur) अणु
			घातercap_add_attr(cur, "powercap-current",
					  &pcaps[i].pattrs[j]);
			pcaps[i].pattrs[j].attr.attr.mode |= 0220;
			pcaps[i].pattrs[j].attr.store = घातercap_store;
			pcaps[i].pg.attrs[j] = &pcaps[i].pattrs[j].attr.attr;
			j++;
		पूर्ण

		अगर (sysfs_create_group(घातercap_kobj, &pcaps[i].pg)) अणु
			pr_warn("Failed to create powercap attribute group %s\n",
				pcaps[i].pg.name);
			जाओ out_pcaps_pattrs;
		पूर्ण
		i++;
	पूर्ण

	वापस;

out_pcaps_pattrs:
	जबतक (--i >= 0) अणु
		kमुक्त(pcaps[i].pattrs);
		kमुक्त(pcaps[i].pg.attrs);
		kमुक्त(pcaps[i].pg.name);
	पूर्ण
	kobject_put(घातercap_kobj);
out_pcaps:
	kमुक्त(pcaps);
पूर्ण
