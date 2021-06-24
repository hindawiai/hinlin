<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Multiplexer subप्रणाली
 *
 * Copyright (C) 2017 Axentia Technologies AB
 *
 * Author: Peter Rosin <peda@axentia.se>
 */

#घोषणा pr_fmt(fmt) "mux-core: " fmt

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/idr.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mux/consumer.h>
#समावेश <linux/mux/driver.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>

/*
 * The idle-as-is "state" is not an actual state that may be selected, it
 * only implies that the state should not be changed. So, use that state
 * as indication that the cached state of the multiplexer is unknown.
 */
#घोषणा MUX_CACHE_UNKNOWN MUX_IDLE_AS_IS

अटल काष्ठा class mux_class = अणु
	.name = "mux",
	.owner = THIS_MODULE,
पूर्ण;

अटल DEFINE_IDA(mux_ida);

अटल पूर्णांक __init mux_init(व्योम)
अणु
	ida_init(&mux_ida);
	वापस class_रेजिस्टर(&mux_class);
पूर्ण

अटल व्योम __निकास mux_निकास(व्योम)
अणु
	class_unरेजिस्टर(&mux_class);
	ida_destroy(&mux_ida);
पूर्ण

अटल व्योम mux_chip_release(काष्ठा device *dev)
अणु
	काष्ठा mux_chip *mux_chip = to_mux_chip(dev);

	ida_simple_हटाओ(&mux_ida, mux_chip->id);
	kमुक्त(mux_chip);
पूर्ण

अटल स्थिर काष्ठा device_type mux_type = अणु
	.name = "mux-chip",
	.release = mux_chip_release,
पूर्ण;

/**
 * mux_chip_alloc() - Allocate a mux-chip.
 * @dev: The parent device implementing the mux पूर्णांकerface.
 * @controllers: The number of mux controllers to allocate क्रम this chip.
 * @माप_priv: Size of extra memory area क्रम निजी use by the caller.
 *
 * After allocating the mux-chip with the desired number of mux controllers
 * but beक्रमe रेजिस्टरing the chip, the mux driver is required to configure
 * the number of valid mux states in the mux_chip->mux[N].states members and
 * the desired idle state in the वापसed mux_chip->mux[N].idle_state members.
 * The शेष idle state is MUX_IDLE_AS_IS. The mux driver also needs to
 * provide a poपूर्णांकer to the operations काष्ठा in the mux_chip->ops member
 * beक्रमe रेजिस्टरing the mux-chip with mux_chip_रेजिस्टर.
 *
 * Return: A poपूर्णांकer to the new mux-chip, or an ERR_PTR with a negative त्रुटि_सं.
 */
काष्ठा mux_chip *mux_chip_alloc(काष्ठा device *dev,
				अचिन्हित पूर्णांक controllers, माप_प्रकार माप_priv)
अणु
	काष्ठा mux_chip *mux_chip;
	पूर्णांक i;

	अगर (WARN_ON(!dev || !controllers))
		वापस ERR_PTR(-EINVAL);

	mux_chip = kzalloc(माप(*mux_chip) +
			   controllers * माप(*mux_chip->mux) +
			   माप_priv, GFP_KERNEL);
	अगर (!mux_chip)
		वापस ERR_PTR(-ENOMEM);

	mux_chip->mux = (काष्ठा mux_control *)(mux_chip + 1);
	mux_chip->dev.class = &mux_class;
	mux_chip->dev.type = &mux_type;
	mux_chip->dev.parent = dev;
	mux_chip->dev.of_node = dev->of_node;
	dev_set_drvdata(&mux_chip->dev, mux_chip);

	mux_chip->id = ida_simple_get(&mux_ida, 0, 0, GFP_KERNEL);
	अगर (mux_chip->id < 0) अणु
		पूर्णांक err = mux_chip->id;

		pr_err("muxchipX failed to get a device id\n");
		kमुक्त(mux_chip);
		वापस ERR_PTR(err);
	पूर्ण
	dev_set_name(&mux_chip->dev, "muxchip%d", mux_chip->id);

	mux_chip->controllers = controllers;
	क्रम (i = 0; i < controllers; ++i) अणु
		काष्ठा mux_control *mux = &mux_chip->mux[i];

		mux->chip = mux_chip;
		sema_init(&mux->lock, 1);
		mux->cached_state = MUX_CACHE_UNKNOWN;
		mux->idle_state = MUX_IDLE_AS_IS;
	पूर्ण

	device_initialize(&mux_chip->dev);

	वापस mux_chip;
पूर्ण
EXPORT_SYMBOL_GPL(mux_chip_alloc);

