<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Jerome Glisse.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Alex Deucher
 *          Jerome Glisse
 */

#समावेश <linux/console.h>
#समावेश <linux/efi.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/vga_चयनeroo.h>
#समावेश <linux/vgaarb.h>

#समावेश <drm/drm_cache.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/radeon_drm.h>

#समावेश "radeon_device.h"
#समावेश "radeon_reg.h"
#समावेश "radeon.h"
#समावेश "atom.h"

अटल स्थिर अक्षर radeon_family_name[][16] = अणु
	"R100",
	"RV100",
	"RS100",
	"RV200",
	"RS200",
	"R200",
	"RV250",
	"RS300",
	"RV280",
	"R300",
	"R350",
	"RV350",
	"RV380",
	"R420",
	"R423",
	"RV410",
	"RS400",
	"RS480",
	"RS600",
	"RS690",
	"RS740",
	"RV515",
	"R520",
	"RV530",
	"RV560",
	"RV570",
	"R580",
	"R600",
	"RV610",
	"RV630",
	"RV670",
	"RV620",
	"RV635",
	"RS780",
	"RS880",
	"RV770",
	"RV730",
	"RV710",
	"RV740",
	"CEDAR",
	"REDWOOD",
	"JUNIPER",
	"CYPRESS",
	"HEMLOCK",
	"PALM",
	"SUMO",
	"SUMO2",
	"BARTS",
	"TURKS",
	"CAICOS",
	"CAYMAN",
	"ARUBA",
	"TAHITI",
	"PITCAIRN",
	"VERDE",
	"OLAND",
	"HAINAN",
	"BONAIRE",
	"KAVERI",
	"KABINI",
	"HAWAII",
	"MULLINS",
	"LAST",
पूर्ण;

