<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LOCKD_NETNS_H__
#घोषणा __LOCKD_NETNS_H__

#समावेश <linux/fs.h>
#समावेश <net/netns/generic.h>

काष्ठा lockd_net अणु
	अचिन्हित पूर्णांक nlmsvc_users;
	अचिन्हित दीर्घ next_gc;
	अचिन्हित दीर्घ nrhosts;

	काष्ठा delayed_work grace_period_end;
	काष्ठा lock_manager lockd_manager;

	काष्ठा list_head nsm_handles;
पूर्ण;

बाह्य अचिन्हित पूर्णांक lockd_net_id;

#पूर्ण_अगर
