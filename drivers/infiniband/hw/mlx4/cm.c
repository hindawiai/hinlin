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

#समावेश <linux/mlx4/cmd.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/idr.h>
#समावेश <rdma/ib_cm.h>

#समावेश "mlx4_ib.h"

#घोषणा CM_CLEANUP_CACHE_TIMEOUT  (30 * HZ)

काष्ठा id_map_entry अणु
	काष्ठा rb_node node;

	u32 sl_cm_id;
	u32 pv_cm_id;
	पूर्णांक slave_id;
	पूर्णांक scheduled_delete;
	काष्ठा mlx4_ib_dev *dev;

	काष्ठा list_head list;
	काष्ठा delayed_work समयout;
पूर्ण;

काष्ठा rej_पंचांगout_entry अणु
	पूर्णांक slave;
	u32 rem_pv_cm_id;
	काष्ठा delayed_work समयout;
	काष्ठा xarray *xa_rej_पंचांगout;
पूर्ण;

काष्ठा cm_generic_msg अणु
	काष्ठा ib_mad_hdr hdr;

	__be32 local_comm_id;
	__be32 remote_comm_id;
	अचिन्हित अक्षर unused[2];
	__be16 rej_reason;
पूर्ण;

काष्ठा cm_sidr_generic_msg अणु
	काष्ठा ib_mad_hdr hdr;
	__be32 request_id;
पूर्ण;

काष्ठा cm_req_msg अणु
	अचिन्हित अक्षर unused[0x60];
	जोड़ ib_gid primary_path_sgid;
पूर्ण;


अटल व्योम set_local_comm_id(काष्ठा ib_mad *mad, u32 cm_id)
अणु
	अगर (mad->mad_hdr.attr_id == CM_SIDR_REQ_ATTR_ID) अणु
		काष्ठा cm_sidr_generic_msg *msg =
			(काष्ठा cm_sidr_generic_msg *)mad;
		msg->request_id = cpu_to_be32(cm_id);
	पूर्ण अन्यथा अगर (mad->mad_hdr.attr_id == CM_SIDR_REP_ATTR_ID) अणु
		pr_err("trying to set local_comm_id in SIDR_REP\n");
		वापस;
	पूर्ण अन्यथा अणु
		काष्ठा cm_generic_msg *msg = (काष्ठा cm_generic_msg *)mad;
		msg->local_comm_id = cpu_to_be32(cm_id);
	पूर्ण
पूर्ण

अटल u32 get_local_comm_id(काष्ठा ib_mad *mad)
अणु
	अगर (mad->mad_hdr.attr_id == CM_SIDR_REQ_ATTR_ID) अणु
		काष्ठा cm_sidr_generic_msg *msg =
			(काष्ठा cm_sidr_generic_msg *)mad;
		वापस be32_to_cpu(msg->request_id);
	पूर्ण अन्यथा अगर (mad->mad_hdr.attr_id == CM_SIDR_REP_ATTR_ID) अणु
		pr_err("trying to set local_comm_id in SIDR_REP\n");
		वापस -1;
	पूर्ण अन्यथा अणु
		काष्ठा cm_generic_msg *msg = (काष्ठा cm_generic_msg *)mad;
		वापस be32_to_cpu(msg->local_comm_id);
	पूर्ण
पूर्ण

अटल व्योम set_remote_comm_id(काष्ठा ib_mad *mad, u32 cm_id)
अणु
	अगर (mad->mad_hdr.attr_id == CM_SIDR_REP_ATTR_ID) अणु
		काष्ठा cm_sidr_generic_msg *msg =
			(काष्ठा cm_sidr_generic_msg *)mad;
		msg->request_id = cpu_to_be32(cm_id);
	पूर्ण अन्यथा अगर (mad->mad_hdr.attr_id == CM_SIDR_REQ_ATTR_ID) अणु
		pr_err("trying to set remote_comm_id in SIDR_REQ\n");
		वापस;
	पूर्ण अन्यथा अणु
		काष्ठा cm_generic_msg *msg = (काष्ठा cm_generic_msg *)mad;
		msg->remote_comm_id = cpu_to_be32(cm_id);
	पूर्ण
पूर्ण

