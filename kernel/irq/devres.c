<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/gfp.h>
#समावेश <linux/irq.h>

#समावेश "internals.h"

/*
 * Device resource management aware IRQ request/मुक्त implementation.
 */
काष्ठा irq_devres अणु
	अचिन्हित पूर्णांक irq;
	व्योम *dev_id;
पूर्ण;

अटल व्योम devm_irq_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा irq_devres *this = res;

	मुक्त_irq(this->irq, this->dev_id);
पूर्ण

अटल पूर्णांक devm_irq_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा irq_devres *this = res, *match = data;

	वापस this->irq == match->irq && this->dev_id == match->dev_id;
पूर्ण

/**
 *	devm_request_thपढ़ोed_irq - allocate an पूर्णांकerrupt line क्रम a managed device
 *	@dev: device to request पूर्णांकerrupt क्रम
 *	@irq: Interrupt line to allocate
 *	@handler: Function to be called when the IRQ occurs
 *	@thपढ़ो_fn: function to be called in a thपढ़ोed पूर्णांकerrupt context. शून्य
 *		    क्रम devices which handle everything in @handler
 *	@irqflags: Interrupt type flags
 *	@devname: An ascii name क्रम the claiming device, dev_name(dev) अगर शून्य
 *	@dev_id: A cookie passed back to the handler function
 *
 *	Except क्रम the extra @dev argument, this function takes the
 *	same arguments and perक्रमms the same function as
 *	request_thपढ़ोed_irq().  IRQs requested with this function will be
 *	स्वतःmatically मुक्तd on driver detach.
 *
 *	If an IRQ allocated with this function needs to be मुक्तd
 *	separately, devm_मुक्त_irq() must be used.
 */
पूर्णांक devm_request_thपढ़ोed_irq(काष्ठा device *dev, अचिन्हित पूर्णांक irq,
			      irq_handler_t handler, irq_handler_t thपढ़ो_fn,
			      अचिन्हित दीर्घ irqflags, स्थिर अक्षर *devname,
			      व्योम *dev_id)
