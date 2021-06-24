<शैली गुरु>
/*
 * Copyright 2008 Intel Corporation <hong.liu@पूर्णांकel.com>
 * Copyright 2008 Red Hat <mjg@redhat.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON-INFRINGEMENT.  IN NO EVENT SHALL INTEL AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/firmware.h>
#समावेश <acpi/video.h>

#समावेश "display/intel_panel.h"

#समावेश "i915_drv.h"
#समावेश "intel_acpi.h"
#समावेश "intel_display_types.h"
#समावेश "intel_opregion.h"

#घोषणा OPREGION_HEADER_OFFSET 0
#घोषणा OPREGION_ACPI_OFFSET   0x100
#घोषणा   ACPI_CLID 0x01ac /* current lid state indicator */
#घोषणा   ACPI_CDCK 0x01b0 /* current करोcking state indicator */
#घोषणा OPREGION_SWSCI_OFFSET  0x200
#घोषणा OPREGION_ASLE_OFFSET   0x300
#घोषणा OPREGION_VBT_OFFSET    0x400
#घोषणा OPREGION_ASLE_EXT_OFFSET	0x1C00

#घोषणा OPREGION_SIGNATURE "IntelGraphicsMem"
#घोषणा MBOX_ACPI      (1<<0)
#घोषणा MBOX_SWSCI     (1<<1)
#घोषणा MBOX_ASLE      (1<<2)
#घोषणा MBOX_ASLE_EXT  (1<<4)

काष्ठा opregion_header अणु
	u8 signature[16];
	u32 size;
	काष्ठा अणु
		u8 rsvd;
		u8 revision;
		u8 minor;
		u8 major;
	पूर्ण  __packed over;
	u8 bios_ver[32];
	u8 vbios_ver[16];
	u8 driver_ver[16];
	u32 mboxes;
	u32 driver_model;
	u32 pcon;
	u8 dver[32];
	u8 rsvd[124];
पूर्ण __packed;

/* OpRegion mailbox #1: खुला ACPI methods */
काष्ठा opregion_acpi अणु
	u32 drdy;       /* driver पढ़ोiness */
	u32 csts;       /* notअगरication status */
	u32 cevt;       /* current event */
	u8 rsvd1[20];
	u32 didl[8];    /* supported display devices ID list */
	u32 cpdl[8];    /* currently presented display list */
	u32 cadl[8];    /* currently active display list */
	u32 nadl[8];    /* next active devices list */
	u32 aslp;       /* ASL sleep समय-out */
	u32 tidx;       /* toggle table index */
	u32 chpd;       /* current hotplug enable indicator */
	u32 clid;       /* current lid state*/
	u32 cdck;       /* current करोcking state */
	u32 sxsw;       /* Sx state resume */
	u32 evts;       /* ASL supported events */
	u32 cnot;       /* current OS notअगरication */
	u32 nrdy;       /* driver status */
	u32 did2[7];	/* extended supported display devices ID list */
	u32 cpd2[7];	/* extended attached display devices list */
	u8 rsvd2[4];
पूर्ण __packed;

/* OpRegion mailbox #2: SWSCI */
काष्ठा opregion_swsci अणु
	u32 scic;       /* SWSCI command|status|data */
	u32 parm;       /* command parameters */
	u32 dslp;       /* driver sleep समय-out */
	u8 rsvd[244];
पूर्ण __packed;

/* OpRegion mailbox #3: ASLE */
काष्ठा opregion_asle अणु
	u32 ardy;       /* driver पढ़ोiness */
	u32 aslc;       /* ASLE पूर्णांकerrupt command */
	u32 tche;       /* technology enabled indicator */
	u32 alsi;       /* current ALS illuminance पढ़ोing */
	u32 bclp;       /* backlight brightness to set */
	u32 pfit;       /* panel fitting state */
	u32 cblv;       /* current brightness level */
	u16 bclm[20];   /* backlight level duty cycle mapping table */
	u32 cpfm;       /* current panel fitting mode */
	u32 epfm;       /* enabled panel fitting modes */
	u8 plut[74];    /* panel LUT and identअगरier */
	u32 pfmb;       /* PWM freq and min brightness */
	u32 cddv;       /* color correction शेष values */
	u32 pcft;       /* घातer conservation features */
	u32 srot;       /* supported rotation angles */
	u32 iuer;       /* IUER events */
	u64 fdss;
	u32 fdsp;
	u32 stat;
	u64 rvda;	/* Physical (2.0) or relative from opregion (2.1+)
			 * address of raw VBT data. */
	u32 rvds;	/* Size of raw vbt data */
	u8 rsvd[58];
पूर्ण __packed;

/* OpRegion mailbox #5: ASLE ext */
काष्ठा opregion_asle_ext अणु
	u32 phed;	/* Panel Header */
	u8 bddc[256];	/* Panel EDID */
	u8 rsvd[764];
पूर्ण __packed;

/* Driver पढ़ोiness indicator */
#घोषणा ASLE_ARDY_READY		(1 << 0)
#घोषणा ASLE_ARDY_NOT_READY	(0 << 0)

/* ASLE Interrupt Command (ASLC) bits */
#घोषणा ASLC_SET_ALS_ILLUM		(1 << 0)
#घोषणा ASLC_SET_BACKLIGHT		(1 << 1)
#घोषणा ASLC_SET_PFIT			(1 << 2)
#घोषणा ASLC_SET_PWM_FREQ		(1 << 3)
#घोषणा ASLC_SUPPORTED_ROTATION_ANGLES	(1 << 4)
#घोषणा ASLC_BUTTON_ARRAY		(1 << 5)
#घोषणा ASLC_CONVERTIBLE_INDICATOR	(1 << 6)
#घोषणा ASLC_DOCKING_INDICATOR		(1 << 7)
#घोषणा ASLC_ISCT_STATE_CHANGE		(1 << 8)
#घोषणा ASLC_REQ_MSK			0x1ff
/* response bits */
#घोषणा ASLC_ALS_ILLUM_FAILED		(1 << 10)
#घोषणा ASLC_BACKLIGHT_FAILED		(1 << 12)
#घोषणा ASLC_PFIT_FAILED		(1 << 14)
#घोषणा ASLC_PWM_FREQ_FAILED		(1 << 16)
#घोषणा ASLC_ROTATION_ANGLES_FAILED	(1 << 18)
#घोषणा ASLC_BUTTON_ARRAY_FAILED	(1 << 20)
#घोषणा ASLC_CONVERTIBLE_FAILED		(1 << 22)
#घोषणा ASLC_DOCKING_FAILED		(1 << 24)
#घोषणा ASLC_ISCT_STATE_FAILED		(1 << 26)

