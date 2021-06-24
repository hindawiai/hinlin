<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
//
// core.c  --  Voltage/Current Regulator framework.
//
// Copyright 2007, 2008 Wolfson Microelectronics PLC.
// Copyright 2008 SlimLogic Ltd.
//
// Author: Liam Girdwood <lrg@slimlogic.co.uk>

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/async.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/suspend.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regulator/coupler.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/module.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/regulator.h>

#समावेश "dummy.h"
#समावेश "internal.h"

#घोषणा rdev_crit(rdev, fmt, ...)					\
	pr_crit("%s: " fmt, rdev_get_name(rdev), ##__VA_ARGS__)
#घोषणा rdev_err(rdev, fmt, ...)					\
	pr_err("%s: " fmt, rdev_get_name(rdev), ##__VA_ARGS__)
#घोषणा rdev_warn(rdev, fmt, ...)					\
	pr_warn("%s: " fmt, rdev_get_name(rdev), ##__VA_ARGS__)
#घोषणा rdev_info(rdev, fmt, ...)					\
	pr_info("%s: " fmt, rdev_get_name(rdev), ##__VA_ARGS__)
#घोषणा rdev_dbg(rdev, fmt, ...)					\
	pr_debug("%s: " fmt, rdev_get_name(rdev), ##__VA_ARGS__)

अटल DEFINE_WW_CLASS(regulator_ww_class);
अटल DEFINE_MUTEX(regulator_nesting_mutex);
अटल DEFINE_MUTEX(regulator_list_mutex);
अटल LIST_HEAD(regulator_map_list);
अटल LIST_HEAD(regulator_ena_gpio_list);
अटल LIST_HEAD(regulator_supply_alias_list);
अटल LIST_HEAD(regulator_coupler_list);
अटल bool has_full_स्थिरraपूर्णांकs;

अटल काष्ठा dentry *debugfs_root;

/*
 * काष्ठा regulator_map
 *
 * Used to provide symbolic supply names to devices.
 */
काष्ठा regulator_map अणु
	काष्ठा list_head list;
	स्थिर अक्षर *dev_name;   /* The dev_name() क्रम the consumer */
	स्थिर अक्षर *supply;
	काष्ठा regulator_dev *regulator;
पूर्ण;

/*
 * काष्ठा regulator_enable_gpio
 *
 * Management क्रम shared enable GPIO pin
 */
काष्ठा regulator_enable_gpio अणु
	काष्ठा list_head list;
	काष्ठा gpio_desc *gpiod;
	u32 enable_count;	/* a number of enabled shared GPIO */
	u32 request_count;	/* a number of requested shared GPIO */
पूर्ण;

/*
 * काष्ठा regulator_supply_alias
 *
 * Used to map lookups क्रम a supply onto an alternative device.
 */
काष्ठा regulator_supply_alias अणु
	काष्ठा list_head list;
	काष्ठा device *src_dev;
	स्थिर अक्षर *src_supply;
	काष्ठा device *alias_dev;
	स्थिर अक्षर *alias_supply;
पूर्ण;

अटल पूर्णांक _regulator_is_enabled(काष्ठा regulator_dev *rdev);
अटल पूर्णांक _regulator_disable(काष्ठा regulator *regulator);
अटल पूर्णांक _regulator_get_current_limit(काष्ठा regulator_dev *rdev);
अटल अचिन्हित पूर्णांक _regulator_get_mode(काष्ठा regulator_dev *rdev);
अटल पूर्णांक _notअगरier_call_chain(काष्ठा regulator_dev *rdev,
				  अचिन्हित दीर्घ event, व्योम *data);
अटल पूर्णांक _regulator_करो_set_voltage(काष्ठा regulator_dev *rdev,
				     पूर्णांक min_uV, पूर्णांक max_uV);
अटल पूर्णांक regulator_balance_voltage(काष्ठा regulator_dev *rdev,
				     suspend_state_t state);
अटल काष्ठा regulator *create_regulator(काष्ठा regulator_dev *rdev,
					  काष्ठा device *dev,
					  स्थिर अक्षर *supply_name);
अटल व्योम destroy_regulator(काष्ठा regulator *regulator);
अटल व्योम _regulator_put(काष्ठा regulator *regulator);

स्थिर अक्षर *rdev_get_name(काष्ठा regulator_dev *rdev)
अणु
	अगर (rdev->स्थिरraपूर्णांकs && rdev->स्थिरraपूर्णांकs->name)
		वापस rdev->स्थिरraपूर्णांकs->name;
	अन्यथा अगर (rdev->desc->name)
		वापस rdev->desc->name;
	अन्यथा
		वापस "";
पूर्ण

अटल bool have_full_स्थिरraपूर्णांकs(व्योम)
अणु
	वापस has_full_स्थिरraपूर्णांकs || of_have_populated_dt();
पूर्ण

अटल bool regulator_ops_is_valid(काष्ठा regulator_dev *rdev, पूर्णांक ops)
अणु
	अगर (!rdev->स्थिरraपूर्णांकs) अणु
		rdev_err(rdev, "no constraints\n");
		वापस false;
	पूर्ण

	अगर (rdev->स्थिरraपूर्णांकs->valid_ops_mask & ops)
		वापस true;

	वापस false;
पूर्ण

/**
 * regulator_lock_nested - lock a single regulator
 * @rdev:		regulator source
 * @ww_ctx:		w/w mutex acquire context
 *
 * This function can be called many बार by one task on
 * a single regulator and its mutex will be locked only
 * once. If a task, which is calling this function is other
 * than the one, which initially locked the mutex, it will
 * रुको on mutex.
 */
अटल अंतरभूत पूर्णांक regulator_lock_nested(काष्ठा regulator_dev *rdev,
					काष्ठा ww_acquire_ctx *ww_ctx)
अणु
	bool lock = false;
	पूर्णांक ret = 0;

	mutex_lock(&regulator_nesting_mutex);

	अगर (ww_ctx || !ww_mutex_trylock(&rdev->mutex)) अणु
		अगर (rdev->mutex_owner == current)
			rdev->ref_cnt++;
		अन्यथा
			lock = true;

		अगर (lock) अणु
			mutex_unlock(&regulator_nesting_mutex);
			ret = ww_mutex_lock(&rdev->mutex, ww_ctx);
			mutex_lock(&regulator_nesting_mutex);
		पूर्ण
	पूर्ण अन्यथा अणु
		lock = true;
	पूर्ण

	अगर (lock && ret != -EDEADLK) अणु
		rdev->ref_cnt++;
		rdev->mutex_owner = current;
	पूर्ण

	mutex_unlock(&regulator_nesting_mutex);

	वापस ret;
पूर्ण

/**
 * regulator_lock - lock a single regulator
 * @rdev:		regulator source
 *
 * This function can be called many बार by one task on
 * a single regulator and its mutex will be locked only
 * once. If a task, which is calling this function is other
 * than the one, which initially locked the mutex, it will
 * रुको on mutex.
 */
अटल व्योम regulator_lock(काष्ठा regulator_dev *rdev)
अणु
	regulator_lock_nested(rdev, शून्य);
पूर्ण

/**
 * regulator_unlock - unlock a single regulator
 * @rdev:		regulator_source
 *
 * This function unlocks the mutex when the
 * reference counter reaches 0.
 */
अटल व्योम regulator_unlock(काष्ठा regulator_dev *rdev)
अणु
	mutex_lock(&regulator_nesting_mutex);

	अगर (--rdev->ref_cnt == 0) अणु
		rdev->mutex_owner = शून्य;
		ww_mutex_unlock(&rdev->mutex);
	पूर्ण

	WARN_ON_ONCE(rdev->ref_cnt < 0);

	mutex_unlock(&regulator_nesting_mutex);
पूर्ण

अटल bool regulator_supply_is_couple(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा regulator_dev *c_rdev;
	पूर्णांक i;

	क्रम (i = 1; i < rdev->coupling_desc.n_coupled; i++) अणु
		c_rdev = rdev->coupling_desc.coupled_rdevs[i];

		अगर (rdev->supply->rdev == c_rdev)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम regulator_unlock_recursive(काष्ठा regulator_dev *rdev,
				       अचिन्हित पूर्णांक n_coupled)
अणु
	काष्ठा regulator_dev *c_rdev, *supply_rdev;
	पूर्णांक i, supply_n_coupled;

	क्रम (i = n_coupled; i > 0; i--) अणु
		c_rdev = rdev->coupling_desc.coupled_rdevs[i - 1];

		अगर (!c_rdev)
			जारी;

		अगर (c_rdev->supply && !regulator_supply_is_couple(c_rdev)) अणु
			supply_rdev = c_rdev->supply->rdev;
			supply_n_coupled = supply_rdev->coupling_desc.n_coupled;

			regulator_unlock_recursive(supply_rdev,
						   supply_n_coupled);
		पूर्ण

		regulator_unlock(c_rdev);
	पूर्ण
पूर्ण

अटल पूर्णांक regulator_lock_recursive(काष्ठा regulator_dev *rdev,
				    काष्ठा regulator_dev **new_contended_rdev,
				    काष्ठा regulator_dev **old_contended_rdev,
				    काष्ठा ww_acquire_ctx *ww_ctx)
अणु
	काष्ठा regulator_dev *c_rdev;
	पूर्णांक i, err;

	क्रम (i = 0; i < rdev->coupling_desc.n_coupled; i++) अणु
		c_rdev = rdev->coupling_desc.coupled_rdevs[i];

		अगर (!c_rdev)
			जारी;

		अगर (c_rdev != *old_contended_rdev) अणु
			err = regulator_lock_nested(c_rdev, ww_ctx);
			अगर (err) अणु
				अगर (err == -EDEADLK) अणु
					*new_contended_rdev = c_rdev;
					जाओ err_unlock;
				पूर्ण

				/* shouldn't happen */
				WARN_ON_ONCE(err != -EALREADY);
			पूर्ण
		पूर्ण अन्यथा अणु
			*old_contended_rdev = शून्य;
		पूर्ण

		अगर (c_rdev->supply && !regulator_supply_is_couple(c_rdev)) अणु
			err = regulator_lock_recursive(c_rdev->supply->rdev,
						       new_contended_rdev,
						       old_contended_rdev,
						       ww_ctx);
			अगर (err) अणु
				regulator_unlock(c_rdev);
				जाओ err_unlock;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

err_unlock:
	regulator_unlock_recursive(rdev, i);

	वापस err;
पूर्ण

/**
 * regulator_unlock_dependent - unlock regulator's suppliers and coupled
 *				regulators
 * @rdev:			regulator source
 * @ww_ctx:			w/w mutex acquire context
 *
 * Unlock all regulators related with rdev by coupling or supplying.
 */
अटल व्योम regulator_unlock_dependent(काष्ठा regulator_dev *rdev,
				       काष्ठा ww_acquire_ctx *ww_ctx)
अणु
	regulator_unlock_recursive(rdev, rdev->coupling_desc.n_coupled);
	ww_acquire_fini(ww_ctx);
पूर्ण

/**
 * regulator_lock_dependent - lock regulator's suppliers and coupled regulators
 * @rdev:			regulator source
 * @ww_ctx:			w/w mutex acquire context
 *
 * This function as a wrapper on regulator_lock_recursive(), which locks
 * all regulators related with rdev by coupling or supplying.
 */
अटल व्योम regulator_lock_dependent(काष्ठा regulator_dev *rdev,
				     काष्ठा ww_acquire_ctx *ww_ctx)
अणु
	काष्ठा regulator_dev *new_contended_rdev = शून्य;
	काष्ठा regulator_dev *old_contended_rdev = शून्य;
	पूर्णांक err;

	mutex_lock(&regulator_list_mutex);

	ww_acquire_init(ww_ctx, &regulator_ww_class);

	करो अणु
		अगर (new_contended_rdev) अणु
			ww_mutex_lock_slow(&new_contended_rdev->mutex, ww_ctx);
			old_contended_rdev = new_contended_rdev;
			old_contended_rdev->ref_cnt++;
		पूर्ण

		err = regulator_lock_recursive(rdev,
					       &new_contended_rdev,
					       &old_contended_rdev,
					       ww_ctx);

		अगर (old_contended_rdev)
			regulator_unlock(old_contended_rdev);

	पूर्ण जबतक (err == -EDEADLK);

	ww_acquire_करोne(ww_ctx);

	mutex_unlock(&regulator_list_mutex);
पूर्ण

/**
 * of_get_child_regulator - get a child regulator device node
 * based on supply name
 * @parent: Parent device node
 * @prop_name: Combination regulator supply name and "-supply"
 *
 * Traverse all child nodes.
 * Extract the child regulator device node corresponding to the supply name.
 * वापसs the device node corresponding to the regulator अगर found, अन्यथा
 * वापसs शून्य.
 */
अटल काष्ठा device_node *of_get_child_regulator(काष्ठा device_node *parent,
						  स्थिर अक्षर *prop_name)
अणु
	काष्ठा device_node *regnode = शून्य;
	काष्ठा device_node *child = शून्य;

	क्रम_each_child_of_node(parent, child) अणु
		regnode = of_parse_phandle(child, prop_name, 0);

		अगर (!regnode) अणु
			regnode = of_get_child_regulator(child, prop_name);
			अगर (regnode)
				जाओ err_node_put;
		पूर्ण अन्यथा अणु
			जाओ err_node_put;
		पूर्ण
	पूर्ण
	वापस शून्य;

err_node_put:
	of_node_put(child);
	वापस regnode;
पूर्ण

/**
 * of_get_regulator - get a regulator device node based on supply name
 * @dev: Device poपूर्णांकer क्रम the consumer (of regulator) device
 * @supply: regulator supply name
 *
 * Extract the regulator device node corresponding to the supply name.
 * वापसs the device node corresponding to the regulator अगर found, अन्यथा
 * वापसs शून्य.
 */
अटल काष्ठा device_node *of_get_regulator(काष्ठा device *dev, स्थिर अक्षर *supply)
अणु
	काष्ठा device_node *regnode = शून्य;
	अक्षर prop_name[64]; /* 64 is max size of property name */

	dev_dbg(dev, "Looking up %s-supply from device tree\n", supply);

	snम_लिखो(prop_name, 64, "%s-supply", supply);
	regnode = of_parse_phandle(dev->of_node, prop_name, 0);

	अगर (!regnode) अणु
		regnode = of_get_child_regulator(dev->of_node, prop_name);
		अगर (regnode)
			वापस regnode;

		dev_dbg(dev, "Looking up %s property in node %pOF failed\n",
				prop_name, dev->of_node);
		वापस शून्य;
	पूर्ण
	वापस regnode;
पूर्ण

/* Platक्रमm voltage स्थिरraपूर्णांक check */
पूर्णांक regulator_check_voltage(काष्ठा regulator_dev *rdev,
			    पूर्णांक *min_uV, पूर्णांक *max_uV)
अणु
	BUG_ON(*min_uV > *max_uV);

	अगर (!regulator_ops_is_valid(rdev, REGULATOR_CHANGE_VOLTAGE)) अणु
		rdev_err(rdev, "voltage operation not allowed\n");
		वापस -EPERM;
	पूर्ण

	अगर (*max_uV > rdev->स्थिरraपूर्णांकs->max_uV)
		*max_uV = rdev->स्थिरraपूर्णांकs->max_uV;
	अगर (*min_uV < rdev->स्थिरraपूर्णांकs->min_uV)
		*min_uV = rdev->स्थिरraपूर्णांकs->min_uV;

	अगर (*min_uV > *max_uV) अणु
		rdev_err(rdev, "unsupportable voltage range: %d-%duV\n",
			 *min_uV, *max_uV);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* वापस 0 अगर the state is valid */
अटल पूर्णांक regulator_check_states(suspend_state_t state)
अणु
	वापस (state > PM_SUSPEND_MAX || state == PM_SUSPEND_TO_IDLE);
पूर्ण

/* Make sure we select a voltage that suits the needs of all
 * regulator consumers
 */
पूर्णांक regulator_check_consumers(काष्ठा regulator_dev *rdev,
			      पूर्णांक *min_uV, पूर्णांक *max_uV,
			      suspend_state_t state)
अणु
	काष्ठा regulator *regulator;
	काष्ठा regulator_voltage *voltage;

	list_क्रम_each_entry(regulator, &rdev->consumer_list, list) अणु
		voltage = &regulator->voltage[state];
		/*
		 * Assume consumers that didn't say anything are OK
		 * with anything in the स्थिरraपूर्णांक range.
		 */
		अगर (!voltage->min_uV && !voltage->max_uV)
			जारी;

		अगर (*max_uV > voltage->max_uV)
			*max_uV = voltage->max_uV;
		अगर (*min_uV < voltage->min_uV)
			*min_uV = voltage->min_uV;
	पूर्ण

	अगर (*min_uV > *max_uV) अणु
		rdev_err(rdev, "Restricting voltage, %u-%uuV\n",
			*min_uV, *max_uV);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* current स्थिरraपूर्णांक check */
अटल पूर्णांक regulator_check_current_limit(काष्ठा regulator_dev *rdev,
					पूर्णांक *min_uA, पूर्णांक *max_uA)
अणु
	BUG_ON(*min_uA > *max_uA);

	अगर (!regulator_ops_is_valid(rdev, REGULATOR_CHANGE_CURRENT)) अणु
		rdev_err(rdev, "current operation not allowed\n");
		वापस -EPERM;
	पूर्ण

	अगर (*max_uA > rdev->स्थिरraपूर्णांकs->max_uA)
		*max_uA = rdev->स्थिरraपूर्णांकs->max_uA;
	अगर (*min_uA < rdev->स्थिरraपूर्णांकs->min_uA)
		*min_uA = rdev->स्थिरraपूर्णांकs->min_uA;

	अगर (*min_uA > *max_uA) अणु
		rdev_err(rdev, "unsupportable current range: %d-%duA\n",
			 *min_uA, *max_uA);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* operating mode स्थिरraपूर्णांक check */
अटल पूर्णांक regulator_mode_स्थिरrain(काष्ठा regulator_dev *rdev,
				    अचिन्हित पूर्णांक *mode)
अणु
	चयन (*mode) अणु
	हाल REGULATOR_MODE_FAST:
	हाल REGULATOR_MODE_NORMAL:
	हाल REGULATOR_MODE_IDLE:
	हाल REGULATOR_MODE_STANDBY:
		अवरोध;
	शेष:
		rdev_err(rdev, "invalid mode %x specified\n", *mode);
		वापस -EINVAL;
	पूर्ण

	अगर (!regulator_ops_is_valid(rdev, REGULATOR_CHANGE_MODE)) अणु
		rdev_err(rdev, "mode operation not allowed\n");
		वापस -EPERM;
	पूर्ण

	/* The modes are biपंचांगasks, the most घातer hungry modes having
	 * the lowest values. If the requested mode isn't supported
	 * try higher modes.
	 */
	जबतक (*mode) अणु
		अगर (rdev->स्थिरraपूर्णांकs->valid_modes_mask & *mode)
			वापस 0;
		*mode /= 2;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल अंतरभूत काष्ठा regulator_state *
regulator_get_suspend_state(काष्ठा regulator_dev *rdev, suspend_state_t state)
अणु
	अगर (rdev->स्थिरraपूर्णांकs == शून्य)
		वापस शून्य;

	चयन (state) अणु
	हाल PM_SUSPEND_STANDBY:
		वापस &rdev->स्थिरraपूर्णांकs->state_standby;
	हाल PM_SUSPEND_MEM:
		वापस &rdev->स्थिरraपूर्णांकs->state_mem;
	हाल PM_SUSPEND_MAX:
		वापस &rdev->स्थिरraपूर्णांकs->state_disk;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regulator_state *
regulator_get_suspend_state_check(काष्ठा regulator_dev *rdev, suspend_state_t state)
अणु
	स्थिर काष्ठा regulator_state *rstate;

	rstate = regulator_get_suspend_state(rdev, state);
	अगर (rstate == शून्य)
		वापस शून्य;

	/* If we have no suspend mode configuration करोn't set anything;
	 * only warn अगर the driver implements set_suspend_voltage or
	 * set_suspend_mode callback.
	 */
	अगर (rstate->enabled != ENABLE_IN_SUSPEND &&
	    rstate->enabled != DISABLE_IN_SUSPEND) अणु
		अगर (rdev->desc->ops->set_suspend_voltage ||
		    rdev->desc->ops->set_suspend_mode)
			rdev_warn(rdev, "No configuration\n");
		वापस शून्य;
	पूर्ण

	वापस rstate;
पूर्ण

अटल sमाप_प्रकार regulator_uV_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);
	पूर्णांक uV;

	regulator_lock(rdev);
	uV = regulator_get_voltage_rdev(rdev);
	regulator_unlock(rdev);

	अगर (uV < 0)
		वापस uV;
	वापस प्र_लिखो(buf, "%d\n", uV);
पूर्ण
अटल DEVICE_ATTR(microvolts, 0444, regulator_uV_show, शून्य);

अटल sमाप_प्रकार regulator_uA_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", _regulator_get_current_limit(rdev));
पूर्ण
अटल DEVICE_ATTR(microamps, 0444, regulator_uA_show, शून्य);

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", rdev_get_name(rdev));
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल स्थिर अक्षर *regulator_opmode_to_str(पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		वापस "fast";
	हाल REGULATOR_MODE_NORMAL:
		वापस "normal";
	हाल REGULATOR_MODE_IDLE:
		वापस "idle";
	हाल REGULATOR_MODE_STANDBY:
		वापस "standby";
	पूर्ण
	वापस "unknown";
पूर्ण

अटल sमाप_प्रकार regulator_prपूर्णांक_opmode(अक्षर *buf, पूर्णांक mode)
अणु
	वापस प्र_लिखो(buf, "%s\n", regulator_opmode_to_str(mode));
पूर्ण

अटल sमाप_प्रकार regulator_opmode_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);

	वापस regulator_prपूर्णांक_opmode(buf, _regulator_get_mode(rdev));
पूर्ण
अटल DEVICE_ATTR(opmode, 0444, regulator_opmode_show, शून्य);

अटल sमाप_प्रकार regulator_prपूर्णांक_state(अक्षर *buf, पूर्णांक state)
अणु
	अगर (state > 0)
		वापस प्र_लिखो(buf, "enabled\n");
	अन्यथा अगर (state == 0)
		वापस प्र_लिखो(buf, "disabled\n");
	अन्यथा
		वापस प्र_लिखो(buf, "unknown\n");
पूर्ण

अटल sमाप_प्रकार regulator_state_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);
	sमाप_प्रकार ret;

	regulator_lock(rdev);
	ret = regulator_prपूर्णांक_state(buf, _regulator_is_enabled(rdev));
	regulator_unlock(rdev);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR(state, 0444, regulator_state_show, शून्य);

अटल sमाप_प्रकार regulator_status_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);
	पूर्णांक status;
	अक्षर *label;

	status = rdev->desc->ops->get_status(rdev);
	अगर (status < 0)
		वापस status;

	चयन (status) अणु
	हाल REGULATOR_STATUS_OFF:
		label = "off";
		अवरोध;
	हाल REGULATOR_STATUS_ON:
		label = "on";
		अवरोध;
	हाल REGULATOR_STATUS_ERROR:
		label = "error";
		अवरोध;
	हाल REGULATOR_STATUS_FAST:
		label = "fast";
		अवरोध;
	हाल REGULATOR_STATUS_NORMAL:
		label = "normal";
		अवरोध;
	हाल REGULATOR_STATUS_IDLE:
		label = "idle";
		अवरोध;
	हाल REGULATOR_STATUS_STANDBY:
		label = "standby";
		अवरोध;
	हाल REGULATOR_STATUS_BYPASS:
		label = "bypass";
		अवरोध;
	हाल REGULATOR_STATUS_UNDEFINED:
		label = "undefined";
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	वापस प्र_लिखो(buf, "%s\n", label);
पूर्ण
अटल DEVICE_ATTR(status, 0444, regulator_status_show, शून्य);

अटल sमाप_प्रकार regulator_min_uA_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);

	अगर (!rdev->स्थिरraपूर्णांकs)
		वापस प्र_लिखो(buf, "constraint not defined\n");

	वापस प्र_लिखो(buf, "%d\n", rdev->स्थिरraपूर्णांकs->min_uA);
पूर्ण
अटल DEVICE_ATTR(min_microamps, 0444, regulator_min_uA_show, शून्य);

अटल sमाप_प्रकार regulator_max_uA_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);

	अगर (!rdev->स्थिरraपूर्णांकs)
		वापस प्र_लिखो(buf, "constraint not defined\n");

	वापस प्र_लिखो(buf, "%d\n", rdev->स्थिरraपूर्णांकs->max_uA);
पूर्ण
अटल DEVICE_ATTR(max_microamps, 0444, regulator_max_uA_show, शून्य);

अटल sमाप_प्रकार regulator_min_uV_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);

	अगर (!rdev->स्थिरraपूर्णांकs)
		वापस प्र_लिखो(buf, "constraint not defined\n");

	वापस प्र_लिखो(buf, "%d\n", rdev->स्थिरraपूर्णांकs->min_uV);
पूर्ण
अटल DEVICE_ATTR(min_microvolts, 0444, regulator_min_uV_show, शून्य);

अटल sमाप_प्रकार regulator_max_uV_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);

	अगर (!rdev->स्थिरraपूर्णांकs)
		वापस प्र_लिखो(buf, "constraint not defined\n");

	वापस प्र_लिखो(buf, "%d\n", rdev->स्थिरraपूर्णांकs->max_uV);
