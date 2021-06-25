<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
#समावेश "dpaa2-eth.h"
/* Copyright 2020 NXP
 */

#घोषणा DPAA2_ETH_TRAP_DROP(_id, _group_id)					\
	DEVLINK_TRAP_GENERIC(DROP, DROP, _id,					\
			     DEVLINK_TRAP_GROUP_GENERIC_ID_##_group_id, 0)

अटल स्थिर काष्ठा devlink_trap_group dpaa2_eth_trap_groups_arr[] = अणु
	DEVLINK_TRAP_GROUP_GENERIC(PARSER_ERROR_DROPS, 0),
पूर्ण;

अटल स्थिर काष्ठा devlink_trap dpaa2_eth_traps_arr[] = अणु
	DPAA2_ETH_TRAP_DROP(VXLAN_PARSING, PARSER_ERROR_DROPS),
	DPAA2_ETH_TRAP_DROP(LLC_SNAP_PARSING, PARSER_ERROR_DROPS),
	DPAA2_ETH_TRAP_DROP(VLAN_PARSING, PARSER_ERROR_DROPS),
	DPAA2_ETH_TRAP_DROP(PPPOE_PPP_PARSING, PARSER_ERROR_DROPS),
	DPAA2_ETH_TRAP_DROP(MPLS_PARSING, PARSER_ERROR_DROPS),
	DPAA2_ETH_TRAP_DROP(ARP_PARSING, PARSER_ERROR_DROPS),
	DPAA2_ETH_TRAP_DROP(IP_1_PARSING, PARSER_ERROR_DROPS),
	DPAA2_ETH_TRAP_DROP(IP_N_PARSING, PARSER_ERROR_DROPS),
	DPAA2_ETH_TRAP_DROP(GRE_PARSING, PARSER_ERROR_DROPS),
	DPAA2_ETH_TRAP_DROP(UDP_PARSING, PARSER_ERROR_DROPS),
	DPAA2_ETH_TRAP_DROP(TCP_PARSING, PARSER_ERROR_DROPS),
	DPAA2_ETH_TRAP_DROP(IPSEC_PARSING, PARSER_ERROR_DROPS),
	DPAA2_ETH_TRAP_DROP(SCTP_PARSING, PARSER_ERROR_DROPS),
	DPAA2_ETH_TRAP_DROP(DCCP_PARSING, PARSER_ERROR_DROPS),
	DPAA2_ETH_TRAP_DROP(GTP_PARSING, PARSER_ERROR_DROPS),
	DPAA2_ETH_TRAP_DROP(ESP_PARSING, PARSER_ERROR_DROPS),
पूर्ण;

अटल पूर्णांक dpaa2_eth_dl_info_get(काष्ठा devlink *devlink,
				 काष्ठा devlink_info_req *req,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dpaa2_eth_devlink_priv *dl_priv = devlink_priv(devlink);
	काष्ठा dpaa2_eth_priv *priv = dl_priv->dpaa2_priv;
	अक्षर buf[10];
	पूर्णांक err;

	err = devlink_info_driver_name_put(req, KBUILD_MODNAME);
	अगर (err)
		वापस err;

	scnम_लिखो(buf, 10, "%d.%d", priv->dpni_ver_major, priv->dpni_ver_minor);
	err = devlink_info_version_running_put(req, "dpni", buf);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल काष्ठा dpaa2_eth_trap_item *
dpaa2_eth_dl_trap_item_lookup(काष्ठा dpaa2_eth_priv *priv, u16 trap_id)
अणु
	काष्ठा dpaa2_eth_trap_data *dpaa2_eth_trap_data = priv->trap_data;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dpaa2_eth_traps_arr); i++) अणु
		अगर (dpaa2_eth_traps_arr[i].id == trap_id)
			वापस &dpaa2_eth_trap_data->trap_items_arr[i];
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा dpaa2_eth_trap_item *dpaa2_eth_dl_get_trap(काष्ठा dpaa2_eth_priv *priv,
						  काष्ठा dpaa2_fapr *fapr)
