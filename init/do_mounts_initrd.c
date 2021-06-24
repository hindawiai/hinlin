<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/unistd.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/minix_fs.h>
#समावेश <linux/romfs_fs.h>
#समावेश <linux/initrd.h>
#समावेश <linux/sched.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/kmod.h>
#समावेश <uapi/linux/mount.h>

#समावेश "do_mounts.h"

अचिन्हित दीर्घ initrd_start, initrd_end;
पूर्णांक initrd_below_start_ok;
अचिन्हित पूर्णांक real_root_dev;	/* करो_proc_करोपूर्णांकvec cannot handle kdev_t */
अटल पूर्णांक __initdata mount_initrd = 1;

phys_addr_t phys_initrd_start __initdata;
अचिन्हित दीर्घ phys_initrd_size __initdata;

अटल पूर्णांक __init no_initrd(अक्षर *str)
अणु
	mount_initrd = 0;
	वापस 1;
पूर्ण

__setup("noinitrd", no_initrd);

अटल पूर्णांक __init early_initrdmem(अक्षर *p)
अणु
	phys_addr_t start;
	अचिन्हित दीर्घ size;
	अक्षर *endp;

	start = memparse(p, &endp);
	अगर (*endp == ',') अणु
		size = memparse(endp + 1, शून्य);

		phys_initrd_start = start;
		phys_initrd_size = size;
	पूर्ण
	वापस 0;
पूर्ण
early_param("initrdmem", early_initrdmem);

अटल पूर्णांक __init early_initrd(अक्षर *p)
अणु
	वापस early_initrdmem(p);
पूर्ण
early_param("initrd", early_initrd);

अटल पूर्णांक __init init_linuxrc(काष्ठा subprocess_info *info, काष्ठा cred *new)
अणु
	ksys_unshare(CLONE_FS | CLONE_खाताS);
	console_on_rootfs();
	/* move initrd over / and स_बदलो/chroot in initrd root */
	init_स_बदलो("/root");
	init_mount(".", "/", शून्य, MS_MOVE, शून्य);
	init_chroot(".");
	ksys_setsid();
	वापस 0;
पूर्ण

अटल व्योम __init handle_initrd(व्योम)
अणु
	काष्ठा subprocess_info *info;
	अटल अक्षर *argv[] = अणु "linuxrc", शून्य, पूर्ण;
	बाह्य अक्षर *envp_init[];
	पूर्णांक error;

	pr_warn("using deprecated initrd support, will be removed in 2021.\n");

	real_root_dev = new_encode_dev(ROOT_DEV);
	create_dev("/dev/root.old", Root_RAM0);
	/* mount initrd on rootfs' /root */
	mount_block_root("/dev/root.old", root_mountflags & ~MS_RDONLY);
	init_सूची_गढ़ो("/old", 0700);
	init_स_बदलो("/old");

	/*
	 * In हाल that a resume from disk is carried out by linuxrc or one of
	 * its children, we need to tell the मुक्तzer not to रुको क्रम us.
	 */
	current->flags |= PF_FREEZER_SKIP;

	info = call_usermodehelper_setup("/linuxrc", argv, envp_init,
					 GFP_KERNEL, init_linuxrc, शून्य, शून्य);
	अगर (!info)
		वापस;
	call_usermodehelper_exec(info, UMH_WAIT_PROC);

	current->flags &= ~PF_FREEZER_SKIP;

	/* move initrd to rootfs' /old */
	init_mount("..", ".", शून्य, MS_MOVE, शून्य);
	/* चयन root and cwd back to / of rootfs */
	init_chroot("..");

	अगर (new_decode_dev(real_root_dev) == Root_RAM0) अणु
		init_स_बदलो("/old");
		वापस;
	पूर्ण

	init_स_बदलो("/");
	ROOT_DEV = new_decode_dev(real_root_dev);
	mount_root();

	prपूर्णांकk(KERN_NOTICE "Trying to move old root to /initrd ... ");
	error = init_mount("/old", "/root/initrd", शून्य, MS_MOVE, शून्य);
	अगर (!error)
		prपूर्णांकk("okay\n");
	अन्यथा अणु
		अगर (error == -ENOENT)
			prपूर्णांकk("/initrd does not exist. Ignored.\n");
		अन्यथा
			prपूर्णांकk("failed\n");
		prपूर्णांकk(KERN_NOTICE "Unmounting old root\n");
		init_umount("/old", MNT_DETACH);
	पूर्ण
पूर्ण

bool __init initrd_load(व्योम)
अणु
	अगर (mount_initrd) अणु
		create_dev("/dev/ram", Root_RAM0);
		/*
		 * Load the initrd data पूर्णांकo /dev/ram0. Execute it as initrd
		 * unless /dev/ram0 is supposed to be our actual root device,
		 * in that हाल the ram disk is just set up here, and माला_लो
		 * mounted in the normal path.
		 */
		अगर (rd_load_image("/initrd.image") && ROOT_DEV != Root_RAM0) अणु
			init_unlink("/initrd.image");
			handle_initrd();
			वापस true;
		पूर्ण
	पूर्ण
	init_unlink("/initrd.image");
	वापस false;
पूर्ण
