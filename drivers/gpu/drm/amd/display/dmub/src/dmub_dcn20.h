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
 * Authors: AMD
 *
 */

#अगर_अघोषित _DMUB_DCN20_H_
#घोषणा _DMUB_DCN20_H_

#समावेश "../inc/dmub_cmd.h"

काष्ठा dmub_srv;

/* DCN20 रेजिस्टर definitions. */

#घोषणा DMUB_COMMON_REGS() \
	DMUB_SR(DMCUB_CNTL) \
	DMUB_SR(DMCUB_MEM_CNTL) \
	DMUB_SR(DMCUB_SEC_CNTL) \
	DMUB_SR(DMCUB_INBOX1_BASE_ADDRESS) \
	DMUB_SR(DMCUB_INBOX1_SIZE) \
	DMUB_SR(DMCUB_INBOX1_RPTR) \
	DMUB_SR(DMCUB_INBOX1_WPTR) \
	DMUB_SR(DMCUB_OUTBOX0_BASE_ADDRESS) \
	DMUB_SR(DMCUB_OUTBOX0_SIZE) \
	DMUB_SR(DMCUB_OUTBOX0_RPTR) \
	DMUB_SR(DMCUB_OUTBOX0_WPTR) \
	DMUB_SR(DMCUB_OUTBOX1_BASE_ADDRESS) \
	DMUB_SR(DMCUB_OUTBOX1_SIZE) \
	DMUB_SR(DMCUB_OUTBOX1_RPTR) \
	DMUB_SR(DMCUB_OUTBOX1_WPTR) \
	DMUB_SR(DMCUB_REGION3_CW0_OFFSET) \
	DMUB_SR(DMCUB_REGION3_CW1_OFFSET) \
	DMUB_SR(DMCUB_REGION3_CW2_OFFSET) \
	DMUB_SR(DMCUB_REGION3_CW3_OFFSET) \
	DMUB_SR(DMCUB_REGION3_CW4_OFFSET) \
	DMUB_SR(DMCUB_REGION3_CW5_OFFSET) \
	DMUB_SR(DMCUB_REGION3_CW6_OFFSET) \
	DMUB_SR(DMCUB_REGION3_CW7_OFFSET) \
	DMUB_SR(DMCUB_REGION3_CW0_OFFSET_HIGH) \
	DMUB_SR(DMCUB_REGION3_CW1_OFFSET_HIGH) \
	DMUB_SR(DMCUB_REGION3_CW2_OFFSET_HIGH) \
	DMUB_SR(DMCUB_REGION3_CW3_OFFSET_HIGH) \
	DMUB_SR(DMCUB_REGION3_CW4_OFFSET_HIGH) \
	DMUB_SR(DMCUB_REGION3_CW5_OFFSET_HIGH) \
	DMUB_SR(DMCUB_REGION3_CW6_OFFSET_HIGH) \
	DMUB_SR(DMCUB_REGION3_CW7_OFFSET_HIGH) \
	DMUB_SR(DMCUB_REGION3_CW0_BASE_ADDRESS) \
	DMUB_SR(DMCUB_REGION3_CW1_BASE_ADDRESS) \
	DMUB_SR(DMCUB_REGION3_CW2_BASE_ADDRESS) \
	DMUB_SR(DMCUB_REGION3_CW3_BASE_ADDRESS) \
	DMUB_SR(DMCUB_REGION3_CW4_BASE_ADDRESS) \
	DMUB_SR(DMCUB_REGION3_CW5_BASE_ADDRESS) \
	DMUB_SR(DMCUB_REGION3_CW6_BASE_ADDRESS) \
	DMUB_SR(DMCUB_REGION3_CW7_BASE_ADDRESS) \
	DMUB_SR(DMCUB_REGION3_CW0_TOP_ADDRESS) \
	DMUB_SR(DMCUB_REGION3_CW1_TOP_ADDRESS) \
	DMUB_SR(DMCUB_REGION3_CW2_TOP_ADDRESS) \
	DMUB_SR(DMCUB_REGION3_CW3_TOP_ADDRESS) \
	DMUB_SR(DMCUB_REGION3_CW4_TOP_ADDRESS) \
	DMUB_SR(DMCUB_REGION3_CW5_TOP_ADDRESS) \
	DMUB_SR(DMCUB_REGION3_CW6_TOP_ADDRESS) \
	DMUB_SR(DMCUB_REGION3_CW7_TOP_ADDRESS) \
	DMUB_SR(DMCUB_REGION4_OFFSET) \
	DMUB_SR(DMCUB_REGION4_OFFSET_HIGH) \
	DMUB_SR(DMCUB_REGION4_TOP_ADDRESS) \
	DMUB_SR(DMCUB_REGION5_OFFSET) \
	DMUB_SR(DMCUB_REGION5_OFFSET_HIGH) \
	DMUB_SR(DMCUB_REGION5_TOP_ADDRESS) \
	DMUB_SR(DMCUB_SCRATCH0) \
	DMUB_SR(DMCUB_SCRATCH1) \
	DMUB_SR(DMCUB_SCRATCH2) \
	DMUB_SR(DMCUB_SCRATCH3) \
	DMUB_SR(DMCUB_SCRATCH4) \
	DMUB_SR(DMCUB_SCRATCH5) \
	DMUB_SR(DMCUB_SCRATCH6) \
	DMUB_SR(DMCUB_SCRATCH7) \
	DMUB_SR(DMCUB_SCRATCH8) \
	DMUB_SR(DMCUB_SCRATCH9) \
	DMUB_SR(DMCUB_SCRATCH10) \
	DMUB_SR(DMCUB_SCRATCH11) \
	DMUB_SR(DMCUB_SCRATCH12) \
	DMUB_SR(DMCUB_SCRATCH13) \
	DMUB_SR(DMCUB_SCRATCH14) \
	DMUB_SR(DMCUB_SCRATCH15) \
	DMUB_SR(DMCUB_GPINT_DATAIN1) \
	DMUB_SR(CC_DC_PIPE_DIS) \
	DMUB_SR(MMHUBBUB_SOFT_RESET) \
	DMUB_SR(DCN_VM_FB_LOCATION_BASE) \
	DMUB_SR(DCN_VM_FB_OFFSET) \
	DMUB_SR(DMCUB_INTERRUPT_ACK)

