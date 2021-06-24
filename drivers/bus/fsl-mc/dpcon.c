<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * Copyright 2013-2016 Freescale Semiconductor Inc.
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/fsl/mc.h>

#समावेश "fsl-mc-private.h"

/**
 * dpcon_खोलो() - Open a control session क्रम the specअगरied object
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @dpcon_id:	DPCON unique ID
 * @token:	Returned token; use in subsequent API calls
 *
 * This function can be used to खोलो a control session क्रम an
 * alपढ़ोy created object; an object may have been declared in
 * the DPL or by calling the dpcon_create() function.
 * This function वापसs a unique authentication token,
 * associated with the specअगरic object ID and the specअगरic MC
 * portal; this token must be used in all subsequent commands क्रम
 * this specअगरic object.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpcon_खोलो(काष्ठा fsl_mc_io *mc_io,
	       u32 cmd_flags,
	       पूर्णांक dpcon_id,
	       u16 *token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpcon_cmd_खोलो *dpcon_cmd;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPCON_CMDID_OPEN,
					  cmd_flags,
					  0);
	dpcon_cmd = (काष्ठा dpcon_cmd_खोलो *)cmd.params;
	dpcon_cmd->dpcon_id = cpu_to_le32(dpcon_id);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	*token = mc_cmd_hdr_पढ़ो_token(&cmd);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dpcon_खोलो);

/**
 * dpcon_बंद() - Close the control session of the object
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPCON object
 *
 * After this function is called, no further operations are
 * allowed on the object without खोलोing a new control session.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpcon_बंद(काष्ठा fsl_mc_io *mc_io,
		u32 cmd_flags,
		u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPCON_CMDID_CLOSE,
					  cmd_flags,
					  token);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण
EXPORT_SYMBOL_GPL(dpcon_बंद);

/**
 * dpcon_enable() - Enable the DPCON
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPCON object
 *
 * Return:	'0' on Success; Error code otherwise
 */
पूर्णांक dpcon_enable(काष्ठा fsl_mc_io *mc_io,
		 u32 cmd_flags,
		 u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPCON_CMDID_ENABLE,
					  cmd_flags,
					  token);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण
EXPORT_SYMBOL_GPL(dpcon_enable);

/**
 * dpcon_disable() - Disable the DPCON
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPCON object
 *
 * Return:	'0' on Success; Error code otherwise
 */
पूर्णांक dpcon_disable(काष्ठा fsl_mc_io *mc_io,
		  u32 cmd_flags,
		  u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPCON_CMDID_DISABLE,
					  cmd_flags,
					  token);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण
EXPORT_SYMBOL_GPL(dpcon_disable);

/**
 * dpcon_reset() - Reset the DPCON, वापसs the object to initial state.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPCON object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpcon_reset(काष्ठा fsl_mc_io *mc_io,
		u32 cmd_flags,
		u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPCON_CMDID_RESET,
					  cmd_flags, token);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण
EXPORT_SYMBOL_GPL(dpcon_reset);

/**
 * dpcon_get_attributes() - Retrieve DPCON attributes.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPCON object
 * @attr:	Object's attributes
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpcon_get_attributes(काष्ठा fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 token,
			 काष्ठा dpcon_attr *attr)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpcon_rsp_get_attr *dpcon_rsp;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPCON_CMDID_GET_ATTR,
					  cmd_flags,
					  token);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	dpcon_rsp = (काष्ठा dpcon_rsp_get_attr *)cmd.params;
	attr->id = le32_to_cpu(dpcon_rsp->id);
	attr->qbman_ch_id = le16_to_cpu(dpcon_rsp->qbman_ch_id);
	attr->num_priorities = dpcon_rsp->num_priorities;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dpcon_get_attributes);

/**
 * dpcon_set_notअगरication() - Set DPCON notअगरication destination
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPCON object
 * @cfg:	Notअगरication parameters
 *
 * Return:	'0' on Success; Error code otherwise
 */
पूर्णांक dpcon_set_notअगरication(काष्ठा fsl_mc_io *mc_io,
			   u32 cmd_flags,
			   u16 token,
			   काष्ठा dpcon_notअगरication_cfg *cfg)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpcon_cmd_set_notअगरication *dpcon_cmd;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPCON_CMDID_SET_NOTIFICATION,
					  cmd_flags,
					  token);
	dpcon_cmd = (काष्ठा dpcon_cmd_set_notअगरication *)cmd.params;
	dpcon_cmd->dpio_id = cpu_to_le32(cfg->dpio_id);
	dpcon_cmd->priority = cfg->priority;
	dpcon_cmd->user_ctx = cpu_to_le64(cfg->user_ctx);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण
EXPORT_SYMBOL_GPL(dpcon_set_notअगरication);
