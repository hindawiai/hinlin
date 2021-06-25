<शैली गुरु>
/*
 * Copyright 2007-8 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
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
 *
 * Authors: Dave Airlie
 *          Alex Deucher
 */

#समावेश <linux/pci.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/radeon_drm.h>

#समावेश "radeon.h"

#समावेश "atom.h"
#समावेश "atom-bits.h"
#समावेश "radeon_asic.h"
#समावेश "radeon_atombios.h"
#समावेश "radeon_legacy_encoders.h"

जोड़ atom_supported_devices अणु
	काष्ठा _ATOM_SUPPORTED_DEVICES_INFO info;
	काष्ठा _ATOM_SUPPORTED_DEVICES_INFO_2 info_2;
	काष्ठा _ATOM_SUPPORTED_DEVICES_INFO_2d1 info_2d1;
पूर्ण;

अटल व्योम radeon_lookup_i2c_gpio_quirks(काष्ठा radeon_device *rdev,
					  ATOM_GPIO_I2C_ASSIGMENT *gpio,
					  u8 index)
अणु
	/* r4xx mask is technically not used by the hw, so patch in the legacy mask bits */
	अगर ((rdev->family == CHIP_R420) ||
	    (rdev->family == CHIP_R423) ||
	    (rdev->family == CHIP_RV410)) अणु
		अगर ((le16_to_cpu(gpio->usClkMaskRegisterIndex) == 0x0018) ||
		    (le16_to_cpu(gpio->usClkMaskRegisterIndex) == 0x0019) ||
		    (le16_to_cpu(gpio->usClkMaskRegisterIndex) == 0x001a)) अणु
			gpio->ucClkMaskShअगरt = 0x19;
			gpio->ucDataMaskShअगरt = 0x18;
		पूर्ण
	पूर्ण

	/* some evergreen boards have bad data क्रम this entry */
	अगर (ASIC_IS_DCE4(rdev)) अणु
		अगर ((index == 7) &&
		    (le16_to_cpu(gpio->usClkMaskRegisterIndex) == 0x1936) &&
		    (gpio->sucI2cId.ucAccess == 0)) अणु
			gpio->sucI2cId.ucAccess = 0x97;
			gpio->ucDataMaskShअगरt = 8;
			gpio->ucDataEnShअगरt = 8;
			gpio->ucDataY_Shअगरt = 8;
			gpio->ucDataA_Shअगरt = 8;
		पूर्ण
	पूर्ण

	/* some DCE3 boards have bad data क्रम this entry */
	अगर (ASIC_IS_DCE3(rdev)) अणु
		अगर ((index == 4) &&
		    (le16_to_cpu(gpio->usClkMaskRegisterIndex) == 0x1fda) &&
		    (gpio->sucI2cId.ucAccess == 0x94))
			gpio->sucI2cId.ucAccess = 0x14;
	पूर्ण
पूर्ण

अटल काष्ठा radeon_i2c_bus_rec radeon_get_bus_rec_क्रम_i2c_gpio(ATOM_GPIO_I2C_ASSIGMENT *gpio)
अणु
	काष्ठा radeon_i2c_bus_rec i2c;

	स_रखो(&i2c, 0, माप(काष्ठा radeon_i2c_bus_rec));

	i2c.mask_clk_reg = le16_to_cpu(gpio->usClkMaskRegisterIndex) * 4;
	i2c.mask_data_reg = le16_to_cpu(gpio->usDataMaskRegisterIndex) * 4;
	i2c.en_clk_reg = le16_to_cpu(gpio->usClkEnRegisterIndex) * 4;
	i2c.en_data_reg = le16_to_cpu(gpio->usDataEnRegisterIndex) * 4;
	i2c.y_clk_reg = le16_to_cpu(gpio->usClkY_RegisterIndex) * 4;
	i2c.y_data_reg = le16_to_cpu(gpio->usDataY_RegisterIndex) * 4;
	i2c.a_clk_reg = le16_to_cpu(gpio->usClkA_RegisterIndex) * 4;
	i2c.a_data_reg = le16_to_cpu(gpio->usDataA_RegisterIndex) * 4;
	i2c.mask_clk_mask = (1 << gpio->ucClkMaskShअगरt);
	i2c.mask_data_mask = (1 << gpio->ucDataMaskShअगरt);
	i2c.en_clk_mask = (1 << gpio->ucClkEnShअगरt);
	i2c.en_data_mask = (1 << gpio->ucDataEnShअगरt);
	i2c.y_clk_mask = (1 << gpio->ucClkY_Shअगरt);
	i2c.y_data_mask = (1 << gpio->ucDataY_Shअगरt);
	i2c.a_clk_mask = (1 << gpio->ucClkA_Shअगरt);
	i2c.a_data_mask = (1 << gpio->ucDataA_Shअगरt);

	अगर (gpio->sucI2cId.sbfAccess.bfHW_Capable)
		i2c.hw_capable = true;
	अन्यथा
		i2c.hw_capable = false;

	अगर (gpio->sucI2cId.ucAccess == 0xa0)
		i2c.mm_i2c = true;
	अन्यथा
		i2c.mm_i2c = false;

	i2c.i2c_id = gpio->sucI2cId.ucAccess;

	अगर (i2c.mask_clk_reg)
		i2c.valid = true;
	अन्यथा
		i2c.valid = false;

	वापस i2c;
पूर्ण

अटल काष्ठा radeon_i2c_bus_rec radeon_lookup_i2c_gpio(काष्ठा radeon_device *rdev,
							       uपूर्णांक8_t id)
अणु
	काष्ठा atom_context *ctx = rdev->mode_info.atom_context;
	ATOM_GPIO_I2C_ASSIGMENT *gpio;
	काष्ठा radeon_i2c_bus_rec i2c;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, GPIO_I2C_Info);
	काष्ठा _ATOM_GPIO_I2C_INFO *i2c_info;
	uपूर्णांक16_t data_offset, size;
	पूर्णांक i, num_indices;

	स_रखो(&i2c, 0, माप(काष्ठा radeon_i2c_bus_rec));
	i2c.valid = false;

	अगर (atom_parse_data_header(ctx, index, &size, शून्य, शून्य, &data_offset)) अणु
		i2c_info = (काष्ठा _ATOM_GPIO_I2C_INFO *)(ctx->bios + data_offset);

		num_indices = (size - माप(ATOM_COMMON_TABLE_HEADER)) /
			माप(ATOM_GPIO_I2C_ASSIGMENT);

		gpio = &i2c_info->asGPIO_Info[0];
		क्रम (i = 0; i < num_indices; i++) अणु

			radeon_lookup_i2c_gpio_quirks(rdev, gpio, i);

			अगर (gpio->sucI2cId.ucAccess == id) अणु
				i2c = radeon_get_bus_rec_क्रम_i2c_gpio(gpio);
				अवरोध;
			पूर्ण
			gpio = (ATOM_GPIO_I2C_ASSIGMENT *)
				((u8 *)gpio + माप(ATOM_GPIO_I2C_ASSIGMENT));
		पूर्ण
	पूर्ण

	वापस i2c;
पूर्ण

व्योम radeon_atombios_i2c_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा atom_context *ctx = rdev->mode_info.atom_context;
	ATOM_GPIO_I2C_ASSIGMENT *gpio;
	काष्ठा radeon_i2c_bus_rec i2c;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, GPIO_I2C_Info);
	काष्ठा _ATOM_GPIO_I2C_INFO *i2c_info;
	uपूर्णांक16_t data_offset, size;
	पूर्णांक i, num_indices;
	अक्षर sपंचांगp[32];

	अगर (atom_parse_data_header(ctx, index, &size, शून्य, शून्य, &data_offset)) अणु
		i2c_info = (काष्ठा _ATOM_GPIO_I2C_INFO *)(ctx->bios + data_offset);

		num_indices = (size - माप(ATOM_COMMON_TABLE_HEADER)) /
			माप(ATOM_GPIO_I2C_ASSIGMENT);

		gpio = &i2c_info->asGPIO_Info[0];
		क्रम (i = 0; i < num_indices; i++) अणु
			radeon_lookup_i2c_gpio_quirks(rdev, gpio, i);

			i2c = radeon_get_bus_rec_क्रम_i2c_gpio(gpio);

			अगर (i2c.valid) अणु
				प्र_लिखो(sपंचांगp, "0x%x", i2c.i2c_id);
				rdev->i2c_bus[i] = radeon_i2c_create(rdev->ddev, &i2c, sपंचांगp);
			पूर्ण
			gpio = (ATOM_GPIO_I2C_ASSIGMENT *)
				((u8 *)gpio + माप(ATOM_GPIO_I2C_ASSIGMENT));
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा radeon_gpio_rec radeon_atombios_lookup_gpio(काष्ठा radeon_device *rdev,
						   u8 id)
अणु
	काष्ठा atom_context *ctx = rdev->mode_info.atom_context;
	काष्ठा radeon_gpio_rec gpio;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, GPIO_Pin_LUT);
	काष्ठा _ATOM_GPIO_PIN_LUT *gpio_info;
	ATOM_GPIO_PIN_ASSIGNMENT *pin;
	u16 data_offset, size;
	पूर्णांक i, num_indices;

	स_रखो(&gpio, 0, माप(काष्ठा radeon_gpio_rec));
	gpio.valid = false;

	अगर (atom_parse_data_header(ctx, index, &size, शून्य, शून्य, &data_offset)) अणु
		gpio_info = (काष्ठा _ATOM_GPIO_PIN_LUT *)(ctx->bios + data_offset);

		num_indices = (size - माप(ATOM_COMMON_TABLE_HEADER)) /
			माप(ATOM_GPIO_PIN_ASSIGNMENT);

		pin = gpio_info->asGPIO_Pin;
		क्रम (i = 0; i < num_indices; i++) अणु
			अगर (id == pin->ucGPIO_ID) अणु
				gpio.id = pin->ucGPIO_ID;
				gpio.reg = le16_to_cpu(pin->usGpioPin_AIndex) * 4;
				gpio.shअगरt = pin->ucGpioPinBitShअगरt;
				gpio.mask = (1 << pin->ucGpioPinBitShअगरt);
				gpio.valid = true;
				अवरोध;
			पूर्ण
			pin = (ATOM_GPIO_PIN_ASSIGNMENT *)
				((u8 *)pin + माप(ATOM_GPIO_PIN_ASSIGNMENT));
		पूर्ण
	पूर्ण

	वापस gpio;
पूर्ण

अटल काष्ठा radeon_hpd radeon_atom_get_hpd_info_from_gpio(काष्ठा radeon_device *rdev,
							    काष्ठा radeon_gpio_rec *gpio)
अणु
	काष्ठा radeon_hpd hpd;
	u32 reg;

	स_रखो(&hpd, 0, माप(काष्ठा radeon_hpd));

	अगर (ASIC_IS_DCE6(rdev))
		reg = SI_DC_GPIO_HPD_A;
	अन्यथा अगर (ASIC_IS_DCE4(rdev))
		reg = EVERGREEN_DC_GPIO_HPD_A;
	अन्यथा
		reg = AVIVO_DC_GPIO_HPD_A;

	hpd.gpio = *gpio;
	अगर (gpio->reg == reg) अणु
		चयन(gpio->mask) अणु
		हाल (1 << 0):
			hpd.hpd = RADEON_HPD_1;
			अवरोध;
		हाल (1 << 8):
			hpd.hpd = RADEON_HPD_2;
			अवरोध;
		हाल (1 << 16):
			hpd.hpd = RADEON_HPD_3;
			अवरोध;
		हाल (1 << 24):
			hpd.hpd = RADEON_HPD_4;
			अवरोध;
		हाल (1 << 26):
			hpd.hpd = RADEON_HPD_5;
			अवरोध;
		हाल (1 << 28):
			hpd.hpd = RADEON_HPD_6;
			अवरोध;
		शेष:
			hpd.hpd = RADEON_HPD_NONE;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		hpd.hpd = RADEON_HPD_NONE;
	वापस hpd;
पूर्ण

अटल bool radeon_atom_apply_quirks(काष्ठा drm_device *dev,
				     uपूर्णांक32_t supported_device,
				     पूर्णांक *connector_type,
				     काष्ठा radeon_i2c_bus_rec *i2c_bus,
				     uपूर्णांक16_t *line_mux,
				     काष्ठा radeon_hpd *hpd)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	/* Asus M2A-VM HDMI board lists the DVI port as HDMI */
	अगर ((pdev->device == 0x791e) &&
	    (pdev->subप्रणाली_venकरोr == 0x1043) &&
	    (pdev->subप्रणाली_device == 0x826d)) अणु
		अगर ((*connector_type == DRM_MODE_CONNECTOR_HDMIA) &&
		    (supported_device == ATOM_DEVICE_DFP3_SUPPORT))
			*connector_type = DRM_MODE_CONNECTOR_DVID;
	पूर्ण

	/* Asrock RS600 board lists the DVI port as HDMI */
	अगर ((pdev->device == 0x7941) &&
	    (pdev->subप्रणाली_venकरोr == 0x1849) &&
	    (pdev->subप्रणाली_device == 0x7941)) अणु
		अगर ((*connector_type == DRM_MODE_CONNECTOR_HDMIA) &&
		    (supported_device == ATOM_DEVICE_DFP3_SUPPORT))
			*connector_type = DRM_MODE_CONNECTOR_DVID;
	पूर्ण

	/* MSI K9A2GM V2/V3 board has no HDMI or DVI */
	अगर ((pdev->device == 0x796e) &&
	    (pdev->subप्रणाली_venकरोr == 0x1462) &&
	    (pdev->subप्रणाली_device == 0x7302)) अणु
		अगर ((supported_device == ATOM_DEVICE_DFP2_SUPPORT) ||
		    (supported_device == ATOM_DEVICE_DFP3_SUPPORT))
			वापस false;
	पूर्ण

	/* a-bit f-i90hd - ciaranm on #radeonhd - this board has no DVI */
	अगर ((pdev->device == 0x7941) &&
	    (pdev->subप्रणाली_venकरोr == 0x147b) &&
	    (pdev->subप्रणाली_device == 0x2412)) अणु
		अगर (*connector_type == DRM_MODE_CONNECTOR_DVII)
			वापस false;
	पूर्ण

	/* Falcon NW laptop lists vga ddc line क्रम LVDS */
	अगर ((pdev->device == 0x5653) &&
	    (pdev->subप्रणाली_venकरोr == 0x1462) &&
	    (pdev->subप्रणाली_device == 0x0291)) अणु
		अगर (*connector_type == DRM_MODE_CONNECTOR_LVDS) अणु
			i2c_bus->valid = false;
			*line_mux = 53;
		पूर्ण
	पूर्ण

	/* HIS X1300 is DVI+VGA, not DVI+DVI */
	अगर ((pdev->device == 0x7146) &&
	    (pdev->subप्रणाली_venकरोr == 0x17af) &&
	    (pdev->subप्रणाली_device == 0x2058)) अणु
		अगर (supported_device == ATOM_DEVICE_DFP1_SUPPORT)
			वापस false;
	पूर्ण

	/* Gigabyte X1300 is DVI+VGA, not DVI+DVI */
	अगर ((pdev->device == 0x7142) &&
	    (pdev->subप्रणाली_venकरोr == 0x1458) &&
	    (pdev->subप्रणाली_device == 0x2134)) अणु
		अगर (supported_device == ATOM_DEVICE_DFP1_SUPPORT)
			वापस false;
	पूर्ण


	/* Funky macbooks */
	अगर ((pdev->device == 0x71C5) &&
	    (pdev->subप्रणाली_venकरोr == 0x106b) &&
	    (pdev->subप्रणाली_device == 0x0080)) अणु
		अगर ((supported_device == ATOM_DEVICE_CRT1_SUPPORT) ||
		    (supported_device == ATOM_DEVICE_DFP2_SUPPORT))
			वापस false;
		अगर (supported_device == ATOM_DEVICE_CRT2_SUPPORT)
			*line_mux = 0x90;
	पूर्ण

	/* mac rv630, rv730, others */
	अगर ((supported_device == ATOM_DEVICE_TV1_SUPPORT) &&
	    (*connector_type == DRM_MODE_CONNECTOR_DVII)) अणु
		*connector_type = DRM_MODE_CONNECTOR_9PinDIN;
		*line_mux = CONNECTOR_7PIN_DIN_ENUM_ID1;
	पूर्ण

	/* ASUS HD 3600 XT board lists the DVI port as HDMI */
	अगर ((pdev->device == 0x9598) &&
	    (pdev->subप्रणाली_venकरोr == 0x1043) &&
	    (pdev->subप्रणाली_device == 0x01da)) अणु
		अगर (*connector_type == DRM_MODE_CONNECTOR_HDMIA) अणु
			*connector_type = DRM_MODE_CONNECTOR_DVII;
		पूर्ण
	पूर्ण

	/* ASUS HD 3600 board lists the DVI port as HDMI */
	अगर ((pdev->device == 0x9598) &&
	    (pdev->subप्रणाली_venकरोr == 0x1043) &&
	    (pdev->subप्रणाली_device == 0x01e4)) अणु
		अगर (*connector_type == DRM_MODE_CONNECTOR_HDMIA) अणु
			*connector_type = DRM_MODE_CONNECTOR_DVII;
		पूर्ण
	पूर्ण

	/* ASUS HD 3450 board lists the DVI port as HDMI */
	अगर ((pdev->device == 0x95C5) &&
	    (pdev->subप्रणाली_venकरोr == 0x1043) &&
	    (pdev->subप्रणाली_device == 0x01e2)) अणु
		अगर (*connector_type == DRM_MODE_CONNECTOR_HDMIA) अणु
			*connector_type = DRM_MODE_CONNECTOR_DVII;
		पूर्ण
	पूर्ण

	/* some BIOSes seem to report DAC on HDMI - usually this is a board with
	 * HDMI + VGA reporting as HDMI
	 */
	अगर (*connector_type == DRM_MODE_CONNECTOR_HDMIA) अणु
		अगर (supported_device & (ATOM_DEVICE_CRT_SUPPORT)) अणु
			*connector_type = DRM_MODE_CONNECTOR_VGA;
			*line_mux = 0;
		पूर्ण
	पूर्ण

	/* Acer laptop (Acer TravelMate 5730/5730G) has an HDMI port
	 * on the laptop and a DVI port on the करोcking station and
	 * both share the same encoder, hpd pin, and ddc line.
	 * So जबतक the bios table is technically correct,
	 * we drop the DVI port here since xअक्रमr has no concept of
	 * encoders and will try and drive both connectors
	 * with dअगरferent crtcs which isn't possible on the hardware
	 * side and leaves no crtcs क्रम LVDS or VGA.
	 */
	अगर (((pdev->device == 0x95c4) || (pdev->device == 0x9591)) &&
	    (pdev->subप्रणाली_venकरोr == 0x1025) &&
	    (pdev->subप्रणाली_device == 0x013c)) अणु
		अगर ((*connector_type == DRM_MODE_CONNECTOR_DVII) &&
		    (supported_device == ATOM_DEVICE_DFP1_SUPPORT)) अणु
			/* actually it's a DVI-D port not DVI-I */
			*connector_type = DRM_MODE_CONNECTOR_DVID;
			वापस false;
		पूर्ण
	पूर्ण

	/* XFX Pine Group device rv730 reports no VGA DDC lines
	 * even though they are wired up to record 0x93
	 */
	अगर ((pdev->device == 0x9498) &&
	    (pdev->subप्रणाली_venकरोr == 0x1682) &&
	    (pdev->subप्रणाली_device == 0x2452) &&
	    (i2c_bus->valid == false) &&
	    !(supported_device & (ATOM_DEVICE_TV_SUPPORT | ATOM_DEVICE_CV_SUPPORT))) अणु
		काष्ठा radeon_device *rdev = dev->dev_निजी;
		*i2c_bus = radeon_lookup_i2c_gpio(rdev, 0x93);
	पूर्ण

	/* Fujitsu D3003-S2 board lists DVI-I as DVI-D and VGA */
	अगर (((pdev->device == 0x9802) ||
	     (pdev->device == 0x9805) ||
	     (pdev->device == 0x9806)) &&
	    (pdev->subप्रणाली_venकरोr == 0x1734) &&
	    (pdev->subप्रणाली_device == 0x11bd)) अणु
		अगर (*connector_type == DRM_MODE_CONNECTOR_VGA) अणु
			*connector_type = DRM_MODE_CONNECTOR_DVII;
			*line_mux = 0x3103;
		पूर्ण अन्यथा अगर (*connector_type == DRM_MODE_CONNECTOR_DVID) अणु
			*connector_type = DRM_MODE_CONNECTOR_DVII;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल स्थिर पूर्णांक supported_devices_connector_convert[] = अणु
	DRM_MODE_CONNECTOR_Unknown,
	DRM_MODE_CONNECTOR_VGA,
	DRM_MODE_CONNECTOR_DVII,
	DRM_MODE_CONNECTOR_DVID,
	DRM_MODE_CONNECTOR_DVIA,
	DRM_MODE_CONNECTOR_SVIDEO,
	DRM_MODE_CONNECTOR_Composite,
	DRM_MODE_CONNECTOR_LVDS,
	DRM_MODE_CONNECTOR_Unknown,
	DRM_MODE_CONNECTOR_Unknown,
	DRM_MODE_CONNECTOR_HDMIA,
	DRM_MODE_CONNECTOR_HDMIB,
	DRM_MODE_CONNECTOR_Unknown,
	DRM_MODE_CONNECTOR_Unknown,
	DRM_MODE_CONNECTOR_9PinDIN,
	DRM_MODE_CONNECTOR_DisplayPort
पूर्ण;

अटल स्थिर uपूर्णांक16_t supported_devices_connector_object_id_convert[] = अणु
	CONNECTOR_OBJECT_ID_NONE,
	CONNECTOR_OBJECT_ID_VGA,
	CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_I, /* not all boards support DL */
	CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_D, /* not all boards support DL */
	CONNECTOR_OBJECT_ID_VGA, /* technically DVI-A */
	CONNECTOR_OBJECT_ID_COMPOSITE,
	CONNECTOR_OBJECT_ID_SVIDEO,
	CONNECTOR_OBJECT_ID_LVDS,
	CONNECTOR_OBJECT_ID_9PIN_DIN,
	CONNECTOR_OBJECT_ID_9PIN_DIN,
	CONNECTOR_OBJECT_ID_DISPLAYPORT,
	CONNECTOR_OBJECT_ID_HDMI_TYPE_A,
	CONNECTOR_OBJECT_ID_HDMI_TYPE_B,
	CONNECTOR_OBJECT_ID_SVIDEO
पूर्ण;

अटल स्थिर पूर्णांक object_connector_convert[] = अणु
	DRM_MODE_CONNECTOR_Unknown,
	DRM_MODE_CONNECTOR_DVII,
	DRM_MODE_CONNECTOR_DVII,
	DRM_MODE_CONNECTOR_DVID,
	DRM_MODE_CONNECTOR_DVID,
	DRM_MODE_CONNECTOR_VGA,
	DRM_MODE_CONNECTOR_Composite,
	DRM_MODE_CONNECTOR_SVIDEO,
	DRM_MODE_CONNECTOR_Unknown,
	DRM_MODE_CONNECTOR_Unknown,
	DRM_MODE_CONNECTOR_9PinDIN,
	DRM_MODE_CONNECTOR_Unknown,
	DRM_MODE_CONNECTOR_HDMIA,
	DRM_MODE_CONNECTOR_HDMIB,
	DRM_MODE_CONNECTOR_LVDS,
	DRM_MODE_CONNECTOR_9PinDIN,
	DRM_MODE_CONNECTOR_Unknown,
	DRM_MODE_CONNECTOR_Unknown,
	DRM_MODE_CONNECTOR_Unknown,
	DRM_MODE_CONNECTOR_DisplayPort,
	DRM_MODE_CONNECTOR_eDP,
	DRM_MODE_CONNECTOR_Unknown
पूर्ण;

