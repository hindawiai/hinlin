<शैली गुरु>
/*
 * Copyright (c) 2006 Intel Corporation.  All rights reserved.
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

#समावेश <linux/completion.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/अक्रमom.h>

#समावेश <rdma/ib_cache.h>
#समावेश "sa.h"

अटल पूर्णांक mcast_add_one(काष्ठा ib_device *device);
अटल व्योम mcast_हटाओ_one(काष्ठा ib_device *device, व्योम *client_data);

अटल काष्ठा ib_client mcast_client = अणु
	.name   = "ib_multicast",
	.add    = mcast_add_one,
	.हटाओ = mcast_हटाओ_one
पूर्ण;

अटल काष्ठा ib_sa_client	sa_client;
अटल काष्ठा workqueue_काष्ठा	*mcast_wq;
अटल जोड़ ib_gid mgid0;

काष्ठा mcast_device;

काष्ठा mcast_port अणु
	काष्ठा mcast_device	*dev;
	spinlock_t		lock;
	काष्ठा rb_root		table;
	atomic_t		refcount;
	काष्ठा completion	comp;
	u32			port_num;
पूर्ण;

काष्ठा mcast_device अणु
	काष्ठा ib_device	*device;
	काष्ठा ib_event_handler	event_handler;
	पूर्णांक			start_port;
	पूर्णांक			end_port;
	काष्ठा mcast_port	port[];
पूर्ण;

क्रमागत mcast_state अणु
	MCAST_JOINING,
	MCAST_MEMBER,
	MCAST_ERROR,
पूर्ण;

क्रमागत mcast_group_state अणु
	MCAST_IDLE,
	MCAST_BUSY,
	MCAST_GROUP_ERROR,
	MCAST_PKEY_EVENT
पूर्ण;

क्रमागत अणु
	MCAST_INVALID_PKEY_INDEX = 0xFFFF
पूर्ण;

काष्ठा mcast_member;

काष्ठा mcast_group अणु
	काष्ठा ib_sa_mcmember_rec rec;
	काष्ठा rb_node		node;
	काष्ठा mcast_port	*port;
	spinlock_t		lock;
	काष्ठा work_काष्ठा	work;
	काष्ठा list_head	pending_list;
	काष्ठा list_head	active_list;
	काष्ठा mcast_member	*last_join;
	पूर्णांक			members[NUM_JOIN_MEMBERSHIP_TYPES];
	atomic_t		refcount;
	क्रमागत mcast_group_state	state;
	काष्ठा ib_sa_query	*query;
	u16			pkey_index;
	u8			leave_state;
	पूर्णांक			retries;
पूर्ण;

काष्ठा mcast_member अणु
	काष्ठा ib_sa_multicast	multicast;
	काष्ठा ib_sa_client	*client;
	काष्ठा mcast_group	*group;
	काष्ठा list_head	list;
	क्रमागत mcast_state	state;
	atomic_t		refcount;
	काष्ठा completion	comp;
पूर्ण;

अटल व्योम join_handler(पूर्णांक status, काष्ठा ib_sa_mcmember_rec *rec,
			 व्योम *context);
अटल व्योम leave_handler(पूर्णांक status, काष्ठा ib_sa_mcmember_rec *rec,
			  व्योम *context);

अटल काष्ठा mcast_group *mcast_find(काष्ठा mcast_port *port,
				      जोड़ ib_gid *mgid)
अणु
	काष्ठा rb_node *node = port->table.rb_node;
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

अटल काष्ठा mcast_group *mcast_insert(काष्ठा mcast_port *port,
					काष्ठा mcast_group *group,
					पूर्णांक allow_duplicates)
अणु
	काष्ठा rb_node **link = &port->table.rb_node;
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
		अन्यथा अगर (allow_duplicates)
			link = &(*link)->rb_left;
		अन्यथा
			वापस cur_group;
	पूर्ण
	rb_link_node(&group->node, parent, link);
	rb_insert_color(&group->node, &port->table);
	वापस शून्य;
पूर्ण

अटल व्योम deref_port(काष्ठा mcast_port *port)
अणु
	अगर (atomic_dec_and_test(&port->refcount))
		complete(&port->comp);
पूर्ण

अटल व्योम release_group(काष्ठा mcast_group *group)
अणु
	काष्ठा mcast_port *port = group->port;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	अगर (atomic_dec_and_test(&group->refcount)) अणु
		rb_erase(&group->node, &port->table);
		spin_unlock_irqrestore(&port->lock, flags);
		kमुक्त(group);
		deref_port(port);
	पूर्ण अन्यथा
		spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम deref_member(काष्ठा mcast_member *member)
अणु
	अगर (atomic_dec_and_test(&member->refcount))
		complete(&member->comp);
पूर्ण

अटल व्योम queue_join(काष्ठा mcast_member *member)
अणु
	काष्ठा mcast_group *group = member->group;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&group->lock, flags);
	list_add_tail(&member->list, &group->pending_list);
	अगर (group->state == MCAST_IDLE) अणु
		group->state = MCAST_BUSY;
		atomic_inc(&group->refcount);
		queue_work(mcast_wq, &group->work);
	पूर्ण
	spin_unlock_irqrestore(&group->lock, flags);
पूर्ण

/*
 * A multicast group has four types of members: full member, non member,
 * senकरोnly non member and senकरोnly full member.
 * We need to keep track of the number of members of each
 * type based on their join state.  Adjust the number of members the beदीर्घ to
 * the specअगरied join states.
 */
