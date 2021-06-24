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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Eric Anholt <eric@anholt.net>
 *    Thomas Richter <thor@math.tu-berlin.de>
 *
 * Minor modअगरications (Dithering enable):
 *    Thomas Richter <thor@math.tu-berlin.de>
 *
 */

#समावेश "intel_display_types.h"
#समावेश "intel_dvo_dev.h"

/*
 * रेजिस्टर definitions क्रम the i82807aa.
 *
 * Documentation on this chipset can be found in datasheet #29069001 at
 * पूर्णांकel.com.
 */

/*
 * VCH Revision & GMBus Base Addr
 */
#घोषणा VR00		0x00
# define VR00_BASE_ADDRESS_MASK		0x007f

/*
 * Functionality Enable
 */
#घोषणा VR01		0x01

/*
 * Enable the panel fitter
 */
# define VR01_PANEL_FIT_ENABLE		(1 << 3)
/*
 * Enables the LCD display.
 *
 * This must not be set जबतक VR01_DVO_BYPASS_ENABLE is set.
 */
# define VR01_LCD_ENABLE		(1 << 2)
/* Enables the DVO repeater. */
# define VR01_DVO_BYPASS_ENABLE		(1 << 1)
/* Enables the DVO घड़ी */
# define VR01_DVO_ENABLE		(1 << 0)
/* Enable dithering क्रम 18bpp panels. Not करोcumented. */
# define VR01_DITHER_ENABLE             (1 << 4)

/*
 * LCD Interface Format
 */
#घोषणा VR10		0x10
/* Enables LVDS output instead of CMOS */
# define VR10_LVDS_ENABLE		(1 << 4)
/* Enables 18-bit LVDS output. */
# define VR10_INTERFACE_1X18		(0 << 2)
/* Enables 24-bit LVDS or CMOS output */
# define VR10_INTERFACE_1X24		(1 << 2)
/* Enables 2x18-bit LVDS or CMOS output. */
# define VR10_INTERFACE_2X18		(2 << 2)
/* Enables 2x24-bit LVDS output */
# define VR10_INTERFACE_2X24		(3 << 2)
/* Mask that defines the depth of the pipeline */
# define VR10_INTERFACE_DEPTH_MASK      (3 << 2)

/*
 * VR20 LCD Horizontal Display Size
 */
#घोषणा VR20	0x20

/*
 * LCD Vertical Display Size
 */
#घोषणा VR21	0x21

/*
 * Panel घातer करोwn status
 */
#घोषणा VR30		0x30
/* Read only bit indicating that the panel is not in a safe घातeroff state. */
# define VR30_PANEL_ON			(1 << 15)

#घोषणा VR40		0x40
# define VR40_STALL_ENABLE		(1 << 13)
# define VR40_VERTICAL_INTERP_ENABLE	(1 << 12)
# define VR40_ENHANCED_PANEL_FITTING	(1 << 11)
# define VR40_HORIZONTAL_INTERP_ENABLE	(1 << 10)
# define VR40_AUTO_RATIO_ENABLE		(1 << 9)
# define VR40_CLOCK_GATING_ENABLE	(1 << 8)

/*
 * Panel Fitting Vertical Ratio
 * (((image_height - 1) << 16) / ((panel_height - 1))) >> 2
 */
#घोषणा VR41		0x41

/*
 * Panel Fitting Horizontal Ratio
 * (((image_width - 1) << 16) / ((panel_width - 1))) >> 2
 */
#घोषणा VR42		0x42

/*
 * Horizontal Image Size
 */
#घोषणा VR43		0x43

/* VR80 GPIO 0
 */
#घोषणा VR80	    0x80
#घोषणा VR81	    0x81
#घोषणा VR82	    0x82
#घोषणा VR83	    0x83
#घोषणा VR84	    0x84
#घोषणा VR85	    0x85
#घोषणा VR86	    0x86
#घोषणा VR87	    0x87

/* VR88 GPIO 8
 */
#घोषणा VR88	    0x88

/* Graphics BIOS scratch 0
 */
#घोषणा VR8E	    0x8E
# define VR8E_PANEL_TYPE_MASK		(0xf << 0)
# define VR8E_PANEL_INTERFACE_CMOS	(0 << 4)
# define VR8E_PANEL_INTERFACE_LVDS	(1 << 4)
# define VR8E_FORCE_DEFAULT_PANEL	(1 << 5)