bool radeon_get_atom_connector_info_from_object_table(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	काष्ठा atom_context *ctx = mode_info->atom_context;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, Object_Header);
	u16 size, data_offset;
	u8 frev, crev;
	ATOM_CONNECTOR_OBJECT_TABLE *con_obj;
	ATOM_ENCODER_OBJECT_TABLE *enc_obj;
	ATOM_OBJECT_TABLE *router_obj;
	ATOM_DISPLAY_OBJECT_PATH_TABLE *path_obj;
	ATOM_OBJECT_HEADER *obj_header;
	पूर्णांक i, j, k, path_size, device_support;
	पूर्णांक connector_type;
	u16 igp_lane_info, conn_id, connector_object_id;
	काष्ठा radeon_i2c_bus_rec ddc_bus;
	काष्ठा radeon_router router;
	काष्ठा radeon_gpio_rec gpio;
	काष्ठा radeon_hpd hpd;

	अगर (!atom_parse_data_header(ctx, index, &size, &frev, &crev, &data_offset))
		वापस false;

	अगर (crev < 2)
		वापस false;

	obj_header = (ATOM_OBJECT_HEADER *) (ctx->bios + data_offset);
	path_obj = (ATOM_DISPLAY_OBJECT_PATH_TABLE *)
	    (ctx->bios + data_offset +
	     le16_to_cpu(obj_header->usDisplayPathTableOffset));
	con_obj = (ATOM_CONNECTOR_OBJECT_TABLE *)
	    (ctx->bios + data_offset +
	     le16_to_cpu(obj_header->usConnectorObjectTableOffset));
	enc_obj = (ATOM_ENCODER_OBJECT_TABLE *)
	    (ctx->bios + data_offset +
	     le16_to_cpu(obj_header->usEncoderObjectTableOffset));
	router_obj = (ATOM_OBJECT_TABLE *)
		(ctx->bios + data_offset +
		 le16_to_cpu(obj_header->usRouterObjectTableOffset));
	device_support = le16_to_cpu(obj_header->usDeviceSupport);

	path_size = 0;
	क्रम (i = 0; i < path_obj->ucNumOfDispPath; i++) अणु
		uपूर्णांक8_t *addr = (uपूर्णांक8_t *) path_obj->asDispPath;
		ATOM_DISPLAY_OBJECT_PATH *path;
		addr += path_size;
		path = (ATOM_DISPLAY_OBJECT_PATH *) addr;
		path_size += le16_to_cpu(path->usSize);

		अगर (device_support & le16_to_cpu(path->usDeviceTag)) अणु
			uपूर्णांक8_t con_obj_id, con_obj_num;

			con_obj_id =
			    (le16_to_cpu(path->usConnObjectId) & OBJECT_ID_MASK)
			    >> OBJECT_ID_SHIFT;
			con_obj_num =
			    (le16_to_cpu(path->usConnObjectId) & ENUM_ID_MASK)
			    >> ENUM_ID_SHIFT;

			/* TODO CV support */
			अगर (le16_to_cpu(path->usDeviceTag) ==
				ATOM_DEVICE_CV_SUPPORT)
				जारी;

			/* IGP chips */
			अगर ((rdev->flags & RADEON_IS_IGP) &&
			    (con_obj_id ==
			     CONNECTOR_OBJECT_ID_PCIE_CONNECTOR)) अणु
				uपूर्णांक16_t igp_offset = 0;
				ATOM_INTEGRATED_SYSTEM_INFO_V2 *igp_obj;

				index =
				    GetIndexIntoMasterTable(DATA,
							    IntegratedSystemInfo);

				अगर (atom_parse_data_header(ctx, index, &size, &frev,
							   &crev, &igp_offset)) अणु

					अगर (crev >= 2) अणु
						igp_obj =
							(ATOM_INTEGRATED_SYSTEM_INFO_V2
							 *) (ctx->bios + igp_offset);

						अगर (igp_obj) अणु
							uपूर्णांक32_t slot_config, ct;

							अगर (con_obj_num == 1)
								slot_config =
									igp_obj->
									ulDDISlot1Config;
							अन्यथा
								slot_config =
									igp_obj->
									ulDDISlot2Config;

							ct = (slot_config >> 16) & 0xff;
							connector_type =
								object_connector_convert
								[ct];
							connector_object_id = ct;
							igp_lane_info =
								slot_config & 0xffff;
						पूर्ण अन्यथा
							जारी;
					पूर्ण अन्यथा
						जारी;
				पूर्ण अन्यथा अणु
					igp_lane_info = 0;
					connector_type =
						object_connector_convert[con_obj_id];
					connector_object_id = con_obj_id;
				पूर्ण
			पूर्ण अन्यथा अणु
				igp_lane_info = 0;
				connector_type =
				    object_connector_convert[con_obj_id];
				connector_object_id = con_obj_id;
			पूर्ण

			अगर (connector_type == DRM_MODE_CONNECTOR_Unknown)
				जारी;

			router.ddc_valid = false;
			router.cd_valid = false;
			क्रम (j = 0; j < ((le16_to_cpu(path->usSize) - 8) / 2); j++) अणु
				uपूर्णांक8_t grph_obj_type =
				    (le16_to_cpu(path->usGraphicObjIds[j]) &
				     OBJECT_TYPE_MASK) >> OBJECT_TYPE_SHIFT;

				अगर (grph_obj_type == GRAPH_OBJECT_TYPE_ENCODER) अणु
					क्रम (k = 0; k < enc_obj->ucNumberOfObjects; k++) अणु
						u16 encoder_obj = le16_to_cpu(enc_obj->asObjects[k].usObjectID);
						अगर (le16_to_cpu(path->usGraphicObjIds[j]) == encoder_obj) अणु
							ATOM_COMMON_RECORD_HEADER *record = (ATOM_COMMON_RECORD_HEADER *)
								(ctx->bios + data_offset +
								 le16_to_cpu(enc_obj->asObjects[k].usRecordOffset));
							ATOM_ENCODER_CAP_RECORD *cap_record;
							u16 caps = 0;

							जबतक (record->ucRecordSize > 0 &&
							       record->ucRecordType > 0 &&
							       record->ucRecordType <= ATOM_MAX_OBJECT_RECORD_NUMBER) अणु
								चयन (record->ucRecordType) अणु
								हाल ATOM_ENCODER_CAP_RECORD_TYPE:
									cap_record =(ATOM_ENCODER_CAP_RECORD *)
										record;
									caps = le16_to_cpu(cap_record->usEncoderCap);
									अवरोध;
								पूर्ण
								record = (ATOM_COMMON_RECORD_HEADER *)
									((अक्षर *)record + record->ucRecordSize);
							पूर्ण
							radeon_add_atom_encoder(dev,
										encoder_obj,
										le16_to_cpu
										(path->
										 usDeviceTag),
										caps);
						पूर्ण
					पूर्ण
				पूर्ण अन्यथा अगर (grph_obj_type == GRAPH_OBJECT_TYPE_ROUTER) अणु
					क्रम (k = 0; k < router_obj->ucNumberOfObjects; k++) अणु
						u16 router_obj_id = le16_to_cpu(router_obj->asObjects[k].usObjectID);
						अगर (le16_to_cpu(path->usGraphicObjIds[j]) == router_obj_id) अणु
							ATOM_COMMON_RECORD_HEADER *record = (ATOM_COMMON_RECORD_HEADER *)
								(ctx->bios + data_offset +
								 le16_to_cpu(router_obj->asObjects[k].usRecordOffset));
							ATOM_I2C_RECORD *i2c_record;
							ATOM_I2C_ID_CONFIG_ACCESS *i2c_config;
							ATOM_ROUTER_DDC_PATH_SELECT_RECORD *ddc_path;
							ATOM_ROUTER_DATA_CLOCK_PATH_SELECT_RECORD *cd_path;
							ATOM_SRC_DST_TABLE_FOR_ONE_OBJECT *router_src_dst_table =
								(ATOM_SRC_DST_TABLE_FOR_ONE_OBJECT *)
								(ctx->bios + data_offset +
								 le16_to_cpu(router_obj->asObjects[k].usSrcDstTableOffset));
							u8 *num_dst_objs = (u8 *)
								((u8 *)router_src_dst_table + 1 +
								 (router_src_dst_table->ucNumberOfSrc * 2));
							u16 *dst_objs = (u16 *)(num_dst_objs + 1);
							पूर्णांक क्रमागत_id;

							router.router_id = router_obj_id;
							क्रम (क्रमागत_id = 0; क्रमागत_id < (*num_dst_objs); क्रमागत_id++) अणु
								अगर (le16_to_cpu(path->usConnObjectId) ==
								    le16_to_cpu(dst_objs[क्रमागत_id]))
									अवरोध;
							पूर्ण

							जबतक (record->ucRecordSize > 0 &&
							       record->ucRecordType > 0 &&
							       record->ucRecordType <= ATOM_MAX_OBJECT_RECORD_NUMBER) अणु
								चयन (record->ucRecordType) अणु
								हाल ATOM_I2C_RECORD_TYPE:
									i2c_record =
										(ATOM_I2C_RECORD *)
										record;
									i2c_config =
										(ATOM_I2C_ID_CONFIG_ACCESS *)
										&i2c_record->sucI2cId;
									router.i2c_info =
										radeon_lookup_i2c_gpio(rdev,
												       i2c_config->
												       ucAccess);
									router.i2c_addr = i2c_record->ucI2CAddr >> 1;
									अवरोध;
								हाल ATOM_ROUTER_DDC_PATH_SELECT_RECORD_TYPE:
									ddc_path = (ATOM_ROUTER_DDC_PATH_SELECT_RECORD *)
										record;
									router.ddc_valid = true;
									router.ddc_mux_type = ddc_path->ucMuxType;
									router.ddc_mux_control_pin = ddc_path->ucMuxControlPin;
									router.ddc_mux_state = ddc_path->ucMuxState[क्रमागत_id];
									अवरोध;
								हाल ATOM_ROUTER_DATA_CLOCK_PATH_SELECT_RECORD_TYPE:
									cd_path = (ATOM_ROUTER_DATA_CLOCK_PATH_SELECT_RECORD *)
										record;
									router.cd_valid = true;
									router.cd_mux_type = cd_path->ucMuxType;
									router.cd_mux_control_pin = cd_path->ucMuxControlPin;
									router.cd_mux_state = cd_path->ucMuxState[क्रमागत_id];
									अवरोध;
								पूर्ण
								record = (ATOM_COMMON_RECORD_HEADER *)
									((अक्षर *)record + record->ucRecordSize);
							पूर्ण
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण

			/* look up gpio क्रम ddc, hpd */
			ddc_bus.valid = false;
			hpd.hpd = RADEON_HPD_NONE;
			अगर ((le16_to_cpu(path->usDeviceTag) &
			     (ATOM_DEVICE_TV_SUPPORT | ATOM_DEVICE_CV_SUPPORT)) == 0) अणु
				क्रम (j = 0; j < con_obj->ucNumberOfObjects; j++) अणु
					अगर (le16_to_cpu(path->usConnObjectId) ==
					    le16_to_cpu(con_obj->asObjects[j].
							usObjectID)) अणु
						ATOM_COMMON_RECORD_HEADER
						    *record =
						    (ATOM_COMMON_RECORD_HEADER
						     *)
						    (ctx->bios + data_offset +
						     le16_to_cpu(con_obj->
								 asObjects[j].
								 usRecordOffset));
						ATOM_I2C_RECORD *i2c_record;
						ATOM_HPD_INT_RECORD *hpd_record;
						ATOM_I2C_ID_CONFIG_ACCESS *i2c_config;

						जबतक (record->ucRecordSize > 0 &&
						       record->ucRecordType > 0 &&
						       record->ucRecordType <= ATOM_MAX_OBJECT_RECORD_NUMBER) अणु
							चयन (record->ucRecordType) अणु
							हाल ATOM_I2C_RECORD_TYPE:
								i2c_record =
								    (ATOM_I2C_RECORD *)
									record;
								i2c_config =
									(ATOM_I2C_ID_CONFIG_ACCESS *)
									&i2c_record->sucI2cId;
								ddc_bus = radeon_lookup_i2c_gpio(rdev,
												 i2c_config->
												 ucAccess);
								अवरोध;
							हाल ATOM_HPD_INT_RECORD_TYPE:
								hpd_record =
									(ATOM_HPD_INT_RECORD *)
									record;
								gpio = radeon_atombios_lookup_gpio(rdev,
											  hpd_record->ucHPDIntGPIOID);
								hpd = radeon_atom_get_hpd_info_from_gpio(rdev, &gpio);
								hpd.plugged_state = hpd_record->ucPlugged_PinState;
								अवरोध;
							पूर्ण
							record =
							    (ATOM_COMMON_RECORD_HEADER
							     *) ((अक्षर *)record
								 +
								 record->
								 ucRecordSize);
						पूर्ण
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण

			/* needed क्रम aux chan transactions */
			ddc_bus.hpd = hpd.hpd;

			conn_id = le16_to_cpu(path->usConnObjectId);

			अगर (!radeon_atom_apply_quirks
			    (dev, le16_to_cpu(path->usDeviceTag), &connector_type,
			     &ddc_bus, &conn_id, &hpd))
				जारी;

			radeon_add_atom_connector(dev,
						  conn_id,
						  le16_to_cpu(path->
							      usDeviceTag),
						  connector_type, &ddc_bus,
						  igp_lane_info,
						  connector_object_id,
						  &hpd,
						  &router);

		पूर्ण
	पूर्ण

	radeon_link_encoder_connector(dev);

	radeon_setup_mst_connector(dev);
	वापस true;
पूर्ण

अटल uपूर्णांक16_t atombios_get_connector_object_id(काष्ठा drm_device *dev,
						 पूर्णांक connector_type,
						 uपूर्णांक16_t devices)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	अगर (rdev->flags & RADEON_IS_IGP) अणु
		वापस supported_devices_connector_object_id_convert
			[connector_type];
	पूर्ण अन्यथा अगर (((connector_type == DRM_MODE_CONNECTOR_DVII) ||
		    (connector_type == DRM_MODE_CONNECTOR_DVID)) &&
		   (devices & ATOM_DEVICE_DFP2_SUPPORT))  अणु
		काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
		काष्ठा atom_context *ctx = mode_info->atom_context;
		पूर्णांक index = GetIndexIntoMasterTable(DATA, XTMDS_Info);
		uपूर्णांक16_t size, data_offset;
		uपूर्णांक8_t frev, crev;
		ATOM_XTMDS_INFO *xपंचांगds;

		अगर (atom_parse_data_header(ctx, index, &size, &frev, &crev, &data_offset)) अणु
			xपंचांगds = (ATOM_XTMDS_INFO *)(ctx->bios + data_offset);

			अगर (xपंचांगds->ucSupportedLink & ATOM_XTMDS_SUPPORTED_DUALLINK) अणु
				अगर (connector_type == DRM_MODE_CONNECTOR_DVII)
					वापस CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_I;
				अन्यथा
					वापस CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_D;
			पूर्ण अन्यथा अणु
				अगर (connector_type == DRM_MODE_CONNECTOR_DVII)
					वापस CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I;
				अन्यथा
					वापस CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_D;
			पूर्ण
		पूर्ण अन्यथा
			वापस supported_devices_connector_object_id_convert
				[connector_type];
	पूर्ण अन्यथा अणु
		वापस supported_devices_connector_object_id_convert
			[connector_type];
	पूर्ण
पूर्ण

काष्ठा bios_connector अणु
	bool valid;
	uपूर्णांक16_t line_mux;
	uपूर्णांक16_t devices;
	पूर्णांक connector_type;
	काष्ठा radeon_i2c_bus_rec ddc_bus;
	काष्ठा radeon_hpd hpd;
पूर्ण;

bool radeon_get_atom_connector_info_from_supported_devices_table(काष्ठा
								 drm_device
								 *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	काष्ठा atom_context *ctx = mode_info->atom_context;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, SupportedDevicesInfo);
	uपूर्णांक16_t size, data_offset;
	uपूर्णांक8_t frev, crev;
	uपूर्णांक16_t device_support;
	uपूर्णांक8_t dac;
	जोड़ atom_supported_devices *supported_devices;
	पूर्णांक i, j, max_device;
	काष्ठा bios_connector *bios_connectors;
	माप_प्रकार bc_size = माप(*bios_connectors) * ATOM_MAX_SUPPORTED_DEVICE;
	काष्ठा radeon_router router;

	router.ddc_valid = false;
	router.cd_valid = false;

	bios_connectors = kzalloc(bc_size, GFP_KERNEL);
	अगर (!bios_connectors)
		वापस false;

	अगर (!atom_parse_data_header(ctx, index, &size, &frev, &crev,
				    &data_offset)) अणु
		kमुक्त(bios_connectors);
		वापस false;
	पूर्ण

	supported_devices =
	    (जोड़ atom_supported_devices *)(ctx->bios + data_offset);

	device_support = le16_to_cpu(supported_devices->info.usDeviceSupport);

	अगर (frev > 1)
		max_device = ATOM_MAX_SUPPORTED_DEVICE;
	अन्यथा
		max_device = ATOM_MAX_SUPPORTED_DEVICE_INFO;

	क्रम (i = 0; i < max_device; i++) अणु
		ATOM_CONNECTOR_INFO_I2C ci =
		    supported_devices->info.asConnInfo[i];

		bios_connectors[i].valid = false;

		अगर (!(device_support & (1 << i))) अणु
			जारी;
		पूर्ण

		अगर (i == ATOM_DEVICE_CV_INDEX) अणु
			DRM_DEBUG_KMS("Skipping Component Video\n");
			जारी;
		पूर्ण

		bios_connectors[i].connector_type =
		    supported_devices_connector_convert[ci.sucConnectorInfo.
							sbfAccess.
							bfConnectorType];

		अगर (bios_connectors[i].connector_type ==
		    DRM_MODE_CONNECTOR_Unknown)
			जारी;

		dac = ci.sucConnectorInfo.sbfAccess.bfAssociatedDAC;

		bios_connectors[i].line_mux =
			ci.sucI2cId.ucAccess;

		/* give tv unique connector ids */
		अगर (i == ATOM_DEVICE_TV1_INDEX) अणु
			bios_connectors[i].ddc_bus.valid = false;
			bios_connectors[i].line_mux = 50;
		पूर्ण अन्यथा अगर (i == ATOM_DEVICE_TV2_INDEX) अणु
			bios_connectors[i].ddc_bus.valid = false;
			bios_connectors[i].line_mux = 51;
		पूर्ण अन्यथा अगर (i == ATOM_DEVICE_CV_INDEX) अणु
			bios_connectors[i].ddc_bus.valid = false;
			bios_connectors[i].line_mux = 52;
		पूर्ण अन्यथा
			bios_connectors[i].ddc_bus =
			    radeon_lookup_i2c_gpio(rdev,
						   bios_connectors[i].line_mux);

		अगर ((crev > 1) && (frev > 1)) अणु
			u8 isb = supported_devices->info_2d1.asIntSrcInfo[i].ucIntSrcBiपंचांगap;
			चयन (isb) अणु
			हाल 0x4:
				bios_connectors[i].hpd.hpd = RADEON_HPD_1;
				अवरोध;
			हाल 0xa:
				bios_connectors[i].hpd.hpd = RADEON_HPD_2;
				अवरोध;
			शेष:
				bios_connectors[i].hpd.hpd = RADEON_HPD_NONE;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (i == ATOM_DEVICE_DFP1_INDEX)
				bios_connectors[i].hpd.hpd = RADEON_HPD_1;
			अन्यथा अगर (i == ATOM_DEVICE_DFP2_INDEX)
				bios_connectors[i].hpd.hpd = RADEON_HPD_2;
			अन्यथा
				bios_connectors[i].hpd.hpd = RADEON_HPD_NONE;
		पूर्ण

		/* Always set the connector type to VGA क्रम CRT1/CRT2. अगर they are
		 * shared with a DVI port, we'll pick up the DVI connector when we
		 * merge the outमाला_दो.  Some bioses incorrectly list VGA ports as DVI.
		 */
		अगर (i == ATOM_DEVICE_CRT1_INDEX || i == ATOM_DEVICE_CRT2_INDEX)
			bios_connectors[i].connector_type =
			    DRM_MODE_CONNECTOR_VGA;

		अगर (!radeon_atom_apply_quirks
		    (dev, (1 << i), &bios_connectors[i].connector_type,
		     &bios_connectors[i].ddc_bus, &bios_connectors[i].line_mux,
		     &bios_connectors[i].hpd))
			जारी;

		bios_connectors[i].valid = true;
		bios_connectors[i].devices = (1 << i);

		अगर (ASIC_IS_AVIVO(rdev) || radeon_r4xx_atom)
			radeon_add_atom_encoder(dev,
						radeon_get_encoder_क्रमागत(dev,
								      (1 << i),
								      dac),
						(1 << i),
						0);
		अन्यथा
			radeon_add_legacy_encoder(dev,
						  radeon_get_encoder_क्रमागत(dev,
									(1 << i),
									dac),
						  (1 << i));
	पूर्ण

	/* combine shared connectors */
	क्रम (i = 0; i < max_device; i++) अणु
		अगर (bios_connectors[i].valid) अणु
			क्रम (j = 0; j < max_device; j++) अणु
				अगर (bios_connectors[j].valid && (i != j)) अणु
					अगर (bios_connectors[i].line_mux ==
					    bios_connectors[j].line_mux) अणु
						/* make sure not to combine LVDS */
						अगर (bios_connectors[i].devices & (ATOM_DEVICE_LCD_SUPPORT)) अणु
							bios_connectors[i].line_mux = 53;
							bios_connectors[i].ddc_bus.valid = false;
							जारी;
						पूर्ण
						अगर (bios_connectors[j].devices & (ATOM_DEVICE_LCD_SUPPORT)) अणु
							bios_connectors[j].line_mux = 53;
							bios_connectors[j].ddc_bus.valid = false;
							जारी;
						पूर्ण
						/* combine analog and digital क्रम DVI-I */
						अगर (((bios_connectors[i].devices & (ATOM_DEVICE_DFP_SUPPORT)) &&
						     (bios_connectors[j].devices & (ATOM_DEVICE_CRT_SUPPORT))) ||
						    ((bios_connectors[j].devices & (ATOM_DEVICE_DFP_SUPPORT)) &&
						     (bios_connectors[i].devices & (ATOM_DEVICE_CRT_SUPPORT)))) अणु
							bios_connectors[i].devices |=
								bios_connectors[j].devices;
							bios_connectors[i].connector_type =
								DRM_MODE_CONNECTOR_DVII;
							अगर (bios_connectors[j].devices & (ATOM_DEVICE_DFP_SUPPORT))
								bios_connectors[i].hpd =
									bios_connectors[j].hpd;
							bios_connectors[j].valid = false;
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* add the connectors */
	क्रम (i = 0; i < max_device; i++) अणु
		अगर (bios_connectors[i].valid) अणु
			uपूर्णांक16_t connector_object_id =
				atombios_get_connector_object_id(dev,
						      bios_connectors[i].connector_type,
						      bios_connectors[i].devices);
			radeon_add_atom_connector(dev,
						  bios_connectors[i].line_mux,
						  bios_connectors[i].devices,
						  bios_connectors[i].
						  connector_type,
						  &bios_connectors[i].ddc_bus,
						  0,
						  connector_object_id,
						  &bios_connectors[i].hpd,
						  &router);
		पूर्ण
	पूर्ण

	radeon_link_encoder_connector(dev);

	kमुक्त(bios_connectors);
	वापस true;
पूर्ण

जोड़ firmware_info अणु
	ATOM_FIRMWARE_INFO info;
	ATOM_FIRMWARE_INFO_V1_2 info_12;
	ATOM_FIRMWARE_INFO_V1_3 info_13;
	ATOM_FIRMWARE_INFO_V1_4 info_14;
	ATOM_FIRMWARE_INFO_V2_1 info_21;
	ATOM_FIRMWARE_INFO_V2_2 info_22;
पूर्ण;

जोड़ igp_info अणु
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO info;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V2 info_2;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V6 info_6;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V1_7 info_7;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V1_8 info_8;
पूर्ण;

अटल व्योम radeon_atombios_get_dentist_vco_freq(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, IntegratedSystemInfo);
	जोड़ igp_info *igp_info;
	u8 frev, crev;
	u16 data_offset;

	अगर (atom_parse_data_header(mode_info->atom_context, index, शून्य,
			&frev, &crev, &data_offset)) अणु
		igp_info = (जोड़ igp_info *)(mode_info->atom_context->bios +
			data_offset);
		rdev->घड़ी.vco_freq =
			le32_to_cpu(igp_info->info_6.ulDentistVCOFreq);
	पूर्ण
पूर्ण

