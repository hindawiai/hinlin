<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies */

#समावेश <devlink.h>

#समावेश "mlx5_core.h"
#समावेश "fw_reset.h"
#समावेश "fs_core.h"
#समावेश "eswitch.h"
#समावेश "sf/dev/dev.h"
#समावेश "sf/sf.h"

अटल पूर्णांक mlx5_devlink_flash_update(काष्ठा devlink *devlink,
				     काष्ठा devlink_flash_update_params *params,
				     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);

	वापस mlx5_firmware_flash(dev, params->fw, extack);
पूर्ण

अटल u8 mlx5_fw_ver_major(u32 version)
अणु
	वापस (version >> 24) & 0xff;
पूर्ण

अटल u8 mlx5_fw_ver_minor(u32 version)
अणु
	वापस (version >> 16) & 0xff;
पूर्ण

अटल u16 mlx5_fw_ver_subminor(u32 version)
अणु
	वापस version & 0xffff;
पूर्ण

#घोषणा DEVLINK_FW_STRING_LEN 32

अटल पूर्णांक
mlx5_devlink_info_get(काष्ठा devlink *devlink, काष्ठा devlink_info_req *req,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);
	अक्षर version_str[DEVLINK_FW_STRING_LEN];
	u32 running_fw, stored_fw;
	पूर्णांक err;

	err = devlink_info_driver_name_put(req, KBUILD_MODNAME);
	अगर (err)
		वापस err;

	err = devlink_info_version_fixed_put(req, "fw.psid", dev->board_id);
	अगर (err)
		वापस err;

	err = mlx5_fw_version_query(dev, &running_fw, &stored_fw);
	अगर (err)
		वापस err;

	snम_लिखो(version_str, माप(version_str), "%d.%d.%04d",
		 mlx5_fw_ver_major(running_fw), mlx5_fw_ver_minor(running_fw),
		 mlx5_fw_ver_subminor(running_fw));
	err = devlink_info_version_running_put(req, "fw.version", version_str);
	अगर (err)
		वापस err;

	/* no pending version, वापस running (stored) version */
	अगर (stored_fw == 0)
		stored_fw = running_fw;

	snम_लिखो(version_str, माप(version_str), "%d.%d.%04d",
		 mlx5_fw_ver_major(stored_fw), mlx5_fw_ver_minor(stored_fw),
		 mlx5_fw_ver_subminor(stored_fw));
	err = devlink_info_version_stored_put(req, "fw.version", version_str);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_devlink_reload_fw_activate(काष्ठा devlink *devlink, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);
	u8 reset_level, reset_type, net_port_alive;
	पूर्णांक err;

	err = mlx5_fw_reset_query(dev, &reset_level, &reset_type);
	अगर (err)
		वापस err;
	अगर (!(reset_level & MLX5_MFRL_REG_RESET_LEVEL3)) अणु
		NL_SET_ERR_MSG_MOD(extack, "FW activate requires reboot");
		वापस -EINVAL;
	पूर्ण

	net_port_alive = !!(reset_type & MLX5_MFRL_REG_RESET_TYPE_NET_PORT_ALIVE);
	err = mlx5_fw_reset_set_reset_sync(dev, net_port_alive);
	अगर (err)
		जाओ out;

	err = mlx5_fw_reset_रुको_reset_करोne(dev);
out:
	अगर (err)
		NL_SET_ERR_MSG_MOD(extack, "FW activate command failed");
	वापस err;
पूर्ण

अटल पूर्णांक mlx5_devlink_trigger_fw_live_patch(काष्ठा devlink *devlink,
					      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);
	u8 reset_level;
	पूर्णांक err;

	err = mlx5_fw_reset_query(dev, &reset_level, शून्य);
	अगर (err)
		वापस err;
	अगर (!(reset_level & MLX5_MFRL_REG_RESET_LEVEL0)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "FW upgrade to the stored FW can't be done by FW live patching");
		वापस -EINVAL;
	पूर्ण

	वापस mlx5_fw_reset_set_live_patch(dev);
पूर्ण

