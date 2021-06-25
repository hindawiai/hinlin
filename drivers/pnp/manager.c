<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * manager.c - Resource Management, Conflict Resolution, Activation and Disabling of Devices
 *
 * based on isapnp.c resource management (c) Jaroslav Kysela <perex@perex.cz>
 * Copyright 2003 Adam Belay <ambx1@neo.rr.com>
 * Copyright (C) 2008 Hewlett-Packard Development Company, L.P.
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pnp.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/mutex.h>
#समावेश "base.h"

DEFINE_MUTEX(pnp_res_mutex);

अटल काष्ठा resource *pnp_find_resource(काष्ठा pnp_dev *dev,
					  अचिन्हित अक्षर rule,
					  अचिन्हित दीर्घ type,
					  अचिन्हित पूर्णांक bar)
अणु
	काष्ठा resource *res = pnp_get_resource(dev, type, bar);

	/* when the resource alपढ़ोy exists, set its resource bits from rule */
	अगर (res) अणु
		res->flags &= ~IORESOURCE_BITS;
		res->flags |= rule & IORESOURCE_BITS;
	पूर्ण

	वापस res;
पूर्ण

अटल पूर्णांक pnp_assign_port(काष्ठा pnp_dev *dev, काष्ठा pnp_port *rule, पूर्णांक idx)
अणु
	काष्ठा resource *res, local_res;

	res = pnp_find_resource(dev, rule->flags, IORESOURCE_IO, idx);
	अगर (res) अणु
		pnp_dbg(&dev->dev, "  io %d already set to %#llx-%#llx "
			"flags %#lx\n", idx, (अचिन्हित दीर्घ दीर्घ) res->start,
			(अचिन्हित दीर्घ दीर्घ) res->end, res->flags);
		वापस 0;
	पूर्ण

	res = &local_res;
	res->flags = rule->flags | IORESOURCE_AUTO;
	res->start = 0;
	res->end = 0;

	अगर (!rule->size) अणु
		res->flags |= IORESOURCE_DISABLED;
		pnp_dbg(&dev->dev, "  io %d disabled\n", idx);
		जाओ __add;
	पूर्ण

	res->start = rule->min;
	res->end = res->start + rule->size - 1;

	जबतक (!pnp_check_port(dev, res)) अणु
		res->start += rule->align;
		res->end = res->start + rule->size - 1;
		अगर (res->start > rule->max || !rule->align) अणु
			pnp_dbg(&dev->dev, "  couldn't assign io %d "
				"(min %#llx max %#llx)\n", idx,
				(अचिन्हित दीर्घ दीर्घ) rule->min,
				(अचिन्हित दीर्घ दीर्घ) rule->max);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

__add:
	pnp_add_io_resource(dev, res->start, res->end, res->flags);
	वापस 0;
पूर्ण

अटल पूर्णांक pnp_assign_mem(काष्ठा pnp_dev *dev, काष्ठा pnp_mem *rule, पूर्णांक idx)
अणु
	काष्ठा resource *res, local_res;

	res = pnp_find_resource(dev, rule->flags, IORESOURCE_MEM, idx);
	अगर (res) अणु
		pnp_dbg(&dev->dev, "  mem %d already set to %#llx-%#llx "
			"flags %#lx\n", idx, (अचिन्हित दीर्घ दीर्घ) res->start,
			(अचिन्हित दीर्घ दीर्घ) res->end, res->flags);
		वापस 0;
	पूर्ण

	res = &local_res;
	res->flags = rule->flags | IORESOURCE_AUTO;
	res->start = 0;
	res->end = 0;

	/* ??? rule->flags restricted to 8 bits, all tests bogus ??? */
	अगर (!(rule->flags & IORESOURCE_MEM_WRITEABLE))
		res->flags |= IORESOURCE_READONLY;
	अगर (rule->flags & IORESOURCE_MEM_RANGELENGTH)
		res->flags |= IORESOURCE_RANGELENGTH;
	अगर (rule->flags & IORESOURCE_MEM_SHADOWABLE)
		res->flags |= IORESOURCE_SHADOWABLE;

	अगर (!rule->size) अणु
		res->flags |= IORESOURCE_DISABLED;
		pnp_dbg(&dev->dev, "  mem %d disabled\n", idx);
		जाओ __add;
	पूर्ण

	res->start = rule->min;
	res->end = res->start + rule->size - 1;

	जबतक (!pnp_check_mem(dev, res)) अणु
		res->start += rule->align;
		res->end = res->start + rule->size - 1;
		अगर (res->start > rule->max || !rule->align) अणु
			pnp_dbg(&dev->dev, "  couldn't assign mem %d "
				"(min %#llx max %#llx)\n", idx,
				(अचिन्हित दीर्घ दीर्घ) rule->min,
				(अचिन्हित दीर्घ दीर्घ) rule->max);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

__add:
	pnp_add_mem_resource(dev, res->start, res->end, res->flags);
	वापस 0;
पूर्ण

