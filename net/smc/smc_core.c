<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 *  Basic Transport Functions exploiting Infiniband API
 *
 *  Copyright IBM Corp. 2016
 *
 *  Author(s):  Ursula Braun <ubraun@linux.vnet.ibm.com>
 */

#समावेश <linux/socket.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/रुको.h>
#समावेश <linux/reboot.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/smc.h>
#समावेश <net/tcp.h>
#समावेश <net/sock.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_cache.h>

#समावेश "smc.h"
#समावेश "smc_clc.h"
#समावेश "smc_core.h"
#समावेश "smc_ib.h"
#समावेश "smc_wr.h"
#समावेश "smc_llc.h"
#समावेश "smc_cdc.h"
#समावेश "smc_close.h"
#समावेश "smc_ism.h"
#समावेश "smc_netlink.h"

#घोषणा SMC_LGR_NUM_INCR		256
#घोषणा SMC_LGR_FREE_DELAY_SERV		(600 * HZ)
#घोषणा SMC_LGR_FREE_DELAY_CLNT		(SMC_LGR_FREE_DELAY_SERV + 10 * HZ)

काष्ठा smc_lgr_list smc_lgr_list = अणु	/* established link groups */
	.lock = __SPIN_LOCK_UNLOCKED(smc_lgr_list.lock),
	.list = LIST_HEAD_INIT(smc_lgr_list.list),
	.num = 0,
पूर्ण;

अटल atomic_t lgr_cnt = ATOMIC_INIT(0); /* number of existing link groups */
अटल DECLARE_WAIT_QUEUE_HEAD(lgrs_deleted);

अटल व्योम smc_buf_मुक्त(काष्ठा smc_link_group *lgr, bool is_rmb,
			 काष्ठा smc_buf_desc *buf_desc);
अटल व्योम __smc_lgr_terminate(काष्ठा smc_link_group *lgr, bool soft);

अटल व्योम smc_link_करोwn_work(काष्ठा work_काष्ठा *work);

/* वापस head of link group list and its lock क्रम a given link group */
अटल अंतरभूत काष्ठा list_head *smc_lgr_list_head(काष्ठा smc_link_group *lgr,
						  spinlock_t **lgr_lock)
अणु
	अगर (lgr->is_smcd) अणु
		*lgr_lock = &lgr->smcd->lgr_lock;
		वापस &lgr->smcd->lgr_list;
	पूर्ण

	*lgr_lock = &smc_lgr_list.lock;
	वापस &smc_lgr_list.list;
पूर्ण

अटल व्योम smc_ibdev_cnt_inc(काष्ठा smc_link *lnk)
अणु
	atomic_inc(&lnk->smcibdev->lnk_cnt_by_port[lnk->ibport - 1]);
पूर्ण

अटल व्योम smc_ibdev_cnt_dec(काष्ठा smc_link *lnk)
अणु
	atomic_dec(&lnk->smcibdev->lnk_cnt_by_port[lnk->ibport - 1]);
पूर्ण

अटल व्योम smc_lgr_schedule_मुक्त_work(काष्ठा smc_link_group *lgr)
अणु
	/* client link group creation always follows the server link group
	 * creation. For client use a somewhat higher removal delay समय,
	 * otherwise there is a risk of out-of-sync link groups.
	 */
	अगर (!lgr->मुक्तing) अणु
		mod_delayed_work(प्रणाली_wq, &lgr->मुक्त_work,
				 (!lgr->is_smcd && lgr->role == SMC_CLNT) ?
						SMC_LGR_FREE_DELAY_CLNT :
						SMC_LGR_FREE_DELAY_SERV);
	पूर्ण
पूर्ण

/* Register connection's alert token in our lookup काष्ठाure.
 * To use rbtrees we have to implement our own insert core.
 * Requires @conns_lock
 * @smc		connection to रेजिस्टर
 * Returns 0 on success, != otherwise.
 */
अटल व्योम smc_lgr_add_alert_token(काष्ठा smc_connection *conn)
अणु
	काष्ठा rb_node **link, *parent = शून्य;
	u32 token = conn->alert_token_local;

	link = &conn->lgr->conns_all.rb_node;
	जबतक (*link) अणु
		काष्ठा smc_connection *cur = rb_entry(*link,
					काष्ठा smc_connection, alert_node);

		parent = *link;
		अगर (cur->alert_token_local > token)
			link = &parent->rb_left;
		अन्यथा
			link = &parent->rb_right;
	पूर्ण
	/* Put the new node there */
	rb_link_node(&conn->alert_node, parent, link);
	rb_insert_color(&conn->alert_node, &conn->lgr->conns_all);
पूर्ण

/* assign an SMC-R link to the connection */
अटल पूर्णांक smcr_lgr_conn_assign_link(काष्ठा smc_connection *conn, bool first)
अणु
	क्रमागत smc_link_state expected = first ? SMC_LNK_ACTIVATING :
				       SMC_LNK_ACTIVE;
	पूर्णांक i, j;

	/* करो link balancing */
	क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++) अणु
		काष्ठा smc_link *lnk = &conn->lgr->lnk[i];

		अगर (lnk->state != expected || lnk->link_is_asym)
			जारी;
		अगर (conn->lgr->role == SMC_CLNT) अणु
			conn->lnk = lnk; /* temporary, SMC server assigns link*/
			अवरोध;
		पूर्ण
		अगर (conn->lgr->conns_num % 2) अणु
			क्रम (j = i + 1; j < SMC_LINKS_PER_LGR_MAX; j++) अणु
				काष्ठा smc_link *lnk2;

				lnk2 = &conn->lgr->lnk[j];
				अगर (lnk2->state == expected &&
				    !lnk2->link_is_asym) अणु
					conn->lnk = lnk2;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (!conn->lnk)
			conn->lnk = lnk;
		अवरोध;
	पूर्ण
	अगर (!conn->lnk)
		वापस SMC_CLC_DECL_NOACTLINK;
	atomic_inc(&conn->lnk->conn_cnt);
	वापस 0;
पूर्ण

/* Register connection in link group by assigning an alert token
 * रेजिस्टरed in a search tree.
 * Requires @conns_lock
 * Note that '0' is a reserved value and not asचिन्हित.
 */
अटल पूर्णांक smc_lgr_रेजिस्टर_conn(काष्ठा smc_connection *conn, bool first)
अणु
	काष्ठा smc_sock *smc = container_of(conn, काष्ठा smc_sock, conn);
	अटल atomic_t nexttoken = ATOMIC_INIT(0);
	पूर्णांक rc;

	अगर (!conn->lgr->is_smcd) अणु
		rc = smcr_lgr_conn_assign_link(conn, first);
		अगर (rc)
			वापस rc;
	पूर्ण
	/* find a new alert_token_local value not yet used by some connection
	 * in this link group
	 */
	sock_hold(&smc->sk); /* sock_put in smc_lgr_unरेजिस्टर_conn() */
	जबतक (!conn->alert_token_local) अणु
		conn->alert_token_local = atomic_inc_वापस(&nexttoken);
		अगर (smc_lgr_find_conn(conn->alert_token_local, conn->lgr))
			conn->alert_token_local = 0;
	पूर्ण
	smc_lgr_add_alert_token(conn);
	conn->lgr->conns_num++;
	वापस 0;
पूर्ण

/* Unरेजिस्टर connection and reset the alert token of the given connection<
 */
अटल व्योम __smc_lgr_unरेजिस्टर_conn(काष्ठा smc_connection *conn)
अणु
	काष्ठा smc_sock *smc = container_of(conn, काष्ठा smc_sock, conn);
	काष्ठा smc_link_group *lgr = conn->lgr;

	rb_erase(&conn->alert_node, &lgr->conns_all);
	अगर (conn->lnk)
		atomic_dec(&conn->lnk->conn_cnt);
	lgr->conns_num--;
	conn->alert_token_local = 0;
	sock_put(&smc->sk); /* sock_hold in smc_lgr_रेजिस्टर_conn() */
पूर्ण

/* Unरेजिस्टर connection from lgr
 */
अटल व्योम smc_lgr_unरेजिस्टर_conn(काष्ठा smc_connection *conn)
अणु
	काष्ठा smc_link_group *lgr = conn->lgr;

	अगर (!lgr)
		वापस;
	ग_लिखो_lock_bh(&lgr->conns_lock);
	अगर (conn->alert_token_local) अणु
		__smc_lgr_unरेजिस्टर_conn(conn);
	पूर्ण
	ग_लिखो_unlock_bh(&lgr->conns_lock);
	conn->lgr = शून्य;
पूर्ण

पूर्णांक smc_nl_get_sys_info(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा smc_nl_dmp_ctx *cb_ctx = smc_nl_dmp_ctx(cb);
	अक्षर hostname[SMC_MAX_HOSTNAME_LEN + 1];
	अक्षर smc_seid[SMC_MAX_EID_LEN + 1];
	काष्ठा smcd_dev *smcd_dev;
	काष्ठा nlattr *attrs;
	u8 *seid = शून्य;
	u8 *host = शून्य;
	व्योम *nlh;

	nlh = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &smc_gen_nl_family, NLM_F_MULTI,
			  SMC_NETLINK_GET_SYS_INFO);
	अगर (!nlh)
		जाओ errmsg;
	अगर (cb_ctx->pos[0])
		जाओ errout;
	attrs = nla_nest_start(skb, SMC_GEN_SYS_INFO);
	अगर (!attrs)
		जाओ errout;
	अगर (nla_put_u8(skb, SMC_NLA_SYS_VER, SMC_V2))
		जाओ errattr;
	अगर (nla_put_u8(skb, SMC_NLA_SYS_REL, SMC_RELEASE))
		जाओ errattr;
	अगर (nla_put_u8(skb, SMC_NLA_SYS_IS_ISM_V2, smc_ism_is_v2_capable()))
		जाओ errattr;
	smc_clc_get_hostname(&host);
	अगर (host) अणु
		स_नकल(hostname, host, SMC_MAX_HOSTNAME_LEN);
		hostname[SMC_MAX_HOSTNAME_LEN] = 0;
		अगर (nla_put_string(skb, SMC_NLA_SYS_LOCAL_HOST, hostname))
			जाओ errattr;
	पूर्ण
	mutex_lock(&smcd_dev_list.mutex);
	smcd_dev = list_first_entry_or_null(&smcd_dev_list.list,
					    काष्ठा smcd_dev, list);
	अगर (smcd_dev)
		smc_ism_get_प्रणाली_eid(smcd_dev, &seid);
	mutex_unlock(&smcd_dev_list.mutex);
	अगर (seid && smc_ism_is_v2_capable()) अणु
		स_नकल(smc_seid, seid, SMC_MAX_EID_LEN);
		smc_seid[SMC_MAX_EID_LEN] = 0;
		अगर (nla_put_string(skb, SMC_NLA_SYS_SEID, smc_seid))
			जाओ errattr;
	पूर्ण
	nla_nest_end(skb, attrs);
	genlmsg_end(skb, nlh);
	cb_ctx->pos[0] = 1;
	वापस skb->len;

errattr:
	nla_nest_cancel(skb, attrs);
errout:
	genlmsg_cancel(skb, nlh);
errmsg:
	वापस skb->len;
पूर्ण

अटल पूर्णांक smc_nl_fill_lgr(काष्ठा smc_link_group *lgr,
			   काष्ठा sk_buff *skb,
			   काष्ठा netlink_callback *cb)
अणु
	अक्षर smc_target[SMC_MAX_PNETID_LEN + 1];
	काष्ठा nlattr *attrs;

	attrs = nla_nest_start(skb, SMC_GEN_LGR_SMCR);
	अगर (!attrs)
		जाओ errout;

	अगर (nla_put_u32(skb, SMC_NLA_LGR_R_ID, *((u32 *)&lgr->id)))
		जाओ errattr;
	अगर (nla_put_u32(skb, SMC_NLA_LGR_R_CONNS_NUM, lgr->conns_num))
		जाओ errattr;
	अगर (nla_put_u8(skb, SMC_NLA_LGR_R_ROLE, lgr->role))
		जाओ errattr;
	अगर (nla_put_u8(skb, SMC_NLA_LGR_R_TYPE, lgr->type))
		जाओ errattr;
	अगर (nla_put_u8(skb, SMC_NLA_LGR_R_VLAN_ID, lgr->vlan_id))
		जाओ errattr;
	स_नकल(smc_target, lgr->pnet_id, SMC_MAX_PNETID_LEN);
	smc_target[SMC_MAX_PNETID_LEN] = 0;
	अगर (nla_put_string(skb, SMC_NLA_LGR_R_PNETID, smc_target))
		जाओ errattr;

	nla_nest_end(skb, attrs);
	वापस 0;
