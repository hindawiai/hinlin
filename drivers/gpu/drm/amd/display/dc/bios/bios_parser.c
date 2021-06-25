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

#समावेश "atom.h"

#समावेश "dc_bios_types.h"
#समावेश "include/gpio_service_interface.h"
#समावेश "include/grph_object_ctrl_defs.h"
#समावेश "include/bios_parser_interface.h"
#समावेश "include/i2caux_interface.h"
#समावेश "include/logger_interface.h"

#समावेश "command_table.h"
#समावेश "bios_parser_helper.h"
#समावेश "command_table_helper.h"
#समावेश "bios_parser.h"
#समावेश "bios_parser_types_internal.h"
#समावेश "bios_parser_interface.h"

#समावेश "bios_parser_common.h"

#समावेश "dc.h"

#घोषणा THREE_PERCENT_OF_10000 300

#घोषणा LAST_RECORD_TYPE 0xff

#घोषणा DC_LOGGER \
	bp->base.ctx->logger

#घोषणा DATA_TABLES(table) (bp->master_data_tbl->ListOfDataTables.table)

अटल व्योम get_atom_data_table_revision(
	ATOM_COMMON_TABLE_HEADER *atom_data_tbl,
	काष्ठा atom_data_revision *tbl_revision);
अटल uपूर्णांक32_t get_src_obj_list(काष्ठा bios_parser *bp, ATOM_OBJECT *object,
	uपूर्णांक16_t **id_list);
अटल ATOM_OBJECT *get_bios_object(काष्ठा bios_parser *bp,
	काष्ठा graphics_object_id id);
अटल क्रमागत bp_result get_gpio_i2c_info(काष्ठा bios_parser *bp,
	ATOM_I2C_RECORD *record,
	काष्ठा graphics_object_i2c_info *info);
अटल ATOM_HPD_INT_RECORD *get_hpd_record(काष्ठा bios_parser *bp,
	ATOM_OBJECT *object);
अटल काष्ठा device_id device_type_from_device_id(uपूर्णांक16_t device_id);
अटल uपूर्णांक32_t संकेत_to_ss_id(क्रमागत as_संकेत_type संकेत);
अटल uपूर्णांक32_t get_support_mask_क्रम_device_id(काष्ठा device_id device_id);
अटल ATOM_ENCODER_CAP_RECORD_V2 *get_encoder_cap_record(
	काष्ठा bios_parser *bp,
	ATOM_OBJECT *object);

#घोषणा BIOS_IMAGE_SIZE_OFFSET 2
#घोषणा BIOS_IMAGE_SIZE_UNIT 512

/*****************************************************************************/
अटल bool bios_parser_स्थिरruct(
	काष्ठा bios_parser *bp,
	काष्ठा bp_init_data *init,
	क्रमागत dce_version dce_version);

अटल uपूर्णांक8_t bios_parser_get_connectors_number(
	काष्ठा dc_bios *dcb);

अटल क्रमागत bp_result bios_parser_get_embedded_panel_info(
	काष्ठा dc_bios *dcb,
	काष्ठा embedded_panel_info *info);

/*****************************************************************************/

काष्ठा dc_bios *bios_parser_create(
	काष्ठा bp_init_data *init,
	क्रमागत dce_version dce_version)
अणु
	काष्ठा bios_parser *bp = शून्य;

	bp = kzalloc(माप(काष्ठा bios_parser), GFP_KERNEL);
	अगर (!bp)
		वापस शून्य;

	अगर (bios_parser_स्थिरruct(bp, init, dce_version))
		वापस &bp->base;

	kमुक्त(bp);
	BREAK_TO_DEBUGGER();
	वापस शून्य;
पूर्ण

अटल व्योम bios_parser_deकाष्ठा(काष्ठा bios_parser *bp)
अणु
	kमुक्त(bp->base.bios_local_image);
	kमुक्त(bp->base.पूर्णांकegrated_info);
पूर्ण

अटल व्योम bios_parser_destroy(काष्ठा dc_bios **dcb)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(*dcb);

	अगर (!bp) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	bios_parser_deकाष्ठा(bp);

	kमुक्त(bp);
	*dcb = शून्य;
पूर्ण

अटल uपूर्णांक8_t get_number_of_objects(काष्ठा bios_parser *bp, uपूर्णांक32_t offset)
अणु
	ATOM_OBJECT_TABLE *table;

	uपूर्णांक32_t object_table_offset = bp->object_info_tbl_offset + offset;

	table = GET_IMAGE(ATOM_OBJECT_TABLE, object_table_offset);

	अगर (!table)
		वापस 0;
	अन्यथा
		वापस table->ucNumberOfObjects;
पूर्ण

अटल uपूर्णांक8_t bios_parser_get_connectors_number(काष्ठा dc_bios *dcb)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);

	वापस get_number_of_objects(bp,
		le16_to_cpu(bp->object_info_tbl.v1_1->usConnectorObjectTableOffset));
पूर्ण

अटल काष्ठा graphics_object_id bios_parser_get_connector_id(
	काष्ठा dc_bios *dcb,
	uपूर्णांक8_t i)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	काष्ठा graphics_object_id object_id = dal_graphics_object_id_init(
		0, ENUM_ID_UNKNOWN, OBJECT_TYPE_UNKNOWN);
	uपूर्णांक16_t id;

	uपूर्णांक32_t connector_table_offset = bp->object_info_tbl_offset
		+ le16_to_cpu(bp->object_info_tbl.v1_1->usConnectorObjectTableOffset);

	ATOM_OBJECT_TABLE *tbl =
		GET_IMAGE(ATOM_OBJECT_TABLE, connector_table_offset);

	अगर (!tbl) अणु
		dm_error("Can't get connector table from atom bios.\n");
		वापस object_id;
	पूर्ण

	अगर (tbl->ucNumberOfObjects <= i) अणु
		dm_error("Can't find connector id %d in connector table of size %d.\n",
			 i, tbl->ucNumberOfObjects);
		वापस object_id;
	पूर्ण

	id = le16_to_cpu(tbl->asObjects[i].usObjectID);
	object_id = object_id_from_bios_object_id(id);
	वापस object_id;
पूर्ण

अटल क्रमागत bp_result bios_parser_get_src_obj(काष्ठा dc_bios *dcb,
	काष्ठा graphics_object_id object_id, uपूर्णांक32_t index,
	काष्ठा graphics_object_id *src_object_id)
अणु
	uपूर्णांक32_t number;
	uपूर्णांक16_t *id;
	ATOM_OBJECT *object;
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);

	अगर (!src_object_id)
		वापस BP_RESULT_BADINPUT;

	object = get_bios_object(bp, object_id);

	अगर (!object) अणु
		BREAK_TO_DEBUGGER(); /* Invalid object id */
		वापस BP_RESULT_BADINPUT;
	पूर्ण

	number = get_src_obj_list(bp, object, &id);

	अगर (number <= index)
		वापस BP_RESULT_BADINPUT;

	*src_object_id = object_id_from_bios_object_id(id[index]);

	वापस BP_RESULT_OK;
पूर्ण

अटल क्रमागत bp_result bios_parser_get_i2c_info(काष्ठा dc_bios *dcb,
	काष्ठा graphics_object_id id,
	काष्ठा graphics_object_i2c_info *info)
अणु
	uपूर्णांक32_t offset;
	ATOM_OBJECT *object;
	ATOM_COMMON_RECORD_HEADER *header;
	ATOM_I2C_RECORD *record;
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);

	अगर (!info)
		वापस BP_RESULT_BADINPUT;

	object = get_bios_object(bp, id);

	अगर (!object)
		वापस BP_RESULT_BADINPUT;

	offset = le16_to_cpu(object->usRecordOffset)
			+ bp->object_info_tbl_offset;

	क्रम (;;) अणु
		header = GET_IMAGE(ATOM_COMMON_RECORD_HEADER, offset);

		अगर (!header)
			वापस BP_RESULT_BADBIOSTABLE;

		अगर (LAST_RECORD_TYPE == header->ucRecordType ||
			!header->ucRecordSize)
			अवरोध;

		अगर (ATOM_I2C_RECORD_TYPE == header->ucRecordType
			&& माप(ATOM_I2C_RECORD) <= header->ucRecordSize) अणु
			/* get the I2C info */
			record = (ATOM_I2C_RECORD *) header;

			अगर (get_gpio_i2c_info(bp, record, info) == BP_RESULT_OK)
				वापस BP_RESULT_OK;
		पूर्ण

		offset += header->ucRecordSize;
	पूर्ण

	वापस BP_RESULT_NORECORD;
पूर्ण

अटल क्रमागत bp_result bios_parser_get_hpd_info(काष्ठा dc_bios *dcb,
	काष्ठा graphics_object_id id,
	काष्ठा graphics_object_hpd_info *info)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	ATOM_OBJECT *object;
	ATOM_HPD_INT_RECORD *record = शून्य;

	अगर (!info)
		वापस BP_RESULT_BADINPUT;

	object = get_bios_object(bp, id);

	अगर (!object)
		वापस BP_RESULT_BADINPUT;

	record = get_hpd_record(bp, object);

	अगर (record != शून्य) अणु
		info->hpd_पूर्णांक_gpio_uid = record->ucHPDIntGPIOID;
		info->hpd_active = record->ucPlugged_PinState;
		वापस BP_RESULT_OK;
	पूर्ण

	वापस BP_RESULT_NORECORD;
पूर्ण

अटल क्रमागत bp_result bios_parser_get_device_tag_record(
	काष्ठा bios_parser *bp,
	ATOM_OBJECT *object,
	ATOM_CONNECTOR_DEVICE_TAG_RECORD **record)
अणु
	ATOM_COMMON_RECORD_HEADER *header;
	uपूर्णांक32_t offset;

	offset = le16_to_cpu(object->usRecordOffset)
			+ bp->object_info_tbl_offset;

	क्रम (;;) अणु
		header = GET_IMAGE(ATOM_COMMON_RECORD_HEADER, offset);

		अगर (!header)
			वापस BP_RESULT_BADBIOSTABLE;

		offset += header->ucRecordSize;

		अगर (LAST_RECORD_TYPE == header->ucRecordType ||
			!header->ucRecordSize)
			अवरोध;

		अगर (ATOM_CONNECTOR_DEVICE_TAG_RECORD_TYPE !=
			header->ucRecordType)
			जारी;

		अगर (माप(ATOM_CONNECTOR_DEVICE_TAG) > header->ucRecordSize)
			जारी;

		*record = (ATOM_CONNECTOR_DEVICE_TAG_RECORD *) header;
		वापस BP_RESULT_OK;
	पूर्ण

	वापस BP_RESULT_NORECORD;
पूर्ण

अटल क्रमागत bp_result bios_parser_get_device_tag(
	काष्ठा dc_bios *dcb,
	काष्ठा graphics_object_id connector_object_id,
	uपूर्णांक32_t device_tag_index,
	काष्ठा connector_device_tag_info *info)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	ATOM_OBJECT *object;
	ATOM_CONNECTOR_DEVICE_TAG_RECORD *record = शून्य;
	ATOM_CONNECTOR_DEVICE_TAG *device_tag;

	अगर (!info)
		वापस BP_RESULT_BADINPUT;

	/* getBiosObject will वापस MXM object */
	object = get_bios_object(bp, connector_object_id);

	अगर (!object) अणु
		BREAK_TO_DEBUGGER(); /* Invalid object id */
		वापस BP_RESULT_BADINPUT;
	पूर्ण

	अगर (bios_parser_get_device_tag_record(bp, object, &record)
		!= BP_RESULT_OK)
		वापस BP_RESULT_NORECORD;

	अगर (device_tag_index >= record->ucNumberOfDevice)
		वापस BP_RESULT_NORECORD;

	device_tag = &record->asDeviceTag[device_tag_index];

	info->acpi_device = le32_to_cpu(device_tag->ulACPIDeviceEnum);
	info->dev_id =
		device_type_from_device_id(le16_to_cpu(device_tag->usDeviceID));

	वापस BP_RESULT_OK;
पूर्ण

अटल क्रमागत bp_result get_firmware_info_v1_4(
	काष्ठा bios_parser *bp,
	काष्ठा dc_firmware_info *info);
अटल क्रमागत bp_result get_firmware_info_v2_1(
	काष्ठा bios_parser *bp,
	काष्ठा dc_firmware_info *info);
अटल क्रमागत bp_result get_firmware_info_v2_2(
	काष्ठा bios_parser *bp,
	काष्ठा dc_firmware_info *info);

अटल क्रमागत bp_result bios_parser_get_firmware_info(
	काष्ठा dc_bios *dcb,
	काष्ठा dc_firmware_info *info)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	क्रमागत bp_result result = BP_RESULT_BADBIOSTABLE;
	ATOM_COMMON_TABLE_HEADER *header;
	काष्ठा atom_data_revision revision;

	अगर (info && DATA_TABLES(FirmwareInfo)) अणु
		header = GET_IMAGE(ATOM_COMMON_TABLE_HEADER,
			DATA_TABLES(FirmwareInfo));
		get_atom_data_table_revision(header, &revision);
		चयन (revision.major) अणु
		हाल 1:
			चयन (revision.minor) अणु
			हाल 4:
				result = get_firmware_info_v1_4(bp, info);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;

		हाल 2:
			चयन (revision.minor) अणु
			हाल 1:
				result = get_firmware_info_v2_1(bp, info);
				अवरोध;
			हाल 2:
				result = get_firmware_info_v2_2(bp, info);
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

अटल क्रमागत bp_result get_firmware_info_v1_4(
	काष्ठा bios_parser *bp,
	काष्ठा dc_firmware_info *info)
