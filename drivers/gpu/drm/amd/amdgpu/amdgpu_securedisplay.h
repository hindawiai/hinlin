<शैली गुरु>
/*
 * Copyright 2021 Advanced Micro Devices, Inc.
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
 *
 */
#अगर_अघोषित _AMDGPU_SECUREDISPLAY_H
#घोषणा _AMDGPU_SECUREDISPLAY_H

#समावेश "amdgpu.h"
#समावेश "ta_secureDisplay_if.h"

व्योम amdgpu_securedisplay_debugfs_init(काष्ठा amdgpu_device *adev);
व्योम psp_securedisplay_parse_resp_status(काष्ठा psp_context *psp,
		क्रमागत ta_securedisplay_status status);
व्योम psp_prep_securedisplay_cmd_buf(काष्ठा psp_context *psp, काष्ठा securedisplay_cmd **cmd,
		क्रमागत ta_securedisplay_command command_id);

#पूर्ण_अगर
