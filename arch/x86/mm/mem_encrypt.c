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

#समावेश <linux/linkage.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/dma-direct.h>
#समावेश <linux/swiotlb.h>
#समावेश <linux/mem_encrypt.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/virtio_config.h>

#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/bootparam.h>
#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/processor-flags.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/cmdline.h>

#समावेश "mm_internal.h"

/*
 * Since SME related variables are set early in the boot process they must
 * reside in the .data section so as not to be zeroed out when the .bss
 * section is later cleared.
 */
u64 sme_me_mask __section(".data") = 0;
u64 sev_status __section(".data") = 0;
u64 sev_check_data __section(".data") = 0;
EXPORT_SYMBOL(sme_me_mask);
DEFINE_STATIC_KEY_FALSE(sev_enable_key);
EXPORT_SYMBOL_GPL(sev_enable_key);

/* Buffer used क्रम early in-place encryption by BSP, no locking needed */
अटल अक्षर sme_early_buffer[PAGE_SIZE] __initdata __aligned(PAGE_SIZE);

/*
 * This routine करोes not change the underlying encryption setting of the
 * page(s) that map this memory. It assumes that eventually the memory is
 * meant to be accessed as either encrypted or decrypted but the contents
 * are currently not in the desired state.
 *
 * This routine follows the steps outlined in the AMD64 Architecture
 * Programmer's Manual Volume 2, Section 7.10.8 Encrypt-in-Place.
 */
अटल व्योम __init __sme_early_enc_dec(resource_माप_प्रकार paddr,
				       अचिन्हित दीर्घ size, bool enc)
अणु
	व्योम *src, *dst;
	माप_प्रकार len;

	अगर (!sme_me_mask)
		वापस;

	wbinvd();

	/*
	 * There are limited number of early mapping slots, so map (at most)
	 * one page at समय.
	 */
	जबतक (size) अणु
		len = min_t(माप_प्रकार, माप(sme_early_buffer), size);

		/*
		 * Create mappings क्रम the current and desired क्रमmat of
		 * the memory. Use a ग_लिखो-रक्षित mapping क्रम the source.
		 */
		src = enc ? early_memremap_decrypted_wp(paddr, len) :
			    early_memremap_encrypted_wp(paddr, len);

		dst = enc ? early_memremap_encrypted(paddr, len) :
			    early_memremap_decrypted(paddr, len);

		/*
		 * If a mapping can't be obtained to perक्रमm the operation,
		 * then eventual access of that area in the desired mode
		 * will cause a crash.
		 */
		BUG_ON(!src || !dst);

		/*
		 * Use a temporary buffer, of cache-line multiple size, to
		 * aव्योम data corruption as करोcumented in the APM.
		 */
		स_नकल(sme_early_buffer, src, len);
		स_नकल(dst, sme_early_buffer, len);

		early_memunmap(dst, len);
		early_memunmap(src, len);

		paddr += len;
		size -= len;
	पूर्ण
पूर्ण

व्योम __init sme_early_encrypt(resource_माप_प्रकार paddr, अचिन्हित दीर्घ size)
अणु
	__sme_early_enc_dec(paddr, size, true);
पूर्ण

व्योम __init sme_early_decrypt(resource_माप_प्रकार paddr, अचिन्हित दीर्घ size)
अणु
	__sme_early_enc_dec(paddr, size, false);
पूर्ण

अटल व्योम __init __sme_early_map_unmap_mem(व्योम *vaddr, अचिन्हित दीर्घ size,
					     bool map)
अणु
	अचिन्हित दीर्घ paddr = (अचिन्हित दीर्घ)vaddr - __PAGE_OFFSET;
	pmdval_t pmd_flags, pmd;

	/* Use early_pmd_flags but हटाओ the encryption mask */
	pmd_flags = __sme_clr(early_pmd_flags);

	करो अणु
		pmd = map ? (paddr & PMD_MASK) + pmd_flags : 0;
		__early_make_pgtable((अचिन्हित दीर्घ)vaddr, pmd);

		vaddr += PMD_SIZE;
		paddr += PMD_SIZE;
		size = (size <= PMD_SIZE) ? 0 : size - PMD_SIZE;
	पूर्ण जबतक (size);

	flush_tlb_local();
