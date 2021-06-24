<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Universal घातer supply monitor class
 *
 *  Copyright तऊ 2007  Anton Vorontsov <cbou@mail.ru>
 *  Copyright तऊ 2004  Szabolcs Gyurko
 *  Copyright तऊ 2003  Ian Molton <spyro@f2s.com>
 *
 *  Modअगरied: 2004, Oct     Szabolcs Gyurko
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/property.h>
#समावेश <linux/thermal.h>
#समावेश "power_supply.h"

/* exported क्रम the APM Power driver, APM emulation */
काष्ठा class *घातer_supply_class;
EXPORT_SYMBOL_GPL(घातer_supply_class);

ATOMIC_NOTIFIER_HEAD(घातer_supply_notअगरier);
EXPORT_SYMBOL_GPL(घातer_supply_notअगरier);

अटल काष्ठा device_type घातer_supply_dev_type;

#घोषणा POWER_SUPPLY_DEFERRED_REGISTER_TIME	msecs_to_jअगरfies(10)

अटल bool __घातer_supply_is_supplied_by(काष्ठा घातer_supply *supplier,
					 काष्ठा घातer_supply *supply)
अणु
	पूर्णांक i;

	अगर (!supply->supplied_from && !supplier->supplied_to)
		वापस false;

	/* Support both supplied_to and supplied_from modes */
	अगर (supply->supplied_from) अणु
		अगर (!supplier->desc->name)
			वापस false;
		क्रम (i = 0; i < supply->num_supplies; i++)
			अगर (!म_भेद(supplier->desc->name, supply->supplied_from[i]))
				वापस true;
	पूर्ण अन्यथा अणु
		अगर (!supply->desc->name)
			वापस false;
		क्रम (i = 0; i < supplier->num_supplicants; i++)
			अगर (!म_भेद(supplier->supplied_to[i], supply->desc->name))
				वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक __घातer_supply_changed_work(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा घातer_supply *psy = data;
	काष्ठा घातer_supply *pst = dev_get_drvdata(dev);

	अगर (__घातer_supply_is_supplied_by(psy, pst)) अणु
		अगर (pst->desc->बाह्यal_घातer_changed)
			pst->desc->बाह्यal_घातer_changed(pst);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम घातer_supply_changed_work(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा घातer_supply *psy = container_of(work, काष्ठा घातer_supply,
						changed_work);

	dev_dbg(&psy->dev, "%s\n", __func__);

	spin_lock_irqsave(&psy->changed_lock, flags);
	/*
	 * Check 'changed' here to aव्योम issues due to race between
	 * घातer_supply_changed() and this routine. In worst हाल
	 * घातer_supply_changed() can be called again just beक्रमe we take above
	 * lock. During the first call of this routine we will mark 'changed' as
	 * false and it will stay false क्रम the next call as well.
	 */
	अगर (likely(psy->changed)) अणु
		psy->changed = false;
		spin_unlock_irqrestore(&psy->changed_lock, flags);
		class_क्रम_each_device(घातer_supply_class, शून्य, psy,
				      __घातer_supply_changed_work);
		घातer_supply_update_leds(psy);
		atomic_notअगरier_call_chain(&घातer_supply_notअगरier,
				PSY_EVENT_PROP_CHANGED, psy);
		kobject_uevent(&psy->dev.kobj, KOBJ_CHANGE);
		spin_lock_irqsave(&psy->changed_lock, flags);
	पूर्ण

	/*
	 * Hold the wakeup_source until all events are processed.
	 * घातer_supply_changed() might have called again and have set 'changed'
	 * to true.
	 */
	अगर (likely(!psy->changed))
		pm_relax(&psy->dev);
	spin_unlock_irqrestore(&psy->changed_lock, flags);
पूर्ण

व्योम घातer_supply_changed(काष्ठा घातer_supply *psy)
अणु
	अचिन्हित दीर्घ flags;

	dev_dbg(&psy->dev, "%s\n", __func__);

	spin_lock_irqsave(&psy->changed_lock, flags);
	psy->changed = true;
	pm_stay_awake(&psy->dev);
	spin_unlock_irqrestore(&psy->changed_lock, flags);
	schedule_work(&psy->changed_work);
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_changed);

/*
 * Notअगरy that घातer supply was रेजिस्टरed after parent finished the probing.
 *
 * Often घातer supply is रेजिस्टरed from driver's probe function. However
 * calling घातer_supply_changed() directly from घातer_supply_रेजिस्टर()
 * would lead to execution of get_property() function provided by the driver
 * too early - beक्रमe the probe ends.
 *
 * Aव्योम that by रुकोing on parent's mutex.
 */
अटल व्योम घातer_supply_deferred_रेजिस्टर_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा घातer_supply *psy = container_of(work, काष्ठा घातer_supply,
						deferred_रेजिस्टर_work.work);

	अगर (psy->dev.parent) अणु
		जबतक (!mutex_trylock(&psy->dev.parent->mutex)) अणु
			अगर (psy->removing)
				वापस;
			msleep(10);
		पूर्ण
	पूर्ण

	घातer_supply_changed(psy);

	अगर (psy->dev.parent)
		mutex_unlock(&psy->dev.parent->mutex);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल पूर्णांक __घातer_supply_populate_supplied_from(काष्ठा device *dev,
						 व्योम *data)
अणु
	काष्ठा घातer_supply *psy = data;
	काष्ठा घातer_supply *epsy = dev_get_drvdata(dev);
	काष्ठा device_node *np;
	पूर्णांक i = 0;

	करो अणु
		np = of_parse_phandle(psy->of_node, "power-supplies", i++);
		अगर (!np)
			अवरोध;

		अगर (np == epsy->of_node) अणु
			dev_dbg(&psy->dev, "%s: Found supply : %s\n",
				psy->desc->name, epsy->desc->name);
			psy->supplied_from[i-1] = (अक्षर *)epsy->desc->name;
			psy->num_supplies++;
			of_node_put(np);
			अवरोध;
		पूर्ण
		of_node_put(np);
	पूर्ण जबतक (np);

	वापस 0;
पूर्ण

अटल पूर्णांक घातer_supply_populate_supplied_from(काष्ठा घातer_supply *psy)
अणु
	पूर्णांक error;

	error = class_क्रम_each_device(घातer_supply_class, शून्य, psy,
				      __घातer_supply_populate_supplied_from);

	dev_dbg(&psy->dev, "%s %d\n", __func__, error);

	वापस error;
पूर्ण

अटल पूर्णांक  __घातer_supply_find_supply_from_node(काष्ठा device *dev,
						 व्योम *data)
अणु
	काष्ठा device_node *np = data;
	काष्ठा घातer_supply *epsy = dev_get_drvdata(dev);

	/* वापसing non-zero अवरोधs out of class_क्रम_each_device loop */
	अगर (epsy->of_node == np)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक घातer_supply_find_supply_from_node(काष्ठा device_node *supply_node)
अणु
	पूर्णांक error;

	/*
	 * class_क्रम_each_device() either वापसs its own errors or values
	 * वापसed by __घातer_supply_find_supply_from_node().
	 *
	 * __घातer_supply_find_supply_from_node() will वापस 0 (no match)
	 * or 1 (match).
	 *
	 * We वापस 0 अगर class_क्रम_each_device() वापसed 1, -EPROBE_DEFER अगर
	 * it वापसed 0, or error as वापसed by it.
	 */
	error = class_क्रम_each_device(घातer_supply_class, शून्य, supply_node,
				       __घातer_supply_find_supply_from_node);

	वापस error ? (error == 1 ? 0 : error) : -EPROBE_DEFER;
पूर्ण

अटल पूर्णांक घातer_supply_check_supplies(काष्ठा घातer_supply *psy)
अणु
	काष्ठा device_node *np;
	पूर्णांक cnt = 0;

	/* If there is alपढ़ोy a list honor it */
	अगर (psy->supplied_from && psy->num_supplies > 0)
		वापस 0;

	/* No device node found, nothing to करो */
	अगर (!psy->of_node)
		वापस 0;

	करो अणु
		पूर्णांक ret;

		np = of_parse_phandle(psy->of_node, "power-supplies", cnt++);
		अगर (!np)
			अवरोध;

		ret = घातer_supply_find_supply_from_node(np);
		of_node_put(np);

		अगर (ret) अणु
			dev_dbg(&psy->dev, "Failed to find supply!\n");
			वापस ret;
		पूर्ण
	पूर्ण जबतक (np);

	/* Missing valid "power-supplies" entries */
	अगर (cnt == 1)
		वापस 0;

	/* All supplies found, allocate अक्षर ** array क्रम filling */
	psy->supplied_from = devm_kzalloc(&psy->dev, माप(psy->supplied_from),
					  GFP_KERNEL);
	अगर (!psy->supplied_from)
		वापस -ENOMEM;

	*psy->supplied_from = devm_kसुस्मृति(&psy->dev,
					   cnt - 1, माप(अक्षर *),
					   GFP_KERNEL);
	अगर (!*psy->supplied_from)
		वापस -ENOMEM;

	वापस घातer_supply_populate_supplied_from(psy);
पूर्ण
#अन्यथा
अटल पूर्णांक घातer_supply_check_supplies(काष्ठा घातer_supply *psy)
अणु
	पूर्णांक nval, ret;

	अगर (!psy->dev.parent)
		वापस 0;

	nval = device_property_पढ़ो_string_array(psy->dev.parent,
						 "supplied-from", शून्य, 0);
	अगर (nval <= 0)
		वापस 0;

	psy->supplied_from = devm_kदो_स्मृति_array(&psy->dev, nval,
						माप(अक्षर *), GFP_KERNEL);
	अगर (!psy->supplied_from)
		वापस -ENOMEM;

	ret = device_property_पढ़ो_string_array(psy->dev.parent,
		"supplied-from", (स्थिर अक्षर **)psy->supplied_from, nval);
	अगर (ret < 0)
		वापस ret;

	psy->num_supplies = nval;

	वापस 0;
पूर्ण
#पूर्ण_अगर

काष्ठा psy_am_i_supplied_data अणु
	काष्ठा घातer_supply *psy;
	अचिन्हित पूर्णांक count;
पूर्ण;

अटल पूर्णांक __घातer_supply_am_i_supplied(काष्ठा device *dev, व्योम *_data)
अणु
	जोड़ घातer_supply_propval ret = अणु0,पूर्ण;
	काष्ठा घातer_supply *epsy = dev_get_drvdata(dev);
	काष्ठा psy_am_i_supplied_data *data = _data;

	अगर (__घातer_supply_is_supplied_by(epsy, data->psy)) अणु
		data->count++;
		अगर (!epsy->desc->get_property(epsy, POWER_SUPPLY_PROP_ONLINE,
					&ret))
			वापस ret.पूर्णांकval;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक घातer_supply_am_i_supplied(काष्ठा घातer_supply *psy)
अणु
	काष्ठा psy_am_i_supplied_data data = अणु psy, 0 पूर्ण;
	पूर्णांक error;

	error = class_क्रम_each_device(घातer_supply_class, शून्य, &data,
				      __घातer_supply_am_i_supplied);

	dev_dbg(&psy->dev, "%s count %u err %d\n", __func__, data.count, error);

	अगर (data.count == 0)
		वापस -ENODEV;

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_am_i_supplied);