अटल पूर्णांक mux_control_set(काष्ठा mux_control *mux, पूर्णांक state)
अणु
	पूर्णांक ret = mux->chip->ops->set(mux, state);

	mux->cached_state = ret < 0 ? MUX_CACHE_UNKNOWN : state;

	वापस ret;
पूर्ण

/**
 * mux_chip_रेजिस्टर() - Register a mux-chip, thus पढ़ोying the controllers
 *			 क्रम use.
 * @mux_chip: The mux-chip to रेजिस्टर.
 *
 * Do not retry registration of the same mux-chip on failure. You should
 * instead put it away with mux_chip_मुक्त() and allocate a new one, अगर you
 * क्रम some reason would like to retry registration.
 *
 * Return: Zero on success or a negative त्रुटि_सं on error.
 */
पूर्णांक mux_chip_रेजिस्टर(काष्ठा mux_chip *mux_chip)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < mux_chip->controllers; ++i) अणु
		काष्ठा mux_control *mux = &mux_chip->mux[i];

		अगर (mux->idle_state == mux->cached_state)
			जारी;

		ret = mux_control_set(mux, mux->idle_state);
		अगर (ret < 0) अणु
			dev_err(&mux_chip->dev, "unable to set idle state\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = device_add(&mux_chip->dev);
	अगर (ret < 0)
		dev_err(&mux_chip->dev,
			"device_add failed in %s: %d\n", __func__, ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mux_chip_रेजिस्टर);

/**
 * mux_chip_unरेजिस्टर() - Take the mux-chip off-line.
 * @mux_chip: The mux-chip to unरेजिस्टर.
 *
 * mux_chip_unरेजिस्टर() reverses the effects of mux_chip_रेजिस्टर().
 * But not completely, you should not try to call mux_chip_रेजिस्टर()
 * on a mux-chip that has been रेजिस्टरed beक्रमe.
 */
व्योम mux_chip_unरेजिस्टर(काष्ठा mux_chip *mux_chip)
अणु
	device_del(&mux_chip->dev);
पूर्ण
EXPORT_SYMBOL_GPL(mux_chip_unरेजिस्टर);

/**
 * mux_chip_मुक्त() - Free the mux-chip क्रम good.
 * @mux_chip: The mux-chip to मुक्त.
 *
 * mux_chip_मुक्त() reverses the effects of mux_chip_alloc().
 */
व्योम mux_chip_मुक्त(काष्ठा mux_chip *mux_chip)
अणु
	अगर (!mux_chip)
		वापस;

	put_device(&mux_chip->dev);
पूर्ण
EXPORT_SYMBOL_GPL(mux_chip_मुक्त);

अटल व्योम devm_mux_chip_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा mux_chip *mux_chip = *(काष्ठा mux_chip **)res;

	mux_chip_मुक्त(mux_chip);
पूर्ण

/**
 * devm_mux_chip_alloc() - Resource-managed version of mux_chip_alloc().
 * @dev: The parent device implementing the mux पूर्णांकerface.
 * @controllers: The number of mux controllers to allocate क्रम this chip.
 * @माप_priv: Size of extra memory area क्रम निजी use by the caller.
 *
 * See mux_chip_alloc() क्रम more details.
 *
 * Return: A poपूर्णांकer to the new mux-chip, or an ERR_PTR with a negative त्रुटि_सं.
 */
काष्ठा mux_chip *devm_mux_chip_alloc(काष्ठा device *dev,
				     अचिन्हित पूर्णांक controllers,
				     माप_प्रकार माप_priv)
अणु
	काष्ठा mux_chip **ptr, *mux_chip;

	ptr = devres_alloc(devm_mux_chip_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	mux_chip = mux_chip_alloc(dev, controllers, माप_priv);
	अगर (IS_ERR(mux_chip)) अणु
		devres_मुक्त(ptr);
		वापस mux_chip;
	पूर्ण

	*ptr = mux_chip;
	devres_add(dev, ptr);

	वापस mux_chip;
पूर्ण
EXPORT_SYMBOL_GPL(devm_mux_chip_alloc);

अटल व्योम devm_mux_chip_reg_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा mux_chip *mux_chip = *(काष्ठा mux_chip **)res;

	mux_chip_unरेजिस्टर(mux_chip);
पूर्ण

/**
 * devm_mux_chip_रेजिस्टर() - Resource-managed version mux_chip_रेजिस्टर().
 * @dev: The parent device implementing the mux पूर्णांकerface.
 * @mux_chip: The mux-chip to रेजिस्टर.
 *
 * See mux_chip_रेजिस्टर() क्रम more details.
 *
 * Return: Zero on success or a negative त्रुटि_सं on error.
 */
पूर्णांक devm_mux_chip_रेजिस्टर(काष्ठा device *dev,
			   काष्ठा mux_chip *mux_chip)
अणु
	काष्ठा mux_chip **ptr;
	पूर्णांक res;

	ptr = devres_alloc(devm_mux_chip_reg_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	res = mux_chip_रेजिस्टर(mux_chip);
	अगर (res) अणु
		devres_मुक्त(ptr);
		वापस res;
	पूर्ण

	*ptr = mux_chip;
	devres_add(dev, ptr);

	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(devm_mux_chip_रेजिस्टर);

/**
 * mux_control_states() - Query the number of multiplexer states.
 * @mux: The mux-control to query.
 *
 * Return: The number of multiplexer states.
 */
अचिन्हित पूर्णांक mux_control_states(काष्ठा mux_control *mux)
अणु
	वापस mux->states;
पूर्ण
EXPORT_SYMBOL_GPL(mux_control_states);

/*
 * The mux->lock must be करोwn when calling this function.
 */
अटल पूर्णांक __mux_control_select(काष्ठा mux_control *mux, पूर्णांक state)
अणु
	पूर्णांक ret;

	अगर (WARN_ON(state < 0 || state >= mux->states))
		वापस -EINVAL;

	अगर (mux->cached_state == state)
		वापस 0;

	ret = mux_control_set(mux, state);
	अगर (ret >= 0)
		वापस 0;

	/* The mux update failed, try to revert अगर appropriate... */
	अगर (mux->idle_state != MUX_IDLE_AS_IS)
		mux_control_set(mux, mux->idle_state);

	वापस ret;
पूर्ण

/**
 * mux_control_select() - Select the given multiplexer state.
 * @mux: The mux-control to request a change of state from.
 * @state: The new requested state.
 *
 * On successfully selecting the mux-control state, it will be locked until
 * there is a call to mux_control_deselect(). If the mux-control is alपढ़ोy
 * selected when mux_control_select() is called, the caller will be blocked
 * until mux_control_deselect() is called (by someone अन्यथा).
 *
 * Thereक्रमe, make sure to call mux_control_deselect() when the operation is
 * complete and the mux-control is मुक्त क्रम others to use, but करो not call
 * mux_control_deselect() अगर mux_control_select() fails.
 *
 * Return: 0 when the mux-control state has the requested state or a negative
 * त्रुटि_सं on error.
 */
पूर्णांक mux_control_select(काष्ठा mux_control *mux, अचिन्हित पूर्णांक state)
अणु
	पूर्णांक ret;

	ret = करोwn_समाप्तable(&mux->lock);
	अगर (ret < 0)
		वापस ret;

	ret = __mux_control_select(mux, state);

	अगर (ret < 0)
		up(&mux->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mux_control_select);

/**
 * mux_control_try_select() - Try to select the given multiplexer state.
 * @mux: The mux-control to request a change of state from.
 * @state: The new requested state.
 *
 * On successfully selecting the mux-control state, it will be locked until
 * mux_control_deselect() called.
 *
 * Thereक्रमe, make sure to call mux_control_deselect() when the operation is
 * complete and the mux-control is मुक्त क्रम others to use, but करो not call
 * mux_control_deselect() अगर mux_control_try_select() fails.
 *
 * Return: 0 when the mux-control state has the requested state or a negative
 * त्रुटि_सं on error. Specअगरically -EBUSY अगर the mux-control is contended.
 */
पूर्णांक mux_control_try_select(काष्ठा mux_control *mux, अचिन्हित पूर्णांक state)
अणु
	पूर्णांक ret;

	अगर (करोwn_trylock(&mux->lock))
		वापस -EBUSY;

	ret = __mux_control_select(mux, state);

	अगर (ret < 0)
		up(&mux->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mux_control_try_select);

/**
 * mux_control_deselect() - Deselect the previously selected multiplexer state.
 * @mux: The mux-control to deselect.
 *
 * It is required that a single call is made to mux_control_deselect() क्रम
 * each and every successful call made to either of mux_control_select() or
 * mux_control_try_select().
 *
 * Return: 0 on success and a negative त्रुटि_सं on error. An error can only
 * occur अगर the mux has an idle state. Note that even अगर an error occurs, the
 * mux-control is unlocked and is thus मुक्त क्रम the next access.
 */
पूर्णांक mux_control_deselect(काष्ठा mux_control *mux)
अणु
	पूर्णांक ret = 0;

	अगर (mux->idle_state != MUX_IDLE_AS_IS &&
	    mux->idle_state != mux->cached_state)
		ret = mux_control_set(mux, mux->idle_state);

	up(&mux->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mux_control_deselect);

/* Note this function वापसs a reference to the mux_chip dev. */
अटल काष्ठा mux_chip *of_find_mux_chip_by_node(काष्ठा device_node *np)
अणु
	काष्ठा device *dev;

	dev = class_find_device_by_of_node(&mux_class, np);

	वापस dev ? to_mux_chip(dev) : शून्य;
पूर्ण

/**
 * mux_control_get() - Get the mux-control क्रम a device.
 * @dev: The device that needs a mux-control.
 * @mux_name: The name identअगरying the mux-control.
 *
 * Return: A poपूर्णांकer to the mux-control, or an ERR_PTR with a negative त्रुटि_सं.
 */
काष्ठा mux_control *mux_control_get(काष्ठा device *dev, स्थिर अक्षर *mux_name)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा of_phandle_args args;
	काष्ठा mux_chip *mux_chip;
	अचिन्हित पूर्णांक controller;
	पूर्णांक index = 0;
	पूर्णांक ret;

	अगर (mux_name) अणु
		index = of_property_match_string(np, "mux-control-names",
						 mux_name);
		अगर (index < 0) अणु
			dev_err(dev, "mux controller '%s' not found\n",
				mux_name);
			वापस ERR_PTR(index);
		पूर्ण
	पूर्ण

	ret = of_parse_phandle_with_args(np,
					 "mux-controls", "#mux-control-cells",
					 index, &args);
	अगर (ret) अणु
		dev_err(dev, "%pOF: failed to get mux-control %s(%i)\n",
			np, mux_name ?: "", index);
		वापस ERR_PTR(ret);
	पूर्ण

	mux_chip = of_find_mux_chip_by_node(args.np);
	of_node_put(args.np);
	अगर (!mux_chip)
		वापस ERR_PTR(-EPROBE_DEFER);

	अगर (args.args_count > 1 ||
	    (!args.args_count && (mux_chip->controllers > 1))) अणु
		dev_err(dev, "%pOF: wrong #mux-control-cells for %pOF\n",
			np, args.np);
		put_device(&mux_chip->dev);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	controller = 0;
	अगर (args.args_count)
		controller = args.args[0];

	अगर (controller >= mux_chip->controllers) अणु
		dev_err(dev, "%pOF: bad mux controller %u specified in %pOF\n",
			np, controller, args.np);
		put_device(&mux_chip->dev);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस &mux_chip->mux[controller];
पूर्ण
EXPORT_SYMBOL_GPL(mux_control_get);

/**
 * mux_control_put() - Put away the mux-control क्रम good.
 * @mux: The mux-control to put away.
 *
 * mux_control_put() reverses the effects of mux_control_get().
 */
व्योम mux_control_put(काष्ठा mux_control *mux)
अणु
	put_device(&mux->chip->dev);
पूर्ण
EXPORT_SYMBOL_GPL(mux_control_put);

अटल व्योम devm_mux_control_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा mux_control *mux = *(काष्ठा mux_control **)res;

	mux_control_put(mux);
पूर्ण

/**
 * devm_mux_control_get() - Get the mux-control क्रम a device, with resource
 *			    management.
 * @dev: The device that needs a mux-control.
 * @mux_name: The name identअगरying the mux-control.
 *
 * Return: Poपूर्णांकer to the mux-control, or an ERR_PTR with a negative त्रुटि_सं.
 */
काष्ठा mux_control *devm_mux_control_get(काष्ठा device *dev,
					 स्थिर अक्षर *mux_name)
अणु
	काष्ठा mux_control **ptr, *mux;

	ptr = devres_alloc(devm_mux_control_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	mux = mux_control_get(dev, mux_name);
	अगर (IS_ERR(mux)) अणु
		devres_मुक्त(ptr);
		वापस mux;
	पूर्ण

	*ptr = mux;
	devres_add(dev, ptr);

	वापस mux;
पूर्ण
EXPORT_SYMBOL_GPL(devm_mux_control_get);

/*
 * Using subsys_initcall instead of module_init here to try to ensure - क्रम
 * the non-modular हाल - that the subप्रणाली is initialized when mux consumers
 * and mux controllers start to use it.
 * For the modular हाल, the ordering is ensured with module dependencies.
 */
subsys_initcall(mux_init);
module_निकास(mux_निकास);

MODULE_DESCRIPTION("Multiplexer subsystem");
MODULE_AUTHOR("Peter Rosin <peda@axentia.se>");
MODULE_LICENSE("GPL v2");