errattr:
	nla_nest_cancel(skb, attrs);
errout:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक smc_nl_fill_lgr_link(काष्ठा smc_link_group *lgr,
				काष्ठा smc_link *link,
				काष्ठा sk_buff *skb,
				काष्ठा netlink_callback *cb)
अणु
	अक्षर smc_ibname[IB_DEVICE_NAME_MAX];
	u8 smc_gid_target[41];
	काष्ठा nlattr *attrs;
	u32 link_uid = 0;
	व्योम *nlh;

	nlh = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &smc_gen_nl_family, NLM_F_MULTI,
			  SMC_NETLINK_GET_LINK_SMCR);
	अगर (!nlh)
		जाओ errmsg;

	attrs = nla_nest_start(skb, SMC_GEN_LINK_SMCR);
	अगर (!attrs)
		जाओ errout;

	अगर (nla_put_u8(skb, SMC_NLA_LINK_ID, link->link_id))
		जाओ errattr;
	अगर (nla_put_u32(skb, SMC_NLA_LINK_STATE, link->state))
		जाओ errattr;
	अगर (nla_put_u32(skb, SMC_NLA_LINK_CONN_CNT,
			atomic_पढ़ो(&link->conn_cnt)))
		जाओ errattr;
	अगर (nla_put_u8(skb, SMC_NLA_LINK_IB_PORT, link->ibport))
		जाओ errattr;
	अगर (nla_put_u32(skb, SMC_NLA_LINK_NET_DEV, link->ndev_अगरidx))
		जाओ errattr;
	snम_लिखो(smc_ibname, माप(smc_ibname), "%s", link->ibname);
	अगर (nla_put_string(skb, SMC_NLA_LINK_IB_DEV, smc_ibname))
		जाओ errattr;
	स_नकल(&link_uid, link->link_uid, माप(link_uid));
	अगर (nla_put_u32(skb, SMC_NLA_LINK_UID, link_uid))
		जाओ errattr;
	स_नकल(&link_uid, link->peer_link_uid, माप(link_uid));
	अगर (nla_put_u32(skb, SMC_NLA_LINK_PEER_UID, link_uid))
		जाओ errattr;
	स_रखो(smc_gid_target, 0, माप(smc_gid_target));
	smc_gid_be16_convert(smc_gid_target, link->gid);
	अगर (nla_put_string(skb, SMC_NLA_LINK_GID, smc_gid_target))
		जाओ errattr;
	स_रखो(smc_gid_target, 0, माप(smc_gid_target));
	smc_gid_be16_convert(smc_gid_target, link->peer_gid);
	अगर (nla_put_string(skb, SMC_NLA_LINK_PEER_GID, smc_gid_target))
		जाओ errattr;

	nla_nest_end(skb, attrs);
	genlmsg_end(skb, nlh);
	वापस 0;
errattr:
	nla_nest_cancel(skb, attrs);
errout:
	genlmsg_cancel(skb, nlh);
errmsg:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक smc_nl_handle_lgr(काष्ठा smc_link_group *lgr,
			     काष्ठा sk_buff *skb,
			     काष्ठा netlink_callback *cb,
			     bool list_links)
अणु
	व्योम *nlh;
	पूर्णांक i;

	nlh = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &smc_gen_nl_family, NLM_F_MULTI,
			  SMC_NETLINK_GET_LGR_SMCR);
	अगर (!nlh)
		जाओ errmsg;
	अगर (smc_nl_fill_lgr(lgr, skb, cb))
		जाओ errout;

	genlmsg_end(skb, nlh);
	अगर (!list_links)
		जाओ out;
	क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++) अणु
		अगर (!smc_link_usable(&lgr->lnk[i]))
			जारी;
		अगर (smc_nl_fill_lgr_link(lgr, &lgr->lnk[i], skb, cb))
			जाओ errout;
	पूर्ण
out:
	वापस 0;

errout:
	genlmsg_cancel(skb, nlh);
errmsg:
	वापस -EMSGSIZE;
पूर्ण

अटल व्योम smc_nl_fill_lgr_list(काष्ठा smc_lgr_list *smc_lgr,
				 काष्ठा sk_buff *skb,
				 काष्ठा netlink_callback *cb,
				 bool list_links)
अणु
	काष्ठा smc_nl_dmp_ctx *cb_ctx = smc_nl_dmp_ctx(cb);
	काष्ठा smc_link_group *lgr;
	पूर्णांक snum = cb_ctx->pos[0];
	पूर्णांक num = 0;

	spin_lock_bh(&smc_lgr->lock);
	list_क्रम_each_entry(lgr, &smc_lgr->list, list) अणु
		अगर (num < snum)
			जाओ next;
		अगर (smc_nl_handle_lgr(lgr, skb, cb, list_links))
			जाओ errout;
next:
		num++;
	पूर्ण
errout:
	spin_unlock_bh(&smc_lgr->lock);
	cb_ctx->pos[0] = num;
पूर्ण

अटल पूर्णांक smc_nl_fill_smcd_lgr(काष्ठा smc_link_group *lgr,
				काष्ठा sk_buff *skb,
				काष्ठा netlink_callback *cb)
अणु
	अक्षर smc_host[SMC_MAX_HOSTNAME_LEN + 1];
	अक्षर smc_pnet[SMC_MAX_PNETID_LEN + 1];
	अक्षर smc_eid[SMC_MAX_EID_LEN + 1];
	काष्ठा nlattr *v2_attrs;
	काष्ठा nlattr *attrs;
	व्योम *nlh;

	nlh = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &smc_gen_nl_family, NLM_F_MULTI,
			  SMC_NETLINK_GET_LGR_SMCD);
	अगर (!nlh)
		जाओ errmsg;

	attrs = nla_nest_start(skb, SMC_GEN_LGR_SMCD);
	अगर (!attrs)
		जाओ errout;

	अगर (nla_put_u32(skb, SMC_NLA_LGR_D_ID, *((u32 *)&lgr->id)))
		जाओ errattr;
	अगर (nla_put_u64_64bit(skb, SMC_NLA_LGR_D_GID, lgr->smcd->local_gid,
			      SMC_NLA_LGR_D_PAD))
		जाओ errattr;
	अगर (nla_put_u64_64bit(skb, SMC_NLA_LGR_D_PEER_GID, lgr->peer_gid,
			      SMC_NLA_LGR_D_PAD))
		जाओ errattr;
	अगर (nla_put_u8(skb, SMC_NLA_LGR_D_VLAN_ID, lgr->vlan_id))
		जाओ errattr;
	अगर (nla_put_u32(skb, SMC_NLA_LGR_D_CONNS_NUM, lgr->conns_num))
		जाओ errattr;
	अगर (nla_put_u32(skb, SMC_NLA_LGR_D_CHID, smc_ism_get_chid(lgr->smcd)))
		जाओ errattr;
	स_नकल(smc_pnet, lgr->smcd->pnetid, SMC_MAX_PNETID_LEN);
	smc_pnet[SMC_MAX_PNETID_LEN] = 0;
	अगर (nla_put_string(skb, SMC_NLA_LGR_D_PNETID, smc_pnet))
		जाओ errattr;

	v2_attrs = nla_nest_start(skb, SMC_NLA_LGR_V2);
	अगर (!v2_attrs)
		जाओ errattr;
	अगर (nla_put_u8(skb, SMC_NLA_LGR_V2_VER, lgr->smc_version))
		जाओ errv2attr;
	अगर (nla_put_u8(skb, SMC_NLA_LGR_V2_REL, lgr->peer_smc_release))
		जाओ errv2attr;
	अगर (nla_put_u8(skb, SMC_NLA_LGR_V2_OS, lgr->peer_os))
		जाओ errv2attr;
	स_नकल(smc_host, lgr->peer_hostname, SMC_MAX_HOSTNAME_LEN);
	smc_host[SMC_MAX_HOSTNAME_LEN] = 0;
	अगर (nla_put_string(skb, SMC_NLA_LGR_V2_PEER_HOST, smc_host))
		जाओ errv2attr;
	स_नकल(smc_eid, lgr->negotiated_eid, SMC_MAX_EID_LEN);
	smc_eid[SMC_MAX_EID_LEN] = 0;
	अगर (nla_put_string(skb, SMC_NLA_LGR_V2_NEG_EID, smc_eid))
		जाओ errv2attr;

	nla_nest_end(skb, v2_attrs);
	nla_nest_end(skb, attrs);
	genlmsg_end(skb, nlh);
	वापस 0;

errv2attr:
	nla_nest_cancel(skb, v2_attrs);
errattr:
	nla_nest_cancel(skb, attrs);
errout:
	genlmsg_cancel(skb, nlh);
errmsg:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक smc_nl_handle_smcd_lgr(काष्ठा smcd_dev *dev,
				  काष्ठा sk_buff *skb,
				  काष्ठा netlink_callback *cb)
अणु
	काष्ठा smc_nl_dmp_ctx *cb_ctx = smc_nl_dmp_ctx(cb);
	काष्ठा smc_link_group *lgr;
	पूर्णांक snum = cb_ctx->pos[1];
	पूर्णांक rc = 0, num = 0;

	spin_lock_bh(&dev->lgr_lock);
	list_क्रम_each_entry(lgr, &dev->lgr_list, list) अणु
		अगर (!lgr->is_smcd)
			जारी;
		अगर (num < snum)
			जाओ next;
		rc = smc_nl_fill_smcd_lgr(lgr, skb, cb);
		अगर (rc)
			जाओ errout;
next:
		num++;
	पूर्ण
errout:
	spin_unlock_bh(&dev->lgr_lock);
	cb_ctx->pos[1] = num;
	वापस rc;
पूर्ण

अटल पूर्णांक smc_nl_fill_smcd_dev(काष्ठा smcd_dev_list *dev_list,
				काष्ठा sk_buff *skb,
				काष्ठा netlink_callback *cb)
अणु
	काष्ठा smc_nl_dmp_ctx *cb_ctx = smc_nl_dmp_ctx(cb);
	काष्ठा smcd_dev *smcd_dev;
	पूर्णांक snum = cb_ctx->pos[0];
	पूर्णांक rc = 0, num = 0;

	mutex_lock(&dev_list->mutex);
	list_क्रम_each_entry(smcd_dev, &dev_list->list, list) अणु
		अगर (list_empty(&smcd_dev->lgr_list))
			जारी;
		अगर (num < snum)
			जाओ next;
		rc = smc_nl_handle_smcd_lgr(smcd_dev, skb, cb);
		अगर (rc)
			जाओ errout;
next:
		num++;
	पूर्ण
errout:
	mutex_unlock(&dev_list->mutex);
	cb_ctx->pos[0] = num;
	वापस rc;
पूर्ण

