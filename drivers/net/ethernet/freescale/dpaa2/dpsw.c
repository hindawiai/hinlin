<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2014-2016 Freescale Semiconductor Inc.
 * Copyright 2017-2021 NXP
 *
 */

#समावेश <linux/fsl/mc.h>
#समावेश "dpsw.h"
#समावेश "dpsw-cmd.h"

अटल व्योम build_अगर_id_biपंचांगap(__le64 *bmap, स्थिर u16 *id, स्थिर u16 num_अगरs)
अणु
	पूर्णांक i;

	क्रम (i = 0; (i < num_अगरs) && (i < DPSW_MAX_IF); i++) अणु
		अगर (id[i] < DPSW_MAX_IF)
			bmap[id[i] / 64] |= cpu_to_le64(BIT_MASK(id[i] % 64));
	पूर्ण
पूर्ण

/**
 * dpsw_खोलो() - Open a control session क्रम the specअगरied object
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @dpsw_id:	DPSW unique ID
 * @token:	Returned token; use in subsequent API calls
 *
 * This function can be used to खोलो a control session क्रम an
 * alपढ़ोy created object; an object may have been declared in
 * the DPL or by calling the dpsw_create() function.
 * This function वापसs a unique authentication token,
 * associated with the specअगरic object ID and the specअगरic MC
 * portal; this token must be used in all subsequent commands क्रम
 * this specअगरic object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_खोलो(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, पूर्णांक dpsw_id, u16 *token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_खोलो *cmd_params;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_OPEN,
					  cmd_flags,
					  0);
	cmd_params = (काष्ठा dpsw_cmd_खोलो *)cmd.params;
	cmd_params->dpsw_id = cpu_to_le32(dpsw_id);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	*token = mc_cmd_hdr_पढ़ो_token(&cmd);

	वापस 0;
पूर्ण

/**
 * dpsw_बंद() - Close the control session of the object
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 *
 * After this function is called, no further operations are
 * allowed on the object without खोलोing a new control session.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_बंद(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_CLOSE,
					  cmd_flags,
					  token);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_enable() - Enable DPSW functionality
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_enable(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_ENABLE,
					  cmd_flags,
					  token);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_disable() - Disable DPSW functionality
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_disable(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_DISABLE,
					  cmd_flags,
					  token);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_reset() - Reset the DPSW, वापसs the object to initial state.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_reset(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_RESET,
					  cmd_flags,
					  token);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_set_irq_enable() - Set overall पूर्णांकerrupt state.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPCI object
 * @irq_index:	The पूर्णांकerrupt index to configure
 * @en:		Interrupt state - enable = 1, disable = 0
 *
 * Allows GPP software to control when पूर्णांकerrupts are generated.
 * Each पूर्णांकerrupt can have up to 32 causes.  The enable/disable control's the
 * overall पूर्णांकerrupt state. अगर the पूर्णांकerrupt is disabled no causes will cause
 * an पूर्णांकerrupt
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_set_irq_enable(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			u8 irq_index, u8 en)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_set_irq_enable *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_SET_IRQ_ENABLE,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_set_irq_enable *)cmd.params;
	dpsw_set_field(cmd_params->enable_state, ENABLE, en);
	cmd_params->irq_index = irq_index;

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_set_irq_mask() - Set पूर्णांकerrupt mask.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPCI object
 * @irq_index:	The पूर्णांकerrupt index to configure
 * @mask:	Event mask to trigger पूर्णांकerrupt;
 *		each bit:
 *			0 = ignore event
 *			1 = consider event क्रम निश्चितing IRQ
 *
 * Every पूर्णांकerrupt can have up to 32 causes and the पूर्णांकerrupt model supports
 * masking/unmasking each cause independently
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_set_irq_mask(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
		      u8 irq_index, u32 mask)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_set_irq_mask *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_SET_IRQ_MASK,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_set_irq_mask *)cmd.params;
	cmd_params->mask = cpu_to_le32(mask);
	cmd_params->irq_index = irq_index;

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_get_irq_status() - Get the current status of any pending पूर्णांकerrupts
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @irq_index:	The पूर्णांकerrupt index to configure
 * @status:	Returned पूर्णांकerrupts status - one bit per cause:
 *			0 = no पूर्णांकerrupt pending
 *			1 = पूर्णांकerrupt pending
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_get_irq_status(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			u8 irq_index, u32 *status)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_get_irq_status *cmd_params;
	काष्ठा dpsw_rsp_get_irq_status *rsp_params;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_GET_IRQ_STATUS,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_get_irq_status *)cmd.params;
	cmd_params->status = cpu_to_le32(*status);
	cmd_params->irq_index = irq_index;

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	rsp_params = (काष्ठा dpsw_rsp_get_irq_status *)cmd.params;
	*status = le32_to_cpu(rsp_params->status);

	वापस 0;
पूर्ण

/**
 * dpsw_clear_irq_status() - Clear a pending पूर्णांकerrupt's status
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPCI object
 * @irq_index:	The पूर्णांकerrupt index to configure
 * @status:	bits to clear (W1C) - one bit per cause:
 *			0 = करोn't change
 *			1 = clear status bit
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_clear_irq_status(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			  u8 irq_index, u32 status)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_clear_irq_status *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_CLEAR_IRQ_STATUS,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_clear_irq_status *)cmd.params;
	cmd_params->status = cpu_to_le32(status);
	cmd_params->irq_index = irq_index;

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_get_attributes() - Retrieve DPSW attributes
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @attr:	Returned DPSW attributes
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_get_attributes(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			काष्ठा dpsw_attr *attr)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_rsp_get_attr *rsp_params;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_GET_ATTR,
					  cmd_flags,
					  token);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	rsp_params = (काष्ठा dpsw_rsp_get_attr *)cmd.params;
	attr->num_अगरs = le16_to_cpu(rsp_params->num_अगरs);
	attr->max_fdbs = rsp_params->max_fdbs;
	attr->num_fdbs = rsp_params->num_fdbs;
	attr->max_vlans = le16_to_cpu(rsp_params->max_vlans);
	attr->num_vlans = le16_to_cpu(rsp_params->num_vlans);
	attr->max_fdb_entries = le16_to_cpu(rsp_params->max_fdb_entries);
	attr->fdb_aging_समय = le16_to_cpu(rsp_params->fdb_aging_समय);
	attr->id = le32_to_cpu(rsp_params->dpsw_id);
	attr->mem_size = le16_to_cpu(rsp_params->mem_size);
	attr->max_fdb_mc_groups = le16_to_cpu(rsp_params->max_fdb_mc_groups);
	attr->max_meters_per_अगर = rsp_params->max_meters_per_अगर;
	attr->options = le64_to_cpu(rsp_params->options);
	attr->component_type = dpsw_get_field(rsp_params->component_type, COMPONENT_TYPE);
	attr->flooding_cfg = dpsw_get_field(rsp_params->repl_cfg, FLOODING_CFG);
	attr->broadcast_cfg = dpsw_get_field(rsp_params->repl_cfg, BROADCAST_CFG);
	वापस 0;
पूर्ण

/**
 * dpsw_अगर_set_link_cfg() - Set the link configuration.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @अगर_id:	Interface id
 * @cfg:	Link configuration
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_अगर_set_link_cfg(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token, u16 अगर_id,
			 काष्ठा dpsw_link_cfg *cfg)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_अगर_set_link_cfg *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_IF_SET_LINK_CFG,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_अगर_set_link_cfg *)cmd.params;
	cmd_params->अगर_id = cpu_to_le16(अगर_id);
	cmd_params->rate = cpu_to_le32(cfg->rate);
	cmd_params->options = cpu_to_le64(cfg->options);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_अगर_get_link_state - Return the link state
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @अगर_id:	Interface id
 * @state:	Link state	1 - linkup, 0 - link करोwn or disconnected
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_अगर_get_link_state(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			   u16 अगर_id, काष्ठा dpsw_link_state *state)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_अगर_get_link_state *cmd_params;
	काष्ठा dpsw_rsp_अगर_get_link_state *rsp_params;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_IF_GET_LINK_STATE,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_अगर_get_link_state *)cmd.params;
	cmd_params->अगर_id = cpu_to_le16(अगर_id);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	rsp_params = (काष्ठा dpsw_rsp_अगर_get_link_state *)cmd.params;
	state->rate = le32_to_cpu(rsp_params->rate);
	state->options = le64_to_cpu(rsp_params->options);
	state->up = dpsw_get_field(rsp_params->up, UP);

	वापस 0;
पूर्ण

/**
 * dpsw_अगर_set_tci() - Set शेष VLAN Tag Control Inक्रमmation (TCI)
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @अगर_id:	Interface Identअगरier
 * @cfg:	Tag Control Inक्रमmation Configuration
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_अगर_set_tci(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token, u16 अगर_id,
		    स्थिर काष्ठा dpsw_tci_cfg *cfg)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_अगर_set_tci *cmd_params;
	u16 पंचांगp_conf = 0;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_IF_SET_TCI,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_अगर_set_tci *)cmd.params;
	cmd_params->अगर_id = cpu_to_le16(अगर_id);
	dpsw_set_field(पंचांगp_conf, VLAN_ID, cfg->vlan_id);
	dpsw_set_field(पंचांगp_conf, DEI, cfg->dei);
	dpsw_set_field(पंचांगp_conf, PCP, cfg->pcp);
	cmd_params->conf = cpu_to_le16(पंचांगp_conf);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_अगर_get_tci() - Get शेष VLAN Tag Control Inक्रमmation (TCI)
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @अगर_id:	Interface Identअगरier
 * @cfg:	Tag Control Inक्रमmation Configuration
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_अगर_get_tci(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token, u16 अगर_id,
		    काष्ठा dpsw_tci_cfg *cfg)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_अगर_get_tci *cmd_params;
	काष्ठा dpsw_rsp_अगर_get_tci *rsp_params;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_IF_GET_TCI,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_अगर_get_tci *)cmd.params;
	cmd_params->अगर_id = cpu_to_le16(अगर_id);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	rsp_params = (काष्ठा dpsw_rsp_अगर_get_tci *)cmd.params;
	cfg->pcp = rsp_params->pcp;
	cfg->dei = rsp_params->dei;
	cfg->vlan_id = le16_to_cpu(rsp_params->vlan_id);

	वापस 0;
पूर्ण

/**
 * dpsw_अगर_set_stp() - Function sets Spanning Tree Protocol (STP) state.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @अगर_id:	Interface Identअगरier
 * @cfg:	STP State configuration parameters
 *
 * The following STP states are supported -
 * blocking, listening, learning, क्रमwarding and disabled.
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_अगर_set_stp(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token, u16 अगर_id,
		    स्थिर काष्ठा dpsw_stp_cfg *cfg)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_अगर_set_stp *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_IF_SET_STP,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_अगर_set_stp *)cmd.params;
	cmd_params->अगर_id = cpu_to_le16(अगर_id);
	cmd_params->vlan_id = cpu_to_le16(cfg->vlan_id);
	dpsw_set_field(cmd_params->state, STATE, cfg->state);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_अगर_get_counter() - Get specअगरic counter of particular पूर्णांकerface
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @अगर_id:	Interface Identअगरier
 * @type:	Counter type
 * @counter:	वापस value
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_अगर_get_counter(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			u16 अगर_id, क्रमागत dpsw_counter type, u64 *counter)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_अगर_get_counter *cmd_params;
	काष्ठा dpsw_rsp_अगर_get_counter *rsp_params;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_IF_GET_COUNTER,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_अगर_get_counter *)cmd.params;
	cmd_params->अगर_id = cpu_to_le16(अगर_id);
	dpsw_set_field(cmd_params->type, COUNTER_TYPE, type);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	rsp_params = (काष्ठा dpsw_rsp_अगर_get_counter *)cmd.params;
	*counter = le64_to_cpu(rsp_params->counter);

	वापस 0;
पूर्ण

/**
 * dpsw_अगर_enable() - Enable Interface
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @अगर_id:	Interface Identअगरier
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_अगर_enable(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token, u16 अगर_id)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_अगर *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_IF_ENABLE,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_अगर *)cmd.params;
	cmd_params->अगर_id = cpu_to_le16(अगर_id);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_अगर_disable() - Disable Interface
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @अगर_id:	Interface Identअगरier
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_अगर_disable(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token, u16 अगर_id)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_अगर *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_IF_DISABLE,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_अगर *)cmd.params;
	cmd_params->अगर_id = cpu_to_le16(अगर_id);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_अगर_get_attributes() - Function obtains attributes of पूर्णांकerface
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @अगर_id:	Interface Identअगरier
 * @attr:	Returned पूर्णांकerface attributes
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_अगर_get_attributes(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			   u16 अगर_id, काष्ठा dpsw_अगर_attr *attr)
अणु
	काष्ठा dpsw_rsp_अगर_get_attr *rsp_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_अगर *cmd_params;
	पूर्णांक err;

	cmd.header = mc_encode_cmd_header(DPSW_CMDID_IF_GET_ATTR, cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_अगर *)cmd.params;
	cmd_params->अगर_id = cpu_to_le16(अगर_id);

	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	rsp_params = (काष्ठा dpsw_rsp_अगर_get_attr *)cmd.params;
	attr->num_tcs = rsp_params->num_tcs;
	attr->rate = le32_to_cpu(rsp_params->rate);
	attr->options = le32_to_cpu(rsp_params->options);
	attr->qdid = le16_to_cpu(rsp_params->qdid);
	attr->enabled = dpsw_get_field(rsp_params->conf, ENABLED);
	attr->accept_all_vlan = dpsw_get_field(rsp_params->conf,
					       ACCEPT_ALL_VLAN);
	attr->admit_untagged = dpsw_get_field(rsp_params->conf,
					      ADMIT_UNTAGGED);

	वापस 0;
पूर्ण

/**
 * dpsw_अगर_set_max_frame_length() - Set Maximum Receive frame length.
 * @mc_io:		Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:		Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:		Token of DPSW object
 * @अगर_id:		Interface Identअगरier
 * @frame_length:	Maximum Frame Length
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_अगर_set_max_frame_length(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
				 u16 अगर_id, u16 frame_length)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_अगर_set_max_frame_length *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_IF_SET_MAX_FRAME_LENGTH,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_अगर_set_max_frame_length *)cmd.params;
	cmd_params->अगर_id = cpu_to_le16(अगर_id);
	cmd_params->frame_length = cpu_to_le16(frame_length);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_vlan_add() - Adding new VLAN to DPSW.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @vlan_id:	VLAN Identअगरier
 * @cfg:	VLAN configuration
 *
 * Only VLAN ID and FDB ID are required parameters here.
 * 12 bit VLAN ID is defined in IEEE802.1Q.
 * Adding a duplicate VLAN ID is not allowed.
 * FDB ID can be shared across multiple VLANs. Shared learning
 * is obtained by calling dpsw_vlan_add क्रम multiple VLAN IDs
 * with same fdb_id
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_vlan_add(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
		  u16 vlan_id, स्थिर काष्ठा dpsw_vlan_cfg *cfg)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_vlan_add *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_VLAN_ADD,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_vlan_add *)cmd.params;
	cmd_params->fdb_id = cpu_to_le16(cfg->fdb_id);
	cmd_params->vlan_id = cpu_to_le16(vlan_id);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_vlan_add_अगर() - Adding a set of पूर्णांकerfaces to an existing VLAN.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @vlan_id:	VLAN Identअगरier
 * @cfg:	Set of पूर्णांकerfaces to add
 *
 * It adds only पूर्णांकerfaces not beदीर्घing to this VLAN yet,
 * otherwise an error is generated and an entire command is
 * ignored. This function can be called numerous बार always
 * providing required पूर्णांकerfaces delta.
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_vlan_add_अगर(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
		     u16 vlan_id, स्थिर काष्ठा dpsw_vlan_अगर_cfg *cfg)
अणु
	काष्ठा dpsw_cmd_vlan_add_अगर *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_VLAN_ADD_IF,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_vlan_add_अगर *)cmd.params;
	cmd_params->vlan_id = cpu_to_le16(vlan_id);
	cmd_params->options = cpu_to_le16(cfg->options);
	cmd_params->fdb_id = cpu_to_le16(cfg->fdb_id);
	build_अगर_id_biपंचांगap(&cmd_params->अगर_id, cfg->अगर_id, cfg->num_अगरs);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_vlan_add_अगर_untagged() - Defining a set of पूर्णांकerfaces that should be
 *				transmitted as untagged.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @vlan_id:	VLAN Identअगरier
 * @cfg:	Set of पूर्णांकerfaces that should be transmitted as untagged
 *
 * These पूर्णांकerfaces should alपढ़ोy beदीर्घ to this VLAN.
 * By शेष all पूर्णांकerfaces are transmitted as tagged.
 * Providing un-existing पूर्णांकerface or untagged पूर्णांकerface that is
 * configured untagged alपढ़ोy generates an error and the entire
 * command is ignored.
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_vlan_add_अगर_untagged(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			      u16 vlan_id, स्थिर काष्ठा dpsw_vlan_अगर_cfg *cfg)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_vlan_manage_अगर *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_VLAN_ADD_IF_UNTAGGED,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_vlan_manage_अगर *)cmd.params;
	cmd_params->vlan_id = cpu_to_le16(vlan_id);
	build_अगर_id_biपंचांगap(&cmd_params->अगर_id, cfg->अगर_id, cfg->num_अगरs);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_vlan_हटाओ_अगर() - Remove पूर्णांकerfaces from an existing VLAN.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @vlan_id:	VLAN Identअगरier
 * @cfg:	Set of पूर्णांकerfaces that should be हटाओd
 *
 * Interfaces must beदीर्घ to this VLAN, otherwise an error
 * is वापसed and an the command is ignored
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_vlan_हटाओ_अगर(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			u16 vlan_id, स्थिर काष्ठा dpsw_vlan_अगर_cfg *cfg)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_vlan_manage_अगर *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_VLAN_REMOVE_IF,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_vlan_manage_अगर *)cmd.params;
	cmd_params->vlan_id = cpu_to_le16(vlan_id);
	build_अगर_id_biपंचांगap(&cmd_params->अगर_id, cfg->अगर_id, cfg->num_अगरs);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_vlan_हटाओ_अगर_untagged() - Define a set of पूर्णांकerfaces that should be
 *		converted from transmitted as untagged to transmit as tagged.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @vlan_id:	VLAN Identअगरier
 * @cfg:	Set of पूर्णांकerfaces that should be हटाओd
 *
 * Interfaces provided by API have to beदीर्घ to this VLAN and
 * configured untagged, otherwise an error is वापसed and the
 * command is ignored
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_vlan_हटाओ_अगर_untagged(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
				 u16 vlan_id, स्थिर काष्ठा dpsw_vlan_अगर_cfg *cfg)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_vlan_manage_अगर *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_VLAN_REMOVE_IF_UNTAGGED,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_vlan_manage_अगर *)cmd.params;
	cmd_params->vlan_id = cpu_to_le16(vlan_id);
	build_अगर_id_biपंचांगap(&cmd_params->अगर_id, cfg->अगर_id, cfg->num_अगरs);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_vlan_हटाओ() - Remove an entire VLAN
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @vlan_id:	VLAN Identअगरier
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_vlan_हटाओ(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
		     u16 vlan_id)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_vlan_हटाओ *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_VLAN_REMOVE,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_vlan_हटाओ *)cmd.params;
	cmd_params->vlan_id = cpu_to_le16(vlan_id);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_fdb_add() - Add FDB to चयन and Returns handle to FDB table क्रम
 *		the reference
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @fdb_id:	Returned Forwarding Database Identअगरier
 * @cfg:	FDB Configuration
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_fdb_add(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token, u16 *fdb_id,
		 स्थिर काष्ठा dpsw_fdb_cfg *cfg)
अणु
	काष्ठा dpsw_cmd_fdb_add *cmd_params;
	काष्ठा dpsw_rsp_fdb_add *rsp_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	पूर्णांक err;

	cmd.header = mc_encode_cmd_header(DPSW_CMDID_FDB_ADD,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_fdb_add *)cmd.params;
	cmd_params->fdb_ageing_समय = cpu_to_le16(cfg->fdb_ageing_समय);
	cmd_params->num_fdb_entries = cpu_to_le16(cfg->num_fdb_entries);

	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	rsp_params = (काष्ठा dpsw_rsp_fdb_add *)cmd.params;
	*fdb_id = le16_to_cpu(rsp_params->fdb_id);

	वापस 0;
पूर्ण

/**
 * dpsw_fdb_हटाओ() - Remove FDB from चयन
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @fdb_id:	Forwarding Database Identअगरier
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_fdb_हटाओ(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token, u16 fdb_id)
अणु
	काष्ठा dpsw_cmd_fdb_हटाओ *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_FDB_REMOVE,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_fdb_हटाओ *)cmd.params;
	cmd_params->fdb_id = cpu_to_le16(fdb_id);

	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_fdb_add_unicast() - Function adds an unicast entry पूर्णांकo MAC lookup table
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @fdb_id:	Forwarding Database Identअगरier
 * @cfg:	Unicast entry configuration
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_fdb_add_unicast(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			 u16 fdb_id, स्थिर काष्ठा dpsw_fdb_unicast_cfg *cfg)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_fdb_unicast_op *cmd_params;
	पूर्णांक i;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_FDB_ADD_UNICAST,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_fdb_unicast_op *)cmd.params;
	cmd_params->fdb_id = cpu_to_le16(fdb_id);
	cmd_params->अगर_egress = cpu_to_le16(cfg->अगर_egress);
	क्रम (i = 0; i < 6; i++)
		cmd_params->mac_addr[i] = cfg->mac_addr[5 - i];
	dpsw_set_field(cmd_params->type, ENTRY_TYPE, cfg->type);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_fdb_dump() - Dump the content of FDB table पूर्णांकo memory.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @fdb_id:	Forwarding Database Identअगरier
 * @iova_addr:	Data will be stored here as an array of काष्ठा fdb_dump_entry
 * @iova_size:	Memory size allocated at iova_addr
 * @num_entries:Number of entries written at iova_addr
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 *
 * The memory allocated at iova_addr must be initialized with zero beक्रमe
 * command execution. If the FDB table करोes not fit पूर्णांकo memory MC will stop
 * after the memory is filled up.
 * The काष्ठा fdb_dump_entry array must be parsed until the end of memory
 * area or until an entry with mac_addr set to zero is found.
 */
