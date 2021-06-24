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

#अगर_अघोषित KFD_PM4_HEADERS_DIQ_H_
#घोषणा KFD_PM4_HEADERS_DIQ_H_

/*--------------------_INसूचीECT_BUFFER-------------------- */

#अगर_अघोषित _PM4__INसूचीECT_BUFFER_DEFINED
#घोषणा _PM4__INसूचीECT_BUFFER_DEFINED
क्रमागत _INसूचीECT_BUFFER_cache_policy_क्रमागत अणु
	cache_policy___indirect_buffer__lru = 0,
	cache_policy___indirect_buffer__stream = 1,
	cache_policy___indirect_buffer__bypass = 2
पूर्ण;

क्रमागत अणु
	IT_INसूचीECT_BUFFER_PASID = 0x5C
पूर्ण;

काष्ठा pm4__indirect_buffer_pasid अणु
	जोड़ अणु
		जोड़ PM4_MES_TYPE_3_HEADER header;	/* header */
		अचिन्हित पूर्णांक ordinal1;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक reserved1:2;
			अचिन्हित पूर्णांक ib_base_lo:30;
		पूर्ण bitfields2;
		अचिन्हित पूर्णांक ordinal2;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक ib_base_hi:16;
			अचिन्हित पूर्णांक reserved2:16;
		पूर्ण bitfields3;
		अचिन्हित पूर्णांक ordinal3;
	पूर्ण;

	जोड़ अणु
		अचिन्हित पूर्णांक control;
		अचिन्हित पूर्णांक ordinal4;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक pasid:10;
			अचिन्हित पूर्णांक reserved4:22;
		पूर्ण bitfields5;
		अचिन्हित पूर्णांक ordinal5;
	पूर्ण;

पूर्ण;

#पूर्ण_अगर

/*--------------------_RELEASE_MEM-------------------- */

#अगर_अघोषित _PM4__RELEASE_MEM_DEFINED
#घोषणा _PM4__RELEASE_MEM_DEFINED
क्रमागत _RELEASE_MEM_event_index_क्रमागत अणु
	event_index___release_mem__end_of_pipe = 5,
	event_index___release_mem__shader_करोne = 6
पूर्ण;

क्रमागत _RELEASE_MEM_cache_policy_क्रमागत अणु
	cache_policy___release_mem__lru = 0,
	cache_policy___release_mem__stream = 1,
	cache_policy___release_mem__bypass = 2
पूर्ण;

क्रमागत _RELEASE_MEM_dst_sel_क्रमागत अणु
	dst_sel___release_mem__memory_controller = 0,
	dst_sel___release_mem__tc_l2 = 1,
	dst_sel___release_mem__queue_ग_लिखो_poपूर्णांकer_रेजिस्टर = 2,
	dst_sel___release_mem__queue_ग_लिखो_poपूर्णांकer_poll_mask_bit = 3
पूर्ण;

क्रमागत _RELEASE_MEM_पूर्णांक_sel_क्रमागत अणु
	पूर्णांक_sel___release_mem__none = 0,
	पूर्णांक_sel___release_mem__send_पूर्णांकerrupt_only = 1,
	पूर्णांक_sel___release_mem__send_पूर्णांकerrupt_after_ग_लिखो_confirm = 2,
	पूर्णांक_sel___release_mem__send_data_after_ग_लिखो_confirm = 3
पूर्ण;

क्रमागत _RELEASE_MEM_data_sel_क्रमागत अणु
	data_sel___release_mem__none = 0,
	data_sel___release_mem__send_32_bit_low = 1,
	data_sel___release_mem__send_64_bit_data = 2,
	data_sel___release_mem__send_gpu_घड़ी_counter = 3,
	data_sel___release_mem__send_cp_perfcounter_hi_lo = 4,
	data_sel___release_mem__store_gds_data_to_memory = 5
पूर्ण;

काष्ठा pm4__release_mem अणु
	जोड़ अणु
		जोड़ PM4_MES_TYPE_3_HEADER header;	/*header */
		अचिन्हित पूर्णांक ordinal1;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक event_type:6;
			अचिन्हित पूर्णांक reserved1:2;
			क्रमागत _RELEASE_MEM_event_index_क्रमागत event_index:4;
			अचिन्हित पूर्णांक tcl1_vol_action_ena:1;
			अचिन्हित पूर्णांक tc_vol_action_ena:1;
			अचिन्हित पूर्णांक reserved2:1;
			अचिन्हित पूर्णांक tc_wb_action_ena:1;
			अचिन्हित पूर्णांक tcl1_action_ena:1;
			अचिन्हित पूर्णांक tc_action_ena:1;
			अचिन्हित पूर्णांक reserved3:6;
			अचिन्हित पूर्णांक atc:1;
			क्रमागत _RELEASE_MEM_cache_policy_क्रमागत cache_policy:2;
			अचिन्हित पूर्णांक reserved4:5;
		पूर्ण bitfields2;
		अचिन्हित पूर्णांक ordinal2;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक reserved5:16;
			क्रमागत _RELEASE_MEM_dst_sel_क्रमागत dst_sel:2;
			अचिन्हित पूर्णांक reserved6:6;
			क्रमागत _RELEASE_MEM_पूर्णांक_sel_क्रमागत पूर्णांक_sel:3;
			अचिन्हित पूर्णांक reserved7:2;
			क्रमागत _RELEASE_MEM_data_sel_क्रमागत data_sel:3;
		पूर्ण bitfields3;
		अचिन्हित पूर्णांक ordinal3;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक reserved8:2;
			अचिन्हित पूर्णांक address_lo_32b:30;
		पूर्ण bitfields4;
		काष्ठा अणु
			अचिन्हित पूर्णांक reserved9:3;
			अचिन्हित पूर्णांक address_lo_64b:29;
		पूर्ण bitfields5;
		अचिन्हित पूर्णांक ordinal4;
	पूर्ण;

	अचिन्हित पूर्णांक address_hi;

	अचिन्हित पूर्णांक data_lo;

	अचिन्हित पूर्णांक data_hi;

