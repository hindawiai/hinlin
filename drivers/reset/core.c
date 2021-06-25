<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Reset Controller framework
 *
 * Copyright 2013 Philipp Zabel, Pengutronix
 */
#समावेश <linux/atomic.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/reset.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/slab.h>

अटल DEFINE_MUTEX(reset_list_mutex);
अटल LIST_HEAD(reset_controller_list);

अटल DEFINE_MUTEX(reset_lookup_mutex);
अटल LIST_HEAD(reset_lookup_list);

/**
 * काष्ठा reset_control - a reset control
 * @rcdev: a poपूर्णांकer to the reset controller device
 *         this reset control beदीर्घs to
 * @list: list entry क्रम the rcdev's reset controller list
 * @id: ID of the reset controller in the reset
 *      controller device
 * @refcnt: Number of माला_लो of this reset_control
 * @acquired: Only one reset_control may be acquired क्रम a given rcdev and id.
 * @shared: Is this a shared (1), or an exclusive (0) reset_control?
 * @array: Is this an array of reset controls (1)?
 * @deनिश्चित_count: Number of बार this reset line has been deनिश्चितed
 * @triggered_count: Number of बार this reset line has been reset. Currently
 *                   only used क्रम shared resets, which means that the value
 *                   will be either 0 or 1.
 */
काष्ठा reset_control अणु
	काष्ठा reset_controller_dev *rcdev;
	काष्ठा list_head list;
	अचिन्हित पूर्णांक id;
	काष्ठा kref refcnt;
	bool acquired;
	bool shared;
	bool array;
	atomic_t deनिश्चित_count;
	atomic_t triggered_count;
पूर्ण;

/**
 * काष्ठा reset_control_array - an array of reset controls
 * @base: reset control क्रम compatibility with reset control API functions
 * @num_rstcs: number of reset controls
 * @rstc: array of reset controls
 */
काष्ठा reset_control_array अणु
	काष्ठा reset_control base;
	अचिन्हित पूर्णांक num_rstcs;
	काष्ठा reset_control *rstc[];
पूर्ण;

अटल स्थिर अक्षर *rcdev_name(काष्ठा reset_controller_dev *rcdev)
अणु
	अगर (rcdev->dev)
		वापस dev_name(rcdev->dev);

	अगर (rcdev->of_node)
		वापस rcdev->of_node->full_name;

	वापस शून्य;
पूर्ण

/**
 * of_reset_simple_xlate - translate reset_spec to the reset line number
 * @rcdev: a poपूर्णांकer to the reset controller device
 * @reset_spec: reset line specअगरier as found in the device tree
 *
 * This अटल translation function is used by शेष अगर of_xlate in
 * :c:type:`reset_controller_dev` is not set. It is useful क्रम all reset
 * controllers with 1:1 mapping, where reset lines can be indexed by number
 * without gaps.
 */
अटल पूर्णांक of_reset_simple_xlate(काष्ठा reset_controller_dev *rcdev,
			  स्थिर काष्ठा of_phandle_args *reset_spec)
अणु
	अगर (reset_spec->args[0] >= rcdev->nr_resets)
		वापस -EINVAL;

	वापस reset_spec->args[0];
पूर्ण

/**
 * reset_controller_रेजिस्टर - रेजिस्टर a reset controller device
 * @rcdev: a poपूर्णांकer to the initialized reset controller device
 */