पूर्ण
अटल DEVICE_ATTR(max_microvolts, 0444, regulator_max_uV_show, शून्य);

अटल sमाप_प्रकार regulator_total_uA_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);
	काष्ठा regulator *regulator;
	पूर्णांक uA = 0;

	regulator_lock(rdev);
	list_क्रम_each_entry(regulator, &rdev->consumer_list, list) अणु
		अगर (regulator->enable_count)
			uA += regulator->uA_load;
	पूर्ण
	regulator_unlock(rdev);
	वापस प्र_लिखो(buf, "%d\n", uA);
पूर्ण
अटल DEVICE_ATTR(requested_microamps, 0444, regulator_total_uA_show, शून्य);

अटल sमाप_प्रकार num_users_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", rdev->use_count);
पूर्ण
अटल DEVICE_ATTR_RO(num_users);

अटल sमाप_प्रकार type_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);

	चयन (rdev->desc->type) अणु
	हाल REGULATOR_VOLTAGE:
		वापस प्र_लिखो(buf, "voltage\n");
	हाल REGULATOR_CURRENT:
		वापस प्र_लिखो(buf, "current\n");
	पूर्ण
	वापस प्र_लिखो(buf, "unknown\n");
पूर्ण
अटल DEVICE_ATTR_RO(type);

अटल sमाप_प्रकार regulator_suspend_mem_uV_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", rdev->स्थिरraपूर्णांकs->state_mem.uV);
पूर्ण
अटल DEVICE_ATTR(suspend_mem_microvolts, 0444,
		regulator_suspend_mem_uV_show, शून्य);

अटल sमाप_प्रकार regulator_suspend_disk_uV_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", rdev->स्थिरraपूर्णांकs->state_disk.uV);
पूर्ण
अटल DEVICE_ATTR(suspend_disk_microvolts, 0444,
		regulator_suspend_disk_uV_show, शून्य);

अटल sमाप_प्रकार regulator_suspend_standby_uV_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", rdev->स्थिरraपूर्णांकs->state_standby.uV);
पूर्ण
अटल DEVICE_ATTR(suspend_standby_microvolts, 0444,
		regulator_suspend_standby_uV_show, शून्य);

अटल sमाप_प्रकार regulator_suspend_mem_mode_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);

	वापस regulator_prपूर्णांक_opmode(buf,
		rdev->स्थिरraपूर्णांकs->state_mem.mode);
पूर्ण
अटल DEVICE_ATTR(suspend_mem_mode, 0444,
		regulator_suspend_mem_mode_show, शून्य);

अटल sमाप_प्रकार regulator_suspend_disk_mode_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);

	वापस regulator_prपूर्णांक_opmode(buf,
		rdev->स्थिरraपूर्णांकs->state_disk.mode);
पूर्ण
अटल DEVICE_ATTR(suspend_disk_mode, 0444,
		regulator_suspend_disk_mode_show, शून्य);

अटल sमाप_प्रकार regulator_suspend_standby_mode_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);

	वापस regulator_prपूर्णांक_opmode(buf,
		rdev->स्थिरraपूर्णांकs->state_standby.mode);
पूर्ण
अटल DEVICE_ATTR(suspend_standby_mode, 0444,
		regulator_suspend_standby_mode_show, शून्य);

अटल sमाप_प्रकार regulator_suspend_mem_state_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);

	वापस regulator_prपूर्णांक_state(buf,
			rdev->स्थिरraपूर्णांकs->state_mem.enabled);
पूर्ण
अटल DEVICE_ATTR(suspend_mem_state, 0444,
		regulator_suspend_mem_state_show, शून्य);

अटल sमाप_प्रकार regulator_suspend_disk_state_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);

	वापस regulator_prपूर्णांक_state(buf,
			rdev->स्थिरraपूर्णांकs->state_disk.enabled);
पूर्ण
अटल DEVICE_ATTR(suspend_disk_state, 0444,
		regulator_suspend_disk_state_show, शून्य);

अटल sमाप_प्रकार regulator_suspend_standby_state_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);

	वापस regulator_prपूर्णांक_state(buf,
			rdev->स्थिरraपूर्णांकs->state_standby.enabled);
पूर्ण
अटल DEVICE_ATTR(suspend_standby_state, 0444,
		regulator_suspend_standby_state_show, शून्य);

अटल sमाप_प्रकार regulator_bypass_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);
	स्थिर अक्षर *report;
	bool bypass;
	पूर्णांक ret;

	ret = rdev->desc->ops->get_bypass(rdev, &bypass);

	अगर (ret != 0)
		report = "unknown";
	अन्यथा अगर (bypass)
		report = "enabled";
	अन्यथा
		report = "disabled";

	वापस प्र_लिखो(buf, "%s\n", report);
पूर्ण
अटल DEVICE_ATTR(bypass, 0444,
		   regulator_bypass_show, शून्य);

/* Calculate the new optimum regulator operating mode based on the new total
 * consumer load. All locks held by caller
 */
