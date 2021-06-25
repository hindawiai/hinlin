<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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

#अगर_अघोषित _AMDGPU_RAS_EEPROM_H
#घोषणा _AMDGPU_RAS_EEPROM_H

#समावेश <linux/i2c.h>

काष्ठा amdgpu_device;

क्रमागत amdgpu_ras_eeprom_err_typeअणु
	AMDGPU_RAS_EEPROM_ERR_PLACE_HOLDER,
	AMDGPU_RAS_EEPROM_ERR_RECOVERABLE,
	AMDGPU_RAS_EEPROM_ERR_NON_RECOVERABLE
पूर्ण;

काष्ठा amdgpu_ras_eeprom_table_header अणु
	uपूर्णांक32_t header;
	uपूर्णांक32_t version;
	uपूर्णांक32_t first_rec_offset;
	uपूर्णांक32_t tbl_size;
	uपूर्णांक32_t checksum;
पूर्ण__attribute__((__packed__));

काष्ठा amdgpu_ras_eeprom_control अणु
	काष्ठा amdgpu_ras_eeprom_table_header tbl_hdr;
	uपूर्णांक32_t next_addr;
	अचिन्हित पूर्णांक num_recs;
	काष्ठा mutex tbl_mutex;
	uपूर्णांक32_t tbl_byte_sum;
	uपूर्णांक16_t i2c_address; // 8-bit represented address
पूर्ण;

/*
 * Represents single table record. Packed to be easily serialized पूर्णांकo byte
 * stream.
 */
काष्ठा eeprom_table_record अणु

	जोड़ अणु
		uपूर्णांक64_t address;
		uपूर्णांक64_t offset;
	पूर्ण;

	uपूर्णांक64_t retired_page;
	uपूर्णांक64_t ts;

	क्रमागत amdgpu_ras_eeprom_err_type err_type;

	जोड़ अणु
		अचिन्हित अक्षर bank;
		अचिन्हित अक्षर cu;
	पूर्ण;

	अचिन्हित अक्षर mem_channel;
	अचिन्हित अक्षर mcumc_id;
पूर्ण__attribute__((__packed__));

पूर्णांक amdgpu_ras_eeprom_init(काष्ठा amdgpu_ras_eeprom_control *control,
			bool *exceed_err_limit);
पूर्णांक amdgpu_ras_eeprom_reset_table(काष्ठा amdgpu_ras_eeprom_control *control);

bool amdgpu_ras_eeprom_check_err_threshold(काष्ठा amdgpu_device *adev);

पूर्णांक amdgpu_ras_eeprom_process_recods(काष्ठा amdgpu_ras_eeprom_control *control,
					    काष्ठा eeprom_table_record *records,
					    bool ग_लिखो,
					    पूर्णांक num);

अंतरभूत uपूर्णांक32_t amdgpu_ras_eeprom_get_record_max_length(व्योम);

व्योम amdgpu_ras_eeprom_test(काष्ठा amdgpu_ras_eeprom_control *control);

#पूर्ण_अगर // _AMDGPU_RAS_EEPROM_H