पूर्णांक reset_controller_रेजिस्टर(काष्ठा reset_controller_dev *rcdev)
अणु
	अगर (!rcdev->of_xlate) अणु
		rcdev->of_reset_n_cells = 1;
		rcdev->of_xlate = of_reset_simple_xlate;
	पूर्ण

	INIT_LIST_HEAD(&rcdev->reset_control_head);

	mutex_lock(&reset_list_mutex);
	list_add(&rcdev->list, &reset_controller_list);
	mutex_unlock(&reset_list_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(reset_controller_रेजिस्टर);

/**
 * reset_controller_unरेजिस्टर - unरेजिस्टर a reset controller device
 * @rcdev: a poपूर्णांकer to the reset controller device
 */
व्योम reset_controller_unरेजिस्टर(काष्ठा reset_controller_dev *rcdev)
अणु
	mutex_lock(&reset_list_mutex);
	list_del(&rcdev->list);
	mutex_unlock(&reset_list_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(reset_controller_unरेजिस्टर);

अटल व्योम devm_reset_controller_release(काष्ठा device *dev, व्योम *res)
अणु
	reset_controller_unरेजिस्टर(*(काष्ठा reset_controller_dev **)res);
पूर्ण

/**
 * devm_reset_controller_रेजिस्टर - resource managed reset_controller_रेजिस्टर()
 * @dev: device that is रेजिस्टरing this reset controller
 * @rcdev: a poपूर्णांकer to the initialized reset controller device
 *
 * Managed reset_controller_रेजिस्टर(). For reset controllers रेजिस्टरed by
 * this function, reset_controller_unरेजिस्टर() is स्वतःmatically called on
 * driver detach. See reset_controller_रेजिस्टर() क्रम more inक्रमmation.
 */
पूर्णांक devm_reset_controller_रेजिस्टर(काष्ठा device *dev,
				   काष्ठा reset_controller_dev *rcdev)
अणु
	काष्ठा reset_controller_dev **rcdevp;
	पूर्णांक ret;

	rcdevp = devres_alloc(devm_reset_controller_release, माप(*rcdevp),
			      GFP_KERNEL);
	अगर (!rcdevp)
		वापस -ENOMEM;

	ret = reset_controller_रेजिस्टर(rcdev);
	अगर (ret) अणु
		devres_मुक्त(rcdevp);
		वापस ret;
	पूर्ण

	*rcdevp = rcdev;
	devres_add(dev, rcdevp);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_reset_controller_रेजिस्टर);

/**
 * reset_controller_add_lookup - रेजिस्टर a set of lookup entries
 * @lookup: array of reset lookup entries
 * @num_entries: number of entries in the lookup array
 */
व्योम reset_controller_add_lookup(काष्ठा reset_control_lookup *lookup,
				 अचिन्हित पूर्णांक num_entries)
अणु
	काष्ठा reset_control_lookup *entry;
	अचिन्हित पूर्णांक i;

	mutex_lock(&reset_lookup_mutex);
	क्रम (i = 0; i < num_entries; i++) अणु
		entry = &lookup[i];

		अगर (!entry->dev_id || !entry->provider) अणु
			pr_warn("%s(): reset lookup entry badly specified, skipping\n",
				__func__);
			जारी;
		पूर्ण

		list_add_tail(&entry->list, &reset_lookup_list);
	पूर्ण
	mutex_unlock(&reset_lookup_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(reset_controller_add_lookup);

अटल अंतरभूत काष्ठा reset_control_array *
rstc_to_array(काष्ठा reset_control *rstc) अणु
	वापस container_of(rstc, काष्ठा reset_control_array, base);
पूर्ण

अटल पूर्णांक reset_control_array_reset(काष्ठा reset_control_array *resets)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < resets->num_rstcs; i++) अणु
		ret = reset_control_reset(resets->rstc[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक reset_control_array_rearm(काष्ठा reset_control_array *resets)
अणु
	काष्ठा reset_control *rstc;
	पूर्णांक i;

	क्रम (i = 0; i < resets->num_rstcs; i++) अणु
		rstc = resets->rstc[i];

		अगर (!rstc)
			जारी;

		अगर (WARN_ON(IS_ERR(rstc)))
			वापस -EINVAL;

		अगर (rstc->shared) अणु
			अगर (WARN_ON(atomic_पढ़ो(&rstc->deनिश्चित_count) != 0))
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			अगर (!rstc->acquired)
				वापस -EPERM;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < resets->num_rstcs; i++) अणु
		rstc = resets->rstc[i];

		अगर (rstc && rstc->shared)
			WARN_ON(atomic_dec_वापस(&rstc->triggered_count) < 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक reset_control_array_निश्चित(काष्ठा reset_control_array *resets)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < resets->num_rstcs; i++) अणु
		ret = reset_control_निश्चित(resets->rstc[i]);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	जबतक (i--)
		reset_control_deनिश्चित(resets->rstc[i]);
	वापस ret;
पूर्ण

अटल पूर्णांक reset_control_array_deनिश्चित(काष्ठा reset_control_array *resets)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < resets->num_rstcs; i++) अणु
		ret = reset_control_deनिश्चित(resets->rstc[i]);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	जबतक (i--)
		reset_control_निश्चित(resets->rstc[i]);
	वापस ret;
पूर्ण

अटल पूर्णांक reset_control_array_acquire(काष्ठा reset_control_array *resets)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < resets->num_rstcs; i++) अणु
		err = reset_control_acquire(resets->rstc[i]);
		अगर (err < 0)
			जाओ release;
	पूर्ण

	वापस 0;

release:
	जबतक (i--)
		reset_control_release(resets->rstc[i]);

	वापस err;
पूर्ण

अटल व्योम reset_control_array_release(काष्ठा reset_control_array *resets)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < resets->num_rstcs; i++)
		reset_control_release(resets->rstc[i]);
पूर्ण

अटल अंतरभूत bool reset_control_is_array(काष्ठा reset_control *rstc)
अणु
	वापस rstc->array;
पूर्ण

/**
 * reset_control_reset - reset the controlled device
 * @rstc: reset controller
 *
 * On a shared reset line the actual reset pulse is only triggered once क्रम the
 * lअगरeसमय of the reset_control instance: क्रम all but the first caller this is
 * a no-op.
 * Consumers must not use reset_control_(de)निश्चित on shared reset lines when
 * reset_control_reset has been used.
 *
 * If rstc is शून्य it is an optional reset and the function will just
 * वापस 0.
 */
