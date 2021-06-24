<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * V4L2 asynchronous subdevice registration API
 *
 * Copyright (C) 2012-2013, Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>

अटल पूर्णांक v4l2_async_notअगरier_call_bound(काष्ठा v4l2_async_notअगरier *n,
					  काष्ठा v4l2_subdev *subdev,
					  काष्ठा v4l2_async_subdev *asd)
अणु
	अगर (!n->ops || !n->ops->bound)
		वापस 0;

	वापस n->ops->bound(n, subdev, asd);
पूर्ण

अटल व्योम v4l2_async_notअगरier_call_unbind(काष्ठा v4l2_async_notअगरier *n,
					    काष्ठा v4l2_subdev *subdev,
					    काष्ठा v4l2_async_subdev *asd)
अणु
	अगर (!n->ops || !n->ops->unbind)
		वापस;

	n->ops->unbind(n, subdev, asd);
पूर्ण

अटल पूर्णांक v4l2_async_notअगरier_call_complete(काष्ठा v4l2_async_notअगरier *n)
अणु
	अगर (!n->ops || !n->ops->complete)
		वापस 0;

	वापस n->ops->complete(n);
पूर्ण

अटल bool match_i2c(काष्ठा v4l2_async_notअगरier *notअगरier,
		      काष्ठा v4l2_subdev *sd, काष्ठा v4l2_async_subdev *asd)
अणु
#अगर IS_ENABLED(CONFIG_I2C)
	काष्ठा i2c_client *client = i2c_verअगरy_client(sd->dev);

	वापस client &&
		asd->match.i2c.adapter_id == client->adapter->nr &&
		asd->match.i2c.address == client->addr;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल bool match_fwnode(काष्ठा v4l2_async_notअगरier *notअगरier,
			 काष्ठा v4l2_subdev *sd, काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा fwnode_handle *other_fwnode;
	काष्ठा fwnode_handle *dev_fwnode;
	bool asd_fwnode_is_ep;
	bool sd_fwnode_is_ep;
	काष्ठा device *dev;

	/*
	 * Both the subdev and the async subdev can provide either an endpoपूर्णांक
	 * fwnode or a device fwnode. Start with the simple हाल of direct
	 * fwnode matching.
	 */
	अगर (sd->fwnode == asd->match.fwnode)
		वापस true;

	/*
	 * Check the same situation क्रम any possible secondary asचिन्हित to the
	 * subdev's fwnode
	 */
	अगर (!IS_ERR_OR_शून्य(sd->fwnode->secondary) &&
	    sd->fwnode->secondary == asd->match.fwnode)
		वापस true;

	/*
	 * Otherwise, check अगर the sd fwnode and the asd fwnode refer to an
	 * endpoपूर्णांक or a device. If they're of the same type, there's no match.
	 * Technically speaking this checks अगर the nodes refer to a connected
	 * endpoपूर्णांक, which is the simplest check that works क्रम both OF and
	 * ACPI. This won't make a dअगरference, as drivers should not try to
	 * match unconnected endpoपूर्णांकs.
	 */
	sd_fwnode_is_ep = fwnode_graph_is_endpoपूर्णांक(sd->fwnode);
	asd_fwnode_is_ep = fwnode_graph_is_endpoपूर्णांक(asd->match.fwnode);

	अगर (sd_fwnode_is_ep == asd_fwnode_is_ep)
		वापस false;

	/*
	 * The sd and asd fwnodes are of dअगरferent types. Get the device fwnode
	 * parent of the endpoपूर्णांक fwnode, and compare it with the other fwnode.
	 */
	अगर (sd_fwnode_is_ep) अणु
		dev_fwnode = fwnode_graph_get_port_parent(sd->fwnode);
		other_fwnode = asd->match.fwnode;
	पूर्ण अन्यथा अणु
		dev_fwnode = fwnode_graph_get_port_parent(asd->match.fwnode);
		other_fwnode = sd->fwnode;
	पूर्ण

	fwnode_handle_put(dev_fwnode);

	अगर (dev_fwnode != other_fwnode)
		वापस false;

	/*
	 * We have a heterogeneous match. Retrieve the काष्ठा device of the side
	 * that matched on a device fwnode to prपूर्णांक its driver name.
	 */
	अगर (sd_fwnode_is_ep)
		dev = notअगरier->v4l2_dev ? notअगरier->v4l2_dev->dev
		    : notअगरier->sd->dev;
	अन्यथा
		dev = sd->dev;

	अगर (dev && dev->driver) अणु
		अगर (sd_fwnode_is_ep)
			dev_warn(dev, "Driver %s uses device fwnode, incorrect match may occur\n",
				 dev->driver->name);
		dev_notice(dev, "Consider updating driver %s to match on endpoints\n",
			   dev->driver->name);
	पूर्ण

	वापस true;
पूर्ण

अटल LIST_HEAD(subdev_list);
अटल LIST_HEAD(notअगरier_list);
अटल DEFINE_MUTEX(list_lock);

अटल काष्ठा v4l2_async_subdev *
v4l2_async_find_match(काष्ठा v4l2_async_notअगरier *notअगरier,
		      काष्ठा v4l2_subdev *sd)
अणु
	bool (*match)(काष्ठा v4l2_async_notअगरier *notअगरier,
		      काष्ठा v4l2_subdev *sd, काष्ठा v4l2_async_subdev *asd);
	काष्ठा v4l2_async_subdev *asd;

	list_क्रम_each_entry(asd, &notअगरier->रुकोing, list) अणु
		/* bus_type has been verअगरied valid beक्रमe */
		चयन (asd->match_type) अणु
		हाल V4L2_ASYNC_MATCH_I2C:
			match = match_i2c;
			अवरोध;
		हाल V4L2_ASYNC_MATCH_FWNODE:
			match = match_fwnode;
			अवरोध;
		शेष:
			/* Cannot happen, unless someone अवरोधs us */
			WARN_ON(true);
			वापस शून्य;
		पूर्ण

		/* match cannot be शून्य here */
		अगर (match(notअगरier, sd, asd))
			वापस asd;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Compare two async sub-device descriptors क्रम equivalence */
अटल bool asd_equal(काष्ठा v4l2_async_subdev *asd_x,
		      काष्ठा v4l2_async_subdev *asd_y)
अणु
	अगर (asd_x->match_type != asd_y->match_type)
		वापस false;

	चयन (asd_x->match_type) अणु
	हाल V4L2_ASYNC_MATCH_I2C:
		वापस asd_x->match.i2c.adapter_id ==
			asd_y->match.i2c.adapter_id &&
			asd_x->match.i2c.address ==
			asd_y->match.i2c.address;
	हाल V4L2_ASYNC_MATCH_FWNODE:
		वापस asd_x->match.fwnode == asd_y->match.fwnode;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

/* Find the sub-device notअगरier रेजिस्टरed by a sub-device driver. */
अटल काष्ठा v4l2_async_notअगरier *
v4l2_async_find_subdev_notअगरier(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा v4l2_async_notअगरier *n;

	list_क्रम_each_entry(n, &notअगरier_list, list)
		अगर (n->sd == sd)
			वापस n;

	वापस शून्य;
पूर्ण

/* Get v4l2_device related to the notअगरier अगर one can be found. */
अटल काष्ठा v4l2_device *
v4l2_async_notअगरier_find_v4l2_dev(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	जबतक (notअगरier->parent)
		notअगरier = notअगरier->parent;

	वापस notअगरier->v4l2_dev;
पूर्ण

/*
 * Return true अगर all child sub-device notअगरiers are complete, false otherwise.
 */
अटल bool
v4l2_async_notअगरier_can_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा v4l2_subdev *sd;

	अगर (!list_empty(&notअगरier->रुकोing))
		वापस false;

	list_क्रम_each_entry(sd, &notअगरier->करोne, async_list) अणु
		काष्ठा v4l2_async_notअगरier *subdev_notअगरier =
			v4l2_async_find_subdev_notअगरier(sd);

		अगर (subdev_notअगरier &&
		    !v4l2_async_notअगरier_can_complete(subdev_notअगरier))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Complete the master notअगरier अगर possible. This is करोne when all async
 * sub-devices have been bound; v4l2_device is also available then.
 */
अटल पूर्णांक
v4l2_async_notअगरier_try_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	/* Quick check whether there are still more sub-devices here. */
	अगर (!list_empty(&notअगरier->रुकोing))
		वापस 0;

	/* Check the entire notअगरier tree; find the root notअगरier first. */
	जबतक (notअगरier->parent)
		notअगरier = notअगरier->parent;

	/* This is root अगर it has v4l2_dev. */
	अगर (!notअगरier->v4l2_dev)
		वापस 0;

	/* Is everything पढ़ोy? */
	अगर (!v4l2_async_notअगरier_can_complete(notअगरier))
		वापस 0;

	वापस v4l2_async_notअगरier_call_complete(notअगरier);
पूर्ण

अटल पूर्णांक
v4l2_async_notअगरier_try_all_subdevs(काष्ठा v4l2_async_notअगरier *notअगरier);

अटल पूर्णांक v4l2_async_match_notअगरy(काष्ठा v4l2_async_notअगरier *notअगरier,
				   काष्ठा v4l2_device *v4l2_dev,
				   काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा v4l2_async_notअगरier *subdev_notअगरier;
	पूर्णांक ret;

	ret = v4l2_device_रेजिस्टर_subdev(v4l2_dev, sd);
	अगर (ret < 0)
		वापस ret;

	ret = v4l2_async_notअगरier_call_bound(notअगरier, sd, asd);
	अगर (ret < 0) अणु
		v4l2_device_unरेजिस्टर_subdev(sd);
		वापस ret;
	पूर्ण

	/* Remove from the रुकोing list */
	list_del(&asd->list);
	sd->asd = asd;
	sd->notअगरier = notअगरier;

	/* Move from the global subdevice list to notअगरier's करोne */
	list_move(&sd->async_list, &notअगरier->करोne);

	/*
	 * See अगर the sub-device has a notअगरier. If not, वापस here.
	 */
	subdev_notअगरier = v4l2_async_find_subdev_notअगरier(sd);
	अगर (!subdev_notअगरier || subdev_notअगरier->parent)
		वापस 0;

	/*
	 * Proceed with checking क्रम the sub-device notअगरier's async
	 * sub-devices, and वापस the result. The error will be handled by the
	 * caller.
	 */
	subdev_notअगरier->parent = notअगरier;

	वापस v4l2_async_notअगरier_try_all_subdevs(subdev_notअगरier);
पूर्ण

/* Test all async sub-devices in a notअगरier क्रम a match. */
अटल पूर्णांक
v4l2_async_notअगरier_try_all_subdevs(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा v4l2_device *v4l2_dev =
		v4l2_async_notअगरier_find_v4l2_dev(notअगरier);
	काष्ठा v4l2_subdev *sd;

	अगर (!v4l2_dev)
		वापस 0;

again:
	list_क्रम_each_entry(sd, &subdev_list, async_list) अणु
		काष्ठा v4l2_async_subdev *asd;
		पूर्णांक ret;

		asd = v4l2_async_find_match(notअगरier, sd);
		अगर (!asd)
			जारी;

		ret = v4l2_async_match_notअगरy(notअगरier, v4l2_dev, sd, asd);
		अगर (ret < 0)
			वापस ret;

		/*
		 * v4l2_async_match_notअगरy() may lead to रेजिस्टरing a
		 * new notअगरier and thus changing the async subdevs
		 * list. In order to proceed safely from here, restart
		 * parsing the list from the beginning.
		 */
		जाओ again;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम v4l2_async_cleanup(काष्ठा v4l2_subdev *sd)
अणु
	v4l2_device_unरेजिस्टर_subdev(sd);
	/*
	 * Subdevice driver will reprobe and put the subdev back
	 * onto the list
	 */
	list_del_init(&sd->async_list);
	sd->asd = शून्य;
पूर्ण

/* Unbind all sub-devices in the notअगरier tree. */
अटल व्योम
v4l2_async_notअगरier_unbind_all_subdevs(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा v4l2_subdev *sd, *पंचांगp;

	list_क्रम_each_entry_safe(sd, पंचांगp, &notअगरier->करोne, async_list) अणु
		काष्ठा v4l2_async_notअगरier *subdev_notअगरier =
			v4l2_async_find_subdev_notअगरier(sd);

		अगर (subdev_notअगरier)
			v4l2_async_notअगरier_unbind_all_subdevs(subdev_notअगरier);

		v4l2_async_notअगरier_call_unbind(notअगरier, sd, sd->asd);
		v4l2_async_cleanup(sd);

		list_move(&sd->async_list, &subdev_list);
	पूर्ण

	notअगरier->parent = शून्य;
पूर्ण

/* See अगर an async sub-device can be found in a notअगरier's lists. */
अटल bool
__v4l2_async_notअगरier_has_async_subdev(काष्ठा v4l2_async_notअगरier *notअगरier,
				       काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा v4l2_async_subdev *asd_y;
	काष्ठा v4l2_subdev *sd;

	list_क्रम_each_entry(asd_y, &notअगरier->रुकोing, list)
		अगर (asd_equal(asd, asd_y))
			वापस true;

	list_क्रम_each_entry(sd, &notअगरier->करोne, async_list) अणु
		अगर (WARN_ON(!sd->asd))
			जारी;

		अगर (asd_equal(asd, sd->asd))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Find out whether an async sub-device was set up alपढ़ोy or
 * whether it exists in a given notअगरier beक्रमe @this_index.
 * If @this_index < 0, search the notअगरier's entire @asd_list.
 */
अटल bool
v4l2_async_notअगरier_has_async_subdev(काष्ठा v4l2_async_notअगरier *notअगरier,
				     काष्ठा v4l2_async_subdev *asd,
				     पूर्णांक this_index)
अणु
	काष्ठा v4l2_async_subdev *asd_y;
	पूर्णांक j = 0;

	lockdep_निश्चित_held(&list_lock);

	/* Check that an asd is not being added more than once. */
	list_क्रम_each_entry(asd_y, &notअगरier->asd_list, asd_list) अणु
		अगर (this_index >= 0 && j++ >= this_index)
			अवरोध;
		अगर (asd_equal(asd, asd_y))
			वापस true;
	पूर्ण

	/* Check that an asd करोes not exist in other notअगरiers. */
	list_क्रम_each_entry(notअगरier, &notअगरier_list, list)
		अगर (__v4l2_async_notअगरier_has_async_subdev(notअगरier, asd))
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक v4l2_async_notअगरier_asd_valid(काष्ठा v4l2_async_notअगरier *notअगरier,
					 काष्ठा v4l2_async_subdev *asd,
					 पूर्णांक this_index)
अणु
	काष्ठा device *dev =
		notअगरier->v4l2_dev ? notअगरier->v4l2_dev->dev : शून्य;

	अगर (!asd)
		वापस -EINVAL;

	चयन (asd->match_type) अणु
	हाल V4L2_ASYNC_MATCH_I2C:
	हाल V4L2_ASYNC_MATCH_FWNODE:
		अगर (v4l2_async_notअगरier_has_async_subdev(notअगरier, asd,
							 this_index)) अणु
			dev_dbg(dev, "subdev descriptor already listed in this or other notifiers\n");
			वापस -EEXIST;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(dev, "Invalid match type %u on %p\n",
			asd->match_type, asd);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम v4l2_async_notअगरier_init(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	INIT_LIST_HEAD(&notअगरier->asd_list);
पूर्ण
EXPORT_SYMBOL(v4l2_async_notअगरier_init);

अटल पूर्णांक __v4l2_async_notअगरier_रेजिस्टर(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा v4l2_async_subdev *asd;
	पूर्णांक ret, i = 0;

	INIT_LIST_HEAD(&notअगरier->रुकोing);
	INIT_LIST_HEAD(&notअगरier->करोne);

	mutex_lock(&list_lock);

	list_क्रम_each_entry(asd, &notअगरier->asd_list, asd_list) अणु
		ret = v4l2_async_notअगरier_asd_valid(notअगरier, asd, i++);
		अगर (ret)
			जाओ err_unlock;

		list_add_tail(&asd->list, &notअगरier->रुकोing);
	पूर्ण

	ret = v4l2_async_notअगरier_try_all_subdevs(notअगरier);
	अगर (ret < 0)
		जाओ err_unbind;

	ret = v4l2_async_notअगरier_try_complete(notअगरier);
	अगर (ret < 0)
		जाओ err_unbind;

	/* Keep also completed notअगरiers on the list */
	list_add(&notअगरier->list, &notअगरier_list);

	mutex_unlock(&list_lock);

	वापस 0;

err_unbind:
	/*
	 * On failure, unbind all sub-devices रेजिस्टरed through this notअगरier.
	 */
	v4l2_async_notअगरier_unbind_all_subdevs(notअगरier);

err_unlock:
	mutex_unlock(&list_lock);

	वापस ret;
पूर्ण

पूर्णांक v4l2_async_notअगरier_रेजिस्टर(काष्ठा v4l2_device *v4l2_dev,
				 काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	पूर्णांक ret;

	अगर (WARN_ON(!v4l2_dev || notअगरier->sd))
		वापस -EINVAL;

	notअगरier->v4l2_dev = v4l2_dev;

	ret = __v4l2_async_notअगरier_रेजिस्टर(notअगरier);
	अगर (ret)
		notअगरier->v4l2_dev = शून्य;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(v4l2_async_notअगरier_रेजिस्टर);

पूर्णांक v4l2_async_subdev_notअगरier_रेजिस्टर(काष्ठा v4l2_subdev *sd,
					काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	पूर्णांक ret;

	अगर (WARN_ON(!sd || notअगरier->v4l2_dev))
		वापस -EINVAL;

	notअगरier->sd = sd;

	ret = __v4l2_async_notअगरier_रेजिस्टर(notअगरier);
	अगर (ret)
		notअगरier->sd = शून्य;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(v4l2_async_subdev_notअगरier_रेजिस्टर);

अटल व्योम
__v4l2_async_notअगरier_unरेजिस्टर(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	अगर (!notअगरier || (!notअगरier->v4l2_dev && !notअगरier->sd))
		वापस;

	v4l2_async_notअगरier_unbind_all_subdevs(notअगरier);

	notअगरier->sd = शून्य;
	notअगरier->v4l2_dev = शून्य;

	list_del(&notअगरier->list);
पूर्ण

व्योम v4l2_async_notअगरier_unरेजिस्टर(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	mutex_lock(&list_lock);

	__v4l2_async_notअगरier_unरेजिस्टर(notअगरier);

	mutex_unlock(&list_lock);
पूर्ण
EXPORT_SYMBOL(v4l2_async_notअगरier_unरेजिस्टर);

अटल व्योम __v4l2_async_notअगरier_cleanup(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा v4l2_async_subdev *asd, *पंचांगp;

	अगर (!notअगरier || !notअगरier->asd_list.next)
		वापस;

	list_क्रम_each_entry_safe(asd, पंचांगp, &notअगरier->asd_list, asd_list) अणु
		चयन (asd->match_type) अणु
		हाल V4L2_ASYNC_MATCH_FWNODE:
			fwnode_handle_put(asd->match.fwnode);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		list_del(&asd->asd_list);
		kमुक्त(asd);
	पूर्ण
पूर्ण

व्योम v4l2_async_notअगरier_cleanup(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	mutex_lock(&list_lock);

	__v4l2_async_notअगरier_cleanup(notअगरier);

	mutex_unlock(&list_lock);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_async_notअगरier_cleanup);

पूर्णांक __v4l2_async_notअगरier_add_subdev(काष्ठा v4l2_async_notअगरier *notअगरier,
				   काष्ठा v4l2_async_subdev *asd)
अणु
	पूर्णांक ret;

	mutex_lock(&list_lock);

	ret = v4l2_async_notअगरier_asd_valid(notअगरier, asd, -1);
	अगर (ret)
		जाओ unlock;

	list_add_tail(&asd->asd_list, &notअगरier->asd_list);

unlock:
	mutex_unlock(&list_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__v4l2_async_notअगरier_add_subdev);

काष्ठा v4l2_async_subdev *
__v4l2_async_notअगरier_add_fwnode_subdev(काष्ठा v4l2_async_notअगरier *notअगरier,
					काष्ठा fwnode_handle *fwnode,
					अचिन्हित पूर्णांक asd_काष्ठा_size)
अणु
	काष्ठा v4l2_async_subdev *asd;
	पूर्णांक ret;

	asd = kzalloc(asd_काष्ठा_size, GFP_KERNEL);
	अगर (!asd)
		वापस ERR_PTR(-ENOMEM);

	asd->match_type = V4L2_ASYNC_MATCH_FWNODE;
	asd->match.fwnode = fwnode_handle_get(fwnode);

	ret = __v4l2_async_notअगरier_add_subdev(notअगरier, asd);
	अगर (ret) अणु
		fwnode_handle_put(fwnode);
		kमुक्त(asd);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस asd;
पूर्ण
EXPORT_SYMBOL_GPL(__v4l2_async_notअगरier_add_fwnode_subdev);

काष्ठा v4l2_async_subdev *
__v4l2_async_notअगरier_add_fwnode_remote_subdev(काष्ठा v4l2_async_notअगरier *notअगर,
					       काष्ठा fwnode_handle *endpoपूर्णांक,
					       अचिन्हित पूर्णांक asd_काष्ठा_size)
अणु
	काष्ठा v4l2_async_subdev *asd;
	काष्ठा fwnode_handle *remote;

	remote = fwnode_graph_get_remote_port_parent(endpoपूर्णांक);
	अगर (!remote)
		वापस ERR_PTR(-ENOTCONN);

	asd = __v4l2_async_notअगरier_add_fwnode_subdev(notअगर, remote,
						      asd_काष्ठा_size);
	/*
	 * Calling __v4l2_async_notअगरier_add_fwnode_subdev grअसल a refcount,
	 * so drop the one we got in fwnode_graph_get_remote_port_parent.
	 */
	fwnode_handle_put(remote);
	वापस asd;
पूर्ण
EXPORT_SYMBOL_GPL(__v4l2_async_notअगरier_add_fwnode_remote_subdev);

काष्ठा v4l2_async_subdev *
__v4l2_async_notअगरier_add_i2c_subdev(काष्ठा v4l2_async_notअगरier *notअगरier,
				     पूर्णांक adapter_id, अचिन्हित लघु address,
				     अचिन्हित पूर्णांक asd_काष्ठा_size)
अणु
	काष्ठा v4l2_async_subdev *asd;
	पूर्णांक ret;

	asd = kzalloc(asd_काष्ठा_size, GFP_KERNEL);
	अगर (!asd)
		वापस ERR_PTR(-ENOMEM);

	asd->match_type = V4L2_ASYNC_MATCH_I2C;
	asd->match.i2c.adapter_id = adapter_id;
	asd->match.i2c.address = address;

	ret = __v4l2_async_notअगरier_add_subdev(notअगरier, asd);
	अगर (ret) अणु
		kमुक्त(asd);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस asd;
पूर्ण
EXPORT_SYMBOL_GPL(__v4l2_async_notअगरier_add_i2c_subdev);

पूर्णांक v4l2_async_रेजिस्टर_subdev(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा v4l2_async_notअगरier *subdev_notअगरier;
	काष्ठा v4l2_async_notअगरier *notअगरier;
	पूर्णांक ret;

	/*
	 * No reference taken. The reference is held by the device
	 * (काष्ठा v4l2_subdev.dev), and async sub-device करोes not
	 * exist independently of the device at any poपूर्णांक of समय.
	 */
	अगर (!sd->fwnode && sd->dev)
		sd->fwnode = dev_fwnode(sd->dev);

	mutex_lock(&list_lock);

	INIT_LIST_HEAD(&sd->async_list);

	list_क्रम_each_entry(notअगरier, &notअगरier_list, list) अणु
		काष्ठा v4l2_device *v4l2_dev =
			v4l2_async_notअगरier_find_v4l2_dev(notअगरier);
		काष्ठा v4l2_async_subdev *asd;

		अगर (!v4l2_dev)
			जारी;

		asd = v4l2_async_find_match(notअगरier, sd);
		अगर (!asd)
			जारी;

		ret = v4l2_async_match_notअगरy(notअगरier, v4l2_dev, sd, asd);
		अगर (ret)
			जाओ err_unbind;

		ret = v4l2_async_notअगरier_try_complete(notअगरier);
		अगर (ret)
			जाओ err_unbind;

		जाओ out_unlock;
	पूर्ण

	/* None matched, रुको क्रम hot-plugging */
	list_add(&sd->async_list, &subdev_list);

out_unlock:
	mutex_unlock(&list_lock);

	वापस 0;

err_unbind:
	/*
	 * Complete failed. Unbind the sub-devices bound through रेजिस्टरing
	 * this async sub-device.
	 */
	subdev_notअगरier = v4l2_async_find_subdev_notअगरier(sd);
	अगर (subdev_notअगरier)
		v4l2_async_notअगरier_unbind_all_subdevs(subdev_notअगरier);

	अगर (sd->asd)
		v4l2_async_notअगरier_call_unbind(notअगरier, sd, sd->asd);
	v4l2_async_cleanup(sd);

	mutex_unlock(&list_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(v4l2_async_रेजिस्टर_subdev);

व्योम v4l2_async_unरेजिस्टर_subdev(काष्ठा v4l2_subdev *sd)
अणु
	अगर (!sd->async_list.next)
		वापस;

	mutex_lock(&list_lock);

	__v4l2_async_notअगरier_unरेजिस्टर(sd->subdev_notअगरier);
	__v4l2_async_notअगरier_cleanup(sd->subdev_notअगरier);
	kमुक्त(sd->subdev_notअगरier);
	sd->subdev_notअगरier = शून्य;

	अगर (sd->asd) अणु
		काष्ठा v4l2_async_notअगरier *notअगरier = sd->notअगरier;

		list_add(&sd->asd->list, &notअगरier->रुकोing);

		v4l2_async_notअगरier_call_unbind(notअगरier, sd, sd->asd);
	पूर्ण

	v4l2_async_cleanup(sd);

	mutex_unlock(&list_lock);
पूर्ण
EXPORT_SYMBOL(v4l2_async_unरेजिस्टर_subdev);

अटल व्योम prपूर्णांक_रुकोing_subdev(काष्ठा seq_file *s,
				 काष्ठा v4l2_async_subdev *asd)
अणु
	चयन (asd->match_type) अणु
	हाल V4L2_ASYNC_MATCH_I2C:
		seq_म_लिखो(s, " [i2c] dev=%d-%04x\n", asd->match.i2c.adapter_id,
			   asd->match.i2c.address);
		अवरोध;
	हाल V4L2_ASYNC_MATCH_FWNODE: अणु
		काष्ठा fwnode_handle *devnode, *fwnode = asd->match.fwnode;

		devnode = fwnode_graph_is_endpoपूर्णांक(fwnode) ?
			  fwnode_graph_get_port_parent(fwnode) :
			  fwnode_handle_get(fwnode);

		seq_म_लिखो(s, " [fwnode] dev=%s, node=%pfw\n",
			   devnode->dev ? dev_name(devnode->dev) : "nil",
			   fwnode);

		fwnode_handle_put(devnode);
		अवरोध;
	पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *
v4l2_async_notअगरier_name(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	अगर (notअगरier->v4l2_dev)
		वापस notअगरier->v4l2_dev->name;
	अन्यथा अगर (notअगरier->sd)
		वापस notअगरier->sd->name;
	अन्यथा
		वापस "nil";
पूर्ण

अटल पूर्णांक pending_subdevs_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा v4l2_async_notअगरier *notअगर;
	काष्ठा v4l2_async_subdev *asd;

	mutex_lock(&list_lock);

	list_क्रम_each_entry(notअगर, &notअगरier_list, list) अणु
		seq_म_लिखो(s, "%s:\n", v4l2_async_notअगरier_name(notअगर));
		list_क्रम_each_entry(asd, &notअगर->रुकोing, list)
			prपूर्णांक_रुकोing_subdev(s, asd);
	पूर्ण

	mutex_unlock(&list_lock);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(pending_subdevs);

व्योम v4l2_async_debug_init(काष्ठा dentry *debugfs_dir)
अणु
	debugfs_create_file("pending_async_subdevices", 0444, debugfs_dir, शून्य,
			    &pending_subdevs_fops);
पूर्ण
