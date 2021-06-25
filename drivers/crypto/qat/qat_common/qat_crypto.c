<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2014 - 2020 Intel Corporation */
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश "adf_accel_devices.h"
#समावेश "adf_common_drv.h"
#समावेश "adf_transport.h"
#समावेश "adf_transport_access_macros.h"
#समावेश "adf_cfg.h"
#समावेश "adf_cfg_strings.h"
#समावेश "qat_crypto.h"
#समावेश "icp_qat_fw.h"

#घोषणा SEC ADF_KERNEL_SEC

अटल काष्ठा service_hndl qat_crypto;

व्योम qat_crypto_put_instance(काष्ठा qat_crypto_instance *inst)
अणु
	atomic_dec(&inst->refctr);
	adf_dev_put(inst->accel_dev);
पूर्ण

अटल पूर्णांक qat_crypto_मुक्त_instances(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा qat_crypto_instance *inst, *पंचांगp;
	पूर्णांक i;

	list_क्रम_each_entry_safe(inst, पंचांगp, &accel_dev->crypto_list, list) अणु
		क्रम (i = 0; i < atomic_पढ़ो(&inst->refctr); i++)
			qat_crypto_put_instance(inst);

		अगर (inst->sym_tx)
			adf_हटाओ_ring(inst->sym_tx);

		अगर (inst->sym_rx)
			adf_हटाओ_ring(inst->sym_rx);

		अगर (inst->pke_tx)
			adf_हटाओ_ring(inst->pke_tx);

		अगर (inst->pke_rx)
			adf_हटाओ_ring(inst->pke_rx);

		list_del(&inst->list);
		kमुक्त(inst);
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा qat_crypto_instance *qat_crypto_get_instance_node(पूर्णांक node)
अणु
	काष्ठा adf_accel_dev *accel_dev = शून्य, *पंचांगp_dev;
	काष्ठा qat_crypto_instance *inst = शून्य, *पंचांगp_inst;
	अचिन्हित दीर्घ best = ~0;

	list_क्रम_each_entry(पंचांगp_dev, adf_devmgr_get_head(), list) अणु
		अचिन्हित दीर्घ ctr;

		अगर ((node == dev_to_node(&GET_DEV(पंचांगp_dev)) ||
		     dev_to_node(&GET_DEV(पंचांगp_dev)) < 0) &&
		    adf_dev_started(पंचांगp_dev) &&
		    !list_empty(&पंचांगp_dev->crypto_list)) अणु
			ctr = atomic_पढ़ो(&पंचांगp_dev->ref_count);
			अगर (best > ctr) अणु
				accel_dev = पंचांगp_dev;
				best = ctr;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!accel_dev) अणु
		pr_info("QAT: Could not find a device on node %d\n", node);
		/* Get any started device */
		list_क्रम_each_entry(पंचांगp_dev, adf_devmgr_get_head(), list) अणु
			अगर (adf_dev_started(पंचांगp_dev) &&
			    !list_empty(&पंचांगp_dev->crypto_list)) अणु
				accel_dev = पंचांगp_dev;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!accel_dev)
		वापस शून्य;

	best = ~0;
	list_क्रम_each_entry(पंचांगp_inst, &accel_dev->crypto_list, list) अणु
		अचिन्हित दीर्घ ctr;

		ctr = atomic_पढ़ो(&पंचांगp_inst->refctr);
		अगर (best > ctr) अणु
			inst = पंचांगp_inst;
			best = ctr;
		पूर्ण
	पूर्ण
	अगर (inst) अणु
		अगर (adf_dev_get(accel_dev)) अणु
			dev_err(&GET_DEV(accel_dev), "Could not increment dev refctr\n");
			वापस शून्य;
		पूर्ण
		atomic_inc(&inst->refctr);
	पूर्ण
	वापस inst;
पूर्ण

/**
 * qat_crypto_dev_config() - create dev config required to create crypto inst.
 *
 * @accel_dev: Poपूर्णांकer to acceleration device.
 *
 * Function creates device configuration required to create crypto instances
 *
 * Return: 0 on success, error code otherwise.
 */
