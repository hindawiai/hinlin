<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017-2018, Intel Corporation
 */

#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/पन.स>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/firmware/पूर्णांकel/stratix10-smc.h>
#समावेश <linux/firmware/पूर्णांकel/stratix10-svc-client.h>
#समावेश <linux/types.h>

/**
 * SVC_NUM_DATA_IN_FIFO - number of काष्ठा stratix10_svc_data in the FIFO
 *
 * SVC_NUM_CHANNEL - number of channel supported by service layer driver
 *
 * FPGA_CONFIG_DATA_CLAIM_TIMEOUT_MS - claim back the submitted buffer(s)
 * from the secure world क्रम FPGA manager to reuse, or to मुक्त the buffer(s)
 * when all bit-stream data had be send.
 *
 * FPGA_CONFIG_STATUS_TIMEOUT_SEC - poll the FPGA configuration status,
 * service layer will वापस error to FPGA manager when समयout occurs,
 * समयout is set to 30 seconds (30 * 1000) at Intel Stratix10 SoC.
 */
#घोषणा SVC_NUM_DATA_IN_FIFO			32
#घोषणा SVC_NUM_CHANNEL				2
#घोषणा FPGA_CONFIG_DATA_CLAIM_TIMEOUT_MS	200
#घोषणा FPGA_CONFIG_STATUS_TIMEOUT_SEC		30

/* stratix10 service layer clients */
#घोषणा STRATIX10_RSU				"stratix10-rsu"

प्रकार व्योम (svc_invoke_fn)(अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ,
			     अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ,
			     अचिन्हित दीर्घ, अचिन्हित दीर्घ,
			     काष्ठा arm_smccc_res *);
काष्ठा stratix10_svc_chan;

/**
 * काष्ठा stratix10_svc - svc निजी data
 * @stratix10_svc_rsu: poपूर्णांकer to stratix10 RSU device
 */
काष्ठा stratix10_svc अणु
	काष्ठा platक्रमm_device *stratix10_svc_rsu;
पूर्ण;

/**
 * काष्ठा stratix10_svc_sh_memory - service shared memory काष्ठाure
 * @sync_complete: state क्रम a completion
 * @addr: physical address of shared memory block
 * @size: size of shared memory block
 * @invoke_fn: function to issue secure monitor or hypervisor call
 *
 * This काष्ठा is used to save physical address and size of shared memory
 * block. The shared memory blocked is allocated by secure monitor software
 * at secure world.
 *
 * Service layer driver uses the physical address and size to create a memory
 * pool, then allocates data buffer from that memory pool क्रम service client.
 */
काष्ठा stratix10_svc_sh_memory अणु
	काष्ठा completion sync_complete;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ size;
	svc_invoke_fn *invoke_fn;
पूर्ण;

/**
 * काष्ठा stratix10_svc_data_mem - service memory काष्ठाure
 * @vaddr: भव address
 * @paddr: physical address
 * @size: size of memory
 * @node: link list head node
 *
 * This काष्ठा is used in a list that keeps track of buffers which have
 * been allocated or मुक्तd from the memory pool. Service layer driver also
 * uses this काष्ठा to transfer physical address to भव address.
 */
काष्ठा stratix10_svc_data_mem अणु
	व्योम *vaddr;
	phys_addr_t paddr;
	माप_प्रकार size;
	काष्ठा list_head node;
पूर्ण;

/**
 * काष्ठा stratix10_svc_data - service data काष्ठाure
 * @chan: service channel
 * @paddr: playload physical address
 * @size: playload size
 * @command: service command requested by client
 * @flag: configuration type (full or partial)
 * @arg: args to be passed via रेजिस्टरs and not physically mapped buffers
 *
 * This काष्ठा is used in service FIFO क्रम पूर्णांकer-process communication.
 */
काष्ठा stratix10_svc_data अणु
	काष्ठा stratix10_svc_chan *chan;
	phys_addr_t paddr;
	माप_प्रकार size;
	u32 command;
	u32 flag;
	u64 arg[3];
पूर्ण;

/**
 * काष्ठा stratix10_svc_controller - service controller
 * @dev: device
 * @chans: array of service channels
 * @num_chans: number of channels in 'chans' array
 * @num_active_client: number of active service client
 * @node: list management
 * @genpool: memory pool poपूर्णांकing to the memory region
 * @task: poपूर्णांकer to the thपढ़ो task which handles SMC or HVC call
 * @svc_fअगरo: a queue क्रम storing service message data
 * @complete_status: state क्रम completion
 * @svc_fअगरo_lock: protect access to service message data queue
 * @invoke_fn: function to issue secure monitor call or hypervisor call
 *
 * This काष्ठा is used to create communication channels क्रम service clients, to
 * handle secure monitor or hypervisor call.
 */
काष्ठा stratix10_svc_controller अणु
	काष्ठा device *dev;
	काष्ठा stratix10_svc_chan *chans;
	पूर्णांक num_chans;
	पूर्णांक num_active_client;
	काष्ठा list_head node;
	काष्ठा gen_pool *genpool;
	काष्ठा task_काष्ठा *task;
	काष्ठा kfअगरo svc_fअगरo;
	काष्ठा completion complete_status;
	spinlock_t svc_fअगरo_lock;
	svc_invoke_fn *invoke_fn;
पूर्ण;

/**
 * काष्ठा stratix10_svc_chan - service communication channel
 * @ctrl: poपूर्णांकer to service controller which is the provider of this channel
 * @scl: poपूर्णांकer to service client which owns the channel
 * @name: service client name associated with the channel
 * @lock: protect access to the channel
 *
 * This काष्ठा is used by service client to communicate with service layer, each
 * service client has its own channel created by service controller.
 */
