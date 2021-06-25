<शैली गुरु>
/*
 * Copyright तऊ 2006 Keith Packard
 * Copyright तऊ 2007-2008 Dave Airlie
 * Copyright तऊ 2007-2008 Intel Corporation
 *   Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 * Copyright तऊ 2014 Intel Corporation
 *   Daniel Vetter <daniel.vetter@ffwll.ch>
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
 */
#अगर_अघोषित __DRM_MODES_H__
#घोषणा __DRM_MODES_H__

#समावेश <linux/hdmi.h>

#समावेश <drm/drm_mode_object.h>
#समावेश <drm/drm_connector.h>

काष्ठा videomode;

/*
 * Note on terminology:  here, क्रम brevity and convenience, we refer to connector
 * control chips as 'CRTCs'.  They can control any type of connector, VGA, LVDS,
 * DVI, etc.  And 'screen' refers to the whole of the visible display, which
 * may span multiple monitors (and thereक्रमe multiple CRTC and connector
 * काष्ठाures).
 */

/**
 * क्रमागत drm_mode_status - hardware support status of a mode
 * @MODE_OK: Mode OK
 * @MODE_HSYNC: hsync out of range
 * @MODE_VSYNC: vsync out of range
 * @MODE_H_ILLEGAL: mode has illegal horizontal timings
 * @MODE_V_ILLEGAL: mode has illegal vertical timings
 * @MODE_BAD_WIDTH: requires an unsupported linepitch
 * @MODE_NOMODE: no mode with a matching name
 * @MODE_NO_INTERLACE: पूर्णांकerlaced mode not supported
 * @MODE_NO_DBLESCAN: द्विगुनscan mode not supported
 * @MODE_NO_VSCAN: multiscan mode not supported
 * @MODE_MEM: insufficient video memory
 * @MODE_VIRTUAL_X: mode width too large क्रम specअगरied भव size
 * @MODE_VIRTUAL_Y: mode height too large क्रम specअगरied भव size
 * @MODE_MEM_VIRT: insufficient video memory given भव size
 * @MODE_NOCLOCK: no fixed घड़ी available
 * @MODE_CLOCK_HIGH: घड़ी required is too high
 * @MODE_CLOCK_LOW: घड़ी required is too low
 * @MODE_CLOCK_RANGE: घड़ी/mode isn't in a ClockRange
 * @MODE_BAD_HVALUE: horizontal timing was out of range
 * @MODE_BAD_VVALUE: vertical timing was out of range
 * @MODE_BAD_VSCAN: VScan value out of range
 * @MODE_HSYNC_NARROW: horizontal sync too narrow
 * @MODE_HSYNC_WIDE: horizontal sync too wide
 * @MODE_HBLANK_NARROW: horizontal blanking too narrow
 * @MODE_HBLANK_WIDE: horizontal blanking too wide
 * @MODE_VSYNC_NARROW: vertical sync too narrow
 * @MODE_VSYNC_WIDE: vertical sync too wide
 * @MODE_VBLANK_NARROW: vertical blanking too narrow
 * @MODE_VBLANK_WIDE: vertical blanking too wide
 * @MODE_PANEL: exceeds panel dimensions
 * @MODE_INTERLACE_WIDTH: width too large क्रम पूर्णांकerlaced mode
 * @MODE_ONE_WIDTH: only one width is supported
 * @MODE_ONE_HEIGHT: only one height is supported
 * @MODE_ONE_SIZE: only one resolution is supported
 * @MODE_NO_REDUCED: monitor करोesn't accept reduced blanking
 * @MODE_NO_STEREO: stereo modes not supported
 * @MODE_NO_420: ycbcr 420 modes not supported
 * @MODE_STALE: mode has become stale
 * @MODE_BAD: unspecअगरied reason
 * @MODE_ERROR: error condition
 *
 * This क्रमागत is used to filter out modes not supported by the driver/hardware
 * combination.
 */
