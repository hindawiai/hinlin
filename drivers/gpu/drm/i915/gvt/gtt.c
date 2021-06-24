<शैली गुरु>
/*
 * GTT भवization
 *
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

#समावेश "i915_drv.h"
#समावेश "gvt.h"
#समावेश "i915_pvinfo.h"
#समावेश "trace.h"

#अगर defined(VERBOSE_DEBUG)
#घोषणा gvt_vdbg_mm(fmt, args...) gvt_dbg_mm(fmt, ##args)
#अन्यथा
#घोषणा gvt_vdbg_mm(fmt, args...)
#पूर्ण_अगर

अटल bool enable_out_of_sync = false;
अटल पूर्णांक pपुनः_स्मृतिated_oos_pages = 8192;

/*
 * validate a gm address and related range size,
 * translate it to host gm address
 */
bool पूर्णांकel_gvt_ggtt_validate_range(काष्ठा पूर्णांकel_vgpu *vgpu, u64 addr, u32 size)
अणु
	अगर (size == 0)
		वापस vgpu_gmadr_is_valid(vgpu, addr);

	अगर (vgpu_gmadr_is_aperture(vgpu, addr) &&
	    vgpu_gmadr_is_aperture(vgpu, addr + size - 1))
		वापस true;
	अन्यथा अगर (vgpu_gmadr_is_hidden(vgpu, addr) &&
		 vgpu_gmadr_is_hidden(vgpu, addr + size - 1))
		वापस true;

	gvt_dbg_mm("Invalid ggtt range at 0x%llx, size: 0x%x\n",
		     addr, size);
	वापस false;
पूर्ण

/* translate a guest gmadr to host gmadr */
पूर्णांक पूर्णांकel_gvt_ggtt_gmadr_g2h(काष्ठा पूर्णांकel_vgpu *vgpu, u64 g_addr, u64 *h_addr)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;

	अगर (drm_WARN(&i915->drm, !vgpu_gmadr_is_valid(vgpu, g_addr),
		     "invalid guest gmadr %llx\n", g_addr))
		वापस -EACCES;

	अगर (vgpu_gmadr_is_aperture(vgpu, g_addr))
		*h_addr = vgpu_aperture_gmadr_base(vgpu)
			  + (g_addr - vgpu_aperture_offset(vgpu));
	अन्यथा
		*h_addr = vgpu_hidden_gmadr_base(vgpu)
			  + (g_addr - vgpu_hidden_offset(vgpu));
	वापस 0;
पूर्ण

/* translate a host gmadr to guest gmadr */
पूर्णांक पूर्णांकel_gvt_ggtt_gmadr_h2g(काष्ठा पूर्णांकel_vgpu *vgpu, u64 h_addr, u64 *g_addr)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;

	अगर (drm_WARN(&i915->drm, !gvt_gmadr_is_valid(vgpu->gvt, h_addr),
		     "invalid host gmadr %llx\n", h_addr))
		वापस -EACCES;

	अगर (gvt_gmadr_is_aperture(vgpu->gvt, h_addr))
		*g_addr = vgpu_aperture_gmadr_base(vgpu)
			+ (h_addr - gvt_aperture_gmadr_base(vgpu->gvt));
	अन्यथा
		*g_addr = vgpu_hidden_gmadr_base(vgpu)
			+ (h_addr - gvt_hidden_gmadr_base(vgpu->gvt));
	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_gvt_ggtt_index_g2h(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ g_index,
			     अचिन्हित दीर्घ *h_index)
अणु
	u64 h_addr;
	पूर्णांक ret;

	ret = पूर्णांकel_gvt_ggtt_gmadr_g2h(vgpu, g_index << I915_GTT_PAGE_SHIFT,
				       &h_addr);
	अगर (ret)
		वापस ret;

	*h_index = h_addr >> I915_GTT_PAGE_SHIFT;
	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_gvt_ggtt_h2g_index(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ h_index,
			     अचिन्हित दीर्घ *g_index)
अणु
	u64 g_addr;
	पूर्णांक ret;

	ret = पूर्णांकel_gvt_ggtt_gmadr_h2g(vgpu, h_index << I915_GTT_PAGE_SHIFT,
				       &g_addr);
	अगर (ret)
		वापस ret;

	*g_index = g_addr >> I915_GTT_PAGE_SHIFT;
	वापस 0;
पूर्ण

#घोषणा gtt_type_is_entry(type) \
	(type > GTT_TYPE_INVALID && type < GTT_TYPE_PPGTT_ENTRY \
	 && type != GTT_TYPE_PPGTT_PTE_ENTRY \
	 && type != GTT_TYPE_PPGTT_ROOT_ENTRY)

#घोषणा gtt_type_is_pt(type) \
	(type >= GTT_TYPE_PPGTT_PTE_PT && type < GTT_TYPE_MAX)

#घोषणा gtt_type_is_pte_pt(type) \
	(type == GTT_TYPE_PPGTT_PTE_PT)

#घोषणा gtt_type_is_root_poपूर्णांकer(type) \
	(gtt_type_is_entry(type) && type > GTT_TYPE_PPGTT_ROOT_ENTRY)

#घोषणा gtt_init_entry(e, t, p, v) करो अणु \
	(e)->type = t; \
	(e)->pdev = p; \
	स_नकल(&(e)->val64, &v, माप(v)); \
पूर्ण जबतक (0)

/*
 * Mappings between GTT_TYPE* क्रमागतerations.
 * Following inक्रमmation can be found according to the given type:
 * - type of next level page table
 * - type of entry inside this level page table
 * - type of entry with PSE set
 *
 * If the given type करोesn't have such a kind of inक्रमmation,
 * e.g. give a l4 root entry type, then request to get its PSE type,
 * give a PTE page table type, then request to get its next level page
 * table type, as we know l4 root entry करोesn't have a PSE bit,
 * and a PTE page table करोesn't have a next level page table type,
 * GTT_TYPE_INVALID will be वापसed. This is useful when traversing a
 * page table.
 */

काष्ठा gtt_type_table_entry अणु
	पूर्णांक entry_type;
	पूर्णांक pt_type;
	पूर्णांक next_pt_type;
	पूर्णांक pse_entry_type;
पूर्ण;

#घोषणा GTT_TYPE_TABLE_ENTRY(type, e_type, cpt_type, npt_type, pse_type) \
	[type] = अणु \
		.entry_type = e_type, \
		.pt_type = cpt_type, \
		.next_pt_type = npt_type, \
		.pse_entry_type = pse_type, \
	पूर्ण

अटल काष्ठा gtt_type_table_entry gtt_type_table[] = अणु
	GTT_TYPE_TABLE_ENTRY(GTT_TYPE_PPGTT_ROOT_L4_ENTRY,
			GTT_TYPE_PPGTT_ROOT_L4_ENTRY,
			GTT_TYPE_INVALID,
			GTT_TYPE_PPGTT_PML4_PT,
			GTT_TYPE_INVALID),
	GTT_TYPE_TABLE_ENTRY(GTT_TYPE_PPGTT_PML4_PT,
			GTT_TYPE_PPGTT_PML4_ENTRY,
			GTT_TYPE_PPGTT_PML4_PT,
			GTT_TYPE_PPGTT_PDP_PT,
			GTT_TYPE_INVALID),
	GTT_TYPE_TABLE_ENTRY(GTT_TYPE_PPGTT_PML4_ENTRY,
			GTT_TYPE_PPGTT_PML4_ENTRY,
			GTT_TYPE_PPGTT_PML4_PT,
			GTT_TYPE_PPGTT_PDP_PT,
			GTT_TYPE_INVALID),
	GTT_TYPE_TABLE_ENTRY(GTT_TYPE_PPGTT_PDP_PT,
			GTT_TYPE_PPGTT_PDP_ENTRY,
			GTT_TYPE_PPGTT_PDP_PT,
			GTT_TYPE_PPGTT_PDE_PT,
			GTT_TYPE_PPGTT_PTE_1G_ENTRY),
	GTT_TYPE_TABLE_ENTRY(GTT_TYPE_PPGTT_ROOT_L3_ENTRY,
			GTT_TYPE_PPGTT_ROOT_L3_ENTRY,
			GTT_TYPE_INVALID,
			GTT_TYPE_PPGTT_PDE_PT,
			GTT_TYPE_PPGTT_PTE_1G_ENTRY),
	GTT_TYPE_TABLE_ENTRY(GTT_TYPE_PPGTT_PDP_ENTRY,
			GTT_TYPE_PPGTT_PDP_ENTRY,
			GTT_TYPE_PPGTT_PDP_PT,
			GTT_TYPE_PPGTT_PDE_PT,
			GTT_TYPE_PPGTT_PTE_1G_ENTRY),
	GTT_TYPE_TABLE_ENTRY(GTT_TYPE_PPGTT_PDE_PT,
			GTT_TYPE_PPGTT_PDE_ENTRY,
			GTT_TYPE_PPGTT_PDE_PT,
			GTT_TYPE_PPGTT_PTE_PT,
			GTT_TYPE_PPGTT_PTE_2M_ENTRY),
	GTT_TYPE_TABLE_ENTRY(GTT_TYPE_PPGTT_PDE_ENTRY,
			GTT_TYPE_PPGTT_PDE_ENTRY,
			GTT_TYPE_PPGTT_PDE_PT,
			GTT_TYPE_PPGTT_PTE_PT,
			GTT_TYPE_PPGTT_PTE_2M_ENTRY),
	/* We take IPS bit as 'PSE' क्रम PTE level. */
	GTT_TYPE_TABLE_ENTRY(GTT_TYPE_PPGTT_PTE_PT,
			GTT_TYPE_PPGTT_PTE_4K_ENTRY,
			GTT_TYPE_PPGTT_PTE_PT,
			GTT_TYPE_INVALID,
			GTT_TYPE_PPGTT_PTE_64K_ENTRY),
	GTT_TYPE_TABLE_ENTRY(GTT_TYPE_PPGTT_PTE_4K_ENTRY,
			GTT_TYPE_PPGTT_PTE_4K_ENTRY,
			GTT_TYPE_PPGTT_PTE_PT,
			GTT_TYPE_INVALID,
			GTT_TYPE_PPGTT_PTE_64K_ENTRY),
	GTT_TYPE_TABLE_ENTRY(GTT_TYPE_PPGTT_PTE_64K_ENTRY,
			GTT_TYPE_PPGTT_PTE_4K_ENTRY,
			GTT_TYPE_PPGTT_PTE_PT,
			GTT_TYPE_INVALID,
			GTT_TYPE_PPGTT_PTE_64K_ENTRY),
	GTT_TYPE_TABLE_ENTRY(GTT_TYPE_PPGTT_PTE_2M_ENTRY,
			GTT_TYPE_PPGTT_PDE_ENTRY,
			GTT_TYPE_PPGTT_PDE_PT,
			GTT_TYPE_INVALID,
			GTT_TYPE_PPGTT_PTE_2M_ENTRY),
	GTT_TYPE_TABLE_ENTRY(GTT_TYPE_PPGTT_PTE_1G_ENTRY,
			GTT_TYPE_PPGTT_PDP_ENTRY,
			GTT_TYPE_PPGTT_PDP_PT,
			GTT_TYPE_INVALID,
			GTT_TYPE_PPGTT_PTE_1G_ENTRY),
	GTT_TYPE_TABLE_ENTRY(GTT_TYPE_GGTT_PTE,
			GTT_TYPE_GGTT_PTE,
			GTT_TYPE_INVALID,
			GTT_TYPE_INVALID,
			GTT_TYPE_INVALID),
पूर्ण;

अटल अंतरभूत पूर्णांक get_next_pt_type(पूर्णांक type)
अणु
	वापस gtt_type_table[type].next_pt_type;
पूर्ण

अटल अंतरभूत पूर्णांक get_pt_type(पूर्णांक type)
अणु
	वापस gtt_type_table[type].pt_type;
पूर्ण

अटल अंतरभूत पूर्णांक get_entry_type(पूर्णांक type)
अणु
	वापस gtt_type_table[type].entry_type;
पूर्ण

अटल अंतरभूत पूर्णांक get_pse_type(पूर्णांक type)
अणु
	वापस gtt_type_table[type].pse_entry_type;
पूर्ण

अटल u64 पढ़ो_pte64(काष्ठा i915_ggtt *ggtt, अचिन्हित दीर्घ index)
अणु
	व्योम __iomem *addr = (gen8_pte_t __iomem *)ggtt->gsm + index;

	वापस पढ़ोq(addr);
पूर्ण

अटल व्योम ggtt_invalidate(काष्ठा पूर्णांकel_gt *gt)
अणु
	mmio_hw_access_pre(gt);
	पूर्णांकel_uncore_ग_लिखो(gt->uncore, GFX_FLSH_CNTL_GEN6, GFX_FLSH_CNTL_EN);
	mmio_hw_access_post(gt);
पूर्ण

अटल व्योम ग_लिखो_pte64(काष्ठा i915_ggtt *ggtt, अचिन्हित दीर्घ index, u64 pte)
अणु
	व्योम __iomem *addr = (gen8_pte_t __iomem *)ggtt->gsm + index;

	ग_लिखोq(pte, addr);
पूर्ण

