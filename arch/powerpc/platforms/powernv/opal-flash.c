<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerNV OPAL Firmware Update Interface
 *
 * Copyright 2013 IBM Corp.
 */

#घोषणा DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/kobject.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/opal.h>

/* FLASH status codes */
#घोषणा FLASH_NO_OP		-1099	/* No operation initiated by user */
#घोषणा FLASH_NO_AUTH		-9002	/* Not a service authority partition */

/* Validate image status values */
#घोषणा VALIDATE_IMG_READY	-1001	/* Image पढ़ोy क्रम validation */
#घोषणा VALIDATE_IMG_INCOMPLETE	-1002	/* User copied < VALIDATE_BUF_SIZE */

/* Manage image status values */
#घोषणा MANAGE_ACTIVE_ERR	-9001	/* Cannot overग_लिखो active img */

/* Flash image status values */
#घोषणा FLASH_IMG_READY		0	/* Img पढ़ोy क्रम flash on reboot */
#घोषणा FLASH_INVALID_IMG	-1003	/* Flash image लघुer than expected */
#घोषणा FLASH_IMG_शून्य_DATA	-1004	/* Bad data in sg list entry */
#घोषणा FLASH_IMG_BAD_LEN	-1005	/* Bad length in sg list entry */

/* Manage operation tokens */
#घोषणा FLASH_REJECT_TMP_SIDE	0	/* Reject temporary fw image */
#घोषणा FLASH_COMMIT_TMP_SIDE	1	/* Commit temporary fw image */

/* Update tokens */
#घोषणा FLASH_UPDATE_CANCEL	0	/* Cancel update request */
#घोषणा FLASH_UPDATE_INIT	1	/* Initiate update */

/* Validate image update result tokens */
#घोषणा VALIDATE_TMP_UPDATE	0     /* T side will be updated */
#घोषणा VALIDATE_FLASH_AUTH	1     /* Partition करोes not have authority */
#घोषणा VALIDATE_INVALID_IMG	2     /* Candidate image is not valid */
#घोषणा VALIDATE_CUR_UNKNOWN	3     /* Current fixpack level is unknown */
/*
 * Current T side will be committed to P side beक्रमe being replace with new
 * image, and the new image is करोwnlevel from current image
 */
#घोषणा VALIDATE_TMP_COMMIT_DL	4
/*
 * Current T side will be committed to P side beक्रमe being replaced with new
 * image
 */
#घोषणा VALIDATE_TMP_COMMIT	5
/*
 * T side will be updated with a करोwnlevel image
 */
#घोषणा VALIDATE_TMP_UPDATE_DL	6
/*
 * The candidate image's release date is later than the system's firmware
 * service entitlement date - service warranty period has expired
 */
#घोषणा VALIDATE_OUT_OF_WRNTY	7

/* Validate buffer size */
#घोषणा VALIDATE_BUF_SIZE	4096

/* XXX: Assume candidate image size is <= 1GB */
#घोषणा MAX_IMAGE_SIZE	0x40000000

/* Image status */
क्रमागत अणु
	IMAGE_INVALID,
	IMAGE_LOADING,
	IMAGE_READY,
पूर्ण;

/* Candidate image data */
काष्ठा image_data_t अणु
	पूर्णांक		status;
	व्योम		*data;
	uपूर्णांक32_t	size;
पूर्ण;

/* Candidate image header */
काष्ठा image_header_t अणु
	uपूर्णांक16_t	magic;
	uपूर्णांक16_t	version;
	uपूर्णांक32_t	size;
पूर्ण;

काष्ठा validate_flash_t अणु
	पूर्णांक		status;		/* Return status */
	व्योम		*buf;		/* Candidate image buffer */
	uपूर्णांक32_t	buf_size;	/* Image size */
	uपूर्णांक32_t	result;		/* Update results token */
पूर्ण;

काष्ठा manage_flash_t अणु
	पूर्णांक status;		/* Return status */
पूर्ण;

काष्ठा update_flash_t अणु
	पूर्णांक status;		/* Return status */
पूर्ण;

अटल काष्ठा image_header_t	image_header;
अटल काष्ठा image_data_t	image_data;
अटल काष्ठा validate_flash_t	validate_flash_data;
अटल काष्ठा manage_flash_t	manage_flash_data;

/* Initialize update_flash_data status to No Operation */
अटल काष्ठा update_flash_t	update_flash_data = अणु
	.status = FLASH_NO_OP,
पूर्ण;

अटल DEFINE_MUTEX(image_data_mutex);

