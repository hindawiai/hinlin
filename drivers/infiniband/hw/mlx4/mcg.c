<शैली गुरु>
/*
 * Copyright (c) 2012 Mellanox Technologies. All rights reserved.
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

#समावेश <rdma/ib_mad.h>
#समावेश <rdma/ib_smi.h>
#समावेश <rdma/ib_cache.h>
#समावेश <rdma/ib_sa.h>

#समावेश <linux/mlx4/cmd.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/delay.h>

#समावेश "mlx4_ib.h"

#घोषणा MAX_VFS		80
#घोषणा MAX_PEND_REQS_PER_FUNC 4
#घोषणा MAD_TIMEOUT_MS	2000

#घोषणा mcg_warn(fmt, arg...)	pr_warn("MCG WARNING: " fmt, ##arg)
#घोषणा mcg_error(fmt, arg...)	pr_err(fmt, ##arg)
#घोषणा mcg_warn_group(group, क्रमmat, arg...) \
	pr_warn("%s-%d: %16s (port %d): WARNING: " क्रमmat, __func__, __LINE__,\
	(group)->name, group->demux->port, ## arg)

#घोषणा mcg_debug_group(group, क्रमmat, arg...) \
	pr_debug("%s-%d: %16s (port %d): WARNING: " क्रमmat, __func__, __LINE__,\
		 (group)->name, (group)->demux->port, ## arg)

#घोषणा mcg_error_group(group, क्रमmat, arg...) \
	pr_err("  %16s: " क्रमmat, (group)->name, ## arg)


अटल जोड़ ib_gid mgid0;

अटल काष्ठा workqueue_काष्ठा *clean_wq;

क्रमागत mcast_state अणु
	MCAST_NOT_MEMBER = 0,
	MCAST_MEMBER,
पूर्ण;

क्रमागत mcast_group_state अणु
	MCAST_IDLE,
	MCAST_JOIN_SENT,
	MCAST_LEAVE_SENT,
	MCAST_RESP_READY
पूर्ण;

काष्ठा mcast_member अणु
	क्रमागत mcast_state state;
	uपूर्णांक8_t			join_state;
	पूर्णांक			num_pend_reqs;
	काष्ठा list_head	pending;
पूर्ण;

काष्ठा ib_sa_mcmember_data अणु
	जोड़ ib_gid	mgid;
	जोड़ ib_gid	port_gid;
	__be32		qkey;
	__be16		mlid;
	u8		mtusel_mtu;
	u8		tclass;
	__be16		pkey;
	u8		ratesel_rate;
	u8		lअगरeपंचांगsel_lअगरeपंचांग;
	__be32		sl_flowlabel_hoplimit;
	u8		scope_join_state;
	u8		proxy_join;
	u8		reserved[2];
पूर्ण __packed __aligned(4);

काष्ठा mcast_group अणु
	काष्ठा ib_sa_mcmember_data rec;
	काष्ठा rb_node		node;
	काष्ठा list_head	mgid0_list;
	काष्ठा mlx4_ib_demux_ctx *demux;
	काष्ठा mcast_member	func[MAX_VFS];
	काष्ठा mutex		lock;
	काष्ठा work_काष्ठा	work;
	काष्ठा list_head	pending_list;
	पूर्णांक			members[3];
	क्रमागत mcast_group_state	state;
	क्रमागत mcast_group_state	prev_state;
	काष्ठा ib_sa_mad	response_sa_mad;
	__be64			last_req_tid;

	अक्षर			name[33]; /* MGID string */
	काष्ठा device_attribute	dentry;

	/* refcount is the reference count क्रम the following:
	   1. Each queued request
	   2. Each invocation of the worker thपढ़ो
	   3. Membership of the port at the SA
	*/
	atomic_t		refcount;

	/* delayed work to clean pending SM request */
	काष्ठा delayed_work	समयout_work;
	काष्ठा list_head	cleanup_list;
पूर्ण;

काष्ठा mcast_req अणु
	पूर्णांक			func;
	काष्ठा ib_sa_mad	sa_mad;
	काष्ठा list_head	group_list;
	काष्ठा list_head	func_list;
	काष्ठा mcast_group	*group;
	पूर्णांक			clean;
पूर्ण;


#घोषणा safe_atomic_dec(ref) \
	करो अणु\
		अगर (atomic_dec_and_test(ref)) \
			mcg_warn_group(group, "did not expect to reach zero\n"); \
	पूर्ण जबतक (0)

अटल स्थिर अक्षर *get_state_string(क्रमागत mcast_group_state state)
अणु
	चयन (state) अणु
	हाल MCAST_IDLE:
		वापस "MCAST_IDLE";
	हाल MCAST_JOIN_SENT:
		वापस "MCAST_JOIN_SENT";
	हाल MCAST_LEAVE_SENT:
		वापस "MCAST_LEAVE_SENT";
	हाल MCAST_RESP_READY:
		वापस "MCAST_RESP_READY";
	पूर्ण
	वापस "Invalid State";
पूर्ण

अटल काष्ठा mcast_group *mcast_find(काष्ठा mlx4_ib_demux_ctx *ctx,
				      जोड़ ib_gid *mgid)
अणु
	काष्ठा rb_node *node = ctx->mcg_table.rb_node;
	काष्ठा mcast_group *group;
	पूर्णांक ret;

	जबतक (node) अणु
		group = rb_entry(node, काष्ठा mcast_group, node);
		ret = स_भेद(mgid->raw, group->rec.mgid.raw, माप *mgid);
		अगर (!ret)
			वापस group;

		अगर (ret < 0)
			node = node->rb_left;
		अन्यथा
			node = node->rb_right;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा mcast_group *mcast_insert(काष्ठा mlx4_ib_demux_ctx *ctx,
					काष्ठा mcast_group *group)
अणु
	काष्ठा rb_node **link = &ctx->mcg_table.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा mcast_group *cur_group;
	पूर्णांक ret;

	जबतक (*link) अणु
		parent = *link;
		cur_group = rb_entry(parent, काष्ठा mcast_group, node);

		ret = स_भेद(group->rec.mgid.raw, cur_group->rec.mgid.raw,
			     माप group->rec.mgid);
		अगर (ret < 0)
			link = &(*link)->rb_left;
		अन्यथा अगर (ret > 0)
			link = &(*link)->rb_right;
		अन्यथा
			वापस cur_group;
	पूर्ण
	rb_link_node(&group->node, parent, link);
	rb_insert_color(&group->node, &ctx->mcg_table);
	वापस शून्य;