अटल व्योम adjust_membership(काष्ठा mcast_group *group, u8 join_state, पूर्णांक inc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_JOIN_MEMBERSHIP_TYPES; i++, join_state >>= 1)
		अगर (join_state & 0x1)
			group->members[i] += inc;
पूर्ण

/*
 * If a multicast group has zero members left क्रम a particular join state, but
 * the group is still a member with the SA, we need to leave that join state.
 * Determine which join states we still beदीर्घ to, but that करो not have any
 * active members.
 */
अटल u8 get_leave_state(काष्ठा mcast_group *group)
अणु
	u8 leave_state = 0;
	पूर्णांक i;

	क्रम (i = 0; i < NUM_JOIN_MEMBERSHIP_TYPES; i++)
		अगर (!group->members[i])
			leave_state |= (0x1 << i);

	वापस leave_state & group->rec.join_state;
पूर्ण

अटल पूर्णांक check_selector(ib_sa_comp_mask comp_mask,
			  ib_sa_comp_mask selector_mask,
			  ib_sa_comp_mask value_mask,
			  u8 selector, u8 src_value, u8 dst_value)
अणु
	पूर्णांक err;

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

अटल पूर्णांक cmp_rec(काष्ठा ib_sa_mcmember_rec *src,
		   काष्ठा ib_sa_mcmember_rec *dst, ib_sa_comp_mask comp_mask)
अणु
	/* MGID must alपढ़ोy match */

	अगर (comp_mask & IB_SA_MCMEMBER_REC_PORT_GID &&
	    स_भेद(&src->port_gid, &dst->port_gid, माप src->port_gid))
		वापस -EINVAL;
	अगर (comp_mask & IB_SA_MCMEMBER_REC_QKEY && src->qkey != dst->qkey)
		वापस -EINVAL;
	अगर (comp_mask & IB_SA_MCMEMBER_REC_MLID && src->mlid != dst->mlid)
		वापस -EINVAL;
	अगर (check_selector(comp_mask, IB_SA_MCMEMBER_REC_MTU_SELECTOR,
			   IB_SA_MCMEMBER_REC_MTU, dst->mtu_selector,
			   src->mtu, dst->mtu))
		वापस -EINVAL;
	अगर (comp_mask & IB_SA_MCMEMBER_REC_TRAFFIC_CLASS &&
	    src->traffic_class != dst->traffic_class)
		वापस -EINVAL;
	अगर (comp_mask & IB_SA_MCMEMBER_REC_PKEY && src->pkey != dst->pkey)
		वापस -EINVAL;
	अगर (check_selector(comp_mask, IB_SA_MCMEMBER_REC_RATE_SELECTOR,
			   IB_SA_MCMEMBER_REC_RATE, dst->rate_selector,
			   src->rate, dst->rate))
		वापस -EINVAL;
	अगर (check_selector(comp_mask,
			   IB_SA_MCMEMBER_REC_PACKET_LIFE_TIME_SELECTOR,
			   IB_SA_MCMEMBER_REC_PACKET_LIFE_TIME,
			   dst->packet_lअगरe_समय_selector,
			   src->packet_lअगरe_समय, dst->packet_lअगरe_समय))
		वापस -EINVAL;
	अगर (comp_mask & IB_SA_MCMEMBER_REC_SL && src->sl != dst->sl)
		वापस -EINVAL;
	अगर (comp_mask & IB_SA_MCMEMBER_REC_FLOW_LABEL &&
	    src->flow_label != dst->flow_label)
		वापस -EINVAL;
	अगर (comp_mask & IB_SA_MCMEMBER_REC_HOP_LIMIT &&
	    src->hop_limit != dst->hop_limit)
		वापस -EINVAL;
	अगर (comp_mask & IB_SA_MCMEMBER_REC_SCOPE && src->scope != dst->scope)
		वापस -EINVAL;

	/* join_state checked separately, proxy_join ignored */

	वापस 0;
