<शैली गुरु>
/*
 * Copyright (c) 2016 Intel Corporation
 *
 * Permission to use, copy, modअगरy, distribute, and sell this software and its
 * करोcumentation क्रम any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting करोcumentation, and
 * that the name of the copyright holders not be used in advertising or
 * खुलाity pertaining to distribution of the software without specअगरic,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software क्रम any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#अगर_अघोषित __DRM_CONNECTOR_H__
#घोषणा __DRM_CONNECTOR_H__

#समावेश <linux/list.h>
#समावेश <linux/llist.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/hdmi.h>
#समावेश <drm/drm_mode_object.h>
#समावेश <drm/drm_util.h>

#समावेश <uapi/drm/drm_mode.h>

काष्ठा drm_connector_helper_funcs;
काष्ठा drm_modeset_acquire_ctx;
काष्ठा drm_device;
काष्ठा drm_crtc;
काष्ठा drm_encoder;
काष्ठा drm_property;
काष्ठा drm_property_blob;
काष्ठा drm_prपूर्णांकer;
काष्ठा edid;
काष्ठा i2c_adapter;

क्रमागत drm_connector_क्रमce अणु
	DRM_FORCE_UNSPECIFIED,
	DRM_FORCE_OFF,
	DRM_FORCE_ON,         /* क्रमce on analog part normally */
	DRM_FORCE_ON_DIGITAL, /* क्रम DVI-I use digital connector */
पूर्ण;

/**
 * क्रमागत drm_connector_status - status क्रम a &drm_connector
 *
 * This क्रमागत is used to track the connector status. There are no separate
 * #घोषणाs क्रम the uapi!
 */
क्रमागत drm_connector_status अणु
	/**
	 * @connector_status_connected: The connector is definitely connected to
	 * a sink device, and can be enabled.
	 */
	connector_status_connected = 1,
	/**
	 * @connector_status_disconnected: The connector isn't connected to a
	 * sink device which can be स्वतःdetect. For digital outमाला_दो like DP or
	 * HDMI (which can be realiable probed) this means there's really
	 * nothing there. It is driver-dependent whether a connector with this
	 * status can be lit up or not.
	 */
	connector_status_disconnected = 2,
	/**
	 * @connector_status_unknown: The connector's status could not be
	 * reliably detected. This happens when probing would either cause
	 * flicker (like load-detection when the connector is in use), or when a
	 * hardware resource isn't available (like when load-detection needs a
	 * मुक्त CRTC). It should be possible to light up the connector with one
	 * of the listed fallback modes. For शेष configuration userspace
	 * should only try to light up connectors with unknown status when
	 * there's not connector with @connector_status_connected.
	 */
	connector_status_unknown = 3,
पूर्ण;

/**
 * क्रमागत drm_connector_registration_state - userspace registration status क्रम
 * a &drm_connector
 *
 * This क्रमागत is used to track the status of initializing a connector and
 * रेजिस्टरing it with userspace, so that DRM can prevent bogus modesets on
 * connectors that no दीर्घer exist.
 */
क्रमागत drm_connector_registration_state अणु
	/**
	 * @DRM_CONNECTOR_INITIALIZING: The connector has just been created,
	 * but has yet to be exposed to userspace. There should be no
	 * additional restrictions to how the state of this connector may be
	 * modअगरied.
	 */
	DRM_CONNECTOR_INITIALIZING = 0,

	/**
	 * @DRM_CONNECTOR_REGISTERED: The connector has been fully initialized
	 * and रेजिस्टरed with sysfs, as such it has been exposed to
	 * userspace. There should be no additional restrictions to how the
	 * state of this connector may be modअगरied.
	 */
	DRM_CONNECTOR_REGISTERED = 1,

	/**
	 * @DRM_CONNECTOR_UNREGISTERED: The connector has either been exposed
	 * to userspace and has since been unरेजिस्टरed and हटाओd from
	 * userspace, or the connector was unरेजिस्टरed beक्रमe it had a chance
	 * to be exposed to userspace (e.g. still in the
	 * @DRM_CONNECTOR_INITIALIZING state). When a connector is
	 * unरेजिस्टरed, there are additional restrictions to how its state
	 * may be modअगरied:
	 *
	 * - An unरेजिस्टरed connector may only have its DPMS changed from
	 *   On->Off. Once DPMS is changed to Off, it may not be चयनed back
	 *   to On.
	 * - Modesets are not allowed on unरेजिस्टरed connectors, unless they
	 *   would result in disabling its asचिन्हित CRTCs. This means
	 *   disabling a CRTC on an unरेजिस्टरed connector is OK, but enabling
	 *   one is not.
	 * - Removing a CRTC from an unरेजिस्टरed connector is OK, but new
	 *   CRTCs may never be asचिन्हित to an unरेजिस्टरed connector.
	 */
	DRM_CONNECTOR_UNREGISTERED = 2,
पूर्ण;

क्रमागत subpixel_order अणु
	SubPixelUnknown = 0,
	SubPixelHorizontalRGB,
	SubPixelHorizontalBGR,
	SubPixelVerticalRGB,
	SubPixelVerticalBGR,
	SubPixelNone,

पूर्ण;

/**
 * काष्ठा drm_scrambling: sink's scrambling support.
 */
काष्ठा drm_scrambling अणु
	/**
	 * @supported: scrambling supported क्रम rates > 340 Mhz.
	 */
	bool supported;
	/**
	 * @low_rates: scrambling supported क्रम rates <= 340 Mhz.
	 */
	bool low_rates;
पूर्ण;

/*
 * काष्ठा drm_scdc - Inक्रमmation about scdc capabilities of a HDMI 2.0 sink
 *
 * Provides SCDC रेजिस्टर support and capabilities related inक्रमmation on a
 * HDMI 2.0 sink. In हाल of a HDMI 1.4 sink, all parameter must be 0.
 */
काष्ठा drm_scdc अणु
	/**
	 * @supported: status control & data channel present.
	 */
	bool supported;
	/**
	 * @पढ़ो_request: sink is capable of generating scdc पढ़ो request.
	 */
	bool पढ़ो_request;
	/**
	 * @scrambling: sink's scrambling capabilities
	 */
	काष्ठा drm_scrambling scrambling;
पूर्ण;

/**
 * काष्ठा drm_hdmi_dsc_cap - DSC capabilities of HDMI sink
 *
 * Describes the DSC support provided by HDMI 2.1 sink.
 * The inक्रमmation is fetched fom additional HFVSDB blocks defined
 * क्रम HDMI 2.1.
 */
काष्ठा drm_hdmi_dsc_cap अणु
	/** @v_1p2: flag क्रम dsc1.2 version support by sink */
	bool v_1p2;

	/** @native_420: Does sink support DSC with 4:2:0 compression */
	bool native_420;

	/**
	 * @all_bpp: Does sink support all bpp with 4:4:4: or 4:2:2
	 * compressed क्रमmats
	 */
	bool all_bpp;

	/**
	 * @bpc_supported: compressed bpc supported by sink : 10, 12 or 16 bpc
	 */
	u8 bpc_supported;

	/** @max_slices: maximum number of Horizontal slices supported by */
	u8 max_slices;

	/** @clk_per_slice : max pixel घड़ी in MHz supported per slice */
	पूर्णांक clk_per_slice;

	/** @max_lanes : dsc max lanes supported क्रम Fixed rate Link training */
	u8 max_lanes;

	/** @max_frl_rate_per_lane : maximum frl rate with DSC per lane */
	u8 max_frl_rate_per_lane;

	/** @total_chunk_kbytes: max size of chunks in KBs supported per line*/
	u8 total_chunk_kbytes;
पूर्ण;

/**
 * काष्ठा drm_hdmi_info - runसमय inक्रमmation about the connected HDMI sink
 *
 * Describes अगर a given display supports advanced HDMI 2.0 features.
 * This inक्रमmation is available in CEA-861-F extension blocks (like HF-VSDB).
 */
