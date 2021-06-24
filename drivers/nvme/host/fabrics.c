<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NVMe over Fabrics common host code.
 * Copyright (c) 2015-2016 HGST, a Western Digital Company.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/init.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/parser.h>
#समावेश <linux/seq_file.h>
#समावेश "nvme.h"
#समावेश "fabrics.h"

अटल LIST_HEAD(nvmf_transports);
अटल DECLARE_RWSEM(nvmf_transports_rwsem);

अटल LIST_HEAD(nvmf_hosts);
अटल DEFINE_MUTEX(nvmf_hosts_mutex);

अटल काष्ठा nvmf_host *nvmf_शेष_host;

अटल काष्ठा nvmf_host *__nvmf_host_find(स्थिर अक्षर *hostnqn)
अणु
	काष्ठा nvmf_host *host;

	list_क्रम_each_entry(host, &nvmf_hosts, list) अणु
		अगर (!म_भेद(host->nqn, hostnqn))
			वापस host;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा nvmf_host *nvmf_host_add(स्थिर अक्षर *hostnqn)
अणु
	काष्ठा nvmf_host *host;

	mutex_lock(&nvmf_hosts_mutex);
	host = __nvmf_host_find(hostnqn);
	अगर (host) अणु
		kref_get(&host->ref);
		जाओ out_unlock;
	पूर्ण

	host = kदो_स्मृति(माप(*host), GFP_KERNEL);
	अगर (!host)
		जाओ out_unlock;

	kref_init(&host->ref);
	strlcpy(host->nqn, hostnqn, NVMF_NQN_SIZE);

	list_add_tail(&host->list, &nvmf_hosts);
out_unlock:
	mutex_unlock(&nvmf_hosts_mutex);
	वापस host;
पूर्ण

अटल काष्ठा nvmf_host *nvmf_host_शेष(व्योम)
अणु
	काष्ठा nvmf_host *host;

	host = kदो_स्मृति(माप(*host), GFP_KERNEL);
	अगर (!host)
		वापस शून्य;

	kref_init(&host->ref);
	uuid_gen(&host->id);
	snम_लिखो(host->nqn, NVMF_NQN_SIZE,
		"nqn.2014-08.org.nvmexpress:uuid:%pUb", &host->id);

	mutex_lock(&nvmf_hosts_mutex);
	list_add_tail(&host->list, &nvmf_hosts);
	mutex_unlock(&nvmf_hosts_mutex);

	वापस host;
पूर्ण

अटल व्योम nvmf_host_destroy(काष्ठा kref *ref)
अणु
	काष्ठा nvmf_host *host = container_of(ref, काष्ठा nvmf_host, ref);

	mutex_lock(&nvmf_hosts_mutex);
	list_del(&host->list);
	mutex_unlock(&nvmf_hosts_mutex);

	kमुक्त(host);
पूर्ण

अटल व्योम nvmf_host_put(काष्ठा nvmf_host *host)
अणु
	अगर (host)
		kref_put(&host->ref, nvmf_host_destroy);
पूर्ण

/**
 * nvmf_get_address() -  Get address/port
 * @ctrl:	Host NVMe controller instance which we got the address
 * @buf:	OUTPUT parameter that will contain the address/port
 * @size:	buffer size
 */
पूर्णांक nvmf_get_address(काष्ठा nvme_ctrl *ctrl, अक्षर *buf, पूर्णांक size)
अणु
	पूर्णांक len = 0;

	अगर (ctrl->opts->mask & NVMF_OPT_TRADDR)
		len += scnम_लिखो(buf, size, "traddr=%s", ctrl->opts->traddr);
	अगर (ctrl->opts->mask & NVMF_OPT_TRSVCID)
		len += scnम_लिखो(buf + len, size - len, "%strsvcid=%s",
				(len) ? "," : "", ctrl->opts->trsvcid);
	अगर (ctrl->opts->mask & NVMF_OPT_HOST_TRADDR)
		len += scnम_लिखो(buf + len, size - len, "%shost_traddr=%s",
				(len) ? "," : "", ctrl->opts->host_traddr);
	len += scnम_लिखो(buf + len, size - len, "\n");

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(nvmf_get_address);

/**
 * nvmf_reg_पढ़ो32() -  NVMe Fabrics "Property Get" API function.
 * @ctrl:	Host NVMe controller instance मुख्यtaining the admin
 *		queue used to submit the property पढ़ो command to
 *		the allocated NVMe controller resource on the target प्रणाली.
 * @off:	Starting offset value of the targeted property
 *		रेजिस्टर (see the fabrics section of the NVMe standard).
 * @val:	OUTPUT parameter that will contain the value of
 *		the property after a successful पढ़ो.
 *
 * Used by the host प्रणाली to retrieve a 32-bit capsule property value
 * from an NVMe controller on the target प्रणाली.
 *
 * ("Capsule property" is an "PCIe register concept" applied to the
 * NVMe fabrics space.)
 *
 * Return:
 *	0: successful पढ़ो
 *	> 0: NVMe error status code
 *	< 0: Linux त्रुटि_सं error code
 */
