<शैली गुरु>
/*
 * Copyright(c) 2011-2016 Intel Corporation. All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *    Zhenyu Wang <zhenyuw@linux.पूर्णांकel.com>
 *    Xiao Zheng <xiao.zheng@पूर्णांकel.com>
 *
 * Contributors:
 *    Min He <min.he@पूर्णांकel.com>
 *    Bing Niu <bing.niu@पूर्णांकel.com>
 *
 */

#अगर_अघोषित _GVT_GTT_H_
#घोषणा _GVT_GTT_H_

#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/mutex.h>
#समावेश <linux/radix-tree.h>

#समावेश "gt/intel_gtt.h"

काष्ठा पूर्णांकel_gvt;
काष्ठा पूर्णांकel_vgpu;
काष्ठा पूर्णांकel_vgpu_mm;

#घोषणा I915_GTT_PAGE_SHIFT         12

#घोषणा INTEL_GVT_INVALID_ADDR (~0UL)

काष्ठा पूर्णांकel_gvt_gtt_entry अणु
	u64 val64;
	पूर्णांक type;
पूर्ण;

काष्ठा पूर्णांकel_gvt_gtt_pte_ops अणु
	पूर्णांक (*get_entry)(व्योम *pt,
			 काष्ठा पूर्णांकel_gvt_gtt_entry *e,
			 अचिन्हित दीर्घ index,
			 bool hypervisor_access,
			 अचिन्हित दीर्घ gpa,
			 काष्ठा पूर्णांकel_vgpu *vgpu);
	पूर्णांक (*set_entry)(व्योम *pt,
			 काष्ठा पूर्णांकel_gvt_gtt_entry *e,
			 अचिन्हित दीर्घ index,
			 bool hypervisor_access,
			 अचिन्हित दीर्घ gpa,
			 काष्ठा पूर्णांकel_vgpu *vgpu);
	bool (*test_present)(काष्ठा पूर्णांकel_gvt_gtt_entry *e);
	व्योम (*clear_present)(काष्ठा पूर्णांकel_gvt_gtt_entry *e);
	व्योम (*set_present)(काष्ठा पूर्णांकel_gvt_gtt_entry *e);
	bool (*test_pse)(काष्ठा पूर्णांकel_gvt_gtt_entry *e);
	व्योम (*clear_pse)(काष्ठा पूर्णांकel_gvt_gtt_entry *e);
	bool (*test_ips)(काष्ठा पूर्णांकel_gvt_gtt_entry *e);
	व्योम (*clear_ips)(काष्ठा पूर्णांकel_gvt_gtt_entry *e);
	bool (*test_64k_splited)(काष्ठा पूर्णांकel_gvt_gtt_entry *e);
	व्योम (*clear_64k_splited)(काष्ठा पूर्णांकel_gvt_gtt_entry *e);
	व्योम (*set_64k_splited)(काष्ठा पूर्णांकel_gvt_gtt_entry *e);
	व्योम (*set_pfn)(काष्ठा पूर्णांकel_gvt_gtt_entry *e, अचिन्हित दीर्घ pfn);
	अचिन्हित दीर्घ (*get_pfn)(काष्ठा पूर्णांकel_gvt_gtt_entry *e);
पूर्ण;

काष्ठा पूर्णांकel_gvt_gtt_gma_ops अणु
	अचिन्हित दीर्घ (*gma_to_ggtt_pte_index)(अचिन्हित दीर्घ gma);
	अचिन्हित दीर्घ (*gma_to_pte_index)(अचिन्हित दीर्घ gma);
	अचिन्हित दीर्घ (*gma_to_pde_index)(अचिन्हित दीर्घ gma);
	अचिन्हित दीर्घ (*gma_to_l3_pdp_index)(अचिन्हित दीर्घ gma);
	अचिन्हित दीर्घ (*gma_to_l4_pdp_index)(अचिन्हित दीर्घ gma);
	अचिन्हित दीर्घ (*gma_to_pml4_index)(अचिन्हित दीर्घ gma);
पूर्ण;

काष्ठा पूर्णांकel_gvt_gtt अणु
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *pte_ops;
	काष्ठा पूर्णांकel_gvt_gtt_gma_ops *gma_ops;
	पूर्णांक (*mm_alloc_page_table)(काष्ठा पूर्णांकel_vgpu_mm *mm);
	व्योम (*mm_मुक्त_page_table)(काष्ठा पूर्णांकel_vgpu_mm *mm);
	काष्ठा list_head oos_page_use_list_head;
	काष्ठा list_head oos_page_मुक्त_list_head;
	काष्ठा mutex ppgtt_mm_lock;
	काष्ठा list_head ppgtt_mm_lru_list_head;

	काष्ठा page *scratch_page;
	अचिन्हित दीर्घ scratch_mfn;
पूर्ण;