पूर्ण

अटल पूर्णांक send_join(काष्ठा mcast_group *group, काष्ठा mcast_member *member)
अणु
	काष्ठा mcast_port *port = group->port;
	पूर्णांक ret;

	group->last_join = member;
	ret = ib_sa_mcmember_rec_query(&sa_client, port->dev->device,
				       port->port_num, IB_MGMT_METHOD_SET,
				       &member->multicast.rec,
				       member->multicast.comp_mask,
				       3000, GFP_KERNEL, join_handler, group,
				       &group->query);
	वापस (ret > 0) ? 0 : ret;
पूर्ण

अटल पूर्णांक send_leave(काष्ठा mcast_group *group, u8 leave_state)
अणु
	काष्ठा mcast_port *port = group->port;
	काष्ठा ib_sa_mcmember_rec rec;
	पूर्णांक ret;

	rec = group->rec;
	rec.join_state = leave_state;
	group->leave_state = leave_state;

	ret = ib_sa_mcmember_rec_query(&sa_client, port->dev->device,
				       port->port_num, IB_SA_METHOD_DELETE, &rec,
				       IB_SA_MCMEMBER_REC_MGID     |
				       IB_SA_MCMEMBER_REC_PORT_GID |
				       IB_SA_MCMEMBER_REC_JOIN_STATE,
				       3000, GFP_KERNEL, leave_handler,
				       group, &group->query);
	वापस (ret > 0) ? 0 : ret;
पूर्ण

अटल व्योम join_group(काष्ठा mcast_group *group, काष्ठा mcast_member *member,
		       u8 join_state)
अणु
	member->state = MCAST_MEMBER;
	adjust_membership(group, join_state, 1);
	group->rec.join_state |= join_state;
	member->multicast.rec = group->rec;
	member->multicast.rec.join_state = join_state;
	list_move(&member->list, &group->active_list);
पूर्ण

अटल पूर्णांक fail_join(काष्ठा mcast_group *group, काष्ठा mcast_member *member,
		     पूर्णांक status)
अणु
	spin_lock_irq(&group->lock);
	list_del_init(&member->list);
	spin_unlock_irq(&group->lock);
	वापस member->multicast.callback(status, &member->multicast);
पूर्ण

अटल व्योम process_group_error(काष्ठा mcast_group *group)
अणु
	काष्ठा mcast_member *member;
	पूर्णांक ret = 0;
	u16 pkey_index;

	अगर (group->state == MCAST_PKEY_EVENT)
		ret = ib_find_pkey(group->port->dev->device,
				   group->port->port_num,
				   be16_to_cpu(group->rec.pkey), &pkey_index);

	spin_lock_irq(&group->lock);
	अगर (group->state == MCAST_PKEY_EVENT && !ret &&
	    group->pkey_index == pkey_index)
		जाओ out;

	जबतक (!list_empty(&group->active_list)) अणु
		member = list_entry(group->active_list.next,
				    काष्ठा mcast_member, list);
		atomic_inc(&member->refcount);
		list_del_init(&member->list);
		adjust_membership(group, member->multicast.rec.join_state, -1);
		member->state = MCAST_ERROR;
		spin_unlock_irq(&group->lock);

		ret = member->multicast.callback(-ENETRESET,
						 &member->multicast);
		deref_member(member);
		अगर (ret)
			ib_sa_मुक्त_multicast(&member->multicast);
		spin_lock_irq(&group->lock);
	पूर्ण

	group->rec.join_state = 0;
