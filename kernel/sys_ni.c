<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/linkage.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश <यंत्र/unistd.h>

#अगर_घोषित CONFIG_ARCH_HAS_SYSCALL_WRAPPER
/* Architectures may override COND_SYSCALL and COND_SYSCALL_COMPAT */
#समावेश <यंत्र/syscall_wrapper.h>
#पूर्ण_अगर /* CONFIG_ARCH_HAS_SYSCALL_WRAPPER */

/*  we can't #समावेश <linux/syscalls.h> here,
    but tell gcc to not warn with -Wmissing-prototypes  */
यंत्रlinkage दीर्घ sys_ni_syscall(व्योम);

/*
 * Non-implemented प्रणाली calls get redirected here.
 */
यंत्रlinkage दीर्घ sys_ni_syscall(व्योम)
अणु
	वापस -ENOSYS;
पूर्ण

#अगर_अघोषित COND_SYSCALL
#घोषणा COND_SYSCALL(name) cond_syscall(sys_##name)
#पूर्ण_अगर /* COND_SYSCALL */

#अगर_अघोषित COND_SYSCALL_COMPAT
#घोषणा COND_SYSCALL_COMPAT(name) cond_syscall(compat_sys_##name)
#पूर्ण_अगर /* COND_SYSCALL_COMPAT */

/*
 * This list is kept in the same order as include/uapi/यंत्र-generic/unistd.h.
 * Architecture specअगरic entries go below, followed by deprecated or obsolete
 * प्रणाली calls.
 */

COND_SYSCALL(io_setup);
COND_SYSCALL_COMPAT(io_setup);
COND_SYSCALL(io_destroy);
COND_SYSCALL(io_submit);
COND_SYSCALL_COMPAT(io_submit);
COND_SYSCALL(io_cancel);
COND_SYSCALL(io_getevents_समय32);
COND_SYSCALL(io_getevents);
COND_SYSCALL(io_pgetevents_समय32);
COND_SYSCALL(io_pgetevents);
COND_SYSCALL_COMPAT(io_pgetevents_समय32);
COND_SYSCALL_COMPAT(io_pgetevents);
COND_SYSCALL(io_uring_setup);
COND_SYSCALL(io_uring_enter);
COND_SYSCALL(io_uring_रेजिस्टर);

/* fs/xattr.c */

/* fs/dcache.c */

/* fs/cookies.c */
COND_SYSCALL(lookup_dcookie);
COND_SYSCALL_COMPAT(lookup_dcookie);

/* fs/eventfd.c */
COND_SYSCALL(eventfd2);

/* fs/eventfd.c */
COND_SYSCALL(epoll_create1);
COND_SYSCALL(epoll_ctl);
COND_SYSCALL(epoll_pरुको);
COND_SYSCALL_COMPAT(epoll_pरुको);
COND_SYSCALL(epoll_pरुको2);
COND_SYSCALL_COMPAT(epoll_pरुको2);

/* fs/fcntl.c */

/* fs/inotअगरy_user.c */
COND_SYSCALL(inotअगरy_init1);
COND_SYSCALL(inotअगरy_add_watch);
COND_SYSCALL(inotअगरy_rm_watch);

/* fs/ioctl.c */

/* fs/ioprio.c */
COND_SYSCALL(ioprio_set);
COND_SYSCALL(ioprio_get);

/* fs/locks.c */
COND_SYSCALL(flock);

/* fs/namei.c */

/* fs/namespace.c */

/* fs/nfsctl.c */

/* fs/खोलो.c */

/* fs/pipe.c */

/* fs/quota.c */
COND_SYSCALL(quotactl);
COND_SYSCALL(quotactl_path);

/* fs/सूची_पढ़ो.c */

/* fs/पढ़ो_ग_लिखो.c */

/* fs/sendfile.c */

/* fs/select.c */

/* fs/संकेतfd.c */
COND_SYSCALL(संकेतfd4);
COND_SYSCALL_COMPAT(संकेतfd4);

/* fs/splice.c */

/* fs/stat.c */

/* fs/sync.c */

/* fs/समयrfd.c */
COND_SYSCALL(समयrfd_create);
COND_SYSCALL(समयrfd_समय_रखो);
COND_SYSCALL(समयrfd_समय_रखो32);
COND_SYSCALL(समयrfd_समय_लो);
COND_SYSCALL(समयrfd_समय_लो32);

