<शैली गुरु>
/*
 * Copyright तऊ 2008 Intel Corporation
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Keith Packard <keithp@keithp.com>
 *
 */

#समावेश <linux/export.h>
#समावेश <linux/i2c.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/byteorder.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "g4x_dp.h"
#समावेश "i915_debugfs.h"
#समावेश "i915_drv.h"
#समावेश "intel_atomic.h"
#समावेश "intel_audio.h"
#समावेश "intel_connector.h"
#समावेश "intel_ddi.h"
#समावेश "intel_display_types.h"
#समावेश "intel_dp.h"
#समावेश "intel_dp_aux.h"
#समावेश "intel_dp_link_training.h"
#समावेश "intel_dp_mst.h"
#समावेश "intel_dpll.h"
#समावेश "intel_dpio_phy.h"
#समावेश "intel_fifo_underrun.h"
#समावेश "intel_hdcp.h"
#समावेश "intel_hdmi.h"
#समावेश "intel_hotplug.h"
#समावेश "intel_lspcon.h"
#समावेश "intel_lvds.h"
#समावेश "intel_panel.h"
#समावेश "intel_pps.h"
#समावेश "intel_psr.h"
#समावेश "intel_sideband.h"
#समावेश "intel_tc.h"
#समावेश "intel_vdsc.h"
#समावेश "intel_vrr.h"

#घोषणा DP_DPRX_ESI_LEN 14

/* DP DSC throughput values used क्रम slice count calculations KPixels/s */
#घोषणा DP_DSC_PEAK_PIXEL_RATE			2720000
#घोषणा DP_DSC_MAX_ENC_THROUGHPUT_0		340000
#घोषणा DP_DSC_MAX_ENC_THROUGHPUT_1		400000

/* DP DSC FEC Overhead factor = 1/(0.972261) */
#घोषणा DP_DSC_FEC_OVERHEAD_FACTOR		972261

/* Compliance test status bits  */
#घोषणा INTEL_DP_RESOLUTION_SHIFT_MASK	0
#घोषणा INTEL_DP_RESOLUTION_PREFERRED	(1 << INTEL_DP_RESOLUTION_SHIFT_MASK)
#घोषणा INTEL_DP_RESOLUTION_STANDARD	(2 << INTEL_DP_RESOLUTION_SHIFT_MASK)
#घोषणा INTEL_DP_RESOLUTION_FAILSAFE	(3 << INTEL_DP_RESOLUTION_SHIFT_MASK)


/* Constants क्रम DP DSC configurations */
अटल स्थिर u8 valid_dsc_bpp[] = अणु6, 8, 10, 12, 15पूर्ण;

/* With Single pipe configuration, HW is capable of supporting maximum
 * of 4 slices per line.
 */
अटल स्थिर u8 valid_dsc_slicecount[] = अणु1, 2, 4पूर्ण;

/**
 * पूर्णांकel_dp_is_edp - is the given port attached to an eDP panel (either CPU or PCH)
 * @पूर्णांकel_dp: DP काष्ठा
 *
 * If a CPU or PCH DP output is attached to an eDP panel, this function
 * will वापस true, and false otherwise.
 */
bool पूर्णांकel_dp_is_edp(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);

	वापस dig_port->base.type == INTEL_OUTPUT_EDP;
पूर्ण

अटल व्योम पूर्णांकel_dp_unset_edid(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);

