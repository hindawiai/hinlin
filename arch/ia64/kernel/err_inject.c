<शैली गुरु>
/*
 * err_inject.c -
 *	1.) Inject errors to a processor.
 *	2.) Query error injection capabilities.
 * This driver aदीर्घ with user space code can be acting as an error
 * injection tool.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Written by: Fenghua Yu <fenghua.yu@पूर्णांकel.com>, Intel Corporation
 * Copyright (C) 2006, Intel Corp.  All rights reserved.
 *
 */
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/cpu.h>
#समावेश <linux/module.h>

#घोषणा ERR_INJ_DEBUG

#घोषणा ERR_DATA_BUFFER_SIZE 3 		// Three 8-byte;

#घोषणा define_one_ro(name) 						\
अटल DEVICE_ATTR(name, 0444, show_##name, शून्य)

#घोषणा define_one_rw(name) 						\
अटल DEVICE_ATTR(name, 0644, show_##name, store_##name)

अटल u64 call_start[NR_CPUS];
अटल u64 phys_addr[NR_CPUS];
अटल u64 err_type_info[NR_CPUS];
अटल u64 err_काष्ठा_info[NR_CPUS];
अटल काष्ठा अणु
	u64 data1;
	u64 data2;
	u64 data3;
पूर्ण __attribute__((__aligned__(16))) err_data_buffer[NR_CPUS];
अटल s64 status[NR_CPUS];
अटल u64 capabilities[NR_CPUS];
अटल u64 resources[NR_CPUS];

#घोषणा show(name) 							\
अटल sमाप_प्रकार 								\
show_##name(काष्ठा device *dev, काष्ठा device_attribute *attr,	\
		अक्षर *buf)						\
अणु									\
	u32 cpu=dev->id;						\
	वापस प्र_लिखो(buf, "%llx\n", name[cpu]);			\
पूर्ण

#घोषणा store(name)							\
अटल sमाप_प्रकार 								\
store_##name(काष्ठा device *dev, काष्ठा device_attribute *attr,	\
					स्थिर अक्षर *buf, माप_प्रकार size)	\
अणु									\
	अचिन्हित पूर्णांक cpu=dev->id;					\
	name[cpu] = simple_म_से_अदीर्घl(buf, शून्य, 16);			\
	वापस size;							\
पूर्ण

show(call_start)

/* It's user's responsibility to call the PAL procedure on a specअगरic
 * processor. The cpu number in driver is only used क्रम storing data.
 */