पूर्णांक smcr_nl_get_lgr(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	bool list_links = false;

	smc_nl_fill_lgr_list(&smc_lgr_list, skb, cb, list_links);
	वापस skb->len;
पूर्ण

पूर्णांक smcr_nl_get_link(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	bool list_links = true;

	smc_nl_fill_lgr_list(&smc_lgr_list, skb, cb, list_links);
	वापस skb->len;
पूर्ण

पूर्णांक smcd_nl_get_lgr(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	smc_nl_fill_smcd_dev(&smcd_dev_list, skb, cb);
	वापस skb->len;
पूर्ण

व्योम smc_lgr_cleanup_early(काष्ठा smc_connection *conn)
अणु
	काष्ठा smc_link_group *lgr = conn->lgr;
	काष्ठा list_head *lgr_list;
	spinlock_t *lgr_lock;

	अगर (!lgr)
		वापस;

	smc_conn_मुक्त(conn);
	lgr_list = smc_lgr_list_head(lgr, &lgr_lock);
	spin_lock_bh(lgr_lock);
	/* करो not use this link group क्रम new connections */
	अगर (!list_empty(lgr_list))
		list_del_init(lgr_list);
	spin_unlock_bh(lgr_lock);
	__smc_lgr_terminate(lgr, true);
पूर्ण

अटल व्योम smcr_lgr_link_deactivate_all(काष्ठा smc_link_group *lgr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++) अणु
		काष्ठा smc_link *lnk = &lgr->lnk[i];

		अगर (smc_link_usable(lnk))
			lnk->state = SMC_LNK_INACTIVE;
	पूर्ण
	wake_up_all(&lgr->llc_msg_रुकोer);
	wake_up_all(&lgr->llc_flow_रुकोer);
पूर्ण

अटल व्योम smc_lgr_मुक्त(काष्ठा smc_link_group *lgr);

अटल व्योम smc_lgr_मुक्त_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smc_link_group *lgr = container_of(to_delayed_work(work),
						  काष्ठा smc_link_group,
						  मुक्त_work);
	spinlock_t *lgr_lock;
	bool conns;

	smc_lgr_list_head(lgr, &lgr_lock);
	spin_lock_bh(lgr_lock);
	अगर (lgr->मुक्तing) अणु
		spin_unlock_bh(lgr_lock);
		वापस;
	पूर्ण
	पढ़ो_lock_bh(&lgr->conns_lock);
	conns = RB_EMPTY_ROOT(&lgr->conns_all);
	पढ़ो_unlock_bh(&lgr->conns_lock);
	अगर (!conns) अणु /* number of lgr connections is no दीर्घer zero */
		spin_unlock_bh(lgr_lock);
		वापस;
	पूर्ण
	list_del_init(&lgr->list); /* हटाओ from smc_lgr_list */
	lgr->मुक्तing = 1; /* this instance करोes the मुक्तing, no new schedule */
	spin_unlock_bh(lgr_lock);
	cancel_delayed_work(&lgr->मुक्त_work);

	अगर (!lgr->is_smcd && !lgr->terminating)
		smc_llc_send_link_delete_all(lgr, true,
					     SMC_LLC_DEL_PROG_INIT_TERM);
	अगर (lgr->is_smcd && !lgr->terminating)
		smc_ism_संकेत_shutकरोwn(lgr);
	अगर (!lgr->is_smcd)
		smcr_lgr_link_deactivate_all(lgr);
	smc_lgr_मुक्त(lgr);
पूर्ण

अटल व्योम smc_lgr_terminate_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smc_link_group *lgr = container_of(work, काष्ठा smc_link_group,
						  terminate_work);

	__smc_lgr_terminate(lgr, true);
पूर्ण

/* वापस next unique link id क्रम the lgr */
अटल u8 smcr_next_link_id(काष्ठा smc_link_group *lgr)
अणु
	u8 link_id;
	पूर्णांक i;

	जबतक (1) अणु
		link_id = ++lgr->next_link_id;
		अगर (!link_id)	/* skip zero as link_id */
			link_id = ++lgr->next_link_id;
		क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++) अणु
			अगर (smc_link_usable(&lgr->lnk[i]) &&
			    lgr->lnk[i].link_id == link_id)
				जारी;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस link_id;
पूर्ण

अटल व्योम smcr_copy_dev_info_to_link(काष्ठा smc_link *link)
अणु
	काष्ठा smc_ib_device *smcibdev = link->smcibdev;

	snम_लिखो(link->ibname, माप(link->ibname), "%s",
		 smcibdev->ibdev->name);
	link->ndev_अगरidx = smcibdev->ndev_अगरidx[link->ibport - 1];
पूर्ण

पूर्णांक smcr_link_init(काष्ठा smc_link_group *lgr, काष्ठा smc_link *lnk,
		   u8 link_idx, काष्ठा smc_init_info *ini)
अणु
	u8 rndvec[3];
	पूर्णांक rc;

	get_device(&ini->ib_dev->ibdev->dev);
	atomic_inc(&ini->ib_dev->lnk_cnt);
	lnk->link_id = smcr_next_link_id(lgr);
	lnk->lgr = lgr;
	lnk->link_idx = link_idx;
	lnk->smcibdev = ini->ib_dev;
	lnk->ibport = ini->ib_port;
	smc_ibdev_cnt_inc(lnk);
	smcr_copy_dev_info_to_link(lnk);
	lnk->path_mtu = ini->ib_dev->pattr[ini->ib_port - 1].active_mtu;
	atomic_set(&lnk->conn_cnt, 0);
	smc_llc_link_set_uid(lnk);
	INIT_WORK(&lnk->link_करोwn_wrk, smc_link_करोwn_work);
	अगर (!ini->ib_dev->initialized) अणु
		rc = (पूर्णांक)smc_ib_setup_per_ibdev(ini->ib_dev);
		अगर (rc)
			जाओ out;
	पूर्ण
	get_अक्रमom_bytes(rndvec, माप(rndvec));
	lnk->psn_initial = rndvec[0] + (rndvec[1] << 8) +
		(rndvec[2] << 16);
	rc = smc_ib_determine_gid(lnk->smcibdev, lnk->ibport,
				  ini->vlan_id, lnk->gid, &lnk->sgid_index);
	अगर (rc)
		जाओ out;
	rc = smc_llc_link_init(lnk);
	अगर (rc)
		जाओ out;
	rc = smc_wr_alloc_link_mem(lnk);
	अगर (rc)
		जाओ clear_llc_lnk;
	rc = smc_ib_create_protection_करोमुख्य(lnk);
	अगर (rc)
		जाओ मुक्त_link_mem;
	rc = smc_ib_create_queue_pair(lnk);
	अगर (rc)
		जाओ dealloc_pd;
	rc = smc_wr_create_link(lnk);
	अगर (rc)
		जाओ destroy_qp;
	lnk->state = SMC_LNK_ACTIVATING;
	वापस 0;

destroy_qp:
	smc_ib_destroy_queue_pair(lnk);
dealloc_pd:
	smc_ib_dealloc_protection_करोमुख्य(lnk);
मुक्त_link_mem:
	smc_wr_मुक्त_link_mem(lnk);
clear_llc_lnk:
	smc_llc_link_clear(lnk, false);
out:
	smc_ibdev_cnt_dec(lnk);
	put_device(&ini->ib_dev->ibdev->dev);
	स_रखो(lnk, 0, माप(काष्ठा smc_link));
	lnk->state = SMC_LNK_UNUSED;
	अगर (!atomic_dec_वापस(&ini->ib_dev->lnk_cnt))
		wake_up(&ini->ib_dev->lnks_deleted);
	वापस rc;
पूर्ण

/* create a new SMC link group */
अटल पूर्णांक smc_lgr_create(काष्ठा smc_sock *smc, काष्ठा smc_init_info *ini)
अणु
	काष्ठा smc_link_group *lgr;
	काष्ठा list_head *lgr_list;
	काष्ठा smc_link *lnk;
	spinlock_t *lgr_lock;
	u8 link_idx;
	पूर्णांक rc = 0;
	पूर्णांक i;

	अगर (ini->is_smcd && ini->vlan_id) अणु
		अगर (smc_ism_get_vlan(ini->ism_dev[ini->ism_selected],
				     ini->vlan_id)) अणु
			rc = SMC_CLC_DECL_ISMVLANERR;
			जाओ out;
		पूर्ण
	पूर्ण

	lgr = kzalloc(माप(*lgr), GFP_KERNEL);
	अगर (!lgr) अणु
		rc = SMC_CLC_DECL_MEM;
		जाओ ism_put_vlan;
	पूर्ण
	lgr->tx_wq = alloc_workqueue("smc_tx_wq-%*phN", 0, 0,
				     SMC_LGR_ID_SIZE, &lgr->id);
	अगर (!lgr->tx_wq) अणु
		rc = -ENOMEM;
		जाओ मुक्त_lgr;
	पूर्ण
	lgr->is_smcd = ini->is_smcd;
	lgr->sync_err = 0;
	lgr->terminating = 0;
	lgr->मुक्तing = 0;
	lgr->vlan_id = ini->vlan_id;
	mutex_init(&lgr->sndbufs_lock);
	mutex_init(&lgr->rmbs_lock);
	rwlock_init(&lgr->conns_lock);
	क्रम (i = 0; i < SMC_RMBE_SIZES; i++) अणु
		INIT_LIST_HEAD(&lgr->sndbufs[i]);
		INIT_LIST_HEAD(&lgr->rmbs[i]);
	पूर्ण
	lgr->next_link_id = 0;
	smc_lgr_list.num += SMC_LGR_NUM_INCR;
	स_नकल(&lgr->id, (u8 *)&smc_lgr_list.num, SMC_LGR_ID_SIZE);
	INIT_DELAYED_WORK(&lgr->मुक्त_work, smc_lgr_मुक्त_work);
	INIT_WORK(&lgr->terminate_work, smc_lgr_terminate_work);
	lgr->conns_all = RB_ROOT;
	अगर (ini->is_smcd) अणु
		/* SMC-D specअगरic settings */
		get_device(&ini->ism_dev[ini->ism_selected]->dev);
		lgr->peer_gid = ini->ism_peer_gid[ini->ism_selected];
		lgr->smcd = ini->ism_dev[ini->ism_selected];
		lgr_list = &ini->ism_dev[ini->ism_selected]->lgr_list;
		lgr_lock = &lgr->smcd->lgr_lock;
		lgr->smc_version = ini->smcd_version;
		lgr->peer_shutकरोwn = 0;
		atomic_inc(&ini->ism_dev[ini->ism_selected]->lgr_cnt);
	पूर्ण अन्यथा अणु
		/* SMC-R specअगरic settings */
		lgr->role = smc->listen_smc ? SMC_SERV : SMC_CLNT;
		स_नकल(lgr->peer_प्रणालीid, ini->ib_lcl->id_क्रम_peer,
		       SMC_SYSTEMID_LEN);
		स_नकल(lgr->pnet_id, ini->ib_dev->pnetid[ini->ib_port - 1],
		       SMC_MAX_PNETID_LEN);
		smc_llc_lgr_init(lgr, smc);

		link_idx = SMC_SINGLE_LINK;
		lnk = &lgr->lnk[link_idx];
		rc = smcr_link_init(lgr, lnk, link_idx, ini);
		अगर (rc)
			जाओ मुक्त_wq;
		lgr_list = &smc_lgr_list.list;
		lgr_lock = &smc_lgr_list.lock;
		atomic_inc(&lgr_cnt);
	पूर्ण
	smc->conn.lgr = lgr;
	spin_lock_bh(lgr_lock);
	list_add_tail(&lgr->list, lgr_list);
	spin_unlock_bh(lgr_lock);
	वापस 0;

मुक्त_wq:
	destroy_workqueue(lgr->tx_wq);
मुक्त_lgr:
	kमुक्त(lgr);
ism_put_vlan:
	अगर (ini->is_smcd && ini->vlan_id)
		smc_ism_put_vlan(ini->ism_dev[ini->ism_selected], ini->vlan_id);
out:
	अगर (rc < 0) अणु
		अगर (rc == -ENOMEM)
			rc = SMC_CLC_DECL_MEM;
		अन्यथा
			rc = SMC_CLC_DECL_INTERR;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक smc_ग_लिखो_space(काष्ठा smc_connection *conn)
अणु
	पूर्णांक buffer_len = conn->peer_rmbe_size;
	जोड़ smc_host_cursor prod;
	जोड़ smc_host_cursor cons;
	पूर्णांक space;

	smc_curs_copy(&prod, &conn->local_tx_ctrl.prod, conn);
	smc_curs_copy(&cons, &conn->local_rx_ctrl.cons, conn);
	/* determine rx_buf space */
	space = buffer_len - smc_curs_dअगरf(buffer_len, &cons, &prod);
	वापस space;
पूर्ण

अटल पूर्णांक smc_चयन_cursor(काष्ठा smc_sock *smc, काष्ठा smc_cdc_tx_pend *pend,
			     काष्ठा smc_wr_buf *wr_buf)
अणु
	काष्ठा smc_connection *conn = &smc->conn;
	जोड़ smc_host_cursor cons, fin;
	पूर्णांक rc = 0;
	पूर्णांक dअगरf;

	smc_curs_copy(&conn->tx_curs_sent, &conn->tx_curs_fin, conn);
	smc_curs_copy(&fin, &conn->local_tx_ctrl_fin, conn);
	/* set prod cursor to old state, enक्रमce tx_rdma_ग_लिखोs() */
	smc_curs_copy(&conn->local_tx_ctrl.prod, &fin, conn);
	smc_curs_copy(&cons, &conn->local_rx_ctrl.cons, conn);

	अगर (smc_curs_comp(conn->peer_rmbe_size, &cons, &fin) < 0) अणु
		/* cons cursor advanced more than fin, and prod was set
		 * fin above, so now prod is smaller than cons. Fix that.
		 */
		dअगरf = smc_curs_dअगरf(conn->peer_rmbe_size, &fin, &cons);
		smc_curs_add(conn->sndbuf_desc->len,
			     &conn->tx_curs_sent, dअगरf);
		smc_curs_add(conn->sndbuf_desc->len,
			     &conn->tx_curs_fin, dअगरf);

		smp_mb__beक्रमe_atomic();
		atomic_add(dअगरf, &conn->sndbuf_space);
		smp_mb__after_atomic();

		smc_curs_add(conn->peer_rmbe_size,
			     &conn->local_tx_ctrl.prod, dअगरf);
		smc_curs_add(conn->peer_rmbe_size,
			     &conn->local_tx_ctrl_fin, dअगरf);
	पूर्ण
	/* recalculate, value is used by tx_rdma_ग_लिखोs() */
	atomic_set(&smc->conn.peer_rmbe_space, smc_ग_लिखो_space(conn));

	अगर (smc->sk.sk_state != SMC_INIT &&
	    smc->sk.sk_state != SMC_CLOSED) अणु
		rc = smcr_cdc_msg_send_validation(conn, pend, wr_buf);
		अगर (!rc) अणु
			queue_delayed_work(conn->lgr->tx_wq, &conn->tx_work, 0);
			smc->sk.sk_data_पढ़ोy(&smc->sk);
		पूर्ण
	पूर्ण अन्यथा अणु
		smc_wr_tx_put_slot(conn->lnk,
				   (काष्ठा smc_wr_tx_pend_priv *)pend);
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम smc_चयन_link_and_count(काष्ठा smc_connection *conn,
				      काष्ठा smc_link *to_lnk)
अणु
	atomic_dec(&conn->lnk->conn_cnt);
	conn->lnk = to_lnk;
	atomic_inc(&conn->lnk->conn_cnt);
पूर्ण

काष्ठा smc_link *smc_चयन_conns(काष्ठा smc_link_group *lgr,
				  काष्ठा smc_link *from_lnk, bool is_dev_err)
अणु
	काष्ठा smc_link *to_lnk = शून्य;
	काष्ठा smc_cdc_tx_pend *pend;
	काष्ठा smc_connection *conn;
	काष्ठा smc_wr_buf *wr_buf;
	काष्ठा smc_sock *smc;
	काष्ठा rb_node *node;
	पूर्णांक i, rc = 0;

	/* link is inactive, wake up tx रुकोers */
	smc_wr_wakeup_tx_रुको(from_lnk);

	क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++) अणु
		अगर (!smc_link_active(&lgr->lnk[i]) || i == from_lnk->link_idx)
			जारी;
		अगर (is_dev_err && from_lnk->smcibdev == lgr->lnk[i].smcibdev &&
		    from_lnk->ibport == lgr->lnk[i].ibport) अणु
			जारी;
		पूर्ण
		to_lnk = &lgr->lnk[i];
		अवरोध;
	पूर्ण
	अगर (!to_lnk) अणु
		smc_lgr_terminate_sched(lgr);
		वापस शून्य;
	पूर्ण
again:
	पढ़ो_lock_bh(&lgr->conns_lock);
	क्रम (node = rb_first(&lgr->conns_all); node; node = rb_next(node)) अणु
		conn = rb_entry(node, काष्ठा smc_connection, alert_node);
		अगर (conn->lnk != from_lnk)
			जारी;
		smc = container_of(conn, काष्ठा smc_sock, conn);
		/* conn->lnk not yet set in SMC_INIT state */
		अगर (smc->sk.sk_state == SMC_INIT)
			जारी;
		अगर (smc->sk.sk_state == SMC_CLOSED ||
		    smc->sk.sk_state == SMC_PEERCLOSEWAIT1 ||
		    smc->sk.sk_state == SMC_PEERCLOSEWAIT2 ||
		    smc->sk.sk_state == SMC_APPFINCLOSEWAIT ||
		    smc->sk.sk_state == SMC_APPCLOSEWAIT1 ||
		    smc->sk.sk_state == SMC_APPCLOSEWAIT2 ||
		    smc->sk.sk_state == SMC_PEERFINCLOSEWAIT ||
		    smc->sk.sk_state == SMC_PEERABORTWAIT ||
		    smc->sk.sk_state == SMC_PROCESSABORT) अणु
			spin_lock_bh(&conn->send_lock);
			smc_चयन_link_and_count(conn, to_lnk);
			spin_unlock_bh(&conn->send_lock);
			जारी;
		पूर्ण
		sock_hold(&smc->sk);
		पढ़ो_unlock_bh(&lgr->conns_lock);
		/* pre-fetch buffer outside of send_lock, might sleep */
		rc = smc_cdc_get_मुक्त_slot(conn, to_lnk, &wr_buf, शून्य, &pend);
		अगर (rc) अणु
			smcr_link_करोwn_cond_sched(to_lnk);
			वापस शून्य;
		पूर्ण
		/* aव्योम race with smcr_tx_sndbuf_nonempty() */
		spin_lock_bh(&conn->send_lock);
		smc_चयन_link_and_count(conn, to_lnk);
		rc = smc_चयन_cursor(smc, pend, wr_buf);
		spin_unlock_bh(&conn->send_lock);
		sock_put(&smc->sk);
		अगर (rc) अणु
			smcr_link_करोwn_cond_sched(to_lnk);
			वापस शून्य;
		पूर्ण
		जाओ again;
	पूर्ण
	पढ़ो_unlock_bh(&lgr->conns_lock);
	वापस to_lnk;
पूर्ण

अटल व्योम smcr_buf_unuse(काष्ठा smc_buf_desc *rmb_desc,
			   काष्ठा smc_link_group *lgr)
अणु
	पूर्णांक rc;

	अगर (rmb_desc->is_conf_rkey && !list_empty(&lgr->list)) अणु
		/* unरेजिस्टर rmb with peer */
		rc = smc_llc_flow_initiate(lgr, SMC_LLC_FLOW_RKEY);
		अगर (!rc) अणु
			/* protect against smc_llc_cli_rkey_exchange() */
			mutex_lock(&lgr->llc_conf_mutex);
			smc_llc_करो_delete_rkey(lgr, rmb_desc);
			rmb_desc->is_conf_rkey = false;
			mutex_unlock(&lgr->llc_conf_mutex);
			smc_llc_flow_stop(lgr, &lgr->llc_flow_lcl);
		पूर्ण
	पूर्ण

	अगर (rmb_desc->is_reg_err) अणु
		/* buf registration failed, reuse not possible */
		mutex_lock(&lgr->rmbs_lock);
		list_del(&rmb_desc->list);
		mutex_unlock(&lgr->rmbs_lock);

		smc_buf_मुक्त(lgr, true, rmb_desc);
	पूर्ण अन्यथा अणु
		rmb_desc->used = 0;
	पूर्ण
पूर्ण

अटल व्योम smc_buf_unuse(काष्ठा smc_connection *conn,
			  काष्ठा smc_link_group *lgr)
अणु
	अगर (conn->sndbuf_desc)
		conn->sndbuf_desc->used = 0;
	अगर (conn->rmb_desc && lgr->is_smcd)
		conn->rmb_desc->used = 0;
	अन्यथा अगर (conn->rmb_desc)
		smcr_buf_unuse(conn->rmb_desc, lgr);
पूर्ण

/* हटाओ a finished connection from its link group */
व्योम smc_conn_मुक्त(काष्ठा smc_connection *conn)
अणु
	काष्ठा smc_link_group *lgr = conn->lgr;

	अगर (!lgr)
		वापस;
	अगर (lgr->is_smcd) अणु
		अगर (!list_empty(&lgr->list))
			smc_ism_unset_conn(conn);
		tasklet_समाप्त(&conn->rx_tsklet);
	पूर्ण अन्यथा अणु
		smc_cdc_tx_dismiss_slots(conn);
		अगर (current_work() != &conn->पात_work)
			cancel_work_sync(&conn->पात_work);
	पूर्ण
	अगर (!list_empty(&lgr->list)) अणु
		smc_lgr_unरेजिस्टर_conn(conn);
		smc_buf_unuse(conn, lgr); /* allow buffer reuse */
	पूर्ण

	अगर (!lgr->conns_num)
		smc_lgr_schedule_मुक्त_work(lgr);
पूर्ण

/* unरेजिस्टर a link from a buf_desc */
अटल व्योम smcr_buf_unmap_link(काष्ठा smc_buf_desc *buf_desc, bool is_rmb,
				काष्ठा smc_link *lnk)
अणु
	अगर (is_rmb)
		buf_desc->is_reg_mr[lnk->link_idx] = false;
	अगर (!buf_desc->is_map_ib[lnk->link_idx])
		वापस;
	अगर (is_rmb) अणु
		अगर (buf_desc->mr_rx[lnk->link_idx]) अणु
			smc_ib_put_memory_region(
					buf_desc->mr_rx[lnk->link_idx]);
			buf_desc->mr_rx[lnk->link_idx] = शून्य;
		पूर्ण
		smc_ib_buf_unmap_sg(lnk, buf_desc, DMA_FROM_DEVICE);
	पूर्ण अन्यथा अणु
		smc_ib_buf_unmap_sg(lnk, buf_desc, DMA_TO_DEVICE);
	पूर्ण
	sg_मुक्त_table(&buf_desc->sgt[lnk->link_idx]);
	buf_desc->is_map_ib[lnk->link_idx] = false;
पूर्ण

/* unmap all buffers of lgr क्रम a deleted link */
अटल व्योम smcr_buf_unmap_lgr(काष्ठा smc_link *lnk)
अणु
	काष्ठा smc_link_group *lgr = lnk->lgr;
	काष्ठा smc_buf_desc *buf_desc, *bf;
	पूर्णांक i;

	क्रम (i = 0; i < SMC_RMBE_SIZES; i++) अणु
		mutex_lock(&lgr->rmbs_lock);
		list_क्रम_each_entry_safe(buf_desc, bf, &lgr->rmbs[i], list)
			smcr_buf_unmap_link(buf_desc, true, lnk);
		mutex_unlock(&lgr->rmbs_lock);
		mutex_lock(&lgr->sndbufs_lock);
		list_क्रम_each_entry_safe(buf_desc, bf, &lgr->sndbufs[i],
					 list)
			smcr_buf_unmap_link(buf_desc, false, lnk);
		mutex_unlock(&lgr->sndbufs_lock);
	पूर्ण
पूर्ण

अटल व्योम smcr_rtoken_clear_link(काष्ठा smc_link *lnk)
अणु
	काष्ठा smc_link_group *lgr = lnk->lgr;
	पूर्णांक i;

	क्रम (i = 0; i < SMC_RMBS_PER_LGR_MAX; i++) अणु
		lgr->rtokens[i][lnk->link_idx].rkey = 0;
		lgr->rtokens[i][lnk->link_idx].dma_addr = 0;
	पूर्ण
पूर्ण

/* must be called under lgr->llc_conf_mutex lock */
व्योम smcr_link_clear(काष्ठा smc_link *lnk, bool log)
अणु
	काष्ठा smc_ib_device *smcibdev;

	अगर (!lnk->lgr || lnk->state == SMC_LNK_UNUSED)
		वापस;
	lnk->peer_qpn = 0;
	smc_llc_link_clear(lnk, log);
	smcr_buf_unmap_lgr(lnk);
	smcr_rtoken_clear_link(lnk);
	smc_ib_modअगरy_qp_reset(lnk);
	smc_wr_मुक्त_link(lnk);
	smc_ib_destroy_queue_pair(lnk);
	smc_ib_dealloc_protection_करोमुख्य(lnk);
	smc_wr_मुक्त_link_mem(lnk);
	smc_ibdev_cnt_dec(lnk);
	put_device(&lnk->smcibdev->ibdev->dev);
	smcibdev = lnk->smcibdev;
	स_रखो(lnk, 0, माप(काष्ठा smc_link));
	lnk->state = SMC_LNK_UNUSED;
	अगर (!atomic_dec_वापस(&smcibdev->lnk_cnt))
		wake_up(&smcibdev->lnks_deleted);
पूर्ण

अटल व्योम smcr_buf_मुक्त(काष्ठा smc_link_group *lgr, bool is_rmb,
			  काष्ठा smc_buf_desc *buf_desc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++)
		smcr_buf_unmap_link(buf_desc, is_rmb, &lgr->lnk[i]);

	अगर (buf_desc->pages)
		__मुक्त_pages(buf_desc->pages, buf_desc->order);
	kमुक्त(buf_desc);
पूर्ण

अटल व्योम smcd_buf_मुक्त(काष्ठा smc_link_group *lgr, bool is_dmb,
			  काष्ठा smc_buf_desc *buf_desc)
अणु
	अगर (is_dmb) अणु
		/* restore original buf len */
		buf_desc->len += माप(काष्ठा smcd_cdc_msg);
		smc_ism_unरेजिस्टर_dmb(lgr->smcd, buf_desc);
	पूर्ण अन्यथा अणु
		kमुक्त(buf_desc->cpu_addr);
	पूर्ण
	kमुक्त(buf_desc);
पूर्ण

अटल व्योम smc_buf_मुक्त(काष्ठा smc_link_group *lgr, bool is_rmb,
			 काष्ठा smc_buf_desc *buf_desc)
अणु
	अगर (lgr->is_smcd)
		smcd_buf_मुक्त(lgr, is_rmb, buf_desc);
	अन्यथा
		smcr_buf_मुक्त(lgr, is_rmb, buf_desc);
पूर्ण

अटल व्योम __smc_lgr_मुक्त_bufs(काष्ठा smc_link_group *lgr, bool is_rmb)
अणु
	काष्ठा smc_buf_desc *buf_desc, *bf_desc;
	काष्ठा list_head *buf_list;
	पूर्णांक i;

	क्रम (i = 0; i < SMC_RMBE_SIZES; i++) अणु
		अगर (is_rmb)
			buf_list = &lgr->rmbs[i];
		अन्यथा
			buf_list = &lgr->sndbufs[i];
		list_क्रम_each_entry_safe(buf_desc, bf_desc, buf_list,
					 list) अणु
			list_del(&buf_desc->list);
			smc_buf_मुक्त(lgr, is_rmb, buf_desc);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम smc_lgr_मुक्त_bufs(काष्ठा smc_link_group *lgr)
अणु
	/* मुक्त send buffers */
	__smc_lgr_मुक्त_bufs(lgr, false);
	/* मुक्त rmbs */
	__smc_lgr_मुक्त_bufs(lgr, true);
पूर्ण

/* हटाओ a link group */
अटल व्योम smc_lgr_मुक्त(काष्ठा smc_link_group *lgr)
अणु
	पूर्णांक i;

	अगर (!lgr->is_smcd) अणु
		mutex_lock(&lgr->llc_conf_mutex);
		क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++) अणु
			अगर (lgr->lnk[i].state != SMC_LNK_UNUSED)
				smcr_link_clear(&lgr->lnk[i], false);
		पूर्ण
		mutex_unlock(&lgr->llc_conf_mutex);
		smc_llc_lgr_clear(lgr);
	पूर्ण

	smc_lgr_मुक्त_bufs(lgr);
	destroy_workqueue(lgr->tx_wq);
	अगर (lgr->is_smcd) अणु
		smc_ism_put_vlan(lgr->smcd, lgr->vlan_id);
		put_device(&lgr->smcd->dev);
		अगर (!atomic_dec_वापस(&lgr->smcd->lgr_cnt))
			wake_up(&lgr->smcd->lgrs_deleted);
	पूर्ण अन्यथा अणु
		अगर (!atomic_dec_वापस(&lgr_cnt))
			wake_up(&lgrs_deleted);
	पूर्ण
	kमुक्त(lgr);
