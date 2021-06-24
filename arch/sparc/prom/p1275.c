<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * p1275.c: Sun IEEE 1275 PROM low level पूर्णांकerface routines
 *
 * Copyright (C) 1996,1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/माला.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/irqflags.h>

#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/spitfire.h>
#समावेश <यंत्र/pstate.h>
#समावेश <यंत्र/ldc.h>

काष्ठा अणु
	दीर्घ prom_callback;			/* 0x00 */
	व्योम (*prom_cअगर_handler)(दीर्घ *);	/* 0x08 */
पूर्ण p1275buf;

बाह्य व्योम prom_world(पूर्णांक);

बाह्य व्योम prom_cअगर_direct(अचिन्हित दीर्घ *args);
बाह्य व्योम prom_cअगर_callback(व्योम);

/*
 * This provides SMP safety on the p1275buf.
 */
DEFINE_RAW_SPINLOCK(prom_entry_lock);

व्योम p1275_cmd_direct(अचिन्हित दीर्घ *args)
अणु
	अचिन्हित दीर्घ flags;

	local_save_flags(flags);
	local_irq_restore((अचिन्हित दीर्घ)PIL_NMI);
	raw_spin_lock(&prom_entry_lock);

	prom_world(1);
	prom_cअगर_direct(args);
	prom_world(0);

	raw_spin_unlock(&prom_entry_lock);
	local_irq_restore(flags);
पूर्ण

व्योम prom_cअगर_init(व्योम *cअगर_handler, व्योम *cअगर_stack)
अणु
	p1275buf.prom_cअगर_handler = (व्योम (*)(दीर्घ *))cअगर_handler;
पूर्ण
