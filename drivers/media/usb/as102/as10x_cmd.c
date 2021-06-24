<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Abilis Systems Single DVB-T Receiver
 * Copyright (C) 2008 Pierrick Hascoet <pierrick.hascoet@abilis.com>
 * Copyright (C) 2010 Devin Heiपंचांगueller <dheiपंचांगueller@kernelद_असल.com>
 */

#समावेश <linux/kernel.h>
#समावेश "as102_drv.h"
#समावेश "as10x_cmd.h"

/**
 * as10x_cmd_turn_on - send turn on command to AS10x
 * @adap:   poपूर्णांकer to AS10x bus adapter
 *
 * Return 0 when no error, < 0 in हाल of error.
 */
पूर्णांक as10x_cmd_turn_on(काष्ठा as10x_bus_adapter_t *adap)
अणु
	पूर्णांक error = AS10X_CMD_ERROR;
	काष्ठा as10x_cmd_t *pcmd, *prsp;

	pcmd = adap->cmd;
	prsp = adap->rsp;

	/* prepare command */
	as10x_cmd_build(pcmd, (++adap->cmd_xid),
			माप(pcmd->body.turn_on.req));

	/* fill command */
	pcmd->body.turn_on.req.proc_id = cpu_to_le16(CONTROL_PROC_TURNON);

	/* send command */
	अगर (adap->ops->xfer_cmd) अणु
		error = adap->ops->xfer_cmd(adap, (uपूर्णांक8_t *) pcmd,
					    माप(pcmd->body.turn_on.req) +
					    HEADER_SIZE,
					    (uपूर्णांक8_t *) prsp,
					    माप(prsp->body.turn_on.rsp) +
					    HEADER_SIZE);
	पूर्ण

	अगर (error < 0)
		जाओ out;

	/* parse response */
	error = as10x_rsp_parse(prsp, CONTROL_PROC_TURNON_RSP);

out:
	वापस error;
पूर्ण

/**
 * as10x_cmd_turn_off - send turn off command to AS10x
 * @adap:   poपूर्णांकer to AS10x bus adapter
 *
 * Return 0 on success or negative value in हाल of error.
 */
पूर्णांक as10x_cmd_turn_off(काष्ठा as10x_bus_adapter_t *adap)
अणु
	पूर्णांक error = AS10X_CMD_ERROR;
	काष्ठा as10x_cmd_t *pcmd, *prsp;

	pcmd = adap->cmd;
	prsp = adap->rsp;

	/* prepare command */
	as10x_cmd_build(pcmd, (++adap->cmd_xid),
			माप(pcmd->body.turn_off.req));

	/* fill command */
	pcmd->body.turn_off.req.proc_id = cpu_to_le16(CONTROL_PROC_TURNOFF);

	/* send command */
	अगर (adap->ops->xfer_cmd) अणु
		error = adap->ops->xfer_cmd(
			adap, (uपूर्णांक8_t *) pcmd,
			माप(pcmd->body.turn_off.req) + HEADER_SIZE,
			(uपूर्णांक8_t *) prsp,
			माप(prsp->body.turn_off.rsp) + HEADER_SIZE);
	पूर्ण

	अगर (error < 0)
		जाओ out;

	/* parse response */
	error = as10x_rsp_parse(prsp, CONTROL_PROC_TURNOFF_RSP);

out:
	वापस error;
पूर्ण

/**
 * as10x_cmd_set_tune - send set tune command to AS10x
 * @adap:    poपूर्णांकer to AS10x bus adapter
 * @ptune:   tune parameters
 *
 * Return 0 on success or negative value in हाल of error.
 */
पूर्णांक as10x_cmd_set_tune(काष्ठा as10x_bus_adapter_t *adap,
		       काष्ठा as10x_tune_args *ptune)
