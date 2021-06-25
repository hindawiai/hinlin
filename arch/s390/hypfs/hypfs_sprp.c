<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Hypervisor fileप्रणाली क्रम Linux on s390.
 *    Set Partition-Resource Parameter पूर्णांकerface.
 *
 *    Copyright IBM Corp. 2013
 *    Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#समावेश <linux/compat.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gfp.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/diag.h>
#समावेश <यंत्र/sclp.h>
#समावेश "hypfs.h"

#घोषणा DIAG304_SET_WEIGHTS	0
#घोषणा DIAG304_QUERY_PRP	1
#घोषणा DIAG304_SET_CAPPING	2

#घोषणा DIAG304_CMD_MAX		2

अटल अंतरभूत अचिन्हित दीर्घ __hypfs_sprp_diag304(व्योम *data, अचिन्हित दीर्घ cmd)
अणु
	रेजिस्टर अचिन्हित दीर्घ _data यंत्र("2") = (अचिन्हित दीर्घ) data;
	रेजिस्टर अचिन्हित दीर्घ _rc यंत्र("3");
	रेजिस्टर अचिन्हित दीर्घ _cmd यंत्र("4") = cmd;

	यंत्र अस्थिर("diag %1,%2,0x304\n"
		     : "=d" (_rc) : "d" (_data), "d" (_cmd) : "memory");

	वापस _rc;
पूर्ण

अटल अचिन्हित दीर्घ hypfs_sprp_diag304(व्योम *data, अचिन्हित दीर्घ cmd)
अणु
	diag_stat_inc(DIAG_STAT_X304);
	वापस __hypfs_sprp_diag304(data, cmd);
पूर्ण

अटल व्योम hypfs_sprp_मुक्त(स्थिर व्योम *data)
अणु
	मुक्त_page((अचिन्हित दीर्घ) data);
पूर्ण

अटल पूर्णांक hypfs_sprp_create(व्योम **data_ptr, व्योम **मुक्त_ptr, माप_प्रकार *size)
अणु
	अचिन्हित दीर्घ rc;
	व्योम *data;

	data = (व्योम *) get_zeroed_page(GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	rc = hypfs_sprp_diag304(data, DIAG304_QUERY_PRP);
	अगर (rc != 1) अणु
		*data_ptr = *मुक्त_ptr = शून्य;
		*size = 0;
		मुक्त_page((अचिन्हित दीर्घ) data);
		वापस -EIO;
	पूर्ण
	*data_ptr = *मुक्त_ptr = data;
	*size = PAGE_SIZE;
	वापस 0;
पूर्ण

अटल पूर्णांक __hypfs_sprp_ioctl(व्योम __user *user_area)
अणु
	काष्ठा hypfs_diag304 *diag304;
	अचिन्हित दीर्घ cmd;
	व्योम __user *udata;
	व्योम *data;
	पूर्णांक rc;

	rc = -ENOMEM;
	data = (व्योम *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	diag304 = kzalloc(माप(*diag304), GFP_KERNEL);
	अगर (!data || !diag304)
		जाओ out;

	rc = -EFAULT;
	अगर (copy_from_user(diag304, user_area, माप(*diag304)))
		जाओ out;
	rc = -EINVAL;
	अगर ((diag304->args[0] >> 8) != 0 || diag304->args[1] > DIAG304_CMD_MAX)
		जाओ out;

	rc = -EFAULT;
	udata = (व्योम __user *)(अचिन्हित दीर्घ) diag304->data;
	अगर (diag304->args[1] == DIAG304_SET_WEIGHTS ||
	    diag304->args[1] == DIAG304_SET_CAPPING)
		अगर (copy_from_user(data, udata, PAGE_SIZE))
			जाओ out;

	cmd = *(अचिन्हित दीर्घ *) &diag304->args[0];
	diag304->rc = hypfs_sprp_diag304(data, cmd);

	अगर (diag304->args[1] == DIAG304_QUERY_PRP)
		अगर (copy_to_user(udata, data, PAGE_SIZE)) अणु
			rc = -EFAULT;
			जाओ out;
		पूर्ण

	rc = copy_to_user(user_area, diag304, माप(*diag304)) ? -EFAULT : 0;
out:
	kमुक्त(diag304);
	मुक्त_page((अचिन्हित दीर्घ) data);
	वापस rc;
पूर्ण

अटल दीर्घ hypfs_sprp_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;
	अगर (is_compat_task())
		argp = compat_ptr(arg);
	अन्यथा
		argp = (व्योम __user *) arg;
	चयन (cmd) अणु
	हाल HYPFS_DIAG304:
		वापस __hypfs_sprp_ioctl(argp);
	शेष: /* unknown ioctl number */
		वापस -ENOTTY;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा hypfs_dbfs_file hypfs_sprp_file = अणु
	.name		= "diag_304",
	.data_create	= hypfs_sprp_create,
	.data_मुक्त	= hypfs_sprp_मुक्त,
	.unlocked_ioctl = hypfs_sprp_ioctl,
पूर्ण;

व्योम hypfs_sprp_init(व्योम)
अणु
	अगर (!sclp.has_sprp)
		वापस;
	hypfs_dbfs_create_file(&hypfs_sprp_file);
पूर्ण

व्योम hypfs_sprp_निकास(व्योम)
अणु
	अगर (!sclp.has_sprp)
		वापस;
	hypfs_dbfs_हटाओ_file(&hypfs_sprp_file);
पूर्ण
