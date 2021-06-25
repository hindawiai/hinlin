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
 *    Eddie Dong <eddie.करोng@पूर्णांकel.com>
 *    Jike Song <jike.song@पूर्णांकel.com>
 *
 * Contributors:
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *    Min He <min.he@पूर्णांकel.com>
 *    Bing Niu <bing.niu@पूर्णांकel.com>
 *
 */

#समावेश "i915_drv.h"
#समावेश "gvt.h"

क्रमागत अणु
	INTEL_GVT_PCI_BAR_GTTMMIO = 0,
	INTEL_GVT_PCI_BAR_APERTURE,
	INTEL_GVT_PCI_BAR_PIO,
	INTEL_GVT_PCI_BAR_MAX,
पूर्ण;

/* biपंचांगap क्रम writable bits (RW or RW1C bits, but cannot co-exist in one
 * byte) byte by byte in standard pci configuration space. (not the full
 * 256 bytes.)
 */
अटल स्थिर u8 pci_cfg_space_rw_bmp[PCI_INTERRUPT_LINE + 4] = अणु
	[PCI_COMMAND]		= 0xff, 0x07,
	[PCI_STATUS]		= 0x00, 0xf9, /* the only one RW1C byte */
	[PCI_CACHE_LINE_SIZE]	= 0xff,
	[PCI_BASE_ADDRESS_0 ... PCI_CARDBUS_CIS - 1] = 0xff,
	[PCI_ROM_ADDRESS]	= 0x01, 0xf8, 0xff, 0xff,
	[PCI_INTERRUPT_LINE]	= 0xff,
पूर्ण;

/**
 * vgpu_pci_cfg_mem_ग_लिखो - ग_लिखो भव cfg space memory
 * @vgpu: target vgpu
 * @off: offset
 * @src: src ptr to ग_लिखो
 * @bytes: number of bytes
 *
 * Use this function to ग_लिखो भव cfg space memory.
 * For standard cfg space, only RW bits can be changed,
 * and we emulates the RW1C behavior of PCI_STATUS रेजिस्टर.
 */
अटल व्योम vgpu_pci_cfg_mem_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक off,
				   u8 *src, अचिन्हित पूर्णांक bytes)
अणु
	u8 *cfg_base = vgpu_cfg_space(vgpu);
	u8 mask, new, old;
	pci_घातer_t pwr;
	पूर्णांक i = 0;

	क्रम (; i < bytes && (off + i < माप(pci_cfg_space_rw_bmp)); i++) अणु
		mask = pci_cfg_space_rw_bmp[off + i];
		old = cfg_base[off + i];
		new = src[i] & mask;

		/**
		 * The PCI_STATUS high byte has RW1C bits, here
		 * emulates clear by writing 1 क्रम these bits.
		 * Writing a 0b to RW1C bits has no effect.
		 */
		अगर (off + i == PCI_STATUS + 1)
			new = (~new & old) & mask;

		cfg_base[off + i] = (old & ~mask) | new;
	पूर्ण

	/* For other configuration space directly copy as it is. */
	अगर (i < bytes)
		स_नकल(cfg_base + off + i, src + i, bytes - i);

	अगर (off == vgpu->cfg_space.pmcsr_off && vgpu->cfg_space.pmcsr_off) अणु
		pwr = (pci_घातer_t __क्रमce)(*(u16*)(&vgpu_cfg_space(vgpu)[off])
			& PCI_PM_CTRL_STATE_MASK);
		अगर (pwr == PCI_D3hot)
			vgpu->d3_entered = true;
		gvt_dbg_core("vgpu-%d power status changed to %d\n",
			     vgpu->id, pwr);
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_vgpu_emulate_cfg_पढ़ो - emulate vGPU configuration space पढ़ो
 * @vgpu: target vgpu
 * @offset: offset
 * @p_data: वापस data ptr
 * @bytes: number of bytes to पढ़ो
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_emulate_cfg_पढ़ो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
	व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;

	अगर (drm_WARN_ON(&i915->drm, bytes > 4))
		वापस -EINVAL;

	अगर (drm_WARN_ON(&i915->drm,
			offset + bytes > vgpu->gvt->device_info.cfg_space_size))
		वापस -EINVAL;

	स_नकल(p_data, vgpu_cfg_space(vgpu) + offset, bytes);
	वापस 0;
पूर्ण

