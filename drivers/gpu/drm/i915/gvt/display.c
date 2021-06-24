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
 *    Zhiyuan Lv <zhiyuan.lv@पूर्णांकel.com>
 *
 * Contributors:
 *    Terrence Xu <terrence.xu@पूर्णांकel.com>
 *    Changbin Du <changbin.du@पूर्णांकel.com>
 *    Bing Niu <bing.niu@पूर्णांकel.com>
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *
 */

#समावेश "i915_drv.h"
#समावेश "gvt.h"

अटल पूर्णांक get_edp_pipe(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	u32 data = vgpu_vreg(vgpu, _TRANS_DDI_FUNC_CTL_EDP);
	पूर्णांक pipe = -1;

	चयन (data & TRANS_DDI_EDP_INPUT_MASK) अणु
	हाल TRANS_DDI_EDP_INPUT_A_ON:
	हाल TRANS_DDI_EDP_INPUT_A_ONOFF:
		pipe = PIPE_A;
		अवरोध;
	हाल TRANS_DDI_EDP_INPUT_B_ONOFF:
		pipe = PIPE_B;
		अवरोध;
	हाल TRANS_DDI_EDP_INPUT_C_ONOFF:
		pipe = PIPE_C;
		अवरोध;
	पूर्ण
	वापस pipe;
पूर्ण

अटल पूर्णांक edp_pipe_is_enabled(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा drm_i915_निजी *dev_priv = vgpu->gvt->gt->i915;

	अगर (!(vgpu_vreg_t(vgpu, PIPECONF(_PIPE_EDP)) & PIPECONF_ENABLE))
		वापस 0;

	अगर (!(vgpu_vreg(vgpu, _TRANS_DDI_FUNC_CTL_EDP) & TRANS_DDI_FUNC_ENABLE))
		वापस 0;
	वापस 1;
पूर्ण

पूर्णांक pipe_is_enabled(काष्ठा पूर्णांकel_vgpu *vgpu, पूर्णांक pipe)
अणु
	काष्ठा drm_i915_निजी *dev_priv = vgpu->gvt->gt->i915;

	अगर (drm_WARN_ON(&dev_priv->drm,
			pipe < PIPE_A || pipe >= I915_MAX_PIPES))
		वापस -EINVAL;

	अगर (vgpu_vreg_t(vgpu, PIPECONF(pipe)) & PIPECONF_ENABLE)
		वापस 1;

	अगर (edp_pipe_is_enabled(vgpu) &&
			get_edp_pipe(vgpu) == pipe)
		वापस 1;
	वापस 0;
पूर्ण

अटल अचिन्हित अक्षर भव_dp_monitor_edid[GVT_EDID_NUM][EDID_SIZE] = अणु
	अणु
/* EDID with 1024x768 as its resolution */
		/*Header*/
		0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
		/* Venकरोr & Product Identअगरication */
		0x22, 0xf0, 0x54, 0x29, 0x00, 0x00, 0x00, 0x00, 0x04, 0x17,
		/* Version & Revision */
		0x01, 0x04,
		/* Basic Display Parameters & Features */
		0xa5, 0x34, 0x20, 0x78, 0x23,
		/* Color Characteristics */
		0xfc, 0x81, 0xa4, 0x55, 0x4d, 0x9d, 0x25, 0x12, 0x50, 0x54,
		/* Established Timings: maximum resolution is 1024x768 */
		0x21, 0x08, 0x00,
		/* Standard Timings. All invalid */
		0x00, 0xc0, 0x00, 0xc0, 0x00, 0x40, 0x00, 0x80, 0x00, 0x00,
		0x00, 0x40, 0x00, 0x00, 0x00, 0x01,
		/* 18 Byte Data Blocks 1: invalid */
		0x00, 0x00, 0x80, 0xa0, 0x70, 0xb0,
		0x23, 0x40, 0x30, 0x20, 0x36, 0x00, 0x06, 0x44, 0x21, 0x00, 0x00, 0x1a,
		/* 18 Byte Data Blocks 2: invalid */
		0x00, 0x00, 0x00, 0xfd, 0x00, 0x18, 0x3c, 0x18, 0x50, 0x11, 0x00, 0x0a,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		/* 18 Byte Data Blocks 3: invalid */
		0x00, 0x00, 0x00, 0xfc, 0x00, 0x48,
		0x50, 0x20, 0x5a, 0x52, 0x32, 0x34, 0x34, 0x30, 0x77, 0x0a, 0x20, 0x20,
		/* 18 Byte Data Blocks 4: invalid */
		0x00, 0x00, 0x00, 0xff, 0x00, 0x43, 0x4e, 0x34, 0x33, 0x30, 0x34, 0x30,
		0x44, 0x58, 0x51, 0x0a, 0x20, 0x20,
		/* Extension Block Count */
		0x00,
		/* Checksum */
		0xef,
	पूर्ण,
	अणु
/* EDID with 1920x1200 as its resolution */
		/*Header*/
		0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
		/* Venकरोr & Product Identअगरication */
		0x22, 0xf0, 0x54, 0x29, 0x00, 0x00, 0x00, 0x00, 0x04, 0x17,
		/* Version & Revision */
		0x01, 0x04,
		/* Basic Display Parameters & Features */
		0xa5, 0x34, 0x20, 0x78, 0x23,
		/* Color Characteristics */
		0xfc, 0x81, 0xa4, 0x55, 0x4d, 0x9d, 0x25, 0x12, 0x50, 0x54,
		/* Established Timings: maximum resolution is 1024x768 */
		0x21, 0x08, 0x00,
		/*
		 * Standard Timings.
		 * below new resolutions can be supported:
		 * 1920x1080, 1280x720, 1280x960, 1280x1024,
		 * 1440x900, 1600x1200, 1680x1050
		 */
		0xd1, 0xc0, 0x81, 0xc0, 0x81, 0x40, 0x81, 0x80, 0x95, 0x00,
		0xa9, 0x40, 0xb3, 0x00, 0x01, 0x01,
		/* 18 Byte Data Blocks 1: max resolution is 1920x1200 */
		0x28, 0x3c, 0x80, 0xa0, 0x70, 0xb0,
		0x23, 0x40, 0x30, 0x20, 0x36, 0x00, 0x06, 0x44, 0x21, 0x00, 0x00, 0x1a,
		/* 18 Byte Data Blocks 2: invalid */
		0x00, 0x00, 0x00, 0xfd, 0x00, 0x18, 0x3c, 0x18, 0x50, 0x11, 0x00, 0x0a,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		/* 18 Byte Data Blocks 3: invalid */
		0x00, 0x00, 0x00, 0xfc, 0x00, 0x48,
		0x50, 0x20, 0x5a, 0x52, 0x32, 0x34, 0x34, 0x30, 0x77, 0x0a, 0x20, 0x20,
		/* 18 Byte Data Blocks 4: invalid */
		0x00, 0x00, 0x00, 0xff, 0x00, 0x43, 0x4e, 0x34, 0x33, 0x30, 0x34, 0x30,
		0x44, 0x58, 0x51, 0x0a, 0x20, 0x20,
		/* Extension Block Count */
		0x00,
		/* Checksum */
		0x45,
	पूर्ण,
पूर्ण;

#घोषणा DPCD_HEADER_SIZE        0xb

/* let the भव display supports DP1.2 */
अटल u8 dpcd_fix_data[DPCD_HEADER_SIZE] = अणु
	0x12, 0x014, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
पूर्ण;

अटल व्योम emulate_monitor_status_change(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा drm_i915_निजी *dev_priv = vgpu->gvt->gt->i915;
	पूर्णांक pipe;

	अगर (IS_BROXTON(dev_priv)) अणु
		क्रमागत transcoder trans;
		क्रमागत port port;

		/* Clear PIPE, DDI, PHY, HPD beक्रमe setting new */
		vgpu_vreg_t(vgpu, GEN8_DE_PORT_ISR) &=
			~(GEN8_DE_PORT_HOTPLUG(HPD_PORT_A) |
			  GEN8_DE_PORT_HOTPLUG(HPD_PORT_B) |
			  GEN8_DE_PORT_HOTPLUG(HPD_PORT_C));

		क्रम_each_pipe(dev_priv, pipe) अणु
			vgpu_vreg_t(vgpu, PIPECONF(pipe)) &=
				~(PIPECONF_ENABLE | I965_PIPECONF_ACTIVE);
			vgpu_vreg_t(vgpu, DSPCNTR(pipe)) &= ~DISPLAY_PLANE_ENABLE;
			vgpu_vreg_t(vgpu, SPRCTL(pipe)) &= ~SPRITE_ENABLE;
			vgpu_vreg_t(vgpu, CURCNTR(pipe)) &= ~MCURSOR_MODE;
			vgpu_vreg_t(vgpu, CURCNTR(pipe)) |= MCURSOR_MODE_DISABLE;
		पूर्ण

		क्रम (trans = TRANSCODER_A; trans <= TRANSCODER_EDP; trans++) अणु
			vgpu_vreg_t(vgpu, TRANS_DDI_FUNC_CTL(trans)) &=
				~(TRANS_DDI_BPC_MASK | TRANS_DDI_MODE_SELECT_MASK |
				  TRANS_DDI_PORT_MASK | TRANS_DDI_FUNC_ENABLE);
		पूर्ण
		vgpu_vreg_t(vgpu, TRANS_DDI_FUNC_CTL(TRANSCODER_A)) &=
			~(TRANS_DDI_BPC_MASK | TRANS_DDI_MODE_SELECT_MASK |
			  TRANS_DDI_PORT_MASK);

		क्रम (port = PORT_A; port <= PORT_C; port++) अणु
			vgpu_vreg_t(vgpu, BXT_PHY_CTL(port)) &=
				~BXT_PHY_LANE_ENABLED;
			vgpu_vreg_t(vgpu, BXT_PHY_CTL(port)) |=
				(BXT_PHY_CMNLANE_POWERDOWN_ACK |
				 BXT_PHY_LANE_POWERDOWN_ACK);

			vgpu_vreg_t(vgpu, BXT_PORT_PLL_ENABLE(port)) &=
				~(PORT_PLL_POWER_STATE | PORT_PLL_POWER_ENABLE |
				  PORT_PLL_REF_SEL | PORT_PLL_LOCK |
				  PORT_PLL_ENABLE);

			vgpu_vreg_t(vgpu, DDI_BUF_CTL(port)) &=
				~(DDI_INIT_DISPLAY_DETECTED |
				  DDI_BUF_CTL_ENABLE);
			vgpu_vreg_t(vgpu, DDI_BUF_CTL(port)) |= DDI_BUF_IS_IDLE;
		पूर्ण
		vgpu_vreg_t(vgpu, PCH_PORT_HOTPLUG) &=
			~(PORTA_HOTPLUG_ENABLE | PORTA_HOTPLUG_STATUS_MASK);
		vgpu_vreg_t(vgpu, PCH_PORT_HOTPLUG) &=
			~(PORTB_HOTPLUG_ENABLE | PORTB_HOTPLUG_STATUS_MASK);
		vgpu_vreg_t(vgpu, PCH_PORT_HOTPLUG) &=
			~(PORTC_HOTPLUG_ENABLE | PORTC_HOTPLUG_STATUS_MASK);
		/* No hpd_invert set in vgpu vbt, need to clear invert mask */
		vgpu_vreg_t(vgpu, PCH_PORT_HOTPLUG) &= ~BXT_DDI_HPD_INVERT_MASK;
		vgpu_vreg_t(vgpu, GEN8_DE_PORT_ISR) &= ~BXT_DE_PORT_HOTPLUG_MASK;

		vgpu_vreg_t(vgpu, BXT_P_CR_GT_DISP_PWRON) &= ~(BIT(0) | BIT(1));
		vgpu_vreg_t(vgpu, BXT_PORT_CL1CM_DW0(DPIO_PHY0)) &=
			~PHY_POWER_GOOD;
		vgpu_vreg_t(vgpu, BXT_PORT_CL1CM_DW0(DPIO_PHY1)) &=
			~PHY_POWER_GOOD;
		vgpu_vreg_t(vgpu, BXT_PHY_CTL_FAMILY(DPIO_PHY0)) &= ~BIT(30);
		vgpu_vreg_t(vgpu, BXT_PHY_CTL_FAMILY(DPIO_PHY1)) &= ~BIT(30);

		vgpu_vreg_t(vgpu, SFUSE_STRAP) &= ~SFUSE_STRAP_DDIB_DETECTED;
		vgpu_vreg_t(vgpu, SFUSE_STRAP) &= ~SFUSE_STRAP_DDIC_DETECTED;

		/*
		 * Only 1 PIPE enabled in current vGPU display and PIPE_A is
		 *  tied to TRANSCODER_A in HW, so it's safe to assume PIPE_A,
		 *   TRANSCODER_A can be enabled. PORT_x depends on the input of
		 *   setup_भव_dp_monitor.
		 */
		vgpu_vreg_t(vgpu, PIPECONF(PIPE_A)) |= PIPECONF_ENABLE;
		vgpu_vreg_t(vgpu, PIPECONF(PIPE_A)) |= I965_PIPECONF_ACTIVE;

		/*
		 * Golden M/N are calculated based on:
		 *   24 bpp, 4 lanes, 154000 pixel clk (from भव EDID),
		 *   DP link clk 1620 MHz and non-स्थिरant_n.
		 * TODO: calculate DP link symbol clk and stream clk m/n.
		 */
		vgpu_vreg_t(vgpu, PIPE_DATA_M1(TRANSCODER_A)) = 63 << TU_SIZE_SHIFT;
		vgpu_vreg_t(vgpu, PIPE_DATA_M1(TRANSCODER_A)) |= 0x5b425e;
		vgpu_vreg_t(vgpu, PIPE_DATA_N1(TRANSCODER_A)) = 0x800000;
		vgpu_vreg_t(vgpu, PIPE_LINK_M1(TRANSCODER_A)) = 0x3cd6e;
		vgpu_vreg_t(vgpu, PIPE_LINK_N1(TRANSCODER_A)) = 0x80000;

		/* Enable per-DDI/PORT vreg */
		अगर (पूर्णांकel_vgpu_has_monitor_on_port(vgpu, PORT_A)) अणु
			vgpu_vreg_t(vgpu, BXT_P_CR_GT_DISP_PWRON) |= BIT(1);
			vgpu_vreg_t(vgpu, BXT_PORT_CL1CM_DW0(DPIO_PHY1)) |=
				PHY_POWER_GOOD;
			vgpu_vreg_t(vgpu, BXT_PHY_CTL_FAMILY(DPIO_PHY1)) |=
				BIT(30);
			vgpu_vreg_t(vgpu, BXT_PHY_CTL(PORT_A)) |=
				BXT_PHY_LANE_ENABLED;
			vgpu_vreg_t(vgpu, BXT_PHY_CTL(PORT_A)) &=
				~(BXT_PHY_CMNLANE_POWERDOWN_ACK |
				  BXT_PHY_LANE_POWERDOWN_ACK);
			vgpu_vreg_t(vgpu, BXT_PORT_PLL_ENABLE(PORT_A)) |=
				(PORT_PLL_POWER_STATE | PORT_PLL_POWER_ENABLE |
				 PORT_PLL_REF_SEL | PORT_PLL_LOCK |
				 PORT_PLL_ENABLE);
			vgpu_vreg_t(vgpu, DDI_BUF_CTL(PORT_A)) |=
				(DDI_BUF_CTL_ENABLE | DDI_INIT_DISPLAY_DETECTED);
			vgpu_vreg_t(vgpu, DDI_BUF_CTL(PORT_A)) &=
				~DDI_BUF_IS_IDLE;
			vgpu_vreg_t(vgpu, TRANS_DDI_FUNC_CTL(TRANSCODER_EDP)) |=
				(TRANS_DDI_BPC_8 | TRANS_DDI_MODE_SELECT_DP_SST |
				 TRANS_DDI_FUNC_ENABLE);
			vgpu_vreg_t(vgpu, PCH_PORT_HOTPLUG) |=
				PORTA_HOTPLUG_ENABLE;
			vgpu_vreg_t(vgpu, GEN8_DE_PORT_ISR) |=
				GEN8_DE_PORT_HOTPLUG(HPD_PORT_A);
		पूर्ण

		अगर (पूर्णांकel_vgpu_has_monitor_on_port(vgpu, PORT_B)) अणु
			vgpu_vreg_t(vgpu, SFUSE_STRAP) |= SFUSE_STRAP_DDIB_DETECTED;
			vgpu_vreg_t(vgpu, BXT_P_CR_GT_DISP_PWRON) |= BIT(0);
			vgpu_vreg_t(vgpu, BXT_PORT_CL1CM_DW0(DPIO_PHY0)) |=
				PHY_POWER_GOOD;
			vgpu_vreg_t(vgpu, BXT_PHY_CTL_FAMILY(DPIO_PHY0)) |=
				BIT(30);
			vgpu_vreg_t(vgpu, BXT_PHY_CTL(PORT_B)) |=
				BXT_PHY_LANE_ENABLED;
			vgpu_vreg_t(vgpu, BXT_PHY_CTL(PORT_B)) &=
				~(BXT_PHY_CMNLANE_POWERDOWN_ACK |
				  BXT_PHY_LANE_POWERDOWN_ACK);
			vgpu_vreg_t(vgpu, BXT_PORT_PLL_ENABLE(PORT_B)) |=
				(PORT_PLL_POWER_STATE | PORT_PLL_POWER_ENABLE |
				 PORT_PLL_REF_SEL | PORT_PLL_LOCK |
				 PORT_PLL_ENABLE);
			vgpu_vreg_t(vgpu, DDI_BUF_CTL(PORT_B)) |=
				DDI_BUF_CTL_ENABLE;
			vgpu_vreg_t(vgpu, DDI_BUF_CTL(PORT_B)) &=
				~DDI_BUF_IS_IDLE;
			vgpu_vreg_t(vgpu, TRANS_DDI_FUNC_CTL(TRANSCODER_A)) |=
				(TRANS_DDI_BPC_8 | TRANS_DDI_MODE_SELECT_DP_SST |
				 (PORT_B << TRANS_DDI_PORT_SHIFT) |
				 TRANS_DDI_FUNC_ENABLE);
			vgpu_vreg_t(vgpu, PCH_PORT_HOTPLUG) |=
				PORTB_HOTPLUG_ENABLE;
			vgpu_vreg_t(vgpu, GEN8_DE_PORT_ISR) |=
				GEN8_DE_PORT_HOTPLUG(HPD_PORT_B);
		पूर्ण

		अगर (पूर्णांकel_vgpu_has_monitor_on_port(vgpu, PORT_C)) अणु
			vgpu_vreg_t(vgpu, SFUSE_STRAP) |= SFUSE_STRAP_DDIC_DETECTED;
			vgpu_vreg_t(vgpu, BXT_P_CR_GT_DISP_PWRON) |= BIT(0);
			vgpu_vreg_t(vgpu, BXT_PORT_CL1CM_DW0(DPIO_PHY0)) |=
				PHY_POWER_GOOD;
			vgpu_vreg_t(vgpu, BXT_PHY_CTL_FAMILY(DPIO_PHY0)) |=
				BIT(30);
			vgpu_vreg_t(vgpu, BXT_PHY_CTL(PORT_C)) |=
				BXT_PHY_LANE_ENABLED;
			vgpu_vreg_t(vgpu, BXT_PHY_CTL(PORT_C)) &=
				~(BXT_PHY_CMNLANE_POWERDOWN_ACK |
				  BXT_PHY_LANE_POWERDOWN_ACK);
			vgpu_vreg_t(vgpu, BXT_PORT_PLL_ENABLE(PORT_C)) |=
				(PORT_PLL_POWER_STATE | PORT_PLL_POWER_ENABLE |
				 PORT_PLL_REF_SEL | PORT_PLL_LOCK |
				 PORT_PLL_ENABLE);
			vgpu_vreg_t(vgpu, DDI_BUF_CTL(PORT_C)) |=
				DDI_BUF_CTL_ENABLE;
			vgpu_vreg_t(vgpu, DDI_BUF_CTL(PORT_C)) &=
				~DDI_BUF_IS_IDLE;
			vgpu_vreg_t(vgpu, TRANS_DDI_FUNC_CTL(TRANSCODER_A)) |=
				(TRANS_DDI_BPC_8 | TRANS_DDI_MODE_SELECT_DP_SST |
				 (PORT_B << TRANS_DDI_PORT_SHIFT) |
				 TRANS_DDI_FUNC_ENABLE);
			vgpu_vreg_t(vgpu, PCH_PORT_HOTPLUG) |=
				PORTC_HOTPLUG_ENABLE;
			vgpu_vreg_t(vgpu, GEN8_DE_PORT_ISR) |=
				GEN8_DE_PORT_HOTPLUG(HPD_PORT_C);
		पूर्ण

		वापस;
	पूर्ण

	vgpu_vreg_t(vgpu, SDEISR) &= ~(SDE_PORTB_HOTPLUG_CPT |
			SDE_PORTC_HOTPLUG_CPT |
			SDE_PORTD_HOTPLUG_CPT);

	अगर (IS_SKYLAKE(dev_priv) ||
	    IS_KABYLAKE(dev_priv) ||
	    IS_COFFEELAKE(dev_priv) ||
	    IS_COMETLAKE(dev_priv)) अणु
		vgpu_vreg_t(vgpu, SDEISR) &= ~(SDE_PORTA_HOTPLUG_SPT |
				SDE_PORTE_HOTPLUG_SPT);
		vgpu_vreg_t(vgpu, SKL_FUSE_STATUS) |=
				SKL_FUSE_DOWNLOAD_STATUS |
				SKL_FUSE_PG_DIST_STATUS(SKL_PG0) |
				SKL_FUSE_PG_DIST_STATUS(SKL_PG1) |
				SKL_FUSE_PG_DIST_STATUS(SKL_PG2);
		/*
		 * Only 1 PIPE enabled in current vGPU display and PIPE_A is
		 *  tied to TRANSCODER_A in HW, so it's safe to assume PIPE_A,
		 *   TRANSCODER_A can be enabled. PORT_x depends on the input of
		 *   setup_भव_dp_monitor, we can bind DPLL0 to any PORT_x
		 *   so we fixed to DPLL0 here.
		 * Setup DPLL0: DP link clk 1620 MHz, non SSC, DP Mode
		 */
		vgpu_vreg_t(vgpu, DPLL_CTRL1) =
			DPLL_CTRL1_OVERRIDE(DPLL_ID_SKL_DPLL0);
		vgpu_vreg_t(vgpu, DPLL_CTRL1) |=
			DPLL_CTRL1_LINK_RATE(DPLL_CTRL1_LINK_RATE_1620, DPLL_ID_SKL_DPLL0);
		vgpu_vreg_t(vgpu, LCPLL1_CTL) =
			LCPLL_PLL_ENABLE | LCPLL_PLL_LOCK;
		vgpu_vreg_t(vgpu, DPLL_STATUS) = DPLL_LOCK(DPLL_ID_SKL_DPLL0);
		/*
		 * Golden M/N are calculated based on:
		 *   24 bpp, 4 lanes, 154000 pixel clk (from भव EDID),
		 *   DP link clk 1620 MHz and non-स्थिरant_n.
		 * TODO: calculate DP link symbol clk and stream clk m/n.
		 */
		vgpu_vreg_t(vgpu, PIPE_DATA_M1(TRANSCODER_A)) = 63 << TU_SIZE_SHIFT;
		vgpu_vreg_t(vgpu, PIPE_DATA_M1(TRANSCODER_A)) |= 0x5b425e;
		vgpu_vreg_t(vgpu, PIPE_DATA_N1(TRANSCODER_A)) = 0x800000;
		vgpu_vreg_t(vgpu, PIPE_LINK_M1(TRANSCODER_A)) = 0x3cd6e;
		vgpu_vreg_t(vgpu, PIPE_LINK_N1(TRANSCODER_A)) = 0x80000;
	पूर्ण

	अगर (पूर्णांकel_vgpu_has_monitor_on_port(vgpu, PORT_B)) अणु
		vgpu_vreg_t(vgpu, DPLL_CTRL2) &=
			~DPLL_CTRL2_DDI_CLK_OFF(PORT_B);
		vgpu_vreg_t(vgpu, DPLL_CTRL2) |=
			DPLL_CTRL2_DDI_CLK_SEL(DPLL_ID_SKL_DPLL0, PORT_B);
		vgpu_vreg_t(vgpu, DPLL_CTRL2) |=
			DPLL_CTRL2_DDI_SEL_OVERRIDE(PORT_B);
		vgpu_vreg_t(vgpu, SFUSE_STRAP) |= SFUSE_STRAP_DDIB_DETECTED;
		vgpu_vreg_t(vgpu, TRANS_DDI_FUNC_CTL(TRANSCODER_A)) &=
			~(TRANS_DDI_BPC_MASK | TRANS_DDI_MODE_SELECT_MASK |
			TRANS_DDI_PORT_MASK);
		vgpu_vreg_t(vgpu, TRANS_DDI_FUNC_CTL(TRANSCODER_A)) |=
			(TRANS_DDI_BPC_8 | TRANS_DDI_MODE_SELECT_DP_SST |
			(PORT_B << TRANS_DDI_PORT_SHIFT) |
			TRANS_DDI_FUNC_ENABLE);
		अगर (IS_BROADWELL(dev_priv)) अणु
			vgpu_vreg_t(vgpu, PORT_CLK_SEL(PORT_B)) &=
				~PORT_CLK_SEL_MASK;
			vgpu_vreg_t(vgpu, PORT_CLK_SEL(PORT_B)) |=
				PORT_CLK_SEL_LCPLL_810;
		पूर्ण
		vgpu_vreg_t(vgpu, DDI_BUF_CTL(PORT_B)) |= DDI_BUF_CTL_ENABLE;
		vgpu_vreg_t(vgpu, DDI_BUF_CTL(PORT_B)) &= ~DDI_BUF_IS_IDLE;
		vgpu_vreg_t(vgpu, SDEISR) |= SDE_PORTB_HOTPLUG_CPT;
	पूर्ण

	अगर (पूर्णांकel_vgpu_has_monitor_on_port(vgpu, PORT_C)) अणु
		vgpu_vreg_t(vgpu, DPLL_CTRL2) &=
			~DPLL_CTRL2_DDI_CLK_OFF(PORT_C);
		vgpu_vreg_t(vgpu, DPLL_CTRL2) |=
			DPLL_CTRL2_DDI_CLK_SEL(DPLL_ID_SKL_DPLL0, PORT_C);
		vgpu_vreg_t(vgpu, DPLL_CTRL2) |=
			DPLL_CTRL2_DDI_SEL_OVERRIDE(PORT_C);
		vgpu_vreg_t(vgpu, SDEISR) |= SDE_PORTC_HOTPLUG_CPT;
		vgpu_vreg_t(vgpu, TRANS_DDI_FUNC_CTL(TRANSCODER_A)) &=
			~(TRANS_DDI_BPC_MASK | TRANS_DDI_MODE_SELECT_MASK |
			TRANS_DDI_PORT_MASK);
		vgpu_vreg_t(vgpu, TRANS_DDI_FUNC_CTL(TRANSCODER_A)) |=
			(TRANS_DDI_BPC_8 | TRANS_DDI_MODE_SELECT_DP_SST |
			(PORT_C << TRANS_DDI_PORT_SHIFT) |
			TRANS_DDI_FUNC_ENABLE);
		अगर (IS_BROADWELL(dev_priv)) अणु
			vgpu_vreg_t(vgpu, PORT_CLK_SEL(PORT_C)) &=
				~PORT_CLK_SEL_MASK;
			vgpu_vreg_t(vgpu, PORT_CLK_SEL(PORT_C)) |=
				PORT_CLK_SEL_LCPLL_810;
		पूर्ण
		vgpu_vreg_t(vgpu, DDI_BUF_CTL(PORT_C)) |= DDI_BUF_CTL_ENABLE;
		vgpu_vreg_t(vgpu, DDI_BUF_CTL(PORT_C)) &= ~DDI_BUF_IS_IDLE;
		vgpu_vreg_t(vgpu, SFUSE_STRAP) |= SFUSE_STRAP_DDIC_DETECTED;
	पूर्ण

	अगर (पूर्णांकel_vgpu_has_monitor_on_port(vgpu, PORT_D)) अणु
		vgpu_vreg_t(vgpu, DPLL_CTRL2) &=
			~DPLL_CTRL2_DDI_CLK_OFF(PORT_D);
		vgpu_vreg_t(vgpu, DPLL_CTRL2) |=
			DPLL_CTRL2_DDI_CLK_SEL(DPLL_ID_SKL_DPLL0, PORT_D);
		vgpu_vreg_t(vgpu, DPLL_CTRL2) |=
			DPLL_CTRL2_DDI_SEL_OVERRIDE(PORT_D);
		vgpu_vreg_t(vgpu, SDEISR) |= SDE_PORTD_HOTPLUG_CPT;
		vgpu_vreg_t(vgpu, TRANS_DDI_FUNC_CTL(TRANSCODER_A)) &=
			~(TRANS_DDI_BPC_MASK | TRANS_DDI_MODE_SELECT_MASK |
			TRANS_DDI_PORT_MASK);
		vgpu_vreg_t(vgpu, TRANS_DDI_FUNC_CTL(TRANSCODER_A)) |=
			(TRANS_DDI_BPC_8 | TRANS_DDI_MODE_SELECT_DP_SST |
			(PORT_D << TRANS_DDI_PORT_SHIFT) |
			TRANS_DDI_FUNC_ENABLE);
		अगर (IS_BROADWELL(dev_priv)) अणु
			vgpu_vreg_t(vgpu, PORT_CLK_SEL(PORT_D)) &=
				~PORT_CLK_SEL_MASK;
			vgpu_vreg_t(vgpu, PORT_CLK_SEL(PORT_D)) |=
				PORT_CLK_SEL_LCPLL_810;
		पूर्ण
		vgpu_vreg_t(vgpu, DDI_BUF_CTL(PORT_D)) |= DDI_BUF_CTL_ENABLE;
		vgpu_vreg_t(vgpu, DDI_BUF_CTL(PORT_D)) &= ~DDI_BUF_IS_IDLE;
		vgpu_vreg_t(vgpu, SFUSE_STRAP) |= SFUSE_STRAP_DDID_DETECTED;
	पूर्ण

	अगर ((IS_SKYLAKE(dev_priv) ||
	     IS_KABYLAKE(dev_priv) ||
	     IS_COFFEELAKE(dev_priv) ||
	     IS_COMETLAKE(dev_priv)) &&
			पूर्णांकel_vgpu_has_monitor_on_port(vgpu, PORT_E)) अणु
		vgpu_vreg_t(vgpu, SDEISR) |= SDE_PORTE_HOTPLUG_SPT;
	पूर्ण

	अगर (पूर्णांकel_vgpu_has_monitor_on_port(vgpu, PORT_A)) अणु
		अगर (IS_BROADWELL(dev_priv))
			vgpu_vreg_t(vgpu, GEN8_DE_PORT_ISR) |=
				GEN8_DE_PORT_HOTPLUG(HPD_PORT_A);
		अन्यथा
			vgpu_vreg_t(vgpu, SDEISR) |= SDE_PORTA_HOTPLUG_SPT;

		vgpu_vreg_t(vgpu, DDI_BUF_CTL(PORT_A)) |= DDI_INIT_DISPLAY_DETECTED;
	पूर्ण

	/* Clear host CRT status, so guest couldn't detect this host CRT. */
	अगर (IS_BROADWELL(dev_priv))
		vgpu_vreg_t(vgpu, PCH_ADPA) &= ~ADPA_CRT_HOTPLUG_MONITOR_MASK;

	/* Disable Primary/Sprite/Cursor plane */
	क्रम_each_pipe(dev_priv, pipe) अणु
		vgpu_vreg_t(vgpu, DSPCNTR(pipe)) &= ~DISPLAY_PLANE_ENABLE;
		vgpu_vreg_t(vgpu, SPRCTL(pipe)) &= ~SPRITE_ENABLE;
		vgpu_vreg_t(vgpu, CURCNTR(pipe)) &= ~MCURSOR_MODE;
		vgpu_vreg_t(vgpu, CURCNTR(pipe)) |= MCURSOR_MODE_DISABLE;
	पूर्ण

	vgpu_vreg_t(vgpu, PIPECONF(PIPE_A)) |= PIPECONF_ENABLE;
पूर्ण

अटल व्योम clean_भव_dp_monitor(काष्ठा पूर्णांकel_vgpu *vgpu, पूर्णांक port_num)
अणु
	काष्ठा पूर्णांकel_vgpu_port *port = पूर्णांकel_vgpu_port(vgpu, port_num);

	kमुक्त(port->edid);
	port->edid = शून्य;

	kमुक्त(port->dpcd);
	port->dpcd = शून्य;
पूर्ण

अटल क्रमागत hrसमयr_restart vblank_समयr_fn(काष्ठा hrसमयr *data)
अणु
	काष्ठा पूर्णांकel_vgpu_vblank_समयr *vblank_समयr;
	काष्ठा पूर्णांकel_vgpu *vgpu;

	vblank_समयr = container_of(data, काष्ठा पूर्णांकel_vgpu_vblank_समयr, समयr);
	vgpu = container_of(vblank_समयr, काष्ठा पूर्णांकel_vgpu, vblank_समयr);

	/* Set vblank emulation request per-vGPU bit */
	पूर्णांकel_gvt_request_service(vgpu->gvt,
				  INTEL_GVT_REQUEST_EMULATE_VBLANK + vgpu->id);
	hrसमयr_add_expires_ns(&vblank_समयr->समयr, vblank_समयr->period);
	वापस HRTIMER_RESTART;
पूर्ण

अटल पूर्णांक setup_भव_dp_monitor(काष्ठा पूर्णांकel_vgpu *vgpu, पूर्णांक port_num,
				    पूर्णांक type, अचिन्हित पूर्णांक resolution)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;
	काष्ठा पूर्णांकel_vgpu_port *port = पूर्णांकel_vgpu_port(vgpu, port_num);
	काष्ठा पूर्णांकel_vgpu_vblank_समयr *vblank_समयr = &vgpu->vblank_समयr;

	अगर (drm_WARN_ON(&i915->drm, resolution >= GVT_EDID_NUM))
		वापस -EINVAL;

	port->edid = kzalloc(माप(*(port->edid)), GFP_KERNEL);
	अगर (!port->edid)
		वापस -ENOMEM;

	port->dpcd = kzalloc(माप(*(port->dpcd)), GFP_KERNEL);
	अगर (!port->dpcd) अणु
		kमुक्त(port->edid);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(port->edid->edid_block, भव_dp_monitor_edid[resolution],
			EDID_SIZE);
	port->edid->data_valid = true;

	स_नकल(port->dpcd->data, dpcd_fix_data, DPCD_HEADER_SIZE);
	port->dpcd->data_valid = true;
	port->dpcd->data[DPCD_SINK_COUNT] = 0x1;
	port->type = type;
	port->id = resolution;
	port->vrefresh_k = GVT_DEFAULT_REFRESH_RATE * MSEC_PER_SEC;
	vgpu->display.port_num = port_num;

	/* Init hrसमयr based on शेष refresh rate */
	hrसमयr_init(&vblank_समयr->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	vblank_समयr->समयr.function = vblank_समयr_fn;
	vblank_समयr->vrefresh_k = port->vrefresh_k;
	vblank_समयr->period = DIV64_U64_ROUND_CLOSEST(NSEC_PER_SEC * MSEC_PER_SEC, vblank_समयr->vrefresh_k);

	emulate_monitor_status_change(vgpu);

	वापस 0;
पूर्ण

/**
 * vgpu_update_vblank_emulation - Update per-vGPU vblank_समयr
 * @vgpu: vGPU operated
 * @turnon: Turn ON/OFF vblank_समयr
 *
 * This function is used to turn on/off or update the per-vGPU vblank_समयr
 * when PIPECONF is enabled or disabled. vblank_समयr period is also updated
 * अगर guest changed the refresh rate.
 *
 */
व्योम vgpu_update_vblank_emulation(काष्ठा पूर्णांकel_vgpu *vgpu, bool turnon)
अणु
	काष्ठा पूर्णांकel_vgpu_vblank_समयr *vblank_समयr = &vgpu->vblank_समयr;
	काष्ठा पूर्णांकel_vgpu_port *port =
		पूर्णांकel_vgpu_port(vgpu, vgpu->display.port_num);

	अगर (turnon) अणु
		/*
		 * Skip the re-enable अगर alपढ़ोy active and vrefresh unchanged.
		 * Otherwise, stop समयr अगर alपढ़ोy active and restart with new
		 *   period.
		 */
		अगर (vblank_समयr->vrefresh_k != port->vrefresh_k ||
		    !hrसमयr_active(&vblank_समयr->समयr)) अणु
			/* Stop समयr beक्रमe start with new period अगर active */
			अगर (hrसमयr_active(&vblank_समयr->समयr))
				hrसमयr_cancel(&vblank_समयr->समयr);

			/* Make sure new refresh rate updated to समयr period */
			vblank_समयr->vrefresh_k = port->vrefresh_k;
			vblank_समयr->period = DIV64_U64_ROUND_CLOSEST(NSEC_PER_SEC * MSEC_PER_SEC, vblank_समयr->vrefresh_k);
			hrसमयr_start(&vblank_समयr->समयr,
				      kसमय_add_ns(kसमय_get(), vblank_समयr->period),
				      HRTIMER_MODE_ABS);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Caller request to stop vblank */
		hrसमयr_cancel(&vblank_समयr->समयr);
	पूर्ण
पूर्ण

अटल व्योम emulate_vblank_on_pipe(काष्ठा पूर्णांकel_vgpu *vgpu, पूर्णांक pipe)
अणु
	काष्ठा drm_i915_निजी *dev_priv = vgpu->gvt->gt->i915;
	काष्ठा पूर्णांकel_vgpu_irq *irq = &vgpu->irq;
	पूर्णांक vblank_event[] = अणु
		[PIPE_A] = PIPE_A_VBLANK,
		[PIPE_B] = PIPE_B_VBLANK,
		[PIPE_C] = PIPE_C_VBLANK,
	पूर्ण;
	पूर्णांक event;

	अगर (pipe < PIPE_A || pipe > PIPE_C)
		वापस;

	क्रम_each_set_bit(event, irq->flip_करोne_event[pipe],
			INTEL_GVT_EVENT_MAX) अणु
		clear_bit(event, irq->flip_करोne_event[pipe]);
		अगर (!pipe_is_enabled(vgpu, pipe))
			जारी;

		पूर्णांकel_vgpu_trigger_भव_event(vgpu, event);
	पूर्ण

	अगर (pipe_is_enabled(vgpu, pipe)) अणु
		vgpu_vreg_t(vgpu, PIPE_FRMCOUNT_G4X(pipe))++;
		पूर्णांकel_vgpu_trigger_भव_event(vgpu, vblank_event[pipe]);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_vgpu_emulate_vblank(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	पूर्णांक pipe;

	mutex_lock(&vgpu->vgpu_lock);
	क्रम_each_pipe(vgpu->gvt->gt->i915, pipe)
		emulate_vblank_on_pipe(vgpu, pipe);
	mutex_unlock(&vgpu->vgpu_lock);
पूर्ण

/**
 * पूर्णांकel_vgpu_emulate_hotplug - trigger hotplug event क्रम vGPU
 * @vgpu: a vGPU
 * @connected: link state
 *
 * This function is used to trigger hotplug पूर्णांकerrupt क्रम vGPU
 *
 */
व्योम पूर्णांकel_vgpu_emulate_hotplug(काष्ठा पूर्णांकel_vgpu *vgpu, bool connected)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;

	/* TODO: add more platक्रमms support */
	अगर (IS_SKYLAKE(i915) ||
	    IS_KABYLAKE(i915) ||
	    IS_COFFEELAKE(i915) ||
	    IS_COMETLAKE(i915)) अणु
		अगर (connected) अणु
			vgpu_vreg_t(vgpu, SFUSE_STRAP) |=
				SFUSE_STRAP_DDID_DETECTED;
			vgpu_vreg_t(vgpu, SDEISR) |= SDE_PORTD_HOTPLUG_CPT;
		पूर्ण अन्यथा अणु
			vgpu_vreg_t(vgpu, SFUSE_STRAP) &=
				~SFUSE_STRAP_DDID_DETECTED;
			vgpu_vreg_t(vgpu, SDEISR) &= ~SDE_PORTD_HOTPLUG_CPT;
		पूर्ण
		vgpu_vreg_t(vgpu, SDEIIR) |= SDE_PORTD_HOTPLUG_CPT;
		vgpu_vreg_t(vgpu, PCH_PORT_HOTPLUG) |=
				PORTD_HOTPLUG_STATUS_MASK;
		पूर्णांकel_vgpu_trigger_भव_event(vgpu, DP_D_HOTPLUG);
	पूर्ण अन्यथा अगर (IS_BROXTON(i915)) अणु
		अगर (पूर्णांकel_vgpu_has_monitor_on_port(vgpu, PORT_A)) अणु
			अगर (connected) अणु
				vgpu_vreg_t(vgpu, GEN8_DE_PORT_ISR) |=
					GEN8_DE_PORT_HOTPLUG(HPD_PORT_A);
			पूर्ण अन्यथा अणु
				vgpu_vreg_t(vgpu, GEN8_DE_PORT_ISR) &=
					~GEN8_DE_PORT_HOTPLUG(HPD_PORT_A);
			पूर्ण
			vgpu_vreg_t(vgpu, GEN8_DE_PORT_IIR) |=
				GEN8_DE_PORT_HOTPLUG(HPD_PORT_A);
			vgpu_vreg_t(vgpu, PCH_PORT_HOTPLUG) &=
				~PORTA_HOTPLUG_STATUS_MASK;
			vgpu_vreg_t(vgpu, PCH_PORT_HOTPLUG) |=
				PORTA_HOTPLUG_LONG_DETECT;
			पूर्णांकel_vgpu_trigger_भव_event(vgpu, DP_A_HOTPLUG);
		पूर्ण
		अगर (पूर्णांकel_vgpu_has_monitor_on_port(vgpu, PORT_B)) अणु
			अगर (connected) अणु
				vgpu_vreg_t(vgpu, GEN8_DE_PORT_ISR) |=
					GEN8_DE_PORT_HOTPLUG(HPD_PORT_B);
				vgpu_vreg_t(vgpu, SFUSE_STRAP) |=
					SFUSE_STRAP_DDIB_DETECTED;
			पूर्ण अन्यथा अणु
				vgpu_vreg_t(vgpu, GEN8_DE_PORT_ISR) &=
					~GEN8_DE_PORT_HOTPLUG(HPD_PORT_B);
				vgpu_vreg_t(vgpu, SFUSE_STRAP) &=
					~SFUSE_STRAP_DDIB_DETECTED;
			पूर्ण
			vgpu_vreg_t(vgpu, GEN8_DE_PORT_IIR) |=
				GEN8_DE_PORT_HOTPLUG(HPD_PORT_B);
			vgpu_vreg_t(vgpu, PCH_PORT_HOTPLUG) &=
				~PORTB_HOTPLUG_STATUS_MASK;
			vgpu_vreg_t(vgpu, PCH_PORT_HOTPLUG) |=
				PORTB_HOTPLUG_LONG_DETECT;
			पूर्णांकel_vgpu_trigger_भव_event(vgpu, DP_B_HOTPLUG);
		पूर्ण
		अगर (पूर्णांकel_vgpu_has_monitor_on_port(vgpu, PORT_C)) अणु
			अगर (connected) अणु
				vgpu_vreg_t(vgpu, GEN8_DE_PORT_ISR) |=
					GEN8_DE_PORT_HOTPLUG(HPD_PORT_C);
				vgpu_vreg_t(vgpu, SFUSE_STRAP) |=
					SFUSE_STRAP_DDIC_DETECTED;
			पूर्ण अन्यथा अणु
				vgpu_vreg_t(vgpu, GEN8_DE_PORT_ISR) &=
					~GEN8_DE_PORT_HOTPLUG(HPD_PORT_C);
				vgpu_vreg_t(vgpu, SFUSE_STRAP) &=
					~SFUSE_STRAP_DDIC_DETECTED;
			पूर्ण
			vgpu_vreg_t(vgpu, GEN8_DE_PORT_IIR) |=
				GEN8_DE_PORT_HOTPLUG(HPD_PORT_C);
			vgpu_vreg_t(vgpu, PCH_PORT_HOTPLUG) &=
				~PORTC_HOTPLUG_STATUS_MASK;
			vgpu_vreg_t(vgpu, PCH_PORT_HOTPLUG) |=
				PORTC_HOTPLUG_LONG_DETECT;
			पूर्णांकel_vgpu_trigger_भव_event(vgpu, DP_C_HOTPLUG);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_vgpu_clean_display - clean vGPU भव display emulation
 * @vgpu: a vGPU
 *
 * This function is used to clean vGPU भव display emulation stuffs
 *
 */
व्योम पूर्णांकel_vgpu_clean_display(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा drm_i915_निजी *dev_priv = vgpu->gvt->gt->i915;

	अगर (IS_SKYLAKE(dev_priv) ||
	    IS_KABYLAKE(dev_priv) ||
	    IS_COFFEELAKE(dev_priv) ||
	    IS_COMETLAKE(dev_priv))
		clean_भव_dp_monitor(vgpu, PORT_D);
	अन्यथा
		clean_भव_dp_monitor(vgpu, PORT_B);

	vgpu_update_vblank_emulation(vgpu, false);
पूर्ण

/**
 * पूर्णांकel_vgpu_init_display- initialize vGPU भव display emulation
 * @vgpu: a vGPU
 * @resolution: resolution index क्रम पूर्णांकel_vgpu_edid
 *
 * This function is used to initialize vGPU भव display emulation stuffs
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 *
 */
पूर्णांक पूर्णांकel_vgpu_init_display(काष्ठा पूर्णांकel_vgpu *vgpu, u64 resolution)
अणु
	काष्ठा drm_i915_निजी *dev_priv = vgpu->gvt->gt->i915;

	पूर्णांकel_vgpu_init_i2c_edid(vgpu);

	अगर (IS_SKYLAKE(dev_priv) ||
	    IS_KABYLAKE(dev_priv) ||
	    IS_COFFEELAKE(dev_priv) ||
	    IS_COMETLAKE(dev_priv))
		वापस setup_भव_dp_monitor(vgpu, PORT_D, GVT_DP_D,
						resolution);
	अन्यथा
		वापस setup_भव_dp_monitor(vgpu, PORT_B, GVT_DP_B,
						resolution);
पूर्ण

/**
 * पूर्णांकel_vgpu_reset_display- reset vGPU भव display emulation
 * @vgpu: a vGPU
 *
 * This function is used to reset vGPU भव display emulation stuffs
 *
 */
व्योम पूर्णांकel_vgpu_reset_display(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	emulate_monitor_status_change(vgpu);
पूर्ण
