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
 *
 * Authors: Christian Kथघnig
 */
#अगर_अघोषित __AMDGPU_MN_H__
#घोषणा __AMDGPU_MN_H__

#समावेश <linux/types.h>
#समावेश <linux/hmm.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पूर्णांकerval_tree.h>

#अगर defined(CONFIG_HMM_MIRROR)
पूर्णांक amdgpu_mn_रेजिस्टर(काष्ठा amdgpu_bo *bo, अचिन्हित दीर्घ addr);
व्योम amdgpu_mn_unरेजिस्टर(काष्ठा amdgpu_bo *bo);
#अन्यथा
अटल अंतरभूत पूर्णांक amdgpu_mn_रेजिस्टर(काष्ठा amdgpu_bo *bo, अचिन्हित दीर्घ addr)
अणु
	DRM_WARN_ONCE("HMM_MIRROR kernel config option is not enabled, "
		      "add CONFIG_ZONE_DEVICE=y in config file to fix this\n");
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत व्योम amdgpu_mn_unरेजिस्टर(काष्ठा amdgpu_bo *bo) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
