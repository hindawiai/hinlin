<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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
 * Authors: AMD
 *
 */

#समावेश <linux/slab.h>

#समावेश "dm_services.h"

#समावेश "ObjectID.h"
#समावेश "atomfirmware.h"

#समावेश "dc_bios_types.h"
#समावेश "include/grph_object_ctrl_defs.h"
#समावेश "include/bios_parser_interface.h"
#समावेश "include/i2caux_interface.h"
#समावेश "include/logger_interface.h"

#समावेश "command_table2.h"

#समावेश "bios_parser_helper.h"
#समावेश "command_table_helper2.h"
#समावेश "bios_parser2.h"
#समावेश "bios_parser_types_internal2.h"
#समावेश "bios_parser_interface.h"

#समावेश "bios_parser_common.h"

/* Temporarily add in defines until ObjectID.h patch is updated in a few days */
#अगर_अघोषित GENERIC_OBJECT_ID_BRACKET_LAYOUT
#घोषणा GENERIC_OBJECT_ID_BRACKET_LAYOUT          0x05
#पूर्ण_अगर /* GENERIC_OBJECT_ID_BRACKET_LAYOUT */

#अगर_अघोषित GENERICOBJECT_BRACKET_LAYOUT_ENUM_ID1
#घोषणा GENERICOBJECT_BRACKET_LAYOUT_ENUM_ID1	\
	(GRAPH_OBJECT_TYPE_GENERIC << OBJECT_TYPE_SHIFT |\
	GRAPH_OBJECT_ENUM_ID1 << ENUM_ID_SHIFT |\
	GENERIC_OBJECT_ID_BRACKET_LAYOUT << OBJECT_ID_SHIFT)
#पूर्ण_अगर /* GENERICOBJECT_BRACKET_LAYOUT_ENUM_ID1 */

#अगर_अघोषित GENERICOBJECT_BRACKET_LAYOUT_ENUM_ID2
#घोषणा GENERICOBJECT_BRACKET_LAYOUT_ENUM_ID2	\
	(GRAPH_OBJECT_TYPE_GENERIC << OBJECT_TYPE_SHIFT |\
	GRAPH_OBJECT_ENUM_ID2 << ENUM_ID_SHIFT |\
	GENERIC_OBJECT_ID_BRACKET_LAYOUT << OBJECT_ID_SHIFT)
#पूर्ण_अगर /* GENERICOBJECT_BRACKET_LAYOUT_ENUM_ID2 */

#घोषणा DC_LOGGER \
	bp->base.ctx->logger

#घोषणा LAST_RECORD_TYPE 0xff
#घोषणा SMU9_SYSPLL0_ID  0

काष्ठा i2c_id_config_access अणु
	uपूर्णांक8_t bfI2C_LineMux:4;
	uपूर्णांक8_t bfHW_EngineID:3;
	uपूर्णांक8_t bfHW_Capable:1;
	uपूर्णांक8_t ucAccess;
पूर्ण;

अटल क्रमागत bp_result get_gpio_i2c_info(काष्ठा bios_parser *bp,
	काष्ठा atom_i2c_record *record,
	काष्ठा graphics_object_i2c_info *info);

अटल क्रमागत bp_result bios_parser_get_firmware_info(
	काष्ठा dc_bios *dcb,
	काष्ठा dc_firmware_info *info);

अटल क्रमागत bp_result bios_parser_get_encoder_cap_info(
	काष्ठा dc_bios *dcb,
	काष्ठा graphics_object_id object_id,
	काष्ठा bp_encoder_cap_info *info);

अटल क्रमागत bp_result get_firmware_info_v3_1(
	काष्ठा bios_parser *bp,
	काष्ठा dc_firmware_info *info);

अटल क्रमागत bp_result get_firmware_info_v3_2(
	काष्ठा bios_parser *bp,
	काष्ठा dc_firmware_info *info);

अटल काष्ठा atom_hpd_पूर्णांक_record *get_hpd_record(काष्ठा bios_parser *bp,
		काष्ठा atom_display_object_path_v2 *object);

अटल काष्ठा atom_encoder_caps_record *get_encoder_cap_record(
	काष्ठा bios_parser *bp,
	काष्ठा atom_display_object_path_v2 *object);

#घोषणा BIOS_IMAGE_SIZE_OFFSET 2
#घोषणा BIOS_IMAGE_SIZE_UNIT 512

#घोषणा DATA_TABLES(table) (bp->master_data_tbl->listOfdatatables.table)

अटल व्योम bios_parser2_deकाष्ठा(काष्ठा bios_parser *bp)
अणु
	kमुक्त(bp->base.bios_local_image);
	kमुक्त(bp->base.पूर्णांकegrated_info);
पूर्ण

अटल व्योम firmware_parser_destroy(काष्ठा dc_bios **dcb)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(*dcb);

	अगर (!bp) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	bios_parser2_deकाष्ठा(bp);

	kमुक्त(bp);
	*dcb = शून्य;
पूर्ण

अटल व्योम get_atom_data_table_revision(
	काष्ठा atom_common_table_header *atom_data_tbl,
	काष्ठा atom_data_revision *tbl_revision)
अणु
	अगर (!tbl_revision)
		वापस;

	/* initialize the revision to 0 which is invalid revision */
	tbl_revision->major = 0;
	tbl_revision->minor = 0;

	अगर (!atom_data_tbl)
		वापस;

	tbl_revision->major =
			(uपूर्णांक32_t) atom_data_tbl->क्रमmat_revision & 0x3f;
	tbl_revision->minor =
			(uपूर्णांक32_t) atom_data_tbl->content_revision & 0x3f;
पूर्ण

/* BIOS oject table displaypath is per connector.
 * There is extra path not क्रम connector. BIOS fill its encoderid as 0
 */
अटल uपूर्णांक8_t bios_parser_get_connectors_number(काष्ठा dc_bios *dcb)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	अचिन्हित पूर्णांक count = 0;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < bp->object_info_tbl.v1_4->number_of_path; i++) अणु
		अगर (bp->object_info_tbl.v1_4->display_path[i].encoderobjid != 0)
			count++;
	पूर्ण
	वापस count;
पूर्ण

अटल काष्ठा graphics_object_id bios_parser_get_connector_id(
	काष्ठा dc_bios *dcb,
	uपूर्णांक8_t i)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	काष्ठा graphics_object_id object_id = dal_graphics_object_id_init(
		0, ENUM_ID_UNKNOWN, OBJECT_TYPE_UNKNOWN);
	काष्ठा object_info_table *tbl = &bp->object_info_tbl;
	काष्ठा display_object_info_table_v1_4 *v1_4 = tbl->v1_4;

	अगर (v1_4->number_of_path > i) अणु
		/* If display_objid is generic object id,  the encoderObj
		 * /extencoderobjId should be 0
		 */
		अगर (v1_4->display_path[i].encoderobjid != 0 &&
				v1_4->display_path[i].display_objid != 0)
			object_id = object_id_from_bios_object_id(
					v1_4->display_path[i].display_objid);
	पूर्ण

	वापस object_id;
पूर्ण

अटल क्रमागत bp_result bios_parser_get_src_obj(काष्ठा dc_bios *dcb,
	काष्ठा graphics_object_id object_id, uपूर्णांक32_t index,
	काष्ठा graphics_object_id *src_object_id)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	अचिन्हित पूर्णांक i;
	क्रमागत bp_result  bp_result = BP_RESULT_BADINPUT;
	काष्ठा graphics_object_id obj_id = अणु0पूर्ण;
	काष्ठा object_info_table *tbl = &bp->object_info_tbl;

	अगर (!src_object_id)
		वापस bp_result;

	चयन (object_id.type) अणु
	/* Encoder's Source is GPU.  BIOS करोes not provide GPU, since all
	 * displaypaths poपूर्णांक to same GPU (0x1100).  Hardcode GPU object type
	 */
	हाल OBJECT_TYPE_ENCODER:
		/* TODO: since num of src must be less than 2.
		 * If found in क्रम loop, should अवरोध.
		 * DAL2 implementation may be changed too
		 */
		क्रम (i = 0; i < tbl->v1_4->number_of_path; i++) अणु
			obj_id = object_id_from_bios_object_id(
			tbl->v1_4->display_path[i].encoderobjid);
			अगर (object_id.type == obj_id.type &&
					object_id.id == obj_id.id &&
						object_id.क्रमागत_id ==
							obj_id.क्रमागत_id) अणु
				*src_object_id =
				object_id_from_bios_object_id(0x1100);
				/* अवरोध; */
			पूर्ण
		पूर्ण
		bp_result = BP_RESULT_OK;
		अवरोध;
	हाल OBJECT_TYPE_CONNECTOR:
		क्रम (i = 0; i < tbl->v1_4->number_of_path; i++) अणु
			obj_id = object_id_from_bios_object_id(
				tbl->v1_4->display_path[i].display_objid);

			अगर (object_id.type == obj_id.type &&
				object_id.id == obj_id.id &&
					object_id.क्रमागत_id == obj_id.क्रमागत_id) अणु
				*src_object_id =
				object_id_from_bios_object_id(
				tbl->v1_4->display_path[i].encoderobjid);
				/* अवरोध; */
			पूर्ण
		पूर्ण
		bp_result = BP_RESULT_OK;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस bp_result;
पूर्ण

/* from graphics_object_id, find display path which includes the object_id */
अटल काष्ठा atom_display_object_path_v2 *get_bios_object(
		काष्ठा bios_parser *bp,
		काष्ठा graphics_object_id id)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा graphics_object_id obj_id = अणु0पूर्ण;

	चयन (id.type) अणु
	हाल OBJECT_TYPE_ENCODER:
		क्रम (i = 0; i < bp->object_info_tbl.v1_4->number_of_path; i++) अणु
			obj_id = object_id_from_bios_object_id(
					bp->object_info_tbl.v1_4->display_path[i].encoderobjid);
			अगर (id.type == obj_id.type && id.id == obj_id.id
					&& id.क्रमागत_id == obj_id.क्रमागत_id)
				वापस &bp->object_info_tbl.v1_4->display_path[i];
		पूर्ण
		fallthrough;
	हाल OBJECT_TYPE_CONNECTOR:
	हाल OBJECT_TYPE_GENERIC:
		/* Both Generic and Connector Object ID
		 * will be stored on display_objid
		 */
		क्रम (i = 0; i < bp->object_info_tbl.v1_4->number_of_path; i++) अणु
			obj_id = object_id_from_bios_object_id(
					bp->object_info_tbl.v1_4->display_path[i].display_objid);
			अगर (id.type == obj_id.type && id.id == obj_id.id
					&& id.क्रमागत_id == obj_id.क्रमागत_id)
				वापस &bp->object_info_tbl.v1_4->display_path[i];
		पूर्ण
		fallthrough;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल क्रमागत bp_result bios_parser_get_i2c_info(काष्ठा dc_bios *dcb,
	काष्ठा graphics_object_id id,
	काष्ठा graphics_object_i2c_info *info)
अणु
	uपूर्णांक32_t offset;
	काष्ठा atom_display_object_path_v2 *object;
	काष्ठा atom_common_record_header *header;
	काष्ठा atom_i2c_record *record;
	काष्ठा atom_i2c_record dummy_record = अणु0पूर्ण;
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);

	अगर (!info)
		वापस BP_RESULT_BADINPUT;

	अगर (id.type == OBJECT_TYPE_GENERIC) अणु
		dummy_record.i2c_id = id.id;

		अगर (get_gpio_i2c_info(bp, &dummy_record, info) == BP_RESULT_OK)
			वापस BP_RESULT_OK;
		अन्यथा
			वापस BP_RESULT_NORECORD;
	पूर्ण

	object = get_bios_object(bp, id);

	अगर (!object)
		वापस BP_RESULT_BADINPUT;

	offset = object->disp_recorकरोffset + bp->object_info_tbl_offset;

	क्रम (;;) अणु
		header = GET_IMAGE(काष्ठा atom_common_record_header, offset);

		अगर (!header)
			वापस BP_RESULT_BADBIOSTABLE;

		अगर (header->record_type == LAST_RECORD_TYPE ||
			!header->record_size)
			अवरोध;

		अगर (header->record_type == ATOM_I2C_RECORD_TYPE
			&& माप(काष्ठा atom_i2c_record) <=
							header->record_size) अणु
			/* get the I2C info */
			record = (काष्ठा atom_i2c_record *) header;

			अगर (get_gpio_i2c_info(bp, record, info) ==
								BP_RESULT_OK)
				वापस BP_RESULT_OK;
		पूर्ण

		offset += header->record_size;
	पूर्ण

	वापस BP_RESULT_NORECORD;
पूर्ण

अटल क्रमागत bp_result get_gpio_i2c_info(
	काष्ठा bios_parser *bp,
	काष्ठा atom_i2c_record *record,
	काष्ठा graphics_object_i2c_info *info)
अणु
	काष्ठा atom_gpio_pin_lut_v2_1 *header;
	uपूर्णांक32_t count = 0;
	अचिन्हित पूर्णांक table_index = 0;
	bool find_valid = false;

	अगर (!info)
		वापस BP_RESULT_BADINPUT;

	/* get the GPIO_I2C info */
	अगर (!DATA_TABLES(gpio_pin_lut))
		वापस BP_RESULT_BADBIOSTABLE;

	header = GET_IMAGE(काष्ठा atom_gpio_pin_lut_v2_1,
					DATA_TABLES(gpio_pin_lut));
	अगर (!header)
		वापस BP_RESULT_BADBIOSTABLE;

	अगर (माप(काष्ठा atom_common_table_header) +
			माप(काष्ठा atom_gpio_pin_assignment)	>
			le16_to_cpu(header->table_header.काष्ठाuresize))
		वापस BP_RESULT_BADBIOSTABLE;

	/* TODO: is version change? */
	अगर (header->table_header.content_revision != 1)
		वापस BP_RESULT_UNSUPPORTED;

	/* get data count */
	count = (le16_to_cpu(header->table_header.काष्ठाuresize)
			- माप(काष्ठा atom_common_table_header))
				/ माप(काष्ठा atom_gpio_pin_assignment);

	क्रम (table_index = 0; table_index < count; table_index++) अणु
		अगर (((record->i2c_id & I2C_HW_CAP) == (
		header->gpio_pin[table_index].gpio_id &
						I2C_HW_CAP)) &&
		((record->i2c_id & I2C_HW_ENGINE_ID_MASK)  ==
		(header->gpio_pin[table_index].gpio_id &
					I2C_HW_ENGINE_ID_MASK)) &&
		((record->i2c_id & I2C_HW_LANE_MUX) ==
		(header->gpio_pin[table_index].gpio_id &
						I2C_HW_LANE_MUX))) अणु
			/* still valid */
			find_valid = true;
			अवरोध;
		पूर्ण
	पूर्ण

	/* If we करोn't find the entry that we are looking क्रम then
	 *  we will वापस BP_Result_BadBiosTable.
	 */
	अगर (find_valid == false)
		वापस BP_RESULT_BADBIOSTABLE;

	/* get the GPIO_I2C_INFO */
	info->i2c_hw_assist = (record->i2c_id & I2C_HW_CAP) ? true : false;
	info->i2c_line = record->i2c_id & I2C_HW_LANE_MUX;
	info->i2c_engine_id = (record->i2c_id & I2C_HW_ENGINE_ID_MASK) >> 4;
	info->i2c_slave_address = record->i2c_slave_addr;

	/* TODO: check how to get रेजिस्टर offset क्रम en, Y, etc. */
	info->gpio_info.clk_a_रेजिस्टर_index =
			le16_to_cpu(
			header->gpio_pin[table_index].data_a_reg_index);
	info->gpio_info.clk_a_shअगरt =
			header->gpio_pin[table_index].gpio_bitshअगरt;

	वापस BP_RESULT_OK;
