<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2002 ARM Limited, All Rights Reserved.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip/arm-gic.h>

#समावेश "irq-gic-common.h"

अटल DEFINE_RAW_SPINLOCK(irq_controller_lock);

अटल स्थिर काष्ठा gic_kvm_info *gic_kvm_info;

स्थिर काष्ठा gic_kvm_info *gic_get_kvm_info(व्योम)
अणु
	वापस gic_kvm_info;
पूर्ण

व्योम gic_set_kvm_info(स्थिर काष्ठा gic_kvm_info *info)
अणु
	BUG_ON(gic_kvm_info != शून्य);
	gic_kvm_info = info;
पूर्ण

व्योम gic_enable_of_quirks(स्थिर काष्ठा device_node *np,
			  स्थिर काष्ठा gic_quirk *quirks, व्योम *data)
अणु
	क्रम (; quirks->desc; quirks++) अणु
		अगर (!of_device_is_compatible(np, quirks->compatible))
			जारी;
		अगर (quirks->init(data))
			pr_info("GIC: enabling workaround for %s\n",
				quirks->desc);
	पूर्ण
पूर्ण

व्योम gic_enable_quirks(u32 iidr, स्थिर काष्ठा gic_quirk *quirks,
		व्योम *data)
अणु
	क्रम (; quirks->desc; quirks++) अणु
		अगर (quirks->compatible)
			जारी;
		अगर (quirks->iidr != (quirks->mask & iidr))
			जारी;
		अगर (quirks->init(data))
			pr_info("GIC: enabling workaround for %s\n",
				quirks->desc);
	पूर्ण
पूर्ण

पूर्णांक gic_configure_irq(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक type,
		       व्योम __iomem *base, व्योम (*sync_access)(व्योम))
अणु
	u32 confmask = 0x2 << ((irq % 16) * 2);
	u32 confoff = (irq / 16) * 4;
	u32 val, oldval;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	/*
	 * Read current configuration रेजिस्टर, and insert the config
	 * क्रम "irq", depending on "type".
	 */
	raw_spin_lock_irqsave(&irq_controller_lock, flags);
	val = oldval = पढ़ोl_relaxed(base + confoff);
	अगर (type & IRQ_TYPE_LEVEL_MASK)
		val &= ~confmask;
	अन्यथा अगर (type & IRQ_TYPE_EDGE_BOTH)
		val |= confmask;

	/* If the current configuration is the same, then we are करोne */
	अगर (val == oldval) अणु
		raw_spin_unlock_irqrestore(&irq_controller_lock, flags);
		वापस 0;
	पूर्ण

	/*
	 * Write back the new configuration, and possibly re-enable
	 * the पूर्णांकerrupt. If we fail to ग_लिखो a new configuration क्रम
	 * an SPI then WARN and वापस an error. If we fail to ग_लिखो the
	 * configuration क्रम a PPI this is most likely because the GIC
	 * करोes not allow us to set the configuration or we are in a
	 * non-secure mode, and hence it may not be catastrophic.
	 */
	ग_लिखोl_relaxed(val, base + confoff);
	अगर (पढ़ोl_relaxed(base + confoff) != val)
		ret = -EINVAL;

	raw_spin_unlock_irqrestore(&irq_controller_lock, flags);

	अगर (sync_access)
		sync_access();

	वापस ret;
पूर्ण

व्योम gic_dist_config(व्योम __iomem *base, पूर्णांक gic_irqs,
		     व्योम (*sync_access)(व्योम))
अणु
	अचिन्हित पूर्णांक i;

	/*
	 * Set all global पूर्णांकerrupts to be level triggered, active low.
	 */
	क्रम (i = 32; i < gic_irqs; i += 16)
		ग_लिखोl_relaxed(GICD_INT_ACTLOW_LVLTRIG,
					base + GIC_DIST_CONFIG + i / 4);

	/*
	 * Set priority on all global पूर्णांकerrupts.
	 */
	क्रम (i = 32; i < gic_irqs; i += 4)
		ग_लिखोl_relaxed(GICD_INT_DEF_PRI_X4, base + GIC_DIST_PRI + i);

	/*
	 * Deactivate and disable all SPIs. Leave the PPI and SGIs
	 * alone as they are in the redistributor रेजिस्टरs on GICv3.
	 */
	क्रम (i = 32; i < gic_irqs; i += 32) अणु
		ग_लिखोl_relaxed(GICD_INT_EN_CLR_X32,
			       base + GIC_DIST_ACTIVE_CLEAR + i / 8);
		ग_लिखोl_relaxed(GICD_INT_EN_CLR_X32,
			       base + GIC_DIST_ENABLE_CLEAR + i / 8);
	पूर्ण

	अगर (sync_access)
		sync_access();
पूर्ण

व्योम gic_cpu_config(व्योम __iomem *base, पूर्णांक nr, व्योम (*sync_access)(व्योम))
अणु
	पूर्णांक i;

	/*
	 * Deal with the banked PPI and SGI पूर्णांकerrupts - disable all
	 * निजी पूर्णांकerrupts. Make sure everything is deactivated.
	 */
	क्रम (i = 0; i < nr; i += 32) अणु
		ग_लिखोl_relaxed(GICD_INT_EN_CLR_X32,
			       base + GIC_DIST_ACTIVE_CLEAR + i / 8);
		ग_लिखोl_relaxed(GICD_INT_EN_CLR_X32,
			       base + GIC_DIST_ENABLE_CLEAR + i / 8);
	पूर्ण

	/*
	 * Set priority on PPI and SGI पूर्णांकerrupts
	 */
	क्रम (i = 0; i < nr; i += 4)
		ग_लिखोl_relaxed(GICD_INT_DEF_PRI_X4,
					base + GIC_DIST_PRI + i * 4 / 4);

	अगर (sync_access)
		sync_access();
पूर्ण