पूर्ण

अटल पूर्णांक send_mad_to_wire(काष्ठा mlx4_ib_demux_ctx *ctx, काष्ठा ib_mad *mad)
अणु
	काष्ठा mlx4_ib_dev *dev = ctx->dev;
	काष्ठा rdma_ah_attr	ah_attr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->sm_lock, flags);
	अगर (!dev->sm_ah[ctx->port - 1]) अणु
		/* port is not yet Active, sm_ah not पढ़ोy */
		spin_unlock_irqrestore(&dev->sm_lock, flags);
		वापस -EAGAIN;
	पूर्ण
	mlx4_ib_query_ah(dev->sm_ah[ctx->port - 1], &ah_attr);
	spin_unlock_irqrestore(&dev->sm_lock, flags);
	वापस mlx4_ib_send_to_wire(dev, mlx4_master_func_num(dev->dev),
				    ctx->port, IB_QPT_GSI, 0, 1, IB_QP1_QKEY,
				    &ah_attr, शून्य, 0xffff, mad);
पूर्ण

अटल पूर्णांक send_mad_to_slave(पूर्णांक slave, काष्ठा mlx4_ib_demux_ctx *ctx,
			     काष्ठा ib_mad *mad)
अणु
	काष्ठा mlx4_ib_dev *dev = ctx->dev;
	काष्ठा ib_mad_agent *agent = dev->send_agent[ctx->port - 1][1];
	काष्ठा ib_wc wc;
	काष्ठा rdma_ah_attr ah_attr;

	/* Our agent might not yet be रेजिस्टरed when mads start to arrive */
	अगर (!agent)
		वापस -EAGAIN;

	rdma_query_ah(dev->sm_ah[ctx->port - 1], &ah_attr);

	अगर (ib_find_cached_pkey(&dev->ib_dev, ctx->port, IB_DEFAULT_PKEY_FULL, &wc.pkey_index))
		वापस -EINVAL;
	wc.sl = 0;
	wc.dlid_path_bits = 0;
	wc.port_num = ctx->port;
	wc.slid = rdma_ah_get_dlid(&ah_attr);  /* खोलोsm lid */
	wc.src_qp = 1;
	वापस mlx4_ib_send_to_slave(dev, slave, ctx->port, IB_QPT_GSI, &wc, शून्य, mad);
पूर्ण

अटल पूर्णांक send_join_to_wire(काष्ठा mcast_group *group, काष्ठा ib_sa_mad *sa_mad)
अणु
	काष्ठा ib_sa_mad mad;
	काष्ठा ib_sa_mcmember_data *sa_mad_data = (काष्ठा ib_sa_mcmember_data *)&mad.data;
	पूर्णांक ret;

	/* we rely on a mad request as arrived from a VF */
	स_नकल(&mad, sa_mad, माप mad);

	/* fix port GID to be the real one (slave 0) */
	sa_mad_data->port_gid.global.पूर्णांकerface_id = group->demux->guid_cache[0];

	/* assign our own TID */
	mad.mad_hdr.tid = mlx4_ib_get_new_demux_tid(group->demux);
	group->last_req_tid = mad.mad_hdr.tid; /* keep it क्रम later validation */

	ret = send_mad_to_wire(group->demux, (काष्ठा ib_mad *)&mad);
	/* set समयout handler */
	अगर (!ret) अणु
		/* calls mlx4_ib_mcg_समयout_handler */
		queue_delayed_work(group->demux->mcg_wq, &group->समयout_work,
				msecs_to_jअगरfies(MAD_TIMEOUT_MS));
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक send_leave_to_wire(काष्ठा mcast_group *group, u8 join_state)
अणु
	काष्ठा ib_sa_mad mad;
	काष्ठा ib_sa_mcmember_data *sa_data = (काष्ठा ib_sa_mcmember_data *)&mad.data;
	पूर्णांक ret;

	स_रखो(&mad, 0, माप mad);
	mad.mad_hdr.base_version = 1;
	mad.mad_hdr.mgmt_class = IB_MGMT_CLASS_SUBN_ADM;
	mad.mad_hdr.class_version = 2;
	mad.mad_hdr.method = IB_SA_METHOD_DELETE;
	mad.mad_hdr.status = cpu_to_be16(0);
	mad.mad_hdr.class_specअगरic = cpu_to_be16(0);
	mad.mad_hdr.tid = mlx4_ib_get_new_demux_tid(group->demux);
	group->last_req_tid = mad.mad_hdr.tid; /* keep it क्रम later validation */
	mad.mad_hdr.attr_id = cpu_to_be16(IB_SA_ATTR_MC_MEMBER_REC);
	mad.mad_hdr.attr_mod = cpu_to_be32(0);
	mad.sa_hdr.sm_key = 0x0;
	mad.sa_hdr.attr_offset = cpu_to_be16(7);
	mad.sa_hdr.comp_mask = IB_SA_MCMEMBER_REC_MGID |
		IB_SA_MCMEMBER_REC_PORT_GID | IB_SA_MCMEMBER_REC_JOIN_STATE;

	*sa_data = group->rec;
	sa_data->scope_join_state = join_state;

	ret = send_mad_to_wire(group->demux, (काष्ठा ib_mad *)&mad);
	अगर (ret)
		group->state = MCAST_IDLE;

	/* set समयout handler */
	अगर (!ret) अणु
		/* calls mlx4_ib_mcg_समयout_handler */
		queue_delayed_work(group->demux->mcg_wq, &group->समयout_work,
				msecs_to_jअगरfies(MAD_TIMEOUT_MS));
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक send_reply_to_slave(पूर्णांक slave, काष्ठा mcast_group *group,
		काष्ठा ib_sa_mad *req_sa_mad, u16 status)