अटल पूर्णांक drms_uA_update(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा regulator *sibling;
	पूर्णांक current_uA = 0, output_uV, input_uV, err;
	अचिन्हित पूर्णांक mode;

	/*
	 * first check to see अगर we can set modes at all, otherwise just
	 * tell the consumer everything is OK.
	 */
	अगर (!regulator_ops_is_valid(rdev, REGULATOR_CHANGE_DRMS)) अणु
		rdev_dbg(rdev, "DRMS operation not allowed\n");
		वापस 0;
	पूर्ण

	अगर (!rdev->desc->ops->get_optimum_mode &&
	    !rdev->desc->ops->set_load)
		वापस 0;

	अगर (!rdev->desc->ops->set_mode &&
	    !rdev->desc->ops->set_load)
		वापस -EINVAL;

	/* calc total requested load */
	list_क्रम_each_entry(sibling, &rdev->consumer_list, list) अणु
		अगर (sibling->enable_count)
			current_uA += sibling->uA_load;
	पूर्ण

	current_uA += rdev->स्थिरraपूर्णांकs->प्रणाली_load;

	अगर (rdev->desc->ops->set_load) अणु
		/* set the optimum mode क्रम our new total regulator load */
		err = rdev->desc->ops->set_load(rdev, current_uA);
		अगर (err < 0)
			rdev_err(rdev, "failed to set load %d: %pe\n",
				 current_uA, ERR_PTR(err));
	पूर्ण अन्यथा अणु
		/* get output voltage */
		output_uV = regulator_get_voltage_rdev(rdev);
		अगर (output_uV <= 0) अणु
			rdev_err(rdev, "invalid output voltage found\n");
			वापस -EINVAL;
		पूर्ण

		/* get input voltage */
		input_uV = 0;
		अगर (rdev->supply)
			input_uV = regulator_get_voltage(rdev->supply);
		अगर (input_uV <= 0)
			input_uV = rdev->स्थिरraपूर्णांकs->input_uV;
		अगर (input_uV <= 0) अणु
			rdev_err(rdev, "invalid input voltage found\n");
			वापस -EINVAL;
		पूर्ण

		/* now get the optimum mode क्रम our new total regulator load */
		mode = rdev->desc->ops->get_optimum_mode(rdev, input_uV,
							 output_uV, current_uA);

		/* check the new mode is allowed */
		err = regulator_mode_स्थिरrain(rdev, &mode);
		अगर (err < 0) अणु
			rdev_err(rdev, "failed to get optimum mode @ %d uA %d -> %d uV: %pe\n",
				 current_uA, input_uV, output_uV, ERR_PTR(err));
			वापस err;
		पूर्ण

		err = rdev->desc->ops->set_mode(rdev, mode);
		अगर (err < 0)
			rdev_err(rdev, "failed to set optimum mode %x: %pe\n",
				 mode, ERR_PTR(err));
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक __suspend_set_state(काष्ठा regulator_dev *rdev,
			       स्थिर काष्ठा regulator_state *rstate)
अणु
	पूर्णांक ret = 0;

	अगर (rstate->enabled == ENABLE_IN_SUSPEND &&
		rdev->desc->ops->set_suspend_enable)
		ret = rdev->desc->ops->set_suspend_enable(rdev);
	अन्यथा अगर (rstate->enabled == DISABLE_IN_SUSPEND &&
		rdev->desc->ops->set_suspend_disable)
		ret = rdev->desc->ops->set_suspend_disable(rdev);
	अन्यथा /* OK अगर set_suspend_enable or set_suspend_disable is शून्य */
		ret = 0;

	अगर (ret < 0) अणु
		rdev_err(rdev, "failed to enabled/disable: %pe\n", ERR_PTR(ret));
		वापस ret;
	पूर्ण

	अगर (rdev->desc->ops->set_suspend_voltage && rstate->uV > 0) अणु
		ret = rdev->desc->ops->set_suspend_voltage(rdev, rstate->uV);
		अगर (ret < 0) अणु
			rdev_err(rdev, "failed to set voltage: %pe\n", ERR_PTR(ret));
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (rdev->desc->ops->set_suspend_mode && rstate->mode > 0) अणु
		ret = rdev->desc->ops->set_suspend_mode(rdev, rstate->mode);
		अगर (ret < 0) अणु
			rdev_err(rdev, "failed to set mode: %pe\n", ERR_PTR(ret));
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक suspend_set_initial_state(काष्ठा regulator_dev *rdev)
अणु
	स्थिर काष्ठा regulator_state *rstate;

	rstate = regulator_get_suspend_state_check(rdev,
			rdev->स्थिरraपूर्णांकs->initial_state);
	अगर (!rstate)
		वापस 0;

	वापस __suspend_set_state(rdev, rstate);
पूर्ण

#अगर defined(DEBUG) || defined(CONFIG_DYNAMIC_DEBUG)
अटल व्योम prपूर्णांक_स्थिरraपूर्णांकs_debug(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा regulation_स्थिरraपूर्णांकs *स्थिरraपूर्णांकs = rdev->स्थिरraपूर्णांकs;
	अक्षर buf[160] = "";
	माप_प्रकार len = माप(buf) - 1;
	पूर्णांक count = 0;
	पूर्णांक ret;

	अगर (स्थिरraपूर्णांकs->min_uV && स्थिरraपूर्णांकs->max_uV) अणु
		अगर (स्थिरraपूर्णांकs->min_uV == स्थिरraपूर्णांकs->max_uV)
			count += scnम_लिखो(buf + count, len - count, "%d mV ",
					   स्थिरraपूर्णांकs->min_uV / 1000);
		अन्यथा
			count += scnम_लिखो(buf + count, len - count,
					   "%d <--> %d mV ",
					   स्थिरraपूर्णांकs->min_uV / 1000,
					   स्थिरraपूर्णांकs->max_uV / 1000);
	पूर्ण

	अगर (!स्थिरraपूर्णांकs->min_uV ||
	    स्थिरraपूर्णांकs->min_uV != स्थिरraपूर्णांकs->max_uV) अणु
		ret = regulator_get_voltage_rdev(rdev);
		अगर (ret > 0)
			count += scnम_लिखो(buf + count, len - count,
					   "at %d mV ", ret / 1000);
	पूर्ण

	अगर (स्थिरraपूर्णांकs->uV_offset)
		count += scnम_लिखो(buf + count, len - count, "%dmV offset ",
				   स्थिरraपूर्णांकs->uV_offset / 1000);

	अगर (स्थिरraपूर्णांकs->min_uA && स्थिरraपूर्णांकs->max_uA) अणु
		अगर (स्थिरraपूर्णांकs->min_uA == स्थिरraपूर्णांकs->max_uA)
			count += scnम_लिखो(buf + count, len - count, "%d mA ",
					   स्थिरraपूर्णांकs->min_uA / 1000);
		अन्यथा
			count += scnम_लिखो(buf + count, len - count,
					   "%d <--> %d mA ",
					   स्थिरraपूर्णांकs->min_uA / 1000,
					   स्थिरraपूर्णांकs->max_uA / 1000);
	पूर्ण

	अगर (!स्थिरraपूर्णांकs->min_uA ||
	    स्थिरraपूर्णांकs->min_uA != स्थिरraपूर्णांकs->max_uA) अणु
		ret = _regulator_get_current_limit(rdev);
		अगर (ret > 0)
			count += scnम_लिखो(buf + count, len - count,
					   "at %d mA ", ret / 1000);
	पूर्ण

	अगर (स्थिरraपूर्णांकs->valid_modes_mask & REGULATOR_MODE_FAST)
		count += scnम_लिखो(buf + count, len - count, "fast ");
	अगर (स्थिरraपूर्णांकs->valid_modes_mask & REGULATOR_MODE_NORMAL)
		count += scnम_लिखो(buf + count, len - count, "normal ");
	अगर (स्थिरraपूर्णांकs->valid_modes_mask & REGULATOR_MODE_IDLE)
		count += scnम_लिखो(buf + count, len - count, "idle ");
	अगर (स्थिरraपूर्णांकs->valid_modes_mask & REGULATOR_MODE_STANDBY)
		count += scnम_लिखो(buf + count, len - count, "standby ");

	अगर (!count)
		count = scnम_लिखो(buf, len, "no parameters");
	अन्यथा
		--count;

	count += scnम_लिखो(buf + count, len - count, ", %s",
		_regulator_is_enabled(rdev) ? "enabled" : "disabled");

	rdev_dbg(rdev, "%s\n", buf);
पूर्ण
#अन्यथा /* !DEBUG && !CONFIG_DYNAMIC_DEBUG */
अटल अंतरभूत व्योम prपूर्णांक_स्थिरraपूर्णांकs_debug(काष्ठा regulator_dev *rdev) अणुपूर्ण
#पूर्ण_अगर /* !DEBUG && !CONFIG_DYNAMIC_DEBUG */

अटल व्योम prपूर्णांक_स्थिरraपूर्णांकs(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा regulation_स्थिरraपूर्णांकs *स्थिरraपूर्णांकs = rdev->स्थिरraपूर्णांकs;

	prपूर्णांक_स्थिरraपूर्णांकs_debug(rdev);

	अगर ((स्थिरraपूर्णांकs->min_uV != स्थिरraपूर्णांकs->max_uV) &&
	    !regulator_ops_is_valid(rdev, REGULATOR_CHANGE_VOLTAGE))
		rdev_warn(rdev,
			  "Voltage range but no REGULATOR_CHANGE_VOLTAGE\n");
पूर्ण

अटल पूर्णांक machine_स्थिरraपूर्णांकs_voltage(काष्ठा regulator_dev *rdev,
	काष्ठा regulation_स्थिरraपूर्णांकs *स्थिरraपूर्णांकs)
अणु
	स्थिर काष्ठा regulator_ops *ops = rdev->desc->ops;
	पूर्णांक ret;

	/* करो we need to apply the स्थिरraपूर्णांक voltage */
	अगर (rdev->स्थिरraपूर्णांकs->apply_uV &&
	    rdev->स्थिरraपूर्णांकs->min_uV && rdev->स्थिरraपूर्णांकs->max_uV) अणु
		पूर्णांक target_min, target_max;
		पूर्णांक current_uV = regulator_get_voltage_rdev(rdev);

		अगर (current_uV == -ENOTRECOVERABLE) अणु
			/* This regulator can't be पढ़ो and must be initialized */
			rdev_info(rdev, "Setting %d-%duV\n",
				  rdev->स्थिरraपूर्णांकs->min_uV,
				  rdev->स्थिरraपूर्णांकs->max_uV);
			_regulator_करो_set_voltage(rdev,
						  rdev->स्थिरraपूर्णांकs->min_uV,
						  rdev->स्थिरraपूर्णांकs->max_uV);
			current_uV = regulator_get_voltage_rdev(rdev);
		पूर्ण

		अगर (current_uV < 0) अणु
			rdev_err(rdev,
				 "failed to get the current voltage: %pe\n",
				 ERR_PTR(current_uV));
			वापस current_uV;
		पूर्ण

		/*
		 * If we're below the minimum voltage move up to the
		 * minimum voltage, अगर we're above the maximum voltage
		 * then move करोwn to the maximum.
		 */
		target_min = current_uV;
		target_max = current_uV;

		अगर (current_uV < rdev->स्थिरraपूर्णांकs->min_uV) अणु
			target_min = rdev->स्थिरraपूर्णांकs->min_uV;
			target_max = rdev->स्थिरraपूर्णांकs->min_uV;
		पूर्ण

		अगर (current_uV > rdev->स्थिरraपूर्णांकs->max_uV) अणु
			target_min = rdev->स्थिरraपूर्णांकs->max_uV;
			target_max = rdev->स्थिरraपूर्णांकs->max_uV;
		पूर्ण

		अगर (target_min != current_uV || target_max != current_uV) अणु
			rdev_info(rdev, "Bringing %duV into %d-%duV\n",
				  current_uV, target_min, target_max);
			ret = _regulator_करो_set_voltage(
				rdev, target_min, target_max);
			अगर (ret < 0) अणु
				rdev_err(rdev,
					"failed to apply %d-%duV constraint: %pe\n",
					target_min, target_max, ERR_PTR(ret));
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	/* स्थिरrain machine-level voltage specs to fit
	 * the actual range supported by this regulator.
	 */
	अगर (ops->list_voltage && rdev->desc->n_voltages) अणु
		पूर्णांक	count = rdev->desc->n_voltages;
		पूर्णांक	i;
		पूर्णांक	min_uV = पूर्णांक_उच्च;
		पूर्णांक	max_uV = पूर्णांक_न्यून;
		पूर्णांक	cmin = स्थिरraपूर्णांकs->min_uV;
		पूर्णांक	cmax = स्थिरraपूर्णांकs->max_uV;

		/* it's safe to स्वतःconfigure fixed-voltage supplies
		 * and the स्थिरraपूर्णांकs are used by list_voltage.
		 */
		अगर (count == 1 && !cmin) अणु
			cmin = 1;
			cmax = पूर्णांक_उच्च;
			स्थिरraपूर्णांकs->min_uV = cmin;
			स्थिरraपूर्णांकs->max_uV = cmax;
		पूर्ण

		/* voltage स्थिरraपूर्णांकs are optional */
		अगर ((cmin == 0) && (cmax == 0))
			वापस 0;

		/* अन्यथा require explicit machine-level स्थिरraपूर्णांकs */
		अगर (cmin <= 0 || cmax <= 0 || cmax < cmin) अणु
			rdev_err(rdev, "invalid voltage constraints\n");
			वापस -EINVAL;
		पूर्ण

		/* no need to loop voltages अगर range is continuous */
		अगर (rdev->desc->continuous_voltage_range)
			वापस 0;

		/* initial: [cmin..cmax] valid, [min_uV..max_uV] not */
		क्रम (i = 0; i < count; i++) अणु
			पूर्णांक	value;

			value = ops->list_voltage(rdev, i);
			अगर (value <= 0)
				जारी;

			/* maybe adjust [min_uV..max_uV] */
			अगर (value >= cmin && value < min_uV)
				min_uV = value;
			अगर (value <= cmax && value > max_uV)
				max_uV = value;
		पूर्ण

		/* final: [min_uV..max_uV] valid अगरf स्थिरraपूर्णांकs valid */
		अगर (max_uV < min_uV) अणु
			rdev_err(rdev,
				 "unsupportable voltage constraints %u-%uuV\n",
				 min_uV, max_uV);
			वापस -EINVAL;
		पूर्ण

		/* use regulator's subset of machine स्थिरraपूर्णांकs */
		अगर (स्थिरraपूर्णांकs->min_uV < min_uV) अणु
			rdev_dbg(rdev, "override min_uV, %d -> %d\n",
				 स्थिरraपूर्णांकs->min_uV, min_uV);
			स्थिरraपूर्णांकs->min_uV = min_uV;
		पूर्ण
		अगर (स्थिरraपूर्णांकs->max_uV > max_uV) अणु
			rdev_dbg(rdev, "override max_uV, %d -> %d\n",
				 स्थिरraपूर्णांकs->max_uV, max_uV);
			स्थिरraपूर्णांकs->max_uV = max_uV;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक machine_स्थिरraपूर्णांकs_current(काष्ठा regulator_dev *rdev,
	काष्ठा regulation_स्थिरraपूर्णांकs *स्थिरraपूर्णांकs)
अणु
	स्थिर काष्ठा regulator_ops *ops = rdev->desc->ops;
	पूर्णांक ret;

	अगर (!स्थिरraपूर्णांकs->min_uA && !स्थिरraपूर्णांकs->max_uA)
		वापस 0;

	अगर (स्थिरraपूर्णांकs->min_uA > स्थिरraपूर्णांकs->max_uA) अणु
		rdev_err(rdev, "Invalid current constraints\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!ops->set_current_limit || !ops->get_current_limit) अणु
		rdev_warn(rdev, "Operation of current configuration missing\n");
		वापस 0;
	पूर्ण

	/* Set regulator current in स्थिरraपूर्णांकs range */
	ret = ops->set_current_limit(rdev, स्थिरraपूर्णांकs->min_uA,
			स्थिरraपूर्णांकs->max_uA);
	अगर (ret < 0) अणु
		rdev_err(rdev, "Failed to set current constraint, %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक _regulator_करो_enable(काष्ठा regulator_dev *rdev);

/**
 * set_machine_स्थिरraपूर्णांकs - sets regulator स्थिरraपूर्णांकs
 * @rdev: regulator source
 *
 * Allows platक्रमm initialisation code to define and स्थिरrain
 * regulator circuits e.g. valid voltage/current ranges, etc.  NOTE:
 * Constraपूर्णांकs *must* be set by platक्रमm code in order क्रम some
 * regulator operations to proceed i.e. set_voltage, set_current_limit,
 * set_mode.
 */
अटल पूर्णांक set_machine_स्थिरraपूर्णांकs(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret = 0;
	स्थिर काष्ठा regulator_ops *ops = rdev->desc->ops;

	ret = machine_स्थिरraपूर्णांकs_voltage(rdev, rdev->स्थिरraपूर्णांकs);
	अगर (ret != 0)
		वापस ret;

	ret = machine_स्थिरraपूर्णांकs_current(rdev, rdev->स्थिरraपूर्णांकs);
	अगर (ret != 0)
		वापस ret;

	अगर (rdev->स्थिरraपूर्णांकs->ilim_uA && ops->set_input_current_limit) अणु
		ret = ops->set_input_current_limit(rdev,
						   rdev->स्थिरraपूर्णांकs->ilim_uA);
		अगर (ret < 0) अणु
			rdev_err(rdev, "failed to set input limit: %pe\n", ERR_PTR(ret));
			वापस ret;
		पूर्ण
	पूर्ण

	/* करो we need to setup our suspend state */
	अगर (rdev->स्थिरraपूर्णांकs->initial_state) अणु
		ret = suspend_set_initial_state(rdev);
		अगर (ret < 0) अणु
			rdev_err(rdev, "failed to set suspend state: %pe\n", ERR_PTR(ret));
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (rdev->स्थिरraपूर्णांकs->initial_mode) अणु
		अगर (!ops->set_mode) अणु
			rdev_err(rdev, "no set_mode operation\n");
			वापस -EINVAL;
		पूर्ण

		ret = ops->set_mode(rdev, rdev->स्थिरraपूर्णांकs->initial_mode);
		अगर (ret < 0) अणु
			rdev_err(rdev, "failed to set initial mode: %pe\n", ERR_PTR(ret));
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अगर (rdev->स्थिरraपूर्णांकs->प्रणाली_load) अणु
		/*
		 * We'll only apply the initial प्रणाली load अगर an
		 * initial mode wasn't specअगरied.
		 */
		drms_uA_update(rdev);
	पूर्ण

	अगर ((rdev->स्थिरraपूर्णांकs->ramp_delay || rdev->स्थिरraपूर्णांकs->ramp_disable)
		&& ops->set_ramp_delay) अणु
		ret = ops->set_ramp_delay(rdev, rdev->स्थिरraपूर्णांकs->ramp_delay);
		अगर (ret < 0) अणु
			rdev_err(rdev, "failed to set ramp_delay: %pe\n", ERR_PTR(ret));
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (rdev->स्थिरraपूर्णांकs->pull_करोwn && ops->set_pull_करोwn) अणु
		ret = ops->set_pull_करोwn(rdev);
		अगर (ret < 0) अणु
			rdev_err(rdev, "failed to set pull down: %pe\n", ERR_PTR(ret));
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (rdev->स्थिरraपूर्णांकs->soft_start && ops->set_soft_start) अणु
		ret = ops->set_soft_start(rdev);
		अगर (ret < 0) अणु
			rdev_err(rdev, "failed to set soft start: %pe\n", ERR_PTR(ret));
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (rdev->स्थिरraपूर्णांकs->over_current_protection
		&& ops->set_over_current_protection) अणु
		ret = ops->set_over_current_protection(rdev);
		अगर (ret < 0) अणु
			rdev_err(rdev, "failed to set over current protection: %pe\n",
				 ERR_PTR(ret));
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (rdev->स्थिरraपूर्णांकs->active_disअक्षरge && ops->set_active_disअक्षरge) अणु
		bool ad_state = (rdev->स्थिरraपूर्णांकs->active_disअक्षरge ==
			      REGULATOR_ACTIVE_DISCHARGE_ENABLE) ? true : false;

		ret = ops->set_active_disअक्षरge(rdev, ad_state);
		अगर (ret < 0) अणु
			rdev_err(rdev, "failed to set active discharge: %pe\n", ERR_PTR(ret));
			वापस ret;
		पूर्ण
	पूर्ण

	/* If the स्थिरraपूर्णांकs say the regulator should be on at this poपूर्णांक
	 * and we have control then make sure it is enabled.
	 */
	अगर (rdev->स्थिरraपूर्णांकs->always_on || rdev->स्थिरraपूर्णांकs->boot_on) अणु
		/* If we want to enable this regulator, make sure that we know
		 * the supplying regulator.
		 */
		अगर (rdev->supply_name && !rdev->supply)
			वापस -EPROBE_DEFER;

		अगर (rdev->supply) अणु
			ret = regulator_enable(rdev->supply);
			अगर (ret < 0) अणु
				_regulator_put(rdev->supply);
				rdev->supply = शून्य;
				वापस ret;
			पूर्ण
		पूर्ण

		ret = _regulator_करो_enable(rdev);
		अगर (ret < 0 && ret != -EINVAL) अणु
			rdev_err(rdev, "failed to enable: %pe\n", ERR_PTR(ret));
			वापस ret;
		पूर्ण

		अगर (rdev->स्थिरraपूर्णांकs->always_on)
			rdev->use_count++;
	पूर्ण अन्यथा अगर (rdev->desc->off_on_delay) अणु
		rdev->last_off = kसमय_get();
	पूर्ण

	prपूर्णांक_स्थिरraपूर्णांकs(rdev);
	वापस 0;
पूर्ण

/**
 * set_supply - set regulator supply regulator
 * @rdev: regulator name
 * @supply_rdev: supply regulator name
 *
 * Called by platक्रमm initialisation code to set the supply regulator क्रम this
 * regulator. This ensures that a regulators supply will also be enabled by the
 * core अगर it's child is enabled.
 */
अटल पूर्णांक set_supply(काष्ठा regulator_dev *rdev,
		      काष्ठा regulator_dev *supply_rdev)
अणु
	पूर्णांक err;

	rdev_info(rdev, "supplied by %s\n", rdev_get_name(supply_rdev));

	अगर (!try_module_get(supply_rdev->owner))
		वापस -ENODEV;

	rdev->supply = create_regulator(supply_rdev, &rdev->dev, "SUPPLY");
	अगर (rdev->supply == शून्य) अणु
		err = -ENOMEM;
		वापस err;
	पूर्ण
	supply_rdev->खोलो_count++;

	वापस 0;
पूर्ण

/**
 * set_consumer_device_supply - Bind a regulator to a symbolic supply
 * @rdev:         regulator source
 * @consumer_dev_name: dev_name() string क्रम device supply applies to
 * @supply:       symbolic name क्रम supply
 *
 * Allows platक्रमm initialisation code to map physical regulator
 * sources to symbolic names क्रम supplies क्रम use by devices.  Devices
 * should use these symbolic names to request regulators, aव्योमing the
 * need to provide board-specअगरic regulator names as platक्रमm data.
 */
अटल पूर्णांक set_consumer_device_supply(काष्ठा regulator_dev *rdev,
				      स्थिर अक्षर *consumer_dev_name,
				      स्थिर अक्षर *supply)
अणु
	काष्ठा regulator_map *node, *new_node;
	पूर्णांक has_dev;

	अगर (supply == शून्य)
		वापस -EINVAL;

	अगर (consumer_dev_name != शून्य)
		has_dev = 1;
	अन्यथा
		has_dev = 0;

	new_node = kzalloc(माप(काष्ठा regulator_map), GFP_KERNEL);
	अगर (new_node == शून्य)
		वापस -ENOMEM;

	new_node->regulator = rdev;
	new_node->supply = supply;

	अगर (has_dev) अणु
		new_node->dev_name = kstrdup(consumer_dev_name, GFP_KERNEL);
		अगर (new_node->dev_name == शून्य) अणु
			kमुक्त(new_node);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	mutex_lock(&regulator_list_mutex);
	list_क्रम_each_entry(node, &regulator_map_list, list) अणु
		अगर (node->dev_name && consumer_dev_name) अणु
			अगर (म_भेद(node->dev_name, consumer_dev_name) != 0)
				जारी;
		पूर्ण अन्यथा अगर (node->dev_name || consumer_dev_name) अणु
			जारी;
		पूर्ण

		अगर (म_भेद(node->supply, supply) != 0)
			जारी;

		pr_debug("%s: %s/%s is '%s' supply; fail %s/%s\n",
			 consumer_dev_name,
			 dev_name(&node->regulator->dev),
			 node->regulator->desc->name,
			 supply,
			 dev_name(&rdev->dev), rdev_get_name(rdev));
		जाओ fail;
	पूर्ण

	list_add(&new_node->list, &regulator_map_list);
	mutex_unlock(&regulator_list_mutex);

	वापस 0;

fail:
	mutex_unlock(&regulator_list_mutex);
	kमुक्त(new_node->dev_name);
	kमुक्त(new_node);
	वापस -EBUSY;
पूर्ण

अटल व्योम unset_regulator_supplies(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा regulator_map *node, *n;

	list_क्रम_each_entry_safe(node, n, &regulator_map_list, list) अणु
		अगर (rdev == node->regulator) अणु
			list_del(&node->list);
			kमुक्त(node->dev_name);
			kमुक्त(node);
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल sमाप_प्रकार स्थिरraपूर्णांक_flags_पढ़ो_file(काष्ठा file *file,
					  अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	स्थिर काष्ठा regulator *regulator = file->निजी_data;
	स्थिर काष्ठा regulation_स्थिरraपूर्णांकs *c = regulator->rdev->स्थिरraपूर्णांकs;
	अक्षर *buf;
	sमाप_प्रकार ret;

	अगर (!c)
		वापस 0;

	buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = snम_लिखो(buf, PAGE_SIZE,
			"always_on: %u\n"
			"boot_on: %u\n"
			"apply_uV: %u\n"
			"ramp_disable: %u\n"
			"soft_start: %u\n"
			"pull_down: %u\n"
			"over_current_protection: %u\n",
			c->always_on,
			c->boot_on,
			c->apply_uV,
			c->ramp_disable,
			c->soft_start,
			c->pull_करोwn,
			c->over_current_protection);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, ret);
	kमुक्त(buf);

	वापस ret;
पूर्ण

#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations स्थिरraपूर्णांक_flags_fops = अणु
#अगर_घोषित CONFIG_DEBUG_FS
	.खोलो = simple_खोलो,
	.पढ़ो = स्थिरraपूर्णांक_flags_पढ़ो_file,
	.llseek = शेष_llseek,
#पूर्ण_अगर
पूर्ण;

#घोषणा REG_STR_SIZE	64

अटल काष्ठा regulator *create_regulator(काष्ठा regulator_dev *rdev,
					  काष्ठा device *dev,
					  स्थिर अक्षर *supply_name)
अणु
	काष्ठा regulator *regulator;
	पूर्णांक err = 0;

	अगर (dev) अणु
		अक्षर buf[REG_STR_SIZE];
		पूर्णांक size;

		size = snम_लिखो(buf, REG_STR_SIZE, "%s-%s",
				dev->kobj.name, supply_name);
		अगर (size >= REG_STR_SIZE)
			वापस शून्य;

		supply_name = kstrdup(buf, GFP_KERNEL);
		अगर (supply_name == शून्य)
			वापस शून्य;
	पूर्ण अन्यथा अणु
		supply_name = kstrdup_स्थिर(supply_name, GFP_KERNEL);
		अगर (supply_name == शून्य)
			वापस शून्य;
	पूर्ण

	regulator = kzalloc(माप(*regulator), GFP_KERNEL);
	अगर (regulator == शून्य) अणु
		kमुक्त(supply_name);
		वापस शून्य;
	पूर्ण

	regulator->rdev = rdev;
	regulator->supply_name = supply_name;

	regulator_lock(rdev);
	list_add(&regulator->list, &rdev->consumer_list);
	regulator_unlock(rdev);

	अगर (dev) अणु
		regulator->dev = dev;

		/* Add a link to the device sysfs entry */
		err = sysfs_create_link_nowarn(&rdev->dev.kobj, &dev->kobj,
					       supply_name);
		अगर (err) अणु
			rdev_dbg(rdev, "could not add device link %s: %pe\n",
				  dev->kobj.name, ERR_PTR(err));
			/* non-fatal */
		पूर्ण
	पूर्ण

	अगर (err != -EEXIST)
		regulator->debugfs = debugfs_create_dir(supply_name, rdev->debugfs);
	अगर (!regulator->debugfs) अणु
		rdev_dbg(rdev, "Failed to create debugfs directory\n");
	पूर्ण अन्यथा अणु
		debugfs_create_u32("uA_load", 0444, regulator->debugfs,
				   &regulator->uA_load);
		debugfs_create_u32("min_uV", 0444, regulator->debugfs,
				   &regulator->voltage[PM_SUSPEND_ON].min_uV);
		debugfs_create_u32("max_uV", 0444, regulator->debugfs,
				   &regulator->voltage[PM_SUSPEND_ON].max_uV);
		debugfs_create_file("constraint_flags", 0444,
				    regulator->debugfs, regulator,
				    &स्थिरraपूर्णांक_flags_fops);
	पूर्ण

	/*
	 * Check now अगर the regulator is an always on regulator - अगर
	 * it is then we करोn't need to करो nearly so much work क्रम
	 * enable/disable calls.
	 */
	अगर (!regulator_ops_is_valid(rdev, REGULATOR_CHANGE_STATUS) &&
	    _regulator_is_enabled(rdev))
		regulator->always_on = true;

	वापस regulator;
पूर्ण

अटल पूर्णांक _regulator_get_enable_समय(काष्ठा regulator_dev *rdev)
अणु
	अगर (rdev->स्थिरraपूर्णांकs && rdev->स्थिरraपूर्णांकs->enable_समय)
		वापस rdev->स्थिरraपूर्णांकs->enable_समय;
	अगर (rdev->desc->ops->enable_समय)
		वापस rdev->desc->ops->enable_समय(rdev);
	वापस rdev->desc->enable_समय;
पूर्ण

अटल काष्ठा regulator_supply_alias *regulator_find_supply_alias(
		काष्ठा device *dev, स्थिर अक्षर *supply)
अणु
	काष्ठा regulator_supply_alias *map;

	list_क्रम_each_entry(map, &regulator_supply_alias_list, list)
		अगर (map->src_dev == dev && म_भेद(map->src_supply, supply) == 0)
			वापस map;

	वापस शून्य;
पूर्ण

अटल व्योम regulator_supply_alias(काष्ठा device **dev, स्थिर अक्षर **supply)
अणु
	काष्ठा regulator_supply_alias *map;

	map = regulator_find_supply_alias(*dev, *supply);
	अगर (map) अणु
		dev_dbg(*dev, "Mapping supply %s to %s,%s\n",
				*supply, map->alias_supply,
				dev_name(map->alias_dev));
		*dev = map->alias_dev;
		*supply = map->alias_supply;
	पूर्ण
पूर्ण

अटल पूर्णांक regulator_match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा regulator_dev *r = dev_to_rdev(dev);

	वापस म_भेद(rdev_get_name(r), data) == 0;
पूर्ण

अटल काष्ठा regulator_dev *regulator_lookup_by_name(स्थिर अक्षर *name)
अणु
	काष्ठा device *dev;

	dev = class_find_device(&regulator_class, शून्य, name, regulator_match);

	वापस dev ? dev_to_rdev(dev) : शून्य;
पूर्ण

/**
 * regulator_dev_lookup - lookup a regulator device.
 * @dev: device क्रम regulator "consumer".
 * @supply: Supply name or regulator ID.
 *
 * If successful, वापसs a काष्ठा regulator_dev that corresponds to the name
 * @supply and with the embedded काष्ठा device refcount incremented by one.
 * The refcount must be dropped by calling put_device().
 * On failure one of the following ERR-PTR-encoded values is वापसed:
 * -ENODEV अगर lookup fails permanently, -EPROBE_DEFER अगर lookup could succeed
 * in the future.
 */
अटल काष्ठा regulator_dev *regulator_dev_lookup(काष्ठा device *dev,
						  स्थिर अक्षर *supply)
अणु
	काष्ठा regulator_dev *r = शून्य;
	काष्ठा device_node *node;
	काष्ठा regulator_map *map;
	स्थिर अक्षर *devname = शून्य;

	regulator_supply_alias(&dev, &supply);

	/* first करो a dt based lookup */
	अगर (dev && dev->of_node) अणु
		node = of_get_regulator(dev, supply);
		अगर (node) अणु
			r = of_find_regulator_by_node(node);
			अगर (r)
				वापस r;

			/*
			 * We have a node, but there is no device.
			 * assume it has not रेजिस्टरed yet.
			 */
			वापस ERR_PTR(-EPROBE_DEFER);
		पूर्ण
	पूर्ण

	/* अगर not found, try करोing it non-dt way */
	अगर (dev)
		devname = dev_name(dev);

	mutex_lock(&regulator_list_mutex);
	list_क्रम_each_entry(map, &regulator_map_list, list) अणु
		/* If the mapping has a device set up it must match */
		अगर (map->dev_name &&
		    (!devname || म_भेद(map->dev_name, devname)))
			जारी;

		अगर (म_भेद(map->supply, supply) == 0 &&
		    get_device(&map->regulator->dev)) अणु
			r = map->regulator;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&regulator_list_mutex);

	अगर (r)
		वापस r;

	r = regulator_lookup_by_name(supply);
	अगर (r)
		वापस r;

	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल पूर्णांक regulator_resolve_supply(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा regulator_dev *r;
	काष्ठा device *dev = rdev->dev.parent;
	पूर्णांक ret = 0;

	/* No supply to resolve? */
	अगर (!rdev->supply_name)
		वापस 0;

	/* Supply alपढ़ोy resolved? (fast-path without locking contention) */
	अगर (rdev->supply)
		वापस 0;

	r = regulator_dev_lookup(dev, rdev->supply_name);
	अगर (IS_ERR(r)) अणु
		ret = PTR_ERR(r);

		/* Did the lookup explicitly defer क्रम us? */
		अगर (ret == -EPROBE_DEFER)
			जाओ out;

		अगर (have_full_स्थिरraपूर्णांकs()) अणु
			r = dummy_regulator_rdev;
			get_device(&r->dev);
		पूर्ण अन्यथा अणु
			dev_err(dev, "Failed to resolve %s-supply for %s\n",
				rdev->supply_name, rdev->desc->name);
			ret = -EPROBE_DEFER;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (r == rdev) अणु
		dev_err(dev, "Supply for %s (%s) resolved to itself\n",
			rdev->desc->name, rdev->supply_name);
		अगर (!have_full_स्थिरraपूर्णांकs()) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		r = dummy_regulator_rdev;
		get_device(&r->dev);
	पूर्ण

	/*
	 * If the supply's parent device is not the same as the
	 * regulator's parent device, then ensure the parent device
	 * is bound beक्रमe we resolve the supply, in हाल the parent
	 * device get probe deferred and unरेजिस्टरs the supply.
	 */
	अगर (r->dev.parent && r->dev.parent != rdev->dev.parent) अणु
		अगर (!device_is_bound(r->dev.parent)) अणु
			put_device(&r->dev);
			ret = -EPROBE_DEFER;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Recursively resolve the supply of the supply */
	ret = regulator_resolve_supply(r);
	अगर (ret < 0) अणु
		put_device(&r->dev);
		जाओ out;
	पूर्ण

	/*
	 * Recheck rdev->supply with rdev->mutex lock held to aव्योम a race
	 * between rdev->supply null check and setting rdev->supply in
	 * set_supply() from concurrent tasks.
	 */
	regulator_lock(rdev);

	/* Supply just resolved by a concurrent task? */
	अगर (rdev->supply) अणु
		regulator_unlock(rdev);
		put_device(&r->dev);
		जाओ out;
	पूर्ण

	ret = set_supply(rdev, r);
	अगर (ret < 0) अणु
		regulator_unlock(rdev);
		put_device(&r->dev);
		जाओ out;
	पूर्ण

	regulator_unlock(rdev);

	/*
	 * In set_machine_स्थिरraपूर्णांकs() we may have turned this regulator on
	 * but we couldn't propagate to the supply if it hadn't been resolved
	 * yet.  Do it now.
	 */
	अगर (rdev->use_count) अणु
		ret = regulator_enable(rdev->supply);
		अगर (ret < 0) अणु
			_regulator_put(rdev->supply);
			rdev->supply = शून्य;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस ret;
पूर्ण

/* Internal regulator request function */
काष्ठा regulator *_regulator_get(काष्ठा device *dev, स्थिर अक्षर *id,
				 क्रमागत regulator_get_type get_type)
अणु
	काष्ठा regulator_dev *rdev;
	काष्ठा regulator *regulator;
	काष्ठा device_link *link;
	पूर्णांक ret;

	अगर (get_type >= MAX_GET_TYPE) अणु
		dev_err(dev, "invalid type %d in %s\n", get_type, __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (id == शून्य) अणु
		pr_err("get() with no identifier\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	rdev = regulator_dev_lookup(dev, id);
	अगर (IS_ERR(rdev)) अणु
		ret = PTR_ERR(rdev);

		/*
		 * If regulator_dev_lookup() fails with error other
		 * than -ENODEV our job here is करोne, we simply वापस it.
		 */
		अगर (ret != -ENODEV)
			वापस ERR_PTR(ret);

		अगर (!have_full_स्थिरraपूर्णांकs()) अणु
			dev_warn(dev,
				 "incomplete constraints, dummy supplies not allowed\n");
			वापस ERR_PTR(-ENODEV);
		पूर्ण

		चयन (get_type) अणु
		हाल NORMAL_GET:
			/*
			 * Assume that a regulator is physically present and
			 * enabled, even अगर it isn't hooked up, and just
			 * provide a dummy.
			 */
			dev_warn(dev, "supply %s not found, using dummy regulator\n", id);
			rdev = dummy_regulator_rdev;
			get_device(&rdev->dev);
			अवरोध;

		हाल EXCLUSIVE_GET:
			dev_warn(dev,
				 "dummy supplies not allowed for exclusive requests\n");
			fallthrough;

		शेष:
			वापस ERR_PTR(-ENODEV);
		पूर्ण
	पूर्ण

	अगर (rdev->exclusive) अणु
		regulator = ERR_PTR(-EPERM);
		put_device(&rdev->dev);
		वापस regulator;
	पूर्ण

	अगर (get_type == EXCLUSIVE_GET && rdev->खोलो_count) अणु
		regulator = ERR_PTR(-EBUSY);
		put_device(&rdev->dev);
		वापस regulator;
	पूर्ण

	mutex_lock(&regulator_list_mutex);
	ret = (rdev->coupling_desc.n_resolved != rdev->coupling_desc.n_coupled);
	mutex_unlock(&regulator_list_mutex);

	अगर (ret != 0) अणु
		regulator = ERR_PTR(-EPROBE_DEFER);
		put_device(&rdev->dev);
		वापस regulator;
	पूर्ण

	ret = regulator_resolve_supply(rdev);
	अगर (ret < 0) अणु
		regulator = ERR_PTR(ret);
		put_device(&rdev->dev);
		वापस regulator;
	पूर्ण

	अगर (!try_module_get(rdev->owner)) अणु
		regulator = ERR_PTR(-EPROBE_DEFER);
		put_device(&rdev->dev);
		वापस regulator;
	पूर्ण

	regulator = create_regulator(rdev, dev, id);
	अगर (regulator == शून्य) अणु
		regulator = ERR_PTR(-ENOMEM);
		module_put(rdev->owner);
		put_device(&rdev->dev);
		वापस regulator;
	पूर्ण

	rdev->खोलो_count++;
	अगर (get_type == EXCLUSIVE_GET) अणु
		rdev->exclusive = 1;

		ret = _regulator_is_enabled(rdev);
		अगर (ret > 0)
			rdev->use_count = 1;
		अन्यथा
			rdev->use_count = 0;
	पूर्ण

	link = device_link_add(dev, &rdev->dev, DL_FLAG_STATELESS);
	अगर (!IS_ERR_OR_शून्य(link))
		regulator->device_link = true;

	वापस regulator;
पूर्ण

/**
 * regulator_get - lookup and obtain a reference to a regulator.
 * @dev: device क्रम regulator "consumer"
 * @id: Supply name or regulator ID.
 *
 * Returns a काष्ठा regulator corresponding to the regulator producer,
 * or IS_ERR() condition containing त्रुटि_सं.
 *
 * Use of supply names configured via set_consumer_device_supply() is
 * strongly encouraged.  It is recommended that the supply name used
 * should match the name used क्रम the supply and/or the relevant
 * device pins in the datasheet.
 */
काष्ठा regulator *regulator_get(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	वापस _regulator_get(dev, id, NORMAL_GET);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_get);

/**
 * regulator_get_exclusive - obtain exclusive access to a regulator.
 * @dev: device क्रम regulator "consumer"
 * @id: Supply name or regulator ID.
 *
 * Returns a काष्ठा regulator corresponding to the regulator producer,
 * or IS_ERR() condition containing त्रुटि_सं.  Other consumers will be
 * unable to obtain this regulator जबतक this reference is held and the
 * use count क्रम the regulator will be initialised to reflect the current
 * state of the regulator.
 *
 * This is पूर्णांकended क्रम use by consumers which cannot tolerate shared
 * use of the regulator such as those which need to क्रमce the
 * regulator off क्रम correct operation of the hardware they are
 * controlling.
 *
 * Use of supply names configured via set_consumer_device_supply() is
 * strongly encouraged.  It is recommended that the supply name used
 * should match the name used क्रम the supply and/or the relevant
 * device pins in the datasheet.
 */
काष्ठा regulator *regulator_get_exclusive(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	वापस _regulator_get(dev, id, EXCLUSIVE_GET);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_get_exclusive);

/**
 * regulator_get_optional - obtain optional access to a regulator.
 * @dev: device क्रम regulator "consumer"
 * @id: Supply name or regulator ID.
 *
 * Returns a काष्ठा regulator corresponding to the regulator producer,
 * or IS_ERR() condition containing त्रुटि_सं.
 *
 * This is पूर्णांकended क्रम use by consumers क्रम devices which can have
 * some supplies unconnected in normal use, such as some MMC devices.
 * It can allow the regulator core to provide stub supplies क्रम other
 * supplies requested using normal regulator_get() calls without
 * disrupting the operation of drivers that can handle असलent
 * supplies.
 *
 * Use of supply names configured via set_consumer_device_supply() is
 * strongly encouraged.  It is recommended that the supply name used
 * should match the name used क्रम the supply and/or the relevant
 * device pins in the datasheet.
 */
काष्ठा regulator *regulator_get_optional(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	वापस _regulator_get(dev, id, OPTIONAL_GET);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_get_optional);

अटल व्योम destroy_regulator(काष्ठा regulator *regulator)
अणु
	काष्ठा regulator_dev *rdev = regulator->rdev;

	debugfs_हटाओ_recursive(regulator->debugfs);

	अगर (regulator->dev) अणु
		अगर (regulator->device_link)
			device_link_हटाओ(regulator->dev, &rdev->dev);

		/* हटाओ any sysfs entries */
		sysfs_हटाओ_link(&rdev->dev.kobj, regulator->supply_name);
	पूर्ण

	regulator_lock(rdev);
	list_del(&regulator->list);

	rdev->खोलो_count--;
	rdev->exclusive = 0;
	regulator_unlock(rdev);

	kमुक्त_स्थिर(regulator->supply_name);
	kमुक्त(regulator);
पूर्ण

/* regulator_list_mutex lock held by regulator_put() */
अटल व्योम _regulator_put(काष्ठा regulator *regulator)
अणु
	काष्ठा regulator_dev *rdev;

	अगर (IS_ERR_OR_शून्य(regulator))
		वापस;

	lockdep_निश्चित_held_once(&regulator_list_mutex);

	/* Docs say you must disable beक्रमe calling regulator_put() */
	WARN_ON(regulator->enable_count);

	rdev = regulator->rdev;

	destroy_regulator(regulator);

	module_put(rdev->owner);
	put_device(&rdev->dev);
पूर्ण

/**
 * regulator_put - "free" the regulator source
 * @regulator: regulator source
 *
 * Note: drivers must ensure that all regulator_enable calls made on this
 * regulator source are balanced by regulator_disable calls prior to calling
 * this function.
 */
व्योम regulator_put(काष्ठा regulator *regulator)
अणु
	mutex_lock(&regulator_list_mutex);
	_regulator_put(regulator);
	mutex_unlock(&regulator_list_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_put);

/**
 * regulator_रेजिस्टर_supply_alias - Provide device alias क्रम supply lookup
 *
 * @dev: device that will be given as the regulator "consumer"
 * @id: Supply name or regulator ID
 * @alias_dev: device that should be used to lookup the supply
 * @alias_id: Supply name or regulator ID that should be used to lookup the
 * supply
 *
 * All lookups क्रम id on dev will instead be conducted क्रम alias_id on
 * alias_dev.
 */
पूर्णांक regulator_रेजिस्टर_supply_alias(काष्ठा device *dev, स्थिर अक्षर *id,
				    काष्ठा device *alias_dev,
				    स्थिर अक्षर *alias_id)
अणु
	काष्ठा regulator_supply_alias *map;

	map = regulator_find_supply_alias(dev, id);
	अगर (map)
		वापस -EEXIST;

	map = kzalloc(माप(काष्ठा regulator_supply_alias), GFP_KERNEL);
	अगर (!map)
		वापस -ENOMEM;

	map->src_dev = dev;
	map->src_supply = id;
	map->alias_dev = alias_dev;
	map->alias_supply = alias_id;

	list_add(&map->list, &regulator_supply_alias_list);

	pr_info("Adding alias for supply %s,%s -> %s,%s\n",
		id, dev_name(dev), alias_id, dev_name(alias_dev));

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_रेजिस्टर_supply_alias);

/**
 * regulator_unरेजिस्टर_supply_alias - Remove device alias
 *
 * @dev: device that will be given as the regulator "consumer"
 * @id: Supply name or regulator ID
 *
 * Remove a lookup alias अगर one exists क्रम id on dev.
 */
व्योम regulator_unरेजिस्टर_supply_alias(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	काष्ठा regulator_supply_alias *map;

	map = regulator_find_supply_alias(dev, id);
	अगर (map) अणु
		list_del(&map->list);
		kमुक्त(map);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(regulator_unरेजिस्टर_supply_alias);

/**
 * regulator_bulk_रेजिस्टर_supply_alias - रेजिस्टर multiple aliases
 *
 * @dev: device that will be given as the regulator "consumer"
 * @id: List of supply names or regulator IDs
 * @alias_dev: device that should be used to lookup the supply
 * @alias_id: List of supply names or regulator IDs that should be used to
 * lookup the supply
 * @num_id: Number of aliases to रेजिस्टर
 *
 * @वापस 0 on success, an त्रुटि_सं on failure.
 *
 * This helper function allows drivers to रेजिस्टर several supply
 * aliases in one operation.  If any of the aliases cannot be
 * रेजिस्टरed any aliases that were रेजिस्टरed will be हटाओd
 * beक्रमe वापसing to the caller.
 */
पूर्णांक regulator_bulk_रेजिस्टर_supply_alias(काष्ठा device *dev,
					 स्थिर अक्षर *स्थिर *id,
					 काष्ठा device *alias_dev,
					 स्थिर अक्षर *स्थिर *alias_id,
					 पूर्णांक num_id)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < num_id; ++i) अणु
		ret = regulator_रेजिस्टर_supply_alias(dev, id[i], alias_dev,
						      alias_id[i]);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	dev_err(dev,
		"Failed to create supply alias %s,%s -> %s,%s\n",
		id[i], dev_name(dev), alias_id[i], dev_name(alias_dev));

	जबतक (--i >= 0)
		regulator_unरेजिस्टर_supply_alias(dev, id[i]);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_bulk_रेजिस्टर_supply_alias);

/**
 * regulator_bulk_unरेजिस्टर_supply_alias - unरेजिस्टर multiple aliases
 *
 * @dev: device that will be given as the regulator "consumer"
 * @id: List of supply names or regulator IDs
 * @num_id: Number of aliases to unरेजिस्टर
 *
 * This helper function allows drivers to unरेजिस्टर several supply
 * aliases in one operation.
 */
व्योम regulator_bulk_unरेजिस्टर_supply_alias(काष्ठा device *dev,
					    स्थिर अक्षर *स्थिर *id,
					    पूर्णांक num_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_id; ++i)
		regulator_unरेजिस्टर_supply_alias(dev, id[i]);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_bulk_unरेजिस्टर_supply_alias);


/* Manage enable GPIO list. Same GPIO pin can be shared among regulators */
अटल पूर्णांक regulator_ena_gpio_request(काष्ठा regulator_dev *rdev,
				स्थिर काष्ठा regulator_config *config)
अणु
	काष्ठा regulator_enable_gpio *pin, *new_pin;
	काष्ठा gpio_desc *gpiod;

	gpiod = config->ena_gpiod;
	new_pin = kzalloc(माप(*new_pin), GFP_KERNEL);

	mutex_lock(&regulator_list_mutex);

	list_क्रम_each_entry(pin, &regulator_ena_gpio_list, list) अणु
		अगर (pin->gpiod == gpiod) अणु
			rdev_dbg(rdev, "GPIO is already used\n");
			जाओ update_ena_gpio_to_rdev;
		पूर्ण
	पूर्ण

	अगर (new_pin == शून्य) अणु
		mutex_unlock(&regulator_list_mutex);
		वापस -ENOMEM;
	पूर्ण

	pin = new_pin;
	new_pin = शून्य;

	pin->gpiod = gpiod;
	list_add(&pin->list, &regulator_ena_gpio_list);

update_ena_gpio_to_rdev:
	pin->request_count++;
	rdev->ena_pin = pin;

	mutex_unlock(&regulator_list_mutex);
	kमुक्त(new_pin);

	वापस 0;
पूर्ण

अटल व्योम regulator_ena_gpio_मुक्त(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा regulator_enable_gpio *pin, *n;

	अगर (!rdev->ena_pin)
		वापस;

	/* Free the GPIO only in हाल of no use */
	list_क्रम_each_entry_safe(pin, n, &regulator_ena_gpio_list, list) अणु
		अगर (pin != rdev->ena_pin)
			जारी;

		अगर (--pin->request_count)
			अवरोध;

		gpiod_put(pin->gpiod);
		list_del(&pin->list);
		kमुक्त(pin);
		अवरोध;
	पूर्ण

	rdev->ena_pin = शून्य;
पूर्ण

/**
 * regulator_ena_gpio_ctrl - balance enable_count of each GPIO and actual GPIO pin control
 * @rdev: regulator_dev काष्ठाure
 * @enable: enable GPIO at initial use?
 *
 * GPIO is enabled in हाल of initial use. (enable_count is 0)
 * GPIO is disabled when it is not shared any more. (enable_count <= 1)
 */
अटल पूर्णांक regulator_ena_gpio_ctrl(काष्ठा regulator_dev *rdev, bool enable)
अणु
	काष्ठा regulator_enable_gpio *pin = rdev->ena_pin;

	अगर (!pin)
		वापस -EINVAL;

	अगर (enable) अणु
		/* Enable GPIO at initial use */
		अगर (pin->enable_count == 0)
			gpiod_set_value_cansleep(pin->gpiod, 1);

		pin->enable_count++;
	पूर्ण अन्यथा अणु
		अगर (pin->enable_count > 1) अणु
			pin->enable_count--;
			वापस 0;
		पूर्ण

		/* Disable GPIO अगर not used */
		अगर (pin->enable_count <= 1) अणु
			gpiod_set_value_cansleep(pin->gpiod, 0);
			pin->enable_count = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * _regulator_enable_delay - a delay helper function
 * @delay: समय to delay in microseconds
 *
 * Delay क्रम the requested amount of समय as per the guidelines in:
 *
 *     Documentation/समयrs/समयrs-howto.rst
 *
 * The assumption here is that regulators will never be enabled in
 * atomic context and thereक्रमe sleeping functions can be used.
 */
अटल व्योम _regulator_enable_delay(अचिन्हित पूर्णांक delay)
अणु
	अचिन्हित पूर्णांक ms = delay / 1000;
	अचिन्हित पूर्णांक us = delay % 1000;

	अगर (ms > 0) अणु
		/*
		 * For small enough values, handle super-millisecond
		 * delays in the usleep_range() call below.
		 */
		अगर (ms < 20)
			us += ms * 1000;
		अन्यथा
			msleep(ms);
	पूर्ण

	/*
	 * Give the scheduler some room to coalesce with any other
	 * wakeup sources. For delays लघुer than 10 us, करोn't even
	 * bother setting up high-resolution समयrs and just busy-
	 * loop.
	 */
	अगर (us >= 10)
		usleep_range(us, us + 100);
	अन्यथा
		udelay(us);
पूर्ण

/**
 * _regulator_check_status_enabled
 *
 * A helper function to check अगर the regulator status can be पूर्णांकerpreted
 * as 'regulator is enabled'.
 * @rdev: the regulator device to check
 *
 * Return:
 * * 1			- अगर status shows regulator is in enabled state
 * * 0			- अगर not enabled state
 * * Error Value	- as received from ops->get_status()
 */
अटल अंतरभूत पूर्णांक _regulator_check_status_enabled(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret = rdev->desc->ops->get_status(rdev);

	अगर (ret < 0) अणु
		rdev_info(rdev, "get_status returned error: %d\n", ret);
		वापस ret;
	पूर्ण

	चयन (ret) अणु
	हाल REGULATOR_STATUS_OFF:
	हाल REGULATOR_STATUS_ERROR:
	हाल REGULATOR_STATUS_UNDEFINED:
		वापस 0;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल पूर्णांक _regulator_करो_enable(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret, delay;

	/* Query beक्रमe enabling in हाल configuration dependent.  */
	ret = _regulator_get_enable_समय(rdev);
	अगर (ret >= 0) अणु
		delay = ret;
	पूर्ण अन्यथा अणु
		rdev_warn(rdev, "enable_time() failed: %pe\n", ERR_PTR(ret));
		delay = 0;
	पूर्ण

	trace_regulator_enable(rdev_get_name(rdev));

	अगर (rdev->desc->off_on_delay && rdev->last_off) अणु
		/* अगर needed, keep a distance of off_on_delay from last समय
		 * this regulator was disabled.
		 */
		kसमय_प्रकार end = kसमय_add_us(rdev->last_off, rdev->desc->off_on_delay);
		s64 reमुख्यing = kसमय_us_delta(end, kसमय_get());

		अगर (reमुख्यing > 0)
			_regulator_enable_delay(reमुख्यing);
	पूर्ण

	अगर (rdev->ena_pin) अणु
		अगर (!rdev->ena_gpio_state) अणु
			ret = regulator_ena_gpio_ctrl(rdev, true);
			अगर (ret < 0)
				वापस ret;
			rdev->ena_gpio_state = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (rdev->desc->ops->enable) अणु
		ret = rdev->desc->ops->enable(rdev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	/* Allow the regulator to ramp; it would be useful to extend
	 * this क्रम bulk operations so that the regulators can ramp
	 * together.
	 */
	trace_regulator_enable_delay(rdev_get_name(rdev));

	/* If poll_enabled_समय is set, poll upto the delay calculated
	 * above, delaying poll_enabled_समय uS to check अगर the regulator
	 * actually got enabled.
	 * If the regulator isn't enabled after enable_delay has
	 * expired, वापस -ETIMEDOUT.
	 */
	अगर (rdev->desc->poll_enabled_समय) अणु
		अचिन्हित पूर्णांक समय_reमुख्यing = delay;

		जबतक (समय_reमुख्यing > 0) अणु
			_regulator_enable_delay(rdev->desc->poll_enabled_समय);

			अगर (rdev->desc->ops->get_status) अणु
				ret = _regulator_check_status_enabled(rdev);
				अगर (ret < 0)
					वापस ret;
				अन्यथा अगर (ret)
					अवरोध;
			पूर्ण अन्यथा अगर (rdev->desc->ops->is_enabled(rdev))
				अवरोध;

			समय_reमुख्यing -= rdev->desc->poll_enabled_समय;
		पूर्ण

		अगर (समय_reमुख्यing <= 0) अणु
			rdev_err(rdev, "Enabled check timed out\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण अन्यथा अणु
		_regulator_enable_delay(delay);
	पूर्ण

	trace_regulator_enable_complete(rdev_get_name(rdev));

	वापस 0;
पूर्ण

/**
 * _regulator_handle_consumer_enable - handle that a consumer enabled
 * @regulator: regulator source
 *
 * Some things on a regulator consumer (like the contribution towards total
 * load on the regulator) only have an effect when the consumer wants the
 * regulator enabled.  Explained in example with two consumers of the same
 * regulator:
 *   consumer A: set_load(100);       => total load = 0
 *   consumer A: regulator_enable();  => total load = 100
 *   consumer B: set_load(1000);      => total load = 100
 *   consumer B: regulator_enable();  => total load = 1100
 *   consumer A: regulator_disable(); => total_load = 1000
 *
 * This function (together with _regulator_handle_consumer_disable) is
 * responsible क्रम keeping track of the refcount क्रम a given regulator consumer
 * and applying / unapplying these things.
 *
 * Returns 0 upon no error; -error upon error.
 */
अटल पूर्णांक _regulator_handle_consumer_enable(काष्ठा regulator *regulator)
अणु
	काष्ठा regulator_dev *rdev = regulator->rdev;

	lockdep_निश्चित_held_once(&rdev->mutex.base);

	regulator->enable_count++;
	अगर (regulator->uA_load && regulator->enable_count == 1)
		वापस drms_uA_update(rdev);

	वापस 0;
पूर्ण

/**
 * _regulator_handle_consumer_disable - handle that a consumer disabled
 * @regulator: regulator source
 *
 * The opposite of _regulator_handle_consumer_enable().
 *
 * Returns 0 upon no error; -error upon error.
 */
अटल पूर्णांक _regulator_handle_consumer_disable(काष्ठा regulator *regulator)
अणु
	काष्ठा regulator_dev *rdev = regulator->rdev;

	lockdep_निश्चित_held_once(&rdev->mutex.base);

	अगर (!regulator->enable_count) अणु
		rdev_err(rdev, "Underflow of regulator enable count\n");
		वापस -EINVAL;
	पूर्ण

	regulator->enable_count--;
	अगर (regulator->uA_load && regulator->enable_count == 0)
		वापस drms_uA_update(rdev);

	वापस 0;
पूर्ण

/* locks held by regulator_enable() */
अटल पूर्णांक _regulator_enable(काष्ठा regulator *regulator)
अणु
	काष्ठा regulator_dev *rdev = regulator->rdev;
	पूर्णांक ret;

	lockdep_निश्चित_held_once(&rdev->mutex.base);

	अगर (rdev->use_count == 0 && rdev->supply) अणु
		ret = _regulator_enable(rdev->supply);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* balance only अगर there are regulators coupled */
	अगर (rdev->coupling_desc.n_coupled > 1) अणु
		ret = regulator_balance_voltage(rdev, PM_SUSPEND_ON);
		अगर (ret < 0)
			जाओ err_disable_supply;
	पूर्ण

	ret = _regulator_handle_consumer_enable(regulator);
	अगर (ret < 0)
		जाओ err_disable_supply;

	अगर (rdev->use_count == 0) अणु
		/*
		 * The regulator may alपढ़ोy be enabled अगर it's not चयनable
		 * or was left on
		 */
		ret = _regulator_is_enabled(rdev);
		अगर (ret == -EINVAL || ret == 0) अणु
			अगर (!regulator_ops_is_valid(rdev,
					REGULATOR_CHANGE_STATUS)) अणु
				ret = -EPERM;
				जाओ err_consumer_disable;
			पूर्ण

			ret = _regulator_करो_enable(rdev);
			अगर (ret < 0)
				जाओ err_consumer_disable;

			_notअगरier_call_chain(rdev, REGULATOR_EVENT_ENABLE,
					     शून्य);
		पूर्ण अन्यथा अगर (ret < 0) अणु
			rdev_err(rdev, "is_enabled() failed: %pe\n", ERR_PTR(ret));
			जाओ err_consumer_disable;
		पूर्ण
		/* Fallthrough on positive वापस values - alपढ़ोy enabled */
	पूर्ण

	rdev->use_count++;

	वापस 0;

err_consumer_disable:
	_regulator_handle_consumer_disable(regulator);

err_disable_supply:
	अगर (rdev->use_count == 0 && rdev->supply)
		_regulator_disable(rdev->supply);

	वापस ret;
पूर्ण

/**
 * regulator_enable - enable regulator output
 * @regulator: regulator source
 *
 * Request that the regulator be enabled with the regulator output at
 * the predefined voltage or current value.  Calls to regulator_enable()
 * must be balanced with calls to regulator_disable().
 *
 * NOTE: the output value can be set by other drivers, boot loader or may be
 * hardwired in the regulator.
 */
पूर्णांक regulator_enable(काष्ठा regulator *regulator)
अणु
	काष्ठा regulator_dev *rdev = regulator->rdev;
	काष्ठा ww_acquire_ctx ww_ctx;
	पूर्णांक ret;

	regulator_lock_dependent(rdev, &ww_ctx);
	ret = _regulator_enable(regulator);
	regulator_unlock_dependent(rdev, &ww_ctx);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_enable);

अटल पूर्णांक _regulator_करो_disable(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret;

	trace_regulator_disable(rdev_get_name(rdev));

	अगर (rdev->ena_pin) अणु
		अगर (rdev->ena_gpio_state) अणु
			ret = regulator_ena_gpio_ctrl(rdev, false);
			अगर (ret < 0)
				वापस ret;
			rdev->ena_gpio_state = 0;
		पूर्ण

	पूर्ण अन्यथा अगर (rdev->desc->ops->disable) अणु
		ret = rdev->desc->ops->disable(rdev);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	अगर (rdev->desc->off_on_delay)
		rdev->last_off = kसमय_get();

	trace_regulator_disable_complete(rdev_get_name(rdev));

	वापस 0;
पूर्ण

/* locks held by regulator_disable() */
अटल पूर्णांक _regulator_disable(काष्ठा regulator *regulator)
अणु
	काष्ठा regulator_dev *rdev = regulator->rdev;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held_once(&rdev->mutex.base);

	अगर (WARN(rdev->use_count <= 0,
		 "unbalanced disables for %s\n", rdev_get_name(rdev)))
		वापस -EIO;

	/* are we the last user and permitted to disable ? */
	अगर (rdev->use_count == 1 &&
	    (rdev->स्थिरraपूर्णांकs && !rdev->स्थिरraपूर्णांकs->always_on)) अणु

		/* we are last user */
		अगर (regulator_ops_is_valid(rdev, REGULATOR_CHANGE_STATUS)) अणु
			ret = _notअगरier_call_chain(rdev,
						   REGULATOR_EVENT_PRE_DISABLE,
						   शून्य);
			अगर (ret & NOTIFY_STOP_MASK)
				वापस -EINVAL;

			ret = _regulator_करो_disable(rdev);
			अगर (ret < 0) अणु
				rdev_err(rdev, "failed to disable: %pe\n", ERR_PTR(ret));
				_notअगरier_call_chain(rdev,
						REGULATOR_EVENT_ABORT_DISABLE,
						शून्य);
				वापस ret;
			पूर्ण
			_notअगरier_call_chain(rdev, REGULATOR_EVENT_DISABLE,
					शून्य);
		पूर्ण

		rdev->use_count = 0;
	पूर्ण अन्यथा अगर (rdev->use_count > 1) अणु
		rdev->use_count--;
	पूर्ण

	अगर (ret == 0)
		ret = _regulator_handle_consumer_disable(regulator);

	अगर (ret == 0 && rdev->coupling_desc.n_coupled > 1)
		ret = regulator_balance_voltage(rdev, PM_SUSPEND_ON);

	अगर (ret == 0 && rdev->use_count == 0 && rdev->supply)
		ret = _regulator_disable(rdev->supply);

	वापस ret;
पूर्ण

/**
 * regulator_disable - disable regulator output
 * @regulator: regulator source
 *
 * Disable the regulator output voltage or current.  Calls to
 * regulator_enable() must be balanced with calls to
 * regulator_disable().
 *
 * NOTE: this will only disable the regulator output अगर no other consumer
 * devices have it enabled, the regulator device supports disabling and
 * machine स्थिरraपूर्णांकs permit this operation.
 */
पूर्णांक regulator_disable(काष्ठा regulator *regulator)
अणु
	काष्ठा regulator_dev *rdev = regulator->rdev;
	काष्ठा ww_acquire_ctx ww_ctx;
	पूर्णांक ret;

	regulator_lock_dependent(rdev, &ww_ctx);
	ret = _regulator_disable(regulator);
	regulator_unlock_dependent(rdev, &ww_ctx);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_disable);

/* locks held by regulator_क्रमce_disable() */
अटल पूर्णांक _regulator_क्रमce_disable(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret = 0;

	lockdep_निश्चित_held_once(&rdev->mutex.base);

	ret = _notअगरier_call_chain(rdev, REGULATOR_EVENT_FORCE_DISABLE |
			REGULATOR_EVENT_PRE_DISABLE, शून्य);
	अगर (ret & NOTIFY_STOP_MASK)
		वापस -EINVAL;

	ret = _regulator_करो_disable(rdev);
	अगर (ret < 0) अणु
		rdev_err(rdev, "failed to force disable: %pe\n", ERR_PTR(ret));
		_notअगरier_call_chain(rdev, REGULATOR_EVENT_FORCE_DISABLE |
				REGULATOR_EVENT_ABORT_DISABLE, शून्य);
		वापस ret;
	पूर्ण

	_notअगरier_call_chain(rdev, REGULATOR_EVENT_FORCE_DISABLE |
			REGULATOR_EVENT_DISABLE, शून्य);

	वापस 0;
पूर्ण

/**
 * regulator_क्रमce_disable - क्रमce disable regulator output
 * @regulator: regulator source
 *
 * Forcibly disable the regulator output voltage or current.
 * NOTE: this *will* disable the regulator output even अगर other consumer
 * devices have it enabled. This should be used क्रम situations when device
 * damage will likely occur अगर the regulator is not disabled (e.g. over temp).
 */
पूर्णांक regulator_क्रमce_disable(काष्ठा regulator *regulator)
अणु
	काष्ठा regulator_dev *rdev = regulator->rdev;
	काष्ठा ww_acquire_ctx ww_ctx;
	पूर्णांक ret;

	regulator_lock_dependent(rdev, &ww_ctx);

	ret = _regulator_क्रमce_disable(regulator->rdev);

	अगर (rdev->coupling_desc.n_coupled > 1)
		regulator_balance_voltage(rdev, PM_SUSPEND_ON);

	अगर (regulator->uA_load) अणु
		regulator->uA_load = 0;
		ret = drms_uA_update(rdev);
	पूर्ण

	अगर (rdev->use_count != 0 && rdev->supply)
		_regulator_disable(rdev->supply);

	regulator_unlock_dependent(rdev, &ww_ctx);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_क्रमce_disable);

अटल व्योम regulator_disable_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा regulator_dev *rdev = container_of(work, काष्ठा regulator_dev,
						  disable_work.work);
	काष्ठा ww_acquire_ctx ww_ctx;
	पूर्णांक count, i, ret;
	काष्ठा regulator *regulator;
	पूर्णांक total_count = 0;

	regulator_lock_dependent(rdev, &ww_ctx);

	/*
	 * Workqueue functions queue the new work instance जबतक the previous
	 * work instance is being processed. Cancel the queued work instance
	 * as the work instance under processing करोes the job of the queued
	 * work instance.
	 */
	cancel_delayed_work(&rdev->disable_work);

	list_क्रम_each_entry(regulator, &rdev->consumer_list, list) अणु
		count = regulator->deferred_disables;

		अगर (!count)
			जारी;

		total_count += count;
		regulator->deferred_disables = 0;

		क्रम (i = 0; i < count; i++) अणु
			ret = _regulator_disable(regulator);
			अगर (ret != 0)
				rdev_err(rdev, "Deferred disable failed: %pe\n",
					 ERR_PTR(ret));
		पूर्ण
	पूर्ण
	WARN_ON(!total_count);

	अगर (rdev->coupling_desc.n_coupled > 1)
		regulator_balance_voltage(rdev, PM_SUSPEND_ON);

	regulator_unlock_dependent(rdev, &ww_ctx);
पूर्ण

/**
 * regulator_disable_deferred - disable regulator output with delay
 * @regulator: regulator source
 * @ms: milliseconds until the regulator is disabled
 *
 * Execute regulator_disable() on the regulator after a delay.  This
 * is पूर्णांकended क्रम use with devices that require some समय to quiesce.
 *
 * NOTE: this will only disable the regulator output अगर no other consumer
 * devices have it enabled, the regulator device supports disabling and
 * machine स्थिरraपूर्णांकs permit this operation.
 */
पूर्णांक regulator_disable_deferred(काष्ठा regulator *regulator, पूर्णांक ms)
अणु
	काष्ठा regulator_dev *rdev = regulator->rdev;

	अगर (!ms)
		वापस regulator_disable(regulator);

	regulator_lock(rdev);
	regulator->deferred_disables++;
	mod_delayed_work(प्रणाली_घातer_efficient_wq, &rdev->disable_work,
			 msecs_to_jअगरfies(ms));
	regulator_unlock(rdev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_disable_deferred);

अटल पूर्णांक _regulator_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	/* A GPIO control always takes precedence */
	अगर (rdev->ena_pin)
		वापस rdev->ena_gpio_state;

	/* If we करोn't know then assume that the regulator is always on */
	अगर (!rdev->desc->ops->is_enabled)
		वापस 1;

	वापस rdev->desc->ops->is_enabled(rdev);
पूर्ण

अटल पूर्णांक _regulator_list_voltage(काष्ठा regulator_dev *rdev,
				   अचिन्हित selector, पूर्णांक lock)
अणु
	स्थिर काष्ठा regulator_ops *ops = rdev->desc->ops;
	पूर्णांक ret;

	अगर (rdev->desc->fixed_uV && rdev->desc->n_voltages == 1 && !selector)
		वापस rdev->desc->fixed_uV;

	अगर (ops->list_voltage) अणु
		अगर (selector >= rdev->desc->n_voltages)
			वापस -EINVAL;
		अगर (selector < rdev->desc->linear_min_sel)
			वापस 0;
		अगर (lock)
			regulator_lock(rdev);
		ret = ops->list_voltage(rdev, selector);
		अगर (lock)
			regulator_unlock(rdev);
	पूर्ण अन्यथा अगर (rdev->is_चयन && rdev->supply) अणु
		ret = _regulator_list_voltage(rdev->supply->rdev,
					      selector, lock);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (ret > 0) अणु
		अगर (ret < rdev->स्थिरraपूर्णांकs->min_uV)
			ret = 0;
		अन्यथा अगर (ret > rdev->स्थिरraपूर्णांकs->max_uV)
			ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * regulator_is_enabled - is the regulator output enabled
 * @regulator: regulator source
 *
 * Returns positive अगर the regulator driver backing the source/client
 * has requested that the device be enabled, zero अगर it hasn't, अन्यथा a
 * negative त्रुटि_सं code.
 *
 * Note that the device backing this regulator handle can have multiple
 * users, so it might be enabled even अगर regulator_enable() was never
 * called क्रम this particular source.
 */
पूर्णांक regulator_is_enabled(काष्ठा regulator *regulator)
अणु
	पूर्णांक ret;

	अगर (regulator->always_on)
		वापस 1;

	regulator_lock(regulator->rdev);
	ret = _regulator_is_enabled(regulator->rdev);
	regulator_unlock(regulator->rdev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_is_enabled);

/**
 * regulator_count_voltages - count regulator_list_voltage() selectors
 * @regulator: regulator source
 *
 * Returns number of selectors, or negative त्रुटि_सं.  Selectors are
 * numbered starting at zero, and typically correspond to bitfields
 * in hardware रेजिस्टरs.
 */
पूर्णांक regulator_count_voltages(काष्ठा regulator *regulator)
अणु
	काष्ठा regulator_dev	*rdev = regulator->rdev;

	अगर (rdev->desc->n_voltages)
		वापस rdev->desc->n_voltages;

	अगर (!rdev->is_चयन || !rdev->supply)
		वापस -EINVAL;

	वापस regulator_count_voltages(rdev->supply);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_count_voltages);

/**
 * regulator_list_voltage - क्रमागतerate supported voltages
 * @regulator: regulator source
 * @selector: identअगरy voltage to list
 * Context: can sleep
 *
 * Returns a voltage that can be passed to @regulator_set_voltage(),
 * zero अगर this selector code can't be used on this प्रणाली, or a
 * negative त्रुटि_सं.
 */
पूर्णांक regulator_list_voltage(काष्ठा regulator *regulator, अचिन्हित selector)
अणु
	वापस _regulator_list_voltage(regulator->rdev, selector, 1);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_list_voltage);

/**
 * regulator_get_regmap - get the regulator's रेजिस्टर map
 * @regulator: regulator source
 *
 * Returns the रेजिस्टर map क्रम the given regulator, or an ERR_PTR value
 * अगर the regulator करोesn't use regmap.
 */
काष्ठा regmap *regulator_get_regmap(काष्ठा regulator *regulator)
अणु
	काष्ठा regmap *map = regulator->rdev->regmap;

	वापस map ? map : ERR_PTR(-EOPNOTSUPP);
पूर्ण

/**
 * regulator_get_hardware_vsel_रेजिस्टर - get the HW voltage selector रेजिस्टर
 * @regulator: regulator source
 * @vsel_reg: voltage selector रेजिस्टर, output parameter
 * @vsel_mask: mask क्रम voltage selector bitfield, output parameter
 *
 * Returns the hardware रेजिस्टर offset and biपंचांगask used क्रम setting the
 * regulator voltage. This might be useful when configuring voltage-scaling
 * hardware or firmware that can make I2C requests behind the kernel's back,
 * क्रम example.
 *
 * On success, the output parameters @vsel_reg and @vsel_mask are filled in
 * and 0 is वापसed, otherwise a negative त्रुटि_सं is वापसed.
 */
पूर्णांक regulator_get_hardware_vsel_रेजिस्टर(काष्ठा regulator *regulator,
					 अचिन्हित *vsel_reg,
					 अचिन्हित *vsel_mask)
अणु
	काष्ठा regulator_dev *rdev = regulator->rdev;
	स्थिर काष्ठा regulator_ops *ops = rdev->desc->ops;

	अगर (ops->set_voltage_sel != regulator_set_voltage_sel_regmap)
		वापस -EOPNOTSUPP;

	*vsel_reg = rdev->desc->vsel_reg;
	*vsel_mask = rdev->desc->vsel_mask;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_get_hardware_vsel_रेजिस्टर);

/**
 * regulator_list_hardware_vsel - get the HW-specअगरic रेजिस्टर value क्रम a selector
 * @regulator: regulator source
 * @selector: identअगरy voltage to list
 *
 * Converts the selector to a hardware-specअगरic voltage selector that can be
 * directly written to the regulator रेजिस्टरs. The address of the voltage
 * रेजिस्टर can be determined by calling @regulator_get_hardware_vsel_रेजिस्टर.
 *
 * On error a negative त्रुटि_सं is वापसed.
 */
पूर्णांक regulator_list_hardware_vsel(काष्ठा regulator *regulator,
				 अचिन्हित selector)
अणु
	काष्ठा regulator_dev *rdev = regulator->rdev;
	स्थिर काष्ठा regulator_ops *ops = rdev->desc->ops;

	अगर (selector >= rdev->desc->n_voltages)
		वापस -EINVAL;
	अगर (selector < rdev->desc->linear_min_sel)
		वापस 0;
	अगर (ops->set_voltage_sel != regulator_set_voltage_sel_regmap)
		वापस -EOPNOTSUPP;

	वापस selector;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_list_hardware_vsel);

/**
 * regulator_get_linear_step - वापस the voltage step size between VSEL values
 * @regulator: regulator source
 *
 * Returns the voltage step size between VSEL values क्रम linear
 * regulators, or वापस 0 अगर the regulator isn't a linear regulator.
 */
अचिन्हित पूर्णांक regulator_get_linear_step(काष्ठा regulator *regulator)
अणु
	काष्ठा regulator_dev *rdev = regulator->rdev;

	वापस rdev->desc->uV_step;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_get_linear_step);

/**
 * regulator_is_supported_voltage - check अगर a voltage range can be supported
 *
 * @regulator: Regulator to check.
 * @min_uV: Minimum required voltage in uV.
 * @max_uV: Maximum required voltage in uV.
 *
 * Returns a boolean.
 */
पूर्णांक regulator_is_supported_voltage(काष्ठा regulator *regulator,
				   पूर्णांक min_uV, पूर्णांक max_uV)
अणु
	काष्ठा regulator_dev *rdev = regulator->rdev;
	पूर्णांक i, voltages, ret;

	/* If we can't change voltage check the current voltage */
	अगर (!regulator_ops_is_valid(rdev, REGULATOR_CHANGE_VOLTAGE)) अणु
		ret = regulator_get_voltage(regulator);
		अगर (ret >= 0)
			वापस min_uV <= ret && ret <= max_uV;
		अन्यथा
			वापस ret;
	पूर्ण

	/* Any voltage within स्थिरrains range is fine? */
	अगर (rdev->desc->continuous_voltage_range)
		वापस min_uV >= rdev->स्थिरraपूर्णांकs->min_uV &&
				max_uV <= rdev->स्थिरraपूर्णांकs->max_uV;

	ret = regulator_count_voltages(regulator);
	अगर (ret < 0)
		वापस 0;
	voltages = ret;

	क्रम (i = 0; i < voltages; i++) अणु
		ret = regulator_list_voltage(regulator, i);

		अगर (ret >= min_uV && ret <= max_uV)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_is_supported_voltage);

अटल पूर्णांक regulator_map_voltage(काष्ठा regulator_dev *rdev, पूर्णांक min_uV,
				 पूर्णांक max_uV)
अणु
	स्थिर काष्ठा regulator_desc *desc = rdev->desc;

	अगर (desc->ops->map_voltage)
		वापस desc->ops->map_voltage(rdev, min_uV, max_uV);

	अगर (desc->ops->list_voltage == regulator_list_voltage_linear)
		वापस regulator_map_voltage_linear(rdev, min_uV, max_uV);

	अगर (desc->ops->list_voltage == regulator_list_voltage_linear_range)
		वापस regulator_map_voltage_linear_range(rdev, min_uV, max_uV);

	अगर (desc->ops->list_voltage ==
		regulator_list_voltage_pickable_linear_range)
		वापस regulator_map_voltage_pickable_linear_range(rdev,
							min_uV, max_uV);

	वापस regulator_map_voltage_iterate(rdev, min_uV, max_uV);
पूर्ण

अटल पूर्णांक _regulator_call_set_voltage(काष्ठा regulator_dev *rdev,
				       पूर्णांक min_uV, पूर्णांक max_uV,
				       अचिन्हित *selector)
अणु
	काष्ठा pre_voltage_change_data data;
	पूर्णांक ret;

	data.old_uV = regulator_get_voltage_rdev(rdev);
	data.min_uV = min_uV;
	data.max_uV = max_uV;
	ret = _notअगरier_call_chain(rdev, REGULATOR_EVENT_PRE_VOLTAGE_CHANGE,
				   &data);
	अगर (ret & NOTIFY_STOP_MASK)
		वापस -EINVAL;

	ret = rdev->desc->ops->set_voltage(rdev, min_uV, max_uV, selector);
	अगर (ret >= 0)
		वापस ret;

	_notअगरier_call_chain(rdev, REGULATOR_EVENT_ABORT_VOLTAGE_CHANGE,
			     (व्योम *)data.old_uV);

	वापस ret;
पूर्ण

अटल पूर्णांक _regulator_call_set_voltage_sel(काष्ठा regulator_dev *rdev,
					   पूर्णांक uV, अचिन्हित selector)
अणु
	काष्ठा pre_voltage_change_data data;
	पूर्णांक ret;

	data.old_uV = regulator_get_voltage_rdev(rdev);
	data.min_uV = uV;
	data.max_uV = uV;
	ret = _notअगरier_call_chain(rdev, REGULATOR_EVENT_PRE_VOLTAGE_CHANGE,
				   &data);
	अगर (ret & NOTIFY_STOP_MASK)
		वापस -EINVAL;

	ret = rdev->desc->ops->set_voltage_sel(rdev, selector);
	अगर (ret >= 0)
		वापस ret;

	_notअगरier_call_chain(rdev, REGULATOR_EVENT_ABORT_VOLTAGE_CHANGE,
			     (व्योम *)data.old_uV);

	वापस ret;
पूर्ण

अटल पूर्णांक _regulator_set_voltage_sel_step(काष्ठा regulator_dev *rdev,
					   पूर्णांक uV, पूर्णांक new_selector)
अणु
	स्थिर काष्ठा regulator_ops *ops = rdev->desc->ops;
	पूर्णांक dअगरf, old_sel, curr_sel, ret;

	/* Stepping is only needed अगर the regulator is enabled. */
	अगर (!_regulator_is_enabled(rdev))
		जाओ final_set;

	अगर (!ops->get_voltage_sel)
		वापस -EINVAL;

	old_sel = ops->get_voltage_sel(rdev);
	अगर (old_sel < 0)
		वापस old_sel;

	dअगरf = new_selector - old_sel;
	अगर (dअगरf == 0)
		वापस 0; /* No change needed. */

	अगर (dअगरf > 0) अणु
		/* Stepping up. */
		क्रम (curr_sel = old_sel + rdev->desc->vsel_step;
		     curr_sel < new_selector;
		     curr_sel += rdev->desc->vsel_step) अणु
			/*
			 * Call the callback directly instead of using
			 * _regulator_call_set_voltage_sel() as we करोn't
			 * want to notअगरy anyone yet. Same in the branch
			 * below.
			 */
			ret = ops->set_voltage_sel(rdev, curr_sel);
			अगर (ret)
				जाओ try_revert;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Stepping करोwn. */
		क्रम (curr_sel = old_sel - rdev->desc->vsel_step;
		     curr_sel > new_selector;
		     curr_sel -= rdev->desc->vsel_step) अणु
			ret = ops->set_voltage_sel(rdev, curr_sel);
			अगर (ret)
				जाओ try_revert;
		पूर्ण
	पूर्ण

final_set:
	/* The final selector will trigger the notअगरiers. */
	वापस _regulator_call_set_voltage_sel(rdev, uV, new_selector);

try_revert:
	/*
	 * At least try to वापस to the previous voltage अगर setting a new
	 * one failed.
	 */
	(व्योम)ops->set_voltage_sel(rdev, old_sel);
	वापस ret;
पूर्ण

अटल पूर्णांक _regulator_set_voltage_समय(काष्ठा regulator_dev *rdev,
				       पूर्णांक old_uV, पूर्णांक new_uV)
अणु
	अचिन्हित पूर्णांक ramp_delay = 0;

	अगर (rdev->स्थिरraपूर्णांकs->ramp_delay)
		ramp_delay = rdev->स्थिरraपूर्णांकs->ramp_delay;
	अन्यथा अगर (rdev->desc->ramp_delay)
		ramp_delay = rdev->desc->ramp_delay;
	अन्यथा अगर (rdev->स्थिरraपूर्णांकs->settling_समय)
		वापस rdev->स्थिरraपूर्णांकs->settling_समय;
	अन्यथा अगर (rdev->स्थिरraपूर्णांकs->settling_समय_up &&
		 (new_uV > old_uV))
		वापस rdev->स्थिरraपूर्णांकs->settling_समय_up;
	अन्यथा अगर (rdev->स्थिरraपूर्णांकs->settling_समय_करोwn &&
		 (new_uV < old_uV))
		वापस rdev->स्थिरraपूर्णांकs->settling_समय_करोwn;

	अगर (ramp_delay == 0) अणु
		rdev_dbg(rdev, "ramp_delay not set\n");
		वापस 0;
	पूर्ण

	वापस DIV_ROUND_UP(असल(new_uV - old_uV), ramp_delay);
पूर्ण

अटल पूर्णांक _regulator_करो_set_voltage(काष्ठा regulator_dev *rdev,
				     पूर्णांक min_uV, पूर्णांक max_uV)
अणु
	पूर्णांक ret;
	पूर्णांक delay = 0;
	पूर्णांक best_val = 0;
	अचिन्हित पूर्णांक selector;
	पूर्णांक old_selector = -1;
	स्थिर काष्ठा regulator_ops *ops = rdev->desc->ops;
	पूर्णांक old_uV = regulator_get_voltage_rdev(rdev);

	trace_regulator_set_voltage(rdev_get_name(rdev), min_uV, max_uV);

	min_uV += rdev->स्थिरraपूर्णांकs->uV_offset;
	max_uV += rdev->स्थिरraपूर्णांकs->uV_offset;

	/*
	 * If we can't obtain the old selector there is not enough
	 * info to call set_voltage_समय_sel().
	 */
	अगर (_regulator_is_enabled(rdev) &&
	    ops->set_voltage_समय_sel && ops->get_voltage_sel) अणु
		old_selector = ops->get_voltage_sel(rdev);
		अगर (old_selector < 0)
			वापस old_selector;
	पूर्ण

	अगर (ops->set_voltage) अणु
		ret = _regulator_call_set_voltage(rdev, min_uV, max_uV,
						  &selector);

		अगर (ret >= 0) अणु
			अगर (ops->list_voltage)
				best_val = ops->list_voltage(rdev,
							     selector);
			अन्यथा
				best_val = regulator_get_voltage_rdev(rdev);
		पूर्ण

	पूर्ण अन्यथा अगर (ops->set_voltage_sel) अणु
		ret = regulator_map_voltage(rdev, min_uV, max_uV);
		अगर (ret >= 0) अणु
			best_val = ops->list_voltage(rdev, ret);
			अगर (min_uV <= best_val && max_uV >= best_val) अणु
				selector = ret;
				अगर (old_selector == selector)
					ret = 0;
				अन्यथा अगर (rdev->desc->vsel_step)
					ret = _regulator_set_voltage_sel_step(
						rdev, best_val, selector);
				अन्यथा
					ret = _regulator_call_set_voltage_sel(
						rdev, best_val, selector);
			पूर्ण अन्यथा अणु
				ret = -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	अगर (ret)
		जाओ out;

	अगर (ops->set_voltage_समय_sel) अणु
		/*
		 * Call set_voltage_समय_sel अगर successfully obtained
		 * old_selector
		 */
		अगर (old_selector >= 0 && old_selector != selector)
			delay = ops->set_voltage_समय_sel(rdev, old_selector,
							  selector);
	पूर्ण अन्यथा अणु
		अगर (old_uV != best_val) अणु
			अगर (ops->set_voltage_समय)
				delay = ops->set_voltage_समय(rdev, old_uV,
							      best_val);
			अन्यथा
				delay = _regulator_set_voltage_समय(rdev,
								    old_uV,
								    best_val);
		पूर्ण
	पूर्ण

	अगर (delay < 0) अणु
		rdev_warn(rdev, "failed to get delay: %pe\n", ERR_PTR(delay));
		delay = 0;
	पूर्ण

	/* Insert any necessary delays */
	अगर (delay >= 1000) अणु
		mdelay(delay / 1000);
		udelay(delay % 1000);
	पूर्ण अन्यथा अगर (delay) अणु
		udelay(delay);
	पूर्ण

	अगर (best_val >= 0) अणु
		अचिन्हित दीर्घ data = best_val;

		_notअगरier_call_chain(rdev, REGULATOR_EVENT_VOLTAGE_CHANGE,
				     (व्योम *)data);
	पूर्ण

out:
	trace_regulator_set_voltage_complete(rdev_get_name(rdev), best_val);

	वापस ret;
पूर्ण

अटल पूर्णांक _regulator_करो_set_suspend_voltage(काष्ठा regulator_dev *rdev,
				  पूर्णांक min_uV, पूर्णांक max_uV, suspend_state_t state)
अणु
	काष्ठा regulator_state *rstate;
	पूर्णांक uV, sel;

	rstate = regulator_get_suspend_state(rdev, state);
	अगर (rstate == शून्य)
		वापस -EINVAL;

	अगर (min_uV < rstate->min_uV)
		min_uV = rstate->min_uV;
	अगर (max_uV > rstate->max_uV)
		max_uV = rstate->max_uV;

	sel = regulator_map_voltage(rdev, min_uV, max_uV);
	अगर (sel < 0)
		वापस sel;

	uV = rdev->desc->ops->list_voltage(rdev, sel);
	अगर (uV >= min_uV && uV <= max_uV)
		rstate->uV = uV;

	वापस 0;
पूर्ण

अटल पूर्णांक regulator_set_voltage_unlocked(काष्ठा regulator *regulator,
					  पूर्णांक min_uV, पूर्णांक max_uV,
					  suspend_state_t state)
अणु
	काष्ठा regulator_dev *rdev = regulator->rdev;
	काष्ठा regulator_voltage *voltage = &regulator->voltage[state];
	पूर्णांक ret = 0;
	पूर्णांक old_min_uV, old_max_uV;
	पूर्णांक current_uV;

	/* If we're setting the same range as last समय the change
	 * should be a noop (some cpufreq implementations use the same
	 * voltage क्रम multiple frequencies, क्रम example).
	 */
	अगर (voltage->min_uV == min_uV && voltage->max_uV == max_uV)
		जाओ out;

	/* If we're trying to set a range that overlaps the current voltage,
	 * वापस successfully even though the regulator करोes not support
	 * changing the voltage.
	 */
	अगर (!regulator_ops_is_valid(rdev, REGULATOR_CHANGE_VOLTAGE)) अणु
		current_uV = regulator_get_voltage_rdev(rdev);
		अगर (min_uV <= current_uV && current_uV <= max_uV) अणु
			voltage->min_uV = min_uV;
			voltage->max_uV = max_uV;
			जाओ out;
		पूर्ण
	पूर्ण

	/* sanity check */
	अगर (!rdev->desc->ops->set_voltage &&
	    !rdev->desc->ops->set_voltage_sel) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* स्थिरraपूर्णांकs check */
	ret = regulator_check_voltage(rdev, &min_uV, &max_uV);
	अगर (ret < 0)
		जाओ out;

	/* restore original values in हाल of error */
	old_min_uV = voltage->min_uV;
	old_max_uV = voltage->max_uV;
	voltage->min_uV = min_uV;
	voltage->max_uV = max_uV;

	/* क्रम not coupled regulators this will just set the voltage */
	ret = regulator_balance_voltage(rdev, state);
	अगर (ret < 0) अणु
		voltage->min_uV = old_min_uV;
		voltage->max_uV = old_max_uV;
	पूर्ण

out:
	वापस ret;
पूर्ण

पूर्णांक regulator_set_voltage_rdev(काष्ठा regulator_dev *rdev, पूर्णांक min_uV,
			       पूर्णांक max_uV, suspend_state_t state)
अणु
	पूर्णांक best_supply_uV = 0;
	पूर्णांक supply_change_uV = 0;
	पूर्णांक ret;

	अगर (rdev->supply &&
	    regulator_ops_is_valid(rdev->supply->rdev,
				   REGULATOR_CHANGE_VOLTAGE) &&
	    (rdev->desc->min_dropout_uV || !(rdev->desc->ops->get_voltage ||
					   rdev->desc->ops->get_voltage_sel))) अणु
		पूर्णांक current_supply_uV;
		पूर्णांक selector;

		selector = regulator_map_voltage(rdev, min_uV, max_uV);
		अगर (selector < 0) अणु
			ret = selector;
			जाओ out;
		पूर्ण

		best_supply_uV = _regulator_list_voltage(rdev, selector, 0);
		अगर (best_supply_uV < 0) अणु
			ret = best_supply_uV;
			जाओ out;
		पूर्ण

		best_supply_uV += rdev->desc->min_dropout_uV;

		current_supply_uV = regulator_get_voltage_rdev(rdev->supply->rdev);
		अगर (current_supply_uV < 0) अणु
			ret = current_supply_uV;
			जाओ out;
		पूर्ण

		supply_change_uV = best_supply_uV - current_supply_uV;
	पूर्ण

	अगर (supply_change_uV > 0) अणु
		ret = regulator_set_voltage_unlocked(rdev->supply,
				best_supply_uV, पूर्णांक_उच्च, state);
		अगर (ret) अणु
			dev_err(&rdev->dev, "Failed to increase supply voltage: %pe\n",
				ERR_PTR(ret));
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (state == PM_SUSPEND_ON)
		ret = _regulator_करो_set_voltage(rdev, min_uV, max_uV);
	अन्यथा
		ret = _regulator_करो_set_suspend_voltage(rdev, min_uV,
							max_uV, state);
	अगर (ret < 0)
		जाओ out;

	अगर (supply_change_uV < 0) अणु
		ret = regulator_set_voltage_unlocked(rdev->supply,
				best_supply_uV, पूर्णांक_उच्च, state);
		अगर (ret)
			dev_warn(&rdev->dev, "Failed to decrease supply voltage: %pe\n",
				 ERR_PTR(ret));
		/* No need to fail here */
		ret = 0;
	पूर्ण

out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_set_voltage_rdev);

अटल पूर्णांक regulator_limit_voltage_step(काष्ठा regulator_dev *rdev,
					पूर्णांक *current_uV, पूर्णांक *min_uV)
अणु
	काष्ठा regulation_स्थिरraपूर्णांकs *स्थिरraपूर्णांकs = rdev->स्थिरraपूर्णांकs;

	/* Limit voltage change only अगर necessary */
	अगर (!स्थिरraपूर्णांकs->max_uV_step || !_regulator_is_enabled(rdev))
		वापस 1;

	अगर (*current_uV < 0) अणु
		*current_uV = regulator_get_voltage_rdev(rdev);

		अगर (*current_uV < 0)
			वापस *current_uV;
	पूर्ण

	अगर (असल(*current_uV - *min_uV) <= स्थिरraपूर्णांकs->max_uV_step)
		वापस 1;

	/* Clamp target voltage within the given step */
	अगर (*current_uV < *min_uV)
		*min_uV = min(*current_uV + स्थिरraपूर्णांकs->max_uV_step,
			      *min_uV);
	अन्यथा
		*min_uV = max(*current_uV - स्थिरraपूर्णांकs->max_uV_step,
			      *min_uV);

	वापस 0;
पूर्ण

अटल पूर्णांक regulator_get_optimal_voltage(काष्ठा regulator_dev *rdev,
					 पूर्णांक *current_uV,
					 पूर्णांक *min_uV, पूर्णांक *max_uV,
					 suspend_state_t state,
					 पूर्णांक n_coupled)
अणु
	काष्ठा coupling_desc *c_desc = &rdev->coupling_desc;
	काष्ठा regulator_dev **c_rdevs = c_desc->coupled_rdevs;
	काष्ठा regulation_स्थिरraपूर्णांकs *स्थिरraपूर्णांकs = rdev->स्थिरraपूर्णांकs;
	पूर्णांक desired_min_uV = 0, desired_max_uV = पूर्णांक_उच्च;
	पूर्णांक max_current_uV = 0, min_current_uV = पूर्णांक_उच्च;
	पूर्णांक highest_min_uV = 0, target_uV, possible_uV;
	पूर्णांक i, ret, max_spपढ़ो;
	bool करोne;

	*current_uV = -1;

	/*
	 * If there are no coupled regulators, simply set the voltage
	 * demanded by consumers.
	 */
	अगर (n_coupled == 1) अणु
		/*
		 * If consumers करोn't provide any demands, set voltage
		 * to min_uV
		 */
		desired_min_uV = स्थिरraपूर्णांकs->min_uV;
		desired_max_uV = स्थिरraपूर्णांकs->max_uV;

		ret = regulator_check_consumers(rdev,
						&desired_min_uV,
						&desired_max_uV, state);
		अगर (ret < 0)
			वापस ret;

		possible_uV = desired_min_uV;
		करोne = true;

		जाओ finish;
	पूर्ण

	/* Find highest min desired voltage */
	क्रम (i = 0; i < n_coupled; i++) अणु
		पूर्णांक पंचांगp_min = 0;
		पूर्णांक पंचांगp_max = पूर्णांक_उच्च;

		lockdep_निश्चित_held_once(&c_rdevs[i]->mutex.base);

		ret = regulator_check_consumers(c_rdevs[i],
						&पंचांगp_min,
						&पंचांगp_max, state);
		अगर (ret < 0)
			वापस ret;

		ret = regulator_check_voltage(c_rdevs[i], &पंचांगp_min, &पंचांगp_max);
		अगर (ret < 0)
			वापस ret;

		highest_min_uV = max(highest_min_uV, पंचांगp_min);

		अगर (i == 0) अणु
			desired_min_uV = पंचांगp_min;
			desired_max_uV = पंचांगp_max;
		पूर्ण
	पूर्ण

	max_spपढ़ो = स्थिरraपूर्णांकs->max_spपढ़ो[0];

	/*
	 * Let target_uV be equal to the desired one अगर possible.
	 * If not, set it to minimum voltage, allowed by other coupled
	 * regulators.
	 */
	target_uV = max(desired_min_uV, highest_min_uV - max_spपढ़ो);

	/*
	 * Find min and max voltages, which currently aren't violating
	 * max_spपढ़ो.
	 */
	क्रम (i = 1; i < n_coupled; i++) अणु
		पूर्णांक पंचांगp_act;

		अगर (!_regulator_is_enabled(c_rdevs[i]))
			जारी;

		पंचांगp_act = regulator_get_voltage_rdev(c_rdevs[i]);
		अगर (पंचांगp_act < 0)
			वापस पंचांगp_act;

		min_current_uV = min(पंचांगp_act, min_current_uV);
		max_current_uV = max(पंचांगp_act, max_current_uV);
	पूर्ण

	/* There aren't any other regulators enabled */
	अगर (max_current_uV == 0) अणु
		possible_uV = target_uV;
	पूर्ण अन्यथा अणु
		/*
		 * Correct target voltage, so as it currently isn't
		 * violating max_spपढ़ो
		 */
		possible_uV = max(target_uV, max_current_uV - max_spपढ़ो);
		possible_uV = min(possible_uV, min_current_uV + max_spपढ़ो);
	पूर्ण

	अगर (possible_uV > desired_max_uV)
		वापस -EINVAL;

	करोne = (possible_uV == target_uV);
	desired_min_uV = possible_uV;

finish:
	/* Apply max_uV_step स्थिरraपूर्णांक अगर necessary */
	अगर (state == PM_SUSPEND_ON) अणु
		ret = regulator_limit_voltage_step(rdev, current_uV,
						   &desired_min_uV);
		अगर (ret < 0)
			वापस ret;

		अगर (ret == 0)
			करोne = false;
	पूर्ण

	/* Set current_uV अगर wasn't करोne earlier in the code and अगर necessary */
	अगर (n_coupled > 1 && *current_uV == -1) अणु

		अगर (_regulator_is_enabled(rdev)) अणु
			ret = regulator_get_voltage_rdev(rdev);
			अगर (ret < 0)
				वापस ret;

			*current_uV = ret;
		पूर्ण अन्यथा अणु
			*current_uV = desired_min_uV;
		पूर्ण
	पूर्ण

	*min_uV = desired_min_uV;
	*max_uV = desired_max_uV;

	वापस करोne;
पूर्ण

पूर्णांक regulator_करो_balance_voltage(काष्ठा regulator_dev *rdev,
				 suspend_state_t state, bool skip_coupled)
अणु
	काष्ठा regulator_dev **c_rdevs;
	काष्ठा regulator_dev *best_rdev;
	काष्ठा coupling_desc *c_desc = &rdev->coupling_desc;
	पूर्णांक i, ret, n_coupled, best_min_uV, best_max_uV, best_c_rdev;
	अचिन्हित पूर्णांक delta, best_delta;
	अचिन्हित दीर्घ c_rdev_करोne = 0;
	bool best_c_rdev_करोne;

	c_rdevs = c_desc->coupled_rdevs;
	n_coupled = skip_coupled ? 1 : c_desc->n_coupled;

	/*
	 * Find the best possible voltage change on each loop. Leave the loop
	 * अगर there isn't any possible change.
	 */
	करो अणु
		best_c_rdev_करोne = false;
		best_delta = 0;
		best_min_uV = 0;
		best_max_uV = 0;
		best_c_rdev = 0;
		best_rdev = शून्य;

		/*
		 * Find highest dअगरference between optimal voltage
		 * and current voltage.
		 */
		क्रम (i = 0; i < n_coupled; i++) अणु
			/*
			 * optimal_uV is the best voltage that can be set क्रम
			 * i-th regulator at the moment without violating
			 * max_spपढ़ो स्थिरraपूर्णांक in order to balance
			 * the coupled voltages.
			 */
			पूर्णांक optimal_uV = 0, optimal_max_uV = 0, current_uV = 0;

			अगर (test_bit(i, &c_rdev_करोne))
				जारी;

			ret = regulator_get_optimal_voltage(c_rdevs[i],
							    &current_uV,
							    &optimal_uV,
							    &optimal_max_uV,
							    state, n_coupled);
			अगर (ret < 0)
				जाओ out;

			delta = असल(optimal_uV - current_uV);

			अगर (delta && best_delta <= delta) अणु
				best_c_rdev_करोne = ret;
				best_delta = delta;
				best_rdev = c_rdevs[i];
				best_min_uV = optimal_uV;
				best_max_uV = optimal_max_uV;
				best_c_rdev = i;
			पूर्ण
		पूर्ण

		/* Nothing to change, वापस successfully */
		अगर (!best_rdev) अणु
			ret = 0;
			जाओ out;
		पूर्ण

		ret = regulator_set_voltage_rdev(best_rdev, best_min_uV,
						 best_max_uV, state);

		अगर (ret < 0)
			जाओ out;

		अगर (best_c_rdev_करोne)
			set_bit(best_c_rdev, &c_rdev_करोne);

	पूर्ण जबतक (n_coupled > 1);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक regulator_balance_voltage(काष्ठा regulator_dev *rdev,
				     suspend_state_t state)
अणु
	काष्ठा coupling_desc *c_desc = &rdev->coupling_desc;
	काष्ठा regulator_coupler *coupler = c_desc->coupler;
	bool skip_coupled = false;

	/*
	 * If प्रणाली is in a state other than PM_SUSPEND_ON, करोn't check
	 * other coupled regulators.
	 */
	अगर (state != PM_SUSPEND_ON)
		skip_coupled = true;

	अगर (c_desc->n_resolved < c_desc->n_coupled) अणु
		rdev_err(rdev, "Not all coupled regulators registered\n");
		वापस -EPERM;
	पूर्ण

	/* Invoke custom balancer क्रम customized couplers */
	अगर (coupler && coupler->balance_voltage)
		वापस coupler->balance_voltage(coupler, rdev, state);

	वापस regulator_करो_balance_voltage(rdev, state, skip_coupled);
पूर्ण

/**
 * regulator_set_voltage - set regulator output voltage
 * @regulator: regulator source
 * @min_uV: Minimum required voltage in uV
 * @max_uV: Maximum acceptable voltage in uV
 *
 * Sets a voltage regulator to the desired output voltage. This can be set
 * during any regulator state. IOW, regulator can be disabled or enabled.
 *
 * If the regulator is enabled then the voltage will change to the new value
 * immediately otherwise अगर the regulator is disabled the regulator will
 * output at the new voltage when enabled.
 *
 * NOTE: If the regulator is shared between several devices then the lowest
 * request voltage that meets the प्रणाली स्थिरraपूर्णांकs will be used.
 * Regulator प्रणाली स्थिरraपूर्णांकs must be set क्रम this regulator beक्रमe
 * calling this function otherwise this call will fail.
 */
पूर्णांक regulator_set_voltage(काष्ठा regulator *regulator, पूर्णांक min_uV, पूर्णांक max_uV)
अणु
	काष्ठा ww_acquire_ctx ww_ctx;
	पूर्णांक ret;

	regulator_lock_dependent(regulator->rdev, &ww_ctx);

	ret = regulator_set_voltage_unlocked(regulator, min_uV, max_uV,
					     PM_SUSPEND_ON);

	regulator_unlock_dependent(regulator->rdev, &ww_ctx);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_set_voltage);

अटल अंतरभूत पूर्णांक regulator_suspend_toggle(काष्ठा regulator_dev *rdev,
					   suspend_state_t state, bool en)
अणु
	काष्ठा regulator_state *rstate;

	rstate = regulator_get_suspend_state(rdev, state);
	अगर (rstate == शून्य)
		वापस -EINVAL;

	अगर (!rstate->changeable)
		वापस -EPERM;

	rstate->enabled = (en) ? ENABLE_IN_SUSPEND : DISABLE_IN_SUSPEND;

	वापस 0;
पूर्ण

पूर्णांक regulator_suspend_enable(काष्ठा regulator_dev *rdev,
				    suspend_state_t state)
अणु
	वापस regulator_suspend_toggle(rdev, state, true);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_suspend_enable);

पूर्णांक regulator_suspend_disable(काष्ठा regulator_dev *rdev,
				     suspend_state_t state)
अणु
	काष्ठा regulator *regulator;
	काष्ठा regulator_voltage *voltage;

	/*
	 * अगर any consumer wants this regulator device keeping on in
	 * suspend states, करोn't set it as disabled.
	 */
	list_क्रम_each_entry(regulator, &rdev->consumer_list, list) अणु
		voltage = &regulator->voltage[state];
		अगर (voltage->min_uV || voltage->max_uV)
			वापस 0;
	पूर्ण

	वापस regulator_suspend_toggle(rdev, state, false);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_suspend_disable);

