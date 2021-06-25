<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2006 Intel Corporation
 *
 * Authors:
 *    Eric Anholt <eric@anholt.net>
 */

#अगर_अघोषित _INTEL_BIOS_H_
#घोषणा _INTEL_BIOS_H_

काष्ठा drm_device;

काष्ठा vbt_header अणु
	u8 signature[20];		/**< Always starts with 'VBT$' */
	u16 version;			/**< decimal */
	u16 header_size;		/**< in bytes */
	u16 vbt_size;			/**< in bytes */
	u8 vbt_checksum;
	u8 reserved0;
	u32 bdb_offset;			/**< from beginning of VBT */
	u32 aim_offset[4];		/**< from beginning of VBT */
पूर्ण __packed;


काष्ठा bdb_header अणु
	u8 signature[16];		/**< Always 'BIOS_DATA_BLOCK' */
	u16 version;			/**< decimal */
	u16 header_size;		/**< in bytes */
	u16 bdb_size;			/**< in bytes */
पूर्ण;

/* strictly speaking, this is a "skip" block, but it has पूर्णांकeresting info */
काष्ठा vbios_data अणु
	u8 type; /* 0 == desktop, 1 == mobile */
	u8 relstage;
	u8 chipset;
	u8 lvds_present:1;
	u8 tv_present:1;
	u8 rsvd2:6; /* finish byte */
	u8 rsvd3[4];
	u8 signon[155];
	u8 copyright[61];
	u16 code_segment;
	u8 करोs_boot_mode;
	u8 bandwidth_percent;
	u8 rsvd4; /* popup memory size */
	u8 resize_pci_bios;
	u8 rsvd5; /* is crt alपढ़ोy on ddc2 */
पूर्ण __packed;

/*
 * There are several types of BIOS data blocks (BDBs), each block has
 * an ID and size in the first 3 bytes (ID in first, size in next 2).
 * Known types are listed below.
 */
#घोषणा BDB_GENERAL_FEATURES	  1
#घोषणा BDB_GENERAL_DEFINITIONS	  2
#घोषणा BDB_OLD_TOGGLE_LIST	  3
#घोषणा BDB_MODE_SUPPORT_LIST	  4
#घोषणा BDB_GENERIC_MODE_TABLE	  5
#घोषणा BDB_EXT_MMIO_REGS	  6
#घोषणा BDB_SWF_IO		  7
#घोषणा BDB_SWF_MMIO		  8
#घोषणा BDB_DOT_CLOCK_TABLE	  9
#घोषणा BDB_MODE_REMOVAL_TABLE	 10
#घोषणा BDB_CHILD_DEVICE_TABLE	 11
#घोषणा BDB_DRIVER_FEATURES	 12
#घोषणा BDB_DRIVER_PERSISTENCE	 13
#घोषणा BDB_EXT_TABLE_PTRS	 14
#घोषणा BDB_DOT_CLOCK_OVERRIDE	 15
#घोषणा BDB_DISPLAY_SELECT	 16
/* 17 rsvd */
#घोषणा BDB_DRIVER_ROTATION	 18
#घोषणा BDB_DISPLAY_REMOVE	 19
#घोषणा BDB_OEM_CUSTOM		 20
#घोषणा BDB_EFP_LIST		 21 /* workarounds क्रम VGA hsync/vsync */
#घोषणा BDB_SDVO_LVDS_OPTIONS	 22
#घोषणा BDB_SDVO_PANEL_DTDS	 23
#घोषणा BDB_SDVO_LVDS_PNP_IDS	 24
#घोषणा BDB_SDVO_LVDS_POWER_SEQ	 25
#घोषणा BDB_TV_OPTIONS		 26
#घोषणा BDB_EDP			 27
#घोषणा BDB_LVDS_OPTIONS	 40
#घोषणा BDB_LVDS_LFP_DATA_PTRS	 41
#घोषणा BDB_LVDS_LFP_DATA	 42
#घोषणा BDB_LVDS_BACKLIGHT	 43
#घोषणा BDB_LVDS_POWER		 44
#घोषणा BDB_SKIP		254 /* VBIOS निजी block, ignore */