/* fs/uबार.c */

/* kernel/acct.c */
COND_SYSCALL(acct);

/* kernel/capability.c */
COND_SYSCALL(capget);
COND_SYSCALL(capset);

/* kernel/exec_करोमुख्य.c */

/* kernel/निकास.c */

/* kernel/विभाजन.c */
/* __ARCH_WANT_SYS_CLONE3 */
COND_SYSCALL(clone3);

/* kernel/futex.c */
COND_SYSCALL(futex);
COND_SYSCALL(futex_समय32);
COND_SYSCALL(set_robust_list);
COND_SYSCALL_COMPAT(set_robust_list);
COND_SYSCALL(get_robust_list);
COND_SYSCALL_COMPAT(get_robust_list);

/* kernel/hrसमयr.c */

/* kernel/iसमयr.c */

/* kernel/kexec.c */
COND_SYSCALL(kexec_load);
COND_SYSCALL_COMPAT(kexec_load);

/* kernel/module.c */
COND_SYSCALL(init_module);
COND_SYSCALL(delete_module);

/* kernel/posix-समयrs.c */

/* kernel/prपूर्णांकk.c */
COND_SYSCALL(syslog);

/* kernel/ptrace.c */

/* kernel/sched/core.c */

/* kernel/sys.c */
COND_SYSCALL(setregid);
COND_SYSCALL(setgid);
COND_SYSCALL(setreuid);
COND_SYSCALL(setuid);
COND_SYSCALL(setresuid);
COND_SYSCALL(getresuid);
COND_SYSCALL(setresgid);
COND_SYSCALL(getresgid);
COND_SYSCALL(setfsuid);
COND_SYSCALL(setfsgid);
COND_SYSCALL(setgroups);
COND_SYSCALL(getgroups);

/* kernel/समय.c */

/* kernel/समयr.c */

/* ipc/mqueue.c */
COND_SYSCALL(mq_खोलो);
COND_SYSCALL_COMPAT(mq_खोलो);
COND_SYSCALL(mq_unlink);
COND_SYSCALL(mq_समयdsend);
COND_SYSCALL(mq_समयdsend_समय32);
COND_SYSCALL(mq_समयdreceive);
COND_SYSCALL(mq_समयdreceive_समय32);
COND_SYSCALL(mq_notअगरy);
COND_SYSCALL_COMPAT(mq_notअगरy);
COND_SYSCALL(mq_माला_लोetattr);
COND_SYSCALL_COMPAT(mq_माला_लोetattr);

/* ipc/msg.c */
COND_SYSCALL(msgget);
COND_SYSCALL(old_msgctl);
COND_SYSCALL(msgctl);
COND_SYSCALL_COMPAT(msgctl);
COND_SYSCALL_COMPAT(old_msgctl);
COND_SYSCALL(msgrcv);
COND_SYSCALL_COMPAT(msgrcv);
COND_SYSCALL(msgsnd);
COND_SYSCALL_COMPAT(msgsnd);

/* ipc/sem.c */
COND_SYSCALL(semget);
COND_SYSCALL(old_semctl);
COND_SYSCALL(semctl);
COND_SYSCALL_COMPAT(semctl);
COND_SYSCALL_COMPAT(old_semctl);
COND_SYSCALL(semसमयकरोp);
COND_SYSCALL(semसमयकरोp_समय32);
COND_SYSCALL(semop);

/* ipc/shm.c */
COND_SYSCALL(shmget);
COND_SYSCALL(old_shmctl);
COND_SYSCALL(shmctl);
COND_SYSCALL_COMPAT(shmctl);
COND_SYSCALL_COMPAT(old_shmctl);
COND_SYSCALL(shmat);
COND_SYSCALL_COMPAT(shmat);
COND_SYSCALL(shmdt);

/* net/socket.c */
COND_SYSCALL(socket);
COND_SYSCALL(socketpair);
COND_SYSCALL(bind);
COND_SYSCALL(listen);
COND_SYSCALL(accept);
COND_SYSCALL(connect);
COND_SYSCALL(माला_लोockname);
COND_SYSCALL(getpeername);
COND_SYSCALL(setsockopt);
COND_SYSCALL_COMPAT(setsockopt);
COND_SYSCALL(माला_लोockopt);
COND_SYSCALL_COMPAT(माला_लोockopt);
COND_SYSCALL(sendto);
COND_SYSCALL(shutकरोwn);
COND_SYSCALL(recvfrom);
COND_SYSCALL_COMPAT(recvfrom);
COND_SYSCALL(sendmsg);
COND_SYSCALL_COMPAT(sendmsg);
COND_SYSCALL(recvmsg);
COND_SYSCALL_COMPAT(recvmsg);

