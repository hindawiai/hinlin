<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) Sistina Software, Inc.  1997-2003  All rights reserved.
**  Copyright (C) 2004-2011 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/configfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/dlmस्थिरants.h>
#समावेश <net/ipv6.h>
#समावेश <net/sock.h>

#समावेश "config.h"
#समावेश "lowcomms.h"

/*
 * /config/dlm/<cluster>/spaces/<space>/nodes/<node>/nodeid
 * /config/dlm/<cluster>/spaces/<space>/nodes/<node>/weight
 * /config/dlm/<cluster>/comms/<comm>/nodeid
 * /config/dlm/<cluster>/comms/<comm>/local
 * /config/dlm/<cluster>/comms/<comm>/addr      (ग_लिखो only)
 * /config/dlm/<cluster>/comms/<comm>/addr_list (पढ़ो only)
 * The <cluster> level is useless, but I haven't figured out how to aव्योम it.
 */

अटल काष्ठा config_group *space_list;
अटल काष्ठा config_group *comm_list;
अटल काष्ठा dlm_comm *local_comm;
अटल uपूर्णांक32_t dlm_comm_count;

काष्ठा dlm_clusters;
काष्ठा dlm_cluster;
काष्ठा dlm_spaces;
काष्ठा dlm_space;
काष्ठा dlm_comms;
काष्ठा dlm_comm;
काष्ठा dlm_nodes;
काष्ठा dlm_node;

अटल काष्ठा config_group *make_cluster(काष्ठा config_group *, स्थिर अक्षर *);
अटल व्योम drop_cluster(काष्ठा config_group *, काष्ठा config_item *);
अटल व्योम release_cluster(काष्ठा config_item *);
अटल काष्ठा config_group *make_space(काष्ठा config_group *, स्थिर अक्षर *);
अटल व्योम drop_space(काष्ठा config_group *, काष्ठा config_item *);
अटल व्योम release_space(काष्ठा config_item *);
अटल काष्ठा config_item *make_comm(काष्ठा config_group *, स्थिर अक्षर *);
अटल व्योम drop_comm(काष्ठा config_group *, काष्ठा config_item *);
अटल व्योम release_comm(काष्ठा config_item *);
अटल काष्ठा config_item *make_node(काष्ठा config_group *, स्थिर अक्षर *);
अटल व्योम drop_node(काष्ठा config_group *, काष्ठा config_item *);
अटल व्योम release_node(काष्ठा config_item *);

अटल काष्ठा configfs_attribute *comm_attrs[];
अटल काष्ठा configfs_attribute *node_attrs[];

काष्ठा dlm_cluster अणु
	काष्ठा config_group group;
	अचिन्हित पूर्णांक cl_tcp_port;
	अचिन्हित पूर्णांक cl_buffer_size;
	अचिन्हित पूर्णांक cl_rsbtbl_size;
	अचिन्हित पूर्णांक cl_recover_समयr;
	अचिन्हित पूर्णांक cl_toss_secs;
	अचिन्हित पूर्णांक cl_scan_secs;
	अचिन्हित पूर्णांक cl_log_debug;
	अचिन्हित पूर्णांक cl_log_info;
	अचिन्हित पूर्णांक cl_protocol;
	अचिन्हित पूर्णांक cl_mark;
	अचिन्हित पूर्णांक cl_समयwarn_cs;
	अचिन्हित पूर्णांक cl_रुकोwarn_us;
	अचिन्हित पूर्णांक cl_new_rsb_count;
	अचिन्हित पूर्णांक cl_recover_callbacks;
	अक्षर cl_cluster_name[DLM_LOCKSPACE_LEN];
पूर्ण;

अटल काष्ठा dlm_cluster *config_item_to_cluster(काष्ठा config_item *i)
अणु
	वापस i ? container_of(to_config_group(i), काष्ठा dlm_cluster, group) :
		   शून्य;
पूर्ण

क्रमागत अणु
	CLUSTER_ATTR_TCP_PORT = 0,
	CLUSTER_ATTR_BUFFER_SIZE,
	CLUSTER_ATTR_RSBTBL_SIZE,
	CLUSTER_ATTR_RECOVER_TIMER,
	CLUSTER_ATTR_TOSS_SECS,
	CLUSTER_ATTR_SCAN_SECS,
	CLUSTER_ATTR_LOG_DEBUG,
	CLUSTER_ATTR_LOG_INFO,
	CLUSTER_ATTR_PROTOCOL,
	CLUSTER_ATTR_MARK,
	CLUSTER_ATTR_TIMEWARN_CS,
	CLUSTER_ATTR_WAITWARN_US,
	CLUSTER_ATTR_NEW_RSB_COUNT,
	CLUSTER_ATTR_RECOVER_CALLBACKS,
	CLUSTER_ATTR_CLUSTER_NAME,