पूर्णांक nvmf_reg_पढ़ो32(काष्ठा nvme_ctrl *ctrl, u32 off, u32 *val)
अणु
	काष्ठा nvme_command cmd;
	जोड़ nvme_result res;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.prop_get.opcode = nvme_fabrics_command;
	cmd.prop_get.fctype = nvme_fabrics_type_property_get;
	cmd.prop_get.offset = cpu_to_le32(off);

	ret = __nvme_submit_sync_cmd(ctrl->fabrics_q, &cmd, &res, शून्य, 0, 0,
			NVME_QID_ANY, 0, 0, false);

	अगर (ret >= 0)
		*val = le64_to_cpu(res.u64);
	अगर (unlikely(ret != 0))
		dev_err(ctrl->device,
			"Property Get error: %d, offset %#x\n",
			ret > 0 ? ret & ~NVME_SC_DNR : ret, off);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nvmf_reg_पढ़ो32);

/**
 * nvmf_reg_पढ़ो64() -  NVMe Fabrics "Property Get" API function.
 * @ctrl:	Host NVMe controller instance मुख्यtaining the admin
 *		queue used to submit the property पढ़ो command to
 *		the allocated controller resource on the target प्रणाली.
 * @off:	Starting offset value of the targeted property
 *		रेजिस्टर (see the fabrics section of the NVMe standard).
 * @val:	OUTPUT parameter that will contain the value of
 *		the property after a successful पढ़ो.
 *
 * Used by the host प्रणाली to retrieve a 64-bit capsule property value
 * from an NVMe controller on the target प्रणाली.
 *
 * ("Capsule property" is an "PCIe register concept" applied to the
 * NVMe fabrics space.)
 *
 * Return:
 *	0: successful पढ़ो
 *	> 0: NVMe error status code
 *	< 0: Linux त्रुटि_सं error code
 */
पूर्णांक nvmf_reg_पढ़ो64(काष्ठा nvme_ctrl *ctrl, u32 off, u64 *val)
अणु
	काष्ठा nvme_command cmd;
	जोड़ nvme_result res;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.prop_get.opcode = nvme_fabrics_command;
	cmd.prop_get.fctype = nvme_fabrics_type_property_get;
	cmd.prop_get.attrib = 1;
	cmd.prop_get.offset = cpu_to_le32(off);

	ret = __nvme_submit_sync_cmd(ctrl->fabrics_q, &cmd, &res, शून्य, 0, 0,
			NVME_QID_ANY, 0, 0, false);

	अगर (ret >= 0)
		*val = le64_to_cpu(res.u64);
	अगर (unlikely(ret != 0))
		dev_err(ctrl->device,
			"Property Get error: %d, offset %#x\n",
			ret > 0 ? ret & ~NVME_SC_DNR : ret, off);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nvmf_reg_पढ़ो64);

/**
 * nvmf_reg_ग_लिखो32() -  NVMe Fabrics "Property Write" API function.
 * @ctrl:	Host NVMe controller instance मुख्यtaining the admin
 *		queue used to submit the property पढ़ो command to
 *		the allocated NVMe controller resource on the target प्रणाली.
 * @off:	Starting offset value of the targeted property
 *		रेजिस्टर (see the fabrics section of the NVMe standard).
 * @val:	Input parameter that contains the value to be
 *		written to the property.
 *
 * Used by the NVMe host प्रणाली to ग_लिखो a 32-bit capsule property value
 * to an NVMe controller on the target प्रणाली.
 *
 * ("Capsule property" is an "PCIe register concept" applied to the
 * NVMe fabrics space.)
 *
 * Return:
 *	0: successful ग_लिखो
 *	> 0: NVMe error status code
 *	< 0: Linux त्रुटि_सं error code
 */
पूर्णांक nvmf_reg_ग_लिखो32(काष्ठा nvme_ctrl *ctrl, u32 off, u32 val)
अणु
	काष्ठा nvme_command cmd;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.prop_set.opcode = nvme_fabrics_command;
	cmd.prop_set.fctype = nvme_fabrics_type_property_set;
	cmd.prop_set.attrib = 0;
	cmd.prop_set.offset = cpu_to_le32(off);
	cmd.prop_set.value = cpu_to_le64(val);

	ret = __nvme_submit_sync_cmd(ctrl->fabrics_q, &cmd, शून्य, शून्य, 0, 0,
			NVME_QID_ANY, 0, 0, false);
	अगर (unlikely(ret))
		dev_err(ctrl->device,
			"Property Set error: %d, offset %#x\n",
			ret > 0 ? ret & ~NVME_SC_DNR : ret, off);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nvmf_reg_ग_लिखो32);

/**
 * nvmf_log_connect_error() - Error-parsing-diagnostic prपूर्णांक
 * out function क्रम connect() errors.
 *
 * @ctrl: the specअगरic /dev/nvmeX device that had the error.
 *
 * @errval: Error code to be decoded in a more human-मित्रly
 *	    prपूर्णांकout.
 *
 * @offset: For use with the NVMe error code NVME_SC_CONNECT_INVALID_PARAM.
 *
 * @cmd: This is the SQE portion of a submission capsule.
 *
 * @data: This is the "Data" portion of a submission capsule.
 */
अटल व्योम nvmf_log_connect_error(काष्ठा nvme_ctrl *ctrl,
		पूर्णांक errval, पूर्णांक offset, काष्ठा nvme_command *cmd,
		काष्ठा nvmf_connect_data *data)
