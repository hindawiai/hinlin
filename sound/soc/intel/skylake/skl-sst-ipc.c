<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * skl-sst-ipc.c - Intel skl IPC Support
 *
 * Copyright (C) 2014-15, Intel Corporation.
 */
#समावेश <linux/device.h>

#समावेश "../common/sst-dsp.h"
#समावेश "../common/sst-dsp-priv.h"
#समावेश "skl.h"
#समावेश "skl-sst-dsp.h"
#समावेश "skl-sst-ipc.h"
#समावेश "sound/hdaudio_ext.h"


#घोषणा IPC_IXC_STATUS_BITS		24

/* Global Message - Generic */
#घोषणा IPC_GLB_TYPE_SHIFT		24
#घोषणा IPC_GLB_TYPE_MASK		(0xf << IPC_GLB_TYPE_SHIFT)
#घोषणा IPC_GLB_TYPE(x)			((x) << IPC_GLB_TYPE_SHIFT)

/* Global Message - Reply */
#घोषणा IPC_GLB_REPLY_STATUS_SHIFT	24
#घोषणा IPC_GLB_REPLY_STATUS_MASK	((0x1 << IPC_GLB_REPLY_STATUS_SHIFT) - 1)
#घोषणा IPC_GLB_REPLY_STATUS(x)		((x) << IPC_GLB_REPLY_STATUS_SHIFT)

#घोषणा IPC_GLB_REPLY_TYPE_SHIFT	29
#घोषणा IPC_GLB_REPLY_TYPE_MASK		0x1F
#घोषणा IPC_GLB_REPLY_TYPE(x)		(((x) >> IPC_GLB_REPLY_TYPE_SHIFT) \
					& IPC_GLB_RPLY_TYPE_MASK)

#घोषणा IPC_TIMEOUT_MSECS		3000

#घोषणा IPC_EMPTY_LIST_SIZE		8

#घोषणा IPC_MSG_TARGET_SHIFT		30
#घोषणा IPC_MSG_TARGET_MASK		0x1
#घोषणा IPC_MSG_TARGET(x)		(((x) & IPC_MSG_TARGET_MASK) \
					<< IPC_MSG_TARGET_SHIFT)

#घोषणा IPC_MSG_सूची_SHIFT		29
#घोषणा IPC_MSG_सूची_MASK		0x1
#घोषणा IPC_MSG_सूची(x)			(((x) & IPC_MSG_सूची_MASK) \
					<< IPC_MSG_सूची_SHIFT)
/* Global Notअगरication Message */
#घोषणा IPC_GLB_NOTIFY_TYPE_SHIFT	16
#घोषणा IPC_GLB_NOTIFY_TYPE_MASK	0xFF
#घोषणा IPC_GLB_NOTIFY_TYPE(x)		(((x) >> IPC_GLB_NOTIFY_TYPE_SHIFT) \
					& IPC_GLB_NOTIFY_TYPE_MASK)

#घोषणा IPC_GLB_NOTIFY_MSG_TYPE_SHIFT	24
#घोषणा IPC_GLB_NOTIFY_MSG_TYPE_MASK	0x1F
#घोषणा IPC_GLB_NOTIFY_MSG_TYPE(x)	(((x) >> IPC_GLB_NOTIFY_MSG_TYPE_SHIFT)	\
						& IPC_GLB_NOTIFY_MSG_TYPE_MASK)

#घोषणा IPC_GLB_NOTIFY_RSP_SHIFT	29
#घोषणा IPC_GLB_NOTIFY_RSP_MASK		0x1
#घोषणा IPC_GLB_NOTIFY_RSP_TYPE(x)	(((x) >> IPC_GLB_NOTIFY_RSP_SHIFT) \
					& IPC_GLB_NOTIFY_RSP_MASK)

/* Pipeline operations */

/* Create pipeline message */
#घोषणा IPC_PPL_MEM_SIZE_SHIFT		0
#घोषणा IPC_PPL_MEM_SIZE_MASK		0x7FF
#घोषणा IPC_PPL_MEM_SIZE(x)		(((x) & IPC_PPL_MEM_SIZE_MASK) \
					<< IPC_PPL_MEM_SIZE_SHIFT)

#घोषणा IPC_PPL_TYPE_SHIFT		11
#घोषणा IPC_PPL_TYPE_MASK		0x1F
#घोषणा IPC_PPL_TYPE(x)			(((x) & IPC_PPL_TYPE_MASK) \
					<< IPC_PPL_TYPE_SHIFT)

#घोषणा IPC_INSTANCE_ID_SHIFT		16
#घोषणा IPC_INSTANCE_ID_MASK		0xFF
#घोषणा IPC_INSTANCE_ID(x)		(((x) & IPC_INSTANCE_ID_MASK) \
					<< IPC_INSTANCE_ID_SHIFT)

#घोषणा IPC_PPL_LP_MODE_SHIFT           0
#घोषणा IPC_PPL_LP_MODE_MASK            0x1
#घोषणा IPC_PPL_LP_MODE(x)              (((x) & IPC_PPL_LP_MODE_MASK) \
					<< IPC_PPL_LP_MODE_SHIFT)

/* Set pipeline state message */
#घोषणा IPC_PPL_STATE_SHIFT		0
#घोषणा IPC_PPL_STATE_MASK		0x1F
#घोषणा IPC_PPL_STATE(x)		(((x) & IPC_PPL_STATE_MASK) \
					<< IPC_PPL_STATE_SHIFT)

/* Module operations primary रेजिस्टर */
#घोषणा IPC_MOD_ID_SHIFT		0
#घोषणा IPC_MOD_ID_MASK		0xFFFF
#घोषणा IPC_MOD_ID(x)		(((x) & IPC_MOD_ID_MASK) \
					<< IPC_MOD_ID_SHIFT)

#घोषणा IPC_MOD_INSTANCE_ID_SHIFT	16
#घोषणा IPC_MOD_INSTANCE_ID_MASK	0xFF
#घोषणा IPC_MOD_INSTANCE_ID(x)	(((x) & IPC_MOD_INSTANCE_ID_MASK) \
					<< IPC_MOD_INSTANCE_ID_SHIFT)

/* Init instance message extension रेजिस्टर */
#घोषणा IPC_PARAM_BLOCK_SIZE_SHIFT	0
#घोषणा IPC_PARAM_BLOCK_SIZE_MASK	0xFFFF
#घोषणा IPC_PARAM_BLOCK_SIZE(x)		(((x) & IPC_PARAM_BLOCK_SIZE_MASK) \
					<< IPC_PARAM_BLOCK_SIZE_SHIFT)

