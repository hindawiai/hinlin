<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2020 Linaro Limited
 *
 * Author: Daniel Lezcano <daniel.lezcano@linaro.org>
 *
 * The घातercap based Dynamic Thermal Power Management framework
 * provides to the userspace a consistent API to set the घातer limit
 * on some devices.
 *
 * DTPM defines the functions to create a tree of स्थिरraपूर्णांकs. Each
 * parent node is a भव description of the aggregation of the
 * children. It propagates the स्थिरraपूर्णांकs set at its level to its
 * children and collect the children घातer inक्रमmation. The leaves of
 * the tree are the real devices which have the ability to get their
 * current घातer consumption and set their घातer limit.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/dtpm.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/घातercap.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>

#घोषणा DTPM_POWER_LIMIT_FLAG 0

अटल स्थिर अक्षर *स्थिरraपूर्णांक_name[] = अणु
	"Instantaneous",
पूर्ण;

अटल DEFINE_MUTEX(dtpm_lock);
अटल काष्ठा घातercap_control_type *pct;
अटल काष्ठा dtpm *root;

अटल पूर्णांक get_समय_winकरोw_us(काष्ठा घातercap_zone *pcz, पूर्णांक cid, u64 *winकरोw)
अणु
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक set_समय_winकरोw_us(काष्ठा घातercap_zone *pcz, पूर्णांक cid, u64 winकरोw)
अणु
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक get_max_घातer_range_uw(काष्ठा घातercap_zone *pcz, u64 *max_घातer_uw)
अणु
	काष्ठा dtpm *dtpm = to_dtpm(pcz);

	mutex_lock(&dtpm_lock);
	*max_घातer_uw = dtpm->घातer_max - dtpm->घातer_min;
	mutex_unlock(&dtpm_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक __get_घातer_uw(काष्ठा dtpm *dtpm, u64 *घातer_uw)
अणु
	काष्ठा dtpm *child;
	u64 घातer;
	पूर्णांक ret = 0;

	अगर (dtpm->ops) अणु
		*घातer_uw = dtpm->ops->get_घातer_uw(dtpm);
		वापस 0;
	पूर्ण

	*घातer_uw = 0;

	list_क्रम_each_entry(child, &dtpm->children, sibling) अणु
		ret = __get_घातer_uw(child, &घातer);
		अगर (ret)
			अवरोध;
		*घातer_uw += घातer;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक get_घातer_uw(काष्ठा घातercap_zone *pcz, u64 *घातer_uw)
अणु
	काष्ठा dtpm *dtpm = to_dtpm(pcz);
	पूर्णांक ret;

	mutex_lock(&dtpm_lock);
	ret = __get_घातer_uw(dtpm, घातer_uw);
	mutex_unlock(&dtpm_lock);

	वापस ret;
पूर्ण

अटल व्योम __dtpm_rebalance_weight(काष्ठा dtpm *dtpm)
अणु
	काष्ठा dtpm *child;

	list_क्रम_each_entry(child, &dtpm->children, sibling) अणु

		pr_debug("Setting weight '%d' for '%s'\n",
			 child->weight, child->zone.name);

		child->weight = DIV64_U64_ROUND_CLOSEST(
			child->घातer_max * 1024, dtpm->घातer_max);

		__dtpm_rebalance_weight(child);
	पूर्ण
पूर्ण

अटल व्योम __dtpm_sub_घातer(काष्ठा dtpm *dtpm)
अणु
	काष्ठा dtpm *parent = dtpm->parent;

	जबतक (parent) अणु
		parent->घातer_min -= dtpm->घातer_min;
		parent->घातer_max -= dtpm->घातer_max;
		parent->घातer_limit -= dtpm->घातer_limit;
		parent = parent->parent;
	पूर्ण

	__dtpm_rebalance_weight(root);
पूर्ण

अटल व्योम __dtpm_add_घातer(काष्ठा dtpm *dtpm)
अणु
	काष्ठा dtpm *parent = dtpm->parent;

	जबतक (parent) अणु
		parent->घातer_min += dtpm->घातer_min;
		parent->घातer_max += dtpm->घातer_max;
		parent->घातer_limit += dtpm->घातer_limit;
		parent = parent->parent;
	पूर्ण

	__dtpm_rebalance_weight(root);
पूर्ण

/**
 * dtpm_update_घातer - Update the घातer on the dtpm
 * @dtpm: a poपूर्णांकer to a dtpm काष्ठाure to update
 * @घातer_min: a u64 representing the new घातer_min value
 * @घातer_max: a u64 representing the new घातer_max value
 *
 * Function to update the घातer values of the dtpm node specअगरied in
 * parameter. These new values will be propagated to the tree.
 *
 * Return: zero on success, -EINVAL अगर the values are inconsistent
 */
पूर्णांक dtpm_update_घातer(काष्ठा dtpm *dtpm, u64 घातer_min, u64 घातer_max)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&dtpm_lock);

	अगर (घातer_min == dtpm->घातer_min && घातer_max == dtpm->घातer_max)
		जाओ unlock;

	अगर (घातer_max < घातer_min) अणु
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	__dtpm_sub_घातer(dtpm);

	dtpm->घातer_min = घातer_min;
	dtpm->घातer_max = घातer_max;
	अगर (!test_bit(DTPM_POWER_LIMIT_FLAG, &dtpm->flags))
		dtpm->घातer_limit = घातer_max;

	__dtpm_add_घातer(dtpm);

