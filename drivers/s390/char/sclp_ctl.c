<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IOCTL पूर्णांकerface क्रम SCLP
 *
 * Copyright IBM Corp. 2012
 *
 * Author: Michael Holzheu <holzheu@linux.vnet.ibm.com>
 */

#समावेश <linux/compat.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/gfp.h>
#समावेश <linux/init.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/fs.h>
#समावेश <यंत्र/sclp_ctl.h>
#समावेश <यंत्र/sclp.h>

#समावेश "sclp.h"

/*
 * Supported command words
 */
अटल अचिन्हित पूर्णांक sclp_ctl_sccb_wlist[] = अणु
	0x00400002,
	0x00410002,
पूर्ण;

/*
 * Check अगर command word is supported
 */
अटल पूर्णांक sclp_ctl_cmdw_supported(अचिन्हित पूर्णांक cmdw)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sclp_ctl_sccb_wlist); i++) अणु
		अगर (cmdw == sclp_ctl_sccb_wlist[i])
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __user *u64_to_uptr(u64 value)
अणु
	अगर (is_compat_task())
		वापस compat_ptr(value);
	अन्यथा
		वापस (व्योम __user *)(अचिन्हित दीर्घ)value;
पूर्ण

/*
 * Start SCLP request
 */
अटल पूर्णांक sclp_ctl_ioctl_sccb(व्योम __user *user_area)
अणु
	काष्ठा sclp_ctl_sccb ctl_sccb;
	काष्ठा sccb_header *sccb;
	अचिन्हित दीर्घ copied;
	पूर्णांक rc;

	अगर (copy_from_user(&ctl_sccb, user_area, माप(ctl_sccb)))
		वापस -EFAULT;
	अगर (!sclp_ctl_cmdw_supported(ctl_sccb.cmdw))
		वापस -EOPNOTSUPP;
	sccb = (व्योम *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!sccb)
		वापस -ENOMEM;
	copied = PAGE_SIZE -
		copy_from_user(sccb, u64_to_uptr(ctl_sccb.sccb), PAGE_SIZE);
	अगर (दुरत्व(काष्ठा sccb_header, length) +
	    माप(sccb->length) > copied || sccb->length > copied) अणु
		rc = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण
	अगर (sccb->length < 8) अणु
		rc = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण
	rc = sclp_sync_request(ctl_sccb.cmdw, sccb);
	अगर (rc)
		जाओ out_मुक्त;
	अगर (copy_to_user(u64_to_uptr(ctl_sccb.sccb), sccb, sccb->length))
		rc = -EFAULT;
out_मुक्त:
	मुक्त_page((अचिन्हित दीर्घ) sccb);
	वापस rc;
पूर्ण

/*
 * SCLP SCCB ioctl function
 */
अटल दीर्घ sclp_ctl_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			   अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp;

	अगर (is_compat_task())
		argp = compat_ptr(arg);
	अन्यथा
		argp = (व्योम __user *) arg;
	चयन (cmd) अणु
	हाल SCLP_CTL_SCCB:
		वापस sclp_ctl_ioctl_sccb(argp);
	शेष: /* unknown ioctl number */
		वापस -ENOTTY;
	पूर्ण
पूर्ण

/*
 * File operations
 */
अटल स्थिर काष्ठा file_operations sclp_ctl_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = nonseekable_खोलो,
	.unlocked_ioctl = sclp_ctl_ioctl,
	.compat_ioctl = sclp_ctl_ioctl,
	.llseek = no_llseek,
पूर्ण;

/*
 * Misc device definition
 */
अटल काष्ठा miscdevice sclp_ctl_device = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = "sclp",
	.fops = &sclp_ctl_fops,
पूर्ण;
builtin_misc_device(sclp_ctl_device);
