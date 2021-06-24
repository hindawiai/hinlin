<शैली गुरु>
/*
 * Copyright तऊ 2006-2016 Intel Corporation
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

/*
 * This inक्रमmation is निजी to VBT parsing in पूर्णांकel_bios.c.
 *
 * Please करो NOT include anywhere अन्यथा.
 */
#अगर_अघोषित _INTEL_BIOS_PRIVATE
#त्रुटि "intel_vbt_defs.h is private to intel_bios.c"
#पूर्ण_अगर

#अगर_अघोषित _INTEL_VBT_DEFS_H_
#घोषणा _INTEL_VBT_DEFS_H_

#समावेश "intel_bios.h"

/**
 * काष्ठा vbt_header - VBT Header काष्ठाure
 * @signature:		VBT signature, always starts with "$VBT"
 * @version:		Version of this काष्ठाure
 * @header_size:	Size of this काष्ठाure
 * @vbt_size:		Size of VBT (VBT Header, BDB Header and data blocks)
 * @vbt_checksum:	Checksum
 * @reserved0:		Reserved
 * @bdb_offset:		Offset of &काष्ठा bdb_header from beginning of VBT
 * @aim_offset:		Offsets of add-in data blocks from beginning of VBT
 */
काष्ठा vbt_header अणु
	u8 signature[20];
	u16 version;
	u16 header_size;
	u16 vbt_size;
	u8 vbt_checksum;
	u8 reserved0;
	u32 bdb_offset;
	u32 aim_offset[4];
पूर्ण __packed;

/**
 * काष्ठा bdb_header - BDB Header काष्ठाure
 * @signature:		BDB signature "BIOS_DATA_BLOCK"
 * @version:		Version of the data block definitions
 * @header_size:	Size of this काष्ठाure
 * @bdb_size:		Size of BDB (BDB Header and data blocks)
 */
काष्ठा bdb_header अणु
	u8 signature[16];
	u16 version;
	u16 header_size;
	u16 bdb_size;
पूर्ण __packed;

/*
 * There are several types of BIOS data blocks (BDBs), each block has
 * an ID and size in the first 3 bytes (ID in first, size in next 2).
 * Known types are listed below.
 */
क्रमागत bdb_block_id अणु
	BDB_GENERAL_FEATURES		= 1,
	BDB_GENERAL_DEFINITIONS		= 2,
	BDB_OLD_TOGGLE_LIST		= 3,
	BDB_MODE_SUPPORT_LIST		= 4,
	BDB_GENERIC_MODE_TABLE		= 5,
	BDB_EXT_MMIO_REGS		= 6,
	BDB_SWF_IO			= 7,
	BDB_SWF_MMIO			= 8,
	BDB_PSR				= 9,
	BDB_MODE_REMOVAL_TABLE		= 10,
	BDB_CHILD_DEVICE_TABLE		= 11,
	BDB_DRIVER_FEATURES		= 12,
	BDB_DRIVER_PERSISTENCE		= 13,
	BDB_EXT_TABLE_PTRS		= 14,
	BDB_DOT_CLOCK_OVERRIDE		= 15,
	BDB_DISPLAY_SELECT		= 16,
	BDB_DRIVER_ROTATION		= 18,
	BDB_DISPLAY_REMOVE		= 19,
	BDB_OEM_CUSTOM			= 20,
	BDB_EFP_LIST			= 21, /* workarounds क्रम VGA hsync/vsync */
	BDB_SDVO_LVDS_OPTIONS		= 22,
	BDB_SDVO_PANEL_DTDS		= 23,
	BDB_SDVO_LVDS_PNP_IDS		= 24,
	BDB_SDVO_LVDS_POWER_SEQ		= 25,
	BDB_TV_OPTIONS			= 26,
	BDB_EDP				= 27,
	BDB_LVDS_OPTIONS		= 40,
	BDB_LVDS_LFP_DATA_PTRS		= 41,
	BDB_LVDS_LFP_DATA		= 42,
	BDB_LVDS_BACKLIGHT		= 43,
	BDB_LFP_POWER			= 44,
	BDB_MIPI_CONFIG			= 52,
	BDB_MIPI_SEQUENCE		= 53,
	BDB_COMPRESSION_PARAMETERS	= 56,
	BDB_GENERIC_DTD			= 58,
	BDB_SKIP			= 254, /* VBIOS निजी block, ignore */
