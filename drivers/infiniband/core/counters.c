<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2019 Mellanox Technologies. All rights reserved.
 */
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/rdma_counter.h>

#समावेश "core_priv.h"
#समावेश "restrack.h"

#घोषणा ALL_AUTO_MODE_MASKS (RDMA_COUNTER_MASK_QP_TYPE | RDMA_COUNTER_MASK_PID)

अटल पूर्णांक __counter_set_mode(काष्ठा rdma_port_counter *port_counter,
			      क्रमागत rdma_nl_counter_mode new_mode,
			      क्रमागत rdma_nl_counter_mask new_mask)
अणु
	अगर (new_mode == RDMA_COUNTER_MODE_AUTO) अणु
		अगर (new_mask & (~ALL_AUTO_MODE_MASKS))
			वापस -EINVAL;
		अगर (port_counter->num_counters)
			वापस -EBUSY;
	पूर्ण

	port_counter->mode.mode = new_mode;
	port_counter->mode.mask = new_mask;
	वापस 0;
पूर्ण

/*
 * rdma_counter_set_स्वतः_mode() - Turn on/off per-port स्वतः mode
 *
 * @dev: Device to operate
 * @port: Port to use
 * @mask: Mask to configure
 * @extack: Message to the user
 *
 * Return 0 on success. If counter mode wasn't changed then it is considered
 * as success as well.
 * Return -EBUSY when changing to स्वतः mode जबतक there are bounded counters.
 *
 */
पूर्णांक rdma_counter_set_स्वतः_mode(काष्ठा ib_device *dev, u32 port,
			       क्रमागत rdma_nl_counter_mask mask,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा rdma_port_counter *port_counter;
	क्रमागत rdma_nl_counter_mode mode;
	पूर्णांक ret;

	port_counter = &dev->port_data[port].port_counter;
	अगर (!port_counter->hstats)
		वापस -EOPNOTSUPP;

	mutex_lock(&port_counter->lock);
	अगर (mask)
		mode = RDMA_COUNTER_MODE_AUTO;
	अन्यथा
		mode = (port_counter->num_counters) ? RDMA_COUNTER_MODE_MANUAL :
						      RDMA_COUNTER_MODE_NONE;

	अगर (port_counter->mode.mode == mode &&
	    port_counter->mode.mask == mask) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	ret = __counter_set_mode(port_counter, mode, mask);

out:
	mutex_unlock(&port_counter->lock);
	अगर (ret == -EBUSY)
		NL_SET_ERR_MSG(
			extack,
			"Modifying auto mode is not allowed when there is a bound QP");
	वापस ret;
पूर्ण

अटल व्योम स्वतः_mode_init_counter(काष्ठा rdma_counter *counter,
				   स्थिर काष्ठा ib_qp *qp,
				   क्रमागत rdma_nl_counter_mask new_mask)
अणु
	काष्ठा स्वतः_mode_param *param = &counter->mode.param;

	counter->mode.mode = RDMA_COUNTER_MODE_AUTO;
	counter->mode.mask = new_mask;

	अगर (new_mask & RDMA_COUNTER_MASK_QP_TYPE)
		param->qp_type = qp->qp_type;
पूर्ण

अटल पूर्णांक __rdma_counter_bind_qp(काष्ठा rdma_counter *counter,
				  काष्ठा ib_qp *qp)
अणु
	पूर्णांक ret;

	अगर (qp->counter)
		वापस -EINVAL;

	अगर (!qp->device->ops.counter_bind_qp)
		वापस -EOPNOTSUPP;

	mutex_lock(&counter->lock);
	ret = qp->device->ops.counter_bind_qp(counter, qp);
	mutex_unlock(&counter->lock);

	वापस ret;
पूर्ण

अटल काष्ठा rdma_counter *alloc_and_bind(काष्ठा ib_device *dev, u32 port,
					   काष्ठा ib_qp *qp,
					   क्रमागत rdma_nl_counter_mode mode)
अणु
	काष्ठा rdma_port_counter *port_counter;
	काष्ठा rdma_counter *counter;
	पूर्णांक ret;

	अगर (!dev->ops.counter_dealloc || !dev->ops.counter_alloc_stats)
		वापस शून्य;

	counter = kzalloc(माप(*counter), GFP_KERNEL);
	अगर (!counter)
		वापस शून्य;

	counter->device    = dev;
	counter->port      = port;

	rdma_restrack_new(&counter->res, RDMA_RESTRACK_COUNTER);
	counter->stats = dev->ops.counter_alloc_stats(counter);
	अगर (!counter->stats)
		जाओ err_stats;

	port_counter = &dev->port_data[port].port_counter;
	mutex_lock(&port_counter->lock);
	चयन (mode) अणु
	हाल RDMA_COUNTER_MODE_MANUAL:
		ret = __counter_set_mode(port_counter, RDMA_COUNTER_MODE_MANUAL,
					 0);
		अगर (ret) अणु
			mutex_unlock(&port_counter->lock);
			जाओ err_mode;
		पूर्ण
		अवरोध;
	हाल RDMA_COUNTER_MODE_AUTO:
		स्वतः_mode_init_counter(counter, qp, port_counter->mode.mask);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		mutex_unlock(&port_counter->lock);
		जाओ err_mode;
	पूर्ण

	port_counter->num_counters++;
	mutex_unlock(&port_counter->lock);

	counter->mode.mode = mode;
	kref_init(&counter->kref);
	mutex_init(&counter->lock);

	ret = __rdma_counter_bind_qp(counter, qp);
	अगर (ret)
		जाओ err_mode;

	rdma_restrack_parent_name(&counter->res, &qp->res);
	rdma_restrack_add(&counter->res);
	वापस counter;

err_mode:
	kमुक्त(counter->stats);
err_stats:
	rdma_restrack_put(&counter->res);
	kमुक्त(counter);
	वापस शून्य;
पूर्ण

अटल व्योम rdma_counter_मुक्त(काष्ठा rdma_counter *counter)
अणु
	काष्ठा rdma_port_counter *port_counter;

	port_counter = &counter->device->port_data[counter->port].port_counter;
	mutex_lock(&port_counter->lock);
	port_counter->num_counters--;
	अगर (!port_counter->num_counters &&
	    (port_counter->mode.mode == RDMA_COUNTER_MODE_MANUAL))
		__counter_set_mode(port_counter, RDMA_COUNTER_MODE_NONE, 0);

	mutex_unlock(&port_counter->lock);

	rdma_restrack_del(&counter->res);
	kमुक्त(counter->stats);
	kमुक्त(counter);
पूर्ण

अटल bool स्वतः_mode_match(काष्ठा ib_qp *qp, काष्ठा rdma_counter *counter,
			    क्रमागत rdma_nl_counter_mask स्वतः_mask)
अणु
	काष्ठा स्वतः_mode_param *param = &counter->mode.param;
	bool match = true;

	अगर (स्वतः_mask & RDMA_COUNTER_MASK_QP_TYPE)
		match &= (param->qp_type == qp->qp_type);

	अगर (स्वतः_mask & RDMA_COUNTER_MASK_PID)
		match &= (task_pid_nr(counter->res.task) ==
			  task_pid_nr(qp->res.task));

	वापस match;
पूर्ण

अटल पूर्णांक __rdma_counter_unbind_qp(काष्ठा ib_qp *qp)
अणु
	काष्ठा rdma_counter *counter = qp->counter;
	पूर्णांक ret;

	अगर (!qp->device->ops.counter_unbind_qp)
		वापस -EOPNOTSUPP;

	mutex_lock(&counter->lock);
	ret = qp->device->ops.counter_unbind_qp(qp);
	mutex_unlock(&counter->lock);

	वापस ret;
पूर्ण

अटल व्योम counter_history_stat_update(काष्ठा rdma_counter *counter)
अणु
	काष्ठा ib_device *dev = counter->device;
	काष्ठा rdma_port_counter *port_counter;
	पूर्णांक i;

	port_counter = &dev->port_data[counter->port].port_counter;
	अगर (!port_counter->hstats)
		वापस;

	rdma_counter_query_stats(counter);

	क्रम (i = 0; i < counter->stats->num_counters; i++)
		port_counter->hstats->value[i] += counter->stats->value[i];
पूर्ण

/*
 * rdma_get_counter_स्वतः_mode - Find the counter that @qp should be bound
 *     with in स्वतः mode
 *
 * Return: The counter (with ref-count increased) अगर found
 */
अटल काष्ठा rdma_counter *rdma_get_counter_स्वतः_mode(काष्ठा ib_qp *qp,
						       u32 port)
अणु
	काष्ठा rdma_port_counter *port_counter;
	काष्ठा rdma_counter *counter = शून्य;
	काष्ठा ib_device *dev = qp->device;
	काष्ठा rdma_restrack_entry *res;
	काष्ठा rdma_restrack_root *rt;
	अचिन्हित दीर्घ id = 0;

	port_counter = &dev->port_data[port].port_counter;
	rt = &dev->res[RDMA_RESTRACK_COUNTER];
	xa_lock(&rt->xa);
	xa_क्रम_each(&rt->xa, id, res) अणु
		counter = container_of(res, काष्ठा rdma_counter, res);
		अगर ((counter->device != qp->device) || (counter->port != port))
			जाओ next;

		अगर (स्वतः_mode_match(qp, counter, port_counter->mode.mask))
			अवरोध;
next:
		counter = शून्य;
	पूर्ण

	अगर (counter && !kref_get_unless_zero(&counter->kref))
		counter = शून्य;

	xa_unlock(&rt->xa);
	वापस counter;
पूर्ण

अटल व्योम counter_release(काष्ठा kref *kref)
अणु
	काष्ठा rdma_counter *counter;

	counter = container_of(kref, काष्ठा rdma_counter, kref);
	counter_history_stat_update(counter);
	counter->device->ops.counter_dealloc(counter);
	rdma_counter_मुक्त(counter);
पूर्ण

/*
 * rdma_counter_bind_qp_स्वतः - Check and bind the QP to a counter base on
 *   the स्वतः-mode rule
 */
पूर्णांक rdma_counter_bind_qp_स्वतः(काष्ठा ib_qp *qp, u32 port)
अणु
	काष्ठा rdma_port_counter *port_counter;
	काष्ठा ib_device *dev = qp->device;
	काष्ठा rdma_counter *counter;
	पूर्णांक ret;

	अगर (!rdma_restrack_is_tracked(&qp->res) || rdma_is_kernel_res(&qp->res))
		वापस 0;

	अगर (!rdma_is_port_valid(dev, port))
		वापस -EINVAL;

	port_counter = &dev->port_data[port].port_counter;
	अगर (port_counter->mode.mode != RDMA_COUNTER_MODE_AUTO)
		वापस 0;

	counter = rdma_get_counter_स्वतः_mode(qp, port);
	अगर (counter) अणु
		ret = __rdma_counter_bind_qp(counter, qp);
		अगर (ret) अणु
			kref_put(&counter->kref, counter_release);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		counter = alloc_and_bind(dev, port, qp, RDMA_COUNTER_MODE_AUTO);
		अगर (!counter)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * rdma_counter_unbind_qp - Unbind a qp from a counter
 * @क्रमce:
 *   true - Decrease the counter ref-count anyway (e.g., qp destroy)
 */
पूर्णांक rdma_counter_unbind_qp(काष्ठा ib_qp *qp, bool क्रमce)
अणु
	काष्ठा rdma_counter *counter = qp->counter;
	पूर्णांक ret;

	अगर (!counter)
		वापस -EINVAL;

	ret = __rdma_counter_unbind_qp(qp);
	अगर (ret && !क्रमce)
		वापस ret;

	kref_put(&counter->kref, counter_release);
	वापस 0;
पूर्ण

पूर्णांक rdma_counter_query_stats(काष्ठा rdma_counter *counter)
अणु
	काष्ठा ib_device *dev = counter->device;
	पूर्णांक ret;

	अगर (!dev->ops.counter_update_stats)
		वापस -EINVAL;

	mutex_lock(&counter->lock);
	ret = dev->ops.counter_update_stats(counter);
	mutex_unlock(&counter->lock);

	वापस ret;
पूर्ण

अटल u64 get_running_counters_hwstat_sum(काष्ठा ib_device *dev,
					   u32 port, u32 index)
अणु
	काष्ठा rdma_restrack_entry *res;
	काष्ठा rdma_restrack_root *rt;
	काष्ठा rdma_counter *counter;
	अचिन्हित दीर्घ id = 0;
	u64 sum = 0;

	rt = &dev->res[RDMA_RESTRACK_COUNTER];
	xa_lock(&rt->xa);
	xa_क्रम_each(&rt->xa, id, res) अणु
		अगर (!rdma_restrack_get(res))
			जारी;

		xa_unlock(&rt->xa);

		counter = container_of(res, काष्ठा rdma_counter, res);
		अगर ((counter->device != dev) || (counter->port != port) ||
		    rdma_counter_query_stats(counter))
			जाओ next;

		sum += counter->stats->value[index];

next:
		xa_lock(&rt->xa);
		rdma_restrack_put(res);
	पूर्ण

	xa_unlock(&rt->xa);
	वापस sum;
पूर्ण

/*
 * rdma_counter_get_hwstat_value() - Get the sum value of all counters on a
 *   specअगरic port, including the running ones and history data
 */
u64 rdma_counter_get_hwstat_value(काष्ठा ib_device *dev, u32 port, u32 index)
अणु
	काष्ठा rdma_port_counter *port_counter;
	u64 sum;

	port_counter = &dev->port_data[port].port_counter;
	अगर (!port_counter->hstats)
		वापस 0;

	sum = get_running_counters_hwstat_sum(dev, port, index);
	sum += port_counter->hstats->value[index];

	वापस sum;
पूर्ण

अटल काष्ठा ib_qp *rdma_counter_get_qp(काष्ठा ib_device *dev, u32 qp_num)
अणु
	काष्ठा rdma_restrack_entry *res = शून्य;
	काष्ठा ib_qp *qp = शून्य;

	res = rdma_restrack_get_byid(dev, RDMA_RESTRACK_QP, qp_num);
	अगर (IS_ERR(res))
		वापस शून्य;

	qp = container_of(res, काष्ठा ib_qp, res);
	अगर (qp->qp_type == IB_QPT_RAW_PACKET && !capable(CAP_NET_RAW))
		जाओ err;

	वापस qp;

err:
	rdma_restrack_put(res);
	वापस शून्य;
पूर्ण

अटल काष्ठा rdma_counter *rdma_get_counter_by_id(काष्ठा ib_device *dev,
						   u32 counter_id)
अणु
	काष्ठा rdma_restrack_entry *res;
	काष्ठा rdma_counter *counter;

	res = rdma_restrack_get_byid(dev, RDMA_RESTRACK_COUNTER, counter_id);
	अगर (IS_ERR(res))
		वापस शून्य;

	counter = container_of(res, काष्ठा rdma_counter, res);
	kref_get(&counter->kref);
	rdma_restrack_put(res);

	वापस counter;
पूर्ण

/*
 * rdma_counter_bind_qpn() - Bind QP @qp_num to counter @counter_id
 */
पूर्णांक rdma_counter_bind_qpn(काष्ठा ib_device *dev, u32 port,
			  u32 qp_num, u32 counter_id)
अणु
	काष्ठा rdma_port_counter *port_counter;
	काष्ठा rdma_counter *counter;
	काष्ठा ib_qp *qp;
	पूर्णांक ret;

	port_counter = &dev->port_data[port].port_counter;
	अगर (port_counter->mode.mode == RDMA_COUNTER_MODE_AUTO)
		वापस -EINVAL;

	qp = rdma_counter_get_qp(dev, qp_num);
	अगर (!qp)
		वापस -ENOENT;

	counter = rdma_get_counter_by_id(dev, counter_id);
	अगर (!counter) अणु
		ret = -ENOENT;
		जाओ err;
	पूर्ण

	अगर (rdma_is_kernel_res(&counter->res) != rdma_is_kernel_res(&qp->res)) अणु
		ret = -EINVAL;
		जाओ err_task;
	पूर्ण

	अगर ((counter->device != qp->device) || (counter->port != qp->port)) अणु
		ret = -EINVAL;
		जाओ err_task;
	पूर्ण

	ret = __rdma_counter_bind_qp(counter, qp);
	अगर (ret)
		जाओ err_task;

	rdma_restrack_put(&qp->res);
	वापस 0;

err_task:
	kref_put(&counter->kref, counter_release);
err:
	rdma_restrack_put(&qp->res);
	वापस ret;
पूर्ण

/*
 * rdma_counter_bind_qpn_alloc() - Alloc a counter and bind QP @qp_num to it
 *   The id of new counter is वापसed in @counter_id
 */
पूर्णांक rdma_counter_bind_qpn_alloc(काष्ठा ib_device *dev, u32 port,
				u32 qp_num, u32 *counter_id)
अणु
	काष्ठा rdma_port_counter *port_counter;
	काष्ठा rdma_counter *counter;
	काष्ठा ib_qp *qp;
	पूर्णांक ret;

	अगर (!rdma_is_port_valid(dev, port))
		वापस -EINVAL;

	port_counter = &dev->port_data[port].port_counter;
	अगर (!port_counter->hstats)
		वापस -EOPNOTSUPP;

	अगर (port_counter->mode.mode == RDMA_COUNTER_MODE_AUTO)
		वापस -EINVAL;

	qp = rdma_counter_get_qp(dev, qp_num);
	अगर (!qp)
		वापस -ENOENT;

	अगर (rdma_is_port_valid(dev, qp->port) && (qp->port != port)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	counter = alloc_and_bind(dev, port, qp, RDMA_COUNTER_MODE_MANUAL);
	अगर (!counter) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	अगर (counter_id)
		*counter_id = counter->id;

	rdma_restrack_put(&qp->res);
	वापस 0;

err:
	rdma_restrack_put(&qp->res);
	वापस ret;
पूर्ण

/*
 * rdma_counter_unbind_qpn() - Unbind QP @qp_num from a counter
 */
पूर्णांक rdma_counter_unbind_qpn(काष्ठा ib_device *dev, u32 port,
			    u32 qp_num, u32 counter_id)
अणु
	काष्ठा rdma_port_counter *port_counter;
	काष्ठा ib_qp *qp;
	पूर्णांक ret;

	अगर (!rdma_is_port_valid(dev, port))
		वापस -EINVAL;

	qp = rdma_counter_get_qp(dev, qp_num);
	अगर (!qp)
		वापस -ENOENT;

	अगर (rdma_is_port_valid(dev, qp->port) && (qp->port != port)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	port_counter = &dev->port_data[port].port_counter;
	अगर (!qp->counter || qp->counter->id != counter_id ||
	    port_counter->mode.mode != RDMA_COUNTER_MODE_MANUAL) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = rdma_counter_unbind_qp(qp, false);

out:
	rdma_restrack_put(&qp->res);
	वापस ret;
पूर्ण

पूर्णांक rdma_counter_get_mode(काष्ठा ib_device *dev, u32 port,
			  क्रमागत rdma_nl_counter_mode *mode,
			  क्रमागत rdma_nl_counter_mask *mask)
अणु
	काष्ठा rdma_port_counter *port_counter;

	port_counter = &dev->port_data[port].port_counter;
	*mode = port_counter->mode.mode;
	*mask = port_counter->mode.mask;

	वापस 0;
पूर्ण

व्योम rdma_counter_init(काष्ठा ib_device *dev)
अणु
	काष्ठा rdma_port_counter *port_counter;
	u32 port, i;

	अगर (!dev->port_data)
		वापस;

	rdma_क्रम_each_port(dev, port) अणु
		port_counter = &dev->port_data[port].port_counter;
		port_counter->mode.mode = RDMA_COUNTER_MODE_NONE;
		mutex_init(&port_counter->lock);

		अगर (!dev->ops.alloc_hw_stats)
			जारी;

		port_counter->hstats = dev->ops.alloc_hw_stats(dev, port);
		अगर (!port_counter->hstats)
			जाओ fail;
	पूर्ण

	वापस;

fail:
	क्रम (i = port; i >= rdma_start_port(dev); i--) अणु
		port_counter = &dev->port_data[port].port_counter;
		kमुक्त(port_counter->hstats);
		port_counter->hstats = शून्य;
		mutex_destroy(&port_counter->lock);
	पूर्ण
पूर्ण

व्योम rdma_counter_release(काष्ठा ib_device *dev)
अणु
	काष्ठा rdma_port_counter *port_counter;
	u32 port;

	rdma_क्रम_each_port(dev, port) अणु
		port_counter = &dev->port_data[port].port_counter;
		kमुक्त(port_counter->hstats);
		mutex_destroy(&port_counter->lock);
	पूर्ण
पूर्ण