/* Technology enabled indicator */
#घोषणा ASLE_TCHE_ALS_EN	(1 << 0)
#घोषणा ASLE_TCHE_BLC_EN	(1 << 1)
#घोषणा ASLE_TCHE_PFIT_EN	(1 << 2)
#घोषणा ASLE_TCHE_PFMB_EN	(1 << 3)

/* ASLE backlight brightness to set */
#घोषणा ASLE_BCLP_VALID                (1<<31)
#घोषणा ASLE_BCLP_MSK          (~(1<<31))

/* ASLE panel fitting request */
#घोषणा ASLE_PFIT_VALID         (1<<31)
#घोषणा ASLE_PFIT_CENTER (1<<0)
#घोषणा ASLE_PFIT_STRETCH_TEXT (1<<1)
#घोषणा ASLE_PFIT_STRETCH_GFX (1<<2)

/* PWM frequency and minimum brightness */
#घोषणा ASLE_PFMB_BRIGHTNESS_MASK (0xff)
#घोषणा ASLE_PFMB_BRIGHTNESS_VALID (1<<8)
#घोषणा ASLE_PFMB_PWM_MASK (0x7ffffe00)
#घोषणा ASLE_PFMB_PWM_VALID (1<<31)

#घोषणा ASLE_CBLV_VALID         (1<<31)

/* IUER */
#घोषणा ASLE_IUER_DOCKING		(1 << 7)
#घोषणा ASLE_IUER_CONVERTIBLE		(1 << 6)
#घोषणा ASLE_IUER_ROTATION_LOCK_BTN	(1 << 4)
#घोषणा ASLE_IUER_VOLUME_DOWN_BTN	(1 << 3)
#घोषणा ASLE_IUER_VOLUME_UP_BTN		(1 << 2)
#घोषणा ASLE_IUER_WINDOWS_BTN		(1 << 1)
#घोषणा ASLE_IUER_POWER_BTN		(1 << 0)

/* Software System Control Interrupt (SWSCI) */
#घोषणा SWSCI_SCIC_INDICATOR		(1 << 0)
#घोषणा SWSCI_SCIC_MAIN_FUNCTION_SHIFT	1
#घोषणा SWSCI_SCIC_MAIN_FUNCTION_MASK	(0xf << 1)
#घोषणा SWSCI_SCIC_SUB_FUNCTION_SHIFT	8
#घोषणा SWSCI_SCIC_SUB_FUNCTION_MASK	(0xff << 8)
#घोषणा SWSCI_SCIC_EXIT_PARAMETER_SHIFT	8
#घोषणा SWSCI_SCIC_EXIT_PARAMETER_MASK	(0xff << 8)
#घोषणा SWSCI_SCIC_EXIT_STATUS_SHIFT	5
#घोषणा SWSCI_SCIC_EXIT_STATUS_MASK	(7 << 5)
#घोषणा SWSCI_SCIC_EXIT_STATUS_SUCCESS	1

#घोषणा SWSCI_FUNCTION_CODE(मुख्य, sub) \
	((मुख्य) << SWSCI_SCIC_MAIN_FUNCTION_SHIFT | \
	 (sub) << SWSCI_SCIC_SUB_FUNCTION_SHIFT)

/* SWSCI: Get BIOS Data (GBDA) */
#घोषणा SWSCI_GBDA			4
#घोषणा SWSCI_GBDA_SUPPORTED_CALLS	SWSCI_FUNCTION_CODE(SWSCI_GBDA, 0)
#घोषणा SWSCI_GBDA_REQUESTED_CALLBACKS	SWSCI_FUNCTION_CODE(SWSCI_GBDA, 1)
#घोषणा SWSCI_GBDA_BOOT_DISPLAY_PREF	SWSCI_FUNCTION_CODE(SWSCI_GBDA, 4)
#घोषणा SWSCI_GBDA_PANEL_DETAILS	SWSCI_FUNCTION_CODE(SWSCI_GBDA, 5)
#घोषणा SWSCI_GBDA_TV_STANDARD		SWSCI_FUNCTION_CODE(SWSCI_GBDA, 6)
#घोषणा SWSCI_GBDA_INTERNAL_GRAPHICS	SWSCI_FUNCTION_CODE(SWSCI_GBDA, 7)
#घोषणा SWSCI_GBDA_SPREAD_SPECTRUM	SWSCI_FUNCTION_CODE(SWSCI_GBDA, 10)