अटल पूर्णांक _regulator_set_suspend_voltage(काष्ठा regulator *regulator,
					  पूर्णांक min_uV, पूर्णांक max_uV,
					  suspend_state_t state)
अणु
	काष्ठा regulator_dev *rdev = regulator->rdev;
	काष्ठा regulator_state *rstate;

	rstate = regulator_get_suspend_state(rdev, state);
	अगर (rstate == शून्य)
		वापस -EINVAL;

	अगर (rstate->min_uV == rstate->max_uV) अणु
		rdev_err(rdev, "The suspend voltage can't be changed!\n");
		वापस -EPERM;
	पूर्ण

	वापस regulator_set_voltage_unlocked(regulator, min_uV, max_uV, state);
पूर्ण

पूर्णांक regulator_set_suspend_voltage(काष्ठा regulator *regulator, पूर्णांक min_uV,
				  पूर्णांक max_uV, suspend_state_t state)
अणु
	काष्ठा ww_acquire_ctx ww_ctx;
	पूर्णांक ret;

	/* PM_SUSPEND_ON is handled by regulator_set_voltage() */
	अगर (regulator_check_states(state) || state == PM_SUSPEND_ON)
		वापस -EINVAL;

	regulator_lock_dependent(regulator->rdev, &ww_ctx);

	ret = _regulator_set_suspend_voltage(regulator, min_uV,
					     max_uV, state);

	regulator_unlock_dependent(regulator->rdev, &ww_ctx);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_set_suspend_voltage);

