<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved.
 */

#समावेश <rdma/rdma_cm.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/restrack.h>
#समावेश <rdma/rdma_counter.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/pid_namespace.h>

#समावेश "cma_priv.h"
#समावेश "restrack.h"

/**
 * rdma_restrack_init() - initialize and allocate resource tracking
 * @dev:  IB device
 *
 * Return: 0 on success
 */
पूर्णांक rdma_restrack_init(काष्ठा ib_device *dev)
अणु
	काष्ठा rdma_restrack_root *rt;
	पूर्णांक i;

	dev->res = kसुस्मृति(RDMA_RESTRACK_MAX, माप(*rt), GFP_KERNEL);
	अगर (!dev->res)
		वापस -ENOMEM;

	rt = dev->res;

	क्रम (i = 0; i < RDMA_RESTRACK_MAX; i++)
		xa_init_flags(&rt[i].xa, XA_FLAGS_ALLOC);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *type2str(क्रमागत rdma_restrack_type type)
अणु
	अटल स्थिर अक्षर * स्थिर names[RDMA_RESTRACK_MAX] = अणु
		[RDMA_RESTRACK_PD] = "PD",
		[RDMA_RESTRACK_CQ] = "CQ",
		[RDMA_RESTRACK_QP] = "QP",
		[RDMA_RESTRACK_CM_ID] = "CM_ID",
		[RDMA_RESTRACK_MR] = "MR",
		[RDMA_RESTRACK_CTX] = "CTX",
		[RDMA_RESTRACK_COUNTER] = "COUNTER",
		[RDMA_RESTRACK_SRQ] = "SRQ",
	पूर्ण;

	वापस names[type];
पूर्ण;

/**
 * rdma_restrack_clean() - clean resource tracking
 * @dev:  IB device
 */
व्योम rdma_restrack_clean(काष्ठा ib_device *dev)
अणु
	काष्ठा rdma_restrack_root *rt = dev->res;
	काष्ठा rdma_restrack_entry *e;
	अक्षर buf[TASK_COMM_LEN];
	bool found = false;
	स्थिर अक्षर *owner;
	पूर्णांक i;

	क्रम (i = 0 ; i < RDMA_RESTRACK_MAX; i++) अणु
		काष्ठा xarray *xa = &dev->res[i].xa;

		अगर (!xa_empty(xa)) अणु
			अचिन्हित दीर्घ index;

			अगर (!found) अणु
				pr_err("restrack: %s", CUT_HERE);
				dev_err(&dev->dev, "BUG: RESTRACK detected leak of resources\n");
			पूर्ण
			xa_क्रम_each(xa, index, e) अणु
				अगर (rdma_is_kernel_res(e)) अणु
					owner = e->kern_name;
				पूर्ण अन्यथा अणु
					/*
					 * There is no need to call get_task_काष्ठा here,
					 * because we can be here only अगर there are more
					 * get_task_काष्ठा() call than put_task_काष्ठा().
					 */
					get_task_comm(buf, e->task);
					owner = buf;
				पूर्ण

				pr_err("restrack: %s %s object allocated by %s is not freed\n",
				       rdma_is_kernel_res(e) ? "Kernel" :
							       "User",
				       type2str(e->type), owner);
			पूर्ण
			found = true;
		पूर्ण
		xa_destroy(xa);
	पूर्ण
	अगर (found)
		pr_err("restrack: %s", CUT_HERE);

	kमुक्त(rt);
पूर्ण

/**
 * rdma_restrack_count() - the current usage of specअगरic object
 * @dev:  IB device
 * @type: actual type of object to operate
 */
पूर्णांक rdma_restrack_count(काष्ठा ib_device *dev, क्रमागत rdma_restrack_type type)
अणु
	काष्ठा rdma_restrack_root *rt = &dev->res[type];
	काष्ठा rdma_restrack_entry *e;
	XA_STATE(xas, &rt->xa, 0);
	u32 cnt = 0;

	xa_lock(&rt->xa);
	xas_क्रम_each(&xas, e, U32_MAX)
		cnt++;
	xa_unlock(&rt->xa);
	वापस cnt;
पूर्ण
EXPORT_SYMBOL(rdma_restrack_count);