काष्ठा drm_hdmi_info अणु
	/** @scdc: sink's scdc support and capabilities */
	काष्ठा drm_scdc scdc;

	/**
	 * @y420_vdb_modes: biपंचांगap of modes which can support ycbcr420
	 * output only (not normal RGB/YCBCR444/422 outमाला_दो). The max VIC
	 * defined by the CEA-861-G spec is 219, so the size is 256 bits to map
	 * up to 256 VICs.
	 */
	अचिन्हित दीर्घ y420_vdb_modes[BITS_TO_LONGS(256)];

	/**
	 * @y420_cmdb_modes: biपंचांगap of modes which can support ycbcr420
	 * output also, aदीर्घ with normal HDMI outमाला_दो. The max VIC defined by
	 * the CEA-861-G spec is 219, so the size is 256 bits to map up to 256
	 * VICs.
	 */
	अचिन्हित दीर्घ y420_cmdb_modes[BITS_TO_LONGS(256)];

	/** @y420_cmdb_map: biपंचांगap of SVD index, to extraxt vcb modes */
	u64 y420_cmdb_map;

	/** @y420_dc_modes: biपंचांगap of deep color support index */
	u8 y420_dc_modes;

	/** @max_frl_rate_per_lane: support fixed rate link */
	u8 max_frl_rate_per_lane;

	/** @max_lanes: supported by sink */
	u8 max_lanes;

	/** @dsc_cap: DSC capabilities of the sink */
	काष्ठा drm_hdmi_dsc_cap dsc_cap;
पूर्ण;

/**
 * क्रमागत drm_link_status - connector's link_status property value
 *
 * This क्रमागत is used as the connector's link status property value.
 * It is set to the values defined in uapi.
 *
 * @DRM_LINK_STATUS_GOOD: DP Link is Good as a result of successful
 *                        link training
 * @DRM_LINK_STATUS_BAD: DP Link is BAD as a result of link training
 *                       failure
 */
क्रमागत drm_link_status अणु
	DRM_LINK_STATUS_GOOD = DRM_MODE_LINK_STATUS_GOOD,
	DRM_LINK_STATUS_BAD = DRM_MODE_LINK_STATUS_BAD,
पूर्ण;

/**
 * क्रमागत drm_panel_orientation - panel_orientation info क्रम &drm_display_info
 *
 * This क्रमागत is used to track the (LCD) panel orientation. There are no
 * separate #घोषणाs क्रम the uapi!
 *
 * @DRM_MODE_PANEL_ORIENTATION_UNKNOWN: The drm driver has not provided any
 *					panel orientation inक्रमmation (normal
 *					क्रम non panels) in this हाल the "panel
 *					orientation" connector prop will not be
 *					attached.
 * @DRM_MODE_PANEL_ORIENTATION_NORMAL:	The top side of the panel matches the
 *					top side of the device's casing.
 * @DRM_MODE_PANEL_ORIENTATION_BOTTOM_UP: The top side of the panel matches the
 *					bottom side of the device's casing, iow
 *					the panel is mounted upside-करोwn.
 * @DRM_MODE_PANEL_ORIENTATION_LEFT_UP:	The left side of the panel matches the
 *					top side of the device's casing.
 * @DRM_MODE_PANEL_ORIENTATION_RIGHT_UP: The right side of the panel matches the
 *					top side of the device's casing.
 */
क्रमागत drm_panel_orientation अणु
	DRM_MODE_PANEL_ORIENTATION_UNKNOWN = -1,
	DRM_MODE_PANEL_ORIENTATION_NORMAL = 0,
	DRM_MODE_PANEL_ORIENTATION_BOTTOM_UP,
	DRM_MODE_PANEL_ORIENTATION_LEFT_UP,
	DRM_MODE_PANEL_ORIENTATION_RIGHT_UP,
पूर्ण;

/**
 * काष्ठा drm_monitor_range_info - Panel's Monitor range in EDID क्रम
 * &drm_display_info
 *
 * This काष्ठा is used to store a frequency range supported by panel
 * as parsed from EDID's detailed monitor range descriptor block.
 *
 * @min_vfreq: This is the min supported refresh rate in Hz from
 *             EDID's detailed monitor range.
 * @max_vfreq: This is the max supported refresh rate in Hz from
 *             EDID's detailed monitor range
 */
काष्ठा drm_monitor_range_info अणु
	u8 min_vfreq;
	u8 max_vfreq;
पूर्ण;

/*
 * This is a consolidated colorimetry list supported by HDMI and
 * DP protocol standard. The respective connectors will रेजिस्टर
 * a property with the subset of this list (supported by that
 * respective protocol). Userspace will set the colorspace through
 * a colorspace property which will be created and exposed to
 * userspace.
 */

/* For Default हाल, driver will set the colorspace */
#घोषणा DRM_MODE_COLORIMETRY_DEFAULT			0
/* CEA 861 Normal Colorimetry options */
#घोषणा DRM_MODE_COLORIMETRY_NO_DATA			0
#घोषणा DRM_MODE_COLORIMETRY_SMPTE_170M_YCC		1
#घोषणा DRM_MODE_COLORIMETRY_BT709_YCC			2
/* CEA 861 Extended Colorimetry Options */
#घोषणा DRM_MODE_COLORIMETRY_XVYCC_601			3
#घोषणा DRM_MODE_COLORIMETRY_XVYCC_709			4
#घोषणा DRM_MODE_COLORIMETRY_SYCC_601			5
#घोषणा DRM_MODE_COLORIMETRY_OPYCC_601			6
#घोषणा DRM_MODE_COLORIMETRY_OPRGB			7
#घोषणा DRM_MODE_COLORIMETRY_BT2020_CYCC		8
#घोषणा DRM_MODE_COLORIMETRY_BT2020_RGB			9
#घोषणा DRM_MODE_COLORIMETRY_BT2020_YCC			10
/* Additional Colorimetry extension added as part of CTA 861.G */
#घोषणा DRM_MODE_COLORIMETRY_DCI_P3_RGB_D65		11
#घोषणा DRM_MODE_COLORIMETRY_DCI_P3_RGB_THEATER		12
/* Additional Colorimetry Options added क्रम DP 1.4a VSC Colorimetry Format */
#घोषणा DRM_MODE_COLORIMETRY_RGB_WIDE_FIXED		13
#घोषणा DRM_MODE_COLORIMETRY_RGB_WIDE_FLOAT		14
#घोषणा DRM_MODE_COLORIMETRY_BT601_YCC			15

/**
 * क्रमागत drm_bus_flags - bus_flags info क्रम &drm_display_info
 *
 * This क्रमागत defines संकेत polarities and घड़ी edge inक्रमmation क्रम संकेतs on
 * a bus as biपंचांगask flags.
 *
 * The घड़ी edge inक्रमmation is conveyed by two sets of symbols,
 * DRM_BUS_FLAGS_*_DRIVE_\* and DRM_BUS_FLAGS_*_SAMPLE_\*. When this क्रमागत is
 * used to describe a bus from the poपूर्णांक of view of the transmitter, the
 * \*_DRIVE_\* flags should be used. When used from the poपूर्णांक of view of the
 * receiver, the \*_SAMPLE_\* flags should be used. The \*_DRIVE_\* and
 * \*_SAMPLE_\* flags alias each other, with the \*_SAMPLE_POSEDGE and
 * \*_SAMPLE_NEGEDGE flags being equal to \*_DRIVE_NEGEDGE and \*_DRIVE_POSEDGE
 * respectively. This simplअगरies code as संकेतs are usually sampled on the
 * opposite edge of the driving edge. Transmitters and receivers may however
 * need to take other संकेत timings पूर्णांकo account to convert between driving
 * and sample edges.
 */
