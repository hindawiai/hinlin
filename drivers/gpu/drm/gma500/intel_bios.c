<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2006 Intel Corporation
 *
 * Authors:
 *    Eric Anholt <eric@anholt.net>
 */
#समावेश <drm/drm.h>
#समावेश <drm/drm_dp_helper.h>

#समावेश "intel_bios.h"
#समावेश "psb_drv.h"
#समावेश "psb_intel_drv.h"
#समावेश "psb_intel_reg.h"

#घोषणा	SLAVE_ADDR1	0x70
#घोषणा	SLAVE_ADDR2	0x72

अटल व्योम *find_section(काष्ठा bdb_header *bdb, पूर्णांक section_id)
अणु
	u8 *base = (u8 *)bdb;
	पूर्णांक index = 0;
	u16 total, current_size;
	u8 current_id;

	/* skip to first section */
	index += bdb->header_size;
	total = bdb->bdb_size;

	/* walk the sections looking क्रम section_id */
	जबतक (index < total) अणु
		current_id = *(base + index);
		index++;
		current_size = *((u16 *)(base + index));
		index += 2;
		अगर (current_id == section_id)
			वापस base + index;
		index += current_size;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम
parse_edp(काष्ठा drm_psb_निजी *dev_priv, काष्ठा bdb_header *bdb)
अणु
	काष्ठा bdb_edp *edp;
	काष्ठा edp_घातer_seq *edp_pps;
	काष्ठा edp_link_params *edp_link_params;
	uपूर्णांक8_t	panel_type;

	edp = find_section(bdb, BDB_EDP);

	dev_priv->edp.bpp = 18;
	अगर (!edp) अणु
		अगर (dev_priv->edp.support) अणु
			DRM_DEBUG_KMS("No eDP BDB found but eDP panel supported, assume %dbpp panel color depth.\n",
				      dev_priv->edp.bpp);
		पूर्ण
		वापस;
	पूर्ण

	panel_type = dev_priv->panel_type;
	चयन ((edp->color_depth >> (panel_type * 2)) & 3) अणु
	हाल EDP_18BPP:
		dev_priv->edp.bpp = 18;
		अवरोध;
	हाल EDP_24BPP:
		dev_priv->edp.bpp = 24;
		अवरोध;
	हाल EDP_30BPP:
		dev_priv->edp.bpp = 30;
		अवरोध;
	पूर्ण

	/* Get the eDP sequencing and link info */
	edp_pps = &edp->घातer_seqs[panel_type];
	edp_link_params = &edp->link_params[panel_type];

	dev_priv->edp.pps = *edp_pps;

	DRM_DEBUG_KMS("EDP timing in vbt t1_t3 %d t8 %d t9 %d t10 %d t11_t12 %d\n",
				dev_priv->edp.pps.t1_t3, dev_priv->edp.pps.t8,
				dev_priv->edp.pps.t9, dev_priv->edp.pps.t10,
				dev_priv->edp.pps.t11_t12);

	dev_priv->edp.rate = edp_link_params->rate ? DP_LINK_BW_2_7 :
		DP_LINK_BW_1_62;
	चयन (edp_link_params->lanes) अणु
	हाल 0:
		dev_priv->edp.lanes = 1;
		अवरोध;
	हाल 1:
		dev_priv->edp.lanes = 2;
		अवरोध;
	हाल 3:
	शेष:
		dev_priv->edp.lanes = 4;
		अवरोध;
	पूर्ण
	DRM_DEBUG_KMS("VBT reports EDP: Lane_count %d, Lane_rate %d, Bpp %d\n",
			dev_priv->edp.lanes, dev_priv->edp.rate, dev_priv->edp.bpp);

	चयन (edp_link_params->preemphasis) अणु
	हाल 0:
		dev_priv->edp.preemphasis = DP_TRAIN_PRE_EMPH_LEVEL_0;
		अवरोध;
	हाल 1:
		dev_priv->edp.preemphasis = DP_TRAIN_PRE_EMPH_LEVEL_1;
		अवरोध;
	हाल 2:
		dev_priv->edp.preemphasis = DP_TRAIN_PRE_EMPH_LEVEL_2;
		अवरोध;
	हाल 3:
		dev_priv->edp.preemphasis = DP_TRAIN_PRE_EMPH_LEVEL_3;
		अवरोध;
	पूर्ण
	चयन (edp_link_params->vswing) अणु
	हाल 0:
		dev_priv->edp.vswing = DP_TRAIN_VOLTAGE_SWING_LEVEL_0;
		अवरोध;
	हाल 1:
		dev_priv->edp.vswing = DP_TRAIN_VOLTAGE_SWING_LEVEL_1;
		अवरोध;
	हाल 2:
		dev_priv->edp.vswing = DP_TRAIN_VOLTAGE_SWING_LEVEL_2;
		अवरोध;
	हाल 3:
		dev_priv->edp.vswing = DP_TRAIN_VOLTAGE_SWING_LEVEL_3;
		अवरोध;
	पूर्ण
	DRM_DEBUG_KMS("VBT reports EDP: VSwing  %d, Preemph %d\n",
			dev_priv->edp.vswing, dev_priv->edp.preemphasis);