अटल u32 get_remote_comm_id(काष्ठा ib_mad *mad)
अणु
	अगर (mad->mad_hdr.attr_id == CM_SIDR_REP_ATTR_ID) अणु
		काष्ठा cm_sidr_generic_msg *msg =
			(काष्ठा cm_sidr_generic_msg *)mad;
		वापस be32_to_cpu(msg->request_id);
	पूर्ण अन्यथा अगर (mad->mad_hdr.attr_id == CM_SIDR_REQ_ATTR_ID) अणु
		pr_err("trying to set remote_comm_id in SIDR_REQ\n");
		वापस -1;
	पूर्ण अन्यथा अणु
		काष्ठा cm_generic_msg *msg = (काष्ठा cm_generic_msg *)mad;
		वापस be32_to_cpu(msg->remote_comm_id);
	पूर्ण
पूर्ण

अटल जोड़ ib_gid gid_from_req_msg(काष्ठा ib_device *ibdev, काष्ठा ib_mad *mad)
अणु
	काष्ठा cm_req_msg *msg = (काष्ठा cm_req_msg *)mad;

	वापस msg->primary_path_sgid;
पूर्ण

/* Lock should be taken beक्रमe called */
अटल काष्ठा id_map_entry *
id_map_find_by_sl_id(काष्ठा ib_device *ibdev, u32 slave_id, u32 sl_cm_id)
अणु
	काष्ठा rb_root *sl_id_map = &to_mdev(ibdev)->sriov.sl_id_map;
	काष्ठा rb_node *node = sl_id_map->rb_node;

	जबतक (node) अणु
		काष्ठा id_map_entry *id_map_entry =
			rb_entry(node, काष्ठा id_map_entry, node);

		अगर (id_map_entry->sl_cm_id > sl_cm_id)
			node = node->rb_left;
		अन्यथा अगर (id_map_entry->sl_cm_id < sl_cm_id)
			node = node->rb_right;
		अन्यथा अगर (id_map_entry->slave_id > slave_id)
			node = node->rb_left;
		अन्यथा अगर (id_map_entry->slave_id < slave_id)
			node = node->rb_right;
		अन्यथा
			वापस id_map_entry;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम id_map_ent_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delay = to_delayed_work(work);
	काष्ठा id_map_entry *ent = container_of(delay, काष्ठा id_map_entry, समयout);
	काष्ठा id_map_entry *found_ent;
	काष्ठा mlx4_ib_dev *dev = ent->dev;
	काष्ठा mlx4_ib_sriov *sriov = &dev->sriov;
	काष्ठा rb_root *sl_id_map = &sriov->sl_id_map;

	spin_lock(&sriov->id_map_lock);
	अगर (!xa_erase(&sriov->pv_id_table, ent->pv_cm_id))
		जाओ out;
	found_ent = id_map_find_by_sl_id(&dev->ib_dev, ent->slave_id, ent->sl_cm_id);
	अगर (found_ent && found_ent == ent)
		rb_erase(&found_ent->node, sl_id_map);

out:
	list_del(&ent->list);
	spin_unlock(&sriov->id_map_lock);
	kमुक्त(ent);
पूर्ण

अटल व्योम sl_id_map_add(काष्ठा ib_device *ibdev, काष्ठा id_map_entry *new)
अणु
	काष्ठा rb_root *sl_id_map = &to_mdev(ibdev)->sriov.sl_id_map;
	काष्ठा rb_node **link = &sl_id_map->rb_node, *parent = शून्य;
	काष्ठा id_map_entry *ent;
	पूर्णांक slave_id = new->slave_id;
	पूर्णांक sl_cm_id = new->sl_cm_id;

	ent = id_map_find_by_sl_id(ibdev, slave_id, sl_cm_id);
	अगर (ent) अणु
		pr_debug("overriding existing sl_id_map entry (cm_id = %x)\n",
			 sl_cm_id);

		rb_replace_node(&ent->node, &new->node, sl_id_map);
		वापस;
	पूर्ण

	/* Go to the bottom of the tree */
	जबतक (*link) अणु
		parent = *link;
		ent = rb_entry(parent, काष्ठा id_map_entry, node);

		अगर (ent->sl_cm_id > sl_cm_id || (ent->sl_cm_id == sl_cm_id && ent->slave_id > slave_id))
			link = &(*link)->rb_left;
		अन्यथा
			link = &(*link)->rb_right;
	पूर्ण

	rb_link_node(&new->node, parent, link);
	rb_insert_color(&new->node, sl_id_map);
