<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __LINUX_INITRD_H
#घोषणा __LINUX_INITRD_H

#घोषणा INITRD_MINOR 250 /* shouldn't collide with /dev/ram* too soon ... */

/* starting block # of image */
बाह्य पूर्णांक rd_image_start;

/* size of a single RAM disk */
बाह्य अचिन्हित दीर्घ rd_size;

/* 1 अगर it is not an error अगर initrd_start < memory_start */
बाह्य पूर्णांक initrd_below_start_ok;

/* मुक्त_initrd_mem always माला_लो called with the next two as arguments.. */
बाह्य अचिन्हित दीर्घ initrd_start, initrd_end;
बाह्य व्योम मुक्त_initrd_mem(अचिन्हित दीर्घ, अचिन्हित दीर्घ);

#अगर_घोषित CONFIG_BLK_DEV_INITRD
बाह्य व्योम __init reserve_initrd_mem(व्योम);
बाह्य व्योम रुको_क्रम_initramfs(व्योम);
#अन्यथा
अटल अंतरभूत व्योम __init reserve_initrd_mem(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम रुको_क्रम_initramfs(व्योम) अणुपूर्ण
#पूर्ण_अगर

बाह्य phys_addr_t phys_initrd_start;
बाह्य अचिन्हित दीर्घ phys_initrd_size;

बाह्य अचिन्हित पूर्णांक real_root_dev;

बाह्य अक्षर __initramfs_start[];
बाह्य अचिन्हित दीर्घ __initramfs_size;

व्योम console_on_rootfs(व्योम);

#पूर्ण_अगर /* __LINUX_INITRD_H */
