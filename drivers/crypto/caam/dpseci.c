<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2017-2018 NXP
 */

#समावेश <linux/fsl/mc.h>
#समावेश "dpseci.h"
#समावेश "dpseci_cmd.h"

/**
 * dpseci_खोलो() - Open a control session क्रम the specअगरied object
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @dpseci_id:	DPSECI unique ID
 * @token:	Returned token; use in subsequent API calls
 *
 * This function can be used to खोलो a control session क्रम an alपढ़ोy created
 * object; an object may have been declared अटलally in the DPL
 * or created dynamically.
 * This function वापसs a unique authentication token, associated with the
 * specअगरic object ID and the specअगरic MC portal; this token must be used in all
 * subsequent commands क्रम this specअगरic object.
 *
 * Return:	'0' on success, error code otherwise
 */
पूर्णांक dpseci_खोलो(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, पूर्णांक dpseci_id,
		u16 *token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpseci_cmd_खोलो *cmd_params;
	पूर्णांक err;

	cmd.header = mc_encode_cmd_header(DPSECI_CMDID_OPEN,
					  cmd_flags,
					  0);
	cmd_params = (काष्ठा dpseci_cmd_खोलो *)cmd.params;
	cmd_params->dpseci_id = cpu_to_le32(dpseci_id);
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	*token = mc_cmd_hdr_पढ़ो_token(&cmd);

	वापस 0;
पूर्ण

/**
 * dpseci_बंद() - Close the control session of the object
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSECI object
 *
 * After this function is called, no further operations are allowed on the
 * object without खोलोing a new control session.
 *
 * Return:	'0' on success, error code otherwise
 */
पूर्णांक dpseci_बंद(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	cmd.header = mc_encode_cmd_header(DPSECI_CMDID_CLOSE,
					  cmd_flags,
					  token);
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpseci_enable() - Enable the DPSECI, allow sending and receiving frames
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSECI object
 *
 * Return:	'0' on success, error code otherwise
 */
पूर्णांक dpseci_enable(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	cmd.header = mc_encode_cmd_header(DPSECI_CMDID_ENABLE,
					  cmd_flags,
					  token);
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpseci_disable() - Disable the DPSECI, stop sending and receiving frames
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSECI object
 *
 * Return:	'0' on success, error code otherwise
 */
पूर्णांक dpseci_disable(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	cmd.header = mc_encode_cmd_header(DPSECI_CMDID_DISABLE,
					  cmd_flags,
					  token);

	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpseci_reset() - Reset the DPSECI, वापसs the object to initial state
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSECI object
 *
 * Return:	'0' on success, error code otherwise
 */
पूर्णांक dpseci_reset(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	cmd.header = mc_encode_cmd_header(DPSECI_CMDID_RESET,
					  cmd_flags,
					  token);
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpseci_is_enabled() - Check अगर the DPSECI is enabled.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSECI object
 * @en:		Returns '1' if object is enabled; '0' otherwise
 *
 * Return:	'0' on success, error code otherwise
 */
पूर्णांक dpseci_is_enabled(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
		      पूर्णांक *en)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpseci_rsp_is_enabled *rsp_params;
	पूर्णांक err;

	cmd.header = mc_encode_cmd_header(DPSECI_CMDID_IS_ENABLED,
					  cmd_flags,
					  token);
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	rsp_params = (काष्ठा dpseci_rsp_is_enabled *)cmd.params;
	*en = dpseci_get_field(rsp_params->is_enabled, ENABLE);

	वापस 0;
पूर्ण

/**
 * dpseci_get_attributes() - Retrieve DPSECI attributes
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSECI object
 * @attr:	Returned object's attributes
 *
 * Return:	'0' on success, error code otherwise
 */
पूर्णांक dpseci_get_attributes(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			  काष्ठा dpseci_attr *attr)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpseci_rsp_get_attributes *rsp_params;
	पूर्णांक err;

	cmd.header = mc_encode_cmd_header(DPSECI_CMDID_GET_ATTR,
					  cmd_flags,
					  token);
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	rsp_params = (काष्ठा dpseci_rsp_get_attributes *)cmd.params;
	attr->id = le32_to_cpu(rsp_params->id);
	attr->num_tx_queues = rsp_params->num_tx_queues;
	attr->num_rx_queues = rsp_params->num_rx_queues;
	attr->options = le32_to_cpu(rsp_params->options);

	वापस 0;
पूर्ण

/**
 * dpseci_set_rx_queue() - Set Rx queue configuration
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSECI object
 * @queue:	Select the queue relative to number of priorities configured at
 *		DPSECI creation; use DPSECI_ALL_QUEUES to configure all
 *		Rx queues identically.
 * @cfg:	Rx queue configuration
 *
 * Return:	'0' on success, error code otherwise
 */
पूर्णांक dpseci_set_rx_queue(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			u8 queue, स्थिर काष्ठा dpseci_rx_queue_cfg *cfg)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpseci_cmd_queue *cmd_params;

	cmd.header = mc_encode_cmd_header(DPSECI_CMDID_SET_RX_QUEUE,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpseci_cmd_queue *)cmd.params;
	cmd_params->dest_id = cpu_to_le32(cfg->dest_cfg.dest_id);
	cmd_params->priority = cfg->dest_cfg.priority;
	cmd_params->queue = queue;
	dpseci_set_field(cmd_params->dest_type, DEST_TYPE,
			 cfg->dest_cfg.dest_type);
	cmd_params->user_ctx = cpu_to_le64(cfg->user_ctx);
	cmd_params->options = cpu_to_le32(cfg->options);
	dpseci_set_field(cmd_params->order_preservation_en, ORDER_PRESERVATION,
			 cfg->order_preservation_en);

	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpseci_get_rx_queue() - Retrieve Rx queue attributes
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSECI object
 * @queue:	Select the queue relative to number of priorities configured at
 *		DPSECI creation
 * @attr:	Returned Rx queue attributes
 *
 * Return:	'0' on success, error code otherwise
 */
पूर्णांक dpseci_get_rx_queue(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			u8 queue, काष्ठा dpseci_rx_queue_attr *attr)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpseci_cmd_queue *cmd_params;
	पूर्णांक err;

	cmd.header = mc_encode_cmd_header(DPSECI_CMDID_GET_RX_QUEUE,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpseci_cmd_queue *)cmd.params;
	cmd_params->queue = queue;
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	attr->dest_cfg.dest_id = le32_to_cpu(cmd_params->dest_id);
	attr->dest_cfg.priority = cmd_params->priority;
	attr->dest_cfg.dest_type = dpseci_get_field(cmd_params->dest_type,
						    DEST_TYPE);
	attr->user_ctx = le64_to_cpu(cmd_params->user_ctx);
	attr->fqid = le32_to_cpu(cmd_params->fqid);
	attr->order_preservation_en =
		dpseci_get_field(cmd_params->order_preservation_en,
				 ORDER_PRESERVATION);

	वापस 0;
पूर्ण

/**
 * dpseci_get_tx_queue() - Retrieve Tx queue attributes
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSECI object
 * @queue:	Select the queue relative to number of priorities configured at
 *		DPSECI creation
 * @attr:	Returned Tx queue attributes
 *
 * Return:	'0' on success, error code otherwise
 */
पूर्णांक dpseci_get_tx_queue(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			u8 queue, काष्ठा dpseci_tx_queue_attr *attr)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpseci_cmd_queue *cmd_params;
	काष्ठा dpseci_rsp_get_tx_queue *rsp_params;
	पूर्णांक err;

	cmd.header = mc_encode_cmd_header(DPSECI_CMDID_GET_TX_QUEUE,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpseci_cmd_queue *)cmd.params;
	cmd_params->queue = queue;
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	rsp_params = (काष्ठा dpseci_rsp_get_tx_queue *)cmd.params;
	attr->fqid = le32_to_cpu(rsp_params->fqid);
	attr->priority = rsp_params->priority;

	वापस 0;
पूर्ण

/**
 * dpseci_get_sec_attr() - Retrieve SEC accelerator attributes
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSECI object
 * @attr:	Returned SEC attributes
 *
 * Return:	'0' on success, error code otherwise
 */
पूर्णांक dpseci_get_sec_attr(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			काष्ठा dpseci_sec_attr *attr)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpseci_rsp_get_sec_attr *rsp_params;
	पूर्णांक err;

	cmd.header = mc_encode_cmd_header(DPSECI_CMDID_GET_SEC_ATTR,
					  cmd_flags,
					  token);
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	rsp_params = (काष्ठा dpseci_rsp_get_sec_attr *)cmd.params;
	attr->ip_id = le16_to_cpu(rsp_params->ip_id);
	attr->major_rev = rsp_params->major_rev;
	attr->minor_rev = rsp_params->minor_rev;
	attr->era = rsp_params->era;
	attr->deco_num = rsp_params->deco_num;
	attr->zuc_auth_acc_num = rsp_params->zuc_auth_acc_num;
	attr->zuc_enc_acc_num = rsp_params->zuc_enc_acc_num;
	attr->snow_f8_acc_num = rsp_params->snow_f8_acc_num;
	attr->snow_f9_acc_num = rsp_params->snow_f9_acc_num;
	attr->crc_acc_num = rsp_params->crc_acc_num;
	attr->pk_acc_num = rsp_params->pk_acc_num;
	attr->kasumi_acc_num = rsp_params->kasumi_acc_num;
	attr->rng_acc_num = rsp_params->rng_acc_num;
	attr->md_acc_num = rsp_params->md_acc_num;
	attr->arc4_acc_num = rsp_params->arc4_acc_num;
	attr->des_acc_num = rsp_params->des_acc_num;
	attr->aes_acc_num = rsp_params->aes_acc_num;
	attr->ccha_acc_num = rsp_params->ccha_acc_num;
	attr->ptha_acc_num = rsp_params->ptha_acc_num;

	वापस 0;
पूर्ण

/**
 * dpseci_get_api_version() - Get Data Path SEC Interface API version
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @major_ver:	Major version of data path sec API
 * @minor_ver:	Minor version of data path sec API
 *
 * Return:	'0' on success, error code otherwise
 */
पूर्णांक dpseci_get_api_version(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags,
			   u16 *major_ver, u16 *minor_ver)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpseci_rsp_get_api_version *rsp_params;
	पूर्णांक err;

	cmd.header = mc_encode_cmd_header(DPSECI_CMDID_GET_API_VERSION,
					  cmd_flags, 0);
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	rsp_params = (काष्ठा dpseci_rsp_get_api_version *)cmd.params;
	*major_ver = le16_to_cpu(rsp_params->major);
	*minor_ver = le16_to_cpu(rsp_params->minor);

	वापस 0;
पूर्ण

/**
 * dpseci_set_congestion_notअगरication() - Set congestion group
 *	notअगरication configuration
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSECI object
 * @cfg:	congestion notअगरication configuration
 *
 * Return:	'0' on success, error code otherwise
 */
पूर्णांक dpseci_set_congestion_notअगरication(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags,
	u16 token, स्थिर काष्ठा dpseci_congestion_notअगरication_cfg *cfg)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpseci_cmd_congestion_notअगरication *cmd_params;

	cmd.header = mc_encode_cmd_header(
			DPSECI_CMDID_SET_CONGESTION_NOTIFICATION,
			cmd_flags,
			token);
	cmd_params = (काष्ठा dpseci_cmd_congestion_notअगरication *)cmd.params;
	cmd_params->dest_id = cpu_to_le32(cfg->dest_cfg.dest_id);
	cmd_params->notअगरication_mode = cpu_to_le16(cfg->notअगरication_mode);
	cmd_params->priority = cfg->dest_cfg.priority;
	dpseci_set_field(cmd_params->options, CGN_DEST_TYPE,
			 cfg->dest_cfg.dest_type);
	dpseci_set_field(cmd_params->options, CGN_UNITS, cfg->units);
	cmd_params->message_iova = cpu_to_le64(cfg->message_iova);
	cmd_params->message_ctx = cpu_to_le64(cfg->message_ctx);
	cmd_params->threshold_entry = cpu_to_le32(cfg->threshold_entry);
	cmd_params->threshold_निकास = cpu_to_le32(cfg->threshold_निकास);

	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpseci_get_congestion_notअगरication() - Get congestion group notअगरication
 *	configuration
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSECI object
 * @cfg:	congestion notअगरication configuration
 *
 * Return:	'0' on success, error code otherwise
 */
पूर्णांक dpseci_get_congestion_notअगरication(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags,
	u16 token, काष्ठा dpseci_congestion_notअगरication_cfg *cfg)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpseci_cmd_congestion_notअगरication *rsp_params;
	पूर्णांक err;

	cmd.header = mc_encode_cmd_header(
			DPSECI_CMDID_GET_CONGESTION_NOTIFICATION,
			cmd_flags,
			token);
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	rsp_params = (काष्ठा dpseci_cmd_congestion_notअगरication *)cmd.params;
	cfg->dest_cfg.dest_id = le32_to_cpu(rsp_params->dest_id);
	cfg->notअगरication_mode = le16_to_cpu(rsp_params->notअगरication_mode);
	cfg->dest_cfg.priority = rsp_params->priority;
	cfg->dest_cfg.dest_type = dpseci_get_field(rsp_params->options,
						   CGN_DEST_TYPE);
	cfg->units = dpseci_get_field(rsp_params->options, CGN_UNITS);
	cfg->message_iova = le64_to_cpu(rsp_params->message_iova);
	cfg->message_ctx = le64_to_cpu(rsp_params->message_ctx);
	cfg->threshold_entry = le32_to_cpu(rsp_params->threshold_entry);
	cfg->threshold_निकास = le32_to_cpu(rsp_params->threshold_निकास);

	वापस 0;
पूर्ण