पूर्णांक reset_control_reset(काष्ठा reset_control *rstc)
अणु
	पूर्णांक ret;

	अगर (!rstc)
		वापस 0;

	अगर (WARN_ON(IS_ERR(rstc)))
		वापस -EINVAL;

	अगर (reset_control_is_array(rstc))
		वापस reset_control_array_reset(rstc_to_array(rstc));

	अगर (!rstc->rcdev->ops->reset)
		वापस -ENOTSUPP;

	अगर (rstc->shared) अणु
		अगर (WARN_ON(atomic_पढ़ो(&rstc->deनिश्चित_count) != 0))
			वापस -EINVAL;

		अगर (atomic_inc_वापस(&rstc->triggered_count) != 1)
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर (!rstc->acquired)
			वापस -EPERM;
	पूर्ण

	ret = rstc->rcdev->ops->reset(rstc->rcdev, rstc->id);
	अगर (rstc->shared && ret)
		atomic_dec(&rstc->triggered_count);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(reset_control_reset);

/**
 * reset_control_bulk_reset - reset the controlled devices in order
 * @num_rstcs: number of entries in rstcs array
 * @rstcs: array of काष्ठा reset_control_bulk_data with reset controls set
 *
 * Issue a reset on all provided reset controls, in order.
 *
 * See also: reset_control_reset()
 */
पूर्णांक reset_control_bulk_reset(पूर्णांक num_rstcs,
			     काष्ठा reset_control_bulk_data *rstcs)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < num_rstcs; i++) अणु
		ret = reset_control_reset(rstcs[i].rstc);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(reset_control_bulk_reset);

/**
 * reset_control_rearm - allow shared reset line to be re-triggered"
 * @rstc: reset controller
 *
 * On a shared reset line the actual reset pulse is only triggered once क्रम the
 * lअगरeसमय of the reset_control instance, except अगर this call is used.
 *
 * Calls to this function must be balanced with calls to reset_control_reset,
 * a warning is thrown in हाल triggered_count ever dips below 0.
 *
 * Consumers must not use reset_control_(de)निश्चित on shared reset lines when
 * reset_control_reset or reset_control_rearm have been used.
 *
 * If rstc is शून्य the function will just वापस 0.
 */
पूर्णांक reset_control_rearm(काष्ठा reset_control *rstc)
अणु
	अगर (!rstc)
		वापस 0;

	अगर (WARN_ON(IS_ERR(rstc)))
		वापस -EINVAL;

	अगर (reset_control_is_array(rstc))
		वापस reset_control_array_rearm(rstc_to_array(rstc));

	अगर (rstc->shared) अणु
		अगर (WARN_ON(atomic_पढ़ो(&rstc->deनिश्चित_count) != 0))
			वापस -EINVAL;

		WARN_ON(atomic_dec_वापस(&rstc->triggered_count) < 0);
	पूर्ण अन्यथा अणु
		अगर (!rstc->acquired)
			वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(reset_control_rearm);

/**
 * reset_control_निश्चित - निश्चितs the reset line
 * @rstc: reset controller
 *
 * Calling this on an exclusive reset controller guarantees that the reset
 * will be निश्चितed. When called on a shared reset controller the line may
 * still be deनिश्चितed, as दीर्घ as other users keep it so.
 *
 * For shared reset controls a driver cannot expect the hw's रेजिस्टरs and
 * पूर्णांकernal state to be reset, but must be prepared क्रम this to happen.
 * Consumers must not use reset_control_reset on shared reset lines when
 * reset_control_(de)निश्चित has been used.
 *
 * If rstc is शून्य it is an optional reset and the function will just
 * वापस 0.
 */
पूर्णांक reset_control_निश्चित(काष्ठा reset_control *rstc)
अणु
	अगर (!rstc)
		वापस 0;

	अगर (WARN_ON(IS_ERR(rstc)))
		वापस -EINVAL;

	अगर (reset_control_is_array(rstc))
		वापस reset_control_array_निश्चित(rstc_to_array(rstc));

	अगर (rstc->shared) अणु
		अगर (WARN_ON(atomic_पढ़ो(&rstc->triggered_count) != 0))
			वापस -EINVAL;

		अगर (WARN_ON(atomic_पढ़ो(&rstc->deनिश्चित_count) == 0))
			वापस -EINVAL;

		अगर (atomic_dec_वापस(&rstc->deनिश्चित_count) != 0)
			वापस 0;

		/*
		 * Shared reset controls allow the reset line to be in any state
		 * after this call, so करोing nothing is a valid option.
		 */
		अगर (!rstc->rcdev->ops->निश्चित)
			वापस 0;
	पूर्ण अन्यथा अणु
		/*
		 * If the reset controller करोes not implement .निश्चित(), there
		 * is no way to guarantee that the reset line is निश्चितed after
		 * this call.
		 */
		अगर (!rstc->rcdev->ops->निश्चित)
			वापस -ENOTSUPP;

		अगर (!rstc->acquired) अणु
			WARN(1, "reset %s (ID: %u) is not acquired\n",
			     rcdev_name(rstc->rcdev), rstc->id);
			वापस -EPERM;
		पूर्ण
	पूर्ण

	वापस rstc->rcdev->ops->निश्चित(rstc->rcdev, rstc->id);
पूर्ण
EXPORT_SYMBOL_GPL(reset_control_निश्चित);