पूर्ण

अटल क्रमागत bp_result bios_parser_get_hpd_info(
	काष्ठा dc_bios *dcb,
	काष्ठा graphics_object_id id,
	काष्ठा graphics_object_hpd_info *info)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	काष्ठा atom_display_object_path_v2 *object;
	काष्ठा atom_hpd_पूर्णांक_record *record = शून्य;

	अगर (!info)
		वापस BP_RESULT_BADINPUT;

	object = get_bios_object(bp, id);

	अगर (!object)
		वापस BP_RESULT_BADINPUT;

	record = get_hpd_record(bp, object);

	अगर (record != शून्य) अणु
		info->hpd_पूर्णांक_gpio_uid = record->pin_id;
		info->hpd_active = record->plugin_pin_state;
		वापस BP_RESULT_OK;
	पूर्ण

	वापस BP_RESULT_NORECORD;
पूर्ण

अटल काष्ठा atom_hpd_पूर्णांक_record *get_hpd_record(
	काष्ठा bios_parser *bp,
	काष्ठा atom_display_object_path_v2 *object)
अणु
	काष्ठा atom_common_record_header *header;
	uपूर्णांक32_t offset;

	अगर (!object) अणु
		BREAK_TO_DEBUGGER(); /* Invalid object */
		वापस शून्य;
	पूर्ण

	offset = le16_to_cpu(object->disp_recorकरोffset)
			+ bp->object_info_tbl_offset;

	क्रम (;;) अणु
		header = GET_IMAGE(काष्ठा atom_common_record_header, offset);

		अगर (!header)
			वापस शून्य;

		अगर (header->record_type == LAST_RECORD_TYPE ||
			!header->record_size)
			अवरोध;

		अगर (header->record_type == ATOM_HPD_INT_RECORD_TYPE
			&& माप(काष्ठा atom_hpd_पूर्णांक_record) <=
							header->record_size)
			वापस (काष्ठा atom_hpd_पूर्णांक_record *) header;

		offset += header->record_size;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * bios_parser_get_gpio_pin_info
 * Get GpioPin inक्रमmation of input gpio id
 *
 * @dcb:     poपूर्णांकer to the DC BIOS
 * @gpio_id: GPIO ID
 * @info:    GpioPin inक्रमmation काष्ठाure
 * वापस: Bios parser result code
 * note:
 *  to get the GPIO PIN INFO, we need:
 *  1. get the GPIO_ID from other object table, see GetHPDInfo()
 *  2. in DATA_TABLE.GPIO_Pin_LUT, search all records,
 *	to get the रेजिस्टरA  offset/mask
 */
अटल क्रमागत bp_result bios_parser_get_gpio_pin_info(
	काष्ठा dc_bios *dcb,
	uपूर्णांक32_t gpio_id,
	काष्ठा gpio_pin_info *info)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	काष्ठा atom_gpio_pin_lut_v2_1 *header;
	uपूर्णांक32_t count = 0;
	uपूर्णांक32_t i = 0;

	अगर (!DATA_TABLES(gpio_pin_lut))
		वापस BP_RESULT_BADBIOSTABLE;

	header = GET_IMAGE(काष्ठा atom_gpio_pin_lut_v2_1,
						DATA_TABLES(gpio_pin_lut));
	अगर (!header)
		वापस BP_RESULT_BADBIOSTABLE;

	अगर (माप(काष्ठा atom_common_table_header) +
			माप(काष्ठा atom_gpio_pin_assignment)
			> le16_to_cpu(header->table_header.काष्ठाuresize))
		वापस BP_RESULT_BADBIOSTABLE;

	अगर (header->table_header.content_revision != 1)
		वापस BP_RESULT_UNSUPPORTED;

	/* Temporary hard code gpio pin info */
#अगर defined(FOR_SIMNOW_BOOT)
	अणु
		काष्ठा  atom_gpio_pin_assignment  gpio_pin[8] = अणु
				अणु0x5db5, 0, 0, 1, 0पूर्ण,
				अणु0x5db5, 8, 8, 2, 0पूर्ण,
				अणु0x5db5, 0x10, 0x10, 3, 0पूर्ण,
				अणु0x5db5, 0x18, 0x14, 4, 0पूर्ण,
				अणु0x5db5, 0x1A, 0x18, 5, 0पूर्ण,
				अणु0x5db5, 0x1C, 0x1C, 6, 0पूर्ण,
		पूर्ण;

		count = 6;
		स_हटाओ(header->gpio_pin, gpio_pin, माप(gpio_pin));
	पूर्ण
#अन्यथा
	count = (le16_to_cpu(header->table_header.काष्ठाuresize)
			- माप(काष्ठा atom_common_table_header))
				/ माप(काष्ठा atom_gpio_pin_assignment);
#पूर्ण_अगर
	क्रम (i = 0; i < count; ++i) अणु
		अगर (header->gpio_pin[i].gpio_id != gpio_id)
			जारी;

		info->offset =
			(uपूर्णांक32_t) le16_to_cpu(
					header->gpio_pin[i].data_a_reg_index);
		info->offset_y = info->offset + 2;
		info->offset_en = info->offset + 1;
		info->offset_mask = info->offset - 1;

		info->mask = (uपूर्णांक32_t) (1 <<
			header->gpio_pin[i].gpio_bitshअगरt);
		info->mask_y = info->mask + 2;
		info->mask_en = info->mask + 1;
		info->mask_mask = info->mask - 1;

		वापस BP_RESULT_OK;
	पूर्ण

	वापस BP_RESULT_NORECORD;
पूर्ण

अटल काष्ठा device_id device_type_from_device_id(uपूर्णांक16_t device_id)
अणु

	काष्ठा device_id result_device_id;

	result_device_id.raw_device_tag = device_id;

	चयन (device_id) अणु
	हाल ATOM_DISPLAY_LCD1_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_LCD;
		result_device_id.क्रमागत_id = 1;
		अवरोध;

	हाल ATOM_DISPLAY_DFP1_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_DFP;
		result_device_id.क्रमागत_id = 1;
		अवरोध;

	हाल ATOM_DISPLAY_DFP2_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_DFP;
		result_device_id.क्रमागत_id = 2;
		अवरोध;

	हाल ATOM_DISPLAY_DFP3_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_DFP;
		result_device_id.क्रमागत_id = 3;
		अवरोध;

	हाल ATOM_DISPLAY_DFP4_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_DFP;
		result_device_id.क्रमागत_id = 4;
		अवरोध;

	हाल ATOM_DISPLAY_DFP5_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_DFP;
		result_device_id.क्रमागत_id = 5;
		अवरोध;

	हाल ATOM_DISPLAY_DFP6_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_DFP;
		result_device_id.क्रमागत_id = 6;
		अवरोध;

	शेष:
		BREAK_TO_DEBUGGER(); /* Invalid device Id */
		result_device_id.device_type = DEVICE_TYPE_UNKNOWN;
		result_device_id.क्रमागत_id = 0;
	पूर्ण
	वापस result_device_id;
पूर्ण

अटल क्रमागत bp_result bios_parser_get_device_tag(
	काष्ठा dc_bios *dcb,
	काष्ठा graphics_object_id connector_object_id,
	uपूर्णांक32_t device_tag_index,
	काष्ठा connector_device_tag_info *info)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	काष्ठा atom_display_object_path_v2 *object;

	अगर (!info)
		वापस BP_RESULT_BADINPUT;

	/* getBiosObject will वापस MXM object */
	object = get_bios_object(bp, connector_object_id);

	अगर (!object) अणु
		BREAK_TO_DEBUGGER(); /* Invalid object id */
		वापस BP_RESULT_BADINPUT;
	पूर्ण

	info->acpi_device = 0; /* BIOS no दीर्घer provides this */
	info->dev_id = device_type_from_device_id(object->device_tag);

	वापस BP_RESULT_OK;
पूर्ण

अटल क्रमागत bp_result get_ss_info_v4_1(
	काष्ठा bios_parser *bp,
	uपूर्णांक32_t id,
	uपूर्णांक32_t index,
	काष्ठा spपढ़ो_spectrum_info *ss_info)
अणु
	क्रमागत bp_result result = BP_RESULT_OK;
	काष्ठा atom_display_controller_info_v4_1 *disp_cntl_tbl = शून्य;
	काष्ठा atom_smu_info_v3_3 *smu_info = शून्य;

	अगर (!ss_info)
		वापस BP_RESULT_BADINPUT;

	अगर (!DATA_TABLES(dce_info))
		वापस BP_RESULT_BADBIOSTABLE;

	disp_cntl_tbl =  GET_IMAGE(काष्ठा atom_display_controller_info_v4_1,
							DATA_TABLES(dce_info));
	अगर (!disp_cntl_tbl)
		वापस BP_RESULT_BADBIOSTABLE;


	ss_info->type.STEP_AND_DELAY_INFO = false;
	ss_info->spपढ़ो_percentage_भागider = 1000;
	/* BIOS no दीर्घer uses target घड़ी.  Always enable क्रम now */
	ss_info->target_घड़ी_range = 0xffffffff;

	चयन (id) अणु
	हाल AS_SIGNAL_TYPE_DVI:
		ss_info->spपढ़ो_spectrum_percentage =
				disp_cntl_tbl->dvi_ss_percentage;
		ss_info->spपढ़ो_spectrum_range =
				disp_cntl_tbl->dvi_ss_rate_10hz * 10;
		अगर (disp_cntl_tbl->dvi_ss_mode & ATOM_SS_CENTRE_SPREAD_MODE)
			ss_info->type.CENTER_MODE = true;
		अवरोध;
	हाल AS_SIGNAL_TYPE_HDMI:
		ss_info->spपढ़ो_spectrum_percentage =
				disp_cntl_tbl->hdmi_ss_percentage;
		ss_info->spपढ़ो_spectrum_range =
				disp_cntl_tbl->hdmi_ss_rate_10hz * 10;
		अगर (disp_cntl_tbl->hdmi_ss_mode & ATOM_SS_CENTRE_SPREAD_MODE)
			ss_info->type.CENTER_MODE = true;
		अवरोध;
	/* TODO LVDS not support anymore? */
	हाल AS_SIGNAL_TYPE_DISPLAY_PORT:
		ss_info->spपढ़ो_spectrum_percentage =
				disp_cntl_tbl->dp_ss_percentage;
		ss_info->spपढ़ो_spectrum_range =
				disp_cntl_tbl->dp_ss_rate_10hz * 10;
		अगर (disp_cntl_tbl->dp_ss_mode & ATOM_SS_CENTRE_SPREAD_MODE)
			ss_info->type.CENTER_MODE = true;
		अवरोध;
	हाल AS_SIGNAL_TYPE_GPU_PLL:
		/* atom_firmware: DAL only get data from dce_info table.
		 * अगर data within smu_info is needed क्रम DAL, VBIOS should
		 * copy it पूर्णांकo dce_info
		 */
		result = BP_RESULT_UNSUPPORTED;
		अवरोध;
	हाल AS_SIGNAL_TYPE_XGMI:
		smu_info =  GET_IMAGE(काष्ठा atom_smu_info_v3_3,
				      DATA_TABLES(smu_info));
		अगर (!smu_info)
			वापस BP_RESULT_BADBIOSTABLE;

		ss_info->spपढ़ो_spectrum_percentage =
				smu_info->waflclk_ss_percentage;
		ss_info->spपढ़ो_spectrum_range =
				smu_info->gpuclk_ss_rate_10hz * 10;
		अगर (smu_info->waflclk_ss_mode & ATOM_SS_CENTRE_SPREAD_MODE)
			ss_info->type.CENTER_MODE = true;
		अवरोध;
	शेष:
		result = BP_RESULT_UNSUPPORTED;
	पूर्ण

	वापस result;
पूर्ण

अटल क्रमागत bp_result get_ss_info_v4_2(
	काष्ठा bios_parser *bp,
	uपूर्णांक32_t id,
	uपूर्णांक32_t index,
	काष्ठा spपढ़ो_spectrum_info *ss_info)
अणु
	क्रमागत bp_result result = BP_RESULT_OK;
	काष्ठा atom_display_controller_info_v4_2 *disp_cntl_tbl = शून्य;
	काष्ठा atom_smu_info_v3_1 *smu_info = शून्य;

	अगर (!ss_info)
		वापस BP_RESULT_BADINPUT;

	अगर (!DATA_TABLES(dce_info))
		वापस BP_RESULT_BADBIOSTABLE;

	अगर (!DATA_TABLES(smu_info))
		वापस BP_RESULT_BADBIOSTABLE;

	disp_cntl_tbl =  GET_IMAGE(काष्ठा atom_display_controller_info_v4_2,
							DATA_TABLES(dce_info));
	अगर (!disp_cntl_tbl)
		वापस BP_RESULT_BADBIOSTABLE;

	smu_info =  GET_IMAGE(काष्ठा atom_smu_info_v3_1, DATA_TABLES(smu_info));
	अगर (!smu_info)
		वापस BP_RESULT_BADBIOSTABLE;

	ss_info->type.STEP_AND_DELAY_INFO = false;
	ss_info->spपढ़ो_percentage_भागider = 1000;
	/* BIOS no दीर्घer uses target घड़ी.  Always enable क्रम now */
	ss_info->target_घड़ी_range = 0xffffffff;

	चयन (id) अणु
	हाल AS_SIGNAL_TYPE_DVI:
		ss_info->spपढ़ो_spectrum_percentage =
				disp_cntl_tbl->dvi_ss_percentage;
		ss_info->spपढ़ो_spectrum_range =
				disp_cntl_tbl->dvi_ss_rate_10hz * 10;
		अगर (disp_cntl_tbl->dvi_ss_mode & ATOM_SS_CENTRE_SPREAD_MODE)
			ss_info->type.CENTER_MODE = true;
		अवरोध;
	हाल AS_SIGNAL_TYPE_HDMI:
		ss_info->spपढ़ो_spectrum_percentage =
				disp_cntl_tbl->hdmi_ss_percentage;
		ss_info->spपढ़ो_spectrum_range =
				disp_cntl_tbl->hdmi_ss_rate_10hz * 10;
		अगर (disp_cntl_tbl->hdmi_ss_mode & ATOM_SS_CENTRE_SPREAD_MODE)
			ss_info->type.CENTER_MODE = true;
		अवरोध;
	/* TODO LVDS not support anymore? */
	हाल AS_SIGNAL_TYPE_DISPLAY_PORT:
		ss_info->spपढ़ो_spectrum_percentage =
				smu_info->gpuclk_ss_percentage;
		ss_info->spपढ़ो_spectrum_range =
				smu_info->gpuclk_ss_rate_10hz * 10;
		अगर (smu_info->gpuclk_ss_mode & ATOM_SS_CENTRE_SPREAD_MODE)
			ss_info->type.CENTER_MODE = true;
		अवरोध;
	हाल AS_SIGNAL_TYPE_GPU_PLL:
		/* atom_firmware: DAL only get data from dce_info table.
		 * अगर data within smu_info is needed क्रम DAL, VBIOS should
		 * copy it पूर्णांकo dce_info
		 */
		result = BP_RESULT_UNSUPPORTED;
		अवरोध;
	शेष:
		result = BP_RESULT_UNSUPPORTED;
	पूर्ण

	वापस result;