अणु
	ATOM_FIRMWARE_INFO_V1_4 *firmware_info =
		GET_IMAGE(ATOM_FIRMWARE_INFO_V1_4,
			DATA_TABLES(FirmwareInfo));

	अगर (!info)
		वापस BP_RESULT_BADINPUT;

	अगर (!firmware_info)
		वापस BP_RESULT_BADBIOSTABLE;

	स_रखो(info, 0, माप(*info));

	/* Pixel घड़ी pll inक्रमmation. We need to convert from 10KHz units पूर्णांकo
	 * KHz units */
	info->pll_info.crystal_frequency =
		le16_to_cpu(firmware_info->usReferenceClock) * 10;
	info->pll_info.min_input_pxl_clk_pll_frequency =
		le16_to_cpu(firmware_info->usMinPixelClockPLL_Input) * 10;
	info->pll_info.max_input_pxl_clk_pll_frequency =
		le16_to_cpu(firmware_info->usMaxPixelClockPLL_Input) * 10;
	info->pll_info.min_output_pxl_clk_pll_frequency =
		le32_to_cpu(firmware_info->ulMinPixelClockPLL_Output) * 10;
	info->pll_info.max_output_pxl_clk_pll_frequency =
		le32_to_cpu(firmware_info->ulMaxPixelClockPLL_Output) * 10;

	अगर (firmware_info->usFirmwareCapability.sbfAccess.MemoryClockSS_Support)
		/* Since there is no inक्रमmation on the SS, report conservative
		 * value 3% क्रम bandwidth calculation */
		/* unit of 0.01% */
		info->feature.memory_clk_ss_percentage = THREE_PERCENT_OF_10000;

	अगर (firmware_info->usFirmwareCapability.sbfAccess.EngineClockSS_Support)
		/* Since there is no inक्रमmation on the SS,report conservative
		 * value 3% क्रम bandwidth calculation */
		/* unit of 0.01% */
		info->feature.engine_clk_ss_percentage = THREE_PERCENT_OF_10000;

	वापस BP_RESULT_OK;
पूर्ण

अटल क्रमागत bp_result get_ss_info_v3_1(
	काष्ठा bios_parser *bp,
	uपूर्णांक32_t id,
	uपूर्णांक32_t index,
	काष्ठा spपढ़ो_spectrum_info *ss_info);

अटल क्रमागत bp_result get_firmware_info_v2_1(
	काष्ठा bios_parser *bp,
	काष्ठा dc_firmware_info *info)
अणु
	ATOM_FIRMWARE_INFO_V2_1 *firmwareInfo =
		GET_IMAGE(ATOM_FIRMWARE_INFO_V2_1, DATA_TABLES(FirmwareInfo));
	काष्ठा spपढ़ो_spectrum_info पूर्णांकernalSS;
	uपूर्णांक32_t index;

	अगर (!info)
		वापस BP_RESULT_BADINPUT;

	अगर (!firmwareInfo)
		वापस BP_RESULT_BADBIOSTABLE;

	स_रखो(info, 0, माप(*info));

	/* Pixel घड़ी pll inक्रमmation. We need to convert from 10KHz units पूर्णांकo
	 * KHz units */
	info->pll_info.crystal_frequency =
		le16_to_cpu(firmwareInfo->usCoreReferenceClock) * 10;
	info->pll_info.min_input_pxl_clk_pll_frequency =
		le16_to_cpu(firmwareInfo->usMinPixelClockPLL_Input) * 10;
	info->pll_info.max_input_pxl_clk_pll_frequency =
		le16_to_cpu(firmwareInfo->usMaxPixelClockPLL_Input) * 10;
	info->pll_info.min_output_pxl_clk_pll_frequency =
		le32_to_cpu(firmwareInfo->ulMinPixelClockPLL_Output) * 10;
	info->pll_info.max_output_pxl_clk_pll_frequency =
		le32_to_cpu(firmwareInfo->ulMaxPixelClockPLL_Output) * 10;
	info->शेष_display_engine_pll_frequency =
		le32_to_cpu(firmwareInfo->ulDefaultDispEngineClkFreq) * 10;
	info->बाह्यal_घड़ी_source_frequency_क्रम_dp =
		le16_to_cpu(firmwareInfo->usUniphyDPModeExtClkFreq) * 10;
	info->min_allowed_bl_level = firmwareInfo->ucMinAllowedBL_Level;

	/* There should be only one entry in the SS info table क्रम Memory Clock
	 */
	index = 0;
	अगर (firmwareInfo->usFirmwareCapability.sbfAccess.MemoryClockSS_Support)
		/* Since there is no inक्रमmation क्रम बाह्यal SS, report
		 *  conservative value 3% क्रम bandwidth calculation */
		/* unit of 0.01% */
		info->feature.memory_clk_ss_percentage = THREE_PERCENT_OF_10000;
	अन्यथा अगर (get_ss_info_v3_1(bp,
		ASIC_INTERNAL_MEMORY_SS, index, &पूर्णांकernalSS) == BP_RESULT_OK) अणु
		अगर (पूर्णांकernalSS.spपढ़ो_spectrum_percentage) अणु
			info->feature.memory_clk_ss_percentage =
				पूर्णांकernalSS.spपढ़ो_spectrum_percentage;
			अगर (पूर्णांकernalSS.type.CENTER_MODE) अणु
				/* अगर it is centermode, the exact SS Percentage
				 * will be round up of half of the percentage
				 * reported in the SS table */
				++info->feature.memory_clk_ss_percentage;
				info->feature.memory_clk_ss_percentage /= 2;
			पूर्ण
		पूर्ण
	पूर्ण

	/* There should be only one entry in the SS info table क्रम Engine Clock
	 */
	index = 1;
	अगर (firmwareInfo->usFirmwareCapability.sbfAccess.EngineClockSS_Support)
		/* Since there is no inक्रमmation क्रम बाह्यal SS, report
		 * conservative value 3% क्रम bandwidth calculation */
		/* unit of 0.01% */
		info->feature.engine_clk_ss_percentage = THREE_PERCENT_OF_10000;
	अन्यथा अगर (get_ss_info_v3_1(bp,
		ASIC_INTERNAL_ENGINE_SS, index, &पूर्णांकernalSS) == BP_RESULT_OK) अणु
		अगर (पूर्णांकernalSS.spपढ़ो_spectrum_percentage) अणु
			info->feature.engine_clk_ss_percentage =
				पूर्णांकernalSS.spपढ़ो_spectrum_percentage;
			अगर (पूर्णांकernalSS.type.CENTER_MODE) अणु
				/* अगर it is centermode, the exact SS Percentage
				 * will be round up of half of the percentage
				 * reported in the SS table */
				++info->feature.engine_clk_ss_percentage;
				info->feature.engine_clk_ss_percentage /= 2;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस BP_RESULT_OK;
पूर्ण

अटल क्रमागत bp_result get_firmware_info_v2_2(
	काष्ठा bios_parser *bp,
	काष्ठा dc_firmware_info *info)
अणु
	ATOM_FIRMWARE_INFO_V2_2 *firmware_info;
	काष्ठा spपढ़ो_spectrum_info पूर्णांकernal_ss;
	uपूर्णांक32_t index;

	अगर (!info)
		वापस BP_RESULT_BADINPUT;

	firmware_info = GET_IMAGE(ATOM_FIRMWARE_INFO_V2_2,
		DATA_TABLES(FirmwareInfo));

	अगर (!firmware_info)
		वापस BP_RESULT_BADBIOSTABLE;

	स_रखो(info, 0, माप(*info));

	/* Pixel घड़ी pll inक्रमmation. We need to convert from 10KHz units पूर्णांकo
	 * KHz units */
	info->pll_info.crystal_frequency =
		le16_to_cpu(firmware_info->usCoreReferenceClock) * 10;
	info->pll_info.min_input_pxl_clk_pll_frequency =
		le16_to_cpu(firmware_info->usMinPixelClockPLL_Input) * 10;
	info->pll_info.max_input_pxl_clk_pll_frequency =
		le16_to_cpu(firmware_info->usMaxPixelClockPLL_Input) * 10;
	info->pll_info.min_output_pxl_clk_pll_frequency =
		le32_to_cpu(firmware_info->ulMinPixelClockPLL_Output) * 10;
	info->pll_info.max_output_pxl_clk_pll_frequency =
		le32_to_cpu(firmware_info->ulMaxPixelClockPLL_Output) * 10;
	info->शेष_display_engine_pll_frequency =
		le32_to_cpu(firmware_info->ulDefaultDispEngineClkFreq) * 10;
	info->बाह्यal_घड़ी_source_frequency_क्रम_dp =
		le16_to_cpu(firmware_info->usUniphyDPModeExtClkFreq) * 10;

	/* There should be only one entry in the SS info table क्रम Memory Clock
	 */
	index = 0;
	अगर (firmware_info->usFirmwareCapability.sbfAccess.MemoryClockSS_Support)
		/* Since there is no inक्रमmation क्रम बाह्यal SS, report
		 *  conservative value 3% क्रम bandwidth calculation */
		/* unit of 0.01% */
		info->feature.memory_clk_ss_percentage = THREE_PERCENT_OF_10000;
	अन्यथा अगर (get_ss_info_v3_1(bp,
			ASIC_INTERNAL_MEMORY_SS, index, &पूर्णांकernal_ss) == BP_RESULT_OK) अणु
		अगर (पूर्णांकernal_ss.spपढ़ो_spectrum_percentage) अणु
			info->feature.memory_clk_ss_percentage =
					पूर्णांकernal_ss.spपढ़ो_spectrum_percentage;
			अगर (पूर्णांकernal_ss.type.CENTER_MODE) अणु
				/* अगर it is centermode, the exact SS Percentage
				 * will be round up of half of the percentage
				 * reported in the SS table */
				++info->feature.memory_clk_ss_percentage;
				info->feature.memory_clk_ss_percentage /= 2;
			पूर्ण
		पूर्ण
	पूर्ण

	/* There should be only one entry in the SS info table क्रम Engine Clock
	 */
	index = 1;
	अगर (firmware_info->usFirmwareCapability.sbfAccess.EngineClockSS_Support)
		/* Since there is no inक्रमmation क्रम बाह्यal SS, report
		 * conservative value 3% क्रम bandwidth calculation */
		/* unit of 0.01% */
		info->feature.engine_clk_ss_percentage = THREE_PERCENT_OF_10000;
	अन्यथा अगर (get_ss_info_v3_1(bp,
			ASIC_INTERNAL_ENGINE_SS, index, &पूर्णांकernal_ss) == BP_RESULT_OK) अणु
		अगर (पूर्णांकernal_ss.spपढ़ो_spectrum_percentage) अणु
			info->feature.engine_clk_ss_percentage =
					पूर्णांकernal_ss.spपढ़ो_spectrum_percentage;
			अगर (पूर्णांकernal_ss.type.CENTER_MODE) अणु
				/* अगर it is centermode, the exact SS Percentage
				 * will be round up of half of the percentage
				 * reported in the SS table */
				++info->feature.engine_clk_ss_percentage;
				info->feature.engine_clk_ss_percentage /= 2;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Remote Display */
	info->remote_display_config = firmware_info->ucRemoteDisplayConfig;

	/* Is allowed minimum BL level */
	info->min_allowed_bl_level = firmware_info->ucMinAllowedBL_Level;
	/* Used starting from CI */
	info->smu_gpu_pll_output_freq =
			(uपूर्णांक32_t) (le32_to_cpu(firmware_info->ulGPUPLL_OutputFreq) * 10);

	वापस BP_RESULT_OK;
पूर्ण

अटल क्रमागत bp_result get_ss_info_v3_1(
	काष्ठा bios_parser *bp,
	uपूर्णांक32_t id,
	uपूर्णांक32_t index,
	काष्ठा spपढ़ो_spectrum_info *ss_info)
अणु
	ATOM_ASIC_INTERNAL_SS_INFO_V3 *ss_table_header_include;
	ATOM_ASIC_SS_ASSIGNMENT_V3 *tbl;
	uपूर्णांक32_t table_size;
	uपूर्णांक32_t i;
	uपूर्णांक32_t table_index = 0;

	अगर (!ss_info)
		वापस BP_RESULT_BADINPUT;

	अगर (!DATA_TABLES(ASIC_InternalSS_Info))
		वापस BP_RESULT_UNSUPPORTED;

	ss_table_header_include = GET_IMAGE(ATOM_ASIC_INTERNAL_SS_INFO_V3,
		DATA_TABLES(ASIC_InternalSS_Info));
	table_size =
		(le16_to_cpu(ss_table_header_include->sHeader.usStructureSize)
				- माप(ATOM_COMMON_TABLE_HEADER))
				/ माप(ATOM_ASIC_SS_ASSIGNMENT_V3);

	tbl = (ATOM_ASIC_SS_ASSIGNMENT_V3 *)
				&ss_table_header_include->asSpपढ़ोSpectrum[0];

	स_रखो(ss_info, 0, माप(काष्ठा spपढ़ो_spectrum_info));

	क्रम (i = 0; i < table_size; i++) अणु
		अगर (tbl[i].ucClockIndication != (uपूर्णांक8_t) id)
			जारी;

		अगर (table_index != index) अणु
			table_index++;
			जारी;
		पूर्ण
		/* VBIOS पूर्णांकroduced new defines क्रम Version 3, same values as
		 *  beक्रमe, so now use these new ones क्रम Version 3.
		 * Shouldn't affect field VBIOS's V3 as define values are still
		 *  same.
		 * #घोषणा SS_MODE_V3_CENTRE_SPREAD_MASK                0x01
		 * #घोषणा SS_MODE_V3_EXTERNAL_SS_MASK                  0x02

		 * Old VBIOS defines:
		 * #घोषणा ATOM_SS_CENTRE_SPREAD_MODE_MASK        0x00000001
		 * #घोषणा ATOM_EXTERNAL_SS_MASK                  0x00000002
		 */

		अगर (SS_MODE_V3_EXTERNAL_SS_MASK & tbl[i].ucSpपढ़ोSpectrumMode)
			ss_info->type.EXTERNAL = true;

		अगर (SS_MODE_V3_CENTRE_SPREAD_MASK & tbl[i].ucSpपढ़ोSpectrumMode)
			ss_info->type.CENTER_MODE = true;

		/* Older VBIOS (in field) always provides SS percentage in 0.01%
		 * units set Divider to 100 */
		ss_info->spपढ़ो_percentage_भागider = 100;

		/* #घोषणा SS_MODE_V3_PERCENTAGE_DIV_BY_1000_MASK 0x10 */
		अगर (SS_MODE_V3_PERCENTAGE_DIV_BY_1000_MASK
				& tbl[i].ucSpपढ़ोSpectrumMode)
			ss_info->spपढ़ो_percentage_भागider = 1000;

		ss_info->type.STEP_AND_DELAY_INFO = false;
		/* convert [10KHz] पूर्णांकo [KHz] */
		ss_info->target_घड़ी_range =
				le32_to_cpu(tbl[i].ulTargetClockRange) * 10;
		ss_info->spपढ़ो_spectrum_percentage =
				(uपूर्णांक32_t)le16_to_cpu(tbl[i].usSpपढ़ोSpectrumPercentage);
		ss_info->spपढ़ो_spectrum_range =
				(uपूर्णांक32_t)(le16_to_cpu(tbl[i].usSpपढ़ोRateIn10Hz) * 10);

		वापस BP_RESULT_OK;
	पूर्ण
	वापस BP_RESULT_NORECORD;
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