पूर्ण;

/*
 * Block 1 - General Bit Definitions
 */

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
	u8 underscan_vga_timings:1;
	u8 display_घड़ी_mode:1;
	u8 vbios_hotplug_support:1;

        /* bits 3 */
	u8 disable_smooth_vision:1;
	u8 single_dvi:1;
	u8 rotate_180:1;					/* 181 */
	u8 fdi_rx_polarity_inverted:1;
	u8 vbios_extended_mode:1;				/* 160 */
	u8 copy_ilfp_dtd_to_sdvo_lvds_dtd:1;			/* 160 */
	u8 panel_best_fit_timing:1;				/* 160 */
	u8 ignore_strap_state:1;				/* 160 */

        /* bits 4 */
	u8 legacy_monitor_detect;

        /* bits 5 */
	u8 पूर्णांक_crt_support:1;
	u8 पूर्णांक_tv_support:1;
	u8 पूर्णांक_efp_support:1;
	u8 dp_ssc_enable:1;	/* PCH attached eDP supports SSC */
	u8 dp_ssc_freq:1;	/* SSC freq क्रम PCH attached eDP */
	u8 dp_ssc_करोngle_supported:1;
	u8 rsvd11:2; /* finish byte */
पूर्ण __packed;

/*
 * Block 2 - General Bytes Definition
 */

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

/* Add the device class क्रम LFP, TV, HDMI */
#घोषणा DEVICE_TYPE_INT_LFP		0x1022
#घोषणा DEVICE_TYPE_INT_TV		0x1009
#घोषणा DEVICE_TYPE_HDMI		0x60D2
#घोषणा DEVICE_TYPE_DP			0x68C6
#घोषणा DEVICE_TYPE_DP_DUAL_MODE	0x60D6
#घोषणा DEVICE_TYPE_eDP			0x78C6

#घोषणा DEVICE_TYPE_CLASS_EXTENSION	(1 << 15)
#घोषणा DEVICE_TYPE_POWER_MANAGEMENT	(1 << 14)
#घोषणा DEVICE_TYPE_HOTPLUG_SIGNALING	(1 << 13)
#घोषणा DEVICE_TYPE_INTERNAL_CONNECTOR	(1 << 12)
#घोषणा DEVICE_TYPE_NOT_HDMI_OUTPUT	(1 << 11)
#घोषणा DEVICE_TYPE_MIPI_OUTPUT		(1 << 10)
#घोषणा DEVICE_TYPE_COMPOSITE_OUTPUT	(1 << 9)
#घोषणा DEVICE_TYPE_DUAL_CHANNEL	(1 << 8)
#घोषणा DEVICE_TYPE_HIGH_SPEED_LINK	(1 << 6)
#घोषणा DEVICE_TYPE_LVDS_SIGNALING	(1 << 5)
#घोषणा DEVICE_TYPE_TMDS_DVI_SIGNALING	(1 << 4)
#घोषणा DEVICE_TYPE_VIDEO_SIGNALING	(1 << 3)
#घोषणा DEVICE_TYPE_DISPLAYPORT_OUTPUT	(1 << 2)
#घोषणा DEVICE_TYPE_DIGITAL_OUTPUT	(1 << 1)
#घोषणा DEVICE_TYPE_ANALOG_OUTPUT	(1 << 0)

/*
 * Bits we care about when checking क्रम DEVICE_TYPE_eDP. Depending on the
 * प्रणाली, the other bits may or may not be set क्रम eDP outमाला_दो.
 */