अणु
	पूर्णांक err_sctype = errval & (~NVME_SC_DNR);

	चयन (err_sctype) अणु

	हाल (NVME_SC_CONNECT_INVALID_PARAM):
		अगर (offset >> 16) अणु
			अक्षर *inv_data = "Connect Invalid Data Parameter";

			चयन (offset & 0xffff) अणु
			हाल (दुरत्व(काष्ठा nvmf_connect_data, cntlid)):
				dev_err(ctrl->device,
					"%s, cntlid: %d\n",
					inv_data, data->cntlid);
				अवरोध;
			हाल (दुरत्व(काष्ठा nvmf_connect_data, hostnqn)):
				dev_err(ctrl->device,
					"%s, hostnqn \"%s\"\n",
					inv_data, data->hostnqn);
				अवरोध;
			हाल (दुरत्व(काष्ठा nvmf_connect_data, subsysnqn)):
				dev_err(ctrl->device,
					"%s, subsysnqn \"%s\"\n",
					inv_data, data->subsysnqn);
				अवरोध;
			शेष:
				dev_err(ctrl->device,
					"%s, starting byte offset: %d\n",
				       inv_data, offset & 0xffff);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अक्षर *inv_sqe = "Connect Invalid SQE Parameter";

			चयन (offset) अणु
			हाल (दुरत्व(काष्ठा nvmf_connect_command, qid)):
				dev_err(ctrl->device,
				       "%s, qid %d\n",
					inv_sqe, cmd->connect.qid);
				अवरोध;
			शेष:
				dev_err(ctrl->device,
					"%s, starting byte offset: %d\n",
					inv_sqe, offset);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल NVME_SC_CONNECT_INVALID_HOST:
		dev_err(ctrl->device,
			"Connect for subsystem %s is not allowed, hostnqn: %s\n",
			data->subsysnqn, data->hostnqn);
		अवरोध;

	हाल NVME_SC_CONNECT_CTRL_BUSY:
		dev_err(ctrl->device,
			"Connect command failed: controller is busy or not available\n");
		अवरोध;

	हाल NVME_SC_CONNECT_FORMAT:
		dev_err(ctrl->device,
			"Connect incompatible format: %d",
			cmd->connect.recfmt);
		अवरोध;

	हाल NVME_SC_HOST_PATH_ERROR:
		dev_err(ctrl->device,
			"Connect command failed: host path error\n");
		अवरोध;

	शेष:
		dev_err(ctrl->device,
			"Connect command failed, error wo/DNR bit: %d\n",
			err_sctype);
		अवरोध;
	पूर्ण /* चयन (err_sctype) */
पूर्ण

/**
 * nvmf_connect_admin_queue() - NVMe Fabrics Admin Queue "Connect"
 *				API function.
 * @ctrl:	Host nvme controller instance used to request
 *              a new NVMe controller allocation on the target
 *              प्रणाली and  establish an NVMe Admin connection to
 *              that controller.
 *
 * This function enables an NVMe host device to request a new allocation of
 * an NVMe controller resource on a target प्रणाली as well establish a
 * fabrics-protocol connection of the NVMe Admin queue between the
 * host प्रणाली device and the allocated NVMe controller on the
 * target प्रणाली via a NVMe Fabrics "Connect" command.
 *
 * Return:
 *	0: success
 *	> 0: NVMe error status code
 *	< 0: Linux त्रुटि_सं error code
 *
 */
पूर्णांक nvmf_connect_admin_queue(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvme_command cmd;
	जोड़ nvme_result res;
	काष्ठा nvmf_connect_data *data;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.connect.opcode = nvme_fabrics_command;
	cmd.connect.fctype = nvme_fabrics_type_connect;
	cmd.connect.qid = 0;
	cmd.connect.sqsize = cpu_to_le16(NVME_AQ_DEPTH - 1);

	/*
	 * Set keep-alive समयout in seconds granularity (ms * 1000)
	 */
	cmd.connect.kato = cpu_to_le32(ctrl->kato * 1000);

	अगर (ctrl->opts->disable_sqflow)
		cmd.connect.cattr |= NVME_CONNECT_DISABLE_SQFLOW;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	uuid_copy(&data->hostid, &ctrl->opts->host->id);
	data->cntlid = cpu_to_le16(0xffff);
	म_नकलन(data->subsysnqn, ctrl->opts->subsysnqn, NVMF_NQN_SIZE);
	म_नकलन(data->hostnqn, ctrl->opts->host->nqn, NVMF_NQN_SIZE);

	ret = __nvme_submit_sync_cmd(ctrl->fabrics_q, &cmd, &res,
			data, माप(*data), 0, NVME_QID_ANY, 1,
			BLK_MQ_REQ_RESERVED | BLK_MQ_REQ_NOWAIT, false);
	अगर (ret) अणु
		nvmf_log_connect_error(ctrl, ret, le32_to_cpu(res.u32),
				       &cmd, data);
		जाओ out_मुक्त_data;
	पूर्ण

	ctrl->cntlid = le16_to_cpu(res.u16);

out_मुक्त_data:
	kमुक्त(data);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nvmf_connect_admin_queue);