/**
 * regulator_set_voltage_समय - get उठाओ/fall समय
 * @regulator: regulator source
 * @old_uV: starting voltage in microvolts
 * @new_uV: target voltage in microvolts
 *
 * Provided with the starting and ending voltage, this function attempts to
 * calculate the समय in microseconds required to rise or fall to this new
 * voltage.
 */
पूर्णांक regulator_set_voltage_समय(काष्ठा regulator *regulator,
			       पूर्णांक old_uV, पूर्णांक new_uV)
अणु
	काष्ठा regulator_dev *rdev = regulator->rdev;
	स्थिर काष्ठा regulator_ops *ops = rdev->desc->ops;
	पूर्णांक old_sel = -1;
	पूर्णांक new_sel = -1;
	पूर्णांक voltage;
	पूर्णांक i;

	अगर (ops->set_voltage_समय)
		वापस ops->set_voltage_समय(rdev, old_uV, new_uV);
	अन्यथा अगर (!ops->set_voltage_समय_sel)
		वापस _regulator_set_voltage_समय(rdev, old_uV, new_uV);

	/* Currently requires operations to करो this */
	अगर (!ops->list_voltage || !rdev->desc->n_voltages)
		वापस -EINVAL;

	क्रम (i = 0; i < rdev->desc->n_voltages; i++) अणु
		/* We only look क्रम exact voltage matches here */
		अगर (i < rdev->desc->linear_min_sel)
			जारी;

		अगर (old_sel >= 0 && new_sel >= 0)
			अवरोध;

		voltage = regulator_list_voltage(regulator, i);
		अगर (voltage < 0)
			वापस -EINVAL;
		अगर (voltage == 0)
			जारी;
		अगर (voltage == old_uV)
			old_sel = i;
		अगर (voltage == new_uV)
			new_sel = i;
	पूर्ण

	अगर (old_sel < 0 || new_sel < 0)
		वापस -EINVAL;

	वापस ops->set_voltage_समय_sel(rdev, old_sel, new_sel);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_set_voltage_समय);