अणु
	काष्ठा ib_sa_mad mad;
	काष्ठा ib_sa_mcmember_data *sa_data = (काष्ठा ib_sa_mcmember_data *)&mad.data;
	काष्ठा ib_sa_mcmember_data *req_sa_data = (काष्ठा ib_sa_mcmember_data *)&req_sa_mad->data;
	पूर्णांक ret;

	स_रखो(&mad, 0, माप mad);
	mad.mad_hdr.base_version = 1;
	mad.mad_hdr.mgmt_class = IB_MGMT_CLASS_SUBN_ADM;
	mad.mad_hdr.class_version = 2;
	mad.mad_hdr.method = IB_MGMT_METHOD_GET_RESP;
	mad.mad_hdr.status = cpu_to_be16(status);
	mad.mad_hdr.class_specअगरic = cpu_to_be16(0);
	mad.mad_hdr.tid = req_sa_mad->mad_hdr.tid;
	*(u8 *)&mad.mad_hdr.tid = 0; /* resetting tid to 0 */
	mad.mad_hdr.attr_id = cpu_to_be16(IB_SA_ATTR_MC_MEMBER_REC);
	mad.mad_hdr.attr_mod = cpu_to_be32(0);
	mad.sa_hdr.sm_key = req_sa_mad->sa_hdr.sm_key;
	mad.sa_hdr.attr_offset = cpu_to_be16(7);
	mad.sa_hdr.comp_mask = 0; /* ignored on responses, see IBTA spec */

	*sa_data = group->rec;

	/* reस्थिरruct VF's requested join_state and port_gid */
	sa_data->scope_join_state &= 0xf0;
	sa_data->scope_join_state |= (group->func[slave].join_state & 0x0f);
	स_नकल(&sa_data->port_gid, &req_sa_data->port_gid, माप req_sa_data->port_gid);

	ret = send_mad_to_slave(slave, group->demux, (काष्ठा ib_mad *)&mad);
	वापस ret;
पूर्ण

अटल पूर्णांक check_selector(ib_sa_comp_mask comp_mask,
			  ib_sa_comp_mask selector_mask,
			  ib_sa_comp_mask value_mask,
			  u8 src_value, u8 dst_value)
अणु
	पूर्णांक err;
	u8 selector = dst_value >> 6;
	dst_value &= 0x3f;
	src_value &= 0x3f;

	अगर (!(comp_mask & selector_mask) || !(comp_mask & value_mask))
		वापस 0;

	चयन (selector) अणु
	हाल IB_SA_GT:
		err = (src_value <= dst_value);
		अवरोध;
	हाल IB_SA_LT:
		err = (src_value >= dst_value);
		अवरोध;
	हाल IB_SA_EQ:
		err = (src_value != dst_value);
		अवरोध;
	शेष:
		err = 0;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल u16 cmp_rec(काष्ठा ib_sa_mcmember_data *src,
		   काष्ठा ib_sa_mcmember_data *dst, ib_sa_comp_mask comp_mask)
अणु
	/* src is group record, dst is request record */
	/* MGID must alपढ़ोy match */
	/* Port_GID we always replace to our Port_GID, so it is a match */

#घोषणा MAD_STATUS_REQ_INVALID 0x0200
	अगर (comp_mask & IB_SA_MCMEMBER_REC_QKEY && src->qkey != dst->qkey)
		वापस MAD_STATUS_REQ_INVALID;
	अगर (comp_mask & IB_SA_MCMEMBER_REC_MLID && src->mlid != dst->mlid)
		वापस MAD_STATUS_REQ_INVALID;
	अगर (check_selector(comp_mask, IB_SA_MCMEMBER_REC_MTU_SELECTOR,
				 IB_SA_MCMEMBER_REC_MTU,
				 src->mtusel_mtu, dst->mtusel_mtu))
		वापस MAD_STATUS_REQ_INVALID;
	अगर (comp_mask & IB_SA_MCMEMBER_REC_TRAFFIC_CLASS &&
	    src->tclass != dst->tclass)
		वापस MAD_STATUS_REQ_INVALID;
	अगर (comp_mask & IB_SA_MCMEMBER_REC_PKEY && src->pkey != dst->pkey)
		वापस MAD_STATUS_REQ_INVALID;
	अगर (check_selector(comp_mask, IB_SA_MCMEMBER_REC_RATE_SELECTOR,
				 IB_SA_MCMEMBER_REC_RATE,
				 src->ratesel_rate, dst->ratesel_rate))
		वापस MAD_STATUS_REQ_INVALID;
	अगर (check_selector(comp_mask,
				 IB_SA_MCMEMBER_REC_PACKET_LIFE_TIME_SELECTOR,
				 IB_SA_MCMEMBER_REC_PACKET_LIFE_TIME,
				 src->lअगरeपंचांगsel_lअगरeपंचांग, dst->lअगरeपंचांगsel_lअगरeपंचांग))
		वापस MAD_STATUS_REQ_INVALID;
	अगर (comp_mask & IB_SA_MCMEMBER_REC_SL &&
			(be32_to_cpu(src->sl_flowlabel_hoplimit) & 0xf0000000) !=
			(be32_to_cpu(dst->sl_flowlabel_hoplimit) & 0xf0000000))
		वापस MAD_STATUS_REQ_INVALID;
	अगर (comp_mask & IB_SA_MCMEMBER_REC_FLOW_LABEL &&
			(be32_to_cpu(src->sl_flowlabel_hoplimit) & 0x0fffff00) !=
			(be32_to_cpu(dst->sl_flowlabel_hoplimit) & 0x0fffff00))
		वापस MAD_STATUS_REQ_INVALID;
	अगर (comp_mask & IB_SA_MCMEMBER_REC_HOP_LIMIT &&
			(be32_to_cpu(src->sl_flowlabel_hoplimit) & 0x000000ff) !=
			(be32_to_cpu(dst->sl_flowlabel_hoplimit) & 0x000000ff))
		वापस MAD_STATUS_REQ_INVALID;
	अगर (comp_mask & IB_SA_MCMEMBER_REC_SCOPE &&
			(src->scope_join_state & 0xf0) !=
			(dst->scope_join_state & 0xf0))
		वापस MAD_STATUS_REQ_INVALID;

	/* join_state checked separately, proxy_join ignored */

	वापस 0;
पूर्ण

/* release group, वापस 1 अगर this was last release and group is destroyed
 * timout work is canceled sync */
