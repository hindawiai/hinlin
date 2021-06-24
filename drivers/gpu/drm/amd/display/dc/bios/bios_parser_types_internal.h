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

#अगर_अघोषित __DAL_BIOS_PARSER_TYPES_BIOS_H__
#घोषणा __DAL_BIOS_PARSER_TYPES_BIOS_H__

#समावेश "dc_bios_types.h"
#समावेश "bios_parser_helper.h"

काष्ठा atom_data_revision अणु
	uपूर्णांक32_t major;
	uपूर्णांक32_t minor;
पूर्ण;

काष्ठा object_info_table अणु
	काष्ठा atom_data_revision revision;
	जोड़ अणु
		ATOM_OBJECT_HEADER *v1_1;
		ATOM_OBJECT_HEADER_V3 *v1_3;
	पूर्ण;
पूर्ण;

क्रमागत spपढ़ो_spectrum_id अणु
	SS_ID_UNKNOWN = 0,
	SS_ID_DP1 = 0xf1,
	SS_ID_DP2 = 0xf2,
	SS_ID_LVLINK_2700MHZ = 0xf3,
	SS_ID_LVLINK_1620MHZ = 0xf4
पूर्ण;

काष्ठा bios_parser अणु
	काष्ठा dc_bios base;

	काष्ठा object_info_table object_info_tbl;
	uपूर्णांक32_t object_info_tbl_offset;
	ATOM_MASTER_DATA_TABLE *master_data_tbl;

	स्थिर काष्ठा bios_parser_helper *bios_helper;

	स्थिर काष्ठा command_table_helper *cmd_helper;
	काष्ठा cmd_tbl cmd_tbl;

	bool remap_device_tags;
पूर्ण;

/* Bios Parser from DC Bios */
#घोषणा BP_FROM_DCB(dc_bios) \
	container_of(dc_bios, काष्ठा bios_parser, base)

#पूर्ण_अगर