/**
 * regulator_set_voltage_समय_sel - get उठाओ/fall समय
 * @rdev: regulator source device
 * @old_selector: selector क्रम starting voltage
 * @new_selector: selector क्रम target voltage
 *
 * Provided with the starting and target voltage selectors, this function
 * वापसs समय in microseconds required to rise or fall to this new voltage
 *
 * Drivers providing ramp_delay in regulation_स्थिरraपूर्णांकs can use this as their
 * set_voltage_समय_sel() operation.
 */
पूर्णांक regulator_set_voltage_समय_sel(काष्ठा regulator_dev *rdev,
				   अचिन्हित पूर्णांक old_selector,
				   अचिन्हित पूर्णांक new_selector)
अणु
	पूर्णांक old_volt, new_volt;

	/* sanity check */
	अगर (!rdev->desc->ops->list_voltage)
		वापस -EINVAL;

	old_volt = rdev->desc->ops->list_voltage(rdev, old_selector);
	new_volt = rdev->desc->ops->list_voltage(rdev, new_selector);

	अगर (rdev->desc->ops->set_voltage_समय)
		वापस rdev->desc->ops->set_voltage_समय(rdev, old_volt,
							 new_volt);
	अन्यथा
		वापस _regulator_set_voltage_समय(rdev, old_volt, new_volt);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_set_voltage_समय_sel);

/**
 * regulator_sync_voltage - re-apply last regulator output voltage
 * @regulator: regulator source
 *
 * Re-apply the last configured voltage.  This is पूर्णांकended to be used
 * where some बाह्यal control source the consumer is cooperating with
 * has caused the configured voltage to change.
 */
पूर्णांक regulator_sync_voltage(काष्ठा regulator *regulator)
अणु
	काष्ठा regulator_dev *rdev = regulator->rdev;
	काष्ठा regulator_voltage *voltage = &regulator->voltage[PM_SUSPEND_ON];
	पूर्णांक ret, min_uV, max_uV;

	regulator_lock(rdev);

	अगर (!rdev->desc->ops->set_voltage &&
	    !rdev->desc->ops->set_voltage_sel) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* This is only going to work अगर we've had a voltage configured. */
	अगर (!voltage->min_uV && !voltage->max_uV) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	min_uV = voltage->min_uV;
	max_uV = voltage->max_uV;

	/* This should be a paranoia check... */
	ret = regulator_check_voltage(rdev, &min_uV, &max_uV);
	अगर (ret < 0)
		जाओ out;

	ret = regulator_check_consumers(rdev, &min_uV, &max_uV, 0);
	अगर (ret < 0)
		जाओ out;

	/* balance only, अगर regulator is coupled */
	अगर (rdev->coupling_desc.n_coupled > 1)
		ret = regulator_balance_voltage(rdev, PM_SUSPEND_ON);
	अन्यथा
		ret = _regulator_करो_set_voltage(rdev, min_uV, max_uV);

out:
	regulator_unlock(rdev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_sync_voltage);

पूर्णांक regulator_get_voltage_rdev(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक sel, ret;
	bool bypassed;

	अगर (rdev->desc->ops->get_bypass) अणु
		ret = rdev->desc->ops->get_bypass(rdev, &bypassed);
		अगर (ret < 0)
			वापस ret;
		अगर (bypassed) अणु
			/* अगर bypassed the regulator must have a supply */
			अगर (!rdev->supply) अणु
				rdev_err(rdev,
					 "bypassed regulator has no supply!\n");
				वापस -EPROBE_DEFER;
			पूर्ण

			वापस regulator_get_voltage_rdev(rdev->supply->rdev);
		पूर्ण
	पूर्ण

	अगर (rdev->desc->ops->get_voltage_sel) अणु
		sel = rdev->desc->ops->get_voltage_sel(rdev);
		अगर (sel < 0)
			वापस sel;
		ret = rdev->desc->ops->list_voltage(rdev, sel);
	पूर्ण अन्यथा अगर (rdev->desc->ops->get_voltage) अणु
		ret = rdev->desc->ops->get_voltage(rdev);
	पूर्ण अन्यथा अगर (rdev->desc->ops->list_voltage) अणु
		ret = rdev->desc->ops->list_voltage(rdev, 0);
	पूर्ण अन्यथा अगर (rdev->desc->fixed_uV && (rdev->desc->n_voltages == 1)) अणु
		ret = rdev->desc->fixed_uV;
	पूर्ण अन्यथा अगर (rdev->supply) अणु
		ret = regulator_get_voltage_rdev(rdev->supply->rdev);
	पूर्ण अन्यथा अगर (rdev->supply_name) अणु
		वापस -EPROBE_DEFER;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (ret < 0)
		वापस ret;
	वापस ret - rdev->स्थिरraपूर्णांकs->uV_offset;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_get_voltage_rdev);

/**
 * regulator_get_voltage - get regulator output voltage
 * @regulator: regulator source
 *
 * This वापसs the current regulator voltage in uV.
 *
 * NOTE: If the regulator is disabled it will वापस the voltage value. This
 * function should not be used to determine regulator state.
 */
पूर्णांक regulator_get_voltage(काष्ठा regulator *regulator)
अणु
	काष्ठा ww_acquire_ctx ww_ctx;
	पूर्णांक ret;

	regulator_lock_dependent(regulator->rdev, &ww_ctx);
	ret = regulator_get_voltage_rdev(regulator->rdev);
	regulator_unlock_dependent(regulator->rdev, &ww_ctx);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_get_voltage);

/**
 * regulator_set_current_limit - set regulator output current limit
 * @regulator: regulator source
 * @min_uA: Minimum supported current in uA
 * @max_uA: Maximum supported current in uA
 *
 * Sets current sink to the desired output current. This can be set during
 * any regulator state. IOW, regulator can be disabled or enabled.
 *
 * If the regulator is enabled then the current will change to the new value
 * immediately otherwise अगर the regulator is disabled the regulator will
 * output at the new current when enabled.
 *
 * NOTE: Regulator प्रणाली स्थिरraपूर्णांकs must be set क्रम this regulator beक्रमe
 * calling this function otherwise this call will fail.
 */
पूर्णांक regulator_set_current_limit(काष्ठा regulator *regulator,
			       पूर्णांक min_uA, पूर्णांक max_uA)
अणु
	काष्ठा regulator_dev *rdev = regulator->rdev;
	पूर्णांक ret;

	regulator_lock(rdev);

	/* sanity check */
	अगर (!rdev->desc->ops->set_current_limit) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* स्थिरraपूर्णांकs check */
	ret = regulator_check_current_limit(rdev, &min_uA, &max_uA);
	अगर (ret < 0)
		जाओ out;

	ret = rdev->desc->ops->set_current_limit(rdev, min_uA, max_uA);
out:
	regulator_unlock(rdev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_set_current_limit);

अटल पूर्णांक _regulator_get_current_limit_unlocked(काष्ठा regulator_dev *rdev)
अणु
	/* sanity check */
	अगर (!rdev->desc->ops->get_current_limit)
		वापस -EINVAL;

	वापस rdev->desc->ops->get_current_limit(rdev);
पूर्ण

अटल पूर्णांक _regulator_get_current_limit(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret;

	regulator_lock(rdev);
	ret = _regulator_get_current_limit_unlocked(rdev);
	regulator_unlock(rdev);

	वापस ret;
पूर्ण

/**
 * regulator_get_current_limit - get regulator output current
 * @regulator: regulator source
 *
 * This वापसs the current supplied by the specअगरied current sink in uA.
 *
 * NOTE: If the regulator is disabled it will वापस the current value. This
 * function should not be used to determine regulator state.
 */
पूर्णांक regulator_get_current_limit(काष्ठा regulator *regulator)
अणु
	वापस _regulator_get_current_limit(regulator->rdev);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_get_current_limit);

/**
 * regulator_set_mode - set regulator operating mode
 * @regulator: regulator source
 * @mode: operating mode - one of the REGULATOR_MODE स्थिरants
 *
 * Set regulator operating mode to increase regulator efficiency or improve
 * regulation perक्रमmance.
 *
 * NOTE: Regulator प्रणाली स्थिरraपूर्णांकs must be set क्रम this regulator beक्रमe
 * calling this function otherwise this call will fail.
 */
पूर्णांक regulator_set_mode(काष्ठा regulator *regulator, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा regulator_dev *rdev = regulator->rdev;
	पूर्णांक ret;
	पूर्णांक regulator_curr_mode;

	regulator_lock(rdev);

	/* sanity check */
	अगर (!rdev->desc->ops->set_mode) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* वापस अगर the same mode is requested */
	अगर (rdev->desc->ops->get_mode) अणु
		regulator_curr_mode = rdev->desc->ops->get_mode(rdev);
		अगर (regulator_curr_mode == mode) अणु
			ret = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	/* स्थिरraपूर्णांकs check */
	ret = regulator_mode_स्थिरrain(rdev, &mode);
	अगर (ret < 0)
		जाओ out;

	ret = rdev->desc->ops->set_mode(rdev, mode);
out:
	regulator_unlock(rdev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_set_mode);

अटल अचिन्हित पूर्णांक _regulator_get_mode_unlocked(काष्ठा regulator_dev *rdev)
अणु
	/* sanity check */
	अगर (!rdev->desc->ops->get_mode)
		वापस -EINVAL;

	वापस rdev->desc->ops->get_mode(rdev);
पूर्ण

अटल अचिन्हित पूर्णांक _regulator_get_mode(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret;

	regulator_lock(rdev);
	ret = _regulator_get_mode_unlocked(rdev);
	regulator_unlock(rdev);

	वापस ret;
पूर्ण

/**
 * regulator_get_mode - get regulator operating mode
 * @regulator: regulator source
 *
 * Get the current regulator operating mode.
 */
अचिन्हित पूर्णांक regulator_get_mode(काष्ठा regulator *regulator)
अणु
	वापस _regulator_get_mode(regulator->rdev);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_get_mode);

अटल पूर्णांक _regulator_get_error_flags(काष्ठा regulator_dev *rdev,
					अचिन्हित पूर्णांक *flags)
अणु
	पूर्णांक ret;

	regulator_lock(rdev);

	/* sanity check */
	अगर (!rdev->desc->ops->get_error_flags) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = rdev->desc->ops->get_error_flags(rdev, flags);
out:
	regulator_unlock(rdev);
	वापस ret;
पूर्ण

/**
 * regulator_get_error_flags - get regulator error inक्रमmation
 * @regulator: regulator source
 * @flags: poपूर्णांकer to store error flags
 *
 * Get the current regulator error inक्रमmation.
 */
पूर्णांक regulator_get_error_flags(काष्ठा regulator *regulator,
				अचिन्हित पूर्णांक *flags)
अणु
	वापस _regulator_get_error_flags(regulator->rdev, flags);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_get_error_flags);

/**
 * regulator_set_load - set regulator load
 * @regulator: regulator source
 * @uA_load: load current
 *
 * Notअगरies the regulator core of a new device load. This is then used by
 * DRMS (अगर enabled by स्थिरraपूर्णांकs) to set the most efficient regulator
 * operating mode क्रम the new regulator loading.
 *
 * Consumer devices notअगरy their supply regulator of the maximum घातer
 * they will require (can be taken from device datasheet in the घातer
 * consumption tables) when they change operational status and hence घातer
 * state. Examples of operational state changes that can affect घातer
 * consumption are :-
 *
 *    o Device is खोलोed / बंदd.
 *    o Device I/O is about to begin or has just finished.
 *    o Device is idling in between work.
 *
 * This inक्रमmation is also exported via sysfs to userspace.
 *
 * DRMS will sum the total requested load on the regulator and change
 * to the most efficient operating mode अगर platक्रमm स्थिरraपूर्णांकs allow.
 *
 * NOTE: when a regulator consumer requests to have a regulator
 * disabled then any load that consumer requested no दीर्घer counts
 * toward the total requested load.  If the regulator is re-enabled
 * then the previously requested load will start counting again.
 *
 * If a regulator is an always-on regulator then an inभागidual consumer's
 * load will still be हटाओd अगर that consumer is fully disabled.
 *
 * On error a negative त्रुटि_सं is वापसed.
 */
पूर्णांक regulator_set_load(काष्ठा regulator *regulator, पूर्णांक uA_load)
अणु
	काष्ठा regulator_dev *rdev = regulator->rdev;
	पूर्णांक old_uA_load;
	पूर्णांक ret = 0;

	regulator_lock(rdev);
	old_uA_load = regulator->uA_load;
	regulator->uA_load = uA_load;
	अगर (regulator->enable_count && old_uA_load != uA_load) अणु
		ret = drms_uA_update(rdev);
		अगर (ret < 0)
			regulator->uA_load = old_uA_load;
	पूर्ण
	regulator_unlock(rdev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_set_load);