पूर्ण

अटल u16
get_blocksize(व्योम *p)
अणु
	u16 *block_ptr, block_size;

	block_ptr = (u16 *)((अक्षर *)p - 2);
	block_size = *block_ptr;
	वापस block_size;
पूर्ण

अटल व्योम fill_detail_timing_data(काष्ठा drm_display_mode *panel_fixed_mode,
			काष्ठा lvds_dvo_timing *dvo_timing)
अणु
	panel_fixed_mode->hdisplay = (dvo_timing->hactive_hi << 8) |
		dvo_timing->hactive_lo;
	panel_fixed_mode->hsync_start = panel_fixed_mode->hdisplay +
		((dvo_timing->hsync_off_hi << 8) | dvo_timing->hsync_off_lo);
	panel_fixed_mode->hsync_end = panel_fixed_mode->hsync_start +
		dvo_timing->hsync_pulse_width;
	panel_fixed_mode->htotal = panel_fixed_mode->hdisplay +
		((dvo_timing->hblank_hi << 8) | dvo_timing->hblank_lo);

	panel_fixed_mode->vdisplay = (dvo_timing->vactive_hi << 8) |
		dvo_timing->vactive_lo;
	panel_fixed_mode->vsync_start = panel_fixed_mode->vdisplay +
		dvo_timing->vsync_off;
	panel_fixed_mode->vsync_end = panel_fixed_mode->vsync_start +
		dvo_timing->vsync_pulse_width;
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

	/* Some VBTs have bogus h/vtotal values */
	अगर (panel_fixed_mode->hsync_end > panel_fixed_mode->htotal)
		panel_fixed_mode->htotal = panel_fixed_mode->hsync_end + 1;
	अगर (panel_fixed_mode->vsync_end > panel_fixed_mode->vtotal)
		panel_fixed_mode->vtotal = panel_fixed_mode->vsync_end + 1;

	drm_mode_set_name(panel_fixed_mode);
पूर्ण

अटल व्योम parse_backlight_data(काष्ठा drm_psb_निजी *dev_priv,
				काष्ठा bdb_header *bdb)