अणु
	काष्ठा irq_devres *dr;
	पूर्णांक rc;

	dr = devres_alloc(devm_irq_release, माप(काष्ठा irq_devres),
			  GFP_KERNEL);
	अगर (!dr)
		वापस -ENOMEM;

	अगर (!devname)
		devname = dev_name(dev);

	rc = request_thपढ़ोed_irq(irq, handler, thपढ़ो_fn, irqflags, devname,
				  dev_id);
	अगर (rc) अणु
		devres_मुक्त(dr);
		वापस rc;
	पूर्ण

	dr->irq = irq;
	dr->dev_id = dev_id;
	devres_add(dev, dr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(devm_request_thपढ़ोed_irq);

/**
 *	devm_request_any_context_irq - allocate an पूर्णांकerrupt line क्रम a managed device
 *	@dev: device to request पूर्णांकerrupt क्रम
 *	@irq: Interrupt line to allocate
 *	@handler: Function to be called when the IRQ occurs
 *	@irqflags: Interrupt type flags
 *	@devname: An ascii name क्रम the claiming device, dev_name(dev) अगर शून्य
 *	@dev_id: A cookie passed back to the handler function
 *
 *	Except क्रम the extra @dev argument, this function takes the
 *	same arguments and perक्रमms the same function as
 *	request_any_context_irq().  IRQs requested with this function will be
 *	स्वतःmatically मुक्तd on driver detach.
 *
 *	If an IRQ allocated with this function needs to be मुक्तd
 *	separately, devm_मुक्त_irq() must be used.
 */
पूर्णांक devm_request_any_context_irq(काष्ठा device *dev, अचिन्हित पूर्णांक irq,
			      irq_handler_t handler, अचिन्हित दीर्घ irqflags,
			      स्थिर अक्षर *devname, व्योम *dev_id)
अणु
	काष्ठा irq_devres *dr;
	पूर्णांक rc;

	dr = devres_alloc(devm_irq_release, माप(काष्ठा irq_devres),
			  GFP_KERNEL);
	अगर (!dr)
		वापस -ENOMEM;

	अगर (!devname)
		devname = dev_name(dev);

	rc = request_any_context_irq(irq, handler, irqflags, devname, dev_id);
	अगर (rc < 0) अणु
		devres_मुक्त(dr);
		वापस rc;
	पूर्ण

	dr->irq = irq;
	dr->dev_id = dev_id;
	devres_add(dev, dr);

	वापस rc;
पूर्ण
EXPORT_SYMBOL(devm_request_any_context_irq);

/**
 *	devm_मुक्त_irq - मुक्त an पूर्णांकerrupt
 *	@dev: device to मुक्त पूर्णांकerrupt क्रम
 *	@irq: Interrupt line to मुक्त
 *	@dev_id: Device identity to मुक्त
 *
 *	Except क्रम the extra @dev argument, this function takes the
 *	same arguments and perक्रमms the same function as मुक्त_irq().
 *	This function instead of मुक्त_irq() should be used to manually
 *	मुक्त IRQs allocated with devm_request_irq().
 */
व्योम devm_मुक्त_irq(काष्ठा device *dev, अचिन्हित पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा irq_devres match_data = अणु irq, dev_id पूर्ण;

	WARN_ON(devres_destroy(dev, devm_irq_release, devm_irq_match,
			       &match_data));
	मुक्त_irq(irq, dev_id);
पूर्ण
EXPORT_SYMBOL(devm_मुक्त_irq);

काष्ठा irq_desc_devres अणु
	अचिन्हित पूर्णांक from;
	अचिन्हित पूर्णांक cnt;
पूर्ण;

अटल व्योम devm_irq_desc_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा irq_desc_devres *this = res;

	irq_मुक्त_descs(this->from, this->cnt);
पूर्ण

/**
 * __devm_irq_alloc_descs - Allocate and initialize a range of irq descriptors
 *			    क्रम a managed device
 * @dev:	Device to allocate the descriptors क्रम
 * @irq:	Allocate क्रम specअगरic irq number अगर irq >= 0
 * @from:	Start the search from this irq number
 * @cnt:	Number of consecutive irqs to allocate
 * @node:	Preferred node on which the irq descriptor should be allocated
 * @owner:	Owning module (can be शून्य)
 * @affinity:	Optional poपूर्णांकer to an irq_affinity_desc array of size @cnt
 *		which hपूर्णांकs where the irq descriptors should be allocated
 *		and which शेष affinities to use
 *
 * Returns the first irq number or error code.
 *
 * Note: Use the provided wrappers (devm_irq_alloc_desc*) क्रम simplicity.
 */
पूर्णांक __devm_irq_alloc_descs(काष्ठा device *dev, पूर्णांक irq, अचिन्हित पूर्णांक from,
			   अचिन्हित पूर्णांक cnt, पूर्णांक node, काष्ठा module *owner,
			   स्थिर काष्ठा irq_affinity_desc *affinity)
अणु
	काष्ठा irq_desc_devres *dr;
	पूर्णांक base;

	dr = devres_alloc(devm_irq_desc_release, माप(*dr), GFP_KERNEL);
	अगर (!dr)
		वापस -ENOMEM;

	base = __irq_alloc_descs(irq, from, cnt, node, owner, affinity);
	अगर (base < 0) अणु
		devres_मुक्त(dr);
		वापस base;
	पूर्ण

	dr->from = base;
	dr->cnt = cnt;
	devres_add(dev, dr);

	वापस base;
पूर्ण
EXPORT_SYMBOL_GPL(__devm_irq_alloc_descs);

#अगर_घोषित CONFIG_GENERIC_IRQ_CHIP
/**
 * devm_irq_alloc_generic_chip - Allocate and initialize a generic chip
 *                               क्रम a managed device
 * @dev:	Device to allocate the generic chip क्रम
 * @name:	Name of the irq chip
 * @num_ct:	Number of irq_chip_type instances associated with this
 * @irq_base:	Interrupt base nr क्रम this chip
 * @reg_base:	Register base address (भव)
 * @handler:	Default flow handler associated with this chip
 *
 * Returns an initialized irq_chip_generic काष्ठाure. The chip शेषs
 * to the primary (index 0) irq_chip_type and @handler
 */
काष्ठा irq_chip_generic *
devm_irq_alloc_generic_chip(काष्ठा device *dev, स्थिर अक्षर *name, पूर्णांक num_ct,
			    अचिन्हित पूर्णांक irq_base, व्योम __iomem *reg_base,
			    irq_flow_handler_t handler)
अणु
	काष्ठा irq_chip_generic *gc;

	gc = devm_kzalloc(dev, काष्ठा_size(gc, chip_types, num_ct), GFP_KERNEL);
	अगर (gc)
		irq_init_generic_chip(gc, name, num_ct,
				      irq_base, reg_base, handler);

	वापस gc;
पूर्ण
EXPORT_SYMBOL_GPL(devm_irq_alloc_generic_chip);

काष्ठा irq_generic_chip_devres अणु
	काष्ठा irq_chip_generic *gc;
	u32 msk;
	अचिन्हित पूर्णांक clr;
	अचिन्हित पूर्णांक set;
पूर्ण;

अटल व्योम devm_irq_हटाओ_generic_chip(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा irq_generic_chip_devres *this = res;

	irq_हटाओ_generic_chip(this->gc, this->msk, this->clr, this->set);
पूर्ण

/**
 * devm_irq_setup_generic_chip - Setup a range of पूर्णांकerrupts with a generic
 *                               chip क्रम a managed device
 *
 * @dev:	Device to setup the generic chip क्रम
 * @gc:		Generic irq chip holding all data
 * @msk:	Biपंचांगask holding the irqs to initialize relative to gc->irq_base
 * @flags:	Flags क्रम initialization
 * @clr:	IRQ_* bits to clear
 * @set:	IRQ_* bits to set
 *
 * Set up max. 32 पूर्णांकerrupts starting from gc->irq_base. Note, this
 * initializes all पूर्णांकerrupts to the primary irq_chip_type and its
 * associated handler.
 */
पूर्णांक devm_irq_setup_generic_chip(काष्ठा device *dev, काष्ठा irq_chip_generic *gc,
				u32 msk, क्रमागत irq_gc_flags flags,
				अचिन्हित पूर्णांक clr, अचिन्हित पूर्णांक set)
अणु
	काष्ठा irq_generic_chip_devres *dr;

	dr = devres_alloc(devm_irq_हटाओ_generic_chip,
			  माप(*dr), GFP_KERNEL);
	अगर (!dr)
		वापस -ENOMEM;

	irq_setup_generic_chip(gc, msk, flags, clr, set);

	dr->gc = gc;
	dr->msk = msk;
	dr->clr = clr;
	dr->set = set;
	devres_add(dev, dr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_irq_setup_generic_chip);
#पूर्ण_अगर /* CONFIG_GENERIC_IRQ_CHIP */