/* SWSCI: System BIOS Callbacks (SBCB) */
#घोषणा SWSCI_SBCB			6
#घोषणा SWSCI_SBCB_SUPPORTED_CALLBACKS	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 0)
#घोषणा SWSCI_SBCB_INIT_COMPLETION	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 1)
#घोषणा SWSCI_SBCB_PRE_HIRES_SET_MODE	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 3)
#घोषणा SWSCI_SBCB_POST_HIRES_SET_MODE	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 4)
#घोषणा SWSCI_SBCB_DISPLAY_SWITCH	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 5)
#घोषणा SWSCI_SBCB_SET_TV_FORMAT	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 6)
#घोषणा SWSCI_SBCB_ADAPTER_POWER_STATE	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 7)
#घोषणा SWSCI_SBCB_DISPLAY_POWER_STATE	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 8)
#घोषणा SWSCI_SBCB_SET_BOOT_DISPLAY	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 9)
#घोषणा SWSCI_SBCB_SET_PANEL_DETAILS	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 10)
#घोषणा SWSCI_SBCB_SET_INTERNAL_GFX	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 11)
#घोषणा SWSCI_SBCB_POST_HIRES_TO_DOS_FS	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 16)
#घोषणा SWSCI_SBCB_SUSPEND_RESUME	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 17)
#घोषणा SWSCI_SBCB_SET_SPREAD_SPECTRUM	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 18)
#घोषणा SWSCI_SBCB_POST_VBE_PM		SWSCI_FUNCTION_CODE(SWSCI_SBCB, 19)
#घोषणा SWSCI_SBCB_ENABLE_DISABLE_AUDIO	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 21)

#घोषणा MAX_DSLP	1500

अटल पूर्णांक swsci(काष्ठा drm_i915_निजी *dev_priv,
		 u32 function, u32 parm, u32 *parm_out)
अणु
	काष्ठा opregion_swsci *swsci = dev_priv->opregion.swsci;
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);
	u32 मुख्य_function, sub_function, scic;
	u16 swsci_val;
	u32 dslp;

	अगर (!swsci)
		वापस -ENODEV;

	मुख्य_function = (function & SWSCI_SCIC_MAIN_FUNCTION_MASK) >>
		SWSCI_SCIC_MAIN_FUNCTION_SHIFT;
	sub_function = (function & SWSCI_SCIC_SUB_FUNCTION_MASK) >>
		SWSCI_SCIC_SUB_FUNCTION_SHIFT;

	/* Check अगर we can call the function. See swsci_setup क्रम details. */
	अगर (मुख्य_function == SWSCI_SBCB) अणु
		अगर ((dev_priv->opregion.swsci_sbcb_sub_functions &
		     (1 << sub_function)) == 0)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (मुख्य_function == SWSCI_GBDA) अणु
		अगर ((dev_priv->opregion.swsci_gbda_sub_functions &
		     (1 << sub_function)) == 0)
			वापस -EINVAL;
	पूर्ण

	/* Driver sleep समयout in ms. */
	dslp = swsci->dslp;
	अगर (!dslp) अणु
		/* The spec says 2ms should be the शेष, but it's too small
		 * क्रम some machines. */
		dslp = 50;
	पूर्ण अन्यथा अगर (dslp > MAX_DSLP) अणु
		/* Hey bios, trust must be earned. */
		DRM_INFO_ONCE("ACPI BIOS requests an excessive sleep of %u ms, "
			      "using %u ms instead\n", dslp, MAX_DSLP);
		dslp = MAX_DSLP;
	पूर्ण

	/* The spec tells us to करो this, but we are the only user... */
	scic = swsci->scic;
	अगर (scic & SWSCI_SCIC_INDICATOR) अणु
		drm_dbg(&dev_priv->drm, "SWSCI request already in progress\n");
		वापस -EBUSY;
	पूर्ण

	scic = function | SWSCI_SCIC_INDICATOR;

	swsci->parm = parm;
	swsci->scic = scic;

	/* Ensure SCI event is selected and event trigger is cleared. */
	pci_पढ़ो_config_word(pdev, SWSCI, &swsci_val);
	अगर (!(swsci_val & SWSCI_SCISEL) || (swsci_val & SWSCI_GSSCIE)) अणु
		swsci_val |= SWSCI_SCISEL;
		swsci_val &= ~SWSCI_GSSCIE;
		pci_ग_लिखो_config_word(pdev, SWSCI, swsci_val);
	पूर्ण

	/* Use event trigger to tell bios to check the mail. */
	swsci_val |= SWSCI_GSSCIE;
	pci_ग_लिखो_config_word(pdev, SWSCI, swsci_val);

	/* Poll क्रम the result. */
#घोषणा C (((scic = swsci->scic) & SWSCI_SCIC_INDICATOR) == 0)
	अगर (रुको_क्रम(C, dslp)) अणु
		drm_dbg(&dev_priv->drm, "SWSCI request timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

	scic = (scic & SWSCI_SCIC_EXIT_STATUS_MASK) >>
		SWSCI_SCIC_EXIT_STATUS_SHIFT;

	/* Note: scic == 0 is an error! */
	अगर (scic != SWSCI_SCIC_EXIT_STATUS_SUCCESS) अणु
		drm_dbg(&dev_priv->drm, "SWSCI request error %u\n", scic);
		वापस -EIO;
	पूर्ण

	अगर (parm_out)
		*parm_out = swsci->parm;

	वापस 0;

#अघोषित C
पूर्ण

#घोषणा DISPLAY_TYPE_CRT			0
#घोषणा DISPLAY_TYPE_TV				1
#घोषणा DISPLAY_TYPE_EXTERNAL_FLAT_PANEL	2
#घोषणा DISPLAY_TYPE_INTERNAL_FLAT_PANEL	3

पूर्णांक पूर्णांकel_opregion_notअगरy_encoder(काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder,
				  bool enable)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_encoder->base.dev);
	u32 parm = 0;
	u32 type = 0;
	u32 port;

	/* करोn't care about old stuff क्रम now */
	अगर (!HAS_DDI(dev_priv))
		वापस 0;

	अगर (पूर्णांकel_encoder->type == INTEL_OUTPUT_DSI)
		port = 0;
	अन्यथा
		port = पूर्णांकel_encoder->port;

	अगर (port == PORT_E)  अणु
		port = 0;
	पूर्ण अन्यथा अणु
		parm |= 1 << port;
		port++;
	पूर्ण

	अगर (!enable)
		parm |= 4 << 8;

	चयन (पूर्णांकel_encoder->type) अणु
	हाल INTEL_OUTPUT_ANALOG:
		type = DISPLAY_TYPE_CRT;
		अवरोध;
	हाल INTEL_OUTPUT_DDI:
	हाल INTEL_OUTPUT_DP:
	हाल INTEL_OUTPUT_HDMI:
	हाल INTEL_OUTPUT_DP_MST:
		type = DISPLAY_TYPE_EXTERNAL_FLAT_PANEL;
		अवरोध;
	हाल INTEL_OUTPUT_EDP:
	हाल INTEL_OUTPUT_DSI:
		type = DISPLAY_TYPE_INTERNAL_FLAT_PANEL;
		अवरोध;
	शेष:
		drm_WARN_ONCE(&dev_priv->drm, 1,
			      "unsupported intel_encoder type %d\n",
			      पूर्णांकel_encoder->type);
		वापस -EINVAL;
	पूर्ण

	parm |= type << (16 + port * 3);

	वापस swsci(dev_priv, SWSCI_SBCB_DISPLAY_POWER_STATE, parm, शून्य);