out:
	group->state = MCAST_BUSY;
	spin_unlock_irq(&group->lock);
पूर्ण

अटल व्योम mcast_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mcast_group *group;
	काष्ठा mcast_member *member;
	काष्ठा ib_sa_multicast *multicast;
	पूर्णांक status, ret;
	u8 join_state;

	group = container_of(work, typeof(*group), work);
retest:
	spin_lock_irq(&group->lock);
	जबतक (!list_empty(&group->pending_list) ||
	       (group->state != MCAST_BUSY)) अणु

		अगर (group->state != MCAST_BUSY) अणु
			spin_unlock_irq(&group->lock);
			process_group_error(group);
			जाओ retest;
		पूर्ण

		member = list_entry(group->pending_list.next,
				    काष्ठा mcast_member, list);
		multicast = &member->multicast;
		join_state = multicast->rec.join_state;
		atomic_inc(&member->refcount);

		अगर (join_state == (group->rec.join_state & join_state)) अणु
			status = cmp_rec(&group->rec, &multicast->rec,
					 multicast->comp_mask);
			अगर (!status)
				join_group(group, member, join_state);
			अन्यथा
				list_del_init(&member->list);
			spin_unlock_irq(&group->lock);
			ret = multicast->callback(status, multicast);
		पूर्ण अन्यथा अणु
			spin_unlock_irq(&group->lock);
			status = send_join(group, member);
			अगर (!status) अणु
				deref_member(member);
				वापस;
			पूर्ण
			ret = fail_join(group, member, status);
		पूर्ण

		deref_member(member);
		अगर (ret)
			ib_sa_मुक्त_multicast(&member->multicast);
		spin_lock_irq(&group->lock);
	पूर्ण

	join_state = get_leave_state(group);
	अगर (join_state) अणु
		group->rec.join_state &= ~join_state;
		spin_unlock_irq(&group->lock);
		अगर (send_leave(group, join_state))
			जाओ retest;
	पूर्ण अन्यथा अणु
		group->state = MCAST_IDLE;
		spin_unlock_irq(&group->lock);
		release_group(group);
	पूर्ण
पूर्ण

/*
 * Fail a join request अगर it is still active - at the head of the pending queue.
 */
अटल व्योम process_join_error(काष्ठा mcast_group *group, पूर्णांक status)
अणु
	काष्ठा mcast_member *member;
	पूर्णांक ret;

	spin_lock_irq(&group->lock);
	member = list_entry(group->pending_list.next,
			    काष्ठा mcast_member, list);
	अगर (group->last_join == member) अणु
		atomic_inc(&member->refcount);
		list_del_init(&member->list);
		spin_unlock_irq(&group->lock);
		ret = member->multicast.callback(status, &member->multicast);
		deref_member(member);
		अगर (ret)
			ib_sa_मुक्त_multicast(&member->multicast);
	पूर्ण अन्यथा
		spin_unlock_irq(&group->lock);
पूर्ण

अटल व्योम join_handler(पूर्णांक status, काष्ठा ib_sa_mcmember_rec *rec,
			 व्योम *context)
अणु
	काष्ठा mcast_group *group = context;
	u16 pkey_index = MCAST_INVALID_PKEY_INDEX;

	अगर (status)
		process_join_error(group, status);
	अन्यथा अणु
		पूर्णांक mgids_changed, is_mgid0;

		अगर (ib_find_pkey(group->port->dev->device,
				 group->port->port_num, be16_to_cpu(rec->pkey),
				 &pkey_index))
			pkey_index = MCAST_INVALID_PKEY_INDEX;

		spin_lock_irq(&group->port->lock);
		अगर (group->state == MCAST_BUSY &&
		    group->pkey_index == MCAST_INVALID_PKEY_INDEX)
			group->pkey_index = pkey_index;
		mgids_changed = स_भेद(&rec->mgid, &group->rec.mgid,
				       माप(group->rec.mgid));
		group->rec = *rec;
		अगर (mgids_changed) अणु
			rb_erase(&group->node, &group->port->table);
			is_mgid0 = !स_भेद(&mgid0, &group->rec.mgid,
					   माप(mgid0));
			mcast_insert(group->port, group, is_mgid0);
		पूर्ण
		spin_unlock_irq(&group->port->lock);
	पूर्ण
	mcast_work_handler(&group->work);