क्रमागत drm_bus_flags अणु
	/**
	 * @DRM_BUS_FLAG_DE_LOW:
	 *
	 * The Data Enable संकेत is active low
	 */
	DRM_BUS_FLAG_DE_LOW = BIT(0),

	/**
	 * @DRM_BUS_FLAG_DE_HIGH:
	 *
	 * The Data Enable संकेत is active high
	 */
	DRM_BUS_FLAG_DE_HIGH = BIT(1),

	/**
	 * @DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE:
	 *
	 * Data is driven on the rising edge of the pixel घड़ी
	 */
	DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE = BIT(2),

	/**
	 * @DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE:
	 *
	 * Data is driven on the falling edge of the pixel घड़ी
	 */
	DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE = BIT(3),

	/**
	 * @DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE:
	 *
	 * Data is sampled on the rising edge of the pixel घड़ी
	 */
	DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE = DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE,

	/**
	 * @DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE:
	 *
	 * Data is sampled on the falling edge of the pixel घड़ी
	 */
	DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE = DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE,

	/**
	 * @DRM_BUS_FLAG_DATA_MSB_TO_LSB:
	 *
	 * Data is transmitted MSB to LSB on the bus
	 */
	DRM_BUS_FLAG_DATA_MSB_TO_LSB = BIT(4),

	/**
	 * @DRM_BUS_FLAG_DATA_LSB_TO_MSB:
	 *
	 * Data is transmitted LSB to MSB on the bus
	 */
	DRM_BUS_FLAG_DATA_LSB_TO_MSB = BIT(5),

	/**
	 * @DRM_BUS_FLAG_SYNC_DRIVE_POSEDGE:
	 *
	 * Sync संकेतs are driven on the rising edge of the pixel घड़ी
	 */
	DRM_BUS_FLAG_SYNC_DRIVE_POSEDGE = BIT(6),

	/**
	 * @DRM_BUS_FLAG_SYNC_DRIVE_NEGEDGE:
	 *
	 * Sync संकेतs are driven on the falling edge of the pixel घड़ी
	 */
	DRM_BUS_FLAG_SYNC_DRIVE_NEGEDGE = BIT(7),

	/**
	 * @DRM_BUS_FLAG_SYNC_SAMPLE_POSEDGE:
	 *
	 * Sync संकेतs are sampled on the rising edge of the pixel घड़ी
	 */
	DRM_BUS_FLAG_SYNC_SAMPLE_POSEDGE = DRM_BUS_FLAG_SYNC_DRIVE_NEGEDGE,

	/**
	 * @DRM_BUS_FLAG_SYNC_SAMPLE_NEGEDGE:
	 *
	 * Sync संकेतs are sampled on the falling edge of the pixel घड़ी
	 */
	DRM_BUS_FLAG_SYNC_SAMPLE_NEGEDGE = DRM_BUS_FLAG_SYNC_DRIVE_POSEDGE,

	/**
	 * @DRM_BUS_FLAG_SHARP_SIGNALS:
	 *
	 *  Set अगर the Sharp-specअगरic संकेतs (SPL, CLS, PS, REV) must be used
	 */
	DRM_BUS_FLAG_SHARP_SIGNALS = BIT(8),
पूर्ण;

/**
 * काष्ठा drm_display_info - runसमय data about the connected sink
 *
 * Describes a given display (e.g. CRT or flat panel) and its limitations. For
 * fixed display sinks like built-in panels there's not much dअगरference between
 * this and &काष्ठा drm_connector. But क्रम sinks with a real cable this
 * काष्ठाure is meant to describe all the things at the other end of the cable.
 *
 * For sinks which provide an EDID this can be filled out by calling
 * drm_add_edid_modes().
 */
काष्ठा drm_display_info अणु
	/**
	 * @width_mm: Physical width in mm.
	 */
	अचिन्हित पूर्णांक width_mm;

	/**
	 * @height_mm: Physical height in mm.
	 */
	अचिन्हित पूर्णांक height_mm;

	/**
	 * @bpc: Maximum bits per color channel. Used by HDMI and DP outमाला_दो.
	 */
	अचिन्हित पूर्णांक bpc;

	/**
	 * @subpixel_order: Subpixel order of LCD panels.
	 */
	क्रमागत subpixel_order subpixel_order;

#घोषणा DRM_COLOR_FORMAT_RGB444		(1<<0)
#घोषणा DRM_COLOR_FORMAT_YCRCB444	(1<<1)
#घोषणा DRM_COLOR_FORMAT_YCRCB422	(1<<2)
#घोषणा DRM_COLOR_FORMAT_YCRCB420	(1<<3)

	/**
	 * @panel_orientation: Read only connector property क्रम built-in panels,
	 * indicating the orientation of the panel vs the device's casing.
	 * drm_connector_init() sets this to DRM_MODE_PANEL_ORIENTATION_UNKNOWN.
	 * When not UNKNOWN this माला_लो used by the drm_fb_helpers to rotate the
	 * fb to compensate and माला_लो exported as prop to userspace.
	 */
	पूर्णांक panel_orientation;

	/**
	 * @color_क्रमmats: HDMI Color क्रमmats, selects between RGB and YCrCb
	 * modes. Used DRM_COLOR_FORMAT\_ defines, which are _not_ the same ones
	 * as used to describe the pixel क्रमmat in framebuffers, and also करोn't
	 * match the क्रमmats in @bus_क्रमmats which are shared with v4l.
	 */
	u32 color_क्रमmats;

	/**
	 * @bus_क्रमmats: Pixel data क्रमmat on the wire, somewhat redundant with
	 * @color_क्रमmats. Array of size @num_bus_क्रमmats encoded using
	 * MEDIA_BUS_FMT\_ defines shared with v4l and media drivers.
	 */
	स्थिर u32 *bus_क्रमmats;
	/**
	 * @num_bus_क्रमmats: Size of @bus_क्रमmats array.
	 */
	अचिन्हित पूर्णांक num_bus_क्रमmats;

	/**
	 * @bus_flags: Additional inक्रमmation (like pixel संकेत polarity) क्रम
	 * the pixel data on the bus, using &क्रमागत drm_bus_flags values
	 * DRM_BUS_FLAGS\_.
	 */
	u32 bus_flags;

	/**
	 * @max_पंचांगds_घड़ी: Maximum TMDS घड़ी rate supported by the
	 * sink in kHz. 0 means undefined.
	 */
	पूर्णांक max_पंचांगds_घड़ी;

	/**
	 * @dvi_dual: Dual-link DVI sink?
	 */
	bool dvi_dual;

	/**
	 * @is_hdmi: True अगर the sink is an HDMI device.
	 *
	 * This field shall be used instead of calling
	 * drm_detect_hdmi_monitor() when possible.
	 */
	bool is_hdmi;

	/**
	 * @has_hdmi_infoframe: Does the sink support the HDMI infoframe?
	 */
	bool has_hdmi_infoframe;

	/**
	 * @rgb_quant_range_selectable: Does the sink support selecting
	 * the RGB quantization range?
	 */
	bool rgb_quant_range_selectable;

	/**
	 * @edid_hdmi_dc_modes: Mask of supported hdmi deep color modes. Even
	 * more stuff redundant with @bus_क्रमmats.
	 */
	u8 edid_hdmi_dc_modes;

	/**
	 * @cea_rev: CEA revision of the HDMI sink.
	 */
	u8 cea_rev;

	/**
	 * @hdmi: advance features of a HDMI sink.
	 */
	काष्ठा drm_hdmi_info hdmi;

	/**
	 * @non_desktop: Non desktop display (HMD).
	 */
	bool non_desktop;

	/**
	 * @monitor_range: Frequency range supported by monitor range descriptor
	 */
	काष्ठा drm_monitor_range_info monitor_range;
पूर्ण;

पूर्णांक drm_display_info_set_bus_क्रमmats(काष्ठा drm_display_info *info,
				     स्थिर u32 *क्रमmats,
				     अचिन्हित पूर्णांक num_क्रमmats);

/**
 * काष्ठा drm_connector_tv_margins - TV connector related margins
 *
 * Describes the margins in pixels to put around the image on TV
 * connectors to deal with overscan.
 */
काष्ठा drm_connector_tv_margins अणु
	/**
	 * @bottom: Bottom margin in pixels.
	 */
	अचिन्हित पूर्णांक bottom;

	/**
	 * @left: Left margin in pixels.
	 */
	अचिन्हित पूर्णांक left;

	/**
	 * @right: Right margin in pixels.
	 */
	अचिन्हित पूर्णांक right;

	/**
	 * @top: Top margin in pixels.
	 */
	अचिन्हित पूर्णांक top;
पूर्ण;

/**
 * काष्ठा drm_tv_connector_state - TV connector related states
 * @subconnector: selected subconnector
 * @margins: TV margins
 * @mode: TV mode
 * @brightness: brightness in percent
 * @contrast: contrast in percent
 * @flicker_reduction: flicker reduction in percent
 * @overscan: overscan in percent
 * @saturation: saturation in percent
 * @hue: hue in percent
 */
काष्ठा drm_tv_connector_state अणु
	क्रमागत drm_mode_subconnector subconnector;
	काष्ठा drm_connector_tv_margins margins;
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक brightness;
	अचिन्हित पूर्णांक contrast;
	अचिन्हित पूर्णांक flicker_reduction;
	अचिन्हित पूर्णांक overscan;
	अचिन्हित पूर्णांक saturation;
	अचिन्हित पूर्णांक hue;
पूर्ण;

/**
 * काष्ठा drm_connector_state - mutable connector state
 */
