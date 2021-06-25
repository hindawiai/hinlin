<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2015-2018 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_CORE_H
#घोषणा _MLXSW_CORE_H

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/gfp.h>
#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/net_namespace.h>
#समावेश <net/devlink.h>

#समावेश "trap.h"
#समावेश "reg.h"
#समावेश "cmd.h"
#समावेश "resources.h"

क्रमागत mlxsw_core_resource_id अणु
	MLXSW_CORE_RESOURCE_PORTS = 1,
	MLXSW_CORE_RESOURCE_MAX,
पूर्ण;

काष्ठा mlxsw_core;
काष्ठा mlxsw_core_port;
काष्ठा mlxsw_driver;
काष्ठा mlxsw_bus;
काष्ठा mlxsw_bus_info;
काष्ठा mlxsw_fw_rev;

अचिन्हित पूर्णांक mlxsw_core_max_ports(स्थिर काष्ठा mlxsw_core *mlxsw_core);

व्योम *mlxsw_core_driver_priv(काष्ठा mlxsw_core *mlxsw_core);

bool mlxsw_core_res_query_enabled(स्थिर काष्ठा mlxsw_core *mlxsw_core);

bool mlxsw_core_temp_warn_enabled(स्थिर काष्ठा mlxsw_core *mlxsw_core);

bool
mlxsw_core_fw_rev_minor_subminor_validate(स्थिर काष्ठा mlxsw_fw_rev *rev,
					  स्थिर काष्ठा mlxsw_fw_rev *req_rev);

पूर्णांक mlxsw_core_driver_रेजिस्टर(काष्ठा mlxsw_driver *mlxsw_driver);
व्योम mlxsw_core_driver_unरेजिस्टर(काष्ठा mlxsw_driver *mlxsw_driver);

पूर्णांक mlxsw_core_bus_device_रेजिस्टर(स्थिर काष्ठा mlxsw_bus_info *mlxsw_bus_info,
				   स्थिर काष्ठा mlxsw_bus *mlxsw_bus,
				   व्योम *bus_priv, bool reload,
				   काष्ठा devlink *devlink,
				   काष्ठा netlink_ext_ack *extack);
व्योम mlxsw_core_bus_device_unरेजिस्टर(काष्ठा mlxsw_core *mlxsw_core, bool reload);

काष्ठा mlxsw_tx_info अणु
	u8 local_port;
	bool is_emad;
पूर्ण;

काष्ठा mlxsw_rx_md_info अणु
	u32 cookie_index;
	u32 latency;
	u32 tx_congestion;
	जोड़ अणु
		/* Valid when 'tx_port_valid' is set. */
		u16 tx_sys_port;
		u16 tx_lag_id;
	पूर्ण;
	u8 tx_lag_port_index; /* Valid when 'tx_port_is_lag' is set. */
	u8 tx_tc;
	u8 latency_valid:1,
	   tx_congestion_valid:1,
	   tx_tc_valid:1,
	   tx_port_valid:1,
	   tx_port_is_lag:1,
	   unused:3;
पूर्ण;

bool mlxsw_core_skb_transmit_busy(काष्ठा mlxsw_core *mlxsw_core,
				  स्थिर काष्ठा mlxsw_tx_info *tx_info);
पूर्णांक mlxsw_core_skb_transmit(काष्ठा mlxsw_core *mlxsw_core, काष्ठा sk_buff *skb,
			    स्थिर काष्ठा mlxsw_tx_info *tx_info);
व्योम mlxsw_core_ptp_transmitted(काष्ठा mlxsw_core *mlxsw_core,
				काष्ठा sk_buff *skb, u8 local_port);

काष्ठा mlxsw_rx_listener अणु
	व्योम (*func)(काष्ठा sk_buff *skb, u8 local_port, व्योम *priv);
	u8 local_port;
	u8 mirror_reason;
	u16 trap_id;
पूर्ण;

काष्ठा mlxsw_event_listener अणु
	व्योम (*func)(स्थिर काष्ठा mlxsw_reg_info *reg,
		     अक्षर *payload, व्योम *priv);
	क्रमागत mlxsw_event_trap_id trap_id;
पूर्ण;

