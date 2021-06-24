<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * init/noinitramfs.c
 *
 * Copyright (C) 2006, NXP Semiconductors, All Rights Reserved
 * Author: Jean-Paul Saman <jean-paul.saman@nxp.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/kdev_t.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/init_syscalls.h>

/*
 * Create a simple rootfs that is similar to the शेष initramfs
 */
अटल पूर्णांक __init शेष_rootfs(व्योम)
अणु
	पूर्णांक err;

	err = init_सूची_गढ़ो("/dev", 0755);
	अगर (err < 0)
		जाओ out;

	err = init_mknod("/dev/console", S_IFCHR | S_IRUSR | S_IWUSR,
			new_encode_dev(MKDEV(5, 1)));
	अगर (err < 0)
		जाओ out;

	err = init_सूची_गढ़ो("/root", 0700);
	अगर (err < 0)
		जाओ out;

	वापस 0;

out:
	prपूर्णांकk(KERN_WARNING "Failed to create a rootfs\n");
	वापस err;
पूर्ण
rootfs_initcall(शेष_rootfs);
