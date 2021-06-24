<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * custom_method.c - debugfs पूर्णांकerface क्रम customizing ACPI control method
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/acpi.h>
#समावेश <linux/security.h>

#समावेश "internal.h"

MODULE_LICENSE("GPL");

अटल काष्ठा dentry *cm_dentry;

/* /sys/kernel/debug/acpi/custom_method */

अटल sमाप_प्रकार cm_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	अटल अक्षर *buf;
	अटल u32 max_size;
	अटल u32 uncopied_bytes;

	काष्ठा acpi_table_header table;
	acpi_status status;
	पूर्णांक ret;

	ret = security_locked_करोwn(LOCKDOWN_ACPI_TABLES);
	अगर (ret)
		वापस ret;

	अगर (!(*ppos)) अणु
		/* parse the table header to get the table length */
		अगर (count <= माप(काष्ठा acpi_table_header))
			वापस -EINVAL;
		अगर (copy_from_user(&table, user_buf,
				   माप(काष्ठा acpi_table_header)))
			वापस -EFAULT;
		uncopied_bytes = max_size = table.length;
		/* make sure the buf is not allocated */
		kमुक्त(buf);
		buf = kzalloc(max_size, GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;
	पूर्ण

	अगर (buf == शून्य)
		वापस -EINVAL;

	अगर ((*ppos > max_size) ||
	    (*ppos + count > max_size) ||
	    (*ppos + count < count) ||
	    (count > uncopied_bytes)) अणु
		kमुक्त(buf);
		buf = शून्य;
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(buf + (*ppos), user_buf, count)) अणु
		kमुक्त(buf);
		buf = शून्य;
		वापस -EFAULT;
	पूर्ण

	uncopied_bytes -= count;
	*ppos += count;

	अगर (!uncopied_bytes) अणु
		status = acpi_install_method(buf);
		kमुक्त(buf);
		buf = शून्य;
		अगर (ACPI_FAILURE(status))
			वापस -EINVAL;
		add_taपूर्णांक(TAINT_OVERRIDDEN_ACPI_TABLE, LOCKDEP_NOW_UNRELIABLE);
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations cm_fops = अणु
	.ग_लिखो = cm_ग_लिखो,
	.llseek = शेष_llseek,
पूर्ण;

अटल पूर्णांक __init acpi_custom_method_init(व्योम)
अणु
	cm_dentry = debugfs_create_file("custom_method", S_IWUSR,
					acpi_debugfs_dir, शून्य, &cm_fops);
	वापस 0;
पूर्ण

अटल व्योम __निकास acpi_custom_method_निकास(व्योम)
अणु
	debugfs_हटाओ(cm_dentry);
पूर्ण

module_init(acpi_custom_method_init);
module_निकास(acpi_custom_method_निकास);