/**
 * regulator_allow_bypass - allow the regulator to go पूर्णांकo bypass mode
 *
 * @regulator: Regulator to configure
 * @enable: enable or disable bypass mode
 *
 * Allow the regulator to go पूर्णांकo bypass mode अगर all other consumers
 * क्रम the regulator also enable bypass mode and the machine
 * स्थिरraपूर्णांकs allow this.  Bypass mode means that the regulator is
 * simply passing the input directly to the output with no regulation.
 */
पूर्णांक regulator_allow_bypass(काष्ठा regulator *regulator, bool enable)
अणु
	काष्ठा regulator_dev *rdev = regulator->rdev;
	स्थिर अक्षर *name = rdev_get_name(rdev);
	पूर्णांक ret = 0;

	अगर (!rdev->desc->ops->set_bypass)
		वापस 0;

	अगर (!regulator_ops_is_valid(rdev, REGULATOR_CHANGE_BYPASS))
		वापस 0;

	regulator_lock(rdev);

	अगर (enable && !regulator->bypass) अणु
		rdev->bypass_count++;

		अगर (rdev->bypass_count == rdev->खोलो_count) अणु
			trace_regulator_bypass_enable(name);

			ret = rdev->desc->ops->set_bypass(rdev, enable);
			अगर (ret != 0)
				rdev->bypass_count--;
			अन्यथा
				trace_regulator_bypass_enable_complete(name);
		पूर्ण

	पूर्ण अन्यथा अगर (!enable && regulator->bypass) अणु
		rdev->bypass_count--;

		अगर (rdev->bypass_count != rdev->खोलो_count) अणु
			trace_regulator_bypass_disable(name);

			ret = rdev->desc->ops->set_bypass(rdev, enable);
			अगर (ret != 0)
				rdev->bypass_count++;
			अन्यथा
				trace_regulator_bypass_disable_complete(name);
		पूर्ण
	पूर्ण

	अगर (ret == 0)
		regulator->bypass = enable;

	regulator_unlock(rdev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_allow_bypass);

/**
 * regulator_रेजिस्टर_notअगरier - रेजिस्टर regulator event notअगरier
 * @regulator: regulator source
 * @nb: notअगरier block
 *
 * Register notअगरier block to receive regulator events.
 */
पूर्णांक regulator_रेजिस्टर_notअगरier(काष्ठा regulator *regulator,
			      काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&regulator->rdev->notअगरier,
						nb);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_रेजिस्टर_notअगरier);

/**
 * regulator_unरेजिस्टर_notअगरier - unरेजिस्टर regulator event notअगरier
 * @regulator: regulator source
 * @nb: notअगरier block
 *
 * Unरेजिस्टर regulator event notअगरier block.
 */
पूर्णांक regulator_unरेजिस्टर_notअगरier(काष्ठा regulator *regulator,
				काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&regulator->rdev->notअगरier,
						  nb);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_unरेजिस्टर_notअगरier);

/* notअगरy regulator consumers and करोwnstream regulator consumers.
 * Note mutex must be held by caller.
 */
अटल पूर्णांक _notअगरier_call_chain(काष्ठा regulator_dev *rdev,
				  अचिन्हित दीर्घ event, व्योम *data)
अणु
	/* call rdev chain first */
	वापस blocking_notअगरier_call_chain(&rdev->notअगरier, event, data);
पूर्ण

/**
 * regulator_bulk_get - get multiple regulator consumers
 *
 * @dev:           Device to supply
 * @num_consumers: Number of consumers to रेजिस्टर
 * @consumers:     Configuration of consumers; clients are stored here.
 *
 * @वापस 0 on success, an त्रुटि_सं on failure.
 *
 * This helper function allows drivers to get several regulator
 * consumers in one operation.  If any of the regulators cannot be
 * acquired then any regulators that were allocated will be मुक्तd
 * beक्रमe वापसing to the caller.
 */
पूर्णांक regulator_bulk_get(काष्ठा device *dev, पूर्णांक num_consumers,
		       काष्ठा regulator_bulk_data *consumers)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < num_consumers; i++)
		consumers[i].consumer = शून्य;

	क्रम (i = 0; i < num_consumers; i++) अणु
		consumers[i].consumer = regulator_get(dev,
						      consumers[i].supply);
		अगर (IS_ERR(consumers[i].consumer)) अणु
			ret = PTR_ERR(consumers[i].consumer);
			consumers[i].consumer = शून्य;
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	अगर (ret != -EPROBE_DEFER)
		dev_err(dev, "Failed to get supply '%s': %pe\n",
			consumers[i].supply, ERR_PTR(ret));
	अन्यथा
		dev_dbg(dev, "Failed to get supply '%s', deferring\n",
			consumers[i].supply);

	जबतक (--i >= 0)
		regulator_put(consumers[i].consumer);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_bulk_get);

अटल व्योम regulator_bulk_enable_async(व्योम *data, async_cookie_t cookie)
अणु
	काष्ठा regulator_bulk_data *bulk = data;

	bulk->ret = regulator_enable(bulk->consumer);
पूर्ण

/**
 * regulator_bulk_enable - enable multiple regulator consumers
 *
 * @num_consumers: Number of consumers
 * @consumers:     Consumer data; clients are stored here.
 * @वापस         0 on success, an त्रुटि_सं on failure
 *
 * This convenience API allows consumers to enable multiple regulator
 * clients in a single API call.  If any consumers cannot be enabled
 * then any others that were enabled will be disabled again prior to
 * वापस.
 */
पूर्णांक regulator_bulk_enable(पूर्णांक num_consumers,
			  काष्ठा regulator_bulk_data *consumers)
अणु
	ASYNC_DOMAIN_EXCLUSIVE(async_करोमुख्य);
	पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < num_consumers; i++) अणु
		async_schedule_करोमुख्य(regulator_bulk_enable_async,
				      &consumers[i], &async_करोमुख्य);
	पूर्ण

	async_synchronize_full_करोमुख्य(&async_करोमुख्य);

	/* If any consumer failed we need to unwind any that succeeded */
	क्रम (i = 0; i < num_consumers; i++) अणु
		अगर (consumers[i].ret != 0) अणु
			ret = consumers[i].ret;
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	क्रम (i = 0; i < num_consumers; i++) अणु
		अगर (consumers[i].ret < 0)
			pr_err("Failed to enable %s: %pe\n", consumers[i].supply,
			       ERR_PTR(consumers[i].ret));
		अन्यथा
			regulator_disable(consumers[i].consumer);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_bulk_enable);

/**
 * regulator_bulk_disable - disable multiple regulator consumers
 *
 * @num_consumers: Number of consumers
 * @consumers:     Consumer data; clients are stored here.
 * @वापस         0 on success, an त्रुटि_सं on failure
 *
 * This convenience API allows consumers to disable multiple regulator
 * clients in a single API call.  If any consumers cannot be disabled
 * then any others that were disabled will be enabled again prior to
 * वापस.
 */
पूर्णांक regulator_bulk_disable(पूर्णांक num_consumers,
			   काष्ठा regulator_bulk_data *consumers)
अणु
	पूर्णांक i;
	पूर्णांक ret, r;

	क्रम (i = num_consumers - 1; i >= 0; --i) अणु
		ret = regulator_disable(consumers[i].consumer);
		अगर (ret != 0)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	pr_err("Failed to disable %s: %pe\n", consumers[i].supply, ERR_PTR(ret));
	क्रम (++i; i < num_consumers; ++i) अणु
		r = regulator_enable(consumers[i].consumer);
		अगर (r != 0)
			pr_err("Failed to re-enable %s: %pe\n",
			       consumers[i].supply, ERR_PTR(r));
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_bulk_disable);

/**
 * regulator_bulk_क्रमce_disable - क्रमce disable multiple regulator consumers
 *
 * @num_consumers: Number of consumers
 * @consumers:     Consumer data; clients are stored here.
 * @वापस         0 on success, an त्रुटि_सं on failure
 *
 * This convenience API allows consumers to क्रमcibly disable multiple regulator
 * clients in a single API call.
 * NOTE: This should be used क्रम situations when device damage will
 * likely occur अगर the regulators are not disabled (e.g. over temp).
 * Although regulator_क्रमce_disable function call क्रम some consumers can
 * वापस error numbers, the function is called क्रम all consumers.
 */
पूर्णांक regulator_bulk_क्रमce_disable(पूर्णांक num_consumers,
			   काष्ठा regulator_bulk_data *consumers)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < num_consumers; i++) अणु
		consumers[i].ret =
			    regulator_क्रमce_disable(consumers[i].consumer);

		/* Store first error क्रम reporting */
		अगर (consumers[i].ret && !ret)
			ret = consumers[i].ret;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_bulk_क्रमce_disable);

/**
 * regulator_bulk_मुक्त - मुक्त multiple regulator consumers
 *
 * @num_consumers: Number of consumers
 * @consumers:     Consumer data; clients are stored here.
 *
 * This convenience API allows consumers to मुक्त multiple regulator
 * clients in a single API call.
 */
व्योम regulator_bulk_मुक्त(पूर्णांक num_consumers,
			 काष्ठा regulator_bulk_data *consumers)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_consumers; i++) अणु
		regulator_put(consumers[i].consumer);
		consumers[i].consumer = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(regulator_bulk_मुक्त);

/**
 * regulator_notअगरier_call_chain - call regulator event notअगरier
 * @rdev: regulator source
 * @event: notअगरier block
 * @data: callback-specअगरic data.
 *
 * Called by regulator drivers to notअगरy clients a regulator event has
 * occurred.
 */
पूर्णांक regulator_notअगरier_call_chain(काष्ठा regulator_dev *rdev,
				  अचिन्हित दीर्घ event, व्योम *data)
अणु
	_notअगरier_call_chain(rdev, event, data);
	वापस NOTIFY_DONE;

पूर्ण
EXPORT_SYMBOL_GPL(regulator_notअगरier_call_chain);

/**
 * regulator_mode_to_status - convert a regulator mode पूर्णांकo a status
 *
 * @mode: Mode to convert
 *
 * Convert a regulator mode पूर्णांकo a status.
 */
पूर्णांक regulator_mode_to_status(अचिन्हित पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		वापस REGULATOR_STATUS_FAST;
	हाल REGULATOR_MODE_NORMAL:
		वापस REGULATOR_STATUS_NORMAL;
	हाल REGULATOR_MODE_IDLE:
		वापस REGULATOR_STATUS_IDLE;
	हाल REGULATOR_MODE_STANDBY:
		वापस REGULATOR_STATUS_STANDBY;
	शेष:
		वापस REGULATOR_STATUS_UNDEFINED;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(regulator_mode_to_status);

अटल काष्ठा attribute *regulator_dev_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_num_users.attr,
	&dev_attr_type.attr,
	&dev_attr_microvolts.attr,
	&dev_attr_microamps.attr,
	&dev_attr_opmode.attr,
	&dev_attr_state.attr,
	&dev_attr_status.attr,
	&dev_attr_bypass.attr,
	&dev_attr_requested_microamps.attr,
	&dev_attr_min_microvolts.attr,
	&dev_attr_max_microvolts.attr,
	&dev_attr_min_microamps.attr,
	&dev_attr_max_microamps.attr,
	&dev_attr_suspend_standby_state.attr,
	&dev_attr_suspend_mem_state.attr,
	&dev_attr_suspend_disk_state.attr,
	&dev_attr_suspend_standby_microvolts.attr,
	&dev_attr_suspend_mem_microvolts.attr,
	&dev_attr_suspend_disk_microvolts.attr,
	&dev_attr_suspend_standby_mode.attr,
	&dev_attr_suspend_mem_mode.attr,
	&dev_attr_suspend_disk_mode.attr,
	शून्य
पूर्ण;

/*
 * To aव्योम cluttering sysfs (and memory) with useless state, only
 * create attributes that can be meaningfully displayed.
 */
अटल umode_t regulator_attr_is_visible(काष्ठा kobject *kobj,
					 काष्ठा attribute *attr, पूर्णांक idx)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा regulator_dev *rdev = dev_to_rdev(dev);
	स्थिर काष्ठा regulator_ops *ops = rdev->desc->ops;
	umode_t mode = attr->mode;

	/* these three are always present */
	अगर (attr == &dev_attr_name.attr ||
	    attr == &dev_attr_num_users.attr ||
	    attr == &dev_attr_type.attr)
		वापस mode;

	/* some attributes need specअगरic methods to be displayed */
	अगर (attr == &dev_attr_microvolts.attr) अणु
		अगर ((ops->get_voltage && ops->get_voltage(rdev) >= 0) ||
		    (ops->get_voltage_sel && ops->get_voltage_sel(rdev) >= 0) ||
		    (ops->list_voltage && ops->list_voltage(rdev, 0) >= 0) ||
		    (rdev->desc->fixed_uV && rdev->desc->n_voltages == 1))
			वापस mode;
		वापस 0;
	पूर्ण

	अगर (attr == &dev_attr_microamps.attr)
		वापस ops->get_current_limit ? mode : 0;

	अगर (attr == &dev_attr_opmode.attr)
		वापस ops->get_mode ? mode : 0;

	अगर (attr == &dev_attr_state.attr)
		वापस (rdev->ena_pin || ops->is_enabled) ? mode : 0;

	अगर (attr == &dev_attr_status.attr)
		वापस ops->get_status ? mode : 0;

	अगर (attr == &dev_attr_bypass.attr)
		वापस ops->get_bypass ? mode : 0;

	/* स्थिरraपूर्णांकs need specअगरic supporting methods */
	अगर (attr == &dev_attr_min_microvolts.attr ||
	    attr == &dev_attr_max_microvolts.attr)
		वापस (ops->set_voltage || ops->set_voltage_sel) ? mode : 0;

	अगर (attr == &dev_attr_min_microamps.attr ||
	    attr == &dev_attr_max_microamps.attr)
		वापस ops->set_current_limit ? mode : 0;

	अगर (attr == &dev_attr_suspend_standby_state.attr ||
	    attr == &dev_attr_suspend_mem_state.attr ||
	    attr == &dev_attr_suspend_disk_state.attr)
		वापस mode;

	अगर (attr == &dev_attr_suspend_standby_microvolts.attr ||
	    attr == &dev_attr_suspend_mem_microvolts.attr ||
	    attr == &dev_attr_suspend_disk_microvolts.attr)
		वापस ops->set_suspend_voltage ? mode : 0;

	अगर (attr == &dev_attr_suspend_standby_mode.attr ||
	    attr == &dev_attr_suspend_mem_mode.attr ||
	    attr == &dev_attr_suspend_disk_mode.attr)
		वापस ops->set_suspend_mode ? mode : 0;

	वापस mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group regulator_dev_group = अणु
	.attrs = regulator_dev_attrs,
	.is_visible = regulator_attr_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *regulator_dev_groups[] = अणु
	&regulator_dev_group,
	शून्य
पूर्ण;

अटल व्योम regulator_dev_release(काष्ठा device *dev)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);

	kमुक्त(rdev->स्थिरraपूर्णांकs);
	of_node_put(rdev->dev.of_node);
	kमुक्त(rdev);
पूर्ण

