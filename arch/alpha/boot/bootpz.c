<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/alpha/boot/bootpz.c
 *
 * Copyright (C) 1997 Jay Estabrook
 *
 * This file is used क्रम creating a compressed BOOTP file क्रम the
 * Linux/AXP kernel
 *
 * based signअगरicantly on the arch/alpha/boot/मुख्य.c of Linus Torvalds
 * and the decompression code from MILO.
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

#समावेश "kzsize.h"

/* FIXME FIXME FIXME */
#घोषणा MALLOC_AREA_SIZE 0x200000 /* 2MB क्रम now */
/* FIXME FIXME FIXME */


/*
  WARNING NOTE

  It is very possible that turning on additional messages may cause
  kernel image corruption due to stack usage to करो the prपूर्णांकing.

*/

#अघोषित DEBUG_CHECK_RANGE
#अघोषित DEBUG_ADDRESSES
#अघोषित DEBUG_LAST_STEPS

बाह्य अचिन्हित दीर्घ चयन_to_osf_pal(अचिन्हित दीर्घ nr,
	काष्ठा pcb_काष्ठा * pcb_va, काष्ठा pcb_काष्ठा * pcb_pa,
	अचिन्हित दीर्घ *vptb);

बाह्य पूर्णांक decompress_kernel(व्योम* destination, व्योम *source,
			     माप_प्रकार ksize, माप_प्रकार kzsize);

बाह्य व्योम move_stack(अचिन्हित दीर्घ new_stack);

काष्ठा hwrpb_काष्ठा *hwrpb = INIT_HWRPB;
अटल काष्ठा pcb_काष्ठा pcb_va[1];

/*
 * Find a physical address of a भव object..
 *
 * This is easy using the भव page table address.
 */
#घोषणा VPTB	((अचिन्हित दीर्घ *) 0x200000000)

अटल अंतरभूत अचिन्हित दीर्घ
find_pa(अचिन्हित दीर्घ address)
अणु
	अचिन्हित दीर्घ result;

	result = VPTB[address >> 13];
	result >>= 32;
	result <<= 13;
	result |= address & 0x1fff;
	वापस result;
पूर्ण	

पूर्णांक
check_range(अचिन्हित दीर्घ vstart, अचिन्हित दीर्घ vend,
	    अचिन्हित दीर्घ kstart, अचिन्हित दीर्घ kend)
अणु
	अचिन्हित दीर्घ vaddr, kaddr;

#अगर_घोषित DEBUG_CHECK_RANGE
	srm_prपूर्णांकk("check_range: V[0x%lx:0x%lx] K[0x%lx:0x%lx]\n",
		   vstart, vend, kstart, kend);
#पूर्ण_अगर
	/* करो some range checking क्रम detecting an overlap... */
	क्रम (vaddr = vstart; vaddr <= vend; vaddr += PAGE_SIZE)
	अणु
		kaddr = (find_pa(vaddr) | PAGE_OFFSET);
		अगर (kaddr >= kstart && kaddr <= kend)
		अणु
#अगर_घोषित DEBUG_CHECK_RANGE
			srm_prपूर्णांकk("OVERLAP: vaddr 0x%lx kaddr 0x%lx"
				   " [0x%lx:0x%lx]\n",
				   vaddr, kaddr, kstart, kend);
#पूर्ण_अगर
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
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
	pcb_pa = (काष्ठा pcb_काष्ठा *)find_pa((अचिन्हित दीर्घ)pcb_va);

	/*
	 * a0 = 2 (OSF)
	 * a1 = वापस address, but we give the यंत्र the vaddr of the PCB
	 * a2 = physical addr of PCB
	 * a3 = new भव page table poपूर्णांकer
	 * a4 = KSP (but the यंत्र sets it)
	 */
	srm_prपूर्णांकk("Switching to OSF PAL-code... ");

	i = चयन_to_osf_pal(2, pcb_va, pcb_pa, VPTB);
	अगर (i) अणु
		srm_prपूर्णांकk("failed, code %ld\n", i);
		__halt();
	पूर्ण

	percpu = (काष्ठा percpu_काष्ठा *)
		(INIT_HWRPB->processor_offset + (अचिन्हित दीर्घ) INIT_HWRPB);
	rev = percpu->pal_revision = percpu->palcode_avail[2];

	srm_prपूर्णांकk("OK (rev %lx)\n", rev);

	tbia(); /* करो it directly in हाल we are SMP */
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