अटल पूर्णांक mlx5_devlink_reload_करोwn(काष्ठा devlink *devlink, bool netns_change,
				    क्रमागत devlink_reload_action action,
				    क्रमागत devlink_reload_limit limit,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);
	bool sf_dev_allocated;

	sf_dev_allocated = mlx5_sf_dev_allocated(dev);
	अगर (sf_dev_allocated) अणु
		/* Reload results in deleting SF device which further results in
		 * unरेजिस्टरing devlink instance जबतक holding devlink_mutext.
		 * Hence, करो not support reload.
		 */
		NL_SET_ERR_MSG_MOD(extack, "reload is unsupported when SFs are allocated");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (mlx5_lag_is_active(dev)) अणु
		NL_SET_ERR_MSG_MOD(extack, "reload is unsupported in Lag mode");
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (action) अणु
	हाल DEVLINK_RELOAD_ACTION_DRIVER_REINIT:
		mlx5_unload_one(dev);
		वापस 0;
	हाल DEVLINK_RELOAD_ACTION_FW_ACTIVATE:
		अगर (limit == DEVLINK_RELOAD_LIMIT_NO_RESET)
			वापस mlx5_devlink_trigger_fw_live_patch(devlink, extack);
		वापस mlx5_devlink_reload_fw_activate(devlink, extack);
	शेष:
		/* Unsupported action should not get to this function */
		WARN_ON(1);
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_devlink_reload_up(काष्ठा devlink *devlink, क्रमागत devlink_reload_action action,
				  क्रमागत devlink_reload_limit limit, u32 *actions_perक्रमmed,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);

	*actions_perक्रमmed = BIT(action);
	चयन (action) अणु
	हाल DEVLINK_RELOAD_ACTION_DRIVER_REINIT:
		वापस mlx5_load_one(dev);
	हाल DEVLINK_RELOAD_ACTION_FW_ACTIVATE:
		अगर (limit == DEVLINK_RELOAD_LIMIT_NO_RESET)
			अवरोध;
		/* On fw_activate action, also driver is reloaded and reinit perक्रमmed */
		*actions_perक्रमmed |= BIT(DEVLINK_RELOAD_ACTION_DRIVER_REINIT);
		वापस mlx5_load_one(dev);
	शेष:
		/* Unsupported action should not get to this function */
		WARN_ON(1);
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा mlx5_devlink_trap *mlx5_find_trap_by_id(काष्ठा mlx5_core_dev *dev, पूर्णांक trap_id)
अणु
	काष्ठा mlx5_devlink_trap *dl_trap;

	list_क्रम_each_entry(dl_trap, &dev->priv.traps, list)
		अगर (dl_trap->trap.id == trap_id)
			वापस dl_trap;

	वापस शून्य;
पूर्ण

अटल पूर्णांक mlx5_devlink_trap_init(काष्ठा devlink *devlink, स्थिर काष्ठा devlink_trap *trap,
				  व्योम *trap_ctx)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);
	काष्ठा mlx5_devlink_trap *dl_trap;

	dl_trap = kzalloc(माप(*dl_trap), GFP_KERNEL);
	अगर (!dl_trap)
		वापस -ENOMEM;

	dl_trap->trap.id = trap->id;
	dl_trap->trap.action = DEVLINK_TRAP_ACTION_DROP;
	dl_trap->item = trap_ctx;

	अगर (mlx5_find_trap_by_id(dev, trap->id)) अणु
		kमुक्त(dl_trap);
		mlx5_core_err(dev, "Devlink trap: Trap 0x%x already found", trap->id);
		वापस -EEXIST;
	पूर्ण

	list_add_tail(&dl_trap->list, &dev->priv.traps);
	वापस 0;
पूर्ण

अटल व्योम mlx5_devlink_trap_fini(काष्ठा devlink *devlink, स्थिर काष्ठा devlink_trap *trap,
				   व्योम *trap_ctx)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);
	काष्ठा mlx5_devlink_trap *dl_trap;

	dl_trap = mlx5_find_trap_by_id(dev, trap->id);
	अगर (!dl_trap) अणु
		mlx5_core_err(dev, "Devlink trap: Missing trap id 0x%x", trap->id);
		वापस;
	पूर्ण
	list_del(&dl_trap->list);
	kमुक्त(dl_trap);
पूर्ण