/* Graphics BIOS scratch 1
 */
#घोषणा VR8F	    0x8F
# define VR8F_VCH_PRESENT		(1 << 0)
# define VR8F_DISPLAY_CONN		(1 << 1)
# define VR8F_POWER_MASK		(0x3c)
# define VR8F_POWER_POS			(2)

/* Some Bios implementations करो not restore the DVO state upon
 * resume from standby. Thus, this driver has to handle it
 * instead. The following list contains all रेजिस्टरs that
 * require saving.
 */
अटल स्थिर u16 backup_addresses[] = अणु
	0x11, 0x12,
	0x18, 0x19, 0x1a, 0x1f,
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
	0x8e, 0x8f,
	0x10		/* this must come last */
पूर्ण;


काष्ठा ivch_priv अणु
	bool quiet;

	u16 width, height;

	/* Register backup */

	u16 reg_backup[ARRAY_SIZE(backup_addresses)];
पूर्ण;


अटल व्योम ivch_dump_regs(काष्ठा पूर्णांकel_dvo_device *dvo);
/*
 * Reads a रेजिस्टर on the ivch.
 *
 * Each of the 256 रेजिस्टरs are 16 bits दीर्घ.
 */
अटल bool ivch_पढ़ो(काष्ठा पूर्णांकel_dvo_device *dvo, पूर्णांक addr, u16 *data)
अणु
	काष्ठा ivch_priv *priv = dvo->dev_priv;
	काष्ठा i2c_adapter *adapter = dvo->i2c_bus;
	u8 out_buf[1];
	u8 in_buf[2];

	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = dvo->slave_addr,
			.flags = I2C_M_RD,
			.len = 0,
		पूर्ण,
		अणु
			.addr = 0,
			.flags = I2C_M_NOSTART,
			.len = 1,
			.buf = out_buf,
		पूर्ण,
		अणु
			.addr = dvo->slave_addr,
			.flags = I2C_M_RD | I2C_M_NOSTART,
			.len = 2,
			.buf = in_buf,
		पूर्ण
	पूर्ण;

	out_buf[0] = addr;

	अगर (i2c_transfer(adapter, msgs, 3) == 3) अणु
		*data = (in_buf[1] << 8) | in_buf[0];
		वापस true;
	पूर्ण

	अगर (!priv->quiet) अणु
		DRM_DEBUG_KMS("Unable to read register 0x%02x from "
				"%s:%02x.\n",
			  addr, adapter->name, dvo->slave_addr);
	पूर्ण
	वापस false;
पूर्ण

/* Writes a 16-bit रेजिस्टर on the ivch */
अटल bool ivch_ग_लिखो(काष्ठा पूर्णांकel_dvo_device *dvo, पूर्णांक addr, u16 data)
अणु
	काष्ठा ivch_priv *priv = dvo->dev_priv;
	काष्ठा i2c_adapter *adapter = dvo->i2c_bus;
	u8 out_buf[3];
	काष्ठा i2c_msg msg = अणु
		.addr = dvo->slave_addr,
		.flags = 0,
		.len = 3,
		.buf = out_buf,
	पूर्ण;

	out_buf[0] = addr;
	out_buf[1] = data & 0xff;
	out_buf[2] = data >> 8;

	अगर (i2c_transfer(adapter, &msg, 1) == 1)
		वापस true;

	अगर (!priv->quiet) अणु
		DRM_DEBUG_KMS("Unable to write register 0x%02x to %s:%d.\n",
			  addr, adapter->name, dvo->slave_addr);
	पूर्ण

	वापस false;
पूर्ण

