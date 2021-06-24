<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/export.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/slab.h>

#समावेश <linux/uaccess.h>

#समावेश "spufs.h"

/**
 * sys_spu_run - run code loaded पूर्णांकo an SPU
 *
 * @unpc:    next program counter क्रम the SPU
 * @ustatus: status of the SPU
 *
 * This प्रणाली call transfers the control of execution of a
 * user space thपढ़ो to an SPU. It will वापस when the
 * SPU has finished executing or when it hits an error
 * condition and it will be पूर्णांकerrupted अगर a संकेत needs
 * to be delivered to a handler in user space.
 *
 * The next program counter is set to the passed value
 * beक्रमe the SPU starts fetching code and the user space
 * poपूर्णांकer माला_लो updated with the new value when वापसing
 * from kernel space.
 *
 * The status value वापसed from spu_run reflects the
 * value of the spu_status रेजिस्टर after the SPU has stopped.
 *
 */
अटल दीर्घ करो_spu_run(काष्ठा file *filp,
			__u32 __user *unpc,
			__u32 __user *ustatus)
अणु
	दीर्घ ret;
	काष्ठा spufs_inode_info *i;
	u32 npc, status;

	ret = -EFAULT;
	अगर (get_user(npc, unpc))
		जाओ out;

	/* check अगर this file was created by spu_create */
	ret = -EINVAL;
	अगर (filp->f_op != &spufs_context_fops)
		जाओ out;

	i = SPUFS_I(file_inode(filp));
	ret = spufs_run_spu(i->i_ctx, &npc, &status);

	अगर (put_user(npc, unpc))
		ret = -EFAULT;

	अगर (ustatus && put_user(status, ustatus))
		ret = -EFAULT;
out:
	वापस ret;
पूर्ण

अटल दीर्घ करो_spu_create(स्थिर अक्षर __user *pathname, अचिन्हित पूर्णांक flags,
		umode_t mode, काष्ठा file *neighbor)
अणु
	काष्ठा path path;
	काष्ठा dentry *dentry;
	पूर्णांक ret;

	dentry = user_path_create(AT_FDCWD, pathname, &path, LOOKUP_सूचीECTORY);
	ret = PTR_ERR(dentry);
	अगर (!IS_ERR(dentry)) अणु
		ret = spufs_create(&path, dentry, flags, mode, neighbor);
		करोne_path_create(&path, dentry);
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा spufs_calls spufs_calls = अणु
	.create_thपढ़ो = करो_spu_create,
	.spu_run = करो_spu_run,
	.notअगरy_spus_active = करो_notअगरy_spus_active,
	.owner = THIS_MODULE,
#अगर_घोषित CONFIG_COREDUMP
	.coredump_extra_notes_size = spufs_coredump_extra_notes_size,
	.coredump_extra_notes_ग_लिखो = spufs_coredump_extra_notes_ग_लिखो,
#पूर्ण_अगर
पूर्ण;
