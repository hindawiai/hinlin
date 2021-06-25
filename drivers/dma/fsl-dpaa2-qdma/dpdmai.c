<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright 2019 NXP

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/fsl/mc.h>
#समावेश "dpdmai.h"

काष्ठा dpdmai_rsp_get_attributes अणु
	__le32 id;
	u8 num_of_priorities;
	u8 pad0[3];
	__le16 major;
	__le16 minor;
पूर्ण;

काष्ठा dpdmai_cmd_queue अणु
	__le32 dest_id;
	u8 priority;
	u8 queue;
	u8 dest_type;
	u8 pad;
	__le64 user_ctx;
	जोड़ अणु
		__le32 options;
		__le32 fqid;
	पूर्ण;
पूर्ण;

काष्ठा dpdmai_rsp_get_tx_queue अणु
	__le64 pad;
	__le32 fqid;
पूर्ण;

#घोषणा MC_CMD_OP(_cmd, _param, _offset, _width, _type, _arg) \
	((_cmd).params[_param] |= mc_enc((_offset), (_width), _arg))

/* cmd, param, offset, width, type, arg_name */
#घोषणा DPDMAI_CMD_CREATE(cmd, cfg) \
करो अणु \
	MC_CMD_OP(cmd, 0, 8,  8,  u8,  (cfg)->priorities[0]);\
	MC_CMD_OP(cmd, 0, 16, 8,  u8,  (cfg)->priorities[1]);\
पूर्ण जबतक (0)

अटल अंतरभूत u64 mc_enc(पूर्णांक lsoffset, पूर्णांक width, u64 val)
अणु
	वापस (val & MAKE_UMASK64(width)) << lsoffset;
पूर्ण

/**
 * dpdmai_खोलो() - Open a control session क्रम the specअगरied object
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @dpdmai_id:	DPDMAI unique ID
 * @token:	Returned token; use in subsequent API calls
 *
 * This function can be used to खोलो a control session क्रम an
 * alपढ़ोy created object; an object may have been declared in
 * the DPL or by calling the dpdmai_create() function.
 * This function वापसs a unique authentication token,
 * associated with the specअगरic object ID and the specअगरic MC
 * portal; this token must be used in all subsequent commands क्रम
 * this specअगरic object.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpdmai_खोलो(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags,
		पूर्णांक dpdmai_id, u16 *token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	__le64 *cmd_dpdmai_id;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPDMAI_CMDID_OPEN,
					  cmd_flags, 0);

	cmd_dpdmai_id = cmd.params;
	*cmd_dpdmai_id = cpu_to_le32(dpdmai_id);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	*token = mc_cmd_hdr_पढ़ो_token(&cmd);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dpdmai_खोलो);

/**
 * dpdmai_बंद() - Close the control session of the object
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPDMAI object
 *
 * After this function is called, no further operations are
 * allowed on the object without खोलोing a new control session.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpdmai_बंद(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPDMAI_CMDID_CLOSE,
					  cmd_flags, token);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण
EXPORT_SYMBOL_GPL(dpdmai_बंद);

/**
 * dpdmai_create() - Create the DPDMAI object
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @cfg:	Configuration काष्ठाure
 * @token:	Returned token; use in subsequent API calls
 *
 * Create the DPDMAI object, allocate required resources and
 * perक्रमm required initialization.
 *
 * The object can be created either by declaring it in the
 * DPL file, or by calling this function.
 *
 * This function वापसs a unique authentication token,
 * associated with the specअगरic object ID and the specअगरic MC
 * portal; this token must be used in all subsequent calls to
 * this specअगरic object. For objects that are created using the
 * DPL file, call dpdmai_खोलो() function to get an authentication
 * token first.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpdmai_create(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags,
		  स्थिर काष्ठा dpdmai_cfg *cfg, u16 *token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPDMAI_CMDID_CREATE,
					  cmd_flags, 0);
	DPDMAI_CMD_CREATE(cmd, cfg);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	*token = mc_cmd_hdr_पढ़ो_token(&cmd);

	वापस 0;
पूर्ण

/**
 * dpdmai_destroy() - Destroy the DPDMAI object and release all its resources.
 * @mc_io:      Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:  Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:      Token of DPDMAI object
 *
 * Return:      '0' on Success; error code otherwise.
 */
पूर्णांक dpdmai_destroy(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPDMAI_CMDID_DESTROY,
					  cmd_flags, token);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण
EXPORT_SYMBOL_GPL(dpdmai_destroy);

