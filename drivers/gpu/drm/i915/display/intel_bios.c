<शैली गुरु>
/*
 * Copyright तऊ 2006 Intel Corporation
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
 *    Eric Anholt <eric@anholt.net>
 *
 */

#समावेश <drm/drm_dp_helper.h>

#समावेश "display/intel_display.h"
#समावेश "display/intel_display_types.h"
#समावेश "display/intel_gmbus.h"

#समावेश "i915_drv.h"

#घोषणा _INTEL_BIOS_PRIVATE
#समावेश "intel_vbt_defs.h"

/**
 * DOC: Video BIOS Table (VBT)
 *
 * The Video BIOS Table, or VBT, provides platक्रमm and board specअगरic
 * configuration inक्रमmation to the driver that is not discoverable or available
 * through other means. The configuration is mostly related to display
 * hardware. The VBT is available via the ACPI OpRegion or, on older प्रणालीs, in
 * the PCI ROM.
 *
 * The VBT consists of a VBT Header (defined as &काष्ठा vbt_header), a BDB
 * Header (&काष्ठा bdb_header), and a number of BIOS Data Blocks (BDB) that
 * contain the actual configuration inक्रमmation. The VBT Header, and thus the
 * VBT, begins with "$VBT" signature. The VBT Header contains the offset of the
 * BDB Header. The data blocks are concatenated after the BDB Header. The data
 * blocks have a 1-byte Block ID, 2-byte Block Size, and Block Size bytes of
 * data. (Block 53, the MIPI Sequence Block is an exception.)
 *
 * The driver parses the VBT during load. The relevant inक्रमmation is stored in
 * driver निजी data क्रम ease of use, and the actual VBT is not पढ़ो after
 * that.
 */

/* Wrapper क्रम VBT child device config */
काष्ठा पूर्णांकel_bios_encoder_data अणु
	काष्ठा drm_i915_निजी *i915;

	काष्ठा child_device_config child;
	काष्ठा dsc_compression_parameters_entry *dsc;
	काष्ठा list_head node;
पूर्ण;

#घोषणा	SLAVE_ADDR1	0x70
#घोषणा	SLAVE_ADDR2	0x72

/* Get BDB block size given a poपूर्णांकer to Block ID. */
अटल u32 _get_blocksize(स्थिर u8 *block_base)
अणु
	/* The MIPI Sequence Block v3+ has a separate size field. */
	अगर (*block_base == BDB_MIPI_SEQUENCE && *(block_base + 3) >= 3)
		वापस *((स्थिर u32 *)(block_base + 4));
	अन्यथा
		वापस *((स्थिर u16 *)(block_base + 1));
पूर्ण

/* Get BDB block size give a poपूर्णांकer to data after Block ID and Block Size. */
अटल u32 get_blocksize(स्थिर व्योम *block_data)
अणु
	वापस _get_blocksize(block_data - 3);
पूर्ण

अटल स्थिर व्योम *
find_section(स्थिर व्योम *_bdb, क्रमागत bdb_block_id section_id)
अणु
	स्थिर काष्ठा bdb_header *bdb = _bdb;
	स्थिर u8 *base = _bdb;
	पूर्णांक index = 0;
	u32 total, current_size;
	क्रमागत bdb_block_id current_id;

	/* skip to first section */
	index += bdb->header_size;
	total = bdb->bdb_size;

	/* walk the sections looking क्रम section_id */
	जबतक (index + 3 < total) अणु
		current_id = *(base + index);
		current_size = _get_blocksize(base + index);
		index += 3;

		अगर (index + current_size > total)
			वापस शून्य;

		अगर (current_id == section_id)
			वापस base + index;

		index += current_size;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम
fill_detail_timing_data(काष्ठा drm_display_mode *panel_fixed_mode,
			स्थिर काष्ठा lvds_dvo_timing *dvo_timing)
अणु
	panel_fixed_mode->hdisplay = (dvo_timing->hactive_hi << 8) |
		dvo_timing->hactive_lo;
	panel_fixed_mode->hsync_start = panel_fixed_mode->hdisplay +
		((dvo_timing->hsync_off_hi << 8) | dvo_timing->hsync_off_lo);
	panel_fixed_mode->hsync_end = panel_fixed_mode->hsync_start +
		((dvo_timing->hsync_pulse_width_hi << 8) |
			dvo_timing->hsync_pulse_width_lo);
	panel_fixed_mode->htotal = panel_fixed_mode->hdisplay +
		((dvo_timing->hblank_hi << 8) | dvo_timing->hblank_lo);

	panel_fixed_mode->vdisplay = (dvo_timing->vactive_hi << 8) |
		dvo_timing->vactive_lo;
	panel_fixed_mode->vsync_start = panel_fixed_mode->vdisplay +
		((dvo_timing->vsync_off_hi << 4) | dvo_timing->vsync_off_lo);
	panel_fixed_mode->vsync_end = panel_fixed_mode->vsync_start +
		((dvo_timing->vsync_pulse_width_hi << 4) |
			dvo_timing->vsync_pulse_width_lo);
	panel_fixed_mode->vtotal = panel_fixed_mode->vdisplay +
		((dvo_timing->vblank_hi << 8) | dvo_timing->vblank_lo);
	panel_fixed_mode->घड़ी = dvo_timing->घड़ी * 10;
	panel_fixed_mode->type = DRM_MODE_TYPE_PREFERRED;

	अगर (dvo_timing->hsync_positive)
		panel_fixed_mode->flags |= DRM_MODE_FLAG_PHSYNC;
	अन्यथा
		panel_fixed_mode->flags |= DRM_MODE_FLAG_NHSYNC;

	अगर (dvo_timing->vsync_positive)
		panel_fixed_mode->flags |= DRM_MODE_FLAG_PVSYNC;
	अन्यथा
		panel_fixed_mode->flags |= DRM_MODE_FLAG_NVSYNC;

	panel_fixed_mode->width_mm = (dvo_timing->himage_hi << 8) |
		dvo_timing->himage_lo;
	panel_fixed_mode->height_mm = (dvo_timing->vimage_hi << 8) |
		dvo_timing->vimage_lo;

	/* Some VBTs have bogus h/vtotal values */
	अगर (panel_fixed_mode->hsync_end > panel_fixed_mode->htotal)
		panel_fixed_mode->htotal = panel_fixed_mode->hsync_end + 1;
	अगर (panel_fixed_mode->vsync_end > panel_fixed_mode->vtotal)
		panel_fixed_mode->vtotal = panel_fixed_mode->vsync_end + 1;

	drm_mode_set_name(panel_fixed_mode);
पूर्ण

अटल स्थिर काष्ठा lvds_dvo_timing *
get_lvds_dvo_timing(स्थिर काष्ठा bdb_lvds_lfp_data *lvds_lfp_data,
		    स्थिर काष्ठा bdb_lvds_lfp_data_ptrs *lvds_lfp_data_ptrs,
		    पूर्णांक index)
अणु
	/*
	 * the size of fp_timing varies on the dअगरferent platक्रमm.
	 * So calculate the DVO timing relative offset in LVDS data
	 * entry to get the DVO timing entry
	 */

	पूर्णांक lfp_data_size =
		lvds_lfp_data_ptrs->ptr[1].dvo_timing_offset -
		lvds_lfp_data_ptrs->ptr[0].dvo_timing_offset;
	पूर्णांक dvo_timing_offset =
		lvds_lfp_data_ptrs->ptr[0].dvo_timing_offset -
		lvds_lfp_data_ptrs->ptr[0].fp_timing_offset;
	अक्षर *entry = (अक्षर *)lvds_lfp_data->data + lfp_data_size * index;

	वापस (काष्ठा lvds_dvo_timing *)(entry + dvo_timing_offset);
पूर्ण

/* get lvds_fp_timing entry
 * this function may वापस शून्य अगर the corresponding entry is invalid
 */
अटल स्थिर काष्ठा lvds_fp_timing *
get_lvds_fp_timing(स्थिर काष्ठा bdb_header *bdb,
		   स्थिर काष्ठा bdb_lvds_lfp_data *data,
		   स्थिर काष्ठा bdb_lvds_lfp_data_ptrs *ptrs,
		   पूर्णांक index)
अणु
	माप_प्रकार data_ofs = (स्थिर u8 *)data - (स्थिर u8 *)bdb;
	u16 data_size = ((स्थिर u16 *)data)[-1]; /* stored in header */
	माप_प्रकार ofs;

	अगर (index >= ARRAY_SIZE(ptrs->ptr))
		वापस शून्य;
	ofs = ptrs->ptr[index].fp_timing_offset;
	अगर (ofs < data_ofs ||
	    ofs + माप(काष्ठा lvds_fp_timing) > data_ofs + data_size)
		वापस शून्य;
	वापस (स्थिर काष्ठा lvds_fp_timing *)((स्थिर u8 *)bdb + ofs);
पूर्ण

/* Parse general panel options */
अटल व्योम
parse_panel_options(काष्ठा drm_i915_निजी *i915,
		    स्थिर काष्ठा bdb_header *bdb)
अणु
	स्थिर काष्ठा bdb_lvds_options *lvds_options;
	पूर्णांक panel_type;
	पूर्णांक drrs_mode;
	पूर्णांक ret;

	lvds_options = find_section(bdb, BDB_LVDS_OPTIONS);
	अगर (!lvds_options)
		वापस;

	i915->vbt.lvds_dither = lvds_options->pixel_dither;

	ret = पूर्णांकel_opregion_get_panel_type(i915);
	अगर (ret >= 0) अणु
		drm_WARN_ON(&i915->drm, ret > 0xf);
		panel_type = ret;
		drm_dbg_kms(&i915->drm, "Panel type: %d (OpRegion)\n",
			    panel_type);
	पूर्ण अन्यथा अणु
		अगर (lvds_options->panel_type > 0xf) अणु
			drm_dbg_kms(&i915->drm,
				    "Invalid VBT panel type 0x%x\n",
				    lvds_options->panel_type);
			वापस;
		पूर्ण
		panel_type = lvds_options->panel_type;
		drm_dbg_kms(&i915->drm, "Panel type: %d (VBT)\n",
			    panel_type);
	पूर्ण

	i915->vbt.panel_type = panel_type;

	drrs_mode = (lvds_options->dps_panel_type_bits
				>> (panel_type * 2)) & MODE_MASK;
	/*
	 * VBT has अटल DRRS = 0 and seamless DRRS = 2.
	 * The below piece of code is required to adjust vbt.drrs_type
	 * to match the क्रमागत drrs_support_type.
	 */
	चयन (drrs_mode) अणु
	हाल 0:
		i915->vbt.drrs_type = STATIC_DRRS_SUPPORT;
		drm_dbg_kms(&i915->drm, "DRRS supported mode is static\n");
		अवरोध;
	हाल 2:
		i915->vbt.drrs_type = SEAMLESS_DRRS_SUPPORT;
		drm_dbg_kms(&i915->drm,
			    "DRRS supported mode is seamless\n");
		अवरोध;
	शेष:
		i915->vbt.drrs_type = DRRS_NOT_SUPPORTED;
		drm_dbg_kms(&i915->drm,
			    "DRRS not supported (VBT input)\n");
		अवरोध;
	पूर्ण
पूर्ण

/* Try to find पूर्णांकegrated panel timing data */
अटल व्योम
parse_lfp_panel_dtd(काष्ठा drm_i915_निजी *i915,
		    स्थिर काष्ठा bdb_header *bdb)
अणु
	स्थिर काष्ठा bdb_lvds_lfp_data *lvds_lfp_data;
	स्थिर काष्ठा bdb_lvds_lfp_data_ptrs *lvds_lfp_data_ptrs;
	स्थिर काष्ठा lvds_dvo_timing *panel_dvo_timing;
	स्थिर काष्ठा lvds_fp_timing *fp_timing;
	काष्ठा drm_display_mode *panel_fixed_mode;
	पूर्णांक panel_type = i915->vbt.panel_type;

	lvds_lfp_data = find_section(bdb, BDB_LVDS_LFP_DATA);
	अगर (!lvds_lfp_data)
		वापस;

	lvds_lfp_data_ptrs = find_section(bdb, BDB_LVDS_LFP_DATA_PTRS);
	अगर (!lvds_lfp_data_ptrs)
		वापस;

	panel_dvo_timing = get_lvds_dvo_timing(lvds_lfp_data,
					       lvds_lfp_data_ptrs,
					       panel_type);

	panel_fixed_mode = kzalloc(माप(*panel_fixed_mode), GFP_KERNEL);
	अगर (!panel_fixed_mode)
		वापस;

	fill_detail_timing_data(panel_fixed_mode, panel_dvo_timing);

	i915->vbt.lfp_lvds_vbt_mode = panel_fixed_mode;

	drm_dbg_kms(&i915->drm,
		    "Found panel mode in BIOS VBT legacy lfp table:\n");
	drm_mode_debug_prपूर्णांकmodeline(panel_fixed_mode);

	fp_timing = get_lvds_fp_timing(bdb, lvds_lfp_data,
				       lvds_lfp_data_ptrs,
				       panel_type);
	अगर (fp_timing) अणु
		/* check the resolution, just to be sure */
		अगर (fp_timing->x_res == panel_fixed_mode->hdisplay &&
		    fp_timing->y_res == panel_fixed_mode->vdisplay) अणु
			i915->vbt.bios_lvds_val = fp_timing->lvds_reg_val;
			drm_dbg_kms(&i915->drm,
				    "VBT initial LVDS value %x\n",
				    i915->vbt.bios_lvds_val);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
parse_generic_dtd(काष्ठा drm_i915_निजी *i915,
		  स्थिर काष्ठा bdb_header *bdb)
अणु
	स्थिर काष्ठा bdb_generic_dtd *generic_dtd;
	स्थिर काष्ठा generic_dtd_entry *dtd;
	काष्ठा drm_display_mode *panel_fixed_mode;
	पूर्णांक num_dtd;

	generic_dtd = find_section(bdb, BDB_GENERIC_DTD);
	अगर (!generic_dtd)
		वापस;

	अगर (generic_dtd->gdtd_size < माप(काष्ठा generic_dtd_entry)) अणु
		drm_err(&i915->drm, "GDTD size %u is too small.\n",
			generic_dtd->gdtd_size);
		वापस;
	पूर्ण अन्यथा अगर (generic_dtd->gdtd_size !=
		   माप(काष्ठा generic_dtd_entry)) अणु
		drm_err(&i915->drm, "Unexpected GDTD size %u\n",
			generic_dtd->gdtd_size);
		/* DTD has unknown fields, but keep going */
	पूर्ण

	num_dtd = (get_blocksize(generic_dtd) -
		   माप(काष्ठा bdb_generic_dtd)) / generic_dtd->gdtd_size;
	अगर (i915->vbt.panel_type >= num_dtd) अणु
		drm_err(&i915->drm,
			"Panel type %d not found in table of %d DTD's\n",
			i915->vbt.panel_type, num_dtd);
		वापस;
	पूर्ण

	dtd = &generic_dtd->dtd[i915->vbt.panel_type];

	panel_fixed_mode = kzalloc(माप(*panel_fixed_mode), GFP_KERNEL);
	अगर (!panel_fixed_mode)
		वापस;

	panel_fixed_mode->hdisplay = dtd->hactive;
	panel_fixed_mode->hsync_start =
		panel_fixed_mode->hdisplay + dtd->hfront_porch;
	panel_fixed_mode->hsync_end =
		panel_fixed_mode->hsync_start + dtd->hsync;
	panel_fixed_mode->htotal =
		panel_fixed_mode->hdisplay + dtd->hblank;

	panel_fixed_mode->vdisplay = dtd->vactive;
	panel_fixed_mode->vsync_start =
		panel_fixed_mode->vdisplay + dtd->vfront_porch;
	panel_fixed_mode->vsync_end =
		panel_fixed_mode->vsync_start + dtd->vsync;
	panel_fixed_mode->vtotal =
		panel_fixed_mode->vdisplay + dtd->vblank;

	panel_fixed_mode->घड़ी = dtd->pixel_घड़ी;
	panel_fixed_mode->width_mm = dtd->width_mm;
	panel_fixed_mode->height_mm = dtd->height_mm;

	panel_fixed_mode->type = DRM_MODE_TYPE_PREFERRED;
	drm_mode_set_name(panel_fixed_mode);

	अगर (dtd->hsync_positive_polarity)
		panel_fixed_mode->flags |= DRM_MODE_FLAG_PHSYNC;
	अन्यथा
		panel_fixed_mode->flags |= DRM_MODE_FLAG_NHSYNC;

	अगर (dtd->vsync_positive_polarity)
		panel_fixed_mode->flags |= DRM_MODE_FLAG_PVSYNC;
	अन्यथा
		panel_fixed_mode->flags |= DRM_MODE_FLAG_NVSYNC;

	drm_dbg_kms(&i915->drm,
		    "Found panel mode in BIOS VBT generic dtd table:\n");
	drm_mode_debug_prपूर्णांकmodeline(panel_fixed_mode);

	i915->vbt.lfp_lvds_vbt_mode = panel_fixed_mode;
पूर्ण

अटल व्योम
parse_panel_dtd(काष्ठा drm_i915_निजी *i915,
		स्थिर काष्ठा bdb_header *bdb)
अणु
	/*
	 * Older VBTs provided provided DTD inक्रमmation क्रम पूर्णांकernal displays
	 * through the "LFP panel DTD" block (42).  As of VBT revision 229,
	 * that block is now deprecated and DTD inक्रमmation should be provided
	 * via a newer "generic DTD" block (58).  Just to be safe, we'll
	 * try the new generic DTD block first on VBT >= 229, but still fall
	 * back to trying the old LFP block अगर that fails.
	 */
	अगर (bdb->version >= 229)
		parse_generic_dtd(i915, bdb);
	अगर (!i915->vbt.lfp_lvds_vbt_mode)
		parse_lfp_panel_dtd(i915, bdb);
पूर्ण

अटल व्योम
parse_lfp_backlight(काष्ठा drm_i915_निजी *i915,
		    स्थिर काष्ठा bdb_header *bdb)
अणु
	स्थिर काष्ठा bdb_lfp_backlight_data *backlight_data;
	स्थिर काष्ठा lfp_backlight_data_entry *entry;
	पूर्णांक panel_type = i915->vbt.panel_type;
	u16 level;

	backlight_data = find_section(bdb, BDB_LVDS_BACKLIGHT);
	अगर (!backlight_data)
		वापस;

	अगर (backlight_data->entry_size != माप(backlight_data->data[0])) अणु
		drm_dbg_kms(&i915->drm,
			    "Unsupported backlight data entry size %u\n",
			    backlight_data->entry_size);
		वापस;
	पूर्ण

	entry = &backlight_data->data[panel_type];

	i915->vbt.backlight.present = entry->type == BDB_BACKLIGHT_TYPE_PWM;
	अगर (!i915->vbt.backlight.present) अणु
		drm_dbg_kms(&i915->drm,
			    "PWM backlight not present in VBT (type %u)\n",
			    entry->type);
		वापस;
	पूर्ण

	i915->vbt.backlight.type = INTEL_BACKLIGHT_DISPLAY_DDI;
	अगर (bdb->version >= 191 &&
	    get_blocksize(backlight_data) >= माप(*backlight_data)) अणु
		स्थिर काष्ठा lfp_backlight_control_method *method;

		method = &backlight_data->backlight_control[panel_type];
		i915->vbt.backlight.type = method->type;
		i915->vbt.backlight.controller = method->controller;
	पूर्ण

	i915->vbt.backlight.pwm_freq_hz = entry->pwm_freq_hz;
	i915->vbt.backlight.active_low_pwm = entry->active_low_pwm;

	अगर (bdb->version >= 234) अणु
		u16 min_level;
		bool scale;

		level = backlight_data->brightness_level[panel_type].level;
		min_level = backlight_data->brightness_min_level[panel_type].level;

		अगर (bdb->version >= 236)
			scale = backlight_data->brightness_precision_bits[panel_type] == 16;
		अन्यथा
			scale = level > 255;

		अगर (scale)
			min_level = min_level / 255;

		अगर (min_level > 255) अणु
			drm_warn(&i915->drm, "Brightness min level > 255\n");
			level = 255;
		पूर्ण
		i915->vbt.backlight.min_brightness = min_level;
	पूर्ण अन्यथा अणु
		level = backlight_data->level[panel_type];
		i915->vbt.backlight.min_brightness = entry->min_brightness;
	पूर्ण

	drm_dbg_kms(&i915->drm,
		    "VBT backlight PWM modulation frequency %u Hz, "
		    "active %s, min brightness %u, level %u, controller %u\n",
		    i915->vbt.backlight.pwm_freq_hz,
		    i915->vbt.backlight.active_low_pwm ? "low" : "high",
		    i915->vbt.backlight.min_brightness,
		    level,
		    i915->vbt.backlight.controller);
पूर्ण

/* Try to find sdvo panel data */
अटल व्योम
parse_sdvo_panel_data(काष्ठा drm_i915_निजी *i915,
		      स्थिर काष्ठा bdb_header *bdb)
अणु
	स्थिर काष्ठा bdb_sdvo_panel_dtds *dtds;
	काष्ठा drm_display_mode *panel_fixed_mode;
	पूर्णांक index;

	index = i915->params.vbt_sdvo_panel_type;
	अगर (index == -2) अणु
		drm_dbg_kms(&i915->drm,
			    "Ignore SDVO panel mode from BIOS VBT tables.\n");
		वापस;
	पूर्ण

	अगर (index == -1) अणु
		स्थिर काष्ठा bdb_sdvo_lvds_options *sdvo_lvds_options;

		sdvo_lvds_options = find_section(bdb, BDB_SDVO_LVDS_OPTIONS);
		अगर (!sdvo_lvds_options)
			वापस;

		index = sdvo_lvds_options->panel_type;
	पूर्ण

	dtds = find_section(bdb, BDB_SDVO_PANEL_DTDS);
	अगर (!dtds)
		वापस;

	panel_fixed_mode = kzalloc(माप(*panel_fixed_mode), GFP_KERNEL);
	अगर (!panel_fixed_mode)
		वापस;

	fill_detail_timing_data(panel_fixed_mode, &dtds->dtds[index]);

	i915->vbt.sdvo_lvds_vbt_mode = panel_fixed_mode;

	drm_dbg_kms(&i915->drm,
		    "Found SDVO panel mode in BIOS VBT tables:\n");
	drm_mode_debug_prपूर्णांकmodeline(panel_fixed_mode);
पूर्ण

अटल पूर्णांक पूर्णांकel_bios_ssc_frequency(काष्ठा drm_i915_निजी *i915,
				    bool alternate)
अणु
	चयन (DISPLAY_VER(i915)) अणु
	हाल 2:
		वापस alternate ? 66667 : 48000;
	हाल 3:
	हाल 4:
		वापस alternate ? 100000 : 96000;
	शेष:
		वापस alternate ? 100000 : 120000;
	पूर्ण
पूर्ण

अटल व्योम
parse_general_features(काष्ठा drm_i915_निजी *i915,
		       स्थिर काष्ठा bdb_header *bdb)
अणु
	स्थिर काष्ठा bdb_general_features *general;

	general = find_section(bdb, BDB_GENERAL_FEATURES);
	अगर (!general)
		वापस;

	i915->vbt.पूर्णांक_tv_support = general->पूर्णांक_tv_support;
	/* पूर्णांक_crt_support can't be trusted on earlier platक्रमms */
	अगर (bdb->version >= 155 &&
	    (HAS_DDI(i915) || IS_VALLEYVIEW(i915)))
		i915->vbt.पूर्णांक_crt_support = general->पूर्णांक_crt_support;
	i915->vbt.lvds_use_ssc = general->enable_ssc;
	i915->vbt.lvds_ssc_freq =
		पूर्णांकel_bios_ssc_frequency(i915, general->ssc_freq);
	i915->vbt.display_घड़ी_mode = general->display_घड़ी_mode;
	i915->vbt.fdi_rx_polarity_inverted = general->fdi_rx_polarity_inverted;
	अगर (bdb->version >= 181) अणु
		i915->vbt.orientation = general->rotate_180 ?
			DRM_MODE_PANEL_ORIENTATION_BOTTOM_UP :
			DRM_MODE_PANEL_ORIENTATION_NORMAL;
	पूर्ण अन्यथा अणु
		i915->vbt.orientation = DRM_MODE_PANEL_ORIENTATION_UNKNOWN;
	पूर्ण
	drm_dbg_kms(&i915->drm,
		    "BDB_GENERAL_FEATURES int_tv_support %d int_crt_support %d lvds_use_ssc %d lvds_ssc_freq %d display_clock_mode %d fdi_rx_polarity_inverted %d\n",
		    i915->vbt.पूर्णांक_tv_support,
		    i915->vbt.पूर्णांक_crt_support,
		    i915->vbt.lvds_use_ssc,
		    i915->vbt.lvds_ssc_freq,
		    i915->vbt.display_घड़ी_mode,
		    i915->vbt.fdi_rx_polarity_inverted);
पूर्ण

अटल स्थिर काष्ठा child_device_config *
child_device_ptr(स्थिर काष्ठा bdb_general_definitions *defs, पूर्णांक i)
अणु
	वापस (स्थिर व्योम *) &defs->devices[i * defs->child_dev_size];
पूर्ण

अटल व्योम
parse_sdvo_device_mapping(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा sdvo_device_mapping *mapping;
	स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata;
	स्थिर काष्ठा child_device_config *child;
	पूर्णांक count = 0;

	/*
	 * Only parse SDVO mappings on gens that could have SDVO. This isn't
	 * accurate and करोesn't have to be, as long as it's not too strict.
	 */
	अगर (!IS_DISPLAY_RANGE(i915, 3, 7)) अणु
		drm_dbg_kms(&i915->drm, "Skipping SDVO device mapping\n");
		वापस;
	पूर्ण

	list_क्रम_each_entry(devdata, &i915->vbt.display_devices, node) अणु
		child = &devdata->child;

		अगर (child->slave_addr != SLAVE_ADDR1 &&
		    child->slave_addr != SLAVE_ADDR2) अणु
			/*
			 * If the slave address is neither 0x70 nor 0x72,
			 * it is not a SDVO device. Skip it.
			 */
			जारी;
		पूर्ण
		अगर (child->dvo_port != DEVICE_PORT_DVOB &&
		    child->dvo_port != DEVICE_PORT_DVOC) अणु
			/* skip the incorrect SDVO port */
			drm_dbg_kms(&i915->drm,
				    "Incorrect SDVO port. Skip it\n");
			जारी;
		पूर्ण
		drm_dbg_kms(&i915->drm,
			    "the SDVO device with slave addr %2x is found on"
			    " %s port\n",
			    child->slave_addr,
			    (child->dvo_port == DEVICE_PORT_DVOB) ?
			    "SDVOB" : "SDVOC");
		mapping = &i915->vbt.sdvo_mappings[child->dvo_port - 1];
		अगर (!mapping->initialized) अणु
			mapping->dvo_port = child->dvo_port;
			mapping->slave_addr = child->slave_addr;
			mapping->dvo_wiring = child->dvo_wiring;
			mapping->ddc_pin = child->ddc_pin;
			mapping->i2c_pin = child->i2c_pin;
			mapping->initialized = 1;
			drm_dbg_kms(&i915->drm,
				    "SDVO device: dvo=%x, addr=%x, wiring=%d, ddc_pin=%d, i2c_pin=%d\n",
				    mapping->dvo_port, mapping->slave_addr,
				    mapping->dvo_wiring, mapping->ddc_pin,
				    mapping->i2c_pin);
		पूर्ण अन्यथा अणु
			drm_dbg_kms(&i915->drm,
				    "Maybe one SDVO port is shared by "
				    "two SDVO device.\n");
		पूर्ण
		अगर (child->slave2_addr) अणु
			/* Maybe this is a SDVO device with multiple inमाला_दो */
			/* And the mapping info is not added */
			drm_dbg_kms(&i915->drm,
				    "there exists the slave2_addr. Maybe this"
				    " is a SDVO device with multiple inputs.\n");
		पूर्ण
		count++;
	पूर्ण

	अगर (!count) अणु
		/* No SDVO device info is found */
		drm_dbg_kms(&i915->drm,
			    "No SDVO device info is found in VBT\n");
	पूर्ण
पूर्ण

अटल व्योम
parse_driver_features(काष्ठा drm_i915_निजी *i915,
		      स्थिर काष्ठा bdb_header *bdb)
अणु
	स्थिर काष्ठा bdb_driver_features *driver;

	driver = find_section(bdb, BDB_DRIVER_FEATURES);
	अगर (!driver)
		वापस;

	अगर (DISPLAY_VER(i915) >= 5) अणु
		/*
		 * Note that we consider BDB_DRIVER_FEATURE_INT_SDVO_LVDS
		 * to mean "eDP". The VBT spec करोesn't agree with that
		 * पूर्णांकerpretation, but real world VBTs seem to.
		 */
		अगर (driver->lvds_config != BDB_DRIVER_FEATURE_INT_LVDS)
			i915->vbt.पूर्णांक_lvds_support = 0;
	पूर्ण अन्यथा अणु
		/*
		 * FIXME it's not clear which BDB version has the LVDS config
		 * bits defined. Revision history in the VBT spec says:
		 * "0.92 | Add two definitions क्रम VBT value of LVDS Active
		 *  Config (00b and 11b values defined) | 06/13/2005"
		 * but करोes not the specअगरy the BDB version.
		 *
		 * So far version 134 (on i945gm) is the oldest VBT observed
		 * in the wild with the bits correctly populated. Version
		 * 108 (on i85x) करोes not have the bits correctly populated.
		 */
		अगर (bdb->version >= 134 &&
		    driver->lvds_config != BDB_DRIVER_FEATURE_INT_LVDS &&
		    driver->lvds_config != BDB_DRIVER_FEATURE_INT_SDVO_LVDS)
			i915->vbt.पूर्णांक_lvds_support = 0;
	पूर्ण

	अगर (bdb->version < 228) अणु
		drm_dbg_kms(&i915->drm, "DRRS State Enabled:%d\n",
			    driver->drrs_enabled);
		/*
		 * If DRRS is not supported, drrs_type has to be set to 0.
		 * This is because, VBT is configured in such a way that
		 * अटल DRRS is 0 and DRRS not supported is represented by
		 * driver->drrs_enabled=false
		 */
		अगर (!driver->drrs_enabled)
			i915->vbt.drrs_type = DRRS_NOT_SUPPORTED;

		i915->vbt.psr.enable = driver->psr_enabled;
	पूर्ण
पूर्ण

अटल व्योम
parse_घातer_conservation_features(काष्ठा drm_i915_निजी *i915,
				  स्थिर काष्ठा bdb_header *bdb)
अणु
	स्थिर काष्ठा bdb_lfp_घातer *घातer;
	u8 panel_type = i915->vbt.panel_type;

	अगर (bdb->version < 228)
		वापस;

	घातer = find_section(bdb, BDB_LFP_POWER);
	अगर (!घातer)
		वापस;

	i915->vbt.psr.enable = घातer->psr & BIT(panel_type);

	/*
	 * If DRRS is not supported, drrs_type has to be set to 0.
	 * This is because, VBT is configured in such a way that
	 * अटल DRRS is 0 and DRRS not supported is represented by
	 * घातer->drrs & BIT(panel_type)=false
	 */
	अगर (!(घातer->drrs & BIT(panel_type)))
		i915->vbt.drrs_type = DRRS_NOT_SUPPORTED;

	अगर (bdb->version >= 232)
		i915->vbt.edp.hobl = घातer->hobl & BIT(panel_type);
पूर्ण

अटल व्योम
parse_edp(काष्ठा drm_i915_निजी *i915, स्थिर काष्ठा bdb_header *bdb)
अणु
	स्थिर काष्ठा bdb_edp *edp;
	स्थिर काष्ठा edp_घातer_seq *edp_pps;
	स्थिर काष्ठा edp_fast_link_params *edp_link_params;
	पूर्णांक panel_type = i915->vbt.panel_type;

	edp = find_section(bdb, BDB_EDP);
	अगर (!edp)
		वापस;

	चयन ((edp->color_depth >> (panel_type * 2)) & 3) अणु
	हाल EDP_18BPP:
		i915->vbt.edp.bpp = 18;
		अवरोध;
	हाल EDP_24BPP:
		i915->vbt.edp.bpp = 24;
		अवरोध;
	हाल EDP_30BPP:
		i915->vbt.edp.bpp = 30;
		अवरोध;
	पूर्ण

	/* Get the eDP sequencing and link info */
	edp_pps = &edp->घातer_seqs[panel_type];
	edp_link_params = &edp->fast_link_params[panel_type];

	i915->vbt.edp.pps = *edp_pps;

	चयन (edp_link_params->rate) अणु
	हाल EDP_RATE_1_62:
		i915->vbt.edp.rate = DP_LINK_BW_1_62;
		अवरोध;
	हाल EDP_RATE_2_7:
		i915->vbt.edp.rate = DP_LINK_BW_2_7;
		अवरोध;
	शेष:
		drm_dbg_kms(&i915->drm,
			    "VBT has unknown eDP link rate value %u\n",
			     edp_link_params->rate);
		अवरोध;
	पूर्ण

	चयन (edp_link_params->lanes) अणु
	हाल EDP_LANE_1:
		i915->vbt.edp.lanes = 1;
		अवरोध;
	हाल EDP_LANE_2:
		i915->vbt.edp.lanes = 2;
		अवरोध;
	हाल EDP_LANE_4:
		i915->vbt.edp.lanes = 4;
		अवरोध;
	शेष:
		drm_dbg_kms(&i915->drm,
			    "VBT has unknown eDP lane count value %u\n",
			    edp_link_params->lanes);
		अवरोध;
	पूर्ण

	चयन (edp_link_params->preemphasis) अणु
	हाल EDP_PREEMPHASIS_NONE:
		i915->vbt.edp.preemphasis = DP_TRAIN_PRE_EMPH_LEVEL_0;
		अवरोध;
	हाल EDP_PREEMPHASIS_3_5dB:
		i915->vbt.edp.preemphasis = DP_TRAIN_PRE_EMPH_LEVEL_1;
		अवरोध;
	हाल EDP_PREEMPHASIS_6dB:
		i915->vbt.edp.preemphasis = DP_TRAIN_PRE_EMPH_LEVEL_2;
		अवरोध;
	हाल EDP_PREEMPHASIS_9_5dB:
		i915->vbt.edp.preemphasis = DP_TRAIN_PRE_EMPH_LEVEL_3;
		अवरोध;
	शेष:
		drm_dbg_kms(&i915->drm,
			    "VBT has unknown eDP pre-emphasis value %u\n",
			    edp_link_params->preemphasis);
		अवरोध;
	पूर्ण

	चयन (edp_link_params->vswing) अणु
	हाल EDP_VSWING_0_4V:
		i915->vbt.edp.vswing = DP_TRAIN_VOLTAGE_SWING_LEVEL_0;
		अवरोध;
	हाल EDP_VSWING_0_6V:
		i915->vbt.edp.vswing = DP_TRAIN_VOLTAGE_SWING_LEVEL_1;
		अवरोध;
	हाल EDP_VSWING_0_8V:
		i915->vbt.edp.vswing = DP_TRAIN_VOLTAGE_SWING_LEVEL_2;
		अवरोध;
	हाल EDP_VSWING_1_2V:
		i915->vbt.edp.vswing = DP_TRAIN_VOLTAGE_SWING_LEVEL_3;
		अवरोध;
	शेष:
		drm_dbg_kms(&i915->drm,
			    "VBT has unknown eDP voltage swing value %u\n",
			    edp_link_params->vswing);
		अवरोध;
	पूर्ण

	अगर (bdb->version >= 173) अणु
		u8 vswing;

		/* Don't पढ़ो from VBT अगर module parameter has valid value*/
		अगर (i915->params.edp_vswing) अणु
			i915->vbt.edp.low_vswing =
				i915->params.edp_vswing == 1;
		पूर्ण अन्यथा अणु
			vswing = (edp->edp_vswing_preemph >> (panel_type * 4)) & 0xF;
			i915->vbt.edp.low_vswing = vswing == 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
parse_psr(काष्ठा drm_i915_निजी *i915, स्थिर काष्ठा bdb_header *bdb)
अणु
	स्थिर काष्ठा bdb_psr *psr;
	स्थिर काष्ठा psr_table *psr_table;
	पूर्णांक panel_type = i915->vbt.panel_type;

	psr = find_section(bdb, BDB_PSR);
	अगर (!psr) अणु
		drm_dbg_kms(&i915->drm, "No PSR BDB found.\n");
		वापस;
	पूर्ण

	psr_table = &psr->psr_table[panel_type];

	i915->vbt.psr.full_link = psr_table->full_link;
	i915->vbt.psr.require_aux_wakeup = psr_table->require_aux_to_wakeup;

	/* Allowed VBT values goes from 0 to 15 */
	i915->vbt.psr.idle_frames = psr_table->idle_frames < 0 ? 0 :
		psr_table->idle_frames > 15 ? 15 : psr_table->idle_frames;

	चयन (psr_table->lines_to_रुको) अणु
	हाल 0:
		i915->vbt.psr.lines_to_रुको = PSR_0_LINES_TO_WAIT;
		अवरोध;
	हाल 1:
		i915->vbt.psr.lines_to_रुको = PSR_1_LINE_TO_WAIT;
		अवरोध;
	हाल 2:
		i915->vbt.psr.lines_to_रुको = PSR_4_LINES_TO_WAIT;
		अवरोध;
	हाल 3:
		i915->vbt.psr.lines_to_रुको = PSR_8_LINES_TO_WAIT;
		अवरोध;
	शेष:
		drm_dbg_kms(&i915->drm,
			    "VBT has unknown PSR lines to wait %u\n",
			    psr_table->lines_to_रुको);
		अवरोध;
	पूर्ण

	/*
	 * New psr options 0=500us, 1=100us, 2=2500us, 3=0us
	 * Old decimal value is wake up समय in multiples of 100 us.
	 */
	अगर (bdb->version >= 205 &&
	    (IS_GEN9_BC(i915) || DISPLAY_VER(i915) >= 10)) अणु
		चयन (psr_table->tp1_wakeup_समय) अणु
		हाल 0:
			i915->vbt.psr.tp1_wakeup_समय_us = 500;
			अवरोध;
		हाल 1:
			i915->vbt.psr.tp1_wakeup_समय_us = 100;
			अवरोध;
		हाल 3:
			i915->vbt.psr.tp1_wakeup_समय_us = 0;
			अवरोध;
		शेष:
			drm_dbg_kms(&i915->drm,
				    "VBT tp1 wakeup time value %d is outside range[0-3], defaulting to max value 2500us\n",
				    psr_table->tp1_wakeup_समय);
			fallthrough;
		हाल 2:
			i915->vbt.psr.tp1_wakeup_समय_us = 2500;
			अवरोध;
		पूर्ण

		चयन (psr_table->tp2_tp3_wakeup_समय) अणु
		हाल 0:
			i915->vbt.psr.tp2_tp3_wakeup_समय_us = 500;
			अवरोध;
		हाल 1:
			i915->vbt.psr.tp2_tp3_wakeup_समय_us = 100;
			अवरोध;
		हाल 3:
			i915->vbt.psr.tp2_tp3_wakeup_समय_us = 0;
			अवरोध;
		शेष:
			drm_dbg_kms(&i915->drm,
				    "VBT tp2_tp3 wakeup time value %d is outside range[0-3], defaulting to max value 2500us\n",
				    psr_table->tp2_tp3_wakeup_समय);
			fallthrough;
		हाल 2:
			i915->vbt.psr.tp2_tp3_wakeup_समय_us = 2500;
		अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		i915->vbt.psr.tp1_wakeup_समय_us = psr_table->tp1_wakeup_समय * 100;
		i915->vbt.psr.tp2_tp3_wakeup_समय_us = psr_table->tp2_tp3_wakeup_समय * 100;
	पूर्ण

	अगर (bdb->version >= 226) अणु
		u32 wakeup_समय = psr->psr2_tp2_tp3_wakeup_समय;

		wakeup_समय = (wakeup_समय >> (2 * panel_type)) & 0x3;
		चयन (wakeup_समय) अणु
		हाल 0:
			wakeup_समय = 500;
			अवरोध;
		हाल 1:
			wakeup_समय = 100;
			अवरोध;
		हाल 3:
			wakeup_समय = 50;
			अवरोध;
		शेष:
		हाल 2:
			wakeup_समय = 2500;
			अवरोध;
		पूर्ण
		i915->vbt.psr.psr2_tp2_tp3_wakeup_समय_us = wakeup_समय;
	पूर्ण अन्यथा अणु
		/* Reusing PSR1 wakeup समय क्रम PSR2 in older VBTs */
		i915->vbt.psr.psr2_tp2_tp3_wakeup_समय_us = i915->vbt.psr.tp2_tp3_wakeup_समय_us;
	पूर्ण
पूर्ण

अटल व्योम parse_dsi_backlight_ports(काष्ठा drm_i915_निजी *i915,
				      u16 version, क्रमागत port port)
अणु
	अगर (!i915->vbt.dsi.config->dual_link || version < 197) अणु
		i915->vbt.dsi.bl_ports = BIT(port);
		अगर (i915->vbt.dsi.config->cabc_supported)
			i915->vbt.dsi.cabc_ports = BIT(port);

		वापस;
	पूर्ण

	चयन (i915->vbt.dsi.config->dl_dcs_backlight_ports) अणु
	हाल DL_DCS_PORT_A:
		i915->vbt.dsi.bl_ports = BIT(PORT_A);
		अवरोध;
	हाल DL_DCS_PORT_C:
		i915->vbt.dsi.bl_ports = BIT(PORT_C);
		अवरोध;
	शेष:
	हाल DL_DCS_PORT_A_AND_C:
		i915->vbt.dsi.bl_ports = BIT(PORT_A) | BIT(PORT_C);
		अवरोध;
	पूर्ण

	अगर (!i915->vbt.dsi.config->cabc_supported)
		वापस;

	चयन (i915->vbt.dsi.config->dl_dcs_cabc_ports) अणु
	हाल DL_DCS_PORT_A:
		i915->vbt.dsi.cabc_ports = BIT(PORT_A);
		अवरोध;
	हाल DL_DCS_PORT_C:
		i915->vbt.dsi.cabc_ports = BIT(PORT_C);
		अवरोध;
	शेष:
	हाल DL_DCS_PORT_A_AND_C:
		i915->vbt.dsi.cabc_ports =
					BIT(PORT_A) | BIT(PORT_C);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
parse_mipi_config(काष्ठा drm_i915_निजी *i915,
		  स्थिर काष्ठा bdb_header *bdb)
अणु
	स्थिर काष्ठा bdb_mipi_config *start;
	स्थिर काष्ठा mipi_config *config;
	स्थिर काष्ठा mipi_pps_data *pps;
	पूर्णांक panel_type = i915->vbt.panel_type;
	क्रमागत port port;

	/* parse MIPI blocks only अगर LFP type is MIPI */
	अगर (!पूर्णांकel_bios_is_dsi_present(i915, &port))
		वापस;

	/* Initialize this to undefined indicating no generic MIPI support */
	i915->vbt.dsi.panel_id = MIPI_DSI_UNDEFINED_PANEL_ID;

	/* Block #40 is alपढ़ोy parsed and panel_fixed_mode is
	 * stored in i915->lfp_lvds_vbt_mode
	 * resuse this when needed
	 */

	/* Parse #52 क्रम panel index used from panel_type alपढ़ोy
	 * parsed
	 */
	start = find_section(bdb, BDB_MIPI_CONFIG);
	अगर (!start) अणु
		drm_dbg_kms(&i915->drm, "No MIPI config BDB found");
		वापस;
	पूर्ण

	drm_dbg(&i915->drm, "Found MIPI Config block, panel index = %d\n",
		panel_type);

	/*
	 * get hold of the correct configuration block and pps data as per
	 * the panel_type as index
	 */
	config = &start->config[panel_type];
	pps = &start->pps[panel_type];

	/* store as of now full data. Trim when we realise all is not needed */
	i915->vbt.dsi.config = kmemdup(config, माप(काष्ठा mipi_config), GFP_KERNEL);
	अगर (!i915->vbt.dsi.config)
		वापस;

	i915->vbt.dsi.pps = kmemdup(pps, माप(काष्ठा mipi_pps_data), GFP_KERNEL);
	अगर (!i915->vbt.dsi.pps) अणु
		kमुक्त(i915->vbt.dsi.config);
		वापस;
	पूर्ण

	parse_dsi_backlight_ports(i915, bdb->version, port);

	/* FIXME is the 90 vs. 270 correct? */
	चयन (config->rotation) अणु
	हाल ENABLE_ROTATION_0:
		/*
		 * Most (all?) VBTs claim 0 degrees despite having
		 * an upside करोwn panel, thus we करो not trust this.
		 */
		i915->vbt.dsi.orientation =
			DRM_MODE_PANEL_ORIENTATION_UNKNOWN;
		अवरोध;
	हाल ENABLE_ROTATION_90:
		i915->vbt.dsi.orientation =
			DRM_MODE_PANEL_ORIENTATION_RIGHT_UP;
		अवरोध;
	हाल ENABLE_ROTATION_180:
		i915->vbt.dsi.orientation =
			DRM_MODE_PANEL_ORIENTATION_BOTTOM_UP;
		अवरोध;
	हाल ENABLE_ROTATION_270:
		i915->vbt.dsi.orientation =
			DRM_MODE_PANEL_ORIENTATION_LEFT_UP;
		अवरोध;
	पूर्ण

	/* We have mandatory mipi config blocks. Initialize as generic panel */
	i915->vbt.dsi.panel_id = MIPI_DSI_GENERIC_PANEL_ID;
पूर्ण

/* Find the sequence block and size क्रम the given panel. */
अटल स्थिर u8 *
find_panel_sequence_block(स्थिर काष्ठा bdb_mipi_sequence *sequence,
			  u16 panel_id, u32 *seq_size)
अणु
	u32 total = get_blocksize(sequence);
	स्थिर u8 *data = &sequence->data[0];
	u8 current_id;
	u32 current_size;
	पूर्णांक header_size = sequence->version >= 3 ? 5 : 3;
	पूर्णांक index = 0;
	पूर्णांक i;

	/* skip new block size */
	अगर (sequence->version >= 3)
		data += 4;

	क्रम (i = 0; i < MAX_MIPI_CONFIGURATIONS && index < total; i++) अणु
		अगर (index + header_size > total) अणु
			DRM_ERROR("Invalid sequence block (header)\n");
			वापस शून्य;
		पूर्ण

		current_id = *(data + index);
		अगर (sequence->version >= 3)
			current_size = *((स्थिर u32 *)(data + index + 1));
		अन्यथा
			current_size = *((स्थिर u16 *)(data + index + 1));

		index += header_size;

		अगर (index + current_size > total) अणु
			DRM_ERROR("Invalid sequence block\n");
			वापस शून्य;
		पूर्ण

		अगर (current_id == panel_id) अणु
			*seq_size = current_size;
			वापस data + index;
		पूर्ण

		index += current_size;
	पूर्ण

	DRM_ERROR("Sequence block detected but no valid configuration\n");

	वापस शून्य;
पूर्ण

अटल पूर्णांक जाओ_next_sequence(स्थिर u8 *data, पूर्णांक index, पूर्णांक total)
अणु
	u16 len;

	/* Skip Sequence Byte. */
	क्रम (index = index + 1; index < total; index += len) अणु
		u8 operation_byte = *(data + index);
		index++;

		चयन (operation_byte) अणु
		हाल MIPI_SEQ_ELEM_END:
			वापस index;
		हाल MIPI_SEQ_ELEM_SEND_PKT:
			अगर (index + 4 > total)
				वापस 0;

			len = *((स्थिर u16 *)(data + index + 2)) + 4;
			अवरोध;
		हाल MIPI_SEQ_ELEM_DELAY:
			len = 4;
			अवरोध;
		हाल MIPI_SEQ_ELEM_GPIO:
			len = 2;
			अवरोध;
		हाल MIPI_SEQ_ELEM_I2C:
			अगर (index + 7 > total)
				वापस 0;
			len = *(data + index + 6) + 7;
			अवरोध;
		शेष:
			DRM_ERROR("Unknown operation byte\n");
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक जाओ_next_sequence_v3(स्थिर u8 *data, पूर्णांक index, पूर्णांक total)
अणु
	पूर्णांक seq_end;
	u16 len;
	u32 size_of_sequence;

	/*
	 * Could skip sequence based on Size of Sequence alone, but also करो some
	 * checking on the काष्ठाure.
	 */
	अगर (total < 5) अणु
		DRM_ERROR("Too small sequence size\n");
		वापस 0;
	पूर्ण

	/* Skip Sequence Byte. */
	index++;

	/*
	 * Size of Sequence. Excludes the Sequence Byte and the size itself,
	 * includes MIPI_SEQ_ELEM_END byte, excludes the final MIPI_SEQ_END
	 * byte.
	 */
	size_of_sequence = *((स्थिर u32 *)(data + index));
	index += 4;

	seq_end = index + size_of_sequence;
	अगर (seq_end > total) अणु
		DRM_ERROR("Invalid sequence size\n");
		वापस 0;
	पूर्ण

	क्रम (; index < total; index += len) अणु
		u8 operation_byte = *(data + index);
		index++;

		अगर (operation_byte == MIPI_SEQ_ELEM_END) अणु
			अगर (index != seq_end) अणु
				DRM_ERROR("Invalid element structure\n");
				वापस 0;
			पूर्ण
			वापस index;
		पूर्ण

		len = *(data + index);
		index++;

		/*
		 * FIXME: Would be nice to check elements like क्रम v1/v2 in
		 * जाओ_next_sequence() above.
		 */
		चयन (operation_byte) अणु
		हाल MIPI_SEQ_ELEM_SEND_PKT:
		हाल MIPI_SEQ_ELEM_DELAY:
		हाल MIPI_SEQ_ELEM_GPIO:
		हाल MIPI_SEQ_ELEM_I2C:
		हाल MIPI_SEQ_ELEM_SPI:
		हाल MIPI_SEQ_ELEM_PMIC:
			अवरोध;
		शेष:
			DRM_ERROR("Unknown operation byte %u\n",
				  operation_byte);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Get len of pre-fixed deनिश्चित fragment from a v1 init OTP sequence,
 * skip all delay + gpio opeअक्रमs and stop at the first DSI packet op.
 */
अटल पूर्णांक get_init_otp_deनिश्चित_fragment_len(काष्ठा drm_i915_निजी *i915)
अणु
	स्थिर u8 *data = i915->vbt.dsi.sequence[MIPI_SEQ_INIT_OTP];
	पूर्णांक index, len;

	अगर (drm_WARN_ON(&i915->drm,
			!data || i915->vbt.dsi.seq_version != 1))
		वापस 0;

	/* index = 1 to skip sequence byte */
	क्रम (index = 1; data[index] != MIPI_SEQ_ELEM_END; index += len) अणु
		चयन (data[index]) अणु
		हाल MIPI_SEQ_ELEM_SEND_PKT:
			वापस index == 1 ? 0 : index;
		हाल MIPI_SEQ_ELEM_DELAY:
			len = 5; /* 1 byte क्रम opeअक्रम + uपूर्णांक32 */
			अवरोध;
		हाल MIPI_SEQ_ELEM_GPIO:
			len = 3; /* 1 byte क्रम op, 1 क्रम gpio_nr, 1 क्रम value */
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Some v1 VBT MIPI sequences करो the deनिश्चित in the init OTP sequence.
 * The deनिश्चित must be करोne beक्रमe calling पूर्णांकel_dsi_device_पढ़ोy, so क्रम
 * these devices we split the init OTP sequence पूर्णांकo a deनिश्चित sequence and
 * the actual init OTP part.
 */
अटल व्योम fixup_mipi_sequences(काष्ठा drm_i915_निजी *i915)
अणु
	u8 *init_otp;
	पूर्णांक len;

	/* Limit this to VLV क्रम now. */
	अगर (!IS_VALLEYVIEW(i915))
		वापस;

	/* Limit this to v1 vid-mode sequences */
	अगर (i915->vbt.dsi.config->is_cmd_mode ||
	    i915->vbt.dsi.seq_version != 1)
		वापस;

	/* Only करो this अगर there are otp and निश्चित seqs and no deनिश्चित seq */
	अगर (!i915->vbt.dsi.sequence[MIPI_SEQ_INIT_OTP] ||
	    !i915->vbt.dsi.sequence[MIPI_SEQ_ASSERT_RESET] ||
	    i915->vbt.dsi.sequence[MIPI_SEQ_DEASSERT_RESET])
		वापस;

	/* The deनिश्चित-sequence ends at the first DSI packet */
	len = get_init_otp_deनिश्चित_fragment_len(i915);
	अगर (!len)
		वापस;

	drm_dbg_kms(&i915->drm,
		    "Using init OTP fragment to deassert reset\n");

	/* Copy the fragment, update seq byte and terminate it */
	init_otp = (u8 *)i915->vbt.dsi.sequence[MIPI_SEQ_INIT_OTP];
	i915->vbt.dsi.deनिश्चित_seq = kmemdup(init_otp, len + 1, GFP_KERNEL);
	अगर (!i915->vbt.dsi.deनिश्चित_seq)
		वापस;
	i915->vbt.dsi.deनिश्चित_seq[0] = MIPI_SEQ_DEASSERT_RESET;
	i915->vbt.dsi.deनिश्चित_seq[len] = MIPI_SEQ_ELEM_END;
	/* Use the copy क्रम deनिश्चित */
	i915->vbt.dsi.sequence[MIPI_SEQ_DEASSERT_RESET] =
		i915->vbt.dsi.deनिश्चित_seq;
	/* Replace the last byte of the fragment with init OTP seq byte */
	init_otp[len - 1] = MIPI_SEQ_INIT_OTP;
	/* And make MIPI_MIPI_SEQ_INIT_OTP poपूर्णांक to it */
	i915->vbt.dsi.sequence[MIPI_SEQ_INIT_OTP] = init_otp + len - 1;
पूर्ण

अटल व्योम
parse_mipi_sequence(काष्ठा drm_i915_निजी *i915,
		    स्थिर काष्ठा bdb_header *bdb)
अणु
	पूर्णांक panel_type = i915->vbt.panel_type;
	स्थिर काष्ठा bdb_mipi_sequence *sequence;
	स्थिर u8 *seq_data;
	u32 seq_size;
	u8 *data;
	पूर्णांक index = 0;

	/* Only our generic panel driver uses the sequence block. */
	अगर (i915->vbt.dsi.panel_id != MIPI_DSI_GENERIC_PANEL_ID)
		वापस;

	sequence = find_section(bdb, BDB_MIPI_SEQUENCE);
	अगर (!sequence) अणु
		drm_dbg_kms(&i915->drm,
			    "No MIPI Sequence found, parsing complete\n");
		वापस;
	पूर्ण

	/* Fail gracefully क्रम क्रमward incompatible sequence block. */
	अगर (sequence->version >= 4) अणु
		drm_err(&i915->drm,
			"Unable to parse MIPI Sequence Block v%u\n",
			sequence->version);
		वापस;
	पूर्ण

	drm_dbg(&i915->drm, "Found MIPI sequence block v%u\n",
		sequence->version);

	seq_data = find_panel_sequence_block(sequence, panel_type, &seq_size);
	अगर (!seq_data)
		वापस;

	data = kmemdup(seq_data, seq_size, GFP_KERNEL);
	अगर (!data)
		वापस;

	/* Parse the sequences, store poपूर्णांकers to each sequence. */
	क्रम (;;) अणु
		u8 seq_id = *(data + index);
		अगर (seq_id == MIPI_SEQ_END)
			अवरोध;

		अगर (seq_id >= MIPI_SEQ_MAX) अणु
			drm_err(&i915->drm, "Unknown sequence %u\n",
				seq_id);
			जाओ err;
		पूर्ण

		/* Log about presence of sequences we won't run. */
		अगर (seq_id == MIPI_SEQ_TEAR_ON || seq_id == MIPI_SEQ_TEAR_OFF)
			drm_dbg_kms(&i915->drm,
				    "Unsupported sequence %u\n", seq_id);

		i915->vbt.dsi.sequence[seq_id] = data + index;

		अगर (sequence->version >= 3)
			index = जाओ_next_sequence_v3(data, index, seq_size);
		अन्यथा
			index = जाओ_next_sequence(data, index, seq_size);
		अगर (!index) अणु
			drm_err(&i915->drm, "Invalid sequence %u\n",
				seq_id);
			जाओ err;
		पूर्ण
	पूर्ण

	i915->vbt.dsi.data = data;
	i915->vbt.dsi.size = seq_size;
	i915->vbt.dsi.seq_version = sequence->version;

	fixup_mipi_sequences(i915);

	drm_dbg(&i915->drm, "MIPI related VBT parsing complete\n");
	वापस;

err:
	kमुक्त(data);
	स_रखो(i915->vbt.dsi.sequence, 0, माप(i915->vbt.dsi.sequence));
पूर्ण

अटल व्योम
parse_compression_parameters(काष्ठा drm_i915_निजी *i915,
			     स्थिर काष्ठा bdb_header *bdb)
अणु
	स्थिर काष्ठा bdb_compression_parameters *params;
	काष्ठा पूर्णांकel_bios_encoder_data *devdata;
	स्थिर काष्ठा child_device_config *child;
	u16 block_size;
	पूर्णांक index;

	अगर (bdb->version < 198)
		वापस;

	params = find_section(bdb, BDB_COMPRESSION_PARAMETERS);
	अगर (params) अणु
		/* Sanity checks */
		अगर (params->entry_size != माप(params->data[0])) अणु
			drm_dbg_kms(&i915->drm,
				    "VBT: unsupported compression param entry size\n");
			वापस;
		पूर्ण

		block_size = get_blocksize(params);
		अगर (block_size < माप(*params)) अणु
			drm_dbg_kms(&i915->drm,
				    "VBT: expected 16 compression param entries\n");
			वापस;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(devdata, &i915->vbt.display_devices, node) अणु
		child = &devdata->child;

		अगर (!child->compression_enable)
			जारी;

		अगर (!params) अणु
			drm_dbg_kms(&i915->drm,
				    "VBT: compression params not available\n");
			जारी;
		पूर्ण

		अगर (child->compression_method_cps) अणु
			drm_dbg_kms(&i915->drm,
				    "VBT: CPS compression not supported\n");
			जारी;
		पूर्ण

		index = child->compression_काष्ठाure_index;

		devdata->dsc = kmemdup(&params->data[index],
				       माप(*devdata->dsc), GFP_KERNEL);
	पूर्ण
पूर्ण

अटल u8 translate_iboost(u8 val)
अणु
	अटल स्थिर u8 mapping[] = अणु 1, 3, 7 पूर्ण; /* See VBT spec */

	अगर (val >= ARRAY_SIZE(mapping)) अणु
		DRM_DEBUG_KMS("Unsupported I_boost value found in VBT (%d), display may not work properly\n", val);
		वापस 0;
	पूर्ण
	वापस mapping[val];
पूर्ण

अटल क्रमागत port get_port_by_ddc_pin(काष्ठा drm_i915_निजी *i915, u8 ddc_pin)
अणु
	स्थिर काष्ठा ddi_vbt_port_info *info;
	क्रमागत port port;

	अगर (!ddc_pin)
		वापस PORT_NONE;

	क्रम_each_port(port) अणु
		info = &i915->vbt.ddi_port_info[port];

		अगर (info->devdata && ddc_pin == info->alternate_ddc_pin)
			वापस port;
	पूर्ण

	वापस PORT_NONE;
पूर्ण

अटल व्योम sanitize_ddc_pin(काष्ठा drm_i915_निजी *i915,
			     क्रमागत port port)
अणु
	काष्ठा ddi_vbt_port_info *info = &i915->vbt.ddi_port_info[port];
	काष्ठा child_device_config *child;
	क्रमागत port p;

	p = get_port_by_ddc_pin(i915, info->alternate_ddc_pin);
	अगर (p == PORT_NONE)
		वापस;

	drm_dbg_kms(&i915->drm,
		    "port %c trying to use the same DDC pin (0x%x) as port %c, "
		    "disabling port %c DVI/HDMI support\n",
		    port_name(port), info->alternate_ddc_pin,
		    port_name(p), port_name(p));

	/*
	 * If we have multiple ports supposedly sharing the pin, then dvi/hdmi
	 * couldn't exist on the shared port. Otherwise they share the same ddc
	 * pin and प्रणाली couldn't communicate with them separately.
	 *
	 * Give inverse child device order the priority, last one wins. Yes,
	 * there are real machines (eg. Asrock B250M-HDV) where VBT has both
	 * port A and port E with the same AUX ch and we must pick port E :(
	 */
	info = &i915->vbt.ddi_port_info[p];
	child = &info->devdata->child;

	child->device_type &= ~DEVICE_TYPE_TMDS_DVI_SIGNALING;
	child->device_type |= DEVICE_TYPE_NOT_HDMI_OUTPUT;

	info->alternate_ddc_pin = 0;
पूर्ण

अटल क्रमागत port get_port_by_aux_ch(काष्ठा drm_i915_निजी *i915, u8 aux_ch)
अणु
	स्थिर काष्ठा ddi_vbt_port_info *info;
	क्रमागत port port;

	अगर (!aux_ch)
		वापस PORT_NONE;

	क्रम_each_port(port) अणु
		info = &i915->vbt.ddi_port_info[port];

		अगर (info->devdata && aux_ch == info->alternate_aux_channel)
			वापस port;
	पूर्ण

	वापस PORT_NONE;
पूर्ण

अटल व्योम sanitize_aux_ch(काष्ठा drm_i915_निजी *i915,
			    क्रमागत port port)
अणु
	काष्ठा ddi_vbt_port_info *info = &i915->vbt.ddi_port_info[port];
	काष्ठा child_device_config *child;
	क्रमागत port p;

	p = get_port_by_aux_ch(i915, info->alternate_aux_channel);
	अगर (p == PORT_NONE)
		वापस;

	drm_dbg_kms(&i915->drm,
		    "port %c trying to use the same AUX CH (0x%x) as port %c, "
		    "disabling port %c DP support\n",
		    port_name(port), info->alternate_aux_channel,
		    port_name(p), port_name(p));

	/*
	 * If we have multiple ports supposedly sharing the aux channel, then DP
	 * couldn't exist on the shared port. Otherwise they share the same aux
	 * channel and प्रणाली couldn't communicate with them separately.
	 *
	 * Give inverse child device order the priority, last one wins. Yes,
	 * there are real machines (eg. Asrock B250M-HDV) where VBT has both
	 * port A and port E with the same AUX ch and we must pick port E :(
	 */
	info = &i915->vbt.ddi_port_info[p];
	child = &info->devdata->child;

	child->device_type &= ~DEVICE_TYPE_DISPLAYPORT_OUTPUT;
	info->alternate_aux_channel = 0;
पूर्ण

अटल स्थिर u8 cnp_ddc_pin_map[] = अणु
	[0] = 0, /* N/A */
	[DDC_BUS_DDI_B] = GMBUS_PIN_1_BXT,
	[DDC_BUS_DDI_C] = GMBUS_PIN_2_BXT,
	[DDC_BUS_DDI_D] = GMBUS_PIN_4_CNP, /* sic */
	[DDC_BUS_DDI_F] = GMBUS_PIN_3_BXT, /* sic */
पूर्ण;

अटल स्थिर u8 icp_ddc_pin_map[] = अणु
	[ICL_DDC_BUS_DDI_A] = GMBUS_PIN_1_BXT,
	[ICL_DDC_BUS_DDI_B] = GMBUS_PIN_2_BXT,
	[TGL_DDC_BUS_DDI_C] = GMBUS_PIN_3_BXT,
	[ICL_DDC_BUS_PORT_1] = GMBUS_PIN_9_TC1_ICP,
	[ICL_DDC_BUS_PORT_2] = GMBUS_PIN_10_TC2_ICP,
	[ICL_DDC_BUS_PORT_3] = GMBUS_PIN_11_TC3_ICP,
	[ICL_DDC_BUS_PORT_4] = GMBUS_PIN_12_TC4_ICP,
	[TGL_DDC_BUS_PORT_5] = GMBUS_PIN_13_TC5_TGP,
	[TGL_DDC_BUS_PORT_6] = GMBUS_PIN_14_TC6_TGP,
पूर्ण;

अटल स्थिर u8 rkl_pch_tgp_ddc_pin_map[] = अणु
	[ICL_DDC_BUS_DDI_A] = GMBUS_PIN_1_BXT,
	[ICL_DDC_BUS_DDI_B] = GMBUS_PIN_2_BXT,
	[RKL_DDC_BUS_DDI_D] = GMBUS_PIN_9_TC1_ICP,
	[RKL_DDC_BUS_DDI_E] = GMBUS_PIN_10_TC2_ICP,
पूर्ण;

अटल स्थिर u8 adls_ddc_pin_map[] = अणु
	[ICL_DDC_BUS_DDI_A] = GMBUS_PIN_1_BXT,
	[ADLS_DDC_BUS_PORT_TC1] = GMBUS_PIN_9_TC1_ICP,
	[ADLS_DDC_BUS_PORT_TC2] = GMBUS_PIN_10_TC2_ICP,
	[ADLS_DDC_BUS_PORT_TC3] = GMBUS_PIN_11_TC3_ICP,
	[ADLS_DDC_BUS_PORT_TC4] = GMBUS_PIN_12_TC4_ICP,
पूर्ण;

अटल स्थिर u8 gen9bc_tgp_ddc_pin_map[] = अणु
	[DDC_BUS_DDI_B] = GMBUS_PIN_2_BXT,
	[DDC_BUS_DDI_C] = GMBUS_PIN_9_TC1_ICP,
	[DDC_BUS_DDI_D] = GMBUS_PIN_10_TC2_ICP,
पूर्ण;

अटल u8 map_ddc_pin(काष्ठा drm_i915_निजी *i915, u8 vbt_pin)
अणु
	स्थिर u8 *ddc_pin_map;
	पूर्णांक n_entries;

	अगर (HAS_PCH_ADP(i915)) अणु
		ddc_pin_map = adls_ddc_pin_map;
		n_entries = ARRAY_SIZE(adls_ddc_pin_map);
	पूर्ण अन्यथा अगर (INTEL_PCH_TYPE(i915) >= PCH_DG1) अणु
		वापस vbt_pin;
	पूर्ण अन्यथा अगर (IS_ROCKETLAKE(i915) && INTEL_PCH_TYPE(i915) == PCH_TGP) अणु
		ddc_pin_map = rkl_pch_tgp_ddc_pin_map;
		n_entries = ARRAY_SIZE(rkl_pch_tgp_ddc_pin_map);
	पूर्ण अन्यथा अगर (HAS_PCH_TGP(i915) && IS_GEN9_BC(i915)) अणु
		ddc_pin_map = gen9bc_tgp_ddc_pin_map;
		n_entries = ARRAY_SIZE(gen9bc_tgp_ddc_pin_map);
	पूर्ण अन्यथा अगर (INTEL_PCH_TYPE(i915) >= PCH_ICP) अणु
		ddc_pin_map = icp_ddc_pin_map;
		n_entries = ARRAY_SIZE(icp_ddc_pin_map);
	पूर्ण अन्यथा अगर (HAS_PCH_CNP(i915)) अणु
		ddc_pin_map = cnp_ddc_pin_map;
		n_entries = ARRAY_SIZE(cnp_ddc_pin_map);
	पूर्ण अन्यथा अणु
		/* Assuming direct map */
		वापस vbt_pin;
	पूर्ण

	अगर (vbt_pin < n_entries && ddc_pin_map[vbt_pin] != 0)
		वापस ddc_pin_map[vbt_pin];

	drm_dbg_kms(&i915->drm,
		    "Ignoring alternate pin: VBT claims DDC pin %d, which is not valid for this platform\n",
		    vbt_pin);
	वापस 0;
पूर्ण

अटल क्रमागत port __dvo_port_to_port(पूर्णांक n_ports, पूर्णांक n_dvo,
				    स्थिर पूर्णांक port_mapping[][3], u8 dvo_port)
अणु
	क्रमागत port port;
	पूर्णांक i;

	क्रम (port = PORT_A; port < n_ports; port++) अणु
		क्रम (i = 0; i < n_dvo; i++) अणु
			अगर (port_mapping[port][i] == -1)
				अवरोध;

			अगर (dvo_port == port_mapping[port][i])
				वापस port;
		पूर्ण
	पूर्ण

	वापस PORT_NONE;
पूर्ण

अटल क्रमागत port dvo_port_to_port(काष्ठा drm_i915_निजी *i915,
				  u8 dvo_port)
अणु
	/*
	 * Each DDI port can have more than one value on the "DVO Port" field,
	 * so look क्रम all the possible values क्रम each port.
	 */
	अटल स्थिर पूर्णांक port_mapping[][3] = अणु
		[PORT_A] = अणु DVO_PORT_HDMIA, DVO_PORT_DPA, -1 पूर्ण,
		[PORT_B] = अणु DVO_PORT_HDMIB, DVO_PORT_DPB, -1 पूर्ण,
		[PORT_C] = अणु DVO_PORT_HDMIC, DVO_PORT_DPC, -1 पूर्ण,
		[PORT_D] = अणु DVO_PORT_HDMID, DVO_PORT_DPD, -1 पूर्ण,
		[PORT_E] = अणु DVO_PORT_HDMIE, DVO_PORT_DPE, DVO_PORT_CRT पूर्ण,
		[PORT_F] = अणु DVO_PORT_HDMIF, DVO_PORT_DPF, -1 पूर्ण,
		[PORT_G] = अणु DVO_PORT_HDMIG, DVO_PORT_DPG, -1 पूर्ण,
		[PORT_H] = अणु DVO_PORT_HDMIH, DVO_PORT_DPH, -1 पूर्ण,
		[PORT_I] = अणु DVO_PORT_HDMII, DVO_PORT_DPI, -1 पूर्ण,
	पूर्ण;
	/*
	 * RKL VBT uses PHY based mapping. Combo PHYs A,B,C,D
	 * map to DDI A,B,TC1,TC2 respectively.
	 */
	अटल स्थिर पूर्णांक rkl_port_mapping[][3] = अणु
		[PORT_A] = अणु DVO_PORT_HDMIA, DVO_PORT_DPA, -1 पूर्ण,
		[PORT_B] = अणु DVO_PORT_HDMIB, DVO_PORT_DPB, -1 पूर्ण,
		[PORT_C] = अणु -1 पूर्ण,
		[PORT_TC1] = अणु DVO_PORT_HDMIC, DVO_PORT_DPC, -1 पूर्ण,
		[PORT_TC2] = अणु DVO_PORT_HDMID, DVO_PORT_DPD, -1 पूर्ण,
	पूर्ण;
	/*
	 * Alderlake S ports used in the driver are PORT_A, PORT_D, PORT_E,
	 * PORT_F and PORT_G, we need to map that to correct VBT sections.
	 */
	अटल स्थिर पूर्णांक adls_port_mapping[][3] = अणु
		[PORT_A] = अणु DVO_PORT_HDMIA, DVO_PORT_DPA, -1 पूर्ण,
		[PORT_B] = अणु -1 पूर्ण,
		[PORT_C] = अणु -1 पूर्ण,
		[PORT_TC1] = अणु DVO_PORT_HDMIB, DVO_PORT_DPB, -1 पूर्ण,
		[PORT_TC2] = अणु DVO_PORT_HDMIC, DVO_PORT_DPC, -1 पूर्ण,
		[PORT_TC3] = अणु DVO_PORT_HDMID, DVO_PORT_DPD, -1 पूर्ण,
		[PORT_TC4] = अणु DVO_PORT_HDMIE, DVO_PORT_DPE, -1 पूर्ण,
	पूर्ण;

	अगर (IS_ALDERLAKE_S(i915))
		वापस __dvo_port_to_port(ARRAY_SIZE(adls_port_mapping),
					  ARRAY_SIZE(adls_port_mapping[0]),
					  adls_port_mapping,
					  dvo_port);
	अन्यथा अगर (IS_DG1(i915) || IS_ROCKETLAKE(i915))
		वापस __dvo_port_to_port(ARRAY_SIZE(rkl_port_mapping),
					  ARRAY_SIZE(rkl_port_mapping[0]),
					  rkl_port_mapping,
					  dvo_port);
	अन्यथा
		वापस __dvo_port_to_port(ARRAY_SIZE(port_mapping),
					  ARRAY_SIZE(port_mapping[0]),
					  port_mapping,
					  dvo_port);
पूर्ण

अटल पूर्णांक parse_bdb_230_dp_max_link_rate(स्थिर पूर्णांक vbt_max_link_rate)
अणु
	चयन (vbt_max_link_rate) अणु
	शेष:
	हाल BDB_230_VBT_DP_MAX_LINK_RATE_DEF:
		वापस 0;
	हाल BDB_230_VBT_DP_MAX_LINK_RATE_UHBR20:
		वापस 2000000;
	हाल BDB_230_VBT_DP_MAX_LINK_RATE_UHBR13P5:
		वापस 1350000;
	हाल BDB_230_VBT_DP_MAX_LINK_RATE_UHBR10:
		वापस 1000000;
	हाल BDB_230_VBT_DP_MAX_LINK_RATE_HBR3:
		वापस 810000;
	हाल BDB_230_VBT_DP_MAX_LINK_RATE_HBR2:
		वापस 540000;
	हाल BDB_230_VBT_DP_MAX_LINK_RATE_HBR:
		वापस 270000;
	हाल BDB_230_VBT_DP_MAX_LINK_RATE_LBR:
		वापस 162000;
	पूर्ण
पूर्ण

अटल पूर्णांक parse_bdb_216_dp_max_link_rate(स्थिर पूर्णांक vbt_max_link_rate)
अणु
	चयन (vbt_max_link_rate) अणु
	शेष:
	हाल BDB_216_VBT_DP_MAX_LINK_RATE_HBR3:
		वापस 810000;
	हाल BDB_216_VBT_DP_MAX_LINK_RATE_HBR2:
		वापस 540000;
	हाल BDB_216_VBT_DP_MAX_LINK_RATE_HBR:
		वापस 270000;
	हाल BDB_216_VBT_DP_MAX_LINK_RATE_LBR:
		वापस 162000;
	पूर्ण
पूर्ण

अटल व्योम sanitize_device_type(काष्ठा पूर्णांकel_bios_encoder_data *devdata,
				 क्रमागत port port)
अणु
	काष्ठा drm_i915_निजी *i915 = devdata->i915;
	bool is_hdmi;

	अगर (port != PORT_A || DISPLAY_VER(i915) >= 12)
		वापस;

	अगर (!(devdata->child.device_type & DEVICE_TYPE_TMDS_DVI_SIGNALING))
		वापस;

	is_hdmi = !(devdata->child.device_type & DEVICE_TYPE_NOT_HDMI_OUTPUT);

	drm_dbg_kms(&i915->drm, "VBT claims port A supports DVI%s, ignoring\n",
		    is_hdmi ? "/HDMI" : "");

	devdata->child.device_type &= ~DEVICE_TYPE_TMDS_DVI_SIGNALING;
	devdata->child.device_type |= DEVICE_TYPE_NOT_HDMI_OUTPUT;
पूर्ण

अटल bool
पूर्णांकel_bios_encoder_supports_crt(स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata)
अणु
	वापस devdata->child.device_type & DEVICE_TYPE_ANALOG_OUTPUT;
पूर्ण

bool
पूर्णांकel_bios_encoder_supports_dvi(स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata)
अणु
	वापस devdata->child.device_type & DEVICE_TYPE_TMDS_DVI_SIGNALING;
पूर्ण

bool
पूर्णांकel_bios_encoder_supports_hdmi(स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata)
अणु
	वापस पूर्णांकel_bios_encoder_supports_dvi(devdata) &&
		(devdata->child.device_type & DEVICE_TYPE_NOT_HDMI_OUTPUT) == 0;
पूर्ण

bool
पूर्णांकel_bios_encoder_supports_dp(स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata)
अणु
	वापस devdata->child.device_type & DEVICE_TYPE_DISPLAYPORT_OUTPUT;
पूर्ण

अटल bool
पूर्णांकel_bios_encoder_supports_edp(स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata)
अणु
	वापस पूर्णांकel_bios_encoder_supports_dp(devdata) &&
		devdata->child.device_type & DEVICE_TYPE_INTERNAL_CONNECTOR;
पूर्ण

अटल व्योम parse_ddi_port(काष्ठा drm_i915_निजी *i915,
			   काष्ठा पूर्णांकel_bios_encoder_data *devdata)
अणु
	स्थिर काष्ठा child_device_config *child = &devdata->child;
	काष्ठा ddi_vbt_port_info *info;
	bool is_dvi, is_hdmi, is_dp, is_edp, is_crt, supports_typec_usb, supports_tbt;
	पूर्णांक dp_boost_level, hdmi_boost_level;
	क्रमागत port port;

	port = dvo_port_to_port(i915, child->dvo_port);
	अगर (port == PORT_NONE)
		वापस;

	info = &i915->vbt.ddi_port_info[port];

	अगर (info->devdata) अणु
		drm_dbg_kms(&i915->drm,
			    "More than one child device for port %c in VBT, using the first.\n",
			    port_name(port));
		वापस;
	पूर्ण

	sanitize_device_type(devdata, port);

	is_dvi = पूर्णांकel_bios_encoder_supports_dvi(devdata);
	is_dp = पूर्णांकel_bios_encoder_supports_dp(devdata);
	is_crt = पूर्णांकel_bios_encoder_supports_crt(devdata);
	is_hdmi = पूर्णांकel_bios_encoder_supports_hdmi(devdata);
	is_edp = पूर्णांकel_bios_encoder_supports_edp(devdata);

	supports_typec_usb = पूर्णांकel_bios_encoder_supports_typec_usb(devdata);
	supports_tbt = पूर्णांकel_bios_encoder_supports_tbt(devdata);

	drm_dbg_kms(&i915->drm,
		    "Port %c VBT info: CRT:%d DVI:%d HDMI:%d DP:%d eDP:%d LSPCON:%d USB-Type-C:%d TBT:%d DSC:%d\n",
		    port_name(port), is_crt, is_dvi, is_hdmi, is_dp, is_edp,
		    HAS_LSPCON(i915) && child->lspcon,
		    supports_typec_usb, supports_tbt,
		    devdata->dsc != शून्य);

	अगर (is_dvi) अणु
		u8 ddc_pin;

		ddc_pin = map_ddc_pin(i915, child->ddc_pin);
		अगर (पूर्णांकel_gmbus_is_valid_pin(i915, ddc_pin)) अणु
			info->alternate_ddc_pin = ddc_pin;
			sanitize_ddc_pin(i915, port);
		पूर्ण अन्यथा अणु
			drm_dbg_kms(&i915->drm,
				    "Port %c has invalid DDC pin %d, "
				    "sticking to defaults\n",
				    port_name(port), ddc_pin);
		पूर्ण
	पूर्ण

	अगर (is_dp) अणु
		info->alternate_aux_channel = child->aux_channel;

		sanitize_aux_ch(i915, port);
	पूर्ण

	अगर (i915->vbt.version >= 158) अणु
		/* The VBT HDMI level shअगरt values match the table we have. */
		u8 hdmi_level_shअगरt = child->hdmi_level_shअगरter_value;
		drm_dbg_kms(&i915->drm,
			    "Port %c VBT HDMI level shift: %d\n",
			    port_name(port),
			    hdmi_level_shअगरt);
		info->hdmi_level_shअगरt = hdmi_level_shअगरt;
		info->hdmi_level_shअगरt_set = true;
	पूर्ण

	अगर (i915->vbt.version >= 204) अणु
		पूर्णांक max_पंचांगds_घड़ी;

		चयन (child->hdmi_max_data_rate) अणु
		शेष:
			MISSING_CASE(child->hdmi_max_data_rate);
			fallthrough;
		हाल HDMI_MAX_DATA_RATE_PLATFORM:
			max_पंचांगds_घड़ी = 0;
			अवरोध;
		हाल HDMI_MAX_DATA_RATE_297:
			max_पंचांगds_घड़ी = 297000;
			अवरोध;
		हाल HDMI_MAX_DATA_RATE_165:
			max_पंचांगds_घड़ी = 165000;
			अवरोध;
		पूर्ण

		अगर (max_पंचांगds_घड़ी)
			drm_dbg_kms(&i915->drm,
				    "Port %c VBT HDMI max TMDS clock: %d kHz\n",
				    port_name(port), max_पंचांगds_घड़ी);
		info->max_पंचांगds_घड़ी = max_पंचांगds_घड़ी;
	पूर्ण

	/* I_boost config क्रम SKL and above */
	dp_boost_level = पूर्णांकel_bios_encoder_dp_boost_level(devdata);
	अगर (dp_boost_level)
		drm_dbg_kms(&i915->drm,
			    "Port %c VBT (e)DP boost level: %d\n",
			    port_name(port), dp_boost_level);

	hdmi_boost_level = पूर्णांकel_bios_encoder_hdmi_boost_level(devdata);
	अगर (hdmi_boost_level)
		drm_dbg_kms(&i915->drm,
			    "Port %c VBT HDMI boost level: %d\n",
			    port_name(port), hdmi_boost_level);

	/* DP max link rate क्रम CNL+ */
	अगर (i915->vbt.version >= 216) अणु
		अगर (i915->vbt.version >= 230)
			info->dp_max_link_rate = parse_bdb_230_dp_max_link_rate(child->dp_max_link_rate);
		अन्यथा
			info->dp_max_link_rate = parse_bdb_216_dp_max_link_rate(child->dp_max_link_rate);

		drm_dbg_kms(&i915->drm,
			    "Port %c VBT DP max link rate: %d\n",
			    port_name(port), info->dp_max_link_rate);
	पूर्ण

	info->devdata = devdata;
पूर्ण

अटल व्योम parse_ddi_ports(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा पूर्णांकel_bios_encoder_data *devdata;

	अगर (!HAS_DDI(i915) && !IS_CHERRYVIEW(i915))
		वापस;

	अगर (i915->vbt.version < 155)
		वापस;

	list_क्रम_each_entry(devdata, &i915->vbt.display_devices, node)
		parse_ddi_port(i915, devdata);
पूर्ण

अटल व्योम
parse_general_definitions(काष्ठा drm_i915_निजी *i915,
			  स्थिर काष्ठा bdb_header *bdb)
अणु
	स्थिर काष्ठा bdb_general_definitions *defs;
	काष्ठा पूर्णांकel_bios_encoder_data *devdata;
	स्थिर काष्ठा child_device_config *child;
	पूर्णांक i, child_device_num;
	u8 expected_size;
	u16 block_size;
	पूर्णांक bus_pin;

	defs = find_section(bdb, BDB_GENERAL_DEFINITIONS);
	अगर (!defs) अणु
		drm_dbg_kms(&i915->drm,
			    "No general definition block is found, no devices defined.\n");
		वापस;
	पूर्ण

	block_size = get_blocksize(defs);
	अगर (block_size < माप(*defs)) अणु
		drm_dbg_kms(&i915->drm,
			    "General definitions block too small (%u)\n",
			    block_size);
		वापस;
	पूर्ण

	bus_pin = defs->crt_ddc_gmbus_pin;
	drm_dbg_kms(&i915->drm, "crt_ddc_bus_pin: %d\n", bus_pin);
	अगर (पूर्णांकel_gmbus_is_valid_pin(i915, bus_pin))
		i915->vbt.crt_ddc_pin = bus_pin;

	अगर (bdb->version < 106) अणु
		expected_size = 22;
	पूर्ण अन्यथा अगर (bdb->version < 111) अणु
		expected_size = 27;
	पूर्ण अन्यथा अगर (bdb->version < 195) अणु
		expected_size = LEGACY_CHILD_DEVICE_CONFIG_SIZE;
	पूर्ण अन्यथा अगर (bdb->version == 195) अणु
		expected_size = 37;
	पूर्ण अन्यथा अगर (bdb->version <= 215) अणु
		expected_size = 38;
	पूर्ण अन्यथा अगर (bdb->version <= 237) अणु
		expected_size = 39;
	पूर्ण अन्यथा अणु
		expected_size = माप(*child);
		BUILD_BUG_ON(माप(*child) < 39);
		drm_dbg(&i915->drm,
			"Expected child device config size for VBT version %u not known; assuming %u\n",
			bdb->version, expected_size);
	पूर्ण

	/* Flag an error क्रम unexpected size, but जारी anyway. */
	अगर (defs->child_dev_size != expected_size)
		drm_err(&i915->drm,
			"Unexpected child device config size %u (expected %u for VBT version %u)\n",
			defs->child_dev_size, expected_size, bdb->version);

	/* The legacy sized child device config is the minimum we need. */
	अगर (defs->child_dev_size < LEGACY_CHILD_DEVICE_CONFIG_SIZE) अणु
		drm_dbg_kms(&i915->drm,
			    "Child device config size %u is too small.\n",
			    defs->child_dev_size);
		वापस;
	पूर्ण

	/* get the number of child device */
	child_device_num = (block_size - माप(*defs)) / defs->child_dev_size;

	क्रम (i = 0; i < child_device_num; i++) अणु
		child = child_device_ptr(defs, i);
		अगर (!child->device_type)
			जारी;

		drm_dbg_kms(&i915->drm,
			    "Found VBT child device with type 0x%x\n",
			    child->device_type);

		devdata = kzalloc(माप(*devdata), GFP_KERNEL);
		अगर (!devdata)
			अवरोध;

		devdata->i915 = i915;

		/*
		 * Copy as much as we know (माप) and is available
		 * (child_dev_size) of the child device config. Accessing the
		 * data must depend on VBT version.
		 */
		स_नकल(&devdata->child, child,
		       min_t(माप_प्रकार, defs->child_dev_size, माप(*child)));

		list_add_tail(&devdata->node, &i915->vbt.display_devices);
	पूर्ण

	अगर (list_empty(&i915->vbt.display_devices))
		drm_dbg_kms(&i915->drm,
			    "no child dev is parsed from VBT\n");
पूर्ण

/* Common शेषs which may be overridden by VBT. */
अटल व्योम
init_vbt_शेषs(काष्ठा drm_i915_निजी *i915)
अणु
	i915->vbt.crt_ddc_pin = GMBUS_PIN_VGADDC;

	/* Default to having backlight */
	i915->vbt.backlight.present = true;

	/* LFP panel data */
	i915->vbt.lvds_dither = 1;

	/* SDVO panel data */
	i915->vbt.sdvo_lvds_vbt_mode = शून्य;

	/* general features */
	i915->vbt.पूर्णांक_tv_support = 1;
	i915->vbt.पूर्णांक_crt_support = 1;

	/* driver features */
	i915->vbt.पूर्णांक_lvds_support = 1;

	/* Default to using SSC */
	i915->vbt.lvds_use_ssc = 1;
	/*
	 * Core/SandyBridge/IvyBridge use alternative (120MHz) reference
	 * घड़ी क्रम LVDS.
	 */
	i915->vbt.lvds_ssc_freq = पूर्णांकel_bios_ssc_frequency(i915,
							   !HAS_PCH_SPLIT(i915));
	drm_dbg_kms(&i915->drm, "Set default to SSC at %d kHz\n",
		    i915->vbt.lvds_ssc_freq);
पूर्ण

/* Defaults to initialize only अगर there is no VBT. */
अटल व्योम
init_vbt_missing_शेषs(काष्ठा drm_i915_निजी *i915)
अणु
	क्रमागत port port;
	पूर्णांक ports = PORT_A | PORT_B | PORT_C | PORT_D | PORT_E | PORT_F;

	अगर (!HAS_DDI(i915) && !IS_CHERRYVIEW(i915))
		वापस;

	क्रम_each_port_masked(port, ports) अणु
		काष्ठा पूर्णांकel_bios_encoder_data *devdata;
		काष्ठा child_device_config *child;
		क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, port);

		/*
		 * VBT has the TypeC mode (native,TBT/USB) and we करोn't want
		 * to detect it.
		 */
		अगर (पूर्णांकel_phy_is_tc(i915, phy))
			जारी;

		/* Create fake child device config */
		devdata = kzalloc(माप(*devdata), GFP_KERNEL);
		अगर (!devdata)
			अवरोध;

		devdata->i915 = i915;
		child = &devdata->child;

		अगर (port == PORT_F)
			child->dvo_port = DVO_PORT_HDMIF;
		अन्यथा अगर (port == PORT_E)
			child->dvo_port = DVO_PORT_HDMIE;
		अन्यथा
			child->dvo_port = DVO_PORT_HDMIA + port;

		अगर (port != PORT_A && port != PORT_E)
			child->device_type |= DEVICE_TYPE_TMDS_DVI_SIGNALING;

		अगर (port != PORT_E)
			child->device_type |= DEVICE_TYPE_DISPLAYPORT_OUTPUT;

		अगर (port == PORT_A)
			child->device_type |= DEVICE_TYPE_INTERNAL_CONNECTOR;

		list_add_tail(&devdata->node, &i915->vbt.display_devices);

		drm_dbg_kms(&i915->drm,
			    "Generating default VBT child device with type 0x04%x on port %c\n",
			    child->device_type, port_name(port));
	पूर्ण

	/* Bypass some minimum baseline VBT version checks */
	i915->vbt.version = 155;
पूर्ण

अटल स्थिर काष्ठा bdb_header *get_bdb_header(स्थिर काष्ठा vbt_header *vbt)
अणु
	स्थिर व्योम *_vbt = vbt;

	वापस _vbt + vbt->bdb_offset;
पूर्ण

/**
 * पूर्णांकel_bios_is_valid_vbt - करोes the given buffer contain a valid VBT
 * @buf:	poपूर्णांकer to a buffer to validate
 * @size:	size of the buffer
 *
 * Returns true on valid VBT.
 */
bool पूर्णांकel_bios_is_valid_vbt(स्थिर व्योम *buf, माप_प्रकार size)
अणु
	स्थिर काष्ठा vbt_header *vbt = buf;
	स्थिर काष्ठा bdb_header *bdb;

	अगर (!vbt)
		वापस false;

	अगर (माप(काष्ठा vbt_header) > size) अणु
		DRM_DEBUG_DRIVER("VBT header incomplete\n");
		वापस false;
	पूर्ण

	अगर (स_भेद(vbt->signature, "$VBT", 4)) अणु
		DRM_DEBUG_DRIVER("VBT invalid signature\n");
		वापस false;
	पूर्ण

	अगर (vbt->vbt_size > size) अणु
		DRM_DEBUG_DRIVER("VBT incomplete (vbt_size overflows)\n");
		वापस false;
	पूर्ण

	size = vbt->vbt_size;

	अगर (range_overflows_t(माप_प्रकार,
			      vbt->bdb_offset,
			      माप(काष्ठा bdb_header),
			      size)) अणु
		DRM_DEBUG_DRIVER("BDB header incomplete\n");
		वापस false;
	पूर्ण

	bdb = get_bdb_header(vbt);
	अगर (range_overflows_t(माप_प्रकार, vbt->bdb_offset, bdb->bdb_size, size)) अणु
		DRM_DEBUG_DRIVER("BDB incomplete\n");
		वापस false;
	पूर्ण

	वापस vbt;
पूर्ण

अटल काष्ठा vbt_header *oprom_get_vbt(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(i915->drm.dev);
	व्योम __iomem *p = शून्य, *oprom;
	काष्ठा vbt_header *vbt;
	u16 vbt_size;
	माप_प्रकार i, size;

	oprom = pci_map_rom(pdev, &size);
	अगर (!oprom)
		वापस शून्य;

	/* Scour memory looking क्रम the VBT signature. */
	क्रम (i = 0; i + 4 < size; i += 4) अणु
		अगर (ioपढ़ो32(oprom + i) != *((स्थिर u32 *)"$VBT"))
			जारी;

		p = oprom + i;
		size -= i;
		अवरोध;
	पूर्ण

	अगर (!p)
		जाओ err_unmap_oprom;

	अगर (माप(काष्ठा vbt_header) > size) अणु
		drm_dbg(&i915->drm, "VBT header incomplete\n");
		जाओ err_unmap_oprom;
	पूर्ण

	vbt_size = ioपढ़ो16(p + दुरत्व(काष्ठा vbt_header, vbt_size));
	अगर (vbt_size > size) अणु
		drm_dbg(&i915->drm,
			"VBT incomplete (vbt_size overflows)\n");
		जाओ err_unmap_oprom;
	पूर्ण

	/* The rest will be validated by पूर्णांकel_bios_is_valid_vbt() */
	vbt = kदो_स्मृति(vbt_size, GFP_KERNEL);
	अगर (!vbt)
		जाओ err_unmap_oprom;

	स_नकल_fromio(vbt, p, vbt_size);

	अगर (!पूर्णांकel_bios_is_valid_vbt(vbt, vbt_size))
		जाओ err_मुक्त_vbt;

	pci_unmap_rom(pdev, oprom);

	वापस vbt;

err_मुक्त_vbt:
	kमुक्त(vbt);
err_unmap_oprom:
	pci_unmap_rom(pdev, oprom);

	वापस शून्य;
पूर्ण

/**
 * पूर्णांकel_bios_init - find VBT and initialize settings from the BIOS
 * @i915: i915 device instance
 *
 * Parse and initialize settings from the Video BIOS Tables (VBT). If the VBT
 * was not found in ACPI OpRegion, try to find it in PCI ROM first. Also
 * initialize some शेषs अगर the VBT is not present at all.
 */
व्योम पूर्णांकel_bios_init(काष्ठा drm_i915_निजी *i915)
अणु
	स्थिर काष्ठा vbt_header *vbt = i915->opregion.vbt;
	काष्ठा vbt_header *oprom_vbt = शून्य;
	स्थिर काष्ठा bdb_header *bdb;

	INIT_LIST_HEAD(&i915->vbt.display_devices);

	अगर (!HAS_DISPLAY(i915)) अणु
		drm_dbg_kms(&i915->drm,
			    "Skipping VBT init due to disabled display.\n");
		वापस;
	पूर्ण

	init_vbt_शेषs(i915);

	/* If the OpRegion करोes not have VBT, look in PCI ROM. */
	अगर (!vbt) अणु
		oprom_vbt = oprom_get_vbt(i915);
		अगर (!oprom_vbt)
			जाओ out;

		vbt = oprom_vbt;

		drm_dbg_kms(&i915->drm, "Found valid VBT in PCI ROM\n");
	पूर्ण

	bdb = get_bdb_header(vbt);
	i915->vbt.version = bdb->version;

	drm_dbg_kms(&i915->drm,
		    "VBT signature \"%.*s\", BDB version %d\n",
		    (पूर्णांक)माप(vbt->signature), vbt->signature, bdb->version);

	/* Grab useful general definitions */
	parse_general_features(i915, bdb);
	parse_general_definitions(i915, bdb);
	parse_panel_options(i915, bdb);
	parse_panel_dtd(i915, bdb);
	parse_lfp_backlight(i915, bdb);
	parse_sdvo_panel_data(i915, bdb);
	parse_driver_features(i915, bdb);
	parse_घातer_conservation_features(i915, bdb);
	parse_edp(i915, bdb);
	parse_psr(i915, bdb);
	parse_mipi_config(i915, bdb);
	parse_mipi_sequence(i915, bdb);

	/* Depends on child device list */
	parse_compression_parameters(i915, bdb);

out:
	अगर (!vbt) अणु
		drm_info(&i915->drm,
			 "Failed to find VBIOS tables (VBT)\n");
		init_vbt_missing_शेषs(i915);
	पूर्ण

	/* Further processing on pre-parsed or generated child device data */
	parse_sdvo_device_mapping(i915);
	parse_ddi_ports(i915);

	kमुक्त(oprom_vbt);
पूर्ण

/**
 * पूर्णांकel_bios_driver_हटाओ - Free any resources allocated by पूर्णांकel_bios_init()
 * @i915: i915 device instance
 */
व्योम पूर्णांकel_bios_driver_हटाओ(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा पूर्णांकel_bios_encoder_data *devdata, *n;

	list_क्रम_each_entry_safe(devdata, n, &i915->vbt.display_devices, node) अणु
		list_del(&devdata->node);
		kमुक्त(devdata->dsc);
		kमुक्त(devdata);
	पूर्ण

	kमुक्त(i915->vbt.sdvo_lvds_vbt_mode);
	i915->vbt.sdvo_lvds_vbt_mode = शून्य;
	kमुक्त(i915->vbt.lfp_lvds_vbt_mode);
	i915->vbt.lfp_lvds_vbt_mode = शून्य;
	kमुक्त(i915->vbt.dsi.data);
	i915->vbt.dsi.data = शून्य;
	kमुक्त(i915->vbt.dsi.pps);
	i915->vbt.dsi.pps = शून्य;
	kमुक्त(i915->vbt.dsi.config);
	i915->vbt.dsi.config = शून्य;
	kमुक्त(i915->vbt.dsi.deनिश्चित_seq);
	i915->vbt.dsi.deनिश्चित_seq = शून्य;
पूर्ण

/**
 * पूर्णांकel_bios_is_tv_present - is पूर्णांकegrated TV present in VBT
 * @i915: i915 device instance
 *
 * Return true अगर TV is present. If no child devices were parsed from VBT,
 * assume TV is present.
 */
bool पूर्णांकel_bios_is_tv_present(काष्ठा drm_i915_निजी *i915)
अणु
	स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata;
	स्थिर काष्ठा child_device_config *child;

	अगर (!i915->vbt.पूर्णांक_tv_support)
		वापस false;

	अगर (list_empty(&i915->vbt.display_devices))
		वापस true;

	list_क्रम_each_entry(devdata, &i915->vbt.display_devices, node) अणु
		child = &devdata->child;

		/*
		 * If the device type is not TV, जारी.
		 */
		चयन (child->device_type) अणु
		हाल DEVICE_TYPE_INT_TV:
		हाल DEVICE_TYPE_TV:
		हाल DEVICE_TYPE_TV_SVIDEO_COMPOSITE:
			अवरोध;
		शेष:
			जारी;
		पूर्ण
		/* Only when the addin_offset is non-zero, it is regarded
		 * as present.
		 */
		अगर (child->addin_offset)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * पूर्णांकel_bios_is_lvds_present - is LVDS present in VBT
 * @i915:	i915 device instance
 * @i2c_pin:	i2c pin क्रम LVDS अगर present
 *
 * Return true अगर LVDS is present. If no child devices were parsed from VBT,
 * assume LVDS is present.
 */
bool पूर्णांकel_bios_is_lvds_present(काष्ठा drm_i915_निजी *i915, u8 *i2c_pin)
अणु
	स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata;
	स्थिर काष्ठा child_device_config *child;

	अगर (list_empty(&i915->vbt.display_devices))
		वापस true;

	list_क्रम_each_entry(devdata, &i915->vbt.display_devices, node) अणु
		child = &devdata->child;

		/* If the device type is not LFP, जारी.
		 * We have to check both the new identअगरiers as well as the
		 * old क्रम compatibility with some BIOSes.
		 */
		अगर (child->device_type != DEVICE_TYPE_INT_LFP &&
		    child->device_type != DEVICE_TYPE_LFP)
			जारी;

		अगर (पूर्णांकel_gmbus_is_valid_pin(i915, child->i2c_pin))
			*i2c_pin = child->i2c_pin;

		/* However, we cannot trust the BIOS ग_लिखोrs to populate
		 * the VBT correctly.  Since LVDS requires additional
		 * inक्रमmation from AIM blocks, a non-zero addin offset is
		 * a good indicator that the LVDS is actually present.
		 */
		अगर (child->addin_offset)
			वापस true;

		/* But even then some BIOS ग_लिखोrs perक्रमm some black magic
		 * and instantiate the device without reference to any
		 * additional data.  Trust that अगर the VBT was written पूर्णांकo
		 * the OpRegion then they have validated the LVDS's existence.
		 */
		अगर (i915->opregion.vbt)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * पूर्णांकel_bios_is_port_present - is the specअगरied digital port present
 * @i915:	i915 device instance
 * @port:	port to check
 *
 * Return true अगर the device in %port is present.
 */
bool पूर्णांकel_bios_is_port_present(काष्ठा drm_i915_निजी *i915, क्रमागत port port)
अणु
	स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata;
	स्थिर काष्ठा child_device_config *child;
	अटल स्थिर काष्ठा अणु
		u16 dp, hdmi;
	पूर्ण port_mapping[] = अणु
		[PORT_B] = अणु DVO_PORT_DPB, DVO_PORT_HDMIB, पूर्ण,
		[PORT_C] = अणु DVO_PORT_DPC, DVO_PORT_HDMIC, पूर्ण,
		[PORT_D] = अणु DVO_PORT_DPD, DVO_PORT_HDMID, पूर्ण,
		[PORT_E] = अणु DVO_PORT_DPE, DVO_PORT_HDMIE, पूर्ण,
		[PORT_F] = अणु DVO_PORT_DPF, DVO_PORT_HDMIF, पूर्ण,
	पूर्ण;

	अगर (HAS_DDI(i915)) अणु
		स्थिर काष्ठा ddi_vbt_port_info *port_info =
			&i915->vbt.ddi_port_info[port];

		वापस port_info->devdata;
	पूर्ण

	/* FIXME maybe deal with port A as well? */
	अगर (drm_WARN_ON(&i915->drm,
			port == PORT_A) || port >= ARRAY_SIZE(port_mapping))
		वापस false;

	list_क्रम_each_entry(devdata, &i915->vbt.display_devices, node) अणु
		child = &devdata->child;

		अगर ((child->dvo_port == port_mapping[port].dp ||
		     child->dvo_port == port_mapping[port].hdmi) &&
		    (child->device_type & (DEVICE_TYPE_TMDS_DVI_SIGNALING |
					   DEVICE_TYPE_DISPLAYPORT_OUTPUT)))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * पूर्णांकel_bios_is_port_edp - is the device in given port eDP
 * @i915:	i915 device instance
 * @port:	port to check
 *
 * Return true अगर the device in %port is eDP.
 */
bool पूर्णांकel_bios_is_port_edp(काष्ठा drm_i915_निजी *i915, क्रमागत port port)
अणु
	स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata;
	स्थिर काष्ठा child_device_config *child;
	अटल स्थिर लघु port_mapping[] = अणु
		[PORT_B] = DVO_PORT_DPB,
		[PORT_C] = DVO_PORT_DPC,
		[PORT_D] = DVO_PORT_DPD,
		[PORT_E] = DVO_PORT_DPE,
		[PORT_F] = DVO_PORT_DPF,
	पूर्ण;

	अगर (HAS_DDI(i915)) अणु
		स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata;

		devdata = पूर्णांकel_bios_encoder_data_lookup(i915, port);

		वापस devdata && पूर्णांकel_bios_encoder_supports_edp(devdata);
	पूर्ण

	list_क्रम_each_entry(devdata, &i915->vbt.display_devices, node) अणु
		child = &devdata->child;

		अगर (child->dvo_port == port_mapping[port] &&
		    (child->device_type & DEVICE_TYPE_eDP_BITS) ==
		    (DEVICE_TYPE_eDP & DEVICE_TYPE_eDP_BITS))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool child_dev_is_dp_dual_mode(स्थिर काष्ठा child_device_config *child,
				      क्रमागत port port)
अणु
	अटल स्थिर काष्ठा अणु
		u16 dp, hdmi;
	पूर्ण port_mapping[] = अणु
		/*
		 * Buggy VBTs may declare DP ports as having
		 * HDMI type dvo_port :( So let's check both.
		 */
		[PORT_B] = अणु DVO_PORT_DPB, DVO_PORT_HDMIB, पूर्ण,
		[PORT_C] = अणु DVO_PORT_DPC, DVO_PORT_HDMIC, पूर्ण,
		[PORT_D] = अणु DVO_PORT_DPD, DVO_PORT_HDMID, पूर्ण,
		[PORT_E] = अणु DVO_PORT_DPE, DVO_PORT_HDMIE, पूर्ण,
		[PORT_F] = अणु DVO_PORT_DPF, DVO_PORT_HDMIF, पूर्ण,
	पूर्ण;

	अगर (port == PORT_A || port >= ARRAY_SIZE(port_mapping))
		वापस false;

	अगर ((child->device_type & DEVICE_TYPE_DP_DUAL_MODE_BITS) !=
	    (DEVICE_TYPE_DP_DUAL_MODE & DEVICE_TYPE_DP_DUAL_MODE_BITS))
		वापस false;

	अगर (child->dvo_port == port_mapping[port].dp)
		वापस true;

	/* Only accept a HDMI dvo_port as DP++ अगर it has an AUX channel */
	अगर (child->dvo_port == port_mapping[port].hdmi &&
	    child->aux_channel != 0)
		वापस true;

	वापस false;
पूर्ण

bool पूर्णांकel_bios_is_port_dp_dual_mode(काष्ठा drm_i915_निजी *i915,
				     क्रमागत port port)
अणु
	स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata;

	list_क्रम_each_entry(devdata, &i915->vbt.display_devices, node) अणु
		अगर (child_dev_is_dp_dual_mode(&devdata->child, port))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * पूर्णांकel_bios_is_dsi_present - is DSI present in VBT
 * @i915:	i915 device instance
 * @port:	port क्रम DSI अगर present
 *
 * Return true अगर DSI is present, and वापस the port in %port.
 */
bool पूर्णांकel_bios_is_dsi_present(काष्ठा drm_i915_निजी *i915,
			       क्रमागत port *port)
अणु
	स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata;
	स्थिर काष्ठा child_device_config *child;
	u8 dvo_port;

	list_क्रम_each_entry(devdata, &i915->vbt.display_devices, node) अणु
		child = &devdata->child;

		अगर (!(child->device_type & DEVICE_TYPE_MIPI_OUTPUT))
			जारी;

		dvo_port = child->dvo_port;

		अगर (dvo_port == DVO_PORT_MIPIA ||
		    (dvo_port == DVO_PORT_MIPIB && DISPLAY_VER(i915) >= 11) ||
		    (dvo_port == DVO_PORT_MIPIC && DISPLAY_VER(i915) < 11)) अणु
			अगर (port)
				*port = dvo_port - DVO_PORT_MIPIA;
			वापस true;
		पूर्ण अन्यथा अगर (dvo_port == DVO_PORT_MIPIB ||
			   dvo_port == DVO_PORT_MIPIC ||
			   dvo_port == DVO_PORT_MIPID) अणु
			drm_dbg_kms(&i915->drm,
				    "VBT has unsupported DSI port %c\n",
				    port_name(dvo_port - DVO_PORT_MIPIA));
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम fill_dsc(काष्ठा पूर्णांकel_crtc_state *crtc_state,
		     काष्ठा dsc_compression_parameters_entry *dsc,
		     पूर्णांक dsc_max_bpc)
अणु
	काष्ठा drm_dsc_config *vdsc_cfg = &crtc_state->dsc.config;
	पूर्णांक bpc = 8;

	vdsc_cfg->dsc_version_major = dsc->version_major;
	vdsc_cfg->dsc_version_minor = dsc->version_minor;

	अगर (dsc->support_12bpc && dsc_max_bpc >= 12)
		bpc = 12;
	अन्यथा अगर (dsc->support_10bpc && dsc_max_bpc >= 10)
		bpc = 10;
	अन्यथा अगर (dsc->support_8bpc && dsc_max_bpc >= 8)
		bpc = 8;
	अन्यथा
		DRM_DEBUG_KMS("VBT: Unsupported BPC %d for DCS\n",
			      dsc_max_bpc);

	crtc_state->pipe_bpp = bpc * 3;

	crtc_state->dsc.compressed_bpp = min(crtc_state->pipe_bpp,
					     VBT_DSC_MAX_BPP(dsc->max_bpp));

	/*
	 * FIXME: This is ugly, and slice count should take DSC engine
	 * throughput etc. पूर्णांकo account.
	 *
	 * Also, per spec DSI supports 1, 2, 3 or 4 horizontal slices.
	 */
	अगर (dsc->slices_per_line & BIT(2)) अणु
		crtc_state->dsc.slice_count = 4;
	पूर्ण अन्यथा अगर (dsc->slices_per_line & BIT(1)) अणु
		crtc_state->dsc.slice_count = 2;
	पूर्ण अन्यथा अणु
		/* FIXME */
		अगर (!(dsc->slices_per_line & BIT(0)))
			DRM_DEBUG_KMS("VBT: Unsupported DSC slice count for DSI\n");

		crtc_state->dsc.slice_count = 1;
	पूर्ण

	अगर (crtc_state->hw.adjusted_mode.crtc_hdisplay %
	    crtc_state->dsc.slice_count != 0)
		DRM_DEBUG_KMS("VBT: DSC hdisplay %d not divisible by slice count %d\n",
			      crtc_state->hw.adjusted_mode.crtc_hdisplay,
			      crtc_state->dsc.slice_count);

	/*
	 * The VBT rc_buffer_block_size and rc_buffer_size definitions
	 * correspond to DP 1.4 DPCD offsets 0x62 and 0x63.
	 */
	vdsc_cfg->rc_model_size = drm_dsc_dp_rc_buffer_size(dsc->rc_buffer_block_size,
							    dsc->rc_buffer_size);

	/* FIXME: DSI spec says bpc + 1 क्रम this one */
	vdsc_cfg->line_buf_depth = VBT_DSC_LINE_BUFFER_DEPTH(dsc->line_buffer_depth);

	vdsc_cfg->block_pred_enable = dsc->block_prediction_enable;

	vdsc_cfg->slice_height = dsc->slice_height;
पूर्ण

/* FIXME: initially DSI specअगरic */
bool पूर्णांकel_bios_get_dsc_params(काष्ठा पूर्णांकel_encoder *encoder,
			       काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       पूर्णांक dsc_max_bpc)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata;
	स्थिर काष्ठा child_device_config *child;

	list_क्रम_each_entry(devdata, &i915->vbt.display_devices, node) अणु
		child = &devdata->child;

		अगर (!(child->device_type & DEVICE_TYPE_MIPI_OUTPUT))
			जारी;

		अगर (child->dvo_port - DVO_PORT_MIPIA == encoder->port) अणु
			अगर (!devdata->dsc)
				वापस false;

			अगर (crtc_state)
				fill_dsc(crtc_state, devdata->dsc, dsc_max_bpc);

			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

/**
 * पूर्णांकel_bios_is_port_hpd_inverted - is HPD inverted क्रम %port
 * @i915:	i915 device instance
 * @port:	port to check
 *
 * Return true अगर HPD should be inverted क्रम %port.
 */
bool
पूर्णांकel_bios_is_port_hpd_inverted(स्थिर काष्ठा drm_i915_निजी *i915,
				क्रमागत port port)
अणु
	स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata =
		i915->vbt.ddi_port_info[port].devdata;

	अगर (drm_WARN_ON_ONCE(&i915->drm, !IS_GEN9_LP(i915)))
		वापस false;

	वापस devdata && devdata->child.hpd_invert;
पूर्ण

/**
 * पूर्णांकel_bios_is_lspcon_present - अगर LSPCON is attached on %port
 * @i915:	i915 device instance
 * @port:	port to check
 *
 * Return true अगर LSPCON is present on this port
 */
bool
पूर्णांकel_bios_is_lspcon_present(स्थिर काष्ठा drm_i915_निजी *i915,
			     क्रमागत port port)
अणु
	स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata =
		i915->vbt.ddi_port_info[port].devdata;

	वापस HAS_LSPCON(i915) && devdata && devdata->child.lspcon;
पूर्ण

/**
 * पूर्णांकel_bios_is_lane_reversal_needed - अगर lane reversal needed on port
 * @i915:       i915 device instance
 * @port:       port to check
 *
 * Return true अगर port requires lane reversal
 */
bool
पूर्णांकel_bios_is_lane_reversal_needed(स्थिर काष्ठा drm_i915_निजी *i915,
				   क्रमागत port port)
अणु
	स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata =
		i915->vbt.ddi_port_info[port].devdata;

	वापस devdata && devdata->child.lane_reversal;
पूर्ण

क्रमागत aux_ch पूर्णांकel_bios_port_aux_ch(काष्ठा drm_i915_निजी *i915,
				   क्रमागत port port)
अणु
	स्थिर काष्ठा ddi_vbt_port_info *info =
		&i915->vbt.ddi_port_info[port];
	क्रमागत aux_ch aux_ch;

	अगर (!info->alternate_aux_channel) अणु
		aux_ch = (क्रमागत aux_ch)port;

		drm_dbg_kms(&i915->drm,
			    "using AUX %c for port %c (platform default)\n",
			    aux_ch_name(aux_ch), port_name(port));
		वापस aux_ch;
	पूर्ण

	/*
	 * RKL/DG1 VBT uses PHY based mapping. Combo PHYs A,B,C,D
	 * map to DDI A,B,TC1,TC2 respectively.
	 *
	 * ADL-S VBT uses PHY based mapping. Combo PHYs A,B,C,D,E
	 * map to DDI A,TC1,TC2,TC3,TC4 respectively.
	 */
	चयन (info->alternate_aux_channel) अणु
	हाल DP_AUX_A:
		aux_ch = AUX_CH_A;
		अवरोध;
	हाल DP_AUX_B:
		अगर (IS_ALDERLAKE_S(i915))
			aux_ch = AUX_CH_USBC1;
		अन्यथा
			aux_ch = AUX_CH_B;
		अवरोध;
	हाल DP_AUX_C:
		अगर (IS_ALDERLAKE_S(i915))
			aux_ch = AUX_CH_USBC2;
		अन्यथा अगर (IS_DG1(i915) || IS_ROCKETLAKE(i915))
			aux_ch = AUX_CH_USBC1;
		अन्यथा
			aux_ch = AUX_CH_C;
		अवरोध;
	हाल DP_AUX_D:
		अगर (IS_ALDERLAKE_S(i915))
			aux_ch = AUX_CH_USBC3;
		अन्यथा अगर (IS_DG1(i915) || IS_ROCKETLAKE(i915))
			aux_ch = AUX_CH_USBC2;
		अन्यथा
			aux_ch = AUX_CH_D;
		अवरोध;
	हाल DP_AUX_E:
		अगर (IS_ALDERLAKE_S(i915))
			aux_ch = AUX_CH_USBC4;
		अन्यथा
			aux_ch = AUX_CH_E;
		अवरोध;
	हाल DP_AUX_F:
		aux_ch = AUX_CH_F;
		अवरोध;
	हाल DP_AUX_G:
		aux_ch = AUX_CH_G;
		अवरोध;
	हाल DP_AUX_H:
		aux_ch = AUX_CH_H;
		अवरोध;
	हाल DP_AUX_I:
		aux_ch = AUX_CH_I;
		अवरोध;
	शेष:
		MISSING_CASE(info->alternate_aux_channel);
		aux_ch = AUX_CH_A;
		अवरोध;
	पूर्ण

	drm_dbg_kms(&i915->drm, "using AUX %c for port %c (VBT)\n",
		    aux_ch_name(aux_ch), port_name(port));

	वापस aux_ch;
पूर्ण

पूर्णांक पूर्णांकel_bios_max_पंचांगds_घड़ी(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);

	वापस i915->vbt.ddi_port_info[encoder->port].max_पंचांगds_घड़ी;
पूर्ण

पूर्णांक पूर्णांकel_bios_hdmi_level_shअगरt(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	स्थिर काष्ठा ddi_vbt_port_info *info =
		&i915->vbt.ddi_port_info[encoder->port];

	वापस info->hdmi_level_shअगरt_set ? info->hdmi_level_shअगरt : -1;
पूर्ण

पूर्णांक पूर्णांकel_bios_encoder_dp_boost_level(स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata)
अणु
	अगर (!devdata || devdata->i915->vbt.version < 196 || !devdata->child.iboost)
		वापस 0;

	वापस translate_iboost(devdata->child.dp_iboost_level);
पूर्ण

पूर्णांक पूर्णांकel_bios_encoder_hdmi_boost_level(स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata)
अणु
	अगर (!devdata || devdata->i915->vbt.version < 196 || !devdata->child.iboost)
		वापस 0;

	वापस translate_iboost(devdata->child.hdmi_iboost_level);
पूर्ण

पूर्णांक पूर्णांकel_bios_dp_max_link_rate(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);

	वापस i915->vbt.ddi_port_info[encoder->port].dp_max_link_rate;
पूर्ण

पूर्णांक पूर्णांकel_bios_alternate_ddc_pin(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);

	वापस i915->vbt.ddi_port_info[encoder->port].alternate_ddc_pin;
पूर्ण

bool पूर्णांकel_bios_encoder_supports_typec_usb(स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata)
अणु
	वापस devdata->i915->vbt.version >= 195 && devdata->child.dp_usb_type_c;
पूर्ण

bool पूर्णांकel_bios_encoder_supports_tbt(स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata)
अणु
	वापस devdata->i915->vbt.version >= 209 && devdata->child.tbt;
पूर्ण

स्थिर काष्ठा पूर्णांकel_bios_encoder_data *
पूर्णांकel_bios_encoder_data_lookup(काष्ठा drm_i915_निजी *i915, क्रमागत port port)
अणु
	वापस i915->vbt.ddi_port_info[port].devdata;
पूर्ण
