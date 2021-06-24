<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __MMSCH_V1_0_H__
#घोषणा __MMSCH_V1_0_H__

#घोषणा MMSCH_VERSION_MAJOR	1
#घोषणा MMSCH_VERSION_MINOR	0
#घोषणा MMSCH_VERSION	(MMSCH_VERSION_MAJOR << 16 | MMSCH_VERSION_MINOR)

क्रमागत mmsch_v1_0_command_type अणु
	MMSCH_COMMAND__सूचीECT_REG_WRITE = 0,
	MMSCH_COMMAND__सूचीECT_REG_POLLING = 2,
	MMSCH_COMMAND__सूचीECT_REG_READ_MODIFY_WRITE = 3,
	MMSCH_COMMAND__INसूचीECT_REG_WRITE = 8,
	MMSCH_COMMAND__END = 0xf
पूर्ण;

काष्ठा mmsch_v1_0_init_header अणु
	uपूर्णांक32_t version;
	uपूर्णांक32_t header_size;
	uपूर्णांक32_t vce_init_status;
	uपूर्णांक32_t uvd_init_status;
	uपूर्णांक32_t vce_table_offset;
	uपूर्णांक32_t vce_table_size;
	uपूर्णांक32_t uvd_table_offset;
	uपूर्णांक32_t uvd_table_size;
पूर्ण;

काष्ठा mmsch_vf_eng_init_header अणु
	uपूर्णांक32_t init_status;
	uपूर्णांक32_t table_offset;
	uपूर्णांक32_t table_size;
पूर्ण;

काष्ठा mmsch_v1_1_init_header अणु
	uपूर्णांक32_t version;
	uपूर्णांक32_t total_size;
	काष्ठा mmsch_vf_eng_init_header eng[2];
पूर्ण;

काष्ठा mmsch_v1_0_cmd_direct_reg_header अणु
	uपूर्णांक32_t reg_offset   : 28;
	uपूर्णांक32_t command_type : 4;
पूर्ण;

काष्ठा mmsch_v1_0_cmd_indirect_reg_header अणु
	uपूर्णांक32_t reg_offset    : 20;
	uपूर्णांक32_t reg_idx_space : 8;
	uपूर्णांक32_t command_type  : 4;
पूर्ण;

काष्ठा mmsch_v1_0_cmd_direct_ग_लिखो अणु
	काष्ठा mmsch_v1_0_cmd_direct_reg_header cmd_header;
	uपूर्णांक32_t reg_value;
पूर्ण;

काष्ठा mmsch_v1_0_cmd_direct_पढ़ो_modअगरy_ग_लिखो अणु
	काष्ठा mmsch_v1_0_cmd_direct_reg_header cmd_header;
	uपूर्णांक32_t ग_लिखो_data;
	uपूर्णांक32_t mask_value;
पूर्ण;

काष्ठा mmsch_v1_0_cmd_direct_polling अणु
	काष्ठा mmsch_v1_0_cmd_direct_reg_header cmd_header;
	uपूर्णांक32_t mask_value;
	uपूर्णांक32_t रुको_value;
पूर्ण;

काष्ठा mmsch_v1_0_cmd_end अणु
	काष्ठा mmsch_v1_0_cmd_direct_reg_header cmd_header;
पूर्ण;

काष्ठा mmsch_v1_0_cmd_indirect_ग_लिखो अणु
	काष्ठा mmsch_v1_0_cmd_indirect_reg_header cmd_header;
	uपूर्णांक32_t reg_value;
पूर्ण;

अटल अंतरभूत व्योम mmsch_v1_0_insert_direct_wt(काष्ठा mmsch_v1_0_cmd_direct_ग_लिखो *direct_wt,
					       uपूर्णांक32_t *init_table,
					       uपूर्णांक32_t reg_offset,
					       uपूर्णांक32_t value)
अणु
	direct_wt->cmd_header.reg_offset = reg_offset;
	direct_wt->reg_value = value;
	स_नकल((व्योम *)init_table, direct_wt, माप(काष्ठा mmsch_v1_0_cmd_direct_ग_लिखो));
पूर्ण

अटल अंतरभूत व्योम mmsch_v1_0_insert_direct_rd_mod_wt(काष्ठा mmsch_v1_0_cmd_direct_पढ़ो_modअगरy_ग_लिखो *direct_rd_mod_wt,
						      uपूर्णांक32_t *init_table,
						      uपूर्णांक32_t reg_offset,
						      uपूर्णांक32_t mask, uपूर्णांक32_t data)
अणु
	direct_rd_mod_wt->cmd_header.reg_offset = reg_offset;
	direct_rd_mod_wt->mask_value = mask;
	direct_rd_mod_wt->ग_लिखो_data = data;
	स_नकल((व्योम *)init_table, direct_rd_mod_wt,
	       माप(काष्ठा mmsch_v1_0_cmd_direct_पढ़ो_modअगरy_ग_लिखो));
पूर्ण

अटल अंतरभूत व्योम mmsch_v1_0_insert_direct_poll(काष्ठा mmsch_v1_0_cmd_direct_polling *direct_poll,
						 uपूर्णांक32_t *init_table,
						 uपूर्णांक32_t reg_offset,
						 uपूर्णांक32_t mask, uपूर्णांक32_t रुको)
अणु
	direct_poll->cmd_header.reg_offset = reg_offset;
	direct_poll->mask_value = mask;
	direct_poll->रुको_value = रुको;
	स_नकल((व्योम *)init_table, direct_poll, माप(काष्ठा mmsch_v1_0_cmd_direct_polling));
पूर्ण

#घोषणा MMSCH_V1_0_INSERT_सूचीECT_RD_MOD_WT(reg, mask, data) अणु \
	mmsch_v1_0_insert_direct_rd_mod_wt(&direct_rd_mod_wt, \
					   init_table, (reg), \
					   (mask), (data)); \
	init_table += माप(काष्ठा mmsch_v1_0_cmd_direct_पढ़ो_modअगरy_ग_लिखो)/4; \
	table_size += माप(काष्ठा mmsch_v1_0_cmd_direct_पढ़ो_modअगरy_ग_लिखो)/4; \
पूर्ण

#घोषणा MMSCH_V1_0_INSERT_सूचीECT_WT(reg, value) अणु \
	mmsch_v1_0_insert_direct_wt(&direct_wt, \
				    init_table, (reg), \
				    (value)); \
	init_table += माप(काष्ठा mmsch_v1_0_cmd_direct_ग_लिखो)/4; \
	table_size += माप(काष्ठा mmsch_v1_0_cmd_direct_ग_लिखो)/4; \
पूर्ण

#घोषणा MMSCH_V1_0_INSERT_सूचीECT_POLL(reg, mask, रुको) अणु \
	mmsch_v1_0_insert_direct_poll(&direct_poll, \
				      init_table, (reg), \
				      (mask), (रुको)); \
	init_table += माप(काष्ठा mmsch_v1_0_cmd_direct_polling)/4; \
	table_size += माप(काष्ठा mmsch_v1_0_cmd_direct_polling)/4; \
पूर्ण

#पूर्ण_अगर