/**
 * nvmf_connect_io_queue() - NVMe Fabrics I/O Queue "Connect"
 *			     API function.
 * @ctrl:	Host nvme controller instance used to establish an
 *		NVMe I/O queue connection to the alपढ़ोy allocated NVMe
 *		controller on the target प्रणाली.
 * @qid:	NVMe I/O queue number क्रम the new I/O connection between
 *		host and target (note qid == 0 is illegal as this is
 *		the Admin queue, per NVMe standard).
 * @poll:	Whether or not to poll क्रम the completion of the connect cmd.
 *
 * This function issues a fabrics-protocol connection
 * of a NVMe I/O queue (via NVMe Fabrics "Connect" command)
 * between the host प्रणाली device and the allocated NVMe controller
 * on the target प्रणाली.
 *
 * Return:
 *	0: success
 *	> 0: NVMe error status code
 *	< 0: Linux त्रुटि_सं error code
 */
पूर्णांक nvmf_connect_io_queue(काष्ठा nvme_ctrl *ctrl, u16 qid, bool poll)
अणु
	काष्ठा nvme_command cmd;
	काष्ठा nvmf_connect_data *data;
	जोड़ nvme_result res;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.connect.opcode = nvme_fabrics_command;
	cmd.connect.fctype = nvme_fabrics_type_connect;
	cmd.connect.qid = cpu_to_le16(qid);
	cmd.connect.sqsize = cpu_to_le16(ctrl->sqsize);

	अगर (ctrl->opts->disable_sqflow)
		cmd.connect.cattr |= NVME_CONNECT_DISABLE_SQFLOW;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	uuid_copy(&data->hostid, &ctrl->opts->host->id);
	data->cntlid = cpu_to_le16(ctrl->cntlid);
	म_नकलन(data->subsysnqn, ctrl->opts->subsysnqn, NVMF_NQN_SIZE);
	म_नकलन(data->hostnqn, ctrl->opts->host->nqn, NVMF_NQN_SIZE);

	ret = __nvme_submit_sync_cmd(ctrl->connect_q, &cmd, &res,
			data, माप(*data), 0, qid, 1,
			BLK_MQ_REQ_RESERVED | BLK_MQ_REQ_NOWAIT, poll);
	अगर (ret) अणु
		nvmf_log_connect_error(ctrl, ret, le32_to_cpu(res.u32),
				       &cmd, data);
	पूर्ण
	kमुक्त(data);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nvmf_connect_io_queue);

bool nvmf_should_reconnect(काष्ठा nvme_ctrl *ctrl)
अणु
	अगर (ctrl->opts->max_reconnects == -1 ||
	    ctrl->nr_reconnects < ctrl->opts->max_reconnects)
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(nvmf_should_reconnect);

/**
 * nvmf_रेजिस्टर_transport() - NVMe Fabrics Library registration function.
 * @ops:	Transport ops instance to be रेजिस्टरed to the
 *		common fabrics library.
 *
 * API function that रेजिस्टरs the type of specअगरic transport fabric
 * being implemented to the common NVMe fabrics library. Part of
 * the overall init sequence of starting up a fabrics driver.
 */
पूर्णांक nvmf_रेजिस्टर_transport(काष्ठा nvmf_transport_ops *ops)
अणु
	अगर (!ops->create_ctrl)
		वापस -EINVAL;

	करोwn_ग_लिखो(&nvmf_transports_rwsem);
	list_add_tail(&ops->entry, &nvmf_transports);
	up_ग_लिखो(&nvmf_transports_rwsem);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nvmf_रेजिस्टर_transport);

/**
 * nvmf_unरेजिस्टर_transport() - NVMe Fabrics Library unregistration function.
 * @ops:	Transport ops instance to be unरेजिस्टरed from the
 *		common fabrics library.
 *
 * Fabrics API function that unरेजिस्टरs the type of specअगरic transport
 * fabric being implemented from the common NVMe fabrics library.
 * Part of the overall निकास sequence of unloading the implemented driver.
 */
व्योम nvmf_unरेजिस्टर_transport(काष्ठा nvmf_transport_ops *ops)
अणु
	करोwn_ग_लिखो(&nvmf_transports_rwsem);
	list_del(&ops->entry);
	up_ग_लिखो(&nvmf_transports_rwsem);
पूर्ण
EXPORT_SYMBOL_GPL(nvmf_unरेजिस्टर_transport);

अटल काष्ठा nvmf_transport_ops *nvmf_lookup_transport(
		काष्ठा nvmf_ctrl_options *opts)