अटल पूर्णांक __घातer_supply_is_प्रणाली_supplied(काष्ठा device *dev, व्योम *data)
अणु
	जोड़ घातer_supply_propval ret = अणु0,पूर्ण;
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक *count = data;

	(*count)++;
	अगर (psy->desc->type != POWER_SUPPLY_TYPE_BATTERY)
		अगर (!psy->desc->get_property(psy, POWER_SUPPLY_PROP_ONLINE,
					&ret))
			वापस ret.पूर्णांकval;

	वापस 0;
पूर्ण

पूर्णांक घातer_supply_is_प्रणाली_supplied(व्योम)
अणु
	पूर्णांक error;
	अचिन्हित पूर्णांक count = 0;

	error = class_क्रम_each_device(घातer_supply_class, शून्य, &count,
				      __घातer_supply_is_प्रणाली_supplied);

	/*
	 * If no घातer class device was found at all, most probably we are
	 * running on a desktop प्रणाली, so assume we are on मुख्यs घातer.
	 */
	अगर (count == 0)
		वापस 1;

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_is_प्रणाली_supplied);

अटल पूर्णांक __घातer_supply_get_supplier_max_current(काष्ठा device *dev,
						   व्योम *data)
अणु
	जोड़ घातer_supply_propval ret = अणु0,पूर्ण;
	काष्ठा घातer_supply *epsy = dev_get_drvdata(dev);
	काष्ठा घातer_supply *psy = data;

	अगर (__घातer_supply_is_supplied_by(epsy, psy))
		अगर (!epsy->desc->get_property(epsy,
					      POWER_SUPPLY_PROP_CURRENT_MAX,
					      &ret))
			वापस ret.पूर्णांकval;

	वापस 0;