काष्ठा bdb_general_features अणु
	/* bits 1 */
	u8 panel_fitting:2;
	u8 flexaim:1;
	u8 msg_enable:1;
	u8 clear_screen:3;
	u8 color_flip:1;

	/* bits 2 */
	u8 करोwnload_ext_vbt:1;
	u8 enable_ssc:1;
	u8 ssc_freq:1;
	u8 enable_lfp_on_override:1;
	u8 disable_ssc_ddt:1;
	u8 rsvd8:3; /* finish byte */

	/* bits 3 */
	u8 disable_smooth_vision:1;
	u8 single_dvi:1;
	u8 rsvd9:6; /* finish byte */

	/* bits 4 */
	u8 legacy_monitor_detect;

	/* bits 5 */
	u8 पूर्णांक_crt_support:1;
	u8 पूर्णांक_tv_support:1;
	u8 पूर्णांक_efp_support:1;
	u8 dp_ssc_enb:1;	/* PCH attached eDP supports SSC */
	u8 dp_ssc_freq:1;	/* SSC freq क्रम PCH attached eDP */
	u8 rsvd11:3; /* finish byte */
पूर्ण __packed;

/* pre-915 */
#घोषणा GPIO_PIN_DVI_LVDS	0x03 /* "DVI/LVDS DDC GPIO pins" */
#घोषणा GPIO_PIN_ADD_I2C	0x05 /* "ADDCARD I2C GPIO pins" */
#घोषणा GPIO_PIN_ADD_DDC	0x04 /* "ADDCARD DDC GPIO pins" */
#घोषणा GPIO_PIN_ADD_DDC_I2C	0x06 /* "ADDCARD DDC/I2C GPIO pins" */

/* Pre 915 */
#घोषणा DEVICE_TYPE_NONE	0x00
#घोषणा DEVICE_TYPE_CRT		0x01
#घोषणा DEVICE_TYPE_TV		0x09
#घोषणा DEVICE_TYPE_EFP		0x12
#घोषणा DEVICE_TYPE_LFP		0x22
/* On 915+ */
#घोषणा DEVICE_TYPE_CRT_DPMS		0x6001
#घोषणा DEVICE_TYPE_CRT_DPMS_HOTPLUG	0x4001
#घोषणा DEVICE_TYPE_TV_COMPOSITE	0x0209
#घोषणा DEVICE_TYPE_TV_MACROVISION	0x0289
#घोषणा DEVICE_TYPE_TV_RF_COMPOSITE	0x020c
#घोषणा DEVICE_TYPE_TV_SVIDEO_COMPOSITE	0x0609
#घोषणा DEVICE_TYPE_TV_SCART		0x0209
#घोषणा DEVICE_TYPE_TV_CODEC_HOTPLUG_PWR 0x6009
#घोषणा DEVICE_TYPE_EFP_HOTPLUG_PWR	0x6012
#घोषणा DEVICE_TYPE_EFP_DVI_HOTPLUG_PWR	0x6052
#घोषणा DEVICE_TYPE_EFP_DVI_I		0x6053
#घोषणा DEVICE_TYPE_EFP_DVI_D_DUAL	0x6152
#घोषणा DEVICE_TYPE_EFP_DVI_D_HDCP	0x60d2
#घोषणा DEVICE_TYPE_OPENLDI_HOTPLUG_PWR	0x6062
#घोषणा DEVICE_TYPE_OPENLDI_DUALPIX	0x6162
#घोषणा DEVICE_TYPE_LFP_PANELLINK	0x5012
#घोषणा DEVICE_TYPE_LFP_CMOS_PWR	0x5042
#घोषणा DEVICE_TYPE_LFP_LVDS_PWR	0x5062
#घोषणा DEVICE_TYPE_LFP_LVDS_DUAL	0x5162
#घोषणा DEVICE_TYPE_LFP_LVDS_DUAL_HDCP	0x51e2

#घोषणा DEVICE_CFG_NONE		0x00
#घोषणा DEVICE_CFG_12BIT_DVOB	0x01
#घोषणा DEVICE_CFG_12BIT_DVOC	0x02
#घोषणा DEVICE_CFG_24BIT_DVOBC	0x09
#घोषणा DEVICE_CFG_24BIT_DVOCB	0x0a
#घोषणा DEVICE_CFG_DUAL_DVOB	0x11
#घोषणा DEVICE_CFG_DUAL_DVOC	0x12
#घोषणा DEVICE_CFG_DUAL_DVOBC	0x13
#घोषणा DEVICE_CFG_DUAL_LINK_DVOBC	0x19
#घोषणा DEVICE_CFG_DUAL_LINK_DVOCB	0x1a