पूर्ण

अटल काष्ठा id_map_entry *
id_map_alloc(काष्ठा ib_device *ibdev, पूर्णांक slave_id, u32 sl_cm_id)
अणु
	पूर्णांक ret;
	काष्ठा id_map_entry *ent;
	काष्ठा mlx4_ib_sriov *sriov = &to_mdev(ibdev)->sriov;

	ent = kदो_स्मृति(माप (काष्ठा id_map_entry), GFP_KERNEL);
	अगर (!ent)
		वापस ERR_PTR(-ENOMEM);

	ent->sl_cm_id = sl_cm_id;
	ent->slave_id = slave_id;
	ent->scheduled_delete = 0;
	ent->dev = to_mdev(ibdev);
	INIT_DELAYED_WORK(&ent->समयout, id_map_ent_समयout);

	ret = xa_alloc_cyclic(&sriov->pv_id_table, &ent->pv_cm_id, ent,
			xa_limit_32b, &sriov->pv_id_next, GFP_KERNEL);
	अगर (ret >= 0) अणु
		spin_lock(&sriov->id_map_lock);
		sl_id_map_add(ibdev, ent);
		list_add_tail(&ent->list, &sriov->cm_list);
		spin_unlock(&sriov->id_map_lock);
		वापस ent;
	पूर्ण

	/*error flow*/
	kमुक्त(ent);
	mlx4_ib_warn(ibdev, "Allocation failed (err:0x%x)\n", ret);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल काष्ठा id_map_entry *
id_map_get(काष्ठा ib_device *ibdev, पूर्णांक *pv_cm_id, पूर्णांक slave_id, पूर्णांक sl_cm_id)
अणु
	काष्ठा id_map_entry *ent;
	काष्ठा mlx4_ib_sriov *sriov = &to_mdev(ibdev)->sriov;

	spin_lock(&sriov->id_map_lock);
	अगर (*pv_cm_id == -1) अणु
		ent = id_map_find_by_sl_id(ibdev, slave_id, sl_cm_id);
		अगर (ent)
			*pv_cm_id = (पूर्णांक) ent->pv_cm_id;
	पूर्ण अन्यथा
		ent = xa_load(&sriov->pv_id_table, *pv_cm_id);
	spin_unlock(&sriov->id_map_lock);

	वापस ent;
पूर्ण

अटल व्योम schedule_delayed(काष्ठा ib_device *ibdev, काष्ठा id_map_entry *id)
अणु
	काष्ठा mlx4_ib_sriov *sriov = &to_mdev(ibdev)->sriov;
	अचिन्हित दीर्घ flags;

	spin_lock(&sriov->id_map_lock);
	spin_lock_irqsave(&sriov->going_करोwn_lock, flags);
	/*make sure that there is no schedule inside the scheduled work.*/
	अगर (!sriov->is_going_करोwn && !id->scheduled_delete) अणु
		id->scheduled_delete = 1;
		schedule_delayed_work(&id->समयout, CM_CLEANUP_CACHE_TIMEOUT);
	पूर्ण अन्यथा अगर (id->scheduled_delete) अणु
		/* Adjust समयout अगर alपढ़ोy scheduled */
		mod_delayed_work(प्रणाली_wq, &id->समयout, CM_CLEANUP_CACHE_TIMEOUT);
	पूर्ण
	spin_unlock_irqrestore(&sriov->going_करोwn_lock, flags);
	spin_unlock(&sriov->id_map_lock);
पूर्ण

#घोषणा REJ_REASON(m) be16_to_cpu(((काष्ठा cm_generic_msg *)(m))->rej_reason)
पूर्णांक mlx4_ib_multiplex_cm_handler(काष्ठा ib_device *ibdev, पूर्णांक port, पूर्णांक slave_id,
		काष्ठा ib_mad *mad)
