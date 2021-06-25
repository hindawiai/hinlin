<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common syscall restarting data
 */
#अगर_अघोषित __LINUX_RESTART_BLOCK_H
#घोषणा __LINUX_RESTART_BLOCK_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/समय64.h>

काष्ठा बारpec;
काष्ठा old_बारpec32;
काष्ठा pollfd;

क्रमागत बारpec_type अणु
	TT_NONE		= 0,
	TT_NATIVE	= 1,
	TT_COMPAT	= 2,
पूर्ण;

/*
 * System call restart block.
 */
काष्ठा restart_block अणु
	अचिन्हित दीर्घ arch_data;
	दीर्घ (*fn)(काष्ठा restart_block *);
	जोड़ अणु
		/* For futex_रुको and futex_रुको_requeue_pi */
		काष्ठा अणु
			u32 __user *uaddr;
			u32 val;
			u32 flags;
			u32 bitset;
			u64 समय;
			u32 __user *uaddr2;
		पूर्ण futex;
		/* For nanosleep */
		काष्ठा अणु
			घड़ीid_t घड़ीid;
			क्रमागत बारpec_type type;
			जोड़ अणु
				काष्ठा __kernel_बारpec __user *rmtp;
				काष्ठा old_बारpec32 __user *compat_rmtp;
			पूर्ण;
			u64 expires;
		पूर्ण nanosleep;
		/* For poll */
		काष्ठा अणु
			काष्ठा pollfd __user *ufds;
			पूर्णांक nfds;
			पूर्णांक has_समयout;
			अचिन्हित दीर्घ tv_sec;
			अचिन्हित दीर्घ tv_nsec;
		पूर्ण poll;
	पूर्ण;
पूर्ण;

बाह्य दीर्घ करो_no_restart_syscall(काष्ठा restart_block *parm);

#पूर्ण_अगर /* __LINUX_RESTART_BLOCK_H */