#घोषणा DEVICE_WIRE_NONE	0x00
#घोषणा DEVICE_WIRE_DVOB	0x01
#घोषणा DEVICE_WIRE_DVOC	0x02
#घोषणा DEVICE_WIRE_DVOBC	0x03
#घोषणा DEVICE_WIRE_DVOBB	0x05
#घोषणा DEVICE_WIRE_DVOCC	0x06
#घोषणा DEVICE_WIRE_DVOB_MASTER 0x0d
#घोषणा DEVICE_WIRE_DVOC_MASTER 0x0e

#घोषणा DEVICE_PORT_DVOA	0x00 /* none on 845+ */
#घोषणा DEVICE_PORT_DVOB	0x01
#घोषणा DEVICE_PORT_DVOC	0x02

काष्ठा child_device_config अणु
	u16 handle;
	u16 device_type;
	u8  device_id[10]; /* ascii string */
	u16 addin_offset;
	u8  dvo_port; /* See Device_PORT_* above */
	u8  i2c_pin;
	u8  slave_addr;
	u8  ddc_pin;
	u16 edid_ptr;
	u8  dvo_cfg; /* See DEVICE_CFG_* above */
	u8  dvo2_port;
	u8  i2c2_pin;
	u8  slave2_addr;
	u8  ddc2_pin;
	u8  capabilities;
	u8  dvo_wiring;/* See DEVICE_WIRE_* above */
	u8  dvo2_wiring;
	u16 extended_type;
	u8  dvo_function;
पूर्ण __packed;


काष्ठा bdb_general_definitions अणु
	/* DDC GPIO */
	u8 crt_ddc_gmbus_pin;

	/* DPMS bits */
	u8 dpms_acpi:1;
	u8 skip_boot_crt_detect:1;
	u8 dpms_aim:1;
	u8 rsvd1:5; /* finish byte */

	/* boot device bits */
	u8 boot_display[2];
	u8 child_dev_size;

	/*
	 * Device info:
	 * If TV is present, it'll be at devices[0].
	 * LVDS will be next, either devices[0] or [1], अगर present.
	 * On some platक्रमms the number of device is 6. But could be as few as
	 * 4 अगर both TV and LVDS are missing.
	 * And the device num is related with the size of general definition
	 * block. It is obtained by using the following क्रमmula:
	 * number = (block_size - माप(bdb_general_definitions))/
	 *	     माप(child_device_config);
	 */
	काष्ठा child_device_config devices[];
पूर्ण;

काष्ठा bdb_lvds_options अणु
	u8 panel_type;
	u8 rsvd1;
	/* LVDS capabilities, stored in a dword */
	u8 pfit_mode:2;
	u8 pfit_text_mode_enhanced:1;
	u8 pfit_gfx_mode_enhanced:1;
	u8 pfit_ratio_स्वतः:1;
	u8 pixel_dither:1;
	u8 lvds_edid:1;
	u8 rsvd2:1;
	u8 rsvd4;
पूर्ण __packed;

काष्ठा bdb_lvds_backlight अणु
	u8 type:2;
	u8 pol:1;
	u8 gpio:3;
	u8 gmbus:2;
	u16 freq;
	u8 minbrightness;
	u8 i2caddr;
	u8 brightnesscmd;
	/*FIXME: more...*/
पूर्ण __packed;

/* LFP poपूर्णांकer table contains entries to the काष्ठा below */
काष्ठा bdb_lvds_lfp_data_ptr अणु
	u16 fp_timing_offset; /* offsets are from start of bdb */
	u8 fp_table_size;
	u16 dvo_timing_offset;
	u8 dvo_table_size;
	u16 panel_pnp_id_offset;
	u8 pnp_table_size;
पूर्ण __packed;

