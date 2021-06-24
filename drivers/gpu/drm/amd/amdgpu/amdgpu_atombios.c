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

#समावेश <drm/amdgpu_drm.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_atombios.h"
#समावेश "amdgpu_atomfirmware.h"
#समावेश "amdgpu_i2c.h"
#समावेश "amdgpu_display.h"

#समावेश "atom.h"
#समावेश "atom-bits.h"
#समावेश "atombios_encoders.h"
#समावेश "bif/bif_4_1_d.h"

अटल व्योम amdgpu_atombios_lookup_i2c_gpio_quirks(काष्ठा amdgpu_device *adev,
					  ATOM_GPIO_I2C_ASSIGMENT *gpio,
					  u8 index)
अणु

पूर्ण

अटल काष्ठा amdgpu_i2c_bus_rec amdgpu_atombios_get_bus_rec_क्रम_i2c_gpio(ATOM_GPIO_I2C_ASSIGMENT *gpio)
अणु
	काष्ठा amdgpu_i2c_bus_rec i2c;

	स_रखो(&i2c, 0, माप(काष्ठा amdgpu_i2c_bus_rec));

	i2c.mask_clk_reg = le16_to_cpu(gpio->usClkMaskRegisterIndex);
	i2c.mask_data_reg = le16_to_cpu(gpio->usDataMaskRegisterIndex);
	i2c.en_clk_reg = le16_to_cpu(gpio->usClkEnRegisterIndex);
	i2c.en_data_reg = le16_to_cpu(gpio->usDataEnRegisterIndex);
	i2c.y_clk_reg = le16_to_cpu(gpio->usClkY_RegisterIndex);
	i2c.y_data_reg = le16_to_cpu(gpio->usDataY_RegisterIndex);
	i2c.a_clk_reg = le16_to_cpu(gpio->usClkA_RegisterIndex);
	i2c.a_data_reg = le16_to_cpu(gpio->usDataA_RegisterIndex);
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

काष्ठा amdgpu_i2c_bus_rec amdgpu_atombios_lookup_i2c_gpio(काष्ठा amdgpu_device *adev,
							  uपूर्णांक8_t id)
अणु
	काष्ठा atom_context *ctx = adev->mode_info.atom_context;
	ATOM_GPIO_I2C_ASSIGMENT *gpio;
	काष्ठा amdgpu_i2c_bus_rec i2c;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, GPIO_I2C_Info);
	काष्ठा _ATOM_GPIO_I2C_INFO *i2c_info;
	uपूर्णांक16_t data_offset, size;
	पूर्णांक i, num_indices;

	स_रखो(&i2c, 0, माप(काष्ठा amdgpu_i2c_bus_rec));
	i2c.valid = false;

	अगर (amdgpu_atom_parse_data_header(ctx, index, &size, शून्य, शून्य, &data_offset)) अणु
		i2c_info = (काष्ठा _ATOM_GPIO_I2C_INFO *)(ctx->bios + data_offset);

		num_indices = (size - माप(ATOM_COMMON_TABLE_HEADER)) /
			माप(ATOM_GPIO_I2C_ASSIGMENT);

		gpio = &i2c_info->asGPIO_Info[0];
		क्रम (i = 0; i < num_indices; i++) अणु

			amdgpu_atombios_lookup_i2c_gpio_quirks(adev, gpio, i);

			अगर (gpio->sucI2cId.ucAccess == id) अणु
				i2c = amdgpu_atombios_get_bus_rec_क्रम_i2c_gpio(gpio);
				अवरोध;
			पूर्ण
			gpio = (ATOM_GPIO_I2C_ASSIGMENT *)
				((u8 *)gpio + माप(ATOM_GPIO_I2C_ASSIGMENT));
		पूर्ण
	पूर्ण

	वापस i2c;
पूर्ण

व्योम amdgpu_atombios_i2c_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा atom_context *ctx = adev->mode_info.atom_context;
	ATOM_GPIO_I2C_ASSIGMENT *gpio;
	काष्ठा amdgpu_i2c_bus_rec i2c;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, GPIO_I2C_Info);
	काष्ठा _ATOM_GPIO_I2C_INFO *i2c_info;
	uपूर्णांक16_t data_offset, size;
	पूर्णांक i, num_indices;
	अक्षर sपंचांगp[32];

	अगर (amdgpu_atom_parse_data_header(ctx, index, &size, शून्य, शून्य, &data_offset)) अणु
		i2c_info = (काष्ठा _ATOM_GPIO_I2C_INFO *)(ctx->bios + data_offset);

		num_indices = (size - माप(ATOM_COMMON_TABLE_HEADER)) /
			माप(ATOM_GPIO_I2C_ASSIGMENT);

		gpio = &i2c_info->asGPIO_Info[0];
		क्रम (i = 0; i < num_indices; i++) अणु
			amdgpu_atombios_lookup_i2c_gpio_quirks(adev, gpio, i);

			i2c = amdgpu_atombios_get_bus_rec_क्रम_i2c_gpio(gpio);

			अगर (i2c.valid) अणु
				प्र_लिखो(sपंचांगp, "0x%x", i2c.i2c_id);
				adev->i2c_bus[i] = amdgpu_i2c_create(adev_to_drm(adev), &i2c, sपंचांगp);
			पूर्ण
			gpio = (ATOM_GPIO_I2C_ASSIGMENT *)
				((u8 *)gpio + माप(ATOM_GPIO_I2C_ASSIGMENT));
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा amdgpu_gpio_rec
amdgpu_atombios_lookup_gpio(काष्ठा amdgpu_device *adev,
			    u8 id)
