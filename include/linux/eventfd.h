<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  include/linux/eventfd.h
 *
 *  Copyright (C) 2007  Davide Libenzi <davidel@xmailserver.org>
 *
 */

#अगर_अघोषित _LINUX_EVENTFD_H
#घोषणा _LINUX_EVENTFD_H

#समावेश <linux/fcntl.h>
#समावेश <linux/रुको.h>
#समावेश <linux/err.h>
#समावेश <linux/percpu-defs.h>
#समावेश <linux/percpu.h>

/*
 * CAREFUL: Check include/uapi/यंत्र-generic/fcntl.h when defining
 * new flags, since they might collide with O_* ones. We want
 * to re-use O_* flags that couldn't possibly have a meaning
 * from eventfd, in order to leave a मुक्त define-space क्रम
 * shared O_* flags.
 */
#घोषणा EFD_SEMAPHORE (1 << 0)
#घोषणा EFD_CLOEXEC O_CLOEXEC
#घोषणा EFD_NONBLOCK O_NONBLOCK

#घोषणा EFD_SHARED_FCNTL_FLAGS (O_CLOEXEC | O_NONBLOCK)
#घोषणा EFD_FLAGS_SET (EFD_SHARED_FCNTL_FLAGS | EFD_SEMAPHORE)

काष्ठा eventfd_ctx;
काष्ठा file;

#अगर_घोषित CONFIG_EVENTFD

व्योम eventfd_ctx_put(काष्ठा eventfd_ctx *ctx);
काष्ठा file *eventfd_fget(पूर्णांक fd);
काष्ठा eventfd_ctx *eventfd_ctx_fdget(पूर्णांक fd);
काष्ठा eventfd_ctx *eventfd_ctx_fileget(काष्ठा file *file);
__u64 eventfd_संकेत(काष्ठा eventfd_ctx *ctx, __u64 n);
पूर्णांक eventfd_ctx_हटाओ_रुको_queue(काष्ठा eventfd_ctx *ctx, रुको_queue_entry_t *रुको,
				  __u64 *cnt);
व्योम eventfd_ctx_करो_पढ़ो(काष्ठा eventfd_ctx *ctx, __u64 *cnt);

DECLARE_PER_CPU(पूर्णांक, eventfd_wake_count);

अटल अंतरभूत bool eventfd_संकेत_count(व्योम)
अणु
	वापस this_cpu_पढ़ो(eventfd_wake_count);
पूर्ण

#अन्यथा /* CONFIG_EVENTFD */

/*
 * Ugly ugly ugly error layer to support modules that uses eventfd but
 * pretend to work in !CONFIG_EVENTFD configurations. Namely, AIO.
 */

अटल अंतरभूत काष्ठा eventfd_ctx *eventfd_ctx_fdget(पूर्णांक fd)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत पूर्णांक eventfd_संकेत(काष्ठा eventfd_ctx *ctx, पूर्णांक n)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत व्योम eventfd_ctx_put(काष्ठा eventfd_ctx *ctx)
अणु

पूर्ण

अटल अंतरभूत पूर्णांक eventfd_ctx_हटाओ_रुको_queue(काष्ठा eventfd_ctx *ctx,
						रुको_queue_entry_t *रुको, __u64 *cnt)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत bool eventfd_संकेत_count(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम eventfd_ctx_करो_पढ़ो(काष्ठा eventfd_ctx *ctx, __u64 *cnt)
अणु

पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_EVENTFD_H */

