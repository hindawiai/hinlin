<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/alpha/boot/bootp.c
 *
 * Copyright (C) 1997 Jay Estabrook
 *
 * This file is used क्रम creating a bootp file क्रम the Linux/AXP kernel
 *
 * based signअगरicantly on the arch/alpha/boot/मुख्य.c of Linus Torvalds
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <generated/utsrelease.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/console.h>
#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/पन.स>

#समावेश <मानकतर्क.स>

#समावेश "ksize.h"

बाह्य अचिन्हित दीर्घ चयन_to_osf_pal(अचिन्हित दीर्घ nr,
	काष्ठा pcb_काष्ठा * pcb_va, काष्ठा pcb_काष्ठा * pcb_pa,
	अचिन्हित दीर्घ *vptb);

बाह्य व्योम move_stack(अचिन्हित दीर्घ new_stack);

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

अटल अंतरभूत व्योम
load(अचिन्हित दीर्घ dst, अचिन्हित दीर्घ src, अचिन्हित दीर्घ count)
अणु
	स_नकल((व्योम *)dst, (व्योम *)src, count);
पूर्ण

/*
 * Start the kernel.
 */
अटल अंतरभूत व्योम
runkernel(व्योम)
अणु
	__यंत्र__ __अस्थिर__(
		"bis %0,%0,$27\n\t"
		"jmp ($27)"
		: /* no outमाला_दो: it करोesn't even वापस */
		: "r" (START_ADDR));
पूर्ण

बाह्य अक्षर _end;
#घोषणा KERNEL_ORIGIN \
	((((अचिन्हित दीर्घ)&_end) + 511) & ~511)

व्योम
start_kernel(व्योम)
अणु
	/*
	 * Note that this crufty stuff with अटल and envval
	 * and envbuf is because:
	 *
	 * 1. Frequently, the stack is लघु, and we करोn't want to overrun;
	 * 2. Frequently the stack is where we are going to copy the kernel to;
	 * 3. A certain SRM console required the GET_ENV output to stack.
	 *    ??? A comment in the aboot sources indicates that the GET_ENV
	 *    destination must be quadword aligned.  Might this explain the
	 *    behaviour, rather than requiring output to the stack, which
	 *    seems rather far-fetched.
	 */
	अटल दीर्घ nbytes;
	अटल अक्षर envval[256] __attribute__((aligned(8)));
	अटल अचिन्हित दीर्घ initrd_start;

	srm_prपूर्णांकk("Linux/AXP bootp loader for Linux " UTS_RELEASE "\n");
	अगर (INIT_HWRPB->pagesize != 8192) अणु
		srm_prपूर्णांकk("Expected 8kB pages, got %ldkB\n",
		           INIT_HWRPB->pagesize >> 10);
		वापस;
	पूर्ण
	अगर (INIT_HWRPB->vptb != (अचिन्हित दीर्घ) VPTB) अणु
		srm_prपूर्णांकk("Expected vptb at %p, got %p\n",
			   VPTB, (व्योम *)INIT_HWRPB->vptb);
		वापस;
	पूर्ण
	pal_init();

	/* The initrd must be page-aligned.  See below क्रम the 
	   cause of the magic number 5.  */
	initrd_start = ((START_ADDR + 5*KERNEL_SIZE + PAGE_SIZE) |
			(PAGE_SIZE-1)) + 1;
#अगर_घोषित INITRD_IMAGE_SIZE
	srm_prपूर्णांकk("Initrd positioned at %#lx\n", initrd_start);
#पूर्ण_अगर

	/*
	 * Move the stack to a safe place to ensure it won't be
	 * overwritten by kernel image.
	 */
	move_stack(initrd_start - PAGE_SIZE);

	nbytes = callback_दो_पर्या(ENV_BOOTED_OSFLAGS, envval, माप(envval));
	अगर (nbytes < 0 || nbytes >= माप(envval)) अणु
		nbytes = 0;
	पूर्ण
	envval[nbytes] = '\0';
	srm_prपूर्णांकk("Loading the kernel...'%s'\n", envval);

	/* NOTE: *no* callbacks or prपूर्णांकouts from here on out!!! */

	/* This is a hack, as some consoles seem to get भव 20000000 (ie
	 * where the SRM console माला_दो the kernel bootp image) memory
	 * overlapping physical memory where the kernel wants to be put,
	 * which causes real problems when attempting to copy the क्रमmer to
	 * the latter... :-(
	 *
	 * So, we first move the kernel भव-to-physical way above where
	 * we physically want the kernel to end up, then copy it from there
	 * to its final resting place... ;-पूर्ण
	 *
	 * Sigh...  */

#अगर_घोषित INITRD_IMAGE_SIZE
	load(initrd_start, KERNEL_ORIGIN+KERNEL_SIZE, INITRD_IMAGE_SIZE);
#पूर्ण_अगर
        load(START_ADDR+(4*KERNEL_SIZE), KERNEL_ORIGIN, KERNEL_SIZE);
        load(START_ADDR, START_ADDR+(4*KERNEL_SIZE), KERNEL_SIZE);

	स_रखो((अक्षर*)ZERO_PGE, 0, PAGE_SIZE);
	म_नकल((अक्षर*)ZERO_PGE, envval);
#अगर_घोषित INITRD_IMAGE_SIZE
	((दीर्घ *)(ZERO_PGE+256))[0] = initrd_start;
	((दीर्घ *)(ZERO_PGE+256))[1] = INITRD_IMAGE_SIZE;
#पूर्ण_अगर

	runkernel();
पूर्ण