अटल पूर्णांक release_group(काष्ठा mcast_group *group, पूर्णांक from_समयout_handler)
अणु
	काष्ठा mlx4_ib_demux_ctx *ctx = group->demux;
	पूर्णांक nzgroup;

	mutex_lock(&ctx->mcg_table_lock);
	mutex_lock(&group->lock);
	अगर (atomic_dec_and_test(&group->refcount)) अणु
		अगर (!from_समयout_handler) अणु
			अगर (group->state != MCAST_IDLE &&
			    !cancel_delayed_work(&group->समयout_work)) अणु
				atomic_inc(&group->refcount);
				mutex_unlock(&group->lock);
				mutex_unlock(&ctx->mcg_table_lock);
				वापस 0;
			पूर्ण
		पूर्ण

		nzgroup = स_भेद(&group->rec.mgid, &mgid0, माप mgid0);
		अगर (nzgroup)
			del_sysfs_port_mcg_attr(ctx->dev, ctx->port, &group->dentry.attr);
		अगर (!list_empty(&group->pending_list))
			mcg_warn_group(group, "releasing a group with non empty pending list\n");
		अगर (nzgroup)
			rb_erase(&group->node, &ctx->mcg_table);
		list_del_init(&group->mgid0_list);
		mutex_unlock(&group->lock);
		mutex_unlock(&ctx->mcg_table_lock);
		kमुक्त(group);
		वापस 1;
	पूर्ण अन्यथा अणु
		mutex_unlock(&group->lock);
		mutex_unlock(&ctx->mcg_table_lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम adjust_membership(काष्ठा mcast_group *group, u8 join_state, पूर्णांक inc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++, join_state >>= 1)
		अगर (join_state & 0x1)
			group->members[i] += inc;
पूर्ण

अटल u8 get_leave_state(काष्ठा mcast_group *group)
अणु
	u8 leave_state = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++)
		अगर (!group->members[i])
			leave_state |= (1 << i);

	वापस leave_state & (group->rec.scope_join_state & 0xf);
पूर्ण

अटल पूर्णांक join_group(काष्ठा mcast_group *group, पूर्णांक slave, u8 join_mask)
अणु
	पूर्णांक ret = 0;
	u8 join_state;

	/* हटाओ bits that slave is alपढ़ोy member of, and adjust */
	join_state = join_mask & (~group->func[slave].join_state);
	adjust_membership(group, join_state, 1);
	group->func[slave].join_state |= join_state;
	अगर (group->func[slave].state != MCAST_MEMBER && join_state) अणु
		group->func[slave].state = MCAST_MEMBER;
		ret = 1;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक leave_group(काष्ठा mcast_group *group, पूर्णांक slave, u8 leave_state)
अणु
	पूर्णांक ret = 0;

	adjust_membership(group, leave_state, -1);
	group->func[slave].join_state &= ~leave_state;
	अगर (!group->func[slave].join_state) अणु
		group->func[slave].state = MCAST_NOT_MEMBER;
		ret = 1;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक check_leave(काष्ठा mcast_group *group, पूर्णांक slave, u8 leave_mask)
अणु
	अगर (group->func[slave].state != MCAST_MEMBER)
		वापस MAD_STATUS_REQ_INVALID;

	/* make sure we're not deleting unset bits */
	अगर (~group->func[slave].join_state & leave_mask)
		वापस MAD_STATUS_REQ_INVALID;

	अगर (!leave_mask)
		वापस MAD_STATUS_REQ_INVALID;

	वापस 0;
पूर्ण

अटल व्योम mlx4_ib_mcg_समयout_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delay = to_delayed_work(work);
	काष्ठा mcast_group *group;
	काष्ठा mcast_req *req = शून्य;

	group = container_of(delay, typeof(*group), समयout_work);

	mutex_lock(&group->lock);
	अगर (group->state == MCAST_JOIN_SENT) अणु
		अगर (!list_empty(&group->pending_list)) अणु
			req = list_first_entry(&group->pending_list, काष्ठा mcast_req, group_list);
			list_del(&req->group_list);
			list_del(&req->func_list);
			--group->func[req->func].num_pend_reqs;
			mutex_unlock(&group->lock);
			kमुक्त(req);
			अगर (स_भेद(&group->rec.mgid, &mgid0, माप mgid0)) अणु
				अगर (release_group(group, 1))
					वापस;
			पूर्ण अन्यथा अणु
				kमुक्त(group);
				वापस;
			पूर्ण
			mutex_lock(&group->lock);
		पूर्ण अन्यथा
			mcg_warn_group(group, "DRIVER BUG\n");
	पूर्ण अन्यथा अगर (group->state == MCAST_LEAVE_SENT) अणु
		अगर (group->rec.scope_join_state & 0xf)
			group->rec.scope_join_state &= 0xf0;
		group->state = MCAST_IDLE;
		mutex_unlock(&group->lock);
		अगर (release_group(group, 1))
			वापस;
		mutex_lock(&group->lock);
	पूर्ण अन्यथा
		mcg_warn_group(group, "invalid state %s\n", get_state_string(group->state));
	group->state = MCAST_IDLE;
	atomic_inc(&group->refcount);
	अगर (!queue_work(group->demux->mcg_wq, &group->work))
		safe_atomic_dec(&group->refcount);

	mutex_unlock(&group->lock);
पूर्ण

अटल पूर्णांक handle_leave_req(काष्ठा mcast_group *group, u8 leave_mask,
			    काष्ठा mcast_req *req)
अणु
	u16 status;

	अगर (req->clean)
		leave_mask = group->func[req->func].join_state;

	status = check_leave(group, req->func, leave_mask);
	अगर (!status)
		leave_group(group, req->func, leave_mask);

	अगर (!req->clean)
		send_reply_to_slave(req->func, group, &req->sa_mad, status);
	--group->func[req->func].num_pend_reqs;
	list_del(&req->group_list);
	list_del(&req->func_list);
	kमुक्त(req);
	वापस 1;
पूर्ण

अटल पूर्णांक handle_join_req(काष्ठा mcast_group *group, u8 join_mask,
			   काष्ठा mcast_req *req)
अणु
	u8 group_join_state = group->rec.scope_join_state & 0xf;
	पूर्णांक ref = 0;
	u16 status;
	काष्ठा ib_sa_mcmember_data *sa_data = (काष्ठा ib_sa_mcmember_data *)req->sa_mad.data;

	अगर (join_mask == (group_join_state & join_mask)) अणु
		/* port's membership need not change */
		status = cmp_rec(&group->rec, sa_data, req->sa_mad.sa_hdr.comp_mask);
		अगर (!status)
			join_group(group, req->func, join_mask);

		--group->func[req->func].num_pend_reqs;
		send_reply_to_slave(req->func, group, &req->sa_mad, status);
		list_del(&req->group_list);
		list_del(&req->func_list);
		kमुक्त(req);
		++ref;
	पूर्ण अन्यथा अणु
		/* port's membership needs to be updated */
		group->prev_state = group->state;
		अगर (send_join_to_wire(group, &req->sa_mad)) अणु
			--group->func[req->func].num_pend_reqs;
			list_del(&req->group_list);
			list_del(&req->func_list);
			kमुक्त(req);
			ref = 1;
			group->state = group->prev_state;
		पूर्ण अन्यथा
			group->state = MCAST_JOIN_SENT;
	पूर्ण

	वापस ref;
