<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Management Complex (MC) userspace support
 *
 * Copyright 2021 NXP
 *
 */

#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/miscdevice.h>

#समावेश "fsl-mc-private.h"

काष्ठा uapi_priv_data अणु
	काष्ठा fsl_mc_uapi *uapi;
	काष्ठा fsl_mc_io *mc_io;
पूर्ण;

काष्ठा fsl_mc_cmd_desc अणु
	u16 cmdid_value;
	u16 cmdid_mask;
	पूर्णांक size;
	bool token;
	पूर्णांक flags;
पूर्ण;

#घोषणा FSL_MC_CHECK_MODULE_ID		BIT(0)
#घोषणा FSL_MC_CAP_NET_ADMIN_NEEDED	BIT(1)

क्रमागत fsl_mc_cmd_index अणु
	DPDBG_DUMP = 0,
	DPDBG_SET,
	DPRC_GET_CONTAINER_ID,
	DPRC_CREATE_CONT,
	DPRC_DESTROY_CONT,
	DPRC_ASSIGN,
	DPRC_UNASSIGN,
	DPRC_GET_OBJ_COUNT,
	DPRC_GET_OBJ,
	DPRC_GET_RES_COUNT,
	DPRC_GET_RES_IDS,
	DPRC_SET_OBJ_LABEL,
	DPRC_SET_LOCKED,
	DPRC_CONNECT,
	DPRC_DISCONNECT,
	DPRC_GET_POOL,
	DPRC_GET_POOL_COUNT,
	DPRC_GET_CONNECTION,
	DPCI_GET_LINK_STATE,
	DPCI_GET_PEER_ATTR,
	DPAIOP_GET_SL_VERSION,
	DPAIOP_GET_STATE,
	DPMNG_GET_VERSION,
	DPSECI_GET_TX_QUEUE,
	DPMAC_GET_COUNTER,
	DPMAC_GET_MAC_ADDR,
	DPNI_SET_PRIM_MAC,
	DPNI_GET_PRIM_MAC,
	DPNI_GET_STATISTICS,
	DPNI_GET_LINK_STATE,
	DPNI_GET_MAX_FRAME_LENGTH,
	DPSW_GET_TAILDROP,
	DPSW_SET_TAILDROP,
	DPSW_IF_GET_COUNTER,
	DPSW_IF_GET_MAX_FRAME_LENGTH,
	DPDMUX_GET_COUNTER,
	DPDMUX_IF_GET_MAX_FRAME_LENGTH,
	GET_ATTR,
	GET_IRQ_MASK,
	GET_IRQ_STATUS,
	CLOSE,
	OPEN,
	GET_API_VERSION,
	DESTROY,
	CREATE,
पूर्ण;