अटल क्रमागत bp_result bios_parser_adjust_pixel_घड़ी(
	काष्ठा dc_bios *dcb,
	काष्ठा bp_adjust_pixel_घड़ी_parameters *bp_params)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);

	अगर (!bp->cmd_tbl.adjust_display_pll)
		वापस BP_RESULT_FAILURE;

	वापस bp->cmd_tbl.adjust_display_pll(bp, bp_params);
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

अटल क्रमागत bp_result bios_parser_enable_spपढ़ो_spectrum_on_ppll(
	काष्ठा dc_bios *dcb,
	काष्ठा bp_spपढ़ो_spectrum_parameters *bp_params,
	bool enable)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);

	अगर (!bp->cmd_tbl.enable_spपढ़ो_spectrum_on_ppll)
		वापस BP_RESULT_FAILURE;

	वापस bp->cmd_tbl.enable_spपढ़ो_spectrum_on_ppll(
			bp, bp_params, enable);

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

अटल क्रमागत bp_result bios_parser_program_display_engine_pll(
	काष्ठा dc_bios *dcb,
	काष्ठा bp_pixel_घड़ी_parameters *bp_params)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);

	अगर (!bp->cmd_tbl.program_घड़ी)
		वापस BP_RESULT_FAILURE;

	वापस bp->cmd_tbl.program_घड़ी(bp, bp_params);

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

अटल bool bios_parser_is_device_id_supported(
	काष्ठा dc_bios *dcb,
	काष्ठा device_id id)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);

	uपूर्णांक32_t mask = get_support_mask_क्रम_device_id(id);

	वापस (le16_to_cpu(bp->object_info_tbl.v1_1->usDeviceSupport) & mask) != 0;
पूर्ण

अटल ATOM_HPD_INT_RECORD *get_hpd_record(काष्ठा bios_parser *bp,
	ATOM_OBJECT *object)
अणु
	ATOM_COMMON_RECORD_HEADER *header;
	uपूर्णांक32_t offset;

	अगर (!object) अणु
		BREAK_TO_DEBUGGER(); /* Invalid object */
		वापस शून्य;
	पूर्ण

	offset = le16_to_cpu(object->usRecordOffset)
			+ bp->object_info_tbl_offset;

	क्रम (;;) अणु
		header = GET_IMAGE(ATOM_COMMON_RECORD_HEADER, offset);

		अगर (!header)
			वापस शून्य;

		अगर (LAST_RECORD_TYPE == header->ucRecordType ||
			!header->ucRecordSize)
			अवरोध;

		अगर (ATOM_HPD_INT_RECORD_TYPE == header->ucRecordType
			&& माप(ATOM_HPD_INT_RECORD) <= header->ucRecordSize)
			वापस (ATOM_HPD_INT_RECORD *) header;

		offset += header->ucRecordSize;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल क्रमागत bp_result get_ss_info_from_ss_info_table(
	काष्ठा bios_parser *bp,
	uपूर्णांक32_t id,
	काष्ठा spपढ़ो_spectrum_info *ss_info);
अटल क्रमागत bp_result get_ss_info_from_tbl(
	काष्ठा bios_parser *bp,
	uपूर्णांक32_t id,
	काष्ठा spपढ़ो_spectrum_info *ss_info);
/**
 * bios_parser_get_spपढ़ो_spectrum_info
 * Get spपढ़ो spectrum inक्रमmation from the ASIC_InternalSS_Info(ver 2.1 or
 * ver 3.1) or SS_Info table from the VBIOS. Currently ASIC_InternalSS_Info
 * ver 2.1 can co-exist with SS_Info table. Expect ASIC_InternalSS_Info ver 3.1,
 * there is only one entry क्रम each संकेत /ss id.  However, there is
 * no planning of supporting multiple spपढ़ो Sprectum entry क्रम EverGreen
 * @dcb:     poपूर्णांकer to the DC BIOS
 * @संकेत:  ASSignalType to be converted to info index
 * @index:   number of entries that match the converted info index
 * @ss_info: sprectrum inक्रमmation काष्ठाure,
 * वापस:   Bios parser result code
 */
अटल क्रमागत bp_result bios_parser_get_spपढ़ो_spectrum_info(
	काष्ठा dc_bios *dcb,
	क्रमागत as_संकेत_type संकेत,
	uपूर्णांक32_t index,
	काष्ठा spपढ़ो_spectrum_info *ss_info)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	क्रमागत bp_result result = BP_RESULT_UNSUPPORTED;
	uपूर्णांक32_t clk_id_ss = 0;
	ATOM_COMMON_TABLE_HEADER *header;
	काष्ठा atom_data_revision tbl_revision;

	अगर (!ss_info) /* check क्रम bad input */
		वापस BP_RESULT_BADINPUT;
	/* संकेत translation */
	clk_id_ss = संकेत_to_ss_id(संकेत);

	अगर (!DATA_TABLES(ASIC_InternalSS_Info))
		अगर (!index)
			वापस get_ss_info_from_ss_info_table(bp, clk_id_ss,
				ss_info);

	header = GET_IMAGE(ATOM_COMMON_TABLE_HEADER,
		DATA_TABLES(ASIC_InternalSS_Info));
	get_atom_data_table_revision(header, &tbl_revision);

	चयन (tbl_revision.major) अणु
	हाल 2:
		चयन (tbl_revision.minor) अणु
		हाल 1:
			/* there can not be more then one entry क्रम Internal
			 * SS Info table version 2.1 */
			अगर (!index)
				वापस get_ss_info_from_tbl(bp, clk_id_ss,
						ss_info);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 3:
		चयन (tbl_revision.minor) अणु
		हाल 1:
			वापस get_ss_info_v3_1(bp, clk_id_ss, index, ss_info);
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

अटल क्रमागत bp_result get_ss_info_from_पूर्णांकernal_ss_info_tbl_V2_1(
	काष्ठा bios_parser *bp,
	uपूर्णांक32_t id,
	काष्ठा spपढ़ो_spectrum_info *info);

/**
 * get_ss_info_from_table
 * Get spपढ़ो sprectrum inक्रमmation from the ASIC_InternalSS_Info Ver 2.1 or
 * SS_Info table from the VBIOS
 * There can not be more than 1 entry क्रम  ASIC_InternalSS_Info Ver 2.1 or
 * SS_Info.
 *
 * @bp:      poपूर्णांकer to the BIOS parser
 * @id:      spपढ़ो sprectrum info index
 * @ss_info: sprectrum inक्रमmation काष्ठाure,
 * वापस:   BIOS parser result code
 */
अटल क्रमागत bp_result get_ss_info_from_tbl(
	काष्ठा bios_parser *bp,
	uपूर्णांक32_t id,
	काष्ठा spपढ़ो_spectrum_info *ss_info)
अणु
	अगर (!ss_info) /* check क्रम bad input, अगर ss_info is not शून्य */
		वापस BP_RESULT_BADINPUT;
	/* क्रम SS_Info table only support DP and LVDS */
	अगर (id == ASIC_INTERNAL_SS_ON_DP || id == ASIC_INTERNAL_SS_ON_LVDS)
		वापस get_ss_info_from_ss_info_table(bp, id, ss_info);
	अन्यथा
		वापस get_ss_info_from_पूर्णांकernal_ss_info_tbl_V2_1(bp, id,
			ss_info);
पूर्ण

/**
 * get_ss_info_from_पूर्णांकernal_ss_info_tbl_V2_1
 * Get spपढ़ो sprectrum inक्रमmation from the ASIC_InternalSS_Info table Ver 2.1
 * from the VBIOS
 * There will not be multiple entry क्रम Ver 2.1
 *
 * @bp:    poपूर्णांकer to the Bios parser
 * @id:    spपढ़ो sprectrum info index
 * @info:  sprectrum inक्रमmation काष्ठाure,
 * वापस: Bios parser result code
 */
अटल क्रमागत bp_result get_ss_info_from_पूर्णांकernal_ss_info_tbl_V2_1(
	काष्ठा bios_parser *bp,
	uपूर्णांक32_t id,
	काष्ठा spपढ़ो_spectrum_info *info)
अणु
	क्रमागत bp_result result = BP_RESULT_UNSUPPORTED;
	ATOM_ASIC_INTERNAL_SS_INFO_V2 *header;
	ATOM_ASIC_SS_ASSIGNMENT_V2 *tbl;
	uपूर्णांक32_t tbl_size, i;

	अगर (!DATA_TABLES(ASIC_InternalSS_Info))
		वापस result;

	header = GET_IMAGE(ATOM_ASIC_INTERNAL_SS_INFO_V2,
		DATA_TABLES(ASIC_InternalSS_Info));

	स_रखो(info, 0, माप(काष्ठा spपढ़ो_spectrum_info));

	tbl_size = (le16_to_cpu(header->sHeader.usStructureSize)
			- माप(ATOM_COMMON_TABLE_HEADER))
					/ माप(ATOM_ASIC_SS_ASSIGNMENT_V2);

	tbl = (ATOM_ASIC_SS_ASSIGNMENT_V2 *)
					&(header->asSpपढ़ोSpectrum[0]);
	क्रम (i = 0; i < tbl_size; i++) अणु
		result = BP_RESULT_NORECORD;

		अगर (tbl[i].ucClockIndication != (uपूर्णांक8_t)id)
			जारी;

		अगर (ATOM_EXTERNAL_SS_MASK
			& tbl[i].ucSpपढ़ोSpectrumMode) अणु
			info->type.EXTERNAL = true;
		पूर्ण
		अगर (ATOM_SS_CENTRE_SPREAD_MODE_MASK
			& tbl[i].ucSpपढ़ोSpectrumMode) अणु
			info->type.CENTER_MODE = true;
		पूर्ण
		info->type.STEP_AND_DELAY_INFO = false;
		/* convert [10KHz] पूर्णांकo [KHz] */
		info->target_घड़ी_range =
			le32_to_cpu(tbl[i].ulTargetClockRange) * 10;
		info->spपढ़ो_spectrum_percentage =
			(uपूर्णांक32_t)le16_to_cpu(tbl[i].usSpपढ़ोSpectrumPercentage);
		info->spपढ़ो_spectrum_range =
			(uपूर्णांक32_t)(le16_to_cpu(tbl[i].usSpपढ़ोRateIn10Hz) * 10);
		result = BP_RESULT_OK;
		अवरोध;
	पूर्ण

	वापस result;

पूर्ण

/**
 * get_ss_info_from_ss_info_table
 * Get spपढ़ो sprectrum inक्रमmation from the SS_Info table from the VBIOS
 * अगर the poपूर्णांकer to info is शून्य, indicate the caller what to know the number
 * of entries that matches the id
 * क्रम, the SS_Info table, there should not be more than 1 entry match.
 *
 * @bp:      poपूर्णांकer to the Bios parser
 * @id:      spपढ़ो sprectrum id
 * @ss_info: sprectrum inक्रमmation काष्ठाure,
 * वापस:   Bios parser result code
 */
अटल क्रमागत bp_result get_ss_info_from_ss_info_table(
	काष्ठा bios_parser *bp,
	uपूर्णांक32_t id,
	काष्ठा spपढ़ो_spectrum_info *ss_info)
अणु
	क्रमागत bp_result result = BP_RESULT_UNSUPPORTED;
	ATOM_SPREAD_SPECTRUM_INFO *tbl;
	ATOM_COMMON_TABLE_HEADER *header;
	uपूर्णांक32_t table_size;
	uपूर्णांक32_t i;
	uपूर्णांक32_t id_local = SS_ID_UNKNOWN;
	काष्ठा atom_data_revision revision;

	/* exist of the SS_Info table */
	/* check क्रम bad input, pSSinfo can not be शून्य */
	अगर (!DATA_TABLES(SS_Info) || !ss_info)
		वापस result;

	header = GET_IMAGE(ATOM_COMMON_TABLE_HEADER, DATA_TABLES(SS_Info));
	get_atom_data_table_revision(header, &revision);

	tbl = GET_IMAGE(ATOM_SPREAD_SPECTRUM_INFO, DATA_TABLES(SS_Info));

	अगर (1 != revision.major || 2 > revision.minor)
		वापस result;

	/* have to convert from Internal_SS क्रमmat to SS_Info क्रमmat */
	चयन (id) अणु
	हाल ASIC_INTERNAL_SS_ON_DP:
		id_local = SS_ID_DP1;
		अवरोध;
	हाल ASIC_INTERNAL_SS_ON_LVDS:
	अणु
		काष्ठा embedded_panel_info panel_info;

		अगर (bios_parser_get_embedded_panel_info(&bp->base, &panel_info)
				== BP_RESULT_OK)
			id_local = panel_info.ss_id;
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	अगर (id_local == SS_ID_UNKNOWN)
		वापस result;

	table_size = (le16_to_cpu(tbl->sHeader.usStructureSize) -
			माप(ATOM_COMMON_TABLE_HEADER)) /
					माप(ATOM_SPREAD_SPECTRUM_ASSIGNMENT);

	क्रम (i = 0; i < table_size; i++) अणु
		अगर (id_local != (uपूर्णांक32_t)tbl->asSS_Info[i].ucSS_Id)
			जारी;

		स_रखो(ss_info, 0, माप(काष्ठा spपढ़ो_spectrum_info));

		अगर (ATOM_EXTERNAL_SS_MASK &
				tbl->asSS_Info[i].ucSpपढ़ोSpectrumType)
			ss_info->type.EXTERNAL = true;

		अगर (ATOM_SS_CENTRE_SPREAD_MODE_MASK &
				tbl->asSS_Info[i].ucSpपढ़ोSpectrumType)
			ss_info->type.CENTER_MODE = true;

		ss_info->type.STEP_AND_DELAY_INFO = true;
		ss_info->spपढ़ो_spectrum_percentage =
			(uपूर्णांक32_t)le16_to_cpu(tbl->asSS_Info[i].usSpपढ़ोSpectrumPercentage);
		ss_info->step_and_delay_info.step = tbl->asSS_Info[i].ucSS_Step;
		ss_info->step_and_delay_info.delay =
			tbl->asSS_Info[i].ucSS_Delay;
		ss_info->step_and_delay_info.recommended_ref_भाग =
			tbl->asSS_Info[i].ucRecommendedRef_Div;
		ss_info->spपढ़ो_spectrum_range =
			(uपूर्णांक32_t)tbl->asSS_Info[i].ucSS_Range * 10000;

		/* there will be only one entry क्रम each display type in SS_info
		 * table */
		result = BP_RESULT_OK;
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण
अटल क्रमागत bp_result get_embedded_panel_info_v1_2(
	काष्ठा bios_parser *bp,
	काष्ठा embedded_panel_info *info);