अटल पूर्णांक pnp_assign_irq(काष्ठा pnp_dev *dev, काष्ठा pnp_irq *rule, पूर्णांक idx)
अणु
	काष्ठा resource *res, local_res;
	पूर्णांक i;

	/* IRQ priority: this table is good क्रम i386 */
	अटल अचिन्हित लघु xtab[16] = अणु
		5, 10, 11, 12, 9, 14, 15, 7, 3, 4, 13, 0, 1, 6, 8, 2
	पूर्ण;

	res = pnp_find_resource(dev, rule->flags, IORESOURCE_IRQ, idx);
	अगर (res) अणु
		pnp_dbg(&dev->dev, "  irq %d already set to %d flags %#lx\n",
			idx, (पूर्णांक) res->start, res->flags);
		वापस 0;
	पूर्ण

	res = &local_res;
	res->flags = rule->flags | IORESOURCE_AUTO;
	res->start = -1;
	res->end = -1;

	अगर (biपंचांगap_empty(rule->map.bits, PNP_IRQ_NR)) अणु
		res->flags |= IORESOURCE_DISABLED;
		pnp_dbg(&dev->dev, "  irq %d disabled\n", idx);
		जाओ __add;
	पूर्ण

	/* TBD: need check क्रम >16 IRQ */
	res->start = find_next_bit(rule->map.bits, PNP_IRQ_NR, 16);
	अगर (res->start < PNP_IRQ_NR) अणु
		res->end = res->start;
		जाओ __add;
	पूर्ण
	क्रम (i = 0; i < 16; i++) अणु
		अगर (test_bit(xtab[i], rule->map.bits)) अणु
			res->start = res->end = xtab[i];
			अगर (pnp_check_irq(dev, res))
				जाओ __add;
		पूर्ण
	पूर्ण

	अगर (rule->flags & IORESOURCE_IRQ_OPTIONAL) अणु
		res->start = -1;
		res->end = -1;
		res->flags |= IORESOURCE_DISABLED;
		pnp_dbg(&dev->dev, "  irq %d disabled (optional)\n", idx);
		जाओ __add;
	पूर्ण

	pnp_dbg(&dev->dev, "  couldn't assign irq %d\n", idx);
	वापस -EBUSY;

__add:
	pnp_add_irq_resource(dev, res->start, res->flags);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ISA_DMA_API
अटल पूर्णांक pnp_assign_dma(काष्ठा pnp_dev *dev, काष्ठा pnp_dma *rule, पूर्णांक idx)
अणु
	काष्ठा resource *res, local_res;
	पूर्णांक i;

	/* DMA priority: this table is good क्रम i386 */
	अटल अचिन्हित लघु xtab[8] = अणु
		1, 3, 5, 6, 7, 0, 2, 4
	पूर्ण;

	res = pnp_find_resource(dev, rule->flags, IORESOURCE_DMA, idx);
	अगर (res) अणु
		pnp_dbg(&dev->dev, "  dma %d already set to %d flags %#lx\n",
			idx, (पूर्णांक) res->start, res->flags);
		वापस 0;
	पूर्ण

	res = &local_res;
	res->flags = rule->flags | IORESOURCE_AUTO;
	res->start = -1;
	res->end = -1;

	अगर (!rule->map) अणु
		res->flags |= IORESOURCE_DISABLED;
		pnp_dbg(&dev->dev, "  dma %d disabled\n", idx);
		जाओ __add;
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		अगर (rule->map & (1 << xtab[i])) अणु
			res->start = res->end = xtab[i];
			अगर (pnp_check_dma(dev, res))
				जाओ __add;
		पूर्ण
	पूर्ण

	pnp_dbg(&dev->dev, "  couldn't assign dma %d\n", idx);
	वापस -EBUSY;

__add:
	pnp_add_dma_resource(dev, res->start, res->flags);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_ISA_DMA_API */

व्योम pnp_init_resources(काष्ठा pnp_dev *dev)
अणु
	pnp_मुक्त_resources(dev);
पूर्ण

अटल व्योम pnp_clean_resource_table(काष्ठा pnp_dev *dev)
अणु
	काष्ठा pnp_resource *pnp_res, *पंचांगp;

	list_क्रम_each_entry_safe(pnp_res, पंचांगp, &dev->resources, list) अणु
		अगर (pnp_res->res.flags & IORESOURCE_AUTO)
			pnp_मुक्त_resource(pnp_res);
	पूर्ण
पूर्ण

/**
 * pnp_assign_resources - assigns resources to the device based on the specअगरied dependent number
 * @dev: poपूर्णांकer to the desired device
 * @set: the dependent function number
 */
अटल पूर्णांक pnp_assign_resources(काष्ठा pnp_dev *dev, पूर्णांक set)
अणु
	काष्ठा pnp_option *option;
	पूर्णांक nport = 0, nmem = 0, nirq = 0;
	पूर्णांक ndma __maybe_unused = 0;
	पूर्णांक ret = 0;

	pnp_dbg(&dev->dev, "pnp_assign_resources, try dependent set %d\n", set);
	mutex_lock(&pnp_res_mutex);
	pnp_clean_resource_table(dev);

	list_क्रम_each_entry(option, &dev->options, list) अणु
		अगर (pnp_option_is_dependent(option) &&
		    pnp_option_set(option) != set)
				जारी;

		चयन (option->type) अणु
		हाल IORESOURCE_IO:
			ret = pnp_assign_port(dev, &option->u.port, nport++);
			अवरोध;
		हाल IORESOURCE_MEM:
			ret = pnp_assign_mem(dev, &option->u.mem, nmem++);
			अवरोध;
		हाल IORESOURCE_IRQ:
			ret = pnp_assign_irq(dev, &option->u.irq, nirq++);
			अवरोध;
