<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * devres.c  --  Voltage/Current Regulator framework devres implementation.
 *
 * Copyright 2013 Linaro Ltd
 */

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/module.h>

#समावेश "internal.h"

अटल व्योम devm_regulator_release(काष्ठा device *dev, व्योम *res)
अणु
	regulator_put(*(काष्ठा regulator **)res);
पूर्ण

अटल काष्ठा regulator *_devm_regulator_get(काष्ठा device *dev, स्थिर अक्षर *id,
					     पूर्णांक get_type)
अणु
	काष्ठा regulator **ptr, *regulator;

	ptr = devres_alloc(devm_regulator_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	regulator = _regulator_get(dev, id, get_type);
	अगर (!IS_ERR(regulator)) अणु
		*ptr = regulator;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस regulator;
पूर्ण

/**
 * devm_regulator_get - Resource managed regulator_get()
 * @dev: device to supply
 * @id:  supply name or regulator ID.
 *
 * Managed regulator_get(). Regulators वापसed from this function are
 * स्वतःmatically regulator_put() on driver detach. See regulator_get() क्रम more
 * inक्रमmation.
 */
काष्ठा regulator *devm_regulator_get(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	वापस _devm_regulator_get(dev, id, NORMAL_GET);
पूर्ण
EXPORT_SYMBOL_GPL(devm_regulator_get);

/**
 * devm_regulator_get_exclusive - Resource managed regulator_get_exclusive()
 * @dev: device to supply
 * @id:  supply name or regulator ID.
 *
 * Managed regulator_get_exclusive(). Regulators वापसed from this function
 * are स्वतःmatically regulator_put() on driver detach. See regulator_get() क्रम
 * more inक्रमmation.
 */
काष्ठा regulator *devm_regulator_get_exclusive(काष्ठा device *dev,
					       स्थिर अक्षर *id)
अणु
	वापस _devm_regulator_get(dev, id, EXCLUSIVE_GET);
पूर्ण
EXPORT_SYMBOL_GPL(devm_regulator_get_exclusive);

/**
 * devm_regulator_get_optional - Resource managed regulator_get_optional()
 * @dev: device to supply
 * @id:  supply name or regulator ID.
 *
 * Managed regulator_get_optional(). Regulators वापसed from this
 * function are स्वतःmatically regulator_put() on driver detach. See
 * regulator_get_optional() क्रम more inक्रमmation.
 */
काष्ठा regulator *devm_regulator_get_optional(काष्ठा device *dev,
					      स्थिर अक्षर *id)
अणु
	वापस _devm_regulator_get(dev, id, OPTIONAL_GET);
पूर्ण
EXPORT_SYMBOL_GPL(devm_regulator_get_optional);

अटल पूर्णांक devm_regulator_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा regulator **r = res;
	अगर (!r || !*r) अणु
		WARN_ON(!r || !*r);
		वापस 0;
	पूर्ण
	वापस *r == data;
पूर्ण

/**
 * devm_regulator_put - Resource managed regulator_put()
 * @regulator: regulator to मुक्त
 *
 * Deallocate a regulator allocated with devm_regulator_get(). Normally
 * this function will not need to be called and the resource management
 * code will ensure that the resource is मुक्तd.
 */
व्योम devm_regulator_put(काष्ठा regulator *regulator)
अणु
	पूर्णांक rc;

	rc = devres_release(regulator->dev, devm_regulator_release,
			    devm_regulator_match, regulator);
	अगर (rc != 0)
		WARN_ON(rc);
पूर्ण
EXPORT_SYMBOL_GPL(devm_regulator_put);

काष्ठा regulator_bulk_devres अणु
	काष्ठा regulator_bulk_data *consumers;
	पूर्णांक num_consumers;
पूर्ण;

अटल व्योम devm_regulator_bulk_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा regulator_bulk_devres *devres = res;

	regulator_bulk_मुक्त(devres->num_consumers, devres->consumers);
पूर्ण

/**
 * devm_regulator_bulk_get - managed get multiple regulator consumers
 *
 * @dev:           device to supply
 * @num_consumers: number of consumers to रेजिस्टर
 * @consumers:     configuration of consumers; clients are stored here.
 *
 * @वापस 0 on success, an त्रुटि_सं on failure.
 *
 * This helper function allows drivers to get several regulator
 * consumers in one operation with management, the regulators will
 * स्वतःmatically be मुक्तd when the device is unbound.  If any of the
 * regulators cannot be acquired then any regulators that were
 * allocated will be मुक्तd beक्रमe वापसing to the caller.
 */
पूर्णांक devm_regulator_bulk_get(काष्ठा device *dev, पूर्णांक num_consumers,
			    काष्ठा regulator_bulk_data *consumers)
अणु
	काष्ठा regulator_bulk_devres *devres;
	पूर्णांक ret;

	devres = devres_alloc(devm_regulator_bulk_release,
			      माप(*devres), GFP_KERNEL);
	अगर (!devres)
		वापस -ENOMEM;

	ret = regulator_bulk_get(dev, num_consumers, consumers);
	अगर (!ret) अणु
		devres->consumers = consumers;
		devres->num_consumers = num_consumers;
		devres_add(dev, devres);
	पूर्ण अन्यथा अणु
		devres_मुक्त(devres);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_regulator_bulk_get);

अटल व्योम devm_rdev_release(काष्ठा device *dev, व्योम *res)
अणु
	regulator_unरेजिस्टर(*(काष्ठा regulator_dev **)res);
पूर्ण

/**
 * devm_regulator_रेजिस्टर - Resource managed regulator_रेजिस्टर()
 * @dev:            device to supply
 * @regulator_desc: regulator to रेजिस्टर
 * @config:         runसमय configuration क्रम regulator
 *
 * Called by regulator drivers to रेजिस्टर a regulator.  Returns a
 * valid poपूर्णांकer to काष्ठा regulator_dev on success or an ERR_PTR() on
 * error.  The regulator will स्वतःmatically be released when the device
 * is unbound.
 */
काष्ठा regulator_dev *devm_regulator_रेजिस्टर(काष्ठा device *dev,
				  स्थिर काष्ठा regulator_desc *regulator_desc,
				  स्थिर काष्ठा regulator_config *config)
अणु
	काष्ठा regulator_dev **ptr, *rdev;

	ptr = devres_alloc(devm_rdev_release, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	rdev = regulator_रेजिस्टर(regulator_desc, config);
	अगर (!IS_ERR(rdev)) अणु
		*ptr = rdev;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस rdev;
पूर्ण
EXPORT_SYMBOL_GPL(devm_regulator_रेजिस्टर);

अटल पूर्णांक devm_rdev_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा regulator_dev **r = res;
	अगर (!r || !*r) अणु
		WARN_ON(!r || !*r);
		वापस 0;
	पूर्ण
	वापस *r == data;
पूर्ण

/**
 * devm_regulator_unरेजिस्टर - Resource managed regulator_unरेजिस्टर()
 * @dev:  device to supply
 * @rdev: regulator to मुक्त
 *
 * Unरेजिस्टर a regulator रेजिस्टरed with devm_regulator_रेजिस्टर().
 * Normally this function will not need to be called and the resource
 * management code will ensure that the resource is मुक्तd.
 */
व्योम devm_regulator_unरेजिस्टर(काष्ठा device *dev, काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक rc;

	rc = devres_release(dev, devm_rdev_release, devm_rdev_match, rdev);
	अगर (rc != 0)
		WARN_ON(rc);
पूर्ण
EXPORT_SYMBOL_GPL(devm_regulator_unरेजिस्टर);

काष्ठा regulator_supply_alias_match अणु
	काष्ठा device *dev;
	स्थिर अक्षर *id;
पूर्ण;

अटल पूर्णांक devm_regulator_match_supply_alias(काष्ठा device *dev, व्योम *res,
					     व्योम *data)
अणु
	काष्ठा regulator_supply_alias_match *match = res;
	काष्ठा regulator_supply_alias_match *target = data;

	वापस match->dev == target->dev && म_भेद(match->id, target->id) == 0;
पूर्ण

अटल व्योम devm_regulator_destroy_supply_alias(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा regulator_supply_alias_match *match = res;

	regulator_unरेजिस्टर_supply_alias(match->dev, match->id);
पूर्ण

/**
 * devm_regulator_रेजिस्टर_supply_alias - Resource managed
 * regulator_रेजिस्टर_supply_alias()
 *
 * @dev:       device to supply
 * @id:        supply name or regulator ID
 * @alias_dev: device that should be used to lookup the supply
 * @alias_id:  supply name or regulator ID that should be used to lookup the
 * supply
 *
 * The supply alias will स्वतःmatically be unरेजिस्टरed when the source
 * device is unbound.
 */
पूर्णांक devm_regulator_रेजिस्टर_supply_alias(काष्ठा device *dev, स्थिर अक्षर *id,
					 काष्ठा device *alias_dev,
					 स्थिर अक्षर *alias_id)
अणु
	काष्ठा regulator_supply_alias_match *match;
	पूर्णांक ret;

	match = devres_alloc(devm_regulator_destroy_supply_alias,
			   माप(काष्ठा regulator_supply_alias_match),
			   GFP_KERNEL);
	अगर (!match)
		वापस -ENOMEM;

	match->dev = dev;
	match->id = id;

	ret = regulator_रेजिस्टर_supply_alias(dev, id, alias_dev, alias_id);
	अगर (ret < 0) अणु
		devres_मुक्त(match);
		वापस ret;
	पूर्ण

	devres_add(dev, match);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_regulator_रेजिस्टर_supply_alias);

/**
 * devm_regulator_unरेजिस्टर_supply_alias - Resource managed
 * regulator_unरेजिस्टर_supply_alias()
 *
 * @dev: device to supply
 * @id:  supply name or regulator ID
 *
 * Unरेजिस्टर an alias रेजिस्टरed with
 * devm_regulator_रेजिस्टर_supply_alias(). Normally this function
 * will not need to be called and the resource management code
 * will ensure that the resource is मुक्तd.
 */
व्योम devm_regulator_unरेजिस्टर_supply_alias(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	काष्ठा regulator_supply_alias_match match;
	पूर्णांक rc;

	match.dev = dev;
	match.id = id;

	rc = devres_release(dev, devm_regulator_destroy_supply_alias,
			    devm_regulator_match_supply_alias, &match);
	अगर (rc != 0)
		WARN_ON(rc);
पूर्ण
EXPORT_SYMBOL_GPL(devm_regulator_unरेजिस्टर_supply_alias);

/**
 * devm_regulator_bulk_रेजिस्टर_supply_alias - Managed रेजिस्टर
 * multiple aliases
 *
 * @dev:       device to supply
 * @id:        list of supply names or regulator IDs
 * @alias_dev: device that should be used to lookup the supply
 * @alias_id:  list of supply names or regulator IDs that should be used to
 *             lookup the supply
 * @num_id:    number of aliases to रेजिस्टर
 *
 * @वापस 0 on success, an त्रुटि_सं on failure.
 *
 * This helper function allows drivers to रेजिस्टर several supply
 * aliases in one operation, the aliases will be स्वतःmatically
 * unरेजिस्टरs when the source device is unbound.  If any of the
 * aliases cannot be रेजिस्टरed any aliases that were रेजिस्टरed
 * will be हटाओd beक्रमe वापसing to the caller.
 */
पूर्णांक devm_regulator_bulk_रेजिस्टर_supply_alias(काष्ठा device *dev,
					      स्थिर अक्षर *स्थिर *id,
					      काष्ठा device *alias_dev,
					      स्थिर अक्षर *स्थिर *alias_id,
					      पूर्णांक num_id)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < num_id; ++i) अणु
		ret = devm_regulator_रेजिस्टर_supply_alias(dev, id[i],
							   alias_dev,
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
		devm_regulator_unरेजिस्टर_supply_alias(dev, id[i]);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_regulator_bulk_रेजिस्टर_supply_alias);

/**
 * devm_regulator_bulk_unरेजिस्टर_supply_alias - Managed unरेजिस्टर
 * multiple aliases
 *
 * @dev:    device to supply
 * @id:     list of supply names or regulator IDs
 * @num_id: number of aliases to unरेजिस्टर
 *
 * Unरेजिस्टर aliases रेजिस्टरed with
 * devm_regulator_bulk_रेजिस्टर_supply_alias(). Normally this function
 * will not need to be called and the resource management code
 * will ensure that the resource is मुक्तd.
 */
व्योम devm_regulator_bulk_unरेजिस्टर_supply_alias(काष्ठा device *dev,
						 स्थिर अक्षर *स्थिर *id,
						 पूर्णांक num_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_id; ++i)
		devm_regulator_unरेजिस्टर_supply_alias(dev, id[i]);
पूर्ण
EXPORT_SYMBOL_GPL(devm_regulator_bulk_unरेजिस्टर_supply_alias);

काष्ठा regulator_notअगरier_match अणु
	काष्ठा regulator *regulator;
	काष्ठा notअगरier_block *nb;
पूर्ण;

अटल पूर्णांक devm_regulator_match_notअगरier(काष्ठा device *dev, व्योम *res,
					 व्योम *data)
अणु
	काष्ठा regulator_notअगरier_match *match = res;
	काष्ठा regulator_notअगरier_match *target = data;

	वापस match->regulator == target->regulator && match->nb == target->nb;
पूर्ण

अटल व्योम devm_regulator_destroy_notअगरier(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा regulator_notअगरier_match *match = res;

	regulator_unरेजिस्टर_notअगरier(match->regulator, match->nb);
पूर्ण

/**
 * devm_regulator_रेजिस्टर_notअगरier - Resource managed
 * regulator_रेजिस्टर_notअगरier
 *
 * @regulator: regulator source
 * @nb:        notअगरier block
 *
 * The notअगरier will be रेजिस्टरs under the consumer device and be
 * स्वतःmatically be unरेजिस्टरed when the source device is unbound.
 */
पूर्णांक devm_regulator_रेजिस्टर_notअगरier(काष्ठा regulator *regulator,
				     काष्ठा notअगरier_block *nb)
अणु
	काष्ठा regulator_notअगरier_match *match;
	पूर्णांक ret;

	match = devres_alloc(devm_regulator_destroy_notअगरier,
			     माप(काष्ठा regulator_notअगरier_match),
			     GFP_KERNEL);
	अगर (!match)
		वापस -ENOMEM;

	match->regulator = regulator;
	match->nb = nb;

	ret = regulator_रेजिस्टर_notअगरier(regulator, nb);
	अगर (ret < 0) अणु
		devres_मुक्त(match);
		वापस ret;
	पूर्ण

	devres_add(regulator->dev, match);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_regulator_रेजिस्टर_notअगरier);

/**
 * devm_regulator_unरेजिस्टर_notअगरier - Resource managed
 * regulator_unरेजिस्टर_notअगरier()
 *
 * @regulator: regulator source
 * @nb:        notअगरier block
 *
 * Unरेजिस्टर a notअगरier रेजिस्टरed with devm_regulator_रेजिस्टर_notअगरier().
 * Normally this function will not need to be called and the resource
 * management code will ensure that the resource is मुक्तd.
 */
व्योम devm_regulator_unरेजिस्टर_notअगरier(काष्ठा regulator *regulator,
					काष्ठा notअगरier_block *nb)
अणु
	काष्ठा regulator_notअगरier_match match;
	पूर्णांक rc;

	match.regulator = regulator;
	match.nb = nb;

	rc = devres_release(regulator->dev, devm_regulator_destroy_notअगरier,
			    devm_regulator_match_notअगरier, &match);
	अगर (rc != 0)
		WARN_ON(rc);
पूर्ण
EXPORT_SYMBOL_GPL(devm_regulator_unरेजिस्टर_notअगरier);