#घोषणा IPC_PPL_INSTANCE_ID_SHIFT	16
#घोषणा IPC_PPL_INSTANCE_ID_MASK	0xFF
#घोषणा IPC_PPL_INSTANCE_ID(x)		(((x) & IPC_PPL_INSTANCE_ID_MASK) \
					<< IPC_PPL_INSTANCE_ID_SHIFT)

#घोषणा IPC_CORE_ID_SHIFT		24
#घोषणा IPC_CORE_ID_MASK		0x1F
#घोषणा IPC_CORE_ID(x)			(((x) & IPC_CORE_ID_MASK) \
					<< IPC_CORE_ID_SHIFT)

#घोषणा IPC_DOMAIN_SHIFT                28
#घोषणा IPC_DOMAIN_MASK                 0x1
#घोषणा IPC_DOMAIN(x)                   (((x) & IPC_DOMAIN_MASK) \
					<< IPC_DOMAIN_SHIFT)

/* Bind/Unbind message extension रेजिस्टर */
#घोषणा IPC_DST_MOD_ID_SHIFT		0
#घोषणा IPC_DST_MOD_ID(x)		(((x) & IPC_MOD_ID_MASK) \
					<< IPC_DST_MOD_ID_SHIFT)

#घोषणा IPC_DST_MOD_INSTANCE_ID_SHIFT 16
#घोषणा IPC_DST_MOD_INSTANCE_ID(x)	(((x) & IPC_MOD_INSTANCE_ID_MASK) \
					<< IPC_DST_MOD_INSTANCE_ID_SHIFT)

#घोषणा IPC_DST_QUEUE_SHIFT		24
#घोषणा IPC_DST_QUEUE_MASK		0x7
#घोषणा IPC_DST_QUEUE(x)		(((x) & IPC_DST_QUEUE_MASK) \
					<< IPC_DST_QUEUE_SHIFT)

#घोषणा IPC_SRC_QUEUE_SHIFT		27
#घोषणा IPC_SRC_QUEUE_MASK		0x7
#घोषणा IPC_SRC_QUEUE(x)		(((x) & IPC_SRC_QUEUE_MASK) \
					<< IPC_SRC_QUEUE_SHIFT)
/* Load Module count */
#घोषणा IPC_LOAD_MODULE_SHIFT		0
#घोषणा IPC_LOAD_MODULE_MASK		0xFF
#घोषणा IPC_LOAD_MODULE_CNT(x)		(((x) & IPC_LOAD_MODULE_MASK) \
					<< IPC_LOAD_MODULE_SHIFT)

/* Save pipeline messgae extension रेजिस्टर */
#घोषणा IPC_DMA_ID_SHIFT		0
#घोषणा IPC_DMA_ID_MASK			0x1F
#घोषणा IPC_DMA_ID(x)			(((x) & IPC_DMA_ID_MASK) \
					<< IPC_DMA_ID_SHIFT)
/* Large Config message extension रेजिस्टर */
#घोषणा IPC_DATA_OFFSET_SZ_SHIFT	0
#घोषणा IPC_DATA_OFFSET_SZ_MASK		0xFFFFF
#घोषणा IPC_DATA_OFFSET_SZ(x)		(((x) & IPC_DATA_OFFSET_SZ_MASK) \
					<< IPC_DATA_OFFSET_SZ_SHIFT)
#घोषणा IPC_DATA_OFFSET_SZ_CLEAR	~(IPC_DATA_OFFSET_SZ_MASK \
					  << IPC_DATA_OFFSET_SZ_SHIFT)

#घोषणा IPC_LARGE_PARAM_ID_SHIFT	20
#घोषणा IPC_LARGE_PARAM_ID_MASK		0xFF
#घोषणा IPC_LARGE_PARAM_ID(x)		(((x) & IPC_LARGE_PARAM_ID_MASK) \
					<< IPC_LARGE_PARAM_ID_SHIFT)

#घोषणा IPC_FINAL_BLOCK_SHIFT		28
#घोषणा IPC_FINAL_BLOCK_MASK		0x1
#घोषणा IPC_FINAL_BLOCK(x)		(((x) & IPC_FINAL_BLOCK_MASK) \
					<< IPC_FINAL_BLOCK_SHIFT)

#घोषणा IPC_INITIAL_BLOCK_SHIFT		29
#घोषणा IPC_INITIAL_BLOCK_MASK		0x1
#घोषणा IPC_INITIAL_BLOCK(x)		(((x) & IPC_INITIAL_BLOCK_MASK) \
					<< IPC_INITIAL_BLOCK_SHIFT)
#घोषणा IPC_INITIAL_BLOCK_CLEAR		~(IPC_INITIAL_BLOCK_MASK \
					  << IPC_INITIAL_BLOCK_SHIFT)
/* Set D0ix IPC extension रेजिस्टर */
#घोषणा IPC_D0IX_WAKE_SHIFT		0
#घोषणा IPC_D0IX_WAKE_MASK		0x1
#घोषणा IPC_D0IX_WAKE(x)		(((x) & IPC_D0IX_WAKE_MASK) \
					<< IPC_D0IX_WAKE_SHIFT)

#घोषणा IPC_D0IX_STREAMING_SHIFT	1
#घोषणा IPC_D0IX_STREAMING_MASK		0x1
#घोषणा IPC_D0IX_STREAMING(x)		(((x) & IPC_D0IX_STREAMING_MASK) \
					<< IPC_D0IX_STREAMING_SHIFT)


क्रमागत skl_ipc_msg_target अणु
	IPC_FW_GEN_MSG = 0,
	IPC_MOD_MSG = 1
पूर्ण;

क्रमागत skl_ipc_msg_direction अणु
	IPC_MSG_REQUEST = 0,
	IPC_MSG_REPLY = 1
पूर्ण;

/* Global Message Types */
क्रमागत skl_ipc_glb_type अणु
	IPC_GLB_GET_FW_VERSION = 0, /* Retrieves firmware version */
	IPC_GLB_LOAD_MULTIPLE_MODS = 15,
	IPC_GLB_UNLOAD_MULTIPLE_MODS = 16,
	IPC_GLB_CREATE_PPL = 17,
	IPC_GLB_DELETE_PPL = 18,
	IPC_GLB_SET_PPL_STATE = 19,
	IPC_GLB_GET_PPL_STATE = 20,
	IPC_GLB_GET_PPL_CONTEXT_SIZE = 21,
	IPC_GLB_SAVE_PPL = 22,
	IPC_GLB_RESTORE_PPL = 23,
	IPC_GLB_LOAD_LIBRARY = 24,
	IPC_GLB_NOTIFY = 26,
	IPC_GLB_MAX_IPC_MSG_NUMBER = 31 /* Maximum message number */
