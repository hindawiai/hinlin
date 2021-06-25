<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/sys_arm.c
 *
 *  Copyright (C) People who wrote linux/arch/i386/kernel/sys_i386.c
 *  Copyright (C) 1995, 1996 Russell King.
 *
 *  This file contains various अक्रमom प्रणाली calls that
 *  have a non-standard calling sequence on the Linux/arm
 *  platक्रमm.
 */
#समावेश <linux/export.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/sem.h>
#समावेश <linux/msg.h>
#समावेश <linux/shm.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/syscalls.h>
#समावेश <linux/mman.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/ipc.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>

/*
 * Since loff_t is a 64 bit type we aव्योम a lot of ABI hassle
 * with a dअगरferent argument ordering.
 */
यंत्रlinkage दीर्घ sys_arm_fadvise64_64(पूर्णांक fd, पूर्णांक advice,
				     loff_t offset, loff_t len)
अणु
	वापस ksys_fadvise64_64(fd, offset, len, advice);
पूर्ण
