<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-पूर्णांकegrator/core.c
 *
 *  Copyright (C) 2000-2003 Deep Blue Solutions Ltd
 */
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/memblock.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/amba/serial.h>
#समावेश <linux/पन.स>
#समावेश <linux/स्थिति.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/समय.स>

#समावेश "hardware.h"
#समावेश "cm.h"
#समावेश "common.h"

अटल DEFINE_RAW_SPINLOCK(cm_lock);
अटल व्योम __iomem *cm_base;

/**
 * cm_get - get the value from the CM_CTRL रेजिस्टर
 */
u32 cm_get(व्योम)
अणु
	वापस पढ़ोl(cm_base + INTEGRATOR_HDR_CTRL_OFFSET);
पूर्ण

/**
 * cm_control - update the CM_CTRL रेजिस्टर.
 * @mask: bits to change
 * @set: bits to set
 */
व्योम cm_control(u32 mask, u32 set)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	raw_spin_lock_irqsave(&cm_lock, flags);
	val = पढ़ोl(cm_base + INTEGRATOR_HDR_CTRL_OFFSET) & ~mask;
	ग_लिखोl(val | set, cm_base + INTEGRATOR_HDR_CTRL_OFFSET);
	raw_spin_unlock_irqrestore(&cm_lock, flags);
पूर्ण

व्योम cm_clear_irqs(व्योम)
अणु
	/* disable core module IRQs */
	ग_लिखोl(0xffffffffU, cm_base + INTEGRATOR_HDR_IC_OFFSET +
		IRQ_ENABLE_CLEAR);
पूर्ण

अटल स्थिर काष्ठा of_device_id cm_match[] = अणु
	अणु .compatible = "arm,core-module-integrator"पूर्ण,
	अणु पूर्ण,
पूर्ण;

व्योम cm_init(व्योम)
अणु
	काष्ठा device_node *cm = of_find_matching_node(शून्य, cm_match);

	अगर (!cm) अणु
		pr_crit("no core module node found in device tree\n");
		वापस;
	पूर्ण
	cm_base = of_iomap(cm, 0);
	अगर (!cm_base) अणु
		pr_crit("could not remap core module\n");
		वापस;
	पूर्ण
	cm_clear_irqs();
पूर्ण

/*
 * We need to stop things allocating the low memory; ideally we need a
 * better implementation of GFP_DMA which करोes not assume that DMA-able
 * memory starts at zero.
 */
व्योम __init पूर्णांकegrator_reserve(व्योम)
अणु
	memblock_reserve(PHYS_OFFSET, __pa(swapper_pg_dir) - PHYS_OFFSET);
पूर्ण
