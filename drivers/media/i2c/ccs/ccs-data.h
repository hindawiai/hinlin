<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * CCS अटल data in-memory data काष्ठाure definitions
 *
 * Copyright 2019--2020 Intel Corporation
 */

#अगर_अघोषित __CCS_DATA_H__
#घोषणा __CCS_DATA_H__

#समावेश <linux/types.h>

काष्ठा device;

/**
 * काष्ठा ccs_data_block_version - CCS अटल data version
 * @version_major: Major version number
 * @version_minor: Minor version number
 * @date_year: Year
 * @date_month: Month
 * @date_day: Day
 */
काष्ठा ccs_data_block_version अणु
	u16 version_major;
	u16 version_minor;
	u16 date_year;
	u8 date_month;
	u8 date_day;
पूर्ण;

/**
 * काष्ठा ccs_reg - CCS रेजिस्टर value
 * @addr: The 16-bit address of the रेजिस्टर
 * @len: Length of the data
 * @value: Data
 */
काष्ठा ccs_reg अणु
	u16 addr;
	u16 len;
	u8 *value;
पूर्ण;

/**
 * काष्ठा ccs_अगर_rule - CCS अटल data अगर rule
 * @addr: Register address
 * @value: Register value
 * @mask: Value applied to both actual रेजिस्टर value and @value
 */
काष्ठा ccs_अगर_rule अणु
	u16 addr;
	u8 value;
	u8 mask;
पूर्ण;

/**
 * काष्ठा ccs_frame_क्रमmat_desc - CCS frame क्रमmat descriptor
 * @pixelcode: The pixelcode; CCS_DATA_BLOCK_FFD_PIXELCODE_*
 * @value: Value related to the pixelcode
 */
काष्ठा ccs_frame_क्रमmat_desc अणु
	u8 pixelcode;
	u16 value;
पूर्ण;

/**
 * काष्ठा ccs_frame_क्रमmat_descs - A series of CCS frame क्रमmat descriptors
 * @num_column_descs: Number of column descriptors
 * @num_row_descs: Number of row descriptors
 * @column_descs: Column descriptors
 * @row_descs: Row descriptors
 */
काष्ठा ccs_frame_क्रमmat_descs अणु
	u8 num_column_descs;
	u8 num_row_descs;
	काष्ठा ccs_frame_क्रमmat_desc *column_descs;
	काष्ठा ccs_frame_क्रमmat_desc *row_descs;
पूर्ण;

/**
 * काष्ठा ccs_pdaf_पढ़ोout - CCS PDAF data पढ़ोout descriptor
 * @pdaf_पढ़ोout_info_order: PDAF पढ़ोout order
 * @ffd: Frame क्रमmat of PDAF data
 */
काष्ठा ccs_pdaf_पढ़ोout अणु
	u8 pdaf_पढ़ोout_info_order;
	काष्ठा ccs_frame_क्रमmat_descs *ffd;
पूर्ण;

/**
 * काष्ठा ccs_rule - A CCS अटल data rule
 * @num_अगर_rules: Number of अगर rules
 * @अगर_rules: If rules
 * @num_पढ़ो_only_regs: Number of पढ़ो-only रेजिस्टरs
 * @पढ़ो_only_regs: Read-only रेजिस्टरs
 * @num_manufacturer_regs: Number of manufacturer-specअगरic रेजिस्टरs
 * @manufacturer_regs: Manufacturer-specअगरic रेजिस्टरs
 * @frame_क्रमmat: Frame क्रमmat
 * @pdaf_पढ़ोout: PDAF पढ़ोout
 */
काष्ठा ccs_rule अणु
	माप_प्रकार num_अगर_rules;
	काष्ठा ccs_अगर_rule *अगर_rules;
	माप_प्रकार num_पढ़ो_only_regs;
	काष्ठा ccs_reg *पढ़ो_only_regs;
	माप_प्रकार num_manufacturer_regs;
	काष्ठा ccs_reg *manufacturer_regs;
	काष्ठा ccs_frame_क्रमmat_descs *frame_क्रमmat;
	काष्ठा ccs_pdaf_पढ़ोout *pdaf_पढ़ोout;
पूर्ण;

/**
 * काष्ठा ccs_pdaf_pix_loc_block_desc - PDAF pixel location block descriptor
 * @block_type_id: Block type identअगरier, from 0 to n
 * @repeat_x: Number of बार this block is repeated to right
 */
काष्ठा ccs_pdaf_pix_loc_block_desc अणु
	u8 block_type_id;
	u16 repeat_x;
पूर्ण;

/**
 * काष्ठा ccs_pdaf_pix_loc_block_desc_group - PDAF pixel location block
 *					      descriptor group
 * @repeat_y: Number of बार the group is repeated करोwn
 * @num_block_descs: Number of block descriptors in @block_descs
 * @block_descs: Block descriptors
 */
काष्ठा ccs_pdaf_pix_loc_block_desc_group अणु
	u8 repeat_y;
	u16 num_block_descs;
	काष्ठा ccs_pdaf_pix_loc_block_desc *block_descs;
पूर्ण;

