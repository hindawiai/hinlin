<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित INCLUDE_XEN_OPS_H
#घोषणा INCLUDE_XEN_OPS_H

#समावेश <linux/percpu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/efi.h>
#समावेश <xen/features.h>
#समावेश <यंत्र/xen/पूर्णांकerface.h>
#समावेश <xen/पूर्णांकerface/vcpu.h>

DECLARE_PER_CPU(काष्ठा vcpu_info *, xen_vcpu);

DECLARE_PER_CPU(uपूर्णांक32_t, xen_vcpu_id);
अटल अंतरभूत uपूर्णांक32_t xen_vcpu_nr(पूर्णांक cpu)
अणु
	वापस per_cpu(xen_vcpu_id, cpu);
पूर्ण

#घोषणा XEN_VCPU_ID_INVALID U32_MAX

व्योम xen_arch_pre_suspend(व्योम);
व्योम xen_arch_post_suspend(पूर्णांक suspend_cancelled);

व्योम xen_समयr_resume(व्योम);
व्योम xen_arch_resume(व्योम);
व्योम xen_arch_suspend(व्योम);

व्योम xen_reboot(पूर्णांक reason);

व्योम xen_resume_notअगरier_रेजिस्टर(काष्ठा notअगरier_block *nb);
व्योम xen_resume_notअगरier_unरेजिस्टर(काष्ठा notअगरier_block *nb);

bool xen_vcpu_stolen(पूर्णांक vcpu);
व्योम xen_setup_runstate_info(पूर्णांक cpu);
व्योम xen_समय_setup_guest(व्योम);
व्योम xen_manage_runstate_समय(पूर्णांक action);
व्योम xen_get_runstate_snapshot(काष्ठा vcpu_runstate_info *res);
u64 xen_steal_घड़ी(पूर्णांक cpu);

पूर्णांक xen_setup_shutकरोwn_event(व्योम);

बाह्य अचिन्हित दीर्घ *xen_contiguous_biपंचांगap;

#अगर defined(CONFIG_XEN_PV) || defined(CONFIG_ARM) || defined(CONFIG_ARM64)
पूर्णांक xen_create_contiguous_region(phys_addr_t pstart, अचिन्हित पूर्णांक order,
				अचिन्हित पूर्णांक address_bits,
				dma_addr_t *dma_handle);

व्योम xen_destroy_contiguous_region(phys_addr_t pstart, अचिन्हित पूर्णांक order);
#अन्यथा
अटल अंतरभूत पूर्णांक xen_create_contiguous_region(phys_addr_t pstart,
					       अचिन्हित पूर्णांक order,
					       अचिन्हित पूर्णांक address_bits,
					       dma_addr_t *dma_handle)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम xen_destroy_contiguous_region(phys_addr_t pstart,
						 अचिन्हित पूर्णांक order) अणु पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_XEN_PV)
पूर्णांक xen_remap_pfn(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
		  xen_pfn_t *pfn, पूर्णांक nr, पूर्णांक *err_ptr, pgprot_t prot,
		  अचिन्हित पूर्णांक करोmid, bool no_translate, काष्ठा page **pages);
#अन्यथा
अटल अंतरभूत पूर्णांक xen_remap_pfn(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
				xen_pfn_t *pfn, पूर्णांक nr, पूर्णांक *err_ptr,
				pgprot_t prot,  अचिन्हित पूर्णांक करोmid,
				bool no_translate, काष्ठा page **pages)
अणु
	BUG();
	वापस 0;
पूर्ण
#पूर्ण_अगर

काष्ठा vm_area_काष्ठा;

#अगर_घोषित CONFIG_XEN_AUTO_XLATE
पूर्णांक xen_xlate_remap_gfn_array(काष्ठा vm_area_काष्ठा *vma,
			      अचिन्हित दीर्घ addr,
			      xen_pfn_t *gfn, पूर्णांक nr,
			      पूर्णांक *err_ptr, pgprot_t prot,
			      अचिन्हित पूर्णांक करोmid,
			      काष्ठा page **pages);
पूर्णांक xen_xlate_unmap_gfn_range(काष्ठा vm_area_काष्ठा *vma,
			      पूर्णांक nr, काष्ठा page **pages);
#अन्यथा
/*
 * These two functions are called from arch/x86/xen/mmu.c and so stubs
 * are needed क्रम a configuration not specअगरying CONFIG_XEN_AUTO_XLATE.
 */
अटल अंतरभूत पूर्णांक xen_xlate_remap_gfn_array(काष्ठा vm_area_काष्ठा *vma,
					    अचिन्हित दीर्घ addr,
					    xen_pfn_t *gfn, पूर्णांक nr,
					    पूर्णांक *err_ptr, pgprot_t prot,
					    अचिन्हित पूर्णांक करोmid,
					    काष्ठा page **pages)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक xen_xlate_unmap_gfn_range(काष्ठा vm_area_काष्ठा *vma,
					    पूर्णांक nr, काष्ठा page **pages)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

पूर्णांक xen_remap_vma_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ len);