पूर्ण

पूर्णांक घातer_supply_set_input_current_limit_from_supplier(काष्ठा घातer_supply *psy)
अणु
	जोड़ घातer_supply_propval val = अणु0,पूर्ण;
	पूर्णांक curr;

	अगर (!psy->desc->set_property)
		वापस -EINVAL;

	/*
	 * This function is not पूर्णांकended क्रम use with a supply with multiple
	 * suppliers, we simply pick the first supply to report a non 0
	 * max-current.
	 */
	curr = class_क्रम_each_device(घातer_supply_class, शून्य, psy,
				      __घातer_supply_get_supplier_max_current);
	अगर (curr <= 0)
		वापस (curr == 0) ? -ENODEV : curr;

	val.पूर्णांकval = curr;

	वापस psy->desc->set_property(psy,
				POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT, &val);
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_set_input_current_limit_from_supplier);

पूर्णांक घातer_supply_set_battery_अक्षरged(काष्ठा घातer_supply *psy)
अणु
	अगर (atomic_पढ़ो(&psy->use_cnt) >= 0 &&
			psy->desc->type == POWER_SUPPLY_TYPE_BATTERY &&
			psy->desc->set_अक्षरged) अणु
		psy->desc->set_अक्षरged(psy);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_set_battery_अक्षरged);

अटल पूर्णांक घातer_supply_match_device_by_name(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	स्थिर अक्षर *name = data;
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);

	वापस म_भेद(psy->desc->name, name) == 0;
पूर्ण

/**
 * घातer_supply_get_by_name() - Search क्रम a घातer supply and वापसs its ref
 * @name: Power supply name to fetch
 *
 * If घातer supply was found, it increases reference count क्रम the
 * पूर्णांकernal घातer supply's device. The user should घातer_supply_put()
 * after usage.
 *
 * Return: On success वापसs a reference to a घातer supply with
 * matching name equals to @name, a शून्य otherwise.
 */
काष्ठा घातer_supply *घातer_supply_get_by_name(स्थिर अक्षर *name)
अणु
	काष्ठा घातer_supply *psy = शून्य;
	काष्ठा device *dev = class_find_device(घातer_supply_class, शून्य, name,
					घातer_supply_match_device_by_name);

	अगर (dev) अणु
		psy = dev_get_drvdata(dev);
		atomic_inc(&psy->use_cnt);
	पूर्ण

	वापस psy;
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_get_by_name);

/**
 * घातer_supply_put() - Drop reference obtained with घातer_supply_get_by_name
 * @psy: Reference to put
 *
 * The reference to घातer supply should be put beक्रमe unरेजिस्टरing
 * the घातer supply.
 */
व्योम घातer_supply_put(काष्ठा घातer_supply *psy)
अणु
	might_sleep();

	atomic_dec(&psy->use_cnt);
	put_device(&psy->dev);
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_put);

#अगर_घोषित CONFIG_OF
अटल पूर्णांक घातer_supply_match_device_node(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	वापस dev->parent && dev->parent->of_node == data;
पूर्ण

/**
 * घातer_supply_get_by_phandle() - Search क्रम a घातer supply and वापसs its ref
 * @np: Poपूर्णांकer to device node holding phandle property
 * @property: Name of property holding a घातer supply name
 *
 * If घातer supply was found, it increases reference count क्रम the
 * पूर्णांकernal घातer supply's device. The user should घातer_supply_put()
 * after usage.
 *
 * Return: On success वापसs a reference to a घातer supply with
 * matching name equals to value under @property, शून्य or ERR_PTR otherwise.
 */
काष्ठा घातer_supply *घातer_supply_get_by_phandle(काष्ठा device_node *np,
							स्थिर अक्षर *property)
अणु
	काष्ठा device_node *घातer_supply_np;
	काष्ठा घातer_supply *psy = शून्य;
	काष्ठा device *dev;

	घातer_supply_np = of_parse_phandle(np, property, 0);
	अगर (!घातer_supply_np)
		वापस ERR_PTR(-ENODEV);

	dev = class_find_device(घातer_supply_class, शून्य, घातer_supply_np,
						घातer_supply_match_device_node);

	of_node_put(घातer_supply_np);

	अगर (dev) अणु
		psy = dev_get_drvdata(dev);
		atomic_inc(&psy->use_cnt);
	पूर्ण

	वापस psy;
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_get_by_phandle);

