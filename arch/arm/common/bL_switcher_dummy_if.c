<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/common/bL_चयनer_dummy_अगर.c -- b.L चयनer dummy पूर्णांकerface
 *
 * Created by:	Nicolas Pitre, November 2012
 * Copyright:	(C) 2012-2013  Linaro Limited
 *
 * Dummy पूर्णांकerface to user space क्रम debugging purpose only.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/bL_चयनer.h>

अटल sमाप_प्रकार bL_चयनer_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			माप_प्रकार len, loff_t *pos)
अणु
	अचिन्हित अक्षर val[3];
	अचिन्हित पूर्णांक cpu, cluster;
	पूर्णांक ret;

	pr_debug("%s\n", __func__);

	अगर (len < 3)
		वापस -EINVAL;

	अगर (copy_from_user(val, buf, 3))
		वापस -EFAULT;

	/* क्रमmat: <cpu#>,<cluster#> */
	अगर (val[0] < '0' || val[0] > '9' ||
	    val[1] != ',' ||
	    val[2] < '0' || val[2] > '1')
		वापस -EINVAL;

	cpu = val[0] - '0';
	cluster = val[2] - '0';
	ret = bL_चयन_request(cpu, cluster);

	वापस ret ? : len;
पूर्ण

अटल स्थिर काष्ठा file_operations bL_चयनer_fops = अणु
	.ग_लिखो		= bL_चयनer_ग_लिखो,
	.owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा miscdevice bL_चयनer_device = अणु
	MISC_DYNAMIC_MINOR,
	"b.L_switcher",
	&bL_चयनer_fops
पूर्ण;
module_misc_device(bL_चयनer_device);

MODULE_AUTHOR("Nicolas Pitre <nico@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("big.LITTLE switcher dummy user interface");