अणु
	काष्ठा id_map_entry *id;
	u32 sl_cm_id;
	पूर्णांक pv_cm_id = -1;

	अगर (mad->mad_hdr.attr_id == CM_REQ_ATTR_ID ||
	    mad->mad_hdr.attr_id == CM_REP_ATTR_ID ||
	    mad->mad_hdr.attr_id == CM_MRA_ATTR_ID ||
	    mad->mad_hdr.attr_id == CM_SIDR_REQ_ATTR_ID ||
	    (mad->mad_hdr.attr_id == CM_REJ_ATTR_ID && REJ_REASON(mad) == IB_CM_REJ_TIMEOUT)) अणु
		sl_cm_id = get_local_comm_id(mad);
		id = id_map_get(ibdev, &pv_cm_id, slave_id, sl_cm_id);
		अगर (id)
			जाओ cont;
		id = id_map_alloc(ibdev, slave_id, sl_cm_id);
		अगर (IS_ERR(id)) अणु
			mlx4_ib_warn(ibdev, "%s: id{slave: %d, sl_cm_id: 0x%x} Failed to id_map_alloc\n",
				__func__, slave_id, sl_cm_id);
			वापस PTR_ERR(id);
		पूर्ण
	पूर्ण अन्यथा अगर (mad->mad_hdr.attr_id == CM_REJ_ATTR_ID ||
		   mad->mad_hdr.attr_id == CM_SIDR_REP_ATTR_ID) अणु
		वापस 0;
	पूर्ण अन्यथा अणु
		sl_cm_id = get_local_comm_id(mad);
		id = id_map_get(ibdev, &pv_cm_id, slave_id, sl_cm_id);
	पूर्ण

	अगर (!id) अणु
		pr_debug("id{slave: %d, sl_cm_id: 0x%x} is NULL! attr_id: 0x%x\n",
			 slave_id, sl_cm_id, be16_to_cpu(mad->mad_hdr.attr_id));
		वापस -EINVAL;
	पूर्ण

cont:
	set_local_comm_id(mad, id->pv_cm_id);

	अगर (mad->mad_hdr.attr_id == CM_DREQ_ATTR_ID)
		schedule_delayed(ibdev, id);
	वापस 0;
पूर्ण

अटल व्योम rej_पंचांगout_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delay = to_delayed_work(work);
	काष्ठा rej_पंचांगout_entry *item = container_of(delay, काष्ठा rej_पंचांगout_entry, समयout);
	काष्ठा rej_पंचांगout_entry *deleted;

	deleted = xa_cmpxchg(item->xa_rej_पंचांगout, item->rem_pv_cm_id, item, शून्य, 0);

	अगर (deleted != item)
		pr_debug("deleted(%p) != item(%p)\n", deleted, item);

	kमुक्त(item);
पूर्ण

अटल पूर्णांक alloc_rej_पंचांगout(काष्ठा mlx4_ib_sriov *sriov, u32 rem_pv_cm_id, पूर्णांक slave)
अणु
	काष्ठा rej_पंचांगout_entry *item;
	काष्ठा rej_पंचांगout_entry *old;
	पूर्णांक ret = 0;

	xa_lock(&sriov->xa_rej_पंचांगout);
	item = xa_load(&sriov->xa_rej_पंचांगout, (अचिन्हित दीर्घ)rem_pv_cm_id);

	अगर (item) अणु
		अगर (xa_err(item))
			ret =  xa_err(item);
		अन्यथा
			/* If a retry, adjust delayed work */
			mod_delayed_work(प्रणाली_wq, &item->समयout, CM_CLEANUP_CACHE_TIMEOUT);
		जाओ err_or_exists;
	पूर्ण
	xa_unlock(&sriov->xa_rej_पंचांगout);

	item = kदो_स्मृति(माप(*item), GFP_KERNEL);
	अगर (!item)
		वापस -ENOMEM;

	INIT_DELAYED_WORK(&item->समयout, rej_पंचांगout_समयout);
	item->slave = slave;
	item->rem_pv_cm_id = rem_pv_cm_id;
	item->xa_rej_पंचांगout = &sriov->xa_rej_पंचांगout;

	old = xa_cmpxchg(&sriov->xa_rej_पंचांगout, (अचिन्हित दीर्घ)rem_pv_cm_id, शून्य, item, GFP_KERNEL);
	अगर (old) अणु
		pr_debug(
			"Non-null old entry (%p) or error (%d) when inserting\n",
			old, xa_err(old));
		kमुक्त(item);
		वापस xa_err(old);
	पूर्ण

	schedule_delayed_work(&item->समयout, CM_CLEANUP_CACHE_TIMEOUT);

	वापस 0;