काष्ठा stratix10_svc_chan अणु
	काष्ठा stratix10_svc_controller *ctrl;
	काष्ठा stratix10_svc_client *scl;
	अक्षर *name;
	spinlock_t lock;
पूर्ण;

अटल LIST_HEAD(svc_ctrl);
अटल LIST_HEAD(svc_data_mem);

/**
 * svc_pa_to_va() - translate physical address to भव address
 * @addr: to be translated physical address
 *
 * Return: valid भव address or शून्य अगर the provided physical
 * address करोesn't exist.
 */
अटल व्योम *svc_pa_to_va(अचिन्हित दीर्घ addr)
अणु
	काष्ठा stratix10_svc_data_mem *pmem;

	pr_debug("claim back P-addr=0x%016x\n", (अचिन्हित पूर्णांक)addr);
	list_क्रम_each_entry(pmem, &svc_data_mem, node)
		अगर (pmem->paddr == addr)
			वापस pmem->vaddr;

	/* physical address is not found */
	वापस शून्य;
पूर्ण

/**
 * svc_thपढ़ो_cmd_data_claim() - claim back buffer from the secure world
 * @ctrl: poपूर्णांकer to service layer controller
 * @p_data: poपूर्णांकer to service data काष्ठाure
 * @cb_data: poपूर्णांकer to callback data काष्ठाure to service client
 *
 * Claim back the submitted buffers from the secure world and pass buffer
 * back to service client (FPGA manager, etc) क्रम reuse.
 */
अटल व्योम svc_thपढ़ो_cmd_data_claim(काष्ठा stratix10_svc_controller *ctrl,
				      काष्ठा stratix10_svc_data *p_data,
				      काष्ठा stratix10_svc_cb_data *cb_data)
अणु
	काष्ठा arm_smccc_res res;
	अचिन्हित दीर्घ समयout;

	reinit_completion(&ctrl->complete_status);
	समयout = msecs_to_jअगरfies(FPGA_CONFIG_DATA_CLAIM_TIMEOUT_MS);

	pr_debug("%s: claim back the submitted buffer\n", __func__);
	करो अणु
		ctrl->invoke_fn(INTEL_SIP_SMC_FPGA_CONFIG_COMPLETED_WRITE,
				0, 0, 0, 0, 0, 0, 0, &res);

		अगर (res.a0 == INTEL_SIP_SMC_STATUS_OK) अणु
			अगर (!res.a1) अणु
				complete(&ctrl->complete_status);
				अवरोध;
			पूर्ण
			cb_data->status = BIT(SVC_STATUS_BUFFER_DONE);
			cb_data->kaddr1 = svc_pa_to_va(res.a1);
			cb_data->kaddr2 = (res.a2) ?
					  svc_pa_to_va(res.a2) : शून्य;
			cb_data->kaddr3 = (res.a3) ?
					  svc_pa_to_va(res.a3) : शून्य;
			p_data->chan->scl->receive_cb(p_data->chan->scl,
						      cb_data);
		पूर्ण अन्यथा अणु
			pr_debug("%s: secure world busy, polling again\n",
				 __func__);
		पूर्ण
	पूर्ण जबतक (res.a0 == INTEL_SIP_SMC_STATUS_OK ||
		 res.a0 == INTEL_SIP_SMC_STATUS_BUSY ||
		 रुको_क्रम_completion_समयout(&ctrl->complete_status, समयout));
पूर्ण

/**
 * svc_thपढ़ो_cmd_config_status() - check configuration status
 * @ctrl: poपूर्णांकer to service layer controller
 * @p_data: poपूर्णांकer to service data काष्ठाure
 * @cb_data: poपूर्णांकer to callback data काष्ठाure to service client
 *
 * Check whether the secure firmware at secure world has finished the FPGA
 * configuration, and then inक्रमm FPGA manager the configuration status.
 */
अटल व्योम svc_thपढ़ो_cmd_config_status(काष्ठा stratix10_svc_controller *ctrl,
					 काष्ठा stratix10_svc_data *p_data,
					 काष्ठा stratix10_svc_cb_data *cb_data)
अणु
	काष्ठा arm_smccc_res res;
	पूर्णांक count_in_sec;

	cb_data->kaddr1 = शून्य;
	cb_data->kaddr2 = शून्य;
	cb_data->kaddr3 = शून्य;
	cb_data->status = BIT(SVC_STATUS_ERROR);

	pr_debug("%s: polling config status\n", __func__);

	count_in_sec = FPGA_CONFIG_STATUS_TIMEOUT_SEC;
	जबतक (count_in_sec) अणु
		ctrl->invoke_fn(INTEL_SIP_SMC_FPGA_CONFIG_ISDONE,
				0, 0, 0, 0, 0, 0, 0, &res);
		अगर ((res.a0 == INTEL_SIP_SMC_STATUS_OK) ||
		    (res.a0 == INTEL_SIP_SMC_STATUS_ERROR))
			अवरोध;

		/*
		 * configuration is still in progress, रुको one second then
		 * poll again
		 */
		msleep(1000);
		count_in_sec--;
	पूर्ण

	अगर (res.a0 == INTEL_SIP_SMC_STATUS_OK && count_in_sec)
		cb_data->status = BIT(SVC_STATUS_COMPLETED);

	p_data->chan->scl->receive_cb(p_data->chan->scl, cb_data);
पूर्ण

/**
 * svc_thपढ़ो_recv_status_ok() - handle the successful status
 * @p_data: poपूर्णांकer to service data काष्ठाure
 * @cb_data: poपूर्णांकer to callback data काष्ठाure to service client
 * @res: result from SMC or HVC call
 *
 * Send back the correspond status to the service clients.
 */
