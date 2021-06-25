<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2008, 2009 खोलो80211s Ltd.
 * Authors:    Luis Carlos Cobo <luisca@cozybit.com>
 *             Javier Carकरोna <javier@cozybit.com>
 */

#अगर_अघोषित IEEE80211S_H
#घोषणा IEEE80211S_H

#समावेश <linux/types.h>
#समावेश <linux/jhash.h>
#समावेश "ieee80211_i.h"


/* Data काष्ठाures */

/**
 * क्रमागत mesh_path_flags - mac80211 mesh path flags
 *
 * @MESH_PATH_ACTIVE: the mesh path can be used क्रम क्रमwarding
 * @MESH_PATH_RESOLVING: the discovery process is running क्रम this mesh path
 * @MESH_PATH_SN_VALID: the mesh path contains a valid destination sequence
 *	number
 * @MESH_PATH_FIXED: the mesh path has been manually set and should not be
 *	modअगरied
 * @MESH_PATH_RESOLVED: the mesh path can has been resolved
 * @MESH_PATH_REQ_QUEUED: there is an unsent path request क्रम this destination
 *	alपढ़ोy queued up, रुकोing क्रम the discovery process to start.
 * @MESH_PATH_DELETED: the mesh path has been deleted and should no दीर्घer
 *	be used
 *
 * MESH_PATH_RESOLVED is used by the mesh path समयr to
 * decide when to stop or cancel the mesh path discovery.
 */
क्रमागत mesh_path_flags अणु
	MESH_PATH_ACTIVE =	BIT(0),
	MESH_PATH_RESOLVING =	BIT(1),
	MESH_PATH_SN_VALID =	BIT(2),
	MESH_PATH_FIXED	=	BIT(3),
	MESH_PATH_RESOLVED =	BIT(4),
	MESH_PATH_REQ_QUEUED =	BIT(5),
	MESH_PATH_DELETED =	BIT(6),
पूर्ण;

/**
 * क्रमागत mesh_deferred_task_flags - mac80211 mesh deferred tasks
 *
 *
 *
 * @MESH_WORK_HOUSEKEEPING: run the periodic mesh housekeeping tasks
 * @MESH_WORK_ROOT: the mesh root station needs to send a frame
 * @MESH_WORK_DRIFT_ADJUST: समय to compensate क्रम घड़ी drअगरt relative to other
 * mesh nodes
 * @MESH_WORK_MBSS_CHANGED: rebuild beacon and notअगरy driver of BSS changes
 */
क्रमागत mesh_deferred_task_flags अणु
	MESH_WORK_HOUSEKEEPING,
	MESH_WORK_ROOT,
	MESH_WORK_DRIFT_ADJUST,
	MESH_WORK_MBSS_CHANGED,
पूर्ण;

/**
 * काष्ठा mesh_path - mac80211 mesh path काष्ठाure
 *
 * @dst: mesh path destination mac address
 * @mpp: mesh proxy mac address
 * @rhash: rhashtable list poपूर्णांकer
 * @walk_list: linked list containing all mesh_path objects.
 * @gate_list: list poपूर्णांकer क्रम known gates list
 * @sdata: mesh subअगर
 * @next_hop: mesh neighbor to which frames क्रम this destination will be
 *	क्रमwarded
 * @समयr: mesh path discovery समयr
 * @frame_queue: pending queue क्रम frames sent to this destination जबतक the
 *	path is unresolved
 * @rcu: rcu head क्रम मुक्तing mesh path
 * @sn: target sequence number
 * @metric: current metric to this destination
 * @hop_count: hops to destination
 * @exp_समय: in jअगरfies, when the path will expire or when it expired
 * @discovery_समयout: समयout (lapse in jअगरfies) used क्रम the last discovery
 *	retry
 * @discovery_retries: number of discovery retries
 * @flags: mesh path flags, as specअगरied on &क्रमागत mesh_path_flags
 * @state_lock: mesh path state lock used to protect changes to the
 * mpath itself.  No need to take this lock when adding or removing
 * an mpath to a hash bucket on a path table.
 * @rann_snd_addr: the RANN sender address
 * @rann_metric: the aggregated path metric towards the root node
 * @last_preq_to_root: Timestamp of last PREQ sent to root
 * @is_root: the destination station of this path is a root node
 * @is_gate: the destination station of this path is a mesh gate
 * @path_change_count: the number of path changes to destination
 *
 *
 * The dst address is unique in the mesh path table. Since the mesh_path is
 * रक्षित by RCU, deleting the next_hop STA must हटाओ / substitute the
 * mesh_path काष्ठाure and रुको until that is no दीर्घer reachable beक्रमe
 * destroying the STA completely.
 */
