<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/चयनdev/चयनdev.c - Switch device API
 * Copyright (c) 2014-2015 Jiri Pirko <jiri@resnulli.us>
 * Copyright (c) 2014-2015 Scott Feldman <sfeldma@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/list.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/चयनdev.h>

अटल LIST_HEAD(deferred);
अटल DEFINE_SPINLOCK(deferred_lock);

प्रकार व्योम चयनdev_deferred_func_t(काष्ठा net_device *dev,
				       स्थिर व्योम *data);

काष्ठा चयनdev_deferred_item अणु
	काष्ठा list_head list;
	काष्ठा net_device *dev;
	चयनdev_deferred_func_t *func;
	अचिन्हित दीर्घ data[];
पूर्ण;

अटल काष्ठा चयनdev_deferred_item *चयनdev_deferred_dequeue(व्योम)
अणु
	काष्ठा चयनdev_deferred_item *dfitem;

	spin_lock_bh(&deferred_lock);
	अगर (list_empty(&deferred)) अणु
		dfitem = शून्य;
		जाओ unlock;
	पूर्ण
	dfitem = list_first_entry(&deferred,
				  काष्ठा चयनdev_deferred_item, list);
	list_del(&dfitem->list);
unlock:
	spin_unlock_bh(&deferred_lock);
	वापस dfitem;
पूर्ण

/**
 *	चयनdev_deferred_process - Process ops in deferred queue
 *
 *	Called to flush the ops currently queued in deferred ops queue.
 *	rtnl_lock must be held.
 */
व्योम चयनdev_deferred_process(व्योम)
अणु
	काष्ठा चयनdev_deferred_item *dfitem;

	ASSERT_RTNL();

	जबतक ((dfitem = चयनdev_deferred_dequeue())) अणु
		dfitem->func(dfitem->dev, dfitem->data);
		dev_put(dfitem->dev);
		kमुक्त(dfitem);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(चयनdev_deferred_process);

अटल व्योम चयनdev_deferred_process_work(काष्ठा work_काष्ठा *work)
अणु
	rtnl_lock();
	चयनdev_deferred_process();
	rtnl_unlock();
पूर्ण

अटल DECLARE_WORK(deferred_process_work, चयनdev_deferred_process_work);

अटल पूर्णांक चयनdev_deferred_enqueue(काष्ठा net_device *dev,
				      स्थिर व्योम *data, माप_प्रकार data_len,
				      चयनdev_deferred_func_t *func)
अणु
	काष्ठा चयनdev_deferred_item *dfitem;

	dfitem = kदो_स्मृति(माप(*dfitem) + data_len, GFP_ATOMIC);
	अगर (!dfitem)
		वापस -ENOMEM;
	dfitem->dev = dev;
	dfitem->func = func;
	स_नकल(dfitem->data, data, data_len);
	dev_hold(dev);
	spin_lock_bh(&deferred_lock);
	list_add_tail(&dfitem->list, &deferred);
	spin_unlock_bh(&deferred_lock);
	schedule_work(&deferred_process_work);
	वापस 0;
पूर्ण

अटल पूर्णांक चयनdev_port_attr_notअगरy(क्रमागत चयनdev_notअगरier_type nt,
				      काष्ठा net_device *dev,
				      स्थिर काष्ठा चयनdev_attr *attr,
				      काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;
	पूर्णांक rc;

	काष्ठा चयनdev_notअगरier_port_attr_info attr_info = अणु
		.attr = attr,
		.handled = false,
	पूर्ण;

	rc = call_चयनdev_blocking_notअगरiers(nt, dev,
					       &attr_info.info, extack);
	err = notअगरier_to_त्रुटि_सं(rc);
	अगर (err) अणु
		WARN_ON(!attr_info.handled);
		वापस err;
	पूर्ण

	अगर (!attr_info.handled)
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल पूर्णांक चयनdev_port_attr_set_now(काष्ठा net_device *dev,
				       स्थिर काष्ठा चयनdev_attr *attr,
				       काष्ठा netlink_ext_ack *extack)
अणु
	वापस चयनdev_port_attr_notअगरy(SWITCHDEV_PORT_ATTR_SET, dev, attr,
					  extack);
पूर्ण

अटल व्योम चयनdev_port_attr_set_deferred(काष्ठा net_device *dev,
					     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा चयनdev_attr *attr = data;
	पूर्णांक err;

	err = चयनdev_port_attr_set_now(dev, attr, शून्य);
	अगर (err && err != -EOPNOTSUPP)
		netdev_err(dev, "failed (err=%d) to set attribute (id=%d)\n",
			   err, attr->id);
	अगर (attr->complete)
		attr->complete(dev, err, attr->complete_priv);
पूर्ण

अटल पूर्णांक चयनdev_port_attr_set_defer(काष्ठा net_device *dev,
					 स्थिर काष्ठा चयनdev_attr *attr)
अणु
	वापस चयनdev_deferred_enqueue(dev, attr, माप(*attr),
					  चयनdev_port_attr_set_deferred);
पूर्ण

/**
 *	चयनdev_port_attr_set - Set port attribute
 *
 *	@dev: port device
 *	@attr: attribute to set
 *	@extack: netlink extended ack, क्रम error message propagation
 *
 *	rtnl_lock must be held and must not be in atomic section,
 *	in हाल SWITCHDEV_F_DEFER flag is not set.
 */
पूर्णांक चयनdev_port_attr_set(काष्ठा net_device *dev,
			    स्थिर काष्ठा चयनdev_attr *attr,
			    काष्ठा netlink_ext_ack *extack)
अणु
	अगर (attr->flags & SWITCHDEV_F_DEFER)
		वापस चयनdev_port_attr_set_defer(dev, attr);
	ASSERT_RTNL();
	वापस चयनdev_port_attr_set_now(dev, attr, extack);
पूर्ण
EXPORT_SYMBOL_GPL(चयनdev_port_attr_set);

अटल माप_प्रकार चयनdev_obj_size(स्थिर काष्ठा चयनdev_obj *obj)
अणु
	चयन (obj->id) अणु
	हाल SWITCHDEV_OBJ_ID_PORT_VLAN:
		वापस माप(काष्ठा चयनdev_obj_port_vlan);
	हाल SWITCHDEV_OBJ_ID_PORT_MDB:
		वापस माप(काष्ठा चयनdev_obj_port_mdb);
	हाल SWITCHDEV_OBJ_ID_HOST_MDB:
		वापस माप(काष्ठा चयनdev_obj_port_mdb);
	शेष:
		BUG();
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक चयनdev_port_obj_notअगरy(क्रमागत चयनdev_notअगरier_type nt,
				     काष्ठा net_device *dev,
				     स्थिर काष्ठा चयनdev_obj *obj,
				     काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक rc;
	पूर्णांक err;

	काष्ठा चयनdev_notअगरier_port_obj_info obj_info = अणु
		.obj = obj,
		.handled = false,
	पूर्ण;

	rc = call_चयनdev_blocking_notअगरiers(nt, dev, &obj_info.info, extack);
	err = notअगरier_to_त्रुटि_सं(rc);
	अगर (err) अणु
		WARN_ON(!obj_info.handled);
		वापस err;
	पूर्ण
	अगर (!obj_info.handled)
		वापस -EOPNOTSUPP;
	वापस 0;
पूर्ण

अटल व्योम चयनdev_port_obj_add_deferred(काष्ठा net_device *dev,
					    स्थिर व्योम *data)
अणु
	स्थिर काष्ठा चयनdev_obj *obj = data;
	पूर्णांक err;

	ASSERT_RTNL();
	err = चयनdev_port_obj_notअगरy(SWITCHDEV_PORT_OBJ_ADD,
					dev, obj, शून्य);
	अगर (err && err != -EOPNOTSUPP)
		netdev_err(dev, "failed (err=%d) to add object (id=%d)\n",
			   err, obj->id);
	अगर (obj->complete)
		obj->complete(dev, err, obj->complete_priv);
पूर्ण

अटल पूर्णांक चयनdev_port_obj_add_defer(काष्ठा net_device *dev,
					स्थिर काष्ठा चयनdev_obj *obj)
अणु
	वापस चयनdev_deferred_enqueue(dev, obj, चयनdev_obj_size(obj),
					  चयनdev_port_obj_add_deferred);
पूर्ण

/**
 *	चयनdev_port_obj_add - Add port object
 *
 *	@dev: port device
 *	@obj: object to add
 *	@extack: netlink extended ack
 *
 *	rtnl_lock must be held and must not be in atomic section,
 *	in हाल SWITCHDEV_F_DEFER flag is not set.
 */
पूर्णांक चयनdev_port_obj_add(काष्ठा net_device *dev,
			   स्थिर काष्ठा चयनdev_obj *obj,
			   काष्ठा netlink_ext_ack *extack)
अणु
	अगर (obj->flags & SWITCHDEV_F_DEFER)
		वापस चयनdev_port_obj_add_defer(dev, obj);
	ASSERT_RTNL();
	वापस चयनdev_port_obj_notअगरy(SWITCHDEV_PORT_OBJ_ADD,
					 dev, obj, extack);
पूर्ण
EXPORT_SYMBOL_GPL(चयनdev_port_obj_add);

अटल पूर्णांक चयनdev_port_obj_del_now(काष्ठा net_device *dev,
				      स्थिर काष्ठा चयनdev_obj *obj)
अणु
	वापस चयनdev_port_obj_notअगरy(SWITCHDEV_PORT_OBJ_DEL,
					 dev, obj, शून्य);
पूर्ण

अटल व्योम चयनdev_port_obj_del_deferred(काष्ठा net_device *dev,
					    स्थिर व्योम *data)
अणु
	स्थिर काष्ठा चयनdev_obj *obj = data;
	पूर्णांक err;

	err = चयनdev_port_obj_del_now(dev, obj);
	अगर (err && err != -EOPNOTSUPP)
		netdev_err(dev, "failed (err=%d) to del object (id=%d)\n",
			   err, obj->id);
	अगर (obj->complete)
		obj->complete(dev, err, obj->complete_priv);
पूर्ण

अटल पूर्णांक चयनdev_port_obj_del_defer(काष्ठा net_device *dev,
					स्थिर काष्ठा चयनdev_obj *obj)
अणु
	वापस चयनdev_deferred_enqueue(dev, obj, चयनdev_obj_size(obj),
					  चयनdev_port_obj_del_deferred);
पूर्ण

/**
 *	चयनdev_port_obj_del - Delete port object
 *
 *	@dev: port device
 *	@obj: object to delete
 *
 *	rtnl_lock must be held and must not be in atomic section,
 *	in हाल SWITCHDEV_F_DEFER flag is not set.
 */
पूर्णांक चयनdev_port_obj_del(काष्ठा net_device *dev,
			   स्थिर काष्ठा चयनdev_obj *obj)
अणु
	अगर (obj->flags & SWITCHDEV_F_DEFER)
		वापस चयनdev_port_obj_del_defer(dev, obj);
	ASSERT_RTNL();
	वापस चयनdev_port_obj_del_now(dev, obj);
पूर्ण
EXPORT_SYMBOL_GPL(चयनdev_port_obj_del);

अटल ATOMIC_NOTIFIER_HEAD(चयनdev_notअगर_chain);
अटल BLOCKING_NOTIFIER_HEAD(चयनdev_blocking_notअगर_chain);

/**
 *	रेजिस्टर_चयनdev_notअगरier - Register notअगरier
 *	@nb: notअगरier_block
 *
 *	Register चयन device notअगरier.
 */
पूर्णांक रेजिस्टर_चयनdev_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_रेजिस्टर(&चयनdev_notअगर_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_चयनdev_notअगरier);

/**
 *	unरेजिस्टर_चयनdev_notअगरier - Unरेजिस्टर notअगरier
 *	@nb: notअगरier_block
 *
 *	Unरेजिस्टर चयन device notअगरier.
 */
पूर्णांक unरेजिस्टर_चयनdev_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_unरेजिस्टर(&चयनdev_notअगर_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_चयनdev_notअगरier);

/**
 *	call_चयनdev_notअगरiers - Call notअगरiers
 *	@val: value passed unmodअगरied to notअगरier function
 *	@dev: port device
 *	@info: notअगरier inक्रमmation data
 *	@extack: netlink extended ack
 *	Call all network notअगरier blocks.
 */
पूर्णांक call_चयनdev_notअगरiers(अचिन्हित दीर्घ val, काष्ठा net_device *dev,
			     काष्ठा चयनdev_notअगरier_info *info,
			     काष्ठा netlink_ext_ack *extack)
अणु
	info->dev = dev;
	info->extack = extack;
	वापस atomic_notअगरier_call_chain(&चयनdev_notअगर_chain, val, info);
पूर्ण
EXPORT_SYMBOL_GPL(call_चयनdev_notअगरiers);

पूर्णांक रेजिस्टर_चयनdev_blocking_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	काष्ठा blocking_notअगरier_head *chain = &चयनdev_blocking_notअगर_chain;

	वापस blocking_notअगरier_chain_रेजिस्टर(chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_चयनdev_blocking_notअगरier);

पूर्णांक unरेजिस्टर_चयनdev_blocking_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	काष्ठा blocking_notअगरier_head *chain = &चयनdev_blocking_notअगर_chain;

	वापस blocking_notअगरier_chain_unरेजिस्टर(chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_चयनdev_blocking_notअगरier);

पूर्णांक call_चयनdev_blocking_notअगरiers(अचिन्हित दीर्घ val, काष्ठा net_device *dev,
				      काष्ठा चयनdev_notअगरier_info *info,
				      काष्ठा netlink_ext_ack *extack)
अणु
	info->dev = dev;
	info->extack = extack;
	वापस blocking_notअगरier_call_chain(&चयनdev_blocking_notअगर_chain,
					    val, info);
पूर्ण
EXPORT_SYMBOL_GPL(call_चयनdev_blocking_notअगरiers);

अटल पूर्णांक __चयनdev_handle_port_obj_add(काष्ठा net_device *dev,
			काष्ठा चयनdev_notअगरier_port_obj_info *port_obj_info,
			bool (*check_cb)(स्थिर काष्ठा net_device *dev),
			पूर्णांक (*add_cb)(काष्ठा net_device *dev,
				      स्थिर काष्ठा चयनdev_obj *obj,
				      काष्ठा netlink_ext_ack *extack))
अणु
	काष्ठा netlink_ext_ack *extack;
	काष्ठा net_device *lower_dev;
	काष्ठा list_head *iter;
	पूर्णांक err = -EOPNOTSUPP;

	extack = चयनdev_notअगरier_info_to_extack(&port_obj_info->info);

	अगर (check_cb(dev)) अणु
		err = add_cb(dev, port_obj_info->obj, extack);
		अगर (err != -EOPNOTSUPP)
			port_obj_info->handled = true;
		वापस err;
	पूर्ण

	/* Switch ports might be stacked under e.g. a LAG. Ignore the
	 * unsupported devices, another driver might be able to handle them. But
	 * propagate to the callers any hard errors.
	 *
	 * If the driver करोes its own bookkeeping of stacked ports, it's not
	 * necessary to go through this helper.
	 */
	netdev_क्रम_each_lower_dev(dev, lower_dev, iter) अणु
		अगर (netअगर_is_bridge_master(lower_dev))
			जारी;

		err = __चयनdev_handle_port_obj_add(lower_dev, port_obj_info,
						      check_cb, add_cb);
		अगर (err && err != -EOPNOTSUPP)
			वापस err;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक चयनdev_handle_port_obj_add(काष्ठा net_device *dev,
			काष्ठा चयनdev_notअगरier_port_obj_info *port_obj_info,
			bool (*check_cb)(स्थिर काष्ठा net_device *dev),
			पूर्णांक (*add_cb)(काष्ठा net_device *dev,
				      स्थिर काष्ठा चयनdev_obj *obj,
				      काष्ठा netlink_ext_ack *extack))
अणु
	पूर्णांक err;

	err = __चयनdev_handle_port_obj_add(dev, port_obj_info, check_cb,
					      add_cb);
	अगर (err == -EOPNOTSUPP)
		err = 0;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(चयनdev_handle_port_obj_add);

अटल पूर्णांक __चयनdev_handle_port_obj_del(काष्ठा net_device *dev,
			काष्ठा चयनdev_notअगरier_port_obj_info *port_obj_info,
			bool (*check_cb)(स्थिर काष्ठा net_device *dev),
			पूर्णांक (*del_cb)(काष्ठा net_device *dev,
				      स्थिर काष्ठा चयनdev_obj *obj))
अणु
	काष्ठा net_device *lower_dev;
	काष्ठा list_head *iter;
	पूर्णांक err = -EOPNOTSUPP;

	अगर (check_cb(dev)) अणु
		err = del_cb(dev, port_obj_info->obj);
		अगर (err != -EOPNOTSUPP)
			port_obj_info->handled = true;
		वापस err;
	पूर्ण

	/* Switch ports might be stacked under e.g. a LAG. Ignore the
	 * unsupported devices, another driver might be able to handle them. But
	 * propagate to the callers any hard errors.
	 *
	 * If the driver करोes its own bookkeeping of stacked ports, it's not
	 * necessary to go through this helper.
	 */
	netdev_क्रम_each_lower_dev(dev, lower_dev, iter) अणु
		अगर (netअगर_is_bridge_master(lower_dev))
			जारी;

		err = __चयनdev_handle_port_obj_del(lower_dev, port_obj_info,
						      check_cb, del_cb);
		अगर (err && err != -EOPNOTSUPP)
			वापस err;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक चयनdev_handle_port_obj_del(काष्ठा net_device *dev,
			काष्ठा चयनdev_notअगरier_port_obj_info *port_obj_info,
			bool (*check_cb)(स्थिर काष्ठा net_device *dev),
			पूर्णांक (*del_cb)(काष्ठा net_device *dev,
				      स्थिर काष्ठा चयनdev_obj *obj))
अणु
	पूर्णांक err;

	err = __चयनdev_handle_port_obj_del(dev, port_obj_info, check_cb,
					      del_cb);
	अगर (err == -EOPNOTSUPP)
		err = 0;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(चयनdev_handle_port_obj_del);

अटल पूर्णांक __चयनdev_handle_port_attr_set(काष्ठा net_device *dev,
			काष्ठा चयनdev_notअगरier_port_attr_info *port_attr_info,
			bool (*check_cb)(स्थिर काष्ठा net_device *dev),
			पूर्णांक (*set_cb)(काष्ठा net_device *dev,
				      स्थिर काष्ठा चयनdev_attr *attr,
				      काष्ठा netlink_ext_ack *extack))
अणु
	काष्ठा netlink_ext_ack *extack;
	काष्ठा net_device *lower_dev;
	काष्ठा list_head *iter;
	पूर्णांक err = -EOPNOTSUPP;

	extack = चयनdev_notअगरier_info_to_extack(&port_attr_info->info);

	अगर (check_cb(dev)) अणु
		err = set_cb(dev, port_attr_info->attr, extack);
		अगर (err != -EOPNOTSUPP)
			port_attr_info->handled = true;
		वापस err;
	पूर्ण

	/* Switch ports might be stacked under e.g. a LAG. Ignore the
	 * unsupported devices, another driver might be able to handle them. But
	 * propagate to the callers any hard errors.
	 *
	 * If the driver करोes its own bookkeeping of stacked ports, it's not
	 * necessary to go through this helper.
	 */
	netdev_क्रम_each_lower_dev(dev, lower_dev, iter) अणु
		अगर (netअगर_is_bridge_master(lower_dev))
			जारी;

		err = __चयनdev_handle_port_attr_set(lower_dev, port_attr_info,
						       check_cb, set_cb);
		अगर (err && err != -EOPNOTSUPP)
			वापस err;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक चयनdev_handle_port_attr_set(काष्ठा net_device *dev,
			काष्ठा चयनdev_notअगरier_port_attr_info *port_attr_info,
			bool (*check_cb)(स्थिर काष्ठा net_device *dev),
			पूर्णांक (*set_cb)(काष्ठा net_device *dev,
				      स्थिर काष्ठा चयनdev_attr *attr,
				      काष्ठा netlink_ext_ack *extack))
अणु
	पूर्णांक err;

	err = __चयनdev_handle_port_attr_set(dev, port_attr_info, check_cb,
					       set_cb);
	अगर (err == -EOPNOTSUPP)
		err = 0;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(चयनdev_handle_port_attr_set);
