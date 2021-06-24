<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Memory Encryption Support
 *
 * Copyright (C) 2016 Advanced Micro Devices, Inc.
 *
 * Author: Tom Lendacky <thomas.lendacky@amd.com>
 */

#घोषणा DISABLE_BRANCH_PROFILING

/*
 * Since we're dealing with identity mappings, physical and भव
 * addresses are the same, so override these defines which are ultimately
 * used by the headers in misc.h.
 */
#घोषणा __pa(x)  ((अचिन्हित दीर्घ)(x))
#घोषणा __va(x)  ((व्योम *)((अचिन्हित दीर्घ)(x)))

/*
 * Special hack: we have to be careful, because no indirections are
 * allowed here, and paravirt_ops is a kind of one. As it will only run in
 * baremetal anyway, we just keep it from happening. (This list needs to
 * be extended when new paravirt and debugging variants are added.)
 */
#अघोषित CONFIG_PARAVIRT
#अघोषित CONFIG_PARAVIRT_XXL
#अघोषित CONFIG_PARAVIRT_SPINLOCKS

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/mem_encrypt.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/cmdline.h>

#समावेश "mm_internal.h"

#घोषणा PGD_FLAGS		_KERNPG_TABLE_NOENC
#घोषणा P4D_FLAGS		_KERNPG_TABLE_NOENC
#घोषणा PUD_FLAGS		_KERNPG_TABLE_NOENC
#घोषणा PMD_FLAGS		_KERNPG_TABLE_NOENC

#घोषणा PMD_FLAGS_LARGE		(__PAGE_KERNEL_LARGE_EXEC & ~_PAGE_GLOBAL)

#घोषणा PMD_FLAGS_DEC		PMD_FLAGS_LARGE
#घोषणा PMD_FLAGS_DEC_WP	((PMD_FLAGS_DEC & ~_PAGE_LARGE_CACHE_MASK) | \
				 (_PAGE_PAT_LARGE | _PAGE_PWT))

#घोषणा PMD_FLAGS_ENC		(PMD_FLAGS_LARGE | _PAGE_ENC)

#घोषणा PTE_FLAGS		(__PAGE_KERNEL_EXEC & ~_PAGE_GLOBAL)

#घोषणा PTE_FLAGS_DEC		PTE_FLAGS
#घोषणा PTE_FLAGS_DEC_WP	((PTE_FLAGS_DEC & ~_PAGE_CACHE_MASK) | \
				 (_PAGE_PAT | _PAGE_PWT))

#घोषणा PTE_FLAGS_ENC		(PTE_FLAGS | _PAGE_ENC)

काष्ठा sme_populate_pgd_data अणु
	व्योम    *pgtable_area;
	pgd_t   *pgd;

	pmdval_t pmd_flags;
	pteval_t pte_flags;
	अचिन्हित दीर्घ paddr;

	अचिन्हित दीर्घ vaddr;
	अचिन्हित दीर्घ vaddr_end;
पूर्ण;

/*
 * This work area lives in the .init.scratch section, which lives outside of
 * the kernel proper. It is sized to hold the पूर्णांकermediate copy buffer and
 * more than enough pagetable pages.
 *
 * By using this section, the kernel can be encrypted in place and it
 * aव्योमs any possibility of boot parameters or initramfs images being
 * placed such that the in-place encryption logic overग_लिखोs them.  This
 * section is 2MB aligned to allow क्रम simple pagetable setup using only
 * PMD entries (see vmlinux.lds.S).
 */
अटल अक्षर sme_workarea[2 * PMD_PAGE_SIZE] __section(".init.scratch");

अटल अक्षर sme_cmdline_arg[] __initdata = "mem_encrypt";
अटल अक्षर sme_cmdline_on[]  __initdata = "on";
अटल अक्षर sme_cmdline_off[] __initdata = "off";

अटल व्योम __init sme_clear_pgd(काष्ठा sme_populate_pgd_data *ppd)
अणु
	अचिन्हित दीर्घ pgd_start, pgd_end, pgd_size;
	pgd_t *pgd_p;

	pgd_start = ppd->vaddr & PGसूची_MASK;
	pgd_end = ppd->vaddr_end & PGसूची_MASK;

	pgd_size = (((pgd_end - pgd_start) / PGसूची_SIZE) + 1) * माप(pgd_t);

	pgd_p = ppd->pgd + pgd_index(ppd->vaddr);

	स_रखो(pgd_p, 0, pgd_size);
