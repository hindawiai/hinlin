<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015 Anton Ivanov (aivanov@अणुbrocade.com,kot-begemot.co.ukपूर्ण)
 * Copyright (C) 2015 Thomas Meyer (thomas@m3y3r.de)
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#अगर_अघोषित __OS_H__
#घोषणा __OS_H__

#समावेश <मानकतर्क.स>
#समावेश <irq_user.h>
#समावेश <दीर्घ_लाँघ.h>
#समावेश <mm_id.h>

#घोषणा CATCH_EINTR(expr) जबतक ((त्रुटि_सं = 0, ((expr) < 0)) && (त्रुटि_सं == EINTR))

#घोषणा OS_TYPE_खाता 1
#घोषणा OS_TYPE_सूची 2
#घोषणा OS_TYPE_SYMLINK 3
#घोषणा OS_TYPE_CHARDEV 4
#घोषणा OS_TYPE_BLOCKDEV 5
#घोषणा OS_TYPE_FIFO 6
#घोषणा OS_TYPE_SOCK 7

/* os_access() flags */
#घोषणा OS_ACC_F_OK    0       /* Test क्रम existence.  */
#घोषणा OS_ACC_X_OK    1       /* Test क्रम execute permission.  */
#घोषणा OS_ACC_W_OK    2       /* Test क्रम ग_लिखो permission.  */
#घोषणा OS_ACC_R_OK    4       /* Test क्रम पढ़ो permission.  */
#घोषणा OS_ACC_RW_OK   (OS_ACC_W_OK | OS_ACC_R_OK) /* Test क्रम RW permission */

#अगर_घोषित CONFIG_64BIT
#घोषणा OS_LIB_PATH	"/usr/lib64/"
#अन्यथा
#घोषणा OS_LIB_PATH	"/usr/lib/"
#पूर्ण_अगर

#घोषणा OS_SENDMSG_MAX_FDS 8

/*
 * types taken from stat_file() in hostfs_user.c
 * (अगर they are wrong here, they are wrong there...).
 */
काष्ठा uml_stat अणु
	पूर्णांक                ust_dev;        /* device */
	अचिन्हित दीर्घ दीर्घ ust_ino;        /* inode */
	पूर्णांक                ust_mode;       /* protection */
	पूर्णांक                ust_nlink;      /* number of hard links */
	पूर्णांक                ust_uid;        /* user ID of owner */
	पूर्णांक                ust_gid;        /* group ID of owner */
	अचिन्हित दीर्घ दीर्घ ust_size;       /* total size, in bytes */
	पूर्णांक                ust_blksize;    /* blocksize क्रम fileप्रणाली I/O */
	अचिन्हित दीर्घ दीर्घ ust_blocks;     /* number of blocks allocated */
	अचिन्हित दीर्घ      ust_aसमय;      /* समय of last access */
	अचिन्हित दीर्घ      ust_mसमय;      /* समय of last modअगरication */
	अचिन्हित दीर्घ      ust_स_समय;      /* समय of last change */
पूर्ण;

काष्ठा खोलोflags अणु
	अचिन्हित पूर्णांक r : 1;
	अचिन्हित पूर्णांक w : 1;
	अचिन्हित पूर्णांक s : 1;	/* O_SYNC */
	अचिन्हित पूर्णांक c : 1;	/* O_CREAT */
	अचिन्हित पूर्णांक t : 1;	/* O_TRUNC */
	अचिन्हित पूर्णांक a : 1;	/* O_APPEND */
	अचिन्हित पूर्णांक e : 1;	/* O_EXCL */
	अचिन्हित पूर्णांक cl : 1;    /* FD_CLOEXEC */
पूर्ण;

#घोषणा OPENFLAGS() ((काष्ठा खोलोflags) अणु .r = 0, .w = 0, .s = 0, .c = 0, \
					  .t = 0, .a = 0, .e = 0, .cl = 0 पूर्ण)

अटल अंतरभूत काष्ठा खोलोflags of_पढ़ो(काष्ठा खोलोflags flags)
अणु
	flags.r = 1;
	वापस flags;
पूर्ण

अटल अंतरभूत काष्ठा खोलोflags of_ग_लिखो(काष्ठा खोलोflags flags)
अणु
	flags.w = 1;
	वापस flags;
पूर्ण

अटल अंतरभूत काष्ठा खोलोflags of_rdwr(काष्ठा खोलोflags flags)
अणु
	वापस of_पढ़ो(of_ग_लिखो(flags));
पूर्ण

अटल अंतरभूत काष्ठा खोलोflags of_set_rw(काष्ठा खोलोflags flags, पूर्णांक r, पूर्णांक w)
अणु
	flags.r = r;
	flags.w = w;
	वापस flags;
पूर्ण

अटल अंतरभूत काष्ठा खोलोflags of_sync(काष्ठा खोलोflags flags)
अणु
	flags.s = 1;
	वापस flags;
पूर्ण

अटल अंतरभूत काष्ठा खोलोflags of_create(काष्ठा खोलोflags flags)
अणु
	flags.c = 1;
	वापस flags;
पूर्ण

अटल अंतरभूत काष्ठा खोलोflags of_trunc(काष्ठा खोलोflags flags)
अणु
	flags.t = 1;
	वापस flags;
पूर्ण

अटल अंतरभूत काष्ठा खोलोflags of_append(काष्ठा खोलोflags flags)
अणु
	flags.a = 1;
	वापस flags;
पूर्ण

अटल अंतरभूत काष्ठा खोलोflags of_excl(काष्ठा खोलोflags flags)
अणु
	flags.e = 1;
	वापस flags;
पूर्ण

अटल अंतरभूत काष्ठा खोलोflags of_cloexec(काष्ठा खोलोflags flags)
अणु
	flags.cl = 1;
	वापस flags;
पूर्ण

