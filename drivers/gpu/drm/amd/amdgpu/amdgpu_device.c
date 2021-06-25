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
#समावेश <linux/घातer_supply.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/console.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/amdgpu_drm.h>
#समावेश <linux/vgaarb.h>
#समावेश <linux/vga_चयनeroo.h>
#समावेश <linux/efi.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_trace.h"
#समावेश "amdgpu_i2c.h"
#समावेश "atom.h"
#समावेश "amdgpu_atombios.h"
#समावेश "amdgpu_atomfirmware.h"
#समावेश "amd_pcie.h"
#अगर_घोषित CONFIG_DRM_AMDGPU_SI
#समावेश "si.h"
#पूर्ण_अगर
#अगर_घोषित CONFIG_DRM_AMDGPU_CIK
#समावेश "cik.h"
#पूर्ण_अगर
#समावेश "vi.h"
#समावेश "soc15.h"
#समावेश "nv.h"
#समावेश "bif/bif_4_1_d.h"
#समावेश <linux/pci.h>
#समावेश <linux/firmware.h>
#समावेश "amdgpu_vf_error.h"

#समावेश "amdgpu_amdkfd.h"
#समावेश "amdgpu_pm.h"

#समावेश "amdgpu_xgmi.h"
#समावेश "amdgpu_ras.h"
#समावेश "amdgpu_pmu.h"
#समावेश "amdgpu_fru_eeprom.h"
#समावेश "amdgpu_reset.h"

#समावेश <linux/suspend.h>
#समावेश <drm/task_barrier.h>
#समावेश <linux/pm_runसमय.स>

MODULE_FIRMWARE("amdgpu/vega10_gpu_info.bin");
MODULE_FIRMWARE("amdgpu/vega12_gpu_info.bin");
MODULE_FIRMWARE("amdgpu/raven_gpu_info.bin");
MODULE_FIRMWARE("amdgpu/picasso_gpu_info.bin");
MODULE_FIRMWARE("amdgpu/raven2_gpu_info.bin");
MODULE_FIRMWARE("amdgpu/arcturus_gpu_info.bin");
MODULE_FIRMWARE("amdgpu/renoir_gpu_info.bin");
MODULE_FIRMWARE("amdgpu/navi10_gpu_info.bin");
MODULE_FIRMWARE("amdgpu/navi14_gpu_info.bin");
MODULE_FIRMWARE("amdgpu/navi12_gpu_info.bin");
MODULE_FIRMWARE("amdgpu/vangogh_gpu_info.bin");

#घोषणा AMDGPU_RESUME_MS		2000

स्थिर अक्षर *amdgpu_asic_name[] = अणु
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
	"TOPAZ",
	"TONGA",
	"FIJI",
	"CARRIZO",
	"STONEY",
	"POLARIS10",
	"POLARIS11",
	"POLARIS12",
	"VEGAM",
	"VEGA10",
	"VEGA12",
	"VEGA20",
	"RAVEN",
	"ARCTURUS",
	"RENOIR",
	"ALDEBARAN",
	"NAVI10",
	"NAVI14",
	"NAVI12",
	"SIENNA_CICHLID",
	"NAVY_FLOUNDER",
	"VANGOGH",
	"DIMGREY_CAVEFISH",
	"LAST",
पूर्ण;

/**
 * DOC: pcie_replay_count
 *
 * The amdgpu driver provides a sysfs API क्रम reporting the total number
 * of PCIe replays (NAKs)
 * The file pcie_replay_count is used क्रम this and वापसs the total
 * number of replays as a sum of the NAKs generated and NAKs received
 */

अटल sमाप_प्रकार amdgpu_device_get_pcie_replay_count(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	uपूर्णांक64_t cnt = amdgpu_asic_get_pcie_replay_count(adev);

	वापस sysfs_emit(buf, "%llu\n", cnt);
पूर्ण

अटल DEVICE_ATTR(pcie_replay_count, S_IRUGO,
		amdgpu_device_get_pcie_replay_count, शून्य);

अटल व्योम amdgpu_device_get_pcie_info(काष्ठा amdgpu_device *adev);

/**
 * DOC: product_name
 *
 * The amdgpu driver provides a sysfs API क्रम reporting the product name
 * क्रम the device
 * The file serial_number is used क्रम this and वापसs the product name
 * as वापसed from the FRU.
 * NOTE: This is only available क्रम certain server cards
 */

अटल sमाप_प्रकार amdgpu_device_get_product_name(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);

	वापस sysfs_emit(buf, "%s\n", adev->product_name);
पूर्ण

अटल DEVICE_ATTR(product_name, S_IRUGO,
		amdgpu_device_get_product_name, शून्य);

/**
 * DOC: product_number
 *
 * The amdgpu driver provides a sysfs API क्रम reporting the part number
 * क्रम the device
 * The file serial_number is used क्रम this and वापसs the part number
 * as वापसed from the FRU.
 * NOTE: This is only available क्रम certain server cards
 */

अटल sमाप_प्रकार amdgpu_device_get_product_number(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);

	वापस sysfs_emit(buf, "%s\n", adev->product_number);
पूर्ण

अटल DEVICE_ATTR(product_number, S_IRUGO,
		amdgpu_device_get_product_number, शून्य);

/**
 * DOC: serial_number
 *
 * The amdgpu driver provides a sysfs API क्रम reporting the serial number
 * क्रम the device
 * The file serial_number is used क्रम this and वापसs the serial number
 * as वापसed from the FRU.
 * NOTE: This is only available क्रम certain server cards
 */

अटल sमाप_प्रकार amdgpu_device_get_serial_number(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);

	वापस sysfs_emit(buf, "%s\n", adev->serial);
पूर्ण

अटल DEVICE_ATTR(serial_number, S_IRUGO,
		amdgpu_device_get_serial_number, शून्य);

/**
 * amdgpu_device_supports_px - Is the device a dGPU with ATPX घातer control
 *
 * @dev: drm_device poपूर्णांकer
 *
 * Returns true अगर the device is a dGPU with ATPX घातer control,
 * otherwise वापस false.
 */
bool amdgpu_device_supports_px(काष्ठा drm_device *dev)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);

	अगर ((adev->flags & AMD_IS_PX) && !amdgpu_is_atpx_hybrid())
		वापस true;
	वापस false;
पूर्ण

/**
 * amdgpu_device_supports_boco - Is the device a dGPU with ACPI घातer resources
 *
 * @dev: drm_device poपूर्णांकer
 *
 * Returns true अगर the device is a dGPU with ACPI घातer control,
 * otherwise वापस false.
 */
bool amdgpu_device_supports_boco(काष्ठा drm_device *dev)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);

	अगर (adev->has_pr3 ||
	    ((adev->flags & AMD_IS_PX) && amdgpu_is_atpx_hybrid()))
		वापस true;
	वापस false;
पूर्ण

/**
 * amdgpu_device_supports_baco - Does the device support BACO
 *
 * @dev: drm_device poपूर्णांकer
 *
 * Returns true अगर the device supporte BACO,
 * otherwise वापस false.
 */
bool amdgpu_device_supports_baco(काष्ठा drm_device *dev)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);

	वापस amdgpu_asic_supports_baco(adev);
पूर्ण

/*
 * VRAM access helper functions
 */

/**
 * amdgpu_device_vram_access - पढ़ो/ग_लिखो a buffer in vram
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @pos: offset of the buffer in vram
 * @buf: भव address of the buffer in प्रणाली memory
 * @size: पढ़ो/ग_लिखो size, माप(@buf) must > @size
 * @ग_लिखो: true - ग_लिखो to vram, otherwise - पढ़ो from vram
 */
व्योम amdgpu_device_vram_access(काष्ठा amdgpu_device *adev, loff_t pos,
			       uपूर्णांक32_t *buf, माप_प्रकार size, bool ग_लिखो)
अणु
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t hi = ~0;
	uपूर्णांक64_t last;


#अगर_घोषित CONFIG_64BIT
	last = min(pos + size, adev->gmc.visible_vram_size);
	अगर (last > pos) अणु
		व्योम __iomem *addr = adev->mman.aper_base_kaddr + pos;
		माप_प्रकार count = last - pos;

		अगर (ग_लिखो) अणु
			स_नकल_toio(addr, buf, count);
			mb();
			amdgpu_asic_flush_hdp(adev, शून्य);
		पूर्ण अन्यथा अणु
			amdgpu_asic_invalidate_hdp(adev, शून्य);
			mb();
			स_नकल_fromio(buf, addr, count);
		पूर्ण

		अगर (count == size)
			वापस;

		pos += count;
		buf += count / 4;
		size -= count;
	पूर्ण
#पूर्ण_अगर

	spin_lock_irqsave(&adev->mmio_idx_lock, flags);
	क्रम (last = pos + size; pos < last; pos += 4) अणु
		uपूर्णांक32_t पंचांगp = pos >> 31;

		WREG32_NO_KIQ(mmMM_INDEX, ((uपूर्णांक32_t)pos) | 0x80000000);
		अगर (पंचांगp != hi) अणु
			WREG32_NO_KIQ(mmMM_INDEX_HI, पंचांगp);
			hi = पंचांगp;
		पूर्ण
		अगर (ग_लिखो)
			WREG32_NO_KIQ(mmMM_DATA, *buf++);
		अन्यथा
			*buf++ = RREG32_NO_KIQ(mmMM_DATA);
	पूर्ण
	spin_unlock_irqrestore(&adev->mmio_idx_lock, flags);
पूर्ण

/*
 * रेजिस्टर access helper functions.
 */

/* Check अगर hw access should be skipped because of hotplug or device error */
bool amdgpu_device_skip_hw_access(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->in_pci_err_recovery)
		वापस true;

#अगर_घोषित CONFIG_LOCKDEP
	/*
	 * This is a bit complicated to understand, so worth a comment. What we निश्चित
	 * here is that the GPU reset is not running on another thपढ़ो in parallel.
	 *
	 * For this we trylock the पढ़ो side of the reset semaphore, अगर that succeeds
	 * we know that the reset is not running in paralell.
	 *
	 * If the trylock fails we निश्चित that we are either alपढ़ोy holding the पढ़ो
	 * side of the lock or are the reset thपढ़ो itself and hold the ग_लिखो side of
	 * the lock.
	 */
	अगर (in_task()) अणु
		अगर (करोwn_पढ़ो_trylock(&adev->reset_sem))
			up_पढ़ो(&adev->reset_sem);
		अन्यथा
			lockdep_निश्चित_held(&adev->reset_sem);
	पूर्ण
#पूर्ण_अगर
	वापस false;
पूर्ण

/**
 * amdgpu_device_rreg - पढ़ो a memory mapped IO or indirect रेजिस्टर
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @reg: dword aligned रेजिस्टर offset
 * @acc_flags: access flags which require special behavior
 *
 * Returns the 32 bit value from the offset specअगरied.
 */
uपूर्णांक32_t amdgpu_device_rreg(काष्ठा amdgpu_device *adev,
			    uपूर्णांक32_t reg, uपूर्णांक32_t acc_flags)
अणु
	uपूर्णांक32_t ret;

	अगर (amdgpu_device_skip_hw_access(adev))
		वापस 0;

	अगर ((reg * 4) < adev->rmmio_size) अणु
		अगर (!(acc_flags & AMDGPU_REGS_NO_KIQ) &&
		    amdgpu_sriov_runसमय(adev) &&
		    करोwn_पढ़ो_trylock(&adev->reset_sem)) अणु
			ret = amdgpu_kiq_rreg(adev, reg);
			up_पढ़ो(&adev->reset_sem);
		पूर्ण अन्यथा अणु
			ret = पढ़ोl(((व्योम __iomem *)adev->rmmio) + (reg * 4));
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = adev->pcie_rreg(adev, reg * 4);
	पूर्ण

	trace_amdgpu_device_rreg(adev->pdev->device, reg, ret);

	वापस ret;
पूर्ण

/*
 * MMIO रेजिस्टर पढ़ो with bytes helper functions
 * @offset:bytes offset from MMIO start
 *
*/

/**
 * amdgpu_mm_rreg8 - पढ़ो a memory mapped IO रेजिस्टर
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @offset: byte aligned रेजिस्टर offset
 *
 * Returns the 8 bit value from the offset specअगरied.
 */
uपूर्णांक8_t amdgpu_mm_rreg8(काष्ठा amdgpu_device *adev, uपूर्णांक32_t offset)
अणु
	अगर (amdgpu_device_skip_hw_access(adev))
		वापस 0;

	अगर (offset < adev->rmmio_size)
		वापस (पढ़ोb(adev->rmmio + offset));
	BUG();
पूर्ण

/*
 * MMIO रेजिस्टर ग_लिखो with bytes helper functions
 * @offset:bytes offset from MMIO start
 * @value: the value want to be written to the रेजिस्टर
 *
*/
/**
 * amdgpu_mm_wreg8 - पढ़ो a memory mapped IO रेजिस्टर
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @offset: byte aligned रेजिस्टर offset
 * @value: 8 bit value to ग_लिखो
 *
 * Writes the value specअगरied to the offset specअगरied.
 */
व्योम amdgpu_mm_wreg8(काष्ठा amdgpu_device *adev, uपूर्णांक32_t offset, uपूर्णांक8_t value)
अणु
	अगर (amdgpu_device_skip_hw_access(adev))
		वापस;

	अगर (offset < adev->rmmio_size)
		ग_लिखोb(value, adev->rmmio + offset);
	अन्यथा
		BUG();
पूर्ण

/**
 * amdgpu_device_wreg - ग_लिखो to a memory mapped IO or indirect रेजिस्टर
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @reg: dword aligned रेजिस्टर offset
 * @v: 32 bit value to ग_लिखो to the रेजिस्टर
 * @acc_flags: access flags which require special behavior
 *
 * Writes the value specअगरied to the offset specअगरied.
 */
व्योम amdgpu_device_wreg(काष्ठा amdgpu_device *adev,
			uपूर्णांक32_t reg, uपूर्णांक32_t v,
			uपूर्णांक32_t acc_flags)
अणु
	अगर (amdgpu_device_skip_hw_access(adev))
		वापस;

	अगर ((reg * 4) < adev->rmmio_size) अणु
		अगर (!(acc_flags & AMDGPU_REGS_NO_KIQ) &&
		    amdgpu_sriov_runसमय(adev) &&
		    करोwn_पढ़ो_trylock(&adev->reset_sem)) अणु
			amdgpu_kiq_wreg(adev, reg, v);
			up_पढ़ो(&adev->reset_sem);
		पूर्ण अन्यथा अणु
			ग_लिखोl(v, ((व्योम __iomem *)adev->rmmio) + (reg * 4));
		पूर्ण
	पूर्ण अन्यथा अणु
		adev->pcie_wreg(adev, reg * 4, v);
	पूर्ण

	trace_amdgpu_device_wreg(adev->pdev->device, reg, v);
पूर्ण

/*
 * amdgpu_mm_wreg_mmio_rlc -  ग_लिखो रेजिस्टर either with mmio or with RLC path अगर in range
 *
 * this function is invoked only the debugfs रेजिस्टर access
 * */
व्योम amdgpu_mm_wreg_mmio_rlc(काष्ठा amdgpu_device *adev,
			     uपूर्णांक32_t reg, uपूर्णांक32_t v)
अणु
	अगर (amdgpu_device_skip_hw_access(adev))
		वापस;

	अगर (amdgpu_sriov_fullaccess(adev) &&
	    adev->gfx.rlc.funcs &&
	    adev->gfx.rlc.funcs->is_rlcg_access_range) अणु
		अगर (adev->gfx.rlc.funcs->is_rlcg_access_range(adev, reg))
			वापस adev->gfx.rlc.funcs->rlcg_wreg(adev, reg, v, 0);
	पूर्ण अन्यथा अणु
		ग_लिखोl(v, ((व्योम __iomem *)adev->rmmio) + (reg * 4));
	पूर्ण
पूर्ण

/**
 * amdgpu_mm_rकरोorbell - पढ़ो a करोorbell dword
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @index: करोorbell index
 *
 * Returns the value in the करोorbell aperture at the
 * requested करोorbell index (CIK).
 */
u32 amdgpu_mm_rकरोorbell(काष्ठा amdgpu_device *adev, u32 index)
अणु
	अगर (amdgpu_device_skip_hw_access(adev))
		वापस 0;

	अगर (index < adev->करोorbell.num_करोorbells) अणु
		वापस पढ़ोl(adev->करोorbell.ptr + index);
	पूर्ण अन्यथा अणु
		DRM_ERROR("reading beyond doorbell aperture: 0x%08x!\n", index);
		वापस 0;
	पूर्ण
पूर्ण

/**
 * amdgpu_mm_wकरोorbell - ग_लिखो a करोorbell dword
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @index: करोorbell index
 * @v: value to ग_लिखो
 *
 * Writes @v to the करोorbell aperture at the
 * requested करोorbell index (CIK).
 */
व्योम amdgpu_mm_wकरोorbell(काष्ठा amdgpu_device *adev, u32 index, u32 v)
अणु
	अगर (amdgpu_device_skip_hw_access(adev))
		वापस;

	अगर (index < adev->करोorbell.num_करोorbells) अणु
		ग_लिखोl(v, adev->करोorbell.ptr + index);
	पूर्ण अन्यथा अणु
		DRM_ERROR("writing beyond doorbell aperture: 0x%08x!\n", index);
	पूर्ण
पूर्ण

/**
 * amdgpu_mm_rकरोorbell64 - पढ़ो a करोorbell Qword
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @index: करोorbell index
 *
 * Returns the value in the करोorbell aperture at the
 * requested करोorbell index (VEGA10+).
 */
u64 amdgpu_mm_rकरोorbell64(काष्ठा amdgpu_device *adev, u32 index)
अणु
	अगर (amdgpu_device_skip_hw_access(adev))
		वापस 0;

	अगर (index < adev->करोorbell.num_करोorbells) अणु
		वापस atomic64_पढ़ो((atomic64_t *)(adev->करोorbell.ptr + index));
	पूर्ण अन्यथा अणु
		DRM_ERROR("reading beyond doorbell aperture: 0x%08x!\n", index);
		वापस 0;
	पूर्ण
पूर्ण

/**
 * amdgpu_mm_wकरोorbell64 - ग_लिखो a करोorbell Qword
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @index: करोorbell index
 * @v: value to ग_लिखो
 *
 * Writes @v to the करोorbell aperture at the
 * requested करोorbell index (VEGA10+).
 */
व्योम amdgpu_mm_wकरोorbell64(काष्ठा amdgpu_device *adev, u32 index, u64 v)
अणु
	अगर (amdgpu_device_skip_hw_access(adev))
		वापस;

	अगर (index < adev->करोorbell.num_करोorbells) अणु
		atomic64_set((atomic64_t *)(adev->करोorbell.ptr + index), v);
	पूर्ण अन्यथा अणु
		DRM_ERROR("writing beyond doorbell aperture: 0x%08x!\n", index);
	पूर्ण
पूर्ण

/**
 * amdgpu_device_indirect_rreg - पढ़ो an indirect रेजिस्टर
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @pcie_index: mmio रेजिस्टर offset
 * @pcie_data: mmio रेजिस्टर offset
 * @reg_addr: indirect रेजिस्टर address to पढ़ो from
 *
 * Returns the value of indirect रेजिस्टर @reg_addr
 */
u32 amdgpu_device_indirect_rreg(काष्ठा amdgpu_device *adev,
				u32 pcie_index, u32 pcie_data,
				u32 reg_addr)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;
	व्योम __iomem *pcie_index_offset;
	व्योम __iomem *pcie_data_offset;

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	pcie_index_offset = (व्योम __iomem *)adev->rmmio + pcie_index * 4;
	pcie_data_offset = (व्योम __iomem *)adev->rmmio + pcie_data * 4;

	ग_लिखोl(reg_addr, pcie_index_offset);
	पढ़ोl(pcie_index_offset);
	r = पढ़ोl(pcie_data_offset);
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);

	वापस r;
पूर्ण

/**
 * amdgpu_device_indirect_rreg64 - पढ़ो a 64bits indirect रेजिस्टर
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @pcie_index: mmio रेजिस्टर offset
 * @pcie_data: mmio रेजिस्टर offset
 * @reg_addr: indirect रेजिस्टर address to पढ़ो from
 *
 * Returns the value of indirect रेजिस्टर @reg_addr
 */
u64 amdgpu_device_indirect_rreg64(काष्ठा amdgpu_device *adev,
				  u32 pcie_index, u32 pcie_data,
				  u32 reg_addr)
अणु
	अचिन्हित दीर्घ flags;
	u64 r;
	व्योम __iomem *pcie_index_offset;
	व्योम __iomem *pcie_data_offset;

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	pcie_index_offset = (व्योम __iomem *)adev->rmmio + pcie_index * 4;
	pcie_data_offset = (व्योम __iomem *)adev->rmmio + pcie_data * 4;

	/* पढ़ो low 32 bits */
	ग_लिखोl(reg_addr, pcie_index_offset);
	पढ़ोl(pcie_index_offset);
	r = पढ़ोl(pcie_data_offset);
	/* पढ़ो high 32 bits */
	ग_लिखोl(reg_addr + 4, pcie_index_offset);
	पढ़ोl(pcie_index_offset);
	r |= ((u64)पढ़ोl(pcie_data_offset) << 32);
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);

	वापस r;
पूर्ण

/**
 * amdgpu_device_indirect_wreg - ग_लिखो an indirect रेजिस्टर address
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @pcie_index: mmio रेजिस्टर offset
 * @pcie_data: mmio रेजिस्टर offset
 * @reg_addr: indirect रेजिस्टर offset
 * @reg_data: indirect रेजिस्टर data
 *
 */
व्योम amdgpu_device_indirect_wreg(काष्ठा amdgpu_device *adev,
				 u32 pcie_index, u32 pcie_data,
				 u32 reg_addr, u32 reg_data)
अणु
	अचिन्हित दीर्घ flags;
	व्योम __iomem *pcie_index_offset;
	व्योम __iomem *pcie_data_offset;

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	pcie_index_offset = (व्योम __iomem *)adev->rmmio + pcie_index * 4;
	pcie_data_offset = (व्योम __iomem *)adev->rmmio + pcie_data * 4;

	ग_लिखोl(reg_addr, pcie_index_offset);
	पढ़ोl(pcie_index_offset);
	ग_लिखोl(reg_data, pcie_data_offset);
	पढ़ोl(pcie_data_offset);
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);
पूर्ण

/**
 * amdgpu_device_indirect_wreg64 - ग_लिखो a 64bits indirect रेजिस्टर address
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @pcie_index: mmio रेजिस्टर offset
 * @pcie_data: mmio रेजिस्टर offset
 * @reg_addr: indirect रेजिस्टर offset
 * @reg_data: indirect रेजिस्टर data
 *
 */
व्योम amdgpu_device_indirect_wreg64(काष्ठा amdgpu_device *adev,
				   u32 pcie_index, u32 pcie_data,
				   u32 reg_addr, u64 reg_data)
अणु
	अचिन्हित दीर्घ flags;
	व्योम __iomem *pcie_index_offset;
	व्योम __iomem *pcie_data_offset;

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	pcie_index_offset = (व्योम __iomem *)adev->rmmio + pcie_index * 4;
	pcie_data_offset = (व्योम __iomem *)adev->rmmio + pcie_data * 4;

	/* ग_लिखो low 32 bits */
	ग_लिखोl(reg_addr, pcie_index_offset);
	पढ़ोl(pcie_index_offset);
	ग_लिखोl((u32)(reg_data & 0xffffffffULL), pcie_data_offset);
	पढ़ोl(pcie_data_offset);
	/* ग_लिखो high 32 bits */
	ग_लिखोl(reg_addr + 4, pcie_index_offset);
	पढ़ोl(pcie_index_offset);
	ग_लिखोl((u32)(reg_data >> 32), pcie_data_offset);
	पढ़ोl(pcie_data_offset);
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);
पूर्ण

/**
 * amdgpu_invalid_rreg - dummy reg पढ़ो function
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @reg: offset of रेजिस्टर
 *
 * Dummy रेजिस्टर पढ़ो function.  Used क्रम रेजिस्टर blocks
 * that certain asics करोn't have (all asics).
 * Returns the value in the रेजिस्टर.
 */
अटल uपूर्णांक32_t amdgpu_invalid_rreg(काष्ठा amdgpu_device *adev, uपूर्णांक32_t reg)
अणु
	DRM_ERROR("Invalid callback to read register 0x%04X\n", reg);
	BUG();
	वापस 0;
