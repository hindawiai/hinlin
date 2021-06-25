<शैली गुरु>
/*
 * Copyright (c) 2017, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित __MLX5E_REP_H__
#घोषणा __MLX5E_REP_H__

#समावेश <net/ip_tunnels.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/mutex.h>
#समावेश "eswitch.h"
#समावेश "en.h"
#समावेश "lib/port_tun.h"

#अगर_घोषित CONFIG_MLX5_ESWITCH
बाह्य स्थिर काष्ठा mlx5e_rx_handlers mlx5e_rx_handlers_rep;

काष्ठा mlx5e_neigh_update_table अणु
	काष्ठा rhashtable       neigh_ht;
	/* Save the neigh hash entries in a list in addition to the hash table
	 * (neigh_ht). In order to iterate easily over the neigh entries.
	 * Used क्रम stats query.
	 */
	काष्ठा list_head	neigh_list;
	/* protect lookup/हटाओ operations */
	काष्ठा mutex		encap_lock;
	काष्ठा notअगरier_block   netevent_nb;
	काष्ठा delayed_work     neigh_stats_work;
	अचिन्हित दीर्घ           min_पूर्णांकerval; /* jअगरfies */
पूर्ण;

काष्ठा mlx5_tc_ct_priv;
काष्ठा mlx5e_rep_bond;
काष्ठा mlx5e_tc_tun_encap;

काष्ठा mlx5_rep_uplink_priv अणु
	/* Filters DB - instantiated by the uplink representor and shared by
	 * the uplink's VFs
	 */
	काष्ठा rhashtable  tc_ht;

	/* indirect block callbacks are invoked on bind/unbind events
	 * on रेजिस्टरed higher level devices (e.g. tunnel devices)
	 *
	 * tc_indr_block_cb_priv_list is used to lookup indirect callback
	 * निजी data
	 *
	 */
	काष्ठा list_head	    tc_indr_block_priv_list;

	काष्ठा mlx5_tun_entropy tun_entropy;

	/* protects unपढ़ोy_flows */
	काष्ठा mutex                unपढ़ोy_flows_lock;
	काष्ठा list_head            unपढ़ोy_flows;
	काष्ठा work_काष्ठा          reoffload_flows_work;

	/* maps tun_info to a unique id*/
	काष्ठा mapping_ctx *tunnel_mapping;
	/* maps tun_enc_opts to a unique id*/
	काष्ठा mapping_ctx *tunnel_enc_opts_mapping;

	काष्ठा mlx5_tc_ct_priv *ct_priv;
	काष्ठा mlx5_esw_psample *esw_psample;

	/* support eचयन vports bonding */
	काष्ठा mlx5e_rep_bond *bond;

	/* tc tunneling encapsulation निजी data */
	काष्ठा mlx5e_tc_tun_encap *encap;
पूर्ण;

काष्ठा mlx5e_rep_priv अणु
	काष्ठा mlx5_eचयन_rep *rep;
	काष्ठा mlx5e_neigh_update_table neigh_update;
	काष्ठा net_device      *netdev;
	काष्ठा mlx5_flow_table *root_ft;
	काष्ठा mlx5_flow_handle *vport_rx_rule;
	काष्ठा list_head       vport_sqs_list;
	काष्ठा mlx5_rep_uplink_priv uplink_priv; /* valid क्रम uplink rep */
	काष्ठा rtnl_link_stats64 prev_vf_vport_stats;
पूर्ण;

अटल अंतरभूत
काष्ठा mlx5e_rep_priv *mlx5e_rep_to_rep_priv(काष्ठा mlx5_eचयन_rep *rep)
अणु
	वापस rep->rep_data[REP_ETH].priv;
पूर्ण

काष्ठा mlx5e_neigh अणु
	जोड़ अणु
		__be32	v4;
		काष्ठा in6_addr v6;
	पूर्ण dst_ip;
	पूर्णांक family;
पूर्ण;

काष्ठा mlx5e_neigh_hash_entry अणु
	काष्ठा rhash_head rhash_node;
	काष्ठा mlx5e_neigh m_neigh;
	काष्ठा mlx5e_priv *priv;
	काष्ठा net_device *neigh_dev;

	/* Save the neigh hash entry in a list on the representor in
	 * addition to the hash table. In order to iterate easily over the
	 * neighbour entries. Used क्रम stats query.
	 */
	काष्ठा list_head neigh_list;

	/* protects encap list */
	spinlock_t encap_list_lock;
	/* encap list sharing the same neigh */
	काष्ठा list_head encap_list;

	/* neigh hash entry can be deleted only when the refcount is zero.
	 * refcount is needed to aव्योम neigh hash entry removal by TC, जबतक
	 * it's used by the neigh notअगरication call.
	 */
	refcount_t refcnt;

	/* Save the last reported समय offloaded trafic pass over one of the
	 * neigh hash entry flows. Use it to periodically update the neigh
	 * 'used' value and aव्योम neigh deleting by the kernel.
	 */
	अचिन्हित दीर्घ reported_lastuse;

	काष्ठा rcu_head rcu;
पूर्ण;

क्रमागत अणु
	/* set when the encap entry is successfully offloaded पूर्णांकo HW */
	MLX5_ENCAP_ENTRY_VALID     = BIT(0),
	MLX5_REFORMAT_DECAP        = BIT(1),
	MLX5_ENCAP_ENTRY_NO_ROUTE  = BIT(2),
