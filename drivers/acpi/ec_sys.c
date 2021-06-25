<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ec_sys.c
 *
 * Copyright (C) 2010 SUSE Products GmbH/Novell
 * Author:
 *      Thomas Renninger <trenn@suse.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/acpi.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश "internal.h"

MODULE_AUTHOR("Thomas Renninger <trenn@suse.de>");
MODULE_DESCRIPTION("ACPI EC sysfs access driver");
MODULE_LICENSE("GPL");

अटल bool ग_लिखो_support;
module_param(ग_लिखो_support, bool, 0644);
MODULE_PARM_DESC(ग_लिखो_support, "Dangerous, reboot and removal of battery may "
		 "be needed.");

#घोषणा EC_SPACE_SIZE 256

अटल काष्ठा dentry *acpi_ec_debugfs_dir;

अटल sमाप_प्रकार acpi_ec_पढ़ो_io(काष्ठा file *f, अक्षर __user *buf,
			       माप_प्रकार count, loff_t *off)
अणु
	/* Use this अगर support पढ़ोing/writing multiple ECs exists in ec.c:
	 * काष्ठा acpi_ec *ec = ((काष्ठा seq_file *)f->निजी_data)->निजी;
	 */
	अचिन्हित पूर्णांक size = EC_SPACE_SIZE;
	loff_t init_off = *off;
	पूर्णांक err = 0;

	अगर (*off >= size)
		वापस 0;
	अगर (*off + count >= size) अणु
		size -= *off;
		count = size;
	पूर्ण अन्यथा
		size = count;

	जबतक (size) अणु
		u8 byte_पढ़ो;
		err = ec_पढ़ो(*off, &byte_पढ़ो);
		अगर (err)
			वापस err;
		अगर (put_user(byte_पढ़ो, buf + *off - init_off)) अणु
			अगर (*off - init_off)
				वापस *off - init_off; /* partial पढ़ो */
			वापस -EFAULT;
		पूर्ण
		*off += 1;
		size--;
	पूर्ण
	वापस count;
पूर्ण

अटल sमाप_प्रकार acpi_ec_ग_लिखो_io(काष्ठा file *f, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *off)
अणु
	/* Use this अगर support पढ़ोing/writing multiple ECs exists in ec.c:
	 * काष्ठा acpi_ec *ec = ((काष्ठा seq_file *)f->निजी_data)->निजी;
	 */

	अचिन्हित पूर्णांक size = count;
	loff_t init_off = *off;
	पूर्णांक err = 0;

	अगर (!ग_लिखो_support)
		वापस -EINVAL;

	अगर (*off >= EC_SPACE_SIZE)
		वापस 0;
	अगर (*off + count >= EC_SPACE_SIZE) अणु
		size = EC_SPACE_SIZE - *off;
		count = size;
	पूर्ण

	जबतक (size) अणु
		u8 byte_ग_लिखो;
		अगर (get_user(byte_ग_लिखो, buf + *off - init_off)) अणु
			अगर (*off - init_off)
				वापस *off - init_off; /* partial ग_लिखो */
			वापस -EFAULT;
		पूर्ण
		err = ec_ग_लिखो(*off, byte_ग_लिखो);
		अगर (err)
			वापस err;

		*off += 1;
		size--;
	पूर्ण
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations acpi_ec_io_ops = अणु
	.owner = THIS_MODULE,
	.खोलो  = simple_खोलो,
	.पढ़ो  = acpi_ec_पढ़ो_io,
	.ग_लिखो = acpi_ec_ग_लिखो_io,
	.llseek = शेष_llseek,
पूर्ण;

अटल व्योम acpi_ec_add_debugfs(काष्ठा acpi_ec *ec, अचिन्हित पूर्णांक ec_device_count)
अणु
	काष्ठा dentry *dev_dir;
	अक्षर name[64];
	umode_t mode = 0400;

	अगर (ec_device_count == 0)
		acpi_ec_debugfs_dir = debugfs_create_dir("ec", शून्य);

	प्र_लिखो(name, "ec%u", ec_device_count);
	dev_dir = debugfs_create_dir(name, acpi_ec_debugfs_dir);

	debugfs_create_x32("gpe", 0444, dev_dir, &first_ec->gpe);
	debugfs_create_bool("use_global_lock", 0444, dev_dir,
			    &first_ec->global_lock);

	अगर (ग_लिखो_support)
		mode = 0600;
	debugfs_create_file("io", mode, dev_dir, ec, &acpi_ec_io_ops);
पूर्ण

अटल पूर्णांक __init acpi_ec_sys_init(व्योम)
अणु
	अगर (first_ec)
		acpi_ec_add_debugfs(first_ec, 0);
	वापस 0;
पूर्ण

अटल व्योम __निकास acpi_ec_sys_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(acpi_ec_debugfs_dir);
पूर्ण

module_init(acpi_ec_sys_init);
module_निकास(acpi_ec_sys_निकास);