/*
 * xen_remap_करोमुख्य_gfn_array() - map an array of क्रमeign frames by gfn
 * @vma:     VMA to map the pages पूर्णांकo
 * @addr:    Address at which to map the pages
 * @gfn:     Array of GFNs to map
 * @nr:      Number entries in the GFN array
 * @err_ptr: Returns per-GFN error status.
 * @prot:    page protection mask
 * @करोmid:   Doमुख्य owning the pages
 * @pages:   Array of pages अगर this करोमुख्य has an स्वतः-translated physmap
 *
 * @gfn and @err_ptr may poपूर्णांक to the same buffer, the GFNs will be
 * overwritten by the error codes after they are mapped.
 *
 * Returns the number of successfully mapped frames, or a -ve error
 * code.
 */
अटल अंतरभूत पूर्णांक xen_remap_करोमुख्य_gfn_array(काष्ठा vm_area_काष्ठा *vma,
					     अचिन्हित दीर्घ addr,
					     xen_pfn_t *gfn, पूर्णांक nr,
					     पूर्णांक *err_ptr, pgprot_t prot,
					     अचिन्हित पूर्णांक करोmid,
					     काष्ठा page **pages)
अणु
	अगर (xen_feature(XENFEAT_स्वतः_translated_physmap))
		वापस xen_xlate_remap_gfn_array(vma, addr, gfn, nr, err_ptr,
						 prot, करोmid, pages);

	/* We BUG_ON because it's a programmer error to pass a शून्य err_ptr,
	 * and the consequences later is quite hard to detect what the actual
	 * cause of "wrong memory was mapped in".
	 */
	BUG_ON(err_ptr == शून्य);
	वापस xen_remap_pfn(vma, addr, gfn, nr, err_ptr, prot, करोmid,
			     false, pages);
पूर्ण

/*
 * xen_remap_करोमुख्य_mfn_array() - map an array of क्रमeign frames by mfn
 * @vma:     VMA to map the pages पूर्णांकo
 * @addr:    Address at which to map the pages
 * @mfn:     Array of MFNs to map
 * @nr:      Number entries in the MFN array
 * @err_ptr: Returns per-MFN error status.
 * @prot:    page protection mask
 * @करोmid:   Doमुख्य owning the pages
 * @pages:   Array of pages अगर this करोमुख्य has an स्वतः-translated physmap
 *
 * @mfn and @err_ptr may poपूर्णांक to the same buffer, the MFNs will be
 * overwritten by the error codes after they are mapped.
 *
 * Returns the number of successfully mapped frames, or a -ve error
 * code.
 */
अटल अंतरभूत पूर्णांक xen_remap_करोमुख्य_mfn_array(काष्ठा vm_area_काष्ठा *vma,
					     अचिन्हित दीर्घ addr, xen_pfn_t *mfn,
					     पूर्णांक nr, पूर्णांक *err_ptr,
					     pgprot_t prot, अचिन्हित पूर्णांक करोmid,
					     काष्ठा page **pages)
अणु
	अगर (xen_feature(XENFEAT_स्वतः_translated_physmap))
		वापस -EOPNOTSUPP;

	वापस xen_remap_pfn(vma, addr, mfn, nr, err_ptr, prot, करोmid,
			     true, pages);
पूर्ण

/* xen_remap_करोमुख्य_gfn_range() - map a range of क्रमeign frames
 * @vma:     VMA to map the pages पूर्णांकo
 * @addr:    Address at which to map the pages
 * @gfn:     First GFN to map.
 * @nr:      Number frames to map
 * @prot:    page protection mask
 * @करोmid:   Doमुख्य owning the pages
 * @pages:   Array of pages अगर this करोमुख्य has an स्वतः-translated physmap
 *
 * Returns the number of successfully mapped frames, or a -ve error
 * code.
 */
अटल अंतरभूत पूर्णांक xen_remap_करोमुख्य_gfn_range(काष्ठा vm_area_काष्ठा *vma,
					     अचिन्हित दीर्घ addr,
					     xen_pfn_t gfn, पूर्णांक nr,
					     pgprot_t prot, अचिन्हित पूर्णांक करोmid,
					     काष्ठा page **pages)
अणु
	अगर (xen_feature(XENFEAT_स्वतः_translated_physmap))
		वापस -EOPNOTSUPP;

	वापस xen_remap_pfn(vma, addr, &gfn, nr, शून्य, prot, करोmid, false,
			     pages);
पूर्ण

पूर्णांक xen_unmap_करोमुख्य_gfn_range(काष्ठा vm_area_काष्ठा *vma,
			       पूर्णांक numpgs, काष्ठा page **pages);

पूर्णांक xen_xlate_map_ballooned_pages(xen_pfn_t **pfns, व्योम **vaddr,
				  अचिन्हित दीर्घ nr_grant_frames);

bool xen_running_on_version_or_later(अचिन्हित पूर्णांक major, अचिन्हित पूर्णांक minor);

व्योम xen_efi_runसमय_setup(व्योम);


#अगर defined(CONFIG_XEN_PV) && !defined(CONFIG_PREEMPTION)

DECLARE_PER_CPU(bool, xen_in_preemptible_hcall);

अटल अंतरभूत व्योम xen_preemptible_hcall_begin(व्योम)
अणु
	__this_cpu_ग_लिखो(xen_in_preemptible_hcall, true);
पूर्ण

अटल अंतरभूत व्योम xen_preemptible_hcall_end(व्योम)
अणु
	__this_cpu_ग_लिखो(xen_in_preemptible_hcall, false);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम xen_preemptible_hcall_begin(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम xen_preemptible_hcall_end(व्योम) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_XEN_PV && !CONFIG_PREEMPTION */

#पूर्ण_अगर /* INCLUDE_XEN_OPS_H */