पूर्ण

व्योम __init sme_unmap_bootdata(अक्षर *real_mode_data)
अणु
	काष्ठा boot_params *boot_data;
	अचिन्हित दीर्घ cmdline_paddr;

	अगर (!sme_active())
		वापस;

	/* Get the command line address beक्रमe unmapping the real_mode_data */
	boot_data = (काष्ठा boot_params *)real_mode_data;
	cmdline_paddr = boot_data->hdr.cmd_line_ptr | ((u64)boot_data->ext_cmd_line_ptr << 32);

	__sme_early_map_unmap_mem(real_mode_data, माप(boot_params), false);

	अगर (!cmdline_paddr)
		वापस;

	__sme_early_map_unmap_mem(__va(cmdline_paddr), COMMAND_LINE_SIZE, false);
पूर्ण

व्योम __init sme_map_bootdata(अक्षर *real_mode_data)
अणु
	काष्ठा boot_params *boot_data;
	अचिन्हित दीर्घ cmdline_paddr;

	अगर (!sme_active())
		वापस;

	__sme_early_map_unmap_mem(real_mode_data, माप(boot_params), true);

	/* Get the command line address after mapping the real_mode_data */
	boot_data = (काष्ठा boot_params *)real_mode_data;
	cmdline_paddr = boot_data->hdr.cmd_line_ptr | ((u64)boot_data->ext_cmd_line_ptr << 32);

	अगर (!cmdline_paddr)
		वापस;

	__sme_early_map_unmap_mem(__va(cmdline_paddr), COMMAND_LINE_SIZE, true);
पूर्ण

व्योम __init sme_early_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!sme_me_mask)
		वापस;

	early_pmd_flags = __sme_set(early_pmd_flags);

	__supported_pte_mask = __sme_set(__supported_pte_mask);

	/* Update the protection map with memory encryption mask */
	क्रम (i = 0; i < ARRAY_SIZE(protection_map); i++)
		protection_map[i] = pgprot_encrypted(protection_map[i]);

	अगर (sev_active())
		swiotlb_क्रमce = SWIOTLB_FORCE;
पूर्ण

व्योम __init sev_setup_arch(व्योम)
अणु
	phys_addr_t total_mem = memblock_phys_mem_size();
	अचिन्हित दीर्घ size;

	अगर (!sev_active())
		वापस;

	/*
	 * For SEV, all DMA has to occur via shared/unencrypted pages.
	 * SEV uses SWIOTLB to make this happen without changing device
	 * drivers. However, depending on the workload being run, the
	 * शेष 64MB of SWIOTLB may not be enough and SWIOTLB may
	 * run out of buffers क्रम DMA, resulting in I/O errors and/or
	 * perक्रमmance degradation especially with high I/O workloads.
	 *
	 * Adjust the शेष size of SWIOTLB क्रम SEV guests using
	 * a percentage of guest memory क्रम SWIOTLB buffers.
	 * Also, as the SWIOTLB bounce buffer memory is allocated
	 * from low memory, ensure that the adjusted size is within
	 * the limits of low available memory.
	 *
	 * The percentage of guest memory used here क्रम SWIOTLB buffers
	 * is more of an approximation of the अटल adjusपंचांगent which
	 * 64MB क्रम <1G, and ~128M to 256M क्रम 1G-to-4G, i.e., the 6%
	 */
	size = total_mem * 6 / 100;
	size = clamp_val(size, IO_TLB_DEFAULT_SIZE, SZ_1G);
	swiotlb_adjust_size(size);
पूर्ण

