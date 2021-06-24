<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  S390 version
 *
 *  Derived from "include/asm-i386/statfs.h"
 */

#अगर_अघोषित _S390_STATFS_H
#घोषणा _S390_STATFS_H

/*
 * We can't use <यंत्र-generic/statfs.h> because in 64-bit mode
 * we mix पूर्णांकs of dअगरferent sizes in our काष्ठा statfs.
 */

#अगर_अघोषित __KERNEL_STRICT_NAMES
#समावेश <linux/types.h>
प्रकार __kernel_fsid_t	fsid_t;
#पूर्ण_अगर

काष्ठा statfs अणु
	अचिन्हित पूर्णांक	f_type;
	अचिन्हित पूर्णांक	f_bsize;
	अचिन्हित दीर्घ	f_blocks;
	अचिन्हित दीर्घ	f_bमुक्त;
	अचिन्हित दीर्घ	f_bavail;
	अचिन्हित दीर्घ	f_files;
	अचिन्हित दीर्घ	f_fमुक्त;
	__kernel_fsid_t f_fsid;
	अचिन्हित पूर्णांक	f_namelen;
	अचिन्हित पूर्णांक	f_frsize;
	अचिन्हित पूर्णांक	f_flags;
	अचिन्हित पूर्णांक	f_spare[4];
पूर्ण;

काष्ठा statfs64 अणु
	अचिन्हित पूर्णांक	f_type;
	अचिन्हित पूर्णांक	f_bsize;
	अचिन्हित दीर्घ दीर्घ f_blocks;
	अचिन्हित दीर्घ दीर्घ f_bमुक्त;
	अचिन्हित दीर्घ दीर्घ f_bavail;
	अचिन्हित दीर्घ दीर्घ f_files;
	अचिन्हित दीर्घ दीर्घ f_fमुक्त;
	__kernel_fsid_t f_fsid;
	अचिन्हित पूर्णांक	f_namelen;
	अचिन्हित पूर्णांक	f_frsize;
	अचिन्हित पूर्णांक	f_flags;
	अचिन्हित पूर्णांक	f_spare[4];
पूर्ण;

#पूर्ण_अगर