अटल sमाप_प्रकार
store_call_start(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक cpu=dev->id;
	अचिन्हित दीर्घ call_start = simple_म_से_अदीर्घl(buf, शून्य, 16);

#अगर_घोषित ERR_INJ_DEBUG
	prपूर्णांकk(KERN_DEBUG "pal_mc_err_inject for cpu%d:\n", cpu);
	prपूर्णांकk(KERN_DEBUG "err_type_info=%llx,\n", err_type_info[cpu]);
	prपूर्णांकk(KERN_DEBUG "err_struct_info=%llx,\n", err_काष्ठा_info[cpu]);
	prपूर्णांकk(KERN_DEBUG "err_data_buffer=%llx, %llx, %llx.\n",
			  err_data_buffer[cpu].data1,
			  err_data_buffer[cpu].data2,
			  err_data_buffer[cpu].data3);
#पूर्ण_अगर
	चयन (call_start) अणु
	    हाल 0: /* Do nothing. */
		अवरोध;
	    हाल 1: /* Call pal_mc_error_inject in physical mode. */
		status[cpu]=ia64_pal_mc_error_inject_phys(err_type_info[cpu],
					err_काष्ठा_info[cpu],
					ia64_tpa(&err_data_buffer[cpu]),
					&capabilities[cpu],
			 		&resources[cpu]);
		अवरोध;
	    हाल 2: /* Call pal_mc_error_inject in भव mode. */
		status[cpu]=ia64_pal_mc_error_inject_virt(err_type_info[cpu],
					err_काष्ठा_info[cpu],
					ia64_tpa(&err_data_buffer[cpu]),
					&capabilities[cpu],
			 		&resources[cpu]);
		अवरोध;
	    शेष:
		status[cpu] = -EINVAL;
		अवरोध;
	पूर्ण

#अगर_घोषित ERR_INJ_DEBUG
	prपूर्णांकk(KERN_DEBUG "Returns: status=%d,\n", (पूर्णांक)status[cpu]);
	prपूर्णांकk(KERN_DEBUG "capabilities=%llx,\n", capabilities[cpu]);
	prपूर्णांकk(KERN_DEBUG "resources=%llx\n", resources[cpu]);
#पूर्ण_अगर
	वापस size;
पूर्ण

show(err_type_info)
store(err_type_info)

अटल sमाप_प्रकार
show_भव_to_phys(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	अचिन्हित पूर्णांक cpu=dev->id;
	वापस प्र_लिखो(buf, "%llx\n", phys_addr[cpu]);
पूर्ण

अटल sमाप_प्रकार
store_भव_to_phys(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक cpu=dev->id;
	u64 virt_addr=simple_म_से_अदीर्घl(buf, शून्य, 16);
	पूर्णांक ret;

	ret = get_user_pages_fast(virt_addr, 1, FOLL_WRITE, शून्य);
	अगर (ret<=0) अणु
#अगर_घोषित ERR_INJ_DEBUG
		prपूर्णांकk("Virtual address %llx is not existing.\n", virt_addr);
#पूर्ण_अगर
		वापस -EINVAL;
	पूर्ण

	phys_addr[cpu] = ia64_tpa(virt_addr);
	वापस size;
पूर्ण

show(err_काष्ठा_info)
store(err_काष्ठा_info)

अटल sमाप_प्रकार
show_err_data_buffer(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित पूर्णांक cpu=dev->id;

	वापस प्र_लिखो(buf, "%llx, %llx, %llx\n",
			err_data_buffer[cpu].data1,
			err_data_buffer[cpu].data2,
			err_data_buffer[cpu].data3);
पूर्ण

अटल sमाप_प्रकार
store_err_data_buffer(काष्ठा device *dev,
			काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक cpu=dev->id;
	पूर्णांक ret;

#अगर_घोषित ERR_INJ_DEBUG
	prपूर्णांकk("write err_data_buffer=[%llx,%llx,%llx] on cpu%d\n",
		 err_data_buffer[cpu].data1,
		 err_data_buffer[cpu].data2,
		 err_data_buffer[cpu].data3,
		 cpu);
#पूर्ण_अगर
	ret = माला_पूछो(buf, "%llx, %llx, %llx",
			&err_data_buffer[cpu].data1,
			&err_data_buffer[cpu].data2,
			&err_data_buffer[cpu].data3);
	अगर (ret!=ERR_DATA_BUFFER_SIZE)
		वापस -EINVAL;

	वापस size;
पूर्ण

show(status)
show(capabilities)
show(resources)

define_one_rw(call_start);
define_one_rw(err_type_info);
define_one_rw(err_काष्ठा_info);
define_one_rw(err_data_buffer);
define_one_rw(भव_to_phys);
define_one_ro(status);
define_one_ro(capabilities);
define_one_ro(resources);

अटल काष्ठा attribute *शेष_attrs[] = अणु
	&dev_attr_call_start.attr,
	&dev_attr_भव_to_phys.attr,
	&dev_attr_err_type_info.attr,
	&dev_attr_err_काष्ठा_info.attr,
	&dev_attr_err_data_buffer.attr,
	&dev_attr_status.attr,
	&dev_attr_capabilities.attr,
	&dev_attr_resources.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group err_inject_attr_group = अणु
	.attrs = शेष_attrs,
	.name = "err_inject"
पूर्ण;
/* Add/Remove err_inject पूर्णांकerface क्रम CPU device */
अटल पूर्णांक err_inject_add_dev(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *sys_dev = get_cpu_device(cpu);

	वापस sysfs_create_group(&sys_dev->kobj, &err_inject_attr_group);
पूर्ण

अटल पूर्णांक err_inject_हटाओ_dev(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *sys_dev = get_cpu_device(cpu);

	sysfs_हटाओ_group(&sys_dev->kobj, &err_inject_attr_group);
	वापस 0;
पूर्ण

अटल क्रमागत cpuhp_state hp_online;

अटल पूर्णांक __init err_inject_init(व्योम)
अणु
	पूर्णांक ret;
#अगर_घोषित ERR_INJ_DEBUG
	prपूर्णांकk(KERN_INFO "Enter error injection driver.\n");
#पूर्ण_अगर

	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "ia64/err_inj:online",
				err_inject_add_dev, err_inject_हटाओ_dev);
	अगर (ret >= 0) अणु
		hp_online = ret;
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम __निकास err_inject_निकास(व्योम)
अणु
#अगर_घोषित ERR_INJ_DEBUG
	prपूर्णांकk(KERN_INFO "Exit error injection driver.\n");
#पूर्ण_अगर
	cpuhp_हटाओ_state(hp_online);
पूर्ण

module_init(err_inject_init);
module_निकास(err_inject_निकास);

MODULE_AUTHOR("Fenghua Yu <fenghua.yu@intel.com>");
MODULE_DESCRIPTION("MC error injection kernel sysfs interface");
MODULE_LICENSE("GPL");