पूर्ण

/**
 * amdgpu_invalid_wreg - dummy reg ग_लिखो function
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @reg: offset of रेजिस्टर
 * @v: value to ग_लिखो to the रेजिस्टर
 *
 * Dummy रेजिस्टर पढ़ो function.  Used क्रम रेजिस्टर blocks
 * that certain asics करोn't have (all asics).
 */
अटल व्योम amdgpu_invalid_wreg(काष्ठा amdgpu_device *adev, uपूर्णांक32_t reg, uपूर्णांक32_t v)
अणु
	DRM_ERROR("Invalid callback to write register 0x%04X with 0x%08X\n",
		  reg, v);
	BUG();
पूर्ण

/**
 * amdgpu_invalid_rreg64 - dummy 64 bit reg पढ़ो function
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @reg: offset of रेजिस्टर
 *
 * Dummy रेजिस्टर पढ़ो function.  Used क्रम रेजिस्टर blocks
 * that certain asics करोn't have (all asics).
 * Returns the value in the रेजिस्टर.
 */
अटल uपूर्णांक64_t amdgpu_invalid_rreg64(काष्ठा amdgpu_device *adev, uपूर्णांक32_t reg)
अणु
	DRM_ERROR("Invalid callback to read 64 bit register 0x%04X\n", reg);
	BUG();
	वापस 0;
पूर्ण

/**
 * amdgpu_invalid_wreg64 - dummy reg ग_लिखो function
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @reg: offset of रेजिस्टर
 * @v: value to ग_लिखो to the रेजिस्टर
 *
 * Dummy रेजिस्टर पढ़ो function.  Used क्रम रेजिस्टर blocks
 * that certain asics करोn't have (all asics).
 */
अटल व्योम amdgpu_invalid_wreg64(काष्ठा amdgpu_device *adev, uपूर्णांक32_t reg, uपूर्णांक64_t v)
अणु
	DRM_ERROR("Invalid callback to write 64 bit register 0x%04X with 0x%08llX\n",
		  reg, v);
	BUG();
पूर्ण

/**
 * amdgpu_block_invalid_rreg - dummy reg पढ़ो function
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @block: offset of instance
 * @reg: offset of रेजिस्टर
 *
 * Dummy रेजिस्टर पढ़ो function.  Used क्रम रेजिस्टर blocks
 * that certain asics करोn't have (all asics).
 * Returns the value in the रेजिस्टर.
 */
अटल uपूर्णांक32_t amdgpu_block_invalid_rreg(काष्ठा amdgpu_device *adev,
					  uपूर्णांक32_t block, uपूर्णांक32_t reg)
अणु
	DRM_ERROR("Invalid callback to read register 0x%04X in block 0x%04X\n",
		  reg, block);
	BUG();
	वापस 0;
पूर्ण

/**
 * amdgpu_block_invalid_wreg - dummy reg ग_लिखो function
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @block: offset of instance
 * @reg: offset of रेजिस्टर
 * @v: value to ग_लिखो to the रेजिस्टर
 *
 * Dummy रेजिस्टर पढ़ो function.  Used क्रम रेजिस्टर blocks
 * that certain asics करोn't have (all asics).
 */
अटल व्योम amdgpu_block_invalid_wreg(काष्ठा amdgpu_device *adev,
				      uपूर्णांक32_t block,
				      uपूर्णांक32_t reg, uपूर्णांक32_t v)
अणु
	DRM_ERROR("Invalid block callback to write register 0x%04X in block 0x%04X with 0x%08X\n",
		  reg, block, v);
	BUG();
पूर्ण

/**
 * amdgpu_device_asic_init - Wrapper क्रम atom asic_init
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Does any asic specअगरic work and then calls atom asic init.
 */
अटल पूर्णांक amdgpu_device_asic_init(काष्ठा amdgpu_device *adev)
अणु
	amdgpu_asic_pre_asic_init(adev);

	वापस amdgpu_atom_asic_init(adev->mode_info.atom_context);
पूर्ण

/**
 * amdgpu_device_vram_scratch_init - allocate the VRAM scratch page
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Allocates a scratch page of VRAM क्रम use by various things in the
 * driver.
 */
अटल पूर्णांक amdgpu_device_vram_scratch_init(काष्ठा amdgpu_device *adev)
अणु
	वापस amdgpu_bo_create_kernel(adev, AMDGPU_GPU_PAGE_SIZE,
				       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM,
				       &adev->vram_scratch.robj,
				       &adev->vram_scratch.gpu_addr,
				       (व्योम **)&adev->vram_scratch.ptr);
पूर्ण

/**
 * amdgpu_device_vram_scratch_fini - Free the VRAM scratch page
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Frees the VRAM scratch page.
 */
अटल व्योम amdgpu_device_vram_scratch_fini(काष्ठा amdgpu_device *adev)
अणु
	amdgpu_bo_मुक्त_kernel(&adev->vram_scratch.robj, शून्य, शून्य);
पूर्ण

/**
 * amdgpu_device_program_रेजिस्टर_sequence - program an array of रेजिस्टरs.
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @रेजिस्टरs: poपूर्णांकer to the रेजिस्टर array
 * @array_size: size of the रेजिस्टर array
 *
 * Programs an array or रेजिस्टरs with and and or masks.
 * This is a helper क्रम setting golden रेजिस्टरs.
 */