अटल काष्ठा fsl_mc_cmd_desc fsl_mc_accepted_cmds[] = अणु
	[DPDBG_DUMP] = अणु
		.cmdid_value = 0x1300,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 28,
	पूर्ण,
	[DPDBG_SET] = अणु
		.cmdid_value = 0x1400,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 28,
	पूर्ण,
	[DPRC_GET_CONTAINER_ID] = अणु
		.cmdid_value = 0x8300,
		.cmdid_mask = 0xFFF0,
		.token = false,
		.size = 8,
	पूर्ण,
	[DPRC_CREATE_CONT] = अणु
		.cmdid_value = 0x1510,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 40,
		.flags = FSL_MC_CAP_NET_ADMIN_NEEDED,
	पूर्ण,
	[DPRC_DESTROY_CONT] = अणु
		.cmdid_value = 0x1520,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 12,
		.flags = FSL_MC_CAP_NET_ADMIN_NEEDED,
	पूर्ण,
	[DPRC_ASSIGN] = अणु
		.cmdid_value = 0x1570,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 40,
		.flags = FSL_MC_CAP_NET_ADMIN_NEEDED,
	पूर्ण,
	[DPRC_UNASSIGN] = अणु
		.cmdid_value = 0x1580,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 40,
		.flags = FSL_MC_CAP_NET_ADMIN_NEEDED,
	पूर्ण,
	[DPRC_GET_OBJ_COUNT] = अणु
		.cmdid_value = 0x1590,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 16,
	पूर्ण,
	[DPRC_GET_OBJ] = अणु
		.cmdid_value = 0x15A0,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 12,
	पूर्ण,
	[DPRC_GET_RES_COUNT] = अणु
		.cmdid_value = 0x15B0,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 32,
	पूर्ण,
	[DPRC_GET_RES_IDS] = अणु
		.cmdid_value = 0x15C0,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 40,
	पूर्ण,
	[DPRC_SET_OBJ_LABEL] = अणु
		.cmdid_value = 0x1610,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 48,
		.flags = FSL_MC_CAP_NET_ADMIN_NEEDED,
	पूर्ण,
	[DPRC_SET_LOCKED] = अणु
		.cmdid_value = 0x16B0,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 16,
		.flags = FSL_MC_CAP_NET_ADMIN_NEEDED,
	पूर्ण,
	[DPRC_CONNECT] = अणु
		.cmdid_value = 0x1670,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 56,
		.flags = FSL_MC_CAP_NET_ADMIN_NEEDED,
	पूर्ण,
	[DPRC_DISCONNECT] = अणु
		.cmdid_value = 0x1680,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 32,
		.flags = FSL_MC_CAP_NET_ADMIN_NEEDED,
	पूर्ण,
	[DPRC_GET_POOL] = अणु
		.cmdid_value = 0x1690,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 12,
	पूर्ण,
	[DPRC_GET_POOL_COUNT] = अणु
		.cmdid_value = 0x16A0,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 8,
	पूर्ण,
	[DPRC_GET_CONNECTION] = अणु
		.cmdid_value = 0x16C0,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 32,
	पूर्ण,

	[DPCI_GET_LINK_STATE] = अणु
		.cmdid_value = 0x0E10,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 8,
	पूर्ण,
	[DPCI_GET_PEER_ATTR] = अणु
		.cmdid_value = 0x0E20,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 8,
	पूर्ण,
	[DPAIOP_GET_SL_VERSION] = अणु
		.cmdid_value = 0x2820,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 8,
	पूर्ण,
	[DPAIOP_GET_STATE] = अणु
		.cmdid_value = 0x2830,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 8,
	पूर्ण,
	[DPMNG_GET_VERSION] = अणु
		.cmdid_value = 0x8310,
		.cmdid_mask = 0xFFF0,
		.token = false,
		.size = 8,
	पूर्ण,
	[DPSECI_GET_TX_QUEUE] = अणु
		.cmdid_value = 0x1970,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 14,
	पूर्ण,
	[DPMAC_GET_COUNTER] = अणु
		.cmdid_value = 0x0c40,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 9,
	पूर्ण,
	[DPMAC_GET_MAC_ADDR] = अणु
		.cmdid_value = 0x0c50,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 8,
	पूर्ण,
	[DPNI_SET_PRIM_MAC] = अणु
		.cmdid_value = 0x2240,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 16,
		.flags = FSL_MC_CAP_NET_ADMIN_NEEDED,
	पूर्ण,
	[DPNI_GET_PRIM_MAC] = अणु
		.cmdid_value = 0x2250,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 8,
	पूर्ण,
	[DPNI_GET_STATISTICS] = अणु
		.cmdid_value = 0x25D0,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 10,
	पूर्ण,
	[DPNI_GET_LINK_STATE] = अणु
		.cmdid_value = 0x2150,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 8,
	पूर्ण,
	[DPNI_GET_MAX_FRAME_LENGTH] = अणु
		.cmdid_value = 0x2170,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 8,
	पूर्ण,
	[DPSW_GET_TAILDROP] = अणु
		.cmdid_value = 0x0A80,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 14,
	पूर्ण,
	[DPSW_SET_TAILDROP] = अणु
		.cmdid_value = 0x0A90,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 24,
		.flags = FSL_MC_CAP_NET_ADMIN_NEEDED,
	पूर्ण,
	[DPSW_IF_GET_COUNTER] = अणु
		.cmdid_value = 0x0340,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 11,
	पूर्ण,
	[DPSW_IF_GET_MAX_FRAME_LENGTH] = अणु
		.cmdid_value = 0x0450,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 10,
	पूर्ण,
	[DPDMUX_GET_COUNTER] = अणु
		.cmdid_value = 0x0b20,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 11,
	पूर्ण,
	[DPDMUX_IF_GET_MAX_FRAME_LENGTH] = अणु
		.cmdid_value = 0x0a20,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 10,
	पूर्ण,
	[GET_ATTR] = अणु
		.cmdid_value = 0x0040,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 8,
	पूर्ण,
	[GET_IRQ_MASK] = अणु
		.cmdid_value = 0x0150,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 13,
	पूर्ण,
	[GET_IRQ_STATUS] = अणु
		.cmdid_value = 0x0160,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 13,
	पूर्ण,
	[CLOSE] = अणु
		.cmdid_value = 0x8000,
		.cmdid_mask = 0xFFF0,
		.token = true,
		.size = 8,
	पूर्ण,

	/* Common commands amongst all types of objects. Must be checked last. */
	[OPEN] = अणु
		.cmdid_value = 0x8000,
		.cmdid_mask = 0xFC00,
		.token = false,
		.size = 12,
		.flags = FSL_MC_CHECK_MODULE_ID,
	पूर्ण,
	[GET_API_VERSION] = अणु
		.cmdid_value = 0xA000,
		.cmdid_mask = 0xFC00,
		.token = false,
		.size = 8,
		.flags = FSL_MC_CHECK_MODULE_ID,
	पूर्ण,
	[DESTROY] = अणु
		.cmdid_value = 0x9800,
		.cmdid_mask = 0xFC00,
		.token = true,
		.size = 12,
		.flags = FSL_MC_CHECK_MODULE_ID | FSL_MC_CAP_NET_ADMIN_NEEDED,
	पूर्ण,
	[CREATE] = अणु
		.cmdid_value = 0x9000,
		.cmdid_mask = 0xFC00,
		.token = true,
		.size = 64,
		.flags = FSL_MC_CHECK_MODULE_ID | FSL_MC_CAP_NET_ADMIN_NEEDED,
	पूर्ण,