पूर्णांक qat_crypto_dev_config(काष्ठा adf_accel_dev *accel_dev)
अणु
	अक्षर key[ADF_CFG_MAX_KEY_LEN_IN_BYTES];
	पूर्णांक banks = GET_MAX_BANKS(accel_dev);
	पूर्णांक cpus = num_online_cpus();
	अचिन्हित दीर्घ val;
	पूर्णांक instances;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (adf_hw_dev_has_crypto(accel_dev))
		instances = min(cpus, banks);
	अन्यथा
		instances = 0;

	ret = adf_cfg_section_add(accel_dev, ADF_KERNEL_SEC);
	अगर (ret)
		जाओ err;

	ret = adf_cfg_section_add(accel_dev, "Accelerator0");
	अगर (ret)
		जाओ err;

	क्रम (i = 0; i < instances; i++) अणु
		val = i;
		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_ASYM_BANK_NUM, i);
		ret = adf_cfg_add_key_value_param(accel_dev, ADF_KERNEL_SEC,
						  key, &val, ADF_DEC);
		अगर (ret)
			जाओ err;

		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_SYM_BANK_NUM, i);
		ret = adf_cfg_add_key_value_param(accel_dev, ADF_KERNEL_SEC,
						  key, &val, ADF_DEC);
		अगर (ret)
			जाओ err;

		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_ETRMGR_CORE_AFFINITY,
			 i);
		ret = adf_cfg_add_key_value_param(accel_dev, ADF_KERNEL_SEC,
						  key, &val, ADF_DEC);
		अगर (ret)
			जाओ err;

		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_ASYM_SIZE, i);
		val = 128;
		ret = adf_cfg_add_key_value_param(accel_dev, ADF_KERNEL_SEC,
						  key, &val, ADF_DEC);
		अगर (ret)
			जाओ err;

		val = 512;
		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_SYM_SIZE, i);
		ret = adf_cfg_add_key_value_param(accel_dev, ADF_KERNEL_SEC,
						  key, &val, ADF_DEC);
		अगर (ret)
			जाओ err;

		val = 0;
		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_ASYM_TX, i);
		ret = adf_cfg_add_key_value_param(accel_dev, ADF_KERNEL_SEC,
						  key, &val, ADF_DEC);
		अगर (ret)
			जाओ err;

		val = 2;
		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_SYM_TX, i);
		ret = adf_cfg_add_key_value_param(accel_dev, ADF_KERNEL_SEC,
						  key, &val, ADF_DEC);
		अगर (ret)
			जाओ err;

		val = 8;
		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_ASYM_RX, i);
		ret = adf_cfg_add_key_value_param(accel_dev, ADF_KERNEL_SEC,
						  key, &val, ADF_DEC);
		अगर (ret)
			जाओ err;

		val = 10;
		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_SYM_RX, i);
		ret = adf_cfg_add_key_value_param(accel_dev, ADF_KERNEL_SEC,
						  key, &val, ADF_DEC);
		अगर (ret)
			जाओ err;

		val = ADF_COALESCING_DEF_TIME;
		snम_लिखो(key, माप(key), ADF_ETRMGR_COALESCE_TIMER_FORMAT, i);
		ret = adf_cfg_add_key_value_param(accel_dev, "Accelerator0",
						  key, &val, ADF_DEC);
		अगर (ret)
			जाओ err;
	पूर्ण

	val = i;
	ret = adf_cfg_add_key_value_param(accel_dev, ADF_KERNEL_SEC, ADF_NUM_CY,
					  &val, ADF_DEC);
	अगर (ret)
		जाओ err;

	set_bit(ADF_STATUS_CONFIGURED, &accel_dev->status);
	वापस 0;
err:
	dev_err(&GET_DEV(accel_dev), "Failed to start QAT accel dev\n");
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(qat_crypto_dev_config);

