<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  copyright (c) 2006 IBM Corporation
 *  Authored by: Mike D. Day <ncmike@us.ibm.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/kobject.h>
#समावेश <linux/err.h>

#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <यंत्र/xen/hypercall.h>

#समावेश <xen/xen.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/version.h>
#अगर_घोषित CONFIG_XEN_HAVE_VPMU
#समावेश <xen/पूर्णांकerface/xenpmu.h>
#पूर्ण_अगर

#घोषणा HYPERVISOR_ATTR_RO(_name) \
अटल काष्ठा hyp_sysfs_attr  _name##_attr = __ATTR_RO(_name)

#घोषणा HYPERVISOR_ATTR_RW(_name) \
अटल काष्ठा hyp_sysfs_attr _name##_attr = \
	__ATTR(_name, 0644, _name##_show, _name##_store)

काष्ठा hyp_sysfs_attr अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा hyp_sysfs_attr *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा hyp_sysfs_attr *, स्थिर अक्षर *, माप_प्रकार);
	व्योम *hyp_attr_data;
पूर्ण;

अटल sमाप_प्रकार type_show(काष्ठा hyp_sysfs_attr *attr, अक्षर *buffer)
अणु
	वापस प्र_लिखो(buffer, "xen\n");
पूर्ण

HYPERVISOR_ATTR_RO(type);

अटल पूर्णांक __init xen_sysfs_type_init(व्योम)
अणु
	वापस sysfs_create_file(hypervisor_kobj, &type_attr.attr);
पूर्ण

अटल sमाप_प्रकार guest_type_show(काष्ठा hyp_sysfs_attr *attr, अक्षर *buffer)
अणु
	स्थिर अक्षर *type;

	चयन (xen_करोमुख्य_type) अणु
	हाल XEN_NATIVE:
		/* ARM only. */
		type = "Xen";
		अवरोध;
	हाल XEN_PV_DOMAIN:
		type = "PV";
		अवरोध;
	हाल XEN_HVM_DOMAIN:
		type = xen_pvh_करोमुख्य() ? "PVH" : "HVM";
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस प्र_लिखो(buffer, "%s\n", type);
पूर्ण

HYPERVISOR_ATTR_RO(guest_type);

अटल पूर्णांक __init xen_sysfs_guest_type_init(व्योम)
अणु
	वापस sysfs_create_file(hypervisor_kobj, &guest_type_attr.attr);
पूर्ण

/* xen version attributes */
अटल sमाप_प्रकार major_show(काष्ठा hyp_sysfs_attr *attr, अक्षर *buffer)
अणु
	पूर्णांक version = HYPERVISOR_xen_version(XENVER_version, शून्य);
	अगर (version)
		वापस प्र_लिखो(buffer, "%d\n", version >> 16);
	वापस -ENODEV;
पूर्ण

HYPERVISOR_ATTR_RO(major);

अटल sमाप_प्रकार minor_show(काष्ठा hyp_sysfs_attr *attr, अक्षर *buffer)
अणु
	पूर्णांक version = HYPERVISOR_xen_version(XENVER_version, शून्य);
	अगर (version)
		वापस प्र_लिखो(buffer, "%d\n", version & 0xff);
	वापस -ENODEV;
पूर्ण

HYPERVISOR_ATTR_RO(minor);

अटल sमाप_प्रकार extra_show(काष्ठा hyp_sysfs_attr *attr, अक्षर *buffer)
अणु
	पूर्णांक ret = -ENOMEM;
	अक्षर *extra;

	extra = kदो_स्मृति(XEN_EXTRAVERSION_LEN, GFP_KERNEL);
	अगर (extra) अणु
		ret = HYPERVISOR_xen_version(XENVER_extraversion, extra);
		अगर (!ret)
			ret = प्र_लिखो(buffer, "%s\n", extra);
		kमुक्त(extra);
	पूर्ण

	वापस ret;
पूर्ण

HYPERVISOR_ATTR_RO(extra);

अटल काष्ठा attribute *version_attrs[] = अणु
	&major_attr.attr,
	&minor_attr.attr,
	&extra_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group version_group = अणु
	.name = "version",
	.attrs = version_attrs,