#घोषणा DEVICE_TYPE_eDP_BITS \
	(DEVICE_TYPE_INTERNAL_CONNECTOR |	\
	 DEVICE_TYPE_MIPI_OUTPUT |		\
	 DEVICE_TYPE_COMPOSITE_OUTPUT |		\
	 DEVICE_TYPE_DUAL_CHANNEL |		\
	 DEVICE_TYPE_LVDS_SIGNALING |		\
	 DEVICE_TYPE_TMDS_DVI_SIGNALING |	\
	 DEVICE_TYPE_VIDEO_SIGNALING |		\
	 DEVICE_TYPE_DISPLAYPORT_OUTPUT |	\
	 DEVICE_TYPE_ANALOG_OUTPUT)

#घोषणा DEVICE_TYPE_DP_DUAL_MODE_BITS \
	(DEVICE_TYPE_INTERNAL_CONNECTOR |	\
	 DEVICE_TYPE_MIPI_OUTPUT |		\
	 DEVICE_TYPE_COMPOSITE_OUTPUT |		\
	 DEVICE_TYPE_LVDS_SIGNALING |		\
	 DEVICE_TYPE_TMDS_DVI_SIGNALING |	\
	 DEVICE_TYPE_VIDEO_SIGNALING |		\
	 DEVICE_TYPE_DISPLAYPORT_OUTPUT |	\
	 DEVICE_TYPE_DIGITAL_OUTPUT |		\
	 DEVICE_TYPE_ANALOG_OUTPUT)

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

/* dvo_port pre BDB 155 */
#घोषणा DEVICE_PORT_DVOA	0x00 /* none on 845+ */
#घोषणा DEVICE_PORT_DVOB	0x01
#घोषणा DEVICE_PORT_DVOC	0x02

/* dvo_port BDB 155+ */
#घोषणा DVO_PORT_HDMIA		0
#घोषणा DVO_PORT_HDMIB		1
#घोषणा DVO_PORT_HDMIC		2
#घोषणा DVO_PORT_HDMID		3
#घोषणा DVO_PORT_LVDS		4
#घोषणा DVO_PORT_TV		5
#घोषणा DVO_PORT_CRT		6
#घोषणा DVO_PORT_DPB		7
#घोषणा DVO_PORT_DPC		8
#घोषणा DVO_PORT_DPD		9
#घोषणा DVO_PORT_DPA		10
#घोषणा DVO_PORT_DPE		11				/* 193 */
#घोषणा DVO_PORT_HDMIE		12				/* 193 */
#घोषणा DVO_PORT_DPF		13				/* N/A */
#घोषणा DVO_PORT_HDMIF		14				/* N/A */
#घोषणा DVO_PORT_DPG		15				/* 217 */
#घोषणा DVO_PORT_HDMIG		16				/* 217 */
#घोषणा DVO_PORT_DPH		17				/* 217 */
#घोषणा DVO_PORT_HDMIH		18				/* 217 */
#घोषणा DVO_PORT_DPI		19				/* 217 */
#घोषणा DVO_PORT_HDMII		20				/* 217 */
#घोषणा DVO_PORT_MIPIA		21				/* 171 */
#घोषणा DVO_PORT_MIPIB		22				/* 171 */
#घोषणा DVO_PORT_MIPIC		23				/* 171 */
#घोषणा DVO_PORT_MIPID		24				/* 171 */

#घोषणा HDMI_MAX_DATA_RATE_PLATFORM	0			/* 204 */
#घोषणा HDMI_MAX_DATA_RATE_297		1			/* 204 */
#घोषणा HDMI_MAX_DATA_RATE_165		2			/* 204 */

#घोषणा LEGACY_CHILD_DEVICE_CONFIG_SIZE		33

