<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/tee.h>
#समावेश <linux/tee_drv.h>
#समावेश <linux/psp-tee.h>
#समावेश <linux/slab.h>
#समावेश <linux/psp-sev.h>
#समावेश "amdtee_if.h"
#समावेश "amdtee_private.h"

अटल पूर्णांक tee_params_to_amd_params(काष्ठा tee_param *tee, u32 count,
				    काष्ठा tee_operation *amd)
अणु
	पूर्णांक i, ret = 0;
	u32 type;

	अगर (!count)
		वापस 0;

	अगर (!tee || !amd || count > TEE_MAX_PARAMS)
		वापस -EINVAL;

	amd->param_types = 0;
	क्रम (i = 0; i < count; i++) अणु
		/* AMD TEE करोes not support meta parameter */
		अगर (tee[i].attr > TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT)
			वापस -EINVAL;

		amd->param_types |= ((tee[i].attr & 0xF) << i * 4);
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		type = TEE_PARAM_TYPE_GET(amd->param_types, i);
		pr_debug("%s: type[%d] = 0x%x\n", __func__, i, type);

		अगर (type == TEE_OP_PARAM_TYPE_INVALID)
			वापस -EINVAL;

		अगर (type == TEE_OP_PARAM_TYPE_NONE)
			जारी;

		/* It is assumed that all values are within 2^32-1 */
		अगर (type > TEE_OP_PARAM_TYPE_VALUE_INOUT) अणु
			u32 buf_id = get_buffer_id(tee[i].u.memref.shm);

			amd->params[i].mref.buf_id = buf_id;
			amd->params[i].mref.offset = tee[i].u.memref.shm_offs;
			amd->params[i].mref.size = tee[i].u.memref.size;
			pr_debug("%s: bufid[%d] = 0x%x, offset[%d] = 0x%x, size[%d] = 0x%x\n",
				 __func__,
				 i, amd->params[i].mref.buf_id,
				 i, amd->params[i].mref.offset,
				 i, amd->params[i].mref.size);
		पूर्ण अन्यथा अणु
			अगर (tee[i].u.value.c)
				pr_warn("%s: Discarding value c", __func__);

			amd->params[i].val.a = tee[i].u.value.a;
			amd->params[i].val.b = tee[i].u.value.b;
			pr_debug("%s: a[%d] = 0x%x, b[%d] = 0x%x\n", __func__,
				 i, amd->params[i].val.a,
				 i, amd->params[i].val.b);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक amd_params_to_tee_params(काष्ठा tee_param *tee, u32 count,
				    काष्ठा tee_operation *amd)
अणु
	पूर्णांक i, ret = 0;
	u32 type;

	अगर (!count)
		वापस 0;

	अगर (!tee || !amd || count > TEE_MAX_PARAMS)
		वापस -EINVAL;

	/* Assumes amd->param_types is valid */
	क्रम (i = 0; i < count; i++) अणु
		type = TEE_PARAM_TYPE_GET(amd->param_types, i);
		pr_debug("%s: type[%d] = 0x%x\n", __func__, i, type);

		अगर (type == TEE_OP_PARAM_TYPE_INVALID ||
		    type > TEE_OP_PARAM_TYPE_MEMREF_INOUT)
			वापस -EINVAL;

		अगर (type == TEE_OP_PARAM_TYPE_NONE ||
		    type == TEE_OP_PARAM_TYPE_VALUE_INPUT ||
		    type == TEE_OP_PARAM_TYPE_MEMREF_INPUT)
			जारी;

		/*
		 * It is assumed that buf_id reमुख्यs unchanged क्रम
		 * both खोलो_session and invoke_cmd call
		 */
		अगर (type > TEE_OP_PARAM_TYPE_MEMREF_INPUT) अणु
			tee[i].u.memref.shm_offs = amd->params[i].mref.offset;
			tee[i].u.memref.size = amd->params[i].mref.size;
			pr_debug("%s: bufid[%d] = 0x%x, offset[%d] = 0x%x, size[%d] = 0x%x\n",
				 __func__,
				 i, amd->params[i].mref.buf_id,
				 i, amd->params[i].mref.offset,
				 i, amd->params[i].mref.size);
		पूर्ण अन्यथा अणु
			/* field 'c' not supported by AMD TEE */
			tee[i].u.value.a = amd->params[i].val.a;
			tee[i].u.value.b = amd->params[i].val.b;
			tee[i].u.value.c = 0;
			pr_debug("%s: a[%d] = 0x%x, b[%d] = 0x%x\n",
				 __func__,
				 i, amd->params[i].val.a,
				 i, amd->params[i].val.b);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल DEFINE_MUTEX(ta_refcount_mutex);