#घोषणा DMUB_COMMON_FIELDS() \
	DMUB_SF(DMCUB_CNTL, DMCUB_ENABLE) \
	DMUB_SF(DMCUB_CNTL, DMCUB_SOFT_RESET) \
	DMUB_SF(DMCUB_CNTL, DMCUB_TRACEPORT_EN) \
	DMUB_SF(DMCUB_MEM_CNTL, DMCUB_MEM_READ_SPACE) \
	DMUB_SF(DMCUB_MEM_CNTL, DMCUB_MEM_WRITE_SPACE) \
	DMUB_SF(DMCUB_SEC_CNTL, DMCUB_SEC_RESET) \
	DMUB_SF(DMCUB_SEC_CNTL, DMCUB_MEM_UNIT_ID) \
	DMUB_SF(DMCUB_REGION3_CW0_TOP_ADDRESS, DMCUB_REGION3_CW0_TOP_ADDRESS) \
	DMUB_SF(DMCUB_REGION3_CW0_TOP_ADDRESS, DMCUB_REGION3_CW0_ENABLE) \
	DMUB_SF(DMCUB_REGION3_CW1_TOP_ADDRESS, DMCUB_REGION3_CW1_TOP_ADDRESS) \
	DMUB_SF(DMCUB_REGION3_CW1_TOP_ADDRESS, DMCUB_REGION3_CW1_ENABLE) \
	DMUB_SF(DMCUB_REGION3_CW2_TOP_ADDRESS, DMCUB_REGION3_CW2_TOP_ADDRESS) \
	DMUB_SF(DMCUB_REGION3_CW2_TOP_ADDRESS, DMCUB_REGION3_CW2_ENABLE) \
	DMUB_SF(DMCUB_REGION3_CW3_TOP_ADDRESS, DMCUB_REGION3_CW3_TOP_ADDRESS) \
	DMUB_SF(DMCUB_REGION3_CW3_TOP_ADDRESS, DMCUB_REGION3_CW3_ENABLE) \
	DMUB_SF(DMCUB_REGION3_CW4_TOP_ADDRESS, DMCUB_REGION3_CW4_TOP_ADDRESS) \
	DMUB_SF(DMCUB_REGION3_CW4_TOP_ADDRESS, DMCUB_REGION3_CW4_ENABLE) \
	DMUB_SF(DMCUB_REGION3_CW5_TOP_ADDRESS, DMCUB_REGION3_CW5_TOP_ADDRESS) \
	DMUB_SF(DMCUB_REGION3_CW5_TOP_ADDRESS, DMCUB_REGION3_CW5_ENABLE) \
	DMUB_SF(DMCUB_REGION3_CW6_TOP_ADDRESS, DMCUB_REGION3_CW6_TOP_ADDRESS) \
	DMUB_SF(DMCUB_REGION3_CW6_TOP_ADDRESS, DMCUB_REGION3_CW6_ENABLE) \
	DMUB_SF(DMCUB_REGION3_CW7_TOP_ADDRESS, DMCUB_REGION3_CW7_TOP_ADDRESS) \
	DMUB_SF(DMCUB_REGION3_CW7_TOP_ADDRESS, DMCUB_REGION3_CW7_ENABLE) \
	DMUB_SF(DMCUB_REGION4_TOP_ADDRESS, DMCUB_REGION4_TOP_ADDRESS) \
	DMUB_SF(DMCUB_REGION4_TOP_ADDRESS, DMCUB_REGION4_ENABLE) \
	DMUB_SF(DMCUB_REGION5_TOP_ADDRESS, DMCUB_REGION5_TOP_ADDRESS) \
	DMUB_SF(DMCUB_REGION5_TOP_ADDRESS, DMCUB_REGION5_ENABLE) \
	DMUB_SF(CC_DC_PIPE_DIS, DC_DMCUB_ENABLE) \
	DMUB_SF(MMHUBBUB_SOFT_RESET, DMUIF_SOFT_RESET) \
	DMUB_SF(DCN_VM_FB_LOCATION_BASE, FB_BASE) \
	DMUB_SF(DCN_VM_FB_OFFSET, FB_OFFSET) \
	DMUB_SF(DMCUB_INTERRUPT_ACK, DMCUB_OUTBOX0_READY_INT_ACK)