अणु
	काष्ठा nvmf_transport_ops *ops;

	lockdep_निश्चित_held(&nvmf_transports_rwsem);

	list_क्रम_each_entry(ops, &nvmf_transports, entry) अणु
		अगर (म_भेद(ops->name, opts->transport) == 0)
			वापस ops;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर match_table_t opt_tokens = अणु
	अणु NVMF_OPT_TRANSPORT,		"transport=%s"		पूर्ण,
	अणु NVMF_OPT_TRADDR,		"traddr=%s"		पूर्ण,
	अणु NVMF_OPT_TRSVCID,		"trsvcid=%s"		पूर्ण,
	अणु NVMF_OPT_NQN,			"nqn=%s"		पूर्ण,
	अणु NVMF_OPT_QUEUE_SIZE,		"queue_size=%d"		पूर्ण,
	अणु NVMF_OPT_NR_IO_QUEUES,	"nr_io_queues=%d"	पूर्ण,
	अणु NVMF_OPT_RECONNECT_DELAY,	"reconnect_delay=%d"	पूर्ण,
	अणु NVMF_OPT_CTRL_LOSS_TMO,	"ctrl_loss_tmo=%d"	पूर्ण,
	अणु NVMF_OPT_KATO,		"keep_alive_tmo=%d"	पूर्ण,
	अणु NVMF_OPT_HOSTNQN,		"hostnqn=%s"		पूर्ण,
	अणु NVMF_OPT_HOST_TRADDR,		"host_traddr=%s"	पूर्ण,
	अणु NVMF_OPT_HOST_ID,		"hostid=%s"		पूर्ण,
	अणु NVMF_OPT_DUP_CONNECT,		"duplicate_connect"	पूर्ण,
	अणु NVMF_OPT_DISABLE_SQFLOW,	"disable_sqflow"	पूर्ण,
	अणु NVMF_OPT_HDR_DIGEST,		"hdr_digest"		पूर्ण,
	अणु NVMF_OPT_DATA_DIGEST,		"data_digest"		पूर्ण,
	अणु NVMF_OPT_NR_WRITE_QUEUES,	"nr_write_queues=%d"	पूर्ण,
	अणु NVMF_OPT_NR_POLL_QUEUES,	"nr_poll_queues=%d"	पूर्ण,
	अणु NVMF_OPT_TOS,			"tos=%d"		पूर्ण,
	अणु NVMF_OPT_FAIL_FAST_TMO,	"fast_io_fail_tmo=%d"	पूर्ण,
	अणु NVMF_OPT_ERR,			शून्य			पूर्ण
पूर्ण;

अटल पूर्णांक nvmf_parse_options(काष्ठा nvmf_ctrl_options *opts,
		स्थिर अक्षर *buf)
