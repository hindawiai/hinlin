<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PS3 System Manager core.
 *
 *  Copyright (C) 2007 Sony Computer Entertainment Inc.
 *  Copyright 2007 Sony Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/lv1call.h>
#समावेश <यंत्र/ps3.h>

/**
 * Staticly linked routines that allow late binding of a loaded sys-manager
 * module.
 */

अटल काष्ठा ps3_sys_manager_ops ps3_sys_manager_ops;

/**
 * ps3_रेजिस्टर_sys_manager_ops - Bind ps3_sys_manager_ops to a module.
 * @ops: काष्ठा ps3_sys_manager_ops.
 *
 * To be called from ps3_sys_manager_probe() and ps3_sys_manager_हटाओ() to
 * रेजिस्टर call back ops क्रम घातer control.  Copies data to the अटल
 * variable ps3_sys_manager_ops.
 */

व्योम ps3_sys_manager_रेजिस्टर_ops(स्थिर काष्ठा ps3_sys_manager_ops *ops)
अणु
	BUG_ON(!ops);
	BUG_ON(!ops->dev);
	ps3_sys_manager_ops = *ops;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_sys_manager_रेजिस्टर_ops);

व्योम __noवापस ps3_sys_manager_घातer_off(व्योम)
अणु
	अगर (ps3_sys_manager_ops.घातer_off)
		ps3_sys_manager_ops.घातer_off(ps3_sys_manager_ops.dev);

	ps3_sys_manager_halt();
पूर्ण

व्योम __noवापस ps3_sys_manager_restart(व्योम)
अणु
	अगर (ps3_sys_manager_ops.restart)
		ps3_sys_manager_ops.restart(ps3_sys_manager_ops.dev);

	ps3_sys_manager_halt();
पूर्ण

व्योम __noवापस ps3_sys_manager_halt(व्योम)
अणु
	pr_emerg("System Halted, OK to turn off power\n");
	local_irq_disable();
	जबतक (1)
		lv1_छोड़ो(1);
पूर्ण