पूर्ण

/**
 * bios_parser_get_spपढ़ो_spectrum_info
 * Get spपढ़ो spectrum inक्रमmation from the ASIC_InternalSS_Info(ver 2.1 or
 * ver 3.1) or SS_Info table from the VBIOS. Currently ASIC_InternalSS_Info
 * ver 2.1 can co-exist with SS_Info table. Expect ASIC_InternalSS_Info
 * ver 3.1,
 * there is only one entry क्रम each संकेत /ss id.  However, there is
 * no planning of supporting multiple spपढ़ो Sprectum entry क्रम EverGreen
 * @dcb:     poपूर्णांकer to the DC BIOS
 * @संकेत:  ASSignalType to be converted to info index
 * @index:   number of entries that match the converted info index
 * @ss_info: sprectrum inक्रमmation काष्ठाure,
 * वापस: Bios parser result code
 */
अटल क्रमागत bp_result bios_parser_get_spपढ़ो_spectrum_info(
	काष्ठा dc_bios *dcb,
	क्रमागत as_संकेत_type संकेत,
	uपूर्णांक32_t index,
	काष्ठा spपढ़ो_spectrum_info *ss_info)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	क्रमागत bp_result result = BP_RESULT_UNSUPPORTED;
	काष्ठा atom_common_table_header *header;
	काष्ठा atom_data_revision tbl_revision;

	अगर (!ss_info) /* check क्रम bad input */
		वापस BP_RESULT_BADINPUT;

	अगर (!DATA_TABLES(dce_info))
		वापस BP_RESULT_UNSUPPORTED;

	header = GET_IMAGE(काष्ठा atom_common_table_header,
						DATA_TABLES(dce_info));
	get_atom_data_table_revision(header, &tbl_revision);

	चयन (tbl_revision.major) अणु
	हाल 4:
		चयन (tbl_revision.minor) अणु
		हाल 1:
			वापस get_ss_info_v4_1(bp, संकेत, index, ss_info);
		हाल 2:
		हाल 3:
			वापस get_ss_info_v4_2(bp, संकेत, index, ss_info);
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	/* there can not be more then one entry क्रम SS Info table */
	वापस result;
पूर्ण

अटल क्रमागत bp_result get_soc_bb_info_v4_4(
	काष्ठा bios_parser *bp,
	काष्ठा bp_soc_bb_info *soc_bb_info)
अणु
	क्रमागत bp_result result = BP_RESULT_OK;
	काष्ठा atom_display_controller_info_v4_4 *disp_cntl_tbl = शून्य;

	अगर (!soc_bb_info)
		वापस BP_RESULT_BADINPUT;

	अगर (!DATA_TABLES(dce_info))
		वापस BP_RESULT_BADBIOSTABLE;

	अगर (!DATA_TABLES(smu_info))
		वापस BP_RESULT_BADBIOSTABLE;

	disp_cntl_tbl =  GET_IMAGE(काष्ठा atom_display_controller_info_v4_4,
							DATA_TABLES(dce_info));
	अगर (!disp_cntl_tbl)
		वापस BP_RESULT_BADBIOSTABLE;

	soc_bb_info->dram_घड़ी_change_latency_100ns = disp_cntl_tbl->max_mclk_chg_lat;
	soc_bb_info->dram_sr_enter_निकास_latency_100ns = disp_cntl_tbl->max_sr_enter_निकास_lat;
	soc_bb_info->dram_sr_निकास_latency_100ns = disp_cntl_tbl->max_sr_निकास_lat;

	वापस result;
पूर्ण

अटल क्रमागत bp_result bios_parser_get_soc_bb_info(
	काष्ठा dc_bios *dcb,
	काष्ठा bp_soc_bb_info *soc_bb_info)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	क्रमागत bp_result result = BP_RESULT_UNSUPPORTED;
	काष्ठा atom_common_table_header *header;
	काष्ठा atom_data_revision tbl_revision;

	अगर (!soc_bb_info) /* check क्रम bad input */
		वापस BP_RESULT_BADINPUT;

	अगर (!DATA_TABLES(dce_info))
		वापस BP_RESULT_UNSUPPORTED;

	header = GET_IMAGE(काष्ठा atom_common_table_header,
						DATA_TABLES(dce_info));
	get_atom_data_table_revision(header, &tbl_revision);

	चयन (tbl_revision.major) अणु
	हाल 4:
		चयन (tbl_revision.minor) अणु
		हाल 1:
		हाल 2:
		हाल 3:
			अवरोध;
		हाल 4:
			result = get_soc_bb_info_v4_4(bp, soc_bb_info);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

अटल क्रमागत bp_result get_disp_caps_v4_1(
	काष्ठा bios_parser *bp,
	uपूर्णांक8_t *dce_caps)
अणु
	क्रमागत bp_result result = BP_RESULT_OK;
	काष्ठा atom_display_controller_info_v4_1 *disp_cntl_tbl = शून्य;

	अगर (!dce_caps)
		वापस BP_RESULT_BADINPUT;

	अगर (!DATA_TABLES(dce_info))
		वापस BP_RESULT_BADBIOSTABLE;

	disp_cntl_tbl = GET_IMAGE(काष्ठा atom_display_controller_info_v4_1,
							DATA_TABLES(dce_info));

	अगर (!disp_cntl_tbl)
		वापस BP_RESULT_BADBIOSTABLE;

	*dce_caps = disp_cntl_tbl->display_caps;

	वापस result;
पूर्ण

अटल क्रमागत bp_result get_disp_caps_v4_2(
	काष्ठा bios_parser *bp,
	uपूर्णांक8_t *dce_caps)
अणु
	क्रमागत bp_result result = BP_RESULT_OK;
	काष्ठा atom_display_controller_info_v4_2 *disp_cntl_tbl = शून्य;

	अगर (!dce_caps)
		वापस BP_RESULT_BADINPUT;

	अगर (!DATA_TABLES(dce_info))
		वापस BP_RESULT_BADBIOSTABLE;

	disp_cntl_tbl = GET_IMAGE(काष्ठा atom_display_controller_info_v4_2,
							DATA_TABLES(dce_info));

	अगर (!disp_cntl_tbl)
		वापस BP_RESULT_BADBIOSTABLE;

	*dce_caps = disp_cntl_tbl->display_caps;

	वापस result;
पूर्ण

अटल क्रमागत bp_result get_disp_caps_v4_3(
	काष्ठा bios_parser *bp,
	uपूर्णांक8_t *dce_caps)
अणु
	क्रमागत bp_result result = BP_RESULT_OK;
	काष्ठा atom_display_controller_info_v4_3 *disp_cntl_tbl = शून्य;

	अगर (!dce_caps)
		वापस BP_RESULT_BADINPUT;

	अगर (!DATA_TABLES(dce_info))
		वापस BP_RESULT_BADBIOSTABLE;

	disp_cntl_tbl = GET_IMAGE(काष्ठा atom_display_controller_info_v4_3,
							DATA_TABLES(dce_info));

	अगर (!disp_cntl_tbl)
		वापस BP_RESULT_BADBIOSTABLE;

	*dce_caps = disp_cntl_tbl->display_caps;

	वापस result;
पूर्ण

अटल क्रमागत bp_result get_disp_caps_v4_4(
	काष्ठा bios_parser *bp,
	uपूर्णांक8_t *dce_caps)
अणु
	क्रमागत bp_result result = BP_RESULT_OK;
	काष्ठा atom_display_controller_info_v4_4 *disp_cntl_tbl = शून्य;

	अगर (!dce_caps)
		वापस BP_RESULT_BADINPUT;

	अगर (!DATA_TABLES(dce_info))
		वापस BP_RESULT_BADBIOSTABLE;

	disp_cntl_tbl = GET_IMAGE(काष्ठा atom_display_controller_info_v4_4,
							DATA_TABLES(dce_info));

	अगर (!disp_cntl_tbl)
		वापस BP_RESULT_BADBIOSTABLE;

	*dce_caps = disp_cntl_tbl->display_caps;

	वापस result;
पूर्ण

अटल क्रमागत bp_result bios_parser_get_lttpr_पूर्णांकerop(
	काष्ठा dc_bios *dcb,
	uपूर्णांक8_t *dce_caps)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	क्रमागत bp_result result = BP_RESULT_UNSUPPORTED;
	काष्ठा atom_common_table_header *header;
	काष्ठा atom_data_revision tbl_revision;

	अगर (!DATA_TABLES(dce_info))
		वापस BP_RESULT_UNSUPPORTED;

	header = GET_IMAGE(काष्ठा atom_common_table_header,
						DATA_TABLES(dce_info));
	get_atom_data_table_revision(header, &tbl_revision);
	चयन (tbl_revision.major) अणु
	हाल 4:
		चयन (tbl_revision.minor) अणु
		हाल 1:
			result = get_disp_caps_v4_1(bp, dce_caps);
			*dce_caps = !!(*dce_caps & DCE_INFO_CAPS_VBIOS_LTTPR_TRANSPARENT_ENABLE);
			अवरोध;
		हाल 2:
			result = get_disp_caps_v4_2(bp, dce_caps);
			*dce_caps = !!(*dce_caps & DCE_INFO_CAPS_VBIOS_LTTPR_TRANSPARENT_ENABLE);
			अवरोध;
		हाल 3:
			result = get_disp_caps_v4_3(bp, dce_caps);
			*dce_caps = !!(*dce_caps & DCE_INFO_CAPS_VBIOS_LTTPR_TRANSPARENT_ENABLE);
			अवरोध;
		हाल 4:
			result = get_disp_caps_v4_4(bp, dce_caps);
			*dce_caps = !!(*dce_caps & DCE_INFO_CAPS_VBIOS_LTTPR_TRANSPARENT_ENABLE);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

अटल क्रमागत bp_result bios_parser_get_lttpr_caps(
	काष्ठा dc_bios *dcb,
	uपूर्णांक8_t *dce_caps)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	क्रमागत bp_result result = BP_RESULT_UNSUPPORTED;
	काष्ठा atom_common_table_header *header;
	काष्ठा atom_data_revision tbl_revision;

	अगर (!DATA_TABLES(dce_info))
		वापस BP_RESULT_UNSUPPORTED;

	header = GET_IMAGE(काष्ठा atom_common_table_header,
						DATA_TABLES(dce_info));
	get_atom_data_table_revision(header, &tbl_revision);
	चयन (tbl_revision.major) अणु
	हाल 4:
		चयन (tbl_revision.minor) अणु
		हाल 1:
			result = get_disp_caps_v4_1(bp, dce_caps);
			*dce_caps = !!(*dce_caps & DCE_INFO_CAPS_LTTPR_SUPPORT_ENABLE);
			अवरोध;
		हाल 2:
			result = get_disp_caps_v4_2(bp, dce_caps);
			*dce_caps = !!(*dce_caps & DCE_INFO_CAPS_LTTPR_SUPPORT_ENABLE);
			अवरोध;
		हाल 3:
			result = get_disp_caps_v4_3(bp, dce_caps);
			*dce_caps = !!(*dce_caps & DCE_INFO_CAPS_LTTPR_SUPPORT_ENABLE);
			अवरोध;
		हाल 4:
			result = get_disp_caps_v4_4(bp, dce_caps);
			*dce_caps = !!(*dce_caps & DCE_INFO_CAPS_LTTPR_SUPPORT_ENABLE);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

अटल क्रमागत bp_result get_embedded_panel_info_v2_1(
		काष्ठा bios_parser *bp,
		काष्ठा embedded_panel_info *info)
