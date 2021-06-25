<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/base/घातer/घड़ी_ops.c - Generic घड़ी manipulation PM callbacks
 *
 * Copyright (c) 2011 Rafael J. Wysocki <rjw@sisk.pl>, Renesas Electronics Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm.h>
#समावेश <linux/pm_घड़ी.h>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>

#अगर_घोषित CONFIG_PM_CLK

क्रमागत pce_status अणु
	PCE_STATUS_NONE = 0,
	PCE_STATUS_ACQUIRED,
	PCE_STATUS_PREPARED,
	PCE_STATUS_ENABLED,
	PCE_STATUS_ERROR,
पूर्ण;

काष्ठा pm_घड़ी_entry अणु
	काष्ठा list_head node;
	अक्षर *con_id;
	काष्ठा clk *clk;
	क्रमागत pce_status status;
	bool enabled_when_prepared;
पूर्ण;

/**
 * pm_clk_list_lock - ensure exclusive access क्रम modअगरying the PM घड़ी
 *		      entry list.
 * @psd: pm_subsys_data instance corresponding to the PM घड़ी entry list
 *	 and clk_op_might_sleep count to be modअगरied.
 *
 * Get exclusive access beक्रमe modअगरying the PM घड़ी entry list and the
 * घड़ी_op_might_sleep count to guard against concurrent modअगरications.
 * This also protects against a concurrent घड़ी_op_might_sleep and PM घड़ी
 * entry list usage in pm_clk_suspend()/pm_clk_resume() that may or may not
 * happen in atomic context, hence both the mutex and the spinlock must be
 * taken here.
 */
अटल व्योम pm_clk_list_lock(काष्ठा pm_subsys_data *psd)
	__acquires(&psd->lock)
अणु
	mutex_lock(&psd->घड़ी_mutex);
	spin_lock_irq(&psd->lock);
पूर्ण

/**
 * pm_clk_list_unlock - counterpart to pm_clk_list_lock().
 * @psd: the same pm_subsys_data instance previously passed to
 *	 pm_clk_list_lock().
 */
अटल व्योम pm_clk_list_unlock(काष्ठा pm_subsys_data *psd)
	__releases(&psd->lock)
अणु
	spin_unlock_irq(&psd->lock);
	mutex_unlock(&psd->घड़ी_mutex);
पूर्ण

/**
 * pm_clk_op_lock - ensure exclusive access क्रम perक्रमming घड़ी operations.
 * @psd: pm_subsys_data instance corresponding to the PM घड़ी entry list
 *	 and clk_op_might_sleep count being used.
 * @flags: stored irq flags.
 * @fn: string क्रम the caller function's name.
 *
 * This is used by pm_clk_suspend() and pm_clk_resume() to guard
 * against concurrent modअगरications to the घड़ी entry list and the
 * घड़ी_op_might_sleep count. If घड़ी_op_might_sleep is != 0 then
 * only the mutex can be locked and those functions can only be used in
 * non atomic context. If घड़ी_op_might_sleep == 0 then these functions
 * may be used in any context and only the spinlock can be locked.
 * Returns -EINVAL अगर called in atomic context when घड़ी ops might sleep.
 */
अटल पूर्णांक pm_clk_op_lock(काष्ठा pm_subsys_data *psd, अचिन्हित दीर्घ *flags,
			  स्थिर अक्षर *fn)
	/* sparse annotations करोn't work here as exit state isn't अटल */
अणु
	bool atomic_context = in_atomic() || irqs_disabled();