अणु
	काष्ठा atom_context *ctx = adev->mode_info.atom_context;
	काष्ठा amdgpu_gpio_rec gpio;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, GPIO_Pin_LUT);
	काष्ठा _ATOM_GPIO_PIN_LUT *gpio_info;
	ATOM_GPIO_PIN_ASSIGNMENT *pin;
	u16 data_offset, size;
	पूर्णांक i, num_indices;

	स_रखो(&gpio, 0, माप(काष्ठा amdgpu_gpio_rec));
	gpio.valid = false;

	अगर (amdgpu_atom_parse_data_header(ctx, index, &size, शून्य, शून्य, &data_offset)) अणु
		gpio_info = (काष्ठा _ATOM_GPIO_PIN_LUT *)(ctx->bios + data_offset);

		num_indices = (size - माप(ATOM_COMMON_TABLE_HEADER)) /
			माप(ATOM_GPIO_PIN_ASSIGNMENT);

		pin = gpio_info->asGPIO_Pin;
		क्रम (i = 0; i < num_indices; i++) अणु
			अगर (id == pin->ucGPIO_ID) अणु
				gpio.id = pin->ucGPIO_ID;
				gpio.reg = le16_to_cpu(pin->usGpioPin_AIndex);
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

अटल काष्ठा amdgpu_hpd
amdgpu_atombios_get_hpd_info_from_gpio(काष्ठा amdgpu_device *adev,
				       काष्ठा amdgpu_gpio_rec *gpio)
अणु
	काष्ठा amdgpu_hpd hpd;
	u32 reg;

	स_रखो(&hpd, 0, माप(काष्ठा amdgpu_hpd));

	reg = amdgpu_display_hpd_get_gpio_reg(adev);

	hpd.gpio = *gpio;
	अगर (gpio->reg == reg) अणु
		चयन(gpio->mask) अणु
		हाल (1 << 0):
			hpd.hpd = AMDGPU_HPD_1;
			अवरोध;
		हाल (1 << 8):
			hpd.hpd = AMDGPU_HPD_2;
			अवरोध;
		हाल (1 << 16):
			hpd.hpd = AMDGPU_HPD_3;
			अवरोध;
		हाल (1 << 24):
			hpd.hpd = AMDGPU_HPD_4;
			अवरोध;
		हाल (1 << 26):
			hpd.hpd = AMDGPU_HPD_5;
			अवरोध;
		हाल (1 << 28):
			hpd.hpd = AMDGPU_HPD_6;
			अवरोध;
		शेष:
			hpd.hpd = AMDGPU_HPD_NONE;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		hpd.hpd = AMDGPU_HPD_NONE;
	वापस hpd;
पूर्ण

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

bool amdgpu_atombios_has_dce_engine_info(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_mode_info *mode_info = &adev->mode_info;
	काष्ठा atom_context *ctx = mode_info->atom_context;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, Object_Header);
	u16 size, data_offset;
	u8 frev, crev;
	ATOM_DISPLAY_OBJECT_PATH_TABLE *path_obj;
	ATOM_OBJECT_HEADER *obj_header;

	अगर (!amdgpu_atom_parse_data_header(ctx, index, &size, &frev, &crev, &data_offset))
		वापस false;

	अगर (crev < 2)
		वापस false;

	obj_header = (ATOM_OBJECT_HEADER *) (ctx->bios + data_offset);
	path_obj = (ATOM_DISPLAY_OBJECT_PATH_TABLE *)
	    (ctx->bios + data_offset +
	     le16_to_cpu(obj_header->usDisplayPathTableOffset));

	अगर (path_obj->ucNumOfDispPath)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