अटल क्रमागत bp_result get_embedded_panel_info_v1_3(
	काष्ठा bios_parser *bp,
	काष्ठा embedded_panel_info *info);

अटल क्रमागत bp_result bios_parser_get_embedded_panel_info(
	काष्ठा dc_bios *dcb,
	काष्ठा embedded_panel_info *info)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	ATOM_COMMON_TABLE_HEADER *hdr;

	अगर (!DATA_TABLES(LCD_Info))
		वापस BP_RESULT_FAILURE;

	hdr = GET_IMAGE(ATOM_COMMON_TABLE_HEADER, DATA_TABLES(LCD_Info));

	अगर (!hdr)
		वापस BP_RESULT_BADBIOSTABLE;

	चयन (hdr->ucTableFormatRevision) अणु
	हाल 1:
		चयन (hdr->ucTableContentRevision) अणु
		हाल 0:
		हाल 1:
		हाल 2:
			वापस get_embedded_panel_info_v1_2(bp, info);
		हाल 3:
			वापस get_embedded_panel_info_v1_3(bp, info);
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस BP_RESULT_FAILURE;
पूर्ण

अटल क्रमागत bp_result get_embedded_panel_info_v1_2(
	काष्ठा bios_parser *bp,
	काष्ठा embedded_panel_info *info)
अणु
	ATOM_LVDS_INFO_V12 *lvds;

	अगर (!info)
		वापस BP_RESULT_BADINPUT;

	अगर (!DATA_TABLES(LVDS_Info))
		वापस BP_RESULT_UNSUPPORTED;

	lvds =
		GET_IMAGE(ATOM_LVDS_INFO_V12, DATA_TABLES(LVDS_Info));

	अगर (!lvds)
		वापस BP_RESULT_BADBIOSTABLE;

	अगर (1 != lvds->sHeader.ucTableFormatRevision
		|| 2 > lvds->sHeader.ucTableContentRevision)
		वापस BP_RESULT_UNSUPPORTED;

	स_रखो(info, 0, माप(काष्ठा embedded_panel_info));

	/* We need to convert from 10KHz units पूर्णांकo KHz units*/
	info->lcd_timing.pixel_clk =
		le16_to_cpu(lvds->sLCDTiming.usPixClk) * 10;
	/* usHActive करोes not include borders, according to VBIOS team*/
	info->lcd_timing.horizontal_addressable =
		le16_to_cpu(lvds->sLCDTiming.usHActive);
	/* usHBlanking_Time includes borders, so we should really be subtracting
	 * borders duing this translation, but LVDS generally*/
	/* करोesn't have borders, so we should be okay leaving this as is क्रम
	 * now.  May need to revisit अगर we ever have LVDS with borders*/
	info->lcd_timing.horizontal_blanking_समय =
			le16_to_cpu(lvds->sLCDTiming.usHBlanking_Time);
	/* usVActive करोes not include borders, according to VBIOS team*/
	info->lcd_timing.vertical_addressable =
			le16_to_cpu(lvds->sLCDTiming.usVActive);
	/* usVBlanking_Time includes borders, so we should really be subtracting
	 * borders duing this translation, but LVDS generally*/
	/* करोesn't have borders, so we should be okay leaving this as is क्रम
	 * now. May need to revisit अगर we ever have LVDS with borders*/
	info->lcd_timing.vertical_blanking_समय =
		le16_to_cpu(lvds->sLCDTiming.usVBlanking_Time);
	info->lcd_timing.horizontal_sync_offset =
		le16_to_cpu(lvds->sLCDTiming.usHSyncOffset);
	info->lcd_timing.horizontal_sync_width =
		le16_to_cpu(lvds->sLCDTiming.usHSyncWidth);
	info->lcd_timing.vertical_sync_offset =
		le16_to_cpu(lvds->sLCDTiming.usVSyncOffset);
	info->lcd_timing.vertical_sync_width =
		le16_to_cpu(lvds->sLCDTiming.usVSyncWidth);
	info->lcd_timing.horizontal_border = lvds->sLCDTiming.ucHBorder;
	info->lcd_timing.vertical_border = lvds->sLCDTiming.ucVBorder;
	info->lcd_timing.misc_info.HORIZONTAL_CUT_OFF =
		lvds->sLCDTiming.susModeMiscInfo.sbfAccess.HorizontalCutOff;
	info->lcd_timing.misc_info.H_SYNC_POLARITY =
		~(uपूर्णांक32_t)
		lvds->sLCDTiming.susModeMiscInfo.sbfAccess.HSyncPolarity;
	info->lcd_timing.misc_info.V_SYNC_POLARITY =
		~(uपूर्णांक32_t)
		lvds->sLCDTiming.susModeMiscInfo.sbfAccess.VSyncPolarity;
	info->lcd_timing.misc_info.VERTICAL_CUT_OFF =
		lvds->sLCDTiming.susModeMiscInfo.sbfAccess.VerticalCutOff;
	info->lcd_timing.misc_info.H_REPLICATION_BY2 =
		lvds->sLCDTiming.susModeMiscInfo.sbfAccess.H_ReplicationBy2;
	info->lcd_timing.misc_info.V_REPLICATION_BY2 =
		lvds->sLCDTiming.susModeMiscInfo.sbfAccess.V_ReplicationBy2;
	info->lcd_timing.misc_info.COMPOSITE_SYNC =
		lvds->sLCDTiming.susModeMiscInfo.sbfAccess.CompositeSync;
	info->lcd_timing.misc_info.INTERLACE =
		lvds->sLCDTiming.susModeMiscInfo.sbfAccess.Interlace;
	info->lcd_timing.misc_info.DOUBLE_CLOCK =
		lvds->sLCDTiming.susModeMiscInfo.sbfAccess.DoubleClock;
	info->ss_id = lvds->ucSS_Id;

	अणु
		uपूर्णांक8_t rr = le16_to_cpu(lvds->usSupportedRefreshRate);
		/* Get minimum supported refresh rate*/
		अगर (SUPPORTED_LCD_REFRESHRATE_30Hz & rr)
			info->supported_rr.REFRESH_RATE_30HZ = 1;
		अन्यथा अगर (SUPPORTED_LCD_REFRESHRATE_40Hz & rr)
			info->supported_rr.REFRESH_RATE_40HZ = 1;
		अन्यथा अगर (SUPPORTED_LCD_REFRESHRATE_48Hz & rr)
			info->supported_rr.REFRESH_RATE_48HZ = 1;
		अन्यथा अगर (SUPPORTED_LCD_REFRESHRATE_50Hz & rr)
			info->supported_rr.REFRESH_RATE_50HZ = 1;
		अन्यथा अगर (SUPPORTED_LCD_REFRESHRATE_60Hz & rr)
			info->supported_rr.REFRESH_RATE_60HZ = 1;
	पूर्ण

	/*Drr panel support can be reported by VBIOS*/
	अगर (LCDPANEL_CAP_DRR_SUPPORTED
			& lvds->ucLCDPanel_SpecialHandlingCap)
		info->drr_enabled = 1;

	अगर (ATOM_PANEL_MISC_DUAL & lvds->ucLVDS_Misc)
		info->lcd_timing.misc_info.DOUBLE_CLOCK = true;

	अगर (ATOM_PANEL_MISC_888RGB & lvds->ucLVDS_Misc)
		info->lcd_timing.misc_info.RGB888 = true;

	info->lcd_timing.misc_info.GREY_LEVEL =
		(uपूर्णांक32_t) (ATOM_PANEL_MISC_GREY_LEVEL &
			lvds->ucLVDS_Misc) >> ATOM_PANEL_MISC_GREY_LEVEL_SHIFT;

	अगर (ATOM_PANEL_MISC_SPATIAL & lvds->ucLVDS_Misc)
		info->lcd_timing.misc_info.SPATIAL = true;

	अगर (ATOM_PANEL_MISC_TEMPORAL & lvds->ucLVDS_Misc)
		info->lcd_timing.misc_info.TEMPORAL = true;

	अगर (ATOM_PANEL_MISC_API_ENABLED & lvds->ucLVDS_Misc)
		info->lcd_timing.misc_info.API_ENABLED = true;

	वापस BP_RESULT_OK;
पूर्ण

अटल क्रमागत bp_result get_embedded_panel_info_v1_3(
	काष्ठा bios_parser *bp,
	काष्ठा embedded_panel_info *info)
अणु
	ATOM_LCD_INFO_V13 *lvds;

	अगर (!info)
		वापस BP_RESULT_BADINPUT;

	अगर (!DATA_TABLES(LCD_Info))
		वापस BP_RESULT_UNSUPPORTED;

	lvds = GET_IMAGE(ATOM_LCD_INFO_V13, DATA_TABLES(LCD_Info));

	अगर (!lvds)
		वापस BP_RESULT_BADBIOSTABLE;

	अगर (!((1 == lvds->sHeader.ucTableFormatRevision)
			&& (3 <= lvds->sHeader.ucTableContentRevision)))
		वापस BP_RESULT_UNSUPPORTED;

	स_रखो(info, 0, माप(काष्ठा embedded_panel_info));

	/* We need to convert from 10KHz units पूर्णांकo KHz units */
	info->lcd_timing.pixel_clk =
			le16_to_cpu(lvds->sLCDTiming.usPixClk) * 10;
	/* usHActive करोes not include borders, according to VBIOS team */
	info->lcd_timing.horizontal_addressable =
			le16_to_cpu(lvds->sLCDTiming.usHActive);
	/* usHBlanking_Time includes borders, so we should really be subtracting
	 * borders duing this translation, but LVDS generally*/
	/* करोesn't have borders, so we should be okay leaving this as is क्रम
	 * now.  May need to revisit अगर we ever have LVDS with borders*/
	info->lcd_timing.horizontal_blanking_समय =
		le16_to_cpu(lvds->sLCDTiming.usHBlanking_Time);
	/* usVActive करोes not include borders, according to VBIOS team*/
	info->lcd_timing.vertical_addressable =
		le16_to_cpu(lvds->sLCDTiming.usVActive);
	/* usVBlanking_Time includes borders, so we should really be subtracting
	 * borders duing this translation, but LVDS generally*/
	/* करोesn't have borders, so we should be okay leaving this as is क्रम
	 * now. May need to revisit अगर we ever have LVDS with borders*/
	info->lcd_timing.vertical_blanking_समय =
		le16_to_cpu(lvds->sLCDTiming.usVBlanking_Time);
	info->lcd_timing.horizontal_sync_offset =
		le16_to_cpu(lvds->sLCDTiming.usHSyncOffset);
	info->lcd_timing.horizontal_sync_width =
		le16_to_cpu(lvds->sLCDTiming.usHSyncWidth);
	info->lcd_timing.vertical_sync_offset =
		le16_to_cpu(lvds->sLCDTiming.usVSyncOffset);
	info->lcd_timing.vertical_sync_width =
		le16_to_cpu(lvds->sLCDTiming.usVSyncWidth);
	info->lcd_timing.horizontal_border = lvds->sLCDTiming.ucHBorder;
	info->lcd_timing.vertical_border = lvds->sLCDTiming.ucVBorder;
	info->lcd_timing.misc_info.HORIZONTAL_CUT_OFF =
		lvds->sLCDTiming.susModeMiscInfo.sbfAccess.HorizontalCutOff;
	info->lcd_timing.misc_info.H_SYNC_POLARITY =
		~(uपूर्णांक32_t)
		lvds->sLCDTiming.susModeMiscInfo.sbfAccess.HSyncPolarity;
	info->lcd_timing.misc_info.V_SYNC_POLARITY =
		~(uपूर्णांक32_t)
		lvds->sLCDTiming.susModeMiscInfo.sbfAccess.VSyncPolarity;
	info->lcd_timing.misc_info.VERTICAL_CUT_OFF =
		lvds->sLCDTiming.susModeMiscInfo.sbfAccess.VerticalCutOff;
	info->lcd_timing.misc_info.H_REPLICATION_BY2 =
		lvds->sLCDTiming.susModeMiscInfo.sbfAccess.H_ReplicationBy2;
	info->lcd_timing.misc_info.V_REPLICATION_BY2 =
		lvds->sLCDTiming.susModeMiscInfo.sbfAccess.V_ReplicationBy2;
	info->lcd_timing.misc_info.COMPOSITE_SYNC =
		lvds->sLCDTiming.susModeMiscInfo.sbfAccess.CompositeSync;
	info->lcd_timing.misc_info.INTERLACE =
		lvds->sLCDTiming.susModeMiscInfo.sbfAccess.Interlace;
	info->lcd_timing.misc_info.DOUBLE_CLOCK =
		lvds->sLCDTiming.susModeMiscInfo.sbfAccess.DoubleClock;
	info->ss_id = lvds->ucSS_Id;

	/* Drr panel support can be reported by VBIOS*/
	अगर (LCDPANEL_CAP_V13_DRR_SUPPORTED
			& lvds->ucLCDPanel_SpecialHandlingCap)
		info->drr_enabled = 1;

	/* Get supported refresh rate*/
	अगर (info->drr_enabled == 1) अणु
		uपूर्णांक8_t min_rr =
				lvds->sRefreshRateSupport.ucMinRefreshRateForDRR;
		uपूर्णांक8_t rr = lvds->sRefreshRateSupport.ucSupportedRefreshRate;

		अगर (min_rr != 0) अणु
			अगर (SUPPORTED_LCD_REFRESHRATE_30Hz & min_rr)
				info->supported_rr.REFRESH_RATE_30HZ = 1;
			अन्यथा अगर (SUPPORTED_LCD_REFRESHRATE_40Hz & min_rr)
				info->supported_rr.REFRESH_RATE_40HZ = 1;
			अन्यथा अगर (SUPPORTED_LCD_REFRESHRATE_48Hz & min_rr)
				info->supported_rr.REFRESH_RATE_48HZ = 1;
			अन्यथा अगर (SUPPORTED_LCD_REFRESHRATE_50Hz & min_rr)
				info->supported_rr.REFRESH_RATE_50HZ = 1;
			अन्यथा अगर (SUPPORTED_LCD_REFRESHRATE_60Hz & min_rr)
				info->supported_rr.REFRESH_RATE_60HZ = 1;
		पूर्ण अन्यथा अणु
			अगर (SUPPORTED_LCD_REFRESHRATE_30Hz & rr)
				info->supported_rr.REFRESH_RATE_30HZ = 1;
			अन्यथा अगर (SUPPORTED_LCD_REFRESHRATE_40Hz & rr)
				info->supported_rr.REFRESH_RATE_40HZ = 1;
			अन्यथा अगर (SUPPORTED_LCD_REFRESHRATE_48Hz & rr)
				info->supported_rr.REFRESH_RATE_48HZ = 1;
			अन्यथा अगर (SUPPORTED_LCD_REFRESHRATE_50Hz & rr)
				info->supported_rr.REFRESH_RATE_50HZ = 1;
			अन्यथा अगर (SUPPORTED_LCD_REFRESHRATE_60Hz & rr)
				info->supported_rr.REFRESH_RATE_60HZ = 1;
		पूर्ण
	पूर्ण

	अगर (ATOM_PANEL_MISC_V13_DUAL & lvds->ucLCD_Misc)
		info->lcd_timing.misc_info.DOUBLE_CLOCK = true;

	अगर (ATOM_PANEL_MISC_V13_8BIT_PER_COLOR & lvds->ucLCD_Misc)
		info->lcd_timing.misc_info.RGB888 = true;

	info->lcd_timing.misc_info.GREY_LEVEL =
			(uपूर्णांक32_t) (ATOM_PANEL_MISC_V13_GREY_LEVEL &
				lvds->ucLCD_Misc) >> ATOM_PANEL_MISC_V13_GREY_LEVEL_SHIFT;

	वापस BP_RESULT_OK;