अटल पूर्णांक mlx5_devlink_trap_action_set(काष्ठा devlink *devlink,
					स्थिर काष्ठा devlink_trap *trap,
					क्रमागत devlink_trap_action action,
					काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);
	क्रमागत devlink_trap_action action_orig;
	काष्ठा mlx5_devlink_trap *dl_trap;
	पूर्णांक err = 0;

	अगर (is_mdev_चयनdev_mode(dev)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Devlink traps can't be set in switchdev mode");
		वापस -EOPNOTSUPP;
	पूर्ण

	dl_trap = mlx5_find_trap_by_id(dev, trap->id);
	अगर (!dl_trap) अणु
		mlx5_core_err(dev, "Devlink trap: Set action on invalid trap id 0x%x", trap->id);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (action != DEVLINK_TRAP_ACTION_DROP && action != DEVLINK_TRAP_ACTION_TRAP) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (action == dl_trap->trap.action)
		जाओ out;

	action_orig = dl_trap->trap.action;
	dl_trap->trap.action = action;
	err = mlx5_blocking_notअगरier_call_chain(dev, MLX5_DRIVER_EVENT_TYPE_TRAP,
						&dl_trap->trap);
	अगर (err)
		dl_trap->trap.action = action_orig;
out:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा devlink_ops mlx5_devlink_ops = अणु
#अगर_घोषित CONFIG_MLX5_ESWITCH
	.eचयन_mode_set = mlx5_devlink_eचयन_mode_set,
	.eचयन_mode_get = mlx5_devlink_eचयन_mode_get,
	.eचयन_अंतरभूत_mode_set = mlx5_devlink_eचयन_अंतरभूत_mode_set,
	.eचयन_अंतरभूत_mode_get = mlx5_devlink_eचयन_अंतरभूत_mode_get,
	.eचयन_encap_mode_set = mlx5_devlink_eचयन_encap_mode_set,
	.eचयन_encap_mode_get = mlx5_devlink_eचयन_encap_mode_get,
	.port_function_hw_addr_get = mlx5_devlink_port_function_hw_addr_get,
	.port_function_hw_addr_set = mlx5_devlink_port_function_hw_addr_set,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MLX5_SF_MANAGER
	.port_new = mlx5_devlink_sf_port_new,
	.port_del = mlx5_devlink_sf_port_del,
	.port_fn_state_get = mlx5_devlink_sf_port_fn_state_get,
	.port_fn_state_set = mlx5_devlink_sf_port_fn_state_set,
#पूर्ण_अगर
	.flash_update = mlx5_devlink_flash_update,
	.info_get = mlx5_devlink_info_get,
	.reload_actions = BIT(DEVLINK_RELOAD_ACTION_DRIVER_REINIT) |
			  BIT(DEVLINK_RELOAD_ACTION_FW_ACTIVATE),
	.reload_limits = BIT(DEVLINK_RELOAD_LIMIT_NO_RESET),
	.reload_करोwn = mlx5_devlink_reload_करोwn,
	.reload_up = mlx5_devlink_reload_up,
	.trap_init = mlx5_devlink_trap_init,
	.trap_fini = mlx5_devlink_trap_fini,
	.trap_action_set = mlx5_devlink_trap_action_set,
पूर्ण;

व्योम mlx5_devlink_trap_report(काष्ठा mlx5_core_dev *dev, पूर्णांक trap_id, काष्ठा sk_buff *skb,
			      काष्ठा devlink_port *dl_port)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(dev);
	काष्ठा mlx5_devlink_trap *dl_trap;

	dl_trap = mlx5_find_trap_by_id(dev, trap_id);
	अगर (!dl_trap) अणु
		mlx5_core_err(dev, "Devlink trap: Report on invalid trap id 0x%x", trap_id);
		वापस;
	पूर्ण

	अगर (dl_trap->trap.action != DEVLINK_TRAP_ACTION_TRAP) अणु
		mlx5_core_dbg(dev, "Devlink trap: Trap id %d has action %d", trap_id,
			      dl_trap->trap.action);
		वापस;
	पूर्ण
	devlink_trap_report(devlink, skb, dl_trap->item, dl_port, शून्य);
पूर्ण

पूर्णांक mlx5_devlink_trap_get_num_active(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_devlink_trap *dl_trap;
	पूर्णांक count = 0;

	list_क्रम_each_entry(dl_trap, &dev->priv.traps, list)
		अगर (dl_trap->trap.action == DEVLINK_TRAP_ACTION_TRAP)
			count++;

	वापस count;
पूर्ण

पूर्णांक mlx5_devlink_traps_get_action(काष्ठा mlx5_core_dev *dev, पूर्णांक trap_id,
				  क्रमागत devlink_trap_action *action)
अणु
	काष्ठा mlx5_devlink_trap *dl_trap;

	dl_trap = mlx5_find_trap_by_id(dev, trap_id);
	अगर (!dl_trap) अणु
		mlx5_core_err(dev, "Devlink trap: Get action on invalid trap id 0x%x",
			      trap_id);
		वापस -EINVAL;
	पूर्ण

	*action = dl_trap->trap.action;
	वापस 0;
पूर्ण

काष्ठा devlink *mlx5_devlink_alloc(व्योम)
अणु
	वापस devlink_alloc(&mlx5_devlink_ops, माप(काष्ठा mlx5_core_dev));
पूर्ण

व्योम mlx5_devlink_मुक्त(काष्ठा devlink *devlink)
अणु
	devlink_मुक्त(devlink);
पूर्ण

अटल पूर्णांक mlx5_devlink_fs_mode_validate(काष्ठा devlink *devlink, u32 id,
					 जोड़ devlink_param_value val,
					 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);
	अक्षर *value = val.vstr;
	पूर्णांक err = 0;

	अगर (!म_भेद(value, "dmfs")) अणु
		वापस 0;
	पूर्ण अन्यथा अगर (!म_भेद(value, "smfs")) अणु
		u8 eचयन_mode;
		bool smfs_cap;

		eचयन_mode = mlx5_eचयन_mode(dev);
		smfs_cap = mlx5_fs_dr_is_supported(dev);

		अगर (!smfs_cap) अणु
			err = -EOPNOTSUPP;
			NL_SET_ERR_MSG_MOD(extack,
					   "Software managed steering is not supported by current device");
		पूर्ण

		अन्यथा अगर (eचयन_mode == MLX5_ESWITCH_OFFLOADS) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Software managed steering is not supported when eswitch offloads enabled.");
			err = -EOPNOTSUPP;
		पूर्ण
	पूर्ण अन्यथा अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Bad parameter: supported values are [\"dmfs\", \"smfs\"]");
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mlx5_devlink_fs_mode_set(काष्ठा devlink *devlink, u32 id,
				    काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);
	क्रमागत mlx5_flow_steering_mode mode;

	अगर (!म_भेद(ctx->val.vstr, "smfs"))
		mode = MLX5_FLOW_STEERING_MODE_SMFS;
	अन्यथा
		mode = MLX5_FLOW_STEERING_MODE_DMFS;
	dev->priv.steering->mode = mode;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_devlink_fs_mode_get(काष्ठा devlink *devlink, u32 id,
				    काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);

	अगर (dev->priv.steering->mode == MLX5_FLOW_STEERING_MODE_SMFS)
		म_नकल(ctx->val.vstr, "smfs");
	अन्यथा
		म_नकल(ctx->val.vstr, "dmfs");
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_devlink_enable_roce_validate(काष्ठा devlink *devlink, u32 id,
					     जोड़ devlink_param_value val,
					     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);
	bool new_state = val.vbool;

	अगर (new_state && !MLX5_CAP_GEN(dev, roce)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Device doesn't support RoCE");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (mlx5_core_is_mp_slave(dev) || mlx5_lag_is_active(dev)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Multi port slave/Lag device can't configure RoCE");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_MLX5_ESWITCH
अटल पूर्णांक mlx5_devlink_large_group_num_validate(काष्ठा devlink *devlink, u32 id,
						 जोड़ devlink_param_value val,
						 काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक group_num = val.vu32;

	अगर (group_num < 1 || group_num > 1024) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Unsupported group number, supported range is 1-1024");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_devlink_esw_port_metadata_set(काष्ठा devlink *devlink, u32 id,
					      काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);

	अगर (!MLX5_ESWITCH_MANAGER(dev))
		वापस -EOPNOTSUPP;

	वापस mlx5_esw_offloads_vport_metadata_set(dev->priv.eचयन, ctx->val.vbool);
पूर्ण

अटल पूर्णांक mlx5_devlink_esw_port_metadata_get(काष्ठा devlink *devlink, u32 id,
					      काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);

	अगर (!MLX5_ESWITCH_MANAGER(dev))
		वापस -EOPNOTSUPP;

	ctx->val.vbool = mlx5_eचयन_vport_match_metadata_enabled(dev->priv.eचयन);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_devlink_esw_port_metadata_validate(काष्ठा devlink *devlink, u32 id,
						   जोड़ devlink_param_value val,
						   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);
	u8 esw_mode;

	अगर (!MLX5_ESWITCH_MANAGER(dev)) अणु
		NL_SET_ERR_MSG_MOD(extack, "E-Switch is unsupported");
		वापस -EOPNOTSUPP;
	पूर्ण
	esw_mode = mlx5_eचयन_mode(dev);
	अगर (esw_mode == MLX5_ESWITCH_OFFLOADS) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "E-Switch must either disabled or non switchdev mode");
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक mlx5_devlink_enable_remote_dev_reset_set(काष्ठा devlink *devlink, u32 id,
						    काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);

	mlx5_fw_reset_enable_remote_dev_reset_set(dev, ctx->val.vbool);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_devlink_enable_remote_dev_reset_get(काष्ठा devlink *devlink, u32 id,
						    काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);

	ctx->val.vbool = mlx5_fw_reset_enable_remote_dev_reset_get(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा devlink_param mlx5_devlink_params[] = अणु
	DEVLINK_PARAM_DRIVER(MLX5_DEVLINK_PARAM_ID_FLOW_STEERING_MODE,
			     "flow_steering_mode", DEVLINK_PARAM_TYPE_STRING,
			     BIT(DEVLINK_PARAM_CMODE_RUNTIME),
			     mlx5_devlink_fs_mode_get, mlx5_devlink_fs_mode_set,
			     mlx5_devlink_fs_mode_validate),
	DEVLINK_PARAM_GENERIC(ENABLE_ROCE, BIT(DEVLINK_PARAM_CMODE_DRIVERINIT),
			      शून्य, शून्य, mlx5_devlink_enable_roce_validate),
#अगर_घोषित CONFIG_MLX5_ESWITCH
	DEVLINK_PARAM_DRIVER(MLX5_DEVLINK_PARAM_ID_ESW_LARGE_GROUP_NUM,
			     "fdb_large_groups", DEVLINK_PARAM_TYPE_U32,
			     BIT(DEVLINK_PARAM_CMODE_DRIVERINIT),
			     शून्य, शून्य,
			     mlx5_devlink_large_group_num_validate),
	DEVLINK_PARAM_DRIVER(MLX5_DEVLINK_PARAM_ID_ESW_PORT_METADATA,
			     "esw_port_metadata", DEVLINK_PARAM_TYPE_BOOL,
			     BIT(DEVLINK_PARAM_CMODE_RUNTIME),
			     mlx5_devlink_esw_port_metadata_get,
			     mlx5_devlink_esw_port_metadata_set,
			     mlx5_devlink_esw_port_metadata_validate),
#पूर्ण_अगर
	DEVLINK_PARAM_GENERIC(ENABLE_REMOTE_DEV_RESET, BIT(DEVLINK_PARAM_CMODE_RUNTIME),
			      mlx5_devlink_enable_remote_dev_reset_get,
			      mlx5_devlink_enable_remote_dev_reset_set, शून्य),
पूर्ण;

अटल व्योम mlx5_devlink_set_params_init_values(काष्ठा devlink *devlink)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);
	जोड़ devlink_param_value value;

	अगर (dev->priv.steering->mode == MLX5_FLOW_STEERING_MODE_DMFS)
		म_नकल(value.vstr, "dmfs");
	अन्यथा
		म_नकल(value.vstr, "smfs");
	devlink_param_driverinit_value_set(devlink,
					   MLX5_DEVLINK_PARAM_ID_FLOW_STEERING_MODE,
					   value);

	value.vbool = MLX5_CAP_GEN(dev, roce);
	devlink_param_driverinit_value_set(devlink,
					   DEVLINK_PARAM_GENERIC_ID_ENABLE_ROCE,
					   value);

#अगर_घोषित CONFIG_MLX5_ESWITCH
	value.vu32 = ESW_OFFLOADS_DEFAULT_NUM_GROUPS;
	devlink_param_driverinit_value_set(devlink,
					   MLX5_DEVLINK_PARAM_ID_ESW_LARGE_GROUP_NUM,
					   value);

	अगर (MLX5_ESWITCH_MANAGER(dev)) अणु
		अगर (mlx5_esw_vport_match_metadata_supported(dev->priv.eचयन)) अणु
			dev->priv.eचयन->flags |= MLX5_ESWITCH_VPORT_MATCH_METADATA;
			value.vbool = true;
		पूर्ण अन्यथा अणु
			value.vbool = false;
		पूर्ण
		devlink_param_driverinit_value_set(devlink,
						   MLX5_DEVLINK_PARAM_ID_ESW_PORT_METADATA,
						   value);
	पूर्ण
#पूर्ण_अगर
पूर्ण

#घोषणा MLX5_TRAP_DROP(_id, _group_id)					\
	DEVLINK_TRAP_GENERIC(DROP, DROP, _id,				\
			     DEVLINK_TRAP_GROUP_GENERIC_ID_##_group_id, \
			     DEVLINK_TRAP_METADATA_TYPE_F_IN_PORT)

अटल स्थिर काष्ठा devlink_trap mlx5_traps_arr[] = अणु
	MLX5_TRAP_DROP(INGRESS_VLAN_FILTER, L2_DROPS),
	MLX5_TRAP_DROP(DMAC_FILTER, L2_DROPS),
पूर्ण;

अटल स्थिर काष्ठा devlink_trap_group mlx5_trap_groups_arr[] = अणु
	DEVLINK_TRAP_GROUP_GENERIC(L2_DROPS, 0),
पूर्ण;

अटल पूर्णांक mlx5_devlink_traps_रेजिस्टर(काष्ठा devlink *devlink)
अणु
	काष्ठा mlx5_core_dev *core_dev = devlink_priv(devlink);
	पूर्णांक err;

	err = devlink_trap_groups_रेजिस्टर(devlink, mlx5_trap_groups_arr,
					   ARRAY_SIZE(mlx5_trap_groups_arr));
	अगर (err)
		वापस err;

	err = devlink_traps_रेजिस्टर(devlink, mlx5_traps_arr, ARRAY_SIZE(mlx5_traps_arr),
				     &core_dev->priv);
	अगर (err)
		जाओ err_trap_group;
	वापस 0;

err_trap_group:
	devlink_trap_groups_unरेजिस्टर(devlink, mlx5_trap_groups_arr,
				       ARRAY_SIZE(mlx5_trap_groups_arr));
	वापस err;
पूर्ण

अटल व्योम mlx5_devlink_traps_unरेजिस्टर(काष्ठा devlink *devlink)
अणु
	devlink_traps_unरेजिस्टर(devlink, mlx5_traps_arr, ARRAY_SIZE(mlx5_traps_arr));
	devlink_trap_groups_unरेजिस्टर(devlink, mlx5_trap_groups_arr,
				       ARRAY_SIZE(mlx5_trap_groups_arr));
पूर्ण

पूर्णांक mlx5_devlink_रेजिस्टर(काष्ठा devlink *devlink, काष्ठा device *dev)
अणु
	पूर्णांक err;

	err = devlink_रेजिस्टर(devlink, dev);
	अगर (err)
		वापस err;

	err = devlink_params_रेजिस्टर(devlink, mlx5_devlink_params,
				      ARRAY_SIZE(mlx5_devlink_params));
	अगर (err)
		जाओ params_reg_err;
	mlx5_devlink_set_params_init_values(devlink);
	devlink_params_publish(devlink);

	err = mlx5_devlink_traps_रेजिस्टर(devlink);
	अगर (err)
		जाओ traps_reg_err;

	वापस 0;

traps_reg_err:
	devlink_params_unरेजिस्टर(devlink, mlx5_devlink_params,
				  ARRAY_SIZE(mlx5_devlink_params));
params_reg_err:
	devlink_unरेजिस्टर(devlink);
	वापस err;
पूर्ण

व्योम mlx5_devlink_unरेजिस्टर(काष्ठा devlink *devlink)
अणु
	mlx5_devlink_traps_unरेजिस्टर(devlink);
	devlink_params_unरेजिस्टर(devlink, mlx5_devlink_params,
				  ARRAY_SIZE(mlx5_devlink_params));
	devlink_unरेजिस्टर(devlink);
पूर्ण