पूर्ण

अटल स्थिर काष्ठा अणु
	pci_घातer_t pci_घातer_state;
	u32 parm;
पूर्ण घातer_state_map[] = अणु
	अणु PCI_D0,	0x00 पूर्ण,
	अणु PCI_D1,	0x01 पूर्ण,
	अणु PCI_D2,	0x02 पूर्ण,
	अणु PCI_D3hot,	0x04 पूर्ण,
	अणु PCI_D3cold,	0x04 पूर्ण,
पूर्ण;

पूर्णांक पूर्णांकel_opregion_notअगरy_adapter(काष्ठा drm_i915_निजी *dev_priv,
				  pci_घातer_t state)
अणु
	पूर्णांक i;

	अगर (!HAS_DDI(dev_priv))
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(घातer_state_map); i++) अणु
		अगर (state == घातer_state_map[i].pci_घातer_state)
			वापस swsci(dev_priv, SWSCI_SBCB_ADAPTER_POWER_STATE,
				     घातer_state_map[i].parm, शून्य);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल u32 asle_set_backlight(काष्ठा drm_i915_निजी *dev_priv, u32 bclp)
अणु
	काष्ठा पूर्णांकel_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा opregion_asle *asle = dev_priv->opregion.asle;
	काष्ठा drm_device *dev = &dev_priv->drm;

	drm_dbg(&dev_priv->drm, "bclp = 0x%08x\n", bclp);

	अगर (acpi_video_get_backlight_type() == acpi_backlight_native) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "opregion backlight request ignored\n");
		वापस 0;
	पूर्ण

	अगर (!(bclp & ASLE_BCLP_VALID))
		वापस ASLC_BACKLIGHT_FAILED;

	bclp &= ASLE_BCLP_MSK;
	अगर (bclp > 255)
		वापस ASLC_BACKLIGHT_FAILED;

	drm_modeset_lock(&dev->mode_config.connection_mutex, शून्य);

	/*
	 * Update backlight on all connectors that support backlight (usually
	 * only one).
	 */
	drm_dbg_kms(&dev_priv->drm, "updating opregion backlight %d/255\n",
		    bclp);
	drm_connector_list_iter_begin(dev, &conn_iter);
	क्रम_each_पूर्णांकel_connector_iter(connector, &conn_iter)
		पूर्णांकel_panel_set_backlight_acpi(connector->base.state, bclp, 255);
	drm_connector_list_iter_end(&conn_iter);
	asle->cblv = DIV_ROUND_UP(bclp * 100, 255) | ASLE_CBLV_VALID;

	drm_modeset_unlock(&dev->mode_config.connection_mutex);


	वापस 0;
पूर्ण

अटल u32 asle_set_als_illum(काष्ठा drm_i915_निजी *dev_priv, u32 alsi)
अणु
	/* alsi is the current ALS पढ़ोing in lux. 0 indicates below sensor
	   range, 0xffff indicates above sensor range. 1-0xfffe are valid */
	drm_dbg(&dev_priv->drm, "Illum is not supported\n");
	वापस ASLC_ALS_ILLUM_FAILED;
पूर्ण

अटल u32 asle_set_pwm_freq(काष्ठा drm_i915_निजी *dev_priv, u32 pfmb)
अणु
	drm_dbg(&dev_priv->drm, "PWM freq is not supported\n");
	वापस ASLC_PWM_FREQ_FAILED;
पूर्ण

अटल u32 asle_set_pfit(काष्ठा drm_i915_निजी *dev_priv, u32 pfit)
अणु
	/* Panel fitting is currently controlled by the X code, so this is a
	   noop until modesetting support works fully */
	drm_dbg(&dev_priv->drm, "Pfit is not supported\n");
	वापस ASLC_PFIT_FAILED;
पूर्ण

अटल u32 asle_set_supported_rotation_angles(काष्ठा drm_i915_निजी *dev_priv, u32 srot)
अणु
	drm_dbg(&dev_priv->drm, "SROT is not supported\n");
	वापस ASLC_ROTATION_ANGLES_FAILED;
पूर्ण

अटल u32 asle_set_button_array(काष्ठा drm_i915_निजी *dev_priv, u32 iuer)
अणु
	अगर (!iuer)
		drm_dbg(&dev_priv->drm,
			"Button array event is not supported (nothing)\n");
	अगर (iuer & ASLE_IUER_ROTATION_LOCK_BTN)
		drm_dbg(&dev_priv->drm,
			"Button array event is not supported (rotation lock)\n");
	अगर (iuer & ASLE_IUER_VOLUME_DOWN_BTN)
		drm_dbg(&dev_priv->drm,
			"Button array event is not supported (volume down)\n");
	अगर (iuer & ASLE_IUER_VOLUME_UP_BTN)
		drm_dbg(&dev_priv->drm,
			"Button array event is not supported (volume up)\n");
	अगर (iuer & ASLE_IUER_WINDOWS_BTN)
		drm_dbg(&dev_priv->drm,
			"Button array event is not supported (windows)\n");
	अगर (iuer & ASLE_IUER_POWER_BTN)
		drm_dbg(&dev_priv->drm,
			"Button array event is not supported (power)\n");

	वापस ASLC_BUTTON_ARRAY_FAILED;
