<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// GPIO Aggregator
//
// Copyright (C) 2019-2020 Glider bv

#घोषणा DRV_NAME       "gpio-aggregator"
#घोषणा pr_fmt(fmt)	DRV_NAME ": " fmt

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/idr.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/overflow.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>


/*
 * GPIO Aggregator sysfs पूर्णांकerface
 */

काष्ठा gpio_aggregator अणु
	काष्ठा gpiod_lookup_table *lookups;
	काष्ठा platक्रमm_device *pdev;
	अक्षर args[];
पूर्ण;

अटल DEFINE_MUTEX(gpio_aggregator_lock);	/* protects idr */
अटल DEFINE_IDR(gpio_aggregator_idr);

अटल पूर्णांक aggr_add_gpio(काष्ठा gpio_aggregator *aggr, स्थिर अक्षर *key,
			 पूर्णांक hwnum, अचिन्हित पूर्णांक *n)
अणु
	काष्ठा gpiod_lookup_table *lookups;

	lookups = kपुनः_स्मृति(aggr->lookups, काष्ठा_size(lookups, table, *n + 2),
			   GFP_KERNEL);
	अगर (!lookups)
		वापस -ENOMEM;

	lookups->table[*n] = GPIO_LOOKUP_IDX(key, hwnum, शून्य, *n, 0);

	(*n)++;
	स_रखो(&lookups->table[*n], 0, माप(lookups->table[*n]));

	aggr->lookups = lookups;
	वापस 0;
पूर्ण

अटल पूर्णांक aggr_parse(काष्ठा gpio_aggregator *aggr)
अणु
	अक्षर *args = skip_spaces(aggr->args);
	अक्षर *name, *offsets, *p;
	अचिन्हित दीर्घ *biपंचांगap;
	अचिन्हित पूर्णांक i, n = 0;
	पूर्णांक error = 0;

	biपंचांगap = biपंचांगap_alloc(ARCH_NR_GPIOS, GFP_KERNEL);
	अगर (!biपंचांगap)
		वापस -ENOMEM;

	args = next_arg(args, &name, &p);
	जबतक (*args) अणु
		args = next_arg(args, &offsets, &p);

		p = get_options(offsets, 0, &error);
		अगर (error == 0 || *p) अणु
			/* Named GPIO line */
			error = aggr_add_gpio(aggr, name, U16_MAX, &n);
			अगर (error)
				जाओ मुक्त_biपंचांगap;

			name = offsets;
			जारी;
		पूर्ण

		/* GPIO chip + offset(s) */
		error = biपंचांगap_parselist(offsets, biपंचांगap, ARCH_NR_GPIOS);
		अगर (error) अणु
			pr_err("Cannot parse %s: %d\n", offsets, error);
			जाओ मुक्त_biपंचांगap;
		पूर्ण

		क्रम_each_set_bit(i, biपंचांगap, ARCH_NR_GPIOS) अणु
			error = aggr_add_gpio(aggr, name, i, &n);
			अगर (error)
				जाओ मुक्त_biपंचांगap;
		पूर्ण

		args = next_arg(args, &name, &p);
	पूर्ण

	अगर (!n) अणु
		pr_err("No GPIOs specified\n");
		error = -EINVAL;
	पूर्ण

मुक्त_biपंचांगap:
	biपंचांगap_मुक्त(biपंचांगap);
	वापस error;
पूर्ण