पूर्ण

अटल व्योम smcd_unरेजिस्टर_all_dmbs(काष्ठा smc_link_group *lgr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SMC_RMBE_SIZES; i++) अणु
		काष्ठा smc_buf_desc *buf_desc;

		list_क्रम_each_entry(buf_desc, &lgr->rmbs[i], list) अणु
			buf_desc->len += माप(काष्ठा smcd_cdc_msg);
			smc_ism_unरेजिस्टर_dmb(lgr->smcd, buf_desc);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम smc_sk_wake_ups(काष्ठा smc_sock *smc)
अणु
	smc->sk.sk_ग_लिखो_space(&smc->sk);
	smc->sk.sk_data_पढ़ोy(&smc->sk);
	smc->sk.sk_state_change(&smc->sk);
पूर्ण

/* समाप्त a connection */
अटल व्योम smc_conn_समाप्त(काष्ठा smc_connection *conn, bool soft)
अणु
	काष्ठा smc_sock *smc = container_of(conn, काष्ठा smc_sock, conn);

	अगर (conn->lgr->is_smcd && conn->lgr->peer_shutकरोwn)
		conn->local_tx_ctrl.conn_state_flags.peer_conn_पात = 1;
	अन्यथा
		smc_बंद_पात(conn);
	conn->समाप्तed = 1;
	smc->sk.sk_err = ECONNABORTED;
	smc_sk_wake_ups(smc);
	अगर (conn->lgr->is_smcd) अणु
		smc_ism_unset_conn(conn);
		अगर (soft)
			tasklet_समाप्त(&conn->rx_tsklet);
		अन्यथा
			tasklet_unlock_रुको(&conn->rx_tsklet);
	पूर्ण अन्यथा अणु
		smc_cdc_tx_dismiss_slots(conn);
	पूर्ण
	smc_lgr_unरेजिस्टर_conn(conn);
	smc_बंद_active_पात(smc);