क्रमागत drm_mode_status अणु
	MODE_OK = 0,
	MODE_HSYNC,
	MODE_VSYNC,
	MODE_H_ILLEGAL,
	MODE_V_ILLEGAL,
	MODE_BAD_WIDTH,
	MODE_NOMODE,
	MODE_NO_INTERLACE,
	MODE_NO_DBLESCAN,
	MODE_NO_VSCAN,
	MODE_MEM,
	MODE_VIRTUAL_X,
	MODE_VIRTUAL_Y,
	MODE_MEM_VIRT,
	MODE_NOCLOCK,
	MODE_CLOCK_HIGH,
	MODE_CLOCK_LOW,
	MODE_CLOCK_RANGE,
	MODE_BAD_HVALUE,
	MODE_BAD_VVALUE,
	MODE_BAD_VSCAN,
	MODE_HSYNC_NARROW,
	MODE_HSYNC_WIDE,
	MODE_HBLANK_NARROW,
	MODE_HBLANK_WIDE,
	MODE_VSYNC_NARROW,
	MODE_VSYNC_WIDE,
	MODE_VBLANK_NARROW,
	MODE_VBLANK_WIDE,
	MODE_PANEL,
	MODE_INTERLACE_WIDTH,
	MODE_ONE_WIDTH,
	MODE_ONE_HEIGHT,
	MODE_ONE_SIZE,
	MODE_NO_REDUCED,
	MODE_NO_STEREO,
	MODE_NO_420,
	MODE_STALE = -3,
	MODE_BAD = -2,
	MODE_ERROR = -1
पूर्ण;

#घोषणा DRM_MODE(nm, t, c, hd, hss, hse, ht, hsk, vd, vss, vse, vt, vs, f) \
	.name = nm, .status = 0, .type = (t), .घड़ी = (c), \
	.hdisplay = (hd), .hsync_start = (hss), .hsync_end = (hse), \
	.htotal = (ht), .hskew = (hsk), .vdisplay = (vd), \
	.vsync_start = (vss), .vsync_end = (vse), .vtotal = (vt), \
	.vscan = (vs), .flags = (f)

/**
 * DRM_SIMPLE_MODE - Simple display mode
 * @hd: Horizontal resolution, width
 * @vd: Vertical resolution, height
 * @hd_mm: Display width in millimeters
 * @vd_mm: Display height in millimeters
 *
 * This macro initializes a &drm_display_mode that only contains info about
 * resolution and physical size.
 */
#घोषणा DRM_SIMPLE_MODE(hd, vd, hd_mm, vd_mm) \
	.type = DRM_MODE_TYPE_DRIVER, .घड़ी = 1 /* pass validation */, \
	.hdisplay = (hd), .hsync_start = (hd), .hsync_end = (hd), \
	.htotal = (hd), .vdisplay = (vd), .vsync_start = (vd), \
	.vsync_end = (vd), .vtotal = (vd), .width_mm = (hd_mm), \
	.height_mm = (vd_mm)

#घोषणा CRTC_INTERLACE_HALVE_V	(1 << 0) /* halve V values क्रम पूर्णांकerlacing */
#घोषणा CRTC_STEREO_DOUBLE	(1 << 1) /* adjust timings क्रम stereo modes */
#घोषणा CRTC_NO_DBLSCAN		(1 << 2) /* करोn't adjust द्विगुनscan */
#घोषणा CRTC_NO_VSCAN		(1 << 3) /* करोn't adjust द्विगुनscan */
#घोषणा CRTC_STEREO_DOUBLE_ONLY	(CRTC_STEREO_DOUBLE | CRTC_NO_DBLSCAN | CRTC_NO_VSCAN)

#घोषणा DRM_MODE_FLAG_3D_MAX	DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF

#घोषणा DRM_MODE_MATCH_TIMINGS (1 << 0)
#घोषणा DRM_MODE_MATCH_CLOCK (1 << 1)
#घोषणा DRM_MODE_MATCH_FLAGS (1 << 2)
#घोषणा DRM_MODE_MATCH_3D_FLAGS (1 << 3)
#घोषणा DRM_MODE_MATCH_ASPECT_RATIO (1 << 4)