पूर्ण

अटल व्योम leave_handler(पूर्णांक status, काष्ठा ib_sa_mcmember_rec *rec,
			  व्योम *context)
अणु
	काष्ठा mcast_group *group = context;

	अगर (status && group->retries > 0 &&
	    !send_leave(group, group->leave_state))
		group->retries--;
	अन्यथा
		mcast_work_handler(&group->work);
पूर्ण

अटल काष्ठा mcast_group *acquire_group(काष्ठा mcast_port *port,
					 जोड़ ib_gid *mgid, gfp_t gfp_mask)
अणु
	काष्ठा mcast_group *group, *cur_group;
	अचिन्हित दीर्घ flags;
	पूर्णांक is_mgid0;

	is_mgid0 = !स_भेद(&mgid0, mgid, माप mgid0);
	अगर (!is_mgid0) अणु
		spin_lock_irqsave(&port->lock, flags);
		group = mcast_find(port, mgid);
		अगर (group)
			जाओ found;
		spin_unlock_irqrestore(&port->lock, flags);
	पूर्ण

	group = kzalloc(माप *group, gfp_mask);
	अगर (!group)
		वापस शून्य;

	group->retries = 3;
	group->port = port;
	group->rec.mgid = *mgid;
	group->pkey_index = MCAST_INVALID_PKEY_INDEX;
	INIT_LIST_HEAD(&group->pending_list);
	INIT_LIST_HEAD(&group->active_list);
	INIT_WORK(&group->work, mcast_work_handler);
	spin_lock_init(&group->lock);

	spin_lock_irqsave(&port->lock, flags);
	cur_group = mcast_insert(port, group, is_mgid0);
	अगर (cur_group) अणु
		kमुक्त(group);
		group = cur_group;
	पूर्ण अन्यथा
		atomic_inc(&port->refcount);
found:
	atomic_inc(&group->refcount);
	spin_unlock_irqrestore(&port->lock, flags);
	वापस group;
पूर्ण

/*
 * We serialize all join requests to a single group to make our lives much
 * easier.  Otherwise, two users could try to join the same group
 * simultaneously, with dअगरferent configurations, one could leave जबतक the
 * join is in progress, etc., which makes locking around error recovery
 * dअगरficult.
 */
काष्ठा ib_sa_multicast *
ib_sa_join_multicast(काष्ठा ib_sa_client *client,
		     काष्ठा ib_device *device, u32 port_num,
		     काष्ठा ib_sa_mcmember_rec *rec,
		     ib_sa_comp_mask comp_mask, gfp_t gfp_mask,
		     पूर्णांक (*callback)(पूर्णांक status,
				     काष्ठा ib_sa_multicast *multicast),
		     व्योम *context)
अणु
	काष्ठा mcast_device *dev;
	काष्ठा mcast_member *member;
	काष्ठा ib_sa_multicast *multicast;
	पूर्णांक ret;

	dev = ib_get_client_data(device, &mcast_client);
	अगर (!dev)
		वापस ERR_PTR(-ENODEV);

	member = kदो_स्मृति(माप *member, gfp_mask);
	अगर (!member)
		वापस ERR_PTR(-ENOMEM);

	ib_sa_client_get(client);
	member->client = client;
	member->multicast.rec = *rec;
	member->multicast.comp_mask = comp_mask;
	member->multicast.callback = callback;
	member->multicast.context = context;
	init_completion(&member->comp);
	atomic_set(&member->refcount, 1);
	member->state = MCAST_JOINING;

	member->group = acquire_group(&dev->port[port_num - dev->start_port],
				      &rec->mgid, gfp_mask);
	अगर (!member->group) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	/*
	 * The user will get the multicast काष्ठाure in their callback.  They
	 * could then मुक्त the multicast काष्ठाure beक्रमe we can वापस from
	 * this routine.  So we save the poपूर्णांकer to वापस beक्रमe queuing
	 * any callback.
	 */
	multicast = &member->multicast;
	queue_join(member);
	वापस multicast;

err:
	ib_sa_client_put(client);
	kमुक्त(member);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL(ib_sa_join_multicast);