/* file.c */
बाह्य पूर्णांक os_stat_file(स्थिर अक्षर *file_name, काष्ठा uml_stat *buf);
बाह्य पूर्णांक os_stat_fd(स्थिर पूर्णांक fd, काष्ठा uml_stat *buf);
बाह्य पूर्णांक os_access(स्थिर अक्षर *file, पूर्णांक mode);
बाह्य पूर्णांक os_set_exec_बंद(पूर्णांक fd);
बाह्य पूर्णांक os_ioctl_generic(पूर्णांक fd, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
बाह्य पूर्णांक os_get_अगरname(पूर्णांक fd, अक्षर *namebuf);
बाह्य पूर्णांक os_set_slip(पूर्णांक fd);
बाह्य पूर्णांक os_mode_fd(पूर्णांक fd, पूर्णांक mode);
बाह्य पूर्णांक os_fsync_file(पूर्णांक fd);

बाह्य पूर्णांक os_seek_file(पूर्णांक fd, अचिन्हित दीर्घ दीर्घ offset);
बाह्य पूर्णांक os_खोलो_file(स्थिर अक्षर *file, काष्ठा खोलोflags flags, पूर्णांक mode);
बाह्य पूर्णांक os_पढ़ो_file(पूर्णांक fd, व्योम *buf, पूर्णांक len);
बाह्य पूर्णांक os_ग_लिखो_file(पूर्णांक fd, स्थिर व्योम *buf, पूर्णांक count);
बाह्य पूर्णांक os_sync_file(पूर्णांक fd);
बाह्य पूर्णांक os_file_size(स्थिर अक्षर *file, अचिन्हित दीर्घ दीर्घ *size_out);
बाह्य पूर्णांक os_pपढ़ो_file(पूर्णांक fd, व्योम *buf, पूर्णांक len, अचिन्हित दीर्घ दीर्घ offset);
बाह्य पूर्णांक os_pग_लिखो_file(पूर्णांक fd, स्थिर व्योम *buf, पूर्णांक count, अचिन्हित दीर्घ दीर्घ offset);
बाह्य पूर्णांक os_file_modसमय(स्थिर अक्षर *file, दीर्घ दीर्घ *modसमय);
बाह्य पूर्णांक os_pipe(पूर्णांक *fd, पूर्णांक stream, पूर्णांक बंद_on_exec);
बाह्य पूर्णांक os_set_fd_async(पूर्णांक fd);
बाह्य पूर्णांक os_clear_fd_async(पूर्णांक fd);
बाह्य पूर्णांक os_set_fd_block(पूर्णांक fd, पूर्णांक blocking);
बाह्य पूर्णांक os_accept_connection(पूर्णांक fd);
बाह्य पूर्णांक os_create_unix_socket(स्थिर अक्षर *file, पूर्णांक len, पूर्णांक बंद_on_exec);
बाह्य पूर्णांक os_shutकरोwn_socket(पूर्णांक fd, पूर्णांक r, पूर्णांक w);
बाह्य व्योम os_बंद_file(पूर्णांक fd);
बाह्य पूर्णांक os_rcv_fd(पूर्णांक fd, पूर्णांक *helper_pid_out);
बाह्य पूर्णांक create_unix_socket(अक्षर *file, पूर्णांक len, पूर्णांक बंद_on_exec);
बाह्य पूर्णांक os_connect_socket(स्थिर अक्षर *name);
बाह्य पूर्णांक os_file_type(अक्षर *file);
बाह्य पूर्णांक os_file_mode(स्थिर अक्षर *file, काष्ठा खोलोflags *mode_out);
बाह्य पूर्णांक os_lock_file(पूर्णांक fd, पूर्णांक excl);
बाह्य व्योम os_flush_मानक_निकास(व्योम);
बाह्य पूर्णांक os_stat_fileप्रणाली(अक्षर *path, दीर्घ *bsize_out,
			      दीर्घ दीर्घ *blocks_out, दीर्घ दीर्घ *bमुक्त_out,
			      दीर्घ दीर्घ *bavail_out, दीर्घ दीर्घ *files_out,
			      दीर्घ दीर्घ *fमुक्त_out, व्योम *fsid_out,
			      पूर्णांक fsid_size, दीर्घ *namelen_out,
			      दीर्घ *spare_out);
बाह्य पूर्णांक os_change_dir(अक्षर *dir);
बाह्य पूर्णांक os_fchange_dir(पूर्णांक fd);
बाह्य अचिन्हित os_major(अचिन्हित दीर्घ दीर्घ dev);
बाह्य अचिन्हित os_minor(अचिन्हित दीर्घ दीर्घ dev);
बाह्य अचिन्हित दीर्घ दीर्घ os_makedev(अचिन्हित major, अचिन्हित minor);
बाह्य पूर्णांक os_falloc_punch(पूर्णांक fd, अचिन्हित दीर्घ दीर्घ offset, पूर्णांक count);
बाह्य पूर्णांक os_eventfd(अचिन्हित पूर्णांक initval, पूर्णांक flags);
बाह्य पूर्णांक os_sendmsg_fds(पूर्णांक fd, स्थिर व्योम *buf, अचिन्हित पूर्णांक len,
			  स्थिर पूर्णांक *fds, अचिन्हित पूर्णांक fds_num);
पूर्णांक os_poll(अचिन्हित पूर्णांक n, स्थिर पूर्णांक *fds);

/* start_up.c */
बाह्य व्योम os_early_checks(व्योम);
बाह्य व्योम os_check_bugs(व्योम);
बाह्य व्योम check_host_supports_tls(पूर्णांक *supports_tls, पूर्णांक *tls_min);

/* mem.c */
बाह्य पूर्णांक create_mem_file(अचिन्हित दीर्घ दीर्घ len);

/* process.c */
बाह्य अचिन्हित दीर्घ os_process_pc(पूर्णांक pid);
बाह्य पूर्णांक os_process_parent(पूर्णांक pid);
बाह्य व्योम os_alarm_process(पूर्णांक pid);
बाह्य व्योम os_stop_process(पूर्णांक pid);
बाह्य व्योम os_समाप्त_process(पूर्णांक pid, पूर्णांक reap_child);
बाह्य व्योम os_समाप्त_ptraced_process(पूर्णांक pid, पूर्णांक reap_child);

बाह्य पूर्णांक os_getpid(व्योम);
बाह्य पूर्णांक os_getpgrp(व्योम);

बाह्य व्योम init_new_thपढ़ो_संकेतs(व्योम);

बाह्य पूर्णांक os_map_memory(व्योम *virt, पूर्णांक fd, अचिन्हित दीर्घ दीर्घ off,
			 अचिन्हित दीर्घ len, पूर्णांक r, पूर्णांक w, पूर्णांक x);
बाह्य पूर्णांक os_protect_memory(व्योम *addr, अचिन्हित दीर्घ len,
			     पूर्णांक r, पूर्णांक w, पूर्णांक x);
बाह्य पूर्णांक os_unmap_memory(व्योम *addr, पूर्णांक len);
बाह्य पूर्णांक os_drop_memory(व्योम *addr, पूर्णांक length);
बाह्य पूर्णांक can_drop_memory(व्योम);
बाह्य व्योम os_flush_मानक_निकास(व्योम);
बाह्य पूर्णांक os_mincore(व्योम *addr, अचिन्हित दीर्घ len);

/* execvp.c */
बाह्य पूर्णांक execvp_noalloc(अक्षर *buf, स्थिर अक्षर *file, अक्षर *स्थिर argv[]);
/* helper.c */
बाह्य पूर्णांक run_helper(व्योम (*pre_exec)(व्योम *), व्योम *pre_data, अक्षर **argv);
बाह्य पूर्णांक run_helper_thपढ़ो(पूर्णांक (*proc)(व्योम *), व्योम *arg,
			     अचिन्हित पूर्णांक flags, अचिन्हित दीर्घ *stack_out);
बाह्य पूर्णांक helper_रुको(पूर्णांक pid);


/* umid.c */
बाह्य पूर्णांक umid_file_name(अक्षर *name, अक्षर *buf, पूर्णांक len);
बाह्य पूर्णांक set_umid(अक्षर *name);
बाह्य अक्षर *get_umid(व्योम);

/* संकेत.c */
बाह्य व्योम समयr_set_संकेत_handler(व्योम);
बाह्य व्योम set_sigstack(व्योम *sig_stack, पूर्णांक size);
बाह्य व्योम हटाओ_sigstack(व्योम);
बाह्य व्योम set_handler(पूर्णांक sig);
बाह्य व्योम send_sigio_to_self(व्योम);
बाह्य पूर्णांक change_sig(पूर्णांक संकेत, पूर्णांक on);
बाह्य व्योम block_संकेतs(व्योम);
बाह्य व्योम unblock_संकेतs(व्योम);
बाह्य पूर्णांक get_संकेतs(व्योम);
बाह्य पूर्णांक set_संकेतs(पूर्णांक enable);
बाह्य पूर्णांक set_संकेतs_trace(पूर्णांक enable);
बाह्य पूर्णांक os_is_संकेत_stack(व्योम);
बाह्य व्योम deliver_alarm(व्योम);
बाह्य व्योम रेजिस्टर_pm_wake_संकेत(व्योम);

/* util.c */
बाह्य व्योम stack_protections(अचिन्हित दीर्घ address);
बाह्य पूर्णांक raw(पूर्णांक fd);
बाह्य व्योम setup_machinename(अक्षर *machine_out);
बाह्य व्योम setup_hostinfo(अक्षर *buf, पूर्णांक len);
बाह्य व्योम os_dump_core(व्योम) __attribute__ ((noवापस));
बाह्य व्योम um_early_prपूर्णांकk(स्थिर अक्षर *s, अचिन्हित पूर्णांक n);
बाह्य व्योम os_fix_helper_संकेतs(व्योम);
बाह्य व्योम os_info(स्थिर अक्षर *fmt, ...)
	__attribute__ ((क्रमmat (म_लिखो, 1, 2)));
बाह्य व्योम os_warn(स्थिर अक्षर *fmt, ...)
	__attribute__ ((क्रमmat (म_लिखो, 1, 2)));

/* समय.c */
बाह्य व्योम os_idle_sleep(व्योम);
बाह्य पूर्णांक os_समयr_create(व्योम);
बाह्य पूर्णांक os_समयr_set_पूर्णांकerval(अचिन्हित दीर्घ दीर्घ nsecs);
बाह्य पूर्णांक os_समयr_one_shot(अचिन्हित दीर्घ दीर्घ nsecs);
बाह्य व्योम os_समयr_disable(व्योम);
बाह्य व्योम uml_idle_समयr(व्योम);
बाह्य दीर्घ दीर्घ os_persistent_घड़ी_emulation(व्योम);
बाह्य दीर्घ दीर्घ os_nsecs(व्योम);

/* skas/mem.c */
बाह्य दीर्घ run_syscall_stub(काष्ठा mm_id * mm_idp,
			     पूर्णांक syscall, अचिन्हित दीर्घ *args, दीर्घ expected,
			     व्योम **addr, पूर्णांक करोne);
बाह्य दीर्घ syscall_stub_data(काष्ठा mm_id * mm_idp,
			      अचिन्हित दीर्घ *data, पूर्णांक data_count,
			      व्योम **addr, व्योम **stub_addr);
बाह्य पूर्णांक map(काष्ठा mm_id * mm_idp, अचिन्हित दीर्घ virt,
	       अचिन्हित दीर्घ len, पूर्णांक prot, पूर्णांक phys_fd,
	       अचिन्हित दीर्घ दीर्घ offset, पूर्णांक करोne, व्योम **data);
बाह्य पूर्णांक unmap(काष्ठा mm_id * mm_idp, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
		 पूर्णांक करोne, व्योम **data);
बाह्य पूर्णांक protect(काष्ठा mm_id * mm_idp, अचिन्हित दीर्घ addr,
		   अचिन्हित दीर्घ len, अचिन्हित पूर्णांक prot, पूर्णांक करोne, व्योम **data);

/* skas/process.c */
बाह्य पूर्णांक is_skas_winch(पूर्णांक pid, पूर्णांक fd, व्योम *data);
बाह्य पूर्णांक start_userspace(अचिन्हित दीर्घ stub_stack);
बाह्य पूर्णांक copy_context_skas0(अचिन्हित दीर्घ stack, पूर्णांक pid);
बाह्य व्योम userspace(काष्ठा uml_pt_regs *regs, अचिन्हित दीर्घ *aux_fp_regs);
बाह्य पूर्णांक map_stub_pages(पूर्णांक fd, अचिन्हित दीर्घ code, अचिन्हित दीर्घ data,
			  अचिन्हित दीर्घ stack);
बाह्य व्योम new_thपढ़ो(व्योम *stack, लाँघ_बफ *buf, व्योम (*handler)(व्योम));
बाह्य व्योम चयन_thपढ़ोs(लाँघ_बफ *me, लाँघ_बफ *you);
बाह्य पूर्णांक start_idle_thपढ़ो(व्योम *stack, लाँघ_बफ *चयन_buf);
बाह्य व्योम initial_thपढ़ो_cb_skas(व्योम (*proc)(व्योम *),
				 व्योम *arg);
बाह्य व्योम halt_skas(व्योम);
बाह्य व्योम reboot_skas(व्योम);

/* irq.c */
बाह्य पूर्णांक os_रुकोing_क्रम_events_epoll(व्योम);
बाह्य व्योम *os_epoll_get_data_poपूर्णांकer(पूर्णांक index);
बाह्य पूर्णांक os_epoll_triggered(पूर्णांक index, पूर्णांक events);
बाह्य पूर्णांक os_event_mask(क्रमागत um_irq_type irq_type);
बाह्य पूर्णांक os_setup_epoll(व्योम);
बाह्य पूर्णांक os_add_epoll_fd(पूर्णांक events, पूर्णांक fd, व्योम *data);
बाह्य पूर्णांक os_mod_epoll_fd(पूर्णांक events, पूर्णांक fd, व्योम *data);
बाह्य पूर्णांक os_del_epoll_fd(पूर्णांक fd);
बाह्य व्योम os_set_ioignore(व्योम);
बाह्य व्योम os_बंद_epoll_fd(व्योम);
बाह्य व्योम um_irqs_suspend(व्योम);
बाह्य व्योम um_irqs_resume(व्योम);

/* sigio.c */
बाह्य पूर्णांक add_sigio_fd(पूर्णांक fd);
बाह्य पूर्णांक ignore_sigio_fd(पूर्णांक fd);
बाह्य व्योम maybe_sigio_broken(पूर्णांक fd);
बाह्य व्योम sigio_broken(पूर्णांक fd);
/*
 * unlocked versions क्रम IRQ controller code.
 *
 * This is safe because it's used at suspend/resume and nothing
 * अन्यथा is running.
 */
बाह्य पूर्णांक __add_sigio_fd(पूर्णांक fd);
बाह्य पूर्णांक __ignore_sigio_fd(पूर्णांक fd);

/* prctl.c */
बाह्य पूर्णांक os_arch_prctl(पूर्णांक pid, पूर्णांक option, अचिन्हित दीर्घ *arg2);

/* tty.c */
बाह्य पूर्णांक get_pty(व्योम);

/* sys-$ARCH/task_size.c */
बाह्य अचिन्हित दीर्घ os_get_top_address(व्योम);

दीर्घ syscall(दीर्घ number, ...);

/* irqflags tracing */
बाह्य व्योम block_संकेतs_trace(व्योम);
बाह्य व्योम unblock_संकेतs_trace(व्योम);
बाह्य व्योम um_trace_संकेतs_on(व्योम);
बाह्य व्योम um_trace_संकेतs_off(व्योम);

/* समय-travel */
बाह्य व्योम deliver_समय_प्रकारravel_irqs(व्योम);

#पूर्ण_अगर