/**
 * काष्ठा drm_display_mode - DRM kernel-पूर्णांकernal display mode काष्ठाure
 * @hdisplay: horizontal display size
 * @hsync_start: horizontal sync start
 * @hsync_end: horizontal sync end
 * @htotal: horizontal total size
 * @hskew: horizontal skew?!
 * @vdisplay: vertical display size
 * @vsync_start: vertical sync start
 * @vsync_end: vertical sync end
 * @vtotal: vertical total size
 * @vscan: vertical scan?!
 * @crtc_hdisplay: hardware mode horizontal display size
 * @crtc_hblank_start: hardware mode horizontal blank start
 * @crtc_hblank_end: hardware mode horizontal blank end
 * @crtc_hsync_start: hardware mode horizontal sync start
 * @crtc_hsync_end: hardware mode horizontal sync end
 * @crtc_htotal: hardware mode horizontal total size
 * @crtc_hskew: hardware mode horizontal skew?!
 * @crtc_vdisplay: hardware mode vertical display size
 * @crtc_vblank_start: hardware mode vertical blank start
 * @crtc_vblank_end: hardware mode vertical blank end
 * @crtc_vsync_start: hardware mode vertical sync start
 * @crtc_vsync_end: hardware mode vertical sync end
 * @crtc_vtotal: hardware mode vertical total size
 *
 * This is the kernel API display mode inक्रमmation काष्ठाure. For the
 * user-space version see काष्ठा drm_mode_modeinfo.
 *
 * The horizontal and vertical timings are defined per the following diagram.
 *
 * ::
 *
 *
 *               Active                 Front           Sync           Back
 *              Region                 Porch                          Porch
 *     <-----------------------><----------------><-------------><-------------->
 *       //////////////////////|
 *      ////////////////////// |
 *     //////////////////////  |..................               ................
 *                                                _______________
 *     <----- [hv]display ----->
 *     <------------- [hv]sync_start ------------>
 *     <--------------------- [hv]sync_end --------------------->
 *     <-------------------------------- [hv]total ----------------------------->*
 *
 * This काष्ठाure contains two copies of timings. First are the plain timings,
 * which specअगरy the logical mode, as it would be क्रम a progressive 1:1 scanout
 * at the refresh rate userspace can observe through vblank बारtamps. Then
 * there's the hardware timings, which are corrected क्रम पूर्णांकerlacing,
 * द्विगुन-घड़ीing and similar things. They are provided as a convenience, and
 * can be appropriately computed using drm_mode_set_crtcinfo().
 *
 * For prपूर्णांकing you can use %DRM_MODE_FMT and DRM_MODE_ARG().
 */
