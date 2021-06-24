<शैली गुरु>
/*
 * Copyright 2017 Valve Corporation
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
 * Authors: Andres Rodriguez <andresx7@gmail.com>
 */

#अगर_अघोषित __AMDGPU_SCHED_H__
#घोषणा __AMDGPU_SCHED_H__

क्रमागत drm_sched_priority;

काष्ठा drm_device;
काष्ठा drm_file;

पूर्णांक amdgpu_to_sched_priority(पूर्णांक amdgpu_priority,
			     क्रमागत drm_sched_priority *prio);
पूर्णांक amdgpu_sched_ioctl(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *filp);

#पूर्ण_अगर // __AMDGPU_SCHED_H__