/* DDC Bus DDI Type 155+ */
क्रमागत vbt_gmbus_ddi अणु
	DDC_BUS_DDI_B = 0x1,
	DDC_BUS_DDI_C,
	DDC_BUS_DDI_D,
	DDC_BUS_DDI_F,
	ICL_DDC_BUS_DDI_A = 0x1,
	ICL_DDC_BUS_DDI_B,
	TGL_DDC_BUS_DDI_C,
	RKL_DDC_BUS_DDI_D = 0x3,
	RKL_DDC_BUS_DDI_E,
	ICL_DDC_BUS_PORT_1 = 0x4,
	ICL_DDC_BUS_PORT_2,
	ICL_DDC_BUS_PORT_3,
	ICL_DDC_BUS_PORT_4,
	TGL_DDC_BUS_PORT_5,
	TGL_DDC_BUS_PORT_6,
	ADLS_DDC_BUS_PORT_TC1 = 0x2,
	ADLS_DDC_BUS_PORT_TC2,
	ADLS_DDC_BUS_PORT_TC3,
	ADLS_DDC_BUS_PORT_TC4
पूर्ण;

#घोषणा DP_AUX_A 0x40
#घोषणा DP_AUX_B 0x10
#घोषणा DP_AUX_C 0x20
#घोषणा DP_AUX_D 0x30
#घोषणा DP_AUX_E 0x50
#घोषणा DP_AUX_F 0x60
#घोषणा DP_AUX_G 0x70
#घोषणा DP_AUX_H 0x80
#घोषणा DP_AUX_I 0x90

/* DP max link rate 216+ */
#घोषणा BDB_216_VBT_DP_MAX_LINK_RATE_HBR3	0
#घोषणा BDB_216_VBT_DP_MAX_LINK_RATE_HBR2	1
#घोषणा BDB_216_VBT_DP_MAX_LINK_RATE_HBR	2
#घोषणा BDB_216_VBT_DP_MAX_LINK_RATE_LBR	3

/* DP max link rate 230+ */
#घोषणा BDB_230_VBT_DP_MAX_LINK_RATE_DEF	0
#घोषणा BDB_230_VBT_DP_MAX_LINK_RATE_LBR	1
#घोषणा BDB_230_VBT_DP_MAX_LINK_RATE_HBR	2
#घोषणा BDB_230_VBT_DP_MAX_LINK_RATE_HBR2	3
#घोषणा BDB_230_VBT_DP_MAX_LINK_RATE_HBR3	4
#घोषणा BDB_230_VBT_DP_MAX_LINK_RATE_UHBR10	5
#घोषणा BDB_230_VBT_DP_MAX_LINK_RATE_UHBR13P5	6
#घोषणा BDB_230_VBT_DP_MAX_LINK_RATE_UHBR20	7

/*
 * The child device config, aka the display device data काष्ठाure, provides a
 * description of a port and its configuration on the platक्रमm.
 *
 * The child device config size has been increased, and fields have been added
 * and their meaning has changed over समय. Care must be taken when accessing
 * basically any of the fields to ensure the correct पूर्णांकerpretation क्रम the BDB
 * version in question.
 *
 * When we copy the child device configs to dev_priv->vbt.child_dev, we reserve
 * space क्रम the full काष्ठाure below, and initialize the tail not actually
 * present in VBT to zeros. Accessing those fields is fine, as दीर्घ as the
 * शेष zero is taken पूर्णांकo account, again according to the BDB version.
 *
 * BDB versions 155 and below are considered legacy, and version 155 seems to be
 * a baseline क्रम some of the VBT करोcumentation. When adding new fields, please
 * include the BDB version when the field was added, अगर it's above that.
 */
