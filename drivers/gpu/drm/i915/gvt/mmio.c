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
 *    Ke Yu
 *    Kevin Tian <kevin.tian@पूर्णांकel.com>
 *    Dexuan Cui
 *
 * Contributors:
 *    Tina Zhang <tina.zhang@पूर्णांकel.com>
 *    Min He <min.he@पूर्णांकel.com>
 *    Niu Bing <bing.niu@पूर्णांकel.com>
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *
 */

#समावेश "i915_drv.h"
#समावेश "gvt.h"

/**
 * पूर्णांकel_vgpu_gpa_to_mmio_offset - translate a GPA to MMIO offset
 * @vgpu: a vGPU
 * @gpa: guest physical address
 *
 * Returns:
 * Zero on success, negative error code अगर failed
 */
पूर्णांक पूर्णांकel_vgpu_gpa_to_mmio_offset(काष्ठा पूर्णांकel_vgpu *vgpu, u64 gpa)
अणु
	u64 gtपंचांगmio_gpa = पूर्णांकel_vgpu_get_bar_gpa(vgpu, PCI_BASE_ADDRESS_0);
	वापस gpa - gtपंचांगmio_gpa;
पूर्ण

#घोषणा reg_is_mmio(gvt, reg)  \
	(reg >= 0 && reg < gvt->device_info.mmio_size)

#घोषणा reg_is_gtt(gvt, reg)   \
	(reg >= gvt->device_info.gtt_start_offset \
	 && reg < gvt->device_info.gtt_start_offset + gvt_ggtt_sz(gvt))

अटल व्योम failsafe_emulate_mmio_rw(काष्ठा पूर्णांकel_vgpu *vgpu, u64 pa,
		व्योम *p_data, अचिन्हित पूर्णांक bytes, bool पढ़ो)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = शून्य;
	व्योम *pt = शून्य;
	अचिन्हित पूर्णांक offset = 0;

	अगर (!vgpu || !p_data)
		वापस;

	gvt = vgpu->gvt;
	mutex_lock(&vgpu->vgpu_lock);
	offset = पूर्णांकel_vgpu_gpa_to_mmio_offset(vgpu, pa);
	अगर (reg_is_mmio(gvt, offset)) अणु
		अगर (पढ़ो)
			पूर्णांकel_vgpu_शेष_mmio_पढ़ो(vgpu, offset, p_data,
					bytes);
		अन्यथा
			पूर्णांकel_vgpu_शेष_mmio_ग_लिखो(vgpu, offset, p_data,
					bytes);
	पूर्ण अन्यथा अगर (reg_is_gtt(gvt, offset)) अणु
		offset -= gvt->device_info.gtt_start_offset;
		pt = vgpu->gtt.ggtt_mm->ggtt_mm.भव_ggtt + offset;
		अगर (पढ़ो)
			स_नकल(p_data, pt, bytes);
		अन्यथा
			स_नकल(pt, p_data, bytes);

	पूर्ण
	mutex_unlock(&vgpu->vgpu_lock);
पूर्ण

/**
 * पूर्णांकel_vgpu_emulate_mmio_पढ़ो - emulate MMIO पढ़ो
 * @vgpu: a vGPU
 * @pa: guest physical address
 * @p_data: data वापस buffer
 * @bytes: access data length
 *
 * Returns:
 * Zero on success, negative error code अगर failed
 */
