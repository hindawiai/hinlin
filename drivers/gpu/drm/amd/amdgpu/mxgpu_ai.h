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

#अगर_अघोषित __MXGPU_AI_H__
#घोषणा __MXGPU_AI_H__

#घोषणा AI_MAILBOX_POLL_ACK_TIMEDOUT	500
#घोषणा AI_MAILBOX_POLL_MSG_TIMEDOUT	6000
#घोषणा AI_MAILBOX_POLL_FLR_TIMEDOUT	5000
#घोषणा AI_MAILBOX_POLL_MSG_REP_MAX	11

क्रमागत idh_request अणु
	IDH_REQ_GPU_INIT_ACCESS = 1,
	IDH_REL_GPU_INIT_ACCESS,
	IDH_REQ_GPU_FINI_ACCESS,
	IDH_REL_GPU_FINI_ACCESS,
	IDH_REQ_GPU_RESET_ACCESS,

	IDH_LOG_VF_ERROR       = 200,
पूर्ण;

क्रमागत idh_event अणु
	IDH_CLR_MSG_BUF	= 0,
	IDH_READY_TO_ACCESS_GPU,
	IDH_FLR_NOTIFICATION,
	IDH_FLR_NOTIFICATION_CMPL,
	IDH_SUCCESS,
	IDH_FAIL,
	IDH_QUERY_ALIVE,

	IDH_TEXT_MESSAGE = 255,
पूर्ण;

बाह्य स्थिर काष्ठा amdgpu_virt_ops xgpu_ai_virt_ops;

व्योम xgpu_ai_mailbox_set_irq_funcs(काष्ठा amdgpu_device *adev);
पूर्णांक xgpu_ai_mailbox_add_irq_id(काष्ठा amdgpu_device *adev);
पूर्णांक xgpu_ai_mailbox_get_irq(काष्ठा amdgpu_device *adev);
व्योम xgpu_ai_mailbox_put_irq(काष्ठा amdgpu_device *adev);

#घोषणा AI_MAIBOX_CONTROL_TRN_OFFSET_BYTE SOC15_REG_OFFSET(NBIO, 0, mmBIF_BX_PF0_MAILBOX_CONTROL) * 4
#घोषणा AI_MAIBOX_CONTROL_RCV_OFFSET_BYTE SOC15_REG_OFFSET(NBIO, 0, mmBIF_BX_PF0_MAILBOX_CONTROL) * 4 + 1

#पूर्ण_अगर