अटल व्योम svc_thपढ़ो_recv_status_ok(काष्ठा stratix10_svc_data *p_data,
				      काष्ठा stratix10_svc_cb_data *cb_data,
				      काष्ठा arm_smccc_res res)
अणु
	cb_data->kaddr1 = शून्य;
	cb_data->kaddr2 = शून्य;
	cb_data->kaddr3 = शून्य;

	चयन (p_data->command) अणु
	हाल COMMAND_RECONFIG:
	हाल COMMAND_RSU_UPDATE:
	हाल COMMAND_RSU_NOTIFY:
		cb_data->status = BIT(SVC_STATUS_OK);
		अवरोध;
	हाल COMMAND_RECONFIG_DATA_SUBMIT:
		cb_data->status = BIT(SVC_STATUS_BUFFER_SUBMITTED);
		अवरोध;
	हाल COMMAND_RECONFIG_STATUS:
		cb_data->status = BIT(SVC_STATUS_COMPLETED);
		अवरोध;
	हाल COMMAND_RSU_RETRY:
	हाल COMMAND_RSU_MAX_RETRY:
		cb_data->status = BIT(SVC_STATUS_OK);
		cb_data->kaddr1 = &res.a1;
		अवरोध;
	हाल COMMAND_RSU_DCMF_VERSION:
		cb_data->status = BIT(SVC_STATUS_OK);
		cb_data->kaddr1 = &res.a1;
		cb_data->kaddr2 = &res.a2;
		अवरोध;
	शेष:
		pr_warn("it shouldn't happen\n");
		अवरोध;
	पूर्ण

	pr_debug("%s: call receive_cb\n", __func__);
	p_data->chan->scl->receive_cb(p_data->chan->scl, cb_data);
पूर्ण

/**
 * svc_normal_to_secure_thपढ़ो() - the function to run in the kthपढ़ो
 * @data: data poपूर्णांकer क्रम kthपढ़ो function
 *
 * Service layer driver creates stratix10_svc_smc_hvc_call kthपढ़ो on CPU
 * node 0, its function stratix10_svc_secure_call_thपढ़ो is used to handle
 * SMC or HVC calls between kernel driver and secure monitor software.
 *
 * Return: 0 क्रम success or -ENOMEM on error.
 */
