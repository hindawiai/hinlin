<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_BPFILTER_H
#घोषणा _LINUX_BPFILTER_H

#समावेश <uapi/linux/bpfilter.h>
#समावेश <linux/usermode_driver.h>
#समावेश <linux/sockptr.h>

काष्ठा sock;
पूर्णांक bpfilter_ip_set_sockopt(काष्ठा sock *sk, पूर्णांक optname, sockptr_t optval,
			    अचिन्हित पूर्णांक optlen);
पूर्णांक bpfilter_ip_get_sockopt(काष्ठा sock *sk, पूर्णांक optname, अक्षर __user *optval,
			    पूर्णांक __user *optlen);
व्योम bpfilter_umh_cleanup(काष्ठा umd_info *info);

काष्ठा bpfilter_umh_ops अणु
	काष्ठा umd_info info;
	/* since ip_माला_लोockopt() can run in parallel, serialize access to umh */
	काष्ठा mutex lock;
	पूर्णांक (*sockopt)(काष्ठा sock *sk, पूर्णांक optname, sockptr_t optval,
		       अचिन्हित पूर्णांक optlen, bool is_set);
	पूर्णांक (*start)(व्योम);
पूर्ण;
बाह्य काष्ठा bpfilter_umh_ops bpfilter_ops;
#पूर्ण_अगर