/* Must record the SP (it is भव) on entry, so we can make sure
   not to overग_लिखो it during movement or decompression. */
अचिन्हित दीर्घ SP_on_entry;

/* Calculate the kernel image address based on the end of the BOOTP
   bootstrapper (ie this program).
*/
बाह्य अक्षर _end;
#घोषणा KERNEL_ORIGIN \
	((((अचिन्हित दीर्घ)&_end) + 511) & ~511)

/* Round address to next higher page boundary. */
#घोषणा NEXT_PAGE(a)	(((a) | (PAGE_SIZE - 1)) + 1)

#अगर_घोषित INITRD_IMAGE_SIZE
# define REAL_INITRD_SIZE INITRD_IMAGE_SIZE
#अन्यथा
# define REAL_INITRD_SIZE 0
#पूर्ण_अगर

/* Defines from include/यंत्र-alpha/प्रणाली.h

	BOOT_ADDR	Virtual address at which the consoles loads
			the BOOTP image.

	KERNEL_START    KSEG address at which the kernel is built to run,
			which includes some initial data pages beक्रमe the
			code.

	START_ADDR	KSEG address of the entry poपूर्णांक of kernel code.

	ZERO_PGE	KSEG address of page full of zeroes, but 
			upon entry to kerne cvan be expected
			to hold the parameter list and possible
			INTRD inक्रमmation.

   These are used in the local defines below.
*/
  

/* Virtual addresses क्रम the BOOTP image. Note that this includes the
   bootstrapper code as well as the compressed kernel image, and
   possibly the INITRD image.

   Oh, and करो NOT क्रमget the STACK, which appears to be placed भवly
   beyond the end of the loaded image.
*/
#घोषणा V_BOOT_IMAGE_START	BOOT_ADDR
#घोषणा V_BOOT_IMAGE_END	SP_on_entry

/* Virtual addresses क्रम just the bootstrapper part of the BOOTP image. */
#घोषणा V_BOOTSTRAPPER_START	BOOT_ADDR
#घोषणा V_BOOTSTRAPPER_END	KERNEL_ORIGIN

/* Virtual addresses क्रम just the data part of the BOOTP
   image. This may also include the INITRD image, but always
   includes the STACK.
*/
#घोषणा V_DATA_START		KERNEL_ORIGIN
#घोषणा V_INITRD_START		(KERNEL_ORIGIN + KERNEL_Z_SIZE)
#घोषणा V_INTRD_END		(V_INITRD_START + REAL_INITRD_SIZE)
#घोषणा V_DATA_END	 	V_BOOT_IMAGE_END

/* KSEG addresses क्रम the uncompressed kernel.

   Note that the end address includes workspace क्रम the decompression.
   Note also that the DATA_START address is ZERO_PGE, to which we ग_लिखो
   just beक्रमe jumping to the kernel image at START_ADDR.
 */
#घोषणा K_KERNEL_DATA_START	ZERO_PGE
#घोषणा K_KERNEL_IMAGE_START	START_ADDR
#घोषणा K_KERNEL_IMAGE_END	(START_ADDR + KERNEL_SIZE)

/* Define to where we may have to decompress the kernel image, beक्रमe
   we move it to the final position, in हाल of overlap. This will be
   above the final position of the kernel.

   Regardless of overlap, we move the INITRD image to the end of this
   copy area, because there needs to be a buffer area after the kernel
   क्रम "bootmem" anyway.
*/
#घोषणा K_COPY_IMAGE_START	NEXT_PAGE(K_KERNEL_IMAGE_END)
/* Reserve one page below INITRD क्रम the new stack. */
#घोषणा K_INITRD_START \
    NEXT_PAGE(K_COPY_IMAGE_START + KERNEL_SIZE + PAGE_SIZE)
#घोषणा K_COPY_IMAGE_END \
    (K_INITRD_START + REAL_INITRD_SIZE + MALLOC_AREA_SIZE)