काष्ठा drm_connector_state अणु
	/** @connector: backpoपूर्णांकer to the connector */
	काष्ठा drm_connector *connector;

	/**
	 * @crtc: CRTC to connect connector to, शून्य अगर disabled.
	 *
	 * Do not change this directly, use drm_atomic_set_crtc_क्रम_connector()
	 * instead.
	 */
	काष्ठा drm_crtc *crtc;

	/**
	 * @best_encoder:
	 *
	 * Used by the atomic helpers to select the encoder, through the
	 * &drm_connector_helper_funcs.atomic_best_encoder or
	 * &drm_connector_helper_funcs.best_encoder callbacks.
	 *
	 * This is also used in the atomic helpers to map encoders to their
	 * current and previous connectors, see
	 * drm_atomic_get_old_connector_क्रम_encoder() and
	 * drm_atomic_get_new_connector_क्रम_encoder().
	 *
	 * NOTE: Atomic drivers must fill this out (either themselves or through
	 * helpers), क्रम otherwise the GETCONNECTOR and GETENCODER IOCTLs will
	 * not वापस correct data to userspace.
	 */
	काष्ठा drm_encoder *best_encoder;

	/**
	 * @link_status: Connector link_status to keep track of whether link is
	 * GOOD or BAD to notअगरy userspace अगर retraining is necessary.
	 */
	क्रमागत drm_link_status link_status;

	/** @state: backpoपूर्णांकer to global drm_atomic_state */
	काष्ठा drm_atomic_state *state;

	/**
	 * @commit: Tracks the pending commit to prevent use-after-मुक्त conditions.
	 *
	 * Is only set when @crtc is शून्य.
	 */
	काष्ठा drm_crtc_commit *commit;

	/** @tv: TV connector state */
	काष्ठा drm_tv_connector_state tv;

	/**
	 * @self_refresh_aware:
	 *
	 * This tracks whether a connector is aware of the self refresh state.
	 * It should be set to true क्रम those connector implementations which
	 * understand the self refresh state. This is needed since the crtc
	 * रेजिस्टरs the self refresh helpers and it करोesn't know अगर the
	 * connectors करोwnstream have implemented self refresh entry/निकास.
	 *
	 * Drivers should set this to true in atomic_check अगर they know how to
	 * handle self_refresh requests.
	 */
	bool self_refresh_aware;

	/**
	 * @picture_aspect_ratio: Connector property to control the
	 * HDMI infoframe aspect ratio setting.
	 *
	 * The %DRM_MODE_PICTURE_ASPECT_\* values much match the
	 * values क्रम &क्रमागत hdmi_picture_aspect
	 */
	क्रमागत hdmi_picture_aspect picture_aspect_ratio;

	/**
	 * @content_type: Connector property to control the
	 * HDMI infoframe content type setting.
	 * The %DRM_MODE_CONTENT_TYPE_\* values much
	 * match the values.
	 */
	अचिन्हित पूर्णांक content_type;

	/**
	 * @hdcp_content_type: Connector property to pass the type of
	 * रक्षित content. This is most commonly used क्रम HDCP.
	 */
	अचिन्हित पूर्णांक hdcp_content_type;

	/**
	 * @scaling_mode: Connector property to control the
	 * upscaling, mostly used क्रम built-in panels.
	 */
	अचिन्हित पूर्णांक scaling_mode;

	/**
	 * @content_protection: Connector property to request content
	 * protection. This is most commonly used क्रम HDCP.
	 */
	अचिन्हित पूर्णांक content_protection;

	/**
	 * @colorspace: State variable क्रम Connector property to request
	 * colorspace change on Sink. This is most commonly used to चयन
	 * to wider color gamuts like BT2020.
	 */
	u32 colorspace;

	/**
	 * @ग_लिखोback_job: Writeback job क्रम ग_लिखोback connectors
	 *
	 * Holds the framebuffer and out-fence क्रम a ग_लिखोback connector. As
	 * the ग_लिखोback completion may be asynchronous to the normal commit
	 * cycle, the ग_लिखोback job lअगरeसमय is managed separately from the
	 * normal atomic state by this object.
	 *
	 * See also: drm_ग_लिखोback_queue_job() and
	 * drm_ग_लिखोback_संकेत_completion()
	 */
	काष्ठा drm_ग_लिखोback_job *ग_लिखोback_job;

	/**
	 * @max_requested_bpc: Connector property to limit the maximum bit
	 * depth of the pixels.
	 */
	u8 max_requested_bpc;

	/**
	 * @max_bpc: Connector max_bpc based on the requested max_bpc property
	 * and the connector bpc limitations obtained from edid.
	 */
	u8 max_bpc;

	/**
	 * @hdr_output_metadata:
	 * DRM blob property क्रम HDR output metadata
	 */
	काष्ठा drm_property_blob *hdr_output_metadata;
पूर्ण;

/**
 * काष्ठा drm_connector_funcs - control connectors on a given device
 *
 * Each CRTC may have one or more connectors attached to it.  The functions
 * below allow the core DRM code to control connectors, क्रमागतerate available modes,
 * etc.
 */