पूर्ण;

क्रमागत skl_ipc_glb_reply अणु
	IPC_GLB_REPLY_SUCCESS = 0,

	IPC_GLB_REPLY_UNKNOWN_MSG_TYPE = 1,
	IPC_GLB_REPLY_ERROR_INVALID_PARAM = 2,

	IPC_GLB_REPLY_BUSY = 3,
	IPC_GLB_REPLY_PENDING = 4,
	IPC_GLB_REPLY_FAILURE = 5,
	IPC_GLB_REPLY_INVALID_REQUEST = 6,

	IPC_GLB_REPLY_OUT_OF_MEMORY = 7,
	IPC_GLB_REPLY_OUT_OF_MIPS = 8,

	IPC_GLB_REPLY_INVALID_RESOURCE_ID = 9,
	IPC_GLB_REPLY_INVALID_RESOURCE_STATE = 10,

	IPC_GLB_REPLY_MOD_MGMT_ERROR = 100,
	IPC_GLB_REPLY_MOD_LOAD_CL_FAILED = 101,
	IPC_GLB_REPLY_MOD_LOAD_INVALID_HASH = 102,

	IPC_GLB_REPLY_MOD_UNLOAD_INST_EXIST = 103,
	IPC_GLB_REPLY_MOD_NOT_INITIALIZED = 104,

	IPC_GLB_REPLY_INVALID_CONFIG_PARAM_ID = 120,
	IPC_GLB_REPLY_INVALID_CONFIG_DATA_LEN = 121,
	IPC_GLB_REPLY_GATEWAY_NOT_INITIALIZED = 140,
	IPC_GLB_REPLY_GATEWAY_NOT_EXIST = 141,
	IPC_GLB_REPLY_SCLK_ALREADY_RUNNING = 150,
	IPC_GLB_REPLY_MCLK_ALREADY_RUNNING = 151,

	IPC_GLB_REPLY_PPL_NOT_INITIALIZED = 160,
	IPC_GLB_REPLY_PPL_NOT_EXIST = 161,
	IPC_GLB_REPLY_PPL_SAVE_FAILED = 162,
	IPC_GLB_REPLY_PPL_RESTORE_FAILED = 163,

	IPC_MAX_STATUS = ((1<<IPC_IXC_STATUS_BITS)-1)
पूर्ण;

क्रमागत skl_ipc_notअगरication_type अणु
	IPC_GLB_NOTIFY_GLITCH = 0,
	IPC_GLB_NOTIFY_OVERRUN = 1,
	IPC_GLB_NOTIFY_UNDERRUN = 2,
	IPC_GLB_NOTIFY_END_STREAM = 3,
	IPC_GLB_NOTIFY_PHRASE_DETECTED = 4,
	IPC_GLB_NOTIFY_RESOURCE_EVENT = 5,
	IPC_GLB_NOTIFY_LOG_BUFFER_STATUS = 6,
	IPC_GLB_NOTIFY_TIMESTAMP_CAPTURED = 7,
	IPC_GLB_NOTIFY_FW_READY = 8
पूर्ण;

/* Module Message Types */
क्रमागत skl_ipc_module_msg अणु
	IPC_MOD_INIT_INSTANCE = 0,
	IPC_MOD_CONFIG_GET = 1,
	IPC_MOD_CONFIG_SET = 2,
	IPC_MOD_LARGE_CONFIG_GET = 3,
	IPC_MOD_LARGE_CONFIG_SET = 4,
	IPC_MOD_BIND = 5,
	IPC_MOD_UNBIND = 6,
	IPC_MOD_SET_DX = 7,
	IPC_MOD_SET_D0IX = 8
पूर्ण;

व्योम skl_ipc_tx_data_copy(काष्ठा ipc_message *msg, अक्षर *tx_data,
		माप_प्रकार tx_size)
अणु
	अगर (tx_size)
		स_नकल(msg->tx.data, tx_data, tx_size);
पूर्ण

अटल bool skl_ipc_is_dsp_busy(काष्ठा sst_dsp *dsp)
अणु
	u32 hipci;

	hipci = sst_dsp_shim_पढ़ो_unlocked(dsp, SKL_ADSP_REG_HIPCI);
	वापस (hipci & SKL_ADSP_REG_HIPCI_BUSY);
पूर्ण

/* Lock to be held by caller */
अटल व्योम skl_ipc_tx_msg(काष्ठा sst_generic_ipc *ipc, काष्ठा ipc_message *msg)
अणु
	काष्ठा skl_ipc_header *header = (काष्ठा skl_ipc_header *)(&msg->tx.header);

	अगर (msg->tx.size)
		sst_dsp_outbox_ग_लिखो(ipc->dsp, msg->tx.data, msg->tx.size);
	sst_dsp_shim_ग_लिखो_unlocked(ipc->dsp, SKL_ADSP_REG_HIPCIE,
						header->extension);
	sst_dsp_shim_ग_लिखो_unlocked(ipc->dsp, SKL_ADSP_REG_HIPCI,
		header->primary | SKL_ADSP_REG_HIPCI_BUSY);
पूर्ण

पूर्णांक skl_ipc_check_D0i0(काष्ठा sst_dsp *dsp, bool state)
अणु
	पूर्णांक ret;

	/* check D0i3 support */
	अगर (!dsp->fw_ops.set_state_D0i0)
		वापस 0;

	/* Attempt D0i0 or D0i3 based on state */
	अगर (state)
		ret = dsp->fw_ops.set_state_D0i0(dsp);
	अन्यथा
		ret = dsp->fw_ops.set_state_D0i3(dsp);

	वापस ret;
पूर्ण

अटल काष्ठा ipc_message *skl_ipc_reply_get_msg(काष्ठा sst_generic_ipc *ipc,
				u64 ipc_header)
अणु
	काष्ठा ipc_message *msg =  शून्य;
	काष्ठा skl_ipc_header *header = (काष्ठा skl_ipc_header *)(&ipc_header);

	अगर (list_empty(&ipc->rx_list)) अणु
		dev_err(ipc->dev, "ipc: rx list is empty but received 0x%x\n",
			header->primary);
		जाओ out;
	पूर्ण

	msg = list_first_entry(&ipc->rx_list, काष्ठा ipc_message, list);

	list_del(&msg->list);
out:
	वापस msg;

पूर्ण