काष्ठा dmub_srv_common_reg_offset अणु
#घोषणा DMUB_SR(reg) uपूर्णांक32_t reg;
	DMUB_COMMON_REGS()
#अघोषित DMUB_SR
पूर्ण;

काष्ठा dmub_srv_common_reg_shअगरt अणु
#घोषणा DMUB_SF(reg, field) uपूर्णांक8_t reg##__##field;
	DMUB_COMMON_FIELDS()
#अघोषित DMUB_SF
पूर्ण;

काष्ठा dmub_srv_common_reg_mask अणु
#घोषणा DMUB_SF(reg, field) uपूर्णांक32_t reg##__##field;
	DMUB_COMMON_FIELDS()
#अघोषित DMUB_SF
पूर्ण;

काष्ठा dmub_srv_common_regs अणु
	स्थिर काष्ठा dmub_srv_common_reg_offset offset;
	स्थिर काष्ठा dmub_srv_common_reg_mask mask;
	स्थिर काष्ठा dmub_srv_common_reg_shअगरt shअगरt;
पूर्ण;

बाह्य स्थिर काष्ठा dmub_srv_common_regs dmub_srv_dcn20_regs;

/* Hardware functions. */

व्योम dmub_dcn20_init(काष्ठा dmub_srv *dmub);

व्योम dmub_dcn20_reset(काष्ठा dmub_srv *dmub);

व्योम dmub_dcn20_reset_release(काष्ठा dmub_srv *dmub);

व्योम dmub_dcn20_backकरोor_load(काष्ठा dmub_srv *dmub,
			      स्थिर काष्ठा dmub_winकरोw *cw0,
			      स्थिर काष्ठा dmub_winकरोw *cw1);

व्योम dmub_dcn20_setup_winकरोws(काष्ठा dmub_srv *dmub,
			      स्थिर काष्ठा dmub_winकरोw *cw2,
			      स्थिर काष्ठा dmub_winकरोw *cw3,
			      स्थिर काष्ठा dmub_winकरोw *cw4,
			      स्थिर काष्ठा dmub_winकरोw *cw5,
			      स्थिर काष्ठा dmub_winकरोw *cw6);

व्योम dmub_dcn20_setup_mailbox(काष्ठा dmub_srv *dmub,
			      स्थिर काष्ठा dmub_region *inbox1);

uपूर्णांक32_t dmub_dcn20_get_inbox1_rptr(काष्ठा dmub_srv *dmub);

व्योम dmub_dcn20_set_inbox1_wptr(काष्ठा dmub_srv *dmub, uपूर्णांक32_t wptr_offset);

व्योम dmub_dcn20_setup_out_mailbox(काष्ठा dmub_srv *dmub,
			      स्थिर काष्ठा dmub_region *outbox1);

uपूर्णांक32_t dmub_dcn20_get_outbox1_wptr(काष्ठा dmub_srv *dmub);

व्योम dmub_dcn20_set_outbox1_rptr(काष्ठा dmub_srv *dmub, uपूर्णांक32_t rptr_offset);

व्योम dmub_dcn20_setup_outbox0(काष्ठा dmub_srv *dmub,
			      स्थिर काष्ठा dmub_region *outbox0);

uपूर्णांक32_t dmub_dcn20_get_outbox0_wptr(काष्ठा dmub_srv *dmub);

व्योम dmub_dcn20_set_outbox0_rptr(काष्ठा dmub_srv *dmub, uपूर्णांक32_t rptr_offset);

bool dmub_dcn20_is_hw_init(काष्ठा dmub_srv *dmub);

bool dmub_dcn20_is_supported(काष्ठा dmub_srv *dmub);

व्योम dmub_dcn20_set_gpपूर्णांक(काष्ठा dmub_srv *dmub,
			  जोड़ dmub_gpपूर्णांक_data_रेजिस्टर reg);

bool dmub_dcn20_is_gpपूर्णांक_acked(काष्ठा dmub_srv *dmub,
			       जोड़ dmub_gpपूर्णांक_data_रेजिस्टर reg);

uपूर्णांक32_t dmub_dcn20_get_gpपूर्णांक_response(काष्ठा dmub_srv *dmub);

व्योम dmub_dcn20_enable_dmub_boot_options(काष्ठा dmub_srv *dmub);

व्योम dmub_dcn20_skip_dmub_panel_घातer_sequence(काष्ठा dmub_srv *dmub, bool skip);

जोड़ dmub_fw_boot_status dmub_dcn20_get_fw_boot_status(काष्ठा dmub_srv *dmub);

bool dmub_dcn20_use_cached_inbox(काष्ठा dmub_srv *dmub);

bool dmub_dcn20_use_cached_trace_buffer(काष्ठा dmub_srv *dmub);

#पूर्ण_अगर /* _DMUB_DCN20_H_ */
