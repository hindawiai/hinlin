<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2016-2018 NXP
 */

#समावेश <linux/fsl/mc.h>

#समावेश "dprtc.h"
#समावेश "dprtc-cmd.h"

/**
 * dprtc_खोलो() - Open a control session क्रम the specअगरied object.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @dprtc_id:	DPRTC unique ID
 * @token:	Returned token; use in subsequent API calls
 *
 * This function can be used to खोलो a control session क्रम an
 * alपढ़ोy created object; an object may have been declared in
 * the DPL or by calling the dprtc_create function.
 * This function वापसs a unique authentication token,
 * associated with the specअगरic object ID and the specअगरic MC
 * portal; this token must be used in all subsequent commands क्रम
 * this specअगरic object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dprtc_खोलो(काष्ठा fsl_mc_io *mc_io,
	       u32 cmd_flags,
	       पूर्णांक dprtc_id,
	       u16 *token)
अणु
	काष्ठा dprtc_cmd_खोलो *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	पूर्णांक err;

	cmd.header = mc_encode_cmd_header(DPRTC_CMDID_OPEN,
					  cmd_flags,
					  0);
	cmd_params = (काष्ठा dprtc_cmd_खोलो *)cmd.params;
	cmd_params->dprtc_id = cpu_to_le32(dprtc_id);

	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	*token = mc_cmd_hdr_पढ़ो_token(&cmd);

	वापस 0;
पूर्ण

/**
 * dprtc_बंद() - Close the control session of the object
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPRTC object
 *
 * After this function is called, no further operations are
 * allowed on the object without खोलोing a new control session.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dprtc_बंद(काष्ठा fsl_mc_io *mc_io,
		u32 cmd_flags,
		u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	cmd.header = mc_encode_cmd_header(DPRTC_CMDID_CLOSE, cmd_flags,
					  token);

	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dprtc_set_irq_enable() - Set overall पूर्णांकerrupt state.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPRTC object
 * @irq_index:	The पूर्णांकerrupt index to configure
 * @en:		Interrupt state - enable = 1, disable = 0
 *
 * Allows GPP software to control when पूर्णांकerrupts are generated.
 * Each पूर्णांकerrupt can have up to 32 causes.  The enable/disable control's the
 * overall पूर्णांकerrupt state. अगर the पूर्णांकerrupt is disabled no causes will cause
 * an पूर्णांकerrupt.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dprtc_set_irq_enable(काष्ठा fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 token,
			 u8 irq_index,
			 u8 en)
अणु
	काष्ठा dprtc_cmd_set_irq_enable *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	cmd.header = mc_encode_cmd_header(DPRTC_CMDID_SET_IRQ_ENABLE,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dprtc_cmd_set_irq_enable *)cmd.params;
	cmd_params->irq_index = irq_index;
	cmd_params->en = en;

	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dprtc_get_irq_enable() - Get overall पूर्णांकerrupt state
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPRTC object
 * @irq_index:	The पूर्णांकerrupt index to configure
 * @en:		Returned पूर्णांकerrupt state - enable = 1, disable = 0
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dprtc_get_irq_enable(काष्ठा fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 token,
			 u8 irq_index,
			 u8 *en)
अणु
	काष्ठा dprtc_rsp_get_irq_enable *rsp_params;
	काष्ठा dprtc_cmd_get_irq *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	पूर्णांक err;

	cmd.header = mc_encode_cmd_header(DPRTC_CMDID_GET_IRQ_ENABLE,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dprtc_cmd_get_irq *)cmd.params;
	cmd_params->irq_index = irq_index;

	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	rsp_params = (काष्ठा dprtc_rsp_get_irq_enable *)cmd.params;
	*en = rsp_params->en;

	वापस 0;
पूर्ण

/**
 * dprtc_set_irq_mask() - Set पूर्णांकerrupt mask.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPRTC object
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
पूर्णांक dprtc_set_irq_mask(काष्ठा fsl_mc_io *mc_io,
		       u32 cmd_flags,
		       u16 token,
		       u8 irq_index,
		       u32 mask)
अणु
	काष्ठा dprtc_cmd_set_irq_mask *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	cmd.header = mc_encode_cmd_header(DPRTC_CMDID_SET_IRQ_MASK,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dprtc_cmd_set_irq_mask *)cmd.params;
	cmd_params->mask = cpu_to_le32(mask);
	cmd_params->irq_index = irq_index;

	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dprtc_get_irq_mask() - Get पूर्णांकerrupt mask.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPRTC object
 * @irq_index:	The पूर्णांकerrupt index to configure
 * @mask:	Returned event mask to trigger पूर्णांकerrupt
 *
 * Every पूर्णांकerrupt can have up to 32 causes and the पूर्णांकerrupt model supports
 * masking/unmasking each cause independently
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dprtc_get_irq_mask(काष्ठा fsl_mc_io *mc_io,
		       u32 cmd_flags,
		       u16 token,
		       u8 irq_index,
		       u32 *mask)
अणु
	काष्ठा dprtc_rsp_get_irq_mask *rsp_params;
	काष्ठा dprtc_cmd_get_irq *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	पूर्णांक err;

	cmd.header = mc_encode_cmd_header(DPRTC_CMDID_GET_IRQ_MASK,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dprtc_cmd_get_irq *)cmd.params;
	cmd_params->irq_index = irq_index;

	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	rsp_params = (काष्ठा dprtc_rsp_get_irq_mask *)cmd.params;
	*mask = le32_to_cpu(rsp_params->mask);

	वापस 0;
पूर्ण

/**
 * dprtc_get_irq_status() - Get the current status of any pending पूर्णांकerrupts.
 *
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPRTC object
 * @irq_index:	The पूर्णांकerrupt index to configure
 * @status:	Returned पूर्णांकerrupts status - one bit per cause:
 *			0 = no पूर्णांकerrupt pending
 *			1 = पूर्णांकerrupt pending
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dprtc_get_irq_status(काष्ठा fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 token,
			 u8 irq_index,
			 u32 *status)
अणु
	काष्ठा dprtc_cmd_get_irq_status *cmd_params;
	काष्ठा dprtc_rsp_get_irq_status *rsp_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	पूर्णांक err;

	cmd.header = mc_encode_cmd_header(DPRTC_CMDID_GET_IRQ_STATUS,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dprtc_cmd_get_irq_status *)cmd.params;
	cmd_params->status = cpu_to_le32(*status);
	cmd_params->irq_index = irq_index;

	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	rsp_params = (काष्ठा dprtc_rsp_get_irq_status *)cmd.params;
	*status = le32_to_cpu(rsp_params->status);

	वापस 0;
पूर्ण

/**
 * dprtc_clear_irq_status() - Clear a pending पूर्णांकerrupt's status
 *
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPRTC object
 * @irq_index:	The पूर्णांकerrupt index to configure
 * @status:	Bits to clear (W1C) - one bit per cause:
 *			0 = करोn't change
 *			1 = clear status bit
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dprtc_clear_irq_status(काष्ठा fsl_mc_io *mc_io,
			   u32 cmd_flags,
			   u16 token,
			   u8 irq_index,
			   u32 status)
अणु
	काष्ठा dprtc_cmd_clear_irq_status *cmd_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	cmd.header = mc_encode_cmd_header(DPRTC_CMDID_CLEAR_IRQ_STATUS,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dprtc_cmd_clear_irq_status *)cmd.params;
	cmd_params->irq_index = irq_index;
	cmd_params->status = cpu_to_le32(status);

	वापस mc_send_command(mc_io, &cmd);
पूर्ण
