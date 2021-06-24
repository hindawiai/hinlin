<शैली गुरु>
/* amdgpu_drv.h -- Private header क्रम amdgpu driver -*- linux-c -*-
 *
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Fremont, Calअगरornia.
 * All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित __AMDGPU_DRV_H__
#घोषणा __AMDGPU_DRV_H__

#समावेश <linux/firmware.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "amd_shared.h"

/* General customization:
 */

#घोषणा DRIVER_AUTHOR		"AMD linux driver team"

#घोषणा DRIVER_NAME		"amdgpu"
#घोषणा DRIVER_DESC		"AMD GPU"
#घोषणा DRIVER_DATE		"20150101"

दीर्घ amdgpu_drm_ioctl(काष्ठा file *filp,
		      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

#पूर्ण_अगर
