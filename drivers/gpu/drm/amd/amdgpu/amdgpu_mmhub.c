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

#समावेश "amdgpu.h"
#समावेश "amdgpu_ras.h"

पूर्णांक amdgpu_mmhub_ras_late_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;
	काष्ठा ras_ih_अगर ih_info = अणु
		.cb = शून्य,
	पूर्ण;
	काष्ठा ras_fs_अगर fs_info = अणु
		.sysfs_name = "mmhub_err_count",
	पूर्ण;

	अगर (!adev->mmhub.ras_अगर) अणु
		adev->mmhub.ras_अगर = kदो_स्मृति(माप(काष्ठा ras_common_अगर), GFP_KERNEL);
		अगर (!adev->mmhub.ras_अगर)
			वापस -ENOMEM;
		adev->mmhub.ras_अगर->block = AMDGPU_RAS_BLOCK__MMHUB;
		adev->mmhub.ras_अगर->type = AMDGPU_RAS_ERROR__MULTI_UNCORRECTABLE;
		adev->mmhub.ras_अगर->sub_block_index = 0;
		म_नकल(adev->mmhub.ras_अगर->name, "mmhub");
	पूर्ण
	ih_info.head = fs_info.head = *adev->mmhub.ras_अगर;
	r = amdgpu_ras_late_init(adev, adev->mmhub.ras_अगर,
				 &fs_info, &ih_info);
	अगर (r || !amdgpu_ras_is_supported(adev, adev->mmhub.ras_अगर->block)) अणु
		kमुक्त(adev->mmhub.ras_अगर);
		adev->mmhub.ras_अगर = शून्य;
	पूर्ण

	वापस r;
पूर्ण

व्योम amdgpu_mmhub_ras_fini(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_ras_is_supported(adev, AMDGPU_RAS_BLOCK__MMHUB) &&
			adev->mmhub.ras_अगर) अणु
		काष्ठा ras_common_अगर *ras_अगर = adev->mmhub.ras_अगर;
		काष्ठा ras_ih_अगर ih_info = अणु
			.cb = शून्य,
		पूर्ण;

		amdgpu_ras_late_fini(adev, ras_अगर, &ih_info);
		kमुक्त(ras_अगर);
	पूर्ण
पूर्ण
