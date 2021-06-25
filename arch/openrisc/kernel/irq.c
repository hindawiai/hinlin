<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OpenRISC irq.c
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * Modअगरications क्रम the OpenRISC architecture:
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/export.h>
#समावेश <linux/irqflags.h>

/* पढ़ो पूर्णांकerrupt enabled status */
अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	वापस mfspr(SPR_SR) & (SPR_SR_IEE|SPR_SR_TEE);
पूर्ण
EXPORT_SYMBOL(arch_local_save_flags);

/* set पूर्णांकerrupt enabled status */
व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	mtspr(SPR_SR, ((mfspr(SPR_SR) & ~(SPR_SR_IEE|SPR_SR_TEE)) | flags));
पूर्ण
EXPORT_SYMBOL(arch_local_irq_restore);

व्योम __init init_IRQ(व्योम)
अणु
	irqchip_init();
पूर्ण

व्योम __irq_entry करो_IRQ(काष्ठा pt_regs *regs)
अणु
	handle_arch_irq(regs);
पूर्ण
