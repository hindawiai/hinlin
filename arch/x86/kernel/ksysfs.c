<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Architecture specअगरic sysfs attributes in /sys/kernel
 *
 * Copyright (C) 2007, Intel Corp.
 *      Huang Ying <ying.huang@पूर्णांकel.com>
 * Copyright (C) 2013, 2013 Red Hat, Inc.
 *      Dave Young <dyoung@redhat.com>
 */

#समावेश <linux/kobject.h>
#समावेश <linux/माला.स>
#समावेश <linux/sysfs.h>
#समावेश <linux/init.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/setup.h>

अटल sमाप_प्रकार version_show(काष्ठा kobject *kobj,
			    काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0x%04x\n", boot_params.hdr.version);
पूर्ण

अटल काष्ठा kobj_attribute boot_params_version_attr = __ATTR_RO(version);

अटल sमाप_प्रकार boot_params_data_पढ़ो(काष्ठा file *fp, काष्ठा kobject *kobj,
				     काष्ठा bin_attribute *bin_attr,
				     अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	स_नकल(buf, (व्योम *)&boot_params + off, count);
	वापस count;
पूर्ण

अटल काष्ठा bin_attribute boot_params_data_attr = अणु
	.attr = अणु
		.name = "data",
		.mode = S_IRUGO,
	पूर्ण,
	.पढ़ो = boot_params_data_पढ़ो,
	.size = माप(boot_params),
पूर्ण;

अटल काष्ठा attribute *boot_params_version_attrs[] = अणु
	&boot_params_version_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा bin_attribute *boot_params_data_attrs[] = अणु
	&boot_params_data_attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group boot_params_attr_group = अणु
	.attrs = boot_params_version_attrs,
	.bin_attrs = boot_params_data_attrs,
पूर्ण;

अटल पूर्णांक kobj_to_setup_data_nr(काष्ठा kobject *kobj, पूर्णांक *nr)
अणु
	स्थिर अक्षर *name;

	name = kobject_name(kobj);
	वापस kstrtoपूर्णांक(name, 10, nr);
पूर्ण

अटल पूर्णांक get_setup_data_paddr(पूर्णांक nr, u64 *paddr)
अणु
	पूर्णांक i = 0;
	काष्ठा setup_data *data;
	u64 pa_data = boot_params.hdr.setup_data;

	जबतक (pa_data) अणु
		अगर (nr == i) अणु
			*paddr = pa_data;
			वापस 0;
		पूर्ण
		data = memremap(pa_data, माप(*data), MEMREMAP_WB);
		अगर (!data)
			वापस -ENOMEM;

		pa_data = data->next;
		memunmap(data);
		i++;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __init get_setup_data_size(पूर्णांक nr, माप_प्रकार *size)
अणु
	पूर्णांक i = 0;
	काष्ठा setup_data *data;
	u64 pa_data = boot_params.hdr.setup_data;

	जबतक (pa_data) अणु
		data = memremap(pa_data, माप(*data), MEMREMAP_WB);
		अगर (!data)
			वापस -ENOMEM;
		अगर (nr == i) अणु
			अगर (data->type == SETUP_INसूचीECT &&
			    ((काष्ठा setup_indirect *)data->data)->type != SETUP_INसूचीECT)
				*size = ((काष्ठा setup_indirect *)data->data)->len;
			अन्यथा
				*size = data->len;

			memunmap(data);
			वापस 0;
		पूर्ण

		pa_data = data->next;
		memunmap(data);
		i++;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार type_show(काष्ठा kobject *kobj,
			 काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr, ret;
	u64 paddr;
	काष्ठा setup_data *data;

	ret = kobj_to_setup_data_nr(kobj, &nr);
	अगर (ret)
		वापस ret;

	ret = get_setup_data_paddr(nr, &paddr);
	अगर (ret)
		वापस ret;
	data = memremap(paddr, माप(*data), MEMREMAP_WB);
	अगर (!data)
		वापस -ENOMEM;

	अगर (data->type == SETUP_INसूचीECT)
		ret = प्र_लिखो(buf, "0x%x\n", ((काष्ठा setup_indirect *)data->data)->type);
	अन्यथा
		ret = प्र_लिखो(buf, "0x%x\n", data->type);
	memunmap(data);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार setup_data_data_पढ़ो(काष्ठा file *fp,
				    काष्ठा kobject *kobj,
				    काष्ठा bin_attribute *bin_attr,
				    अक्षर *buf,
				    loff_t off, माप_प्रकार count)
अणु
	पूर्णांक nr, ret = 0;
	u64 paddr, len;
	काष्ठा setup_data *data;
	व्योम *p;

	ret = kobj_to_setup_data_nr(kobj, &nr);
	अगर (ret)
		वापस ret;

	ret = get_setup_data_paddr(nr, &paddr);
	अगर (ret)
		वापस ret;
	data = memremap(paddr, माप(*data), MEMREMAP_WB);
	अगर (!data)
		वापस -ENOMEM;

	अगर (data->type == SETUP_INसूचीECT &&
	    ((काष्ठा setup_indirect *)data->data)->type != SETUP_INसूचीECT) अणु
		paddr = ((काष्ठा setup_indirect *)data->data)->addr;
		len = ((काष्ठा setup_indirect *)data->data)->len;
	पूर्ण अन्यथा अणु
		paddr += माप(*data);
		len = data->len;
	पूर्ण

	अगर (off > len) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (count > len - off)
		count = len - off;

	अगर (!count)
		जाओ out;

	ret = count;
	p = memremap(paddr, len, MEMREMAP_WB);
	अगर (!p) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	स_नकल(buf, p + off, count);
	memunmap(p);
out:
	memunmap(data);
	वापस ret;
पूर्ण

अटल काष्ठा kobj_attribute type_attr = __ATTR_RO(type);

अटल काष्ठा bin_attribute data_attr __ro_after_init = अणु
	.attr = अणु
		.name = "data",
		.mode = S_IRUGO,
	पूर्ण,
	.पढ़ो = setup_data_data_पढ़ो,
पूर्ण;

अटल काष्ठा attribute *setup_data_type_attrs[] = अणु
	&type_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा bin_attribute *setup_data_data_attrs[] = अणु
	&data_attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group setup_data_attr_group = अणु
	.attrs = setup_data_type_attrs,
	.bin_attrs = setup_data_data_attrs,
पूर्ण;

अटल पूर्णांक __init create_setup_data_node(काष्ठा kobject *parent,
					 काष्ठा kobject **kobjp, पूर्णांक nr)
अणु
	पूर्णांक ret = 0;
	माप_प्रकार size;
	काष्ठा kobject *kobj;
	अक्षर name[16]; /* should be enough क्रम setup_data nodes numbers */
	snम_लिखो(name, 16, "%d", nr);

	kobj = kobject_create_and_add(name, parent);
	अगर (!kobj)
		वापस -ENOMEM;

	ret = get_setup_data_size(nr, &size);
	अगर (ret)
		जाओ out_kobj;

	data_attr.size = size;
	ret = sysfs_create_group(kobj, &setup_data_attr_group);
	अगर (ret)
		जाओ out_kobj;
	*kobjp = kobj;

	वापस 0;
out_kobj:
	kobject_put(kobj);
	वापस ret;
पूर्ण

अटल व्योम __init cleanup_setup_data_node(काष्ठा kobject *kobj)
अणु
	sysfs_हटाओ_group(kobj, &setup_data_attr_group);
	kobject_put(kobj);
पूर्ण

अटल पूर्णांक __init get_setup_data_total_num(u64 pa_data, पूर्णांक *nr)
अणु
	पूर्णांक ret = 0;
	काष्ठा setup_data *data;

	*nr = 0;
	जबतक (pa_data) अणु
		*nr += 1;
		data = memremap(pa_data, माप(*data), MEMREMAP_WB);
		अगर (!data) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		pa_data = data->next;
		memunmap(data);
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक __init create_setup_data_nodes(काष्ठा kobject *parent)
अणु
	काष्ठा kobject *setup_data_kobj, **kobjp;
	u64 pa_data;
	पूर्णांक i, j, nr, ret = 0;

	pa_data = boot_params.hdr.setup_data;
	अगर (!pa_data)
		वापस 0;

	setup_data_kobj = kobject_create_and_add("setup_data", parent);
	अगर (!setup_data_kobj) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = get_setup_data_total_num(pa_data, &nr);
	अगर (ret)
		जाओ out_setup_data_kobj;

	kobjp = kदो_स्मृति_array(nr, माप(*kobjp), GFP_KERNEL);
	अगर (!kobjp) अणु
		ret = -ENOMEM;
		जाओ out_setup_data_kobj;
	पूर्ण

	क्रम (i = 0; i < nr; i++) अणु
		ret = create_setup_data_node(setup_data_kobj, kobjp + i, i);
		अगर (ret)
			जाओ out_clean_nodes;
	पूर्ण

	kमुक्त(kobjp);
	वापस 0;

out_clean_nodes:
	क्रम (j = i - 1; j >= 0; j--)
		cleanup_setup_data_node(*(kobjp + j));
	kमुक्त(kobjp);
out_setup_data_kobj:
	kobject_put(setup_data_kobj);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक __init boot_params_ksysfs_init(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा kobject *boot_params_kobj;

	boot_params_kobj = kobject_create_and_add("boot_params",
						  kernel_kobj);
	अगर (!boot_params_kobj) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = sysfs_create_group(boot_params_kobj, &boot_params_attr_group);
	अगर (ret)
		जाओ out_boot_params_kobj;

	ret = create_setup_data_nodes(boot_params_kobj);
	अगर (ret)
		जाओ out_create_group;

	वापस 0;
out_create_group:
	sysfs_हटाओ_group(boot_params_kobj, &boot_params_attr_group);
out_boot_params_kobj:
	kobject_put(boot_params_kobj);
out:
	वापस ret;
पूर्ण

arch_initcall(boot_params_ksysfs_init);