काष्ठा bdb_lvds_lfp_data_ptrs अणु
	u8 lvds_entries; /* followed by one or more lvds_data_ptr काष्ठाs */
	काष्ठा bdb_lvds_lfp_data_ptr ptr[16];
पूर्ण __packed;

/* LFP data has 3 blocks per entry */
काष्ठा lvds_fp_timing अणु
	u16 x_res;
	u16 y_res;
	u32 lvds_reg;
	u32 lvds_reg_val;
	u32 pp_on_reg;
	u32 pp_on_reg_val;
	u32 pp_off_reg;
	u32 pp_off_reg_val;
	u32 pp_cycle_reg;
	u32 pp_cycle_reg_val;
	u32 pfit_reg;
	u32 pfit_reg_val;
	u16 terminator;
पूर्ण __packed;

काष्ठा lvds_dvo_timing अणु
	u16 घड़ी;		/**< In 10khz */
	u8 hactive_lo;
	u8 hblank_lo;
	u8 hblank_hi:4;
	u8 hactive_hi:4;
	u8 vactive_lo;
	u8 vblank_lo;
	u8 vblank_hi:4;
	u8 vactive_hi:4;
	u8 hsync_off_lo;
	u8 hsync_pulse_width;
	u8 vsync_pulse_width:4;
	u8 vsync_off:4;
	u8 rsvd0:6;
	u8 hsync_off_hi:2;
	u8 h_image;
	u8 v_image;
	u8 max_hv;
	u8 h_border;
	u8 v_border;
	u8 rsvd1:3;
	u8 digital:2;
	u8 vsync_positive:1;
	u8 hsync_positive:1;
	u8 rsvd2:1;
पूर्ण __packed;

काष्ठा lvds_pnp_id अणु
	u16 mfg_name;
	u16 product_code;
	u32 serial;
	u8 mfg_week;
	u8 mfg_year;
पूर्ण __packed;

काष्ठा bdb_lvds_lfp_data_entry अणु
	काष्ठा lvds_fp_timing fp_timing;
	काष्ठा lvds_dvo_timing dvo_timing;
	काष्ठा lvds_pnp_id pnp_id;
पूर्ण __packed;

काष्ठा bdb_lvds_lfp_data अणु
	काष्ठा bdb_lvds_lfp_data_entry data[16];
पूर्ण __packed;

काष्ठा aimdb_header अणु
	अक्षर signature[16];
	अक्षर oem_device[20];
	u16 aimdb_version;
	u16 aimdb_header_size;
	u16 aimdb_size;
पूर्ण __packed;

काष्ठा aimdb_block अणु
	u8 aimdb_id;
	u16 aimdb_size;
पूर्ण __packed;

काष्ठा vch_panel_data अणु
	u16 fp_timing_offset;
	u8 fp_timing_size;
	u16 dvo_timing_offset;
	u8 dvo_timing_size;
	u16 text_fitting_offset;
	u8 text_fitting_size;
	u16 graphics_fitting_offset;
	u8 graphics_fitting_size;
पूर्ण __packed;

काष्ठा vch_bdb_22 अणु
	काष्ठा aimdb_block aimdb_block;
	काष्ठा vch_panel_data panels[16];
पूर्ण __packed;

काष्ठा bdb_sdvo_lvds_options अणु
	u8 panel_backlight;
	u8 h40_set_panel_type;
	u8 panel_type;
	u8 ssc_clk_freq;
	u16 als_low_trip;
	u16 als_high_trip;
	u8 sclalarcoeff_tab_row_num;
	u8 sclalarcoeff_tab_row_size;
	u8 coefficient[8];
	u8 panel_misc_bits_1;
	u8 panel_misc_bits_2;
	u8 panel_misc_bits_3;
	u8 panel_misc_bits_4;
पूर्ण __packed;

#घोषणा BDB_DRIVER_FEATURE_NO_LVDS		0
#घोषणा BDB_DRIVER_FEATURE_INT_LVDS		1
#घोषणा BDB_DRIVER_FEATURE_SDVO_LVDS		2
#घोषणा BDB_DRIVER_FEATURE_EDP			3

