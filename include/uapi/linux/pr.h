<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_PR_H
#घोषणा _UAPI_PR_H

#समावेश <linux/types.h>

क्रमागत pr_type अणु
	PR_WRITE_EXCLUSIVE		= 1,
	PR_EXCLUSIVE_ACCESS		= 2,
	PR_WRITE_EXCLUSIVE_REG_ONLY	= 3,
	PR_EXCLUSIVE_ACCESS_REG_ONLY	= 4,
	PR_WRITE_EXCLUSIVE_ALL_REGS	= 5,
	PR_EXCLUSIVE_ACCESS_ALL_REGS	= 6,
पूर्ण;

काष्ठा pr_reservation अणु
	__u64	key;
	__u32	type;
	__u32	flags;
पूर्ण;

काष्ठा pr_registration अणु
	__u64	old_key;
	__u64	new_key;
	__u32	flags;
	__u32	__pad;
पूर्ण;

काष्ठा pr_preempt अणु
	__u64	old_key;
	__u64	new_key;
	__u32	type;
	__u32	flags;
पूर्ण;

काष्ठा pr_clear अणु
	__u64	key;
	__u32	flags;
	__u32	__pad;
पूर्ण;

#घोषणा PR_FL_IGNORE_KEY	(1 << 0)	/* ignore existing key */

#घोषणा IOC_PR_REGISTER		_IOW('p', 200, काष्ठा pr_registration)
#घोषणा IOC_PR_RESERVE		_IOW('p', 201, काष्ठा pr_reservation)
#घोषणा IOC_PR_RELEASE		_IOW('p', 202, काष्ठा pr_reservation)
#घोषणा IOC_PR_PREEMPT		_IOW('p', 203, काष्ठा pr_preempt)
#घोषणा IOC_PR_PREEMPT_ABORT	_IOW('p', 204, काष्ठा pr_preempt)
#घोषणा IOC_PR_CLEAR		_IOW('p', 205, काष्ठा pr_clear)

#पूर्ण_अगर /* _UAPI_PR_H */