/* mm/filemap.c */

/* mm/nommu.c, also with MMU */
COND_SYSCALL(mremap);

/* security/keys/keyctl.c */
COND_SYSCALL(add_key);
COND_SYSCALL(request_key);
COND_SYSCALL(keyctl);
COND_SYSCALL_COMPAT(keyctl);

/* security/landlock/syscalls.c */
COND_SYSCALL(landlock_create_ruleset);
COND_SYSCALL(landlock_add_rule);
COND_SYSCALL(landlock_restrict_self);

/* arch/example/kernel/sys_example.c */

/* mm/fadvise.c */
COND_SYSCALL(fadvise64_64);

/* mm/, CONFIG_MMU only */
COND_SYSCALL(swapon);
COND_SYSCALL(swapoff);
COND_SYSCALL(mprotect);
COND_SYSCALL(msync);
COND_SYSCALL(mlock);
COND_SYSCALL(munlock);
COND_SYSCALL(mlockall);
COND_SYSCALL(munlockall);
COND_SYSCALL(mincore);
COND_SYSCALL(madvise);
COND_SYSCALL(process_madvise);
COND_SYSCALL(remap_file_pages);
COND_SYSCALL(mbind);
COND_SYSCALL_COMPAT(mbind);
COND_SYSCALL(get_mempolicy);
COND_SYSCALL_COMPAT(get_mempolicy);
COND_SYSCALL(set_mempolicy);
COND_SYSCALL_COMPAT(set_mempolicy);
COND_SYSCALL(migrate_pages);
COND_SYSCALL_COMPAT(migrate_pages);
COND_SYSCALL(move_pages);
COND_SYSCALL_COMPAT(move_pages);

COND_SYSCALL(perf_event_खोलो);
COND_SYSCALL(accept4);
COND_SYSCALL(recvmmsg);
COND_SYSCALL(recvmmsg_समय32);
COND_SYSCALL_COMPAT(recvmmsg_समय32);
COND_SYSCALL_COMPAT(recvmmsg_समय64);

/*
 * Architecture specअगरic syscalls: see further below
 */

/* fanotअगरy */
COND_SYSCALL(fanotअगरy_init);
COND_SYSCALL(fanotअगरy_mark);

/* खोलो by handle */
COND_SYSCALL(name_to_handle_at);
COND_SYSCALL(खोलो_by_handle_at);
COND_SYSCALL_COMPAT(खोलो_by_handle_at);

COND_SYSCALL(sendmmsg);
COND_SYSCALL_COMPAT(sendmmsg);
COND_SYSCALL(process_vm_पढ़ोv);
COND_SYSCALL_COMPAT(process_vm_पढ़ोv);
COND_SYSCALL(process_vm_ग_लिखोv);
COND_SYSCALL_COMPAT(process_vm_ग_लिखोv);

/* compare kernel poपूर्णांकers */
COND_SYSCALL(kcmp);

COND_SYSCALL(finit_module);

/* operate on Secure Computing state */
COND_SYSCALL(seccomp);

COND_SYSCALL(memfd_create);

/* access BPF programs and maps */
COND_SYSCALL(bpf);

/* execveat */
COND_SYSCALL(execveat);

COND_SYSCALL(userfaultfd);

/* membarrier */
COND_SYSCALL(membarrier);

COND_SYSCALL(mlock2);

COND_SYSCALL(copy_file_range);

/* memory protection keys */
COND_SYSCALL(pkey_mprotect);
COND_SYSCALL(pkey_alloc);
COND_SYSCALL(pkey_मुक्त);


/*
 * Architecture specअगरic weak syscall entries.
 */

/* pciconfig: alpha, arm, arm64, ia64, sparc */
COND_SYSCALL(pciconfig_पढ़ो);
COND_SYSCALL(pciconfig_ग_लिखो);
COND_SYSCALL(pciconfig_iobase);

/* sys_socketcall: arm, mips, x86, ... */
COND_SYSCALL(socketcall);
COND_SYSCALL_COMPAT(socketcall);