अटल काष्ठा list_head ta_list = LIST_HEAD_INIT(ta_list);

अटल u32 get_ta_refcount(u32 ta_handle)
अणु
	काष्ठा amdtee_ta_data *ta_data;
	u32 count = 0;

	/* Caller must hold a mutex */
	list_क्रम_each_entry(ta_data, &ta_list, list_node)
		अगर (ta_data->ta_handle == ta_handle)
			वापस ++ta_data->refcount;

	ta_data = kzalloc(माप(*ta_data), GFP_KERNEL);
	अगर (ta_data) अणु
		ta_data->ta_handle = ta_handle;
		ta_data->refcount = 1;
		count = ta_data->refcount;
		list_add(&ta_data->list_node, &ta_list);
	पूर्ण

	वापस count;
पूर्ण

अटल u32 put_ta_refcount(u32 ta_handle)
अणु
	काष्ठा amdtee_ta_data *ta_data;
	u32 count = 0;

	/* Caller must hold a mutex */
	list_क्रम_each_entry(ta_data, &ta_list, list_node)
		अगर (ta_data->ta_handle == ta_handle) अणु
			count = --ta_data->refcount;
			अगर (count == 0) अणु
				list_del(&ta_data->list_node);
				kमुक्त(ta_data);
				अवरोध;
			पूर्ण
		पूर्ण

	वापस count;
पूर्ण

पूर्णांक handle_unload_ta(u32 ta_handle)
अणु
	काष्ठा tee_cmd_unload_ta cmd = अणु0पूर्ण;
	u32 status, count;
	पूर्णांक ret;

	अगर (!ta_handle)
		वापस -EINVAL;

	mutex_lock(&ta_refcount_mutex);

	count = put_ta_refcount(ta_handle);

	अगर (count) अणु
		pr_debug("unload ta: not unloading %u count %u\n",
			 ta_handle, count);
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	cmd.ta_handle = ta_handle;

	ret = psp_tee_process_cmd(TEE_CMD_ID_UNLOAD_TA, (व्योम *)&cmd,
				  माप(cmd), &status);
	अगर (!ret && status != 0) अणु
		pr_err("unload ta: status = 0x%x\n", status);
		ret = -EBUSY;
	पूर्ण अन्यथा अणु
		pr_debug("unloaded ta handle %u\n", ta_handle);
	पूर्ण

unlock:
	mutex_unlock(&ta_refcount_mutex);
	वापस ret;
पूर्ण

पूर्णांक handle_बंद_session(u32 ta_handle, u32 info)
अणु
	काष्ठा tee_cmd_बंद_session cmd = अणु0पूर्ण;
	u32 status;
	पूर्णांक ret;

	अगर (ta_handle == 0)
		वापस -EINVAL;

	cmd.ta_handle = ta_handle;
	cmd.session_info = info;

	ret = psp_tee_process_cmd(TEE_CMD_ID_CLOSE_SESSION, (व्योम *)&cmd,
				  माप(cmd), &status);
	अगर (!ret && status != 0) अणु
		pr_err("close session: status = 0x%x\n", status);
		ret = -EBUSY;
	पूर्ण

	वापस ret;
पूर्ण

व्योम handle_unmap_shmem(u32 buf_id)
अणु
	काष्ठा tee_cmd_unmap_shared_mem cmd = अणु0पूर्ण;
	u32 status;
	पूर्णांक ret;

	cmd.buf_id = buf_id;

	ret = psp_tee_process_cmd(TEE_CMD_ID_UNMAP_SHARED_MEM, (व्योम *)&cmd,
				  माप(cmd), &status);
	अगर (!ret)
		pr_debug("unmap shared memory: buf_id %u status = 0x%x\n",
			 buf_id, status);
पूर्ण