काष्ठा mlxsw_listener अणु
	u16 trap_id;
	जोड़ अणु
		काष्ठा mlxsw_rx_listener rx_listener;
		काष्ठा mlxsw_event_listener event_listener;
	पूर्ण;
	क्रमागत mlxsw_reg_hpkt_action en_action; /* Action when enabled */
	क्रमागत mlxsw_reg_hpkt_action dis_action; /* Action when disabled */
	u8 en_trap_group; /* Trap group when enabled */
	u8 dis_trap_group; /* Trap group when disabled */
	u8 is_ctrl:1, /* should go via control buffer or not */
	   is_event:1,
	   enabled_on_रेजिस्टर:1; /* Trap should be enabled when listener
				   * is रेजिस्टरed.
				   */
पूर्ण;

#घोषणा __MLXSW_RXL(_func, _trap_id, _en_action, _is_ctrl, _en_trap_group,	\
		    _dis_action, _enabled_on_रेजिस्टर, _dis_trap_group,		\
		    _mirror_reason)						\
	अणु									\
		.trap_id = MLXSW_TRAP_ID_##_trap_id,				\
		.rx_listener =							\
		अणु								\
			.func = _func,						\
			.local_port = MLXSW_PORT_DONT_CARE,			\
			.mirror_reason = _mirror_reason,			\
			.trap_id = MLXSW_TRAP_ID_##_trap_id,			\
		पूर्ण,								\
		.en_action = MLXSW_REG_HPKT_ACTION_##_en_action,		\
		.dis_action = MLXSW_REG_HPKT_ACTION_##_dis_action,		\
		.en_trap_group = MLXSW_REG_HTGT_TRAP_GROUP_##_en_trap_group,	\
		.dis_trap_group = MLXSW_REG_HTGT_TRAP_GROUP_##_dis_trap_group,	\
		.is_ctrl = _is_ctrl,						\
		.enabled_on_रेजिस्टर = _enabled_on_रेजिस्टर,			\
	पूर्ण

#घोषणा MLXSW_RXL(_func, _trap_id, _en_action, _is_ctrl, _trap_group,		\
		  _dis_action)							\
	__MLXSW_RXL(_func, _trap_id, _en_action, _is_ctrl, _trap_group,		\
		    _dis_action, true, _trap_group, 0)

#घोषणा MLXSW_RXL_DIS(_func, _trap_id, _en_action, _is_ctrl, _en_trap_group,	\
		      _dis_action, _dis_trap_group)				\
	__MLXSW_RXL(_func, _trap_id, _en_action, _is_ctrl, _en_trap_group,	\
		    _dis_action, false, _dis_trap_group, 0)

#घोषणा MLXSW_RXL_MIRROR(_func, _session_id, _trap_group, _mirror_reason)	\
	__MLXSW_RXL(_func, MIRROR_SESSION##_session_id,	TRAP_TO_CPU, false,	\
		    _trap_group, TRAP_TO_CPU, true, _trap_group,		\
		    _mirror_reason)

#घोषणा MLXSW_EVENTL(_func, _trap_id, _trap_group)				\
	अणु									\
		.trap_id = MLXSW_TRAP_ID_##_trap_id,				\
		.event_listener =						\
		अणु								\
			.func = _func,						\
			.trap_id = MLXSW_TRAP_ID_##_trap_id,			\
		पूर्ण,								\
		.en_action = MLXSW_REG_HPKT_ACTION_TRAP_TO_CPU,			\
		.en_trap_group = MLXSW_REG_HTGT_TRAP_GROUP_##_trap_group,	\
		.is_event = true,						\
		.enabled_on_रेजिस्टर = true,					\
	पूर्ण

पूर्णांक mlxsw_core_rx_listener_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core,
				    स्थिर काष्ठा mlxsw_rx_listener *rxl,
				    व्योम *priv, bool enabled);
व्योम mlxsw_core_rx_listener_unरेजिस्टर(काष्ठा mlxsw_core *mlxsw_core,
				       स्थिर काष्ठा mlxsw_rx_listener *rxl);

पूर्णांक mlxsw_core_event_listener_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core,
				       स्थिर काष्ठा mlxsw_event_listener *el,
				       व्योम *priv);
