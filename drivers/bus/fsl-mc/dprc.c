<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2020 NXP
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/fsl/mc.h>

#समावेश "fsl-mc-private.h"

/*
 * cache the DPRC version to reduce the number of commands
 * towards the mc firmware
 */
अटल u16 dprc_major_ver;
अटल u16 dprc_minor_ver;

/**
 * dprc_खोलो() - Open DPRC object क्रम use
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @container_id: Container ID to खोलो
 * @token:	Returned token of DPRC object
 *
 * Return:	'0' on Success; Error code otherwise.
 *
 * @warning	Required beक्रमe any operation on the object.
 */
पूर्णांक dprc_खोलो(काष्ठा fsl_mc_io *mc_io,
	      u32 cmd_flags,
	      पूर्णांक container_id,
	      u16 *token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dprc_cmd_खोलो *cmd_params;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPRC_CMDID_OPEN, cmd_flags,
					  0);
	cmd_params = (काष्ठा dprc_cmd_खोलो *)cmd.params;
	cmd_params->container_id = cpu_to_le32(container_id);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	*token = mc_cmd_hdr_पढ़ो_token(&cmd);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dprc_खोलो);

/**
 * dprc_बंद() - Close the control session of the object
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPRC object
 *
 * After this function is called, no further operations are
 * allowed on the object without खोलोing a new control session.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dprc_बंद(काष्ठा fsl_mc_io *mc_io,
	       u32 cmd_flags,
	       u16 token)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPRC_CMDID_CLOSE, cmd_flags,
					  token);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण
EXPORT_SYMBOL_GPL(dprc_बंद);

/**
 * dprc_reset_container - Reset child container.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPRC object
 * @child_container_id:	ID of the container to reset
 * @options: 32 bit options:
 *   - 0 (no bits set) - all the objects inside the container are
 *     reset. The child containers are entered recursively and the
 *     objects reset. All the objects (including the child containers)
 *     are बंदd.
 *   - bit 0 set - all the objects inside the container are reset.
 *     However the child containers are not entered recursively.
 *     This option is supported क्रम API versions >= 6.5
 * In हाल a software context crashes or becomes non-responsive, the parent
 * may wish to reset its resources container beक्रमe the software context is
 * restarted.
 *
 * This routine inक्रमms all objects asचिन्हित to the child container that the
 * container is being reset, so they may perक्रमm any cleanup operations that are
 * needed. All objects handles that were owned by the child container shall be
 * बंदd.
 *
 * Note that such request may be submitted even अगर the child software context
 * has not crashed, but the resulting object cleanup operations will not be
 * aware of that.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dprc_reset_container(काष्ठा fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 token,
			 पूर्णांक child_container_id,
			 u32 options)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dprc_cmd_reset_container *cmd_params;
	u32 cmdid = DPRC_CMDID_RESET_CONT;
	पूर्णांक err;

	/*
	 * If the DPRC object version was not yet cached, cache it now.
	 * Otherwise use the alपढ़ोy cached value.
	 */
	अगर (!dprc_major_ver && !dprc_minor_ver) अणु
		err = dprc_get_api_version(mc_io, 0,
				&dprc_major_ver,
				&dprc_minor_ver);
		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * MC API 6.5 पूर्णांकroduced a new field in the command used to pass
	 * some flags.
	 * Bit 0 indicates that the child containers are not recursively reset.
	 */
	अगर (dprc_major_ver > 6 || (dprc_major_ver == 6 && dprc_minor_ver >= 5))
		cmdid = DPRC_CMDID_RESET_CONT_V2;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(cmdid, cmd_flags, token);
	cmd_params = (काष्ठा dprc_cmd_reset_container *)cmd.params;
	cmd_params->child_container_id = cpu_to_le32(child_container_id);
	cmd_params->options = cpu_to_le32(options);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण
EXPORT_SYMBOL_GPL(dprc_reset_container);

