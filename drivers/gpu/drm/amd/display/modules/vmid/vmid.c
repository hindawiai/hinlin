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

#समावेश "mod_vmid.h"

काष्ठा core_vmid अणु
	काष्ठा mod_vmid खुला;
	काष्ठा dc *dc;

	अचिन्हित पूर्णांक num_vmid;
	अचिन्हित पूर्णांक num_vmids_available;
	uपूर्णांक64_t ptb_asचिन्हित_to_vmid[MAX_VMID];
	काष्ठा dc_भव_addr_space_config base_config;
पूर्ण;

#घोषणा MOD_VMID_TO_CORE(mod_vmid)\
		container_of(mod_vmid, काष्ठा core_vmid, खुला)

अटल व्योम add_ptb_to_table(काष्ठा core_vmid *core_vmid, अचिन्हित पूर्णांक vmid, uपूर्णांक64_t ptb)
अणु
	अगर (vmid < MAX_VMID) अणु
		core_vmid->ptb_asचिन्हित_to_vmid[vmid] = ptb;
		core_vmid->num_vmids_available--;
	पूर्ण
पूर्ण

अटल व्योम clear_entry_from_vmid_table(काष्ठा core_vmid *core_vmid, अचिन्हित पूर्णांक vmid)
अणु
	अगर (vmid < MAX_VMID) अणु
		core_vmid->ptb_asचिन्हित_to_vmid[vmid] = 0;
		core_vmid->num_vmids_available++;
	पूर्ण
पूर्ण

अटल व्योम evict_vmids(काष्ठा core_vmid *core_vmid)
अणु
	पूर्णांक i;
	uपूर्णांक16_t ord = dc_get_vmid_use_vector(core_vmid->dc);

	// At this poपूर्णांक any positions with value 0 are unused vmids, evict them
	क्रम (i = 1; i < core_vmid->num_vmid; i++) अणु
		अगर (!(ord & (1u << i)))
			clear_entry_from_vmid_table(core_vmid, i);
	पूर्ण
पूर्ण

// Return value of -1 indicates vmid table unitialized or ptb dne in the table
अटल पूर्णांक get_existing_vmid_क्रम_ptb(काष्ठा core_vmid *core_vmid, uपूर्णांक64_t ptb)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < core_vmid->num_vmid; i++) अणु
		अगर (core_vmid->ptb_asचिन्हित_to_vmid[i] == ptb)
			वापस i;
	पूर्ण

	वापस -1;
पूर्ण

// Expected to be called only when there's an available vmid
अटल पूर्णांक get_next_available_vmid(काष्ठा core_vmid *core_vmid)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < core_vmid->num_vmid; i++) अणु
		अगर (core_vmid->ptb_asचिन्हित_to_vmid[i] == 0)
			वापस i;
	पूर्ण

	वापस -1;
पूर्ण

uपूर्णांक8_t mod_vmid_get_क्रम_ptb(काष्ठा mod_vmid *mod_vmid, uपूर्णांक64_t ptb)
अणु
	काष्ठा core_vmid *core_vmid = MOD_VMID_TO_CORE(mod_vmid);
	पूर्णांक vmid = 0;

	// Physical address माला_लो vmid 0
	अगर (ptb == 0)
		वापस 0;

	vmid = get_existing_vmid_क्रम_ptb(core_vmid, ptb);

	अगर (vmid == -1) अणु
		काष्ठा dc_भव_addr_space_config va_config = core_vmid->base_config;

		va_config.page_table_base_addr = ptb;

		अगर (core_vmid->num_vmids_available == 0)
			evict_vmids(core_vmid);

		vmid = get_next_available_vmid(core_vmid);
		अगर (vmid != -1) अणु
			add_ptb_to_table(core_vmid, vmid, ptb);

			dc_setup_vm_context(core_vmid->dc, &va_config, vmid);
		पूर्ण अन्यथा
			ASSERT(0);
	पूर्ण

	वापस vmid;
पूर्ण

व्योम mod_vmid_reset(काष्ठा mod_vmid *mod_vmid)
अणु
	काष्ठा core_vmid *core_vmid = MOD_VMID_TO_CORE(mod_vmid);

	core_vmid->num_vmids_available = core_vmid->num_vmid - 1;
	स_रखो(core_vmid->ptb_asचिन्हित_to_vmid, 0, माप(core_vmid->ptb_asचिन्हित_to_vmid[0]) * MAX_VMID);
पूर्ण

काष्ठा mod_vmid *mod_vmid_create(
		काष्ठा dc *dc,
		अचिन्हित पूर्णांक num_vmid,
		काष्ठा dc_भव_addr_space_config *va_config)
अणु
	काष्ठा core_vmid *core_vmid;

	अगर (num_vmid <= 1)
		जाओ fail_no_vm_ctx;

	अगर (dc == शून्य)
		जाओ fail_dc_null;

	core_vmid = kzalloc(माप(काष्ठा core_vmid), GFP_KERNEL);

	अगर (core_vmid == शून्य)
		जाओ fail_alloc_context;

	core_vmid->dc = dc;
	core_vmid->num_vmid = num_vmid;
	core_vmid->num_vmids_available = num_vmid - 1;
	core_vmid->base_config = *va_config;

	स_रखो(core_vmid->ptb_asचिन्हित_to_vmid, 0, माप(core_vmid->ptb_asचिन्हित_to_vmid[0]) * MAX_VMID);

	वापस &core_vmid->खुला;

fail_no_vm_ctx:
fail_alloc_context:
fail_dc_null:
	वापस शून्य;
पूर्ण

व्योम mod_vmid_destroy(काष्ठा mod_vmid *mod_vmid)
अणु
	अगर (mod_vmid != शून्य) अणु
		काष्ठा core_vmid *core_vmid = MOD_VMID_TO_CORE(mod_vmid);

		kमुक्त(core_vmid);
	पूर्ण
पूर्ण