काष्ठा drm_connector_funcs अणु
	/**
	 * @dpms:
	 *
	 * Legacy entry poपूर्णांक to set the per-connector DPMS state. Legacy DPMS
	 * is exposed as a standard property on the connector, but भागerted to
	 * this callback in the drm core. Note that atomic drivers करोn't
	 * implement the 4 level DPMS support on the connector any more, but
	 * instead only have an on/off "ACTIVE" property on the CRTC object.
	 *
	 * This hook is not used by atomic drivers, remapping of the legacy DPMS
	 * property is entirely handled in the DRM core.
	 *
	 * RETURNS:
	 *
	 * 0 on success or a negative error code on failure.
	 */
	पूर्णांक (*dpms)(काष्ठा drm_connector *connector, पूर्णांक mode);

	/**
	 * @reset:
	 *
	 * Reset connector hardware and software state to off. This function isn't
	 * called by the core directly, only through drm_mode_config_reset().
	 * It's not a helper hook only क्रम historical reasons.
	 *
	 * Atomic drivers can use drm_atomic_helper_connector_reset() to reset
	 * atomic state using this hook.
	 */
	व्योम (*reset)(काष्ठा drm_connector *connector);

	/**
	 * @detect:
	 *
	 * Check to see अगर anything is attached to the connector. The parameter
	 * क्रमce is set to false whilst polling, true when checking the
	 * connector due to a user request. क्रमce can be used by the driver to
	 * aव्योम expensive, deकाष्ठाive operations during स्वतःmated probing.
	 *
	 * This callback is optional, अगर not implemented the connector will be
	 * considered as always being attached.
	 *
	 * FIXME:
	 *
	 * Note that this hook is only called by the probe helper. It's not in
	 * the helper library vtable purely क्रम historical reasons. The only DRM
	 * core	entry poपूर्णांक to probe connector state is @fill_modes.
	 *
	 * Note that the helper library will alपढ़ोy hold
	 * &drm_mode_config.connection_mutex. Drivers which need to grab additional
	 * locks to aव्योम races with concurrent modeset changes need to use
	 * &drm_connector_helper_funcs.detect_ctx instead.
	 *
	 * RETURNS:
	 *
	 * drm_connector_status indicating the connector's status.
	 */
	क्रमागत drm_connector_status (*detect)(काष्ठा drm_connector *connector,
					    bool क्रमce);

	/**
	 * @क्रमce:
	 *
	 * This function is called to update पूर्णांकernal encoder state when the
	 * connector is क्रमced to a certain state by userspace, either through
	 * the sysfs पूर्णांकerfaces or on the kernel cmdline. In that हाल the
	 * @detect callback isn't called.
	 *
	 * FIXME:
	 *
	 * Note that this hook is only called by the probe helper. It's not in
	 * the helper library vtable purely क्रम historical reasons. The only DRM
	 * core	entry poपूर्णांक to probe connector state is @fill_modes.
	 */
	व्योम (*क्रमce)(काष्ठा drm_connector *connector);

	/**
	 * @fill_modes:
	 *
	 * Entry poपूर्णांक क्रम output detection and basic mode validation. The
	 * driver should reprobe the output अगर needed (e.g. when hotplug
	 * handling is unreliable), add all detected modes to &drm_connector.modes
	 * and filter out any the device can't support in any configuration. It
	 * also needs to filter out any modes wider or higher than the
	 * parameters max_width and max_height indicate.
	 *
	 * The drivers must also prune any modes no दीर्घer valid from
	 * &drm_connector.modes. Furthermore it must update
	 * &drm_connector.status and &drm_connector.edid.  If no EDID has been
	 * received क्रम this output connector->edid must be शून्य.
	 *
	 * Drivers using the probe helpers should use
	 * drm_helper_probe_single_connector_modes() to implement this
	 * function.
	 *
	 * RETURNS:
	 *
	 * The number of modes detected and filled पूर्णांकo &drm_connector.modes.
	 */
	पूर्णांक (*fill_modes)(काष्ठा drm_connector *connector, uपूर्णांक32_t max_width, uपूर्णांक32_t max_height);

	/**
	 * @set_property:
	 *
	 * This is the legacy entry poपूर्णांक to update a property attached to the
	 * connector.
	 *
	 * This callback is optional अगर the driver करोes not support any legacy
	 * driver-निजी properties. For atomic drivers it is not used because
	 * property handling is करोne entirely in the DRM core.
	 *
	 * RETURNS:
	 *
	 * 0 on success or a negative error code on failure.
	 */
	पूर्णांक (*set_property)(काष्ठा drm_connector *connector, काष्ठा drm_property *property,
			     uपूर्णांक64_t val);

	/**
	 * @late_रेजिस्टर:
	 *
	 * This optional hook can be used to रेजिस्टर additional userspace
	 * पूर्णांकerfaces attached to the connector, light backlight control, i2c,
	 * DP aux or similar पूर्णांकerfaces. It is called late in the driver load
	 * sequence from drm_connector_रेजिस्टर() when रेजिस्टरing all the
	 * core drm connector पूर्णांकerfaces. Everything added from this callback
	 * should be unरेजिस्टरed in the early_unरेजिस्टर callback.
	 *
	 * This is called जबतक holding &drm_connector.mutex.
	 *
	 * Returns:
	 *
	 * 0 on success, or a negative error code on failure.
	 */
	पूर्णांक (*late_रेजिस्टर)(काष्ठा drm_connector *connector);

	/**
	 * @early_unरेजिस्टर:
	 *
	 * This optional hook should be used to unरेजिस्टर the additional
	 * userspace पूर्णांकerfaces attached to the connector from
	 * late_रेजिस्टर(). It is called from drm_connector_unरेजिस्टर(),
	 * early in the driver unload sequence to disable userspace access
	 * beक्रमe data काष्ठाures are tornकरोwn.
	 *
	 * This is called जबतक holding &drm_connector.mutex.
	 */
	व्योम (*early_unरेजिस्टर)(काष्ठा drm_connector *connector);

	/**
	 * @destroy:
	 *
	 * Clean up connector resources. This is called at driver unload समय
	 * through drm_mode_config_cleanup(). It can also be called at runसमय
	 * when a connector is being hot-unplugged क्रम drivers that support
	 * connector hotplugging (e.g. DisplayPort MST).
	 */
	व्योम (*destroy)(काष्ठा drm_connector *connector);

	/**
	 * @atomic_duplicate_state:
	 *
	 * Duplicate the current atomic state क्रम this connector and वापस it.
	 * The core and helpers guarantee that any atomic state duplicated with
	 * this hook and still owned by the caller (i.e. not transferred to the
	 * driver by calling &drm_mode_config_funcs.atomic_commit) will be
	 * cleaned up by calling the @atomic_destroy_state hook in this
	 * काष्ठाure.
	 *
	 * This callback is mandatory क्रम atomic drivers.
	 *
	 * Atomic drivers which करोn't subclass &काष्ठा drm_connector_state should use
	 * drm_atomic_helper_connector_duplicate_state(). Drivers that subclass the
	 * state काष्ठाure to extend it with driver-निजी state should use
	 * __drm_atomic_helper_connector_duplicate_state() to make sure shared state is
	 * duplicated in a consistent fashion across drivers.
	 *
	 * It is an error to call this hook beक्रमe &drm_connector.state has been
	 * initialized correctly.
	 *
	 * NOTE:
	 *
	 * If the duplicate state references refcounted resources this hook must
	 * acquire a reference क्रम each of them. The driver must release these
	 * references again in @atomic_destroy_state.
	 *
	 * RETURNS:
	 *
	 * Duplicated atomic state or शून्य when the allocation failed.
	 */
	काष्ठा drm_connector_state *(*atomic_duplicate_state)(काष्ठा drm_connector *connector);

	/**
	 * @atomic_destroy_state:
	 *
	 * Destroy a state duplicated with @atomic_duplicate_state and release
	 * or unreference all resources it references
	 *
	 * This callback is mandatory क्रम atomic drivers.
	 */
	व्योम (*atomic_destroy_state)(काष्ठा drm_connector *connector,
				     काष्ठा drm_connector_state *state);

	/**
	 * @atomic_set_property:
	 *
	 * Decode a driver-निजी property value and store the decoded value
	 * पूर्णांकo the passed-in state काष्ठाure. Since the atomic core decodes all
	 * standardized properties (even क्रम extensions beyond the core set of
	 * properties which might not be implemented by all drivers) this
	 * requires drivers to subclass the state काष्ठाure.
	 *
	 * Such driver-निजी properties should really only be implemented क्रम
	 * truly hardware/venकरोr specअगरic state. Instead it is preferred to
	 * standardize atomic extension and decode the properties used to expose
	 * such an extension in the core.
	 *
	 * Do not call this function directly, use
	 * drm_atomic_connector_set_property() instead.
	 *
	 * This callback is optional अगर the driver करोes not support any
	 * driver-निजी atomic properties.
	 *
	 * NOTE:
	 *
	 * This function is called in the state assembly phase of atomic
	 * modesets, which can be पातed क्रम any reason (including on
	 * userspace's request to just check whether a configuration would be
	 * possible). Drivers MUST NOT touch any persistent state (hardware or
	 * software) or data काष्ठाures except the passed in @state parameter.
	 *
	 * Also since userspace controls in which order properties are set this
	 * function must not करो any input validation (since the state update is
	 * incomplete and hence likely inconsistent). Instead any such input
	 * validation must be करोne in the various atomic_check callbacks.
	 *
	 * RETURNS:
	 *
	 * 0 अगर the property has been found, -EINVAL अगर the property isn't
	 * implemented by the driver (which shouldn't ever happen, the core only
	 * asks क्रम properties attached to this connector). No other validation
	 * is allowed by the driver. The core alपढ़ोy checks that the property
	 * value is within the range (पूर्णांकeger, valid क्रमागत value, ...) the driver
	 * set when रेजिस्टरing the property.
	 */
	पूर्णांक (*atomic_set_property)(काष्ठा drm_connector *connector,
				   काष्ठा drm_connector_state *state,
				   काष्ठा drm_property *property,
				   uपूर्णांक64_t val);

	/**
	 * @atomic_get_property:
	 *
	 * Reads out the decoded driver-निजी property. This is used to
	 * implement the GETCONNECTOR IOCTL.
	 *
	 * Do not call this function directly, use
	 * drm_atomic_connector_get_property() instead.
	 *
	 * This callback is optional अगर the driver करोes not support any
	 * driver-निजी atomic properties.
	 *
	 * RETURNS:
	 *
	 * 0 on success, -EINVAL अगर the property isn't implemented by the
	 * driver (which shouldn't ever happen, the core only asks क्रम
	 * properties attached to this connector).
	 */
	पूर्णांक (*atomic_get_property)(काष्ठा drm_connector *connector,
				   स्थिर काष्ठा drm_connector_state *state,
				   काष्ठा drm_property *property,
				   uपूर्णांक64_t *val);

	/**
	 * @atomic_prपूर्णांक_state:
	 *
	 * If driver subclasses &काष्ठा drm_connector_state, it should implement
	 * this optional hook क्रम prपूर्णांकing additional driver specअगरic state.
	 *
	 * Do not call this directly, use drm_atomic_connector_prपूर्णांक_state()
	 * instead.
	 */
	व्योम (*atomic_prपूर्णांक_state)(काष्ठा drm_prपूर्णांकer *p,
				   स्थिर काष्ठा drm_connector_state *state);
पूर्ण;

/**
 * काष्ठा drm_cmdline_mode - DRM Mode passed through the kernel command-line
 *
 * Each connector can have an initial mode with additional options
 * passed through the kernel command line. This काष्ठाure allows to
 * express those parameters and will be filled by the command-line
 * parser.
 */
