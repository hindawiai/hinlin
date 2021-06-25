<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Common CPM code
 *
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 *
 * Copyright 2007-2008,2010 Freescale Semiconductor, Inc.
 *
 * Some parts derived from commproc.c/cpm2_common.c, which is:
 * Copyright (c) 1997 Dan error_act (dmalek@jlc.net)
 * Copyright (c) 1999-2001 Dan Malek <dan@embeddedalley.com>
 * Copyright (c) 2000 MontaVista Software, Inc (source@mvista.com)
 * 2006 (c) MontaVista Software, Inc.
 * Vitaly Bordug <vbordug@ru.mvista.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/of_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/export.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/cpm.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <soc/fsl/qe/qe.h>

#समावेश <mm/mmu_decl.h>

#अगर defined(CONFIG_CPM2) || defined(CONFIG_8xx_GPIO)
#समावेश <linux/of_gpपन.स>
#पूर्ण_अगर

अटल पूर्णांक __init cpm_init(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,cpm1");
	अगर (!np)
		np = of_find_compatible_node(शून्य, शून्य, "fsl,cpm2");
	अगर (!np)
		वापस -ENODEV;
	cpm_muram_init();
	of_node_put(np);
	वापस 0;
पूर्ण
subsys_initcall(cpm_init);

#अगर_घोषित CONFIG_PPC_EARLY_DEBUG_CPM
अटल u32 __iomem *cpm_udbg_txdesc;
अटल u8 __iomem *cpm_udbg_txbuf;

अटल व्योम udbg_अ_दो_cpm(अक्षर c)
अणु
	अगर (c == '\n')
		udbg_अ_दो_cpm('\r');

	जबतक (in_be32(&cpm_udbg_txdesc[0]) & 0x80000000)
		;

	out_8(cpm_udbg_txbuf, c);
	out_be32(&cpm_udbg_txdesc[0], 0xa0000001);
पूर्ण

व्योम __init udbg_init_cpm(व्योम)
अणु
#अगर_घोषित CONFIG_PPC_8xx
	mmu_mapin_immr();

	cpm_udbg_txdesc = (u32 __iomem __क्रमce *)
			  (CONFIG_PPC_EARLY_DEBUG_CPM_ADDR - PHYS_IMMR_BASE +
			   VIRT_IMMR_BASE);
	cpm_udbg_txbuf = (u8 __iomem __क्रमce *)
			 (in_be32(&cpm_udbg_txdesc[1]) - PHYS_IMMR_BASE +
			  VIRT_IMMR_BASE);
#अन्यथा
	cpm_udbg_txdesc = (u32 __iomem __क्रमce *)
			  CONFIG_PPC_EARLY_DEBUG_CPM_ADDR;
	cpm_udbg_txbuf = (u8 __iomem __क्रमce *)in_be32(&cpm_udbg_txdesc[1]);
#पूर्ण_अगर

	अगर (cpm_udbg_txdesc) अणु
#अगर_घोषित CONFIG_CPM2
		setbat(1, 0xf0000000, 0xf0000000, 1024*1024, PAGE_KERNEL_NCG);
#पूर्ण_अगर
		udbg_अ_दो = udbg_अ_दो_cpm;
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_CPM2) || defined(CONFIG_8xx_GPIO)

काष्ठा cpm2_ioports अणु
	u32 dir, par, sor, odr, dat;
	u32 res[3];
पूर्ण;

काष्ठा cpm2_gpio32_chip अणु
	काष्ठा of_mm_gpio_chip mm_gc;
	spinlock_t lock;

	/* shaकरोwed data रेजिस्टर to clear/set bits safely */
	u32 cpdata;
पूर्ण;