अणु
	पूर्णांक error = AS10X_CMD_ERROR;
	काष्ठा as10x_cmd_t *preq, *prsp;

	preq = adap->cmd;
	prsp = adap->rsp;

	/* prepare command */
	as10x_cmd_build(preq, (++adap->cmd_xid),
			माप(preq->body.set_tune.req));

	/* fill command */
	preq->body.set_tune.req.proc_id = cpu_to_le16(CONTROL_PROC_SETTUNE);
	preq->body.set_tune.req.args.freq = (__क्रमce __u32)cpu_to_le32(ptune->freq);
	preq->body.set_tune.req.args.bandwidth = ptune->bandwidth;
	preq->body.set_tune.req.args.hier_select = ptune->hier_select;
	preq->body.set_tune.req.args.modulation = ptune->modulation;
	preq->body.set_tune.req.args.hierarchy = ptune->hierarchy;
	preq->body.set_tune.req.args.पूर्णांकerleaving_mode  =
		ptune->पूर्णांकerleaving_mode;
	preq->body.set_tune.req.args.code_rate  = ptune->code_rate;
	preq->body.set_tune.req.args.guard_पूर्णांकerval = ptune->guard_पूर्णांकerval;
	preq->body.set_tune.req.args.transmission_mode  =
		ptune->transmission_mode;

	/* send command */
	अगर (adap->ops->xfer_cmd) अणु
		error = adap->ops->xfer_cmd(adap,
					    (uपूर्णांक8_t *) preq,
					    माप(preq->body.set_tune.req)
					    + HEADER_SIZE,
					    (uपूर्णांक8_t *) prsp,
					    माप(prsp->body.set_tune.rsp)
					    + HEADER_SIZE);
	पूर्ण

	अगर (error < 0)
		जाओ out;

	/* parse response */
	error = as10x_rsp_parse(prsp, CONTROL_PROC_SETTUNE_RSP);

out:
	वापस error;
पूर्ण

/**
 * as10x_cmd_get_tune_status - send get tune status command to AS10x
 * @adap: poपूर्णांकer to AS10x bus adapter
 * @pstatus: poपूर्णांकer to updated status काष्ठाure of the current tune
 *
 * Return 0 on success or negative value in हाल of error.
 */
पूर्णांक as10x_cmd_get_tune_status(काष्ठा as10x_bus_adapter_t *adap,
			      काष्ठा as10x_tune_status *pstatus)
अणु
	पूर्णांक error = AS10X_CMD_ERROR;
	काष्ठा as10x_cmd_t  *preq, *prsp;

	preq = adap->cmd;
	prsp = adap->rsp;

	/* prepare command */
	as10x_cmd_build(preq, (++adap->cmd_xid),
			माप(preq->body.get_tune_status.req));

	/* fill command */
	preq->body.get_tune_status.req.proc_id =
		cpu_to_le16(CONTROL_PROC_GETTUNESTAT);

	/* send command */
	अगर (adap->ops->xfer_cmd) अणु
		error = adap->ops->xfer_cmd(
			adap,
			(uपूर्णांक8_t *) preq,
			माप(preq->body.get_tune_status.req) + HEADER_SIZE,
			(uपूर्णांक8_t *) prsp,
			माप(prsp->body.get_tune_status.rsp) + HEADER_SIZE);
	पूर्ण

	अगर (error < 0)
		जाओ out;

	/* parse response */
	error = as10x_rsp_parse(prsp, CONTROL_PROC_GETTUNESTAT_RSP);
	अगर (error < 0)
		जाओ out;

	/* Response OK -> get response data */
	pstatus->tune_state = prsp->body.get_tune_status.rsp.sts.tune_state;
	pstatus->संकेत_strength  =
		le16_to_cpu((__क्रमce __le16)prsp->body.get_tune_status.rsp.sts.संकेत_strength);
	pstatus->PER = le16_to_cpu((__क्रमce __le16)prsp->body.get_tune_status.rsp.sts.PER);
	pstatus->BER = le16_to_cpu((__क्रमce __le16)prsp->body.get_tune_status.rsp.sts.BER);

out:
	वापस error;
पूर्ण

/**
 * as10x_cmd_get_tps - send get TPS command to AS10x
 * @adap:      poपूर्णांकer to AS10x handle
 * @ptps:      poपूर्णांकer to TPS parameters काष्ठाure
 *
 * Return 0 on success or negative value in हाल of error.
 */