पूर्ण;

अटल पूर्णांक __init xen_sysfs_version_init(व्योम)
अणु
	वापस sysfs_create_group(hypervisor_kobj, &version_group);
पूर्ण

/* UUID */

अटल sमाप_प्रकार uuid_show_fallback(काष्ठा hyp_sysfs_attr *attr, अक्षर *buffer)
अणु
	अक्षर *vm, *val;
	पूर्णांक ret;
	बाह्य पूर्णांक xenstored_पढ़ोy;

	अगर (!xenstored_पढ़ोy)
		वापस -EBUSY;

	vm = xenbus_पढ़ो(XBT_NIL, "vm", "", शून्य);
	अगर (IS_ERR(vm))
		वापस PTR_ERR(vm);
	val = xenbus_पढ़ो(XBT_NIL, vm, "uuid", शून्य);
	kमुक्त(vm);
	अगर (IS_ERR(val))
		वापस PTR_ERR(val);
	ret = प्र_लिखो(buffer, "%s\n", val);
	kमुक्त(val);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार uuid_show(काष्ठा hyp_sysfs_attr *attr, अक्षर *buffer)
अणु
	xen_करोमुख्य_handle_t uuid;
	पूर्णांक ret;
	ret = HYPERVISOR_xen_version(XENVER_guest_handle, uuid);
	अगर (ret)
		वापस uuid_show_fallback(attr, buffer);
	ret = प्र_लिखो(buffer, "%pU\n", uuid);
	वापस ret;
पूर्ण

HYPERVISOR_ATTR_RO(uuid);

अटल पूर्णांक __init xen_sysfs_uuid_init(व्योम)
अणु
	वापस sysfs_create_file(hypervisor_kobj, &uuid_attr.attr);
पूर्ण

/* xen compilation attributes */

अटल sमाप_प्रकार compiler_show(काष्ठा hyp_sysfs_attr *attr, अक्षर *buffer)
अणु
	पूर्णांक ret = -ENOMEM;
	काष्ठा xen_compile_info *info;

	info = kदो_स्मृति(माप(काष्ठा xen_compile_info), GFP_KERNEL);
	अगर (info) अणु
		ret = HYPERVISOR_xen_version(XENVER_compile_info, info);
		अगर (!ret)
			ret = प्र_लिखो(buffer, "%s\n", info->compiler);
		kमुक्त(info);
	पूर्ण

	वापस ret;
पूर्ण

HYPERVISOR_ATTR_RO(compiler);

अटल sमाप_प्रकार compiled_by_show(काष्ठा hyp_sysfs_attr *attr, अक्षर *buffer)
अणु
	पूर्णांक ret = -ENOMEM;
	काष्ठा xen_compile_info *info;

	info = kदो_स्मृति(माप(काष्ठा xen_compile_info), GFP_KERNEL);
	अगर (info) अणु
		ret = HYPERVISOR_xen_version(XENVER_compile_info, info);
		अगर (!ret)
			ret = प्र_लिखो(buffer, "%s\n", info->compile_by);
		kमुक्त(info);
	पूर्ण

	वापस ret;
पूर्ण

HYPERVISOR_ATTR_RO(compiled_by);

अटल sमाप_प्रकार compile_date_show(काष्ठा hyp_sysfs_attr *attr, अक्षर *buffer)
अणु
	पूर्णांक ret = -ENOMEM;
	काष्ठा xen_compile_info *info;

	info = kदो_स्मृति(माप(काष्ठा xen_compile_info), GFP_KERNEL);
	अगर (info) अणु
		ret = HYPERVISOR_xen_version(XENVER_compile_info, info);
		अगर (!ret)
			ret = प्र_लिखो(buffer, "%s\n", info->compile_date);
		kमुक्त(info);
	पूर्ण

	वापस ret;
पूर्ण

HYPERVISOR_ATTR_RO(compile_date);

अटल काष्ठा attribute *xen_compile_attrs[] = अणु
	&compiler_attr.attr,
	&compiled_by_attr.attr,
	&compile_date_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group xen_compilation_group = अणु
	.name = "compilation",
	.attrs = xen_compile_attrs,
पूर्ण;

अटल पूर्णांक __init xen_sysfs_compilation_init(व्योम)
अणु
	वापस sysfs_create_group(hypervisor_kobj, &xen_compilation_group);
पूर्ण

/* xen properties info */

अटल sमाप_प्रकार capabilities_show(काष्ठा hyp_sysfs_attr *attr, अक्षर *buffer)
अणु
	पूर्णांक ret = -ENOMEM;
	अक्षर *caps;

	caps = kदो_स्मृति(XEN_CAPABILITIES_INFO_LEN, GFP_KERNEL);
	अगर (caps) अणु
		ret = HYPERVISOR_xen_version(XENVER_capabilities, caps);
		अगर (!ret)
			ret = प्र_लिखो(buffer, "%s\n", caps);
		kमुक्त(caps);
	पूर्ण

	वापस ret;
पूर्ण

HYPERVISOR_ATTR_RO(capabilities);

अटल sमाप_प्रकार changeset_show(काष्ठा hyp_sysfs_attr *attr, अक्षर *buffer)
अणु
	पूर्णांक ret = -ENOMEM;
	अक्षर *cset;

	cset = kदो_स्मृति(XEN_CHANGESET_INFO_LEN, GFP_KERNEL);
	अगर (cset) अणु
		ret = HYPERVISOR_xen_version(XENVER_changeset, cset);
		अगर (!ret)
			ret = प्र_लिखो(buffer, "%s\n", cset);
		kमुक्त(cset);
	पूर्ण

	वापस ret;
पूर्ण

HYPERVISOR_ATTR_RO(changeset);

अटल sमाप_प्रकार भव_start_show(काष्ठा hyp_sysfs_attr *attr, अक्षर *buffer)
अणु
	पूर्णांक ret = -ENOMEM;
	काष्ठा xen_platक्रमm_parameters *parms;

	parms = kदो_स्मृति(माप(काष्ठा xen_platक्रमm_parameters), GFP_KERNEL);
	अगर (parms) अणु
		ret = HYPERVISOR_xen_version(XENVER_platक्रमm_parameters,
					     parms);
		अगर (!ret)
			ret = प्र_लिखो(buffer, "%"PRI_xen_uदीर्घ"\n",
				      parms->virt_start);
		kमुक्त(parms);
	पूर्ण

	वापस ret;
पूर्ण

HYPERVISOR_ATTR_RO(भव_start);

अटल sमाप_प्रकार pagesize_show(काष्ठा hyp_sysfs_attr *attr, अक्षर *buffer)
अणु
	पूर्णांक ret;

	ret = HYPERVISOR_xen_version(XENVER_pagesize, शून्य);
	अगर (ret > 0)
		ret = प्र_लिखो(buffer, "%x\n", ret);

	वापस ret;
पूर्ण

HYPERVISOR_ATTR_RO(pagesize);

अटल sमाप_प्रकार xen_feature_show(पूर्णांक index, अक्षर *buffer)
अणु
	sमाप_प्रकार ret;
	काष्ठा xen_feature_info info;

	info.submap_idx = index;
	ret = HYPERVISOR_xen_version(XENVER_get_features, &info);
	अगर (!ret)
		ret = प्र_लिखो(buffer, "%08x", info.submap);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार features_show(काष्ठा hyp_sysfs_attr *attr, अक्षर *buffer)
अणु
	sमाप_प्रकार len;
	पूर्णांक i;

	len = 0;
	क्रम (i = XENFEAT_NR_SUBMAPS-1; i >= 0; i--) अणु
		पूर्णांक ret = xen_feature_show(i, buffer + len);
		अगर (ret < 0) अणु
			अगर (len == 0)
				len = ret;
			अवरोध;
		पूर्ण
		len += ret;
	पूर्ण
	अगर (len > 0)
		buffer[len++] = '\n';

	वापस len;
पूर्ण

HYPERVISOR_ATTR_RO(features);

