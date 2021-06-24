<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_KCMP_H
#घोषणा _UAPI_LINUX_KCMP_H

#समावेश <linux/types.h>

/* Comparison type */
क्रमागत kcmp_type अणु
	KCMP_खाता,
	KCMP_VM,
	KCMP_खाताS,
	KCMP_FS,
	KCMP_SIGHAND,
	KCMP_IO,
	KCMP_SYSVSEM,
	KCMP_EPOLL_TFD,

	KCMP_TYPES,
पूर्ण;

/* Slot क्रम KCMP_EPOLL_TFD */
काष्ठा kcmp_epoll_slot अणु
	__u32 efd;		/* epoll file descriptor */
	__u32 tfd;		/* target file number */
	__u32 toff;		/* target offset within same numbered sequence */
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_KCMP_H */