अटल पूर्णांक map_aperture(काष्ठा पूर्णांकel_vgpu *vgpu, bool map)
अणु
	phys_addr_t aperture_pa = vgpu_aperture_pa_base(vgpu);
	अचिन्हित दीर्घ aperture_sz = vgpu_aperture_sz(vgpu);
	u64 first_gfn;
	u64 val;
	पूर्णांक ret;

	अगर (map == vgpu->cfg_space.bar[INTEL_GVT_PCI_BAR_APERTURE].tracked)
		वापस 0;

	val = vgpu_cfg_space(vgpu)[PCI_BASE_ADDRESS_2];
	अगर (val & PCI_BASE_ADDRESS_MEM_TYPE_64)
		val = *(u64 *)(vgpu_cfg_space(vgpu) + PCI_BASE_ADDRESS_2);
	अन्यथा
		val = *(u32 *)(vgpu_cfg_space(vgpu) + PCI_BASE_ADDRESS_2);

	first_gfn = (val + vgpu_aperture_offset(vgpu)) >> PAGE_SHIFT;

	ret = पूर्णांकel_gvt_hypervisor_map_gfn_to_mfn(vgpu, first_gfn,
						  aperture_pa >> PAGE_SHIFT,
						  aperture_sz >> PAGE_SHIFT,
						  map);
	अगर (ret)
		वापस ret;

	vgpu->cfg_space.bar[INTEL_GVT_PCI_BAR_APERTURE].tracked = map;
	वापस 0;
पूर्ण

अटल पूर्णांक trap_gtपंचांगmio(काष्ठा पूर्णांकel_vgpu *vgpu, bool trap)
अणु
	u64 start, end;
	u64 val;
	पूर्णांक ret;

	अगर (trap == vgpu->cfg_space.bar[INTEL_GVT_PCI_BAR_GTTMMIO].tracked)
		वापस 0;

	val = vgpu_cfg_space(vgpu)[PCI_BASE_ADDRESS_0];
	अगर (val & PCI_BASE_ADDRESS_MEM_TYPE_64)
		start = *(u64 *)(vgpu_cfg_space(vgpu) + PCI_BASE_ADDRESS_0);
	अन्यथा
		start = *(u32 *)(vgpu_cfg_space(vgpu) + PCI_BASE_ADDRESS_0);

	start &= ~GENMASK(3, 0);
	end = start + vgpu->cfg_space.bar[INTEL_GVT_PCI_BAR_GTTMMIO].size - 1;

	ret = पूर्णांकel_gvt_hypervisor_set_trap_area(vgpu, start, end, trap);
	अगर (ret)
		वापस ret;

	vgpu->cfg_space.bar[INTEL_GVT_PCI_BAR_GTTMMIO].tracked = trap;
	वापस 0;
पूर्ण

अटल पूर्णांक emulate_pci_command_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
	अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u8 old = vgpu_cfg_space(vgpu)[offset];
	u8 new = *(u8 *)p_data;
	u8 changed = old ^ new;
	पूर्णांक ret;

	vgpu_pci_cfg_mem_ग_लिखो(vgpu, offset, p_data, bytes);
	अगर (!(changed & PCI_COMMAND_MEMORY))
		वापस 0;

	अगर (old & PCI_COMMAND_MEMORY) अणु
		ret = trap_gtपंचांगmio(vgpu, false);
		अगर (ret)
			वापस ret;
		ret = map_aperture(vgpu, false);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = trap_gtपंचांगmio(vgpu, true);
		अगर (ret)
			वापस ret;
		ret = map_aperture(vgpu, true);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक emulate_pci_rom_bar_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
	अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 *pval = (u32 *)(vgpu_cfg_space(vgpu) + offset);
	u32 new = *(u32 *)(p_data);

	अगर ((new & PCI_ROM_ADDRESS_MASK) == PCI_ROM_ADDRESS_MASK)
		/* We करोn't have rom, वापस size of 0. */
		*pval = 0;
	अन्यथा
		vgpu_pci_cfg_mem_ग_लिखो(vgpu, offset, p_data, bytes);
	वापस 0;
पूर्ण

