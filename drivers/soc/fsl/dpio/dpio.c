<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2016 NXP
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/fsl/mc.h>

#समावेश "dpio.h"
#समावेश "dpio-cmd.h"

/*
 * Data Path I/O Portal API
 * Contains initialization APIs and runसमय control APIs क्रम DPIO
 */

/**
 * dpio_खोलो() - Open a control session क्रम the specअगरied object
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @dpio_id:	DPIO unique ID
 * @token:	Returned token; use in subsequent API calls
 *
 * This function can be used to खोलो a control session क्रम an
 * alपढ़ोy created object; an object may have been declared in
 * the DPL or by calling the dpio_create() function.
 * This function वापसs a unique authentication token,
 * associated with the specअगरic object ID and the specअगरic MC
 * portal; this token must be used in all subsequent commands क्रम
 * this specअगरic object.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpio_खोलो(काष्ठा fsl_mc_io *mc_io,
	      u32 cmd_flags,
	      पूर्णांक dpio_id,
	      u16 *token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpio_cmd_खोलो *dpio_cmd;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPIO_CMDID_OPEN,
					  cmd_flags,
					  0);
	dpio_cmd = (काष्ठा dpio_cmd_खोलो *)cmd.params;
	dpio_cmd->dpio_id = cpu_to_le32(dpio_id);

	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	*token = mc_cmd_hdr_पढ़ो_token(&cmd);

	वापस 0;
पूर्ण

/**
 * dpio_बंद() - Close the control session of the object
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPIO object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpio_बंद(काष्ठा fsl_mc_io *mc_io,
	       u32 cmd_flags,
	       u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPIO_CMDID_CLOSE,
					  cmd_flags,
					  token);

	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpio_enable() - Enable the DPIO, allow I/O portal operations.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPIO object
 *
 * Return:	'0' on Success; Error code otherwise
 */
पूर्णांक dpio_enable(काष्ठा fsl_mc_io *mc_io,
		u32 cmd_flags,
		u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPIO_CMDID_ENABLE,
					  cmd_flags,
					  token);

	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpio_disable() - Disable the DPIO, stop any I/O portal operation.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPIO object
 *
 * Return:	'0' on Success; Error code otherwise
 */
पूर्णांक dpio_disable(काष्ठा fsl_mc_io *mc_io,
		 u32 cmd_flags,
		 u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPIO_CMDID_DISABLE,
					  cmd_flags,
					  token);

	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpio_get_attributes() - Retrieve DPIO attributes
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPIO object
 * @attr:	Returned object's attributes
 *
 * Return:	'0' on Success; Error code otherwise
 */
पूर्णांक dpio_get_attributes(काष्ठा fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			काष्ठा dpio_attr *attr)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpio_rsp_get_attr *dpio_rsp;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPIO_CMDID_GET_ATTR,
					  cmd_flags,
					  token);

	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	dpio_rsp = (काष्ठा dpio_rsp_get_attr *)cmd.params;
	attr->id = le32_to_cpu(dpio_rsp->id);
	attr->qbman_portal_id = le16_to_cpu(dpio_rsp->qbman_portal_id);
	attr->num_priorities = dpio_rsp->num_priorities;
	attr->channel_mode = dpio_rsp->channel_mode & DPIO_CHANNEL_MODE_MASK;
	attr->qbman_portal_ce_offset =
		le64_to_cpu(dpio_rsp->qbman_portal_ce_addr);
	attr->qbman_portal_ci_offset =
		le64_to_cpu(dpio_rsp->qbman_portal_ci_addr);
	attr->qbman_version = le32_to_cpu(dpio_rsp->qbman_version);

	वापस 0;
पूर्ण

पूर्णांक dpio_set_stashing_destination(काष्ठा fsl_mc_io *mc_io,
				  u32 cmd_flags,
				  u16 token,
				  u8 sdest)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpio_stashing_dest *dpio_cmd;

	cmd.header = mc_encode_cmd_header(DPIO_CMDID_SET_STASHING_DEST,
					  cmd_flags, token);
	dpio_cmd = (काष्ठा dpio_stashing_dest *)cmd.params;
	dpio_cmd->sdest = sdest;

	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpio_get_api_version - Get Data Path I/O API version
 * @mc_io:	Poपूर्णांकer to MC portal's DPIO object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @major_ver:	Major version of DPIO API
 * @minor_ver:	Minor version of DPIO API
 *
 * Return:	'0' on Success; Error code otherwise
 */
पूर्णांक dpio_get_api_version(काष्ठा fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 *major_ver,
			 u16 *minor_ver)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPIO_CMDID_GET_API_VERSION,
					  cmd_flags, 0);

	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	mc_cmd_पढ़ो_api_version(&cmd, major_ver, minor_ver);

	वापस 0;
पूर्ण

/**
 * dpio_reset() - Reset the DPIO, वापसs the object to initial state.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPIO object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpio_reset(काष्ठा fsl_mc_io *mc_io,
	       u32 cmd_flags,
	       u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPIO_CMDID_RESET,
					  cmd_flags,
					  token);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण
