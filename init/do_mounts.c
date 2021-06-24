<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/fd.h>
#समावेश <linux/tty.h>
#समावेश <linux/suspend.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/security.h>
#समावेश <linux/delay.h>
#समावेश <linux/genhd.h>
#समावेश <linux/mount.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/initrd.h>
#समावेश <linux/async.h>
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/slab.h>
#समावेश <linux/ramfs.h>
#समावेश <linux/shmem_fs.h>

#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_fs_sb.h>
#समावेश <linux/nfs_mount.h>
#समावेश <linux/raid/detect.h>
#समावेश <uapi/linux/mount.h>

#समावेश "do_mounts.h"

पूर्णांक root_mountflags = MS_RDONLY | MS_SILENT;
अटल अक्षर * __initdata root_device_name;
अटल अक्षर __initdata saved_root_name[64];
अटल पूर्णांक root_रुको;

dev_t ROOT_DEV;

अटल पूर्णांक __init load_ramdisk(अक्षर *str)
अणु
	pr_warn("ignoring the deprecated load_ramdisk= option\n");
	वापस 1;
पूर्ण
__setup("load_ramdisk=", load_ramdisk);

अटल पूर्णांक __init पढ़ोonly(अक्षर *str)
अणु
	अगर (*str)
		वापस 0;
	root_mountflags |= MS_RDONLY;
	वापस 1;
पूर्ण

अटल पूर्णांक __init पढ़ोग_लिखो(अक्षर *str)
अणु
	अगर (*str)
		वापस 0;
	root_mountflags &= ~MS_RDONLY;
	वापस 1;
पूर्ण

__setup("ro", पढ़ोonly);
__setup("rw", पढ़ोग_लिखो);

#अगर_घोषित CONFIG_BLOCK
काष्ठा uuidcmp अणु
	स्थिर अक्षर *uuid;
	पूर्णांक len;
पूर्ण;

/**
 * match_dev_by_uuid - callback क्रम finding a partition using its uuid
 * @dev:	device passed in by the caller
 * @data:	opaque poपूर्णांकer to the desired काष्ठा uuidcmp to match
 *
 * Returns 1 अगर the device matches, and 0 otherwise.
 */
अटल पूर्णांक match_dev_by_uuid(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा block_device *bdev = dev_to_bdev(dev);
	स्थिर काष्ठा uuidcmp *cmp = data;

	अगर (!bdev->bd_meta_info ||
	    strnहालcmp(cmp->uuid, bdev->bd_meta_info->uuid, cmp->len))
		वापस 0;
	वापस 1;
पूर्ण

/**
 * devt_from_partuuid - looks up the dev_t of a partition by its UUID
 * @uuid_str:	अक्षर array containing ascii UUID
 *
 * The function will वापस the first partition which contains a matching
 * UUID value in its partition_meta_info काष्ठा.  This करोes not search
 * by fileप्रणाली UUIDs.
 *
 * If @uuid_str is followed by a "/PARTNROFF=%d", then the number will be
 * extracted and used as an offset from the partition identअगरied by the UUID.
 *
 * Returns the matching dev_t on success or 0 on failure.
 */
अटल dev_t devt_from_partuuid(स्थिर अक्षर *uuid_str)
अणु
	काष्ठा uuidcmp cmp;
	काष्ठा device *dev = शून्य;
	dev_t devt = 0;
	पूर्णांक offset = 0;
	अक्षर *slash;

	cmp.uuid = uuid_str;

	slash = म_अक्षर(uuid_str, '/');
	/* Check क्रम optional partition number offset attributes. */
	अगर (slash) अणु
		अक्षर c = 0;

		/* Explicitly fail on poor PARTUUID syntax. */
		अगर (माला_पूछो(slash + 1, "PARTNROFF=%d%c", &offset, &c) != 1)
			जाओ clear_root_रुको;
		cmp.len = slash - uuid_str;
	पूर्ण अन्यथा अणु
		cmp.len = म_माप(uuid_str);
	पूर्ण

	अगर (!cmp.len)
		जाओ clear_root_रुको;

	dev = class_find_device(&block_class, शून्य, &cmp, &match_dev_by_uuid);
	अगर (!dev)
		वापस 0;

	अगर (offset) अणु
		/*
		 * Attempt to find the requested partition by adding an offset
		 * to the partition number found by UUID.
		 */
		काष्ठा block_device *part;

		part = bdget_disk(dev_to_disk(dev),
				  dev_to_bdev(dev)->bd_partno + offset);
		अगर (part) अणु
			devt = part->bd_dev;
			bdput(part);
		पूर्ण
	पूर्ण अन्यथा अणु
		devt = dev->devt;
	पूर्ण

	put_device(dev);
	वापस devt;

clear_root_रुको:
	pr_err("VFS: PARTUUID= is invalid.\n"
	       "Expected PARTUUID=<valid-uuid-id>[/PARTNROFF=%%d]\n");
	अगर (root_रुको)
		pr_err("Disabling rootwait; root= is invalid.\n");
	root_रुको = 0;
	वापस 0;
पूर्ण

/**
 * match_dev_by_label - callback क्रम finding a partition using its label
 * @dev:	device passed in by the caller
 * @data:	opaque poपूर्णांकer to the label to match
 *
 * Returns 1 अगर the device matches, and 0 otherwise.
 */
अटल पूर्णांक match_dev_by_label(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा block_device *bdev = dev_to_bdev(dev);
	स्थिर अक्षर *label = data;

	अगर (!bdev->bd_meta_info || म_भेद(label, bdev->bd_meta_info->volname))
		वापस 0;
	वापस 1;
पूर्ण

अटल dev_t devt_from_partlabel(स्थिर अक्षर *label)
अणु
	काष्ठा device *dev;
	dev_t devt = 0;

	dev = class_find_device(&block_class, शून्य, label, &match_dev_by_label);
	अगर (dev) अणु
		devt = dev->devt;
		put_device(dev);
	पूर्ण

	वापस devt;
पूर्ण

अटल dev_t devt_from_devname(स्थिर अक्षर *name)
अणु
	dev_t devt = 0;
	पूर्णांक part;
	अक्षर s[32];
	अक्षर *p;

	अगर (म_माप(name) > 31)
		वापस 0;
	म_नकल(s, name);
	क्रम (p = s; *p; p++) अणु
		अगर (*p == '/')
			*p = '!';
	पूर्ण

	devt = blk_lookup_devt(s, 0);
	अगर (devt)
		वापस devt;

	/*
	 * Try non-existent, but valid partition, which may only exist after
	 * खोलोing the device, like partitioned md devices.
	 */
	जबतक (p > s && है_अंक(p[-1]))
		p--;
	अगर (p == s || !*p || *p == '0')
		वापस 0;

	/* try disk name without <part number> */
	part = simple_म_से_अदीर्घ(p, शून्य, 10);
	*p = '\0';
	devt = blk_lookup_devt(s, part);
	अगर (devt)
		वापस devt;

	/* try disk name without p<part number> */
	अगर (p < s + 2 || !है_अंक(p[-2]) || p[-1] != 'p')
		वापस 0;
	p[-1] = '\0';
	वापस blk_lookup_devt(s, part);
पूर्ण
#पूर्ण_अगर /* CONFIG_BLOCK */

अटल dev_t devt_from_devnum(स्थिर अक्षर *name)
अणु
	अचिन्हित maj, min, offset;
	dev_t devt = 0;
	अक्षर *p, dummy;

	अगर (माला_पूछो(name, "%u:%u%c", &maj, &min, &dummy) == 2 ||
	    माला_पूछो(name, "%u:%u:%u:%c", &maj, &min, &offset, &dummy) == 3) अणु
		devt = MKDEV(maj, min);
		अगर (maj != MAJOR(devt) || min != MINOR(devt))
			वापस 0;
	पूर्ण अन्यथा अणु
		devt = new_decode_dev(simple_म_से_अदीर्घ(name, &p, 16));
		अगर (*p)
			वापस 0;
	पूर्ण

	वापस devt;
पूर्ण

/*
 *	Convert a name पूर्णांकo device number.  We accept the following variants:
 *
 *	1) <hex_major><hex_minor> device number in hexadecimal represents itself
 *         no leading 0x, क्रम example b302.
 *	2) /dev/nfs represents Root_NFS (0xff)
 *	3) /dev/<disk_name> represents the device number of disk
 *	4) /dev/<disk_name><decimal> represents the device number
 *         of partition - device number of disk plus the partition number
 *	5) /dev/<disk_name>p<decimal> - same as the above, that क्रमm is
 *	   used when disk name of partitioned disk ends on a digit.
 *	6) PARTUUID=00112233-4455-6677-8899-AABBCCDDEEFF representing the
 *	   unique id of a partition अगर the partition table provides it.
 *	   The UUID may be either an EFI/GPT UUID, or refer to an MSDOS
 *	   partition using the क्रमmat SSSSSSSS-PP, where SSSSSSSS is a zero-
 *	   filled hex representation of the 32-bit "NT disk signature", and PP
 *	   is a zero-filled hex representation of the 1-based partition number.
 *	7) PARTUUID=<UUID>/PARTNROFF=<पूर्णांक> to select a partition in relation to
 *	   a partition with a known unique id.
 *	8) <major>:<minor> major and minor number of the device separated by
 *	   a colon.
 *	9) PARTLABEL=<name> with name being the GPT partition label.
 *	   MSDOS partitions करो not support labels!
 *	10) /dev/cअगरs represents Root_CIFS (0xfe)
 *
 *	If name करोesn't have fall पूर्णांकo the categories above, we वापस (0,0).
 *	block_class is used to check अगर something is a disk name. If the disk
 *	name contains slashes, the device name has them replaced with
 *	bangs.
 */
dev_t name_to_dev_t(स्थिर अक्षर *name)
अणु
	अगर (म_भेद(name, "/dev/nfs") == 0)
		वापस Root_NFS;
	अगर (म_भेद(name, "/dev/cifs") == 0)
		वापस Root_CIFS;
	अगर (म_भेद(name, "/dev/ram") == 0)
		वापस Root_RAM0;
#अगर_घोषित CONFIG_BLOCK
	अगर (म_भेदन(name, "PARTUUID=", 9) == 0)
		वापस devt_from_partuuid(name + 9);
	अगर (म_भेदन(name, "PARTLABEL=", 10) == 0)
		वापस devt_from_partlabel(name + 10);
	अगर (म_भेदन(name, "/dev/", 5) == 0)
		वापस devt_from_devname(name + 5);
#पूर्ण_अगर
	वापस devt_from_devnum(name);
पूर्ण
EXPORT_SYMBOL_GPL(name_to_dev_t);

अटल पूर्णांक __init root_dev_setup(अक्षर *line)
अणु
	strlcpy(saved_root_name, line, माप(saved_root_name));
	वापस 1;
पूर्ण

__setup("root=", root_dev_setup);

अटल पूर्णांक __init rootरुको_setup(अक्षर *str)
अणु
	अगर (*str)
		वापस 0;
	root_रुको = 1;
	वापस 1;
पूर्ण

__setup("rootwait", rootरुको_setup);

अटल अक्षर * __initdata root_mount_data;
अटल पूर्णांक __init root_data_setup(अक्षर *str)
अणु
	root_mount_data = str;
	वापस 1;
पूर्ण

अटल अक्षर * __initdata root_fs_names;
अटल पूर्णांक __init fs_names_setup(अक्षर *str)
अणु
	root_fs_names = str;
	वापस 1;
पूर्ण

अटल अचिन्हित पूर्णांक __initdata root_delay;
अटल पूर्णांक __init root_delay_setup(अक्षर *str)
अणु
	root_delay = simple_म_से_अदीर्घ(str, शून्य, 0);
	वापस 1;
पूर्ण

__setup("rootflags=", root_data_setup);
__setup("rootfstype=", fs_names_setup);
__setup("rootdelay=", root_delay_setup);

अटल व्योम __init get_fs_names(अक्षर *page)
अणु
	अक्षर *s = page;

	अगर (root_fs_names) अणु
		म_नकल(page, root_fs_names);
		जबतक (*s++) अणु
			अगर (s[-1] == ',')
				s[-1] = '\0';
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक len = get_fileप्रणाली_list(page);
		अक्षर *p, *next;

		page[len] = '\0';
		क्रम (p = page-1; p; p = next) अणु
			next = म_अक्षर(++p, '\n');
			अगर (*p++ != '\t')
				जारी;
			जबतक ((*s++ = *p++) != '\n')
				;
			s[-1] = '\0';
		पूर्ण
	पूर्ण
	*s = '\0';
पूर्ण

अटल पूर्णांक __init करो_mount_root(स्थिर अक्षर *name, स्थिर अक्षर *fs,
				 स्थिर पूर्णांक flags, स्थिर व्योम *data)
अणु
	काष्ठा super_block *s;
	काष्ठा page *p = शून्य;
	अक्षर *data_page = शून्य;
	पूर्णांक ret;

	अगर (data) अणु
		/* init_mount() requires a full page as fअगरth argument */
		p = alloc_page(GFP_KERNEL);
		अगर (!p)
			वापस -ENOMEM;
		data_page = page_address(p);
		/* zero-pad. init_mount() will make sure it's terminated */
		म_नकलन(data_page, data, PAGE_SIZE);
	पूर्ण

	ret = init_mount(name, "/root", fs, flags, data_page);
	अगर (ret)
		जाओ out;

	init_स_बदलो("/root");
	s = current->fs->pwd.dentry->d_sb;
	ROOT_DEV = s->s_dev;
	prपूर्णांकk(KERN_INFO
	       "VFS: Mounted root (%s filesystem)%s on device %u:%u.\n",
	       s->s_type->name,
	       sb_rकरोnly(s) ? " readonly" : "",
	       MAJOR(ROOT_DEV), MINOR(ROOT_DEV));

out:
	अगर (p)
		put_page(p);
	वापस ret;
पूर्ण

व्योम __init mount_block_root(अक्षर *name, पूर्णांक flags)
अणु
	काष्ठा page *page = alloc_page(GFP_KERNEL);
	अक्षर *fs_names = page_address(page);
	अक्षर *p;
	अक्षर b[BDEVNAME_SIZE];

	scnम_लिखो(b, BDEVNAME_SIZE, "unknown-block(%u,%u)",
		  MAJOR(ROOT_DEV), MINOR(ROOT_DEV));
	get_fs_names(fs_names);
retry:
	क्रम (p = fs_names; *p; p += म_माप(p)+1) अणु
		पूर्णांक err = करो_mount_root(name, p, flags, root_mount_data);
		चयन (err) अणु
			हाल 0:
				जाओ out;
			हाल -EACCES:
			हाल -EINVAL:
				जारी;
		पूर्ण
	        /*
		 * Allow the user to distinguish between failed sys_खोलो
		 * and bad superblock on root device.
		 * and give them a list of the available devices
		 */
		prपूर्णांकk("VFS: Cannot open root device \"%s\" or %s: error %d\n",
				root_device_name, b, err);
		prपूर्णांकk("Please append a correct \"root=\" boot option; here are the available partitions:\n");

		prपूर्णांकk_all_partitions();
#अगर_घोषित CONFIG_DEBUG_BLOCK_EXT_DEVT
		prपूर्णांकk("DEBUG_BLOCK_EXT_DEVT is enabled, you need to specify "
		       "explicit textual name for \"root=\" boot option.\n");
#पूर्ण_अगर
		panic("VFS: Unable to mount root fs on %s", b);
	पूर्ण
	अगर (!(flags & SB_RDONLY)) अणु
		flags |= SB_RDONLY;
		जाओ retry;
	पूर्ण

	prपूर्णांकk("List of all partitions:\n");
	prपूर्णांकk_all_partitions();
	prपूर्णांकk("No filesystem could mount root, tried: ");
	क्रम (p = fs_names; *p; p += म_माप(p)+1)
		prपूर्णांकk(" %s", p);
	prपूर्णांकk("\n");
	panic("VFS: Unable to mount root fs on %s", b);
out:
	put_page(page);
पूर्ण
 
#अगर_घोषित CONFIG_ROOT_NFS

#घोषणा NFSROOT_TIMEOUT_MIN	5
#घोषणा NFSROOT_TIMEOUT_MAX	30
#घोषणा NFSROOT_RETRY_MAX	5

अटल पूर्णांक __init mount_nfs_root(व्योम)
अणु
	अक्षर *root_dev, *root_data;
	अचिन्हित पूर्णांक समयout;
	पूर्णांक try, err;

	err = nfs_root_data(&root_dev, &root_data);
	अगर (err != 0)
		वापस 0;

	/*
	 * The server or network may not be पढ़ोy, so try several
	 * बार.  Stop after a few tries in हाल the client wants
	 * to fall back to other boot methods.
	 */
	समयout = NFSROOT_TIMEOUT_MIN;
	क्रम (try = 1; ; try++) अणु
		err = करो_mount_root(root_dev, "nfs",
					root_mountflags, root_data);
		अगर (err == 0)
			वापस 1;
		अगर (try > NFSROOT_RETRY_MAX)
			अवरोध;

		/* Wait, in हाल the server refused us immediately */
		ssleep(समयout);
		समयout <<= 1;
		अगर (समयout > NFSROOT_TIMEOUT_MAX)
			समयout = NFSROOT_TIMEOUT_MAX;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CIFS_ROOT

बाह्य पूर्णांक cअगरs_root_data(अक्षर **dev, अक्षर **opts);

#घोषणा CIFSROOT_TIMEOUT_MIN	5
#घोषणा CIFSROOT_TIMEOUT_MAX	30
#घोषणा CIFSROOT_RETRY_MAX	5

अटल पूर्णांक __init mount_cअगरs_root(व्योम)
अणु
	अक्षर *root_dev, *root_data;
	अचिन्हित पूर्णांक समयout;
	पूर्णांक try, err;

	err = cअगरs_root_data(&root_dev, &root_data);
	अगर (err != 0)
		वापस 0;

	समयout = CIFSROOT_TIMEOUT_MIN;
	क्रम (try = 1; ; try++) अणु
		err = करो_mount_root(root_dev, "cifs", root_mountflags,
				    root_data);
		अगर (err == 0)
			वापस 1;
		अगर (try > CIFSROOT_RETRY_MAX)
			अवरोध;

		ssleep(समयout);
		समयout <<= 1;
		अगर (समयout > CIFSROOT_TIMEOUT_MAX)
			समयout = CIFSROOT_TIMEOUT_MAX;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम __init mount_root(व्योम)
अणु
#अगर_घोषित CONFIG_ROOT_NFS
	अगर (ROOT_DEV == Root_NFS) अणु
		अगर (!mount_nfs_root())
			prपूर्णांकk(KERN_ERR "VFS: Unable to mount root fs via NFS.\n");
		वापस;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_CIFS_ROOT
	अगर (ROOT_DEV == Root_CIFS) अणु
		अगर (!mount_cअगरs_root())
			prपूर्णांकk(KERN_ERR "VFS: Unable to mount root fs via SMB.\n");
		वापस;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_BLOCK
	अणु
		पूर्णांक err = create_dev("/dev/root", ROOT_DEV);

		अगर (err < 0)
			pr_emerg("Failed to create /dev/root: %d\n", err);
		mount_block_root("/dev/root", root_mountflags);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Prepare the namespace - decide what/where to mount, load ramdisks, etc.
 */
व्योम __init prepare_namespace(व्योम)
अणु
	अगर (root_delay) अणु
		prपूर्णांकk(KERN_INFO "Waiting %d sec before mounting root device...\n",
		       root_delay);
		ssleep(root_delay);
	पूर्ण

	/*
	 * रुको क्रम the known devices to complete their probing
	 *
	 * Note: this is a potential source of दीर्घ boot delays.
	 * For example, it is not atypical to रुको 5 seconds here
	 * क्रम the touchpad of a laptop to initialize.
	 */
	रुको_क्रम_device_probe();

	md_run_setup();

	अगर (saved_root_name[0]) अणु
		root_device_name = saved_root_name;
		अगर (!म_भेदन(root_device_name, "mtd", 3) ||
		    !म_भेदन(root_device_name, "ubi", 3)) अणु
			mount_block_root(root_device_name, root_mountflags);
			जाओ out;
		पूर्ण
		ROOT_DEV = name_to_dev_t(root_device_name);
		अगर (म_भेदन(root_device_name, "/dev/", 5) == 0)
			root_device_name += 5;
	पूर्ण

	अगर (initrd_load())
		जाओ out;

	/* रुको क्रम any asynchronous scanning to complete */
	अगर ((ROOT_DEV == 0) && root_रुको) अणु
		prपूर्णांकk(KERN_INFO "Waiting for root device %s...\n",
			saved_root_name);
		जबतक (driver_probe_करोne() != 0 ||
			(ROOT_DEV = name_to_dev_t(saved_root_name)) == 0)
			msleep(5);
		async_synchronize_full();
	पूर्ण

	mount_root();
out:
	devपंचांगpfs_mount();
	init_mount(".", "/", शून्य, MS_MOVE, शून्य);
	init_chroot(".");
पूर्ण

अटल bool is_पंचांगpfs;
अटल पूर्णांक rootfs_init_fs_context(काष्ठा fs_context *fc)
अणु
	अगर (IS_ENABLED(CONFIG_TMPFS) && is_पंचांगpfs)
		वापस shmem_init_fs_context(fc);

	वापस ramfs_init_fs_context(fc);
पूर्ण

काष्ठा file_प्रणाली_type rootfs_fs_type = अणु
	.name		= "rootfs",
	.init_fs_context = rootfs_init_fs_context,
	.समाप्त_sb	= समाप्त_litter_super,
पूर्ण;

व्योम __init init_rootfs(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_TMPFS) && !saved_root_name[0] &&
		(!root_fs_names || म_माला(root_fs_names, "tmpfs")))
		is_पंचांगpfs = true;
पूर्ण
