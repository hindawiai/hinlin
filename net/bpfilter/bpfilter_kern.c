<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/umh.h>
#समावेश <linux/bpfilter.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश "msgfmt.h"

बाह्य अक्षर bpfilter_umh_start;
बाह्य अक्षर bpfilter_umh_end;

अटल व्योम shutकरोwn_umh(व्योम)
अणु
	काष्ठा umd_info *info = &bpfilter_ops.info;
	काष्ठा pid *tgid = info->tgid;

	अगर (tgid) अणु
		समाप्त_pid(tgid, SIGKILL, 1);
		रुको_event(tgid->रुको_pidfd, thपढ़ो_group_निकासed(tgid));
		bpfilter_umh_cleanup(info);
	पूर्ण
पूर्ण

अटल व्योम __stop_umh(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_INET))
		shutकरोwn_umh();
पूर्ण

अटल पूर्णांक bpfilter_send_req(काष्ठा mbox_request *req)
अणु
	काष्ठा mbox_reply reply;
	loff_t pos = 0;
	sमाप_प्रकार n;

	अगर (!bpfilter_ops.info.tgid)
		वापस -EFAULT;
	pos = 0;
	n = kernel_ग_लिखो(bpfilter_ops.info.pipe_to_umh, req, माप(*req),
			   &pos);
	अगर (n != माप(*req)) अणु
		pr_err("write fail %zd\n", n);
		जाओ stop;
	पूर्ण
	pos = 0;
	n = kernel_पढ़ो(bpfilter_ops.info.pipe_from_umh, &reply, माप(reply),
			&pos);
	अगर (n != माप(reply)) अणु
		pr_err("read fail %zd\n", n);
		जाओ stop;
	पूर्ण
	वापस reply.status;
stop:
	__stop_umh();
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक bpfilter_process_sockopt(काष्ठा sock *sk, पूर्णांक optname,
				    sockptr_t optval, अचिन्हित पूर्णांक optlen,
				    bool is_set)
अणु
	काष्ठा mbox_request req = अणु
		.is_set		= is_set,
		.pid		= current->pid,
		.cmd		= optname,
		.addr		= (uपूर्णांकptr_t)optval.user,
		.len		= optlen,
	पूर्ण;
	अगर (uaccess_kernel() || sockptr_is_kernel(optval)) अणु
		pr_err("kernel access not supported\n");
		वापस -EFAULT;
	पूर्ण
	वापस bpfilter_send_req(&req);
पूर्ण

अटल पूर्णांक start_umh(व्योम)
अणु
	काष्ठा mbox_request req = अणु .pid = current->pid पूर्ण;
	पूर्णांक err;

	/* विभाजन usermode process */
	err = विभाजन_usermode_driver(&bpfilter_ops.info);
	अगर (err)
		वापस err;
	pr_info("Loaded bpfilter_umh pid %d\n", pid_nr(bpfilter_ops.info.tgid));

	/* health check that usermode process started correctly */
	अगर (bpfilter_send_req(&req) != 0) अणु
		shutकरोwn_umh();
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init load_umh(व्योम)
अणु
	पूर्णांक err;

	err = umd_load_blob(&bpfilter_ops.info,
			    &bpfilter_umh_start,
			    &bpfilter_umh_end - &bpfilter_umh_start);
	अगर (err)
		वापस err;

	mutex_lock(&bpfilter_ops.lock);
	err = start_umh();
	अगर (!err && IS_ENABLED(CONFIG_INET)) अणु
		bpfilter_ops.sockopt = &bpfilter_process_sockopt;
		bpfilter_ops.start = &start_umh;
	पूर्ण
	mutex_unlock(&bpfilter_ops.lock);
	अगर (err)
		umd_unload_blob(&bpfilter_ops.info);
	वापस err;
पूर्ण

अटल व्योम __निकास fini_umh(व्योम)
अणु
	mutex_lock(&bpfilter_ops.lock);
	अगर (IS_ENABLED(CONFIG_INET)) अणु
		shutकरोwn_umh();
		bpfilter_ops.start = शून्य;
		bpfilter_ops.sockopt = शून्य;
	पूर्ण
	mutex_unlock(&bpfilter_ops.lock);

	umd_unload_blob(&bpfilter_ops.info);
पूर्ण
module_init(load_umh);
module_निकास(fini_umh);
MODULE_LICENSE("GPL");