अटल व्योम devm_घातer_supply_put(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा घातer_supply **psy = res;

	घातer_supply_put(*psy);
पूर्ण

/**
 * devm_घातer_supply_get_by_phandle() - Resource managed version of
 *  घातer_supply_get_by_phandle()
 * @dev: Poपूर्णांकer to device holding phandle property
 * @property: Name of property holding a घातer supply phandle
 *
 * Return: On success वापसs a reference to a घातer supply with
 * matching name equals to value under @property, शून्य or ERR_PTR otherwise.
 */
काष्ठा घातer_supply *devm_घातer_supply_get_by_phandle(काष्ठा device *dev,
						      स्थिर अक्षर *property)
अणु
	काष्ठा घातer_supply **ptr, *psy;

	अगर (!dev->of_node)
		वापस ERR_PTR(-ENODEV);

	ptr = devres_alloc(devm_घातer_supply_put, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	psy = घातer_supply_get_by_phandle(dev->of_node, property);
	अगर (IS_ERR_OR_शून्य(psy)) अणु
		devres_मुक्त(ptr);
	पूर्ण अन्यथा अणु
		*ptr = psy;
		devres_add(dev, ptr);
	पूर्ण
	वापस psy;
पूर्ण
EXPORT_SYMBOL_GPL(devm_घातer_supply_get_by_phandle);
#पूर्ण_अगर /* CONFIG_OF */

पूर्णांक घातer_supply_get_battery_info(काष्ठा घातer_supply *psy,
				  काष्ठा घातer_supply_battery_info *info)
अणु
	काष्ठा घातer_supply_resistance_temp_table *resist_table;
	काष्ठा device_node *battery_np;
	स्थिर अक्षर *value;
	पूर्णांक err, len, index;
	स्थिर __be32 *list;

	info->energy_full_design_uwh         = -EINVAL;
	info->अक्षरge_full_design_uah         = -EINVAL;
	info->voltage_min_design_uv          = -EINVAL;
	info->voltage_max_design_uv          = -EINVAL;
	info->preअक्षरge_current_ua           = -EINVAL;
	info->अक्षरge_term_current_ua         = -EINVAL;
	info->स्थिरant_अक्षरge_current_max_ua = -EINVAL;
	info->स्थिरant_अक्षरge_voltage_max_uv = -EINVAL;
	info->temp_ambient_alert_min         = पूर्णांक_न्यून;
	info->temp_ambient_alert_max         = पूर्णांक_उच्च;
	info->temp_alert_min                 = पूर्णांक_न्यून;
	info->temp_alert_max                 = पूर्णांक_उच्च;
	info->temp_min                       = पूर्णांक_न्यून;
	info->temp_max                       = पूर्णांक_उच्च;
	info->factory_पूर्णांकernal_resistance_uohm  = -EINVAL;
	info->resist_table = शून्य;

	क्रम (index = 0; index < POWER_SUPPLY_OCV_TEMP_MAX; index++) अणु
		info->ocv_table[index]       = शून्य;
		info->ocv_temp[index]        = -EINVAL;
		info->ocv_table_size[index]  = -EINVAL;
	पूर्ण

	अगर (!psy->of_node) अणु
		dev_warn(&psy->dev, "%s currently only supports devicetree\n",
			 __func__);
		वापस -ENXIO;
	पूर्ण

	battery_np = of_parse_phandle(psy->of_node, "monitored-battery", 0);
	अगर (!battery_np)
		वापस -ENODEV;

	err = of_property_पढ़ो_string(battery_np, "compatible", &value);
	अगर (err)
		जाओ out_put_node;

	अगर (म_भेद("simple-battery", value)) अणु
		err = -ENODEV;
		जाओ out_put_node;
	पूर्ण

	/* The property and field names below must correspond to elements
	 * in क्रमागत घातer_supply_property. For reasoning, see
	 * Documentation/घातer/घातer_supply_class.rst.
	 */

	of_property_पढ़ो_u32(battery_np, "energy-full-design-microwatt-hours",
			     &info->energy_full_design_uwh);
	of_property_पढ़ो_u32(battery_np, "charge-full-design-microamp-hours",
			     &info->अक्षरge_full_design_uah);
	of_property_पढ़ो_u32(battery_np, "voltage-min-design-microvolt",
			     &info->voltage_min_design_uv);
	of_property_पढ़ो_u32(battery_np, "voltage-max-design-microvolt",
			     &info->voltage_max_design_uv);
	of_property_पढ़ो_u32(battery_np, "trickle-charge-current-microamp",
			     &info->trickleअक्षरge_current_ua);
	of_property_पढ़ो_u32(battery_np, "precharge-current-microamp",
			     &info->preअक्षरge_current_ua);
	of_property_पढ़ो_u32(battery_np, "precharge-upper-limit-microvolt",
			     &info->preअक्षरge_voltage_max_uv);
	of_property_पढ़ो_u32(battery_np, "charge-term-current-microamp",
			     &info->अक्षरge_term_current_ua);
	of_property_पढ़ो_u32(battery_np, "re-charge-voltage-microvolt",
			     &info->अक्षरge_restart_voltage_uv);
	of_property_पढ़ो_u32(battery_np, "over-voltage-threshold-microvolt",
			     &info->overvoltage_limit_uv);
	of_property_पढ़ो_u32(battery_np, "constant-charge-current-max-microamp",
			     &info->स्थिरant_अक्षरge_current_max_ua);
	of_property_पढ़ो_u32(battery_np, "constant-charge-voltage-max-microvolt",
			     &info->स्थिरant_अक्षरge_voltage_max_uv);
	of_property_पढ़ो_u32(battery_np, "factory-internal-resistance-micro-ohms",
			     &info->factory_पूर्णांकernal_resistance_uohm);

	of_property_पढ़ो_u32_index(battery_np, "ambient-celsius",
				   0, &info->temp_ambient_alert_min);
	of_property_पढ़ो_u32_index(battery_np, "ambient-celsius",
				   1, &info->temp_ambient_alert_max);
	of_property_पढ़ो_u32_index(battery_np, "alert-celsius",
				   0, &info->temp_alert_min);
	of_property_पढ़ो_u32_index(battery_np, "alert-celsius",
				   1, &info->temp_alert_max);
	of_property_पढ़ो_u32_index(battery_np, "operating-range-celsius",
				   0, &info->temp_min);
	of_property_पढ़ो_u32_index(battery_np, "operating-range-celsius",
				   1, &info->temp_max);

	len = of_property_count_u32_elems(battery_np, "ocv-capacity-celsius");
	अगर (len < 0 && len != -EINVAL) अणु
		err = len;
		जाओ out_put_node;
	पूर्ण अन्यथा अगर (len > POWER_SUPPLY_OCV_TEMP_MAX) अणु
		dev_err(&psy->dev, "Too many temperature values\n");
		err = -EINVAL;
		जाओ out_put_node;
	पूर्ण अन्यथा अगर (len > 0) अणु
		of_property_पढ़ो_u32_array(battery_np, "ocv-capacity-celsius",
					   info->ocv_temp, len);
	पूर्ण

	क्रम (index = 0; index < len; index++) अणु
		काष्ठा घातer_supply_battery_ocv_table *table;
		अक्षर *propname;
		पूर्णांक i, tab_len, size;

		propname = kaप्र_लिखो(GFP_KERNEL, "ocv-capacity-table-%d", index);
		list = of_get_property(battery_np, propname, &size);
		अगर (!list || !size) अणु
			dev_err(&psy->dev, "failed to get %s\n", propname);
			kमुक्त(propname);
			घातer_supply_put_battery_info(psy, info);
			err = -EINVAL;
			जाओ out_put_node;
		पूर्ण

		kमुक्त(propname);
		tab_len = size / (2 * माप(__be32));
		info->ocv_table_size[index] = tab_len;

		table = info->ocv_table[index] =
			devm_kसुस्मृति(&psy->dev, tab_len, माप(*table), GFP_KERNEL);
		अगर (!info->ocv_table[index]) अणु
			घातer_supply_put_battery_info(psy, info);
			err = -ENOMEM;
			जाओ out_put_node;
		पूर्ण

		क्रम (i = 0; i < tab_len; i++) अणु
			table[i].ocv = be32_to_cpu(*list);
			list++;
			table[i].capacity = be32_to_cpu(*list);
			list++;
		पूर्ण
	पूर्ण

	list = of_get_property(battery_np, "resistance-temp-table", &len);
	अगर (!list || !len)
		जाओ out_put_node;

	info->resist_table_size = len / (2 * माप(__be32));
	resist_table = info->resist_table = devm_kसुस्मृति(&psy->dev,
							 info->resist_table_size,
							 माप(*resist_table),
							 GFP_KERNEL);
	अगर (!info->resist_table) अणु
		घातer_supply_put_battery_info(psy, info);
		err = -ENOMEM;
		जाओ out_put_node;
	पूर्ण

	क्रम (index = 0; index < info->resist_table_size; index++) अणु
		resist_table[index].temp = be32_to_cpu(*list++);
		resist_table[index].resistance = be32_to_cpu(*list++);
	पूर्ण

out_put_node:
	of_node_put(battery_np);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_get_battery_info);

व्योम घातer_supply_put_battery_info(काष्ठा घातer_supply *psy,
				   काष्ठा घातer_supply_battery_info *info)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < POWER_SUPPLY_OCV_TEMP_MAX; i++) अणु
		अगर (info->ocv_table[i])
			devm_kमुक्त(&psy->dev, info->ocv_table[i]);
	पूर्ण

	अगर (info->resist_table)
		devm_kमुक्त(&psy->dev, info->resist_table);
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_put_battery_info);

