<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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

#अगर_अघोषित KFD_PM4_HEADERS_H_
#घोषणा KFD_PM4_HEADERS_H_

#अगर_अघोषित PM4_MES_HEADER_DEFINED
#घोषणा PM4_MES_HEADER_DEFINED
जोड़ PM4_MES_TYPE_3_HEADER अणु
	काष्ठा अणु
		/* reserved */
		uपूर्णांक32_t reserved1:8;
		/* IT opcode */
		uपूर्णांक32_t opcode:8;
		/* number of DWORDs - 1 in the inक्रमmation body */
		uपूर्णांक32_t count:14;
		/* packet identअगरier. It should be 3 क्रम type 3 packets */
		uपूर्णांक32_t type:2;
	पूर्ण;
	uपूर्णांक32_t u32all;
पूर्ण;
#पूर्ण_अगर /* PM4_MES_HEADER_DEFINED */


/*--------------------MES_MAP_PROCESS-------------------- */

#अगर_अघोषित PM4_MES_MAP_PROCESS_DEFINED
#घोषणा PM4_MES_MAP_PROCESS_DEFINED

काष्ठा pm4_map_process अणु
	जोड़ अणु
		जोड़ PM4_MES_TYPE_3_HEADER header;	/* header */
		uपूर्णांक32_t ordinal1;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t pasid:16;
			uपूर्णांक32_t reserved1:8;
			uपूर्णांक32_t diq_enable:1;
			uपूर्णांक32_t process_quantum:7;
		पूर्ण bitfields2;
		uपूर्णांक32_t ordinal2;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t page_table_base:28;
			uपूर्णांक32_t reserved3:4;
		पूर्ण bitfields3;
		uपूर्णांक32_t ordinal3;
	पूर्ण;

	uपूर्णांक32_t sh_mem_bases;
	uपूर्णांक32_t sh_mem_ape1_base;
	uपूर्णांक32_t sh_mem_ape1_limit;
	uपूर्णांक32_t sh_mem_config;
	uपूर्णांक32_t gds_addr_lo;
	uपूर्णांक32_t gds_addr_hi;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t num_gws:6;
			uपूर्णांक32_t reserved4:2;
			uपूर्णांक32_t num_oac:4;
			uपूर्णांक32_t reserved5:4;
			uपूर्णांक32_t gds_size:6;
			uपूर्णांक32_t num_queues:10;
		पूर्ण bitfields10;
		uपूर्णांक32_t ordinal10;
	पूर्ण;

पूर्ण;
#पूर्ण_अगर

#अगर_अघोषित PM4_MES_MAP_PROCESS_DEFINED_KV_SCRATCH
#घोषणा PM4_MES_MAP_PROCESS_DEFINED_KV_SCRATCH

काष्ठा pm4_map_process_scratch_kv अणु
	जोड़ अणु
		जोड़ PM4_MES_TYPE_3_HEADER   header; /* header */
		uपूर्णांक32_t            ordinal1;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t pasid:16;
			uपूर्णांक32_t reserved1:8;
			uपूर्णांक32_t diq_enable:1;
			uपूर्णांक32_t process_quantum:7;
		पूर्ण bitfields2;
		uपूर्णांक32_t ordinal2;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t page_table_base:28;
			uपूर्णांक32_t reserved2:4;
		पूर्ण bitfields3;
		uपूर्णांक32_t ordinal3;
	पूर्ण;

	uपूर्णांक32_t reserved3;
	uपूर्णांक32_t sh_mem_bases;
	uपूर्णांक32_t sh_mem_config;
	uपूर्णांक32_t sh_mem_ape1_base;
	uपूर्णांक32_t sh_mem_ape1_limit;
	uपूर्णांक32_t sh_hidden_निजी_base_vmid;
	uपूर्णांक32_t reserved4;
	uपूर्णांक32_t reserved5;
	uपूर्णांक32_t gds_addr_lo;
	uपूर्णांक32_t gds_addr_hi;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t num_gws:6;
			uपूर्णांक32_t reserved6:2;
			uपूर्णांक32_t num_oac:4;
			uपूर्णांक32_t reserved7:4;
			uपूर्णांक32_t gds_size:6;
			uपूर्णांक32_t num_queues:10;
		पूर्ण bitfields14;
		uपूर्णांक32_t ordinal14;
	पूर्ण;

	uपूर्णांक32_t completion_संकेत_lo32;
uपूर्णांक32_t completion_संकेत_hi32;
पूर्ण;
#पूर्ण_अगर

क्रमागत अणु
	CACHE_FLUSH_AND_INV_TS_EVENT = 0x00000014
पूर्ण;

#पूर्ण_अगर /* KFD_PM4_HEADERS_H_ */