अणु
	काष्ठा lcd_info_v2_1 *lvds;

	अगर (!info)
		वापस BP_RESULT_BADINPUT;

	अगर (!DATA_TABLES(lcd_info))
		वापस BP_RESULT_UNSUPPORTED;

	lvds = GET_IMAGE(काष्ठा lcd_info_v2_1, DATA_TABLES(lcd_info));

	अगर (!lvds)
		वापस BP_RESULT_BADBIOSTABLE;

	/* TODO: previous vv1_3, should v2_1 */
	अगर (!((lvds->table_header.क्रमmat_revision == 2)
			&& (lvds->table_header.content_revision >= 1)))
		वापस BP_RESULT_UNSUPPORTED;

	स_रखो(info, 0, माप(काष्ठा embedded_panel_info));

	/* We need to convert from 10KHz units पूर्णांकo KHz units */
	info->lcd_timing.pixel_clk = le16_to_cpu(lvds->lcd_timing.pixclk) * 10;
	/* usHActive करोes not include borders, according to VBIOS team */
	info->lcd_timing.horizontal_addressable = le16_to_cpu(lvds->lcd_timing.h_active);
	/* usHBlanking_Time includes borders, so we should really be
	 * subtractingborders duing this translation, but LVDS generally
	 * करोesn't have borders, so we should be okay leaving this as is क्रम
	 * now.  May need to revisit अगर we ever have LVDS with borders
	 */
	info->lcd_timing.horizontal_blanking_समय = le16_to_cpu(lvds->lcd_timing.h_blanking_समय);
	/* usVActive करोes not include borders, according to VBIOS team*/
	info->lcd_timing.vertical_addressable = le16_to_cpu(lvds->lcd_timing.v_active);
	/* usVBlanking_Time includes borders, so we should really be
	 * subtracting borders duing this translation, but LVDS generally
	 * करोesn't have borders, so we should be okay leaving this as is क्रम
	 * now. May need to revisit अगर we ever have LVDS with borders
	 */
	info->lcd_timing.vertical_blanking_समय = le16_to_cpu(lvds->lcd_timing.v_blanking_समय);
	info->lcd_timing.horizontal_sync_offset = le16_to_cpu(lvds->lcd_timing.h_sync_offset);
	info->lcd_timing.horizontal_sync_width = le16_to_cpu(lvds->lcd_timing.h_sync_width);
	info->lcd_timing.vertical_sync_offset = le16_to_cpu(lvds->lcd_timing.v_sync_offset);
	info->lcd_timing.vertical_sync_width = le16_to_cpu(lvds->lcd_timing.v_syncwidth);
	info->lcd_timing.horizontal_border = lvds->lcd_timing.h_border;
	info->lcd_timing.vertical_border = lvds->lcd_timing.v_border;

	/* not provided by VBIOS */
	info->lcd_timing.misc_info.HORIZONTAL_CUT_OFF = 0;

	info->lcd_timing.misc_info.H_SYNC_POLARITY = ~(uपूर्णांक32_t) (lvds->lcd_timing.miscinfo
			& ATOM_HSYNC_POLARITY);
	info->lcd_timing.misc_info.V_SYNC_POLARITY = ~(uपूर्णांक32_t) (lvds->lcd_timing.miscinfo
			& ATOM_VSYNC_POLARITY);

	/* not provided by VBIOS */
	info->lcd_timing.misc_info.VERTICAL_CUT_OFF = 0;

	info->lcd_timing.misc_info.H_REPLICATION_BY2 = !!(lvds->lcd_timing.miscinfo
			& ATOM_H_REPLICATIONBY2);
	info->lcd_timing.misc_info.V_REPLICATION_BY2 = !!(lvds->lcd_timing.miscinfo
			& ATOM_V_REPLICATIONBY2);
	info->lcd_timing.misc_info.COMPOSITE_SYNC = !!(lvds->lcd_timing.miscinfo
			& ATOM_COMPOSITESYNC);
	info->lcd_timing.misc_info.INTERLACE = !!(lvds->lcd_timing.miscinfo & ATOM_INTERLACE);

	/* not provided by VBIOS*/
	info->lcd_timing.misc_info.DOUBLE_CLOCK = 0;
	/* not provided by VBIOS*/
	info->ss_id = 0;

	info->realtek_eDPToLVDS = !!(lvds->dplvdsrxid == eDP_TO_LVDS_REALTEK_ID);

	वापस BP_RESULT_OK;
पूर्ण

अटल क्रमागत bp_result bios_parser_get_embedded_panel_info(
		काष्ठा dc_bios *dcb,
		काष्ठा embedded_panel_info *info)
अणु
	काष्ठा bios_parser
	*bp = BP_FROM_DCB(dcb);
	काष्ठा atom_common_table_header *header;
	काष्ठा atom_data_revision tbl_revision;

	अगर (!DATA_TABLES(lcd_info))
		वापस BP_RESULT_FAILURE;

	header = GET_IMAGE(काष्ठा atom_common_table_header, DATA_TABLES(lcd_info));

	अगर (!header)
		वापस BP_RESULT_BADBIOSTABLE;

	get_atom_data_table_revision(header, &tbl_revision);

	चयन (tbl_revision.major) अणु
	हाल 2:
		चयन (tbl_revision.minor) अणु
		हाल 1:
			वापस get_embedded_panel_info_v2_1(bp, info);
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस BP_RESULT_FAILURE;
पूर्ण

अटल uपूर्णांक32_t get_support_mask_क्रम_device_id(काष्ठा device_id device_id)
अणु
	क्रमागत dal_device_type device_type = device_id.device_type;
	uपूर्णांक32_t क्रमागत_id = device_id.क्रमागत_id;

	चयन (device_type) अणु
	हाल DEVICE_TYPE_LCD:
		चयन (क्रमागत_id) अणु
		हाल 1:
			वापस ATOM_DISPLAY_LCD1_SUPPORT;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल DEVICE_TYPE_DFP:
		चयन (क्रमागत_id) अणु
		हाल 1:
			वापस ATOM_DISPLAY_DFP1_SUPPORT;
		हाल 2:
			वापस ATOM_DISPLAY_DFP2_SUPPORT;
		हाल 3:
			वापस ATOM_DISPLAY_DFP3_SUPPORT;
		हाल 4:
			वापस ATOM_DISPLAY_DFP4_SUPPORT;
		हाल 5:
			वापस ATOM_DISPLAY_DFP5_SUPPORT;
		हाल 6:
			वापस ATOM_DISPLAY_DFP6_SUPPORT;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Unidentअगरied device ID, वापस empty support mask. */
	वापस 0;
पूर्ण

अटल bool bios_parser_is_device_id_supported(
	काष्ठा dc_bios *dcb,
	काष्ठा device_id id)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);

	uपूर्णांक32_t mask = get_support_mask_क्रम_device_id(id);

	वापस (le16_to_cpu(bp->object_info_tbl.v1_4->supporteddevices) &
								mask) != 0;
पूर्ण

अटल uपूर्णांक32_t bios_parser_get_ss_entry_number(
	काष्ठा dc_bios *dcb,
	क्रमागत as_संकेत_type संकेत)
अणु
	/* TODO: DAL2 atomfirmware implementation करोes not need this.
	 * why DAL3 need this?
	 */
	वापस 1;
पूर्ण

अटल क्रमागत bp_result bios_parser_transmitter_control(
	काष्ठा dc_bios *dcb,
	काष्ठा bp_transmitter_control *cntl)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);

	अगर (!bp->cmd_tbl.transmitter_control)
		वापस BP_RESULT_FAILURE;

	वापस bp->cmd_tbl.transmitter_control(bp, cntl);
पूर्ण

अटल क्रमागत bp_result bios_parser_encoder_control(
	काष्ठा dc_bios *dcb,
	काष्ठा bp_encoder_control *cntl)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);

	अगर (!bp->cmd_tbl.dig_encoder_control)
		वापस BP_RESULT_FAILURE;

	वापस bp->cmd_tbl.dig_encoder_control(bp, cntl);
पूर्ण

अटल क्रमागत bp_result bios_parser_set_pixel_घड़ी(
	काष्ठा dc_bios *dcb,
	काष्ठा bp_pixel_घड़ी_parameters *bp_params)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);

	अगर (!bp->cmd_tbl.set_pixel_घड़ी)
		वापस BP_RESULT_FAILURE;

	वापस bp->cmd_tbl.set_pixel_घड़ी(bp, bp_params);
पूर्ण

अटल क्रमागत bp_result bios_parser_set_dce_घड़ी(
	काष्ठा dc_bios *dcb,
	काष्ठा bp_set_dce_घड़ी_parameters *bp_params)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);

	अगर (!bp->cmd_tbl.set_dce_घड़ी)
		वापस BP_RESULT_FAILURE;

	वापस bp->cmd_tbl.set_dce_घड़ी(bp, bp_params);
पूर्ण

अटल क्रमागत bp_result bios_parser_program_crtc_timing(
	काष्ठा dc_bios *dcb,
	काष्ठा bp_hw_crtc_timing_parameters *bp_params)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);

	अगर (!bp->cmd_tbl.set_crtc_timing)
		वापस BP_RESULT_FAILURE;

	वापस bp->cmd_tbl.set_crtc_timing(bp, bp_params);
पूर्ण

अटल क्रमागत bp_result bios_parser_enable_crtc(
	काष्ठा dc_bios *dcb,
	क्रमागत controller_id id,
	bool enable)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);

	अगर (!bp->cmd_tbl.enable_crtc)
		वापस BP_RESULT_FAILURE;

	वापस bp->cmd_tbl.enable_crtc(bp, id, enable);
पूर्ण

अटल क्रमागत bp_result bios_parser_enable_disp_घातer_gating(
	काष्ठा dc_bios *dcb,
	क्रमागत controller_id controller_id,
	क्रमागत bp_pipe_control_action action)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);

	अगर (!bp->cmd_tbl.enable_disp_घातer_gating)
		वापस BP_RESULT_FAILURE;

	वापस bp->cmd_tbl.enable_disp_घातer_gating(bp, controller_id,
		action);
पूर्ण

अटल क्रमागत bp_result bios_parser_enable_lvपंचांगa_control(
	काष्ठा dc_bios *dcb,
	uपूर्णांक8_t uc_pwr_on,
	uपूर्णांक8_t panel_instance)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);

	अगर (!bp->cmd_tbl.enable_lvपंचांगa_control)
		वापस BP_RESULT_FAILURE;

	वापस bp->cmd_tbl.enable_lvपंचांगa_control(bp, uc_pwr_on, panel_instance);
पूर्ण

अटल bool bios_parser_is_accelerated_mode(
	काष्ठा dc_bios *dcb)
अणु
	वापस bios_is_accelerated_mode(dcb);
पूर्ण

/**
 * bios_parser_set_scratch_critical_state - update critical state bit
 *                                          in VBIOS scratch रेजिस्टर
 *
 * @dcb:   poपूर्णांकer to the DC BIO
 * @state: set or reset state
 */
अटल व्योम bios_parser_set_scratch_critical_state(
	काष्ठा dc_bios *dcb,
	bool state)
अणु
	bios_set_scratch_critical_state(dcb, state);
पूर्ण

अटल क्रमागत bp_result bios_parser_get_firmware_info(
	काष्ठा dc_bios *dcb,
	काष्ठा dc_firmware_info *info)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	क्रमागत bp_result result = BP_RESULT_BADBIOSTABLE;
	काष्ठा atom_common_table_header *header;

	काष्ठा atom_data_revision revision;

	अगर (info && DATA_TABLES(firmwareinfo)) अणु
		header = GET_IMAGE(काष्ठा atom_common_table_header,
				DATA_TABLES(firmwareinfo));
		get_atom_data_table_revision(header, &revision);
		चयन (revision.major) अणु
		हाल 3:
			चयन (revision.minor) अणु
			हाल 1:
				result = get_firmware_info_v3_1(bp, info);
				अवरोध;
			हाल 2:
			हाल 3:
			हाल 4:
				result = get_firmware_info_v3_2(bp, info);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

अटल क्रमागत bp_result get_firmware_info_v3_1(
	काष्ठा bios_parser *bp,
	काष्ठा dc_firmware_info *info)
अणु
	काष्ठा atom_firmware_info_v3_1 *firmware_info;
	काष्ठा atom_display_controller_info_v4_1 *dce_info = शून्य;

	अगर (!info)
		वापस BP_RESULT_BADINPUT;

	firmware_info = GET_IMAGE(काष्ठा atom_firmware_info_v3_1,
			DATA_TABLES(firmwareinfo));

	dce_info = GET_IMAGE(काष्ठा atom_display_controller_info_v4_1,
			DATA_TABLES(dce_info));

	अगर (!firmware_info || !dce_info)
		वापस BP_RESULT_BADBIOSTABLE;

	स_रखो(info, 0, माप(*info));

	/* Pixel घड़ी pll inक्रमmation. */
	 /* We need to convert from 10KHz units पूर्णांकo KHz units */
	info->शेष_memory_clk = firmware_info->bootup_mclk_in10khz * 10;
	info->शेष_engine_clk = firmware_info->bootup_sclk_in10khz * 10;

	 /* 27MHz क्रम Vega10: */
	info->pll_info.crystal_frequency = dce_info->dce_refclk_10khz * 10;

	/* Hardcode frequency अगर BIOS gives no DCE Ref Clk */
	अगर (info->pll_info.crystal_frequency == 0)
		info->pll_info.crystal_frequency = 27000;
	/*dp_phy_ref_clk is not correct क्रम atom_display_controller_info_v4_2, but we करोn't use it*/
	info->dp_phy_ref_clk     = dce_info->dpphy_refclk_10khz * 10;
	info->i2c_engine_ref_clk = dce_info->i2c_engine_refclk_10khz * 10;

	/* Get GPU PLL VCO Clock */

	अगर (bp->cmd_tbl.get_smu_घड़ी_info != शून्य) अणु
		/* VBIOS gives in 10KHz */
		info->smu_gpu_pll_output_freq =
				bp->cmd_tbl.get_smu_घड़ी_info(bp, SMU9_SYSPLL0_ID) * 10;
	पूर्ण

	info->oem_i2c_present = false;

	वापस BP_RESULT_OK;
पूर्ण

अटल क्रमागत bp_result get_firmware_info_v3_2(
	काष्ठा bios_parser *bp,
	काष्ठा dc_firmware_info *info)
अणु
	काष्ठा atom_firmware_info_v3_2 *firmware_info;
	काष्ठा atom_display_controller_info_v4_1 *dce_info = शून्य;
	काष्ठा atom_common_table_header *header;
	काष्ठा atom_data_revision revision;
	काष्ठा atom_smu_info_v3_2 *smu_info_v3_2 = शून्य;
	काष्ठा atom_smu_info_v3_3 *smu_info_v3_3 = शून्य;

	अगर (!info)
		वापस BP_RESULT_BADINPUT;

	firmware_info = GET_IMAGE(काष्ठा atom_firmware_info_v3_2,
			DATA_TABLES(firmwareinfo));

	dce_info = GET_IMAGE(काष्ठा atom_display_controller_info_v4_1,
			DATA_TABLES(dce_info));

	अगर (!firmware_info || !dce_info)
		वापस BP_RESULT_BADBIOSTABLE;

	स_रखो(info, 0, माप(*info));

	header = GET_IMAGE(काष्ठा atom_common_table_header,
					DATA_TABLES(smu_info));
	get_atom_data_table_revision(header, &revision);

	अगर (revision.minor == 2) अणु
		/* Vega12 */
		smu_info_v3_2 = GET_IMAGE(काष्ठा atom_smu_info_v3_2,
							DATA_TABLES(smu_info));

		अगर (!smu_info_v3_2)
			वापस BP_RESULT_BADBIOSTABLE;

		info->शेष_engine_clk = smu_info_v3_2->bootup_dcefclk_10khz * 10;
	पूर्ण अन्यथा अगर (revision.minor == 3) अणु
		/* Vega20 */
		smu_info_v3_3 = GET_IMAGE(काष्ठा atom_smu_info_v3_3,
							DATA_TABLES(smu_info));

		अगर (!smu_info_v3_3)
			वापस BP_RESULT_BADBIOSTABLE;

		info->शेष_engine_clk = smu_info_v3_3->bootup_dcefclk_10khz * 10;
	पूर्ण

	 // We need to convert from 10KHz units पूर्णांकo KHz units.
	info->शेष_memory_clk = firmware_info->bootup_mclk_in10khz * 10;

	 /* 27MHz क्रम Vega10 & Vega12; 100MHz क्रम Vega20 */
	info->pll_info.crystal_frequency = dce_info->dce_refclk_10khz * 10;
	/* Hardcode frequency अगर BIOS gives no DCE Ref Clk */
	अगर (info->pll_info.crystal_frequency == 0) अणु
		अगर (revision.minor == 2)
			info->pll_info.crystal_frequency = 27000;
		अन्यथा अगर (revision.minor == 3)
			info->pll_info.crystal_frequency = 100000;
	पूर्ण
	/*dp_phy_ref_clk is not correct क्रम atom_display_controller_info_v4_2, but we करोn't use it*/
	info->dp_phy_ref_clk     = dce_info->dpphy_refclk_10khz * 10;
	info->i2c_engine_ref_clk = dce_info->i2c_engine_refclk_10khz * 10;

	/* Get GPU PLL VCO Clock */
	अगर (bp->cmd_tbl.get_smu_घड़ी_info != शून्य) अणु
		अगर (revision.minor == 2)
			info->smu_gpu_pll_output_freq =
					bp->cmd_tbl.get_smu_घड़ी_info(bp, SMU9_SYSPLL0_ID) * 10;
		अन्यथा अगर (revision.minor == 3)
			info->smu_gpu_pll_output_freq =
					bp->cmd_tbl.get_smu_घड़ी_info(bp, SMU11_SYSPLL3_0_ID) * 10;
	पूर्ण

	अगर (firmware_info->board_i2c_feature_id == 0x2) अणु
		info->oem_i2c_present = true;
		info->oem_i2c_obj_id = firmware_info->board_i2c_feature_gpio_id;
	पूर्ण अन्यथा अणु
		info->oem_i2c_present = false;
	पूर्ण

	वापस BP_RESULT_OK;