/**
 * घातer_supply_temp2resist_simple() - find the battery पूर्णांकernal resistance
 * percent
 * @table: Poपूर्णांकer to battery resistance temperature table
 * @table_len: The table length
 * @temp: Current temperature
 *
 * This helper function is used to look up battery पूर्णांकernal resistance percent
 * according to current temperature value from the resistance temperature table,
 * and the table must be ordered descending. Then the actual battery पूर्णांकernal
 * resistance = the ideal battery पूर्णांकernal resistance * percent / 100.
 *
 * Return: the battery पूर्णांकernal resistance percent
 */
पूर्णांक घातer_supply_temp2resist_simple(काष्ठा घातer_supply_resistance_temp_table *table,
				    पूर्णांक table_len, पूर्णांक temp)
अणु
	पूर्णांक i, resist;

	क्रम (i = 0; i < table_len; i++)
		अगर (temp > table[i].temp)
			अवरोध;

	अगर (i > 0 && i < table_len) अणु
		पूर्णांक पंचांगp;

		पंचांगp = (table[i - 1].resistance - table[i].resistance) *
			(temp - table[i].temp);
		पंचांगp /= table[i - 1].temp - table[i].temp;
		resist = पंचांगp + table[i].resistance;
	पूर्ण अन्यथा अगर (i == 0) अणु
		resist = table[0].resistance;
	पूर्ण अन्यथा अणु
		resist = table[table_len - 1].resistance;
	पूर्ण

	वापस resist;
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_temp2resist_simple);

/**
 * घातer_supply_ocv2cap_simple() - find the battery capacity
 * @table: Poपूर्णांकer to battery OCV lookup table
 * @table_len: OCV table length
 * @ocv: Current OCV value
 *
 * This helper function is used to look up battery capacity according to
 * current OCV value from one OCV table, and the OCV table must be ordered
 * descending.
 *
 * Return: the battery capacity.
 */
पूर्णांक घातer_supply_ocv2cap_simple(काष्ठा घातer_supply_battery_ocv_table *table,
				पूर्णांक table_len, पूर्णांक ocv)
अणु
	पूर्णांक i, cap, पंचांगp;

	क्रम (i = 0; i < table_len; i++)
		अगर (ocv > table[i].ocv)
			अवरोध;

	अगर (i > 0 && i < table_len) अणु
		पंचांगp = (table[i - 1].capacity - table[i].capacity) *
			(ocv - table[i].ocv);
		पंचांगp /= table[i - 1].ocv - table[i].ocv;
		cap = पंचांगp + table[i].capacity;
	पूर्ण अन्यथा अगर (i == 0) अणु
		cap = table[0].capacity;
	पूर्ण अन्यथा अणु
		cap = table[table_len - 1].capacity;
	पूर्ण

	वापस cap;
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_ocv2cap_simple);

काष्ठा घातer_supply_battery_ocv_table *
घातer_supply_find_ocv2cap_table(काष्ठा घातer_supply_battery_info *info,
				पूर्णांक temp, पूर्णांक *table_len)
अणु
	पूर्णांक best_temp_dअगरf = पूर्णांक_उच्च, temp_dअगरf;
	u8 i, best_index = 0;

	अगर (!info->ocv_table[0])
		वापस शून्य;

	क्रम (i = 0; i < POWER_SUPPLY_OCV_TEMP_MAX; i++) अणु
		temp_dअगरf = असल(info->ocv_temp[i] - temp);

		अगर (temp_dअगरf < best_temp_dअगरf) अणु
			best_temp_dअगरf = temp_dअगरf;
			best_index = i;
		पूर्ण
	पूर्ण

	*table_len = info->ocv_table_size[best_index];
	वापस info->ocv_table[best_index];
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_find_ocv2cap_table);

पूर्णांक घातer_supply_batinfo_ocv2cap(काष्ठा घातer_supply_battery_info *info,
				 पूर्णांक ocv, पूर्णांक temp)
अणु
	काष्ठा घातer_supply_battery_ocv_table *table;
	पूर्णांक table_len;

	table = घातer_supply_find_ocv2cap_table(info, temp, &table_len);
	अगर (!table)
		वापस -EINVAL;

	वापस घातer_supply_ocv2cap_simple(table, table_len, ocv);
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_batinfo_ocv2cap);

पूर्णांक घातer_supply_get_property(काष्ठा घातer_supply *psy,
			    क्रमागत घातer_supply_property psp,
			    जोड़ घातer_supply_propval *val)
अणु
	अगर (atomic_पढ़ो(&psy->use_cnt) <= 0) अणु
		अगर (!psy->initialized)
			वापस -EAGAIN;
		वापस -ENODEV;
	पूर्ण

	वापस psy->desc->get_property(psy, psp, val);
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_get_property);

पूर्णांक घातer_supply_set_property(काष्ठा घातer_supply *psy,
			    क्रमागत घातer_supply_property psp,
			    स्थिर जोड़ घातer_supply_propval *val)