अटल पूर्णांक emulate_pci_bar_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
	व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 new = *(u32 *)(p_data);
	bool lo = IS_ALIGNED(offset, 8);
	u64 size;
	पूर्णांक ret = 0;
	bool mmio_enabled =
		vgpu_cfg_space(vgpu)[PCI_COMMAND] & PCI_COMMAND_MEMORY;
	काष्ठा पूर्णांकel_vgpu_pci_bar *bars = vgpu->cfg_space.bar;

	/*
	 * Power-up software can determine how much address
	 * space the device requires by writing a value of
	 * all 1's to the रेजिस्टर and then पढ़ोing the value
	 * back. The device will वापस 0's in all don't-care
	 * address bits.
	 */
	अगर (new == 0xffffffff) अणु
		चयन (offset) अणु
		हाल PCI_BASE_ADDRESS_0:
		हाल PCI_BASE_ADDRESS_1:
			size = ~(bars[INTEL_GVT_PCI_BAR_GTTMMIO].size -1);
			पूर्णांकel_vgpu_ग_लिखो_pci_bar(vgpu, offset,
						size >> (lo ? 0 : 32), lo);
			/*
			 * Untrap the BAR, since guest hasn't configured a
			 * valid GPA
			 */
			ret = trap_gtपंचांगmio(vgpu, false);
			अवरोध;
		हाल PCI_BASE_ADDRESS_2:
		हाल PCI_BASE_ADDRESS_3:
			size = ~(bars[INTEL_GVT_PCI_BAR_APERTURE].size -1);
			पूर्णांकel_vgpu_ग_लिखो_pci_bar(vgpu, offset,
						size >> (lo ? 0 : 32), lo);
			ret = map_aperture(vgpu, false);
			अवरोध;
		शेष:
			/* Unimplemented BARs */
			पूर्णांकel_vgpu_ग_लिखो_pci_bar(vgpu, offset, 0x0, false);
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (offset) अणु
		हाल PCI_BASE_ADDRESS_0:
		हाल PCI_BASE_ADDRESS_1:
			/*
			 * Untrap the old BAR first, since guest has
			 * re-configured the BAR
			 */
			trap_gtपंचांगmio(vgpu, false);
			पूर्णांकel_vgpu_ग_लिखो_pci_bar(vgpu, offset, new, lo);
			ret = trap_gtपंचांगmio(vgpu, mmio_enabled);
			अवरोध;
		हाल PCI_BASE_ADDRESS_2:
		हाल PCI_BASE_ADDRESS_3:
			map_aperture(vgpu, false);
			पूर्णांकel_vgpu_ग_लिखो_pci_bar(vgpu, offset, new, lo);
			ret = map_aperture(vgpu, mmio_enabled);
			अवरोध;
		शेष:
			पूर्णांकel_vgpu_ग_लिखो_pci_bar(vgpu, offset, new, lo);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/**
 * पूर्णांकel_vgpu_emulate_cfg_पढ़ो - emulate vGPU configuration space ग_लिखो
 * @vgpu: target vgpu
 * @offset: offset
 * @p_data: ग_लिखो data ptr
 * @bytes: number of bytes to ग_लिखो
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_emulate_cfg_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
	व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;
	पूर्णांक ret;

	अगर (drm_WARN_ON(&i915->drm, bytes > 4))
		वापस -EINVAL;

	अगर (drm_WARN_ON(&i915->drm,
			offset + bytes > vgpu->gvt->device_info.cfg_space_size))
		वापस -EINVAL;

	/* First check अगर it's PCI_COMMAND */
	अगर (IS_ALIGNED(offset, 2) && offset == PCI_COMMAND) अणु
		अगर (drm_WARN_ON(&i915->drm, bytes > 2))
			वापस -EINVAL;
		वापस emulate_pci_command_ग_लिखो(vgpu, offset, p_data, bytes);
	पूर्ण

	चयन (roundकरोwn(offset, 4)) अणु
	हाल PCI_ROM_ADDRESS:
		अगर (drm_WARN_ON(&i915->drm, !IS_ALIGNED(offset, 4)))
			वापस -EINVAL;
		वापस emulate_pci_rom_bar_ग_लिखो(vgpu, offset, p_data, bytes);

	हाल PCI_BASE_ADDRESS_0 ... PCI_BASE_ADDRESS_5:
		अगर (drm_WARN_ON(&i915->drm, !IS_ALIGNED(offset, 4)))
			वापस -EINVAL;
		वापस emulate_pci_bar_ग_लिखो(vgpu, offset, p_data, bytes);

	हाल INTEL_GVT_PCI_SWSCI:
		अगर (drm_WARN_ON(&i915->drm, !IS_ALIGNED(offset, 4)))
			वापस -EINVAL;
		ret = पूर्णांकel_vgpu_emulate_opregion_request(vgpu, *(u32 *)p_data);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल INTEL_GVT_PCI_OPREGION:
		अगर (drm_WARN_ON(&i915->drm, !IS_ALIGNED(offset, 4)))
			वापस -EINVAL;
		ret = पूर्णांकel_vgpu_opregion_base_ग_लिखो_handler(vgpu,
						   *(u32 *)p_data);
		अगर (ret)
			वापस ret;

		vgpu_pci_cfg_mem_ग_लिखो(vgpu, offset, p_data, bytes);
		अवरोध;
	शेष:
		vgpu_pci_cfg_mem_ग_लिखो(vgpu, offset, p_data, bytes);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * पूर्णांकel_vgpu_init_cfg_space - init vGPU configuration space when create vGPU
 *
 * @vgpu: a vGPU
 * @primary: is the vGPU presented as primary
 *
 */