/* Probes the given bus and slave address क्रम an ivch */
अटल bool ivch_init(काष्ठा पूर्णांकel_dvo_device *dvo,
		      काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा ivch_priv *priv;
	u16 temp;
	पूर्णांक i;

	priv = kzalloc(माप(काष्ठा ivch_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस false;

	dvo->i2c_bus = adapter;
	dvo->dev_priv = priv;
	priv->quiet = true;

	अगर (!ivch_पढ़ो(dvo, VR00, &temp))
		जाओ out;
	priv->quiet = false;

	/* Since the identअगरication bits are probably zeroes, which करोesn't seem
	 * very unique, check that the value in the base address field matches
	 * the address it's responding on.
	 */
	अगर ((temp & VR00_BASE_ADDRESS_MASK) != dvo->slave_addr) अणु
		DRM_DEBUG_KMS("ivch detect failed due to address mismatch "
			  "(%d vs %d)\n",
			  (temp & VR00_BASE_ADDRESS_MASK), dvo->slave_addr);
		जाओ out;
	पूर्ण

	ivch_पढ़ो(dvo, VR20, &priv->width);
	ivch_पढ़ो(dvo, VR21, &priv->height);

	/* Make a backup of the रेजिस्टरs to be able to restore them
	 * upon suspend.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(backup_addresses); i++)
		ivch_पढ़ो(dvo, backup_addresses[i], priv->reg_backup + i);

	ivch_dump_regs(dvo);

	वापस true;

out:
	kमुक्त(priv);
	वापस false;
पूर्ण

अटल क्रमागत drm_connector_status ivch_detect(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	वापस connector_status_connected;
पूर्ण

अटल क्रमागत drm_mode_status ivch_mode_valid(काष्ठा पूर्णांकel_dvo_device *dvo,
					    काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->घड़ी > 112000)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

/* Restore the DVO रेजिस्टरs after a resume
 * from RAM. Registers have been saved during
 * the initialization.
 */
अटल व्योम ivch_reset(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	काष्ठा ivch_priv *priv = dvo->dev_priv;
	पूर्णांक i;

	DRM_DEBUG_KMS("Resetting the IVCH registers\n");

	ivch_ग_लिखो(dvo, VR10, 0x0000);

	क्रम (i = 0; i < ARRAY_SIZE(backup_addresses); i++)
		ivch_ग_लिखो(dvo, backup_addresses[i], priv->reg_backup[i]);
पूर्ण

/* Sets the घातer state of the panel connected to the ivch */
अटल व्योम ivch_dpms(काष्ठा पूर्णांकel_dvo_device *dvo, bool enable)
अणु
	पूर्णांक i;
	u16 vr01, vr30, backlight;

	ivch_reset(dvo);

	/* Set the new घातer state of the panel. */
	अगर (!ivch_पढ़ो(dvo, VR01, &vr01))
		वापस;

	अगर (enable)
		backlight = 1;
	अन्यथा
		backlight = 0;

	ivch_ग_लिखो(dvo, VR80, backlight);

	अगर (enable)
		vr01 |= VR01_LCD_ENABLE | VR01_DVO_ENABLE;
	अन्यथा
		vr01 &= ~(VR01_LCD_ENABLE | VR01_DVO_ENABLE);

	ivch_ग_लिखो(dvo, VR01, vr01);

	/* Wait क्रम the panel to make its state transition */
	क्रम (i = 0; i < 100; i++) अणु
		अगर (!ivch_पढ़ो(dvo, VR30, &vr30))
			अवरोध;

		अगर (((vr30 & VR30_PANEL_ON) != 0) == enable)
			अवरोध;
		udelay(1000);
	पूर्ण
	/* रुको some more; vch may fail to resync someबार without this */
	udelay(16 * 1000);
पूर्ण

अटल bool ivch_get_hw_state(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	u16 vr01;

	ivch_reset(dvo);

	/* Set the new घातer state of the panel. */
	अगर (!ivch_पढ़ो(dvo, VR01, &vr01))
		वापस false;

	अगर (vr01 & VR01_LCD_ENABLE)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम ivch_mode_set(काष्ठा पूर्णांकel_dvo_device *dvo,
			  स्थिर काष्ठा drm_display_mode *mode,
			  स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा ivch_priv *priv = dvo->dev_priv;
	u16 vr40 = 0;
	u16 vr01 = 0;
	u16 vr10;

	ivch_reset(dvo);

	vr10 = priv->reg_backup[ARRAY_SIZE(backup_addresses) - 1];

	/* Enable dithering क्रम 18 bpp pipelines */
	vr10 &= VR10_INTERFACE_DEPTH_MASK;
	अगर (vr10 == VR10_INTERFACE_2X18 || vr10 == VR10_INTERFACE_1X18)
		vr01 = VR01_DITHER_ENABLE;

	vr40 = (VR40_STALL_ENABLE | VR40_VERTICAL_INTERP_ENABLE |
		VR40_HORIZONTAL_INTERP_ENABLE);

	अगर (mode->hdisplay != adjusted_mode->crtc_hdisplay ||
	    mode->vdisplay != adjusted_mode->crtc_vdisplay) अणु
		u16 x_ratio, y_ratio;

		vr01 |= VR01_PANEL_FIT_ENABLE;
		vr40 |= VR40_CLOCK_GATING_ENABLE;
		x_ratio = (((mode->hdisplay - 1) << 16) /
			   (adjusted_mode->crtc_hdisplay - 1)) >> 2;
		y_ratio = (((mode->vdisplay - 1) << 16) /
			   (adjusted_mode->crtc_vdisplay - 1)) >> 2;
		ivch_ग_लिखो(dvo, VR42, x_ratio);
		ivch_ग_लिखो(dvo, VR41, y_ratio);
	पूर्ण अन्यथा अणु
		vr01 &= ~VR01_PANEL_FIT_ENABLE;
		vr40 &= ~VR40_CLOCK_GATING_ENABLE;
	पूर्ण
	vr40 &= ~VR40_AUTO_RATIO_ENABLE;

	ivch_ग_लिखो(dvo, VR01, vr01);
	ivch_ग_लिखो(dvo, VR40, vr40);
पूर्ण

अटल व्योम ivch_dump_regs(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	u16 val;

	ivch_पढ़ो(dvo, VR00, &val);
	DRM_DEBUG_KMS("VR00: 0x%04x\n", val);
	ivch_पढ़ो(dvo, VR01, &val);
	DRM_DEBUG_KMS("VR01: 0x%04x\n", val);
	ivch_पढ़ो(dvo, VR10, &val);
	DRM_DEBUG_KMS("VR10: 0x%04x\n", val);
	ivch_पढ़ो(dvo, VR30, &val);
	DRM_DEBUG_KMS("VR30: 0x%04x\n", val);
	ivch_पढ़ो(dvo, VR40, &val);
	DRM_DEBUG_KMS("VR40: 0x%04x\n", val);

	/* GPIO रेजिस्टरs */
	ivch_पढ़ो(dvo, VR80, &val);
	DRM_DEBUG_KMS("VR80: 0x%04x\n", val);
	ivch_पढ़ो(dvo, VR81, &val);
	DRM_DEBUG_KMS("VR81: 0x%04x\n", val);
	ivch_पढ़ो(dvo, VR82, &val);
	DRM_DEBUG_KMS("VR82: 0x%04x\n", val);
	ivch_पढ़ो(dvo, VR83, &val);
	DRM_DEBUG_KMS("VR83: 0x%04x\n", val);
	ivch_पढ़ो(dvo, VR84, &val);
	DRM_DEBUG_KMS("VR84: 0x%04x\n", val);
	ivch_पढ़ो(dvo, VR85, &val);
	DRM_DEBUG_KMS("VR85: 0x%04x\n", val);
	ivch_पढ़ो(dvo, VR86, &val);
	DRM_DEBUG_KMS("VR86: 0x%04x\n", val);
	ivch_पढ़ो(dvo, VR87, &val);
	DRM_DEBUG_KMS("VR87: 0x%04x\n", val);
	ivch_पढ़ो(dvo, VR88, &val);
	DRM_DEBUG_KMS("VR88: 0x%04x\n", val);

	/* Scratch रेजिस्टर 0 - AIM Panel type */
	ivch_पढ़ो(dvo, VR8E, &val);
	DRM_DEBUG_KMS("VR8E: 0x%04x\n", val);

	/* Scratch रेजिस्टर 1 - Status रेजिस्टर */
	ivch_पढ़ो(dvo, VR8F, &val);
	DRM_DEBUG_KMS("VR8F: 0x%04x\n", val);
पूर्ण

अटल व्योम ivch_destroy(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	काष्ठा ivch_priv *priv = dvo->dev_priv;

	अगर (priv) अणु
		kमुक्त(priv);
		dvo->dev_priv = शून्य;
	पूर्ण
पूर्ण

स्थिर काष्ठा पूर्णांकel_dvo_dev_ops ivch_ops = अणु
	.init = ivch_init,
	.dpms = ivch_dpms,
	.get_hw_state = ivch_get_hw_state,
	.mode_valid = ivch_mode_valid,
	.mode_set = ivch_mode_set,
	.detect = ivch_detect,
	.dump_regs = ivch_dump_regs,
	.destroy = ivch_destroy,
पूर्ण;