काष्ठा child_device_config अणु
	u16 handle;
	u16 device_type; /* See DEVICE_TYPE_* above */

	जोड़ अणु
		u8  device_id[10]; /* ascii string */
		काष्ठा अणु
			u8 i2c_speed;
			u8 dp_onboard_redriver;			/* 158 */
			u8 dp_onकरोck_redriver;			/* 158 */
			u8 hdmi_level_shअगरter_value:5;		/* 169 */
			u8 hdmi_max_data_rate:3;		/* 204 */
			u16 dtd_buf_ptr;			/* 161 */
			u8 edidless_efp:1;			/* 161 */
			u8 compression_enable:1;		/* 198 */
			u8 compression_method_cps:1;		/* 198 */
			u8 ganged_edp:1;			/* 202 */
			u8 reserved0:4;
			u8 compression_काष्ठाure_index:4;	/* 198 */
			u8 reserved1:4;
			u8 slave_port;				/* 202 */
			u8 reserved2;
		पूर्ण __packed;
	पूर्ण __packed;

	u16 addin_offset;
	u8 dvo_port; /* See DEVICE_PORT_* and DVO_PORT_* above */
	u8 i2c_pin;
	u8 slave_addr;
	u8 ddc_pin;
	u16 edid_ptr;
	u8 dvo_cfg; /* See DEVICE_CFG_* above */

	जोड़ अणु
		काष्ठा अणु
			u8 dvo2_port;
			u8 i2c2_pin;
			u8 slave2_addr;
			u8 ddc2_pin;
		पूर्ण __packed;
		काष्ठा अणु
			u8 efp_routed:1;			/* 158 */
			u8 lane_reversal:1;			/* 184 */
			u8 lspcon:1;				/* 192 */
			u8 iboost:1;				/* 196 */
			u8 hpd_invert:1;			/* 196 */
			u8 use_vbt_vswing:1;			/* 218 */
			u8 flag_reserved:2;
			u8 hdmi_support:1;			/* 158 */
			u8 dp_support:1;			/* 158 */
			u8 पंचांगds_support:1;			/* 158 */
			u8 support_reserved:5;
			u8 aux_channel;
			u8 करोngle_detect;
		पूर्ण __packed;
	पूर्ण __packed;

	u8 pipe_cap:2;
	u8 sdvo_stall:1;					/* 158 */
	u8 hpd_status:2;
	u8 पूर्णांकegrated_encoder:1;
	u8 capabilities_reserved:2;
	u8 dvo_wiring; /* See DEVICE_WIRE_* above */

	जोड़ अणु
		u8 dvo2_wiring;
		u8 mipi_bridge_type;				/* 171 */
	पूर्ण __packed;

	u16 extended_type;
	u8 dvo_function;
	u8 dp_usb_type_c:1;					/* 195 */
	u8 tbt:1;						/* 209 */
	u8 flags2_reserved:2;					/* 195 */
	u8 dp_port_trace_length:4;				/* 209 */
	u8 dp_gpio_index;					/* 195 */
	u16 dp_gpio_pin_num;					/* 195 */
	u8 dp_iboost_level:4;					/* 196 */
	u8 hdmi_iboost_level:4;					/* 196 */
	u8 dp_max_link_rate:3;					/* 216/230 CNL+ */
	u8 dp_max_link_rate_reserved:5;				/* 216/230 */
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
	 *	     defs->child_dev_size;
	 */
	u8 devices[];
पूर्ण __packed;

/*
 * Block 9 - SRD Feature Block
 */

काष्ठा psr_table अणु
	/* Feature bits */
	u8 full_link:1;
	u8 require_aux_to_wakeup:1;
	u8 feature_bits_rsvd:6;

	/* Wait बार */
	u8 idle_frames:4;
	u8 lines_to_रुको:3;
	u8 रुको_बार_rsvd:1;

	/* TP wake up समय in multiple of 100 */
	u16 tp1_wakeup_समय;
	u16 tp2_tp3_wakeup_समय;
पूर्ण __packed;

काष्ठा bdb_psr अणु
	काष्ठा psr_table psr_table[16];

	/* PSR2 TP2/TP3 wakeup समय क्रम 16 panels */
	u32 psr2_tp2_tp3_wakeup_समय;
