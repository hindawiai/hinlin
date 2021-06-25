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
 *    Kevin Tian <kevin.tian@पूर्णांकel.com>
 *    Eddie Dong <eddie.करोng@पूर्णांकel.com>
 *    Zhiyuan Lv <zhiyuan.lv@पूर्णांकel.com>
 *
 * Contributors:
 *    Min He <min.he@पूर्णांकel.com>
 *    Tina Zhang <tina.zhang@पूर्णांकel.com>
 *    Pei Zhang <pei.zhang@पूर्णांकel.com>
 *    Niu Bing <bing.niu@पूर्णांकel.com>
 *    Ping Gao <ping.a.gao@पूर्णांकel.com>
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *

 */

#समावेश "i915_drv.h"
#समावेश "gvt.h"
#समावेश "i915_pvinfo.h"
#समावेश "display/intel_display_types.h"

/* XXX FIXME i915 has changed PP_XXX definition */
#घोषणा PCH_PP_STATUS  _MMIO(0xc7200)
#घोषणा PCH_PP_CONTROL _MMIO(0xc7204)
#घोषणा PCH_PP_ON_DELAYS _MMIO(0xc7208)
#घोषणा PCH_PP_OFF_DELAYS _MMIO(0xc720c)
#घोषणा PCH_PP_DIVISOR _MMIO(0xc7210)