क्रमागत पूर्णांकel_gvt_gtt_type अणु
	GTT_TYPE_INVALID = 0,

	GTT_TYPE_GGTT_PTE,

	GTT_TYPE_PPGTT_PTE_4K_ENTRY,
	GTT_TYPE_PPGTT_PTE_64K_ENTRY,
	GTT_TYPE_PPGTT_PTE_2M_ENTRY,
	GTT_TYPE_PPGTT_PTE_1G_ENTRY,

	GTT_TYPE_PPGTT_PTE_ENTRY,

	GTT_TYPE_PPGTT_PDE_ENTRY,
	GTT_TYPE_PPGTT_PDP_ENTRY,
	GTT_TYPE_PPGTT_PML4_ENTRY,

	GTT_TYPE_PPGTT_ROOT_ENTRY,

	GTT_TYPE_PPGTT_ROOT_L3_ENTRY,
	GTT_TYPE_PPGTT_ROOT_L4_ENTRY,

	GTT_TYPE_PPGTT_ENTRY,

	GTT_TYPE_PPGTT_PTE_PT,
	GTT_TYPE_PPGTT_PDE_PT,
	GTT_TYPE_PPGTT_PDP_PT,
	GTT_TYPE_PPGTT_PML4_PT,

	GTT_TYPE_MAX,
पूर्ण;

क्रमागत पूर्णांकel_gvt_mm_type अणु
	INTEL_GVT_MM_GGTT,
	INTEL_GVT_MM_PPGTT,
पूर्ण;

#घोषणा GVT_RING_CTX_NR_PDPS	GEN8_3LVL_PDPES

काष्ठा पूर्णांकel_gvt_partial_pte अणु
	अचिन्हित दीर्घ offset;
	u64 data;
	काष्ठा list_head list;
पूर्ण;

काष्ठा पूर्णांकel_vgpu_mm अणु
	क्रमागत पूर्णांकel_gvt_mm_type type;
	काष्ठा पूर्णांकel_vgpu *vgpu;

	काष्ठा kref ref;
	atomic_t pincount;

	जोड़ अणु
		काष्ठा अणु
			क्रमागत पूर्णांकel_gvt_gtt_type root_entry_type;
			/*
			 * The 4 PDPs in ring context. For 48bit addressing,
			 * only PDP0 is valid and poपूर्णांक to PML4. For 32it
			 * addressing, all 4 are used as true PDPs.
			 */
			u64 guest_pdps[GVT_RING_CTX_NR_PDPS];
			u64 shaकरोw_pdps[GVT_RING_CTX_NR_PDPS];
			bool shaकरोwed;

			काष्ठा list_head list;
			काष्ठा list_head lru_list;
			काष्ठा list_head link; /* possible LRI shaकरोw mm list */
		पूर्ण ppgtt_mm;
		काष्ठा अणु
			व्योम *भव_ggtt;
			/* Save/restore क्रम PM */
			u64 *host_ggtt_aperture;
			u64 *host_ggtt_hidden;
			काष्ठा list_head partial_pte_list;
		पूर्ण ggtt_mm;
	पूर्ण;
पूर्ण;

काष्ठा पूर्णांकel_vgpu_mm *पूर्णांकel_vgpu_create_ppgtt_mm(काष्ठा पूर्णांकel_vgpu *vgpu,
		क्रमागत पूर्णांकel_gvt_gtt_type root_entry_type, u64 pdps[]);

अटल अंतरभूत व्योम पूर्णांकel_vgpu_mm_get(काष्ठा पूर्णांकel_vgpu_mm *mm)
अणु
	kref_get(&mm->ref);
पूर्ण

व्योम _पूर्णांकel_vgpu_mm_release(काष्ठा kref *mm_ref);

अटल अंतरभूत व्योम पूर्णांकel_vgpu_mm_put(काष्ठा पूर्णांकel_vgpu_mm *mm)
अणु
	kref_put(&mm->ref, _पूर्णांकel_vgpu_mm_release);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_vgpu_destroy_mm(काष्ठा पूर्णांकel_vgpu_mm *mm)
अणु
	पूर्णांकel_vgpu_mm_put(mm);
पूर्ण

काष्ठा पूर्णांकel_vgpu_guest_page;

काष्ठा पूर्णांकel_vgpu_scratch_pt अणु
	काष्ठा page *page;
	अचिन्हित दीर्घ page_mfn;
पूर्ण;

काष्ठा पूर्णांकel_vgpu_gtt अणु
	काष्ठा पूर्णांकel_vgpu_mm *ggtt_mm;
	अचिन्हित दीर्घ active_ppgtt_mm_biपंचांगap;
	काष्ठा list_head ppgtt_mm_list_head;
	काष्ठा radix_tree_root spt_tree;
	काष्ठा list_head oos_page_list_head;
	काष्ठा list_head post_shaकरोw_list_head;
	काष्ठा पूर्णांकel_vgpu_scratch_pt scratch_pt[GTT_TYPE_MAX];
पूर्ण;