अणु
	काष्ठा bdb_lvds_backlight *vbt_lvds_bl = शून्य;
	काष्ठा bdb_lvds_backlight *lvds_bl;
	u8 p_type = 0;
	व्योम *bl_start = शून्य;
	काष्ठा bdb_lvds_options *lvds_opts
				= find_section(bdb, BDB_LVDS_OPTIONS);

	dev_priv->lvds_bl = शून्य;

	अगर (lvds_opts)
		p_type = lvds_opts->panel_type;
	अन्यथा
		वापस;

	bl_start = find_section(bdb, BDB_LVDS_BACKLIGHT);
	vbt_lvds_bl = (काष्ठा bdb_lvds_backlight *)(bl_start + 1) + p_type;

	lvds_bl = kmemdup(vbt_lvds_bl, माप(*vbt_lvds_bl), GFP_KERNEL);
	अगर (!lvds_bl) अणु
		dev_err(dev_priv->dev->dev, "out of memory for backlight data\n");
		वापस;
	पूर्ण
	dev_priv->lvds_bl = lvds_bl;
पूर्ण

/* Try to find पूर्णांकegrated panel data */
अटल व्योम parse_lfp_panel_data(काष्ठा drm_psb_निजी *dev_priv,
			    काष्ठा bdb_header *bdb)
अणु
	काष्ठा bdb_lvds_options *lvds_options;
	काष्ठा bdb_lvds_lfp_data *lvds_lfp_data;
	काष्ठा bdb_lvds_lfp_data_entry *entry;
	काष्ठा lvds_dvo_timing *dvo_timing;
	काष्ठा drm_display_mode *panel_fixed_mode;

	/* Defaults अगर we can't find VBT info */
	dev_priv->lvds_dither = 0;
	dev_priv->lvds_vbt = 0;

	lvds_options = find_section(bdb, BDB_LVDS_OPTIONS);
	अगर (!lvds_options)
		वापस;

	dev_priv->lvds_dither = lvds_options->pixel_dither;
	dev_priv->panel_type = lvds_options->panel_type;

	अगर (lvds_options->panel_type == 0xff)
		वापस;

	lvds_lfp_data = find_section(bdb, BDB_LVDS_LFP_DATA);
	अगर (!lvds_lfp_data)
		वापस;


	entry = &lvds_lfp_data->data[lvds_options->panel_type];
	dvo_timing = &entry->dvo_timing;

	panel_fixed_mode = kzalloc(माप(*panel_fixed_mode),
				      GFP_KERNEL);
	अगर (panel_fixed_mode == शून्य) अणु
		dev_err(dev_priv->dev->dev, "out of memory for fixed panel mode\n");
		वापस;
	पूर्ण

	dev_priv->lvds_vbt = 1;
	fill_detail_timing_data(panel_fixed_mode, dvo_timing);

	अगर (panel_fixed_mode->htotal > 0 && panel_fixed_mode->vtotal > 0) अणु
		dev_priv->lfp_lvds_vbt_mode = panel_fixed_mode;
		drm_mode_debug_prपूर्णांकmodeline(panel_fixed_mode);
	पूर्ण अन्यथा अणु
		dev_dbg(dev_priv->dev->dev, "ignoring invalid LVDS VBT\n");
		dev_priv->lvds_vbt = 0;
		kमुक्त(panel_fixed_mode);
	पूर्ण
	वापस;
पूर्ण

/* Try to find sdvo panel data */
अटल व्योम parse_sdvo_panel_data(काष्ठा drm_psb_निजी *dev_priv,
		      काष्ठा bdb_header *bdb)
अणु
	काष्ठा bdb_sdvo_lvds_options *sdvo_lvds_options;
	काष्ठा lvds_dvo_timing *dvo_timing;
	काष्ठा drm_display_mode *panel_fixed_mode;

	dev_priv->sdvo_lvds_vbt_mode = शून्य;

	sdvo_lvds_options = find_section(bdb, BDB_SDVO_LVDS_OPTIONS);
	अगर (!sdvo_lvds_options)
		वापस;

	dvo_timing = find_section(bdb, BDB_SDVO_PANEL_DTDS);
	अगर (!dvo_timing)
		वापस;

	panel_fixed_mode = kzalloc(माप(*panel_fixed_mode), GFP_KERNEL);

	अगर (!panel_fixed_mode)
		वापस;

	fill_detail_timing_data(panel_fixed_mode,
			dvo_timing + sdvo_lvds_options->panel_type);

	dev_priv->sdvo_lvds_vbt_mode = panel_fixed_mode;

	वापस;
