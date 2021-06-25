<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FS_CEPH_MON_CLIENT_H
#घोषणा _FS_CEPH_MON_CLIENT_H

#समावेश <linux/completion.h>
#समावेश <linux/kref.h>
#समावेश <linux/rbtree.h>

#समावेश <linux/ceph/messenger.h>

काष्ठा ceph_client;
काष्ठा ceph_mount_args;
काष्ठा ceph_auth_client;

/*
 * The monitor map क्रमागतerates the set of all monitors.
 */
काष्ठा ceph_monmap अणु
	काष्ठा ceph_fsid fsid;
	u32 epoch;
	u32 num_mon;
	काष्ठा ceph_entity_inst mon_inst[];
पूर्ण;

काष्ठा ceph_mon_client;
काष्ठा ceph_mon_generic_request;


/*
 * Generic mechanism क्रम resending monitor requests.
 */
प्रकार व्योम (*ceph_monc_request_func_t)(काष्ठा ceph_mon_client *monc,
					 पूर्णांक newmon);

/* a pending monitor request */
काष्ठा ceph_mon_request अणु
	काष्ठा ceph_mon_client *monc;
	काष्ठा delayed_work delayed_work;
	अचिन्हित दीर्घ delay;
	ceph_monc_request_func_t करो_request;
पूर्ण;

प्रकार व्योम (*ceph_monc_callback_t)(काष्ठा ceph_mon_generic_request *);

/*
 * ceph_mon_generic_request is being used क्रम the statfs and
 * mon_get_version requests which are being करोne a bit dअगरferently
 * because we need to get data back to the caller
 */
काष्ठा ceph_mon_generic_request अणु
	काष्ठा ceph_mon_client *monc;
	काष्ठा kref kref;
	u64 tid;
	काष्ठा rb_node node;
	पूर्णांक result;

	काष्ठा completion completion;
	ceph_monc_callback_t complete_cb;
	u64 निजी_data;          /* r_tid/linger_id */

	काष्ठा ceph_msg *request;  /* original request */
	काष्ठा ceph_msg *reply;    /* and reply */

	जोड़ अणु
		काष्ठा ceph_statfs *st;
		u64 newest;
	पूर्ण u;
पूर्ण;

काष्ठा ceph_mon_client अणु
	काष्ठा ceph_client *client;
	काष्ठा ceph_monmap *monmap;

	काष्ठा mutex mutex;
	काष्ठा delayed_work delayed_work;

	काष्ठा ceph_auth_client *auth;
	काष्ठा ceph_msg *m_auth, *m_auth_reply, *m_subscribe, *m_subscribe_ack;
	पूर्णांक pending_auth;

	bool hunting;
	पूर्णांक cur_mon;                       /* last monitor i contacted */
	अचिन्हित दीर्घ sub_renew_after;
	अचिन्हित दीर्घ sub_renew_sent;
	काष्ठा ceph_connection con;

	bool had_a_connection;
	पूर्णांक hunt_mult; /* [1..CEPH_MONC_HUNT_MAX_MULT] */

	/* pending generic requests */
	काष्ठा rb_root generic_request_tree;
	u64 last_tid;

	/* subs, indexed with CEPH_SUB_* */
	काष्ठा अणु
		काष्ठा ceph_mon_subscribe_item item;
		bool want;
		u32 have; /* epoch */
	पूर्ण subs[4];
	पूर्णांक fs_cluster_id; /* "mdsmap.<id>" sub */

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs_file;
#पूर्ण_अगर
पूर्ण;

बाह्य पूर्णांक ceph_monmap_contains(काष्ठा ceph_monmap *m,
				काष्ठा ceph_entity_addr *addr);

बाह्य पूर्णांक ceph_monc_init(काष्ठा ceph_mon_client *monc, काष्ठा ceph_client *cl);
बाह्य व्योम ceph_monc_stop(काष्ठा ceph_mon_client *monc);
बाह्य व्योम ceph_monc_reखोलो_session(काष्ठा ceph_mon_client *monc);

क्रमागत अणु
	CEPH_SUB_MONMAP = 0,
	CEPH_SUB_OSDMAP,
	CEPH_SUB_FSMAP,
	CEPH_SUB_MDSMAP,
पूर्ण;

बाह्य स्थिर अक्षर *ceph_sub_str[];

/*
 * The model here is to indicate that we need a new map of at least
 * epoch @epoch, and also call in when we receive a map.  We will
 * periodically rerequest the map from the monitor cluster until we
 * get what we want.
 */
bool ceph_monc_want_map(काष्ठा ceph_mon_client *monc, पूर्णांक sub, u32 epoch,
			bool continuous);
व्योम ceph_monc_got_map(काष्ठा ceph_mon_client *monc, पूर्णांक sub, u32 epoch);
व्योम ceph_monc_renew_subs(काष्ठा ceph_mon_client *monc);

बाह्य पूर्णांक ceph_monc_रुको_osdmap(काष्ठा ceph_mon_client *monc, u32 epoch,
				 अचिन्हित दीर्घ समयout);

पूर्णांक ceph_monc_करो_statfs(काष्ठा ceph_mon_client *monc, u64 data_pool,
			काष्ठा ceph_statfs *buf);

पूर्णांक ceph_monc_get_version(काष्ठा ceph_mon_client *monc, स्थिर अक्षर *what,
			  u64 *newest);
पूर्णांक ceph_monc_get_version_async(काष्ठा ceph_mon_client *monc, स्थिर अक्षर *what,
				ceph_monc_callback_t cb, u64 निजी_data);

पूर्णांक ceph_monc_blocklist_add(काष्ठा ceph_mon_client *monc,
			    काष्ठा ceph_entity_addr *client_addr);

बाह्य पूर्णांक ceph_monc_खोलो_session(काष्ठा ceph_mon_client *monc);

बाह्य पूर्णांक ceph_monc_validate_auth(काष्ठा ceph_mon_client *monc);

#पूर्ण_अगर