unlock:
	mutex_unlock(&dtpm_lock);

	वापस ret;
पूर्ण

/**
 * dtpm_release_zone - Cleanup when the node is released
 * @pcz: a poपूर्णांकer to a घातercap_zone काष्ठाure
 *
 * Do some housecleaning and update the weight on the tree. The
 * release will be denied अगर the node has children. This function must
 * be called by the specअगरic release callback of the dअगरferent
 * backends.
 *
 * Return: 0 on success, -EBUSY अगर there are children
 */
पूर्णांक dtpm_release_zone(काष्ठा घातercap_zone *pcz)
अणु
	काष्ठा dtpm *dtpm = to_dtpm(pcz);
	काष्ठा dtpm *parent = dtpm->parent;

	mutex_lock(&dtpm_lock);

	अगर (!list_empty(&dtpm->children)) अणु
		mutex_unlock(&dtpm_lock);
		वापस -EBUSY;
	पूर्ण

	अगर (parent)
		list_del(&dtpm->sibling);

	__dtpm_sub_घातer(dtpm);

	mutex_unlock(&dtpm_lock);

	अगर (dtpm->ops)
		dtpm->ops->release(dtpm);

	अगर (root == dtpm)
		root = शून्य;

	kमुक्त(dtpm);

	वापस 0;
पूर्ण

अटल पूर्णांक __get_घातer_limit_uw(काष्ठा dtpm *dtpm, पूर्णांक cid, u64 *घातer_limit)
अणु
	*घातer_limit = dtpm->घातer_limit;
	वापस 0;
पूर्ण

अटल पूर्णांक get_घातer_limit_uw(काष्ठा घातercap_zone *pcz,
			      पूर्णांक cid, u64 *घातer_limit)
अणु
	काष्ठा dtpm *dtpm = to_dtpm(pcz);
	पूर्णांक ret;

	mutex_lock(&dtpm_lock);
	ret = __get_घातer_limit_uw(dtpm, cid, घातer_limit);
	mutex_unlock(&dtpm_lock);

	वापस ret;
पूर्ण

/*
 * Set the घातer limit on the nodes, the घातer limit is distributed
 * given the weight of the children.
 *
 * The dtpm node lock must be held when calling this function.
 */