/**
 * dprc_set_irq() - Set IRQ inक्रमmation क्रम the DPRC to trigger an पूर्णांकerrupt.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPRC object
 * @irq_index:	Identअगरies the पूर्णांकerrupt index to configure
 * @irq_cfg:	IRQ configuration
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dprc_set_irq(काष्ठा fsl_mc_io *mc_io,
		 u32 cmd_flags,
		 u16 token,
		 u8 irq_index,
		 काष्ठा dprc_irq_cfg *irq_cfg)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dprc_cmd_set_irq *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPRC_CMDID_SET_IRQ,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dprc_cmd_set_irq *)cmd.params;
	cmd_params->irq_val = cpu_to_le32(irq_cfg->val);
	cmd_params->irq_index = irq_index;
	cmd_params->irq_addr = cpu_to_le64(irq_cfg->paddr);
	cmd_params->irq_num = cpu_to_le32(irq_cfg->irq_num);

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dprc_set_irq_enable() - Set overall पूर्णांकerrupt state.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPRC object
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
पूर्णांक dprc_set_irq_enable(काष्ठा fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			u8 irq_index,
			u8 en)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dprc_cmd_set_irq_enable *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPRC_CMDID_SET_IRQ_ENABLE,
					  cmd_flags, token);
	cmd_params = (काष्ठा dprc_cmd_set_irq_enable *)cmd.params;
	cmd_params->enable = en & DPRC_ENABLE;
	cmd_params->irq_index = irq_index;

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dprc_set_irq_mask() - Set पूर्णांकerrupt mask.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPRC object
 * @irq_index:	The पूर्णांकerrupt index to configure
 * @mask:	event mask to trigger पूर्णांकerrupt;
 *			each bit:
 *				0 = ignore event
 *				1 = consider event क्रम निश्चितing irq
 *
 * Every पूर्णांकerrupt can have up to 32 causes and the पूर्णांकerrupt model supports
 * masking/unmasking each cause independently
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dprc_set_irq_mask(काष्ठा fsl_mc_io *mc_io,
		      u32 cmd_flags,
		      u16 token,
		      u8 irq_index,
		      u32 mask)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dprc_cmd_set_irq_mask *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPRC_CMDID_SET_IRQ_MASK,
					  cmd_flags, token);
	cmd_params = (काष्ठा dprc_cmd_set_irq_mask *)cmd.params;
	cmd_params->mask = cpu_to_le32(mask);
	cmd_params->irq_index = irq_index;

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dprc_get_irq_status() - Get the current status of any pending पूर्णांकerrupts.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPRC object
 * @irq_index:	The पूर्णांकerrupt index to configure
 * @status:	Returned पूर्णांकerrupts status - one bit per cause:
 *			0 = no पूर्णांकerrupt pending
 *			1 = पूर्णांकerrupt pending
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dprc_get_irq_status(काष्ठा fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			u8 irq_index,
			u32 *status)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dprc_cmd_get_irq_status *cmd_params;
	काष्ठा dprc_rsp_get_irq_status *rsp_params;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPRC_CMDID_GET_IRQ_STATUS,
					  cmd_flags, token);
	cmd_params = (काष्ठा dprc_cmd_get_irq_status *)cmd.params;
	cmd_params->status = cpu_to_le32(*status);
	cmd_params->irq_index = irq_index;

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	rsp_params = (काष्ठा dprc_rsp_get_irq_status *)cmd.params;
	*status = le32_to_cpu(rsp_params->status);

	वापस 0;
पूर्ण

/**
 * dprc_clear_irq_status() - Clear a pending पूर्णांकerrupt's status
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPRC object
 * @irq_index:	The पूर्णांकerrupt index to configure
 * @status:	bits to clear (W1C) - one bit per cause:
 *					0 = करोn't change
 *					1 = clear status bit
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dprc_clear_irq_status(काष्ठा fsl_mc_io *mc_io,
			  u32 cmd_flags,
			  u16 token,
			  u8 irq_index,
			  u32 status)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dprc_cmd_clear_irq_status *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPRC_CMDID_CLEAR_IRQ_STATUS,
					  cmd_flags, token);
	cmd_params = (काष्ठा dprc_cmd_clear_irq_status *)cmd.params;
	cmd_params->status = cpu_to_le32(status);
	cmd_params->irq_index = irq_index;

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण

/**
 * dprc_get_attributes() - Obtains container attributes
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPRC object
 * @attributes	Returned container attributes
 *
 * Return:     '0' on Success; Error code otherwise.
 */
