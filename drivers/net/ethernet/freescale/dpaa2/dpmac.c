<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/* Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2019 NXP
 */
#समावेश <linux/fsl/mc.h>
#समावेश "dpmac.h"
#समावेश "dpmac-cmd.h"

/**
 * dpmac_खोलो() - Open a control session क्रम the specअगरied object.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @dpmac_id:	DPMAC unique ID
 * @token:	Returned token; use in subsequent API calls
 *
 * This function can be used to खोलो a control session क्रम an
 * alपढ़ोy created object; an object may have been declared in
 * the DPL or by calling the dpmac_create function.
 * This function वापसs a unique authentication token,
 * associated with the specअगरic object ID and the specअगरic MC
 * portal; this token must be used in all subsequent commands क्रम
 * this specअगरic object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpmac_खोलो(काष्ठा fsl_mc_io *mc_io,
	       u32 cmd_flags,
	       पूर्णांक dpmac_id,
	       u16 *token)
अणु
	काष्ठा dpmac_cmd_खोलो *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_OPEN,
					  cmd_flags,
					  0);
	cmd_params = (काष्ठा dpmac_cmd_खोलो *)cmd.params;
	cmd_params->dpmac_id = cpu_to_le32(dpmac_id);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	*token = mc_cmd_hdr_पढ़ो_token(&cmd);

	वापस err;
पूर्ण

/**
 * dpmac_बंद() - Close the control session of the object
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPMAC object
 *
 * After this function is called, no further operations are
 * allowed on the object without खोलोing a new control session.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpmac_बंद(काष्ठा fsl_mc_io *mc_io,
		u32 cmd_flags,
		u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_CLOSE, cmd_flags,
					  token);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpmac_get_attributes - Retrieve DPMAC attributes.
 *
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPMAC object
 * @attr:	Returned object's attributes
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpmac_get_attributes(काष्ठा fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 token,
			 काष्ठा dpmac_attr *attr)
अणु
	काष्ठा dpmac_rsp_get_attributes *rsp_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_GET_ATTR,
					  cmd_flags,
					  token);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	rsp_params = (काष्ठा dpmac_rsp_get_attributes *)cmd.params;
	attr->eth_अगर = rsp_params->eth_अगर;
	attr->link_type = rsp_params->link_type;
	attr->id = le16_to_cpu(rsp_params->id);
	attr->max_rate = le32_to_cpu(rsp_params->max_rate);

	वापस 0;
पूर्ण

/**
 * dpmac_set_link_state() - Set the Ethernet link status
 * @mc_io:      Poपूर्णांकer to opaque I/O object
 * @cmd_flags:  Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:      Token of DPMAC object
 * @link_state: Link state configuration
 *
 * Return:      '0' on Success; Error code otherwise.
 */
पूर्णांक dpmac_set_link_state(काष्ठा fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 token,
			 काष्ठा dpmac_link_state *link_state)
अणु
	काष्ठा dpmac_cmd_set_link_state *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_SET_LINK_STATE,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpmac_cmd_set_link_state *)cmd.params;
	cmd_params->options = cpu_to_le64(link_state->options);
	cmd_params->rate = cpu_to_le32(link_state->rate);
	dpmac_set_field(cmd_params->state, STATE, link_state->up);
	dpmac_set_field(cmd_params->state, STATE_VALID,
			link_state->state_valid);
	cmd_params->supported = cpu_to_le64(link_state->supported);
	cmd_params->advertising = cpu_to_le64(link_state->advertising);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpmac_get_counter() - Read a specअगरic DPMAC counter
 * @mc_io:	Poपूर्णांकer to opaque I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPMAC object
 * @id:		The requested counter ID
 * @value:	Returned counter value
 *
 * Return:	The requested counter; '0' otherwise.
 */
पूर्णांक dpmac_get_counter(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
		      क्रमागत dpmac_counter_id id, u64 *value)
अणु
	काष्ठा dpmac_cmd_get_counter *dpmac_cmd;
	काष्ठा dpmac_rsp_get_counter *dpmac_rsp;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	पूर्णांक err = 0;

	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_GET_COUNTER,
					  cmd_flags,
					  token);
	dpmac_cmd = (काष्ठा dpmac_cmd_get_counter *)cmd.params;
	dpmac_cmd->id = id;

	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	dpmac_rsp = (काष्ठा dpmac_rsp_get_counter *)cmd.params;
	*value = le64_to_cpu(dpmac_rsp->counter);

	वापस 0;
पूर्ण
