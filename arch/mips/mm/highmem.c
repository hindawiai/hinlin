<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/tlbflush.h>

अचिन्हित दीर्घ highstart_pfn, highend_pfn;

व्योम kmap_flush_tlb(अचिन्हित दीर्घ addr)
अणु
	flush_tlb_one(addr);
पूर्ण
EXPORT_SYMBOL(kmap_flush_tlb);