पूर्ण

अटल pud_t __init *sme_prepare_pgd(काष्ठा sme_populate_pgd_data *ppd)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	pgd = ppd->pgd + pgd_index(ppd->vaddr);
	अगर (pgd_none(*pgd)) अणु
		p4d = ppd->pgtable_area;
		स_रखो(p4d, 0, माप(*p4d) * PTRS_PER_P4D);
		ppd->pgtable_area += माप(*p4d) * PTRS_PER_P4D;
		set_pgd(pgd, __pgd(PGD_FLAGS | __pa(p4d)));
	पूर्ण

	p4d = p4d_offset(pgd, ppd->vaddr);
	अगर (p4d_none(*p4d)) अणु
		pud = ppd->pgtable_area;
		स_रखो(pud, 0, माप(*pud) * PTRS_PER_PUD);
		ppd->pgtable_area += माप(*pud) * PTRS_PER_PUD;
		set_p4d(p4d, __p4d(P4D_FLAGS | __pa(pud)));
	पूर्ण

	pud = pud_offset(p4d, ppd->vaddr);
	अगर (pud_none(*pud)) अणु
		pmd = ppd->pgtable_area;
		स_रखो(pmd, 0, माप(*pmd) * PTRS_PER_PMD);
		ppd->pgtable_area += माप(*pmd) * PTRS_PER_PMD;
		set_pud(pud, __pud(PUD_FLAGS | __pa(pmd)));
	पूर्ण

	अगर (pud_large(*pud))
		वापस शून्य;

	वापस pud;
पूर्ण

अटल व्योम __init sme_populate_pgd_large(काष्ठा sme_populate_pgd_data *ppd)
अणु
	pud_t *pud;
	pmd_t *pmd;

	pud = sme_prepare_pgd(ppd);
	अगर (!pud)
		वापस;

	pmd = pmd_offset(pud, ppd->vaddr);
	अगर (pmd_large(*pmd))
		वापस;

	set_pmd(pmd, __pmd(ppd->paddr | ppd->pmd_flags));
पूर्ण

अटल व्योम __init sme_populate_pgd(काष्ठा sme_populate_pgd_data *ppd)
अणु
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	pud = sme_prepare_pgd(ppd);
	अगर (!pud)
		वापस;

	pmd = pmd_offset(pud, ppd->vaddr);
	अगर (pmd_none(*pmd)) अणु
		pte = ppd->pgtable_area;
		स_रखो(pte, 0, माप(*pte) * PTRS_PER_PTE);
		ppd->pgtable_area += माप(*pte) * PTRS_PER_PTE;
		set_pmd(pmd, __pmd(PMD_FLAGS | __pa(pte)));
	पूर्ण

	अगर (pmd_large(*pmd))
		वापस;

	pte = pte_offset_map(pmd, ppd->vaddr);
	अगर (pte_none(*pte))
		set_pte(pte, __pte(ppd->paddr | ppd->pte_flags));
पूर्ण

अटल व्योम __init __sme_map_range_pmd(काष्ठा sme_populate_pgd_data *ppd)
अणु
	जबतक (ppd->vaddr < ppd->vaddr_end) अणु
		sme_populate_pgd_large(ppd);

		ppd->vaddr += PMD_PAGE_SIZE;
		ppd->paddr += PMD_PAGE_SIZE;
	पूर्ण
पूर्ण

अटल व्योम __init __sme_map_range_pte(काष्ठा sme_populate_pgd_data *ppd)
अणु
	जबतक (ppd->vaddr < ppd->vaddr_end) अणु
		sme_populate_pgd(ppd);

		ppd->vaddr += PAGE_SIZE;
		ppd->paddr += PAGE_SIZE;
	पूर्ण
पूर्ण

अटल व्योम __init __sme_map_range(काष्ठा sme_populate_pgd_data *ppd,
				   pmdval_t pmd_flags, pteval_t pte_flags)