अचिन्हित दीर्घ पूर्णांकel_gvt_get_device_type(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा drm_i915_निजी *i915 = gvt->gt->i915;

	अगर (IS_BROADWELL(i915))
		वापस D_BDW;
	अन्यथा अगर (IS_SKYLAKE(i915))
		वापस D_SKL;
	अन्यथा अगर (IS_KABYLAKE(i915))
		वापस D_KBL;
	अन्यथा अगर (IS_BROXTON(i915))
		वापस D_BXT;
	अन्यथा अगर (IS_COFFEELAKE(i915) || IS_COMETLAKE(i915))
		वापस D_CFL;

	वापस 0;
पूर्ण

bool पूर्णांकel_gvt_match_device(काष्ठा पूर्णांकel_gvt *gvt,
		अचिन्हित दीर्घ device)
अणु
	वापस पूर्णांकel_gvt_get_device_type(gvt) & device;
पूर्ण

अटल व्योम पढ़ो_vreg(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
	व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	स_नकल(p_data, &vgpu_vreg(vgpu, offset), bytes);
पूर्ण

अटल व्योम ग_लिखो_vreg(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
	व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	स_नकल(&vgpu_vreg(vgpu, offset), p_data, bytes);
पूर्ण

काष्ठा पूर्णांकel_gvt_mmio_info *पूर्णांकel_gvt_find_mmio_info(काष्ठा पूर्णांकel_gvt *gvt,
						  अचिन्हित पूर्णांक offset)
अणु
	काष्ठा पूर्णांकel_gvt_mmio_info *e;

	hash_क्रम_each_possible(gvt->mmio.mmio_info_table, e, node, offset) अणु
		अगर (e->offset == offset)
			वापस e;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक new_mmio_info(काष्ठा पूर्णांकel_gvt *gvt,
		u32 offset, u16 flags, u32 size,
		u32 addr_mask, u32 ro_mask, u32 device,
		gvt_mmio_func पढ़ो, gvt_mmio_func ग_लिखो)
अणु
	काष्ठा पूर्णांकel_gvt_mmio_info *info, *p;
	u32 start, end, i;

	अगर (!पूर्णांकel_gvt_match_device(gvt, device))
		वापस 0;

	अगर (WARN_ON(!IS_ALIGNED(offset, 4)))
		वापस -EINVAL;

	start = offset;
	end = offset + size;

	क्रम (i = start; i < end; i += 4) अणु
		info = kzalloc(माप(*info), GFP_KERNEL);
		अगर (!info)
			वापस -ENOMEM;

		info->offset = i;
		p = पूर्णांकel_gvt_find_mmio_info(gvt, info->offset);
		अगर (p) अणु
			WARN(1, "dup mmio definition offset %x\n",
				info->offset);
			kमुक्त(info);

			/* We वापस -EEXIST here to make GVT-g load fail.
			 * So duplicated MMIO can be found as soon as
			 * possible.
			 */
			वापस -EEXIST;
		पूर्ण

		info->ro_mask = ro_mask;
		info->device = device;
		info->पढ़ो = पढ़ो ? पढ़ो : पूर्णांकel_vgpu_शेष_mmio_पढ़ो;
		info->ग_लिखो = ग_लिखो ? ग_लिखो : पूर्णांकel_vgpu_शेष_mmio_ग_लिखो;
		gvt->mmio.mmio_attribute[info->offset / 4] = flags;
		INIT_HLIST_NODE(&info->node);
		hash_add(gvt->mmio.mmio_info_table, &info->node, info->offset);
		gvt->mmio.num_tracked_mmio++;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * पूर्णांकel_gvt_render_mmio_to_engine - convert a mmio offset पूर्णांकo the engine
 * @gvt: a GVT device
 * @offset: रेजिस्टर offset
 *
 * Returns:
 * The engine containing the offset within its mmio page.
 */
स्थिर काष्ठा पूर्णांकel_engine_cs *
पूर्णांकel_gvt_render_mmio_to_engine(काष्ठा पूर्णांकel_gvt *gvt, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	offset &= ~GENMASK(11, 0);
	क्रम_each_engine(engine, gvt->gt, id)
		अगर (engine->mmio_base == offset)
			वापस engine;

	वापस शून्य;
पूर्ण

#घोषणा offset_to_fence_num(offset) \
	((offset - i915_mmio_reg_offset(FENCE_REG_GEN6_LO(0))) >> 3)

#घोषणा fence_num_to_offset(num) \
	(num * 8 + i915_mmio_reg_offset(FENCE_REG_GEN6_LO(0)))


व्योम enter_failsafe_mode(काष्ठा पूर्णांकel_vgpu *vgpu, पूर्णांक reason)
अणु
	चयन (reason) अणु
	हाल GVT_FAILSAFE_UNSUPPORTED_GUEST:
		pr_err("Detected your guest driver doesn't support GVT-g.\n");
		अवरोध;
	हाल GVT_FAILSAFE_INSUFFICIENT_RESOURCE:
		pr_err("Graphics resource is not enough for the guest\n");
		अवरोध;
	हाल GVT_FAILSAFE_GUEST_ERR:
		pr_err("GVT Internal error  for the guest\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	pr_err("Now vgpu %d will enter failsafe mode.\n", vgpu->id);
	vgpu->failsafe = true;
पूर्ण

अटल पूर्णांक sanitize_fence_mmio_access(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक fence_num, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	अचिन्हित पूर्णांक max_fence = vgpu_fence_sz(vgpu);

	अगर (fence_num >= max_fence) अणु
		gvt_vgpu_err("access oob fence reg %d/%d\n",
			     fence_num, max_fence);

		/* When guest access oob fence regs without access
		 * pv_info first, we treat guest not supporting GVT,
		 * and we will let vgpu enter failsafe mode.
		 */
		अगर (!vgpu->pv_notअगरied)
			enter_failsafe_mode(vgpu,
					GVT_FAILSAFE_UNSUPPORTED_GUEST);

		स_रखो(p_data, 0, bytes);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gamw_echo_dev_rw_ia_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 ips = (*(u32 *)p_data) & GAMW_ECO_ENABLE_64K_IPS_FIELD;

	अगर (INTEL_GEN(vgpu->gvt->gt->i915) <= 10) अणु
		अगर (ips == GAMW_ECO_ENABLE_64K_IPS_FIELD)
			gvt_dbg_core("vgpu%d: ips enabled\n", vgpu->id);
		अन्यथा अगर (!ips)
			gvt_dbg_core("vgpu%d: ips disabled\n", vgpu->id);
		अन्यथा अणु
			/* All engines must be enabled together क्रम vGPU,
			 * since we करोn't know which engine the ppgtt will
			 * bind to when shaकरोwing.
			 */
			gvt_vgpu_err("Unsupported IPS setting %x, cannot enable 64K gtt.\n",
				     ips);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ग_लिखो_vreg(vgpu, offset, p_data, bytes);
	वापस 0;
पूर्ण

अटल पूर्णांक fence_mmio_पढ़ो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक off,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	पूर्णांक ret;

	ret = sanitize_fence_mmio_access(vgpu, offset_to_fence_num(off),
			p_data, bytes);
	अगर (ret)
		वापस ret;
	पढ़ो_vreg(vgpu, off, p_data, bytes);
	वापस 0;
पूर्ण

अटल पूर्णांक fence_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक off,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	अचिन्हित पूर्णांक fence_num = offset_to_fence_num(off);
	पूर्णांक ret;

	ret = sanitize_fence_mmio_access(vgpu, fence_num, p_data, bytes);
	अगर (ret)
		वापस ret;
	ग_लिखो_vreg(vgpu, off, p_data, bytes);

	mmio_hw_access_pre(gvt->gt);
	पूर्णांकel_vgpu_ग_लिखो_fence(vgpu, fence_num,
			vgpu_vreg64(vgpu, fence_num_to_offset(fence_num)));
	mmio_hw_access_post(gvt->gt);
	वापस 0;
पूर्ण

#घोषणा CALC_MODE_MASK_REG(old, new) \
	(((new) & GENMASK(31, 16)) \
	 | ((((old) & GENMASK(15, 0)) & ~((new) >> 16)) \
	 | ((new) & ((new) >> 16))))

अटल पूर्णांक mul_क्रमce_wake_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 old, new;
	u32 ack_reg_offset;

	old = vgpu_vreg(vgpu, offset);
	new = CALC_MODE_MASK_REG(old, *(u32 *)p_data);

	अगर (INTEL_GEN(vgpu->gvt->gt->i915)  >=  9) अणु
		चयन (offset) अणु
		हाल FORCEWAKE_RENDER_GEN9_REG:
			ack_reg_offset = FORCEWAKE_ACK_RENDER_GEN9_REG;
			अवरोध;
		हाल FORCEWAKE_GT_GEN9_REG:
			ack_reg_offset = FORCEWAKE_ACK_GT_GEN9_REG;
			अवरोध;
		हाल FORCEWAKE_MEDIA_GEN9_REG:
			ack_reg_offset = FORCEWAKE_ACK_MEDIA_GEN9_REG;
			अवरोध;
		शेष:
			/*should not hit here*/
			gvt_vgpu_err("invalid forcewake offset 0x%x\n", offset);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		ack_reg_offset = FORCEWAKE_ACK_HSW_REG;
	पूर्ण

	vgpu_vreg(vgpu, offset) = new;
	vgpu_vreg(vgpu, ack_reg_offset) = (new & GENMASK(15, 0));
	वापस 0;
पूर्ण

अटल पूर्णांक gdrst_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
			    व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	पूर्णांकel_engine_mask_t engine_mask = 0;
	u32 data;

	ग_लिखो_vreg(vgpu, offset, p_data, bytes);
	data = vgpu_vreg(vgpu, offset);

	अगर (data & GEN6_GRDOM_FULL) अणु
		gvt_dbg_mmio("vgpu%d: request full GPU reset\n", vgpu->id);
		engine_mask = ALL_ENGINES;
	पूर्ण अन्यथा अणु
		अगर (data & GEN6_GRDOM_RENDER) अणु
			gvt_dbg_mmio("vgpu%d: request RCS reset\n", vgpu->id);
			engine_mask |= BIT(RCS0);
		पूर्ण
		अगर (data & GEN6_GRDOM_MEDIA) अणु
			gvt_dbg_mmio("vgpu%d: request VCS reset\n", vgpu->id);
			engine_mask |= BIT(VCS0);
		पूर्ण
		अगर (data & GEN6_GRDOM_BLT) अणु
			gvt_dbg_mmio("vgpu%d: request BCS Reset\n", vgpu->id);
			engine_mask |= BIT(BCS0);
		पूर्ण
		अगर (data & GEN6_GRDOM_VECS) अणु
			gvt_dbg_mmio("vgpu%d: request VECS Reset\n", vgpu->id);
			engine_mask |= BIT(VECS0);
		पूर्ण
		अगर (data & GEN8_GRDOM_MEDIA2) अणु
			gvt_dbg_mmio("vgpu%d: request VCS2 Reset\n", vgpu->id);
			engine_mask |= BIT(VCS1);
		पूर्ण
		अगर (data & GEN9_GRDOM_GUC) अणु
			gvt_dbg_mmio("vgpu%d: request GUC Reset\n", vgpu->id);
			vgpu_vreg_t(vgpu, GUC_STATUS) |= GS_MIA_IN_RESET;
		पूर्ण
		engine_mask &= vgpu->gvt->gt->info.engine_mask;
	पूर्ण

	/* vgpu_lock alपढ़ोy hold by emulate mmio r/w */
	पूर्णांकel_gvt_reset_vgpu_locked(vgpu, false, engine_mask);

	/* sw will रुको क्रम the device to ack the reset request */
	vgpu_vreg(vgpu, offset) = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक gmbus_mmio_पढ़ो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	वापस पूर्णांकel_gvt_i2c_handle_gmbus_पढ़ो(vgpu, offset, p_data, bytes);
पूर्ण

अटल पूर्णांक gmbus_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	वापस पूर्णांकel_gvt_i2c_handle_gmbus_ग_लिखो(vgpu, offset, p_data, bytes);
पूर्ण

अटल पूर्णांक pch_pp_control_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	ग_लिखो_vreg(vgpu, offset, p_data, bytes);

	अगर (vgpu_vreg(vgpu, offset) & PANEL_POWER_ON) अणु
		vgpu_vreg_t(vgpu, PCH_PP_STATUS) |= PP_ON;
		vgpu_vreg_t(vgpu, PCH_PP_STATUS) |= PP_SEQUENCE_STATE_ON_IDLE;
		vgpu_vreg_t(vgpu, PCH_PP_STATUS) &= ~PP_SEQUENCE_POWER_DOWN;
		vgpu_vreg_t(vgpu, PCH_PP_STATUS) &= ~PP_CYCLE_DELAY_ACTIVE;

	पूर्ण अन्यथा
		vgpu_vreg_t(vgpu, PCH_PP_STATUS) &=
			~(PP_ON | PP_SEQUENCE_POWER_DOWN
					| PP_CYCLE_DELAY_ACTIVE);
	वापस 0;
पूर्ण

अटल पूर्णांक transconf_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	ग_लिखो_vreg(vgpu, offset, p_data, bytes);

	अगर (vgpu_vreg(vgpu, offset) & TRANS_ENABLE)
		vgpu_vreg(vgpu, offset) |= TRANS_STATE_ENABLE;
	अन्यथा
		vgpu_vreg(vgpu, offset) &= ~TRANS_STATE_ENABLE;
	वापस 0;
पूर्ण

अटल पूर्णांक lcpll_ctl_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	ग_लिखो_vreg(vgpu, offset, p_data, bytes);

	अगर (vgpu_vreg(vgpu, offset) & LCPLL_PLL_DISABLE)
		vgpu_vreg(vgpu, offset) &= ~LCPLL_PLL_LOCK;
	अन्यथा
		vgpu_vreg(vgpu, offset) |= LCPLL_PLL_LOCK;

	अगर (vgpu_vreg(vgpu, offset) & LCPLL_CD_SOURCE_FCLK)
		vgpu_vreg(vgpu, offset) |= LCPLL_CD_SOURCE_FCLK_DONE;
	अन्यथा
		vgpu_vreg(vgpu, offset) &= ~LCPLL_CD_SOURCE_FCLK_DONE;

	वापस 0;
पूर्ण

अटल पूर्णांक dpy_reg_mmio_पढ़ो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	चयन (offset) अणु
	हाल 0xe651c:
	हाल 0xe661c:
	हाल 0xe671c:
	हाल 0xe681c:
		vgpu_vreg(vgpu, offset) = 1 << 17;
		अवरोध;
	हाल 0xe6c04:
		vgpu_vreg(vgpu, offset) = 0x3;
		अवरोध;
	हाल 0xe6e1c:
		vgpu_vreg(vgpu, offset) = 0x2f << 16;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	पढ़ो_vreg(vgpu, offset, p_data, bytes);
	वापस 0;
पूर्ण

/*
 * Only PIPE_A is enabled in current vGPU display and PIPE_A is tied to
 *   TRANSCODER_A in HW. DDI/PORT could be PORT_x depends on
 *   setup_भव_dp_monitor().
 * emulate_monitor_status_change() set up PLL क्रम PORT_x as the initial enabled
 *   DPLL. Later guest driver may setup a dअगरferent DPLLx when setting mode.
 * So the correct sequence to find DP stream घड़ी is:
 *   Check TRANS_DDI_FUNC_CTL on TRANSCODER_A to get PORT_x.
 *   Check correct PLLx क्रम PORT_x to get PLL frequency and DP bitrate.
 * Then Refresh rate then can be calculated based on follow equations:
 *   Pixel घड़ी = h_total * v_total * refresh_rate
 *   stream घड़ी = Pixel घड़ी
 *   ls_clk = DP bitrate
 *   Link M/N = strm_clk / ls_clk
 */

अटल u32 bdw_vgpu_get_dp_bitrate(काष्ठा पूर्णांकel_vgpu *vgpu, क्रमागत port port)
अणु
	u32 dp_br = 0;
	u32 ddi_pll_sel = vgpu_vreg_t(vgpu, PORT_CLK_SEL(port));

	चयन (ddi_pll_sel) अणु
	हाल PORT_CLK_SEL_LCPLL_2700:
		dp_br = 270000 * 2;
		अवरोध;
	हाल PORT_CLK_SEL_LCPLL_1350:
		dp_br = 135000 * 2;
		अवरोध;
	हाल PORT_CLK_SEL_LCPLL_810:
		dp_br = 81000 * 2;
		अवरोध;
	हाल PORT_CLK_SEL_SPLL:
	अणु
		चयन (vgpu_vreg_t(vgpu, SPLL_CTL) & SPLL_FREQ_MASK) अणु
		हाल SPLL_FREQ_810MHz:
			dp_br = 81000 * 2;
			अवरोध;
		हाल SPLL_FREQ_1350MHz:
			dp_br = 135000 * 2;
			अवरोध;
		हाल SPLL_FREQ_2700MHz:
			dp_br = 270000 * 2;
			अवरोध;
		शेष:
			gvt_dbg_dpy("vgpu-%d PORT_%c can't get freq from SPLL 0x%08x\n",
				    vgpu->id, port_name(port), vgpu_vreg_t(vgpu, SPLL_CTL));
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल PORT_CLK_SEL_WRPLL1:
	हाल PORT_CLK_SEL_WRPLL2:
	अणु
		u32 wrpll_ctl;
		पूर्णांक refclk, n, p, r;

		अगर (ddi_pll_sel == PORT_CLK_SEL_WRPLL1)
			wrpll_ctl = vgpu_vreg_t(vgpu, WRPLL_CTL(DPLL_ID_WRPLL1));
		अन्यथा
			wrpll_ctl = vgpu_vreg_t(vgpu, WRPLL_CTL(DPLL_ID_WRPLL2));

		चयन (wrpll_ctl & WRPLL_REF_MASK) अणु
		हाल WRPLL_REF_PCH_SSC:
			refclk = vgpu->gvt->gt->i915->dpll.ref_clks.ssc;
			अवरोध;
		हाल WRPLL_REF_LCPLL:
			refclk = 2700000;
			अवरोध;
		शेष:
			gvt_dbg_dpy("vgpu-%d PORT_%c WRPLL can't get refclk 0x%08x\n",
				    vgpu->id, port_name(port), wrpll_ctl);
			जाओ out;
		पूर्ण

		r = wrpll_ctl & WRPLL_DIVIDER_REF_MASK;
		p = (wrpll_ctl & WRPLL_DIVIDER_POST_MASK) >> WRPLL_DIVIDER_POST_SHIFT;
		n = (wrpll_ctl & WRPLL_DIVIDER_FB_MASK) >> WRPLL_DIVIDER_FB_SHIFT;

		dp_br = (refclk * n / 10) / (p * r) * 2;
		अवरोध;
	पूर्ण
	शेष:
		gvt_dbg_dpy("vgpu-%d PORT_%c has invalid clock select 0x%08x\n",
			    vgpu->id, port_name(port), vgpu_vreg_t(vgpu, PORT_CLK_SEL(port)));
		अवरोध;
	पूर्ण

out:
	वापस dp_br;
पूर्ण

अटल u32 bxt_vgpu_get_dp_bitrate(काष्ठा पूर्णांकel_vgpu *vgpu, क्रमागत port port)
अणु
	u32 dp_br = 0;
	पूर्णांक refclk = vgpu->gvt->gt->i915->dpll.ref_clks.nssc;
	क्रमागत dpio_phy phy = DPIO_PHY0;
	क्रमागत dpio_channel ch = DPIO_CH0;
	काष्ठा dpll घड़ी = अणु0पूर्ण;
	u32 temp;

	/* Port to PHY mapping is fixed, see bxt_ddi_phy_infoअणुपूर्ण */
	चयन (port) अणु
	हाल PORT_A:
		phy = DPIO_PHY1;
		ch = DPIO_CH0;
		अवरोध;
	हाल PORT_B:
		phy = DPIO_PHY0;
		ch = DPIO_CH0;
		अवरोध;
	हाल PORT_C:
		phy = DPIO_PHY0;
		ch = DPIO_CH1;
		अवरोध;
	शेष:
		gvt_dbg_dpy("vgpu-%d no PHY for PORT_%c\n", vgpu->id, port_name(port));
		जाओ out;
	पूर्ण

	temp = vgpu_vreg_t(vgpu, BXT_PORT_PLL_ENABLE(port));
	अगर (!(temp & PORT_PLL_ENABLE) || !(temp & PORT_PLL_LOCK)) अणु
		gvt_dbg_dpy("vgpu-%d PORT_%c PLL_ENABLE 0x%08x isn't enabled or locked\n",
			    vgpu->id, port_name(port), temp);
		जाओ out;
	पूर्ण

	घड़ी.m1 = 2;
	घड़ी.m2 = (vgpu_vreg_t(vgpu, BXT_PORT_PLL(phy, ch, 0)) & PORT_PLL_M2_MASK) << 22;
	अगर (vgpu_vreg_t(vgpu, BXT_PORT_PLL(phy, ch, 3)) & PORT_PLL_M2_FRAC_ENABLE)
		घड़ी.m2 |= vgpu_vreg_t(vgpu, BXT_PORT_PLL(phy, ch, 2)) & PORT_PLL_M2_FRAC_MASK;
	घड़ी.n = (vgpu_vreg_t(vgpu, BXT_PORT_PLL(phy, ch, 1)) & PORT_PLL_N_MASK) >> PORT_PLL_N_SHIFT;
	घड़ी.p1 = (vgpu_vreg_t(vgpu, BXT_PORT_PLL_EBB_0(phy, ch)) & PORT_PLL_P1_MASK) >> PORT_PLL_P1_SHIFT;
	घड़ी.p2 = (vgpu_vreg_t(vgpu, BXT_PORT_PLL_EBB_0(phy, ch)) & PORT_PLL_P2_MASK) >> PORT_PLL_P2_SHIFT;
	घड़ी.m = घड़ी.m1 * घड़ी.m2;
	घड़ी.p = घड़ी.p1 * घड़ी.p2;

	अगर (घड़ी.n == 0 || घड़ी.p == 0) अणु
		gvt_dbg_dpy("vgpu-%d PORT_%c PLL has invalid divider\n", vgpu->id, port_name(port));
		जाओ out;
	पूर्ण

	घड़ी.vco = DIV_ROUND_CLOSEST_ULL(mul_u32_u32(refclk, घड़ी.m), घड़ी.n << 22);
	घड़ी.करोt = DIV_ROUND_CLOSEST(घड़ी.vco, घड़ी.p);

	dp_br = घड़ी.करोt / 5;

out:
	वापस dp_br;
पूर्ण

अटल u32 skl_vgpu_get_dp_bitrate(काष्ठा पूर्णांकel_vgpu *vgpu, क्रमागत port port)
अणु
	u32 dp_br = 0;
	क्रमागत पूर्णांकel_dpll_id dpll_id = DPLL_ID_SKL_DPLL0;

	/* Find the enabled DPLL क्रम the DDI/PORT */
	अगर (!(vgpu_vreg_t(vgpu, DPLL_CTRL2) & DPLL_CTRL2_DDI_CLK_OFF(port)) &&
	    (vgpu_vreg_t(vgpu, DPLL_CTRL2) & DPLL_CTRL2_DDI_SEL_OVERRIDE(port))) अणु
		dpll_id += (vgpu_vreg_t(vgpu, DPLL_CTRL2) &
			DPLL_CTRL2_DDI_CLK_SEL_MASK(port)) >>
			DPLL_CTRL2_DDI_CLK_SEL_SHIFT(port);
	पूर्ण अन्यथा अणु
		gvt_dbg_dpy("vgpu-%d DPLL for PORT_%c isn't turned on\n",
			    vgpu->id, port_name(port));
		वापस dp_br;
	पूर्ण

	/* Find PLL output frequency from correct DPLL, and get bir rate */
	चयन ((vgpu_vreg_t(vgpu, DPLL_CTRL1) &
		DPLL_CTRL1_LINK_RATE_MASK(dpll_id)) >>
		DPLL_CTRL1_LINK_RATE_SHIFT(dpll_id)) अणु
		हाल DPLL_CTRL1_LINK_RATE_810:
			dp_br = 81000 * 2;
			अवरोध;
		हाल DPLL_CTRL1_LINK_RATE_1080:
			dp_br = 108000 * 2;
			अवरोध;
		हाल DPLL_CTRL1_LINK_RATE_1350:
			dp_br = 135000 * 2;
			अवरोध;
		हाल DPLL_CTRL1_LINK_RATE_1620:
			dp_br = 162000 * 2;
			अवरोध;
		हाल DPLL_CTRL1_LINK_RATE_2160:
			dp_br = 216000 * 2;
			अवरोध;
		हाल DPLL_CTRL1_LINK_RATE_2700:
			dp_br = 270000 * 2;
			अवरोध;
		शेष:
			dp_br = 0;
			gvt_dbg_dpy("vgpu-%d PORT_%c fail to get DPLL-%d freq\n",
				    vgpu->id, port_name(port), dpll_id);
	पूर्ण

	वापस dp_br;
पूर्ण

अटल व्योम vgpu_update_refresh_rate(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा drm_i915_निजी *dev_priv = vgpu->gvt->gt->i915;
	क्रमागत port port;
	u32 dp_br, link_m, link_n, htotal, vtotal;

	/* Find DDI/PORT asचिन्हित to TRANSCODER_A, expect B or D */
	port = (vgpu_vreg_t(vgpu, TRANS_DDI_FUNC_CTL(TRANSCODER_A)) &
		TRANS_DDI_PORT_MASK) >> TRANS_DDI_PORT_SHIFT;
	अगर (port != PORT_B && port != PORT_D) अणु
		gvt_dbg_dpy("vgpu-%d unsupported PORT_%c\n", vgpu->id, port_name(port));
		वापस;
	पूर्ण

	/* Calculate DP bitrate from PLL */
	अगर (IS_BROADWELL(dev_priv))
		dp_br = bdw_vgpu_get_dp_bitrate(vgpu, port);
	अन्यथा अगर (IS_BROXTON(dev_priv))
		dp_br = bxt_vgpu_get_dp_bitrate(vgpu, port);
	अन्यथा
		dp_br = skl_vgpu_get_dp_bitrate(vgpu, port);

	/* Get DP link symbol घड़ी M/N */
	link_m = vgpu_vreg_t(vgpu, PIPE_LINK_M1(TRANSCODER_A));
	link_n = vgpu_vreg_t(vgpu, PIPE_LINK_N1(TRANSCODER_A));

	/* Get H/V total from transcoder timing */
	htotal = (vgpu_vreg_t(vgpu, HTOTAL(TRANSCODER_A)) >> TRANS_HTOTAL_SHIFT);
	vtotal = (vgpu_vreg_t(vgpu, VTOTAL(TRANSCODER_A)) >> TRANS_VTOTAL_SHIFT);

	अगर (dp_br && link_n && htotal && vtotal) अणु
		u64 pixel_clk = 0;
		u32 new_rate = 0;
		u32 *old_rate = &(पूर्णांकel_vgpu_port(vgpu, vgpu->display.port_num)->vrefresh_k);

		/* Calcuate pixel घड़ी by (ls_clk * M / N) */
		pixel_clk = भाग_u64(mul_u32_u32(link_m, dp_br), link_n);
		pixel_clk *= MSEC_PER_SEC;

		/* Calcuate refresh rate by (pixel_clk / (h_total * v_total)) */
		new_rate = DIV64_U64_ROUND_CLOSEST(mul_u64_u32_shr(pixel_clk, MSEC_PER_SEC, 0), mul_u32_u32(htotal + 1, vtotal + 1));

		अगर (*old_rate != new_rate)
			*old_rate = new_rate;

		gvt_dbg_dpy("vgpu-%d PIPE_%c refresh rate updated to %d\n",
			    vgpu->id, pipe_name(PIPE_A), new_rate);
	पूर्ण
पूर्ण

अटल पूर्णांक pipeconf_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 data;

	ग_लिखो_vreg(vgpu, offset, p_data, bytes);
	data = vgpu_vreg(vgpu, offset);

	अगर (data & PIPECONF_ENABLE) अणु
		vgpu_vreg(vgpu, offset) |= I965_PIPECONF_ACTIVE;
		vgpu_update_refresh_rate(vgpu);
		vgpu_update_vblank_emulation(vgpu, true);
	पूर्ण अन्यथा अणु
		vgpu_vreg(vgpu, offset) &= ~I965_PIPECONF_ACTIVE;
		vgpu_update_vblank_emulation(vgpu, false);
	पूर्ण
	वापस 0;
पूर्ण

/* sorted in ascending order */
अटल i915_reg_t क्रमce_nonpriv_white_list[] = अणु
	_MMIO(0xd80),
	GEN9_CS_DEBUG_MODE1, //_MMIO(0x20ec)
	GEN9_CTX_PREEMPT_REG,//_MMIO(0x2248)
	CL_PRIMITIVES_COUNT, //_MMIO(0x2340)
	PS_INVOCATION_COUNT, //_MMIO(0x2348)
	PS_DEPTH_COUNT, //_MMIO(0x2350)
	GEN8_CS_CHICKEN1,//_MMIO(0x2580)
	_MMIO(0x2690),
	_MMIO(0x2694),
	_MMIO(0x2698),
	_MMIO(0x2754),
	_MMIO(0x28a0),
	_MMIO(0x4de0),
	_MMIO(0x4de4),
	_MMIO(0x4dfc),
	GEN7_COMMON_SLICE_CHICKEN1,//_MMIO(0x7010)
	_MMIO(0x7014),
	HDC_CHICKEN0,//_MMIO(0x7300)
	GEN8_HDC_CHICKEN1,//_MMIO(0x7304)
	_MMIO(0x7700),
	_MMIO(0x7704),
	_MMIO(0x7708),
	_MMIO(0x770c),
	_MMIO(0x83a8),
	_MMIO(0xb110),
	GEN8_L3SQCREG4,//_MMIO(0xb118)
	_MMIO(0xe100),
	_MMIO(0xe18c),
	_MMIO(0xe48c),
	_MMIO(0xe5f4),
	_MMIO(0x64844),
पूर्ण;

/* a simple द्वा_खोज */
अटल अंतरभूत bool in_whitelist(u32 reg)
अणु
	पूर्णांक left = 0, right = ARRAY_SIZE(क्रमce_nonpriv_white_list);
	i915_reg_t *array = क्रमce_nonpriv_white_list;

	जबतक (left < right) अणु
		पूर्णांक mid = (left + right)/2;

		अगर (reg > array[mid].reg)
			left = mid + 1;
		अन्यथा अगर (reg < array[mid].reg)
			right = mid;
		अन्यथा
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक क्रमce_nonpriv_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
	अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 reg_nonpriv = (*(u32 *)p_data) & REG_GENMASK(25, 2);
	स्थिर काष्ठा पूर्णांकel_engine_cs *engine =
		पूर्णांकel_gvt_render_mmio_to_engine(vgpu->gvt, offset);

	अगर (bytes != 4 || !IS_ALIGNED(offset, bytes) || !engine) अणु
		gvt_err("vgpu(%d) Invalid FORCE_NONPRIV offset %x(%dB)\n",
			vgpu->id, offset, bytes);
		वापस -EINVAL;
	पूर्ण

	अगर (!in_whitelist(reg_nonpriv) &&
	    reg_nonpriv != i915_mmio_reg_offset(RING_NOPID(engine->mmio_base))) अणु
		gvt_err("vgpu(%d) Invalid FORCE_NONPRIV write %x at offset %x\n",
			vgpu->id, reg_nonpriv, offset);
	पूर्ण अन्यथा
		पूर्णांकel_vgpu_शेष_mmio_ग_लिखो(vgpu, offset, p_data, bytes);

	वापस 0;
पूर्ण

अटल पूर्णांक ddi_buf_ctl_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	ग_लिखो_vreg(vgpu, offset, p_data, bytes);

	अगर (vgpu_vreg(vgpu, offset) & DDI_BUF_CTL_ENABLE) अणु
		vgpu_vreg(vgpu, offset) &= ~DDI_BUF_IS_IDLE;
	पूर्ण अन्यथा अणु
		vgpu_vreg(vgpu, offset) |= DDI_BUF_IS_IDLE;
		अगर (offset == i915_mmio_reg_offset(DDI_BUF_CTL(PORT_E)))
			vgpu_vreg_t(vgpu, DP_TP_STATUS(PORT_E))
				&= ~DP_TP_STATUS_AUTOTRAIN_DONE;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fdi_rx_iir_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	vgpu_vreg(vgpu, offset) &= ~*(u32 *)p_data;
	वापस 0;
पूर्ण

#घोषणा FDI_LINK_TRAIN_PATTERN1         0
#घोषणा FDI_LINK_TRAIN_PATTERN2         1

अटल पूर्णांक fdi_स्वतः_training_started(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	u32 ddi_buf_ctl = vgpu_vreg_t(vgpu, DDI_BUF_CTL(PORT_E));
	u32 rx_ctl = vgpu_vreg(vgpu, _FDI_RXA_CTL);
	u32 tx_ctl = vgpu_vreg_t(vgpu, DP_TP_CTL(PORT_E));

	अगर ((ddi_buf_ctl & DDI_BUF_CTL_ENABLE) &&
			(rx_ctl & FDI_RX_ENABLE) &&
			(rx_ctl & FDI_AUTO_TRAINING) &&
			(tx_ctl & DP_TP_CTL_ENABLE) &&
			(tx_ctl & DP_TP_CTL_FDI_AUTOTRAIN))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक check_fdi_rx_train_status(काष्ठा पूर्णांकel_vgpu *vgpu,
		क्रमागत pipe pipe, अचिन्हित पूर्णांक train_pattern)
अणु
	i915_reg_t fdi_rx_imr, fdi_tx_ctl, fdi_rx_ctl;
	अचिन्हित पूर्णांक fdi_rx_check_bits, fdi_tx_check_bits;
	अचिन्हित पूर्णांक fdi_rx_train_bits, fdi_tx_train_bits;
	अचिन्हित पूर्णांक fdi_iir_check_bits;

	fdi_rx_imr = FDI_RX_IMR(pipe);
	fdi_tx_ctl = FDI_TX_CTL(pipe);
	fdi_rx_ctl = FDI_RX_CTL(pipe);

	अगर (train_pattern == FDI_LINK_TRAIN_PATTERN1) अणु
		fdi_rx_train_bits = FDI_LINK_TRAIN_PATTERN_1_CPT;
		fdi_tx_train_bits = FDI_LINK_TRAIN_PATTERN_1;
		fdi_iir_check_bits = FDI_RX_BIT_LOCK;
	पूर्ण अन्यथा अगर (train_pattern == FDI_LINK_TRAIN_PATTERN2) अणु
		fdi_rx_train_bits = FDI_LINK_TRAIN_PATTERN_2_CPT;
		fdi_tx_train_bits = FDI_LINK_TRAIN_PATTERN_2;
		fdi_iir_check_bits = FDI_RX_SYMBOL_LOCK;
	पूर्ण अन्यथा अणु
		gvt_vgpu_err("Invalid train pattern %d\n", train_pattern);
		वापस -EINVAL;
	पूर्ण

	fdi_rx_check_bits = FDI_RX_ENABLE | fdi_rx_train_bits;
	fdi_tx_check_bits = FDI_TX_ENABLE | fdi_tx_train_bits;

	/* If imr bit has been masked */
	अगर (vgpu_vreg_t(vgpu, fdi_rx_imr) & fdi_iir_check_bits)
		वापस 0;

	अगर (((vgpu_vreg_t(vgpu, fdi_tx_ctl) & fdi_tx_check_bits)
			== fdi_tx_check_bits)
		&& ((vgpu_vreg_t(vgpu, fdi_rx_ctl) & fdi_rx_check_bits)
			== fdi_rx_check_bits))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

#घोषणा INVALID_INDEX (~0U)

अटल अचिन्हित पूर्णांक calc_index(अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक start,
	अचिन्हित पूर्णांक next, अचिन्हित पूर्णांक end, i915_reg_t i915_end)
अणु
	अचिन्हित पूर्णांक range = next - start;

	अगर (!end)
		end = i915_mmio_reg_offset(i915_end);
	अगर (offset < start || offset > end)
		वापस INVALID_INDEX;
	offset -= start;
	वापस offset / range;
पूर्ण

#घोषणा FDI_RX_CTL_TO_PIPE(offset) \
	calc_index(offset, _FDI_RXA_CTL, _FDI_RXB_CTL, 0, FDI_RX_CTL(PIPE_C))

#घोषणा FDI_TX_CTL_TO_PIPE(offset) \
	calc_index(offset, _FDI_TXA_CTL, _FDI_TXB_CTL, 0, FDI_TX_CTL(PIPE_C))

#घोषणा FDI_RX_IMR_TO_PIPE(offset) \
	calc_index(offset, _FDI_RXA_IMR, _FDI_RXB_IMR, 0, FDI_RX_IMR(PIPE_C))

अटल पूर्णांक update_fdi_rx_iir_status(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	i915_reg_t fdi_rx_iir;
	अचिन्हित पूर्णांक index;
	पूर्णांक ret;

	अगर (FDI_RX_CTL_TO_PIPE(offset) != INVALID_INDEX)
		index = FDI_RX_CTL_TO_PIPE(offset);
	अन्यथा अगर (FDI_TX_CTL_TO_PIPE(offset) != INVALID_INDEX)
		index = FDI_TX_CTL_TO_PIPE(offset);
	अन्यथा अगर (FDI_RX_IMR_TO_PIPE(offset) != INVALID_INDEX)
		index = FDI_RX_IMR_TO_PIPE(offset);
	अन्यथा अणु
		gvt_vgpu_err("Unsupport registers %x\n", offset);
		वापस -EINVAL;
	पूर्ण

	ग_लिखो_vreg(vgpu, offset, p_data, bytes);

	fdi_rx_iir = FDI_RX_IIR(index);

	ret = check_fdi_rx_train_status(vgpu, index, FDI_LINK_TRAIN_PATTERN1);
	अगर (ret < 0)
		वापस ret;
	अगर (ret)
		vgpu_vreg_t(vgpu, fdi_rx_iir) |= FDI_RX_BIT_LOCK;

	ret = check_fdi_rx_train_status(vgpu, index, FDI_LINK_TRAIN_PATTERN2);
	अगर (ret < 0)
		वापस ret;
	अगर (ret)
		vgpu_vreg_t(vgpu, fdi_rx_iir) |= FDI_RX_SYMBOL_LOCK;

	अगर (offset == _FDI_RXA_CTL)
		अगर (fdi_स्वतः_training_started(vgpu))
			vgpu_vreg_t(vgpu, DP_TP_STATUS(PORT_E)) |=
				DP_TP_STATUS_AUTOTRAIN_DONE;
	वापस 0;
पूर्ण

#घोषणा DP_TP_CTL_TO_PORT(offset) \
	calc_index(offset, _DP_TP_CTL_A, _DP_TP_CTL_B, 0, DP_TP_CTL(PORT_E))

अटल पूर्णांक dp_tp_ctl_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	i915_reg_t status_reg;
	अचिन्हित पूर्णांक index;
	u32 data;

	ग_लिखो_vreg(vgpu, offset, p_data, bytes);

	index = DP_TP_CTL_TO_PORT(offset);
	data = (vgpu_vreg(vgpu, offset) & GENMASK(10, 8)) >> 8;
	अगर (data == 0x2) अणु
		status_reg = DP_TP_STATUS(index);
		vgpu_vreg_t(vgpu, status_reg) |= (1 << 25);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dp_tp_status_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 reg_val;
	u32 sticky_mask;

	reg_val = *((u32 *)p_data);
	sticky_mask = GENMASK(27, 26) | (1 << 24);

	vgpu_vreg(vgpu, offset) = (reg_val & ~sticky_mask) |
		(vgpu_vreg(vgpu, offset) & sticky_mask);
	vgpu_vreg(vgpu, offset) &= ~(reg_val & sticky_mask);
	वापस 0;
पूर्ण

अटल पूर्णांक pch_adpa_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 data;

	ग_लिखो_vreg(vgpu, offset, p_data, bytes);
	data = vgpu_vreg(vgpu, offset);

	अगर (data & ADPA_CRT_HOTPLUG_FORCE_TRIGGER)
		vgpu_vreg(vgpu, offset) &= ~ADPA_CRT_HOTPLUG_FORCE_TRIGGER;
	वापस 0;
पूर्ण

अटल पूर्णांक south_chicken2_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 data;

	ग_लिखो_vreg(vgpu, offset, p_data, bytes);
	data = vgpu_vreg(vgpu, offset);

	अगर (data & FDI_MPHY_IOSFSB_RESET_CTL)
		vgpu_vreg(vgpu, offset) |= FDI_MPHY_IOSFSB_RESET_STATUS;
	अन्यथा
		vgpu_vreg(vgpu, offset) &= ~FDI_MPHY_IOSFSB_RESET_STATUS;
	वापस 0;
पूर्ण

#घोषणा DSPSURF_TO_PIPE(offset) \
	calc_index(offset, _DSPASURF, _DSPBSURF, 0, DSPSURF(PIPE_C))

अटल पूर्णांक pri_surf_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा drm_i915_निजी *dev_priv = vgpu->gvt->gt->i915;
	u32 pipe = DSPSURF_TO_PIPE(offset);
	पूर्णांक event = SKL_FLIP_EVENT(pipe, PLANE_PRIMARY);

	ग_लिखो_vreg(vgpu, offset, p_data, bytes);
	vgpu_vreg_t(vgpu, DSPSURFLIVE(pipe)) = vgpu_vreg(vgpu, offset);

	vgpu_vreg_t(vgpu, PIPE_FLIPCOUNT_G4X(pipe))++;

	अगर (vgpu_vreg_t(vgpu, DSPCNTR(pipe)) & PLANE_CTL_ASYNC_FLIP)
		पूर्णांकel_vgpu_trigger_भव_event(vgpu, event);
	अन्यथा
		set_bit(event, vgpu->irq.flip_करोne_event[pipe]);

	वापस 0;
पूर्ण

#घोषणा SPRSURF_TO_PIPE(offset) \
	calc_index(offset, _SPRA_SURF, _SPRB_SURF, 0, SPRSURF(PIPE_C))

अटल पूर्णांक spr_surf_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 pipe = SPRSURF_TO_PIPE(offset);
	पूर्णांक event = SKL_FLIP_EVENT(pipe, PLANE_SPRITE0);

	ग_लिखो_vreg(vgpu, offset, p_data, bytes);
	vgpu_vreg_t(vgpu, SPRSURFLIVE(pipe)) = vgpu_vreg(vgpu, offset);

	अगर (vgpu_vreg_t(vgpu, SPRCTL(pipe)) & PLANE_CTL_ASYNC_FLIP)
		पूर्णांकel_vgpu_trigger_भव_event(vgpu, event);
	अन्यथा
		set_bit(event, vgpu->irq.flip_करोne_event[pipe]);

	वापस 0;
पूर्ण

अटल पूर्णांक reg50080_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
			       अचिन्हित पूर्णांक offset, व्योम *p_data,
			       अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा drm_i915_निजी *dev_priv = vgpu->gvt->gt->i915;
	क्रमागत pipe pipe = REG_50080_TO_PIPE(offset);
	क्रमागत plane_id plane = REG_50080_TO_PLANE(offset);
	पूर्णांक event = SKL_FLIP_EVENT(pipe, plane);

	ग_लिखो_vreg(vgpu, offset, p_data, bytes);
	अगर (plane == PLANE_PRIMARY) अणु
		vgpu_vreg_t(vgpu, DSPSURFLIVE(pipe)) = vgpu_vreg(vgpu, offset);
		vgpu_vreg_t(vgpu, PIPE_FLIPCOUNT_G4X(pipe))++;
	पूर्ण अन्यथा अणु
		vgpu_vreg_t(vgpu, SPRSURFLIVE(pipe)) = vgpu_vreg(vgpu, offset);
	पूर्ण

	अगर ((vgpu_vreg(vgpu, offset) & REG50080_FLIP_TYPE_MASK) == REG50080_FLIP_TYPE_ASYNC)
		पूर्णांकel_vgpu_trigger_भव_event(vgpu, event);
	अन्यथा
		set_bit(event, vgpu->irq.flip_करोne_event[pipe]);

	वापस 0;
पूर्ण

अटल पूर्णांक trigger_aux_channel_पूर्णांकerrupt(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक reg)
अणु
	काष्ठा drm_i915_निजी *dev_priv = vgpu->gvt->gt->i915;
	क्रमागत पूर्णांकel_gvt_event_type event;

	अगर (reg == i915_mmio_reg_offset(DP_AUX_CH_CTL(AUX_CH_A)))
		event = AUX_CHANNEL_A;
	अन्यथा अगर (reg == _PCH_DPB_AUX_CH_CTL ||
		 reg == i915_mmio_reg_offset(DP_AUX_CH_CTL(AUX_CH_B)))
		event = AUX_CHANNEL_B;
	अन्यथा अगर (reg == _PCH_DPC_AUX_CH_CTL ||
		 reg == i915_mmio_reg_offset(DP_AUX_CH_CTL(AUX_CH_C)))
		event = AUX_CHANNEL_C;
	अन्यथा अगर (reg == _PCH_DPD_AUX_CH_CTL ||
		 reg == i915_mmio_reg_offset(DP_AUX_CH_CTL(AUX_CH_D)))
		event = AUX_CHANNEL_D;
	अन्यथा अणु
		drm_WARN_ON(&dev_priv->drm, true);
		वापस -EINVAL;
	पूर्ण

	पूर्णांकel_vgpu_trigger_भव_event(vgpu, event);
	वापस 0;
पूर्ण

अटल पूर्णांक dp_aux_ch_ctl_trans_करोne(काष्ठा पूर्णांकel_vgpu *vgpu, u32 value,
		अचिन्हित पूर्णांक reg, पूर्णांक len, bool data_valid)
अणु
	/* mark transaction करोne */
	value |= DP_AUX_CH_CTL_DONE;
	value &= ~DP_AUX_CH_CTL_SEND_BUSY;
	value &= ~DP_AUX_CH_CTL_RECEIVE_ERROR;

	अगर (data_valid)
		value &= ~DP_AUX_CH_CTL_TIME_OUT_ERROR;
	अन्यथा
		value |= DP_AUX_CH_CTL_TIME_OUT_ERROR;

	/* message size */
	value &= ~(0xf << 20);
	value |= (len << 20);
	vgpu_vreg(vgpu, reg) = value;

	अगर (value & DP_AUX_CH_CTL_INTERRUPT)
		वापस trigger_aux_channel_पूर्णांकerrupt(vgpu, reg);
	वापस 0;
पूर्ण

अटल व्योम dp_aux_ch_ctl_link_training(काष्ठा पूर्णांकel_vgpu_dpcd_data *dpcd,
		u8 t)
अणु
	अगर ((t & DPCD_TRAINING_PATTERN_SET_MASK) == DPCD_TRAINING_PATTERN_1) अणु
		/* training pattern 1 क्रम CR */
		/* set LANE0_CR_DONE, LANE1_CR_DONE */
		dpcd->data[DPCD_LANE0_1_STATUS] |= DPCD_LANES_CR_DONE;
		/* set LANE2_CR_DONE, LANE3_CR_DONE */
		dpcd->data[DPCD_LANE2_3_STATUS] |= DPCD_LANES_CR_DONE;
	पूर्ण अन्यथा अगर ((t & DPCD_TRAINING_PATTERN_SET_MASK) ==
			DPCD_TRAINING_PATTERN_2) अणु
		/* training pattern 2 क्रम EQ */
		/* Set CHANNEL_EQ_DONE and  SYMBOL_LOCKED क्रम Lane0_1 */
		dpcd->data[DPCD_LANE0_1_STATUS] |= DPCD_LANES_EQ_DONE;
		dpcd->data[DPCD_LANE0_1_STATUS] |= DPCD_SYMBOL_LOCKED;
		/* Set CHANNEL_EQ_DONE and  SYMBOL_LOCKED क्रम Lane2_3 */
		dpcd->data[DPCD_LANE2_3_STATUS] |= DPCD_LANES_EQ_DONE;
		dpcd->data[DPCD_LANE2_3_STATUS] |= DPCD_SYMBOL_LOCKED;
		/* set INTERLANE_ALIGN_DONE */
		dpcd->data[DPCD_LANE_ALIGN_STATUS_UPDATED] |=
			DPCD_INTERLANE_ALIGN_DONE;
	पूर्ण अन्यथा अगर ((t & DPCD_TRAINING_PATTERN_SET_MASK) ==
			DPCD_LINK_TRAINING_DISABLED) अणु
		/* finish link training */
		/* set sink status as synchronized */
		dpcd->data[DPCD_SINK_STATUS] = DPCD_SINK_IN_SYNC;
	पूर्ण
पूर्ण

#घोषणा _REG_HSW_DP_AUX_CH_CTL(dp) \
	((dp) ? (_PCH_DPB_AUX_CH_CTL + ((dp)-1)*0x100) : 0x64010)

#घोषणा _REG_SKL_DP_AUX_CH_CTL(dp) (0x64010 + (dp) * 0x100)

#घोषणा OFFSET_TO_DP_AUX_PORT(offset) (((offset) & 0xF00) >> 8)

#घोषणा dpy_is_valid_port(port)	\
		(((port) >= PORT_A) && ((port) < I915_MAX_PORTS))

अटल पूर्णांक dp_aux_ch_ctl_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा पूर्णांकel_vgpu_display *display = &vgpu->display;
	पूर्णांक msg, addr, ctrl, op, len;
	पूर्णांक port_index = OFFSET_TO_DP_AUX_PORT(offset);
	काष्ठा पूर्णांकel_vgpu_dpcd_data *dpcd = शून्य;
	काष्ठा पूर्णांकel_vgpu_port *port = शून्य;
	u32 data;

	अगर (!dpy_is_valid_port(port_index)) अणु
		gvt_vgpu_err("Unsupported DP port access!\n");
		वापस 0;
	पूर्ण

	ग_लिखो_vreg(vgpu, offset, p_data, bytes);
	data = vgpu_vreg(vgpu, offset);

	अगर ((INTEL_GEN(vgpu->gvt->gt->i915) >= 9)
		&& offset != _REG_SKL_DP_AUX_CH_CTL(port_index)) अणु
		/* SKL DPB/C/D aux ctl रेजिस्टर changed */
		वापस 0;
	पूर्ण अन्यथा अगर (IS_BROADWELL(vgpu->gvt->gt->i915) &&
		   offset != _REG_HSW_DP_AUX_CH_CTL(port_index)) अणु
		/* ग_लिखो to the data रेजिस्टरs */
		वापस 0;
	पूर्ण

	अगर (!(data & DP_AUX_CH_CTL_SEND_BUSY)) अणु
		/* just want to clear the sticky bits */
		vgpu_vreg(vgpu, offset) = 0;
		वापस 0;
	पूर्ण

	port = &display->ports[port_index];
	dpcd = port->dpcd;

	/* पढ़ो out message from DATA1 रेजिस्टर */
	msg = vgpu_vreg(vgpu, offset + 4);
	addr = (msg >> 8) & 0xffff;
	ctrl = (msg >> 24) & 0xff;
	len = msg & 0xff;
	op = ctrl >> 4;

	अगर (op == GVT_AUX_NATIVE_WRITE) अणु
		पूर्णांक t;
		u8 buf[16];

		अगर ((addr + len + 1) >= DPCD_SIZE) अणु
			/*
			 * Write request exceeds what we supported,
			 * DCPD spec: When a Source Device is writing a DPCD
			 * address not supported by the Sink Device, the Sink
			 * Device shall reply with AUX NACK and ै Mै  equal to
			 * zero.
			 */

			/* NAK the ग_लिखो */
			vgpu_vreg(vgpu, offset + 4) = AUX_NATIVE_REPLY_NAK;
			dp_aux_ch_ctl_trans_करोne(vgpu, data, offset, 2, true);
			वापस 0;
		पूर्ण

		/*
		 * Write request क्रमmat: Headr (command + address + size) occupies
		 * 4 bytes, followed by (len + 1) bytes of data. See details at
		 * पूर्णांकel_dp_aux_transfer().
		 */
		अगर ((len + 1 + 4) > AUX_BURST_SIZE) अणु
			gvt_vgpu_err("dp_aux_header: len %d is too large\n", len);
			वापस -EINVAL;
		पूर्ण

		/* unpack data from vreg to buf */
		क्रम (t = 0; t < 4; t++) अणु
			u32 r = vgpu_vreg(vgpu, offset + 8 + t * 4);

			buf[t * 4] = (r >> 24) & 0xff;
			buf[t * 4 + 1] = (r >> 16) & 0xff;
			buf[t * 4 + 2] = (r >> 8) & 0xff;
			buf[t * 4 + 3] = r & 0xff;
		पूर्ण

		/* ग_लिखो to भव DPCD */
		अगर (dpcd && dpcd->data_valid) अणु
			क्रम (t = 0; t <= len; t++) अणु
				पूर्णांक p = addr + t;

				dpcd->data[p] = buf[t];
				/* check क्रम link training */
				अगर (p == DPCD_TRAINING_PATTERN_SET)
					dp_aux_ch_ctl_link_training(dpcd,
							buf[t]);
			पूर्ण
		पूर्ण

		/* ACK the ग_लिखो */
		vgpu_vreg(vgpu, offset + 4) = 0;
		dp_aux_ch_ctl_trans_करोne(vgpu, data, offset, 1,
				dpcd && dpcd->data_valid);
		वापस 0;
	पूर्ण

	अगर (op == GVT_AUX_NATIVE_READ) अणु
		पूर्णांक idx, i, ret = 0;

		अगर ((addr + len + 1) >= DPCD_SIZE) अणु
			/*
			 * पढ़ो request exceeds what we supported
			 * DPCD spec: A Sink Device receiving a Native AUX CH
			 * पढ़ो request क्रम an unsupported DPCD address must
			 * reply with an AUX ACK and पढ़ो data set equal to
			 * zero instead of replying with AUX NACK.
			 */

			/* ACK the READ*/
			vgpu_vreg(vgpu, offset + 4) = 0;
			vgpu_vreg(vgpu, offset + 8) = 0;
			vgpu_vreg(vgpu, offset + 12) = 0;
			vgpu_vreg(vgpu, offset + 16) = 0;
			vgpu_vreg(vgpu, offset + 20) = 0;

			dp_aux_ch_ctl_trans_करोne(vgpu, data, offset, len + 2,
					true);
			वापस 0;
		पूर्ण

		क्रम (idx = 1; idx <= 5; idx++) अणु
			/* clear the data रेजिस्टरs */
			vgpu_vreg(vgpu, offset + 4 * idx) = 0;
		पूर्ण

		/*
		 * Read reply क्रमmat: ACK (1 byte) plus (len + 1) bytes of data.
		 */
		अगर ((len + 2) > AUX_BURST_SIZE) अणु
			gvt_vgpu_err("dp_aux_header: len %d is too large\n", len);
			वापस -EINVAL;
		पूर्ण

		/* पढ़ो from भव DPCD to vreg */
		/* first 4 bytes: [ACK][addr][addr+1][addr+2] */
		अगर (dpcd && dpcd->data_valid) अणु
			क्रम (i = 1; i <= (len + 1); i++) अणु
				पूर्णांक t;

				t = dpcd->data[addr + i - 1];
				t <<= (24 - 8 * (i % 4));
				ret |= t;

				अगर ((i % 4 == 3) || (i == (len + 1))) अणु
					vgpu_vreg(vgpu, offset +
							(i / 4 + 1) * 4) = ret;
					ret = 0;
				पूर्ण
			पूर्ण
		पूर्ण
		dp_aux_ch_ctl_trans_करोne(vgpu, data, offset, len + 2,
				dpcd && dpcd->data_valid);
		वापस 0;
	पूर्ण

	/* i2c transaction starts */
	पूर्णांकel_gvt_i2c_handle_aux_ch_ग_लिखो(vgpu, port_index, offset, p_data);

	अगर (data & DP_AUX_CH_CTL_INTERRUPT)
		trigger_aux_channel_पूर्णांकerrupt(vgpu, offset);
	वापस 0;
पूर्ण

अटल पूर्णांक mbctl_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	*(u32 *)p_data &= (~GEN6_MBCTL_ENABLE_BOOT_FETCH);
	ग_लिखो_vreg(vgpu, offset, p_data, bytes);
	वापस 0;
पूर्ण

अटल पूर्णांक vga_control_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	bool vga_disable;

	ग_लिखो_vreg(vgpu, offset, p_data, bytes);
	vga_disable = vgpu_vreg(vgpu, offset) & VGA_DISP_DISABLE;

	gvt_dbg_core("vgpu%d: %s VGA mode\n", vgpu->id,
			vga_disable ? "Disable" : "Enable");
	वापस 0;
पूर्ण

अटल u32 पढ़ो_भव_sbi_रेजिस्टर(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक sbi_offset)
अणु
	काष्ठा पूर्णांकel_vgpu_display *display = &vgpu->display;
	पूर्णांक num = display->sbi.number;
	पूर्णांक i;

	क्रम (i = 0; i < num; ++i)
		अगर (display->sbi.रेजिस्टरs[i].offset == sbi_offset)
			अवरोध;

	अगर (i == num)
		वापस 0;

	वापस display->sbi.रेजिस्टरs[i].value;
पूर्ण

अटल व्योम ग_लिखो_भव_sbi_रेजिस्टर(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, u32 value)
अणु
	काष्ठा पूर्णांकel_vgpu_display *display = &vgpu->display;
	पूर्णांक num = display->sbi.number;
	पूर्णांक i;

	क्रम (i = 0; i < num; ++i) अणु
		अगर (display->sbi.रेजिस्टरs[i].offset == offset)
			अवरोध;
	पूर्ण

	अगर (i == num) अणु
		अगर (num == SBI_REG_MAX) अणु
			gvt_vgpu_err("SBI caching meets maximum limits\n");
			वापस;
		पूर्ण
		display->sbi.number++;
	पूर्ण

	display->sbi.रेजिस्टरs[i].offset = offset;
	display->sbi.रेजिस्टरs[i].value = value;
पूर्ण

अटल पूर्णांक sbi_data_mmio_पढ़ो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	अगर (((vgpu_vreg_t(vgpu, SBI_CTL_STAT) & SBI_OPCODE_MASK) >>
				SBI_OPCODE_SHIFT) == SBI_CMD_CRRD) अणु
		अचिन्हित पूर्णांक sbi_offset = (vgpu_vreg_t(vgpu, SBI_ADDR) &
				SBI_ADDR_OFFSET_MASK) >> SBI_ADDR_OFFSET_SHIFT;
		vgpu_vreg(vgpu, offset) = पढ़ो_भव_sbi_रेजिस्टर(vgpu,
				sbi_offset);
	पूर्ण
	पढ़ो_vreg(vgpu, offset, p_data, bytes);
	वापस 0;
पूर्ण

अटल पूर्णांक sbi_ctl_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 data;

	ग_लिखो_vreg(vgpu, offset, p_data, bytes);
	data = vgpu_vreg(vgpu, offset);

	data &= ~(SBI_STAT_MASK << SBI_STAT_SHIFT);
	data |= SBI_READY;

	data &= ~(SBI_RESPONSE_MASK << SBI_RESPONSE_SHIFT);
	data |= SBI_RESPONSE_SUCCESS;

	vgpu_vreg(vgpu, offset) = data;

	अगर (((vgpu_vreg_t(vgpu, SBI_CTL_STAT) & SBI_OPCODE_MASK) >>
				SBI_OPCODE_SHIFT) == SBI_CMD_CRWR) अणु
		अचिन्हित पूर्णांक sbi_offset = (vgpu_vreg_t(vgpu, SBI_ADDR) &
				SBI_ADDR_OFFSET_MASK) >> SBI_ADDR_OFFSET_SHIFT;

		ग_लिखो_भव_sbi_रेजिस्टर(vgpu, sbi_offset,
					   vgpu_vreg_t(vgpu, SBI_DATA));
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा _vgtअगर_reg(x) \
	(VGT_PVINFO_PAGE + दुरत्व(काष्ठा vgt_अगर, x))

अटल पूर्णांक pvinfo_mmio_पढ़ो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	bool invalid_पढ़ो = false;

	पढ़ो_vreg(vgpu, offset, p_data, bytes);

	चयन (offset) अणु
	हाल _vgtअगर_reg(magic) ... _vgtअगर_reg(vgt_id):
		अगर (offset + bytes > _vgtअगर_reg(vgt_id) + 4)
			invalid_पढ़ो = true;
		अवरोध;
	हाल _vgtअगर_reg(avail_rs.mappable_gmadr.base) ...
		_vgtअगर_reg(avail_rs.fence_num):
		अगर (offset + bytes >
			_vgtअगर_reg(avail_rs.fence_num) + 4)
			invalid_पढ़ो = true;
		अवरोध;
	हाल 0x78010:	/* vgt_caps */
	हाल 0x7881c:
		अवरोध;
	शेष:
		invalid_पढ़ो = true;
		अवरोध;
	पूर्ण
	अगर (invalid_पढ़ो)
		gvt_vgpu_err("invalid pvinfo read: [%x:%x] = %x\n",
				offset, bytes, *(u32 *)p_data);
	vgpu->pv_notअगरied = true;
	वापस 0;
पूर्ण

अटल पूर्णांक handle_g2v_notअगरication(काष्ठा पूर्णांकel_vgpu *vgpu, पूर्णांक notअगरication)
अणु
	क्रमागत पूर्णांकel_gvt_gtt_type root_entry_type = GTT_TYPE_PPGTT_ROOT_L4_ENTRY;
	काष्ठा पूर्णांकel_vgpu_mm *mm;
	u64 *pdps;

	pdps = (u64 *)&vgpu_vreg64_t(vgpu, vgtअगर_reg(pdp[0]));

	चयन (notअगरication) अणु
	हाल VGT_G2V_PPGTT_L3_PAGE_TABLE_CREATE:
		root_entry_type = GTT_TYPE_PPGTT_ROOT_L3_ENTRY;
		fallthrough;
	हाल VGT_G2V_PPGTT_L4_PAGE_TABLE_CREATE:
		mm = पूर्णांकel_vgpu_get_ppgtt_mm(vgpu, root_entry_type, pdps);
		वापस PTR_ERR_OR_ZERO(mm);
	हाल VGT_G2V_PPGTT_L3_PAGE_TABLE_DESTROY:
	हाल VGT_G2V_PPGTT_L4_PAGE_TABLE_DESTROY:
		वापस पूर्णांकel_vgpu_put_ppgtt_mm(vgpu, pdps);
	हाल VGT_G2V_EXECLIST_CONTEXT_CREATE:
	हाल VGT_G2V_EXECLIST_CONTEXT_DESTROY:
	हाल 1:	/* Remove this in guest driver. */
		अवरोध;
	शेष:
		gvt_vgpu_err("Invalid PV notification %d\n", notअगरication);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक send_display_पढ़ोy_uevent(काष्ठा पूर्णांकel_vgpu *vgpu, पूर्णांक पढ़ोy)
अणु
	काष्ठा kobject *kobj = &vgpu->gvt->gt->i915->drm.primary->kdev->kobj;
	अक्षर *env[3] = अणुशून्य, शून्य, शून्यपूर्ण;
	अक्षर vmid_str[20];
	अक्षर display_पढ़ोy_str[20];

	snम_लिखो(display_पढ़ोy_str, 20, "GVT_DISPLAY_READY=%d", पढ़ोy);
	env[0] = display_पढ़ोy_str;

	snम_लिखो(vmid_str, 20, "VMID=%d", vgpu->id);
	env[1] = vmid_str;

	वापस kobject_uevent_env(kobj, KOBJ_ADD, env);
पूर्ण

अटल पूर्णांक pvinfo_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 data = *(u32 *)p_data;
	bool invalid_ग_लिखो = false;

	चयन (offset) अणु
	हाल _vgtअगर_reg(display_पढ़ोy):
		send_display_पढ़ोy_uevent(vgpu, data ? 1 : 0);
		अवरोध;
	हाल _vgtअगर_reg(g2v_notअगरy):
		handle_g2v_notअगरication(vgpu, data);
		अवरोध;
	/* add xhot and yhot to handled list to aव्योम error log */
	हाल _vgtअगर_reg(cursor_x_hot):
	हाल _vgtअगर_reg(cursor_y_hot):
	हाल _vgtअगर_reg(pdp[0].lo):
	हाल _vgtअगर_reg(pdp[0].hi):
	हाल _vgtअगर_reg(pdp[1].lo):
	हाल _vgtअगर_reg(pdp[1].hi):
	हाल _vgtअगर_reg(pdp[2].lo):
	हाल _vgtअगर_reg(pdp[2].hi):
	हाल _vgtअगर_reg(pdp[3].lo):
	हाल _vgtअगर_reg(pdp[3].hi):
	हाल _vgtअगर_reg(execlist_context_descriptor_lo):
	हाल _vgtअगर_reg(execlist_context_descriptor_hi):
		अवरोध;
	हाल _vgtअगर_reg(rsv5[0])..._vgtअगर_reg(rsv5[3]):
		invalid_ग_लिखो = true;
		enter_failsafe_mode(vgpu, GVT_FAILSAFE_INSUFFICIENT_RESOURCE);
		अवरोध;
	शेष:
		invalid_ग_लिखो = true;
		gvt_vgpu_err("invalid pvinfo write offset %x bytes %x data %x\n",
				offset, bytes, data);
		अवरोध;
	पूर्ण

	अगर (!invalid_ग_लिखो)
		ग_लिखो_vreg(vgpu, offset, p_data, bytes);

	वापस 0;
पूर्ण

अटल पूर्णांक pf_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;
	u32 val = *(u32 *)p_data;

	अगर ((offset == _PS_1A_CTRL || offset == _PS_2A_CTRL ||
	   offset == _PS_1B_CTRL || offset == _PS_2B_CTRL ||
	   offset == _PS_1C_CTRL) && (val & PS_PLANE_SEL_MASK) != 0) अणु
		drm_WARN_ONCE(&i915->drm, true,
			      "VM(%d): guest is trying to scaling a plane\n",
			      vgpu->id);
		वापस 0;
	पूर्ण

	वापस पूर्णांकel_vgpu_शेष_mmio_ग_लिखो(vgpu, offset, p_data, bytes);
पूर्ण

अटल पूर्णांक घातer_well_ctl_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	ग_लिखो_vreg(vgpu, offset, p_data, bytes);

	अगर (vgpu_vreg(vgpu, offset) &
	    HSW_PWR_WELL_CTL_REQ(HSW_PW_CTL_IDX_GLOBAL))
		vgpu_vreg(vgpu, offset) |=
			HSW_PWR_WELL_CTL_STATE(HSW_PW_CTL_IDX_GLOBAL);
	अन्यथा
		vgpu_vreg(vgpu, offset) &=
			~HSW_PWR_WELL_CTL_STATE(HSW_PW_CTL_IDX_GLOBAL);
	वापस 0;
पूर्ण

अटल पूर्णांक gen9_dbuf_ctl_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	ग_लिखो_vreg(vgpu, offset, p_data, bytes);

	अगर (vgpu_vreg(vgpu, offset) & DBUF_POWER_REQUEST)
		vgpu_vreg(vgpu, offset) |= DBUF_POWER_STATE;
	अन्यथा
		vgpu_vreg(vgpu, offset) &= ~DBUF_POWER_STATE;

	वापस 0;
पूर्ण

अटल पूर्णांक fpga_dbg_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
	अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	ग_लिखो_vreg(vgpu, offset, p_data, bytes);

	अगर (vgpu_vreg(vgpu, offset) & FPGA_DBG_RM_NOCLAIM)
		vgpu_vreg(vgpu, offset) &= ~FPGA_DBG_RM_NOCLAIM;
	वापस 0;
पूर्ण

अटल पूर्णांक dma_ctrl_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;
	u32 mode;

	ग_लिखो_vreg(vgpu, offset, p_data, bytes);
	mode = vgpu_vreg(vgpu, offset);

	अगर (GFX_MODE_BIT_SET_IN_MASK(mode, START_DMA)) अणु
		drm_WARN_ONCE(&i915->drm, 1,
				"VM(%d): iGVT-g doesn't support GuC\n",
				vgpu->id);
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gen9_trtte_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;
	u32 trtte = *(u32 *)p_data;

	अगर ((trtte & 1) && (trtte & (1 << 1)) == 0) अणु
		drm_WARN(&i915->drm, 1,
				"VM(%d): Use physical address for TRTT!\n",
				vgpu->id);
		वापस -EINVAL;
	पूर्ण
	ग_लिखो_vreg(vgpu, offset, p_data, bytes);

	वापस 0;
पूर्ण

अटल पूर्णांक gen9_trtt_chicken_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	ग_लिखो_vreg(vgpu, offset, p_data, bytes);
	वापस 0;
पूर्ण

अटल पूर्णांक dpll_status_पढ़ो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 v = 0;

	अगर (vgpu_vreg(vgpu, 0x46010) & (1 << 31))
		v |= (1 << 0);

	अगर (vgpu_vreg(vgpu, 0x46014) & (1 << 31))
		v |= (1 << 8);

	अगर (vgpu_vreg(vgpu, 0x46040) & (1 << 31))
		v |= (1 << 16);

	अगर (vgpu_vreg(vgpu, 0x46060) & (1 << 31))
		v |= (1 << 24);

	vgpu_vreg(vgpu, offset) = v;

	वापस पूर्णांकel_vgpu_शेष_mmio_पढ़ो(vgpu, offset, p_data, bytes);
पूर्ण

अटल पूर्णांक mailbox_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 value = *(u32 *)p_data;
	u32 cmd = value & 0xff;
	u32 *data0 = &vgpu_vreg_t(vgpu, GEN6_PCODE_DATA);

	चयन (cmd) अणु
	हाल GEN9_PCODE_READ_MEM_LATENCY:
		अगर (IS_SKYLAKE(vgpu->gvt->gt->i915) ||
		    IS_KABYLAKE(vgpu->gvt->gt->i915) ||
		    IS_COFFEELAKE(vgpu->gvt->gt->i915) ||
		    IS_COMETLAKE(vgpu->gvt->gt->i915)) अणु
			/**
			 * "Read memory latency" command on gen9.
			 * Below memory latency values are पढ़ो
			 * from skylake platक्रमm.
			 */
			अगर (!*data0)
				*data0 = 0x1e1a1100;
			अन्यथा
				*data0 = 0x61514b3d;
		पूर्ण अन्यथा अगर (IS_BROXTON(vgpu->gvt->gt->i915)) अणु
			/**
			 * "Read memory latency" command on gen9.
			 * Below memory latency values are पढ़ो
			 * from Broxton MRB.
			 */
			अगर (!*data0)
				*data0 = 0x16080707;
			अन्यथा
				*data0 = 0x16161616;
		पूर्ण
		अवरोध;
	हाल SKL_PCODE_CDCLK_CONTROL:
		अगर (IS_SKYLAKE(vgpu->gvt->gt->i915) ||
		    IS_KABYLAKE(vgpu->gvt->gt->i915) ||
		    IS_COFFEELAKE(vgpu->gvt->gt->i915) ||
		    IS_COMETLAKE(vgpu->gvt->gt->i915))
			*data0 = SKL_CDCLK_READY_FOR_CHANGE;
		अवरोध;
	हाल GEN6_PCODE_READ_RC6VIDS:
		*data0 |= 0x1;
		अवरोध;
	पूर्ण

	gvt_dbg_core("VM(%d) write %x to mailbox, return data0 %x\n",
		     vgpu->id, value, *data0);
	/**
	 * PCODE_READY clear means पढ़ोy क्रम pcode पढ़ो/ग_लिखो,
	 * PCODE_ERROR_MASK clear means no error happened. In GVT-g we
	 * always emulate as pcode पढ़ो/ग_लिखो success and पढ़ोy क्रम access
	 * anyसमय, since we करोn't touch real physical रेजिस्टरs here.
	 */
	value &= ~(GEN6_PCODE_READY | GEN6_PCODE_ERROR_MASK);
	वापस पूर्णांकel_vgpu_शेष_mmio_ग_लिखो(vgpu, offset, &value, bytes);
पूर्ण

अटल पूर्णांक hws_pga_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 value = *(u32 *)p_data;
	स्थिर काष्ठा पूर्णांकel_engine_cs *engine =
		पूर्णांकel_gvt_render_mmio_to_engine(vgpu->gvt, offset);

	अगर (value != 0 &&
	    !पूर्णांकel_gvt_ggtt_validate_range(vgpu, value, I915_GTT_PAGE_SIZE)) अणु
		gvt_vgpu_err("write invalid HWSP address, reg:0x%x, value:0x%x\n",
			      offset, value);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Need to emulate all the HWSP रेजिस्टर ग_लिखो to ensure host can
	 * update the VM CSB status correctly. Here listed रेजिस्टरs can
	 * support BDW, SKL or other platक्रमms with same HWSP रेजिस्टरs.
	 */
	अगर (unlikely(!engine)) अणु
		gvt_vgpu_err("access unknown hardware status page register:0x%x\n",
			     offset);
		वापस -EINVAL;
	पूर्ण
	vgpu->hws_pga[engine->id] = value;
	gvt_dbg_mmio("VM(%d) write: 0x%x to HWSP: 0x%x\n",
		     vgpu->id, value, offset);

	वापस पूर्णांकel_vgpu_शेष_mmio_ग_लिखो(vgpu, offset, &value, bytes);
पूर्ण

अटल पूर्णांक skl_घातer_well_ctl_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 v = *(u32 *)p_data;

	अगर (IS_BROXTON(vgpu->gvt->gt->i915))
		v &= (1 << 31) | (1 << 29);
	अन्यथा
		v &= (1 << 31) | (1 << 29) | (1 << 9) |
			(1 << 7) | (1 << 5) | (1 << 3) | (1 << 1);
	v |= (v >> 1);

	वापस पूर्णांकel_vgpu_शेष_mmio_ग_लिखो(vgpu, offset, &v, bytes);
पूर्ण

अटल पूर्णांक skl_lcpll_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 v = *(u32 *)p_data;

	/* other bits are MBZ. */
	v &= (1 << 31) | (1 << 30);
	v & (1 << 31) ? (v |= (1 << 30)) : (v &= ~(1 << 30));

	vgpu_vreg(vgpu, offset) = v;

	वापस 0;
पूर्ण

अटल पूर्णांक bxt_de_pll_enable_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 v = *(u32 *)p_data;

	अगर (v & BXT_DE_PLL_PLL_ENABLE)
		v |= BXT_DE_PLL_LOCK;

	vgpu_vreg(vgpu, offset) = v;

	वापस 0;
पूर्ण

अटल पूर्णांक bxt_port_pll_enable_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 v = *(u32 *)p_data;

	अगर (v & PORT_PLL_ENABLE)
		v |= PORT_PLL_LOCK;

	vgpu_vreg(vgpu, offset) = v;

	वापस 0;
पूर्ण

अटल पूर्णांक bxt_phy_ctl_family_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 v = *(u32 *)p_data;
	u32 data = v & COMMON_RESET_DIS ? BXT_PHY_LANE_ENABLED : 0;

	चयन (offset) अणु
	हाल _PHY_CTL_FAMILY_EDP:
		vgpu_vreg(vgpu, _BXT_PHY_CTL_DDI_A) = data;
		अवरोध;
	हाल _PHY_CTL_FAMILY_DDI:
		vgpu_vreg(vgpu, _BXT_PHY_CTL_DDI_B) = data;
		vgpu_vreg(vgpu, _BXT_PHY_CTL_DDI_C) = data;
		अवरोध;
	पूर्ण

	vgpu_vreg(vgpu, offset) = v;

	वापस 0;
पूर्ण

अटल पूर्णांक bxt_port_tx_dw3_पढ़ो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 v = vgpu_vreg(vgpu, offset);

	v &= ~UNIQUE_TRANGE_EN_METHOD;

	vgpu_vreg(vgpu, offset) = v;

	वापस पूर्णांकel_vgpu_शेष_mmio_पढ़ो(vgpu, offset, p_data, bytes);
पूर्ण

अटल पूर्णांक bxt_pcs_dw12_grp_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 v = *(u32 *)p_data;

	अगर (offset == _PORT_PCS_DW12_GRP_A || offset == _PORT_PCS_DW12_GRP_B) अणु
		vgpu_vreg(vgpu, offset - 0x600) = v;
		vgpu_vreg(vgpu, offset - 0x800) = v;
	पूर्ण अन्यथा अणु
		vgpu_vreg(vgpu, offset - 0x400) = v;
		vgpu_vreg(vgpu, offset - 0x600) = v;
	पूर्ण

	vgpu_vreg(vgpu, offset) = v;

	वापस 0;
पूर्ण

अटल पूर्णांक bxt_gt_disp_pwron_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 v = *(u32 *)p_data;

	अगर (v & BIT(0)) अणु
		vgpu_vreg_t(vgpu, BXT_PORT_CL1CM_DW0(DPIO_PHY0)) &=
			~PHY_RESERVED;
		vgpu_vreg_t(vgpu, BXT_PORT_CL1CM_DW0(DPIO_PHY0)) |=
			PHY_POWER_GOOD;
	पूर्ण

	अगर (v & BIT(1)) अणु
		vgpu_vreg_t(vgpu, BXT_PORT_CL1CM_DW0(DPIO_PHY1)) &=
			~PHY_RESERVED;
		vgpu_vreg_t(vgpu, BXT_PORT_CL1CM_DW0(DPIO_PHY1)) |=
			PHY_POWER_GOOD;
	पूर्ण


	vgpu_vreg(vgpu, offset) = v;

	वापस 0;
पूर्ण

अटल पूर्णांक edp_psr_imr_iir_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	vgpu_vreg(vgpu, offset) = 0;
	वापस 0;
पूर्ण

/*
 * FixMe:
 * If guest fills non-priv batch buffer on ApolloLake/Broxton as Mesa i965 did:
 * 717e7539124d (i965: Use a WC map and स_नकल क्रम the batch instead of pग_लिखो.)
 * Due to the missing flush of bb filled by VM vCPU, host GPU hangs on executing
 * these MI_BATCH_BUFFER.
 * Temporarily workaround this by setting SNOOP bit क्रम PAT3 used by PPGTT
 * PML4 PTE: PAT(0) PCD(1) PWT(1).
 * The perक्रमmance is still expected to be low, will need further improvement.
 */
अटल पूर्णांक bxt_ppat_low_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
			      व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u64 pat =
		GEN8_PPAT(0, CHV_PPAT_SNOOP) |
		GEN8_PPAT(1, 0) |
		GEN8_PPAT(2, 0) |
		GEN8_PPAT(3, CHV_PPAT_SNOOP) |
		GEN8_PPAT(4, CHV_PPAT_SNOOP) |
		GEN8_PPAT(5, CHV_PPAT_SNOOP) |
		GEN8_PPAT(6, CHV_PPAT_SNOOP) |
		GEN8_PPAT(7, CHV_PPAT_SNOOP);

	vgpu_vreg(vgpu, offset) = lower_32_bits(pat);

	वापस 0;
पूर्ण

अटल पूर्णांक guc_status_पढ़ो(काष्ठा पूर्णांकel_vgpu *vgpu,
			   अचिन्हित पूर्णांक offset, व्योम *p_data,
			   अचिन्हित पूर्णांक bytes)
अणु
	/* keep MIA_IN_RESET beक्रमe clearing */
	पढ़ो_vreg(vgpu, offset, p_data, bytes);
	vgpu_vreg(vgpu, offset) &= ~GS_MIA_IN_RESET;
	वापस 0;
पूर्ण

अटल पूर्णांक mmio_पढ़ो_from_hw(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	स्थिर काष्ठा पूर्णांकel_engine_cs *engine =
		पूर्णांकel_gvt_render_mmio_to_engine(gvt, offset);

	/**
	 * Read HW reg in following हाल
	 * a. the offset isn't a ring mmio
	 * b. the offset's ring is running on hw.
	 * c. the offset is ring समय stamp mmio
	 */

	अगर (!engine ||
	    vgpu == gvt->scheduler.engine_owner[engine->id] ||
	    offset == i915_mmio_reg_offset(RING_TIMESTAMP(engine->mmio_base)) ||
	    offset == i915_mmio_reg_offset(RING_TIMESTAMP_UDW(engine->mmio_base))) अणु
		mmio_hw_access_pre(gvt->gt);
		vgpu_vreg(vgpu, offset) =
			पूर्णांकel_uncore_पढ़ो(gvt->gt->uncore, _MMIO(offset));
		mmio_hw_access_post(gvt->gt);
	पूर्ण

	वापस पूर्णांकel_vgpu_शेष_mmio_पढ़ो(vgpu, offset, p_data, bytes);
पूर्ण

अटल पूर्णांक elsp_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;
	स्थिर काष्ठा पूर्णांकel_engine_cs *engine = पूर्णांकel_gvt_render_mmio_to_engine(vgpu->gvt, offset);
	काष्ठा पूर्णांकel_vgpu_execlist *execlist;
	u32 data = *(u32 *)p_data;
	पूर्णांक ret = 0;

	अगर (drm_WARN_ON(&i915->drm, !engine))
		वापस -EINVAL;

	execlist = &vgpu->submission.execlist[engine->id];

	execlist->elsp_dwords.data[3 - execlist->elsp_dwords.index] = data;
	अगर (execlist->elsp_dwords.index == 3) अणु
		ret = पूर्णांकel_vgpu_submit_execlist(vgpu, engine);
		अगर(ret)
			gvt_vgpu_err("fail submit workload on ring %s\n",
				     engine->name);
	पूर्ण

	++execlist->elsp_dwords.index;
	execlist->elsp_dwords.index &= 0x3;
	वापस ret;
पूर्ण

अटल पूर्णांक ring_mode_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 data = *(u32 *)p_data;
	स्थिर काष्ठा पूर्णांकel_engine_cs *engine =
		पूर्णांकel_gvt_render_mmio_to_engine(vgpu->gvt, offset);
	bool enable_execlist;
	पूर्णांक ret;

	(*(u32 *)p_data) &= ~_MASKED_BIT_ENABLE(1);
	अगर (IS_COFFEELAKE(vgpu->gvt->gt->i915) ||
	    IS_COMETLAKE(vgpu->gvt->gt->i915))
		(*(u32 *)p_data) &= ~_MASKED_BIT_ENABLE(2);
	ग_लिखो_vreg(vgpu, offset, p_data, bytes);

	अगर (IS_MASKED_BITS_ENABLED(data, 1)) अणु
		enter_failsafe_mode(vgpu, GVT_FAILSAFE_UNSUPPORTED_GUEST);
		वापस 0;
	पूर्ण

	अगर ((IS_COFFEELAKE(vgpu->gvt->gt->i915) ||
	     IS_COMETLAKE(vgpu->gvt->gt->i915)) &&
	    IS_MASKED_BITS_ENABLED(data, 2)) अणु
		enter_failsafe_mode(vgpu, GVT_FAILSAFE_UNSUPPORTED_GUEST);
		वापस 0;
	पूर्ण

	/* when PPGTT mode enabled, we will check अगर guest has called
	 * pvinfo, अगर not, we will treat this guest as non-gvtg-aware
	 * guest, and stop emulating its cfg space, mmio, gtt, etc.
	 */
	अगर ((IS_MASKED_BITS_ENABLED(data, GFX_PPGTT_ENABLE) ||
	    IS_MASKED_BITS_ENABLED(data, GFX_RUN_LIST_ENABLE)) &&
	    !vgpu->pv_notअगरied) अणु
		enter_failsafe_mode(vgpu, GVT_FAILSAFE_UNSUPPORTED_GUEST);
		वापस 0;
	पूर्ण
	अगर (IS_MASKED_BITS_ENABLED(data, GFX_RUN_LIST_ENABLE) ||
	    IS_MASKED_BITS_DISABLED(data, GFX_RUN_LIST_ENABLE)) अणु
		enable_execlist = !!(data & GFX_RUN_LIST_ENABLE);

		gvt_dbg_core("EXECLIST %s on ring %s\n",
			     (enable_execlist ? "enabling" : "disabling"),
			     engine->name);

		अगर (!enable_execlist)
			वापस 0;

		ret = पूर्णांकel_vgpu_select_submission_ops(vgpu,
						       engine->mask,
						       INTEL_VGPU_EXECLIST_SUBMISSION);
		अगर (ret)
			वापस ret;

		पूर्णांकel_vgpu_start_schedule(vgpu);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gvt_reg_tlb_control_handler(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	अचिन्हित पूर्णांक id = 0;

	ग_लिखो_vreg(vgpu, offset, p_data, bytes);
	vgpu_vreg(vgpu, offset) = 0;

	चयन (offset) अणु
	हाल 0x4260:
		id = RCS0;
		अवरोध;
	हाल 0x4264:
		id = VCS0;
		अवरोध;
	हाल 0x4268:
		id = VCS1;
		अवरोध;
	हाल 0x426c:
		id = BCS0;
		अवरोध;
	हाल 0x4270:
		id = VECS0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	set_bit(id, (व्योम *)vgpu->submission.tlb_handle_pending);

	वापस 0;
पूर्ण

अटल पूर्णांक ring_reset_ctl_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
	अचिन्हित पूर्णांक offset, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 data;

	ग_लिखो_vreg(vgpu, offset, p_data, bytes);
	data = vgpu_vreg(vgpu, offset);

	अगर (IS_MASKED_BITS_ENABLED(data, RESET_CTL_REQUEST_RESET))
		data |= RESET_CTL_READY_TO_RESET;
	अन्यथा अगर (data & _MASKED_BIT_DISABLE(RESET_CTL_REQUEST_RESET))
		data &= ~RESET_CTL_READY_TO_RESET;

	vgpu_vreg(vgpu, offset) = data;
	वापस 0;
पूर्ण

अटल पूर्णांक csfe_chicken1_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu,
				    अचिन्हित पूर्णांक offset, व्योम *p_data,
				    अचिन्हित पूर्णांक bytes)
अणु
	u32 data = *(u32 *)p_data;

	(*(u32 *)p_data) &= ~_MASKED_BIT_ENABLE(0x18);
	ग_लिखो_vreg(vgpu, offset, p_data, bytes);

	अगर (IS_MASKED_BITS_ENABLED(data, 0x10) ||
	    IS_MASKED_BITS_ENABLED(data, 0x8))
		enter_failsafe_mode(vgpu, GVT_FAILSAFE_UNSUPPORTED_GUEST);

	वापस 0;
पूर्ण

#घोषणा MMIO_F(reg, s, f, am, rm, d, r, w) करो अणु \
	ret = new_mmio_info(gvt, i915_mmio_reg_offset(reg), \
		f, s, am, rm, d, r, w); \
	अगर (ret) \
		वापस ret; \
पूर्ण जबतक (0)

#घोषणा MMIO_D(reg, d) \
	MMIO_F(reg, 4, 0, 0, 0, d, शून्य, शून्य)

#घोषणा MMIO_DH(reg, d, r, w) \
	MMIO_F(reg, 4, 0, 0, 0, d, r, w)

#घोषणा MMIO_DFH(reg, d, f, r, w) \
	MMIO_F(reg, 4, f, 0, 0, d, r, w)

#घोषणा MMIO_GM(reg, d, r, w) \
	MMIO_F(reg, 4, F_GMADR, 0xFFFFF000, 0, d, r, w)

#घोषणा MMIO_GM_RDR(reg, d, r, w) \
	MMIO_F(reg, 4, F_GMADR | F_CMD_ACCESS, 0xFFFFF000, 0, d, r, w)

#घोषणा MMIO_RO(reg, d, f, rm, r, w) \
	MMIO_F(reg, 4, F_RO | f, 0, rm, d, r, w)

#घोषणा MMIO_RING_F(prefix, s, f, am, rm, d, r, w) करो अणु \
	MMIO_F(prefix(RENDER_RING_BASE), s, f, am, rm, d, r, w); \
	MMIO_F(prefix(BLT_RING_BASE), s, f, am, rm, d, r, w); \
	MMIO_F(prefix(GEN6_BSD_RING_BASE), s, f, am, rm, d, r, w); \
	MMIO_F(prefix(VEBOX_RING_BASE), s, f, am, rm, d, r, w); \
	अगर (HAS_ENGINE(gvt->gt, VCS1)) \
		MMIO_F(prefix(GEN8_BSD2_RING_BASE), s, f, am, rm, d, r, w); \
पूर्ण जबतक (0)

#घोषणा MMIO_RING_D(prefix, d) \
	MMIO_RING_F(prefix, 4, 0, 0, 0, d, शून्य, शून्य)

#घोषणा MMIO_RING_DFH(prefix, d, f, r, w) \
	MMIO_RING_F(prefix, 4, f, 0, 0, d, r, w)

#घोषणा MMIO_RING_GM(prefix, d, r, w) \
	MMIO_RING_F(prefix, 4, F_GMADR, 0xFFFF0000, 0, d, r, w)

#घोषणा MMIO_RING_GM_RDR(prefix, d, r, w) \
	MMIO_RING_F(prefix, 4, F_GMADR | F_CMD_ACCESS, 0xFFFF0000, 0, d, r, w)

#घोषणा MMIO_RING_RO(prefix, d, f, rm, r, w) \
	MMIO_RING_F(prefix, 4, F_RO | f, 0, rm, d, r, w)

अटल पूर्णांक init_generic_mmio_info(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा drm_i915_निजी *dev_priv = gvt->gt->i915;
	पूर्णांक ret;

	MMIO_RING_DFH(RING_IMR, D_ALL, 0, शून्य,
		पूर्णांकel_vgpu_reg_imr_handler);

	MMIO_DFH(SDEIMR, D_ALL, 0, शून्य, पूर्णांकel_vgpu_reg_imr_handler);
	MMIO_DFH(SDEIER, D_ALL, 0, शून्य, पूर्णांकel_vgpu_reg_ier_handler);
	MMIO_DFH(SDEIIR, D_ALL, 0, शून्य, पूर्णांकel_vgpu_reg_iir_handler);
	MMIO_D(SDEISR, D_ALL);

	MMIO_RING_DFH(RING_HWSTAM, D_ALL, 0, शून्य, शून्य);


	MMIO_DH(GEN8_GAMW_ECO_DEV_RW_IA, D_BDW_PLUS, शून्य,
		gamw_echo_dev_rw_ia_ग_लिखो);

	MMIO_GM_RDR(BSD_HWS_PGA_GEN7, D_ALL, शून्य, शून्य);
	MMIO_GM_RDR(BLT_HWS_PGA_GEN7, D_ALL, शून्य, शून्य);
	MMIO_GM_RDR(VEBOX_HWS_PGA_GEN7, D_ALL, शून्य, शून्य);

#घोषणा RING_REG(base) _MMIO((base) + 0x28)
	MMIO_RING_DFH(RING_REG, D_ALL, F_CMD_ACCESS, शून्य, शून्य);
#अघोषित RING_REG

#घोषणा RING_REG(base) _MMIO((base) + 0x134)
	MMIO_RING_DFH(RING_REG, D_ALL, F_CMD_ACCESS, शून्य, शून्य);
#अघोषित RING_REG

#घोषणा RING_REG(base) _MMIO((base) + 0x6c)
	MMIO_RING_DFH(RING_REG, D_ALL, 0, mmio_पढ़ो_from_hw, शून्य);
#अघोषित RING_REG
	MMIO_DH(GEN7_SC_INSTDONE, D_BDW_PLUS, mmio_पढ़ो_from_hw, शून्य);

	MMIO_GM_RDR(_MMIO(0x2148), D_ALL, शून्य, शून्य);
	MMIO_GM_RDR(CCID(RENDER_RING_BASE), D_ALL, शून्य, शून्य);
	MMIO_GM_RDR(_MMIO(0x12198), D_ALL, शून्य, शून्य);
	MMIO_D(GEN7_CXT_SIZE, D_ALL);

	MMIO_RING_DFH(RING_TAIL, D_ALL, 0, शून्य, शून्य);
	MMIO_RING_DFH(RING_HEAD, D_ALL, 0, शून्य, शून्य);
	MMIO_RING_DFH(RING_CTL, D_ALL, 0, शून्य, शून्य);
	MMIO_RING_DFH(RING_ACTHD, D_ALL, 0, mmio_पढ़ो_from_hw, शून्य);
	MMIO_RING_GM(RING_START, D_ALL, शून्य, शून्य);

	/* RING MODE */
#घोषणा RING_REG(base) _MMIO((base) + 0x29c)
	MMIO_RING_DFH(RING_REG, D_ALL,
		F_MODE_MASK | F_CMD_ACCESS | F_CMD_WRITE_PATCH, शून्य,
		ring_mode_mmio_ग_लिखो);
#अघोषित RING_REG

	MMIO_RING_DFH(RING_MI_MODE, D_ALL, F_MODE_MASK | F_CMD_ACCESS,
		शून्य, शून्य);
	MMIO_RING_DFH(RING_INSTPM, D_ALL, F_MODE_MASK | F_CMD_ACCESS,
			शून्य, शून्य);
	MMIO_RING_DFH(RING_TIMESTAMP, D_ALL, F_CMD_ACCESS,
			mmio_पढ़ो_from_hw, शून्य);
	MMIO_RING_DFH(RING_TIMESTAMP_UDW, D_ALL, F_CMD_ACCESS,
			mmio_पढ़ो_from_hw, शून्य);

	MMIO_DFH(GEN7_GT_MODE, D_ALL, F_MODE_MASK | F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(CACHE_MODE_0_GEN7, D_ALL, F_MODE_MASK | F_CMD_ACCESS,
		शून्य, शून्य);
	MMIO_DFH(CACHE_MODE_1, D_ALL, F_MODE_MASK | F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(CACHE_MODE_0, D_ALL, F_MODE_MASK | F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x2124), D_ALL, F_MODE_MASK | F_CMD_ACCESS, शून्य, शून्य);

	MMIO_DFH(_MMIO(0x20dc), D_ALL, F_MODE_MASK | F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_3D_CHICKEN3, D_ALL, F_MODE_MASK | F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x2088), D_ALL, F_MODE_MASK | F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(FF_SLICE_CS_CHICKEN2, D_ALL,
		 F_MODE_MASK | F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x2470), D_ALL, F_MODE_MASK | F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(GAM_ECOCHK, D_ALL, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(GEN7_COMMON_SLICE_CHICKEN1, D_ALL, F_MODE_MASK | F_CMD_ACCESS,
		शून्य, शून्य);
	MMIO_DFH(COMMON_SLICE_CHICKEN2, D_ALL, F_MODE_MASK | F_CMD_ACCESS,
		 शून्य, शून्य);
	MMIO_DFH(_MMIO(0x9030), D_ALL, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x20a0), D_ALL, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x2420), D_ALL, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x2430), D_ALL, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x2434), D_ALL, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x2438), D_ALL, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x243c), D_ALL, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x7018), D_ALL, F_MODE_MASK | F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(HALF_SLICE_CHICKEN3, D_ALL, F_MODE_MASK | F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(GEN7_HALF_SLICE_CHICKEN1, D_ALL, F_MODE_MASK | F_CMD_ACCESS, शून्य, शून्य);

	/* display */
	MMIO_F(_MMIO(0x60220), 0x20, 0, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_D(_MMIO(0x602a0), D_ALL);

	MMIO_D(_MMIO(0x65050), D_ALL);
	MMIO_D(_MMIO(0x650b4), D_ALL);

	MMIO_D(_MMIO(0xc4040), D_ALL);
	MMIO_D(DERRMR, D_ALL);

	MMIO_D(PIPEDSL(PIPE_A), D_ALL);
	MMIO_D(PIPEDSL(PIPE_B), D_ALL);
	MMIO_D(PIPEDSL(PIPE_C), D_ALL);
	MMIO_D(PIPEDSL(_PIPE_EDP), D_ALL);

	MMIO_DH(PIPECONF(PIPE_A), D_ALL, शून्य, pipeconf_mmio_ग_लिखो);
	MMIO_DH(PIPECONF(PIPE_B), D_ALL, शून्य, pipeconf_mmio_ग_लिखो);
	MMIO_DH(PIPECONF(PIPE_C), D_ALL, शून्य, pipeconf_mmio_ग_लिखो);
	MMIO_DH(PIPECONF(_PIPE_EDP), D_ALL, शून्य, pipeconf_mmio_ग_लिखो);

	MMIO_D(PIPESTAT(PIPE_A), D_ALL);
	MMIO_D(PIPESTAT(PIPE_B), D_ALL);
	MMIO_D(PIPESTAT(PIPE_C), D_ALL);
	MMIO_D(PIPESTAT(_PIPE_EDP), D_ALL);

	MMIO_D(PIPE_FLIPCOUNT_G4X(PIPE_A), D_ALL);
	MMIO_D(PIPE_FLIPCOUNT_G4X(PIPE_B), D_ALL);
	MMIO_D(PIPE_FLIPCOUNT_G4X(PIPE_C), D_ALL);
	MMIO_D(PIPE_FLIPCOUNT_G4X(_PIPE_EDP), D_ALL);

	MMIO_D(PIPE_FRMCOUNT_G4X(PIPE_A), D_ALL);
	MMIO_D(PIPE_FRMCOUNT_G4X(PIPE_B), D_ALL);
	MMIO_D(PIPE_FRMCOUNT_G4X(PIPE_C), D_ALL);
	MMIO_D(PIPE_FRMCOUNT_G4X(_PIPE_EDP), D_ALL);

	MMIO_D(CURCNTR(PIPE_A), D_ALL);
	MMIO_D(CURCNTR(PIPE_B), D_ALL);
	MMIO_D(CURCNTR(PIPE_C), D_ALL);

	MMIO_D(CURPOS(PIPE_A), D_ALL);
	MMIO_D(CURPOS(PIPE_B), D_ALL);
	MMIO_D(CURPOS(PIPE_C), D_ALL);

	MMIO_D(CURBASE(PIPE_A), D_ALL);
	MMIO_D(CURBASE(PIPE_B), D_ALL);
	MMIO_D(CURBASE(PIPE_C), D_ALL);

	MMIO_D(CUR_FBC_CTL(PIPE_A), D_ALL);
	MMIO_D(CUR_FBC_CTL(PIPE_B), D_ALL);
	MMIO_D(CUR_FBC_CTL(PIPE_C), D_ALL);

	MMIO_D(_MMIO(0x700ac), D_ALL);
	MMIO_D(_MMIO(0x710ac), D_ALL);
	MMIO_D(_MMIO(0x720ac), D_ALL);

	MMIO_D(_MMIO(0x70090), D_ALL);
	MMIO_D(_MMIO(0x70094), D_ALL);
	MMIO_D(_MMIO(0x70098), D_ALL);
	MMIO_D(_MMIO(0x7009c), D_ALL);

	MMIO_D(DSPCNTR(PIPE_A), D_ALL);
	MMIO_D(DSPADDR(PIPE_A), D_ALL);
	MMIO_D(DSPSTRIDE(PIPE_A), D_ALL);
	MMIO_D(DSPPOS(PIPE_A), D_ALL);
	MMIO_D(DSPSIZE(PIPE_A), D_ALL);
	MMIO_DH(DSPSURF(PIPE_A), D_ALL, शून्य, pri_surf_mmio_ग_लिखो);
	MMIO_D(DSPOFFSET(PIPE_A), D_ALL);
	MMIO_D(DSPSURFLIVE(PIPE_A), D_ALL);
	MMIO_DH(REG_50080(PIPE_A, PLANE_PRIMARY), D_ALL, शून्य,
		reg50080_mmio_ग_लिखो);

	MMIO_D(DSPCNTR(PIPE_B), D_ALL);
	MMIO_D(DSPADDR(PIPE_B), D_ALL);
	MMIO_D(DSPSTRIDE(PIPE_B), D_ALL);
	MMIO_D(DSPPOS(PIPE_B), D_ALL);
	MMIO_D(DSPSIZE(PIPE_B), D_ALL);
	MMIO_DH(DSPSURF(PIPE_B), D_ALL, शून्य, pri_surf_mmio_ग_लिखो);
	MMIO_D(DSPOFFSET(PIPE_B), D_ALL);
	MMIO_D(DSPSURFLIVE(PIPE_B), D_ALL);
	MMIO_DH(REG_50080(PIPE_B, PLANE_PRIMARY), D_ALL, शून्य,
		reg50080_mmio_ग_लिखो);

	MMIO_D(DSPCNTR(PIPE_C), D_ALL);
	MMIO_D(DSPADDR(PIPE_C), D_ALL);
	MMIO_D(DSPSTRIDE(PIPE_C), D_ALL);
	MMIO_D(DSPPOS(PIPE_C), D_ALL);
	MMIO_D(DSPSIZE(PIPE_C), D_ALL);
	MMIO_DH(DSPSURF(PIPE_C), D_ALL, शून्य, pri_surf_mmio_ग_लिखो);
	MMIO_D(DSPOFFSET(PIPE_C), D_ALL);
	MMIO_D(DSPSURFLIVE(PIPE_C), D_ALL);
	MMIO_DH(REG_50080(PIPE_C, PLANE_PRIMARY), D_ALL, शून्य,
		reg50080_mmio_ग_लिखो);

	MMIO_D(SPRCTL(PIPE_A), D_ALL);
	MMIO_D(SPRLINOFF(PIPE_A), D_ALL);
	MMIO_D(SPRSTRIDE(PIPE_A), D_ALL);
	MMIO_D(SPRPOS(PIPE_A), D_ALL);
	MMIO_D(SPRSIZE(PIPE_A), D_ALL);
	MMIO_D(SPRKEYVAL(PIPE_A), D_ALL);
	MMIO_D(SPRKEYMSK(PIPE_A), D_ALL);
	MMIO_DH(SPRSURF(PIPE_A), D_ALL, शून्य, spr_surf_mmio_ग_लिखो);
	MMIO_D(SPRKEYMAX(PIPE_A), D_ALL);
	MMIO_D(SPROFFSET(PIPE_A), D_ALL);
	MMIO_D(SPRSCALE(PIPE_A), D_ALL);
	MMIO_D(SPRSURFLIVE(PIPE_A), D_ALL);
	MMIO_DH(REG_50080(PIPE_A, PLANE_SPRITE0), D_ALL, शून्य,
		reg50080_mmio_ग_लिखो);

	MMIO_D(SPRCTL(PIPE_B), D_ALL);
	MMIO_D(SPRLINOFF(PIPE_B), D_ALL);
	MMIO_D(SPRSTRIDE(PIPE_B), D_ALL);
	MMIO_D(SPRPOS(PIPE_B), D_ALL);
	MMIO_D(SPRSIZE(PIPE_B), D_ALL);
	MMIO_D(SPRKEYVAL(PIPE_B), D_ALL);
	MMIO_D(SPRKEYMSK(PIPE_B), D_ALL);
	MMIO_DH(SPRSURF(PIPE_B), D_ALL, शून्य, spr_surf_mmio_ग_लिखो);
	MMIO_D(SPRKEYMAX(PIPE_B), D_ALL);
	MMIO_D(SPROFFSET(PIPE_B), D_ALL);
	MMIO_D(SPRSCALE(PIPE_B), D_ALL);
	MMIO_D(SPRSURFLIVE(PIPE_B), D_ALL);
	MMIO_DH(REG_50080(PIPE_B, PLANE_SPRITE0), D_ALL, शून्य,
		reg50080_mmio_ग_लिखो);

	MMIO_D(SPRCTL(PIPE_C), D_ALL);
	MMIO_D(SPRLINOFF(PIPE_C), D_ALL);
	MMIO_D(SPRSTRIDE(PIPE_C), D_ALL);
	MMIO_D(SPRPOS(PIPE_C), D_ALL);
	MMIO_D(SPRSIZE(PIPE_C), D_ALL);
	MMIO_D(SPRKEYVAL(PIPE_C), D_ALL);
	MMIO_D(SPRKEYMSK(PIPE_C), D_ALL);
	MMIO_DH(SPRSURF(PIPE_C), D_ALL, शून्य, spr_surf_mmio_ग_लिखो);
	MMIO_D(SPRKEYMAX(PIPE_C), D_ALL);
	MMIO_D(SPROFFSET(PIPE_C), D_ALL);
	MMIO_D(SPRSCALE(PIPE_C), D_ALL);
	MMIO_D(SPRSURFLIVE(PIPE_C), D_ALL);
	MMIO_DH(REG_50080(PIPE_C, PLANE_SPRITE0), D_ALL, शून्य,
		reg50080_mmio_ग_लिखो);

	MMIO_D(HTOTAL(TRANSCODER_A), D_ALL);
	MMIO_D(HBLANK(TRANSCODER_A), D_ALL);
	MMIO_D(HSYNC(TRANSCODER_A), D_ALL);
	MMIO_D(VTOTAL(TRANSCODER_A), D_ALL);
	MMIO_D(VBLANK(TRANSCODER_A), D_ALL);
	MMIO_D(VSYNC(TRANSCODER_A), D_ALL);
	MMIO_D(BCLRPAT(TRANSCODER_A), D_ALL);
	MMIO_D(VSYNCSHIFT(TRANSCODER_A), D_ALL);
	MMIO_D(PIPESRC(TRANSCODER_A), D_ALL);

	MMIO_D(HTOTAL(TRANSCODER_B), D_ALL);
	MMIO_D(HBLANK(TRANSCODER_B), D_ALL);
	MMIO_D(HSYNC(TRANSCODER_B), D_ALL);
	MMIO_D(VTOTAL(TRANSCODER_B), D_ALL);
	MMIO_D(VBLANK(TRANSCODER_B), D_ALL);
	MMIO_D(VSYNC(TRANSCODER_B), D_ALL);
	MMIO_D(BCLRPAT(TRANSCODER_B), D_ALL);
	MMIO_D(VSYNCSHIFT(TRANSCODER_B), D_ALL);
	MMIO_D(PIPESRC(TRANSCODER_B), D_ALL);

	MMIO_D(HTOTAL(TRANSCODER_C), D_ALL);
	MMIO_D(HBLANK(TRANSCODER_C), D_ALL);
	MMIO_D(HSYNC(TRANSCODER_C), D_ALL);
	MMIO_D(VTOTAL(TRANSCODER_C), D_ALL);
	MMIO_D(VBLANK(TRANSCODER_C), D_ALL);
	MMIO_D(VSYNC(TRANSCODER_C), D_ALL);
	MMIO_D(BCLRPAT(TRANSCODER_C), D_ALL);
	MMIO_D(VSYNCSHIFT(TRANSCODER_C), D_ALL);
	MMIO_D(PIPESRC(TRANSCODER_C), D_ALL);

	MMIO_D(HTOTAL(TRANSCODER_EDP), D_ALL);
	MMIO_D(HBLANK(TRANSCODER_EDP), D_ALL);
	MMIO_D(HSYNC(TRANSCODER_EDP), D_ALL);
	MMIO_D(VTOTAL(TRANSCODER_EDP), D_ALL);
	MMIO_D(VBLANK(TRANSCODER_EDP), D_ALL);
	MMIO_D(VSYNC(TRANSCODER_EDP), D_ALL);
	MMIO_D(BCLRPAT(TRANSCODER_EDP), D_ALL);
	MMIO_D(VSYNCSHIFT(TRANSCODER_EDP), D_ALL);

	MMIO_D(PIPE_DATA_M1(TRANSCODER_A), D_ALL);
	MMIO_D(PIPE_DATA_N1(TRANSCODER_A), D_ALL);
	MMIO_D(PIPE_DATA_M2(TRANSCODER_A), D_ALL);
	MMIO_D(PIPE_DATA_N2(TRANSCODER_A), D_ALL);
	MMIO_D(PIPE_LINK_M1(TRANSCODER_A), D_ALL);
	MMIO_D(PIPE_LINK_N1(TRANSCODER_A), D_ALL);
	MMIO_D(PIPE_LINK_M2(TRANSCODER_A), D_ALL);
	MMIO_D(PIPE_LINK_N2(TRANSCODER_A), D_ALL);

	MMIO_D(PIPE_DATA_M1(TRANSCODER_B), D_ALL);
	MMIO_D(PIPE_DATA_N1(TRANSCODER_B), D_ALL);
	MMIO_D(PIPE_DATA_M2(TRANSCODER_B), D_ALL);
	MMIO_D(PIPE_DATA_N2(TRANSCODER_B), D_ALL);
	MMIO_D(PIPE_LINK_M1(TRANSCODER_B), D_ALL);
	MMIO_D(PIPE_LINK_N1(TRANSCODER_B), D_ALL);
	MMIO_D(PIPE_LINK_M2(TRANSCODER_B), D_ALL);
	MMIO_D(PIPE_LINK_N2(TRANSCODER_B), D_ALL);

	MMIO_D(PIPE_DATA_M1(TRANSCODER_C), D_ALL);
	MMIO_D(PIPE_DATA_N1(TRANSCODER_C), D_ALL);
	MMIO_D(PIPE_DATA_M2(TRANSCODER_C), D_ALL);
	MMIO_D(PIPE_DATA_N2(TRANSCODER_C), D_ALL);
	MMIO_D(PIPE_LINK_M1(TRANSCODER_C), D_ALL);
	MMIO_D(PIPE_LINK_N1(TRANSCODER_C), D_ALL);
	MMIO_D(PIPE_LINK_M2(TRANSCODER_C), D_ALL);
	MMIO_D(PIPE_LINK_N2(TRANSCODER_C), D_ALL);

	MMIO_D(PIPE_DATA_M1(TRANSCODER_EDP), D_ALL);
	MMIO_D(PIPE_DATA_N1(TRANSCODER_EDP), D_ALL);
	MMIO_D(PIPE_DATA_M2(TRANSCODER_EDP), D_ALL);
	MMIO_D(PIPE_DATA_N2(TRANSCODER_EDP), D_ALL);
	MMIO_D(PIPE_LINK_M1(TRANSCODER_EDP), D_ALL);
	MMIO_D(PIPE_LINK_N1(TRANSCODER_EDP), D_ALL);
	MMIO_D(PIPE_LINK_M2(TRANSCODER_EDP), D_ALL);
	MMIO_D(PIPE_LINK_N2(TRANSCODER_EDP), D_ALL);

	MMIO_D(PF_CTL(PIPE_A), D_ALL);
	MMIO_D(PF_WIN_SZ(PIPE_A), D_ALL);
	MMIO_D(PF_WIN_POS(PIPE_A), D_ALL);
	MMIO_D(PF_VSCALE(PIPE_A), D_ALL);
	MMIO_D(PF_HSCALE(PIPE_A), D_ALL);

	MMIO_D(PF_CTL(PIPE_B), D_ALL);
	MMIO_D(PF_WIN_SZ(PIPE_B), D_ALL);
	MMIO_D(PF_WIN_POS(PIPE_B), D_ALL);
	MMIO_D(PF_VSCALE(PIPE_B), D_ALL);
	MMIO_D(PF_HSCALE(PIPE_B), D_ALL);

	MMIO_D(PF_CTL(PIPE_C), D_ALL);
	MMIO_D(PF_WIN_SZ(PIPE_C), D_ALL);
	MMIO_D(PF_WIN_POS(PIPE_C), D_ALL);
	MMIO_D(PF_VSCALE(PIPE_C), D_ALL);
	MMIO_D(PF_HSCALE(PIPE_C), D_ALL);

	MMIO_D(WM0_PIPE_ILK(PIPE_A), D_ALL);
	MMIO_D(WM0_PIPE_ILK(PIPE_B), D_ALL);
	MMIO_D(WM0_PIPE_ILK(PIPE_C), D_ALL);
	MMIO_D(WM1_LP_ILK, D_ALL);
	MMIO_D(WM2_LP_ILK, D_ALL);
	MMIO_D(WM3_LP_ILK, D_ALL);
	MMIO_D(WM1S_LP_ILK, D_ALL);
	MMIO_D(WM2S_LP_IVB, D_ALL);
	MMIO_D(WM3S_LP_IVB, D_ALL);

	MMIO_D(BLC_PWM_CPU_CTL2, D_ALL);
	MMIO_D(BLC_PWM_CPU_CTL, D_ALL);
	MMIO_D(BLC_PWM_PCH_CTL1, D_ALL);
	MMIO_D(BLC_PWM_PCH_CTL2, D_ALL);

	MMIO_D(_MMIO(0x48268), D_ALL);

	MMIO_F(PCH_GMBUS0, 4 * 4, 0, 0, 0, D_ALL, gmbus_mmio_पढ़ो,
		gmbus_mmio_ग_लिखो);
	MMIO_F(PCH_GPIO_BASE, 6 * 4, F_UNALIGN, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(_MMIO(0xe4f00), 0x28, 0, 0, 0, D_ALL, शून्य, शून्य);

	MMIO_F(_MMIO(_PCH_DPB_AUX_CH_CTL), 6 * 4, 0, 0, 0, D_PRE_SKL, शून्य,
		dp_aux_ch_ctl_mmio_ग_लिखो);
	MMIO_F(_MMIO(_PCH_DPC_AUX_CH_CTL), 6 * 4, 0, 0, 0, D_PRE_SKL, शून्य,
		dp_aux_ch_ctl_mmio_ग_लिखो);
	MMIO_F(_MMIO(_PCH_DPD_AUX_CH_CTL), 6 * 4, 0, 0, 0, D_PRE_SKL, शून्य,
		dp_aux_ch_ctl_mmio_ग_लिखो);

	MMIO_DH(PCH_ADPA, D_PRE_SKL, शून्य, pch_adpa_mmio_ग_लिखो);

	MMIO_DH(_MMIO(_PCH_TRANSACONF), D_ALL, शून्य, transconf_mmio_ग_लिखो);
	MMIO_DH(_MMIO(_PCH_TRANSBCONF), D_ALL, शून्य, transconf_mmio_ग_लिखो);

	MMIO_DH(FDI_RX_IIR(PIPE_A), D_ALL, शून्य, fdi_rx_iir_mmio_ग_लिखो);
	MMIO_DH(FDI_RX_IIR(PIPE_B), D_ALL, शून्य, fdi_rx_iir_mmio_ग_लिखो);
	MMIO_DH(FDI_RX_IIR(PIPE_C), D_ALL, शून्य, fdi_rx_iir_mmio_ग_लिखो);
	MMIO_DH(FDI_RX_IMR(PIPE_A), D_ALL, शून्य, update_fdi_rx_iir_status);
	MMIO_DH(FDI_RX_IMR(PIPE_B), D_ALL, शून्य, update_fdi_rx_iir_status);
	MMIO_DH(FDI_RX_IMR(PIPE_C), D_ALL, शून्य, update_fdi_rx_iir_status);
	MMIO_DH(FDI_RX_CTL(PIPE_A), D_ALL, शून्य, update_fdi_rx_iir_status);
	MMIO_DH(FDI_RX_CTL(PIPE_B), D_ALL, शून्य, update_fdi_rx_iir_status);
	MMIO_DH(FDI_RX_CTL(PIPE_C), D_ALL, शून्य, update_fdi_rx_iir_status);

	MMIO_D(_MMIO(_PCH_TRANS_HTOTAL_A), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_HBLANK_A), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_HSYNC_A), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_VTOTAL_A), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_VBLANK_A), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_VSYNC_A), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_VSYNCSHIFT_A), D_ALL);

	MMIO_D(_MMIO(_PCH_TRANS_HTOTAL_B), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_HBLANK_B), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_HSYNC_B), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_VTOTAL_B), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_VBLANK_B), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_VSYNC_B), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_VSYNCSHIFT_B), D_ALL);

	MMIO_D(_MMIO(_PCH_TRANSA_DATA_M1), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANSA_DATA_N1), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANSA_DATA_M2), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANSA_DATA_N2), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANSA_LINK_M1), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANSA_LINK_N1), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANSA_LINK_M2), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANSA_LINK_N2), D_ALL);

	MMIO_D(TRANS_DP_CTL(PIPE_A), D_ALL);
	MMIO_D(TRANS_DP_CTL(PIPE_B), D_ALL);
	MMIO_D(TRANS_DP_CTL(PIPE_C), D_ALL);

	MMIO_D(TVIDEO_DIP_CTL(PIPE_A), D_ALL);
	MMIO_D(TVIDEO_DIP_DATA(PIPE_A), D_ALL);
	MMIO_D(TVIDEO_DIP_GCP(PIPE_A), D_ALL);

	MMIO_D(TVIDEO_DIP_CTL(PIPE_B), D_ALL);
	MMIO_D(TVIDEO_DIP_DATA(PIPE_B), D_ALL);
	MMIO_D(TVIDEO_DIP_GCP(PIPE_B), D_ALL);

	MMIO_D(TVIDEO_DIP_CTL(PIPE_C), D_ALL);
	MMIO_D(TVIDEO_DIP_DATA(PIPE_C), D_ALL);
	MMIO_D(TVIDEO_DIP_GCP(PIPE_C), D_ALL);

	MMIO_D(_MMIO(_FDI_RXA_MISC), D_ALL);
	MMIO_D(_MMIO(_FDI_RXB_MISC), D_ALL);
	MMIO_D(_MMIO(_FDI_RXA_TUSIZE1), D_ALL);
	MMIO_D(_MMIO(_FDI_RXA_TUSIZE2), D_ALL);
	MMIO_D(_MMIO(_FDI_RXB_TUSIZE1), D_ALL);
	MMIO_D(_MMIO(_FDI_RXB_TUSIZE2), D_ALL);

	MMIO_DH(PCH_PP_CONTROL, D_ALL, शून्य, pch_pp_control_mmio_ग_लिखो);
	MMIO_D(PCH_PP_DIVISOR, D_ALL);
	MMIO_D(PCH_PP_STATUS,  D_ALL);
	MMIO_D(PCH_LVDS, D_ALL);
	MMIO_D(_MMIO(_PCH_DPLL_A), D_ALL);
	MMIO_D(_MMIO(_PCH_DPLL_B), D_ALL);
	MMIO_D(_MMIO(_PCH_FPA0), D_ALL);
	MMIO_D(_MMIO(_PCH_FPA1), D_ALL);
	MMIO_D(_MMIO(_PCH_FPB0), D_ALL);
	MMIO_D(_MMIO(_PCH_FPB1), D_ALL);
	MMIO_D(PCH_DREF_CONTROL, D_ALL);
	MMIO_D(PCH_RAWCLK_FREQ, D_ALL);
	MMIO_D(PCH_DPLL_SEL, D_ALL);

	MMIO_D(_MMIO(0x61208), D_ALL);
	MMIO_D(_MMIO(0x6120c), D_ALL);
	MMIO_D(PCH_PP_ON_DELAYS, D_ALL);
	MMIO_D(PCH_PP_OFF_DELAYS, D_ALL);

	MMIO_DH(_MMIO(0xe651c), D_ALL, dpy_reg_mmio_पढ़ो, शून्य);
	MMIO_DH(_MMIO(0xe661c), D_ALL, dpy_reg_mmio_पढ़ो, शून्य);
	MMIO_DH(_MMIO(0xe671c), D_ALL, dpy_reg_mmio_पढ़ो, शून्य);
	MMIO_DH(_MMIO(0xe681c), D_ALL, dpy_reg_mmio_पढ़ो, शून्य);
	MMIO_DH(_MMIO(0xe6c04), D_ALL, dpy_reg_mmio_पढ़ो, शून्य);
	MMIO_DH(_MMIO(0xe6e1c), D_ALL, dpy_reg_mmio_पढ़ो, शून्य);

	MMIO_RO(PCH_PORT_HOTPLUG, D_ALL, 0,
		PORTA_HOTPLUG_STATUS_MASK
		| PORTB_HOTPLUG_STATUS_MASK
		| PORTC_HOTPLUG_STATUS_MASK
		| PORTD_HOTPLUG_STATUS_MASK,
		शून्य, शून्य);

	MMIO_DH(LCPLL_CTL, D_ALL, शून्य, lcpll_ctl_mmio_ग_लिखो);
	MMIO_D(FUSE_STRAP, D_ALL);
	MMIO_D(DIGITAL_PORT_HOTPLUG_CNTRL, D_ALL);

	MMIO_D(DISP_ARB_CTL, D_ALL);
	MMIO_D(DISP_ARB_CTL2, D_ALL);

	MMIO_D(ILK_DISPLAY_CHICKEN1, D_ALL);
	MMIO_D(ILK_DISPLAY_CHICKEN2, D_ALL);
	MMIO_D(ILK_DSPCLK_GATE_D, D_ALL);

	MMIO_D(SOUTH_CHICKEN1, D_ALL);
	MMIO_DH(SOUTH_CHICKEN2, D_ALL, शून्य, south_chicken2_mmio_ग_लिखो);
	MMIO_D(_MMIO(_TRANSA_CHICKEN1), D_ALL);
	MMIO_D(_MMIO(_TRANSB_CHICKEN1), D_ALL);
	MMIO_D(SOUTH_DSPCLK_GATE_D, D_ALL);
	MMIO_D(_MMIO(_TRANSA_CHICKEN2), D_ALL);
	MMIO_D(_MMIO(_TRANSB_CHICKEN2), D_ALL);

	MMIO_D(ILK_DPFC_CB_BASE, D_ALL);
	MMIO_D(ILK_DPFC_CONTROL, D_ALL);
	MMIO_D(ILK_DPFC_RECOMP_CTL, D_ALL);
	MMIO_D(ILK_DPFC_STATUS, D_ALL);
	MMIO_D(ILK_DPFC_FENCE_YOFF, D_ALL);
	MMIO_D(ILK_DPFC_CHICKEN, D_ALL);
	MMIO_D(ILK_FBC_RT_BASE, D_ALL);

	MMIO_D(IPS_CTL, D_ALL);

	MMIO_D(PIPE_CSC_COEFF_RY_GY(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_BY(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_RU_GU(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_BU(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_RV_GV(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_BV(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_MODE(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_PRखातापूर्णF_HI(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_PRखातापूर्णF_ME(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_PRखातापूर्णF_LO(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_POSTOFF_HI(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_POSTOFF_ME(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_POSTOFF_LO(PIPE_A), D_ALL);

	MMIO_D(PIPE_CSC_COEFF_RY_GY(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_BY(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_RU_GU(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_BU(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_RV_GV(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_BV(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_MODE(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_PRखातापूर्णF_HI(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_PRखातापूर्णF_ME(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_PRखातापूर्णF_LO(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_POSTOFF_HI(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_POSTOFF_ME(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_POSTOFF_LO(PIPE_B), D_ALL);

	MMIO_D(PIPE_CSC_COEFF_RY_GY(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_BY(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_RU_GU(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_BU(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_RV_GV(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_BV(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_MODE(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_PRखातापूर्णF_HI(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_PRखातापूर्णF_ME(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_PRखातापूर्णF_LO(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_POSTOFF_HI(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_POSTOFF_ME(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_POSTOFF_LO(PIPE_C), D_ALL);

	MMIO_D(PREC_PAL_INDEX(PIPE_A), D_ALL);
	MMIO_D(PREC_PAL_DATA(PIPE_A), D_ALL);
	MMIO_F(PREC_PAL_GC_MAX(PIPE_A, 0), 4 * 3, 0, 0, 0, D_ALL, शून्य, शून्य);

	MMIO_D(PREC_PAL_INDEX(PIPE_B), D_ALL);
	MMIO_D(PREC_PAL_DATA(PIPE_B), D_ALL);
	MMIO_F(PREC_PAL_GC_MAX(PIPE_B, 0), 4 * 3, 0, 0, 0, D_ALL, शून्य, शून्य);

	MMIO_D(PREC_PAL_INDEX(PIPE_C), D_ALL);
	MMIO_D(PREC_PAL_DATA(PIPE_C), D_ALL);
	MMIO_F(PREC_PAL_GC_MAX(PIPE_C, 0), 4 * 3, 0, 0, 0, D_ALL, शून्य, शून्य);

	MMIO_D(_MMIO(0x60110), D_ALL);
	MMIO_D(_MMIO(0x61110), D_ALL);
	MMIO_F(_MMIO(0x70400), 0x40, 0, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(_MMIO(0x71400), 0x40, 0, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(_MMIO(0x72400), 0x40, 0, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(_MMIO(0x70440), 0xc, 0, 0, 0, D_PRE_SKL, शून्य, शून्य);
	MMIO_F(_MMIO(0x71440), 0xc, 0, 0, 0, D_PRE_SKL, शून्य, शून्य);
	MMIO_F(_MMIO(0x72440), 0xc, 0, 0, 0, D_PRE_SKL, शून्य, शून्य);
	MMIO_F(_MMIO(0x7044c), 0xc, 0, 0, 0, D_PRE_SKL, शून्य, शून्य);
	MMIO_F(_MMIO(0x7144c), 0xc, 0, 0, 0, D_PRE_SKL, शून्य, शून्य);
	MMIO_F(_MMIO(0x7244c), 0xc, 0, 0, 0, D_PRE_SKL, शून्य, शून्य);

	MMIO_D(WM_LINETIME(PIPE_A), D_ALL);
	MMIO_D(WM_LINETIME(PIPE_B), D_ALL);
	MMIO_D(WM_LINETIME(PIPE_C), D_ALL);
	MMIO_D(SPLL_CTL, D_ALL);
	MMIO_D(_MMIO(_WRPLL_CTL1), D_ALL);
	MMIO_D(_MMIO(_WRPLL_CTL2), D_ALL);
	MMIO_D(PORT_CLK_SEL(PORT_A), D_ALL);
	MMIO_D(PORT_CLK_SEL(PORT_B), D_ALL);
	MMIO_D(PORT_CLK_SEL(PORT_C), D_ALL);
	MMIO_D(PORT_CLK_SEL(PORT_D), D_ALL);
	MMIO_D(PORT_CLK_SEL(PORT_E), D_ALL);
	MMIO_D(TRANS_CLK_SEL(TRANSCODER_A), D_ALL);
	MMIO_D(TRANS_CLK_SEL(TRANSCODER_B), D_ALL);
	MMIO_D(TRANS_CLK_SEL(TRANSCODER_C), D_ALL);

	MMIO_D(HSW_NDE_RSTWRN_OPT, D_ALL);
	MMIO_D(_MMIO(0x46508), D_ALL);

	MMIO_D(_MMIO(0x49080), D_ALL);
	MMIO_D(_MMIO(0x49180), D_ALL);
	MMIO_D(_MMIO(0x49280), D_ALL);

	MMIO_F(_MMIO(0x49090), 0x14, 0, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(_MMIO(0x49190), 0x14, 0, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(_MMIO(0x49290), 0x14, 0, 0, 0, D_ALL, शून्य, शून्य);

	MMIO_D(GAMMA_MODE(PIPE_A), D_ALL);
	MMIO_D(GAMMA_MODE(PIPE_B), D_ALL);
	MMIO_D(GAMMA_MODE(PIPE_C), D_ALL);

	MMIO_D(PIPE_MULT(PIPE_A), D_ALL);
	MMIO_D(PIPE_MULT(PIPE_B), D_ALL);
	MMIO_D(PIPE_MULT(PIPE_C), D_ALL);

	MMIO_D(HSW_TVIDEO_DIP_CTL(TRANSCODER_A), D_ALL);
	MMIO_D(HSW_TVIDEO_DIP_CTL(TRANSCODER_B), D_ALL);
	MMIO_D(HSW_TVIDEO_DIP_CTL(TRANSCODER_C), D_ALL);

	MMIO_DH(SFUSE_STRAP, D_ALL, शून्य, शून्य);
	MMIO_D(SBI_ADDR, D_ALL);
	MMIO_DH(SBI_DATA, D_ALL, sbi_data_mmio_पढ़ो, शून्य);
	MMIO_DH(SBI_CTL_STAT, D_ALL, शून्य, sbi_ctl_mmio_ग_लिखो);
	MMIO_D(PIXCLK_GATE, D_ALL);

	MMIO_F(_MMIO(_DPA_AUX_CH_CTL), 6 * 4, 0, 0, 0, D_ALL, शून्य,
		dp_aux_ch_ctl_mmio_ग_लिखो);

	MMIO_DH(DDI_BUF_CTL(PORT_A), D_ALL, शून्य, ddi_buf_ctl_mmio_ग_लिखो);
	MMIO_DH(DDI_BUF_CTL(PORT_B), D_ALL, शून्य, ddi_buf_ctl_mmio_ग_लिखो);
	MMIO_DH(DDI_BUF_CTL(PORT_C), D_ALL, शून्य, ddi_buf_ctl_mmio_ग_लिखो);
	MMIO_DH(DDI_BUF_CTL(PORT_D), D_ALL, शून्य, ddi_buf_ctl_mmio_ग_लिखो);
	MMIO_DH(DDI_BUF_CTL(PORT_E), D_ALL, शून्य, ddi_buf_ctl_mmio_ग_लिखो);

	MMIO_DH(DP_TP_CTL(PORT_A), D_ALL, शून्य, dp_tp_ctl_mmio_ग_लिखो);
	MMIO_DH(DP_TP_CTL(PORT_B), D_ALL, शून्य, dp_tp_ctl_mmio_ग_लिखो);
	MMIO_DH(DP_TP_CTL(PORT_C), D_ALL, शून्य, dp_tp_ctl_mmio_ग_लिखो);
	MMIO_DH(DP_TP_CTL(PORT_D), D_ALL, शून्य, dp_tp_ctl_mmio_ग_लिखो);
	MMIO_DH(DP_TP_CTL(PORT_E), D_ALL, शून्य, dp_tp_ctl_mmio_ग_लिखो);

	MMIO_DH(DP_TP_STATUS(PORT_A), D_ALL, शून्य, dp_tp_status_mmio_ग_लिखो);
	MMIO_DH(DP_TP_STATUS(PORT_B), D_ALL, शून्य, dp_tp_status_mmio_ग_लिखो);
	MMIO_DH(DP_TP_STATUS(PORT_C), D_ALL, शून्य, dp_tp_status_mmio_ग_लिखो);
	MMIO_DH(DP_TP_STATUS(PORT_D), D_ALL, शून्य, dp_tp_status_mmio_ग_लिखो);
	MMIO_DH(DP_TP_STATUS(PORT_E), D_ALL, शून्य, शून्य);

	MMIO_F(_MMIO(_DDI_BUF_TRANS_A), 0x50, 0, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(_MMIO(0x64e60), 0x50, 0, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(_MMIO(0x64eC0), 0x50, 0, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(_MMIO(0x64f20), 0x50, 0, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(_MMIO(0x64f80), 0x50, 0, 0, 0, D_ALL, शून्य, शून्य);

	MMIO_D(HSW_AUD_CFG(PIPE_A), D_ALL);
	MMIO_D(HSW_AUD_PIN_ELD_CP_VLD, D_ALL);
	MMIO_D(HSW_AUD_MISC_CTRL(PIPE_A), D_ALL);

	MMIO_DH(_MMIO(_TRANS_DDI_FUNC_CTL_A), D_ALL, शून्य, शून्य);
	MMIO_DH(_MMIO(_TRANS_DDI_FUNC_CTL_B), D_ALL, शून्य, शून्य);
	MMIO_DH(_MMIO(_TRANS_DDI_FUNC_CTL_C), D_ALL, शून्य, शून्य);
	MMIO_DH(_MMIO(_TRANS_DDI_FUNC_CTL_EDP), D_ALL, शून्य, शून्य);

	MMIO_D(_MMIO(_TRANSA_MSA_MISC), D_ALL);
	MMIO_D(_MMIO(_TRANSB_MSA_MISC), D_ALL);
	MMIO_D(_MMIO(_TRANSC_MSA_MISC), D_ALL);
	MMIO_D(_MMIO(_TRANS_EDP_MSA_MISC), D_ALL);

	MMIO_DH(FORCEWAKE, D_ALL, शून्य, शून्य);
	MMIO_D(FORCEWAKE_ACK, D_ALL);
	MMIO_D(GEN6_GT_CORE_STATUS, D_ALL);
	MMIO_D(GEN6_GT_THREAD_STATUS_REG, D_ALL);
	MMIO_DFH(GTFIFODBG, D_ALL, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(GTFIFOCTL, D_ALL, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DH(FORCEWAKE_MT, D_PRE_SKL, शून्य, mul_क्रमce_wake_ग_लिखो);
	MMIO_DH(FORCEWAKE_ACK_HSW, D_BDW, शून्य, शून्य);
	MMIO_D(ECOBUS, D_ALL);
	MMIO_DH(GEN6_RC_CONTROL, D_ALL, शून्य, शून्य);
	MMIO_DH(GEN6_RC_STATE, D_ALL, शून्य, शून्य);
	MMIO_D(GEN6_RPNSWREQ, D_ALL);
	MMIO_D(GEN6_RC_VIDEO_FREQ, D_ALL);
	MMIO_D(GEN6_RP_DOWN_TIMEOUT, D_ALL);
	MMIO_D(GEN6_RP_INTERRUPT_LIMITS, D_ALL);
	MMIO_D(GEN6_RPSTAT1, D_ALL);
	MMIO_D(GEN6_RP_CONTROL, D_ALL);
	MMIO_D(GEN6_RP_UP_THRESHOLD, D_ALL);
	MMIO_D(GEN6_RP_DOWN_THRESHOLD, D_ALL);
	MMIO_D(GEN6_RP_CUR_UP_EI, D_ALL);
	MMIO_D(GEN6_RP_CUR_UP, D_ALL);
	MMIO_D(GEN6_RP_PREV_UP, D_ALL);
	MMIO_D(GEN6_RP_CUR_DOWN_EI, D_ALL);
	MMIO_D(GEN6_RP_CUR_DOWN, D_ALL);
	MMIO_D(GEN6_RP_PREV_DOWN, D_ALL);
	MMIO_D(GEN6_RP_UP_EI, D_ALL);
	MMIO_D(GEN6_RP_DOWN_EI, D_ALL);
	MMIO_D(GEN6_RP_IDLE_HYSTERSIS, D_ALL);
	MMIO_D(GEN6_RC1_WAKE_RATE_LIMIT, D_ALL);
	MMIO_D(GEN6_RC6_WAKE_RATE_LIMIT, D_ALL);
	MMIO_D(GEN6_RC6pp_WAKE_RATE_LIMIT, D_ALL);
	MMIO_D(GEN6_RC_EVALUATION_INTERVAL, D_ALL);
	MMIO_D(GEN6_RC_IDLE_HYSTERSIS, D_ALL);
	MMIO_D(GEN6_RC_SLEEP, D_ALL);
	MMIO_D(GEN6_RC1e_THRESHOLD, D_ALL);
	MMIO_D(GEN6_RC6_THRESHOLD, D_ALL);
	MMIO_D(GEN6_RC6p_THRESHOLD, D_ALL);
	MMIO_D(GEN6_RC6pp_THRESHOLD, D_ALL);
	MMIO_D(GEN6_PMINTRMSK, D_ALL);
	MMIO_DH(HSW_PWR_WELL_CTL1, D_BDW, शून्य, घातer_well_ctl_mmio_ग_लिखो);
	MMIO_DH(HSW_PWR_WELL_CTL2, D_BDW, शून्य, घातer_well_ctl_mmio_ग_लिखो);
	MMIO_DH(HSW_PWR_WELL_CTL3, D_BDW, शून्य, घातer_well_ctl_mmio_ग_लिखो);
	MMIO_DH(HSW_PWR_WELL_CTL4, D_BDW, शून्य, घातer_well_ctl_mmio_ग_लिखो);
	MMIO_DH(HSW_PWR_WELL_CTL5, D_BDW, शून्य, घातer_well_ctl_mmio_ग_लिखो);
	MMIO_DH(HSW_PWR_WELL_CTL6, D_BDW, शून्य, घातer_well_ctl_mmio_ग_लिखो);

	MMIO_D(RSTDBYCTL, D_ALL);

	MMIO_DH(GEN6_GDRST, D_ALL, शून्य, gdrst_mmio_ग_लिखो);
	MMIO_F(FENCE_REG_GEN6_LO(0), 0x80, 0, 0, 0, D_ALL, fence_mmio_पढ़ो, fence_mmio_ग_लिखो);
	MMIO_DH(CPU_VGACNTRL, D_ALL, शून्य, vga_control_mmio_ग_लिखो);

	MMIO_D(TILECTL, D_ALL);

	MMIO_D(GEN6_UCGCTL1, D_ALL);
	MMIO_D(GEN6_UCGCTL2, D_ALL);

	MMIO_F(_MMIO(0x4f000), 0x90, 0, 0, 0, D_ALL, शून्य, शून्य);

	MMIO_D(GEN6_PCODE_DATA, D_ALL);
	MMIO_D(_MMIO(0x13812c), D_ALL);
	MMIO_DH(GEN7_ERR_INT, D_ALL, शून्य, शून्य);
	MMIO_D(HSW_EDRAM_CAP, D_ALL);
	MMIO_D(HSW_IDICR, D_ALL);
	MMIO_DH(GFX_FLSH_CNTL_GEN6, D_ALL, शून्य, शून्य);

	MMIO_D(_MMIO(0x3c), D_ALL);
	MMIO_D(_MMIO(0x860), D_ALL);
	MMIO_D(ECOSKPD, D_ALL);
	MMIO_D(_MMIO(0x121d0), D_ALL);
	MMIO_D(GEN6_BLITTER_ECOSKPD, D_ALL);
	MMIO_D(_MMIO(0x41d0), D_ALL);
	MMIO_D(GAC_ECO_BITS, D_ALL);
	MMIO_D(_MMIO(0x6200), D_ALL);
	MMIO_D(_MMIO(0x6204), D_ALL);
	MMIO_D(_MMIO(0x6208), D_ALL);
	MMIO_D(_MMIO(0x7118), D_ALL);
	MMIO_D(_MMIO(0x7180), D_ALL);
	MMIO_D(_MMIO(0x7408), D_ALL);
	MMIO_D(_MMIO(0x7c00), D_ALL);
	MMIO_DH(GEN6_MBCTL, D_ALL, शून्य, mbctl_ग_लिखो);
	MMIO_D(_MMIO(0x911c), D_ALL);
	MMIO_D(_MMIO(0x9120), D_ALL);
	MMIO_DFH(GEN7_UCGCTL4, D_ALL, F_CMD_ACCESS, शून्य, शून्य);

	MMIO_D(GAB_CTL, D_ALL);
	MMIO_D(_MMIO(0x48800), D_ALL);
	MMIO_D(_MMIO(0xce044), D_ALL);
	MMIO_D(_MMIO(0xe6500), D_ALL);
	MMIO_D(_MMIO(0xe6504), D_ALL);
	MMIO_D(_MMIO(0xe6600), D_ALL);
	MMIO_D(_MMIO(0xe6604), D_ALL);
	MMIO_D(_MMIO(0xe6700), D_ALL);
	MMIO_D(_MMIO(0xe6704), D_ALL);
	MMIO_D(_MMIO(0xe6800), D_ALL);
	MMIO_D(_MMIO(0xe6804), D_ALL);
	MMIO_D(PCH_GMBUS4, D_ALL);
	MMIO_D(PCH_GMBUS5, D_ALL);

	MMIO_D(_MMIO(0x902c), D_ALL);
	MMIO_D(_MMIO(0xec008), D_ALL);
	MMIO_D(_MMIO(0xec00c), D_ALL);
	MMIO_D(_MMIO(0xec008 + 0x18), D_ALL);
	MMIO_D(_MMIO(0xec00c + 0x18), D_ALL);
	MMIO_D(_MMIO(0xec008 + 0x18 * 2), D_ALL);
	MMIO_D(_MMIO(0xec00c + 0x18 * 2), D_ALL);
	MMIO_D(_MMIO(0xec008 + 0x18 * 3), D_ALL);
	MMIO_D(_MMIO(0xec00c + 0x18 * 3), D_ALL);
	MMIO_D(_MMIO(0xec408), D_ALL);
	MMIO_D(_MMIO(0xec40c), D_ALL);
	MMIO_D(_MMIO(0xec408 + 0x18), D_ALL);
	MMIO_D(_MMIO(0xec40c + 0x18), D_ALL);
	MMIO_D(_MMIO(0xec408 + 0x18 * 2), D_ALL);
	MMIO_D(_MMIO(0xec40c + 0x18 * 2), D_ALL);
	MMIO_D(_MMIO(0xec408 + 0x18 * 3), D_ALL);
	MMIO_D(_MMIO(0xec40c + 0x18 * 3), D_ALL);
	MMIO_D(_MMIO(0xfc810), D_ALL);
	MMIO_D(_MMIO(0xfc81c), D_ALL);
	MMIO_D(_MMIO(0xfc828), D_ALL);
	MMIO_D(_MMIO(0xfc834), D_ALL);
	MMIO_D(_MMIO(0xfcc00), D_ALL);
	MMIO_D(_MMIO(0xfcc0c), D_ALL);
	MMIO_D(_MMIO(0xfcc18), D_ALL);
	MMIO_D(_MMIO(0xfcc24), D_ALL);
	MMIO_D(_MMIO(0xfd000), D_ALL);
	MMIO_D(_MMIO(0xfd00c), D_ALL);
	MMIO_D(_MMIO(0xfd018), D_ALL);
	MMIO_D(_MMIO(0xfd024), D_ALL);
	MMIO_D(_MMIO(0xfd034), D_ALL);

	MMIO_DH(FPGA_DBG, D_ALL, शून्य, fpga_dbg_mmio_ग_लिखो);
	MMIO_D(_MMIO(0x2054), D_ALL);
	MMIO_D(_MMIO(0x12054), D_ALL);
	MMIO_D(_MMIO(0x22054), D_ALL);
	MMIO_D(_MMIO(0x1a054), D_ALL);

	MMIO_D(_MMIO(0x44070), D_ALL);
	MMIO_DFH(_MMIO(0x215c), D_BDW_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x2178), D_ALL, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x217c), D_ALL, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x12178), D_ALL, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x1217c), D_ALL, F_CMD_ACCESS, शून्य, शून्य);

	MMIO_F(_MMIO(0x2290), 8, F_CMD_ACCESS, 0, 0, D_BDW_PLUS, शून्य, शून्य);
	MMIO_D(_MMIO(0x2b00), D_BDW_PLUS);
	MMIO_D(_MMIO(0x2360), D_BDW_PLUS);
	MMIO_F(_MMIO(0x5200), 32, F_CMD_ACCESS, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(_MMIO(0x5240), 32, F_CMD_ACCESS, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(_MMIO(0x5280), 16, F_CMD_ACCESS, 0, 0, D_ALL, शून्य, शून्य);

	MMIO_DFH(_MMIO(0x1c17c), D_BDW_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x1c178), D_BDW_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(BCS_SWCTRL, D_ALL, F_CMD_ACCESS, शून्य, शून्य);

	MMIO_F(HS_INVOCATION_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(DS_INVOCATION_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(IA_VERTICES_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(IA_PRIMITIVES_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(VS_INVOCATION_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(GS_INVOCATION_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(GS_PRIMITIVES_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(CL_INVOCATION_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(CL_PRIMITIVES_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(PS_INVOCATION_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_F(PS_DEPTH_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, शून्य, शून्य);
	MMIO_DH(_MMIO(0x4260), D_BDW_PLUS, शून्य, gvt_reg_tlb_control_handler);
	MMIO_DH(_MMIO(0x4264), D_BDW_PLUS, शून्य, gvt_reg_tlb_control_handler);
	MMIO_DH(_MMIO(0x4268), D_BDW_PLUS, शून्य, gvt_reg_tlb_control_handler);
	MMIO_DH(_MMIO(0x426c), D_BDW_PLUS, शून्य, gvt_reg_tlb_control_handler);
	MMIO_DH(_MMIO(0x4270), D_BDW_PLUS, शून्य, gvt_reg_tlb_control_handler);
	MMIO_DFH(_MMIO(0x4094), D_BDW_PLUS, F_CMD_ACCESS, शून्य, शून्य);

	MMIO_DFH(ARB_MODE, D_ALL, F_MODE_MASK | F_CMD_ACCESS, शून्य, शून्य);
	MMIO_RING_GM(RING_BBADDR, D_ALL, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x2220), D_ALL, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x12220), D_ALL, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x22220), D_ALL, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_RING_DFH(RING_SYNC_1, D_ALL, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_RING_DFH(RING_SYNC_0, D_ALL, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x22178), D_BDW_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x1a178), D_BDW_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x1a17c), D_BDW_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x2217c), D_BDW_PLUS, F_CMD_ACCESS, शून्य, शून्य);

	MMIO_DH(EDP_PSR_IMR, D_BDW_PLUS, शून्य, edp_psr_imr_iir_ग_लिखो);
	MMIO_DH(EDP_PSR_IIR, D_BDW_PLUS, शून्य, edp_psr_imr_iir_ग_लिखो);
	MMIO_DH(GUC_STATUS, D_ALL, guc_status_पढ़ो, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक init_bdw_mmio_info(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा drm_i915_निजी *dev_priv = gvt->gt->i915;
	पूर्णांक ret;

	MMIO_DH(GEN8_GT_IMR(0), D_BDW_PLUS, शून्य, पूर्णांकel_vgpu_reg_imr_handler);
	MMIO_DH(GEN8_GT_IER(0), D_BDW_PLUS, शून्य, पूर्णांकel_vgpu_reg_ier_handler);
	MMIO_DH(GEN8_GT_IIR(0), D_BDW_PLUS, शून्य, पूर्णांकel_vgpu_reg_iir_handler);
	MMIO_D(GEN8_GT_ISR(0), D_BDW_PLUS);

	MMIO_DH(GEN8_GT_IMR(1), D_BDW_PLUS, शून्य, पूर्णांकel_vgpu_reg_imr_handler);
	MMIO_DH(GEN8_GT_IER(1), D_BDW_PLUS, शून्य, पूर्णांकel_vgpu_reg_ier_handler);
	MMIO_DH(GEN8_GT_IIR(1), D_BDW_PLUS, शून्य, पूर्णांकel_vgpu_reg_iir_handler);
	MMIO_D(GEN8_GT_ISR(1), D_BDW_PLUS);

	MMIO_DH(GEN8_GT_IMR(2), D_BDW_PLUS, शून्य, पूर्णांकel_vgpu_reg_imr_handler);
	MMIO_DH(GEN8_GT_IER(2), D_BDW_PLUS, शून्य, पूर्णांकel_vgpu_reg_ier_handler);
	MMIO_DH(GEN8_GT_IIR(2), D_BDW_PLUS, शून्य, पूर्णांकel_vgpu_reg_iir_handler);
	MMIO_D(GEN8_GT_ISR(2), D_BDW_PLUS);

	MMIO_DH(GEN8_GT_IMR(3), D_BDW_PLUS, शून्य, पूर्णांकel_vgpu_reg_imr_handler);
	MMIO_DH(GEN8_GT_IER(3), D_BDW_PLUS, शून्य, पूर्णांकel_vgpu_reg_ier_handler);
	MMIO_DH(GEN8_GT_IIR(3), D_BDW_PLUS, शून्य, पूर्णांकel_vgpu_reg_iir_handler);
	MMIO_D(GEN8_GT_ISR(3), D_BDW_PLUS);

	MMIO_DH(GEN8_DE_PIPE_IMR(PIPE_A), D_BDW_PLUS, शून्य,
		पूर्णांकel_vgpu_reg_imr_handler);
	MMIO_DH(GEN8_DE_PIPE_IER(PIPE_A), D_BDW_PLUS, शून्य,
		पूर्णांकel_vgpu_reg_ier_handler);
	MMIO_DH(GEN8_DE_PIPE_IIR(PIPE_A), D_BDW_PLUS, शून्य,
		पूर्णांकel_vgpu_reg_iir_handler);
	MMIO_D(GEN8_DE_PIPE_ISR(PIPE_A), D_BDW_PLUS);

	MMIO_DH(GEN8_DE_PIPE_IMR(PIPE_B), D_BDW_PLUS, शून्य,
		पूर्णांकel_vgpu_reg_imr_handler);
	MMIO_DH(GEN8_DE_PIPE_IER(PIPE_B), D_BDW_PLUS, शून्य,
		पूर्णांकel_vgpu_reg_ier_handler);
	MMIO_DH(GEN8_DE_PIPE_IIR(PIPE_B), D_BDW_PLUS, शून्य,
		पूर्णांकel_vgpu_reg_iir_handler);
	MMIO_D(GEN8_DE_PIPE_ISR(PIPE_B), D_BDW_PLUS);

	MMIO_DH(GEN8_DE_PIPE_IMR(PIPE_C), D_BDW_PLUS, शून्य,
		पूर्णांकel_vgpu_reg_imr_handler);
	MMIO_DH(GEN8_DE_PIPE_IER(PIPE_C), D_BDW_PLUS, शून्य,
		पूर्णांकel_vgpu_reg_ier_handler);
	MMIO_DH(GEN8_DE_PIPE_IIR(PIPE_C), D_BDW_PLUS, शून्य,
		पूर्णांकel_vgpu_reg_iir_handler);
	MMIO_D(GEN8_DE_PIPE_ISR(PIPE_C), D_BDW_PLUS);

	MMIO_DH(GEN8_DE_PORT_IMR, D_BDW_PLUS, शून्य, पूर्णांकel_vgpu_reg_imr_handler);
	MMIO_DH(GEN8_DE_PORT_IER, D_BDW_PLUS, शून्य, पूर्णांकel_vgpu_reg_ier_handler);
	MMIO_DH(GEN8_DE_PORT_IIR, D_BDW_PLUS, शून्य, पूर्णांकel_vgpu_reg_iir_handler);
	MMIO_D(GEN8_DE_PORT_ISR, D_BDW_PLUS);

	MMIO_DH(GEN8_DE_MISC_IMR, D_BDW_PLUS, शून्य, पूर्णांकel_vgpu_reg_imr_handler);
	MMIO_DH(GEN8_DE_MISC_IER, D_BDW_PLUS, शून्य, पूर्णांकel_vgpu_reg_ier_handler);
	MMIO_DH(GEN8_DE_MISC_IIR, D_BDW_PLUS, शून्य, पूर्णांकel_vgpu_reg_iir_handler);
	MMIO_D(GEN8_DE_MISC_ISR, D_BDW_PLUS);

	MMIO_DH(GEN8_PCU_IMR, D_BDW_PLUS, शून्य, पूर्णांकel_vgpu_reg_imr_handler);
	MMIO_DH(GEN8_PCU_IER, D_BDW_PLUS, शून्य, पूर्णांकel_vgpu_reg_ier_handler);
	MMIO_DH(GEN8_PCU_IIR, D_BDW_PLUS, शून्य, पूर्णांकel_vgpu_reg_iir_handler);
	MMIO_D(GEN8_PCU_ISR, D_BDW_PLUS);

	MMIO_DH(GEN8_MASTER_IRQ, D_BDW_PLUS, शून्य,
		पूर्णांकel_vgpu_reg_master_irq_handler);

	MMIO_RING_DFH(RING_ACTHD_UDW, D_BDW_PLUS, 0,
		mmio_पढ़ो_from_hw, शून्य);

#घोषणा RING_REG(base) _MMIO((base) + 0xd0)
	MMIO_RING_F(RING_REG, 4, F_RO, 0,
		~_MASKED_BIT_ENABLE(RESET_CTL_REQUEST_RESET), D_BDW_PLUS, शून्य,
		ring_reset_ctl_ग_लिखो);
#अघोषित RING_REG

#घोषणा RING_REG(base) _MMIO((base) + 0x230)
	MMIO_RING_DFH(RING_REG, D_BDW_PLUS, 0, शून्य, elsp_mmio_ग_लिखो);
#अघोषित RING_REG

#घोषणा RING_REG(base) _MMIO((base) + 0x234)
	MMIO_RING_F(RING_REG, 8, F_RO, 0, ~0, D_BDW_PLUS,
		शून्य, शून्य);
#अघोषित RING_REG

#घोषणा RING_REG(base) _MMIO((base) + 0x244)
	MMIO_RING_DFH(RING_REG, D_BDW_PLUS, F_CMD_ACCESS, शून्य, शून्य);
#अघोषित RING_REG

#घोषणा RING_REG(base) _MMIO((base) + 0x370)
	MMIO_RING_F(RING_REG, 48, F_RO, 0, ~0, D_BDW_PLUS, शून्य, शून्य);
#अघोषित RING_REG

#घोषणा RING_REG(base) _MMIO((base) + 0x3a0)
	MMIO_RING_DFH(RING_REG, D_BDW_PLUS, F_MODE_MASK, शून्य, शून्य);
#अघोषित RING_REG

	MMIO_D(PIPEMISC(PIPE_A), D_BDW_PLUS);
	MMIO_D(PIPEMISC(PIPE_B), D_BDW_PLUS);
	MMIO_D(PIPEMISC(PIPE_C), D_BDW_PLUS);
	MMIO_D(_MMIO(0x1c1d0), D_BDW_PLUS);
	MMIO_D(GEN6_MBCUNIT_SNPCR, D_BDW_PLUS);
	MMIO_D(GEN7_MISCCPCTL, D_BDW_PLUS);
	MMIO_D(_MMIO(0x1c054), D_BDW_PLUS);

	MMIO_DH(GEN6_PCODE_MAILBOX, D_BDW_PLUS, शून्य, mailbox_ग_लिखो);

	MMIO_D(GEN8_PRIVATE_PAT_LO, D_BDW_PLUS & ~D_BXT);
	MMIO_D(GEN8_PRIVATE_PAT_HI, D_BDW_PLUS);

	MMIO_D(GAMTARBMODE, D_BDW_PLUS);

#घोषणा RING_REG(base) _MMIO((base) + 0x270)
	MMIO_RING_F(RING_REG, 32, F_CMD_ACCESS, 0, 0, D_BDW_PLUS, शून्य, शून्य);
#अघोषित RING_REG

	MMIO_RING_GM(RING_HWS_PGA, D_BDW_PLUS, शून्य, hws_pga_ग_लिखो);

	MMIO_DFH(HDC_CHICKEN0, D_BDW_PLUS, F_MODE_MASK | F_CMD_ACCESS, शून्य, शून्य);

	MMIO_D(CHICKEN_PIPESL_1(PIPE_A), D_BDW_PLUS);
	MMIO_D(CHICKEN_PIPESL_1(PIPE_B), D_BDW_PLUS);
	MMIO_D(CHICKEN_PIPESL_1(PIPE_C), D_BDW_PLUS);

	MMIO_D(WM_MISC, D_BDW);
	MMIO_D(_MMIO(_SRD_CTL_EDP), D_BDW);

	MMIO_D(_MMIO(0x6671c), D_BDW_PLUS);
	MMIO_D(_MMIO(0x66c00), D_BDW_PLUS);
	MMIO_D(_MMIO(0x66c04), D_BDW_PLUS);

	MMIO_D(HSW_GTT_CACHE_EN, D_BDW_PLUS);

	MMIO_D(GEN8_EU_DISABLE0, D_BDW_PLUS);
	MMIO_D(GEN8_EU_DISABLE1, D_BDW_PLUS);
	MMIO_D(GEN8_EU_DISABLE2, D_BDW_PLUS);

	MMIO_D(_MMIO(0xfdc), D_BDW_PLUS);
	MMIO_DFH(GEN8_ROW_CHICKEN, D_BDW_PLUS, F_MODE_MASK | F_CMD_ACCESS,
		शून्य, शून्य);
	MMIO_DFH(GEN7_ROW_CHICKEN2, D_BDW_PLUS, F_MODE_MASK | F_CMD_ACCESS,
		शून्य, शून्य);
	MMIO_DFH(GEN8_UCGCTL6, D_BDW_PLUS, F_CMD_ACCESS, शून्य, शून्य);

	MMIO_DFH(_MMIO(0xb1f0), D_BDW, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0xb1c0), D_BDW, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(GEN8_L3SQCREG4, D_BDW_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0xb100), D_BDW, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0xb10c), D_BDW, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_D(_MMIO(0xb110), D_BDW);

	MMIO_F(_MMIO(0x24d0), 48, F_CMD_ACCESS | F_CMD_WRITE_PATCH, 0, 0,
		D_BDW_PLUS, शून्य, क्रमce_nonpriv_ग_लिखो);

	MMIO_D(_MMIO(0x44484), D_BDW_PLUS);
	MMIO_D(_MMIO(0x4448c), D_BDW_PLUS);

	MMIO_DFH(_MMIO(0x83a4), D_BDW, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_D(GEN8_L3_LRA_1_GPGPU, D_BDW_PLUS);

	MMIO_DFH(_MMIO(0x8430), D_BDW, F_CMD_ACCESS, शून्य, शून्य);

	MMIO_D(_MMIO(0x110000), D_BDW_PLUS);

	MMIO_D(_MMIO(0x48400), D_BDW_PLUS);

	MMIO_D(_MMIO(0x6e570), D_BDW_PLUS);
	MMIO_D(_MMIO(0x65f10), D_BDW_PLUS);

	MMIO_DFH(_MMIO(0xe194), D_BDW_PLUS, F_MODE_MASK | F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0xe188), D_BDW_PLUS, F_MODE_MASK | F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(HALF_SLICE_CHICKEN2, D_BDW_PLUS, F_MODE_MASK | F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x2580), D_BDW_PLUS, F_MODE_MASK | F_CMD_ACCESS, शून्य, शून्य);

	MMIO_DFH(_MMIO(0x2248), D_BDW, F_CMD_ACCESS, शून्य, शून्य);

	MMIO_DFH(_MMIO(0xe220), D_BDW_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0xe230), D_BDW_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0xe240), D_BDW_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0xe260), D_BDW_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0xe270), D_BDW_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0xe280), D_BDW_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0xe2a0), D_BDW_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0xe2b0), D_BDW_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0xe2c0), D_BDW_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x21f0), D_BDW_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक init_skl_mmio_info(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा drm_i915_निजी *dev_priv = gvt->gt->i915;
	पूर्णांक ret;

	MMIO_DH(FORCEWAKE_RENDER_GEN9, D_SKL_PLUS, शून्य, mul_क्रमce_wake_ग_लिखो);
	MMIO_DH(FORCEWAKE_ACK_RENDER_GEN9, D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(FORCEWAKE_GT_GEN9, D_SKL_PLUS, शून्य, mul_क्रमce_wake_ग_लिखो);
	MMIO_DH(FORCEWAKE_ACK_GT_GEN9, D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(FORCEWAKE_MEDIA_GEN9, D_SKL_PLUS, शून्य, mul_क्रमce_wake_ग_लिखो);
	MMIO_DH(FORCEWAKE_ACK_MEDIA_GEN9, D_SKL_PLUS, शून्य, शून्य);

	MMIO_F(DP_AUX_CH_CTL(AUX_CH_B), 6 * 4, 0, 0, 0, D_SKL_PLUS, शून्य,
						dp_aux_ch_ctl_mmio_ग_लिखो);
	MMIO_F(DP_AUX_CH_CTL(AUX_CH_C), 6 * 4, 0, 0, 0, D_SKL_PLUS, शून्य,
						dp_aux_ch_ctl_mmio_ग_लिखो);
	MMIO_F(DP_AUX_CH_CTL(AUX_CH_D), 6 * 4, 0, 0, 0, D_SKL_PLUS, शून्य,
						dp_aux_ch_ctl_mmio_ग_लिखो);

	MMIO_D(HSW_PWR_WELL_CTL1, D_SKL_PLUS);
	MMIO_DH(HSW_PWR_WELL_CTL2, D_SKL_PLUS, शून्य, skl_घातer_well_ctl_ग_लिखो);

	MMIO_DH(DBUF_CTL_S(0), D_SKL_PLUS, शून्य, gen9_dbuf_ctl_mmio_ग_लिखो);

	MMIO_D(GEN9_PG_ENABLE, D_SKL_PLUS);
	MMIO_D(GEN9_MEDIA_PG_IDLE_HYSTERESIS, D_SKL_PLUS);
	MMIO_D(GEN9_RENDER_PG_IDLE_HYSTERESIS, D_SKL_PLUS);
	MMIO_DFH(GEN9_GAMT_ECO_REG_RW_IA, D_SKL_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(MMCD_MISC_CTRL, D_SKL_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DH(CHICKEN_PAR1_1, D_SKL_PLUS, शून्य, शून्य);
	MMIO_D(DC_STATE_EN, D_SKL_PLUS);
	MMIO_D(DC_STATE_DEBUG, D_SKL_PLUS);
	MMIO_D(CDCLK_CTL, D_SKL_PLUS);
	MMIO_DH(LCPLL1_CTL, D_SKL_PLUS, शून्य, skl_lcpll_ग_लिखो);
	MMIO_DH(LCPLL2_CTL, D_SKL_PLUS, शून्य, skl_lcpll_ग_लिखो);
	MMIO_D(_MMIO(_DPLL1_CFGCR1), D_SKL_PLUS);
	MMIO_D(_MMIO(_DPLL2_CFGCR1), D_SKL_PLUS);
	MMIO_D(_MMIO(_DPLL3_CFGCR1), D_SKL_PLUS);
	MMIO_D(_MMIO(_DPLL1_CFGCR2), D_SKL_PLUS);
	MMIO_D(_MMIO(_DPLL2_CFGCR2), D_SKL_PLUS);
	MMIO_D(_MMIO(_DPLL3_CFGCR2), D_SKL_PLUS);
	MMIO_D(DPLL_CTRL1, D_SKL_PLUS);
	MMIO_D(DPLL_CTRL2, D_SKL_PLUS);
	MMIO_DH(DPLL_STATUS, D_SKL_PLUS, dpll_status_पढ़ो, शून्य);

	MMIO_DH(SKL_PS_WIN_POS(PIPE_A, 0), D_SKL_PLUS, शून्य, pf_ग_लिखो);
	MMIO_DH(SKL_PS_WIN_POS(PIPE_A, 1), D_SKL_PLUS, शून्य, pf_ग_लिखो);
	MMIO_DH(SKL_PS_WIN_POS(PIPE_B, 0), D_SKL_PLUS, शून्य, pf_ग_लिखो);
	MMIO_DH(SKL_PS_WIN_POS(PIPE_B, 1), D_SKL_PLUS, शून्य, pf_ग_लिखो);
	MMIO_DH(SKL_PS_WIN_POS(PIPE_C, 0), D_SKL_PLUS, शून्य, pf_ग_लिखो);
	MMIO_DH(SKL_PS_WIN_POS(PIPE_C, 1), D_SKL_PLUS, शून्य, pf_ग_लिखो);

	MMIO_DH(SKL_PS_WIN_SZ(PIPE_A, 0), D_SKL_PLUS, शून्य, pf_ग_लिखो);
	MMIO_DH(SKL_PS_WIN_SZ(PIPE_A, 1), D_SKL_PLUS, शून्य, pf_ग_लिखो);
	MMIO_DH(SKL_PS_WIN_SZ(PIPE_B, 0), D_SKL_PLUS, शून्य, pf_ग_लिखो);
	MMIO_DH(SKL_PS_WIN_SZ(PIPE_B, 1), D_SKL_PLUS, शून्य, pf_ग_लिखो);
	MMIO_DH(SKL_PS_WIN_SZ(PIPE_C, 0), D_SKL_PLUS, शून्य, pf_ग_लिखो);
	MMIO_DH(SKL_PS_WIN_SZ(PIPE_C, 1), D_SKL_PLUS, शून्य, pf_ग_लिखो);

	MMIO_DH(SKL_PS_CTRL(PIPE_A, 0), D_SKL_PLUS, शून्य, pf_ग_लिखो);
	MMIO_DH(SKL_PS_CTRL(PIPE_A, 1), D_SKL_PLUS, शून्य, pf_ग_लिखो);
	MMIO_DH(SKL_PS_CTRL(PIPE_B, 0), D_SKL_PLUS, शून्य, pf_ग_लिखो);
	MMIO_DH(SKL_PS_CTRL(PIPE_B, 1), D_SKL_PLUS, शून्य, pf_ग_लिखो);
	MMIO_DH(SKL_PS_CTRL(PIPE_C, 0), D_SKL_PLUS, शून्य, pf_ग_लिखो);
	MMIO_DH(SKL_PS_CTRL(PIPE_C, 1), D_SKL_PLUS, शून्य, pf_ग_लिखो);

	MMIO_DH(PLANE_BUF_CFG(PIPE_A, 0), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_BUF_CFG(PIPE_A, 1), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_BUF_CFG(PIPE_A, 2), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_BUF_CFG(PIPE_A, 3), D_SKL_PLUS, शून्य, शून्य);

	MMIO_DH(PLANE_BUF_CFG(PIPE_B, 0), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_BUF_CFG(PIPE_B, 1), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_BUF_CFG(PIPE_B, 2), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_BUF_CFG(PIPE_B, 3), D_SKL_PLUS, शून्य, शून्य);

	MMIO_DH(PLANE_BUF_CFG(PIPE_C, 0), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_BUF_CFG(PIPE_C, 1), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_BUF_CFG(PIPE_C, 2), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_BUF_CFG(PIPE_C, 3), D_SKL_PLUS, शून्य, शून्य);

	MMIO_DH(CUR_BUF_CFG(PIPE_A), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(CUR_BUF_CFG(PIPE_B), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(CUR_BUF_CFG(PIPE_C), D_SKL_PLUS, शून्य, शून्य);

	MMIO_F(PLANE_WM(PIPE_A, 0, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, शून्य, शून्य);
	MMIO_F(PLANE_WM(PIPE_A, 1, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, शून्य, शून्य);
	MMIO_F(PLANE_WM(PIPE_A, 2, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, शून्य, शून्य);

	MMIO_F(PLANE_WM(PIPE_B, 0, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, शून्य, शून्य);
	MMIO_F(PLANE_WM(PIPE_B, 1, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, शून्य, शून्य);
	MMIO_F(PLANE_WM(PIPE_B, 2, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, शून्य, शून्य);

	MMIO_F(PLANE_WM(PIPE_C, 0, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, शून्य, शून्य);
	MMIO_F(PLANE_WM(PIPE_C, 1, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, शून्य, शून्य);
	MMIO_F(PLANE_WM(PIPE_C, 2, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, शून्य, शून्य);

	MMIO_F(CUR_WM(PIPE_A, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, शून्य, शून्य);
	MMIO_F(CUR_WM(PIPE_B, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, शून्य, शून्य);
	MMIO_F(CUR_WM(PIPE_C, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, शून्य, शून्य);

	MMIO_DH(PLANE_WM_TRANS(PIPE_A, 0), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_WM_TRANS(PIPE_A, 1), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_WM_TRANS(PIPE_A, 2), D_SKL_PLUS, शून्य, शून्य);

	MMIO_DH(PLANE_WM_TRANS(PIPE_B, 0), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_WM_TRANS(PIPE_B, 1), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_WM_TRANS(PIPE_B, 2), D_SKL_PLUS, शून्य, शून्य);

	MMIO_DH(PLANE_WM_TRANS(PIPE_C, 0), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_WM_TRANS(PIPE_C, 1), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_WM_TRANS(PIPE_C, 2), D_SKL_PLUS, शून्य, शून्य);

	MMIO_DH(CUR_WM_TRANS(PIPE_A), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(CUR_WM_TRANS(PIPE_B), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(CUR_WM_TRANS(PIPE_C), D_SKL_PLUS, शून्य, शून्य);

	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_A, 0), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_A, 1), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_A, 2), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_A, 3), D_SKL_PLUS, शून्य, शून्य);

	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_B, 0), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_B, 1), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_B, 2), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_B, 3), D_SKL_PLUS, शून्य, शून्य);

	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_C, 0), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_C, 1), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_C, 2), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_C, 3), D_SKL_PLUS, शून्य, शून्य);

	MMIO_DH(_MMIO(_REG_701C0(PIPE_A, 1)), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(_MMIO(_REG_701C0(PIPE_A, 2)), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(_MMIO(_REG_701C0(PIPE_A, 3)), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(_MMIO(_REG_701C0(PIPE_A, 4)), D_SKL_PLUS, शून्य, शून्य);

	MMIO_DH(_MMIO(_REG_701C0(PIPE_B, 1)), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(_MMIO(_REG_701C0(PIPE_B, 2)), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(_MMIO(_REG_701C0(PIPE_B, 3)), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(_MMIO(_REG_701C0(PIPE_B, 4)), D_SKL_PLUS, शून्य, शून्य);

	MMIO_DH(_MMIO(_REG_701C0(PIPE_C, 1)), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(_MMIO(_REG_701C0(PIPE_C, 2)), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(_MMIO(_REG_701C0(PIPE_C, 3)), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(_MMIO(_REG_701C0(PIPE_C, 4)), D_SKL_PLUS, शून्य, शून्य);

	MMIO_DH(_MMIO(_REG_701C4(PIPE_A, 1)), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(_MMIO(_REG_701C4(PIPE_A, 2)), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(_MMIO(_REG_701C4(PIPE_A, 3)), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(_MMIO(_REG_701C4(PIPE_A, 4)), D_SKL_PLUS, शून्य, शून्य);

	MMIO_DH(_MMIO(_REG_701C4(PIPE_B, 1)), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(_MMIO(_REG_701C4(PIPE_B, 2)), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(_MMIO(_REG_701C4(PIPE_B, 3)), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(_MMIO(_REG_701C4(PIPE_B, 4)), D_SKL_PLUS, शून्य, शून्य);

	MMIO_DH(_MMIO(_REG_701C4(PIPE_C, 1)), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(_MMIO(_REG_701C4(PIPE_C, 2)), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(_MMIO(_REG_701C4(PIPE_C, 3)), D_SKL_PLUS, शून्य, शून्य);
	MMIO_DH(_MMIO(_REG_701C4(PIPE_C, 4)), D_SKL_PLUS, शून्य, शून्य);

	MMIO_D(_MMIO(_PLANE_CTL_3_A), D_SKL_PLUS);
	MMIO_D(_MMIO(_PLANE_CTL_3_B), D_SKL_PLUS);
	MMIO_D(_MMIO(0x72380), D_SKL_PLUS);
	MMIO_D(_MMIO(0x7239c), D_SKL_PLUS);
	MMIO_D(_MMIO(_PLANE_SURF_3_A), D_SKL_PLUS);
	MMIO_D(_MMIO(_PLANE_SURF_3_B), D_SKL_PLUS);

	MMIO_D(CSR_SSP_BASE, D_SKL_PLUS);
	MMIO_D(CSR_HTP_SKL, D_SKL_PLUS);
	MMIO_D(CSR_LAST_WRITE, D_SKL_PLUS);

	MMIO_DFH(BDW_SCRATCH1, D_SKL_PLUS, F_CMD_ACCESS, शून्य, शून्य);

	MMIO_D(SKL_DFSM, D_SKL_PLUS);
	MMIO_D(DISPIO_CR_TX_BMU_CR0, D_SKL_PLUS);

	MMIO_F(GEN9_GFX_MOCS(0), 0x7f8, F_CMD_ACCESS, 0, 0, D_SKL_PLUS,
		शून्य, शून्य);
	MMIO_F(GEN7_L3CNTLREG2, 0x80, F_CMD_ACCESS, 0, 0, D_SKL_PLUS,
		शून्य, शून्य);

	MMIO_D(RPM_CONFIG0, D_SKL_PLUS);
	MMIO_D(_MMIO(0xd08), D_SKL_PLUS);
	MMIO_D(RC6_LOCATION, D_SKL_PLUS);
	MMIO_DFH(GEN7_FF_SLICE_CS_CHICKEN1, D_SKL_PLUS,
		 F_MODE_MASK | F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(GEN9_CS_DEBUG_MODE1, D_SKL_PLUS, F_MODE_MASK | F_CMD_ACCESS,
		शून्य, शून्य);

	/* TRTT */
	MMIO_DFH(TRVATTL3PTRDW(0), D_SKL_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(TRVATTL3PTRDW(1), D_SKL_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(TRVATTL3PTRDW(2), D_SKL_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(TRVATTL3PTRDW(3), D_SKL_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(TRVADR, D_SKL_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(TRTTE, D_SKL_PLUS, F_CMD_ACCESS | F_PM_SAVE,
		 शून्य, gen9_trtte_ग_लिखो);
	MMIO_DFH(_MMIO(0x4dfc), D_SKL_PLUS, F_PM_SAVE,
		 शून्य, gen9_trtt_chicken_ग_लिखो);

	MMIO_D(_MMIO(0x46430), D_SKL_PLUS);

	MMIO_D(_MMIO(0x46520), D_SKL_PLUS);

	MMIO_D(_MMIO(0xc403c), D_SKL_PLUS);
	MMIO_DFH(GEN8_GARBCNTL, D_SKL_PLUS, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DH(DMA_CTRL, D_SKL_PLUS, शून्य, dma_ctrl_ग_लिखो);

	MMIO_D(_MMIO(0x65900), D_SKL_PLUS);
	MMIO_D(GEN6_STOLEN_RESERVED, D_SKL_PLUS);
	MMIO_D(_MMIO(0x4068), D_SKL_PLUS);
	MMIO_D(_MMIO(0x67054), D_SKL_PLUS);
	MMIO_D(_MMIO(0x6e560), D_SKL_PLUS);
	MMIO_D(_MMIO(0x6e554), D_SKL_PLUS);
	MMIO_D(_MMIO(0x2b20), D_SKL_PLUS);
	MMIO_D(_MMIO(0x65f00), D_SKL_PLUS);
	MMIO_D(_MMIO(0x65f08), D_SKL_PLUS);
	MMIO_D(_MMIO(0x320f0), D_SKL_PLUS);

	MMIO_D(_MMIO(0x70034), D_SKL_PLUS);
	MMIO_D(_MMIO(0x71034), D_SKL_PLUS);
	MMIO_D(_MMIO(0x72034), D_SKL_PLUS);

	MMIO_D(_MMIO(_PLANE_KEYVAL_1(PIPE_A)), D_SKL_PLUS);
	MMIO_D(_MMIO(_PLANE_KEYVAL_1(PIPE_B)), D_SKL_PLUS);
	MMIO_D(_MMIO(_PLANE_KEYVAL_1(PIPE_C)), D_SKL_PLUS);
	MMIO_D(_MMIO(_PLANE_KEYMAX_1(PIPE_A)), D_SKL_PLUS);
	MMIO_D(_MMIO(_PLANE_KEYMAX_1(PIPE_B)), D_SKL_PLUS);
	MMIO_D(_MMIO(_PLANE_KEYMAX_1(PIPE_C)), D_SKL_PLUS);
	MMIO_D(_MMIO(_PLANE_KEYMSK_1(PIPE_A)), D_SKL_PLUS);
	MMIO_D(_MMIO(_PLANE_KEYMSK_1(PIPE_B)), D_SKL_PLUS);
	MMIO_D(_MMIO(_PLANE_KEYMSK_1(PIPE_C)), D_SKL_PLUS);

	MMIO_D(_MMIO(0x44500), D_SKL_PLUS);
#घोषणा CSFE_CHICKEN1_REG(base) _MMIO((base) + 0xD4)
	MMIO_RING_DFH(CSFE_CHICKEN1_REG, D_SKL_PLUS, F_MODE_MASK | F_CMD_ACCESS,
		      शून्य, csfe_chicken1_mmio_ग_लिखो);
#अघोषित CSFE_CHICKEN1_REG
	MMIO_DFH(GEN8_HDC_CHICKEN1, D_SKL_PLUS, F_MODE_MASK | F_CMD_ACCESS,
		 शून्य, शून्य);
	MMIO_DFH(GEN9_WM_CHICKEN3, D_SKL_PLUS, F_MODE_MASK | F_CMD_ACCESS,
		 शून्य, शून्य);

	MMIO_DFH(GAMT_CHKN_BIT_REG, D_KBL | D_CFL, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_D(GEN9_CTX_PREEMPT_REG, D_SKL_PLUS & ~D_BXT);

	वापस 0;
पूर्ण

अटल पूर्णांक init_bxt_mmio_info(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा drm_i915_निजी *dev_priv = gvt->gt->i915;
	पूर्णांक ret;

	MMIO_F(_MMIO(0x80000), 0x3000, 0, 0, 0, D_BXT, शून्य, शून्य);

	MMIO_D(GEN7_SAMPLER_INSTDONE, D_BXT);
	MMIO_D(GEN7_ROW_INSTDONE, D_BXT);
	MMIO_D(GEN8_FAULT_TLB_DATA0, D_BXT);
	MMIO_D(GEN8_FAULT_TLB_DATA1, D_BXT);
	MMIO_D(ERROR_GEN6, D_BXT);
	MMIO_D(DONE_REG, D_BXT);
	MMIO_D(EIR, D_BXT);
	MMIO_D(PGTBL_ER, D_BXT);
	MMIO_D(_MMIO(0x4194), D_BXT);
	MMIO_D(_MMIO(0x4294), D_BXT);
	MMIO_D(_MMIO(0x4494), D_BXT);

	MMIO_RING_D(RING_PSMI_CTL, D_BXT);
	MMIO_RING_D(RING_DMA_FADD, D_BXT);
	MMIO_RING_D(RING_DMA_FADD_UDW, D_BXT);
	MMIO_RING_D(RING_IPEHR, D_BXT);
	MMIO_RING_D(RING_INSTPS, D_BXT);
	MMIO_RING_D(RING_BBADDR_UDW, D_BXT);
	MMIO_RING_D(RING_BBSTATE, D_BXT);
	MMIO_RING_D(RING_IPEIR, D_BXT);

	MMIO_F(SOFT_SCRATCH(0), 16 * 4, 0, 0, 0, D_BXT, शून्य, शून्य);

	MMIO_DH(BXT_P_CR_GT_DISP_PWRON, D_BXT, शून्य, bxt_gt_disp_pwron_ग_लिखो);
	MMIO_D(BXT_RP_STATE_CAP, D_BXT);
	MMIO_DH(BXT_PHY_CTL_FAMILY(DPIO_PHY0), D_BXT,
		शून्य, bxt_phy_ctl_family_ग_लिखो);
	MMIO_DH(BXT_PHY_CTL_FAMILY(DPIO_PHY1), D_BXT,
		शून्य, bxt_phy_ctl_family_ग_लिखो);
	MMIO_D(BXT_PHY_CTL(PORT_A), D_BXT);
	MMIO_D(BXT_PHY_CTL(PORT_B), D_BXT);
	MMIO_D(BXT_PHY_CTL(PORT_C), D_BXT);
	MMIO_DH(BXT_PORT_PLL_ENABLE(PORT_A), D_BXT,
		शून्य, bxt_port_pll_enable_ग_लिखो);
	MMIO_DH(BXT_PORT_PLL_ENABLE(PORT_B), D_BXT,
		शून्य, bxt_port_pll_enable_ग_लिखो);
	MMIO_DH(BXT_PORT_PLL_ENABLE(PORT_C), D_BXT, शून्य,
		bxt_port_pll_enable_ग_लिखो);

	MMIO_D(BXT_PORT_CL1CM_DW0(DPIO_PHY0), D_BXT);
	MMIO_D(BXT_PORT_CL1CM_DW9(DPIO_PHY0), D_BXT);
	MMIO_D(BXT_PORT_CL1CM_DW10(DPIO_PHY0), D_BXT);
	MMIO_D(BXT_PORT_CL1CM_DW28(DPIO_PHY0), D_BXT);
	MMIO_D(BXT_PORT_CL1CM_DW30(DPIO_PHY0), D_BXT);
	MMIO_D(BXT_PORT_CL2CM_DW6(DPIO_PHY0), D_BXT);
	MMIO_D(BXT_PORT_REF_DW3(DPIO_PHY0), D_BXT);
	MMIO_D(BXT_PORT_REF_DW6(DPIO_PHY0), D_BXT);
	MMIO_D(BXT_PORT_REF_DW8(DPIO_PHY0), D_BXT);

	MMIO_D(BXT_PORT_CL1CM_DW0(DPIO_PHY1), D_BXT);
	MMIO_D(BXT_PORT_CL1CM_DW9(DPIO_PHY1), D_BXT);
	MMIO_D(BXT_PORT_CL1CM_DW10(DPIO_PHY1), D_BXT);
	MMIO_D(BXT_PORT_CL1CM_DW28(DPIO_PHY1), D_BXT);
	MMIO_D(BXT_PORT_CL1CM_DW30(DPIO_PHY1), D_BXT);
	MMIO_D(BXT_PORT_CL2CM_DW6(DPIO_PHY1), D_BXT);
	MMIO_D(BXT_PORT_REF_DW3(DPIO_PHY1), D_BXT);
	MMIO_D(BXT_PORT_REF_DW6(DPIO_PHY1), D_BXT);
	MMIO_D(BXT_PORT_REF_DW8(DPIO_PHY1), D_BXT);

	MMIO_D(BXT_PORT_PLL_EBB_0(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_PLL_EBB_4(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW10_LN01(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW10_GRP(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW12_LN01(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW12_LN23(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_DH(BXT_PORT_PCS_DW12_GRP(DPIO_PHY0, DPIO_CH0), D_BXT,
		शून्य, bxt_pcs_dw12_grp_ग_लिखो);
	MMIO_D(BXT_PORT_TX_DW2_LN0(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW2_GRP(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_DH(BXT_PORT_TX_DW3_LN0(DPIO_PHY0, DPIO_CH0), D_BXT,
		bxt_port_tx_dw3_पढ़ो, शून्य);
	MMIO_D(BXT_PORT_TX_DW3_GRP(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW4_LN0(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW4_GRP(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY0, DPIO_CH0, 0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY0, DPIO_CH0, 1), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY0, DPIO_CH0, 2), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY0, DPIO_CH0, 3), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH0, 0), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH0, 1), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH0, 2), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH0, 3), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH0, 6), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH0, 8), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH0, 9), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH0, 10), D_BXT);

	MMIO_D(BXT_PORT_PLL_EBB_0(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_D(BXT_PORT_PLL_EBB_4(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW10_LN01(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW10_GRP(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW12_LN01(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW12_LN23(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_DH(BXT_PORT_PCS_DW12_GRP(DPIO_PHY0, DPIO_CH1), D_BXT,
		शून्य, bxt_pcs_dw12_grp_ग_लिखो);
	MMIO_D(BXT_PORT_TX_DW2_LN0(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_D(BXT_PORT_TX_DW2_GRP(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_DH(BXT_PORT_TX_DW3_LN0(DPIO_PHY0, DPIO_CH1), D_BXT,
		bxt_port_tx_dw3_पढ़ो, शून्य);
	MMIO_D(BXT_PORT_TX_DW3_GRP(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_D(BXT_PORT_TX_DW4_LN0(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_D(BXT_PORT_TX_DW4_GRP(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY0, DPIO_CH1, 0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY0, DPIO_CH1, 1), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY0, DPIO_CH1, 2), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY0, DPIO_CH1, 3), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH1, 0), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH1, 1), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH1, 2), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH1, 3), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH1, 6), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH1, 8), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH1, 9), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH1, 10), D_BXT);

	MMIO_D(BXT_PORT_PLL_EBB_0(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_PLL_EBB_4(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW10_LN01(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW10_GRP(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW12_LN01(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW12_LN23(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_DH(BXT_PORT_PCS_DW12_GRP(DPIO_PHY1, DPIO_CH0), D_BXT,
		शून्य, bxt_pcs_dw12_grp_ग_लिखो);
	MMIO_D(BXT_PORT_TX_DW2_LN0(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW2_GRP(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_DH(BXT_PORT_TX_DW3_LN0(DPIO_PHY1, DPIO_CH0), D_BXT,
		bxt_port_tx_dw3_पढ़ो, शून्य);
	MMIO_D(BXT_PORT_TX_DW3_GRP(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW4_LN0(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW4_GRP(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY1, DPIO_CH0, 0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY1, DPIO_CH0, 1), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY1, DPIO_CH0, 2), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY1, DPIO_CH0, 3), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY1, DPIO_CH0, 0), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY1, DPIO_CH0, 1), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY1, DPIO_CH0, 2), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY1, DPIO_CH0, 3), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY1, DPIO_CH0, 6), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY1, DPIO_CH0, 8), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY1, DPIO_CH0, 9), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY1, DPIO_CH0, 10), D_BXT);

	MMIO_D(BXT_DE_PLL_CTL, D_BXT);
	MMIO_DH(BXT_DE_PLL_ENABLE, D_BXT, शून्य, bxt_de_pll_enable_ग_लिखो);
	MMIO_D(BXT_DSI_PLL_CTL, D_BXT);
	MMIO_D(BXT_DSI_PLL_ENABLE, D_BXT);

	MMIO_D(GEN9_CLKGATE_DIS_0, D_BXT);
	MMIO_D(GEN9_CLKGATE_DIS_4, D_BXT);

	MMIO_D(HSW_TVIDEO_DIP_GCP(TRANSCODER_A), D_BXT);
	MMIO_D(HSW_TVIDEO_DIP_GCP(TRANSCODER_B), D_BXT);
	MMIO_D(HSW_TVIDEO_DIP_GCP(TRANSCODER_C), D_BXT);

	MMIO_D(RC6_CTX_BASE, D_BXT);

	MMIO_D(GEN8_PUSHBUS_CONTROL, D_BXT);
	MMIO_D(GEN8_PUSHBUS_ENABLE, D_BXT);
	MMIO_D(GEN8_PUSHBUS_SHIFT, D_BXT);
	MMIO_D(GEN6_GFXPAUSE, D_BXT);
	MMIO_DFH(GEN8_L3SQCREG1, D_BXT, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(GEN8_L3CNTLREG, D_BXT, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_DFH(_MMIO(0x20D8), D_BXT, F_CMD_ACCESS, शून्य, शून्य);
	MMIO_F(GEN8_RING_CS_GPR(RENDER_RING_BASE, 0), 0x40, F_CMD_ACCESS,
	       0, 0, D_BXT, शून्य, शून्य);
	MMIO_F(GEN8_RING_CS_GPR(GEN6_BSD_RING_BASE, 0), 0x40, F_CMD_ACCESS,
	       0, 0, D_BXT, शून्य, शून्य);
	MMIO_F(GEN8_RING_CS_GPR(BLT_RING_BASE, 0), 0x40, F_CMD_ACCESS,
	       0, 0, D_BXT, शून्य, शून्य);
	MMIO_F(GEN8_RING_CS_GPR(VEBOX_RING_BASE, 0), 0x40, F_CMD_ACCESS,
	       0, 0, D_BXT, शून्य, शून्य);

	MMIO_DFH(GEN9_CTX_PREEMPT_REG, D_BXT, F_CMD_ACCESS, शून्य, शून्य);

	MMIO_DH(GEN8_PRIVATE_PAT_LO, D_BXT, शून्य, bxt_ppat_low_ग_लिखो);

	वापस 0;
पूर्ण

अटल काष्ठा gvt_mmio_block *find_mmio_block(काष्ठा पूर्णांकel_gvt *gvt,
					      अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित दीर्घ device = पूर्णांकel_gvt_get_device_type(gvt);
	काष्ठा gvt_mmio_block *block = gvt->mmio.mmio_block;
	पूर्णांक num = gvt->mmio.num_mmio_block;
	पूर्णांक i;

	क्रम (i = 0; i < num; i++, block++) अणु
		अगर (!(device & block->device))
			जारी;
		अगर (offset >= i915_mmio_reg_offset(block->offset) &&
		    offset < i915_mmio_reg_offset(block->offset) + block->size)
			वापस block;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * पूर्णांकel_gvt_clean_mmio_info - clean up MMIO inक्रमmation table क्रम GVT device
 * @gvt: GVT device
 *
 * This function is called at the driver unloading stage, to clean up the MMIO
 * inक्रमmation table of GVT device
 *
 */
व्योम पूर्णांकel_gvt_clean_mmio_info(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा hlist_node *पंचांगp;
	काष्ठा पूर्णांकel_gvt_mmio_info *e;
	पूर्णांक i;

	hash_क्रम_each_safe(gvt->mmio.mmio_info_table, i, पंचांगp, e, node)
		kमुक्त(e);

	vमुक्त(gvt->mmio.mmio_attribute);
	gvt->mmio.mmio_attribute = शून्य;
पूर्ण

/* Special MMIO blocks. रेजिस्टरs in MMIO block ranges should not be command
 * accessible (should have no F_CMD_ACCESS flag).
 * otherwise, need to update cmd_reg_handler in cmd_parser.c
 */
अटल काष्ठा gvt_mmio_block mmio_blocks[] = अणु
	अणुD_SKL_PLUS, _MMIO(CSR_MMIO_START_RANGE), 0x3000, शून्य, शून्यपूर्ण,
	अणुD_ALL, _MMIO(MCHBAR_MIRROR_BASE_SNB), 0x40000, शून्य, शून्यपूर्ण,
	अणुD_ALL, _MMIO(VGT_PVINFO_PAGE), VGT_PVINFO_SIZE,
		pvinfo_mmio_पढ़ो, pvinfo_mmio_ग_लिखोपूर्ण,
	अणुD_ALL, LGC_PALETTE(PIPE_A, 0), 1024, शून्य, शून्यपूर्ण,
	अणुD_ALL, LGC_PALETTE(PIPE_B, 0), 1024, शून्य, शून्यपूर्ण,
	अणुD_ALL, LGC_PALETTE(PIPE_C, 0), 1024, शून्य, शून्यपूर्ण,
पूर्ण;

/**
 * पूर्णांकel_gvt_setup_mmio_info - setup MMIO inक्रमmation table क्रम GVT device
 * @gvt: GVT device
 *
 * This function is called at the initialization stage, to setup the MMIO
 * inक्रमmation table क्रम GVT device
 *
 * Returns:
 * zero on success, negative अगर failed.
 */
पूर्णांक पूर्णांकel_gvt_setup_mmio_info(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा पूर्णांकel_gvt_device_info *info = &gvt->device_info;
	काष्ठा drm_i915_निजी *i915 = gvt->gt->i915;
	पूर्णांक size = info->mmio_size / 4 * माप(*gvt->mmio.mmio_attribute);
	पूर्णांक ret;

	gvt->mmio.mmio_attribute = vzalloc(size);
	अगर (!gvt->mmio.mmio_attribute)
		वापस -ENOMEM;

	ret = init_generic_mmio_info(gvt);
	अगर (ret)
		जाओ err;

	अगर (IS_BROADWELL(i915)) अणु
		ret = init_bdw_mmio_info(gvt);
		अगर (ret)
			जाओ err;
	पूर्ण अन्यथा अगर (IS_SKYLAKE(i915) ||
		   IS_KABYLAKE(i915) ||
		   IS_COFFEELAKE(i915) ||
		   IS_COMETLAKE(i915)) अणु
		ret = init_bdw_mmio_info(gvt);
		अगर (ret)
			जाओ err;
		ret = init_skl_mmio_info(gvt);
		अगर (ret)
			जाओ err;
	पूर्ण अन्यथा अगर (IS_BROXTON(i915)) अणु
		ret = init_bdw_mmio_info(gvt);
		अगर (ret)
			जाओ err;
		ret = init_skl_mmio_info(gvt);
		अगर (ret)
			जाओ err;
		ret = init_bxt_mmio_info(gvt);
		अगर (ret)
			जाओ err;
	पूर्ण

	gvt->mmio.mmio_block = mmio_blocks;
	gvt->mmio.num_mmio_block = ARRAY_SIZE(mmio_blocks);

	वापस 0;
err:
	पूर्णांकel_gvt_clean_mmio_info(gvt);
	वापस ret;
पूर्ण

/**
 * पूर्णांकel_gvt_क्रम_each_tracked_mmio - iterate each tracked mmio
 * @gvt: a GVT device
 * @handler: the handler
 * @data: निजी data given to handler
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
पूर्णांक पूर्णांकel_gvt_क्रम_each_tracked_mmio(काष्ठा पूर्णांकel_gvt *gvt,
	पूर्णांक (*handler)(काष्ठा पूर्णांकel_gvt *gvt, u32 offset, व्योम *data),
	व्योम *data)
अणु
	काष्ठा gvt_mmio_block *block = gvt->mmio.mmio_block;
	काष्ठा पूर्णांकel_gvt_mmio_info *e;
	पूर्णांक i, j, ret;

	hash_क्रम_each(gvt->mmio.mmio_info_table, i, e, node) अणु
		ret = handler(gvt, e->offset, data);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < gvt->mmio.num_mmio_block; i++, block++) अणु
		/* pvinfo data करोesn't come from hw mmio */
		अगर (i915_mmio_reg_offset(block->offset) == VGT_PVINFO_PAGE)
			जारी;

		क्रम (j = 0; j < block->size; j += 4) अणु
			ret = handler(gvt,
				      i915_mmio_reg_offset(block->offset) + j,
				      data);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * पूर्णांकel_vgpu_शेष_mmio_पढ़ो - शेष MMIO पढ़ो handler
 * @vgpu: a vGPU
 * @offset: access offset
 * @p_data: data वापस buffer
 * @bytes: access data length
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_शेष_mmio_पढ़ो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	पढ़ो_vreg(vgpu, offset, p_data, bytes);
	वापस 0;
पूर्ण

/**
 * पूर्णांकel_t_शेष_mmio_ग_लिखो - शेष MMIO ग_लिखो handler
 * @vgpu: a vGPU
 * @offset: access offset
 * @p_data: ग_लिखो data buffer
 * @bytes: access data length
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_शेष_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	ग_लिखो_vreg(vgpu, offset, p_data, bytes);
	वापस 0;
पूर्ण

/**
 * पूर्णांकel_vgpu_mask_mmio_ग_लिखो - ग_लिखो mask रेजिस्टर
 * @vgpu: a vGPU
 * @offset: access offset
 * @p_data: ग_लिखो data buffer
 * @bytes: access data length
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_mask_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	u32 mask, old_vreg;

	old_vreg = vgpu_vreg(vgpu, offset);
	ग_लिखो_vreg(vgpu, offset, p_data, bytes);
	mask = vgpu_vreg(vgpu, offset) >> 16;
	vgpu_vreg(vgpu, offset) = (old_vreg & ~mask) |
				(vgpu_vreg(vgpu, offset) & mask);

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_gvt_in_क्रमce_nonpriv_whitelist - अगर a mmio is in whitelist to be
 * क्रमce-nopriv रेजिस्टर
 *
 * @gvt: a GVT device
 * @offset: रेजिस्टर offset
 *
 * Returns:
 * True अगर the रेजिस्टर is in क्रमce-nonpriv whitelist;
 * False अगर outside;
 */
bool पूर्णांकel_gvt_in_क्रमce_nonpriv_whitelist(काष्ठा पूर्णांकel_gvt *gvt,
					  अचिन्हित पूर्णांक offset)
अणु
	वापस in_whitelist(offset);
पूर्ण

/**
 * पूर्णांकel_vgpu_mmio_reg_rw - emulate tracked mmio रेजिस्टरs
 * @vgpu: a vGPU
 * @offset: रेजिस्टर offset
 * @pdata: data buffer
 * @bytes: data length
 * @is_पढ़ो: पढ़ो or ग_लिखो
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_mmio_reg_rw(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
			   व्योम *pdata, अचिन्हित पूर्णांक bytes, bool is_पढ़ो)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा पूर्णांकel_gvt_mmio_info *mmio_info;
	काष्ठा gvt_mmio_block *mmio_block;
	gvt_mmio_func func;
	पूर्णांक ret;

	अगर (drm_WARN_ON(&i915->drm, bytes > 8))
		वापस -EINVAL;

	/*
	 * Handle special MMIO blocks.
	 */
	mmio_block = find_mmio_block(gvt, offset);
	अगर (mmio_block) अणु
		func = is_पढ़ो ? mmio_block->पढ़ो : mmio_block->ग_लिखो;
		अगर (func)
			वापस func(vgpu, offset, pdata, bytes);
		जाओ शेष_rw;
	पूर्ण

	/*
	 * Normal tracked MMIOs.
	 */
	mmio_info = पूर्णांकel_gvt_find_mmio_info(gvt, offset);
	अगर (!mmio_info) अणु
		gvt_dbg_mmio("untracked MMIO %08x len %d\n", offset, bytes);
		जाओ शेष_rw;
	पूर्ण

	अगर (is_पढ़ो)
		वापस mmio_info->पढ़ो(vgpu, offset, pdata, bytes);
	अन्यथा अणु
		u64 ro_mask = mmio_info->ro_mask;
		u32 old_vreg = 0;
		u64 data = 0;

		अगर (पूर्णांकel_gvt_mmio_has_mode_mask(gvt, mmio_info->offset)) अणु
			old_vreg = vgpu_vreg(vgpu, offset);
		पूर्ण

		अगर (likely(!ro_mask))
			ret = mmio_info->ग_लिखो(vgpu, offset, pdata, bytes);
		अन्यथा अगर (!~ro_mask) अणु
			gvt_vgpu_err("try to write RO reg %x\n", offset);
			वापस 0;
		पूर्ण अन्यथा अणु
			/* keep the RO bits in the भव रेजिस्टर */
			स_नकल(&data, pdata, bytes);
			data &= ~ro_mask;
			data |= vgpu_vreg(vgpu, offset) & ro_mask;
			ret = mmio_info->ग_लिखो(vgpu, offset, &data, bytes);
		पूर्ण

		/* higher 16bits of mode ctl regs are mask bits क्रम change */
		अगर (पूर्णांकel_gvt_mmio_has_mode_mask(gvt, mmio_info->offset)) अणु
			u32 mask = vgpu_vreg(vgpu, offset) >> 16;

			vgpu_vreg(vgpu, offset) = (old_vreg & ~mask)
					| (vgpu_vreg(vgpu, offset) & mask);
		पूर्ण
	पूर्ण

	वापस ret;

शेष_rw:
	वापस is_पढ़ो ?
		पूर्णांकel_vgpu_शेष_mmio_पढ़ो(vgpu, offset, pdata, bytes) :
		पूर्णांकel_vgpu_शेष_mmio_ग_लिखो(vgpu, offset, pdata, bytes);
पूर्ण

व्योम पूर्णांकel_gvt_restore_fence(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu;
	पूर्णांक i, id;

	idr_क्रम_each_entry(&(gvt)->vgpu_idr, vgpu, id) अणु
		mmio_hw_access_pre(gvt->gt);
		क्रम (i = 0; i < vgpu_fence_sz(vgpu); i++)
			पूर्णांकel_vgpu_ग_लिखो_fence(vgpu, i, vgpu_vreg64(vgpu, fence_num_to_offset(i)));
		mmio_hw_access_post(gvt->gt);
	पूर्ण
पूर्ण

अटल पूर्णांक mmio_pm_restore_handler(काष्ठा पूर्णांकel_gvt *gvt, u32 offset, व्योम *data)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = data;
	काष्ठा drm_i915_निजी *dev_priv = gvt->gt->i915;

	अगर (gvt->mmio.mmio_attribute[offset >> 2] & F_PM_SAVE)
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, _MMIO(offset), vgpu_vreg(vgpu, offset));

	वापस 0;
पूर्ण

व्योम पूर्णांकel_gvt_restore_mmio(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu;
	पूर्णांक id;

	idr_क्रम_each_entry(&(gvt)->vgpu_idr, vgpu, id) अणु
		mmio_hw_access_pre(gvt->gt);
		पूर्णांकel_gvt_क्रम_each_tracked_mmio(gvt, mmio_pm_restore_handler, vgpu);
		mmio_hw_access_post(gvt->gt);
	पूर्ण
पूर्ण