अटल पूर्णांक __set_घातer_limit_uw(काष्ठा dtpm *dtpm, पूर्णांक cid, u64 घातer_limit)
अणु
	काष्ठा dtpm *child;
	पूर्णांक ret = 0;
	u64 घातer;

	/*
	 * A max घातer limitation means we हटाओ the घातer limit,
	 * otherwise we set a स्थिरraपूर्णांक and flag the dtpm node.
	 */
	अगर (घातer_limit == dtpm->घातer_max) अणु
		clear_bit(DTPM_POWER_LIMIT_FLAG, &dtpm->flags);
	पूर्ण अन्यथा अणु
		set_bit(DTPM_POWER_LIMIT_FLAG, &dtpm->flags);
	पूर्ण

	pr_debug("Setting power limit for '%s': %llu uW\n",
		 dtpm->zone.name, घातer_limit);

	/*
	 * Only leaves of the dtpm tree has ops to get/set the घातer
	 */
	अगर (dtpm->ops) अणु
		dtpm->घातer_limit = dtpm->ops->set_घातer_uw(dtpm, घातer_limit);
	पूर्ण अन्यथा अणु
		dtpm->घातer_limit = 0;

		list_क्रम_each_entry(child, &dtpm->children, sibling) अणु

			/*
			 * Integer भागision rounding will inevitably
			 * lead to a dअगरferent min or max value when
			 * set several बार. In order to restore the
			 * initial value, we क्रमce the child's min or
			 * max घातer every समय अगर the स्थिरraपूर्णांक is
			 * at the boundaries.
			 */
			अगर (घातer_limit == dtpm->घातer_max) अणु
				घातer = child->घातer_max;
			पूर्ण अन्यथा अगर (घातer_limit == dtpm->घातer_min) अणु
				घातer = child->घातer_min;
			पूर्ण अन्यथा अणु
				घातer = DIV_ROUND_CLOSEST_ULL(
					घातer_limit * child->weight, 1024);
			पूर्ण

			pr_debug("Setting power limit for '%s': %llu uW\n",
				 child->zone.name, घातer);

			ret = __set_घातer_limit_uw(child, cid, घातer);
			अगर (!ret)
				ret = __get_घातer_limit_uw(child, cid, &घातer);

			अगर (ret)
				अवरोध;

			dtpm->घातer_limit += घातer;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक set_घातer_limit_uw(काष्ठा घातercap_zone *pcz,
			      पूर्णांक cid, u64 घातer_limit)
अणु
	काष्ठा dtpm *dtpm = to_dtpm(pcz);
	पूर्णांक ret;

	mutex_lock(&dtpm_lock);

	/*
	 * Don't allow values outside of the घातer range previously
	 * set when initializing the घातer numbers.
	 */
	घातer_limit = clamp_val(घातer_limit, dtpm->घातer_min, dtpm->घातer_max);

	ret = __set_घातer_limit_uw(dtpm, cid, घातer_limit);

	pr_debug("%s: power limit: %llu uW, power max: %llu uW\n",
		 dtpm->zone.name, dtpm->घातer_limit, dtpm->घातer_max);

	mutex_unlock(&dtpm_lock);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *get_स्थिरraपूर्णांक_name(काष्ठा घातercap_zone *pcz, पूर्णांक cid)
अणु
	वापस स्थिरraपूर्णांक_name[cid];
पूर्ण

अटल पूर्णांक get_max_घातer_uw(काष्ठा घातercap_zone *pcz, पूर्णांक id, u64 *max_घातer)
अणु
	काष्ठा dtpm *dtpm = to_dtpm(pcz);

	mutex_lock(&dtpm_lock);
	*max_घातer = dtpm->घातer_max;
	mutex_unlock(&dtpm_lock);

	वापस 0;
पूर्ण

अटल काष्ठा घातercap_zone_स्थिरraपूर्णांक_ops स्थिरraपूर्णांक_ops = अणु
	.set_घातer_limit_uw = set_घातer_limit_uw,
	.get_घातer_limit_uw = get_घातer_limit_uw,
	.set_समय_winकरोw_us = set_समय_winकरोw_us,
	.get_समय_winकरोw_us = get_समय_winकरोw_us,
	.get_max_घातer_uw = get_max_घातer_uw,
	.get_name = get_स्थिरraपूर्णांक_name,
पूर्ण;

अटल काष्ठा घातercap_zone_ops zone_ops = अणु
	.get_max_घातer_range_uw = get_max_घातer_range_uw,
	.get_घातer_uw = get_घातer_uw,
	.release = dtpm_release_zone,
पूर्ण;

/**
 * dtpm_alloc - Allocate and initialize a dtpm काष्ठा
 * @name: a string specअगरying the name of the node
 *
 * Return: a काष्ठा dtpm poपूर्णांकer, शून्य in हाल of error
 */
