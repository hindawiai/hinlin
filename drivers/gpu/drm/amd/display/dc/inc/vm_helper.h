<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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

#अगर_अघोषित DC_INC_VM_HELPER_H_
#घोषणा DC_INC_VM_HELPER_H_

#समावेश "dc_types.h"

#घोषणा MAX_HUBP 6

काष्ठा vmid_usage अणु
	पूर्णांक vmid_usage[2];
पूर्ण;

काष्ठा vm_helper अणु
	अचिन्हित पूर्णांक num_vmid;
	काष्ठा vmid_usage hubp_vmid_usage[MAX_HUBP];
पूर्ण;

व्योम vm_helper_mark_vmid_used(काष्ठा vm_helper *vm_helper, अचिन्हित पूर्णांक pos, uपूर्णांक8_t hubp_idx);

व्योम vm_helper_init(
	काष्ठा vm_helper *vm_helper,
	अचिन्हित पूर्णांक num_vmid);

#पूर्ण_अगर /* DC_INC_VM_HELPER_H_ */
