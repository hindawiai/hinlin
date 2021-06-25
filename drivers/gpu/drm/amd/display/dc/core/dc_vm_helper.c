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

#समावेश "vm_helper.h"
#समावेश "dc.h"

व्योम vm_helper_mark_vmid_used(काष्ठा vm_helper *vm_helper, अचिन्हित पूर्णांक pos, uपूर्णांक8_t hubp_idx)
अणु
	काष्ठा vmid_usage vmids = vm_helper->hubp_vmid_usage[hubp_idx];

	vmids.vmid_usage[0] = vmids.vmid_usage[1];
	vmids.vmid_usage[1] = 1 << pos;
पूर्ण

पूर्णांक dc_setup_प्रणाली_context(काष्ठा dc *dc, काष्ठा dc_phy_addr_space_config *pa_config)
अणु
	पूर्णांक num_vmids = 0;

	/* Call HWSS to setup HUBBUB क्रम address config */
	अगर (dc->hwss.init_sys_ctx) अणु
		num_vmids = dc->hwss.init_sys_ctx(dc->hwseq, dc, pa_config);

		/* Pre-init प्रणाली aperture start/end क्रम all HUBP instances (अगर not gating?)
		 * or cache प्रणाली aperture अगर using घातer gating
		 */
		स_नकल(&dc->vm_pa_config, pa_config, माप(काष्ठा dc_phy_addr_space_config));
		dc->vm_pa_config.valid = true;
	पूर्ण

	वापस num_vmids;
पूर्ण

व्योम dc_setup_vm_context(काष्ठा dc *dc, काष्ठा dc_भव_addr_space_config *va_config, पूर्णांक vmid)
अणु
	dc->hwss.init_vm_ctx(dc->hwseq, dc, va_config, vmid);
पूर्ण

पूर्णांक dc_get_vmid_use_vector(काष्ठा dc *dc)
अणु
	पूर्णांक i;
	पूर्णांक in_use = 0;

	क्रम (i = 0; i < MAX_HUBP; i++)
		in_use |= dc->vm_helper->hubp_vmid_usage[i].vmid_usage[0]
			| dc->vm_helper->hubp_vmid_usage[i].vmid_usage[1];
	वापस in_use;
पूर्ण

व्योम vm_helper_init(काष्ठा vm_helper *vm_helper, अचिन्हित पूर्णांक num_vmid)
अणु
	vm_helper->num_vmid = num_vmid;

	स_रखो(vm_helper->hubp_vmid_usage, 0, माप(vm_helper->hubp_vmid_usage[0]) * MAX_HUBP);
पूर्ण
