<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * devपंचांगpfs - kernel-मुख्यtained पंचांगpfs-based /dev
 *
 * Copyright (C) 2009, Kay Sievers <kay.sievers@vrfy.org>
 *
 * During bootup, beक्रमe any driver core device is रेजिस्टरed,
 * devपंचांगpfs, a पंचांगpfs-based fileप्रणाली is created. Every driver-core
 * device which requests a device node, will add a node in this
 * fileप्रणाली.
 * By शेष, all devices are named after the name of the device,
 * owned by root and have a शेष mode of 0600. Subप्रणालीs can
 * overग_लिखो the शेष setting अगर needed.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/mount.h>
#समावेश <linux/device.h>
#समावेश <linux/genhd.h>
#समावेश <linux/namei.h>
#समावेश <linux/fs.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/ramfs.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/init_syscalls.h>
#समावेश <uapi/linux/mount.h>
#समावेश "base.h"

अटल काष्ठा task_काष्ठा *thपढ़ो;

अटल पूर्णांक __initdata mount_dev = IS_ENABLED(CONFIG_DEVTMPFS_MOUNT);

अटल DEFINE_SPINLOCK(req_lock);

अटल काष्ठा req अणु
	काष्ठा req *next;
	काष्ठा completion करोne;
	पूर्णांक err;
	स्थिर अक्षर *name;
	umode_t mode;	/* 0 => delete */
	kuid_t uid;
	kgid_t gid;
	काष्ठा device *dev;
पूर्ण *requests;

अटल पूर्णांक __init mount_param(अक्षर *str)
अणु
	mount_dev = simple_म_से_अदीर्घ(str, शून्य, 0);
	वापस 1;
पूर्ण
__setup("devtmpfs.mount=", mount_param);

अटल काष्ठा vfsmount *mnt;

अटल काष्ठा dentry *खुला_dev_mount(काष्ठा file_प्रणाली_type *fs_type, पूर्णांक flags,
		      स्थिर अक्षर *dev_name, व्योम *data)
अणु
	काष्ठा super_block *s = mnt->mnt_sb;
	atomic_inc(&s->s_active);
	करोwn_ग_लिखो(&s->s_umount);
	वापस dget(s->s_root);
पूर्ण

अटल काष्ठा file_प्रणाली_type पूर्णांकernal_fs_type = अणु
	.name = "devtmpfs",
#अगर_घोषित CONFIG_TMPFS
	.init_fs_context = shmem_init_fs_context,
	.parameters	= shmem_fs_parameters,
#अन्यथा
	.init_fs_context = ramfs_init_fs_context,
	.parameters	= ramfs_fs_parameters,
#पूर्ण_अगर
	.समाप्त_sb = समाप्त_litter_super,
पूर्ण;

अटल काष्ठा file_प्रणाली_type dev_fs_type = अणु
	.name = "devtmpfs",
	.mount = खुला_dev_mount,
पूर्ण;

#अगर_घोषित CONFIG_BLOCK
अटल अंतरभूत पूर्णांक is_blockdev(काष्ठा device *dev)
अणु
	वापस dev->class == &block_class;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक is_blockdev(काष्ठा device *dev) अणु वापस 0; पूर्ण
#पूर्ण_अगर

अटल पूर्णांक devपंचांगpfs_submit_req(काष्ठा req *req, स्थिर अक्षर *पंचांगp)
अणु
	init_completion(&req->करोne);

	spin_lock(&req_lock);
	req->next = requests;
	requests = req;
	spin_unlock(&req_lock);

	wake_up_process(thपढ़ो);
	रुको_क्रम_completion(&req->करोne);

	kमुक्त(पंचांगp);

	वापस req->err;
पूर्ण