#घोषणा K_COPY_IMAGE_SIZE \
    NEXT_PAGE(K_COPY_IMAGE_END - K_COPY_IMAGE_START)

व्योम
start_kernel(व्योम)
अणु
	पूर्णांक must_move = 0;

	/* Initialize these क्रम the decompression-in-place situation,
	   which is the smallest amount of work and most likely to
	   occur when using the normal START_ADDR of the kernel
	   (currently set to 16MB, to clear all console code.
	*/
	अचिन्हित दीर्घ uncompressed_image_start = K_KERNEL_IMAGE_START;
	अचिन्हित दीर्घ uncompressed_image_end = K_KERNEL_IMAGE_END;

	अचिन्हित दीर्घ initrd_image_start = K_INITRD_START;

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
	रेजिस्टर अचिन्हित दीर्घ यंत्र_sp यंत्र("30");

	SP_on_entry = यंत्र_sp;

	srm_prपूर्णांकk("Linux/Alpha BOOTPZ Loader for Linux " UTS_RELEASE "\n");

	/* Validity check the HWRPB. */
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

	/* PALcode (re)initialization. */
	pal_init();

	/* Get the parameter list from the console environment variable. */
	nbytes = callback_दो_पर्या(ENV_BOOTED_OSFLAGS, envval, माप(envval));
	अगर (nbytes < 0 || nbytes >= माप(envval)) अणु
		nbytes = 0;
	पूर्ण
	envval[nbytes] = '\0';

#अगर_घोषित DEBUG_ADDRESSES
	srm_prपूर्णांकk("START_ADDR 0x%lx\n", START_ADDR);
	srm_prपूर्णांकk("KERNEL_ORIGIN 0x%lx\n", KERNEL_ORIGIN);
	srm_prपूर्णांकk("KERNEL_SIZE 0x%x\n", KERNEL_SIZE);
	srm_prपूर्णांकk("KERNEL_Z_SIZE 0x%x\n", KERNEL_Z_SIZE);
#पूर्ण_अगर

	/* Since all the SRM consoles load the BOOTP image at भव
	 * 0x20000000, we have to ensure that the physical memory
	 * pages occupied by that image करो NOT overlap the physical
	 * address range where the kernel wants to be run.  This
	 * causes real problems when attempting to cdecompress the
	 * क्रमmer पूर्णांकo the latter... :-(
	 *
	 * So, we may have to decompress/move the kernel/INITRD image
	 * भव-to-physical someplace अन्यथा first beक्रमe moving
	 * kernel /INITRD to their final resting places... ;-पूर्ण
	 *
	 * Sigh...
	 */

	/* First, check to see अगर the range of addresses occupied by
	   the bootstrapper part of the BOOTP image include any of the
	   physical pages पूर्णांकo which the kernel will be placed क्रम
	   execution.

	   We only need check on the final kernel image range, since we
	   will put the INITRD someplace that we can be sure is not
	   in conflict.
	 */
	अगर (check_range(V_BOOTSTRAPPER_START, V_BOOTSTRAPPER_END,
			K_KERNEL_DATA_START, K_KERNEL_IMAGE_END))
	अणु
		srm_prपूर्णांकk("FATAL ERROR: overlap of bootstrapper code\n");
		__halt();
	पूर्ण

	/* Next, check to see अगर the range of addresses occupied by
	   the compressed kernel/INITRD/stack portion of the BOOTP
	   image include any of the physical pages पूर्णांकo which the
	   decompressed kernel or the INITRD will be placed क्रम
	   execution.
	 */
	अगर (check_range(V_DATA_START, V_DATA_END,
			K_KERNEL_IMAGE_START, K_COPY_IMAGE_END))
	अणु
#अगर_घोषित DEBUG_ADDRESSES
		srm_prपूर्णांकk("OVERLAP: cannot decompress in place\n");
#पूर्ण_अगर
		uncompressed_image_start = K_COPY_IMAGE_START;
		uncompressed_image_end = K_COPY_IMAGE_END;
		must_move = 1;

		/* Finally, check to see अगर the range of addresses
		   occupied by the compressed kernel/INITRD part of
		   the BOOTP image include any of the physical pages
		   पूर्णांकo which that part is to be copied क्रम
		   decompression.
		*/
		जबतक (check_range(V_DATA_START, V_DATA_END,
				   uncompressed_image_start,
				   uncompressed_image_end))
		अणु