काष्ठा drm_display_mode अणु
	/**
	 * @घड़ी:
	 *
	 * Pixel घड़ी in kHz.
	 */
	पूर्णांक घड़ी;		/* in kHz */
	u16 hdisplay;
	u16 hsync_start;
	u16 hsync_end;
	u16 htotal;
	u16 hskew;
	u16 vdisplay;
	u16 vsync_start;
	u16 vsync_end;
	u16 vtotal;
	u16 vscan;
	/**
	 * @flags:
	 *
	 * Sync and timing flags:
	 *
	 *  - DRM_MODE_FLAG_PHSYNC: horizontal sync is active high.
	 *  - DRM_MODE_FLAG_NHSYNC: horizontal sync is active low.
	 *  - DRM_MODE_FLAG_PVSYNC: vertical sync is active high.
	 *  - DRM_MODE_FLAG_NVSYNC: vertical sync is active low.
	 *  - DRM_MODE_FLAG_INTERLACE: mode is पूर्णांकerlaced.
	 *  - DRM_MODE_FLAG_DBLSCAN: mode uses द्विगुनscan.
	 *  - DRM_MODE_FLAG_CSYNC: mode uses composite sync.
	 *  - DRM_MODE_FLAG_PCSYNC: composite sync is active high.
	 *  - DRM_MODE_FLAG_NCSYNC: composite sync is active low.
	 *  - DRM_MODE_FLAG_HSKEW: hskew provided (not used?).
	 *  - DRM_MODE_FLAG_BCAST: <deprecated>
	 *  - DRM_MODE_FLAG_PIXMUX: <deprecated>
	 *  - DRM_MODE_FLAG_DBLCLK: द्विगुन-घड़ीed mode.
	 *  - DRM_MODE_FLAG_CLKDIV2: half-घड़ीed mode.
	 *
	 * Additionally there's flags to specअगरy how 3D modes are packed:
	 *
	 *  - DRM_MODE_FLAG_3D_NONE: normal, non-3D mode.
	 *  - DRM_MODE_FLAG_3D_FRAME_PACKING: 2 full frames क्रम left and right.
	 *  - DRM_MODE_FLAG_3D_FIELD_ALTERNATIVE: पूर्णांकerleaved like fields.
	 *  - DRM_MODE_FLAG_3D_LINE_ALTERNATIVE: पूर्णांकerleaved lines.
	 *  - DRM_MODE_FLAG_3D_SIDE_BY_SIDE_FULL: side-by-side full frames.
	 *  - DRM_MODE_FLAG_3D_L_DEPTH: ?
	 *  - DRM_MODE_FLAG_3D_L_DEPTH_GFX_GFX_DEPTH: ?
	 *  - DRM_MODE_FLAG_3D_TOP_AND_BOTTOM: frame split पूर्णांकo top and bottom
	 *    parts.
	 *  - DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF: frame split पूर्णांकo left and
	 *    right parts.
	 */
	u32 flags;

	/**
	 * @crtc_घड़ी:
	 *
	 * Actual pixel or करोt घड़ी in the hardware. This dअगरfers from the
	 * logical @घड़ी when e.g. using पूर्णांकerlacing, द्विगुन-घड़ीing, stereo
	 * modes or other fancy stuff that changes the timings and संकेतs
	 * actually sent over the wire.
	 *
	 * This is again in kHz.
	 *
	 * Note that with digital outमाला_दो like HDMI or DP there's usually a
	 * massive confusion between the करोt घड़ी and the संकेत घड़ी at the
	 * bit encoding level. Especially when a 8b/10b encoding is used and the
	 * dअगरference is exactly a factor of 10.
	 */
	पूर्णांक crtc_घड़ी;
	u16 crtc_hdisplay;
	u16 crtc_hblank_start;
	u16 crtc_hblank_end;
	u16 crtc_hsync_start;
	u16 crtc_hsync_end;
	u16 crtc_htotal;
	u16 crtc_hskew;
	u16 crtc_vdisplay;
	u16 crtc_vblank_start;
	u16 crtc_vblank_end;
	u16 crtc_vsync_start;
	u16 crtc_vsync_end;
	u16 crtc_vtotal;

	/**
	 * @width_mm:
	 *
	 * Addressable size of the output in mm, projectors should set this to
	 * 0.
	 */
	u16 width_mm;

	/**
	 * @height_mm:
	 *
	 * Addressable size of the output in mm, projectors should set this to
	 * 0.
	 */
	u16 height_mm;

	/**
	 * @type:
	 *
	 * A biपंचांगask of flags, mostly about the source of a mode. Possible flags
	 * are:
	 *
	 *  - DRM_MODE_TYPE_PREFERRED: Preferred mode, usually the native
	 *    resolution of an LCD panel. There should only be one preferred
	 *    mode per connector at any given समय.
	 *  - DRM_MODE_TYPE_DRIVER: Mode created by the driver, which is all of
	 *    them really. Drivers must set this bit क्रम all modes they create
	 *    and expose to userspace.
	 *  - DRM_MODE_TYPE_USERDEF: Mode defined or selected via the kernel
	 *    command line.
	 *
	 * Plus a big list of flags which shouldn't be used at all, but are
	 * still around since these flags are also used in the userspace ABI.
	 * We no दीर्घer accept modes with these types though:
	 *
	 *  - DRM_MODE_TYPE_BUILTIN: Meant क्रम hard-coded modes, unused.
	 *    Use DRM_MODE_TYPE_DRIVER instead.
	 *  - DRM_MODE_TYPE_DEFAULT: Again a leftover, use
	 *    DRM_MODE_TYPE_PREFERRED instead.
	 *  - DRM_MODE_TYPE_CLOCK_C and DRM_MODE_TYPE_CRTC_C: Define leftovers
	 *    which are stuck around क्रम hysterical raisins only. No one has an
	 *    idea what they were meant क्रम. Don't use.
	 */
	u8 type;

	/**
	 * @expose_to_userspace:
	 *
	 * Indicates whether the mode is to be exposed to the userspace.
	 * This is to मुख्यtain a set of exposed modes जबतक preparing
	 * user-mode's list in drm_mode_अ_लोonnector ioctl. The purpose of
	 * this only lies in the ioctl function, and is not to be used
	 * outside the function.
	 */
	bool expose_to_userspace;

	/**
	 * @head:
	 *
	 * काष्ठा list_head क्रम mode lists.
	 */
	काष्ठा list_head head;

	/**
	 * @name:
	 *
	 * Human-पढ़ोable name of the mode, filled out with drm_mode_set_name().
	 */
	अक्षर name[DRM_DISPLAY_MODE_LEN];

	/**
	 * @status:
	 *
	 * Status of the mode, used to filter out modes not supported by the
	 * hardware. See क्रमागत &drm_mode_status.
	 */
	क्रमागत drm_mode_status status;

	/**
	 * @picture_aspect_ratio:
	 *
	 * Field क्रम setting the HDMI picture aspect ratio of a mode.
	 */
	क्रमागत hdmi_picture_aspect picture_aspect_ratio;