#अगर defined(CONFIG_VGA_SWITCHEROO)
bool radeon_has_atpx_dgpu_घातer_cntl(व्योम);
bool radeon_is_atpx_hybrid(व्योम);
#अन्यथा
अटल अंतरभूत bool radeon_has_atpx_dgpu_घातer_cntl(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool radeon_is_atpx_hybrid(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर

#घोषणा RADEON_PX_QUIRK_DISABLE_PX  (1 << 0)

काष्ठा radeon_px_quirk अणु
	u32 chip_venकरोr;
	u32 chip_device;
	u32 subsys_venकरोr;
	u32 subsys_device;
	u32 px_quirk_flags;
पूर्ण;

अटल काष्ठा radeon_px_quirk radeon_px_quirk_list[] = अणु
	/* Acer aspire 5560g (CPU: AMD A4-3305M; GPU: AMD Radeon HD 6480g + 7470m)
	 * https://bugzilla.kernel.org/show_bug.cgi?id=74551
	 */
	अणु PCI_VENDOR_ID_ATI, 0x6760, 0x1025, 0x0672, RADEON_PX_QUIRK_DISABLE_PX पूर्ण,
	/* Asus K73TA laptop with AMD A6-3400M APU and Radeon 6550 GPU
	 * https://bugzilla.kernel.org/show_bug.cgi?id=51381
	 */
	अणु PCI_VENDOR_ID_ATI, 0x6741, 0x1043, 0x108c, RADEON_PX_QUIRK_DISABLE_PX पूर्ण,
	/* Asus K53TK laptop with AMD A6-3420M APU and Radeon 7670m GPU
	 * https://bugzilla.kernel.org/show_bug.cgi?id=51381
	 */
	अणु PCI_VENDOR_ID_ATI, 0x6840, 0x1043, 0x2122, RADEON_PX_QUIRK_DISABLE_PX पूर्ण,
	/* Asus K53TK laptop with AMD A6-3420M APU and Radeon 7670m GPU
	 * https://bugs.मुक्तdesktop.org/show_bug.cgi?id=101491
	 */
	अणु PCI_VENDOR_ID_ATI, 0x6741, 0x1043, 0x2122, RADEON_PX_QUIRK_DISABLE_PX पूर्ण,
	/* Asus K73TK laptop with AMD A6-3420M APU and Radeon 7670m GPU
	 * https://bugzilla.kernel.org/show_bug.cgi?id=51381#c52
	 */
	अणु PCI_VENDOR_ID_ATI, 0x6840, 0x1043, 0x2123, RADEON_PX_QUIRK_DISABLE_PX पूर्ण,
	अणु 0, 0, 0, 0, 0 पूर्ण,
पूर्ण;

bool radeon_is_px(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	अगर (rdev->flags & RADEON_IS_PX)
		वापस true;
	वापस false;
पूर्ण

अटल व्योम radeon_device_handle_px_quirks(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_px_quirk *p = radeon_px_quirk_list;

	/* Apply PX quirks */
	जबतक (p && p->chip_device != 0) अणु
		अगर (rdev->pdev->venकरोr == p->chip_venकरोr &&
		    rdev->pdev->device == p->chip_device &&
		    rdev->pdev->subप्रणाली_venकरोr == p->subsys_venकरोr &&
		    rdev->pdev->subप्रणाली_device == p->subsys_device) अणु
			rdev->px_quirk_flags = p->px_quirk_flags;
			अवरोध;
		पूर्ण
		++p;
	पूर्ण

	अगर (rdev->px_quirk_flags & RADEON_PX_QUIRK_DISABLE_PX)
		rdev->flags &= ~RADEON_IS_PX;

	/* disable PX is the प्रणाली करोesn't support dGPU घातer control or hybrid gfx */
	अगर (!radeon_is_atpx_hybrid() &&
	    !radeon_has_atpx_dgpu_घातer_cntl())
		rdev->flags &= ~RADEON_IS_PX;
पूर्ण

/**
 * radeon_program_रेजिस्टर_sequence - program an array of रेजिस्टरs.
 *
 * @rdev: radeon_device poपूर्णांकer
 * @रेजिस्टरs: poपूर्णांकer to the रेजिस्टर array
 * @array_size: size of the रेजिस्टर array
 *
 * Programs an array or रेजिस्टरs with and and or masks.
 * This is a helper क्रम setting golden रेजिस्टरs.
 */
व्योम radeon_program_रेजिस्टर_sequence(काष्ठा radeon_device *rdev,
				      स्थिर u32 *रेजिस्टरs,
				      स्थिर u32 array_size)
अणु
	u32 पंचांगp, reg, and_mask, or_mask;
	पूर्णांक i;

	अगर (array_size % 3)
		वापस;

	क्रम (i = 0; i < array_size; i +=3) अणु
		reg = रेजिस्टरs[i + 0];
		and_mask = रेजिस्टरs[i + 1];
		or_mask = रेजिस्टरs[i + 2];

		अगर (and_mask == 0xffffffff) अणु
			पंचांगp = or_mask;
		पूर्ण अन्यथा अणु
			पंचांगp = RREG32(reg);
			पंचांगp &= ~and_mask;
			पंचांगp |= or_mask;
		पूर्ण
		WREG32(reg, पंचांगp);
	पूर्ण
पूर्ण

व्योम radeon_pci_config_reset(काष्ठा radeon_device *rdev)
अणु
	pci_ग_लिखो_config_dword(rdev->pdev, 0x7c, RADEON_ASIC_RESET_DATA);
पूर्ण

/**
 * radeon_surface_init - Clear GPU surface रेजिस्टरs.
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Clear GPU surface रेजिस्टरs (r1xx-r5xx).
 */
व्योम radeon_surface_init(काष्ठा radeon_device *rdev)
अणु
	/* FIXME: check this out */
	अगर (rdev->family < CHIP_R600) अणु
		पूर्णांक i;

		क्रम (i = 0; i < RADEON_GEM_MAX_SURFACES; i++) अणु
			अगर (rdev->surface_regs[i].bo)
				radeon_bo_get_surface_reg(rdev->surface_regs[i].bo);
			अन्यथा
				radeon_clear_surface_reg(rdev, i);
		पूर्ण
		/* enable surfaces */
		WREG32(RADEON_SURFACE_CNTL, 0);
	पूर्ण
पूर्ण

/*
 * GPU scratch रेजिस्टरs helpers function.
 */
/**
 * radeon_scratch_init - Init scratch रेजिस्टर driver inक्रमmation.
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Init CP scratch रेजिस्टर driver inक्रमmation (r1xx-r5xx)
 */
व्योम radeon_scratch_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	/* FIXME: check this out */
	अगर (rdev->family < CHIP_R300) अणु
		rdev->scratch.num_reg = 5;
	पूर्ण अन्यथा अणु
		rdev->scratch.num_reg = 7;
	पूर्ण
	rdev->scratch.reg_base = RADEON_SCRATCH_REG0;
	क्रम (i = 0; i < rdev->scratch.num_reg; i++) अणु
		rdev->scratch.मुक्त[i] = true;
		rdev->scratch.reg[i] = rdev->scratch.reg_base + (i * 4);
	पूर्ण
पूर्ण

/**
 * radeon_scratch_get - Allocate a scratch रेजिस्टर
 *
 * @rdev: radeon_device poपूर्णांकer
 * @reg: scratch रेजिस्टर mmio offset
 *
 * Allocate a CP scratch रेजिस्टर क्रम use by the driver (all asics).
 * Returns 0 on success or -EINVAL on failure.
 */
पूर्णांक radeon_scratch_get(काष्ठा radeon_device *rdev, uपूर्णांक32_t *reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rdev->scratch.num_reg; i++) अणु
		अगर (rdev->scratch.मुक्त[i]) अणु
			rdev->scratch.मुक्त[i] = false;
			*reg = rdev->scratch.reg[i];
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

/**
 * radeon_scratch_मुक्त - Free a scratch रेजिस्टर
 *
 * @rdev: radeon_device poपूर्णांकer
 * @reg: scratch रेजिस्टर mmio offset
 *
 * Free a CP scratch रेजिस्टर allocated क्रम use by the driver (all asics)
 */
व्योम radeon_scratch_मुक्त(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rdev->scratch.num_reg; i++) अणु
		अगर (rdev->scratch.reg[i] == reg) अणु
			rdev->scratch.मुक्त[i] = true;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * GPU करोorbell aperture helpers function.
 */
/**
 * radeon_करोorbell_init - Init करोorbell driver inक्रमmation.
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Init करोorbell driver inक्रमmation (CIK)
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक radeon_करोorbell_init(काष्ठा radeon_device *rdev)
अणु
	/* करोorbell bar mapping */
	rdev->करोorbell.base = pci_resource_start(rdev->pdev, 2);
	rdev->करोorbell.size = pci_resource_len(rdev->pdev, 2);

	rdev->करोorbell.num_करोorbells = min_t(u32, rdev->करोorbell.size / माप(u32), RADEON_MAX_DOORBELLS);
	अगर (rdev->करोorbell.num_करोorbells == 0)
		वापस -EINVAL;

	rdev->करोorbell.ptr = ioremap(rdev->करोorbell.base, rdev->करोorbell.num_करोorbells * माप(u32));
	अगर (rdev->करोorbell.ptr == शून्य) अणु
		वापस -ENOMEM;
	पूर्ण
	DRM_INFO("doorbell mmio base: 0x%08X\n", (uपूर्णांक32_t)rdev->करोorbell.base);
	DRM_INFO("doorbell mmio size: %u\n", (अचिन्हित)rdev->करोorbell.size);

	स_रखो(&rdev->करोorbell.used, 0, माप(rdev->करोorbell.used));

	वापस 0;
पूर्ण

/**
 * radeon_करोorbell_fini - Tear करोwn करोorbell driver inक्रमmation.
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Tear करोwn करोorbell driver inक्रमmation (CIK)
 */
अटल व्योम radeon_करोorbell_fini(काष्ठा radeon_device *rdev)
अणु
	iounmap(rdev->करोorbell.ptr);
	rdev->करोorbell.ptr = शून्य;
पूर्ण

/**
 * radeon_करोorbell_get - Allocate a करोorbell entry
 *
 * @rdev: radeon_device poपूर्णांकer
 * @करोorbell: करोorbell index
 *
 * Allocate a करोorbell क्रम use by the driver (all asics).
 * Returns 0 on success or -EINVAL on failure.
 */
पूर्णांक radeon_करोorbell_get(काष्ठा radeon_device *rdev, u32 *करोorbell)
अणु
	अचिन्हित दीर्घ offset = find_first_zero_bit(rdev->करोorbell.used, rdev->करोorbell.num_करोorbells);
	अगर (offset < rdev->करोorbell.num_करोorbells) अणु
		__set_bit(offset, rdev->करोorbell.used);
		*करोorbell = offset;
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * radeon_करोorbell_मुक्त - Free a करोorbell entry
 *
 * @rdev: radeon_device poपूर्णांकer
 * @करोorbell: करोorbell index
 *
 * Free a करोorbell allocated क्रम use by the driver (all asics)
 */
व्योम radeon_करोorbell_मुक्त(काष्ठा radeon_device *rdev, u32 करोorbell)
अणु
	अगर (करोorbell < rdev->करोorbell.num_करोorbells)
		__clear_bit(करोorbell, rdev->करोorbell.used);
पूर्ण

/*
 * radeon_wb_*()
 * Writeback is the the method by which the the GPU updates special pages
 * in memory with the status of certain GPU events (fences, ring poपूर्णांकers,
 * etc.).
 */

/**
 * radeon_wb_disable - Disable Writeback
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Disables Writeback (all asics).  Used क्रम suspend.
 */
व्योम radeon_wb_disable(काष्ठा radeon_device *rdev)
अणु
	rdev->wb.enabled = false;
पूर्ण

/**
 * radeon_wb_fini - Disable Writeback and मुक्त memory
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Disables Writeback and मुक्तs the Writeback memory (all asics).
 * Used at driver shutकरोwn.
 */
व्योम radeon_wb_fini(काष्ठा radeon_device *rdev)
अणु
	radeon_wb_disable(rdev);
	अगर (rdev->wb.wb_obj) अणु
		अगर (!radeon_bo_reserve(rdev->wb.wb_obj, false)) अणु
			radeon_bo_kunmap(rdev->wb.wb_obj);
			radeon_bo_unpin(rdev->wb.wb_obj);
			radeon_bo_unreserve(rdev->wb.wb_obj);
		पूर्ण
		radeon_bo_unref(&rdev->wb.wb_obj);
		rdev->wb.wb = शून्य;
		rdev->wb.wb_obj = शून्य;
	पूर्ण
पूर्ण

/**
 * radeon_wb_init- Init Writeback driver info and allocate memory
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Disables Writeback and मुक्तs the Writeback memory (all asics).
 * Used at driver startup.
 * Returns 0 on success or an -error on failure.
 */
पूर्णांक radeon_wb_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (rdev->wb.wb_obj == शून्य) अणु
		r = radeon_bo_create(rdev, RADEON_GPU_PAGE_SIZE, PAGE_SIZE, true,
				     RADEON_GEM_DOMAIN_GTT, 0, शून्य, शून्य,
				     &rdev->wb.wb_obj);
		अगर (r) अणु
			dev_warn(rdev->dev, "(%d) create WB bo failed\n", r);
			वापस r;
		पूर्ण
		r = radeon_bo_reserve(rdev->wb.wb_obj, false);
		अगर (unlikely(r != 0)) अणु
			radeon_wb_fini(rdev);
			वापस r;
		पूर्ण
		r = radeon_bo_pin(rdev->wb.wb_obj, RADEON_GEM_DOMAIN_GTT,
				&rdev->wb.gpu_addr);
		अगर (r) अणु
			radeon_bo_unreserve(rdev->wb.wb_obj);
			dev_warn(rdev->dev, "(%d) pin WB bo failed\n", r);
			radeon_wb_fini(rdev);
			वापस r;
		पूर्ण
		r = radeon_bo_kmap(rdev->wb.wb_obj, (व्योम **)&rdev->wb.wb);
		radeon_bo_unreserve(rdev->wb.wb_obj);
		अगर (r) अणु
			dev_warn(rdev->dev, "(%d) map WB bo failed\n", r);
			radeon_wb_fini(rdev);
			वापस r;
		पूर्ण
	पूर्ण

	/* clear wb memory */
	स_रखो((अक्षर *)rdev->wb.wb, 0, RADEON_GPU_PAGE_SIZE);
	/* disable event_ग_लिखो fences */
	rdev->wb.use_event = false;
	/* disabled via module param */
	अगर (radeon_no_wb == 1) अणु
		rdev->wb.enabled = false;
	पूर्ण अन्यथा अणु
		अगर (rdev->flags & RADEON_IS_AGP) अणु
			/* often unreliable on AGP */
			rdev->wb.enabled = false;
		पूर्ण अन्यथा अगर (rdev->family < CHIP_R300) अणु
			/* often unreliable on pre-r300 */
			rdev->wb.enabled = false;
		पूर्ण अन्यथा अणु
			rdev->wb.enabled = true;
			/* event_ग_लिखो fences are only available on r600+ */
			अगर (rdev->family >= CHIP_R600) अणु
				rdev->wb.use_event = true;
			पूर्ण
		पूर्ण
	पूर्ण
	/* always use ग_लिखोback/events on NI, APUs */
	अगर (rdev->family >= CHIP_PALM) अणु
		rdev->wb.enabled = true;
		rdev->wb.use_event = true;
	पूर्ण

	dev_info(rdev->dev, "WB %sabled\n", rdev->wb.enabled ? "en" : "dis");

	वापस 0;
पूर्ण

/**
 * radeon_vram_location - try to find VRAM location
 * @rdev: radeon device काष्ठाure holding all necessary inक्रमmations
 * @mc: memory controller काष्ठाure holding memory inक्रमmations
 * @base: base address at which to put VRAM
 *
 * Function will place try to place VRAM at base address provided
 * as parameter (which is so far either PCI aperture address or
 * क्रम IGP TOM base address).
 *
 * If there is not enough space to fit the unvisible VRAM in the 32bits
 * address space then we limit the VRAM size to the aperture.
 *
 * If we are using AGP and अगर the AGP aperture करोesn't allow us to have
 * room क्रम all the VRAM than we restrict the VRAM to the PCI aperture
 * size and prपूर्णांक a warning.
 *
 * This function will never fails, worst हाल are limiting VRAM.
 *
 * Note: GTT start, end, size should be initialized beक्रमe calling this
 * function on AGP platक्रमm.
 *
 * Note 1: We करोn't explicitly enक्रमce VRAM start to be aligned on VRAM size,
 * this shouldn't be a problem as we are using the PCI aperture as a reference.
 * Otherwise this would be needed क्रम rv280, all r3xx, and all r4xx, but
 * not IGP.
 *
 * Note 2: we use mc_vram_size as on some board we need to program the mc to
 * cover the whole aperture even अगर VRAM size is inferior to aperture size
 * Novell bug 204882 + aदीर्घ with lots of ubuntu ones
 *
 * Note 3: when limiting vram it's safe to overwritte real_vram_size because
 * we are not in हाल where real_vram_size is inferior to mc_vram_size (ie
 * note afected by bogus hw of Novell bug 204882 + aदीर्घ with lots of ubuntu
 * ones)
 *
 * Note 4: IGP TOM addr should be the same as the aperture addr, we करोn't
 * explicitly check क्रम that thought.
 *
 * FIXME: when reducing VRAM size align new size on घातer of 2.
 */
व्योम radeon_vram_location(काष्ठा radeon_device *rdev, काष्ठा radeon_mc *mc, u64 base)
अणु
	uपूर्णांक64_t limit = (uपूर्णांक64_t)radeon_vram_limit << 20;

	mc->vram_start = base;
	अगर (mc->mc_vram_size > (rdev->mc.mc_mask - base + 1)) अणु
		dev_warn(rdev->dev, "limiting VRAM to PCI aperture size\n");
		mc->real_vram_size = mc->aper_size;
		mc->mc_vram_size = mc->aper_size;
	पूर्ण
	mc->vram_end = mc->vram_start + mc->mc_vram_size - 1;
	अगर (rdev->flags & RADEON_IS_AGP && mc->vram_end > mc->gtt_start && mc->vram_start <= mc->gtt_end) अणु
		dev_warn(rdev->dev, "limiting VRAM to PCI aperture size\n");
		mc->real_vram_size = mc->aper_size;
		mc->mc_vram_size = mc->aper_size;
	पूर्ण
	mc->vram_end = mc->vram_start + mc->mc_vram_size - 1;
	अगर (limit && limit < mc->real_vram_size)
		mc->real_vram_size = limit;
	dev_info(rdev->dev, "VRAM: %lluM 0x%016llX - 0x%016llX (%lluM used)\n",
			mc->mc_vram_size >> 20, mc->vram_start,
			mc->vram_end, mc->real_vram_size >> 20);
पूर्ण

/**
 * radeon_gtt_location - try to find GTT location
 * @rdev: radeon device काष्ठाure holding all necessary inक्रमmations
 * @mc: memory controller काष्ठाure holding memory inक्रमmations
 *
 * Function will place try to place GTT beक्रमe or after VRAM.
 *
 * If GTT size is bigger than space left then we ajust GTT size.
 * Thus function will never fails.
 *
 * FIXME: when reducing GTT size align new size on घातer of 2.
 */
व्योम radeon_gtt_location(काष्ठा radeon_device *rdev, काष्ठा radeon_mc *mc)
अणु
	u64 size_af, size_bf;

	size_af = ((rdev->mc.mc_mask - mc->vram_end) + mc->gtt_base_align) & ~mc->gtt_base_align;
	size_bf = mc->vram_start & ~mc->gtt_base_align;
	अगर (size_bf > size_af) अणु
		अगर (mc->gtt_size > size_bf) अणु
			dev_warn(rdev->dev, "limiting GTT\n");
			mc->gtt_size = size_bf;
		पूर्ण
		mc->gtt_start = (mc->vram_start & ~mc->gtt_base_align) - mc->gtt_size;
	पूर्ण अन्यथा अणु
		अगर (mc->gtt_size > size_af) अणु
			dev_warn(rdev->dev, "limiting GTT\n");
			mc->gtt_size = size_af;
		पूर्ण
		mc->gtt_start = (mc->vram_end + 1 + mc->gtt_base_align) & ~mc->gtt_base_align;
	पूर्ण
	mc->gtt_end = mc->gtt_start + mc->gtt_size - 1;
	dev_info(rdev->dev, "GTT: %lluM 0x%016llX - 0x%016llX\n",
			mc->gtt_size >> 20, mc->gtt_start, mc->gtt_end);
पूर्ण

/*
 * GPU helpers function.
 */

/*
 * radeon_device_is_भव - check अगर we are running is a भव environment
 *
 * Check अगर the asic has been passed through to a VM (all asics).
 * Used at driver startup.
 * Returns true अगर भव or false अगर not.
 */
bool radeon_device_is_भव(व्योम)
अणु
#अगर_घोषित CONFIG_X86
	वापस boot_cpu_has(X86_FEATURE_HYPERVISOR);
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

/**
 * radeon_card_posted - check अगर the hw has alपढ़ोy been initialized
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Check अगर the asic has been initialized (all asics).
 * Used at driver startup.
 * Returns true अगर initialized or false अगर not.
 */
bool radeon_card_posted(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t reg;

	/* क्रम pass through, always क्रमce asic_init क्रम CI */
	अगर (rdev->family >= CHIP_BONAIRE &&
	    radeon_device_is_भव())
		वापस false;

	/* required क्रम EFI mode on macbook2,1 which uses an r5xx asic */
	अगर (efi_enabled(EFI_BOOT) &&
	    (rdev->pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_APPLE) &&
	    (rdev->family < CHIP_R600))
		वापस false;

	अगर (ASIC_IS_NODCE(rdev))
		जाओ check_memsize;

	/* first check CRTCs */
	अगर (ASIC_IS_DCE4(rdev)) अणु
		reg = RREG32(EVERGREEN_CRTC_CONTROL + EVERGREEN_CRTC0_REGISTER_OFFSET) |
			RREG32(EVERGREEN_CRTC_CONTROL + EVERGREEN_CRTC1_REGISTER_OFFSET);
			अगर (rdev->num_crtc >= 4) अणु
				reg |= RREG32(EVERGREEN_CRTC_CONTROL + EVERGREEN_CRTC2_REGISTER_OFFSET) |
					RREG32(EVERGREEN_CRTC_CONTROL + EVERGREEN_CRTC3_REGISTER_OFFSET);
			पूर्ण
			अगर (rdev->num_crtc >= 6) अणु
				reg |= RREG32(EVERGREEN_CRTC_CONTROL + EVERGREEN_CRTC4_REGISTER_OFFSET) |
					RREG32(EVERGREEN_CRTC_CONTROL + EVERGREEN_CRTC5_REGISTER_OFFSET);
			पूर्ण
		अगर (reg & EVERGREEN_CRTC_MASTER_EN)
			वापस true;
	पूर्ण अन्यथा अगर (ASIC_IS_AVIVO(rdev)) अणु
		reg = RREG32(AVIVO_D1CRTC_CONTROL) |
		      RREG32(AVIVO_D2CRTC_CONTROL);
		अगर (reg & AVIVO_CRTC_EN) अणु
			वापस true;
		पूर्ण
	पूर्ण अन्यथा अणु
		reg = RREG32(RADEON_CRTC_GEN_CNTL) |
		      RREG32(RADEON_CRTC2_GEN_CNTL);
		अगर (reg & RADEON_CRTC_EN) अणु
			वापस true;
		पूर्ण
	पूर्ण

check_memsize:
	/* then check MEM_SIZE, in हाल the crtcs are off */
	अगर (rdev->family >= CHIP_R600)
		reg = RREG32(R600_CONFIG_MEMSIZE);
	अन्यथा
		reg = RREG32(RADEON_CONFIG_MEMSIZE);

	अगर (reg)
		वापस true;

	वापस false;

पूर्ण

/**
 * radeon_update_bandwidth_info - update display bandwidth params
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Used when sclk/mclk are चयनed or display modes are set.
 * params are used to calculate display watermarks (all asics)
 */
व्योम radeon_update_bandwidth_info(काष्ठा radeon_device *rdev)
अणु
	fixed20_12 a;
	u32 sclk = rdev->pm.current_sclk;
	u32 mclk = rdev->pm.current_mclk;

	/* sclk/mclk in Mhz */
	a.full = dfixed_स्थिर(100);
	rdev->pm.sclk.full = dfixed_स्थिर(sclk);
	rdev->pm.sclk.full = dfixed_भाग(rdev->pm.sclk, a);
	rdev->pm.mclk.full = dfixed_स्थिर(mclk);
	rdev->pm.mclk.full = dfixed_भाग(rdev->pm.mclk, a);

	अगर (rdev->flags & RADEON_IS_IGP) अणु
		a.full = dfixed_स्थिर(16);
		/* core_bandwidth = sclk(Mhz) * 16 */
		rdev->pm.core_bandwidth.full = dfixed_भाग(rdev->pm.sclk, a);
	पूर्ण
पूर्ण

/**
 * radeon_boot_test_post_card - check and possibly initialize the hw
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Check अगर the asic is initialized and अगर not, attempt to initialize
 * it (all asics).
 * Returns true अगर initialized or false अगर not.
 */
bool radeon_boot_test_post_card(काष्ठा radeon_device *rdev)
अणु
	अगर (radeon_card_posted(rdev))
		वापस true;

	अगर (rdev->bios) अणु
		DRM_INFO("GPU not posted. posting now...\n");
		अगर (rdev->is_atom_bios)
			atom_asic_init(rdev->mode_info.atom_context);
		अन्यथा
			radeon_combios_asic_init(rdev->ddev);
		वापस true;
	पूर्ण अन्यथा अणु
		dev_err(rdev->dev, "Card not posted and no BIOS - ignoring\n");
		वापस false;
	पूर्ण
पूर्ण

/**
 * radeon_dummy_page_init - init dummy page used by the driver
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Allocate the dummy page used by the driver (all asics).
 * This dummy page is used by the driver as a filler क्रम gart entries
 * when pages are taken out of the GART
 * Returns 0 on sucess, -ENOMEM on failure.
 */
पूर्णांक radeon_dummy_page_init(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->dummy_page.page)
		वापस 0;
	rdev->dummy_page.page = alloc_page(GFP_DMA32 | GFP_KERNEL | __GFP_ZERO);
	अगर (rdev->dummy_page.page == शून्य)
		वापस -ENOMEM;
	rdev->dummy_page.addr = dma_map_page(&rdev->pdev->dev, rdev->dummy_page.page,
					0, PAGE_SIZE, PCI_DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(&rdev->pdev->dev, rdev->dummy_page.addr)) अणु
		dev_err(&rdev->pdev->dev, "Failed to DMA MAP the dummy page\n");
		__मुक्त_page(rdev->dummy_page.page);
		rdev->dummy_page.page = शून्य;
		वापस -ENOMEM;
	पूर्ण
	rdev->dummy_page.entry = radeon_gart_get_page_entry(rdev->dummy_page.addr,
							    RADEON_GART_PAGE_DUMMY);
	वापस 0;
पूर्ण

/**
 * radeon_dummy_page_fini - मुक्त dummy page used by the driver
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Frees the dummy page used by the driver (all asics).
 */
व्योम radeon_dummy_page_fini(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->dummy_page.page == शून्य)
		वापस;
	pci_unmap_page(rdev->pdev, rdev->dummy_page.addr,
			PAGE_SIZE, PCI_DMA_BIसूचीECTIONAL);
	__मुक्त_page(rdev->dummy_page.page);
	rdev->dummy_page.page = शून्य;
पूर्ण


/* ATOM accessor methods */
/*
 * ATOM is an पूर्णांकerpreted byte code stored in tables in the vbios.  The
 * driver रेजिस्टरs callbacks to access रेजिस्टरs and the पूर्णांकerpreter
 * in the driver parses the tables and executes then to program specअगरic
 * actions (set display modes, asic init, etc.).  See radeon_atombios.c,
 * atomमूलप्रण.स, and atom.c
 */

/**
 * cail_pll_पढ़ो - पढ़ो PLL रेजिस्टर
 *
 * @info: atom card_info poपूर्णांकer
 * @reg: PLL रेजिस्टर offset
 *
 * Provides a PLL रेजिस्टर accessor क्रम the atom पूर्णांकerpreter (r4xx+).
 * Returns the value of the PLL रेजिस्टर.
 */
अटल uपूर्णांक32_t cail_pll_पढ़ो(काष्ठा card_info *info, uपूर्णांक32_t reg)
अणु
	काष्ठा radeon_device *rdev = info->dev->dev_निजी;
	uपूर्णांक32_t r;

	r = rdev->pll_rreg(rdev, reg);
	वापस r;
पूर्ण

/**
 * cail_pll_ग_लिखो - ग_लिखो PLL रेजिस्टर
 *
 * @info: atom card_info poपूर्णांकer
 * @reg: PLL रेजिस्टर offset
 * @val: value to ग_लिखो to the pll रेजिस्टर
 *
 * Provides a PLL रेजिस्टर accessor क्रम the atom पूर्णांकerpreter (r4xx+).
 */
अटल व्योम cail_pll_ग_लिखो(काष्ठा card_info *info, uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	काष्ठा radeon_device *rdev = info->dev->dev_निजी;

	rdev->pll_wreg(rdev, reg, val);
पूर्ण

/**
 * cail_mc_पढ़ो - पढ़ो MC (Memory Controller) रेजिस्टर
 *
 * @info: atom card_info poपूर्णांकer
 * @reg: MC रेजिस्टर offset
 *
 * Provides an MC रेजिस्टर accessor क्रम the atom पूर्णांकerpreter (r4xx+).
 * Returns the value of the MC रेजिस्टर.
 */
अटल uपूर्णांक32_t cail_mc_पढ़ो(काष्ठा card_info *info, uपूर्णांक32_t reg)
अणु
	काष्ठा radeon_device *rdev = info->dev->dev_निजी;
	uपूर्णांक32_t r;

	r = rdev->mc_rreg(rdev, reg);
	वापस r;
पूर्ण

/**
 * cail_mc_ग_लिखो - ग_लिखो MC (Memory Controller) रेजिस्टर
 *
 * @info: atom card_info poपूर्णांकer
 * @reg: MC रेजिस्टर offset
 * @val: value to ग_लिखो to the pll रेजिस्टर
 *
 * Provides a MC रेजिस्टर accessor क्रम the atom पूर्णांकerpreter (r4xx+).
 */
अटल व्योम cail_mc_ग_लिखो(काष्ठा card_info *info, uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	काष्ठा radeon_device *rdev = info->dev->dev_निजी;

	rdev->mc_wreg(rdev, reg, val);
पूर्ण

/**
 * cail_reg_ग_लिखो - ग_लिखो MMIO रेजिस्टर
 *
 * @info: atom card_info poपूर्णांकer
 * @reg: MMIO रेजिस्टर offset
 * @val: value to ग_लिखो to the pll रेजिस्टर
 *
 * Provides a MMIO रेजिस्टर accessor क्रम the atom पूर्णांकerpreter (r4xx+).
 */
अटल व्योम cail_reg_ग_लिखो(काष्ठा card_info *info, uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	काष्ठा radeon_device *rdev = info->dev->dev_निजी;

	WREG32(reg*4, val);
पूर्ण

/**
 * cail_reg_पढ़ो - पढ़ो MMIO रेजिस्टर
 *
 * @info: atom card_info poपूर्णांकer
 * @reg: MMIO रेजिस्टर offset
 *
 * Provides an MMIO रेजिस्टर accessor क्रम the atom पूर्णांकerpreter (r4xx+).
 * Returns the value of the MMIO रेजिस्टर.
 */
अटल uपूर्णांक32_t cail_reg_पढ़ो(काष्ठा card_info *info, uपूर्णांक32_t reg)
अणु
	काष्ठा radeon_device *rdev = info->dev->dev_निजी;
	uपूर्णांक32_t r;

	r = RREG32(reg*4);
	वापस r;
पूर्ण

/**
 * cail_ioreg_ग_लिखो - ग_लिखो IO रेजिस्टर
 *
 * @info: atom card_info poपूर्णांकer
 * @reg: IO रेजिस्टर offset
 * @val: value to ग_लिखो to the pll रेजिस्टर
 *
 * Provides a IO रेजिस्टर accessor क्रम the atom पूर्णांकerpreter (r4xx+).
 */
अटल व्योम cail_ioreg_ग_लिखो(काष्ठा card_info *info, uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	काष्ठा radeon_device *rdev = info->dev->dev_निजी;

	WREG32_IO(reg*4, val);
पूर्ण

/**
 * cail_ioreg_पढ़ो - पढ़ो IO रेजिस्टर
 *
 * @info: atom card_info poपूर्णांकer
 * @reg: IO रेजिस्टर offset
 *
 * Provides an IO रेजिस्टर accessor क्रम the atom पूर्णांकerpreter (r4xx+).
 * Returns the value of the IO रेजिस्टर.
 */
अटल uपूर्णांक32_t cail_ioreg_पढ़ो(काष्ठा card_info *info, uपूर्णांक32_t reg)
अणु
	काष्ठा radeon_device *rdev = info->dev->dev_निजी;
	uपूर्णांक32_t r;

	r = RREG32_IO(reg*4);
	वापस r;
पूर्ण

/**
 * radeon_atombios_init - init the driver info and callbacks क्रम atombios
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Initializes the driver info and रेजिस्टर access callbacks क्रम the
 * ATOM पूर्णांकerpreter (r4xx+).
 * Returns 0 on sucess, -ENOMEM on failure.
 * Called at driver startup.
 */
पूर्णांक radeon_atombios_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा card_info *atom_card_info =
	    kzalloc(माप(काष्ठा card_info), GFP_KERNEL);

	अगर (!atom_card_info)
		वापस -ENOMEM;

	rdev->mode_info.atom_card_info = atom_card_info;
	atom_card_info->dev = rdev->ddev;
	atom_card_info->reg_पढ़ो = cail_reg_पढ़ो;
	atom_card_info->reg_ग_लिखो = cail_reg_ग_लिखो;
	/* needed क्रम iio ops */
	अगर (rdev->rio_mem) अणु
		atom_card_info->ioreg_पढ़ो = cail_ioreg_पढ़ो;
		atom_card_info->ioreg_ग_लिखो = cail_ioreg_ग_लिखो;
	पूर्ण अन्यथा अणु
		DRM_ERROR("Unable to find PCI I/O BAR; using MMIO for ATOM IIO\n");
		atom_card_info->ioreg_पढ़ो = cail_reg_पढ़ो;
		atom_card_info->ioreg_ग_लिखो = cail_reg_ग_लिखो;
	पूर्ण
	atom_card_info->mc_पढ़ो = cail_mc_पढ़ो;
	atom_card_info->mc_ग_लिखो = cail_mc_ग_लिखो;
	atom_card_info->pll_पढ़ो = cail_pll_पढ़ो;
	atom_card_info->pll_ग_लिखो = cail_pll_ग_लिखो;

	rdev->mode_info.atom_context = atom_parse(atom_card_info, rdev->bios);
	अगर (!rdev->mode_info.atom_context) अणु
		radeon_atombios_fini(rdev);
		वापस -ENOMEM;
	पूर्ण

	mutex_init(&rdev->mode_info.atom_context->mutex);
	mutex_init(&rdev->mode_info.atom_context->scratch_mutex);
	radeon_atom_initialize_bios_scratch_regs(rdev->ddev);
	atom_allocate_fb_scratch(rdev->mode_info.atom_context);
	वापस 0;
पूर्ण

/**
 * radeon_atombios_fini - मुक्त the driver info and callbacks क्रम atombios
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Frees the driver info and रेजिस्टर access callbacks क्रम the ATOM
 * पूर्णांकerpreter (r4xx+).
 * Called at driver shutकरोwn.
 */
व्योम radeon_atombios_fini(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->mode_info.atom_context) अणु
		kमुक्त(rdev->mode_info.atom_context->scratch);
	पूर्ण
	kमुक्त(rdev->mode_info.atom_context);
	rdev->mode_info.atom_context = शून्य;
	kमुक्त(rdev->mode_info.atom_card_info);
	rdev->mode_info.atom_card_info = शून्य;
पूर्ण

/* COMBIOS */
/*
 * COMBIOS is the bios क्रमmat prior to ATOM. It provides
 * command tables similar to ATOM, but करोesn't have a unअगरied
 * parser.  See radeon_combios.c
 */

/**
 * radeon_combios_init - init the driver info क्रम combios
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Initializes the driver info क्रम combios (r1xx-r3xx).
 * Returns 0 on sucess.
 * Called at driver startup.
 */
पूर्णांक radeon_combios_init(काष्ठा radeon_device *rdev)
अणु
	radeon_combios_initialize_bios_scratch_regs(rdev->ddev);
	वापस 0;
पूर्ण

/**
 * radeon_combios_fini - मुक्त the driver info क्रम combios
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Frees the driver info क्रम combios (r1xx-r3xx).
 * Called at driver shutकरोwn.
 */
व्योम radeon_combios_fini(काष्ठा radeon_device *rdev)
अणु
पूर्ण

/* अगर we get transitioned to only one device, take VGA back */
/**
 * radeon_vga_set_decode - enable/disable vga decode
 *
 * @cookie: radeon_device poपूर्णांकer
 * @state: enable/disable vga decode
 *
 * Enable/disable vga decode (all asics).
 * Returns VGA resource flags.
 */
अटल अचिन्हित पूर्णांक radeon_vga_set_decode(व्योम *cookie, bool state)
अणु
	काष्ठा radeon_device *rdev = cookie;
	radeon_vga_set_state(rdev, state);
	अगर (state)
		वापस VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM |
		       VGA_RSRC_NORMAL_IO | VGA_RSRC_NORMAL_MEM;
	अन्यथा
		वापस VGA_RSRC_NORMAL_IO | VGA_RSRC_NORMAL_MEM;
पूर्ण

/**
 * radeon_check_pot_argument - check that argument is a घातer of two
 *
 * @arg: value to check
 *
 * Validates that a certain argument is a घातer of two (all asics).
 * Returns true अगर argument is valid.
 */
अटल bool radeon_check_pot_argument(पूर्णांक arg)
अणु
	वापस (arg & (arg - 1)) == 0;
पूर्ण

/**
 * Determine a sensible शेष GART size according to ASIC family.
 *
 * @family: ASIC family name
 */
अटल पूर्णांक radeon_gart_size_स्वतः(क्रमागत radeon_family family)
अणु
	/* शेष to a larger gart size on newer asics */
	अगर (family >= CHIP_TAHITI)
		वापस 2048;
	अन्यथा अगर (family >= CHIP_RV770)
		वापस 1024;
	अन्यथा
		वापस 512;
पूर्ण

/**
 * radeon_check_arguments - validate module params
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Validates certain module parameters and updates
 * the associated values used by the driver (all asics).
 */
अटल व्योम radeon_check_arguments(काष्ठा radeon_device *rdev)
अणु
	/* vramlimit must be a घातer of two */
	अगर (!radeon_check_pot_argument(radeon_vram_limit)) अणु
		dev_warn(rdev->dev, "vram limit (%d) must be a power of 2\n",
				radeon_vram_limit);
		radeon_vram_limit = 0;
	पूर्ण

	अगर (radeon_gart_size == -1) अणु
		radeon_gart_size = radeon_gart_size_स्वतः(rdev->family);
	पूर्ण
	/* gtt size must be घातer of two and greater or equal to 32M */
	अगर (radeon_gart_size < 32) अणु
		dev_warn(rdev->dev, "gart size (%d) too small\n",
				radeon_gart_size);
		radeon_gart_size = radeon_gart_size_स्वतः(rdev->family);
	पूर्ण अन्यथा अगर (!radeon_check_pot_argument(radeon_gart_size)) अणु
		dev_warn(rdev->dev, "gart size (%d) must be a power of 2\n",
				radeon_gart_size);
		radeon_gart_size = radeon_gart_size_स्वतः(rdev->family);
	पूर्ण
	rdev->mc.gtt_size = (uपूर्णांक64_t)radeon_gart_size << 20;

	/* AGP mode can only be -1, 1, 2, 4, 8 */
	चयन (radeon_agpmode) अणु
	हाल -1:
	हाल 0:
	हाल 1:
	हाल 2:
	हाल 4:
	हाल 8:
		अवरोध;
	शेष:
		dev_warn(rdev->dev, "invalid AGP mode %d (valid mode: "
				"-1, 0, 1, 2, 4, 8)\n", radeon_agpmode);
		radeon_agpmode = 0;
		अवरोध;
	पूर्ण

	अगर (!radeon_check_pot_argument(radeon_vm_size)) अणु
		dev_warn(rdev->dev, "VM size (%d) must be a power of 2\n",
			 radeon_vm_size);
		radeon_vm_size = 4;
	पूर्ण

	अगर (radeon_vm_size < 1) अणु
		dev_warn(rdev->dev, "VM size (%d) too small, min is 1GB\n",
			 radeon_vm_size);
		radeon_vm_size = 4;
	पूर्ण

	/*
	 * Max GPUVM size क्रम Cayman, SI and CI are 40 bits.
	 */
	अगर (radeon_vm_size > 1024) अणु
		dev_warn(rdev->dev, "VM size (%d) too large, max is 1TB\n",
			 radeon_vm_size);
		radeon_vm_size = 4;
	पूर्ण

	/* defines number of bits in page table versus page directory,
	 * a page is 4KB so we have 12 bits offset, minimum 9 bits in the
	 * page table and the reमुख्यing bits are in the page directory */
	अगर (radeon_vm_block_size == -1) अणु

		/* Total bits covered by PD + PTs */
		अचिन्हित bits = ilog2(radeon_vm_size) + 18;

		/* Make sure the PD is 4K in size up to 8GB address space.
		   Above that split equal between PD and PTs */
		अगर (radeon_vm_size <= 8)
			radeon_vm_block_size = bits - 9;
		अन्यथा
			radeon_vm_block_size = (bits + 3) / 2;

	पूर्ण अन्यथा अगर (radeon_vm_block_size < 9) अणु
		dev_warn(rdev->dev, "VM page table size (%d) too small\n",
			 radeon_vm_block_size);
		radeon_vm_block_size = 9;
	पूर्ण

	अगर (radeon_vm_block_size > 24 ||
	    (radeon_vm_size * 1024) < (1ull << radeon_vm_block_size)) अणु
		dev_warn(rdev->dev, "VM page table size (%d) too large\n",
			 radeon_vm_block_size);
		radeon_vm_block_size = 9;
	पूर्ण
पूर्ण

/**
 * radeon_चयनeroo_set_state - set चयनeroo state
 *
 * @pdev: pci dev poपूर्णांकer
 * @state: vga_चयनeroo state
 *
 * Callback क्रम the चयनeroo driver.  Suspends or resumes the
 * the asics beक्रमe or after it is घातered up using ACPI methods.
 */
अटल व्योम radeon_चयनeroo_set_state(काष्ठा pci_dev *pdev, क्रमागत vga_चयनeroo_state state)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);

	अगर (radeon_is_px(dev) && state == VGA_SWITCHEROO_OFF)
		वापस;

	अगर (state == VGA_SWITCHEROO_ON) अणु
		pr_info("radeon: switched on\n");
		/* करोn't suspend or resume card normally */
		dev->चयन_घातer_state = DRM_SWITCH_POWER_CHANGING;

		radeon_resume_kms(dev, true, true);

		dev->चयन_घातer_state = DRM_SWITCH_POWER_ON;
		drm_kms_helper_poll_enable(dev);
	पूर्ण अन्यथा अणु
		pr_info("radeon: switched off\n");
		drm_kms_helper_poll_disable(dev);
		dev->चयन_घातer_state = DRM_SWITCH_POWER_CHANGING;
		radeon_suspend_kms(dev, true, true, false);
		dev->चयन_घातer_state = DRM_SWITCH_POWER_OFF;
	पूर्ण
पूर्ण

/**
 * radeon_चयनeroo_can_चयन - see अगर चयनeroo state can change
 *
 * @pdev: pci dev poपूर्णांकer
 *
 * Callback क्रम the चयनeroo driver.  Check of the चयनeroo
 * state can be changed.
 * Returns true अगर the state can be changed, false अगर not.
 */
अटल bool radeon_चयनeroo_can_चयन(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);

	/*
	 * FIXME: खोलो_count is रक्षित by drm_global_mutex but that would lead to
	 * locking inversion with the driver load path. And the access here is
	 * completely racy anyway. So करोn't bother with locking क्रम now.
	 */
	वापस atomic_पढ़ो(&dev->खोलो_count) == 0;
पूर्ण

अटल स्थिर काष्ठा vga_चयनeroo_client_ops radeon_चयनeroo_ops = अणु
	.set_gpu_state = radeon_चयनeroo_set_state,
	.reprobe = शून्य,
	.can_चयन = radeon_चयनeroo_can_चयन,
पूर्ण;

/**
 * radeon_device_init - initialize the driver
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ddev: drm dev poपूर्णांकer
 * @pdev: pci dev poपूर्णांकer
 * @flags: driver flags
 *
 * Initializes the driver info and hw (all asics).
 * Returns 0 क्रम success or an error on failure.
 * Called at driver startup.
 */
पूर्णांक radeon_device_init(काष्ठा radeon_device *rdev,
		       काष्ठा drm_device *ddev,
		       काष्ठा pci_dev *pdev,
		       uपूर्णांक32_t flags)
अणु
	पूर्णांक r, i;
	पूर्णांक dma_bits;
	bool runसमय = false;

	rdev->shutकरोwn = false;
	rdev->dev = &pdev->dev;
	rdev->ddev = ddev;
	rdev->pdev = pdev;
	rdev->flags = flags;
	rdev->family = flags & RADEON_FAMILY_MASK;
	rdev->is_atom_bios = false;
	rdev->usec_समयout = RADEON_MAX_USEC_TIMEOUT;
	rdev->mc.gtt_size = 512 * 1024 * 1024;
	rdev->accel_working = false;
	/* set up ring ids */
	क्रम (i = 0; i < RADEON_NUM_RINGS; i++) अणु
		rdev->ring[i].idx = i;
	पूर्ण
	rdev->fence_context = dma_fence_context_alloc(RADEON_NUM_RINGS);

	DRM_INFO("initializing kernel modesetting (%s 0x%04X:0x%04X 0x%04X:0x%04X 0x%02X).\n",
		 radeon_family_name[rdev->family], pdev->venकरोr, pdev->device,
		 pdev->subप्रणाली_venकरोr, pdev->subप्रणाली_device, pdev->revision);

	/* mutex initialization are all करोne here so we
	 * can recall function without having locking issues */
	mutex_init(&rdev->ring_lock);
	mutex_init(&rdev->dc_hw_i2c_mutex);
	atomic_set(&rdev->ih.lock, 0);
	mutex_init(&rdev->gem.mutex);
	mutex_init(&rdev->pm.mutex);
	mutex_init(&rdev->gpu_घड़ी_mutex);
	mutex_init(&rdev->srbm_mutex);
	init_rwsem(&rdev->pm.mclk_lock);
	init_rwsem(&rdev->exclusive_lock);
	init_रुकोqueue_head(&rdev->irq.vblank_queue);
	r = radeon_gem_init(rdev);
	अगर (r)
		वापस r;

	radeon_check_arguments(rdev);
	/* Adjust VM size here.
	 * Max GPUVM size क्रम cayman+ is 40 bits.
	 */
	rdev->vm_manager.max_pfn = radeon_vm_size << 18;

	/* Set asic functions */
	r = radeon_asic_init(rdev);
	अगर (r)
		वापस r;

	/* all of the newer IGP chips have an पूर्णांकernal gart
	 * However some rs4xx report as AGP, so हटाओ that here.
	 */
	अगर ((rdev->family >= CHIP_RS400) &&
	    (rdev->flags & RADEON_IS_IGP)) अणु
		rdev->flags &= ~RADEON_IS_AGP;
	पूर्ण

	अगर (rdev->flags & RADEON_IS_AGP && radeon_agpmode == -1) अणु
		radeon_agp_disable(rdev);
	पूर्ण

	/* Set the पूर्णांकernal MC address mask
	 * This is the max address of the GPU's
	 * पूर्णांकernal address space.
	 */
	अगर (rdev->family >= CHIP_CAYMAN)
		rdev->mc.mc_mask = 0xffffffffffULL; /* 40 bit MC */
	अन्यथा अगर (rdev->family >= CHIP_CEDAR)
		rdev->mc.mc_mask = 0xfffffffffULL; /* 36 bit MC */
	अन्यथा
		rdev->mc.mc_mask = 0xffffffffULL; /* 32 bit MC */

	/* set DMA mask.
	 * PCIE - can handle 40-bits.
	 * IGP - can handle 40-bits
	 * AGP - generally dma32 is safest
	 * PCI - dma32 क्रम legacy pci gart, 40 bits on newer asics
	 */
	dma_bits = 40;
	अगर (rdev->flags & RADEON_IS_AGP)
		dma_bits = 32;
	अगर ((rdev->flags & RADEON_IS_PCI) &&
	    (rdev->family <= CHIP_RS740))
		dma_bits = 32;
#अगर_घोषित CONFIG_PPC64
	अगर (rdev->family == CHIP_CEDAR)
		dma_bits = 32;
#पूर्ण_अगर

	r = dma_set_mask_and_coherent(&rdev->pdev->dev, DMA_BIT_MASK(dma_bits));
	अगर (r) अणु
		pr_warn("radeon: No suitable DMA available\n");
		वापस r;
	पूर्ण
	rdev->need_swiotlb = drm_need_swiotlb(dma_bits);

	/* Registers mapping */
	/* TODO: block userspace mapping of io रेजिस्टर */
	spin_lock_init(&rdev->mmio_idx_lock);
	spin_lock_init(&rdev->smc_idx_lock);
	spin_lock_init(&rdev->pll_idx_lock);
	spin_lock_init(&rdev->mc_idx_lock);
	spin_lock_init(&rdev->pcie_idx_lock);
	spin_lock_init(&rdev->pciep_idx_lock);
	spin_lock_init(&rdev->pअगर_idx_lock);
	spin_lock_init(&rdev->cg_idx_lock);
	spin_lock_init(&rdev->uvd_idx_lock);
	spin_lock_init(&rdev->rcu_idx_lock);
	spin_lock_init(&rdev->didt_idx_lock);
	spin_lock_init(&rdev->end_idx_lock);
	अगर (rdev->family >= CHIP_BONAIRE) अणु
		rdev->rmmio_base = pci_resource_start(rdev->pdev, 5);
		rdev->rmmio_size = pci_resource_len(rdev->pdev, 5);
	पूर्ण अन्यथा अणु
		rdev->rmmio_base = pci_resource_start(rdev->pdev, 2);
		rdev->rmmio_size = pci_resource_len(rdev->pdev, 2);
	पूर्ण
	rdev->rmmio = ioremap(rdev->rmmio_base, rdev->rmmio_size);
	अगर (rdev->rmmio == शून्य)
		वापस -ENOMEM;

	/* करोorbell bar mapping */
	अगर (rdev->family >= CHIP_BONAIRE)
		radeon_करोorbell_init(rdev);

	/* io port mapping */
	क्रम (i = 0; i < DEVICE_COUNT_RESOURCE; i++) अणु
		अगर (pci_resource_flags(rdev->pdev, i) & IORESOURCE_IO) अणु
			rdev->rio_mem_size = pci_resource_len(rdev->pdev, i);
			rdev->rio_mem = pci_iomap(rdev->pdev, i, rdev->rio_mem_size);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (rdev->rio_mem == शून्य)
		DRM_ERROR("Unable to find PCI I/O BAR\n");

	अगर (rdev->flags & RADEON_IS_PX)
		radeon_device_handle_px_quirks(rdev);

	/* अगर we have > 1 VGA cards, then disable the radeon VGA resources */
	/* this will fail क्रम cards that aren't VGA class devices, just
	 * ignore it */
	vga_client_रेजिस्टर(rdev->pdev, rdev, शून्य, radeon_vga_set_decode);

	अगर (rdev->flags & RADEON_IS_PX)
		runसमय = true;
	अगर (!pci_is_thunderbolt_attached(rdev->pdev))
		vga_चयनeroo_रेजिस्टर_client(rdev->pdev,
					       &radeon_चयनeroo_ops, runसमय);
	अगर (runसमय)
		vga_चयनeroo_init_करोमुख्य_pm_ops(rdev->dev, &rdev->vga_pm_करोमुख्य);

	r = radeon_init(rdev);
	अगर (r)
		जाओ failed;

	radeon_gem_debugfs_init(rdev);
	radeon_mst_debugfs_init(rdev);

	अगर (rdev->flags & RADEON_IS_AGP && !rdev->accel_working) अणु
		/* Acceleration not working on AGP card try again
		 * with fallback to PCI or PCIE GART
		 */
		radeon_asic_reset(rdev);
		radeon_fini(rdev);
		radeon_agp_disable(rdev);
		r = radeon_init(rdev);
		अगर (r)
			जाओ failed;
	पूर्ण

	r = radeon_ib_ring_tests(rdev);
	अगर (r)
		DRM_ERROR("ib ring test failed (%d).\n", r);

	/*
	 * Turks/Thames GPU will मुक्तze whole laptop अगर DPM is not restarted
	 * after the CP ring have chew one packet at least. Hence here we stop
	 * and restart DPM after the radeon_ib_ring_tests().
	 */
	अगर (rdev->pm.dpm_enabled &&
	    (rdev->pm.pm_method == PM_METHOD_DPM) &&
	    (rdev->family == CHIP_TURKS) &&
	    (rdev->flags & RADEON_IS_MOBILITY)) अणु
		mutex_lock(&rdev->pm.mutex);
		radeon_dpm_disable(rdev);
		radeon_dpm_enable(rdev);
		mutex_unlock(&rdev->pm.mutex);
	पूर्ण

	अगर ((radeon_testing & 1)) अणु
		अगर (rdev->accel_working)
			radeon_test_moves(rdev);
		अन्यथा
			DRM_INFO("radeon: acceleration disabled, skipping move tests\n");
	पूर्ण
	अगर ((radeon_testing & 2)) अणु
		अगर (rdev->accel_working)
			radeon_test_syncing(rdev);
		अन्यथा
			DRM_INFO("radeon: acceleration disabled, skipping sync tests\n");
	पूर्ण
	अगर (radeon_benchmarking) अणु
		अगर (rdev->accel_working)
			radeon_benchmark(rdev, radeon_benchmarking);
		अन्यथा
			DRM_INFO("radeon: acceleration disabled, skipping benchmarks\n");
	पूर्ण
	वापस 0;

failed:
	/* balance pm_runसमय_get_sync() in radeon_driver_unload_kms() */
	अगर (radeon_is_px(ddev))
		pm_runसमय_put_noidle(ddev->dev);
	अगर (runसमय)
		vga_चयनeroo_fini_करोमुख्य_pm_ops(rdev->dev);
	वापस r;
पूर्ण

/**
 * radeon_device_fini - tear करोwn the driver
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Tear करोwn the driver info (all asics).
 * Called at driver shutकरोwn.
 */
व्योम radeon_device_fini(काष्ठा radeon_device *rdev)
अणु
	DRM_INFO("radeon: finishing device.\n");
	rdev->shutकरोwn = true;
	/* evict vram memory */
	radeon_bo_evict_vram(rdev);
	radeon_fini(rdev);
	अगर (!pci_is_thunderbolt_attached(rdev->pdev))
		vga_चयनeroo_unरेजिस्टर_client(rdev->pdev);
	अगर (rdev->flags & RADEON_IS_PX)
		vga_चयनeroo_fini_करोमुख्य_pm_ops(rdev->dev);
	vga_client_रेजिस्टर(rdev->pdev, शून्य, शून्य, शून्य);
	अगर (rdev->rio_mem)
		pci_iounmap(rdev->pdev, rdev->rio_mem);
	rdev->rio_mem = शून्य;
	iounmap(rdev->rmmio);
	rdev->rmmio = शून्य;
	अगर (rdev->family >= CHIP_BONAIRE)
		radeon_करोorbell_fini(rdev);
पूर्ण


/*
 * Suspend & resume.
 */
/*
 * radeon_suspend_kms - initiate device suspend
 *
 * Puts the hw in the suspend state (all asics).
 * Returns 0 क्रम success or an error on failure.
 * Called at driver suspend.
 */
पूर्णांक radeon_suspend_kms(काष्ठा drm_device *dev, bool suspend,
		       bool fbcon, bool मुक्तze)
अणु
	काष्ठा radeon_device *rdev;
	काष्ठा pci_dev *pdev;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_connector *connector;
	पूर्णांक i, r;

	अगर (dev == शून्य || dev->dev_निजी == शून्य) अणु
		वापस -ENODEV;
	पूर्ण

	rdev = dev->dev_निजी;
	pdev = to_pci_dev(dev->dev);

	अगर (dev->चयन_घातer_state == DRM_SWITCH_POWER_OFF)
		वापस 0;

	drm_kms_helper_poll_disable(dev);

	drm_modeset_lock_all(dev);
	/* turn off display hw */
	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		drm_helper_connector_dpms(connector, DRM_MODE_DPMS_OFF);
	पूर्ण
	drm_modeset_unlock_all(dev);

	/* unpin the front buffers and cursors */
	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
		काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
		काष्ठा drm_framebuffer *fb = crtc->primary->fb;
		काष्ठा radeon_bo *robj;

		अगर (radeon_crtc->cursor_bo) अणु
			काष्ठा radeon_bo *robj = gem_to_radeon_bo(radeon_crtc->cursor_bo);
			r = radeon_bo_reserve(robj, false);
			अगर (r == 0) अणु
				radeon_bo_unpin(robj);
				radeon_bo_unreserve(robj);
			पूर्ण
		पूर्ण

		अगर (fb == शून्य || fb->obj[0] == शून्य) अणु
			जारी;
		पूर्ण
		robj = gem_to_radeon_bo(fb->obj[0]);
		/* करोn't unpin kernel fb objects */
		अगर (!radeon_fbdev_robj_is_fb(rdev, robj)) अणु
			r = radeon_bo_reserve(robj, false);
			अगर (r == 0) अणु
				radeon_bo_unpin(robj);
				radeon_bo_unreserve(robj);
			पूर्ण
		पूर्ण
	पूर्ण
	/* evict vram memory */
	radeon_bo_evict_vram(rdev);

	/* रुको क्रम gpu to finish processing current batch */
	क्रम (i = 0; i < RADEON_NUM_RINGS; i++) अणु
		r = radeon_fence_रुको_empty(rdev, i);
		अगर (r) अणु
			/* delay GPU reset to resume */
			radeon_fence_driver_क्रमce_completion(rdev, i);
		पूर्ण
	पूर्ण

	radeon_save_bios_scratch_regs(rdev);

	radeon_suspend(rdev);
	radeon_hpd_fini(rdev);
	/* evict reमुख्यing vram memory
	 * This second call to evict vram is to evict the gart page table
	 * using the CPU.
	 */
	radeon_bo_evict_vram(rdev);

	radeon_agp_suspend(rdev);

	pci_save_state(pdev);
	अगर (मुक्तze && rdev->family >= CHIP_CEDAR && !(rdev->flags & RADEON_IS_IGP)) अणु
		rdev->asic->asic_reset(rdev, true);
		pci_restore_state(pdev);
	पूर्ण अन्यथा अगर (suspend) अणु
		/* Shut करोwn the device */
		pci_disable_device(pdev);
		pci_set_घातer_state(pdev, PCI_D3hot);
	पूर्ण

	अगर (fbcon) अणु
		console_lock();
		radeon_fbdev_set_suspend(rdev, 1);
		console_unlock();
	पूर्ण
	वापस 0;
पूर्ण

/*
 * radeon_resume_kms - initiate device resume
 *
 * Bring the hw back to operating state (all asics).
 * Returns 0 क्रम success or an error on failure.
 * Called at driver resume.
 */
पूर्णांक radeon_resume_kms(काष्ठा drm_device *dev, bool resume, bool fbcon)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	काष्ठा drm_crtc *crtc;
	पूर्णांक r;

	अगर (dev->चयन_घातer_state == DRM_SWITCH_POWER_OFF)
		वापस 0;

	अगर (fbcon) अणु
		console_lock();
	पूर्ण
	अगर (resume) अणु
		pci_set_घातer_state(pdev, PCI_D0);
		pci_restore_state(pdev);
		अगर (pci_enable_device(pdev)) अणु
			अगर (fbcon)
				console_unlock();
			वापस -1;
		पूर्ण
	पूर्ण
	/* resume AGP अगर in use */
	radeon_agp_resume(rdev);
	radeon_resume(rdev);

	r = radeon_ib_ring_tests(rdev);
	अगर (r)
		DRM_ERROR("ib ring test failed (%d).\n", r);

	अगर ((rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled) अणु
		/* करो dpm late init */
		r = radeon_pm_late_init(rdev);
		अगर (r) अणु
			rdev->pm.dpm_enabled = false;
			DRM_ERROR("radeon_pm_late_init failed, disabling dpm\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		/* resume old pm late */
		radeon_pm_resume(rdev);
	पूर्ण

	radeon_restore_bios_scratch_regs(rdev);

	/* pin cursors */
	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
		काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);

		अगर (radeon_crtc->cursor_bo) अणु
			काष्ठा radeon_bo *robj = gem_to_radeon_bo(radeon_crtc->cursor_bo);
			r = radeon_bo_reserve(robj, false);
			अगर (r == 0) अणु
				/* Only 27 bit offset क्रम legacy cursor */
				r = radeon_bo_pin_restricted(robj,
							     RADEON_GEM_DOMAIN_VRAM,
							     ASIC_IS_AVIVO(rdev) ?
							     0 : 1 << 27,
							     &radeon_crtc->cursor_addr);
				अगर (r != 0)
					DRM_ERROR("Failed to pin cursor BO (%d)\n", r);
				radeon_bo_unreserve(robj);
			पूर्ण
		पूर्ण
	पूर्ण

	/* init dig PHYs, disp eng pll */
	अगर (rdev->is_atom_bios) अणु
		radeon_atom_encoder_init(rdev);
		radeon_atom_disp_eng_pll_init(rdev);
		/* turn on the BL */
		अगर (rdev->mode_info.bl_encoder) अणु
			u8 bl_level = radeon_get_backlight_level(rdev,
								 rdev->mode_info.bl_encoder);
			radeon_set_backlight_level(rdev, rdev->mode_info.bl_encoder,
						   bl_level);
		पूर्ण
	पूर्ण
	/* reset hpd state */
	radeon_hpd_init(rdev);
	/* blat the mode back in */
	अगर (fbcon) अणु
		drm_helper_resume_क्रमce_mode(dev);
		/* turn on display hw */
		drm_modeset_lock_all(dev);
		list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
			drm_helper_connector_dpms(connector, DRM_MODE_DPMS_ON);
		पूर्ण
		drm_modeset_unlock_all(dev);
	पूर्ण

	drm_kms_helper_poll_enable(dev);

	/* set the घातer state here in हाल we are a PX प्रणाली or headless */
	अगर ((rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled)
		radeon_pm_compute_घड़ीs(rdev);

	अगर (fbcon) अणु
		radeon_fbdev_set_suspend(rdev, 0);
		console_unlock();
	पूर्ण

	वापस 0;
पूर्ण

/**
 * radeon_gpu_reset - reset the asic
 *
 * @rdev: radeon device poपूर्णांकer
 *
 * Attempt the reset the GPU अगर it has hung (all asics).
 * Returns 0 क्रम success or an error on failure.
 */
पूर्णांक radeon_gpu_reset(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित ring_sizes[RADEON_NUM_RINGS];
	uपूर्णांक32_t *ring_data[RADEON_NUM_RINGS];

	bool saved = false;

	पूर्णांक i, r;
	पूर्णांक resched;

	करोwn_ग_लिखो(&rdev->exclusive_lock);

	अगर (!rdev->needs_reset) अणु
		up_ग_लिखो(&rdev->exclusive_lock);
		वापस 0;
	पूर्ण

	atomic_inc(&rdev->gpu_reset_counter);

	radeon_save_bios_scratch_regs(rdev);
	/* block TTM */
	resched = tपंचांग_bo_lock_delayed_workqueue(&rdev->mman.bdev);
	radeon_suspend(rdev);
	radeon_hpd_fini(rdev);

	क्रम (i = 0; i < RADEON_NUM_RINGS; ++i) अणु
		ring_sizes[i] = radeon_ring_backup(rdev, &rdev->ring[i],
						   &ring_data[i]);
		अगर (ring_sizes[i]) अणु
			saved = true;
			dev_info(rdev->dev, "Saved %d dwords of commands "
				 "on ring %d.\n", ring_sizes[i], i);
		पूर्ण
	पूर्ण

	r = radeon_asic_reset(rdev);
	अगर (!r) अणु
		dev_info(rdev->dev, "GPU reset succeeded, trying to resume\n");
		radeon_resume(rdev);
	पूर्ण

	radeon_restore_bios_scratch_regs(rdev);

	क्रम (i = 0; i < RADEON_NUM_RINGS; ++i) अणु
		अगर (!r && ring_data[i]) अणु
			radeon_ring_restore(rdev, &rdev->ring[i],
					    ring_sizes[i], ring_data[i]);
		पूर्ण अन्यथा अणु
			radeon_fence_driver_क्रमce_completion(rdev, i);
			kमुक्त(ring_data[i]);
		पूर्ण
	पूर्ण

	अगर ((rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled) अणु
		/* करो dpm late init */
		r = radeon_pm_late_init(rdev);
		अगर (r) अणु
			rdev->pm.dpm_enabled = false;
			DRM_ERROR("radeon_pm_late_init failed, disabling dpm\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		/* resume old pm late */
		radeon_pm_resume(rdev);
	पूर्ण

	/* init dig PHYs, disp eng pll */
	अगर (rdev->is_atom_bios) अणु
		radeon_atom_encoder_init(rdev);
		radeon_atom_disp_eng_pll_init(rdev);
		/* turn on the BL */
		अगर (rdev->mode_info.bl_encoder) अणु
			u8 bl_level = radeon_get_backlight_level(rdev,
								 rdev->mode_info.bl_encoder);
			radeon_set_backlight_level(rdev, rdev->mode_info.bl_encoder,
						   bl_level);
		पूर्ण
	पूर्ण
	/* reset hpd state */
	radeon_hpd_init(rdev);

	tपंचांग_bo_unlock_delayed_workqueue(&rdev->mman.bdev, resched);

	rdev->in_reset = true;
	rdev->needs_reset = false;

	करोwngrade_ग_लिखो(&rdev->exclusive_lock);

	drm_helper_resume_क्रमce_mode(rdev->ddev);

	/* set the घातer state here in हाल we are a PX प्रणाली or headless */
	अगर ((rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled)
		radeon_pm_compute_घड़ीs(rdev);

	अगर (!r) अणु
		r = radeon_ib_ring_tests(rdev);
		अगर (r && saved)
			r = -EAGAIN;
	पूर्ण अन्यथा अणु
		/* bad news, how to tell it to userspace ? */
		dev_info(rdev->dev, "GPU reset failed\n");
	पूर्ण

	rdev->needs_reset = r == -EAGAIN;
	rdev->in_reset = false;

	up_पढ़ो(&rdev->exclusive_lock);
	वापस r;
पूर्ण