काष्ठा mesh_path अणु
	u8 dst[ETH_ALEN];
	u8 mpp[ETH_ALEN];	/* used क्रम MPP or MAP */
	काष्ठा rhash_head rhash;
	काष्ठा hlist_node walk_list;
	काष्ठा hlist_node gate_list;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा sta_info __rcu *next_hop;
	काष्ठा समयr_list समयr;
	काष्ठा sk_buff_head frame_queue;
	काष्ठा rcu_head rcu;
	u32 sn;
	u32 metric;
	u8 hop_count;
	अचिन्हित दीर्घ exp_समय;
	u32 discovery_समयout;
	u8 discovery_retries;
	क्रमागत mesh_path_flags flags;
	spinlock_t state_lock;
	u8 rann_snd_addr[ETH_ALEN];
	u32 rann_metric;
	अचिन्हित दीर्घ last_preq_to_root;
	bool is_root;
	bool is_gate;
	u32 path_change_count;
पूर्ण;

/**
 * काष्ठा mesh_table
 *
 * @known_gates: list of known mesh gates and their mpaths by the station. The
 * gate's mpath may or may not be resolved and active.
 * @gates_lock: protects updates to known_gates
 * @rhead: the rhashtable containing काष्ठा mesh_paths, keyed by dest addr
 * @walk_head: linked list containging all mesh_path objects
 * @walk_lock: lock protecting walk_head
 * @entries: number of entries in the table
 */
काष्ठा mesh_table अणु
	काष्ठा hlist_head known_gates;
	spinlock_t gates_lock;
	काष्ठा rhashtable rhead;
	काष्ठा hlist_head walk_head;
	spinlock_t walk_lock;
	atomic_t entries;		/* Up to MAX_MESH_NEIGHBOURS */
पूर्ण;

/* Recent multicast cache */
/* RMC_BUCKETS must be a घातer of 2, maximum 256 */
#घोषणा RMC_BUCKETS		256
#घोषणा RMC_QUEUE_MAX_LEN	4
#घोषणा RMC_TIMEOUT		(3 * HZ)

/**
 * काष्ठा rmc_entry - entry in the Recent Multicast Cache
 *
 * @seqnum: mesh sequence number of the frame
 * @exp_समय: expiration समय of the entry, in jअगरfies
 * @sa: source address of the frame
 * @list: hashtable list poपूर्णांकer
 *
 * The Recent Multicast Cache keeps track of the latest multicast frames that
 * have been received by a mesh पूर्णांकerface and discards received multicast frames
 * that are found in the cache.
 */
काष्ठा rmc_entry अणु
	काष्ठा hlist_node list;
	अचिन्हित दीर्घ exp_समय;
	u32 seqnum;
	u8 sa[ETH_ALEN];
पूर्ण;

काष्ठा mesh_rmc अणु
	काष्ठा hlist_head bucket[RMC_BUCKETS];
	u32 idx_mask;
पूर्ण;

#घोषणा IEEE80211_MESH_HOUSEKEEPING_INTERVAL (60 * HZ)

#घोषणा MESH_PATH_EXPIRE (600 * HZ)

/* Default maximum number of plinks per पूर्णांकerface */
#घोषणा MESH_MAX_PLINKS		256

/* Maximum number of paths per पूर्णांकerface */
#घोषणा MESH_MAX_MPATHS		1024

/* Number of frames buffered per destination क्रम unresolved destinations */
#घोषणा MESH_FRAME_QUEUE_LEN	10

/* Public पूर्णांकerfaces */
/* Various */
पूर्णांक ieee80211_fill_mesh_addresses(काष्ठा ieee80211_hdr *hdr, __le16 *fc,
				  स्थिर u8 *da, स्थिर u8 *sa);
अचिन्हित पूर्णांक ieee80211_new_mesh_header(काष्ठा ieee80211_sub_अगर_data *sdata,
				       काष्ठा ieee80211s_hdr *meshhdr,
				       स्थिर अक्षर *addr4or5, स्थिर अक्षर *addr6);
पूर्णांक mesh_rmc_check(काष्ठा ieee80211_sub_अगर_data *sdata,
		   स्थिर u8 *addr, काष्ठा ieee80211s_hdr *mesh_hdr);
bool mesh_matches_local(काष्ठा ieee80211_sub_अगर_data *sdata,
			काष्ठा ieee802_11_elems *ie);
व्योम mesh_ids_set_शेष(काष्ठा ieee80211_अगर_mesh *mesh);
पूर्णांक mesh_add_meshconf_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
			 काष्ठा sk_buff *skb);
पूर्णांक mesh_add_meshid_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
		       काष्ठा sk_buff *skb);
पूर्णांक mesh_add_rsn_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
		    काष्ठा sk_buff *skb);
