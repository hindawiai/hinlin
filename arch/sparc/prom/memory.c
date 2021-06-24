<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* memory.c: Prom routine क्रम acquiring various bits of inक्रमmation
 *           about RAM on the machine, both भव and physical.
 *
 * Copyright (C) 1995, 2008 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1997 Michael A. Grअगरfith (grअगर@acm.org)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sort.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/page.h>

अटल पूर्णांक __init prom_meminit_v0(व्योम)
अणु
	काष्ठा linux_mlist_v0 *p;
	पूर्णांक index;

	index = 0;
	क्रम (p = *(romvec->pv_v0mem.v0_available); p; p = p->theres_more) अणु
		sp_banks[index].base_addr = (अचिन्हित दीर्घ) p->start_adr;
		sp_banks[index].num_bytes = p->num_bytes;
		index++;
	पूर्ण

	वापस index;
पूर्ण

अटल पूर्णांक __init prom_meminit_v2(व्योम)
अणु
	काष्ठा linux_prom_रेजिस्टरs reg[64];
	phandle node;
	पूर्णांक size, num_ents, i;

	node = prom_searchsiblings(prom_अ_लोhild(prom_root_node), "memory");
	size = prom_getproperty(node, "available", (अक्षर *) reg, माप(reg));
	num_ents = size / माप(काष्ठा linux_prom_रेजिस्टरs);

	क्रम (i = 0; i < num_ents; i++) अणु
		sp_banks[i].base_addr = reg[i].phys_addr;
		sp_banks[i].num_bytes = reg[i].reg_size;
	पूर्ण

	वापस num_ents;
पूर्ण

अटल पूर्णांक sp_banks_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा sparc_phys_banks *x = a, *y = b;

	अगर (x->base_addr > y->base_addr)
		वापस 1;
	अगर (x->base_addr < y->base_addr)
		वापस -1;
	वापस 0;
पूर्ण

/* Initialize the memory lists based upon the prom version. */
व्योम __init prom_meminit(व्योम)
अणु
	पूर्णांक i, num_ents = 0;

	चयन (prom_vers) अणु
	हाल PROM_V0:
		num_ents = prom_meminit_v0();
		अवरोध;

	हाल PROM_V2:
	हाल PROM_V3:
		num_ents = prom_meminit_v2();
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	sort(sp_banks, num_ents, माप(काष्ठा sparc_phys_banks),
	     sp_banks_cmp, शून्य);

	/* Sentinel.  */
	sp_banks[num_ents].base_addr = 0xdeadbeef;
	sp_banks[num_ents].num_bytes = 0;

	क्रम (i = 0; i < num_ents; i++)
		sp_banks[i].num_bytes &= PAGE_MASK;
पूर्ण
