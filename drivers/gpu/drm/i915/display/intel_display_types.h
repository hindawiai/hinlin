<शैली गुरु>
/*
 * Copyright (c) 2006 Dave Airlie <airlied@linux.ie>
 * Copyright (c) 2007-2008 Intel Corporation
 *   Jesse Barnes <jesse.barnes@पूर्णांकel.com>
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
 */

#अगर_अघोषित __INTEL_DISPLAY_TYPES_H__
#घोषणा __INTEL_DISPLAY_TYPES_H__

#समावेश <linux/async.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pwm.h>
#समावेश <linux/sched/घड़ी.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_dp_dual_mode_helper.h>
#समावेश <drm/drm_dp_mst_helper.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_rect.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/i915_mei_hdcp_पूर्णांकerface.h>
#समावेश <media/cec-notअगरier.h>

#समावेश "i915_drv.h"
#समावेश "intel_de.h"

काष्ठा drm_prपूर्णांकer;
काष्ठा __पूर्णांकel_global_objs_state;

/*
 * Display related stuff
 */

/* these are outमाला_दो from the chip - पूर्णांकegrated only
   बाह्यal chips are via DVO or SDVO output */
क्रमागत पूर्णांकel_output_type अणु
	INTEL_OUTPUT_UNUSED = 0,
	INTEL_OUTPUT_ANALOG = 1,
	INTEL_OUTPUT_DVO = 2,
	INTEL_OUTPUT_SDVO = 3,
	INTEL_OUTPUT_LVDS = 4,
	INTEL_OUTPUT_TVOUT = 5,
	INTEL_OUTPUT_HDMI = 6,
	INTEL_OUTPUT_DP = 7,
	INTEL_OUTPUT_EDP = 8,
	INTEL_OUTPUT_DSI = 9,
	INTEL_OUTPUT_DDI = 10,
	INTEL_OUTPUT_DP_MST = 11,
पूर्ण;

क्रमागत hdmi_क्रमce_audio अणु
	HDMI_AUDIO_OFF_DVI = -2,	/* no aux data क्रम HDMI-DVI converter */
	HDMI_AUDIO_OFF,			/* क्रमce turn off HDMI audio */
	HDMI_AUDIO_AUTO,		/* trust EDID */
	HDMI_AUDIO_ON,			/* क्रमce turn on HDMI audio */
पूर्ण;

/* "Broadcast RGB" property */
क्रमागत पूर्णांकel_broadcast_rgb अणु
	INTEL_BROADCAST_RGB_AUTO,
	INTEL_BROADCAST_RGB_FULL,
	INTEL_BROADCAST_RGB_LIMITED,
पूर्ण;

काष्ठा पूर्णांकel_fb_view अणु
	/*
	 * The remap inक्रमmation used in the remapped and rotated views to
	 * create the DMA scatter-gather list क्रम each FB color plane. This sg
	 * list is created aदीर्घ with the view type (gtt.type) specअगरic
	 * i915_vma object and contains the list of FB object pages (reordered
	 * in the rotated view) that are visible in the view.
	 * In the normal view the FB object's backing store sg list is used
	 * directly and hence the remap inक्रमmation here is not used.
	 */
	काष्ठा i915_ggtt_view gtt;

	/*
	 * The GTT view (gtt.type) specअगरic inक्रमmation क्रम each FB color
	 * plane. In the normal GTT view all क्रमmats (up to 4 color planes),
	 * in the rotated and remapped GTT view all no-CCS क्रमmats (up to 2
	 * color planes) are supported.
	 *
	 * TODO: add support क्रम CCS क्रमmats in the remapped GTT view.
	 *
	 * The view inक्रमmation shared by all FB color planes in the FB,
	 * like dst x/y and src/dst width, is stored separately in
	 * पूर्णांकel_plane_state.
	 */
	काष्ठा i915_color_plane_view अणु
		u32 offset;
		अचिन्हित पूर्णांक x, y;
		/*
		 * Plane stride in:
		 *   bytes क्रम 0/180 degree rotation
		 *   pixels क्रम 90/270 degree rotation
		 */
		अचिन्हित पूर्णांक stride;
	पूर्ण color_plane[4];
पूर्ण;

काष्ठा पूर्णांकel_framebuffer अणु
	काष्ठा drm_framebuffer base;
	काष्ठा पूर्णांकel_frontbuffer *frontbuffer;

	/* Params to remap the FB pages and program the plane रेजिस्टरs in each view. */
	काष्ठा पूर्णांकel_fb_view normal_view;
	काष्ठा पूर्णांकel_fb_view rotated_view;
	काष्ठा पूर्णांकel_fb_view remapped_view;
पूर्ण;

काष्ठा पूर्णांकel_fbdev अणु
	काष्ठा drm_fb_helper helper;
	काष्ठा पूर्णांकel_framebuffer *fb;
	काष्ठा i915_vma *vma;
	अचिन्हित दीर्घ vma_flags;
	async_cookie_t cookie;
	पूर्णांक preferred_bpp;

	/* Whether or not fbdev hpd processing is temporarily suspended */
	bool hpd_suspended : 1;
	/* Set when a hotplug was received जबतक HPD processing was
	 * suspended
	 */
	bool hpd_रुकोing : 1;

	/* Protects hpd_suspended */
	काष्ठा mutex hpd_lock;
पूर्ण;

क्रमागत पूर्णांकel_hotplug_state अणु
	INTEL_HOTPLUG_UNCHANGED,
	INTEL_HOTPLUG_CHANGED,
	INTEL_HOTPLUG_RETRY,
पूर्ण;