#अगर_घोषित CONFIG_ISA_DMA_API
		हाल IORESOURCE_DMA:
			ret = pnp_assign_dma(dev, &option->u.dma, ndma++);
			अवरोध;
#पूर्ण_अगर
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	mutex_unlock(&pnp_res_mutex);
	अगर (ret < 0) अणु
		pnp_dbg(&dev->dev, "pnp_assign_resources failed (%d)\n", ret);
		pnp_clean_resource_table(dev);
	पूर्ण अन्यथा
		dbg_pnp_show_resources(dev, "pnp_assign_resources succeeded");
	वापस ret;
पूर्ण

/**
 * pnp_स्वतः_config_dev - स्वतःmatically assigns resources to a device
 * @dev: poपूर्णांकer to the desired device
 */
पूर्णांक pnp_स्वतः_config_dev(काष्ठा pnp_dev *dev)
अणु
	पूर्णांक i, ret;

	अगर (!pnp_can_configure(dev)) अणु
		pnp_dbg(&dev->dev, "configuration not supported\n");
		वापस -ENODEV;
	पूर्ण

	ret = pnp_assign_resources(dev, 0);
	अगर (ret == 0)
		वापस 0;

	क्रम (i = 1; i < dev->num_dependent_sets; i++) अणु
		ret = pnp_assign_resources(dev, i);
		अगर (ret == 0)
			वापस 0;
	पूर्ण

	dev_err(&dev->dev, "unable to assign resources\n");
	वापस ret;
पूर्ण

/**
 * pnp_start_dev - low-level start of the PnP device
 * @dev: poपूर्णांकer to the desired device
 *
 * assumes that resources have alपढ़ोy been allocated
 */
पूर्णांक pnp_start_dev(काष्ठा pnp_dev *dev)
अणु
	अगर (!pnp_can_ग_लिखो(dev)) अणु
		pnp_dbg(&dev->dev, "activation not supported\n");
		वापस -EINVAL;
	पूर्ण

	dbg_pnp_show_resources(dev, "pnp_start_dev");
	अगर (dev->protocol->set(dev) < 0) अणु
		dev_err(&dev->dev, "activation failed\n");
		वापस -EIO;
	पूर्ण

	dev_info(&dev->dev, "activated\n");
	वापस 0;
पूर्ण

/**
 * pnp_stop_dev - low-level disable of the PnP device
 * @dev: poपूर्णांकer to the desired device
 *
 * करोes not मुक्त resources
 */
पूर्णांक pnp_stop_dev(काष्ठा pnp_dev *dev)
अणु
	अगर (!pnp_can_disable(dev)) अणु
		pnp_dbg(&dev->dev, "disabling not supported\n");
		वापस -EINVAL;
	पूर्ण
	अगर (dev->protocol->disable(dev) < 0) अणु
		dev_err(&dev->dev, "disable failed\n");
		वापस -EIO;
	पूर्ण

	dev_info(&dev->dev, "disabled\n");
	वापस 0;
पूर्ण

/**
 * pnp_activate_dev - activates a PnP device क्रम use
 * @dev: poपूर्णांकer to the desired device
 *
 * करोes not validate or set resources so be careful.
 */
पूर्णांक pnp_activate_dev(काष्ठा pnp_dev *dev)
अणु
	पूर्णांक error;

	अगर (dev->active)
		वापस 0;

	/* ensure resources are allocated */
	अगर (pnp_स्वतः_config_dev(dev))
		वापस -EBUSY;

	error = pnp_start_dev(dev);
	अगर (error)
		वापस error;

	dev->active = 1;
	वापस 0;
पूर्ण

/**
 * pnp_disable_dev - disables device
 * @dev: poपूर्णांकer to the desired device
 *
 * inक्रमm the correct pnp protocol so that resources can be used by other devices
 */
पूर्णांक pnp_disable_dev(काष्ठा pnp_dev *dev)
अणु
	पूर्णांक error;

	अगर (!dev->active)
		वापस 0;

	error = pnp_stop_dev(dev);
	अगर (error)
		वापस error;

	dev->active = 0;

	/* release the resources so that other devices can use them */
	mutex_lock(&pnp_res_mutex);
	pnp_clean_resource_table(dev);
	mutex_unlock(&pnp_res_mutex);

	वापस 0;
पूर्ण

EXPORT_SYMBOL(pnp_start_dev);
EXPORT_SYMBOL(pnp_stop_dev);
EXPORT_SYMBOL(pnp_activate_dev);
EXPORT_SYMBOL(pnp_disable_dev);
