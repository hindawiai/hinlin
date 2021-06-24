<शैली गुरु>
/*
 * linux/drivers/video/fb_sys_पढ़ो.c - Generic file operations where
 * framebuffer is in प्रणाली RAM
 *
 * Copyright (C) 2007 Antonino Daplas <adaplas@pol.net>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 *
 */
#समावेश <linux/fb.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>

sमाप_प्रकार fb_sys_पढ़ो(काष्ठा fb_info *info, अक्षर __user *buf, माप_प्रकार count,
		    loff_t *ppos)
अणु
	अचिन्हित दीर्घ p = *ppos;
	व्योम *src;
	पूर्णांक err = 0;
	अचिन्हित दीर्घ total_size;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस -EPERM;

	total_size = info->screen_size;

	अगर (total_size == 0)
		total_size = info->fix.smem_len;

	अगर (p >= total_size)
		वापस 0;

	अगर (count >= total_size)
		count = total_size;

	अगर (count + p > total_size)
		count = total_size - p;

	src = (व्योम __क्रमce *)(info->screen_base + p);

	अगर (info->fbops->fb_sync)
		info->fbops->fb_sync(info);

	अगर (copy_to_user(buf, src, count))
		err = -EFAULT;

	अगर  (!err)
		*ppos += count;

	वापस (err) ? err : count;
पूर्ण
EXPORT_SYMBOL_GPL(fb_sys_पढ़ो);

sमाप_प्रकार fb_sys_ग_लिखो(काष्ठा fb_info *info, स्थिर अक्षर __user *buf,
		     माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित दीर्घ p = *ppos;
	व्योम *dst;
	पूर्णांक err = 0;
	अचिन्हित दीर्घ total_size;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस -EPERM;

	total_size = info->screen_size;

	अगर (total_size == 0)
		total_size = info->fix.smem_len;

	अगर (p > total_size)
		वापस -EFBIG;

	अगर (count > total_size) अणु
		err = -EFBIG;
		count = total_size;
	पूर्ण

	अगर (count + p > total_size) अणु
		अगर (!err)
			err = -ENOSPC;

		count = total_size - p;
	पूर्ण

	dst = (व्योम __क्रमce *) (info->screen_base + p);

	अगर (info->fbops->fb_sync)
		info->fbops->fb_sync(info);

	अगर (copy_from_user(dst, buf, count))
		err = -EFAULT;

	अगर  (!err)
		*ppos += count;

	वापस (err) ? err : count;
पूर्ण
EXPORT_SYMBOL_GPL(fb_sys_ग_लिखो);

MODULE_AUTHOR("Antonino Daplas <adaplas@pol.net>");
MODULE_DESCRIPTION("Generic file read (fb in system RAM)");
MODULE_LICENSE("GPL");