पूर्णांक mesh_add_venकरोr_ies(काष्ठा ieee80211_sub_अगर_data *sdata,
			काष्ठा sk_buff *skb);
पूर्णांक mesh_add_ht_cap_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
		       काष्ठा sk_buff *skb);
पूर्णांक mesh_add_ht_oper_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
			काष्ठा sk_buff *skb);
पूर्णांक mesh_add_vht_cap_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
			काष्ठा sk_buff *skb);
पूर्णांक mesh_add_vht_oper_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
			 काष्ठा sk_buff *skb);
पूर्णांक mesh_add_he_cap_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
		       काष्ठा sk_buff *skb, u8 ie_len);
पूर्णांक mesh_add_he_oper_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
			काष्ठा sk_buff *skb);
पूर्णांक mesh_add_he_6ghz_cap_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
			    काष्ठा sk_buff *skb);
व्योम mesh_rmc_मुक्त(काष्ठा ieee80211_sub_अगर_data *sdata);
पूर्णांक mesh_rmc_init(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211s_init(व्योम);
व्योम ieee80211s_update_metric(काष्ठा ieee80211_local *local,
			      काष्ठा sta_info *sta,
			      काष्ठा ieee80211_tx_status *st);
व्योम ieee80211_mesh_init_sdata(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_mesh_tearकरोwn_sdata(काष्ठा ieee80211_sub_अगर_data *sdata);
पूर्णांक ieee80211_start_mesh(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_stop_mesh(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_mesh_root_setup(काष्ठा ieee80211_अगर_mesh *अगरmsh);
स्थिर काष्ठा ieee80211_mesh_sync_ops *ieee80211_mesh_sync_ops_get(u8 method);
/* wrapper क्रम ieee80211_bss_info_change_notअगरy() */
व्योम ieee80211_mbss_info_change_notअगरy(काष्ठा ieee80211_sub_अगर_data *sdata,
				       u32 changed);

/* mesh घातer save */
u32 ieee80211_mps_local_status_update(काष्ठा ieee80211_sub_अगर_data *sdata);
u32 ieee80211_mps_set_sta_local_pm(काष्ठा sta_info *sta,
				   क्रमागत nl80211_mesh_घातer_mode pm);
व्योम ieee80211_mps_set_frame_flags(काष्ठा ieee80211_sub_अगर_data *sdata,
				   काष्ठा sta_info *sta,
				   काष्ठा ieee80211_hdr *hdr);
व्योम ieee80211_mps_sta_status_update(काष्ठा sta_info *sta);
व्योम ieee80211_mps_rx_h_sta_process(काष्ठा sta_info *sta,
				    काष्ठा ieee80211_hdr *hdr);
व्योम ieee80211_mpsp_trigger_process(u8 *qc, काष्ठा sta_info *sta,
				    bool tx, bool acked);
व्योम ieee80211_mps_frame_release(काष्ठा sta_info *sta,
				 काष्ठा ieee802_11_elems *elems);

/* Mesh paths */
पूर्णांक mesh_nexthop_lookup(काष्ठा ieee80211_sub_अगर_data *sdata,
			काष्ठा sk_buff *skb);
पूर्णांक mesh_nexthop_resolve(काष्ठा ieee80211_sub_अगर_data *sdata,
			 काष्ठा sk_buff *skb);
व्योम mesh_path_start_discovery(काष्ठा ieee80211_sub_अगर_data *sdata);
काष्ठा mesh_path *mesh_path_lookup(काष्ठा ieee80211_sub_अगर_data *sdata,
				   स्थिर u8 *dst);
काष्ठा mesh_path *mpp_path_lookup(काष्ठा ieee80211_sub_अगर_data *sdata,
				  स्थिर u8 *dst);
पूर्णांक mpp_path_add(काष्ठा ieee80211_sub_अगर_data *sdata,
		 स्थिर u8 *dst, स्थिर u8 *mpp);
काष्ठा mesh_path *
mesh_path_lookup_by_idx(काष्ठा ieee80211_sub_अगर_data *sdata, पूर्णांक idx);
काष्ठा mesh_path *
mpp_path_lookup_by_idx(काष्ठा ieee80211_sub_अगर_data *sdata, पूर्णांक idx);
व्योम mesh_path_fix_nexthop(काष्ठा mesh_path *mpath, काष्ठा sta_info *next_hop);
व्योम mesh_path_expire(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम mesh_rx_path_sel_frame(काष्ठा ieee80211_sub_अगर_data *sdata,
			    काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len);
काष्ठा mesh_path *
mesh_path_add(काष्ठा ieee80211_sub_अगर_data *sdata, स्थिर u8 *dst);

पूर्णांक mesh_path_add_gate(काष्ठा mesh_path *mpath);
पूर्णांक mesh_path_send_to_gates(काष्ठा mesh_path *mpath);
पूर्णांक mesh_gate_num(काष्ठा ieee80211_sub_अगर_data *sdata);
u32 airसमय_link_metric_get(काष्ठा ieee80211_local *local,
			    काष्ठा sta_info *sta);

/* Mesh plinks */
व्योम mesh_neighbour_update(काष्ठा ieee80211_sub_अगर_data *sdata,
			   u8 *hw_addr, काष्ठा ieee802_11_elems *ie,
			   काष्ठा ieee80211_rx_status *rx_status);
bool mesh_peer_accepts_plinks(काष्ठा ieee802_11_elems *ie);
u32 mesh_accept_plinks_update(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम mesh_plink_समयr(काष्ठा समयr_list *t);
व्योम mesh_plink_broken(काष्ठा sta_info *sta);
u32 mesh_plink_deactivate(काष्ठा sta_info *sta);
u32 mesh_plink_खोलो(काष्ठा sta_info *sta);
u32 mesh_plink_block(काष्ठा sta_info *sta);
व्योम mesh_rx_plink_frame(काष्ठा ieee80211_sub_अगर_data *sdata,
			 काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len,
			 काष्ठा ieee80211_rx_status *rx_status);
व्योम mesh_sta_cleanup(काष्ठा sta_info *sta);

/* Private पूर्णांकerfaces */
/* Mesh paths */
पूर्णांक mesh_path_error_tx(काष्ठा ieee80211_sub_अगर_data *sdata,
		       u8 ttl, स्थिर u8 *target, u32 target_sn,
		       u16 target_rcode, स्थिर u8 *ra);
व्योम mesh_path_assign_nexthop(काष्ठा mesh_path *mpath, काष्ठा sta_info *sta);
व्योम mesh_path_flush_pending(काष्ठा mesh_path *mpath);
व्योम mesh_path_tx_pending(काष्ठा mesh_path *mpath);
पूर्णांक mesh_pathtbl_init(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम mesh_pathtbl_unरेजिस्टर(काष्ठा ieee80211_sub_अगर_data *sdata);
पूर्णांक mesh_path_del(काष्ठा ieee80211_sub_अगर_data *sdata, स्थिर u8 *addr);
व्योम mesh_path_समयr(काष्ठा समयr_list *t);
व्योम mesh_path_flush_by_nexthop(काष्ठा sta_info *sta);
व्योम mesh_path_discard_frame(काष्ठा ieee80211_sub_अगर_data *sdata,
			     काष्ठा sk_buff *skb);
व्योम mesh_path_tx_root_frame(काष्ठा ieee80211_sub_अगर_data *sdata);

bool mesh_action_is_path_sel(काष्ठा ieee80211_mgmt *mgmt);

#अगर_घोषित CONFIG_MAC80211_MESH
अटल अंतरभूत
u32 mesh_plink_inc_estab_count(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	atomic_inc(&sdata->u.mesh.estab_plinks);
	वापस mesh_accept_plinks_update(sdata) | BSS_CHANGED_BEACON;
पूर्ण

अटल अंतरभूत
u32 mesh_plink_dec_estab_count(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	atomic_dec(&sdata->u.mesh.estab_plinks);
	वापस mesh_accept_plinks_update(sdata) | BSS_CHANGED_BEACON;
पूर्ण

अटल अंतरभूत पूर्णांक mesh_plink_मुक्त_count(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	वापस sdata->u.mesh.mshcfg.करोt11MeshMaxPeerLinks -
	       atomic_पढ़ो(&sdata->u.mesh.estab_plinks);
पूर्ण

अटल अंतरभूत bool mesh_plink_availables(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	वापस (min_t(दीर्घ, mesh_plink_मुक्त_count(sdata),
		   MESH_MAX_PLINKS - sdata->local->num_sta)) > 0;
पूर्ण

अटल अंतरभूत व्योम mesh_path_activate(काष्ठा mesh_path *mpath)
अणु
	mpath->flags |= MESH_PATH_ACTIVE | MESH_PATH_RESOLVED;
पूर्ण

अटल अंतरभूत bool mesh_path_sel_is_hwmp(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	वापस sdata->u.mesh.mesh_pp_id == IEEE80211_PATH_PROTOCOL_HWMP;
पूर्ण

व्योम mesh_path_flush_by_अगरace(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम mesh_sync_adjust_tsf(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211s_stop(व्योम);
#अन्यथा
अटल अंतरभूत bool mesh_path_sel_is_hwmp(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु वापस false; पूर्ण
अटल अंतरभूत व्योम mesh_path_flush_by_अगरace(काष्ठा ieee80211_sub_अगर_data *sdata)
अणुपूर्ण
अटल अंतरभूत व्योम ieee80211s_stop(व्योम) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* IEEE80211S_H */