/**
 * dpdmai_enable() - Enable the DPDMAI, allow sending and receiving frames.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPDMAI object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpdmai_enable(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPDMAI_CMDID_ENABLE,
					  cmd_flags, token);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण
EXPORT_SYMBOL_GPL(dpdmai_enable);

/**
 * dpdmai_disable() - Disable the DPDMAI, stop sending and receiving frames.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPDMAI object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpdmai_disable(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPDMAI_CMDID_DISABLE,
					  cmd_flags, token);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण
EXPORT_SYMBOL_GPL(dpdmai_disable);

/**
 * dpdmai_reset() - Reset the DPDMAI, वापसs the object to initial state.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPDMAI object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpdmai_reset(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPDMAI_CMDID_RESET,
					  cmd_flags, token);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण
EXPORT_SYMBOL_GPL(dpdmai_reset);

/**
 * dpdmai_get_attributes() - Retrieve DPDMAI attributes.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPDMAI object
 * @attr:	Returned object's attributes
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpdmai_get_attributes(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags,
			  u16 token, काष्ठा dpdmai_attr *attr)
अणु
	काष्ठा dpdmai_rsp_get_attributes *rsp_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPDMAI_CMDID_GET_ATTR,
					  cmd_flags, token);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	rsp_params = (काष्ठा dpdmai_rsp_get_attributes *)cmd.params;
	attr->id = le32_to_cpu(rsp_params->id);
	attr->version.major = le16_to_cpu(rsp_params->major);
	attr->version.minor = le16_to_cpu(rsp_params->minor);
	attr->num_of_priorities = rsp_params->num_of_priorities;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dpdmai_get_attributes);

/**
 * dpdmai_set_rx_queue() - Set Rx queue configuration
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPDMAI object
 * @priority:	Select the queue relative to number of
 *		priorities configured at DPDMAI creation
 * @cfg:	Rx queue configuration
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpdmai_set_rx_queue(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			u8 priority, स्थिर काष्ठा dpdmai_rx_queue_cfg *cfg)
अणु
	काष्ठा dpdmai_cmd_queue *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPDMAI_CMDID_SET_RX_QUEUE,
					  cmd_flags, token);

	cmd_params = (काष्ठा dpdmai_cmd_queue *)cmd.params;
	cmd_params->dest_id = cpu_to_le32(cfg->dest_cfg.dest_id);
	cmd_params->priority = cfg->dest_cfg.priority;
	cmd_params->queue = priority;
	cmd_params->dest_type = cfg->dest_cfg.dest_type;
	cmd_params->user_ctx = cpu_to_le64(cfg->user_ctx);
	cmd_params->options = cpu_to_le32(cfg->options);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण
EXPORT_SYMBOL_GPL(dpdmai_set_rx_queue);

/**
 * dpdmai_get_rx_queue() - Retrieve Rx queue attributes.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPDMAI object
 * @priority:	Select the queue relative to number of
 *				priorities configured at DPDMAI creation
 * @attr:	Returned Rx queue attributes
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpdmai_get_rx_queue(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			u8 priority, काष्ठा dpdmai_rx_queue_attr *attr)
अणु
	काष्ठा dpdmai_cmd_queue *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPDMAI_CMDID_GET_RX_QUEUE,
					  cmd_flags, token);

	cmd_params = (काष्ठा dpdmai_cmd_queue *)cmd.params;
	cmd_params->queue = priority;

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	attr->dest_cfg.dest_id = le32_to_cpu(cmd_params->dest_id);
	attr->dest_cfg.priority = cmd_params->priority;
	attr->dest_cfg.dest_type = cmd_params->dest_type;
	attr->user_ctx = le64_to_cpu(cmd_params->user_ctx);
	attr->fqid = le32_to_cpu(cmd_params->fqid);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dpdmai_get_rx_queue);

/**
 * dpdmai_get_tx_queue() - Retrieve Tx queue attributes.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPDMAI object
 * @priority:	Select the queue relative to number of
 *			priorities configured at DPDMAI creation
 * @fqid:	Returned Tx queue
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpdmai_get_tx_queue(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags,
			u16 token, u8 priority, u32 *fqid)
अणु
	काष्ठा dpdmai_rsp_get_tx_queue *rsp_params;
	काष्ठा dpdmai_cmd_queue *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPDMAI_CMDID_GET_TX_QUEUE,
					  cmd_flags, token);

	cmd_params = (काष्ठा dpdmai_cmd_queue *)cmd.params;
	cmd_params->queue = priority;

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */

	rsp_params = (काष्ठा dpdmai_rsp_get_tx_queue *)cmd.params;
	*fqid = le32_to_cpu(rsp_params->fqid);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dpdmai_get_tx_queue);

MODULE_LICENSE("GPL v2");