अटल sमाप_प्रकार new_device_store(काष्ठा device_driver *driver, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	काष्ठा gpio_aggregator *aggr;
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक res, id;

	/* kernfs guarantees string termination, so count + 1 is safe */
	aggr = kzalloc(माप(*aggr) + count + 1, GFP_KERNEL);
	अगर (!aggr)
		वापस -ENOMEM;

	स_नकल(aggr->args, buf, count + 1);

	aggr->lookups = kzalloc(काष्ठा_size(aggr->lookups, table, 1),
				GFP_KERNEL);
	अगर (!aggr->lookups) अणु
		res = -ENOMEM;
		जाओ मुक्त_ga;
	पूर्ण

	mutex_lock(&gpio_aggregator_lock);
	id = idr_alloc(&gpio_aggregator_idr, aggr, 0, 0, GFP_KERNEL);
	mutex_unlock(&gpio_aggregator_lock);

	अगर (id < 0) अणु
		res = id;
		जाओ मुक्त_table;
	पूर्ण

	aggr->lookups->dev_id = kaप्र_लिखो(GFP_KERNEL, "%s.%d", DRV_NAME, id);
	अगर (!aggr->lookups->dev_id) अणु
		res = -ENOMEM;
		जाओ हटाओ_idr;
	पूर्ण

	res = aggr_parse(aggr);
	अगर (res)
		जाओ मुक्त_dev_id;

	gpiod_add_lookup_table(aggr->lookups);

	pdev = platक्रमm_device_रेजिस्टर_simple(DRV_NAME, id, शून्य, 0);
	अगर (IS_ERR(pdev)) अणु
		res = PTR_ERR(pdev);
		जाओ हटाओ_table;
	पूर्ण

	aggr->pdev = pdev;
	वापस count;

हटाओ_table:
	gpiod_हटाओ_lookup_table(aggr->lookups);
मुक्त_dev_id:
	kमुक्त(aggr->lookups->dev_id);
हटाओ_idr:
	mutex_lock(&gpio_aggregator_lock);
	idr_हटाओ(&gpio_aggregator_idr, id);
	mutex_unlock(&gpio_aggregator_lock);
मुक्त_table:
	kमुक्त(aggr->lookups);
मुक्त_ga:
	kमुक्त(aggr);
	वापस res;
पूर्ण

अटल DRIVER_ATTR_WO(new_device);

अटल व्योम gpio_aggregator_मुक्त(काष्ठा gpio_aggregator *aggr)
अणु
	platक्रमm_device_unरेजिस्टर(aggr->pdev);
	gpiod_हटाओ_lookup_table(aggr->lookups);
	kमुक्त(aggr->lookups->dev_id);
	kमुक्त(aggr->lookups);
	kमुक्त(aggr);
पूर्ण

अटल sमाप_प्रकार delete_device_store(काष्ठा device_driver *driver,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा gpio_aggregator *aggr;
	अचिन्हित पूर्णांक id;
	पूर्णांक error;

	अगर (!str_has_prefix(buf, DRV_NAME "."))
		वापस -EINVAL;

	error = kstrtouपूर्णांक(buf + म_माप(DRV_NAME "."), 10, &id);
	अगर (error)
		वापस error;

	mutex_lock(&gpio_aggregator_lock);
	aggr = idr_हटाओ(&gpio_aggregator_idr, id);
	mutex_unlock(&gpio_aggregator_lock);
	अगर (!aggr)
		वापस -ENOENT;

	gpio_aggregator_मुक्त(aggr);
	वापस count;
पूर्ण
अटल DRIVER_ATTR_WO(delete_device);

अटल काष्ठा attribute *gpio_aggregator_attrs[] = अणु
	&driver_attr_new_device.attr,
	&driver_attr_delete_device.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(gpio_aggregator);

अटल पूर्णांक __निकास gpio_aggregator_idr_हटाओ(पूर्णांक id, व्योम *p, व्योम *data)
अणु
	gpio_aggregator_मुक्त(p);
	वापस 0;
पूर्ण

अटल व्योम __निकास gpio_aggregator_हटाओ_all(व्योम)
अणु
	mutex_lock(&gpio_aggregator_lock);
	idr_क्रम_each(&gpio_aggregator_idr, gpio_aggregator_idr_हटाओ, शून्य);
	idr_destroy(&gpio_aggregator_idr);
	mutex_unlock(&gpio_aggregator_lock);
पूर्ण


/*
 *  GPIO Forwarder
 */

काष्ठा gpiochip_fwd अणु
	काष्ठा gpio_chip chip;
	काष्ठा gpio_desc **descs;
	जोड़ अणु
		काष्ठा mutex mlock;	/* protects पंचांगp[] अगर can_sleep */
		spinlock_t slock;	/* protects पंचांगp[] अगर !can_sleep */
	पूर्ण;
	अचिन्हित दीर्घ पंचांगp[];		/* values and descs क्रम multiple ops */
पूर्ण;

अटल पूर्णांक gpio_fwd_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gpiochip_fwd *fwd = gpiochip_get_data(chip);

	वापस gpiod_get_direction(fwd->descs[offset]);
पूर्ण

अटल पूर्णांक gpio_fwd_direction_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gpiochip_fwd *fwd = gpiochip_get_data(chip);

	वापस gpiod_direction_input(fwd->descs[offset]);
पूर्ण

अटल पूर्णांक gpio_fwd_direction_output(काष्ठा gpio_chip *chip,
				     अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा gpiochip_fwd *fwd = gpiochip_get_data(chip);

	वापस gpiod_direction_output(fwd->descs[offset], value);
पूर्ण

अटल पूर्णांक gpio_fwd_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gpiochip_fwd *fwd = gpiochip_get_data(chip);

	वापस gpiod_get_value(fwd->descs[offset]);
पूर्ण

अटल पूर्णांक gpio_fwd_get_multiple(काष्ठा gpiochip_fwd *fwd, अचिन्हित दीर्घ *mask,
				 अचिन्हित दीर्घ *bits)
अणु
	काष्ठा gpio_desc **descs;
	अचिन्हित दीर्घ *values;
	अचिन्हित पूर्णांक i, j = 0;
	पूर्णांक error;

	/* Both values biपंचांगap and desc poपूर्णांकers are stored in पंचांगp[] */
	values = &fwd->पंचांगp[0];
	descs = (व्योम *)&fwd->पंचांगp[BITS_TO_LONGS(fwd->chip.ngpio)];

	biपंचांगap_clear(values, 0, fwd->chip.ngpio);
	क्रम_each_set_bit(i, mask, fwd->chip.ngpio)
		descs[j++] = fwd->descs[i];

	error = gpiod_get_array_value(j, descs, शून्य, values);
	अगर (error)
		वापस error;

	j = 0;
	क्रम_each_set_bit(i, mask, fwd->chip.ngpio)
		__assign_bit(i, bits, test_bit(j++, values));

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_fwd_get_multiple_locked(काष्ठा gpio_chip *chip,
					अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	काष्ठा gpiochip_fwd *fwd = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	पूर्णांक error;

	अगर (chip->can_sleep) अणु
		mutex_lock(&fwd->mlock);
		error = gpio_fwd_get_multiple(fwd, mask, bits);
		mutex_unlock(&fwd->mlock);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&fwd->slock, flags);
		error = gpio_fwd_get_multiple(fwd, mask, bits);
		spin_unlock_irqrestore(&fwd->slock, flags);
	पूर्ण

	वापस error;
पूर्ण

अटल व्योम gpio_fwd_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा gpiochip_fwd *fwd = gpiochip_get_data(chip);

	gpiod_set_value(fwd->descs[offset], value);
पूर्ण

अटल व्योम gpio_fwd_set_multiple(काष्ठा gpiochip_fwd *fwd, अचिन्हित दीर्घ *mask,
				  अचिन्हित दीर्घ *bits)
अणु
	काष्ठा gpio_desc **descs;
	अचिन्हित दीर्घ *values;
	अचिन्हित पूर्णांक i, j = 0;

	/* Both values biपंचांगap and desc poपूर्णांकers are stored in पंचांगp[] */
	values = &fwd->पंचांगp[0];
	descs = (व्योम *)&fwd->पंचांगp[BITS_TO_LONGS(fwd->chip.ngpio)];

	क्रम_each_set_bit(i, mask, fwd->chip.ngpio) अणु
		__assign_bit(j, values, test_bit(i, bits));
		descs[j++] = fwd->descs[i];
	पूर्ण

	gpiod_set_array_value(j, descs, शून्य, values);
पूर्ण

अटल व्योम gpio_fwd_set_multiple_locked(काष्ठा gpio_chip *chip,
					 अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	काष्ठा gpiochip_fwd *fwd = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;

	अगर (chip->can_sleep) अणु
		mutex_lock(&fwd->mlock);
		gpio_fwd_set_multiple(fwd, mask, bits);
		mutex_unlock(&fwd->mlock);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&fwd->slock, flags);
		gpio_fwd_set_multiple(fwd, mask, bits);
		spin_unlock_irqrestore(&fwd->slock, flags);
	पूर्ण
पूर्ण

अटल पूर्णांक gpio_fwd_set_config(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			       अचिन्हित दीर्घ config)
अणु
	काष्ठा gpiochip_fwd *fwd = gpiochip_get_data(chip);

	वापस gpiod_set_config(fwd->descs[offset], config);
पूर्ण

/**
 * gpiochip_fwd_create() - Create a new GPIO क्रमwarder
 * @dev: Parent device poपूर्णांकer
 * @ngpios: Number of GPIOs in the क्रमwarder.
 * @descs: Array containing the GPIO descriptors to क्रमward to.
 *         This array must contain @ngpios entries, and must not be deallocated
 *         beक्रमe the क्रमwarder has been destroyed again.
 *
 * This function creates a new gpiochip, which क्रमwards all GPIO operations to
 * the passed GPIO descriptors.
 *
 * Return: An opaque object poपूर्णांकer, or an ERR_PTR()-encoded negative error
 *         code on failure.
 */
अटल काष्ठा gpiochip_fwd *gpiochip_fwd_create(काष्ठा device *dev,
						अचिन्हित पूर्णांक ngpios,
						काष्ठा gpio_desc *descs[])
अणु
	स्थिर अक्षर *label = dev_name(dev);
	काष्ठा gpiochip_fwd *fwd;
	काष्ठा gpio_chip *chip;
	अचिन्हित पूर्णांक i;
	पूर्णांक error;

	fwd = devm_kzalloc(dev, काष्ठा_size(fwd, पंचांगp,
			   BITS_TO_LONGS(ngpios) + ngpios), GFP_KERNEL);
	अगर (!fwd)
		वापस ERR_PTR(-ENOMEM);

	chip = &fwd->chip;

	/*
	 * If any of the GPIO lines are sleeping, then the entire क्रमwarder
	 * will be sleeping.
	 * If any of the chips support .set_config(), then the क्रमwarder will
	 * support setting configs.
	 */
	क्रम (i = 0; i < ngpios; i++) अणु
		काष्ठा gpio_chip *parent = gpiod_to_chip(descs[i]);

		dev_dbg(dev, "%u => gpio-%d\n", i, desc_to_gpio(descs[i]));

		अगर (gpiod_cansleep(descs[i]))
			chip->can_sleep = true;
		अगर (parent && parent->set_config)
			chip->set_config = gpio_fwd_set_config;
	पूर्ण

	chip->label = label;
	chip->parent = dev;
	chip->owner = THIS_MODULE;
	chip->get_direction = gpio_fwd_get_direction;
	chip->direction_input = gpio_fwd_direction_input;
	chip->direction_output = gpio_fwd_direction_output;
	chip->get = gpio_fwd_get;
	chip->get_multiple = gpio_fwd_get_multiple_locked;
	chip->set = gpio_fwd_set;
	chip->set_multiple = gpio_fwd_set_multiple_locked;
	chip->base = -1;
	chip->ngpio = ngpios;
	fwd->descs = descs;

	अगर (chip->can_sleep)
		mutex_init(&fwd->mlock);
	अन्यथा
		spin_lock_init(&fwd->slock);

	error = devm_gpiochip_add_data(dev, chip, fwd);
	अगर (error)
		वापस ERR_PTR(error);

	वापस fwd;
पूर्ण


/*
 *  GPIO Aggregator platक्रमm device
 */

अटल पूर्णांक gpio_aggregator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा gpio_desc **descs;
	काष्ठा gpiochip_fwd *fwd;
	पूर्णांक i, n;

	n = gpiod_count(dev, शून्य);
	अगर (n < 0)
		वापस n;

	descs = devm_kदो_स्मृति_array(dev, n, माप(*descs), GFP_KERNEL);
	अगर (!descs)
		वापस -ENOMEM;

	क्रम (i = 0; i < n; i++) अणु
		descs[i] = devm_gpiod_get_index(dev, शून्य, i, GPIOD_ASIS);
		अगर (IS_ERR(descs[i]))
			वापस PTR_ERR(descs[i]);
	पूर्ण

	fwd = gpiochip_fwd_create(dev, n, descs);
	अगर (IS_ERR(fwd))
		वापस PTR_ERR(fwd);

	platक्रमm_set_drvdata(pdev, fwd);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id gpio_aggregator_dt_ids[] = अणु
	/*
	 * Add GPIO-operated devices controlled from userspace below,
	 * or use "driver_override" in sysfs
	 */
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gpio_aggregator_dt_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver gpio_aggregator_driver = अणु
	.probe = gpio_aggregator_probe,
	.driver = अणु
		.name = DRV_NAME,
		.groups = gpio_aggregator_groups,
		.of_match_table = of_match_ptr(gpio_aggregator_dt_ids),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init gpio_aggregator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&gpio_aggregator_driver);
पूर्ण
module_init(gpio_aggregator_init);

अटल व्योम __निकास gpio_aggregator_निकास(व्योम)
अणु
	gpio_aggregator_हटाओ_all();
	platक्रमm_driver_unरेजिस्टर(&gpio_aggregator_driver);
पूर्ण
module_निकास(gpio_aggregator_निकास);

MODULE_AUTHOR("Geert Uytterhoeven <geert+renesas@glider.be>");
MODULE_DESCRIPTION("GPIO Aggregator");
MODULE_LICENSE("GPL v2");
