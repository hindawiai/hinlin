<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/ipc/msgutil.c
 * Copyright (C) 1999, 2004 Manfred Spraul
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/init.h>
#समावेश <linux/security.h>
#समावेश <linux/slab.h>
#समावेश <linux/ipc.h>
#समावेश <linux/msg.h>
#समावेश <linux/ipc_namespace.h>
#समावेश <linux/utsname.h>
#समावेश <linux/proc_ns.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sched.h>

#समावेश "util.h"

DEFINE_SPINLOCK(mq_lock);

/*
 * The next 2 defines are here bc this is the only file
 * compiled when either CONFIG_SYSVIPC and CONFIG_POSIX_MQUEUE
 * and not CONFIG_IPC_NS.
 */
काष्ठा ipc_namespace init_ipc_ns = अणु
	.ns.count = REFCOUNT_INIT(1),
	.user_ns = &init_user_ns,
	.ns.inum = PROC_IPC_INIT_INO,
#अगर_घोषित CONFIG_IPC_NS
	.ns.ops = &ipcns_operations,
#पूर्ण_अगर
पूर्ण;

काष्ठा msg_msgseg अणु
	काष्ठा msg_msgseg *next;
	/* the next part of the message follows immediately */
पूर्ण;

#घोषणा DATALEN_MSG	((माप_प्रकार)PAGE_SIZE-माप(काष्ठा msg_msg))
#घोषणा DATALEN_SEG	((माप_प्रकार)PAGE_SIZE-माप(काष्ठा msg_msgseg))


अटल काष्ठा msg_msg *alloc_msg(माप_प्रकार len)
अणु
	काष्ठा msg_msg *msg;
	काष्ठा msg_msgseg **pseg;
	माप_प्रकार alen;

	alen = min(len, DATALEN_MSG);
	msg = kदो_स्मृति(माप(*msg) + alen, GFP_KERNEL_ACCOUNT);
	अगर (msg == शून्य)
		वापस शून्य;

	msg->next = शून्य;
	msg->security = शून्य;

	len -= alen;
	pseg = &msg->next;
	जबतक (len > 0) अणु
		काष्ठा msg_msgseg *seg;

		cond_resched();

		alen = min(len, DATALEN_SEG);
		seg = kदो_स्मृति(माप(*seg) + alen, GFP_KERNEL_ACCOUNT);
		अगर (seg == शून्य)
			जाओ out_err;
		*pseg = seg;
		seg->next = शून्य;
		pseg = &seg->next;
		len -= alen;
	पूर्ण

	वापस msg;

out_err:
	मुक्त_msg(msg);
	वापस शून्य;
पूर्ण

काष्ठा msg_msg *load_msg(स्थिर व्योम __user *src, माप_प्रकार len)
अणु
	काष्ठा msg_msg *msg;
	काष्ठा msg_msgseg *seg;
	पूर्णांक err = -EFAULT;
	माप_प्रकार alen;

	msg = alloc_msg(len);
	अगर (msg == शून्य)
		वापस ERR_PTR(-ENOMEM);

	alen = min(len, DATALEN_MSG);
	अगर (copy_from_user(msg + 1, src, alen))
		जाओ out_err;

	क्रम (seg = msg->next; seg != शून्य; seg = seg->next) अणु
		len -= alen;
		src = (अक्षर __user *)src + alen;
		alen = min(len, DATALEN_SEG);
		अगर (copy_from_user(seg + 1, src, alen))
			जाओ out_err;
	पूर्ण

	err = security_msg_msg_alloc(msg);
	अगर (err)
		जाओ out_err;

	वापस msg;

out_err:
	मुक्त_msg(msg);
	वापस ERR_PTR(err);
पूर्ण
#अगर_घोषित CONFIG_CHECKPOINT_RESTORE
काष्ठा msg_msg *copy_msg(काष्ठा msg_msg *src, काष्ठा msg_msg *dst)
अणु
	काष्ठा msg_msgseg *dst_pseg, *src_pseg;
	माप_प्रकार len = src->m_ts;
	माप_प्रकार alen;

	अगर (src->m_ts > dst->m_ts)
		वापस ERR_PTR(-EINVAL);

	alen = min(len, DATALEN_MSG);
	स_नकल(dst + 1, src + 1, alen);

	क्रम (dst_pseg = dst->next, src_pseg = src->next;
	     src_pseg != शून्य;
	     dst_pseg = dst_pseg->next, src_pseg = src_pseg->next) अणु

		len -= alen;
		alen = min(len, DATALEN_SEG);
		स_नकल(dst_pseg + 1, src_pseg + 1, alen);
	पूर्ण

	dst->m_type = src->m_type;
	dst->m_ts = src->m_ts;

	वापस dst;
पूर्ण
#अन्यथा
काष्ठा msg_msg *copy_msg(काष्ठा msg_msg *src, काष्ठा msg_msg *dst)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण
#पूर्ण_अगर
पूर्णांक store_msg(व्योम __user *dest, काष्ठा msg_msg *msg, माप_प्रकार len)
अणु
	माप_प्रकार alen;
	काष्ठा msg_msgseg *seg;

	alen = min(len, DATALEN_MSG);
	अगर (copy_to_user(dest, msg + 1, alen))
		वापस -1;

	क्रम (seg = msg->next; seg != शून्य; seg = seg->next) अणु
		len -= alen;
		dest = (अक्षर __user *)dest + alen;
		alen = min(len, DATALEN_SEG);
		अगर (copy_to_user(dest, seg + 1, alen))
			वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

व्योम मुक्त_msg(काष्ठा msg_msg *msg)
अणु
	काष्ठा msg_msgseg *seg;

	security_msg_msg_मुक्त(msg);

	seg = msg->next;
	kमुक्त(msg);
	जबतक (seg != शून्य) अणु
		काष्ठा msg_msgseg *पंचांगp = seg->next;

		cond_resched();
		kमुक्त(seg);
		seg = पंचांगp;
	पूर्ण
पूर्ण
