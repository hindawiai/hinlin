<शैली गुरु>
/*
 * linux/arch/arm/mach-omap1/irq.c
 *
 * Interrupt handler क्रम all OMAP boards
 *
 * Copyright (C) 2004 Nokia Corporation
 * Written by Tony Lindgren <tony@atomide.com>
 * Major cleanups by Juha Yrjथघlथअ <juha.yrjola@nokia.com>
 *
 * Completely re-written to support various OMAP chips with bank specअगरic
 * पूर्णांकerrupt handlers.
 *
 * Some snippets of the code taken from the older OMAP पूर्णांकerrupt handler
 * Copyright (C) 2001 RidgeRun, Inc. Greg Lonnon <glonnon@ridgerun.com>
 *
 * GPIO पूर्णांकerrupt handler moved to gpio.c by Juha Yrjola
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * You should have received a copy of the  GNU General Public License aदीर्घ
 * with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश "soc.h"

#समावेश <mach/hardware.h>

#समावेश "common.h"

#घोषणा IRQ_BANK(irq) ((irq) >> 5)
#घोषणा IRQ_BIT(irq)  ((irq) & 0x1f)

काष्ठा omap_irq_bank अणु
	अचिन्हित दीर्घ base_reg;
	व्योम __iomem *va;
	अचिन्हित दीर्घ trigger_map;
	अचिन्हित दीर्घ wake_enable;
पूर्ण;

अटल u32 omap_l2_irq;
अटल अचिन्हित पूर्णांक irq_bank_count;
अटल काष्ठा omap_irq_bank *irq_banks;
अटल काष्ठा irq_करोमुख्य *करोमुख्य;

अटल अंतरभूत अचिन्हित पूर्णांक irq_bank_पढ़ोl(पूर्णांक bank, पूर्णांक offset)
अणु
	वापस पढ़ोl_relaxed(irq_banks[bank].va + offset);
पूर्ण
अटल अंतरभूत व्योम irq_bank_ग_लिखोl(अचिन्हित दीर्घ value, पूर्णांक bank, पूर्णांक offset)
अणु
	ग_लिखोl_relaxed(value, irq_banks[bank].va + offset);
पूर्ण

अटल व्योम omap_ack_irq(पूर्णांक irq)
अणु
	अगर (irq > 31)
		ग_लिखोl_relaxed(0x1, irq_banks[1].va + IRQ_CONTROL_REG_OFFSET);

	ग_लिखोl_relaxed(0x1, irq_banks[0].va + IRQ_CONTROL_REG_OFFSET);
पूर्ण

अटल व्योम omap_mask_ack_irq(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);

	ct->chip.irq_mask(d);
	omap_ack_irq(d->irq);
पूर्ण

/*
 * Allows tuning the IRQ type and priority
 *
 * NOTE: There is currently no OMAP fiq handler क्रम Linux. Read the
 *	 mailing list thपढ़ोs on FIQ handlers अगर you are planning to
 *	 add a FIQ handler क्रम OMAP.
 */
अटल व्योम omap_irq_set_cfg(पूर्णांक irq, पूर्णांक fiq, पूर्णांक priority, पूर्णांक trigger)
अणु
	चिन्हित पूर्णांक bank;
	अचिन्हित दीर्घ val, offset;

	bank = IRQ_BANK(irq);
	/* FIQ is only available on bank 0 पूर्णांकerrupts */
	fiq = bank ? 0 : (fiq & 0x1);
	val = fiq | ((priority & 0x1f) << 2) | ((trigger & 0x1) << 1);
	offset = IRQ_ILR0_REG_OFFSET + IRQ_BIT(irq) * 0x4;
	irq_bank_ग_लिखोl(val, bank, offset);
पूर्ण

#अगर defined (CONFIG_ARCH_OMAP730) || defined (CONFIG_ARCH_OMAP850)
अटल काष्ठा omap_irq_bank omap7xx_irq_banks[] = अणु
	अणु .base_reg = OMAP_IH1_BASE,		.trigger_map = 0xb3f8e22f पूर्ण,
	अणु .base_reg = OMAP_IH2_BASE,		.trigger_map = 0xfdb9c1f2 पूर्ण,
	अणु .base_reg = OMAP_IH2_BASE + 0x100,	.trigger_map = 0x800040f3 पूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP15XX
अटल काष्ठा omap_irq_bank omap1510_irq_banks[] = अणु
	अणु .base_reg = OMAP_IH1_BASE,		.trigger_map = 0xb3febfff पूर्ण,
	अणु .base_reg = OMAP_IH2_BASE,		.trigger_map = 0xffbfffed पूर्ण,
पूर्ण;
अटल काष्ठा omap_irq_bank omap310_irq_banks[] = अणु
	अणु .base_reg = OMAP_IH1_BASE,		.trigger_map = 0xb3faefc3 पूर्ण,
	अणु .base_reg = OMAP_IH2_BASE,		.trigger_map = 0x65b3c061 पूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_OMAP16XX)

अटल काष्ठा omap_irq_bank omap1610_irq_banks[] = अणु
	अणु .base_reg = OMAP_IH1_BASE,		.trigger_map = 0xb3fefe8f पूर्ण,
	अणु .base_reg = OMAP_IH2_BASE,		.trigger_map = 0xfdb7c1fd पूर्ण,
	अणु .base_reg = OMAP_IH2_BASE + 0x100,	.trigger_map = 0xffffb7ff पूर्ण,
	अणु .base_reg = OMAP_IH2_BASE + 0x200,	.trigger_map = 0xffffffff पूर्ण,
पूर्ण;
#पूर्ण_अगर

यंत्रlinkage व्योम __exception_irq_entry omap1_handle_irq(काष्ठा pt_regs *regs)
अणु
	व्योम __iomem *l1 = irq_banks[0].va;
	व्योम __iomem *l2 = irq_banks[1].va;
	u32 irqnr;

	करो अणु
		irqnr = पढ़ोl_relaxed(l1 + IRQ_ITR_REG_OFFSET);
		irqnr &= ~(पढ़ोl_relaxed(l1 + IRQ_MIR_REG_OFFSET) & 0xffffffff);
		अगर (!irqnr)
			अवरोध;

		irqnr = पढ़ोl_relaxed(l1 + IRQ_SIR_FIQ_REG_OFFSET);
		अगर (irqnr)
			जाओ irq;

		irqnr = पढ़ोl_relaxed(l1 + IRQ_SIR_IRQ_REG_OFFSET);
		अगर (irqnr == omap_l2_irq) अणु
			irqnr = पढ़ोl_relaxed(l2 + IRQ_SIR_IRQ_REG_OFFSET);
			अगर (irqnr)
				irqnr += 32;
		पूर्ण
irq:
		अगर (irqnr)
			handle_करोमुख्य_irq(करोमुख्य, irqnr, regs);
		अन्यथा
			अवरोध;
	पूर्ण जबतक (irqnr);
पूर्ण

अटल __init व्योम
omap_alloc_gc(व्योम __iomem *base, अचिन्हित पूर्णांक irq_start, अचिन्हित पूर्णांक num)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;

	gc = irq_alloc_generic_chip("MPU", 1, irq_start, base,
				    handle_level_irq);
	ct = gc->chip_types;
	ct->chip.irq_ack = omap_mask_ack_irq;
	ct->chip.irq_mask = irq_gc_mask_set_bit;
	ct->chip.irq_unmask = irq_gc_mask_clr_bit;
	ct->chip.irq_set_wake = irq_gc_set_wake;
	ct->regs.mask = IRQ_MIR_REG_OFFSET;
	irq_setup_generic_chip(gc, IRQ_MSK(num), IRQ_GC_INIT_MASK_CACHE,
			       IRQ_NOREQUEST | IRQ_NOPROBE, 0);
पूर्ण

व्योम __init omap1_init_irq(व्योम)
अणु
	काष्ठा irq_chip_type *ct;
	काष्ठा irq_data *d = शून्य;
	पूर्णांक i, j, irq_base;
	अचिन्हित दीर्घ nr_irqs;

#अगर defined(CONFIG_ARCH_OMAP730) || defined(CONFIG_ARCH_OMAP850)
	अगर (cpu_is_omap7xx()) अणु
		irq_banks = omap7xx_irq_banks;
		irq_bank_count = ARRAY_SIZE(omap7xx_irq_banks);
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_OMAP15XX
	अगर (cpu_is_omap1510()) अणु
		irq_banks = omap1510_irq_banks;
		irq_bank_count = ARRAY_SIZE(omap1510_irq_banks);
	पूर्ण
	अगर (cpu_is_omap310()) अणु
		irq_banks = omap310_irq_banks;
		irq_bank_count = ARRAY_SIZE(omap310_irq_banks);
	पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_ARCH_OMAP16XX)
	अगर (cpu_is_omap16xx()) अणु
		irq_banks = omap1610_irq_banks;
		irq_bank_count = ARRAY_SIZE(omap1610_irq_banks);
	पूर्ण
#पूर्ण_अगर

	क्रम (i = 0; i < irq_bank_count; i++) अणु
		irq_banks[i].va = ioremap(irq_banks[i].base_reg, 0xff);
		अगर (WARN_ON(!irq_banks[i].va))
			वापस;
	पूर्ण

	nr_irqs = irq_bank_count * 32;

	irq_base = irq_alloc_descs(-1, 0, nr_irqs, 0);
	अगर (irq_base < 0) अणु
		pr_warn("Couldn't allocate IRQ numbers\n");
		irq_base = 0;
	पूर्ण
	omap_l2_irq = cpu_is_omap7xx() ? irq_base + 1 : irq_base;
	omap_l2_irq -= NR_IRQS_LEGACY;

	करोमुख्य = irq_करोमुख्य_add_legacy(शून्य, nr_irqs, irq_base, 0,
				       &irq_करोमुख्य_simple_ops, शून्य);

	pr_info("Total of %lu interrupts in %i interrupt banks\n",
		nr_irqs, irq_bank_count);

	/* Mask and clear all पूर्णांकerrupts */
	क्रम (i = 0; i < irq_bank_count; i++) अणु
		irq_bank_ग_लिखोl(~0x0, i, IRQ_MIR_REG_OFFSET);
		irq_bank_ग_लिखोl(0x0, i, IRQ_ITR_REG_OFFSET);
	पूर्ण

	/* Clear any pending पूर्णांकerrupts */
	irq_bank_ग_लिखोl(0x03, 0, IRQ_CONTROL_REG_OFFSET);
	irq_bank_ग_लिखोl(0x03, 1, IRQ_CONTROL_REG_OFFSET);

	/* Enable पूर्णांकerrupts in global mask */
	अगर (cpu_is_omap7xx())
		irq_bank_ग_लिखोl(0x0, 0, IRQ_GMR_REG_OFFSET);

	/* Install the पूर्णांकerrupt handlers क्रम each bank */
	क्रम (i = 0; i < irq_bank_count; i++) अणु
		क्रम (j = i * 32; j < (i + 1) * 32; j++) अणु
			पूर्णांक irq_trigger;

			irq_trigger = irq_banks[i].trigger_map >> IRQ_BIT(j);
			omap_irq_set_cfg(j, 0, 0, irq_trigger);
			irq_clear_status_flags(j, IRQ_NOREQUEST);
		पूर्ण
		omap_alloc_gc(irq_banks[i].va, irq_base + i * 32, 32);
	पूर्ण

	/* Unmask level 2 handler */
	d = irq_get_irq_data(irq_find_mapping(करोमुख्य, omap_l2_irq));
	अगर (d) अणु
		ct = irq_data_get_chip_type(d);
		ct->chip.irq_unmask(d);
	पूर्ण
पूर्ण