/**
 * reset_control_bulk_निश्चित - निश्चितs the reset lines in order
 * @num_rstcs: number of entries in rstcs array
 * @rstcs: array of काष्ठा reset_control_bulk_data with reset controls set
 *
 * Assert the reset lines क्रम all provided reset controls, in order.
 * If an निश्चितion fails, alपढ़ोy निश्चितed resets are deनिश्चितed again.
 *
 * See also: reset_control_निश्चित()
 */
पूर्णांक reset_control_bulk_निश्चित(पूर्णांक num_rstcs,
			      काष्ठा reset_control_bulk_data *rstcs)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < num_rstcs; i++) अणु
		ret = reset_control_निश्चित(rstcs[i].rstc);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	जबतक (i--)
		reset_control_deनिश्चित(rstcs[i].rstc);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(reset_control_bulk_निश्चित);

/**
 * reset_control_deनिश्चित - deनिश्चितs the reset line
 * @rstc: reset controller
 *
 * After calling this function, the reset is guaranteed to be deनिश्चितed.
 * Consumers must not use reset_control_reset on shared reset lines when
 * reset_control_(de)निश्चित has been used.
 *
 * If rstc is शून्य it is an optional reset and the function will just
 * वापस 0.
 */
पूर्णांक reset_control_deनिश्चित(काष्ठा reset_control *rstc)
अणु
	अगर (!rstc)
		वापस 0;

	अगर (WARN_ON(IS_ERR(rstc)))
		वापस -EINVAL;

	अगर (reset_control_is_array(rstc))
		वापस reset_control_array_deनिश्चित(rstc_to_array(rstc));

	अगर (rstc->shared) अणु
		अगर (WARN_ON(atomic_पढ़ो(&rstc->triggered_count) != 0))
			वापस -EINVAL;

		अगर (atomic_inc_वापस(&rstc->deनिश्चित_count) != 1)
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर (!rstc->acquired) अणु
			WARN(1, "reset %s (ID: %u) is not acquired\n",
			     rcdev_name(rstc->rcdev), rstc->id);
			वापस -EPERM;
		पूर्ण
	पूर्ण

	/*
	 * If the reset controller करोes not implement .deनिश्चित(), we assume
	 * that it handles self-deनिश्चितing reset lines via .reset(). In that
	 * हाल, the reset lines are deनिश्चितed by शेष. If that is not the
	 * हाल, the reset controller driver should implement .deनिश्चित() and
	 * वापस -ENOTSUPP.
	 */
	अगर (!rstc->rcdev->ops->deनिश्चित)
		वापस 0;

	वापस rstc->rcdev->ops->deनिश्चित(rstc->rcdev, rstc->id);
पूर्ण
EXPORT_SYMBOL_GPL(reset_control_deनिश्चित);

/**
 * reset_control_bulk_deनिश्चित - deनिश्चितs the reset lines in reverse order
 * @num_rstcs: number of entries in rstcs array
 * @rstcs: array of काष्ठा reset_control_bulk_data with reset controls set
 *
 * Deनिश्चित the reset lines क्रम all provided reset controls, in reverse order.
 * If a deनिश्चितion fails, alपढ़ोy deनिश्चितed resets are निश्चितed again.
 *
 * See also: reset_control_deनिश्चित()
 */
पूर्णांक reset_control_bulk_deनिश्चित(पूर्णांक num_rstcs,
				काष्ठा reset_control_bulk_data *rstcs)
अणु
	पूर्णांक ret, i;

	क्रम (i = num_rstcs - 1; i >= 0; i--) अणु
		ret = reset_control_deनिश्चित(rstcs[i].rstc);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	जबतक (i < num_rstcs)
		reset_control_निश्चित(rstcs[i++].rstc);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(reset_control_bulk_deनिश्चित);

/**
 * reset_control_status - वापसs a negative त्रुटि_सं अगर not supported, a
 * positive value अगर the reset line is निश्चितed, or zero अगर the reset
 * line is not निश्चितed or अगर the desc is शून्य (optional reset).
 * @rstc: reset controller
 */
पूर्णांक reset_control_status(काष्ठा reset_control *rstc)
अणु
	अगर (!rstc)
		वापस 0;

	अगर (WARN_ON(IS_ERR(rstc)) || reset_control_is_array(rstc))
		वापस -EINVAL;

	अगर (rstc->rcdev->ops->status)
		वापस rstc->rcdev->ops->status(rstc->rcdev, rstc->id);

	वापस -ENOTSUPP;
पूर्ण
EXPORT_SYMBOL_GPL(reset_control_status);

/**
 * reset_control_acquire() - acquires a reset control क्रम exclusive use
 * @rstc: reset control
 *
 * This is used to explicitly acquire a reset control क्रम exclusive use. Note
 * that exclusive resets are requested as acquired by शेष. In order क्रम a
 * second consumer to be able to control the reset, the first consumer has to
 * release it first. Typically the easiest way to achieve this is to call the
 * reset_control_get_exclusive_released() to obtain an instance of the reset
 * control. Such reset controls are not acquired by शेष.
 *
 * Consumers implementing shared access to an exclusive reset need to follow
 * a specअगरic protocol in order to work together. Beक्रमe consumers can change
 * a reset they must acquire exclusive access using reset_control_acquire().
 * After they are करोne operating the reset, they must release exclusive access
 * with a call to reset_control_release(). Consumers are not granted exclusive
 * access to the reset as दीर्घ as another consumer hasn't released a reset.
 *
 * See also: reset_control_release()
 */