अटल व्योम __init __set_clr_pte_enc(pte_t *kpte, पूर्णांक level, bool enc)
अणु
	pgprot_t old_prot, new_prot;
	अचिन्हित दीर्घ pfn, pa, size;
	pte_t new_pte;

	चयन (level) अणु
	हाल PG_LEVEL_4K:
		pfn = pte_pfn(*kpte);
		old_prot = pte_pgprot(*kpte);
		अवरोध;
	हाल PG_LEVEL_2M:
		pfn = pmd_pfn(*(pmd_t *)kpte);
		old_prot = pmd_pgprot(*(pmd_t *)kpte);
		अवरोध;
	हाल PG_LEVEL_1G:
		pfn = pud_pfn(*(pud_t *)kpte);
		old_prot = pud_pgprot(*(pud_t *)kpte);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	new_prot = old_prot;
	अगर (enc)
		pgprot_val(new_prot) |= _PAGE_ENC;
	अन्यथा
		pgprot_val(new_prot) &= ~_PAGE_ENC;

	/* If prot is same then करो nothing. */
	अगर (pgprot_val(old_prot) == pgprot_val(new_prot))
		वापस;

	pa = pfn << PAGE_SHIFT;
	size = page_level_size(level);

	/*
	 * We are going to perक्रमm in-place en-/decryption and change the
	 * physical page attribute from C=1 to C=0 or vice versa. Flush the
	 * caches to ensure that data माला_लो accessed with the correct C-bit.
	 */
	clflush_cache_range(__va(pa), size);

	/* Encrypt/decrypt the contents in-place */
	अगर (enc)
		sme_early_encrypt(pa, size);
	अन्यथा
		sme_early_decrypt(pa, size);

	/* Change the page encryption mask. */
	new_pte = pfn_pte(pfn, new_prot);
	set_pte_atomic(kpte, new_pte);
पूर्ण

अटल पूर्णांक __init early_set_memory_enc_dec(अचिन्हित दीर्घ vaddr,
					   अचिन्हित दीर्घ size, bool enc)
अणु
	अचिन्हित दीर्घ vaddr_end, vaddr_next;
	अचिन्हित दीर्घ psize, pmask;
	पूर्णांक split_page_size_mask;
	पूर्णांक level, ret;
	pte_t *kpte;

	vaddr_next = vaddr;
	vaddr_end = vaddr + size;

	क्रम (; vaddr < vaddr_end; vaddr = vaddr_next) अणु
		kpte = lookup_address(vaddr, &level);
		अगर (!kpte || pte_none(*kpte)) अणु
			ret = 1;
			जाओ out;
		पूर्ण

		अगर (level == PG_LEVEL_4K) अणु
			__set_clr_pte_enc(kpte, level, enc);
			vaddr_next = (vaddr & PAGE_MASK) + PAGE_SIZE;
			जारी;
		पूर्ण

		psize = page_level_size(level);
		pmask = page_level_mask(level);

		/*
		 * Check whether we can change the large page in one go.
		 * We request a split when the address is not aligned and
		 * the number of pages to set/clear encryption bit is smaller
		 * than the number of pages in the large page.
		 */
		अगर (vaddr == (vaddr & pmask) &&
		    ((vaddr_end - vaddr) >= psize)) अणु
			__set_clr_pte_enc(kpte, level, enc);
			vaddr_next = (vaddr & pmask) + psize;
			जारी;
		पूर्ण

		/*
		 * The भव address is part of a larger page, create the next
		 * level page table mapping (4K or 2M). If it is part of a 2M
		 * page then we request a split of the large page पूर्णांकo 4K
		 * chunks. A 1GB large page is split पूर्णांकo 2M pages, resp.
		 */
		अगर (level == PG_LEVEL_2M)
			split_page_size_mask = 0;
		अन्यथा
			split_page_size_mask = 1 << PG_LEVEL_2M;

		/*
		 * kernel_physical_mapping_change() करोes not flush the TLBs, so
		 * a TLB flush is required after we निकास from the क्रम loop.
		 */
		kernel_physical_mapping_change(__pa(vaddr & pmask),
					       __pa((vaddr_end & pmask) + psize),
					       split_page_size_mask);
	पूर्ण

	ret = 0;

out:
	__flush_tlb_all();
	वापस ret;
पूर्ण

पूर्णांक __init early_set_memory_decrypted(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ size)
अणु
	वापस early_set_memory_enc_dec(vaddr, size, false);
पूर्ण

पूर्णांक __init early_set_memory_encrypted(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ size)
अणु
	वापस early_set_memory_enc_dec(vaddr, size, true);
पूर्ण