पूर्ण

अटल व्योम smc_lgr_cleanup(काष्ठा smc_link_group *lgr)
अणु
	अगर (lgr->is_smcd) अणु
		smc_ism_संकेत_shutकरोwn(lgr);
		smcd_unरेजिस्टर_all_dmbs(lgr);
	पूर्ण अन्यथा अणु
		u32 rsn = lgr->llc_termination_rsn;

		अगर (!rsn)
			rsn = SMC_LLC_DEL_PROG_INIT_TERM;
		smc_llc_send_link_delete_all(lgr, false, rsn);
		smcr_lgr_link_deactivate_all(lgr);
	पूर्ण
पूर्ण

/* terminate link group
 * @soft: true अगर link group shutकरोwn can take its समय
 *	  false अगर immediate link group shutकरोwn is required
 */
अटल व्योम __smc_lgr_terminate(काष्ठा smc_link_group *lgr, bool soft)
अणु
	काष्ठा smc_connection *conn;
	काष्ठा smc_sock *smc;
	काष्ठा rb_node *node;

	अगर (lgr->terminating)
		वापस;	/* lgr alपढ़ोy terminating */
	/* cancel मुक्त_work sync, will terminate when lgr->मुक्तing is set */
	cancel_delayed_work_sync(&lgr->मुक्त_work);
	lgr->terminating = 1;

	/* समाप्त reमुख्यing link group connections */
	पढ़ो_lock_bh(&lgr->conns_lock);
	node = rb_first(&lgr->conns_all);
	जबतक (node) अणु
		पढ़ो_unlock_bh(&lgr->conns_lock);
		conn = rb_entry(node, काष्ठा smc_connection, alert_node);
		smc = container_of(conn, काष्ठा smc_sock, conn);
		sock_hold(&smc->sk); /* sock_put below */
		lock_sock(&smc->sk);
		smc_conn_समाप्त(conn, soft);
		release_sock(&smc->sk);
		sock_put(&smc->sk); /* sock_hold above */
		पढ़ो_lock_bh(&lgr->conns_lock);
		node = rb_first(&lgr->conns_all);
	पूर्ण
	पढ़ो_unlock_bh(&lgr->conns_lock);
	smc_lgr_cleanup(lgr);
	smc_lgr_मुक्त(lgr);
पूर्ण

/* unlink link group and schedule termination */
व्योम smc_lgr_terminate_sched(काष्ठा smc_link_group *lgr)
अणु
	spinlock_t *lgr_lock;

	smc_lgr_list_head(lgr, &lgr_lock);
	spin_lock_bh(lgr_lock);
	अगर (list_empty(&lgr->list) || lgr->terminating || lgr->मुक्तing) अणु
		spin_unlock_bh(lgr_lock);
		वापस;	/* lgr alपढ़ोy terminating */
	पूर्ण
	list_del_init(&lgr->list);
	lgr->मुक्तing = 1;
	spin_unlock_bh(lgr_lock);
	schedule_work(&lgr->terminate_work);
पूर्ण

/* Called when peer lgr shutकरोwn (regularly or abnormally) is received */
व्योम smc_smcd_terminate(काष्ठा smcd_dev *dev, u64 peer_gid, अचिन्हित लघु vlan)
अणु
	काष्ठा smc_link_group *lgr, *l;
	LIST_HEAD(lgr_मुक्त_list);

	/* run common cleanup function and build मुक्त list */
	spin_lock_bh(&dev->lgr_lock);
	list_क्रम_each_entry_safe(lgr, l, &dev->lgr_list, list) अणु
		अगर ((!peer_gid || lgr->peer_gid == peer_gid) &&
		    (vlan == VLAN_VID_MASK || lgr->vlan_id == vlan)) अणु
			अगर (peer_gid) /* peer triggered termination */
				lgr->peer_shutकरोwn = 1;
			list_move(&lgr->list, &lgr_मुक्त_list);
			lgr->मुक्तing = 1;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&dev->lgr_lock);

	/* cancel the regular मुक्त workers and actually मुक्त lgrs */
	list_क्रम_each_entry_safe(lgr, l, &lgr_मुक्त_list, list) अणु
		list_del_init(&lgr->list);
		schedule_work(&lgr->terminate_work);
	पूर्ण
पूर्ण

/* Called when an SMCD device is हटाओd or the smc module is unloaded */
व्योम smc_smcd_terminate_all(काष्ठा smcd_dev *smcd)
अणु
	काष्ठा smc_link_group *lgr, *lg;
	LIST_HEAD(lgr_मुक्त_list);

	spin_lock_bh(&smcd->lgr_lock);
	list_splice_init(&smcd->lgr_list, &lgr_मुक्त_list);
	list_क्रम_each_entry(lgr, &lgr_मुक्त_list, list)
		lgr->मुक्तing = 1;
	spin_unlock_bh(&smcd->lgr_lock);

	list_क्रम_each_entry_safe(lgr, lg, &lgr_मुक्त_list, list) अणु
		list_del_init(&lgr->list);
		__smc_lgr_terminate(lgr, false);
	पूर्ण

	अगर (atomic_पढ़ो(&smcd->lgr_cnt))
		रुको_event(smcd->lgrs_deleted, !atomic_पढ़ो(&smcd->lgr_cnt));
पूर्ण

/* Called when an SMCR device is हटाओd or the smc module is unloaded.
 * If smcibdev is given, all SMCR link groups using this device are terminated.
 * If smcibdev is शून्य, all SMCR link groups are terminated.
 */
व्योम smc_smcr_terminate_all(काष्ठा smc_ib_device *smcibdev)
अणु
	काष्ठा smc_link_group *lgr, *lg;
	LIST_HEAD(lgr_मुक्त_list);
	पूर्णांक i;

	spin_lock_bh(&smc_lgr_list.lock);
	अगर (!smcibdev) अणु
		list_splice_init(&smc_lgr_list.list, &lgr_मुक्त_list);
		list_क्रम_each_entry(lgr, &lgr_मुक्त_list, list)
			lgr->मुक्तing = 1;
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry_safe(lgr, lg, &smc_lgr_list.list, list) अणु
			क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++) अणु
				अगर (lgr->lnk[i].smcibdev == smcibdev)
					smcr_link_करोwn_cond_sched(&lgr->lnk[i]);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_bh(&smc_lgr_list.lock);

	list_क्रम_each_entry_safe(lgr, lg, &lgr_मुक्त_list, list) अणु
		list_del_init(&lgr->list);
		smc_llc_set_termination_rsn(lgr, SMC_LLC_DEL_OP_INIT_TERM);
		__smc_lgr_terminate(lgr, false);
	पूर्ण

	अगर (smcibdev) अणु
		अगर (atomic_पढ़ो(&smcibdev->lnk_cnt))
			रुको_event(smcibdev->lnks_deleted,
				   !atomic_पढ़ो(&smcibdev->lnk_cnt));
	पूर्ण अन्यथा अणु
		अगर (atomic_पढ़ो(&lgr_cnt))
			रुको_event(lgrs_deleted, !atomic_पढ़ो(&lgr_cnt));
	पूर्ण
पूर्ण