पूर्णांक handle_invoke_cmd(काष्ठा tee_ioctl_invoke_arg *arg, u32 sinfo,
		      काष्ठा tee_param *p)
अणु
	काष्ठा tee_cmd_invoke_cmd cmd = अणु0पूर्ण;
	पूर्णांक ret;

	अगर (!arg || (!p && arg->num_params))
		वापस -EINVAL;

	arg->ret_origin = TEEC_ORIGIN_COMMS;

	अगर (arg->session == 0) अणु
		arg->ret = TEEC_ERROR_BAD_PARAMETERS;
		वापस -EINVAL;
	पूर्ण

	ret = tee_params_to_amd_params(p, arg->num_params, &cmd.op);
	अगर (ret) अणु
		pr_err("invalid Params. Abort invoke command\n");
		arg->ret = TEEC_ERROR_BAD_PARAMETERS;
		वापस ret;
	पूर्ण

	cmd.ta_handle = get_ta_handle(arg->session);
	cmd.cmd_id = arg->func;
	cmd.session_info = sinfo;

	ret = psp_tee_process_cmd(TEE_CMD_ID_INVOKE_CMD, (व्योम *)&cmd,
				  माप(cmd), &arg->ret);
	अगर (ret) अणु
		arg->ret = TEEC_ERROR_COMMUNICATION;
	पूर्ण अन्यथा अणु
		ret = amd_params_to_tee_params(p, arg->num_params, &cmd.op);
		अगर (unlikely(ret)) अणु
			pr_err("invoke command: failed to copy output\n");
			arg->ret = TEEC_ERROR_GENERIC;
			वापस ret;
		पूर्ण
		arg->ret_origin = cmd.वापस_origin;
		pr_debug("invoke command: RO = 0x%x ret = 0x%x\n",
			 arg->ret_origin, arg->ret);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक handle_map_shmem(u32 count, काष्ठा shmem_desc *start, u32 *buf_id)
अणु
	काष्ठा tee_cmd_map_shared_mem *cmd;
	phys_addr_t paddr;
	पूर्णांक ret, i;
	u32 status;

	अगर (!count || !start || !buf_id)
		वापस -EINVAL;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	/* Size must be page aligned */
	क्रम (i = 0; i < count ; i++) अणु
		अगर (!start[i].kaddr || (start[i].size & (PAGE_SIZE - 1))) अणु
			ret = -EINVAL;
			जाओ मुक्त_cmd;
		पूर्ण

		अगर ((u64)start[i].kaddr & (PAGE_SIZE - 1)) अणु
			pr_err("map shared memory: page unaligned. addr 0x%llx",
			       (u64)start[i].kaddr);
			ret = -EINVAL;
			जाओ मुक्त_cmd;
		पूर्ण
	पूर्ण

	cmd->sg_list.count = count;

	/* Create buffer list */
	क्रम (i = 0; i < count ; i++) अणु
		paddr = __psp_pa(start[i].kaddr);
		cmd->sg_list.buf[i].hi_addr = upper_32_bits(paddr);
		cmd->sg_list.buf[i].low_addr = lower_32_bits(paddr);
		cmd->sg_list.buf[i].size = start[i].size;
		cmd->sg_list.size += cmd->sg_list.buf[i].size;

		pr_debug("buf[%d]:hi addr = 0x%x\n", i,
			 cmd->sg_list.buf[i].hi_addr);
		pr_debug("buf[%d]:low addr = 0x%x\n", i,
			 cmd->sg_list.buf[i].low_addr);
		pr_debug("buf[%d]:size = 0x%x\n", i, cmd->sg_list.buf[i].size);
		pr_debug("list size = 0x%x\n", cmd->sg_list.size);
	पूर्ण

	*buf_id = 0;

	ret = psp_tee_process_cmd(TEE_CMD_ID_MAP_SHARED_MEM, (व्योम *)cmd,
				  माप(*cmd), &status);
	अगर (!ret && !status) अणु
		*buf_id = cmd->buf_id;
		pr_debug("mapped buffer ID = 0x%x\n", *buf_id);
	पूर्ण अन्यथा अणु
		pr_err("map shared memory: status = 0x%x\n", status);
		ret = -ENOMEM;
	पूर्ण

मुक्त_cmd:
	kमुक्त(cmd);

	वापस ret;