/*
 * SME and SEV are very similar but they are not the same, so there are
 * बार that the kernel will need to distinguish between SME and SEV. The
 * sme_active() and sev_active() functions are used क्रम this.  When a
 * distinction isn't needed, the mem_encrypt_active() function can be used.
 *
 * The trampoline code is a good example क्रम this requirement.  Beक्रमe
 * paging is activated, SME will access all memory as decrypted, but SEV
 * will access all memory as encrypted.  So, when APs are being brought
 * up under SME the trampoline area cannot be encrypted, whereas under SEV
 * the trampoline area must be encrypted.
 */
bool sev_active(व्योम)
अणु
	वापस sev_status & MSR_AMD64_SEV_ENABLED;
पूर्ण

bool sme_active(व्योम)
अणु
	वापस sme_me_mask && !sev_active();
पूर्ण
EXPORT_SYMBOL_GPL(sev_active);

/* Needs to be called from non-instrumentable code */
bool noinstr sev_es_active(व्योम)
अणु
	वापस sev_status & MSR_AMD64_SEV_ES_ENABLED;
पूर्ण

/* Override क्रम DMA direct allocation check - ARCH_HAS_FORCE_DMA_UNENCRYPTED */
bool क्रमce_dma_unencrypted(काष्ठा device *dev)
अणु
	/*
	 * For SEV, all DMA must be to unencrypted addresses.
	 */
	अगर (sev_active())
		वापस true;

	/*
	 * For SME, all DMA must be to unencrypted addresses अगर the
	 * device करोes not support DMA to addresses that include the
	 * encryption mask.
	 */
	अगर (sme_active()) अणु
		u64 dma_enc_mask = DMA_BIT_MASK(__ffs64(sme_me_mask));
		u64 dma_dev_mask = min_not_zero(dev->coherent_dma_mask,
						dev->bus_dma_limit);

		अगर (dma_dev_mask <= dma_enc_mask)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम __init mem_encrypt_मुक्त_decrypted_mem(व्योम)
अणु
	अचिन्हित दीर्घ vaddr, vaddr_end, npages;
	पूर्णांक r;

	vaddr = (अचिन्हित दीर्घ)__start_bss_decrypted_unused;
	vaddr_end = (अचिन्हित दीर्घ)__end_bss_decrypted;
	npages = (vaddr_end - vaddr) >> PAGE_SHIFT;

	/*
	 * The unused memory range was mapped decrypted, change the encryption
	 * attribute from decrypted to encrypted beक्रमe मुक्तing it.
	 */
	अगर (mem_encrypt_active()) अणु
		r = set_memory_encrypted(vaddr, npages);
		अगर (r) अणु
			pr_warn("failed to free unused decrypted pages\n");
			वापस;
		पूर्ण
	पूर्ण

	मुक्त_init_pages("unused decrypted", vaddr, vaddr_end);
पूर्ण

अटल व्योम prपूर्णांक_mem_encrypt_feature_info(व्योम)
अणु
	pr_info("AMD Memory Encryption Features active:");

	/* Secure Memory Encryption */
	अगर (sme_active()) अणु
		/*
		 * SME is mutually exclusive with any of the SEV
		 * features below.
		 */
		pr_cont(" SME\n");
		वापस;
	पूर्ण

	/* Secure Encrypted Virtualization */
	अगर (sev_active())
		pr_cont(" SEV");

	/* Encrypted Register State */
	अगर (sev_es_active())
		pr_cont(" SEV-ES");

	pr_cont("\n");
पूर्ण

/* Architecture __weak replacement functions */
व्योम __init mem_encrypt_init(व्योम)
अणु
	अगर (!sme_me_mask)
		वापस;

	/* Call पूर्णांकo SWIOTLB to update the SWIOTLB DMA buffers */
	swiotlb_update_mem_attributes();

	/*
	 * With SEV, we need to unroll the rep string I/O inकाष्ठाions,
	 * but SEV-ES supports them through the #VC handler.
	 */
	अगर (sev_active() && !sev_es_active())
		अटल_branch_enable(&sev_enable_key);

	prपूर्णांक_mem_encrypt_feature_info();
पूर्ण

पूर्णांक arch_has_restricted_virtio_memory_access(व्योम)
अणु
	वापस sev_active();
पूर्ण
EXPORT_SYMBOL_GPL(arch_has_restricted_virtio_memory_access);