व्योम mlxsw_core_event_listener_unरेजिस्टर(काष्ठा mlxsw_core *mlxsw_core,
					  स्थिर काष्ठा mlxsw_event_listener *el);

पूर्णांक mlxsw_core_trap_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core,
			     स्थिर काष्ठा mlxsw_listener *listener,
			     व्योम *priv);
व्योम mlxsw_core_trap_unरेजिस्टर(काष्ठा mlxsw_core *mlxsw_core,
				स्थिर काष्ठा mlxsw_listener *listener,
				व्योम *priv);
पूर्णांक mlxsw_core_trap_state_set(काष्ठा mlxsw_core *mlxsw_core,
			      स्थिर काष्ठा mlxsw_listener *listener,
			      bool enabled);

प्रकार व्योम mlxsw_reg_trans_cb_t(काष्ठा mlxsw_core *mlxsw_core, अक्षर *payload,
				  माप_प्रकार payload_len, अचिन्हित दीर्घ cb_priv);

पूर्णांक mlxsw_reg_trans_query(काष्ठा mlxsw_core *mlxsw_core,
			  स्थिर काष्ठा mlxsw_reg_info *reg, अक्षर *payload,
			  काष्ठा list_head *bulk_list,
			  mlxsw_reg_trans_cb_t *cb, अचिन्हित दीर्घ cb_priv);
पूर्णांक mlxsw_reg_trans_ग_लिखो(काष्ठा mlxsw_core *mlxsw_core,
			  स्थिर काष्ठा mlxsw_reg_info *reg, अक्षर *payload,
			  काष्ठा list_head *bulk_list,
			  mlxsw_reg_trans_cb_t *cb, अचिन्हित दीर्घ cb_priv);
पूर्णांक mlxsw_reg_trans_bulk_रुको(काष्ठा list_head *bulk_list);

पूर्णांक mlxsw_reg_query(काष्ठा mlxsw_core *mlxsw_core,
		    स्थिर काष्ठा mlxsw_reg_info *reg, अक्षर *payload);
पूर्णांक mlxsw_reg_ग_लिखो(काष्ठा mlxsw_core *mlxsw_core,
		    स्थिर काष्ठा mlxsw_reg_info *reg, अक्षर *payload);

काष्ठा mlxsw_rx_info अणु
	bool is_lag;
	जोड़ अणु
		u16 sys_port;
		u16 lag_id;
	पूर्ण u;
	u8 lag_port_index;
	u8 mirror_reason;
	पूर्णांक trap_id;
पूर्ण;

व्योम mlxsw_core_skb_receive(काष्ठा mlxsw_core *mlxsw_core, काष्ठा sk_buff *skb,
			    काष्ठा mlxsw_rx_info *rx_info);

व्योम mlxsw_core_lag_mapping_set(काष्ठा mlxsw_core *mlxsw_core,
				u16 lag_id, u8 port_index, u8 local_port);
u8 mlxsw_core_lag_mapping_get(काष्ठा mlxsw_core *mlxsw_core,
			      u16 lag_id, u8 port_index);
व्योम mlxsw_core_lag_mapping_clear(काष्ठा mlxsw_core *mlxsw_core,
				  u16 lag_id, u8 local_port);

व्योम *mlxsw_core_port_driver_priv(काष्ठा mlxsw_core_port *mlxsw_core_port);
पूर्णांक mlxsw_core_port_init(काष्ठा mlxsw_core *mlxsw_core, u8 local_port,
			 u32 port_number, bool split, u32 split_port_subnumber,
			 bool splittable, u32 lanes,
			 स्थिर अचिन्हित अक्षर *चयन_id,
			 अचिन्हित अक्षर चयन_id_len);
व्योम mlxsw_core_port_fini(काष्ठा mlxsw_core *mlxsw_core, u8 local_port);
पूर्णांक mlxsw_core_cpu_port_init(काष्ठा mlxsw_core *mlxsw_core,
			     व्योम *port_driver_priv,
			     स्थिर अचिन्हित अक्षर *चयन_id,
			     अचिन्हित अक्षर चयन_id_len);
व्योम mlxsw_core_cpu_port_fini(काष्ठा mlxsw_core *mlxsw_core);
व्योम mlxsw_core_port_eth_set(काष्ठा mlxsw_core *mlxsw_core, u8 local_port,
			     व्योम *port_driver_priv, काष्ठा net_device *dev);