पूर्ण

अटल क्रमागत bp_result bios_parser_get_encoder_cap_info(
	काष्ठा dc_bios *dcb,
	काष्ठा graphics_object_id object_id,
	काष्ठा bp_encoder_cap_info *info)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	काष्ठा atom_display_object_path_v2 *object;
	काष्ठा atom_encoder_caps_record *record = शून्य;

	अगर (!info)
		वापस BP_RESULT_BADINPUT;

	object = get_bios_object(bp, object_id);

	अगर (!object)
		वापस BP_RESULT_BADINPUT;

	record = get_encoder_cap_record(bp, object);
	अगर (!record)
		वापस BP_RESULT_NORECORD;

	info->DP_HBR2_CAP = (record->encodercaps &
			ATOM_ENCODER_CAP_RECORD_HBR2) ? 1 : 0;
	info->DP_HBR2_EN = (record->encodercaps &
			ATOM_ENCODER_CAP_RECORD_HBR2_EN) ? 1 : 0;
	info->DP_HBR3_EN = (record->encodercaps &
			ATOM_ENCODER_CAP_RECORD_HBR3_EN) ? 1 : 0;
	info->HDMI_6GB_EN = (record->encodercaps &
			ATOM_ENCODER_CAP_RECORD_HDMI6Gbps_EN) ? 1 : 0;
	info->DP_IS_USB_C = (record->encodercaps &
			ATOM_ENCODER_CAP_RECORD_USB_C_TYPE) ? 1 : 0;

	वापस BP_RESULT_OK;
पूर्ण


अटल काष्ठा atom_encoder_caps_record *get_encoder_cap_record(
	काष्ठा bios_parser *bp,
	काष्ठा atom_display_object_path_v2 *object)
अणु
	काष्ठा atom_common_record_header *header;
	uपूर्णांक32_t offset;

	अगर (!object) अणु
		BREAK_TO_DEBUGGER(); /* Invalid object */
		वापस शून्य;
	पूर्ण

	offset = object->encoder_recorकरोffset + bp->object_info_tbl_offset;

	क्रम (;;) अणु
		header = GET_IMAGE(काष्ठा atom_common_record_header, offset);

		अगर (!header)
			वापस शून्य;

		offset += header->record_size;

		अगर (header->record_type == LAST_RECORD_TYPE ||
				!header->record_size)
			अवरोध;

		अगर (header->record_type != ATOM_ENCODER_CAP_RECORD_TYPE)
			जारी;

		अगर (माप(काष्ठा atom_encoder_caps_record) <=
							header->record_size)
			वापस (काष्ठा atom_encoder_caps_record *)header;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा atom_disp_connector_caps_record *get_disp_connector_caps_record(
	काष्ठा bios_parser *bp,
	काष्ठा atom_display_object_path_v2 *object)
अणु
	काष्ठा atom_common_record_header *header;
	uपूर्णांक32_t offset;

	अगर (!object) अणु
		BREAK_TO_DEBUGGER(); /* Invalid object */
		वापस शून्य;
	पूर्ण

	offset = object->disp_recorकरोffset + bp->object_info_tbl_offset;

	क्रम (;;) अणु
		header = GET_IMAGE(काष्ठा atom_common_record_header, offset);

		अगर (!header)
			वापस शून्य;

		offset += header->record_size;

		अगर (header->record_type == LAST_RECORD_TYPE ||
				!header->record_size)
			अवरोध;

		अगर (header->record_type != ATOM_DISP_CONNECTOR_CAPS_RECORD_TYPE)
			जारी;

		अगर (माप(काष्ठा atom_disp_connector_caps_record) <=
							header->record_size)
			वापस (काष्ठा atom_disp_connector_caps_record *)header;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल क्रमागत bp_result bios_parser_get_disp_connector_caps_info(
	काष्ठा dc_bios *dcb,
	काष्ठा graphics_object_id object_id,
	काष्ठा bp_disp_connector_caps_info *info)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	काष्ठा atom_display_object_path_v2 *object;
	काष्ठा atom_disp_connector_caps_record *record = शून्य;

	अगर (!info)
		वापस BP_RESULT_BADINPUT;

	object = get_bios_object(bp, object_id);

	अगर (!object)
		वापस BP_RESULT_BADINPUT;

	record = get_disp_connector_caps_record(bp, object);
	अगर (!record)
		वापस BP_RESULT_NORECORD;

	info->INTERNAL_DISPLAY = (record->connectcaps & ATOM_CONNECTOR_CAP_INTERNAL_DISPLAY)
									? 1 : 0;
	info->INTERNAL_DISPLAY_BL = (record->connectcaps & ATOM_CONNECTOR_CAP_INTERNAL_DISPLAY_BL)
											? 1 : 0;

	वापस BP_RESULT_OK;
पूर्ण

अटल क्रमागत bp_result get_vram_info_v23(
	काष्ठा bios_parser *bp,
	काष्ठा dc_vram_info *info)
अणु
	काष्ठा atom_vram_info_header_v2_3 *info_v23;
	क्रमागत bp_result result = BP_RESULT_OK;

	info_v23 = GET_IMAGE(काष्ठा atom_vram_info_header_v2_3,
						DATA_TABLES(vram_info));

	अगर (info_v23 == शून्य)
		वापस BP_RESULT_BADBIOSTABLE;

	info->num_chans = info_v23->vram_module[0].channel_num;
	info->dram_channel_width_bytes = (1 << info_v23->vram_module[0].channel_width) / 8;

	वापस result;
पूर्ण

अटल क्रमागत bp_result get_vram_info_v24(
	काष्ठा bios_parser *bp,
	काष्ठा dc_vram_info *info)
अणु
	काष्ठा atom_vram_info_header_v2_4 *info_v24;
	क्रमागत bp_result result = BP_RESULT_OK;

	info_v24 = GET_IMAGE(काष्ठा atom_vram_info_header_v2_4,
						DATA_TABLES(vram_info));

	अगर (info_v24 == शून्य)
		वापस BP_RESULT_BADBIOSTABLE;

	info->num_chans = info_v24->vram_module[0].channel_num;
	info->dram_channel_width_bytes = (1 << info_v24->vram_module[0].channel_width) / 8;

	वापस result;
पूर्ण

अटल क्रमागत bp_result get_vram_info_v25(
	काष्ठा bios_parser *bp,
	काष्ठा dc_vram_info *info)
अणु
	काष्ठा atom_vram_info_header_v2_5 *info_v25;
	क्रमागत bp_result result = BP_RESULT_OK;

	info_v25 = GET_IMAGE(काष्ठा atom_vram_info_header_v2_5,
						DATA_TABLES(vram_info));

	अगर (info_v25 == शून्य)
		वापस BP_RESULT_BADBIOSTABLE;

	info->num_chans = info_v25->vram_module[0].channel_num;
	info->dram_channel_width_bytes = (1 << info_v25->vram_module[0].channel_width) / 8;

	वापस result;
पूर्ण

/*
 * get_पूर्णांकegrated_info_v11
 *
 * @brief
 * Get V8 पूर्णांकegrated BIOS inक्रमmation
 *
 * @param
 * bios_parser *bp - [in]BIOS parser handler to get master data table
 * पूर्णांकegrated_info *info - [out] store and output पूर्णांकegrated info
 *
 * @वापस
 * क्रमागत bp_result - BP_RESULT_OK अगर inक्रमmation is available,
 *                  BP_RESULT_BADBIOSTABLE otherwise.
 */
अटल क्रमागत bp_result get_पूर्णांकegrated_info_v11(
	काष्ठा bios_parser *bp,
	काष्ठा पूर्णांकegrated_info *info)
