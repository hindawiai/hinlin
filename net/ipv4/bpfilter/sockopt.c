<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/bpfilter.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <linux/रुको.h>
#समावेश <linux/kmod.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>

काष्ठा bpfilter_umh_ops bpfilter_ops;
EXPORT_SYMBOL_GPL(bpfilter_ops);

व्योम bpfilter_umh_cleanup(काष्ठा umd_info *info)
अणु
	fput(info->pipe_to_umh);
	fput(info->pipe_from_umh);
	put_pid(info->tgid);
	info->tgid = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(bpfilter_umh_cleanup);

अटल पूर्णांक bpfilter_mbox_request(काष्ठा sock *sk, पूर्णांक optname, sockptr_t optval,
				 अचिन्हित पूर्णांक optlen, bool is_set)
अणु
	पूर्णांक err;
	mutex_lock(&bpfilter_ops.lock);
	अगर (!bpfilter_ops.sockopt) अणु
		mutex_unlock(&bpfilter_ops.lock);
		request_module("bpfilter");
		mutex_lock(&bpfilter_ops.lock);

		अगर (!bpfilter_ops.sockopt) अणु
			err = -ENOPROTOOPT;
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (bpfilter_ops.info.tgid &&
	    thपढ़ो_group_निकासed(bpfilter_ops.info.tgid))
		bpfilter_umh_cleanup(&bpfilter_ops.info);

	अगर (!bpfilter_ops.info.tgid) अणु
		err = bpfilter_ops.start();
		अगर (err)
			जाओ out;
	पूर्ण
	err = bpfilter_ops.sockopt(sk, optname, optval, optlen, is_set);
out:
	mutex_unlock(&bpfilter_ops.lock);
	वापस err;
पूर्ण

पूर्णांक bpfilter_ip_set_sockopt(काष्ठा sock *sk, पूर्णांक optname, sockptr_t optval,
			    अचिन्हित पूर्णांक optlen)
अणु
	वापस bpfilter_mbox_request(sk, optname, optval, optlen, true);
पूर्ण

पूर्णांक bpfilter_ip_get_sockopt(काष्ठा sock *sk, पूर्णांक optname, अक्षर __user *optval,
			    पूर्णांक __user *optlen)
अणु
	पूर्णांक len;

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	वापस bpfilter_mbox_request(sk, optname, USER_SOCKPTR(optval), len,
				     false);
पूर्ण

अटल पूर्णांक __init bpfilter_sockopt_init(व्योम)
अणु
	mutex_init(&bpfilter_ops.lock);
	bpfilter_ops.info.tgid = शून्य;
	bpfilter_ops.info.driver_name = "bpfilter_umh";

	वापस 0;
पूर्ण
device_initcall(bpfilter_sockopt_init);