पूर्णांक reset_control_acquire(काष्ठा reset_control *rstc)
अणु
	काष्ठा reset_control *rc;

	अगर (!rstc)
		वापस 0;

	अगर (WARN_ON(IS_ERR(rstc)))
		वापस -EINVAL;

	अगर (reset_control_is_array(rstc))
		वापस reset_control_array_acquire(rstc_to_array(rstc));

	mutex_lock(&reset_list_mutex);

	अगर (rstc->acquired) अणु
		mutex_unlock(&reset_list_mutex);
		वापस 0;
	पूर्ण

	list_क्रम_each_entry(rc, &rstc->rcdev->reset_control_head, list) अणु
		अगर (rstc != rc && rstc->id == rc->id) अणु
			अगर (rc->acquired) अणु
				mutex_unlock(&reset_list_mutex);
				वापस -EBUSY;
			पूर्ण
		पूर्ण
	पूर्ण

	rstc->acquired = true;

	mutex_unlock(&reset_list_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(reset_control_acquire);

/**
 * reset_control_bulk_acquire - acquires reset controls क्रम exclusive use
 * @num_rstcs: number of entries in rstcs array
 * @rstcs: array of काष्ठा reset_control_bulk_data with reset controls set
 *
 * This is used to explicitly acquire reset controls requested with
 * reset_control_bulk_get_exclusive_release() क्रम temporary exclusive use.
 *
 * See also: reset_control_acquire(), reset_control_bulk_release()
 */
पूर्णांक reset_control_bulk_acquire(पूर्णांक num_rstcs,
			       काष्ठा reset_control_bulk_data *rstcs)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < num_rstcs; i++) अणु
		ret = reset_control_acquire(rstcs[i].rstc);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	जबतक (i--)
		reset_control_release(rstcs[i].rstc);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(reset_control_bulk_acquire);

/**
 * reset_control_release() - releases exclusive access to a reset control
 * @rstc: reset control
 *
 * Releases exclusive access right to a reset control previously obtained by a
 * call to reset_control_acquire(). Until a consumer calls this function, no
 * other consumers will be granted exclusive access.
 *
 * See also: reset_control_acquire()
 */
व्योम reset_control_release(काष्ठा reset_control *rstc)
अणु
	अगर (!rstc || WARN_ON(IS_ERR(rstc)))
		वापस;

	अगर (reset_control_is_array(rstc))
		reset_control_array_release(rstc_to_array(rstc));
	अन्यथा
		rstc->acquired = false;
पूर्ण
EXPORT_SYMBOL_GPL(reset_control_release);

/**
 * reset_control_bulk_release() - releases exclusive access to reset controls
 * @num_rstcs: number of entries in rstcs array
 * @rstcs: array of काष्ठा reset_control_bulk_data with reset controls set
 *
 * Releases exclusive access right to reset controls previously obtained by a
 * call to reset_control_bulk_acquire().
 *
 * See also: reset_control_release(), reset_control_bulk_acquire()
 */
व्योम reset_control_bulk_release(पूर्णांक num_rstcs,
				काष्ठा reset_control_bulk_data *rstcs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_rstcs; i++)
		reset_control_release(rstcs[i].rstc);
पूर्ण
EXPORT_SYMBOL_GPL(reset_control_bulk_release);

अटल काष्ठा reset_control *__reset_control_get_पूर्णांकernal(
				काष्ठा reset_controller_dev *rcdev,
				अचिन्हित पूर्णांक index, bool shared, bool acquired)
अणु
	काष्ठा reset_control *rstc;

	lockdep_निश्चित_held(&reset_list_mutex);

	list_क्रम_each_entry(rstc, &rcdev->reset_control_head, list) अणु
		अगर (rstc->id == index) अणु
			/*
			 * Allow creating a secondary exclusive reset_control
			 * that is initially not acquired क्रम an alपढ़ोy
			 * controlled reset line.
			 */
			अगर (!rstc->shared && !shared && !acquired)
				अवरोध;

			अगर (WARN_ON(!rstc->shared || !shared))
				वापस ERR_PTR(-EBUSY);

			kref_get(&rstc->refcnt);
			वापस rstc;
		पूर्ण
	पूर्ण

	rstc = kzalloc(माप(*rstc), GFP_KERNEL);
	अगर (!rstc)
		वापस ERR_PTR(-ENOMEM);

	try_module_get(rcdev->owner);

	rstc->rcdev = rcdev;
	list_add(&rstc->list, &rcdev->reset_control_head);
	rstc->id = index;
	kref_init(&rstc->refcnt);
	rstc->acquired = acquired;
	rstc->shared = shared;

	वापस rstc;
पूर्ण

