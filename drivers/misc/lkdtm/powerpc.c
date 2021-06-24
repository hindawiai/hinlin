<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश "lkdtm.h"
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/mmu.h>

/* Inserts new slb entries */
अटल व्योम insert_slb_entry(अचिन्हित दीर्घ p, पूर्णांक ssize, पूर्णांक page_size)
अणु
	अचिन्हित दीर्घ flags;

	flags = SLB_VSID_KERNEL | mmu_psize_defs[page_size].sllp;
	preempt_disable();

	यंत्र अस्थिर("slbmte %0,%1" :
		     : "r" (mk_vsid_data(p, ssize, flags)),
		       "r" (mk_esid_data(p, ssize, SLB_NUM_BOLTED))
		     : "memory");

	यंत्र अस्थिर("slbmte %0,%1" :
			: "r" (mk_vsid_data(p, ssize, flags)),
			  "r" (mk_esid_data(p, ssize, SLB_NUM_BOLTED + 1))
			: "memory");
	preempt_enable();
पूर्ण

/* Inject slb multihit on vदो_स्मृति-ed address i.e 0xD00... */
अटल पूर्णांक inject_vदो_स्मृति_slb_multihit(व्योम)
अणु
	अक्षर *p;

	p = vदो_स्मृति(PAGE_SIZE);
	अगर (!p)
		वापस -ENOMEM;

	insert_slb_entry((अचिन्हित दीर्घ)p, MMU_SEGSIZE_1T, mmu_vदो_स्मृति_psize);
	/*
	 * This triggers exception, If handled correctly we must recover
	 * from this error.
	 */
	p[0] = '!';
	vमुक्त(p);
	वापस 0;
पूर्ण

/* Inject slb multihit on kदो_स्मृति-ed address i.e 0xC00... */
अटल पूर्णांक inject_kदो_स्मृति_slb_multihit(व्योम)
अणु
	अक्षर *p;

	p = kदो_स्मृति(2048, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	insert_slb_entry((अचिन्हित दीर्घ)p, MMU_SEGSIZE_1T, mmu_linear_psize);
	/*
	 * This triggers exception, If handled correctly we must recover
	 * from this error.
	 */
	p[0] = '!';
	kमुक्त(p);
	वापस 0;
पूर्ण

/*
 * Few initial SLB entries are bolted. Add a test to inject
 * multihit in bolted entry 0.
 */
अटल व्योम insert_dup_slb_entry_0(व्योम)
अणु
	अचिन्हित दीर्घ test_address = PAGE_OFFSET, *test_ptr;
	अचिन्हित दीर्घ esid, vsid;
	अचिन्हित दीर्घ i = 0;

	test_ptr = (अचिन्हित दीर्घ *)test_address;
	preempt_disable();

	यंत्र अस्थिर("slbmfee  %0,%1" : "=r" (esid) : "r" (i));
	यंत्र अस्थिर("slbmfev  %0,%1" : "=r" (vsid) : "r" (i));

	/* क्रम i !=0 we would need to mask out the old entry number */
	यंत्र अस्थिर("slbmte %0,%1" :
			: "r" (vsid),
			  "r" (esid | SLB_NUM_BOLTED)
			: "memory");

	यंत्र अस्थिर("slbmfee  %0,%1" : "=r" (esid) : "r" (i));
	यंत्र अस्थिर("slbmfev  %0,%1" : "=r" (vsid) : "r" (i));

	/* क्रम i !=0 we would need to mask out the old entry number */
	यंत्र अस्थिर("slbmte %0,%1" :
			: "r" (vsid),
			  "r" (esid | (SLB_NUM_BOLTED + 1))
			: "memory");

	pr_info("%s accessing test address 0x%lx: 0x%lx\n",
		__func__, test_address, *test_ptr);

	preempt_enable();
पूर्ण

व्योम lkdपंचांग_PPC_SLB_MULTIHIT(व्योम)
अणु
	अगर (!radix_enabled()) अणु
		pr_info("Injecting SLB multihit errors\n");
		/*
		 * These need not be separate tests, And they करो pretty
		 * much same thing. In any हाल we must recover from the
		 * errors पूर्णांकroduced by these functions, machine would not
		 * survive these tests in हाल of failure to handle.
		 */
		inject_vदो_स्मृति_slb_multihit();
		inject_kदो_स्मृति_slb_multihit();
		insert_dup_slb_entry_0();
		pr_info("Recovered from SLB multihit errors\n");
	पूर्ण अन्यथा अणु
		pr_err("XFAIL: This test is for ppc64 and with hash mode MMU only\n");
	पूर्ण
पूर्ण