पूर्णांक skl_ipc_process_notअगरication(काष्ठा sst_generic_ipc *ipc,
		काष्ठा skl_ipc_header header)
अणु
	काष्ठा skl_dev *skl = container_of(ipc, काष्ठा skl_dev, ipc);

	अगर (IPC_GLB_NOTIFY_MSG_TYPE(header.primary)) अणु
		चयन (IPC_GLB_NOTIFY_TYPE(header.primary)) अणु

		हाल IPC_GLB_NOTIFY_UNDERRUN:
			dev_err(ipc->dev, "FW Underrun %x\n", header.primary);
			अवरोध;

		हाल IPC_GLB_NOTIFY_RESOURCE_EVENT:
			dev_err(ipc->dev, "MCPS Budget Violation: %x\n",
						header.primary);
			अवरोध;

		हाल IPC_GLB_NOTIFY_FW_READY:
			skl->boot_complete = true;
			wake_up(&skl->boot_रुको);
			अवरोध;

		हाल IPC_GLB_NOTIFY_PHRASE_DETECTED:
			dev_dbg(ipc->dev, "***** Phrase Detected **********\n");

			/*
			 * Per HW recomendation, After phrase detection,
			 * clear the CGCTL.MISCBDCGE.
			 *
			 * This will be set back on stream closure
			 */
			skl->enable_miscbdcge(ipc->dev, false);
			skl->miscbdcg_disabled = true;
			अवरोध;

		शेष:
			dev_err(ipc->dev, "ipc: Unhandled error msg=%x\n",
						header.primary);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा skl_ipc_err_map अणु
	स्थिर अक्षर *msg;
	क्रमागत skl_ipc_glb_reply reply;
	पूर्णांक err;
पूर्ण;

अटल काष्ठा skl_ipc_err_map skl_err_map[] = अणु
	अणु"DSP out of memory", IPC_GLB_REPLY_OUT_OF_MEMORY, -ENOMEMपूर्ण,
	अणु"DSP busy", IPC_GLB_REPLY_BUSY, -EBUSYपूर्ण,
	अणु"SCLK already running", IPC_GLB_REPLY_SCLK_ALREADY_RUNNING,
			IPC_GLB_REPLY_SCLK_ALREADY_RUNNINGपूर्ण,
	अणु"MCLK already running", IPC_GLB_REPLY_MCLK_ALREADY_RUNNING,
			IPC_GLB_REPLY_MCLK_ALREADY_RUNNINGपूर्ण,
पूर्ण;

अटल पूर्णांक skl_ipc_set_reply_error_code(काष्ठा sst_generic_ipc *ipc, u32 reply)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(skl_err_map); i++) अणु
		अगर (skl_err_map[i].reply == reply)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(skl_err_map)) अणु
		dev_err(ipc->dev, "ipc FW reply: %d FW Error Code: %u\n",
				reply,
				ipc->dsp->fw_ops.get_fw_errcode(ipc->dsp));
		वापस -EINVAL;
	पूर्ण

	अगर (skl_err_map[i].err < 0)
		dev_err(ipc->dev, "ipc FW reply: %s FW Error Code: %u\n",
				skl_err_map[i].msg,
				ipc->dsp->fw_ops.get_fw_errcode(ipc->dsp));
	अन्यथा
		dev_info(ipc->dev, "ipc FW reply: %s FW Error Code: %u\n",
				skl_err_map[i].msg,
				ipc->dsp->fw_ops.get_fw_errcode(ipc->dsp));

	वापस skl_err_map[i].err;
पूर्ण

व्योम skl_ipc_process_reply(काष्ठा sst_generic_ipc *ipc,
		काष्ठा skl_ipc_header header)
अणु
	काष्ठा ipc_message *msg;
	u32 reply = header.primary & IPC_GLB_REPLY_STATUS_MASK;
	u64 *ipc_header = (u64 *)(&header);
	काष्ठा skl_dev *skl = container_of(ipc, काष्ठा skl_dev, ipc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ipc->dsp->spinlock, flags);
	msg = skl_ipc_reply_get_msg(ipc, *ipc_header);
	spin_unlock_irqrestore(&ipc->dsp->spinlock, flags);
	अगर (msg == शून्य) अणु
		dev_dbg(ipc->dev, "ipc: rx list is empty\n");
		वापस;
	पूर्ण

	msg->rx.header = *ipc_header;
	/* first process the header */
	अगर (reply == IPC_GLB_REPLY_SUCCESS) अणु
		dev_dbg(ipc->dev, "ipc FW reply %x: success\n", header.primary);
		/* copy the rx data from the mailbox */
		sst_dsp_inbox_पढ़ो(ipc->dsp, msg->rx.data, msg->rx.size);
		चयन (IPC_GLB_NOTIFY_MSG_TYPE(header.primary)) अणु
		हाल IPC_GLB_LOAD_MULTIPLE_MODS:
		हाल IPC_GLB_LOAD_LIBRARY:
			skl->mod_load_complete = true;
			skl->mod_load_status = true;
			wake_up(&skl->mod_load_रुको);
			अवरोध;

		शेष:
			अवरोध;

		पूर्ण
	पूर्ण अन्यथा अणु
		msg->त्रुटि_सं = skl_ipc_set_reply_error_code(ipc, reply);
		चयन (IPC_GLB_NOTIFY_MSG_TYPE(header.primary)) अणु
		हाल IPC_GLB_LOAD_MULTIPLE_MODS:
		हाल IPC_GLB_LOAD_LIBRARY:
			skl->mod_load_complete = true;
			skl->mod_load_status = false;
			wake_up(&skl->mod_load_रुको);
			अवरोध;

		शेष:
			अवरोध;

		पूर्ण
	पूर्ण

	spin_lock_irqsave(&ipc->dsp->spinlock, flags);
	sst_ipc_tx_msg_reply_complete(ipc, msg);
	spin_unlock_irqrestore(&ipc->dsp->spinlock, flags);
पूर्ण