अणु
	अचिन्हित दीर्घ vaddr_end;

	ppd->pmd_flags = pmd_flags;
	ppd->pte_flags = pte_flags;

	/* Save original end value since we modअगरy the काष्ठा value */
	vaddr_end = ppd->vaddr_end;

	/* If start is not 2MB aligned, create PTE entries */
	ppd->vaddr_end = ALIGN(ppd->vaddr, PMD_PAGE_SIZE);
	__sme_map_range_pte(ppd);

	/* Create PMD entries */
	ppd->vaddr_end = vaddr_end & PMD_PAGE_MASK;
	__sme_map_range_pmd(ppd);

	/* If end is not 2MB aligned, create PTE entries */
	ppd->vaddr_end = vaddr_end;
	__sme_map_range_pte(ppd);
पूर्ण

अटल व्योम __init sme_map_range_encrypted(काष्ठा sme_populate_pgd_data *ppd)
अणु
	__sme_map_range(ppd, PMD_FLAGS_ENC, PTE_FLAGS_ENC);
पूर्ण

अटल व्योम __init sme_map_range_decrypted(काष्ठा sme_populate_pgd_data *ppd)
अणु
	__sme_map_range(ppd, PMD_FLAGS_DEC, PTE_FLAGS_DEC);
पूर्ण

अटल व्योम __init sme_map_range_decrypted_wp(काष्ठा sme_populate_pgd_data *ppd)
अणु
	__sme_map_range(ppd, PMD_FLAGS_DEC_WP, PTE_FLAGS_DEC_WP);
पूर्ण