पूर्णांक dprc_get_attributes(काष्ठा fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			काष्ठा dprc_attributes *attr)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dprc_rsp_get_attributes *rsp_params;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPRC_CMDID_GET_ATTR,
					  cmd_flags,
					  token);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	rsp_params = (काष्ठा dprc_rsp_get_attributes *)cmd.params;
	attr->container_id = le32_to_cpu(rsp_params->container_id);
	attr->icid = le32_to_cpu(rsp_params->icid);
	attr->options = le32_to_cpu(rsp_params->options);
	attr->portal_id = le32_to_cpu(rsp_params->portal_id);

	वापस 0;
पूर्ण

/**
 * dprc_get_obj_count() - Obtains the number of objects in the DPRC
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPRC object
 * @obj_count:	Number of objects asचिन्हित to the DPRC
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dprc_get_obj_count(काष्ठा fsl_mc_io *mc_io,
		       u32 cmd_flags,
		       u16 token,
		       पूर्णांक *obj_count)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dprc_rsp_get_obj_count *rsp_params;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPRC_CMDID_GET_OBJ_COUNT,
					  cmd_flags, token);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	rsp_params = (काष्ठा dprc_rsp_get_obj_count *)cmd.params;
	*obj_count = le32_to_cpu(rsp_params->obj_count);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dprc_get_obj_count);

/**
 * dprc_get_obj() - Get general inक्रमmation on an object
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPRC object
 * @obj_index:	Index of the object to be queried (< obj_count)
 * @obj_desc:	Returns the requested object descriptor
 *
 * The object descriptors are retrieved one by one by incrementing
 * obj_index up to (not including) the value of obj_count वापसed
 * from dprc_get_obj_count(). dprc_get_obj_count() must
 * be called prior to dprc_get_obj().
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dprc_get_obj(काष्ठा fsl_mc_io *mc_io,
		 u32 cmd_flags,
		 u16 token,
		 पूर्णांक obj_index,
		 काष्ठा fsl_mc_obj_desc *obj_desc)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dprc_cmd_get_obj *cmd_params;
	काष्ठा dprc_rsp_get_obj *rsp_params;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPRC_CMDID_GET_OBJ,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dprc_cmd_get_obj *)cmd.params;
	cmd_params->obj_index = cpu_to_le32(obj_index);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	rsp_params = (काष्ठा dprc_rsp_get_obj *)cmd.params;
	obj_desc->id = le32_to_cpu(rsp_params->id);
	obj_desc->venकरोr = le16_to_cpu(rsp_params->venकरोr);
	obj_desc->irq_count = rsp_params->irq_count;
	obj_desc->region_count = rsp_params->region_count;
	obj_desc->state = le32_to_cpu(rsp_params->state);
	obj_desc->ver_major = le16_to_cpu(rsp_params->version_major);
	obj_desc->ver_minor = le16_to_cpu(rsp_params->version_minor);
	obj_desc->flags = le16_to_cpu(rsp_params->flags);
	म_नकलन(obj_desc->type, rsp_params->type, 16);
	obj_desc->type[15] = '\0';
	म_नकलन(obj_desc->label, rsp_params->label, 16);
	obj_desc->label[15] = '\0';
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dprc_get_obj);

/**
 * dprc_set_obj_irq() - Set IRQ inक्रमmation क्रम object to trigger an पूर्णांकerrupt.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPRC object
 * @obj_type:	Type of the object to set its IRQ
 * @obj_id:	ID of the object to set its IRQ
 * @irq_index:	The पूर्णांकerrupt index to configure
 * @irq_cfg:	IRQ configuration
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dprc_set_obj_irq(काष्ठा fsl_mc_io *mc_io,
		     u32 cmd_flags,
		     u16 token,
		     अक्षर *obj_type,
		     पूर्णांक obj_id,
		     u8 irq_index,
		     काष्ठा dprc_irq_cfg *irq_cfg)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dprc_cmd_set_obj_irq *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPRC_CMDID_SET_OBJ_IRQ,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dprc_cmd_set_obj_irq *)cmd.params;
	cmd_params->irq_val = cpu_to_le32(irq_cfg->val);
	cmd_params->irq_index = irq_index;
	cmd_params->irq_addr = cpu_to_le64(irq_cfg->paddr);
	cmd_params->irq_num = cpu_to_le32(irq_cfg->irq_num);
	cmd_params->obj_id = cpu_to_le32(obj_id);
	म_नकलन(cmd_params->obj_type, obj_type, 16);
	cmd_params->obj_type[15] = '\0';

	/* send command to mc*/
	वापस mc_send_command(mc_io, &cmd);