पूर्ण

अटल व्योम mlx4_ib_mcg_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mcast_group *group;
	काष्ठा mcast_req *req = शून्य;
	काष्ठा ib_sa_mcmember_data *sa_data;
	u8 req_join_state;
	पूर्णांक rc = 1; /* release_count - this is क्रम the scheduled work */
	u16 status;
	u8 method;

	group = container_of(work, typeof(*group), work);

	mutex_lock(&group->lock);

	/* First, let's see अगर a response from SM is रुकोing regarding this group.
	 * If so, we need to update the group's REC. If this is a bad response, we
	 * may need to send a bad response to a VF रुकोing क्रम it. If VF is रुकोing
	 * and this is a good response, the VF will be answered later in this func. */
	अगर (group->state == MCAST_RESP_READY) अणु
		/* cancels mlx4_ib_mcg_समयout_handler */
		cancel_delayed_work(&group->समयout_work);
		status = be16_to_cpu(group->response_sa_mad.mad_hdr.status);
		method = group->response_sa_mad.mad_hdr.method;
		अगर (group->last_req_tid != group->response_sa_mad.mad_hdr.tid) अणु
			mcg_warn_group(group, "Got MAD response to existing MGID but wrong TID, dropping. Resp TID=%llx, group TID=%llx\n",
				be64_to_cpu(group->response_sa_mad.mad_hdr.tid),
				be64_to_cpu(group->last_req_tid));
			group->state = group->prev_state;
			जाओ process_requests;
		पूर्ण
		अगर (status) अणु
			अगर (!list_empty(&group->pending_list))
				req = list_first_entry(&group->pending_list,
						काष्ठा mcast_req, group_list);
			अगर (method == IB_MGMT_METHOD_GET_RESP) अणु
					अगर (req) अणु
						send_reply_to_slave(req->func, group, &req->sa_mad, status);
						--group->func[req->func].num_pend_reqs;
						list_del(&req->group_list);
						list_del(&req->func_list);
						kमुक्त(req);
						++rc;
					पूर्ण अन्यथा
						mcg_warn_group(group, "no request for failed join\n");
			पूर्ण अन्यथा अगर (method == IB_SA_METHOD_DELETE_RESP && group->demux->flushing)
				++rc;
		पूर्ण अन्यथा अणु
			u8 resp_join_state;
			u8 cur_join_state;

			resp_join_state = ((काष्ठा ib_sa_mcmember_data *)
						group->response_sa_mad.data)->scope_join_state & 0xf;
			cur_join_state = group->rec.scope_join_state & 0xf;

			अगर (method == IB_MGMT_METHOD_GET_RESP) अणु
				/* successfull join */
				अगर (!cur_join_state && resp_join_state)
					--rc;
			पूर्ण अन्यथा अगर (!resp_join_state)
					++rc;
			स_नकल(&group->rec, group->response_sa_mad.data, माप group->rec);
		पूर्ण
		group->state = MCAST_IDLE;
	पूर्ण

process_requests:
	/* We should now go over pending join/leave requests, as दीर्घ as we are idle. */
	जबतक (!list_empty(&group->pending_list) && group->state == MCAST_IDLE) अणु
		req = list_first_entry(&group->pending_list, काष्ठा mcast_req,
				       group_list);
		sa_data = (काष्ठा ib_sa_mcmember_data *)req->sa_mad.data;
		req_join_state = sa_data->scope_join_state & 0xf;

		/* For a leave request, we will immediately answer the VF, and
		 * update our पूर्णांकernal counters. The actual leave will be sent
		 * to SM later, अगर at all needed. We dequeue the request now. */
		अगर (req->sa_mad.mad_hdr.method == IB_SA_METHOD_DELETE)
			rc += handle_leave_req(group, req_join_state, req);
		अन्यथा
			rc += handle_join_req(group, req_join_state, req);
	पूर्ण

	/* Handle leaves */
	अगर (group->state == MCAST_IDLE) अणु
		req_join_state = get_leave_state(group);
		अगर (req_join_state) अणु
			group->rec.scope_join_state &= ~req_join_state;
			group->prev_state = group->state;
			अगर (send_leave_to_wire(group, req_join_state)) अणु
				group->state = group->prev_state;
				++rc;
			पूर्ण अन्यथा
				group->state = MCAST_LEAVE_SENT;
		पूर्ण
	पूर्ण

	अगर (!list_empty(&group->pending_list) && group->state == MCAST_IDLE)
		जाओ process_requests;
	mutex_unlock(&group->lock);

	जबतक (rc--)
		release_group(group, 0);
पूर्ण

अटल काष्ठा mcast_group *search_relocate_mgid0_group(काष्ठा mlx4_ib_demux_ctx *ctx,
						       __be64 tid,
						       जोड़ ib_gid *new_mgid)
अणु
	काष्ठा mcast_group *group = शून्य, *cur_group, *n;
	काष्ठा mcast_req *req;

	mutex_lock(&ctx->mcg_table_lock);
	list_क्रम_each_entry_safe(group, n, &ctx->mcg_mgid0_list, mgid0_list) अणु
		mutex_lock(&group->lock);
		अगर (group->last_req_tid == tid) अणु
			अगर (स_भेद(new_mgid, &mgid0, माप mgid0)) अणु
				group->rec.mgid = *new_mgid;
				प्र_लिखो(group->name, "%016llx%016llx",
						be64_to_cpu(group->rec.mgid.global.subnet_prefix),
						be64_to_cpu(group->rec.mgid.global.पूर्णांकerface_id));
				list_del_init(&group->mgid0_list);
				cur_group = mcast_insert(ctx, group);
				अगर (cur_group) अणु
					/* A race between our code and SM. Silently cleaning the new one */
					req = list_first_entry(&group->pending_list,
							       काष्ठा mcast_req, group_list);
					--group->func[req->func].num_pend_reqs;
					list_del(&req->group_list);
					list_del(&req->func_list);
					kमुक्त(req);
					mutex_unlock(&group->lock);
					mutex_unlock(&ctx->mcg_table_lock);
					release_group(group, 0);
					वापस शून्य;
				पूर्ण

				atomic_inc(&group->refcount);
				add_sysfs_port_mcg_attr(ctx->dev, ctx->port, &group->dentry.attr);
				mutex_unlock(&group->lock);
				mutex_unlock(&ctx->mcg_table_lock);
				वापस group;
			पूर्ण अन्यथा अणु
				काष्ठा mcast_req *पंचांगp1, *पंचांगp2;

				list_del(&group->mgid0_list);
				अगर (!list_empty(&group->pending_list) && group->state != MCAST_IDLE)
					cancel_delayed_work_sync(&group->समयout_work);

				list_क्रम_each_entry_safe(पंचांगp1, पंचांगp2, &group->pending_list, group_list) अणु
					list_del(&पंचांगp1->group_list);
					kमुक्त(पंचांगp1);
				पूर्ण
				mutex_unlock(&group->lock);
				mutex_unlock(&ctx->mcg_table_lock);
				kमुक्त(group);
				वापस शून्य;
			पूर्ण
		पूर्ण
		mutex_unlock(&group->lock);
	पूर्ण
	mutex_unlock(&ctx->mcg_table_lock);

	वापस शून्य;
