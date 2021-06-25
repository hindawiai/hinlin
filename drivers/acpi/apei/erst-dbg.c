<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * APEI Error Record Serialization Table debug support
 *
 * ERST is a way provided by APEI to save and retrieve hardware error
 * inक्रमmation to and from a persistent store. This file provide the
 * debugging/testing support क्रम ERST kernel support and firmware
 * implementation.
 *
 * Copyright 2010 Intel Corp.
 *   Author: Huang Ying <ying.huang@पूर्णांकel.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <acpi/apei.h>
#समावेश <linux/miscdevice.h>

#समावेश "apei-internal.h"

#घोषणा ERST_DBG_PFX			"ERST DBG: "

#घोषणा ERST_DBG_RECORD_LEN_MAX		0x4000

अटल व्योम *erst_dbg_buf;
अटल अचिन्हित पूर्णांक erst_dbg_buf_len;

/* Prevent erst_dbg_पढ़ो/ग_लिखो from being invoked concurrently */
अटल DEFINE_MUTEX(erst_dbg_mutex);

अटल पूर्णांक erst_dbg_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक rc, *pos;

	अगर (erst_disable)
		वापस -ENODEV;

	pos = (पूर्णांक *)&file->निजी_data;

	rc = erst_get_record_id_begin(pos);
	अगर (rc)
		वापस rc;

	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल पूर्णांक erst_dbg_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	erst_get_record_id_end();

	वापस 0;
पूर्ण

अटल दीर्घ erst_dbg_ioctl(काष्ठा file *f, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक rc;
	u64 record_id;
	u32 record_count;

	चयन (cmd) अणु
	हाल APEI_ERST_CLEAR_RECORD:
		rc = copy_from_user(&record_id, (व्योम __user *)arg,
				    माप(record_id));
		अगर (rc)
			वापस -EFAULT;
		वापस erst_clear(record_id);
	हाल APEI_ERST_GET_RECORD_COUNT:
		rc = erst_get_record_count();
		अगर (rc < 0)
			वापस rc;
		record_count = rc;
		rc = put_user(record_count, (u32 __user *)arg);
		अगर (rc)
			वापस rc;
		वापस 0;
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार erst_dbg_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
			     माप_प्रकार usize, loff_t *off)
अणु
	पूर्णांक rc, *pos;
	sमाप_प्रकार len = 0;
	u64 id;

	अगर (*off)
		वापस -EINVAL;

	अगर (mutex_lock_पूर्णांकerruptible(&erst_dbg_mutex) != 0)
		वापस -EINTR;

	pos = (पूर्णांक *)&filp->निजी_data;

retry_next:
	rc = erst_get_record_id_next(pos, &id);
	अगर (rc)
		जाओ out;
	/* no more record */
	अगर (id == APEI_ERST_INVALID_RECORD_ID) अणु
		/*
		 * If the persistent store is empty initially, the function
		 * 'erst_read' below will वापस "-ENOENT" value. This causes
		 * 'retry_next' label is entered again. The वापसed value
		 * should be zero indicating the पढ़ो operation is खातापूर्ण.
		 */
		len = 0;

		जाओ out;
	पूर्ण
retry:
	rc = len = erst_पढ़ो(id, erst_dbg_buf, erst_dbg_buf_len);
	/* The record may be cleared by others, try पढ़ो next record */
	अगर (rc == -ENOENT)
		जाओ retry_next;
	अगर (rc < 0)
		जाओ out;
	अगर (len > ERST_DBG_RECORD_LEN_MAX) अणु
		pr_warn(ERST_DBG_PFX
			"Record (ID: 0x%llx) length is too long: %zd\n", id, len);
		rc = -EIO;
		जाओ out;
	पूर्ण
	अगर (len > erst_dbg_buf_len) अणु
		व्योम *p;
		rc = -ENOMEM;
		p = kदो_स्मृति(len, GFP_KERNEL);
		अगर (!p)
			जाओ out;
		kमुक्त(erst_dbg_buf);
		erst_dbg_buf = p;
		erst_dbg_buf_len = len;
		जाओ retry;
	पूर्ण

	rc = -EINVAL;
	अगर (len > usize)
		जाओ out;

	rc = -EFAULT;
	अगर (copy_to_user(ubuf, erst_dbg_buf, len))
		जाओ out;
	rc = 0;
out:
	mutex_unlock(&erst_dbg_mutex);
	वापस rc ? rc : len;
पूर्ण

अटल sमाप_प्रकार erst_dbg_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
			      माप_प्रकार usize, loff_t *off)
अणु
	पूर्णांक rc;
	काष्ठा cper_record_header *rcd;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (usize > ERST_DBG_RECORD_LEN_MAX) अणु
		pr_err(ERST_DBG_PFX "Too long record to be written\n");
		वापस -EINVAL;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&erst_dbg_mutex))
		वापस -EINTR;
	अगर (usize > erst_dbg_buf_len) अणु
		व्योम *p;
		rc = -ENOMEM;
		p = kदो_स्मृति(usize, GFP_KERNEL);
		अगर (!p)
			जाओ out;
		kमुक्त(erst_dbg_buf);
		erst_dbg_buf = p;
		erst_dbg_buf_len = usize;
	पूर्ण
	rc = copy_from_user(erst_dbg_buf, ubuf, usize);
	अगर (rc) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण
	rcd = erst_dbg_buf;
	rc = -EINVAL;
	अगर (rcd->record_length != usize)
		जाओ out;

	rc = erst_ग_लिखो(erst_dbg_buf);

out:
	mutex_unlock(&erst_dbg_mutex);
	वापस rc < 0 ? rc : usize;
पूर्ण

अटल स्थिर काष्ठा file_operations erst_dbg_ops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= erst_dbg_खोलो,
	.release	= erst_dbg_release,
	.पढ़ो		= erst_dbg_पढ़ो,
	.ग_लिखो		= erst_dbg_ग_लिखो,
	.unlocked_ioctl	= erst_dbg_ioctl,
	.llseek		= no_llseek,
पूर्ण;

अटल काष्ठा miscdevice erst_dbg_dev = अणु
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "erst_dbg",
	.fops	= &erst_dbg_ops,
पूर्ण;

अटल __init पूर्णांक erst_dbg_init(व्योम)
अणु
	अगर (erst_disable) अणु
		pr_info(ERST_DBG_PFX "ERST support is disabled.\n");
		वापस -ENODEV;
	पूर्ण
	वापस misc_रेजिस्टर(&erst_dbg_dev);
पूर्ण

अटल __निकास व्योम erst_dbg_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&erst_dbg_dev);
	kमुक्त(erst_dbg_buf);
पूर्ण

module_init(erst_dbg_init);
module_निकास(erst_dbg_निकास);

MODULE_AUTHOR("Huang Ying");
MODULE_DESCRIPTION("APEI Error Record Serialization Table debug support");
MODULE_LICENSE("GPL");