काष्ठा bdb_driver_features अणु
	u8 boot_dev_algorithm:1;
	u8 block_display_चयन:1;
	u8 allow_display_चयन:1;
	u8 hotplug_dvo:1;
	u8 dual_view_zoom:1;
	u8 पूर्णांक15h_hook:1;
	u8 sprite_in_clone:1;
	u8 primary_lfp_id:1;

	u16 boot_mode_x;
	u16 boot_mode_y;
	u8 boot_mode_bpp;
	u8 boot_mode_refresh;

	u16 enable_lfp_primary:1;
	u16 selective_mode_pruning:1;
	u16 dual_frequency:1;
	u16 render_घड़ी_freq:1; /* 0: high freq; 1: low freq */
	u16 nt_clone_support:1;
	u16 घातer_scheme_ui:1; /* 0: CUI; 1: 3rd party */
	u16 sprite_display_assign:1; /* 0: secondary; 1: primary */
	u16 cui_aspect_scaling:1;
	u16 preserve_aspect_ratio:1;
	u16 sdvo_device_घातer_करोwn:1;
	u16 crt_hotplug:1;
	u16 lvds_config:2;
	u16 tv_hotplug:1;
	u16 hdmi_config:2;

	u8 अटल_display:1;
	u8 reserved2:7;
	u16 legacy_crt_max_x;
	u16 legacy_crt_max_y;
	u8 legacy_crt_max_refresh;

	u8 hdmi_termination;
	u8 custom_vbt_version;
पूर्ण __packed;

#घोषणा EDP_18BPP	0
#घोषणा EDP_24BPP	1
#घोषणा EDP_30BPP	2
#घोषणा EDP_RATE_1_62	0
#घोषणा EDP_RATE_2_7	1
#घोषणा EDP_LANE_1	0
#घोषणा EDP_LANE_2	1
#घोषणा EDP_LANE_4	3
#घोषणा EDP_PREEMPHASIS_NONE	0
#घोषणा EDP_PREEMPHASIS_3_5dB	1
#घोषणा EDP_PREEMPHASIS_6dB	2
#घोषणा EDP_PREEMPHASIS_9_5dB	3
#घोषणा EDP_VSWING_0_4V		0
#घोषणा EDP_VSWING_0_6V		1
#घोषणा EDP_VSWING_0_8V		2
#घोषणा EDP_VSWING_1_2V		3

काष्ठा edp_घातer_seq अणु
	u16 t1_t3;
	u16 t8;
	u16 t9;
	u16 t10;
	u16 t11_t12;
पूर्ण __attribute__ ((packed));

काष्ठा edp_link_params अणु
	u8 rate:4;
	u8 lanes:4;
	u8 preemphasis:4;
	u8 vswing:4;
पूर्ण __attribute__ ((packed));

काष्ठा bdb_edp अणु
	काष्ठा edp_घातer_seq घातer_seqs[16];
	u32 color_depth;
	u32 sdrrs_msa_timing_delay;
	काष्ठा edp_link_params link_params[16];
पूर्ण __attribute__ ((packed));

बाह्य पूर्णांक psb_पूर्णांकel_init_bios(काष्ठा drm_device *dev);
बाह्य व्योम psb_पूर्णांकel_destroy_bios(काष्ठा drm_device *dev);

/*
 * Driver<->VBIOS पूर्णांकeraction occurs through scratch bits in
 * GR18 & SWF*.
 */

/* GR18 bits are set on display चयन and hotkey events */
#घोषणा GR18_DRIVER_SWITCH_EN	(1<<7) /* 0: VBIOS control, 1: driver control */
#घोषणा GR18_HOTKEY_MASK	0x78 /* See also SWF4 15:0 */
#घोषणा   GR18_HK_NONE		(0x0<<3)
#घोषणा   GR18_HK_LFP_STRETCH	(0x1<<3)
#घोषणा   GR18_HK_TOGGLE_DISP	(0x2<<3)
#घोषणा   GR18_HK_DISP_SWITCH	(0x4<<3) /* see SWF14 15:0 क्रम what to enable */
#घोषणा   GR18_HK_POPUP_DISABLED (0x6<<3)
#घोषणा   GR18_HK_POPUP_ENABLED	(0x7<<3)
#घोषणा   GR18_HK_PFIT		(0x8<<3)
#घोषणा   GR18_HK_APM_CHANGE	(0xa<<3)
#घोषणा   GR18_HK_MULTIPLE	(0xc<<3)
#घोषणा GR18_USER_INT_EN	(1<<2)
#घोषणा GR18_A0000_FLUSH_EN	(1<<1)
#घोषणा GR18_SMM_EN		(1<<0)

