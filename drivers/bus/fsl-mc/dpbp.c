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
 * dpbp_खोलो() - Open a control session क्रम the specअगरied object.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @dpbp_id:	DPBP unique ID
 * @token:	Returned token; use in subsequent API calls
 *
 * This function can be used to खोलो a control session क्रम an
 * alपढ़ोy created object; an object may have been declared in
 * the DPL or by calling the dpbp_create function.
 * This function वापसs a unique authentication token,
 * associated with the specअगरic object ID and the specअगरic MC
 * portal; this token must be used in all subsequent commands क्रम
 * this specअगरic object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpbp_खोलो(काष्ठा fsl_mc_io *mc_io,
	      u32 cmd_flags,
	      पूर्णांक dpbp_id,
	      u16 *token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpbp_cmd_खोलो *cmd_params;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPBP_CMDID_OPEN,
					  cmd_flags, 0);
	cmd_params = (काष्ठा dpbp_cmd_खोलो *)cmd.params;
	cmd_params->dpbp_id = cpu_to_le32(dpbp_id);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	*token = mc_cmd_hdr_पढ़ो_token(&cmd);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(dpbp_खोलो);

/**
 * dpbp_बंद() - Close the control session of the object
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPBP object
 *
 * After this function is called, no further operations are
 * allowed on the object without खोलोing a new control session.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpbp_बंद(काष्ठा fsl_mc_io *mc_io,
	       u32 cmd_flags,
	       u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPBP_CMDID_CLOSE, cmd_flags,
					  token);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण
EXPORT_SYMBOL_GPL(dpbp_बंद);

/**
 * dpbp_enable() - Enable the DPBP.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPBP object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpbp_enable(काष्ठा fsl_mc_io *mc_io,
		u32 cmd_flags,
		u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPBP_CMDID_ENABLE, cmd_flags,
					  token);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण
EXPORT_SYMBOL_GPL(dpbp_enable);

/**
 * dpbp_disable() - Disable the DPBP.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPBP object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpbp_disable(काष्ठा fsl_mc_io *mc_io,
		 u32 cmd_flags,
		 u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPBP_CMDID_DISABLE,
					  cmd_flags, token);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण
EXPORT_SYMBOL_GPL(dpbp_disable);

/**
 * dpbp_reset() - Reset the DPBP, वापसs the object to initial state.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPBP object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpbp_reset(काष्ठा fsl_mc_io *mc_io,
	       u32 cmd_flags,
	       u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPBP_CMDID_RESET,
					  cmd_flags, token);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण
EXPORT_SYMBOL_GPL(dpbp_reset);

/**
 * dpbp_get_attributes - Retrieve DPBP attributes.
 *
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPBP object
 * @attr:	Returned object's attributes
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpbp_get_attributes(काष्ठा fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			काष्ठा dpbp_attr *attr)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpbp_rsp_get_attributes *rsp_params;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPBP_CMDID_GET_ATTR,
					  cmd_flags, token);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	rsp_params = (काष्ठा dpbp_rsp_get_attributes *)cmd.params;
	attr->bpid = le16_to_cpu(rsp_params->bpid);
	attr->id = le32_to_cpu(rsp_params->id);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dpbp_get_attributes);