काष्ठा dtpm *dtpm_alloc(काष्ठा dtpm_ops *ops)
अणु
	काष्ठा dtpm *dtpm;

	dtpm = kzalloc(माप(*dtpm), GFP_KERNEL);
	अगर (dtpm) अणु
		INIT_LIST_HEAD(&dtpm->children);
		INIT_LIST_HEAD(&dtpm->sibling);
		dtpm->weight = 1024;
		dtpm->ops = ops;
	पूर्ण

	वापस dtpm;
पूर्ण

/**
 * dtpm_unरेजिस्टर - Unरेजिस्टर a dtpm node from the hierarchy tree
 * @dtpm: a poपूर्णांकer to a dtpm काष्ठाure corresponding to the node to be हटाओd
 *
 * Call the underlying घातercap unरेजिस्टर function. That will call
 * the release callback of the घातercap zone.
 */
व्योम dtpm_unरेजिस्टर(काष्ठा dtpm *dtpm)
अणु
	घातercap_unरेजिस्टर_zone(pct, &dtpm->zone);

	pr_info("Unregistered dtpm node '%s'\n", dtpm->zone.name);
पूर्ण

/**
 * dtpm_रेजिस्टर - Register a dtpm node in the hierarchy tree
 * @name: a string specअगरying the name of the node
 * @dtpm: a poपूर्णांकer to a dtpm काष्ठाure corresponding to the new node
 * @parent: a poपूर्णांकer to a dtpm काष्ठाure corresponding to the parent node
 *
 * Create a dtpm node in the tree. If no parent is specअगरied, the node
 * is the root node of the hierarchy. If the root node alपढ़ोy exists,
 * then the registration will fail. The घातercap controller must be
 * initialized beक्रमe calling this function.
 *
 * The dtpm काष्ठाure must be initialized with the घातer numbers
 * beक्रमe calling this function.
 *
 * Return: zero on success, a negative value in हाल of error:
 *  -EAGAIN: the function is called beक्रमe the framework is initialized.
 *  -EBUSY: the root node is alपढ़ोy inserted
 *  -EINVAL: * there is no root node yet and @parent is specअगरied
 *           * no all ops are defined
 *           * parent have ops which are reserved क्रम leaves
 *   Other negative values are reported back from the घातercap framework
 */
पूर्णांक dtpm_रेजिस्टर(स्थिर अक्षर *name, काष्ठा dtpm *dtpm, काष्ठा dtpm *parent)
अणु
	काष्ठा घातercap_zone *pcz;

	अगर (!pct)
		वापस -EAGAIN;

	अगर (root && !parent)
		वापस -EBUSY;

	अगर (!root && parent)
		वापस -EINVAL;

	अगर (parent && parent->ops)
		वापस -EINVAL;

	अगर (!dtpm)
		वापस -EINVAL;

	अगर (dtpm->ops && !(dtpm->ops->set_घातer_uw &&
			   dtpm->ops->get_घातer_uw &&
			   dtpm->ops->release))
		वापस -EINVAL;

	pcz = घातercap_रेजिस्टर_zone(&dtpm->zone, pct, name,
				     parent ? &parent->zone : शून्य,
				     &zone_ops, MAX_DTPM_CONSTRAINTS,
				     &स्थिरraपूर्णांक_ops);
	अगर (IS_ERR(pcz))
		वापस PTR_ERR(pcz);

	mutex_lock(&dtpm_lock);

	अगर (parent) अणु
		list_add_tail(&dtpm->sibling, &parent->children);
		dtpm->parent = parent;
	पूर्ण अन्यथा अणु
		root = dtpm;
	पूर्ण

	__dtpm_add_घातer(dtpm);

	pr_info("Registered dtpm node '%s' / %llu-%llu uW, \n",
		dtpm->zone.name, dtpm->घातer_min, dtpm->घातer_max);

	mutex_unlock(&dtpm_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक __init dtpm_init(व्योम)
अणु
	काष्ठा dtpm_descr **dtpm_descr;

	pct = घातercap_रेजिस्टर_control_type(शून्य, "dtpm", शून्य);
	अगर (IS_ERR(pct)) अणु
		pr_err("Failed to register control type\n");
		वापस PTR_ERR(pct);
	पूर्ण

	क्रम_each_dtpm_table(dtpm_descr)
		(*dtpm_descr)->init(*dtpm_descr);

	वापस 0;
पूर्ण
late_initcall(dtpm_init);