अटल व्योम __reset_control_release(काष्ठा kref *kref)
अणु
	काष्ठा reset_control *rstc = container_of(kref, काष्ठा reset_control,
						  refcnt);

	lockdep_निश्चित_held(&reset_list_mutex);

	module_put(rstc->rcdev->owner);

	list_del(&rstc->list);
	kमुक्त(rstc);
पूर्ण

अटल व्योम __reset_control_put_पूर्णांकernal(काष्ठा reset_control *rstc)
अणु
	lockdep_निश्चित_held(&reset_list_mutex);

	kref_put(&rstc->refcnt, __reset_control_release);
पूर्ण

काष्ठा reset_control *__of_reset_control_get(काष्ठा device_node *node,
				     स्थिर अक्षर *id, पूर्णांक index, bool shared,
				     bool optional, bool acquired)
अणु
	काष्ठा reset_control *rstc;
	काष्ठा reset_controller_dev *r, *rcdev;
	काष्ठा of_phandle_args args;
	पूर्णांक rstc_id;
	पूर्णांक ret;

	अगर (!node)
		वापस ERR_PTR(-EINVAL);

	अगर (id) अणु
		index = of_property_match_string(node,
						 "reset-names", id);
		अगर (index == -EILSEQ)
			वापस ERR_PTR(index);
		अगर (index < 0)
			वापस optional ? शून्य : ERR_PTR(-ENOENT);
	पूर्ण

	ret = of_parse_phandle_with_args(node, "resets", "#reset-cells",
					 index, &args);
	अगर (ret == -EINVAL)
		वापस ERR_PTR(ret);
	अगर (ret)
		वापस optional ? शून्य : ERR_PTR(ret);

	mutex_lock(&reset_list_mutex);
	rcdev = शून्य;
	list_क्रम_each_entry(r, &reset_controller_list, list) अणु
		अगर (args.np == r->of_node) अणु
			rcdev = r;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!rcdev) अणु
		rstc = ERR_PTR(-EPROBE_DEFER);
		जाओ out;
	पूर्ण

	अगर (WARN_ON(args.args_count != rcdev->of_reset_n_cells)) अणु
		rstc = ERR_PTR(-EINVAL);
		जाओ out;
	पूर्ण

	rstc_id = rcdev->of_xlate(rcdev, &args);
	अगर (rstc_id < 0) अणु
		rstc = ERR_PTR(rstc_id);
		जाओ out;
	पूर्ण

	/* reset_list_mutex also protects the rcdev's reset_control list */
	rstc = __reset_control_get_पूर्णांकernal(rcdev, rstc_id, shared, acquired);

out:
	mutex_unlock(&reset_list_mutex);
	of_node_put(args.np);

	वापस rstc;
पूर्ण
EXPORT_SYMBOL_GPL(__of_reset_control_get);

अटल काष्ठा reset_controller_dev *
__reset_controller_by_name(स्थिर अक्षर *name)
अणु
	काष्ठा reset_controller_dev *rcdev;

	lockdep_निश्चित_held(&reset_list_mutex);

	list_क्रम_each_entry(rcdev, &reset_controller_list, list) अणु
		अगर (!rcdev->dev)
			जारी;

		अगर (!म_भेद(name, dev_name(rcdev->dev)))
			वापस rcdev;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा reset_control *
__reset_control_get_from_lookup(काष्ठा device *dev, स्थिर अक्षर *con_id,
				bool shared, bool optional, bool acquired)
अणु
	स्थिर काष्ठा reset_control_lookup *lookup;
	काष्ठा reset_controller_dev *rcdev;
	स्थिर अक्षर *dev_id = dev_name(dev);
	काष्ठा reset_control *rstc = शून्य;

	mutex_lock(&reset_lookup_mutex);

	list_क्रम_each_entry(lookup, &reset_lookup_list, list) अणु
		अगर (म_भेद(lookup->dev_id, dev_id))
			जारी;

		अगर ((!con_id && !lookup->con_id) ||
		    ((con_id && lookup->con_id) &&
		     !म_भेद(con_id, lookup->con_id))) अणु
			mutex_lock(&reset_list_mutex);
			rcdev = __reset_controller_by_name(lookup->provider);
			अगर (!rcdev) अणु
				mutex_unlock(&reset_list_mutex);
				mutex_unlock(&reset_lookup_mutex);
				/* Reset provider may not be पढ़ोy yet. */
				वापस ERR_PTR(-EPROBE_DEFER);
			पूर्ण

			rstc = __reset_control_get_पूर्णांकernal(rcdev,
							    lookup->index,
							    shared, acquired);
			mutex_unlock(&reset_list_mutex);
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&reset_lookup_mutex);

	अगर (!rstc)
		वापस optional ? शून्य : ERR_PTR(-ENOENT);

	वापस rstc;
पूर्ण

काष्ठा reset_control *__reset_control_get(काष्ठा device *dev, स्थिर अक्षर *id,
					  पूर्णांक index, bool shared, bool optional,
					  bool acquired)
