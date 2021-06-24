<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Abilis Systems Single DVB-T Receiver
 * Copyright (C) 2008 Pierrick Hascoet <pierrick.hascoet@abilis.com>
 */

#समावेश <linux/kernel.h>
#समावेश "as102_drv.h"
#समावेश "as10x_cmd.h"

/**
 * as10x_cmd_add_PID_filter - send add filter command to AS10x
 * @adap:      poपूर्णांकer to AS10x bus adapter
 * @filter:    TSFilter filter क्रम DVB-T
 *
 * Return 0 on success or negative value in हाल of error.
 */
पूर्णांक as10x_cmd_add_PID_filter(काष्ठा as10x_bus_adapter_t *adap,
			     काष्ठा as10x_ts_filter *filter)
अणु
	पूर्णांक error;
	काष्ठा as10x_cmd_t *pcmd, *prsp;

	pcmd = adap->cmd;
	prsp = adap->rsp;

	/* prepare command */
	as10x_cmd_build(pcmd, (++adap->cmd_xid),
			माप(pcmd->body.add_pid_filter.req));

	/* fill command */
	pcmd->body.add_pid_filter.req.proc_id =
		cpu_to_le16(CONTROL_PROC_SETFILTER);
	pcmd->body.add_pid_filter.req.pid = cpu_to_le16(filter->pid);
	pcmd->body.add_pid_filter.req.stream_type = filter->type;

	अगर (filter->idx < 16)
		pcmd->body.add_pid_filter.req.idx = filter->idx;
	अन्यथा
		pcmd->body.add_pid_filter.req.idx = 0xFF;

	/* send command */
	अगर (adap->ops->xfer_cmd) अणु
		error = adap->ops->xfer_cmd(adap, (uपूर्णांक8_t *) pcmd,
				माप(pcmd->body.add_pid_filter.req)
				+ HEADER_SIZE, (uपूर्णांक8_t *) prsp,
				माप(prsp->body.add_pid_filter.rsp)
				+ HEADER_SIZE);
	पूर्ण अन्यथा अणु
		error = AS10X_CMD_ERROR;
	पूर्ण

	अगर (error < 0)
		जाओ out;

	/* parse response */
	error = as10x_rsp_parse(prsp, CONTROL_PROC_SETFILTER_RSP);

	अगर (error == 0) अणु
		/* Response OK -> get response data */
		filter->idx = prsp->body.add_pid_filter.rsp.filter_id;
	पूर्ण

out:
	वापस error;
पूर्ण

/**
 * as10x_cmd_del_PID_filter - Send delete filter command to AS10x
 * @adap:         poपूर्णांकer to AS10x bus adapte
 * @pid_value:    PID to delete
 *
 * Return 0 on success or negative value in हाल of error.
 */
पूर्णांक as10x_cmd_del_PID_filter(काष्ठा as10x_bus_adapter_t *adap,
			     uपूर्णांक16_t pid_value)
अणु
	पूर्णांक error;
	काष्ठा as10x_cmd_t *pcmd, *prsp;

	pcmd = adap->cmd;
	prsp = adap->rsp;

	/* prepare command */
	as10x_cmd_build(pcmd, (++adap->cmd_xid),
			माप(pcmd->body.del_pid_filter.req));

	/* fill command */
	pcmd->body.del_pid_filter.req.proc_id =
		cpu_to_le16(CONTROL_PROC_REMOVEFILTER);
	pcmd->body.del_pid_filter.req.pid = cpu_to_le16(pid_value);

	/* send command */
	अगर (adap->ops->xfer_cmd) अणु
		error = adap->ops->xfer_cmd(adap, (uपूर्णांक8_t *) pcmd,
				माप(pcmd->body.del_pid_filter.req)
				+ HEADER_SIZE, (uपूर्णांक8_t *) prsp,
				माप(prsp->body.del_pid_filter.rsp)
				+ HEADER_SIZE);
	पूर्ण अन्यथा अणु
		error = AS10X_CMD_ERROR;
	पूर्ण

	अगर (error < 0)
		जाओ out;

	/* parse response */
	error = as10x_rsp_parse(prsp, CONTROL_PROC_REMOVEFILTER_RSP);

out:
	वापस error;
पूर्ण

/**
 * as10x_cmd_start_streaming - Send start streaming command to AS10x
 * @adap:   poपूर्णांकer to AS10x bus adapter
 *
 * Return 0 on success or negative value in हाल of error.
 */
पूर्णांक as10x_cmd_start_streaming(काष्ठा as10x_bus_adapter_t *adap)
अणु
	पूर्णांक error;
	काष्ठा as10x_cmd_t *pcmd, *prsp;

	pcmd = adap->cmd;
	prsp = adap->rsp;

	/* prepare command */
	as10x_cmd_build(pcmd, (++adap->cmd_xid),
			माप(pcmd->body.start_streaming.req));

	/* fill command */
	pcmd->body.start_streaming.req.proc_id =
		cpu_to_le16(CONTROL_PROC_START_STREAMING);

	/* send command */
	अगर (adap->ops->xfer_cmd) अणु
		error = adap->ops->xfer_cmd(adap, (uपूर्णांक8_t *) pcmd,
				माप(pcmd->body.start_streaming.req)
				+ HEADER_SIZE, (uपूर्णांक8_t *) prsp,
				माप(prsp->body.start_streaming.rsp)
				+ HEADER_SIZE);
	पूर्ण अन्यथा अणु
		error = AS10X_CMD_ERROR;
	पूर्ण

	अगर (error < 0)
		जाओ out;

	/* parse response */
	error = as10x_rsp_parse(prsp, CONTROL_PROC_START_STREAMING_RSP);

out:
	वापस error;
पूर्ण

/**
 * as10x_cmd_stop_streaming - Send stop streaming command to AS10x
 * @adap:   poपूर्णांकer to AS10x bus adapter
 *
 * Return 0 on success or negative value in हाल of error.
 */
पूर्णांक as10x_cmd_stop_streaming(काष्ठा as10x_bus_adapter_t *adap)
अणु
	पूर्णांक8_t error;
	काष्ठा as10x_cmd_t *pcmd, *prsp;

	pcmd = adap->cmd;
	prsp = adap->rsp;

	/* prepare command */
	as10x_cmd_build(pcmd, (++adap->cmd_xid),
			माप(pcmd->body.stop_streaming.req));

	/* fill command */
	pcmd->body.stop_streaming.req.proc_id =
		cpu_to_le16(CONTROL_PROC_STOP_STREAMING);

	/* send command */
	अगर (adap->ops->xfer_cmd) अणु
		error = adap->ops->xfer_cmd(adap, (uपूर्णांक8_t *) pcmd,
				माप(pcmd->body.stop_streaming.req)
				+ HEADER_SIZE, (uपूर्णांक8_t *) prsp,
				माप(prsp->body.stop_streaming.rsp)
				+ HEADER_SIZE);
	पूर्ण अन्यथा अणु
		error = AS10X_CMD_ERROR;
	पूर्ण

	अगर (error < 0)
		जाओ out;

	/* parse response */
	error = as10x_rsp_parse(prsp, CONTROL_PROC_STOP_STREAMING_RSP);

out:
	वापस error;
पूर्ण