/* update sink rates from dpcd */
अटल व्योम पूर्णांकel_dp_set_sink_rates(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	अटल स्थिर पूर्णांक dp_rates[] = अणु
		162000, 270000, 540000, 810000
	पूर्ण;
	पूर्णांक i, max_rate;
	पूर्णांक max_lttpr_rate;

	अगर (drm_dp_has_quirk(&पूर्णांकel_dp->desc, DP_DPCD_QUIRK_CAN_DO_MAX_LINK_RATE_3_24_GBPS)) अणु
		/* Needed, e.g., क्रम Apple MBP 2017, 15 inch eDP Retina panel */
		अटल स्थिर पूर्णांक quirk_rates[] = अणु 162000, 270000, 324000 पूर्ण;

		स_नकल(पूर्णांकel_dp->sink_rates, quirk_rates, माप(quirk_rates));
		पूर्णांकel_dp->num_sink_rates = ARRAY_SIZE(quirk_rates);

		वापस;
	पूर्ण

	max_rate = drm_dp_bw_code_to_link_rate(पूर्णांकel_dp->dpcd[DP_MAX_LINK_RATE]);
	max_lttpr_rate = drm_dp_lttpr_max_link_rate(पूर्णांकel_dp->lttpr_common_caps);
	अगर (max_lttpr_rate)
		max_rate = min(max_rate, max_lttpr_rate);

	क्रम (i = 0; i < ARRAY_SIZE(dp_rates); i++) अणु
		अगर (dp_rates[i] > max_rate)
			अवरोध;
		पूर्णांकel_dp->sink_rates[i] = dp_rates[i];
	पूर्ण

	पूर्णांकel_dp->num_sink_rates = i;
पूर्ण

/* Get length of rates array potentially limited by max_rate. */
अटल पूर्णांक पूर्णांकel_dp_rate_limit_len(स्थिर पूर्णांक *rates, पूर्णांक len, पूर्णांक max_rate)
अणु
	पूर्णांक i;

	/* Limit results by potentially reduced max rate */
	क्रम (i = 0; i < len; i++) अणु
		अगर (rates[len - i - 1] <= max_rate)
			वापस len - i;
	पूर्ण

	वापस 0;
पूर्ण

/* Get length of common rates array potentially limited by max_rate. */
अटल पूर्णांक पूर्णांकel_dp_common_len_rate_limit(स्थिर काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					  पूर्णांक max_rate)
अणु
	वापस पूर्णांकel_dp_rate_limit_len(पूर्णांकel_dp->common_rates,
				       पूर्णांकel_dp->num_common_rates, max_rate);
पूर्ण

/* Theoretical max between source and sink */
अटल पूर्णांक पूर्णांकel_dp_max_common_rate(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	वापस पूर्णांकel_dp->common_rates[पूर्णांकel_dp->num_common_rates - 1];
पूर्ण

/* Theoretical max between source and sink */
अटल पूर्णांक पूर्णांकel_dp_max_common_lane_count(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	पूर्णांक source_max = dig_port->max_lanes;
	पूर्णांक sink_max = drm_dp_max_lane_count(पूर्णांकel_dp->dpcd);
	पूर्णांक fia_max = पूर्णांकel_tc_port_fia_max_lane_count(dig_port);
	पूर्णांक lttpr_max = drm_dp_lttpr_max_lane_count(पूर्णांकel_dp->lttpr_common_caps);

	अगर (lttpr_max)
		sink_max = min(sink_max, lttpr_max);

	वापस min3(source_max, sink_max, fia_max);
पूर्ण

पूर्णांक पूर्णांकel_dp_max_lane_count(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	वापस पूर्णांकel_dp->max_link_lane_count;
पूर्ण

पूर्णांक
पूर्णांकel_dp_link_required(पूर्णांक pixel_घड़ी, पूर्णांक bpp)
अणु
	/* pixel_घड़ी is in kHz, भागide bpp by 8 क्रम bit to Byte conversion */
	वापस DIV_ROUND_UP(pixel_घड़ी * bpp, 8);
पूर्ण

पूर्णांक
पूर्णांकel_dp_max_data_rate(पूर्णांक max_link_घड़ी, पूर्णांक max_lanes)
अणु
	/* max_link_घड़ी is the link symbol घड़ी (LS_Clk) in kHz and not the
	 * link rate that is generally expressed in Gbps. Since, 8 bits of data
	 * is transmitted every LS_Clk per lane, there is no need to account क्रम
	 * the channel encoding that is करोne in the PHY layer here.
	 */

	वापस max_link_घड़ी * max_lanes;
पूर्ण

bool पूर्णांकel_dp_can_bigjoiner(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा पूर्णांकel_digital_port *पूर्णांकel_dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_encoder *encoder = &पूर्णांकel_dig_port->base;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	वापस DISPLAY_VER(dev_priv) >= 12 ||
		(IS_DISPLAY_VER(dev_priv, 11) &&
		 encoder->port != PORT_A);
पूर्ण

अटल पूर्णांक cnl_max_source_rate(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dig_port->base.base.dev);
	क्रमागत port port = dig_port->base.port;

	u32 voltage = पूर्णांकel_de_पढ़ो(dev_priv, CNL_PORT_COMP_DW3) & VOLTAGE_INFO_MASK;

	/* Low voltage SKUs are limited to max of 5.4G */
	अगर (voltage == VOLTAGE_INFO_0_85V)
		वापस 540000;

	/* For this SKU 8.1G is supported in all ports */
	अगर (IS_CNL_WITH_PORT_F(dev_priv))
		वापस 810000;

	/* For other SKUs, max rate on ports A and D is 5.4G */
	अगर (port == PORT_A || port == PORT_D)
		वापस 540000;

	वापस 810000;
पूर्ण

अटल पूर्णांक icl_max_source_rate(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dig_port->base.base.dev);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, dig_port->base.port);

	अगर (पूर्णांकel_phy_is_combo(dev_priv, phy) &&
	    !पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		वापस 540000;

	वापस 810000;
पूर्ण

अटल पूर्णांक ehl_max_source_rate(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	अगर (पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		वापस 540000;

	वापस 810000;
पूर्ण

अटल व्योम
पूर्णांकel_dp_set_source_rates(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	/* The values must be in increasing order */
	अटल स्थिर पूर्णांक cnl_rates[] = अणु
		162000, 216000, 270000, 324000, 432000, 540000, 648000, 810000
	पूर्ण;
	अटल स्थिर पूर्णांक bxt_rates[] = अणु
		162000, 216000, 243000, 270000, 324000, 432000, 540000
	पूर्ण;
	अटल स्थिर पूर्णांक skl_rates[] = अणु
		162000, 216000, 270000, 324000, 432000, 540000
	पूर्ण;
	अटल स्थिर पूर्णांक hsw_rates[] = अणु
		162000, 270000, 540000
	पूर्ण;
	अटल स्थिर पूर्णांक g4x_rates[] = अणु
		162000, 270000
	पूर्ण;
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_encoder *encoder = &dig_port->base;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dig_port->base.base.dev);
	स्थिर पूर्णांक *source_rates;
	पूर्णांक size, max_rate = 0, vbt_max_rate;

	/* This should only be करोne once */
	drm_WARN_ON(&dev_priv->drm,
		    पूर्णांकel_dp->source_rates || पूर्णांकel_dp->num_source_rates);

	अगर (DISPLAY_VER(dev_priv) >= 11 || IS_CANNONLAKE(dev_priv)) अणु
		source_rates = cnl_rates;
		size = ARRAY_SIZE(cnl_rates);
		अगर (IS_DISPLAY_VER(dev_priv, 10))
			max_rate = cnl_max_source_rate(पूर्णांकel_dp);
		अन्यथा अगर (IS_JSL_EHL(dev_priv))
			max_rate = ehl_max_source_rate(पूर्णांकel_dp);
		अन्यथा
			max_rate = icl_max_source_rate(पूर्णांकel_dp);
	पूर्ण अन्यथा अगर (IS_GEN9_LP(dev_priv)) अणु
		source_rates = bxt_rates;
		size = ARRAY_SIZE(bxt_rates);
	पूर्ण अन्यथा अगर (IS_GEN9_BC(dev_priv)) अणु
		source_rates = skl_rates;
		size = ARRAY_SIZE(skl_rates);
	पूर्ण अन्यथा अगर ((IS_HASWELL(dev_priv) && !IS_HSW_ULX(dev_priv)) ||
		   IS_BROADWELL(dev_priv)) अणु
		source_rates = hsw_rates;
		size = ARRAY_SIZE(hsw_rates);
	पूर्ण अन्यथा अणु
		source_rates = g4x_rates;
		size = ARRAY_SIZE(g4x_rates);
	पूर्ण

	vbt_max_rate = पूर्णांकel_bios_dp_max_link_rate(encoder);
	अगर (max_rate && vbt_max_rate)
		max_rate = min(max_rate, vbt_max_rate);
	अन्यथा अगर (vbt_max_rate)
		max_rate = vbt_max_rate;

	अगर (max_rate)
		size = पूर्णांकel_dp_rate_limit_len(source_rates, size, max_rate);

	पूर्णांकel_dp->source_rates = source_rates;
	पूर्णांकel_dp->num_source_rates = size;
पूर्ण

अटल पूर्णांक पूर्णांकersect_rates(स्थिर पूर्णांक *source_rates, पूर्णांक source_len,
			   स्थिर पूर्णांक *sink_rates, पूर्णांक sink_len,
			   पूर्णांक *common_rates)
अणु
	पूर्णांक i = 0, j = 0, k = 0;

	जबतक (i < source_len && j < sink_len) अणु
		अगर (source_rates[i] == sink_rates[j]) अणु
			अगर (WARN_ON(k >= DP_MAX_SUPPORTED_RATES))
				वापस k;
			common_rates[k] = source_rates[i];
			++k;
			++i;
			++j;
		पूर्ण अन्यथा अगर (source_rates[i] < sink_rates[j]) अणु
			++i;
		पूर्ण अन्यथा अणु
			++j;
		पूर्ण
	पूर्ण
	वापस k;
पूर्ण

/* वापस index of rate in rates array, or -1 अगर not found */
अटल पूर्णांक पूर्णांकel_dp_rate_index(स्थिर पूर्णांक *rates, पूर्णांक len, पूर्णांक rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		अगर (rate == rates[i])
			वापस i;

	वापस -1;
पूर्ण

अटल व्योम पूर्णांकel_dp_set_common_rates(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);

	drm_WARN_ON(&i915->drm,
		    !पूर्णांकel_dp->num_source_rates || !पूर्णांकel_dp->num_sink_rates);

	पूर्णांकel_dp->num_common_rates = पूर्णांकersect_rates(पूर्णांकel_dp->source_rates,
						     पूर्णांकel_dp->num_source_rates,
						     पूर्णांकel_dp->sink_rates,
						     पूर्णांकel_dp->num_sink_rates,
						     पूर्णांकel_dp->common_rates);

	/* Paranoia, there should always be something in common. */
	अगर (drm_WARN_ON(&i915->drm, पूर्णांकel_dp->num_common_rates == 0)) अणु
		पूर्णांकel_dp->common_rates[0] = 162000;
		पूर्णांकel_dp->num_common_rates = 1;
	पूर्ण
पूर्ण

अटल bool पूर्णांकel_dp_link_params_valid(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, पूर्णांक link_rate,
				       u8 lane_count)
अणु
	/*
	 * FIXME: we need to synchronize the current link parameters with
	 * hardware पढ़ोout. Currently fast link training करोesn't work on
	 * boot-up.
	 */
	अगर (link_rate == 0 ||
	    link_rate > पूर्णांकel_dp->max_link_rate)
		वापस false;

	अगर (lane_count == 0 ||
	    lane_count > पूर्णांकel_dp_max_lane_count(पूर्णांकel_dp))
		वापस false;

	वापस true;
पूर्ण

अटल bool पूर्णांकel_dp_can_link_train_fallback_क्रम_edp(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
						     पूर्णांक link_rate,
						     u8 lane_count)
अणु
	स्थिर काष्ठा drm_display_mode *fixed_mode =
		पूर्णांकel_dp->attached_connector->panel.fixed_mode;
	पूर्णांक mode_rate, max_rate;

	mode_rate = पूर्णांकel_dp_link_required(fixed_mode->घड़ी, 18);
	max_rate = पूर्णांकel_dp_max_data_rate(link_rate, lane_count);
	अगर (mode_rate > max_rate)
		वापस false;

	वापस true;
पूर्ण

पूर्णांक पूर्णांकel_dp_get_link_train_fallback_values(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					    पूर्णांक link_rate, u8 lane_count)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	पूर्णांक index;

	/*
	 * TODO: Enable fallback on MST links once MST link compute can handle
	 * the fallback params.
	 */
	अगर (पूर्णांकel_dp->is_mst) अणु
		drm_err(&i915->drm, "Link Training Unsuccessful\n");
		वापस -1;
	पूर्ण

	अगर (पूर्णांकel_dp_is_edp(पूर्णांकel_dp) && !पूर्णांकel_dp->use_max_params) अणु
		drm_dbg_kms(&i915->drm,
			    "Retrying Link training for eDP with max parameters\n");
		पूर्णांकel_dp->use_max_params = true;
		वापस 0;
	पूर्ण

	index = पूर्णांकel_dp_rate_index(पूर्णांकel_dp->common_rates,
				    पूर्णांकel_dp->num_common_rates,
				    link_rate);
	अगर (index > 0) अणु
		अगर (पूर्णांकel_dp_is_edp(पूर्णांकel_dp) &&
		    !पूर्णांकel_dp_can_link_train_fallback_क्रम_edp(पूर्णांकel_dp,
							      पूर्णांकel_dp->common_rates[index - 1],
							      lane_count)) अणु
			drm_dbg_kms(&i915->drm,
				    "Retrying Link training for eDP with same parameters\n");
			वापस 0;
		पूर्ण
		पूर्णांकel_dp->max_link_rate = पूर्णांकel_dp->common_rates[index - 1];
		पूर्णांकel_dp->max_link_lane_count = lane_count;
	पूर्ण अन्यथा अगर (lane_count > 1) अणु
		अगर (पूर्णांकel_dp_is_edp(पूर्णांकel_dp) &&
		    !पूर्णांकel_dp_can_link_train_fallback_क्रम_edp(पूर्णांकel_dp,
							      पूर्णांकel_dp_max_common_rate(पूर्णांकel_dp),
							      lane_count >> 1)) अणु
			drm_dbg_kms(&i915->drm,
				    "Retrying Link training for eDP with same parameters\n");
			वापस 0;
		पूर्ण
		पूर्णांकel_dp->max_link_rate = पूर्णांकel_dp_max_common_rate(पूर्णांकel_dp);
		पूर्णांकel_dp->max_link_lane_count = lane_count >> 1;
	पूर्ण अन्यथा अणु
		drm_err(&i915->drm, "Link Training Unsuccessful\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

u32 पूर्णांकel_dp_mode_to_fec_घड़ी(u32 mode_घड़ी)
अणु
	वापस भाग_u64(mul_u32_u32(mode_घड़ी, 1000000U),
		       DP_DSC_FEC_OVERHEAD_FACTOR);
पूर्ण

अटल पूर्णांक
small_joiner_ram_size_bits(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (DISPLAY_VER(i915) >= 11)
		वापस 7680 * 8;
	अन्यथा
		वापस 6144 * 8;
पूर्ण

अटल u16 पूर्णांकel_dp_dsc_get_output_bpp(काष्ठा drm_i915_निजी *i915,
				       u32 link_घड़ी, u32 lane_count,
				       u32 mode_घड़ी, u32 mode_hdisplay,
				       bool bigjoiner)
अणु
	u32 bits_per_pixel, max_bpp_small_joiner_ram;
	पूर्णांक i;

	/*
	 * Available Link Bandwidth(Kbits/sec) = (NumberOfLanes)*
	 * (LinkSymbolClock)* 8 * (TimeSlotsPerMTP)
	 * क्रम SST -> TimeSlotsPerMTP is 1,
	 * क्रम MST -> TimeSlotsPerMTP has to be calculated
	 */
	bits_per_pixel = (link_घड़ी * lane_count * 8) /
			 पूर्णांकel_dp_mode_to_fec_घड़ी(mode_घड़ी);
	drm_dbg_kms(&i915->drm, "Max link bpp: %u\n", bits_per_pixel);

	/* Small Joiner Check: output bpp <= joiner RAM (bits) / Horiz. width */
	max_bpp_small_joiner_ram = small_joiner_ram_size_bits(i915) /
		mode_hdisplay;

	अगर (bigjoiner)
		max_bpp_small_joiner_ram *= 2;

	drm_dbg_kms(&i915->drm, "Max small joiner bpp: %u\n",
		    max_bpp_small_joiner_ram);

	/*
	 * Greatest allowed DSC BPP = MIN (output BPP from available Link BW
	 * check, output bpp from small joiner RAM check)
	 */
	bits_per_pixel = min(bits_per_pixel, max_bpp_small_joiner_ram);

	अगर (bigjoiner) अणु
		u32 max_bpp_bigjoiner =
			i915->max_cdclk_freq * 48 /
			पूर्णांकel_dp_mode_to_fec_घड़ी(mode_घड़ी);

		DRM_DEBUG_KMS("Max big joiner bpp: %u\n", max_bpp_bigjoiner);
		bits_per_pixel = min(bits_per_pixel, max_bpp_bigjoiner);
	पूर्ण

	/* Error out अगर the max bpp is less than smallest allowed valid bpp */
	अगर (bits_per_pixel < valid_dsc_bpp[0]) अणु
		drm_dbg_kms(&i915->drm, "Unsupported BPP %u, min %u\n",
			    bits_per_pixel, valid_dsc_bpp[0]);
		वापस 0;
	पूर्ण

	/* Find the nearest match in the array of known BPPs from VESA */
	क्रम (i = 0; i < ARRAY_SIZE(valid_dsc_bpp) - 1; i++) अणु
		अगर (bits_per_pixel < valid_dsc_bpp[i + 1])
			अवरोध;
	पूर्ण
	bits_per_pixel = valid_dsc_bpp[i];

	/*
	 * Compressed BPP in U6.4 क्रमmat so multiply by 16, क्रम Gen 11,
	 * fractional part is 0
	 */
	वापस bits_per_pixel << 4;
पूर्ण

अटल u8 पूर्णांकel_dp_dsc_get_slice_count(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				       पूर्णांक mode_घड़ी, पूर्णांक mode_hdisplay,
				       bool bigjoiner)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	u8 min_slice_count, i;
	पूर्णांक max_slice_width;

	अगर (mode_घड़ी <= DP_DSC_PEAK_PIXEL_RATE)
		min_slice_count = DIV_ROUND_UP(mode_घड़ी,
					       DP_DSC_MAX_ENC_THROUGHPUT_0);
	अन्यथा
		min_slice_count = DIV_ROUND_UP(mode_घड़ी,
					       DP_DSC_MAX_ENC_THROUGHPUT_1);

	max_slice_width = drm_dp_dsc_sink_max_slice_width(पूर्णांकel_dp->dsc_dpcd);
	अगर (max_slice_width < DP_DSC_MIN_SLICE_WIDTH_VALUE) अणु
		drm_dbg_kms(&i915->drm,
			    "Unsupported slice width %d by DP DSC Sink device\n",
			    max_slice_width);
		वापस 0;
	पूर्ण
	/* Also take पूर्णांकo account max slice width */
	min_slice_count = max_t(u8, min_slice_count,
				DIV_ROUND_UP(mode_hdisplay,
					     max_slice_width));

	/* Find the बंदst match to the valid slice count values */
	क्रम (i = 0; i < ARRAY_SIZE(valid_dsc_slicecount); i++) अणु
		u8 test_slice_count = valid_dsc_slicecount[i] << bigjoiner;

		अगर (test_slice_count >
		    drm_dp_dsc_sink_max_slice_count(पूर्णांकel_dp->dsc_dpcd, false))
			अवरोध;

		/* big joiner needs small joiner to be enabled */
		अगर (bigjoiner && test_slice_count < 4)
			जारी;

		अगर (min_slice_count <= test_slice_count)
			वापस test_slice_count;
	पूर्ण

	drm_dbg_kms(&i915->drm, "Unsupported Slice Count %d\n",
		    min_slice_count);
	वापस 0;
पूर्ण

अटल क्रमागत पूर्णांकel_output_क्रमmat
पूर्णांकel_dp_output_क्रमmat(काष्ठा drm_connector *connector,
		       स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_attached_dp(to_पूर्णांकel_connector(connector));
	स्थिर काष्ठा drm_display_info *info = &connector->display_info;

	अगर (!connector->ycbcr_420_allowed ||
	    !drm_mode_is_420_only(info, mode))
		वापस INTEL_OUTPUT_FORMAT_RGB;

	अगर (पूर्णांकel_dp->dfp.rgb_to_ycbcr &&
	    पूर्णांकel_dp->dfp.ycbcr_444_to_420)
		वापस INTEL_OUTPUT_FORMAT_RGB;

	अगर (पूर्णांकel_dp->dfp.ycbcr_444_to_420)
		वापस INTEL_OUTPUT_FORMAT_YCBCR444;
	अन्यथा
		वापस INTEL_OUTPUT_FORMAT_YCBCR420;
पूर्ण

पूर्णांक पूर्णांकel_dp_min_bpp(क्रमागत पूर्णांकel_output_क्रमmat output_क्रमmat)
अणु
	अगर (output_क्रमmat == INTEL_OUTPUT_FORMAT_RGB)
		वापस 6 * 3;
	अन्यथा
		वापस 8 * 3;
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_output_bpp(क्रमागत पूर्णांकel_output_क्रमmat output_क्रमmat, पूर्णांक bpp)
अणु
	/*
	 * bpp value was assumed to RGB क्रमmat. And YCbCr 4:2:0 output
	 * क्रमmat of the number of bytes per pixel will be half the number
	 * of bytes of RGB pixel.
	 */
	अगर (output_क्रमmat == INTEL_OUTPUT_FORMAT_YCBCR420)
		bpp /= 2;

	वापस bpp;
पूर्ण

अटल पूर्णांक
पूर्णांकel_dp_mode_min_output_bpp(काष्ठा drm_connector *connector,
			     स्थिर काष्ठा drm_display_mode *mode)
अणु
	क्रमागत पूर्णांकel_output_क्रमmat output_क्रमmat =
		पूर्णांकel_dp_output_क्रमmat(connector, mode);

	वापस पूर्णांकel_dp_output_bpp(output_क्रमmat, पूर्णांकel_dp_min_bpp(output_क्रमmat));
पूर्ण

अटल bool पूर्णांकel_dp_hdisplay_bad(काष्ठा drm_i915_निजी *dev_priv,
				  पूर्णांक hdisplay)
अणु
	/*
	 * Older platक्रमms करोn't like hdisplay==4096 with DP.
	 *
	 * On ILK/SNB/IVB the pipe seems to be somewhat running (scanline
	 * and frame counter increment), but we करोn't get vblank पूर्णांकerrupts,
	 * and the pipe underruns immediately. The link also करोesn't seem
	 * to get trained properly.
	 *
	 * On CHV the vblank पूर्णांकerrupts करोn't seem to disappear but
	 * otherwise the symptoms are similar.
	 *
	 * TODO: confirm the behaviour on HSW+
	 */
	वापस hdisplay == 4096 && !HAS_DDI(dev_priv);
पूर्ण

अटल क्रमागत drm_mode_status
पूर्णांकel_dp_mode_valid_करोwnstream(काष्ठा पूर्णांकel_connector *connector,
			       स्थिर काष्ठा drm_display_mode *mode,
			       पूर्णांक target_घड़ी)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_attached_dp(connector);
	स्थिर काष्ठा drm_display_info *info = &connector->base.display_info;
	पूर्णांक पंचांगds_घड़ी;

	/* If PCON supports FRL MODE, check FRL bandwidth स्थिरraपूर्णांकs */
	अगर (पूर्णांकel_dp->dfp.pcon_max_frl_bw) अणु
		पूर्णांक target_bw;
		पूर्णांक max_frl_bw;
		पूर्णांक bpp = पूर्णांकel_dp_mode_min_output_bpp(&connector->base, mode);

		target_bw = bpp * target_घड़ी;

		max_frl_bw = पूर्णांकel_dp->dfp.pcon_max_frl_bw;

		/* converting bw from Gbps to Kbps*/
		max_frl_bw = max_frl_bw * 1000000;

		अगर (target_bw > max_frl_bw)
			वापस MODE_CLOCK_HIGH;

		वापस MODE_OK;
	पूर्ण

	अगर (पूर्णांकel_dp->dfp.max_करोtघड़ी &&
	    target_घड़ी > पूर्णांकel_dp->dfp.max_करोtघड़ी)
		वापस MODE_CLOCK_HIGH;

	/* Assume 8bpc क्रम the DP++/HDMI/DVI TMDS घड़ी check */
	पंचांगds_घड़ी = target_घड़ी;
	अगर (drm_mode_is_420_only(info, mode))
		पंचांगds_घड़ी /= 2;

	अगर (पूर्णांकel_dp->dfp.min_पंचांगds_घड़ी &&
	    पंचांगds_घड़ी < पूर्णांकel_dp->dfp.min_पंचांगds_घड़ी)
		वापस MODE_CLOCK_LOW;
	अगर (पूर्णांकel_dp->dfp.max_पंचांगds_घड़ी &&
	    पंचांगds_घड़ी > पूर्णांकel_dp->dfp.max_पंचांगds_घड़ी)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल क्रमागत drm_mode_status
पूर्णांकel_dp_mode_valid(काष्ठा drm_connector *connector,
		    काष्ठा drm_display_mode *mode)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_attached_dp(to_पूर्णांकel_connector(connector));
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = to_पूर्णांकel_connector(connector);
	काष्ठा drm_display_mode *fixed_mode = पूर्णांकel_connector->panel.fixed_mode;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->dev);
	पूर्णांक target_घड़ी = mode->घड़ी;
	पूर्णांक max_rate, mode_rate, max_lanes, max_link_घड़ी;
	पूर्णांक max_करोtclk = dev_priv->max_करोtclk_freq;
	u16 dsc_max_output_bpp = 0;
	u8 dsc_slice_count = 0;
	क्रमागत drm_mode_status status;
	bool dsc = false, bigjoiner = false;

	अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस MODE_NO_DBLESCAN;

	अगर (mode->flags & DRM_MODE_FLAG_DBLCLK)
		वापस MODE_H_ILLEGAL;

	अगर (पूर्णांकel_dp_is_edp(पूर्णांकel_dp) && fixed_mode) अणु
		अगर (mode->hdisplay != fixed_mode->hdisplay)
			वापस MODE_PANEL;

		अगर (mode->vdisplay != fixed_mode->vdisplay)
			वापस MODE_PANEL;

		target_घड़ी = fixed_mode->घड़ी;
	पूर्ण

	अगर (mode->घड़ी < 10000)
		वापस MODE_CLOCK_LOW;

	अगर ((target_घड़ी > max_करोtclk || mode->hdisplay > 5120) &&
	    पूर्णांकel_dp_can_bigjoiner(पूर्णांकel_dp)) अणु
		bigjoiner = true;
		max_करोtclk *= 2;
	पूर्ण
	अगर (target_घड़ी > max_करोtclk)
		वापस MODE_CLOCK_HIGH;

	max_link_घड़ी = पूर्णांकel_dp_max_link_rate(पूर्णांकel_dp);
	max_lanes = पूर्णांकel_dp_max_lane_count(पूर्णांकel_dp);

	max_rate = पूर्णांकel_dp_max_data_rate(max_link_घड़ी, max_lanes);
	mode_rate = पूर्णांकel_dp_link_required(target_घड़ी,
					   पूर्णांकel_dp_mode_min_output_bpp(connector, mode));

	अगर (पूर्णांकel_dp_hdisplay_bad(dev_priv, mode->hdisplay))
		वापस MODE_H_ILLEGAL;

	/*
	 * Output bpp is stored in 6.4 क्रमmat so right shअगरt by 4 to get the
	 * पूर्णांकeger value since we support only पूर्णांकeger values of bpp.
	 */
	अगर (DISPLAY_VER(dev_priv) >= 10 &&
	    drm_dp_sink_supports_dsc(पूर्णांकel_dp->dsc_dpcd)) अणु
		अगर (पूर्णांकel_dp_is_edp(पूर्णांकel_dp)) अणु
			dsc_max_output_bpp =
				drm_edp_dsc_sink_output_bpp(पूर्णांकel_dp->dsc_dpcd) >> 4;
			dsc_slice_count =
				drm_dp_dsc_sink_max_slice_count(पूर्णांकel_dp->dsc_dpcd,
								true);
		पूर्ण अन्यथा अगर (drm_dp_sink_supports_fec(पूर्णांकel_dp->fec_capable)) अणु
			dsc_max_output_bpp =
				पूर्णांकel_dp_dsc_get_output_bpp(dev_priv,
							    max_link_घड़ी,
							    max_lanes,
							    target_घड़ी,
							    mode->hdisplay,
							    bigjoiner) >> 4;
			dsc_slice_count =
				पूर्णांकel_dp_dsc_get_slice_count(पूर्णांकel_dp,
							     target_घड़ी,
							     mode->hdisplay,
							     bigjoiner);
		पूर्ण

		dsc = dsc_max_output_bpp && dsc_slice_count;
	पूर्ण

	/* big joiner configuration needs DSC */
	अगर (bigjoiner && !dsc)
		वापस MODE_CLOCK_HIGH;

	अगर (mode_rate > max_rate && !dsc)
		वापस MODE_CLOCK_HIGH;

	status = पूर्णांकel_dp_mode_valid_करोwnstream(पूर्णांकel_connector,
						mode, target_घड़ी);
	अगर (status != MODE_OK)
		वापस status;

	वापस पूर्णांकel_mode_valid_max_plane_size(dev_priv, mode, bigjoiner);
पूर्ण

bool पूर्णांकel_dp_source_supports_hbr2(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	पूर्णांक max_rate = पूर्णांकel_dp->source_rates[पूर्णांकel_dp->num_source_rates - 1];

	वापस max_rate >= 540000;
पूर्ण

bool पूर्णांकel_dp_source_supports_hbr3(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	पूर्णांक max_rate = पूर्णांकel_dp->source_rates[पूर्णांकel_dp->num_source_rates - 1];

	वापस max_rate >= 810000;
पूर्ण

अटल व्योम snम_लिखो_पूर्णांक_array(अक्षर *str, माप_प्रकार len,
			       स्थिर पूर्णांक *array, पूर्णांक nelem)
अणु
	पूर्णांक i;

	str[0] = '\0';

	क्रम (i = 0; i < nelem; i++) अणु
		पूर्णांक r = snम_लिखो(str, len, "%s%d", i ? ", " : "", array[i]);
		अगर (r >= len)
			वापस;
		str += r;
		len -= r;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_dp_prपूर्णांक_rates(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	अक्षर str[128]; /* FIXME: too big क्रम stack? */

	अगर (!drm_debug_enabled(DRM_UT_KMS))
		वापस;

	snम_लिखो_पूर्णांक_array(str, माप(str),
			   पूर्णांकel_dp->source_rates, पूर्णांकel_dp->num_source_rates);
	drm_dbg_kms(&i915->drm, "source rates: %s\n", str);

	snम_लिखो_पूर्णांक_array(str, माप(str),
			   पूर्णांकel_dp->sink_rates, पूर्णांकel_dp->num_sink_rates);
	drm_dbg_kms(&i915->drm, "sink rates: %s\n", str);

	snम_लिखो_पूर्णांक_array(str, माप(str),
			   पूर्णांकel_dp->common_rates, पूर्णांकel_dp->num_common_rates);
	drm_dbg_kms(&i915->drm, "common rates: %s\n", str);
पूर्ण

पूर्णांक
पूर्णांकel_dp_max_link_rate(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	पूर्णांक len;

	len = पूर्णांकel_dp_common_len_rate_limit(पूर्णांकel_dp, पूर्णांकel_dp->max_link_rate);
	अगर (drm_WARN_ON(&i915->drm, len <= 0))
		वापस 162000;

	वापस पूर्णांकel_dp->common_rates[len - 1];
पूर्ण

पूर्णांक पूर्णांकel_dp_rate_select(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, पूर्णांक rate)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	पूर्णांक i = पूर्णांकel_dp_rate_index(पूर्णांकel_dp->sink_rates,
				    पूर्णांकel_dp->num_sink_rates, rate);

	अगर (drm_WARN_ON(&i915->drm, i < 0))
		i = 0;

	वापस i;
पूर्ण

व्योम पूर्णांकel_dp_compute_rate(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, पूर्णांक port_घड़ी,
			   u8 *link_bw, u8 *rate_select)
अणु
	/* eDP 1.4 rate select method. */
	अगर (पूर्णांकel_dp->use_rate_select) अणु
		*link_bw = 0;
		*rate_select =
			पूर्णांकel_dp_rate_select(पूर्णांकel_dp, port_घड़ी);
	पूर्ण अन्यथा अणु
		*link_bw = drm_dp_link_rate_to_bw_code(port_घड़ी);
		*rate_select = 0;
	पूर्ण
पूर्ण

अटल bool पूर्णांकel_dp_source_supports_fec(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					 स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);

	/* On TGL, FEC is supported on all Pipes */
	अगर (DISPLAY_VER(dev_priv) >= 12)
		वापस true;

	अगर (IS_DISPLAY_VER(dev_priv, 11) && pipe_config->cpu_transcoder != TRANSCODER_A)
		वापस true;

	वापस false;
पूर्ण

अटल bool पूर्णांकel_dp_supports_fec(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	वापस पूर्णांकel_dp_source_supports_fec(पूर्णांकel_dp, pipe_config) &&
		drm_dp_sink_supports_fec(पूर्णांकel_dp->fec_capable);
पूर्ण

अटल bool पूर्णांकel_dp_supports_dsc(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_DP) && !crtc_state->fec_enable)
		वापस false;

	वापस पूर्णांकel_dsc_source_support(crtc_state) &&
		drm_dp_sink_supports_dsc(पूर्णांकel_dp->dsc_dpcd);
पूर्ण

अटल bool पूर्णांकel_dp_hdmi_ycbcr420(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	वापस crtc_state->output_क्रमmat == INTEL_OUTPUT_FORMAT_YCBCR420 ||
		(crtc_state->output_क्रमmat == INTEL_OUTPUT_FORMAT_YCBCR444 &&
		 पूर्णांकel_dp->dfp.ycbcr_444_to_420);
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_hdmi_पंचांगds_घड़ी(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state, पूर्णांक bpc)
अणु
	पूर्णांक घड़ी = crtc_state->hw.adjusted_mode.crtc_घड़ी * bpc / 8;

	अगर (पूर्णांकel_dp_hdmi_ycbcr420(पूर्णांकel_dp, crtc_state))
		घड़ी /= 2;

	वापस घड़ी;
पूर्ण

अटल bool पूर्णांकel_dp_hdmi_पंचांगds_घड़ी_valid(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state, पूर्णांक bpc)
अणु
	पूर्णांक पंचांगds_घड़ी = पूर्णांकel_dp_hdmi_पंचांगds_घड़ी(पूर्णांकel_dp, crtc_state, bpc);

	अगर (पूर्णांकel_dp->dfp.min_पंचांगds_घड़ी &&
	    पंचांगds_घड़ी < पूर्णांकel_dp->dfp.min_पंचांगds_घड़ी)
		वापस false;

	अगर (पूर्णांकel_dp->dfp.max_पंचांगds_घड़ी &&
	    पंचांगds_घड़ी > पूर्णांकel_dp->dfp.max_पंचांगds_घड़ी)
		वापस false;

	वापस true;
पूर्ण

अटल bool पूर्णांकel_dp_hdmi_deep_color_possible(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
					      पूर्णांक bpc)
अणु

	वापस पूर्णांकel_hdmi_deep_color_possible(crtc_state, bpc,
					      पूर्णांकel_dp->has_hdmi_sink,
					      पूर्णांकel_dp_hdmi_ycbcr420(पूर्णांकel_dp, crtc_state)) &&
		पूर्णांकel_dp_hdmi_पंचांगds_घड़ी_valid(पूर्णांकel_dp, crtc_state, bpc);
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_max_bpp(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = पूर्णांकel_dp->attached_connector;
	पूर्णांक bpp, bpc;

	bpc = crtc_state->pipe_bpp / 3;

	अगर (पूर्णांकel_dp->dfp.max_bpc)
		bpc = min_t(पूर्णांक, bpc, पूर्णांकel_dp->dfp.max_bpc);

	अगर (पूर्णांकel_dp->dfp.min_पंचांगds_घड़ी) अणु
		क्रम (; bpc >= 10; bpc -= 2) अणु
			अगर (पूर्णांकel_dp_hdmi_deep_color_possible(पूर्णांकel_dp, crtc_state, bpc))
				अवरोध;
		पूर्ण
	पूर्ण

	bpp = bpc * 3;
	अगर (पूर्णांकel_dp_is_edp(पूर्णांकel_dp)) अणु
		/* Get bpp from vbt only क्रम panels that करोnt have bpp in edid */
		अगर (पूर्णांकel_connector->base.display_info.bpc == 0 &&
		    dev_priv->vbt.edp.bpp && dev_priv->vbt.edp.bpp < bpp) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "clamping bpp for eDP panel to BIOS-provided %i\n",
				    dev_priv->vbt.edp.bpp);
			bpp = dev_priv->vbt.edp.bpp;
		पूर्ण
	पूर्ण

	वापस bpp;
पूर्ण

/* Adjust link config limits based on compliance test requests. */
व्योम
पूर्णांकel_dp_adjust_compliance_config(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				  काष्ठा पूर्णांकel_crtc_state *pipe_config,
				  काष्ठा link_config_limits *limits)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);

	/* For DP Compliance we override the computed bpp क्रम the pipe */
	अगर (पूर्णांकel_dp->compliance.test_data.bpc != 0) अणु
		पूर्णांक bpp = 3 * पूर्णांकel_dp->compliance.test_data.bpc;

		limits->min_bpp = limits->max_bpp = bpp;
		pipe_config->dither_क्रमce_disable = bpp == 6 * 3;

		drm_dbg_kms(&i915->drm, "Setting pipe_bpp to %d\n", bpp);
	पूर्ण

	/* Use values requested by Compliance Test Request */
	अगर (पूर्णांकel_dp->compliance.test_type == DP_TEST_LINK_TRAINING) अणु
		पूर्णांक index;

		/* Validate the compliance test data since max values
		 * might have changed due to link train fallback.
		 */
		अगर (पूर्णांकel_dp_link_params_valid(पूर्णांकel_dp, पूर्णांकel_dp->compliance.test_link_rate,
					       पूर्णांकel_dp->compliance.test_lane_count)) अणु
			index = पूर्णांकel_dp_rate_index(पूर्णांकel_dp->common_rates,
						    पूर्णांकel_dp->num_common_rates,
						    पूर्णांकel_dp->compliance.test_link_rate);
			अगर (index >= 0)
				limits->min_घड़ी = limits->max_घड़ी = index;
			limits->min_lane_count = limits->max_lane_count =
				पूर्णांकel_dp->compliance.test_lane_count;
		पूर्ण
	पूर्ण
पूर्ण

/* Optimize link config in order: max bpp, min घड़ी, min lanes */
अटल पूर्णांक
पूर्णांकel_dp_compute_link_config_wide(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				  काष्ठा पूर्णांकel_crtc_state *pipe_config,
				  स्थिर काष्ठा link_config_limits *limits)
अणु
	काष्ठा drm_display_mode *adjusted_mode = &pipe_config->hw.adjusted_mode;
	पूर्णांक bpp, घड़ी, lane_count;
	पूर्णांक mode_rate, link_घड़ी, link_avail;

	क्रम (bpp = limits->max_bpp; bpp >= limits->min_bpp; bpp -= 2 * 3) अणु
		पूर्णांक output_bpp = पूर्णांकel_dp_output_bpp(pipe_config->output_क्रमmat, bpp);

		mode_rate = पूर्णांकel_dp_link_required(adjusted_mode->crtc_घड़ी,
						   output_bpp);

		क्रम (घड़ी = limits->min_घड़ी; घड़ी <= limits->max_घड़ी; घड़ी++) अणु
			क्रम (lane_count = limits->min_lane_count;
			     lane_count <= limits->max_lane_count;
			     lane_count <<= 1) अणु
				link_घड़ी = पूर्णांकel_dp->common_rates[घड़ी];
				link_avail = पूर्णांकel_dp_max_data_rate(link_घड़ी,
								    lane_count);

				अगर (mode_rate <= link_avail) अणु
					pipe_config->lane_count = lane_count;
					pipe_config->pipe_bpp = bpp;
					pipe_config->port_घड़ी = link_घड़ी;

					वापस 0;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_dsc_compute_bpp(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, u8 dsc_max_bpc)
अणु
	पूर्णांक i, num_bpc;
	u8 dsc_bpc[3] = अणु0पूर्ण;

	num_bpc = drm_dp_dsc_sink_supported_input_bpcs(पूर्णांकel_dp->dsc_dpcd,
						       dsc_bpc);
	क्रम (i = 0; i < num_bpc; i++) अणु
		अगर (dsc_max_bpc >= dsc_bpc[i])
			वापस dsc_bpc[i] * 3;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा DSC_SUPPORTED_VERSION_MIN		1

अटल पूर्णांक पूर्णांकel_dp_dsc_compute_params(काष्ठा पूर्णांकel_encoder *encoder,
				       काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	काष्ठा drm_dsc_config *vdsc_cfg = &crtc_state->dsc.config;
	u8 line_buf_depth;
	पूर्णांक ret;

	/*
	 * RC_MODEL_SIZE is currently a स्थिरant across all configurations.
	 *
	 * FIXME: Look पूर्णांकo using sink defined DPCD DP_DSC_RC_BUF_BLK_SIZE and
	 * DP_DSC_RC_BUF_SIZE क्रम this.
	 */
	vdsc_cfg->rc_model_size = DSC_RC_MODEL_SIZE_CONST;

	ret = पूर्णांकel_dsc_compute_params(encoder, crtc_state);
	अगर (ret)
		वापस ret;

	/*
	 * Slice Height of 8 works क्रम all currently available panels. So start
	 * with that अगर pic_height is an पूर्णांकegral multiple of 8. Eventually add
	 * logic to try multiple slice heights.
	 */
	अगर (vdsc_cfg->pic_height % 8 == 0)
		vdsc_cfg->slice_height = 8;
	अन्यथा अगर (vdsc_cfg->pic_height % 4 == 0)
		vdsc_cfg->slice_height = 4;
	अन्यथा
		vdsc_cfg->slice_height = 2;

	vdsc_cfg->dsc_version_major =
		(पूर्णांकel_dp->dsc_dpcd[DP_DSC_REV - DP_DSC_SUPPORT] &
		 DP_DSC_MAJOR_MASK) >> DP_DSC_MAJOR_SHIFT;
	vdsc_cfg->dsc_version_minor =
		min(DSC_SUPPORTED_VERSION_MIN,
		    (पूर्णांकel_dp->dsc_dpcd[DP_DSC_REV - DP_DSC_SUPPORT] &
		     DP_DSC_MINOR_MASK) >> DP_DSC_MINOR_SHIFT);

	vdsc_cfg->convert_rgb = पूर्णांकel_dp->dsc_dpcd[DP_DSC_DEC_COLOR_FORMAT_CAP - DP_DSC_SUPPORT] &
		DP_DSC_RGB;

	line_buf_depth = drm_dp_dsc_sink_line_buf_depth(पूर्णांकel_dp->dsc_dpcd);
	अगर (!line_buf_depth) अणु
		drm_dbg_kms(&i915->drm,
			    "DSC Sink Line Buffer Depth invalid\n");
		वापस -EINVAL;
	पूर्ण

	अगर (vdsc_cfg->dsc_version_minor == 2)
		vdsc_cfg->line_buf_depth = (line_buf_depth == DSC_1_2_MAX_LINEBUF_DEPTH_BITS) ?
			DSC_1_2_MAX_LINEBUF_DEPTH_VAL : line_buf_depth;
	अन्यथा
		vdsc_cfg->line_buf_depth = (line_buf_depth > DSC_1_1_MAX_LINEBUF_DEPTH_BITS) ?
			DSC_1_1_MAX_LINEBUF_DEPTH_BITS : line_buf_depth;

	vdsc_cfg->block_pred_enable =
		पूर्णांकel_dp->dsc_dpcd[DP_DSC_BLK_PREDICTION_SUPPORT - DP_DSC_SUPPORT] &
		DP_DSC_BLK_PREDICTION_IS_SUPPORTED;

	वापस drm_dsc_compute_rc_parameters(vdsc_cfg);
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_dsc_compute_config(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				       काष्ठा पूर्णांकel_crtc_state *pipe_config,
				       काष्ठा drm_connector_state *conn_state,
				       काष्ठा link_config_limits *limits)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dig_port->base.base.dev);
	स्थिर काष्ठा drm_display_mode *adjusted_mode =
		&pipe_config->hw.adjusted_mode;
	u8 dsc_max_bpc;
	पूर्णांक pipe_bpp;
	पूर्णांक ret;

	pipe_config->fec_enable = !पूर्णांकel_dp_is_edp(पूर्णांकel_dp) &&
		पूर्णांकel_dp_supports_fec(पूर्णांकel_dp, pipe_config);

	अगर (!पूर्णांकel_dp_supports_dsc(पूर्णांकel_dp, pipe_config))
		वापस -EINVAL;

	/* Max DSC Input BPC क्रम ICL is 10 and क्रम TGL+ is 12 */
	अगर (DISPLAY_VER(dev_priv) >= 12)
		dsc_max_bpc = min_t(u8, 12, conn_state->max_requested_bpc);
	अन्यथा
		dsc_max_bpc = min_t(u8, 10,
				    conn_state->max_requested_bpc);

	pipe_bpp = पूर्णांकel_dp_dsc_compute_bpp(पूर्णांकel_dp, dsc_max_bpc);

	/* Min Input BPC क्रम ICL+ is 8 */
	अगर (pipe_bpp < 8 * 3) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "No DSC support for less than 8bpc\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * For now enable DSC क्रम max bpp, max link rate, max lane count.
	 * Optimize this later क्रम the minimum possible link rate/lane count
	 * with DSC enabled क्रम the requested mode.
	 */
	pipe_config->pipe_bpp = pipe_bpp;
	pipe_config->port_घड़ी = पूर्णांकel_dp->common_rates[limits->max_घड़ी];
	pipe_config->lane_count = limits->max_lane_count;

	अगर (पूर्णांकel_dp_is_edp(पूर्णांकel_dp)) अणु
		pipe_config->dsc.compressed_bpp =
			min_t(u16, drm_edp_dsc_sink_output_bpp(पूर्णांकel_dp->dsc_dpcd) >> 4,
			      pipe_config->pipe_bpp);
		pipe_config->dsc.slice_count =
			drm_dp_dsc_sink_max_slice_count(पूर्णांकel_dp->dsc_dpcd,
							true);
	पूर्ण अन्यथा अणु
		u16 dsc_max_output_bpp;
		u8 dsc_dp_slice_count;

		dsc_max_output_bpp =
			पूर्णांकel_dp_dsc_get_output_bpp(dev_priv,
						    pipe_config->port_घड़ी,
						    pipe_config->lane_count,
						    adjusted_mode->crtc_घड़ी,
						    adjusted_mode->crtc_hdisplay,
						    pipe_config->bigjoiner);
		dsc_dp_slice_count =
			पूर्णांकel_dp_dsc_get_slice_count(पूर्णांकel_dp,
						     adjusted_mode->crtc_घड़ी,
						     adjusted_mode->crtc_hdisplay,
						     pipe_config->bigjoiner);
		अगर (!dsc_max_output_bpp || !dsc_dp_slice_count) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "Compressed BPP/Slice Count not supported\n");
			वापस -EINVAL;
		पूर्ण
		pipe_config->dsc.compressed_bpp = min_t(u16,
							       dsc_max_output_bpp >> 4,
							       pipe_config->pipe_bpp);
		pipe_config->dsc.slice_count = dsc_dp_slice_count;
	पूर्ण
	/*
	 * VDSC engine operates at 1 Pixel per घड़ी, so अगर peak pixel rate
	 * is greater than the maximum Cdघड़ी and अगर slice count is even
	 * then we need to use 2 VDSC instances.
	 */
	अगर (adjusted_mode->crtc_घड़ी > dev_priv->max_cdclk_freq ||
	    pipe_config->bigjoiner) अणु
		अगर (pipe_config->dsc.slice_count < 2) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "Cannot split stream to use 2 VDSC instances\n");
			वापस -EINVAL;
		पूर्ण

		pipe_config->dsc.dsc_split = true;
	पूर्ण

	ret = पूर्णांकel_dp_dsc_compute_params(&dig_port->base, pipe_config);
	अगर (ret < 0) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Cannot compute valid DSC parameters for Input Bpp = %d "
			    "Compressed BPP = %d\n",
			    pipe_config->pipe_bpp,
			    pipe_config->dsc.compressed_bpp);
		वापस ret;
	पूर्ण

	pipe_config->dsc.compression_enable = true;
	drm_dbg_kms(&dev_priv->drm, "DP DSC computed with Input Bpp = %d "
		    "Compressed Bpp = %d Slice Count = %d\n",
		    pipe_config->pipe_bpp,
		    pipe_config->dsc.compressed_bpp,
		    pipe_config->dsc.slice_count);

	वापस 0;
पूर्ण

अटल पूर्णांक
पूर्णांकel_dp_compute_link_config(काष्ठा पूर्णांकel_encoder *encoder,
			     काष्ठा पूर्णांकel_crtc_state *pipe_config,
			     काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	स्थिर काष्ठा drm_display_mode *adjusted_mode =
		&pipe_config->hw.adjusted_mode;
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	काष्ठा link_config_limits limits;
	पूर्णांक common_len;
	पूर्णांक ret;

	common_len = पूर्णांकel_dp_common_len_rate_limit(पूर्णांकel_dp,
						    पूर्णांकel_dp->max_link_rate);

	/* No common link rates between source and sink */
	drm_WARN_ON(encoder->base.dev, common_len <= 0);

	limits.min_घड़ी = 0;
	limits.max_घड़ी = common_len - 1;

	limits.min_lane_count = 1;
	limits.max_lane_count = पूर्णांकel_dp_max_lane_count(पूर्णांकel_dp);

	limits.min_bpp = पूर्णांकel_dp_min_bpp(pipe_config->output_क्रमmat);
	limits.max_bpp = पूर्णांकel_dp_max_bpp(पूर्णांकel_dp, pipe_config);

	अगर (पूर्णांकel_dp->use_max_params) अणु
		/*
		 * Use the maximum घड़ी and number of lanes the eDP panel
		 * advertizes being capable of in हाल the initial fast
		 * optimal params failed us. The panels are generally
		 * deचिन्हित to support only a single घड़ी and lane
		 * configuration, and typically on older panels these
		 * values correspond to the native resolution of the panel.
		 */
		limits.min_lane_count = limits.max_lane_count;
		limits.min_घड़ी = limits.max_घड़ी;
	पूर्ण

	पूर्णांकel_dp_adjust_compliance_config(पूर्णांकel_dp, pipe_config, &limits);

	drm_dbg_kms(&i915->drm, "DP link computation with max lane count %i "
		    "max rate %d max bpp %d pixel clock %iKHz\n",
		    limits.max_lane_count,
		    पूर्णांकel_dp->common_rates[limits.max_घड़ी],
		    limits.max_bpp, adjusted_mode->crtc_घड़ी);

	अगर ((adjusted_mode->crtc_घड़ी > i915->max_करोtclk_freq ||
	     adjusted_mode->crtc_hdisplay > 5120) &&
	    पूर्णांकel_dp_can_bigjoiner(पूर्णांकel_dp))
		pipe_config->bigjoiner = true;

	/*
	 * Optimize क्रम slow and wide क्रम everything, because there are some
	 * eDP 1.3 and 1.4 panels करोn't work well with fast and narrow.
	 */
	ret = पूर्णांकel_dp_compute_link_config_wide(पूर्णांकel_dp, pipe_config, &limits);

	/* enable compression अगर the mode करोesn't fit available BW */
	drm_dbg_kms(&i915->drm, "Force DSC en = %d\n", पूर्णांकel_dp->क्रमce_dsc_en);
	अगर (ret || पूर्णांकel_dp->क्रमce_dsc_en || pipe_config->bigjoiner) अणु
		ret = पूर्णांकel_dp_dsc_compute_config(पूर्णांकel_dp, pipe_config,
						  conn_state, &limits);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (pipe_config->dsc.compression_enable) अणु
		drm_dbg_kms(&i915->drm,
			    "DP lane count %d clock %d Input bpp %d Compressed bpp %d\n",
			    pipe_config->lane_count, pipe_config->port_घड़ी,
			    pipe_config->pipe_bpp,
			    pipe_config->dsc.compressed_bpp);

		drm_dbg_kms(&i915->drm,
			    "DP link rate required %i available %i\n",
			    पूर्णांकel_dp_link_required(adjusted_mode->crtc_घड़ी,
						   pipe_config->dsc.compressed_bpp),
			    पूर्णांकel_dp_max_data_rate(pipe_config->port_घड़ी,
						   pipe_config->lane_count));
	पूर्ण अन्यथा अणु
		drm_dbg_kms(&i915->drm, "DP lane count %d clock %d bpp %d\n",
			    pipe_config->lane_count, pipe_config->port_घड़ी,
			    pipe_config->pipe_bpp);

		drm_dbg_kms(&i915->drm,
			    "DP link rate required %i available %i\n",
			    पूर्णांकel_dp_link_required(adjusted_mode->crtc_घड़ी,
						   pipe_config->pipe_bpp),
			    पूर्णांकel_dp_max_data_rate(pipe_config->port_घड़ी,
						   pipe_config->lane_count));
	पूर्ण
	वापस 0;
पूर्ण

bool पूर्णांकel_dp_limited_color_range(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	स्थिर काष्ठा पूर्णांकel_digital_connector_state *पूर्णांकel_conn_state =
		to_पूर्णांकel_digital_connector_state(conn_state);
	स्थिर काष्ठा drm_display_mode *adjusted_mode =
		&crtc_state->hw.adjusted_mode;

	/*
	 * Our YCbCr output is always limited range.
	 * crtc_state->limited_color_range only applies to RGB,
	 * and it must never be set क्रम YCbCr or we risk setting
	 * some conflicting bits in PIPECONF which will mess up
	 * the colors on the monitor.
	 */
	अगर (crtc_state->output_क्रमmat != INTEL_OUTPUT_FORMAT_RGB)
		वापस false;

	अगर (पूर्णांकel_conn_state->broadcast_rgb == INTEL_BROADCAST_RGB_AUTO) अणु
		/*
		 * See:
		 * CEA-861-E - 5.1 Default Encoding Parameters
		 * VESA DisplayPort Ver.1.2a - 5.1.1.1 Video Colorimetry
		 */
		वापस crtc_state->pipe_bpp != 18 &&
			drm_शेष_rgb_quant_range(adjusted_mode) ==
			HDMI_QUANTIZATION_RANGE_LIMITED;
	पूर्ण अन्यथा अणु
		वापस पूर्णांकel_conn_state->broadcast_rgb ==
			INTEL_BROADCAST_RGB_LIMITED;
	पूर्ण
पूर्ण

अटल bool पूर्णांकel_dp_port_has_audio(काष्ठा drm_i915_निजी *dev_priv,
				    क्रमागत port port)
अणु
	अगर (IS_G4X(dev_priv))
		वापस false;
	अगर (DISPLAY_VER(dev_priv) < 12 && port == PORT_A)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम पूर्णांकel_dp_compute_vsc_colorimetry(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
					     स्थिर काष्ठा drm_connector_state *conn_state,
					     काष्ठा drm_dp_vsc_sdp *vsc)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	/*
	 * Prepare VSC Header क्रम SU as per DP 1.4 spec, Table 2-118
	 * VSC SDP supporting 3D stereo, PSR2, and Pixel Encoding/
	 * Colorimetry Format indication.
	 */
	vsc->revision = 0x5;
	vsc->length = 0x13;

	/* DP 1.4a spec, Table 2-120 */
	चयन (crtc_state->output_क्रमmat) अणु
	हाल INTEL_OUTPUT_FORMAT_YCBCR444:
		vsc->pixelक्रमmat = DP_PIXELFORMAT_YUV444;
		अवरोध;
	हाल INTEL_OUTPUT_FORMAT_YCBCR420:
		vsc->pixelक्रमmat = DP_PIXELFORMAT_YUV420;
		अवरोध;
	हाल INTEL_OUTPUT_FORMAT_RGB:
	शेष:
		vsc->pixelक्रमmat = DP_PIXELFORMAT_RGB;
	पूर्ण

	चयन (conn_state->colorspace) अणु
	हाल DRM_MODE_COLORIMETRY_BT709_YCC:
		vsc->colorimetry = DP_COLORIMETRY_BT709_YCC;
		अवरोध;
	हाल DRM_MODE_COLORIMETRY_XVYCC_601:
		vsc->colorimetry = DP_COLORIMETRY_XVYCC_601;
		अवरोध;
	हाल DRM_MODE_COLORIMETRY_XVYCC_709:
		vsc->colorimetry = DP_COLORIMETRY_XVYCC_709;
		अवरोध;
	हाल DRM_MODE_COLORIMETRY_SYCC_601:
		vsc->colorimetry = DP_COLORIMETRY_SYCC_601;
		अवरोध;
	हाल DRM_MODE_COLORIMETRY_OPYCC_601:
		vsc->colorimetry = DP_COLORIMETRY_OPYCC_601;
		अवरोध;
	हाल DRM_MODE_COLORIMETRY_BT2020_CYCC:
		vsc->colorimetry = DP_COLORIMETRY_BT2020_CYCC;
		अवरोध;
	हाल DRM_MODE_COLORIMETRY_BT2020_RGB:
		vsc->colorimetry = DP_COLORIMETRY_BT2020_RGB;
		अवरोध;
	हाल DRM_MODE_COLORIMETRY_BT2020_YCC:
		vsc->colorimetry = DP_COLORIMETRY_BT2020_YCC;
		अवरोध;
	हाल DRM_MODE_COLORIMETRY_DCI_P3_RGB_D65:
	हाल DRM_MODE_COLORIMETRY_DCI_P3_RGB_THEATER:
		vsc->colorimetry = DP_COLORIMETRY_DCI_P3_RGB;
		अवरोध;
	शेष:
		/*
		 * RGB->YCBCR color conversion uses the BT.709
		 * color space.
		 */
		अगर (crtc_state->output_क्रमmat == INTEL_OUTPUT_FORMAT_YCBCR420)
			vsc->colorimetry = DP_COLORIMETRY_BT709_YCC;
		अन्यथा
			vsc->colorimetry = DP_COLORIMETRY_DEFAULT;
		अवरोध;
	पूर्ण

	vsc->bpc = crtc_state->pipe_bpp / 3;

	/* only RGB pixelक्रमmat supports 6 bpc */
	drm_WARN_ON(&dev_priv->drm,
		    vsc->bpc == 6 && vsc->pixelक्रमmat != DP_PIXELFORMAT_RGB);

	/* all YCbCr are always limited range */
	vsc->dynamic_range = DP_DYNAMIC_RANGE_CTA;
	vsc->content_type = DP_CONTENT_TYPE_NOT_DEFINED;
पूर्ण

अटल व्योम पूर्णांकel_dp_compute_vsc_sdp(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				     काष्ठा पूर्णांकel_crtc_state *crtc_state,
				     स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_dp_vsc_sdp *vsc = &crtc_state->infoframes.vsc;

	/* When a crtc state has PSR, VSC SDP will be handled by PSR routine */
	अगर (crtc_state->has_psr)
		वापस;

	अगर (!पूर्णांकel_dp_needs_vsc_sdp(crtc_state, conn_state))
		वापस;

	crtc_state->infoframes.enable |= पूर्णांकel_hdmi_infoframe_enable(DP_SDP_VSC);
	vsc->sdp_type = DP_SDP_VSC;
	पूर्णांकel_dp_compute_vsc_colorimetry(crtc_state, conn_state,
					 &crtc_state->infoframes.vsc);
पूर्ण

व्योम पूर्णांकel_dp_compute_psr_vsc_sdp(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  स्थिर काष्ठा drm_connector_state *conn_state,
				  काष्ठा drm_dp_vsc_sdp *vsc)
अणु
	vsc->sdp_type = DP_SDP_VSC;

	अगर (पूर्णांकel_dp->psr.psr2_enabled) अणु
		अगर (पूर्णांकel_dp->psr.colorimetry_support &&
		    पूर्णांकel_dp_needs_vsc_sdp(crtc_state, conn_state)) अणु
			/* [PSR2, +Colorimetry] */
			पूर्णांकel_dp_compute_vsc_colorimetry(crtc_state, conn_state,
							 vsc);
		पूर्ण अन्यथा अणु
			/*
			 * [PSR2, -Colorimetry]
			 * Prepare VSC Header क्रम SU as per eDP 1.4 spec, Table 6-11
			 * 3D stereo + PSR/PSR2 + Y-coordinate.
			 */
			vsc->revision = 0x4;
			vsc->length = 0xe;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * [PSR1]
		 * Prepare VSC Header क्रम SU as per DP 1.4 spec, Table 2-118
		 * VSC SDP supporting 3D stereo + PSR (applies to eDP v1.3 or
		 * higher).
		 */
		vsc->revision = 0x2;
		vsc->length = 0x8;
	पूर्ण
पूर्ण

अटल व्योम
पूर्णांकel_dp_compute_hdr_metadata_infoframe_sdp(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					    काष्ठा पूर्णांकel_crtc_state *crtc_state,
					    स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	पूर्णांक ret;
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा hdmi_drm_infoframe *drm_infoframe = &crtc_state->infoframes.drm.drm;

	अगर (!conn_state->hdr_output_metadata)
		वापस;

	ret = drm_hdmi_infoframe_set_hdr_metadata(drm_infoframe, conn_state);

	अगर (ret) अणु
		drm_dbg_kms(&dev_priv->drm, "couldn't set HDR metadata in infoframe\n");
		वापस;
	पूर्ण

	crtc_state->infoframes.enable |=
		पूर्णांकel_hdmi_infoframe_enable(HDMI_PACKET_TYPE_GAMUT_METADATA);
पूर्ण

अटल व्योम
पूर्णांकel_dp_drrs_compute_config(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			     काष्ठा पूर्णांकel_crtc_state *pipe_config,
			     पूर्णांक output_bpp, bool स्थिरant_n)
अणु
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = पूर्णांकel_dp->attached_connector;
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	पूर्णांक pixel_घड़ी;

	अगर (pipe_config->vrr.enable)
		वापस;

	/*
	 * DRRS and PSR can't be enable together, so giving preference to PSR
	 * as it allows more घातer-savings by complete shutting करोwn display,
	 * so to guarantee this, पूर्णांकel_dp_drrs_compute_config() must be called
	 * after पूर्णांकel_psr_compute_config().
	 */
	अगर (pipe_config->has_psr)
		वापस;

	अगर (!पूर्णांकel_connector->panel.करोwnघड़ी_mode ||
	    dev_priv->drrs.type != SEAMLESS_DRRS_SUPPORT)
		वापस;

	pipe_config->has_drrs = true;

	pixel_घड़ी = पूर्णांकel_connector->panel.करोwnघड़ी_mode->घड़ी;
	अगर (pipe_config->splitter.enable)
		pixel_घड़ी /= pipe_config->splitter.link_count;

	पूर्णांकel_link_compute_m_n(output_bpp, pipe_config->lane_count, pixel_घड़ी,
			       pipe_config->port_घड़ी, &pipe_config->dp_m2_n2,
			       स्थिरant_n, pipe_config->fec_enable);

	/* FIXME: असलtract this better */
	अगर (pipe_config->splitter.enable)
		pipe_config->dp_m2_n2.gmch_m *= pipe_config->splitter.link_count;
पूर्ण

पूर्णांक
पूर्णांकel_dp_compute_config(काष्ठा पूर्णांकel_encoder *encoder,
			काष्ठा पूर्णांकel_crtc_state *pipe_config,
			काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा drm_display_mode *adjusted_mode = &pipe_config->hw.adjusted_mode;
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	क्रमागत port port = encoder->port;
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = पूर्णांकel_dp->attached_connector;
	काष्ठा पूर्णांकel_digital_connector_state *पूर्णांकel_conn_state =
		to_पूर्णांकel_digital_connector_state(conn_state);
	bool स्थिरant_n = drm_dp_has_quirk(&पूर्णांकel_dp->desc, DP_DPCD_QUIRK_CONSTANT_N);
	पूर्णांक ret = 0, output_bpp;

	अगर (HAS_PCH_SPLIT(dev_priv) && !HAS_DDI(dev_priv) && port != PORT_A)
		pipe_config->has_pch_encoder = true;

	pipe_config->output_क्रमmat = पूर्णांकel_dp_output_क्रमmat(&पूर्णांकel_connector->base,
							    adjusted_mode);

	अगर (pipe_config->output_क्रमmat == INTEL_OUTPUT_FORMAT_YCBCR420) अणु
		ret = पूर्णांकel_pch_panel_fitting(pipe_config, conn_state);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!पूर्णांकel_dp_port_has_audio(dev_priv, port))
		pipe_config->has_audio = false;
	अन्यथा अगर (पूर्णांकel_conn_state->क्रमce_audio == HDMI_AUDIO_AUTO)
		pipe_config->has_audio = पूर्णांकel_dp->has_audio;
	अन्यथा
		pipe_config->has_audio = पूर्णांकel_conn_state->क्रमce_audio == HDMI_AUDIO_ON;

	अगर (पूर्णांकel_dp_is_edp(पूर्णांकel_dp) && पूर्णांकel_connector->panel.fixed_mode) अणु
		पूर्णांकel_fixed_panel_mode(पूर्णांकel_connector->panel.fixed_mode,
				       adjusted_mode);

		अगर (HAS_GMCH(dev_priv))
			ret = पूर्णांकel_gmch_panel_fitting(pipe_config, conn_state);
		अन्यथा
			ret = पूर्णांकel_pch_panel_fitting(pipe_config, conn_state);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (adjusted_mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस -EINVAL;

	अगर (HAS_GMCH(dev_priv) &&
	    adjusted_mode->flags & DRM_MODE_FLAG_INTERLACE)
		वापस -EINVAL;

	अगर (adjusted_mode->flags & DRM_MODE_FLAG_DBLCLK)
		वापस -EINVAL;

	अगर (पूर्णांकel_dp_hdisplay_bad(dev_priv, adjusted_mode->crtc_hdisplay))
		वापस -EINVAL;

	ret = पूर्णांकel_dp_compute_link_config(encoder, pipe_config, conn_state);
	अगर (ret < 0)
		वापस ret;

	pipe_config->limited_color_range =
		पूर्णांकel_dp_limited_color_range(pipe_config, conn_state);

	अगर (pipe_config->dsc.compression_enable)
		output_bpp = pipe_config->dsc.compressed_bpp;
	अन्यथा
		output_bpp = पूर्णांकel_dp_output_bpp(pipe_config->output_क्रमmat,
						 pipe_config->pipe_bpp);

	अगर (पूर्णांकel_dp->mso_link_count) अणु
		पूर्णांक n = पूर्णांकel_dp->mso_link_count;
		पूर्णांक overlap = पूर्णांकel_dp->mso_pixel_overlap;

		pipe_config->splitter.enable = true;
		pipe_config->splitter.link_count = n;
		pipe_config->splitter.pixel_overlap = overlap;

		drm_dbg_kms(&dev_priv->drm, "MSO link count %d, pixel overlap %d\n",
			    n, overlap);

		adjusted_mode->crtc_hdisplay = adjusted_mode->crtc_hdisplay / n + overlap;
		adjusted_mode->crtc_hblank_start = adjusted_mode->crtc_hblank_start / n + overlap;
		adjusted_mode->crtc_hblank_end = adjusted_mode->crtc_hblank_end / n + overlap;
		adjusted_mode->crtc_hsync_start = adjusted_mode->crtc_hsync_start / n + overlap;
		adjusted_mode->crtc_hsync_end = adjusted_mode->crtc_hsync_end / n + overlap;
		adjusted_mode->crtc_htotal = adjusted_mode->crtc_htotal / n + overlap;
		adjusted_mode->crtc_घड़ी /= n;
	पूर्ण

	पूर्णांकel_link_compute_m_n(output_bpp,
			       pipe_config->lane_count,
			       adjusted_mode->crtc_घड़ी,
			       pipe_config->port_घड़ी,
			       &pipe_config->dp_m_n,
			       स्थिरant_n, pipe_config->fec_enable);

	/* FIXME: असलtract this better */
	अगर (pipe_config->splitter.enable)
		pipe_config->dp_m_n.gmch_m *= pipe_config->splitter.link_count;

	अगर (!HAS_DDI(dev_priv))
		g4x_dp_set_घड़ी(encoder, pipe_config);

	पूर्णांकel_vrr_compute_config(pipe_config, conn_state);
	पूर्णांकel_psr_compute_config(पूर्णांकel_dp, pipe_config);
	पूर्णांकel_dp_drrs_compute_config(पूर्णांकel_dp, pipe_config, output_bpp,
				     स्थिरant_n);
	पूर्णांकel_dp_compute_vsc_sdp(पूर्णांकel_dp, pipe_config, conn_state);
	पूर्णांकel_dp_compute_hdr_metadata_infoframe_sdp(पूर्णांकel_dp, pipe_config, conn_state);

	वापस 0;
पूर्ण

व्योम पूर्णांकel_dp_set_link_params(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			      पूर्णांक link_rate, पूर्णांक lane_count)
अणु
	पूर्णांकel_dp->link_trained = false;
	पूर्णांकel_dp->link_rate = link_rate;
	पूर्णांकel_dp->lane_count = lane_count;
पूर्ण

/* Enable backlight PWM and backlight PP control. */
व्योम पूर्णांकel_edp_backlight_on(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(to_पूर्णांकel_encoder(conn_state->best_encoder));
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);

	अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		वापस;

	drm_dbg_kms(&i915->drm, "\n");

	पूर्णांकel_panel_enable_backlight(crtc_state, conn_state);
	पूर्णांकel_pps_backlight_on(पूर्णांकel_dp);
पूर्ण

/* Disable backlight PP control and backlight PWM. */
व्योम पूर्णांकel_edp_backlight_off(स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(to_पूर्णांकel_encoder(old_conn_state->best_encoder));
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);

	अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		वापस;

	drm_dbg_kms(&i915->drm, "\n");

	पूर्णांकel_pps_backlight_off(पूर्णांकel_dp);
	पूर्णांकel_panel_disable_backlight(old_conn_state);
पूर्ण

अटल bool करोwnstream_hpd_needs_d0(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	/*
	 * DPCD 1.2+ should support BRANCH_DEVICE_CTRL, and thus
	 * be capable of संकेतling करोwnstream hpd with a दीर्घ pulse.
	 * Whether or not that means D3 is safe to use is not clear,
	 * but let's assume so until proven otherwise.
	 *
	 * FIXME should really check all करोwnstream ports...
	 */
	वापस पूर्णांकel_dp->dpcd[DP_DPCD_REV] == 0x11 &&
		drm_dp_is_branch(पूर्णांकel_dp->dpcd) &&
		पूर्णांकel_dp->करोwnstream_ports[0] & DP_DS_PORT_HPD;
पूर्ण

व्योम पूर्णांकel_dp_sink_set_decompression_state(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
					   bool enable)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	पूर्णांक ret;

	अगर (!crtc_state->dsc.compression_enable)
		वापस;

	ret = drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux, DP_DSC_ENABLE,
				 enable ? DP_DECOMPRESSION_EN : 0);
	अगर (ret < 0)
		drm_dbg_kms(&i915->drm,
			    "Failed to %s sink decompression state\n",
			    enable ? "enable" : "disable");
पूर्ण

अटल व्योम
पूर्णांकel_edp_init_source_oui(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, bool careful)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	u8 oui[] = अणु 0x00, 0xaa, 0x01 पूर्ण;
	u8 buf[3] = अणु 0 पूर्ण;

	/*
	 * During driver init, we want to be careful and aव्योम changing the source OUI अगर it's
	 * alपढ़ोy set to what we want, so as to aव्योम clearing any state by accident
	 */
	अगर (careful) अणु
		अगर (drm_dp_dpcd_पढ़ो(&पूर्णांकel_dp->aux, DP_SOURCE_OUI, buf, माप(buf)) < 0)
			drm_err(&i915->drm, "Failed to read source OUI\n");

		अगर (स_भेद(oui, buf, माप(oui)) == 0)
			वापस;
	पूर्ण

	अगर (drm_dp_dpcd_ग_लिखो(&पूर्णांकel_dp->aux, DP_SOURCE_OUI, oui, माप(oui)) < 0)
		drm_err(&i915->drm, "Failed to write source OUI\n");
पूर्ण

/* If the device supports it, try to set the घातer state appropriately */
व्योम पूर्णांकel_dp_set_घातer(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, u8 mode)
अणु
	काष्ठा पूर्णांकel_encoder *encoder = &dp_to_dig_port(पूर्णांकel_dp)->base;
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	पूर्णांक ret, i;

	/* Should have a valid DPCD by this poपूर्णांक */
	अगर (पूर्णांकel_dp->dpcd[DP_DPCD_REV] < 0x11)
		वापस;

	अगर (mode != DP_SET_POWER_D0) अणु
		अगर (करोwnstream_hpd_needs_d0(पूर्णांकel_dp))
			वापस;

		ret = drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux, DP_SET_POWER, mode);
	पूर्ण अन्यथा अणु
		काष्ठा पूर्णांकel_lspcon *lspcon = dp_to_lspcon(पूर्णांकel_dp);

		lspcon_resume(dp_to_dig_port(पूर्णांकel_dp));

		/* Write the source OUI as early as possible */
		अगर (पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
			पूर्णांकel_edp_init_source_oui(पूर्णांकel_dp, false);

		/*
		 * When turning on, we need to retry क्रम 1ms to give the sink
		 * समय to wake up.
		 */
		क्रम (i = 0; i < 3; i++) अणु
			ret = drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux, DP_SET_POWER, mode);
			अगर (ret == 1)
				अवरोध;
			msleep(1);
		पूर्ण

		अगर (ret == 1 && lspcon->active)
			lspcon_रुको_pcon_mode(lspcon);
	पूर्ण

	अगर (ret != 1)
		drm_dbg_kms(&i915->drm, "[ENCODER:%d:%s] Set power to %s failed\n",
			    encoder->base.base.id, encoder->base.name,
			    mode == DP_SET_POWER_D0 ? "D0" : "D3");
पूर्ण

अटल bool
पूर्णांकel_dp_get_dpcd(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);

/**
 * पूर्णांकel_dp_sync_state - sync the encoder state during init/resume
 * @encoder: पूर्णांकel encoder to sync
 * @crtc_state: state क्रम the CRTC connected to the encoder
 *
 * Sync any state stored in the encoder wrt. HW state during driver init
 * and प्रणाली resume.
 */
व्योम पूर्णांकel_dp_sync_state(काष्ठा पूर्णांकel_encoder *encoder,
			 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);

	/*
	 * Don't clobber DPCD if it's been alपढ़ोy पढ़ो out during output
	 * setup (eDP) or detect.
	 */
	अगर (पूर्णांकel_dp->dpcd[DP_DPCD_REV] == 0)
		पूर्णांकel_dp_get_dpcd(पूर्णांकel_dp);

	पूर्णांकel_dp->max_link_lane_count = पूर्णांकel_dp_max_common_lane_count(पूर्णांकel_dp);
	पूर्णांकel_dp->max_link_rate = पूर्णांकel_dp_max_common_rate(पूर्णांकel_dp);
पूर्ण

bool पूर्णांकel_dp_initial_fastset_check(काष्ठा पूर्णांकel_encoder *encoder,
				    काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);

	/*
	 * If BIOS has set an unsupported or non-standard link rate क्रम some
	 * reason क्रमce an encoder recompute and full modeset.
	 */
	अगर (पूर्णांकel_dp_rate_index(पूर्णांकel_dp->source_rates, पूर्णांकel_dp->num_source_rates,
				crtc_state->port_घड़ी) < 0) अणु
		drm_dbg_kms(&i915->drm, "Forcing full modeset due to unsupported link rate\n");
		crtc_state->uapi.connectors_changed = true;
		वापस false;
	पूर्ण

	/*
	 * FIXME hack to क्रमce full modeset when DSC is being used.
	 *
	 * As दीर्घ as we करो not have full state पढ़ोout and config comparison
	 * of crtc_state->dsc, we have no way to ensure reliable fastset.
	 * Remove once we have पढ़ोout क्रम DSC.
	 */
	अगर (crtc_state->dsc.compression_enable) अणु
		drm_dbg_kms(&i915->drm, "Forcing full modeset due to DSC being enabled\n");
		crtc_state->uapi.mode_changed = true;
		वापस false;
	पूर्ण

	अगर (CAN_PSR(पूर्णांकel_dp)) अणु
		drm_dbg_kms(&i915->drm, "Forcing full modeset to compute PSR state\n");
		crtc_state->uapi.mode_changed = true;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम पूर्णांकel_dp_get_pcon_dsc_cap(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);

	/* Clear the cached रेजिस्टर set to aव्योम using stale values */

	स_रखो(पूर्णांकel_dp->pcon_dsc_dpcd, 0, माप(पूर्णांकel_dp->pcon_dsc_dpcd));

	अगर (drm_dp_dpcd_पढ़ो(&पूर्णांकel_dp->aux, DP_PCON_DSC_ENCODER,
			     पूर्णांकel_dp->pcon_dsc_dpcd,
			     माप(पूर्णांकel_dp->pcon_dsc_dpcd)) < 0)
		drm_err(&i915->drm, "Failed to read DPCD register 0x%x\n",
			DP_PCON_DSC_ENCODER);

	drm_dbg_kms(&i915->drm, "PCON ENCODER DSC DPCD: %*ph\n",
		    (पूर्णांक)माप(पूर्णांकel_dp->pcon_dsc_dpcd), पूर्णांकel_dp->pcon_dsc_dpcd);
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_pcon_get_frl_mask(u8 frl_bw_mask)
अणु
	पूर्णांक bw_gbps[] = अणु9, 18, 24, 32, 40, 48पूर्ण;
	पूर्णांक i;

	क्रम (i = ARRAY_SIZE(bw_gbps) - 1; i >= 0; i--) अणु
		अगर (frl_bw_mask & (1 << i))
			वापस bw_gbps[i];
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_pcon_set_frl_mask(पूर्णांक max_frl)
अणु
	चयन (max_frl) अणु
	हाल 48:
		वापस DP_PCON_FRL_BW_MASK_48GBPS;
	हाल 40:
		वापस DP_PCON_FRL_BW_MASK_40GBPS;
	हाल 32:
		वापस DP_PCON_FRL_BW_MASK_32GBPS;
	हाल 24:
		वापस DP_PCON_FRL_BW_MASK_24GBPS;
	हाल 18:
		वापस DP_PCON_FRL_BW_MASK_18GBPS;
	हाल 9:
		वापस DP_PCON_FRL_BW_MASK_9GBPS;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_hdmi_sink_max_frl(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = पूर्णांकel_dp->attached_connector;
	काष्ठा drm_connector *connector = &पूर्णांकel_connector->base;
	पूर्णांक max_frl_rate;
	पूर्णांक max_lanes, rate_per_lane;
	पूर्णांक max_dsc_lanes, dsc_rate_per_lane;

	max_lanes = connector->display_info.hdmi.max_lanes;
	rate_per_lane = connector->display_info.hdmi.max_frl_rate_per_lane;
	max_frl_rate = max_lanes * rate_per_lane;

	अगर (connector->display_info.hdmi.dsc_cap.v_1p2) अणु
		max_dsc_lanes = connector->display_info.hdmi.dsc_cap.max_lanes;
		dsc_rate_per_lane = connector->display_info.hdmi.dsc_cap.max_frl_rate_per_lane;
		अगर (max_dsc_lanes && dsc_rate_per_lane)
			max_frl_rate = min(max_frl_rate, max_dsc_lanes * dsc_rate_per_lane);
	पूर्ण

	वापस max_frl_rate;
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_pcon_start_frl_training(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
#घोषणा TIMEOUT_FRL_READY_MS 500
#घोषणा TIMEOUT_HDMI_LINK_ACTIVE_MS 1000

	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	पूर्णांक max_frl_bw, max_pcon_frl_bw, max_edid_frl_bw, ret;
	u8 max_frl_bw_mask = 0, frl_trained_mask;
	bool is_active;

	ret = drm_dp_pcon_reset_frl_config(&पूर्णांकel_dp->aux);
	अगर (ret < 0)
		वापस ret;

	max_pcon_frl_bw = पूर्णांकel_dp->dfp.pcon_max_frl_bw;
	drm_dbg(&i915->drm, "PCON max rate = %d Gbps\n", max_pcon_frl_bw);

	max_edid_frl_bw = पूर्णांकel_dp_hdmi_sink_max_frl(पूर्णांकel_dp);
	drm_dbg(&i915->drm, "Sink max rate from EDID = %d Gbps\n", max_edid_frl_bw);

	max_frl_bw = min(max_edid_frl_bw, max_pcon_frl_bw);

	अगर (max_frl_bw <= 0)
		वापस -EINVAL;

	ret = drm_dp_pcon_frl_prepare(&पूर्णांकel_dp->aux, false);
	अगर (ret < 0)
		वापस ret;
	/* Wait क्रम PCON to be FRL Ready */
	रुको_क्रम(is_active = drm_dp_pcon_is_frl_पढ़ोy(&पूर्णांकel_dp->aux) == true, TIMEOUT_FRL_READY_MS);

	अगर (!is_active)
		वापस -ETIMEDOUT;

	max_frl_bw_mask = पूर्णांकel_dp_pcon_set_frl_mask(max_frl_bw);
	ret = drm_dp_pcon_frl_configure_1(&पूर्णांकel_dp->aux, max_frl_bw,
					  DP_PCON_ENABLE_SEQUENTIAL_LINK);
	अगर (ret < 0)
		वापस ret;
	ret = drm_dp_pcon_frl_configure_2(&पूर्णांकel_dp->aux, max_frl_bw_mask,
					  DP_PCON_FRL_LINK_TRAIN_NORMAL);
	अगर (ret < 0)
		वापस ret;
	ret = drm_dp_pcon_frl_enable(&पूर्णांकel_dp->aux);
	अगर (ret < 0)
		वापस ret;
	/*
	 * Wait क्रम FRL to be completed
	 * Check अगर the HDMI Link is up and active.
	 */
	रुको_क्रम(is_active = drm_dp_pcon_hdmi_link_active(&पूर्णांकel_dp->aux) == true, TIMEOUT_HDMI_LINK_ACTIVE_MS);

	अगर (!is_active)
		वापस -ETIMEDOUT;

	/* Verअगरy HDMI Link configuration shows FRL Mode */
	अगर (drm_dp_pcon_hdmi_link_mode(&पूर्णांकel_dp->aux, &frl_trained_mask) !=
	    DP_PCON_HDMI_MODE_FRL) अणु
		drm_dbg(&i915->drm, "HDMI couldn't be trained in FRL Mode\n");
		वापस -EINVAL;
	पूर्ण
	drm_dbg(&i915->drm, "MAX_FRL_MASK = %u, FRL_TRAINED_MASK = %u\n", max_frl_bw_mask, frl_trained_mask);

	पूर्णांकel_dp->frl.trained_rate_gbps = पूर्णांकel_dp_pcon_get_frl_mask(frl_trained_mask);
	पूर्णांकel_dp->frl.is_trained = true;
	drm_dbg(&i915->drm, "FRL trained with : %d Gbps\n", पूर्णांकel_dp->frl.trained_rate_gbps);

	वापस 0;
पूर्ण

अटल bool पूर्णांकel_dp_is_hdmi_2_1_sink(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	अगर (drm_dp_is_branch(पूर्णांकel_dp->dpcd) &&
	    पूर्णांकel_dp->has_hdmi_sink &&
	    पूर्णांकel_dp_hdmi_sink_max_frl(पूर्णांकel_dp) > 0)
		वापस true;

	वापस false;
पूर्ण

व्योम पूर्णांकel_dp_check_frl_training(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);

	/*
	 * Always go क्रम FRL training अगर:
	 * -PCON supports SRC_CTL_MODE (VESA DP2.0-HDMI2.1 PCON Spec Draft-1 Sec-7)
	 * -sink is HDMI2.1
	 */
	अगर (!(पूर्णांकel_dp->करोwnstream_ports[2] & DP_PCON_SOURCE_CTL_MODE) ||
	    !पूर्णांकel_dp_is_hdmi_2_1_sink(पूर्णांकel_dp) ||
	    पूर्णांकel_dp->frl.is_trained)
		वापस;

	अगर (पूर्णांकel_dp_pcon_start_frl_training(पूर्णांकel_dp) < 0) अणु
		पूर्णांक ret, mode;

		drm_dbg(&dev_priv->drm, "Couldn't set FRL mode, continuing with TMDS mode\n");
		ret = drm_dp_pcon_reset_frl_config(&पूर्णांकel_dp->aux);
		mode = drm_dp_pcon_hdmi_link_mode(&पूर्णांकel_dp->aux, शून्य);

		अगर (ret < 0 || mode != DP_PCON_HDMI_MODE_TMDS)
			drm_dbg(&dev_priv->drm, "Issue with PCON, cannot set TMDS mode\n");
	पूर्ण अन्यथा अणु
		drm_dbg(&dev_priv->drm, "FRL training Completed\n");
	पूर्ण
पूर्ण

अटल पूर्णांक
पूर्णांकel_dp_pcon_dsc_enc_slice_height(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	पूर्णांक vactive = crtc_state->hw.adjusted_mode.vdisplay;

	वापस पूर्णांकel_hdmi_dsc_get_slice_height(vactive);
पूर्ण

अटल पूर्णांक
पूर्णांकel_dp_pcon_dsc_enc_slices(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = पूर्णांकel_dp->attached_connector;
	काष्ठा drm_connector *connector = &पूर्णांकel_connector->base;
	पूर्णांक hdmi_throughput = connector->display_info.hdmi.dsc_cap.clk_per_slice;
	पूर्णांक hdmi_max_slices = connector->display_info.hdmi.dsc_cap.max_slices;
	पूर्णांक pcon_max_slices = drm_dp_pcon_dsc_max_slices(पूर्णांकel_dp->pcon_dsc_dpcd);
	पूर्णांक pcon_max_slice_width = drm_dp_pcon_dsc_max_slice_width(पूर्णांकel_dp->pcon_dsc_dpcd);

	वापस पूर्णांकel_hdmi_dsc_get_num_slices(crtc_state, pcon_max_slices,
					     pcon_max_slice_width,
					     hdmi_max_slices, hdmi_throughput);
पूर्ण

अटल पूर्णांक
पूर्णांकel_dp_pcon_dsc_enc_bpp(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			  पूर्णांक num_slices, पूर्णांक slice_width)
अणु
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = पूर्णांकel_dp->attached_connector;
	काष्ठा drm_connector *connector = &पूर्णांकel_connector->base;
	पूर्णांक output_क्रमmat = crtc_state->output_क्रमmat;
	bool hdmi_all_bpp = connector->display_info.hdmi.dsc_cap.all_bpp;
	पूर्णांक pcon_fractional_bpp = drm_dp_pcon_dsc_bpp_incr(पूर्णांकel_dp->pcon_dsc_dpcd);
	पूर्णांक hdmi_max_chunk_bytes =
		connector->display_info.hdmi.dsc_cap.total_chunk_kbytes * 1024;

	वापस पूर्णांकel_hdmi_dsc_get_bpp(pcon_fractional_bpp, slice_width,
				      num_slices, output_क्रमmat, hdmi_all_bpp,
				      hdmi_max_chunk_bytes);
पूर्ण

व्योम
पूर्णांकel_dp_pcon_dsc_configure(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	u8 pps_param[6];
	पूर्णांक slice_height;
	पूर्णांक slice_width;
	पूर्णांक num_slices;
	पूर्णांक bits_per_pixel;
	पूर्णांक ret;
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = पूर्णांकel_dp->attached_connector;
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	काष्ठा drm_connector *connector;
	bool hdmi_is_dsc_1_2;

	अगर (!पूर्णांकel_dp_is_hdmi_2_1_sink(पूर्णांकel_dp))
		वापस;

	अगर (!पूर्णांकel_connector)
		वापस;
	connector = &पूर्णांकel_connector->base;
	hdmi_is_dsc_1_2 = connector->display_info.hdmi.dsc_cap.v_1p2;

	अगर (!drm_dp_pcon_enc_is_dsc_1_2(पूर्णांकel_dp->pcon_dsc_dpcd) ||
	    !hdmi_is_dsc_1_2)
		वापस;

	slice_height = पूर्णांकel_dp_pcon_dsc_enc_slice_height(crtc_state);
	अगर (!slice_height)
		वापस;

	num_slices = पूर्णांकel_dp_pcon_dsc_enc_slices(पूर्णांकel_dp, crtc_state);
	अगर (!num_slices)
		वापस;

	slice_width = DIV_ROUND_UP(crtc_state->hw.adjusted_mode.hdisplay,
				   num_slices);

	bits_per_pixel = पूर्णांकel_dp_pcon_dsc_enc_bpp(पूर्णांकel_dp, crtc_state,
						   num_slices, slice_width);
	अगर (!bits_per_pixel)
		वापस;

	pps_param[0] = slice_height & 0xFF;
	pps_param[1] = slice_height >> 8;
	pps_param[2] = slice_width & 0xFF;
	pps_param[3] = slice_width >> 8;
	pps_param[4] = bits_per_pixel & 0xFF;
	pps_param[5] = (bits_per_pixel >> 8) & 0x3;

	ret = drm_dp_pcon_pps_override_param(&पूर्णांकel_dp->aux, pps_param);
	अगर (ret < 0)
		drm_dbg_kms(&i915->drm, "Failed to set pcon DSC\n");
पूर्ण

व्योम पूर्णांकel_dp_configure_protocol_converter(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	u8 पंचांगp;

	अगर (पूर्णांकel_dp->dpcd[DP_DPCD_REV] < 0x13)
		वापस;

	अगर (!drm_dp_is_branch(पूर्णांकel_dp->dpcd))
		वापस;

	पंचांगp = पूर्णांकel_dp->has_hdmi_sink ?
		DP_HDMI_DVI_OUTPUT_CONFIG : 0;

	अगर (drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux,
			       DP_PROTOCOL_CONVERTER_CONTROL_0, पंचांगp) != 1)
		drm_dbg_kms(&i915->drm, "Failed to set protocol converter HDMI mode to %s\n",
			    enableddisabled(पूर्णांकel_dp->has_hdmi_sink));

	पंचांगp = crtc_state->output_क्रमmat == INTEL_OUTPUT_FORMAT_YCBCR444 &&
		पूर्णांकel_dp->dfp.ycbcr_444_to_420 ? DP_CONVERSION_TO_YCBCR420_ENABLE : 0;

	अगर (drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux,
			       DP_PROTOCOL_CONVERTER_CONTROL_1, पंचांगp) != 1)
		drm_dbg_kms(&i915->drm,
			    "Failed to set protocol converter YCbCr 4:2:0 conversion mode to %s\n",
			    enableddisabled(पूर्णांकel_dp->dfp.ycbcr_444_to_420));

	पंचांगp = 0;
	अगर (पूर्णांकel_dp->dfp.rgb_to_ycbcr) अणु
		bool bt2020, bt709;

		/*
		 * FIXME: Currently अगर userspace selects BT2020 or BT709, but PCON supports only
		 * RGB->YCbCr क्रम BT601 colorspace, we go ahead with BT601, as शेष.
		 *
		 */
		पंचांगp = DP_CONVERSION_BT601_RGB_YCBCR_ENABLE;

		bt2020 = drm_dp_करोwnstream_rgb_to_ycbcr_conversion(पूर्णांकel_dp->dpcd,
								   पूर्णांकel_dp->करोwnstream_ports,
								   DP_DS_HDMI_BT2020_RGB_YCBCR_CONV);
		bt709 = drm_dp_करोwnstream_rgb_to_ycbcr_conversion(पूर्णांकel_dp->dpcd,
								  पूर्णांकel_dp->करोwnstream_ports,
								  DP_DS_HDMI_BT709_RGB_YCBCR_CONV);
		चयन (crtc_state->infoframes.vsc.colorimetry) अणु
		हाल DP_COLORIMETRY_BT2020_RGB:
		हाल DP_COLORIMETRY_BT2020_YCC:
			अगर (bt2020)
				पंचांगp = DP_CONVERSION_BT2020_RGB_YCBCR_ENABLE;
			अवरोध;
		हाल DP_COLORIMETRY_BT709_YCC:
		हाल DP_COLORIMETRY_XVYCC_709:
			अगर (bt709)
				पंचांगp = DP_CONVERSION_BT709_RGB_YCBCR_ENABLE;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (drm_dp_pcon_convert_rgb_to_ycbcr(&पूर्णांकel_dp->aux, पंचांगp) < 0)
		drm_dbg_kms(&i915->drm,
			   "Failed to set protocol converter RGB->YCbCr conversion mode to %s\n",
			   enableddisabled(पंचांगp ? true : false));
पूर्ण


bool पूर्णांकel_dp_get_colorimetry_status(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	u8 dprx = 0;

	अगर (drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux, DP_DPRX_FEATURE_ENUMERATION_LIST,
			      &dprx) != 1)
		वापस false;
	वापस dprx & DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORTED;
पूर्ण

अटल व्योम पूर्णांकel_dp_get_dsc_sink_cap(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);

	/*
	 * Clear the cached रेजिस्टर set to aव्योम using stale values
	 * क्रम the sinks that करो not support DSC.
	 */
	स_रखो(पूर्णांकel_dp->dsc_dpcd, 0, माप(पूर्णांकel_dp->dsc_dpcd));

	/* Clear fec_capable to aव्योम using stale values */
	पूर्णांकel_dp->fec_capable = 0;

	/* Cache the DSC DPCD अगर eDP or DP rev >= 1.4 */
	अगर (पूर्णांकel_dp->dpcd[DP_DPCD_REV] >= 0x14 ||
	    पूर्णांकel_dp->edp_dpcd[0] >= DP_EDP_14) अणु
		अगर (drm_dp_dpcd_पढ़ो(&पूर्णांकel_dp->aux, DP_DSC_SUPPORT,
				     पूर्णांकel_dp->dsc_dpcd,
				     माप(पूर्णांकel_dp->dsc_dpcd)) < 0)
			drm_err(&i915->drm,
				"Failed to read DPCD register 0x%x\n",
				DP_DSC_SUPPORT);

		drm_dbg_kms(&i915->drm, "DSC DPCD: %*ph\n",
			    (पूर्णांक)माप(पूर्णांकel_dp->dsc_dpcd),
			    पूर्णांकel_dp->dsc_dpcd);

		/* FEC is supported only on DP 1.4 */
		अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp) &&
		    drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux, DP_FEC_CAPABILITY,
				      &पूर्णांकel_dp->fec_capable) < 0)
			drm_err(&i915->drm,
				"Failed to read FEC DPCD register\n");

		drm_dbg_kms(&i915->drm, "FEC CAPABILITY: %x\n",
			    पूर्णांकel_dp->fec_capable);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_edp_mso_mode_fixup(काष्ठा पूर्णांकel_connector *connector,
				     काष्ठा drm_display_mode *mode)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_attached_dp(connector);
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);
	पूर्णांक n = पूर्णांकel_dp->mso_link_count;
	पूर्णांक overlap = पूर्णांकel_dp->mso_pixel_overlap;

	अगर (!mode || !n)
		वापस;

	mode->hdisplay = (mode->hdisplay - overlap) * n;
	mode->hsync_start = (mode->hsync_start - overlap) * n;
	mode->hsync_end = (mode->hsync_end - overlap) * n;
	mode->htotal = (mode->htotal - overlap) * n;
	mode->घड़ी *= n;

	drm_mode_set_name(mode);

	drm_dbg_kms(&i915->drm,
		    "[CONNECTOR:%d:%s] using generated MSO mode: ",
		    connector->base.base.id, connector->base.name);
	drm_mode_debug_prपूर्णांकmodeline(mode);
पूर्ण

अटल व्योम पूर्णांकel_edp_mso_init(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	u8 mso;

	अगर (पूर्णांकel_dp->edp_dpcd[0] < DP_EDP_14)
		वापस;

	अगर (drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux, DP_EDP_MSO_LINK_CAPABILITIES, &mso) != 1) अणु
		drm_err(&i915->drm, "Failed to read MSO cap\n");
		वापस;
	पूर्ण

	/* Valid configurations are SST or MSO 2x1, 2x2, 4x1 */
	mso &= DP_EDP_MSO_NUMBER_OF_LINKS_MASK;
	अगर (mso % 2 || mso > drm_dp_max_lane_count(पूर्णांकel_dp->dpcd)) अणु
		drm_err(&i915->drm, "Invalid MSO link count cap %u\n", mso);
		mso = 0;
	पूर्ण

	अगर (mso) अणु
		drm_dbg_kms(&i915->drm, "Sink MSO %ux%u configuration\n",
			    mso, drm_dp_max_lane_count(पूर्णांकel_dp->dpcd) / mso);
		अगर (!HAS_MSO(i915)) अणु
			drm_err(&i915->drm, "No source MSO support, disabling\n");
			mso = 0;
		पूर्ण
	पूर्ण

	पूर्णांकel_dp->mso_link_count = mso;
	पूर्णांकel_dp->mso_pixel_overlap = 0; /* FIXME: पढ़ो from DisplayID v2.0 */
पूर्ण

अटल bool
पूर्णांकel_edp_init_dpcd(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		to_i915(dp_to_dig_port(पूर्णांकel_dp)->base.base.dev);

	/* this function is meant to be called only once */
	drm_WARN_ON(&dev_priv->drm, पूर्णांकel_dp->dpcd[DP_DPCD_REV] != 0);

	अगर (drm_dp_पढ़ो_dpcd_caps(&पूर्णांकel_dp->aux, पूर्णांकel_dp->dpcd) != 0)
		वापस false;

	drm_dp_पढ़ो_desc(&पूर्णांकel_dp->aux, &पूर्णांकel_dp->desc,
			 drm_dp_is_branch(पूर्णांकel_dp->dpcd));

	/*
	 * Read the eDP display control रेजिस्टरs.
	 *
	 * Do this independent of DP_DPCD_DISPLAY_CONTROL_CAPABLE bit in
	 * DP_EDP_CONFIGURATION_CAP, because some buggy displays करो not have it
	 * set, but require eDP 1.4+ detection (e.g. क्रम supported link rates
	 * method). The display control रेजिस्टरs should पढ़ो zero अगर they're
	 * not supported anyway.
	 */
	अगर (drm_dp_dpcd_पढ़ो(&पूर्णांकel_dp->aux, DP_EDP_DPCD_REV,
			     पूर्णांकel_dp->edp_dpcd, माप(पूर्णांकel_dp->edp_dpcd)) ==
			     माप(पूर्णांकel_dp->edp_dpcd))
		drm_dbg_kms(&dev_priv->drm, "eDP DPCD: %*ph\n",
			    (पूर्णांक)माप(पूर्णांकel_dp->edp_dpcd),
			    पूर्णांकel_dp->edp_dpcd);

	/*
	 * This has to be called after पूर्णांकel_dp->edp_dpcd is filled, PSR checks
	 * क्रम SET_POWER_CAPABLE bit in पूर्णांकel_dp->edp_dpcd[1]
	 */
	पूर्णांकel_psr_init_dpcd(पूर्णांकel_dp);

	/* Read the eDP 1.4+ supported link rates. */
	अगर (पूर्णांकel_dp->edp_dpcd[0] >= DP_EDP_14) अणु
		__le16 sink_rates[DP_MAX_SUPPORTED_RATES];
		पूर्णांक i;

		drm_dp_dpcd_पढ़ो(&पूर्णांकel_dp->aux, DP_SUPPORTED_LINK_RATES,
				sink_rates, माप(sink_rates));

		क्रम (i = 0; i < ARRAY_SIZE(sink_rates); i++) अणु
			पूर्णांक val = le16_to_cpu(sink_rates[i]);

			अगर (val == 0)
				अवरोध;

			/* Value पढ़ो multiplied by 200kHz gives the per-lane
			 * link rate in kHz. The source rates are, however,
			 * stored in terms of LS_Clk kHz. The full conversion
			 * back to symbols is
			 * (val * 200kHz)*(8/10 ch. encoding)*(1/8 bit to Byte)
			 */
			पूर्णांकel_dp->sink_rates[i] = (val * 200) / 10;
		पूर्ण
		पूर्णांकel_dp->num_sink_rates = i;
	पूर्ण

	/*
	 * Use DP_LINK_RATE_SET अगर DP_SUPPORTED_LINK_RATES are available,
	 * शेष to DP_MAX_LINK_RATE and DP_LINK_BW_SET otherwise.
	 */
	अगर (पूर्णांकel_dp->num_sink_rates)
		पूर्णांकel_dp->use_rate_select = true;
	अन्यथा
		पूर्णांकel_dp_set_sink_rates(पूर्णांकel_dp);

	पूर्णांकel_dp_set_common_rates(पूर्णांकel_dp);

	/* Read the eDP DSC DPCD रेजिस्टरs */
	अगर (DISPLAY_VER(dev_priv) >= 10)
		पूर्णांकel_dp_get_dsc_sink_cap(पूर्णांकel_dp);

	/*
	 * If needed, program our source OUI so we can make various Intel-specअगरic AUX services
	 * available (such as HDR backlight controls)
	 */
	पूर्णांकel_edp_init_source_oui(पूर्णांकel_dp, true);

	पूर्णांकel_edp_mso_init(पूर्णांकel_dp);

	वापस true;
पूर्ण

अटल bool
पूर्णांकel_dp_has_sink_count(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	अगर (!पूर्णांकel_dp->attached_connector)
		वापस false;

	वापस drm_dp_पढ़ो_sink_count_cap(&पूर्णांकel_dp->attached_connector->base,
					  पूर्णांकel_dp->dpcd,
					  &पूर्णांकel_dp->desc);
पूर्ण

अटल bool
पूर्णांकel_dp_get_dpcd(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	पूर्णांक ret;

	अगर (पूर्णांकel_dp_init_lttpr_and_dprx_caps(पूर्णांकel_dp) < 0)
		वापस false;

	/*
	 * Don't clobber cached eDP rates. Also skip re-पढ़ोing
	 * the OUI/ID since we know it won't change.
	 */
	अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp)) अणु
		drm_dp_पढ़ो_desc(&पूर्णांकel_dp->aux, &पूर्णांकel_dp->desc,
				 drm_dp_is_branch(पूर्णांकel_dp->dpcd));

		पूर्णांकel_dp_set_sink_rates(पूर्णांकel_dp);
		पूर्णांकel_dp_set_common_rates(पूर्णांकel_dp);
	पूर्ण

	अगर (पूर्णांकel_dp_has_sink_count(पूर्णांकel_dp)) अणु
		ret = drm_dp_पढ़ो_sink_count(&पूर्णांकel_dp->aux);
		अगर (ret < 0)
			वापस false;

		/*
		 * Sink count can change between लघु pulse hpd hence
		 * a member variable in पूर्णांकel_dp will track any changes
		 * between लघु pulse पूर्णांकerrupts.
		 */
		पूर्णांकel_dp->sink_count = ret;

		/*
		 * SINK_COUNT == 0 and DOWNSTREAM_PORT_PRESENT == 1 implies that
		 * a करोngle is present but no display. Unless we require to know
		 * अगर a करोngle is present or not, we करोn't need to update
		 * करोwnstream port inक्रमmation. So, an early वापस here saves
		 * समय from perक्रमming other operations which are not required.
		 */
		अगर (!पूर्णांकel_dp->sink_count)
			वापस false;
	पूर्ण

	वापस drm_dp_पढ़ो_करोwnstream_info(&पूर्णांकel_dp->aux, पूर्णांकel_dp->dpcd,
					   पूर्णांकel_dp->करोwnstream_ports) == 0;
पूर्ण

अटल bool
पूर्णांकel_dp_can_mst(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);

	वापस i915->params.enable_dp_mst &&
		पूर्णांकel_dp->can_mst &&
		drm_dp_पढ़ो_mst_cap(&पूर्णांकel_dp->aux, पूर्णांकel_dp->dpcd);
पूर्ण

अटल व्योम
पूर्णांकel_dp_configure_mst(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_encoder *encoder =
		&dp_to_dig_port(पूर्णांकel_dp)->base;
	bool sink_can_mst = drm_dp_पढ़ो_mst_cap(&पूर्णांकel_dp->aux, पूर्णांकel_dp->dpcd);

	drm_dbg_kms(&i915->drm,
		    "[ENCODER:%d:%s] MST support: port: %s, sink: %s, modparam: %s\n",
		    encoder->base.base.id, encoder->base.name,
		    yesno(पूर्णांकel_dp->can_mst), yesno(sink_can_mst),
		    yesno(i915->params.enable_dp_mst));

	अगर (!पूर्णांकel_dp->can_mst)
		वापस;

	पूर्णांकel_dp->is_mst = sink_can_mst &&
		i915->params.enable_dp_mst;

	drm_dp_mst_topology_mgr_set_mst(&पूर्णांकel_dp->mst_mgr,
					पूर्णांकel_dp->is_mst);
पूर्ण

अटल bool
पूर्णांकel_dp_get_sink_irq_esi(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, u8 *sink_irq_vector)
अणु
	वापस drm_dp_dpcd_पढ़ो(&पूर्णांकel_dp->aux, DP_SINK_COUNT_ESI,
				sink_irq_vector, DP_DPRX_ESI_LEN) ==
		DP_DPRX_ESI_LEN;
पूर्ण

bool
पूर्णांकel_dp_needs_vsc_sdp(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		       स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	/*
	 * As per DP 1.4a spec section 2.2.4.3 [MSA Field क्रम Indication
	 * of Color Encoding Format and Content Color Gamut], in order to
	 * sending YCBCR 420 or HDR BT.2020 संकेतs we should use DP VSC SDP.
	 */
	अगर (crtc_state->output_क्रमmat == INTEL_OUTPUT_FORMAT_YCBCR420)
		वापस true;

	चयन (conn_state->colorspace) अणु
	हाल DRM_MODE_COLORIMETRY_SYCC_601:
	हाल DRM_MODE_COLORIMETRY_OPYCC_601:
	हाल DRM_MODE_COLORIMETRY_BT2020_YCC:
	हाल DRM_MODE_COLORIMETRY_BT2020_RGB:
	हाल DRM_MODE_COLORIMETRY_BT2020_CYCC:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल sमाप_प्रकार पूर्णांकel_dp_vsc_sdp_pack(स्थिर काष्ठा drm_dp_vsc_sdp *vsc,
				     काष्ठा dp_sdp *sdp, माप_प्रकार size)
अणु
	माप_प्रकार length = माप(काष्ठा dp_sdp);

	अगर (size < length)
		वापस -ENOSPC;

	स_रखो(sdp, 0, size);

	/*
	 * Prepare VSC Header क्रम SU as per DP 1.4a spec, Table 2-119
	 * VSC SDP Header Bytes
	 */
	sdp->sdp_header.HB0 = 0; /* Secondary-Data Packet ID = 0 */
	sdp->sdp_header.HB1 = vsc->sdp_type; /* Secondary-data Packet Type */
	sdp->sdp_header.HB2 = vsc->revision; /* Revision Number */
	sdp->sdp_header.HB3 = vsc->length; /* Number of Valid Data Bytes */

	/*
	 * Only revision 0x5 supports Pixel Encoding/Colorimetry Format as
	 * per DP 1.4a spec.
	 */
	अगर (vsc->revision != 0x5)
		जाओ out;

	/* VSC SDP Payload क्रम DB16 through DB18 */
	/* Pixel Encoding and Colorimetry Formats  */
	sdp->db[16] = (vsc->pixelक्रमmat & 0xf) << 4; /* DB16[7:4] */
	sdp->db[16] |= vsc->colorimetry & 0xf; /* DB16[3:0] */

	चयन (vsc->bpc) अणु
	हाल 6:
		/* 6bpc: 0x0 */
		अवरोध;
	हाल 8:
		sdp->db[17] = 0x1; /* DB17[3:0] */
		अवरोध;
	हाल 10:
		sdp->db[17] = 0x2;
		अवरोध;
	हाल 12:
		sdp->db[17] = 0x3;
		अवरोध;
	हाल 16:
		sdp->db[17] = 0x4;
		अवरोध;
	शेष:
		MISSING_CASE(vsc->bpc);
		अवरोध;
	पूर्ण
	/* Dynamic Range and Component Bit Depth */
	अगर (vsc->dynamic_range == DP_DYNAMIC_RANGE_CTA)
		sdp->db[17] |= 0x80;  /* DB17[7] */

	/* Content Type */
	sdp->db[18] = vsc->content_type & 0x7;

out:
	वापस length;
पूर्ण

अटल sमाप_प्रकार
पूर्णांकel_dp_hdr_metadata_infoframe_sdp_pack(स्थिर काष्ठा hdmi_drm_infoframe *drm_infoframe,
					 काष्ठा dp_sdp *sdp,
					 माप_प्रकार size)
अणु
	माप_प्रकार length = माप(काष्ठा dp_sdp);
	स्थिर पूर्णांक infoframe_size = HDMI_INFOFRAME_HEADER_SIZE + HDMI_DRM_INFOFRAME_SIZE;
	अचिन्हित अक्षर buf[HDMI_INFOFRAME_HEADER_SIZE + HDMI_DRM_INFOFRAME_SIZE];
	sमाप_प्रकार len;

	अगर (size < length)
		वापस -ENOSPC;

	स_रखो(sdp, 0, size);

	len = hdmi_drm_infoframe_pack_only(drm_infoframe, buf, माप(buf));
	अगर (len < 0) अणु
		DRM_DEBUG_KMS("buffer size is smaller than hdr metadata infoframe\n");
		वापस -ENOSPC;
	पूर्ण

	अगर (len != infoframe_size) अणु
		DRM_DEBUG_KMS("wrong static hdr metadata size\n");
		वापस -ENOSPC;
	पूर्ण

	/*
	 * Set up the infoframe sdp packet क्रम HDR अटल metadata.
	 * Prepare VSC Header क्रम SU as per DP 1.4a spec,
	 * Table 2-100 and Table 2-101
	 */

	/* Secondary-Data Packet ID, 00h क्रम non-Audio INFOFRAME */
	sdp->sdp_header.HB0 = 0;
	/*
	 * Packet Type 80h + Non-audio INFOFRAME Type value
	 * HDMI_INFOFRAME_TYPE_DRM: 0x87
	 * - 80h + Non-audio INFOFRAME Type value
	 * - InfoFrame Type: 0x07
	 *    [CTA-861-G Table-42 Dynamic Range and Mastering InfoFrame]
	 */
	sdp->sdp_header.HB1 = drm_infoframe->type;
	/*
	 * Least Signअगरicant Eight Bits of (Data Byte Count ै  1)
	 * infoframe_size - 1
	 */
	sdp->sdp_header.HB2 = 0x1D;
	/* INFOFRAME SDP Version Number */
	sdp->sdp_header.HB3 = (0x13 << 2);
	/* CTA Header Byte 2 (INFOFRAME Version Number) */
	sdp->db[0] = drm_infoframe->version;
	/* CTA Header Byte 3 (Length of INFOFRAME): HDMI_DRM_INFOFRAME_SIZE */
	sdp->db[1] = drm_infoframe->length;
	/*
	 * Copy HDMI_DRM_INFOFRAME_SIZE size from a buffer after
	 * HDMI_INFOFRAME_HEADER_SIZE
	 */
	BUILD_BUG_ON(माप(sdp->db) < HDMI_DRM_INFOFRAME_SIZE + 2);
	स_नकल(&sdp->db[2], &buf[HDMI_INFOFRAME_HEADER_SIZE],
	       HDMI_DRM_INFOFRAME_SIZE);

	/*
	 * Size of DP infoframe sdp packet क्रम HDR अटल metadata consists of
	 * - DP SDP Header(काष्ठा dp_sdp_header): 4 bytes
	 * - Two Data Blocks: 2 bytes
	 *    CTA Header Byte2 (INFOFRAME Version Number)
	 *    CTA Header Byte3 (Length of INFOFRAME)
	 * - HDMI_DRM_INFOFRAME_SIZE: 26 bytes
	 *
	 * Prior to GEN11's GMP रेजिस्टर size is identical to DP HDR अटल metadata
	 * infoframe size. But GEN11+ has larger than that size, ग_लिखो_infoframe
	 * will pad rest of the size.
	 */
	वापस माप(काष्ठा dp_sdp_header) + 2 + HDMI_DRM_INFOFRAME_SIZE;
पूर्ण

अटल व्योम पूर्णांकel_ग_लिखो_dp_sdp(काष्ठा पूर्णांकel_encoder *encoder,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       अचिन्हित पूर्णांक type)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा dp_sdp sdp = अणुपूर्ण;
	sमाप_प्रकार len;

	अगर ((crtc_state->infoframes.enable &
	     पूर्णांकel_hdmi_infoframe_enable(type)) == 0)
		वापस;

	चयन (type) अणु
	हाल DP_SDP_VSC:
		len = पूर्णांकel_dp_vsc_sdp_pack(&crtc_state->infoframes.vsc, &sdp,
					    माप(sdp));
		अवरोध;
	हाल HDMI_PACKET_TYPE_GAMUT_METADATA:
		len = पूर्णांकel_dp_hdr_metadata_infoframe_sdp_pack(&crtc_state->infoframes.drm.drm,
							       &sdp, माप(sdp));
		अवरोध;
	शेष:
		MISSING_CASE(type);
		वापस;
	पूर्ण

	अगर (drm_WARN_ON(&dev_priv->drm, len < 0))
		वापस;

	dig_port->ग_लिखो_infoframe(encoder, crtc_state, type, &sdp, len);
पूर्ण

व्योम पूर्णांकel_ग_लिखो_dp_vsc_sdp(काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    काष्ठा drm_dp_vsc_sdp *vsc)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा dp_sdp sdp = अणुपूर्ण;
	sमाप_प्रकार len;

	len = पूर्णांकel_dp_vsc_sdp_pack(vsc, &sdp, माप(sdp));

	अगर (drm_WARN_ON(&dev_priv->drm, len < 0))
		वापस;

	dig_port->ग_लिखो_infoframe(encoder, crtc_state, DP_SDP_VSC,
					&sdp, len);
पूर्ण

व्योम पूर्णांकel_dp_set_infoframes(काष्ठा पूर्णांकel_encoder *encoder,
			     bool enable,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			     स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	i915_reg_t reg = HSW_TVIDEO_DIP_CTL(crtc_state->cpu_transcoder);
	u32 dip_enable = VIDEO_DIP_ENABLE_AVI_HSW | VIDEO_DIP_ENABLE_GCP_HSW |
			 VIDEO_DIP_ENABLE_VS_HSW | VIDEO_DIP_ENABLE_GMP_HSW |
			 VIDEO_DIP_ENABLE_SPD_HSW | VIDEO_DIP_ENABLE_DRM_GLK;
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, reg);

	/* TODO: Add DSC हाल (DIP_ENABLE_PPS) */
	/* When PSR is enabled, this routine करोesn't disable VSC DIP */
	अगर (पूर्णांकel_psr_enabled(पूर्णांकel_dp))
		val &= ~dip_enable;
	अन्यथा
		val &= ~(dip_enable | VIDEO_DIP_ENABLE_VSC_HSW);

	अगर (!enable) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
		वापस;
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);

	/* When PSR is enabled, VSC SDP is handled by PSR routine */
	अगर (!पूर्णांकel_psr_enabled(पूर्णांकel_dp))
		पूर्णांकel_ग_लिखो_dp_sdp(encoder, crtc_state, DP_SDP_VSC);

	पूर्णांकel_ग_लिखो_dp_sdp(encoder, crtc_state, HDMI_PACKET_TYPE_GAMUT_METADATA);
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_vsc_sdp_unpack(काष्ठा drm_dp_vsc_sdp *vsc,
				   स्थिर व्योम *buffer, माप_प्रकार size)
अणु
	स्थिर काष्ठा dp_sdp *sdp = buffer;

	अगर (size < माप(काष्ठा dp_sdp))
		वापस -EINVAL;

	स_रखो(vsc, 0, size);

	अगर (sdp->sdp_header.HB0 != 0)
		वापस -EINVAL;

	अगर (sdp->sdp_header.HB1 != DP_SDP_VSC)
		वापस -EINVAL;

	vsc->sdp_type = sdp->sdp_header.HB1;
	vsc->revision = sdp->sdp_header.HB2;
	vsc->length = sdp->sdp_header.HB3;

	अगर ((sdp->sdp_header.HB2 == 0x2 && sdp->sdp_header.HB3 == 0x8) ||
	    (sdp->sdp_header.HB2 == 0x4 && sdp->sdp_header.HB3 == 0xe)) अणु
		/*
		 * - HB2 = 0x2, HB3 = 0x8
		 *   VSC SDP supporting 3D stereo + PSR
		 * - HB2 = 0x4, HB3 = 0xe
		 *   VSC SDP supporting 3D stereo + PSR2 with Y-coordinate of
		 *   first scan line of the SU region (applies to eDP v1.4b
		 *   and higher).
		 */
		वापस 0;
	पूर्ण अन्यथा अगर (sdp->sdp_header.HB2 == 0x5 && sdp->sdp_header.HB3 == 0x13) अणु
		/*
		 * - HB2 = 0x5, HB3 = 0x13
		 *   VSC SDP supporting 3D stereo + PSR2 + Pixel Encoding/Colorimetry
		 *   Format.
		 */
		vsc->pixelक्रमmat = (sdp->db[16] >> 4) & 0xf;
		vsc->colorimetry = sdp->db[16] & 0xf;
		vsc->dynamic_range = (sdp->db[17] >> 7) & 0x1;

		चयन (sdp->db[17] & 0x7) अणु
		हाल 0x0:
			vsc->bpc = 6;
			अवरोध;
		हाल 0x1:
			vsc->bpc = 8;
			अवरोध;
		हाल 0x2:
			vsc->bpc = 10;
			अवरोध;
		हाल 0x3:
			vsc->bpc = 12;
			अवरोध;
		हाल 0x4:
			vsc->bpc = 16;
			अवरोध;
		शेष:
			MISSING_CASE(sdp->db[17] & 0x7);
			वापस -EINVAL;
		पूर्ण

		vsc->content_type = sdp->db[18] & 0x7;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
पूर्णांकel_dp_hdr_metadata_infoframe_sdp_unpack(काष्ठा hdmi_drm_infoframe *drm_infoframe,
					   स्थिर व्योम *buffer, माप_प्रकार size)
अणु
	पूर्णांक ret;

	स्थिर काष्ठा dp_sdp *sdp = buffer;

	अगर (size < माप(काष्ठा dp_sdp))
		वापस -EINVAL;

	अगर (sdp->sdp_header.HB0 != 0)
		वापस -EINVAL;

	अगर (sdp->sdp_header.HB1 != HDMI_INFOFRAME_TYPE_DRM)
		वापस -EINVAL;

	/*
	 * Least Signअगरicant Eight Bits of (Data Byte Count ै  1)
	 * 1Dh (i.e., Data Byte Count = 30 bytes).
	 */
	अगर (sdp->sdp_header.HB2 != 0x1D)
		वापस -EINVAL;

	/* Most Signअगरicant Two Bits of (Data Byte Count ै  1), Clear to 00b. */
	अगर ((sdp->sdp_header.HB3 & 0x3) != 0)
		वापस -EINVAL;

	/* INFOFRAME SDP Version Number */
	अगर (((sdp->sdp_header.HB3 >> 2) & 0x3f) != 0x13)
		वापस -EINVAL;

	/* CTA Header Byte 2 (INFOFRAME Version Number) */
	अगर (sdp->db[0] != 1)
		वापस -EINVAL;

	/* CTA Header Byte 3 (Length of INFOFRAME): HDMI_DRM_INFOFRAME_SIZE */
	अगर (sdp->db[1] != HDMI_DRM_INFOFRAME_SIZE)
		वापस -EINVAL;

	ret = hdmi_drm_infoframe_unpack_only(drm_infoframe, &sdp->db[2],
					     HDMI_DRM_INFOFRAME_SIZE);

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_पढ़ो_dp_vsc_sdp(काष्ठा पूर्णांकel_encoder *encoder,
				  काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  काष्ठा drm_dp_vsc_sdp *vsc)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	अचिन्हित पूर्णांक type = DP_SDP_VSC;
	काष्ठा dp_sdp sdp = अणुपूर्ण;
	पूर्णांक ret;

	/* When PSR is enabled, VSC SDP is handled by PSR routine */
	अगर (पूर्णांकel_psr_enabled(पूर्णांकel_dp))
		वापस;

	अगर ((crtc_state->infoframes.enable &
	     पूर्णांकel_hdmi_infoframe_enable(type)) == 0)
		वापस;

	dig_port->पढ़ो_infoframe(encoder, crtc_state, type, &sdp, माप(sdp));

	ret = पूर्णांकel_dp_vsc_sdp_unpack(vsc, &sdp, माप(sdp));

	अगर (ret)
		drm_dbg_kms(&dev_priv->drm, "Failed to unpack DP VSC SDP\n");
पूर्ण

अटल व्योम पूर्णांकel_पढ़ो_dp_hdr_metadata_infoframe_sdp(काष्ठा पूर्णांकel_encoder *encoder,
						     काष्ठा पूर्णांकel_crtc_state *crtc_state,
						     काष्ठा hdmi_drm_infoframe *drm_infoframe)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	अचिन्हित पूर्णांक type = HDMI_PACKET_TYPE_GAMUT_METADATA;
	काष्ठा dp_sdp sdp = अणुपूर्ण;
	पूर्णांक ret;

	अगर ((crtc_state->infoframes.enable &
	    पूर्णांकel_hdmi_infoframe_enable(type)) == 0)
		वापस;

	dig_port->पढ़ो_infoframe(encoder, crtc_state, type, &sdp,
				 माप(sdp));

	ret = पूर्णांकel_dp_hdr_metadata_infoframe_sdp_unpack(drm_infoframe, &sdp,
							 माप(sdp));

	अगर (ret)
		drm_dbg_kms(&dev_priv->drm,
			    "Failed to unpack DP HDR Metadata Infoframe SDP\n");
पूर्ण

व्योम पूर्णांकel_पढ़ो_dp_sdp(काष्ठा पूर्णांकel_encoder *encoder,
		       काष्ठा पूर्णांकel_crtc_state *crtc_state,
		       अचिन्हित पूर्णांक type)
अणु
	अगर (encoder->type != INTEL_OUTPUT_DDI)
		वापस;

	चयन (type) अणु
	हाल DP_SDP_VSC:
		पूर्णांकel_पढ़ो_dp_vsc_sdp(encoder, crtc_state,
				      &crtc_state->infoframes.vsc);
		अवरोध;
	हाल HDMI_PACKET_TYPE_GAMUT_METADATA:
		पूर्णांकel_पढ़ो_dp_hdr_metadata_infoframe_sdp(encoder, crtc_state,
							 &crtc_state->infoframes.drm.drm);
		अवरोध;
	शेष:
		MISSING_CASE(type);
		अवरोध;
	पूर्ण
पूर्ण

अटल u8 पूर्णांकel_dp_स्वतःtest_link_training(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	पूर्णांक status = 0;
	पूर्णांक test_link_rate;
	u8 test_lane_count, test_link_bw;
	/* (DP CTS 1.2)
	 * 4.3.1.11
	 */
	/* Read the TEST_LANE_COUNT and TEST_LINK_RTAE fields (DP CTS 3.1.4) */
	status = drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux, DP_TEST_LANE_COUNT,
				   &test_lane_count);

	अगर (status <= 0) अणु
		drm_dbg_kms(&i915->drm, "Lane count read failed\n");
		वापस DP_TEST_NAK;
	पूर्ण
	test_lane_count &= DP_MAX_LANE_COUNT_MASK;

	status = drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux, DP_TEST_LINK_RATE,
				   &test_link_bw);
	अगर (status <= 0) अणु
		drm_dbg_kms(&i915->drm, "Link Rate read failed\n");
		वापस DP_TEST_NAK;
	पूर्ण
	test_link_rate = drm_dp_bw_code_to_link_rate(test_link_bw);

	/* Validate the requested link rate and lane count */
	अगर (!पूर्णांकel_dp_link_params_valid(पूर्णांकel_dp, test_link_rate,
					test_lane_count))
		वापस DP_TEST_NAK;

	पूर्णांकel_dp->compliance.test_lane_count = test_lane_count;
	पूर्णांकel_dp->compliance.test_link_rate = test_link_rate;

	वापस DP_TEST_ACK;
पूर्ण

अटल u8 पूर्णांकel_dp_स्वतःtest_video_pattern(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	u8 test_pattern;
	u8 test_misc;
	__be16 h_width, v_height;
	पूर्णांक status = 0;

	/* Read the TEST_PATTERN (DP CTS 3.1.5) */
	status = drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux, DP_TEST_PATTERN,
				   &test_pattern);
	अगर (status <= 0) अणु
		drm_dbg_kms(&i915->drm, "Test pattern read failed\n");
		वापस DP_TEST_NAK;
	पूर्ण
	अगर (test_pattern != DP_COLOR_RAMP)
		वापस DP_TEST_NAK;

	status = drm_dp_dpcd_पढ़ो(&पूर्णांकel_dp->aux, DP_TEST_H_WIDTH_HI,
				  &h_width, 2);
	अगर (status <= 0) अणु
		drm_dbg_kms(&i915->drm, "H Width read failed\n");
		वापस DP_TEST_NAK;
	पूर्ण

	status = drm_dp_dpcd_पढ़ो(&पूर्णांकel_dp->aux, DP_TEST_V_HEIGHT_HI,
				  &v_height, 2);
	अगर (status <= 0) अणु
		drm_dbg_kms(&i915->drm, "V Height read failed\n");
		वापस DP_TEST_NAK;
	पूर्ण

	status = drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux, DP_TEST_MISC0,
				   &test_misc);
	अगर (status <= 0) अणु
		drm_dbg_kms(&i915->drm, "TEST MISC read failed\n");
		वापस DP_TEST_NAK;
	पूर्ण
	अगर ((test_misc & DP_TEST_COLOR_FORMAT_MASK) != DP_COLOR_FORMAT_RGB)
		वापस DP_TEST_NAK;
	अगर (test_misc & DP_TEST_DYNAMIC_RANGE_CEA)
		वापस DP_TEST_NAK;
	चयन (test_misc & DP_TEST_BIT_DEPTH_MASK) अणु
	हाल DP_TEST_BIT_DEPTH_6:
		पूर्णांकel_dp->compliance.test_data.bpc = 6;
		अवरोध;
	हाल DP_TEST_BIT_DEPTH_8:
		पूर्णांकel_dp->compliance.test_data.bpc = 8;
		अवरोध;
	शेष:
		वापस DP_TEST_NAK;
	पूर्ण

	पूर्णांकel_dp->compliance.test_data.video_pattern = test_pattern;
	पूर्णांकel_dp->compliance.test_data.hdisplay = be16_to_cpu(h_width);
	पूर्णांकel_dp->compliance.test_data.vdisplay = be16_to_cpu(v_height);
	/* Set test active flag here so userspace करोesn't पूर्णांकerrupt things */
	पूर्णांकel_dp->compliance.test_active = true;

	वापस DP_TEST_ACK;
पूर्ण

अटल u8 पूर्णांकel_dp_स्वतःtest_edid(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	u8 test_result = DP_TEST_ACK;
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = पूर्णांकel_dp->attached_connector;
	काष्ठा drm_connector *connector = &पूर्णांकel_connector->base;

	अगर (पूर्णांकel_connector->detect_edid == शून्य ||
	    connector->edid_corrupt ||
	    पूर्णांकel_dp->aux.i2c_defer_count > 6) अणु
		/* Check EDID पढ़ो क्रम NACKs, DEFERs and corruption
		 * (DP CTS 1.2 Core r1.1)
		 *    4.2.2.4 : Failed EDID पढ़ो, I2C_NAK
		 *    4.2.2.5 : Failed EDID पढ़ो, I2C_DEFER
		 *    4.2.2.6 : EDID corruption detected
		 * Use failsafe mode क्रम all हालs
		 */
		अगर (पूर्णांकel_dp->aux.i2c_nack_count > 0 ||
			पूर्णांकel_dp->aux.i2c_defer_count > 0)
			drm_dbg_kms(&i915->drm,
				    "EDID read had %d NACKs, %d DEFERs\n",
				    पूर्णांकel_dp->aux.i2c_nack_count,
				    पूर्णांकel_dp->aux.i2c_defer_count);
		पूर्णांकel_dp->compliance.test_data.edid = INTEL_DP_RESOLUTION_FAILSAFE;
	पूर्ण अन्यथा अणु
		काष्ठा edid *block = पूर्णांकel_connector->detect_edid;

		/* We have to ग_लिखो the checksum
		 * of the last block पढ़ो
		 */
		block += पूर्णांकel_connector->detect_edid->extensions;

		अगर (drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux, DP_TEST_EDID_CHECKSUM,
				       block->checksum) <= 0)
			drm_dbg_kms(&i915->drm,
				    "Failed to write EDID checksum\n");

		test_result = DP_TEST_ACK | DP_TEST_EDID_CHECKSUM_WRITE;
		पूर्णांकel_dp->compliance.test_data.edid = INTEL_DP_RESOLUTION_PREFERRED;
	पूर्ण

	/* Set test active flag here so userspace करोesn't पूर्णांकerrupt things */
	पूर्णांकel_dp->compliance.test_active = true;

	वापस test_result;
पूर्ण

अटल व्योम पूर्णांकel_dp_phy_pattern_update(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
			to_i915(dp_to_dig_port(पूर्णांकel_dp)->base.base.dev);
	काष्ठा drm_dp_phy_test_params *data =
			&पूर्णांकel_dp->compliance.test_data.phytest;
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	क्रमागत pipe pipe = crtc->pipe;
	u32 pattern_val;

	चयन (data->phy_pattern) अणु
	हाल DP_PHY_TEST_PATTERN_NONE:
		DRM_DEBUG_KMS("Disable Phy Test Pattern\n");
		पूर्णांकel_de_ग_लिखो(dev_priv, DDI_DP_COMP_CTL(pipe), 0x0);
		अवरोध;
	हाल DP_PHY_TEST_PATTERN_D10_2:
		DRM_DEBUG_KMS("Set D10.2 Phy Test Pattern\n");
		पूर्णांकel_de_ग_लिखो(dev_priv, DDI_DP_COMP_CTL(pipe),
			       DDI_DP_COMP_CTL_ENABLE | DDI_DP_COMP_CTL_D10_2);
		अवरोध;
	हाल DP_PHY_TEST_PATTERN_ERROR_COUNT:
		DRM_DEBUG_KMS("Set Error Count Phy Test Pattern\n");
		पूर्णांकel_de_ग_लिखो(dev_priv, DDI_DP_COMP_CTL(pipe),
			       DDI_DP_COMP_CTL_ENABLE |
			       DDI_DP_COMP_CTL_SCRAMBLED_0);
		अवरोध;
	हाल DP_PHY_TEST_PATTERN_PRBS7:
		DRM_DEBUG_KMS("Set PRBS7 Phy Test Pattern\n");
		पूर्णांकel_de_ग_लिखो(dev_priv, DDI_DP_COMP_CTL(pipe),
			       DDI_DP_COMP_CTL_ENABLE | DDI_DP_COMP_CTL_PRBS7);
		अवरोध;
	हाल DP_PHY_TEST_PATTERN_80BIT_CUSTOM:
		/*
		 * FIXME: Ideally pattern should come from DPCD 0x250. As
		 * current firmware of DPR-100 could not set it, so hardcoding
		 * now क्रम complaince test.
		 */
		DRM_DEBUG_KMS("Set 80Bit Custom Phy Test Pattern 0x3e0f83e0 0x0f83e0f8 0x0000f83e\n");
		pattern_val = 0x3e0f83e0;
		पूर्णांकel_de_ग_लिखो(dev_priv, DDI_DP_COMP_PAT(pipe, 0), pattern_val);
		pattern_val = 0x0f83e0f8;
		पूर्णांकel_de_ग_लिखो(dev_priv, DDI_DP_COMP_PAT(pipe, 1), pattern_val);
		pattern_val = 0x0000f83e;
		पूर्णांकel_de_ग_लिखो(dev_priv, DDI_DP_COMP_PAT(pipe, 2), pattern_val);
		पूर्णांकel_de_ग_लिखो(dev_priv, DDI_DP_COMP_CTL(pipe),
			       DDI_DP_COMP_CTL_ENABLE |
			       DDI_DP_COMP_CTL_CUSTOM80);
		अवरोध;
	हाल DP_PHY_TEST_PATTERN_CP2520:
		/*
		 * FIXME: Ideally pattern should come from DPCD 0x24A. As
		 * current firmware of DPR-100 could not set it, so hardcoding
		 * now क्रम complaince test.
		 */
		DRM_DEBUG_KMS("Set HBR2 compliance Phy Test Pattern\n");
		pattern_val = 0xFB;
		पूर्णांकel_de_ग_लिखो(dev_priv, DDI_DP_COMP_CTL(pipe),
			       DDI_DP_COMP_CTL_ENABLE | DDI_DP_COMP_CTL_HBR2 |
			       pattern_val);
		अवरोध;
	शेष:
		WARN(1, "Invalid Phy Test Pattern\n");
	पूर्ण
पूर्ण

अटल व्योम
पूर्णांकel_dp_स्वतःtest_phy_ddi_disable(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा drm_device *dev = dig_port->base.base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(dig_port->base.base.crtc);
	क्रमागत pipe pipe = crtc->pipe;
	u32 trans_ddi_func_ctl_value, trans_conf_value, dp_tp_ctl_value;

	trans_ddi_func_ctl_value = पूर्णांकel_de_पढ़ो(dev_priv,
						 TRANS_DDI_FUNC_CTL(pipe));
	trans_conf_value = पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(pipe));
	dp_tp_ctl_value = पूर्णांकel_de_पढ़ो(dev_priv, TGL_DP_TP_CTL(pipe));

	trans_ddi_func_ctl_value &= ~(TRANS_DDI_FUNC_ENABLE |
				      TGL_TRANS_DDI_PORT_MASK);
	trans_conf_value &= ~PIPECONF_ENABLE;
	dp_tp_ctl_value &= ~DP_TP_CTL_ENABLE;

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPECONF(pipe), trans_conf_value);
	पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_DDI_FUNC_CTL(pipe),
		       trans_ddi_func_ctl_value);
	पूर्णांकel_de_ग_लिखो(dev_priv, TGL_DP_TP_CTL(pipe), dp_tp_ctl_value);
पूर्ण

अटल व्योम
पूर्णांकel_dp_स्वतःtest_phy_ddi_enable(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा drm_device *dev = dig_port->base.base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत port port = dig_port->base.port;
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(dig_port->base.base.crtc);
	क्रमागत pipe pipe = crtc->pipe;
	u32 trans_ddi_func_ctl_value, trans_conf_value, dp_tp_ctl_value;

	trans_ddi_func_ctl_value = पूर्णांकel_de_पढ़ो(dev_priv,
						 TRANS_DDI_FUNC_CTL(pipe));
	trans_conf_value = पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(pipe));
	dp_tp_ctl_value = पूर्णांकel_de_पढ़ो(dev_priv, TGL_DP_TP_CTL(pipe));

	trans_ddi_func_ctl_value |= TRANS_DDI_FUNC_ENABLE |
				    TGL_TRANS_DDI_SELECT_PORT(port);
	trans_conf_value |= PIPECONF_ENABLE;
	dp_tp_ctl_value |= DP_TP_CTL_ENABLE;

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPECONF(pipe), trans_conf_value);
	पूर्णांकel_de_ग_लिखो(dev_priv, TGL_DP_TP_CTL(pipe), dp_tp_ctl_value);
	पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_DDI_FUNC_CTL(pipe),
		       trans_ddi_func_ctl_value);
पूर्ण

अटल व्योम पूर्णांकel_dp_process_phy_request(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_dp_phy_test_params *data =
		&पूर्णांकel_dp->compliance.test_data.phytest;
	u8 link_status[DP_LINK_STATUS_SIZE];

	अगर (drm_dp_dpcd_पढ़ो_phy_link_status(&पूर्णांकel_dp->aux, DP_PHY_DPRX,
					     link_status) < 0) अणु
		DRM_DEBUG_KMS("failed to get link status\n");
		वापस;
	पूर्ण

	/* retrieve vswing & pre-emphasis setting */
	पूर्णांकel_dp_get_adjust_train(पूर्णांकel_dp, crtc_state, DP_PHY_DPRX,
				  link_status);

	पूर्णांकel_dp_स्वतःtest_phy_ddi_disable(पूर्णांकel_dp, crtc_state);

	पूर्णांकel_dp_set_संकेत_levels(पूर्णांकel_dp, crtc_state, DP_PHY_DPRX);

	पूर्णांकel_dp_phy_pattern_update(पूर्णांकel_dp, crtc_state);

	पूर्णांकel_dp_स्वतःtest_phy_ddi_enable(पूर्णांकel_dp, crtc_state);

	drm_dp_set_phy_test_pattern(&पूर्णांकel_dp->aux, data,
				    link_status[DP_DPCD_REV]);
पूर्ण

अटल u8 पूर्णांकel_dp_स्वतःtest_phy_pattern(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_dp_phy_test_params *data =
		&पूर्णांकel_dp->compliance.test_data.phytest;

	अगर (drm_dp_get_phy_test_pattern(&पूर्णांकel_dp->aux, data)) अणु
		DRM_DEBUG_KMS("DP Phy Test pattern AUX read failure\n");
		वापस DP_TEST_NAK;
	पूर्ण

	/* Set test active flag here so userspace करोesn't पूर्णांकerrupt things */
	पूर्णांकel_dp->compliance.test_active = true;

	वापस DP_TEST_ACK;
पूर्ण

अटल व्योम पूर्णांकel_dp_handle_test_request(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	u8 response = DP_TEST_NAK;
	u8 request = 0;
	पूर्णांक status;

	status = drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux, DP_TEST_REQUEST, &request);
	अगर (status <= 0) अणु
		drm_dbg_kms(&i915->drm,
			    "Could not read test request from sink\n");
		जाओ update_status;
	पूर्ण

	चयन (request) अणु
	हाल DP_TEST_LINK_TRAINING:
		drm_dbg_kms(&i915->drm, "LINK_TRAINING test requested\n");
		response = पूर्णांकel_dp_स्वतःtest_link_training(पूर्णांकel_dp);
		अवरोध;
	हाल DP_TEST_LINK_VIDEO_PATTERN:
		drm_dbg_kms(&i915->drm, "TEST_PATTERN test requested\n");
		response = पूर्णांकel_dp_स्वतःtest_video_pattern(पूर्णांकel_dp);
		अवरोध;
	हाल DP_TEST_LINK_EDID_READ:
		drm_dbg_kms(&i915->drm, "EDID test requested\n");
		response = पूर्णांकel_dp_स्वतःtest_edid(पूर्णांकel_dp);
		अवरोध;
	हाल DP_TEST_LINK_PHY_TEST_PATTERN:
		drm_dbg_kms(&i915->drm, "PHY_PATTERN test requested\n");
		response = पूर्णांकel_dp_स्वतःtest_phy_pattern(पूर्णांकel_dp);
		अवरोध;
	शेष:
		drm_dbg_kms(&i915->drm, "Invalid test request '%02x'\n",
			    request);
		अवरोध;
	पूर्ण

	अगर (response & DP_TEST_ACK)
		पूर्णांकel_dp->compliance.test_type = request;

update_status:
	status = drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux, DP_TEST_RESPONSE, response);
	अगर (status <= 0)
		drm_dbg_kms(&i915->drm,
			    "Could not write test response to sink\n");
पूर्ण

अटल व्योम
पूर्णांकel_dp_mst_hpd_irq(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, u8 *esi, bool *handled)
अणु
		drm_dp_mst_hpd_irq(&पूर्णांकel_dp->mst_mgr, esi, handled);

		अगर (esi[1] & DP_CP_IRQ) अणु
			पूर्णांकel_hdcp_handle_cp_irq(पूर्णांकel_dp->attached_connector);
			*handled = true;
		पूर्ण
पूर्ण

/**
 * पूर्णांकel_dp_check_mst_status - service any pending MST पूर्णांकerrupts, check link status
 * @पूर्णांकel_dp: Intel DP काष्ठा
 *
 * Read any pending MST पूर्णांकerrupts, call MST core to handle these and ack the
 * पूर्णांकerrupts. Check अगर the मुख्य and AUX link state is ok.
 *
 * Returns:
 * - %true अगर pending पूर्णांकerrupts were serviced (or no पूर्णांकerrupts were
 *   pending) w/o detecting an error condition.
 * - %false अगर an error condition - like AUX failure or a loss of link - is
 *   detected, which needs servicing from the hotplug work.
 */
अटल bool
पूर्णांकel_dp_check_mst_status(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	bool link_ok = true;

	drm_WARN_ON_ONCE(&i915->drm, पूर्णांकel_dp->active_mst_links < 0);

	क्रम (;;) अणु
		/*
		 * The +2 is because DP_DPRX_ESI_LEN is 14, but we then
		 * pass in "esi+10" to drm_dp_channel_eq_ok(), which
		 * takes a 6-byte array. So we actually need 16 bytes
		 * here.
		 *
		 * Somebody who knows what the limits actually are
		 * should check this, but क्रम now this is at least
		 * harmless and aव्योमs a valid compiler warning about
		 * using more of the array than we have allocated.
		 */
		u8 esi[DP_DPRX_ESI_LEN+2] = अणुपूर्ण;
		bool handled;
		पूर्णांक retry;

		अगर (!पूर्णांकel_dp_get_sink_irq_esi(पूर्णांकel_dp, esi)) अणु
			drm_dbg_kms(&i915->drm,
				    "failed to get ESI - device may have failed\n");
			link_ok = false;

			अवरोध;
		पूर्ण

		/* check link status - esi[10] = 0x200c */
		अगर (पूर्णांकel_dp->active_mst_links > 0 && link_ok &&
		    !drm_dp_channel_eq_ok(&esi[10], पूर्णांकel_dp->lane_count)) अणु
			drm_dbg_kms(&i915->drm,
				    "channel EQ not ok, retraining\n");
			link_ok = false;
		पूर्ण

		drm_dbg_kms(&i915->drm, "got esi %3ph\n", esi);

		पूर्णांकel_dp_mst_hpd_irq(पूर्णांकel_dp, esi, &handled);

		अगर (!handled)
			अवरोध;

		क्रम (retry = 0; retry < 3; retry++) अणु
			पूर्णांक wret;

			wret = drm_dp_dpcd_ग_लिखो(&पूर्णांकel_dp->aux,
						 DP_SINK_COUNT_ESI+1,
						 &esi[1], 3);
			अगर (wret == 3)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस link_ok;
पूर्ण

अटल व्योम
पूर्णांकel_dp_handle_hdmi_link_status_change(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	bool is_active;
	u8 buf = 0;

	is_active = drm_dp_pcon_hdmi_link_active(&पूर्णांकel_dp->aux);
	अगर (पूर्णांकel_dp->frl.is_trained && !is_active) अणु
		अगर (drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux, DP_PCON_HDMI_LINK_CONFIG_1, &buf) < 0)
			वापस;

		buf &=  ~DP_PCON_ENABLE_HDMI_LINK;
		अगर (drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux, DP_PCON_HDMI_LINK_CONFIG_1, buf) < 0)
			वापस;

		drm_dp_pcon_hdmi_frl_link_error_count(&पूर्णांकel_dp->aux, &पूर्णांकel_dp->attached_connector->base);

		/* Restart FRL training or fall back to TMDS mode */
		पूर्णांकel_dp_check_frl_training(पूर्णांकel_dp);
	पूर्ण
पूर्ण

अटल bool
पूर्णांकel_dp_needs_link_retrain(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	u8 link_status[DP_LINK_STATUS_SIZE];

	अगर (!पूर्णांकel_dp->link_trained)
		वापस false;

	/*
	 * While PSR source HW is enabled, it will control मुख्य-link sending
	 * frames, enabling and disabling it so trying to करो a retrain will fail
	 * as the link would or not be on or it could mix training patterns
	 * and frame data at the same समय causing retrain to fail.
	 * Also when निकासing PSR, HW will retrain the link anyways fixing
	 * any link status error.
	 */
	अगर (पूर्णांकel_psr_enabled(पूर्णांकel_dp))
		वापस false;

	अगर (drm_dp_dpcd_पढ़ो_phy_link_status(&पूर्णांकel_dp->aux, DP_PHY_DPRX,
					     link_status) < 0)
		वापस false;

	/*
	 * Validate the cached values of पूर्णांकel_dp->link_rate and
	 * पूर्णांकel_dp->lane_count beक्रमe attempting to retrain.
	 *
	 * FIXME would be nice to user the crtc state here, but since
	 * we need to call this from the लघु HPD handler that seems
	 * a bit hard.
	 */
	अगर (!पूर्णांकel_dp_link_params_valid(पूर्णांकel_dp, पूर्णांकel_dp->link_rate,
					पूर्णांकel_dp->lane_count))
		वापस false;

	/* Retrain अगर Channel EQ or CR not ok */
	वापस !drm_dp_channel_eq_ok(link_status, पूर्णांकel_dp->lane_count);
पूर्ण

अटल bool पूर्णांकel_dp_has_connector(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				   स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_encoder *encoder;
	क्रमागत pipe pipe;

	अगर (!conn_state->best_encoder)
		वापस false;

	/* SST */
	encoder = &dp_to_dig_port(पूर्णांकel_dp)->base;
	अगर (conn_state->best_encoder == &encoder->base)
		वापस true;

	/* MST */
	क्रम_each_pipe(i915, pipe) अणु
		encoder = &पूर्णांकel_dp->mst_encoders[pipe]->base;
		अगर (conn_state->best_encoder == &encoder->base)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_prep_link_retrain(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				      काष्ठा drm_modeset_acquire_ctx *ctx,
				      u32 *crtc_mask)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा पूर्णांकel_connector *connector;
	पूर्णांक ret = 0;

	*crtc_mask = 0;

	अगर (!पूर्णांकel_dp_needs_link_retrain(पूर्णांकel_dp))
		वापस 0;

	drm_connector_list_iter_begin(&i915->drm, &conn_iter);
	क्रम_each_पूर्णांकel_connector_iter(connector, &conn_iter) अणु
		काष्ठा drm_connector_state *conn_state =
			connector->base.state;
		काष्ठा पूर्णांकel_crtc_state *crtc_state;
		काष्ठा पूर्णांकel_crtc *crtc;

		अगर (!पूर्णांकel_dp_has_connector(पूर्णांकel_dp, conn_state))
			जारी;

		crtc = to_पूर्णांकel_crtc(conn_state->crtc);
		अगर (!crtc)
			जारी;

		ret = drm_modeset_lock(&crtc->base.mutex, ctx);
		अगर (ret)
			अवरोध;

		crtc_state = to_पूर्णांकel_crtc_state(crtc->base.state);

		drm_WARN_ON(&i915->drm, !पूर्णांकel_crtc_has_dp_encoder(crtc_state));

		अगर (!crtc_state->hw.active)
			जारी;

		अगर (conn_state->commit &&
		    !try_रुको_क्रम_completion(&conn_state->commit->hw_करोne))
			जारी;

		*crtc_mask |= drm_crtc_mask(&crtc->base);
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	अगर (!पूर्णांकel_dp_needs_link_retrain(पूर्णांकel_dp))
		*crtc_mask = 0;

	वापस ret;
पूर्ण

अटल bool पूर्णांकel_dp_is_connected(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा पूर्णांकel_connector *connector = पूर्णांकel_dp->attached_connector;

	वापस connector->base.status == connector_status_connected ||
		पूर्णांकel_dp->is_mst;
पूर्ण

पूर्णांक पूर्णांकel_dp_retrain_link(काष्ठा पूर्णांकel_encoder *encoder,
			  काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	काष्ठा पूर्णांकel_crtc *crtc;
	u32 crtc_mask;
	पूर्णांक ret;

	अगर (!पूर्णांकel_dp_is_connected(पूर्णांकel_dp))
		वापस 0;

	ret = drm_modeset_lock(&dev_priv->drm.mode_config.connection_mutex,
			       ctx);
	अगर (ret)
		वापस ret;

	ret = पूर्णांकel_dp_prep_link_retrain(पूर्णांकel_dp, ctx, &crtc_mask);
	अगर (ret)
		वापस ret;

	अगर (crtc_mask == 0)
		वापस 0;

	drm_dbg_kms(&dev_priv->drm, "[ENCODER:%d:%s] retraining link\n",
		    encoder->base.base.id, encoder->base.name);

	क्रम_each_पूर्णांकel_crtc_mask(&dev_priv->drm, crtc, crtc_mask) अणु
		स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
			to_पूर्णांकel_crtc_state(crtc->base.state);

		/* Suppress underruns caused by re-training */
		पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, crtc->pipe, false);
		अगर (crtc_state->has_pch_encoder)
			पूर्णांकel_set_pch_fअगरo_underrun_reporting(dev_priv,
							      पूर्णांकel_crtc_pch_transcoder(crtc), false);
	पूर्ण

	क्रम_each_पूर्णांकel_crtc_mask(&dev_priv->drm, crtc, crtc_mask) अणु
		स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
			to_पूर्णांकel_crtc_state(crtc->base.state);

		/* retrain on the MST master transcoder */
		अगर (DISPLAY_VER(dev_priv) >= 12 &&
		    पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_DP_MST) &&
		    !पूर्णांकel_dp_mst_is_master_trans(crtc_state))
			जारी;

		पूर्णांकel_dp_check_frl_training(पूर्णांकel_dp);
		पूर्णांकel_dp_pcon_dsc_configure(पूर्णांकel_dp, crtc_state);
		पूर्णांकel_dp_start_link_train(पूर्णांकel_dp, crtc_state);
		पूर्णांकel_dp_stop_link_train(पूर्णांकel_dp, crtc_state);
		अवरोध;
	पूर्ण

	क्रम_each_पूर्णांकel_crtc_mask(&dev_priv->drm, crtc, crtc_mask) अणु
		स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
			to_पूर्णांकel_crtc_state(crtc->base.state);

		/* Keep underrun reporting disabled until things are stable */
		पूर्णांकel_रुको_क्रम_vblank(dev_priv, crtc->pipe);

		पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, crtc->pipe, true);
		अगर (crtc_state->has_pch_encoder)
			पूर्णांकel_set_pch_fअगरo_underrun_reporting(dev_priv,
							      पूर्णांकel_crtc_pch_transcoder(crtc), true);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_prep_phy_test(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				  काष्ठा drm_modeset_acquire_ctx *ctx,
				  u32 *crtc_mask)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा पूर्णांकel_connector *connector;
	पूर्णांक ret = 0;

	*crtc_mask = 0;

	drm_connector_list_iter_begin(&i915->drm, &conn_iter);
	क्रम_each_पूर्णांकel_connector_iter(connector, &conn_iter) अणु
		काष्ठा drm_connector_state *conn_state =
			connector->base.state;
		काष्ठा पूर्णांकel_crtc_state *crtc_state;
		काष्ठा पूर्णांकel_crtc *crtc;

		अगर (!पूर्णांकel_dp_has_connector(पूर्णांकel_dp, conn_state))
			जारी;

		crtc = to_पूर्णांकel_crtc(conn_state->crtc);
		अगर (!crtc)
			जारी;

		ret = drm_modeset_lock(&crtc->base.mutex, ctx);
		अगर (ret)
			अवरोध;

		crtc_state = to_पूर्णांकel_crtc_state(crtc->base.state);

		drm_WARN_ON(&i915->drm, !पूर्णांकel_crtc_has_dp_encoder(crtc_state));

		अगर (!crtc_state->hw.active)
			जारी;

		अगर (conn_state->commit &&
		    !try_रुको_क्रम_completion(&conn_state->commit->hw_करोne))
			जारी;

		*crtc_mask |= drm_crtc_mask(&crtc->base);
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_करो_phy_test(काष्ठा पूर्णांकel_encoder *encoder,
				काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	काष्ठा पूर्णांकel_crtc *crtc;
	u32 crtc_mask;
	पूर्णांक ret;

	ret = drm_modeset_lock(&dev_priv->drm.mode_config.connection_mutex,
			       ctx);
	अगर (ret)
		वापस ret;

	ret = पूर्णांकel_dp_prep_phy_test(पूर्णांकel_dp, ctx, &crtc_mask);
	अगर (ret)
		वापस ret;

	अगर (crtc_mask == 0)
		वापस 0;

	drm_dbg_kms(&dev_priv->drm, "[ENCODER:%d:%s] PHY test\n",
		    encoder->base.base.id, encoder->base.name);

	क्रम_each_पूर्णांकel_crtc_mask(&dev_priv->drm, crtc, crtc_mask) अणु
		स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
			to_पूर्णांकel_crtc_state(crtc->base.state);

		/* test on the MST master transcoder */
		अगर (DISPLAY_VER(dev_priv) >= 12 &&
		    पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_DP_MST) &&
		    !पूर्णांकel_dp_mst_is_master_trans(crtc_state))
			जारी;

		पूर्णांकel_dp_process_phy_request(पूर्णांकel_dp, crtc_state);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

व्योम पूर्णांकel_dp_phy_test(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_modeset_acquire_ctx ctx;
	पूर्णांक ret;

	drm_modeset_acquire_init(&ctx, 0);

	क्रम (;;) अणु
		ret = पूर्णांकel_dp_करो_phy_test(encoder, &ctx);

		अगर (ret == -EDEADLK) अणु
			drm_modeset_backoff(&ctx);
			जारी;
		पूर्ण

		अवरोध;
	पूर्ण

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);
	drm_WARN(encoder->base.dev, ret,
		 "Acquiring modeset locks failed with %i\n", ret);
पूर्ण

अटल व्योम पूर्णांकel_dp_check_device_service_irq(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	u8 val;

	अगर (पूर्णांकel_dp->dpcd[DP_DPCD_REV] < 0x11)
		वापस;

	अगर (drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux,
			      DP_DEVICE_SERVICE_IRQ_VECTOR, &val) != 1 || !val)
		वापस;

	drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux, DP_DEVICE_SERVICE_IRQ_VECTOR, val);

	अगर (val & DP_AUTOMATED_TEST_REQUEST)
		पूर्णांकel_dp_handle_test_request(पूर्णांकel_dp);

	अगर (val & DP_CP_IRQ)
		पूर्णांकel_hdcp_handle_cp_irq(पूर्णांकel_dp->attached_connector);

	अगर (val & DP_SINK_SPECIFIC_IRQ)
		drm_dbg_kms(&i915->drm, "Sink specific irq unhandled\n");
पूर्ण

अटल व्योम पूर्णांकel_dp_check_link_service_irq(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	u8 val;

	अगर (पूर्णांकel_dp->dpcd[DP_DPCD_REV] < 0x11)
		वापस;

	अगर (drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux,
			      DP_LINK_SERVICE_IRQ_VECTOR_ESI0, &val) != 1 || !val) अणु
		drm_dbg_kms(&i915->drm, "Error in reading link service irq vector\n");
		वापस;
	पूर्ण

	अगर (drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux,
			       DP_LINK_SERVICE_IRQ_VECTOR_ESI0, val) != 1) अणु
		drm_dbg_kms(&i915->drm, "Error in writing link service irq vector\n");
		वापस;
	पूर्ण

	अगर (val & HDMI_LINK_STATUS_CHANGED)
		पूर्णांकel_dp_handle_hdmi_link_status_change(पूर्णांकel_dp);
पूर्ण

/*
 * According to DP spec
 * 5.1.2:
 *  1. Read DPCD
 *  2. Configure link according to Receiver Capabilities
 *  3. Use Link Training from 2.5.3.3 and 3.5.1.3
 *  4. Check link status on receipt of hot-plug पूर्णांकerrupt
 *
 * पूर्णांकel_dp_लघु_pulse -  handles लघु pulse पूर्णांकerrupts
 * when full detection is not required.
 * Returns %true अगर लघु pulse is handled and full detection
 * is NOT required and %false otherwise.
 */
अटल bool
पूर्णांकel_dp_लघु_pulse(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	u8 old_sink_count = पूर्णांकel_dp->sink_count;
	bool ret;

	/*
	 * Clearing compliance test variables to allow capturing
	 * of values क्रम next स्वतःmated test request.
	 */
	स_रखो(&पूर्णांकel_dp->compliance, 0, माप(पूर्णांकel_dp->compliance));

	/*
	 * Now पढ़ो the DPCD to see अगर it's actually running
	 * If the current value of sink count करोesn't match with
	 * the value that was stored earlier or dpcd पढ़ो failed
	 * we need to करो full detection
	 */
	ret = पूर्णांकel_dp_get_dpcd(पूर्णांकel_dp);

	अगर ((old_sink_count != पूर्णांकel_dp->sink_count) || !ret) अणु
		/* No need to proceed अगर we are going to करो full detect */
		वापस false;
	पूर्ण

	पूर्णांकel_dp_check_device_service_irq(पूर्णांकel_dp);
	पूर्णांकel_dp_check_link_service_irq(पूर्णांकel_dp);

	/* Handle CEC पूर्णांकerrupts, अगर any */
	drm_dp_cec_irq(&पूर्णांकel_dp->aux);

	/* defer to the hotplug work क्रम link retraining अगर needed */
	अगर (पूर्णांकel_dp_needs_link_retrain(पूर्णांकel_dp))
		वापस false;

	पूर्णांकel_psr_लघु_pulse(पूर्णांकel_dp);

	चयन (पूर्णांकel_dp->compliance.test_type) अणु
	हाल DP_TEST_LINK_TRAINING:
		drm_dbg_kms(&dev_priv->drm,
			    "Link Training Compliance Test requested\n");
		/* Send a Hotplug Uevent to userspace to start modeset */
		drm_kms_helper_hotplug_event(&dev_priv->drm);
		अवरोध;
	हाल DP_TEST_LINK_PHY_TEST_PATTERN:
		drm_dbg_kms(&dev_priv->drm,
			    "PHY test pattern Compliance Test requested\n");
		/*
		 * Schedule दीर्घ hpd to करो the test
		 *
		 * FIXME get rid of the ad-hoc phy test modeset code
		 * and properly incorporate it पूर्णांकo the normal modeset.
		 */
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* XXX this is probably wrong क्रम multiple करोwnstream ports */
अटल क्रमागत drm_connector_status
पूर्णांकel_dp_detect_dpcd(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	u8 *dpcd = पूर्णांकel_dp->dpcd;
	u8 type;

	अगर (drm_WARN_ON(&i915->drm, पूर्णांकel_dp_is_edp(पूर्णांकel_dp)))
		वापस connector_status_connected;

	lspcon_resume(dig_port);

	अगर (!पूर्णांकel_dp_get_dpcd(पूर्णांकel_dp))
		वापस connector_status_disconnected;

	/* अगर there's no downstream port, we're करोne */
	अगर (!drm_dp_is_branch(dpcd))
		वापस connector_status_connected;

	/* If we're HPD-aware, SINK_COUNT changes dynamically */
	अगर (पूर्णांकel_dp_has_sink_count(पूर्णांकel_dp) &&
	    पूर्णांकel_dp->करोwnstream_ports[0] & DP_DS_PORT_HPD) अणु
		वापस पूर्णांकel_dp->sink_count ?
		connector_status_connected : connector_status_disconnected;
	पूर्ण

	अगर (पूर्णांकel_dp_can_mst(पूर्णांकel_dp))
		वापस connector_status_connected;

	/* If no HPD, poke DDC gently */
	अगर (drm_probe_ddc(&पूर्णांकel_dp->aux.ddc))
		वापस connector_status_connected;

	/* Well we tried, say unknown क्रम unreliable port types */
	अगर (पूर्णांकel_dp->dpcd[DP_DPCD_REV] >= 0x11) अणु
		type = पूर्णांकel_dp->करोwnstream_ports[0] & DP_DS_PORT_TYPE_MASK;
		अगर (type == DP_DS_PORT_TYPE_VGA ||
		    type == DP_DS_PORT_TYPE_NON_EDID)
			वापस connector_status_unknown;
	पूर्ण अन्यथा अणु
		type = पूर्णांकel_dp->dpcd[DP_DOWNSTREAMPORT_PRESENT] &
			DP_DWN_STRM_PORT_TYPE_MASK;
		अगर (type == DP_DWN_STRM_PORT_TYPE_ANALOG ||
		    type == DP_DWN_STRM_PORT_TYPE_OTHER)
			वापस connector_status_unknown;
	पूर्ण

	/* Anything अन्यथा is out of spec, warn and ignore */
	drm_dbg_kms(&i915->drm, "Broken DP branch device, ignoring\n");
	वापस connector_status_disconnected;
पूर्ण

अटल क्रमागत drm_connector_status
edp_detect(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	वापस connector_status_connected;
पूर्ण

/*
 * पूर्णांकel_digital_port_connected - is the specअगरied port connected?
 * @encoder: पूर्णांकel_encoder
 *
 * In हालs where there's a connector physically connected but it can't be used
 * by our hardware we also वापस false, since the rest of the driver should
 * pretty much treat the port as disconnected. This is relevant क्रम type-C
 * (starting on ICL) where there's ownership involved.
 *
 * Return %true अगर port is connected, %false otherwise.
 */
bool पूर्णांकel_digital_port_connected(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	bool is_connected = false;
	पूर्णांकel_wakeref_t wakeref;

	with_पूर्णांकel_display_घातer(dev_priv, POWER_DOMAIN_DISPLAY_CORE, wakeref)
		is_connected = dig_port->connected(encoder);

	वापस is_connected;
पूर्ण

अटल काष्ठा edid *
पूर्णांकel_dp_get_edid(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = पूर्णांकel_dp->attached_connector;

	/* use cached edid अगर we have one */
	अगर (पूर्णांकel_connector->edid) अणु
		/* invalid edid */
		अगर (IS_ERR(पूर्णांकel_connector->edid))
			वापस शून्य;

		वापस drm_edid_duplicate(पूर्णांकel_connector->edid);
	पूर्ण अन्यथा
		वापस drm_get_edid(&पूर्णांकel_connector->base,
				    &पूर्णांकel_dp->aux.ddc);
पूर्ण

अटल व्योम
पूर्णांकel_dp_update_dfp(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
		    स्थिर काष्ठा edid *edid)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_connector *connector = पूर्णांकel_dp->attached_connector;

	पूर्णांकel_dp->dfp.max_bpc =
		drm_dp_करोwnstream_max_bpc(पूर्णांकel_dp->dpcd,
					  पूर्णांकel_dp->करोwnstream_ports, edid);

	पूर्णांकel_dp->dfp.max_करोtघड़ी =
		drm_dp_करोwnstream_max_करोtघड़ी(पूर्णांकel_dp->dpcd,
					       पूर्णांकel_dp->करोwnstream_ports);

	पूर्णांकel_dp->dfp.min_पंचांगds_घड़ी =
		drm_dp_करोwnstream_min_पंचांगds_घड़ी(पूर्णांकel_dp->dpcd,
						 पूर्णांकel_dp->करोwnstream_ports,
						 edid);
	पूर्णांकel_dp->dfp.max_पंचांगds_घड़ी =
		drm_dp_करोwnstream_max_पंचांगds_घड़ी(पूर्णांकel_dp->dpcd,
						 पूर्णांकel_dp->करोwnstream_ports,
						 edid);

	पूर्णांकel_dp->dfp.pcon_max_frl_bw =
		drm_dp_get_pcon_max_frl_bw(पूर्णांकel_dp->dpcd,
					   पूर्णांकel_dp->करोwnstream_ports);

	drm_dbg_kms(&i915->drm,
		    "[CONNECTOR:%d:%s] DFP max bpc %d, max dotclock %d, TMDS clock %d-%d, PCON Max FRL BW %dGbps\n",
		    connector->base.base.id, connector->base.name,
		    पूर्णांकel_dp->dfp.max_bpc,
		    पूर्णांकel_dp->dfp.max_करोtघड़ी,
		    पूर्णांकel_dp->dfp.min_पंचांगds_घड़ी,
		    पूर्णांकel_dp->dfp.max_पंचांगds_घड़ी,
		    पूर्णांकel_dp->dfp.pcon_max_frl_bw);

	पूर्णांकel_dp_get_pcon_dsc_cap(पूर्णांकel_dp);
पूर्ण

अटल व्योम
पूर्णांकel_dp_update_420(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_connector *connector = पूर्णांकel_dp->attached_connector;
	bool is_branch, ycbcr_420_passthrough, ycbcr_444_to_420, rgb_to_ycbcr;

	/* No YCbCr output support on gmch platक्रमms */
	अगर (HAS_GMCH(i915))
		वापस;

	/*
	 * ILK करोesn't seem capable of DP YCbCr output. The
	 * displayed image is severly corrupted. SNB+ is fine.
	 */
	अगर (IS_IRONLAKE(i915))
		वापस;

	is_branch = drm_dp_is_branch(पूर्णांकel_dp->dpcd);
	ycbcr_420_passthrough =
		drm_dp_करोwnstream_420_passthrough(पूर्णांकel_dp->dpcd,
						  पूर्णांकel_dp->करोwnstream_ports);
	/* on-board LSPCON always assumed to support 4:4:4->4:2:0 conversion */
	ycbcr_444_to_420 =
		dp_to_dig_port(पूर्णांकel_dp)->lspcon.active ||
		drm_dp_करोwnstream_444_to_420_conversion(पूर्णांकel_dp->dpcd,
							पूर्णांकel_dp->करोwnstream_ports);
	rgb_to_ycbcr = drm_dp_करोwnstream_rgb_to_ycbcr_conversion(पूर्णांकel_dp->dpcd,
								 पूर्णांकel_dp->करोwnstream_ports,
								 DP_DS_HDMI_BT601_RGB_YCBCR_CONV |
								 DP_DS_HDMI_BT709_RGB_YCBCR_CONV |
								 DP_DS_HDMI_BT2020_RGB_YCBCR_CONV);

	अगर (DISPLAY_VER(i915) >= 11) अणु
		/* Let PCON convert from RGB->YCbCr अगर possible */
		अगर (is_branch && rgb_to_ycbcr && ycbcr_444_to_420) अणु
			पूर्णांकel_dp->dfp.rgb_to_ycbcr = true;
			पूर्णांकel_dp->dfp.ycbcr_444_to_420 = true;
			connector->base.ycbcr_420_allowed = true;
		पूर्ण अन्यथा अणु
		/* Prefer 4:2:0 passthrough over 4:4:4->4:2:0 conversion */
			पूर्णांकel_dp->dfp.ycbcr_444_to_420 =
				ycbcr_444_to_420 && !ycbcr_420_passthrough;

			connector->base.ycbcr_420_allowed =
				!is_branch || ycbcr_444_to_420 || ycbcr_420_passthrough;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* 4:4:4->4:2:0 conversion is the only way */
		पूर्णांकel_dp->dfp.ycbcr_444_to_420 = ycbcr_444_to_420;

		connector->base.ycbcr_420_allowed = ycbcr_444_to_420;
	पूर्ण

	drm_dbg_kms(&i915->drm,
		    "[CONNECTOR:%d:%s] RGB->YcbCr conversion? %s, YCbCr 4:2:0 allowed? %s, YCbCr 4:4:4->4:2:0 conversion? %s\n",
		    connector->base.base.id, connector->base.name,
		    yesno(पूर्णांकel_dp->dfp.rgb_to_ycbcr),
		    yesno(connector->base.ycbcr_420_allowed),
		    yesno(पूर्णांकel_dp->dfp.ycbcr_444_to_420));
पूर्ण

अटल व्योम
पूर्णांकel_dp_set_edid(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा पूर्णांकel_connector *connector = पूर्णांकel_dp->attached_connector;
	काष्ठा edid *edid;

	पूर्णांकel_dp_unset_edid(पूर्णांकel_dp);
	edid = पूर्णांकel_dp_get_edid(पूर्णांकel_dp);
	connector->detect_edid = edid;

	पूर्णांकel_dp_update_dfp(पूर्णांकel_dp, edid);
	पूर्णांकel_dp_update_420(पूर्णांकel_dp);

	अगर (edid && edid->input & DRM_EDID_INPUT_DIGITAL) अणु
		पूर्णांकel_dp->has_hdmi_sink = drm_detect_hdmi_monitor(edid);
		पूर्णांकel_dp->has_audio = drm_detect_monitor_audio(edid);
	पूर्ण

	drm_dp_cec_set_edid(&पूर्णांकel_dp->aux, edid);
पूर्ण

अटल व्योम
पूर्णांकel_dp_unset_edid(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा पूर्णांकel_connector *connector = पूर्णांकel_dp->attached_connector;

	drm_dp_cec_unset_edid(&पूर्णांकel_dp->aux);
	kमुक्त(connector->detect_edid);
	connector->detect_edid = शून्य;

	पूर्णांकel_dp->has_hdmi_sink = false;
	पूर्णांकel_dp->has_audio = false;

	पूर्णांकel_dp->dfp.max_bpc = 0;
	पूर्णांकel_dp->dfp.max_करोtघड़ी = 0;
	पूर्णांकel_dp->dfp.min_पंचांगds_घड़ी = 0;
	पूर्णांकel_dp->dfp.max_पंचांगds_घड़ी = 0;

	पूर्णांकel_dp->dfp.pcon_max_frl_bw = 0;

	पूर्णांकel_dp->dfp.ycbcr_444_to_420 = false;
	connector->base.ycbcr_420_allowed = false;
पूर्ण

अटल पूर्णांक
पूर्णांकel_dp_detect(काष्ठा drm_connector *connector,
		काष्ठा drm_modeset_acquire_ctx *ctx,
		bool क्रमce)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_attached_dp(to_पूर्णांकel_connector(connector));
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_encoder *encoder = &dig_port->base;
	क्रमागत drm_connector_status status;

	drm_dbg_kms(&dev_priv->drm, "[CONNECTOR:%d:%s]\n",
		    connector->base.id, connector->name);
	drm_WARN_ON(&dev_priv->drm,
		    !drm_modeset_is_locked(&dev_priv->drm.mode_config.connection_mutex));

	अगर (!INTEL_DISPLAY_ENABLED(dev_priv))
		वापस connector_status_disconnected;

	/* Can't disconnect eDP */
	अगर (पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		status = edp_detect(पूर्णांकel_dp);
	अन्यथा अगर (पूर्णांकel_digital_port_connected(encoder))
		status = पूर्णांकel_dp_detect_dpcd(पूर्णांकel_dp);
	अन्यथा
		status = connector_status_disconnected;

	अगर (status == connector_status_disconnected) अणु
		स_रखो(&पूर्णांकel_dp->compliance, 0, माप(पूर्णांकel_dp->compliance));
		स_रखो(पूर्णांकel_dp->dsc_dpcd, 0, माप(पूर्णांकel_dp->dsc_dpcd));

		अगर (पूर्णांकel_dp->is_mst) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "MST device may have disappeared %d vs %d\n",
				    पूर्णांकel_dp->is_mst,
				    पूर्णांकel_dp->mst_mgr.mst_state);
			पूर्णांकel_dp->is_mst = false;
			drm_dp_mst_topology_mgr_set_mst(&पूर्णांकel_dp->mst_mgr,
							पूर्णांकel_dp->is_mst);
		पूर्ण

		जाओ out;
	पूर्ण

	/* Read DP Sink DSC Cap DPCD regs क्रम DP v1.4 */
	अगर (DISPLAY_VER(dev_priv) >= 11)
		पूर्णांकel_dp_get_dsc_sink_cap(पूर्णांकel_dp);

	पूर्णांकel_dp_configure_mst(पूर्णांकel_dp);

	/*
	 * TODO: Reset link params when चयनing to MST mode, until MST
	 * supports link training fallback params.
	 */
	अगर (पूर्णांकel_dp->reset_link_params || पूर्णांकel_dp->is_mst) अणु
		/* Initial max link lane count */
		पूर्णांकel_dp->max_link_lane_count = पूर्णांकel_dp_max_common_lane_count(पूर्णांकel_dp);

		/* Initial max link rate */
		पूर्णांकel_dp->max_link_rate = पूर्णांकel_dp_max_common_rate(पूर्णांकel_dp);

		पूर्णांकel_dp->reset_link_params = false;
	पूर्ण

	पूर्णांकel_dp_prपूर्णांक_rates(पूर्णांकel_dp);

	अगर (पूर्णांकel_dp->is_mst) अणु
		/*
		 * If we are in MST mode then this connector
		 * won't appear connected or have anything
		 * with EDID on it
		 */
		status = connector_status_disconnected;
		जाओ out;
	पूर्ण

	/*
	 * Some बाह्यal monitors करो not संकेत loss of link synchronization
	 * with an IRQ_HPD, so क्रमce a link status check.
	 */
	अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp)) अणु
		पूर्णांक ret;

		ret = पूर्णांकel_dp_retrain_link(encoder, ctx);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * Clearing NACK and defer counts to get their exact values
	 * जबतक पढ़ोing EDID which are required by Compliance tests
	 * 4.2.2.4 and 4.2.2.5
	 */
	पूर्णांकel_dp->aux.i2c_nack_count = 0;
	पूर्णांकel_dp->aux.i2c_defer_count = 0;

	पूर्णांकel_dp_set_edid(पूर्णांकel_dp);
	अगर (पूर्णांकel_dp_is_edp(पूर्णांकel_dp) ||
	    to_पूर्णांकel_connector(connector)->detect_edid)
		status = connector_status_connected;

	पूर्णांकel_dp_check_device_service_irq(पूर्णांकel_dp);

out:
	अगर (status != connector_status_connected && !पूर्णांकel_dp->is_mst)
		पूर्णांकel_dp_unset_edid(पूर्णांकel_dp);

	/*
	 * Make sure the refs क्रम घातer wells enabled during detect are
	 * dropped to aव्योम a new detect cycle triggered by HPD polling.
	 */
	पूर्णांकel_display_घातer_flush_work(dev_priv);

	अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		drm_dp_set_subconnector_property(connector,
						 status,
						 पूर्णांकel_dp->dpcd,
						 पूर्णांकel_dp->करोwnstream_ports);
	वापस status;
पूर्ण

अटल व्योम
पूर्णांकel_dp_क्रमce(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_attached_dp(to_पूर्णांकel_connector(connector));
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder = &dig_port->base;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_encoder->base.dev);
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य aux_करोमुख्य =
		पूर्णांकel_aux_घातer_करोमुख्य(dig_port);
	पूर्णांकel_wakeref_t wakeref;

	drm_dbg_kms(&dev_priv->drm, "[CONNECTOR:%d:%s]\n",
		    connector->base.id, connector->name);
	पूर्णांकel_dp_unset_edid(पूर्णांकel_dp);

	अगर (connector->status != connector_status_connected)
		वापस;

	wakeref = पूर्णांकel_display_घातer_get(dev_priv, aux_करोमुख्य);

	पूर्णांकel_dp_set_edid(पूर्णांकel_dp);

	पूर्णांकel_display_घातer_put(dev_priv, aux_करोमुख्य, wakeref);
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = to_पूर्णांकel_connector(connector);
	काष्ठा edid *edid;
	पूर्णांक num_modes = 0;

	edid = पूर्णांकel_connector->detect_edid;
	अगर (edid) अणु
		num_modes = पूर्णांकel_connector_update_modes(connector, edid);

		अगर (पूर्णांकel_vrr_is_capable(connector))
			drm_connector_set_vrr_capable_property(connector,
							       true);
	पूर्ण

	/* Also add fixed mode, which may or may not be present in EDID */
	अगर (पूर्णांकel_dp_is_edp(पूर्णांकel_attached_dp(पूर्णांकel_connector)) &&
	    पूर्णांकel_connector->panel.fixed_mode) अणु
		काष्ठा drm_display_mode *mode;

		mode = drm_mode_duplicate(connector->dev,
					  पूर्णांकel_connector->panel.fixed_mode);
		अगर (mode) अणु
			drm_mode_probed_add(connector, mode);
			num_modes++;
		पूर्ण
	पूर्ण

	अगर (num_modes)
		वापस num_modes;

	अगर (!edid) अणु
		काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_attached_dp(पूर्णांकel_connector);
		काष्ठा drm_display_mode *mode;

		mode = drm_dp_करोwnstream_mode(connector->dev,
					      पूर्णांकel_dp->dpcd,
					      पूर्णांकel_dp->करोwnstream_ports);
		अगर (mode) अणु
			drm_mode_probed_add(connector, mode);
			num_modes++;
		पूर्ण
	पूर्ण

	वापस num_modes;
पूर्ण

अटल पूर्णांक
पूर्णांकel_dp_connector_रेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_attached_dp(to_पूर्णांकel_connector(connector));
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_lspcon *lspcon = &dig_port->lspcon;
	पूर्णांक ret;

	ret = पूर्णांकel_connector_रेजिस्टर(connector);
	अगर (ret)
		वापस ret;

	drm_dbg_kms(&i915->drm, "registering %s bus for %s\n",
		    पूर्णांकel_dp->aux.name, connector->kdev->kobj.name);

	पूर्णांकel_dp->aux.dev = connector->kdev;
	ret = drm_dp_aux_रेजिस्टर(&पूर्णांकel_dp->aux);
	अगर (!ret)
		drm_dp_cec_रेजिस्टर_connector(&पूर्णांकel_dp->aux, connector);

	अगर (!पूर्णांकel_bios_is_lspcon_present(i915, dig_port->base.port))
		वापस ret;

	/*
	 * ToDo: Clean this up to handle lspcon init and resume more
	 * efficiently and streamlined.
	 */
	अगर (lspcon_init(dig_port)) अणु
		lspcon_detect_hdr_capability(lspcon);
		अगर (lspcon->hdr_supported)
			drm_object_attach_property(&connector->base,
						   connector->dev->mode_config.hdr_output_metadata_property,
						   0);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
पूर्णांकel_dp_connector_unरेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_attached_dp(to_पूर्णांकel_connector(connector));

	drm_dp_cec_unरेजिस्टर_connector(&पूर्णांकel_dp->aux);
	drm_dp_aux_unरेजिस्टर(&पूर्णांकel_dp->aux);
	पूर्णांकel_connector_unरेजिस्टर(connector);
पूर्ण

व्योम पूर्णांकel_dp_encoder_flush_work(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(to_पूर्णांकel_encoder(encoder));
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = &dig_port->dp;

	पूर्णांकel_dp_mst_encoder_cleanup(dig_port);

	पूर्णांकel_pps_vdd_off_sync(पूर्णांकel_dp);

	पूर्णांकel_dp_aux_fini(पूर्णांकel_dp);
पूर्ण

व्योम पूर्णांकel_dp_encoder_suspend(काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(पूर्णांकel_encoder);

	पूर्णांकel_pps_vdd_off_sync(पूर्णांकel_dp);
पूर्ण

व्योम पूर्णांकel_dp_encoder_shutकरोwn(काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(पूर्णांकel_encoder);

	पूर्णांकel_pps_रुको_घातer_cycle(पूर्णांकel_dp);
पूर्ण

अटल पूर्णांक पूर्णांकel_modeset_tile_group(काष्ठा पूर्णांकel_atomic_state *state,
				    पूर्णांक tile_group_id)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा drm_connector *connector;
	पूर्णांक ret = 0;

	drm_connector_list_iter_begin(&dev_priv->drm, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		काष्ठा drm_connector_state *conn_state;
		काष्ठा पूर्णांकel_crtc_state *crtc_state;
		काष्ठा पूर्णांकel_crtc *crtc;

		अगर (!connector->has_tile ||
		    connector->tile_group->id != tile_group_id)
			जारी;

		conn_state = drm_atomic_get_connector_state(&state->base,
							    connector);
		अगर (IS_ERR(conn_state)) अणु
			ret = PTR_ERR(conn_state);
			अवरोध;
		पूर्ण

		crtc = to_पूर्णांकel_crtc(conn_state->crtc);

		अगर (!crtc)
			जारी;

		crtc_state = पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
		crtc_state->uapi.mode_changed = true;

		ret = drm_atomic_add_affected_planes(&state->base, &crtc->base);
		अगर (ret)
			अवरोध;
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_modeset_affected_transcoders(काष्ठा पूर्णांकel_atomic_state *state, u8 transcoders)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc;

	अगर (transcoders == 0)
		वापस 0;

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		काष्ठा पूर्णांकel_crtc_state *crtc_state;
		पूर्णांक ret;

		crtc_state = पूर्णांकel_atomic_get_crtc_state(&state->base, crtc);
		अगर (IS_ERR(crtc_state))
			वापस PTR_ERR(crtc_state);

		अगर (!crtc_state->hw.enable)
			जारी;

		अगर (!(transcoders & BIT(crtc_state->cpu_transcoder)))
			जारी;

		crtc_state->uapi.mode_changed = true;

		ret = drm_atomic_add_affected_connectors(&state->base, &crtc->base);
		अगर (ret)
			वापस ret;

		ret = drm_atomic_add_affected_planes(&state->base, &crtc->base);
		अगर (ret)
			वापस ret;

		transcoders &= ~BIT(crtc_state->cpu_transcoder);
	पूर्ण

	drm_WARN_ON(&dev_priv->drm, transcoders != 0);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_modeset_synced_crtcs(काष्ठा पूर्णांकel_atomic_state *state,
				      काष्ठा drm_connector *connector)
अणु
	स्थिर काष्ठा drm_connector_state *old_conn_state =
		drm_atomic_get_old_connector_state(&state->base, connector);
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state;
	काष्ठा पूर्णांकel_crtc *crtc;
	u8 transcoders;

	crtc = to_पूर्णांकel_crtc(old_conn_state->crtc);
	अगर (!crtc)
		वापस 0;

	old_crtc_state = पूर्णांकel_atomic_get_old_crtc_state(state, crtc);

	अगर (!old_crtc_state->hw.active)
		वापस 0;

	transcoders = old_crtc_state->sync_mode_slaves_mask;
	अगर (old_crtc_state->master_transcoder != INVALID_TRANSCODER)
		transcoders |= BIT(old_crtc_state->master_transcoder);

	वापस पूर्णांकel_modeset_affected_transcoders(state,
						  transcoders);
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_connector_atomic_check(काष्ठा drm_connector *conn,
					   काष्ठा drm_atomic_state *_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(conn->dev);
	काष्ठा पूर्णांकel_atomic_state *state = to_पूर्णांकel_atomic_state(_state);
	पूर्णांक ret;

	ret = पूर्णांकel_digital_connector_atomic_check(conn, &state->base);
	अगर (ret)
		वापस ret;

	/*
	 * We करोn't enable port sync on BDW due to missing w/as and
	 * due to not having adjusted the modeset sequence appropriately.
	 */
	अगर (DISPLAY_VER(dev_priv) < 9)
		वापस 0;

	अगर (!पूर्णांकel_connector_needs_modeset(state, conn))
		वापस 0;

	अगर (conn->has_tile) अणु
		ret = पूर्णांकel_modeset_tile_group(state, conn->tile_group->id);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस पूर्णांकel_modeset_synced_crtcs(state, conn);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs पूर्णांकel_dp_connector_funcs = अणु
	.क्रमce = पूर्णांकel_dp_क्रमce,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.atomic_get_property = पूर्णांकel_digital_connector_atomic_get_property,
	.atomic_set_property = पूर्णांकel_digital_connector_atomic_set_property,
	.late_रेजिस्टर = पूर्णांकel_dp_connector_रेजिस्टर,
	.early_unरेजिस्टर = पूर्णांकel_dp_connector_unरेजिस्टर,
	.destroy = पूर्णांकel_connector_destroy,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
	.atomic_duplicate_state = पूर्णांकel_digital_connector_duplicate_state,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs पूर्णांकel_dp_connector_helper_funcs = अणु
	.detect_ctx = पूर्णांकel_dp_detect,
	.get_modes = पूर्णांकel_dp_get_modes,
	.mode_valid = पूर्णांकel_dp_mode_valid,
	.atomic_check = पूर्णांकel_dp_connector_atomic_check,
पूर्ण;

क्रमागत irqवापस
पूर्णांकel_dp_hpd_pulse(काष्ठा पूर्णांकel_digital_port *dig_port, bool दीर्घ_hpd)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = &dig_port->dp;

	अगर (dig_port->base.type == INTEL_OUTPUT_EDP &&
	    (दीर्घ_hpd || !पूर्णांकel_pps_have_घातer(पूर्णांकel_dp))) अणु
		/*
		 * vdd off can generate a दीर्घ/लघु pulse on eDP which
		 * would require vdd on to handle it, and thus we
		 * would end up in an endless cycle of
		 * "vdd off -> long/short hpd -> vdd on -> detect -> vdd off -> ..."
		 */
		drm_dbg_kms(&i915->drm,
			    "ignoring %s hpd on eDP [ENCODER:%d:%s]\n",
			    दीर्घ_hpd ? "long" : "short",
			    dig_port->base.base.base.id,
			    dig_port->base.base.name);
		वापस IRQ_HANDLED;
	पूर्ण

	drm_dbg_kms(&i915->drm, "got hpd irq on [ENCODER:%d:%s] - %s\n",
		    dig_port->base.base.base.id,
		    dig_port->base.base.name,
		    दीर्घ_hpd ? "long" : "short");

	अगर (दीर्घ_hpd) अणु
		पूर्णांकel_dp->reset_link_params = true;
		वापस IRQ_NONE;
	पूर्ण

	अगर (पूर्णांकel_dp->is_mst) अणु
		अगर (!पूर्णांकel_dp_check_mst_status(पूर्णांकel_dp))
			वापस IRQ_NONE;
	पूर्ण अन्यथा अगर (!पूर्णांकel_dp_लघु_pulse(पूर्णांकel_dp)) अणु
		वापस IRQ_NONE;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/* check the VBT to see whether the eDP is on another port */
bool पूर्णांकel_dp_is_port_edp(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port port)
अणु
	/*
	 * eDP not supported on g4x. so bail out early just
	 * क्रम a bit extra safety in हाल the VBT is bonkers.
	 */
	अगर (DISPLAY_VER(dev_priv) < 5)
		वापस false;

	अगर (DISPLAY_VER(dev_priv) < 9 && port == PORT_A)
		वापस true;

	वापस पूर्णांकel_bios_is_port_edp(dev_priv, port);
पूर्ण

अटल व्योम
पूर्णांकel_dp_add_properties(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->dev);
	क्रमागत port port = dp_to_dig_port(पूर्णांकel_dp)->base.port;

	अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		drm_connector_attach_dp_subconnector_property(connector);

	अगर (!IS_G4X(dev_priv) && port != PORT_A)
		पूर्णांकel_attach_क्रमce_audio_property(connector);

	पूर्णांकel_attach_broadcast_rgb_property(connector);
	अगर (HAS_GMCH(dev_priv))
		drm_connector_attach_max_bpc_property(connector, 6, 10);
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 5)
		drm_connector_attach_max_bpc_property(connector, 6, 12);

	/* Register HDMI colorspace क्रम हाल of lspcon */
	अगर (पूर्णांकel_bios_is_lspcon_present(dev_priv, port)) अणु
		drm_connector_attach_content_type_property(connector);
		पूर्णांकel_attach_hdmi_colorspace_property(connector);
	पूर्ण अन्यथा अणु
		पूर्णांकel_attach_dp_colorspace_property(connector);
	पूर्ण

	अगर (IS_GEMINILAKE(dev_priv) || DISPLAY_VER(dev_priv) >= 11)
		drm_object_attach_property(&connector->base,
					   connector->dev->mode_config.hdr_output_metadata_property,
					   0);

	अगर (पूर्णांकel_dp_is_edp(पूर्णांकel_dp)) अणु
		u32 allowed_scalers;

		allowed_scalers = BIT(DRM_MODE_SCALE_ASPECT) | BIT(DRM_MODE_SCALE_FULLSCREEN);
		अगर (!HAS_GMCH(dev_priv))
			allowed_scalers |= BIT(DRM_MODE_SCALE_CENTER);

		drm_connector_attach_scaling_mode_property(connector, allowed_scalers);

		connector->state->scaling_mode = DRM_MODE_SCALE_ASPECT;

	पूर्ण

	अगर (HAS_VRR(dev_priv))
		drm_connector_attach_vrr_capable_property(connector);
पूर्ण

/**
 * पूर्णांकel_dp_set_drrs_state - program रेजिस्टरs क्रम RR चयन to take effect
 * @dev_priv: i915 device
 * @crtc_state: a poपूर्णांकer to the active पूर्णांकel_crtc_state
 * @refresh_rate: RR to be programmed
 *
 * This function माला_लो called when refresh rate (RR) has to be changed from
 * one frequency to another. Switches can be between high and low RR
 * supported by the panel or to any other RR based on media playback (in
 * this हाल, RR value needs to be passed from user space).
 *
 * The caller of this function needs to take a lock on dev_priv->drrs.
 */
अटल व्योम पूर्णांकel_dp_set_drrs_state(काष्ठा drm_i915_निजी *dev_priv,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				    पूर्णांक refresh_rate)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = dev_priv->drrs.dp;
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	क्रमागत drrs_refresh_rate_type index = DRRS_HIGH_RR;

	अगर (refresh_rate <= 0) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Refresh rate should be positive non-zero.\n");
		वापस;
	पूर्ण

	अगर (पूर्णांकel_dp == शून्य) अणु
		drm_dbg_kms(&dev_priv->drm, "DRRS not supported.\n");
		वापस;
	पूर्ण

	अगर (!पूर्णांकel_crtc) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "DRRS: intel_crtc not initialized\n");
		वापस;
	पूर्ण

	अगर (dev_priv->drrs.type < SEAMLESS_DRRS_SUPPORT) अणु
		drm_dbg_kms(&dev_priv->drm, "Only Seamless DRRS supported.\n");
		वापस;
	पूर्ण

	अगर (drm_mode_vrefresh(पूर्णांकel_dp->attached_connector->panel.करोwnघड़ी_mode) ==
			refresh_rate)
		index = DRRS_LOW_RR;

	अगर (index == dev_priv->drrs.refresh_rate_type) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "DRRS requested for previously set RR...ignoring\n");
		वापस;
	पूर्ण

	अगर (!crtc_state->hw.active) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "eDP encoder disabled. CRTC not Active\n");
		वापस;
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) >= 8 && !IS_CHERRYVIEW(dev_priv)) अणु
		चयन (index) अणु
		हाल DRRS_HIGH_RR:
			पूर्णांकel_dp_set_m_n(crtc_state, M1_N1);
			अवरोध;
		हाल DRRS_LOW_RR:
			पूर्णांकel_dp_set_m_n(crtc_state, M2_N2);
			अवरोध;
		हाल DRRS_MAX_RR:
		शेष:
			drm_err(&dev_priv->drm,
				"Unsupported refreshrate type\n");
		पूर्ण
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) > 6) अणु
		i915_reg_t reg = PIPECONF(crtc_state->cpu_transcoder);
		u32 val;

		val = पूर्णांकel_de_पढ़ो(dev_priv, reg);
		अगर (index > DRRS_HIGH_RR) अणु
			अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
				val |= PIPECONF_EDP_RR_MODE_SWITCH_VLV;
			अन्यथा
				val |= PIPECONF_EDP_RR_MODE_SWITCH;
		पूर्ण अन्यथा अणु
			अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
				val &= ~PIPECONF_EDP_RR_MODE_SWITCH_VLV;
			अन्यथा
				val &= ~PIPECONF_EDP_RR_MODE_SWITCH;
		पूर्ण
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
	पूर्ण

	dev_priv->drrs.refresh_rate_type = index;

	drm_dbg_kms(&dev_priv->drm, "eDP Refresh Rate set to : %dHz\n",
		    refresh_rate);
पूर्ण

अटल व्योम
पूर्णांकel_edp_drrs_enable_locked(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);

	dev_priv->drrs.busy_frontbuffer_bits = 0;
	dev_priv->drrs.dp = पूर्णांकel_dp;
पूर्ण

/**
 * पूर्णांकel_edp_drrs_enable - init drrs काष्ठा अगर supported
 * @पूर्णांकel_dp: DP काष्ठा
 * @crtc_state: A poपूर्णांकer to the active crtc state.
 *
 * Initializes frontbuffer_bits and drrs.dp
 */
व्योम पूर्णांकel_edp_drrs_enable(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);

	अगर (!crtc_state->has_drrs)
		वापस;

	drm_dbg_kms(&dev_priv->drm, "Enabling DRRS\n");

	mutex_lock(&dev_priv->drrs.mutex);

	अगर (dev_priv->drrs.dp) अणु
		drm_warn(&dev_priv->drm, "DRRS already enabled\n");
		जाओ unlock;
	पूर्ण

	पूर्णांकel_edp_drrs_enable_locked(पूर्णांकel_dp);

unlock:
	mutex_unlock(&dev_priv->drrs.mutex);
पूर्ण

अटल व्योम
पूर्णांकel_edp_drrs_disable_locked(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);

	अगर (dev_priv->drrs.refresh_rate_type == DRRS_LOW_RR) अणु
		पूर्णांक refresh;

		refresh = drm_mode_vrefresh(पूर्णांकel_dp->attached_connector->panel.fixed_mode);
		पूर्णांकel_dp_set_drrs_state(dev_priv, crtc_state, refresh);
	पूर्ण

	dev_priv->drrs.dp = शून्य;
पूर्ण

/**
 * पूर्णांकel_edp_drrs_disable - Disable DRRS
 * @पूर्णांकel_dp: DP काष्ठा
 * @old_crtc_state: Poपूर्णांकer to old crtc_state.
 *
 */
व्योम पूर्णांकel_edp_drrs_disable(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);

	अगर (!old_crtc_state->has_drrs)
		वापस;

	mutex_lock(&dev_priv->drrs.mutex);
	अगर (!dev_priv->drrs.dp) अणु
		mutex_unlock(&dev_priv->drrs.mutex);
		वापस;
	पूर्ण

	पूर्णांकel_edp_drrs_disable_locked(पूर्णांकel_dp, old_crtc_state);
	mutex_unlock(&dev_priv->drrs.mutex);

	cancel_delayed_work_sync(&dev_priv->drrs.work);
पूर्ण

/**
 * पूर्णांकel_edp_drrs_update - Update DRRS state
 * @पूर्णांकel_dp: Intel DP
 * @crtc_state: new CRTC state
 *
 * This function will update DRRS states, disabling or enabling DRRS when
 * executing fastsets. For full modeset, पूर्णांकel_edp_drrs_disable() and
 * पूर्णांकel_edp_drrs_enable() should be called instead.
 */
व्योम
पूर्णांकel_edp_drrs_update(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);

	अगर (dev_priv->drrs.type != SEAMLESS_DRRS_SUPPORT)
		वापस;

	mutex_lock(&dev_priv->drrs.mutex);

	/* New state matches current one? */
	अगर (crtc_state->has_drrs == !!dev_priv->drrs.dp)
		जाओ unlock;

	अगर (crtc_state->has_drrs)
		पूर्णांकel_edp_drrs_enable_locked(पूर्णांकel_dp);
	अन्यथा
		पूर्णांकel_edp_drrs_disable_locked(पूर्णांकel_dp, crtc_state);

unlock:
	mutex_unlock(&dev_priv->drrs.mutex);
पूर्ण

अटल व्योम पूर्णांकel_edp_drrs_करोwnघड़ी_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		container_of(work, typeof(*dev_priv), drrs.work.work);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp;

	mutex_lock(&dev_priv->drrs.mutex);

	पूर्णांकel_dp = dev_priv->drrs.dp;

	अगर (!पूर्णांकel_dp)
		जाओ unlock;

	/*
	 * The delayed work can race with an invalidate hence we need to
	 * recheck.
	 */

	अगर (dev_priv->drrs.busy_frontbuffer_bits)
		जाओ unlock;

	अगर (dev_priv->drrs.refresh_rate_type != DRRS_LOW_RR) अणु
		काष्ठा drm_crtc *crtc = dp_to_dig_port(पूर्णांकel_dp)->base.base.crtc;

		पूर्णांकel_dp_set_drrs_state(dev_priv, to_पूर्णांकel_crtc(crtc)->config,
			drm_mode_vrefresh(पूर्णांकel_dp->attached_connector->panel.करोwnघड़ी_mode));
	पूर्ण

unlock:
	mutex_unlock(&dev_priv->drrs.mutex);
पूर्ण

/**
 * पूर्णांकel_edp_drrs_invalidate - Disable Idleness DRRS
 * @dev_priv: i915 device
 * @frontbuffer_bits: frontbuffer plane tracking bits
 *
 * This function माला_लो called everyसमय rendering on the given planes start.
 * Hence DRRS needs to be Upघड़ीed, i.e. (LOW_RR -> HIGH_RR).
 *
 * Dirty frontbuffers relevant to DRRS are tracked in busy_frontbuffer_bits.
 */
व्योम पूर्णांकel_edp_drrs_invalidate(काष्ठा drm_i915_निजी *dev_priv,
			       अचिन्हित पूर्णांक frontbuffer_bits)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp;
	काष्ठा drm_crtc *crtc;
	क्रमागत pipe pipe;

	अगर (dev_priv->drrs.type == DRRS_NOT_SUPPORTED)
		वापस;

	cancel_delayed_work(&dev_priv->drrs.work);

	mutex_lock(&dev_priv->drrs.mutex);

	पूर्णांकel_dp = dev_priv->drrs.dp;
	अगर (!पूर्णांकel_dp) अणु
		mutex_unlock(&dev_priv->drrs.mutex);
		वापस;
	पूर्ण

	crtc = dp_to_dig_port(पूर्णांकel_dp)->base.base.crtc;
	pipe = to_पूर्णांकel_crtc(crtc)->pipe;

	frontbuffer_bits &= INTEL_FRONTBUFFER_ALL_MASK(pipe);
	dev_priv->drrs.busy_frontbuffer_bits |= frontbuffer_bits;

	/* invalidate means busy screen hence upघड़ी */
	अगर (frontbuffer_bits && dev_priv->drrs.refresh_rate_type == DRRS_LOW_RR)
		पूर्णांकel_dp_set_drrs_state(dev_priv, to_पूर्णांकel_crtc(crtc)->config,
					drm_mode_vrefresh(पूर्णांकel_dp->attached_connector->panel.fixed_mode));

	mutex_unlock(&dev_priv->drrs.mutex);
पूर्ण

/**
 * पूर्णांकel_edp_drrs_flush - Restart Idleness DRRS
 * @dev_priv: i915 device
 * @frontbuffer_bits: frontbuffer plane tracking bits
 *
 * This function माला_लो called every समय rendering on the given planes has
 * completed or flip on a crtc is completed. So DRRS should be upघड़ीed
 * (LOW_RR -> HIGH_RR). And also Idleness detection should be started again,
 * अगर no other planes are dirty.
 *
 * Dirty frontbuffers relevant to DRRS are tracked in busy_frontbuffer_bits.
 */
व्योम पूर्णांकel_edp_drrs_flush(काष्ठा drm_i915_निजी *dev_priv,
			  अचिन्हित पूर्णांक frontbuffer_bits)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp;
	काष्ठा drm_crtc *crtc;
	क्रमागत pipe pipe;

	अगर (dev_priv->drrs.type == DRRS_NOT_SUPPORTED)
		वापस;

	cancel_delayed_work(&dev_priv->drrs.work);

	mutex_lock(&dev_priv->drrs.mutex);

	पूर्णांकel_dp = dev_priv->drrs.dp;
	अगर (!पूर्णांकel_dp) अणु
		mutex_unlock(&dev_priv->drrs.mutex);
		वापस;
	पूर्ण

	crtc = dp_to_dig_port(पूर्णांकel_dp)->base.base.crtc;
	pipe = to_पूर्णांकel_crtc(crtc)->pipe;

	frontbuffer_bits &= INTEL_FRONTBUFFER_ALL_MASK(pipe);
	dev_priv->drrs.busy_frontbuffer_bits &= ~frontbuffer_bits;

	/* flush means busy screen hence upघड़ी */
	अगर (frontbuffer_bits && dev_priv->drrs.refresh_rate_type == DRRS_LOW_RR)
		पूर्णांकel_dp_set_drrs_state(dev_priv, to_पूर्णांकel_crtc(crtc)->config,
					drm_mode_vrefresh(पूर्णांकel_dp->attached_connector->panel.fixed_mode));

	/*
	 * flush also means no more activity hence schedule करोwnघड़ी, अगर all
	 * other fbs are quiescent too
	 */
	अगर (!dev_priv->drrs.busy_frontbuffer_bits)
		schedule_delayed_work(&dev_priv->drrs.work,
				msecs_to_jअगरfies(1000));
	mutex_unlock(&dev_priv->drrs.mutex);
पूर्ण

/**
 * DOC: Display Refresh Rate Switching (DRRS)
 *
 * Display Refresh Rate Switching (DRRS) is a घातer conservation feature
 * which enables swtching between low and high refresh rates,
 * dynamically, based on the usage scenario. This feature is applicable
 * क्रम पूर्णांकernal panels.
 *
 * Indication that the panel supports DRRS is given by the panel EDID, which
 * would list multiple refresh rates क्रम one resolution.
 *
 * DRRS is of 2 types - अटल and seamless.
 * Static DRRS involves changing refresh rate (RR) by करोing a full modeset
 * (may appear as a blink on screen) and is used in करोck-unकरोck scenario.
 * Seamless DRRS involves changing RR without any visual effect to the user
 * and can be used during normal प्रणाली usage. This is करोne by programming
 * certain रेजिस्टरs.
 *
 * Support क्रम अटल/seamless DRRS may be indicated in the VBT based on
 * inमाला_दो from the panel spec.
 *
 * DRRS saves घातer by चयनing to low RR based on usage scenarios.
 *
 * The implementation is based on frontbuffer tracking implementation.  When
 * there is a disturbance on the screen triggered by user activity or a periodic
 * प्रणाली activity, DRRS is disabled (RR is changed to high RR).  When there is
 * no movement on screen, after a समयout of 1 second, a चयन to low RR is
 * made.
 *
 * For पूर्णांकegration with frontbuffer tracking code, पूर्णांकel_edp_drrs_invalidate()
 * and पूर्णांकel_edp_drrs_flush() are called.
 *
 * DRRS can be further extended to support other पूर्णांकernal panels and also
 * the scenario of video playback wherein RR is set based on the rate
 * requested by userspace.
 */

/**
 * पूर्णांकel_dp_drrs_init - Init basic DRRS work and mutex.
 * @connector: eDP connector
 * @fixed_mode: preferred mode of panel
 *
 * This function is  called only once at driver load to initialize basic
 * DRRS stuff.
 *
 * Returns:
 * Downघड़ी mode अगर panel supports it, अन्यथा वापस शून्य.
 * DRRS support is determined by the presence of करोwnघड़ी mode (apart
 * from VBT setting).
 */
अटल काष्ठा drm_display_mode *
पूर्णांकel_dp_drrs_init(काष्ठा पूर्णांकel_connector *connector,
		   काष्ठा drm_display_mode *fixed_mode)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा drm_display_mode *करोwnघड़ी_mode = शून्य;

	INIT_DELAYED_WORK(&dev_priv->drrs.work, पूर्णांकel_edp_drrs_करोwnघड़ी_work);
	mutex_init(&dev_priv->drrs.mutex);

	अगर (DISPLAY_VER(dev_priv) <= 6) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "DRRS supported for Gen7 and above\n");
		वापस शून्य;
	पूर्ण

	अगर (dev_priv->vbt.drrs_type != SEAMLESS_DRRS_SUPPORT) अणु
		drm_dbg_kms(&dev_priv->drm, "VBT doesn't support DRRS\n");
		वापस शून्य;
	पूर्ण

	करोwnघड़ी_mode = पूर्णांकel_panel_edid_करोwnघड़ी_mode(connector, fixed_mode);
	अगर (!करोwnघड़ी_mode) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Downclock mode is not found. DRRS not supported\n");
		वापस शून्य;
	पूर्ण

	dev_priv->drrs.type = dev_priv->vbt.drrs_type;

	dev_priv->drrs.refresh_rate_type = DRRS_HIGH_RR;
	drm_dbg_kms(&dev_priv->drm,
		    "seamless DRRS supported for eDP panel.\n");
	वापस करोwnघड़ी_mode;
पूर्ण

अटल bool पूर्णांकel_edp_init_connector(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				     काष्ठा पूर्णांकel_connector *पूर्णांकel_connector)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा drm_connector *connector = &पूर्णांकel_connector->base;
	काष्ठा drm_display_mode *fixed_mode = शून्य;
	काष्ठा drm_display_mode *करोwnघड़ी_mode = शून्य;
	bool has_dpcd;
	क्रमागत pipe pipe = INVALID_PIPE;
	काष्ठा edid *edid;

	अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		वापस true;

	/*
	 * On IBX/CPT we may get here with LVDS alपढ़ोy रेजिस्टरed. Since the
	 * driver uses the only पूर्णांकernal घातer sequencer available क्रम both
	 * eDP and LVDS bail out early in this हाल to prevent पूर्णांकerfering
	 * with an alपढ़ोy घातered-on LVDS घातer sequencer.
	 */
	अगर (पूर्णांकel_get_lvds_encoder(dev_priv)) अणु
		drm_WARN_ON(dev,
			    !(HAS_PCH_IBX(dev_priv) || HAS_PCH_CPT(dev_priv)));
		drm_info(&dev_priv->drm,
			 "LVDS was detected, not registering eDP\n");

		वापस false;
	पूर्ण

	पूर्णांकel_pps_init(पूर्णांकel_dp);

	/* Cache DPCD and EDID क्रम edp. */
	has_dpcd = पूर्णांकel_edp_init_dpcd(पूर्णांकel_dp);

	अगर (!has_dpcd) अणु
		/* अगर this fails, presume the device is a ghost */
		drm_info(&dev_priv->drm,
			 "failed to retrieve link info, disabling eDP\n");
		जाओ out_vdd_off;
	पूर्ण

	mutex_lock(&dev->mode_config.mutex);
	edid = drm_get_edid(connector, &पूर्णांकel_dp->aux.ddc);
	अगर (edid) अणु
		अगर (drm_add_edid_modes(connector, edid)) अणु
			drm_connector_update_edid_property(connector, edid);
		पूर्ण अन्यथा अणु
			kमुक्त(edid);
			edid = ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण अन्यथा अणु
		edid = ERR_PTR(-ENOENT);
	पूर्ण
	पूर्णांकel_connector->edid = edid;

	fixed_mode = पूर्णांकel_panel_edid_fixed_mode(पूर्णांकel_connector);
	अगर (fixed_mode)
		करोwnघड़ी_mode = पूर्णांकel_dp_drrs_init(पूर्णांकel_connector, fixed_mode);

	/* multiply the mode घड़ी and horizontal timings क्रम MSO */
	पूर्णांकel_edp_mso_mode_fixup(पूर्णांकel_connector, fixed_mode);
	पूर्णांकel_edp_mso_mode_fixup(पूर्णांकel_connector, करोwnघड़ी_mode);

	/* fallback to VBT अगर available क्रम eDP */
	अगर (!fixed_mode)
		fixed_mode = पूर्णांकel_panel_vbt_fixed_mode(पूर्णांकel_connector);
	mutex_unlock(&dev->mode_config.mutex);

	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		/*
		 * Figure out the current pipe क्रम the initial backlight setup.
		 * If the current pipe isn't valid, try the PPS pipe, and अगर that
		 * fails just assume pipe A.
		 */
		pipe = vlv_active_pipe(पूर्णांकel_dp);

		अगर (pipe != PIPE_A && pipe != PIPE_B)
			pipe = पूर्णांकel_dp->pps.pps_pipe;

		अगर (pipe != PIPE_A && pipe != PIPE_B)
			pipe = PIPE_A;

		drm_dbg_kms(&dev_priv->drm,
			    "using pipe %c for initial backlight setup\n",
			    pipe_name(pipe));
	पूर्ण

	पूर्णांकel_panel_init(&पूर्णांकel_connector->panel, fixed_mode, करोwnघड़ी_mode);
	पूर्णांकel_connector->panel.backlight.घातer = पूर्णांकel_pps_backlight_घातer;
	पूर्णांकel_panel_setup_backlight(connector, pipe);

	अगर (fixed_mode) अणु
		drm_connector_set_panel_orientation_with_quirk(connector,
				dev_priv->vbt.orientation,
				fixed_mode->hdisplay, fixed_mode->vdisplay);
	पूर्ण

	वापस true;

out_vdd_off:
	पूर्णांकel_pps_vdd_off_sync(पूर्णांकel_dp);

	वापस false;
पूर्ण

अटल व्योम पूर्णांकel_dp_modeset_retry_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector;
	काष्ठा drm_connector *connector;

	पूर्णांकel_connector = container_of(work, typeof(*पूर्णांकel_connector),
				       modeset_retry_work);
	connector = &पूर्णांकel_connector->base;
	DRM_DEBUG_KMS("[CONNECTOR:%d:%s]\n", connector->base.id,
		      connector->name);

	/* Grab the locks beक्रमe changing connector property*/
	mutex_lock(&connector->dev->mode_config.mutex);
	/* Set connector link status to BAD and send a Uevent to notअगरy
	 * userspace to करो a modeset.
	 */
	drm_connector_set_link_status_property(connector,
					       DRM_MODE_LINK_STATUS_BAD);
	mutex_unlock(&connector->dev->mode_config.mutex);
	/* Send Hotplug uevent so userspace can reprobe */
	drm_kms_helper_hotplug_event(connector->dev);
पूर्ण

bool
पूर्णांकel_dp_init_connector(काष्ठा पूर्णांकel_digital_port *dig_port,
			काष्ठा पूर्णांकel_connector *पूर्णांकel_connector)
अणु
	काष्ठा drm_connector *connector = &पूर्णांकel_connector->base;
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = &dig_port->dp;
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder = &dig_port->base;
	काष्ठा drm_device *dev = पूर्णांकel_encoder->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत port port = पूर्णांकel_encoder->port;
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, port);
	पूर्णांक type;

	/* Initialize the work क्रम modeset in हाल of link train failure */
	INIT_WORK(&पूर्णांकel_connector->modeset_retry_work,
		  पूर्णांकel_dp_modeset_retry_work_fn);

	अगर (drm_WARN(dev, dig_port->max_lanes < 1,
		     "Not enough lanes (%d) for DP on [ENCODER:%d:%s]\n",
		     dig_port->max_lanes, पूर्णांकel_encoder->base.base.id,
		     पूर्णांकel_encoder->base.name))
		वापस false;

	पूर्णांकel_dp_set_source_rates(पूर्णांकel_dp);

	पूर्णांकel_dp->reset_link_params = true;
	पूर्णांकel_dp->pps.pps_pipe = INVALID_PIPE;
	पूर्णांकel_dp->pps.active_pipe = INVALID_PIPE;

	/* Preserve the current hw state. */
	पूर्णांकel_dp->DP = पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg);
	पूर्णांकel_dp->attached_connector = पूर्णांकel_connector;

	अगर (पूर्णांकel_dp_is_port_edp(dev_priv, port)) अणु
		/*
		 * Currently we करोn't support eDP on TypeC ports, although in
		 * theory it could work on TypeC legacy ports.
		 */
		drm_WARN_ON(dev, पूर्णांकel_phy_is_tc(dev_priv, phy));
		type = DRM_MODE_CONNECTOR_eDP;
	पूर्ण अन्यथा अणु
		type = DRM_MODE_CONNECTOR_DisplayPort;
	पूर्ण

	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		पूर्णांकel_dp->pps.active_pipe = vlv_active_pipe(पूर्णांकel_dp);

	/*
	 * For eDP we always set the encoder type to INTEL_OUTPUT_EDP, but
	 * क्रम DP the encoder type can be set by the caller to
	 * INTEL_OUTPUT_UNKNOWN क्रम DDI, so करोn't reग_लिखो it.
	 */
	अगर (type == DRM_MODE_CONNECTOR_eDP)
		पूर्णांकel_encoder->type = INTEL_OUTPUT_EDP;

	/* eDP only on port B and/or C on vlv/chv */
	अगर (drm_WARN_ON(dev, (IS_VALLEYVIEW(dev_priv) ||
			      IS_CHERRYVIEW(dev_priv)) &&
			पूर्णांकel_dp_is_edp(पूर्णांकel_dp) &&
			port != PORT_B && port != PORT_C))
		वापस false;

	drm_dbg_kms(&dev_priv->drm,
		    "Adding %s connector on [ENCODER:%d:%s]\n",
		    type == DRM_MODE_CONNECTOR_eDP ? "eDP" : "DP",
		    पूर्णांकel_encoder->base.base.id, पूर्णांकel_encoder->base.name);

	drm_connector_init(dev, connector, &पूर्णांकel_dp_connector_funcs, type);
	drm_connector_helper_add(connector, &पूर्णांकel_dp_connector_helper_funcs);

	अगर (!HAS_GMCH(dev_priv))
		connector->पूर्णांकerlace_allowed = true;
	connector->द्विगुनscan_allowed = 0;

	पूर्णांकel_connector->polled = DRM_CONNECTOR_POLL_HPD;

	पूर्णांकel_dp_aux_init(पूर्णांकel_dp);

	पूर्णांकel_connector_attach_encoder(पूर्णांकel_connector, पूर्णांकel_encoder);

	अगर (HAS_DDI(dev_priv))
		पूर्णांकel_connector->get_hw_state = पूर्णांकel_ddi_connector_get_hw_state;
	अन्यथा
		पूर्णांकel_connector->get_hw_state = पूर्णांकel_connector_get_hw_state;

	/* init MST on ports that can support it */
	पूर्णांकel_dp_mst_encoder_init(dig_port,
				  पूर्णांकel_connector->base.base.id);

	अगर (!पूर्णांकel_edp_init_connector(पूर्णांकel_dp, पूर्णांकel_connector)) अणु
		पूर्णांकel_dp_aux_fini(पूर्णांकel_dp);
		पूर्णांकel_dp_mst_encoder_cleanup(dig_port);
		जाओ fail;
	पूर्ण

	पूर्णांकel_dp_add_properties(पूर्णांकel_dp, connector);

	अगर (is_hdcp_supported(dev_priv, port) && !पूर्णांकel_dp_is_edp(पूर्णांकel_dp)) अणु
		पूर्णांक ret = पूर्णांकel_dp_init_hdcp(dig_port, पूर्णांकel_connector);
		अगर (ret)
			drm_dbg_kms(&dev_priv->drm,
				    "HDCP init failed, skipping.\n");
	पूर्ण

	/* For G4X desktop chip, PEG_BAND_GAP_DATA 3:0 must first be written
	 * 0xd.  Failure to करो so will result in spurious पूर्णांकerrupts being
	 * generated on the port when a cable is not attached.
	 */
	अगर (IS_G45(dev_priv)) अणु
		u32 temp = पूर्णांकel_de_पढ़ो(dev_priv, PEG_BAND_GAP_DATA);
		पूर्णांकel_de_ग_लिखो(dev_priv, PEG_BAND_GAP_DATA,
			       (temp & ~0xf) | 0xd);
	पूर्ण

	पूर्णांकel_dp->frl.is_trained = false;
	पूर्णांकel_dp->frl.trained_rate_gbps = 0;

	पूर्णांकel_psr_init(पूर्णांकel_dp);

	वापस true;

fail:
	drm_connector_cleanup(connector);

	वापस false;
पूर्ण

व्योम पूर्णांकel_dp_mst_suspend(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_encoder *encoder;

	क्रम_each_पूर्णांकel_encoder(&dev_priv->drm, encoder) अणु
		काष्ठा पूर्णांकel_dp *पूर्णांकel_dp;

		अगर (encoder->type != INTEL_OUTPUT_DDI)
			जारी;

		पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);

		अगर (!पूर्णांकel_dp->can_mst)
			जारी;

		अगर (पूर्णांकel_dp->is_mst)
			drm_dp_mst_topology_mgr_suspend(&पूर्णांकel_dp->mst_mgr);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_dp_mst_resume(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_encoder *encoder;

	क्रम_each_पूर्णांकel_encoder(&dev_priv->drm, encoder) अणु
		काष्ठा पूर्णांकel_dp *पूर्णांकel_dp;
		पूर्णांक ret;

		अगर (encoder->type != INTEL_OUTPUT_DDI)
			जारी;

		पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);

		अगर (!पूर्णांकel_dp->can_mst)
			जारी;

		ret = drm_dp_mst_topology_mgr_resume(&पूर्णांकel_dp->mst_mgr,
						     true);
		अगर (ret) अणु
			पूर्णांकel_dp->is_mst = false;
			drm_dp_mst_topology_mgr_set_mst(&पूर्णांकel_dp->mst_mgr,
							false);
		पूर्ण
	पूर्ण
पूर्ण