पूर्णांक devपंचांगpfs_create_node(काष्ठा device *dev)
अणु
	स्थिर अक्षर *पंचांगp = शून्य;
	काष्ठा req req;

	अगर (!thपढ़ो)
		वापस 0;

	req.mode = 0;
	req.uid = GLOBAL_ROOT_UID;
	req.gid = GLOBAL_ROOT_GID;
	req.name = device_get_devnode(dev, &req.mode, &req.uid, &req.gid, &पंचांगp);
	अगर (!req.name)
		वापस -ENOMEM;

	अगर (req.mode == 0)
		req.mode = 0600;
	अगर (is_blockdev(dev))
		req.mode |= S_IFBLK;
	अन्यथा
		req.mode |= S_IFCHR;

	req.dev = dev;

	वापस devपंचांगpfs_submit_req(&req, पंचांगp);
पूर्ण

पूर्णांक devपंचांगpfs_delete_node(काष्ठा device *dev)
अणु
	स्थिर अक्षर *पंचांगp = शून्य;
	काष्ठा req req;

	अगर (!thपढ़ो)
		वापस 0;

	req.name = device_get_devnode(dev, शून्य, शून्य, शून्य, &पंचांगp);
	अगर (!req.name)
		वापस -ENOMEM;

	req.mode = 0;
	req.dev = dev;

	वापस devपंचांगpfs_submit_req(&req, पंचांगp);
पूर्ण

अटल पूर्णांक dev_सूची_गढ़ो(स्थिर अक्षर *name, umode_t mode)
अणु
	काष्ठा dentry *dentry;
	काष्ठा path path;
	पूर्णांक err;

	dentry = kern_path_create(AT_FDCWD, name, &path, LOOKUP_सूचीECTORY);
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);

	err = vfs_सूची_गढ़ो(&init_user_ns, d_inode(path.dentry), dentry, mode);
	अगर (!err)
		/* mark as kernel-created inode */
		d_inode(dentry)->i_निजी = &thपढ़ो;
	करोne_path_create(&path, dentry);
	वापस err;
पूर्ण

अटल पूर्णांक create_path(स्थिर अक्षर *nodepath)
अणु
	अक्षर *path;
	अक्षर *s;
	पूर्णांक err = 0;

	/* parent directories करो not exist, create them */
	path = kstrdup(nodepath, GFP_KERNEL);
	अगर (!path)
		वापस -ENOMEM;

	s = path;
	क्रम (;;) अणु
		s = म_अक्षर(s, '/');
		अगर (!s)
			अवरोध;
		s[0] = '\0';
		err = dev_सूची_गढ़ो(path, 0755);
		अगर (err && err != -EEXIST)
			अवरोध;
		s[0] = '/';
		s++;
	पूर्ण
	kमुक्त(path);
	वापस err;
पूर्ण

अटल पूर्णांक handle_create(स्थिर अक्षर *nodename, umode_t mode, kuid_t uid,
			 kgid_t gid, काष्ठा device *dev)
अणु
	काष्ठा dentry *dentry;
	काष्ठा path path;
	पूर्णांक err;

	dentry = kern_path_create(AT_FDCWD, nodename, &path, 0);
	अगर (dentry == ERR_PTR(-ENOENT)) अणु
		create_path(nodename);
		dentry = kern_path_create(AT_FDCWD, nodename, &path, 0);
	पूर्ण
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);

	err = vfs_mknod(&init_user_ns, d_inode(path.dentry), dentry, mode,
			dev->devt);
	अगर (!err) अणु
		काष्ठा iattr newattrs;

		newattrs.ia_mode = mode;
		newattrs.ia_uid = uid;
		newattrs.ia_gid = gid;
		newattrs.ia_valid = ATTR_MODE|ATTR_UID|ATTR_GID;
		inode_lock(d_inode(dentry));
		notअगरy_change(&init_user_ns, dentry, &newattrs, शून्य);
		inode_unlock(d_inode(dentry));

		/* mark as kernel-created inode */
		d_inode(dentry)->i_निजी = &thपढ़ो;
	पूर्ण
	करोne_path_create(&path, dentry);
	वापस err;
पूर्ण