पूर्ण

पूर्णांक handle_खोलो_session(काष्ठा tee_ioctl_खोलो_session_arg *arg, u32 *info,
			काष्ठा tee_param *p)
अणु
	काष्ठा tee_cmd_खोलो_session cmd = अणु0पूर्ण;
	पूर्णांक ret;

	अगर (!arg || !info || (!p && arg->num_params))
		वापस -EINVAL;

	arg->ret_origin = TEEC_ORIGIN_COMMS;

	अगर (arg->session == 0) अणु
		arg->ret = TEEC_ERROR_GENERIC;
		वापस -EINVAL;
	पूर्ण

	ret = tee_params_to_amd_params(p, arg->num_params, &cmd.op);
	अगर (ret) अणु
		pr_err("invalid Params. Abort open session\n");
		arg->ret = TEEC_ERROR_BAD_PARAMETERS;
		वापस ret;
	पूर्ण

	cmd.ta_handle = get_ta_handle(arg->session);
	*info = 0;

	ret = psp_tee_process_cmd(TEE_CMD_ID_OPEN_SESSION, (व्योम *)&cmd,
				  माप(cmd), &arg->ret);
	अगर (ret) अणु
		arg->ret = TEEC_ERROR_COMMUNICATION;
	पूर्ण अन्यथा अणु
		ret = amd_params_to_tee_params(p, arg->num_params, &cmd.op);
		अगर (unlikely(ret)) अणु
			pr_err("open session: failed to copy output\n");
			arg->ret = TEEC_ERROR_GENERIC;
			वापस ret;
		पूर्ण
		arg->ret_origin = cmd.वापस_origin;
		*info = cmd.session_info;
		pr_debug("open session: session info = 0x%x\n", *info);
	पूर्ण

	pr_debug("open session: ret = 0x%x RO = 0x%x\n", arg->ret,
		 arg->ret_origin);

	वापस ret;
पूर्ण

पूर्णांक handle_load_ta(व्योम *data, u32 size, काष्ठा tee_ioctl_खोलो_session_arg *arg)
अणु
	काष्ठा tee_cmd_unload_ta unload_cmd = अणुपूर्ण;
	काष्ठा tee_cmd_load_ta load_cmd = अणुपूर्ण;
	phys_addr_t blob;
	पूर्णांक ret;

	अगर (size == 0 || !data || !arg)
		वापस -EINVAL;

	blob = __psp_pa(data);
	अगर (blob & (PAGE_SIZE - 1)) अणु
		pr_err("load TA: page unaligned. blob 0x%llx", blob);
		वापस -EINVAL;
	पूर्ण

	load_cmd.hi_addr = upper_32_bits(blob);
	load_cmd.low_addr = lower_32_bits(blob);
	load_cmd.size = size;

	mutex_lock(&ta_refcount_mutex);

	ret = psp_tee_process_cmd(TEE_CMD_ID_LOAD_TA, (व्योम *)&load_cmd,
				  माप(load_cmd), &arg->ret);
	अगर (ret) अणु
		arg->ret_origin = TEEC_ORIGIN_COMMS;
		arg->ret = TEEC_ERROR_COMMUNICATION;
	पूर्ण अन्यथा अगर (arg->ret == TEEC_SUCCESS) अणु
		ret = get_ta_refcount(load_cmd.ta_handle);
		अगर (!ret) अणु
			arg->ret_origin = TEEC_ORIGIN_COMMS;
			arg->ret = TEEC_ERROR_OUT_OF_MEMORY;

			/* Unload the TA on error */
			unload_cmd.ta_handle = load_cmd.ta_handle;
			psp_tee_process_cmd(TEE_CMD_ID_UNLOAD_TA,
					    (व्योम *)&unload_cmd,
					    माप(unload_cmd), &ret);
		पूर्ण अन्यथा अणु
			set_session_id(load_cmd.ta_handle, 0, &arg->session);
		पूर्ण
	पूर्ण
	mutex_unlock(&ta_refcount_mutex);

	pr_debug("load TA: TA handle = 0x%x, RO = 0x%x, ret = 0x%x\n",
		 load_cmd.ta_handle, arg->ret_origin, arg->ret);

	वापस 0;
पूर्ण