व्योम mlxsw_core_port_ib_set(काष्ठा mlxsw_core *mlxsw_core, u8 local_port,
			    व्योम *port_driver_priv);
व्योम mlxsw_core_port_clear(काष्ठा mlxsw_core *mlxsw_core, u8 local_port,
			   व्योम *port_driver_priv);
क्रमागत devlink_port_type mlxsw_core_port_type_get(काष्ठा mlxsw_core *mlxsw_core,
						u8 local_port);
काष्ठा devlink_port *
mlxsw_core_port_devlink_port_get(काष्ठा mlxsw_core *mlxsw_core,
				 u8 local_port);
bool mlxsw_core_port_is_xm(स्थिर काष्ठा mlxsw_core *mlxsw_core, u8 local_port);
काष्ठा mlxsw_env *mlxsw_core_env(स्थिर काष्ठा mlxsw_core *mlxsw_core);
bool mlxsw_core_is_initialized(स्थिर काष्ठा mlxsw_core *mlxsw_core);
पूर्णांक mlxsw_core_module_max_width(काष्ठा mlxsw_core *mlxsw_core, u8 module);

पूर्णांक mlxsw_core_schedule_dw(काष्ठा delayed_work *dwork, अचिन्हित दीर्घ delay);
bool mlxsw_core_schedule_work(काष्ठा work_काष्ठा *work);
व्योम mlxsw_core_flush_owq(व्योम);
पूर्णांक mlxsw_core_resources_query(काष्ठा mlxsw_core *mlxsw_core, अक्षर *mbox,
			       काष्ठा mlxsw_res *res);

#घोषणा MLXSW_CONFIG_PROखाता_SWID_COUNT 8

काष्ठा mlxsw_swid_config अणु
	u8	used_type:1,
		used_properties:1;
	u8	type;
	u8	properties;
पूर्ण;

काष्ठा mlxsw_config_profile अणु
	u16	used_max_vepa_channels:1,
		used_max_mid:1,
		used_max_pgt:1,
		used_max_प्रणाली_port:1,
		used_max_vlan_groups:1,
		used_max_regions:1,
		used_flood_tables:1,
		used_flood_mode:1,
		used_max_ib_mc:1,
		used_max_pkey:1,
		used_ar_sec:1,
		used_adaptive_routing_group_cap:1,
		used_kvd_sizes:1,
		used_kvh_xlt_cache_mode:1;
	u8	max_vepa_channels;
	u16	max_mid;
	u16	max_pgt;
	u16	max_प्रणाली_port;
	u16	max_vlan_groups;
	u16	max_regions;
	u8	max_flood_tables;
	u8	max_vid_flood_tables;
	u8	flood_mode;
	u8	max_fid_offset_flood_tables;
	u16	fid_offset_flood_table_size;
	u8	max_fid_flood_tables;
	u16	fid_flood_table_size;
	u16	max_ib_mc;
	u16	max_pkey;
	u8	ar_sec;
	u16	adaptive_routing_group_cap;
	u8	arn;
	u32	kvd_linear_size;
	u8	kvd_hash_single_parts;
	u8	kvd_hash_द्विगुन_parts;
	u8	kvh_xlt_cache_mode;
	काष्ठा mlxsw_swid_config swid_config[MLXSW_CONFIG_PROखाता_SWID_COUNT];
पूर्ण;