अणु
	substring_t args[MAX_OPT_ARGS];
	अक्षर *options, *o, *p;
	पूर्णांक token, ret = 0;
	माप_प्रकार nqnlen  = 0;
	पूर्णांक ctrl_loss_पंचांगo = NVMF_DEF_CTRL_LOSS_TMO;
	uuid_t hostid;

	/* Set शेषs */
	opts->queue_size = NVMF_DEF_QUEUE_SIZE;
	opts->nr_io_queues = num_online_cpus();
	opts->reconnect_delay = NVMF_DEF_RECONNECT_DELAY;
	opts->kato = 0;
	opts->duplicate_connect = false;
	opts->fast_io_fail_पंचांगo = NVMF_DEF_FAIL_FAST_TMO;
	opts->hdr_digest = false;
	opts->data_digest = false;
	opts->tos = -1; /* < 0 == use transport शेष */

	options = o = kstrdup(buf, GFP_KERNEL);
	अगर (!options)
		वापस -ENOMEM;

	uuid_gen(&hostid);

	जबतक ((p = strsep(&o, ",\n")) != शून्य) अणु
		अगर (!*p)
			जारी;

		token = match_token(p, opt_tokens, args);
		opts->mask |= token;
		चयन (token) अणु
		हाल NVMF_OPT_TRANSPORT:
			p = match_strdup(args);
			अगर (!p) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			kमुक्त(opts->transport);
			opts->transport = p;
			अवरोध;
		हाल NVMF_OPT_NQN:
			p = match_strdup(args);
			अगर (!p) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			kमुक्त(opts->subsysnqn);
			opts->subsysnqn = p;
			nqnlen = म_माप(opts->subsysnqn);
			अगर (nqnlen >= NVMF_NQN_SIZE) अणु
				pr_err("%s needs to be < %d bytes\n",
					opts->subsysnqn, NVMF_NQN_SIZE);
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			opts->discovery_nqn =
				!(म_भेद(opts->subsysnqn,
					 NVME_DISC_SUBSYS_NAME));
			अवरोध;
		हाल NVMF_OPT_TRADDR:
			p = match_strdup(args);
			अगर (!p) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			kमुक्त(opts->traddr);
			opts->traddr = p;
			अवरोध;
		हाल NVMF_OPT_TRSVCID:
			p = match_strdup(args);
			अगर (!p) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			kमुक्त(opts->trsvcid);
			opts->trsvcid = p;
			अवरोध;
		हाल NVMF_OPT_QUEUE_SIZE:
			अगर (match_पूर्णांक(args, &token)) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			अगर (token < NVMF_MIN_QUEUE_SIZE ||
			    token > NVMF_MAX_QUEUE_SIZE) अणु
				pr_err("Invalid queue_size %d\n", token);
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			opts->queue_size = token;
			अवरोध;
		हाल NVMF_OPT_NR_IO_QUEUES:
			अगर (match_पूर्णांक(args, &token)) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			अगर (token <= 0) अणु
				pr_err("Invalid number of IOQs %d\n", token);
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			अगर (opts->discovery_nqn) अणु
				pr_debug("Ignoring nr_io_queues value for discovery controller\n");
				अवरोध;
			पूर्ण

			opts->nr_io_queues = min_t(अचिन्हित पूर्णांक,
					num_online_cpus(), token);
			अवरोध;
		हाल NVMF_OPT_KATO:
			अगर (match_पूर्णांक(args, &token)) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण

			अगर (token < 0) अणु
				pr_err("Invalid keep_alive_tmo %d\n", token);
				ret = -EINVAL;
				जाओ out;
			पूर्ण अन्यथा अगर (token == 0 && !opts->discovery_nqn) अणु
				/* Allowed क्रम debug */
				pr_warn("keep_alive_tmo 0 won't execute keep alives!!!\n");
			पूर्ण
			opts->kato = token;
			अवरोध;
		हाल NVMF_OPT_CTRL_LOSS_TMO:
			अगर (match_पूर्णांक(args, &token)) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण

			अगर (token < 0)
				pr_warn("ctrl_loss_tmo < 0 will reconnect forever\n");
			ctrl_loss_पंचांगo = token;
			अवरोध;
		हाल NVMF_OPT_FAIL_FAST_TMO:
			अगर (match_पूर्णांक(args, &token)) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण

			अगर (token >= 0)
				pr_warn("I/O fail on reconnect controller after %d sec\n",
					token);
			opts->fast_io_fail_पंचांगo = token;
			अवरोध;
		हाल NVMF_OPT_HOSTNQN:
			अगर (opts->host) अणु
				pr_err("hostnqn already user-assigned: %s\n",
				       opts->host->nqn);
				ret = -EADDRINUSE;
				जाओ out;
			पूर्ण
			p = match_strdup(args);
			अगर (!p) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			nqnlen = म_माप(p);
			अगर (nqnlen >= NVMF_NQN_SIZE) अणु
				pr_err("%s needs to be < %d bytes\n",
					p, NVMF_NQN_SIZE);
				kमुक्त(p);
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			nvmf_host_put(opts->host);
			opts->host = nvmf_host_add(p);
			kमुक्त(p);
			अगर (!opts->host) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			अवरोध;
		हाल NVMF_OPT_RECONNECT_DELAY:
			अगर (match_पूर्णांक(args, &token)) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			अगर (token <= 0) अणु
				pr_err("Invalid reconnect_delay %d\n", token);
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			opts->reconnect_delay = token;
			अवरोध;
		हाल NVMF_OPT_HOST_TRADDR:
			p = match_strdup(args);
			अगर (!p) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			kमुक्त(opts->host_traddr);
			opts->host_traddr = p;
			अवरोध;
		हाल NVMF_OPT_HOST_ID:
			p = match_strdup(args);
			अगर (!p) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			ret = uuid_parse(p, &hostid);
			अगर (ret) अणु
				pr_err("Invalid hostid %s\n", p);
				ret = -EINVAL;
				kमुक्त(p);
				जाओ out;
			पूर्ण
			kमुक्त(p);
			अवरोध;
		हाल NVMF_OPT_DUP_CONNECT:
			opts->duplicate_connect = true;
			अवरोध;
		हाल NVMF_OPT_DISABLE_SQFLOW:
			opts->disable_sqflow = true;
			अवरोध;
		हाल NVMF_OPT_HDR_DIGEST:
			opts->hdr_digest = true;
			अवरोध;
		हाल NVMF_OPT_DATA_DIGEST:
			opts->data_digest = true;
			अवरोध;
		हाल NVMF_OPT_NR_WRITE_QUEUES:
			अगर (match_पूर्णांक(args, &token)) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			अगर (token <= 0) अणु
				pr_err("Invalid nr_write_queues %d\n", token);
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			opts->nr_ग_लिखो_queues = token;
			अवरोध;
		हाल NVMF_OPT_NR_POLL_QUEUES:
			अगर (match_पूर्णांक(args, &token)) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			अगर (token <= 0) अणु
				pr_err("Invalid nr_poll_queues %d\n", token);
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			opts->nr_poll_queues = token;
			अवरोध;
		हाल NVMF_OPT_TOS:
			अगर (match_पूर्णांक(args, &token)) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			अगर (token < 0) अणु
				pr_err("Invalid type of service %d\n", token);
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			अगर (token > 255) अणु
				pr_warn("Clamping type of service to 255\n");
				token = 255;
			पूर्ण
			opts->tos = token;
			अवरोध;
		शेष:
			pr_warn("unknown parameter or missing value '%s' in ctrl creation request\n",
				p);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (opts->discovery_nqn) अणु
		opts->nr_io_queues = 0;
		opts->nr_ग_लिखो_queues = 0;
		opts->nr_poll_queues = 0;
		opts->duplicate_connect = true;
	पूर्ण अन्यथा अणु
		अगर (!opts->kato)
			opts->kato = NVME_DEFAULT_KATO;
	पूर्ण
	अगर (ctrl_loss_पंचांगo < 0) अणु
		opts->max_reconnects = -1;
	पूर्ण अन्यथा अणु
		opts->max_reconnects = DIV_ROUND_UP(ctrl_loss_पंचांगo,
						opts->reconnect_delay);
		अगर (ctrl_loss_पंचांगo < opts->fast_io_fail_पंचांगo)
			pr_warn("failfast tmo (%d) larger than controller loss tmo (%d)\n",
				opts->fast_io_fail_पंचांगo, ctrl_loss_पंचांगo);
	पूर्ण

	अगर (!opts->host) अणु
		kref_get(&nvmf_शेष_host->ref);
		opts->host = nvmf_शेष_host;
	पूर्ण

	uuid_copy(&opts->host->id, &hostid);

out:
	kमुक्त(options);
	वापस ret;
पूर्ण

अटल पूर्णांक nvmf_check_required_opts(काष्ठा nvmf_ctrl_options *opts,
		अचिन्हित पूर्णांक required_opts)
अणु
	अगर ((opts->mask & required_opts) != required_opts) अणु
		पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(opt_tokens); i++) अणु
			अगर ((opt_tokens[i].token & required_opts) &&
			    !(opt_tokens[i].token & opts->mask)) अणु
				pr_warn("missing parameter '%s'\n",
					opt_tokens[i].pattern);
			पूर्ण
		पूर्ण

		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

bool nvmf_ip_options_match(काष्ठा nvme_ctrl *ctrl,
		काष्ठा nvmf_ctrl_options *opts)
अणु
	अगर (!nvmf_ctlr_matches_baseopts(ctrl, opts) ||
	    म_भेद(opts->traddr, ctrl->opts->traddr) ||
	    म_भेद(opts->trsvcid, ctrl->opts->trsvcid))
		वापस false;

	/*
	 * Checking the local address is rough. In most हालs, none is specअगरied
	 * and the host port is selected by the stack.
	 *
	 * Assume no match अगर:
	 * -  local address is specअगरied and address is not the same
	 * -  local address is not specअगरied but remote is, or vice versa
	 *    (admin using specअगरic host_traddr when it matters).
	 */
	अगर ((opts->mask & NVMF_OPT_HOST_TRADDR) &&
	    (ctrl->opts->mask & NVMF_OPT_HOST_TRADDR)) अणु
		अगर (म_भेद(opts->host_traddr, ctrl->opts->host_traddr))
			वापस false;
	पूर्ण अन्यथा अगर ((opts->mask & NVMF_OPT_HOST_TRADDR) ||
		   (ctrl->opts->mask & NVMF_OPT_HOST_TRADDR)) अणु
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(nvmf_ip_options_match);

अटल पूर्णांक nvmf_check_allowed_opts(काष्ठा nvmf_ctrl_options *opts,
		अचिन्हित पूर्णांक allowed_opts)
अणु
	अगर (opts->mask & ~allowed_opts) अणु
		पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(opt_tokens); i++) अणु
			अगर ((opt_tokens[i].token & opts->mask) &&
			    (opt_tokens[i].token & ~allowed_opts)) अणु
				pr_warn("invalid parameter '%s'\n",
					opt_tokens[i].pattern);
			पूर्ण
		पूर्ण

		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम nvmf_मुक्त_options(काष्ठा nvmf_ctrl_options *opts)
अणु
	nvmf_host_put(opts->host);
	kमुक्त(opts->transport);
	kमुक्त(opts->traddr);
	kमुक्त(opts->trsvcid);
	kमुक्त(opts->subsysnqn);
	kमुक्त(opts->host_traddr);
	kमुक्त(opts);
पूर्ण
EXPORT_SYMBOL_GPL(nvmf_मुक्त_options);

#घोषणा NVMF_REQUIRED_OPTS	(NVMF_OPT_TRANSPORT | NVMF_OPT_NQN)
#घोषणा NVMF_ALLOWED_OPTS	(NVMF_OPT_QUEUE_SIZE | NVMF_OPT_NR_IO_QUEUES | \
				 NVMF_OPT_KATO | NVMF_OPT_HOSTNQN | \
				 NVMF_OPT_HOST_ID | NVMF_OPT_DUP_CONNECT |\
				 NVMF_OPT_DISABLE_SQFLOW |\
				 NVMF_OPT_FAIL_FAST_TMO)

अटल काष्ठा nvme_ctrl *
nvmf_create_ctrl(काष्ठा device *dev, स्थिर अक्षर *buf)
अणु
	काष्ठा nvmf_ctrl_options *opts;
	काष्ठा nvmf_transport_ops *ops;
	काष्ठा nvme_ctrl *ctrl;
	पूर्णांक ret;

	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts)
		वापस ERR_PTR(-ENOMEM);

	ret = nvmf_parse_options(opts, buf);
	अगर (ret)
		जाओ out_मुक्त_opts;


	request_module("nvme-%s", opts->transport);

	/*
	 * Check the generic options first as we need a valid transport क्रम
	 * the lookup below.  Then clear the generic flags so that transport
	 * drivers करोn't have to care about them.
	 */
	ret = nvmf_check_required_opts(opts, NVMF_REQUIRED_OPTS);
	अगर (ret)
		जाओ out_मुक्त_opts;
	opts->mask &= ~NVMF_REQUIRED_OPTS;

	करोwn_पढ़ो(&nvmf_transports_rwsem);
	ops = nvmf_lookup_transport(opts);
	अगर (!ops) अणु
		pr_info("no handler found for transport %s.\n",
			opts->transport);
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (!try_module_get(ops->module)) अणु
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	up_पढ़ो(&nvmf_transports_rwsem);

	ret = nvmf_check_required_opts(opts, ops->required_opts);
	अगर (ret)
		जाओ out_module_put;
	ret = nvmf_check_allowed_opts(opts, NVMF_ALLOWED_OPTS |
				ops->allowed_opts | ops->required_opts);
	अगर (ret)
		जाओ out_module_put;

	ctrl = ops->create_ctrl(dev, opts);
	अगर (IS_ERR(ctrl)) अणु
		ret = PTR_ERR(ctrl);
		जाओ out_module_put;
	पूर्ण

	module_put(ops->module);
	वापस ctrl;