पूर्ण
EXPORT_SYMBOL_GPL(dprc_set_obj_irq);

/**
 * dprc_get_obj_region() - Get region inक्रमmation क्रम a specअगरied object.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPRC object
 * @obj_type;	Object type as वापसed in dprc_get_obj()
 * @obj_id:	Unique object instance as वापसed in dprc_get_obj()
 * @region_index: The specअगरic region to query
 * @region_desc:  Returns the requested region descriptor
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dprc_get_obj_region(काष्ठा fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			अक्षर *obj_type,
			पूर्णांक obj_id,
			u8 region_index,
			काष्ठा dprc_region_desc *region_desc)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dprc_cmd_get_obj_region *cmd_params;
	काष्ठा dprc_rsp_get_obj_region *rsp_params;
	पूर्णांक err;

    /*
     * If the DPRC object version was not yet cached, cache it now.
     * Otherwise use the alपढ़ोy cached value.
     */
	अगर (!dprc_major_ver && !dprc_minor_ver) अणु
		err = dprc_get_api_version(mc_io, 0,
				      &dprc_major_ver,
				      &dprc_minor_ver);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (dprc_major_ver > 6 || (dprc_major_ver == 6 && dprc_minor_ver >= 6)) अणु
		/*
		 * MC API version 6.6 changed the size of the MC portals and software
		 * portals to 64K (as implemented by hardware). If older API is in use the
		 * size reported is less (64 bytes क्रम mc portals and 4K क्रम software
		 * portals).
		 */

		cmd.header = mc_encode_cmd_header(DPRC_CMDID_GET_OBJ_REG_V3,
						  cmd_flags, token);

	पूर्ण अन्यथा अगर (dprc_major_ver == 6 && dprc_minor_ver >= 3) अणु
		/*
		 * MC API version 6.3 पूर्णांकroduced a new field to the region
		 * descriptor: base_address. If the older API is in use then the base
		 * address is set to zero to indicate it needs to be obtained अन्यथाwhere
		 * (typically the device tree).
		 */
		cmd.header = mc_encode_cmd_header(DPRC_CMDID_GET_OBJ_REG_V2,
						  cmd_flags, token);
	पूर्ण अन्यथा अणु
		cmd.header = mc_encode_cmd_header(DPRC_CMDID_GET_OBJ_REG,
						  cmd_flags, token);
	पूर्ण

	cmd_params = (काष्ठा dprc_cmd_get_obj_region *)cmd.params;
	cmd_params->obj_id = cpu_to_le32(obj_id);
	cmd_params->region_index = region_index;
	म_नकलन(cmd_params->obj_type, obj_type, 16);
	cmd_params->obj_type[15] = '\0';

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	rsp_params = (काष्ठा dprc_rsp_get_obj_region *)cmd.params;
	region_desc->base_offset = le64_to_cpu(rsp_params->base_offset);
	region_desc->size = le32_to_cpu(rsp_params->size);
	region_desc->type = rsp_params->type;
	region_desc->flags = le32_to_cpu(rsp_params->flags);
	अगर (dprc_major_ver > 6 || (dprc_major_ver == 6 && dprc_minor_ver >= 3))
		region_desc->base_address = le64_to_cpu(rsp_params->base_addr);
	अन्यथा
		region_desc->base_address = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dprc_get_obj_region);