अटल पूर्णांक dev_सूची_हटाओ(स्थिर अक्षर *name)
अणु
	काष्ठा path parent;
	काष्ठा dentry *dentry;
	पूर्णांक err;

	dentry = kern_path_locked(name, &parent);
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);
	अगर (d_really_is_positive(dentry)) अणु
		अगर (d_inode(dentry)->i_निजी == &thपढ़ो)
			err = vfs_सूची_हटाओ(&init_user_ns, d_inode(parent.dentry),
					dentry);
		अन्यथा
			err = -EPERM;
	पूर्ण अन्यथा अणु
		err = -ENOENT;
	पूर्ण
	dput(dentry);
	inode_unlock(d_inode(parent.dentry));
	path_put(&parent);
	वापस err;
पूर्ण

अटल पूर्णांक delete_path(स्थिर अक्षर *nodepath)
अणु
	अक्षर *path;
	पूर्णांक err = 0;

	path = kstrdup(nodepath, GFP_KERNEL);
	अगर (!path)
		वापस -ENOMEM;

	क्रम (;;) अणु
		अक्षर *base;

		base = म_खोजप(path, '/');
		अगर (!base)
			अवरोध;
		base[0] = '\0';
		err = dev_सूची_हटाओ(path);
		अगर (err)
			अवरोध;
	पूर्ण

	kमुक्त(path);
	वापस err;
पूर्ण

अटल पूर्णांक dev_mynode(काष्ठा device *dev, काष्ठा inode *inode, काष्ठा kstat *stat)
अणु
	/* did we create it */
	अगर (inode->i_निजी != &thपढ़ो)
		वापस 0;

	/* करोes the dev_t match */
	अगर (is_blockdev(dev)) अणु
		अगर (!S_ISBLK(stat->mode))
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर (!S_ISCHR(stat->mode))
			वापस 0;
	पूर्ण
	अगर (stat->rdev != dev->devt)
		वापस 0;

	/* ours */
	वापस 1;
पूर्ण

अटल पूर्णांक handle_हटाओ(स्थिर अक्षर *nodename, काष्ठा device *dev)
अणु
	काष्ठा path parent;
	काष्ठा dentry *dentry;
	पूर्णांक deleted = 0;
	पूर्णांक err;

	dentry = kern_path_locked(nodename, &parent);
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);

	अगर (d_really_is_positive(dentry)) अणु
		काष्ठा kstat stat;
		काष्ठा path p = अणु.mnt = parent.mnt, .dentry = dentryपूर्ण;
		err = vfs_getattr(&p, &stat, STATX_TYPE | STATX_MODE,
				  AT_STATX_SYNC_AS_STAT);
		अगर (!err && dev_mynode(dev, d_inode(dentry), &stat)) अणु
			काष्ठा iattr newattrs;
			/*
			 * beक्रमe unlinking this node, reset permissions
			 * of possible references like hardlinks
			 */
			newattrs.ia_uid = GLOBAL_ROOT_UID;
			newattrs.ia_gid = GLOBAL_ROOT_GID;
			newattrs.ia_mode = stat.mode & ~0777;
			newattrs.ia_valid =
				ATTR_UID|ATTR_GID|ATTR_MODE;
			inode_lock(d_inode(dentry));
			notअगरy_change(&init_user_ns, dentry, &newattrs, शून्य);
			inode_unlock(d_inode(dentry));
			err = vfs_unlink(&init_user_ns, d_inode(parent.dentry),
					 dentry, शून्य);
			अगर (!err || err == -ENOENT)
				deleted = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = -ENOENT;
	पूर्ण
	dput(dentry);
	inode_unlock(d_inode(parent.dentry));

	path_put(&parent);
	अगर (deleted && म_अक्षर(nodename, '/'))
		delete_path(nodename);
	वापस err;
पूर्ण

/*
 * If configured, or requested by the commandline, devपंचांगpfs will be
 * स्वतः-mounted after the kernel mounted the root fileप्रणाली.
 */
पूर्णांक __init devपंचांगpfs_mount(व्योम)
अणु
	पूर्णांक err;

	अगर (!mount_dev)
		वापस 0;

	अगर (!thपढ़ो)
		वापस 0;

	err = init_mount("devtmpfs", "dev", "devtmpfs", MS_SILENT, शून्य);
	अगर (err)
		prपूर्णांकk(KERN_INFO "devtmpfs: error mounting %i\n", err);
	अन्यथा
		prपूर्णांकk(KERN_INFO "devtmpfs: mounted\n");
	वापस err;