out_module_put:
	module_put(ops->module);
	जाओ out_मुक्त_opts;
out_unlock:
	up_पढ़ो(&nvmf_transports_rwsem);
out_मुक्त_opts:
	nvmf_मुक्त_options(opts);
	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा class *nvmf_class;
अटल काष्ठा device *nvmf_device;
अटल DEFINE_MUTEX(nvmf_dev_mutex);

अटल sमाप_प्रकार nvmf_dev_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
		माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा seq_file *seq_file = file->निजी_data;
	काष्ठा nvme_ctrl *ctrl;
	स्थिर अक्षर *buf;
	पूर्णांक ret = 0;

	अगर (count > PAGE_SIZE)
		वापस -ENOMEM;

	buf = memdup_user_nul(ubuf, count);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	mutex_lock(&nvmf_dev_mutex);
	अगर (seq_file->निजी) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	ctrl = nvmf_create_ctrl(nvmf_device, buf);
	अगर (IS_ERR(ctrl)) अणु
		ret = PTR_ERR(ctrl);
		जाओ out_unlock;
	पूर्ण

	seq_file->निजी = ctrl;

out_unlock:
	mutex_unlock(&nvmf_dev_mutex);
	kमुक्त(buf);
	वापस ret ? ret : count;
पूर्ण

अटल पूर्णांक nvmf_dev_show(काष्ठा seq_file *seq_file, व्योम *निजी)
अणु
	काष्ठा nvme_ctrl *ctrl;
	पूर्णांक ret = 0;

	mutex_lock(&nvmf_dev_mutex);
	ctrl = seq_file->निजी;
	अगर (!ctrl) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	seq_म_लिखो(seq_file, "instance=%d,cntlid=%d\n",
			ctrl->instance, ctrl->cntlid);

out_unlock:
	mutex_unlock(&nvmf_dev_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक nvmf_dev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/*
	 * The miscdevice code initializes file->निजी_data, but करोesn't
	 * make use of it later.
	 */
	file->निजी_data = शून्य;
	वापस single_खोलो(file, nvmf_dev_show, शून्य);
पूर्ण

अटल पूर्णांक nvmf_dev_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq_file = file->निजी_data;
	काष्ठा nvme_ctrl *ctrl = seq_file->निजी;

	अगर (ctrl)
		nvme_put_ctrl(ctrl);
	वापस single_release(inode, file);
पूर्ण

अटल स्थिर काष्ठा file_operations nvmf_dev_fops = अणु
	.owner		= THIS_MODULE,
	.ग_लिखो		= nvmf_dev_ग_लिखो,
	.पढ़ो		= seq_पढ़ो,
	.खोलो		= nvmf_dev_खोलो,
	.release	= nvmf_dev_release,
पूर्ण;

अटल काष्ठा miscdevice nvmf_misc = अणु
	.minor		= MISC_DYNAMIC_MINOR,
	.name           = "nvme-fabrics",
	.fops		= &nvmf_dev_fops,
पूर्ण;

अटल पूर्णांक __init nvmf_init(व्योम)
अणु
	पूर्णांक ret;

	nvmf_शेष_host = nvmf_host_शेष();
	अगर (!nvmf_शेष_host)
		वापस -ENOMEM;

	nvmf_class = class_create(THIS_MODULE, "nvme-fabrics");
	अगर (IS_ERR(nvmf_class)) अणु
		pr_err("couldn't register class nvme-fabrics\n");
		ret = PTR_ERR(nvmf_class);
		जाओ out_मुक्त_host;
	पूर्ण

	nvmf_device =
		device_create(nvmf_class, शून्य, MKDEV(0, 0), शून्य, "ctl");
	अगर (IS_ERR(nvmf_device)) अणु
		pr_err("couldn't create nvme-fabris device!\n");
		ret = PTR_ERR(nvmf_device);
		जाओ out_destroy_class;
	पूर्ण

	ret = misc_रेजिस्टर(&nvmf_misc);
	अगर (ret) अणु
		pr_err("couldn't register misc device: %d\n", ret);
		जाओ out_destroy_device;
	पूर्ण

	वापस 0;

out_destroy_device:
	device_destroy(nvmf_class, MKDEV(0, 0));
out_destroy_class:
	class_destroy(nvmf_class);
out_मुक्त_host:
	nvmf_host_put(nvmf_शेष_host);
	वापस ret;
पूर्ण

अटल व्योम __निकास nvmf_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&nvmf_misc);
	device_destroy(nvmf_class, MKDEV(0, 0));
	class_destroy(nvmf_class);
	nvmf_host_put(nvmf_शेष_host);

	BUILD_BUG_ON(माप(काष्ठा nvmf_common_command) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvmf_connect_command) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvmf_property_get_command) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvmf_property_set_command) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvmf_connect_data) != 1024);
पूर्ण

MODULE_LICENSE("GPL v2");

module_init(nvmf_init);
module_निकास(nvmf_निकास);
