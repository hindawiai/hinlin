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
 */

#अगर_अघोषित __MXGPU_VI_H__
#घोषणा __MXGPU_VI_H__

#घोषणा VI_MAILBOX_TIMEDOUT	12000
#घोषणा VI_MAILBOX_RESET_TIME	12

/* VI mailbox messages request */
क्रमागत idh_request अणु
	IDH_REQ_GPU_INIT_ACCESS	= 1,
	IDH_REL_GPU_INIT_ACCESS,
	IDH_REQ_GPU_FINI_ACCESS,
	IDH_REL_GPU_FINI_ACCESS,
	IDH_REQ_GPU_RESET_ACCESS,

	IDH_LOG_VF_ERROR       = 200,
पूर्ण;

/* VI mailbox messages data */
क्रमागत idh_event अणु
	IDH_CLR_MSG_BUF = 0,
	IDH_READY_TO_ACCESS_GPU,
	IDH_FLR_NOTIFICATION,
	IDH_FLR_NOTIFICATION_CMPL,

	IDH_TEXT_MESSAGE = 255
पूर्ण;

बाह्य स्थिर काष्ठा amdgpu_virt_ops xgpu_vi_virt_ops;

व्योम xgpu_vi_init_golden_रेजिस्टरs(काष्ठा amdgpu_device *adev);
व्योम xgpu_vi_mailbox_set_irq_funcs(काष्ठा amdgpu_device *adev);
पूर्णांक xgpu_vi_mailbox_add_irq_id(काष्ठा amdgpu_device *adev);
पूर्णांक xgpu_vi_mailbox_get_irq(काष्ठा amdgpu_device *adev);
व्योम xgpu_vi_mailbox_put_irq(काष्ठा amdgpu_device *adev);

#पूर्ण_अगर