पूर्णांक dpsw_fdb_dump(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token, u16 fdb_id,
		  u64 iova_addr, u32 iova_size, u16 *num_entries)
अणु
	काष्ठा dpsw_cmd_fdb_dump *cmd_params;
	काष्ठा dpsw_rsp_fdb_dump *rsp_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_FDB_DUMP,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_fdb_dump *)cmd.params;
	cmd_params->fdb_id = cpu_to_le16(fdb_id);
	cmd_params->iova_addr = cpu_to_le64(iova_addr);
	cmd_params->iova_size = cpu_to_le32(iova_size);

	/* send command to mc */
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	rsp_params = (काष्ठा dpsw_rsp_fdb_dump *)cmd.params;
	*num_entries = le16_to_cpu(rsp_params->num_entries);

	वापस 0;
पूर्ण

/**
 * dpsw_fdb_हटाओ_unicast() - हटाओs an entry from MAC lookup table
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @fdb_id:	Forwarding Database Identअगरier
 * @cfg:	Unicast entry configuration
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_fdb_हटाओ_unicast(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			    u16 fdb_id, स्थिर काष्ठा dpsw_fdb_unicast_cfg *cfg)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_fdb_unicast_op *cmd_params;
	पूर्णांक i;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_FDB_REMOVE_UNICAST,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_fdb_unicast_op *)cmd.params;
	cmd_params->fdb_id = cpu_to_le16(fdb_id);
	क्रम (i = 0; i < 6; i++)
		cmd_params->mac_addr[i] = cfg->mac_addr[5 - i];
	cmd_params->अगर_egress = cpu_to_le16(cfg->अगर_egress);
	dpsw_set_field(cmd_params->type, ENTRY_TYPE, cfg->type);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_fdb_add_multicast() - Add a set of egress पूर्णांकerfaces to multi-cast group
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @fdb_id:	Forwarding Database Identअगरier
 * @cfg:	Multicast entry configuration
 *
 * If group करोesn't exist, it will be created.
 * It adds only पूर्णांकerfaces not beदीर्घing to this multicast group
 * yet, otherwise error will be generated and the command is
 * ignored.
 * This function may be called numerous बार always providing
 * required पूर्णांकerfaces delta.
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_fdb_add_multicast(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			   u16 fdb_id, स्थिर काष्ठा dpsw_fdb_multicast_cfg *cfg)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_fdb_multicast_op *cmd_params;
	पूर्णांक i;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_FDB_ADD_MULTICAST,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_fdb_multicast_op *)cmd.params;
	cmd_params->fdb_id = cpu_to_le16(fdb_id);
	cmd_params->num_अगरs = cpu_to_le16(cfg->num_अगरs);
	dpsw_set_field(cmd_params->type, ENTRY_TYPE, cfg->type);
	build_अगर_id_biपंचांगap(&cmd_params->अगर_id, cfg->अगर_id, cfg->num_अगरs);
	क्रम (i = 0; i < 6; i++)
		cmd_params->mac_addr[i] = cfg->mac_addr[5 - i];

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_fdb_हटाओ_multicast() - Removing पूर्णांकerfaces from an existing multicast
 *				group.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @fdb_id:	Forwarding Database Identअगरier
 * @cfg:	Multicast entry configuration
 *
 * Interfaces provided by this API have to exist in the group,
 * otherwise an error will be वापसed and an entire command
 * ignored. If there is no पूर्णांकerface left in the group,
 * an entire group is deleted
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_fdb_हटाओ_multicast(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			      u16 fdb_id, स्थिर काष्ठा dpsw_fdb_multicast_cfg *cfg)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_fdb_multicast_op *cmd_params;
	पूर्णांक i;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_FDB_REMOVE_MULTICAST,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_fdb_multicast_op *)cmd.params;
	cmd_params->fdb_id = cpu_to_le16(fdb_id);
	cmd_params->num_अगरs = cpu_to_le16(cfg->num_अगरs);
	dpsw_set_field(cmd_params->type, ENTRY_TYPE, cfg->type);
	build_अगर_id_biपंचांगap(&cmd_params->अगर_id, cfg->अगर_id, cfg->num_अगरs);
	क्रम (i = 0; i < 6; i++)
		cmd_params->mac_addr[i] = cfg->mac_addr[5 - i];

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_ctrl_अगर_get_attributes() - Obtain control पूर्णांकerface attributes
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @attr:	Returned control पूर्णांकerface attributes
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_ctrl_अगर_get_attributes(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags,
				u16 token, काष्ठा dpsw_ctrl_अगर_attr *attr)
अणु
	काष्ठा dpsw_rsp_ctrl_अगर_get_attr *rsp_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	पूर्णांक err;

	cmd.header = mc_encode_cmd_header(DPSW_CMDID_CTRL_IF_GET_ATTR,
					  cmd_flags, token);

	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	rsp_params = (काष्ठा dpsw_rsp_ctrl_अगर_get_attr *)cmd.params;
	attr->rx_fqid = le32_to_cpu(rsp_params->rx_fqid);
	attr->rx_err_fqid = le32_to_cpu(rsp_params->rx_err_fqid);
	attr->tx_err_conf_fqid = le32_to_cpu(rsp_params->tx_err_conf_fqid);

	वापस 0;
पूर्ण

/**
 * dpsw_ctrl_अगर_set_pools() - Set control पूर्णांकerface buffer pools
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @cfg:	Buffer pools configuration
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_ctrl_अगर_set_pools(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			   स्थिर काष्ठा dpsw_ctrl_अगर_pools_cfg *cfg)
अणु
	काष्ठा dpsw_cmd_ctrl_अगर_set_pools *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	पूर्णांक i;

	cmd.header = mc_encode_cmd_header(DPSW_CMDID_CTRL_IF_SET_POOLS,
					  cmd_flags, token);
	cmd_params = (काष्ठा dpsw_cmd_ctrl_अगर_set_pools *)cmd.params;
	cmd_params->num_dpbp = cfg->num_dpbp;
	क्रम (i = 0; i < DPSW_MAX_DPBP; i++) अणु
		cmd_params->dpbp_id[i] = cpu_to_le32(cfg->pools[i].dpbp_id);
		cmd_params->buffer_size[i] =
			cpu_to_le16(cfg->pools[i].buffer_size);
		cmd_params->backup_pool_mask |=
			DPSW_BACKUP_POOL(cfg->pools[i].backup_pool, i);
	पूर्ण

	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_ctrl_अगर_set_queue() - Set Rx queue configuration
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of dpsw object
 * @qtype:	dpsw_queue_type of the targeted queue
 * @cfg:	Rx queue configuration
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_ctrl_अगर_set_queue(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			   क्रमागत dpsw_queue_type qtype,
			   स्थिर काष्ठा dpsw_ctrl_अगर_queue_cfg *cfg)
अणु
	काष्ठा dpsw_cmd_ctrl_अगर_set_queue *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	cmd.header = mc_encode_cmd_header(DPSW_CMDID_CTRL_IF_SET_QUEUE,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_ctrl_अगर_set_queue *)cmd.params;
	cmd_params->dest_id = cpu_to_le32(cfg->dest_cfg.dest_id);
	cmd_params->dest_priority = cfg->dest_cfg.priority;
	cmd_params->qtype = qtype;
	cmd_params->user_ctx = cpu_to_le64(cfg->user_ctx);
	cmd_params->options = cpu_to_le32(cfg->options);
	dpsw_set_field(cmd_params->dest_type,
		       DEST_TYPE,
		       cfg->dest_cfg.dest_type);

	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_get_api_version() - Get Data Path Switch API version
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @major_ver:	Major version of data path चयन API
 * @minor_ver:	Minor version of data path चयन API
 *
 * Return:  '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_get_api_version(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags,
			 u16 *major_ver, u16 *minor_ver)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_rsp_get_api_version *rsp_params;
	पूर्णांक err;

	cmd.header = mc_encode_cmd_header(DPSW_CMDID_GET_API_VERSION,
					  cmd_flags,
					  0);

	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	rsp_params = (काष्ठा dpsw_rsp_get_api_version *)cmd.params;
	*major_ver = le16_to_cpu(rsp_params->version_major);
	*minor_ver = le16_to_cpu(rsp_params->version_minor);

	वापस 0;
पूर्ण

/**
 * dpsw_अगर_get_port_mac_addr() - Retrieve MAC address associated to the physical port
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @अगर_id:	Interface Identअगरier
 * @mac_addr:	MAC address of the physical port, अगर any, otherwise 0
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_अगर_get_port_mac_addr(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			      u16 अगर_id, u8 mac_addr[6])
अणु
	काष्ठा dpsw_rsp_अगर_get_mac_addr *rsp_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpsw_cmd_अगर *cmd_params;
	पूर्णांक err, i;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_IF_GET_PORT_MAC_ADDR,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_अगर *)cmd.params;
	cmd_params->अगर_id = cpu_to_le16(अगर_id);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	rsp_params = (काष्ठा dpsw_rsp_अगर_get_mac_addr *)cmd.params;
	क्रम (i = 0; i < 6; i++)
		mac_addr[5 - i] = rsp_params->mac_addr[i];

	वापस 0;
पूर्ण

/**
 * dpsw_ctrl_अगर_enable() - Enable control पूर्णांकerface
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_ctrl_अगर_enable(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	cmd.header = mc_encode_cmd_header(DPSW_CMDID_CTRL_IF_ENABLE, cmd_flags,
					  token);

	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_ctrl_अगर_disable() - Function disables control पूर्णांकerface
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_ctrl_अगर_disable(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	cmd.header = mc_encode_cmd_header(DPSW_CMDID_CTRL_IF_DISABLE,
					  cmd_flags,
					  token);

	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_set_egress_flood() - Set egress parameters associated with an FDB ID
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @cfg:	Egress flooding configuration
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_set_egress_flood(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			  स्थिर काष्ठा dpsw_egress_flood_cfg *cfg)
अणु
	काष्ठा dpsw_cmd_set_egress_flood *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	cmd.header = mc_encode_cmd_header(DPSW_CMDID_SET_EGRESS_FLOOD, cmd_flags, token);
	cmd_params = (काष्ठा dpsw_cmd_set_egress_flood *)cmd.params;
	cmd_params->fdb_id = cpu_to_le16(cfg->fdb_id);
	cmd_params->flood_type = cfg->flood_type;
	build_अगर_id_biपंचांगap(&cmd_params->अगर_id, cfg->अगर_id, cfg->num_अगरs);

	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_अगर_set_learning_mode() - Configure the learning mode on an पूर्णांकerface.
 * If this API is used, it will take precedence over the FDB configuration.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @अगर_id:	InterfaceID
 * @mode:	Learning mode
 *
 * Return:	Completion status. '0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_अगर_set_learning_mode(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			      u16 अगर_id, क्रमागत dpsw_learning_mode mode)
अणु
	काष्ठा dpsw_cmd_अगर_set_learning_mode *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	cmd.header = mc_encode_cmd_header(DPSW_CMDID_IF_SET_LEARNING_MODE,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_अगर_set_learning_mode *)cmd.params;
	cmd_params->अगर_id = cpu_to_le16(अगर_id);
	dpsw_set_field(cmd_params->mode, LEARNING_MODE, mode);

	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_acl_add() - Create an ACL table
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @acl_id:	Returned ACL ID, क्रम future references
 * @cfg:	ACL configuration
 *
 * Create Access Control List table. Multiple ACLs can be created and
 * co-exist in L2 चयन
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_acl_add(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token, u16 *acl_id,
		 स्थिर काष्ठा dpsw_acl_cfg *cfg)
अणु
	काष्ठा dpsw_cmd_acl_add *cmd_params;
	काष्ठा dpsw_rsp_acl_add *rsp_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	पूर्णांक err;

	cmd.header = mc_encode_cmd_header(DPSW_CMDID_ACL_ADD, cmd_flags, token);
	cmd_params = (काष्ठा dpsw_cmd_acl_add *)cmd.params;
	cmd_params->max_entries = cpu_to_le16(cfg->max_entries);

	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	rsp_params = (काष्ठा dpsw_rsp_acl_add *)cmd.params;
	*acl_id = le16_to_cpu(rsp_params->acl_id);

	वापस 0;
पूर्ण

/**
 * dpsw_acl_हटाओ() - Remove an ACL table from L2 चयन.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @acl_id:	ACL ID
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_acl_हटाओ(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
		    u16 acl_id)
अणु
	काष्ठा dpsw_cmd_acl_हटाओ *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	cmd.header = mc_encode_cmd_header(DPSW_CMDID_ACL_REMOVE, cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_acl_हटाओ *)cmd.params;
	cmd_params->acl_id = cpu_to_le16(acl_id);

	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_acl_add_अगर() - Associate पूर्णांकerface/पूर्णांकerfaces with an ACL table.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @acl_id:	ACL ID
 * @cfg:	Interfaces list
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_acl_add_अगर(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
		    u16 acl_id, स्थिर काष्ठा dpsw_acl_अगर_cfg *cfg)
अणु
	काष्ठा dpsw_cmd_acl_अगर *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	cmd.header = mc_encode_cmd_header(DPSW_CMDID_ACL_ADD_IF, cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_acl_अगर *)cmd.params;
	cmd_params->acl_id = cpu_to_le16(acl_id);
	cmd_params->num_अगरs = cpu_to_le16(cfg->num_अगरs);
	build_अगर_id_biपंचांगap(&cmd_params->अगर_id, cfg->अगर_id, cfg->num_अगरs);

	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_acl_हटाओ_अगर() - De-associate पूर्णांकerface/पूर्णांकerfaces from an ACL table
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @acl_id:	ACL ID
 * @cfg:	Interfaces list
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_acl_हटाओ_अगर(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
		       u16 acl_id, स्थिर काष्ठा dpsw_acl_अगर_cfg *cfg)
अणु
	काष्ठा dpsw_cmd_acl_अगर *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_ACL_REMOVE_IF, cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_acl_अगर *)cmd.params;
	cmd_params->acl_id = cpu_to_le16(acl_id);
	cmd_params->num_अगरs = cpu_to_le16(cfg->num_अगरs);
	build_अगर_id_biपंचांगap(&cmd_params->अगर_id, cfg->अगर_id, cfg->num_अगरs);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_acl_prepare_entry_cfg() - Setup an ACL entry
 * @key:		Key
 * @entry_cfg_buf:	Zeroed 256 bytes of memory beक्रमe mapping it to DMA
 *
 * This function has to be called beक्रमe adding or removing acl_entry
 *
 */
