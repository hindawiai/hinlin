<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SPU file प्रणाली -- प्रणाली call stubs
 *
 * (C) Copyright IBM Deutschland Entwicklung GmbH 2005
 * (C) Copyright 2006-2007, IBM Corporation
 *
 * Author: Arnd Bergmann <arndb@de.ibm.com>
 */
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/binfmts.h>

#समावेश <यंत्र/spu.h>

/* रक्षित by rcu */
अटल काष्ठा spufs_calls *spufs_calls;

#अगर_घोषित CONFIG_SPU_FS_MODULE

अटल अंतरभूत काष्ठा spufs_calls *spufs_calls_get(व्योम)
अणु
	काष्ठा spufs_calls *calls = शून्य;

	rcu_पढ़ो_lock();
	calls = rcu_dereference(spufs_calls);
	अगर (calls && !try_module_get(calls->owner))
		calls = शून्य;
	rcu_पढ़ो_unlock();

	वापस calls;
पूर्ण

अटल अंतरभूत व्योम spufs_calls_put(काष्ठा spufs_calls *calls)
अणु
	BUG_ON(calls != spufs_calls);

	/* we करोn't need to rcu this, as we hold a reference to the module */
	module_put(spufs_calls->owner);
पूर्ण

#अन्यथा /* !defined CONFIG_SPU_FS_MODULE */

अटल अंतरभूत काष्ठा spufs_calls *spufs_calls_get(व्योम)
अणु
	वापस spufs_calls;
पूर्ण

अटल अंतरभूत व्योम spufs_calls_put(काष्ठा spufs_calls *calls) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_SPU_FS_MODULE */

SYSCALL_DEFINE4(spu_create, स्थिर अक्षर __user *, name, अचिन्हित पूर्णांक, flags,
	umode_t, mode, पूर्णांक, neighbor_fd)
अणु
	दीर्घ ret;
	काष्ठा spufs_calls *calls;

	calls = spufs_calls_get();
	अगर (!calls)
		वापस -ENOSYS;

	अगर (flags & SPU_CREATE_AFFINITY_SPU) अणु
		काष्ठा fd neighbor = fdget(neighbor_fd);
		ret = -EBADF;
		अगर (neighbor.file) अणु
			ret = calls->create_thपढ़ो(name, flags, mode, neighbor.file);
			fdput(neighbor);
		पूर्ण
	पूर्ण अन्यथा
		ret = calls->create_thपढ़ो(name, flags, mode, शून्य);

	spufs_calls_put(calls);
	वापस ret;
पूर्ण

SYSCALL_DEFINE3(spu_run,पूर्णांक, fd, __u32 __user *, unpc, __u32 __user *, ustatus)
अणु
	दीर्घ ret;
	काष्ठा fd arg;
	काष्ठा spufs_calls *calls;

	calls = spufs_calls_get();
	अगर (!calls)
		वापस -ENOSYS;

	ret = -EBADF;
	arg = fdget(fd);
	अगर (arg.file) अणु
		ret = calls->spu_run(arg.file, unpc, ustatus);
		fdput(arg);
	पूर्ण

	spufs_calls_put(calls);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COREDUMP
पूर्णांक elf_coredump_extra_notes_size(व्योम)
अणु
	काष्ठा spufs_calls *calls;
	पूर्णांक ret;

	calls = spufs_calls_get();
	अगर (!calls)
		वापस 0;

	ret = calls->coredump_extra_notes_size();

	spufs_calls_put(calls);

	वापस ret;
पूर्ण

पूर्णांक elf_coredump_extra_notes_ग_लिखो(काष्ठा coredump_params *cprm)
अणु
	काष्ठा spufs_calls *calls;
	पूर्णांक ret;

	calls = spufs_calls_get();
	अगर (!calls)
		वापस 0;

	ret = calls->coredump_extra_notes_ग_लिखो(cprm);

	spufs_calls_put(calls);

	वापस ret;
पूर्ण
#पूर्ण_अगर

व्योम notअगरy_spus_active(व्योम)
अणु
	काष्ठा spufs_calls *calls;

	calls = spufs_calls_get();
	अगर (!calls)
		वापस;

	calls->notअगरy_spus_active();
	spufs_calls_put(calls);

	वापस;
पूर्ण

पूर्णांक रेजिस्टर_spu_syscalls(काष्ठा spufs_calls *calls)
अणु
	अगर (spufs_calls)
		वापस -EBUSY;

	rcu_assign_poपूर्णांकer(spufs_calls, calls);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_spu_syscalls);

व्योम unरेजिस्टर_spu_syscalls(काष्ठा spufs_calls *calls)
अणु
	BUG_ON(spufs_calls->owner != calls->owner);
	RCU_INIT_POINTER(spufs_calls, शून्य);
	synchronize_rcu();
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_spu_syscalls);