try_again:
	spin_lock_irqsave(&psd->lock, *flags);
	अगर (!psd->घड़ी_op_might_sleep) अणु
		/* the __release is there to work around sparse limitations */
		__release(&psd->lock);
		वापस 0;
	पूर्ण

	/* bail out अगर in atomic context */
	अगर (atomic_context) अणु
		pr_err("%s: atomic context with clock_ops_might_sleep = %d",
		       fn, psd->घड़ी_op_might_sleep);
		spin_unlock_irqrestore(&psd->lock, *flags);
		might_sleep();
		वापस -EPERM;
	पूर्ण

	/* we must चयन to the mutex */
	spin_unlock_irqrestore(&psd->lock, *flags);
	mutex_lock(&psd->घड़ी_mutex);

	/*
	 * There was a possibility क्रम psd->घड़ी_op_might_sleep
	 * to become 0 above. Keep the mutex only अगर not the हाल.
	 */
	अगर (likely(psd->घड़ी_op_might_sleep))
		वापस 0;

	mutex_unlock(&psd->घड़ी_mutex);
	जाओ try_again;
पूर्ण

/**
 * pm_clk_op_unlock - counterpart to pm_clk_op_lock().
 * @psd: the same pm_subsys_data instance previously passed to
 *	 pm_clk_op_lock().
 * @flags: irq flags provided by pm_clk_op_lock().
 */
अटल व्योम pm_clk_op_unlock(काष्ठा pm_subsys_data *psd, अचिन्हित दीर्घ *flags)
	/* sparse annotations करोn't work here as entry state isn't अटल */
अणु
	अगर (psd->घड़ी_op_might_sleep) अणु
		mutex_unlock(&psd->घड़ी_mutex);
	पूर्ण अन्यथा अणु
		/* the __acquire is there to work around sparse limitations */
		__acquire(&psd->lock);
		spin_unlock_irqrestore(&psd->lock, *flags);
	पूर्ण
पूर्ण

/**
 * __pm_clk_enable - Enable a घड़ी, reporting any errors
 * @dev: The device क्रम the given घड़ी
 * @ce: PM घड़ी entry corresponding to the घड़ी.
 */
अटल अंतरभूत व्योम __pm_clk_enable(काष्ठा device *dev, काष्ठा pm_घड़ी_entry *ce)
अणु
	पूर्णांक ret;

	चयन (ce->status) अणु
	हाल PCE_STATUS_ACQUIRED:
		ret = clk_prepare_enable(ce->clk);
		अवरोध;
	हाल PCE_STATUS_PREPARED:
		ret = clk_enable(ce->clk);
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	अगर (!ret)
		ce->status = PCE_STATUS_ENABLED;
	अन्यथा
		dev_err(dev, "%s: failed to enable clk %p, error %d\n",
			__func__, ce->clk, ret);
पूर्ण

/**
 * pm_clk_acquire - Acquire a device घड़ी.
 * @dev: Device whose घड़ी is to be acquired.
 * @ce: PM घड़ी entry corresponding to the घड़ी.
 */
अटल व्योम pm_clk_acquire(काष्ठा device *dev, काष्ठा pm_घड़ी_entry *ce)
अणु
	अगर (!ce->clk)
		ce->clk = clk_get(dev, ce->con_id);
	अगर (IS_ERR(ce->clk)) अणु
		ce->status = PCE_STATUS_ERROR;
		वापस;
	पूर्ण अन्यथा अगर (clk_is_enabled_when_prepared(ce->clk)) अणु
		/* we defer preparing the घड़ी in that हाल */
		ce->status = PCE_STATUS_ACQUIRED;
		ce->enabled_when_prepared = true;
	पूर्ण अन्यथा अगर (clk_prepare(ce->clk)) अणु
		ce->status = PCE_STATUS_ERROR;
		dev_err(dev, "clk_prepare() failed\n");
		वापस;
	पूर्ण अन्यथा अणु
		ce->status = PCE_STATUS_PREPARED;
	पूर्ण
	dev_dbg(dev, "Clock %pC con_id %s managed by runtime PM.\n",
		ce->clk, ce->con_id);
पूर्ण

अटल पूर्णांक __pm_clk_add(काष्ठा device *dev, स्थिर अक्षर *con_id,
			काष्ठा clk *clk)