bool radeon_atom_get_घड़ी_info(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, FirmwareInfo);
	जोड़ firmware_info *firmware_info;
	uपूर्णांक8_t frev, crev;
	काष्ठा radeon_pll *p1pll = &rdev->घड़ी.p1pll;
	काष्ठा radeon_pll *p2pll = &rdev->घड़ी.p2pll;
	काष्ठा radeon_pll *dcpll = &rdev->घड़ी.dcpll;
	काष्ठा radeon_pll *spll = &rdev->घड़ी.spll;
	काष्ठा radeon_pll *mpll = &rdev->घड़ी.mpll;
	uपूर्णांक16_t data_offset;

	अगर (atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset)) अणु
		firmware_info =
			(जोड़ firmware_info *)(mode_info->atom_context->bios +
						data_offset);
		/* pixel घड़ीs */
		p1pll->reference_freq =
		    le16_to_cpu(firmware_info->info.usReferenceClock);
		p1pll->reference_भाग = 0;

		अगर ((frev < 2) && (crev < 2))
			p1pll->pll_out_min =
				le16_to_cpu(firmware_info->info.usMinPixelClockPLL_Output);
		अन्यथा
			p1pll->pll_out_min =
				le32_to_cpu(firmware_info->info_12.ulMinPixelClockPLL_Output);
		p1pll->pll_out_max =
		    le32_to_cpu(firmware_info->info.ulMaxPixelClockPLL_Output);

		अगर (((frev < 2) && (crev >= 4)) || (frev >= 2)) अणु
			p1pll->lcd_pll_out_min =
				le16_to_cpu(firmware_info->info_14.usLcdMinPixelClockPLL_Output) * 100;
			अगर (p1pll->lcd_pll_out_min == 0)
				p1pll->lcd_pll_out_min = p1pll->pll_out_min;
			p1pll->lcd_pll_out_max =
				le16_to_cpu(firmware_info->info_14.usLcdMaxPixelClockPLL_Output) * 100;
			अगर (p1pll->lcd_pll_out_max == 0)
				p1pll->lcd_pll_out_max = p1pll->pll_out_max;
		पूर्ण अन्यथा अणु
			p1pll->lcd_pll_out_min = p1pll->pll_out_min;
			p1pll->lcd_pll_out_max = p1pll->pll_out_max;
		पूर्ण

		अगर (p1pll->pll_out_min == 0) अणु
			अगर (ASIC_IS_AVIVO(rdev))
				p1pll->pll_out_min = 64800;
			अन्यथा
				p1pll->pll_out_min = 20000;
		पूर्ण

		p1pll->pll_in_min =
		    le16_to_cpu(firmware_info->info.usMinPixelClockPLL_Input);
		p1pll->pll_in_max =
		    le16_to_cpu(firmware_info->info.usMaxPixelClockPLL_Input);

		*p2pll = *p1pll;

		/* प्रणाली घड़ी */
		अगर (ASIC_IS_DCE4(rdev))
			spll->reference_freq =
				le16_to_cpu(firmware_info->info_21.usCoreReferenceClock);
		अन्यथा
			spll->reference_freq =
				le16_to_cpu(firmware_info->info.usReferenceClock);
		spll->reference_भाग = 0;

		spll->pll_out_min =
		    le16_to_cpu(firmware_info->info.usMinEngineClockPLL_Output);
		spll->pll_out_max =
		    le32_to_cpu(firmware_info->info.ulMaxEngineClockPLL_Output);

		/* ??? */
		अगर (spll->pll_out_min == 0) अणु
			अगर (ASIC_IS_AVIVO(rdev))
				spll->pll_out_min = 64800;
			अन्यथा
				spll->pll_out_min = 20000;
		पूर्ण

		spll->pll_in_min =
		    le16_to_cpu(firmware_info->info.usMinEngineClockPLL_Input);
		spll->pll_in_max =
		    le16_to_cpu(firmware_info->info.usMaxEngineClockPLL_Input);

		/* memory घड़ी */
		अगर (ASIC_IS_DCE4(rdev))
			mpll->reference_freq =
				le16_to_cpu(firmware_info->info_21.usMemoryReferenceClock);
		अन्यथा
			mpll->reference_freq =
				le16_to_cpu(firmware_info->info.usReferenceClock);
		mpll->reference_भाग = 0;

		mpll->pll_out_min =
		    le16_to_cpu(firmware_info->info.usMinMemoryClockPLL_Output);
		mpll->pll_out_max =
		    le32_to_cpu(firmware_info->info.ulMaxMemoryClockPLL_Output);

		/* ??? */
		अगर (mpll->pll_out_min == 0) अणु
			अगर (ASIC_IS_AVIVO(rdev))
				mpll->pll_out_min = 64800;
			अन्यथा
				mpll->pll_out_min = 20000;
		पूर्ण

		mpll->pll_in_min =
		    le16_to_cpu(firmware_info->info.usMinMemoryClockPLL_Input);
		mpll->pll_in_max =
		    le16_to_cpu(firmware_info->info.usMaxMemoryClockPLL_Input);

		rdev->घड़ी.शेष_sclk =
		    le32_to_cpu(firmware_info->info.ulDefaultEngineClock);
		rdev->घड़ी.शेष_mclk =
		    le32_to_cpu(firmware_info->info.ulDefaultMemoryClock);

		अगर (ASIC_IS_DCE4(rdev)) अणु
			rdev->घड़ी.शेष_dispclk =
				le32_to_cpu(firmware_info->info_21.ulDefaultDispEngineClkFreq);
			अगर (rdev->घड़ी.शेष_dispclk == 0) अणु
				अगर (ASIC_IS_DCE6(rdev))
					rdev->घड़ी.शेष_dispclk = 60000; /* 600 Mhz */
				अन्यथा अगर (ASIC_IS_DCE5(rdev))
					rdev->घड़ी.शेष_dispclk = 54000; /* 540 Mhz */
				अन्यथा
					rdev->घड़ी.शेष_dispclk = 60000; /* 600 Mhz */
			पूर्ण
			/* set a reasonable शेष क्रम DP */
			अगर (ASIC_IS_DCE6(rdev) && (rdev->घड़ी.शेष_dispclk < 53900)) अणु
				DRM_INFO("Changing default dispclk from %dMhz to 600Mhz\n",
					 rdev->घड़ी.शेष_dispclk / 100);
				rdev->घड़ी.शेष_dispclk = 60000;
			पूर्ण
			rdev->घड़ी.dp_extclk =
				le16_to_cpu(firmware_info->info_21.usUniphyDPModeExtClkFreq);
			rdev->घड़ी.current_dispclk = rdev->घड़ी.शेष_dispclk;
		पूर्ण
		*dcpll = *p1pll;

		rdev->घड़ी.max_pixel_घड़ी = le16_to_cpu(firmware_info->info.usMaxPixelClock);
		अगर (rdev->घड़ी.max_pixel_घड़ी == 0)
			rdev->घड़ी.max_pixel_घड़ी = 40000;

		/* not technically a घड़ी, but... */
		rdev->mode_info.firmware_flags =
			le16_to_cpu(firmware_info->info.usFirmwareCapability.susAccess);

		अगर (ASIC_IS_DCE8(rdev))
			rdev->घड़ी.vco_freq =
				le32_to_cpu(firmware_info->info_22.ulGPUPLL_OutputFreq);
		अन्यथा अगर (ASIC_IS_DCE5(rdev))
			rdev->घड़ी.vco_freq = rdev->घड़ी.current_dispclk;
		अन्यथा अगर (ASIC_IS_DCE41(rdev))
			radeon_atombios_get_dentist_vco_freq(rdev);
		अन्यथा
			rdev->घड़ी.vco_freq = rdev->घड़ी.current_dispclk;

		अगर (rdev->घड़ी.vco_freq == 0)
			rdev->घड़ी.vco_freq = 360000;	/* 3.6 GHz */

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

bool radeon_atombios_sideport_present(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, IntegratedSystemInfo);
	जोड़ igp_info *igp_info;
	u8 frev, crev;
	u16 data_offset;

	/* sideport is AMD only */
	अगर (rdev->family == CHIP_RS600)
		वापस false;

	अगर (atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset)) अणु
		igp_info = (जोड़ igp_info *)(mode_info->atom_context->bios +
				      data_offset);
		चयन (crev) अणु
		हाल 1:
			अगर (le32_to_cpu(igp_info->info.ulBootUpMemoryClock))
				वापस true;
			अवरोध;
		हाल 2:
			अगर (le32_to_cpu(igp_info->info_2.ulBootUpSidePortClock))
				वापस true;
			अवरोध;
		शेष:
			DRM_ERROR("Unsupported IGP table: %d %d\n", frev, crev);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

bool radeon_atombios_get_पंचांगds_info(काष्ठा radeon_encoder *encoder,
				   काष्ठा radeon_encoder_पूर्णांक_पंचांगds *पंचांगds)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, TMDS_Info);
	uपूर्णांक16_t data_offset;
	काष्ठा _ATOM_TMDS_INFO *पंचांगds_info;
	uपूर्णांक8_t frev, crev;
	uपूर्णांक16_t maxfreq;
	पूर्णांक i;

	अगर (atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset)) अणु
		पंचांगds_info =
			(काष्ठा _ATOM_TMDS_INFO *)(mode_info->atom_context->bios +
						   data_offset);

		maxfreq = le16_to_cpu(पंचांगds_info->usMaxFrequency);
		क्रम (i = 0; i < 4; i++) अणु
			पंचांगds->पंचांगds_pll[i].freq =
			    le16_to_cpu(पंचांगds_info->asMiscInfo[i].usFrequency);
			पंचांगds->पंचांगds_pll[i].value =
			    पंचांगds_info->asMiscInfo[i].ucPLL_ChargePump & 0x3f;
			पंचांगds->पंचांगds_pll[i].value |=
			    (पंचांगds_info->asMiscInfo[i].
			     ucPLL_VCO_Gain & 0x3f) << 6;
			पंचांगds->पंचांगds_pll[i].value |=
			    (पंचांगds_info->asMiscInfo[i].
			     ucPLL_DutyCycle & 0xf) << 12;
			पंचांगds->पंचांगds_pll[i].value |=
			    (पंचांगds_info->asMiscInfo[i].
			     ucPLL_VoltageSwing & 0xf) << 16;

			DRM_DEBUG_KMS("TMDS PLL From ATOMBIOS %u %x\n",
				  पंचांगds->पंचांगds_pll[i].freq,
				  पंचांगds->पंचांगds_pll[i].value);

			अगर (maxfreq == पंचांगds->पंचांगds_pll[i].freq) अणु
				पंचांगds->पंचांगds_pll[i].freq = 0xffffffff;
				अवरोध;
			पूर्ण
		पूर्ण
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

bool radeon_atombios_get_ppll_ss_info(काष्ठा radeon_device *rdev,
				      काष्ठा radeon_atom_ss *ss,
				      पूर्णांक id)
अणु
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, PPLL_SS_Info);
	uपूर्णांक16_t data_offset, size;
	काष्ठा _ATOM_SPREAD_SPECTRUM_INFO *ss_info;
	काष्ठा _ATOM_SPREAD_SPECTRUM_ASSIGNMENT *ss_assign;
	uपूर्णांक8_t frev, crev;
	पूर्णांक i, num_indices;

	स_रखो(ss, 0, माप(काष्ठा radeon_atom_ss));
	अगर (atom_parse_data_header(mode_info->atom_context, index, &size,
				   &frev, &crev, &data_offset)) अणु
		ss_info =
			(काष्ठा _ATOM_SPREAD_SPECTRUM_INFO *)(mode_info->atom_context->bios + data_offset);

		num_indices = (size - माप(ATOM_COMMON_TABLE_HEADER)) /
			माप(ATOM_SPREAD_SPECTRUM_ASSIGNMENT);
		ss_assign = (काष्ठा _ATOM_SPREAD_SPECTRUM_ASSIGNMENT*)
			((u8 *)&ss_info->asSS_Info[0]);
		क्रम (i = 0; i < num_indices; i++) अणु
			अगर (ss_assign->ucSS_Id == id) अणु
				ss->percentage =
					le16_to_cpu(ss_assign->usSpपढ़ोSpectrumPercentage);
				ss->type = ss_assign->ucSpपढ़ोSpectrumType;
				ss->step = ss_assign->ucSS_Step;
				ss->delay = ss_assign->ucSS_Delay;
				ss->range = ss_assign->ucSS_Range;
				ss->refभाग = ss_assign->ucRecommendedRef_Div;
				वापस true;
			पूर्ण
			ss_assign = (काष्ठा _ATOM_SPREAD_SPECTRUM_ASSIGNMENT*)
				((u8 *)ss_assign + माप(काष्ठा _ATOM_SPREAD_SPECTRUM_ASSIGNMENT));
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम radeon_atombios_get_igp_ss_overrides(काष्ठा radeon_device *rdev,
						 काष्ठा radeon_atom_ss *ss,
						 पूर्णांक id)
अणु
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, IntegratedSystemInfo);
	u16 data_offset, size;
	जोड़ igp_info *igp_info;
	u8 frev, crev;
	u16 percentage = 0, rate = 0;

	/* get any igp specअगरic overrides */
	अगर (atom_parse_data_header(mode_info->atom_context, index, &size,
				   &frev, &crev, &data_offset)) अणु
		igp_info = (जोड़ igp_info *)
			(mode_info->atom_context->bios + data_offset);
		चयन (crev) अणु
		हाल 6:
			चयन (id) अणु
			हाल ASIC_INTERNAL_SS_ON_TMDS:
				percentage = le16_to_cpu(igp_info->info_6.usDVISSPercentage);
				rate = le16_to_cpu(igp_info->info_6.usDVISSpपढ़ोRateIn10Hz);
				अवरोध;
			हाल ASIC_INTERNAL_SS_ON_HDMI:
				percentage = le16_to_cpu(igp_info->info_6.usHDMISSPercentage);
				rate = le16_to_cpu(igp_info->info_6.usHDMISSpपढ़ोRateIn10Hz);
				अवरोध;
			हाल ASIC_INTERNAL_SS_ON_LVDS:
				percentage = le16_to_cpu(igp_info->info_6.usLvdsSSPercentage);
				rate = le16_to_cpu(igp_info->info_6.usLvdsSSpपढ़ोRateIn10Hz);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 7:
			चयन (id) अणु
			हाल ASIC_INTERNAL_SS_ON_TMDS:
				percentage = le16_to_cpu(igp_info->info_7.usDVISSPercentage);
				rate = le16_to_cpu(igp_info->info_7.usDVISSpपढ़ोRateIn10Hz);
				अवरोध;
			हाल ASIC_INTERNAL_SS_ON_HDMI:
				percentage = le16_to_cpu(igp_info->info_7.usHDMISSPercentage);
				rate = le16_to_cpu(igp_info->info_7.usHDMISSpपढ़ोRateIn10Hz);
				अवरोध;
			हाल ASIC_INTERNAL_SS_ON_LVDS:
				percentage = le16_to_cpu(igp_info->info_7.usLvdsSSPercentage);
				rate = le16_to_cpu(igp_info->info_7.usLvdsSSpपढ़ोRateIn10Hz);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 8:
			चयन (id) अणु
			हाल ASIC_INTERNAL_SS_ON_TMDS:
				percentage = le16_to_cpu(igp_info->info_8.usDVISSPercentage);
				rate = le16_to_cpu(igp_info->info_8.usDVISSpपढ़ोRateIn10Hz);
				अवरोध;
			हाल ASIC_INTERNAL_SS_ON_HDMI:
				percentage = le16_to_cpu(igp_info->info_8.usHDMISSPercentage);
				rate = le16_to_cpu(igp_info->info_8.usHDMISSpपढ़ोRateIn10Hz);
				अवरोध;
			हाल ASIC_INTERNAL_SS_ON_LVDS:
				percentage = le16_to_cpu(igp_info->info_8.usLvdsSSPercentage);
				rate = le16_to_cpu(igp_info->info_8.usLvdsSSpपढ़ोRateIn10Hz);
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			DRM_ERROR("Unsupported IGP table: %d %d\n", frev, crev);
			अवरोध;
		पूर्ण
		अगर (percentage)
			ss->percentage = percentage;
		अगर (rate)
			ss->rate = rate;
	पूर्ण
पूर्ण

जोड़ asic_ss_info अणु
	काष्ठा _ATOM_ASIC_INTERNAL_SS_INFO info;
	काष्ठा _ATOM_ASIC_INTERNAL_SS_INFO_V2 info_2;
	काष्ठा _ATOM_ASIC_INTERNAL_SS_INFO_V3 info_3;
पूर्ण;

जोड़ asic_ss_assignment अणु
	काष्ठा _ATOM_ASIC_SS_ASSIGNMENT v1;
	काष्ठा _ATOM_ASIC_SS_ASSIGNMENT_V2 v2;
	काष्ठा _ATOM_ASIC_SS_ASSIGNMENT_V3 v3;
पूर्ण;

bool radeon_atombios_get_asic_ss_info(काष्ठा radeon_device *rdev,
				      काष्ठा radeon_atom_ss *ss,
				      पूर्णांक id, u32 घड़ी)
अणु
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, ASIC_InternalSS_Info);
	uपूर्णांक16_t data_offset, size;
	जोड़ asic_ss_info *ss_info;
	जोड़ asic_ss_assignment *ss_assign;
	uपूर्णांक8_t frev, crev;
	पूर्णांक i, num_indices;

	अगर (id == ASIC_INTERNAL_MEMORY_SS) अणु
		अगर (!(rdev->mode_info.firmware_flags & ATOM_BIOS_INFO_MEMORY_CLOCK_SS_SUPPORT))
			वापस false;
	पूर्ण
	अगर (id == ASIC_INTERNAL_ENGINE_SS) अणु
		अगर (!(rdev->mode_info.firmware_flags & ATOM_BIOS_INFO_ENGINE_CLOCK_SS_SUPPORT))
			वापस false;
	पूर्ण

	स_रखो(ss, 0, माप(काष्ठा radeon_atom_ss));
	अगर (atom_parse_data_header(mode_info->atom_context, index, &size,
				   &frev, &crev, &data_offset)) अणु

		ss_info =
			(जोड़ asic_ss_info *)(mode_info->atom_context->bios + data_offset);

		चयन (frev) अणु
		हाल 1:
			num_indices = (size - माप(ATOM_COMMON_TABLE_HEADER)) /
				माप(ATOM_ASIC_SS_ASSIGNMENT);

			ss_assign = (जोड़ asic_ss_assignment *)((u8 *)&ss_info->info.asSpपढ़ोSpectrum[0]);
			क्रम (i = 0; i < num_indices; i++) अणु
				अगर ((ss_assign->v1.ucClockIndication == id) &&
				    (घड़ी <= le32_to_cpu(ss_assign->v1.ulTargetClockRange))) अणु
					ss->percentage =
						le16_to_cpu(ss_assign->v1.usSpपढ़ोSpectrumPercentage);
					ss->type = ss_assign->v1.ucSpपढ़ोSpectrumMode;
					ss->rate = le16_to_cpu(ss_assign->v1.usSpपढ़ोRateInKhz);
					ss->percentage_भागider = 100;
					वापस true;
				पूर्ण
				ss_assign = (जोड़ asic_ss_assignment *)
					((u8 *)ss_assign + माप(ATOM_ASIC_SS_ASSIGNMENT));
			पूर्ण
			अवरोध;
		हाल 2:
			num_indices = (size - माप(ATOM_COMMON_TABLE_HEADER)) /
				माप(ATOM_ASIC_SS_ASSIGNMENT_V2);
			ss_assign = (जोड़ asic_ss_assignment *)((u8 *)&ss_info->info_2.asSpपढ़ोSpectrum[0]);
			क्रम (i = 0; i < num_indices; i++) अणु
				अगर ((ss_assign->v2.ucClockIndication == id) &&
				    (घड़ी <= le32_to_cpu(ss_assign->v2.ulTargetClockRange))) अणु
					ss->percentage =
						le16_to_cpu(ss_assign->v2.usSpपढ़ोSpectrumPercentage);
					ss->type = ss_assign->v2.ucSpपढ़ोSpectrumMode;
					ss->rate = le16_to_cpu(ss_assign->v2.usSpपढ़ोRateIn10Hz);
					ss->percentage_भागider = 100;
					अगर ((crev == 2) &&
					    ((id == ASIC_INTERNAL_ENGINE_SS) ||
					     (id == ASIC_INTERNAL_MEMORY_SS)))
						ss->rate /= 100;
					वापस true;
				पूर्ण
				ss_assign = (जोड़ asic_ss_assignment *)
					((u8 *)ss_assign + माप(ATOM_ASIC_SS_ASSIGNMENT_V2));
			पूर्ण
			अवरोध;
		हाल 3:
			num_indices = (size - माप(ATOM_COMMON_TABLE_HEADER)) /
				माप(ATOM_ASIC_SS_ASSIGNMENT_V3);
			ss_assign = (जोड़ asic_ss_assignment *)((u8 *)&ss_info->info_3.asSpपढ़ोSpectrum[0]);
			क्रम (i = 0; i < num_indices; i++) अणु
				अगर ((ss_assign->v3.ucClockIndication == id) &&
				    (घड़ी <= le32_to_cpu(ss_assign->v3.ulTargetClockRange))) अणु
					ss->percentage =
						le16_to_cpu(ss_assign->v3.usSpपढ़ोSpectrumPercentage);
					ss->type = ss_assign->v3.ucSpपढ़ोSpectrumMode;
					ss->rate = le16_to_cpu(ss_assign->v3.usSpपढ़ोRateIn10Hz);
					अगर (ss_assign->v3.ucSpपढ़ोSpectrumMode &
					    SS_MODE_V3_PERCENTAGE_DIV_BY_1000_MASK)
						ss->percentage_भागider = 1000;
					अन्यथा
						ss->percentage_भागider = 100;
					अगर ((id == ASIC_INTERNAL_ENGINE_SS) ||
					    (id == ASIC_INTERNAL_MEMORY_SS))
						ss->rate /= 100;
					अगर (rdev->flags & RADEON_IS_IGP)
						radeon_atombios_get_igp_ss_overrides(rdev, ss, id);
					वापस true;
				पूर्ण
				ss_assign = (जोड़ asic_ss_assignment *)
					((u8 *)ss_assign + माप(ATOM_ASIC_SS_ASSIGNMENT_V3));
			पूर्ण
			अवरोध;
		शेष:
			DRM_ERROR("Unsupported ASIC_InternalSS_Info table: %d %d\n", frev, crev);
			अवरोध;
		पूर्ण

	पूर्ण
	वापस false;
पूर्ण

जोड़ lvds_info अणु
	काष्ठा _ATOM_LVDS_INFO info;
	काष्ठा _ATOM_LVDS_INFO_V12 info_12;
पूर्ण;

