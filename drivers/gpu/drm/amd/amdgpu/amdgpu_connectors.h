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

#अगर_अघोषित __AMDGPU_CONNECTORS_H__
#घोषणा __AMDGPU_CONNECTORS_H__

काष्ठा edid *amdgpu_connector_edid(काष्ठा drm_connector *connector);
व्योम amdgpu_connector_hotplug(काष्ठा drm_connector *connector);
पूर्णांक amdgpu_connector_get_monitor_bpc(काष्ठा drm_connector *connector);
u16 amdgpu_connector_encoder_get_dp_bridge_encoder_id(काष्ठा drm_connector *connector);
bool amdgpu_connector_is_dp12_capable(काष्ठा drm_connector *connector);
व्योम
amdgpu_connector_add(काष्ठा amdgpu_device *adev,
		      uपूर्णांक32_t connector_id,
		      uपूर्णांक32_t supported_device,
		      पूर्णांक connector_type,
		      काष्ठा amdgpu_i2c_bus_rec *i2c_bus,
		      uपूर्णांक16_t connector_object_id,
		      काष्ठा amdgpu_hpd *hpd,
		      काष्ठा amdgpu_router *router);

#पूर्ण_अगर
