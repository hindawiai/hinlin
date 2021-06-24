<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * nodemanager.h
 *
 * Function prototypes
 *
 * Copyright (C) 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित O2CLUSTER_NODEMANAGER_H
#घोषणा O2CLUSTER_NODEMANAGER_H

#समावेश "ocfs2_nodemanager.h"

/* This totally करोesn't beदीर्घ here. */
#समावेश <linux/configfs.h>
#समावेश <linux/rbtree.h>

क्रमागत o2nm_fence_method अणु
	O2NM_FENCE_RESET	= 0,
	O2NM_FENCE_PANIC,
	O2NM_FENCE_METHODS,	/* Number of fence methods */
पूर्ण;

काष्ठा o2nm_node अणु
	spinlock_t		nd_lock;
	काष्ठा config_item	nd_item;
	अक्षर			nd_name[O2NM_MAX_NAME_LEN+1]; /* replace? */
	__u8			nd_num;
	/* only one address per node, as attributes, क्रम now. */
	__be32			nd_ipv4_address;
	__be16			nd_ipv4_port;
	काष्ठा rb_node		nd_ip_node;
	/* there can be only one local node क्रम now */
	पूर्णांक			nd_local;

	अचिन्हित दीर्घ		nd_set_attributes;
पूर्ण;

काष्ठा o2nm_cluster अणु
	काष्ठा config_group	cl_group;
	अचिन्हित		cl_has_local:1;
	u8			cl_local_node;
	rwlock_t		cl_nodes_lock;
	काष्ठा o2nm_node  	*cl_nodes[O2NM_MAX_NODES];
	काष्ठा rb_root		cl_node_ip_tree;
	अचिन्हित पूर्णांक		cl_idle_समयout_ms;
	अचिन्हित पूर्णांक		cl_keepalive_delay_ms;
	अचिन्हित पूर्णांक		cl_reconnect_delay_ms;
	क्रमागत o2nm_fence_method	cl_fence_method;

	/* this biपंचांगap is part of a hack क्रम disk biपंचांगap.. will go eventually. - zab */
	अचिन्हित दीर्घ	cl_nodes_biपंचांगap[BITS_TO_LONGS(O2NM_MAX_NODES)];
पूर्ण;

बाह्य काष्ठा o2nm_cluster *o2nm_single_cluster;

u8 o2nm_this_node(व्योम);

पूर्णांक o2nm_configured_node_map(अचिन्हित दीर्घ *map, अचिन्हित bytes);
काष्ठा o2nm_node *o2nm_get_node_by_num(u8 node_num);
काष्ठा o2nm_node *o2nm_get_node_by_ip(__be32 addr);
व्योम o2nm_node_get(काष्ठा o2nm_node *node);
व्योम o2nm_node_put(काष्ठा o2nm_node *node);

पूर्णांक o2nm_depend_item(काष्ठा config_item *item);
व्योम o2nm_undepend_item(काष्ठा config_item *item);
पूर्णांक o2nm_depend_this_node(व्योम);
व्योम o2nm_undepend_this_node(व्योम);

#पूर्ण_अगर /* O2CLUSTER_NODEMANAGER_H */