काष्ठा radeon_encoder_atom_dig *radeon_atombios_get_lvds_info(काष्ठा
							      radeon_encoder
							      *encoder)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, LVDS_Info);
	uपूर्णांक16_t data_offset, misc;
	जोड़ lvds_info *lvds_info;
	uपूर्णांक8_t frev, crev;
	काष्ठा radeon_encoder_atom_dig *lvds = शून्य;
	पूर्णांक encoder_क्रमागत = (encoder->encoder_क्रमागत & ENUM_ID_MASK) >> ENUM_ID_SHIFT;

	अगर (atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset)) अणु
		lvds_info =
			(जोड़ lvds_info *)(mode_info->atom_context->bios + data_offset);
		lvds =
		    kzalloc(माप(काष्ठा radeon_encoder_atom_dig), GFP_KERNEL);

		अगर (!lvds)
			वापस शून्य;

		lvds->native_mode.घड़ी =
		    le16_to_cpu(lvds_info->info.sLCDTiming.usPixClk) * 10;
		lvds->native_mode.hdisplay =
		    le16_to_cpu(lvds_info->info.sLCDTiming.usHActive);
		lvds->native_mode.vdisplay =
		    le16_to_cpu(lvds_info->info.sLCDTiming.usVActive);
		lvds->native_mode.htotal = lvds->native_mode.hdisplay +
			le16_to_cpu(lvds_info->info.sLCDTiming.usHBlanking_Time);
		lvds->native_mode.hsync_start = lvds->native_mode.hdisplay +
			le16_to_cpu(lvds_info->info.sLCDTiming.usHSyncOffset);
		lvds->native_mode.hsync_end = lvds->native_mode.hsync_start +
			le16_to_cpu(lvds_info->info.sLCDTiming.usHSyncWidth);
		lvds->native_mode.vtotal = lvds->native_mode.vdisplay +
			le16_to_cpu(lvds_info->info.sLCDTiming.usVBlanking_Time);
		lvds->native_mode.vsync_start = lvds->native_mode.vdisplay +
			le16_to_cpu(lvds_info->info.sLCDTiming.usVSyncOffset);
		lvds->native_mode.vsync_end = lvds->native_mode.vsync_start +
			le16_to_cpu(lvds_info->info.sLCDTiming.usVSyncWidth);
		lvds->panel_pwr_delay =
		    le16_to_cpu(lvds_info->info.usOffDelayInMs);
		lvds->lcd_misc = lvds_info->info.ucLVDS_Misc;

		misc = le16_to_cpu(lvds_info->info.sLCDTiming.susModeMiscInfo.usAccess);
		अगर (misc & ATOM_VSYNC_POLARITY)
			lvds->native_mode.flags |= DRM_MODE_FLAG_NVSYNC;
		अगर (misc & ATOM_HSYNC_POLARITY)
			lvds->native_mode.flags |= DRM_MODE_FLAG_NHSYNC;
		अगर (misc & ATOM_COMPOSITESYNC)
			lvds->native_mode.flags |= DRM_MODE_FLAG_CSYNC;
		अगर (misc & ATOM_INTERLACE)
			lvds->native_mode.flags |= DRM_MODE_FLAG_INTERLACE;
		अगर (misc & ATOM_DOUBLE_CLOCK_MODE)
			lvds->native_mode.flags |= DRM_MODE_FLAG_DBLSCAN;

		lvds->native_mode.width_mm = le16_to_cpu(lvds_info->info.sLCDTiming.usImageHSize);
		lvds->native_mode.height_mm = le16_to_cpu(lvds_info->info.sLCDTiming.usImageVSize);

		/* set crtc values */
		drm_mode_set_crtcinfo(&lvds->native_mode, CRTC_INTERLACE_HALVE_V);

		lvds->lcd_ss_id = lvds_info->info.ucSS_Id;

		encoder->native_mode = lvds->native_mode;

		अगर (encoder_क्रमागत == 2)
			lvds->linkb = true;
		अन्यथा
			lvds->linkb = false;

		/* parse the lcd record table */
		अगर (le16_to_cpu(lvds_info->info.usModePatchTableOffset)) अणु
			ATOM_FAKE_EDID_PATCH_RECORD *fake_edid_record;
			ATOM_PANEL_RESOLUTION_PATCH_RECORD *panel_res_record;
			bool bad_record = false;
			u8 *record;

			अगर ((frev == 1) && (crev < 2))
				/* असलolute */
				record = (u8 *)(mode_info->atom_context->bios +
						le16_to_cpu(lvds_info->info.usModePatchTableOffset));
			अन्यथा
				/* relative */
				record = (u8 *)(mode_info->atom_context->bios +
						data_offset +
						le16_to_cpu(lvds_info->info.usModePatchTableOffset));
			जबतक (*record != ATOM_RECORD_END_TYPE) अणु
				चयन (*record) अणु
				हाल LCD_MODE_PATCH_RECORD_MODE_TYPE:
					record += माप(ATOM_PATCH_RECORD_MODE);
					अवरोध;
				हाल LCD_RTS_RECORD_TYPE:
					record += माप(ATOM_LCD_RTS_RECORD);
					अवरोध;
				हाल LCD_CAP_RECORD_TYPE:
					record += माप(ATOM_LCD_MODE_CONTROL_CAP);
					अवरोध;
				हाल LCD_FAKE_EDID_PATCH_RECORD_TYPE:
					fake_edid_record = (ATOM_FAKE_EDID_PATCH_RECORD *)record;
					अगर (fake_edid_record->ucFakeEDIDLength) अणु
						काष्ठा edid *edid;
						पूर्णांक edid_size =
							max((पूर्णांक)EDID_LENGTH, (पूर्णांक)fake_edid_record->ucFakeEDIDLength);
						edid = kदो_स्मृति(edid_size, GFP_KERNEL);
						अगर (edid) अणु
							स_नकल((u8 *)edid, (u8 *)&fake_edid_record->ucFakeEDIDString[0],
							       fake_edid_record->ucFakeEDIDLength);

							अगर (drm_edid_is_valid(edid)) अणु
								rdev->mode_info.bios_hardcoded_edid = edid;
								rdev->mode_info.bios_hardcoded_edid_size = edid_size;
							पूर्ण अन्यथा
								kमुक्त(edid);
						पूर्ण
					पूर्ण
					record += fake_edid_record->ucFakeEDIDLength ?
						fake_edid_record->ucFakeEDIDLength + 2 :
						माप(ATOM_FAKE_EDID_PATCH_RECORD);
					अवरोध;
				हाल LCD_PANEL_RESOLUTION_RECORD_TYPE:
					panel_res_record = (ATOM_PANEL_RESOLUTION_PATCH_RECORD *)record;
					lvds->native_mode.width_mm = panel_res_record->usHSize;
					lvds->native_mode.height_mm = panel_res_record->usVSize;
					record += माप(ATOM_PANEL_RESOLUTION_PATCH_RECORD);
					अवरोध;
				शेष:
					DRM_ERROR("Bad LCD record %d\n", *record);
					bad_record = true;
					अवरोध;
				पूर्ण
				अगर (bad_record)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस lvds;
पूर्ण

काष्ठा radeon_encoder_primary_dac *
radeon_atombios_get_primary_dac_info(काष्ठा radeon_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, CompassionateData);
	uपूर्णांक16_t data_offset;
	काष्ठा _COMPASSIONATE_DATA *dac_info;
	uपूर्णांक8_t frev, crev;
	uपूर्णांक8_t bg, dac;
	काष्ठा radeon_encoder_primary_dac *p_dac = शून्य;

	अगर (atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset)) अणु
		dac_info = (काष्ठा _COMPASSIONATE_DATA *)
			(mode_info->atom_context->bios + data_offset);

		p_dac = kzalloc(माप(काष्ठा radeon_encoder_primary_dac), GFP_KERNEL);

		अगर (!p_dac)
			वापस शून्य;

		bg = dac_info->ucDAC1_BG_Adjusपंचांगent;
		dac = dac_info->ucDAC1_DAC_Adjusपंचांगent;
		p_dac->ps2_pdac_adj = (bg << 8) | (dac);

	पूर्ण
	वापस p_dac;
पूर्ण

bool radeon_atom_get_tv_timings(काष्ठा radeon_device *rdev, पूर्णांक index,
				काष्ठा drm_display_mode *mode)
अणु
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	ATOM_ANALOG_TV_INFO *tv_info;
	ATOM_ANALOG_TV_INFO_V1_2 *tv_info_v1_2;
	ATOM_DTD_FORMAT *dtd_timings;
	पूर्णांक data_index = GetIndexIntoMasterTable(DATA, AnalogTV_Info);
	u8 frev, crev;
	u16 data_offset, misc;

	अगर (!atom_parse_data_header(mode_info->atom_context, data_index, शून्य,
				    &frev, &crev, &data_offset))
		वापस false;

	चयन (crev) अणु
	हाल 1:
		tv_info = (ATOM_ANALOG_TV_INFO *)(mode_info->atom_context->bios + data_offset);
		अगर (index >= MAX_SUPPORTED_TV_TIMING)
			वापस false;

		mode->crtc_htotal = le16_to_cpu(tv_info->aModeTimings[index].usCRTC_H_Total);
		mode->crtc_hdisplay = le16_to_cpu(tv_info->aModeTimings[index].usCRTC_H_Disp);
		mode->crtc_hsync_start = le16_to_cpu(tv_info->aModeTimings[index].usCRTC_H_SyncStart);
		mode->crtc_hsync_end = le16_to_cpu(tv_info->aModeTimings[index].usCRTC_H_SyncStart) +
			le16_to_cpu(tv_info->aModeTimings[index].usCRTC_H_SyncWidth);

		mode->crtc_vtotal = le16_to_cpu(tv_info->aModeTimings[index].usCRTC_V_Total);
		mode->crtc_vdisplay = le16_to_cpu(tv_info->aModeTimings[index].usCRTC_V_Disp);
		mode->crtc_vsync_start = le16_to_cpu(tv_info->aModeTimings[index].usCRTC_V_SyncStart);
		mode->crtc_vsync_end = le16_to_cpu(tv_info->aModeTimings[index].usCRTC_V_SyncStart) +
			le16_to_cpu(tv_info->aModeTimings[index].usCRTC_V_SyncWidth);

		mode->flags = 0;
		misc = le16_to_cpu(tv_info->aModeTimings[index].susModeMiscInfo.usAccess);
		अगर (misc & ATOM_VSYNC_POLARITY)
			mode->flags |= DRM_MODE_FLAG_NVSYNC;
		अगर (misc & ATOM_HSYNC_POLARITY)
			mode->flags |= DRM_MODE_FLAG_NHSYNC;
		अगर (misc & ATOM_COMPOSITESYNC)
			mode->flags |= DRM_MODE_FLAG_CSYNC;
		अगर (misc & ATOM_INTERLACE)
			mode->flags |= DRM_MODE_FLAG_INTERLACE;
		अगर (misc & ATOM_DOUBLE_CLOCK_MODE)
			mode->flags |= DRM_MODE_FLAG_DBLSCAN;

		mode->crtc_घड़ी = mode->घड़ी =
			le16_to_cpu(tv_info->aModeTimings[index].usPixelClock) * 10;

		अगर (index == 1) अणु
			/* PAL timings appear to have wrong values क्रम totals */
			mode->crtc_htotal -= 1;
			mode->crtc_vtotal -= 1;
		पूर्ण
		अवरोध;
	हाल 2:
		tv_info_v1_2 = (ATOM_ANALOG_TV_INFO_V1_2 *)(mode_info->atom_context->bios + data_offset);
		अगर (index >= MAX_SUPPORTED_TV_TIMING_V1_2)
			वापस false;

		dtd_timings = &tv_info_v1_2->aModeTimings[index];
		mode->crtc_htotal = le16_to_cpu(dtd_timings->usHActive) +
			le16_to_cpu(dtd_timings->usHBlanking_Time);
		mode->crtc_hdisplay = le16_to_cpu(dtd_timings->usHActive);
		mode->crtc_hsync_start = le16_to_cpu(dtd_timings->usHActive) +
			le16_to_cpu(dtd_timings->usHSyncOffset);
		mode->crtc_hsync_end = mode->crtc_hsync_start +
			le16_to_cpu(dtd_timings->usHSyncWidth);

		mode->crtc_vtotal = le16_to_cpu(dtd_timings->usVActive) +
			le16_to_cpu(dtd_timings->usVBlanking_Time);
		mode->crtc_vdisplay = le16_to_cpu(dtd_timings->usVActive);
		mode->crtc_vsync_start = le16_to_cpu(dtd_timings->usVActive) +
			le16_to_cpu(dtd_timings->usVSyncOffset);
		mode->crtc_vsync_end = mode->crtc_vsync_start +
			le16_to_cpu(dtd_timings->usVSyncWidth);

		mode->flags = 0;
		misc = le16_to_cpu(dtd_timings->susModeMiscInfo.usAccess);
		अगर (misc & ATOM_VSYNC_POLARITY)
			mode->flags |= DRM_MODE_FLAG_NVSYNC;
		अगर (misc & ATOM_HSYNC_POLARITY)
			mode->flags |= DRM_MODE_FLAG_NHSYNC;
		अगर (misc & ATOM_COMPOSITESYNC)
			mode->flags |= DRM_MODE_FLAG_CSYNC;
		अगर (misc & ATOM_INTERLACE)
			mode->flags |= DRM_MODE_FLAG_INTERLACE;
		अगर (misc & ATOM_DOUBLE_CLOCK_MODE)
			mode->flags |= DRM_MODE_FLAG_DBLSCAN;

		mode->crtc_घड़ी = mode->घड़ी =
			le16_to_cpu(dtd_timings->usPixClk) * 10;
		अवरोध;
	पूर्ण
	वापस true;
पूर्ण

क्रमागत radeon_tv_std
radeon_atombios_get_tv_info(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, AnalogTV_Info);
	uपूर्णांक16_t data_offset;
	uपूर्णांक8_t frev, crev;
	काष्ठा _ATOM_ANALOG_TV_INFO *tv_info;
	क्रमागत radeon_tv_std tv_std = TV_STD_NTSC;

	अगर (atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset)) अणु

		tv_info = (काष्ठा _ATOM_ANALOG_TV_INFO *)
			(mode_info->atom_context->bios + data_offset);

		चयन (tv_info->ucTV_BootUpDefaultStandard) अणु
		हाल ATOM_TV_NTSC:
			tv_std = TV_STD_NTSC;
			DRM_DEBUG_KMS("Default TV standard: NTSC\n");
			अवरोध;
		हाल ATOM_TV_NTSCJ:
			tv_std = TV_STD_NTSC_J;
			DRM_DEBUG_KMS("Default TV standard: NTSC-J\n");
			अवरोध;
		हाल ATOM_TV_PAL:
			tv_std = TV_STD_PAL;
			DRM_DEBUG_KMS("Default TV standard: PAL\n");
			अवरोध;
		हाल ATOM_TV_PALM:
			tv_std = TV_STD_PAL_M;
			DRM_DEBUG_KMS("Default TV standard: PAL-M\n");
			अवरोध;
		हाल ATOM_TV_PALN:
			tv_std = TV_STD_PAL_N;
			DRM_DEBUG_KMS("Default TV standard: PAL-N\n");
			अवरोध;
		हाल ATOM_TV_PALCN:
			tv_std = TV_STD_PAL_CN;
			DRM_DEBUG_KMS("Default TV standard: PAL-CN\n");
			अवरोध;
		हाल ATOM_TV_PAL60:
			tv_std = TV_STD_PAL_60;
			DRM_DEBUG_KMS("Default TV standard: PAL-60\n");
			अवरोध;
		हाल ATOM_TV_SECAM:
			tv_std = TV_STD_SECAM;
			DRM_DEBUG_KMS("Default TV standard: SECAM\n");
			अवरोध;
		शेष:
			tv_std = TV_STD_NTSC;
			DRM_DEBUG_KMS("Unknown TV standard; defaulting to NTSC\n");
			अवरोध;
		पूर्ण
	पूर्ण
	वापस tv_std;
पूर्ण

काष्ठा radeon_encoder_tv_dac *
radeon_atombios_get_tv_dac_info(काष्ठा radeon_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, CompassionateData);
	uपूर्णांक16_t data_offset;
	काष्ठा _COMPASSIONATE_DATA *dac_info;
	uपूर्णांक8_t frev, crev;
	uपूर्णांक8_t bg, dac;
	काष्ठा radeon_encoder_tv_dac *tv_dac = शून्य;

	अगर (atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset)) अणु

		dac_info = (काष्ठा _COMPASSIONATE_DATA *)
			(mode_info->atom_context->bios + data_offset);

		tv_dac = kzalloc(माप(काष्ठा radeon_encoder_tv_dac), GFP_KERNEL);

		अगर (!tv_dac)
			वापस शून्य;

		bg = dac_info->ucDAC2_CRT2_BG_Adjusपंचांगent;
		dac = dac_info->ucDAC2_CRT2_DAC_Adjusपंचांगent;
		tv_dac->ps2_tvdac_adj = (bg << 16) | (dac << 20);

		bg = dac_info->ucDAC2_PAL_BG_Adjusपंचांगent;
		dac = dac_info->ucDAC2_PAL_DAC_Adjusपंचांगent;
		tv_dac->pal_tvdac_adj = (bg << 16) | (dac << 20);

		bg = dac_info->ucDAC2_NTSC_BG_Adjusपंचांगent;
		dac = dac_info->ucDAC2_NTSC_DAC_Adjusपंचांगent;
		tv_dac->ntsc_tvdac_adj = (bg << 16) | (dac << 20);

		tv_dac->tv_std = radeon_atombios_get_tv_info(rdev);
	पूर्ण
	वापस tv_dac;
पूर्ण

अटल स्थिर अक्षर *thermal_controller_names[] = अणु
	"NONE",
	"lm63",
	"adm1032",
	"adm1030",
	"max6649",
	"lm63", /* lm64 */
	"f75375",
	"asc7xxx",
पूर्ण;

अटल स्थिर अक्षर *pp_lib_thermal_controller_names[] = अणु
	"NONE",
	"lm63",
	"adm1032",
	"adm1030",
	"max6649",
	"lm63", /* lm64 */
	"f75375",
	"RV6xx",
	"RV770",
	"adt7473",
	"NONE",
	"External GPIO",
	"Evergreen",
	"emc2103",
	"Sumo",
	"Northern Islands",
	"Southern Islands",
	"lm96163",
	"Sea Islands",
पूर्ण;

जोड़ घातer_info अणु
	काष्ठा _ATOM_POWERPLAY_INFO info;
	काष्ठा _ATOM_POWERPLAY_INFO_V2 info_2;
	काष्ठा _ATOM_POWERPLAY_INFO_V3 info_3;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE pplib;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE2 pplib2;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE3 pplib3;
पूर्ण;

जोड़ pplib_घड़ी_info अणु
	काष्ठा _ATOM_PPLIB_R600_CLOCK_INFO r600;
	काष्ठा _ATOM_PPLIB_RS780_CLOCK_INFO rs780;
	काष्ठा _ATOM_PPLIB_EVERGREEN_CLOCK_INFO evergreen;
	काष्ठा _ATOM_PPLIB_SUMO_CLOCK_INFO sumo;
	काष्ठा _ATOM_PPLIB_SI_CLOCK_INFO si;
	काष्ठा _ATOM_PPLIB_CI_CLOCK_INFO ci;
पूर्ण;

जोड़ pplib_घातer_state अणु
	काष्ठा _ATOM_PPLIB_STATE v1;
	काष्ठा _ATOM_PPLIB_STATE_V2 v2;
पूर्ण;

अटल व्योम radeon_atombios_parse_misc_flags_1_3(काष्ठा radeon_device *rdev,
						 पूर्णांक state_index,
						 u32 misc, u32 misc2)
अणु
	rdev->pm.घातer_state[state_index].misc = misc;
	rdev->pm.घातer_state[state_index].misc2 = misc2;
	/* order matters! */
	अगर (misc & ATOM_PM_MISCINFO_POWER_SAVING_MODE)
		rdev->pm.घातer_state[state_index].type =
			POWER_STATE_TYPE_POWERSAVE;
	अगर (misc & ATOM_PM_MISCINFO_DEFAULT_DC_STATE_ENTRY_TRUE)
		rdev->pm.घातer_state[state_index].type =
			POWER_STATE_TYPE_BATTERY;
	अगर (misc & ATOM_PM_MISCINFO_DEFAULT_LOW_DC_STATE_ENTRY_TRUE)
		rdev->pm.घातer_state[state_index].type =
			POWER_STATE_TYPE_BATTERY;
	अगर (misc & ATOM_PM_MISCINFO_LOAD_BALANCE_EN)
		rdev->pm.घातer_state[state_index].type =
			POWER_STATE_TYPE_BALANCED;
	अगर (misc & ATOM_PM_MISCINFO_3D_ACCELERATION_EN) अणु
		rdev->pm.घातer_state[state_index].type =
			POWER_STATE_TYPE_PERFORMANCE;
		rdev->pm.घातer_state[state_index].flags &=
			~RADEON_PM_STATE_SINGLE_DISPLAY_ONLY;
	पूर्ण
	अगर (misc2 & ATOM_PM_MISCINFO2_SYSTEM_AC_LITE_MODE)
		rdev->pm.घातer_state[state_index].type =
			POWER_STATE_TYPE_BALANCED;
	अगर (misc & ATOM_PM_MISCINFO_DRIVER_DEFAULT_MODE) अणु
		rdev->pm.घातer_state[state_index].type =
			POWER_STATE_TYPE_DEFAULT;
		rdev->pm.शेष_घातer_state_index = state_index;
		rdev->pm.घातer_state[state_index].शेष_घड़ी_mode =
			&rdev->pm.घातer_state[state_index].घड़ी_info[0];
	पूर्ण अन्यथा अगर (state_index == 0) अणु
		rdev->pm.घातer_state[state_index].घड़ी_info[0].flags |=
			RADEON_PM_MODE_NO_DISPLAY;
	पूर्ण
पूर्ण

अटल पूर्णांक radeon_atombios_parse_घातer_table_1_3(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	u32 misc, misc2 = 0;
	पूर्णांक num_modes = 0, i;
	पूर्णांक state_index = 0;
	काष्ठा radeon_i2c_bus_rec i2c_bus;
	जोड़ घातer_info *घातer_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);
	u16 data_offset;
	u8 frev, crev;

	अगर (!atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset))
		वापस state_index;
	घातer_info = (जोड़ घातer_info *)(mode_info->atom_context->bios + data_offset);

	/* add the i2c bus क्रम thermal/fan chip */
	अगर ((घातer_info->info.ucOverdriveThermalController > 0) &&
	    (घातer_info->info.ucOverdriveThermalController < ARRAY_SIZE(thermal_controller_names))) अणु
		DRM_INFO("Possible %s thermal controller at 0x%02x\n",
			 thermal_controller_names[घातer_info->info.ucOverdriveThermalController],
			 घातer_info->info.ucOverdriveControllerAddress >> 1);
		i2c_bus = radeon_lookup_i2c_gpio(rdev, घातer_info->info.ucOverdriveI2cLine);
		rdev->pm.i2c_bus = radeon_i2c_lookup(rdev, &i2c_bus);
		अगर (rdev->pm.i2c_bus) अणु
			काष्ठा i2c_board_info info = अणु पूर्ण;
			स्थिर अक्षर *name = thermal_controller_names[घातer_info->info.
								    ucOverdriveThermalController];
			info.addr = घातer_info->info.ucOverdriveControllerAddress >> 1;
			strlcpy(info.type, name, माप(info.type));
			i2c_new_client_device(&rdev->pm.i2c_bus->adapter, &info);
		पूर्ण
	पूर्ण
	num_modes = घातer_info->info.ucNumOfPowerModeEntries;
	अगर (num_modes > ATOM_MAX_NUMBEROF_POWER_BLOCK)
		num_modes = ATOM_MAX_NUMBEROF_POWER_BLOCK;
	अगर (num_modes == 0)
		वापस state_index;
	rdev->pm.घातer_state = kसुस्मृति(num_modes,
				       माप(काष्ठा radeon_घातer_state),
				       GFP_KERNEL);
	अगर (!rdev->pm.घातer_state)
		वापस state_index;
	/* last mode is usually शेष, array is low to high */
	क्रम (i = 0; i < num_modes; i++) अणु
		/* aव्योम memory leaks from invalid modes or unknown frev. */
		अगर (!rdev->pm.घातer_state[state_index].घड़ी_info) अणु
			rdev->pm.घातer_state[state_index].घड़ी_info =
				kzalloc(माप(काष्ठा radeon_pm_घड़ी_info),
					GFP_KERNEL);
		पूर्ण
		अगर (!rdev->pm.घातer_state[state_index].घड़ी_info)
			जाओ out;
		rdev->pm.घातer_state[state_index].num_घड़ी_modes = 1;
		rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.type = VOLTAGE_NONE;
		चयन (frev) अणु
		हाल 1:
			rdev->pm.घातer_state[state_index].घड़ी_info[0].mclk =
				le16_to_cpu(घातer_info->info.asPowerPlayInfo[i].usMemoryClock);
			rdev->pm.घातer_state[state_index].घड़ी_info[0].sclk =
				le16_to_cpu(घातer_info->info.asPowerPlayInfo[i].usEngineClock);
			/* skip invalid modes */
			अगर ((rdev->pm.घातer_state[state_index].घड़ी_info[0].mclk == 0) ||
			    (rdev->pm.घातer_state[state_index].घड़ी_info[0].sclk == 0))
				जारी;
			rdev->pm.घातer_state[state_index].pcie_lanes =
				घातer_info->info.asPowerPlayInfo[i].ucNumPciELanes;
			misc = le32_to_cpu(घातer_info->info.asPowerPlayInfo[i].ulMiscInfo);
			अगर ((misc & ATOM_PM_MISCINFO_VOLTAGE_DROP_SUPPORT) ||
			    (misc & ATOM_PM_MISCINFO_VOLTAGE_DROP_ACTIVE_HIGH)) अणु
				rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.type =
					VOLTAGE_GPIO;
				rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.gpio =
					radeon_atombios_lookup_gpio(rdev,
							   घातer_info->info.asPowerPlayInfo[i].ucVoltageDropIndex);
				अगर (misc & ATOM_PM_MISCINFO_VOLTAGE_DROP_ACTIVE_HIGH)
					rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.active_high =
						true;
				अन्यथा
					rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.active_high =
						false;
			पूर्ण अन्यथा अगर (misc & ATOM_PM_MISCINFO_PROGRAM_VOLTAGE) अणु
				rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.type =
					VOLTAGE_VDDC;
				rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.vddc_id =
					घातer_info->info.asPowerPlayInfo[i].ucVoltageDropIndex;
			पूर्ण
			rdev->pm.घातer_state[state_index].flags = RADEON_PM_STATE_SINGLE_DISPLAY_ONLY;
			radeon_atombios_parse_misc_flags_1_3(rdev, state_index, misc, 0);
			state_index++;
			अवरोध;
		हाल 2:
			rdev->pm.घातer_state[state_index].घड़ी_info[0].mclk =
				le32_to_cpu(घातer_info->info_2.asPowerPlayInfo[i].ulMemoryClock);
			rdev->pm.घातer_state[state_index].घड़ी_info[0].sclk =
				le32_to_cpu(घातer_info->info_2.asPowerPlayInfo[i].ulEngineClock);
			/* skip invalid modes */
			अगर ((rdev->pm.घातer_state[state_index].घड़ी_info[0].mclk == 0) ||
			    (rdev->pm.घातer_state[state_index].घड़ी_info[0].sclk == 0))
				जारी;
			rdev->pm.घातer_state[state_index].pcie_lanes =
				घातer_info->info_2.asPowerPlayInfo[i].ucNumPciELanes;
			misc = le32_to_cpu(घातer_info->info_2.asPowerPlayInfo[i].ulMiscInfo);
			misc2 = le32_to_cpu(घातer_info->info_2.asPowerPlayInfo[i].ulMiscInfo2);
			अगर ((misc & ATOM_PM_MISCINFO_VOLTAGE_DROP_SUPPORT) ||
			    (misc & ATOM_PM_MISCINFO_VOLTAGE_DROP_ACTIVE_HIGH)) अणु
				rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.type =
					VOLTAGE_GPIO;
				rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.gpio =
					radeon_atombios_lookup_gpio(rdev,
							   घातer_info->info_2.asPowerPlayInfo[i].ucVoltageDropIndex);
				अगर (misc & ATOM_PM_MISCINFO_VOLTAGE_DROP_ACTIVE_HIGH)
					rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.active_high =
						true;
				अन्यथा
					rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.active_high =
						false;
			पूर्ण अन्यथा अगर (misc & ATOM_PM_MISCINFO_PROGRAM_VOLTAGE) अणु
				rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.type =
					VOLTAGE_VDDC;
				rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.vddc_id =
					घातer_info->info_2.asPowerPlayInfo[i].ucVoltageDropIndex;
			पूर्ण
			rdev->pm.घातer_state[state_index].flags = RADEON_PM_STATE_SINGLE_DISPLAY_ONLY;
			radeon_atombios_parse_misc_flags_1_3(rdev, state_index, misc, misc2);
			state_index++;
			अवरोध;
		हाल 3:
			rdev->pm.घातer_state[state_index].घड़ी_info[0].mclk =
				le32_to_cpu(घातer_info->info_3.asPowerPlayInfo[i].ulMemoryClock);
			rdev->pm.घातer_state[state_index].घड़ी_info[0].sclk =
				le32_to_cpu(घातer_info->info_3.asPowerPlayInfo[i].ulEngineClock);
			/* skip invalid modes */
			अगर ((rdev->pm.घातer_state[state_index].घड़ी_info[0].mclk == 0) ||
			    (rdev->pm.घातer_state[state_index].घड़ी_info[0].sclk == 0))
				जारी;
			rdev->pm.घातer_state[state_index].pcie_lanes =
				घातer_info->info_3.asPowerPlayInfo[i].ucNumPciELanes;
			misc = le32_to_cpu(घातer_info->info_3.asPowerPlayInfo[i].ulMiscInfo);
			misc2 = le32_to_cpu(घातer_info->info_3.asPowerPlayInfo[i].ulMiscInfo2);
			अगर ((misc & ATOM_PM_MISCINFO_VOLTAGE_DROP_SUPPORT) ||
			    (misc & ATOM_PM_MISCINFO_VOLTAGE_DROP_ACTIVE_HIGH)) अणु
				rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.type =
					VOLTAGE_GPIO;
				rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.gpio =
					radeon_atombios_lookup_gpio(rdev,
							   घातer_info->info_3.asPowerPlayInfo[i].ucVoltageDropIndex);
				अगर (misc & ATOM_PM_MISCINFO_VOLTAGE_DROP_ACTIVE_HIGH)
					rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.active_high =
						true;
				अन्यथा
					rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.active_high =
						false;
			पूर्ण अन्यथा अगर (misc & ATOM_PM_MISCINFO_PROGRAM_VOLTAGE) अणु
				rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.type =
					VOLTAGE_VDDC;
				rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.vddc_id =
					घातer_info->info_3.asPowerPlayInfo[i].ucVoltageDropIndex;
				अगर (misc2 & ATOM_PM_MISCINFO2_VDDCI_DYNAMIC_VOLTAGE_EN) अणु
					rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.vddci_enabled =
						true;
					rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.vddci_id =
						घातer_info->info_3.asPowerPlayInfo[i].ucVDDCI_VoltageDropIndex;
				पूर्ण
			पूर्ण
			rdev->pm.घातer_state[state_index].flags = RADEON_PM_STATE_SINGLE_DISPLAY_ONLY;
			radeon_atombios_parse_misc_flags_1_3(rdev, state_index, misc, misc2);
			state_index++;
			अवरोध;
		पूर्ण
	पूर्ण