err_or_exists:
	xa_unlock(&sriov->xa_rej_पंचांगout);
	वापस ret;
पूर्ण

अटल पूर्णांक lookup_rej_पंचांगout_slave(काष्ठा mlx4_ib_sriov *sriov, u32 rem_pv_cm_id)
अणु
	काष्ठा rej_पंचांगout_entry *item;
	पूर्णांक slave;

	xa_lock(&sriov->xa_rej_पंचांगout);
	item = xa_load(&sriov->xa_rej_पंचांगout, (अचिन्हित दीर्घ)rem_pv_cm_id);

	अगर (!item || xa_err(item)) अणु
		pr_debug("Could not find slave. rem_pv_cm_id 0x%x error: %d\n",
			 rem_pv_cm_id, xa_err(item));
		slave = !item ? -ENOENT : xa_err(item);
	पूर्ण अन्यथा अणु
		slave = item->slave;
	पूर्ण
	xa_unlock(&sriov->xa_rej_पंचांगout);

	वापस slave;
पूर्ण

पूर्णांक mlx4_ib_demux_cm_handler(काष्ठा ib_device *ibdev, पूर्णांक port, पूर्णांक *slave,
			     काष्ठा ib_mad *mad)
अणु
	काष्ठा mlx4_ib_sriov *sriov = &to_mdev(ibdev)->sriov;
	u32 rem_pv_cm_id = get_local_comm_id(mad);
	u32 pv_cm_id;
	काष्ठा id_map_entry *id;
	पूर्णांक sts;

	अगर (mad->mad_hdr.attr_id == CM_REQ_ATTR_ID ||
	    mad->mad_hdr.attr_id == CM_SIDR_REQ_ATTR_ID) अणु
		जोड़ ib_gid gid;

		अगर (!slave)
			वापस 0;

		gid = gid_from_req_msg(ibdev, mad);
		*slave = mlx4_ib_find_real_gid(ibdev, port, gid.global.पूर्णांकerface_id);
		अगर (*slave < 0) अणु
			mlx4_ib_warn(ibdev, "failed matching slave_id by gid (0x%llx)\n",
				     be64_to_cpu(gid.global.पूर्णांकerface_id));
			वापस -ENOENT;
		पूर्ण

		sts = alloc_rej_पंचांगout(sriov, rem_pv_cm_id, *slave);
		अगर (sts)
			/* Even अगर this fails, we pass on the REQ to the slave */
			pr_debug("Could not allocate rej_tmout entry. rem_pv_cm_id 0x%x slave %d status %d\n",
				 rem_pv_cm_id, *slave, sts);

		वापस 0;
	पूर्ण

	pv_cm_id = get_remote_comm_id(mad);
	id = id_map_get(ibdev, (पूर्णांक *)&pv_cm_id, -1, -1);

	अगर (!id) अणु
		अगर (mad->mad_hdr.attr_id == CM_REJ_ATTR_ID &&
		    REJ_REASON(mad) == IB_CM_REJ_TIMEOUT && slave) अणु
			*slave = lookup_rej_पंचांगout_slave(sriov, rem_pv_cm_id);

			वापस (*slave < 0) ? *slave : 0;
		पूर्ण
		pr_debug("Couldn't find an entry for pv_cm_id 0x%x, attr_id 0x%x\n",
			 pv_cm_id, be16_to_cpu(mad->mad_hdr.attr_id));
		वापस -ENOENT;
	पूर्ण

	अगर (slave)
		*slave = id->slave_id;
	set_remote_comm_id(mad, id->sl_cm_id);

	अगर (mad->mad_hdr.attr_id == CM_DREQ_ATTR_ID ||
	    mad->mad_hdr.attr_id == CM_REJ_ATTR_ID)
		schedule_delayed(ibdev, id);

	वापस 0;
पूर्ण

व्योम mlx4_ib_cm_paravirt_init(काष्ठा mlx4_ib_dev *dev)
अणु
	spin_lock_init(&dev->sriov.id_map_lock);
	INIT_LIST_HEAD(&dev->sriov.cm_list);
	dev->sriov.sl_id_map = RB_ROOT;
	xa_init_flags(&dev->sriov.pv_id_table, XA_FLAGS_ALLOC);
	xa_init(&dev->sriov.xa_rej_पंचांगout);
पूर्ण

