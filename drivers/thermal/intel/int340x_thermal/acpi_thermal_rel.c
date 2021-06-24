<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* acpi_thermal_rel.c driver क्रम exporting ACPI thermal relationship
 *
 * Copyright (c) 2014 Intel Corp
 */

/*
 * Two functionalities included:
 * 1. Export _TRT, _ART, via misc device पूर्णांकerface to the userspace.
 * 2. Provide parsing result to kernel drivers
 *
 */
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/acpi.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/fs.h>
#समावेश "acpi_thermal_rel.h"

अटल acpi_handle acpi_thermal_rel_handle;
अटल DEFINE_SPINLOCK(acpi_thermal_rel_chrdev_lock);
अटल पूर्णांक acpi_thermal_rel_chrdev_count;	/* #बार खोलोed */
अटल पूर्णांक acpi_thermal_rel_chrdev_exclu;	/* alपढ़ोy खोलो exclusive? */

अटल पूर्णांक acpi_thermal_rel_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	spin_lock(&acpi_thermal_rel_chrdev_lock);
	अगर (acpi_thermal_rel_chrdev_exclu ||
	    (acpi_thermal_rel_chrdev_count && (file->f_flags & O_EXCL))) अणु
		spin_unlock(&acpi_thermal_rel_chrdev_lock);
		वापस -EBUSY;
	पूर्ण

	अगर (file->f_flags & O_EXCL)
		acpi_thermal_rel_chrdev_exclu = 1;
	acpi_thermal_rel_chrdev_count++;

	spin_unlock(&acpi_thermal_rel_chrdev_lock);

	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल पूर्णांक acpi_thermal_rel_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	spin_lock(&acpi_thermal_rel_chrdev_lock);
	acpi_thermal_rel_chrdev_count--;
	acpi_thermal_rel_chrdev_exclu = 0;
	spin_unlock(&acpi_thermal_rel_chrdev_lock);

	वापस 0;
पूर्ण

/**
 * acpi_parse_trt - Thermal Relationship Table _TRT क्रम passive cooling
 *
 * @handle: ACPI handle of the device contains _TRT
 * @trt_count: the number of valid entries resulted from parsing _TRT
 * @trtp: poपूर्णांकer to poपूर्णांकer of array of _TRT entries in parsing result
 * @create_dev: whether to create platक्रमm devices क्रम target and source
 *
 */
पूर्णांक acpi_parse_trt(acpi_handle handle, पूर्णांक *trt_count, काष्ठा trt **trtp,
		bool create_dev)
अणु
	acpi_status status;
	पूर्णांक result = 0;
	पूर्णांक i;
	पूर्णांक nr_bad_entries = 0;
	काष्ठा trt *trts;
	काष्ठा acpi_device *adev;
	जोड़ acpi_object *p;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा acpi_buffer element = अणु 0, शून्य पूर्ण;
	काष्ठा acpi_buffer trt_क्रमmat = अणु माप("RRNNNNNN"), "RRNNNNNN" पूर्ण;

	status = acpi_evaluate_object(handle, "_TRT", शून्य, &buffer);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	p = buffer.poपूर्णांकer;
	अगर (!p || (p->type != ACPI_TYPE_PACKAGE)) अणु
		pr_err("Invalid _TRT data\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण

	*trt_count = p->package.count;
	trts = kसुस्मृति(*trt_count, माप(काष्ठा trt), GFP_KERNEL);
	अगर (!trts) अणु
		result = -ENOMEM;
		जाओ end;
	पूर्ण

	क्रम (i = 0; i < *trt_count; i++) अणु
		काष्ठा trt *trt = &trts[i - nr_bad_entries];

		element.length = माप(काष्ठा trt);
		element.poपूर्णांकer = trt;

		status = acpi_extract_package(&(p->package.elements[i]),
					      &trt_क्रमmat, &element);
		अगर (ACPI_FAILURE(status)) अणु
			nr_bad_entries++;
			pr_warn("_TRT package %d is invalid, ignored\n", i);
			जारी;
		पूर्ण
		अगर (!create_dev)
			जारी;

		result = acpi_bus_get_device(trt->source, &adev);
		अगर (result)
			pr_warn("Failed to get source ACPI device\n");

		result = acpi_bus_get_device(trt->target, &adev);
		अगर (result)
			pr_warn("Failed to get target ACPI device\n");
	पूर्ण

	result = 0;

	*trtp = trts;
	/* करोn't count bad entries */
	*trt_count -= nr_bad_entries;
end:
	kमुक्त(buffer.poपूर्णांकer);
	वापस result;
पूर्ण
EXPORT_SYMBOL(acpi_parse_trt);

/**
 * acpi_parse_art - Parse Active Relationship Table _ART
 *
 * @handle: ACPI handle of the device contains _ART
 * @art_count: the number of valid entries resulted from parsing _ART
 * @artp: poपूर्णांकer to poपूर्णांकer of array of art entries in parsing result
 * @create_dev: whether to create platक्रमm devices क्रम target and source
 *
 */
पूर्णांक acpi_parse_art(acpi_handle handle, पूर्णांक *art_count, काष्ठा art **artp,
		bool create_dev)
अणु
	acpi_status status;
	पूर्णांक result = 0;
	पूर्णांक i;
	पूर्णांक nr_bad_entries = 0;
	काष्ठा art *arts;
	काष्ठा acpi_device *adev;
	जोड़ acpi_object *p;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा acpi_buffer element = अणु 0, शून्य पूर्ण;
	काष्ठा acpi_buffer art_क्रमmat =	अणु
		माप("RRNNNNNNNNNNN"), "RRNNNNNNNNNNN" पूर्ण;

	status = acpi_evaluate_object(handle, "_ART", शून्य, &buffer);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	p = buffer.poपूर्णांकer;
	अगर (!p || (p->type != ACPI_TYPE_PACKAGE)) अणु
		pr_err("Invalid _ART data\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण

	/* ignore p->package.elements[0], as this is _ART Revision field */
	*art_count = p->package.count - 1;
	arts = kसुस्मृति(*art_count, माप(काष्ठा art), GFP_KERNEL);
	अगर (!arts) अणु
		result = -ENOMEM;
		जाओ end;
	पूर्ण

	क्रम (i = 0; i < *art_count; i++) अणु
		काष्ठा art *art = &arts[i - nr_bad_entries];

		element.length = माप(काष्ठा art);
		element.poपूर्णांकer = art;

		status = acpi_extract_package(&(p->package.elements[i + 1]),
					      &art_क्रमmat, &element);
		अगर (ACPI_FAILURE(status)) अणु
			pr_warn("_ART package %d is invalid, ignored", i);
			nr_bad_entries++;
			जारी;
		पूर्ण
		अगर (!create_dev)
			जारी;

		अगर (art->source) अणु
			result = acpi_bus_get_device(art->source, &adev);
			अगर (result)
				pr_warn("Failed to get source ACPI device\n");
		पूर्ण
		अगर (art->target) अणु
			result = acpi_bus_get_device(art->target, &adev);
			अगर (result)
				pr_warn("Failed to get target ACPI device\n");
		पूर्ण
	पूर्ण

	*artp = arts;
	/* करोn't count bad entries */
	*art_count -= nr_bad_entries;
end:
	kमुक्त(buffer.poपूर्णांकer);
	वापस result;
पूर्ण
EXPORT_SYMBOL(acpi_parse_art);


/* get device name from acpi handle */
अटल व्योम get_single_name(acpi_handle handle, अक्षर *name)
अणु
	काष्ठा acpi_buffer buffer = अणुACPI_ALLOCATE_BUFFERपूर्ण;

	अगर (ACPI_FAILURE(acpi_get_name(handle, ACPI_SINGLE_NAME, &buffer)))
		pr_warn("Failed to get device name from acpi handle\n");
	अन्यथा अणु
		स_नकल(name, buffer.poपूर्णांकer, ACPI_NAMESEG_SIZE);
		kमुक्त(buffer.poपूर्णांकer);
	पूर्ण
पूर्ण

अटल पूर्णांक fill_art(अक्षर __user *ubuf)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक count;
	पूर्णांक art_len;
	काष्ठा art *arts = शून्य;
	जोड़ art_object *art_user;

	ret = acpi_parse_art(acpi_thermal_rel_handle, &count, &arts, false);
	अगर (ret)
		जाओ मुक्त_art;
	art_len = count * माप(जोड़ art_object);
	art_user = kzalloc(art_len, GFP_KERNEL);
	अगर (!art_user) अणु
		ret = -ENOMEM;
		जाओ मुक्त_art;
	पूर्ण
	/* now fill in user art data */
	क्रम (i = 0; i < count; i++) अणु
		/* userspace art needs device name instead of acpi reference */
		get_single_name(arts[i].source, art_user[i].source_device);
		get_single_name(arts[i].target, art_user[i].target_device);
		/* copy the rest पूर्णांक data in addition to source and target */
		स_नकल(&art_user[i].weight, &arts[i].weight,
			माप(u64) * (ACPI_NR_ART_ELEMENTS - 2));
	पूर्ण

	अगर (copy_to_user(ubuf, art_user, art_len))
		ret = -EFAULT;
	kमुक्त(art_user);
मुक्त_art:
	kमुक्त(arts);
	वापस ret;
पूर्ण

अटल पूर्णांक fill_trt(अक्षर __user *ubuf)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक count;
	पूर्णांक trt_len;
	काष्ठा trt *trts = शून्य;
	जोड़ trt_object *trt_user;

	ret = acpi_parse_trt(acpi_thermal_rel_handle, &count, &trts, false);
	अगर (ret)
		जाओ मुक्त_trt;
	trt_len = count * माप(जोड़ trt_object);
	trt_user = kzalloc(trt_len, GFP_KERNEL);
	अगर (!trt_user) अणु
		ret = -ENOMEM;
		जाओ मुक्त_trt;
	पूर्ण
	/* now fill in user trt data */
	क्रम (i = 0; i < count; i++) अणु
		/* userspace trt needs device name instead of acpi reference */
		get_single_name(trts[i].source, trt_user[i].source_device);
		get_single_name(trts[i].target, trt_user[i].target_device);
		trt_user[i].sample_period = trts[i].sample_period;
		trt_user[i].influence = trts[i].influence;
	पूर्ण

	अगर (copy_to_user(ubuf, trt_user, trt_len))
		ret = -EFAULT;
	kमुक्त(trt_user);
मुक्त_trt:
	kमुक्त(trts);
	वापस ret;
पूर्ण

अटल दीर्घ acpi_thermal_rel_ioctl(काष्ठा file *f, अचिन्हित पूर्णांक cmd,
				   अचिन्हित दीर्घ __arg)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ length = 0;
	पूर्णांक count = 0;
	अक्षर __user *arg = (व्योम __user *)__arg;
	काष्ठा trt *trts = शून्य;
	काष्ठा art *arts = शून्य;

	चयन (cmd) अणु
	हाल ACPI_THERMAL_GET_TRT_COUNT:
		ret = acpi_parse_trt(acpi_thermal_rel_handle, &count,
				&trts, false);
		kमुक्त(trts);
		अगर (!ret)
			वापस put_user(count, (अचिन्हित दीर्घ __user *)__arg);
		वापस ret;
	हाल ACPI_THERMAL_GET_TRT_LEN:
		ret = acpi_parse_trt(acpi_thermal_rel_handle, &count,
				&trts, false);
		kमुक्त(trts);
		length = count * माप(जोड़ trt_object);
		अगर (!ret)
			वापस put_user(length, (अचिन्हित दीर्घ __user *)__arg);
		वापस ret;
	हाल ACPI_THERMAL_GET_TRT:
		वापस fill_trt(arg);
	हाल ACPI_THERMAL_GET_ART_COUNT:
		ret = acpi_parse_art(acpi_thermal_rel_handle, &count,
				&arts, false);
		kमुक्त(arts);
		अगर (!ret)
			वापस put_user(count, (अचिन्हित दीर्घ __user *)__arg);
		वापस ret;
	हाल ACPI_THERMAL_GET_ART_LEN:
		ret = acpi_parse_art(acpi_thermal_rel_handle, &count,
				&arts, false);
		kमुक्त(arts);
		length = count * माप(जोड़ art_object);
		अगर (!ret)
			वापस put_user(length, (अचिन्हित दीर्घ __user *)__arg);
		वापस ret;

	हाल ACPI_THERMAL_GET_ART:
		वापस fill_art(arg);

	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations acpi_thermal_rel_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= acpi_thermal_rel_खोलो,
	.release	= acpi_thermal_rel_release,
	.unlocked_ioctl	= acpi_thermal_rel_ioctl,
	.llseek		= no_llseek,
पूर्ण;

अटल काष्ठा miscdevice acpi_thermal_rel_misc_device = अणु
	.minor	= MISC_DYNAMIC_MINOR,
	"acpi_thermal_rel",
	&acpi_thermal_rel_fops
पूर्ण;

पूर्णांक acpi_thermal_rel_misc_device_add(acpi_handle handle)
अणु
	acpi_thermal_rel_handle = handle;

	वापस misc_रेजिस्टर(&acpi_thermal_rel_misc_device);
पूर्ण
EXPORT_SYMBOL(acpi_thermal_rel_misc_device_add);

पूर्णांक acpi_thermal_rel_misc_device_हटाओ(acpi_handle handle)
अणु
	misc_deरेजिस्टर(&acpi_thermal_rel_misc_device);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(acpi_thermal_rel_misc_device_हटाओ);

MODULE_AUTHOR("Zhang Rui <rui.zhang@intel.com>");
MODULE_AUTHOR("Jacob Pan <jacob.jun.pan@intel.com");
MODULE_DESCRIPTION("Intel acpi thermal rel misc dev driver");
MODULE_LICENSE("GPL v2");