अणु
	काष्ठा pm_subsys_data *psd = dev_to_psd(dev);
	काष्ठा pm_घड़ी_entry *ce;

	अगर (!psd)
		वापस -EINVAL;

	ce = kzalloc(माप(*ce), GFP_KERNEL);
	अगर (!ce)
		वापस -ENOMEM;

	अगर (con_id) अणु
		ce->con_id = kstrdup(con_id, GFP_KERNEL);
		अगर (!ce->con_id) अणु
			kमुक्त(ce);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (IS_ERR(clk)) अणु
			kमुक्त(ce);
			वापस -ENOENT;
		पूर्ण
		ce->clk = clk;
	पूर्ण

	pm_clk_acquire(dev, ce);

	pm_clk_list_lock(psd);
	list_add_tail(&ce->node, &psd->घड़ी_list);
	अगर (ce->enabled_when_prepared)
		psd->घड़ी_op_might_sleep++;
	pm_clk_list_unlock(psd);
	वापस 0;
पूर्ण

/**
 * pm_clk_add - Start using a device घड़ी क्रम घातer management.
 * @dev: Device whose घड़ी is going to be used क्रम घातer management.
 * @con_id: Connection ID of the घड़ी.
 *
 * Add the घड़ी represented by @con_id to the list of घड़ीs used क्रम
 * the घातer management of @dev.
 */