out:
	/* मुक्त any unused घड़ी_info allocation. */
	अगर (state_index && state_index < num_modes) अणु
		kमुक्त(rdev->pm.घातer_state[state_index].घड़ी_info);
		rdev->pm.घातer_state[state_index].घड़ी_info = शून्य;
	पूर्ण

	/* last mode is usually शेष */
	अगर (state_index && rdev->pm.शेष_घातer_state_index == -1) अणु
		rdev->pm.घातer_state[state_index - 1].type =
			POWER_STATE_TYPE_DEFAULT;
		rdev->pm.शेष_घातer_state_index = state_index - 1;
		rdev->pm.घातer_state[state_index - 1].शेष_घड़ी_mode =
			&rdev->pm.घातer_state[state_index - 1].घड़ी_info[0];
		rdev->pm.घातer_state[state_index - 1].flags &=
			~RADEON_PM_STATE_SINGLE_DISPLAY_ONLY;
		rdev->pm.घातer_state[state_index - 1].misc = 0;
		rdev->pm.घातer_state[state_index - 1].misc2 = 0;
	पूर्ण
	वापस state_index;
पूर्ण

अटल व्योम radeon_atombios_add_pplib_thermal_controller(काष्ठा radeon_device *rdev,
							 ATOM_PPLIB_THERMALCONTROLLER *controller)
अणु
	काष्ठा radeon_i2c_bus_rec i2c_bus;

	/* add the i2c bus क्रम thermal/fan chip */
	अगर (controller->ucType > 0) अणु
		अगर (controller->ucFanParameters & ATOM_PP_FANPARAMETERS_NOFAN)
			rdev->pm.no_fan = true;
		rdev->pm.fan_pulses_per_revolution =
			controller->ucFanParameters & ATOM_PP_FANPARAMETERS_TACHOMETER_PULSES_PER_REVOLUTION_MASK;
		अगर (rdev->pm.fan_pulses_per_revolution) अणु
			rdev->pm.fan_min_rpm = controller->ucFanMinRPM;
			rdev->pm.fan_max_rpm = controller->ucFanMaxRPM;
		पूर्ण
		अगर (controller->ucType == ATOM_PP_THERMALCONTROLLER_RV6xx) अणु
			DRM_INFO("Internal thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			rdev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_RV6XX;
		पूर्ण अन्यथा अगर (controller->ucType == ATOM_PP_THERMALCONTROLLER_RV770) अणु
			DRM_INFO("Internal thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			rdev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_RV770;
		पूर्ण अन्यथा अगर (controller->ucType == ATOM_PP_THERMALCONTROLLER_EVERGREEN) अणु
			DRM_INFO("Internal thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			rdev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_EVERGREEN;
		पूर्ण अन्यथा अगर (controller->ucType == ATOM_PP_THERMALCONTROLLER_SUMO) अणु
			DRM_INFO("Internal thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			rdev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_SUMO;
		पूर्ण अन्यथा अगर (controller->ucType == ATOM_PP_THERMALCONTROLLER_NISLANDS) अणु
			DRM_INFO("Internal thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			rdev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_NI;
		पूर्ण अन्यथा अगर (controller->ucType == ATOM_PP_THERMALCONTROLLER_SISLANDS) अणु
			DRM_INFO("Internal thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			rdev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_SI;
		पूर्ण अन्यथा अगर (controller->ucType == ATOM_PP_THERMALCONTROLLER_CISLANDS) अणु
			DRM_INFO("Internal thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			rdev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_CI;
		पूर्ण अन्यथा अगर (controller->ucType == ATOM_PP_THERMALCONTROLLER_KAVERI) अणु
			DRM_INFO("Internal thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			rdev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_KV;
		पूर्ण अन्यथा अगर (controller->ucType ==
			   ATOM_PP_THERMALCONTROLLER_EXTERNAL_GPIO) अणु
			DRM_INFO("External GPIO thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			rdev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_EXTERNAL_GPIO;
		पूर्ण अन्यथा अगर (controller->ucType ==
			   ATOM_PP_THERMALCONTROLLER_ADT7473_WITH_INTERNAL) अणु
			DRM_INFO("ADT7473 with internal thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			rdev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_ADT7473_WITH_INTERNAL;
		पूर्ण अन्यथा अगर (controller->ucType ==
			   ATOM_PP_THERMALCONTROLLER_EMC2103_WITH_INTERNAL) अणु
			DRM_INFO("EMC2103 with internal thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			rdev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_EMC2103_WITH_INTERNAL;
		पूर्ण अन्यथा अगर (controller->ucType < ARRAY_SIZE(pp_lib_thermal_controller_names)) अणु
			DRM_INFO("Possible %s thermal controller at 0x%02x %s fan control\n",
				 pp_lib_thermal_controller_names[controller->ucType],
				 controller->ucI2cAddress >> 1,
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			rdev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_EXTERNAL;
			i2c_bus = radeon_lookup_i2c_gpio(rdev, controller->ucI2cLine);
			rdev->pm.i2c_bus = radeon_i2c_lookup(rdev, &i2c_bus);
			अगर (rdev->pm.i2c_bus) अणु
				काष्ठा i2c_board_info info = अणु पूर्ण;
				स्थिर अक्षर *name = pp_lib_thermal_controller_names[controller->ucType];
				info.addr = controller->ucI2cAddress >> 1;
				strlcpy(info.type, name, माप(info.type));
				i2c_new_client_device(&rdev->pm.i2c_bus->adapter, &info);
			पूर्ण
		पूर्ण अन्यथा अणु
			DRM_INFO("Unknown thermal controller type %d at 0x%02x %s fan control\n",
				 controller->ucType,
				 controller->ucI2cAddress >> 1,
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
		पूर्ण
	पूर्ण
पूर्ण

व्योम radeon_atombios_get_शेष_voltages(काष्ठा radeon_device *rdev,
					  u16 *vddc, u16 *vddci, u16 *mvdd)
अणु
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, FirmwareInfo);
	u8 frev, crev;
	u16 data_offset;
	जोड़ firmware_info *firmware_info;

	*vddc = 0;
	*vddci = 0;
	*mvdd = 0;

	अगर (atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset)) अणु
		firmware_info =
			(जोड़ firmware_info *)(mode_info->atom_context->bios +
						data_offset);
		*vddc = le16_to_cpu(firmware_info->info_14.usBootUpVDDCVoltage);
		अगर ((frev == 2) && (crev >= 2)) अणु
			*vddci = le16_to_cpu(firmware_info->info_22.usBootUpVDDCIVoltage);
			*mvdd = le16_to_cpu(firmware_info->info_22.usBootUpMVDDCVoltage);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम radeon_atombios_parse_pplib_non_घड़ी_info(काष्ठा radeon_device *rdev,
						       पूर्णांक state_index, पूर्णांक mode_index,
						       काष्ठा _ATOM_PPLIB_NONCLOCK_INFO *non_घड़ी_info)
अणु
	पूर्णांक j;
	u32 misc = le32_to_cpu(non_घड़ी_info->ulCapsAndSettings);
	u32 misc2 = le16_to_cpu(non_घड़ी_info->usClassअगरication);
	u16 vddc, vddci, mvdd;

	radeon_atombios_get_शेष_voltages(rdev, &vddc, &vddci, &mvdd);

	rdev->pm.घातer_state[state_index].misc = misc;
	rdev->pm.घातer_state[state_index].misc2 = misc2;
	rdev->pm.घातer_state[state_index].pcie_lanes =
		((misc & ATOM_PPLIB_PCIE_LINK_WIDTH_MASK) >>
		 ATOM_PPLIB_PCIE_LINK_WIDTH_SHIFT) + 1;
	चयन (misc2 & ATOM_PPLIB_CLASSIFICATION_UI_MASK) अणु
	हाल ATOM_PPLIB_CLASSIFICATION_UI_BATTERY:
		rdev->pm.घातer_state[state_index].type =
			POWER_STATE_TYPE_BATTERY;
		अवरोध;
	हाल ATOM_PPLIB_CLASSIFICATION_UI_BALANCED:
		rdev->pm.घातer_state[state_index].type =
			POWER_STATE_TYPE_BALANCED;
		अवरोध;
	हाल ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE:
		rdev->pm.घातer_state[state_index].type =
			POWER_STATE_TYPE_PERFORMANCE;
		अवरोध;
	हाल ATOM_PPLIB_CLASSIFICATION_UI_NONE:
		अगर (misc2 & ATOM_PPLIB_CLASSIFICATION_3DPERFORMANCE)
			rdev->pm.घातer_state[state_index].type =
				POWER_STATE_TYPE_PERFORMANCE;
		अवरोध;
	पूर्ण
	rdev->pm.घातer_state[state_index].flags = 0;
	अगर (misc & ATOM_PPLIB_SINGLE_DISPLAY_ONLY)
		rdev->pm.घातer_state[state_index].flags |=
			RADEON_PM_STATE_SINGLE_DISPLAY_ONLY;
	अगर (misc2 & ATOM_PPLIB_CLASSIFICATION_BOOT) अणु
		rdev->pm.घातer_state[state_index].type =
			POWER_STATE_TYPE_DEFAULT;
		rdev->pm.शेष_घातer_state_index = state_index;
		rdev->pm.घातer_state[state_index].शेष_घड़ी_mode =
			&rdev->pm.घातer_state[state_index].घड़ी_info[mode_index - 1];
		अगर ((rdev->family >= CHIP_BARTS) && !(rdev->flags & RADEON_IS_IGP)) अणु
			/* NI chips post without MC ucode, so शेष घड़ीs are strobe mode only */
			rdev->pm.शेष_sclk = rdev->pm.घातer_state[state_index].घड़ी_info[0].sclk;
			rdev->pm.शेष_mclk = rdev->pm.घातer_state[state_index].घड़ी_info[0].mclk;
			rdev->pm.शेष_vddc = rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.voltage;
			rdev->pm.शेष_vddci = rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.vddci;
		पूर्ण अन्यथा अणु
			u16 max_vddci = 0;

			अगर (ASIC_IS_DCE4(rdev))
				radeon_atom_get_max_voltage(rdev,
							    SET_VOLTAGE_TYPE_ASIC_VDDCI,
							    &max_vddci);
			/* patch the table values with the शेष sclk/mclk from firmware info */
			क्रम (j = 0; j < mode_index; j++) अणु
				rdev->pm.घातer_state[state_index].घड़ी_info[j].mclk =
					rdev->घड़ी.शेष_mclk;
				rdev->pm.घातer_state[state_index].घड़ी_info[j].sclk =
					rdev->घड़ी.शेष_sclk;
				अगर (vddc)
					rdev->pm.घातer_state[state_index].घड़ी_info[j].voltage.voltage =
						vddc;
				अगर (max_vddci)
					rdev->pm.घातer_state[state_index].घड़ी_info[j].voltage.vddci =
						max_vddci;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल bool radeon_atombios_parse_pplib_घड़ी_info(काष्ठा radeon_device *rdev,
						   पूर्णांक state_index, पूर्णांक mode_index,
						   जोड़ pplib_घड़ी_info *घड़ी_info)
अणु
	u32 sclk, mclk;
	u16 vddc;

	अगर (rdev->flags & RADEON_IS_IGP) अणु
		अगर (rdev->family >= CHIP_PALM) अणु
			sclk = le16_to_cpu(घड़ी_info->sumo.usEngineClockLow);
			sclk |= घड़ी_info->sumo.ucEngineClockHigh << 16;
			rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].sclk = sclk;
		पूर्ण अन्यथा अणु
			sclk = le16_to_cpu(घड़ी_info->rs780.usLowEngineClockLow);
			sclk |= घड़ी_info->rs780.ucLowEngineClockHigh << 16;
			rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].sclk = sclk;
		पूर्ण
	पूर्ण अन्यथा अगर (rdev->family >= CHIP_BONAIRE) अणु
		sclk = le16_to_cpu(घड़ी_info->ci.usEngineClockLow);
		sclk |= घड़ी_info->ci.ucEngineClockHigh << 16;
		mclk = le16_to_cpu(घड़ी_info->ci.usMemoryClockLow);
		mclk |= घड़ी_info->ci.ucMemoryClockHigh << 16;
		rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].mclk = mclk;
		rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].sclk = sclk;
		rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].voltage.type =
			VOLTAGE_NONE;
	पूर्ण अन्यथा अगर (rdev->family >= CHIP_TAHITI) अणु
		sclk = le16_to_cpu(घड़ी_info->si.usEngineClockLow);
		sclk |= घड़ी_info->si.ucEngineClockHigh << 16;
		mclk = le16_to_cpu(घड़ी_info->si.usMemoryClockLow);
		mclk |= घड़ी_info->si.ucMemoryClockHigh << 16;
		rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].mclk = mclk;
		rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].sclk = sclk;
		rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].voltage.type =
			VOLTAGE_SW;
		rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].voltage.voltage =
			le16_to_cpu(घड़ी_info->si.usVDDC);
		rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].voltage.vddci =
			le16_to_cpu(घड़ी_info->si.usVDDCI);
	पूर्ण अन्यथा अगर (rdev->family >= CHIP_CEDAR) अणु
		sclk = le16_to_cpu(घड़ी_info->evergreen.usEngineClockLow);
		sclk |= घड़ी_info->evergreen.ucEngineClockHigh << 16;
		mclk = le16_to_cpu(घड़ी_info->evergreen.usMemoryClockLow);
		mclk |= घड़ी_info->evergreen.ucMemoryClockHigh << 16;
		rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].mclk = mclk;
		rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].sclk = sclk;
		rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].voltage.type =
			VOLTAGE_SW;
		rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].voltage.voltage =
			le16_to_cpu(घड़ी_info->evergreen.usVDDC);
		rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].voltage.vddci =
			le16_to_cpu(घड़ी_info->evergreen.usVDDCI);
	पूर्ण अन्यथा अणु
		sclk = le16_to_cpu(घड़ी_info->r600.usEngineClockLow);
		sclk |= घड़ी_info->r600.ucEngineClockHigh << 16;
		mclk = le16_to_cpu(घड़ी_info->r600.usMemoryClockLow);
		mclk |= घड़ी_info->r600.ucMemoryClockHigh << 16;
		rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].mclk = mclk;
		rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].sclk = sclk;
		rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].voltage.type =
			VOLTAGE_SW;
		rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].voltage.voltage =
			le16_to_cpu(घड़ी_info->r600.usVDDC);
	पूर्ण

	/* patch up vddc अगर necessary */
	चयन (rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].voltage.voltage) अणु
	हाल ATOM_VIRTUAL_VOLTAGE_ID0:
	हाल ATOM_VIRTUAL_VOLTAGE_ID1:
	हाल ATOM_VIRTUAL_VOLTAGE_ID2:
	हाल ATOM_VIRTUAL_VOLTAGE_ID3:
	हाल ATOM_VIRTUAL_VOLTAGE_ID4:
	हाल ATOM_VIRTUAL_VOLTAGE_ID5:
	हाल ATOM_VIRTUAL_VOLTAGE_ID6:
	हाल ATOM_VIRTUAL_VOLTAGE_ID7:
		अगर (radeon_atom_get_max_vddc(rdev, VOLTAGE_TYPE_VDDC,
					     rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].voltage.voltage,
					     &vddc) == 0)
			rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].voltage.voltage = vddc;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (rdev->flags & RADEON_IS_IGP) अणु
		/* skip invalid modes */
		अगर (rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].sclk == 0)
			वापस false;
	पूर्ण अन्यथा अणु
		/* skip invalid modes */
		अगर ((rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].mclk == 0) ||
		    (rdev->pm.घातer_state[state_index].घड़ी_info[mode_index].sclk == 0))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक radeon_atombios_parse_घातer_table_4_5(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	काष्ठा _ATOM_PPLIB_NONCLOCK_INFO *non_घड़ी_info;
	जोड़ pplib_घातer_state *घातer_state;
	पूर्णांक i, j;
	पूर्णांक state_index = 0, mode_index = 0;
	जोड़ pplib_घड़ी_info *घड़ी_info;
	bool valid;
	जोड़ घातer_info *घातer_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);
	u16 data_offset;
	u8 frev, crev;

	अगर (!atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset))
		वापस state_index;
	घातer_info = (जोड़ घातer_info *)(mode_info->atom_context->bios + data_offset);

	radeon_atombios_add_pplib_thermal_controller(rdev, &घातer_info->pplib.sThermalController);
	अगर (घातer_info->pplib.ucNumStates == 0)
		वापस state_index;
	rdev->pm.घातer_state = kसुस्मृति(घातer_info->pplib.ucNumStates,
				       माप(काष्ठा radeon_घातer_state),
				       GFP_KERNEL);
	अगर (!rdev->pm.घातer_state)
		वापस state_index;
	/* first mode is usually शेष, followed by low to high */
	क्रम (i = 0; i < घातer_info->pplib.ucNumStates; i++) अणु
		mode_index = 0;
		घातer_state = (जोड़ pplib_घातer_state *)
			(mode_info->atom_context->bios + data_offset +
			 le16_to_cpu(घातer_info->pplib.usStateArrayOffset) +
			 i * घातer_info->pplib.ucStateEntrySize);
		non_घड़ी_info = (काष्ठा _ATOM_PPLIB_NONCLOCK_INFO *)
			(mode_info->atom_context->bios + data_offset +
			 le16_to_cpu(घातer_info->pplib.usNonClockInfoArrayOffset) +
			 (घातer_state->v1.ucNonClockStateIndex *
			  घातer_info->pplib.ucNonClockSize));
		rdev->pm.घातer_state[i].घड़ी_info =
			kसुस्मृति((घातer_info->pplib.ucStateEntrySize - 1) ?
				(घातer_info->pplib.ucStateEntrySize - 1) : 1,
				माप(काष्ठा radeon_pm_घड़ी_info),
				GFP_KERNEL);
		अगर (!rdev->pm.घातer_state[i].घड़ी_info)
			वापस state_index;
		अगर (घातer_info->pplib.ucStateEntrySize - 1) अणु
			क्रम (j = 0; j < (घातer_info->pplib.ucStateEntrySize - 1); j++) अणु
				घड़ी_info = (जोड़ pplib_घड़ी_info *)
					(mode_info->atom_context->bios + data_offset +
					 le16_to_cpu(घातer_info->pplib.usClockInfoArrayOffset) +
					 (घातer_state->v1.ucClockStateIndices[j] *
					  घातer_info->pplib.ucClockInfoSize));
				valid = radeon_atombios_parse_pplib_घड़ी_info(rdev,
									       state_index, mode_index,
									       घड़ी_info);
				अगर (valid)
					mode_index++;
			पूर्ण
		पूर्ण अन्यथा अणु
			rdev->pm.घातer_state[state_index].घड़ी_info[0].mclk =
				rdev->घड़ी.शेष_mclk;
			rdev->pm.घातer_state[state_index].घड़ी_info[0].sclk =
				rdev->घड़ी.शेष_sclk;
			mode_index++;
		पूर्ण
		rdev->pm.घातer_state[state_index].num_घड़ी_modes = mode_index;
		अगर (mode_index) अणु
			radeon_atombios_parse_pplib_non_घड़ी_info(rdev, state_index, mode_index,
								   non_घड़ी_info);
			state_index++;
		पूर्ण
	पूर्ण
	/* अगर multiple घड़ी modes, mark the lowest as no display */
	क्रम (i = 0; i < state_index; i++) अणु
		अगर (rdev->pm.घातer_state[i].num_घड़ी_modes > 1)
			rdev->pm.घातer_state[i].घड़ी_info[0].flags |=
				RADEON_PM_MODE_NO_DISPLAY;
	पूर्ण
	/* first mode is usually शेष */
	अगर (rdev->pm.शेष_घातer_state_index == -1) अणु
		rdev->pm.घातer_state[0].type =
			POWER_STATE_TYPE_DEFAULT;
		rdev->pm.शेष_घातer_state_index = 0;
		rdev->pm.घातer_state[0].शेष_घड़ी_mode =
			&rdev->pm.घातer_state[0].घड़ी_info[0];
	पूर्ण
	वापस state_index;
पूर्ण