अटल काष्ठा ib_device *res_to_dev(काष्ठा rdma_restrack_entry *res)
अणु
	चयन (res->type) अणु
	हाल RDMA_RESTRACK_PD:
		वापस container_of(res, काष्ठा ib_pd, res)->device;
	हाल RDMA_RESTRACK_CQ:
		वापस container_of(res, काष्ठा ib_cq, res)->device;
	हाल RDMA_RESTRACK_QP:
		वापस container_of(res, काष्ठा ib_qp, res)->device;
	हाल RDMA_RESTRACK_CM_ID:
		वापस container_of(res, काष्ठा rdma_id_निजी,
				    res)->id.device;
	हाल RDMA_RESTRACK_MR:
		वापस container_of(res, काष्ठा ib_mr, res)->device;
	हाल RDMA_RESTRACK_CTX:
		वापस container_of(res, काष्ठा ib_ucontext, res)->device;
	हाल RDMA_RESTRACK_COUNTER:
		वापस container_of(res, काष्ठा rdma_counter, res)->device;
	हाल RDMA_RESTRACK_SRQ:
		वापस container_of(res, काष्ठा ib_srq, res)->device;
	शेष:
		WARN_ONCE(true, "Wrong resource tracking type %u\n", res->type);
		वापस शून्य;
	पूर्ण
पूर्ण

/**
 * rdma_restrack_attach_task() - attach the task onto this resource,
 * valid क्रम user space restrack entries.
 * @res:  resource entry
 * @task: the task to attach
 */
अटल व्योम rdma_restrack_attach_task(काष्ठा rdma_restrack_entry *res,
				      काष्ठा task_काष्ठा *task)
अणु
	अगर (WARN_ON_ONCE(!task))
		वापस;

	अगर (res->task)
		put_task_काष्ठा(res->task);
	get_task_काष्ठा(task);
	res->task = task;
	res->user = true;
पूर्ण

/**
 * rdma_restrack_set_name() - set the task क्रम this resource
 * @res:  resource entry
 * @caller: kernel name, the current task will be used अगर the caller is शून्य.
 */
व्योम rdma_restrack_set_name(काष्ठा rdma_restrack_entry *res, स्थिर अक्षर *caller)
अणु
	अगर (caller) अणु
		res->kern_name = caller;
		वापस;
	पूर्ण

	rdma_restrack_attach_task(res, current);
पूर्ण
EXPORT_SYMBOL(rdma_restrack_set_name);

/**
 * rdma_restrack_parent_name() - set the restrack name properties based
 * on parent restrack
 * @dst: destination resource entry
 * @parent: parent resource entry
 */
व्योम rdma_restrack_parent_name(काष्ठा rdma_restrack_entry *dst,
			       स्थिर काष्ठा rdma_restrack_entry *parent)
अणु
	अगर (rdma_is_kernel_res(parent))
		dst->kern_name = parent->kern_name;
	अन्यथा
		rdma_restrack_attach_task(dst, parent->task);
पूर्ण
EXPORT_SYMBOL(rdma_restrack_parent_name);

/**
 * rdma_restrack_new() - Initializes new restrack entry to allow _put() पूर्णांकerface
 * to release memory in fully स्वतःmatic way.
 * @res: Entry to initialize
 * @type: REstrack type
 */
व्योम rdma_restrack_new(काष्ठा rdma_restrack_entry *res,
		       क्रमागत rdma_restrack_type type)
अणु
	kref_init(&res->kref);
	init_completion(&res->comp);
	res->type = type;
पूर्ण
EXPORT_SYMBOL(rdma_restrack_new);

/**
 * rdma_restrack_add() - add object to the reource tracking database
 * @res:  resource entry
 */