/* set new lgr type and clear all asymmetric link tagging */
व्योम smcr_lgr_set_type(काष्ठा smc_link_group *lgr, क्रमागत smc_lgr_type new_type)
अणु
	अक्षर *lgr_type = "";
	पूर्णांक i;

	क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++)
		अगर (smc_link_usable(&lgr->lnk[i]))
			lgr->lnk[i].link_is_asym = false;
	अगर (lgr->type == new_type)
		वापस;
	lgr->type = new_type;

	चयन (lgr->type) अणु
	हाल SMC_LGR_NONE:
		lgr_type = "NONE";
		अवरोध;
	हाल SMC_LGR_SINGLE:
		lgr_type = "SINGLE";
		अवरोध;
	हाल SMC_LGR_SYMMETRIC:
		lgr_type = "SYMMETRIC";
		अवरोध;
	हाल SMC_LGR_ASYMMETRIC_PEER:
		lgr_type = "ASYMMETRIC_PEER";
		अवरोध;
	हाल SMC_LGR_ASYMMETRIC_LOCAL:
		lgr_type = "ASYMMETRIC_LOCAL";
		अवरोध;
	पूर्ण
	pr_warn_ratelimited("smc: SMC-R lg %*phN state changed: "
			    "%s, pnetid %.16s\n", SMC_LGR_ID_SIZE, &lgr->id,
			    lgr_type, lgr->pnet_id);
पूर्ण

/* set new lgr type and tag a link as asymmetric */
व्योम smcr_lgr_set_type_asym(काष्ठा smc_link_group *lgr,
			    क्रमागत smc_lgr_type new_type, पूर्णांक asym_lnk_idx)
अणु
	smcr_lgr_set_type(lgr, new_type);
	lgr->lnk[asym_lnk_idx].link_is_asym = true;
पूर्ण

/* पात connection, पात_work scheduled from tasklet context */
अटल व्योम smc_conn_पात_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smc_connection *conn = container_of(work,
						   काष्ठा smc_connection,
						   पात_work);
	काष्ठा smc_sock *smc = container_of(conn, काष्ठा smc_sock, conn);

	smc_conn_समाप्त(conn, true);
	sock_put(&smc->sk); /* sock_hold करोne by schedulers of पात_work */
पूर्ण

व्योम smcr_port_add(काष्ठा smc_ib_device *smcibdev, u8 ibport)
अणु
	काष्ठा smc_link_group *lgr, *n;

	list_क्रम_each_entry_safe(lgr, n, &smc_lgr_list.list, list) अणु
		काष्ठा smc_link *link;

		अगर (म_भेदन(smcibdev->pnetid[ibport - 1], lgr->pnet_id,
			    SMC_MAX_PNETID_LEN) ||
		    lgr->type == SMC_LGR_SYMMETRIC ||
		    lgr->type == SMC_LGR_ASYMMETRIC_PEER)
			जारी;

		/* trigger local add link processing */
		link = smc_llc_usable_link(lgr);
		अगर (link)
			smc_llc_add_link_local(link);
	पूर्ण
पूर्ण

/* link is करोwn - चयन connections to alternate link,
 * must be called under lgr->llc_conf_mutex lock
 */
अटल व्योम smcr_link_करोwn(काष्ठा smc_link *lnk)
अणु
	काष्ठा smc_link_group *lgr = lnk->lgr;
	काष्ठा smc_link *to_lnk;
	पूर्णांक del_link_id;

	अगर (!lgr || lnk->state == SMC_LNK_UNUSED || list_empty(&lgr->list))
		वापस;

	smc_ib_modअगरy_qp_reset(lnk);
	to_lnk = smc_चयन_conns(lgr, lnk, true);
	अगर (!to_lnk) अणु /* no backup link available */
		smcr_link_clear(lnk, true);
		वापस;
	पूर्ण
	smcr_lgr_set_type(lgr, SMC_LGR_SINGLE);
	del_link_id = lnk->link_id;

	अगर (lgr->role == SMC_SERV) अणु
		/* trigger local delete link processing */
		smc_llc_srv_delete_link_local(to_lnk, del_link_id);
	पूर्ण अन्यथा अणु
		अगर (lgr->llc_flow_lcl.type != SMC_LLC_FLOW_NONE) अणु
			/* another llc task is ongoing */
			mutex_unlock(&lgr->llc_conf_mutex);
			रुको_event_समयout(lgr->llc_flow_रुकोer,
				(list_empty(&lgr->list) ||
				 lgr->llc_flow_lcl.type == SMC_LLC_FLOW_NONE),
				SMC_LLC_WAIT_TIME);
			mutex_lock(&lgr->llc_conf_mutex);
		पूर्ण
		अगर (!list_empty(&lgr->list)) अणु
			smc_llc_send_delete_link(to_lnk, del_link_id,
						 SMC_LLC_REQ, true,
						 SMC_LLC_DEL_LOST_PATH);
			smcr_link_clear(lnk, true);
		पूर्ण
		wake_up(&lgr->llc_flow_रुकोer);	/* wake up next रुकोer */
	पूर्ण
पूर्ण

/* must be called under lgr->llc_conf_mutex lock */
व्योम smcr_link_करोwn_cond(काष्ठा smc_link *lnk)
अणु
	अगर (smc_link_करोwning(&lnk->state))
		smcr_link_करोwn(lnk);
पूर्ण

/* will get the lgr->llc_conf_mutex lock */
व्योम smcr_link_करोwn_cond_sched(काष्ठा smc_link *lnk)
अणु
	अगर (smc_link_करोwning(&lnk->state))
		schedule_work(&lnk->link_करोwn_wrk);
पूर्ण

व्योम smcr_port_err(काष्ठा smc_ib_device *smcibdev, u8 ibport)
अणु
	काष्ठा smc_link_group *lgr, *n;
	पूर्णांक i;

	list_क्रम_each_entry_safe(lgr, n, &smc_lgr_list.list, list) अणु
		अगर (म_भेदन(smcibdev->pnetid[ibport - 1], lgr->pnet_id,
			    SMC_MAX_PNETID_LEN))
			जारी; /* lgr is not affected */
		अगर (list_empty(&lgr->list))
			जारी;
		क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++) अणु
			काष्ठा smc_link *lnk = &lgr->lnk[i];

			अगर (smc_link_usable(lnk) &&
			    lnk->smcibdev == smcibdev && lnk->ibport == ibport)
				smcr_link_करोwn_cond_sched(lnk);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम smc_link_करोwn_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smc_link *link = container_of(work, काष्ठा smc_link,
					     link_करोwn_wrk);
	काष्ठा smc_link_group *lgr = link->lgr;

	अगर (list_empty(&lgr->list))
		वापस;
	wake_up_all(&lgr->llc_msg_रुकोer);
	mutex_lock(&lgr->llc_conf_mutex);
	smcr_link_करोwn(link);
	mutex_unlock(&lgr->llc_conf_mutex);
पूर्ण

/* Determine vlan of पूर्णांकernal TCP socket.
 * @vlan_id: address to store the determined vlan id पूर्णांकo
 */
पूर्णांक smc_vlan_by_tcpsk(काष्ठा socket *clcsock, काष्ठा smc_init_info *ini)
अणु
	काष्ठा dst_entry *dst = sk_dst_get(clcsock->sk);
	काष्ठा net_device *ndev;
	पूर्णांक i, nest_lvl, rc = 0;

	ini->vlan_id = 0;
	अगर (!dst) अणु
		rc = -ENOTCONN;
		जाओ out;
	पूर्ण
	अगर (!dst->dev) अणु
		rc = -ENODEV;
		जाओ out_rel;
	पूर्ण

	ndev = dst->dev;
	अगर (is_vlan_dev(ndev)) अणु
		ini->vlan_id = vlan_dev_vlan_id(ndev);
		जाओ out_rel;
	पूर्ण

	rtnl_lock();
	nest_lvl = ndev->lower_level;
	क्रम (i = 0; i < nest_lvl; i++) अणु
		काष्ठा list_head *lower = &ndev->adj_list.lower;

		अगर (list_empty(lower))
			अवरोध;
		lower = lower->next;
		ndev = (काष्ठा net_device *)netdev_lower_get_next(ndev, &lower);
		अगर (is_vlan_dev(ndev)) अणु
			ini->vlan_id = vlan_dev_vlan_id(ndev);
			अवरोध;
		पूर्ण
	पूर्ण
	rtnl_unlock();

out_rel:
	dst_release(dst);
out:
	वापस rc;
पूर्ण

अटल bool smcr_lgr_match(काष्ठा smc_link_group *lgr,
			   काष्ठा smc_clc_msg_local *lcl,
			   क्रमागत smc_lgr_role role, u32 clcqpn)
अणु
	पूर्णांक i;

	अगर (स_भेद(lgr->peer_प्रणालीid, lcl->id_क्रम_peer, SMC_SYSTEMID_LEN) ||
	    lgr->role != role)
		वापस false;

	क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++) अणु
		अगर (!smc_link_active(&lgr->lnk[i]))
			जारी;
		अगर ((lgr->role == SMC_SERV || lgr->lnk[i].peer_qpn == clcqpn) &&
		    !स_भेद(lgr->lnk[i].peer_gid, &lcl->gid, SMC_GID_SIZE) &&
		    !स_भेद(lgr->lnk[i].peer_mac, lcl->mac, माप(lcl->mac)))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool smcd_lgr_match(काष्ठा smc_link_group *lgr,
			   काष्ठा smcd_dev *smcismdev, u64 peer_gid)
अणु
	वापस lgr->peer_gid == peer_gid && lgr->smcd == smcismdev;
पूर्ण

/* create a new SMC connection (and a new link group अगर necessary) */
पूर्णांक smc_conn_create(काष्ठा smc_sock *smc, काष्ठा smc_init_info *ini)
अणु
	काष्ठा smc_connection *conn = &smc->conn;
	काष्ठा list_head *lgr_list;
	काष्ठा smc_link_group *lgr;
	क्रमागत smc_lgr_role role;
	spinlock_t *lgr_lock;
	पूर्णांक rc = 0;

	lgr_list = ini->is_smcd ? &ini->ism_dev[ini->ism_selected]->lgr_list :
				  &smc_lgr_list.list;
	lgr_lock = ini->is_smcd ? &ini->ism_dev[ini->ism_selected]->lgr_lock :
				  &smc_lgr_list.lock;
	ini->first_contact_local = 1;
	role = smc->listen_smc ? SMC_SERV : SMC_CLNT;
	अगर (role == SMC_CLNT && ini->first_contact_peer)
		/* create new link group as well */
		जाओ create;

	/* determine अगर an existing link group can be reused */
	spin_lock_bh(lgr_lock);
	list_क्रम_each_entry(lgr, lgr_list, list) अणु
		ग_लिखो_lock_bh(&lgr->conns_lock);
		अगर ((ini->is_smcd ?
		     smcd_lgr_match(lgr, ini->ism_dev[ini->ism_selected],
				    ini->ism_peer_gid[ini->ism_selected]) :
		     smcr_lgr_match(lgr, ini->ib_lcl, role, ini->ib_clcqpn)) &&
		    !lgr->sync_err &&
		    (ini->smcd_version == SMC_V2 ||
		     lgr->vlan_id == ini->vlan_id) &&
		    (role == SMC_CLNT || ini->is_smcd ||
		     lgr->conns_num < SMC_RMBS_PER_LGR_MAX)) अणु
			/* link group found */
			ini->first_contact_local = 0;
			conn->lgr = lgr;
			rc = smc_lgr_रेजिस्टर_conn(conn, false);
			ग_लिखो_unlock_bh(&lgr->conns_lock);
			अगर (!rc && delayed_work_pending(&lgr->मुक्त_work))
				cancel_delayed_work(&lgr->मुक्त_work);
			अवरोध;
		पूर्ण
		ग_लिखो_unlock_bh(&lgr->conns_lock);
	पूर्ण
	spin_unlock_bh(lgr_lock);
	अगर (rc)
		वापस rc;

	अगर (role == SMC_CLNT && !ini->first_contact_peer &&
	    ini->first_contact_local) अणु
		/* Server reuses a link group, but Client wants to start
		 * a new one
		 * send out_of_sync decline, reason synchr. error
		 */
		वापस SMC_CLC_DECL_SYNCERR;
	पूर्ण