अणु
	काष्ठा atom_पूर्णांकegrated_प्रणाली_info_v1_11 *info_v11;
	uपूर्णांक32_t i;

	info_v11 = GET_IMAGE(काष्ठा atom_पूर्णांकegrated_प्रणाली_info_v1_11,
					DATA_TABLES(पूर्णांकegratedप्रणालीinfo));

	अगर (info_v11 == शून्य)
		वापस BP_RESULT_BADBIOSTABLE;

	info->gpu_cap_info =
	le32_to_cpu(info_v11->gpucapinfo);
	/*
	* प्रणाली_config: Bit[0] = 0 : PCIE घातer gating disabled
	*                       = 1 : PCIE घातer gating enabled
	*                Bit[1] = 0 : DDR-PLL shut करोwn disabled
	*                       = 1 : DDR-PLL shut करोwn enabled
	*                Bit[2] = 0 : DDR-PLL घातer करोwn disabled
	*                       = 1 : DDR-PLL घातer करोwn enabled
	*/
	info->प्रणाली_config = le32_to_cpu(info_v11->प्रणाली_config);
	info->cpu_cap_info = le32_to_cpu(info_v11->cpucapinfo);
	info->memory_type = info_v11->memorytype;
	info->ma_channel_number = info_v11->umachannelnumber;
	info->lvds_ss_percentage =
	le16_to_cpu(info_v11->lvds_ss_percentage);
	info->dp_ss_control =
	le16_to_cpu(info_v11->reserved1);
	info->lvds_sspपढ़ो_rate_in_10hz =
	le16_to_cpu(info_v11->lvds_ss_rate_10hz);
	info->hdmi_ss_percentage =
	le16_to_cpu(info_v11->hdmi_ss_percentage);
	info->hdmi_sspपढ़ो_rate_in_10hz =
	le16_to_cpu(info_v11->hdmi_ss_rate_10hz);
	info->dvi_ss_percentage =
	le16_to_cpu(info_v11->dvi_ss_percentage);
	info->dvi_sspपढ़ो_rate_in_10_hz =
	le16_to_cpu(info_v11->dvi_ss_rate_10hz);
	info->lvds_misc = info_v11->lvds_misc;
	क्रम (i = 0; i < NUMBER_OF_UCHAR_FOR_GUID; ++i) अणु
		info->ext_disp_conn_info.gu_id[i] =
				info_v11->extdispconninfo.guid[i];
	पूर्ण

	क्रम (i = 0; i < MAX_NUMBER_OF_EXT_DISPLAY_PATH; ++i) अणु
		info->ext_disp_conn_info.path[i].device_connector_id =
		object_id_from_bios_object_id(
		le16_to_cpu(info_v11->extdispconninfo.path[i].connectorobjid));

		info->ext_disp_conn_info.path[i].ext_encoder_obj_id =
		object_id_from_bios_object_id(
			le16_to_cpu(
			info_v11->extdispconninfo.path[i].ext_encoder_objid));

		info->ext_disp_conn_info.path[i].device_tag =
			le16_to_cpu(
				info_v11->extdispconninfo.path[i].device_tag);
		info->ext_disp_conn_info.path[i].device_acpi_क्रमागत =
		le16_to_cpu(
			info_v11->extdispconninfo.path[i].device_acpi_क्रमागत);
		info->ext_disp_conn_info.path[i].ext_aux_ddc_lut_index =
			info_v11->extdispconninfo.path[i].auxddclut_index;
		info->ext_disp_conn_info.path[i].ext_hpd_pin_lut_index =
			info_v11->extdispconninfo.path[i].hpdlut_index;
		info->ext_disp_conn_info.path[i].channel_mapping.raw =
			info_v11->extdispconninfo.path[i].channelmapping;
		info->ext_disp_conn_info.path[i].caps =
				le16_to_cpu(info_v11->extdispconninfo.path[i].caps);
	पूर्ण
	info->ext_disp_conn_info.checksum =
	info_v11->extdispconninfo.checksum;

	info->dp0_ext_hdmi_slv_addr = info_v11->dp0_reसमयr_set.HdmiSlvAddr;
	info->dp0_ext_hdmi_reg_num = info_v11->dp0_reसमयr_set.HdmiRegNum;
	क्रम (i = 0; i < info->dp0_ext_hdmi_reg_num; i++) अणु
		info->dp0_ext_hdmi_reg_settings[i].i2c_reg_index =
				info_v11->dp0_reसमयr_set.HdmiRegSetting[i].ucI2cRegIndex;
		info->dp0_ext_hdmi_reg_settings[i].i2c_reg_val =
				info_v11->dp0_reसमयr_set.HdmiRegSetting[i].ucI2cRegVal;
	पूर्ण
	info->dp0_ext_hdmi_6g_reg_num = info_v11->dp0_reसमयr_set.Hdmi6GRegNum;
	क्रम (i = 0; i < info->dp0_ext_hdmi_6g_reg_num; i++) अणु
		info->dp0_ext_hdmi_6g_reg_settings[i].i2c_reg_index =
				info_v11->dp0_reसमयr_set.Hdmi6GhzRegSetting[i].ucI2cRegIndex;
		info->dp0_ext_hdmi_6g_reg_settings[i].i2c_reg_val =
				info_v11->dp0_reसमयr_set.Hdmi6GhzRegSetting[i].ucI2cRegVal;
	पूर्ण

	info->dp1_ext_hdmi_slv_addr = info_v11->dp1_reसमयr_set.HdmiSlvAddr;
	info->dp1_ext_hdmi_reg_num = info_v11->dp1_reसमयr_set.HdmiRegNum;
	क्रम (i = 0; i < info->dp1_ext_hdmi_reg_num; i++) अणु
		info->dp1_ext_hdmi_reg_settings[i].i2c_reg_index =
				info_v11->dp1_reसमयr_set.HdmiRegSetting[i].ucI2cRegIndex;
		info->dp1_ext_hdmi_reg_settings[i].i2c_reg_val =
				info_v11->dp1_reसमयr_set.HdmiRegSetting[i].ucI2cRegVal;
	पूर्ण
	info->dp1_ext_hdmi_6g_reg_num = info_v11->dp1_reसमयr_set.Hdmi6GRegNum;
	क्रम (i = 0; i < info->dp1_ext_hdmi_6g_reg_num; i++) अणु
		info->dp1_ext_hdmi_6g_reg_settings[i].i2c_reg_index =
				info_v11->dp1_reसमयr_set.Hdmi6GhzRegSetting[i].ucI2cRegIndex;
		info->dp1_ext_hdmi_6g_reg_settings[i].i2c_reg_val =
				info_v11->dp1_reसमयr_set.Hdmi6GhzRegSetting[i].ucI2cRegVal;
	पूर्ण

	info->dp2_ext_hdmi_slv_addr = info_v11->dp2_reसमयr_set.HdmiSlvAddr;
	info->dp2_ext_hdmi_reg_num = info_v11->dp2_reसमयr_set.HdmiRegNum;
	क्रम (i = 0; i < info->dp2_ext_hdmi_reg_num; i++) अणु
		info->dp2_ext_hdmi_reg_settings[i].i2c_reg_index =
				info_v11->dp2_reसमयr_set.HdmiRegSetting[i].ucI2cRegIndex;
		info->dp2_ext_hdmi_reg_settings[i].i2c_reg_val =
				info_v11->dp2_reसमयr_set.HdmiRegSetting[i].ucI2cRegVal;
	पूर्ण
	info->dp2_ext_hdmi_6g_reg_num = info_v11->dp2_reसमयr_set.Hdmi6GRegNum;
	क्रम (i = 0; i < info->dp2_ext_hdmi_6g_reg_num; i++) अणु
		info->dp2_ext_hdmi_6g_reg_settings[i].i2c_reg_index =
				info_v11->dp2_reसमयr_set.Hdmi6GhzRegSetting[i].ucI2cRegIndex;
		info->dp2_ext_hdmi_6g_reg_settings[i].i2c_reg_val =
				info_v11->dp2_reसमयr_set.Hdmi6GhzRegSetting[i].ucI2cRegVal;
	पूर्ण

	info->dp3_ext_hdmi_slv_addr = info_v11->dp3_reसमयr_set.HdmiSlvAddr;
	info->dp3_ext_hdmi_reg_num = info_v11->dp3_reसमयr_set.HdmiRegNum;
	क्रम (i = 0; i < info->dp3_ext_hdmi_reg_num; i++) अणु
		info->dp3_ext_hdmi_reg_settings[i].i2c_reg_index =
				info_v11->dp3_reसमयr_set.HdmiRegSetting[i].ucI2cRegIndex;
		info->dp3_ext_hdmi_reg_settings[i].i2c_reg_val =
				info_v11->dp3_reसमयr_set.HdmiRegSetting[i].ucI2cRegVal;
	पूर्ण
	info->dp3_ext_hdmi_6g_reg_num = info_v11->dp3_reसमयr_set.Hdmi6GRegNum;
	क्रम (i = 0; i < info->dp3_ext_hdmi_6g_reg_num; i++) अणु
		info->dp3_ext_hdmi_6g_reg_settings[i].i2c_reg_index =
				info_v11->dp3_reसमयr_set.Hdmi6GhzRegSetting[i].ucI2cRegIndex;
		info->dp3_ext_hdmi_6g_reg_settings[i].i2c_reg_val =
				info_v11->dp3_reसमयr_set.Hdmi6GhzRegSetting[i].ucI2cRegVal;
	पूर्ण


	/** TODO - review **/
	#अगर 0
	info->boot_up_engine_घड़ी = le32_to_cpu(info_v11->ulBootUpEngineClock)
									* 10;
	info->dentist_vco_freq = le32_to_cpu(info_v11->ulDentistVCOFreq) * 10;
	info->boot_up_uma_घड़ी = le32_to_cpu(info_v8->ulBootUpUMAClock) * 10;

	क्रम (i = 0; i < NUMBER_OF_DISP_CLK_VOLTAGE; ++i) अणु
		/* Convert [10KHz] पूर्णांकo [KHz] */
		info->disp_clk_voltage[i].max_supported_clk =
		le32_to_cpu(info_v11->sDISPCLK_Voltage[i].
			ulMaximumSupportedCLK) * 10;
		info->disp_clk_voltage[i].voltage_index =
		le32_to_cpu(info_v11->sDISPCLK_Voltage[i].ulVoltageIndex);
	पूर्ण

	info->boot_up_req_display_vector =
			le32_to_cpu(info_v11->ulBootUpReqDisplayVector);
	info->boot_up_nb_voltage =
			le16_to_cpu(info_v11->usBootUpNBVoltage);
	info->ext_disp_conn_info_offset =
			le16_to_cpu(info_v11->usExtDispConnInfoOffset);
	info->gmc_restore_reset_समय =
			le32_to_cpu(info_v11->ulGMCRestoreResetTime);
	info->minimum_n_clk =
			le32_to_cpu(info_v11->ulNbpStateNClkFreq[0]);
	क्रम (i = 1; i < 4; ++i)
		info->minimum_n_clk =
				info->minimum_n_clk <
				le32_to_cpu(info_v11->ulNbpStateNClkFreq[i]) ?
				info->minimum_n_clk : le32_to_cpu(
					info_v11->ulNbpStateNClkFreq[i]);

	info->idle_n_clk = le32_to_cpu(info_v11->ulIdleNClk);
	info->ddr_dll_घातer_up_समय =
	    le32_to_cpu(info_v11->ulDDR_DLL_PowerUpTime);
	info->ddr_pll_घातer_up_समय =
		le32_to_cpu(info_v11->ulDDR_PLL_PowerUpTime);
	info->pcie_clk_ss_type = le16_to_cpu(info_v11->usPCIEClkSSType);
	info->max_lvds_pclk_freq_in_single_link =
		le16_to_cpu(info_v11->usMaxLVDSPclkFreqInSingleLink);
	info->max_lvds_pclk_freq_in_single_link =
		le16_to_cpu(info_v11->usMaxLVDSPclkFreqInSingleLink);
	info->lvds_pwr_on_seq_dig_on_to_de_in_4ms =
		info_v11->ucLVDSPwrOnSeqDIGONtoDE_in4Ms;
	info->lvds_pwr_on_seq_de_to_vary_bl_in_4ms =
		info_v11->ucLVDSPwrOnSeqDEtoVARY_BL_in4Ms;
	info->lvds_pwr_on_seq_vary_bl_to_blon_in_4ms =
		info_v11->ucLVDSPwrOnSeqVARY_BLtoBLON_in4Ms;
	info->lvds_pwr_off_seq_vary_bl_to_de_in4ms =
		info_v11->ucLVDSPwrOffSeqVARY_BLtoDE_in4Ms;
	info->lvds_pwr_off_seq_de_to_dig_on_in4ms =
		info_v11->ucLVDSPwrOffSeqDEtoDIGON_in4Ms;
	info->lvds_pwr_off_seq_blon_to_vary_bl_in_4ms =
		info_v11->ucLVDSPwrOffSeqBLONtoVARY_BL_in4Ms;
	info->lvds_off_to_on_delay_in_4ms =
		info_v11->ucLVDSOffToOnDelay_in4Ms;
	info->lvds_bit_depth_control_val =
		le32_to_cpu(info_v11->ulLCDBitDepthControlVal);

	क्रम (i = 0; i < NUMBER_OF_AVAILABLE_SCLK; ++i) अणु
		/* Convert [10KHz] पूर्णांकo [KHz] */
		info->avail_s_clk[i].supported_s_clk =
			le32_to_cpu(info_v11->sAvail_SCLK[i].ulSupportedSCLK)
									* 10;
		info->avail_s_clk[i].voltage_index =
			le16_to_cpu(info_v11->sAvail_SCLK[i].usVoltageIndex);
		info->avail_s_clk[i].voltage_id =
			le16_to_cpu(info_v11->sAvail_SCLK[i].usVoltageID);
	पूर्ण
	#पूर्ण_अगर /* TODO*/

	वापस BP_RESULT_OK;
पूर्ण

अटल क्रमागत bp_result get_पूर्णांकegrated_info_v2_1(
	काष्ठा bios_parser *bp,
	काष्ठा पूर्णांकegrated_info *info)
अणु
	काष्ठा atom_पूर्णांकegrated_प्रणाली_info_v2_1 *info_v2_1;
	uपूर्णांक32_t i;

	info_v2_1 = GET_IMAGE(काष्ठा atom_पूर्णांकegrated_प्रणाली_info_v2_1,
					DATA_TABLES(पूर्णांकegratedप्रणालीinfo));

	अगर (info_v2_1 == शून्य)
		वापस BP_RESULT_BADBIOSTABLE;

	info->gpu_cap_info =
	le32_to_cpu(info_v2_1->gpucapinfo);
	/*
	* प्रणाली_config: Bit[0] = 0 : PCIE घातer gating disabled
	*                       = 1 : PCIE घातer gating enabled
	*                Bit[1] = 0 : DDR-PLL shut करोwn disabled
	*                       = 1 : DDR-PLL shut करोwn enabled
	*                Bit[2] = 0 : DDR-PLL घातer करोwn disabled
	*                       = 1 : DDR-PLL घातer करोwn enabled
	*/
	info->प्रणाली_config = le32_to_cpu(info_v2_1->प्रणाली_config);
	info->cpu_cap_info = le32_to_cpu(info_v2_1->cpucapinfo);
	info->memory_type = info_v2_1->memorytype;
	info->ma_channel_number = info_v2_1->umachannelnumber;
	info->dp_ss_control =
		le16_to_cpu(info_v2_1->reserved1);

	क्रम (i = 0; i < NUMBER_OF_UCHAR_FOR_GUID; ++i) अणु
		info->ext_disp_conn_info.gu_id[i] =
				info_v2_1->extdispconninfo.guid[i];
	पूर्ण

	क्रम (i = 0; i < MAX_NUMBER_OF_EXT_DISPLAY_PATH; ++i) अणु
		info->ext_disp_conn_info.path[i].device_connector_id =
		object_id_from_bios_object_id(
		le16_to_cpu(info_v2_1->extdispconninfo.path[i].connectorobjid));

		info->ext_disp_conn_info.path[i].ext_encoder_obj_id =
		object_id_from_bios_object_id(
			le16_to_cpu(
			info_v2_1->extdispconninfo.path[i].ext_encoder_objid));

		info->ext_disp_conn_info.path[i].device_tag =
			le16_to_cpu(
				info_v2_1->extdispconninfo.path[i].device_tag);
		info->ext_disp_conn_info.path[i].device_acpi_क्रमागत =
		le16_to_cpu(
			info_v2_1->extdispconninfo.path[i].device_acpi_क्रमागत);
		info->ext_disp_conn_info.path[i].ext_aux_ddc_lut_index =
			info_v2_1->extdispconninfo.path[i].auxddclut_index;
		info->ext_disp_conn_info.path[i].ext_hpd_pin_lut_index =
			info_v2_1->extdispconninfo.path[i].hpdlut_index;
		info->ext_disp_conn_info.path[i].channel_mapping.raw =
			info_v2_1->extdispconninfo.path[i].channelmapping;
		info->ext_disp_conn_info.path[i].caps =
				le16_to_cpu(info_v2_1->extdispconninfo.path[i].caps);
	पूर्ण

	info->ext_disp_conn_info.checksum =
		info_v2_1->extdispconninfo.checksum;
	info->dp0_ext_hdmi_slv_addr = info_v2_1->dp0_reसमयr_set.HdmiSlvAddr;
	info->dp0_ext_hdmi_reg_num = info_v2_1->dp0_reसमयr_set.HdmiRegNum;
	क्रम (i = 0; i < info->dp0_ext_hdmi_reg_num; i++) अणु
		info->dp0_ext_hdmi_reg_settings[i].i2c_reg_index =
				info_v2_1->dp0_reसमयr_set.HdmiRegSetting[i].ucI2cRegIndex;
		info->dp0_ext_hdmi_reg_settings[i].i2c_reg_val =
				info_v2_1->dp0_reसमयr_set.HdmiRegSetting[i].ucI2cRegVal;
	पूर्ण
	info->dp0_ext_hdmi_6g_reg_num = info_v2_1->dp0_reसमयr_set.Hdmi6GRegNum;
	क्रम (i = 0; i < info->dp0_ext_hdmi_6g_reg_num; i++) अणु
		info->dp0_ext_hdmi_6g_reg_settings[i].i2c_reg_index =
				info_v2_1->dp0_reसमयr_set.Hdmi6GhzRegSetting[i].ucI2cRegIndex;
		info->dp0_ext_hdmi_6g_reg_settings[i].i2c_reg_val =
				info_v2_1->dp0_reसमयr_set.Hdmi6GhzRegSetting[i].ucI2cRegVal;
	पूर्ण
	info->dp1_ext_hdmi_slv_addr = info_v2_1->dp1_reसमयr_set.HdmiSlvAddr;
	info->dp1_ext_hdmi_reg_num = info_v2_1->dp1_reसमयr_set.HdmiRegNum;
	क्रम (i = 0; i < info->dp1_ext_hdmi_reg_num; i++) अणु
		info->dp1_ext_hdmi_reg_settings[i].i2c_reg_index =
				info_v2_1->dp1_reसमयr_set.HdmiRegSetting[i].ucI2cRegIndex;
		info->dp1_ext_hdmi_reg_settings[i].i2c_reg_val =
				info_v2_1->dp1_reसमयr_set.HdmiRegSetting[i].ucI2cRegVal;
	पूर्ण
	info->dp1_ext_hdmi_6g_reg_num = info_v2_1->dp1_reसमयr_set.Hdmi6GRegNum;
	क्रम (i = 0; i < info->dp1_ext_hdmi_6g_reg_num; i++) अणु
		info->dp1_ext_hdmi_6g_reg_settings[i].i2c_reg_index =
				info_v2_1->dp1_reसमयr_set.Hdmi6GhzRegSetting[i].ucI2cRegIndex;
		info->dp1_ext_hdmi_6g_reg_settings[i].i2c_reg_val =
				info_v2_1->dp1_reसमयr_set.Hdmi6GhzRegSetting[i].ucI2cRegVal;
	पूर्ण
	info->dp2_ext_hdmi_slv_addr = info_v2_1->dp2_reसमयr_set.HdmiSlvAddr;
	info->dp2_ext_hdmi_reg_num = info_v2_1->dp2_reसमयr_set.HdmiRegNum;
	क्रम (i = 0; i < info->dp2_ext_hdmi_reg_num; i++) अणु
		info->dp2_ext_hdmi_reg_settings[i].i2c_reg_index =
				info_v2_1->dp2_reसमयr_set.HdmiRegSetting[i].ucI2cRegIndex;
		info->dp2_ext_hdmi_reg_settings[i].i2c_reg_val =
				info_v2_1->dp2_reसमयr_set.HdmiRegSetting[i].ucI2cRegVal;
	पूर्ण
	info->dp2_ext_hdmi_6g_reg_num = info_v2_1->dp2_reसमयr_set.Hdmi6GRegNum;
	क्रम (i = 0; i < info->dp2_ext_hdmi_6g_reg_num; i++) अणु
		info->dp2_ext_hdmi_6g_reg_settings[i].i2c_reg_index =
				info_v2_1->dp2_reसमयr_set.Hdmi6GhzRegSetting[i].ucI2cRegIndex;
		info->dp2_ext_hdmi_6g_reg_settings[i].i2c_reg_val =
				info_v2_1->dp2_reसमयr_set.Hdmi6GhzRegSetting[i].ucI2cRegVal;
	पूर्ण
	info->dp3_ext_hdmi_slv_addr = info_v2_1->dp3_reसमयr_set.HdmiSlvAddr;
	info->dp3_ext_hdmi_reg_num = info_v2_1->dp3_reसमयr_set.HdmiRegNum;
	क्रम (i = 0; i < info->dp3_ext_hdmi_reg_num; i++) अणु
		info->dp3_ext_hdmi_reg_settings[i].i2c_reg_index =
				info_v2_1->dp3_reसमयr_set.HdmiRegSetting[i].ucI2cRegIndex;
		info->dp3_ext_hdmi_reg_settings[i].i2c_reg_val =
				info_v2_1->dp3_reसमयr_set.HdmiRegSetting[i].ucI2cRegVal;
	पूर्ण
	info->dp3_ext_hdmi_6g_reg_num = info_v2_1->dp3_reसमयr_set.Hdmi6GRegNum;
	क्रम (i = 0; i < info->dp3_ext_hdmi_6g_reg_num; i++) अणु
		info->dp3_ext_hdmi_6g_reg_settings[i].i2c_reg_index =
				info_v2_1->dp3_reसमयr_set.Hdmi6GhzRegSetting[i].ucI2cRegIndex;
		info->dp3_ext_hdmi_6g_reg_settings[i].i2c_reg_val =
				info_v2_1->dp3_reसमयr_set.Hdmi6GhzRegSetting[i].ucI2cRegVal;
	पूर्ण

	info->edp1_info.edp_backlight_pwm_hz =
	le16_to_cpu(info_v2_1->edp1_info.edp_backlight_pwm_hz);
	info->edp1_info.edp_ss_percentage =
	le16_to_cpu(info_v2_1->edp1_info.edp_ss_percentage);
	info->edp1_info.edp_ss_rate_10hz =
	le16_to_cpu(info_v2_1->edp1_info.edp_ss_rate_10hz);
	info->edp1_info.edp_pwr_on_off_delay =
		info_v2_1->edp1_info.edp_pwr_on_off_delay;
	info->edp1_info.edp_pwr_on_vary_bl_to_blon =
		info_v2_1->edp1_info.edp_pwr_on_vary_bl_to_blon;
	info->edp1_info.edp_pwr_करोwn_bloff_to_vary_bloff =
		info_v2_1->edp1_info.edp_pwr_करोwn_bloff_to_vary_bloff;
	info->edp1_info.edp_panel_bpc =
		info_v2_1->edp1_info.edp_panel_bpc;
	info->edp1_info.edp_bootup_bl_level =

	info->edp2_info.edp_backlight_pwm_hz =
	le16_to_cpu(info_v2_1->edp2_info.edp_backlight_pwm_hz);
	info->edp2_info.edp_ss_percentage =
	le16_to_cpu(info_v2_1->edp2_info.edp_ss_percentage);
	info->edp2_info.edp_ss_rate_10hz =
	le16_to_cpu(info_v2_1->edp2_info.edp_ss_rate_10hz);
	info->edp2_info.edp_pwr_on_off_delay =
		info_v2_1->edp2_info.edp_pwr_on_off_delay;
	info->edp2_info.edp_pwr_on_vary_bl_to_blon =
		info_v2_1->edp2_info.edp_pwr_on_vary_bl_to_blon;
	info->edp2_info.edp_pwr_करोwn_bloff_to_vary_bloff =
		info_v2_1->edp2_info.edp_pwr_करोwn_bloff_to_vary_bloff;
	info->edp2_info.edp_panel_bpc =
		info_v2_1->edp2_info.edp_panel_bpc;
	info->edp2_info.edp_bootup_bl_level =
		info_v2_1->edp2_info.edp_bootup_bl_level;

	वापस BP_RESULT_OK;