अटल पूर्णांक qat_crypto_create_instances(काष्ठा adf_accel_dev *accel_dev)
अणु
	अचिन्हित दीर्घ num_inst, num_msg_sym, num_msg_asym;
	अक्षर key[ADF_CFG_MAX_KEY_LEN_IN_BYTES];
	अक्षर val[ADF_CFG_MAX_VAL_LEN_IN_BYTES];
	अचिन्हित दीर्घ sym_bank, asym_bank;
	काष्ठा qat_crypto_instance *inst;
	पूर्णांक msg_size;
	पूर्णांक ret;
	पूर्णांक i;

	INIT_LIST_HEAD(&accel_dev->crypto_list);
	ret = adf_cfg_get_param_value(accel_dev, SEC, ADF_NUM_CY, val);
	अगर (ret)
		वापस ret;

	ret = kम_से_अदीर्घ(val, 0, &num_inst);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < num_inst; i++) अणु
		inst = kzalloc_node(माप(*inst), GFP_KERNEL,
				    dev_to_node(&GET_DEV(accel_dev)));
		अगर (!inst) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		list_add_tail(&inst->list, &accel_dev->crypto_list);
		inst->id = i;
		atomic_set(&inst->refctr, 0);
		inst->accel_dev = accel_dev;

		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_SYM_BANK_NUM, i);
		ret = adf_cfg_get_param_value(accel_dev, SEC, key, val);
		अगर (ret)
			जाओ err;

		ret = kम_से_अदीर्घ(val, 10, &sym_bank);
		अगर (ret)
			जाओ err;

		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_ASYM_BANK_NUM, i);
		ret = adf_cfg_get_param_value(accel_dev, SEC, key, val);
		अगर (ret)
			जाओ err;

		ret = kम_से_अदीर्घ(val, 10, &asym_bank);
		अगर (ret)
			जाओ err;

		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_SYM_SIZE, i);
		ret = adf_cfg_get_param_value(accel_dev, SEC, key, val);
		अगर (ret)
			जाओ err;

		ret = kम_से_अदीर्घ(val, 10, &num_msg_sym);
		अगर (ret)
			जाओ err;

		num_msg_sym = num_msg_sym >> 1;

		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_ASYM_SIZE, i);
		ret = adf_cfg_get_param_value(accel_dev, SEC, key, val);
		अगर (ret)
			जाओ err;

		ret = kम_से_अदीर्घ(val, 10, &num_msg_asym);
		अगर (ret)
			जाओ err;
		num_msg_asym = num_msg_asym >> 1;

		msg_size = ICP_QAT_FW_REQ_DEFAULT_SZ;
		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_SYM_TX, i);
		ret = adf_create_ring(accel_dev, SEC, sym_bank, num_msg_sym,
				      msg_size, key, शून्य, 0, &inst->sym_tx);
		अगर (ret)
			जाओ err;

		msg_size = msg_size >> 1;
		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_ASYM_TX, i);
		ret = adf_create_ring(accel_dev, SEC, asym_bank, num_msg_asym,
				      msg_size, key, शून्य, 0, &inst->pke_tx);
		अगर (ret)
			जाओ err;

		msg_size = ICP_QAT_FW_RESP_DEFAULT_SZ;
		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_SYM_RX, i);
		ret = adf_create_ring(accel_dev, SEC, sym_bank, num_msg_sym,
				      msg_size, key, qat_alg_callback, 0,
				      &inst->sym_rx);
		अगर (ret)
			जाओ err;

		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_ASYM_RX, i);
		ret = adf_create_ring(accel_dev, SEC, asym_bank, num_msg_asym,
				      msg_size, key, qat_alg_asym_callback, 0,
				      &inst->pke_rx);
		अगर (ret)
			जाओ err;
	पूर्ण
	वापस 0;
err:
	qat_crypto_मुक्त_instances(accel_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक qat_crypto_init(काष्ठा adf_accel_dev *accel_dev)
अणु
	अगर (qat_crypto_create_instances(accel_dev))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक qat_crypto_shutकरोwn(काष्ठा adf_accel_dev *accel_dev)
अणु
	वापस qat_crypto_मुक्त_instances(accel_dev);
पूर्ण

अटल पूर्णांक qat_crypto_event_handler(काष्ठा adf_accel_dev *accel_dev,
				    क्रमागत adf_event event)
अणु
	पूर्णांक ret;

	चयन (event) अणु
	हाल ADF_EVENT_INIT:
		ret = qat_crypto_init(accel_dev);
		अवरोध;
	हाल ADF_EVENT_SHUTDOWN:
		ret = qat_crypto_shutकरोwn(accel_dev);
		अवरोध;
	हाल ADF_EVENT_RESTARTING:
	हाल ADF_EVENT_RESTARTED:
	हाल ADF_EVENT_START:
	हाल ADF_EVENT_STOP:
	शेष:
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक qat_crypto_रेजिस्टर(व्योम)
अणु
	स_रखो(&qat_crypto, 0, माप(qat_crypto));
	qat_crypto.event_hld = qat_crypto_event_handler;
	qat_crypto.name = "qat_crypto";
	वापस adf_service_रेजिस्टर(&qat_crypto);
पूर्ण

पूर्णांक qat_crypto_unरेजिस्टर(व्योम)
अणु
	वापस adf_service_unरेजिस्टर(&qat_crypto);
पूर्ण