व्योम dpsw_acl_prepare_entry_cfg(स्थिर काष्ठा dpsw_acl_key *key,
				u8 *entry_cfg_buf)
अणु
	काष्ठा dpsw_prep_acl_entry *ext_params;
	पूर्णांक i;

	ext_params = (काष्ठा dpsw_prep_acl_entry *)entry_cfg_buf;

	क्रम (i = 0; i < 6; i++) अणु
		ext_params->match_l2_dest_mac[i] = key->match.l2_dest_mac[5 - i];
		ext_params->match_l2_source_mac[i] = key->match.l2_source_mac[5 - i];
		ext_params->mask_l2_dest_mac[i] = key->mask.l2_dest_mac[5 - i];
		ext_params->mask_l2_source_mac[i] = key->mask.l2_source_mac[5 - i];
	पूर्ण

	ext_params->match_l2_tpid = cpu_to_le16(key->match.l2_tpid);
	ext_params->match_l2_vlan_id = cpu_to_le16(key->match.l2_vlan_id);
	ext_params->match_l3_dest_ip = cpu_to_le32(key->match.l3_dest_ip);
	ext_params->match_l3_source_ip = cpu_to_le32(key->match.l3_source_ip);
	ext_params->match_l4_dest_port = cpu_to_le16(key->match.l4_dest_port);
	ext_params->match_l4_source_port = cpu_to_le16(key->match.l4_source_port);
	ext_params->match_l2_ether_type = cpu_to_le16(key->match.l2_ether_type);
	ext_params->match_l2_pcp_dei = key->match.l2_pcp_dei;
	ext_params->match_l3_dscp = key->match.l3_dscp;

	ext_params->mask_l2_tpid = cpu_to_le16(key->mask.l2_tpid);
	ext_params->mask_l2_vlan_id = cpu_to_le16(key->mask.l2_vlan_id);
	ext_params->mask_l3_dest_ip = cpu_to_le32(key->mask.l3_dest_ip);
	ext_params->mask_l3_source_ip = cpu_to_le32(key->mask.l3_source_ip);
	ext_params->mask_l4_dest_port = cpu_to_le16(key->mask.l4_dest_port);
	ext_params->mask_l4_source_port = cpu_to_le16(key->mask.l4_source_port);
	ext_params->mask_l2_ether_type = cpu_to_le16(key->mask.l2_ether_type);
	ext_params->mask_l2_pcp_dei = key->mask.l2_pcp_dei;
	ext_params->mask_l3_dscp = key->mask.l3_dscp;
	ext_params->match_l3_protocol = key->match.l3_protocol;
	ext_params->mask_l3_protocol = key->mask.l3_protocol;