पूर्ण

अटल u32 asle_set_convertible(काष्ठा drm_i915_निजी *dev_priv, u32 iuer)
अणु
	अगर (iuer & ASLE_IUER_CONVERTIBLE)
		drm_dbg(&dev_priv->drm,
			"Convertible is not supported (clamshell)\n");
	अन्यथा
		drm_dbg(&dev_priv->drm,
			"Convertible is not supported (slate)\n");

	वापस ASLC_CONVERTIBLE_FAILED;
पूर्ण

अटल u32 asle_set_करोcking(काष्ठा drm_i915_निजी *dev_priv, u32 iuer)
अणु
	अगर (iuer & ASLE_IUER_DOCKING)
		drm_dbg(&dev_priv->drm, "Docking is not supported (docked)\n");
	अन्यथा
		drm_dbg(&dev_priv->drm,
			"Docking is not supported (undocked)\n");

	वापस ASLC_DOCKING_FAILED;
पूर्ण

अटल u32 asle_isct_state(काष्ठा drm_i915_निजी *dev_priv)
अणु
	drm_dbg(&dev_priv->drm, "ISCT is not supported\n");
	वापस ASLC_ISCT_STATE_FAILED;
पूर्ण

अटल व्योम asle_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पूर्णांकel_opregion *opregion =
		container_of(work, काष्ठा पूर्णांकel_opregion, asle_work);
	काष्ठा drm_i915_निजी *dev_priv =
		container_of(opregion, काष्ठा drm_i915_निजी, opregion);
	काष्ठा opregion_asle *asle = dev_priv->opregion.asle;
	u32 aslc_stat = 0;
	u32 aslc_req;

	अगर (!asle)
		वापस;

	aslc_req = asle->aslc;

	अगर (!(aslc_req & ASLC_REQ_MSK)) अणु
		drm_dbg(&dev_priv->drm,
			"No request on ASLC interrupt 0x%08x\n", aslc_req);
		वापस;
	पूर्ण

	अगर (aslc_req & ASLC_SET_ALS_ILLUM)
		aslc_stat |= asle_set_als_illum(dev_priv, asle->alsi);

	अगर (aslc_req & ASLC_SET_BACKLIGHT)
		aslc_stat |= asle_set_backlight(dev_priv, asle->bclp);

	अगर (aslc_req & ASLC_SET_PFIT)
		aslc_stat |= asle_set_pfit(dev_priv, asle->pfit);

	अगर (aslc_req & ASLC_SET_PWM_FREQ)
		aslc_stat |= asle_set_pwm_freq(dev_priv, asle->pfmb);

	अगर (aslc_req & ASLC_SUPPORTED_ROTATION_ANGLES)
		aslc_stat |= asle_set_supported_rotation_angles(dev_priv,
							asle->srot);

	अगर (aslc_req & ASLC_BUTTON_ARRAY)
		aslc_stat |= asle_set_button_array(dev_priv, asle->iuer);

	अगर (aslc_req & ASLC_CONVERTIBLE_INDICATOR)
		aslc_stat |= asle_set_convertible(dev_priv, asle->iuer);

	अगर (aslc_req & ASLC_DOCKING_INDICATOR)
		aslc_stat |= asle_set_करोcking(dev_priv, asle->iuer);

	अगर (aslc_req & ASLC_ISCT_STATE_CHANGE)
		aslc_stat |= asle_isct_state(dev_priv);

	asle->aslc = aslc_stat;
पूर्ण

