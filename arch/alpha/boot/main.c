<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/alpha/boot/मुख्य.c
 *
 * Copyright (C) 1994, 1995 Linus Torvalds
 *
 * This file is the bootloader क्रम the Linux/AXP kernel
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <generated/utsrelease.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/console.h>
#समावेश <यंत्र/hwrpb.h>

#समावेश <मानकतर्क.स>

#समावेश "ksize.h"

बाह्य अचिन्हित दीर्घ चयन_to_osf_pal(अचिन्हित दीर्घ nr,
	काष्ठा pcb_काष्ठा * pcb_va, काष्ठा pcb_काष्ठा * pcb_pa,
	अचिन्हित दीर्घ *vptb);
काष्ठा hwrpb_काष्ठा *hwrpb = INIT_HWRPB;
अटल काष्ठा pcb_काष्ठा pcb_va[1];

/*
 * Find a physical address of a भव object..
 *
 * This is easy using the भव page table address.
 */

अटल अंतरभूत व्योम *
find_pa(अचिन्हित दीर्घ *vptb, व्योम *ptr)
अणु
	अचिन्हित दीर्घ address = (अचिन्हित दीर्घ) ptr;
	अचिन्हित दीर्घ result;

	result = vptb[address >> 13];
	result >>= 32;
	result <<= 13;
	result |= address & 0x1fff;
	वापस (व्योम *) result;
पूर्ण	

/*
 * This function moves पूर्णांकo OSF/1 pal-code, and has a temporary
 * PCB क्रम that. The kernel proper should replace this PCB with
 * the real one as soon as possible.
 *
 * The page table muckery in here depends on the fact that the boot
 * code has the L1 page table identity-map itself in the second PTE
 * in the L1 page table. Thus the L1-page is भवly addressable
 * itself (through three levels) at भव address 0x200802000.
 */

#घोषणा VPTB	((अचिन्हित दीर्घ *) 0x200000000)
#घोषणा L1	((अचिन्हित दीर्घ *) 0x200802000)

व्योम
pal_init(व्योम)
अणु
	अचिन्हित दीर्घ i, rev;
	काष्ठा percpu_काष्ठा * percpu;
	काष्ठा pcb_काष्ठा * pcb_pa;

	/* Create the dummy PCB.  */
	pcb_va->ksp = 0;
	pcb_va->usp = 0;
	pcb_va->ptbr = L1[1] >> 32;
	pcb_va->asn = 0;
	pcb_va->pcc = 0;
	pcb_va->unique = 0;
	pcb_va->flags = 1;
	pcb_va->res1 = 0;
	pcb_va->res2 = 0;
	pcb_pa = find_pa(VPTB, pcb_va);

	/*
	 * a0 = 2 (OSF)
	 * a1 = वापस address, but we give the यंत्र the vaddr of the PCB
	 * a2 = physical addr of PCB
	 * a3 = new भव page table poपूर्णांकer
	 * a4 = KSP (but the यंत्र sets it)
	 */
	srm_prपूर्णांकk("Switching to OSF PAL-code .. ");

	i = चयन_to_osf_pal(2, pcb_va, pcb_pa, VPTB);
	अगर (i) अणु
		srm_prपूर्णांकk("failed, code %ld\n", i);
		__halt();
	पूर्ण

	percpu = (काष्ठा percpu_काष्ठा *)
		(INIT_HWRPB->processor_offset + (अचिन्हित दीर्घ) INIT_HWRPB);
	rev = percpu->pal_revision = percpu->palcode_avail[2];

	srm_prपूर्णांकk("Ok (rev %lx)\n", rev);

	tbia(); /* करो it directly in हाल we are SMP */
पूर्ण

अटल अंतरभूत दीर्घ खोलोboot(व्योम)
अणु
	अक्षर bootdev[256];
	दीर्घ result;

	result = callback_दो_पर्या(ENV_BOOTED_DEV, bootdev, 255);
	अगर (result < 0)
		वापस result;
	वापस callback_खोलो(bootdev, result & 255);
पूर्ण

अटल अंतरभूत दीर्घ बंद(दीर्घ dev)
अणु
	वापस callback_बंद(dev);
पूर्ण

अटल अंतरभूत दीर्घ load(दीर्घ dev, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ count)
अणु
	अक्षर bootfile[256];
	बाह्य अक्षर _end;
	दीर्घ result, boot_size = &_end - (अक्षर *) BOOT_ADDR;

	result = callback_दो_पर्या(ENV_BOOTED_खाता, bootfile, 255);
	अगर (result < 0)
		वापस result;
	result &= 255;
	bootfile[result] = '\0';
	अगर (result)
		srm_prपूर्णांकk("Boot file specification (%s) not implemented\n",
		       bootfile);
	वापस callback_पढ़ो(dev, count, (व्योम *)addr, boot_size/512 + 1);
पूर्ण

/*
 * Start the kernel.
 */
अटल व्योम runkernel(व्योम)
अणु
	__यंत्र__ __अस्थिर__(
		"bis %1,%1,$30\n\t"
		"bis %0,%0,$26\n\t"
		"ret ($26)"
		: /* no outमाला_दो: it करोesn't even वापस */
		: "r" (START_ADDR),
		  "r" (PAGE_SIZE + INIT_STACK));
पूर्ण

व्योम start_kernel(व्योम)
अणु
	दीर्घ i;
	दीर्घ dev;
	पूर्णांक nbytes;
	अक्षर envval[256];

	srm_prपूर्णांकk("Linux/AXP bootloader for Linux " UTS_RELEASE "\n");
	अगर (INIT_HWRPB->pagesize != 8192) अणु
		srm_prपूर्णांकk("Expected 8kB pages, got %ldkB\n", INIT_HWRPB->pagesize >> 10);
		वापस;
	पूर्ण
	pal_init();
	dev = खोलोboot();
	अगर (dev < 0) अणु
		srm_prपूर्णांकk("Unable to open boot device: %016lx\n", dev);
		वापस;
	पूर्ण
	dev &= 0xffffffff;
	srm_prपूर्णांकk("Loading vmlinux ...");
	i = load(dev, START_ADDR, KERNEL_SIZE);
	बंद(dev);
	अगर (i != KERNEL_SIZE) अणु
		srm_prपूर्णांकk("Failed (%lx)\n", i);
		वापस;
	पूर्ण

	nbytes = callback_दो_पर्या(ENV_BOOTED_OSFLAGS, envval, माप(envval));
	अगर (nbytes < 0) अणु
		nbytes = 0;
	पूर्ण
	envval[nbytes] = '\0';
	म_नकल((अक्षर*)ZERO_PGE, envval);

	srm_prपूर्णांकk(" Ok\nNow booting the kernel\n");
	runkernel();
	क्रम (i = 0 ; i < 0x100000000 ; i++)
		/* nothing */;
	__halt();
पूर्ण