/* Set by driver, cleared by VBIOS */
#घोषणा SWF00_YRES_SHIFT	16
#घोषणा SWF00_XRES_SHIFT	0
#घोषणा SWF00_RES_MASK		0xffff

/* Set by VBIOS at boot समय and driver at runसमय */
#घोषणा SWF01_TV2_FORMAT_SHIFT	8
#घोषणा SWF01_TV1_FORMAT_SHIFT	0
#घोषणा SWF01_TV_FORMAT_MASK	0xffff

#घोषणा SWF10_VBIOS_BLC_I2C_EN	(1<<29)
#घोषणा SWF10_GTT_OVERRIDE_EN	(1<<28)
#घोषणा SWF10_LFP_DPMS_OVR	(1<<27) /* override DPMS on display चयन */
#घोषणा SWF10_ACTIVE_TOGGLE_LIST_MASK (7<<24)
#घोषणा   SWF10_OLD_TOGGLE	0x0
#घोषणा   SWF10_TOGGLE_LIST_1	0x1
#घोषणा   SWF10_TOGGLE_LIST_2	0x2
#घोषणा   SWF10_TOGGLE_LIST_3	0x3
#घोषणा   SWF10_TOGGLE_LIST_4	0x4
#घोषणा SWF10_PANNING_EN	(1<<23)
#घोषणा SWF10_DRIVER_LOADED	(1<<22)
#घोषणा SWF10_EXTENDED_DESKTOP	(1<<21)
#घोषणा SWF10_EXCLUSIVE_MODE	(1<<20)
#घोषणा SWF10_OVERLAY_EN	(1<<19)
#घोषणा SWF10_PLANEB_HOLDOFF	(1<<18)
#घोषणा SWF10_PLANEA_HOLDOFF	(1<<17)
#घोषणा SWF10_VGA_HOLDOFF	(1<<16)
#घोषणा SWF10_ACTIVE_DISP_MASK	0xffff
#घोषणा   SWF10_PIPEB_LFP2	(1<<15)
#घोषणा   SWF10_PIPEB_EFP2	(1<<14)
#घोषणा   SWF10_PIPEB_TV2	(1<<13)
#घोषणा   SWF10_PIPEB_CRT2	(1<<12)
#घोषणा   SWF10_PIPEB_LFP	(1<<11)
#घोषणा   SWF10_PIPEB_EFP	(1<<10)
#घोषणा   SWF10_PIPEB_TV	(1<<9)
#घोषणा   SWF10_PIPEB_CRT	(1<<8)
#घोषणा   SWF10_PIPEA_LFP2	(1<<7)
#घोषणा   SWF10_PIPEA_EFP2	(1<<6)
#घोषणा   SWF10_PIPEA_TV2	(1<<5)
#घोषणा   SWF10_PIPEA_CRT2	(1<<4)
#घोषणा   SWF10_PIPEA_LFP	(1<<3)
#घोषणा   SWF10_PIPEA_EFP	(1<<2)
#घोषणा   SWF10_PIPEA_TV	(1<<1)
#घोषणा   SWF10_PIPEA_CRT	(1<<0)

#घोषणा SWF11_MEMORY_SIZE_SHIFT	16
#घोषणा SWF11_SV_TEST_EN	(1<<15)
#घोषणा SWF11_IS_AGP		(1<<14)
#घोषणा SWF11_DISPLAY_HOLDOFF	(1<<13)
#घोषणा SWF11_DPMS_REDUCED	(1<<12)
#घोषणा SWF11_IS_VBE_MODE	(1<<11)
#घोषणा SWF11_PIPEB_ACCESS	(1<<10) /* 0 here means pipe a */
#घोषणा SWF11_DPMS_MASK		0x07
#घोषणा   SWF11_DPMS_OFF	(1<<2)
#घोषणा   SWF11_DPMS_SUSPEND	(1<<1)
#घोषणा   SWF11_DPMS_STANDBY	(1<<0)
#घोषणा   SWF11_DPMS_ON		0

