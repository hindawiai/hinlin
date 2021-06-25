<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015, Linaro Limited
 */

#अगर_अघोषित OPTEE_PRIVATE_H
#घोषणा OPTEE_PRIVATE_H

#समावेश <linux/arm-smccc.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/tee_drv.h>
#समावेश <linux/types.h>
#समावेश "optee_msg.h"

#घोषणा OPTEE_MAX_ARG_SIZE	1024

/* Some Global Platक्रमm error codes used in this driver */
#घोषणा TEEC_SUCCESS			0x00000000
#घोषणा TEEC_ERROR_BAD_PARAMETERS	0xFFFF0006
#घोषणा TEEC_ERROR_NOT_SUPPORTED	0xFFFF000A
#घोषणा TEEC_ERROR_COMMUNICATION	0xFFFF000E
#घोषणा TEEC_ERROR_OUT_OF_MEMORY	0xFFFF000C
#घोषणा TEEC_ERROR_SHORT_BUFFER		0xFFFF0010

#घोषणा TEEC_ORIGIN_COMMS		0x00000002

प्रकार व्योम (optee_invoke_fn)(अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ,
				अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ,
				अचिन्हित दीर्घ, अचिन्हित दीर्घ,
				काष्ठा arm_smccc_res *);

काष्ठा optee_call_queue अणु
	/* Serializes access to this काष्ठा */
	काष्ठा mutex mutex;
	काष्ठा list_head रुकोers;
पूर्ण;

काष्ठा optee_रुको_queue अणु
	/* Serializes access to this काष्ठा */
	काष्ठा mutex mu;
	काष्ठा list_head db;
पूर्ण;

/**
 * काष्ठा optee_supp - supplicant synchronization काष्ठा
 * @ctx			the context of current connected supplicant.
 *			अगर !शून्य the supplicant device is available क्रम use,
 *			अन्यथा busy
 * @mutex:		held जबतक accessing content of this काष्ठा
 * @req_id:		current request id अगर supplicant is करोing synchronous
 *			communication, अन्यथा -1
 * @reqs:		queued request not yet retrieved by supplicant
 * @idr:		IDR holding all requests currently being processed
 *			by supplicant
 * @reqs_c:		completion used by supplicant when रुकोing क्रम a
 *			request to be queued.
 */
काष्ठा optee_supp अणु
	/* Serializes access to this काष्ठा */
	काष्ठा mutex mutex;
	काष्ठा tee_context *ctx;

	पूर्णांक req_id;
	काष्ठा list_head reqs;
	काष्ठा idr idr;
	काष्ठा completion reqs_c;
पूर्ण;

/**
 * काष्ठा optee - मुख्य service काष्ठा
 * @supp_teedev:	supplicant device
 * @teedev:		client device
 * @invoke_fn:		function to issue smc or hvc
 * @call_queue:		queue of thपढ़ोs रुकोing to call @invoke_fn
 * @रुको_queue:		queue of thपढ़ोs from secure world रुकोing क्रम a
 *			secure world sync object
 * @supp:		supplicant synchronization काष्ठा क्रम RPC to supplicant
 * @pool:		shared memory pool
 * @memremaped_shm	भव address of memory in shared memory pool
 * @sec_caps:		secure world capabilities defined by
 *			OPTEE_SMC_SEC_CAP_* in optee_smc.h
 * @scan_bus_करोne	flag अगर device registation was alपढ़ोy करोne.
 * @scan_bus_wq		workqueue to scan optee bus and रेजिस्टर optee drivers
 * @scan_bus_work	workq to scan optee bus and रेजिस्टर optee drivers
 */
काष्ठा optee अणु
	काष्ठा tee_device *supp_teedev;
	काष्ठा tee_device *teedev;
	optee_invoke_fn *invoke_fn;
	काष्ठा optee_call_queue call_queue;
	काष्ठा optee_रुको_queue रुको_queue;
	काष्ठा optee_supp supp;
	काष्ठा tee_shm_pool *pool;
	व्योम *memremaped_shm;
	u32 sec_caps;
	bool   scan_bus_करोne;
	काष्ठा workqueue_काष्ठा *scan_bus_wq;
	काष्ठा work_काष्ठा scan_bus_work;
पूर्ण;

काष्ठा optee_session अणु
	काष्ठा list_head list_node;
	u32 session_id;
पूर्ण;

काष्ठा optee_context_data अणु
	/* Serializes access to this काष्ठा */
	काष्ठा mutex mutex;
	काष्ठा list_head sess_list;
पूर्ण;

काष्ठा optee_rpc_param अणु
	u32	a0;
	u32	a1;
	u32	a2;
	u32	a3;
	u32	a4;
	u32	a5;
	u32	a6;
	u32	a7;
पूर्ण;