अणु
	काष्ठा dpaa2_faf_error_bit अणु
		पूर्णांक position;
		क्रमागत devlink_trap_generic_id trap_id;
	पूर्ण faf_bits[] = अणु
		अणु .position = 5,  .trap_id = DEVLINK_TRAP_GENERIC_ID_VXLAN_PARSING पूर्ण,
		अणु .position = 20, .trap_id = DEVLINK_TRAP_GENERIC_ID_LLC_SNAP_PARSING पूर्ण,
		अणु .position = 24, .trap_id = DEVLINK_TRAP_GENERIC_ID_VLAN_PARSING पूर्ण,
		अणु .position = 26, .trap_id = DEVLINK_TRAP_GENERIC_ID_PPPOE_PPP_PARSING पूर्ण,
		अणु .position = 29, .trap_id = DEVLINK_TRAP_GENERIC_ID_MPLS_PARSING पूर्ण,
		अणु .position = 31, .trap_id = DEVLINK_TRAP_GENERIC_ID_ARP_PARSING पूर्ण,
		अणु .position = 52, .trap_id = DEVLINK_TRAP_GENERIC_ID_IP_1_PARSING पूर्ण,
		अणु .position = 61, .trap_id = DEVLINK_TRAP_GENERIC_ID_IP_N_PARSING पूर्ण,
		अणु .position = 67, .trap_id = DEVLINK_TRAP_GENERIC_ID_GRE_PARSING पूर्ण,
		अणु .position = 71, .trap_id = DEVLINK_TRAP_GENERIC_ID_UDP_PARSING पूर्ण,
		अणु .position = 76, .trap_id = DEVLINK_TRAP_GENERIC_ID_TCP_PARSING पूर्ण,
		अणु .position = 80, .trap_id = DEVLINK_TRAP_GENERIC_ID_IPSEC_PARSING पूर्ण,
		अणु .position = 82, .trap_id = DEVLINK_TRAP_GENERIC_ID_SCTP_PARSING पूर्ण,
		अणु .position = 84, .trap_id = DEVLINK_TRAP_GENERIC_ID_DCCP_PARSING पूर्ण,
		अणु .position = 88, .trap_id = DEVLINK_TRAP_GENERIC_ID_GTP_PARSING पूर्ण,
		अणु .position = 90, .trap_id = DEVLINK_TRAP_GENERIC_ID_ESP_PARSING पूर्ण,
	पूर्ण;
	u64 faf_word;
	u64 mask;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(faf_bits); i++) अणु
		अगर (faf_bits[i].position < 32) अणु
			/* Low part of FAF.
			 * position ranges from 31 to 0, mask from 0 to 31.
			 */
			mask = 1ull << (31 - faf_bits[i].position);
			faf_word = __le32_to_cpu(fapr->faf_lo);
		पूर्ण अन्यथा अणु
			/* High part of FAF.
			 * position ranges from 95 to 32, mask from 0 to 63.
			 */
			mask = 1ull << (63 - (faf_bits[i].position - 32));
			faf_word = __le64_to_cpu(fapr->faf_hi);
		पूर्ण
		अगर (faf_word & mask)
			वापस dpaa2_eth_dl_trap_item_lookup(priv, faf_bits[i].trap_id);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक dpaa2_eth_dl_trap_init(काष्ठा devlink *devlink,
				  स्थिर काष्ठा devlink_trap *trap,
				  व्योम *trap_ctx)
अणु
	काष्ठा dpaa2_eth_devlink_priv *dl_priv = devlink_priv(devlink);
	काष्ठा dpaa2_eth_priv *priv = dl_priv->dpaa2_priv;
	काष्ठा dpaa2_eth_trap_item *dpaa2_eth_trap_item;

	dpaa2_eth_trap_item = dpaa2_eth_dl_trap_item_lookup(priv, trap->id);
	अगर (WARN_ON(!dpaa2_eth_trap_item))
		वापस -ENOENT;

	dpaa2_eth_trap_item->trap_ctx = trap_ctx;

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_dl_trap_action_set(काष्ठा devlink *devlink,
					स्थिर काष्ठा devlink_trap *trap,
					क्रमागत devlink_trap_action action,
					काष्ठा netlink_ext_ack *extack)
