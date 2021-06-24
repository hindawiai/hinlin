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

#अगर_अघोषित AMDGPU_DM_AMDGPU_DM_HDCP_H_
#घोषणा AMDGPU_DM_AMDGPU_DM_HDCP_H_

#समावेश "mod_hdcp.h"
#समावेश "hdcp.h"
#समावेश "dc.h"
#समावेश "dm_cp_psp.h"
#समावेश "amdgpu.h"

काष्ठा mod_hdcp;
काष्ठा mod_hdcp_link;
काष्ठा mod_hdcp_display;
काष्ठा cp_psp;

काष्ठा hdcp_workqueue अणु
	काष्ठा work_काष्ठा cpirq_work;
	काष्ठा work_काष्ठा property_update_work;
	काष्ठा delayed_work callback_dwork;
	काष्ठा delayed_work watchकरोg_समयr_dwork;
	काष्ठा delayed_work property_validate_dwork;
	काष्ठा amdgpu_dm_connector *aconnector;
	काष्ठा mutex mutex;

	काष्ठा mod_hdcp hdcp;
	काष्ठा mod_hdcp_output output;
	काष्ठा mod_hdcp_display display;
	काष्ठा mod_hdcp_link link;

	क्रमागत mod_hdcp_encryption_status encryption_status;
	uपूर्णांक8_t max_link;

	uपूर्णांक8_t *srm;
	uपूर्णांक8_t *srm_temp;
	uपूर्णांक32_t srm_version;
	uपूर्णांक32_t srm_size;
	काष्ठा bin_attribute attr;
पूर्ण;

व्योम hdcp_update_display(काष्ठा hdcp_workqueue *hdcp_work,
			 अचिन्हित पूर्णांक link_index,
			 काष्ठा amdgpu_dm_connector *aconnector,
			 uपूर्णांक8_t content_type,
			 bool enable_encryption);

व्योम hdcp_reset_display(काष्ठा hdcp_workqueue *work, अचिन्हित पूर्णांक link_index);
व्योम hdcp_handle_cpirq(काष्ठा hdcp_workqueue *work, अचिन्हित पूर्णांक link_index);
व्योम hdcp_destroy(काष्ठा kobject *kobj, काष्ठा hdcp_workqueue *work);

काष्ठा hdcp_workqueue *hdcp_create_workqueue(काष्ठा amdgpu_device *adev, काष्ठा cp_psp *cp_psp, काष्ठा dc *dc);

#पूर्ण_अगर /* AMDGPU_DM_AMDGPU_DM_HDCP_H_ */