पूर्ण

अटल __initdata DECLARE_COMPLETION(setup_करोne);

अटल पूर्णांक handle(स्थिर अक्षर *name, umode_t mode, kuid_t uid, kgid_t gid,
		  काष्ठा device *dev)
अणु
	अगर (mode)
		वापस handle_create(name, mode, uid, gid, dev);
	अन्यथा
		वापस handle_हटाओ(name, dev);
पूर्ण

अटल व्योम __noवापस devपंचांगpfs_work_loop(व्योम)
अणु
	जबतक (1) अणु
		spin_lock(&req_lock);
		जबतक (requests) अणु
			काष्ठा req *req = requests;
			requests = शून्य;
			spin_unlock(&req_lock);
			जबतक (req) अणु
				काष्ठा req *next = req->next;
				req->err = handle(req->name, req->mode,
						  req->uid, req->gid, req->dev);
				complete(&req->करोne);
				req = next;
			पूर्ण
			spin_lock(&req_lock);
		पूर्ण
		__set_current_state(TASK_INTERRUPTIBLE);
		spin_unlock(&req_lock);
		schedule();
	पूर्ण
पूर्ण

अटल noअंतरभूत पूर्णांक __init devपंचांगpfs_setup(व्योम *p)
अणु
	पूर्णांक err;

	err = ksys_unshare(CLONE_NEWNS);
	अगर (err)
		जाओ out;
	err = init_mount("devtmpfs", "/", "devtmpfs", MS_SILENT, शून्य);
	अगर (err)
		जाओ out;
	init_स_बदलो("/.."); /* will traverse पूर्णांकo overmounted root */
	init_chroot(".");
out:
	*(पूर्णांक *)p = err;
	वापस err;
पूर्ण

/*
 * The __ref is because devपंचांगpfs_setup needs to be __init क्रम the routines it
 * calls.  That call is करोne जबतक devपंचांगpfs_init, which is marked __init,
 * synchronously रुकोs क्रम it to complete.
 */
अटल पूर्णांक __ref devपंचांगpfsd(व्योम *p)
अणु
	पूर्णांक err = devपंचांगpfs_setup(p);

	complete(&setup_करोne);
	अगर (err)
		वापस err;
	devपंचांगpfs_work_loop();
	वापस 0;
पूर्ण

/*
 * Create devपंचांगpfs instance, driver-core devices will add their device
 * nodes here.
 */
पूर्णांक __init devपंचांगpfs_init(व्योम)
अणु
	अक्षर opts[] = "mode=0755";
	पूर्णांक err;

	mnt = vfs_kern_mount(&पूर्णांकernal_fs_type, 0, "devtmpfs", opts);
	अगर (IS_ERR(mnt)) अणु
		prपूर्णांकk(KERN_ERR "devtmpfs: unable to create devtmpfs %ld\n",
				PTR_ERR(mnt));
		वापस PTR_ERR(mnt);
	पूर्ण
	err = रेजिस्टर_fileप्रणाली(&dev_fs_type);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "devtmpfs: unable to register devtmpfs "
		       "type %i\n", err);
		वापस err;
	पूर्ण

	thपढ़ो = kthपढ़ो_run(devपंचांगpfsd, &err, "kdevtmpfs");
	अगर (!IS_ERR(thपढ़ो)) अणु
		रुको_क्रम_completion(&setup_करोne);
	पूर्ण अन्यथा अणु
		err = PTR_ERR(thपढ़ो);
		thपढ़ो = शून्य;
	पूर्ण

	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "devtmpfs: unable to create devtmpfs %i\n", err);
		unरेजिस्टर_fileप्रणाली(&dev_fs_type);
		वापस err;
	पूर्ण

	prपूर्णांकk(KERN_INFO "devtmpfs: initialized\n");
	वापस 0;
पूर्ण