/**
 * dprc_get_api_version - Get Data Path Resource Container API version
 * @mc_io:	Poपूर्णांकer to Mc portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @major_ver:	Major version of Data Path Resource Container API
 * @minor_ver:	Minor version of Data Path Resource Container API
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dprc_get_api_version(काष्ठा fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 *major_ver,
			 u16 *minor_ver)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPRC_CMDID_GET_API_VERSION,
					  cmd_flags, 0);

	/* send command to mc */
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	mc_cmd_पढ़ो_api_version(&cmd, major_ver, minor_ver);

	वापस 0;
पूर्ण

/**
 * dprc_get_container_id - Get container ID associated with a given portal.
 * @mc_io:		Poपूर्णांकer to Mc portal's I/O object
 * @cmd_flags:		Command flags; one or more of 'MC_CMD_FLAG_'
 * @container_id:	Requested container id
 *
 * Return:	'0' on Success; Error code otherwise.
 */
पूर्णांक dprc_get_container_id(काष्ठा fsl_mc_io *mc_io,
			  u32 cmd_flags,
			  पूर्णांक *container_id)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPRC_CMDID_GET_CONT_ID,
					  cmd_flags,
					  0);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	*container_id = (पूर्णांक)mc_cmd_पढ़ो_object_id(&cmd);

	वापस 0;
पूर्ण

/**
 * dprc_get_connection() - Get connected endpoपूर्णांक and link status अगर connection
 *			exists.
 * @mc_io:	Poपूर्णांकer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPRC object
 * @endpoपूर्णांक1:	Endpoपूर्णांक 1 configuration parameters
 * @endpoपूर्णांक2:	Returned endpoपूर्णांक 2 configuration parameters
 * @state:	Returned link state:
 *		1 - link is up;
 *		0 - link is करोwn;
 *		-1 - no connection (endpoपूर्णांक2 inक्रमmation is irrelevant)
 *
 * Return:     '0' on Success; -ENOTCONN अगर connection करोes not exist.
 */
पूर्णांक dprc_get_connection(काष्ठा fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			स्थिर काष्ठा dprc_endpoपूर्णांक *endpoपूर्णांक1,
			काष्ठा dprc_endpoपूर्णांक *endpoपूर्णांक2,
			पूर्णांक *state)
अणु
	काष्ठा dprc_cmd_get_connection *cmd_params;
	काष्ठा dprc_rsp_get_connection *rsp_params;
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	पूर्णांक err, i;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPRC_CMDID_GET_CONNECTION,
					  cmd_flags,
					  token);
	cmd_params = (काष्ठा dprc_cmd_get_connection *)cmd.params;
	cmd_params->ep1_id = cpu_to_le32(endpoपूर्णांक1->id);
	cmd_params->ep1_पूर्णांकerface_id = cpu_to_le16(endpoपूर्णांक1->अगर_id);
	क्रम (i = 0; i < 16; i++)
		cmd_params->ep1_type[i] = endpoपूर्णांक1->type[i];

	/* send command to mc */
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस -ENOTCONN;

	/* retrieve response parameters */
	rsp_params = (काष्ठा dprc_rsp_get_connection *)cmd.params;
	endpoपूर्णांक2->id = le32_to_cpu(rsp_params->ep2_id);
	endpoपूर्णांक2->अगर_id = le16_to_cpu(rsp_params->ep2_पूर्णांकerface_id);
	*state = le32_to_cpu(rsp_params->state);
	क्रम (i = 0; i < 16; i++)
		endpoपूर्णांक2->type[i] = rsp_params->ep2_type[i];

	वापस 0;
पूर्ण