अणु
	अगर (atomic_पढ़ो(&psy->use_cnt) <= 0 || !psy->desc->set_property)
		वापस -ENODEV;

	वापस psy->desc->set_property(psy, psp, val);
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_set_property);

पूर्णांक घातer_supply_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
					क्रमागत घातer_supply_property psp)
अणु
	अगर (atomic_पढ़ो(&psy->use_cnt) <= 0 ||
			!psy->desc->property_is_ग_लिखोable)
		वापस -ENODEV;

	वापस psy->desc->property_is_ग_लिखोable(psy, psp);
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_property_is_ग_लिखोable);

व्योम घातer_supply_बाह्यal_घातer_changed(काष्ठा घातer_supply *psy)
अणु
	अगर (atomic_पढ़ो(&psy->use_cnt) <= 0 ||
			!psy->desc->बाह्यal_घातer_changed)
		वापस;

	psy->desc->बाह्यal_घातer_changed(psy);
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_बाह्यal_घातer_changed);

पूर्णांक घातer_supply_घातers(काष्ठा घातer_supply *psy, काष्ठा device *dev)
अणु
	वापस sysfs_create_link(&psy->dev.kobj, &dev->kobj, "powers");
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_घातers);

अटल व्योम घातer_supply_dev_release(काष्ठा device *dev)
अणु
	काष्ठा घातer_supply *psy = to_घातer_supply(dev);
	dev_dbg(dev, "%s\n", __func__);
	kमुक्त(psy);
पूर्ण

पूर्णांक घातer_supply_reg_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_रेजिस्टर(&घातer_supply_notअगरier, nb);
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_reg_notअगरier);

व्योम घातer_supply_unreg_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	atomic_notअगरier_chain_unरेजिस्टर(&घातer_supply_notअगरier, nb);
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_unreg_notअगरier);

#अगर_घोषित CONFIG_THERMAL
अटल पूर्णांक घातer_supply_पढ़ो_temp(काष्ठा thermal_zone_device *tzd,
		पूर्णांक *temp)
अणु
	काष्ठा घातer_supply *psy;
	जोड़ घातer_supply_propval val;
	पूर्णांक ret;

	WARN_ON(tzd == शून्य);
	psy = tzd->devdata;
	ret = घातer_supply_get_property(psy, POWER_SUPPLY_PROP_TEMP, &val);
	अगर (ret)
		वापस ret;

	/* Convert tenths of degree Celsius to milli degree Celsius. */
	*temp = val.पूर्णांकval * 100;

	वापस ret;
पूर्ण

अटल काष्ठा thermal_zone_device_ops psy_tzd_ops = अणु
	.get_temp = घातer_supply_पढ़ो_temp,
पूर्ण;

अटल पूर्णांक psy_रेजिस्टर_thermal(काष्ठा घातer_supply *psy)
अणु
	पूर्णांक i, ret;

	अगर (psy->desc->no_thermal)
		वापस 0;

	/* Register battery zone device psy reports temperature */
	क्रम (i = 0; i < psy->desc->num_properties; i++) अणु
		अगर (psy->desc->properties[i] == POWER_SUPPLY_PROP_TEMP) अणु
			psy->tzd = thermal_zone_device_रेजिस्टर(psy->desc->name,
					0, 0, psy, &psy_tzd_ops, शून्य, 0, 0);
			अगर (IS_ERR(psy->tzd))
				वापस PTR_ERR(psy->tzd);
			ret = thermal_zone_device_enable(psy->tzd);
			अगर (ret)
				thermal_zone_device_unरेजिस्टर(psy->tzd);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम psy_unरेजिस्टर_thermal(काष्ठा घातer_supply *psy)
अणु
	अगर (IS_ERR_OR_शून्य(psy->tzd))
		वापस;
	thermal_zone_device_unरेजिस्टर(psy->tzd);
पूर्ण

/* thermal cooling device callbacks */
अटल पूर्णांक ps_get_max_अक्षरge_cntl_limit(काष्ठा thermal_cooling_device *tcd,
					अचिन्हित दीर्घ *state)
अणु
	काष्ठा घातer_supply *psy;
	जोड़ घातer_supply_propval val;
	पूर्णांक ret;

	psy = tcd->devdata;
	ret = घातer_supply_get_property(psy,
			POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT_MAX, &val);
	अगर (ret)
		वापस ret;

	*state = val.पूर्णांकval;

	वापस ret;
पूर्ण

अटल पूर्णांक ps_get_cur_अक्षरge_cntl_limit(काष्ठा thermal_cooling_device *tcd,
					अचिन्हित दीर्घ *state)
अणु
	काष्ठा घातer_supply *psy;
	जोड़ घातer_supply_propval val;
	पूर्णांक ret;

	psy = tcd->devdata;
	ret = घातer_supply_get_property(psy,
			POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT, &val);
	अगर (ret)
		वापस ret;

	*state = val.पूर्णांकval;

	वापस ret;
पूर्ण

अटल पूर्णांक ps_set_cur_अक्षरge_cntl_limit(काष्ठा thermal_cooling_device *tcd,
					अचिन्हित दीर्घ state)
अणु
	काष्ठा घातer_supply *psy;
	जोड़ घातer_supply_propval val;
	पूर्णांक ret;

	psy = tcd->devdata;
	val.पूर्णांकval = state;
	ret = psy->desc->set_property(psy,
		POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT, &val);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा thermal_cooling_device_ops psy_tcd_ops = अणु
	.get_max_state = ps_get_max_अक्षरge_cntl_limit,
	.get_cur_state = ps_get_cur_अक्षरge_cntl_limit,
	.set_cur_state = ps_set_cur_अक्षरge_cntl_limit,
पूर्ण;

अटल पूर्णांक psy_रेजिस्टर_cooler(काष्ठा घातer_supply *psy)
अणु
	पूर्णांक i;

	/* Register क्रम cooling device अगर psy can control अक्षरging */
	क्रम (i = 0; i < psy->desc->num_properties; i++) अणु
		अगर (psy->desc->properties[i] ==
				POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT) अणु
			psy->tcd = thermal_cooling_device_रेजिस्टर(
							(अक्षर *)psy->desc->name,
							psy, &psy_tcd_ops);
			वापस PTR_ERR_OR_ZERO(psy->tcd);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम psy_unरेजिस्टर_cooler(काष्ठा घातer_supply *psy)