व्योम ib_sa_मुक्त_multicast(काष्ठा ib_sa_multicast *multicast)
अणु
	काष्ठा mcast_member *member;
	काष्ठा mcast_group *group;

	member = container_of(multicast, काष्ठा mcast_member, multicast);
	group = member->group;

	spin_lock_irq(&group->lock);
	अगर (member->state == MCAST_MEMBER)
		adjust_membership(group, multicast->rec.join_state, -1);

	list_del_init(&member->list);

	अगर (group->state == MCAST_IDLE) अणु
		group->state = MCAST_BUSY;
		spin_unlock_irq(&group->lock);
		/* Continue to hold reference on group until callback */
		queue_work(mcast_wq, &group->work);
	पूर्ण अन्यथा अणु
		spin_unlock_irq(&group->lock);
		release_group(group);
	पूर्ण

	deref_member(member);
	रुको_क्रम_completion(&member->comp);
	ib_sa_client_put(member->client);
	kमुक्त(member);
पूर्ण
EXPORT_SYMBOL(ib_sa_मुक्त_multicast);

पूर्णांक ib_sa_get_mcmember_rec(काष्ठा ib_device *device, u32 port_num,
			   जोड़ ib_gid *mgid, काष्ठा ib_sa_mcmember_rec *rec)
अणु
	काष्ठा mcast_device *dev;
	काष्ठा mcast_port *port;
	काष्ठा mcast_group *group;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	dev = ib_get_client_data(device, &mcast_client);
	अगर (!dev)
		वापस -ENODEV;

	port = &dev->port[port_num - dev->start_port];
	spin_lock_irqsave(&port->lock, flags);
	group = mcast_find(port, mgid);
	अगर (group)
		*rec = group->rec;
	अन्यथा
		ret = -EADDRNOTAVAIL;
	spin_unlock_irqrestore(&port->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_sa_get_mcmember_rec);

/**
 * ib_init_ah_from_mcmember - Initialize AH attribute from multicast
 * member record and gid of the device.
 * @device:	RDMA device
 * @port_num:	Port of the rdma device to consider
 * @rec:	Multicast member record to use
 * @ndev:	Optional netdevice, applicable only क्रम RoCE
 * @gid_type:	GID type to consider
 * @ah_attr:	AH attribute to fillup on successful completion
 *
 * ib_init_ah_from_mcmember() initializes AH attribute based on multicast
 * member record and other device properties. On success the caller is
 * responsible to call rdma_destroy_ah_attr on the ah_attr. Returns 0 on
 * success or appropriate error code.
 *
 */
पूर्णांक ib_init_ah_from_mcmember(काष्ठा ib_device *device, u32 port_num,
			     काष्ठा ib_sa_mcmember_rec *rec,
			     काष्ठा net_device *ndev,
			     क्रमागत ib_gid_type gid_type,
			     काष्ठा rdma_ah_attr *ah_attr)
अणु
	स्थिर काष्ठा ib_gid_attr *sgid_attr;

	/* GID table is not based on the netdevice क्रम IB link layer,
	 * so ignore ndev during search.
	 */
	अगर (rdma_protocol_ib(device, port_num))
		ndev = शून्य;
	अन्यथा अगर (!rdma_protocol_roce(device, port_num))
		वापस -EINVAL;

	sgid_attr = rdma_find_gid_by_port(device, &rec->port_gid,
					  gid_type, port_num, ndev);
	अगर (IS_ERR(sgid_attr))
		वापस PTR_ERR(sgid_attr);

	स_रखो(ah_attr, 0, माप(*ah_attr));
	ah_attr->type = rdma_ah_find_type(device, port_num);

	rdma_ah_set_dlid(ah_attr, be16_to_cpu(rec->mlid));
	rdma_ah_set_sl(ah_attr, rec->sl);
	rdma_ah_set_port_num(ah_attr, port_num);
	rdma_ah_set_अटल_rate(ah_attr, rec->rate);
	rdma_move_grh_sgid_attr(ah_attr, &rec->mgid,
				be32_to_cpu(rec->flow_label),
				rec->hop_limit,	rec->traffic_class,
				sgid_attr);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ib_init_ah_from_mcmember);

अटल व्योम mcast_groups_event(काष्ठा mcast_port *port,
			       क्रमागत mcast_group_state state)