/* Holds context that is preserved during one STD call */
काष्ठा optee_call_ctx अणु
	/* inक्रमmation about pages list used in last allocation */
	व्योम *pages_list;
	माप_प्रकार num_entries;
पूर्ण;

व्योम optee_handle_rpc(काष्ठा tee_context *ctx, काष्ठा optee_rpc_param *param,
		      काष्ठा optee_call_ctx *call_ctx);
व्योम optee_rpc_finalize_call(काष्ठा optee_call_ctx *call_ctx);

व्योम optee_रुको_queue_init(काष्ठा optee_रुको_queue *wq);
व्योम optee_रुको_queue_निकास(काष्ठा optee_रुको_queue *wq);

u32 optee_supp_thrd_req(काष्ठा tee_context *ctx, u32 func, माप_प्रकार num_params,
			काष्ठा tee_param *param);

पूर्णांक optee_supp_पढ़ो(काष्ठा tee_context *ctx, व्योम __user *buf, माप_प्रकार len);
पूर्णांक optee_supp_ग_लिखो(काष्ठा tee_context *ctx, व्योम __user *buf, माप_प्रकार len);
व्योम optee_supp_init(काष्ठा optee_supp *supp);
व्योम optee_supp_uninit(काष्ठा optee_supp *supp);
व्योम optee_supp_release(काष्ठा optee_supp *supp);

पूर्णांक optee_supp_recv(काष्ठा tee_context *ctx, u32 *func, u32 *num_params,
		    काष्ठा tee_param *param);
पूर्णांक optee_supp_send(काष्ठा tee_context *ctx, u32 ret, u32 num_params,
		    काष्ठा tee_param *param);

u32 optee_करो_call_with_arg(काष्ठा tee_context *ctx, phys_addr_t parg);
पूर्णांक optee_खोलो_session(काष्ठा tee_context *ctx,
		       काष्ठा tee_ioctl_खोलो_session_arg *arg,
		       काष्ठा tee_param *param);
पूर्णांक optee_बंद_session(काष्ठा tee_context *ctx, u32 session);
पूर्णांक optee_invoke_func(काष्ठा tee_context *ctx, काष्ठा tee_ioctl_invoke_arg *arg,
		      काष्ठा tee_param *param);
पूर्णांक optee_cancel_req(काष्ठा tee_context *ctx, u32 cancel_id, u32 session);

व्योम optee_enable_shm_cache(काष्ठा optee *optee);
व्योम optee_disable_shm_cache(काष्ठा optee *optee);

पूर्णांक optee_shm_रेजिस्टर(काष्ठा tee_context *ctx, काष्ठा tee_shm *shm,
		       काष्ठा page **pages, माप_प्रकार num_pages,
		       अचिन्हित दीर्घ start);
पूर्णांक optee_shm_unरेजिस्टर(काष्ठा tee_context *ctx, काष्ठा tee_shm *shm);

पूर्णांक optee_shm_रेजिस्टर_supp(काष्ठा tee_context *ctx, काष्ठा tee_shm *shm,
			    काष्ठा page **pages, माप_प्रकार num_pages,
			    अचिन्हित दीर्घ start);
पूर्णांक optee_shm_unरेजिस्टर_supp(काष्ठा tee_context *ctx, काष्ठा tee_shm *shm);

पूर्णांक optee_from_msg_param(काष्ठा tee_param *params, माप_प्रकार num_params,
			 स्थिर काष्ठा optee_msg_param *msg_params);
पूर्णांक optee_to_msg_param(काष्ठा optee_msg_param *msg_params, माप_प्रकार num_params,
		       स्थिर काष्ठा tee_param *params);

u64 *optee_allocate_pages_list(माप_प्रकार num_entries);
व्योम optee_मुक्त_pages_list(व्योम *array, माप_प्रकार num_entries);
व्योम optee_fill_pages_list(u64 *dst, काष्ठा page **pages, पूर्णांक num_pages,
			   माप_प्रकार page_offset);

#घोषणा PTA_CMD_GET_DEVICES		0x0
#घोषणा PTA_CMD_GET_DEVICES_SUPP	0x1
पूर्णांक optee_क्रमागतerate_devices(u32 func);

/*
 * Small helpers
 */

अटल अंतरभूत व्योम *reg_pair_to_ptr(u32 reg0, u32 reg1)
अणु
	वापस (व्योम *)(अचिन्हित दीर्घ)(((u64)reg0 << 32) | reg1);
पूर्ण

अटल अंतरभूत व्योम reg_pair_from_64(u32 *reg0, u32 *reg1, u64 val)
अणु
	*reg0 = val >> 32;
	*reg1 = val;
पूर्ण

#पूर्ण_अगर /*OPTEE_PRIVATE_H*/