#अगर 0
			uncompressed_image_start += K_COPY_IMAGE_SIZE;
			uncompressed_image_end += K_COPY_IMAGE_SIZE;
			initrd_image_start += K_COPY_IMAGE_SIZE;
#अन्यथा
			/* Keep as बंद as possible to end of BOOTP image. */
			uncompressed_image_start += PAGE_SIZE;
			uncompressed_image_end += PAGE_SIZE;
			initrd_image_start += PAGE_SIZE;
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	srm_prपूर्णांकk("Starting to load the kernel with args '%s'\n", envval);

#अगर_घोषित DEBUG_ADDRESSES
	srm_prपूर्णांकk("Decompressing the kernel...\n"
		   "...from 0x%lx to 0x%lx size 0x%x\n",
		   V_DATA_START,
		   uncompressed_image_start,
		   KERNEL_SIZE);
#पूर्ण_अगर
        decompress_kernel((व्योम *)uncompressed_image_start,
			  (व्योम *)V_DATA_START,
			  KERNEL_SIZE, KERNEL_Z_SIZE);

	/*
	 * Now, move things to their final positions, अगर/as required.
	 */

#अगर_घोषित INITRD_IMAGE_SIZE

	/* First, we always move the INITRD image, अगर present. */
#अगर_घोषित DEBUG_ADDRESSES
	srm_prपूर्णांकk("Moving the INITRD image...\n"
		   " from 0x%lx to 0x%lx size 0x%x\n",
		   V_INITRD_START,
		   initrd_image_start,
		   INITRD_IMAGE_SIZE);
#पूर्ण_अगर
	स_नकल((व्योम *)initrd_image_start, (व्योम *)V_INITRD_START,
	       INITRD_IMAGE_SIZE);

#पूर्ण_अगर /* INITRD_IMAGE_SIZE */

	/* Next, we may have to move the uncompressed kernel to the
	   final destination.
	 */
	अगर (must_move) अणु
#अगर_घोषित DEBUG_ADDRESSES
		srm_prपूर्णांकk("Moving the uncompressed kernel...\n"
			   "...from 0x%lx to 0x%lx size 0x%x\n",
			   uncompressed_image_start,
			   K_KERNEL_IMAGE_START,
			   (अचिन्हित)KERNEL_SIZE);
#पूर्ण_अगर
		/*
		 * Move the stack to a safe place to ensure it won't be
		 * overwritten by kernel image.
		 */
		move_stack(initrd_image_start - PAGE_SIZE);

		स_नकल((व्योम *)K_KERNEL_IMAGE_START,
		       (व्योम *)uncompressed_image_start, KERNEL_SIZE);
	पूर्ण
	
	/* Clear the zero page, then move the argument list in. */
#अगर_घोषित DEBUG_LAST_STEPS
	srm_prपूर्णांकk("Preparing ZERO_PGE...\n");
#पूर्ण_अगर
	स_रखो((अक्षर*)ZERO_PGE, 0, PAGE_SIZE);
	म_नकल((अक्षर*)ZERO_PGE, envval);

#अगर_घोषित INITRD_IMAGE_SIZE

#अगर_घोषित DEBUG_LAST_STEPS
	srm_prपूर्णांकk("Preparing INITRD info...\n");
#पूर्ण_अगर
	/* Finally, set the INITRD paramenters क्रम the kernel. */
	((दीर्घ *)(ZERO_PGE+256))[0] = initrd_image_start;
	((दीर्घ *)(ZERO_PGE+256))[1] = INITRD_IMAGE_SIZE;

#पूर्ण_अगर /* INITRD_IMAGE_SIZE */

#अगर_घोषित DEBUG_LAST_STEPS
	srm_prपूर्णांकk("Doing 'runkernel()'...\n");
#पूर्ण_अगर
	runkernel();
पूर्ण

 /* dummy function, should never be called. */
व्योम *__kदो_स्मृति(माप_प्रकार size, gfp_t flags)
अणु
	वापस (व्योम *)शून्य;
पूर्ण