पूर्ण

/**
 * bios_parser_get_encoder_cap_info - get encoder capability
 *                                    inक्रमmation of input object id
 *
 * @dcb:       poपूर्णांकer to the DC BIOS
 * @object_id: object id
 * @info:      encoder cap inक्रमmation काष्ठाure
 *
 * वापस: Bios parser result code
 */
अटल क्रमागत bp_result bios_parser_get_encoder_cap_info(
	काष्ठा dc_bios *dcb,
	काष्ठा graphics_object_id object_id,
	काष्ठा bp_encoder_cap_info *info)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	ATOM_OBJECT *object;
	ATOM_ENCODER_CAP_RECORD_V2 *record = शून्य;

	अगर (!info)
		वापस BP_RESULT_BADINPUT;

	object = get_bios_object(bp, object_id);

	अगर (!object)
		वापस BP_RESULT_BADINPUT;

	record = get_encoder_cap_record(bp, object);
	अगर (!record)
		वापस BP_RESULT_NORECORD;

	info->DP_HBR2_EN = record->usHBR2En;
	info->DP_HBR3_EN = record->usHBR3En;
	info->HDMI_6GB_EN = record->usHDMI6GEn;
	वापस BP_RESULT_OK;
पूर्ण

/**
 * get_encoder_cap_record - Get encoder cap record क्रम the object
 *
 * @bp:      poपूर्णांकer to the BIOS parser
 * @object:  ATOM object
 * वापस:   atom encoder cap record
 * note:     search all records to find the ATOM_ENCODER_CAP_RECORD_V2 record
 */
अटल ATOM_ENCODER_CAP_RECORD_V2 *get_encoder_cap_record(
	काष्ठा bios_parser *bp,
	ATOM_OBJECT *object)
अणु
	ATOM_COMMON_RECORD_HEADER *header;
	uपूर्णांक32_t offset;

	अगर (!object) अणु
		BREAK_TO_DEBUGGER(); /* Invalid object */
		वापस शून्य;
	पूर्ण

	offset = le16_to_cpu(object->usRecordOffset)
					+ bp->object_info_tbl_offset;

	क्रम (;;) अणु
		header = GET_IMAGE(ATOM_COMMON_RECORD_HEADER, offset);

		अगर (!header)
			वापस शून्य;

		offset += header->ucRecordSize;

		अगर (LAST_RECORD_TYPE == header->ucRecordType ||
				!header->ucRecordSize)
			अवरोध;

		अगर (ATOM_ENCODER_CAP_RECORD_TYPE != header->ucRecordType)
			जारी;

		अगर (माप(ATOM_ENCODER_CAP_RECORD_V2) <= header->ucRecordSize)
			वापस (ATOM_ENCODER_CAP_RECORD_V2 *)header;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल uपूर्णांक32_t get_ss_entry_number(
	काष्ठा bios_parser *bp,
	uपूर्णांक32_t id);
अटल uपूर्णांक32_t get_ss_entry_number_from_पूर्णांकernal_ss_info_tbl_v2_1(
	काष्ठा bios_parser *bp,
	uपूर्णांक32_t id);
अटल uपूर्णांक32_t get_ss_entry_number_from_पूर्णांकernal_ss_info_tbl_V3_1(
	काष्ठा bios_parser *bp,
	uपूर्णांक32_t id);
अटल uपूर्णांक32_t get_ss_entry_number_from_ss_info_tbl(
	काष्ठा bios_parser *bp,
	uपूर्णांक32_t id);

/**
 * BiosParserObject::GetNumberofSpपढ़ोSpectrumEntry
 * Get Number of Spपढ़ोSpectrum Entry from the ASIC_InternalSS_Info table from
 * the VBIOS that match the SSid (to be converted from संकेत)
 *
 * @dcb:    poपूर्णांकer to the DC BIOS
 * @संकेत: ASSignalType to be converted to SSid
 * वापस: number of SS Entry that match the संकेत
 */
अटल uपूर्णांक32_t bios_parser_get_ss_entry_number(
	काष्ठा dc_bios *dcb,
	क्रमागत as_संकेत_type संकेत)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	uपूर्णांक32_t ss_id = 0;
	ATOM_COMMON_TABLE_HEADER *header;
	काष्ठा atom_data_revision revision;

	ss_id = संकेत_to_ss_id(संकेत);

	अगर (!DATA_TABLES(ASIC_InternalSS_Info))
		वापस get_ss_entry_number_from_ss_info_tbl(bp, ss_id);

	header = GET_IMAGE(ATOM_COMMON_TABLE_HEADER,
			DATA_TABLES(ASIC_InternalSS_Info));
	get_atom_data_table_revision(header, &revision);

	चयन (revision.major) अणु
	हाल 2:
		चयन (revision.minor) अणु
		हाल 1:
			वापस get_ss_entry_number(bp, ss_id);
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 3:
		चयन (revision.minor) अणु
		हाल 1:
			वापस
				get_ss_entry_number_from_पूर्णांकernal_ss_info_tbl_V3_1(
						bp, ss_id);
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * get_ss_entry_number_from_ss_info_tbl
 * Get Number of spपढ़ो spectrum entry from the SS_Info table from the VBIOS.
 *
 * @bp:  poपूर्णांकer to the BIOS parser
 * @id:  spपढ़ो spectrum id
 * वापस: number of SS Entry that match the id
 * note: There can only be one entry क्रम each id क्रम SS_Info Table
 */
अटल uपूर्णांक32_t get_ss_entry_number_from_ss_info_tbl(
	काष्ठा bios_parser *bp,
	uपूर्णांक32_t id)
अणु
	ATOM_SPREAD_SPECTRUM_INFO *tbl;
	ATOM_COMMON_TABLE_HEADER *header;
	uपूर्णांक32_t table_size;
	uपूर्णांक32_t i;
	uपूर्णांक32_t number = 0;
	uपूर्णांक32_t id_local = SS_ID_UNKNOWN;
	काष्ठा atom_data_revision revision;

	/* SS_Info table exist */
	अगर (!DATA_TABLES(SS_Info))
		वापस number;

	header = GET_IMAGE(ATOM_COMMON_TABLE_HEADER,
			DATA_TABLES(SS_Info));
	get_atom_data_table_revision(header, &revision);

	tbl = GET_IMAGE(ATOM_SPREAD_SPECTRUM_INFO,
			DATA_TABLES(SS_Info));

	अगर (1 != revision.major || 2 > revision.minor)
		वापस number;

	/* have to convert from Internal_SS क्रमmat to SS_Info क्रमmat */
	चयन (id) अणु
	हाल ASIC_INTERNAL_SS_ON_DP:
		id_local = SS_ID_DP1;
		अवरोध;
	हाल ASIC_INTERNAL_SS_ON_LVDS: अणु
		काष्ठा embedded_panel_info panel_info;

		अगर (bios_parser_get_embedded_panel_info(&bp->base, &panel_info)
				== BP_RESULT_OK)
			id_local = panel_info.ss_id;
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	अगर (id_local == SS_ID_UNKNOWN)
		वापस number;

	table_size = (le16_to_cpu(tbl->sHeader.usStructureSize) -
			माप(ATOM_COMMON_TABLE_HEADER)) /
					माप(ATOM_SPREAD_SPECTRUM_ASSIGNMENT);

	क्रम (i = 0; i < table_size; i++)
		अगर (id_local == (uपूर्णांक32_t)tbl->asSS_Info[i].ucSS_Id) अणु
			number = 1;
			अवरोध;
		पूर्ण

	वापस number;
पूर्ण

/**
 * get_ss_entry_number
 * Get spपढ़ो sprectrum inक्रमmation from the ASIC_InternalSS_Info Ver 2.1 or
 * SS_Info table from the VBIOS
 * There can not be more than 1 entry क्रम  ASIC_InternalSS_Info Ver 2.1 or
 * SS_Info.
 *
 * @bp:    poपूर्णांकer to the BIOS parser
 * @id:    spपढ़ो sprectrum info index
 * वापस: Bios parser result code
 */
अटल uपूर्णांक32_t get_ss_entry_number(काष्ठा bios_parser *bp, uपूर्णांक32_t id)
अणु
	अगर (id == ASIC_INTERNAL_SS_ON_DP || id == ASIC_INTERNAL_SS_ON_LVDS)
		वापस get_ss_entry_number_from_ss_info_tbl(bp, id);

	वापस get_ss_entry_number_from_पूर्णांकernal_ss_info_tbl_v2_1(bp, id);
पूर्ण

/**
 * get_ss_entry_number_from_पूर्णांकernal_ss_info_tbl_v2_1
 * Get NUmber of spपढ़ो sprectrum entry from the ASIC_InternalSS_Info table
 * Ver 2.1 from the VBIOS
 * There will not be multiple entry क्रम Ver 2.1
 *
 * @bp:    poपूर्णांकer to the BIOS parser
 * @id:    spपढ़ो sprectrum info index
 * वापस: number of SS Entry that match the id
 */
अटल uपूर्णांक32_t get_ss_entry_number_from_पूर्णांकernal_ss_info_tbl_v2_1(
	काष्ठा bios_parser *bp,
	uपूर्णांक32_t id)
अणु
	ATOM_ASIC_INTERNAL_SS_INFO_V2 *header_include;
	ATOM_ASIC_SS_ASSIGNMENT_V2 *tbl;
	uपूर्णांक32_t size;
	uपूर्णांक32_t i;

	अगर (!DATA_TABLES(ASIC_InternalSS_Info))
		वापस 0;

	header_include = GET_IMAGE(ATOM_ASIC_INTERNAL_SS_INFO_V2,
			DATA_TABLES(ASIC_InternalSS_Info));

	size = (le16_to_cpu(header_include->sHeader.usStructureSize)
			- माप(ATOM_COMMON_TABLE_HEADER))
						/ माप(ATOM_ASIC_SS_ASSIGNMENT_V2);

	tbl = (ATOM_ASIC_SS_ASSIGNMENT_V2 *)
				&header_include->asSpपढ़ोSpectrum[0];
	क्रम (i = 0; i < size; i++)
		अगर (tbl[i].ucClockIndication == (uपूर्णांक8_t)id)
			वापस 1;

	वापस 0;
पूर्ण
/**
 * get_ss_entry_number_from_पूर्णांकernal_ss_info_table_V3_1
 * Get Number of Spपढ़ोSpectrum Entry from the ASIC_InternalSS_Info table of
 * the VBIOS that matches id
 *
 * @bp:    poपूर्णांकer to the BIOS parser
 * @id:    spपढ़ो sprectrum id
 * वापस: number of SS Entry that match the id
 */
अटल uपूर्णांक32_t get_ss_entry_number_from_पूर्णांकernal_ss_info_tbl_V3_1(
	काष्ठा bios_parser *bp,
	uपूर्णांक32_t id)
अणु
	uपूर्णांक32_t number = 0;
	ATOM_ASIC_INTERNAL_SS_INFO_V3 *header_include;
	ATOM_ASIC_SS_ASSIGNMENT_V3 *tbl;
	uपूर्णांक32_t size;
	uपूर्णांक32_t i;

	अगर (!DATA_TABLES(ASIC_InternalSS_Info))
		वापस number;

	header_include = GET_IMAGE(ATOM_ASIC_INTERNAL_SS_INFO_V3,
			DATA_TABLES(ASIC_InternalSS_Info));
	size = (le16_to_cpu(header_include->sHeader.usStructureSize) -
			माप(ATOM_COMMON_TABLE_HEADER)) /
					माप(ATOM_ASIC_SS_ASSIGNMENT_V3);

	tbl = (ATOM_ASIC_SS_ASSIGNMENT_V3 *)
				&header_include->asSpपढ़ोSpectrum[0];

	क्रम (i = 0; i < size; i++)
		अगर (tbl[i].ucClockIndication == (uपूर्णांक8_t)id)
			number++;

	वापस number;
पूर्ण

/**
 * bios_parser_get_gpio_pin_info
 * Get GpioPin inक्रमmation of input gpio id
 *
 * @dcb:     poपूर्णांकer to the DC BIOS
 * @gpio_id: GPIO ID
 * @info:    GpioPin inक्रमmation काष्ठाure
 * वापस:   Bios parser result code
 * note:
 *  to get the GPIO PIN INFO, we need:
 *  1. get the GPIO_ID from other object table, see GetHPDInfo()
 *  2. in DATA_TABLE.GPIO_Pin_LUT, search all records, to get the रेजिस्टरA
 *  offset/mask
 */
अटल क्रमागत bp_result bios_parser_get_gpio_pin_info(
	काष्ठा dc_bios *dcb,
	uपूर्णांक32_t gpio_id,
	काष्ठा gpio_pin_info *info)
