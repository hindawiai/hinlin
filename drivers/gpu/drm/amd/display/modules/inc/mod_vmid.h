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

#अगर_अघोषित MOD_VMID_H_
#घोषणा MOD_VMID_H_

#घोषणा MAX_VMID 16

#समावेश "dc.h"

काष्ठा mod_vmid अणु
	पूर्णांक dummy;
पूर्ण;

uपूर्णांक8_t mod_vmid_get_क्रम_ptb(काष्ठा mod_vmid *mod_vmid, uपूर्णांक64_t ptb);
व्योम mod_vmid_reset(काष्ठा mod_vmid *mod_vmid);
काष्ठा mod_vmid *mod_vmid_create(
		काष्ठा dc *dc,
		अचिन्हित पूर्णांक num_vmid,
		काष्ठा dc_भव_addr_space_config *va_config);

व्योम mod_vmid_destroy(काष्ठा mod_vmid *mod_vmid);

#पूर्ण_अगर /* MOD_VMID_H_ */