अणु
	अगर (WARN_ON(shared && acquired))
		वापस ERR_PTR(-EINVAL);

	अगर (dev->of_node)
		वापस __of_reset_control_get(dev->of_node, id, index, shared,
					      optional, acquired);

	वापस __reset_control_get_from_lookup(dev, id, shared, optional,
					       acquired);
पूर्ण
EXPORT_SYMBOL_GPL(__reset_control_get);

पूर्णांक __reset_control_bulk_get(काष्ठा device *dev, पूर्णांक num_rstcs,
			     काष्ठा reset_control_bulk_data *rstcs,
			     bool shared, bool optional, bool acquired)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < num_rstcs; i++) अणु
		rstcs[i].rstc = __reset_control_get(dev, rstcs[i].id, 0,
						    shared, optional, acquired);
		अगर (IS_ERR(rstcs[i].rstc)) अणु
			ret = PTR_ERR(rstcs[i].rstc);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	mutex_lock(&reset_list_mutex);
	जबतक (i--)
		__reset_control_put_पूर्णांकernal(rstcs[i].rstc);
	mutex_unlock(&reset_list_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__reset_control_bulk_get);

अटल व्योम reset_control_array_put(काष्ठा reset_control_array *resets)
अणु
	पूर्णांक i;

	mutex_lock(&reset_list_mutex);
	क्रम (i = 0; i < resets->num_rstcs; i++)
		__reset_control_put_पूर्णांकernal(resets->rstc[i]);
	mutex_unlock(&reset_list_mutex);
	kमुक्त(resets);
पूर्ण

/**
 * reset_control_put - मुक्त the reset controller
 * @rstc: reset controller
 */