अणु
	काष्ठा bios_parser *bp = BP_FROM_DCB(dcb);
	ATOM_GPIO_PIN_LUT *header;
	uपूर्णांक32_t count = 0;
	uपूर्णांक32_t i = 0;

	अगर (!DATA_TABLES(GPIO_Pin_LUT))
		वापस BP_RESULT_BADBIOSTABLE;

	header = GET_IMAGE(ATOM_GPIO_PIN_LUT, DATA_TABLES(GPIO_Pin_LUT));
	अगर (!header)
		वापस BP_RESULT_BADBIOSTABLE;

	अगर (माप(ATOM_COMMON_TABLE_HEADER) + माप(ATOM_GPIO_PIN_LUT)
			> le16_to_cpu(header->sHeader.usStructureSize))
		वापस BP_RESULT_BADBIOSTABLE;

	अगर (1 != header->sHeader.ucTableContentRevision)
		वापस BP_RESULT_UNSUPPORTED;

	count = (le16_to_cpu(header->sHeader.usStructureSize)
			- माप(ATOM_COMMON_TABLE_HEADER))
				/ माप(ATOM_GPIO_PIN_ASSIGNMENT);
	क्रम (i = 0; i < count; ++i) अणु
		अगर (header->asGPIO_Pin[i].ucGPIO_ID != gpio_id)
			जारी;

		info->offset =
			(uपूर्णांक32_t) le16_to_cpu(header->asGPIO_Pin[i].usGpioPin_AIndex);
		info->offset_y = info->offset + 2;
		info->offset_en = info->offset + 1;
		info->offset_mask = info->offset - 1;

		info->mask = (uपूर्णांक32_t) (1 <<
			header->asGPIO_Pin[i].ucGpioPinBitShअगरt);
		info->mask_y = info->mask + 2;
		info->mask_en = info->mask + 1;
		info->mask_mask = info->mask - 1;

		वापस BP_RESULT_OK;
	पूर्ण

	वापस BP_RESULT_NORECORD;
पूर्ण

अटल क्रमागत bp_result get_gpio_i2c_info(काष्ठा bios_parser *bp,
	ATOM_I2C_RECORD *record,
	काष्ठा graphics_object_i2c_info *info)
अणु
	ATOM_GPIO_I2C_INFO *header;
	uपूर्णांक32_t count = 0;

	अगर (!info)
		वापस BP_RESULT_BADINPUT;

	/* get the GPIO_I2C info */
	अगर (!DATA_TABLES(GPIO_I2C_Info))
		वापस BP_RESULT_BADBIOSTABLE;

	header = GET_IMAGE(ATOM_GPIO_I2C_INFO, DATA_TABLES(GPIO_I2C_Info));
	अगर (!header)
		वापस BP_RESULT_BADBIOSTABLE;

	अगर (माप(ATOM_COMMON_TABLE_HEADER) + माप(ATOM_GPIO_I2C_ASSIGMENT)
			> le16_to_cpu(header->sHeader.usStructureSize))
		वापस BP_RESULT_BADBIOSTABLE;

	अगर (1 != header->sHeader.ucTableContentRevision)
		वापस BP_RESULT_UNSUPPORTED;

	/* get data count */
	count = (le16_to_cpu(header->sHeader.usStructureSize)
			- माप(ATOM_COMMON_TABLE_HEADER))
				/ माप(ATOM_GPIO_I2C_ASSIGMENT);
	अगर (count < record->sucI2cId.bfI2C_LineMux)
		वापस BP_RESULT_BADBIOSTABLE;

	/* get the GPIO_I2C_INFO */
	info->i2c_hw_assist = record->sucI2cId.bfHW_Capable;
	info->i2c_line = record->sucI2cId.bfI2C_LineMux;
	info->i2c_engine_id = record->sucI2cId.bfHW_EngineID;
	info->i2c_slave_address = record->ucI2CAddr;

	info->gpio_info.clk_mask_रेजिस्टर_index =
			le16_to_cpu(header->asGPIO_Info[info->i2c_line].usClkMaskRegisterIndex);
	info->gpio_info.clk_en_रेजिस्टर_index =
			le16_to_cpu(header->asGPIO_Info[info->i2c_line].usClkEnRegisterIndex);
	info->gpio_info.clk_y_रेजिस्टर_index =
			le16_to_cpu(header->asGPIO_Info[info->i2c_line].usClkY_RegisterIndex);
	info->gpio_info.clk_a_रेजिस्टर_index =
			le16_to_cpu(header->asGPIO_Info[info->i2c_line].usClkA_RegisterIndex);
	info->gpio_info.data_mask_रेजिस्टर_index =
			le16_to_cpu(header->asGPIO_Info[info->i2c_line].usDataMaskRegisterIndex);
	info->gpio_info.data_en_रेजिस्टर_index =
			le16_to_cpu(header->asGPIO_Info[info->i2c_line].usDataEnRegisterIndex);
	info->gpio_info.data_y_रेजिस्टर_index =
			le16_to_cpu(header->asGPIO_Info[info->i2c_line].usDataY_RegisterIndex);
	info->gpio_info.data_a_रेजिस्टर_index =
			le16_to_cpu(header->asGPIO_Info[info->i2c_line].usDataA_RegisterIndex);

	info->gpio_info.clk_mask_shअगरt =
			header->asGPIO_Info[info->i2c_line].ucClkMaskShअगरt;
	info->gpio_info.clk_en_shअगरt =
			header->asGPIO_Info[info->i2c_line].ucClkEnShअगरt;
	info->gpio_info.clk_y_shअगरt =
			header->asGPIO_Info[info->i2c_line].ucClkY_Shअगरt;
	info->gpio_info.clk_a_shअगरt =
			header->asGPIO_Info[info->i2c_line].ucClkA_Shअगरt;
	info->gpio_info.data_mask_shअगरt =
			header->asGPIO_Info[info->i2c_line].ucDataMaskShअगरt;
	info->gpio_info.data_en_shअगरt =
			header->asGPIO_Info[info->i2c_line].ucDataEnShअगरt;
	info->gpio_info.data_y_shअगरt =
			header->asGPIO_Info[info->i2c_line].ucDataY_Shअगरt;
	info->gpio_info.data_a_shअगरt =
			header->asGPIO_Info[info->i2c_line].ucDataA_Shअगरt;

	वापस BP_RESULT_OK;
पूर्ण

अटल bool dal_graphics_object_id_is_valid(काष्ठा graphics_object_id id)
अणु
	bool rc = true;

	चयन (id.type) अणु
	हाल OBJECT_TYPE_UNKNOWN:
		rc = false;
		अवरोध;
	हाल OBJECT_TYPE_GPU:
	हाल OBJECT_TYPE_ENGINE:
		/* करो NOT check क्रम id.id == 0 */
		अगर (id.क्रमागत_id == ENUM_ID_UNKNOWN)
			rc = false;
		अवरोध;
	शेष:
		अगर (id.id == 0 || id.क्रमागत_id == ENUM_ID_UNKNOWN)
			rc = false;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल bool dal_graphics_object_id_is_equal(
	काष्ठा graphics_object_id id1,
	काष्ठा graphics_object_id id2)
अणु
	अगर (false == dal_graphics_object_id_is_valid(id1)) अणु
		dm_output_to_console(
		"%s: Warning: comparing invalid object 'id1'!\n", __func__);
		वापस false;
	पूर्ण

	अगर (false == dal_graphics_object_id_is_valid(id2)) अणु
		dm_output_to_console(
		"%s: Warning: comparing invalid object 'id2'!\n", __func__);
		वापस false;
	पूर्ण

	अगर (id1.id == id2.id && id1.क्रमागत_id == id2.क्रमागत_id
		&& id1.type == id2.type)
		वापस true;

	वापस false;
पूर्ण

अटल ATOM_OBJECT *get_bios_object(काष्ठा bios_parser *bp,
	काष्ठा graphics_object_id id)
अणु
	uपूर्णांक32_t offset;
	ATOM_OBJECT_TABLE *tbl;
	uपूर्णांक32_t i;

	चयन (id.type) अणु
	हाल OBJECT_TYPE_ENCODER:
		offset = le16_to_cpu(bp->object_info_tbl.v1_1->usEncoderObjectTableOffset);
		अवरोध;

	हाल OBJECT_TYPE_CONNECTOR:
		offset = le16_to_cpu(bp->object_info_tbl.v1_1->usConnectorObjectTableOffset);
		अवरोध;

	हाल OBJECT_TYPE_ROUTER:
		offset = le16_to_cpu(bp->object_info_tbl.v1_1->usRouterObjectTableOffset);
		अवरोध;

	हाल OBJECT_TYPE_GENERIC:
		अगर (bp->object_info_tbl.revision.minor < 3)
			वापस शून्य;
		offset = le16_to_cpu(bp->object_info_tbl.v1_3->usMiscObjectTableOffset);
		अवरोध;

	शेष:
		वापस शून्य;
	पूर्ण

	offset += bp->object_info_tbl_offset;

	tbl = GET_IMAGE(ATOM_OBJECT_TABLE, offset);
	अगर (!tbl)
		वापस शून्य;

	क्रम (i = 0; i < tbl->ucNumberOfObjects; i++)
		अगर (dal_graphics_object_id_is_equal(id,
				object_id_from_bios_object_id(
						le16_to_cpu(tbl->asObjects[i].usObjectID))))
			वापस &tbl->asObjects[i];

	वापस शून्य;
पूर्ण

अटल uपूर्णांक32_t get_src_obj_list(काष्ठा bios_parser *bp, ATOM_OBJECT *object,
	uपूर्णांक16_t **id_list)
अणु
	uपूर्णांक32_t offset;
	uपूर्णांक8_t *number;

	अगर (!object) अणु
		BREAK_TO_DEBUGGER(); /* Invalid object id */
		वापस 0;
	पूर्ण

	offset = le16_to_cpu(object->usSrcDstTableOffset)
					+ bp->object_info_tbl_offset;

	number = GET_IMAGE(uपूर्णांक8_t, offset);
	अगर (!number)
		वापस 0;

	offset += माप(uपूर्णांक8_t);
	*id_list = (uपूर्णांक16_t *)bios_get_image(&bp->base, offset, *number * माप(uपूर्णांक16_t));

	अगर (!*id_list)
		वापस 0;

	वापस *number;
पूर्ण

अटल काष्ठा device_id device_type_from_device_id(uपूर्णांक16_t device_id)
अणु

	काष्ठा device_id result_device_id = अणु0पूर्ण;

	चयन (device_id) अणु
	हाल ATOM_DEVICE_LCD1_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_LCD;
		result_device_id.क्रमागत_id = 1;
		अवरोध;

	हाल ATOM_DEVICE_LCD2_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_LCD;
		result_device_id.क्रमागत_id = 2;
		अवरोध;

	हाल ATOM_DEVICE_CRT1_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_CRT;
		result_device_id.क्रमागत_id = 1;
		अवरोध;

	हाल ATOM_DEVICE_CRT2_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_CRT;
		result_device_id.क्रमागत_id = 2;
		अवरोध;

	हाल ATOM_DEVICE_DFP1_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_DFP;
		result_device_id.क्रमागत_id = 1;
		अवरोध;

	हाल ATOM_DEVICE_DFP2_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_DFP;
		result_device_id.क्रमागत_id = 2;
		अवरोध;

	हाल ATOM_DEVICE_DFP3_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_DFP;
		result_device_id.क्रमागत_id = 3;
		अवरोध;

	हाल ATOM_DEVICE_DFP4_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_DFP;
		result_device_id.क्रमागत_id = 4;
		अवरोध;

	हाल ATOM_DEVICE_DFP5_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_DFP;
		result_device_id.क्रमागत_id = 5;
		अवरोध;

	हाल ATOM_DEVICE_DFP6_SUPPORT:
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