irqवापस_t skl_dsp_irq_thपढ़ो_handler(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा sst_dsp *dsp = context;
	काष्ठा skl_dev *skl = dsp->thपढ़ो_context;
	काष्ठा sst_generic_ipc *ipc = &skl->ipc;
	काष्ठा skl_ipc_header header = अणु0पूर्ण;
	u32 hipcie, hipct, hipcte;
	पूर्णांक ipc_irq = 0;

	अगर (dsp->पूर्णांकr_status & SKL_ADSPIS_CL_DMA)
		skl_cldma_process_पूर्णांकr(dsp);

	/* Here we handle IPC पूर्णांकerrupts only */
	अगर (!(dsp->पूर्णांकr_status & SKL_ADSPIS_IPC))
		वापस IRQ_NONE;

	hipcie = sst_dsp_shim_पढ़ो_unlocked(dsp, SKL_ADSP_REG_HIPCIE);
	hipct = sst_dsp_shim_पढ़ो_unlocked(dsp, SKL_ADSP_REG_HIPCT);
	hipcte = sst_dsp_shim_पढ़ो_unlocked(dsp, SKL_ADSP_REG_HIPCTE);

	/* reply message from DSP */
	अगर (hipcie & SKL_ADSP_REG_HIPCIE_DONE) अणु
		sst_dsp_shim_update_bits(dsp, SKL_ADSP_REG_HIPCCTL,
			SKL_ADSP_REG_HIPCCTL_DONE, 0);

		/* clear DONE bit - tell DSP we have completed the operation */
		sst_dsp_shim_update_bits_क्रमced(dsp, SKL_ADSP_REG_HIPCIE,
			SKL_ADSP_REG_HIPCIE_DONE, SKL_ADSP_REG_HIPCIE_DONE);

		ipc_irq = 1;

		/* unmask Done पूर्णांकerrupt */
		sst_dsp_shim_update_bits(dsp, SKL_ADSP_REG_HIPCCTL,
			SKL_ADSP_REG_HIPCCTL_DONE, SKL_ADSP_REG_HIPCCTL_DONE);
	पूर्ण

	/* New message from DSP */
	अगर (hipct & SKL_ADSP_REG_HIPCT_BUSY) अणु
		header.primary = hipct;
		header.extension = hipcte;
		dev_dbg(dsp->dev, "IPC irq: Firmware respond primary:%x\n",
						header.primary);
		dev_dbg(dsp->dev, "IPC irq: Firmware respond extension:%x\n",
						header.extension);

		अगर (IPC_GLB_NOTIFY_RSP_TYPE(header.primary)) अणु
			/* Handle Immediate reply from DSP Core */
			skl_ipc_process_reply(ipc, header);
		पूर्ण अन्यथा अणु
			dev_dbg(dsp->dev, "IPC irq: Notification from firmware\n");
			skl_ipc_process_notअगरication(ipc, header);
		पूर्ण
		/* clear  busy पूर्णांकerrupt */
		sst_dsp_shim_update_bits_क्रमced(dsp, SKL_ADSP_REG_HIPCT,
			SKL_ADSP_REG_HIPCT_BUSY, SKL_ADSP_REG_HIPCT_BUSY);
		ipc_irq = 1;
	पूर्ण

	अगर (ipc_irq == 0)
		वापस IRQ_NONE;

	skl_ipc_पूर्णांक_enable(dsp);

	/* जारी to send any reमुख्यing messages... */
	schedule_work(&ipc->kwork);

	वापस IRQ_HANDLED;
पूर्ण

व्योम skl_ipc_पूर्णांक_enable(काष्ठा sst_dsp *ctx)
अणु
	sst_dsp_shim_update_bits(ctx, SKL_ADSP_REG_ADSPIC,
			SKL_ADSPIC_IPC, SKL_ADSPIC_IPC);
पूर्ण

व्योम skl_ipc_पूर्णांक_disable(काष्ठा sst_dsp *ctx)
अणु
	sst_dsp_shim_update_bits_unlocked(ctx, SKL_ADSP_REG_ADSPIC,
			SKL_ADSPIC_IPC, 0);
पूर्ण

व्योम skl_ipc_op_पूर्णांक_enable(काष्ठा sst_dsp *ctx)
अणु
	/* enable IPC DONE पूर्णांकerrupt */
	sst_dsp_shim_update_bits(ctx, SKL_ADSP_REG_HIPCCTL,
		SKL_ADSP_REG_HIPCCTL_DONE, SKL_ADSP_REG_HIPCCTL_DONE);

	/* Enable IPC BUSY पूर्णांकerrupt */
	sst_dsp_shim_update_bits(ctx, SKL_ADSP_REG_HIPCCTL,
		SKL_ADSP_REG_HIPCCTL_BUSY, SKL_ADSP_REG_HIPCCTL_BUSY);
पूर्ण

व्योम skl_ipc_op_पूर्णांक_disable(काष्ठा sst_dsp *ctx)
अणु
	/* disable IPC DONE पूर्णांकerrupt */
	sst_dsp_shim_update_bits_unlocked(ctx, SKL_ADSP_REG_HIPCCTL,
					SKL_ADSP_REG_HIPCCTL_DONE, 0);

	/* Disable IPC BUSY पूर्णांकerrupt */
	sst_dsp_shim_update_bits_unlocked(ctx, SKL_ADSP_REG_HIPCCTL,
					SKL_ADSP_REG_HIPCCTL_BUSY, 0);

पूर्ण

bool skl_ipc_पूर्णांक_status(काष्ठा sst_dsp *ctx)
अणु
	वापस sst_dsp_shim_पढ़ो_unlocked(ctx,
			SKL_ADSP_REG_ADSPIS) & SKL_ADSPIS_IPC;
पूर्ण

पूर्णांक skl_ipc_init(काष्ठा device *dev, काष्ठा skl_dev *skl)
अणु
	काष्ठा sst_generic_ipc *ipc;
	पूर्णांक err;

	ipc = &skl->ipc;
	ipc->dsp = skl->dsp;
	ipc->dev = dev;

	ipc->tx_data_max_size = SKL_ADSP_W1_SZ;
	ipc->rx_data_max_size = SKL_ADSP_W0_UP_SZ;

	err = sst_ipc_init(ipc);
	अगर (err)
		वापस err;

	ipc->ops.tx_msg = skl_ipc_tx_msg;
	ipc->ops.tx_data_copy = skl_ipc_tx_data_copy;
	ipc->ops.is_dsp_busy = skl_ipc_is_dsp_busy;

	वापस 0;
पूर्ण

व्योम skl_ipc_मुक्त(काष्ठा sst_generic_ipc *ipc)
अणु
	/* Disable IPC DONE पूर्णांकerrupt */
	sst_dsp_shim_update_bits(ipc->dsp, SKL_ADSP_REG_HIPCCTL,
		SKL_ADSP_REG_HIPCCTL_DONE, 0);

	/* Disable IPC BUSY पूर्णांकerrupt */
	sst_dsp_shim_update_bits(ipc->dsp, SKL_ADSP_REG_HIPCCTL,
		SKL_ADSP_REG_HIPCCTL_BUSY, 0);

	sst_ipc_fini(ipc);
पूर्ण

पूर्णांक skl_ipc_create_pipeline(काष्ठा sst_generic_ipc *ipc,
		u16 ppl_mem_size, u8 ppl_type, u8 instance_id, u8 lp_mode)
अणु
	काष्ठा skl_ipc_header header = अणु0पूर्ण;
	काष्ठा sst_ipc_message request = अणु0पूर्ण;
	पूर्णांक ret;

	header.primary = IPC_MSG_TARGET(IPC_FW_GEN_MSG);
	header.primary |= IPC_MSG_सूची(IPC_MSG_REQUEST);
	header.primary |= IPC_GLB_TYPE(IPC_GLB_CREATE_PPL);
	header.primary |= IPC_INSTANCE_ID(instance_id);
	header.primary |= IPC_PPL_TYPE(ppl_type);
	header.primary |= IPC_PPL_MEM_SIZE(ppl_mem_size);

	header.extension = IPC_PPL_LP_MODE(lp_mode);
	request.header = *(u64 *)(&header);

	dev_dbg(ipc->dev, "In %s header=%d\n", __func__, header.primary);
	ret = sst_ipc_tx_message_रुको(ipc, request, शून्य);
	अगर (ret < 0) अणु
		dev_err(ipc->dev, "ipc: create pipeline fail, err: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(skl_ipc_create_pipeline);

पूर्णांक skl_ipc_delete_pipeline(काष्ठा sst_generic_ipc *ipc, u8 instance_id)
अणु
	काष्ठा skl_ipc_header header = अणु0पूर्ण;
	काष्ठा sst_ipc_message request = अणु0पूर्ण;
	पूर्णांक ret;

	header.primary = IPC_MSG_TARGET(IPC_FW_GEN_MSG);
	header.primary |= IPC_MSG_सूची(IPC_MSG_REQUEST);
	header.primary |= IPC_GLB_TYPE(IPC_GLB_DELETE_PPL);
	header.primary |= IPC_INSTANCE_ID(instance_id);
	request.header = *(u64 *)(&header);

	dev_dbg(ipc->dev, "In %s header=%d\n", __func__, header.primary);
	ret = sst_ipc_tx_message_रुको(ipc, request, शून्य);
	अगर (ret < 0) अणु
		dev_err(ipc->dev, "ipc: delete pipeline failed, err %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(skl_ipc_delete_pipeline);

पूर्णांक skl_ipc_set_pipeline_state(काष्ठा sst_generic_ipc *ipc,
		u8 instance_id, क्रमागत skl_ipc_pipeline_state state)
अणु
	काष्ठा skl_ipc_header header = अणु0पूर्ण;
	काष्ठा sst_ipc_message request = अणु0पूर्ण;
	पूर्णांक ret;

	header.primary = IPC_MSG_TARGET(IPC_FW_GEN_MSG);
	header.primary |= IPC_MSG_सूची(IPC_MSG_REQUEST);
	header.primary |= IPC_GLB_TYPE(IPC_GLB_SET_PPL_STATE);
	header.primary |= IPC_INSTANCE_ID(instance_id);
	header.primary |= IPC_PPL_STATE(state);
	request.header = *(u64 *)(&header);

	dev_dbg(ipc->dev, "In %s header=%d\n", __func__, header.primary);
	ret = sst_ipc_tx_message_रुको(ipc, request, शून्य);
	अगर (ret < 0) अणु
		dev_err(ipc->dev, "ipc: set pipeline state failed, err: %d\n", ret);
		वापस ret;
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(skl_ipc_set_pipeline_state);

पूर्णांक
skl_ipc_save_pipeline(काष्ठा sst_generic_ipc *ipc, u8 instance_id, पूर्णांक dma_id)
अणु
	काष्ठा skl_ipc_header header = अणु0पूर्ण;
	काष्ठा sst_ipc_message request = अणु0पूर्ण;
	पूर्णांक ret;

	header.primary = IPC_MSG_TARGET(IPC_FW_GEN_MSG);
	header.primary |= IPC_MSG_सूची(IPC_MSG_REQUEST);
	header.primary |= IPC_GLB_TYPE(IPC_GLB_SAVE_PPL);
	header.primary |= IPC_INSTANCE_ID(instance_id);

	header.extension = IPC_DMA_ID(dma_id);
	request.header = *(u64 *)(&header);

	dev_dbg(ipc->dev, "In %s header=%d\n", __func__, header.primary);
	ret = sst_ipc_tx_message_रुको(ipc, request, शून्य);
	अगर (ret < 0) अणु
		dev_err(ipc->dev, "ipc: save pipeline failed, err: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(skl_ipc_save_pipeline);

पूर्णांक skl_ipc_restore_pipeline(काष्ठा sst_generic_ipc *ipc, u8 instance_id)
अणु
	काष्ठा skl_ipc_header header = अणु0पूर्ण;
	काष्ठा sst_ipc_message request = अणु0पूर्ण;
	पूर्णांक ret;

	header.primary = IPC_MSG_TARGET(IPC_FW_GEN_MSG);
	header.primary |= IPC_MSG_सूची(IPC_MSG_REQUEST);
	header.primary |= IPC_GLB_TYPE(IPC_GLB_RESTORE_PPL);
	header.primary |= IPC_INSTANCE_ID(instance_id);
	request.header = *(u64 *)(&header);

	dev_dbg(ipc->dev, "In %s header=%d\n", __func__, header.primary);
	ret = sst_ipc_tx_message_रुको(ipc, request, शून्य);
	अगर (ret < 0) अणु
		dev_err(ipc->dev, "ipc: restore  pipeline failed, err: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(skl_ipc_restore_pipeline);

पूर्णांक skl_ipc_set_dx(काष्ठा sst_generic_ipc *ipc, u8 instance_id,
		u16 module_id, काष्ठा skl_ipc_dxstate_info *dx)
अणु
	काष्ठा skl_ipc_header header = अणु0पूर्ण;
	काष्ठा sst_ipc_message request;
	पूर्णांक ret;

	header.primary = IPC_MSG_TARGET(IPC_MOD_MSG);
	header.primary |= IPC_MSG_सूची(IPC_MSG_REQUEST);
	header.primary |= IPC_GLB_TYPE(IPC_MOD_SET_DX);
	header.primary |= IPC_MOD_INSTANCE_ID(instance_id);
	header.primary |= IPC_MOD_ID(module_id);

	request.header = *(u64 *)(&header);
	request.data = dx;
	request.size = माप(*dx);

	dev_dbg(ipc->dev, "In %s primary =%x ext=%x\n", __func__,
			 header.primary, header.extension);
	ret = sst_ipc_tx_message_रुको(ipc, request, शून्य);
	अगर (ret < 0) अणु
		dev_err(ipc->dev, "ipc: set dx failed, err %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(skl_ipc_set_dx);

पूर्णांक skl_ipc_init_instance(काष्ठा sst_generic_ipc *ipc,
		काष्ठा skl_ipc_init_instance_msg *msg, व्योम *param_data)
अणु
	काष्ठा skl_ipc_header header = अणु0पूर्ण;
	काष्ठा sst_ipc_message request;
	पूर्णांक ret;
	u32 *buffer = (u32 *)param_data;
	 /* param_block_size must be in dwords */
	u16 param_block_size = msg->param_data_size / माप(u32);

	prपूर्णांक_hex_dump_debug("Param data:", DUMP_PREFIX_NONE,
		16, 4, buffer, param_block_size, false);

	header.primary = IPC_MSG_TARGET(IPC_MOD_MSG);
	header.primary |= IPC_MSG_सूची(IPC_MSG_REQUEST);
	header.primary |= IPC_GLB_TYPE(IPC_MOD_INIT_INSTANCE);
	header.primary |= IPC_MOD_INSTANCE_ID(msg->instance_id);
	header.primary |= IPC_MOD_ID(msg->module_id);

	header.extension = IPC_CORE_ID(msg->core_id);
	header.extension |= IPC_PPL_INSTANCE_ID(msg->ppl_instance_id);
	header.extension |= IPC_PARAM_BLOCK_SIZE(param_block_size);
	header.extension |= IPC_DOMAIN(msg->करोमुख्य);

	request.header = *(u64 *)(&header);
	request.data = param_data;
	request.size = msg->param_data_size;

	dev_dbg(ipc->dev, "In %s primary =%x ext=%x\n", __func__,
			 header.primary, header.extension);
	ret = sst_ipc_tx_message_रुको(ipc, request, शून्य);

	अगर (ret < 0) अणु
		dev_err(ipc->dev, "ipc: init instance failed\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(skl_ipc_init_instance);

पूर्णांक skl_ipc_bind_unbind(काष्ठा sst_generic_ipc *ipc,
		काष्ठा skl_ipc_bind_unbind_msg *msg)
अणु
	काष्ठा skl_ipc_header header = अणु0पूर्ण;
	काष्ठा sst_ipc_message request = अणु0पूर्ण;
	u8 bind_unbind = msg->bind ? IPC_MOD_BIND : IPC_MOD_UNBIND;
	पूर्णांक ret;

	header.primary = IPC_MSG_TARGET(IPC_MOD_MSG);
	header.primary |= IPC_MSG_सूची(IPC_MSG_REQUEST);
	header.primary |= IPC_GLB_TYPE(bind_unbind);
	header.primary |= IPC_MOD_INSTANCE_ID(msg->instance_id);
	header.primary |= IPC_MOD_ID(msg->module_id);

	header.extension = IPC_DST_MOD_ID(msg->dst_module_id);
	header.extension |= IPC_DST_MOD_INSTANCE_ID(msg->dst_instance_id);
	header.extension |= IPC_DST_QUEUE(msg->dst_queue);
	header.extension |= IPC_SRC_QUEUE(msg->src_queue);
	request.header = *(u64 *)(&header);

	dev_dbg(ipc->dev, "In %s hdr=%x ext=%x\n", __func__, header.primary,
			 header.extension);
	ret = sst_ipc_tx_message_रुको(ipc, request, शून्य);
	अगर (ret < 0) अणु
		dev_err(ipc->dev, "ipc: bind/unbind failed\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(skl_ipc_bind_unbind);

/*
 * In order to load a module we need to send IPC to initiate that. DMA will
 * perक्रमmed to load the module memory. The FW supports multiple module load
 * at single shot, so we can send IPC with N modules represented by
 * module_cnt
 */
पूर्णांक skl_ipc_load_modules(काष्ठा sst_generic_ipc *ipc,
				u8 module_cnt, व्योम *data)
अणु
	काष्ठा skl_ipc_header header = अणु0पूर्ण;
	काष्ठा sst_ipc_message request;
	पूर्णांक ret;

	header.primary = IPC_MSG_TARGET(IPC_FW_GEN_MSG);
	header.primary |= IPC_MSG_सूची(IPC_MSG_REQUEST);
	header.primary |= IPC_GLB_TYPE(IPC_GLB_LOAD_MULTIPLE_MODS);
	header.primary |= IPC_LOAD_MODULE_CNT(module_cnt);

	request.header = *(u64 *)(&header);
	request.data = data;
	request.size = माप(u16) * module_cnt;

	ret = sst_ipc_tx_message_noरुको(ipc, request);
	अगर (ret < 0)
		dev_err(ipc->dev, "ipc: load modules failed :%d\n", ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(skl_ipc_load_modules);

पूर्णांक skl_ipc_unload_modules(काष्ठा sst_generic_ipc *ipc, u8 module_cnt,
							व्योम *data)
अणु
	काष्ठा skl_ipc_header header = अणु0पूर्ण;
	काष्ठा sst_ipc_message request;
	पूर्णांक ret;

	header.primary = IPC_MSG_TARGET(IPC_FW_GEN_MSG);
	header.primary |= IPC_MSG_सूची(IPC_MSG_REQUEST);
	header.primary |= IPC_GLB_TYPE(IPC_GLB_UNLOAD_MULTIPLE_MODS);
	header.primary |= IPC_LOAD_MODULE_CNT(module_cnt);

	request.header = *(u64 *)(&header);
	request.data = data;
	request.size = माप(u16) * module_cnt;

	ret = sst_ipc_tx_message_रुको(ipc, request, शून्य);
	अगर (ret < 0)
		dev_err(ipc->dev, "ipc: unload modules failed :%d\n", ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(skl_ipc_unload_modules);

पूर्णांक skl_ipc_set_large_config(काष्ठा sst_generic_ipc *ipc,
		काष्ठा skl_ipc_large_config_msg *msg, u32 *param)
अणु
	काष्ठा skl_ipc_header header = अणु0पूर्ण;
	काष्ठा sst_ipc_message request;
	पूर्णांक ret = 0;
	माप_प्रकार sz_reमुख्यing, tx_size, data_offset;

	header.primary = IPC_MSG_TARGET(IPC_MOD_MSG);
	header.primary |= IPC_MSG_सूची(IPC_MSG_REQUEST);
	header.primary |= IPC_GLB_TYPE(IPC_MOD_LARGE_CONFIG_SET);
	header.primary |= IPC_MOD_INSTANCE_ID(msg->instance_id);
	header.primary |= IPC_MOD_ID(msg->module_id);

	header.extension = IPC_DATA_OFFSET_SZ(msg->param_data_size);
	header.extension |= IPC_LARGE_PARAM_ID(msg->large_param_id);
	header.extension |= IPC_FINAL_BLOCK(0);
	header.extension |= IPC_INITIAL_BLOCK(1);

	sz_reमुख्यing = msg->param_data_size;
	data_offset = 0;
	जबतक (sz_reमुख्यing != 0) अणु
		tx_size = sz_reमुख्यing > SKL_ADSP_W1_SZ
				? SKL_ADSP_W1_SZ : sz_reमुख्यing;
		अगर (tx_size == sz_reमुख्यing)
			header.extension |= IPC_FINAL_BLOCK(1);

		dev_dbg(ipc->dev, "In %s primary=%#x ext=%#x\n", __func__,
			header.primary, header.extension);
		dev_dbg(ipc->dev, "transmitting offset: %#x, size: %#x\n",
			(अचिन्हित)data_offset, (अचिन्हित)tx_size);

		request.header = *(u64 *)(&header);
		request.data = ((अक्षर *)param) + data_offset;
		request.size = tx_size;
		ret = sst_ipc_tx_message_रुको(ipc, request, शून्य);
		अगर (ret < 0) अणु
			dev_err(ipc->dev,
				"ipc: set large config fail, err: %d\n", ret);
			वापस ret;
		पूर्ण
		sz_reमुख्यing -= tx_size;
		data_offset = msg->param_data_size - sz_reमुख्यing;

		/* clear the fields */
		header.extension &= IPC_INITIAL_BLOCK_CLEAR;
		header.extension &= IPC_DATA_OFFSET_SZ_CLEAR;
		/* fill the fields */
		header.extension |= IPC_INITIAL_BLOCK(0);
		header.extension |= IPC_DATA_OFFSET_SZ(data_offset);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(skl_ipc_set_large_config);

पूर्णांक skl_ipc_get_large_config(काष्ठा sst_generic_ipc *ipc,
		काष्ठा skl_ipc_large_config_msg *msg,
		u32 **payload, माप_प्रकार *bytes)
अणु
	काष्ठा skl_ipc_header header = अणु0पूर्ण;
	काष्ठा sst_ipc_message request, reply = अणु0पूर्ण;
	अचिन्हित पूर्णांक *buf;
	पूर्णांक ret;

	reply.data = kzalloc(SKL_ADSP_W1_SZ, GFP_KERNEL);
	अगर (!reply.data)
		वापस -ENOMEM;

	header.primary = IPC_MSG_TARGET(IPC_MOD_MSG);
	header.primary |= IPC_MSG_सूची(IPC_MSG_REQUEST);
	header.primary |= IPC_GLB_TYPE(IPC_MOD_LARGE_CONFIG_GET);
	header.primary |= IPC_MOD_INSTANCE_ID(msg->instance_id);
	header.primary |= IPC_MOD_ID(msg->module_id);

	header.extension = IPC_DATA_OFFSET_SZ(msg->param_data_size);
	header.extension |= IPC_LARGE_PARAM_ID(msg->large_param_id);
	header.extension |= IPC_FINAL_BLOCK(1);
	header.extension |= IPC_INITIAL_BLOCK(1);

	request.header = *(u64 *)&header;
	request.data = *payload;
	request.size = *bytes;
	reply.size = SKL_ADSP_W1_SZ;

	ret = sst_ipc_tx_message_रुको(ipc, request, &reply);
	अगर (ret < 0)
		dev_err(ipc->dev, "ipc: get large config fail, err: %d\n", ret);

	reply.size = (reply.header >> 32) & IPC_DATA_OFFSET_SZ_MASK;
	buf = kपुनः_स्मृति(reply.data, reply.size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	*payload = buf;
	*bytes = reply.size;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(skl_ipc_get_large_config);

पूर्णांक skl_sst_ipc_load_library(काष्ठा sst_generic_ipc *ipc,
				u8 dma_id, u8 table_id, bool रुको)
अणु
	काष्ठा skl_ipc_header header = अणु0पूर्ण;
	काष्ठा sst_ipc_message request = अणु0पूर्ण;
	पूर्णांक ret = 0;

	header.primary = IPC_MSG_TARGET(IPC_FW_GEN_MSG);
	header.primary |= IPC_MSG_सूची(IPC_MSG_REQUEST);
	header.primary |= IPC_GLB_TYPE(IPC_GLB_LOAD_LIBRARY);
	header.primary |= IPC_MOD_INSTANCE_ID(table_id);
	header.primary |= IPC_MOD_ID(dma_id);
	request.header = *(u64 *)(&header);

	अगर (रुको)
		ret = sst_ipc_tx_message_रुको(ipc, request, शून्य);
	अन्यथा
		ret = sst_ipc_tx_message_noरुको(ipc, request);

	अगर (ret < 0)
		dev_err(ipc->dev, "ipc: load lib failed\n");

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(skl_sst_ipc_load_library);

पूर्णांक skl_ipc_set_d0ix(काष्ठा sst_generic_ipc *ipc, काष्ठा skl_ipc_d0ix_msg *msg)
अणु
	काष्ठा skl_ipc_header header = अणु0पूर्ण;
	काष्ठा sst_ipc_message request = अणु0पूर्ण;
	पूर्णांक ret;

	header.primary = IPC_MSG_TARGET(IPC_MOD_MSG);
	header.primary |= IPC_MSG_सूची(IPC_MSG_REQUEST);
	header.primary |= IPC_GLB_TYPE(IPC_MOD_SET_D0IX);
	header.primary |= IPC_MOD_INSTANCE_ID(msg->instance_id);
	header.primary |= IPC_MOD_ID(msg->module_id);

	header.extension = IPC_D0IX_WAKE(msg->wake);
	header.extension |= IPC_D0IX_STREAMING(msg->streaming);
	request.header = *(u64 *)(&header);

	dev_dbg(ipc->dev, "In %s primary=%x ext=%x\n", __func__,
			header.primary,	header.extension);

	/*
	 * Use the nopm IPC here as we करोnt want it checking क्रम D0iX
	 */
	ret = sst_ipc_tx_message_nopm(ipc, request, शून्य);
	अगर (ret < 0)
		dev_err(ipc->dev, "ipc: set d0ix failed, err %d\n", ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(skl_ipc_set_d0ix);
