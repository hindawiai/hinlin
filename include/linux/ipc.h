<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_IPC_H
#घोषणा _LINUX_IPC_H

#समावेश <linux/spinlock.h>
#समावेश <linux/uidgid.h>
#समावेश <linux/rhashtable-types.h>
#समावेश <uapi/linux/ipc.h>
#समावेश <linux/refcount.h>

/* used by in-kernel data काष्ठाures */
काष्ठा kern_ipc_perm अणु
	spinlock_t	lock;
	bool		deleted;
	पूर्णांक		id;
	key_t		key;
	kuid_t		uid;
	kgid_t		gid;
	kuid_t		cuid;
	kgid_t		cgid;
	umode_t		mode;
	अचिन्हित दीर्घ	seq;
	व्योम		*security;

	काष्ठा rhash_head khtnode;

	काष्ठा rcu_head rcu;
	refcount_t refcount;
पूर्ण ____cacheline_aligned_in_smp __अक्रमomize_layout;

#पूर्ण_अगर /* _LINUX_IPC_H */