/* compat syscalls क्रम arm64, x86, ... */
COND_SYSCALL_COMPAT(fanotअगरy_mark);

/* x86 */
COND_SYSCALL(vm86old);
COND_SYSCALL(modअगरy_ldt);
COND_SYSCALL(vm86);
COND_SYSCALL(kexec_file_load);

/* s390 */
COND_SYSCALL(s390_pci_mmio_पढ़ो);
COND_SYSCALL(s390_pci_mmio_ग_लिखो);
COND_SYSCALL(s390_ipc);
COND_SYSCALL_COMPAT(s390_ipc);

/* घातerpc */
COND_SYSCALL(rtas);
COND_SYSCALL(spu_run);
COND_SYSCALL(spu_create);
COND_SYSCALL(subpage_prot);


/*
 * Deprecated प्रणाली calls which are still defined in
 * include/uapi/यंत्र-generic/unistd.h and wanted by >= 1 arch
 */

/* __ARCH_WANT_SYSCALL_NO_FLAGS */
COND_SYSCALL(epoll_create);
COND_SYSCALL(inotअगरy_init);
COND_SYSCALL(eventfd);
COND_SYSCALL(संकेतfd);
COND_SYSCALL_COMPAT(संकेतfd);

/* __ARCH_WANT_SYSCALL_OFF_T */
COND_SYSCALL(fadvise64);

/* __ARCH_WANT_SYSCALL_DEPRECATED */
COND_SYSCALL(epoll_रुको);
COND_SYSCALL(recv);
COND_SYSCALL_COMPAT(recv);
COND_SYSCALL(send);
COND_SYSCALL(bdflush);
COND_SYSCALL(uselib);

/* optional: समय32 */
COND_SYSCALL(समय32);
COND_SYSCALL(sसमय32);
COND_SYSCALL(uसमय32);
COND_SYSCALL(adjसमयx_समय32);
COND_SYSCALL(sched_rr_get_पूर्णांकerval_समय32);
COND_SYSCALL(nanosleep_समय32);
COND_SYSCALL(rt_sigसमयdरुको_समय32);
COND_SYSCALL_COMPAT(rt_sigसमयdरुको_समय32);
COND_SYSCALL(समयr_समय_रखो32);
COND_SYSCALL(समयr_समय_लो32);
COND_SYSCALL(घड़ी_समय_रखो32);
COND_SYSCALL(घड़ी_समय_लो32);
COND_SYSCALL(घड़ी_getres_समय32);
COND_SYSCALL(घड़ी_nanosleep_समय32);
COND_SYSCALL(uबार_समय32);
COND_SYSCALL(fuबारat_समय32);
COND_SYSCALL(pselect6_समय32);
COND_SYSCALL_COMPAT(pselect6_समय32);
COND_SYSCALL(ppoll_समय32);
COND_SYSCALL_COMPAT(ppoll_समय32);
COND_SYSCALL(uसमयnsat_समय32);
COND_SYSCALL(घड़ी_adjसमय32);

/*
 * The syscalls below are not found in include/uapi/यंत्र-generic/unistd.h
 */

/* obsolete: SGETMASK_SYSCALL */
COND_SYSCALL(sgeपंचांगask);
COND_SYSCALL(sseपंचांगask);

/* obsolete: SYSFS_SYSCALL */
COND_SYSCALL(sysfs);

/* obsolete: __ARCH_WANT_SYS_IPC */
COND_SYSCALL(ipc);
COND_SYSCALL_COMPAT(ipc);

/* obsolete: UID16 */
COND_SYSCALL(chown16);
COND_SYSCALL(fchown16);
COND_SYSCALL(getegid16);
COND_SYSCALL(geteuid16);
COND_SYSCALL(getgid16);
COND_SYSCALL(getgroups16);
COND_SYSCALL(getresgid16);
COND_SYSCALL(getresuid16);
COND_SYSCALL(getuid16);
COND_SYSCALL(lchown16);
COND_SYSCALL(setfsgid16);
COND_SYSCALL(setfsuid16);
COND_SYSCALL(setgid16);
COND_SYSCALL(setgroups16);
COND_SYSCALL(setregid16);
COND_SYSCALL(setresgid16);
COND_SYSCALL(setresuid16);
COND_SYSCALL(setreuid16);
COND_SYSCALL(setuid16);

/* restartable sequence */
COND_SYSCALL(rseq);