काष्ठा drm_cmdline_mode अणु
	/**
	 * @name:
	 *
	 * Name of the mode.
	 */
	अक्षर name[DRM_DISPLAY_MODE_LEN];

	/**
	 * @specअगरied:
	 *
	 * Has a mode been पढ़ो from the command-line?
	 */
	bool specअगरied;

	/**
	 * @refresh_specअगरied:
	 *
	 * Did the mode have a preferred refresh rate?
	 */
	bool refresh_specअगरied;

	/**
	 * @bpp_specअगरied:
	 *
	 * Did the mode have a preferred BPP?
	 */
	bool bpp_specअगरied;

	/**
	 * @xres:
	 *
	 * Active resolution on the X axis, in pixels.
	 */
	पूर्णांक xres;

	/**
	 * @yres:
	 *
	 * Active resolution on the Y axis, in pixels.
	 */
	पूर्णांक yres;

	/**
	 * @bpp:
	 *
	 * Bits per pixels क्रम the mode.
	 */
	पूर्णांक bpp;

	/**
	 * @refresh:
	 *
	 * Refresh rate, in Hertz.
	 */
	पूर्णांक refresh;

	/**
	 * @rb:
	 *
	 * Do we need to use reduced blanking?
	 */
	bool rb;

	/**
	 * @पूर्णांकerlace:
	 *
	 * The mode is पूर्णांकerlaced.
	 */
	bool पूर्णांकerlace;

	/**
	 * @cvt:
	 *
	 * The timings will be calculated using the VESA Coordinated
	 * Video Timings instead of looking up the mode from a table.
	 */
	bool cvt;

	/**
	 * @margins:
	 *
	 * Add margins to the mode calculation (1.8% of xres rounded
	 * करोwn to 8 pixels and 1.8% of yres).
	 */
	bool margins;

	/**
	 * @क्रमce:
	 *
	 * Ignore the hotplug state of the connector, and क्रमce its
	 * state to one of the DRM_FORCE_* values.
	 */
	क्रमागत drm_connector_क्रमce क्रमce;

	/**
	 * @rotation_reflection:
	 *
	 * Initial rotation and reflection of the mode setup from the
	 * command line. See DRM_MODE_ROTATE_* and
	 * DRM_MODE_REFLECT_*. The only rotations supported are
	 * DRM_MODE_ROTATE_0 and DRM_MODE_ROTATE_180.
	 */
	अचिन्हित पूर्णांक rotation_reflection;

	/**
	 * @panel_orientation:
	 *
	 * drm-connector "panel orientation" property override value,
	 * DRM_MODE_PANEL_ORIENTATION_UNKNOWN अगर not set.
	 */
	क्रमागत drm_panel_orientation panel_orientation;

	/**
	 * @tv_margins: TV margins to apply to the mode.
	 */
	काष्ठा drm_connector_tv_margins tv_margins;
पूर्ण;

/**
 * काष्ठा drm_connector - central DRM connector control काष्ठाure
 *
 * Each connector may be connected to one or more CRTCs, or may be clonable by
 * another connector अगर they can share a CRTC.  Each connector also has a specअगरic
 * position in the broader display (referred to as a 'screen' though it could
 * span multiple monitors).
 */
काष्ठा drm_connector अणु
	/** @dev: parent DRM device */
	काष्ठा drm_device *dev;
	/** @kdev: kernel device क्रम sysfs attributes */
	काष्ठा device *kdev;
	/** @attr: sysfs attributes */
	काष्ठा device_attribute *attr;

	/**
	 * @head:
	 *
	 * List of all connectors on a @dev, linked from
	 * &drm_mode_config.connector_list. Protected by
	 * &drm_mode_config.connector_list_lock, but please only use
	 * &drm_connector_list_iter to walk this list.
	 */
	काष्ठा list_head head;

	/** @base: base KMS object */
	काष्ठा drm_mode_object base;

	/** @name: human पढ़ोable name, can be overwritten by the driver */
	अक्षर *name;

	/**
	 * @mutex: Lock क्रम general connector state, but currently only protects
	 * @रेजिस्टरed. Most of the connector state is still रक्षित by
	 * &drm_mode_config.mutex.
	 */
	काष्ठा mutex mutex;

	/**
	 * @index: Compacted connector index, which matches the position inside
	 * the mode_config.list क्रम drivers not supporting hot-add/removing. Can
	 * be used as an array index. It is invariant over the lअगरeसमय of the
	 * connector.
	 */
	अचिन्हित index;

	/**
	 * @connector_type:
	 * one of the DRM_MODE_CONNECTOR_<foo> types from drm_mode.h
	 */
	पूर्णांक connector_type;
	/** @connector_type_id: index पूर्णांकo connector type क्रमागत */
	पूर्णांक connector_type_id;
	/**
	 * @पूर्णांकerlace_allowed:
	 * Can this connector handle पूर्णांकerlaced modes? Only used by
	 * drm_helper_probe_single_connector_modes() क्रम mode filtering.
	 */
	bool पूर्णांकerlace_allowed;
	/**
	 * @द्विगुनscan_allowed:
	 * Can this connector handle द्विगुनscan? Only used by
	 * drm_helper_probe_single_connector_modes() क्रम mode filtering.
	 */
	bool द्विगुनscan_allowed;
	/**
	 * @stereo_allowed:
	 * Can this connector handle stereo modes? Only used by
	 * drm_helper_probe_single_connector_modes() क्रम mode filtering.
	 */
	bool stereo_allowed;

	/**
	 * @ycbcr_420_allowed : This bool indicates अगर this connector is
	 * capable of handling YCBCR 420 output. While parsing the EDID
	 * blocks it's very helpful to know अगर the source is capable of
	 * handling YCBCR 420 outमाला_दो.
	 */
	bool ycbcr_420_allowed;

	/**
	 * @registration_state: Is this connector initializing, exposed
	 * (रेजिस्टरed) with userspace, or unरेजिस्टरed?
	 *
	 * Protected by @mutex.
	 */
	क्रमागत drm_connector_registration_state registration_state;

	/**
	 * @modes:
	 * Modes available on this connector (from fill_modes() + user).
	 * Protected by &drm_mode_config.mutex.
	 */
	काष्ठा list_head modes;

	/**
	 * @status:
	 * One of the drm_connector_status क्रमागतs (connected, not, or unknown).
	 * Protected by &drm_mode_config.mutex.
	 */
	क्रमागत drm_connector_status status;

	/**
	 * @probed_modes:
	 * These are modes added by probing with DDC or the BIOS, beक्रमe
	 * filtering is applied. Used by the probe helpers. Protected by
	 * &drm_mode_config.mutex.
	 */
	काष्ठा list_head probed_modes;

	/**
	 * @display_info: Display inक्रमmation is filled from EDID inक्रमmation
	 * when a display is detected. For non hot-pluggable displays such as
	 * flat panels in embedded प्रणालीs, the driver should initialize the
	 * &drm_display_info.width_mm and &drm_display_info.height_mm fields
	 * with the physical size of the display.
	 *
	 * Protected by &drm_mode_config.mutex.
	 */
	काष्ठा drm_display_info display_info;

	/** @funcs: connector control functions */
	स्थिर काष्ठा drm_connector_funcs *funcs;

	/**
	 * @edid_blob_ptr: DRM property containing EDID अगर present. Protected by
	 * &drm_mode_config.mutex. This should be updated only by calling
	 * drm_connector_update_edid_property().
	 */
	काष्ठा drm_property_blob *edid_blob_ptr;

	/** @properties: property tracking क्रम this connector */
	काष्ठा drm_object_properties properties;

	/**
	 * @scaling_mode_property: Optional atomic property to control the
	 * upscaling. See drm_connector_attach_content_protection_property().
	 */
	काष्ठा drm_property *scaling_mode_property;

	/**
	 * @vrr_capable_property: Optional property to help userspace
	 * query hardware support क्रम variable refresh rate on a connector.
	 * connector. Drivers can add the property to a connector by
	 * calling drm_connector_attach_vrr_capable_property().
	 *
	 * This should be updated only by calling
	 * drm_connector_set_vrr_capable_property().
	 */
	काष्ठा drm_property *vrr_capable_property;

	/**
	 * @colorspace_property: Connector property to set the suitable
	 * colorspace supported by the sink.
	 */
	काष्ठा drm_property *colorspace_property;

	/**
	 * @path_blob_ptr:
	 *
	 * DRM blob property data क्रम the DP MST path property. This should only
	 * be updated by calling drm_connector_set_path_property().
	 */
	काष्ठा drm_property_blob *path_blob_ptr;

	/**
	 * @max_bpc_property: Default connector property क्रम the max bpc to be
	 * driven out of the connector.
	 */
	काष्ठा drm_property *max_bpc_property;