अटल अंतरभूत पूर्णांक gtt_get_entry64(व्योम *pt,
		काष्ठा पूर्णांकel_gvt_gtt_entry *e,
		अचिन्हित दीर्घ index, bool hypervisor_access, अचिन्हित दीर्घ gpa,
		काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	स्थिर काष्ठा पूर्णांकel_gvt_device_info *info = &vgpu->gvt->device_info;
	पूर्णांक ret;

	अगर (WARN_ON(info->gtt_entry_size != 8))
		वापस -EINVAL;

	अगर (hypervisor_access) अणु
		ret = पूर्णांकel_gvt_hypervisor_पढ़ो_gpa(vgpu, gpa +
				(index << info->gtt_entry_size_shअगरt),
				&e->val64, 8);
		अगर (WARN_ON(ret))
			वापस ret;
	पूर्ण अन्यथा अगर (!pt) अणु
		e->val64 = पढ़ो_pte64(vgpu->gvt->gt->ggtt, index);
	पूर्ण अन्यथा अणु
		e->val64 = *((u64 *)pt + index);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक gtt_set_entry64(व्योम *pt,
		काष्ठा पूर्णांकel_gvt_gtt_entry *e,
		अचिन्हित दीर्घ index, bool hypervisor_access, अचिन्हित दीर्घ gpa,
		काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	स्थिर काष्ठा पूर्णांकel_gvt_device_info *info = &vgpu->gvt->device_info;
	पूर्णांक ret;

	अगर (WARN_ON(info->gtt_entry_size != 8))
		वापस -EINVAL;

	अगर (hypervisor_access) अणु
		ret = पूर्णांकel_gvt_hypervisor_ग_लिखो_gpa(vgpu, gpa +
				(index << info->gtt_entry_size_shअगरt),
				&e->val64, 8);
		अगर (WARN_ON(ret))
			वापस ret;
	पूर्ण अन्यथा अगर (!pt) अणु
		ग_लिखो_pte64(vgpu->gvt->gt->ggtt, index, e->val64);
	पूर्ण अन्यथा अणु
		*((u64 *)pt + index) = e->val64;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा GTT_HAW 46

#घोषणा ADDR_1G_MASK	GENMASK_ULL(GTT_HAW - 1, 30)
#घोषणा ADDR_2M_MASK	GENMASK_ULL(GTT_HAW - 1, 21)
#घोषणा ADDR_64K_MASK	GENMASK_ULL(GTT_HAW - 1, 16)
#घोषणा ADDR_4K_MASK	GENMASK_ULL(GTT_HAW - 1, 12)

#घोषणा GTT_SPTE_FLAG_MASK GENMASK_ULL(62, 52)
#घोषणा GTT_SPTE_FLAG_64K_SPLITED BIT(52) /* splited 64K gtt entry */

#घोषणा GTT_64K_PTE_STRIDE 16

अटल अचिन्हित दीर्घ gen8_gtt_get_pfn(काष्ठा पूर्णांकel_gvt_gtt_entry *e)
अणु
	अचिन्हित दीर्घ pfn;

	अगर (e->type == GTT_TYPE_PPGTT_PTE_1G_ENTRY)
		pfn = (e->val64 & ADDR_1G_MASK) >> PAGE_SHIFT;
	अन्यथा अगर (e->type == GTT_TYPE_PPGTT_PTE_2M_ENTRY)
		pfn = (e->val64 & ADDR_2M_MASK) >> PAGE_SHIFT;
	अन्यथा अगर (e->type == GTT_TYPE_PPGTT_PTE_64K_ENTRY)
		pfn = (e->val64 & ADDR_64K_MASK) >> PAGE_SHIFT;
	अन्यथा
		pfn = (e->val64 & ADDR_4K_MASK) >> PAGE_SHIFT;
	वापस pfn;
पूर्ण

अटल व्योम gen8_gtt_set_pfn(काष्ठा पूर्णांकel_gvt_gtt_entry *e, अचिन्हित दीर्घ pfn)
अणु
	अगर (e->type == GTT_TYPE_PPGTT_PTE_1G_ENTRY) अणु
		e->val64 &= ~ADDR_1G_MASK;
		pfn &= (ADDR_1G_MASK >> PAGE_SHIFT);
	पूर्ण अन्यथा अगर (e->type == GTT_TYPE_PPGTT_PTE_2M_ENTRY) अणु
		e->val64 &= ~ADDR_2M_MASK;
		pfn &= (ADDR_2M_MASK >> PAGE_SHIFT);
	पूर्ण अन्यथा अगर (e->type == GTT_TYPE_PPGTT_PTE_64K_ENTRY) अणु
		e->val64 &= ~ADDR_64K_MASK;
		pfn &= (ADDR_64K_MASK >> PAGE_SHIFT);
	पूर्ण अन्यथा अणु
		e->val64 &= ~ADDR_4K_MASK;
		pfn &= (ADDR_4K_MASK >> PAGE_SHIFT);
	पूर्ण

	e->val64 |= (pfn << PAGE_SHIFT);
पूर्ण

अटल bool gen8_gtt_test_pse(काष्ठा पूर्णांकel_gvt_gtt_entry *e)
अणु
	वापस !!(e->val64 & _PAGE_PSE);
पूर्ण

अटल व्योम gen8_gtt_clear_pse(काष्ठा पूर्णांकel_gvt_gtt_entry *e)
अणु
	अगर (gen8_gtt_test_pse(e)) अणु
		चयन (e->type) अणु
		हाल GTT_TYPE_PPGTT_PTE_2M_ENTRY:
			e->val64 &= ~_PAGE_PSE;
			e->type = GTT_TYPE_PPGTT_PDE_ENTRY;
			अवरोध;
		हाल GTT_TYPE_PPGTT_PTE_1G_ENTRY:
			e->type = GTT_TYPE_PPGTT_PDP_ENTRY;
			e->val64 &= ~_PAGE_PSE;
			अवरोध;
		शेष:
			WARN_ON(1);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool gen8_gtt_test_ips(काष्ठा पूर्णांकel_gvt_gtt_entry *e)
अणु
	अगर (GEM_WARN_ON(e->type != GTT_TYPE_PPGTT_PDE_ENTRY))
		वापस false;

	वापस !!(e->val64 & GEN8_PDE_IPS_64K);
पूर्ण

अटल व्योम gen8_gtt_clear_ips(काष्ठा पूर्णांकel_gvt_gtt_entry *e)
अणु
	अगर (GEM_WARN_ON(e->type != GTT_TYPE_PPGTT_PDE_ENTRY))
		वापस;

	e->val64 &= ~GEN8_PDE_IPS_64K;
पूर्ण

अटल bool gen8_gtt_test_present(काष्ठा पूर्णांकel_gvt_gtt_entry *e)
अणु
	/*
	 * i915 ग_लिखोs PDP root poपूर्णांकer रेजिस्टरs without present bit,
	 * it also works, so we need to treat root poपूर्णांकer entry
	 * specअगरically.
	 */
	अगर (e->type == GTT_TYPE_PPGTT_ROOT_L3_ENTRY
			|| e->type == GTT_TYPE_PPGTT_ROOT_L4_ENTRY)
		वापस (e->val64 != 0);
	अन्यथा
		वापस (e->val64 & _PAGE_PRESENT);
पूर्ण

अटल व्योम gtt_entry_clear_present(काष्ठा पूर्णांकel_gvt_gtt_entry *e)
अणु
	e->val64 &= ~_PAGE_PRESENT;
पूर्ण

अटल व्योम gtt_entry_set_present(काष्ठा पूर्णांकel_gvt_gtt_entry *e)
अणु
	e->val64 |= _PAGE_PRESENT;
पूर्ण

अटल bool gen8_gtt_test_64k_splited(काष्ठा पूर्णांकel_gvt_gtt_entry *e)
अणु
	वापस !!(e->val64 & GTT_SPTE_FLAG_64K_SPLITED);
पूर्ण

अटल व्योम gen8_gtt_set_64k_splited(काष्ठा पूर्णांकel_gvt_gtt_entry *e)
अणु
	e->val64 |= GTT_SPTE_FLAG_64K_SPLITED;
पूर्ण

अटल व्योम gen8_gtt_clear_64k_splited(काष्ठा पूर्णांकel_gvt_gtt_entry *e)
अणु
	e->val64 &= ~GTT_SPTE_FLAG_64K_SPLITED;
पूर्ण

/*
 * Per-platक्रमm GMA routines.
 */
अटल अचिन्हित दीर्घ gma_to_ggtt_pte_index(अचिन्हित दीर्घ gma)
अणु
	अचिन्हित दीर्घ x = (gma >> I915_GTT_PAGE_SHIFT);

	trace_gma_index(__func__, gma, x);
	वापस x;
पूर्ण

#घोषणा DEFINE_PPGTT_GMA_TO_INDEX(prefix, ename, exp) \
अटल अचिन्हित दीर्घ prefix##_gma_to_##ename##_index(अचिन्हित दीर्घ gma) \
अणु \
	अचिन्हित दीर्घ x = (exp); \
	trace_gma_index(__func__, gma, x); \
	वापस x; \
पूर्ण

DEFINE_PPGTT_GMA_TO_INDEX(gen8, pte, (gma >> 12 & 0x1ff));
DEFINE_PPGTT_GMA_TO_INDEX(gen8, pde, (gma >> 21 & 0x1ff));
DEFINE_PPGTT_GMA_TO_INDEX(gen8, l3_pdp, (gma >> 30 & 0x3));
DEFINE_PPGTT_GMA_TO_INDEX(gen8, l4_pdp, (gma >> 30 & 0x1ff));
DEFINE_PPGTT_GMA_TO_INDEX(gen8, pml4, (gma >> 39 & 0x1ff));

अटल काष्ठा पूर्णांकel_gvt_gtt_pte_ops gen8_gtt_pte_ops = अणु
	.get_entry = gtt_get_entry64,
	.set_entry = gtt_set_entry64,
	.clear_present = gtt_entry_clear_present,
	.set_present = gtt_entry_set_present,
	.test_present = gen8_gtt_test_present,
	.test_pse = gen8_gtt_test_pse,
	.clear_pse = gen8_gtt_clear_pse,
	.clear_ips = gen8_gtt_clear_ips,
	.test_ips = gen8_gtt_test_ips,
	.clear_64k_splited = gen8_gtt_clear_64k_splited,
	.set_64k_splited = gen8_gtt_set_64k_splited,
	.test_64k_splited = gen8_gtt_test_64k_splited,
	.get_pfn = gen8_gtt_get_pfn,
	.set_pfn = gen8_gtt_set_pfn,
पूर्ण;

अटल काष्ठा पूर्णांकel_gvt_gtt_gma_ops gen8_gtt_gma_ops = अणु
	.gma_to_ggtt_pte_index = gma_to_ggtt_pte_index,
	.gma_to_pte_index = gen8_gma_to_pte_index,
	.gma_to_pde_index = gen8_gma_to_pde_index,
	.gma_to_l3_pdp_index = gen8_gma_to_l3_pdp_index,
	.gma_to_l4_pdp_index = gen8_gma_to_l4_pdp_index,
	.gma_to_pml4_index = gen8_gma_to_pml4_index,
पूर्ण;

/* Update entry type per pse and ips bit. */
अटल व्योम update_entry_type_क्रम_real(काष्ठा पूर्णांकel_gvt_gtt_pte_ops *pte_ops,
	काष्ठा पूर्णांकel_gvt_gtt_entry *entry, bool ips)
अणु
	चयन (entry->type) अणु
	हाल GTT_TYPE_PPGTT_PDE_ENTRY:
	हाल GTT_TYPE_PPGTT_PDP_ENTRY:
		अगर (pte_ops->test_pse(entry))
			entry->type = get_pse_type(entry->type);
		अवरोध;
	हाल GTT_TYPE_PPGTT_PTE_4K_ENTRY:
		अगर (ips)
			entry->type = get_pse_type(entry->type);
		अवरोध;
	शेष:
		GEM_BUG_ON(!gtt_type_is_entry(entry->type));
	पूर्ण

	GEM_BUG_ON(entry->type == GTT_TYPE_INVALID);
पूर्ण

/*
 * MM helpers.
 */
अटल व्योम _ppgtt_get_root_entry(काष्ठा पूर्णांकel_vgpu_mm *mm,
		काष्ठा पूर्णांकel_gvt_gtt_entry *entry, अचिन्हित दीर्घ index,
		bool guest)
अणु
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *pte_ops = mm->vgpu->gvt->gtt.pte_ops;

	GEM_BUG_ON(mm->type != INTEL_GVT_MM_PPGTT);

	entry->type = mm->ppgtt_mm.root_entry_type;
	pte_ops->get_entry(guest ? mm->ppgtt_mm.guest_pdps :
			   mm->ppgtt_mm.shaकरोw_pdps,
			   entry, index, false, 0, mm->vgpu);
	update_entry_type_क्रम_real(pte_ops, entry, false);
पूर्ण

अटल अंतरभूत व्योम ppgtt_get_guest_root_entry(काष्ठा पूर्णांकel_vgpu_mm *mm,
		काष्ठा पूर्णांकel_gvt_gtt_entry *entry, अचिन्हित दीर्घ index)
अणु
	_ppgtt_get_root_entry(mm, entry, index, true);
पूर्ण

अटल अंतरभूत व्योम ppgtt_get_shaकरोw_root_entry(काष्ठा पूर्णांकel_vgpu_mm *mm,
		काष्ठा पूर्णांकel_gvt_gtt_entry *entry, अचिन्हित दीर्घ index)
अणु
	_ppgtt_get_root_entry(mm, entry, index, false);
पूर्ण

अटल व्योम _ppgtt_set_root_entry(काष्ठा पूर्णांकel_vgpu_mm *mm,
		काष्ठा पूर्णांकel_gvt_gtt_entry *entry, अचिन्हित दीर्घ index,
		bool guest)
अणु
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *pte_ops = mm->vgpu->gvt->gtt.pte_ops;

	pte_ops->set_entry(guest ? mm->ppgtt_mm.guest_pdps :
			   mm->ppgtt_mm.shaकरोw_pdps,
			   entry, index, false, 0, mm->vgpu);
पूर्ण

अटल अंतरभूत व्योम ppgtt_set_shaकरोw_root_entry(काष्ठा पूर्णांकel_vgpu_mm *mm,
		काष्ठा पूर्णांकel_gvt_gtt_entry *entry, अचिन्हित दीर्घ index)
अणु
	_ppgtt_set_root_entry(mm, entry, index, false);
पूर्ण

अटल व्योम ggtt_get_guest_entry(काष्ठा पूर्णांकel_vgpu_mm *mm,
		काष्ठा पूर्णांकel_gvt_gtt_entry *entry, अचिन्हित दीर्घ index)
अणु
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *pte_ops = mm->vgpu->gvt->gtt.pte_ops;

	GEM_BUG_ON(mm->type != INTEL_GVT_MM_GGTT);

	entry->type = GTT_TYPE_GGTT_PTE;
	pte_ops->get_entry(mm->ggtt_mm.भव_ggtt, entry, index,
			   false, 0, mm->vgpu);
पूर्ण

अटल व्योम ggtt_set_guest_entry(काष्ठा पूर्णांकel_vgpu_mm *mm,
		काष्ठा पूर्णांकel_gvt_gtt_entry *entry, अचिन्हित दीर्घ index)
अणु
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *pte_ops = mm->vgpu->gvt->gtt.pte_ops;

	GEM_BUG_ON(mm->type != INTEL_GVT_MM_GGTT);

	pte_ops->set_entry(mm->ggtt_mm.भव_ggtt, entry, index,
			   false, 0, mm->vgpu);
पूर्ण

अटल व्योम ggtt_get_host_entry(काष्ठा पूर्णांकel_vgpu_mm *mm,
		काष्ठा पूर्णांकel_gvt_gtt_entry *entry, अचिन्हित दीर्घ index)
अणु
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *pte_ops = mm->vgpu->gvt->gtt.pte_ops;

	GEM_BUG_ON(mm->type != INTEL_GVT_MM_GGTT);

	pte_ops->get_entry(शून्य, entry, index, false, 0, mm->vgpu);
पूर्ण

अटल व्योम ggtt_set_host_entry(काष्ठा पूर्णांकel_vgpu_mm *mm,
		काष्ठा पूर्णांकel_gvt_gtt_entry *entry, अचिन्हित दीर्घ index)
अणु
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *pte_ops = mm->vgpu->gvt->gtt.pte_ops;
	अचिन्हित दीर्घ offset = index;

	GEM_BUG_ON(mm->type != INTEL_GVT_MM_GGTT);

	अगर (vgpu_gmadr_is_aperture(mm->vgpu, index << I915_GTT_PAGE_SHIFT)) अणु
		offset -= (vgpu_aperture_gmadr_base(mm->vgpu) >> PAGE_SHIFT);
		mm->ggtt_mm.host_ggtt_aperture[offset] = entry->val64;
	पूर्ण अन्यथा अगर (vgpu_gmadr_is_hidden(mm->vgpu, index << I915_GTT_PAGE_SHIFT)) अणु
		offset -= (vgpu_hidden_gmadr_base(mm->vgpu) >> PAGE_SHIFT);
		mm->ggtt_mm.host_ggtt_hidden[offset] = entry->val64;
	पूर्ण

	pte_ops->set_entry(शून्य, entry, index, false, 0, mm->vgpu);
पूर्ण

/*
 * PPGTT shaकरोw page table helpers.
 */
अटल अंतरभूत पूर्णांक ppgtt_spt_get_entry(
		काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt,
		व्योम *page_table, पूर्णांक type,
		काष्ठा पूर्णांकel_gvt_gtt_entry *e, अचिन्हित दीर्घ index,
		bool guest)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = spt->vgpu->gvt;
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *ops = gvt->gtt.pte_ops;
	पूर्णांक ret;

	e->type = get_entry_type(type);

	अगर (WARN(!gtt_type_is_entry(e->type), "invalid entry type\n"))
		वापस -EINVAL;

	ret = ops->get_entry(page_table, e, index, guest,
			spt->guest_page.gfn << I915_GTT_PAGE_SHIFT,
			spt->vgpu);
	अगर (ret)
		वापस ret;

	update_entry_type_क्रम_real(ops, e, guest ?
				   spt->guest_page.pde_ips : false);

	gvt_vdbg_mm("read ppgtt entry, spt type %d, entry type %d, index %lu, value %llx\n",
		    type, e->type, index, e->val64);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ppgtt_spt_set_entry(
		काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt,
		व्योम *page_table, पूर्णांक type,
		काष्ठा पूर्णांकel_gvt_gtt_entry *e, अचिन्हित दीर्घ index,
		bool guest)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = spt->vgpu->gvt;
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *ops = gvt->gtt.pte_ops;

	अगर (WARN(!gtt_type_is_entry(e->type), "invalid entry type\n"))
		वापस -EINVAL;

	gvt_vdbg_mm("set ppgtt entry, spt type %d, entry type %d, index %lu, value %llx\n",
		    type, e->type, index, e->val64);

	वापस ops->set_entry(page_table, e, index, guest,
			spt->guest_page.gfn << I915_GTT_PAGE_SHIFT,
			spt->vgpu);
पूर्ण

#घोषणा ppgtt_get_guest_entry(spt, e, index) \
	ppgtt_spt_get_entry(spt, शून्य, \
		spt->guest_page.type, e, index, true)

#घोषणा ppgtt_set_guest_entry(spt, e, index) \
	ppgtt_spt_set_entry(spt, शून्य, \
		spt->guest_page.type, e, index, true)

#घोषणा ppgtt_get_shaकरोw_entry(spt, e, index) \
	ppgtt_spt_get_entry(spt, spt->shaकरोw_page.vaddr, \
		spt->shaकरोw_page.type, e, index, false)

#घोषणा ppgtt_set_shaकरोw_entry(spt, e, index) \
	ppgtt_spt_set_entry(spt, spt->shaकरोw_page.vaddr, \
		spt->shaकरोw_page.type, e, index, false)

अटल व्योम *alloc_spt(gfp_t gfp_mask)
अणु
	काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt;

	spt = kzalloc(माप(*spt), gfp_mask);
	अगर (!spt)
		वापस शून्य;

	spt->shaकरोw_page.page = alloc_page(gfp_mask);
	अगर (!spt->shaकरोw_page.page) अणु
		kमुक्त(spt);
		वापस शून्य;
	पूर्ण
	वापस spt;
पूर्ण

अटल व्योम मुक्त_spt(काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt)
अणु
	__मुक्त_page(spt->shaकरोw_page.page);
	kमुक्त(spt);
पूर्ण

अटल पूर्णांक detach_oos_page(काष्ठा पूर्णांकel_vgpu *vgpu,
		काष्ठा पूर्णांकel_vgpu_oos_page *oos_page);

अटल व्योम ppgtt_मुक्त_spt(काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt)
अणु
	काष्ठा device *kdev = spt->vgpu->gvt->gt->i915->drm.dev;

	trace_spt_मुक्त(spt->vgpu->id, spt, spt->guest_page.type);

	dma_unmap_page(kdev, spt->shaकरोw_page.mfn << I915_GTT_PAGE_SHIFT, 4096,
		       PCI_DMA_BIसूचीECTIONAL);

	radix_tree_delete(&spt->vgpu->gtt.spt_tree, spt->shaकरोw_page.mfn);

	अगर (spt->guest_page.gfn) अणु
		अगर (spt->guest_page.oos_page)
			detach_oos_page(spt->vgpu, spt->guest_page.oos_page);

		पूर्णांकel_vgpu_unरेजिस्टर_page_track(spt->vgpu, spt->guest_page.gfn);
	पूर्ण

	list_del_init(&spt->post_shaकरोw_list);
	मुक्त_spt(spt);
पूर्ण

अटल व्योम ppgtt_मुक्त_all_spt(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt, *spn;
	काष्ठा radix_tree_iter iter;
	LIST_HEAD(all_spt);
	व्योम __rcu **slot;

	rcu_पढ़ो_lock();
	radix_tree_क्रम_each_slot(slot, &vgpu->gtt.spt_tree, &iter, 0) अणु
		spt = radix_tree_deref_slot(slot);
		list_move(&spt->post_shaकरोw_list, &all_spt);
	पूर्ण
	rcu_पढ़ो_unlock();

	list_क्रम_each_entry_safe(spt, spn, &all_spt, post_shaकरोw_list)
		ppgtt_मुक्त_spt(spt);
पूर्ण

अटल पूर्णांक ppgtt_handle_guest_ग_लिखो_page_table_bytes(
		काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt,
		u64 pa, व्योम *p_data, पूर्णांक bytes);

अटल पूर्णांक ppgtt_ग_लिखो_protection_handler(
		काष्ठा पूर्णांकel_vgpu_page_track *page_track,
		u64 gpa, व्योम *data, पूर्णांक bytes)
अणु
	काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt = page_track->priv_data;

	पूर्णांक ret;

	अगर (bytes != 4 && bytes != 8)
		वापस -EINVAL;

	ret = ppgtt_handle_guest_ग_लिखो_page_table_bytes(spt, gpa, data, bytes);
	अगर (ret)
		वापस ret;
	वापस ret;
पूर्ण

/* Find a spt by guest gfn. */
अटल काष्ठा पूर्णांकel_vgpu_ppgtt_spt *पूर्णांकel_vgpu_find_spt_by_gfn(
		काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ gfn)
अणु
	काष्ठा पूर्णांकel_vgpu_page_track *track;

	track = पूर्णांकel_vgpu_find_page_track(vgpu, gfn);
	अगर (track && track->handler == ppgtt_ग_लिखो_protection_handler)
		वापस track->priv_data;

	वापस शून्य;
पूर्ण

/* Find the spt by shaकरोw page mfn. */
अटल अंतरभूत काष्ठा पूर्णांकel_vgpu_ppgtt_spt *पूर्णांकel_vgpu_find_spt_by_mfn(
		काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ mfn)
अणु
	वापस radix_tree_lookup(&vgpu->gtt.spt_tree, mfn);
पूर्ण

अटल पूर्णांक reclaim_one_ppgtt_mm(काष्ठा पूर्णांकel_gvt *gvt);

/* Allocate shaकरोw page table without guest page. */
अटल काष्ठा पूर्णांकel_vgpu_ppgtt_spt *ppgtt_alloc_spt(
		काष्ठा पूर्णांकel_vgpu *vgpu, क्रमागत पूर्णांकel_gvt_gtt_type type)
अणु
	काष्ठा device *kdev = vgpu->gvt->gt->i915->drm.dev;
	काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt = शून्य;
	dma_addr_t daddr;
	पूर्णांक ret;

retry:
	spt = alloc_spt(GFP_KERNEL | __GFP_ZERO);
	अगर (!spt) अणु
		अगर (reclaim_one_ppgtt_mm(vgpu->gvt))
			जाओ retry;

		gvt_vgpu_err("fail to allocate ppgtt shadow page\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	spt->vgpu = vgpu;
	atomic_set(&spt->refcount, 1);
	INIT_LIST_HEAD(&spt->post_shaकरोw_list);

	/*
	 * Init shaकरोw_page.
	 */
	spt->shaकरोw_page.type = type;
	daddr = dma_map_page(kdev, spt->shaकरोw_page.page,
			     0, 4096, PCI_DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(kdev, daddr)) अणु
		gvt_vgpu_err("fail to map dma addr\n");
		ret = -EINVAL;
		जाओ err_मुक्त_spt;
	पूर्ण
	spt->shaकरोw_page.vaddr = page_address(spt->shaकरोw_page.page);
	spt->shaकरोw_page.mfn = daddr >> I915_GTT_PAGE_SHIFT;

	ret = radix_tree_insert(&vgpu->gtt.spt_tree, spt->shaकरोw_page.mfn, spt);
	अगर (ret)
		जाओ err_unmap_dma;

	वापस spt;

err_unmap_dma:
	dma_unmap_page(kdev, daddr, PAGE_SIZE, PCI_DMA_BIसूचीECTIONAL);
err_मुक्त_spt:
	मुक्त_spt(spt);
	वापस ERR_PTR(ret);
पूर्ण

/* Allocate shaकरोw page table associated with specअगरic gfn. */
अटल काष्ठा पूर्णांकel_vgpu_ppgtt_spt *ppgtt_alloc_spt_gfn(
		काष्ठा पूर्णांकel_vgpu *vgpu, क्रमागत पूर्णांकel_gvt_gtt_type type,
		अचिन्हित दीर्घ gfn, bool guest_pde_ips)
अणु
	काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt;
	पूर्णांक ret;

	spt = ppgtt_alloc_spt(vgpu, type);
	अगर (IS_ERR(spt))
		वापस spt;

	/*
	 * Init guest_page.
	 */
	ret = पूर्णांकel_vgpu_रेजिस्टर_page_track(vgpu, gfn,
			ppgtt_ग_लिखो_protection_handler, spt);
	अगर (ret) अणु
		ppgtt_मुक्त_spt(spt);
		वापस ERR_PTR(ret);
	पूर्ण

	spt->guest_page.type = type;
	spt->guest_page.gfn = gfn;
	spt->guest_page.pde_ips = guest_pde_ips;

	trace_spt_alloc(vgpu->id, spt, type, spt->shaकरोw_page.mfn, gfn);

	वापस spt;
पूर्ण

#घोषणा pt_entry_size_shअगरt(spt) \
	((spt)->vgpu->gvt->device_info.gtt_entry_size_shअगरt)

#घोषणा pt_entries(spt) \
	(I915_GTT_PAGE_SIZE >> pt_entry_size_shअगरt(spt))

#घोषणा क्रम_each_present_guest_entry(spt, e, i) \
	क्रम (i = 0; i < pt_entries(spt); \
	     i += spt->guest_page.pde_ips ? GTT_64K_PTE_STRIDE : 1) \
		अगर (!ppgtt_get_guest_entry(spt, e, i) && \
		    spt->vgpu->gvt->gtt.pte_ops->test_present(e))

#घोषणा क्रम_each_present_shaकरोw_entry(spt, e, i) \
	क्रम (i = 0; i < pt_entries(spt); \
	     i += spt->shaकरोw_page.pde_ips ? GTT_64K_PTE_STRIDE : 1) \
		अगर (!ppgtt_get_shaकरोw_entry(spt, e, i) && \
		    spt->vgpu->gvt->gtt.pte_ops->test_present(e))

#घोषणा क्रम_each_shaकरोw_entry(spt, e, i) \
	क्रम (i = 0; i < pt_entries(spt); \
	     i += (spt->shaकरोw_page.pde_ips ? GTT_64K_PTE_STRIDE : 1)) \
		अगर (!ppgtt_get_shaकरोw_entry(spt, e, i))

अटल अंतरभूत व्योम ppgtt_get_spt(काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt)
अणु
	पूर्णांक v = atomic_पढ़ो(&spt->refcount);

	trace_spt_refcount(spt->vgpu->id, "inc", spt, v, (v + 1));
	atomic_inc(&spt->refcount);
पूर्ण

अटल अंतरभूत पूर्णांक ppgtt_put_spt(काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt)
अणु
	पूर्णांक v = atomic_पढ़ो(&spt->refcount);

	trace_spt_refcount(spt->vgpu->id, "dec", spt, v, (v - 1));
	वापस atomic_dec_वापस(&spt->refcount);
पूर्ण

अटल पूर्णांक ppgtt_invalidate_spt(काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt);

अटल पूर्णांक ppgtt_invalidate_spt_by_shaकरोw_entry(काष्ठा पूर्णांकel_vgpu *vgpu,
		काष्ठा पूर्णांकel_gvt_gtt_entry *e)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	काष्ठा पूर्णांकel_vgpu_ppgtt_spt *s;
	क्रमागत पूर्णांकel_gvt_gtt_type cur_pt_type;

	GEM_BUG_ON(!gtt_type_is_pt(get_next_pt_type(e->type)));

	अगर (e->type != GTT_TYPE_PPGTT_ROOT_L3_ENTRY
		&& e->type != GTT_TYPE_PPGTT_ROOT_L4_ENTRY) अणु
		cur_pt_type = get_next_pt_type(e->type);

		अगर (!gtt_type_is_pt(cur_pt_type) ||
				!gtt_type_is_pt(cur_pt_type + 1)) अणु
			drm_WARN(&i915->drm, 1,
				 "Invalid page table type, cur_pt_type is: %d\n",
				 cur_pt_type);
			वापस -EINVAL;
		पूर्ण

		cur_pt_type += 1;

		अगर (ops->get_pfn(e) ==
			vgpu->gtt.scratch_pt[cur_pt_type].page_mfn)
			वापस 0;
	पूर्ण
	s = पूर्णांकel_vgpu_find_spt_by_mfn(vgpu, ops->get_pfn(e));
	अगर (!s) अणु
		gvt_vgpu_err("fail to find shadow page: mfn: 0x%lx\n",
				ops->get_pfn(e));
		वापस -ENXIO;
	पूर्ण
	वापस ppgtt_invalidate_spt(s);
पूर्ण

अटल अंतरभूत व्योम ppgtt_invalidate_pte(काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt,
		काष्ठा पूर्णांकel_gvt_gtt_entry *entry)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = spt->vgpu;
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	अचिन्हित दीर्घ pfn;
	पूर्णांक type;

	pfn = ops->get_pfn(entry);
	type = spt->shaकरोw_page.type;

	/* Uninitialized spte or unshaकरोwed spte. */
	अगर (!pfn || pfn == vgpu->gtt.scratch_pt[type].page_mfn)
		वापस;

	पूर्णांकel_gvt_hypervisor_dma_unmap_guest_page(vgpu, pfn << PAGE_SHIFT);
पूर्ण

अटल पूर्णांक ppgtt_invalidate_spt(काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = spt->vgpu;
	काष्ठा पूर्णांकel_gvt_gtt_entry e;
	अचिन्हित दीर्घ index;
	पूर्णांक ret;

	trace_spt_change(spt->vgpu->id, "die", spt,
			spt->guest_page.gfn, spt->shaकरोw_page.type);

	अगर (ppgtt_put_spt(spt) > 0)
		वापस 0;

	क्रम_each_present_shaकरोw_entry(spt, &e, index) अणु
		चयन (e.type) अणु
		हाल GTT_TYPE_PPGTT_PTE_4K_ENTRY:
			gvt_vdbg_mm("invalidate 4K entry\n");
			ppgtt_invalidate_pte(spt, &e);
			अवरोध;
		हाल GTT_TYPE_PPGTT_PTE_64K_ENTRY:
			/* We करोn't setup 64K shaकरोw entry so far. */
			WARN(1, "suspicious 64K gtt entry\n");
			जारी;
		हाल GTT_TYPE_PPGTT_PTE_2M_ENTRY:
			gvt_vdbg_mm("invalidate 2M entry\n");
			जारी;
		हाल GTT_TYPE_PPGTT_PTE_1G_ENTRY:
			WARN(1, "GVT doesn't support 1GB page\n");
			जारी;
		हाल GTT_TYPE_PPGTT_PML4_ENTRY:
		हाल GTT_TYPE_PPGTT_PDP_ENTRY:
		हाल GTT_TYPE_PPGTT_PDE_ENTRY:
			gvt_vdbg_mm("invalidate PMUL4/PDP/PDE entry\n");
			ret = ppgtt_invalidate_spt_by_shaकरोw_entry(
					spt->vgpu, &e);
			अगर (ret)
				जाओ fail;
			अवरोध;
		शेष:
			GEM_BUG_ON(1);
		पूर्ण
	पूर्ण

	trace_spt_change(spt->vgpu->id, "release", spt,
			 spt->guest_page.gfn, spt->shaकरोw_page.type);
	ppgtt_मुक्त_spt(spt);
	वापस 0;
fail:
	gvt_vgpu_err("fail: shadow page %p shadow entry 0x%llx type %d\n",
			spt, e.val64, e.type);
	वापस ret;
पूर्ण

अटल bool vgpu_ips_enabled(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा drm_i915_निजी *dev_priv = vgpu->gvt->gt->i915;

	अगर (INTEL_GEN(dev_priv) == 9 || INTEL_GEN(dev_priv) == 10) अणु
		u32 ips = vgpu_vreg_t(vgpu, GEN8_GAMW_ECO_DEV_RW_IA) &
			GAMW_ECO_ENABLE_64K_IPS_FIELD;

		वापस ips == GAMW_ECO_ENABLE_64K_IPS_FIELD;
	पूर्ण अन्यथा अगर (INTEL_GEN(dev_priv) >= 11) अणु
		/* 64K paging only controlled by IPS bit in PTE now. */
		वापस true;
	पूर्ण अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक ppgtt_populate_spt(काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt);

अटल काष्ठा पूर्णांकel_vgpu_ppgtt_spt *ppgtt_populate_spt_by_guest_entry(
		काष्ठा पूर्णांकel_vgpu *vgpu, काष्ठा पूर्णांकel_gvt_gtt_entry *we)
अणु
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt = शून्य;
	bool ips = false;
	पूर्णांक ret;

	GEM_BUG_ON(!gtt_type_is_pt(get_next_pt_type(we->type)));

	अगर (we->type == GTT_TYPE_PPGTT_PDE_ENTRY)
		ips = vgpu_ips_enabled(vgpu) && ops->test_ips(we);

	spt = पूर्णांकel_vgpu_find_spt_by_gfn(vgpu, ops->get_pfn(we));
	अगर (spt) अणु
		ppgtt_get_spt(spt);

		अगर (ips != spt->guest_page.pde_ips) अणु
			spt->guest_page.pde_ips = ips;

			gvt_dbg_mm("reshadow PDE since ips changed\n");
			clear_page(spt->shaकरोw_page.vaddr);
			ret = ppgtt_populate_spt(spt);
			अगर (ret) अणु
				ppgtt_put_spt(spt);
				जाओ err;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक type = get_next_pt_type(we->type);

		अगर (!gtt_type_is_pt(type)) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		spt = ppgtt_alloc_spt_gfn(vgpu, type, ops->get_pfn(we), ips);
		अगर (IS_ERR(spt)) अणु
			ret = PTR_ERR(spt);
			जाओ err;
		पूर्ण

		ret = पूर्णांकel_vgpu_enable_page_track(vgpu, spt->guest_page.gfn);
		अगर (ret)
			जाओ err_मुक्त_spt;

		ret = ppgtt_populate_spt(spt);
		अगर (ret)
			जाओ err_मुक्त_spt;

		trace_spt_change(vgpu->id, "new", spt, spt->guest_page.gfn,
				 spt->shaकरोw_page.type);
	पूर्ण
	वापस spt;

err_मुक्त_spt:
	ppgtt_मुक्त_spt(spt);
	spt = शून्य;
err:
	gvt_vgpu_err("fail: shadow page %p guest entry 0x%llx type %d\n",
		     spt, we->val64, we->type);
	वापस ERR_PTR(ret);
पूर्ण

अटल अंतरभूत व्योम ppgtt_generate_shaकरोw_entry(काष्ठा पूर्णांकel_gvt_gtt_entry *se,
		काष्ठा पूर्णांकel_vgpu_ppgtt_spt *s, काष्ठा पूर्णांकel_gvt_gtt_entry *ge)
अणु
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *ops = s->vgpu->gvt->gtt.pte_ops;

	se->type = ge->type;
	se->val64 = ge->val64;

	/* Because we always split 64KB pages, so clear IPS in shaकरोw PDE. */
	अगर (se->type == GTT_TYPE_PPGTT_PDE_ENTRY)
		ops->clear_ips(se);

	ops->set_pfn(se, s->shaकरोw_page.mfn);
पूर्ण

/**
 * Check अगर can करो 2M page
 * @vgpu: target vgpu
 * @entry: target pfn's gtt entry
 *
 * Return 1 अगर 2MB huge gtt shaकरोwing is possible, 0 अगर miscondition,
 * negative अगर found err.
 */
अटल पूर्णांक is_2MB_gtt_possible(काष्ठा पूर्णांकel_vgpu *vgpu,
	काष्ठा पूर्णांकel_gvt_gtt_entry *entry)
अणु
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	अचिन्हित दीर्घ pfn;

	अगर (!HAS_PAGE_SIZES(vgpu->gvt->gt->i915, I915_GTT_PAGE_SIZE_2M))
		वापस 0;

	pfn = पूर्णांकel_gvt_hypervisor_gfn_to_mfn(vgpu, ops->get_pfn(entry));
	अगर (pfn == INTEL_GVT_INVALID_ADDR)
		वापस -EINVAL;

	वापस PageTransHuge(pfn_to_page(pfn));
पूर्ण

अटल पूर्णांक split_2MB_gtt_entry(काष्ठा पूर्णांकel_vgpu *vgpu,
	काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt, अचिन्हित दीर्घ index,
	काष्ठा पूर्णांकel_gvt_gtt_entry *se)
अणु
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	काष्ठा पूर्णांकel_vgpu_ppgtt_spt *sub_spt;
	काष्ठा पूर्णांकel_gvt_gtt_entry sub_se;
	अचिन्हित दीर्घ start_gfn;
	dma_addr_t dma_addr;
	अचिन्हित दीर्घ sub_index;
	पूर्णांक ret;

	gvt_dbg_mm("Split 2M gtt entry, index %lu\n", index);

	start_gfn = ops->get_pfn(se);

	sub_spt = ppgtt_alloc_spt(vgpu, GTT_TYPE_PPGTT_PTE_PT);
	अगर (IS_ERR(sub_spt))
		वापस PTR_ERR(sub_spt);

	क्रम_each_shaकरोw_entry(sub_spt, &sub_se, sub_index) अणु
		ret = पूर्णांकel_gvt_hypervisor_dma_map_guest_page(vgpu,
				start_gfn + sub_index, PAGE_SIZE, &dma_addr);
		अगर (ret) अणु
			ppgtt_invalidate_spt(spt);
			वापस ret;
		पूर्ण
		sub_se.val64 = se->val64;

		/* Copy the PAT field from PDE. */
		sub_se.val64 &= ~_PAGE_PAT;
		sub_se.val64 |= (se->val64 & _PAGE_PAT_LARGE) >> 5;

		ops->set_pfn(&sub_se, dma_addr >> PAGE_SHIFT);
		ppgtt_set_shaकरोw_entry(sub_spt, &sub_se, sub_index);
	पूर्ण

	/* Clear dirty field. */
	se->val64 &= ~_PAGE_सूचीTY;

	ops->clear_pse(se);
	ops->clear_ips(se);
	ops->set_pfn(se, sub_spt->shaकरोw_page.mfn);
	ppgtt_set_shaकरोw_entry(spt, se, index);
	वापस 0;
पूर्ण

अटल पूर्णांक split_64KB_gtt_entry(काष्ठा पूर्णांकel_vgpu *vgpu,
	काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt, अचिन्हित दीर्घ index,
	काष्ठा पूर्णांकel_gvt_gtt_entry *se)
अणु
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	काष्ठा पूर्णांकel_gvt_gtt_entry entry = *se;
	अचिन्हित दीर्घ start_gfn;
	dma_addr_t dma_addr;
	पूर्णांक i, ret;

	gvt_vdbg_mm("Split 64K gtt entry, index %lu\n", index);

	GEM_BUG_ON(index % GTT_64K_PTE_STRIDE);

	start_gfn = ops->get_pfn(se);

	entry.type = GTT_TYPE_PPGTT_PTE_4K_ENTRY;
	ops->set_64k_splited(&entry);

	क्रम (i = 0; i < GTT_64K_PTE_STRIDE; i++) अणु
		ret = पूर्णांकel_gvt_hypervisor_dma_map_guest_page(vgpu,
					start_gfn + i, PAGE_SIZE, &dma_addr);
		अगर (ret)
			वापस ret;

		ops->set_pfn(&entry, dma_addr >> PAGE_SHIFT);
		ppgtt_set_shaकरोw_entry(spt, &entry, index + i);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ppgtt_populate_shaकरोw_entry(काष्ठा पूर्णांकel_vgpu *vgpu,
	काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt, अचिन्हित दीर्घ index,
	काष्ठा पूर्णांकel_gvt_gtt_entry *ge)
अणु
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *pte_ops = vgpu->gvt->gtt.pte_ops;
	काष्ठा पूर्णांकel_gvt_gtt_entry se = *ge;
	अचिन्हित दीर्घ gfn, page_size = PAGE_SIZE;
	dma_addr_t dma_addr;
	पूर्णांक ret;

	अगर (!pte_ops->test_present(ge))
		वापस 0;

	gfn = pte_ops->get_pfn(ge);

	चयन (ge->type) अणु
	हाल GTT_TYPE_PPGTT_PTE_4K_ENTRY:
		gvt_vdbg_mm("shadow 4K gtt entry\n");
		अवरोध;
	हाल GTT_TYPE_PPGTT_PTE_64K_ENTRY:
		gvt_vdbg_mm("shadow 64K gtt entry\n");
		/*
		 * The layout of 64K page is special, the page size is
		 * controlled by uper PDE. To be simple, we always split
		 * 64K page to smaller 4K pages in shaकरोw PT.
		 */
		वापस split_64KB_gtt_entry(vgpu, spt, index, &se);
	हाल GTT_TYPE_PPGTT_PTE_2M_ENTRY:
		gvt_vdbg_mm("shadow 2M gtt entry\n");
		ret = is_2MB_gtt_possible(vgpu, ge);
		अगर (ret == 0)
			वापस split_2MB_gtt_entry(vgpu, spt, index, &se);
		अन्यथा अगर (ret < 0)
			वापस ret;
		page_size = I915_GTT_PAGE_SIZE_2M;
		अवरोध;
	हाल GTT_TYPE_PPGTT_PTE_1G_ENTRY:
		gvt_vgpu_err("GVT doesn't support 1GB entry\n");
		वापस -EINVAL;
	शेष:
		GEM_BUG_ON(1);
	पूर्ण

	/* direct shaकरोw */
	ret = पूर्णांकel_gvt_hypervisor_dma_map_guest_page(vgpu, gfn, page_size,
						      &dma_addr);
	अगर (ret)
		वापस -ENXIO;

	pte_ops->set_pfn(&se, dma_addr >> PAGE_SHIFT);
	ppgtt_set_shaकरोw_entry(spt, &se, index);
	वापस 0;
पूर्ण

अटल पूर्णांक ppgtt_populate_spt(काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = spt->vgpu;
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *ops = gvt->gtt.pte_ops;
	काष्ठा पूर्णांकel_vgpu_ppgtt_spt *s;
	काष्ठा पूर्णांकel_gvt_gtt_entry se, ge;
	अचिन्हित दीर्घ gfn, i;
	पूर्णांक ret;

	trace_spt_change(spt->vgpu->id, "born", spt,
			 spt->guest_page.gfn, spt->shaकरोw_page.type);

	क्रम_each_present_guest_entry(spt, &ge, i) अणु
		अगर (gtt_type_is_pt(get_next_pt_type(ge.type))) अणु
			s = ppgtt_populate_spt_by_guest_entry(vgpu, &ge);
			अगर (IS_ERR(s)) अणु
				ret = PTR_ERR(s);
				जाओ fail;
			पूर्ण
			ppgtt_get_shaकरोw_entry(spt, &se, i);
			ppgtt_generate_shaकरोw_entry(&se, s, &ge);
			ppgtt_set_shaकरोw_entry(spt, &se, i);
		पूर्ण अन्यथा अणु
			gfn = ops->get_pfn(&ge);
			अगर (!पूर्णांकel_gvt_hypervisor_is_valid_gfn(vgpu, gfn)) अणु
				ops->set_pfn(&se, gvt->gtt.scratch_mfn);
				ppgtt_set_shaकरोw_entry(spt, &se, i);
				जारी;
			पूर्ण

			ret = ppgtt_populate_shaकरोw_entry(vgpu, spt, i, &ge);
			अगर (ret)
				जाओ fail;
		पूर्ण
	पूर्ण
	वापस 0;
fail:
	gvt_vgpu_err("fail: shadow page %p guest entry 0x%llx type %d\n",
			spt, ge.val64, ge.type);
	वापस ret;
पूर्ण

अटल पूर्णांक ppgtt_handle_guest_entry_removal(काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt,
		काष्ठा पूर्णांकel_gvt_gtt_entry *se, अचिन्हित दीर्घ index)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = spt->vgpu;
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	पूर्णांक ret;

	trace_spt_guest_change(spt->vgpu->id, "remove", spt,
			       spt->shaकरोw_page.type, se->val64, index);

	gvt_vdbg_mm("destroy old shadow entry, type %d, index %lu, value %llx\n",
		    se->type, index, se->val64);

	अगर (!ops->test_present(se))
		वापस 0;

	अगर (ops->get_pfn(se) ==
	    vgpu->gtt.scratch_pt[spt->shaकरोw_page.type].page_mfn)
		वापस 0;

	अगर (gtt_type_is_pt(get_next_pt_type(se->type))) अणु
		काष्ठा पूर्णांकel_vgpu_ppgtt_spt *s =
			पूर्णांकel_vgpu_find_spt_by_mfn(vgpu, ops->get_pfn(se));
		अगर (!s) अणु
			gvt_vgpu_err("fail to find guest page\n");
			ret = -ENXIO;
			जाओ fail;
		पूर्ण
		ret = ppgtt_invalidate_spt(s);
		अगर (ret)
			जाओ fail;
	पूर्ण अन्यथा अणु
		/* We करोn't setup 64K shaकरोw entry so far. */
		WARN(se->type == GTT_TYPE_PPGTT_PTE_64K_ENTRY,
		     "suspicious 64K entry\n");
		ppgtt_invalidate_pte(spt, se);
	पूर्ण

	वापस 0;
fail:
	gvt_vgpu_err("fail: shadow page %p guest entry 0x%llx type %d\n",
			spt, se->val64, se->type);
	वापस ret;
पूर्ण

अटल पूर्णांक ppgtt_handle_guest_entry_add(काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt,
		काष्ठा पूर्णांकel_gvt_gtt_entry *we, अचिन्हित दीर्घ index)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = spt->vgpu;
	काष्ठा पूर्णांकel_gvt_gtt_entry m;
	काष्ठा पूर्णांकel_vgpu_ppgtt_spt *s;
	पूर्णांक ret;

	trace_spt_guest_change(spt->vgpu->id, "add", spt, spt->shaकरोw_page.type,
			       we->val64, index);

	gvt_vdbg_mm("add shadow entry: type %d, index %lu, value %llx\n",
		    we->type, index, we->val64);

	अगर (gtt_type_is_pt(get_next_pt_type(we->type))) अणु
		s = ppgtt_populate_spt_by_guest_entry(vgpu, we);
		अगर (IS_ERR(s)) अणु
			ret = PTR_ERR(s);
			जाओ fail;
		पूर्ण
		ppgtt_get_shaकरोw_entry(spt, &m, index);
		ppgtt_generate_shaकरोw_entry(&m, s, we);
		ppgtt_set_shaकरोw_entry(spt, &m, index);
	पूर्ण अन्यथा अणु
		ret = ppgtt_populate_shaकरोw_entry(vgpu, spt, index, we);
		अगर (ret)
			जाओ fail;
	पूर्ण
	वापस 0;
fail:
	gvt_vgpu_err("fail: spt %p guest entry 0x%llx type %d\n",
		spt, we->val64, we->type);
	वापस ret;
पूर्ण

अटल पूर्णांक sync_oos_page(काष्ठा पूर्णांकel_vgpu *vgpu,
		काष्ठा पूर्णांकel_vgpu_oos_page *oos_page)
अणु
	स्थिर काष्ठा पूर्णांकel_gvt_device_info *info = &vgpu->gvt->device_info;
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *ops = gvt->gtt.pte_ops;
	काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt = oos_page->spt;
	काष्ठा पूर्णांकel_gvt_gtt_entry old, new;
	पूर्णांक index;
	पूर्णांक ret;

	trace_oos_change(vgpu->id, "sync", oos_page->id,
			 spt, spt->guest_page.type);

	old.type = new.type = get_entry_type(spt->guest_page.type);
	old.val64 = new.val64 = 0;

	क्रम (index = 0; index < (I915_GTT_PAGE_SIZE >>
				info->gtt_entry_size_shअगरt); index++) अणु
		ops->get_entry(oos_page->mem, &old, index, false, 0, vgpu);
		ops->get_entry(शून्य, &new, index, true,
			       spt->guest_page.gfn << PAGE_SHIFT, vgpu);

		अगर (old.val64 == new.val64
			&& !test_and_clear_bit(index, spt->post_shaकरोw_biपंचांगap))
			जारी;

		trace_oos_sync(vgpu->id, oos_page->id,
				spt, spt->guest_page.type,
				new.val64, index);

		ret = ppgtt_populate_shaकरोw_entry(vgpu, spt, index, &new);
		अगर (ret)
			वापस ret;

		ops->set_entry(oos_page->mem, &new, index, false, 0, vgpu);
	पूर्ण

	spt->guest_page.ग_लिखो_cnt = 0;
	list_del_init(&spt->post_shaकरोw_list);
	वापस 0;
पूर्ण

अटल पूर्णांक detach_oos_page(काष्ठा पूर्णांकel_vgpu *vgpu,
		काष्ठा पूर्णांकel_vgpu_oos_page *oos_page)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt = oos_page->spt;

	trace_oos_change(vgpu->id, "detach", oos_page->id,
			 spt, spt->guest_page.type);

	spt->guest_page.ग_लिखो_cnt = 0;
	spt->guest_page.oos_page = शून्य;
	oos_page->spt = शून्य;

	list_del_init(&oos_page->vm_list);
	list_move_tail(&oos_page->list, &gvt->gtt.oos_page_मुक्त_list_head);

	वापस 0;
पूर्ण

अटल पूर्णांक attach_oos_page(काष्ठा पूर्णांकel_vgpu_oos_page *oos_page,
		काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = spt->vgpu->gvt;
	पूर्णांक ret;

	ret = पूर्णांकel_gvt_hypervisor_पढ़ो_gpa(spt->vgpu,
			spt->guest_page.gfn << I915_GTT_PAGE_SHIFT,
			oos_page->mem, I915_GTT_PAGE_SIZE);
	अगर (ret)
		वापस ret;

	oos_page->spt = spt;
	spt->guest_page.oos_page = oos_page;

	list_move_tail(&oos_page->list, &gvt->gtt.oos_page_use_list_head);

	trace_oos_change(spt->vgpu->id, "attach", oos_page->id,
			 spt, spt->guest_page.type);
	वापस 0;
पूर्ण

अटल पूर्णांक ppgtt_set_guest_page_sync(काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt)
अणु
	काष्ठा पूर्णांकel_vgpu_oos_page *oos_page = spt->guest_page.oos_page;
	पूर्णांक ret;

	ret = पूर्णांकel_vgpu_enable_page_track(spt->vgpu, spt->guest_page.gfn);
	अगर (ret)
		वापस ret;

	trace_oos_change(spt->vgpu->id, "set page sync", oos_page->id,
			 spt, spt->guest_page.type);

	list_del_init(&oos_page->vm_list);
	वापस sync_oos_page(spt->vgpu, oos_page);
पूर्ण

अटल पूर्णांक ppgtt_allocate_oos_page(काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = spt->vgpu->gvt;
	काष्ठा पूर्णांकel_gvt_gtt *gtt = &gvt->gtt;
	काष्ठा पूर्णांकel_vgpu_oos_page *oos_page = spt->guest_page.oos_page;
	पूर्णांक ret;

	WARN(oos_page, "shadow PPGTT page has already has a oos page\n");

	अगर (list_empty(&gtt->oos_page_मुक्त_list_head)) अणु
		oos_page = container_of(gtt->oos_page_use_list_head.next,
			काष्ठा पूर्णांकel_vgpu_oos_page, list);
		ret = ppgtt_set_guest_page_sync(oos_page->spt);
		अगर (ret)
			वापस ret;
		ret = detach_oos_page(spt->vgpu, oos_page);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा
		oos_page = container_of(gtt->oos_page_मुक्त_list_head.next,
			काष्ठा पूर्णांकel_vgpu_oos_page, list);
	वापस attach_oos_page(oos_page, spt);
पूर्ण

अटल पूर्णांक ppgtt_set_guest_page_oos(काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt)
अणु
	काष्ठा पूर्णांकel_vgpu_oos_page *oos_page = spt->guest_page.oos_page;

	अगर (WARN(!oos_page, "shadow PPGTT page should have a oos page\n"))
		वापस -EINVAL;

	trace_oos_change(spt->vgpu->id, "set page out of sync", oos_page->id,
			 spt, spt->guest_page.type);

	list_add_tail(&oos_page->vm_list, &spt->vgpu->gtt.oos_page_list_head);
	वापस पूर्णांकel_vgpu_disable_page_track(spt->vgpu, spt->guest_page.gfn);
पूर्ण

/**
 * पूर्णांकel_vgpu_sync_oos_pages - sync all the out-of-synced shaकरोw क्रम vGPU
 * @vgpu: a vGPU
 *
 * This function is called beक्रमe submitting a guest workload to host,
 * to sync all the out-of-synced shaकरोw क्रम vGPU
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_sync_oos_pages(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा list_head *pos, *n;
	काष्ठा पूर्णांकel_vgpu_oos_page *oos_page;
	पूर्णांक ret;

	अगर (!enable_out_of_sync)
		वापस 0;

	list_क्रम_each_safe(pos, n, &vgpu->gtt.oos_page_list_head) अणु
		oos_page = container_of(pos,
				काष्ठा पूर्णांकel_vgpu_oos_page, vm_list);
		ret = ppgtt_set_guest_page_sync(oos_page->spt);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * The heart of PPGTT shaकरोw page table.
 */
अटल पूर्णांक ppgtt_handle_guest_ग_लिखो_page_table(
		काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt,
		काष्ठा पूर्णांकel_gvt_gtt_entry *we, अचिन्हित दीर्घ index)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = spt->vgpu;
	पूर्णांक type = spt->shaकरोw_page.type;
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	काष्ठा पूर्णांकel_gvt_gtt_entry old_se;
	पूर्णांक new_present;
	पूर्णांक i, ret;

	new_present = ops->test_present(we);

	/*
	 * Adding the new entry first and then removing the old one, that can
	 * guarantee the ppgtt table is validated during the winकरोw between
	 * adding and removal.
	 */
	ppgtt_get_shaकरोw_entry(spt, &old_se, index);

	अगर (new_present) अणु
		ret = ppgtt_handle_guest_entry_add(spt, we, index);
		अगर (ret)
			जाओ fail;
	पूर्ण

	ret = ppgtt_handle_guest_entry_removal(spt, &old_se, index);
	अगर (ret)
		जाओ fail;

	अगर (!new_present) अणु
		/* For 64KB splited entries, we need clear them all. */
		अगर (ops->test_64k_splited(&old_se) &&
		    !(index % GTT_64K_PTE_STRIDE)) अणु
			gvt_vdbg_mm("remove splited 64K shadow entries\n");
			क्रम (i = 0; i < GTT_64K_PTE_STRIDE; i++) अणु
				ops->clear_64k_splited(&old_se);
				ops->set_pfn(&old_se,
					vgpu->gtt.scratch_pt[type].page_mfn);
				ppgtt_set_shaकरोw_entry(spt, &old_se, index + i);
			पूर्ण
		पूर्ण अन्यथा अगर (old_se.type == GTT_TYPE_PPGTT_PTE_2M_ENTRY ||
			   old_se.type == GTT_TYPE_PPGTT_PTE_1G_ENTRY) अणु
			ops->clear_pse(&old_se);
			ops->set_pfn(&old_se,
				     vgpu->gtt.scratch_pt[type].page_mfn);
			ppgtt_set_shaकरोw_entry(spt, &old_se, index);
		पूर्ण अन्यथा अणु
			ops->set_pfn(&old_se,
				     vgpu->gtt.scratch_pt[type].page_mfn);
			ppgtt_set_shaकरोw_entry(spt, &old_se, index);
		पूर्ण
	पूर्ण

	वापस 0;
fail:
	gvt_vgpu_err("fail: shadow page %p guest entry 0x%llx type %d.\n",
			spt, we->val64, we->type);
	वापस ret;
पूर्ण



अटल अंतरभूत bool can_करो_out_of_sync(काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt)
अणु
	वापस enable_out_of_sync
		&& gtt_type_is_pte_pt(spt->guest_page.type)
		&& spt->guest_page.ग_लिखो_cnt >= 2;
पूर्ण

अटल व्योम ppgtt_set_post_shaकरोw(काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt,
		अचिन्हित दीर्घ index)
अणु
	set_bit(index, spt->post_shaकरोw_biपंचांगap);
	अगर (!list_empty(&spt->post_shaकरोw_list))
		वापस;

	list_add_tail(&spt->post_shaकरोw_list,
			&spt->vgpu->gtt.post_shaकरोw_list_head);
पूर्ण

/**
 * पूर्णांकel_vgpu_flush_post_shaकरोw - flush the post shaकरोw transactions
 * @vgpu: a vGPU
 *
 * This function is called beक्रमe submitting a guest workload to host,
 * to flush all the post shaकरोws क्रम a vGPU.
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_flush_post_shaकरोw(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा list_head *pos, *n;
	काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt;
	काष्ठा पूर्णांकel_gvt_gtt_entry ge;
	अचिन्हित दीर्घ index;
	पूर्णांक ret;

	list_क्रम_each_safe(pos, n, &vgpu->gtt.post_shaकरोw_list_head) अणु
		spt = container_of(pos, काष्ठा पूर्णांकel_vgpu_ppgtt_spt,
				post_shaकरोw_list);

		क्रम_each_set_bit(index, spt->post_shaकरोw_biपंचांगap,
				GTT_ENTRY_NUM_IN_ONE_PAGE) अणु
			ppgtt_get_guest_entry(spt, &ge, index);

			ret = ppgtt_handle_guest_ग_लिखो_page_table(spt,
							&ge, index);
			अगर (ret)
				वापस ret;
			clear_bit(index, spt->post_shaकरोw_biपंचांगap);
		पूर्ण
		list_del_init(&spt->post_shaकरोw_list);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ppgtt_handle_guest_ग_लिखो_page_table_bytes(
		काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt,
		u64 pa, व्योम *p_data, पूर्णांक bytes)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = spt->vgpu;
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	स्थिर काष्ठा पूर्णांकel_gvt_device_info *info = &vgpu->gvt->device_info;
	काष्ठा पूर्णांकel_gvt_gtt_entry we, se;
	अचिन्हित दीर्घ index;
	पूर्णांक ret;

	index = (pa & (PAGE_SIZE - 1)) >> info->gtt_entry_size_shअगरt;

	ppgtt_get_guest_entry(spt, &we, index);

	/*
	 * For page table which has 64K gtt entry, only PTE#0, PTE#16,
	 * PTE#32, ... PTE#496 are used. Unused PTEs update should be
	 * ignored.
	 */
	अगर (we.type == GTT_TYPE_PPGTT_PTE_64K_ENTRY &&
	    (index % GTT_64K_PTE_STRIDE)) अणु
		gvt_vdbg_mm("Ignore write to unused PTE entry, index %lu\n",
			    index);
		वापस 0;
	पूर्ण

	अगर (bytes == info->gtt_entry_size) अणु
		ret = ppgtt_handle_guest_ग_लिखो_page_table(spt, &we, index);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		अगर (!test_bit(index, spt->post_shaकरोw_biपंचांगap)) अणु
			पूर्णांक type = spt->shaकरोw_page.type;

			ppgtt_get_shaकरोw_entry(spt, &se, index);
			ret = ppgtt_handle_guest_entry_removal(spt, &se, index);
			अगर (ret)
				वापस ret;
			ops->set_pfn(&se, vgpu->gtt.scratch_pt[type].page_mfn);
			ppgtt_set_shaकरोw_entry(spt, &se, index);
		पूर्ण
		ppgtt_set_post_shaकरोw(spt, index);
	पूर्ण

	अगर (!enable_out_of_sync)
		वापस 0;

	spt->guest_page.ग_लिखो_cnt++;

	अगर (spt->guest_page.oos_page)
		ops->set_entry(spt->guest_page.oos_page->mem, &we, index,
				false, 0, vgpu);

	अगर (can_करो_out_of_sync(spt)) अणु
		अगर (!spt->guest_page.oos_page)
			ppgtt_allocate_oos_page(spt);

		ret = ppgtt_set_guest_page_oos(spt);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम invalidate_ppgtt_mm(काष्ठा पूर्णांकel_vgpu_mm *mm)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = mm->vgpu;
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा पूर्णांकel_gvt_gtt *gtt = &gvt->gtt;
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *ops = gtt->pte_ops;
	काष्ठा पूर्णांकel_gvt_gtt_entry se;
	पूर्णांक index;

	अगर (!mm->ppgtt_mm.shaकरोwed)
		वापस;

	क्रम (index = 0; index < ARRAY_SIZE(mm->ppgtt_mm.shaकरोw_pdps); index++) अणु
		ppgtt_get_shaकरोw_root_entry(mm, &se, index);

		अगर (!ops->test_present(&se))
			जारी;

		ppgtt_invalidate_spt_by_shaकरोw_entry(vgpu, &se);
		se.val64 = 0;
		ppgtt_set_shaकरोw_root_entry(mm, &se, index);

		trace_spt_guest_change(vgpu->id, "destroy root pointer",
				       शून्य, se.type, se.val64, index);
	पूर्ण

	mm->ppgtt_mm.shaकरोwed = false;
पूर्ण


अटल पूर्णांक shaकरोw_ppgtt_mm(काष्ठा पूर्णांकel_vgpu_mm *mm)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = mm->vgpu;
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा पूर्णांकel_gvt_gtt *gtt = &gvt->gtt;
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *ops = gtt->pte_ops;
	काष्ठा पूर्णांकel_vgpu_ppgtt_spt *spt;
	काष्ठा पूर्णांकel_gvt_gtt_entry ge, se;
	पूर्णांक index, ret;

	अगर (mm->ppgtt_mm.shaकरोwed)
		वापस 0;

	mm->ppgtt_mm.shaकरोwed = true;

	क्रम (index = 0; index < ARRAY_SIZE(mm->ppgtt_mm.guest_pdps); index++) अणु
		ppgtt_get_guest_root_entry(mm, &ge, index);

		अगर (!ops->test_present(&ge))
			जारी;

		trace_spt_guest_change(vgpu->id, __func__, शून्य,
				       ge.type, ge.val64, index);

		spt = ppgtt_populate_spt_by_guest_entry(vgpu, &ge);
		अगर (IS_ERR(spt)) अणु
			gvt_vgpu_err("fail to populate guest root pointer\n");
			ret = PTR_ERR(spt);
			जाओ fail;
		पूर्ण
		ppgtt_generate_shaकरोw_entry(&se, spt, &ge);
		ppgtt_set_shaकरोw_root_entry(mm, &se, index);

		trace_spt_guest_change(vgpu->id, "populate root pointer",
				       शून्य, se.type, se.val64, index);
	पूर्ण

	वापस 0;
fail:
	invalidate_ppgtt_mm(mm);
	वापस ret;
पूर्ण

अटल काष्ठा पूर्णांकel_vgpu_mm *vgpu_alloc_mm(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा पूर्णांकel_vgpu_mm *mm;

	mm = kzalloc(माप(*mm), GFP_KERNEL);
	अगर (!mm)
		वापस शून्य;

	mm->vgpu = vgpu;
	kref_init(&mm->ref);
	atomic_set(&mm->pincount, 0);

	वापस mm;
पूर्ण

अटल व्योम vgpu_मुक्त_mm(काष्ठा पूर्णांकel_vgpu_mm *mm)
अणु
	kमुक्त(mm);
पूर्ण

/**
 * पूर्णांकel_vgpu_create_ppgtt_mm - create a ppgtt mm object क्रम a vGPU
 * @vgpu: a vGPU
 * @root_entry_type: ppgtt root entry type
 * @pdps: guest pdps.
 *
 * This function is used to create a ppgtt mm object क्रम a vGPU.
 *
 * Returns:
 * Zero on success, negative error code in poपूर्णांकer अगर failed.
 */
काष्ठा पूर्णांकel_vgpu_mm *पूर्णांकel_vgpu_create_ppgtt_mm(काष्ठा पूर्णांकel_vgpu *vgpu,
		क्रमागत पूर्णांकel_gvt_gtt_type root_entry_type, u64 pdps[])
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा पूर्णांकel_vgpu_mm *mm;
	पूर्णांक ret;

	mm = vgpu_alloc_mm(vgpu);
	अगर (!mm)
		वापस ERR_PTR(-ENOMEM);

	mm->type = INTEL_GVT_MM_PPGTT;

	GEM_BUG_ON(root_entry_type != GTT_TYPE_PPGTT_ROOT_L3_ENTRY &&
		   root_entry_type != GTT_TYPE_PPGTT_ROOT_L4_ENTRY);
	mm->ppgtt_mm.root_entry_type = root_entry_type;

	INIT_LIST_HEAD(&mm->ppgtt_mm.list);
	INIT_LIST_HEAD(&mm->ppgtt_mm.lru_list);
	INIT_LIST_HEAD(&mm->ppgtt_mm.link);

	अगर (root_entry_type == GTT_TYPE_PPGTT_ROOT_L4_ENTRY)
		mm->ppgtt_mm.guest_pdps[0] = pdps[0];
	अन्यथा
		स_नकल(mm->ppgtt_mm.guest_pdps, pdps,
		       माप(mm->ppgtt_mm.guest_pdps));

	ret = shaकरोw_ppgtt_mm(mm);
	अगर (ret) अणु
		gvt_vgpu_err("failed to shadow ppgtt mm\n");
		vgpu_मुक्त_mm(mm);
		वापस ERR_PTR(ret);
	पूर्ण

	list_add_tail(&mm->ppgtt_mm.list, &vgpu->gtt.ppgtt_mm_list_head);

	mutex_lock(&gvt->gtt.ppgtt_mm_lock);
	list_add_tail(&mm->ppgtt_mm.lru_list, &gvt->gtt.ppgtt_mm_lru_list_head);
	mutex_unlock(&gvt->gtt.ppgtt_mm_lock);

	वापस mm;
पूर्ण

अटल काष्ठा पूर्णांकel_vgpu_mm *पूर्णांकel_vgpu_create_ggtt_mm(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा पूर्णांकel_vgpu_mm *mm;
	अचिन्हित दीर्घ nr_entries;

	mm = vgpu_alloc_mm(vgpu);
	अगर (!mm)
		वापस ERR_PTR(-ENOMEM);

	mm->type = INTEL_GVT_MM_GGTT;

	nr_entries = gvt_ggtt_gm_sz(vgpu->gvt) >> I915_GTT_PAGE_SHIFT;
	mm->ggtt_mm.भव_ggtt =
		vzalloc(array_size(nr_entries,
				   vgpu->gvt->device_info.gtt_entry_size));
	अगर (!mm->ggtt_mm.भव_ggtt) अणु
		vgpu_मुक्त_mm(mm);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	mm->ggtt_mm.host_ggtt_aperture = vzalloc((vgpu_aperture_sz(vgpu) >> PAGE_SHIFT) * माप(u64));
	अगर (!mm->ggtt_mm.host_ggtt_aperture) अणु
		vमुक्त(mm->ggtt_mm.भव_ggtt);
		vgpu_मुक्त_mm(mm);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	mm->ggtt_mm.host_ggtt_hidden = vzalloc((vgpu_hidden_sz(vgpu) >> PAGE_SHIFT) * माप(u64));
	अगर (!mm->ggtt_mm.host_ggtt_hidden) अणु
		vमुक्त(mm->ggtt_mm.host_ggtt_aperture);
		vमुक्त(mm->ggtt_mm.भव_ggtt);
		vgpu_मुक्त_mm(mm);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस mm;
पूर्ण

/**
 * _पूर्णांकel_vgpu_mm_release - destroy a mm object
 * @mm_ref: a kref object
 *
 * This function is used to destroy a mm object क्रम vGPU
 *
 */
व्योम _पूर्णांकel_vgpu_mm_release(काष्ठा kref *mm_ref)
अणु
	काष्ठा पूर्णांकel_vgpu_mm *mm = container_of(mm_ref, typeof(*mm), ref);

	अगर (GEM_WARN_ON(atomic_पढ़ो(&mm->pincount)))
		gvt_err("vgpu mm pin count bug detected\n");

	अगर (mm->type == INTEL_GVT_MM_PPGTT) अणु
		list_del(&mm->ppgtt_mm.list);

		mutex_lock(&mm->vgpu->gvt->gtt.ppgtt_mm_lock);
		list_del(&mm->ppgtt_mm.lru_list);
		mutex_unlock(&mm->vgpu->gvt->gtt.ppgtt_mm_lock);

		invalidate_ppgtt_mm(mm);
	पूर्ण अन्यथा अणु
		vमुक्त(mm->ggtt_mm.भव_ggtt);
		vमुक्त(mm->ggtt_mm.host_ggtt_aperture);
		vमुक्त(mm->ggtt_mm.host_ggtt_hidden);
	पूर्ण

	vgpu_मुक्त_mm(mm);
पूर्ण

/**
 * पूर्णांकel_vgpu_unpin_mm - decrease the pin count of a vGPU mm object
 * @mm: a vGPU mm object
 *
 * This function is called when user करोesn't want to use a vGPU mm object
 */
व्योम पूर्णांकel_vgpu_unpin_mm(काष्ठा पूर्णांकel_vgpu_mm *mm)
अणु
	atomic_dec_अगर_positive(&mm->pincount);
पूर्ण

/**
 * पूर्णांकel_vgpu_pin_mm - increase the pin count of a vGPU mm object
 * @mm: target vgpu mm
 *
 * This function is called when user wants to use a vGPU mm object. If this
 * mm object hasn't been shaकरोwed yet, the shaकरोw will be populated at this
 * समय.
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_pin_mm(काष्ठा पूर्णांकel_vgpu_mm *mm)
अणु
	पूर्णांक ret;

	atomic_inc(&mm->pincount);

	अगर (mm->type == INTEL_GVT_MM_PPGTT) अणु
		ret = shaकरोw_ppgtt_mm(mm);
		अगर (ret)
			वापस ret;

		mutex_lock(&mm->vgpu->gvt->gtt.ppgtt_mm_lock);
		list_move_tail(&mm->ppgtt_mm.lru_list,
			       &mm->vgpu->gvt->gtt.ppgtt_mm_lru_list_head);
		mutex_unlock(&mm->vgpu->gvt->gtt.ppgtt_mm_lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक reclaim_one_ppgtt_mm(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा पूर्णांकel_vgpu_mm *mm;
	काष्ठा list_head *pos, *n;

	mutex_lock(&gvt->gtt.ppgtt_mm_lock);

	list_क्रम_each_safe(pos, n, &gvt->gtt.ppgtt_mm_lru_list_head) अणु
		mm = container_of(pos, काष्ठा पूर्णांकel_vgpu_mm, ppgtt_mm.lru_list);

		अगर (atomic_पढ़ो(&mm->pincount))
			जारी;

		list_del_init(&mm->ppgtt_mm.lru_list);
		mutex_unlock(&gvt->gtt.ppgtt_mm_lock);
		invalidate_ppgtt_mm(mm);
		वापस 1;
	पूर्ण
	mutex_unlock(&gvt->gtt.ppgtt_mm_lock);
	वापस 0;
पूर्ण

/*
 * GMA translation APIs.
 */
अटल अंतरभूत पूर्णांक ppgtt_get_next_level_entry(काष्ठा पूर्णांकel_vgpu_mm *mm,
		काष्ठा पूर्णांकel_gvt_gtt_entry *e, अचिन्हित दीर्घ index, bool guest)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = mm->vgpu;
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	काष्ठा पूर्णांकel_vgpu_ppgtt_spt *s;

	s = पूर्णांकel_vgpu_find_spt_by_mfn(vgpu, ops->get_pfn(e));
	अगर (!s)
		वापस -ENXIO;

	अगर (!guest)
		ppgtt_get_shaकरोw_entry(s, e, index);
	अन्यथा
		ppgtt_get_guest_entry(s, e, index);
	वापस 0;
पूर्ण

/**
 * पूर्णांकel_vgpu_gma_to_gpa - translate a gma to GPA
 * @mm: mm object. could be a PPGTT or GGTT mm object
 * @gma: graphics memory address in this mm object
 *
 * This function is used to translate a graphics memory address in specअगरic
 * graphics memory space to guest physical address.
 *
 * Returns:
 * Guest physical address on success, INTEL_GVT_INVALID_ADDR अगर failed.
 */
अचिन्हित दीर्घ पूर्णांकel_vgpu_gma_to_gpa(काष्ठा पूर्णांकel_vgpu_mm *mm, अचिन्हित दीर्घ gma)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = mm->vgpu;
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *pte_ops = gvt->gtt.pte_ops;
	काष्ठा पूर्णांकel_gvt_gtt_gma_ops *gma_ops = gvt->gtt.gma_ops;
	अचिन्हित दीर्घ gpa = INTEL_GVT_INVALID_ADDR;
	अचिन्हित दीर्घ gma_index[4];
	काष्ठा पूर्णांकel_gvt_gtt_entry e;
	पूर्णांक i, levels = 0;
	पूर्णांक ret;

	GEM_BUG_ON(mm->type != INTEL_GVT_MM_GGTT &&
		   mm->type != INTEL_GVT_MM_PPGTT);

	अगर (mm->type == INTEL_GVT_MM_GGTT) अणु
		अगर (!vgpu_gmadr_is_valid(vgpu, gma))
			जाओ err;

		ggtt_get_guest_entry(mm, &e,
			gma_ops->gma_to_ggtt_pte_index(gma));

		gpa = (pte_ops->get_pfn(&e) << I915_GTT_PAGE_SHIFT)
			+ (gma & ~I915_GTT_PAGE_MASK);

		trace_gma_translate(vgpu->id, "ggtt", 0, 0, gma, gpa);
	पूर्ण अन्यथा अणु
		चयन (mm->ppgtt_mm.root_entry_type) अणु
		हाल GTT_TYPE_PPGTT_ROOT_L4_ENTRY:
			ppgtt_get_shaकरोw_root_entry(mm, &e, 0);

			gma_index[0] = gma_ops->gma_to_pml4_index(gma);
			gma_index[1] = gma_ops->gma_to_l4_pdp_index(gma);
			gma_index[2] = gma_ops->gma_to_pde_index(gma);
			gma_index[3] = gma_ops->gma_to_pte_index(gma);
			levels = 4;
			अवरोध;
		हाल GTT_TYPE_PPGTT_ROOT_L3_ENTRY:
			ppgtt_get_shaकरोw_root_entry(mm, &e,
					gma_ops->gma_to_l3_pdp_index(gma));

			gma_index[0] = gma_ops->gma_to_pde_index(gma);
			gma_index[1] = gma_ops->gma_to_pte_index(gma);
			levels = 2;
			अवरोध;
		शेष:
			GEM_BUG_ON(1);
		पूर्ण

		/* walk the shaकरोw page table and get gpa from guest entry */
		क्रम (i = 0; i < levels; i++) अणु
			ret = ppgtt_get_next_level_entry(mm, &e, gma_index[i],
				(i == levels - 1));
			अगर (ret)
				जाओ err;

			अगर (!pte_ops->test_present(&e)) अणु
				gvt_dbg_core("GMA 0x%lx is not present\n", gma);
				जाओ err;
			पूर्ण
		पूर्ण

		gpa = (pte_ops->get_pfn(&e) << I915_GTT_PAGE_SHIFT) +
					(gma & ~I915_GTT_PAGE_MASK);
		trace_gma_translate(vgpu->id, "ppgtt", 0,
				    mm->ppgtt_mm.root_entry_type, gma, gpa);
	पूर्ण

	वापस gpa;
err:
	gvt_vgpu_err("invalid mm type: %d gma %lx\n", mm->type, gma);
	वापस INTEL_GVT_INVALID_ADDR;
पूर्ण

अटल पूर्णांक emulate_ggtt_mmio_पढ़ो(काष्ठा पूर्णांकel_vgpu *vgpu,
	अचिन्हित पूर्णांक off, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा पूर्णांकel_vgpu_mm *ggtt_mm = vgpu->gtt.ggtt_mm;
	स्थिर काष्ठा पूर्णांकel_gvt_device_info *info = &vgpu->gvt->device_info;
	अचिन्हित दीर्घ index = off >> info->gtt_entry_size_shअगरt;
	अचिन्हित दीर्घ gma;
	काष्ठा पूर्णांकel_gvt_gtt_entry e;

	अगर (bytes != 4 && bytes != 8)
		वापस -EINVAL;

	gma = index << I915_GTT_PAGE_SHIFT;
	अगर (!पूर्णांकel_gvt_ggtt_validate_range(vgpu,
					   gma, 1 << I915_GTT_PAGE_SHIFT)) अणु
		gvt_dbg_mm("read invalid ggtt at 0x%lx\n", gma);
		स_रखो(p_data, 0, bytes);
		वापस 0;
	पूर्ण

	ggtt_get_guest_entry(ggtt_mm, &e, index);
	स_नकल(p_data, (व्योम *)&e.val64 + (off & (info->gtt_entry_size - 1)),
			bytes);
	वापस 0;
पूर्ण

/**
 * पूर्णांकel_vgpu_emulate_gtt_mmio_पढ़ो - emulate GTT MMIO रेजिस्टर पढ़ो
 * @vgpu: a vGPU
 * @off: रेजिस्टर offset
 * @p_data: data will be वापसed to guest
 * @bytes: data length
 *
 * This function is used to emulate the GTT MMIO रेजिस्टर पढ़ो
 *
 * Returns:
 * Zero on success, error code अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_emulate_ggtt_mmio_पढ़ो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक off,
	व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	स्थिर काष्ठा पूर्णांकel_gvt_device_info *info = &vgpu->gvt->device_info;
	पूर्णांक ret;

	अगर (bytes != 4 && bytes != 8)
		वापस -EINVAL;

	off -= info->gtt_start_offset;
	ret = emulate_ggtt_mmio_पढ़ो(vgpu, off, p_data, bytes);
	वापस ret;
पूर्ण

अटल व्योम ggtt_invalidate_pte(काष्ठा पूर्णांकel_vgpu *vgpu,
		काष्ठा पूर्णांकel_gvt_gtt_entry *entry)
अणु
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *pte_ops = vgpu->gvt->gtt.pte_ops;
	अचिन्हित दीर्घ pfn;

	pfn = pte_ops->get_pfn(entry);
	अगर (pfn != vgpu->gvt->gtt.scratch_mfn)
		पूर्णांकel_gvt_hypervisor_dma_unmap_guest_page(vgpu,
						pfn << PAGE_SHIFT);
पूर्ण

अटल पूर्णांक emulate_ggtt_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक off,
	व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	स्थिर काष्ठा पूर्णांकel_gvt_device_info *info = &gvt->device_info;
	काष्ठा पूर्णांकel_vgpu_mm *ggtt_mm = vgpu->gtt.ggtt_mm;
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *ops = gvt->gtt.pte_ops;
	अचिन्हित दीर्घ g_gtt_index = off >> info->gtt_entry_size_shअगरt;
	अचिन्हित दीर्घ gma, gfn;
	काष्ठा पूर्णांकel_gvt_gtt_entry e = अणु.val64 = 0, .type = GTT_TYPE_GGTT_PTEपूर्ण;
	काष्ठा पूर्णांकel_gvt_gtt_entry m = अणु.val64 = 0, .type = GTT_TYPE_GGTT_PTEपूर्ण;
	dma_addr_t dma_addr;
	पूर्णांक ret;
	काष्ठा पूर्णांकel_gvt_partial_pte *partial_pte, *pos, *n;
	bool partial_update = false;

	अगर (bytes != 4 && bytes != 8)
		वापस -EINVAL;

	gma = g_gtt_index << I915_GTT_PAGE_SHIFT;

	/* the VM may configure the whole GM space when ballooning is used */
	अगर (!vgpu_gmadr_is_valid(vgpu, gma))
		वापस 0;

	e.type = GTT_TYPE_GGTT_PTE;
	स_नकल((व्योम *)&e.val64 + (off & (info->gtt_entry_size - 1)), p_data,
			bytes);

	/* If ggtt entry size is 8 bytes, and it's split पूर्णांकo two 4 bytes
	 * ग_लिखो, save the first 4 bytes in a list and update भव
	 * PTE. Only update shaकरोw PTE when the second 4 bytes comes.
	 */
	अगर (bytes < info->gtt_entry_size) अणु
		bool found = false;

		list_क्रम_each_entry_safe(pos, n,
				&ggtt_mm->ggtt_mm.partial_pte_list, list) अणु
			अगर (g_gtt_index == pos->offset >>
					info->gtt_entry_size_shअगरt) अणु
				अगर (off != pos->offset) अणु
					/* the second partial part*/
					पूर्णांक last_off = pos->offset &
						(info->gtt_entry_size - 1);

					स_नकल((व्योम *)&e.val64 + last_off,
						(व्योम *)&pos->data + last_off,
						bytes);

					list_del(&pos->list);
					kमुक्त(pos);
					found = true;
					अवरोध;
				पूर्ण

				/* update of the first partial part */
				pos->data = e.val64;
				ggtt_set_guest_entry(ggtt_mm, &e, g_gtt_index);
				वापस 0;
			पूर्ण
		पूर्ण

		अगर (!found) अणु
			/* the first partial part */
			partial_pte = kzalloc(माप(*partial_pte), GFP_KERNEL);
			अगर (!partial_pte)
				वापस -ENOMEM;
			partial_pte->offset = off;
			partial_pte->data = e.val64;
			list_add_tail(&partial_pte->list,
				&ggtt_mm->ggtt_mm.partial_pte_list);
			partial_update = true;
		पूर्ण
	पूर्ण

	अगर (!partial_update && (ops->test_present(&e))) अणु
		gfn = ops->get_pfn(&e);
		m.val64 = e.val64;
		m.type = e.type;

		/* one PTE update may be issued in multiple ग_लिखोs and the
		 * first ग_लिखो may not स्थिरruct a valid gfn
		 */
		अगर (!पूर्णांकel_gvt_hypervisor_is_valid_gfn(vgpu, gfn)) अणु
			ops->set_pfn(&m, gvt->gtt.scratch_mfn);
			जाओ out;
		पूर्ण

		ret = पूर्णांकel_gvt_hypervisor_dma_map_guest_page(vgpu, gfn,
							PAGE_SIZE, &dma_addr);
		अगर (ret) अणु
			gvt_vgpu_err("fail to populate guest ggtt entry\n");
			/* guest driver may पढ़ो/ग_लिखो the entry when partial
			 * update the entry in this situation p2m will fail
			 * settting the shaकरोw entry to poपूर्णांक to a scratch page
			 */
			ops->set_pfn(&m, gvt->gtt.scratch_mfn);
		पूर्ण अन्यथा
			ops->set_pfn(&m, dma_addr >> PAGE_SHIFT);
	पूर्ण अन्यथा अणु
		ops->set_pfn(&m, gvt->gtt.scratch_mfn);
		ops->clear_present(&m);
	पूर्ण

out:
	ggtt_set_guest_entry(ggtt_mm, &e, g_gtt_index);

	ggtt_get_host_entry(ggtt_mm, &e, g_gtt_index);
	ggtt_invalidate_pte(vgpu, &e);

	ggtt_set_host_entry(ggtt_mm, &m, g_gtt_index);
	ggtt_invalidate(gvt->gt);
	वापस 0;
पूर्ण

/*
 * पूर्णांकel_vgpu_emulate_ggtt_mmio_ग_लिखो - emulate GTT MMIO रेजिस्टर ग_लिखो
 * @vgpu: a vGPU
 * @off: रेजिस्टर offset
 * @p_data: data from guest ग_लिखो
 * @bytes: data length
 *
 * This function is used to emulate the GTT MMIO रेजिस्टर ग_लिखो
 *
 * Returns:
 * Zero on success, error code अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_emulate_ggtt_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक off, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	स्थिर काष्ठा पूर्णांकel_gvt_device_info *info = &vgpu->gvt->device_info;
	पूर्णांक ret;
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;
	काष्ठा पूर्णांकel_engine_cs *engine;
	पूर्णांक i;

	अगर (bytes != 4 && bytes != 8)
		वापस -EINVAL;

	off -= info->gtt_start_offset;
	ret = emulate_ggtt_mmio_ग_लिखो(vgpu, off, p_data, bytes);

	/* अगर ggtt of last submitted context is written,
	 * that context is probably got unpinned.
	 * Set last shaकरोwed ctx to invalid.
	 */
	क्रम_each_engine(engine, vgpu->gvt->gt, i) अणु
		अगर (!s->last_ctx[i].valid)
			जारी;

		अगर (s->last_ctx[i].lrca == (off >> info->gtt_entry_size_shअगरt))
			s->last_ctx[i].valid = false;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक alloc_scratch_pages(काष्ठा पूर्णांकel_vgpu *vgpu,
		क्रमागत पूर्णांकel_gvt_gtt_type type)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;
	काष्ठा पूर्णांकel_vgpu_gtt *gtt = &vgpu->gtt;
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	पूर्णांक page_entry_num = I915_GTT_PAGE_SIZE >>
				vgpu->gvt->device_info.gtt_entry_size_shअगरt;
	व्योम *scratch_pt;
	पूर्णांक i;
	काष्ठा device *dev = vgpu->gvt->gt->i915->drm.dev;
	dma_addr_t daddr;

	अगर (drm_WARN_ON(&i915->drm,
			type < GTT_TYPE_PPGTT_PTE_PT || type >= GTT_TYPE_MAX))
		वापस -EINVAL;

	scratch_pt = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!scratch_pt) अणु
		gvt_vgpu_err("fail to allocate scratch page\n");
		वापस -ENOMEM;
	पूर्ण

	daddr = dma_map_page(dev, virt_to_page(scratch_pt), 0,
			4096, PCI_DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, daddr)) अणु
		gvt_vgpu_err("fail to dmamap scratch_pt\n");
		__मुक्त_page(virt_to_page(scratch_pt));
		वापस -ENOMEM;
	पूर्ण
	gtt->scratch_pt[type].page_mfn =
		(अचिन्हित दीर्घ)(daddr >> I915_GTT_PAGE_SHIFT);
	gtt->scratch_pt[type].page = virt_to_page(scratch_pt);
	gvt_dbg_mm("vgpu%d create scratch_pt: type %d mfn=0x%lx\n",
			vgpu->id, type, gtt->scratch_pt[type].page_mfn);

	/* Build the tree by full filled the scratch pt with the entries which
	 * poपूर्णांक to the next level scratch pt or scratch page. The
	 * scratch_pt[type] indicate the scratch pt/scratch page used by the
	 * 'type' pt.
	 * e.g. scratch_pt[GTT_TYPE_PPGTT_PDE_PT] is used by
	 * GTT_TYPE_PPGTT_PDE_PT level pt, that means this scratch_pt it self
	 * is GTT_TYPE_PPGTT_PTE_PT, and full filled by scratch page mfn.
	 */
	अगर (type > GTT_TYPE_PPGTT_PTE_PT) अणु
		काष्ठा पूर्णांकel_gvt_gtt_entry se;

		स_रखो(&se, 0, माप(काष्ठा पूर्णांकel_gvt_gtt_entry));
		se.type = get_entry_type(type - 1);
		ops->set_pfn(&se, gtt->scratch_pt[type - 1].page_mfn);

		/* The entry parameters like present/ग_लिखोable/cache type
		 * set to the same as i915's scratch page tree.
		 */
		se.val64 |= _PAGE_PRESENT | _PAGE_RW;
		अगर (type == GTT_TYPE_PPGTT_PDE_PT)
			se.val64 |= PPAT_CACHED;

		क्रम (i = 0; i < page_entry_num; i++)
			ops->set_entry(scratch_pt, &se, i, false, 0, vgpu);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक release_scratch_page_tree(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	पूर्णांक i;
	काष्ठा device *dev = vgpu->gvt->gt->i915->drm.dev;
	dma_addr_t daddr;

	क्रम (i = GTT_TYPE_PPGTT_PTE_PT; i < GTT_TYPE_MAX; i++) अणु
		अगर (vgpu->gtt.scratch_pt[i].page != शून्य) अणु
			daddr = (dma_addr_t)(vgpu->gtt.scratch_pt[i].page_mfn <<
					I915_GTT_PAGE_SHIFT);
			dma_unmap_page(dev, daddr, 4096, PCI_DMA_BIसूचीECTIONAL);
			__मुक्त_page(vgpu->gtt.scratch_pt[i].page);
			vgpu->gtt.scratch_pt[i].page = शून्य;
			vgpu->gtt.scratch_pt[i].page_mfn = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक create_scratch_page_tree(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	पूर्णांक i, ret;

	क्रम (i = GTT_TYPE_PPGTT_PTE_PT; i < GTT_TYPE_MAX; i++) अणु
		ret = alloc_scratch_pages(vgpu, i);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	release_scratch_page_tree(vgpu);
	वापस ret;
पूर्ण

/**
 * पूर्णांकel_vgpu_init_gtt - initialize per-vGPU graphics memory virulization
 * @vgpu: a vGPU
 *
 * This function is used to initialize per-vGPU graphics memory भवization
 * components.
 *
 * Returns:
 * Zero on success, error code अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_init_gtt(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा पूर्णांकel_vgpu_gtt *gtt = &vgpu->gtt;

	INIT_RADIX_TREE(&gtt->spt_tree, GFP_KERNEL);

	INIT_LIST_HEAD(&gtt->ppgtt_mm_list_head);
	INIT_LIST_HEAD(&gtt->oos_page_list_head);
	INIT_LIST_HEAD(&gtt->post_shaकरोw_list_head);

	gtt->ggtt_mm = पूर्णांकel_vgpu_create_ggtt_mm(vgpu);
	अगर (IS_ERR(gtt->ggtt_mm)) अणु
		gvt_vgpu_err("fail to create mm for ggtt.\n");
		वापस PTR_ERR(gtt->ggtt_mm);
	पूर्ण

	पूर्णांकel_vgpu_reset_ggtt(vgpu, false);

	INIT_LIST_HEAD(&gtt->ggtt_mm->ggtt_mm.partial_pte_list);

	वापस create_scratch_page_tree(vgpu);
पूर्ण

व्योम पूर्णांकel_vgpu_destroy_all_ppgtt_mm(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा list_head *pos, *n;
	काष्ठा पूर्णांकel_vgpu_mm *mm;

	list_क्रम_each_safe(pos, n, &vgpu->gtt.ppgtt_mm_list_head) अणु
		mm = container_of(pos, काष्ठा पूर्णांकel_vgpu_mm, ppgtt_mm.list);
		पूर्णांकel_vgpu_destroy_mm(mm);
	पूर्ण

	अगर (GEM_WARN_ON(!list_empty(&vgpu->gtt.ppgtt_mm_list_head)))
		gvt_err("vgpu ppgtt mm is not fully destroyed\n");

	अगर (GEM_WARN_ON(!radix_tree_empty(&vgpu->gtt.spt_tree))) अणु
		gvt_err("Why we still has spt not freed?\n");
		ppgtt_मुक्त_all_spt(vgpu);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_vgpu_destroy_ggtt_mm(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा पूर्णांकel_gvt_partial_pte *pos, *next;

	list_क्रम_each_entry_safe(pos, next,
				 &vgpu->gtt.ggtt_mm->ggtt_mm.partial_pte_list,
				 list) अणु
		gvt_dbg_mm("partial PTE update on hold 0x%lx : 0x%llx\n",
			pos->offset, pos->data);
		kमुक्त(pos);
	पूर्ण
	पूर्णांकel_vgpu_destroy_mm(vgpu->gtt.ggtt_mm);
	vgpu->gtt.ggtt_mm = शून्य;
पूर्ण

/**
 * पूर्णांकel_vgpu_clean_gtt - clean up per-vGPU graphics memory virulization
 * @vgpu: a vGPU
 *
 * This function is used to clean up per-vGPU graphics memory भवization
 * components.
 *
 * Returns:
 * Zero on success, error code अगर failed.
 */
व्योम पूर्णांकel_vgpu_clean_gtt(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	पूर्णांकel_vgpu_destroy_all_ppgtt_mm(vgpu);
	पूर्णांकel_vgpu_destroy_ggtt_mm(vgpu);
	release_scratch_page_tree(vgpu);
पूर्ण

अटल व्योम clean_spt_oos(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा पूर्णांकel_gvt_gtt *gtt = &gvt->gtt;
	काष्ठा list_head *pos, *n;
	काष्ठा पूर्णांकel_vgpu_oos_page *oos_page;

	WARN(!list_empty(&gtt->oos_page_use_list_head),
		"someone is still using oos page\n");

	list_क्रम_each_safe(pos, n, &gtt->oos_page_मुक्त_list_head) अणु
		oos_page = container_of(pos, काष्ठा पूर्णांकel_vgpu_oos_page, list);
		list_del(&oos_page->list);
		मुक्त_page((अचिन्हित दीर्घ)oos_page->mem);
		kमुक्त(oos_page);
	पूर्ण
पूर्ण

अटल पूर्णांक setup_spt_oos(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा पूर्णांकel_gvt_gtt *gtt = &gvt->gtt;
	काष्ठा पूर्णांकel_vgpu_oos_page *oos_page;
	पूर्णांक i;
	पूर्णांक ret;

	INIT_LIST_HEAD(&gtt->oos_page_मुक्त_list_head);
	INIT_LIST_HEAD(&gtt->oos_page_use_list_head);

	क्रम (i = 0; i < pपुनः_स्मृतिated_oos_pages; i++) अणु
		oos_page = kzalloc(माप(*oos_page), GFP_KERNEL);
		अगर (!oos_page) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण
		oos_page->mem = (व्योम *)__get_मुक्त_pages(GFP_KERNEL, 0);
		अगर (!oos_page->mem) अणु
			ret = -ENOMEM;
			kमुक्त(oos_page);
			जाओ fail;
		पूर्ण

		INIT_LIST_HEAD(&oos_page->list);
		INIT_LIST_HEAD(&oos_page->vm_list);
		oos_page->id = i;
		list_add_tail(&oos_page->list, &gtt->oos_page_मुक्त_list_head);
	पूर्ण

	gvt_dbg_mm("%d oos pages preallocated\n", i);

	वापस 0;
fail:
	clean_spt_oos(gvt);
	वापस ret;
पूर्ण

/**
 * पूर्णांकel_vgpu_find_ppgtt_mm - find a PPGTT mm object
 * @vgpu: a vGPU
 * @pdps: pdp root array
 *
 * This function is used to find a PPGTT mm object from mm object pool
 *
 * Returns:
 * poपूर्णांकer to mm object on success, शून्य अगर failed.
 */
काष्ठा पूर्णांकel_vgpu_mm *पूर्णांकel_vgpu_find_ppgtt_mm(काष्ठा पूर्णांकel_vgpu *vgpu,
		u64 pdps[])
अणु
	काष्ठा पूर्णांकel_vgpu_mm *mm;
	काष्ठा list_head *pos;

	list_क्रम_each(pos, &vgpu->gtt.ppgtt_mm_list_head) अणु
		mm = container_of(pos, काष्ठा पूर्णांकel_vgpu_mm, ppgtt_mm.list);

		चयन (mm->ppgtt_mm.root_entry_type) अणु
		हाल GTT_TYPE_PPGTT_ROOT_L4_ENTRY:
			अगर (pdps[0] == mm->ppgtt_mm.guest_pdps[0])
				वापस mm;
			अवरोध;
		हाल GTT_TYPE_PPGTT_ROOT_L3_ENTRY:
			अगर (!स_भेद(pdps, mm->ppgtt_mm.guest_pdps,
				    माप(mm->ppgtt_mm.guest_pdps)))
				वापस mm;
			अवरोध;
		शेष:
			GEM_BUG_ON(1);
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * पूर्णांकel_vgpu_get_ppgtt_mm - get or create a PPGTT mm object.
 * @vgpu: a vGPU
 * @root_entry_type: ppgtt root entry type
 * @pdps: guest pdps
 *
 * This function is used to find or create a PPGTT mm object from a guest.
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
काष्ठा पूर्णांकel_vgpu_mm *पूर्णांकel_vgpu_get_ppgtt_mm(काष्ठा पूर्णांकel_vgpu *vgpu,
		क्रमागत पूर्णांकel_gvt_gtt_type root_entry_type, u64 pdps[])
अणु
	काष्ठा पूर्णांकel_vgpu_mm *mm;

	mm = पूर्णांकel_vgpu_find_ppgtt_mm(vgpu, pdps);
	अगर (mm) अणु
		पूर्णांकel_vgpu_mm_get(mm);
	पूर्ण अन्यथा अणु
		mm = पूर्णांकel_vgpu_create_ppgtt_mm(vgpu, root_entry_type, pdps);
		अगर (IS_ERR(mm))
			gvt_vgpu_err("fail to create mm\n");
	पूर्ण
	वापस mm;
पूर्ण

/**
 * पूर्णांकel_vgpu_put_ppgtt_mm - find and put a PPGTT mm object.
 * @vgpu: a vGPU
 * @pdps: guest pdps
 *
 * This function is used to find a PPGTT mm object from a guest and destroy it.
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_put_ppgtt_mm(काष्ठा पूर्णांकel_vgpu *vgpu, u64 pdps[])
अणु
	काष्ठा पूर्णांकel_vgpu_mm *mm;

	mm = पूर्णांकel_vgpu_find_ppgtt_mm(vgpu, pdps);
	अगर (!mm) अणु
		gvt_vgpu_err("fail to find ppgtt instance.\n");
		वापस -EINVAL;
	पूर्ण
	पूर्णांकel_vgpu_mm_put(mm);
	वापस 0;
पूर्ण

/**
 * पूर्णांकel_gvt_init_gtt - initialize mm components of a GVT device
 * @gvt: GVT device
 *
 * This function is called at the initialization stage, to initialize
 * the mm components of a GVT device.
 *
 * Returns:
 * zero on success, negative error code अगर failed.
 */
पूर्णांक पूर्णांकel_gvt_init_gtt(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	पूर्णांक ret;
	व्योम *page;
	काष्ठा device *dev = gvt->gt->i915->drm.dev;
	dma_addr_t daddr;

	gvt_dbg_core("init gtt\n");

	gvt->gtt.pte_ops = &gen8_gtt_pte_ops;
	gvt->gtt.gma_ops = &gen8_gtt_gma_ops;

	page = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!page) अणु
		gvt_err("fail to allocate scratch ggtt page\n");
		वापस -ENOMEM;
	पूर्ण

	daddr = dma_map_page(dev, virt_to_page(page), 0,
			4096, PCI_DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, daddr)) अणु
		gvt_err("fail to dmamap scratch ggtt page\n");
		__मुक्त_page(virt_to_page(page));
		वापस -ENOMEM;
	पूर्ण

	gvt->gtt.scratch_page = virt_to_page(page);
	gvt->gtt.scratch_mfn = (अचिन्हित दीर्घ)(daddr >> I915_GTT_PAGE_SHIFT);

	अगर (enable_out_of_sync) अणु
		ret = setup_spt_oos(gvt);
		अगर (ret) अणु
			gvt_err("fail to initialize SPT oos\n");
			dma_unmap_page(dev, daddr, 4096, PCI_DMA_BIसूचीECTIONAL);
			__मुक्त_page(gvt->gtt.scratch_page);
			वापस ret;
		पूर्ण
	पूर्ण
	INIT_LIST_HEAD(&gvt->gtt.ppgtt_mm_lru_list_head);
	mutex_init(&gvt->gtt.ppgtt_mm_lock);
	वापस 0;
पूर्ण

/**
 * पूर्णांकel_gvt_clean_gtt - clean up mm components of a GVT device
 * @gvt: GVT device
 *
 * This function is called at the driver unloading stage, to clean up the
 * the mm components of a GVT device.
 *
 */
व्योम पूर्णांकel_gvt_clean_gtt(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा device *dev = gvt->gt->i915->drm.dev;
	dma_addr_t daddr = (dma_addr_t)(gvt->gtt.scratch_mfn <<
					I915_GTT_PAGE_SHIFT);

	dma_unmap_page(dev, daddr, 4096, PCI_DMA_BIसूचीECTIONAL);

	__मुक्त_page(gvt->gtt.scratch_page);

	अगर (enable_out_of_sync)
		clean_spt_oos(gvt);
पूर्ण

/**
 * पूर्णांकel_vgpu_invalidate_ppgtt - invalidate PPGTT instances
 * @vgpu: a vGPU
 *
 * This function is called when invalidate all PPGTT instances of a vGPU.
 *
 */
व्योम पूर्णांकel_vgpu_invalidate_ppgtt(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा list_head *pos, *n;
	काष्ठा पूर्णांकel_vgpu_mm *mm;

	list_क्रम_each_safe(pos, n, &vgpu->gtt.ppgtt_mm_list_head) अणु
		mm = container_of(pos, काष्ठा पूर्णांकel_vgpu_mm, ppgtt_mm.list);
		अगर (mm->type == INTEL_GVT_MM_PPGTT) अणु
			mutex_lock(&vgpu->gvt->gtt.ppgtt_mm_lock);
			list_del_init(&mm->ppgtt_mm.lru_list);
			mutex_unlock(&vgpu->gvt->gtt.ppgtt_mm_lock);
			अगर (mm->ppgtt_mm.shaकरोwed)
				invalidate_ppgtt_mm(mm);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_vgpu_reset_ggtt - reset the GGTT entry
 * @vgpu: a vGPU
 * @invalidate_old: invalidate old entries
 *
 * This function is called at the vGPU create stage
 * to reset all the GGTT entries.
 *
 */
व्योम पूर्णांकel_vgpu_reset_ggtt(काष्ठा पूर्णांकel_vgpu *vgpu, bool invalidate_old)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा पूर्णांकel_gvt_gtt_pte_ops *pte_ops = vgpu->gvt->gtt.pte_ops;
	काष्ठा पूर्णांकel_gvt_gtt_entry entry = अणु.type = GTT_TYPE_GGTT_PTEपूर्ण;
	काष्ठा पूर्णांकel_gvt_gtt_entry old_entry;
	u32 index;
	u32 num_entries;

	pte_ops->set_pfn(&entry, gvt->gtt.scratch_mfn);
	pte_ops->set_present(&entry);

	index = vgpu_aperture_gmadr_base(vgpu) >> PAGE_SHIFT;
	num_entries = vgpu_aperture_sz(vgpu) >> PAGE_SHIFT;
	जबतक (num_entries--) अणु
		अगर (invalidate_old) अणु
			ggtt_get_host_entry(vgpu->gtt.ggtt_mm, &old_entry, index);
			ggtt_invalidate_pte(vgpu, &old_entry);
		पूर्ण
		ggtt_set_host_entry(vgpu->gtt.ggtt_mm, &entry, index++);
	पूर्ण

	index = vgpu_hidden_gmadr_base(vgpu) >> PAGE_SHIFT;
	num_entries = vgpu_hidden_sz(vgpu) >> PAGE_SHIFT;
	जबतक (num_entries--) अणु
		अगर (invalidate_old) अणु
			ggtt_get_host_entry(vgpu->gtt.ggtt_mm, &old_entry, index);
			ggtt_invalidate_pte(vgpu, &old_entry);
		पूर्ण
		ggtt_set_host_entry(vgpu->gtt.ggtt_mm, &entry, index++);
	पूर्ण

	ggtt_invalidate(gvt->gt);
पूर्ण

/**
 * पूर्णांकel_vgpu_reset_gtt - reset the all GTT related status
 * @vgpu: a vGPU
 *
 * This function is called from vfio core to reset reset all
 * GTT related status, including GGTT, PPGTT, scratch page.
 *
 */
व्योम पूर्णांकel_vgpu_reset_gtt(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	/* Shaकरोw pages are only created when there is no page
	 * table tracking data, so हटाओ page tracking data after
	 * removing the shaकरोw pages.
	 */
	पूर्णांकel_vgpu_destroy_all_ppgtt_mm(vgpu);
	पूर्णांकel_vgpu_reset_ggtt(vgpu, true);
पूर्ण

/**
 * पूर्णांकel_gvt_restore_ggtt - restore all vGPU's ggtt entries
 * @gvt: पूर्णांकel gvt device
 *
 * This function is called at driver resume stage to restore
 * GGTT entries of every vGPU.
 *
 */
व्योम पूर्णांकel_gvt_restore_ggtt(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu;
	काष्ठा पूर्णांकel_vgpu_mm *mm;
	पूर्णांक id;
	gen8_pte_t pte;
	u32 idx, num_low, num_hi, offset;

	/* Restore dirty host ggtt क्रम all vGPUs */
	idr_क्रम_each_entry(&(gvt)->vgpu_idr, vgpu, id) अणु
		mm = vgpu->gtt.ggtt_mm;

		num_low = vgpu_aperture_sz(vgpu) >> PAGE_SHIFT;
		offset = vgpu_aperture_gmadr_base(vgpu) >> PAGE_SHIFT;
		क्रम (idx = 0; idx < num_low; idx++) अणु
			pte = mm->ggtt_mm.host_ggtt_aperture[idx];
			अगर (pte & _PAGE_PRESENT)
				ग_लिखो_pte64(vgpu->gvt->gt->ggtt, offset + idx, pte);
		पूर्ण

		num_hi = vgpu_hidden_sz(vgpu) >> PAGE_SHIFT;
		offset = vgpu_hidden_gmadr_base(vgpu) >> PAGE_SHIFT;
		क्रम (idx = 0; idx < num_hi; idx++) अणु
			pte = mm->ggtt_mm.host_ggtt_hidden[idx];
			अगर (pte & _PAGE_PRESENT)
				ग_लिखो_pte64(vgpu->gvt->gt->ggtt, offset + idx, pte);
		पूर्ण
	पूर्ण
पूर्ण
