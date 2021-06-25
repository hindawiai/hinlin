<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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
 */
#अगर_अघोषित __COMMON_BOCO_H__
#घोषणा __COMMON_BOCO_H__
#समावेश "hwmgr.h"


क्रमागत baco_cmd_type अणु
	CMD_WRITE = 0,
	CMD_READMODIFYWRITE,
	CMD_WAITFOR,
	CMD_DELAY_MS,
	CMD_DELAY_US,
पूर्ण;

काष्ठा baco_cmd_entry अणु
	क्रमागत baco_cmd_type cmd;
	uपूर्णांक32_t 	reg_offset;
	uपूर्णांक32_t     	mask;
	uपूर्णांक32_t     	shअगरt;
	uपूर्णांक32_t     	समयout;
	uपूर्णांक32_t     	val;
पूर्ण;

काष्ठा soc15_baco_cmd_entry अणु
	क्रमागत baco_cmd_type cmd;
	uपूर्णांक32_t 	hwip;
	uपूर्णांक32_t 	inst;
	uपूर्णांक32_t 	seg;
	uपूर्णांक32_t 	reg_offset;
	uपूर्णांक32_t     	mask;
	uपूर्णांक32_t     	shअगरt;
	uपूर्णांक32_t     	समयout;
	uपूर्णांक32_t     	val;
पूर्ण;

बाह्य bool baco_program_रेजिस्टरs(काष्ठा pp_hwmgr *hwmgr,
				   स्थिर काष्ठा baco_cmd_entry *entry,
				   स्थिर u32 array_size);
बाह्य bool soc15_baco_program_रेजिस्टरs(काष्ठा pp_hwmgr *hwmgr,
					स्थिर काष्ठा soc15_baco_cmd_entry *entry,
					स्थिर u32 array_size);
#पूर्ण_अगर