पूर्ण

अटल व्योम parse_general_features(काष्ठा drm_psb_निजी *dev_priv,
		       काष्ठा bdb_header *bdb)
अणु
	काष्ठा bdb_general_features *general;

	/* Set sensible शेषs in हाल we can't find the general block */
	dev_priv->पूर्णांक_tv_support = 1;
	dev_priv->पूर्णांक_crt_support = 1;

	general = find_section(bdb, BDB_GENERAL_FEATURES);
	अगर (general) अणु
		dev_priv->पूर्णांक_tv_support = general->पूर्णांक_tv_support;
		dev_priv->पूर्णांक_crt_support = general->पूर्णांक_crt_support;
		dev_priv->lvds_use_ssc = general->enable_ssc;

		अगर (dev_priv->lvds_use_ssc) अणु
			dev_priv->lvds_ssc_freq
				= general->ssc_freq ? 100 : 96;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
parse_sdvo_device_mapping(काष्ठा drm_psb_निजी *dev_priv,
			  काष्ठा bdb_header *bdb)
अणु
	काष्ठा sdvo_device_mapping *p_mapping;
	काष्ठा bdb_general_definitions *p_defs;
	काष्ठा child_device_config *p_child;
	पूर्णांक i, child_device_num, count;
	u16	block_size;

	p_defs = find_section(bdb, BDB_GENERAL_DEFINITIONS);
	अगर (!p_defs) अणु
		DRM_DEBUG_KMS("No general definition block is found, unable to construct sdvo mapping.\n");
		वापस;
	पूर्ण
	/* judge whether the size of child device meets the requirements.
	 * If the child device size obtained from general definition block
	 * is dअगरferent with माप(काष्ठा child_device_config), skip the
	 * parsing of sdvo device info
	 */
	अगर (p_defs->child_dev_size != माप(*p_child)) अणु
		/* dअगरferent child dev size . Ignore it */
		DRM_DEBUG_KMS("different child size is found. Invalid.\n");
		वापस;
	पूर्ण
	/* get the block size of general definitions */
	block_size = get_blocksize(p_defs);
	/* get the number of child device */
	child_device_num = (block_size - माप(*p_defs)) /
				माप(*p_child);
	count = 0;
	क्रम (i = 0; i < child_device_num; i++) अणु
		p_child = &(p_defs->devices[i]);
		अगर (!p_child->device_type) अणु
			/* skip the device block अगर device type is invalid */
			जारी;
		पूर्ण
		अगर (p_child->slave_addr != SLAVE_ADDR1 &&
			p_child->slave_addr != SLAVE_ADDR2) अणु
			/*
			 * If the slave address is neither 0x70 nor 0x72,
			 * it is not a SDVO device. Skip it.
			 */
			जारी;
		पूर्ण
		अगर (p_child->dvo_port != DEVICE_PORT_DVOB &&
			p_child->dvo_port != DEVICE_PORT_DVOC) अणु
			/* skip the incorrect SDVO port */
			DRM_DEBUG_KMS("Incorrect SDVO port. Skip it\n");
			जारी;
		पूर्ण
		DRM_DEBUG_KMS("the SDVO device with slave addr %2x is found on"
				" %s port\n",
				p_child->slave_addr,
				(p_child->dvo_port == DEVICE_PORT_DVOB) ?
					"SDVOB" : "SDVOC");
		p_mapping = &(dev_priv->sdvo_mappings[p_child->dvo_port - 1]);
		अगर (!p_mapping->initialized) अणु
			p_mapping->dvo_port = p_child->dvo_port;
			p_mapping->slave_addr = p_child->slave_addr;
			p_mapping->dvo_wiring = p_child->dvo_wiring;
			p_mapping->ddc_pin = p_child->ddc_pin;
			p_mapping->i2c_pin = p_child->i2c_pin;
			p_mapping->initialized = 1;
			DRM_DEBUG_KMS("SDVO device: dvo=%x, addr=%x, wiring=%d, ddc_pin=%d, i2c_pin=%d\n",
				      p_mapping->dvo_port,
				      p_mapping->slave_addr,
				      p_mapping->dvo_wiring,
				      p_mapping->ddc_pin,
				      p_mapping->i2c_pin);
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("Maybe one SDVO port is shared by "
					 "two SDVO device.\n");
		पूर्ण
		अगर (p_child->slave2_addr) अणु
			/* Maybe this is a SDVO device with multiple inमाला_दो */
			/* And the mapping info is not added */
			DRM_DEBUG_KMS("there exists the slave2_addr. Maybe this"
				" is a SDVO device with multiple inputs.\n");
		पूर्ण
		count++;
	पूर्ण

	अगर (!count) अणु
		/* No SDVO device info is found */
		DRM_DEBUG_KMS("No SDVO device info is found in VBT\n");
	पूर्ण
	वापस;