व्योम rdma_restrack_add(काष्ठा rdma_restrack_entry *res)
अणु
	काष्ठा ib_device *dev = res_to_dev(res);
	काष्ठा rdma_restrack_root *rt;
	पूर्णांक ret = 0;

	अगर (!dev)
		वापस;

	अगर (res->no_track)
		जाओ out;

	rt = &dev->res[res->type];

	अगर (res->type == RDMA_RESTRACK_QP) अणु
		/* Special हाल to ensure that LQPN poपूर्णांकs to right QP */
		काष्ठा ib_qp *qp = container_of(res, काष्ठा ib_qp, res);

		WARN_ONCE(qp->qp_num >> 24 || qp->port >> 8,
			  "QP number 0x%0X and port 0x%0X", qp->qp_num,
			  qp->port);
		res->id = qp->qp_num;
		अगर (qp->qp_type == IB_QPT_SMI || qp->qp_type == IB_QPT_GSI)
			res->id |= qp->port << 24;
		ret = xa_insert(&rt->xa, res->id, res, GFP_KERNEL);
		अगर (ret)
			res->id = 0;
	पूर्ण अन्यथा अगर (res->type == RDMA_RESTRACK_COUNTER) अणु
		/* Special हाल to ensure that cntn poपूर्णांकs to right counter */
		काष्ठा rdma_counter *counter;

		counter = container_of(res, काष्ठा rdma_counter, res);
		ret = xa_insert(&rt->xa, counter->id, res, GFP_KERNEL);
		res->id = ret ? 0 : counter->id;
	पूर्ण अन्यथा अणु
		ret = xa_alloc_cyclic(&rt->xa, &res->id, res, xa_limit_32b,
				      &rt->next_id, GFP_KERNEL);
		ret = (ret < 0) ? ret : 0;
	पूर्ण

out:
	अगर (!ret)
		res->valid = true;
पूर्ण
EXPORT_SYMBOL(rdma_restrack_add);

पूर्णांक __must_check rdma_restrack_get(काष्ठा rdma_restrack_entry *res)
अणु
	वापस kref_get_unless_zero(&res->kref);
पूर्ण
EXPORT_SYMBOL(rdma_restrack_get);

/**
 * rdma_restrack_get_byid() - translate from ID to restrack object
 * @dev: IB device
 * @type: resource track type
 * @id: ID to take a look
 *
 * Return: Poपूर्णांकer to restrack entry or -ENOENT in हाल of error.
 */
काष्ठा rdma_restrack_entry *
rdma_restrack_get_byid(काष्ठा ib_device *dev,
		       क्रमागत rdma_restrack_type type, u32 id)
अणु
	काष्ठा rdma_restrack_root *rt = &dev->res[type];
	काष्ठा rdma_restrack_entry *res;

	xa_lock(&rt->xa);
	res = xa_load(&rt->xa, id);
	अगर (!res || !rdma_restrack_get(res))
		res = ERR_PTR(-ENOENT);
	xa_unlock(&rt->xa);

	वापस res;
पूर्ण
EXPORT_SYMBOL(rdma_restrack_get_byid);

अटल व्योम restrack_release(काष्ठा kref *kref)
अणु
	काष्ठा rdma_restrack_entry *res;

	res = container_of(kref, काष्ठा rdma_restrack_entry, kref);
	अगर (res->task) अणु
		put_task_काष्ठा(res->task);
		res->task = शून्य;
	पूर्ण
	complete(&res->comp);
पूर्ण

पूर्णांक rdma_restrack_put(काष्ठा rdma_restrack_entry *res)
अणु
	वापस kref_put(&res->kref, restrack_release);
पूर्ण
EXPORT_SYMBOL(rdma_restrack_put);

/**
 * rdma_restrack_del() - delete object from the reource tracking database
 * @res:  resource entry
 */
व्योम rdma_restrack_del(काष्ठा rdma_restrack_entry *res)
अणु
	काष्ठा rdma_restrack_entry *old;
	काष्ठा rdma_restrack_root *rt;
	काष्ठा ib_device *dev;

	अगर (!res->valid) अणु
		अगर (res->task) अणु
			put_task_काष्ठा(res->task);
			res->task = शून्य;
		पूर्ण
		वापस;
	पूर्ण

	अगर (res->no_track)
		जाओ out;

	dev = res_to_dev(res);
	अगर (WARN_ON(!dev))
		वापस;

	rt = &dev->res[res->type];

	old = xa_erase(&rt->xa, res->id);
	अगर (res->type == RDMA_RESTRACK_MR || res->type == RDMA_RESTRACK_QP)
		वापस;
	WARN_ON(old != res);

out:
	res->valid = false;
	rdma_restrack_put(res);
	रुको_क्रम_completion(&res->comp);
पूर्ण
EXPORT_SYMBOL(rdma_restrack_del);