काष्ठा पूर्णांकel_encoder अणु
	काष्ठा drm_encoder base;

	क्रमागत पूर्णांकel_output_type type;
	क्रमागत port port;
	u16 cloneable;
	u8 pipe_mask;
	क्रमागत पूर्णांकel_hotplug_state (*hotplug)(काष्ठा पूर्णांकel_encoder *encoder,
					    काष्ठा पूर्णांकel_connector *connector);
	क्रमागत पूर्णांकel_output_type (*compute_output_type)(काष्ठा पूर्णांकel_encoder *,
						      काष्ठा पूर्णांकel_crtc_state *,
						      काष्ठा drm_connector_state *);
	पूर्णांक (*compute_config)(काष्ठा पूर्णांकel_encoder *,
			      काष्ठा पूर्णांकel_crtc_state *,
			      काष्ठा drm_connector_state *);
	पूर्णांक (*compute_config_late)(काष्ठा पूर्णांकel_encoder *,
				   काष्ठा पूर्णांकel_crtc_state *,
				   काष्ठा drm_connector_state *);
	व्योम (*update_prepare)(काष्ठा पूर्णांकel_atomic_state *,
			       काष्ठा पूर्णांकel_encoder *,
			       काष्ठा पूर्णांकel_crtc *);
	व्योम (*pre_pll_enable)(काष्ठा पूर्णांकel_atomic_state *,
			       काष्ठा पूर्णांकel_encoder *,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *,
			       स्थिर काष्ठा drm_connector_state *);
	व्योम (*pre_enable)(काष्ठा पूर्णांकel_atomic_state *,
			   काष्ठा पूर्णांकel_encoder *,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *,
			   स्थिर काष्ठा drm_connector_state *);
	व्योम (*enable)(काष्ठा पूर्णांकel_atomic_state *,
		       काष्ठा पूर्णांकel_encoder *,
		       स्थिर काष्ठा पूर्णांकel_crtc_state *,
		       स्थिर काष्ठा drm_connector_state *);
	व्योम (*update_complete)(काष्ठा पूर्णांकel_atomic_state *,
				काष्ठा पूर्णांकel_encoder *,
				काष्ठा पूर्णांकel_crtc *);
	व्योम (*disable)(काष्ठा पूर्णांकel_atomic_state *,
			काष्ठा पूर्णांकel_encoder *,
			स्थिर काष्ठा पूर्णांकel_crtc_state *,
			स्थिर काष्ठा drm_connector_state *);
	व्योम (*post_disable)(काष्ठा पूर्णांकel_atomic_state *,
			     काष्ठा पूर्णांकel_encoder *,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *,
			     स्थिर काष्ठा drm_connector_state *);
	व्योम (*post_pll_disable)(काष्ठा पूर्णांकel_atomic_state *,
				 काष्ठा पूर्णांकel_encoder *,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *,
				 स्थिर काष्ठा drm_connector_state *);
	व्योम (*update_pipe)(काष्ठा पूर्णांकel_atomic_state *,
			    काष्ठा पूर्णांकel_encoder *,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *,
			    स्थिर काष्ठा drm_connector_state *);
	/* Read out the current hw state of this connector, वापसing true अगर
	 * the encoder is active. If the encoder is enabled it also set the pipe
	 * it is connected to in the pipe parameter. */
	bool (*get_hw_state)(काष्ठा पूर्णांकel_encoder *, क्रमागत pipe *pipe);
	/* Reस्थिरructs the equivalent mode flags क्रम the current hardware
	 * state. This must be called _after_ display->get_pipe_config has
	 * pre-filled the pipe config. Note that पूर्णांकel_encoder->base.crtc must
	 * be set correctly beक्रमe calling this function. */
	व्योम (*get_config)(काष्ठा पूर्णांकel_encoder *,
			   काष्ठा पूर्णांकel_crtc_state *pipe_config);

	/*
	 * Optional hook called during init/resume to sync any state
	 * stored in the encoder (eg. DP link parameters) wrt. the HW state.
	 */
	व्योम (*sync_state)(काष्ठा पूर्णांकel_encoder *encoder,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);

	/*
	 * Optional hook, वापसing true अगर this encoder allows a fastset
	 * during the initial commit, false otherwise.
	 */
	bool (*initial_fastset_check)(काष्ठा पूर्णांकel_encoder *encoder,
				      काष्ठा पूर्णांकel_crtc_state *crtc_state);

	/*
	 * Acquires the घातer करोमुख्यs needed क्रम an active encoder during
	 * hardware state पढ़ोout.
	 */
	व्योम (*get_घातer_करोमुख्यs)(काष्ठा पूर्णांकel_encoder *encoder,
				  काष्ठा पूर्णांकel_crtc_state *crtc_state);
	/*
	 * Called during प्रणाली suspend after all pending requests क्रम the
	 * encoder are flushed (क्रम example क्रम DP AUX transactions) and
	 * device पूर्णांकerrupts are disabled.
	 */
	व्योम (*suspend)(काष्ठा पूर्णांकel_encoder *);
	/*
	 * Called during प्रणाली reboot/shutकरोwn after all the
	 * encoders have been disabled and suspended.
	 */
	व्योम (*shutकरोwn)(काष्ठा पूर्णांकel_encoder *encoder);
	/*
	 * Enable/disable the घड़ी to the port.
	 */
	व्योम (*enable_घड़ी)(काष्ठा पूर्णांकel_encoder *encoder,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
	व्योम (*disable_घड़ी)(काष्ठा पूर्णांकel_encoder *encoder);
	/*
	 * Returns whether the port घड़ी is enabled or not.
	 */
	bool (*is_घड़ी_enabled)(काष्ठा पूर्णांकel_encoder *encoder);
	क्रमागत hpd_pin hpd_pin;
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य घातer_करोमुख्य;
	/* क्रम communication with audio component; रक्षित by av_mutex */
	स्थिर काष्ठा drm_connector *audio_connector;

	/* VBT inक्रमmation क्रम this encoder (may be शून्य क्रम older platक्रमms) */
	स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata;
पूर्ण;

काष्ठा पूर्णांकel_panel_bl_funcs अणु
	/* Connector and platक्रमm specअगरic backlight functions */
	पूर्णांक (*setup)(काष्ठा पूर्णांकel_connector *connector, क्रमागत pipe pipe);
	u32 (*get)(काष्ठा पूर्णांकel_connector *connector, क्रमागत pipe pipe);
	व्योम (*set)(स्थिर काष्ठा drm_connector_state *conn_state, u32 level);
	व्योम (*disable)(स्थिर काष्ठा drm_connector_state *conn_state, u32 level);
	व्योम (*enable)(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		       स्थिर काष्ठा drm_connector_state *conn_state, u32 level);
	u32 (*hz_to_pwm)(काष्ठा पूर्णांकel_connector *connector, u32 hz);
पूर्ण;

काष्ठा पूर्णांकel_panel अणु
	काष्ठा drm_display_mode *fixed_mode;
	काष्ठा drm_display_mode *करोwnघड़ी_mode;

	/* backlight */
	काष्ठा अणु
		bool present;
		u32 level;
		u32 min;
		u32 max;
		bool enabled;
		bool combination_mode;	/* gen 2/4 only */
		bool active_low_pwm;
		bool alternate_pwm_increment;	/* lpt+ */

		/* PWM chip */
		u32 pwm_level_min;
		u32 pwm_level_max;
		bool pwm_enabled;
		bool util_pin_active_low;	/* bxt+ */
		u8 controller;		/* bxt+ only */
		काष्ठा pwm_device *pwm;
		काष्ठा pwm_state pwm_state;

		/* DPCD backlight */
		जोड़ अणु
			काष्ठा अणु
				u8 pwmgen_bit_count;
			पूर्ण vesa;
			काष्ठा अणु
				bool sdr_uses_aux;
			पूर्ण पूर्णांकel;
		पूर्ण edp;

		काष्ठा backlight_device *device;

		स्थिर काष्ठा पूर्णांकel_panel_bl_funcs *funcs;
		स्थिर काष्ठा पूर्णांकel_panel_bl_funcs *pwm_funcs;
		व्योम (*घातer)(काष्ठा पूर्णांकel_connector *, bool enable);
	पूर्ण backlight;
पूर्ण;

काष्ठा पूर्णांकel_digital_port;

क्रमागत check_link_response अणु
	HDCP_LINK_PROTECTED	= 0,
	HDCP_TOPOLOGY_CHANGE,
	HDCP_LINK_INTEGRITY_FAILURE,
	HDCP_REAUTH_REQUEST
पूर्ण;

/*
 * This काष्ठाure serves as a translation layer between the generic HDCP code
 * and the bus-specअगरic code. What that means is that HDCP over HDMI dअगरfers
 * from HDCP over DP, so to account क्रम these dअगरferences, we need to
 * communicate with the receiver through this shim.
 *
 * For completeness, the 2 buses dअगरfer in the following ways:
 *	- DP AUX vs. DDC
 *		HDCP रेजिस्टरs on the receiver are set via DP AUX क्रम DP, and
 *		they are set via DDC क्रम HDMI.
 *	- Receiver रेजिस्टर offsets
 *		The offsets of the रेजिस्टरs are dअगरferent क्रम DP vs. HDMI
 *	- Receiver रेजिस्टर masks/offsets
 *		For instance, the पढ़ोy bit क्रम the KSV fअगरo is in a dअगरferent
 *		place on DP vs HDMI
 *	- Receiver रेजिस्टर names
 *		Seriously. In the DP spec, the 16-bit रेजिस्टर containing
 *		करोwnstream inक्रमmation is called BINFO, on HDMI it's called
 *		BSTATUS. To confuse matters further, DP has a BSTATUS रेजिस्टर
 *		with a completely dअगरferent definition.
 *	- KSV FIFO
 *		On HDMI, the ksv fअगरo is पढ़ो all at once, whereas on DP it must
 *		be पढ़ो 3 keys at a समय
 *	- Aksv output
 *		Since Aksv is hidden in hardware, there's dअगरferent procedures
 *		to send it over DP AUX vs DDC
 */
काष्ठा पूर्णांकel_hdcp_shim अणु
	/* Outमाला_दो the transmitter's An and Aksv values to the receiver. */
	पूर्णांक (*ग_लिखो_an_aksv)(काष्ठा पूर्णांकel_digital_port *dig_port, u8 *an);

	/* Reads the receiver's key selection vector */
	पूर्णांक (*पढ़ो_bksv)(काष्ठा पूर्णांकel_digital_port *dig_port, u8 *bksv);

	/*
	 * Reads BINFO from DP receivers and BSTATUS from HDMI receivers. The
	 * definitions are the same in the respective specs, but the names are
	 * dअगरferent. Call it BSTATUS since that's the name the HDMI spec
	 * uses and it was there first.
	 */
	पूर्णांक (*पढ़ो_bstatus)(काष्ठा पूर्णांकel_digital_port *dig_port,
			    u8 *bstatus);

	/* Determines whether a repeater is present करोwnstream */
	पूर्णांक (*repeater_present)(काष्ठा पूर्णांकel_digital_port *dig_port,
				bool *repeater_present);

	/* Reads the receiver's Ri' value */
	पूर्णांक (*पढ़ो_ri_prime)(काष्ठा पूर्णांकel_digital_port *dig_port, u8 *ri);

	/* Determines अगर the receiver's KSV FIFO is पढ़ोy क्रम consumption */
	पूर्णांक (*पढ़ो_ksv_पढ़ोy)(काष्ठा पूर्णांकel_digital_port *dig_port,
			      bool *ksv_पढ़ोy);

	/* Reads the ksv fअगरo क्रम num_करोwnstream devices */
	पूर्णांक (*पढ़ो_ksv_fअगरo)(काष्ठा पूर्णांकel_digital_port *dig_port,
			     पूर्णांक num_करोwnstream, u8 *ksv_fअगरo);

	/* Reads a 32-bit part of V' from the receiver */
	पूर्णांक (*पढ़ो_v_prime_part)(काष्ठा पूर्णांकel_digital_port *dig_port,
				 पूर्णांक i, u32 *part);

	/* Enables HDCP संकेतling on the port */
	पूर्णांक (*toggle_संकेतling)(काष्ठा पूर्णांकel_digital_port *dig_port,
				 क्रमागत transcoder cpu_transcoder,
				 bool enable);

	/* Enable/Disable stream encryption on DP MST Transport Link */
	पूर्णांक (*stream_encryption)(काष्ठा पूर्णांकel_connector *connector,
				 bool enable);

	/* Ensures the link is still रक्षित */
	bool (*check_link)(काष्ठा पूर्णांकel_digital_port *dig_port,
			   काष्ठा पूर्णांकel_connector *connector);

	/* Detects panel's hdcp capability. This is optional क्रम HDMI. */
	पूर्णांक (*hdcp_capable)(काष्ठा पूर्णांकel_digital_port *dig_port,
			    bool *hdcp_capable);

	/* HDCP adaptation(DP/HDMI) required on the port */
	क्रमागत hdcp_wired_protocol protocol;

	/* Detects whether sink is HDCP2.2 capable */
	पूर्णांक (*hdcp_2_2_capable)(काष्ठा पूर्णांकel_digital_port *dig_port,
				bool *capable);

	/* Detects whether a HDCP 1.4 sink connected in MST topology */
	पूर्णांक (*streams_type1_capable)(काष्ठा पूर्णांकel_connector *connector,
				     bool *capable);

	/* Write HDCP2.2 messages */
	पूर्णांक (*ग_लिखो_2_2_msg)(काष्ठा पूर्णांकel_digital_port *dig_port,
			     व्योम *buf, माप_प्रकार size);

	/* Read HDCP2.2 messages */
	पूर्णांक (*पढ़ो_2_2_msg)(काष्ठा पूर्णांकel_digital_port *dig_port,
			    u8 msg_id, व्योम *buf, माप_प्रकार size);

	/*
	 * Implementation of DP HDCP2.2 Errata क्रम the communication of stream
	 * type to Receivers. In DP HDCP2.2 Stream type is one of the input to
	 * the HDCP2.2 Cipher क्रम En/De-Cryption. Not applicable क्रम HDMI.
	 */
	पूर्णांक (*config_stream_type)(काष्ठा पूर्णांकel_digital_port *dig_port,
				  bool is_repeater, u8 type);

	/* Enable/Disable HDCP 2.2 stream encryption on DP MST Transport Link */
	पूर्णांक (*stream_2_2_encryption)(काष्ठा पूर्णांकel_connector *connector,
				     bool enable);

	/* HDCP2.2 Link Integrity Check */
	पूर्णांक (*check_2_2_link)(काष्ठा पूर्णांकel_digital_port *dig_port,
			      काष्ठा पूर्णांकel_connector *connector);
पूर्ण;

काष्ठा पूर्णांकel_hdcp अणु
	स्थिर काष्ठा पूर्णांकel_hdcp_shim *shim;
	/* Mutex क्रम hdcp state of the connector */
	काष्ठा mutex mutex;
	u64 value;
	काष्ठा delayed_work check_work;
	काष्ठा work_काष्ठा prop_work;

	/* HDCP1.4 Encryption status */
	bool hdcp_encrypted;

	/* HDCP2.2 related definitions */
	/* Flag indicates whether this connector supports HDCP2.2 or not. */
	bool hdcp2_supported;

	/* HDCP2.2 Encryption status */
	bool hdcp2_encrypted;

	/*
	 * Content Stream Type defined by content owner. TYPE0(0x0) content can
	 * flow in the link रक्षित by HDCP2.2 or HDCP1.4, where as TYPE1(0x1)
	 * content can flow only through a link रक्षित by HDCP2.2.
	 */
	u8 content_type;

	bool is_paired;
	bool is_repeater;

	/*
	 * Count of ReceiverID_List received. Initialized to 0 at AKE_INIT.
	 * Incremented after processing the RepeaterAuth_Send_ReceiverID_List.
	 * When it rolls over re-auth has to be triggered.
	 */
	u32 seq_num_v;

	/*
	 * Count of RepeaterAuth_Stream_Manage msg propagated.
	 * Initialized to 0 on AKE_INIT. Incremented after every successful
	 * transmission of RepeaterAuth_Stream_Manage message. When it rolls
	 * over re-Auth has to be triggered.
	 */
	u32 seq_num_m;

	/*
	 * Work queue to संकेत the CP_IRQ. Used क्रम the रुकोers to पढ़ो the
	 * available inक्रमmation from HDCP DP sink.
	 */
	रुको_queue_head_t cp_irq_queue;
	atomic_t cp_irq_count;
	पूर्णांक cp_irq_count_cached;

	/*
	 * HDCP रेजिस्टर access क्रम gen12+ need the transcoder associated.
	 * Transcoder attached to the connector could be changed at modeset.
	 * Hence caching the transcoder here.
	 */
	क्रमागत transcoder cpu_transcoder;
	/* Only used क्रम DP MST stream encryption */
	क्रमागत transcoder stream_transcoder;
पूर्ण;

काष्ठा पूर्णांकel_connector अणु
	काष्ठा drm_connector base;
	/*
	 * The fixed encoder this connector is connected to.
	 */
	काष्ठा पूर्णांकel_encoder *encoder;

	/* ACPI device id क्रम ACPI and driver cooperation */
	u32 acpi_device_id;

	/* Reads out the current hw, वापसing true अगर the connector is enabled
	 * and active (i.e. dpms ON state). */
	bool (*get_hw_state)(काष्ठा पूर्णांकel_connector *);

	/* Panel info क्रम eDP and LVDS */
	काष्ठा पूर्णांकel_panel panel;

	/* Cached EDID क्रम eDP and LVDS. May hold ERR_PTR क्रम invalid EDID. */
	काष्ठा edid *edid;
	काष्ठा edid *detect_edid;

	/* Number of बार hotplug detection was tried after an HPD पूर्णांकerrupt */
	पूर्णांक hotplug_retries;

	/* since POLL and HPD connectors may use the same HPD line keep the native
	   state of connector->polled in हाल hotplug storm detection changes it */
	u8 polled;

	काष्ठा drm_dp_mst_port *port;

	काष्ठा पूर्णांकel_dp *mst_port;

	/* Work काष्ठा to schedule a uevent on link train failure */
	काष्ठा work_काष्ठा modeset_retry_work;

	काष्ठा पूर्णांकel_hdcp hdcp;
पूर्ण;

काष्ठा पूर्णांकel_digital_connector_state अणु
	काष्ठा drm_connector_state base;

	क्रमागत hdmi_क्रमce_audio क्रमce_audio;
	पूर्णांक broadcast_rgb;
पूर्ण;

#घोषणा to_पूर्णांकel_digital_connector_state(x) container_of(x, काष्ठा पूर्णांकel_digital_connector_state, base)

काष्ठा dpll अणु
	/* given values */
	पूर्णांक n;
	पूर्णांक m1, m2;
	पूर्णांक p1, p2;
	/* derived values */
	पूर्णांक	करोt;
	पूर्णांक	vco;
	पूर्णांक	m;
	पूर्णांक	p;
पूर्ण;

काष्ठा पूर्णांकel_atomic_state अणु
	काष्ठा drm_atomic_state base;

	पूर्णांकel_wakeref_t wakeref;

	काष्ठा __पूर्णांकel_global_objs_state *global_objs;
	पूर्णांक num_global_objs;

	bool dpll_set, modeset;

	काष्ठा पूर्णांकel_shared_dpll_state shared_dpll[I915_NUM_PLLS];

	/*
	 * Current watermarks can't be trusted during hardware पढ़ोout, so
	 * करोn't bother calculating पूर्णांकermediate watermarks.
	 */
	bool skip_पूर्णांकermediate_wm;

	bool rps_पूर्णांकeractive;

	काष्ठा i915_sw_fence commit_पढ़ोy;

	काष्ठा llist_node मुक्तd;
पूर्ण;

काष्ठा पूर्णांकel_plane_state अणु
	काष्ठा drm_plane_state uapi;

	/*
	 * actual hardware state, the state we program to the hardware.
	 * The following members are used to verअगरy the hardware state:
	 * During initial hw पढ़ोout, they need to be copied from uapi.
	 */
	काष्ठा अणु
		काष्ठा drm_crtc *crtc;
		काष्ठा drm_framebuffer *fb;

		u16 alpha;
		u16 pixel_blend_mode;
		अचिन्हित पूर्णांक rotation;
		क्रमागत drm_color_encoding color_encoding;
		क्रमागत drm_color_range color_range;
		क्रमागत drm_scaling_filter scaling_filter;
	पूर्ण hw;

	काष्ठा i915_vma *vma;
	अचिन्हित दीर्घ flags;
#घोषणा PLANE_HAS_FENCE BIT(0)

	काष्ठा पूर्णांकel_fb_view view;

	/* plane control रेजिस्टर */
	u32 ctl;

	/* plane color control रेजिस्टर */
	u32 color_ctl;

	/* chroma upsampler control रेजिस्टर */
	u32 cus_ctl;

	/*
	 * scaler_id
	 *    = -1 : not using a scaler
	 *    >=  0 : using a scalers
	 *
	 * plane requiring a scaler:
	 *   - During check_plane, its bit is set in
	 *     crtc_state->scaler_state.scaler_users by calling helper function
	 *     update_scaler_plane.
	 *   - scaler_id indicates the scaler it got asचिन्हित.
	 *
	 * plane करोesn't require a scaler:
	 *   - this can happen when scaling is no more required or plane simply
	 *     got disabled.
	 *   - During check_plane, corresponding bit is reset in
	 *     crtc_state->scaler_state.scaler_users by calling helper function
	 *     update_scaler_plane.
	 */
	पूर्णांक scaler_id;

	/*
	 * planar_linked_plane:
	 *
	 * ICL planar क्रमmats require 2 planes that are updated as pairs.
	 * This member is used to make sure the other plane is also updated
	 * when required, and क्रम update_slave() to find the correct
	 * plane_state to pass as argument.
	 */
	काष्ठा पूर्णांकel_plane *planar_linked_plane;

	/*
	 * planar_slave:
	 * If set करोn't update use the linked plane's state क्रम updating
	 * this plane during atomic commit with the update_slave() callback.
	 *
	 * It's also used by the watermark code to ignore wm calculations on
	 * this plane. They're calculated by the linked plane's wm code.
	 */
	u32 planar_slave;

	काष्ठा drm_पूर्णांकel_sprite_colorkey ckey;

	काष्ठा drm_rect psr2_sel_fetch_area;

	/* Clear Color Value */
	u64 ccval;
पूर्ण;

काष्ठा पूर्णांकel_initial_plane_config अणु
	काष्ठा पूर्णांकel_framebuffer *fb;
	काष्ठा i915_vma *vma;
	अचिन्हित पूर्णांक tiling;
	पूर्णांक size;
	u32 base;
	u8 rotation;
पूर्ण;

काष्ठा पूर्णांकel_scaler अणु
	पूर्णांक in_use;
	u32 mode;
पूर्ण;

काष्ठा पूर्णांकel_crtc_scaler_state अणु
#घोषणा SKL_NUM_SCALERS 2
	काष्ठा पूर्णांकel_scaler scalers[SKL_NUM_SCALERS];

	/*
	 * scaler_users: keeps track of users requesting scalers on this crtc.
	 *
	 *     If a bit is set, a user is using a scaler.
	 *     Here user can be a plane or crtc as defined below:
	 *       bits 0-30 - plane (bit position is index from drm_plane_index)
	 *       bit 31    - crtc
	 *
	 * Instead of creating a new index to cover planes and crtc, using
	 * existing drm_plane_index क्रम planes which is well less than 31
	 * planes and bit 31 क्रम crtc. This should be fine to cover all
	 * our platक्रमms.
	 *
	 * पूर्णांकel_atomic_setup_scalers will setup available scalers to users
	 * requesting scalers. It will gracefully fail अगर request exceeds
	 * avilability.
	 */
#घोषणा SKL_CRTC_INDEX 31
	अचिन्हित scaler_users;

	/* scaler used by crtc क्रम panel fitting purpose */
	पूर्णांक scaler_id;
पूर्ण;

/* अणुcrtc,crtc_stateपूर्ण->mode_flags */
/* Flag to get scanline using frame समय stamps */
#घोषणा I915_MODE_FLAG_GET_SCANLINE_FROM_TIMESTAMP (1<<1)
/* Flag to use the scanline counter instead of the pixel counter */
#घोषणा I915_MODE_FLAG_USE_SCANLINE_COUNTER (1<<2)
/*
 * TE0 or TE1 flag is set अगर the crtc has a DSI encoder which
 * is operating in command mode.
 * Flag to use TE from DSI0 instead of VBI in command mode
 */
#घोषणा I915_MODE_FLAG_DSI_USE_TE0 (1<<3)
/* Flag to use TE from DSI1 instead of VBI in command mode */
#घोषणा I915_MODE_FLAG_DSI_USE_TE1 (1<<4)
/* Flag to indicate mipi dsi periodic command mode where we करो not get TE */
#घोषणा I915_MODE_FLAG_DSI_PERIODIC_CMD_MODE (1<<5)
/* Do tricks to make vblank बारtamps sane with VRR? */
#घोषणा I915_MODE_FLAG_VRR (1<<6)

काष्ठा पूर्णांकel_wm_level अणु
	bool enable;
	u32 pri_val;
	u32 spr_val;
	u32 cur_val;
	u32 fbc_val;
पूर्ण;

काष्ठा पूर्णांकel_pipe_wm अणु
	काष्ठा पूर्णांकel_wm_level wm[5];
	bool fbc_wm_enabled;
	bool pipe_enabled;
	bool sprites_enabled;
	bool sprites_scaled;
पूर्ण;

काष्ठा skl_wm_level अणु
	u16 min_ddb_alloc;
	u16 blocks;
	u8 lines;
	bool enable;
	bool ignore_lines;
	bool can_sagv;
पूर्ण;

काष्ठा skl_plane_wm अणु
	काष्ठा skl_wm_level wm[8];
	काष्ठा skl_wm_level uv_wm[8];
	काष्ठा skl_wm_level trans_wm;
	काष्ठा अणु
		काष्ठा skl_wm_level wm0;
		काष्ठा skl_wm_level trans_wm;
	पूर्ण sagv;
	bool is_planar;
पूर्ण;

काष्ठा skl_pipe_wm अणु
	काष्ठा skl_plane_wm planes[I915_MAX_PLANES];
	bool use_sagv_wm;
पूर्ण;

क्रमागत vlv_wm_level अणु
	VLV_WM_LEVEL_PM2,
	VLV_WM_LEVEL_PM5,
	VLV_WM_LEVEL_DDR_DVFS,
	NUM_VLV_WM_LEVELS,
पूर्ण;

काष्ठा vlv_wm_state अणु
	काष्ठा g4x_pipe_wm wm[NUM_VLV_WM_LEVELS];
	काष्ठा g4x_sr_wm sr[NUM_VLV_WM_LEVELS];
	u8 num_levels;
	bool cxsr;
पूर्ण;

काष्ठा vlv_fअगरo_state अणु
	u16 plane[I915_MAX_PLANES];
पूर्ण;

क्रमागत g4x_wm_level अणु
	G4X_WM_LEVEL_NORMAL,
	G4X_WM_LEVEL_SR,
	G4X_WM_LEVEL_HPLL,
	NUM_G4X_WM_LEVELS,
पूर्ण;

काष्ठा g4x_wm_state अणु
	काष्ठा g4x_pipe_wm wm;
	काष्ठा g4x_sr_wm sr;
	काष्ठा g4x_sr_wm hpll;
	bool cxsr;
	bool hpll_en;
	bool fbc_en;
पूर्ण;

काष्ठा पूर्णांकel_crtc_wm_state अणु
	जोड़ अणु
		/*
		 * raw:
		 * The "raw" watermark values produced by the क्रमmula
		 * given the plane's current state. They करो not consider
		 * how much FIFO is actually allocated क्रम each plane.
		 *
		 * optimal:
		 * The "optimal" watermark values given the current
		 * state of the planes and the amount of FIFO
		 * allocated to each, ignoring any previous state
		 * of the planes.
		 *
		 * पूर्णांकermediate:
		 * The "intermediate" watermark values when transitioning
		 * between the old and new "optimal" values. Used when
		 * the watermark रेजिस्टरs are single buffered and hence
		 * their state changes asynchronously with regards to the
		 * actual plane रेजिस्टरs. These are essentially the
		 * worst हाल combination of the old and new "optimal"
		 * watermarks, which are thereक्रमe safe to use when the
		 * plane is in either its old or new state.
		 */
		काष्ठा अणु
			काष्ठा पूर्णांकel_pipe_wm पूर्णांकermediate;
			काष्ठा पूर्णांकel_pipe_wm optimal;
		पूर्ण ilk;

		काष्ठा अणु
			काष्ठा skl_pipe_wm raw;
			/* gen9+ only needs 1-step wm programming */
			काष्ठा skl_pipe_wm optimal;
			काष्ठा skl_ddb_entry ddb;
			काष्ठा skl_ddb_entry plane_ddb_y[I915_MAX_PLANES];
			काष्ठा skl_ddb_entry plane_ddb_uv[I915_MAX_PLANES];
		पूर्ण skl;

		काष्ठा अणु
			काष्ठा g4x_pipe_wm raw[NUM_VLV_WM_LEVELS]; /* not inverted */
			काष्ठा vlv_wm_state पूर्णांकermediate; /* inverted */
			काष्ठा vlv_wm_state optimal; /* inverted */
			काष्ठा vlv_fअगरo_state fअगरo_state;
		पूर्ण vlv;

		काष्ठा अणु
			काष्ठा g4x_pipe_wm raw[NUM_G4X_WM_LEVELS];
			काष्ठा g4x_wm_state पूर्णांकermediate;
			काष्ठा g4x_wm_state optimal;
		पूर्ण g4x;
	पूर्ण;

	/*
	 * Platक्रमms with two-step watermark programming will need to
	 * update watermark programming post-vblank to चयन from the
	 * safe पूर्णांकermediate watermarks to the optimal final
	 * watermarks.
	 */
	bool need_postvbl_update;
पूर्ण;

क्रमागत पूर्णांकel_output_क्रमmat अणु
	INTEL_OUTPUT_FORMAT_RGB,
	INTEL_OUTPUT_FORMAT_YCBCR420,
	INTEL_OUTPUT_FORMAT_YCBCR444,
पूर्ण;

काष्ठा पूर्णांकel_crtc_state अणु
	/*
	 * uapi (drm) state. This is the software state shown to userspace.
	 * In particular, the following members are used क्रम bookkeeping:
	 * - crtc
	 * - state
	 * - *_changed
	 * - event
	 * - commit
	 * - mode_blob
	 */
	काष्ठा drm_crtc_state uapi;

	/*
	 * actual hardware state, the state we program to the hardware.
	 * The following members are used to verअगरy the hardware state:
	 * - enable
	 * - active
	 * - mode / pipe_mode / adjusted_mode
	 * - color property blobs.
	 *
	 * During initial hw पढ़ोout, they need to be copied to uapi.
	 *
	 * Bigjoiner will allow a transcoder mode that spans 2 pipes;
	 * Use the pipe_mode क्रम calculations like watermarks, pipe
	 * scaler, and bandwidth.
	 *
	 * Use adjusted_mode क्रम things that need to know the full
	 * mode on the transcoder, which spans all pipes.
	 */
	काष्ठा अणु
		bool active, enable;
		काष्ठा drm_property_blob *degamma_lut, *gamma_lut, *cपंचांग;
		काष्ठा drm_display_mode mode, pipe_mode, adjusted_mode;
		क्रमागत drm_scaling_filter scaling_filter;
	पूर्ण hw;

	/**
	 * quirks - bitfield with hw state पढ़ोout quirks
	 *
	 * For various reasons the hw state पढ़ोout code might not be able to
	 * completely faithfully पढ़ो out the current state. These हालs are
	 * tracked with quirk flags so that fastboot and state checker can act
	 * accordingly.
	 */
#घोषणा PIPE_CONFIG_QUIRK_MODE_SYNC_FLAGS	(1<<0) /* unreliable sync mode.flags */
#घोषणा PIPE_CONFIG_QUIRK_BIGJOINER_SLAVE      (1<<1) /* bigjoiner slave, partial पढ़ोout */
	अचिन्हित दीर्घ quirks;

	अचिन्हित fb_bits; /* framebuffers to flip */
	bool update_pipe; /* can a fast modeset be perक्रमmed? */
	bool disable_cxsr;
	bool update_wm_pre, update_wm_post; /* watermarks are updated */
	bool fअगरo_changed; /* FIFO split is changed */
	bool preload_luts;
	bool inherited; /* state inherited from BIOS? */

	/* Pipe source size (ie. panel fitter input size)
	 * All planes will be positioned inside this space,
	 * and get clipped at the edges. */
	पूर्णांक pipe_src_w, pipe_src_h;

	/*
	 * Pipe pixel rate, adjusted क्रम
	 * panel fitter/pipe scaler करोwnscaling.
	 */
	अचिन्हित पूर्णांक pixel_rate;

	/* Whether to set up the PCH/FDI. Note that we never allow sharing
	 * between pch encoders and cpu encoders. */
	bool has_pch_encoder;

	/* Are we sending infoframes on the attached port */
	bool has_infoframe;

	/* CPU Transcoder क्रम the pipe. Currently this can only dअगरfer from the
	 * pipe on Haswell and later (where we have a special eDP transcoder)
	 * and Broxton (where we have special DSI transcoders). */
	क्रमागत transcoder cpu_transcoder;

	/*
	 * Use reduced/limited/broadcast rbg range, compressing from the full
	 * range fed पूर्णांकo the crtcs.
	 */
	bool limited_color_range;

	/* Biपंचांगask of encoder types (क्रमागत पूर्णांकel_output_type)
	 * driven by the pipe.
	 */
	अचिन्हित पूर्णांक output_types;

	/* Whether we should send शून्य infoframes. Required क्रम audio. */
	bool has_hdmi_sink;

	/* Audio enabled on this pipe. Only valid अगर either has_hdmi_sink or
	 * has_dp_encoder is set. */
	bool has_audio;

	/*
	 * Enable dithering, used when the selected pipe bpp करोesn't match the
	 * plane bpp.
	 */
	bool dither;

	/*
	 * Dither माला_लो enabled क्रम 18bpp which causes CRC mismatch errors क्रम
	 * compliance video pattern tests.
	 * Disable dither only अगर it is a compliance test request क्रम
	 * 18bpp.
	 */
	bool dither_क्रमce_disable;

	/* Controls क्रम the घड़ी computation, to override various stages. */
	bool घड़ी_set;

	/* SDVO TV has a bunch of special हाल. To make multअगरunction encoders
	 * work correctly, we need to track this at runसमय.*/
	bool sdvo_tv_घड़ी;

	/*
	 * crtc bandwidth limit, करोn't increase pipe bpp or घड़ी अगर not really
	 * required. This is set in the 2nd loop of calling encoder's
	 * ->compute_config अगर the first pick करोesn't work out.
	 */
	bool bw_स्थिरrained;

	/* Settings क्रम the पूर्णांकel dpll used on pretty much everything but
	 * haswell. */
	काष्ठा dpll dpll;

	/* Selected dpll when shared or शून्य. */
	काष्ठा पूर्णांकel_shared_dpll *shared_dpll;

	/* Actual रेजिस्टर state of the dpll, क्रम shared dpll cross-checking. */
	काष्ठा पूर्णांकel_dpll_hw_state dpll_hw_state;

	/*
	 * ICL reserved DPLLs क्रम the CRTC/port. The active PLL is selected by
	 * setting shared_dpll and dpll_hw_state to one of these reserved ones.
	 */
	काष्ठा icl_port_dpll अणु
		काष्ठा पूर्णांकel_shared_dpll *pll;
		काष्ठा पूर्णांकel_dpll_hw_state hw_state;
	पूर्ण icl_port_dplls[ICL_PORT_DPLL_COUNT];

	/* DSI PLL रेजिस्टरs */
	काष्ठा अणु
		u32 ctrl, भाग;
	पूर्ण dsi_pll;

	पूर्णांक pipe_bpp;
	काष्ठा पूर्णांकel_link_m_n dp_m_n;

	/* m2_n2 क्रम eDP करोwnघड़ी */
	काष्ठा पूर्णांकel_link_m_n dp_m2_n2;
	bool has_drrs;

	bool has_psr;
	bool has_psr2;
	bool enable_psr2_sel_fetch;
	u32 dc3co_निकासline;

	/*
	 * Frequence the dpll क्रम the port should run at. Dअगरfers from the
	 * adjusted करोtघड़ी e.g. क्रम DP or 10/12bpc hdmi mode. This is also
	 * alपढ़ोy multiplied by pixel_multiplier.
	 */
	पूर्णांक port_घड़ी;

	/* Used by SDVO (and अगर we ever fix it, HDMI). */
	अचिन्हित pixel_multiplier;

	/* I915_MODE_FLAG_* */
	u8 mode_flags;

	u8 lane_count;

	/*
	 * Used by platक्रमms having DP/HDMI PHY with programmable lane
	 * latency optimization.
	 */
	u8 lane_lat_optim_mask;

	/* minimum acceptable voltage level */
	u8 min_voltage_level;

	/* Panel fitter controls क्रम gen2-gen4 + VLV */
	काष्ठा अणु
		u32 control;
		u32 pgm_ratios;
		u32 lvds_border_bits;
	पूर्ण gmch_pfit;

	/* Panel fitter placement and size क्रम Ironlake+ */
	काष्ठा अणु
		काष्ठा drm_rect dst;
		bool enabled;
		bool क्रमce_thru;
	पूर्ण pch_pfit;

	/* FDI configuration, only valid अगर has_pch_encoder is set. */
	पूर्णांक fdi_lanes;
	काष्ठा पूर्णांकel_link_m_n fdi_m_n;

	bool ips_enabled;

	bool crc_enabled;

	bool enable_fbc;

	bool द्विगुन_wide;

	पूर्णांक pbn;

	काष्ठा पूर्णांकel_crtc_scaler_state scaler_state;

	/* w/a क्रम रुकोing 2 vblanks during crtc enable */
	क्रमागत pipe hsw_workaround_pipe;

	/* IVB sprite scaling w/a (WaCxSRDisabledForSpriteScaling:ivb) */
	bool disable_lp_wm;

	काष्ठा पूर्णांकel_crtc_wm_state wm;

	पूर्णांक min_cdclk[I915_MAX_PLANES];

	u32 data_rate[I915_MAX_PLANES];

	/* FIXME unअगरy with data_rate[] */
	u64 plane_data_rate[I915_MAX_PLANES];
	u64 uv_plane_data_rate[I915_MAX_PLANES];

	/* Gamma mode programmed on the pipe */
	u32 gamma_mode;

	जोड़ अणु
		/* CSC mode programmed on the pipe */
		u32 csc_mode;

		/* CHV CGM mode */
		u32 cgm_mode;
	पूर्ण;

	/* biपंचांगask of logically enabled planes (क्रमागत plane_id) */
	u8 enabled_planes;

	/* biपंचांगask of actually visible planes (क्रमागत plane_id) */
	u8 active_planes;
	u8 nv12_planes;
	u8 c8_planes;

	/* biपंचांगask of planes that will be updated during the commit */
	u8 update_planes;

	काष्ठा अणु
		u32 enable;
		u32 gcp;
		जोड़ hdmi_infoframe avi;
		जोड़ hdmi_infoframe spd;
		जोड़ hdmi_infoframe hdmi;
		जोड़ hdmi_infoframe drm;
		काष्ठा drm_dp_vsc_sdp vsc;
	पूर्ण infoframes;

	/* HDMI scrambling status */
	bool hdmi_scrambling;

	/* HDMI High TMDS अक्षर rate ratio */
	bool hdmi_high_पंचांगds_घड़ी_ratio;

	/* Output क्रमmat RGB/YCBCR etc */
	क्रमागत पूर्णांकel_output_क्रमmat output_क्रमmat;

	/* enable pipe gamma? */
	bool gamma_enable;

	/* enable pipe csc? */
	bool csc_enable;

	/* enable pipe big joiner? */
	bool bigjoiner;

	/* big joiner slave crtc? */
	bool bigjoiner_slave;

	/* linked crtc क्रम bigjoiner, either slave or master */
	काष्ठा पूर्णांकel_crtc *bigjoiner_linked_crtc;

	/* Display Stream compression state */
	काष्ठा अणु
		bool compression_enable;
		bool dsc_split;
		u16 compressed_bpp;
		u8 slice_count;
		काष्ठा drm_dsc_config config;
	पूर्ण dsc;

	/* HSW+ lineसमय watermarks */
	u16 lineसमय;
	u16 ips_lineसमय;

	/* Forward Error correction State */
	bool fec_enable;

	/* Poपूर्णांकer to master transcoder in हाल of tiled displays */
	क्रमागत transcoder master_transcoder;

	/* Biपंचांगask to indicate slaves attached */
	u8 sync_mode_slaves_mask;

	/* Only valid on TGL+ */
	क्रमागत transcoder mst_master_transcoder;

	/* For DSB related info */
	काष्ठा पूर्णांकel_dsb *dsb;

	u32 psr2_man_track_ctl;

	/* Variable Refresh Rate state */
	काष्ठा अणु
		bool enable;
		u8 pipeline_full;
		u16 flipline, vmin, vmax;
	पूर्ण vrr;

	/* Stream Splitter क्रम eDP MSO */
	काष्ठा अणु
		bool enable;
		u8 link_count;
		u8 pixel_overlap;
	पूर्ण splitter;
पूर्ण;

क्रमागत पूर्णांकel_pipe_crc_source अणु
	INTEL_PIPE_CRC_SOURCE_NONE,
	INTEL_PIPE_CRC_SOURCE_PLANE1,
	INTEL_PIPE_CRC_SOURCE_PLANE2,
	INTEL_PIPE_CRC_SOURCE_PLANE3,
	INTEL_PIPE_CRC_SOURCE_PLANE4,
	INTEL_PIPE_CRC_SOURCE_PLANE5,
	INTEL_PIPE_CRC_SOURCE_PLANE6,
	INTEL_PIPE_CRC_SOURCE_PLANE7,
	INTEL_PIPE_CRC_SOURCE_PIPE,
	/* TV/DP on pre-gen5/vlv can't use the pipe source. */
	INTEL_PIPE_CRC_SOURCE_TV,
	INTEL_PIPE_CRC_SOURCE_DP_B,
	INTEL_PIPE_CRC_SOURCE_DP_C,
	INTEL_PIPE_CRC_SOURCE_DP_D,
	INTEL_PIPE_CRC_SOURCE_AUTO,
	INTEL_PIPE_CRC_SOURCE_MAX,
पूर्ण;

#घोषणा INTEL_PIPE_CRC_ENTRIES_NR	128
काष्ठा पूर्णांकel_pipe_crc अणु
	spinlock_t lock;
	पूर्णांक skipped;
	क्रमागत पूर्णांकel_pipe_crc_source source;
पूर्ण;

काष्ठा पूर्णांकel_crtc अणु
	काष्ठा drm_crtc base;
	क्रमागत pipe pipe;
	/*
	 * Whether the crtc and the connected output pipeline is active. Implies
	 * that crtc->enabled is set, i.e. the current mode configuration has
	 * some outमाला_दो connected to this crtc.
	 */
	bool active;
	u8 plane_ids_mask;

	/* I915_MODE_FLAG_* */
	u8 mode_flags;

	u16 vmax_vblank_start;

	काष्ठा पूर्णांकel_display_घातer_करोमुख्य_set enabled_घातer_करोमुख्यs;
	काष्ठा पूर्णांकel_overlay *overlay;

	काष्ठा पूर्णांकel_crtc_state *config;

	/* Access to these should be रक्षित by dev_priv->irq_lock. */
	bool cpu_fअगरo_underrun_disabled;
	bool pch_fअगरo_underrun_disabled;

	/* per-pipe watermark state */
	काष्ठा अणु
		/* watermarks currently being used  */
		जोड़ अणु
			काष्ठा पूर्णांकel_pipe_wm ilk;
			काष्ठा vlv_wm_state vlv;
			काष्ठा g4x_wm_state g4x;
		पूर्ण active;
	पूर्ण wm;

	पूर्णांक scanline_offset;

	काष्ठा अणु
		अचिन्हित start_vbl_count;
		kसमय_प्रकार start_vbl_समय;
		पूर्णांक min_vbl, max_vbl;
		पूर्णांक scanline_start;
#अगर_घोषित CONFIG_DRM_I915_DEBUG_VBLANK_EVADE
		काष्ठा अणु
			u64 min;
			u64 max;
			u64 sum;
			अचिन्हित पूर्णांक over;
			अचिन्हित पूर्णांक बार[17]; /* [1us, 16ms] */
		पूर्ण vbl;
#पूर्ण_अगर
	पूर्ण debug;

	/* scalers available on this crtc */
	पूर्णांक num_scalers;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा पूर्णांकel_pipe_crc pipe_crc;
#पूर्ण_अगर
पूर्ण;

काष्ठा पूर्णांकel_plane अणु
	काष्ठा drm_plane base;
	क्रमागत i9xx_plane_id i9xx_plane;
	क्रमागत plane_id id;
	क्रमागत pipe pipe;
	bool has_fbc;
	bool has_ccs;
	bool need_async_flip_disable_wa;
	u32 frontbuffer_bit;

	काष्ठा अणु
		u32 base, cntl, size;
	पूर्ण cursor;

	/*
	 * NOTE: Do not place new plane state fields here (e.g., when adding
	 * new plane properties).  New runसमय state should now be placed in
	 * the पूर्णांकel_plane_state काष्ठाure and accessed via plane_state.
	 */

	पूर्णांक (*min_width)(स्थिर काष्ठा drm_framebuffer *fb,
			 पूर्णांक color_plane,
			 अचिन्हित पूर्णांक rotation);
	पूर्णांक (*max_width)(स्थिर काष्ठा drm_framebuffer *fb,
			 पूर्णांक color_plane,
			 अचिन्हित पूर्णांक rotation);
	पूर्णांक (*max_height)(स्थिर काष्ठा drm_framebuffer *fb,
			  पूर्णांक color_plane,
			  अचिन्हित पूर्णांक rotation);
	अचिन्हित पूर्णांक (*max_stride)(काष्ठा पूर्णांकel_plane *plane,
				   u32 pixel_क्रमmat, u64 modअगरier,
				   अचिन्हित पूर्णांक rotation);
	व्योम (*update_plane)(काष्ठा पूर्णांकel_plane *plane,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			     स्थिर काष्ठा पूर्णांकel_plane_state *plane_state);
	व्योम (*disable_plane)(काष्ठा पूर्णांकel_plane *plane,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
	bool (*get_hw_state)(काष्ठा पूर्णांकel_plane *plane, क्रमागत pipe *pipe);
	पूर्णांक (*check_plane)(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			   काष्ठा पूर्णांकel_plane_state *plane_state);
	पूर्णांक (*min_cdclk)(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			 स्थिर काष्ठा पूर्णांकel_plane_state *plane_state);
	व्योम (*async_flip)(काष्ठा पूर्णांकel_plane *plane,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			   स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
			   bool async_flip);
	व्योम (*enable_flip_करोne)(काष्ठा पूर्णांकel_plane *plane);
	व्योम (*disable_flip_करोne)(काष्ठा पूर्णांकel_plane *plane);
पूर्ण;

काष्ठा पूर्णांकel_watermark_params अणु
	u16 fअगरo_size;
	u16 max_wm;
	u8 शेष_wm;
	u8 guard_size;
	u8 cacheline_size;
पूर्ण;

काष्ठा cxsr_latency अणु
	bool is_desktop : 1;
	bool is_ddr3 : 1;
	u16 fsb_freq;
	u16 mem_freq;
	u16 display_sr;
	u16 display_hpll_disable;
	u16 cursor_sr;
	u16 cursor_hpll_disable;
पूर्ण;

#घोषणा to_पूर्णांकel_atomic_state(x) container_of(x, काष्ठा पूर्णांकel_atomic_state, base)
#घोषणा to_पूर्णांकel_crtc(x) container_of(x, काष्ठा पूर्णांकel_crtc, base)
#घोषणा to_पूर्णांकel_crtc_state(x) container_of(x, काष्ठा पूर्णांकel_crtc_state, uapi)
#घोषणा to_पूर्णांकel_connector(x) container_of(x, काष्ठा पूर्णांकel_connector, base)
#घोषणा to_पूर्णांकel_encoder(x) container_of(x, काष्ठा पूर्णांकel_encoder, base)
#घोषणा to_पूर्णांकel_framebuffer(x) container_of(x, काष्ठा पूर्णांकel_framebuffer, base)
#घोषणा to_पूर्णांकel_plane(x) container_of(x, काष्ठा पूर्णांकel_plane, base)
#घोषणा to_पूर्णांकel_plane_state(x) container_of(x, काष्ठा पूर्णांकel_plane_state, uapi)
#घोषणा पूर्णांकel_fb_obj(x) ((x) ? to_पूर्णांकel_bo((x)->obj[0]) : शून्य)

काष्ठा पूर्णांकel_hdmi अणु
	i915_reg_t hdmi_reg;
	पूर्णांक ddc_bus;
	काष्ठा अणु
		क्रमागत drm_dp_dual_mode_type type;
		पूर्णांक max_पंचांगds_घड़ी;
	पूर्ण dp_dual_mode;
	bool has_hdmi_sink;
	bool has_audio;
	काष्ठा पूर्णांकel_connector *attached_connector;
	काष्ठा cec_notअगरier *cec_notअगरier;
पूर्ण;

काष्ठा पूर्णांकel_dp_mst_encoder;
/*
 * क्रमागत link_m_n_set:
 *	When platक्रमm provides two set of M_N रेजिस्टरs क्रम dp, we can
 *	program them and चयन between them inहाल of DRRS.
 *	But When only one such रेजिस्टर is provided, we have to program the
 *	required भागider value on that रेजिस्टरs itself based on the DRRS state.
 *
 * M1_N1	: Program dp_m_n on M1_N1 रेजिस्टरs
 *			  dp_m2_n2 on M2_N2 रेजिस्टरs (If supported)
 *
 * M2_N2	: Program dp_m2_n2 on M1_N1 रेजिस्टरs
 *			  M2_N2 रेजिस्टरs are not supported
 */

क्रमागत link_m_n_set अणु
	/* Sets the m1_n1 and m2_n2 */
	M1_N1 = 0,
	M2_N2
पूर्ण;

काष्ठा पूर्णांकel_dp_compliance_data अणु
	अचिन्हित दीर्घ edid;
	u8 video_pattern;
	u16 hdisplay, vdisplay;
	u8 bpc;
	काष्ठा drm_dp_phy_test_params phytest;
पूर्ण;

काष्ठा पूर्णांकel_dp_compliance अणु
	अचिन्हित दीर्घ test_type;
	काष्ठा पूर्णांकel_dp_compliance_data test_data;
	bool test_active;
	पूर्णांक test_link_rate;
	u8 test_lane_count;
पूर्ण;

काष्ठा पूर्णांकel_dp_pcon_frl अणु
	bool is_trained;
	पूर्णांक trained_rate_gbps;
पूर्ण;

काष्ठा पूर्णांकel_pps अणु
	पूर्णांक panel_घातer_up_delay;
	पूर्णांक panel_घातer_करोwn_delay;
	पूर्णांक panel_घातer_cycle_delay;
	पूर्णांक backlight_on_delay;
	पूर्णांक backlight_off_delay;
	काष्ठा delayed_work panel_vdd_work;
	bool want_panel_vdd;
	अचिन्हित दीर्घ last_घातer_on;
	अचिन्हित दीर्घ last_backlight_off;
	kसमय_प्रकार panel_घातer_off_समय;
	पूर्णांकel_wakeref_t vdd_wakeref;

	/*
	 * Pipe whose घातer sequencer is currently locked पूर्णांकo
	 * this port. Only relevant on VLV/CHV.
	 */
	क्रमागत pipe pps_pipe;
	/*
	 * Pipe currently driving the port. Used क्रम preventing
	 * the use of the PPS क्रम any pipe currentrly driving
	 * बाह्यal DP as that will mess things up on VLV.
	 */
	क्रमागत pipe active_pipe;
	/*
	 * Set अगर the sequencer may be reset due to a घातer transition,
	 * requiring a reinitialization. Only relevant on BXT.
	 */
	bool pps_reset;
	काष्ठा edp_घातer_seq pps_delays;
पूर्ण;

काष्ठा पूर्णांकel_psr अणु
	/* Mutex क्रम PSR state of the transcoder */
	काष्ठा mutex lock;

#घोषणा I915_PSR_DEBUG_MODE_MASK	0x0f
#घोषणा I915_PSR_DEBUG_DEFAULT		0x00
#घोषणा I915_PSR_DEBUG_DISABLE		0x01
#घोषणा I915_PSR_DEBUG_ENABLE		0x02
#घोषणा I915_PSR_DEBUG_FORCE_PSR1	0x03
#घोषणा I915_PSR_DEBUG_ENABLE_SEL_FETCH	0x4
#घोषणा I915_PSR_DEBUG_IRQ		0x10

	u32 debug;
	bool sink_support;
	bool source_support;
	bool enabled;
	क्रमागत pipe pipe;
	क्रमागत transcoder transcoder;
	bool active;
	काष्ठा work_काष्ठा work;
	अचिन्हित पूर्णांक busy_frontbuffer_bits;
	bool sink_psr2_support;
	bool link_standby;
	bool colorimetry_support;
	bool psr2_enabled;
	bool psr2_sel_fetch_enabled;
	u8 sink_sync_latency;
	kसमय_प्रकार last_entry_attempt;
	kसमय_प्रकार last_निकास;
	bool sink_not_reliable;
	bool irq_aux_error;
	u16 su_x_granularity;
	bool dc3co_enabled;
	u32 dc3co_निकास_delay;
	काष्ठा delayed_work dc3co_work;
	काष्ठा drm_dp_vsc_sdp vsc;
पूर्ण;

काष्ठा पूर्णांकel_dp अणु
	i915_reg_t output_reg;
	u32 DP;
	पूर्णांक link_rate;
	u8 lane_count;
	u8 sink_count;
	bool link_trained;
	bool has_hdmi_sink;
	bool has_audio;
	bool reset_link_params;
	bool use_max_params;
	u8 dpcd[DP_RECEIVER_CAP_SIZE];
	u8 psr_dpcd[EDP_PSR_RECEIVER_CAP_SIZE];
	u8 करोwnstream_ports[DP_MAX_DOWNSTREAM_PORTS];
	u8 edp_dpcd[EDP_DISPLAY_CTL_CAP_SIZE];
	u8 dsc_dpcd[DP_DSC_RECEIVER_CAP_SIZE];
	u8 lttpr_common_caps[DP_LTTPR_COMMON_CAP_SIZE];
	u8 lttpr_phy_caps[DP_MAX_LTTPR_COUNT][DP_LTTPR_PHY_CAP_SIZE];
	u8 fec_capable;
	u8 pcon_dsc_dpcd[DP_PCON_DSC_ENCODER_CAP_SIZE];
	/* source rates */
	पूर्णांक num_source_rates;
	स्थिर पूर्णांक *source_rates;
	/* sink rates as reported by DP_MAX_LINK_RATE/DP_SUPPORTED_LINK_RATES */
	पूर्णांक num_sink_rates;
	पूर्णांक sink_rates[DP_MAX_SUPPORTED_RATES];
	bool use_rate_select;
	/* पूर्णांकersection of source and sink rates */
	पूर्णांक num_common_rates;
	पूर्णांक common_rates[DP_MAX_SUPPORTED_RATES];
	/* Max lane count क्रम the current link */
	पूर्णांक max_link_lane_count;
	/* Max rate क्रम the current link */
	पूर्णांक max_link_rate;
	पूर्णांक mso_link_count;
	पूर्णांक mso_pixel_overlap;
	/* sink or branch descriptor */
	काष्ठा drm_dp_desc desc;
	काष्ठा drm_dp_aux aux;
	u32 aux_busy_last_status;
	u8 train_set[4];

	काष्ठा पूर्णांकel_pps pps;

	bool can_mst; /* this port supports mst */
	bool is_mst;
	पूर्णांक active_mst_links;

	/* connector directly attached - won't be use क्रम modeset in mst world */
	काष्ठा पूर्णांकel_connector *attached_connector;

	/* mst connector list */
	काष्ठा पूर्णांकel_dp_mst_encoder *mst_encoders[I915_MAX_PIPES];
	काष्ठा drm_dp_mst_topology_mgr mst_mgr;

	u32 (*get_aux_घड़ी_भागider)(काष्ठा पूर्णांकel_dp *dp, पूर्णांक index);
	/*
	 * This function वापसs the value we have to program the AUX_CTL
	 * रेजिस्टर with to kick off an AUX transaction.
	 */
	u32 (*get_aux_send_ctl)(काष्ठा पूर्णांकel_dp *dp, पूर्णांक send_bytes,
				u32 aux_घड़ी_भागider);

	i915_reg_t (*aux_ch_ctl_reg)(काष्ठा पूर्णांकel_dp *dp);
	i915_reg_t (*aux_ch_data_reg)(काष्ठा पूर्णांकel_dp *dp, पूर्णांक index);

	/* This is called beक्रमe a link training is starterd */
	व्योम (*prepare_link_retrain)(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
	व्योम (*set_link_train)(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       u8 dp_train_pat);
	व्योम (*set_idle_link_train)(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
	व्योम (*set_संकेत_levels)(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);

	u8 (*preemph_max)(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
	u8 (*voltage_max)(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);

	/* Displayport compliance testing */
	काष्ठा पूर्णांकel_dp_compliance compliance;

	/* Downstream facing port caps */
	काष्ठा अणु
		पूर्णांक min_पंचांगds_घड़ी, max_पंचांगds_घड़ी;
		पूर्णांक max_करोtघड़ी;
		पूर्णांक pcon_max_frl_bw;
		u8 max_bpc;
		bool ycbcr_444_to_420;
		bool rgb_to_ycbcr;
	पूर्ण dfp;

	/* To control wakeup latency, e.g. क्रम irq-driven dp aux transfers. */
	काष्ठा pm_qos_request pm_qos;

	/* Display stream compression testing */
	bool क्रमce_dsc_en;

	bool hobl_failed;
	bool hobl_active;

	काष्ठा पूर्णांकel_dp_pcon_frl frl;

	काष्ठा पूर्णांकel_psr psr;
पूर्ण;

क्रमागत lspcon_venकरोr अणु
	LSPCON_VENDOR_MCA,
	LSPCON_VENDOR_PARADE
पूर्ण;

काष्ठा पूर्णांकel_lspcon अणु
	bool active;
	bool hdr_supported;
	क्रमागत drm_lspcon_mode mode;
	क्रमागत lspcon_venकरोr venकरोr;
पूर्ण;

काष्ठा पूर्णांकel_digital_port अणु
	काष्ठा पूर्णांकel_encoder base;
	u32 saved_port_bits;
	काष्ठा पूर्णांकel_dp dp;
	काष्ठा पूर्णांकel_hdmi hdmi;
	काष्ठा पूर्णांकel_lspcon lspcon;
	क्रमागत irqवापस (*hpd_pulse)(काष्ठा पूर्णांकel_digital_port *, bool);
	bool release_cl2_override;
	u8 max_lanes;
	/* Used क्रम DP and ICL+ TypeC/DP and TypeC/HDMI ports. */
	क्रमागत aux_ch aux_ch;
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य ddi_io_घातer_करोमुख्य;
	पूर्णांकel_wakeref_t ddi_io_wakeref;
	पूर्णांकel_wakeref_t aux_wakeref;
	काष्ठा mutex tc_lock;	/* protects the TypeC port mode */
	पूर्णांकel_wakeref_t tc_lock_wakeref;
	पूर्णांक tc_link_refcount;
	bool tc_legacy_port:1;
	अक्षर tc_port_name[8];
	क्रमागत tc_port_mode tc_mode;
	क्रमागत phy_fia tc_phy_fia;
	u8 tc_phy_fia_idx;

	/* protects num_hdcp_streams reference count, hdcp_port_data and hdcp_auth_status */
	काष्ठा mutex hdcp_mutex;
	/* the number of pipes using HDCP संकेतling out of this port */
	अचिन्हित पूर्णांक num_hdcp_streams;
	/* port HDCP auth status */
	bool hdcp_auth_status;
	/* HDCP port data need to pass to security f/w */
	काष्ठा hdcp_port_data hdcp_port_data;

	व्योम (*ग_लिखो_infoframe)(काष्ठा पूर्णांकel_encoder *encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				अचिन्हित पूर्णांक type,
				स्थिर व्योम *frame, sमाप_प्रकार len);
	व्योम (*पढ़ो_infoframe)(काष्ठा पूर्णांकel_encoder *encoder,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       अचिन्हित पूर्णांक type,
			       व्योम *frame, sमाप_प्रकार len);
	व्योम (*set_infoframes)(काष्ठा पूर्णांकel_encoder *encoder,
			       bool enable,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       स्थिर काष्ठा drm_connector_state *conn_state);
	u32 (*infoframes_enabled)(काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config);
	bool (*connected)(काष्ठा पूर्णांकel_encoder *encoder);
पूर्ण;

काष्ठा पूर्णांकel_dp_mst_encoder अणु
	काष्ठा पूर्णांकel_encoder base;
	क्रमागत pipe pipe;
	काष्ठा पूर्णांकel_digital_port *primary;
	काष्ठा पूर्णांकel_connector *connector;
पूर्ण;

अटल अंतरभूत क्रमागत dpio_channel
vlv_dig_port_to_channel(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	चयन (dig_port->base.port) अणु
	हाल PORT_B:
	हाल PORT_D:
		वापस DPIO_CH0;
	हाल PORT_C:
		वापस DPIO_CH1;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल अंतरभूत क्रमागत dpio_phy
vlv_dig_port_to_phy(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	चयन (dig_port->base.port) अणु
	हाल PORT_B:
	हाल PORT_C:
		वापस DPIO_PHY0;
	हाल PORT_D:
		वापस DPIO_PHY1;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल अंतरभूत क्रमागत dpio_channel
vlv_pipe_to_channel(क्रमागत pipe pipe)
अणु
	चयन (pipe) अणु
	हाल PIPE_A:
	हाल PIPE_C:
		वापस DPIO_CH0;
	हाल PIPE_B:
		वापस DPIO_CH1;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_crtc *
पूर्णांकel_get_first_crtc(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस to_पूर्णांकel_crtc(drm_crtc_from_index(&dev_priv->drm, 0));
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_crtc *
पूर्णांकel_get_crtc_क्रम_pipe(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe)
अणु
	/* pipe_to_crtc_mapping may have hole on any of 3 display pipe प्रणाली */
	drm_WARN_ON(&dev_priv->drm,
		    !(INTEL_INFO(dev_priv)->pipe_mask & BIT(pipe)));
	वापस dev_priv->pipe_to_crtc_mapping[pipe];
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_crtc *
पूर्णांकel_get_crtc_क्रम_plane(काष्ठा drm_i915_निजी *dev_priv, क्रमागत i9xx_plane_id plane)
अणु
	वापस dev_priv->plane_to_crtc_mapping[plane];
पूर्ण

काष्ठा पूर्णांकel_load_detect_pipe अणु
	काष्ठा drm_atomic_state *restore_state;
पूर्ण;

अटल अंतरभूत काष्ठा पूर्णांकel_encoder *
पूर्णांकel_attached_encoder(काष्ठा पूर्णांकel_connector *connector)
अणु
	वापस connector->encoder;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_encoder_is_dig_port(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	चयन (encoder->type) अणु
	हाल INTEL_OUTPUT_DDI:
	हाल INTEL_OUTPUT_DP:
	हाल INTEL_OUTPUT_EDP:
	हाल INTEL_OUTPUT_HDMI:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत bool पूर्णांकel_encoder_is_mst(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	वापस encoder->type == INTEL_OUTPUT_DP_MST;
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_dp_mst_encoder *
enc_to_mst(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	वापस container_of(&encoder->base, काष्ठा पूर्णांकel_dp_mst_encoder,
			    base.base);
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_digital_port *
enc_to_dig_port(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder = encoder;

	अगर (पूर्णांकel_encoder_is_dig_port(पूर्णांकel_encoder))
		वापस container_of(&encoder->base, काष्ठा पूर्णांकel_digital_port,
				    base.base);
	अन्यथा अगर (पूर्णांकel_encoder_is_mst(पूर्णांकel_encoder))
		वापस enc_to_mst(encoder)->primary;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_digital_port *
पूर्णांकel_attached_dig_port(काष्ठा पूर्णांकel_connector *connector)
अणु
	वापस enc_to_dig_port(पूर्णांकel_attached_encoder(connector));
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_hdmi *
enc_to_पूर्णांकel_hdmi(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	वापस &enc_to_dig_port(encoder)->hdmi;
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_hdmi *
पूर्णांकel_attached_hdmi(काष्ठा पूर्णांकel_connector *connector)
अणु
	वापस enc_to_पूर्णांकel_hdmi(पूर्णांकel_attached_encoder(connector));
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_dp *enc_to_पूर्णांकel_dp(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	वापस &enc_to_dig_port(encoder)->dp;
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_dp *पूर्णांकel_attached_dp(काष्ठा पूर्णांकel_connector *connector)
अणु
	वापस enc_to_पूर्णांकel_dp(पूर्णांकel_attached_encoder(connector));
पूर्ण

अटल अंतरभूत bool पूर्णांकel_encoder_is_dp(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	चयन (encoder->type) अणु
	हाल INTEL_OUTPUT_DP:
	हाल INTEL_OUTPUT_EDP:
		वापस true;
	हाल INTEL_OUTPUT_DDI:
		/* Skip pure HDMI/DVI DDI encoders */
		वापस i915_mmio_reg_valid(enc_to_पूर्णांकel_dp(encoder)->output_reg);
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_lspcon *
enc_to_पूर्णांकel_lspcon(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	वापस &enc_to_dig_port(encoder)->lspcon;
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_digital_port *
dp_to_dig_port(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	वापस container_of(पूर्णांकel_dp, काष्ठा पूर्णांकel_digital_port, dp);
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_lspcon *
dp_to_lspcon(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	वापस &dp_to_dig_port(पूर्णांकel_dp)->lspcon;
पूर्ण

अटल अंतरभूत काष्ठा drm_i915_निजी *
dp_to_i915(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	वापस to_i915(dp_to_dig_port(पूर्णांकel_dp)->base.base.dev);
पूर्ण

#घोषणा CAN_PSR(पूर्णांकel_dp) ((पूर्णांकel_dp)->psr.sink_support && \
			   (पूर्णांकel_dp)->psr.source_support)

अटल अंतरभूत bool पूर्णांकel_encoder_can_psr(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	अगर (!पूर्णांकel_encoder_is_dp(encoder))
		वापस false;

	वापस CAN_PSR(enc_to_पूर्णांकel_dp(encoder));
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_digital_port *
hdmi_to_dig_port(काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi)
अणु
	वापस container_of(पूर्णांकel_hdmi, काष्ठा पूर्णांकel_digital_port, hdmi);
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_plane_state *
पूर्णांकel_atomic_get_plane_state(काष्ठा पूर्णांकel_atomic_state *state,
				 काष्ठा पूर्णांकel_plane *plane)
अणु
	काष्ठा drm_plane_state *ret =
		drm_atomic_get_plane_state(&state->base, &plane->base);

	अगर (IS_ERR(ret))
		वापस ERR_CAST(ret);

	वापस to_पूर्णांकel_plane_state(ret);
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_plane_state *
पूर्णांकel_atomic_get_old_plane_state(काष्ठा पूर्णांकel_atomic_state *state,
				 काष्ठा पूर्णांकel_plane *plane)
अणु
	वापस to_पूर्णांकel_plane_state(drm_atomic_get_old_plane_state(&state->base,
								   &plane->base));
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_plane_state *
पूर्णांकel_atomic_get_new_plane_state(काष्ठा पूर्णांकel_atomic_state *state,
				 काष्ठा पूर्णांकel_plane *plane)
अणु
	वापस to_पूर्णांकel_plane_state(drm_atomic_get_new_plane_state(&state->base,
								   &plane->base));
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_crtc_state *
पूर्णांकel_atomic_get_old_crtc_state(काष्ठा पूर्णांकel_atomic_state *state,
				काष्ठा पूर्णांकel_crtc *crtc)
अणु
	वापस to_पूर्णांकel_crtc_state(drm_atomic_get_old_crtc_state(&state->base,
								 &crtc->base));
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_crtc_state *
पूर्णांकel_atomic_get_new_crtc_state(काष्ठा पूर्णांकel_atomic_state *state,
				काष्ठा पूर्णांकel_crtc *crtc)
अणु
	वापस to_पूर्णांकel_crtc_state(drm_atomic_get_new_crtc_state(&state->base,
								 &crtc->base));
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_digital_connector_state *
पूर्णांकel_atomic_get_new_connector_state(काष्ठा पूर्णांकel_atomic_state *state,
				     काष्ठा पूर्णांकel_connector *connector)
अणु
	वापस to_पूर्णांकel_digital_connector_state(
			drm_atomic_get_new_connector_state(&state->base,
			&connector->base));
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_digital_connector_state *
पूर्णांकel_atomic_get_old_connector_state(काष्ठा पूर्णांकel_atomic_state *state,
				     काष्ठा पूर्णांकel_connector *connector)
अणु
	वापस to_पूर्णांकel_digital_connector_state(
			drm_atomic_get_old_connector_state(&state->base,
			&connector->base));
पूर्ण

/* पूर्णांकel_display.c */
अटल अंतरभूत bool
पूर्णांकel_crtc_has_type(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		    क्रमागत पूर्णांकel_output_type type)
अणु
	वापस crtc_state->output_types & (1 << type);
पूर्ण
अटल अंतरभूत bool
पूर्णांकel_crtc_has_dp_encoder(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	वापस crtc_state->output_types &
		((1 << INTEL_OUTPUT_DP) |
		 (1 << INTEL_OUTPUT_DP_MST) |
		 (1 << INTEL_OUTPUT_EDP));
पूर्ण

अटल अंतरभूत bool
पूर्णांकel_crtc_needs_modeset(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	वापस drm_atomic_crtc_needs_modeset(&crtc_state->uapi);
पूर्ण

अटल अंतरभूत व्योम
पूर्णांकel_रुको_क्रम_vblank(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, pipe);

	drm_crtc_रुको_one_vblank(&crtc->base);
पूर्ण

अटल अंतरभूत व्योम
पूर्णांकel_रुको_क्रम_vblank_अगर_active(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc *crtc = पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, pipe);

	अगर (crtc->active)
		पूर्णांकel_रुको_क्रम_vblank(dev_priv, pipe);
पूर्ण

अटल अंतरभूत u32 पूर्णांकel_plane_ggtt_offset(स्थिर काष्ठा पूर्णांकel_plane_state *state)
अणु
	वापस i915_ggtt_offset(state->vma);
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_frontbuffer *
to_पूर्णांकel_frontbuffer(काष्ठा drm_framebuffer *fb)
अणु
	वापस fb ? to_पूर्णांकel_framebuffer(fb)->frontbuffer : शून्य;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_panel_use_ssc(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (dev_priv->params.panel_use_ssc >= 0)
		वापस dev_priv->params.panel_use_ssc != 0;
	वापस dev_priv->vbt.lvds_use_ssc
		&& !(dev_priv->quirks & QUIRK_LVDS_SSC_DISABLE);
पूर्ण

अटल अंतरभूत u32 i9xx_dpll_compute_fp(काष्ठा dpll *dpll)
अणु
	वापस dpll->n << 16 | dpll->m1 << 8 | dpll->m2;
पूर्ण

अटल अंतरभूत u32 पूर्णांकel_fdi_link_freq(काष्ठा drm_i915_निजी *dev_priv,
				      स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	अगर (HAS_DDI(dev_priv))
		वापस pipe_config->port_घड़ी; /* SPLL */
	अन्यथा
		वापस dev_priv->fdi_pll_freq;
पूर्ण

अटल अंतरभूत bool is_ccs_modअगरier(u64 modअगरier)
अणु
	वापस modअगरier == I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS ||
	       modअगरier == I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS_CC ||
	       modअगरier == I915_FORMAT_MOD_Y_TILED_GEN12_MC_CCS ||
	       modअगरier == I915_FORMAT_MOD_Y_TILED_CCS ||
	       modअगरier == I915_FORMAT_MOD_Yf_TILED_CCS;
पूर्ण

अटल अंतरभूत bool is_gen12_ccs_modअगरier(u64 modअगरier)
अणु
	वापस modअगरier == I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS ||
	       modअगरier == I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS_CC ||
	       modअगरier == I915_FORMAT_MOD_Y_TILED_GEN12_MC_CCS;
पूर्ण

#पूर्ण_अगर /*  __INTEL_DISPLAY_TYPES_H__ */