व्योम पूर्णांकel_opregion_asle_पूर्णांकr(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (dev_priv->opregion.asle)
		schedule_work(&dev_priv->opregion.asle_work);
पूर्ण

#घोषणा ACPI_EV_DISPLAY_SWITCH (1<<0)
#घोषणा ACPI_EV_LID            (1<<1)
#घोषणा ACPI_EV_DOCK           (1<<2)

/*
 * The only video events relevant to opregion are 0x80. These indicate either a
 * करोcking event, lid चयन or display चयन request. In Linux, these are
 * handled by the करोck, button and video drivers.
 */
अटल पूर्णांक पूर्णांकel_opregion_video_event(काष्ठा notअगरier_block *nb,
				      अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा पूर्णांकel_opregion *opregion = container_of(nb, काष्ठा पूर्णांकel_opregion,
						       acpi_notअगरier);
	काष्ठा acpi_bus_event *event = data;
	काष्ठा opregion_acpi *acpi;
	पूर्णांक ret = NOTIFY_OK;

	अगर (म_भेद(event->device_class, ACPI_VIDEO_CLASS) != 0)
		वापस NOTIFY_DONE;

	acpi = opregion->acpi;

	अगर (event->type == 0x80 && ((acpi->cevt & 1) == 0))
		ret = NOTIFY_BAD;

	acpi->csts = 0;

	वापस ret;
पूर्ण

/*
 * Initialise the DIDL field in opregion. This passes a list of devices to
 * the firmware. Values are defined by section B.4.2 of the ACPI specअगरication
 * (version 3)
 */

अटल व्योम set_did(काष्ठा पूर्णांकel_opregion *opregion, पूर्णांक i, u32 val)
अणु
	अगर (i < ARRAY_SIZE(opregion->acpi->didl)) अणु
		opregion->acpi->didl[i] = val;
	पूर्ण अन्यथा अणु
		i -= ARRAY_SIZE(opregion->acpi->didl);

		अगर (WARN_ON(i >= ARRAY_SIZE(opregion->acpi->did2)))
			वापस;

		opregion->acpi->did2[i] = val;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_didl_outमाला_दो(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_opregion *opregion = &dev_priv->opregion;
	काष्ठा पूर्णांकel_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	पूर्णांक i = 0, max_outमाला_दो;

	/*
	 * In theory, did2, the extended didl, माला_लो added at opregion version
	 * 3.0. In practice, however, we're supposed to set it क्रम earlier
	 * versions as well, since a BIOS that करोesn't understand did2 should
	 * not look at it anyway. Use a variable so we can tweak this अगर a need
	 * arises later.
	 */
	max_outमाला_दो = ARRAY_SIZE(opregion->acpi->didl) +
		ARRAY_SIZE(opregion->acpi->did2);

	पूर्णांकel_acpi_device_id_update(dev_priv);

	drm_connector_list_iter_begin(&dev_priv->drm, &conn_iter);
	क्रम_each_पूर्णांकel_connector_iter(connector, &conn_iter) अणु
		अगर (i < max_outमाला_दो)
			set_did(opregion, i, connector->acpi_device_id);
		i++;
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	drm_dbg_kms(&dev_priv->drm, "%d outputs detected\n", i);

	अगर (i > max_outमाला_दो)
		drm_err(&dev_priv->drm,
			"More than %d outputs in connector list\n",
			max_outमाला_दो);

	/* If fewer than max outमाला_दो, the list must be null terminated */
	अगर (i < max_outमाला_दो)
		set_did(opregion, i, 0);
पूर्ण

अटल व्योम पूर्णांकel_setup_cadls(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_opregion *opregion = &dev_priv->opregion;
	काष्ठा पूर्णांकel_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	पूर्णांक i = 0;

	/*
	 * Initialize the CADL field from the connector device ids. This is
	 * essentially the same as copying from the DIDL. Technically, this is
	 * not always correct as display outमाला_दो may exist, but not active. This
	 * initialization is necessary क्रम some Clevo laptops that check this
	 * field beक्रमe processing the brightness and display चयनing hotkeys.
	 *
	 * Note that पूर्णांकernal panels should be at the front of the connector
	 * list alपढ़ोy, ensuring they're not left out.
	 */
	drm_connector_list_iter_begin(&dev_priv->drm, &conn_iter);
	क्रम_each_पूर्णांकel_connector_iter(connector, &conn_iter) अणु
		अगर (i >= ARRAY_SIZE(opregion->acpi->cadl))
			अवरोध;
		opregion->acpi->cadl[i++] = connector->acpi_device_id;
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	/* If fewer than 8 active devices, the list must be null terminated */
	अगर (i < ARRAY_SIZE(opregion->acpi->cadl))
		opregion->acpi->cadl[i] = 0;
पूर्ण

अटल व्योम swsci_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_opregion *opregion = &dev_priv->opregion;
	bool requested_callbacks = false;
	u32 पंचांगp;

	/* Sub-function code 0 is okay, let's allow them. */
	opregion->swsci_gbda_sub_functions = 1;
	opregion->swsci_sbcb_sub_functions = 1;

	/* We use GBDA to ask क्रम supported GBDA calls. */
	अगर (swsci(dev_priv, SWSCI_GBDA_SUPPORTED_CALLS, 0, &पंचांगp) == 0) अणु
		/* make the bits match the sub-function codes */
		पंचांगp <<= 1;
		opregion->swsci_gbda_sub_functions |= पंचांगp;
	पूर्ण

	/*
	 * We also use GBDA to ask क्रम _requested_ SBCB callbacks. The driver
	 * must not call पूर्णांकerfaces that are not specअगरically requested by the
	 * bios.
	 */
	अगर (swsci(dev_priv, SWSCI_GBDA_REQUESTED_CALLBACKS, 0, &पंचांगp) == 0) अणु
		/* here, the bits alपढ़ोy match sub-function codes */
		opregion->swsci_sbcb_sub_functions |= पंचांगp;
		requested_callbacks = true;
	पूर्ण

	/*
	 * But we use SBCB to ask क्रम _supported_ SBCB calls. This करोes not mean
	 * the callback is _requested_. But we still can't call पूर्णांकerfaces that
	 * are not requested.
	 */
	अगर (swsci(dev_priv, SWSCI_SBCB_SUPPORTED_CALLBACKS, 0, &पंचांगp) == 0) अणु
		/* make the bits match the sub-function codes */
		u32 low = पंचांगp & 0x7ff;
		u32 high = पंचांगp & ~0xfff; /* bit 11 is reserved */
		पंचांगp = (high << 4) | (low << 1) | 1;

		/* best guess what to करो with supported wrt requested */
		अगर (requested_callbacks) अणु
			u32 req = opregion->swsci_sbcb_sub_functions;
			अगर ((req & पंचांगp) != req)
				drm_dbg(&dev_priv->drm,
					"SWSCI BIOS requested (%08x) SBCB callbacks that are not supported (%08x)\n",
					req, पंचांगp);
			/* XXX: क्रम now, trust the requested callbacks */
			/* opregion->swsci_sbcb_sub_functions &= पंचांगp; */
		पूर्ण अन्यथा अणु
			opregion->swsci_sbcb_sub_functions |= पंचांगp;
		पूर्ण
	पूर्ण

	drm_dbg(&dev_priv->drm,
		"SWSCI GBDA callbacks %08x, SBCB callbacks %08x\n",
		opregion->swsci_gbda_sub_functions,
		opregion->swsci_sbcb_sub_functions);
पूर्ण

अटल पूर्णांक पूर्णांकel_no_opregion_vbt_callback(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	DRM_DEBUG_KMS("Falling back to manually reading VBT from "
		      "VBIOS ROM for %s\n", id->ident);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id पूर्णांकel_no_opregion_vbt[] = अणु
	अणु
		.callback = पूर्णांकel_no_opregion_vbt_callback,
		.ident = "ThinkCentre A57",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "97027RG"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक पूर्णांकel_load_vbt_firmware(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_opregion *opregion = &dev_priv->opregion;
	स्थिर काष्ठा firmware *fw = शून्य;
	स्थिर अक्षर *name = dev_priv->params.vbt_firmware;
	पूर्णांक ret;

	अगर (!name || !*name)
		वापस -ENOENT;

	ret = request_firmware(&fw, name, dev_priv->drm.dev);
	अगर (ret) अणु
		drm_err(&dev_priv->drm,
			"Requesting VBT firmware \"%s\" failed (%d)\n",
			name, ret);
		वापस ret;
	पूर्ण

	अगर (पूर्णांकel_bios_is_valid_vbt(fw->data, fw->size)) अणु
		opregion->vbt_firmware = kmemdup(fw->data, fw->size, GFP_KERNEL);
		अगर (opregion->vbt_firmware) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "Found valid VBT firmware \"%s\"\n", name);
			opregion->vbt = opregion->vbt_firmware;
			opregion->vbt_size = fw->size;
			ret = 0;
		पूर्ण अन्यथा अणु
			ret = -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		drm_dbg_kms(&dev_priv->drm, "Invalid VBT firmware \"%s\"\n",
			    name);
		ret = -EINVAL;
	पूर्ण

	release_firmware(fw);

	वापस ret;
पूर्ण

पूर्णांक पूर्णांकel_opregion_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_opregion *opregion = &dev_priv->opregion;
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);
	u32 asls, mboxes;
	अक्षर buf[माप(OPREGION_SIGNATURE)];
	पूर्णांक err = 0;
	व्योम *base;
	स्थिर व्योम *vbt;
	u32 vbt_size;

	BUILD_BUG_ON(माप(काष्ठा opregion_header) != 0x100);
	BUILD_BUG_ON(माप(काष्ठा opregion_acpi) != 0x100);
	BUILD_BUG_ON(माप(काष्ठा opregion_swsci) != 0x100);
	BUILD_BUG_ON(माप(काष्ठा opregion_asle) != 0x100);
	BUILD_BUG_ON(माप(काष्ठा opregion_asle_ext) != 0x400);

	pci_पढ़ो_config_dword(pdev, ASLS, &asls);
	drm_dbg(&dev_priv->drm, "graphic opregion physical addr: 0x%x\n",
		asls);
	अगर (asls == 0) अणु
		drm_dbg(&dev_priv->drm, "ACPI OpRegion not supported!\n");
		वापस -ENOTSUPP;
	पूर्ण

	INIT_WORK(&opregion->asle_work, asle_work);

	base = memremap(asls, OPREGION_SIZE, MEMREMAP_WB);
	अगर (!base)
		वापस -ENOMEM;

	स_नकल(buf, base, माप(buf));

	अगर (स_भेद(buf, OPREGION_SIGNATURE, 16)) अणु
		drm_dbg(&dev_priv->drm, "opregion signature mismatch\n");
		err = -EINVAL;
		जाओ err_out;
	पूर्ण
	opregion->header = base;
	opregion->lid_state = base + ACPI_CLID;

	drm_dbg(&dev_priv->drm, "ACPI OpRegion version %u.%u.%u\n",
		opregion->header->over.major,
		opregion->header->over.minor,
		opregion->header->over.revision);

	mboxes = opregion->header->mboxes;
	अगर (mboxes & MBOX_ACPI) अणु
		drm_dbg(&dev_priv->drm, "Public ACPI methods supported\n");
		opregion->acpi = base + OPREGION_ACPI_OFFSET;
		/*
		 * Indicate we handle monitor hotplug events ourselves so we करो
		 * not need ACPI notअगरications क्रम them. Disabling these aव्योमs
		 * triggering the AML code करोing the notअगरation, which may be
		 * broken as Winकरोws also seems to disable these.
		 */
		opregion->acpi->chpd = 1;
	पूर्ण

	अगर (mboxes & MBOX_SWSCI) अणु
		drm_dbg(&dev_priv->drm, "SWSCI supported\n");
		opregion->swsci = base + OPREGION_SWSCI_OFFSET;
		swsci_setup(dev_priv);
	पूर्ण

	अगर (mboxes & MBOX_ASLE) अणु
		drm_dbg(&dev_priv->drm, "ASLE supported\n");
		opregion->asle = base + OPREGION_ASLE_OFFSET;

		opregion->asle->ardy = ASLE_ARDY_NOT_READY;
	पूर्ण

	अगर (mboxes & MBOX_ASLE_EXT)
		drm_dbg(&dev_priv->drm, "ASLE extension supported\n");

	अगर (पूर्णांकel_load_vbt_firmware(dev_priv) == 0)
		जाओ out;

	अगर (dmi_check_प्रणाली(पूर्णांकel_no_opregion_vbt))
		जाओ out;

	अगर (opregion->header->over.major >= 2 && opregion->asle &&
	    opregion->asle->rvda && opregion->asle->rvds) अणु
		resource_माप_प्रकार rvda = opregion->asle->rvda;

		/*
		 * opregion 2.0: rvda is the physical VBT address.
		 *
		 * opregion 2.1+: rvda is अचिन्हित, relative offset from
		 * opregion base, and should never poपूर्णांक within opregion.
		 */
		अगर (opregion->header->over.major > 2 ||
		    opregion->header->over.minor >= 1) अणु
			drm_WARN_ON(&dev_priv->drm, rvda < OPREGION_SIZE);

			rvda += asls;
		पूर्ण

		opregion->rvda = memremap(rvda, opregion->asle->rvds,
					  MEMREMAP_WB);

		vbt = opregion->rvda;
		vbt_size = opregion->asle->rvds;
		अगर (पूर्णांकel_bios_is_valid_vbt(vbt, vbt_size)) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "Found valid VBT in ACPI OpRegion (RVDA)\n");
			opregion->vbt = vbt;
			opregion->vbt_size = vbt_size;
			जाओ out;
		पूर्ण अन्यथा अणु
			drm_dbg_kms(&dev_priv->drm,
				    "Invalid VBT in ACPI OpRegion (RVDA)\n");
			memunmap(opregion->rvda);
			opregion->rvda = शून्य;
		पूर्ण
	पूर्ण

	vbt = base + OPREGION_VBT_OFFSET;
	/*
	 * The VBT specअगरication says that अगर the ASLE ext mailbox is not used
	 * its area is reserved, but on some CHT boards the VBT extends पूर्णांकo the
	 * ASLE ext area. Allow this even though it is against the spec, so we
	 * करो not end up rejecting the VBT on those boards (and end up not
	 * finding the LCD panel because of this).
	 */
	vbt_size = (mboxes & MBOX_ASLE_EXT) ?
		OPREGION_ASLE_EXT_OFFSET : OPREGION_SIZE;
	vbt_size -= OPREGION_VBT_OFFSET;
	अगर (पूर्णांकel_bios_is_valid_vbt(vbt, vbt_size)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Found valid VBT in ACPI OpRegion (Mailbox #4)\n");
		opregion->vbt = vbt;
		opregion->vbt_size = vbt_size;
	पूर्ण अन्यथा अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Invalid VBT in ACPI OpRegion (Mailbox #4)\n");
	पूर्ण

out:
	वापस 0;

err_out:
	memunmap(base);
	वापस err;
पूर्ण

अटल पूर्णांक पूर्णांकel_use_opregion_panel_type_callback(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	DRM_INFO("Using panel type from OpRegion on %s\n", id->ident);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id पूर्णांकel_use_opregion_panel_type[] = अणु
	अणु
		.callback = पूर्णांकel_use_opregion_panel_type_callback,
		.ident = "Conrac GmbH IX45GM2",
		.matches = अणुDMI_MATCH(DMI_SYS_VENDOR, "Conrac GmbH"),
			    DMI_MATCH(DMI_PRODUCT_NAME, "IX45GM2"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

पूर्णांक
पूर्णांकel_opregion_get_panel_type(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 panel_details;
	पूर्णांक ret;

	ret = swsci(dev_priv, SWSCI_GBDA_PANEL_DETAILS, 0x0, &panel_details);
	अगर (ret)
		वापस ret;

	ret = (panel_details >> 8) & 0xff;
	अगर (ret > 0x10) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Invalid OpRegion panel type 0x%x\n", ret);
		वापस -EINVAL;
	पूर्ण

	/* fall back to VBT panel type? */
	अगर (ret == 0x0) अणु
		drm_dbg_kms(&dev_priv->drm, "No panel type in OpRegion\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * So far we know that some machined must use it, others must not use it.
	 * There करोesn't seem to be any way to determine which way to go, except
	 * via a quirk list :(
	 */
	अगर (!dmi_check_प्रणाली(पूर्णांकel_use_opregion_panel_type)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Ignoring OpRegion panel type (%d)\n", ret - 1);
		वापस -ENODEV;
	पूर्ण

	वापस ret - 1;
पूर्ण

व्योम पूर्णांकel_opregion_रेजिस्टर(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा पूर्णांकel_opregion *opregion = &i915->opregion;

	अगर (!opregion->header)
		वापस;

	अगर (opregion->acpi) अणु
		opregion->acpi_notअगरier.notअगरier_call =
			पूर्णांकel_opregion_video_event;
		रेजिस्टर_acpi_notअगरier(&opregion->acpi_notअगरier);
	पूर्ण

	पूर्णांकel_opregion_resume(i915);
पूर्ण

व्योम पूर्णांकel_opregion_resume(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा पूर्णांकel_opregion *opregion = &i915->opregion;

	अगर (!opregion->header)
		वापस;

	अगर (opregion->acpi) अणु
		पूर्णांकel_didl_outमाला_दो(i915);
		पूर्णांकel_setup_cadls(i915);

		/*
		 * Notअगरy BIOS we are पढ़ोy to handle ACPI video ext notअगरs.
		 * Right now, all the events are handled by the ACPI video
		 * module. We करोn't actually need to करो anything with them.
		 */
		opregion->acpi->csts = 0;
		opregion->acpi->drdy = 1;
	पूर्ण

	अगर (opregion->asle) अणु
		opregion->asle->tche = ASLE_TCHE_BLC_EN;
		opregion->asle->ardy = ASLE_ARDY_READY;
	पूर्ण

	पूर्णांकel_opregion_notअगरy_adapter(i915, PCI_D0);
पूर्ण

व्योम पूर्णांकel_opregion_suspend(काष्ठा drm_i915_निजी *i915, pci_घातer_t state)
अणु
	काष्ठा पूर्णांकel_opregion *opregion = &i915->opregion;

	अगर (!opregion->header)
		वापस;

	पूर्णांकel_opregion_notअगरy_adapter(i915, state);

	अगर (opregion->asle)
		opregion->asle->ardy = ASLE_ARDY_NOT_READY;

	cancel_work_sync(&i915->opregion.asle_work);

	अगर (opregion->acpi)
		opregion->acpi->drdy = 0;
पूर्ण

व्योम पूर्णांकel_opregion_unरेजिस्टर(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा पूर्णांकel_opregion *opregion = &i915->opregion;

	पूर्णांकel_opregion_suspend(i915, PCI_D1);

	अगर (!opregion->header)
		वापस;

	अगर (opregion->acpi_notअगरier.notअगरier_call) अणु
		unरेजिस्टर_acpi_notअगरier(&opregion->acpi_notअगरier);
		opregion->acpi_notअगरier.notअगरier_call = शून्य;
	पूर्ण

	/* just clear all opregion memory poपूर्णांकers now */
	memunmap(opregion->header);
	अगर (opregion->rvda) अणु
		memunmap(opregion->rvda);
		opregion->rvda = शून्य;
	पूर्ण
	अगर (opregion->vbt_firmware) अणु
		kमुक्त(opregion->vbt_firmware);
		opregion->vbt_firmware = शून्य;
	पूर्ण
	opregion->header = शून्य;
	opregion->acpi = शून्य;
	opregion->swsci = शून्य;
	opregion->asle = शून्य;
	opregion->vbt = शून्य;
	opregion->lid_state = शून्य;
पूर्ण