अणु
	/* No support क्रम changing the action of an independent packet trap,
	 * only per trap group - parser error drops
	 */
	NL_SET_ERR_MSG_MOD(extack,
			   "Cannot change trap action independently of group");
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक dpaa2_eth_dl_trap_group_action_set(काष्ठा devlink *devlink,
					      स्थिर काष्ठा devlink_trap_group *group,
					      क्रमागत devlink_trap_action action,
					      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dpaa2_eth_devlink_priv *dl_priv = devlink_priv(devlink);
	काष्ठा dpaa2_eth_priv *priv = dl_priv->dpaa2_priv;
	काष्ठा net_device *net_dev = priv->net_dev;
	काष्ठा device *dev = net_dev->dev.parent;
	काष्ठा dpni_error_cfg err_cfg = अणु0पूर्ण;
	पूर्णांक err;

	अगर (group->id != DEVLINK_TRAP_GROUP_GENERIC_ID_PARSER_ERROR_DROPS)
		वापस -EOPNOTSUPP;

	/* Configure handling of frames marked as errors from the parser */
	err_cfg.errors = DPAA2_FAS_RX_ERR_MASK;
	err_cfg.set_frame_annotation = 1;

	चयन (action) अणु
	हाल DEVLINK_TRAP_ACTION_DROP:
		err_cfg.error_action = DPNI_ERROR_ACTION_DISCARD;
		अवरोध;
	हाल DEVLINK_TRAP_ACTION_TRAP:
		err_cfg.error_action = DPNI_ERROR_ACTION_SEND_TO_ERROR_QUEUE;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	err = dpni_set_errors_behavior(priv->mc_io, 0, priv->mc_token, &err_cfg);
	अगर (err) अणु
		dev_err(dev, "dpni_set_errors_behavior failed\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा devlink_ops dpaa2_eth_devlink_ops = अणु
	.info_get = dpaa2_eth_dl_info_get,
	.trap_init = dpaa2_eth_dl_trap_init,
	.trap_action_set = dpaa2_eth_dl_trap_action_set,
	.trap_group_action_set = dpaa2_eth_dl_trap_group_action_set,
पूर्ण;

पूर्णांक dpaa2_eth_dl_रेजिस्टर(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा net_device *net_dev = priv->net_dev;
	काष्ठा device *dev = net_dev->dev.parent;
	काष्ठा dpaa2_eth_devlink_priv *dl_priv;
	पूर्णांक err;

	priv->devlink = devlink_alloc(&dpaa2_eth_devlink_ops, माप(*dl_priv));
	अगर (!priv->devlink) अणु
		dev_err(dev, "devlink_alloc failed\n");
		वापस -ENOMEM;
	पूर्ण
	dl_priv = devlink_priv(priv->devlink);
	dl_priv->dpaa2_priv = priv;

	err = devlink_रेजिस्टर(priv->devlink, dev);
	अगर (err) अणु
		dev_err(dev, "devlink_register() = %d\n", err);
		जाओ devlink_मुक्त;
	पूर्ण

	वापस 0;

devlink_मुक्त:
	devlink_मुक्त(priv->devlink);

	वापस err;
पूर्ण

व्योम dpaa2_eth_dl_unरेजिस्टर(काष्ठा dpaa2_eth_priv *priv)
अणु
	devlink_unरेजिस्टर(priv->devlink);
	devlink_मुक्त(priv->devlink);
पूर्ण

पूर्णांक dpaa2_eth_dl_port_add(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा devlink_port *devlink_port = &priv->devlink_port;
	काष्ठा devlink_port_attrs attrs = अणुपूर्ण;
	पूर्णांक err;

	attrs.flavour = DEVLINK_PORT_FLAVOUR_PHYSICAL;
	devlink_port_attrs_set(devlink_port, &attrs);

	err = devlink_port_रेजिस्टर(priv->devlink, devlink_port, 0);
	अगर (err)
		वापस err;

	devlink_port_type_eth_set(devlink_port, priv->net_dev);

	वापस 0;
पूर्ण

व्योम dpaa2_eth_dl_port_del(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा devlink_port *devlink_port = &priv->devlink_port;

	devlink_port_type_clear(devlink_port);
	devlink_port_unरेजिस्टर(devlink_port);
पूर्ण

पूर्णांक dpaa2_eth_dl_traps_रेजिस्टर(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा dpaa2_eth_trap_data *dpaa2_eth_trap_data;
	काष्ठा net_device *net_dev = priv->net_dev;
	काष्ठा device *dev = net_dev->dev.parent;
	पूर्णांक err;

	dpaa2_eth_trap_data = kzalloc(माप(*dpaa2_eth_trap_data), GFP_KERNEL);
	अगर (!dpaa2_eth_trap_data)
		वापस -ENOMEM;
	priv->trap_data = dpaa2_eth_trap_data;

	dpaa2_eth_trap_data->trap_items_arr = kसुस्मृति(ARRAY_SIZE(dpaa2_eth_traps_arr),
						      माप(काष्ठा dpaa2_eth_trap_item),
						      GFP_KERNEL);
	अगर (!dpaa2_eth_trap_data->trap_items_arr) अणु
		err = -ENOMEM;
		जाओ trap_data_मुक्त;
	पूर्ण

	err = devlink_trap_groups_रेजिस्टर(priv->devlink, dpaa2_eth_trap_groups_arr,
					   ARRAY_SIZE(dpaa2_eth_trap_groups_arr));
	अगर (err) अणु
		dev_err(dev, "devlink_trap_groups_register() = %d\n", err);
		जाओ trap_items_arr_मुक्त;
	पूर्ण

	err = devlink_traps_रेजिस्टर(priv->devlink, dpaa2_eth_traps_arr,
				     ARRAY_SIZE(dpaa2_eth_traps_arr), priv);
	अगर (err) अणु
		dev_err(dev, "devlink_traps_register() = %d\n", err);
		जाओ trap_groups_unregiser;
	पूर्ण

	वापस 0;

trap_groups_unregiser:
	devlink_trap_groups_unरेजिस्टर(priv->devlink, dpaa2_eth_trap_groups_arr,
				       ARRAY_SIZE(dpaa2_eth_trap_groups_arr));
trap_items_arr_मुक्त:
	kमुक्त(dpaa2_eth_trap_data->trap_items_arr);
trap_data_मुक्त:
	kमुक्त(dpaa2_eth_trap_data);
	priv->trap_data = शून्य;

	वापस err;
पूर्ण

व्योम dpaa2_eth_dl_traps_unरेजिस्टर(काष्ठा dpaa2_eth_priv *priv)
अणु
	devlink_traps_unरेजिस्टर(priv->devlink, dpaa2_eth_traps_arr,
				 ARRAY_SIZE(dpaa2_eth_traps_arr));
	devlink_trap_groups_unरेजिस्टर(priv->devlink, dpaa2_eth_trap_groups_arr,
				       ARRAY_SIZE(dpaa2_eth_trap_groups_arr));
	kमुक्त(priv->trap_data->trap_items_arr);
	kमुक्त(priv->trap_data);
पूर्ण