पूर्ण

अटल sमाप_प्रकार sysfs_show_group(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf);

अटल काष्ठा mcast_group *acquire_group(काष्ठा mlx4_ib_demux_ctx *ctx,
					 जोड़ ib_gid *mgid, पूर्णांक create)
अणु
	काष्ठा mcast_group *group, *cur_group;
	पूर्णांक is_mgid0;
	पूर्णांक i;

	is_mgid0 = !स_भेद(&mgid0, mgid, माप mgid0);
	अगर (!is_mgid0) अणु
		group = mcast_find(ctx, mgid);
		अगर (group)
			जाओ found;
	पूर्ण

	अगर (!create)
		वापस ERR_PTR(-ENOENT);

	group = kzalloc(माप(*group), GFP_KERNEL);
	अगर (!group)
		वापस ERR_PTR(-ENOMEM);

	group->demux = ctx;
	group->rec.mgid = *mgid;
	INIT_LIST_HEAD(&group->pending_list);
	INIT_LIST_HEAD(&group->mgid0_list);
	क्रम (i = 0; i < MAX_VFS; ++i)
		INIT_LIST_HEAD(&group->func[i].pending);
	INIT_WORK(&group->work, mlx4_ib_mcg_work_handler);
	INIT_DELAYED_WORK(&group->समयout_work, mlx4_ib_mcg_समयout_handler);
	mutex_init(&group->lock);
	प्र_लिखो(group->name, "%016llx%016llx",
			be64_to_cpu(group->rec.mgid.global.subnet_prefix),
			be64_to_cpu(group->rec.mgid.global.पूर्णांकerface_id));
	sysfs_attr_init(&group->dentry.attr);
	group->dentry.show = sysfs_show_group;
	group->dentry.store = शून्य;
	group->dentry.attr.name = group->name;
	group->dentry.attr.mode = 0400;
	group->state = MCAST_IDLE;

	अगर (is_mgid0) अणु
		list_add(&group->mgid0_list, &ctx->mcg_mgid0_list);
		जाओ found;
	पूर्ण

	cur_group = mcast_insert(ctx, group);
	अगर (cur_group) अणु
		mcg_warn("group just showed up %s - confused\n", cur_group->name);
		kमुक्त(group);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	add_sysfs_port_mcg_attr(ctx->dev, ctx->port, &group->dentry.attr);

found:
	atomic_inc(&group->refcount);
	वापस group;
पूर्ण

अटल व्योम queue_req(काष्ठा mcast_req *req)
अणु
	काष्ठा mcast_group *group = req->group;

	atomic_inc(&group->refcount); /* क्रम the request */
	atomic_inc(&group->refcount); /* क्रम scheduling the work */
	list_add_tail(&req->group_list, &group->pending_list);
	list_add_tail(&req->func_list, &group->func[req->func].pending);
	/* calls mlx4_ib_mcg_work_handler */
	अगर (!queue_work(group->demux->mcg_wq, &group->work))
		safe_atomic_dec(&group->refcount);
पूर्ण

पूर्णांक mlx4_ib_mcg_demux_handler(काष्ठा ib_device *ibdev, पूर्णांक port, पूर्णांक slave,
			      काष्ठा ib_sa_mad *mad)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(ibdev);
	काष्ठा ib_sa_mcmember_data *rec = (काष्ठा ib_sa_mcmember_data *)mad->data;
	काष्ठा mlx4_ib_demux_ctx *ctx = &dev->sriov.demux[port - 1];
	काष्ठा mcast_group *group;

	चयन (mad->mad_hdr.method) अणु
	हाल IB_MGMT_METHOD_GET_RESP:
	हाल IB_SA_METHOD_DELETE_RESP:
		mutex_lock(&ctx->mcg_table_lock);
		group = acquire_group(ctx, &rec->mgid, 0);
		mutex_unlock(&ctx->mcg_table_lock);
		अगर (IS_ERR(group)) अणु
			अगर (mad->mad_hdr.method == IB_MGMT_METHOD_GET_RESP) अणु
				__be64 tid = mad->mad_hdr.tid;
				*(u8 *)(&tid) = (u8)slave; /* in group we kept the modअगरied TID */
				group = search_relocate_mgid0_group(ctx, tid, &rec->mgid);
			पूर्ण अन्यथा
				group = शून्य;
		पूर्ण

		अगर (!group)
			वापस 1;

		mutex_lock(&group->lock);
		group->response_sa_mad = *mad;
		group->prev_state = group->state;
		group->state = MCAST_RESP_READY;
		/* calls mlx4_ib_mcg_work_handler */
		atomic_inc(&group->refcount);
		अगर (!queue_work(ctx->mcg_wq, &group->work))
			safe_atomic_dec(&group->refcount);
		mutex_unlock(&group->lock);
		release_group(group, 0);
		वापस 1; /* consumed */
	हाल IB_MGMT_METHOD_SET:
	हाल IB_SA_METHOD_GET_TABLE:
	हाल IB_SA_METHOD_GET_TABLE_RESP:
	हाल IB_SA_METHOD_DELETE:
		वापस 0; /* not consumed, pass-through to guest over tunnel */
	शेष:
		mcg_warn("In demux, port %d: unexpected MCMember method: 0x%x, dropping\n",
			port, mad->mad_hdr.method);
		वापस 1; /* consumed */
	पूर्ण
पूर्ण