अटल पूर्णांक radeon_atombios_parse_घातer_table_6(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	काष्ठा _ATOM_PPLIB_NONCLOCK_INFO *non_घड़ी_info;
	जोड़ pplib_घातer_state *घातer_state;
	पूर्णांक i, j, non_घड़ी_array_index, घड़ी_array_index;
	पूर्णांक state_index = 0, mode_index = 0;
	जोड़ pplib_घड़ी_info *घड़ी_info;
	काष्ठा _StateArray *state_array;
	काष्ठा _ClockInfoArray *घड़ी_info_array;
	काष्ठा _NonClockInfoArray *non_घड़ी_info_array;
	bool valid;
	जोड़ घातer_info *घातer_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);
	u16 data_offset;
	u8 frev, crev;
	u8 *घातer_state_offset;

	अगर (!atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset))
		वापस state_index;
	घातer_info = (जोड़ घातer_info *)(mode_info->atom_context->bios + data_offset);

	radeon_atombios_add_pplib_thermal_controller(rdev, &घातer_info->pplib.sThermalController);
	state_array = (काष्ठा _StateArray *)
		(mode_info->atom_context->bios + data_offset +
		 le16_to_cpu(घातer_info->pplib.usStateArrayOffset));
	घड़ी_info_array = (काष्ठा _ClockInfoArray *)
		(mode_info->atom_context->bios + data_offset +
		 le16_to_cpu(घातer_info->pplib.usClockInfoArrayOffset));
	non_घड़ी_info_array = (काष्ठा _NonClockInfoArray *)
		(mode_info->atom_context->bios + data_offset +
		 le16_to_cpu(घातer_info->pplib.usNonClockInfoArrayOffset));
	अगर (state_array->ucNumEntries == 0)
		वापस state_index;
	rdev->pm.घातer_state = kसुस्मृति(state_array->ucNumEntries,
				       माप(काष्ठा radeon_घातer_state),
				       GFP_KERNEL);
	अगर (!rdev->pm.घातer_state)
		वापस state_index;
	घातer_state_offset = (u8 *)state_array->states;
	क्रम (i = 0; i < state_array->ucNumEntries; i++) अणु
		mode_index = 0;
		घातer_state = (जोड़ pplib_घातer_state *)घातer_state_offset;
		non_घड़ी_array_index = घातer_state->v2.nonClockInfoIndex;
		non_घड़ी_info = (काष्ठा _ATOM_PPLIB_NONCLOCK_INFO *)
			&non_घड़ी_info_array->nonClockInfo[non_घड़ी_array_index];
		rdev->pm.घातer_state[i].घड़ी_info =
			kसुस्मृति(घातer_state->v2.ucNumDPMLevels ?
				घातer_state->v2.ucNumDPMLevels : 1,
				माप(काष्ठा radeon_pm_घड़ी_info),
				GFP_KERNEL);
		अगर (!rdev->pm.घातer_state[i].घड़ी_info)
			वापस state_index;
		अगर (घातer_state->v2.ucNumDPMLevels) अणु
			क्रम (j = 0; j < घातer_state->v2.ucNumDPMLevels; j++) अणु
				घड़ी_array_index = घातer_state->v2.घड़ीInfoIndex[j];
				घड़ी_info = (जोड़ pplib_घड़ी_info *)
					&घड़ी_info_array->घड़ीInfo[घड़ी_array_index * घड़ी_info_array->ucEntrySize];
				valid = radeon_atombios_parse_pplib_घड़ी_info(rdev,
									       state_index, mode_index,
									       घड़ी_info);
				अगर (valid)
					mode_index++;
			पूर्ण
		पूर्ण अन्यथा अणु
			rdev->pm.घातer_state[state_index].घड़ी_info[0].mclk =
				rdev->घड़ी.शेष_mclk;
			rdev->pm.घातer_state[state_index].घड़ी_info[0].sclk =
				rdev->घड़ी.शेष_sclk;
			mode_index++;
		पूर्ण
		rdev->pm.घातer_state[state_index].num_घड़ी_modes = mode_index;
		अगर (mode_index) अणु
			radeon_atombios_parse_pplib_non_घड़ी_info(rdev, state_index, mode_index,
								   non_घड़ी_info);
			state_index++;
		पूर्ण
		घातer_state_offset += 2 + घातer_state->v2.ucNumDPMLevels;
	पूर्ण
	/* अगर multiple घड़ी modes, mark the lowest as no display */
	क्रम (i = 0; i < state_index; i++) अणु
		अगर (rdev->pm.घातer_state[i].num_घड़ी_modes > 1)
			rdev->pm.घातer_state[i].घड़ी_info[0].flags |=
				RADEON_PM_MODE_NO_DISPLAY;
	पूर्ण
	/* first mode is usually शेष */
	अगर (rdev->pm.शेष_घातer_state_index == -1) अणु
		rdev->pm.घातer_state[0].type =
			POWER_STATE_TYPE_DEFAULT;
		rdev->pm.शेष_घातer_state_index = 0;
		rdev->pm.घातer_state[0].शेष_घड़ी_mode =
			&rdev->pm.घातer_state[0].घड़ी_info[0];
	पूर्ण
	वापस state_index;
पूर्ण

व्योम radeon_atombios_get_घातer_modes(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);
	u16 data_offset;
	u8 frev, crev;
	पूर्णांक state_index = 0;

	rdev->pm.शेष_घातer_state_index = -1;

	अगर (atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset)) अणु
		चयन (frev) अणु
		हाल 1:
		हाल 2:
		हाल 3:
			state_index = radeon_atombios_parse_घातer_table_1_3(rdev);
			अवरोध;
		हाल 4:
		हाल 5:
			state_index = radeon_atombios_parse_घातer_table_4_5(rdev);
			अवरोध;
		हाल 6:
			state_index = radeon_atombios_parse_घातer_table_6(rdev);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (state_index == 0) अणु
		rdev->pm.घातer_state = kzalloc(माप(काष्ठा radeon_घातer_state), GFP_KERNEL);
		अगर (rdev->pm.घातer_state) अणु
			rdev->pm.घातer_state[0].घड़ी_info =
				kसुस्मृति(1,
				        माप(काष्ठा radeon_pm_घड़ी_info),
				        GFP_KERNEL);
			अगर (rdev->pm.घातer_state[0].घड़ी_info) अणु
				/* add the शेष mode */
				rdev->pm.घातer_state[state_index].type =
					POWER_STATE_TYPE_DEFAULT;
				rdev->pm.घातer_state[state_index].num_घड़ी_modes = 1;
				rdev->pm.घातer_state[state_index].घड़ी_info[0].mclk = rdev->घड़ी.शेष_mclk;
				rdev->pm.घातer_state[state_index].घड़ी_info[0].sclk = rdev->घड़ी.शेष_sclk;
				rdev->pm.घातer_state[state_index].शेष_घड़ी_mode =
					&rdev->pm.घातer_state[state_index].घड़ी_info[0];
				rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.type = VOLTAGE_NONE;
				rdev->pm.घातer_state[state_index].pcie_lanes = 16;
				rdev->pm.शेष_घातer_state_index = state_index;
				rdev->pm.घातer_state[state_index].flags = 0;
				state_index++;
			पूर्ण
		पूर्ण
	पूर्ण

	rdev->pm.num_घातer_states = state_index;

	rdev->pm.current_घातer_state_index = rdev->pm.शेष_घातer_state_index;
	rdev->pm.current_घड़ी_mode_index = 0;
	अगर (rdev->pm.शेष_घातer_state_index >= 0)
		rdev->pm.current_vddc =
			rdev->pm.घातer_state[rdev->pm.शेष_घातer_state_index].घड़ी_info[0].voltage.voltage;
	अन्यथा
		rdev->pm.current_vddc = 0;
पूर्ण

जोड़ get_घड़ी_भागiders अणु
	काष्ठा _COMPUTE_MEMORY_ENGINE_PLL_PARAMETERS v1;
	काष्ठा _COMPUTE_MEMORY_ENGINE_PLL_PARAMETERS_V2 v2;
	काष्ठा _COMPUTE_MEMORY_ENGINE_PLL_PARAMETERS_V3 v3;
	काष्ठा _COMPUTE_MEMORY_ENGINE_PLL_PARAMETERS_V4 v4;
	काष्ठा _COMPUTE_MEMORY_ENGINE_PLL_PARAMETERS_V5 v5;
	काष्ठा _COMPUTE_GPU_CLOCK_INPUT_PARAMETERS_V1_6 v6_in;
	काष्ठा _COMPUTE_GPU_CLOCK_OUTPUT_PARAMETERS_V1_6 v6_out;
पूर्ण;

पूर्णांक radeon_atom_get_घड़ी_भागiders(काष्ठा radeon_device *rdev,
				   u8 घड़ी_प्रकारype,
				   u32 घड़ी,
				   bool strobe_mode,
				   काष्ठा atom_घड़ी_भागiders *भागiders)
अणु
	जोड़ get_घड़ी_भागiders args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, ComputeMemoryEnginePLL);
	u8 frev, crev;

	स_रखो(&args, 0, माप(args));
	स_रखो(भागiders, 0, माप(काष्ठा atom_घड़ी_भागiders));

	अगर (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
		वापस -EINVAL;

	चयन (crev) अणु
	हाल 1:
		/* r4xx, r5xx */
		args.v1.ucAction = घड़ी_प्रकारype;
		args.v1.ulClock = cpu_to_le32(घड़ी);	/* 10 khz */

		atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

		भागiders->post_भाग = args.v1.ucPostDiv;
		भागiders->fb_भाग = args.v1.ucFbDiv;
		भागiders->enable_post_भाग = true;
		अवरोध;
	हाल 2:
	हाल 3:
	हाल 5:
		/* r6xx, r7xx, evergreen, ni, si */
		अगर (rdev->family <= CHIP_RV770) अणु
			args.v2.ucAction = घड़ी_प्रकारype;
			args.v2.ulClock = cpu_to_le32(घड़ी);	/* 10 khz */

			atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

			भागiders->post_भाग = args.v2.ucPostDiv;
			भागiders->fb_भाग = le16_to_cpu(args.v2.usFbDiv);
			भागiders->ref_भाग = args.v2.ucAction;
			अगर (rdev->family == CHIP_RV770) अणु
				भागiders->enable_post_भाग = (le32_to_cpu(args.v2.ulClock) & (1 << 24)) ?
					true : false;
				भागiders->vco_mode = (le32_to_cpu(args.v2.ulClock) & (1 << 25)) ? 1 : 0;
			पूर्ण अन्यथा
				भागiders->enable_post_भाग = (भागiders->fb_भाग & 1) ? true : false;
		पूर्ण अन्यथा अणु
			अगर (घड़ी_प्रकारype == COMPUTE_ENGINE_PLL_PARAM) अणु
				args.v3.ulClockParams = cpu_to_le32((घड़ी_प्रकारype << 24) | घड़ी);

				atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

				भागiders->post_भाग = args.v3.ucPostDiv;
				भागiders->enable_post_भाग = (args.v3.ucCntlFlag &
							     ATOM_PLL_CNTL_FLAG_PLL_POST_DIV_EN) ? true : false;
				भागiders->enable_dithen = (args.v3.ucCntlFlag &
							   ATOM_PLL_CNTL_FLAG_FRACTION_DISABLE) ? false : true;
				भागiders->whole_fb_भाग = le16_to_cpu(args.v3.ulFbDiv.usFbDiv);
				भागiders->frac_fb_भाग = le16_to_cpu(args.v3.ulFbDiv.usFbDivFrac);
				भागiders->ref_भाग = args.v3.ucRefDiv;
				भागiders->vco_mode = (args.v3.ucCntlFlag &
						      ATOM_PLL_CNTL_FLAG_MPLL_VCO_MODE) ? 1 : 0;
			पूर्ण अन्यथा अणु
				/* क्रम SI we use ComputeMemoryClockParam क्रम memory plls */
				अगर (rdev->family >= CHIP_TAHITI)
					वापस -EINVAL;
				args.v5.ulClockParams = cpu_to_le32((घड़ी_प्रकारype << 24) | घड़ी);
				अगर (strobe_mode)
					args.v5.ucInputFlag = ATOM_PLL_INPUT_FLAG_PLL_STROBE_MODE_EN;

				atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

				भागiders->post_भाग = args.v5.ucPostDiv;
				भागiders->enable_post_भाग = (args.v5.ucCntlFlag &
							     ATOM_PLL_CNTL_FLAG_PLL_POST_DIV_EN) ? true : false;
				भागiders->enable_dithen = (args.v5.ucCntlFlag &
							   ATOM_PLL_CNTL_FLAG_FRACTION_DISABLE) ? false : true;
				भागiders->whole_fb_भाग = le16_to_cpu(args.v5.ulFbDiv.usFbDiv);
				भागiders->frac_fb_भाग = le16_to_cpu(args.v5.ulFbDiv.usFbDivFrac);
				भागiders->ref_भाग = args.v5.ucRefDiv;
				भागiders->vco_mode = (args.v5.ucCntlFlag &
						      ATOM_PLL_CNTL_FLAG_MPLL_VCO_MODE) ? 1 : 0;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल 4:
		/* fusion */
		args.v4.ulClock = cpu_to_le32(घड़ी);	/* 10 khz */

		atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

		भागiders->post_भागider = भागiders->post_भाग = args.v4.ucPostDiv;
		भागiders->real_घड़ी = le32_to_cpu(args.v4.ulClock);
		अवरोध;
	हाल 6:
		/* CI */
		/* COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK, COMPUTE_GPUCLK_INPUT_FLAG_SCLK */
		args.v6_in.ulClock.ulComputeClockFlag = घड़ी_प्रकारype;
		args.v6_in.ulClock.ulClockFreq = cpu_to_le32(घड़ी);	/* 10 khz */

		atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

		भागiders->whole_fb_भाग = le16_to_cpu(args.v6_out.ulFbDiv.usFbDiv);
		भागiders->frac_fb_भाग = le16_to_cpu(args.v6_out.ulFbDiv.usFbDivFrac);
		भागiders->ref_भाग = args.v6_out.ucPllRefDiv;
		भागiders->post_भाग = args.v6_out.ucPllPostDiv;
		भागiders->flags = args.v6_out.ucPllCntlFlag;
		भागiders->real_घड़ी = le32_to_cpu(args.v6_out.ulClock.ulClock);
		भागiders->post_भागider = args.v6_out.ulClock.ucPostDiv;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक radeon_atom_get_memory_pll_भागiders(काष्ठा radeon_device *rdev,
					u32 घड़ी,
					bool strobe_mode,
					काष्ठा atom_mpll_param *mpll_param)
अणु
	COMPUTE_MEMORY_CLOCK_PARAM_PARAMETERS_V2_1 args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, ComputeMemoryClockParam);
	u8 frev, crev;

	स_रखो(&args, 0, माप(args));
	स_रखो(mpll_param, 0, माप(काष्ठा atom_mpll_param));

	अगर (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
		वापस -EINVAL;

	चयन (frev) अणु
	हाल 2:
		चयन (crev) अणु
		हाल 1:
			/* SI */
			args.ulClock = cpu_to_le32(घड़ी);	/* 10 khz */
			args.ucInputFlag = 0;
			अगर (strobe_mode)
				args.ucInputFlag |= MPLL_INPUT_FLAG_STROBE_MODE_EN;

			atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

			mpll_param->clkfrac = le16_to_cpu(args.ulFbDiv.usFbDivFrac);
			mpll_param->clkf = le16_to_cpu(args.ulFbDiv.usFbDiv);
			mpll_param->post_भाग = args.ucPostDiv;
			mpll_param->dll_speed = args.ucDllSpeed;
			mpll_param->bwcntl = args.ucBWCntl;
			mpll_param->vco_mode =
				(args.ucPllCntlFlag & MPLL_CNTL_FLAG_VCO_MODE_MASK);
			mpll_param->yclk_sel =
				(args.ucPllCntlFlag & MPLL_CNTL_FLAG_BYPASS_DQ_PLL) ? 1 : 0;
			mpll_param->qdr =
				(args.ucPllCntlFlag & MPLL_CNTL_FLAG_QDR_ENABLE) ? 1 : 0;
			mpll_param->half_rate =
				(args.ucPllCntlFlag & MPLL_CNTL_FLAG_AD_HALF_RATE) ? 1 : 0;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

व्योम radeon_atom_set_घड़ी_gating(काष्ठा radeon_device *rdev, पूर्णांक enable)
अणु
	DYNAMIC_CLOCK_GATING_PS_ALLOCATION args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, DynamicClockGating);

	args.ucEnable = enable;

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

uपूर्णांक32_t radeon_atom_get_engine_घड़ी(काष्ठा radeon_device *rdev)
अणु
	GET_ENGINE_CLOCK_PS_ALLOCATION args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, GetEngineClock);

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
	वापस le32_to_cpu(args.ulReturnEngineClock);
पूर्ण

uपूर्णांक32_t radeon_atom_get_memory_घड़ी(काष्ठा radeon_device *rdev)
अणु
	GET_MEMORY_CLOCK_PS_ALLOCATION args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, GetMemoryClock);

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
	वापस le32_to_cpu(args.ulReturnMemoryClock);
पूर्ण

व्योम radeon_atom_set_engine_घड़ी(काष्ठा radeon_device *rdev,
				  uपूर्णांक32_t eng_घड़ी)
अणु
	SET_ENGINE_CLOCK_PS_ALLOCATION args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, SetEngineClock);

	args.ulTargetEngineClock = cpu_to_le32(eng_घड़ी);	/* 10 khz */

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

व्योम radeon_atom_set_memory_घड़ी(काष्ठा radeon_device *rdev,
				  uपूर्णांक32_t mem_घड़ी)
अणु
	SET_MEMORY_CLOCK_PS_ALLOCATION args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, SetMemoryClock);

	अगर (rdev->flags & RADEON_IS_IGP)
		वापस;

	args.ulTargetMemoryClock = cpu_to_le32(mem_घड़ी);	/* 10 khz */

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

व्योम radeon_atom_set_engine_dram_timings(काष्ठा radeon_device *rdev,
					 u32 eng_घड़ी, u32 mem_घड़ी)
अणु
	SET_ENGINE_CLOCK_PS_ALLOCATION args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, DynamicMemorySettings);
	u32 पंचांगp;

	स_रखो(&args, 0, माप(args));

	पंचांगp = eng_घड़ी & SET_CLOCK_FREQ_MASK;
	पंचांगp |= (COMPUTE_ENGINE_PLL_PARAM << 24);

	args.ulTargetEngineClock = cpu_to_le32(पंचांगp);
	अगर (mem_घड़ी)
		args.sReserved.ulClock = cpu_to_le32(mem_घड़ी & SET_CLOCK_FREQ_MASK);

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

व्योम radeon_atom_update_memory_dll(काष्ठा radeon_device *rdev,
				   u32 mem_घड़ी)
अणु
	u32 args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, DynamicMemorySettings);

	args = cpu_to_le32(mem_घड़ी);	/* 10 khz */

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

व्योम radeon_atom_set_ac_timing(काष्ठा radeon_device *rdev,
			       u32 mem_घड़ी)
अणु
	SET_MEMORY_CLOCK_PS_ALLOCATION args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, DynamicMemorySettings);
	u32 पंचांगp = mem_घड़ी | (COMPUTE_MEMORY_PLL_PARAM << 24);

	args.ulTargetMemoryClock = cpu_to_le32(पंचांगp);	/* 10 khz */

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

जोड़ set_voltage अणु
	काष्ठा _SET_VOLTAGE_PS_ALLOCATION alloc;
	काष्ठा _SET_VOLTAGE_PARAMETERS v1;
	काष्ठा _SET_VOLTAGE_PARAMETERS_V2 v2;
	काष्ठा _SET_VOLTAGE_PARAMETERS_V1_3 v3;
पूर्ण;

व्योम radeon_atom_set_voltage(काष्ठा radeon_device *rdev, u16 voltage_level, u8 voltage_type)
अणु
	जोड़ set_voltage args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, SetVoltage);
	u8 frev, crev, volt_index = voltage_level;

	अगर (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
		वापस;

	/* 0xff01 is a flag rather then an actual voltage */
	अगर (voltage_level == 0xff01)
		वापस;

	चयन (crev) अणु
	हाल 1:
		args.v1.ucVoltageType = voltage_type;
		args.v1.ucVoltageMode = SET_ASIC_VOLTAGE_MODE_ALL_SOURCE;
		args.v1.ucVoltageIndex = volt_index;
		अवरोध;
	हाल 2:
		args.v2.ucVoltageType = voltage_type;
		args.v2.ucVoltageMode = SET_ASIC_VOLTAGE_MODE_SET_VOLTAGE;
		args.v2.usVoltageLevel = cpu_to_le16(voltage_level);
		अवरोध;
	हाल 3:
		args.v3.ucVoltageType = voltage_type;
		args.v3.ucVoltageMode = ATOM_SET_VOLTAGE;
		args.v3.usVoltageLevel = cpu_to_le16(voltage_level);
		अवरोध;
	शेष:
		DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
		वापस;
	पूर्ण

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

पूर्णांक radeon_atom_get_max_vddc(काष्ठा radeon_device *rdev, u8 voltage_type,
			     u16 voltage_id, u16 *voltage)
अणु
	जोड़ set_voltage args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, SetVoltage);
	u8 frev, crev;

	अगर (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
		वापस -EINVAL;

	चयन (crev) अणु
	हाल 1:
		वापस -EINVAL;
	हाल 2:
		args.v2.ucVoltageType = SET_VOLTAGE_GET_MAX_VOLTAGE;
		args.v2.ucVoltageMode = 0;
		args.v2.usVoltageLevel = 0;

		atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

		*voltage = le16_to_cpu(args.v2.usVoltageLevel);
		अवरोध;
	हाल 3:
		args.v3.ucVoltageType = voltage_type;
		args.v3.ucVoltageMode = ATOM_GET_VOLTAGE_LEVEL;
		args.v3.usVoltageLevel = cpu_to_le16(voltage_id);

		atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

		*voltage = le16_to_cpu(args.v3.usVoltageLevel);
		अवरोध;
	शेष:
		DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक radeon_atom_get_leakage_vddc_based_on_leakage_idx(काष्ठा radeon_device *rdev,
						      u16 *voltage,
						      u16 leakage_idx)
अणु
	वापस radeon_atom_get_max_vddc(rdev, VOLTAGE_TYPE_VDDC, leakage_idx, voltage);
पूर्ण

पूर्णांक radeon_atom_get_leakage_id_from_vbios(काष्ठा radeon_device *rdev,
					  u16 *leakage_id)
अणु
	जोड़ set_voltage args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, SetVoltage);
	u8 frev, crev;

	अगर (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
		वापस -EINVAL;

	चयन (crev) अणु
	हाल 3:
	हाल 4:
		args.v3.ucVoltageType = 0;
		args.v3.ucVoltageMode = ATOM_GET_LEAKAGE_ID;
		args.v3.usVoltageLevel = 0;

		atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

		*leakage_id = le16_to_cpu(args.v3.usVoltageLevel);
		अवरोध;
	शेष:
		DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक radeon_atom_get_leakage_vddc_based_on_leakage_params(काष्ठा radeon_device *rdev,
							 u16 *vddc, u16 *vddci,
							 u16 भव_voltage_id,
							 u16 vbios_voltage_id)
अणु
	पूर्णांक index = GetIndexIntoMasterTable(DATA, ASIC_ProfilingInfo);
	u8 frev, crev;
	u16 data_offset, size;
	पूर्णांक i, j;
	ATOM_ASIC_PROFILING_INFO_V2_1 *profile;
	u16 *leakage_bin, *vddc_id_buf, *vddc_buf, *vddci_id_buf, *vddci_buf;

	*vddc = 0;
	*vddci = 0;

	अगर (!atom_parse_data_header(rdev->mode_info.atom_context, index, &size,
				    &frev, &crev, &data_offset))
		वापस -EINVAL;

	profile = (ATOM_ASIC_PROFILING_INFO_V2_1 *)
		(rdev->mode_info.atom_context->bios + data_offset);

	चयन (frev) अणु
	हाल 1:
		वापस -EINVAL;
	हाल 2:
		चयन (crev) अणु
		हाल 1:
			अगर (size < माप(ATOM_ASIC_PROFILING_INFO_V2_1))
				वापस -EINVAL;
			leakage_bin = (u16 *)
				(rdev->mode_info.atom_context->bios + data_offset +
				 le16_to_cpu(profile->usLeakageBinArrayOffset));
			vddc_id_buf = (u16 *)
				(rdev->mode_info.atom_context->bios + data_offset +
				 le16_to_cpu(profile->usElbVDDC_IdArrayOffset));
			vddc_buf = (u16 *)
				(rdev->mode_info.atom_context->bios + data_offset +
				 le16_to_cpu(profile->usElbVDDC_LevelArrayOffset));
			vddci_id_buf = (u16 *)
				(rdev->mode_info.atom_context->bios + data_offset +
				 le16_to_cpu(profile->usElbVDDCI_IdArrayOffset));
			vddci_buf = (u16 *)
				(rdev->mode_info.atom_context->bios + data_offset +
				 le16_to_cpu(profile->usElbVDDCI_LevelArrayOffset));

			अगर (profile->ucElbVDDC_Num > 0) अणु
				क्रम (i = 0; i < profile->ucElbVDDC_Num; i++) अणु
					अगर (vddc_id_buf[i] == भव_voltage_id) अणु
						क्रम (j = 0; j < profile->ucLeakageBinNum; j++) अणु
							अगर (vbios_voltage_id <= leakage_bin[j]) अणु
								*vddc = vddc_buf[j * profile->ucElbVDDC_Num + i];
								अवरोध;
							पूर्ण
						पूर्ण
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
			अगर (profile->ucElbVDDCI_Num > 0) अणु
				क्रम (i = 0; i < profile->ucElbVDDCI_Num; i++) अणु
					अगर (vddci_id_buf[i] == भव_voltage_id) अणु
						क्रम (j = 0; j < profile->ucLeakageBinNum; j++) अणु
							अगर (vbios_voltage_id <= leakage_bin[j]) अणु
								*vddci = vddci_buf[j * profile->ucElbVDDCI_Num + i];
								अवरोध;
							पूर्ण
						पूर्ण
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
			अवरोध;
		शेष:
			DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

जोड़ get_voltage_info अणु
	काष्ठा  _GET_VOLTAGE_INFO_INPUT_PARAMETER_V1_2 in;
	काष्ठा  _GET_EVV_VOLTAGE_INFO_OUTPUT_PARAMETER_V1_2 evv_out;
पूर्ण;

पूर्णांक radeon_atom_get_voltage_evv(काष्ठा radeon_device *rdev,
				u16 भव_voltage_id,
				u16 *voltage)
अणु
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, GetVoltageInfo);
	u32 entry_id;
	u32 count = rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk.count;
	जोड़ get_voltage_info args;

	क्रम (entry_id = 0; entry_id < count; entry_id++) अणु
		अगर (rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries[entry_id].v ==
		    भव_voltage_id)
			अवरोध;
	पूर्ण

	अगर (entry_id >= count)
		वापस -EINVAL;

	args.in.ucVoltageType = VOLTAGE_TYPE_VDDC;
	args.in.ucVoltageMode = ATOM_GET_VOLTAGE_EVV_VOLTAGE;
	args.in.usVoltageLevel = cpu_to_le16(भव_voltage_id);
	args.in.ulSCLKFreq =
		cpu_to_le32(rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries[entry_id].clk);

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

	*voltage = le16_to_cpu(args.evv_out.usVoltageLevel);

	वापस 0;