अटल व्योम get_atom_data_table_revision(
	ATOM_COMMON_TABLE_HEADER *atom_data_tbl,
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
			(uपूर्णांक32_t) GET_DATA_TABLE_MAJOR_REVISION(atom_data_tbl);
	tbl_revision->minor =
			(uपूर्णांक32_t) GET_DATA_TABLE_MINOR_REVISION(atom_data_tbl);
पूर्ण

अटल uपूर्णांक32_t संकेत_to_ss_id(क्रमागत as_संकेत_type संकेत)
अणु
	uपूर्णांक32_t clk_id_ss = 0;

	चयन (संकेत) अणु
	हाल AS_SIGNAL_TYPE_DVI:
		clk_id_ss = ASIC_INTERNAL_SS_ON_TMDS;
		अवरोध;
	हाल AS_SIGNAL_TYPE_HDMI:
		clk_id_ss = ASIC_INTERNAL_SS_ON_HDMI;
		अवरोध;
	हाल AS_SIGNAL_TYPE_LVDS:
		clk_id_ss = ASIC_INTERNAL_SS_ON_LVDS;
		अवरोध;
	हाल AS_SIGNAL_TYPE_DISPLAY_PORT:
		clk_id_ss = ASIC_INTERNAL_SS_ON_DP;
		अवरोध;
	हाल AS_SIGNAL_TYPE_GPU_PLL:
		clk_id_ss = ASIC_INTERNAL_GPUPLL_SS;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस clk_id_ss;
पूर्ण

अटल uपूर्णांक32_t get_support_mask_क्रम_device_id(काष्ठा device_id device_id)
अणु
	क्रमागत dal_device_type device_type = device_id.device_type;
	uपूर्णांक32_t क्रमागत_id = device_id.क्रमागत_id;

	चयन (device_type) अणु
	हाल DEVICE_TYPE_LCD:
		चयन (क्रमागत_id) अणु
		हाल 1:
			वापस ATOM_DEVICE_LCD1_SUPPORT;
		हाल 2:
			वापस ATOM_DEVICE_LCD2_SUPPORT;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल DEVICE_TYPE_CRT:
		चयन (क्रमागत_id) अणु
		हाल 1:
			वापस ATOM_DEVICE_CRT1_SUPPORT;
		हाल 2:
			वापस ATOM_DEVICE_CRT2_SUPPORT;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल DEVICE_TYPE_DFP:
		चयन (क्रमागत_id) अणु
		हाल 1:
			वापस ATOM_DEVICE_DFP1_SUPPORT;
		हाल 2:
			वापस ATOM_DEVICE_DFP2_SUPPORT;
		हाल 3:
			वापस ATOM_DEVICE_DFP3_SUPPORT;
		हाल 4:
			वापस ATOM_DEVICE_DFP4_SUPPORT;
		हाल 5:
			वापस ATOM_DEVICE_DFP5_SUPPORT;
		हाल 6:
			वापस ATOM_DEVICE_DFP6_SUPPORT;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल DEVICE_TYPE_CV:
		चयन (क्रमागत_id) अणु
		हाल 1:
			वापस ATOM_DEVICE_CV_SUPPORT;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल DEVICE_TYPE_TV:
		चयन (क्रमागत_id) अणु
		हाल 1:
			वापस ATOM_DEVICE_TV1_SUPPORT;
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

/**
 * bios_parser_set_scratch_critical_state - update critical state
 *                                          bit in VBIOS scratch रेजिस्टर
 * @dcb:    poपूर्णांकer to the DC BIOS
 * @state:  set or reset state
 */
अटल व्योम bios_parser_set_scratch_critical_state(
	काष्ठा dc_bios *dcb,
	bool state)
अणु
	bios_set_scratch_critical_state(dcb, state);
पूर्ण

/*
 * get_पूर्णांकegrated_info_v8
 *
 * @brief
 * Get V8 पूर्णांकegrated BIOS inक्रमmation
 *
 * @param
 * bios_parser *bp - [in]BIOS parser handler to get master data table
 * पूर्णांकegrated_info *info - [out] store and output पूर्णांकegrated info
 *
 * वापस:
 * क्रमागत bp_result - BP_RESULT_OK अगर inक्रमmation is available,
 *                  BP_RESULT_BADBIOSTABLE otherwise.
 */
अटल क्रमागत bp_result get_पूर्णांकegrated_info_v8(
	काष्ठा bios_parser *bp,
	काष्ठा पूर्णांकegrated_info *info)
अणु
	ATOM_INTEGRATED_SYSTEM_INFO_V1_8 *info_v8;
	uपूर्णांक32_t i;

	info_v8 = GET_IMAGE(ATOM_INTEGRATED_SYSTEM_INFO_V1_8,
			bp->master_data_tbl->ListOfDataTables.IntegratedSystemInfo);

	अगर (info_v8 == शून्य)
		वापस BP_RESULT_BADBIOSTABLE;
	info->boot_up_engine_घड़ी = le32_to_cpu(info_v8->ulBootUpEngineClock) * 10;
	info->dentist_vco_freq = le32_to_cpu(info_v8->ulDentistVCOFreq) * 10;
	info->boot_up_uma_घड़ी = le32_to_cpu(info_v8->ulBootUpUMAClock) * 10;

	क्रम (i = 0; i < NUMBER_OF_DISP_CLK_VOLTAGE; ++i) अणु
		/* Convert [10KHz] पूर्णांकo [KHz] */
		info->disp_clk_voltage[i].max_supported_clk =
			le32_to_cpu(info_v8->sDISPCLK_Voltage[i].
				    ulMaximumSupportedCLK) * 10;
		info->disp_clk_voltage[i].voltage_index =
			le32_to_cpu(info_v8->sDISPCLK_Voltage[i].ulVoltageIndex);
	पूर्ण

	info->boot_up_req_display_vector =
		le32_to_cpu(info_v8->ulBootUpReqDisplayVector);
	info->gpu_cap_info =
		le32_to_cpu(info_v8->ulGPUCapInfo);

	/*
	 * प्रणाली_config: Bit[0] = 0 : PCIE घातer gating disabled
	 *                       = 1 : PCIE घातer gating enabled
	 *                Bit[1] = 0 : DDR-PLL shut करोwn disabled
	 *                       = 1 : DDR-PLL shut करोwn enabled
	 *                Bit[2] = 0 : DDR-PLL घातer करोwn disabled
	 *                       = 1 : DDR-PLL घातer करोwn enabled
	 */
	info->प्रणाली_config = le32_to_cpu(info_v8->ulSystemConfig);
	info->cpu_cap_info = le32_to_cpu(info_v8->ulCPUCapInfo);
	info->boot_up_nb_voltage =
		le16_to_cpu(info_v8->usBootUpNBVoltage);
	info->ext_disp_conn_info_offset =
		le16_to_cpu(info_v8->usExtDispConnInfoOffset);
	info->memory_type = info_v8->ucMemoryType;
	info->ma_channel_number = info_v8->ucUMAChannelNumber;
	info->gmc_restore_reset_समय =
		le32_to_cpu(info_v8->ulGMCRestoreResetTime);

	info->minimum_n_clk =
		le32_to_cpu(info_v8->ulNbpStateNClkFreq[0]);
	क्रम (i = 1; i < 4; ++i)
		info->minimum_n_clk =
			info->minimum_n_clk < le32_to_cpu(info_v8->ulNbpStateNClkFreq[i]) ?
			info->minimum_n_clk : le32_to_cpu(info_v8->ulNbpStateNClkFreq[i]);

	info->idle_n_clk = le32_to_cpu(info_v8->ulIdleNClk);
	info->ddr_dll_घातer_up_समय =
		le32_to_cpu(info_v8->ulDDR_DLL_PowerUpTime);
	info->ddr_pll_घातer_up_समय =
		le32_to_cpu(info_v8->ulDDR_PLL_PowerUpTime);
	info->pcie_clk_ss_type = le16_to_cpu(info_v8->usPCIEClkSSType);
	info->lvds_ss_percentage =
		le16_to_cpu(info_v8->usLvdsSSPercentage);
	info->lvds_sspपढ़ो_rate_in_10hz =
		le16_to_cpu(info_v8->usLvdsSSpपढ़ोRateIn10Hz);
	info->hdmi_ss_percentage =
		le16_to_cpu(info_v8->usHDMISSPercentage);
	info->hdmi_sspपढ़ो_rate_in_10hz =
		le16_to_cpu(info_v8->usHDMISSpपढ़ोRateIn10Hz);
	info->dvi_ss_percentage =
		le16_to_cpu(info_v8->usDVISSPercentage);
	info->dvi_sspपढ़ो_rate_in_10_hz =
		le16_to_cpu(info_v8->usDVISSpपढ़ोRateIn10Hz);

	info->max_lvds_pclk_freq_in_single_link =
		le16_to_cpu(info_v8->usMaxLVDSPclkFreqInSingleLink);
	info->lvds_misc = info_v8->ucLvdsMisc;
	info->lvds_pwr_on_seq_dig_on_to_de_in_4ms =
		info_v8->ucLVDSPwrOnSeqDIGONtoDE_in4Ms;
	info->lvds_pwr_on_seq_de_to_vary_bl_in_4ms =
		info_v8->ucLVDSPwrOnSeqDEtoVARY_BL_in4Ms;
	info->lvds_pwr_on_seq_vary_bl_to_blon_in_4ms =
		info_v8->ucLVDSPwrOnSeqVARY_BLtoBLON_in4Ms;
	info->lvds_pwr_off_seq_vary_bl_to_de_in4ms =
		info_v8->ucLVDSPwrOffSeqVARY_BLtoDE_in4Ms;
	info->lvds_pwr_off_seq_de_to_dig_on_in4ms =
		info_v8->ucLVDSPwrOffSeqDEtoDIGON_in4Ms;
	info->lvds_pwr_off_seq_blon_to_vary_bl_in_4ms =
		info_v8->ucLVDSPwrOffSeqBLONtoVARY_BL_in4Ms;
	info->lvds_off_to_on_delay_in_4ms =
		info_v8->ucLVDSOffToOnDelay_in4Ms;
	info->lvds_bit_depth_control_val =
		le32_to_cpu(info_v8->ulLCDBitDepthControlVal);

	क्रम (i = 0; i < NUMBER_OF_AVAILABLE_SCLK; ++i) अणु
		/* Convert [10KHz] पूर्णांकo [KHz] */
		info->avail_s_clk[i].supported_s_clk =
			le32_to_cpu(info_v8->sAvail_SCLK[i].ulSupportedSCLK) * 10;
		info->avail_s_clk[i].voltage_index =
			le16_to_cpu(info_v8->sAvail_SCLK[i].usVoltageIndex);
		info->avail_s_clk[i].voltage_id =
			le16_to_cpu(info_v8->sAvail_SCLK[i].usVoltageID);
	पूर्ण

	क्रम (i = 0; i < NUMBER_OF_UCHAR_FOR_GUID; ++i) अणु
		info->ext_disp_conn_info.gu_id[i] =
			info_v8->sExtDispConnInfo.ucGuid[i];
	पूर्ण

	क्रम (i = 0; i < MAX_NUMBER_OF_EXT_DISPLAY_PATH; ++i) अणु
		info->ext_disp_conn_info.path[i].device_connector_id =
			object_id_from_bios_object_id(
				le16_to_cpu(info_v8->sExtDispConnInfo.sPath[i].usDeviceConnector));

		info->ext_disp_conn_info.path[i].ext_encoder_obj_id =
			object_id_from_bios_object_id(
				le16_to_cpu(info_v8->sExtDispConnInfo.sPath[i].usExtEncoderObjId));

		info->ext_disp_conn_info.path[i].device_tag =
			le16_to_cpu(info_v8->sExtDispConnInfo.sPath[i].usDeviceTag);
		info->ext_disp_conn_info.path[i].device_acpi_क्रमागत =
			le16_to_cpu(info_v8->sExtDispConnInfo.sPath[i].usDeviceACPIEnum);
		info->ext_disp_conn_info.path[i].ext_aux_ddc_lut_index =
			info_v8->sExtDispConnInfo.sPath[i].ucExtAUXDDCLutIndex;
		info->ext_disp_conn_info.path[i].ext_hpd_pin_lut_index =
			info_v8->sExtDispConnInfo.sPath[i].ucExtHPDPINLutIndex;
		info->ext_disp_conn_info.path[i].channel_mapping.raw =
			info_v8->sExtDispConnInfo.sPath[i].ucChannelMapping;
	पूर्ण
	info->ext_disp_conn_info.checksum =
		info_v8->sExtDispConnInfo.ucChecksum;

	वापस BP_RESULT_OK;
पूर्ण

/*
 * get_पूर्णांकegrated_info_v8
 *
 * @brief
 * Get V8 पूर्णांकegrated BIOS inक्रमmation
 *
 * @param
 * bios_parser *bp - [in]BIOS parser handler to get master data table
 * पूर्णांकegrated_info *info - [out] store and output पूर्णांकegrated info
 *
 * वापस:
 * क्रमागत bp_result - BP_RESULT_OK अगर inक्रमmation is available,
 *                  BP_RESULT_BADBIOSTABLE otherwise.
 */
अटल क्रमागत bp_result get_पूर्णांकegrated_info_v9(
	काष्ठा bios_parser *bp,
	काष्ठा पूर्णांकegrated_info *info)
अणु
	ATOM_INTEGRATED_SYSTEM_INFO_V1_9 *info_v9;
	uपूर्णांक32_t i;

	info_v9 = GET_IMAGE(ATOM_INTEGRATED_SYSTEM_INFO_V1_9,
			bp->master_data_tbl->ListOfDataTables.IntegratedSystemInfo);

	अगर (!info_v9)
		वापस BP_RESULT_BADBIOSTABLE;

	info->boot_up_engine_घड़ी = le32_to_cpu(info_v9->ulBootUpEngineClock) * 10;
	info->dentist_vco_freq = le32_to_cpu(info_v9->ulDentistVCOFreq) * 10;
	info->boot_up_uma_घड़ी = le32_to_cpu(info_v9->ulBootUpUMAClock) * 10;

	क्रम (i = 0; i < NUMBER_OF_DISP_CLK_VOLTAGE; ++i) अणु
		/* Convert [10KHz] पूर्णांकo [KHz] */
		info->disp_clk_voltage[i].max_supported_clk =
			le32_to_cpu(info_v9->sDISPCLK_Voltage[i].ulMaximumSupportedCLK) * 10;
		info->disp_clk_voltage[i].voltage_index =
			le32_to_cpu(info_v9->sDISPCLK_Voltage[i].ulVoltageIndex);
	पूर्ण

	info->boot_up_req_display_vector =
		le32_to_cpu(info_v9->ulBootUpReqDisplayVector);
	info->gpu_cap_info = le32_to_cpu(info_v9->ulGPUCapInfo);

	/*
	 * प्रणाली_config: Bit[0] = 0 : PCIE घातer gating disabled
	 *                       = 1 : PCIE घातer gating enabled
	 *                Bit[1] = 0 : DDR-PLL shut करोwn disabled
	 *                       = 1 : DDR-PLL shut करोwn enabled
	 *                Bit[2] = 0 : DDR-PLL घातer करोwn disabled
	 *                       = 1 : DDR-PLL घातer करोwn enabled
	 */
	info->प्रणाली_config = le32_to_cpu(info_v9->ulSystemConfig);
	info->cpu_cap_info = le32_to_cpu(info_v9->ulCPUCapInfo);
	info->boot_up_nb_voltage = le16_to_cpu(info_v9->usBootUpNBVoltage);
	info->ext_disp_conn_info_offset = le16_to_cpu(info_v9->usExtDispConnInfoOffset);
	info->memory_type = info_v9->ucMemoryType;
	info->ma_channel_number = info_v9->ucUMAChannelNumber;
	info->gmc_restore_reset_समय = le32_to_cpu(info_v9->ulGMCRestoreResetTime);

	info->minimum_n_clk = le32_to_cpu(info_v9->ulNbpStateNClkFreq[0]);
	क्रम (i = 1; i < 4; ++i)
		info->minimum_n_clk =
			info->minimum_n_clk < le32_to_cpu(info_v9->ulNbpStateNClkFreq[i]) ?
			info->minimum_n_clk : le32_to_cpu(info_v9->ulNbpStateNClkFreq[i]);

	info->idle_n_clk = le32_to_cpu(info_v9->ulIdleNClk);
	info->ddr_dll_घातer_up_समय = le32_to_cpu(info_v9->ulDDR_DLL_PowerUpTime);
	info->ddr_pll_घातer_up_समय = le32_to_cpu(info_v9->ulDDR_PLL_PowerUpTime);
	info->pcie_clk_ss_type = le16_to_cpu(info_v9->usPCIEClkSSType);
	info->lvds_ss_percentage = le16_to_cpu(info_v9->usLvdsSSPercentage);
	info->lvds_sspपढ़ो_rate_in_10hz = le16_to_cpu(info_v9->usLvdsSSpपढ़ोRateIn10Hz);
	info->hdmi_ss_percentage = le16_to_cpu(info_v9->usHDMISSPercentage);
	info->hdmi_sspपढ़ो_rate_in_10hz = le16_to_cpu(info_v9->usHDMISSpपढ़ोRateIn10Hz);
	info->dvi_ss_percentage = le16_to_cpu(info_v9->usDVISSPercentage);
	info->dvi_sspपढ़ो_rate_in_10_hz = le16_to_cpu(info_v9->usDVISSpपढ़ोRateIn10Hz);

	info->max_lvds_pclk_freq_in_single_link =
		le16_to_cpu(info_v9->usMaxLVDSPclkFreqInSingleLink);
	info->lvds_misc = info_v9->ucLvdsMisc;
	info->lvds_pwr_on_seq_dig_on_to_de_in_4ms =
		info_v9->ucLVDSPwrOnSeqDIGONtoDE_in4Ms;
	info->lvds_pwr_on_seq_de_to_vary_bl_in_4ms =
		info_v9->ucLVDSPwrOnSeqDEtoVARY_BL_in4Ms;
	info->lvds_pwr_on_seq_vary_bl_to_blon_in_4ms =
		info_v9->ucLVDSPwrOnSeqVARY_BLtoBLON_in4Ms;
	info->lvds_pwr_off_seq_vary_bl_to_de_in4ms =
		info_v9->ucLVDSPwrOffSeqVARY_BLtoDE_in4Ms;
	info->lvds_pwr_off_seq_de_to_dig_on_in4ms =
		info_v9->ucLVDSPwrOffSeqDEtoDIGON_in4Ms;
	info->lvds_pwr_off_seq_blon_to_vary_bl_in_4ms =
		info_v9->ucLVDSPwrOffSeqBLONtoVARY_BL_in4Ms;
	info->lvds_off_to_on_delay_in_4ms =
		info_v9->ucLVDSOffToOnDelay_in4Ms;
	info->lvds_bit_depth_control_val =
		le32_to_cpu(info_v9->ulLCDBitDepthControlVal);

	क्रम (i = 0; i < NUMBER_OF_AVAILABLE_SCLK; ++i) अणु
		/* Convert [10KHz] पूर्णांकo [KHz] */
		info->avail_s_clk[i].supported_s_clk =
			le32_to_cpu(info_v9->sAvail_SCLK[i].ulSupportedSCLK) * 10;
		info->avail_s_clk[i].voltage_index =
			le16_to_cpu(info_v9->sAvail_SCLK[i].usVoltageIndex);
		info->avail_s_clk[i].voltage_id =
			le16_to_cpu(info_v9->sAvail_SCLK[i].usVoltageID);
	पूर्ण

	क्रम (i = 0; i < NUMBER_OF_UCHAR_FOR_GUID; ++i) अणु
		info->ext_disp_conn_info.gu_id[i] =
			info_v9->sExtDispConnInfo.ucGuid[i];
	पूर्ण

	क्रम (i = 0; i < MAX_NUMBER_OF_EXT_DISPLAY_PATH; ++i) अणु
		info->ext_disp_conn_info.path[i].device_connector_id =
			object_id_from_bios_object_id(
				le16_to_cpu(info_v9->sExtDispConnInfo.sPath[i].usDeviceConnector));

		info->ext_disp_conn_info.path[i].ext_encoder_obj_id =
			object_id_from_bios_object_id(
				le16_to_cpu(info_v9->sExtDispConnInfo.sPath[i].usExtEncoderObjId));

		info->ext_disp_conn_info.path[i].device_tag =
			le16_to_cpu(info_v9->sExtDispConnInfo.sPath[i].usDeviceTag);
		info->ext_disp_conn_info.path[i].device_acpi_क्रमागत =
			le16_to_cpu(info_v9->sExtDispConnInfo.sPath[i].usDeviceACPIEnum);
		info->ext_disp_conn_info.path[i].ext_aux_ddc_lut_index =
			info_v9->sExtDispConnInfo.sPath[i].ucExtAUXDDCLutIndex;
		info->ext_disp_conn_info.path[i].ext_hpd_pin_lut_index =
			info_v9->sExtDispConnInfo.sPath[i].ucExtHPDPINLutIndex;
		info->ext_disp_conn_info.path[i].channel_mapping.raw =
			info_v9->sExtDispConnInfo.sPath[i].ucChannelMapping;
	पूर्ण
	info->ext_disp_conn_info.checksum =
		info_v9->sExtDispConnInfo.ucChecksum;

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
 * वापस:
 * क्रमागत bp_result - BP_RESULT_OK अगर inक्रमmation is available,
 *                  BP_RESULT_BADBIOSTABLE otherwise.
 */
अटल क्रमागत bp_result स्थिरruct_पूर्णांकegrated_info(
	काष्ठा bios_parser *bp,
	काष्ठा पूर्णांकegrated_info *info)
अणु
	क्रमागत bp_result result = BP_RESULT_BADBIOSTABLE;

	ATOM_COMMON_TABLE_HEADER *header;
	काष्ठा atom_data_revision revision;

	अगर (bp->master_data_tbl->ListOfDataTables.IntegratedSystemInfo) अणु
		header = GET_IMAGE(ATOM_COMMON_TABLE_HEADER,
				bp->master_data_tbl->ListOfDataTables.IntegratedSystemInfo);

		get_atom_data_table_revision(header, &revision);

		/* Don't need to check major revision as they are all 1 */
		चयन (revision.minor) अणु
		हाल 8:
			result = get_पूर्णांकegrated_info_v8(bp, info);
			अवरोध;
		हाल 9:
			result = get_पूर्णांकegrated_info_v9(bp, info);
			अवरोध;
		शेष:
			वापस result;

		पूर्ण
	पूर्ण

	/* Sort voltage table from low to high*/
	अगर (result == BP_RESULT_OK) अणु
		uपूर्णांक32_t i;
		uपूर्णांक32_t j;

		क्रम (i = 1; i < NUMBER_OF_DISP_CLK_VOLTAGE; ++i) अणु
			क्रम (j = i; j > 0; --j) अणु
				अगर (
						info->disp_clk_voltage[j].max_supported_clk <
						info->disp_clk_voltage[j-1].max_supported_clk) अणु
					/* swap j and j - 1*/
					swap(info->disp_clk_voltage[j - 1],
					     info->disp_clk_voltage[j]);
				पूर्ण
			पूर्ण
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
	काष्ठा slot_layout_info *slot_layout_info,
	अचिन्हित पूर्णांक record_offset)