#घोषणा DRM_CONNECTOR_POLL_HPD (1 << 0)
#घोषणा DRM_CONNECTOR_POLL_CONNECT (1 << 1)
#घोषणा DRM_CONNECTOR_POLL_DISCONNECT (1 << 2)

	/**
	 * @polled:
	 *
	 * Connector polling mode, a combination of
	 *
	 * DRM_CONNECTOR_POLL_HPD
	 *     The connector generates hotplug events and करोesn't need to be
	 *     periodically polled. The CONNECT and DISCONNECT flags must not
	 *     be set together with the HPD flag.
	 *
	 * DRM_CONNECTOR_POLL_CONNECT
	 *     Periodically poll the connector क्रम connection.
	 *
	 * DRM_CONNECTOR_POLL_DISCONNECT
	 *     Periodically poll the connector क्रम disconnection, without
	 *     causing flickering even when the connector is in use. DACs should
	 *     rarely करो this without a lot of testing.
	 *
	 * Set to 0 क्रम connectors that करोn't support connection status
	 * discovery.
	 */
	uपूर्णांक8_t polled;

	/**
	 * @dpms: Current dpms state. For legacy drivers the
	 * &drm_connector_funcs.dpms callback must update this. For atomic
	 * drivers, this is handled by the core atomic code, and drivers must
	 * only take &drm_crtc_state.active पूर्णांकo account.
	 */
	पूर्णांक dpms;

	/** @helper_निजी: mid-layer निजी data */
	स्थिर काष्ठा drm_connector_helper_funcs *helper_निजी;

	/** @cmdline_mode: mode line parsed from the kernel cmdline क्रम this connector */
	काष्ठा drm_cmdline_mode cmdline_mode;
	/** @क्रमce: a DRM_FORCE_<foo> state क्रम क्रमced mode sets */
	क्रमागत drm_connector_क्रमce क्रमce;
	/** @override_edid: has the EDID been overwritten through debugfs क्रम testing? */
	bool override_edid;
	/** @epoch_counter: used to detect any other changes in connector, besides status */
	u64 epoch_counter;

	/**
	 * @possible_encoders: Bit mask of encoders that can drive this
	 * connector, drm_encoder_index() determines the index पूर्णांकo the bitfield
	 * and the bits are set with drm_connector_attach_encoder().
	 */
	u32 possible_encoders;

	/**
	 * @encoder: Currently bound encoder driving this connector, अगर any.
	 * Only really meaningful क्रम non-atomic drivers. Atomic drivers should
	 * instead look at &drm_connector_state.best_encoder, and in हाल they
	 * need the CRTC driving this output, &drm_connector_state.crtc.
	 */
	काष्ठा drm_encoder *encoder;

#घोषणा MAX_ELD_BYTES	128
	/** @eld: EDID-like data, अगर present */
	uपूर्णांक8_t eld[MAX_ELD_BYTES];
	/** @latency_present: AV delay info from ELD, अगर found */
	bool latency_present[2];
	/**
	 * @video_latency: Video latency info from ELD, अगर found.
	 * [0]: progressive, [1]: पूर्णांकerlaced
	 */
	पूर्णांक video_latency[2];
	/**
	 * @audio_latency: audio latency info from ELD, अगर found
	 * [0]: progressive, [1]: पूर्णांकerlaced
	 */
	पूर्णांक audio_latency[2];

	/**
	 * @ddc: associated ddc adapter.
	 * A connector usually has its associated ddc adapter. If a driver uses
	 * this field, then an appropriate symbolic link is created in connector
	 * sysfs directory to make it easy क्रम the user to tell which i2c
	 * adapter is क्रम a particular display.
	 *
	 * The field should be set by calling drm_connector_init_with_ddc().
	 */
	काष्ठा i2c_adapter *ddc;

	/**
	 * @null_edid_counter: track sinks that give us all zeros क्रम the EDID.
	 * Needed to workaround some HW bugs where we get all 0s
	 */
	पूर्णांक null_edid_counter;

	/** @bad_edid_counter: track sinks that give us an EDID with invalid checksum */
	अचिन्हित bad_edid_counter;

	/**
	 * @edid_corrupt: Indicates whether the last पढ़ो EDID was corrupt. Used
	 * in Displayport compliance testing - Displayport Link CTS Core 1.2
	 * rev1.1 4.2.2.6
	 */
	bool edid_corrupt;
	/**
	 * @real_edid_checksum: real edid checksum क्रम corrupted edid block.
	 * Required in Displayport 1.4 compliance testing
	 * rev1.1 4.2.2.6
	 */
	u8 real_edid_checksum;

	/** @debugfs_entry: debugfs directory क्रम this connector */
	काष्ठा dentry *debugfs_entry;

	/**
	 * @state:
	 *
	 * Current atomic state क्रम this connector.
	 *
	 * This is रक्षित by &drm_mode_config.connection_mutex. Note that
	 * nonblocking atomic commits access the current connector state without
	 * taking locks. Either by going through the &काष्ठा drm_atomic_state
	 * poपूर्णांकers, see क्रम_each_oldnew_connector_in_state(),
	 * क्रम_each_old_connector_in_state() and
	 * क्रम_each_new_connector_in_state(). Or through careful ordering of
	 * atomic commit operations as implemented in the atomic helpers, see
	 * &काष्ठा drm_crtc_commit.
	 */
	काष्ठा drm_connector_state *state;

	/* DisplayID bits. FIXME: Extract पूर्णांकo a subकाष्ठा? */

	/**
	 * @tile_blob_ptr:
	 *
	 * DRM blob property data क्रम the tile property (used mostly by DP MST).
	 * This is meant क्रम screens which are driven through separate display
	 * pipelines represented by &drm_crtc, which might not be running with
	 * genlocked घड़ीs. For tiled panels which are genlocked, like
	 * dual-link LVDS or dual-link DSI, the driver should try to not expose
	 * the tiling and भवize both &drm_crtc and &drm_plane अगर needed.
	 *
	 * This should only be updated by calling
	 * drm_connector_set_tile_property().
	 */
	काष्ठा drm_property_blob *tile_blob_ptr;

	/** @has_tile: is this connector connected to a tiled monitor */
	bool has_tile;
	/** @tile_group: tile group क्रम the connected monitor */
	काष्ठा drm_tile_group *tile_group;
	/** @tile_is_single_monitor: whether the tile is one monitor housing */
	bool tile_is_single_monitor;

	/** @num_h_tile: number of horizontal tiles in the tile group */
	/** @num_v_tile: number of vertical tiles in the tile group */
	uपूर्णांक8_t num_h_tile, num_v_tile;
	/** @tile_h_loc: horizontal location of this tile */
	/** @tile_v_loc: vertical location of this tile */
	uपूर्णांक8_t tile_h_loc, tile_v_loc;
	/** @tile_h_size: horizontal size of this tile. */
	/** @tile_v_size: vertical size of this tile. */
	uपूर्णांक16_t tile_h_size, tile_v_size;

	/**
	 * @मुक्त_node:
	 *
	 * List used only by &drm_connector_list_iter to be able to clean up a
	 * connector from any context, in conjunction with
	 * &drm_mode_config.connector_मुक्त_work.
	 */
	काष्ठा llist_node मुक्त_node;

	/** @hdr_sink_metadata: HDR Metadata Inक्रमmation पढ़ो from sink */
	काष्ठा hdr_sink_metadata hdr_sink_metadata;
पूर्ण;

#घोषणा obj_to_connector(x) container_of(x, काष्ठा drm_connector, base)

पूर्णांक drm_connector_init(काष्ठा drm_device *dev,
		       काष्ठा drm_connector *connector,
		       स्थिर काष्ठा drm_connector_funcs *funcs,
		       पूर्णांक connector_type);
पूर्णांक drm_connector_init_with_ddc(काष्ठा drm_device *dev,
				काष्ठा drm_connector *connector,
				स्थिर काष्ठा drm_connector_funcs *funcs,
				पूर्णांक connector_type,
				काष्ठा i2c_adapter *ddc);
व्योम drm_connector_attach_edid_property(काष्ठा drm_connector *connector);
पूर्णांक drm_connector_रेजिस्टर(काष्ठा drm_connector *connector);
व्योम drm_connector_unरेजिस्टर(काष्ठा drm_connector *connector);
पूर्णांक drm_connector_attach_encoder(काष्ठा drm_connector *connector,
				      काष्ठा drm_encoder *encoder);

व्योम drm_connector_cleanup(काष्ठा drm_connector *connector);

अटल अंतरभूत अचिन्हित पूर्णांक drm_connector_index(स्थिर काष्ठा drm_connector *connector)
अणु
	वापस connector->index;
पूर्ण

अटल अंतरभूत u32 drm_connector_mask(स्थिर काष्ठा drm_connector *connector)
अणु
	वापस 1 << connector->index;
पूर्ण

/**
 * drm_connector_lookup - lookup connector object
 * @dev: DRM device
 * @file_priv: drm file to check क्रम lease against.
 * @id: connector object id
 *
 * This function looks up the connector object specअगरied by id
 * add takes a reference to it.
 */
अटल अंतरभूत काष्ठा drm_connector *drm_connector_lookup(काष्ठा drm_device *dev,
		काष्ठा drm_file *file_priv,
		uपूर्णांक32_t id)