अटल व्योम rej_पंचांगout_xa_cleanup(काष्ठा mlx4_ib_sriov *sriov, पूर्णांक slave)
अणु
	काष्ठा rej_पंचांगout_entry *item;
	bool flush_needed = false;
	अचिन्हित दीर्घ id;
	पूर्णांक cnt = 0;

	xa_lock(&sriov->xa_rej_पंचांगout);
	xa_क्रम_each(&sriov->xa_rej_पंचांगout, id, item) अणु
		अगर (slave < 0 || slave == item->slave) अणु
			mod_delayed_work(प्रणाली_wq, &item->समयout, 0);
			flush_needed = true;
			++cnt;
		पूर्ण
	पूर्ण
	xa_unlock(&sriov->xa_rej_पंचांगout);

	अगर (flush_needed) अणु
		flush_scheduled_work();
		pr_debug("Deleted %d entries in xarray for slave %d during cleanup\n",
			 cnt, slave);
	पूर्ण

	अगर (slave < 0)
		WARN_ON(!xa_empty(&sriov->xa_rej_पंचांगout));
पूर्ण

/* slave = -1 ==> all slaves */
/* TBD -- call paravirt clean क्रम single slave.  Need क्रम slave RESET event */
व्योम mlx4_ib_cm_paravirt_clean(काष्ठा mlx4_ib_dev *dev, पूर्णांक slave)
अणु
	काष्ठा mlx4_ib_sriov *sriov = &dev->sriov;
	काष्ठा rb_root *sl_id_map = &sriov->sl_id_map;
	काष्ठा list_head lh;
	काष्ठा rb_node *nd;
	पूर्णांक need_flush = 0;
	काष्ठा id_map_entry *map, *पंचांगp_map;
	/* cancel all delayed work queue entries */
	INIT_LIST_HEAD(&lh);
	spin_lock(&sriov->id_map_lock);
	list_क्रम_each_entry_safe(map, पंचांगp_map, &dev->sriov.cm_list, list) अणु
		अगर (slave < 0 || slave == map->slave_id) अणु
			अगर (map->scheduled_delete)
				need_flush |= !cancel_delayed_work(&map->समयout);
		पूर्ण
	पूर्ण

	spin_unlock(&sriov->id_map_lock);

	अगर (need_flush)
		flush_scheduled_work(); /* make sure all समयrs were flushed */

	/* now, हटाओ all leftover entries from databases*/
	spin_lock(&sriov->id_map_lock);
	अगर (slave < 0) अणु
		जबतक (rb_first(sl_id_map)) अणु
			काष्ठा id_map_entry *ent =
				rb_entry(rb_first(sl_id_map),
					 काष्ठा id_map_entry, node);

			rb_erase(&ent->node, sl_id_map);
			xa_erase(&sriov->pv_id_table, ent->pv_cm_id);
		पूर्ण
		list_splice_init(&dev->sriov.cm_list, &lh);
	पूर्ण अन्यथा अणु
		/* first, move nodes beदीर्घing to slave to db हटाओ list */
		nd = rb_first(sl_id_map);
		जबतक (nd) अणु
			काष्ठा id_map_entry *ent =
				rb_entry(nd, काष्ठा id_map_entry, node);
			nd = rb_next(nd);
			अगर (ent->slave_id == slave)
				list_move_tail(&ent->list, &lh);
		पूर्ण
		/* हटाओ those nodes from databases */
		list_क्रम_each_entry_safe(map, पंचांगp_map, &lh, list) अणु
			rb_erase(&map->node, sl_id_map);
			xa_erase(&sriov->pv_id_table, map->pv_cm_id);
		पूर्ण

		/* add reमुख्यing nodes from cm_list */
		list_क्रम_each_entry_safe(map, पंचांगp_map, &dev->sriov.cm_list, list) अणु
			अगर (slave == map->slave_id)
				list_move_tail(&map->list, &lh);
		पूर्ण
	पूर्ण

	spin_unlock(&sriov->id_map_lock);

	/* मुक्त any map entries left behind due to cancel_delayed_work above */
	list_क्रम_each_entry_safe(map, पंचांगp_map, &lh, list) अणु
		list_del(&map->list);
		kमुक्त(map);
	पूर्ण

	rej_पंचांगout_xa_cleanup(sriov, slave);
पूर्ण