create:
	अगर (ini->first_contact_local) अणु
		rc = smc_lgr_create(smc, ini);
		अगर (rc)
			जाओ out;
		lgr = conn->lgr;
		ग_लिखो_lock_bh(&lgr->conns_lock);
		rc = smc_lgr_रेजिस्टर_conn(conn, true);
		ग_लिखो_unlock_bh(&lgr->conns_lock);
		अगर (rc)
			जाओ out;
	पूर्ण
	conn->local_tx_ctrl.common.type = SMC_CDC_MSG_TYPE;
	conn->local_tx_ctrl.len = SMC_WR_TX_SIZE;
	conn->urg_state = SMC_URG_READ;
	INIT_WORK(&smc->conn.पात_work, smc_conn_पात_work);
	अगर (ini->is_smcd) अणु
		conn->rx_off = माप(काष्ठा smcd_cdc_msg);
		smcd_cdc_rx_init(conn); /* init tasklet क्रम this conn */
	पूर्ण अन्यथा अणु
		conn->rx_off = 0;
	पूर्ण
#अगर_अघोषित KERNEL_HAS_ATOMIC64
	spin_lock_init(&conn->acurs_lock);
#पूर्ण_अगर

out:
	वापस rc;
पूर्ण

/* convert the RMB size पूर्णांकo the compressed notation - minimum 16K.
 * In contrast to plain ilog2, this rounds towards the next घातer of 2,
 * so the socket application माला_लो at least its desired sndbuf / rcvbuf size.
 */
अटल u8 smc_compress_bufsize(पूर्णांक size)
अणु
	u8 compressed;

	अगर (size <= SMC_BUF_MIN_SIZE)
		वापस 0;

	size = (size - 1) >> 14;
	compressed = ilog2(size) + 1;
	अगर (compressed >= SMC_RMBE_SIZES)
		compressed = SMC_RMBE_SIZES - 1;
	वापस compressed;
पूर्ण

/* convert the RMB size from compressed notation पूर्णांकo पूर्णांकeger */
पूर्णांक smc_uncompress_bufsize(u8 compressed)
अणु
	u32 size;

	size = 0x00000001 << (((पूर्णांक)compressed) + 14);
	वापस (पूर्णांक)size;
पूर्ण

/* try to reuse a sndbuf or rmb description slot क्रम a certain
 * buffer size; अगर not available, वापस शून्य
 */
अटल काष्ठा smc_buf_desc *smc_buf_get_slot(पूर्णांक compressed_bufsize,
					     काष्ठा mutex *lock,
					     काष्ठा list_head *buf_list)
अणु
	काष्ठा smc_buf_desc *buf_slot;

	mutex_lock(lock);
	list_क्रम_each_entry(buf_slot, buf_list, list) अणु
		अगर (cmpxchg(&buf_slot->used, 0, 1) == 0) अणु
			mutex_unlock(lock);
			वापस buf_slot;
		पूर्ण
	पूर्ण
	mutex_unlock(lock);
	वापस शून्य;
पूर्ण

/* one of the conditions क्रम announcing a receiver's current winकरोw size is
 * that it "results in a minimum increase in the winकरोw size of 10% of the
 * receive buffer space" [RFC7609]
 */
अटल अंतरभूत पूर्णांक smc_rmb_wnd_update_limit(पूर्णांक rmbe_size)
अणु
	वापस min_t(पूर्णांक, rmbe_size / 10, SOCK_MIN_SNDBUF / 2);
पूर्ण

/* map an rmb buf to a link */
अटल पूर्णांक smcr_buf_map_link(काष्ठा smc_buf_desc *buf_desc, bool is_rmb,
			     काष्ठा smc_link *lnk)
अणु
	पूर्णांक rc;

	अगर (buf_desc->is_map_ib[lnk->link_idx])
		वापस 0;

	rc = sg_alloc_table(&buf_desc->sgt[lnk->link_idx], 1, GFP_KERNEL);
	अगर (rc)
		वापस rc;
	sg_set_buf(buf_desc->sgt[lnk->link_idx].sgl,
		   buf_desc->cpu_addr, buf_desc->len);

	/* map sg table to DMA address */
	rc = smc_ib_buf_map_sg(lnk, buf_desc,
			       is_rmb ? DMA_FROM_DEVICE : DMA_TO_DEVICE);
	/* SMC protocol depends on mapping to one DMA address only */
	अगर (rc != 1) अणु
		rc = -EAGAIN;
		जाओ मुक्त_table;
	पूर्ण

	/* create a new memory region क्रम the RMB */
	अगर (is_rmb) अणु
		rc = smc_ib_get_memory_region(lnk->roce_pd,
					      IB_ACCESS_REMOTE_WRITE |
					      IB_ACCESS_LOCAL_WRITE,
					      buf_desc, lnk->link_idx);
		अगर (rc)
			जाओ buf_unmap;
		smc_ib_sync_sg_क्रम_device(lnk, buf_desc, DMA_FROM_DEVICE);
	पूर्ण
	buf_desc->is_map_ib[lnk->link_idx] = true;
	वापस 0;

buf_unmap:
	smc_ib_buf_unmap_sg(lnk, buf_desc,
			    is_rmb ? DMA_FROM_DEVICE : DMA_TO_DEVICE);
मुक्त_table:
	sg_मुक्त_table(&buf_desc->sgt[lnk->link_idx]);
	वापस rc;
पूर्ण

/* रेजिस्टर a new rmb on IB device,
 * must be called under lgr->llc_conf_mutex lock
 */
पूर्णांक smcr_link_reg_rmb(काष्ठा smc_link *link, काष्ठा smc_buf_desc *rmb_desc)
अणु
	अगर (list_empty(&link->lgr->list))
		वापस -ENOLINK;
	अगर (!rmb_desc->is_reg_mr[link->link_idx]) अणु
		/* रेजिस्टर memory region क्रम new rmb */
		अगर (smc_wr_reg_send(link, rmb_desc->mr_rx[link->link_idx])) अणु
			rmb_desc->is_reg_err = true;
			वापस -EFAULT;
		पूर्ण
		rmb_desc->is_reg_mr[link->link_idx] = true;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक _smcr_buf_map_lgr(काष्ठा smc_link *lnk, काष्ठा mutex *lock,
			     काष्ठा list_head *lst, bool is_rmb)
अणु
	काष्ठा smc_buf_desc *buf_desc, *bf;
	पूर्णांक rc = 0;

	mutex_lock(lock);
	list_क्रम_each_entry_safe(buf_desc, bf, lst, list) अणु
		अगर (!buf_desc->used)
			जारी;
		rc = smcr_buf_map_link(buf_desc, is_rmb, lnk);
		अगर (rc)
			जाओ out;
	पूर्ण
out:
	mutex_unlock(lock);
	वापस rc;
पूर्ण

/* map all used buffers of lgr क्रम a new link */
पूर्णांक smcr_buf_map_lgr(काष्ठा smc_link *lnk)
अणु
	काष्ठा smc_link_group *lgr = lnk->lgr;
	पूर्णांक i, rc = 0;

	क्रम (i = 0; i < SMC_RMBE_SIZES; i++) अणु
		rc = _smcr_buf_map_lgr(lnk, &lgr->rmbs_lock,
				       &lgr->rmbs[i], true);
		अगर (rc)
			वापस rc;
		rc = _smcr_buf_map_lgr(lnk, &lgr->sndbufs_lock,
				       &lgr->sndbufs[i], false);
		अगर (rc)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

/* रेजिस्टर all used buffers of lgr क्रम a new link,
 * must be called under lgr->llc_conf_mutex lock
 */
पूर्णांक smcr_buf_reg_lgr(काष्ठा smc_link *lnk)
अणु
	काष्ठा smc_link_group *lgr = lnk->lgr;
	काष्ठा smc_buf_desc *buf_desc, *bf;
	पूर्णांक i, rc = 0;

	mutex_lock(&lgr->rmbs_lock);
	क्रम (i = 0; i < SMC_RMBE_SIZES; i++) अणु
		list_क्रम_each_entry_safe(buf_desc, bf, &lgr->rmbs[i], list) अणु
			अगर (!buf_desc->used)
				जारी;
			rc = smcr_link_reg_rmb(lnk, buf_desc);
			अगर (rc)
				जाओ out;
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&lgr->rmbs_lock);
	वापस rc;
पूर्ण

अटल काष्ठा smc_buf_desc *smcr_new_buf_create(काष्ठा smc_link_group *lgr,
						bool is_rmb, पूर्णांक bufsize)
अणु
	काष्ठा smc_buf_desc *buf_desc;

	/* try to alloc a new buffer */
	buf_desc = kzalloc(माप(*buf_desc), GFP_KERNEL);
	अगर (!buf_desc)
		वापस ERR_PTR(-ENOMEM);

	buf_desc->order = get_order(bufsize);
	buf_desc->pages = alloc_pages(GFP_KERNEL | __GFP_NOWARN |
				      __GFP_NOMEMALLOC | __GFP_COMP |
				      __GFP_NORETRY | __GFP_ZERO,
				      buf_desc->order);
	अगर (!buf_desc->pages) अणु
		kमुक्त(buf_desc);
		वापस ERR_PTR(-EAGAIN);
	पूर्ण
	buf_desc->cpu_addr = (व्योम *)page_address(buf_desc->pages);
	buf_desc->len = bufsize;
	वापस buf_desc;
पूर्ण

/* map buf_desc on all usable links,
 * unused buffers stay mapped as दीर्घ as the link is up
 */
अटल पूर्णांक smcr_buf_map_usable_links(काष्ठा smc_link_group *lgr,
				     काष्ठा smc_buf_desc *buf_desc, bool is_rmb)
अणु
	पूर्णांक i, rc = 0;

	/* protect against parallel link reconfiguration */
	mutex_lock(&lgr->llc_conf_mutex);
	क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++) अणु
		काष्ठा smc_link *lnk = &lgr->lnk[i];

		अगर (!smc_link_usable(lnk))
			जारी;
		अगर (smcr_buf_map_link(buf_desc, is_rmb, lnk)) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&lgr->llc_conf_mutex);
	वापस rc;
पूर्ण

#घोषणा SMCD_DMBE_SIZES		6 /* 0 -> 16KB, 1 -> 32KB, .. 6 -> 1MB */

अटल काष्ठा smc_buf_desc *smcd_new_buf_create(काष्ठा smc_link_group *lgr,
						bool is_dmb, पूर्णांक bufsize)
अणु
	काष्ठा smc_buf_desc *buf_desc;
	पूर्णांक rc;

	अगर (smc_compress_bufsize(bufsize) > SMCD_DMBE_SIZES)
		वापस ERR_PTR(-EAGAIN);

	/* try to alloc a new DMB */
	buf_desc = kzalloc(माप(*buf_desc), GFP_KERNEL);
	अगर (!buf_desc)
		वापस ERR_PTR(-ENOMEM);
	अगर (is_dmb) अणु
		rc = smc_ism_रेजिस्टर_dmb(lgr, bufsize, buf_desc);
		अगर (rc) अणु
			kमुक्त(buf_desc);
			अगर (rc == -ENOMEM)
				वापस ERR_PTR(-EAGAIN);
			अगर (rc == -ENOSPC)
				वापस ERR_PTR(-ENOSPC);
			वापस ERR_PTR(-EIO);
		पूर्ण
		buf_desc->pages = virt_to_page(buf_desc->cpu_addr);
		/* CDC header stored in buf. So, pretend it was smaller */
		buf_desc->len = bufsize - माप(काष्ठा smcd_cdc_msg);
	पूर्ण अन्यथा अणु
		buf_desc->cpu_addr = kzalloc(bufsize, GFP_KERNEL |
					     __GFP_NOWARN | __GFP_NORETRY |
					     __GFP_NOMEMALLOC);
		अगर (!buf_desc->cpu_addr) अणु
			kमुक्त(buf_desc);
			वापस ERR_PTR(-EAGAIN);
		पूर्ण
		buf_desc->len = bufsize;
	पूर्ण
	वापस buf_desc;
पूर्ण