पूर्णांक पूर्णांकel_vgpu_emulate_mmio_पढ़ो(काष्ठा पूर्णांकel_vgpu *vgpu, u64 pa,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा drm_i915_निजी *i915 = gvt->gt->i915;
	अचिन्हित पूर्णांक offset = 0;
	पूर्णांक ret = -EINVAL;

	अगर (vgpu->failsafe) अणु
		failsafe_emulate_mmio_rw(vgpu, pa, p_data, bytes, true);
		वापस 0;
	पूर्ण
	mutex_lock(&vgpu->vgpu_lock);

	offset = पूर्णांकel_vgpu_gpa_to_mmio_offset(vgpu, pa);

	अगर (drm_WARN_ON(&i915->drm, bytes > 8))
		जाओ err;

	अगर (reg_is_gtt(gvt, offset)) अणु
		अगर (drm_WARN_ON(&i915->drm, !IS_ALIGNED(offset, 4) &&
				!IS_ALIGNED(offset, 8)))
			जाओ err;
		अगर (drm_WARN_ON(&i915->drm, bytes != 4 && bytes != 8))
			जाओ err;
		अगर (drm_WARN_ON(&i915->drm,
				!reg_is_gtt(gvt, offset + bytes - 1)))
			जाओ err;

		ret = पूर्णांकel_vgpu_emulate_ggtt_mmio_पढ़ो(vgpu, offset,
				p_data, bytes);
		अगर (ret)
			जाओ err;
		जाओ out;
	पूर्ण

	अगर (drm_WARN_ON_ONCE(&i915->drm, !reg_is_mmio(gvt, offset))) अणु
		ret = पूर्णांकel_gvt_hypervisor_पढ़ो_gpa(vgpu, pa, p_data, bytes);
		जाओ out;
	पूर्ण

	अगर (drm_WARN_ON(&i915->drm, !reg_is_mmio(gvt, offset + bytes - 1)))
		जाओ err;

	अगर (!पूर्णांकel_gvt_mmio_is_unalign(gvt, offset)) अणु
		अगर (drm_WARN_ON(&i915->drm, !IS_ALIGNED(offset, bytes)))
			जाओ err;
	पूर्ण

	ret = पूर्णांकel_vgpu_mmio_reg_rw(vgpu, offset, p_data, bytes, true);
	अगर (ret < 0)
		जाओ err;

	पूर्णांकel_gvt_mmio_set_accessed(gvt, offset);
	ret = 0;
	जाओ out;

err:
	gvt_vgpu_err("fail to emulate MMIO read %08x len %d\n",
			offset, bytes);
out:
	mutex_unlock(&vgpu->vgpu_lock);
	वापस ret;
पूर्ण

/**
 * पूर्णांकel_vgpu_emulate_mmio_ग_लिखो - emulate MMIO ग_लिखो
 * @vgpu: a vGPU
 * @pa: guest physical address
 * @p_data: ग_लिखो data buffer
 * @bytes: access data length
 *
 * Returns:
 * Zero on success, negative error code अगर failed
 */
पूर्णांक पूर्णांकel_vgpu_emulate_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, u64 pa,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा drm_i915_निजी *i915 = gvt->gt->i915;
	अचिन्हित पूर्णांक offset = 0;
	पूर्णांक ret = -EINVAL;

	अगर (vgpu->failsafe) अणु
		failsafe_emulate_mmio_rw(vgpu, pa, p_data, bytes, false);
		वापस 0;
	पूर्ण

	mutex_lock(&vgpu->vgpu_lock);

	offset = पूर्णांकel_vgpu_gpa_to_mmio_offset(vgpu, pa);

	अगर (drm_WARN_ON(&i915->drm, bytes > 8))
		जाओ err;

	अगर (reg_is_gtt(gvt, offset)) अणु
		अगर (drm_WARN_ON(&i915->drm, !IS_ALIGNED(offset, 4) &&
				!IS_ALIGNED(offset, 8)))
			जाओ err;
		अगर (drm_WARN_ON(&i915->drm, bytes != 4 && bytes != 8))
			जाओ err;
		अगर (drm_WARN_ON(&i915->drm,
				!reg_is_gtt(gvt, offset + bytes - 1)))
			जाओ err;

		ret = पूर्णांकel_vgpu_emulate_ggtt_mmio_ग_लिखो(vgpu, offset,
				p_data, bytes);
		अगर (ret)
			जाओ err;
		जाओ out;
	पूर्ण

	अगर (drm_WARN_ON_ONCE(&i915->drm, !reg_is_mmio(gvt, offset))) अणु
		ret = पूर्णांकel_gvt_hypervisor_ग_लिखो_gpa(vgpu, pa, p_data, bytes);
		जाओ out;
	पूर्ण

	ret = पूर्णांकel_vgpu_mmio_reg_rw(vgpu, offset, p_data, bytes, false);
	अगर (ret < 0)
		जाओ err;

	पूर्णांकel_gvt_mmio_set_accessed(gvt, offset);
	ret = 0;
	जाओ out;
err:
	gvt_vgpu_err("fail to emulate MMIO write %08x len %d\n", offset,
		     bytes);
out:
	mutex_unlock(&vgpu->vgpu_lock);
	वापस ret;
पूर्ण


/**
 * पूर्णांकel_vgpu_reset_mmio - reset भव MMIO space
 * @vgpu: a vGPU
 * @dmlr: whether this is device model level reset
 */
व्योम पूर्णांकel_vgpu_reset_mmio(काष्ठा पूर्णांकel_vgpu *vgpu, bool dmlr)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	स्थिर काष्ठा पूर्णांकel_gvt_device_info *info = &gvt->device_info;
	व्योम  *mmio = gvt->firmware.mmio;

	अगर (dmlr) अणु
		स_नकल(vgpu->mmio.vreg, mmio, info->mmio_size);

		vgpu_vreg_t(vgpu, GEN6_GT_THREAD_STATUS_REG) = 0;

		/* set the bit 0:2(Core C-State ) to C0 */
		vgpu_vreg_t(vgpu, GEN6_GT_CORE_STATUS) = 0;

		/* uc reset hw expect GS_MIA_IN_RESET */
		vgpu_vreg_t(vgpu, GUC_STATUS) |= GS_MIA_IN_RESET;

		अगर (IS_BROXTON(vgpu->gvt->gt->i915)) अणु
			vgpu_vreg_t(vgpu, BXT_P_CR_GT_DISP_PWRON) &=
				    ~(BIT(0) | BIT(1));
			vgpu_vreg_t(vgpu, BXT_PORT_CL1CM_DW0(DPIO_PHY0)) &=
				    ~PHY_POWER_GOOD;
			vgpu_vreg_t(vgpu, BXT_PORT_CL1CM_DW0(DPIO_PHY1)) &=
				    ~PHY_POWER_GOOD;
			vgpu_vreg_t(vgpu, BXT_PHY_CTL_FAMILY(DPIO_PHY0)) &=
				    ~BIT(30);
			vgpu_vreg_t(vgpu, BXT_PHY_CTL_FAMILY(DPIO_PHY1)) &=
				    ~BIT(30);
			vgpu_vreg_t(vgpu, BXT_PHY_CTL(PORT_A)) &=
				    ~BXT_PHY_LANE_ENABLED;
			vgpu_vreg_t(vgpu, BXT_PHY_CTL(PORT_A)) |=
				    BXT_PHY_CMNLANE_POWERDOWN_ACK |
				    BXT_PHY_LANE_POWERDOWN_ACK;
			vgpu_vreg_t(vgpu, BXT_PHY_CTL(PORT_B)) &=
				    ~BXT_PHY_LANE_ENABLED;
			vgpu_vreg_t(vgpu, BXT_PHY_CTL(PORT_B)) |=
				    BXT_PHY_CMNLANE_POWERDOWN_ACK |
				    BXT_PHY_LANE_POWERDOWN_ACK;
			vgpu_vreg_t(vgpu, BXT_PHY_CTL(PORT_C)) &=
				    ~BXT_PHY_LANE_ENABLED;
			vgpu_vreg_t(vgpu, BXT_PHY_CTL(PORT_C)) |=
				    BXT_PHY_CMNLANE_POWERDOWN_ACK |
				    BXT_PHY_LANE_POWERDOWN_ACK;
			vgpu_vreg_t(vgpu, SKL_FUSE_STATUS) |=
				SKL_FUSE_DOWNLOAD_STATUS |
				SKL_FUSE_PG_DIST_STATUS(SKL_PG0) |
				SKL_FUSE_PG_DIST_STATUS(SKL_PG1) |
				SKL_FUSE_PG_DIST_STATUS(SKL_PG2);
		पूर्ण
	पूर्ण अन्यथा अणु
#घोषणा GVT_GEN8_MMIO_RESET_OFFSET		(0x44200)
		/* only reset the engine related, so starting with 0x44200
		 * पूर्णांकerrupt include DE,display mmio related will not be
		 * touched
		 */
		स_नकल(vgpu->mmio.vreg, mmio, GVT_GEN8_MMIO_RESET_OFFSET);
	पूर्ण

पूर्ण

/**
 * पूर्णांकel_vgpu_init_mmio - init MMIO  space
 * @vgpu: a vGPU
 *
 * Returns:
 * Zero on success, negative error code अगर failed
 */
पूर्णांक पूर्णांकel_vgpu_init_mmio(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	स्थिर काष्ठा पूर्णांकel_gvt_device_info *info = &vgpu->gvt->device_info;

	vgpu->mmio.vreg = vzalloc(info->mmio_size);
	अगर (!vgpu->mmio.vreg)
		वापस -ENOMEM;

	पूर्णांकel_vgpu_reset_mmio(vgpu, true);

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_vgpu_clean_mmio - clean MMIO space
 * @vgpu: a vGPU
 *
 */
व्योम पूर्णांकel_vgpu_clean_mmio(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	vमुक्त(vgpu->mmio.vreg);
	vgpu->mmio.vreg = शून्य;
पूर्ण