अटल sमाप_प्रकार buildid_show(काष्ठा hyp_sysfs_attr *attr, अक्षर *buffer)
अणु
	sमाप_प्रकार ret;
	काष्ठा xen_build_id *buildid;

	ret = HYPERVISOR_xen_version(XENVER_build_id, शून्य);
	अगर (ret < 0) अणु
		अगर (ret == -EPERM)
			ret = प्र_लिखो(buffer, "<denied>");
		वापस ret;
	पूर्ण

	buildid = kदो_स्मृति(माप(*buildid) + ret, GFP_KERNEL);
	अगर (!buildid)
		वापस -ENOMEM;

	buildid->len = ret;
	ret = HYPERVISOR_xen_version(XENVER_build_id, buildid);
	अगर (ret > 0)
		ret = प्र_लिखो(buffer, "%s", buildid->buf);
	kमुक्त(buildid);

	वापस ret;
पूर्ण

HYPERVISOR_ATTR_RO(buildid);

अटल काष्ठा attribute *xen_properties_attrs[] = अणु
	&capabilities_attr.attr,
	&changeset_attr.attr,
	&भव_start_attr.attr,
	&pagesize_attr.attr,
	&features_attr.attr,
	&buildid_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group xen_properties_group = अणु
	.name = "properties",
	.attrs = xen_properties_attrs,
पूर्ण;

अटल पूर्णांक __init xen_sysfs_properties_init(व्योम)
अणु
	वापस sysfs_create_group(hypervisor_kobj, &xen_properties_group);
पूर्ण

#अगर_घोषित CONFIG_XEN_HAVE_VPMU
काष्ठा pmu_mode अणु
	स्थिर अक्षर *name;
	uपूर्णांक32_t mode;
पूर्ण;

अटल काष्ठा pmu_mode pmu_modes[] = अणु
	अणु"off", XENPMU_MODE_OFFपूर्ण,
	अणु"self", XENPMU_MODE_SELFपूर्ण,
	अणु"hv", XENPMU_MODE_HVपूर्ण,
	अणु"all", XENPMU_MODE_ALLपूर्ण
पूर्ण;

अटल sमाप_प्रकार pmu_mode_store(काष्ठा hyp_sysfs_attr *attr,
			      स्थिर अक्षर *buffer, माप_प्रकार len)
अणु
	पूर्णांक ret;
	काष्ठा xen_pmu_params xp;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pmu_modes); i++) अणु
		अगर (म_भेदन(buffer, pmu_modes[i].name, len - 1) == 0) अणु
			xp.val = pmu_modes[i].mode;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ARRAY_SIZE(pmu_modes))
		वापस -EINVAL;

	xp.version.maj = XENPMU_VER_MAJ;
	xp.version.min = XENPMU_VER_MIN;
	ret = HYPERVISOR_xenpmu_op(XENPMU_mode_set, &xp);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

अटल sमाप_प्रकार pmu_mode_show(काष्ठा hyp_sysfs_attr *attr, अक्षर *buffer)
अणु
	पूर्णांक ret;
	काष्ठा xen_pmu_params xp;
	पूर्णांक i;
	uपूर्णांक32_t mode;

	xp.version.maj = XENPMU_VER_MAJ;
	xp.version.min = XENPMU_VER_MIN;
	ret = HYPERVISOR_xenpmu_op(XENPMU_mode_get, &xp);
	अगर (ret)
		वापस ret;

	mode = (uपूर्णांक32_t)xp.val;
	क्रम (i = 0; i < ARRAY_SIZE(pmu_modes); i++) अणु
		अगर (mode == pmu_modes[i].mode)
			वापस प्र_लिखो(buffer, "%s\n", pmu_modes[i].name);
	पूर्ण

	वापस -EINVAL;
पूर्ण
HYPERVISOR_ATTR_RW(pmu_mode);

अटल sमाप_प्रकार pmu_features_store(काष्ठा hyp_sysfs_attr *attr,
				  स्थिर अक्षर *buffer, माप_प्रकार len)
अणु
	पूर्णांक ret;
	uपूर्णांक32_t features;
	काष्ठा xen_pmu_params xp;

	ret = kstrtou32(buffer, 0, &features);
	अगर (ret)
		वापस ret;

	xp.val = features;
	xp.version.maj = XENPMU_VER_MAJ;
	xp.version.min = XENPMU_VER_MIN;
	ret = HYPERVISOR_xenpmu_op(XENPMU_feature_set, &xp);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

