<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * netprio_cgroup.h			Control Group Priority set
 *
 * Authors:	Neil Horman <nhorman@tuxdriver.com>
 */

#अगर_अघोषित _NETPRIO_CGROUP_H
#घोषणा _NETPRIO_CGROUP_H

#समावेश <linux/cgroup.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/rcupdate.h>

#अगर IS_ENABLED(CONFIG_CGROUP_NET_PRIO)
काष्ठा netprio_map अणु
	काष्ठा rcu_head rcu;
	u32 priomap_len;
	u32 priomap[];
पूर्ण;

अटल अंतरभूत u32 task_netprioidx(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा cgroup_subsys_state *css;
	u32 idx;

	rcu_पढ़ो_lock();
	css = task_css(p, net_prio_cgrp_id);
	idx = css->id;
	rcu_पढ़ो_unlock();
	वापस idx;
पूर्ण

अटल अंतरभूत व्योम sock_update_netprioidx(काष्ठा sock_cgroup_data *skcd)
अणु
	अगर (in_पूर्णांकerrupt())
		वापस;

	sock_cgroup_set_prioidx(skcd, task_netprioidx(current));
पूर्ण

#अन्यथा /* !CONFIG_CGROUP_NET_PRIO */

अटल अंतरभूत u32 task_netprioidx(काष्ठा task_काष्ठा *p)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sock_update_netprioidx(काष्ठा sock_cgroup_data *skcd)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_CGROUP_NET_PRIO */
#पूर्ण_अगर  /* _NET_CLS_CGROUP_H */
