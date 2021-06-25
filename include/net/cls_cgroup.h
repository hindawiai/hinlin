<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * cls_cgroup.h			Control Group Classअगरier
 *
 * Authors:	Thomas Graf <tgraf@suug.ch>
 */

#अगर_अघोषित _NET_CLS_CGROUP_H
#घोषणा _NET_CLS_CGROUP_H

#समावेश <linux/cgroup.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/rcupdate.h>
#समावेश <net/sock.h>
#समावेश <net/inet_sock.h>

#अगर_घोषित CONFIG_CGROUP_NET_CLASSID
काष्ठा cgroup_cls_state अणु
	काष्ठा cgroup_subsys_state css;
	u32 classid;
पूर्ण;

काष्ठा cgroup_cls_state *task_cls_state(काष्ठा task_काष्ठा *p);

अटल अंतरभूत u32 task_cls_classid(काष्ठा task_काष्ठा *p)
अणु
	u32 classid;

	अगर (in_पूर्णांकerrupt())
		वापस 0;

	rcu_पढ़ो_lock();
	classid = container_of(task_css(p, net_cls_cgrp_id),
			       काष्ठा cgroup_cls_state, css)->classid;
	rcu_पढ़ो_unlock();

	वापस classid;
पूर्ण

अटल अंतरभूत व्योम sock_update_classid(काष्ठा sock_cgroup_data *skcd)
अणु
	u32 classid;

	classid = task_cls_classid(current);
	sock_cgroup_set_classid(skcd, classid);
पूर्ण

अटल अंतरभूत u32 __task_get_classid(काष्ठा task_काष्ठा *task)
अणु
	वापस task_cls_state(task)->classid;
पूर्ण

अटल अंतरभूत u32 task_get_classid(स्थिर काष्ठा sk_buff *skb)
अणु
	u32 classid = __task_get_classid(current);

	/* Due to the nature of the classअगरier it is required to ignore all
	 * packets originating from softirq context as accessing `current'
	 * would lead to false results.
	 *
	 * This test assumes that all callers of dev_queue_xmit() explicitly
	 * disable bh. Knowing this, it is possible to detect softirq based
	 * calls by looking at the number of nested bh disable calls because
	 * softirqs always disables bh.
	 */
	अगर (in_serving_softirq()) अणु
		काष्ठा sock *sk = skb_to_full_sk(skb);

		/* If there is an sock_cgroup_classid we'll use that. */
		अगर (!sk || !sk_fullsock(sk))
			वापस 0;

		classid = sock_cgroup_classid(&sk->sk_cgrp_data);
	पूर्ण

	वापस classid;
पूर्ण
#अन्यथा /* !CONFIG_CGROUP_NET_CLASSID */
अटल अंतरभूत व्योम sock_update_classid(काष्ठा sock_cgroup_data *skcd)
अणु
पूर्ण

अटल अंतरभूत u32 task_get_classid(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_CGROUP_NET_CLASSID */
#पूर्ण_अगर  /* _NET_CLS_CGROUP_H */