व्योम पूर्णांकel_vgpu_init_cfg_space(काष्ठा पूर्णांकel_vgpu *vgpu,
			       bool primary)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा pci_dev *pdev = to_pci_dev(gvt->gt->i915->drm.dev);
	स्थिर काष्ठा पूर्णांकel_gvt_device_info *info = &gvt->device_info;
	u16 *gmch_ctl;
	u8 next;

	स_नकल(vgpu_cfg_space(vgpu), gvt->firmware.cfg_space,
	       info->cfg_space_size);

	अगर (!primary) अणु
		vgpu_cfg_space(vgpu)[PCI_CLASS_DEVICE] =
			INTEL_GVT_PCI_CLASS_VGA_OTHER;
		vgpu_cfg_space(vgpu)[PCI_CLASS_PROG] =
			INTEL_GVT_PCI_CLASS_VGA_OTHER;
	पूर्ण

	/* Show guest that there isn't any stolen memory.*/
	gmch_ctl = (u16 *)(vgpu_cfg_space(vgpu) + INTEL_GVT_PCI_GMCH_CONTROL);
	*gmch_ctl &= ~(BDW_GMCH_GMS_MASK << BDW_GMCH_GMS_SHIFT);

	पूर्णांकel_vgpu_ग_लिखो_pci_bar(vgpu, PCI_BASE_ADDRESS_2,
				 gvt_aperture_pa_base(gvt), true);

	vgpu_cfg_space(vgpu)[PCI_COMMAND] &= ~(PCI_COMMAND_IO
					     | PCI_COMMAND_MEMORY
					     | PCI_COMMAND_MASTER);
	/*
	 * Clear the bar upper 32bit and let guest to assign the new value
	 */
	स_रखो(vgpu_cfg_space(vgpu) + PCI_BASE_ADDRESS_1, 0, 4);
	स_रखो(vgpu_cfg_space(vgpu) + PCI_BASE_ADDRESS_3, 0, 4);
	स_रखो(vgpu_cfg_space(vgpu) + PCI_BASE_ADDRESS_4, 0, 8);
	स_रखो(vgpu_cfg_space(vgpu) + INTEL_GVT_PCI_OPREGION, 0, 4);

	vgpu->cfg_space.bar[INTEL_GVT_PCI_BAR_GTTMMIO].size =
		pci_resource_len(pdev, 0);
	vgpu->cfg_space.bar[INTEL_GVT_PCI_BAR_APERTURE].size =
		pci_resource_len(pdev, 2);

	स_रखो(vgpu_cfg_space(vgpu) + PCI_ROM_ADDRESS, 0, 4);

	/* PM Support */
	vgpu->cfg_space.pmcsr_off = 0;
	अगर (vgpu_cfg_space(vgpu)[PCI_STATUS] & PCI_STATUS_CAP_LIST) अणु
		next = vgpu_cfg_space(vgpu)[PCI_CAPABILITY_LIST];
		करो अणु
			अगर (vgpu_cfg_space(vgpu)[next + PCI_CAP_LIST_ID] == PCI_CAP_ID_PM) अणु
				vgpu->cfg_space.pmcsr_off = next + PCI_PM_CTRL;
				अवरोध;
			पूर्ण
			next = vgpu_cfg_space(vgpu)[next + PCI_CAP_LIST_NEXT];
		पूर्ण जबतक (next);
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_vgpu_reset_cfg_space - reset vGPU configuration space
 *
 * @vgpu: a vGPU
 *
 */
व्योम पूर्णांकel_vgpu_reset_cfg_space(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	u8 cmd = vgpu_cfg_space(vgpu)[PCI_COMMAND];
	bool primary = vgpu_cfg_space(vgpu)[PCI_CLASS_DEVICE] !=
				INTEL_GVT_PCI_CLASS_VGA_OTHER;

	अगर (cmd & PCI_COMMAND_MEMORY) अणु
		trap_gtपंचांगmio(vgpu, false);
		map_aperture(vgpu, false);
	पूर्ण

	/**
	 * Currently we only करो such reset when vGPU is not
	 * owned by any VM, so we simply restore entire cfg
	 * space to शेष value.
	 */
	पूर्णांकel_vgpu_init_cfg_space(vgpu, primary);
पूर्ण