पूर्ण __packed;

/*
 * Block 12 - Driver Features Data Block
 */

#घोषणा BDB_DRIVER_FEATURE_NO_LVDS		0
#घोषणा BDB_DRIVER_FEATURE_INT_LVDS		1
#घोषणा BDB_DRIVER_FEATURE_SDVO_LVDS		2
#घोषणा BDB_DRIVER_FEATURE_INT_SDVO_LVDS	3

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
	/* Driver features data block */
	u16 rmpm_enabled:1;
	u16 s2ddt_enabled:1;
	u16 dpst_enabled:1;
	u16 bltclt_enabled:1;
	u16 adb_enabled:1;
	u16 drrs_enabled:1;
	u16 grs_enabled:1;
	u16 gpmt_enabled:1;
	u16 tbt_enabled:1;
	u16 psr_enabled:1;
	u16 ips_enabled:1;
	u16 reserved3:4;
	u16 pc_feature_valid:1;
पूर्ण __packed;

/*
 * Block 22 - SDVO LVDS General Options
 */

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

/*
 * Block 23 - SDVO LVDS Panel DTDs
 */

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
	u8 hsync_pulse_width_lo;
	u8 vsync_pulse_width_lo:4;
	u8 vsync_off_lo:4;
	u8 vsync_pulse_width_hi:2;
	u8 vsync_off_hi:2;
	u8 hsync_pulse_width_hi:2;
	u8 hsync_off_hi:2;
	u8 himage_lo;
	u8 vimage_lo;
	u8 vimage_hi:4;
	u8 himage_hi:4;
	u8 h_border;
	u8 v_border;
	u8 rsvd1:3;
	u8 digital:2;
	u8 vsync_positive:1;
	u8 hsync_positive:1;
	u8 non_पूर्णांकerlaced:1;
पूर्ण __packed;

काष्ठा bdb_sdvo_panel_dtds अणु
	काष्ठा lvds_dvo_timing dtds[4];
पूर्ण __packed;

/*
 * Block 27 - eDP VBT Block
 */

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


काष्ठा edp_fast_link_params अणु
	u8 rate:4;
	u8 lanes:4;
	u8 preemphasis:4;
	u8 vswing:4;
पूर्ण __packed;

काष्ठा edp_pwm_delays अणु
	u16 pwm_on_to_backlight_enable;
	u16 backlight_disable_to_pwm_off;
पूर्ण __packed;

काष्ठा edp_full_link_params अणु
	u8 preemphasis:4;
	u8 vswing:4;
पूर्ण __packed;

काष्ठा bdb_edp अणु
	काष्ठा edp_घातer_seq घातer_seqs[16];
	u32 color_depth;
	काष्ठा edp_fast_link_params fast_link_params[16];
	u32 sdrrs_msa_timing_delay;

	/* ith bit indicates enabled/disabled क्रम (i+1)th panel */
	u16 edp_s3d_feature;					/* 162 */
	u16 edp_t3_optimization;				/* 165 */
	u64 edp_vswing_preemph;					/* 173 */
	u16 fast_link_training;					/* 182 */
	u16 dpcd_600h_ग_लिखो_required;				/* 185 */
	काष्ठा edp_pwm_delays pwm_delays[16];			/* 186 */
	u16 full_link_params_provided;				/* 199 */
	काष्ठा edp_full_link_params full_link_params[16];	/* 199 */
पूर्ण __packed;

/*
 * Block 40 - LFP Data Block
 */

/* Mask क्रम DRRS / Panel Channel / SSC / BLT control bits extraction */
#घोषणा MODE_MASK		0x3