/**
 * काष्ठा ccs_pdaf_pix_loc_pixel_desc - PDAF pixel location block descriptor
 * @pixel_type: Type of the pixel; CCS_DATA_PDAF_PIXEL_TYPE_*
 * @small_offset_x: offset X coordinate
 * @small_offset_y: offset Y coordinate
 */
काष्ठा ccs_pdaf_pix_loc_pixel_desc अणु
	u8 pixel_type;
	u8 small_offset_x;
	u8 small_offset_y;
पूर्ण;

/**
 * काष्ठा ccs_pdaf_pix_loc_pixel_desc_group - PDAF pixel location pixel
 *					      descriptor group
 * @num_descs: Number of descriptors in @descs
 * @descs: PDAF pixel location pixel descriptors
 */
काष्ठा ccs_pdaf_pix_loc_pixel_desc_group अणु
	u8 num_descs;
	काष्ठा ccs_pdaf_pix_loc_pixel_desc *descs;
पूर्ण;

/**
 * काष्ठा ccs_pdaf_pix_loc - PDAF pixel locations
 * @मुख्य_offset_x: Start X coordinate of PDAF pixel blocks
 * @मुख्य_offset_y: Start Y coordinate of PDAF pixel blocks
 * @global_pdaf_type: PDAF pattern type
 * @block_width: Width of a block in pixels
 * @block_height: Heigth of a block in pixels
 * @num_block_desc_groups: Number of block descriptor groups
 * @block_desc_groups: Block descriptor groups
 * @num_pixel_desc_grups: Number of pixel descriptor groups
 * @pixel_desc_groups: Pixel descriptor groups
 */
काष्ठा ccs_pdaf_pix_loc अणु
	u16 मुख्य_offset_x;
	u16 मुख्य_offset_y;
	u8 global_pdaf_type;
	u8 block_width;
	u8 block_height;
	u16 num_block_desc_groups;
	काष्ठा ccs_pdaf_pix_loc_block_desc_group *block_desc_groups;
	u8 num_pixel_desc_grups;
	काष्ठा ccs_pdaf_pix_loc_pixel_desc_group *pixel_desc_groups;
पूर्ण;

/**
 * काष्ठा ccs_data_container - In-memory CCS अटल data
 * @version: CCS अटल data version
 * @num_sensor_पढ़ो_only_regs: Number of the पढ़ो-only रेजिस्टरs क्रम the sensor
 * @sensor_पढ़ो_only_regs: Read-only रेजिस्टरs क्रम the sensor
 * @num_sensor_manufacturer_regs: Number of the manufacturer-specअगरic रेजिस्टरs
 *				  क्रम the sensor
 * @sensor_manufacturer_regs: Manufacturer-specअगरic रेजिस्टरs क्रम the sensor
 * @num_sensor_rules: Number of rules क्रम the sensor
 * @sensor_rules: Rules क्रम the sensor
 * @num_module_पढ़ो_only_regs: Number of the पढ़ो-only रेजिस्टरs क्रम the module
 * @module_पढ़ो_only_regs: Read-only रेजिस्टरs क्रम the module
 * @num_module_manufacturer_regs: Number of the manufacturer-specअगरic रेजिस्टरs
 *				  क्रम the module
 * @module_manufacturer_regs: Manufacturer-specअगरic रेजिस्टरs क्रम the module
 * @num_module_rules: Number of rules क्रम the module
 * @module_rules: Rules क्रम the module
 * @sensor_pdaf: PDAF data क्रम the sensor
 * @module_pdaf: PDAF data क्रम the module
 * @license_length: Lenght of the license data
 * @license: License data
 * @end: Whether or not there's an end block
 * @backing: Raw data, poपूर्णांकed to from अन्यथाwhere so keep it around
 */
काष्ठा ccs_data_container अणु
	काष्ठा ccs_data_block_version *version;
	माप_प्रकार num_sensor_पढ़ो_only_regs;
	काष्ठा ccs_reg *sensor_पढ़ो_only_regs;
	माप_प्रकार num_sensor_manufacturer_regs;
	काष्ठा ccs_reg *sensor_manufacturer_regs;
	माप_प्रकार num_sensor_rules;
	काष्ठा ccs_rule *sensor_rules;
	माप_प्रकार num_module_पढ़ो_only_regs;
	काष्ठा ccs_reg *module_पढ़ो_only_regs;
	माप_प्रकार num_module_manufacturer_regs;
	काष्ठा ccs_reg *module_manufacturer_regs;
	माप_प्रकार num_module_rules;
	काष्ठा ccs_rule *module_rules;
	काष्ठा ccs_pdaf_pix_loc *sensor_pdaf;
	काष्ठा ccs_pdaf_pix_loc *module_pdaf;
	माप_प्रकार license_length;
	अक्षर *license;
	bool end;
	व्योम *backing;
पूर्ण;

पूर्णांक ccs_data_parse(काष्ठा ccs_data_container *ccsdata, स्थिर व्योम *data,
		   माप_प्रकार len, काष्ठा device *dev, bool verbose);

#पूर्ण_अगर /* __CCS_DATA_H__ */