अटल अचिन्हित दीर्घ __init sme_pgtable_calc(अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ entries = 0, tables = 0;

	/*
	 * Perक्रमm a relatively simplistic calculation of the pagetable
	 * entries that are needed. Those mappings will be covered mostly
	 * by 2MB PMD entries so we can conservatively calculate the required
	 * number of P4D, PUD and PMD काष्ठाures needed to perक्रमm the
	 * mappings.  For mappings that are not 2MB aligned, PTE mappings
	 * would be needed क्रम the start and end portion of the address range
	 * that fall outside of the 2MB alignment.  This results in, at most,
	 * two extra pages to hold PTE entries क्रम each range that is mapped.
	 * Incrementing the count क्रम each covers the हाल where the addresses
	 * cross entries.
	 */

	/* PGसूची_SIZE is equal to P4D_SIZE on 4-level machine. */
	अगर (PTRS_PER_P4D > 1)
		entries += (DIV_ROUND_UP(len, PGसूची_SIZE) + 1) * माप(p4d_t) * PTRS_PER_P4D;
	entries += (DIV_ROUND_UP(len, P4D_SIZE) + 1) * माप(pud_t) * PTRS_PER_PUD;
	entries += (DIV_ROUND_UP(len, PUD_SIZE) + 1) * माप(pmd_t) * PTRS_PER_PMD;
	entries += 2 * माप(pte_t) * PTRS_PER_PTE;

	/*
	 * Now calculate the added pagetable काष्ठाures needed to populate
	 * the new pagetables.
	 */

	अगर (PTRS_PER_P4D > 1)
		tables += DIV_ROUND_UP(entries, PGसूची_SIZE) * माप(p4d_t) * PTRS_PER_P4D;
	tables += DIV_ROUND_UP(entries, P4D_SIZE) * माप(pud_t) * PTRS_PER_PUD;
	tables += DIV_ROUND_UP(entries, PUD_SIZE) * माप(pmd_t) * PTRS_PER_PMD;

	वापस entries + tables;
पूर्ण

व्योम __init sme_encrypt_kernel(काष्ठा boot_params *bp)
अणु
	अचिन्हित दीर्घ workarea_start, workarea_end, workarea_len;
	अचिन्हित दीर्घ execute_start, execute_end, execute_len;
	अचिन्हित दीर्घ kernel_start, kernel_end, kernel_len;
	अचिन्हित दीर्घ initrd_start, initrd_end, initrd_len;
	काष्ठा sme_populate_pgd_data ppd;
	अचिन्हित दीर्घ pgtable_area_len;
	अचिन्हित दीर्घ decrypted_base;

	अगर (!sme_active())
		वापस;

	/*
	 * Prepare क्रम encrypting the kernel and initrd by building new
	 * pagetables with the necessary attributes needed to encrypt the
	 * kernel in place.
	 *
	 *   One range of भव addresses will map the memory occupied
	 *   by the kernel and initrd as encrypted.
	 *
	 *   Another range of भव addresses will map the memory occupied
	 *   by the kernel and initrd as decrypted and ग_लिखो-रक्षित.
	 *
	 *     The use of ग_लिखो-protect attribute will prevent any of the
	 *     memory from being cached.
	 */

	/* Physical addresses gives us the identity mapped भव addresses */
	kernel_start = __pa_symbol(_text);
	kernel_end = ALIGN(__pa_symbol(_end), PMD_PAGE_SIZE);
	kernel_len = kernel_end - kernel_start;

	initrd_start = 0;
	initrd_end = 0;
	initrd_len = 0;
#अगर_घोषित CONFIG_BLK_DEV_INITRD
	initrd_len = (अचिन्हित दीर्घ)bp->hdr.ramdisk_size |
		     ((अचिन्हित दीर्घ)bp->ext_ramdisk_size << 32);
	अगर (initrd_len) अणु
		initrd_start = (अचिन्हित दीर्घ)bp->hdr.ramdisk_image |
			       ((अचिन्हित दीर्घ)bp->ext_ramdisk_image << 32);
		initrd_end = PAGE_ALIGN(initrd_start + initrd_len);
		initrd_len = initrd_end - initrd_start;
	पूर्ण
#पूर्ण_अगर

	/*
	 * We're running identity mapped, so we must obtain the address to the
	 * SME encryption workarea using rip-relative addressing.
	 */
	यंत्र ("lea sme_workarea(%%rip), %0"
	     : "=r" (workarea_start)
	     : "p" (sme_workarea));

	/*
	 * Calculate required number of workarea bytes needed:
	 *   executable encryption area size:
	 *     stack page (PAGE_SIZE)
	 *     encryption routine page (PAGE_SIZE)
	 *     पूर्णांकermediate copy buffer (PMD_PAGE_SIZE)
	 *   pagetable काष्ठाures क्रम the encryption of the kernel
	 *   pagetable काष्ठाures क्रम workarea (in हाल not currently mapped)
	 */
	execute_start = workarea_start;
	execute_end = execute_start + (PAGE_SIZE * 2) + PMD_PAGE_SIZE;
	execute_len = execute_end - execute_start;

	/*
	 * One PGD क्रम both encrypted and decrypted mappings and a set of
	 * PUDs and PMDs क्रम each of the encrypted and decrypted mappings.
	 */
	pgtable_area_len = माप(pgd_t) * PTRS_PER_PGD;
	pgtable_area_len += sme_pgtable_calc(execute_end - kernel_start) * 2;
	अगर (initrd_len)
		pgtable_area_len += sme_pgtable_calc(initrd_len) * 2;

	/* PUDs and PMDs needed in the current pagetables क्रम the workarea */
	pgtable_area_len += sme_pgtable_calc(execute_len + pgtable_area_len);

	/*
	 * The total workarea includes the executable encryption area and
	 * the pagetable area. The start of the workarea is alपढ़ोy 2MB
	 * aligned, align the end of the workarea on a 2MB boundary so that
	 * we करोn't try to create/allocate PTE entries from the workarea
	 * beक्रमe it is mapped.
	 */
	workarea_len = execute_len + pgtable_area_len;
	workarea_end = ALIGN(workarea_start + workarea_len, PMD_PAGE_SIZE);

	/*
	 * Set the address to the start of where newly created pagetable
	 * काष्ठाures (PGDs, PUDs and PMDs) will be allocated. New pagetable
	 * काष्ठाures are created when the workarea is added to the current
	 * pagetables and when the new encrypted and decrypted kernel
	 * mappings are populated.
	 */
	ppd.pgtable_area = (व्योम *)execute_end;

	/*
	 * Make sure the current pagetable काष्ठाure has entries क्रम
	 * addressing the workarea.
	 */
	ppd.pgd = (pgd_t *)native_पढ़ो_cr3_pa();
	ppd.paddr = workarea_start;
	ppd.vaddr = workarea_start;
	ppd.vaddr_end = workarea_end;
	sme_map_range_decrypted(&ppd);

	/* Flush the TLB - no globals so cr3 is enough */
	native_ग_लिखो_cr3(__native_पढ़ो_cr3());

	/*
	 * A new pagetable काष्ठाure is being built to allow क्रम the kernel
	 * and initrd to be encrypted. It starts with an empty PGD that will
	 * then be populated with new PUDs and PMDs as the encrypted and
	 * decrypted kernel mappings are created.
	 */
	ppd.pgd = ppd.pgtable_area;
	स_रखो(ppd.pgd, 0, माप(pgd_t) * PTRS_PER_PGD);
	ppd.pgtable_area += माप(pgd_t) * PTRS_PER_PGD;

	/*
	 * A dअगरferent PGD index/entry must be used to get dअगरferent
	 * pagetable entries क्रम the decrypted mapping. Choose the next
	 * PGD index and convert it to a भव address to be used as
	 * the base of the mapping.
	 */
	decrypted_base = (pgd_index(workarea_end) + 1) & (PTRS_PER_PGD - 1);
	अगर (initrd_len) अणु
		अचिन्हित दीर्घ check_base;

		check_base = (pgd_index(initrd_end) + 1) & (PTRS_PER_PGD - 1);
		decrypted_base = max(decrypted_base, check_base);
	पूर्ण
	decrypted_base <<= PGसूची_SHIFT;

	/* Add encrypted kernel (identity) mappings */
	ppd.paddr = kernel_start;
	ppd.vaddr = kernel_start;
	ppd.vaddr_end = kernel_end;
	sme_map_range_encrypted(&ppd);

	/* Add decrypted, ग_लिखो-रक्षित kernel (non-identity) mappings */
	ppd.paddr = kernel_start;
	ppd.vaddr = kernel_start + decrypted_base;
	ppd.vaddr_end = kernel_end + decrypted_base;
	sme_map_range_decrypted_wp(&ppd);

	अगर (initrd_len) अणु
		/* Add encrypted initrd (identity) mappings */
		ppd.paddr = initrd_start;
		ppd.vaddr = initrd_start;
		ppd.vaddr_end = initrd_end;
		sme_map_range_encrypted(&ppd);
		/*
		 * Add decrypted, ग_लिखो-रक्षित initrd (non-identity) mappings
		 */
		ppd.paddr = initrd_start;
		ppd.vaddr = initrd_start + decrypted_base;
		ppd.vaddr_end = initrd_end + decrypted_base;
		sme_map_range_decrypted_wp(&ppd);
	पूर्ण

	/* Add decrypted workarea mappings to both kernel mappings */
	ppd.paddr = workarea_start;
	ppd.vaddr = workarea_start;
	ppd.vaddr_end = workarea_end;
	sme_map_range_decrypted(&ppd);

	ppd.paddr = workarea_start;
	ppd.vaddr = workarea_start + decrypted_base;
	ppd.vaddr_end = workarea_end + decrypted_base;
	sme_map_range_decrypted(&ppd);

	/* Perक्रमm the encryption */
	sme_encrypt_execute(kernel_start, kernel_start + decrypted_base,
			    kernel_len, workarea_start, (अचिन्हित दीर्घ)ppd.pgd);

	अगर (initrd_len)
		sme_encrypt_execute(initrd_start, initrd_start + decrypted_base,
				    initrd_len, workarea_start,
				    (अचिन्हित दीर्घ)ppd.pgd);

	/*
	 * At this poपूर्णांक we are running encrypted.  Remove the mappings क्रम
	 * the decrypted areas - all that is needed क्रम this is to हटाओ
	 * the PGD entry/entries.
	 */
	ppd.vaddr = kernel_start + decrypted_base;
	ppd.vaddr_end = kernel_end + decrypted_base;
	sme_clear_pgd(&ppd);

	अगर (initrd_len) अणु
		ppd.vaddr = initrd_start + decrypted_base;
		ppd.vaddr_end = initrd_end + decrypted_base;
		sme_clear_pgd(&ppd);
	पूर्ण

	ppd.vaddr = workarea_start + decrypted_base;
	ppd.vaddr_end = workarea_end + decrypted_base;
	sme_clear_pgd(&ppd);

	/* Flush the TLB - no globals so cr3 is enough */
	native_ग_लिखो_cr3(__native_पढ़ो_cr3());
पूर्ण

व्योम __init sme_enable(काष्ठा boot_params *bp)
अणु
	स्थिर अक्षर *cmdline_ptr, *cmdline_arg, *cmdline_on, *cmdline_off;
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;
	अचिन्हित दीर्घ feature_mask;
	bool active_by_शेष;
	अचिन्हित दीर्घ me_mask;
	अक्षर buffer[16];
	u64 msr;

	/* Check क्रम the SME/SEV support leaf */
	eax = 0x80000000;
	ecx = 0;
	native_cpuid(&eax, &ebx, &ecx, &edx);
	अगर (eax < 0x8000001f)
		वापस;

#घोषणा AMD_SME_BIT	BIT(0)
#घोषणा AMD_SEV_BIT	BIT(1)

	/*
	 * Check क्रम the SME/SEV feature:
	 *   CPUID Fn8000_001F[EAX]
	 *   - Bit 0 - Secure Memory Encryption support
	 *   - Bit 1 - Secure Encrypted Virtualization support
	 *   CPUID Fn8000_001F[EBX]
	 *   - Bits 5:0 - Pagetable bit position used to indicate encryption
	 */
	eax = 0x8000001f;
	ecx = 0;
	native_cpuid(&eax, &ebx, &ecx, &edx);
	/* Check whether SEV or SME is supported */
	अगर (!(eax & (AMD_SEV_BIT | AMD_SME_BIT)))
		वापस;

	me_mask = 1UL << (ebx & 0x3f);

	/* Check the SEV MSR whether SEV or SME is enabled */
	sev_status   = __rdmsr(MSR_AMD64_SEV);
	feature_mask = (sev_status & MSR_AMD64_SEV_ENABLED) ? AMD_SEV_BIT : AMD_SME_BIT;

	/* Check अगर memory encryption is enabled */
	अगर (feature_mask == AMD_SME_BIT) अणु
		/*
		 * No SME अगर Hypervisor bit is set. This check is here to
		 * prevent a guest from trying to enable SME. For running as a
		 * KVM guest the MSR_AMD64_SYSCFG will be sufficient, but there
		 * might be other hypervisors which emulate that MSR as non-zero
		 * or even pass it through to the guest.
		 * A malicious hypervisor can still trick a guest पूर्णांकo this
		 * path, but there is no way to protect against that.
		 */
		eax = 1;
		ecx = 0;
		native_cpuid(&eax, &ebx, &ecx, &edx);
		अगर (ecx & BIT(31))
			वापस;

		/* For SME, check the SYSCFG MSR */
		msr = __rdmsr(MSR_AMD64_SYSCFG);
		अगर (!(msr & MSR_AMD64_SYSCFG_MEM_ENCRYPT))
			वापस;
	पूर्ण अन्यथा अणु
		/* SEV state cannot be controlled by a command line option */
		sme_me_mask = me_mask;
		physical_mask &= ~sme_me_mask;
		वापस;
	पूर्ण

	/*
	 * Fixups have not been applied to phys_base yet and we're running
	 * identity mapped, so we must obtain the address to the SME command
	 * line argument data using rip-relative addressing.
	 */
	यंत्र ("lea sme_cmdline_arg(%%rip), %0"
	     : "=r" (cmdline_arg)
	     : "p" (sme_cmdline_arg));
	यंत्र ("lea sme_cmdline_on(%%rip), %0"
	     : "=r" (cmdline_on)
	     : "p" (sme_cmdline_on));
	यंत्र ("lea sme_cmdline_off(%%rip), %0"
	     : "=r" (cmdline_off)
	     : "p" (sme_cmdline_off));

	अगर (IS_ENABLED(CONFIG_AMD_MEM_ENCRYPT_ACTIVE_BY_DEFAULT))
		active_by_शेष = true;
	अन्यथा
		active_by_शेष = false;

	cmdline_ptr = (स्थिर अक्षर *)((u64)bp->hdr.cmd_line_ptr |
				     ((u64)bp->ext_cmd_line_ptr << 32));

	cmdline_find_option(cmdline_ptr, cmdline_arg, buffer, माप(buffer));

	अगर (!म_भेदन(buffer, cmdline_on, माप(buffer)))
		sme_me_mask = me_mask;
	अन्यथा अगर (!म_भेदन(buffer, cmdline_off, माप(buffer)))
		sme_me_mask = 0;
	अन्यथा
		sme_me_mask = active_by_शेष ? me_mask : 0;

	physical_mask &= ~sme_me_mask;
पूर्ण