अटल पूर्णांक svc_normal_to_secure_thपढ़ो(व्योम *data)
अणु
	काष्ठा stratix10_svc_controller
			*ctrl = (काष्ठा stratix10_svc_controller *)data;
	काष्ठा stratix10_svc_data *pdata;
	काष्ठा stratix10_svc_cb_data *cbdata;
	काष्ठा arm_smccc_res res;
	अचिन्हित दीर्घ a0, a1, a2;
	पूर्णांक ret_fअगरo = 0;

	pdata =  kदो_स्मृति(माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	cbdata = kदो_स्मृति(माप(*cbdata), GFP_KERNEL);
	अगर (!cbdata) अणु
		kमुक्त(pdata);
		वापस -ENOMEM;
	पूर्ण

	/* शेष set, to हटाओ build warning */
	a0 = INTEL_SIP_SMC_FPGA_CONFIG_LOOPBACK;
	a1 = 0;
	a2 = 0;

	pr_debug("smc_hvc_shm_thread is running\n");

	जबतक (!kthपढ़ो_should_stop()) अणु
		ret_fअगरo = kfअगरo_out_spinlocked(&ctrl->svc_fअगरo,
						pdata, माप(*pdata),
						&ctrl->svc_fअगरo_lock);

		अगर (!ret_fअगरo)
			जारी;

		pr_debug("get from FIFO pa=0x%016x, command=%u, size=%u\n",
			 (अचिन्हित पूर्णांक)pdata->paddr, pdata->command,
			 (अचिन्हित पूर्णांक)pdata->size);

		चयन (pdata->command) अणु
		हाल COMMAND_RECONFIG_DATA_CLAIM:
			svc_thपढ़ो_cmd_data_claim(ctrl, pdata, cbdata);
			जारी;
		हाल COMMAND_RECONFIG:
			a0 = INTEL_SIP_SMC_FPGA_CONFIG_START;
			pr_debug("conf_type=%u\n", (अचिन्हित पूर्णांक)pdata->flag);
			a1 = pdata->flag;
			a2 = 0;
			अवरोध;
		हाल COMMAND_RECONFIG_DATA_SUBMIT:
			a0 = INTEL_SIP_SMC_FPGA_CONFIG_WRITE;
			a1 = (अचिन्हित दीर्घ)pdata->paddr;
			a2 = (अचिन्हित दीर्घ)pdata->size;
			अवरोध;
		हाल COMMAND_RECONFIG_STATUS:
			a0 = INTEL_SIP_SMC_FPGA_CONFIG_ISDONE;
			a1 = 0;
			a2 = 0;
			अवरोध;
		हाल COMMAND_RSU_STATUS:
			a0 = INTEL_SIP_SMC_RSU_STATUS;
			a1 = 0;
			a2 = 0;
			अवरोध;
		हाल COMMAND_RSU_UPDATE:
			a0 = INTEL_SIP_SMC_RSU_UPDATE;
			a1 = pdata->arg[0];
			a2 = 0;
			अवरोध;
		हाल COMMAND_RSU_NOTIFY:
			a0 = INTEL_SIP_SMC_RSU_NOTIFY;
			a1 = pdata->arg[0];
			a2 = 0;
			अवरोध;
		हाल COMMAND_RSU_RETRY:
			a0 = INTEL_SIP_SMC_RSU_RETRY_COUNTER;
			a1 = 0;
			a2 = 0;
			अवरोध;
		हाल COMMAND_RSU_MAX_RETRY:
			a0 = INTEL_SIP_SMC_RSU_MAX_RETRY;
			a1 = 0;
			a2 = 0;
			अवरोध;
		हाल COMMAND_RSU_DCMF_VERSION:
			a0 = INTEL_SIP_SMC_RSU_DCMF_VERSION;
			a1 = 0;
			a2 = 0;
			अवरोध;
		शेष:
			pr_warn("it shouldn't happen\n");
			अवरोध;
		पूर्ण
		pr_debug("%s: before SMC call -- a0=0x%016x a1=0x%016x",
			 __func__, (अचिन्हित पूर्णांक)a0, (अचिन्हित पूर्णांक)a1);
		pr_debug(" a2=0x%016x\n", (अचिन्हित पूर्णांक)a2);

		ctrl->invoke_fn(a0, a1, a2, 0, 0, 0, 0, 0, &res);

		pr_debug("%s: after SMC call -- res.a0=0x%016x",
			 __func__, (अचिन्हित पूर्णांक)res.a0);
		pr_debug(" res.a1=0x%016x, res.a2=0x%016x",
			 (अचिन्हित पूर्णांक)res.a1, (अचिन्हित पूर्णांक)res.a2);
		pr_debug(" res.a3=0x%016x\n", (अचिन्हित पूर्णांक)res.a3);

		अगर (pdata->command == COMMAND_RSU_STATUS) अणु
			अगर (res.a0 == INTEL_SIP_SMC_RSU_ERROR)
				cbdata->status = BIT(SVC_STATUS_ERROR);
			अन्यथा
				cbdata->status = BIT(SVC_STATUS_OK);

			cbdata->kaddr1 = &res;
			cbdata->kaddr2 = शून्य;
			cbdata->kaddr3 = शून्य;
			pdata->chan->scl->receive_cb(pdata->chan->scl, cbdata);
			जारी;
		पूर्ण

		चयन (res.a0) अणु
		हाल INTEL_SIP_SMC_STATUS_OK:
			svc_thपढ़ो_recv_status_ok(pdata, cbdata, res);
			अवरोध;
		हाल INTEL_SIP_SMC_STATUS_BUSY:
			चयन (pdata->command) अणु
			हाल COMMAND_RECONFIG_DATA_SUBMIT:
				svc_thपढ़ो_cmd_data_claim(ctrl,
							  pdata, cbdata);
				अवरोध;
			हाल COMMAND_RECONFIG_STATUS:
				svc_thपढ़ो_cmd_config_status(ctrl,
							     pdata, cbdata);
				अवरोध;
			शेष:
				pr_warn("it shouldn't happen\n");
				अवरोध;
			पूर्ण
			अवरोध;
		हाल INTEL_SIP_SMC_STATUS_REJECTED:
			pr_debug("%s: STATUS_REJECTED\n", __func__);
			अवरोध;
		हाल INTEL_SIP_SMC_STATUS_ERROR:
		हाल INTEL_SIP_SMC_RSU_ERROR:
			pr_err("%s: STATUS_ERROR\n", __func__);
			cbdata->status = BIT(SVC_STATUS_ERROR);
			cbdata->kaddr1 = शून्य;
			cbdata->kaddr2 = शून्य;
			cbdata->kaddr3 = शून्य;
			pdata->chan->scl->receive_cb(pdata->chan->scl, cbdata);
			अवरोध;
		शेष:
			pr_warn("Secure firmware doesn't support...\n");

			/*
			 * be compatible with older version firmware which
			 * करोesn't support RSU notअगरy or retry
			 */
			अगर ((pdata->command == COMMAND_RSU_RETRY) ||
			    (pdata->command == COMMAND_RSU_MAX_RETRY) ||
				(pdata->command == COMMAND_RSU_NOTIFY)) अणु
				cbdata->status =
					BIT(SVC_STATUS_NO_SUPPORT);
				cbdata->kaddr1 = शून्य;
				cbdata->kaddr2 = शून्य;
				cbdata->kaddr3 = शून्य;
				pdata->chan->scl->receive_cb(
					pdata->chan->scl, cbdata);
			पूर्ण
			अवरोध;

		पूर्ण
	पूर्ण

	kमुक्त(cbdata);
	kमुक्त(pdata);

	वापस 0;
पूर्ण

/**
 * svc_normal_to_secure_shm_thपढ़ो() - the function to run in the kthपढ़ो
 * @data: data poपूर्णांकer क्रम kthपढ़ो function
 *
 * Service layer driver creates stratix10_svc_smc_hvc_shm kthपढ़ो on CPU
 * node 0, its function stratix10_svc_secure_shm_thपढ़ो is used to query the
 * physical address of memory block reserved by secure monitor software at
 * secure world.
 *
 * svc_normal_to_secure_shm_thपढ़ो() calls करो_निकास() directly since it is a
 * standlone thपढ़ो क्रम which no one will call kthपढ़ो_stop() or वापस when
 * 'kthread_should_stop()' is true.
 */
अटल पूर्णांक svc_normal_to_secure_shm_thपढ़ो(व्योम *data)
अणु
	काष्ठा stratix10_svc_sh_memory
			*sh_mem = (काष्ठा stratix10_svc_sh_memory *)data;
	काष्ठा arm_smccc_res res;

	/* SMC or HVC call to get shared memory info from secure world */
	sh_mem->invoke_fn(INTEL_SIP_SMC_FPGA_CONFIG_GET_MEM,
			  0, 0, 0, 0, 0, 0, 0, &res);
	अगर (res.a0 == INTEL_SIP_SMC_STATUS_OK) अणु
		sh_mem->addr = res.a1;
		sh_mem->size = res.a2;
	पूर्ण अन्यथा अणु
		pr_err("%s: after SMC call -- res.a0=0x%016x",  __func__,
		       (अचिन्हित पूर्णांक)res.a0);
		sh_mem->addr = 0;
		sh_mem->size = 0;
	पूर्ण

	complete(&sh_mem->sync_complete);
	करो_निकास(0);
पूर्ण

/**
 * svc_get_sh_memory() - get memory block reserved by secure monitor SW
 * @pdev: poपूर्णांकer to service layer device
 * @sh_memory: poपूर्णांकer to service shared memory काष्ठाure
 *
 * Return: zero क्रम successfully getting the physical address of memory block
 * reserved by secure monitor software, or negative value on error.
 */
अटल पूर्णांक svc_get_sh_memory(काष्ठा platक्रमm_device *pdev,
				    काष्ठा stratix10_svc_sh_memory *sh_memory)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा task_काष्ठा *sh_memory_task;
	अचिन्हित पूर्णांक cpu = 0;

	init_completion(&sh_memory->sync_complete);

	/* smc or hvc call happens on cpu 0 bound kthपढ़ो */
	sh_memory_task = kthपढ़ो_create_on_node(svc_normal_to_secure_shm_thपढ़ो,
					       (व्योम *)sh_memory,
						cpu_to_node(cpu),
						"svc_smc_hvc_shm_thread");
	अगर (IS_ERR(sh_memory_task)) अणु
		dev_err(dev, "fail to create stratix10_svc_smc_shm_thread\n");
		वापस -EINVAL;
	पूर्ण

	wake_up_process(sh_memory_task);

	अगर (!रुको_क्रम_completion_समयout(&sh_memory->sync_complete, 10 * HZ)) अणु
		dev_err(dev,
			"timeout to get sh-memory paras from secure world\n");
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (!sh_memory->addr || !sh_memory->size) अणु
		dev_err(dev,
			"failed to get shared memory info from secure world\n");
		वापस -ENOMEM;
	पूर्ण

	dev_dbg(dev, "SM software provides paddr: 0x%016x, size: 0x%08x\n",
		(अचिन्हित पूर्णांक)sh_memory->addr,
		(अचिन्हित पूर्णांक)sh_memory->size);

	वापस 0;
पूर्ण

/**
 * svc_create_memory_pool() - create a memory pool from reserved memory block
 * @pdev: poपूर्णांकer to service layer device
 * @sh_memory: poपूर्णांकer to service shared memory काष्ठाure
 *
 * Return: pool allocated from reserved memory block or ERR_PTR() on error.
 */
अटल काष्ठा gen_pool *
svc_create_memory_pool(काष्ठा platक्रमm_device *pdev,
		       काष्ठा stratix10_svc_sh_memory *sh_memory)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा gen_pool *genpool;
	अचिन्हित दीर्घ vaddr;
	phys_addr_t paddr;
	माप_प्रकार size;
	phys_addr_t begin;
	phys_addr_t end;
	व्योम *va;
	माप_प्रकार page_mask = PAGE_SIZE - 1;
	पूर्णांक min_alloc_order = 3;
	पूर्णांक ret;

	begin = roundup(sh_memory->addr, PAGE_SIZE);
	end = roundकरोwn(sh_memory->addr + sh_memory->size, PAGE_SIZE);
	paddr = begin;
	size = end - begin;
	va = memremap(paddr, size, MEMREMAP_WC);
	अगर (!va) अणु
		dev_err(dev, "fail to remap shared memory\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	vaddr = (अचिन्हित दीर्घ)va;
	dev_dbg(dev,
		"reserved memory vaddr: %p, paddr: 0x%16x size: 0x%8x\n",
		va, (अचिन्हित पूर्णांक)paddr, (अचिन्हित पूर्णांक)size);
	अगर ((vaddr & page_mask) || (paddr & page_mask) ||
	    (size & page_mask)) अणु
		dev_err(dev, "page is not aligned\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	genpool = gen_pool_create(min_alloc_order, -1);
	अगर (!genpool) अणु
		dev_err(dev, "fail to create genpool\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	gen_pool_set_algo(genpool, gen_pool_best_fit, शून्य);
	ret = gen_pool_add_virt(genpool, vaddr, paddr, size, -1);
	अगर (ret) अणु
		dev_err(dev, "fail to add memory chunk to the pool\n");
		gen_pool_destroy(genpool);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस genpool;
पूर्ण

/**
 * svc_smccc_smc() - secure monitor call between normal and secure world
 * @a0: argument passed in रेजिस्टरs 0
 * @a1: argument passed in रेजिस्टरs 1
 * @a2: argument passed in रेजिस्टरs 2
 * @a3: argument passed in रेजिस्टरs 3
 * @a4: argument passed in रेजिस्टरs 4
 * @a5: argument passed in रेजिस्टरs 5
 * @a6: argument passed in रेजिस्टरs 6
 * @a7: argument passed in रेजिस्टरs 7
 * @res: result values from रेजिस्टर 0 to 3
 */
अटल व्योम svc_smccc_smc(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1,
			  अचिन्हित दीर्घ a2, अचिन्हित दीर्घ a3,
			  अचिन्हित दीर्घ a4, अचिन्हित दीर्घ a5,
			  अचिन्हित दीर्घ a6, अचिन्हित दीर्घ a7,
			  काष्ठा arm_smccc_res *res)
अणु
	arm_smccc_smc(a0, a1, a2, a3, a4, a5, a6, a7, res);
पूर्ण

/**
 * svc_smccc_hvc() - hypervisor call between normal and secure world
 * @a0: argument passed in रेजिस्टरs 0
 * @a1: argument passed in रेजिस्टरs 1
 * @a2: argument passed in रेजिस्टरs 2
 * @a3: argument passed in रेजिस्टरs 3
 * @a4: argument passed in रेजिस्टरs 4
 * @a5: argument passed in रेजिस्टरs 5
 * @a6: argument passed in रेजिस्टरs 6
 * @a7: argument passed in रेजिस्टरs 7
 * @res: result values from रेजिस्टर 0 to 3
 */
अटल व्योम svc_smccc_hvc(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1,
			  अचिन्हित दीर्घ a2, अचिन्हित दीर्घ a3,
			  अचिन्हित दीर्घ a4, अचिन्हित दीर्घ a5,
			  अचिन्हित दीर्घ a6, अचिन्हित दीर्घ a7,
			  काष्ठा arm_smccc_res *res)
अणु
	arm_smccc_hvc(a0, a1, a2, a3, a4, a5, a6, a7, res);
पूर्ण

/**
 * get_invoke_func() - invoke SMC or HVC call
 * @dev: poपूर्णांकer to device
 *
 * Return: function poपूर्णांकer to svc_smccc_smc or svc_smccc_hvc.
 */
अटल svc_invoke_fn *get_invoke_func(काष्ठा device *dev)
अणु
	स्थिर अक्षर *method;

	अगर (of_property_पढ़ो_string(dev->of_node, "method", &method)) अणु
		dev_warn(dev, "missing \"method\" property\n");
		वापस ERR_PTR(-ENXIO);
	पूर्ण

	अगर (!म_भेद(method, "smc"))
		वापस svc_smccc_smc;
	अगर (!म_भेद(method, "hvc"))
		वापस svc_smccc_hvc;

	dev_warn(dev, "invalid \"method\" property: %s\n", method);

	वापस ERR_PTR(-EINVAL);
पूर्ण

/**
 * stratix10_svc_request_channel_byname() - request a service channel
 * @client: poपूर्णांकer to service client
 * @name: service client name
 *
 * This function is used by service client to request a service channel.
 *
 * Return: a poपूर्णांकer to channel asचिन्हित to the client on success,
 * or ERR_PTR() on error.
 */
काष्ठा stratix10_svc_chan *stratix10_svc_request_channel_byname(
	काष्ठा stratix10_svc_client *client, स्थिर अक्षर *name)
अणु
	काष्ठा device *dev = client->dev;
	काष्ठा stratix10_svc_controller *controller;
	काष्ठा stratix10_svc_chan *chan = शून्य;
	अचिन्हित दीर्घ flag;
	पूर्णांक i;

	/* अगर probe was called after client's, or error on probe */
	अगर (list_empty(&svc_ctrl))
		वापस ERR_PTR(-EPROBE_DEFER);

	controller = list_first_entry(&svc_ctrl,
				      काष्ठा stratix10_svc_controller, node);
	क्रम (i = 0; i < SVC_NUM_CHANNEL; i++) अणु
		अगर (!म_भेद(controller->chans[i].name, name)) अणु
			chan = &controller->chans[i];
			अवरोध;
		पूर्ण
	पूर्ण

	/* अगर there was no channel match */
	अगर (i == SVC_NUM_CHANNEL) अणु
		dev_err(dev, "%s: channel not allocated\n", __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (chan->scl || !try_module_get(controller->dev->driver->owner)) अणु
		dev_dbg(dev, "%s: svc not free\n", __func__);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	spin_lock_irqsave(&chan->lock, flag);
	chan->scl = client;
	chan->ctrl->num_active_client++;
	spin_unlock_irqrestore(&chan->lock, flag);

	वापस chan;
पूर्ण
EXPORT_SYMBOL_GPL(stratix10_svc_request_channel_byname);

/**
 * stratix10_svc_मुक्त_channel() - मुक्त service channel
 * @chan: service channel to be मुक्तd
 *
 * This function is used by service client to मुक्त a service channel.
 */
व्योम stratix10_svc_मुक्त_channel(काष्ठा stratix10_svc_chan *chan)
अणु
	अचिन्हित दीर्घ flag;

	spin_lock_irqsave(&chan->lock, flag);
	chan->scl = शून्य;
	chan->ctrl->num_active_client--;
	module_put(chan->ctrl->dev->driver->owner);
	spin_unlock_irqrestore(&chan->lock, flag);
पूर्ण
EXPORT_SYMBOL_GPL(stratix10_svc_मुक्त_channel);

/**
 * stratix10_svc_send() - send a message data to the remote
 * @chan: service channel asचिन्हित to the client
 * @msg: message data to be sent, in the क्रमmat of
 * "struct stratix10_svc_client_msg"
 *
 * This function is used by service client to add a message to the service
 * layer driver's queue क्रम being sent to the secure world.
 *
 * Return: 0 क्रम success, -ENOMEM or -ENOBUFS on error.
 */
पूर्णांक stratix10_svc_send(काष्ठा stratix10_svc_chan *chan, व्योम *msg)
अणु
	काष्ठा stratix10_svc_client_msg
		*p_msg = (काष्ठा stratix10_svc_client_msg *)msg;
	काष्ठा stratix10_svc_data_mem *p_mem;
	काष्ठा stratix10_svc_data *p_data;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक cpu = 0;

	p_data = kzalloc(माप(*p_data), GFP_KERNEL);
	अगर (!p_data)
		वापस -ENOMEM;

	/* first client will create kernel thपढ़ो */
	अगर (!chan->ctrl->task) अणु
		chan->ctrl->task =
			kthपढ़ो_create_on_node(svc_normal_to_secure_thपढ़ो,
					      (व्योम *)chan->ctrl,
					      cpu_to_node(cpu),
					      "svc_smc_hvc_thread");
			अगर (IS_ERR(chan->ctrl->task)) अणु
				dev_err(chan->ctrl->dev,
					"failed to create svc_smc_hvc_thread\n");
				kमुक्त(p_data);
				वापस -EINVAL;
			पूर्ण
		kthपढ़ो_bind(chan->ctrl->task, cpu);
		wake_up_process(chan->ctrl->task);
	पूर्ण

	pr_debug("%s: sent P-va=%p, P-com=%x, P-size=%u\n", __func__,
		 p_msg->payload, p_msg->command,
		 (अचिन्हित पूर्णांक)p_msg->payload_length);

	अगर (list_empty(&svc_data_mem)) अणु
		अगर (p_msg->command == COMMAND_RECONFIG) अणु
			काष्ठा stratix10_svc_command_config_type *ct =
				(काष्ठा stratix10_svc_command_config_type *)
				p_msg->payload;
			p_data->flag = ct->flags;
		पूर्ण
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(p_mem, &svc_data_mem, node)
			अगर (p_mem->vaddr == p_msg->payload) अणु
				p_data->paddr = p_mem->paddr;
				अवरोध;
			पूर्ण
	पूर्ण

	p_data->command = p_msg->command;
	p_data->arg[0] = p_msg->arg[0];
	p_data->arg[1] = p_msg->arg[1];
	p_data->arg[2] = p_msg->arg[2];
	p_data->size = p_msg->payload_length;
	p_data->chan = chan;
	pr_debug("%s: put to FIFO pa=0x%016x, cmd=%x, size=%u\n", __func__,
	       (अचिन्हित पूर्णांक)p_data->paddr, p_data->command,
	       (अचिन्हित पूर्णांक)p_data->size);
	ret = kfअगरo_in_spinlocked(&chan->ctrl->svc_fअगरo, p_data,
				  माप(*p_data),
				  &chan->ctrl->svc_fअगरo_lock);

	kमुक्त(p_data);

	अगर (!ret)
		वापस -ENOBUFS;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(stratix10_svc_send);

/**
 * stratix10_svc_करोne() - complete service request transactions
 * @chan: service channel asचिन्हित to the client
 *
 * This function should be called when client has finished its request
 * or there is an error in the request process. It allows the service layer
 * to stop the running thपढ़ो to have maximize savings in kernel resources.
 */
व्योम stratix10_svc_करोne(काष्ठा stratix10_svc_chan *chan)
अणु
	/* stop thपढ़ो when thपढ़ो is running AND only one active client */
	अगर (chan->ctrl->task && chan->ctrl->num_active_client <= 1) अणु
		pr_debug("svc_smc_hvc_shm_thread is stopped\n");
		kthपढ़ो_stop(chan->ctrl->task);
		chan->ctrl->task = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(stratix10_svc_करोne);

/**
 * stratix10_svc_allocate_memory() - allocate memory
 * @chan: service channel asचिन्हित to the client
 * @size: memory size requested by a specअगरic service client
 *
 * Service layer allocates the requested number of bytes buffer from the
 * memory pool, service client uses this function to get allocated buffers.
 *
 * Return: address of allocated memory on success, or ERR_PTR() on error.
 */
व्योम *stratix10_svc_allocate_memory(काष्ठा stratix10_svc_chan *chan,
				    माप_प्रकार size)
अणु
	काष्ठा stratix10_svc_data_mem *pmem;
	अचिन्हित दीर्घ va;
	phys_addr_t pa;
	काष्ठा gen_pool *genpool = chan->ctrl->genpool;
	माप_प्रकार s = roundup(size, 1 << genpool->min_alloc_order);

	pmem = devm_kzalloc(chan->ctrl->dev, माप(*pmem), GFP_KERNEL);
	अगर (!pmem)
		वापस ERR_PTR(-ENOMEM);

	va = gen_pool_alloc(genpool, s);
	अगर (!va)
		वापस ERR_PTR(-ENOMEM);

	स_रखो((व्योम *)va, 0, s);
	pa = gen_pool_virt_to_phys(genpool, va);

	pmem->vaddr = (व्योम *)va;
	pmem->paddr = pa;
	pmem->size = s;
	list_add_tail(&pmem->node, &svc_data_mem);
	pr_debug("%s: va=%p, pa=0x%016x\n", __func__,
		 pmem->vaddr, (अचिन्हित पूर्णांक)pmem->paddr);

	वापस (व्योम *)va;
पूर्ण
EXPORT_SYMBOL_GPL(stratix10_svc_allocate_memory);

/**
 * stratix10_svc_मुक्त_memory() - मुक्त allocated memory
 * @chan: service channel asचिन्हित to the client
 * @kaddr: memory to be मुक्तd
 *
 * This function is used by service client to मुक्त allocated buffers.
 */
व्योम stratix10_svc_मुक्त_memory(काष्ठा stratix10_svc_chan *chan, व्योम *kaddr)
अणु
	काष्ठा stratix10_svc_data_mem *pmem;
	माप_प्रकार size = 0;

	list_क्रम_each_entry(pmem, &svc_data_mem, node)
		अगर (pmem->vaddr == kaddr) अणु
			size = pmem->size;
			अवरोध;
		पूर्ण

	gen_pool_मुक्त(chan->ctrl->genpool, (अचिन्हित दीर्घ)kaddr, size);
	pmem->vaddr = शून्य;
	list_del(&pmem->node);
पूर्ण
EXPORT_SYMBOL_GPL(stratix10_svc_मुक्त_memory);

अटल स्थिर काष्ठा of_device_id stratix10_svc_drv_match[] = अणु
	अणु.compatible = "intel,stratix10-svc"पूर्ण,
	अणु.compatible = "intel,agilex-svc"पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक stratix10_svc_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा stratix10_svc_controller *controller;
	काष्ठा stratix10_svc_chan *chans;
	काष्ठा gen_pool *genpool;
	काष्ठा stratix10_svc_sh_memory *sh_memory;
	काष्ठा stratix10_svc *svc;

	svc_invoke_fn *invoke_fn;
	माप_प्रकार fअगरo_size;
	पूर्णांक ret;

	/* get SMC or HVC function */
	invoke_fn = get_invoke_func(dev);
	अगर (IS_ERR(invoke_fn))
		वापस -EINVAL;

	sh_memory = devm_kzalloc(dev, माप(*sh_memory), GFP_KERNEL);
	अगर (!sh_memory)
		वापस -ENOMEM;

	sh_memory->invoke_fn = invoke_fn;
	ret = svc_get_sh_memory(pdev, sh_memory);
	अगर (ret)
		वापस ret;

	genpool = svc_create_memory_pool(pdev, sh_memory);
	अगर (!genpool)
		वापस -ENOMEM;

	/* allocate service controller and supporting channel */
	controller = devm_kzalloc(dev, माप(*controller), GFP_KERNEL);
	अगर (!controller)
		वापस -ENOMEM;

	chans = devm_kदो_स्मृति_array(dev, SVC_NUM_CHANNEL,
				   माप(*chans), GFP_KERNEL | __GFP_ZERO);
	अगर (!chans)
		वापस -ENOMEM;

	controller->dev = dev;
	controller->num_chans = SVC_NUM_CHANNEL;
	controller->num_active_client = 0;
	controller->chans = chans;
	controller->genpool = genpool;
	controller->task = शून्य;
	controller->invoke_fn = invoke_fn;
	init_completion(&controller->complete_status);

	fअगरo_size = माप(काष्ठा stratix10_svc_data) * SVC_NUM_DATA_IN_FIFO;
	ret = kfअगरo_alloc(&controller->svc_fअगरo, fअगरo_size, GFP_KERNEL);
	अगर (ret) अणु
		dev_err(dev, "failed to allocate FIFO\n");
		वापस ret;
	पूर्ण
	spin_lock_init(&controller->svc_fअगरo_lock);

	chans[0].scl = शून्य;
	chans[0].ctrl = controller;
	chans[0].name = SVC_CLIENT_FPGA;
	spin_lock_init(&chans[0].lock);

	chans[1].scl = शून्य;
	chans[1].ctrl = controller;
	chans[1].name = SVC_CLIENT_RSU;
	spin_lock_init(&chans[1].lock);

	list_add_tail(&controller->node, &svc_ctrl);
	platक्रमm_set_drvdata(pdev, controller);

	/* add svc client device(s) */
	svc = devm_kzalloc(dev, माप(*svc), GFP_KERNEL);
	अगर (!svc)
		वापस -ENOMEM;

	svc->stratix10_svc_rsu = platक्रमm_device_alloc(STRATIX10_RSU, 0);
	अगर (!svc->stratix10_svc_rsu) अणु
		dev_err(dev, "failed to allocate %s device\n", STRATIX10_RSU);
		वापस -ENOMEM;
	पूर्ण

	ret = platक्रमm_device_add(svc->stratix10_svc_rsu);
	अगर (ret) अणु
		platक्रमm_device_put(svc->stratix10_svc_rsu);
		वापस ret;
	पूर्ण
	dev_set_drvdata(dev, svc);

	pr_info("Intel Service Layer Driver Initialized\n");

	वापस ret;
पूर्ण

अटल पूर्णांक stratix10_svc_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा stratix10_svc *svc = dev_get_drvdata(&pdev->dev);
	काष्ठा stratix10_svc_controller *ctrl = platक्रमm_get_drvdata(pdev);

	platक्रमm_device_unरेजिस्टर(svc->stratix10_svc_rsu);

	kfअगरo_मुक्त(&ctrl->svc_fअगरo);
	अगर (ctrl->task) अणु
		kthपढ़ो_stop(ctrl->task);
		ctrl->task = शून्य;
	पूर्ण
	अगर (ctrl->genpool)
		gen_pool_destroy(ctrl->genpool);
	list_del(&ctrl->node);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver stratix10_svc_driver = अणु
	.probe = stratix10_svc_drv_probe,
	.हटाओ = stratix10_svc_drv_हटाओ,
	.driver = अणु
		.name = "stratix10-svc",
		.of_match_table = stratix10_svc_drv_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init stratix10_svc_init(व्योम)
अणु
	काष्ठा device_node *fw_np;
	काष्ठा device_node *np;
	पूर्णांक ret;

	fw_np = of_find_node_by_name(शून्य, "firmware");
	अगर (!fw_np)
		वापस -ENODEV;

	np = of_find_matching_node(fw_np, stratix10_svc_drv_match);
	अगर (!np)
		वापस -ENODEV;

	of_node_put(np);
	ret = of_platक्रमm_populate(fw_np, stratix10_svc_drv_match, शून्य, शून्य);
	अगर (ret)
		वापस ret;

	वापस platक्रमm_driver_रेजिस्टर(&stratix10_svc_driver);
पूर्ण

अटल व्योम __निकास stratix10_svc_निकास(व्योम)
अणु
	वापस platक्रमm_driver_unरेजिस्टर(&stratix10_svc_driver);
पूर्ण

subsys_initcall(stratix10_svc_init);
module_निकास(stratix10_svc_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel Stratix10 Service Layer Driver");
MODULE_AUTHOR("Richard Gong <richard.gong@intel.com>");
MODULE_ALIAS("platform:stratix10-svc");