अणु
	काष्ठा mcast_group *group;
	काष्ठा rb_node *node;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	क्रम (node = rb_first(&port->table); node; node = rb_next(node)) अणु
		group = rb_entry(node, काष्ठा mcast_group, node);
		spin_lock(&group->lock);
		अगर (group->state == MCAST_IDLE) अणु
			atomic_inc(&group->refcount);
			queue_work(mcast_wq, &group->work);
		पूर्ण
		अगर (group->state != MCAST_GROUP_ERROR)
			group->state = state;
		spin_unlock(&group->lock);
	पूर्ण
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम mcast_event_handler(काष्ठा ib_event_handler *handler,
				काष्ठा ib_event *event)
अणु
	काष्ठा mcast_device *dev;
	पूर्णांक index;

	dev = container_of(handler, काष्ठा mcast_device, event_handler);
	अगर (!rdma_cap_ib_mcast(dev->device, event->element.port_num))
		वापस;

	index = event->element.port_num - dev->start_port;

	चयन (event->event) अणु
	हाल IB_EVENT_PORT_ERR:
	हाल IB_EVENT_LID_CHANGE:
	हाल IB_EVENT_CLIENT_REREGISTER:
		mcast_groups_event(&dev->port[index], MCAST_GROUP_ERROR);
		अवरोध;
	हाल IB_EVENT_PKEY_CHANGE:
		mcast_groups_event(&dev->port[index], MCAST_PKEY_EVENT);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक mcast_add_one(काष्ठा ib_device *device)
अणु
	काष्ठा mcast_device *dev;
	काष्ठा mcast_port *port;
	पूर्णांक i;
	पूर्णांक count = 0;

	dev = kदो_स्मृति(काष्ठा_size(dev, port, device->phys_port_cnt),
		      GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dev->start_port = rdma_start_port(device);
	dev->end_port = rdma_end_port(device);

	क्रम (i = 0; i <= dev->end_port - dev->start_port; i++) अणु
		अगर (!rdma_cap_ib_mcast(device, dev->start_port + i))
			जारी;
		port = &dev->port[i];
		port->dev = dev;
		port->port_num = dev->start_port + i;
		spin_lock_init(&port->lock);
		port->table = RB_ROOT;
		init_completion(&port->comp);
		atomic_set(&port->refcount, 1);
		++count;
	पूर्ण

	अगर (!count) अणु
		kमुक्त(dev);
		वापस -EOPNOTSUPP;
	पूर्ण

	dev->device = device;
	ib_set_client_data(device, &mcast_client, dev);

	INIT_IB_EVENT_HANDLER(&dev->event_handler, device, mcast_event_handler);
	ib_रेजिस्टर_event_handler(&dev->event_handler);
	वापस 0;
पूर्ण

अटल व्योम mcast_हटाओ_one(काष्ठा ib_device *device, व्योम *client_data)
अणु
	काष्ठा mcast_device *dev = client_data;
	काष्ठा mcast_port *port;
	पूर्णांक i;

	ib_unरेजिस्टर_event_handler(&dev->event_handler);
	flush_workqueue(mcast_wq);

	क्रम (i = 0; i <= dev->end_port - dev->start_port; i++) अणु
		अगर (rdma_cap_ib_mcast(device, dev->start_port + i)) अणु
			port = &dev->port[i];
			deref_port(port);
			रुको_क्रम_completion(&port->comp);
		पूर्ण
	पूर्ण

	kमुक्त(dev);
पूर्ण

पूर्णांक mcast_init(व्योम)
अणु
	पूर्णांक ret;

	mcast_wq = alloc_ordered_workqueue("ib_mcast", WQ_MEM_RECLAIM);
	अगर (!mcast_wq)
		वापस -ENOMEM;

	ib_sa_रेजिस्टर_client(&sa_client);

	ret = ib_रेजिस्टर_client(&mcast_client);
	अगर (ret)
		जाओ err;
	वापस 0;

err:
	ib_sa_unरेजिस्टर_client(&sa_client);
	destroy_workqueue(mcast_wq);
	वापस ret;
पूर्ण

व्योम mcast_cleanup(व्योम)
अणु
	ib_unरेजिस्टर_client(&mcast_client);
	ib_sa_unरेजिस्टर_client(&sa_client);
	destroy_workqueue(mcast_wq);
पूर्ण