अटल sमाप_प्रकार pmu_features_show(काष्ठा hyp_sysfs_attr *attr, अक्षर *buffer)
अणु
	पूर्णांक ret;
	काष्ठा xen_pmu_params xp;

	xp.version.maj = XENPMU_VER_MAJ;
	xp.version.min = XENPMU_VER_MIN;
	ret = HYPERVISOR_xenpmu_op(XENPMU_feature_get, &xp);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buffer, "0x%x\n", (uपूर्णांक32_t)xp.val);
पूर्ण
HYPERVISOR_ATTR_RW(pmu_features);

अटल काष्ठा attribute *xen_pmu_attrs[] = अणु
	&pmu_mode_attr.attr,
	&pmu_features_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group xen_pmu_group = अणु
	.name = "pmu",
	.attrs = xen_pmu_attrs,
पूर्ण;

अटल पूर्णांक __init xen_sysfs_pmu_init(व्योम)
अणु
	वापस sysfs_create_group(hypervisor_kobj, &xen_pmu_group);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init hyper_sysfs_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	ret = xen_sysfs_type_init();
	अगर (ret)
		जाओ out;
	ret = xen_sysfs_guest_type_init();
	अगर (ret)
		जाओ guest_type_out;
	ret = xen_sysfs_version_init();
	अगर (ret)
		जाओ version_out;
	ret = xen_sysfs_compilation_init();
	अगर (ret)
		जाओ comp_out;
	ret = xen_sysfs_uuid_init();
	अगर (ret)
		जाओ uuid_out;
	ret = xen_sysfs_properties_init();
	अगर (ret)
		जाओ prop_out;
#अगर_घोषित CONFIG_XEN_HAVE_VPMU
	अगर (xen_initial_करोमुख्य()) अणु
		ret = xen_sysfs_pmu_init();
		अगर (ret) अणु
			sysfs_हटाओ_group(hypervisor_kobj,
					   &xen_properties_group);
			जाओ prop_out;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	जाओ out;

prop_out:
	sysfs_हटाओ_file(hypervisor_kobj, &uuid_attr.attr);
uuid_out:
	sysfs_हटाओ_group(hypervisor_kobj, &xen_compilation_group);
comp_out:
	sysfs_हटाओ_group(hypervisor_kobj, &version_group);
version_out:
	sysfs_हटाओ_file(hypervisor_kobj, &guest_type_attr.attr);
guest_type_out:
	sysfs_हटाओ_file(hypervisor_kobj, &type_attr.attr);
out:
	वापस ret;
पूर्ण
device_initcall(hyper_sysfs_init);

अटल sमाप_प्रकार hyp_sysfs_show(काष्ठा kobject *kobj,
			      काष्ठा attribute *attr,
			      अक्षर *buffer)
अणु
	काष्ठा hyp_sysfs_attr *hyp_attr;
	hyp_attr = container_of(attr, काष्ठा hyp_sysfs_attr, attr);
	अगर (hyp_attr->show)
		वापस hyp_attr->show(hyp_attr, buffer);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार hyp_sysfs_store(काष्ठा kobject *kobj,
			       काष्ठा attribute *attr,
			       स्थिर अक्षर *buffer,
			       माप_प्रकार len)
अणु
	काष्ठा hyp_sysfs_attr *hyp_attr;
	hyp_attr = container_of(attr, काष्ठा hyp_sysfs_attr, attr);
	अगर (hyp_attr->store)
		वापस hyp_attr->store(hyp_attr, buffer, len);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops hyp_sysfs_ops = अणु
	.show = hyp_sysfs_show,
	.store = hyp_sysfs_store,
पूर्ण;

अटल काष्ठा kobj_type hyp_sysfs_kobj_type = अणु
	.sysfs_ops = &hyp_sysfs_ops,
पूर्ण;

अटल पूर्णांक __init hypervisor_subsys_init(व्योम)
अणु
	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	hypervisor_kobj->ktype = &hyp_sysfs_kobj_type;
	वापस 0;
पूर्ण
device_initcall(hypervisor_subsys_init);