काष्ठा mlxsw_driver अणु
	काष्ठा list_head list;
	स्थिर अक्षर *kind;
	माप_प्रकार priv_size;
	स्थिर काष्ठा mlxsw_fw_rev *fw_req_rev;
	स्थिर अक्षर *fw_filename;
	पूर्णांक (*init)(काष्ठा mlxsw_core *mlxsw_core,
		    स्थिर काष्ठा mlxsw_bus_info *mlxsw_bus_info,
		    काष्ठा netlink_ext_ack *extack);
	व्योम (*fini)(काष्ठा mlxsw_core *mlxsw_core);
	पूर्णांक (*basic_trap_groups_set)(काष्ठा mlxsw_core *mlxsw_core);
	पूर्णांक (*port_type_set)(काष्ठा mlxsw_core *mlxsw_core, u8 local_port,
			     क्रमागत devlink_port_type new_type);
	पूर्णांक (*port_split)(काष्ठा mlxsw_core *mlxsw_core, u8 local_port,
			  अचिन्हित पूर्णांक count, काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*port_unsplit)(काष्ठा mlxsw_core *mlxsw_core, u8 local_port,
			    काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*sb_pool_get)(काष्ठा mlxsw_core *mlxsw_core,
			   अचिन्हित पूर्णांक sb_index, u16 pool_index,
			   काष्ठा devlink_sb_pool_info *pool_info);
	पूर्णांक (*sb_pool_set)(काष्ठा mlxsw_core *mlxsw_core,
			   अचिन्हित पूर्णांक sb_index, u16 pool_index, u32 size,
			   क्रमागत devlink_sb_threshold_type threshold_type,
			   काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*sb_port_pool_get)(काष्ठा mlxsw_core_port *mlxsw_core_port,
				अचिन्हित पूर्णांक sb_index, u16 pool_index,
				u32 *p_threshold);
	पूर्णांक (*sb_port_pool_set)(काष्ठा mlxsw_core_port *mlxsw_core_port,
				अचिन्हित पूर्णांक sb_index, u16 pool_index,
				u32 threshold, काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*sb_tc_pool_bind_get)(काष्ठा mlxsw_core_port *mlxsw_core_port,
				   अचिन्हित पूर्णांक sb_index, u16 tc_index,
				   क्रमागत devlink_sb_pool_type pool_type,
				   u16 *p_pool_index, u32 *p_threshold);
	पूर्णांक (*sb_tc_pool_bind_set)(काष्ठा mlxsw_core_port *mlxsw_core_port,
				   अचिन्हित पूर्णांक sb_index, u16 tc_index,
				   क्रमागत devlink_sb_pool_type pool_type,
				   u16 pool_index, u32 threshold,
				   काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*sb_occ_snapshot)(काष्ठा mlxsw_core *mlxsw_core,
			       अचिन्हित पूर्णांक sb_index);
	पूर्णांक (*sb_occ_max_clear)(काष्ठा mlxsw_core *mlxsw_core,
				अचिन्हित पूर्णांक sb_index);
	पूर्णांक (*sb_occ_port_pool_get)(काष्ठा mlxsw_core_port *mlxsw_core_port,
				    अचिन्हित पूर्णांक sb_index, u16 pool_index,
				    u32 *p_cur, u32 *p_max);
	पूर्णांक (*sb_occ_tc_port_bind_get)(काष्ठा mlxsw_core_port *mlxsw_core_port,
				       अचिन्हित पूर्णांक sb_index, u16 tc_index,
				       क्रमागत devlink_sb_pool_type pool_type,
				       u32 *p_cur, u32 *p_max);
	पूर्णांक (*trap_init)(काष्ठा mlxsw_core *mlxsw_core,
			 स्थिर काष्ठा devlink_trap *trap, व्योम *trap_ctx);
	व्योम (*trap_fini)(काष्ठा mlxsw_core *mlxsw_core,
			  स्थिर काष्ठा devlink_trap *trap, व्योम *trap_ctx);
	पूर्णांक (*trap_action_set)(काष्ठा mlxsw_core *mlxsw_core,
			       स्थिर काष्ठा devlink_trap *trap,
			       क्रमागत devlink_trap_action action,
			       काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*trap_group_init)(काष्ठा mlxsw_core *mlxsw_core,
			       स्थिर काष्ठा devlink_trap_group *group);
	पूर्णांक (*trap_group_set)(काष्ठा mlxsw_core *mlxsw_core,
			      स्थिर काष्ठा devlink_trap_group *group,
			      स्थिर काष्ठा devlink_trap_policer *policer,
			      काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*trap_policer_init)(काष्ठा mlxsw_core *mlxsw_core,
				 स्थिर काष्ठा devlink_trap_policer *policer);
	व्योम (*trap_policer_fini)(काष्ठा mlxsw_core *mlxsw_core,
				  स्थिर काष्ठा devlink_trap_policer *policer);
	पूर्णांक (*trap_policer_set)(काष्ठा mlxsw_core *mlxsw_core,
				स्थिर काष्ठा devlink_trap_policer *policer,
				u64 rate, u64 burst,
				काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*trap_policer_counter_get)(काष्ठा mlxsw_core *mlxsw_core,
					स्थिर काष्ठा devlink_trap_policer *policer,
					u64 *p_drops);
	व्योम (*txhdr_स्थिरruct)(काष्ठा sk_buff *skb,
				स्थिर काष्ठा mlxsw_tx_info *tx_info);
	पूर्णांक (*resources_रेजिस्टर)(काष्ठा mlxsw_core *mlxsw_core);
	पूर्णांक (*kvd_sizes_get)(काष्ठा mlxsw_core *mlxsw_core,
			     स्थिर काष्ठा mlxsw_config_profile *profile,
			     u64 *p_single_size, u64 *p_द्विगुन_size,
			     u64 *p_linear_size);
	पूर्णांक (*params_रेजिस्टर)(काष्ठा mlxsw_core *mlxsw_core);
	व्योम (*params_unरेजिस्टर)(काष्ठा mlxsw_core *mlxsw_core);

	/* Notअगरy a driver that a बारtamped packet was transmitted. Driver
	 * is responsible क्रम मुक्तing the passed-in SKB.
	 */
	व्योम (*ptp_transmitted)(काष्ठा mlxsw_core *mlxsw_core,
				काष्ठा sk_buff *skb, u8 local_port);

	u8 txhdr_len;
	स्थिर काष्ठा mlxsw_config_profile *profile;
	bool res_query_enabled;
	bool fw_fatal_enabled;
	bool temp_warn_enabled;