पूर्णांक pm_clk_add(काष्ठा device *dev, स्थिर अक्षर *con_id)
अणु
	वापस __pm_clk_add(dev, con_id, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(pm_clk_add);

/**
 * pm_clk_add_clk - Start using a device घड़ी क्रम घातer management.
 * @dev: Device whose घड़ी is going to be used क्रम घातer management.
 * @clk: Clock poपूर्णांकer
 *
 * Add the घड़ी to the list of घड़ीs used क्रम the घातer management of @dev.
 * The घातer-management code will take control of the घड़ी reference, so
 * callers should not call clk_put() on @clk after this function sucessfully
 * वापसed.
 */
पूर्णांक pm_clk_add_clk(काष्ठा device *dev, काष्ठा clk *clk)
अणु
	वापस __pm_clk_add(dev, शून्य, clk);
पूर्ण
EXPORT_SYMBOL_GPL(pm_clk_add_clk);


/**
 * of_pm_clk_add_clk - Start using a device घड़ी क्रम घातer management.
 * @dev: Device whose घड़ी is going to be used क्रम घातer management.
 * @name: Name of घड़ी that is going to be used क्रम घातer management.
 *
 * Add the घड़ी described in the 'clocks' device-tree node that matches
 * with the 'name' provided, to the list of घड़ीs used क्रम the घातer
 * management of @dev. On success, वापसs 0. Returns a negative error
 * code अगर the घड़ी is not found or cannot be added.
 */
पूर्णांक of_pm_clk_add_clk(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा clk *clk;
	पूर्णांक ret;

	अगर (!dev || !dev->of_node || !name)
		वापस -EINVAL;

	clk = of_clk_get_by_name(dev->of_node, name);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	ret = pm_clk_add_clk(dev, clk);
	अगर (ret) अणु
		clk_put(clk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_pm_clk_add_clk);

/**
 * of_pm_clk_add_clks - Start using device घड़ी(s) क्रम घातer management.
 * @dev: Device whose घड़ी(s) is going to be used क्रम घातer management.
 *
 * Add a series of घड़ीs described in the 'clocks' device-tree node क्रम
 * a device to the list of घड़ीs used क्रम the घातer management of @dev.
 * On success, वापसs the number of घड़ीs added. Returns a negative
 * error code अगर there are no घड़ीs in the device node क्रम the device
 * or अगर adding a घड़ी fails.
 */
पूर्णांक of_pm_clk_add_clks(काष्ठा device *dev)
अणु
	काष्ठा clk **clks;
	पूर्णांक i, count;
	पूर्णांक ret;

	अगर (!dev || !dev->of_node)
		वापस -EINVAL;

	count = of_clk_get_parent_count(dev->of_node);
	अगर (count <= 0)
		वापस -ENODEV;

	clks = kसुस्मृति(count, माप(*clks), GFP_KERNEL);
	अगर (!clks)
		वापस -ENOMEM;

	क्रम (i = 0; i < count; i++) अणु
		clks[i] = of_clk_get(dev->of_node, i);
		अगर (IS_ERR(clks[i])) अणु
			ret = PTR_ERR(clks[i]);
			जाओ error;
		पूर्ण

		ret = pm_clk_add_clk(dev, clks[i]);
		अगर (ret) अणु
			clk_put(clks[i]);
			जाओ error;
		पूर्ण
	पूर्ण

	kमुक्त(clks);

	वापस i;

error:
	जबतक (i--)
		pm_clk_हटाओ_clk(dev, clks[i]);

	kमुक्त(clks);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(of_pm_clk_add_clks);

/**
 * __pm_clk_हटाओ - Destroy PM घड़ी entry.
 * @ce: PM घड़ी entry to destroy.
 */
अटल व्योम __pm_clk_हटाओ(काष्ठा pm_घड़ी_entry *ce)
अणु
	अगर (!ce)
		वापस;

	चयन (ce->status) अणु
	हाल PCE_STATUS_ENABLED:
		clk_disable(ce->clk);
		fallthrough;
	हाल PCE_STATUS_PREPARED:
		clk_unprepare(ce->clk);
		fallthrough;
	हाल PCE_STATUS_ACQUIRED:
	हाल PCE_STATUS_ERROR:
		अगर (!IS_ERR(ce->clk))
			clk_put(ce->clk);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	kमुक्त(ce->con_id);
	kमुक्त(ce);
पूर्ण

/**
 * pm_clk_हटाओ - Stop using a device घड़ी क्रम घातer management.
 * @dev: Device whose घड़ी should not be used क्रम PM any more.
 * @con_id: Connection ID of the घड़ी.
 *
 * Remove the घड़ी represented by @con_id from the list of घड़ीs used क्रम
 * the घातer management of @dev.
 */
व्योम pm_clk_हटाओ(काष्ठा device *dev, स्थिर अक्षर *con_id)
अणु
	काष्ठा pm_subsys_data *psd = dev_to_psd(dev);
	काष्ठा pm_घड़ी_entry *ce;

	अगर (!psd)
		वापस;

	pm_clk_list_lock(psd);

	list_क्रम_each_entry(ce, &psd->घड़ी_list, node) अणु
		अगर (!con_id && !ce->con_id)
			जाओ हटाओ;
		अन्यथा अगर (!con_id || !ce->con_id)
			जारी;
		अन्यथा अगर (!म_भेद(con_id, ce->con_id))
			जाओ हटाओ;
	पूर्ण

	pm_clk_list_unlock(psd);
	वापस;

 हटाओ:
	list_del(&ce->node);
	अगर (ce->enabled_when_prepared)
		psd->घड़ी_op_might_sleep--;
	pm_clk_list_unlock(psd);

	__pm_clk_हटाओ(ce);
पूर्ण
EXPORT_SYMBOL_GPL(pm_clk_हटाओ);

/**
 * pm_clk_हटाओ_clk - Stop using a device घड़ी क्रम घातer management.
 * @dev: Device whose घड़ी should not be used क्रम PM any more.
 * @clk: Clock poपूर्णांकer
 *
 * Remove the घड़ी poपूर्णांकed to by @clk from the list of घड़ीs used क्रम
 * the घातer management of @dev.
 */
व्योम pm_clk_हटाओ_clk(काष्ठा device *dev, काष्ठा clk *clk)
अणु
	काष्ठा pm_subsys_data *psd = dev_to_psd(dev);
	काष्ठा pm_घड़ी_entry *ce;

	अगर (!psd || !clk)
		वापस;

	pm_clk_list_lock(psd);

	list_क्रम_each_entry(ce, &psd->घड़ी_list, node) अणु
		अगर (clk == ce->clk)
			जाओ हटाओ;
	पूर्ण

	pm_clk_list_unlock(psd);
	वापस;

 हटाओ:
	list_del(&ce->node);
	अगर (ce->enabled_when_prepared)
		psd->घड़ी_op_might_sleep--;
	pm_clk_list_unlock(psd);

	__pm_clk_हटाओ(ce);
पूर्ण
EXPORT_SYMBOL_GPL(pm_clk_हटाओ_clk);

/**
 * pm_clk_init - Initialize a device's list of घातer management घड़ीs.
 * @dev: Device to initialize the list of PM घड़ीs क्रम.
 *
 * Initialize the lock and घड़ी_list members of the device's pm_subsys_data
 * object, set the count of घड़ीs that might sleep to 0.
 */
व्योम pm_clk_init(काष्ठा device *dev)
अणु
	काष्ठा pm_subsys_data *psd = dev_to_psd(dev);
	अगर (psd) अणु
		INIT_LIST_HEAD(&psd->घड़ी_list);
		mutex_init(&psd->घड़ी_mutex);
		psd->घड़ी_op_might_sleep = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(pm_clk_init);

/**
 * pm_clk_create - Create and initialize a device's list of PM घड़ीs.
 * @dev: Device to create and initialize the list of PM घड़ीs क्रम.
 *
 * Allocate a काष्ठा pm_subsys_data object, initialize its lock and घड़ी_list
 * members and make the @dev's घातer.subsys_data field poपूर्णांक to it.
 */
पूर्णांक pm_clk_create(काष्ठा device *dev)
अणु
	वापस dev_pm_get_subsys_data(dev);
पूर्ण
EXPORT_SYMBOL_GPL(pm_clk_create);

/**
 * pm_clk_destroy - Destroy a device's list of घातer management घड़ीs.
 * @dev: Device to destroy the list of PM घड़ीs क्रम.
 *
 * Clear the @dev's घातer.subsys_data field, हटाओ the list of घड़ी entries
 * from the काष्ठा pm_subsys_data object poपूर्णांकed to by it beक्रमe and मुक्त
 * that object.
 */
व्योम pm_clk_destroy(काष्ठा device *dev)
अणु
	काष्ठा pm_subsys_data *psd = dev_to_psd(dev);
	काष्ठा pm_घड़ी_entry *ce, *c;
	काष्ठा list_head list;

	अगर (!psd)
		वापस;

	INIT_LIST_HEAD(&list);

	pm_clk_list_lock(psd);

	list_क्रम_each_entry_safe_reverse(ce, c, &psd->घड़ी_list, node)
		list_move(&ce->node, &list);
	psd->घड़ी_op_might_sleep = 0;

	pm_clk_list_unlock(psd);

	dev_pm_put_subsys_data(dev);

	list_क्रम_each_entry_safe_reverse(ce, c, &list, node) अणु
		list_del(&ce->node);
		__pm_clk_हटाओ(ce);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(pm_clk_destroy);

/**
 * pm_clk_suspend - Disable घड़ीs in a device's PM घड़ी list.
 * @dev: Device to disable the घड़ीs क्रम.
 */
पूर्णांक pm_clk_suspend(काष्ठा device *dev)
अणु
	काष्ठा pm_subsys_data *psd = dev_to_psd(dev);
	काष्ठा pm_घड़ी_entry *ce;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	dev_dbg(dev, "%s()\n", __func__);

	अगर (!psd)
		वापस 0;

	ret = pm_clk_op_lock(psd, &flags, __func__);
	अगर (ret)
		वापस ret;

	list_क्रम_each_entry_reverse(ce, &psd->घड़ी_list, node) अणु
		अगर (ce->status == PCE_STATUS_ENABLED) अणु
			अगर (ce->enabled_when_prepared) अणु
				clk_disable_unprepare(ce->clk);
				ce->status = PCE_STATUS_ACQUIRED;
			पूर्ण अन्यथा अणु
				clk_disable(ce->clk);
				ce->status = PCE_STATUS_PREPARED;
			पूर्ण
		पूर्ण
	पूर्ण

	pm_clk_op_unlock(psd, &flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_clk_suspend);

/**
 * pm_clk_resume - Enable घड़ीs in a device's PM घड़ी list.
 * @dev: Device to enable the घड़ीs क्रम.
 */
पूर्णांक pm_clk_resume(काष्ठा device *dev)
अणु
	काष्ठा pm_subsys_data *psd = dev_to_psd(dev);
	काष्ठा pm_घड़ी_entry *ce;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	dev_dbg(dev, "%s()\n", __func__);

	अगर (!psd)
		वापस 0;

	ret = pm_clk_op_lock(psd, &flags, __func__);
	अगर (ret)
		वापस ret;

	list_क्रम_each_entry(ce, &psd->घड़ी_list, node)
		__pm_clk_enable(dev, ce);

	pm_clk_op_unlock(psd, &flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_clk_resume);

/**
 * pm_clk_notअगरy - Notअगरy routine क्रम device addition and removal.
 * @nb: Notअगरier block object this function is a member of.
 * @action: Operation being carried out by the caller.
 * @data: Device the routine is being run क्रम.
 *
 * For this function to work, @nb must be a member of an object of type
 * काष्ठा pm_clk_notअगरier_block containing all of the requisite data.
 * Specअगरically, the pm_करोमुख्य member of that object is copied to the device's
 * pm_करोमुख्य field and its con_ids member is used to populate the device's list
 * of PM घड़ीs, depending on @action.
 *
 * If the device's pm_करोमुख्य field is alपढ़ोy populated with a value dअगरferent
 * from the one stored in the काष्ठा pm_clk_notअगरier_block object, the function
 * करोes nothing.
 */
अटल पूर्णांक pm_clk_notअगरy(काष्ठा notअगरier_block *nb,
				 अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा pm_clk_notअगरier_block *clknb;
	काष्ठा device *dev = data;
	अक्षर **con_id;
	पूर्णांक error;

	dev_dbg(dev, "%s() %ld\n", __func__, action);

	clknb = container_of(nb, काष्ठा pm_clk_notअगरier_block, nb);

	चयन (action) अणु
	हाल BUS_NOTIFY_ADD_DEVICE:
		अगर (dev->pm_करोमुख्य)
			अवरोध;

		error = pm_clk_create(dev);
		अगर (error)
			अवरोध;

		dev_pm_करोमुख्य_set(dev, clknb->pm_करोमुख्य);
		अगर (clknb->con_ids[0]) अणु
			क्रम (con_id = clknb->con_ids; *con_id; con_id++)
				pm_clk_add(dev, *con_id);
		पूर्ण अन्यथा अणु
			pm_clk_add(dev, शून्य);
		पूर्ण

		अवरोध;
	हाल BUS_NOTIFY_DEL_DEVICE:
		अगर (dev->pm_करोमुख्य != clknb->pm_करोमुख्य)
			अवरोध;

		dev_pm_करोमुख्य_set(dev, शून्य);
		pm_clk_destroy(dev);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक pm_clk_runसमय_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	dev_dbg(dev, "%s\n", __func__);

	ret = pm_generic_runसमय_suspend(dev);
	अगर (ret) अणु
		dev_err(dev, "failed to suspend device\n");
		वापस ret;
	पूर्ण

	ret = pm_clk_suspend(dev);
	अगर (ret) अणु
		dev_err(dev, "failed to suspend clock\n");
		pm_generic_runसमय_resume(dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_clk_runसमय_suspend);

पूर्णांक pm_clk_runसमय_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	dev_dbg(dev, "%s\n", __func__);

	ret = pm_clk_resume(dev);
	अगर (ret) अणु
		dev_err(dev, "failed to resume clock\n");
		वापस ret;
	पूर्ण

	वापस pm_generic_runसमय_resume(dev);
पूर्ण
EXPORT_SYMBOL_GPL(pm_clk_runसमय_resume);

#अन्यथा /* !CONFIG_PM_CLK */

/**
 * enable_घड़ी - Enable a device घड़ी.
 * @dev: Device whose घड़ी is to be enabled.
 * @con_id: Connection ID of the घड़ी.
 */
अटल व्योम enable_घड़ी(काष्ठा device *dev, स्थिर अक्षर *con_id)
अणु
	काष्ठा clk *clk;

	clk = clk_get(dev, con_id);
	अगर (!IS_ERR(clk)) अणु
		clk_prepare_enable(clk);
		clk_put(clk);
		dev_info(dev, "Runtime PM disabled, clock forced on.\n");
	पूर्ण
पूर्ण

/**
 * disable_घड़ी - Disable a device घड़ी.
 * @dev: Device whose घड़ी is to be disabled.
 * @con_id: Connection ID of the घड़ी.
 */
अटल व्योम disable_घड़ी(काष्ठा device *dev, स्थिर अक्षर *con_id)
अणु
	काष्ठा clk *clk;

	clk = clk_get(dev, con_id);
	अगर (!IS_ERR(clk)) अणु
		clk_disable_unprepare(clk);
		clk_put(clk);
		dev_info(dev, "Runtime PM disabled, clock forced off.\n");
	पूर्ण
पूर्ण

/**
 * pm_clk_notअगरy - Notअगरy routine क्रम device addition and removal.
 * @nb: Notअगरier block object this function is a member of.
 * @action: Operation being carried out by the caller.
 * @data: Device the routine is being run क्रम.
 *
 * For this function to work, @nb must be a member of an object of type
 * काष्ठा pm_clk_notअगरier_block containing all of the requisite data.
 * Specअगरically, the con_ids member of that object is used to enable or disable
 * the device's घड़ीs, depending on @action.
 */
अटल पूर्णांक pm_clk_notअगरy(काष्ठा notअगरier_block *nb,
				 अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा pm_clk_notअगरier_block *clknb;
	काष्ठा device *dev = data;
	अक्षर **con_id;

	dev_dbg(dev, "%s() %ld\n", __func__, action);

	clknb = container_of(nb, काष्ठा pm_clk_notअगरier_block, nb);

	चयन (action) अणु
	हाल BUS_NOTIFY_BIND_DRIVER:
		अगर (clknb->con_ids[0]) अणु
			क्रम (con_id = clknb->con_ids; *con_id; con_id++)
				enable_घड़ी(dev, *con_id);
		पूर्ण अन्यथा अणु
			enable_घड़ी(dev, शून्य);
		पूर्ण
		अवरोध;
	हाल BUS_NOTIFY_DRIVER_NOT_BOUND:
	हाल BUS_NOTIFY_UNBOUND_DRIVER:
		अगर (clknb->con_ids[0]) अणु
			क्रम (con_id = clknb->con_ids; *con_id; con_id++)
				disable_घड़ी(dev, *con_id);
		पूर्ण अन्यथा अणु
			disable_घड़ी(dev, शून्य);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर /* !CONFIG_PM_CLK */

/**
 * pm_clk_add_notअगरier - Add bus type notअगरier क्रम घातer management घड़ीs.
 * @bus: Bus type to add the notअगरier to.
 * @clknb: Notअगरier to be added to the given bus type.
 *
 * The nb member of @clknb is not expected to be initialized and its
 * notअगरier_call member will be replaced with pm_clk_notअगरy().  However,
 * the reमुख्यing members of @clknb should be populated prior to calling this
 * routine.
 */
व्योम pm_clk_add_notअगरier(काष्ठा bus_type *bus,
				 काष्ठा pm_clk_notअगरier_block *clknb)
अणु
	अगर (!bus || !clknb)
		वापस;

	clknb->nb.notअगरier_call = pm_clk_notअगरy;
	bus_रेजिस्टर_notअगरier(bus, &clknb->nb);
पूर्ण
EXPORT_SYMBOL_GPL(pm_clk_add_notअगरier);