पूर्णांक as10x_cmd_get_tps(काष्ठा as10x_bus_adapter_t *adap, काष्ठा as10x_tps *ptps)
अणु
	पूर्णांक error = AS10X_CMD_ERROR;
	काष्ठा as10x_cmd_t *pcmd, *prsp;

	pcmd = adap->cmd;
	prsp = adap->rsp;

	/* prepare command */
	as10x_cmd_build(pcmd, (++adap->cmd_xid),
			माप(pcmd->body.get_tps.req));

	/* fill command */
	pcmd->body.get_tune_status.req.proc_id =
		cpu_to_le16(CONTROL_PROC_GETTPS);

	/* send command */
	अगर (adap->ops->xfer_cmd) अणु
		error = adap->ops->xfer_cmd(adap,
					    (uपूर्णांक8_t *) pcmd,
					    माप(pcmd->body.get_tps.req) +
					    HEADER_SIZE,
					    (uपूर्णांक8_t *) prsp,
					    माप(prsp->body.get_tps.rsp) +
					    HEADER_SIZE);
	पूर्ण

	अगर (error < 0)
		जाओ out;

	/* parse response */
	error = as10x_rsp_parse(prsp, CONTROL_PROC_GETTPS_RSP);
	अगर (error < 0)
		जाओ out;

	/* Response OK -> get response data */
	ptps->modulation = prsp->body.get_tps.rsp.tps.modulation;
	ptps->hierarchy = prsp->body.get_tps.rsp.tps.hierarchy;
	ptps->पूर्णांकerleaving_mode = prsp->body.get_tps.rsp.tps.पूर्णांकerleaving_mode;
	ptps->code_rate_HP = prsp->body.get_tps.rsp.tps.code_rate_HP;
	ptps->code_rate_LP = prsp->body.get_tps.rsp.tps.code_rate_LP;
	ptps->guard_पूर्णांकerval = prsp->body.get_tps.rsp.tps.guard_पूर्णांकerval;
	ptps->transmission_mode  = prsp->body.get_tps.rsp.tps.transmission_mode;
	ptps->DVBH_mask_HP = prsp->body.get_tps.rsp.tps.DVBH_mask_HP;
	ptps->DVBH_mask_LP = prsp->body.get_tps.rsp.tps.DVBH_mask_LP;
	ptps->cell_ID = le16_to_cpu((__क्रमce __le16)prsp->body.get_tps.rsp.tps.cell_ID);

out:
	वापस error;
पूर्ण

/**
 * as10x_cmd_get_demod_stats - send get demod stats command to AS10x
 * @adap:          poपूर्णांकer to AS10x bus adapter
 * @pdemod_stats:  poपूर्णांकer to demod stats parameters काष्ठाure
 *
 * Return 0 on success or negative value in हाल of error.
 */
पूर्णांक as10x_cmd_get_demod_stats(काष्ठा as10x_bus_adapter_t *adap,
			      काष्ठा as10x_demod_stats *pdemod_stats)
अणु
	पूर्णांक error = AS10X_CMD_ERROR;
	काष्ठा as10x_cmd_t *pcmd, *prsp;

	pcmd = adap->cmd;
	prsp = adap->rsp;

	/* prepare command */
	as10x_cmd_build(pcmd, (++adap->cmd_xid),
			माप(pcmd->body.get_demod_stats.req));

	/* fill command */
	pcmd->body.get_demod_stats.req.proc_id =
		cpu_to_le16(CONTROL_PROC_GET_DEMOD_STATS);

	/* send command */
	अगर (adap->ops->xfer_cmd) अणु
		error = adap->ops->xfer_cmd(adap,
				(uपूर्णांक8_t *) pcmd,
				माप(pcmd->body.get_demod_stats.req)
				+ HEADER_SIZE,
				(uपूर्णांक8_t *) prsp,
				माप(prsp->body.get_demod_stats.rsp)
				+ HEADER_SIZE);
	पूर्ण

	अगर (error < 0)
		जाओ out;

	/* parse response */
	error = as10x_rsp_parse(prsp, CONTROL_PROC_GET_DEMOD_STATS_RSP);
	अगर (error < 0)
		जाओ out;

	/* Response OK -> get response data */
	pdemod_stats->frame_count =
		le32_to_cpu((__क्रमce __le32)prsp->body.get_demod_stats.rsp.stats.frame_count);
	pdemod_stats->bad_frame_count =
		le32_to_cpu((__क्रमce __le32)prsp->body.get_demod_stats.rsp.stats.bad_frame_count);
	pdemod_stats->bytes_fixed_by_rs =
		le32_to_cpu((__क्रमce __le32)prsp->body.get_demod_stats.rsp.stats.bytes_fixed_by_rs);
	pdemod_stats->mer =
		le16_to_cpu((__क्रमce __le16)prsp->body.get_demod_stats.rsp.stats.mer);
	pdemod_stats->has_started =
		prsp->body.get_demod_stats.rsp.stats.has_started;