पूर्ण;

पूर्णांक mlxsw_core_kvd_sizes_get(काष्ठा mlxsw_core *mlxsw_core,
			     स्थिर काष्ठा mlxsw_config_profile *profile,
			     u64 *p_single_size, u64 *p_द्विगुन_size,
			     u64 *p_linear_size);

u32 mlxsw_core_पढ़ो_frc_h(काष्ठा mlxsw_core *mlxsw_core);
u32 mlxsw_core_पढ़ो_frc_l(काष्ठा mlxsw_core *mlxsw_core);

व्योम mlxsw_core_emad_string_tlv_enable(काष्ठा mlxsw_core *mlxsw_core);

bool mlxsw_core_res_valid(काष्ठा mlxsw_core *mlxsw_core,
			  क्रमागत mlxsw_res_id res_id);

#घोषणा MLXSW_CORE_RES_VALID(mlxsw_core, लघु_res_id)			\
	mlxsw_core_res_valid(mlxsw_core, MLXSW_RES_ID_##लघु_res_id)

u64 mlxsw_core_res_get(काष्ठा mlxsw_core *mlxsw_core,
		       क्रमागत mlxsw_res_id res_id);

#घोषणा MLXSW_CORE_RES_GET(mlxsw_core, लघु_res_id)			\
	mlxsw_core_res_get(mlxsw_core, MLXSW_RES_ID_##लघु_res_id)

अटल अंतरभूत काष्ठा net *mlxsw_core_net(काष्ठा mlxsw_core *mlxsw_core)
अणु
	वापस devlink_net(priv_to_devlink(mlxsw_core));
पूर्ण

#घोषणा MLXSW_BUS_F_TXRX	BIT(0)
#घोषणा MLXSW_BUS_F_RESET	BIT(1)

काष्ठा mlxsw_bus अणु
	स्थिर अक्षर *kind;
	पूर्णांक (*init)(व्योम *bus_priv, काष्ठा mlxsw_core *mlxsw_core,
		    स्थिर काष्ठा mlxsw_config_profile *profile,
		    काष्ठा mlxsw_res *res);
	व्योम (*fini)(व्योम *bus_priv);
	bool (*skb_transmit_busy)(व्योम *bus_priv,
				  स्थिर काष्ठा mlxsw_tx_info *tx_info);
	पूर्णांक (*skb_transmit)(व्योम *bus_priv, काष्ठा sk_buff *skb,
			    स्थिर काष्ठा mlxsw_tx_info *tx_info);
	पूर्णांक (*cmd_exec)(व्योम *bus_priv, u16 opcode, u8 opcode_mod,
			u32 in_mod, bool out_mbox_direct,
			अक्षर *in_mbox, माप_प्रकार in_mbox_size,
			अक्षर *out_mbox, माप_प्रकार out_mbox_size,
			u8 *p_status);
	u32 (*पढ़ो_frc_h)(व्योम *bus_priv);
	u32 (*पढ़ो_frc_l)(व्योम *bus_priv);
	u8 features;
पूर्ण;

काष्ठा mlxsw_fw_rev अणु
	u16 major;
	u16 minor;
	u16 subminor;
	u16 can_reset_minor;
पूर्ण;

#घोषणा MLXSW_BUS_INFO_XM_LOCAL_PORTS_MAX 4

काष्ठा mlxsw_bus_info अणु
	स्थिर अक्षर *device_kind;
	स्थिर अक्षर *device_name;
	काष्ठा device *dev;
	काष्ठा mlxsw_fw_rev fw_rev;
	u8 vsd[MLXSW_CMD_BOARDINFO_VSD_LEN];
	u8 psid[MLXSW_CMD_BOARDINFO_PSID_LEN];
	u8 low_frequency:1,
	   पढ़ो_frc_capable:1,
	   xm_exists:1;
	u8 xm_local_ports_count;
	u8 xm_local_ports[MLXSW_BUS_INFO_XM_LOCAL_PORTS_MAX];
पूर्ण;

काष्ठा mlxsw_hwmon;

#अगर_घोषित CONFIG_MLXSW_CORE_HWMON

पूर्णांक mlxsw_hwmon_init(काष्ठा mlxsw_core *mlxsw_core,
		     स्थिर काष्ठा mlxsw_bus_info *mlxsw_bus_info,
		     काष्ठा mlxsw_hwmon **p_hwmon);
व्योम mlxsw_hwmon_fini(काष्ठा mlxsw_hwmon *mlxsw_hwmon);

#अन्यथा

अटल अंतरभूत पूर्णांक mlxsw_hwmon_init(काष्ठा mlxsw_core *mlxsw_core,
				   स्थिर काष्ठा mlxsw_bus_info *mlxsw_bus_info,
				   काष्ठा mlxsw_hwmon **p_hwmon)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mlxsw_hwmon_fini(काष्ठा mlxsw_hwmon *mlxsw_hwmon)
अणु
पूर्ण

#पूर्ण_अगर

काष्ठा mlxsw_thermal;

#अगर_घोषित CONFIG_MLXSW_CORE_THERMAL

पूर्णांक mlxsw_thermal_init(काष्ठा mlxsw_core *mlxsw_core,
		       स्थिर काष्ठा mlxsw_bus_info *mlxsw_bus_info,
		       काष्ठा mlxsw_thermal **p_thermal);
व्योम mlxsw_thermal_fini(काष्ठा mlxsw_thermal *thermal);

#अन्यथा

अटल अंतरभूत पूर्णांक mlxsw_thermal_init(काष्ठा mlxsw_core *mlxsw_core,
				     स्थिर काष्ठा mlxsw_bus_info *mlxsw_bus_info,
				     काष्ठा mlxsw_thermal **p_thermal)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mlxsw_thermal_fini(काष्ठा mlxsw_thermal *thermal)
अणु
पूर्ण

#पूर्ण_अगर

क्रमागत mlxsw_devlink_param_id अणु
	MLXSW_DEVLINK_PARAM_ID_BASE = DEVLINK_PARAM_GENERIC_ID_MAX,
	MLXSW_DEVLINK_PARAM_ID_ACL_REGION_REHASH_INTERVAL,
पूर्ण;

काष्ठा mlxsw_skb_cb अणु
	जोड़ अणु
		काष्ठा mlxsw_tx_info tx_info;
		काष्ठा mlxsw_rx_md_info rx_md_info;
	पूर्ण;
पूर्ण;

अटल अंतरभूत काष्ठा mlxsw_skb_cb *mlxsw_skb_cb(काष्ठा sk_buff *skb)
अणु
	BUILD_BUG_ON(माप(mlxsw_skb_cb) > माप(skb->cb));
	वापस (काष्ठा mlxsw_skb_cb *) skb->cb;
पूर्ण

#पूर्ण_अगर