पूर्ण;

काष्ठा mlx5e_decap_key अणु
	काष्ठा ethhdr key;
पूर्ण;

काष्ठा mlx5e_decap_entry अणु
	काष्ठा mlx5e_decap_key key;
	काष्ठा list_head flows;
	काष्ठा hlist_node hlist;
	refcount_t refcnt;
	काष्ठा completion res_पढ़ोy;
	पूर्णांक compl_result;
	काष्ठा mlx5_pkt_reक्रमmat *pkt_reक्रमmat;
	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा mlx5e_encap_entry अणु
	/* attached neigh hash entry */
	काष्ठा mlx5e_neigh_hash_entry *nhe;
	/* neigh hash entry list of encaps sharing the same neigh */
	काष्ठा list_head encap_list;
	/* a node of the eचयन encap hash table which keeping all the encap
	 * entries
	 */
	काष्ठा hlist_node encap_hlist;
	काष्ठा list_head flows;
	काष्ठा list_head route_list;
	काष्ठा mlx5_pkt_reक्रमmat *pkt_reक्रमmat;
	स्थिर काष्ठा ip_tunnel_info *tun_info;
	अचिन्हित अक्षर h_dest[ETH_ALEN];	/* destination eth addr	*/

	काष्ठा net_device *out_dev;
	पूर्णांक route_dev_अगरindex;
	काष्ठा mlx5e_tc_tunnel *tunnel;
	पूर्णांक reक्रमmat_type;
	u8 flags;
	अक्षर *encap_header;
	पूर्णांक encap_size;
	refcount_t refcnt;
	काष्ठा completion res_पढ़ोy;
	पूर्णांक compl_result;
	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा mlx5e_rep_sq अणु
	काष्ठा mlx5_flow_handle	*send_to_vport_rule;
	काष्ठा list_head	 list;
पूर्ण;

पूर्णांक mlx5e_rep_init(व्योम);
व्योम mlx5e_rep_cleanup(व्योम);
पूर्णांक mlx5e_rep_bond_init(काष्ठा mlx5e_rep_priv *rpriv);
व्योम mlx5e_rep_bond_cleanup(काष्ठा mlx5e_rep_priv *rpriv);
पूर्णांक mlx5e_rep_bond_enslave(काष्ठा mlx5_eचयन *esw, काष्ठा net_device *netdev,
			   काष्ठा net_device *lag_dev);
व्योम mlx5e_rep_bond_unslave(काष्ठा mlx5_eचयन *esw,
			    स्थिर काष्ठा net_device *netdev,
			    स्थिर काष्ठा net_device *lag_dev);
पूर्णांक mlx5e_rep_bond_update(काष्ठा mlx5e_priv *priv, bool cleanup);

bool mlx5e_rep_has_offload_stats(स्थिर काष्ठा net_device *dev, पूर्णांक attr_id);
पूर्णांक mlx5e_rep_get_offload_stats(पूर्णांक attr_id, स्थिर काष्ठा net_device *dev,
				व्योम *sp);

bool mlx5e_is_uplink_rep(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_add_sqs_fwd_rules(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_हटाओ_sqs_fwd_rules(काष्ठा mlx5e_priv *priv);

व्योम mlx5e_rep_queue_neigh_stats_work(काष्ठा mlx5e_priv *priv);

bool mlx5e_eचयन_vf_rep(काष्ठा net_device *netdev);
bool mlx5e_eचयन_uplink_rep(काष्ठा net_device *netdev);
अटल अंतरभूत bool mlx5e_eचयन_rep(काष्ठा net_device *netdev)
अणु
	वापस mlx5e_eचयन_vf_rep(netdev) ||
	       mlx5e_eचयन_uplink_rep(netdev);
पूर्ण

#अन्यथा /* CONFIG_MLX5_ESWITCH */
अटल अंतरभूत bool mlx5e_is_uplink_rep(काष्ठा mlx5e_priv *priv) अणु वापस false; पूर्ण
अटल अंतरभूत पूर्णांक mlx5e_add_sqs_fwd_rules(काष्ठा mlx5e_priv *priv) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम mlx5e_हटाओ_sqs_fwd_rules(काष्ठा mlx5e_priv *priv) अणुपूर्ण
अटल अंतरभूत पूर्णांक mlx5e_rep_init(व्योम) अणु वापस 0; पूर्ण;
अटल अंतरभूत व्योम mlx5e_rep_cleanup(व्योम) अणुपूर्ण;
अटल अंतरभूत bool mlx5e_rep_has_offload_stats(स्थिर काष्ठा net_device *dev,
					       पूर्णांक attr_id) अणु वापस false; पूर्ण
अटल अंतरभूत पूर्णांक mlx5e_rep_get_offload_stats(पूर्णांक attr_id,
					      स्थिर काष्ठा net_device *dev,
					      व्योम *sp) अणु वापस -EOPNOTSUPP; पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool mlx5e_is_vport_rep(काष्ठा mlx5e_priv *priv)
अणु
	वापस (MLX5_ESWITCH_MANAGER(priv->mdev) && priv->ppriv);
पूर्ण
#पूर्ण_अगर /* __MLX5E_REP_H__ */