पूर्णांक mlx4_ib_mcg_multiplex_handler(काष्ठा ib_device *ibdev, पूर्णांक port,
				  पूर्णांक slave, काष्ठा ib_sa_mad *sa_mad)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(ibdev);
	काष्ठा ib_sa_mcmember_data *rec = (काष्ठा ib_sa_mcmember_data *)sa_mad->data;
	काष्ठा mlx4_ib_demux_ctx *ctx = &dev->sriov.demux[port - 1];
	काष्ठा mcast_group *group;
	काष्ठा mcast_req *req;
	पूर्णांक may_create = 0;

	अगर (ctx->flushing)
		वापस -EAGAIN;

	चयन (sa_mad->mad_hdr.method) अणु
	हाल IB_MGMT_METHOD_SET:
		may_create = 1;
		fallthrough;
	हाल IB_SA_METHOD_DELETE:
		req = kzalloc(माप *req, GFP_KERNEL);
		अगर (!req)
			वापस -ENOMEM;

		req->func = slave;
		req->sa_mad = *sa_mad;

		mutex_lock(&ctx->mcg_table_lock);
		group = acquire_group(ctx, &rec->mgid, may_create);
		mutex_unlock(&ctx->mcg_table_lock);
		अगर (IS_ERR(group)) अणु
			kमुक्त(req);
			वापस PTR_ERR(group);
		पूर्ण
		mutex_lock(&group->lock);
		अगर (group->func[slave].num_pend_reqs > MAX_PEND_REQS_PER_FUNC) अणु
			mutex_unlock(&group->lock);
			mcg_debug_group(group, "Port %d, Func %d has too many pending requests (%d), dropping\n",
					port, slave, MAX_PEND_REQS_PER_FUNC);
			release_group(group, 0);
			kमुक्त(req);
			वापस -ENOMEM;
		पूर्ण
		++group->func[slave].num_pend_reqs;
		req->group = group;
		queue_req(req);
		mutex_unlock(&group->lock);
		release_group(group, 0);
		वापस 1; /* consumed */
	हाल IB_SA_METHOD_GET_TABLE:
	हाल IB_MGMT_METHOD_GET_RESP:
	हाल IB_SA_METHOD_GET_TABLE_RESP:
	हाल IB_SA_METHOD_DELETE_RESP:
		वापस 0; /* not consumed, pass-through */
	शेष:
		mcg_warn("In multiplex, port %d, func %d: unexpected MCMember method: 0x%x, dropping\n",
			port, slave, sa_mad->mad_hdr.method);
		वापस 1; /* consumed */
	पूर्ण
पूर्ण