व्योम reset_control_put(काष्ठा reset_control *rstc)
अणु
	अगर (IS_ERR_OR_शून्य(rstc))
		वापस;

	अगर (reset_control_is_array(rstc)) अणु
		reset_control_array_put(rstc_to_array(rstc));
		वापस;
	पूर्ण

	mutex_lock(&reset_list_mutex);
	__reset_control_put_पूर्णांकernal(rstc);
	mutex_unlock(&reset_list_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(reset_control_put);

/**
 * reset_control_bulk_put - मुक्त the reset controllers
 * @num_rstcs: number of entries in rstcs array
 * @rstcs: array of काष्ठा reset_control_bulk_data with reset controls set
 */
व्योम reset_control_bulk_put(पूर्णांक num_rstcs, काष्ठा reset_control_bulk_data *rstcs)
अणु
	mutex_lock(&reset_list_mutex);
	जबतक (num_rstcs--) अणु
		अगर (IS_ERR_OR_शून्य(rstcs[num_rstcs].rstc))
			जारी;
		__reset_control_put_पूर्णांकernal(rstcs[num_rstcs].rstc);
	पूर्ण
	mutex_unlock(&reset_list_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(reset_control_bulk_put);

अटल व्योम devm_reset_control_release(काष्ठा device *dev, व्योम *res)
अणु
	reset_control_put(*(काष्ठा reset_control **)res);
पूर्ण

काष्ठा reset_control *__devm_reset_control_get(काष्ठा device *dev,
				     स्थिर अक्षर *id, पूर्णांक index, bool shared,
				     bool optional, bool acquired)
अणु
	काष्ठा reset_control **ptr, *rstc;

	ptr = devres_alloc(devm_reset_control_release, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	rstc = __reset_control_get(dev, id, index, shared, optional, acquired);
	अगर (IS_ERR_OR_शून्य(rstc)) अणु
		devres_मुक्त(ptr);
		वापस rstc;
	पूर्ण

	*ptr = rstc;
	devres_add(dev, ptr);

	वापस rstc;
पूर्ण
EXPORT_SYMBOL_GPL(__devm_reset_control_get);

काष्ठा reset_control_bulk_devres अणु
	पूर्णांक num_rstcs;
	काष्ठा reset_control_bulk_data *rstcs;
पूर्ण;

अटल व्योम devm_reset_control_bulk_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा reset_control_bulk_devres *devres = res;

	reset_control_bulk_put(devres->num_rstcs, devres->rstcs);
पूर्ण

पूर्णांक __devm_reset_control_bulk_get(काष्ठा device *dev, पूर्णांक num_rstcs,
				  काष्ठा reset_control_bulk_data *rstcs,
				  bool shared, bool optional, bool acquired)
अणु
	काष्ठा reset_control_bulk_devres *ptr;
	पूर्णांक ret;

	ptr = devres_alloc(devm_reset_control_bulk_release, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	ret = __reset_control_bulk_get(dev, num_rstcs, rstcs, shared, optional, acquired);
	अगर (ret < 0) अणु
		devres_मुक्त(ptr);
		वापस ret;
	पूर्ण

	ptr->num_rstcs = num_rstcs;
	ptr->rstcs = rstcs;
	devres_add(dev, ptr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__devm_reset_control_bulk_get);

/**
 * __device_reset - find reset controller associated with the device
 *                  and perक्रमm reset
 * @dev: device to be reset by the controller
 * @optional: whether it is optional to reset the device
 *
 * Convenience wrapper क्रम __reset_control_get() and reset_control_reset().
 * This is useful क्रम the common हाल of devices with single, dedicated reset
 * lines.
 */
पूर्णांक __device_reset(काष्ठा device *dev, bool optional)
अणु
	काष्ठा reset_control *rstc;
	पूर्णांक ret;

	rstc = __reset_control_get(dev, शून्य, 0, 0, optional, true);
	अगर (IS_ERR(rstc))
		वापस PTR_ERR(rstc);

	ret = reset_control_reset(rstc);

	reset_control_put(rstc);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__device_reset);

/*
 * APIs to manage an array of reset controls.
 */

/**
 * of_reset_control_get_count - Count number of resets available with a device
 *
 * @node: device node that contains 'resets'.
 *
 * Returns positive reset count on success, or error number on failure and
 * on count being zero.
 */
अटल पूर्णांक of_reset_control_get_count(काष्ठा device_node *node)
अणु
	पूर्णांक count;

	अगर (!node)
		वापस -EINVAL;

	count = of_count_phandle_with_args(node, "resets", "#reset-cells");
	अगर (count == 0)
		count = -ENOENT;

	वापस count;
पूर्ण

/**
 * of_reset_control_array_get - Get a list of reset controls using
 *				device node.
 *
 * @np: device node क्रम the device that requests the reset controls array
 * @shared: whether reset controls are shared or not
 * @optional: whether it is optional to get the reset controls
 * @acquired: only one reset control may be acquired क्रम a given controller
 *            and ID
 *
 * Returns poपूर्णांकer to allocated reset_control on success or error on failure
 */
काष्ठा reset_control *
of_reset_control_array_get(काष्ठा device_node *np, bool shared, bool optional,
			   bool acquired)
अणु
	काष्ठा reset_control_array *resets;
	काष्ठा reset_control *rstc;
	पूर्णांक num, i;

	num = of_reset_control_get_count(np);
	अगर (num < 0)
		वापस optional ? शून्य : ERR_PTR(num);

	resets = kzalloc(काष्ठा_size(resets, rstc, num), GFP_KERNEL);
	अगर (!resets)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < num; i++) अणु
		rstc = __of_reset_control_get(np, शून्य, i, shared, optional,
					      acquired);
		अगर (IS_ERR(rstc))
			जाओ err_rst;
		resets->rstc[i] = rstc;
	पूर्ण
	resets->num_rstcs = num;
	resets->base.array = true;

	वापस &resets->base;

err_rst:
	mutex_lock(&reset_list_mutex);
	जबतक (--i >= 0)
		__reset_control_put_पूर्णांकernal(resets->rstc[i]);
	mutex_unlock(&reset_list_mutex);

	kमुक्त(resets);

	वापस rstc;
पूर्ण
EXPORT_SYMBOL_GPL(of_reset_control_array_get);

/**
 * devm_reset_control_array_get - Resource managed reset control array get
 *
 * @dev: device that requests the list of reset controls
 * @shared: whether reset controls are shared or not
 * @optional: whether it is optional to get the reset controls
 *
 * The reset control array APIs are पूर्णांकended क्रम a list of resets
 * that just have to be निश्चितed or deनिश्चितed, without any
 * requirements on the order.
 *
 * Returns poपूर्णांकer to allocated reset_control on success or error on failure
 */
काष्ठा reset_control *
devm_reset_control_array_get(काष्ठा device *dev, bool shared, bool optional)
अणु
	काष्ठा reset_control **ptr, *rstc;

	ptr = devres_alloc(devm_reset_control_release, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	rstc = of_reset_control_array_get(dev->of_node, shared, optional, true);
	अगर (IS_ERR_OR_शून्य(rstc)) अणु
		devres_मुक्त(ptr);
		वापस rstc;
	पूर्ण

	*ptr = rstc;
	devres_add(dev, ptr);

	वापस rstc;
पूर्ण
EXPORT_SYMBOL_GPL(devm_reset_control_array_get);

अटल पूर्णांक reset_control_get_count_from_lookup(काष्ठा device *dev)
अणु
	स्थिर काष्ठा reset_control_lookup *lookup;
	स्थिर अक्षर *dev_id;
	पूर्णांक count = 0;

	अगर (!dev)
		वापस -EINVAL;

	dev_id = dev_name(dev);
	mutex_lock(&reset_lookup_mutex);

	list_क्रम_each_entry(lookup, &reset_lookup_list, list) अणु
		अगर (!म_भेद(lookup->dev_id, dev_id))
			count++;
	पूर्ण

	mutex_unlock(&reset_lookup_mutex);

	अगर (count == 0)
		count = -ENOENT;

	वापस count;
पूर्ण

/**
 * reset_control_get_count - Count number of resets available with a device
 *
 * @dev: device क्रम which to वापस the number of resets
 *
 * Returns positive reset count on success, or error number on failure and
 * on count being zero.
 */
पूर्णांक reset_control_get_count(काष्ठा device *dev)
अणु
	अगर (dev->of_node)
		वापस of_reset_control_get_count(dev->of_node);

	वापस reset_control_get_count_from_lookup(dev);
पूर्ण
EXPORT_SYMBOL_GPL(reset_control_get_count);