पूर्ण

पूर्णांक radeon_atom_get_voltage_gpio_settings(काष्ठा radeon_device *rdev,
					  u16 voltage_level, u8 voltage_type,
					  u32 *gpio_value, u32 *gpio_mask)
अणु
	जोड़ set_voltage args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, SetVoltage);
	u8 frev, crev;

	अगर (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
		वापस -EINVAL;

	चयन (crev) अणु
	हाल 1:
		वापस -EINVAL;
	हाल 2:
		args.v2.ucVoltageType = voltage_type;
		args.v2.ucVoltageMode = SET_ASIC_VOLTAGE_MODE_GET_GPIOMASK;
		args.v2.usVoltageLevel = cpu_to_le16(voltage_level);

		atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

		*gpio_mask = le32_to_cpu(*(u32 *)&args.v2);

		args.v2.ucVoltageType = voltage_type;
		args.v2.ucVoltageMode = SET_ASIC_VOLTAGE_MODE_GET_GPIOVAL;
		args.v2.usVoltageLevel = cpu_to_le16(voltage_level);

		atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

		*gpio_value = le32_to_cpu(*(u32 *)&args.v2);
		अवरोध;
	शेष:
		DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

जोड़ voltage_object_info अणु
	काष्ठा _ATOM_VOLTAGE_OBJECT_INFO v1;
	काष्ठा _ATOM_VOLTAGE_OBJECT_INFO_V2 v2;
	काष्ठा _ATOM_VOLTAGE_OBJECT_INFO_V3_1 v3;
पूर्ण;

जोड़ voltage_object अणु
	काष्ठा _ATOM_VOLTAGE_OBJECT v1;
	काष्ठा _ATOM_VOLTAGE_OBJECT_V2 v2;
	जोड़ _ATOM_VOLTAGE_OBJECT_V3 v3;
पूर्ण;

अटल ATOM_VOLTAGE_OBJECT *atom_lookup_voltage_object_v1(ATOM_VOLTAGE_OBJECT_INFO *v1,
							  u8 voltage_type)
अणु
	u32 size = le16_to_cpu(v1->sHeader.usStructureSize);
	u32 offset = दुरत्व(ATOM_VOLTAGE_OBJECT_INFO, asVoltageObj[0]);
	u8 *start = (u8 *)v1;

	जबतक (offset < size) अणु
		ATOM_VOLTAGE_OBJECT *vo = (ATOM_VOLTAGE_OBJECT *)(start + offset);
		अगर (vo->ucVoltageType == voltage_type)
			वापस vo;
		offset += दुरत्व(ATOM_VOLTAGE_OBJECT, asFormula.ucVIDAdjustEntries) +
			vo->asFormula.ucNumOfVoltageEntries;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल ATOM_VOLTAGE_OBJECT_V2 *atom_lookup_voltage_object_v2(ATOM_VOLTAGE_OBJECT_INFO_V2 *v2,
							     u8 voltage_type)
अणु
	u32 size = le16_to_cpu(v2->sHeader.usStructureSize);
	u32 offset = दुरत्व(ATOM_VOLTAGE_OBJECT_INFO_V2, asVoltageObj[0]);
	u8 *start = (u8*)v2;

	जबतक (offset < size) अणु
		ATOM_VOLTAGE_OBJECT_V2 *vo = (ATOM_VOLTAGE_OBJECT_V2 *)(start + offset);
		अगर (vo->ucVoltageType == voltage_type)
			वापस vo;
		offset += दुरत्व(ATOM_VOLTAGE_OBJECT_V2, asFormula.asVIDAdjustEntries) +
			(vo->asFormula.ucNumOfVoltageEntries * माप(VOLTAGE_LUT_ENTRY));
	पूर्ण
	वापस शून्य;
पूर्ण

अटल ATOM_VOLTAGE_OBJECT_V3 *atom_lookup_voltage_object_v3(ATOM_VOLTAGE_OBJECT_INFO_V3_1 *v3,
							     u8 voltage_type, u8 voltage_mode)
अणु
	u32 size = le16_to_cpu(v3->sHeader.usStructureSize);
	u32 offset = दुरत्व(ATOM_VOLTAGE_OBJECT_INFO_V3_1, asVoltageObj[0]);
	u8 *start = (u8*)v3;

	जबतक (offset < size) अणु
		ATOM_VOLTAGE_OBJECT_V3 *vo = (ATOM_VOLTAGE_OBJECT_V3 *)(start + offset);
		अगर ((vo->asGpioVoltageObj.sHeader.ucVoltageType == voltage_type) &&
		    (vo->asGpioVoltageObj.sHeader.ucVoltageMode == voltage_mode))
			वापस vo;
		offset += le16_to_cpu(vo->asGpioVoltageObj.sHeader.usSize);
	पूर्ण
	वापस शून्य;
पूर्ण

bool
radeon_atom_is_voltage_gpio(काष्ठा radeon_device *rdev,
			    u8 voltage_type, u8 voltage_mode)
अणु
	पूर्णांक index = GetIndexIntoMasterTable(DATA, VoltageObjectInfo);
	u8 frev, crev;
	u16 data_offset, size;
	जोड़ voltage_object_info *voltage_info;
	जोड़ voltage_object *voltage_object = शून्य;

	अगर (atom_parse_data_header(rdev->mode_info.atom_context, index, &size,
				   &frev, &crev, &data_offset)) अणु
		voltage_info = (जोड़ voltage_object_info *)
			(rdev->mode_info.atom_context->bios + data_offset);

		चयन (frev) अणु
		हाल 1:
		हाल 2:
			चयन (crev) अणु
			हाल 1:
				voltage_object = (जोड़ voltage_object *)
					atom_lookup_voltage_object_v1(&voltage_info->v1, voltage_type);
				अगर (voltage_object &&
				    (voltage_object->v1.asControl.ucVoltageControlId == VOLTAGE_CONTROLLED_BY_GPIO))
					वापस true;
				अवरोध;
			हाल 2:
				voltage_object = (जोड़ voltage_object *)
					atom_lookup_voltage_object_v2(&voltage_info->v2, voltage_type);
				अगर (voltage_object &&
				    (voltage_object->v2.asControl.ucVoltageControlId == VOLTAGE_CONTROLLED_BY_GPIO))
					वापस true;
				अवरोध;
			शेष:
				DRM_ERROR("unknown voltage object table\n");
				वापस false;
			पूर्ण
			अवरोध;
		हाल 3:
			चयन (crev) अणु
			हाल 1:
				अगर (atom_lookup_voltage_object_v3(&voltage_info->v3,
								  voltage_type, voltage_mode))
					वापस true;
				अवरोध;
			शेष:
				DRM_ERROR("unknown voltage object table\n");
				वापस false;
			पूर्ण
			अवरोध;
		शेष:
			DRM_ERROR("unknown voltage object table\n");
			वापस false;
		पूर्ण

	पूर्ण
	वापस false;
पूर्ण

पूर्णांक radeon_atom_get_svi2_info(काष्ठा radeon_device *rdev,
			      u8 voltage_type,
			      u8 *svd_gpio_id, u8 *svc_gpio_id)
अणु
	पूर्णांक index = GetIndexIntoMasterTable(DATA, VoltageObjectInfo);
	u8 frev, crev;
	u16 data_offset, size;
	जोड़ voltage_object_info *voltage_info;
	जोड़ voltage_object *voltage_object = शून्य;

	अगर (atom_parse_data_header(rdev->mode_info.atom_context, index, &size,
				   &frev, &crev, &data_offset)) अणु
		voltage_info = (जोड़ voltage_object_info *)
			(rdev->mode_info.atom_context->bios + data_offset);

		चयन (frev) अणु
		हाल 3:
			चयन (crev) अणु
			हाल 1:
				voltage_object = (जोड़ voltage_object *)
					atom_lookup_voltage_object_v3(&voltage_info->v3,
								      voltage_type,
								      VOLTAGE_OBJ_SVID2);
				अगर (voltage_object) अणु
					*svd_gpio_id = voltage_object->v3.asSVID2Obj.ucSVDGpioId;
					*svc_gpio_id = voltage_object->v3.asSVID2Obj.ucSVCGpioId;
				पूर्ण अन्यथा अणु
					वापस -EINVAL;
				पूर्ण
				अवरोध;
			शेष:
				DRM_ERROR("unknown voltage object table\n");
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		शेष:
			DRM_ERROR("unknown voltage object table\n");
			वापस -EINVAL;
		पूर्ण

	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक radeon_atom_get_max_voltage(काष्ठा radeon_device *rdev,
				u8 voltage_type, u16 *max_voltage)
अणु
	पूर्णांक index = GetIndexIntoMasterTable(DATA, VoltageObjectInfo);
	u8 frev, crev;
	u16 data_offset, size;
	जोड़ voltage_object_info *voltage_info;
	जोड़ voltage_object *voltage_object = शून्य;

	अगर (atom_parse_data_header(rdev->mode_info.atom_context, index, &size,
				   &frev, &crev, &data_offset)) अणु
		voltage_info = (जोड़ voltage_object_info *)
			(rdev->mode_info.atom_context->bios + data_offset);

		चयन (crev) अणु
		हाल 1:
			voltage_object = (जोड़ voltage_object *)
				atom_lookup_voltage_object_v1(&voltage_info->v1, voltage_type);
			अगर (voltage_object) अणु
				ATOM_VOLTAGE_FORMULA *क्रमmula =
					&voltage_object->v1.asFormula;
				अगर (क्रमmula->ucFlag & 1)
					*max_voltage =
						le16_to_cpu(क्रमmula->usVoltageBaseLevel) +
						क्रमmula->ucNumOfVoltageEntries / 2 *
						le16_to_cpu(क्रमmula->usVoltageStep);
				अन्यथा
					*max_voltage =
						le16_to_cpu(क्रमmula->usVoltageBaseLevel) +
						(क्रमmula->ucNumOfVoltageEntries - 1) *
						le16_to_cpu(क्रमmula->usVoltageStep);
				वापस 0;
			पूर्ण
			अवरोध;
		हाल 2:
			voltage_object = (जोड़ voltage_object *)
				atom_lookup_voltage_object_v2(&voltage_info->v2, voltage_type);
			अगर (voltage_object) अणु
				ATOM_VOLTAGE_FORMULA_V2 *क्रमmula =
					&voltage_object->v2.asFormula;
				अगर (क्रमmula->ucNumOfVoltageEntries) अणु
					VOLTAGE_LUT_ENTRY *lut = (VOLTAGE_LUT_ENTRY *)
						((u8 *)&क्रमmula->asVIDAdjustEntries[0] +
						 (माप(VOLTAGE_LUT_ENTRY) * (क्रमmula->ucNumOfVoltageEntries - 1)));
					*max_voltage =
						le16_to_cpu(lut->usVoltageValue);
					वापस 0;
				पूर्ण
			पूर्ण
			अवरोध;
		शेष:
			DRM_ERROR("unknown voltage object table\n");
			वापस -EINVAL;
		पूर्ण

	पूर्ण
	वापस -EINVAL;
पूर्ण

पूर्णांक radeon_atom_get_min_voltage(काष्ठा radeon_device *rdev,
				u8 voltage_type, u16 *min_voltage)
अणु
	पूर्णांक index = GetIndexIntoMasterTable(DATA, VoltageObjectInfo);
	u8 frev, crev;
	u16 data_offset, size;
	जोड़ voltage_object_info *voltage_info;
	जोड़ voltage_object *voltage_object = शून्य;

	अगर (atom_parse_data_header(rdev->mode_info.atom_context, index, &size,
				   &frev, &crev, &data_offset)) अणु
		voltage_info = (जोड़ voltage_object_info *)
			(rdev->mode_info.atom_context->bios + data_offset);

		चयन (crev) अणु
		हाल 1:
			voltage_object = (जोड़ voltage_object *)
				atom_lookup_voltage_object_v1(&voltage_info->v1, voltage_type);
			अगर (voltage_object) अणु
				ATOM_VOLTAGE_FORMULA *क्रमmula =
					&voltage_object->v1.asFormula;
				*min_voltage =
					le16_to_cpu(क्रमmula->usVoltageBaseLevel);
				वापस 0;
			पूर्ण
			अवरोध;
		हाल 2:
			voltage_object = (जोड़ voltage_object *)
				atom_lookup_voltage_object_v2(&voltage_info->v2, voltage_type);
			अगर (voltage_object) अणु
				ATOM_VOLTAGE_FORMULA_V2 *क्रमmula =
					&voltage_object->v2.asFormula;
				अगर (क्रमmula->ucNumOfVoltageEntries) अणु
					*min_voltage =
						le16_to_cpu(क्रमmula->asVIDAdjustEntries[
								    0
								    ].usVoltageValue);
					वापस 0;
				पूर्ण
			पूर्ण
			अवरोध;
		शेष:
			DRM_ERROR("unknown voltage object table\n");
			वापस -EINVAL;
		पूर्ण

	पूर्ण
	वापस -EINVAL;
पूर्ण

पूर्णांक radeon_atom_get_voltage_step(काष्ठा radeon_device *rdev,
				 u8 voltage_type, u16 *voltage_step)
अणु
	पूर्णांक index = GetIndexIntoMasterTable(DATA, VoltageObjectInfo);
	u8 frev, crev;
	u16 data_offset, size;
	जोड़ voltage_object_info *voltage_info;
	जोड़ voltage_object *voltage_object = शून्य;

	अगर (atom_parse_data_header(rdev->mode_info.atom_context, index, &size,
				   &frev, &crev, &data_offset)) अणु
		voltage_info = (जोड़ voltage_object_info *)
			(rdev->mode_info.atom_context->bios + data_offset);

		चयन (crev) अणु
		हाल 1:
			voltage_object = (जोड़ voltage_object *)
				atom_lookup_voltage_object_v1(&voltage_info->v1, voltage_type);
			अगर (voltage_object) अणु
				ATOM_VOLTAGE_FORMULA *क्रमmula =
					&voltage_object->v1.asFormula;
				अगर (क्रमmula->ucFlag & 1)
					*voltage_step =
						(le16_to_cpu(क्रमmula->usVoltageStep) + 1) / 2;
				अन्यथा
					*voltage_step =
						le16_to_cpu(क्रमmula->usVoltageStep);
				वापस 0;
			पूर्ण
			अवरोध;
		हाल 2:
			वापस -EINVAL;
		शेष:
			DRM_ERROR("unknown voltage object table\n");
			वापस -EINVAL;
		पूर्ण

	पूर्ण
	वापस -EINVAL;
पूर्ण

पूर्णांक radeon_atom_round_to_true_voltage(काष्ठा radeon_device *rdev,
				      u8 voltage_type,
				      u16 nominal_voltage,
				      u16 *true_voltage)
अणु
	u16 min_voltage, max_voltage, voltage_step;

	अगर (radeon_atom_get_max_voltage(rdev, voltage_type, &max_voltage))
		वापस -EINVAL;
	अगर (radeon_atom_get_min_voltage(rdev, voltage_type, &min_voltage))
		वापस -EINVAL;
	अगर (radeon_atom_get_voltage_step(rdev, voltage_type, &voltage_step))
		वापस -EINVAL;

	अगर (nominal_voltage <= min_voltage)
		*true_voltage = min_voltage;
	अन्यथा अगर (nominal_voltage >= max_voltage)
		*true_voltage = max_voltage;
	अन्यथा
		*true_voltage = min_voltage +
			((nominal_voltage - min_voltage) / voltage_step) *
			voltage_step;

	वापस 0;
पूर्ण

पूर्णांक radeon_atom_get_voltage_table(काष्ठा radeon_device *rdev,
				  u8 voltage_type, u8 voltage_mode,
				  काष्ठा atom_voltage_table *voltage_table)
अणु
	पूर्णांक index = GetIndexIntoMasterTable(DATA, VoltageObjectInfo);
	u8 frev, crev;
	u16 data_offset, size;
	पूर्णांक i, ret;
	जोड़ voltage_object_info *voltage_info;
	जोड़ voltage_object *voltage_object = शून्य;

	अगर (atom_parse_data_header(rdev->mode_info.atom_context, index, &size,
				   &frev, &crev, &data_offset)) अणु
		voltage_info = (जोड़ voltage_object_info *)
			(rdev->mode_info.atom_context->bios + data_offset);

		चयन (frev) अणु
		हाल 1:
		हाल 2:
			चयन (crev) अणु
			हाल 1:
				DRM_ERROR("old table version %d, %d\n", frev, crev);
				वापस -EINVAL;
			हाल 2:
				voltage_object = (जोड़ voltage_object *)
					atom_lookup_voltage_object_v2(&voltage_info->v2, voltage_type);
				अगर (voltage_object) अणु
					ATOM_VOLTAGE_FORMULA_V2 *क्रमmula =
						&voltage_object->v2.asFormula;
					VOLTAGE_LUT_ENTRY *lut;
					अगर (क्रमmula->ucNumOfVoltageEntries > MAX_VOLTAGE_ENTRIES)
						वापस -EINVAL;
					lut = &क्रमmula->asVIDAdjustEntries[0];
					क्रम (i = 0; i < क्रमmula->ucNumOfVoltageEntries; i++) अणु
						voltage_table->entries[i].value =
							le16_to_cpu(lut->usVoltageValue);
						ret = radeon_atom_get_voltage_gpio_settings(rdev,
											    voltage_table->entries[i].value,
											    voltage_type,
											    &voltage_table->entries[i].smio_low,
											    &voltage_table->mask_low);
						अगर (ret)
							वापस ret;
						lut = (VOLTAGE_LUT_ENTRY *)
							((u8 *)lut + माप(VOLTAGE_LUT_ENTRY));
					पूर्ण
					voltage_table->count = क्रमmula->ucNumOfVoltageEntries;
					वापस 0;
				पूर्ण
				अवरोध;
			शेष:
				DRM_ERROR("unknown voltage object table\n");
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल 3:
			चयन (crev) अणु
			हाल 1:
				voltage_object = (जोड़ voltage_object *)
					atom_lookup_voltage_object_v3(&voltage_info->v3,
								      voltage_type, voltage_mode);
				अगर (voltage_object) अणु
					ATOM_GPIO_VOLTAGE_OBJECT_V3 *gpio =
						&voltage_object->v3.asGpioVoltageObj;
					VOLTAGE_LUT_ENTRY_V2 *lut;
					अगर (gpio->ucGpioEntryNum > MAX_VOLTAGE_ENTRIES)
						वापस -EINVAL;
					lut = &gpio->asVolGpioLut[0];
					क्रम (i = 0; i < gpio->ucGpioEntryNum; i++) अणु
						voltage_table->entries[i].value =
							le16_to_cpu(lut->usVoltageValue);
						voltage_table->entries[i].smio_low =
							le32_to_cpu(lut->ulVoltageId);
						lut = (VOLTAGE_LUT_ENTRY_V2 *)
							((u8 *)lut + माप(VOLTAGE_LUT_ENTRY_V2));
					पूर्ण
					voltage_table->mask_low = le32_to_cpu(gpio->ulGpioMaskVal);
					voltage_table->count = gpio->ucGpioEntryNum;
					voltage_table->phase_delay = gpio->ucPhaseDelay;
					वापस 0;
				पूर्ण
				अवरोध;
			शेष:
				DRM_ERROR("unknown voltage object table\n");
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		शेष:
			DRM_ERROR("unknown voltage object table\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

जोड़ vram_info अणु
	काष्ठा _ATOM_VRAM_INFO_V3 v1_3;
	काष्ठा _ATOM_VRAM_INFO_V4 v1_4;
	काष्ठा _ATOM_VRAM_INFO_HEADER_V2_1 v2_1;
पूर्ण;

पूर्णांक radeon_atom_get_memory_info(काष्ठा radeon_device *rdev,
				u8 module_index, काष्ठा atom_memory_info *mem_info)
अणु
	पूर्णांक index = GetIndexIntoMasterTable(DATA, VRAM_Info);
	u8 frev, crev, i;
	u16 data_offset, size;
	जोड़ vram_info *vram_info;

	स_रखो(mem_info, 0, माप(काष्ठा atom_memory_info));

	अगर (atom_parse_data_header(rdev->mode_info.atom_context, index, &size,
				   &frev, &crev, &data_offset)) अणु
		vram_info = (जोड़ vram_info *)
			(rdev->mode_info.atom_context->bios + data_offset);
		चयन (frev) अणु
		हाल 1:
			चयन (crev) अणु
			हाल 3:
				/* r6xx */
				अगर (module_index < vram_info->v1_3.ucNumOfVRAMModule) अणु
					ATOM_VRAM_MODULE_V3 *vram_module =
						(ATOM_VRAM_MODULE_V3 *)vram_info->v1_3.aVramInfo;

					क्रम (i = 0; i < module_index; i++) अणु
						अगर (le16_to_cpu(vram_module->usSize) == 0)
							वापस -EINVAL;
						vram_module = (ATOM_VRAM_MODULE_V3 *)
							((u8 *)vram_module + le16_to_cpu(vram_module->usSize));
					पूर्ण
					mem_info->mem_venकरोr = vram_module->asMemory.ucMemoryVenderID & 0xf;
					mem_info->mem_type = vram_module->asMemory.ucMemoryType & 0xf0;
				पूर्ण अन्यथा
					वापस -EINVAL;
				अवरोध;
			हाल 4:
				/* r7xx, evergreen */
				अगर (module_index < vram_info->v1_4.ucNumOfVRAMModule) अणु
					ATOM_VRAM_MODULE_V4 *vram_module =
						(ATOM_VRAM_MODULE_V4 *)vram_info->v1_4.aVramInfo;

					क्रम (i = 0; i < module_index; i++) अणु
						अगर (le16_to_cpu(vram_module->usModuleSize) == 0)
							वापस -EINVAL;
						vram_module = (ATOM_VRAM_MODULE_V4 *)
							((u8 *)vram_module + le16_to_cpu(vram_module->usModuleSize));
					पूर्ण
					mem_info->mem_venकरोr = vram_module->ucMemoryVenderID & 0xf;
					mem_info->mem_type = vram_module->ucMemoryType & 0xf0;
				पूर्ण अन्यथा
					वापस -EINVAL;
				अवरोध;
			शेष:
				DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल 2:
			चयन (crev) अणु
			हाल 1:
				/* ni */
				अगर (module_index < vram_info->v2_1.ucNumOfVRAMModule) अणु
					ATOM_VRAM_MODULE_V7 *vram_module =
						(ATOM_VRAM_MODULE_V7 *)vram_info->v2_1.aVramInfo;

					क्रम (i = 0; i < module_index; i++) अणु
						अगर (le16_to_cpu(vram_module->usModuleSize) == 0)
							वापस -EINVAL;
						vram_module = (ATOM_VRAM_MODULE_V7 *)
							((u8 *)vram_module + le16_to_cpu(vram_module->usModuleSize));
					पूर्ण
					mem_info->mem_venकरोr = vram_module->ucMemoryVenderID & 0xf;
					mem_info->mem_type = vram_module->ucMemoryType & 0xf0;
				पूर्ण अन्यथा
					वापस -EINVAL;
				अवरोध;
			शेष:
				DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		शेष:
			DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

पूर्णांक radeon_atom_get_mclk_range_table(काष्ठा radeon_device *rdev,
				     bool gddr5, u8 module_index,
				     काष्ठा atom_memory_घड़ी_range_table *mclk_range_table)
अणु
	पूर्णांक index = GetIndexIntoMasterTable(DATA, VRAM_Info);
	u8 frev, crev, i;
	u16 data_offset, size;
	जोड़ vram_info *vram_info;
	u32 mem_timing_size = gddr5 ?
		माप(ATOM_MEMORY_TIMING_FORMAT_V2) : माप(ATOM_MEMORY_TIMING_FORMAT);

	स_रखो(mclk_range_table, 0, माप(काष्ठा atom_memory_घड़ी_range_table));

	अगर (atom_parse_data_header(rdev->mode_info.atom_context, index, &size,
				   &frev, &crev, &data_offset)) अणु
		vram_info = (जोड़ vram_info *)
			(rdev->mode_info.atom_context->bios + data_offset);
		चयन (frev) अणु
		हाल 1:
			चयन (crev) अणु
			हाल 3:
				DRM_ERROR("old table version %d, %d\n", frev, crev);
				वापस -EINVAL;
			हाल 4:
				/* r7xx, evergreen */
				अगर (module_index < vram_info->v1_4.ucNumOfVRAMModule) अणु
					ATOM_VRAM_MODULE_V4 *vram_module =
						(ATOM_VRAM_MODULE_V4 *)vram_info->v1_4.aVramInfo;
					ATOM_MEMORY_TIMING_FORMAT *क्रमmat;

					क्रम (i = 0; i < module_index; i++) अणु
						अगर (le16_to_cpu(vram_module->usModuleSize) == 0)
							वापस -EINVAL;
						vram_module = (ATOM_VRAM_MODULE_V4 *)
							((u8 *)vram_module + le16_to_cpu(vram_module->usModuleSize));
					पूर्ण
					mclk_range_table->num_entries = (u8)
						((le16_to_cpu(vram_module->usModuleSize) - दुरत्व(ATOM_VRAM_MODULE_V4, asMemTiming)) /
						 mem_timing_size);
					क्रमmat = &vram_module->asMemTiming[0];
					क्रम (i = 0; i < mclk_range_table->num_entries; i++) अणु
						mclk_range_table->mclk[i] = le32_to_cpu(क्रमmat->ulClkRange);
						क्रमmat = (ATOM_MEMORY_TIMING_FORMAT *)
							((u8 *)क्रमmat + mem_timing_size);
					पूर्ण
				पूर्ण अन्यथा
					वापस -EINVAL;
				अवरोध;
			शेष:
				DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल 2:
			DRM_ERROR("new table version %d, %d\n", frev, crev);
			वापस -EINVAL;
		शेष:
			DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

#घोषणा MEM_ID_MASK           0xff000000
#घोषणा MEM_ID_SHIFT          24
#घोषणा CLOCK_RANGE_MASK      0x00ffffff
#घोषणा CLOCK_RANGE_SHIFT     0
#घोषणा LOW_NIBBLE_MASK       0xf
#घोषणा DATA_EQU_PREV         0
#घोषणा DATA_FROM_TABLE       4

पूर्णांक radeon_atom_init_mc_reg_table(काष्ठा radeon_device *rdev,
				  u8 module_index,
				  काष्ठा atom_mc_reg_table *reg_table)
अणु
	पूर्णांक index = GetIndexIntoMasterTable(DATA, VRAM_Info);
	u8 frev, crev, num_entries, t_mem_id, num_ranges = 0;
	u32 i = 0, j;
	u16 data_offset, size;
	जोड़ vram_info *vram_info;

	स_रखो(reg_table, 0, माप(काष्ठा atom_mc_reg_table));

	अगर (atom_parse_data_header(rdev->mode_info.atom_context, index, &size,
				   &frev, &crev, &data_offset)) अणु
		vram_info = (जोड़ vram_info *)
			(rdev->mode_info.atom_context->bios + data_offset);
		चयन (frev) अणु
		हाल 1:
			DRM_ERROR("old table version %d, %d\n", frev, crev);
			वापस -EINVAL;
		हाल 2:
			चयन (crev) अणु
			हाल 1:
				अगर (module_index < vram_info->v2_1.ucNumOfVRAMModule) अणु
					ATOM_INIT_REG_BLOCK *reg_block =
						(ATOM_INIT_REG_BLOCK *)
						((u8 *)vram_info + le16_to_cpu(vram_info->v2_1.usMemClkPatchTblOffset));
					ATOM_MEMORY_SETTING_DATA_BLOCK *reg_data =
						(ATOM_MEMORY_SETTING_DATA_BLOCK *)
						((u8 *)reg_block + (2 * माप(u16)) +
						 le16_to_cpu(reg_block->usRegIndexTblSize));
					ATOM_INIT_REG_INDEX_FORMAT *क्रमmat = &reg_block->asRegIndexBuf[0];
					num_entries = (u8)((le16_to_cpu(reg_block->usRegIndexTblSize)) /
							   माप(ATOM_INIT_REG_INDEX_FORMAT)) - 1;
					अगर (num_entries > VBIOS_MC_REGISTER_ARRAY_SIZE)
						वापस -EINVAL;
					जबतक (i < num_entries) अणु
						अगर (क्रमmat->ucPreRegDataLength & ACCESS_PLACEHOLDER)
							अवरोध;
						reg_table->mc_reg_address[i].s1 =
							(u16)(le16_to_cpu(क्रमmat->usRegIndex));
						reg_table->mc_reg_address[i].pre_reg_data =
							(u8)(क्रमmat->ucPreRegDataLength);
						i++;
						क्रमmat = (ATOM_INIT_REG_INDEX_FORMAT *)
							((u8 *)क्रमmat + माप(ATOM_INIT_REG_INDEX_FORMAT));
					पूर्ण
					reg_table->last = i;
					जबतक ((le32_to_cpu(*(u32 *)reg_data) != END_OF_REG_DATA_BLOCK) &&
					       (num_ranges < VBIOS_MAX_AC_TIMING_ENTRIES)) अणु
						t_mem_id = (u8)((le32_to_cpu(*(u32 *)reg_data) & MEM_ID_MASK)
								>> MEM_ID_SHIFT);
						अगर (module_index == t_mem_id) अणु
							reg_table->mc_reg_table_entry[num_ranges].mclk_max =
								(u32)((le32_to_cpu(*(u32 *)reg_data) & CLOCK_RANGE_MASK)
								      >> CLOCK_RANGE_SHIFT);
							क्रम (i = 0, j = 1; i < reg_table->last; i++) अणु
								अगर ((reg_table->mc_reg_address[i].pre_reg_data & LOW_NIBBLE_MASK) == DATA_FROM_TABLE) अणु
									reg_table->mc_reg_table_entry[num_ranges].mc_data[i] =
										(u32)le32_to_cpu(*((u32 *)reg_data + j));
									j++;
								पूर्ण अन्यथा अगर ((reg_table->mc_reg_address[i].pre_reg_data & LOW_NIBBLE_MASK) == DATA_EQU_PREV) अणु
									reg_table->mc_reg_table_entry[num_ranges].mc_data[i] =
										reg_table->mc_reg_table_entry[num_ranges].mc_data[i - 1];
								पूर्ण
							पूर्ण
							num_ranges++;
						पूर्ण
						reg_data = (ATOM_MEMORY_SETTING_DATA_BLOCK *)
							((u8 *)reg_data + le16_to_cpu(reg_block->usRegDataBlkSize));
					पूर्ण
					अगर (le32_to_cpu(*(u32 *)reg_data) != END_OF_REG_DATA_BLOCK)
						वापस -EINVAL;
					reg_table->num_entries = num_ranges;
				पूर्ण अन्यथा
					वापस -EINVAL;
				अवरोध;
			शेष:
				DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		शेष:
			DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

व्योम radeon_atom_initialize_bios_scratch_regs(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t bios_2_scratch, bios_6_scratch;

	अगर (rdev->family >= CHIP_R600) अणु
		bios_2_scratch = RREG32(R600_BIOS_2_SCRATCH);
		bios_6_scratch = RREG32(R600_BIOS_6_SCRATCH);
	पूर्ण अन्यथा अणु
		bios_2_scratch = RREG32(RADEON_BIOS_2_SCRATCH);
		bios_6_scratch = RREG32(RADEON_BIOS_6_SCRATCH);
	पूर्ण

	/* let the bios control the backlight */
	bios_2_scratch &= ~ATOM_S2_VRI_BRIGHT_ENABLE;

	/* tell the bios not to handle mode चयनing */
	bios_6_scratch |= ATOM_S6_ACC_BLOCK_DISPLAY_SWITCH;

	/* clear the vbios dpms state */
	अगर (ASIC_IS_DCE4(rdev))
		bios_2_scratch &= ~ATOM_S2_DEVICE_DPMS_STATE;

	अगर (rdev->family >= CHIP_R600) अणु
		WREG32(R600_BIOS_2_SCRATCH, bios_2_scratch);
		WREG32(R600_BIOS_6_SCRATCH, bios_6_scratch);
	पूर्ण अन्यथा अणु
		WREG32(RADEON_BIOS_2_SCRATCH, bios_2_scratch);
		WREG32(RADEON_BIOS_6_SCRATCH, bios_6_scratch);
	पूर्ण

पूर्ण

व्योम radeon_save_bios_scratch_regs(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t scratch_reg;
	पूर्णांक i;

	अगर (rdev->family >= CHIP_R600)
		scratch_reg = R600_BIOS_0_SCRATCH;
	अन्यथा
		scratch_reg = RADEON_BIOS_0_SCRATCH;

	क्रम (i = 0; i < RADEON_BIOS_NUM_SCRATCH; i++)
		rdev->bios_scratch[i] = RREG32(scratch_reg + (i * 4));
पूर्ण

व्योम radeon_restore_bios_scratch_regs(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t scratch_reg;
	पूर्णांक i;

	अगर (rdev->family >= CHIP_R600)
		scratch_reg = R600_BIOS_0_SCRATCH;
	अन्यथा
		scratch_reg = RADEON_BIOS_0_SCRATCH;

	क्रम (i = 0; i < RADEON_BIOS_NUM_SCRATCH; i++)
		WREG32(scratch_reg + (i * 4), rdev->bios_scratch[i]);
पूर्ण

व्योम radeon_atom_output_lock(काष्ठा drm_encoder *encoder, bool lock)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t bios_6_scratch;

	अगर (rdev->family >= CHIP_R600)
		bios_6_scratch = RREG32(R600_BIOS_6_SCRATCH);
	अन्यथा
		bios_6_scratch = RREG32(RADEON_BIOS_6_SCRATCH);

	अगर (lock) अणु
		bios_6_scratch |= ATOM_S6_CRITICAL_STATE;
		bios_6_scratch &= ~ATOM_S6_ACC_MODE;
	पूर्ण अन्यथा अणु
		bios_6_scratch &= ~ATOM_S6_CRITICAL_STATE;
		bios_6_scratch |= ATOM_S6_ACC_MODE;
	पूर्ण

	अगर (rdev->family >= CHIP_R600)
		WREG32(R600_BIOS_6_SCRATCH, bios_6_scratch);
	अन्यथा
		WREG32(RADEON_BIOS_6_SCRATCH, bios_6_scratch);
पूर्ण

/* at some poपूर्णांक we may want to अवरोध this out पूर्णांकo inभागidual functions */
व्योम
radeon_atombios_connected_scratch_regs(काष्ठा drm_connector *connector,
				       काष्ठा drm_encoder *encoder,
				       bool connected)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_connector *radeon_connector =
	    to_radeon_connector(connector);
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uपूर्णांक32_t bios_0_scratch, bios_3_scratch, bios_6_scratch;

	अगर (rdev->family >= CHIP_R600) अणु
		bios_0_scratch = RREG32(R600_BIOS_0_SCRATCH);
		bios_3_scratch = RREG32(R600_BIOS_3_SCRATCH);
		bios_6_scratch = RREG32(R600_BIOS_6_SCRATCH);
	पूर्ण अन्यथा अणु
		bios_0_scratch = RREG32(RADEON_BIOS_0_SCRATCH);
		bios_3_scratch = RREG32(RADEON_BIOS_3_SCRATCH);
		bios_6_scratch = RREG32(RADEON_BIOS_6_SCRATCH);
	पूर्ण

	अगर ((radeon_encoder->devices & ATOM_DEVICE_TV1_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_TV1_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("TV1 connected\n");
			bios_3_scratch |= ATOM_S3_TV1_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_TV1;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("TV1 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_TV1_MASK;
			bios_3_scratch &= ~ATOM_S3_TV1_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_TV1;
		पूर्ण
	पूर्ण
	अगर ((radeon_encoder->devices & ATOM_DEVICE_CV_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_CV_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("CV connected\n");
			bios_3_scratch |= ATOM_S3_CV_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_CV;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("CV disconnected\n");
			bios_0_scratch &= ~ATOM_S0_CV_MASK;
			bios_3_scratch &= ~ATOM_S3_CV_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_CV;
		पूर्ण
	पूर्ण
	अगर ((radeon_encoder->devices & ATOM_DEVICE_LCD1_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_LCD1_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("LCD1 connected\n");
			bios_0_scratch |= ATOM_S0_LCD1;
			bios_3_scratch |= ATOM_S3_LCD1_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_LCD1;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("LCD1 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_LCD1;
			bios_3_scratch &= ~ATOM_S3_LCD1_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_LCD1;
		पूर्ण
	पूर्ण
	अगर ((radeon_encoder->devices & ATOM_DEVICE_CRT1_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_CRT1_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("CRT1 connected\n");
			bios_0_scratch |= ATOM_S0_CRT1_COLOR;
			bios_3_scratch |= ATOM_S3_CRT1_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_CRT1;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("CRT1 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_CRT1_MASK;
			bios_3_scratch &= ~ATOM_S3_CRT1_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_CRT1;
		पूर्ण
	पूर्ण
	अगर ((radeon_encoder->devices & ATOM_DEVICE_CRT2_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_CRT2_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("CRT2 connected\n");
			bios_0_scratch |= ATOM_S0_CRT2_COLOR;
			bios_3_scratch |= ATOM_S3_CRT2_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_CRT2;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("CRT2 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_CRT2_MASK;
			bios_3_scratch &= ~ATOM_S3_CRT2_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_CRT2;
		पूर्ण
	पूर्ण
	अगर ((radeon_encoder->devices & ATOM_DEVICE_DFP1_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_DFP1_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("DFP1 connected\n");
			bios_0_scratch |= ATOM_S0_DFP1;
			bios_3_scratch |= ATOM_S3_DFP1_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_DFP1;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("DFP1 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_DFP1;
			bios_3_scratch &= ~ATOM_S3_DFP1_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_DFP1;
		पूर्ण
	पूर्ण
	अगर ((radeon_encoder->devices & ATOM_DEVICE_DFP2_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_DFP2_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("DFP2 connected\n");
			bios_0_scratch |= ATOM_S0_DFP2;
			bios_3_scratch |= ATOM_S3_DFP2_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_DFP2;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("DFP2 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_DFP2;
			bios_3_scratch &= ~ATOM_S3_DFP2_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_DFP2;
		पूर्ण
	पूर्ण
	अगर ((radeon_encoder->devices & ATOM_DEVICE_DFP3_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_DFP3_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("DFP3 connected\n");
			bios_0_scratch |= ATOM_S0_DFP3;
			bios_3_scratch |= ATOM_S3_DFP3_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_DFP3;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("DFP3 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_DFP3;
			bios_3_scratch &= ~ATOM_S3_DFP3_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_DFP3;
		पूर्ण
	पूर्ण
	अगर ((radeon_encoder->devices & ATOM_DEVICE_DFP4_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_DFP4_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("DFP4 connected\n");
			bios_0_scratch |= ATOM_S0_DFP4;
			bios_3_scratch |= ATOM_S3_DFP4_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_DFP4;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("DFP4 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_DFP4;
			bios_3_scratch &= ~ATOM_S3_DFP4_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_DFP4;
		पूर्ण
	पूर्ण
	अगर ((radeon_encoder->devices & ATOM_DEVICE_DFP5_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_DFP5_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("DFP5 connected\n");
			bios_0_scratch |= ATOM_S0_DFP5;
			bios_3_scratch |= ATOM_S3_DFP5_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_DFP5;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("DFP5 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_DFP5;
			bios_3_scratch &= ~ATOM_S3_DFP5_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_DFP5;
		पूर्ण
	पूर्ण
	अगर ((radeon_encoder->devices & ATOM_DEVICE_DFP6_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_DFP6_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("DFP6 connected\n");
			bios_0_scratch |= ATOM_S0_DFP6;
			bios_3_scratch |= ATOM_S3_DFP6_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_DFP6;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("DFP6 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_DFP6;
			bios_3_scratch &= ~ATOM_S3_DFP6_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_DFP6;
		पूर्ण
	पूर्ण

	अगर (rdev->family >= CHIP_R600) अणु
		WREG32(R600_BIOS_0_SCRATCH, bios_0_scratch);
		WREG32(R600_BIOS_3_SCRATCH, bios_3_scratch);
		WREG32(R600_BIOS_6_SCRATCH, bios_6_scratch);
	पूर्ण अन्यथा अणु
		WREG32(RADEON_BIOS_0_SCRATCH, bios_0_scratch);
		WREG32(RADEON_BIOS_3_SCRATCH, bios_3_scratch);
		WREG32(RADEON_BIOS_6_SCRATCH, bios_6_scratch);
	पूर्ण
पूर्ण

व्योम
radeon_atombios_encoder_crtc_scratch_regs(काष्ठा drm_encoder *encoder, पूर्णांक crtc)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uपूर्णांक32_t bios_3_scratch;

	अगर (ASIC_IS_DCE4(rdev))
		वापस;

	अगर (rdev->family >= CHIP_R600)
		bios_3_scratch = RREG32(R600_BIOS_3_SCRATCH);
	अन्यथा
		bios_3_scratch = RREG32(RADEON_BIOS_3_SCRATCH);

	अगर (radeon_encoder->devices & ATOM_DEVICE_TV1_SUPPORT) अणु
		bios_3_scratch &= ~ATOM_S3_TV1_CRTC_ACTIVE;
		bios_3_scratch |= (crtc << 18);
	पूर्ण
	अगर (radeon_encoder->devices & ATOM_DEVICE_CV_SUPPORT) अणु
		bios_3_scratch &= ~ATOM_S3_CV_CRTC_ACTIVE;
		bios_3_scratch |= (crtc << 24);
	पूर्ण
	अगर (radeon_encoder->devices & ATOM_DEVICE_CRT1_SUPPORT) अणु
		bios_3_scratch &= ~ATOM_S3_CRT1_CRTC_ACTIVE;
		bios_3_scratch |= (crtc << 16);
	पूर्ण
	अगर (radeon_encoder->devices & ATOM_DEVICE_CRT2_SUPPORT) अणु
		bios_3_scratch &= ~ATOM_S3_CRT2_CRTC_ACTIVE;
		bios_3_scratch |= (crtc << 20);
	पूर्ण
	अगर (radeon_encoder->devices & ATOM_DEVICE_LCD1_SUPPORT) अणु
		bios_3_scratch &= ~ATOM_S3_LCD1_CRTC_ACTIVE;
		bios_3_scratch |= (crtc << 17);
	पूर्ण
	अगर (radeon_encoder->devices & ATOM_DEVICE_DFP1_SUPPORT) अणु
		bios_3_scratch &= ~ATOM_S3_DFP1_CRTC_ACTIVE;
		bios_3_scratch |= (crtc << 19);
	पूर्ण
	अगर (radeon_encoder->devices & ATOM_DEVICE_DFP2_SUPPORT) अणु
		bios_3_scratch &= ~ATOM_S3_DFP2_CRTC_ACTIVE;
		bios_3_scratch |= (crtc << 23);
	पूर्ण
	अगर (radeon_encoder->devices & ATOM_DEVICE_DFP3_SUPPORT) अणु
		bios_3_scratch &= ~ATOM_S3_DFP3_CRTC_ACTIVE;
		bios_3_scratch |= (crtc << 25);
	पूर्ण

	अगर (rdev->family >= CHIP_R600)
		WREG32(R600_BIOS_3_SCRATCH, bios_3_scratch);
	अन्यथा
		WREG32(RADEON_BIOS_3_SCRATCH, bios_3_scratch);
पूर्ण

व्योम
radeon_atombios_encoder_dpms_scratch_regs(काष्ठा drm_encoder *encoder, bool on)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uपूर्णांक32_t bios_2_scratch;

	अगर (ASIC_IS_DCE4(rdev))
		वापस;

	अगर (rdev->family >= CHIP_R600)
		bios_2_scratch = RREG32(R600_BIOS_2_SCRATCH);
	अन्यथा
		bios_2_scratch = RREG32(RADEON_BIOS_2_SCRATCH);

	अगर (radeon_encoder->devices & ATOM_DEVICE_TV1_SUPPORT) अणु
		अगर (on)
			bios_2_scratch &= ~ATOM_S2_TV1_DPMS_STATE;
		अन्यथा
			bios_2_scratch |= ATOM_S2_TV1_DPMS_STATE;
	पूर्ण
	अगर (radeon_encoder->devices & ATOM_DEVICE_CV_SUPPORT) अणु
		अगर (on)
			bios_2_scratch &= ~ATOM_S2_CV_DPMS_STATE;
		अन्यथा
			bios_2_scratch |= ATOM_S2_CV_DPMS_STATE;
	पूर्ण
	अगर (radeon_encoder->devices & ATOM_DEVICE_CRT1_SUPPORT) अणु
		अगर (on)
			bios_2_scratch &= ~ATOM_S2_CRT1_DPMS_STATE;
		अन्यथा
			bios_2_scratch |= ATOM_S2_CRT1_DPMS_STATE;
	पूर्ण
	अगर (radeon_encoder->devices & ATOM_DEVICE_CRT2_SUPPORT) अणु
		अगर (on)
			bios_2_scratch &= ~ATOM_S2_CRT2_DPMS_STATE;
		अन्यथा
			bios_2_scratch |= ATOM_S2_CRT2_DPMS_STATE;
	पूर्ण
	अगर (radeon_encoder->devices & ATOM_DEVICE_LCD1_SUPPORT) अणु
		अगर (on)
			bios_2_scratch &= ~ATOM_S2_LCD1_DPMS_STATE;
		अन्यथा
			bios_2_scratch |= ATOM_S2_LCD1_DPMS_STATE;
	पूर्ण
	अगर (radeon_encoder->devices & ATOM_DEVICE_DFP1_SUPPORT) अणु
		अगर (on)
			bios_2_scratch &= ~ATOM_S2_DFP1_DPMS_STATE;
		अन्यथा
			bios_2_scratch |= ATOM_S2_DFP1_DPMS_STATE;
	पूर्ण
	अगर (radeon_encoder->devices & ATOM_DEVICE_DFP2_SUPPORT) अणु
		अगर (on)
			bios_2_scratch &= ~ATOM_S2_DFP2_DPMS_STATE;
		अन्यथा
			bios_2_scratch |= ATOM_S2_DFP2_DPMS_STATE;
	पूर्ण
	अगर (radeon_encoder->devices & ATOM_DEVICE_DFP3_SUPPORT) अणु
		अगर (on)
			bios_2_scratch &= ~ATOM_S2_DFP3_DPMS_STATE;
		अन्यथा
			bios_2_scratch |= ATOM_S2_DFP3_DPMS_STATE;
	पूर्ण
	अगर (radeon_encoder->devices & ATOM_DEVICE_DFP4_SUPPORT) अणु
		अगर (on)
			bios_2_scratch &= ~ATOM_S2_DFP4_DPMS_STATE;
		अन्यथा
			bios_2_scratch |= ATOM_S2_DFP4_DPMS_STATE;
	पूर्ण
	अगर (radeon_encoder->devices & ATOM_DEVICE_DFP5_SUPPORT) अणु
		अगर (on)
			bios_2_scratch &= ~ATOM_S2_DFP5_DPMS_STATE;
		अन्यथा
			bios_2_scratch |= ATOM_S2_DFP5_DPMS_STATE;
	पूर्ण

	अगर (rdev->family >= CHIP_R600)
		WREG32(R600_BIOS_2_SCRATCH, bios_2_scratch);
	अन्यथा
		WREG32(RADEON_BIOS_2_SCRATCH, bios_2_scratch);
पूर्ण