पूर्णांक पूर्णांकel_vgpu_init_gtt(काष्ठा पूर्णांकel_vgpu *vgpu);
व्योम पूर्णांकel_vgpu_clean_gtt(काष्ठा पूर्णांकel_vgpu *vgpu);
व्योम पूर्णांकel_vgpu_reset_ggtt(काष्ठा पूर्णांकel_vgpu *vgpu, bool invalidate_old);
व्योम पूर्णांकel_vgpu_invalidate_ppgtt(काष्ठा पूर्णांकel_vgpu *vgpu);

पूर्णांक पूर्णांकel_gvt_init_gtt(काष्ठा पूर्णांकel_gvt *gvt);
व्योम पूर्णांकel_vgpu_reset_gtt(काष्ठा पूर्णांकel_vgpu *vgpu);
व्योम पूर्णांकel_gvt_clean_gtt(काष्ठा पूर्णांकel_gvt *gvt);

काष्ठा पूर्णांकel_vgpu_mm *पूर्णांकel_gvt_find_ppgtt_mm(काष्ठा पूर्णांकel_vgpu *vgpu,
					      पूर्णांक page_table_level,
					      व्योम *root_entry);

काष्ठा पूर्णांकel_vgpu_oos_page अणु
	काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt;
	काष्ठा list_head list;
	काष्ठा list_head vm_list;
	पूर्णांक id;
	व्योम *mem;
पूर्ण;

#घोषणा GTT_ENTRY_NUM_IN_ONE_PAGE 512

/* Represent a vgpu shaकरोw page table. */
काष्ठा पूर्णांकel_vgpu_ppgtt_spt अणु
	atomic_t refcount;
	काष्ठा पूर्णांकel_vgpu *vgpu;

	काष्ठा अणु
		क्रमागत पूर्णांकel_gvt_gtt_type type;
		bool pde_ips; /* क्रम 64KB PTEs */
		व्योम *vaddr;
		काष्ठा page *page;
		अचिन्हित दीर्घ mfn;
	पूर्ण shaकरोw_page;

	काष्ठा अणु
		क्रमागत पूर्णांकel_gvt_gtt_type type;
		bool pde_ips; /* क्रम 64KB PTEs */
		अचिन्हित दीर्घ gfn;
		अचिन्हित दीर्घ ग_लिखो_cnt;
		काष्ठा पूर्णांकel_vgpu_oos_page *oos_page;
	पूर्ण guest_page;

	DECLARE_BITMAP(post_shaकरोw_biपंचांगap, GTT_ENTRY_NUM_IN_ONE_PAGE);
	काष्ठा list_head post_shaकरोw_list;
पूर्ण;

पूर्णांक पूर्णांकel_vgpu_sync_oos_pages(काष्ठा पूर्णांकel_vgpu *vgpu);

पूर्णांक पूर्णांकel_vgpu_flush_post_shaकरोw(काष्ठा पूर्णांकel_vgpu *vgpu);

पूर्णांक पूर्णांकel_vgpu_pin_mm(काष्ठा पूर्णांकel_vgpu_mm *mm);

व्योम पूर्णांकel_vgpu_unpin_mm(काष्ठा पूर्णांकel_vgpu_mm *mm);

अचिन्हित दीर्घ पूर्णांकel_vgpu_gma_to_gpa(काष्ठा पूर्णांकel_vgpu_mm *mm,
		अचिन्हित दीर्घ gma);

काष्ठा पूर्णांकel_vgpu_mm *पूर्णांकel_vgpu_find_ppgtt_mm(काष्ठा पूर्णांकel_vgpu *vgpu,
		u64 pdps[]);

काष्ठा पूर्णांकel_vgpu_mm *पूर्णांकel_vgpu_get_ppgtt_mm(काष्ठा पूर्णांकel_vgpu *vgpu,
		क्रमागत पूर्णांकel_gvt_gtt_type root_entry_type, u64 pdps[]);

पूर्णांक पूर्णांकel_vgpu_put_ppgtt_mm(काष्ठा पूर्णांकel_vgpu *vgpu, u64 pdps[]);

पूर्णांक पूर्णांकel_vgpu_emulate_ggtt_mmio_पढ़ो(काष्ठा पूर्णांकel_vgpu *vgpu,
	अचिन्हित पूर्णांक off, व्योम *p_data, अचिन्हित पूर्णांक bytes);

पूर्णांक पूर्णांकel_vgpu_emulate_ggtt_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
	अचिन्हित पूर्णांक off, व्योम *p_data, अचिन्हित पूर्णांक bytes);

व्योम पूर्णांकel_vgpu_destroy_all_ppgtt_mm(काष्ठा पूर्णांकel_vgpu *vgpu);
व्योम पूर्णांकel_gvt_restore_ggtt(काष्ठा पूर्णांकel_gvt *gvt);

#पूर्ण_अगर /* _GVT_GTT_H_ */