अणु
	अचिन्हित पूर्णांक j;
	काष्ठा bios_parser *bp;
	ATOM_BRACKET_LAYOUT_RECORD *record;
	ATOM_COMMON_RECORD_HEADER *record_header;
	क्रमागत bp_result result = BP_RESULT_NORECORD;

	bp = BP_FROM_DCB(dcb);
	record = शून्य;
	record_header = शून्य;

	क्रम (;;) अणु

		record_header = (ATOM_COMMON_RECORD_HEADER *)
			GET_IMAGE(ATOM_COMMON_RECORD_HEADER, record_offset);
		अगर (record_header == शून्य) अणु
			result = BP_RESULT_BADBIOSTABLE;
			अवरोध;
		पूर्ण

		/* the end of the list */
		अगर (record_header->ucRecordType == 0xff ||
			record_header->ucRecordSize == 0)	अणु
			अवरोध;
		पूर्ण

		अगर (record_header->ucRecordType ==
			ATOM_BRACKET_LAYOUT_RECORD_TYPE &&
			माप(ATOM_BRACKET_LAYOUT_RECORD)
			<= record_header->ucRecordSize) अणु
			record = (ATOM_BRACKET_LAYOUT_RECORD *)
				(record_header);
			result = BP_RESULT_OK;
			अवरोध;
		पूर्ण

		record_offset += record_header->ucRecordSize;
	पूर्ण

	/* वापस अगर the record not found */
	अगर (result != BP_RESULT_OK)
		वापस result;

	/* get slot sizes */
	slot_layout_info->length = record->ucLength;
	slot_layout_info->width = record->ucWidth;

	/* get info क्रम each connector in the slot */
	slot_layout_info->num_of_connectors = record->ucConnNum;
	क्रम (j = 0; j < slot_layout_info->num_of_connectors; ++j) अणु
		slot_layout_info->connectors[j].connector_type =
			(क्रमागत connector_layout_type)
			(record->asConnInfo[j].ucConnectorType);
		चयन (record->asConnInfo[j].ucConnectorType) अणु
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
			record->asConnInfo[j].ucPosition;
		slot_layout_info->connectors[j].connector_id =
			object_id_from_bios_object_id(
				record->asConnInfo[j].usConnectorObjectId);
	पूर्ण
	वापस result;
पूर्ण


अटल क्रमागत bp_result get_bracket_layout_record(
	काष्ठा dc_bios *dcb,
	अचिन्हित पूर्णांक bracket_layout_id,
	काष्ठा slot_layout_info *slot_layout_info)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक record_offset;
	काष्ठा bios_parser *bp;
	क्रमागत bp_result result;
	ATOM_OBJECT *object;
	ATOM_OBJECT_TABLE *object_table;
	अचिन्हित पूर्णांक genericTableOffset;

	bp = BP_FROM_DCB(dcb);
	object = शून्य;
	अगर (slot_layout_info == शून्य) अणु
		DC_LOG_DETECTION_EDID_PARSER("Invalid slot_layout_info\n");
		वापस BP_RESULT_BADINPUT;
	पूर्ण


	genericTableOffset = bp->object_info_tbl_offset +
		bp->object_info_tbl.v1_3->usMiscObjectTableOffset;
	object_table = (ATOM_OBJECT_TABLE *)
		GET_IMAGE(ATOM_OBJECT_TABLE, genericTableOffset);
	अगर (!object_table)
		वापस BP_RESULT_FAILURE;

	result = BP_RESULT_NORECORD;
	क्रम (i = 0; i < object_table->ucNumberOfObjects; ++i) अणु

		अगर (bracket_layout_id ==
			object_table->asObjects[i].usObjectID) अणु

			object = &object_table->asObjects[i];
			record_offset = object->usRecordOffset +
				bp->object_info_tbl_offset;

			result = update_slot_layout_info(dcb, i,
				slot_layout_info, record_offset);
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

/******************************************************************************/

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

	/* bios scratch रेजिस्टर communication */
	.is_accelerated_mode = bios_is_accelerated_mode,

	.set_scratch_critical_state = bios_parser_set_scratch_critical_state,

	.is_device_id_supported = bios_parser_is_device_id_supported,

	/* COMMANDS */
	.encoder_control = bios_parser_encoder_control,

	.transmitter_control = bios_parser_transmitter_control,

	.enable_crtc = bios_parser_enable_crtc,

	.adjust_pixel_घड़ी = bios_parser_adjust_pixel_घड़ी,

	.set_pixel_घड़ी = bios_parser_set_pixel_घड़ी,

	.set_dce_घड़ी = bios_parser_set_dce_घड़ी,

	.enable_spपढ़ो_spectrum_on_ppll = bios_parser_enable_spपढ़ो_spectrum_on_ppll,

	.program_crtc_timing = bios_parser_program_crtc_timing, /* still use.  should probably retire and program directly */

	.program_display_engine_pll = bios_parser_program_display_engine_pll,

	.enable_disp_घातer_gating = bios_parser_enable_disp_घातer_gating,

	/* SW init and patch */

	.bios_parser_destroy = bios_parser_destroy,

	.get_board_layout_info = bios_get_board_layout_info,

	.get_atom_dc_golden_table = शून्य
पूर्ण;

अटल bool bios_parser_स्थिरruct(
	काष्ठा bios_parser *bp,
	काष्ठा bp_init_data *init,
	क्रमागत dce_version dce_version)
अणु
	uपूर्णांक16_t *rom_header_offset = शून्य;
	ATOM_ROM_HEADER *rom_header = शून्य;
	ATOM_OBJECT_HEADER *object_info_tbl;
	काष्ठा atom_data_revision tbl_rev = अणु0पूर्ण;

	अगर (!init)
		वापस false;

	अगर (!init->bios)
		वापस false;

	bp->base.funcs = &vbios_funcs;
	bp->base.bios = init->bios;
	bp->base.bios_size = bp->base.bios[BIOS_IMAGE_SIZE_OFFSET] * BIOS_IMAGE_SIZE_UNIT;

	bp->base.ctx = init->ctx;
	bp->base.bios_local_image = शून्य;

	rom_header_offset =
	GET_IMAGE(uपूर्णांक16_t, OFFSET_TO_POINTER_TO_ATOM_ROM_HEADER);

	अगर (!rom_header_offset)
		वापस false;

	rom_header = GET_IMAGE(ATOM_ROM_HEADER, *rom_header_offset);

	अगर (!rom_header)
		वापस false;

	get_atom_data_table_revision(&rom_header->sHeader, &tbl_rev);
	अगर (tbl_rev.major >= 2 && tbl_rev.minor >= 2)
		वापस false;

	bp->master_data_tbl =
	GET_IMAGE(ATOM_MASTER_DATA_TABLE,
		rom_header->usMasterDataTableOffset);

	अगर (!bp->master_data_tbl)
		वापस false;

	bp->object_info_tbl_offset = DATA_TABLES(Object_Header);

	अगर (!bp->object_info_tbl_offset)
		वापस false;

	object_info_tbl =
	GET_IMAGE(ATOM_OBJECT_HEADER, bp->object_info_tbl_offset);

	अगर (!object_info_tbl)
		वापस false;

	get_atom_data_table_revision(&object_info_tbl->sHeader,
		&bp->object_info_tbl.revision);

	अगर (bp->object_info_tbl.revision.major == 1
		&& bp->object_info_tbl.revision.minor >= 3) अणु
		ATOM_OBJECT_HEADER_V3 *tbl_v3;

		tbl_v3 = GET_IMAGE(ATOM_OBJECT_HEADER_V3,
			bp->object_info_tbl_offset);
		अगर (!tbl_v3)
			वापस false;

		bp->object_info_tbl.v1_3 = tbl_v3;
	पूर्ण अन्यथा अगर (bp->object_info_tbl.revision.major == 1
		&& bp->object_info_tbl.revision.minor >= 1)
		bp->object_info_tbl.v1_1 = object_info_tbl;
	अन्यथा
		वापस false;

	dal_bios_parser_init_cmd_tbl(bp);
	dal_bios_parser_init_cmd_tbl_helper(&bp->cmd_helper, dce_version);

	bp->base.पूर्णांकegrated_info = bios_parser_create_पूर्णांकegrated_info(&bp->base);
	bp->base.fw_info_valid = bios_parser_get_firmware_info(&bp->base, &bp->base.fw_info) == BP_RESULT_OK;

	वापस true;
पूर्ण

/******************************************************************************/