पूर्ण;
#पूर्ण_अगर


/*--------------------_SET_CONFIG_REG-------------------- */

#अगर_अघोषित _PM4__SET_CONFIG_REG_DEFINED
#घोषणा _PM4__SET_CONFIG_REG_DEFINED

काष्ठा pm4__set_config_reg अणु
	जोड़ अणु
		जोड़ PM4_MES_TYPE_3_HEADER header;	/*header */
		अचिन्हित पूर्णांक ordinal1;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक reg_offset:16;
			अचिन्हित पूर्णांक reserved1:7;
			अचिन्हित पूर्णांक vmid_shअगरt:5;
			अचिन्हित पूर्णांक insert_vmid:1;
			अचिन्हित पूर्णांक reserved2:3;
		पूर्ण bitfields2;
		अचिन्हित पूर्णांक ordinal2;
	पूर्ण;

	अचिन्हित पूर्णांक reg_data[1];	/*1..N of these fields */

पूर्ण;
#पूर्ण_अगर

/*--------------------_WAIT_REG_MEM-------------------- */

#अगर_अघोषित _PM4__WAIT_REG_MEM_DEFINED
#घोषणा _PM4__WAIT_REG_MEM_DEFINED
क्रमागत _WAIT_REG_MEM_function_क्रमागत अणु
	function___रुको_reg_mem__always_pass = 0,
	function___रुको_reg_mem__less_than_ref_value = 1,
	function___रुको_reg_mem__less_than_equal_to_the_ref_value = 2,
	function___रुको_reg_mem__equal_to_the_reference_value = 3,
	function___रुको_reg_mem__not_equal_reference_value = 4,
	function___रुको_reg_mem__greater_than_or_equal_reference_value = 5,
	function___रुको_reg_mem__greater_than_reference_value = 6,
	function___रुको_reg_mem__reserved = 7
पूर्ण;

क्रमागत _WAIT_REG_MEM_mem_space_क्रमागत अणु
	mem_space___रुको_reg_mem__रेजिस्टर_space = 0,
	mem_space___रुको_reg_mem__memory_space = 1
पूर्ण;

क्रमागत _WAIT_REG_MEM_operation_क्रमागत अणु
	operation___रुको_reg_mem__रुको_reg_mem = 0,
	operation___रुको_reg_mem__wr_रुको_wr_reg = 1
पूर्ण;

काष्ठा pm4__रुको_reg_mem अणु
	जोड़ अणु
		जोड़ PM4_MES_TYPE_3_HEADER header;	/*header */
		अचिन्हित पूर्णांक ordinal1;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			क्रमागत _WAIT_REG_MEM_function_क्रमागत function:3;
			अचिन्हित पूर्णांक reserved1:1;
			क्रमागत _WAIT_REG_MEM_mem_space_क्रमागत mem_space:2;
			क्रमागत _WAIT_REG_MEM_operation_क्रमागत operation:2;
			अचिन्हित पूर्णांक reserved2:24;
		पूर्ण bitfields2;
		अचिन्हित पूर्णांक ordinal2;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक reserved3:2;
			अचिन्हित पूर्णांक memory_poll_addr_lo:30;
		पूर्ण bitfields3;
		काष्ठा अणु
			अचिन्हित पूर्णांक रेजिस्टर_poll_addr:16;
			अचिन्हित पूर्णांक reserved4:16;
		पूर्ण bitfields4;
		काष्ठा अणु
			अचिन्हित पूर्णांक रेजिस्टर_ग_लिखो_addr:16;
			अचिन्हित पूर्णांक reserved5:16;
		पूर्ण bitfields5;
		अचिन्हित पूर्णांक ordinal3;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक poll_address_hi:16;
			अचिन्हित पूर्णांक reserved6:16;
		पूर्ण bitfields6;
		काष्ठा अणु
			अचिन्हित पूर्णांक रेजिस्टर_ग_लिखो_addr:16;
			अचिन्हित पूर्णांक reserved7:16;
		पूर्ण bitfields7;
		अचिन्हित पूर्णांक ordinal4;
	पूर्ण;

	अचिन्हित पूर्णांक reference;

	अचिन्हित पूर्णांक mask;

	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक poll_पूर्णांकerval:16;
			अचिन्हित पूर्णांक reserved8:16;
		पूर्ण bitfields8;
		अचिन्हित पूर्णांक ordinal7;
	पूर्ण;

पूर्ण;
#पूर्ण_अगर


#पूर्ण_अगर /* KFD_PM4_HEADERS_DIQ_H_ */
