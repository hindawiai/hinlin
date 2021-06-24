<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * nexthops in net namespaces
 */

#अगर_अघोषित __NETNS_NEXTHOP_H__
#घोषणा __NETNS_NEXTHOP_H__

#समावेश <linux/rbtree.h>

काष्ठा netns_nexthop अणु
	काष्ठा rb_root		rb_root;	/* tree of nexthops by id */
	काष्ठा hlist_head	*devhash;	/* nexthops by device */

	अचिन्हित पूर्णांक		seq;		/* रक्षित by rtnl_mutex */
	u32			last_id_allocated;
	काष्ठा blocking_notअगरier_head notअगरier_chain;
पूर्ण;
#पूर्ण_अगर
