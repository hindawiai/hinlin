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

#अगर_अघोषित __AMDGPU_I2C_H__
#घोषणा __AMDGPU_I2C_H__

काष्ठा amdgpu_i2c_chan *amdgpu_i2c_create(काष्ठा drm_device *dev,
					  स्थिर काष्ठा amdgpu_i2c_bus_rec *rec,
					  स्थिर अक्षर *name);
व्योम amdgpu_i2c_destroy(काष्ठा amdgpu_i2c_chan *i2c);
व्योम amdgpu_i2c_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_i2c_fini(काष्ठा amdgpu_device *adev);
व्योम amdgpu_i2c_add(काष्ठा amdgpu_device *adev,
		    स्थिर काष्ठा amdgpu_i2c_bus_rec *rec,
		    स्थिर अक्षर *name);
काष्ठा amdgpu_i2c_chan *
amdgpu_i2c_lookup(काष्ठा amdgpu_device *adev,
		  स्थिर काष्ठा amdgpu_i2c_bus_rec *i2c_bus);
व्योम
amdgpu_i2c_router_select_ddc_port(स्थिर काष्ठा amdgpu_connector *connector);
व्योम
amdgpu_i2c_router_select_cd_port(स्थिर काष्ठा amdgpu_connector *connector);

#पूर्ण_अगर
