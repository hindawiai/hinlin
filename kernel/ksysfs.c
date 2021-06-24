<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kernel/ksysfs.c - sysfs attributes in /sys/kernel, which
 * 		     are not related to any other subप्रणाली
 *
 * Copyright (C) 2004 Kay Sievers <kay.sievers@vrfy.org>
 */

#समावेश <linux/kobject.h>
#समावेश <linux/माला.स>
#समावेश <linux/sysfs.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/kexec.h>
#समावेश <linux/profile.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/sched.h>
#समावेश <linux/capability.h>
#समावेश <linux/compiler.h>

#समावेश <linux/rcupdate.h>	/* rcu_expedited and rcu_normal */

#घोषणा KERNEL_ATTR_RO(_name) \
अटल काष्ठा kobj_attribute _name##_attr = __ATTR_RO(_name)

#घोषणा KERNEL_ATTR_RW(_name) \
अटल काष्ठा kobj_attribute _name##_attr = \
	__ATTR(_name, 0644, _name##_show, _name##_store)

/* current uevent sequence number */
अटल sमाप_प्रकार uevent_seqnum_show(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%llu\n", (अचिन्हित दीर्घ दीर्घ)uevent_seqnum);
पूर्ण
KERNEL_ATTR_RO(uevent_seqnum);

#अगर_घोषित CONFIG_UEVENT_HELPER
/* uevent helper program, used during early boot */
अटल sमाप_प्रकार uevent_helper_show(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", uevent_helper);
पूर्ण
अटल sमाप_प्रकार uevent_helper_store(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अगर (count+1 > UEVENT_HELPER_PATH_LEN)
		वापस -ENOENT;
	स_नकल(uevent_helper, buf, count);
	uevent_helper[count] = '\0';
	अगर (count && uevent_helper[count-1] == '\n')
		uevent_helper[count-1] = '\0';
	वापस count;
पूर्ण
KERNEL_ATTR_RW(uevent_helper);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PROFILING
अटल sमाप_प्रकार profiling_show(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", prof_on);
पूर्ण
अटल sमाप_प्रकार profiling_store(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;

	अगर (prof_on)
		वापस -EEXIST;
	/*
	 * This eventually calls पूर्णांकo get_option() which
	 * has a ton of callers and is not स्थिर.  It is
	 * easiest to cast it away here.
	 */
	profile_setup((अक्षर *)buf);
	ret = profile_init();
	अगर (ret)
		वापस ret;
	ret = create_proc_profile();
	अगर (ret)
		वापस ret;
	वापस count;
पूर्ण
KERNEL_ATTR_RW(profiling);
#पूर्ण_अगर

#अगर_घोषित CONFIG_KEXEC_CORE
अटल sमाप_प्रकार kexec_loaded_show(काष्ठा kobject *kobj,
				 काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", !!kexec_image);
पूर्ण
KERNEL_ATTR_RO(kexec_loaded);

अटल sमाप_प्रकार kexec_crash_loaded_show(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", kexec_crash_loaded());
पूर्ण
KERNEL_ATTR_RO(kexec_crash_loaded);

अटल sमाप_प्रकार kexec_crash_size_show(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%zu\n", crash_get_memory_size());
पूर्ण
अटल sमाप_प्रकार kexec_crash_size_store(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ cnt;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(buf, 0, &cnt))
		वापस -EINVAL;

	ret = crash_shrink_memory(cnt);
	वापस ret < 0 ? ret : count;
पूर्ण
KERNEL_ATTR_RW(kexec_crash_size);

#पूर्ण_अगर /* CONFIG_KEXEC_CORE */

#अगर_घोषित CONFIG_CRASH_CORE

अटल sमाप_प्रकार vmcoreinfo_show(काष्ठा kobject *kobj,
			       काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	phys_addr_t vmcore_base = paddr_vmcoreinfo_note();
	वापस प्र_लिखो(buf, "%pa %x\n", &vmcore_base,
			(अचिन्हित पूर्णांक)VMCOREINFO_NOTE_SIZE);
पूर्ण
KERNEL_ATTR_RO(vmcoreinfo);

#पूर्ण_अगर /* CONFIG_CRASH_CORE */

/* whether file capabilities are enabled */
अटल sमाप_प्रकार fscaps_show(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", file_caps_enabled);
पूर्ण
KERNEL_ATTR_RO(fscaps);

#अगर_अघोषित CONFIG_TINY_RCU
पूर्णांक rcu_expedited;
अटल sमाप_प्रकार rcu_expedited_show(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", READ_ONCE(rcu_expedited));
पूर्ण
अटल sमाप_प्रकार rcu_expedited_store(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अगर (kstrtoपूर्णांक(buf, 0, &rcu_expedited))
		वापस -EINVAL;

	वापस count;
पूर्ण
KERNEL_ATTR_RW(rcu_expedited);

पूर्णांक rcu_normal;
अटल sमाप_प्रकार rcu_normal_show(काष्ठा kobject *kobj,
			       काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", READ_ONCE(rcu_normal));
पूर्ण
अटल sमाप_प्रकार rcu_normal_store(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अगर (kstrtoपूर्णांक(buf, 0, &rcu_normal))
		वापस -EINVAL;

	वापस count;
पूर्ण
KERNEL_ATTR_RW(rcu_normal);
#पूर्ण_अगर /* #अगर_अघोषित CONFIG_TINY_RCU */

/*
 * Make /sys/kernel/notes give the raw contents of our kernel .notes section.
 */
बाह्य स्थिर व्योम __start_notes __weak;
बाह्य स्थिर व्योम __stop_notes __weak;
#घोषणा	notes_size (&__stop_notes - &__start_notes)

अटल sमाप_प्रकार notes_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			  काष्ठा bin_attribute *bin_attr,
			  अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	स_नकल(buf, &__start_notes + off, count);
	वापस count;
पूर्ण

अटल काष्ठा bin_attribute notes_attr __ro_after_init  = अणु
	.attr = अणु
		.name = "notes",
		.mode = S_IRUGO,
	पूर्ण,
	.पढ़ो = &notes_पढ़ो,
पूर्ण;

काष्ठा kobject *kernel_kobj;
EXPORT_SYMBOL_GPL(kernel_kobj);

अटल काष्ठा attribute * kernel_attrs[] = अणु
	&fscaps_attr.attr,
	&uevent_seqnum_attr.attr,
#अगर_घोषित CONFIG_UEVENT_HELPER
	&uevent_helper_attr.attr,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PROFILING
	&profiling_attr.attr,
#पूर्ण_अगर
#अगर_घोषित CONFIG_KEXEC_CORE
	&kexec_loaded_attr.attr,
	&kexec_crash_loaded_attr.attr,
	&kexec_crash_size_attr.attr,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CRASH_CORE
	&vmcoreinfo_attr.attr,
#पूर्ण_अगर
#अगर_अघोषित CONFIG_TINY_RCU
	&rcu_expedited_attr.attr,
	&rcu_normal_attr.attr,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group kernel_attr_group = अणु
	.attrs = kernel_attrs,
पूर्ण;

अटल पूर्णांक __init ksysfs_init(व्योम)
अणु
	पूर्णांक error;

	kernel_kobj = kobject_create_and_add("kernel", शून्य);
	अगर (!kernel_kobj) अणु
		error = -ENOMEM;
		जाओ निकास;
	पूर्ण
	error = sysfs_create_group(kernel_kobj, &kernel_attr_group);
	अगर (error)
		जाओ kset_निकास;

	अगर (notes_size > 0) अणु
		notes_attr.size = notes_size;
		error = sysfs_create_bin_file(kernel_kobj, &notes_attr);
		अगर (error)
			जाओ group_निकास;
	पूर्ण

	वापस 0;

group_निकास:
	sysfs_हटाओ_group(kernel_kobj, &kernel_attr_group);
kset_निकास:
	kobject_put(kernel_kobj);
निकास:
	वापस error;
पूर्ण

core_initcall(ksysfs_init);