पूर्ण;

#घोषणा FSL_MC_NUM_ACCEPTED_CMDS ARRAY_SIZE(fsl_mc_accepted_cmds)

#घोषणा FSL_MC_MAX_MODULE_ID 0x10

अटल पूर्णांक fsl_mc_command_check(काष्ठा fsl_mc_device *mc_dev,
				काष्ठा fsl_mc_command *mc_cmd)
अणु
	काष्ठा fsl_mc_cmd_desc *desc = शून्य;
	पूर्णांक mc_cmd_max_size, i;
	bool token_provided;
	u16 cmdid, module_id;
	अक्षर *mc_cmd_end;
	अक्षर sum = 0;

	/* Check अगर this is an accepted MC command */
	cmdid = mc_cmd_hdr_पढ़ो_cmdid(mc_cmd);
	क्रम (i = 0; i < FSL_MC_NUM_ACCEPTED_CMDS; i++) अणु
		desc = &fsl_mc_accepted_cmds[i];
		अगर ((cmdid & desc->cmdid_mask) == desc->cmdid_value)
			अवरोध;
	पूर्ण
	अगर (i == FSL_MC_NUM_ACCEPTED_CMDS) अणु
		dev_err(&mc_dev->dev, "MC command 0x%04x: cmdid not accepted\n", cmdid);
		वापस -EACCES;
	पूर्ण

	/* Check अगर the size of the command is honored. Anything beyond the
	 * last valid byte of the command should be zeroed.
	 */
	mc_cmd_max_size = माप(*mc_cmd);
	mc_cmd_end = ((अक्षर *)mc_cmd) + desc->size;
	क्रम (i = desc->size; i < mc_cmd_max_size; i++)
		sum |= *mc_cmd_end++;
	अगर (sum) अणु
		dev_err(&mc_dev->dev, "MC command 0x%04x: garbage beyond max size of %d bytes!\n",
			cmdid, desc->size);
		वापस -EACCES;
	पूर्ण

	/* Some MC commands request a token to be passed so that object
	 * identअगरication is possible. Check अगर the token passed in the command
	 * is as expected.
	 */
	token_provided = mc_cmd_hdr_पढ़ो_token(mc_cmd) ? true : false;
	अगर (token_provided != desc->token) अणु
		dev_err(&mc_dev->dev, "MC command 0x%04x: token 0x%04x is invalid!\n",
			cmdid, mc_cmd_hdr_पढ़ो_token(mc_cmd));
		वापस -EACCES;
	पूर्ण

	/* If needed, check अगर the module ID passed is valid */
	अगर (desc->flags & FSL_MC_CHECK_MODULE_ID) अणु
		/* The module ID is represented by bits [4:9] from the cmdid */
		module_id = (cmdid & GENMASK(9, 4)) >> 4;
		अगर (module_id == 0 || module_id > FSL_MC_MAX_MODULE_ID) अणु
			dev_err(&mc_dev->dev, "MC command 0x%04x: unknown module ID 0x%x\n",
				cmdid, module_id);
			वापस -EACCES;
		पूर्ण
	पूर्ण

	/* Some commands alter how hardware resources are managed. For these
	 * commands, check क्रम CAP_NET_ADMIN.
	 */
	अगर (desc->flags & FSL_MC_CAP_NET_ADMIN_NEEDED) अणु
		अगर (!capable(CAP_NET_ADMIN)) अणु
			dev_err(&mc_dev->dev, "MC command 0x%04x: needs CAP_NET_ADMIN!\n",
				cmdid);
			वापस -EPERM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_mc_uapi_send_command(काष्ठा fsl_mc_device *mc_dev, अचिन्हित दीर्घ arg,
				    काष्ठा fsl_mc_io *mc_io)
