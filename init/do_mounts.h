<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/kernel.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/init.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/unistd.h>
#समावेश <linux/slab.h>
#समावेश <linux/mount.h>
#समावेश <linux/major.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/init_syscalls.h>

व्योम  mount_block_root(अक्षर *name, पूर्णांक flags);
व्योम  mount_root(व्योम);
बाह्य पूर्णांक root_mountflags;

अटल अंतरभूत __init पूर्णांक create_dev(अक्षर *name, dev_t dev)
अणु
	init_unlink(name);
	वापस init_mknod(name, S_IFBLK | 0600, new_encode_dev(dev));
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_RAM

पूर्णांक __init rd_load_disk(पूर्णांक n);
पूर्णांक __init rd_load_image(अक्षर *from);

#अन्यथा

अटल अंतरभूत पूर्णांक rd_load_disk(पूर्णांक n) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक rd_load_image(अक्षर *from) अणु वापस 0; पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_BLK_DEV_INITRD

bool __init initrd_load(व्योम);

#अन्यथा

अटल अंतरभूत bool initrd_load(व्योम) अणु वापस false; पूर्ण

#पूर्ण_अगर