पूर्ण;

/**
 * DRM_MODE_FMT - म_लिखो string क्रम &काष्ठा drm_display_mode
 */
#घोषणा DRM_MODE_FMT    "\"%s\": %d %d %d %d %d %d %d %d %d %d 0x%x 0x%x"

/**
 * DRM_MODE_ARG - म_लिखो arguments क्रम &काष्ठा drm_display_mode
 * @m: display mode
 */
#घोषणा DRM_MODE_ARG(m) \
	(m)->name, drm_mode_vrefresh(m), (m)->घड़ी, \
	(m)->hdisplay, (m)->hsync_start, (m)->hsync_end, (m)->htotal, \
	(m)->vdisplay, (m)->vsync_start, (m)->vsync_end, (m)->vtotal, \
	(m)->type, (m)->flags

#घोषणा obj_to_mode(x) container_of(x, काष्ठा drm_display_mode, base)

/**
 * drm_mode_is_stereo - check क्रम stereo mode flags
 * @mode: drm_display_mode to check
 *
 * Returns:
 * True अगर the mode is one of the stereo modes (like side-by-side), false अगर
 * not.
 */
अटल अंतरभूत bool drm_mode_is_stereo(स्थिर काष्ठा drm_display_mode *mode)
अणु
	वापस mode->flags & DRM_MODE_FLAG_3D_MASK;
पूर्ण

काष्ठा drm_connector;
काष्ठा drm_cmdline_mode;

काष्ठा drm_display_mode *drm_mode_create(काष्ठा drm_device *dev);
व्योम drm_mode_destroy(काष्ठा drm_device *dev, काष्ठा drm_display_mode *mode);
व्योम drm_mode_convert_to_umode(काष्ठा drm_mode_modeinfo *out,
			       स्थिर काष्ठा drm_display_mode *in);
पूर्णांक drm_mode_convert_umode(काष्ठा drm_device *dev,
			   काष्ठा drm_display_mode *out,
			   स्थिर काष्ठा drm_mode_modeinfo *in);
व्योम drm_mode_probed_add(काष्ठा drm_connector *connector, काष्ठा drm_display_mode *mode);
व्योम drm_mode_debug_prपूर्णांकmodeline(स्थिर काष्ठा drm_display_mode *mode);
bool drm_mode_is_420_only(स्थिर काष्ठा drm_display_info *display,
			  स्थिर काष्ठा drm_display_mode *mode);
bool drm_mode_is_420_also(स्थिर काष्ठा drm_display_info *display,
			  स्थिर काष्ठा drm_display_mode *mode);
bool drm_mode_is_420(स्थिर काष्ठा drm_display_info *display,
		     स्थिर काष्ठा drm_display_mode *mode);

काष्ठा drm_display_mode *drm_cvt_mode(काष्ठा drm_device *dev,
				      पूर्णांक hdisplay, पूर्णांक vdisplay, पूर्णांक vrefresh,
				      bool reduced, bool पूर्णांकerlaced,
				      bool margins);
काष्ठा drm_display_mode *drm_gtf_mode(काष्ठा drm_device *dev,
				      पूर्णांक hdisplay, पूर्णांक vdisplay, पूर्णांक vrefresh,
				      bool पूर्णांकerlaced, पूर्णांक margins);
काष्ठा drm_display_mode *drm_gtf_mode_complex(काष्ठा drm_device *dev,
					      पूर्णांक hdisplay, पूर्णांक vdisplay,
					      पूर्णांक vrefresh, bool पूर्णांकerlaced,
					      पूर्णांक margins,
					      पूर्णांक GTF_M, पूर्णांक GTF_2C,
					      पूर्णांक GTF_K, पूर्णांक GTF_2J);
व्योम drm_display_mode_from_videomode(स्थिर काष्ठा videomode *vm,
				     काष्ठा drm_display_mode *dmode);
व्योम drm_display_mode_to_videomode(स्थिर काष्ठा drm_display_mode *dmode,
				   काष्ठा videomode *vm);
व्योम drm_bus_flags_from_videomode(स्थिर काष्ठा videomode *vm, u32 *bus_flags);

#अगर defined(CONFIG_OF)
पूर्णांक of_get_drm_display_mode(काष्ठा device_node *np,
			    काष्ठा drm_display_mode *dmode, u32 *bus_flags,
			    पूर्णांक index);
#अन्यथा
अटल अंतरभूत पूर्णांक of_get_drm_display_mode(काष्ठा device_node *np,
					  काष्ठा drm_display_mode *dmode,
					  u32 *bus_flags, पूर्णांक index)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

व्योम drm_mode_set_name(काष्ठा drm_display_mode *mode);
पूर्णांक drm_mode_vrefresh(स्थिर काष्ठा drm_display_mode *mode);
व्योम drm_mode_get_hv_timing(स्थिर काष्ठा drm_display_mode *mode,
			    पूर्णांक *hdisplay, पूर्णांक *vdisplay);

व्योम drm_mode_set_crtcinfo(काष्ठा drm_display_mode *p,
			   पूर्णांक adjust_flags);
व्योम drm_mode_copy(काष्ठा drm_display_mode *dst,
		   स्थिर काष्ठा drm_display_mode *src);
काष्ठा drm_display_mode *drm_mode_duplicate(काष्ठा drm_device *dev,
					    स्थिर काष्ठा drm_display_mode *mode);
bool drm_mode_match(स्थिर काष्ठा drm_display_mode *mode1,
		    स्थिर काष्ठा drm_display_mode *mode2,
		    अचिन्हित पूर्णांक match_flags);
bool drm_mode_equal(स्थिर काष्ठा drm_display_mode *mode1,
		    स्थिर काष्ठा drm_display_mode *mode2);
bool drm_mode_equal_no_घड़ीs(स्थिर काष्ठा drm_display_mode *mode1,
			      स्थिर काष्ठा drm_display_mode *mode2);
bool drm_mode_equal_no_घड़ीs_no_stereo(स्थिर काष्ठा drm_display_mode *mode1,
					स्थिर काष्ठा drm_display_mode *mode2);

/* क्रम use by the crtc helper probe functions */
क्रमागत drm_mode_status drm_mode_validate_driver(काष्ठा drm_device *dev,
					      स्थिर काष्ठा drm_display_mode *mode);
क्रमागत drm_mode_status drm_mode_validate_size(स्थिर काष्ठा drm_display_mode *mode,
					    पूर्णांक maxX, पूर्णांक maxY);
क्रमागत drm_mode_status
drm_mode_validate_ycbcr420(स्थिर काष्ठा drm_display_mode *mode,
			   काष्ठा drm_connector *connector);
व्योम drm_mode_prune_invalid(काष्ठा drm_device *dev,
			    काष्ठा list_head *mode_list, bool verbose);
व्योम drm_mode_sort(काष्ठा list_head *mode_list);
व्योम drm_connector_list_update(काष्ठा drm_connector *connector);

/* parsing cmdline modes */
bool
drm_mode_parse_command_line_क्रम_connector(स्थिर अक्षर *mode_option,
					  स्थिर काष्ठा drm_connector *connector,
					  काष्ठा drm_cmdline_mode *mode);
काष्ठा drm_display_mode *
drm_mode_create_from_cmdline_mode(काष्ठा drm_device *dev,
				  काष्ठा drm_cmdline_mode *cmd);

#पूर्ण_अगर /* __DRM_MODES_H__ */