पूर्ण


अटल व्योम
parse_driver_features(काष्ठा drm_psb_निजी *dev_priv,
		      काष्ठा bdb_header *bdb)
अणु
	काष्ठा bdb_driver_features *driver;

	driver = find_section(bdb, BDB_DRIVER_FEATURES);
	अगर (!driver)
		वापस;

	अगर (driver->lvds_config == BDB_DRIVER_FEATURE_EDP)
		dev_priv->edp.support = 1;

	dev_priv->lvds_enabled_in_vbt = driver->lvds_config != 0;
	DRM_DEBUG_KMS("LVDS VBT config bits: 0x%x\n", driver->lvds_config);

	/* This bit means to use 96Mhz क्रम DPLL_A or not */
	अगर (driver->primary_lfp_id)
		dev_priv->dplla_96mhz = true;
	अन्यथा
		dev_priv->dplla_96mhz = false;
पूर्ण

अटल व्योम
parse_device_mapping(काष्ठा drm_psb_निजी *dev_priv,
		       काष्ठा bdb_header *bdb)
अणु
	काष्ठा bdb_general_definitions *p_defs;
	काष्ठा child_device_config *p_child, *child_dev_ptr;
	पूर्णांक i, child_device_num, count;
	u16	block_size;

	p_defs = find_section(bdb, BDB_GENERAL_DEFINITIONS);
	अगर (!p_defs) अणु
		DRM_DEBUG_KMS("No general definition block is found, no devices defined.\n");
		वापस;
	पूर्ण
	/* judge whether the size of child device meets the requirements.
	 * If the child device size obtained from general definition block
	 * is dअगरferent with माप(काष्ठा child_device_config), skip the
	 * parsing of sdvo device info
	 */
	अगर (p_defs->child_dev_size != माप(*p_child)) अणु
		/* dअगरferent child dev size . Ignore it */
		DRM_DEBUG_KMS("different child size is found. Invalid.\n");
		वापस;
	पूर्ण
	/* get the block size of general definitions */
	block_size = get_blocksize(p_defs);
	/* get the number of child device */
	child_device_num = (block_size - माप(*p_defs)) /
				माप(*p_child);
	count = 0;
	/* get the number of child devices that are present */
	क्रम (i = 0; i < child_device_num; i++) अणु
		p_child = &(p_defs->devices[i]);
		अगर (!p_child->device_type) अणु
			/* skip the device block अगर device type is invalid */
			जारी;
		पूर्ण
		count++;
	पूर्ण
	अगर (!count) अणु
		DRM_DEBUG_KMS("no child dev is parsed from VBT\n");
		वापस;
	पूर्ण
	dev_priv->child_dev = kसुस्मृति(count, माप(*p_child), GFP_KERNEL);
	अगर (!dev_priv->child_dev) अणु
		DRM_DEBUG_KMS("No memory space for child devices\n");
		वापस;
	पूर्ण

	dev_priv->child_dev_num = count;
	count = 0;
	क्रम (i = 0; i < child_device_num; i++) अणु
		p_child = &(p_defs->devices[i]);
		अगर (!p_child->device_type) अणु
			/* skip the device block अगर device type is invalid */
			जारी;
		पूर्ण
		child_dev_ptr = dev_priv->child_dev + count;
		count++;
		स_नकल((व्योम *)child_dev_ptr, (व्योम *)p_child,
					माप(*p_child));
	पूर्ण
	वापस;
पूर्ण


/**
 * psb_पूर्णांकel_init_bios - initialize VBIOS settings & find VBT
 * @dev: DRM device
 *
 * Loads the Video BIOS and checks that the VBT exists.  Sets scratch रेजिस्टरs
 * to appropriate values.
 *
 * VBT existence is a sanity check that is relied on by other i830_bios.c code.
 * Note that it would be better to use a BIOS call to get the VBT, as BIOSes may
 * feed an updated VBT back through that, compared to what we'll fetch using
 * this method of groping around in the BIOS data.
 *
 * Returns 0 on success, nonzero on failure.
 */
पूर्णांक psb_पूर्णांकel_init_bios(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	काष्ठा vbt_header *vbt = शून्य;
	काष्ठा bdb_header *bdb = शून्य;
	u8 __iomem *bios = शून्य;
	माप_प्रकार size;
	पूर्णांक i;


	dev_priv->panel_type = 0xff;

	/* XXX Should this validation be moved to पूर्णांकel_opregion.c? */
	अगर (dev_priv->opregion.vbt) अणु
		काष्ठा vbt_header *vbt = dev_priv->opregion.vbt;
		अगर (स_भेद(vbt->signature, "$VBT", 4) == 0) अणु
			DRM_DEBUG_KMS("Using VBT from OpRegion: %20s\n",
					 vbt->signature);
			bdb = (काष्ठा bdb_header *)((अक्षर *)vbt + vbt->bdb_offset);
		पूर्ण अन्यथा
			dev_priv->opregion.vbt = शून्य;
	पूर्ण

	अगर (bdb == शून्य) अणु
		bios = pci_map_rom(pdev, &size);
		अगर (!bios)
			वापस -1;

		/* Scour memory looking क्रम the VBT signature */
		क्रम (i = 0; i + 4 < size; i++) अणु
			अगर (!स_भेद(bios + i, "$VBT", 4)) अणु
				vbt = (काष्ठा vbt_header *)(bios + i);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!vbt) अणु
			dev_err(dev->dev, "VBT signature missing\n");
			pci_unmap_rom(pdev, bios);
			वापस -1;
		पूर्ण
		bdb = (काष्ठा bdb_header *)(bios + i + vbt->bdb_offset);
	पूर्ण

	/* Grab useful general dxefinitions */
	parse_general_features(dev_priv, bdb);
	parse_driver_features(dev_priv, bdb);
	parse_lfp_panel_data(dev_priv, bdb);
	parse_sdvo_panel_data(dev_priv, bdb);
	parse_sdvo_device_mapping(dev_priv, bdb);
	parse_device_mapping(dev_priv, bdb);
	parse_backlight_data(dev_priv, bdb);
	parse_edp(dev_priv, bdb);

	अगर (bios)
		pci_unmap_rom(pdev, bios);

	वापस 0;
पूर्ण

/*
 * Destroy and मुक्त VBT data
 */
व्योम psb_पूर्णांकel_destroy_bios(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;

	kमुक्त(dev_priv->sdvo_lvds_vbt_mode);
	kमुक्त(dev_priv->lfp_lvds_vbt_mode);
	kमुक्त(dev_priv->lvds_bl);
पूर्ण