व्योम amdgpu_device_program_रेजिस्टर_sequence(काष्ठा amdgpu_device *adev,
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
			अगर (adev->family >= AMDGPU_FAMILY_AI)
				पंचांगp |= (or_mask & and_mask);
			अन्यथा
				पंचांगp |= or_mask;
		पूर्ण
		WREG32(reg, पंचांगp);
	पूर्ण
पूर्ण

/**
 * amdgpu_device_pci_config_reset - reset the GPU
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Resets the GPU using the pci config reset sequence.
 * Only applicable to asics prior to vega10.
 */
व्योम amdgpu_device_pci_config_reset(काष्ठा amdgpu_device *adev)
अणु
	pci_ग_लिखो_config_dword(adev->pdev, 0x7c, AMDGPU_ASIC_RESET_DATA);
पूर्ण

/**
 * amdgpu_device_pci_reset - reset the GPU using generic PCI means
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Resets the GPU using generic pci reset पूर्णांकerfaces (FLR, SBR, etc.).
 */
पूर्णांक amdgpu_device_pci_reset(काष्ठा amdgpu_device *adev)
अणु
	वापस pci_reset_function(adev->pdev);
पूर्ण

/*
 * GPU करोorbell aperture helpers function.
 */
/**
 * amdgpu_device_करोorbell_init - Init करोorbell driver inक्रमmation.
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Init करोorbell driver inक्रमmation (CIK)
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक amdgpu_device_करोorbell_init(काष्ठा amdgpu_device *adev)
अणु

	/* No करोorbell on SI hardware generation */
	अगर (adev->asic_type < CHIP_BONAIRE) अणु
		adev->करोorbell.base = 0;
		adev->करोorbell.size = 0;
		adev->करोorbell.num_करोorbells = 0;
		adev->करोorbell.ptr = शून्य;
		वापस 0;
	पूर्ण

	अगर (pci_resource_flags(adev->pdev, 2) & IORESOURCE_UNSET)
		वापस -EINVAL;

	amdgpu_asic_init_करोorbell_index(adev);

	/* करोorbell bar mapping */
	adev->करोorbell.base = pci_resource_start(adev->pdev, 2);
	adev->करोorbell.size = pci_resource_len(adev->pdev, 2);

	adev->करोorbell.num_करोorbells = min_t(u32, adev->करोorbell.size / माप(u32),
					     adev->करोorbell_index.max_assignment+1);
	अगर (adev->करोorbell.num_करोorbells == 0)
		वापस -EINVAL;

	/* For Vega, reserve and map two pages on करोorbell BAR since SDMA
	 * paging queue करोorbell use the second page. The
	 * AMDGPU_DOORBELL64_MAX_ASSIGNMENT definition assumes all the
	 * करोorbells are in the first page. So with paging queue enabled,
	 * the max num_करोorbells should + 1 page (0x400 in dword)
	 */
	अगर (adev->asic_type >= CHIP_VEGA10)
		adev->करोorbell.num_करोorbells += 0x400;

	adev->करोorbell.ptr = ioremap(adev->करोorbell.base,
				     adev->करोorbell.num_करोorbells *
				     माप(u32));
	अगर (adev->करोorbell.ptr == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/**
 * amdgpu_device_करोorbell_fini - Tear करोwn करोorbell driver inक्रमmation.
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Tear करोwn करोorbell driver inक्रमmation (CIK)
 */
अटल व्योम amdgpu_device_करोorbell_fini(काष्ठा amdgpu_device *adev)
अणु
	iounmap(adev->करोorbell.ptr);
	adev->करोorbell.ptr = शून्य;
पूर्ण



/*
 * amdgpu_device_wb_*()
 * Writeback is the method by which the GPU updates special pages in memory
 * with the status of certain GPU events (fences, ring poपूर्णांकers,etc.).
 */

/**
 * amdgpu_device_wb_fini - Disable Writeback and मुक्त memory
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Disables Writeback and मुक्तs the Writeback memory (all asics).
 * Used at driver shutकरोwn.
 */
अटल व्योम amdgpu_device_wb_fini(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->wb.wb_obj) अणु
		amdgpu_bo_मुक्त_kernel(&adev->wb.wb_obj,
				      &adev->wb.gpu_addr,
				      (व्योम **)&adev->wb.wb);
		adev->wb.wb_obj = शून्य;
	पूर्ण
पूर्ण

/**
 * amdgpu_device_wb_init- Init Writeback driver info and allocate memory
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Initializes ग_लिखोback and allocates ग_लिखोback memory (all asics).
 * Used at driver startup.
 * Returns 0 on success or an -error on failure.
 */
अटल पूर्णांक amdgpu_device_wb_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	अगर (adev->wb.wb_obj == शून्य) अणु
		/* AMDGPU_MAX_WB * माप(uपूर्णांक32_t) * 8 = AMDGPU_MAX_WB 256bit slots */
		r = amdgpu_bo_create_kernel(adev, AMDGPU_MAX_WB * माप(uपूर्णांक32_t) * 8,
					    PAGE_SIZE, AMDGPU_GEM_DOMAIN_GTT,
					    &adev->wb.wb_obj, &adev->wb.gpu_addr,
					    (व्योम **)&adev->wb.wb);
		अगर (r) अणु
			dev_warn(adev->dev, "(%d) create WB bo failed\n", r);
			वापस r;
		पूर्ण

		adev->wb.num_wb = AMDGPU_MAX_WB;
		स_रखो(&adev->wb.used, 0, माप(adev->wb.used));

		/* clear wb memory */
		स_रखो((अक्षर *)adev->wb.wb, 0, AMDGPU_MAX_WB * माप(uपूर्णांक32_t) * 8);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_device_wb_get - Allocate a wb entry
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @wb: wb index
 *
 * Allocate a wb slot क्रम use by the driver (all asics).
 * Returns 0 on success or -EINVAL on failure.
 */
पूर्णांक amdgpu_device_wb_get(काष्ठा amdgpu_device *adev, u32 *wb)
अणु
	अचिन्हित दीर्घ offset = find_first_zero_bit(adev->wb.used, adev->wb.num_wb);

	अगर (offset < adev->wb.num_wb) अणु
		__set_bit(offset, adev->wb.used);
		*wb = offset << 3; /* convert to dw offset */
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * amdgpu_device_wb_मुक्त - Free a wb entry
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @wb: wb index
 *
 * Free a wb slot allocated क्रम use by the driver (all asics)
 */
व्योम amdgpu_device_wb_मुक्त(काष्ठा amdgpu_device *adev, u32 wb)
अणु
	wb >>= 3;
	अगर (wb < adev->wb.num_wb)
		__clear_bit(wb, adev->wb.used);
पूर्ण

/**
 * amdgpu_device_resize_fb_bar - try to resize FB BAR
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Try to resize FB BAR to make all VRAM CPU accessible. We try very hard not
 * to fail, but अगर any of the BARs is not accessible after the size we पात
 * driver loading by वापसing -ENODEV.
 */
पूर्णांक amdgpu_device_resize_fb_bar(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक rbar_size = pci_rebar_bytes_to_size(adev->gmc.real_vram_size);
	काष्ठा pci_bus *root;
	काष्ठा resource *res;
	अचिन्हित i;
	u16 cmd;
	पूर्णांक r;

	/* Bypass क्रम VF */
	अगर (amdgpu_sriov_vf(adev))
		वापस 0;

	/* skip अगर the bios has alपढ़ोy enabled large BAR */
	अगर (adev->gmc.real_vram_size &&
	    (pci_resource_len(adev->pdev, 0) >= adev->gmc.real_vram_size))
		वापस 0;

	/* Check अगर the root BUS has 64bit memory resources */
	root = adev->pdev->bus;
	जबतक (root->parent)
		root = root->parent;

	pci_bus_क्रम_each_resource(root, res, i) अणु
		अगर (res && res->flags & (IORESOURCE_MEM | IORESOURCE_MEM_64) &&
		    res->start > 0x100000000ull)
			अवरोध;
	पूर्ण

	/* Trying to resize is poपूर्णांकless without a root hub winकरोw above 4GB */
	अगर (!res)
		वापस 0;

	/* Limit the BAR size to what is available */
	rbar_size = min(fls(pci_rebar_get_possible_sizes(adev->pdev, 0)) - 1,
			rbar_size);

	/* Disable memory decoding जबतक we change the BAR addresses and size */
	pci_पढ़ो_config_word(adev->pdev, PCI_COMMAND, &cmd);
	pci_ग_लिखो_config_word(adev->pdev, PCI_COMMAND,
			      cmd & ~PCI_COMMAND_MEMORY);

	/* Free the VRAM and करोorbell BAR, we most likely need to move both. */
	amdgpu_device_करोorbell_fini(adev);
	अगर (adev->asic_type >= CHIP_BONAIRE)
		pci_release_resource(adev->pdev, 2);

	pci_release_resource(adev->pdev, 0);

	r = pci_resize_resource(adev->pdev, 0, rbar_size);
	अगर (r == -ENOSPC)
		DRM_INFO("Not enough PCI address space for a large BAR.");
	अन्यथा अगर (r && r != -ENOTSUPP)
		DRM_ERROR("Problem resizing BAR0 (%d).", r);

	pci_assign_unasचिन्हित_bus_resources(adev->pdev->bus);

	/* When the करोorbell or fb BAR isn't available we have no chance of
	 * using the device.
	 */
	r = amdgpu_device_करोorbell_init(adev);
	अगर (r || (pci_resource_flags(adev->pdev, 0) & IORESOURCE_UNSET))
		वापस -ENODEV;

	pci_ग_लिखो_config_word(adev->pdev, PCI_COMMAND, cmd);

	वापस 0;
पूर्ण

/*
 * GPU helpers function.
 */
/**
 * amdgpu_device_need_post - check अगर the hw need post or not
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Check अगर the asic has been initialized (all asics) at driver startup
 * or post is needed अगर  hw reset is perक्रमmed.
 * Returns true अगर need or false अगर not.
 */
bool amdgpu_device_need_post(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t reg;

	अगर (amdgpu_sriov_vf(adev))
		वापस false;

	अगर (amdgpu_passthrough(adev)) अणु
		/* क्रम FIJI: In whole GPU pass-through भवization हाल, after VM reboot
		 * some old smc fw still need driver करो vPost otherwise gpu hang, जबतक
		 * those smc fw version above 22.15 करोesn't have this flaw, so we क्रमce
		 * vpost executed क्रम smc version below 22.15
		 */
		अगर (adev->asic_type == CHIP_FIJI) अणु
			पूर्णांक err;
			uपूर्णांक32_t fw_ver;
			err = request_firmware(&adev->pm.fw, "amdgpu/fiji_smc.bin", adev->dev);
			/* क्रमce vPost अगर error occured */
			अगर (err)
				वापस true;

			fw_ver = *((uपूर्णांक32_t *)adev->pm.fw->data + 69);
			अगर (fw_ver < 0x00160e00)
				वापस true;
		पूर्ण
	पूर्ण

	/* Don't post अगर we need to reset whole hive on init */
	अगर (adev->gmc.xgmi.pending_reset)
		वापस false;

	अगर (adev->has_hw_reset) अणु
		adev->has_hw_reset = false;
		वापस true;
	पूर्ण

	/* bios scratch used on CIK+ */
	अगर (adev->asic_type >= CHIP_BONAIRE)
		वापस amdgpu_atombios_scratch_need_asic_init(adev);

	/* check MEM_SIZE क्रम older asics */
	reg = amdgpu_asic_get_config_memsize(adev);

	अगर ((reg != 0) && (reg != 0xffffffff))
		वापस false;

	वापस true;
पूर्ण

/* अगर we get transitioned to only one device, take VGA back */
/**
 * amdgpu_device_vga_set_decode - enable/disable vga decode
 *
 * @cookie: amdgpu_device poपूर्णांकer
 * @state: enable/disable vga decode
 *
 * Enable/disable vga decode (all asics).
 * Returns VGA resource flags.
 */
अटल अचिन्हित पूर्णांक amdgpu_device_vga_set_decode(व्योम *cookie, bool state)
अणु
	काष्ठा amdgpu_device *adev = cookie;
	amdgpu_asic_set_vga_state(adev, state);
	अगर (state)
		वापस VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM |
		       VGA_RSRC_NORMAL_IO | VGA_RSRC_NORMAL_MEM;
	अन्यथा
		वापस VGA_RSRC_NORMAL_IO | VGA_RSRC_NORMAL_MEM;
पूर्ण

/**
 * amdgpu_device_check_block_size - validate the vm block size
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Validates the vm block size specअगरied via module parameter.
 * The vm block size defines number of bits in page table versus page directory,
 * a page is 4KB so we have 12 bits offset, minimum 9 bits in the
 * page table and the reमुख्यing bits are in the page directory.
 */
अटल व्योम amdgpu_device_check_block_size(काष्ठा amdgpu_device *adev)
अणु
	/* defines number of bits in page table versus page directory,
	 * a page is 4KB so we have 12 bits offset, minimum 9 bits in the
	 * page table and the reमुख्यing bits are in the page directory */
	अगर (amdgpu_vm_block_size == -1)
		वापस;

	अगर (amdgpu_vm_block_size < 9) अणु
		dev_warn(adev->dev, "VM page table size (%d) too small\n",
			 amdgpu_vm_block_size);
		amdgpu_vm_block_size = -1;
	पूर्ण
पूर्ण

/**
 * amdgpu_device_check_vm_size - validate the vm size
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Validates the vm size in GB specअगरied via module parameter.
 * The VM size is the size of the GPU भव memory space in GB.
 */
अटल व्योम amdgpu_device_check_vm_size(काष्ठा amdgpu_device *adev)
अणु
	/* no need to check the शेष value */
	अगर (amdgpu_vm_size == -1)
		वापस;

	अगर (amdgpu_vm_size < 1) अणु
		dev_warn(adev->dev, "VM size (%d) too small, min is 1GB\n",
			 amdgpu_vm_size);
		amdgpu_vm_size = -1;
	पूर्ण
पूर्ण

अटल व्योम amdgpu_device_check_smu_prv_buffer_size(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा sysinfo si;
	bool is_os_64 = (माप(व्योम *) == 8);
	uपूर्णांक64_t total_memory;
	uपूर्णांक64_t dram_size_seven_GB = 0x1B8000000;
	uपूर्णांक64_t dram_माप_प्रकारhree_GB = 0xB8000000;

	अगर (amdgpu_smu_memory_pool_size == 0)
		वापस;

	अगर (!is_os_64) अणु
		DRM_WARN("Not 64-bit OS, feature not supported\n");
		जाओ def_value;
	पूर्ण
	si_meminfo(&si);
	total_memory = (uपूर्णांक64_t)si.totalram * si.mem_unit;

	अगर ((amdgpu_smu_memory_pool_size == 1) ||
		(amdgpu_smu_memory_pool_size == 2)) अणु
		अगर (total_memory < dram_माप_प्रकारhree_GB)
			जाओ def_value1;
	पूर्ण अन्यथा अगर ((amdgpu_smu_memory_pool_size == 4) ||
		(amdgpu_smu_memory_pool_size == 8)) अणु
		अगर (total_memory < dram_size_seven_GB)
			जाओ def_value1;
	पूर्ण अन्यथा अणु
		DRM_WARN("Smu memory pool size not supported\n");
		जाओ def_value;
	पूर्ण
	adev->pm.smu_prv_buffer_size = amdgpu_smu_memory_pool_size << 28;

	वापस;

def_value1:
	DRM_WARN("No enough system memory\n");
def_value:
	adev->pm.smu_prv_buffer_size = 0;
पूर्ण

/**
 * amdgpu_device_check_arguments - validate module params
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Validates certain module parameters and updates
 * the associated values used by the driver (all asics).
 */
अटल पूर्णांक amdgpu_device_check_arguments(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_sched_jobs < 4) अणु
		dev_warn(adev->dev, "sched jobs (%d) must be at least 4\n",
			 amdgpu_sched_jobs);
		amdgpu_sched_jobs = 4;
	पूर्ण अन्यथा अगर (!is_घातer_of_2(amdgpu_sched_jobs))अणु
		dev_warn(adev->dev, "sched jobs (%d) must be a power of 2\n",
			 amdgpu_sched_jobs);
		amdgpu_sched_jobs = roundup_घात_of_two(amdgpu_sched_jobs);
	पूर्ण

	अगर (amdgpu_gart_size != -1 && amdgpu_gart_size < 32) अणु
		/* gart size must be greater or equal to 32M */
		dev_warn(adev->dev, "gart size (%d) too small\n",
			 amdgpu_gart_size);
		amdgpu_gart_size = -1;
	पूर्ण

	अगर (amdgpu_gtt_size != -1 && amdgpu_gtt_size < 32) अणु
		/* gtt size must be greater or equal to 32M */
		dev_warn(adev->dev, "gtt size (%d) too small\n",
				 amdgpu_gtt_size);
		amdgpu_gtt_size = -1;
	पूर्ण

	/* valid range is between 4 and 9 inclusive */
	अगर (amdgpu_vm_fragment_size != -1 &&
	    (amdgpu_vm_fragment_size > 9 || amdgpu_vm_fragment_size < 4)) अणु
		dev_warn(adev->dev, "valid range is between 4 and 9\n");
		amdgpu_vm_fragment_size = -1;
	पूर्ण

	अगर (amdgpu_sched_hw_submission < 2) अणु
		dev_warn(adev->dev, "sched hw submission jobs (%d) must be at least 2\n",
			 amdgpu_sched_hw_submission);
		amdgpu_sched_hw_submission = 2;
	पूर्ण अन्यथा अगर (!is_घातer_of_2(amdgpu_sched_hw_submission)) अणु
		dev_warn(adev->dev, "sched hw submission jobs (%d) must be a power of 2\n",
			 amdgpu_sched_hw_submission);
		amdgpu_sched_hw_submission = roundup_घात_of_two(amdgpu_sched_hw_submission);
	पूर्ण

	amdgpu_device_check_smu_prv_buffer_size(adev);

	amdgpu_device_check_vm_size(adev);

	amdgpu_device_check_block_size(adev);

	adev->firmware.load_type = amdgpu_ucode_get_load_type(adev, amdgpu_fw_load_type);

	amdgpu_gmc_पंचांगz_set(adev);

	amdgpu_gmc_noretry_set(adev);

	वापस 0;
पूर्ण

/**
 * amdgpu_चयनeroo_set_state - set चयनeroo state
 *
 * @pdev: pci dev poपूर्णांकer
 * @state: vga_चयनeroo state
 *
 * Callback क्रम the चयनeroo driver.  Suspends or resumes the
 * the asics beक्रमe or after it is घातered up using ACPI methods.
 */
अटल व्योम amdgpu_चयनeroo_set_state(काष्ठा pci_dev *pdev,
					क्रमागत vga_चयनeroo_state state)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);
	पूर्णांक r;

	अगर (amdgpu_device_supports_px(dev) && state == VGA_SWITCHEROO_OFF)
		वापस;

	अगर (state == VGA_SWITCHEROO_ON) अणु
		pr_info("switched on\n");
		/* करोn't suspend or resume card normally */
		dev->चयन_घातer_state = DRM_SWITCH_POWER_CHANGING;

		pci_set_घातer_state(pdev, PCI_D0);
		amdgpu_device_load_pci_state(pdev);
		r = pci_enable_device(pdev);
		अगर (r)
			DRM_WARN("pci_enable_device failed (%d)\n", r);
		amdgpu_device_resume(dev, true);

		dev->चयन_घातer_state = DRM_SWITCH_POWER_ON;
	पूर्ण अन्यथा अणु
		pr_info("switched off\n");
		dev->चयन_घातer_state = DRM_SWITCH_POWER_CHANGING;
		amdgpu_device_suspend(dev, true);
		amdgpu_device_cache_pci_state(pdev);
		/* Shut करोwn the device */
		pci_disable_device(pdev);
		pci_set_घातer_state(pdev, PCI_D3cold);
		dev->चयन_घातer_state = DRM_SWITCH_POWER_OFF;
	पूर्ण
पूर्ण

/**
 * amdgpu_चयनeroo_can_चयन - see अगर चयनeroo state can change
 *
 * @pdev: pci dev poपूर्णांकer
 *
 * Callback क्रम the चयनeroo driver.  Check of the चयनeroo
 * state can be changed.
 * Returns true अगर the state can be changed, false अगर not.
 */
अटल bool amdgpu_चयनeroo_can_चयन(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);

	/*
	* FIXME: खोलो_count is रक्षित by drm_global_mutex but that would lead to
	* locking inversion with the driver load path. And the access here is
	* completely racy anyway. So करोn't bother with locking क्रम now.
	*/
	वापस atomic_पढ़ो(&dev->खोलो_count) == 0;
पूर्ण

अटल स्थिर काष्ठा vga_चयनeroo_client_ops amdgpu_चयनeroo_ops = अणु
	.set_gpu_state = amdgpu_चयनeroo_set_state,
	.reprobe = शून्य,
	.can_चयन = amdgpu_चयनeroo_can_चयन,
पूर्ण;

/**
 * amdgpu_device_ip_set_घड़ीgating_state - set the CG state
 *
 * @dev: amdgpu_device poपूर्णांकer
 * @block_type: Type of hardware IP (SMU, GFX, UVD, etc.)
 * @state: घड़ीgating state (gate or ungate)
 *
 * Sets the requested घड़ीgating state क्रम all instances of
 * the hardware IP specअगरied.
 * Returns the error code from the last instance.
 */
पूर्णांक amdgpu_device_ip_set_घड़ीgating_state(व्योम *dev,
					   क्रमागत amd_ip_block_type block_type,
					   क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = dev;
	पूर्णांक i, r = 0;

	क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
		अगर (!adev->ip_blocks[i].status.valid)
			जारी;
		अगर (adev->ip_blocks[i].version->type != block_type)
			जारी;
		अगर (!adev->ip_blocks[i].version->funcs->set_घड़ीgating_state)
			जारी;
		r = adev->ip_blocks[i].version->funcs->set_घड़ीgating_state(
			(व्योम *)adev, state);
		अगर (r)
			DRM_ERROR("set_clockgating_state of IP block <%s> failed %d\n",
				  adev->ip_blocks[i].version->funcs->name, r);
	पूर्ण
	वापस r;
पूर्ण

/**
 * amdgpu_device_ip_set_घातergating_state - set the PG state
 *
 * @dev: amdgpu_device poपूर्णांकer
 * @block_type: Type of hardware IP (SMU, GFX, UVD, etc.)
 * @state: घातergating state (gate or ungate)
 *
 * Sets the requested घातergating state क्रम all instances of
 * the hardware IP specअगरied.
 * Returns the error code from the last instance.
 */
पूर्णांक amdgpu_device_ip_set_घातergating_state(व्योम *dev,
					   क्रमागत amd_ip_block_type block_type,
					   क्रमागत amd_घातergating_state state)
अणु
	काष्ठा amdgpu_device *adev = dev;
	पूर्णांक i, r = 0;

	क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
		अगर (!adev->ip_blocks[i].status.valid)
			जारी;
		अगर (adev->ip_blocks[i].version->type != block_type)
			जारी;
		अगर (!adev->ip_blocks[i].version->funcs->set_घातergating_state)
			जारी;
		r = adev->ip_blocks[i].version->funcs->set_घातergating_state(
			(व्योम *)adev, state);
		अगर (r)
			DRM_ERROR("set_powergating_state of IP block <%s> failed %d\n",
				  adev->ip_blocks[i].version->funcs->name, r);
	पूर्ण
	वापस r;
पूर्ण

/**
 * amdgpu_device_ip_get_घड़ीgating_state - get the CG state
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @flags: घड़ीgating feature flags
 *
 * Walks the list of IPs on the device and updates the घड़ीgating
 * flags क्रम each IP.
 * Updates @flags with the feature flags क्रम each hardware IP where
 * घड़ीgating is enabled.
 */
व्योम amdgpu_device_ip_get_घड़ीgating_state(काष्ठा amdgpu_device *adev,
					    u32 *flags)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
		अगर (!adev->ip_blocks[i].status.valid)
			जारी;
		अगर (adev->ip_blocks[i].version->funcs->get_घड़ीgating_state)
			adev->ip_blocks[i].version->funcs->get_घड़ीgating_state((व्योम *)adev, flags);
	पूर्ण
पूर्ण

/**
 * amdgpu_device_ip_रुको_क्रम_idle - रुको क्रम idle
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @block_type: Type of hardware IP (SMU, GFX, UVD, etc.)
 *
 * Waits क्रम the request hardware IP to be idle.
 * Returns 0 क्रम success or a negative error code on failure.
 */
पूर्णांक amdgpu_device_ip_रुको_क्रम_idle(काष्ठा amdgpu_device *adev,
				   क्रमागत amd_ip_block_type block_type)
अणु
	पूर्णांक i, r;

	क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
		अगर (!adev->ip_blocks[i].status.valid)
			जारी;
		अगर (adev->ip_blocks[i].version->type == block_type) अणु
			r = adev->ip_blocks[i].version->funcs->रुको_क्रम_idle((व्योम *)adev);
			अगर (r)
				वापस r;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;

पूर्ण

/**
 * amdgpu_device_ip_is_idle - is the hardware IP idle
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @block_type: Type of hardware IP (SMU, GFX, UVD, etc.)
 *
 * Check अगर the hardware IP is idle or not.
 * Returns true अगर it the IP is idle, false अगर not.
 */
bool amdgpu_device_ip_is_idle(काष्ठा amdgpu_device *adev,
			      क्रमागत amd_ip_block_type block_type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
		अगर (!adev->ip_blocks[i].status.valid)
			जारी;
		अगर (adev->ip_blocks[i].version->type == block_type)
			वापस adev->ip_blocks[i].version->funcs->is_idle((व्योम *)adev);
	पूर्ण
	वापस true;

पूर्ण

/**
 * amdgpu_device_ip_get_ip_block - get a hw IP poपूर्णांकer
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @type: Type of hardware IP (SMU, GFX, UVD, etc.)
 *
 * Returns a poपूर्णांकer to the hardware IP block काष्ठाure
 * अगर it exists क्रम the asic, otherwise शून्य.
 */
काष्ठा amdgpu_ip_block *
amdgpu_device_ip_get_ip_block(काष्ठा amdgpu_device *adev,
			      क्रमागत amd_ip_block_type type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->num_ip_blocks; i++)
		अगर (adev->ip_blocks[i].version->type == type)
			वापस &adev->ip_blocks[i];

	वापस शून्य;
पूर्ण

/**
 * amdgpu_device_ip_block_version_cmp
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @type: क्रमागत amd_ip_block_type
 * @major: major version
 * @minor: minor version
 *
 * वापस 0 अगर equal or greater
 * वापस 1 अगर smaller or the ip_block करोesn't exist
 */
पूर्णांक amdgpu_device_ip_block_version_cmp(काष्ठा amdgpu_device *adev,
				       क्रमागत amd_ip_block_type type,
				       u32 major, u32 minor)
अणु
	काष्ठा amdgpu_ip_block *ip_block = amdgpu_device_ip_get_ip_block(adev, type);

	अगर (ip_block && ((ip_block->version->major > major) ||
			((ip_block->version->major == major) &&
			(ip_block->version->minor >= minor))))
		वापस 0;

	वापस 1;
पूर्ण

/**
 * amdgpu_device_ip_block_add
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ip_block_version: poपूर्णांकer to the IP to add
 *
 * Adds the IP block driver inक्रमmation to the collection of IPs
 * on the asic.
 */
पूर्णांक amdgpu_device_ip_block_add(काष्ठा amdgpu_device *adev,
			       स्थिर काष्ठा amdgpu_ip_block_version *ip_block_version)
अणु
	अगर (!ip_block_version)
		वापस -EINVAL;

	चयन (ip_block_version->type) अणु
	हाल AMD_IP_BLOCK_TYPE_VCN:
		अगर (adev->harvest_ip_mask & AMD_HARVEST_IP_VCN_MASK)
			वापस 0;
		अवरोध;
	हाल AMD_IP_BLOCK_TYPE_JPEG:
		अगर (adev->harvest_ip_mask & AMD_HARVEST_IP_JPEG_MASK)
			वापस 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	DRM_INFO("add ip block number %d <%s>\n", adev->num_ip_blocks,
		  ip_block_version->funcs->name);

	adev->ip_blocks[adev->num_ip_blocks++].version = ip_block_version;

	वापस 0;
पूर्ण

/**
 * amdgpu_device_enable_भव_display - enable भव display feature
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Enabled the भव display feature अगर the user has enabled it via
 * the module parameter भव_display.  This feature provides a भव
 * display hardware on headless boards or in भवized environments.
 * This function parses and validates the configuration string specअगरied by
 * the user and configues the भव display configuration (number of
 * भव connectors, crtcs, etc.) specअगरied.
 */
अटल व्योम amdgpu_device_enable_भव_display(काष्ठा amdgpu_device *adev)
अणु
	adev->enable_भव_display = false;

	अगर (amdgpu_भव_display) अणु
		स्थिर अक्षर *pci_address_name = pci_name(adev->pdev);
		अक्षर *pciaddstr, *pciaddstr_पंचांगp, *pciaddname_पंचांगp, *pciaddname;

		pciaddstr = kstrdup(amdgpu_भव_display, GFP_KERNEL);
		pciaddstr_पंचांगp = pciaddstr;
		जबतक ((pciaddname_पंचांगp = strsep(&pciaddstr_पंचांगp, ";"))) अणु
			pciaddname = strsep(&pciaddname_पंचांगp, ",");
			अगर (!म_भेद("all", pciaddname)
			    || !म_भेद(pci_address_name, pciaddname)) अणु
				दीर्घ num_crtc;
				पूर्णांक res = -1;

				adev->enable_भव_display = true;

				अगर (pciaddname_पंचांगp)
					res = kम_से_दीर्घ(pciaddname_पंचांगp, 10,
						      &num_crtc);

				अगर (!res) अणु
					अगर (num_crtc < 1)
						num_crtc = 1;
					अगर (num_crtc > 6)
						num_crtc = 6;
					adev->mode_info.num_crtc = num_crtc;
				पूर्ण अन्यथा अणु
					adev->mode_info.num_crtc = 1;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण

		DRM_INFO("virtual display string:%s, %s:virtual_display:%d, num_crtc:%d\n",
			 amdgpu_भव_display, pci_address_name,
			 adev->enable_भव_display, adev->mode_info.num_crtc);

		kमुक्त(pciaddstr);
	पूर्ण
पूर्ण

/**
 * amdgpu_device_parse_gpu_info_fw - parse gpu info firmware
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Parses the asic configuration parameters specअगरied in the gpu info
 * firmware and makes them availale to the driver क्रम use in configuring
 * the asic.
 * Returns 0 on success, -EINVAL on failure.
 */
अटल पूर्णांक amdgpu_device_parse_gpu_info_fw(काष्ठा amdgpu_device *adev)
अणु
	स्थिर अक्षर *chip_name;
	अक्षर fw_name[40];
	पूर्णांक err;
	स्थिर काष्ठा gpu_info_firmware_header_v1_0 *hdr;

	adev->firmware.gpu_info_fw = शून्य;

	अगर (adev->mman.discovery_bin) अणु
		amdgpu_discovery_get_gfx_info(adev);

		/*
		 * FIXME: The bounding box is still needed by Navi12, so
		 * temporarily पढ़ो it from gpu_info firmware. Should be droped
		 * when DAL no दीर्घer needs it.
		 */
		अगर (adev->asic_type != CHIP_NAVI12)
			वापस 0;
	पूर्ण

	चयन (adev->asic_type) अणु
#अगर_घोषित CONFIG_DRM_AMDGPU_SI
	हाल CHIP_VERDE:
	हाल CHIP_TAHITI:
	हाल CHIP_PITCAIRN:
	हाल CHIP_OLAND:
	हाल CHIP_HAIन_अंक:
#पूर्ण_अगर
#अगर_घोषित CONFIG_DRM_AMDGPU_CIK
	हाल CHIP_BONAIRE:
	हाल CHIP_HAWAII:
	हाल CHIP_KAVERI:
	हाल CHIP_KABINI:
	हाल CHIP_MULLINS:
#पूर्ण_अगर
	हाल CHIP_TOPAZ:
	हाल CHIP_TONGA:
	हाल CHIP_FIJI:
	हाल CHIP_POLARIS10:
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
	हाल CHIP_VEGAM:
	हाल CHIP_CARRIZO:
	हाल CHIP_STONEY:
	हाल CHIP_VEGA20:
	हाल CHIP_ALDEBARAN:
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_DIMGREY_CAVEFISH:
	शेष:
		वापस 0;
	हाल CHIP_VEGA10:
		chip_name = "vega10";
		अवरोध;
	हाल CHIP_VEGA12:
		chip_name = "vega12";
		अवरोध;
	हाल CHIP_RAVEN:
		अगर (adev->apu_flags & AMD_APU_IS_RAVEN2)
			chip_name = "raven2";
		अन्यथा अगर (adev->apu_flags & AMD_APU_IS_PICASSO)
			chip_name = "picasso";
		अन्यथा
			chip_name = "raven";
		अवरोध;
	हाल CHIP_ARCTURUS:
		chip_name = "arcturus";
		अवरोध;
	हाल CHIP_RENOIR:
		अगर (adev->apu_flags & AMD_APU_IS_RENOIR)
			chip_name = "renoir";
		अन्यथा
			chip_name = "green_sardine";
		अवरोध;
	हाल CHIP_NAVI10:
		chip_name = "navi10";
		अवरोध;
	हाल CHIP_NAVI14:
		chip_name = "navi14";
		अवरोध;
	हाल CHIP_NAVI12:
		chip_name = "navi12";
		अवरोध;
	हाल CHIP_VANGOGH:
		chip_name = "vangogh";
		अवरोध;
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_gpu_info.bin", chip_name);
	err = request_firmware(&adev->firmware.gpu_info_fw, fw_name, adev->dev);
	अगर (err) अणु
		dev_err(adev->dev,
			"Failed to load gpu_info firmware \"%s\"\n",
			fw_name);
		जाओ out;
	पूर्ण
	err = amdgpu_ucode_validate(adev->firmware.gpu_info_fw);
	अगर (err) अणु
		dev_err(adev->dev,
			"Failed to validate gpu_info firmware \"%s\"\n",
			fw_name);
		जाओ out;
	पूर्ण

	hdr = (स्थिर काष्ठा gpu_info_firmware_header_v1_0 *)adev->firmware.gpu_info_fw->data;
	amdgpu_ucode_prपूर्णांक_gpu_info_hdr(&hdr->header);

	चयन (hdr->version_major) अणु
	हाल 1:
	अणु
		स्थिर काष्ठा gpu_info_firmware_v1_0 *gpu_info_fw =
			(स्थिर काष्ठा gpu_info_firmware_v1_0 *)(adev->firmware.gpu_info_fw->data +
								le32_to_cpu(hdr->header.ucode_array_offset_bytes));

		/*
		 * Should be droped when DAL no दीर्घer needs it.
		 */
		अगर (adev->asic_type == CHIP_NAVI12)
			जाओ parse_soc_bounding_box;

		adev->gfx.config.max_shader_engines = le32_to_cpu(gpu_info_fw->gc_num_se);
		adev->gfx.config.max_cu_per_sh = le32_to_cpu(gpu_info_fw->gc_num_cu_per_sh);
		adev->gfx.config.max_sh_per_se = le32_to_cpu(gpu_info_fw->gc_num_sh_per_se);
		adev->gfx.config.max_backends_per_se = le32_to_cpu(gpu_info_fw->gc_num_rb_per_se);
		adev->gfx.config.max_texture_channel_caches =
			le32_to_cpu(gpu_info_fw->gc_num_tccs);
		adev->gfx.config.max_gprs = le32_to_cpu(gpu_info_fw->gc_num_gprs);
		adev->gfx.config.max_gs_thपढ़ोs = le32_to_cpu(gpu_info_fw->gc_num_max_gs_thds);
		adev->gfx.config.gs_vgt_table_depth = le32_to_cpu(gpu_info_fw->gc_gs_table_depth);
		adev->gfx.config.gs_prim_buffer_depth = le32_to_cpu(gpu_info_fw->gc_gsprim_buff_depth);
		adev->gfx.config.द्विगुन_offchip_lds_buf =
			le32_to_cpu(gpu_info_fw->gc_द्विगुन_offchip_lds_buffer);
		adev->gfx.cu_info.wave_front_size = le32_to_cpu(gpu_info_fw->gc_wave_size);
		adev->gfx.cu_info.max_waves_per_simd =
			le32_to_cpu(gpu_info_fw->gc_max_waves_per_simd);
		adev->gfx.cu_info.max_scratch_slots_per_cu =
			le32_to_cpu(gpu_info_fw->gc_max_scratch_slots_per_cu);
		adev->gfx.cu_info.lds_size = le32_to_cpu(gpu_info_fw->gc_lds_size);
		अगर (hdr->version_minor >= 1) अणु
			स्थिर काष्ठा gpu_info_firmware_v1_1 *gpu_info_fw =
				(स्थिर काष्ठा gpu_info_firmware_v1_1 *)(adev->firmware.gpu_info_fw->data +
									le32_to_cpu(hdr->header.ucode_array_offset_bytes));
			adev->gfx.config.num_sc_per_sh =
				le32_to_cpu(gpu_info_fw->num_sc_per_sh);
			adev->gfx.config.num_packer_per_sc =
				le32_to_cpu(gpu_info_fw->num_packer_per_sc);
		पूर्ण

parse_soc_bounding_box:
		/*
		 * soc bounding box info is not पूर्णांकegrated in disocovery table,
		 * we always need to parse it from gpu info firmware अगर needed.
		 */
		अगर (hdr->version_minor == 2) अणु
			स्थिर काष्ठा gpu_info_firmware_v1_2 *gpu_info_fw =
				(स्थिर काष्ठा gpu_info_firmware_v1_2 *)(adev->firmware.gpu_info_fw->data +
									le32_to_cpu(hdr->header.ucode_array_offset_bytes));
			adev->dm.soc_bounding_box = &gpu_info_fw->soc_bounding_box;
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		dev_err(adev->dev,
			"Unsupported gpu_info table %d\n", hdr->header.ucode_version);
		err = -EINVAL;
		जाओ out;
	पूर्ण
out:
	वापस err;
पूर्ण

/**
 * amdgpu_device_ip_early_init - run early init क्रम hardware IPs
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Early initialization pass क्रम hardware IPs.  The hardware IPs that make
 * up each asic are discovered each IP's early_init callback is run.  This
 * is the first stage in initializing the asic.
 * Returns 0 on success, negative error code on failure.
 */
अटल पूर्णांक amdgpu_device_ip_early_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, r;

	amdgpu_device_enable_भव_display(adev);

	अगर (amdgpu_sriov_vf(adev)) अणु
		r = amdgpu_virt_request_full_gpu(adev, true);
		अगर (r)
			वापस r;
	पूर्ण

	चयन (adev->asic_type) अणु
#अगर_घोषित CONFIG_DRM_AMDGPU_SI
	हाल CHIP_VERDE:
	हाल CHIP_TAHITI:
	हाल CHIP_PITCAIRN:
	हाल CHIP_OLAND:
	हाल CHIP_HAIन_अंक:
		adev->family = AMDGPU_FAMILY_SI;
		r = si_set_ip_blocks(adev);
		अगर (r)
			वापस r;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DRM_AMDGPU_CIK
	हाल CHIP_BONAIRE:
	हाल CHIP_HAWAII:
	हाल CHIP_KAVERI:
	हाल CHIP_KABINI:
	हाल CHIP_MULLINS:
		अगर (adev->flags & AMD_IS_APU)
			adev->family = AMDGPU_FAMILY_KV;
		अन्यथा
			adev->family = AMDGPU_FAMILY_CI;

		r = cik_set_ip_blocks(adev);
		अगर (r)
			वापस r;
		अवरोध;
#पूर्ण_अगर
	हाल CHIP_TOPAZ:
	हाल CHIP_TONGA:
	हाल CHIP_FIJI:
	हाल CHIP_POLARIS10:
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
	हाल CHIP_VEGAM:
	हाल CHIP_CARRIZO:
	हाल CHIP_STONEY:
		अगर (adev->flags & AMD_IS_APU)
			adev->family = AMDGPU_FAMILY_CZ;
		अन्यथा
			adev->family = AMDGPU_FAMILY_VI;

		r = vi_set_ip_blocks(adev);
		अगर (r)
			वापस r;
		अवरोध;
	हाल CHIP_VEGA10:
	हाल CHIP_VEGA12:
	हाल CHIP_VEGA20:
	हाल CHIP_RAVEN:
	हाल CHIP_ARCTURUS:
	हाल CHIP_RENOIR:
	हाल CHIP_ALDEBARAN:
		अगर (adev->flags & AMD_IS_APU)
			adev->family = AMDGPU_FAMILY_RV;
		अन्यथा
			adev->family = AMDGPU_FAMILY_AI;

		r = soc15_set_ip_blocks(adev);
		अगर (r)
			वापस r;
		अवरोध;
	हाल  CHIP_NAVI10:
	हाल  CHIP_NAVI14:
	हाल  CHIP_NAVI12:
	हाल  CHIP_SIENNA_CICHLID:
	हाल  CHIP_NAVY_FLOUNDER:
	हाल  CHIP_DIMGREY_CAVEFISH:
	हाल CHIP_VANGOGH:
		अगर (adev->asic_type == CHIP_VANGOGH)
			adev->family = AMDGPU_FAMILY_VGH;
		अन्यथा
			adev->family = AMDGPU_FAMILY_NV;

		r = nv_set_ip_blocks(adev);
		अगर (r)
			वापस r;
		अवरोध;
	शेष:
		/* FIXME: not supported yet */
		वापस -EINVAL;
	पूर्ण

	amdgpu_amdkfd_device_probe(adev);

	adev->pm.pp_feature = amdgpu_pp_feature_mask;
	अगर (amdgpu_sriov_vf(adev) || sched_policy == KFD_SCHED_POLICY_NO_HWS)
		adev->pm.pp_feature &= ~PP_GFXOFF_MASK;
	अगर (amdgpu_sriov_vf(adev) && adev->asic_type == CHIP_SIENNA_CICHLID)
		adev->pm.pp_feature &= ~PP_OVERDRIVE_MASK;

	क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
		अगर ((amdgpu_ip_block_mask & (1 << i)) == 0) अणु
			DRM_ERROR("disabled ip block: %d <%s>\n",
				  i, adev->ip_blocks[i].version->funcs->name);
			adev->ip_blocks[i].status.valid = false;
		पूर्ण अन्यथा अणु
			अगर (adev->ip_blocks[i].version->funcs->early_init) अणु
				r = adev->ip_blocks[i].version->funcs->early_init((व्योम *)adev);
				अगर (r == -ENOENT) अणु
					adev->ip_blocks[i].status.valid = false;
				पूर्ण अन्यथा अगर (r) अणु
					DRM_ERROR("early_init of IP block <%s> failed %d\n",
						  adev->ip_blocks[i].version->funcs->name, r);
					वापस r;
				पूर्ण अन्यथा अणु
					adev->ip_blocks[i].status.valid = true;
				पूर्ण
			पूर्ण अन्यथा अणु
				adev->ip_blocks[i].status.valid = true;
			पूर्ण
		पूर्ण
		/* get the vbios after the asic_funcs are set up */
		अगर (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_COMMON) अणु
			r = amdgpu_device_parse_gpu_info_fw(adev);
			अगर (r)
				वापस r;

			/* Read BIOS */
			अगर (!amdgpu_get_bios(adev))
				वापस -EINVAL;

			r = amdgpu_atombios_init(adev);
			अगर (r) अणु
				dev_err(adev->dev, "amdgpu_atombios_init failed\n");
				amdgpu_vf_error_put(adev, AMDGIM_ERROR_VF_ATOMBIOS_INIT_FAIL, 0, 0);
				वापस r;
			पूर्ण

			/*get pf2vf msg info at it's earliest समय*/
			अगर (amdgpu_sriov_vf(adev))
				amdgpu_virt_init_data_exchange(adev);

		पूर्ण
	पूर्ण

	adev->cg_flags &= amdgpu_cg_mask;
	adev->pg_flags &= amdgpu_pg_mask;

	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_device_ip_hw_init_phase1(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, r;

	क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
		अगर (!adev->ip_blocks[i].status.sw)
			जारी;
		अगर (adev->ip_blocks[i].status.hw)
			जारी;
		अगर (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_COMMON ||
		    (amdgpu_sriov_vf(adev) && (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_PSP)) ||
		    adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_IH) अणु
			r = adev->ip_blocks[i].version->funcs->hw_init(adev);
			अगर (r) अणु
				DRM_ERROR("hw_init of IP block <%s> failed %d\n",
					  adev->ip_blocks[i].version->funcs->name, r);
				वापस r;
			पूर्ण
			adev->ip_blocks[i].status.hw = true;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_device_ip_hw_init_phase2(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, r;

	क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
		अगर (!adev->ip_blocks[i].status.sw)
			जारी;
		अगर (adev->ip_blocks[i].status.hw)
			जारी;
		r = adev->ip_blocks[i].version->funcs->hw_init(adev);
		अगर (r) अणु
			DRM_ERROR("hw_init of IP block <%s> failed %d\n",
				  adev->ip_blocks[i].version->funcs->name, r);
			वापस r;
		पूर्ण
		adev->ip_blocks[i].status.hw = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_device_fw_loading(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r = 0;
	पूर्णांक i;
	uपूर्णांक32_t smu_version;

	अगर (adev->asic_type >= CHIP_VEGA10) अणु
		क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
			अगर (adev->ip_blocks[i].version->type != AMD_IP_BLOCK_TYPE_PSP)
				जारी;

			अगर (!adev->ip_blocks[i].status.sw)
				जारी;

			/* no need to करो the fw loading again अगर alपढ़ोy करोne*/
			अगर (adev->ip_blocks[i].status.hw == true)
				अवरोध;

			अगर (amdgpu_in_reset(adev) || adev->in_suspend) अणु
				r = adev->ip_blocks[i].version->funcs->resume(adev);
				अगर (r) अणु
					DRM_ERROR("resume of IP block <%s> failed %d\n",
							  adev->ip_blocks[i].version->funcs->name, r);
					वापस r;
				पूर्ण
			पूर्ण अन्यथा अणु
				r = adev->ip_blocks[i].version->funcs->hw_init(adev);
				अगर (r) अणु
					DRM_ERROR("hw_init of IP block <%s> failed %d\n",
							  adev->ip_blocks[i].version->funcs->name, r);
					वापस r;
				पूर्ण
			पूर्ण

			adev->ip_blocks[i].status.hw = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!amdgpu_sriov_vf(adev) || adev->asic_type == CHIP_TONGA)
		r = amdgpu_pm_load_smu_firmware(adev, &smu_version);

	वापस r;
पूर्ण

/**
 * amdgpu_device_ip_init - run init क्रम hardware IPs
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Main initialization pass क्रम hardware IPs.  The list of all the hardware
 * IPs that make up the asic is walked and the sw_init and hw_init callbacks
 * are run.  sw_init initializes the software state associated with each IP
 * and hw_init initializes the hardware associated with each IP.
 * Returns 0 on success, negative error code on failure.
 */
अटल पूर्णांक amdgpu_device_ip_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, r;

	r = amdgpu_ras_init(adev);
	अगर (r)
		वापस r;

	क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
		अगर (!adev->ip_blocks[i].status.valid)
			जारी;
		r = adev->ip_blocks[i].version->funcs->sw_init((व्योम *)adev);
		अगर (r) अणु
			DRM_ERROR("sw_init of IP block <%s> failed %d\n",
				  adev->ip_blocks[i].version->funcs->name, r);
			जाओ init_failed;
		पूर्ण
		adev->ip_blocks[i].status.sw = true;

		/* need to करो gmc hw init early so we can allocate gpu mem */
		अगर (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_GMC) अणु
			r = amdgpu_device_vram_scratch_init(adev);
			अगर (r) अणु
				DRM_ERROR("amdgpu_vram_scratch_init failed %d\n", r);
				जाओ init_failed;
			पूर्ण
			r = adev->ip_blocks[i].version->funcs->hw_init((व्योम *)adev);
			अगर (r) अणु
				DRM_ERROR("hw_init %d failed %d\n", i, r);
				जाओ init_failed;
			पूर्ण
			r = amdgpu_device_wb_init(adev);
			अगर (r) अणु
				DRM_ERROR("amdgpu_device_wb_init failed %d\n", r);
				जाओ init_failed;
			पूर्ण
			adev->ip_blocks[i].status.hw = true;

			/* right after GMC hw init, we create CSA */
			अगर (amdgpu_mcbp || amdgpu_sriov_vf(adev)) अणु
				r = amdgpu_allocate_अटल_csa(adev, &adev->virt.csa_obj,
								AMDGPU_GEM_DOMAIN_VRAM,
								AMDGPU_CSA_SIZE);
				अगर (r) अणु
					DRM_ERROR("allocate CSA failed %d\n", r);
					जाओ init_failed;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (amdgpu_sriov_vf(adev))
		amdgpu_virt_init_data_exchange(adev);

	r = amdgpu_ib_pool_init(adev);
	अगर (r) अणु
		dev_err(adev->dev, "IB initialization failed (%d).\n", r);
		amdgpu_vf_error_put(adev, AMDGIM_ERROR_VF_IB_INIT_FAIL, 0, r);
		जाओ init_failed;
	पूर्ण

	r = amdgpu_ucode_create_bo(adev); /* create ucode bo when sw_init complete*/
	अगर (r)
		जाओ init_failed;

	r = amdgpu_device_ip_hw_init_phase1(adev);
	अगर (r)
		जाओ init_failed;

	r = amdgpu_device_fw_loading(adev);
	अगर (r)
		जाओ init_failed;

	r = amdgpu_device_ip_hw_init_phase2(adev);
	अगर (r)
		जाओ init_failed;

	/*
	 * retired pages will be loaded from eeprom and reserved here,
	 * it should be called after amdgpu_device_ip_hw_init_phase2  since
	 * क्रम some ASICs the RAS EEPROM code relies on SMU fully functioning
	 * क्रम I2C communication which only true at this poपूर्णांक.
	 *
	 * amdgpu_ras_recovery_init may fail, but the upper only cares the
	 * failure from bad gpu situation and stop amdgpu init process
	 * accordingly. For other failed हालs, it will still release all
	 * the resource and prपूर्णांक error message, rather than वापसing one
	 * negative value to upper level.
	 *
	 * Note: theoretically, this should be called beक्रमe all vram allocations
	 * to protect retired page from abusing
	 */
	r = amdgpu_ras_recovery_init(adev);
	अगर (r)
		जाओ init_failed;

	अगर (adev->gmc.xgmi.num_physical_nodes > 1)
		amdgpu_xgmi_add_device(adev);

	/* Don't init kfd अगर whole hive need to be reset during init */
	अगर (!adev->gmc.xgmi.pending_reset)
		amdgpu_amdkfd_device_init(adev);

	amdgpu_fru_get_product_info(adev);

init_failed:
	अगर (amdgpu_sriov_vf(adev))
		amdgpu_virt_release_full_gpu(adev, true);

	वापस r;
पूर्ण

/**
 * amdgpu_device_fill_reset_magic - ग_लिखोs reset magic to gart poपूर्णांकer
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Writes a reset magic value to the gart poपूर्णांकer in VRAM.  The driver calls
 * this function beक्रमe a GPU reset.  If the value is retained after a
 * GPU reset, VRAM has not been lost.  Some GPU resets may destry VRAM contents.
 */
अटल व्योम amdgpu_device_fill_reset_magic(काष्ठा amdgpu_device *adev)
अणु
	स_नकल(adev->reset_magic, adev->gart.ptr, AMDGPU_RESET_MAGIC_NUM);
पूर्ण

/**
 * amdgpu_device_check_vram_lost - check अगर vram is valid
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Checks the reset magic value written to the gart poपूर्णांकer in VRAM.
 * The driver calls this after a GPU reset to see अगर the contents of
 * VRAM is lost or now.
 * वापसs true अगर vram is lost, false अगर not.
 */
अटल bool amdgpu_device_check_vram_lost(काष्ठा amdgpu_device *adev)
अणु
	अगर (स_भेद(adev->gart.ptr, adev->reset_magic,
			AMDGPU_RESET_MAGIC_NUM))
		वापस true;

	अगर (!amdgpu_in_reset(adev))
		वापस false;

	/*
	 * For all ASICs with baco/mode1 reset, the VRAM is
	 * always assumed to be lost.
	 */
	चयन (amdgpu_asic_reset_method(adev)) अणु
	हाल AMD_RESET_METHOD_BACO:
	हाल AMD_RESET_METHOD_MODE1:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/**
 * amdgpu_device_set_cg_state - set घड़ीgating क्रम amdgpu device
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @state: घड़ीgating state (gate or ungate)
 *
 * The list of all the hardware IPs that make up the asic is walked and the
 * set_घड़ीgating_state callbacks are run.
 * Late initialization pass enabling घड़ीgating क्रम hardware IPs.
 * Fini or suspend, pass disabling घड़ीgating क्रम hardware IPs.
 * Returns 0 on success, negative error code on failure.
 */

पूर्णांक amdgpu_device_set_cg_state(काष्ठा amdgpu_device *adev,
			       क्रमागत amd_घड़ीgating_state state)
अणु
	पूर्णांक i, j, r;

	अगर (amdgpu_emu_mode == 1)
		वापस 0;

	क्रम (j = 0; j < adev->num_ip_blocks; j++) अणु
		i = state == AMD_CG_STATE_GATE ? j : adev->num_ip_blocks - j - 1;
		अगर (!adev->ip_blocks[i].status.late_initialized)
			जारी;
		/* skip CG क्रम GFX on S0ix */
		अगर (adev->in_s0ix &&
		    adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_GFX)
			जारी;
		/* skip CG क्रम VCE/UVD, it's handled specially */
		अगर (adev->ip_blocks[i].version->type != AMD_IP_BLOCK_TYPE_UVD &&
		    adev->ip_blocks[i].version->type != AMD_IP_BLOCK_TYPE_VCE &&
		    adev->ip_blocks[i].version->type != AMD_IP_BLOCK_TYPE_VCN &&
		    adev->ip_blocks[i].version->type != AMD_IP_BLOCK_TYPE_JPEG &&
		    adev->ip_blocks[i].version->funcs->set_घड़ीgating_state) अणु
			/* enable घड़ीgating to save घातer */
			r = adev->ip_blocks[i].version->funcs->set_घड़ीgating_state((व्योम *)adev,
										     state);
			अगर (r) अणु
				DRM_ERROR("set_clockgating_state(gate) of IP block <%s> failed %d\n",
					  adev->ip_blocks[i].version->funcs->name, r);
				वापस r;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक amdgpu_device_set_pg_state(काष्ठा amdgpu_device *adev,
			       क्रमागत amd_घातergating_state state)
अणु
	पूर्णांक i, j, r;

	अगर (amdgpu_emu_mode == 1)
		वापस 0;

	क्रम (j = 0; j < adev->num_ip_blocks; j++) अणु
		i = state == AMD_PG_STATE_GATE ? j : adev->num_ip_blocks - j - 1;
		अगर (!adev->ip_blocks[i].status.late_initialized)
			जारी;
		/* skip PG क्रम GFX on S0ix */
		अगर (adev->in_s0ix &&
		    adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_GFX)
			जारी;
		/* skip CG क्रम VCE/UVD, it's handled specially */
		अगर (adev->ip_blocks[i].version->type != AMD_IP_BLOCK_TYPE_UVD &&
		    adev->ip_blocks[i].version->type != AMD_IP_BLOCK_TYPE_VCE &&
		    adev->ip_blocks[i].version->type != AMD_IP_BLOCK_TYPE_VCN &&
		    adev->ip_blocks[i].version->type != AMD_IP_BLOCK_TYPE_JPEG &&
		    adev->ip_blocks[i].version->funcs->set_घातergating_state) अणु
			/* enable घातergating to save घातer */
			r = adev->ip_blocks[i].version->funcs->set_घातergating_state((व्योम *)adev,
											state);
			अगर (r) अणु
				DRM_ERROR("set_powergating_state(gate) of IP block <%s> failed %d\n",
					  adev->ip_blocks[i].version->funcs->name, r);
				वापस r;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_device_enable_mgpu_fan_boost(व्योम)
अणु
	काष्ठा amdgpu_gpu_instance *gpu_ins;
	काष्ठा amdgpu_device *adev;
	पूर्णांक i, ret = 0;

	mutex_lock(&mgpu_info.mutex);

	/*
	 * MGPU fan boost feature should be enabled
	 * only when there are two or more dGPUs in
	 * the प्रणाली
	 */
	अगर (mgpu_info.num_dgpu < 2)
		जाओ out;

	क्रम (i = 0; i < mgpu_info.num_dgpu; i++) अणु
		gpu_ins = &(mgpu_info.gpu_ins[i]);
		adev = gpu_ins->adev;
		अगर (!(adev->flags & AMD_IS_APU) &&
		    !gpu_ins->mgpu_fan_enabled) अणु
			ret = amdgpu_dpm_enable_mgpu_fan_boost(adev);
			अगर (ret)
				अवरोध;

			gpu_ins->mgpu_fan_enabled = 1;
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&mgpu_info.mutex);

	वापस ret;
पूर्ण

/**
 * amdgpu_device_ip_late_init - run late init क्रम hardware IPs
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Late initialization pass क्रम hardware IPs.  The list of all the hardware
 * IPs that make up the asic is walked and the late_init callbacks are run.
 * late_init covers any special initialization that an IP requires
 * after all of the have been initialized or something that needs to happen
 * late in the init process.
 * Returns 0 on success, negative error code on failure.
 */
अटल पूर्णांक amdgpu_device_ip_late_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_gpu_instance *gpu_instance;
	पूर्णांक i = 0, r;

	क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
		अगर (!adev->ip_blocks[i].status.hw)
			जारी;
		अगर (adev->ip_blocks[i].version->funcs->late_init) अणु
			r = adev->ip_blocks[i].version->funcs->late_init((व्योम *)adev);
			अगर (r) अणु
				DRM_ERROR("late_init of IP block <%s> failed %d\n",
					  adev->ip_blocks[i].version->funcs->name, r);
				वापस r;
			पूर्ण
		पूर्ण
		adev->ip_blocks[i].status.late_initialized = true;
	पूर्ण

	amdgpu_ras_set_error_query_पढ़ोy(adev, true);

	amdgpu_device_set_cg_state(adev, AMD_CG_STATE_GATE);
	amdgpu_device_set_pg_state(adev, AMD_PG_STATE_GATE);

	amdgpu_device_fill_reset_magic(adev);

	r = amdgpu_device_enable_mgpu_fan_boost();
	अगर (r)
		DRM_ERROR("enable mgpu fan boost failed (%d).\n", r);

	/* For XGMI + passthrough configuration on arcturus, enable light SBR */
	अगर (adev->asic_type == CHIP_ARCTURUS &&
	    amdgpu_passthrough(adev) &&
	    adev->gmc.xgmi.num_physical_nodes > 1)
		smu_set_light_sbr(&adev->smu, true);

	अगर (adev->gmc.xgmi.num_physical_nodes > 1) अणु
		mutex_lock(&mgpu_info.mutex);

		/*
		 * Reset device p-state to low as this was booted with high.
		 *
		 * This should be perक्रमmed only after all devices from the same
		 * hive get initialized.
		 *
		 * However, it's unknown how many device in the hive in advance.
		 * As this is counted one by one during devices initializations.
		 *
		 * So, we रुको क्रम all XGMI पूर्णांकerlinked devices initialized.
		 * This may bring some delays as those devices may come from
		 * dअगरferent hives. But that should be OK.
		 */
		अगर (mgpu_info.num_dgpu == adev->gmc.xgmi.num_physical_nodes) अणु
			क्रम (i = 0; i < mgpu_info.num_gpu; i++) अणु
				gpu_instance = &(mgpu_info.gpu_ins[i]);
				अगर (gpu_instance->adev->flags & AMD_IS_APU)
					जारी;

				r = amdgpu_xgmi_set_pstate(gpu_instance->adev,
						AMDGPU_XGMI_PSTATE_MIN);
				अगर (r) अणु
					DRM_ERROR("pstate setting failed (%d).\n", r);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		mutex_unlock(&mgpu_info.mutex);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_device_ip_fini - run fini क्रम hardware IPs
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Main tearकरोwn pass क्रम hardware IPs.  The list of all the hardware
 * IPs that make up the asic is walked and the hw_fini and sw_fini callbacks
 * are run.  hw_fini tears करोwn the hardware associated with each IP
 * and sw_fini tears करोwn any software state associated with each IP.
 * Returns 0 on success, negative error code on failure.
 */
अटल पूर्णांक amdgpu_device_ip_fini(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, r;

	अगर (amdgpu_sriov_vf(adev) && adev->virt.ras_init_करोne)
		amdgpu_virt_release_ras_err_handler_data(adev);

	amdgpu_ras_pre_fini(adev);

	अगर (adev->gmc.xgmi.num_physical_nodes > 1)
		amdgpu_xgmi_हटाओ_device(adev);

	amdgpu_device_set_pg_state(adev, AMD_PG_STATE_UNGATE);
	amdgpu_device_set_cg_state(adev, AMD_CG_STATE_UNGATE);

	amdgpu_amdkfd_device_fini(adev);

	/* need to disable SMC first */
	क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
		अगर (!adev->ip_blocks[i].status.hw)
			जारी;
		अगर (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_SMC) अणु
			r = adev->ip_blocks[i].version->funcs->hw_fini((व्योम *)adev);
			/* XXX handle errors */
			अगर (r) अणु
				DRM_DEBUG("hw_fini of IP block <%s> failed %d\n",
					  adev->ip_blocks[i].version->funcs->name, r);
			पूर्ण
			adev->ip_blocks[i].status.hw = false;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = adev->num_ip_blocks - 1; i >= 0; i--) अणु
		अगर (!adev->ip_blocks[i].status.hw)
			जारी;

		r = adev->ip_blocks[i].version->funcs->hw_fini((व्योम *)adev);
		/* XXX handle errors */
		अगर (r) अणु
			DRM_DEBUG("hw_fini of IP block <%s> failed %d\n",
				  adev->ip_blocks[i].version->funcs->name, r);
		पूर्ण

		adev->ip_blocks[i].status.hw = false;
	पूर्ण


	क्रम (i = adev->num_ip_blocks - 1; i >= 0; i--) अणु
		अगर (!adev->ip_blocks[i].status.sw)
			जारी;

		अगर (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_GMC) अणु
			amdgpu_ucode_मुक्त_bo(adev);
			amdgpu_मुक्त_अटल_csa(&adev->virt.csa_obj);
			amdgpu_device_wb_fini(adev);
			amdgpu_device_vram_scratch_fini(adev);
			amdgpu_ib_pool_fini(adev);
		पूर्ण

		r = adev->ip_blocks[i].version->funcs->sw_fini((व्योम *)adev);
		/* XXX handle errors */
		अगर (r) अणु
			DRM_DEBUG("sw_fini of IP block <%s> failed %d\n",
				  adev->ip_blocks[i].version->funcs->name, r);
		पूर्ण
		adev->ip_blocks[i].status.sw = false;
		adev->ip_blocks[i].status.valid = false;
	पूर्ण

	क्रम (i = adev->num_ip_blocks - 1; i >= 0; i--) अणु
		अगर (!adev->ip_blocks[i].status.late_initialized)
			जारी;
		अगर (adev->ip_blocks[i].version->funcs->late_fini)
			adev->ip_blocks[i].version->funcs->late_fini((व्योम *)adev);
		adev->ip_blocks[i].status.late_initialized = false;
	पूर्ण

	amdgpu_ras_fini(adev);

	अगर (amdgpu_sriov_vf(adev))
		अगर (amdgpu_virt_release_full_gpu(adev, false))
			DRM_ERROR("failed to release exclusive mode on fini\n");

	वापस 0;
पूर्ण

/**
 * amdgpu_device_delayed_init_work_handler - work handler क्रम IB tests
 *
 * @work: work_काष्ठा.
 */
अटल व्योम amdgpu_device_delayed_init_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा amdgpu_device *adev =
		container_of(work, काष्ठा amdgpu_device, delayed_init_work.work);
	पूर्णांक r;

	r = amdgpu_ib_ring_tests(adev);
	अगर (r)
		DRM_ERROR("ib ring test failed (%d).\n", r);
पूर्ण

अटल व्योम amdgpu_device_delay_enable_gfx_off(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा amdgpu_device *adev =
		container_of(work, काष्ठा amdgpu_device, gfx.gfx_off_delay_work.work);

	mutex_lock(&adev->gfx.gfx_off_mutex);
	अगर (!adev->gfx.gfx_off_state && !adev->gfx.gfx_off_req_count) अणु
		अगर (!amdgpu_dpm_set_घातergating_by_smu(adev, AMD_IP_BLOCK_TYPE_GFX, true))
			adev->gfx.gfx_off_state = true;
	पूर्ण
	mutex_unlock(&adev->gfx.gfx_off_mutex);
पूर्ण

/**
 * amdgpu_device_ip_suspend_phase1 - run suspend क्रम hardware IPs (phase 1)
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Main suspend function क्रम hardware IPs.  The list of all the hardware
 * IPs that make up the asic is walked, घड़ीgating is disabled and the
 * suspend callbacks are run.  suspend माला_दो the hardware and software state
 * in each IP पूर्णांकo a state suitable क्रम suspend.
 * Returns 0 on success, negative error code on failure.
 */
अटल पूर्णांक amdgpu_device_ip_suspend_phase1(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, r;

	amdgpu_device_set_pg_state(adev, AMD_PG_STATE_UNGATE);
	amdgpu_device_set_cg_state(adev, AMD_CG_STATE_UNGATE);

	क्रम (i = adev->num_ip_blocks - 1; i >= 0; i--) अणु
		अगर (!adev->ip_blocks[i].status.valid)
			जारी;

		/* displays are handled separately */
		अगर (adev->ip_blocks[i].version->type != AMD_IP_BLOCK_TYPE_DCE)
			जारी;

		/* XXX handle errors */
		r = adev->ip_blocks[i].version->funcs->suspend(adev);
		/* XXX handle errors */
		अगर (r) अणु
			DRM_ERROR("suspend of IP block <%s> failed %d\n",
				  adev->ip_blocks[i].version->funcs->name, r);
			वापस r;
		पूर्ण

		adev->ip_blocks[i].status.hw = false;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_device_ip_suspend_phase2 - run suspend क्रम hardware IPs (phase 2)
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Main suspend function क्रम hardware IPs.  The list of all the hardware
 * IPs that make up the asic is walked, घड़ीgating is disabled and the
 * suspend callbacks are run.  suspend माला_दो the hardware and software state
 * in each IP पूर्णांकo a state suitable क्रम suspend.
 * Returns 0 on success, negative error code on failure.
 */
अटल पूर्णांक amdgpu_device_ip_suspend_phase2(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, r;

	अगर (adev->in_s0ix)
		amdgpu_gfx_state_change_set(adev, sGpuChangeState_D3Entry);

	क्रम (i = adev->num_ip_blocks - 1; i >= 0; i--) अणु
		अगर (!adev->ip_blocks[i].status.valid)
			जारी;
		/* displays are handled in phase1 */
		अगर (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_DCE)
			जारी;
		/* PSP lost connection when err_event_athub occurs */
		अगर (amdgpu_ras_पूर्णांकr_triggered() &&
		    adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_PSP) अणु
			adev->ip_blocks[i].status.hw = false;
			जारी;
		पूर्ण

		/* skip unnecessary suspend अगर we करो not initialize them yet */
		अगर (adev->gmc.xgmi.pending_reset &&
		    !(adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_GMC ||
		      adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_SMC ||
		      adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_COMMON ||
		      adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_IH)) अणु
			adev->ip_blocks[i].status.hw = false;
			जारी;
		पूर्ण

		/* skip suspend of gfx and psp क्रम S0ix
		 * gfx is in gfxoff state, so on resume it will निकास gfxoff just
		 * like at runसमय. PSP is also part of the always on hardware
		 * so no need to suspend it.
		 */
		अगर (adev->in_s0ix &&
		    (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_PSP ||
		     adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_GFX))
			जारी;

		/* XXX handle errors */
		r = adev->ip_blocks[i].version->funcs->suspend(adev);
		/* XXX handle errors */
		अगर (r) अणु
			DRM_ERROR("suspend of IP block <%s> failed %d\n",
				  adev->ip_blocks[i].version->funcs->name, r);
		पूर्ण
		adev->ip_blocks[i].status.hw = false;
		/* handle putting the SMC in the appropriate state */
		अगर(!amdgpu_sriov_vf(adev))अणु
			अगर (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_SMC) अणु
				r = amdgpu_dpm_set_mp1_state(adev, adev->mp1_state);
				अगर (r) अणु
					DRM_ERROR("SMC failed to set mp1 state %d, %d\n",
							adev->mp1_state, r);
					वापस r;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_device_ip_suspend - run suspend क्रम hardware IPs
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Main suspend function क्रम hardware IPs.  The list of all the hardware
 * IPs that make up the asic is walked, घड़ीgating is disabled and the
 * suspend callbacks are run.  suspend माला_दो the hardware and software state
 * in each IP पूर्णांकo a state suitable क्रम suspend.
 * Returns 0 on success, negative error code on failure.
 */
पूर्णांक amdgpu_device_ip_suspend(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	अगर (amdgpu_sriov_vf(adev)) अणु
		amdgpu_virt_fini_data_exchange(adev);
		amdgpu_virt_request_full_gpu(adev, false);
	पूर्ण

	r = amdgpu_device_ip_suspend_phase1(adev);
	अगर (r)
		वापस r;
	r = amdgpu_device_ip_suspend_phase2(adev);

	अगर (amdgpu_sriov_vf(adev))
		amdgpu_virt_release_full_gpu(adev, false);

	वापस r;
पूर्ण

अटल पूर्णांक amdgpu_device_ip_reinit_early_sriov(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, r;

	अटल क्रमागत amd_ip_block_type ip_order[] = अणु
		AMD_IP_BLOCK_TYPE_GMC,
		AMD_IP_BLOCK_TYPE_COMMON,
		AMD_IP_BLOCK_TYPE_PSP,
		AMD_IP_BLOCK_TYPE_IH,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(ip_order); i++) अणु
		पूर्णांक j;
		काष्ठा amdgpu_ip_block *block;

		block = &adev->ip_blocks[i];
		block->status.hw = false;

		क्रम (j = 0; j < ARRAY_SIZE(ip_order); j++) अणु

			अगर (block->version->type != ip_order[j] ||
				!block->status.valid)
				जारी;

			r = block->version->funcs->hw_init(adev);
			DRM_INFO("RE-INIT-early: %s %s\n", block->version->funcs->name, r?"failed":"succeeded");
			अगर (r)
				वापस r;
			block->status.hw = true;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_device_ip_reinit_late_sriov(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, r;

	अटल क्रमागत amd_ip_block_type ip_order[] = अणु
		AMD_IP_BLOCK_TYPE_SMC,
		AMD_IP_BLOCK_TYPE_DCE,
		AMD_IP_BLOCK_TYPE_GFX,
		AMD_IP_BLOCK_TYPE_SDMA,
		AMD_IP_BLOCK_TYPE_UVD,
		AMD_IP_BLOCK_TYPE_VCE,
		AMD_IP_BLOCK_TYPE_VCN
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(ip_order); i++) अणु
		पूर्णांक j;
		काष्ठा amdgpu_ip_block *block;

		क्रम (j = 0; j < adev->num_ip_blocks; j++) अणु
			block = &adev->ip_blocks[j];

			अगर (block->version->type != ip_order[i] ||
				!block->status.valid ||
				block->status.hw)
				जारी;

			अगर (block->version->type == AMD_IP_BLOCK_TYPE_SMC)
				r = block->version->funcs->resume(adev);
			अन्यथा
				r = block->version->funcs->hw_init(adev);

			DRM_INFO("RE-INIT-late: %s %s\n", block->version->funcs->name, r?"failed":"succeeded");
			अगर (r)
				वापस r;
			block->status.hw = true;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_device_ip_resume_phase1 - run resume क्रम hardware IPs
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * First resume function क्रम hardware IPs.  The list of all the hardware
 * IPs that make up the asic is walked and the resume callbacks are run क्रम
 * COMMON, GMC, and IH.  resume माला_दो the hardware पूर्णांकo a functional state
 * after a suspend and updates the software state as necessary.  This
 * function is also used क्रम restoring the GPU after a GPU reset.
 * Returns 0 on success, negative error code on failure.
 */
अटल पूर्णांक amdgpu_device_ip_resume_phase1(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, r;

	क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
		अगर (!adev->ip_blocks[i].status.valid || adev->ip_blocks[i].status.hw)
			जारी;
		अगर (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_COMMON ||
		    adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_GMC ||
		    adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_IH) अणु

			r = adev->ip_blocks[i].version->funcs->resume(adev);
			अगर (r) अणु
				DRM_ERROR("resume of IP block <%s> failed %d\n",
					  adev->ip_blocks[i].version->funcs->name, r);
				वापस r;
			पूर्ण
			adev->ip_blocks[i].status.hw = true;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_device_ip_resume_phase2 - run resume क्रम hardware IPs
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * First resume function क्रम hardware IPs.  The list of all the hardware
 * IPs that make up the asic is walked and the resume callbacks are run क्रम
 * all blocks except COMMON, GMC, and IH.  resume माला_दो the hardware पूर्णांकo a
 * functional state after a suspend and updates the software state as
 * necessary.  This function is also used क्रम restoring the GPU after a GPU
 * reset.
 * Returns 0 on success, negative error code on failure.
 */
अटल पूर्णांक amdgpu_device_ip_resume_phase2(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, r;

	क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
		अगर (!adev->ip_blocks[i].status.valid || adev->ip_blocks[i].status.hw)
			जारी;
		अगर (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_COMMON ||
		    adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_GMC ||
		    adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_IH ||
		    adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_PSP)
			जारी;
		r = adev->ip_blocks[i].version->funcs->resume(adev);
		अगर (r) अणु
			DRM_ERROR("resume of IP block <%s> failed %d\n",
				  adev->ip_blocks[i].version->funcs->name, r);
			वापस r;
		पूर्ण
		adev->ip_blocks[i].status.hw = true;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_device_ip_resume - run resume क्रम hardware IPs
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Main resume function क्रम hardware IPs.  The hardware IPs
 * are split पूर्णांकo two resume functions because they are
 * are also used in in recovering from a GPU reset and some additional
 * steps need to be take between them.  In this हाल (S3/S4) they are
 * run sequentially.
 * Returns 0 on success, negative error code on failure.
 */
अटल पूर्णांक amdgpu_device_ip_resume(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	r = amdgpu_device_ip_resume_phase1(adev);
	अगर (r)
		वापस r;

	r = amdgpu_device_fw_loading(adev);
	अगर (r)
		वापस r;

	r = amdgpu_device_ip_resume_phase2(adev);

	वापस r;
पूर्ण

/**
 * amdgpu_device_detect_sriov_bios - determine अगर the board supports SR-IOV
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Query the VBIOS data tables to determine अगर the board supports SR-IOV.
 */
अटल व्योम amdgpu_device_detect_sriov_bios(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_sriov_vf(adev)) अणु
		अगर (adev->is_atom_fw) अणु
			अगर (amdgpu_atomfirmware_gpu_supports_भवization(adev))
				adev->virt.caps |= AMDGPU_SRIOV_CAPS_SRIOV_VBIOS;
		पूर्ण अन्यथा अणु
			अगर (amdgpu_atombios_has_gpu_भवization_table(adev))
				adev->virt.caps |= AMDGPU_SRIOV_CAPS_SRIOV_VBIOS;
		पूर्ण

		अगर (!(adev->virt.caps & AMDGPU_SRIOV_CAPS_SRIOV_VBIOS))
			amdgpu_vf_error_put(adev, AMDGIM_ERROR_VF_NO_VBIOS, 0, 0);
	पूर्ण
पूर्ण

/**
 * amdgpu_device_asic_has_dc_support - determine अगर DC supports the asic
 *
 * @asic_type: AMD asic type
 *
 * Check अगर there is DC (new modesetting infraकाष्ठाre) support क्रम an asic.
 * वापसs true अगर DC has support, false अगर not.
 */
bool amdgpu_device_asic_has_dc_support(क्रमागत amd_asic_type asic_type)
अणु
	चयन (asic_type) अणु
#अगर defined(CONFIG_DRM_AMD_DC)
#अगर defined(CONFIG_DRM_AMD_DC_SI)
	हाल CHIP_TAHITI:
	हाल CHIP_PITCAIRN:
	हाल CHIP_VERDE:
	हाल CHIP_OLAND:
#पूर्ण_अगर
	हाल CHIP_BONAIRE:
	हाल CHIP_KAVERI:
	हाल CHIP_KABINI:
	हाल CHIP_MULLINS:
		/*
		 * We have प्रणालीs in the wild with these ASICs that require
		 * LVDS and VGA support which is not supported with DC.
		 *
		 * Fallback to the non-DC driver here by शेष so as not to
		 * cause regressions.
		 */
		वापस amdgpu_dc > 0;
	हाल CHIP_HAWAII:
	हाल CHIP_CARRIZO:
	हाल CHIP_STONEY:
	हाल CHIP_POLARIS10:
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
	हाल CHIP_VEGAM:
	हाल CHIP_TONGA:
	हाल CHIP_FIJI:
	हाल CHIP_VEGA10:
	हाल CHIP_VEGA12:
	हाल CHIP_VEGA20:
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	हाल CHIP_RAVEN:
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI14:
	हाल CHIP_NAVI12:
	हाल CHIP_RENOIR:
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_DIMGREY_CAVEFISH:
	हाल CHIP_VANGOGH:
#पूर्ण_अगर
		वापस amdgpu_dc != 0;
#पूर्ण_अगर
	शेष:
		अगर (amdgpu_dc > 0)
			DRM_INFO_ONCE("Display Core has been requested via kernel parameter "
					 "but isn't supported by ASIC, ignoring\n");
		वापस false;
	पूर्ण
पूर्ण

/**
 * amdgpu_device_has_dc_support - check अगर dc is supported
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Returns true क्रम supported, false क्रम not supported
 */
bool amdgpu_device_has_dc_support(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_sriov_vf(adev) || 
	    adev->enable_भव_display ||
	    (adev->harvest_ip_mask & AMD_HARVEST_IP_DMU_MASK))
		वापस false;

	वापस amdgpu_device_asic_has_dc_support(adev->asic_type);
पूर्ण

अटल व्योम amdgpu_device_xgmi_reset_func(काष्ठा work_काष्ठा *__work)
अणु
	काष्ठा amdgpu_device *adev =
		container_of(__work, काष्ठा amdgpu_device, xgmi_reset_work);
	काष्ठा amdgpu_hive_info *hive = amdgpu_get_xgmi_hive(adev);

	/* It's a bug to not have a hive within this function */
	अगर (WARN_ON(!hive))
		वापस;

	/*
	 * Use task barrier to synchronize all xgmi reset works across the
	 * hive. task_barrier_enter and task_barrier_निकास will block
	 * until all the thपढ़ोs running the xgmi reset works reach
	 * those poपूर्णांकs. task_barrier_full will करो both blocks.
	 */
	अगर (amdgpu_asic_reset_method(adev) == AMD_RESET_METHOD_BACO) अणु

		task_barrier_enter(&hive->tb);
		adev->asic_reset_res = amdgpu_device_baco_enter(adev_to_drm(adev));

		अगर (adev->asic_reset_res)
			जाओ fail;

		task_barrier_निकास(&hive->tb);
		adev->asic_reset_res = amdgpu_device_baco_निकास(adev_to_drm(adev));

		अगर (adev->asic_reset_res)
			जाओ fail;

		अगर (adev->mmhub.ras_funcs &&
		    adev->mmhub.ras_funcs->reset_ras_error_count)
			adev->mmhub.ras_funcs->reset_ras_error_count(adev);
	पूर्ण अन्यथा अणु

		task_barrier_full(&hive->tb);
		adev->asic_reset_res =  amdgpu_asic_reset(adev);
	पूर्ण

fail:
	अगर (adev->asic_reset_res)
		DRM_WARN("ASIC reset failed with error, %d for drm dev, %s",
			 adev->asic_reset_res, adev_to_drm(adev)->unique);
	amdgpu_put_xgmi_hive(hive);
पूर्ण

अटल पूर्णांक amdgpu_device_get_job_समयout_settings(काष्ठा amdgpu_device *adev)
अणु
	अक्षर *input = amdgpu_lockup_समयout;
	अक्षर *समयout_setting = शून्य;
	पूर्णांक index = 0;
	दीर्घ समयout;
	पूर्णांक ret = 0;

	/*
	 * By शेष समयout क्रम non compute jobs is 10000.
	 * And there is no समयout enक्रमced on compute jobs.
	 * In SR-IOV or passthrough mode, समयout क्रम compute
	 * jobs are 60000 by शेष.
	 */
	adev->gfx_समयout = msecs_to_jअगरfies(10000);
	adev->sdma_समयout = adev->video_समयout = adev->gfx_समयout;
	अगर (amdgpu_sriov_vf(adev))
		adev->compute_समयout = amdgpu_sriov_is_pp_one_vf(adev) ?
					msecs_to_jअगरfies(60000) : msecs_to_jअगरfies(10000);
	अन्यथा अगर (amdgpu_passthrough(adev))
		adev->compute_समयout =  msecs_to_jअगरfies(60000);
	अन्यथा
		adev->compute_समयout = MAX_SCHEDULE_TIMEOUT;

	अगर (strnlen(input, AMDGPU_MAX_TIMEOUT_PARAM_LENGTH)) अणु
		जबतक ((समयout_setting = strsep(&input, ",")) &&
				strnlen(समयout_setting, AMDGPU_MAX_TIMEOUT_PARAM_LENGTH)) अणु
			ret = kम_से_दीर्घ(समयout_setting, 0, &समयout);
			अगर (ret)
				वापस ret;

			अगर (समयout == 0) अणु
				index++;
				जारी;
			पूर्ण अन्यथा अगर (समयout < 0) अणु
				समयout = MAX_SCHEDULE_TIMEOUT;
			पूर्ण अन्यथा अणु
				समयout = msecs_to_jअगरfies(समयout);
			पूर्ण

			चयन (index++) अणु
			हाल 0:
				adev->gfx_समयout = समयout;
				अवरोध;
			हाल 1:
				adev->compute_समयout = समयout;
				अवरोध;
			हाल 2:
				adev->sdma_समयout = समयout;
				अवरोध;
			हाल 3:
				adev->video_समयout = समयout;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		/*
		 * There is only one value specअगरied and
		 * it should apply to all non-compute jobs.
		 */
		अगर (index == 1) अणु
			adev->sdma_समयout = adev->video_समयout = adev->gfx_समयout;
			अगर (amdgpu_sriov_vf(adev) || amdgpu_passthrough(adev))
				adev->compute_समयout = adev->gfx_समयout;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा attribute *amdgpu_dev_attributes[] = अणु
	&dev_attr_product_name.attr,
	&dev_attr_product_number.attr,
	&dev_attr_serial_number.attr,
	&dev_attr_pcie_replay_count.attr,
	शून्य
पूर्ण;


/**
 * amdgpu_device_init - initialize the driver
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @flags: driver flags
 *
 * Initializes the driver info and hw (all asics).
 * Returns 0 क्रम success or an error on failure.
 * Called at driver startup.
 */
पूर्णांक amdgpu_device_init(काष्ठा amdgpu_device *adev,
		       uपूर्णांक32_t flags)
अणु
	काष्ठा drm_device *ddev = adev_to_drm(adev);
	काष्ठा pci_dev *pdev = adev->pdev;
	पूर्णांक r, i;
	bool px = false;
	u32 max_MBps;

	adev->shutकरोwn = false;
	adev->flags = flags;

	अगर (amdgpu_क्रमce_asic_type >= 0 && amdgpu_क्रमce_asic_type < CHIP_LAST)
		adev->asic_type = amdgpu_क्रमce_asic_type;
	अन्यथा
		adev->asic_type = flags & AMD_ASIC_MASK;

	adev->usec_समयout = AMDGPU_MAX_USEC_TIMEOUT;
	अगर (amdgpu_emu_mode == 1)
		adev->usec_समयout *= 10;
	adev->gmc.gart_size = 512 * 1024 * 1024;
	adev->accel_working = false;
	adev->num_rings = 0;
	adev->mman.buffer_funcs = शून्य;
	adev->mman.buffer_funcs_ring = शून्य;
	adev->vm_manager.vm_pte_funcs = शून्य;
	adev->vm_manager.vm_pte_num_scheds = 0;
	adev->gmc.gmc_funcs = शून्य;
	adev->harvest_ip_mask = 0x0;
	adev->fence_context = dma_fence_context_alloc(AMDGPU_MAX_RINGS);
	biपंचांगap_zero(adev->gfx.pipe_reserve_biपंचांगap, AMDGPU_MAX_COMPUTE_QUEUES);

	adev->smc_rreg = &amdgpu_invalid_rreg;
	adev->smc_wreg = &amdgpu_invalid_wreg;
	adev->pcie_rreg = &amdgpu_invalid_rreg;
	adev->pcie_wreg = &amdgpu_invalid_wreg;
	adev->pciep_rreg = &amdgpu_invalid_rreg;
	adev->pciep_wreg = &amdgpu_invalid_wreg;
	adev->pcie_rreg64 = &amdgpu_invalid_rreg64;
	adev->pcie_wreg64 = &amdgpu_invalid_wreg64;
	adev->uvd_ctx_rreg = &amdgpu_invalid_rreg;
	adev->uvd_ctx_wreg = &amdgpu_invalid_wreg;
	adev->didt_rreg = &amdgpu_invalid_rreg;
	adev->didt_wreg = &amdgpu_invalid_wreg;
	adev->gc_cac_rreg = &amdgpu_invalid_rreg;
	adev->gc_cac_wreg = &amdgpu_invalid_wreg;
	adev->audio_endpt_rreg = &amdgpu_block_invalid_rreg;
	adev->audio_endpt_wreg = &amdgpu_block_invalid_wreg;

	DRM_INFO("initializing kernel modesetting (%s 0x%04X:0x%04X 0x%04X:0x%04X 0x%02X).\n",
		 amdgpu_asic_name[adev->asic_type], pdev->venकरोr, pdev->device,
		 pdev->subप्रणाली_venकरोr, pdev->subप्रणाली_device, pdev->revision);

	/* mutex initialization are all करोne here so we
	 * can recall function without having locking issues */
	mutex_init(&adev->firmware.mutex);
	mutex_init(&adev->pm.mutex);
	mutex_init(&adev->gfx.gpu_घड़ी_mutex);
	mutex_init(&adev->srbm_mutex);
	mutex_init(&adev->gfx.pipe_reserve_mutex);
	mutex_init(&adev->gfx.gfx_off_mutex);
	mutex_init(&adev->grbm_idx_mutex);
	mutex_init(&adev->mn_lock);
	mutex_init(&adev->virt.vf_errors.lock);
	hash_init(adev->mn_hash);
	atomic_set(&adev->in_gpu_reset, 0);
	init_rwsem(&adev->reset_sem);
	mutex_init(&adev->psp.mutex);
	mutex_init(&adev->notअगरier_lock);

	r = amdgpu_device_check_arguments(adev);
	अगर (r)
		वापस r;

	spin_lock_init(&adev->mmio_idx_lock);
	spin_lock_init(&adev->smc_idx_lock);
	spin_lock_init(&adev->pcie_idx_lock);
	spin_lock_init(&adev->uvd_ctx_idx_lock);
	spin_lock_init(&adev->didt_idx_lock);
	spin_lock_init(&adev->gc_cac_idx_lock);
	spin_lock_init(&adev->se_cac_idx_lock);
	spin_lock_init(&adev->audio_endpt_idx_lock);
	spin_lock_init(&adev->mm_stats.lock);

	INIT_LIST_HEAD(&adev->shaकरोw_list);
	mutex_init(&adev->shaकरोw_list_lock);

	INIT_LIST_HEAD(&adev->reset_list);

	INIT_DELAYED_WORK(&adev->delayed_init_work,
			  amdgpu_device_delayed_init_work_handler);
	INIT_DELAYED_WORK(&adev->gfx.gfx_off_delay_work,
			  amdgpu_device_delay_enable_gfx_off);

	INIT_WORK(&adev->xgmi_reset_work, amdgpu_device_xgmi_reset_func);

	adev->gfx.gfx_off_req_count = 1;
	adev->pm.ac_घातer = घातer_supply_is_प्रणाली_supplied() > 0;

	atomic_set(&adev->throttling_logging_enabled, 1);
	/*
	 * If throttling जारीs, logging will be perक्रमmed every minute
	 * to aव्योम log flooding. "-1" is subtracted since the thermal
	 * throttling पूर्णांकerrupt comes every second. Thus, the total logging
	 * पूर्णांकerval is 59 seconds(retelimited prपूर्णांकk पूर्णांकerval) + 1(रुकोing
	 * क्रम throttling पूर्णांकerrupt) = 60 seconds.
	 */
	ratelimit_state_init(&adev->throttling_logging_rs, (60 - 1) * HZ, 1);
	ratelimit_set_flags(&adev->throttling_logging_rs, RATELIMIT_MSG_ON_RELEASE);

	/* Registers mapping */
	/* TODO: block userspace mapping of io रेजिस्टर */
	अगर (adev->asic_type >= CHIP_BONAIRE) अणु
		adev->rmmio_base = pci_resource_start(adev->pdev, 5);
		adev->rmmio_size = pci_resource_len(adev->pdev, 5);
	पूर्ण अन्यथा अणु
		adev->rmmio_base = pci_resource_start(adev->pdev, 2);
		adev->rmmio_size = pci_resource_len(adev->pdev, 2);
	पूर्ण

	adev->rmmio = ioremap(adev->rmmio_base, adev->rmmio_size);
	अगर (adev->rmmio == शून्य) अणु
		वापस -ENOMEM;
	पूर्ण
	DRM_INFO("register mmio base: 0x%08X\n", (uपूर्णांक32_t)adev->rmmio_base);
	DRM_INFO("register mmio size: %u\n", (अचिन्हित)adev->rmmio_size);

	/* enable PCIE atomic ops */
	r = pci_enable_atomic_ops_to_root(adev->pdev,
					  PCI_EXP_DEVCAP2_ATOMIC_COMP32 |
					  PCI_EXP_DEVCAP2_ATOMIC_COMP64);
	अगर (r) अणु
		adev->have_atomics_support = false;
		DRM_INFO("PCIE atomic ops is not supported\n");
	पूर्ण अन्यथा अणु
		adev->have_atomics_support = true;
	पूर्ण

	amdgpu_device_get_pcie_info(adev);

	अगर (amdgpu_mcbp)
		DRM_INFO("MCBP is enabled\n");

	अगर (amdgpu_mes && adev->asic_type >= CHIP_NAVI10)
		adev->enable_mes = true;

	/* detect hw भवization here */
	amdgpu_detect_भवization(adev);

	r = amdgpu_device_get_job_समयout_settings(adev);
	अगर (r) अणु
		dev_err(adev->dev, "invalid lockup_timeout parameter syntax\n");
		जाओ failed_unmap;
	पूर्ण

	/* early init functions */
	r = amdgpu_device_ip_early_init(adev);
	अगर (r)
		जाओ failed_unmap;

	/* करोorbell bar mapping and करोorbell index init*/
	amdgpu_device_करोorbell_init(adev);

	अगर (amdgpu_emu_mode == 1) अणु
		/* post the asic on emulation mode */
		emu_soc_asic_init(adev);
		जाओ fence_driver_init;
	पूर्ण

	amdgpu_reset_init(adev);

	/* detect अगर we are with an SRIOV vbios */
	amdgpu_device_detect_sriov_bios(adev);

	/* check अगर we need to reset the asic
	 *  E.g., driver was not cleanly unloaded previously, etc.
	 */
	अगर (!amdgpu_sriov_vf(adev) && amdgpu_asic_need_reset_on_init(adev)) अणु
		अगर (adev->gmc.xgmi.num_physical_nodes) अणु
			dev_info(adev->dev, "Pending hive reset.\n");
			adev->gmc.xgmi.pending_reset = true;
			/* Only need to init necessary block क्रम SMU to handle the reset */
			क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
				अगर (!adev->ip_blocks[i].status.valid)
					जारी;
				अगर (!(adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_GMC ||
				      adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_COMMON ||
				      adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_IH ||
				      adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_SMC)) अणु
					DRM_DEBUG("IP %s disabled for hw_init.\n",
						adev->ip_blocks[i].version->funcs->name);
					adev->ip_blocks[i].status.hw = true;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			r = amdgpu_asic_reset(adev);
			अगर (r) अणु
				dev_err(adev->dev, "asic reset on init failed\n");
				जाओ failed;
			पूर्ण
		पूर्ण
	पूर्ण

	pci_enable_pcie_error_reporting(adev->pdev);

	/* Post card अगर necessary */
	अगर (amdgpu_device_need_post(adev)) अणु
		अगर (!adev->bios) अणु
			dev_err(adev->dev, "no vBIOS found\n");
			r = -EINVAL;
			जाओ failed;
		पूर्ण
		DRM_INFO("GPU posting now...\n");
		r = amdgpu_device_asic_init(adev);
		अगर (r) अणु
			dev_err(adev->dev, "gpu post error!\n");
			जाओ failed;
		पूर्ण
	पूर्ण

	अगर (adev->is_atom_fw) अणु
		/* Initialize घड़ीs */
		r = amdgpu_atomfirmware_get_घड़ी_info(adev);
		अगर (r) अणु
			dev_err(adev->dev, "amdgpu_atomfirmware_get_clock_info failed\n");
			amdgpu_vf_error_put(adev, AMDGIM_ERROR_VF_ATOMBIOS_GET_CLOCK_FAIL, 0, 0);
			जाओ failed;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Initialize घड़ीs */
		r = amdgpu_atombios_get_घड़ी_info(adev);
		अगर (r) अणु
			dev_err(adev->dev, "amdgpu_atombios_get_clock_info failed\n");
			amdgpu_vf_error_put(adev, AMDGIM_ERROR_VF_ATOMBIOS_GET_CLOCK_FAIL, 0, 0);
			जाओ failed;
		पूर्ण
		/* init i2c buses */
		अगर (!amdgpu_device_has_dc_support(adev))
			amdgpu_atombios_i2c_init(adev);
	पूर्ण

fence_driver_init:
	/* Fence driver */
	r = amdgpu_fence_driver_init(adev);
	अगर (r) अणु
		dev_err(adev->dev, "amdgpu_fence_driver_init failed\n");
		amdgpu_vf_error_put(adev, AMDGIM_ERROR_VF_FENCE_INIT_FAIL, 0, 0);
		जाओ failed;
	पूर्ण

	/* init the mode config */
	drm_mode_config_init(adev_to_drm(adev));

	r = amdgpu_device_ip_init(adev);
	अगर (r) अणु
		/* failed in exclusive mode due to समयout */
		अगर (amdgpu_sriov_vf(adev) &&
		    !amdgpu_sriov_runसमय(adev) &&
		    amdgpu_virt_mmio_blocked(adev) &&
		    !amdgpu_virt_रुको_reset(adev)) अणु
			dev_err(adev->dev, "VF exclusive mode timeout\n");
			/* Don't send request since VF is inactive. */
			adev->virt.caps &= ~AMDGPU_SRIOV_CAPS_RUNTIME;
			adev->virt.ops = शून्य;
			r = -EAGAIN;
			जाओ release_ras_con;
		पूर्ण
		dev_err(adev->dev, "amdgpu_device_ip_init failed\n");
		amdgpu_vf_error_put(adev, AMDGIM_ERROR_VF_AMDGPU_INIT_FAIL, 0, 0);
		जाओ release_ras_con;
	पूर्ण

	dev_info(adev->dev,
		"SE %d, SH per SE %d, CU per SH %d, active_cu_number %d\n",
			adev->gfx.config.max_shader_engines,
			adev->gfx.config.max_sh_per_se,
			adev->gfx.config.max_cu_per_sh,
			adev->gfx.cu_info.number);

	adev->accel_working = true;

	amdgpu_vm_check_compute_bug(adev);

	/* Initialize the buffer migration limit. */
	अगर (amdgpu_moverate >= 0)
		max_MBps = amdgpu_moverate;
	अन्यथा
		max_MBps = 8; /* Allow 8 MB/s. */
	/* Get a log2 क्रम easy भागisions. */
	adev->mm_stats.log2_max_MBps = ilog2(max(1u, max_MBps));

	amdgpu_fbdev_init(adev);

	r = amdgpu_pm_sysfs_init(adev);
	अगर (r) अणु
		adev->pm_sysfs_en = false;
		DRM_ERROR("registering pm debugfs failed (%d).\n", r);
	पूर्ण अन्यथा
		adev->pm_sysfs_en = true;

	r = amdgpu_ucode_sysfs_init(adev);
	अगर (r) अणु
		adev->ucode_sysfs_en = false;
		DRM_ERROR("Creating firmware sysfs failed (%d).\n", r);
	पूर्ण अन्यथा
		adev->ucode_sysfs_en = true;

	अगर ((amdgpu_testing & 1)) अणु
		अगर (adev->accel_working)
			amdgpu_test_moves(adev);
		अन्यथा
			DRM_INFO("amdgpu: acceleration disabled, skipping move tests\n");
	पूर्ण
	अगर (amdgpu_benchmarking) अणु
		अगर (adev->accel_working)
			amdgpu_benchmark(adev, amdgpu_benchmarking);
		अन्यथा
			DRM_INFO("amdgpu: acceleration disabled, skipping benchmarks\n");
	पूर्ण

	/*
	 * Register gpu instance beक्रमe amdgpu_device_enable_mgpu_fan_boost.
	 * Otherwise the mgpu fan boost feature will be skipped due to the
	 * gpu instance is counted less.
	 */
	amdgpu_रेजिस्टर_gpu_instance(adev);

	/* enable घड़ीgating, etc. after ib tests, etc. since some blocks require
	 * explicit gating rather than handling it स्वतःmatically.
	 */
	अगर (!adev->gmc.xgmi.pending_reset) अणु
		r = amdgpu_device_ip_late_init(adev);
		अगर (r) अणु
			dev_err(adev->dev, "amdgpu_device_ip_late_init failed\n");
			amdgpu_vf_error_put(adev, AMDGIM_ERROR_VF_AMDGPU_LATE_INIT_FAIL, 0, r);
			जाओ release_ras_con;
		पूर्ण
		/* must succeed. */
		amdgpu_ras_resume(adev);
		queue_delayed_work(प्रणाली_wq, &adev->delayed_init_work,
				   msecs_to_jअगरfies(AMDGPU_RESUME_MS));
	पूर्ण

	अगर (amdgpu_sriov_vf(adev))
		flush_delayed_work(&adev->delayed_init_work);

	r = sysfs_create_files(&adev->dev->kobj, amdgpu_dev_attributes);
	अगर (r)
		dev_err(adev->dev, "Could not create amdgpu device attr\n");

	अगर (IS_ENABLED(CONFIG_PERF_EVENTS))
		r = amdgpu_pmu_init(adev);
	अगर (r)
		dev_err(adev->dev, "amdgpu_pmu_init failed\n");

	/* Have stored pci confspace at hand क्रम restore in sudden PCI error */
	अगर (amdgpu_device_cache_pci_state(adev->pdev))
		pci_restore_state(pdev);

	/* अगर we have > 1 VGA cards, then disable the amdgpu VGA resources */
	/* this will fail क्रम cards that aren't VGA class devices, just
	 * ignore it */
	अगर ((adev->pdev->class >> 8) == PCI_CLASS_DISPLAY_VGA)
		vga_client_रेजिस्टर(adev->pdev, adev, शून्य, amdgpu_device_vga_set_decode);

	अगर (amdgpu_device_supports_px(ddev)) अणु
		px = true;
		vga_चयनeroo_रेजिस्टर_client(adev->pdev,
					       &amdgpu_चयनeroo_ops, px);
		vga_चयनeroo_init_करोमुख्य_pm_ops(adev->dev, &adev->vga_pm_करोमुख्य);
	पूर्ण

	अगर (adev->gmc.xgmi.pending_reset)
		queue_delayed_work(प्रणाली_wq, &mgpu_info.delayed_reset_work,
				   msecs_to_jअगरfies(AMDGPU_RESUME_MS));

	वापस 0;

release_ras_con:
	amdgpu_release_ras_context(adev);

failed:
	amdgpu_vf_error_trans_all(adev);

failed_unmap:
	iounmap(adev->rmmio);
	adev->rmmio = शून्य;

	वापस r;
पूर्ण

/**
 * amdgpu_device_fini - tear करोwn the driver
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Tear करोwn the driver info (all asics).
 * Called at driver shutकरोwn.
 */
व्योम amdgpu_device_fini(काष्ठा amdgpu_device *adev)
अणु
	dev_info(adev->dev, "amdgpu: finishing device.\n");
	flush_delayed_work(&adev->delayed_init_work);
	tपंचांग_bo_lock_delayed_workqueue(&adev->mman.bdev);
	adev->shutकरोwn = true;

	kमुक्त(adev->pci_state);

	/* make sure IB test finished beक्रमe entering exclusive mode
	 * to aव्योम preemption on IB test
	 * */
	अगर (amdgpu_sriov_vf(adev)) अणु
		amdgpu_virt_request_full_gpu(adev, false);
		amdgpu_virt_fini_data_exchange(adev);
	पूर्ण

	/* disable all पूर्णांकerrupts */
	amdgpu_irq_disable_all(adev);
	अगर (adev->mode_info.mode_config_initialized)अणु
		अगर (!amdgpu_device_has_dc_support(adev))
			drm_helper_क्रमce_disable_all(adev_to_drm(adev));
		अन्यथा
			drm_atomic_helper_shutकरोwn(adev_to_drm(adev));
	पूर्ण
	amdgpu_fence_driver_fini(adev);
	अगर (adev->pm_sysfs_en)
		amdgpu_pm_sysfs_fini(adev);
	amdgpu_fbdev_fini(adev);
	amdgpu_device_ip_fini(adev);
	release_firmware(adev->firmware.gpu_info_fw);
	adev->firmware.gpu_info_fw = शून्य;
	adev->accel_working = false;

	amdgpu_reset_fini(adev);

	/* मुक्त i2c buses */
	अगर (!amdgpu_device_has_dc_support(adev))
		amdgpu_i2c_fini(adev);

	अगर (amdgpu_emu_mode != 1)
		amdgpu_atombios_fini(adev);

	kमुक्त(adev->bios);
	adev->bios = शून्य;
	अगर (amdgpu_device_supports_px(adev_to_drm(adev))) अणु
		vga_चयनeroo_unरेजिस्टर_client(adev->pdev);
		vga_चयनeroo_fini_करोमुख्य_pm_ops(adev->dev);
	पूर्ण
	अगर ((adev->pdev->class >> 8) == PCI_CLASS_DISPLAY_VGA)
		vga_client_रेजिस्टर(adev->pdev, शून्य, शून्य, शून्य);
	iounmap(adev->rmmio);
	adev->rmmio = शून्य;
	amdgpu_device_करोorbell_fini(adev);

	अगर (adev->ucode_sysfs_en)
		amdgpu_ucode_sysfs_fini(adev);

	sysfs_हटाओ_files(&adev->dev->kobj, amdgpu_dev_attributes);
	अगर (IS_ENABLED(CONFIG_PERF_EVENTS))
		amdgpu_pmu_fini(adev);
	अगर (adev->mman.discovery_bin)
		amdgpu_discovery_fini(adev);
पूर्ण


/*
 * Suspend & resume.
 */
/**
 * amdgpu_device_suspend - initiate device suspend
 *
 * @dev: drm dev poपूर्णांकer
 * @fbcon : notअगरy the fbdev of suspend
 *
 * Puts the hw in the suspend state (all asics).
 * Returns 0 क्रम success or an error on failure.
 * Called at driver suspend.
 */
पूर्णांक amdgpu_device_suspend(काष्ठा drm_device *dev, bool fbcon)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	पूर्णांक r;

	अगर (dev->चयन_घातer_state == DRM_SWITCH_POWER_OFF)
		वापस 0;

	adev->in_suspend = true;
	drm_kms_helper_poll_disable(dev);

	अगर (fbcon)
		amdgpu_fbdev_set_suspend(adev, 1);

	cancel_delayed_work_sync(&adev->delayed_init_work);

	amdgpu_ras_suspend(adev);

	r = amdgpu_device_ip_suspend_phase1(adev);

	अगर (!adev->in_s0ix)
		amdgpu_amdkfd_suspend(adev, adev->in_runpm);

	/* evict vram memory */
	amdgpu_bo_evict_vram(adev);

	amdgpu_fence_driver_suspend(adev);

	r = amdgpu_device_ip_suspend_phase2(adev);
	/* evict reमुख्यing vram memory
	 * This second call to evict vram is to evict the gart page table
	 * using the CPU.
	 */
	amdgpu_bo_evict_vram(adev);

	वापस 0;
पूर्ण

/**
 * amdgpu_device_resume - initiate device resume
 *
 * @dev: drm dev poपूर्णांकer
 * @fbcon : notअगरy the fbdev of resume
 *
 * Bring the hw back to operating state (all asics).
 * Returns 0 क्रम success or an error on failure.
 * Called at driver resume.
 */
पूर्णांक amdgpu_device_resume(काष्ठा drm_device *dev, bool fbcon)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	पूर्णांक r = 0;

	अगर (dev->चयन_घातer_state == DRM_SWITCH_POWER_OFF)
		वापस 0;

	अगर (adev->in_s0ix)
		amdgpu_gfx_state_change_set(adev, sGpuChangeState_D0Entry);

	/* post card */
	अगर (amdgpu_device_need_post(adev)) अणु
		r = amdgpu_device_asic_init(adev);
		अगर (r)
			dev_err(adev->dev, "amdgpu asic init failed\n");
	पूर्ण

	r = amdgpu_device_ip_resume(adev);
	अगर (r) अणु
		dev_err(adev->dev, "amdgpu_device_ip_resume failed (%d).\n", r);
		वापस r;
	पूर्ण
	amdgpu_fence_driver_resume(adev);


	r = amdgpu_device_ip_late_init(adev);
	अगर (r)
		वापस r;

	queue_delayed_work(प्रणाली_wq, &adev->delayed_init_work,
			   msecs_to_jअगरfies(AMDGPU_RESUME_MS));

	अगर (!adev->in_s0ix) अणु
		r = amdgpu_amdkfd_resume(adev, adev->in_runpm);
		अगर (r)
			वापस r;
	पूर्ण

	/* Make sure IB tests flushed */
	flush_delayed_work(&adev->delayed_init_work);

	अगर (fbcon)
		amdgpu_fbdev_set_suspend(adev, 0);

	drm_kms_helper_poll_enable(dev);

	amdgpu_ras_resume(adev);

	/*
	 * Most of the connector probing functions try to acquire runसमय pm
	 * refs to ensure that the GPU is घातered on when connector polling is
	 * perक्रमmed. Since we're calling this from a runसमय PM callback,
	 * trying to acquire rpm refs will cause us to deadlock.
	 *
	 * Since we're guaranteed to be holding the rpm lock, it's safe to
	 * temporarily disable the rpm helpers so this करोesn't deadlock us.
	 */
#अगर_घोषित CONFIG_PM
	dev->dev->घातer.disable_depth++;
#पूर्ण_अगर
	अगर (!amdgpu_device_has_dc_support(adev))
		drm_helper_hpd_irq_event(dev);
	अन्यथा
		drm_kms_helper_hotplug_event(dev);
#अगर_घोषित CONFIG_PM
	dev->dev->घातer.disable_depth--;
#पूर्ण_अगर
	adev->in_suspend = false;

	वापस 0;
पूर्ण

/**
 * amdgpu_device_ip_check_soft_reset - did soft reset succeed
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * The list of all the hardware IPs that make up the asic is walked and
 * the check_soft_reset callbacks are run.  check_soft_reset determines
 * अगर the asic is still hung or not.
 * Returns true अगर any of the IPs are still in a hung state, false अगर not.
 */
अटल bool amdgpu_device_ip_check_soft_reset(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;
	bool asic_hang = false;

	अगर (amdgpu_sriov_vf(adev))
		वापस true;

	अगर (amdgpu_asic_need_full_reset(adev))
		वापस true;

	क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
		अगर (!adev->ip_blocks[i].status.valid)
			जारी;
		अगर (adev->ip_blocks[i].version->funcs->check_soft_reset)
			adev->ip_blocks[i].status.hang =
				adev->ip_blocks[i].version->funcs->check_soft_reset(adev);
		अगर (adev->ip_blocks[i].status.hang) अणु
			dev_info(adev->dev, "IP block:%s is hung!\n", adev->ip_blocks[i].version->funcs->name);
			asic_hang = true;
		पूर्ण
	पूर्ण
	वापस asic_hang;
पूर्ण

/**
 * amdgpu_device_ip_pre_soft_reset - prepare क्रम soft reset
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * The list of all the hardware IPs that make up the asic is walked and the
 * pre_soft_reset callbacks are run अगर the block is hung.  pre_soft_reset
 * handles any IP specअगरic hardware or software state changes that are
 * necessary क्रम a soft reset to succeed.
 * Returns 0 on success, negative error code on failure.
 */
अटल पूर्णांक amdgpu_device_ip_pre_soft_reset(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, r = 0;

	क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
		अगर (!adev->ip_blocks[i].status.valid)
			जारी;
		अगर (adev->ip_blocks[i].status.hang &&
		    adev->ip_blocks[i].version->funcs->pre_soft_reset) अणु
			r = adev->ip_blocks[i].version->funcs->pre_soft_reset(adev);
			अगर (r)
				वापस r;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_device_ip_need_full_reset - check अगर a full asic reset is needed
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Some hardware IPs cannot be soft reset.  If they are hung, a full gpu
 * reset is necessary to recover.
 * Returns true अगर a full asic reset is required, false अगर not.
 */
अटल bool amdgpu_device_ip_need_full_reset(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	अगर (amdgpu_asic_need_full_reset(adev))
		वापस true;

	क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
		अगर (!adev->ip_blocks[i].status.valid)
			जारी;
		अगर ((adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_GMC) ||
		    (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_SMC) ||
		    (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_ACP) ||
		    (adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_DCE) ||
		     adev->ip_blocks[i].version->type == AMD_IP_BLOCK_TYPE_PSP) अणु
			अगर (adev->ip_blocks[i].status.hang) अणु
				dev_info(adev->dev, "Some block need full reset!\n");
				वापस true;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

/**
 * amdgpu_device_ip_soft_reset - करो a soft reset
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * The list of all the hardware IPs that make up the asic is walked and the
 * soft_reset callbacks are run अगर the block is hung.  soft_reset handles any
 * IP specअगरic hardware or software state changes that are necessary to soft
 * reset the IP.
 * Returns 0 on success, negative error code on failure.
 */
अटल पूर्णांक amdgpu_device_ip_soft_reset(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, r = 0;

	क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
		अगर (!adev->ip_blocks[i].status.valid)
			जारी;
		अगर (adev->ip_blocks[i].status.hang &&
		    adev->ip_blocks[i].version->funcs->soft_reset) अणु
			r = adev->ip_blocks[i].version->funcs->soft_reset(adev);
			अगर (r)
				वापस r;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_device_ip_post_soft_reset - clean up from soft reset
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * The list of all the hardware IPs that make up the asic is walked and the
 * post_soft_reset callbacks are run अगर the asic was hung.  post_soft_reset
 * handles any IP specअगरic hardware or software state changes that are
 * necessary after the IP has been soft reset.
 * Returns 0 on success, negative error code on failure.
 */
अटल पूर्णांक amdgpu_device_ip_post_soft_reset(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, r = 0;

	क्रम (i = 0; i < adev->num_ip_blocks; i++) अणु
		अगर (!adev->ip_blocks[i].status.valid)
			जारी;
		अगर (adev->ip_blocks[i].status.hang &&
		    adev->ip_blocks[i].version->funcs->post_soft_reset)
			r = adev->ip_blocks[i].version->funcs->post_soft_reset(adev);
		अगर (r)
			वापस r;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_device_recover_vram - Recover some VRAM contents
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Restores the contents of VRAM buffers from the shaकरोws in GTT.  Used to
 * restore things like GPUVM page tables after a GPU reset where
 * the contents of VRAM might be lost.
 *
 * Returns:
 * 0 on success, negative error code on failure.
 */
अटल पूर्णांक amdgpu_device_recover_vram(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा dma_fence *fence = शून्य, *next = शून्य;
	काष्ठा amdgpu_bo *shaकरोw;
	दीर्घ r = 1, पंचांगo;

	अगर (amdgpu_sriov_runसमय(adev))
		पंचांगo = msecs_to_jअगरfies(8000);
	अन्यथा
		पंचांगo = msecs_to_jअगरfies(100);

	dev_info(adev->dev, "recover vram bo from shadow start\n");
	mutex_lock(&adev->shaकरोw_list_lock);
	list_क्रम_each_entry(shaकरोw, &adev->shaकरोw_list, shaकरोw_list) अणु

		/* No need to recover an evicted BO */
		अगर (shaकरोw->tbo.mem.mem_type != TTM_PL_TT ||
		    shaकरोw->tbo.mem.start == AMDGPU_BO_INVALID_OFFSET ||
		    shaकरोw->parent->tbo.mem.mem_type != TTM_PL_VRAM)
			जारी;

		r = amdgpu_bo_restore_shaकरोw(shaकरोw, &next);
		अगर (r)
			अवरोध;

		अगर (fence) अणु
			पंचांगo = dma_fence_रुको_समयout(fence, false, पंचांगo);
			dma_fence_put(fence);
			fence = next;
			अगर (पंचांगo == 0) अणु
				r = -ETIMEDOUT;
				अवरोध;
			पूर्ण अन्यथा अगर (पंचांगo < 0) अणु
				r = पंचांगo;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			fence = next;
		पूर्ण
	पूर्ण
	mutex_unlock(&adev->shaकरोw_list_lock);

	अगर (fence)
		पंचांगo = dma_fence_रुको_समयout(fence, false, पंचांगo);
	dma_fence_put(fence);

	अगर (r < 0 || पंचांगo <= 0) अणु
		dev_err(adev->dev, "recover vram bo from shadow failed, r is %ld, tmo is %ld\n", r, पंचांगo);
		वापस -EIO;
	पूर्ण

	dev_info(adev->dev, "recover vram bo from shadow done\n");
	वापस 0;
पूर्ण


/**
 * amdgpu_device_reset_sriov - reset ASIC क्रम SR-IOV vf
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @from_hypervisor: request from hypervisor
 *
 * करो VF FLR and reinitialize Asic
 * वापस 0 means succeeded otherwise failed
 */
अटल पूर्णांक amdgpu_device_reset_sriov(काष्ठा amdgpu_device *adev,
				     bool from_hypervisor)
अणु
	पूर्णांक r;

	अगर (from_hypervisor)
		r = amdgpu_virt_request_full_gpu(adev, true);
	अन्यथा
		r = amdgpu_virt_reset_gpu(adev);
	अगर (r)
		वापस r;

	amdgpu_amdkfd_pre_reset(adev);

	/* Resume IP prior to SMC */
	r = amdgpu_device_ip_reinit_early_sriov(adev);
	अगर (r)
		जाओ error;

	amdgpu_virt_init_data_exchange(adev);
	/* we need recover gart prior to run SMC/CP/SDMA resume */
	amdgpu_gtt_mgr_recover(tपंचांग_manager_type(&adev->mman.bdev, TTM_PL_TT));

	r = amdgpu_device_fw_loading(adev);
	अगर (r)
		वापस r;

	/* now we are okay to resume SMC/CP/SDMA */
	r = amdgpu_device_ip_reinit_late_sriov(adev);
	अगर (r)
		जाओ error;

	amdgpu_irq_gpu_reset_resume_helper(adev);
	r = amdgpu_ib_ring_tests(adev);
	amdgpu_amdkfd_post_reset(adev);

error:
	अगर (!r && adev->virt.gim_feature & AMDGIM_FEATURE_GIM_FLR_VRAMLOST) अणु
		amdgpu_inc_vram_lost(adev);
		r = amdgpu_device_recover_vram(adev);
	पूर्ण
	amdgpu_virt_release_full_gpu(adev, true);

	वापस r;
पूर्ण

/**
 * amdgpu_device_has_job_running - check अगर there is any job in mirror list
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * check अगर there is any job in mirror list
 */
bool amdgpu_device_has_job_running(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;
	काष्ठा drm_sched_job *job;

	क्रम (i = 0; i < AMDGPU_MAX_RINGS; ++i) अणु
		काष्ठा amdgpu_ring *ring = adev->rings[i];

		अगर (!ring || !ring->sched.thपढ़ो)
			जारी;

		spin_lock(&ring->sched.job_list_lock);
		job = list_first_entry_or_null(&ring->sched.pending_list,
					       काष्ठा drm_sched_job, list);
		spin_unlock(&ring->sched.job_list_lock);
		अगर (job)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * amdgpu_device_should_recover_gpu - check अगर we should try GPU recovery
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Check amdgpu_gpu_recovery and SRIOV status to see अगर we should try to recover
 * a hung GPU.
 */
bool amdgpu_device_should_recover_gpu(काष्ठा amdgpu_device *adev)
अणु
	अगर (!amdgpu_device_ip_check_soft_reset(adev)) अणु
		dev_info(adev->dev, "Timeout, but no hardware hang detected.\n");
		वापस false;
	पूर्ण

	अगर (amdgpu_gpu_recovery == 0)
		जाओ disabled;

	अगर (amdgpu_sriov_vf(adev))
		वापस true;

	अगर (amdgpu_gpu_recovery == -1) अणु
		चयन (adev->asic_type) अणु
		हाल CHIP_BONAIRE:
		हाल CHIP_HAWAII:
		हाल CHIP_TOPAZ:
		हाल CHIP_TONGA:
		हाल CHIP_FIJI:
		हाल CHIP_POLARIS10:
		हाल CHIP_POLARIS11:
		हाल CHIP_POLARIS12:
		हाल CHIP_VEGAM:
		हाल CHIP_VEGA20:
		हाल CHIP_VEGA10:
		हाल CHIP_VEGA12:
		हाल CHIP_RAVEN:
		हाल CHIP_ARCTURUS:
		हाल CHIP_RENOIR:
		हाल CHIP_NAVI10:
		हाल CHIP_NAVI14:
		हाल CHIP_NAVI12:
		हाल CHIP_SIENNA_CICHLID:
		हाल CHIP_NAVY_FLOUNDER:
		हाल CHIP_DIMGREY_CAVEFISH:
		हाल CHIP_VANGOGH:
		हाल CHIP_ALDEBARAN:
			अवरोध;
		शेष:
			जाओ disabled;
		पूर्ण
	पूर्ण

	वापस true;

disabled:
		dev_info(adev->dev, "GPU recovery disabled.\n");
		वापस false;
पूर्ण

पूर्णांक amdgpu_device_mode1_reset(काष्ठा amdgpu_device *adev)
अणु
        u32 i;
        पूर्णांक ret = 0;

        amdgpu_atombios_scratch_regs_engine_hung(adev, true);

        dev_info(adev->dev, "GPU mode1 reset\n");

        /* disable BM */
        pci_clear_master(adev->pdev);

        amdgpu_device_cache_pci_state(adev->pdev);

        अगर (amdgpu_dpm_is_mode1_reset_supported(adev)) अणु
                dev_info(adev->dev, "GPU smu mode1 reset\n");
                ret = amdgpu_dpm_mode1_reset(adev);
        पूर्ण अन्यथा अणु
                dev_info(adev->dev, "GPU psp mode1 reset\n");
                ret = psp_gpu_reset(adev);
        पूर्ण

        अगर (ret)
                dev_err(adev->dev, "GPU mode1 reset failed\n");

        amdgpu_device_load_pci_state(adev->pdev);

        /* रुको क्रम asic to come out of reset */
        क्रम (i = 0; i < adev->usec_समयout; i++) अणु
                u32 memsize = adev->nbio.funcs->get_memsize(adev);

                अगर (memsize != 0xffffffff)
                        अवरोध;
                udelay(1);
        पूर्ण

        amdgpu_atombios_scratch_regs_engine_hung(adev, false);
        वापस ret;
पूर्ण

पूर्णांक amdgpu_device_pre_asic_reset(काष्ठा amdgpu_device *adev,
				 काष्ठा amdgpu_reset_context *reset_context)
अणु
	पूर्णांक i, r = 0;
	काष्ठा amdgpu_job *job = शून्य;
	bool need_full_reset =
		test_bit(AMDGPU_NEED_FULL_RESET, &reset_context->flags);

	अगर (reset_context->reset_req_dev == adev)
		job = reset_context->job;

	/* no need to dump अगर device is not in good state during probe period */
	अगर (!adev->gmc.xgmi.pending_reset)
		amdgpu_debugfs_रुको_dump(adev);

	अगर (amdgpu_sriov_vf(adev)) अणु
		/* stop the data exchange thपढ़ो */
		amdgpu_virt_fini_data_exchange(adev);
	पूर्ण

	/* block all schedulers and reset given job's ring */
	क्रम (i = 0; i < AMDGPU_MAX_RINGS; ++i) अणु
		काष्ठा amdgpu_ring *ring = adev->rings[i];

		अगर (!ring || !ring->sched.thपढ़ो)
			जारी;

		/* after all hw jobs are reset, hw fence is meaningless, so क्रमce_completion */
		amdgpu_fence_driver_क्रमce_completion(ring);
	पूर्ण

	अगर(job)
		drm_sched_increase_karma(&job->base);

	r = amdgpu_reset_prepare_hwcontext(adev, reset_context);
	/* If reset handler not implemented, जारी; otherwise वापस */
	अगर (r == -ENOSYS)
		r = 0;
	अन्यथा
		वापस r;

	/* Don't suspend on bare metal अगर we are not going to HW reset the ASIC */
	अगर (!amdgpu_sriov_vf(adev)) अणु

		अगर (!need_full_reset)
			need_full_reset = amdgpu_device_ip_need_full_reset(adev);

		अगर (!need_full_reset) अणु
			amdgpu_device_ip_pre_soft_reset(adev);
			r = amdgpu_device_ip_soft_reset(adev);
			amdgpu_device_ip_post_soft_reset(adev);
			अगर (r || amdgpu_device_ip_check_soft_reset(adev)) अणु
				dev_info(adev->dev, "soft reset failed, will fallback to full reset!\n");
				need_full_reset = true;
			पूर्ण
		पूर्ण

		अगर (need_full_reset)
			r = amdgpu_device_ip_suspend(adev);
		अगर (need_full_reset)
			set_bit(AMDGPU_NEED_FULL_RESET, &reset_context->flags);
		अन्यथा
			clear_bit(AMDGPU_NEED_FULL_RESET,
				  &reset_context->flags);
	पूर्ण

	वापस r;
पूर्ण

पूर्णांक amdgpu_करो_asic_reset(काष्ठा list_head *device_list_handle,
			 काष्ठा amdgpu_reset_context *reset_context)
अणु
	काष्ठा amdgpu_device *पंचांगp_adev = शून्य;
	bool need_full_reset, skip_hw_reset, vram_lost = false;
	पूर्णांक r = 0;

	/* Try reset handler method first */
	पंचांगp_adev = list_first_entry(device_list_handle, काष्ठा amdgpu_device,
				    reset_list);
	r = amdgpu_reset_perक्रमm_reset(पंचांगp_adev, reset_context);
	/* If reset handler not implemented, जारी; otherwise वापस */
	अगर (r == -ENOSYS)
		r = 0;
	अन्यथा
		वापस r;

	/* Reset handler not implemented, use the शेष method */
	need_full_reset =
		test_bit(AMDGPU_NEED_FULL_RESET, &reset_context->flags);
	skip_hw_reset = test_bit(AMDGPU_SKIP_HW_RESET, &reset_context->flags);

	/*
	 * ASIC reset has to be करोne on all XGMI hive nodes ASAP
	 * to allow proper links negotiation in FW (within 1 sec)
	 */
	अगर (!skip_hw_reset && need_full_reset) अणु
		list_क्रम_each_entry(पंचांगp_adev, device_list_handle, reset_list) अणु
			/* For XGMI run all resets in parallel to speed up the process */
			अगर (पंचांगp_adev->gmc.xgmi.num_physical_nodes > 1) अणु
				पंचांगp_adev->gmc.xgmi.pending_reset = false;
				अगर (!queue_work(प्रणाली_unbound_wq, &पंचांगp_adev->xgmi_reset_work))
					r = -EALREADY;
			पूर्ण अन्यथा
				r = amdgpu_asic_reset(पंचांगp_adev);

			अगर (r) अणु
				dev_err(पंचांगp_adev->dev, "ASIC reset failed with error, %d for drm dev, %s",
					 r, adev_to_drm(पंचांगp_adev)->unique);
				अवरोध;
			पूर्ण
		पूर्ण

		/* For XGMI रुको क्रम all resets to complete beक्रमe proceed */
		अगर (!r) अणु
			list_क्रम_each_entry(पंचांगp_adev, device_list_handle, reset_list) अणु
				अगर (पंचांगp_adev->gmc.xgmi.num_physical_nodes > 1) अणु
					flush_work(&पंचांगp_adev->xgmi_reset_work);
					r = पंचांगp_adev->asic_reset_res;
					अगर (r)
						अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!r && amdgpu_ras_पूर्णांकr_triggered()) अणु
		list_क्रम_each_entry(पंचांगp_adev, device_list_handle, reset_list) अणु
			अगर (पंचांगp_adev->mmhub.ras_funcs &&
			    पंचांगp_adev->mmhub.ras_funcs->reset_ras_error_count)
				पंचांगp_adev->mmhub.ras_funcs->reset_ras_error_count(पंचांगp_adev);
		पूर्ण

		amdgpu_ras_पूर्णांकr_cleared();
	पूर्ण

	list_क्रम_each_entry(पंचांगp_adev, device_list_handle, reset_list) अणु
		अगर (need_full_reset) अणु
			/* post card */
			r = amdgpu_device_asic_init(पंचांगp_adev);
			अगर (r) अणु
				dev_warn(पंचांगp_adev->dev, "asic atom init failed!");
			पूर्ण अन्यथा अणु
				dev_info(पंचांगp_adev->dev, "GPU reset succeeded, trying to resume\n");
				r = amdgpu_device_ip_resume_phase1(पंचांगp_adev);
				अगर (r)
					जाओ out;

				vram_lost = amdgpu_device_check_vram_lost(पंचांगp_adev);
				अगर (vram_lost) अणु
					DRM_INFO("VRAM is lost due to GPU reset!\n");
					amdgpu_inc_vram_lost(पंचांगp_adev);
				पूर्ण

				r = amdgpu_gtt_mgr_recover(tपंचांग_manager_type(&पंचांगp_adev->mman.bdev, TTM_PL_TT));
				अगर (r)
					जाओ out;

				r = amdgpu_device_fw_loading(पंचांगp_adev);
				अगर (r)
					वापस r;

				r = amdgpu_device_ip_resume_phase2(पंचांगp_adev);
				अगर (r)
					जाओ out;

				अगर (vram_lost)
					amdgpu_device_fill_reset_magic(पंचांगp_adev);

				/*
				 * Add this ASIC as tracked as reset was alपढ़ोy
				 * complete successfully.
				 */
				amdgpu_रेजिस्टर_gpu_instance(पंचांगp_adev);

				अगर (!reset_context->hive &&
				    पंचांगp_adev->gmc.xgmi.num_physical_nodes > 1)
					amdgpu_xgmi_add_device(पंचांगp_adev);

				r = amdgpu_device_ip_late_init(पंचांगp_adev);
				अगर (r)
					जाओ out;

				amdgpu_fbdev_set_suspend(पंचांगp_adev, 0);

				/*
				 * The GPU enters bad state once faulty pages
				 * by ECC has reached the threshold, and ras
				 * recovery is scheduled next. So add one check
				 * here to अवरोध recovery अगर it indeed exceeds
				 * bad page threshold, and remind user to
				 * retire this GPU or setting one bigger
				 * bad_page_threshold value to fix this once
				 * probing driver again.
				 */
				अगर (!amdgpu_ras_eeprom_check_err_threshold(पंचांगp_adev)) अणु
					/* must succeed. */
					amdgpu_ras_resume(पंचांगp_adev);
				पूर्ण अन्यथा अणु
					r = -EINVAL;
					जाओ out;
				पूर्ण

				/* Update PSP FW topology after reset */
				अगर (reset_context->hive &&
				    पंचांगp_adev->gmc.xgmi.num_physical_nodes > 1)
					r = amdgpu_xgmi_update_topology(
						reset_context->hive, पंचांगp_adev);
			पूर्ण
		पूर्ण

out:
		अगर (!r) अणु
			amdgpu_irq_gpu_reset_resume_helper(पंचांगp_adev);
			r = amdgpu_ib_ring_tests(पंचांगp_adev);
			अगर (r) अणु
				dev_err(पंचांगp_adev->dev, "ib ring test failed (%d).\n", r);
				need_full_reset = true;
				r = -EAGAIN;
				जाओ end;
			पूर्ण
		पूर्ण

		अगर (!r)
			r = amdgpu_device_recover_vram(पंचांगp_adev);
		अन्यथा
			पंचांगp_adev->asic_reset_res = r;
	पूर्ण

end:
	अगर (need_full_reset)
		set_bit(AMDGPU_NEED_FULL_RESET, &reset_context->flags);
	अन्यथा
		clear_bit(AMDGPU_NEED_FULL_RESET, &reset_context->flags);
	वापस r;
पूर्ण

अटल bool amdgpu_device_lock_adev(काष्ठा amdgpu_device *adev,
				काष्ठा amdgpu_hive_info *hive)
अणु
	अगर (atomic_cmpxchg(&adev->in_gpu_reset, 0, 1) != 0)
		वापस false;

	अगर (hive) अणु
		करोwn_ग_लिखो_nest_lock(&adev->reset_sem, &hive->hive_lock);
	पूर्ण अन्यथा अणु
		करोwn_ग_लिखो(&adev->reset_sem);
	पूर्ण

	चयन (amdgpu_asic_reset_method(adev)) अणु
	हाल AMD_RESET_METHOD_MODE1:
		adev->mp1_state = PP_MP1_STATE_SHUTDOWN;
		अवरोध;
	हाल AMD_RESET_METHOD_MODE2:
		adev->mp1_state = PP_MP1_STATE_RESET;
		अवरोध;
	शेष:
		adev->mp1_state = PP_MP1_STATE_NONE;
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम amdgpu_device_unlock_adev(काष्ठा amdgpu_device *adev)
अणु
	amdgpu_vf_error_trans_all(adev);
	adev->mp1_state = PP_MP1_STATE_NONE;
	atomic_set(&adev->in_gpu_reset, 0);
	up_ग_लिखो(&adev->reset_sem);
पूर्ण

/*
 * to lockup a list of amdgpu devices in a hive safely, अगर not a hive
 * with multiple nodes, it will be similar as amdgpu_device_lock_adev.
 *
 * unlock won't require roll back.
 */
अटल पूर्णांक amdgpu_device_lock_hive_adev(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_hive_info *hive)
अणु
	काष्ठा amdgpu_device *पंचांगp_adev = शून्य;

	अगर (adev->gmc.xgmi.num_physical_nodes > 1) अणु
		अगर (!hive) अणु
			dev_err(adev->dev, "Hive is NULL while device has multiple xgmi nodes");
			वापस -ENODEV;
		पूर्ण
		list_क्रम_each_entry(पंचांगp_adev, &hive->device_list, gmc.xgmi.head) अणु
			अगर (!amdgpu_device_lock_adev(पंचांगp_adev, hive))
				जाओ roll_back;
		पूर्ण
	पूर्ण अन्यथा अगर (!amdgpu_device_lock_adev(adev, hive))
		वापस -EAGAIN;

	वापस 0;
roll_back:
	अगर (!list_is_first(&पंचांगp_adev->gmc.xgmi.head, &hive->device_list)) अणु
		/*
		 * अगर the lockup iteration अवरोध in the middle of a hive,
		 * it may means there may has a race issue,
		 * or a hive device locked up independently.
		 * we may be in trouble and may not, so will try to roll back
		 * the lock and give out a warnning.
		 */
		dev_warn(पंचांगp_adev->dev, "Hive lock iteration broke in the middle. Rolling back to unlock");
		list_क्रम_each_entry_जारी_reverse(पंचांगp_adev, &hive->device_list, gmc.xgmi.head) अणु
			amdgpu_device_unlock_adev(पंचांगp_adev);
		पूर्ण
	पूर्ण
	वापस -EAGAIN;
पूर्ण

अटल व्योम amdgpu_device_resume_display_audio(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा pci_dev *p = शून्य;

	p = pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(adev->pdev->bus),
			adev->pdev->bus->number, 1);
	अगर (p) अणु
		pm_runसमय_enable(&(p->dev));
		pm_runसमय_resume(&(p->dev));
	पूर्ण
पूर्ण

अटल पूर्णांक amdgpu_device_suspend_display_audio(काष्ठा amdgpu_device *adev)
अणु
	क्रमागत amd_reset_method reset_method;
	काष्ठा pci_dev *p = शून्य;
	u64 expires;

	/*
	 * For now, only BACO and mode1 reset are confirmed
	 * to suffer the audio issue without proper suspended.
	 */
	reset_method = amdgpu_asic_reset_method(adev);
	अगर ((reset_method != AMD_RESET_METHOD_BACO) &&
	     (reset_method != AMD_RESET_METHOD_MODE1))
		वापस -EINVAL;

	p = pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(adev->pdev->bus),
			adev->pdev->bus->number, 1);
	अगर (!p)
		वापस -ENODEV;

	expires = pm_runसमय_स्वतःsuspend_expiration(&(p->dev));
	अगर (!expires)
		/*
		 * If we cannot get the audio device स्वतःsuspend delay,
		 * a fixed 4S पूर्णांकerval will be used. Considering 3S is
		 * the audio controller शेष स्वतःsuspend delay setting.
		 * 4S used here is guaranteed to cover that.
		 */
		expires = kसमय_get_mono_fast_ns() + NSEC_PER_SEC * 4ULL;

	जबतक (!pm_runसमय_status_suspended(&(p->dev))) अणु
		अगर (!pm_runसमय_suspend(&(p->dev)))
			अवरोध;

		अगर (expires < kसमय_get_mono_fast_ns()) अणु
			dev_warn(adev->dev, "failed to suspend display audio\n");
			/* TODO: पात the succeeding gpu reset? */
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	pm_runसमय_disable(&(p->dev));

	वापस 0;
पूर्ण

व्योम amdgpu_device_recheck_guilty_jobs(
	काष्ठा amdgpu_device *adev, काष्ठा list_head *device_list_handle,
	काष्ठा amdgpu_reset_context *reset_context)
अणु
	पूर्णांक i, r = 0;

	क्रम (i = 0; i < AMDGPU_MAX_RINGS; ++i) अणु
		काष्ठा amdgpu_ring *ring = adev->rings[i];
		पूर्णांक ret = 0;
		काष्ठा drm_sched_job *s_job;

		अगर (!ring || !ring->sched.thपढ़ो)
			जारी;

		s_job = list_first_entry_or_null(&ring->sched.pending_list,
				काष्ठा drm_sched_job, list);
		अगर (s_job == शून्य)
			जारी;

		/* clear job's guilty and depend the folowing step to decide the real one */
		drm_sched_reset_karma(s_job);
		drm_sched_resubmit_jobs_ext(&ring->sched, 1);

		ret = dma_fence_रुको_समयout(s_job->s_fence->parent, false, ring->sched.समयout);
		अगर (ret == 0) अणु /* समयout */
			DRM_ERROR("Found the real bad job! ring:%s, job_id:%llx\n",
						ring->sched.name, s_job->id);

			/* set guilty */
			drm_sched_increase_karma(s_job);
retry:
			/* करो hw reset */
			अगर (amdgpu_sriov_vf(adev)) अणु
				amdgpu_virt_fini_data_exchange(adev);
				r = amdgpu_device_reset_sriov(adev, false);
				अगर (r)
					adev->asic_reset_res = r;
			पूर्ण अन्यथा अणु
				clear_bit(AMDGPU_SKIP_HW_RESET,
					  &reset_context->flags);
				r = amdgpu_करो_asic_reset(device_list_handle,
							 reset_context);
				अगर (r && r == -EAGAIN)
					जाओ retry;
			पूर्ण

			/*
			 * add reset counter so that the following
			 * resubmitted job could flush vmid
			 */
			atomic_inc(&adev->gpu_reset_counter);
			जारी;
		पूर्ण

		/* got the hw fence, संकेत finished fence */
		atomic_dec(ring->sched.score);
		dma_fence_get(&s_job->s_fence->finished);
		dma_fence_संकेत(&s_job->s_fence->finished);
		dma_fence_put(&s_job->s_fence->finished);

		/* हटाओ node from list and मुक्त the job */
		spin_lock(&ring->sched.job_list_lock);
		list_del_init(&s_job->list);
		spin_unlock(&ring->sched.job_list_lock);
		ring->sched.ops->मुक्त_job(s_job);
	पूर्ण
पूर्ण

/**
 * amdgpu_device_gpu_recover - reset the asic and recover scheduler
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @job: which job trigger hang
 *
 * Attempt to reset the GPU अगर it has hung (all asics).
 * Attempt to करो soft-reset or full-reset and reinitialize Asic
 * Returns 0 क्रम success or an error on failure.
 */

पूर्णांक amdgpu_device_gpu_recover(काष्ठा amdgpu_device *adev,
			      काष्ठा amdgpu_job *job)
अणु
	काष्ठा list_head device_list, *device_list_handle =  शून्य;
	bool job_संकेतed = false;
	काष्ठा amdgpu_hive_info *hive = शून्य;
	काष्ठा amdgpu_device *पंचांगp_adev = शून्य;
	पूर्णांक i, r = 0;
	bool need_emergency_restart = false;
	bool audio_suspended = false;
	पूर्णांक पंचांगp_vram_lost_counter;
	काष्ठा amdgpu_reset_context reset_context;

	स_रखो(&reset_context, 0, माप(reset_context));

	/*
	 * Special हाल: RAS triggered and full reset isn't supported
	 */
	need_emergency_restart = amdgpu_ras_need_emergency_restart(adev);

	/*
	 * Flush RAM to disk so that after reboot
	 * the user can पढ़ो log and see why the प्रणाली rebooted.
	 */
	अगर (need_emergency_restart && amdgpu_ras_get_context(adev)->reboot) अणु
		DRM_WARN("Emergency reboot.");

		ksys_sync_helper();
		emergency_restart();
	पूर्ण

	dev_info(adev->dev, "GPU %s begin!\n",
		need_emergency_restart ? "jobs stop":"reset");

	/*
	 * Here we trylock to aव्योम chain of resets executing from
	 * either trigger by jobs on dअगरferent adevs in XGMI hive or jobs on
	 * dअगरferent schedulers क्रम same device जबतक this TO handler is running.
	 * We always reset all schedulers क्रम device and all devices क्रम XGMI
	 * hive so that should take care of them too.
	 */
	hive = amdgpu_get_xgmi_hive(adev);
	अगर (hive) अणु
		अगर (atomic_cmpxchg(&hive->in_reset, 0, 1) != 0) अणु
			DRM_INFO("Bailing on TDR for s_job:%llx, hive: %llx as another already in progress",
				job ? job->base.id : -1, hive->hive_id);
			amdgpu_put_xgmi_hive(hive);
			अगर (job)
				drm_sched_increase_karma(&job->base);
			वापस 0;
		पूर्ण
		mutex_lock(&hive->hive_lock);
	पूर्ण

	reset_context.method = AMD_RESET_METHOD_NONE;
	reset_context.reset_req_dev = adev;
	reset_context.job = job;
	reset_context.hive = hive;
	clear_bit(AMDGPU_NEED_FULL_RESET, &reset_context.flags);

	/*
	 * lock the device beक्रमe we try to operate the linked list
	 * अगर didn't get the device lock, don't touch the linked list since
	 * others may iterating it.
	 */
	r = amdgpu_device_lock_hive_adev(adev, hive);
	अगर (r) अणु
		dev_info(adev->dev, "Bailing on TDR for s_job:%llx, as another already in progress",
					job ? job->base.id : -1);

		/* even we skipped this reset, still need to set the job to guilty */
		अगर (job)
			drm_sched_increase_karma(&job->base);
		जाओ skip_recovery;
	पूर्ण

	/*
	 * Build list of devices to reset.
	 * In हाल we are in XGMI hive mode, resort the device list
	 * to put adev in the 1st position.
	 */
	INIT_LIST_HEAD(&device_list);
	अगर (adev->gmc.xgmi.num_physical_nodes > 1) अणु
		list_क्रम_each_entry(पंचांगp_adev, &hive->device_list, gmc.xgmi.head)
			list_add_tail(&पंचांगp_adev->reset_list, &device_list);
		अगर (!list_is_first(&adev->reset_list, &device_list))
			list_rotate_to_front(&adev->reset_list, &device_list);
		device_list_handle = &device_list;
	पूर्ण अन्यथा अणु
		list_add_tail(&adev->reset_list, &device_list);
		device_list_handle = &device_list;
	पूर्ण

	/* block all schedulers and reset given job's ring */
	list_क्रम_each_entry(पंचांगp_adev, device_list_handle, reset_list) अणु
		/*
		 * Try to put the audio codec पूर्णांकo suspend state
		 * beक्रमe gpu reset started.
		 *
		 * Due to the घातer करोमुख्य of the graphics device
		 * is shared with AZ घातer करोमुख्य. Without this,
		 * we may change the audio hardware from behind
		 * the audio driver's back. That will trigger
		 * some audio codec errors.
		 */
		अगर (!amdgpu_device_suspend_display_audio(पंचांगp_adev))
			audio_suspended = true;

		amdgpu_ras_set_error_query_पढ़ोy(पंचांगp_adev, false);

		cancel_delayed_work_sync(&पंचांगp_adev->delayed_init_work);

		अगर (!amdgpu_sriov_vf(पंचांगp_adev))
			amdgpu_amdkfd_pre_reset(पंचांगp_adev);

		/*
		 * Mark these ASICs to be reseted as untracked first
		 * And add them back after reset completed
		 */
		amdgpu_unरेजिस्टर_gpu_instance(पंचांगp_adev);

		amdgpu_fbdev_set_suspend(पंचांगp_adev, 1);

		/* disable ras on ALL IPs */
		अगर (!need_emergency_restart &&
		      amdgpu_device_ip_need_full_reset(पंचांगp_adev))
			amdgpu_ras_suspend(पंचांगp_adev);

		क्रम (i = 0; i < AMDGPU_MAX_RINGS; ++i) अणु
			काष्ठा amdgpu_ring *ring = पंचांगp_adev->rings[i];

			अगर (!ring || !ring->sched.thपढ़ो)
				जारी;

			drm_sched_stop(&ring->sched, job ? &job->base : शून्य);

			अगर (need_emergency_restart)
				amdgpu_job_stop_all_jobs_on_sched(&ring->sched);
		पूर्ण
		atomic_inc(&पंचांगp_adev->gpu_reset_counter);
	पूर्ण

	अगर (need_emergency_restart)
		जाओ skip_sched_resume;

	/*
	 * Must check guilty संकेत here since after this poपूर्णांक all old
	 * HW fences are क्रमce संकेतed.
	 *
	 * job->base holds a reference to parent fence
	 */
	अगर (job && job->base.s_fence->parent &&
	    dma_fence_is_संकेतed(job->base.s_fence->parent)) अणु
		job_संकेतed = true;
		dev_info(adev->dev, "Guilty job already signaled, skipping HW reset");
		जाओ skip_hw_reset;
	पूर्ण

retry:	/* Rest of adevs pre asic reset from XGMI hive. */
	list_क्रम_each_entry(पंचांगp_adev, device_list_handle, reset_list) अणु
		r = amdgpu_device_pre_asic_reset(पंचांगp_adev, &reset_context);
		/*TODO Should we stop ?*/
		अगर (r) अणु
			dev_err(पंचांगp_adev->dev, "GPU pre asic reset failed with err, %d for drm dev, %s ",
				  r, adev_to_drm(पंचांगp_adev)->unique);
			पंचांगp_adev->asic_reset_res = r;
		पूर्ण
	पूर्ण

	पंचांगp_vram_lost_counter = atomic_पढ़ो(&((adev)->vram_lost_counter));
	/* Actual ASIC resets अगर needed.*/
	/* TODO Implement XGMI hive reset logic क्रम SRIOV */
	अगर (amdgpu_sriov_vf(adev)) अणु
		r = amdgpu_device_reset_sriov(adev, job ? false : true);
		अगर (r)
			adev->asic_reset_res = r;
	पूर्ण अन्यथा अणु
		r = amdgpu_करो_asic_reset(device_list_handle, &reset_context);
		अगर (r && r == -EAGAIN)
			जाओ retry;
	पूर्ण

skip_hw_reset:

	/* Post ASIC reset क्रम all devs .*/
	list_क्रम_each_entry(पंचांगp_adev, device_list_handle, reset_list) अणु

		/*
		 * Someबार a later bad compute job can block a good gfx job as gfx
		 * and compute ring share पूर्णांकernal GC HW mutually. We add an additional
		 * guilty jobs recheck step to find the real guilty job, it synchronously
		 * submits and pends क्रम the first job being संकेतed. If it माला_लो समयout,
		 * we identअगरy it as a real guilty job.
		 */
		अगर (amdgpu_gpu_recovery == 2 &&
			!(पंचांगp_vram_lost_counter < atomic_पढ़ो(&adev->vram_lost_counter)))
			amdgpu_device_recheck_guilty_jobs(
				पंचांगp_adev, device_list_handle, &reset_context);

		क्रम (i = 0; i < AMDGPU_MAX_RINGS; ++i) अणु
			काष्ठा amdgpu_ring *ring = पंचांगp_adev->rings[i];

			अगर (!ring || !ring->sched.thपढ़ो)
				जारी;

			/* No poपूर्णांक to resubmit jobs अगर we didn't HW reset*/
			अगर (!पंचांगp_adev->asic_reset_res && !job_संकेतed)
				drm_sched_resubmit_jobs(&ring->sched);

			drm_sched_start(&ring->sched, !पंचांगp_adev->asic_reset_res);
		पूर्ण

		अगर (!amdgpu_device_has_dc_support(पंचांगp_adev) && !job_संकेतed) अणु
			drm_helper_resume_क्रमce_mode(adev_to_drm(पंचांगp_adev));
		पूर्ण

		पंचांगp_adev->asic_reset_res = 0;

		अगर (r) अणु
			/* bad news, how to tell it to userspace ? */
			dev_info(पंचांगp_adev->dev, "GPU reset(%d) failed\n", atomic_पढ़ो(&पंचांगp_adev->gpu_reset_counter));
			amdgpu_vf_error_put(पंचांगp_adev, AMDGIM_ERROR_VF_GPU_RESET_FAIL, 0, r);
		पूर्ण अन्यथा अणु
			dev_info(पंचांगp_adev->dev, "GPU reset(%d) succeeded!\n", atomic_पढ़ो(&पंचांगp_adev->gpu_reset_counter));
		पूर्ण
	पूर्ण

skip_sched_resume:
	list_क्रम_each_entry(पंचांगp_adev, device_list_handle, reset_list) अणु
		/* unlock kfd: SRIOV would करो it separately */
		अगर (!need_emergency_restart && !amdgpu_sriov_vf(पंचांगp_adev))
	                amdgpu_amdkfd_post_reset(पंचांगp_adev);

		/* kfd_post_reset will करो nothing अगर kfd device is not initialized,
		 * need to bring up kfd here अगर it's not be initialized beक्रमe
		 */
		अगर (!adev->kfd.init_complete)
			amdgpu_amdkfd_device_init(adev);

		अगर (audio_suspended)
			amdgpu_device_resume_display_audio(पंचांगp_adev);
		amdgpu_device_unlock_adev(पंचांगp_adev);
	पूर्ण

skip_recovery:
	अगर (hive) अणु
		atomic_set(&hive->in_reset, 0);
		mutex_unlock(&hive->hive_lock);
		amdgpu_put_xgmi_hive(hive);
	पूर्ण

	अगर (r && r != -EAGAIN)
		dev_info(adev->dev, "GPU reset end with ret = %d\n", r);
	वापस r;
पूर्ण

/**
 * amdgpu_device_get_pcie_info - fence pcie info about the PCIE slot
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Fetchs and stores in the driver the PCIE capabilities (gen speed
 * and lanes) of the slot the device is in. Handles APUs and
 * भवized environments where PCIE config space may not be available.
 */
अटल व्योम amdgpu_device_get_pcie_info(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा pci_dev *pdev;
	क्रमागत pci_bus_speed speed_cap, platक्रमm_speed_cap;
	क्रमागत pcie_link_width platक्रमm_link_width;

	अगर (amdgpu_pcie_gen_cap)
		adev->pm.pcie_gen_mask = amdgpu_pcie_gen_cap;

	अगर (amdgpu_pcie_lane_cap)
		adev->pm.pcie_mlw_mask = amdgpu_pcie_lane_cap;

	/* covers APUs as well */
	अगर (pci_is_root_bus(adev->pdev->bus)) अणु
		अगर (adev->pm.pcie_gen_mask == 0)
			adev->pm.pcie_gen_mask = AMDGPU_DEFAULT_PCIE_GEN_MASK;
		अगर (adev->pm.pcie_mlw_mask == 0)
			adev->pm.pcie_mlw_mask = AMDGPU_DEFAULT_PCIE_MLW_MASK;
		वापस;
	पूर्ण

	अगर (adev->pm.pcie_gen_mask && adev->pm.pcie_mlw_mask)
		वापस;

	pcie_bandwidth_available(adev->pdev, शून्य,
				 &platक्रमm_speed_cap, &platक्रमm_link_width);

	अगर (adev->pm.pcie_gen_mask == 0) अणु
		/* asic caps */
		pdev = adev->pdev;
		speed_cap = pcie_get_speed_cap(pdev);
		अगर (speed_cap == PCI_SPEED_UNKNOWN) अणु
			adev->pm.pcie_gen_mask |= (CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN1 |
						  CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN2 |
						  CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN3);
		पूर्ण अन्यथा अणु
			अगर (speed_cap == PCIE_SPEED_32_0GT)
				adev->pm.pcie_gen_mask |= (CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN1 |
							  CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN2 |
							  CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN3 |
							  CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN4 |
							  CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN5);
			अन्यथा अगर (speed_cap == PCIE_SPEED_16_0GT)
				adev->pm.pcie_gen_mask |= (CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN1 |
							  CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN2 |
							  CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN3 |
							  CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN4);
			अन्यथा अगर (speed_cap == PCIE_SPEED_8_0GT)
				adev->pm.pcie_gen_mask |= (CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN1 |
							  CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN2 |
							  CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN3);
			अन्यथा अगर (speed_cap == PCIE_SPEED_5_0GT)
				adev->pm.pcie_gen_mask |= (CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN1 |
							  CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN2);
			अन्यथा
				adev->pm.pcie_gen_mask |= CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN1;
		पूर्ण
		/* platक्रमm caps */
		अगर (platक्रमm_speed_cap == PCI_SPEED_UNKNOWN) अणु
			adev->pm.pcie_gen_mask |= (CAIL_PCIE_LINK_SPEED_SUPPORT_GEN1 |
						   CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2);
		पूर्ण अन्यथा अणु
			अगर (platक्रमm_speed_cap == PCIE_SPEED_32_0GT)
				adev->pm.pcie_gen_mask |= (CAIL_PCIE_LINK_SPEED_SUPPORT_GEN1 |
							   CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2 |
							   CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3 |
							   CAIL_PCIE_LINK_SPEED_SUPPORT_GEN4 |
							   CAIL_PCIE_LINK_SPEED_SUPPORT_GEN5);
			अन्यथा अगर (platक्रमm_speed_cap == PCIE_SPEED_16_0GT)
				adev->pm.pcie_gen_mask |= (CAIL_PCIE_LINK_SPEED_SUPPORT_GEN1 |
							   CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2 |
							   CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3 |
							   CAIL_PCIE_LINK_SPEED_SUPPORT_GEN4);
			अन्यथा अगर (platक्रमm_speed_cap == PCIE_SPEED_8_0GT)
				adev->pm.pcie_gen_mask |= (CAIL_PCIE_LINK_SPEED_SUPPORT_GEN1 |
							   CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2 |
							   CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3);
			अन्यथा अगर (platक्रमm_speed_cap == PCIE_SPEED_5_0GT)
				adev->pm.pcie_gen_mask |= (CAIL_PCIE_LINK_SPEED_SUPPORT_GEN1 |
							   CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2);
			अन्यथा
				adev->pm.pcie_gen_mask |= CAIL_PCIE_LINK_SPEED_SUPPORT_GEN1;

		पूर्ण
	पूर्ण
	अगर (adev->pm.pcie_mlw_mask == 0) अणु
		अगर (platक्रमm_link_width == PCIE_LNK_WIDTH_UNKNOWN) अणु
			adev->pm.pcie_mlw_mask |= AMDGPU_DEFAULT_PCIE_MLW_MASK;
		पूर्ण अन्यथा अणु
			चयन (platक्रमm_link_width) अणु
			हाल PCIE_LNK_X32:
				adev->pm.pcie_mlw_mask = (CAIL_PCIE_LINK_WIDTH_SUPPORT_X32 |
							  CAIL_PCIE_LINK_WIDTH_SUPPORT_X16 |
							  CAIL_PCIE_LINK_WIDTH_SUPPORT_X12 |
							  CAIL_PCIE_LINK_WIDTH_SUPPORT_X8 |
							  CAIL_PCIE_LINK_WIDTH_SUPPORT_X4 |
							  CAIL_PCIE_LINK_WIDTH_SUPPORT_X2 |
							  CAIL_PCIE_LINK_WIDTH_SUPPORT_X1);
				अवरोध;
			हाल PCIE_LNK_X16:
				adev->pm.pcie_mlw_mask = (CAIL_PCIE_LINK_WIDTH_SUPPORT_X16 |
							  CAIL_PCIE_LINK_WIDTH_SUPPORT_X12 |
							  CAIL_PCIE_LINK_WIDTH_SUPPORT_X8 |
							  CAIL_PCIE_LINK_WIDTH_SUPPORT_X4 |
							  CAIL_PCIE_LINK_WIDTH_SUPPORT_X2 |
							  CAIL_PCIE_LINK_WIDTH_SUPPORT_X1);
				अवरोध;
			हाल PCIE_LNK_X12:
				adev->pm.pcie_mlw_mask = (CAIL_PCIE_LINK_WIDTH_SUPPORT_X12 |
							  CAIL_PCIE_LINK_WIDTH_SUPPORT_X8 |
							  CAIL_PCIE_LINK_WIDTH_SUPPORT_X4 |
							  CAIL_PCIE_LINK_WIDTH_SUPPORT_X2 |
							  CAIL_PCIE_LINK_WIDTH_SUPPORT_X1);
				अवरोध;
			हाल PCIE_LNK_X8:
				adev->pm.pcie_mlw_mask = (CAIL_PCIE_LINK_WIDTH_SUPPORT_X8 |
							  CAIL_PCIE_LINK_WIDTH_SUPPORT_X4 |
							  CAIL_PCIE_LINK_WIDTH_SUPPORT_X2 |
							  CAIL_PCIE_LINK_WIDTH_SUPPORT_X1);
				अवरोध;
			हाल PCIE_LNK_X4:
				adev->pm.pcie_mlw_mask = (CAIL_PCIE_LINK_WIDTH_SUPPORT_X4 |
							  CAIL_PCIE_LINK_WIDTH_SUPPORT_X2 |
							  CAIL_PCIE_LINK_WIDTH_SUPPORT_X1);
				अवरोध;
			हाल PCIE_LNK_X2:
				adev->pm.pcie_mlw_mask = (CAIL_PCIE_LINK_WIDTH_SUPPORT_X2 |
							  CAIL_PCIE_LINK_WIDTH_SUPPORT_X1);
				अवरोध;
			हाल PCIE_LNK_X1:
				adev->pm.pcie_mlw_mask = CAIL_PCIE_LINK_WIDTH_SUPPORT_X1;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक amdgpu_device_baco_enter(काष्ठा drm_device *dev)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_ras *ras = amdgpu_ras_get_context(adev);

	अगर (!amdgpu_device_supports_baco(adev_to_drm(adev)))
		वापस -ENOTSUPP;

	अगर (ras && ras->supported && adev->nbio.funcs->enable_करोorbell_पूर्णांकerrupt)
		adev->nbio.funcs->enable_करोorbell_पूर्णांकerrupt(adev, false);

	वापस amdgpu_dpm_baco_enter(adev);
पूर्ण

पूर्णांक amdgpu_device_baco_निकास(काष्ठा drm_device *dev)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_ras *ras = amdgpu_ras_get_context(adev);
	पूर्णांक ret = 0;

	अगर (!amdgpu_device_supports_baco(adev_to_drm(adev)))
		वापस -ENOTSUPP;

	ret = amdgpu_dpm_baco_निकास(adev);
	अगर (ret)
		वापस ret;

	अगर (ras && ras->supported && adev->nbio.funcs->enable_करोorbell_पूर्णांकerrupt)
		adev->nbio.funcs->enable_करोorbell_पूर्णांकerrupt(adev, true);

	वापस 0;
पूर्ण

अटल व्योम amdgpu_cancel_all_tdr(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < AMDGPU_MAX_RINGS; ++i) अणु
		काष्ठा amdgpu_ring *ring = adev->rings[i];

		अगर (!ring || !ring->sched.thपढ़ो)
			जारी;

		cancel_delayed_work_sync(&ring->sched.work_tdr);
	पूर्ण
पूर्ण

/**
 * amdgpu_pci_error_detected - Called when a PCI error is detected.
 * @pdev: PCI device काष्ठा
 * @state: PCI channel state
 *
 * Description: Called when a PCI error is detected.
 *
 * Return: PCI_ERS_RESULT_NEED_RESET or PCI_ERS_RESULT_DISCONNECT.
 */
pci_ers_result_t amdgpu_pci_error_detected(काष्ठा pci_dev *pdev, pci_channel_state_t state)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	पूर्णांक i;

	DRM_INFO("PCI error: detected callback, state(%d)!!\n", state);

	अगर (adev->gmc.xgmi.num_physical_nodes > 1) अणु
		DRM_WARN("No support for XGMI hive yet...");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	चयन (state) अणु
	हाल pci_channel_io_normal:
		वापस PCI_ERS_RESULT_CAN_RECOVER;
	/* Fatal error, prepare क्रम slot reset */
	हाल pci_channel_io_frozen:
		/*
		 * Cancel and रुको क्रम all TDRs in progress अगर failing to
		 * set  adev->in_gpu_reset in amdgpu_device_lock_adev
		 *
		 * Locking adev->reset_sem will prevent any बाह्यal access
		 * to GPU during PCI error recovery
		 */
		जबतक (!amdgpu_device_lock_adev(adev, शून्य))
			amdgpu_cancel_all_tdr(adev);

		/*
		 * Block any work scheduling as we करो क्रम regular GPU reset
		 * क्रम the duration of the recovery
		 */
		क्रम (i = 0; i < AMDGPU_MAX_RINGS; ++i) अणु
			काष्ठा amdgpu_ring *ring = adev->rings[i];

			अगर (!ring || !ring->sched.thपढ़ो)
				जारी;

			drm_sched_stop(&ring->sched, शून्य);
		पूर्ण
		atomic_inc(&adev->gpu_reset_counter);
		वापस PCI_ERS_RESULT_NEED_RESET;
	हाल pci_channel_io_perm_failure:
		/* Permanent error, prepare क्रम device removal */
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * amdgpu_pci_mmio_enabled - Enable MMIO and dump debug रेजिस्टरs
 * @pdev: poपूर्णांकer to PCI device
 */
pci_ers_result_t amdgpu_pci_mmio_enabled(काष्ठा pci_dev *pdev)
अणु

	DRM_INFO("PCI error: mmio enabled callback!!\n");

	/* TODO - dump whatever क्रम debugging purposes */

	/* This called only अगर amdgpu_pci_error_detected वापसs
	 * PCI_ERS_RESULT_CAN_RECOVER. Read/ग_लिखो to the device still
	 * works, no need to reset slot.
	 */

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

/**
 * amdgpu_pci_slot_reset - Called when PCI slot has been reset.
 * @pdev: PCI device काष्ठा
 *
 * Description: This routine is called by the pci error recovery
 * code after the PCI slot has been reset, just beक्रमe we
 * should resume normal operations.
 */
pci_ers_result_t amdgpu_pci_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	पूर्णांक r, i;
	काष्ठा amdgpu_reset_context reset_context;
	u32 memsize;
	काष्ठा list_head device_list;

	DRM_INFO("PCI error: slot reset callback!!\n");

	स_रखो(&reset_context, 0, माप(reset_context));

	INIT_LIST_HEAD(&device_list);
	list_add_tail(&adev->reset_list, &device_list);

	/* रुको क्रम asic to come out of reset */
	msleep(500);

	/* Restore PCI confspace */
	amdgpu_device_load_pci_state(pdev);

	/* confirm  ASIC came out of reset */
	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		memsize = amdgpu_asic_get_config_memsize(adev);

		अगर (memsize != 0xffffffff)
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (memsize == 0xffffffff) अणु
		r = -ETIME;
		जाओ out;
	पूर्ण

	reset_context.method = AMD_RESET_METHOD_NONE;
	reset_context.reset_req_dev = adev;
	set_bit(AMDGPU_NEED_FULL_RESET, &reset_context.flags);
	set_bit(AMDGPU_SKIP_HW_RESET, &reset_context.flags);

	adev->in_pci_err_recovery = true;
	r = amdgpu_device_pre_asic_reset(adev, &reset_context);
	adev->in_pci_err_recovery = false;
	अगर (r)
		जाओ out;

	r = amdgpu_करो_asic_reset(&device_list, &reset_context);

out:
	अगर (!r) अणु
		अगर (amdgpu_device_cache_pci_state(adev->pdev))
			pci_restore_state(adev->pdev);

		DRM_INFO("PCIe error recovery succeeded\n");
	पूर्ण अन्यथा अणु
		DRM_ERROR("PCIe error recovery failed, err:%d", r);
		amdgpu_device_unlock_adev(adev);
	पूर्ण

	वापस r ? PCI_ERS_RESULT_DISCONNECT : PCI_ERS_RESULT_RECOVERED;
पूर्ण

/**
 * amdgpu_pci_resume() - resume normal ops after PCI reset
 * @pdev: poपूर्णांकer to PCI device
 *
 * Called when the error recovery driver tells us that its
 * OK to resume normal operation.
 */
व्योम amdgpu_pci_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	पूर्णांक i;


	DRM_INFO("PCI error: resume callback!!\n");

	क्रम (i = 0; i < AMDGPU_MAX_RINGS; ++i) अणु
		काष्ठा amdgpu_ring *ring = adev->rings[i];

		अगर (!ring || !ring->sched.thपढ़ो)
			जारी;


		drm_sched_resubmit_jobs(&ring->sched);
		drm_sched_start(&ring->sched, true);
	पूर्ण

	amdgpu_device_unlock_adev(adev);
पूर्ण

bool amdgpu_device_cache_pci_state(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	पूर्णांक r;

	r = pci_save_state(pdev);
	अगर (!r) अणु
		kमुक्त(adev->pci_state);

		adev->pci_state = pci_store_saved_state(pdev);

		अगर (!adev->pci_state) अणु
			DRM_ERROR("Failed to store PCI saved state");
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		DRM_WARN("Failed to save PCI state, err:%d\n", r);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

bool amdgpu_device_load_pci_state(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	पूर्णांक r;

	अगर (!adev->pci_state)
		वापस false;

	r = pci_load_saved_state(pdev, adev->pci_state);

	अगर (!r) अणु
		pci_restore_state(pdev);
	पूर्ण अन्यथा अणु
		DRM_WARN("Failed to load PCI state, err:%d\n", r);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण


