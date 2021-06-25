<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/export.h>
#समावेश <linux/suspend.h>
#समावेश <linux/bcd.h>
#समावेश <linux/acpi.h>
#समावेश <linux/uaccess.h>

#समावेश "sleep.h"
#समावेश "internal.h"

/*
 * this file provides support क्रम:
 * /proc/acpi/wakeup
 */

अटल पूर्णांक
acpi_प्रणाली_wakeup_device_seq_show(काष्ठा seq_file *seq, व्योम *offset)
अणु
	काष्ठा acpi_device *dev, *पंचांगp;

	seq_म_लिखो(seq, "Device\tS-state\t  Status   Sysfs node\n");

	mutex_lock(&acpi_device_lock);
	list_क्रम_each_entry_safe(dev, पंचांगp, &acpi_wakeup_device_list,
				 wakeup_list) अणु
		काष्ठा acpi_device_physical_node *entry;

		अगर (!dev->wakeup.flags.valid)
			जारी;

		seq_म_लिखो(seq, "%s\t  S%d\t",
			   dev->pnp.bus_id,
			   (u32) dev->wakeup.sleep_state);

		mutex_lock(&dev->physical_node_lock);

		अगर (!dev->physical_node_count) अणु
			seq_म_लिखो(seq, "%c%-8s\n",
				dev->wakeup.flags.valid ? '*' : ' ',
				device_may_wakeup(&dev->dev) ?
					"enabled" : "disabled");
		पूर्ण अन्यथा अणु
			काष्ठा device *ldev;
			list_क्रम_each_entry(entry, &dev->physical_node_list,
					node) अणु
				ldev = get_device(entry->dev);
				अगर (!ldev)
					जारी;

				अगर (&entry->node !=
						dev->physical_node_list.next)
					seq_म_लिखो(seq, "\t\t");

				seq_म_लिखो(seq, "%c%-8s  %s:%s\n",
					dev->wakeup.flags.valid ? '*' : ' ',
					(device_may_wakeup(&dev->dev) ||
					device_may_wakeup(ldev)) ?
					"enabled" : "disabled",
					ldev->bus ? ldev->bus->name :
					"no-bus", dev_name(ldev));
				put_device(ldev);
			पूर्ण
		पूर्ण

		mutex_unlock(&dev->physical_node_lock);
	पूर्ण
	mutex_unlock(&acpi_device_lock);
	वापस 0;
पूर्ण

अटल व्योम physical_device_enable_wakeup(काष्ठा acpi_device *adev)
अणु
	काष्ठा acpi_device_physical_node *entry;

	mutex_lock(&adev->physical_node_lock);

	list_क्रम_each_entry(entry,
		&adev->physical_node_list, node)
		अगर (entry->dev && device_can_wakeup(entry->dev)) अणु
			bool enable = !device_may_wakeup(entry->dev);
			device_set_wakeup_enable(entry->dev, enable);
		पूर्ण

	mutex_unlock(&adev->physical_node_lock);
पूर्ण

अटल sमाप_प्रकार
acpi_प्रणाली_ग_लिखो_wakeup_device(काष्ठा file *file,
				स्थिर अक्षर __user * buffer,
				माप_प्रकार count, loff_t * ppos)
अणु
	काष्ठा acpi_device *dev, *पंचांगp;
	अक्षर strbuf[5];
	अक्षर str[5] = "";

	अगर (count > 4)
		count = 4;

	अगर (copy_from_user(strbuf, buffer, count))
		वापस -EFAULT;
	strbuf[count] = '\0';
	माला_पूछो(strbuf, "%s", str);

	mutex_lock(&acpi_device_lock);
	list_क्रम_each_entry_safe(dev, पंचांगp, &acpi_wakeup_device_list,
				 wakeup_list) अणु
		अगर (!dev->wakeup.flags.valid)
			जारी;

		अगर (!म_भेदन(dev->pnp.bus_id, str, 4)) अणु
			अगर (device_can_wakeup(&dev->dev)) अणु
				bool enable = !device_may_wakeup(&dev->dev);
				device_set_wakeup_enable(&dev->dev, enable);
			पूर्ण अन्यथा अणु
				physical_device_enable_wakeup(dev);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&acpi_device_lock);
	वापस count;
पूर्ण

अटल पूर्णांक
acpi_प्रणाली_wakeup_device_खोलो_fs(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, acpi_प्रणाली_wakeup_device_seq_show,
			   PDE_DATA(inode));
पूर्ण

अटल स्थिर काष्ठा proc_ops acpi_प्रणाली_wakeup_device_proc_ops = अणु
	.proc_खोलो	= acpi_प्रणाली_wakeup_device_खोलो_fs,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_ग_लिखो	= acpi_प्रणाली_ग_लिखो_wakeup_device,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
पूर्ण;

व्योम __init acpi_sleep_proc_init(व्योम)
अणु
	/* 'wakeup device' [R/W] */
	proc_create("wakeup", S_IFREG | S_IRUGO | S_IWUSR,
		    acpi_root_dir, &acpi_प्रणाली_wakeup_device_proc_ops);
पूर्ण