पूर्ण

/*
 * स्थिरruct_पूर्णांकegrated_info
 *
 * @brief
 * Get पूर्णांकegrated BIOS inक्रमmation based on table revision
 *
 * @param
 * bios_parser *bp - [in]BIOS parser handler to get master data table
 * पूर्णांकegrated_info *info - [out] store and output पूर्णांकegrated info
 *
 * @वापस
 * क्रमागत bp_result - BP_RESULT_OK अगर inक्रमmation is available,
 *                  BP_RESULT_BADBIOSTABLE otherwise.
 */
अटल क्रमागत bp_result स्थिरruct_पूर्णांकegrated_info(
	काष्ठा bios_parser *bp,
	काष्ठा पूर्णांकegrated_info *info)
अणु
	क्रमागत bp_result result = BP_RESULT_BADBIOSTABLE;

	काष्ठा atom_common_table_header *header;
	काष्ठा atom_data_revision revision;
	uपूर्णांक32_t i;
	uपूर्णांक32_t j;

	अगर (info && DATA_TABLES(पूर्णांकegratedप्रणालीinfo)) अणु
		header = GET_IMAGE(काष्ठा atom_common_table_header,
					DATA_TABLES(पूर्णांकegratedप्रणालीinfo));

		get_atom_data_table_revision(header, &revision);

		चयन (revision.major) अणु
		हाल 1:
			चयन (revision.minor) अणु
			हाल 11:
			हाल 12:
				result = get_पूर्णांकegrated_info_v11(bp, info);
				अवरोध;
			शेष:
				वापस result;
			पूर्ण
			अवरोध;
		हाल 2:
			चयन (revision.minor) अणु
			हाल 1:
				result = get_पूर्णांकegrated_info_v2_1(bp, info);
				अवरोध;
			शेष:
				वापस result;
			पूर्ण
			अवरोध;
		शेष:
			वापस result;
		पूर्ण
	पूर्ण

	अगर (result != BP_RESULT_OK)
		वापस result;

	/* Sort voltage table from low to high*/
	क्रम (i = 1; i < NUMBER_OF_DISP_CLK_VOLTAGE; ++i) अणु
		क्रम (j = i; j > 0; --j) अणु
			अगर (info->disp_clk_voltage[j].max_supported_clk <
				info->disp_clk_voltage[j-1].max_supported_clk
				) अणु
				/* swap j and j - 1*/
				swap(info->disp_clk_voltage[j - 1],
				     info->disp_clk_voltage[j]);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

अटल क्रमागत bp_result bios_parser_get_vram_info(
		काष्ठा dc_bios *dcb,
		काष्ठा dc_vram_info *info)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	क्रमागत bp_result result = BP_RESULT_BADBIOSTABLE;
	काष्ठा atom_common_table_header *header;
	काष्ठा atom_data_revision revision;

	अगर (info && DATA_TABLES(vram_info)) अणु
		header = GET_IMAGE(काष्ठा atom_common_table_header,
					DATA_TABLES(vram_info));

		get_atom_data_table_revision(header, &revision);

		चयन (revision.major) अणु
		हाल 2:
			चयन (revision.minor) अणु
			हाल 3:
				result = get_vram_info_v23(bp, info);
				अवरोध;
			हाल 4:
				result = get_vram_info_v24(bp, info);
				अवरोध;
			हाल 5:
				result = get_vram_info_v25(bp, info);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;

		शेष:
			वापस result;
		पूर्ण

	पूर्ण
	वापस result;
पूर्ण

अटल काष्ठा पूर्णांकegrated_info *bios_parser_create_पूर्णांकegrated_info(
	काष्ठा dc_bios *dcb)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	काष्ठा पूर्णांकegrated_info *info = शून्य;

	info = kzalloc(माप(काष्ठा पूर्णांकegrated_info), GFP_KERNEL);

	अगर (info == शून्य) अणु
		ASSERT_CRITICAL(0);
		वापस शून्य;
	पूर्ण

	अगर (स्थिरruct_पूर्णांकegrated_info(bp, info) == BP_RESULT_OK)
		वापस info;

	kमुक्त(info);

	वापस शून्य;
पूर्ण

अटल क्रमागत bp_result update_slot_layout_info(
	काष्ठा dc_bios *dcb,
	अचिन्हित पूर्णांक i,
	काष्ठा slot_layout_info *slot_layout_info)
अणु
	अचिन्हित पूर्णांक record_offset;
	अचिन्हित पूर्णांक j;
	काष्ठा atom_display_object_path_v2 *object;
	काष्ठा atom_bracket_layout_record *record;
	काष्ठा atom_common_record_header *record_header;
	क्रमागत bp_result result;
	काष्ठा bios_parser *bp;
	काष्ठा object_info_table *tbl;
	काष्ठा display_object_info_table_v1_4 *v1_4;

	record = शून्य;
	record_header = शून्य;
	result = BP_RESULT_NORECORD;

	bp = BP_FROM_DCB(dcb);
	tbl = &bp->object_info_tbl;
	v1_4 = tbl->v1_4;

	object = &v1_4->display_path[i];
	record_offset = (अचिन्हित पूर्णांक)
		(object->disp_recorकरोffset) +
		(अचिन्हित पूर्णांक)(bp->object_info_tbl_offset);

	क्रम (;;) अणु

		record_header = (काष्ठा atom_common_record_header *)
			GET_IMAGE(काष्ठा atom_common_record_header,
			record_offset);
		अगर (record_header == शून्य) अणु
			result = BP_RESULT_BADBIOSTABLE;
			अवरोध;
		पूर्ण

		/* the end of the list */
		अगर (record_header->record_type == 0xff ||
			record_header->record_size == 0)	अणु
			अवरोध;
		पूर्ण

		अगर (record_header->record_type ==
			ATOM_BRACKET_LAYOUT_RECORD_TYPE &&
			माप(काष्ठा atom_bracket_layout_record)
			<= record_header->record_size) अणु
			record = (काष्ठा atom_bracket_layout_record *)
				(record_header);
			result = BP_RESULT_OK;
			अवरोध;
		पूर्ण

		record_offset += record_header->record_size;
	पूर्ण

	/* वापस अगर the record not found */
	अगर (result != BP_RESULT_OK)
		वापस result;

	/* get slot sizes */
	slot_layout_info->length = record->bracketlen;
	slot_layout_info->width = record->bracketwidth;

	/* get info क्रम each connector in the slot */
	slot_layout_info->num_of_connectors = record->conn_num;
	क्रम (j = 0; j < slot_layout_info->num_of_connectors; ++j) अणु
		slot_layout_info->connectors[j].connector_type =
			(क्रमागत connector_layout_type)
			(record->conn_info[j].connector_type);
		चयन (record->conn_info[j].connector_type) अणु
		हाल CONNECTOR_TYPE_DVI_D:
			slot_layout_info->connectors[j].connector_type =
				CONNECTOR_LAYOUT_TYPE_DVI_D;
			slot_layout_info->connectors[j].length =
				CONNECTOR_SIZE_DVI;
			अवरोध;

		हाल CONNECTOR_TYPE_HDMI:
			slot_layout_info->connectors[j].connector_type =
				CONNECTOR_LAYOUT_TYPE_HDMI;
			slot_layout_info->connectors[j].length =
				CONNECTOR_SIZE_HDMI;
			अवरोध;

		हाल CONNECTOR_TYPE_DISPLAY_PORT:
			slot_layout_info->connectors[j].connector_type =
				CONNECTOR_LAYOUT_TYPE_DP;
			slot_layout_info->connectors[j].length =
				CONNECTOR_SIZE_DP;
			अवरोध;

		हाल CONNECTOR_TYPE_MINI_DISPLAY_PORT:
			slot_layout_info->connectors[j].connector_type =
				CONNECTOR_LAYOUT_TYPE_MINI_DP;
			slot_layout_info->connectors[j].length =
				CONNECTOR_SIZE_MINI_DP;
			अवरोध;

		शेष:
			slot_layout_info->connectors[j].connector_type =
				CONNECTOR_LAYOUT_TYPE_UNKNOWN;
			slot_layout_info->connectors[j].length =
				CONNECTOR_SIZE_UNKNOWN;
		पूर्ण

		slot_layout_info->connectors[j].position =
			record->conn_info[j].position;
		slot_layout_info->connectors[j].connector_id =
			object_id_from_bios_object_id(
				record->conn_info[j].connectorobjid);
	पूर्ण
	वापस result;
पूर्ण


अटल क्रमागत bp_result get_bracket_layout_record(
	काष्ठा dc_bios *dcb,
	अचिन्हित पूर्णांक bracket_layout_id,
	काष्ठा slot_layout_info *slot_layout_info)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	क्रमागत bp_result result;
	काष्ठा object_info_table *tbl;
	काष्ठा display_object_info_table_v1_4 *v1_4;

	अगर (slot_layout_info == शून्य) अणु
		DC_LOG_DETECTION_EDID_PARSER("Invalid slot_layout_info\n");
		वापस BP_RESULT_BADINPUT;
	पूर्ण
	tbl = &bp->object_info_tbl;
	v1_4 = tbl->v1_4;

	result = BP_RESULT_NORECORD;
	क्रम (i = 0; i < v1_4->number_of_path; ++i)	अणु

		अगर (bracket_layout_id ==
			v1_4->display_path[i].display_objid) अणु
			result = update_slot_layout_info(dcb, i,
				slot_layout_info);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस result;
पूर्ण

अटल क्रमागत bp_result bios_get_board_layout_info(
	काष्ठा dc_bios *dcb,
	काष्ठा board_layout_info *board_layout_info)
अणु
	अचिन्हित पूर्णांक i;
	क्रमागत bp_result record_result;

	स्थिर अचिन्हित पूर्णांक slot_index_to_vbios_id[MAX_BOARD_SLOTS] = अणु
		GENERICOBJECT_BRACKET_LAYOUT_ENUM_ID1,
		GENERICOBJECT_BRACKET_LAYOUT_ENUM_ID2,
		0, 0
	पूर्ण;

	अगर (board_layout_info == शून्य) अणु
		DC_LOG_DETECTION_EDID_PARSER("Invalid board_layout_info\n");
		वापस BP_RESULT_BADINPUT;
	पूर्ण

	board_layout_info->num_of_slots = 0;

	क्रम (i = 0; i < MAX_BOARD_SLOTS; ++i) अणु
		record_result = get_bracket_layout_record(dcb,
			slot_index_to_vbios_id[i],
			&board_layout_info->slots[i]);

		अगर (record_result == BP_RESULT_NORECORD && i > 0)
			अवरोध; /* no more slots present in bios */
		अन्यथा अगर (record_result != BP_RESULT_OK)
			वापस record_result;  /* fail */

		++board_layout_info->num_of_slots;
	पूर्ण

	/* all data is valid */
	board_layout_info->is_number_of_slots_valid = 1;
	board_layout_info->is_slots_size_valid = 1;
	board_layout_info->is_connector_offsets_valid = 1;
	board_layout_info->is_connector_lengths_valid = 1;

	वापस BP_RESULT_OK;