out:
	वापस error;
पूर्ण

/**
 * as10x_cmd_get_impulse_resp - send get impulse response command to AS10x
 * @adap:     poपूर्णांकer to AS10x bus adapter
 * @is_पढ़ोy: poपूर्णांकer to value indicating when impulse
 *	      response data is पढ़ोy
 *
 * Return 0 on success or negative value in हाल of error.
 */
पूर्णांक as10x_cmd_get_impulse_resp(काष्ठा as10x_bus_adapter_t *adap,
			       uपूर्णांक8_t *is_पढ़ोy)
अणु
	पूर्णांक error = AS10X_CMD_ERROR;
	काष्ठा as10x_cmd_t *pcmd, *prsp;

	pcmd = adap->cmd;
	prsp = adap->rsp;

	/* prepare command */
	as10x_cmd_build(pcmd, (++adap->cmd_xid),
			माप(pcmd->body.get_impulse_rsp.req));

	/* fill command */
	pcmd->body.get_impulse_rsp.req.proc_id =
		cpu_to_le16(CONTROL_PROC_GET_IMPULSE_RESP);

	/* send command */
	अगर (adap->ops->xfer_cmd) अणु
		error = adap->ops->xfer_cmd(adap,
					(uपूर्णांक8_t *) pcmd,
					माप(pcmd->body.get_impulse_rsp.req)
					+ HEADER_SIZE,
					(uपूर्णांक8_t *) prsp,
					माप(prsp->body.get_impulse_rsp.rsp)
					+ HEADER_SIZE);
	पूर्ण

	अगर (error < 0)
		जाओ out;

	/* parse response */
	error = as10x_rsp_parse(prsp, CONTROL_PROC_GET_IMPULSE_RESP_RSP);
	अगर (error < 0)
		जाओ out;

	/* Response OK -> get response data */
	*is_पढ़ोy = prsp->body.get_impulse_rsp.rsp.is_पढ़ोy;

out:
	वापस error;
पूर्ण

/**
 * as10x_cmd_build - build AS10x command header
 * @pcmd:     poपूर्णांकer to AS10x command buffer
 * @xid:      sequence id of the command
 * @cmd_len:  length of the command
 */
व्योम as10x_cmd_build(काष्ठा as10x_cmd_t *pcmd,
		     uपूर्णांक16_t xid, uपूर्णांक16_t cmd_len)
अणु
	pcmd->header.req_id = cpu_to_le16(xid);
	pcmd->header.prog = cpu_to_le16(SERVICE_PROG_ID);
	pcmd->header.version = cpu_to_le16(SERVICE_PROG_VERSION);
	pcmd->header.data_len = cpu_to_le16(cmd_len);
पूर्ण

/**
 * as10x_rsp_parse - Parse command response
 * @prsp:       poपूर्णांकer to AS10x command buffer
 * @proc_id:    id of the command
 *
 * Return 0 on success or negative value in हाल of error.
 */
पूर्णांक as10x_rsp_parse(काष्ठा as10x_cmd_t *prsp, uपूर्णांक16_t proc_id)
अणु
	पूर्णांक error;

	/* extract command error code */
	error = prsp->body.common.rsp.error;

	अगर ((error == 0) &&
	    (le16_to_cpu(prsp->body.common.rsp.proc_id) == proc_id)) अणु
		वापस 0;
	पूर्ण

	वापस AS10X_CMD_ERROR;
पूर्ण
