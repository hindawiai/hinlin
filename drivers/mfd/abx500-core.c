<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007-2010 ST-Ericsson
 * Register access functions क्रम the ABX500 Mixed Signal IC family.
 * Author: Mattias Wallin <mattias.wallin@stericsson.com>
 */

#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/mfd/abx500.h>

अटल LIST_HEAD(abx500_list);

काष्ठा abx500_device_entry अणु
	काष्ठा list_head list;
	काष्ठा abx500_ops ops;
	काष्ठा device *dev;
पूर्ण;

अटल व्योम lookup_ops(काष्ठा device *dev, काष्ठा abx500_ops **ops)
अणु
	काष्ठा abx500_device_entry *dev_entry;

	*ops = शून्य;
	list_क्रम_each_entry(dev_entry, &abx500_list, list) अणु
		अगर (dev_entry->dev == dev) अणु
			*ops = &dev_entry->ops;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक abx500_रेजिस्टर_ops(काष्ठा device *dev, काष्ठा abx500_ops *ops)
अणु
	काष्ठा abx500_device_entry *dev_entry;

	dev_entry = devm_kzalloc(dev, माप(*dev_entry), GFP_KERNEL);
	अगर (!dev_entry)
		वापस -ENOMEM;

	dev_entry->dev = dev;
	स_नकल(&dev_entry->ops, ops, माप(*ops));

	list_add_tail(&dev_entry->list, &abx500_list);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(abx500_रेजिस्टर_ops);

व्योम abx500_हटाओ_ops(काष्ठा device *dev)
अणु
	काष्ठा abx500_device_entry *dev_entry, *पंचांगp;

	list_क्रम_each_entry_safe(dev_entry, पंचांगp, &abx500_list, list)
		अगर (dev_entry->dev == dev)
			list_del(&dev_entry->list);
पूर्ण
EXPORT_SYMBOL(abx500_हटाओ_ops);

पूर्णांक abx500_set_रेजिस्टर_पूर्णांकerruptible(काष्ठा device *dev, u8 bank, u8 reg,
	u8 value)
अणु
	काष्ठा abx500_ops *ops;

	lookup_ops(dev->parent, &ops);
	अगर (ops && ops->set_रेजिस्टर)
		वापस ops->set_रेजिस्टर(dev, bank, reg, value);
	अन्यथा
		वापस -ENOTSUPP;
पूर्ण
EXPORT_SYMBOL(abx500_set_रेजिस्टर_पूर्णांकerruptible);

पूर्णांक abx500_get_रेजिस्टर_पूर्णांकerruptible(काष्ठा device *dev, u8 bank, u8 reg,
	u8 *value)
अणु
	काष्ठा abx500_ops *ops;

	lookup_ops(dev->parent, &ops);
	अगर (ops && ops->get_रेजिस्टर)
		वापस ops->get_रेजिस्टर(dev, bank, reg, value);
	अन्यथा
		वापस -ENOTSUPP;
पूर्ण
EXPORT_SYMBOL(abx500_get_रेजिस्टर_पूर्णांकerruptible);

पूर्णांक abx500_get_रेजिस्टर_page_पूर्णांकerruptible(काष्ठा device *dev, u8 bank,
	u8 first_reg, u8 *regvals, u8 numregs)
अणु
	काष्ठा abx500_ops *ops;

	lookup_ops(dev->parent, &ops);
	अगर (ops && ops->get_रेजिस्टर_page)
		वापस ops->get_रेजिस्टर_page(dev, bank,
			first_reg, regvals, numregs);
	अन्यथा
		वापस -ENOTSUPP;
पूर्ण
EXPORT_SYMBOL(abx500_get_रेजिस्टर_page_पूर्णांकerruptible);

पूर्णांक abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(काष्ठा device *dev, u8 bank,
	u8 reg, u8 biपंचांगask, u8 bitvalues)
अणु
	काष्ठा abx500_ops *ops;

	lookup_ops(dev->parent, &ops);
	अगर (ops && ops->mask_and_set_रेजिस्टर)
		वापस ops->mask_and_set_रेजिस्टर(dev, bank,
			reg, biपंचांगask, bitvalues);
	अन्यथा
		वापस -ENOTSUPP;
पूर्ण
EXPORT_SYMBOL(abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible);

पूर्णांक abx500_get_chip_id(काष्ठा device *dev)
अणु
	काष्ठा abx500_ops *ops;

	lookup_ops(dev->parent, &ops);
	अगर (ops && ops->get_chip_id)
		वापस ops->get_chip_id(dev);
	अन्यथा
		वापस -ENOTSUPP;
पूर्ण
EXPORT_SYMBOL(abx500_get_chip_id);

पूर्णांक abx500_event_रेजिस्टरs_startup_state_get(काष्ठा device *dev, u8 *event)
अणु
	काष्ठा abx500_ops *ops;

	lookup_ops(dev->parent, &ops);
	अगर (ops && ops->event_रेजिस्टरs_startup_state_get)
		वापस ops->event_रेजिस्टरs_startup_state_get(dev, event);
	अन्यथा
		वापस -ENOTSUPP;
पूर्ण
EXPORT_SYMBOL(abx500_event_रेजिस्टरs_startup_state_get);

पूर्णांक abx500_startup_irq_enabled(काष्ठा device *dev, अचिन्हित पूर्णांक irq)
अणु
	काष्ठा abx500_ops *ops;

	lookup_ops(dev->parent, &ops);
	अगर (ops && ops->startup_irq_enabled)
		वापस ops->startup_irq_enabled(dev, irq);
	अन्यथा
		वापस -ENOTSUPP;
पूर्ण
EXPORT_SYMBOL(abx500_startup_irq_enabled);