पूर्ण


अटल uपूर्णांक16_t bios_parser_pack_data_tables(
	काष्ठा dc_bios *dcb,
	व्योम *dst)
अणु
#अगर_घोषित PACK_BIOS_DATA
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	काष्ठा atom_rom_header_v2_2 *rom_header = शून्य;
	काष्ठा atom_rom_header_v2_2 *packed_rom_header = शून्य;
	काष्ठा atom_common_table_header *data_tbl_header = शून्य;
	काष्ठा atom_master_list_of_data_tables_v2_1 *data_tbl_list = शून्य;
	काष्ठा atom_master_data_table_v2_1 *packed_master_data_tbl = शून्य;
	काष्ठा atom_data_revision tbl_rev = अणु0पूर्ण;
	uपूर्णांक16_t *rom_header_offset = शून्य;
	स्थिर uपूर्णांक8_t *bios = bp->base.bios;
	uपूर्णांक8_t *bios_dst = (uपूर्णांक8_t *)dst;
	uपूर्णांक16_t packed_rom_header_offset;
	uपूर्णांक16_t packed_masterdatatable_offset;
	uपूर्णांक16_t packed_data_tbl_offset;
	uपूर्णांक16_t data_tbl_offset;
	अचिन्हित पूर्णांक i;

	rom_header_offset =
		GET_IMAGE(uपूर्णांक16_t, OFFSET_TO_ATOM_ROM_HEADER_POINTER);

	अगर (!rom_header_offset)
		वापस 0;

	rom_header = GET_IMAGE(काष्ठा atom_rom_header_v2_2, *rom_header_offset);

	अगर (!rom_header)
		वापस 0;

	get_atom_data_table_revision(&rom_header->table_header, &tbl_rev);
	अगर (!(tbl_rev.major >= 2 && tbl_rev.minor >= 2))
		वापस 0;

	get_atom_data_table_revision(&bp->master_data_tbl->table_header, &tbl_rev);
	अगर (!(tbl_rev.major >= 2 && tbl_rev.minor >= 1))
		वापस 0;

	packed_rom_header_offset =
		OFFSET_TO_ATOM_ROM_HEADER_POINTER + माप(*rom_header_offset);

	packed_masterdatatable_offset =
		packed_rom_header_offset + rom_header->table_header.काष्ठाuresize;

	packed_data_tbl_offset =
		packed_masterdatatable_offset +
		bp->master_data_tbl->table_header.काष्ठाuresize;

	packed_rom_header =
		(काष्ठा atom_rom_header_v2_2 *)(bios_dst + packed_rom_header_offset);

	packed_master_data_tbl =
		(काष्ठा atom_master_data_table_v2_1 *)(bios_dst +
		packed_masterdatatable_offset);

	स_नकल(bios_dst, bios, OFFSET_TO_ATOM_ROM_HEADER_POINTER);

	*((uपूर्णांक16_t *)(bios_dst + OFFSET_TO_ATOM_ROM_HEADER_POINTER)) =
		packed_rom_header_offset;

	स_नकल(bios_dst + packed_rom_header_offset, rom_header,
		rom_header->table_header.काष्ठाuresize);

	packed_rom_header->masterdatatable_offset = packed_masterdatatable_offset;

	स_नकल(&packed_master_data_tbl->table_header,
		&bp->master_data_tbl->table_header,
		माप(bp->master_data_tbl->table_header));

	data_tbl_list = &bp->master_data_tbl->listOfdatatables;

	/* Each data table offset in data table list is 2 bytes,
	 * we can use that to iterate through listOfdatatables
	 * without knowing the name of each member.
	 */
	क्रम (i = 0; i < माप(*data_tbl_list)/माप(uपूर्णांक16_t); i++) अणु
		data_tbl_offset = *((uपूर्णांक16_t *)data_tbl_list + i);

		अगर (data_tbl_offset) अणु
			data_tbl_header =
				(काष्ठा atom_common_table_header *)(bios + data_tbl_offset);

			स_नकल(bios_dst + packed_data_tbl_offset, data_tbl_header,
				data_tbl_header->काष्ठाuresize);

			*((uपूर्णांक16_t *)&packed_master_data_tbl->listOfdatatables + i) =
				packed_data_tbl_offset;

			packed_data_tbl_offset += data_tbl_header->काष्ठाuresize;
		पूर्ण अन्यथा अणु
			*((uपूर्णांक16_t *)&packed_master_data_tbl->listOfdatatables + i) = 0;
		पूर्ण
	पूर्ण
	वापस packed_data_tbl_offset;
#पूर्ण_अगर
	// TODO: There is data bytes alignment issue, disable it क्रम now.
	वापस 0;
पूर्ण

अटल काष्ठा atom_dc_golden_table_v1 *bios_get_golden_table(
		काष्ठा bios_parser *bp,
		uपूर्णांक32_t rev_major,
		uपूर्णांक32_t rev_minor,
		uपूर्णांक16_t *dc_golden_table_ver)
अणु
	काष्ठा atom_display_controller_info_v4_4 *disp_cntl_tbl_4_4 = शून्य;
	uपूर्णांक32_t dc_golden_offset = 0;
	*dc_golden_table_ver = 0;

	अगर (!DATA_TABLES(dce_info))
		वापस शून्य;

	/* ver.4.4 or higher */
	चयन (rev_major) अणु
	हाल 4:
		चयन (rev_minor) अणु
		हाल 4:
			disp_cntl_tbl_4_4 = GET_IMAGE(काष्ठा atom_display_controller_info_v4_4,
									DATA_TABLES(dce_info));
			अगर (!disp_cntl_tbl_4_4)
				वापस शून्य;
			dc_golden_offset = DATA_TABLES(dce_info) + disp_cntl_tbl_4_4->dc_golden_table_offset;
			*dc_golden_table_ver = disp_cntl_tbl_4_4->dc_golden_table_ver;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (!dc_golden_offset)
		वापस शून्य;

	अगर (*dc_golden_table_ver != 1)
		वापस शून्य;

	वापस GET_IMAGE(काष्ठा atom_dc_golden_table_v1,
			dc_golden_offset);
पूर्ण

अटल क्रमागत bp_result bios_get_atom_dc_golden_table(
	काष्ठा dc_bios *dcb)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	क्रमागत bp_result result = BP_RESULT_OK;
	काष्ठा atom_dc_golden_table_v1 *atom_dc_golden_table = शून्य;
	काष्ठा atom_common_table_header *header;
	काष्ठा atom_data_revision tbl_revision;
	uपूर्णांक16_t dc_golden_table_ver = 0;

	header = GET_IMAGE(काष्ठा atom_common_table_header,
							DATA_TABLES(dce_info));
	अगर (!header)
		वापस BP_RESULT_UNSUPPORTED;

	get_atom_data_table_revision(header, &tbl_revision);

	atom_dc_golden_table = bios_get_golden_table(bp,
			tbl_revision.major,
			tbl_revision.minor,
			&dc_golden_table_ver);

	अगर (!atom_dc_golden_table)
		वापस BP_RESULT_UNSUPPORTED;

	dcb->golden_table.dc_golden_table_ver = dc_golden_table_ver;
	dcb->golden_table.aux_dphy_rx_control0_val = atom_dc_golden_table->aux_dphy_rx_control0_val;
	dcb->golden_table.aux_dphy_rx_control1_val = atom_dc_golden_table->aux_dphy_rx_control1_val;
	dcb->golden_table.aux_dphy_tx_control_val = atom_dc_golden_table->aux_dphy_tx_control_val;
	dcb->golden_table.dc_gpio_aux_ctrl_0_val = atom_dc_golden_table->dc_gpio_aux_ctrl_0_val;
	dcb->golden_table.dc_gpio_aux_ctrl_1_val = atom_dc_golden_table->dc_gpio_aux_ctrl_1_val;
	dcb->golden_table.dc_gpio_aux_ctrl_2_val = atom_dc_golden_table->dc_gpio_aux_ctrl_2_val;
	dcb->golden_table.dc_gpio_aux_ctrl_3_val = atom_dc_golden_table->dc_gpio_aux_ctrl_3_val;
	dcb->golden_table.dc_gpio_aux_ctrl_4_val = atom_dc_golden_table->dc_gpio_aux_ctrl_4_val;
	dcb->golden_table.dc_gpio_aux_ctrl_5_val = atom_dc_golden_table->dc_gpio_aux_ctrl_5_val;

	वापस result;
पूर्ण


अटल स्थिर काष्ठा dc_vbios_funcs vbios_funcs = अणु
	.get_connectors_number = bios_parser_get_connectors_number,

	.get_connector_id = bios_parser_get_connector_id,

	.get_src_obj = bios_parser_get_src_obj,

	.get_i2c_info = bios_parser_get_i2c_info,

	.get_hpd_info = bios_parser_get_hpd_info,

	.get_device_tag = bios_parser_get_device_tag,

	.get_spपढ़ो_spectrum_info = bios_parser_get_spपढ़ो_spectrum_info,

	.get_ss_entry_number = bios_parser_get_ss_entry_number,

	.get_embedded_panel_info = bios_parser_get_embedded_panel_info,

	.get_gpio_pin_info = bios_parser_get_gpio_pin_info,

	.get_encoder_cap_info = bios_parser_get_encoder_cap_info,

	.is_device_id_supported = bios_parser_is_device_id_supported,

	.is_accelerated_mode = bios_parser_is_accelerated_mode,

	.set_scratch_critical_state = bios_parser_set_scratch_critical_state,


/*	 COMMANDS */
	.encoder_control = bios_parser_encoder_control,

	.transmitter_control = bios_parser_transmitter_control,

	.enable_crtc = bios_parser_enable_crtc,

	.set_pixel_घड़ी = bios_parser_set_pixel_घड़ी,

	.set_dce_घड़ी = bios_parser_set_dce_घड़ी,

	.program_crtc_timing = bios_parser_program_crtc_timing,

	.enable_disp_घातer_gating = bios_parser_enable_disp_घातer_gating,

	.bios_parser_destroy = firmware_parser_destroy,

	.get_board_layout_info = bios_get_board_layout_info,
	.pack_data_tables = bios_parser_pack_data_tables,

	.get_atom_dc_golden_table = bios_get_atom_dc_golden_table,

	.enable_lvपंचांगa_control = bios_parser_enable_lvपंचांगa_control,

	.get_soc_bb_info = bios_parser_get_soc_bb_info,

	.get_disp_connector_caps_info = bios_parser_get_disp_connector_caps_info,

	.get_lttpr_caps = bios_parser_get_lttpr_caps,

	.get_lttpr_पूर्णांकerop = bios_parser_get_lttpr_पूर्णांकerop,
पूर्ण;

अटल bool bios_parser2_स्थिरruct(
	काष्ठा bios_parser *bp,
	काष्ठा bp_init_data *init,
	क्रमागत dce_version dce_version)
अणु
	uपूर्णांक16_t *rom_header_offset = शून्य;
	काष्ठा atom_rom_header_v2_2 *rom_header = शून्य;
	काष्ठा display_object_info_table_v1_4 *object_info_tbl;
	काष्ठा atom_data_revision tbl_rev = अणु0पूर्ण;

	अगर (!init)
		वापस false;

	अगर (!init->bios)
		वापस false;

	bp->base.funcs = &vbios_funcs;
	bp->base.bios = init->bios;
	bp->base.bios_size = bp->base.bios[OFFSET_TO_ATOM_ROM_IMAGE_SIZE] * BIOS_IMAGE_SIZE_UNIT;

	bp->base.ctx = init->ctx;

	bp->base.bios_local_image = शून्य;

	rom_header_offset =
			GET_IMAGE(uपूर्णांक16_t, OFFSET_TO_ATOM_ROM_HEADER_POINTER);

	अगर (!rom_header_offset)
		वापस false;

	rom_header = GET_IMAGE(काष्ठा atom_rom_header_v2_2, *rom_header_offset);

	अगर (!rom_header)
		वापस false;

	get_atom_data_table_revision(&rom_header->table_header, &tbl_rev);
	अगर (!(tbl_rev.major >= 2 && tbl_rev.minor >= 2))
		वापस false;

	bp->master_data_tbl =
		GET_IMAGE(काष्ठा atom_master_data_table_v2_1,
				rom_header->masterdatatable_offset);

	अगर (!bp->master_data_tbl)
		वापस false;

	bp->object_info_tbl_offset = DATA_TABLES(displayobjectinfo);

	अगर (!bp->object_info_tbl_offset)
		वापस false;

	object_info_tbl =
			GET_IMAGE(काष्ठा display_object_info_table_v1_4,
						bp->object_info_tbl_offset);

	अगर (!object_info_tbl)
		वापस false;

	get_atom_data_table_revision(&object_info_tbl->table_header,
		&bp->object_info_tbl.revision);

	अगर (bp->object_info_tbl.revision.major == 1
		&& bp->object_info_tbl.revision.minor >= 4) अणु
		काष्ठा display_object_info_table_v1_4 *tbl_v1_4;

		tbl_v1_4 = GET_IMAGE(काष्ठा display_object_info_table_v1_4,
			bp->object_info_tbl_offset);
		अगर (!tbl_v1_4)
			वापस false;

		bp->object_info_tbl.v1_4 = tbl_v1_4;
	पूर्ण अन्यथा
		वापस false;

	dal_firmware_parser_init_cmd_tbl(bp);
	dal_bios_parser_init_cmd_tbl_helper2(&bp->cmd_helper, dce_version);

	bp->base.पूर्णांकegrated_info = bios_parser_create_पूर्णांकegrated_info(&bp->base);
	bp->base.fw_info_valid = bios_parser_get_firmware_info(&bp->base, &bp->base.fw_info) == BP_RESULT_OK;
	bios_parser_get_vram_info(&bp->base, &bp->base.vram_info);

	वापस true;
पूर्ण

काष्ठा dc_bios *firmware_parser_create(
	काष्ठा bp_init_data *init,
	क्रमागत dce_version dce_version)
अणु
	काष्ठा bios_parser *bp = शून्य;

	bp = kzalloc(माप(काष्ठा bios_parser), GFP_KERNEL);
	अगर (!bp)
		वापस शून्य;

	अगर (bios_parser2_स्थिरruct(bp, init, dce_version))
		वापस &bp->base;

	kमुक्त(bp);
	वापस शून्य;
पूर्ण