अणु
	काष्ठा fsl_mc_command mc_cmd;
	पूर्णांक error;

	error = copy_from_user(&mc_cmd, (व्योम __user *)arg, माप(mc_cmd));
	अगर (error)
		वापस -EFAULT;

	error = fsl_mc_command_check(mc_dev, &mc_cmd);
	अगर (error)
		वापस error;

	error = mc_send_command(mc_io, &mc_cmd);
	अगर (error)
		वापस error;

	error = copy_to_user((व्योम __user *)arg, &mc_cmd, माप(mc_cmd));
	अगर (error)
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_mc_uapi_dev_खोलो(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा fsl_mc_device *root_mc_device;
	काष्ठा uapi_priv_data *priv_data;
	काष्ठा fsl_mc_io *dynamic_mc_io;
	काष्ठा fsl_mc_uapi *mc_uapi;
	काष्ठा fsl_mc_bus *mc_bus;
	पूर्णांक error;

	priv_data = kzalloc(माप(*priv_data), GFP_KERNEL);
	अगर (!priv_data)
		वापस -ENOMEM;

	mc_uapi = container_of(filep->निजी_data, काष्ठा fsl_mc_uapi, misc);
	mc_bus = container_of(mc_uapi, काष्ठा fsl_mc_bus, uapi_misc);
	root_mc_device = &mc_bus->mc_dev;

	mutex_lock(&mc_uapi->mutex);

	अगर (!mc_uapi->local_instance_in_use) अणु
		priv_data->mc_io = mc_uapi->अटल_mc_io;
		mc_uapi->local_instance_in_use = 1;
	पूर्ण अन्यथा अणु
		error = fsl_mc_portal_allocate(root_mc_device, 0,
					       &dynamic_mc_io);
		अगर (error) अणु
			dev_dbg(&root_mc_device->dev,
				"Could not allocate MC portal\n");
			जाओ error_portal_allocate;
		पूर्ण

		priv_data->mc_io = dynamic_mc_io;
	पूर्ण
	priv_data->uapi = mc_uapi;
	filep->निजी_data = priv_data;

	mutex_unlock(&mc_uapi->mutex);

	वापस 0;

error_portal_allocate:
	mutex_unlock(&mc_uapi->mutex);
	kमुक्त(priv_data);

	वापस error;
पूर्ण

अटल पूर्णांक fsl_mc_uapi_dev_release(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा uapi_priv_data *priv_data;
	काष्ठा fsl_mc_uapi *mc_uapi;
	काष्ठा fsl_mc_io *mc_io;

	priv_data = filep->निजी_data;
	mc_uapi = priv_data->uapi;
	mc_io = priv_data->mc_io;

	mutex_lock(&mc_uapi->mutex);

	अगर (mc_io == mc_uapi->अटल_mc_io)
		mc_uapi->local_instance_in_use = 0;
	अन्यथा
		fsl_mc_portal_मुक्त(mc_io);

	kमुक्त(filep->निजी_data);
	filep->निजी_data =  शून्य;

	mutex_unlock(&mc_uapi->mutex);

	वापस 0;
पूर्ण

अटल दीर्घ fsl_mc_uapi_dev_ioctl(काष्ठा file *file,
				  अचिन्हित पूर्णांक cmd,
				  अचिन्हित दीर्घ arg)
अणु
	काष्ठा uapi_priv_data *priv_data = file->निजी_data;
	काष्ठा fsl_mc_device *root_mc_device;
	काष्ठा fsl_mc_bus *mc_bus;
	पूर्णांक error;

	mc_bus = container_of(priv_data->uapi, काष्ठा fsl_mc_bus, uapi_misc);
	root_mc_device = &mc_bus->mc_dev;

	चयन (cmd) अणु
	हाल FSL_MC_SEND_MC_COMMAND:
		error = fsl_mc_uapi_send_command(root_mc_device, arg, priv_data->mc_io);
		अवरोध;
	शेष:
		dev_dbg(&root_mc_device->dev, "unexpected ioctl call number\n");
		error = -EINVAL;
	पूर्ण

	वापस error;
पूर्ण

अटल स्थिर काष्ठा file_operations fsl_mc_uapi_dev_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = fsl_mc_uapi_dev_खोलो,
	.release = fsl_mc_uapi_dev_release,
	.unlocked_ioctl = fsl_mc_uapi_dev_ioctl,
पूर्ण;

पूर्णांक fsl_mc_uapi_create_device_file(काष्ठा fsl_mc_bus *mc_bus)
अणु
	काष्ठा fsl_mc_device *mc_dev = &mc_bus->mc_dev;
	काष्ठा fsl_mc_uapi *mc_uapi = &mc_bus->uapi_misc;
	पूर्णांक error;

	mc_uapi->misc.minor = MISC_DYNAMIC_MINOR;
	mc_uapi->misc.name = dev_name(&mc_dev->dev);
	mc_uapi->misc.fops = &fsl_mc_uapi_dev_fops;

	error = misc_रेजिस्टर(&mc_uapi->misc);
	अगर (error)
		वापस error;

	mc_uapi->अटल_mc_io = mc_bus->mc_dev.mc_io;

	mutex_init(&mc_uapi->mutex);

	वापस 0;
पूर्ण

व्योम fsl_mc_uapi_हटाओ_device_file(काष्ठा fsl_mc_bus *mc_bus)
अणु
	misc_deरेजिस्टर(&mc_bus->uapi_misc.misc);
पूर्ण