#घोषणा SWF14_GFX_PFIT_EN	(1<<31)
#घोषणा SWF14_TEXT_PFIT_EN	(1<<30)
#घोषणा SWF14_LID_STATUS_CLOSED	(1<<29) /* 0 here means खोलो */
#घोषणा SWF14_POPUP_EN		(1<<28)
#घोषणा SWF14_DISPLAY_HOLDOFF	(1<<27)
#घोषणा SWF14_DISP_DETECT_EN	(1<<26)
#घोषणा SWF14_DOCKING_STATUS_DOCKED (1<<25) /* 0 here means unकरोcked */
#घोषणा SWF14_DRIVER_STATUS	(1<<24)
#घोषणा SWF14_OS_TYPE_WIN9X	(1<<23)
#घोषणा SWF14_OS_TYPE_WINNT	(1<<22)
/* 21:19 rsvd */
#घोषणा SWF14_PM_TYPE_MASK	0x00070000
#घोषणा   SWF14_PM_ACPI_VIDEO	(0x4 << 16)
#घोषणा   SWF14_PM_ACPI		(0x3 << 16)
#घोषणा   SWF14_PM_APM_12	(0x2 << 16)
#घोषणा   SWF14_PM_APM_11	(0x1 << 16)
#घोषणा SWF14_HK_REQUEST_MASK	0x0000ffff /* see GR18 6:3 क्रम event type */
	  /* अगर GR18 indicates a display चयन */
#घोषणा   SWF14_DS_PIPEB_LFP2_EN (1<<15)
#घोषणा   SWF14_DS_PIPEB_EFP2_EN (1<<14)
#घोषणा   SWF14_DS_PIPEB_TV2_EN  (1<<13)
#घोषणा   SWF14_DS_PIPEB_CRT2_EN (1<<12)
#घोषणा   SWF14_DS_PIPEB_LFP_EN  (1<<11)
#घोषणा   SWF14_DS_PIPEB_EFP_EN  (1<<10)
#घोषणा   SWF14_DS_PIPEB_TV_EN	 (1<<9)
#घोषणा   SWF14_DS_PIPEB_CRT_EN  (1<<8)
#घोषणा   SWF14_DS_PIPEA_LFP2_EN (1<<7)
#घोषणा   SWF14_DS_PIPEA_EFP2_EN (1<<6)
#घोषणा   SWF14_DS_PIPEA_TV2_EN  (1<<5)
#घोषणा   SWF14_DS_PIPEA_CRT2_EN (1<<4)
#घोषणा   SWF14_DS_PIPEA_LFP_EN  (1<<3)
#घोषणा   SWF14_DS_PIPEA_EFP_EN  (1<<2)
#घोषणा   SWF14_DS_PIPEA_TV_EN	 (1<<1)
#घोषणा   SWF14_DS_PIPEA_CRT_EN  (1<<0)
	  /* अगर GR18 indicates a panel fitting request */
#घोषणा   SWF14_PFIT_EN		(1<<0) /* 0 means disable */
	  /* अगर GR18 indicates an APM change request */
#घोषणा   SWF14_APM_HIBERNATE	0x4
#घोषणा   SWF14_APM_SUSPEND	0x3
#घोषणा   SWF14_APM_STANDBY	0x1
#घोषणा   SWF14_APM_RESTORE	0x0

/* Add the device class क्रम LFP, TV, HDMI */
#घोषणा	 DEVICE_TYPE_INT_LFP	0x1022
#घोषणा	 DEVICE_TYPE_INT_TV	0x1009
#घोषणा	 DEVICE_TYPE_HDMI	0x60D2
#घोषणा	 DEVICE_TYPE_DP		0x68C6
#घोषणा	 DEVICE_TYPE_eDP	0x78C6

/* define the DVO port क्रम HDMI output type */
#घोषणा		DVO_B		1
#घोषणा		DVO_C		2
#घोषणा		DVO_D		3

/* define the PORT क्रम DP output type */
#घोषणा		PORT_IDPB	7
#घोषणा		PORT_IDPC	8
#घोषणा		PORT_IDPD	9

#पूर्ण_अगर /* _INTEL_BIOS_H_ */