अणु
	अगर (IS_ERR_OR_शून्य(psy->tcd))
		वापस;
	thermal_cooling_device_unरेजिस्टर(psy->tcd);
पूर्ण
#अन्यथा
अटल पूर्णांक psy_रेजिस्टर_thermal(काष्ठा घातer_supply *psy)
अणु
	वापस 0;
पूर्ण

अटल व्योम psy_unरेजिस्टर_thermal(काष्ठा घातer_supply *psy)
अणु
पूर्ण

अटल पूर्णांक psy_रेजिस्टर_cooler(काष्ठा घातer_supply *psy)
अणु
	वापस 0;
पूर्ण

अटल व्योम psy_unरेजिस्टर_cooler(काष्ठा घातer_supply *psy)
अणु
पूर्ण
#पूर्ण_अगर

अटल काष्ठा घातer_supply *__must_check
__घातer_supply_रेजिस्टर(काष्ठा device *parent,
				   स्थिर काष्ठा घातer_supply_desc *desc,
				   स्थिर काष्ठा घातer_supply_config *cfg,
				   bool ws)
अणु
	काष्ठा device *dev;
	काष्ठा घातer_supply *psy;
	पूर्णांक i, rc;

	अगर (!parent)
		pr_warn("%s: Expected proper parent device for '%s'\n",
			__func__, desc->name);

	अगर (!desc || !desc->name || !desc->properties || !desc->num_properties)
		वापस ERR_PTR(-EINVAL);

	क्रम (i = 0; i < desc->num_properties; ++i) अणु
		अगर ((desc->properties[i] == POWER_SUPPLY_PROP_USB_TYPE) &&
		    (!desc->usb_types || !desc->num_usb_types))
			वापस ERR_PTR(-EINVAL);
	पूर्ण

	psy = kzalloc(माप(*psy), GFP_KERNEL);
	अगर (!psy)
		वापस ERR_PTR(-ENOMEM);

	dev = &psy->dev;

	device_initialize(dev);

	dev->class = घातer_supply_class;
	dev->type = &घातer_supply_dev_type;
	dev->parent = parent;
	dev->release = घातer_supply_dev_release;
	dev_set_drvdata(dev, psy);
	psy->desc = desc;
	अगर (cfg) अणु
		dev->groups = cfg->attr_grp;
		psy->drv_data = cfg->drv_data;
		psy->of_node =
			cfg->fwnode ? to_of_node(cfg->fwnode) : cfg->of_node;
		psy->supplied_to = cfg->supplied_to;
		psy->num_supplicants = cfg->num_supplicants;
	पूर्ण

	rc = dev_set_name(dev, "%s", desc->name);
	अगर (rc)
		जाओ dev_set_name_failed;

	INIT_WORK(&psy->changed_work, घातer_supply_changed_work);
	INIT_DELAYED_WORK(&psy->deferred_रेजिस्टर_work,
			  घातer_supply_deferred_रेजिस्टर_work);

	rc = घातer_supply_check_supplies(psy);
	अगर (rc) अणु
		dev_dbg(dev, "Not all required supplies found, defer probe\n");
		जाओ check_supplies_failed;
	पूर्ण

	spin_lock_init(&psy->changed_lock);
	rc = device_add(dev);
	अगर (rc)
		जाओ device_add_failed;

	rc = device_init_wakeup(dev, ws);
	अगर (rc)
		जाओ wakeup_init_failed;

	rc = psy_रेजिस्टर_thermal(psy);
	अगर (rc)
		जाओ रेजिस्टर_thermal_failed;

	rc = psy_रेजिस्टर_cooler(psy);
	अगर (rc)
		जाओ रेजिस्टर_cooler_failed;

	rc = घातer_supply_create_triggers(psy);
	अगर (rc)
		जाओ create_triggers_failed;

	rc = घातer_supply_add_hwmon_sysfs(psy);
	अगर (rc)
		जाओ add_hwmon_sysfs_failed;

	/*
	 * Update use_cnt after any uevents (most notably from device_add()).
	 * We are here still during driver's probe but
	 * the घातer_supply_uevent() calls back driver's get_property
	 * method so:
	 * 1. Driver did not asचिन्हित the वापसed काष्ठा घातer_supply,
	 * 2. Driver could not finish initialization (anything in its probe
	 *    after calling घातer_supply_रेजिस्टर()).
	 */
	atomic_inc(&psy->use_cnt);
	psy->initialized = true;

	queue_delayed_work(प्रणाली_घातer_efficient_wq,
			   &psy->deferred_रेजिस्टर_work,
			   POWER_SUPPLY_DEFERRED_REGISTER_TIME);

	वापस psy;

add_hwmon_sysfs_failed:
	घातer_supply_हटाओ_triggers(psy);
create_triggers_failed:
	psy_unरेजिस्टर_cooler(psy);
रेजिस्टर_cooler_failed:
	psy_unरेजिस्टर_thermal(psy);
रेजिस्टर_thermal_failed:
	device_del(dev);
wakeup_init_failed:
device_add_failed:
check_supplies_failed:
dev_set_name_failed:
	put_device(dev);
	वापस ERR_PTR(rc);
पूर्ण

/**
 * घातer_supply_रेजिस्टर() - Register new घातer supply
 * @parent:	Device to be a parent of घातer supply's device, usually
 *		the device which probe function calls this
 * @desc:	Description of घातer supply, must be valid through whole
 *		lअगरeसमय of this घातer supply
 * @cfg:	Run-समय specअगरic configuration accessed during रेजिस्टरing,
 *		may be शून्य
 *
 * Return: A poपूर्णांकer to newly allocated घातer_supply on success
 * or ERR_PTR otherwise.
 * Use घातer_supply_unरेजिस्टर() on वापसed घातer_supply poपूर्णांकer to release
 * resources.
 */
काष्ठा घातer_supply *__must_check घातer_supply_रेजिस्टर(काष्ठा device *parent,
		स्थिर काष्ठा घातer_supply_desc *desc,
		स्थिर काष्ठा घातer_supply_config *cfg)
अणु
	वापस __घातer_supply_रेजिस्टर(parent, desc, cfg, true);
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_रेजिस्टर);

