<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Abilis Systems Single DVB-T Receiver
 * Copyright (C) 2008 Pierrick Hascoet <pierrick.hascoet@abilis.com>
 */

#समावेश <linux/kernel.h>
#समावेश "as102_drv.h"
#समावेश "as10x_cmd.h"

/***************************/
/* FUNCTION DEFINITION     */
/***************************/

/**
 * as10x_cmd_get_context - Send get context command to AS10x
 * @adap:      poपूर्णांकer to AS10x bus adapter
 * @tag:       context tag
 * @pvalue:    poपूर्णांकer where to store context value पढ़ो
 *
 * Return 0 on success or negative value in हाल of error.
 */
पूर्णांक as10x_cmd_get_context(काष्ठा as10x_bus_adapter_t *adap, uपूर्णांक16_t tag,
			  uपूर्णांक32_t *pvalue)
अणु
	पूर्णांक  error;
	काष्ठा as10x_cmd_t *pcmd, *prsp;

	pcmd = adap->cmd;
	prsp = adap->rsp;

	/* prepare command */
	as10x_cmd_build(pcmd, (++adap->cmd_xid),
			माप(pcmd->body.context.req));

	/* fill command */
	pcmd->body.context.req.proc_id = cpu_to_le16(CONTROL_PROC_CONTEXT);
	pcmd->body.context.req.tag = cpu_to_le16(tag);
	pcmd->body.context.req.type = cpu_to_le16(GET_CONTEXT_DATA);

	/* send command */
	अगर (adap->ops->xfer_cmd) अणु
		error  = adap->ops->xfer_cmd(adap,
					     (uपूर्णांक8_t *) pcmd,
					     माप(pcmd->body.context.req)
					     + HEADER_SIZE,
					     (uपूर्णांक8_t *) prsp,
					     माप(prsp->body.context.rsp)
					     + HEADER_SIZE);
	पूर्ण अन्यथा अणु
		error = AS10X_CMD_ERROR;
	पूर्ण

	अगर (error < 0)
		जाओ out;

	/* parse response: context command करो not follow the common response */
	/* काष्ठाure -> specअगरic handling response parse required            */
	error = as10x_context_rsp_parse(prsp, CONTROL_PROC_CONTEXT_RSP);

	अगर (error == 0) अणु
		/* Response OK -> get response data */
		*pvalue = le32_to_cpu((__क्रमce __le32)prsp->body.context.rsp.reg_val.u.value32);
		/* value वापसed is always a 32-bit value */
	पूर्ण

out:
	वापस error;
पूर्ण

/**
 * as10x_cmd_set_context - send set context command to AS10x
 * @adap:      poपूर्णांकer to AS10x bus adapter
 * @tag:       context tag
 * @value:     value to set in context
 *
 * Return 0 on success or negative value in हाल of error.
 */
पूर्णांक as10x_cmd_set_context(काष्ठा as10x_bus_adapter_t *adap, uपूर्णांक16_t tag,
			  uपूर्णांक32_t value)
अणु
	पूर्णांक error;
	काष्ठा as10x_cmd_t *pcmd, *prsp;

	pcmd = adap->cmd;
	prsp = adap->rsp;

	/* prepare command */
	as10x_cmd_build(pcmd, (++adap->cmd_xid),
			माप(pcmd->body.context.req));

	/* fill command */
	pcmd->body.context.req.proc_id = cpu_to_le16(CONTROL_PROC_CONTEXT);
	/* pcmd->body.context.req.reg_val.mode initialization is not required */
	pcmd->body.context.req.reg_val.u.value32 = (__क्रमce u32)cpu_to_le32(value);
	pcmd->body.context.req.tag = cpu_to_le16(tag);
	pcmd->body.context.req.type = cpu_to_le16(SET_CONTEXT_DATA);

	/* send command */
	अगर (adap->ops->xfer_cmd) अणु
		error  = adap->ops->xfer_cmd(adap,
					     (uपूर्णांक8_t *) pcmd,
					     माप(pcmd->body.context.req)
					     + HEADER_SIZE,
					     (uपूर्णांक8_t *) prsp,
					     माप(prsp->body.context.rsp)
					     + HEADER_SIZE);
	पूर्ण अन्यथा अणु
		error = AS10X_CMD_ERROR;
	पूर्ण

	अगर (error < 0)
		जाओ out;

	/* parse response: context command करो not follow the common response */
	/* काष्ठाure -> specअगरic handling response parse required            */
	error = as10x_context_rsp_parse(prsp, CONTROL_PROC_CONTEXT_RSP);

out:
	वापस error;
पूर्ण

/**
 * as10x_cmd_eLNA_change_mode - send eLNA change mode command to AS10x
 * @adap:      poपूर्णांकer to AS10x bus adapter
 * @mode:      mode selected:
 *		- ON    : 0x0 => eLNA always ON
 *		- OFF   : 0x1 => eLNA always OFF
 *		- AUTO  : 0x2 => eLNA follow hysteresis parameters
 *				 to be ON or OFF
 *
 * Return 0 on success or negative value in हाल of error.
 */
पूर्णांक as10x_cmd_eLNA_change_mode(काष्ठा as10x_bus_adapter_t *adap, uपूर्णांक8_t mode)
अणु
	पूर्णांक error;
	काष्ठा as10x_cmd_t *pcmd, *prsp;

	pcmd = adap->cmd;
	prsp = adap->rsp;

	/* prepare command */
	as10x_cmd_build(pcmd, (++adap->cmd_xid),
			माप(pcmd->body.cfg_change_mode.req));

	/* fill command */
	pcmd->body.cfg_change_mode.req.proc_id =
		cpu_to_le16(CONTROL_PROC_ELNA_CHANGE_MODE);
	pcmd->body.cfg_change_mode.req.mode = mode;

	/* send command */
	अगर (adap->ops->xfer_cmd) अणु
		error  = adap->ops->xfer_cmd(adap, (uपूर्णांक8_t *) pcmd,
				माप(pcmd->body.cfg_change_mode.req)
				+ HEADER_SIZE, (uपूर्णांक8_t *) prsp,
				माप(prsp->body.cfg_change_mode.rsp)
				+ HEADER_SIZE);
	पूर्ण अन्यथा अणु
		error = AS10X_CMD_ERROR;
	पूर्ण

	अगर (error < 0)
		जाओ out;

	/* parse response */
	error = as10x_rsp_parse(prsp, CONTROL_PROC_ELNA_CHANGE_MODE_RSP);

out:
	वापस error;
पूर्ण

/**
 * as10x_context_rsp_parse - Parse context command response
 * @prsp:       poपूर्णांकer to AS10x command response buffer
 * @proc_id:    id of the command
 *
 * Since the contex command response करोes not follow the common
 * response, a specअगरic parse function is required.
 * Return 0 on success or negative value in हाल of error.
 */
पूर्णांक as10x_context_rsp_parse(काष्ठा as10x_cmd_t *prsp, uपूर्णांक16_t proc_id)
अणु
	पूर्णांक err;

	err = prsp->body.context.rsp.error;

	अगर ((err == 0) &&
	    (le16_to_cpu(prsp->body.context.rsp.proc_id) == proc_id)) अणु
		वापस 0;
	पूर्ण
	वापस AS10X_CMD_ERROR;
पूर्ण