/*
 * Validate candidate image
 */
अटल अंतरभूत व्योम opal_flash_validate(व्योम)
अणु
	दीर्घ ret;
	व्योम *buf = validate_flash_data.buf;
	__be32 size = cpu_to_be32(validate_flash_data.buf_size);
	__be32 result;

	ret = opal_validate_flash(__pa(buf), &size, &result);

	validate_flash_data.status = ret;
	validate_flash_data.buf_size = be32_to_cpu(size);
	validate_flash_data.result = be32_to_cpu(result);
पूर्ण

/*
 * Validate output क्रमmat:
 *     validate result token
 *     current image version details
 *     new image version details
 */
अटल sमाप_प्रकार validate_show(काष्ठा kobject *kobj,
			     काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा validate_flash_t *args_buf = &validate_flash_data;
	पूर्णांक len;

	/* Candidate image is not validated */
	अगर (args_buf->status < VALIDATE_TMP_UPDATE) अणु
		len = प्र_लिखो(buf, "%d\n", args_buf->status);
		जाओ out;
	पूर्ण

	/* Result token */
	len = प्र_लिखो(buf, "%d\n", args_buf->result);

	/* Current and candidate image version details */
	अगर ((args_buf->result != VALIDATE_TMP_UPDATE) &&
	    (args_buf->result < VALIDATE_CUR_UNKNOWN))
		जाओ out;

	अगर (args_buf->buf_size > (VALIDATE_BUF_SIZE - len)) अणु
		स_नकल(buf + len, args_buf->buf, VALIDATE_BUF_SIZE - len);
		len = VALIDATE_BUF_SIZE;
	पूर्ण अन्यथा अणु
		स_नकल(buf + len, args_buf->buf, args_buf->buf_size);
		len += args_buf->buf_size;
	पूर्ण
out:
	/* Set status to शेष */
	args_buf->status = FLASH_NO_OP;
	वापस len;
पूर्ण

/*
 * Validate candidate firmware image
 *
 * Note:
 *   We are only पूर्णांकerested in first 4K bytes of the
 *   candidate image.
 */
अटल sमाप_प्रकार validate_store(काष्ठा kobject *kobj,
			      काष्ठा kobj_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा validate_flash_t *args_buf = &validate_flash_data;

	अगर (buf[0] != '1')
		वापस -EINVAL;

	mutex_lock(&image_data_mutex);

	अगर (image_data.status != IMAGE_READY ||
	    image_data.size < VALIDATE_BUF_SIZE) अणु
		args_buf->result = VALIDATE_INVALID_IMG;
		args_buf->status = VALIDATE_IMG_INCOMPLETE;
		जाओ out;
	पूर्ण

	/* Copy first 4k bytes of candidate image */
	स_नकल(args_buf->buf, image_data.data, VALIDATE_BUF_SIZE);

	args_buf->status = VALIDATE_IMG_READY;
	args_buf->buf_size = VALIDATE_BUF_SIZE;

	/* Validate candidate image */
	opal_flash_validate();

out:
	mutex_unlock(&image_data_mutex);
	वापस count;
पूर्ण

/*
 * Manage flash routine
 */
अटल अंतरभूत व्योम opal_flash_manage(uपूर्णांक8_t op)
अणु
	काष्ठा manage_flash_t *स्थिर args_buf = &manage_flash_data;

	args_buf->status = opal_manage_flash(op);
पूर्ण

/*
 * Show manage flash status
 */
अटल sमाप_प्रकार manage_show(काष्ठा kobject *kobj,
			   काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा manage_flash_t *स्थिर args_buf = &manage_flash_data;
	पूर्णांक rc;

	rc = प्र_लिखो(buf, "%d\n", args_buf->status);
	/* Set status to शेष*/
	args_buf->status = FLASH_NO_OP;
	वापस rc;
पूर्ण

/*
 * Manage operations:
 *   0 - Reject
 *   1 - Commit
 */
अटल sमाप_प्रकार manage_store(काष्ठा kobject *kobj,
			    काष्ठा kobj_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	uपूर्णांक8_t op;
	चयन (buf[0]) अणु
	हाल '0':
		op = FLASH_REJECT_TMP_SIDE;
		अवरोध;
	हाल '1':
		op = FLASH_COMMIT_TMP_SIDE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* commit/reject temporary image */
	opal_flash_manage(op);
	वापस count;
पूर्ण

/*
 * OPAL update flash
 */
अटल पूर्णांक opal_flash_update(पूर्णांक op)
अणु
	काष्ठा opal_sg_list *list;
	अचिन्हित दीर्घ addr;
	पूर्णांक64_t rc = OPAL_PARAMETER;

	अगर (op == FLASH_UPDATE_CANCEL) अणु
		pr_alert("FLASH: Image update cancelled\n");
		addr = '\0';
		जाओ flash;
	पूर्ण

	list = opal_vदो_स्मृति_to_sg_list(image_data.data, image_data.size);
	अगर (!list)
		जाओ invalid_img;

	/* First entry address */
	addr = __pa(list);

flash:
	rc = opal_update_flash(addr);

invalid_img:
	वापस rc;
पूर्ण

/* This माला_लो called just beक्रमe प्रणाली reboots */
व्योम opal_flash_update_prपूर्णांक_message(व्योम)
अणु
	अगर (update_flash_data.status != FLASH_IMG_READY)
		वापस;

	pr_alert("FLASH: Flashing new firmware\n");
	pr_alert("FLASH: Image is %u bytes\n", image_data.size);
	pr_alert("FLASH: Performing flash and reboot/shutdown\n");
	pr_alert("FLASH: This will take several minutes. Do not power off!\n");

	/* Small delay to help getting the above message out */
	msleep(500);
पूर्ण

/*
 * Show candidate image status
 */
अटल sमाप_प्रकार update_show(काष्ठा kobject *kobj,
			   काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा update_flash_t *स्थिर args_buf = &update_flash_data;
	वापस प्र_लिखो(buf, "%d\n", args_buf->status);
पूर्ण

/*
 * Set update image flag
 *  1 - Flash new image
 *  0 - Cancel flash request
 */
अटल sमाप_प्रकार update_store(काष्ठा kobject *kobj,
			    काष्ठा kobj_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा update_flash_t *स्थिर args_buf = &update_flash_data;
	पूर्णांक rc = count;

	mutex_lock(&image_data_mutex);

	चयन (buf[0]) अणु
	हाल '0':
		अगर (args_buf->status == FLASH_IMG_READY)
			opal_flash_update(FLASH_UPDATE_CANCEL);
		args_buf->status = FLASH_NO_OP;
		अवरोध;
	हाल '1':
		/* Image is loaded? */
		अगर (image_data.status == IMAGE_READY)
			args_buf->status =
				opal_flash_update(FLASH_UPDATE_INIT);
		अन्यथा
			args_buf->status = FLASH_INVALID_IMG;
		अवरोध;
	शेष:
		rc = -EINVAL;
	पूर्ण

	mutex_unlock(&image_data_mutex);
	वापस rc;
पूर्ण

/*
 * Free image buffer
 */
अटल व्योम मुक्त_image_buf(व्योम)
अणु
	व्योम *addr;
	पूर्णांक size;

	addr = image_data.data;
	size = PAGE_ALIGN(image_data.size);
	जबतक (size > 0) अणु
		ClearPageReserved(vदो_स्मृति_to_page(addr));
		addr += PAGE_SIZE;
		size -= PAGE_SIZE;
	पूर्ण
	vमुक्त(image_data.data);
	image_data.data = शून्य;
	image_data.status = IMAGE_INVALID;
पूर्ण

/*
 * Allocate image buffer.
 */
अटल पूर्णांक alloc_image_buf(अक्षर *buffer, माप_प्रकार count)
अणु
	व्योम *addr;
	पूर्णांक size;

	अगर (count < माप(image_header)) अणु
		pr_warn("FLASH: Invalid candidate image\n");
		वापस -EINVAL;
	पूर्ण

	स_नकल(&image_header, (व्योम *)buffer, माप(image_header));
	image_data.size = be32_to_cpu(image_header.size);
	pr_debug("FLASH: Candidate image size = %u\n", image_data.size);

	अगर (image_data.size > MAX_IMAGE_SIZE) अणु
		pr_warn("FLASH: Too large image\n");
		वापस -EINVAL;
	पूर्ण
	अगर (image_data.size < VALIDATE_BUF_SIZE) अणु
		pr_warn("FLASH: Image is shorter than expected\n");
		वापस -EINVAL;
	पूर्ण

	image_data.data = vzalloc(PAGE_ALIGN(image_data.size));
	अगर (!image_data.data) अणु
		pr_err("%s : Failed to allocate memory\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	/* Pin memory */
	addr = image_data.data;
	size = PAGE_ALIGN(image_data.size);
	जबतक (size > 0) अणु
		SetPageReserved(vदो_स्मृति_to_page(addr));
		addr += PAGE_SIZE;
		size -= PAGE_SIZE;
	पूर्ण

	image_data.status = IMAGE_LOADING;
	वापस 0;
पूर्ण

/*
 * Copy candidate image
 *
 * Parse candidate image header to get total image size
 * and pre-allocate required memory.
 */
अटल sमाप_प्रकार image_data_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *bin_attr,
				अक्षर *buffer, loff_t pos, माप_प्रकार count)
अणु
	पूर्णांक rc;

	mutex_lock(&image_data_mutex);

	/* New image ? */
	अगर (pos == 0) अणु
		/* Free memory, अगर alपढ़ोy allocated */
		अगर (image_data.data)
			मुक्त_image_buf();

		/* Cancel outstanding image update request */
		अगर (update_flash_data.status == FLASH_IMG_READY)
			opal_flash_update(FLASH_UPDATE_CANCEL);

		/* Allocate memory */
		rc = alloc_image_buf(buffer, count);
		अगर (rc)
			जाओ out;
	पूर्ण

	अगर (image_data.status != IMAGE_LOADING) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर ((pos + count) > image_data.size) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	स_नकल(image_data.data + pos, (व्योम *)buffer, count);
	rc = count;

	/* Set image status */
	अगर ((pos + count) == image_data.size) अणु
		pr_debug("FLASH: Candidate image loaded....\n");
		image_data.status = IMAGE_READY;
	पूर्ण

out:
	mutex_unlock(&image_data_mutex);
	वापस rc;
पूर्ण

/*
 * sysfs पूर्णांकerface :
 *  OPAL uses below sysfs files क्रम code update.
 *  We create these files under /sys/firmware/opal.
 *
 *   image		: Interface to load candidate firmware image
 *   validate_flash	: Validate firmware image
 *   manage_flash	: Commit/Reject firmware image
 *   update_flash	: Flash new firmware image
 *
 */
अटल स्थिर काष्ठा bin_attribute image_data_attr = अणु
	.attr = अणु.name = "image", .mode = 0200पूर्ण,
	.size = MAX_IMAGE_SIZE,	/* Limit image size */
	.ग_लिखो = image_data_ग_लिखो,
पूर्ण;

अटल काष्ठा kobj_attribute validate_attribute =
	__ATTR(validate_flash, 0600, validate_show, validate_store);

अटल काष्ठा kobj_attribute manage_attribute =
	__ATTR(manage_flash, 0600, manage_show, manage_store);

अटल काष्ठा kobj_attribute update_attribute =
	__ATTR(update_flash, 0600, update_show, update_store);

अटल काष्ठा attribute *image_op_attrs[] = अणु
	&validate_attribute.attr,
	&manage_attribute.attr,
	&update_attribute.attr,
	शून्य	/* need to शून्य terminate the list of attributes */
पूर्ण;

अटल काष्ठा attribute_group image_op_attr_group = अणु
	.attrs = image_op_attrs,
पूर्ण;

व्योम __init opal_flash_update_init(व्योम)
अणु
	पूर्णांक ret;

	/* Allocate validate image buffer */
	validate_flash_data.buf = kzalloc(VALIDATE_BUF_SIZE, GFP_KERNEL);
	अगर (!validate_flash_data.buf) अणु
		pr_err("%s : Failed to allocate memory\n", __func__);
		वापस;
	पूर्ण

	/* Make sure /sys/firmware/opal directory is created */
	अगर (!opal_kobj) अणु
		pr_warn("FLASH: opal kobject is not available\n");
		जाओ nokobj;
	पूर्ण

	/* Create the sysfs files */
	ret = sysfs_create_group(opal_kobj, &image_op_attr_group);
	अगर (ret) अणु
		pr_warn("FLASH: Failed to create sysfs files\n");
		जाओ nokobj;
	पूर्ण

	ret = sysfs_create_bin_file(opal_kobj, &image_data_attr);
	अगर (ret) अणु
		pr_warn("FLASH: Failed to create sysfs files\n");
		जाओ nosysfs_file;
	पूर्ण

	/* Set शेष status */
	validate_flash_data.status = FLASH_NO_OP;
	manage_flash_data.status = FLASH_NO_OP;
	update_flash_data.status = FLASH_NO_OP;
	image_data.status = IMAGE_INVALID;
	वापस;

nosysfs_file:
	sysfs_हटाओ_group(opal_kobj, &image_op_attr_group);

nokobj:
	kमुक्त(validate_flash_data.buf);
	वापस;
पूर्ण