अटल पूर्णांक __smc_buf_create(काष्ठा smc_sock *smc, bool is_smcd, bool is_rmb)
अणु
	काष्ठा smc_buf_desc *buf_desc = ERR_PTR(-ENOMEM);
	काष्ठा smc_connection *conn = &smc->conn;
	काष्ठा smc_link_group *lgr = conn->lgr;
	काष्ठा list_head *buf_list;
	पूर्णांक bufsize, bufsize_लघु;
	काष्ठा mutex *lock;	/* lock buffer list */
	पूर्णांक sk_buf_size;

	अगर (is_rmb)
		/* use socket recv buffer size (w/o overhead) as start value */
		sk_buf_size = smc->sk.sk_rcvbuf / 2;
	अन्यथा
		/* use socket send buffer size (w/o overhead) as start value */
		sk_buf_size = smc->sk.sk_sndbuf / 2;

	क्रम (bufsize_लघु = smc_compress_bufsize(sk_buf_size);
	     bufsize_लघु >= 0; bufsize_लघु--) अणु

		अगर (is_rmb) अणु
			lock = &lgr->rmbs_lock;
			buf_list = &lgr->rmbs[bufsize_लघु];
		पूर्ण अन्यथा अणु
			lock = &lgr->sndbufs_lock;
			buf_list = &lgr->sndbufs[bufsize_लघु];
		पूर्ण
		bufsize = smc_uncompress_bufsize(bufsize_लघु);
		अगर ((1 << get_order(bufsize)) > SG_MAX_SINGLE_ALLOC)
			जारी;

		/* check क्रम reusable slot in the link group */
		buf_desc = smc_buf_get_slot(bufsize_लघु, lock, buf_list);
		अगर (buf_desc) अणु
			स_रखो(buf_desc->cpu_addr, 0, bufsize);
			अवरोध; /* found reusable slot */
		पूर्ण

		अगर (is_smcd)
			buf_desc = smcd_new_buf_create(lgr, is_rmb, bufsize);
		अन्यथा
			buf_desc = smcr_new_buf_create(lgr, is_rmb, bufsize);

		अगर (PTR_ERR(buf_desc) == -ENOMEM)
			अवरोध;
		अगर (IS_ERR(buf_desc))
			जारी;

		buf_desc->used = 1;
		mutex_lock(lock);
		list_add(&buf_desc->list, buf_list);
		mutex_unlock(lock);
		अवरोध; /* found */
	पूर्ण

	अगर (IS_ERR(buf_desc))
		वापस PTR_ERR(buf_desc);

	अगर (!is_smcd) अणु
		अगर (smcr_buf_map_usable_links(lgr, buf_desc, is_rmb)) अणु
			smcr_buf_unuse(buf_desc, lgr);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (is_rmb) अणु
		conn->rmb_desc = buf_desc;
		conn->rmbe_size_लघु = bufsize_लघु;
		smc->sk.sk_rcvbuf = bufsize * 2;
		atomic_set(&conn->bytes_to_rcv, 0);
		conn->rmbe_update_limit =
			smc_rmb_wnd_update_limit(buf_desc->len);
		अगर (is_smcd)
			smc_ism_set_conn(conn); /* map RMB/smcd_dev to conn */
	पूर्ण अन्यथा अणु
		conn->sndbuf_desc = buf_desc;
		smc->sk.sk_sndbuf = bufsize * 2;
		atomic_set(&conn->sndbuf_space, bufsize);
	पूर्ण
	वापस 0;
पूर्ण

व्योम smc_sndbuf_sync_sg_क्रम_cpu(काष्ठा smc_connection *conn)
अणु
	अगर (!conn->lgr || conn->lgr->is_smcd || !smc_link_active(conn->lnk))
		वापस;
	smc_ib_sync_sg_क्रम_cpu(conn->lnk, conn->sndbuf_desc, DMA_TO_DEVICE);
पूर्ण

व्योम smc_sndbuf_sync_sg_क्रम_device(काष्ठा smc_connection *conn)
अणु
	अगर (!conn->lgr || conn->lgr->is_smcd || !smc_link_active(conn->lnk))
		वापस;
	smc_ib_sync_sg_क्रम_device(conn->lnk, conn->sndbuf_desc, DMA_TO_DEVICE);
पूर्ण

व्योम smc_rmb_sync_sg_क्रम_cpu(काष्ठा smc_connection *conn)
अणु
	पूर्णांक i;

	अगर (!conn->lgr || conn->lgr->is_smcd)
		वापस;
	क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++) अणु
		अगर (!smc_link_active(&conn->lgr->lnk[i]))
			जारी;
		smc_ib_sync_sg_क्रम_cpu(&conn->lgr->lnk[i], conn->rmb_desc,
				       DMA_FROM_DEVICE);
	पूर्ण
पूर्ण

व्योम smc_rmb_sync_sg_क्रम_device(काष्ठा smc_connection *conn)
अणु
	पूर्णांक i;

	अगर (!conn->lgr || conn->lgr->is_smcd)
		वापस;
	क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++) अणु
		अगर (!smc_link_active(&conn->lgr->lnk[i]))
			जारी;
		smc_ib_sync_sg_क्रम_device(&conn->lgr->lnk[i], conn->rmb_desc,
					  DMA_FROM_DEVICE);
	पूर्ण
पूर्ण

/* create the send and receive buffer क्रम an SMC socket;
 * receive buffers are called RMBs;
 * (even though the SMC protocol allows more than one RMB-element per RMB,
 * the Linux implementation uses just one RMB-element per RMB, i.e. uses an
 * extra RMB क्रम every connection in a link group
 */
पूर्णांक smc_buf_create(काष्ठा smc_sock *smc, bool is_smcd)
अणु
	पूर्णांक rc;

	/* create send buffer */
	rc = __smc_buf_create(smc, is_smcd, false);
	अगर (rc)
		वापस rc;
	/* create rmb */
	rc = __smc_buf_create(smc, is_smcd, true);
	अगर (rc) अणु
		mutex_lock(&smc->conn.lgr->sndbufs_lock);
		list_del(&smc->conn.sndbuf_desc->list);
		mutex_unlock(&smc->conn.lgr->sndbufs_lock);
		smc_buf_मुक्त(smc->conn.lgr, false, smc->conn.sndbuf_desc);
		smc->conn.sndbuf_desc = शून्य;
	पूर्ण
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक smc_rmb_reserve_rtoken_idx(काष्ठा smc_link_group *lgr)
अणु
	पूर्णांक i;

	क्रम_each_clear_bit(i, lgr->rtokens_used_mask, SMC_RMBS_PER_LGR_MAX) अणु
		अगर (!test_and_set_bit(i, lgr->rtokens_used_mask))
			वापस i;
	पूर्ण
	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक smc_rtoken_find_by_link(काष्ठा smc_link_group *lgr, पूर्णांक lnk_idx,
				   u32 rkey)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SMC_RMBS_PER_LGR_MAX; i++) अणु
		अगर (test_bit(i, lgr->rtokens_used_mask) &&
		    lgr->rtokens[i][lnk_idx].rkey == rkey)
			वापस i;
	पूर्ण
	वापस -ENOENT;
पूर्ण

/* set rtoken क्रम a new link to an existing rmb */
व्योम smc_rtoken_set(काष्ठा smc_link_group *lgr, पूर्णांक link_idx, पूर्णांक link_idx_new,
		    __be32 nw_rkey_known, __be64 nw_vaddr, __be32 nw_rkey)
अणु
	पूर्णांक rtok_idx;

	rtok_idx = smc_rtoken_find_by_link(lgr, link_idx, ntohl(nw_rkey_known));
	अगर (rtok_idx == -ENOENT)
		वापस;
	lgr->rtokens[rtok_idx][link_idx_new].rkey = ntohl(nw_rkey);
	lgr->rtokens[rtok_idx][link_idx_new].dma_addr = be64_to_cpu(nw_vaddr);
पूर्ण

/* set rtoken क्रम a new link whose link_id is given */
व्योम smc_rtoken_set2(काष्ठा smc_link_group *lgr, पूर्णांक rtok_idx, पूर्णांक link_id,
		     __be64 nw_vaddr, __be32 nw_rkey)
अणु
	u64 dma_addr = be64_to_cpu(nw_vaddr);
	u32 rkey = ntohl(nw_rkey);
	bool found = false;
	पूर्णांक link_idx;

	क्रम (link_idx = 0; link_idx < SMC_LINKS_PER_LGR_MAX; link_idx++) अणु
		अगर (lgr->lnk[link_idx].link_id == link_id) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found)
		वापस;
	lgr->rtokens[rtok_idx][link_idx].rkey = rkey;
	lgr->rtokens[rtok_idx][link_idx].dma_addr = dma_addr;
पूर्ण

/* add a new rtoken from peer */
पूर्णांक smc_rtoken_add(काष्ठा smc_link *lnk, __be64 nw_vaddr, __be32 nw_rkey)
अणु
	काष्ठा smc_link_group *lgr = smc_get_lgr(lnk);
	u64 dma_addr = be64_to_cpu(nw_vaddr);
	u32 rkey = ntohl(nw_rkey);
	पूर्णांक i;

	क्रम (i = 0; i < SMC_RMBS_PER_LGR_MAX; i++) अणु
		अगर (lgr->rtokens[i][lnk->link_idx].rkey == rkey &&
		    lgr->rtokens[i][lnk->link_idx].dma_addr == dma_addr &&
		    test_bit(i, lgr->rtokens_used_mask)) अणु
			/* alपढ़ोy in list */
			वापस i;
		पूर्ण
	पूर्ण
	i = smc_rmb_reserve_rtoken_idx(lgr);
	अगर (i < 0)
		वापस i;
	lgr->rtokens[i][lnk->link_idx].rkey = rkey;
	lgr->rtokens[i][lnk->link_idx].dma_addr = dma_addr;
	वापस i;
पूर्ण

/* delete an rtoken from all links */
पूर्णांक smc_rtoken_delete(काष्ठा smc_link *lnk, __be32 nw_rkey)
अणु
	काष्ठा smc_link_group *lgr = smc_get_lgr(lnk);
	u32 rkey = ntohl(nw_rkey);
	पूर्णांक i, j;

	क्रम (i = 0; i < SMC_RMBS_PER_LGR_MAX; i++) अणु
		अगर (lgr->rtokens[i][lnk->link_idx].rkey == rkey &&
		    test_bit(i, lgr->rtokens_used_mask)) अणु
			क्रम (j = 0; j < SMC_LINKS_PER_LGR_MAX; j++) अणु
				lgr->rtokens[i][j].rkey = 0;
				lgr->rtokens[i][j].dma_addr = 0;
			पूर्ण
			clear_bit(i, lgr->rtokens_used_mask);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENOENT;
पूर्ण

/* save rkey and dma_addr received from peer during clc handshake */
पूर्णांक smc_rmb_rtoken_handling(काष्ठा smc_connection *conn,
			    काष्ठा smc_link *lnk,
			    काष्ठा smc_clc_msg_accept_confirm *clc)
अणु
	conn->rtoken_idx = smc_rtoken_add(lnk, clc->r0.rmb_dma_addr,
					  clc->r0.rmb_rkey);
	अगर (conn->rtoken_idx < 0)
		वापस conn->rtoken_idx;
	वापस 0;
पूर्ण

अटल व्योम smc_core_going_away(व्योम)
अणु
	काष्ठा smc_ib_device *smcibdev;
	काष्ठा smcd_dev *smcd;

	mutex_lock(&smc_ib_devices.mutex);
	list_क्रम_each_entry(smcibdev, &smc_ib_devices.list, list) अणु
		पूर्णांक i;

		क्रम (i = 0; i < SMC_MAX_PORTS; i++)
			set_bit(i, smcibdev->ports_going_away);
	पूर्ण
	mutex_unlock(&smc_ib_devices.mutex);

	mutex_lock(&smcd_dev_list.mutex);
	list_क्रम_each_entry(smcd, &smcd_dev_list.list, list) अणु
		smcd->going_away = 1;
	पूर्ण
	mutex_unlock(&smcd_dev_list.mutex);
पूर्ण

/* Clean up all SMC link groups */
अटल व्योम smc_lgrs_shutकरोwn(व्योम)
अणु
	काष्ठा smcd_dev *smcd;

	smc_core_going_away();

	smc_smcr_terminate_all(शून्य);

	mutex_lock(&smcd_dev_list.mutex);
	list_क्रम_each_entry(smcd, &smcd_dev_list.list, list)
		smc_smcd_terminate_all(smcd);
	mutex_unlock(&smcd_dev_list.mutex);
पूर्ण

अटल पूर्णांक smc_core_reboot_event(काष्ठा notअगरier_block *this,
				 अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	smc_lgrs_shutकरोwn();
	smc_ib_unरेजिस्टर_client();
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block smc_reboot_notअगरier = अणु
	.notअगरier_call = smc_core_reboot_event,
पूर्ण;

पूर्णांक __init smc_core_init(व्योम)
अणु
	वापस रेजिस्टर_reboot_notअगरier(&smc_reboot_notअगरier);
पूर्ण

/* Called (from smc_निकास) when module is हटाओd */
व्योम smc_core_निकास(व्योम)
अणु
	unरेजिस्टर_reboot_notअगरier(&smc_reboot_notअगरier);
	smc_lgrs_shutकरोwn();
पूर्ण
