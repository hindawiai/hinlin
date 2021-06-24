<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *	Berkeley style UIO काष्ठाures	-	Alan Cox 1994.
 *
 *		This program is मुक्त software; you can redistribute it and/or
 *		modअगरy it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
#अगर_अघोषित _UAPI__LINUX_UIO_H
#घोषणा _UAPI__LINUX_UIO_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>


काष्ठा iovec
अणु
	व्योम __user *iov_base;	/* BSD uses caddr_t (1003.1g requires व्योम *) */
	__kernel_माप_प्रकार iov_len; /* Must be माप_प्रकार (1003.1g) */
पूर्ण;

/*
 *	UIO_MAXIOV shall be at least 16 1003.1g (5.4.1.1)
 */
 
#घोषणा UIO_FASTIOV	8
#घोषणा UIO_MAXIOV	1024


#पूर्ण_अगर /* _UAPI__LINUX_UIO_H */