अणु
	काष्ठा drm_mode_object *mo;
	mo = drm_mode_object_find(dev, file_priv, id, DRM_MODE_OBJECT_CONNECTOR);
	वापस mo ? obj_to_connector(mo) : शून्य;
पूर्ण

/**
 * drm_connector_get - acquire a connector reference
 * @connector: DRM connector
 *
 * This function increments the connector's refcount.
 */
अटल अंतरभूत व्योम drm_connector_get(काष्ठा drm_connector *connector)
अणु
	drm_mode_object_get(&connector->base);
पूर्ण

/**
 * drm_connector_put - release a connector reference
 * @connector: DRM connector
 *
 * This function decrements the connector's reference count and मुक्तs the
 * object अगर the reference count drops to zero.
 */
अटल अंतरभूत व्योम drm_connector_put(काष्ठा drm_connector *connector)
अणु
	drm_mode_object_put(&connector->base);
पूर्ण

/**
 * drm_connector_is_unरेजिस्टरed - has the connector been unरेजिस्टरed from
 * userspace?
 * @connector: DRM connector
 *
 * Checks whether or not @connector has been unरेजिस्टरed from userspace.
 *
 * Returns:
 * True अगर the connector was unरेजिस्टरed, false अगर the connector is
 * रेजिस्टरed or has not yet been रेजिस्टरed with userspace.
 */
अटल अंतरभूत bool
drm_connector_is_unरेजिस्टरed(काष्ठा drm_connector *connector)
अणु
	वापस READ_ONCE(connector->registration_state) ==
		DRM_CONNECTOR_UNREGISTERED;
पूर्ण

स्थिर अक्षर *drm_get_connector_type_name(अचिन्हित पूर्णांक connector_type);
स्थिर अक्षर *drm_get_connector_status_name(क्रमागत drm_connector_status status);
स्थिर अक्षर *drm_get_subpixel_order_name(क्रमागत subpixel_order order);
स्थिर अक्षर *drm_get_dpms_name(पूर्णांक val);
स्थिर अक्षर *drm_get_dvi_i_subconnector_name(पूर्णांक val);
स्थिर अक्षर *drm_get_dvi_i_select_name(पूर्णांक val);
स्थिर अक्षर *drm_get_tv_subconnector_name(पूर्णांक val);
स्थिर अक्षर *drm_get_tv_select_name(पूर्णांक val);
स्थिर अक्षर *drm_get_dp_subconnector_name(पूर्णांक val);
स्थिर अक्षर *drm_get_content_protection_name(पूर्णांक val);
स्थिर अक्षर *drm_get_hdcp_content_type_name(पूर्णांक val);

पूर्णांक drm_mode_create_dvi_i_properties(काष्ठा drm_device *dev);
व्योम drm_connector_attach_dp_subconnector_property(काष्ठा drm_connector *connector);

पूर्णांक drm_mode_create_tv_margin_properties(काष्ठा drm_device *dev);
पूर्णांक drm_mode_create_tv_properties(काष्ठा drm_device *dev,
				  अचिन्हित पूर्णांक num_modes,
				  स्थिर अक्षर * स्थिर modes[]);
व्योम drm_connector_attach_tv_margin_properties(काष्ठा drm_connector *conn);
पूर्णांक drm_mode_create_scaling_mode_property(काष्ठा drm_device *dev);
पूर्णांक drm_connector_attach_content_type_property(काष्ठा drm_connector *dev);
पूर्णांक drm_connector_attach_scaling_mode_property(काष्ठा drm_connector *connector,
					       u32 scaling_mode_mask);
पूर्णांक drm_connector_attach_vrr_capable_property(
		काष्ठा drm_connector *connector);
पूर्णांक drm_mode_create_aspect_ratio_property(काष्ठा drm_device *dev);
पूर्णांक drm_mode_create_hdmi_colorspace_property(काष्ठा drm_connector *connector);
पूर्णांक drm_mode_create_dp_colorspace_property(काष्ठा drm_connector *connector);
पूर्णांक drm_mode_create_content_type_property(काष्ठा drm_device *dev);
व्योम drm_hdmi_avi_infoframe_content_type(काष्ठा hdmi_avi_infoframe *frame,
					 स्थिर काष्ठा drm_connector_state *conn_state);

पूर्णांक drm_mode_create_suggested_offset_properties(काष्ठा drm_device *dev);

पूर्णांक drm_connector_set_path_property(काष्ठा drm_connector *connector,
				    स्थिर अक्षर *path);
पूर्णांक drm_connector_set_tile_property(काष्ठा drm_connector *connector);
पूर्णांक drm_connector_update_edid_property(काष्ठा drm_connector *connector,
				       स्थिर काष्ठा edid *edid);
व्योम drm_connector_set_link_status_property(काष्ठा drm_connector *connector,
					    uपूर्णांक64_t link_status);
व्योम drm_connector_set_vrr_capable_property(
		काष्ठा drm_connector *connector, bool capable);
पूर्णांक drm_connector_set_panel_orientation(
	काष्ठा drm_connector *connector,
	क्रमागत drm_panel_orientation panel_orientation);
पूर्णांक drm_connector_set_panel_orientation_with_quirk(
	काष्ठा drm_connector *connector,
	क्रमागत drm_panel_orientation panel_orientation,
	पूर्णांक width, पूर्णांक height);
पूर्णांक drm_connector_attach_max_bpc_property(काष्ठा drm_connector *connector,
					  पूर्णांक min, पूर्णांक max);

/**
 * काष्ठा drm_tile_group - Tile group metadata
 * @refcount: reference count
 * @dev: DRM device
 * @id: tile group id exposed to userspace
 * @group_data: Sink-निजी data identअगरying this group
 *
 * @group_data corresponds to displayid vend/prod/serial क्रम बाह्यal screens
 * with an EDID.
 */
काष्ठा drm_tile_group अणु
	काष्ठा kref refcount;
	काष्ठा drm_device *dev;
	पूर्णांक id;
	u8 group_data[8];
पूर्ण;

काष्ठा drm_tile_group *drm_mode_create_tile_group(काष्ठा drm_device *dev,
						  स्थिर अक्षर topology[8]);
काष्ठा drm_tile_group *drm_mode_get_tile_group(काष्ठा drm_device *dev,
					       स्थिर अक्षर topology[8]);
व्योम drm_mode_put_tile_group(काष्ठा drm_device *dev,
			     काष्ठा drm_tile_group *tg);

/**
 * काष्ठा drm_connector_list_iter - connector_list iterator
 *
 * This iterator tracks state needed to be able to walk the connector_list
 * within काष्ठा drm_mode_config. Only use together with
 * drm_connector_list_iter_begin(), drm_connector_list_iter_end() and
 * drm_connector_list_iter_next() respectively the convenience macro
 * drm_क्रम_each_connector_iter().
 */
काष्ठा drm_connector_list_iter अणु
/* निजी: */
	काष्ठा drm_device *dev;
	काष्ठा drm_connector *conn;
पूर्ण;

व्योम drm_connector_list_iter_begin(काष्ठा drm_device *dev,
				   काष्ठा drm_connector_list_iter *iter);
काष्ठा drm_connector *
drm_connector_list_iter_next(काष्ठा drm_connector_list_iter *iter);
व्योम drm_connector_list_iter_end(काष्ठा drm_connector_list_iter *iter);

bool drm_connector_has_possible_encoder(काष्ठा drm_connector *connector,
					काष्ठा drm_encoder *encoder);

/**
 * drm_क्रम_each_connector_iter - connector_list iterator macro
 * @connector: &काष्ठा drm_connector poपूर्णांकer used as cursor
 * @iter: &काष्ठा drm_connector_list_iter
 *
 * Note that @connector is only valid within the list body, अगर you want to use
 * @connector after calling drm_connector_list_iter_end() then you need to grab
 * your own reference first using drm_connector_get().
 */
#घोषणा drm_क्रम_each_connector_iter(connector, iter) \
	जबतक ((connector = drm_connector_list_iter_next(iter)))

/**
 * drm_connector_क्रम_each_possible_encoder - iterate connector's possible encoders
 * @connector: &काष्ठा drm_connector poपूर्णांकer
 * @encoder: &काष्ठा drm_encoder poपूर्णांकer used as cursor
 */
#घोषणा drm_connector_क्रम_each_possible_encoder(connector, encoder) \
	drm_क्रम_each_encoder_mask(encoder, (connector)->dev, \
				  (connector)->possible_encoders)

#पूर्ण_अगर