अटल sमाप_प्रकार sysfs_show_group(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mcast_group *group =
		container_of(attr, काष्ठा mcast_group, dentry);
	काष्ठा mcast_req *req = शून्य;
	अक्षर state_str[40];
	अक्षर pending_str[40];
	पूर्णांक len;
	पूर्णांक i;
	u32 hoplimit;

	अगर (group->state == MCAST_IDLE)
		scnम_लिखो(state_str, माप(state_str), "%s",
			  get_state_string(group->state));
	अन्यथा
		scnम_लिखो(state_str, माप(state_str), "%s(TID=0x%llx)",
			  get_state_string(group->state),
			  be64_to_cpu(group->last_req_tid));

	अगर (list_empty(&group->pending_list)) अणु
		scnम_लिखो(pending_str, माप(pending_str), "No");
	पूर्ण अन्यथा अणु
		req = list_first_entry(&group->pending_list, काष्ठा mcast_req,
				       group_list);
		scnम_लिखो(pending_str, माप(pending_str), "Yes(TID=0x%llx)",
			  be64_to_cpu(req->sa_mad.mad_hdr.tid));
	पूर्ण

	len = sysfs_emit(buf, "%1d [%02d,%02d,%02d] %4d %4s %5s     ",
			 group->rec.scope_join_state & 0xf,
			 group->members[2],
			 group->members[1],
			 group->members[0],
			 atomic_पढ़ो(&group->refcount),
			 pending_str,
			 state_str);

	क्रम (i = 0; i < MAX_VFS; i++) अणु
		अगर (group->func[i].state == MCAST_MEMBER)
			len += sysfs_emit_at(buf, len, "%d[%1x] ", i,
					     group->func[i].join_state);
	पूर्ण

	hoplimit = be32_to_cpu(group->rec.sl_flowlabel_hoplimit);
	len += sysfs_emit_at(buf, len,
			     "\t\t(%4hx %4x %2x %2x %2x %2x %2x %4x %4x %2x %2x)\n",
			     be16_to_cpu(group->rec.pkey),
			     be32_to_cpu(group->rec.qkey),
			     (group->rec.mtusel_mtu & 0xc0) >> 6,
			     (group->rec.mtusel_mtu & 0x3f),
			     group->rec.tclass,
			     (group->rec.ratesel_rate & 0xc0) >> 6,
			     (group->rec.ratesel_rate & 0x3f),
			     (hoplimit & 0xf0000000) >> 28,
			     (hoplimit & 0x0fffff00) >> 8,
			     (hoplimit & 0x000000ff),
			     group->rec.proxy_join);

	वापस len;
पूर्ण

पूर्णांक mlx4_ib_mcg_port_init(काष्ठा mlx4_ib_demux_ctx *ctx)
अणु
	अक्षर name[20];

	atomic_set(&ctx->tid, 0);
	प्र_लिखो(name, "mlx4_ib_mcg%d", ctx->port);
	ctx->mcg_wq = alloc_ordered_workqueue(name, WQ_MEM_RECLAIM);
	अगर (!ctx->mcg_wq)
		वापस -ENOMEM;

	mutex_init(&ctx->mcg_table_lock);
	ctx->mcg_table = RB_ROOT;
	INIT_LIST_HEAD(&ctx->mcg_mgid0_list);
	ctx->flushing = 0;

	वापस 0;
पूर्ण

अटल व्योम क्रमce_clean_group(काष्ठा mcast_group *group)
अणु
	काष्ठा mcast_req *req, *पंचांगp
		;
	list_क्रम_each_entry_safe(req, पंचांगp, &group->pending_list, group_list) अणु
		list_del(&req->group_list);
		kमुक्त(req);
	पूर्ण
	del_sysfs_port_mcg_attr(group->demux->dev, group->demux->port, &group->dentry.attr);
	rb_erase(&group->node, &group->demux->mcg_table);
	kमुक्त(group);
पूर्ण

अटल व्योम _mlx4_ib_mcg_port_cleanup(काष्ठा mlx4_ib_demux_ctx *ctx, पूर्णांक destroy_wq)
अणु
	पूर्णांक i;
	काष्ठा rb_node *p;
	काष्ठा mcast_group *group;
	अचिन्हित दीर्घ end;
	पूर्णांक count;

	क्रम (i = 0; i < MAX_VFS; ++i)
		clean_vf_mcast(ctx, i);

	end = jअगरfies + msecs_to_jअगरfies(MAD_TIMEOUT_MS + 3000);
	करो अणु
		count = 0;
		mutex_lock(&ctx->mcg_table_lock);
		क्रम (p = rb_first(&ctx->mcg_table); p; p = rb_next(p))
			++count;
		mutex_unlock(&ctx->mcg_table_lock);
		अगर (!count)
			अवरोध;

		usleep_range(1000, 2000);
	पूर्ण जबतक (समय_after(end, jअगरfies));

	flush_workqueue(ctx->mcg_wq);
	अगर (destroy_wq)
		destroy_workqueue(ctx->mcg_wq);

	mutex_lock(&ctx->mcg_table_lock);
	जबतक ((p = rb_first(&ctx->mcg_table)) != शून्य) अणु
		group = rb_entry(p, काष्ठा mcast_group, node);
		अगर (atomic_पढ़ो(&group->refcount))
			mcg_debug_group(group, "group refcount %d!!! (pointer %p)\n",
					atomic_पढ़ो(&group->refcount), group);

		क्रमce_clean_group(group);
	पूर्ण
	mutex_unlock(&ctx->mcg_table_lock);
पूर्ण

काष्ठा clean_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा mlx4_ib_demux_ctx *ctx;
	पूर्णांक destroy_wq;
पूर्ण;

अटल व्योम mcg_clean_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा clean_work *cw = container_of(work, काष्ठा clean_work, work);

	_mlx4_ib_mcg_port_cleanup(cw->ctx, cw->destroy_wq);
	cw->ctx->flushing = 0;
	kमुक्त(cw);
पूर्ण

व्योम mlx4_ib_mcg_port_cleanup(काष्ठा mlx4_ib_demux_ctx *ctx, पूर्णांक destroy_wq)
अणु
	काष्ठा clean_work *work;

	अगर (ctx->flushing)
		वापस;

	ctx->flushing = 1;

	अगर (destroy_wq) अणु
		_mlx4_ib_mcg_port_cleanup(ctx, destroy_wq);
		ctx->flushing = 0;
		वापस;
	पूर्ण

	work = kदो_स्मृति(माप *work, GFP_KERNEL);
	अगर (!work) अणु
		ctx->flushing = 0;
		वापस;
	पूर्ण

	work->ctx = ctx;
	work->destroy_wq = destroy_wq;
	INIT_WORK(&work->work, mcg_clean_task);
	queue_work(clean_wq, &work->work);
पूर्ण

अटल व्योम build_leave_mad(काष्ठा mcast_req *req)
अणु
	काष्ठा ib_sa_mad *mad = &req->sa_mad;

	mad->mad_hdr.method = IB_SA_METHOD_DELETE;
पूर्ण


अटल व्योम clear_pending_reqs(काष्ठा mcast_group *group, पूर्णांक vf)
अणु
	काष्ठा mcast_req *req, *पंचांगp, *group_first = शून्य;
	पूर्णांक clear;
	पूर्णांक pend = 0;

	अगर (!list_empty(&group->pending_list))
		group_first = list_first_entry(&group->pending_list, काष्ठा mcast_req, group_list);

	list_क्रम_each_entry_safe(req, पंचांगp, &group->func[vf].pending, func_list) अणु
		clear = 1;
		अगर (group_first == req &&
		    (group->state == MCAST_JOIN_SENT ||
		     group->state == MCAST_LEAVE_SENT)) अणु
			clear = cancel_delayed_work(&group->समयout_work);
			pend = !clear;
			group->state = MCAST_IDLE;
		पूर्ण
		अगर (clear) अणु
			--group->func[vf].num_pend_reqs;
			list_del(&req->group_list);
			list_del(&req->func_list);
			kमुक्त(req);
			atomic_dec(&group->refcount);
		पूर्ण
	पूर्ण

	अगर (!pend && (!list_empty(&group->func[vf].pending) || group->func[vf].num_pend_reqs)) अणु
		mcg_warn_group(group, "DRIVER BUG: list_empty %d, num_pend_reqs %d\n",
			       list_empty(&group->func[vf].pending), group->func[vf].num_pend_reqs);
	पूर्ण
पूर्ण

अटल पूर्णांक push_deleteing_req(काष्ठा mcast_group *group, पूर्णांक slave)
अणु
	काष्ठा mcast_req *req;
	काष्ठा mcast_req *pend_req;

	अगर (!group->func[slave].join_state)
		वापस 0;

	req = kzalloc(माप *req, GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	अगर (!list_empty(&group->func[slave].pending)) अणु
		pend_req = list_entry(group->func[slave].pending.prev, काष्ठा mcast_req, group_list);
		अगर (pend_req->clean) अणु
			kमुक्त(req);
			वापस 0;
		पूर्ण
	पूर्ण

	req->clean = 1;
	req->func = slave;
	req->group = group;
	++group->func[slave].num_pend_reqs;
	build_leave_mad(req);
	queue_req(req);
	वापस 0;
पूर्ण

व्योम clean_vf_mcast(काष्ठा mlx4_ib_demux_ctx *ctx, पूर्णांक slave)
अणु
	काष्ठा mcast_group *group;
	काष्ठा rb_node *p;

	mutex_lock(&ctx->mcg_table_lock);
	क्रम (p = rb_first(&ctx->mcg_table); p; p = rb_next(p)) अणु
		group = rb_entry(p, काष्ठा mcast_group, node);
		mutex_lock(&group->lock);
		अगर (atomic_पढ़ो(&group->refcount)) अणु
			/* clear pending requests of this VF */
			clear_pending_reqs(group, slave);
			push_deleteing_req(group, slave);
		पूर्ण
		mutex_unlock(&group->lock);
	पूर्ण
	mutex_unlock(&ctx->mcg_table_lock);
पूर्ण


पूर्णांक mlx4_ib_mcg_init(व्योम)
अणु
	clean_wq = alloc_ordered_workqueue("mlx4_ib_mcg", WQ_MEM_RECLAIM);
	अगर (!clean_wq)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम mlx4_ib_mcg_destroy(व्योम)
अणु
	destroy_workqueue(clean_wq);
पूर्ण