bool amdgpu_atombios_get_connector_info_from_object_table(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_mode_info *mode_info = &adev->mode_info;
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
	u16 conn_id, connector_object_id;
	काष्ठा amdgpu_i2c_bus_rec ddc_bus;
	काष्ठा amdgpu_router router;
	काष्ठा amdgpu_gpio_rec gpio;
	काष्ठा amdgpu_hpd hpd;

	अगर (!amdgpu_atom_parse_data_header(ctx, index, &size, &frev, &crev, &data_offset))
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
			uपूर्णांक8_t con_obj_id =
			    (le16_to_cpu(path->usConnObjectId) & OBJECT_ID_MASK)
			    >> OBJECT_ID_SHIFT;

			/* Skip TV/CV support */
			अगर ((le16_to_cpu(path->usDeviceTag) ==
			     ATOM_DEVICE_TV1_SUPPORT) ||
			    (le16_to_cpu(path->usDeviceTag) ==
			     ATOM_DEVICE_CV_SUPPORT))
				जारी;

			अगर (con_obj_id >= ARRAY_SIZE(object_connector_convert)) अणु
				DRM_ERROR("invalid con_obj_id %d for device tag 0x%04x\n",
					  con_obj_id, le16_to_cpu(path->usDeviceTag));
				जारी;
			पूर्ण

			connector_type =
				object_connector_convert[con_obj_id];
			connector_object_id = con_obj_id;

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
							amdgpu_display_add_encoder(adev, encoder_obj,
										    le16_to_cpu(path->usDeviceTag),
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
										amdgpu_atombios_lookup_i2c_gpio(adev,
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
			hpd.hpd = AMDGPU_HPD_NONE;
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
								ddc_bus = amdgpu_atombios_lookup_i2c_gpio(adev,
												 i2c_config->
												 ucAccess);
								अवरोध;
							हाल ATOM_HPD_INT_RECORD_TYPE:
								hpd_record =
									(ATOM_HPD_INT_RECORD *)
									record;
								gpio = amdgpu_atombios_lookup_gpio(adev,
											  hpd_record->ucHPDIntGPIOID);
								hpd = amdgpu_atombios_get_hpd_info_from_gpio(adev, &gpio);
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

			amdgpu_display_add_connector(adev,
						      conn_id,
						      le16_to_cpu(path->usDeviceTag),
						      connector_type, &ddc_bus,
						      connector_object_id,
						      &hpd,
						      &router);

		पूर्ण
	पूर्ण

	amdgpu_link_encoder_connector(adev_to_drm(adev));

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

पूर्णांक amdgpu_atombios_get_घड़ी_info(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_mode_info *mode_info = &adev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, FirmwareInfo);
	uपूर्णांक8_t frev, crev;
	uपूर्णांक16_t data_offset;
	पूर्णांक ret = -EINVAL;

	अगर (amdgpu_atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset)) अणु
		पूर्णांक i;
		काष्ठा amdgpu_pll *ppll = &adev->घड़ी.ppll[0];
		काष्ठा amdgpu_pll *spll = &adev->घड़ी.spll;
		काष्ठा amdgpu_pll *mpll = &adev->घड़ी.mpll;
		जोड़ firmware_info *firmware_info =
			(जोड़ firmware_info *)(mode_info->atom_context->bios +
						data_offset);
		/* pixel घड़ीs */
		ppll->reference_freq =
		    le16_to_cpu(firmware_info->info.usReferenceClock);
		ppll->reference_भाग = 0;

		ppll->pll_out_min =
			le32_to_cpu(firmware_info->info_12.ulMinPixelClockPLL_Output);
		ppll->pll_out_max =
		    le32_to_cpu(firmware_info->info.ulMaxPixelClockPLL_Output);

		ppll->lcd_pll_out_min =
			le16_to_cpu(firmware_info->info_14.usLcdMinPixelClockPLL_Output) * 100;
		अगर (ppll->lcd_pll_out_min == 0)
			ppll->lcd_pll_out_min = ppll->pll_out_min;
		ppll->lcd_pll_out_max =
			le16_to_cpu(firmware_info->info_14.usLcdMaxPixelClockPLL_Output) * 100;
		अगर (ppll->lcd_pll_out_max == 0)
			ppll->lcd_pll_out_max = ppll->pll_out_max;

		अगर (ppll->pll_out_min == 0)
			ppll->pll_out_min = 64800;

		ppll->pll_in_min =
		    le16_to_cpu(firmware_info->info.usMinPixelClockPLL_Input);
		ppll->pll_in_max =
		    le16_to_cpu(firmware_info->info.usMaxPixelClockPLL_Input);

		ppll->min_post_भाग = 2;
		ppll->max_post_भाग = 0x7f;
		ppll->min_frac_feedback_भाग = 0;
		ppll->max_frac_feedback_भाग = 9;
		ppll->min_ref_भाग = 2;
		ppll->max_ref_भाग = 0x3ff;
		ppll->min_feedback_भाग = 4;
		ppll->max_feedback_भाग = 0xfff;
		ppll->best_vco = 0;

		क्रम (i = 1; i < AMDGPU_MAX_PPLL; i++)
			adev->घड़ी.ppll[i] = *ppll;

		/* प्रणाली घड़ी */
		spll->reference_freq =
			le16_to_cpu(firmware_info->info_21.usCoreReferenceClock);
		spll->reference_भाग = 0;

		spll->pll_out_min =
		    le16_to_cpu(firmware_info->info.usMinEngineClockPLL_Output);
		spll->pll_out_max =
		    le32_to_cpu(firmware_info->info.ulMaxEngineClockPLL_Output);

		/* ??? */
		अगर (spll->pll_out_min == 0)
			spll->pll_out_min = 64800;

		spll->pll_in_min =
		    le16_to_cpu(firmware_info->info.usMinEngineClockPLL_Input);
		spll->pll_in_max =
		    le16_to_cpu(firmware_info->info.usMaxEngineClockPLL_Input);

		spll->min_post_भाग = 1;
		spll->max_post_भाग = 1;
		spll->min_ref_भाग = 2;
		spll->max_ref_भाग = 0xff;
		spll->min_feedback_भाग = 4;
		spll->max_feedback_भाग = 0xff;
		spll->best_vco = 0;

		/* memory घड़ी */
		mpll->reference_freq =
			le16_to_cpu(firmware_info->info_21.usMemoryReferenceClock);
		mpll->reference_भाग = 0;

		mpll->pll_out_min =
		    le16_to_cpu(firmware_info->info.usMinMemoryClockPLL_Output);
		mpll->pll_out_max =
		    le32_to_cpu(firmware_info->info.ulMaxMemoryClockPLL_Output);

		/* ??? */
		अगर (mpll->pll_out_min == 0)
			mpll->pll_out_min = 64800;

		mpll->pll_in_min =
		    le16_to_cpu(firmware_info->info.usMinMemoryClockPLL_Input);
		mpll->pll_in_max =
		    le16_to_cpu(firmware_info->info.usMaxMemoryClockPLL_Input);

		adev->घड़ी.शेष_sclk =
		    le32_to_cpu(firmware_info->info.ulDefaultEngineClock);
		adev->घड़ी.शेष_mclk =
		    le32_to_cpu(firmware_info->info.ulDefaultMemoryClock);

		mpll->min_post_भाग = 1;
		mpll->max_post_भाग = 1;
		mpll->min_ref_भाग = 2;
		mpll->max_ref_भाग = 0xff;
		mpll->min_feedback_भाग = 4;
		mpll->max_feedback_भाग = 0xff;
		mpll->best_vco = 0;

		/* disp घड़ी */
		adev->घड़ी.शेष_dispclk =
			le32_to_cpu(firmware_info->info_21.ulDefaultDispEngineClkFreq);
		/* set a reasonable शेष क्रम DP */
		अगर (adev->घड़ी.शेष_dispclk < 53900) अणु
			DRM_DEBUG("Changing default dispclk from %dMhz to 600Mhz\n",
				  adev->घड़ी.शेष_dispclk / 100);
			adev->घड़ी.शेष_dispclk = 60000;
		पूर्ण अन्यथा अगर (adev->घड़ी.शेष_dispclk <= 60000) अणु
			DRM_DEBUG("Changing default dispclk from %dMhz to 625Mhz\n",
				  adev->घड़ी.शेष_dispclk / 100);
			adev->घड़ी.शेष_dispclk = 62500;
		पूर्ण
		adev->घड़ी.dp_extclk =
			le16_to_cpu(firmware_info->info_21.usUniphyDPModeExtClkFreq);
		adev->घड़ी.current_dispclk = adev->घड़ी.शेष_dispclk;

		adev->घड़ी.max_pixel_घड़ी = le16_to_cpu(firmware_info->info.usMaxPixelClock);
		अगर (adev->घड़ी.max_pixel_घड़ी == 0)
			adev->घड़ी.max_pixel_घड़ी = 40000;

		/* not technically a घड़ी, but... */
		adev->mode_info.firmware_flags =
			le16_to_cpu(firmware_info->info.usFirmwareCapability.susAccess);

		ret = 0;
	पूर्ण

	adev->pm.current_sclk = adev->घड़ी.शेष_sclk;
	adev->pm.current_mclk = adev->घड़ी.शेष_mclk;

	वापस ret;
पूर्ण

जोड़ gfx_info अणु
	ATOM_GFX_INFO_V2_1 info;
पूर्ण;

पूर्णांक amdgpu_atombios_get_gfx_info(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_mode_info *mode_info = &adev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, GFX_Info);
	uपूर्णांक8_t frev, crev;
	uपूर्णांक16_t data_offset;
	पूर्णांक ret = -EINVAL;

	अगर (amdgpu_atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset)) अणु
		जोड़ gfx_info *gfx_info = (जोड़ gfx_info *)
			(mode_info->atom_context->bios + data_offset);

		adev->gfx.config.max_shader_engines = gfx_info->info.max_shader_engines;
		adev->gfx.config.max_tile_pipes = gfx_info->info.max_tile_pipes;
		adev->gfx.config.max_cu_per_sh = gfx_info->info.max_cu_per_sh;
		adev->gfx.config.max_sh_per_se = gfx_info->info.max_sh_per_se;
		adev->gfx.config.max_backends_per_se = gfx_info->info.max_backends_per_se;
		adev->gfx.config.max_texture_channel_caches =
			gfx_info->info.max_texture_channel_caches;

		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

जोड़ igp_info अणु
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO info;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V2 info_2;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V6 info_6;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V1_7 info_7;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V1_8 info_8;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V1_9 info_9;
पूर्ण;

/*
 * Return vram width from पूर्णांकegrated प्रणाली info table, अगर available,
 * or 0 अगर not.
 */
पूर्णांक amdgpu_atombios_get_vram_width(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_mode_info *mode_info = &adev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, IntegratedSystemInfo);
	u16 data_offset, size;
	जोड़ igp_info *igp_info;
	u8 frev, crev;

	/* get any igp specअगरic overrides */
	अगर (amdgpu_atom_parse_data_header(mode_info->atom_context, index, &size,
				   &frev, &crev, &data_offset)) अणु
		igp_info = (जोड़ igp_info *)
			(mode_info->atom_context->bios + data_offset);
		चयन (crev) अणु
		हाल 8:
		हाल 9:
			वापस igp_info->info_8.ucUMAChannelNumber * 64;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम amdgpu_atombios_get_igp_ss_overrides(काष्ठा amdgpu_device *adev,
						 काष्ठा amdgpu_atom_ss *ss,
						 पूर्णांक id)
अणु
	काष्ठा amdgpu_mode_info *mode_info = &adev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, IntegratedSystemInfo);
	u16 data_offset, size;
	जोड़ igp_info *igp_info;
	u8 frev, crev;
	u16 percentage = 0, rate = 0;

	/* get any igp specअगरic overrides */
	अगर (amdgpu_atom_parse_data_header(mode_info->atom_context, index, &size,
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
		हाल 9:
			चयन (id) अणु
			हाल ASIC_INTERNAL_SS_ON_TMDS:
				percentage = le16_to_cpu(igp_info->info_9.usDVISSPercentage);
				rate = le16_to_cpu(igp_info->info_9.usDVISSpपढ़ोRateIn10Hz);
				अवरोध;
			हाल ASIC_INTERNAL_SS_ON_HDMI:
				percentage = le16_to_cpu(igp_info->info_9.usHDMISSPercentage);
				rate = le16_to_cpu(igp_info->info_9.usHDMISSpपढ़ोRateIn10Hz);
				अवरोध;
			हाल ASIC_INTERNAL_SS_ON_LVDS:
				percentage = le16_to_cpu(igp_info->info_9.usLvdsSSPercentage);
				rate = le16_to_cpu(igp_info->info_9.usLvdsSSpपढ़ोRateIn10Hz);
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

bool amdgpu_atombios_get_asic_ss_info(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_atom_ss *ss,
				      पूर्णांक id, u32 घड़ी)
अणु
	काष्ठा amdgpu_mode_info *mode_info = &adev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, ASIC_InternalSS_Info);
	uपूर्णांक16_t data_offset, size;
	जोड़ asic_ss_info *ss_info;
	जोड़ asic_ss_assignment *ss_assign;
	uपूर्णांक8_t frev, crev;
	पूर्णांक i, num_indices;

	अगर (id == ASIC_INTERNAL_MEMORY_SS) अणु
		अगर (!(adev->mode_info.firmware_flags & ATOM_BIOS_INFO_MEMORY_CLOCK_SS_SUPPORT))
			वापस false;
	पूर्ण
	अगर (id == ASIC_INTERNAL_ENGINE_SS) अणु
		अगर (!(adev->mode_info.firmware_flags & ATOM_BIOS_INFO_ENGINE_CLOCK_SS_SUPPORT))
			वापस false;
	पूर्ण

	स_रखो(ss, 0, माप(काष्ठा amdgpu_atom_ss));
	अगर (amdgpu_atom_parse_data_header(mode_info->atom_context, index, &size,
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
					अगर (adev->flags & AMD_IS_APU)
						amdgpu_atombios_get_igp_ss_overrides(adev, ss, id);
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

जोड़ get_घड़ी_भागiders अणु
	काष्ठा _COMPUTE_MEMORY_ENGINE_PLL_PARAMETERS v1;
	काष्ठा _COMPUTE_MEMORY_ENGINE_PLL_PARAMETERS_V2 v2;
	काष्ठा _COMPUTE_MEMORY_ENGINE_PLL_PARAMETERS_V3 v3;
	काष्ठा _COMPUTE_MEMORY_ENGINE_PLL_PARAMETERS_V4 v4;
	काष्ठा _COMPUTE_MEMORY_ENGINE_PLL_PARAMETERS_V5 v5;
	काष्ठा _COMPUTE_GPU_CLOCK_INPUT_PARAMETERS_V1_6 v6_in;
	काष्ठा _COMPUTE_GPU_CLOCK_OUTPUT_PARAMETERS_V1_6 v6_out;
पूर्ण;

पूर्णांक amdgpu_atombios_get_घड़ी_भागiders(काष्ठा amdgpu_device *adev,
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

	अगर (!amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context, index, &frev, &crev))
		वापस -EINVAL;

	चयन (crev) अणु
	हाल 2:
	हाल 3:
	हाल 5:
		/* r6xx, r7xx, evergreen, ni, si.
		 * TODO: add support क्रम asic_type <= CHIP_RV770*/
		अगर (घड़ी_प्रकारype == COMPUTE_ENGINE_PLL_PARAM) अणु
			args.v3.ulClockParams = cpu_to_le32((घड़ी_प्रकारype << 24) | घड़ी);

			amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

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
			अगर (adev->asic_type >= CHIP_TAHITI)
				वापस -EINVAL;
			args.v5.ulClockParams = cpu_to_le32((घड़ी_प्रकारype << 24) | घड़ी);
			अगर (strobe_mode)
				args.v5.ucInputFlag = ATOM_PLL_INPUT_FLAG_PLL_STROBE_MODE_EN;

			amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

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
		अवरोध;
	हाल 4:
		/* fusion */
		args.v4.ulClock = cpu_to_le32(घड़ी);	/* 10 khz */

		amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

		भागiders->post_भागider = भागiders->post_भाग = args.v4.ucPostDiv;
		भागiders->real_घड़ी = le32_to_cpu(args.v4.ulClock);
		अवरोध;
	हाल 6:
		/* CI */
		/* COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK, COMPUTE_GPUCLK_INPUT_FLAG_SCLK */
		args.v6_in.ulClock.ulComputeClockFlag = घड़ी_प्रकारype;
		args.v6_in.ulClock.ulClockFreq = cpu_to_le32(घड़ी);	/* 10 khz */

		amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

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

पूर्णांक amdgpu_atombios_get_memory_pll_भागiders(काष्ठा amdgpu_device *adev,
					    u32 घड़ी,
					    bool strobe_mode,
					    काष्ठा atom_mpll_param *mpll_param)
अणु
	COMPUTE_MEMORY_CLOCK_PARAM_PARAMETERS_V2_1 args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, ComputeMemoryClockParam);
	u8 frev, crev;

	स_रखो(&args, 0, माप(args));
	स_रखो(mpll_param, 0, माप(काष्ठा atom_mpll_param));

	अगर (!amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context, index, &frev, &crev))
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

			amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

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

व्योम amdgpu_atombios_set_engine_dram_timings(काष्ठा amdgpu_device *adev,
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

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

व्योम amdgpu_atombios_get_शेष_voltages(काष्ठा amdgpu_device *adev,
					  u16 *vddc, u16 *vddci, u16 *mvdd)
अणु
	काष्ठा amdgpu_mode_info *mode_info = &adev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, FirmwareInfo);
	u8 frev, crev;
	u16 data_offset;
	जोड़ firmware_info *firmware_info;

	*vddc = 0;
	*vddci = 0;
	*mvdd = 0;

	अगर (amdgpu_atom_parse_data_header(mode_info->atom_context, index, शून्य,
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

जोड़ set_voltage अणु
	काष्ठा _SET_VOLTAGE_PS_ALLOCATION alloc;
	काष्ठा _SET_VOLTAGE_PARAMETERS v1;
	काष्ठा _SET_VOLTAGE_PARAMETERS_V2 v2;
	काष्ठा _SET_VOLTAGE_PARAMETERS_V1_3 v3;
पूर्ण;

पूर्णांक amdgpu_atombios_get_max_vddc(काष्ठा amdgpu_device *adev, u8 voltage_type,
			     u16 voltage_id, u16 *voltage)
अणु
	जोड़ set_voltage args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, SetVoltage);
	u8 frev, crev;

	अगर (!amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context, index, &frev, &crev))
		वापस -EINVAL;

	चयन (crev) अणु
	हाल 1:
		वापस -EINVAL;
	हाल 2:
		args.v2.ucVoltageType = SET_VOLTAGE_GET_MAX_VOLTAGE;
		args.v2.ucVoltageMode = 0;
		args.v2.usVoltageLevel = 0;

		amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

		*voltage = le16_to_cpu(args.v2.usVoltageLevel);
		अवरोध;
	हाल 3:
		args.v3.ucVoltageType = voltage_type;
		args.v3.ucVoltageMode = ATOM_GET_VOLTAGE_LEVEL;
		args.v3.usVoltageLevel = cpu_to_le16(voltage_id);

		amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

		*voltage = le16_to_cpu(args.v3.usVoltageLevel);
		अवरोध;
	शेष:
		DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक amdgpu_atombios_get_leakage_vddc_based_on_leakage_idx(काष्ठा amdgpu_device *adev,
						      u16 *voltage,
						      u16 leakage_idx)
अणु
	वापस amdgpu_atombios_get_max_vddc(adev, VOLTAGE_TYPE_VDDC, leakage_idx, voltage);
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


अटल ATOM_VOLTAGE_OBJECT_V3 *amdgpu_atombios_lookup_voltage_object_v3(ATOM_VOLTAGE_OBJECT_INFO_V3_1 *v3,
									u8 voltage_type, u8 voltage_mode)
अणु
	u32 size = le16_to_cpu(v3->sHeader.usStructureSize);
	u32 offset = दुरत्व(ATOM_VOLTAGE_OBJECT_INFO_V3_1, asVoltageObj[0]);
	u8 *start = (u8 *)v3;

	जबतक (offset < size) अणु
		ATOM_VOLTAGE_OBJECT_V3 *vo = (ATOM_VOLTAGE_OBJECT_V3 *)(start + offset);
		अगर ((vo->asGpioVoltageObj.sHeader.ucVoltageType == voltage_type) &&
		    (vo->asGpioVoltageObj.sHeader.ucVoltageMode == voltage_mode))
			वापस vo;
		offset += le16_to_cpu(vo->asGpioVoltageObj.sHeader.usSize);
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक amdgpu_atombios_get_svi2_info(काष्ठा amdgpu_device *adev,
			      u8 voltage_type,
			      u8 *svd_gpio_id, u8 *svc_gpio_id)
अणु
	पूर्णांक index = GetIndexIntoMasterTable(DATA, VoltageObjectInfo);
	u8 frev, crev;
	u16 data_offset, size;
	जोड़ voltage_object_info *voltage_info;
	जोड़ voltage_object *voltage_object = शून्य;

	अगर (amdgpu_atom_parse_data_header(adev->mode_info.atom_context, index, &size,
				   &frev, &crev, &data_offset)) अणु
		voltage_info = (जोड़ voltage_object_info *)
			(adev->mode_info.atom_context->bios + data_offset);

		चयन (frev) अणु
		हाल 3:
			चयन (crev) अणु
			हाल 1:
				voltage_object = (जोड़ voltage_object *)
					amdgpu_atombios_lookup_voltage_object_v3(&voltage_info->v3,
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

bool
amdgpu_atombios_is_voltage_gpio(काष्ठा amdgpu_device *adev,
				u8 voltage_type, u8 voltage_mode)
अणु
	पूर्णांक index = GetIndexIntoMasterTable(DATA, VoltageObjectInfo);
	u8 frev, crev;
	u16 data_offset, size;
	जोड़ voltage_object_info *voltage_info;

	अगर (amdgpu_atom_parse_data_header(adev->mode_info.atom_context, index, &size,
				   &frev, &crev, &data_offset)) अणु
		voltage_info = (जोड़ voltage_object_info *)
			(adev->mode_info.atom_context->bios + data_offset);

		चयन (frev) अणु
		हाल 3:
			चयन (crev) अणु
			हाल 1:
				अगर (amdgpu_atombios_lookup_voltage_object_v3(&voltage_info->v3,
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

पूर्णांक amdgpu_atombios_get_voltage_table(काष्ठा amdgpu_device *adev,
				      u8 voltage_type, u8 voltage_mode,
				      काष्ठा atom_voltage_table *voltage_table)
अणु
	पूर्णांक index = GetIndexIntoMasterTable(DATA, VoltageObjectInfo);
	u8 frev, crev;
	u16 data_offset, size;
	पूर्णांक i;
	जोड़ voltage_object_info *voltage_info;
	जोड़ voltage_object *voltage_object = शून्य;

	अगर (amdgpu_atom_parse_data_header(adev->mode_info.atom_context, index, &size,
				   &frev, &crev, &data_offset)) अणु
		voltage_info = (जोड़ voltage_object_info *)
			(adev->mode_info.atom_context->bios + data_offset);

		चयन (frev) अणु
		हाल 3:
			चयन (crev) अणु
			हाल 1:
				voltage_object = (जोड़ voltage_object *)
					amdgpu_atombios_lookup_voltage_object_v3(&voltage_info->v3,
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

#घोषणा MEM_ID_MASK           0xff000000
#घोषणा MEM_ID_SHIFT          24
#घोषणा CLOCK_RANGE_MASK      0x00ffffff
#घोषणा CLOCK_RANGE_SHIFT     0
#घोषणा LOW_NIBBLE_MASK       0xf
#घोषणा DATA_EQU_PREV         0
#घोषणा DATA_FROM_TABLE       4

पूर्णांक amdgpu_atombios_init_mc_reg_table(काष्ठा amdgpu_device *adev,
				      u8 module_index,
				      काष्ठा atom_mc_reg_table *reg_table)
अणु
	पूर्णांक index = GetIndexIntoMasterTable(DATA, VRAM_Info);
	u8 frev, crev, num_entries, t_mem_id, num_ranges = 0;
	u32 i = 0, j;
	u16 data_offset, size;
	जोड़ vram_info *vram_info;

	स_रखो(reg_table, 0, माप(काष्ठा atom_mc_reg_table));

	अगर (amdgpu_atom_parse_data_header(adev->mode_info.atom_context, index, &size,
				   &frev, &crev, &data_offset)) अणु
		vram_info = (जोड़ vram_info *)
			(adev->mode_info.atom_context->bios + data_offset);
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

bool amdgpu_atombios_has_gpu_भवization_table(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक index = GetIndexIntoMasterTable(DATA, GPUVirtualizationInfo);
	u8 frev, crev;
	u16 data_offset, size;

	अगर (amdgpu_atom_parse_data_header(adev->mode_info.atom_context, index, &size,
					  &frev, &crev, &data_offset))
		वापस true;

	वापस false;
पूर्ण

व्योम amdgpu_atombios_scratch_regs_lock(काष्ठा amdgpu_device *adev, bool lock)
अणु
	uपूर्णांक32_t bios_6_scratch;

	bios_6_scratch = RREG32(adev->bios_scratch_reg_offset + 6);

	अगर (lock) अणु
		bios_6_scratch |= ATOM_S6_CRITICAL_STATE;
		bios_6_scratch &= ~ATOM_S6_ACC_MODE;
	पूर्ण अन्यथा अणु
		bios_6_scratch &= ~ATOM_S6_CRITICAL_STATE;
		bios_6_scratch |= ATOM_S6_ACC_MODE;
	पूर्ण

	WREG32(adev->bios_scratch_reg_offset + 6, bios_6_scratch);
पूर्ण

अटल व्योम amdgpu_atombios_scratch_regs_init(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t bios_2_scratch, bios_6_scratch;

	adev->bios_scratch_reg_offset = mmBIOS_SCRATCH_0;

	bios_2_scratch = RREG32(adev->bios_scratch_reg_offset + 2);
	bios_6_scratch = RREG32(adev->bios_scratch_reg_offset + 6);

	/* let the bios control the backlight */
	bios_2_scratch &= ~ATOM_S2_VRI_BRIGHT_ENABLE;

	/* tell the bios not to handle mode चयनing */
	bios_6_scratch |= ATOM_S6_ACC_BLOCK_DISPLAY_SWITCH;

	/* clear the vbios dpms state */
	bios_2_scratch &= ~ATOM_S2_DEVICE_DPMS_STATE;

	WREG32(adev->bios_scratch_reg_offset + 2, bios_2_scratch);
	WREG32(adev->bios_scratch_reg_offset + 6, bios_6_scratch);
पूर्ण

व्योम amdgpu_atombios_scratch_regs_engine_hung(काष्ठा amdgpu_device *adev,
					      bool hung)
अणु
	u32 पंचांगp = RREG32(adev->bios_scratch_reg_offset + 3);

	अगर (hung)
		पंचांगp |= ATOM_S3_ASIC_GUI_ENGINE_HUNG;
	अन्यथा
		पंचांगp &= ~ATOM_S3_ASIC_GUI_ENGINE_HUNG;

	WREG32(adev->bios_scratch_reg_offset + 3, पंचांगp);
पूर्ण

bool amdgpu_atombios_scratch_need_asic_init(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp = RREG32(adev->bios_scratch_reg_offset + 7);

	अगर (पंचांगp & ATOM_S7_ASIC_INIT_COMPLETE_MASK)
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

/* Atom needs data in little endian क्रमmat so swap as appropriate when copying
 * data to or from atom. Note that atom operates on dw units.
 *
 * Use to_le=true when sending data to atom and provide at least
 * ALIGN(num_bytes,4) bytes in the dst buffer.
 *
 * Use to_le=false when receiving data from atom and provide ALIGN(num_bytes,4)
 * byes in the src buffer.
 */
व्योम amdgpu_atombios_copy_swap(u8 *dst, u8 *src, u8 num_bytes, bool to_le)
अणु
#अगर_घोषित __BIG_ENDIAN
	u32 src_पंचांगp[5], dst_पंचांगp[5];
	पूर्णांक i;
	u8 align_num_bytes = ALIGN(num_bytes, 4);

	अगर (to_le) अणु
		स_नकल(src_पंचांगp, src, num_bytes);
		क्रम (i = 0; i < align_num_bytes / 4; i++)
			dst_पंचांगp[i] = cpu_to_le32(src_पंचांगp[i]);
		स_नकल(dst, dst_पंचांगp, align_num_bytes);
	पूर्ण अन्यथा अणु
		स_नकल(src_पंचांगp, src, align_num_bytes);
		क्रम (i = 0; i < align_num_bytes / 4; i++)
			dst_पंचांगp[i] = le32_to_cpu(src_पंचांगp[i]);
		स_नकल(dst, dst_पंचांगp, num_bytes);
	पूर्ण
#अन्यथा
	स_नकल(dst, src, num_bytes);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक amdgpu_atombios_allocate_fb_scratch(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा atom_context *ctx = adev->mode_info.atom_context;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, VRAM_UsageByFirmware);
	uपूर्णांक16_t data_offset;
	पूर्णांक usage_bytes = 0;
	काष्ठा _ATOM_VRAM_USAGE_BY_FIRMWARE *firmware_usage;
	u64 start_addr;
	u64 size;

	अगर (amdgpu_atom_parse_data_header(ctx, index, शून्य, शून्य, शून्य, &data_offset)) अणु
		firmware_usage = (काष्ठा _ATOM_VRAM_USAGE_BY_FIRMWARE *)(ctx->bios + data_offset);

		DRM_DEBUG("atom firmware requested %08x %dkb\n",
			  le32_to_cpu(firmware_usage->asFirmwareVramReserveInfo[0].ulStartAddrUsedByFirmware),
			  le16_to_cpu(firmware_usage->asFirmwareVramReserveInfo[0].usFirmwareUseInKb));

		start_addr = firmware_usage->asFirmwareVramReserveInfo[0].ulStartAddrUsedByFirmware;
		size = firmware_usage->asFirmwareVramReserveInfo[0].usFirmwareUseInKb;

		अगर ((uपूर्णांक32_t)(start_addr & ATOM_VRAM_OPERATION_FLAGS_MASK) ==
			(uपूर्णांक32_t)(ATOM_VRAM_BLOCK_SRIOV_MSG_SHARE_RESERVATION <<
			ATOM_VRAM_OPERATION_FLAGS_SHIFT)) अणु
			/* Firmware request VRAM reservation क्रम SR-IOV */
			adev->mman.fw_vram_usage_start_offset = (start_addr &
				(~ATOM_VRAM_OPERATION_FLAGS_MASK)) << 10;
			adev->mman.fw_vram_usage_size = size << 10;
			/* Use the शेष scratch size */
			usage_bytes = 0;
		पूर्ण अन्यथा अणु
			usage_bytes = le16_to_cpu(firmware_usage->asFirmwareVramReserveInfo[0].usFirmwareUseInKb) * 1024;
		पूर्ण
	पूर्ण
	ctx->scratch_size_bytes = 0;
	अगर (usage_bytes == 0)
		usage_bytes = 20 * 1024;
	/* allocate some scratch memory */
	ctx->scratch = kzalloc(usage_bytes, GFP_KERNEL);
	अगर (!ctx->scratch)
		वापस -ENOMEM;
	ctx->scratch_size_bytes = usage_bytes;
	वापस 0;
पूर्ण

/* ATOM accessor methods */
/*
 * ATOM is an पूर्णांकerpreted byte code stored in tables in the vbios.  The
 * driver रेजिस्टरs callbacks to access रेजिस्टरs and the पूर्णांकerpreter
 * in the driver parses the tables and executes then to program specअगरic
 * actions (set display modes, asic init, etc.).  See amdgpu_atombios.c,
 * atomमूलप्रण.स, and atom.c
 */

/**
 * cail_pll_पढ़ो - पढ़ो PLL रेजिस्टर
 *
 * @info: atom card_info poपूर्णांकer
 * @reg: PLL रेजिस्टर offset
 *
 * Provides a PLL रेजिस्टर accessor क्रम the atom पूर्णांकerpreter (r4xx+).
 * Returns the value of the PLL रेजिस्टर.
 */
अटल uपूर्णांक32_t cail_pll_पढ़ो(काष्ठा card_info *info, uपूर्णांक32_t reg)
अणु
	वापस 0;
पूर्ण

/**
 * cail_pll_ग_लिखो - ग_लिखो PLL रेजिस्टर
 *
 * @info: atom card_info poपूर्णांकer
 * @reg: PLL रेजिस्टर offset
 * @val: value to ग_लिखो to the pll रेजिस्टर
 *
 * Provides a PLL रेजिस्टर accessor क्रम the atom पूर्णांकerpreter (r4xx+).
 */
अटल व्योम cail_pll_ग_लिखो(काष्ठा card_info *info, uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु

पूर्ण

/**
 * cail_mc_पढ़ो - पढ़ो MC (Memory Controller) रेजिस्टर
 *
 * @info: atom card_info poपूर्णांकer
 * @reg: MC रेजिस्टर offset
 *
 * Provides an MC रेजिस्टर accessor क्रम the atom पूर्णांकerpreter (r4xx+).
 * Returns the value of the MC रेजिस्टर.
 */
अटल uपूर्णांक32_t cail_mc_पढ़ो(काष्ठा card_info *info, uपूर्णांक32_t reg)
अणु
	वापस 0;
पूर्ण

/**
 * cail_mc_ग_लिखो - ग_लिखो MC (Memory Controller) रेजिस्टर
 *
 * @info: atom card_info poपूर्णांकer
 * @reg: MC रेजिस्टर offset
 * @val: value to ग_लिखो to the pll रेजिस्टर
 *
 * Provides a MC रेजिस्टर accessor क्रम the atom पूर्णांकerpreter (r4xx+).
 */
अटल व्योम cail_mc_ग_लिखो(काष्ठा card_info *info, uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु

पूर्ण

/**
 * cail_reg_ग_लिखो - ग_लिखो MMIO रेजिस्टर
 *
 * @info: atom card_info poपूर्णांकer
 * @reg: MMIO रेजिस्टर offset
 * @val: value to ग_लिखो to the pll रेजिस्टर
 *
 * Provides a MMIO रेजिस्टर accessor क्रम the atom पूर्णांकerpreter (r4xx+).
 */
अटल व्योम cail_reg_ग_लिखो(काष्ठा card_info *info, uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(info->dev);

	WREG32(reg, val);
पूर्ण

/**
 * cail_reg_पढ़ो - पढ़ो MMIO रेजिस्टर
 *
 * @info: atom card_info poपूर्णांकer
 * @reg: MMIO रेजिस्टर offset
 *
 * Provides an MMIO रेजिस्टर accessor क्रम the atom पूर्णांकerpreter (r4xx+).
 * Returns the value of the MMIO रेजिस्टर.
 */
अटल uपूर्णांक32_t cail_reg_पढ़ो(काष्ठा card_info *info, uपूर्णांक32_t reg)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(info->dev);
	uपूर्णांक32_t r;

	r = RREG32(reg);
	वापस r;
पूर्ण

अटल sमाप_प्रकार amdgpu_atombios_get_vbios_version(काष्ठा device *dev,
						 काष्ठा device_attribute *attr,
						 अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	काष्ठा atom_context *ctx = adev->mode_info.atom_context;

	वापस sysfs_emit(buf, "%s\n", ctx->vbios_version);
पूर्ण

अटल DEVICE_ATTR(vbios_version, 0444, amdgpu_atombios_get_vbios_version,
		   शून्य);

/**
 * amdgpu_atombios_fini - मुक्त the driver info and callbacks क्रम atombios
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Frees the driver info and रेजिस्टर access callbacks क्रम the ATOM
 * पूर्णांकerpreter (r4xx+).
 * Called at driver shutकरोwn.
 */
व्योम amdgpu_atombios_fini(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->mode_info.atom_context) अणु
		kमुक्त(adev->mode_info.atom_context->scratch);
		kमुक्त(adev->mode_info.atom_context->iio);
	पूर्ण
	kमुक्त(adev->mode_info.atom_context);
	adev->mode_info.atom_context = शून्य;
	kमुक्त(adev->mode_info.atom_card_info);
	adev->mode_info.atom_card_info = शून्य;
	device_हटाओ_file(adev->dev, &dev_attr_vbios_version);
पूर्ण

/**
 * amdgpu_atombios_init - init the driver info and callbacks क्रम atombios
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Initializes the driver info and रेजिस्टर access callbacks क्रम the
 * ATOM पूर्णांकerpreter (r4xx+).
 * Returns 0 on sucess, -ENOMEM on failure.
 * Called at driver startup.
 */
पूर्णांक amdgpu_atombios_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा card_info *atom_card_info =
	    kzalloc(माप(काष्ठा card_info), GFP_KERNEL);
	पूर्णांक ret;

	अगर (!atom_card_info)
		वापस -ENOMEM;

	adev->mode_info.atom_card_info = atom_card_info;
	atom_card_info->dev = adev_to_drm(adev);
	atom_card_info->reg_पढ़ो = cail_reg_पढ़ो;
	atom_card_info->reg_ग_लिखो = cail_reg_ग_लिखो;
	atom_card_info->mc_पढ़ो = cail_mc_पढ़ो;
	atom_card_info->mc_ग_लिखो = cail_mc_ग_लिखो;
	atom_card_info->pll_पढ़ो = cail_pll_पढ़ो;
	atom_card_info->pll_ग_लिखो = cail_pll_ग_लिखो;

	adev->mode_info.atom_context = amdgpu_atom_parse(atom_card_info, adev->bios);
	अगर (!adev->mode_info.atom_context) अणु
		amdgpu_atombios_fini(adev);
		वापस -ENOMEM;
	पूर्ण

	mutex_init(&adev->mode_info.atom_context->mutex);
	अगर (adev->is_atom_fw) अणु
		amdgpu_atomfirmware_scratch_regs_init(adev);
		amdgpu_atomfirmware_allocate_fb_scratch(adev);
	पूर्ण अन्यथा अणु
		amdgpu_atombios_scratch_regs_init(adev);
		amdgpu_atombios_allocate_fb_scratch(adev);
	पूर्ण

	ret = device_create_file(adev->dev, &dev_attr_vbios_version);
	अगर (ret) अणु
		DRM_ERROR("Failed to create device file for VBIOS version\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक amdgpu_atombios_get_data_table(काष्ठा amdgpu_device *adev,
				   uपूर्णांक32_t table,
				   uपूर्णांक16_t *size,
				   uपूर्णांक8_t *frev,
				   uपूर्णांक8_t *crev,
				   uपूर्णांक8_t **addr)
अणु
	uपूर्णांक16_t data_start;

	अगर (!amdgpu_atom_parse_data_header(adev->mode_info.atom_context, table,
					   size, frev, crev, &data_start))
		वापस -EINVAL;

	*addr = (uपूर्णांक8_t *)adev->mode_info.atom_context->bios + data_start;

	वापस 0;
पूर्ण