अटल व्योम cpm2_gpio32_save_regs(काष्ठा of_mm_gpio_chip *mm_gc)
अणु
	काष्ठा cpm2_gpio32_chip *cpm2_gc =
		container_of(mm_gc, काष्ठा cpm2_gpio32_chip, mm_gc);
	काष्ठा cpm2_ioports __iomem *iop = mm_gc->regs;

	cpm2_gc->cpdata = in_be32(&iop->dat);
पूर्ण

अटल पूर्णांक cpm2_gpio32_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा cpm2_ioports __iomem *iop = mm_gc->regs;
	u32 pin_mask;

	pin_mask = 1 << (31 - gpio);

	वापस !!(in_be32(&iop->dat) & pin_mask);
पूर्ण

अटल व्योम __cpm2_gpio32_set(काष्ठा of_mm_gpio_chip *mm_gc, u32 pin_mask,
	पूर्णांक value)
अणु
	काष्ठा cpm2_gpio32_chip *cpm2_gc = gpiochip_get_data(&mm_gc->gc);
	काष्ठा cpm2_ioports __iomem *iop = mm_gc->regs;

	अगर (value)
		cpm2_gc->cpdata |= pin_mask;
	अन्यथा
		cpm2_gc->cpdata &= ~pin_mask;

	out_be32(&iop->dat, cpm2_gc->cpdata);
पूर्ण

अटल व्योम cpm2_gpio32_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक value)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा cpm2_gpio32_chip *cpm2_gc = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;
	u32 pin_mask = 1 << (31 - gpio);

	spin_lock_irqsave(&cpm2_gc->lock, flags);

	__cpm2_gpio32_set(mm_gc, pin_mask, value);

	spin_unlock_irqrestore(&cpm2_gc->lock, flags);
पूर्ण

अटल पूर्णांक cpm2_gpio32_dir_out(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा cpm2_gpio32_chip *cpm2_gc = gpiochip_get_data(gc);
	काष्ठा cpm2_ioports __iomem *iop = mm_gc->regs;
	अचिन्हित दीर्घ flags;
	u32 pin_mask = 1 << (31 - gpio);

	spin_lock_irqsave(&cpm2_gc->lock, flags);

	setbits32(&iop->dir, pin_mask);
	__cpm2_gpio32_set(mm_gc, pin_mask, val);

	spin_unlock_irqrestore(&cpm2_gc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक cpm2_gpio32_dir_in(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा cpm2_gpio32_chip *cpm2_gc = gpiochip_get_data(gc);
	काष्ठा cpm2_ioports __iomem *iop = mm_gc->regs;
	अचिन्हित दीर्घ flags;
	u32 pin_mask = 1 << (31 - gpio);

	spin_lock_irqsave(&cpm2_gc->lock, flags);

	clrbits32(&iop->dir, pin_mask);

	spin_unlock_irqrestore(&cpm2_gc->lock, flags);

	वापस 0;
पूर्ण

पूर्णांक cpm2_gpiochip_add32(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा cpm2_gpio32_chip *cpm2_gc;
	काष्ठा of_mm_gpio_chip *mm_gc;
	काष्ठा gpio_chip *gc;

	cpm2_gc = kzalloc(माप(*cpm2_gc), GFP_KERNEL);
	अगर (!cpm2_gc)
		वापस -ENOMEM;

	spin_lock_init(&cpm2_gc->lock);

	mm_gc = &cpm2_gc->mm_gc;
	gc = &mm_gc->gc;

	mm_gc->save_regs = cpm2_gpio32_save_regs;
	gc->ngpio = 32;
	gc->direction_input = cpm2_gpio32_dir_in;
	gc->direction_output = cpm2_gpio32_dir_out;
	gc->get = cpm2_gpio32_get;
	gc->set = cpm2_gpio32_set;
	gc->parent = dev;
	gc->owner = THIS_MODULE;

	वापस of_mm_gpiochip_add_data(np, mm_gc, cpm2_gc);
पूर्ण
#पूर्ण_अगर /* CONFIG_CPM2 || CONFIG_8xx_GPIO */