अटल व्योम rdev_init_debugfs(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा device *parent = rdev->dev.parent;
	स्थिर अक्षर *rname = rdev_get_name(rdev);
	अक्षर name[NAME_MAX];

	/* Aव्योम duplicate debugfs directory names */
	अगर (parent && rname == rdev->desc->name) अणु
		snम_लिखो(name, माप(name), "%s-%s", dev_name(parent),
			 rname);
		rname = name;
	पूर्ण

	rdev->debugfs = debugfs_create_dir(rname, debugfs_root);
	अगर (!rdev->debugfs) अणु
		rdev_warn(rdev, "Failed to create debugfs directory\n");
		वापस;
	पूर्ण

	debugfs_create_u32("use_count", 0444, rdev->debugfs,
			   &rdev->use_count);
	debugfs_create_u32("open_count", 0444, rdev->debugfs,
			   &rdev->खोलो_count);
	debugfs_create_u32("bypass_count", 0444, rdev->debugfs,
			   &rdev->bypass_count);
पूर्ण

अटल पूर्णांक regulator_रेजिस्टर_resolve_supply(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा regulator_dev *rdev = dev_to_rdev(dev);

	अगर (regulator_resolve_supply(rdev))
		rdev_dbg(rdev, "unable to resolve supply\n");

	वापस 0;
पूर्ण

पूर्णांक regulator_coupler_रेजिस्टर(काष्ठा regulator_coupler *coupler)
अणु
	mutex_lock(&regulator_list_mutex);
	list_add_tail(&coupler->list, &regulator_coupler_list);
	mutex_unlock(&regulator_list_mutex);

	वापस 0;
पूर्ण

अटल काष्ठा regulator_coupler *
regulator_find_coupler(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा regulator_coupler *coupler;
	पूर्णांक err;

	/*
	 * Note that regulators are appended to the list and the generic
	 * coupler is रेजिस्टरed first, hence it will be attached at last
	 * अगर nobody cared.
	 */
	list_क्रम_each_entry_reverse(coupler, &regulator_coupler_list, list) अणु
		err = coupler->attach_regulator(coupler, rdev);
		अगर (!err) अणु
			अगर (!coupler->balance_voltage &&
			    rdev->coupling_desc.n_coupled > 2)
				जाओ err_unsupported;

			वापस coupler;
		पूर्ण

		अगर (err < 0)
			वापस ERR_PTR(err);

		अगर (err == 1)
			जारी;

		अवरोध;
	पूर्ण

	वापस ERR_PTR(-EINVAL);

err_unsupported:
	अगर (coupler->detach_regulator)
		coupler->detach_regulator(coupler, rdev);

	rdev_err(rdev,
		"Voltage balancing for multiple regulator couples is unimplemented\n");

	वापस ERR_PTR(-EPERM);
पूर्ण

अटल व्योम regulator_resolve_coupling(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा regulator_coupler *coupler = rdev->coupling_desc.coupler;
	काष्ठा coupling_desc *c_desc = &rdev->coupling_desc;
	पूर्णांक n_coupled = c_desc->n_coupled;
	काष्ठा regulator_dev *c_rdev;
	पूर्णांक i;

	क्रम (i = 1; i < n_coupled; i++) अणु
		/* alपढ़ोy resolved */
		अगर (c_desc->coupled_rdevs[i])
			जारी;

		c_rdev = of_parse_coupled_regulator(rdev, i - 1);

		अगर (!c_rdev)
			जारी;

		अगर (c_rdev->coupling_desc.coupler != coupler) अणु
			rdev_err(rdev, "coupler mismatch with %s\n",
				 rdev_get_name(c_rdev));
			वापस;
		पूर्ण

		c_desc->coupled_rdevs[i] = c_rdev;
		c_desc->n_resolved++;

		regulator_resolve_coupling(c_rdev);
	पूर्ण
पूर्ण

अटल व्योम regulator_हटाओ_coupling(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा regulator_coupler *coupler = rdev->coupling_desc.coupler;
	काष्ठा coupling_desc *__c_desc, *c_desc = &rdev->coupling_desc;
	काष्ठा regulator_dev *__c_rdev, *c_rdev;
	अचिन्हित पूर्णांक __n_coupled, n_coupled;
	पूर्णांक i, k;
	पूर्णांक err;

	n_coupled = c_desc->n_coupled;

	क्रम (i = 1; i < n_coupled; i++) अणु
		c_rdev = c_desc->coupled_rdevs[i];

		अगर (!c_rdev)
			जारी;

		regulator_lock(c_rdev);

		__c_desc = &c_rdev->coupling_desc;
		__n_coupled = __c_desc->n_coupled;

		क्रम (k = 1; k < __n_coupled; k++) अणु
			__c_rdev = __c_desc->coupled_rdevs[k];

			अगर (__c_rdev == rdev) अणु
				__c_desc->coupled_rdevs[k] = शून्य;
				__c_desc->n_resolved--;
				अवरोध;
			पूर्ण
		पूर्ण

		regulator_unlock(c_rdev);

		c_desc->coupled_rdevs[i] = शून्य;
		c_desc->n_resolved--;
	पूर्ण

	अगर (coupler && coupler->detach_regulator) अणु
		err = coupler->detach_regulator(coupler, rdev);
		अगर (err)
			rdev_err(rdev, "failed to detach from coupler: %pe\n",
				 ERR_PTR(err));
	पूर्ण

	kमुक्त(rdev->coupling_desc.coupled_rdevs);
	rdev->coupling_desc.coupled_rdevs = शून्य;
पूर्ण

अटल पूर्णांक regulator_init_coupling(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा regulator_dev **coupled;
	पूर्णांक err, n_phandles;

	अगर (!IS_ENABLED(CONFIG_OF))
		n_phandles = 0;
	अन्यथा
		n_phandles = of_get_n_coupled(rdev);

	coupled = kसुस्मृति(n_phandles + 1, माप(*coupled), GFP_KERNEL);
	अगर (!coupled)
		वापस -ENOMEM;

	rdev->coupling_desc.coupled_rdevs = coupled;

	/*
	 * Every regulator should always have coupling descriptor filled with
	 * at least poपूर्णांकer to itself.
	 */
	rdev->coupling_desc.coupled_rdevs[0] = rdev;
	rdev->coupling_desc.n_coupled = n_phandles + 1;
	rdev->coupling_desc.n_resolved++;

	/* regulator isn't coupled */
	अगर (n_phandles == 0)
		वापस 0;

	अगर (!of_check_coupling_data(rdev))
		वापस -EPERM;

	mutex_lock(&regulator_list_mutex);
	rdev->coupling_desc.coupler = regulator_find_coupler(rdev);
	mutex_unlock(&regulator_list_mutex);

	अगर (IS_ERR(rdev->coupling_desc.coupler)) अणु
		err = PTR_ERR(rdev->coupling_desc.coupler);
		rdev_err(rdev, "failed to get coupler: %pe\n", ERR_PTR(err));
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक generic_coupler_attach(काष्ठा regulator_coupler *coupler,
				  काष्ठा regulator_dev *rdev)
अणु
	अगर (rdev->coupling_desc.n_coupled > 2) अणु
		rdev_err(rdev,
			 "Voltage balancing for multiple regulator couples is unimplemented\n");
		वापस -EPERM;
	पूर्ण

	अगर (!rdev->स्थिरraपूर्णांकs->always_on) अणु
		rdev_err(rdev,
			 "Coupling of a non always-on regulator is unimplemented\n");
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा regulator_coupler generic_regulator_coupler = अणु
	.attach_regulator = generic_coupler_attach,
पूर्ण;

/**
 * regulator_रेजिस्टर - रेजिस्टर regulator
 * @regulator_desc: regulator to रेजिस्टर
 * @cfg: runसमय configuration क्रम regulator
 *
 * Called by regulator drivers to रेजिस्टर a regulator.
 * Returns a valid poपूर्णांकer to काष्ठा regulator_dev on success
 * or an ERR_PTR() on error.
 */
काष्ठा regulator_dev *
regulator_रेजिस्टर(स्थिर काष्ठा regulator_desc *regulator_desc,
		   स्थिर काष्ठा regulator_config *cfg)
अणु
	स्थिर काष्ठा regulator_init_data *init_data;
	काष्ठा regulator_config *config = शून्य;
	अटल atomic_t regulator_no = ATOMIC_INIT(-1);
	काष्ठा regulator_dev *rdev;
	bool dangling_cfg_gpiod = false;
	bool dangling_of_gpiod = false;
	काष्ठा device *dev;
	पूर्णांक ret, i;

	अगर (cfg == शून्य)
		वापस ERR_PTR(-EINVAL);
	अगर (cfg->ena_gpiod)
		dangling_cfg_gpiod = true;
	अगर (regulator_desc == शून्य) अणु
		ret = -EINVAL;
		जाओ rinse;
	पूर्ण

	dev = cfg->dev;
	WARN_ON(!dev);

	अगर (regulator_desc->name == शून्य || regulator_desc->ops == शून्य) अणु
		ret = -EINVAL;
		जाओ rinse;
	पूर्ण

	अगर (regulator_desc->type != REGULATOR_VOLTAGE &&
	    regulator_desc->type != REGULATOR_CURRENT) अणु
		ret = -EINVAL;
		जाओ rinse;
	पूर्ण

	/* Only one of each should be implemented */
	WARN_ON(regulator_desc->ops->get_voltage &&
		regulator_desc->ops->get_voltage_sel);
	WARN_ON(regulator_desc->ops->set_voltage &&
		regulator_desc->ops->set_voltage_sel);

	/* If we're using selectors we must implement list_voltage. */
	अगर (regulator_desc->ops->get_voltage_sel &&
	    !regulator_desc->ops->list_voltage) अणु
		ret = -EINVAL;
		जाओ rinse;
	पूर्ण
	अगर (regulator_desc->ops->set_voltage_sel &&
	    !regulator_desc->ops->list_voltage) अणु
		ret = -EINVAL;
		जाओ rinse;
	पूर्ण

	rdev = kzalloc(माप(काष्ठा regulator_dev), GFP_KERNEL);
	अगर (rdev == शून्य) अणु
		ret = -ENOMEM;
		जाओ rinse;
	पूर्ण
	device_initialize(&rdev->dev);

	/*
	 * Duplicate the config so the driver could override it after
	 * parsing init data.
	 */
	config = kmemdup(cfg, माप(*cfg), GFP_KERNEL);
	अगर (config == शून्य) अणु
		ret = -ENOMEM;
		जाओ clean;
	पूर्ण

	init_data = regulator_of_get_init_data(dev, regulator_desc, config,
					       &rdev->dev.of_node);

	/*
	 * Someबार not all resources are probed alपढ़ोy so we need to take
	 * that पूर्णांकo account. This happens most the समय अगर the ena_gpiod comes
	 * from a gpio extender or something अन्यथा.
	 */
	अगर (PTR_ERR(init_data) == -EPROBE_DEFER) अणु
		ret = -EPROBE_DEFER;
		जाओ clean;
	पूर्ण

	/*
	 * We need to keep track of any GPIO descriptor coming from the
	 * device tree until we have handled it over to the core. If the
	 * config that was passed in to this function DOES NOT contain
	 * a descriptor, and the config after this call DOES contain
	 * a descriptor, we definitely got one from parsing the device
	 * tree.
	 */
	अगर (!cfg->ena_gpiod && config->ena_gpiod)
		dangling_of_gpiod = true;
	अगर (!init_data) अणु
		init_data = config->init_data;
		rdev->dev.of_node = of_node_get(config->of_node);
	पूर्ण

	ww_mutex_init(&rdev->mutex, &regulator_ww_class);
	rdev->reg_data = config->driver_data;
	rdev->owner = regulator_desc->owner;
	rdev->desc = regulator_desc;
	अगर (config->regmap)
		rdev->regmap = config->regmap;
	अन्यथा अगर (dev_get_regmap(dev, शून्य))
		rdev->regmap = dev_get_regmap(dev, शून्य);
	अन्यथा अगर (dev->parent)
		rdev->regmap = dev_get_regmap(dev->parent, शून्य);
	INIT_LIST_HEAD(&rdev->consumer_list);
	INIT_LIST_HEAD(&rdev->list);
	BLOCKING_INIT_NOTIFIER_HEAD(&rdev->notअगरier);
	INIT_DELAYED_WORK(&rdev->disable_work, regulator_disable_work);

	/* preक्रमm any regulator specअगरic init */
	अगर (init_data && init_data->regulator_init) अणु
		ret = init_data->regulator_init(rdev->reg_data);
		अगर (ret < 0)
			जाओ clean;
	पूर्ण

	अगर (config->ena_gpiod) अणु
		ret = regulator_ena_gpio_request(rdev, config);
		अगर (ret != 0) अणु
			rdev_err(rdev, "Failed to request enable GPIO: %pe\n",
				 ERR_PTR(ret));
			जाओ clean;
		पूर्ण
		/* The regulator core took over the GPIO descriptor */
		dangling_cfg_gpiod = false;
		dangling_of_gpiod = false;
	पूर्ण

	/* रेजिस्टर with sysfs */
	rdev->dev.class = &regulator_class;
	rdev->dev.parent = dev;
	dev_set_name(&rdev->dev, "regulator.%lu",
		    (अचिन्हित दीर्घ) atomic_inc_वापस(&regulator_no));
	dev_set_drvdata(&rdev->dev, rdev);

	/* set regulator स्थिरraपूर्णांकs */
	अगर (init_data)
		rdev->स्थिरraपूर्णांकs = kmemdup(&init_data->स्थिरraपूर्णांकs,
					    माप(*rdev->स्थिरraपूर्णांकs),
					    GFP_KERNEL);
	अन्यथा
		rdev->स्थिरraपूर्णांकs = kzalloc(माप(*rdev->स्थिरraपूर्णांकs),
					    GFP_KERNEL);
	अगर (!rdev->स्थिरraपूर्णांकs) अणु
		ret = -ENOMEM;
		जाओ wash;
	पूर्ण

	अगर (init_data && init_data->supply_regulator)
		rdev->supply_name = init_data->supply_regulator;
	अन्यथा अगर (regulator_desc->supply_name)
		rdev->supply_name = regulator_desc->supply_name;

	ret = set_machine_स्थिरraपूर्णांकs(rdev);
	अगर (ret == -EPROBE_DEFER) अणु
		/* Regulator might be in bypass mode and so needs its supply
		 * to set the स्थिरraपूर्णांकs
		 */
		/* FIXME: this currently triggers a chicken-and-egg problem
		 * when creating -SUPPLY symlink in sysfs to a regulator
		 * that is just being created
		 */
		rdev_dbg(rdev, "will resolve supply early: %s\n",
			 rdev->supply_name);
		ret = regulator_resolve_supply(rdev);
		अगर (!ret)
			ret = set_machine_स्थिरraपूर्णांकs(rdev);
		अन्यथा
			rdev_dbg(rdev, "unable to resolve supply early: %pe\n",
				 ERR_PTR(ret));
	पूर्ण
	अगर (ret < 0)
		जाओ wash;

	ret = regulator_init_coupling(rdev);
	अगर (ret < 0)
		जाओ wash;

	/* add consumers devices */
	अगर (init_data) अणु
		क्रम (i = 0; i < init_data->num_consumer_supplies; i++) अणु
			ret = set_consumer_device_supply(rdev,
				init_data->consumer_supplies[i].dev_name,
				init_data->consumer_supplies[i].supply);
			अगर (ret < 0) अणु
				dev_err(dev, "Failed to set supply %s\n",
					init_data->consumer_supplies[i].supply);
				जाओ unset_supplies;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!rdev->desc->ops->get_voltage &&
	    !rdev->desc->ops->list_voltage &&
	    !rdev->desc->fixed_uV)
		rdev->is_चयन = true;

	ret = device_add(&rdev->dev);
	अगर (ret != 0)
		जाओ unset_supplies;

	rdev_init_debugfs(rdev);

	/* try to resolve regulators coupling since a new one was रेजिस्टरed */
	mutex_lock(&regulator_list_mutex);
	regulator_resolve_coupling(rdev);
	mutex_unlock(&regulator_list_mutex);

	/* try to resolve regulators supply since a new one was रेजिस्टरed */
	class_क्रम_each_device(&regulator_class, शून्य, शून्य,
			      regulator_रेजिस्टर_resolve_supply);
	kमुक्त(config);
	वापस rdev;

unset_supplies:
	mutex_lock(&regulator_list_mutex);
	unset_regulator_supplies(rdev);
	regulator_हटाओ_coupling(rdev);
	mutex_unlock(&regulator_list_mutex);
wash:
	kमुक्त(rdev->coupling_desc.coupled_rdevs);
	mutex_lock(&regulator_list_mutex);
	regulator_ena_gpio_मुक्त(rdev);
	mutex_unlock(&regulator_list_mutex);
clean:
	अगर (dangling_of_gpiod)
		gpiod_put(config->ena_gpiod);
	kमुक्त(config);
	put_device(&rdev->dev);
rinse:
	अगर (dangling_cfg_gpiod)
		gpiod_put(cfg->ena_gpiod);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_रेजिस्टर);

/**
 * regulator_unरेजिस्टर - unरेजिस्टर regulator
 * @rdev: regulator to unरेजिस्टर
 *
 * Called by regulator drivers to unरेजिस्टर a regulator.
 */
व्योम regulator_unरेजिस्टर(काष्ठा regulator_dev *rdev)
अणु
	अगर (rdev == शून्य)
		वापस;

	अगर (rdev->supply) अणु
		जबतक (rdev->use_count--)
			regulator_disable(rdev->supply);
		regulator_put(rdev->supply);
	पूर्ण

	flush_work(&rdev->disable_work.work);

	mutex_lock(&regulator_list_mutex);

	debugfs_हटाओ_recursive(rdev->debugfs);
	WARN_ON(rdev->खोलो_count);
	regulator_हटाओ_coupling(rdev);
	unset_regulator_supplies(rdev);
	list_del(&rdev->list);
	regulator_ena_gpio_मुक्त(rdev);
	device_unरेजिस्टर(&rdev->dev);

	mutex_unlock(&regulator_list_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_unरेजिस्टर);

#अगर_घोषित CONFIG_SUSPEND
/**
 * regulator_suspend - prepare regulators क्रम प्रणाली wide suspend
 * @dev: ``&काष्ठा device`` poपूर्णांकer that is passed to _regulator_suspend()
 *
 * Configure each regulator with it's suspend operating parameters क्रम state.
 */
अटल पूर्णांक regulator_suspend(काष्ठा device *dev)
अणु
	काष्ठा regulator_dev *rdev = dev_to_rdev(dev);
	suspend_state_t state = pm_suspend_target_state;
	पूर्णांक ret;
	स्थिर काष्ठा regulator_state *rstate;

	rstate = regulator_get_suspend_state_check(rdev, state);
	अगर (!rstate)
		वापस 0;

	regulator_lock(rdev);
	ret = __suspend_set_state(rdev, rstate);
	regulator_unlock(rdev);

	वापस ret;
पूर्ण

अटल पूर्णांक regulator_resume(काष्ठा device *dev)
अणु
	suspend_state_t state = pm_suspend_target_state;
	काष्ठा regulator_dev *rdev = dev_to_rdev(dev);
	काष्ठा regulator_state *rstate;
	पूर्णांक ret = 0;

	rstate = regulator_get_suspend_state(rdev, state);
	अगर (rstate == शून्य)
		वापस 0;

	/* Aव्योम grabbing the lock अगर we करोn't need to */
	अगर (!rdev->desc->ops->resume)
		वापस 0;

	regulator_lock(rdev);

	अगर (rstate->enabled == ENABLE_IN_SUSPEND ||
	    rstate->enabled == DISABLE_IN_SUSPEND)
		ret = rdev->desc->ops->resume(rdev);

	regulator_unlock(rdev);

	वापस ret;
पूर्ण
#अन्यथा /* !CONFIG_SUSPEND */

#घोषणा regulator_suspend	शून्य
#घोषणा regulator_resume	शून्य

#पूर्ण_अगर /* !CONFIG_SUSPEND */

#अगर_घोषित CONFIG_PM
अटल स्थिर काष्ठा dev_pm_ops __maybe_unused regulator_pm_ops = अणु
	.suspend	= regulator_suspend,
	.resume		= regulator_resume,
पूर्ण;
#पूर्ण_अगर

काष्ठा class regulator_class = अणु
	.name = "regulator",
	.dev_release = regulator_dev_release,
	.dev_groups = regulator_dev_groups,
#अगर_घोषित CONFIG_PM
	.pm = &regulator_pm_ops,
#पूर्ण_अगर
पूर्ण;
/**
 * regulator_has_full_स्थिरraपूर्णांकs - the प्रणाली has fully specअगरied स्थिरraपूर्णांकs
 *
 * Calling this function will cause the regulator API to disable all
 * regulators which have a zero use count and करोn't have an always_on
 * स्थिरraपूर्णांक in a late_initcall.
 *
 * The पूर्णांकention is that this will become the शेष behaviour in a
 * future kernel release so users are encouraged to use this facility
 * now.
 */
व्योम regulator_has_full_स्थिरraपूर्णांकs(व्योम)
अणु
	has_full_स्थिरraपूर्णांकs = 1;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_has_full_स्थिरraपूर्णांकs);

/**
 * rdev_get_drvdata - get rdev regulator driver data
 * @rdev: regulator
 *
 * Get rdev regulator driver निजी data. This call can be used in the
 * regulator driver context.
 */
व्योम *rdev_get_drvdata(काष्ठा regulator_dev *rdev)
अणु
	वापस rdev->reg_data;
पूर्ण
EXPORT_SYMBOL_GPL(rdev_get_drvdata);

/**
 * regulator_get_drvdata - get regulator driver data
 * @regulator: regulator
 *
 * Get regulator driver निजी data. This call can be used in the consumer
 * driver context when non API regulator specअगरic functions need to be called.
 */
व्योम *regulator_get_drvdata(काष्ठा regulator *regulator)
अणु
	वापस regulator->rdev->reg_data;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_get_drvdata);

/**
 * regulator_set_drvdata - set regulator driver data
 * @regulator: regulator
 * @data: data
 */
व्योम regulator_set_drvdata(काष्ठा regulator *regulator, व्योम *data)
अणु
	regulator->rdev->reg_data = data;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_set_drvdata);

/**
 * rdev_get_id - get regulator ID
 * @rdev: regulator
 */
पूर्णांक rdev_get_id(काष्ठा regulator_dev *rdev)
अणु
	वापस rdev->desc->id;
पूर्ण
EXPORT_SYMBOL_GPL(rdev_get_id);

काष्ठा device *rdev_get_dev(काष्ठा regulator_dev *rdev)
अणु
	वापस &rdev->dev;
पूर्ण
EXPORT_SYMBOL_GPL(rdev_get_dev);

काष्ठा regmap *rdev_get_regmap(काष्ठा regulator_dev *rdev)
अणु
	वापस rdev->regmap;
पूर्ण
EXPORT_SYMBOL_GPL(rdev_get_regmap);

व्योम *regulator_get_init_drvdata(काष्ठा regulator_init_data *reg_init_data)
अणु
	वापस reg_init_data->driver_data;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_get_init_drvdata);

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक supply_map_show(काष्ठा seq_file *sf, व्योम *data)
अणु
	काष्ठा regulator_map *map;

	list_क्रम_each_entry(map, &regulator_map_list, list) अणु
		seq_म_लिखो(sf, "%s -> %s.%s\n",
				rdev_get_name(map->regulator), map->dev_name,
				map->supply);
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(supply_map);

काष्ठा summary_data अणु
	काष्ठा seq_file *s;
	काष्ठा regulator_dev *parent;
	पूर्णांक level;
पूर्ण;

अटल व्योम regulator_summary_show_subtree(काष्ठा seq_file *s,
					   काष्ठा regulator_dev *rdev,
					   पूर्णांक level);

अटल पूर्णांक regulator_summary_show_children(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा regulator_dev *rdev = dev_to_rdev(dev);
	काष्ठा summary_data *summary_data = data;

	अगर (rdev->supply && rdev->supply->rdev == summary_data->parent)
		regulator_summary_show_subtree(summary_data->s, rdev,
					       summary_data->level + 1);

	वापस 0;
पूर्ण

अटल व्योम regulator_summary_show_subtree(काष्ठा seq_file *s,
					   काष्ठा regulator_dev *rdev,
					   पूर्णांक level)
अणु
	काष्ठा regulation_स्थिरraपूर्णांकs *c;
	काष्ठा regulator *consumer;
	काष्ठा summary_data summary_data;
	अचिन्हित पूर्णांक opmode;

	अगर (!rdev)
		वापस;

	opmode = _regulator_get_mode_unlocked(rdev);
	seq_म_लिखो(s, "%*s%-*s %3d %4d %6d %7s ",
		   level * 3 + 1, "",
		   30 - level * 3, rdev_get_name(rdev),
		   rdev->use_count, rdev->खोलो_count, rdev->bypass_count,
		   regulator_opmode_to_str(opmode));

	seq_म_लिखो(s, "%5dmV ", regulator_get_voltage_rdev(rdev) / 1000);
	seq_म_लिखो(s, "%5dmA ",
		   _regulator_get_current_limit_unlocked(rdev) / 1000);

	c = rdev->स्थिरraपूर्णांकs;
	अगर (c) अणु
		चयन (rdev->desc->type) अणु
		हाल REGULATOR_VOLTAGE:
			seq_म_लिखो(s, "%5dmV %5dmV ",
				   c->min_uV / 1000, c->max_uV / 1000);
			अवरोध;
		हाल REGULATOR_CURRENT:
			seq_म_लिखो(s, "%5dmA %5dmA ",
				   c->min_uA / 1000, c->max_uA / 1000);
			अवरोध;
		पूर्ण
	पूर्ण

	seq_माला_दो(s, "\n");

	list_क्रम_each_entry(consumer, &rdev->consumer_list, list) अणु
		अगर (consumer->dev && consumer->dev->class == &regulator_class)
			जारी;

		seq_म_लिखो(s, "%*s%-*s ",
			   (level + 1) * 3 + 1, "",
			   30 - (level + 1) * 3,
			   consumer->supply_name ? consumer->supply_name :
			   consumer->dev ? dev_name(consumer->dev) : "deviceless");

		चयन (rdev->desc->type) अणु
		हाल REGULATOR_VOLTAGE:
			seq_म_लिखो(s, "%3d %33dmA%c%5dmV %5dmV",
				   consumer->enable_count,
				   consumer->uA_load / 1000,
				   consumer->uA_load && !consumer->enable_count ?
				   '*' : ' ',
				   consumer->voltage[PM_SUSPEND_ON].min_uV / 1000,
				   consumer->voltage[PM_SUSPEND_ON].max_uV / 1000);
			अवरोध;
		हाल REGULATOR_CURRENT:
			अवरोध;
		पूर्ण

		seq_माला_दो(s, "\n");
	पूर्ण

	summary_data.s = s;
	summary_data.level = level;
	summary_data.parent = rdev;

	class_क्रम_each_device(&regulator_class, शून्य, &summary_data,
			      regulator_summary_show_children);
पूर्ण

काष्ठा summary_lock_data अणु
	काष्ठा ww_acquire_ctx *ww_ctx;
	काष्ठा regulator_dev **new_contended_rdev;
	काष्ठा regulator_dev **old_contended_rdev;
पूर्ण;

अटल पूर्णांक regulator_summary_lock_one(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा regulator_dev *rdev = dev_to_rdev(dev);
	काष्ठा summary_lock_data *lock_data = data;
	पूर्णांक ret = 0;

	अगर (rdev != *lock_data->old_contended_rdev) अणु
		ret = regulator_lock_nested(rdev, lock_data->ww_ctx);

		अगर (ret == -EDEADLK)
			*lock_data->new_contended_rdev = rdev;
		अन्यथा
			WARN_ON_ONCE(ret);
	पूर्ण अन्यथा अणु
		*lock_data->old_contended_rdev = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक regulator_summary_unlock_one(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा regulator_dev *rdev = dev_to_rdev(dev);
	काष्ठा summary_lock_data *lock_data = data;

	अगर (lock_data) अणु
		अगर (rdev == *lock_data->new_contended_rdev)
			वापस -EDEADLK;
	पूर्ण

	regulator_unlock(rdev);

	वापस 0;
पूर्ण

अटल पूर्णांक regulator_summary_lock_all(काष्ठा ww_acquire_ctx *ww_ctx,
				      काष्ठा regulator_dev **new_contended_rdev,
				      काष्ठा regulator_dev **old_contended_rdev)
अणु
	काष्ठा summary_lock_data lock_data;
	पूर्णांक ret;

	lock_data.ww_ctx = ww_ctx;
	lock_data.new_contended_rdev = new_contended_rdev;
	lock_data.old_contended_rdev = old_contended_rdev;

	ret = class_क्रम_each_device(&regulator_class, शून्य, &lock_data,
				    regulator_summary_lock_one);
	अगर (ret)
		class_क्रम_each_device(&regulator_class, शून्य, &lock_data,
				      regulator_summary_unlock_one);

	वापस ret;
पूर्ण

अटल व्योम regulator_summary_lock(काष्ठा ww_acquire_ctx *ww_ctx)
अणु
	काष्ठा regulator_dev *new_contended_rdev = शून्य;
	काष्ठा regulator_dev *old_contended_rdev = शून्य;
	पूर्णांक err;

	mutex_lock(&regulator_list_mutex);

	ww_acquire_init(ww_ctx, &regulator_ww_class);

	करो अणु
		अगर (new_contended_rdev) अणु
			ww_mutex_lock_slow(&new_contended_rdev->mutex, ww_ctx);
			old_contended_rdev = new_contended_rdev;
			old_contended_rdev->ref_cnt++;
		पूर्ण

		err = regulator_summary_lock_all(ww_ctx,
						 &new_contended_rdev,
						 &old_contended_rdev);

		अगर (old_contended_rdev)
			regulator_unlock(old_contended_rdev);

	पूर्ण जबतक (err == -EDEADLK);

	ww_acquire_करोne(ww_ctx);
पूर्ण

अटल व्योम regulator_summary_unlock(काष्ठा ww_acquire_ctx *ww_ctx)
अणु
	class_क्रम_each_device(&regulator_class, शून्य, शून्य,
			      regulator_summary_unlock_one);
	ww_acquire_fini(ww_ctx);

	mutex_unlock(&regulator_list_mutex);
पूर्ण

अटल पूर्णांक regulator_summary_show_roots(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा regulator_dev *rdev = dev_to_rdev(dev);
	काष्ठा seq_file *s = data;

	अगर (!rdev->supply)
		regulator_summary_show_subtree(s, rdev, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक regulator_summary_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा ww_acquire_ctx ww_ctx;

	seq_माला_दो(s, " regulator                      use open bypass  opmode voltage current     min     max\n");
	seq_माला_दो(s, "---------------------------------------------------------------------------------------\n");

	regulator_summary_lock(&ww_ctx);

	class_क्रम_each_device(&regulator_class, शून्य, s,
			      regulator_summary_show_roots);

	regulator_summary_unlock(&ww_ctx);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(regulator_summary);
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल पूर्णांक __init regulator_init(व्योम)
अणु
	पूर्णांक ret;

	ret = class_रेजिस्टर(&regulator_class);

	debugfs_root = debugfs_create_dir("regulator", शून्य);
	अगर (!debugfs_root)
		pr_warn("regulator: Failed to create debugfs directory\n");

#अगर_घोषित CONFIG_DEBUG_FS
	debugfs_create_file("supply_map", 0444, debugfs_root, शून्य,
			    &supply_map_fops);

	debugfs_create_file("regulator_summary", 0444, debugfs_root,
			    शून्य, &regulator_summary_fops);
#पूर्ण_अगर
	regulator_dummy_init();

	regulator_coupler_रेजिस्टर(&generic_regulator_coupler);

	वापस ret;
पूर्ण

/* init early to allow our consumers to complete प्रणाली booting */
core_initcall(regulator_init);

अटल पूर्णांक regulator_late_cleanup(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा regulator_dev *rdev = dev_to_rdev(dev);
	स्थिर काष्ठा regulator_ops *ops = rdev->desc->ops;
	काष्ठा regulation_स्थिरraपूर्णांकs *c = rdev->स्थिरraपूर्णांकs;
	पूर्णांक enabled, ret;

	अगर (c && c->always_on)
		वापस 0;

	अगर (!regulator_ops_is_valid(rdev, REGULATOR_CHANGE_STATUS))
		वापस 0;

	regulator_lock(rdev);

	अगर (rdev->use_count)
		जाओ unlock;

	/* If we can't read the status assume it's always on. */
	अगर (ops->is_enabled)
		enabled = ops->is_enabled(rdev);
	अन्यथा
		enabled = 1;

	/* But अगर पढ़ोing the status failed, assume that it's off. */
	अगर (enabled <= 0)
		जाओ unlock;

	अगर (have_full_स्थिरraपूर्णांकs()) अणु
		/* We log since this may समाप्त the प्रणाली अगर it goes
		 * wrong.
		 */
		rdev_info(rdev, "disabling\n");
		ret = _regulator_करो_disable(rdev);
		अगर (ret != 0)
			rdev_err(rdev, "couldn't disable: %pe\n", ERR_PTR(ret));
	पूर्ण अन्यथा अणु
		/* The पूर्णांकention is that in future we will
		 * assume that full स्थिरraपूर्णांकs are provided
		 * so warn even अगर we aren't going to करो
		 * anything here.
		 */
		rdev_warn(rdev, "incomplete constraints, leaving on\n");
	पूर्ण

unlock:
	regulator_unlock(rdev);

	वापस 0;
पूर्ण

अटल व्योम regulator_init_complete_work_function(काष्ठा work_काष्ठा *work)
अणु
	/*
	 * Regulators may had failed to resolve their input supplies
	 * when were रेजिस्टरed, either because the input supply was
	 * not रेजिस्टरed yet or because its parent device was not
	 * bound yet. So attempt to resolve the input supplies क्रम
	 * pending regulators beक्रमe trying to disable unused ones.
	 */
	class_क्रम_each_device(&regulator_class, शून्य, शून्य,
			      regulator_रेजिस्टर_resolve_supply);

	/* If we have a full configuration then disable any regulators
	 * we have permission to change the status क्रम and which are
	 * not in use or always_on.  This is effectively the शेष
	 * क्रम DT and ACPI as they have full स्थिरraपूर्णांकs.
	 */
	class_क्रम_each_device(&regulator_class, शून्य, शून्य,
			      regulator_late_cleanup);
पूर्ण

अटल DECLARE_DELAYED_WORK(regulator_init_complete_work,
			    regulator_init_complete_work_function);

अटल पूर्णांक __init regulator_init_complete(व्योम)
अणु
	/*
	 * Since DT करोesn't provide an idiomatic mechanism क्रम
	 * enabling full स्थिरraपूर्णांकs and since it's much more natural
	 * with DT to provide them just assume that a DT enabled
	 * प्रणाली has full स्थिरraपूर्णांकs.
	 */
	अगर (of_have_populated_dt())
		has_full_स्थिरraपूर्णांकs = true;

	/*
	 * We punt completion क्रम an arbitrary amount of समय since
	 * प्रणालीs like distros will load many drivers from userspace
	 * so consumers might not always be पढ़ोy yet, this is
	 * particularly an issue with laptops where this might bounce
	 * the display off then on.  Ideally we'd get a notअगरication
	 * from userspace when this happens but we करोn't so just रुको
	 * a bit and hope we रुकोed दीर्घ enough.  It'd be better अगर
	 * we'd only करो this on प्रणालीs that need it, and a kernel
	 * command line option might be useful.
	 */
	schedule_delayed_work(&regulator_init_complete_work,
			      msecs_to_jअगरfies(30000));

	वापस 0;
पूर्ण
late_initcall_sync(regulator_init_complete);