/**
 * घातer_supply_रेजिस्टर_no_ws() - Register new non-waking-source घातer supply
 * @parent:	Device to be a parent of घातer supply's device, usually
 *		the device which probe function calls this
 * @desc:	Description of घातer supply, must be valid through whole
 *		lअगरeसमय of this घातer supply
 * @cfg:	Run-समय specअगरic configuration accessed during रेजिस्टरing,
 *		may be शून्य
 *
 * Return: A poपूर्णांकer to newly allocated घातer_supply on success
 * or ERR_PTR otherwise.
 * Use घातer_supply_unरेजिस्टर() on वापसed घातer_supply poपूर्णांकer to release
 * resources.
 */
काष्ठा घातer_supply *__must_check
घातer_supply_रेजिस्टर_no_ws(काष्ठा device *parent,
		स्थिर काष्ठा घातer_supply_desc *desc,
		स्थिर काष्ठा घातer_supply_config *cfg)
अणु
	वापस __घातer_supply_रेजिस्टर(parent, desc, cfg, false);
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_रेजिस्टर_no_ws);

अटल व्योम devm_घातer_supply_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा घातer_supply **psy = res;

	घातer_supply_unरेजिस्टर(*psy);
पूर्ण

/**
 * devm_घातer_supply_रेजिस्टर() - Register managed घातer supply
 * @parent:	Device to be a parent of घातer supply's device, usually
 *		the device which probe function calls this
 * @desc:	Description of घातer supply, must be valid through whole
 *		lअगरeसमय of this घातer supply
 * @cfg:	Run-समय specअगरic configuration accessed during रेजिस्टरing,
 *		may be शून्य
 *
 * Return: A poपूर्णांकer to newly allocated घातer_supply on success
 * or ERR_PTR otherwise.
 * The वापसed घातer_supply poपूर्णांकer will be स्वतःmatically unरेजिस्टरed
 * on driver detach.
 */
काष्ठा घातer_supply *__must_check
devm_घातer_supply_रेजिस्टर(काष्ठा device *parent,
		स्थिर काष्ठा घातer_supply_desc *desc,
		स्थिर काष्ठा घातer_supply_config *cfg)
अणु
	काष्ठा घातer_supply **ptr, *psy;

	ptr = devres_alloc(devm_घातer_supply_release, माप(*ptr), GFP_KERNEL);

	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);
	psy = __घातer_supply_रेजिस्टर(parent, desc, cfg, true);
	अगर (IS_ERR(psy)) अणु
		devres_मुक्त(ptr);
	पूर्ण अन्यथा अणु
		*ptr = psy;
		devres_add(parent, ptr);
	पूर्ण
	वापस psy;
पूर्ण
EXPORT_SYMBOL_GPL(devm_घातer_supply_रेजिस्टर);

/**
 * devm_घातer_supply_रेजिस्टर_no_ws() - Register managed non-waking-source घातer supply
 * @parent:	Device to be a parent of घातer supply's device, usually
 *		the device which probe function calls this
 * @desc:	Description of घातer supply, must be valid through whole
 *		lअगरeसमय of this घातer supply
 * @cfg:	Run-समय specअगरic configuration accessed during रेजिस्टरing,
 *		may be शून्य
 *
 * Return: A poपूर्णांकer to newly allocated घातer_supply on success
 * or ERR_PTR otherwise.
 * The वापसed घातer_supply poपूर्णांकer will be स्वतःmatically unरेजिस्टरed
 * on driver detach.
 */
काष्ठा घातer_supply *__must_check
devm_घातer_supply_रेजिस्टर_no_ws(काष्ठा device *parent,
		स्थिर काष्ठा घातer_supply_desc *desc,
		स्थिर काष्ठा घातer_supply_config *cfg)
अणु
	काष्ठा घातer_supply **ptr, *psy;

	ptr = devres_alloc(devm_घातer_supply_release, माप(*ptr), GFP_KERNEL);

	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);
	psy = __घातer_supply_रेजिस्टर(parent, desc, cfg, false);
	अगर (IS_ERR(psy)) अणु
		devres_मुक्त(ptr);
	पूर्ण अन्यथा अणु
		*ptr = psy;
		devres_add(parent, ptr);
	पूर्ण
	वापस psy;
पूर्ण
EXPORT_SYMBOL_GPL(devm_घातer_supply_रेजिस्टर_no_ws);

/**
 * घातer_supply_unरेजिस्टर() - Remove this घातer supply from प्रणाली
 * @psy:	Poपूर्णांकer to घातer supply to unरेजिस्टर
 *
 * Remove this घातer supply from the प्रणाली. The resources of घातer supply
 * will be मुक्तd here or on last घातer_supply_put() call.
 */
व्योम घातer_supply_unरेजिस्टर(काष्ठा घातer_supply *psy)
अणु
	WARN_ON(atomic_dec_वापस(&psy->use_cnt));
	psy->removing = true;
	cancel_work_sync(&psy->changed_work);
	cancel_delayed_work_sync(&psy->deferred_रेजिस्टर_work);
	sysfs_हटाओ_link(&psy->dev.kobj, "powers");
	घातer_supply_हटाओ_hwmon_sysfs(psy);
	घातer_supply_हटाओ_triggers(psy);
	psy_unरेजिस्टर_cooler(psy);
	psy_unरेजिस्टर_thermal(psy);
	device_init_wakeup(&psy->dev, false);
	device_unरेजिस्टर(&psy->dev);
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_unरेजिस्टर);

व्योम *घातer_supply_get_drvdata(काष्ठा घातer_supply *psy)
अणु
	वापस psy->drv_data;
पूर्ण
EXPORT_SYMBOL_GPL(घातer_supply_get_drvdata);

अटल पूर्णांक __init घातer_supply_class_init(व्योम)
अणु
	घातer_supply_class = class_create(THIS_MODULE, "power_supply");

	अगर (IS_ERR(घातer_supply_class))
		वापस PTR_ERR(घातer_supply_class);

	घातer_supply_class->dev_uevent = घातer_supply_uevent;
	घातer_supply_init_attrs(&घातer_supply_dev_type);

	वापस 0;
पूर्ण

अटल व्योम __निकास घातer_supply_class_निकास(व्योम)
अणु
	class_destroy(घातer_supply_class);
पूर्ण

subsys_initcall(घातer_supply_class_init);
module_निकास(घातer_supply_class_निकास);

MODULE_DESCRIPTION("Universal power supply monitor class");
MODULE_AUTHOR("Ian Molton <spyro@f2s.com>, "
	      "Szabolcs Gyurko, "
	      "Anton Vorontsov <cbou@mail.ru>");
MODULE_LICENSE("GPL");