पूर्ण;

अटल sमाप_प्रकार cluster_cluster_name_show(काष्ठा config_item *item, अक्षर *buf)
अणु
	काष्ठा dlm_cluster *cl = config_item_to_cluster(item);
	वापस प्र_लिखो(buf, "%s\n", cl->cl_cluster_name);
पूर्ण

अटल sमाप_प्रकार cluster_cluster_name_store(काष्ठा config_item *item,
					  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा dlm_cluster *cl = config_item_to_cluster(item);

	strlcpy(dlm_config.ci_cluster_name, buf,
				माप(dlm_config.ci_cluster_name));
	strlcpy(cl->cl_cluster_name, buf, माप(cl->cl_cluster_name));
	वापस len;
पूर्ण

CONFIGFS_ATTR(cluster_, cluster_name);

अटल sमाप_प्रकार cluster_set(काष्ठा dlm_cluster *cl, अचिन्हित पूर्णांक *cl_field,
			   पूर्णांक *info_field, पूर्णांक (*check_cb)(अचिन्हित पूर्णांक x),
			   स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक x;
	पूर्णांक rc;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	rc = kstrtouपूर्णांक(buf, 0, &x);
	अगर (rc)
		वापस rc;

	अगर (check_cb) अणु
		rc = check_cb(x);
		अगर (rc)
			वापस rc;
	पूर्ण

	*cl_field = x;
	*info_field = x;

	वापस len;
पूर्ण

#घोषणा CLUSTER_ATTR(name, check_cb)                                          \
अटल sमाप_प्रकार cluster_##name##_store(काष्ठा config_item *item, \
		स्थिर अक्षर *buf, माप_प्रकार len) \
अणु                                                                             \
	काष्ठा dlm_cluster *cl = config_item_to_cluster(item);		      \
	वापस cluster_set(cl, &cl->cl_##name, &dlm_config.ci_##name,         \
			   check_cb, buf, len);                               \
पूर्ण                                                                             \
अटल sमाप_प्रकार cluster_##name##_show(काष्ठा config_item *item, अक्षर *buf)     \
अणु                                                                             \
	काष्ठा dlm_cluster *cl = config_item_to_cluster(item);		      \
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", cl->cl_##name);               \
पूर्ण                                                                             \
CONFIGFS_ATTR(cluster_, name);

अटल पूर्णांक dlm_check_protocol_and_dlm_running(अचिन्हित पूर्णांक x)
अणु
	चयन (x) अणु
	हाल 0:
		/* TCP */
		अवरोध;
	हाल 1:
		/* SCTP */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (dlm_allow_conn)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल पूर्णांक dlm_check_zero_and_dlm_running(अचिन्हित पूर्णांक x)
अणु
	अगर (!x)
		वापस -EINVAL;

	अगर (dlm_allow_conn)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल पूर्णांक dlm_check_zero(अचिन्हित पूर्णांक x)
अणु
	अगर (!x)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक dlm_check_buffer_size(अचिन्हित पूर्णांक x)
अणु
	अगर (x < DEFAULT_BUFFER_SIZE)
		वापस -EINVAL;

	वापस 0;
पूर्ण

CLUSTER_ATTR(tcp_port, dlm_check_zero_and_dlm_running);
CLUSTER_ATTR(buffer_size, dlm_check_buffer_size);
CLUSTER_ATTR(rsbtbl_size, dlm_check_zero);
CLUSTER_ATTR(recover_समयr, dlm_check_zero);
CLUSTER_ATTR(toss_secs, dlm_check_zero);
CLUSTER_ATTR(scan_secs, dlm_check_zero);
CLUSTER_ATTR(log_debug, शून्य);
CLUSTER_ATTR(log_info, शून्य);
CLUSTER_ATTR(protocol, dlm_check_protocol_and_dlm_running);
CLUSTER_ATTR(mark, शून्य);
CLUSTER_ATTR(समयwarn_cs, dlm_check_zero);
CLUSTER_ATTR(रुकोwarn_us, शून्य);
CLUSTER_ATTR(new_rsb_count, शून्य);
CLUSTER_ATTR(recover_callbacks, शून्य);

अटल काष्ठा configfs_attribute *cluster_attrs[] = अणु
	[CLUSTER_ATTR_TCP_PORT] = &cluster_attr_tcp_port,
	[CLUSTER_ATTR_BUFFER_SIZE] = &cluster_attr_buffer_size,
	[CLUSTER_ATTR_RSBTBL_SIZE] = &cluster_attr_rsbtbl_size,
	[CLUSTER_ATTR_RECOVER_TIMER] = &cluster_attr_recover_समयr,
	[CLUSTER_ATTR_TOSS_SECS] = &cluster_attr_toss_secs,
	[CLUSTER_ATTR_SCAN_SECS] = &cluster_attr_scan_secs,
	[CLUSTER_ATTR_LOG_DEBUG] = &cluster_attr_log_debug,
	[CLUSTER_ATTR_LOG_INFO] = &cluster_attr_log_info,
	[CLUSTER_ATTR_PROTOCOL] = &cluster_attr_protocol,
	[CLUSTER_ATTR_MARK] = &cluster_attr_mark,
	[CLUSTER_ATTR_TIMEWARN_CS] = &cluster_attr_समयwarn_cs,
	[CLUSTER_ATTR_WAITWARN_US] = &cluster_attr_रुकोwarn_us,
	[CLUSTER_ATTR_NEW_RSB_COUNT] = &cluster_attr_new_rsb_count,
	[CLUSTER_ATTR_RECOVER_CALLBACKS] = &cluster_attr_recover_callbacks,
	[CLUSTER_ATTR_CLUSTER_NAME] = &cluster_attr_cluster_name,
	शून्य,
पूर्ण;

क्रमागत अणु
	COMM_ATTR_NODEID = 0,
	COMM_ATTR_LOCAL,
	COMM_ATTR_ADDR,
	COMM_ATTR_ADDR_LIST,
	COMM_ATTR_MARK,
पूर्ण;

क्रमागत अणु
	NODE_ATTR_NODEID = 0,
	NODE_ATTR_WEIGHT,
पूर्ण;

काष्ठा dlm_clusters अणु
	काष्ठा configfs_subप्रणाली subsys;
पूर्ण;

काष्ठा dlm_spaces अणु
	काष्ठा config_group ss_group;
पूर्ण;

काष्ठा dlm_space अणु
	काष्ठा config_group group;
	काष्ठा list_head members;
	काष्ठा mutex members_lock;
	पूर्णांक members_count;
	काष्ठा dlm_nodes *nds;
पूर्ण;

काष्ठा dlm_comms अणु
	काष्ठा config_group cs_group;
पूर्ण;

काष्ठा dlm_comm अणु
	काष्ठा config_item item;
	पूर्णांक seq;
	पूर्णांक nodeid;
	पूर्णांक local;
	पूर्णांक addr_count;
	अचिन्हित पूर्णांक mark;
	काष्ठा sockaddr_storage *addr[DLM_MAX_ADDR_COUNT];
पूर्ण;

काष्ठा dlm_nodes अणु
	काष्ठा config_group ns_group;
पूर्ण;

काष्ठा dlm_node अणु
	काष्ठा config_item item;
	काष्ठा list_head list; /* space->members */
	पूर्णांक nodeid;
	पूर्णांक weight;
	पूर्णांक new;
	पूर्णांक comm_seq; /* copy of cm->seq when nd->nodeid is set */
पूर्ण;

अटल काष्ठा configfs_group_operations clusters_ops = अणु
	.make_group = make_cluster,
	.drop_item = drop_cluster,
पूर्ण;

अटल काष्ठा configfs_item_operations cluster_ops = अणु
	.release = release_cluster,
पूर्ण;

अटल काष्ठा configfs_group_operations spaces_ops = अणु
	.make_group = make_space,
	.drop_item = drop_space,
पूर्ण;

अटल काष्ठा configfs_item_operations space_ops = अणु
	.release = release_space,
पूर्ण;

अटल काष्ठा configfs_group_operations comms_ops = अणु
	.make_item = make_comm,
	.drop_item = drop_comm,
पूर्ण;

अटल काष्ठा configfs_item_operations comm_ops = अणु
	.release = release_comm,
पूर्ण;

अटल काष्ठा configfs_group_operations nodes_ops = अणु
	.make_item = make_node,
	.drop_item = drop_node,
पूर्ण;

अटल काष्ठा configfs_item_operations node_ops = अणु
	.release = release_node,
पूर्ण;

अटल स्थिर काष्ठा config_item_type clusters_type = अणु
	.ct_group_ops = &clusters_ops,
	.ct_owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा config_item_type cluster_type = अणु
	.ct_item_ops = &cluster_ops,
	.ct_attrs = cluster_attrs,
	.ct_owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा config_item_type spaces_type = अणु
	.ct_group_ops = &spaces_ops,
	.ct_owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा config_item_type space_type = अणु
	.ct_item_ops = &space_ops,
	.ct_owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा config_item_type comms_type = अणु
	.ct_group_ops = &comms_ops,
	.ct_owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा config_item_type comm_type = अणु
	.ct_item_ops = &comm_ops,
	.ct_attrs = comm_attrs,
	.ct_owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा config_item_type nodes_type = अणु
	.ct_group_ops = &nodes_ops,
	.ct_owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा config_item_type node_type = अणु
	.ct_item_ops = &node_ops,
	.ct_attrs = node_attrs,
	.ct_owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा dlm_space *config_item_to_space(काष्ठा config_item *i)
अणु
	वापस i ? container_of(to_config_group(i), काष्ठा dlm_space, group) :
		   शून्य;
पूर्ण

अटल काष्ठा dlm_comm *config_item_to_comm(काष्ठा config_item *i)
अणु
	वापस i ? container_of(i, काष्ठा dlm_comm, item) : शून्य;
पूर्ण

अटल काष्ठा dlm_node *config_item_to_node(काष्ठा config_item *i)
अणु
	वापस i ? container_of(i, काष्ठा dlm_node, item) : शून्य;
पूर्ण

अटल काष्ठा config_group *make_cluster(काष्ठा config_group *g,
					 स्थिर अक्षर *name)
अणु
	काष्ठा dlm_cluster *cl = शून्य;
	काष्ठा dlm_spaces *sps = शून्य;
	काष्ठा dlm_comms *cms = शून्य;

	cl = kzalloc(माप(काष्ठा dlm_cluster), GFP_NOFS);
	sps = kzalloc(माप(काष्ठा dlm_spaces), GFP_NOFS);
	cms = kzalloc(माप(काष्ठा dlm_comms), GFP_NOFS);

	अगर (!cl || !sps || !cms)
		जाओ fail;

	config_group_init_type_name(&cl->group, name, &cluster_type);
	config_group_init_type_name(&sps->ss_group, "spaces", &spaces_type);
	config_group_init_type_name(&cms->cs_group, "comms", &comms_type);

	configfs_add_शेष_group(&sps->ss_group, &cl->group);
	configfs_add_शेष_group(&cms->cs_group, &cl->group);

	cl->cl_tcp_port = dlm_config.ci_tcp_port;
	cl->cl_buffer_size = dlm_config.ci_buffer_size;
	cl->cl_rsbtbl_size = dlm_config.ci_rsbtbl_size;
	cl->cl_recover_समयr = dlm_config.ci_recover_समयr;
	cl->cl_toss_secs = dlm_config.ci_toss_secs;
	cl->cl_scan_secs = dlm_config.ci_scan_secs;
	cl->cl_log_debug = dlm_config.ci_log_debug;
	cl->cl_log_info = dlm_config.ci_log_info;
	cl->cl_protocol = dlm_config.ci_protocol;
	cl->cl_समयwarn_cs = dlm_config.ci_समयwarn_cs;
	cl->cl_रुकोwarn_us = dlm_config.ci_रुकोwarn_us;
	cl->cl_new_rsb_count = dlm_config.ci_new_rsb_count;
	cl->cl_recover_callbacks = dlm_config.ci_recover_callbacks;
	स_नकल(cl->cl_cluster_name, dlm_config.ci_cluster_name,
	       DLM_LOCKSPACE_LEN);

	space_list = &sps->ss_group;
	comm_list = &cms->cs_group;
	वापस &cl->group;

 fail:
	kमुक्त(cl);
	kमुक्त(sps);
	kमुक्त(cms);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल व्योम drop_cluster(काष्ठा config_group *g, काष्ठा config_item *i)
अणु
	काष्ठा dlm_cluster *cl = config_item_to_cluster(i);

	configfs_हटाओ_शेष_groups(&cl->group);

	space_list = शून्य;
	comm_list = शून्य;

	config_item_put(i);
पूर्ण

अटल व्योम release_cluster(काष्ठा config_item *i)
अणु
	काष्ठा dlm_cluster *cl = config_item_to_cluster(i);
	kमुक्त(cl);
पूर्ण

अटल काष्ठा config_group *make_space(काष्ठा config_group *g, स्थिर अक्षर *name)
अणु
	काष्ठा dlm_space *sp = शून्य;
	काष्ठा dlm_nodes *nds = शून्य;

	sp = kzalloc(माप(काष्ठा dlm_space), GFP_NOFS);
	nds = kzalloc(माप(काष्ठा dlm_nodes), GFP_NOFS);

	अगर (!sp || !nds)
		जाओ fail;

	config_group_init_type_name(&sp->group, name, &space_type);

	config_group_init_type_name(&nds->ns_group, "nodes", &nodes_type);
	configfs_add_शेष_group(&nds->ns_group, &sp->group);

	INIT_LIST_HEAD(&sp->members);
	mutex_init(&sp->members_lock);
	sp->members_count = 0;
	sp->nds = nds;
	वापस &sp->group;

 fail:
	kमुक्त(sp);
	kमुक्त(nds);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल व्योम drop_space(काष्ठा config_group *g, काष्ठा config_item *i)
अणु
	काष्ठा dlm_space *sp = config_item_to_space(i);

	/* निश्चित list_empty(&sp->members) */

	configfs_हटाओ_शेष_groups(&sp->group);
	config_item_put(i);
पूर्ण

अटल व्योम release_space(काष्ठा config_item *i)
अणु
	काष्ठा dlm_space *sp = config_item_to_space(i);
	kमुक्त(sp->nds);
	kमुक्त(sp);
पूर्ण

अटल काष्ठा config_item *make_comm(काष्ठा config_group *g, स्थिर अक्षर *name)
अणु
	काष्ठा dlm_comm *cm;

	cm = kzalloc(माप(काष्ठा dlm_comm), GFP_NOFS);
	अगर (!cm)
		वापस ERR_PTR(-ENOMEM);

	config_item_init_type_name(&cm->item, name, &comm_type);

	cm->seq = dlm_comm_count++;
	अगर (!cm->seq)
		cm->seq = dlm_comm_count++;

	cm->nodeid = -1;
	cm->local = 0;
	cm->addr_count = 0;
	cm->mark = 0;
	वापस &cm->item;
पूर्ण

अटल व्योम drop_comm(काष्ठा config_group *g, काष्ठा config_item *i)
अणु
	काष्ठा dlm_comm *cm = config_item_to_comm(i);
	अगर (local_comm == cm)
		local_comm = शून्य;
	dlm_lowcomms_बंद(cm->nodeid);
	जबतक (cm->addr_count--)
		kमुक्त(cm->addr[cm->addr_count]);
	config_item_put(i);
पूर्ण

अटल व्योम release_comm(काष्ठा config_item *i)
अणु
	काष्ठा dlm_comm *cm = config_item_to_comm(i);
	kमुक्त(cm);
पूर्ण

अटल काष्ठा config_item *make_node(काष्ठा config_group *g, स्थिर अक्षर *name)
अणु
	काष्ठा dlm_space *sp = config_item_to_space(g->cg_item.ci_parent);
	काष्ठा dlm_node *nd;

	nd = kzalloc(माप(काष्ठा dlm_node), GFP_NOFS);
	अगर (!nd)
		वापस ERR_PTR(-ENOMEM);

	config_item_init_type_name(&nd->item, name, &node_type);
	nd->nodeid = -1;
	nd->weight = 1;  /* शेष weight of 1 अगर none is set */
	nd->new = 1;     /* set to 0 once it's been पढ़ो by dlm_nodeid_list() */

	mutex_lock(&sp->members_lock);
	list_add(&nd->list, &sp->members);
	sp->members_count++;
	mutex_unlock(&sp->members_lock);

	वापस &nd->item;
पूर्ण

अटल व्योम drop_node(काष्ठा config_group *g, काष्ठा config_item *i)
अणु
	काष्ठा dlm_space *sp = config_item_to_space(g->cg_item.ci_parent);
	काष्ठा dlm_node *nd = config_item_to_node(i);

	mutex_lock(&sp->members_lock);
	list_del(&nd->list);
	sp->members_count--;
	mutex_unlock(&sp->members_lock);

	config_item_put(i);
पूर्ण

अटल व्योम release_node(काष्ठा config_item *i)
अणु
	काष्ठा dlm_node *nd = config_item_to_node(i);
	kमुक्त(nd);
पूर्ण

अटल काष्ठा dlm_clusters clusters_root = अणु
	.subsys = अणु
		.su_group = अणु
			.cg_item = अणु
				.ci_namebuf = "dlm",
				.ci_type = &clusters_type,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

पूर्णांक __init dlm_config_init(व्योम)
अणु
	config_group_init(&clusters_root.subsys.su_group);
	mutex_init(&clusters_root.subsys.su_mutex);
	वापस configfs_रेजिस्टर_subप्रणाली(&clusters_root.subsys);
पूर्ण

व्योम dlm_config_निकास(व्योम)
अणु
	configfs_unरेजिस्टर_subप्रणाली(&clusters_root.subsys);
पूर्ण

/*
 * Functions क्रम user space to पढ़ो/ग_लिखो attributes
 */

अटल sमाप_प्रकार comm_nodeid_show(काष्ठा config_item *item, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", config_item_to_comm(item)->nodeid);
पूर्ण

अटल sमाप_प्रकार comm_nodeid_store(काष्ठा config_item *item, स्थिर अक्षर *buf,
				 माप_प्रकार len)
अणु
	पूर्णांक rc = kstrtoपूर्णांक(buf, 0, &config_item_to_comm(item)->nodeid);

	अगर (rc)
		वापस rc;
	वापस len;
पूर्ण

अटल sमाप_प्रकार comm_local_show(काष्ठा config_item *item, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", config_item_to_comm(item)->local);
पूर्ण

अटल sमाप_प्रकार comm_local_store(काष्ठा config_item *item, स्थिर अक्षर *buf,
				माप_प्रकार len)
अणु
	काष्ठा dlm_comm *cm = config_item_to_comm(item);
	पूर्णांक rc = kstrtoपूर्णांक(buf, 0, &cm->local);

	अगर (rc)
		वापस rc;
	अगर (cm->local && !local_comm)
		local_comm = cm;
	वापस len;
पूर्ण

अटल sमाप_प्रकार comm_addr_store(काष्ठा config_item *item, स्थिर अक्षर *buf,
		माप_प्रकार len)
अणु
	काष्ठा dlm_comm *cm = config_item_to_comm(item);
	काष्ठा sockaddr_storage *addr;
	पूर्णांक rv;

	अगर (len != माप(काष्ठा sockaddr_storage))
		वापस -EINVAL;

	अगर (cm->addr_count >= DLM_MAX_ADDR_COUNT)
		वापस -ENOSPC;

	addr = kzalloc(माप(*addr), GFP_NOFS);
	अगर (!addr)
		वापस -ENOMEM;

	स_नकल(addr, buf, len);

	rv = dlm_lowcomms_addr(cm->nodeid, addr, len);
	अगर (rv) अणु
		kमुक्त(addr);
		वापस rv;
	पूर्ण

	cm->addr[cm->addr_count++] = addr;
	वापस len;
पूर्ण

अटल sमाप_प्रकार comm_addr_list_show(काष्ठा config_item *item, अक्षर *buf)
अणु
	काष्ठा dlm_comm *cm = config_item_to_comm(item);
	sमाप_प्रकार s;
	sमाप_प्रकार allowance;
	पूर्णांक i;
	काष्ठा sockaddr_storage *addr;
	काष्ठा sockaddr_in *addr_in;
	काष्ठा sockaddr_in6 *addr_in6;
	
	/* Taken from ip6_addr_string() defined in lib/भम_लिखो.c */
	अक्षर buf0[माप("AF_INET6	xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:255.255.255.255\n")];
	

	/* Derived from SIMPLE_ATTR_SIZE of fs/configfs/file.c */
	allowance = 4096;
	buf[0] = '\0';

	क्रम (i = 0; i < cm->addr_count; i++) अणु
		addr = cm->addr[i];

		चयन(addr->ss_family) अणु
		हाल AF_INET:
			addr_in = (काष्ठा sockaddr_in *)addr;
			s = प्र_लिखो(buf0, "AF_INET	%pI4\n", &addr_in->sin_addr.s_addr);
			अवरोध;
		हाल AF_INET6:
			addr_in6 = (काष्ठा sockaddr_in6 *)addr;
			s = प्र_लिखो(buf0, "AF_INET6	%pI6\n", &addr_in6->sin6_addr);
			अवरोध;
		शेष:
			s = प्र_लिखो(buf0, "%s\n", "<UNKNOWN>");
			अवरोध;
		पूर्ण
		allowance -= s;
		अगर (allowance >= 0)
			म_जोड़ो(buf, buf0);
		अन्यथा अणु
			allowance += s;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 4096 - allowance;
पूर्ण

अटल sमाप_प्रकार comm_mark_show(काष्ठा config_item *item, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", config_item_to_comm(item)->mark);
पूर्ण

अटल sमाप_प्रकार comm_mark_store(काष्ठा config_item *item, स्थिर अक्षर *buf,
			       माप_प्रकार len)
अणु
	काष्ठा dlm_comm *comm;
	अचिन्हित पूर्णांक mark;
	पूर्णांक rc;

	rc = kstrtouपूर्णांक(buf, 0, &mark);
	अगर (rc)
		वापस rc;

	अगर (mark == 0)
		mark = dlm_config.ci_mark;

	comm = config_item_to_comm(item);
	rc = dlm_lowcomms_nodes_set_mark(comm->nodeid, mark);
	अगर (rc)
		वापस rc;

	comm->mark = mark;
	वापस len;
पूर्ण

CONFIGFS_ATTR(comm_, nodeid);
CONFIGFS_ATTR(comm_, local);
CONFIGFS_ATTR(comm_, mark);
CONFIGFS_ATTR_WO(comm_, addr);
CONFIGFS_ATTR_RO(comm_, addr_list);

अटल काष्ठा configfs_attribute *comm_attrs[] = अणु
	[COMM_ATTR_NODEID] = &comm_attr_nodeid,
	[COMM_ATTR_LOCAL] = &comm_attr_local,
	[COMM_ATTR_ADDR] = &comm_attr_addr,
	[COMM_ATTR_ADDR_LIST] = &comm_attr_addr_list,
	[COMM_ATTR_MARK] = &comm_attr_mark,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार node_nodeid_show(काष्ठा config_item *item, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", config_item_to_node(item)->nodeid);
पूर्ण

अटल sमाप_प्रकार node_nodeid_store(काष्ठा config_item *item, स्थिर अक्षर *buf,
				 माप_प्रकार len)
अणु
	काष्ठा dlm_node *nd = config_item_to_node(item);
	uपूर्णांक32_t seq = 0;
	पूर्णांक rc = kstrtoपूर्णांक(buf, 0, &nd->nodeid);

	अगर (rc)
		वापस rc;
	dlm_comm_seq(nd->nodeid, &seq);
	nd->comm_seq = seq;
	वापस len;
पूर्ण

अटल sमाप_प्रकार node_weight_show(काष्ठा config_item *item, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", config_item_to_node(item)->weight);
पूर्ण

अटल sमाप_प्रकार node_weight_store(काष्ठा config_item *item, स्थिर अक्षर *buf,
				 माप_प्रकार len)
अणु
	पूर्णांक rc = kstrtoपूर्णांक(buf, 0, &config_item_to_node(item)->weight);

	अगर (rc)
		वापस rc;
	वापस len;
पूर्ण

CONFIGFS_ATTR(node_, nodeid);
CONFIGFS_ATTR(node_, weight);

अटल काष्ठा configfs_attribute *node_attrs[] = अणु
	[NODE_ATTR_NODEID] = &node_attr_nodeid,
	[NODE_ATTR_WEIGHT] = &node_attr_weight,
	शून्य,
पूर्ण;

/*
 * Functions क्रम the dlm to get the info that's been configured
 */

अटल काष्ठा dlm_space *get_space(अक्षर *name)
अणु
	काष्ठा config_item *i;

	अगर (!space_list)
		वापस शून्य;

	mutex_lock(&space_list->cg_subsys->su_mutex);
	i = config_group_find_item(space_list, name);
	mutex_unlock(&space_list->cg_subsys->su_mutex);

	वापस config_item_to_space(i);
पूर्ण

अटल व्योम put_space(काष्ठा dlm_space *sp)
अणु
	config_item_put(&sp->group.cg_item);
पूर्ण

अटल काष्ठा dlm_comm *get_comm(पूर्णांक nodeid)
अणु
	काष्ठा config_item *i;
	काष्ठा dlm_comm *cm = शून्य;
	पूर्णांक found = 0;

	अगर (!comm_list)
		वापस शून्य;

	mutex_lock(&clusters_root.subsys.su_mutex);

	list_क्रम_each_entry(i, &comm_list->cg_children, ci_entry) अणु
		cm = config_item_to_comm(i);

		अगर (cm->nodeid != nodeid)
			जारी;
		found = 1;
		config_item_get(i);
		अवरोध;
	पूर्ण
	mutex_unlock(&clusters_root.subsys.su_mutex);

	अगर (!found)
		cm = शून्य;
	वापस cm;
पूर्ण

अटल व्योम put_comm(काष्ठा dlm_comm *cm)
अणु
	config_item_put(&cm->item);
पूर्ण

/* caller must मुक्त mem */
पूर्णांक dlm_config_nodes(अक्षर *lsname, काष्ठा dlm_config_node **nodes_out,
		     पूर्णांक *count_out)
अणु
	काष्ठा dlm_space *sp;
	काष्ठा dlm_node *nd;
	काष्ठा dlm_config_node *nodes, *node;
	पूर्णांक rv, count;

	sp = get_space(lsname);
	अगर (!sp)
		वापस -EEXIST;

	mutex_lock(&sp->members_lock);
	अगर (!sp->members_count) अणु
		rv = -EINVAL;
		prपूर्णांकk(KERN_ERR "dlm: zero members_count\n");
		जाओ out;
	पूर्ण

	count = sp->members_count;

	nodes = kसुस्मृति(count, माप(काष्ठा dlm_config_node), GFP_NOFS);
	अगर (!nodes) अणु
		rv = -ENOMEM;
		जाओ out;
	पूर्ण

	node = nodes;
	list_क्रम_each_entry(nd, &sp->members, list) अणु
		node->nodeid = nd->nodeid;
		node->weight = nd->weight;
		node->new = nd->new;
		node->comm_seq = nd->comm_seq;
		node++;

		nd->new = 0;
	पूर्ण

	*count_out = count;
	*nodes_out = nodes;
	rv = 0;
 out:
	mutex_unlock(&sp->members_lock);
	put_space(sp);
	वापस rv;
पूर्ण

पूर्णांक dlm_comm_seq(पूर्णांक nodeid, uपूर्णांक32_t *seq)
अणु
	काष्ठा dlm_comm *cm = get_comm(nodeid);
	अगर (!cm)
		वापस -EEXIST;
	*seq = cm->seq;
	put_comm(cm);
	वापस 0;
पूर्ण

पूर्णांक dlm_our_nodeid(व्योम)
अणु
	वापस local_comm ? local_comm->nodeid : 0;
पूर्ण

/* num 0 is first addr, num 1 is second addr */
पूर्णांक dlm_our_addr(काष्ठा sockaddr_storage *addr, पूर्णांक num)
अणु
	अगर (!local_comm)
		वापस -1;
	अगर (num + 1 > local_comm->addr_count)
		वापस -1;
	स_नकल(addr, local_comm->addr[num], माप(*addr));
	वापस 0;
पूर्ण

/* Config file शेषs */
#घोषणा DEFAULT_TCP_PORT       21064
#घोषणा DEFAULT_RSBTBL_SIZE     1024
#घोषणा DEFAULT_RECOVER_TIMER      5
#घोषणा DEFAULT_TOSS_SECS         10
#घोषणा DEFAULT_SCAN_SECS          5
#घोषणा DEFAULT_LOG_DEBUG          0
#घोषणा DEFAULT_LOG_INFO           1
#घोषणा DEFAULT_PROTOCOL           0
#घोषणा DEFAULT_MARK               0
#घोषणा DEFAULT_TIMEWARN_CS      500 /* 5 sec = 500 centiseconds */
#घोषणा DEFAULT_WAITWARN_US	   0
#घोषणा DEFAULT_NEW_RSB_COUNT    128
#घोषणा DEFAULT_RECOVER_CALLBACKS  0
#घोषणा DEFAULT_CLUSTER_NAME      ""

काष्ठा dlm_config_info dlm_config = अणु
	.ci_tcp_port = DEFAULT_TCP_PORT,
	.ci_buffer_size = DEFAULT_BUFFER_SIZE,
	.ci_rsbtbl_size = DEFAULT_RSBTBL_SIZE,
	.ci_recover_समयr = DEFAULT_RECOVER_TIMER,
	.ci_toss_secs = DEFAULT_TOSS_SECS,
	.ci_scan_secs = DEFAULT_SCAN_SECS,
	.ci_log_debug = DEFAULT_LOG_DEBUG,
	.ci_log_info = DEFAULT_LOG_INFO,
	.ci_protocol = DEFAULT_PROTOCOL,
	.ci_mark = DEFAULT_MARK,
	.ci_समयwarn_cs = DEFAULT_TIMEWARN_CS,
	.ci_रुकोwarn_us = DEFAULT_WAITWARN_US,
	.ci_new_rsb_count = DEFAULT_NEW_RSB_COUNT,
	.ci_recover_callbacks = DEFAULT_RECOVER_CALLBACKS,
	.ci_cluster_name = DEFAULT_CLUSTER_NAME
पूर्ण;