काष्ठा bdb_lvds_options अणु
	u8 panel_type;
	u8 panel_type2;						/* 212 */
	/* LVDS capabilities, stored in a dword */
	u8 pfit_mode:2;
	u8 pfit_text_mode_enhanced:1;
	u8 pfit_gfx_mode_enhanced:1;
	u8 pfit_ratio_स्वतः:1;
	u8 pixel_dither:1;
	u8 lvds_edid:1;
	u8 rsvd2:1;
	u8 rsvd4;
	/* LVDS Panel channel bits stored here */
	u32 lvds_panel_channel_bits;
	/* LVDS SSC (Spपढ़ो Spectrum Clock) bits stored here. */
	u16 ssc_bits;
	u16 ssc_freq;
	u16 ssc_ddt;
	/* Panel color depth defined here */
	u16 panel_color_depth;
	/* LVDS panel type bits stored here */
	u32 dps_panel_type_bits;
	/* LVDS backlight control type bits stored here */
	u32 blt_control_type_bits;

	u16 lcdvcc_s0_enable;					/* 200 */
	u32 rotation;						/* 228 */
पूर्ण __packed;

/*
 * Block 41 - LFP Data Table Poपूर्णांकers
 */

/* LFP poपूर्णांकer table contains entries to the काष्ठा below */
काष्ठा lvds_lfp_data_ptr अणु
	u16 fp_timing_offset; /* offsets are from start of bdb */
	u8 fp_table_size;
	u16 dvo_timing_offset;
	u8 dvo_table_size;
	u16 panel_pnp_id_offset;
	u8 pnp_table_size;
पूर्ण __packed;

काष्ठा bdb_lvds_lfp_data_ptrs अणु
	u8 lvds_entries; /* followed by one or more lvds_data_ptr काष्ठाs */
	काष्ठा lvds_lfp_data_ptr ptr[16];
पूर्ण __packed;

/*
 * Block 42 - LFP Data Tables
 */

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

काष्ठा lvds_pnp_id अणु
	u16 mfg_name;
	u16 product_code;
	u32 serial;
	u8 mfg_week;
	u8 mfg_year;
पूर्ण __packed;

काष्ठा lvds_lfp_data_entry अणु
	काष्ठा lvds_fp_timing fp_timing;
	काष्ठा lvds_dvo_timing dvo_timing;
	काष्ठा lvds_pnp_id pnp_id;
पूर्ण __packed;

काष्ठा bdb_lvds_lfp_data अणु
	काष्ठा lvds_lfp_data_entry data[16];
पूर्ण __packed;

/*
 * Block 43 - LFP Backlight Control Data Block
 */

#घोषणा BDB_BACKLIGHT_TYPE_NONE	0
#घोषणा BDB_BACKLIGHT_TYPE_PWM	2

काष्ठा lfp_backlight_data_entry अणु
	u8 type:2;
	u8 active_low_pwm:1;
	u8 obsolete1:5;
	u16 pwm_freq_hz;
	u8 min_brightness; /* Obsolete from 234+ */
	u8 obsolete2;
	u8 obsolete3;
पूर्ण __packed;

काष्ठा lfp_backlight_control_method अणु
	u8 type:4;
	u8 controller:4;
पूर्ण __packed;

काष्ठा lfp_brightness_level अणु
	u16 level;
	u16 reserved;
पूर्ण __packed;

काष्ठा bdb_lfp_backlight_data अणु
	u8 entry_size;
	काष्ठा lfp_backlight_data_entry data[16];
	u8 level[16]; /* Obsolete from 234+ */
	काष्ठा lfp_backlight_control_method backlight_control[16];
	काष्ठा lfp_brightness_level brightness_level[16];		/* 234+ */
	काष्ठा lfp_brightness_level brightness_min_level[16];	/* 234+ */
	u8 brightness_precision_bits[16];						/* 236+ */
पूर्ण __packed;

/*
 * Block 44 - LFP Power Conservation Features Block
 */

काष्ठा als_data_entry अणु
	u16 backlight_adjust;
	u16 lux;
पूर्ण __packed;

काष्ठा agressiveness_profile_entry अणु
	u8 dpst_agressiveness : 4;
	u8 lace_agressiveness : 4;
पूर्ण __packed;

काष्ठा bdb_lfp_घातer अणु
	u8 lfp_feature_bits;
	काष्ठा als_data_entry als[5];
	u8 lace_aggressiveness_profile;
	u16 dpst;
	u16 psr;
	u16 drrs;
	u16 lace_support;
	u16 adt;
	u16 dmrrs;
	u16 adb;
	u16 lace_enabled_status;
	काष्ठा agressiveness_profile_entry aggressivenes[16];
	u16 hobl; /* 232+ */
	u16 vrr_feature_enabled; /* 233+ */
पूर्ण __packed;

/*
 * Block 52 - MIPI Configuration Block
 */

#घोषणा MAX_MIPI_CONFIGURATIONS	6

काष्ठा bdb_mipi_config अणु
	काष्ठा mipi_config config[MAX_MIPI_CONFIGURATIONS];
	काष्ठा mipi_pps_data pps[MAX_MIPI_CONFIGURATIONS];
पूर्ण __packed;

/*
 * Block 53 - MIPI Sequence Block
 */

काष्ठा bdb_mipi_sequence अणु
	u8 version;
	u8 data[]; /* up to 6 variable length blocks */
पूर्ण __packed;

/*
 * Block 56 - Compression Parameters
 */

#घोषणा VBT_RC_BUFFER_BLOCK_SIZE_1KB	0
#घोषणा VBT_RC_BUFFER_BLOCK_SIZE_4KB	1
#घोषणा VBT_RC_BUFFER_BLOCK_SIZE_16KB	2
#घोषणा VBT_RC_BUFFER_BLOCK_SIZE_64KB	3

#घोषणा VBT_DSC_LINE_BUFFER_DEPTH(vbt_value)	((vbt_value) + 8) /* bits */
#घोषणा VBT_DSC_MAX_BPP(vbt_value)		(6 + (vbt_value) * 2)

काष्ठा dsc_compression_parameters_entry अणु
	u8 version_major:4;
	u8 version_minor:4;

	u8 rc_buffer_block_size:2;
	u8 reserved1:6;

	/*
	 * Buffer size in bytes:
	 *
	 * 4 ^ rc_buffer_block_size * 1024 * (rc_buffer_size + 1) bytes
	 */
	u8 rc_buffer_size;
	u32 slices_per_line;

	u8 line_buffer_depth:4;
	u8 reserved2:4;

	/* Flag Bits 1 */
	u8 block_prediction_enable:1;
	u8 reserved3:7;

	u8 max_bpp; /* mapping */

	/* Color depth capabilities */
	u8 reserved4:1;
	u8 support_8bpc:1;
	u8 support_10bpc:1;
	u8 support_12bpc:1;
	u8 reserved5:4;

	u16 slice_height;
पूर्ण __packed;

काष्ठा bdb_compression_parameters अणु
	u16 entry_size;
	काष्ठा dsc_compression_parameters_entry data[16];
पूर्ण __packed;

/*
 * Block 58 - Generic DTD Block
 */

काष्ठा generic_dtd_entry अणु
	u32 pixel_घड़ी;
	u16 hactive;
	u16 hblank;
	u16 hfront_porch;
	u16 hsync;
	u16 vactive;
	u16 vblank;
	u16 vfront_porch;
	u16 vsync;
	u16 width_mm;
	u16 height_mm;

	/* Flags */
	u8 rsvd_flags:6;
	u8 vsync_positive_polarity:1;
	u8 hsync_positive_polarity:1;

	u8 rsvd[3];
पूर्ण __packed;

काष्ठा bdb_generic_dtd अणु
	u16 gdtd_size;
	काष्ठा generic_dtd_entry dtd[];	/* up to 24 DTD's */
पूर्ण __packed;

#पूर्ण_अगर /* _INTEL_VBT_DEFS_H_ */