पूर्ण

/**
 * dpsw_acl_add_entry() - Add a rule to the ACL table.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @acl_id:	ACL ID
 * @cfg:	Entry configuration
 *
 * warning: This function has to be called after dpsw_acl_prepare_entry_cfg()
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_acl_add_entry(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
		       u16 acl_id, स्थिर काष्ठा dpsw_acl_entry_cfg *cfg)
अणु
	काष्ठा dpsw_cmd_acl_entry *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	cmd.header = mc_encode_cmd_header(DPSW_CMDID_ACL_ADD_ENTRY, cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_acl_entry *)cmd.params;
	cmd_params->acl_id = cpu_to_le16(acl_id);
	cmd_params->result_अगर_id = cpu_to_le16(cfg->result.अगर_id);
	cmd_params->precedence = cpu_to_le32(cfg->precedence);
	cmd_params->key_iova = cpu_to_le64(cfg->key_iova);
	dpsw_set_field(cmd_params->result_action,
		       RESULT_ACTION,
		       cfg->result.action);

	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dpsw_acl_हटाओ_entry() - Removes an entry from ACL.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSW object
 * @acl_id:	ACL ID
 * @cfg:	Entry configuration
 *
 * warning: This function has to be called after dpsw_acl_set_entry_cfg()
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dpsw_acl_हटाओ_entry(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			  u16 acl_id, स्थिर काष्ठा dpsw_acl_entry_cfg *cfg)
अणु
	काष्ठा dpsw_cmd_acl_entry *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_ACL_REMOVE_ENTRY,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dpsw_cmd_acl_entry *)cmd.params;
	cmd_params->acl_id = cpu_to_le16(acl_id);
	cmd_params->result_अगर_id = cpu_to_le16(cfg->result.अगर_id);
	cmd_params->precedence = cpu_to_le32(cfg->precedence);
	cmd_params->key_iova = cpu_to_le64(cfg->key_iova);
	dpsw_set_field(cmd_params->result_action,
		       RESULT_ACTION,
		       cfg->result.action);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण
