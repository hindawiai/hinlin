<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2015-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/err.h>
#समावेश <linux/अगर_link.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/completion.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/gfp.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/firmware.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <net/devlink.h>
#समावेश <trace/events/devlink.h>

#समावेश "core.h"
#समावेश "core_env.h"
#समावेश "item.h"
#समावेश "cmd.h"
#समावेश "port.h"
#समावेश "trap.h"
#समावेश "emad.h"
#समावेश "reg.h"
#समावेश "resources.h"
#समावेश "../mlxfw/mlxfw.h"

अटल LIST_HEAD(mlxsw_core_driver_list);
अटल DEFINE_SPINLOCK(mlxsw_core_driver_list_lock);

अटल स्थिर अक्षर mlxsw_core_driver_name[] = "mlxsw_core";

अटल काष्ठा workqueue_काष्ठा *mlxsw_wq;
अटल काष्ठा workqueue_काष्ठा *mlxsw_owq;

काष्ठा mlxsw_core_port अणु
	काष्ठा devlink_port devlink_port;
	व्योम *port_driver_priv;
	u8 local_port;
पूर्ण;

व्योम *mlxsw_core_port_driver_priv(काष्ठा mlxsw_core_port *mlxsw_core_port)
अणु
	वापस mlxsw_core_port->port_driver_priv;
पूर्ण
EXPORT_SYMBOL(mlxsw_core_port_driver_priv);

अटल bool mlxsw_core_port_check(काष्ठा mlxsw_core_port *mlxsw_core_port)
अणु
	वापस mlxsw_core_port->port_driver_priv != शून्य;
पूर्ण

काष्ठा mlxsw_core अणु
	काष्ठा mlxsw_driver *driver;
	स्थिर काष्ठा mlxsw_bus *bus;
	व्योम *bus_priv;
	स्थिर काष्ठा mlxsw_bus_info *bus_info;
	काष्ठा workqueue_काष्ठा *emad_wq;
	काष्ठा list_head rx_listener_list;
	काष्ठा list_head event_listener_list;
	काष्ठा अणु
		atomic64_t tid;
		काष्ठा list_head trans_list;
		spinlock_t trans_list_lock; /* protects trans_list ग_लिखोs */
		bool use_emad;
		bool enable_string_tlv;
	पूर्ण emad;
	काष्ठा अणु
		u8 *mapping; /* lag_id+port_index to local_port mapping */
	पूर्ण lag;
	काष्ठा mlxsw_res res;
	काष्ठा mlxsw_hwmon *hwmon;
	काष्ठा mlxsw_thermal *thermal;
	काष्ठा mlxsw_core_port *ports;
	अचिन्हित पूर्णांक max_ports;
	atomic_t active_ports_count;
	bool fw_flash_in_progress;
	काष्ठा अणु
		काष्ठा devlink_health_reporter *fw_fatal;
	पूर्ण health;
	काष्ठा mlxsw_env *env;
	bool is_initialized; /* Denotes अगर core was alपढ़ोy initialized. */
	अचिन्हित दीर्घ driver_priv[];
	/* driver_priv has to be always the last item */
पूर्ण;

#घोषणा MLXSW_PORT_MAX_PORTS_DEFAULT	0x40

अटल u64 mlxsw_ports_occ_get(व्योम *priv)
अणु
	काष्ठा mlxsw_core *mlxsw_core = priv;

	वापस atomic_पढ़ो(&mlxsw_core->active_ports_count);
पूर्ण

अटल पूर्णांक mlxsw_core_resources_ports_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_core);
	काष्ठा devlink_resource_size_params ports_num_params;
	u32 max_ports;

	max_ports = mlxsw_core->max_ports - 1;
	devlink_resource_size_params_init(&ports_num_params, max_ports,
					  max_ports, 1,
					  DEVLINK_RESOURCE_UNIT_ENTRY);

	वापस devlink_resource_रेजिस्टर(devlink,
					 DEVLINK_RESOURCE_GENERIC_NAME_PORTS,
					 max_ports, MLXSW_CORE_RESOURCE_PORTS,
					 DEVLINK_RESOURCE_ID_PARENT_TOP,
					 &ports_num_params);
पूर्ण

अटल पूर्णांक mlxsw_ports_init(काष्ठा mlxsw_core *mlxsw_core, bool reload)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_core);
	पूर्णांक err;

	/* Switch ports are numbered from 1 to queried value */
	अगर (MLXSW_CORE_RES_VALID(mlxsw_core, MAX_SYSTEM_PORT))
		mlxsw_core->max_ports = MLXSW_CORE_RES_GET(mlxsw_core,
							   MAX_SYSTEM_PORT) + 1;
	अन्यथा
		mlxsw_core->max_ports = MLXSW_PORT_MAX_PORTS_DEFAULT + 1;

	mlxsw_core->ports = kसुस्मृति(mlxsw_core->max_ports,
				    माप(काष्ठा mlxsw_core_port), GFP_KERNEL);
	अगर (!mlxsw_core->ports)
		वापस -ENOMEM;

	अगर (!reload) अणु
		err = mlxsw_core_resources_ports_रेजिस्टर(mlxsw_core);
		अगर (err)
			जाओ err_resources_ports_रेजिस्टर;
	पूर्ण
	atomic_set(&mlxsw_core->active_ports_count, 0);
	devlink_resource_occ_get_रेजिस्टर(devlink, MLXSW_CORE_RESOURCE_PORTS,
					  mlxsw_ports_occ_get, mlxsw_core);

	वापस 0;

err_resources_ports_रेजिस्टर:
	kमुक्त(mlxsw_core->ports);
	वापस err;
पूर्ण

अटल व्योम mlxsw_ports_fini(काष्ठा mlxsw_core *mlxsw_core, bool reload)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_core);

	devlink_resource_occ_get_unरेजिस्टर(devlink, MLXSW_CORE_RESOURCE_PORTS);
	अगर (!reload)
		devlink_resources_unरेजिस्टर(priv_to_devlink(mlxsw_core), शून्य);

	kमुक्त(mlxsw_core->ports);
पूर्ण

अचिन्हित पूर्णांक mlxsw_core_max_ports(स्थिर काष्ठा mlxsw_core *mlxsw_core)
अणु
	वापस mlxsw_core->max_ports;
पूर्ण
EXPORT_SYMBOL(mlxsw_core_max_ports);

व्योम *mlxsw_core_driver_priv(काष्ठा mlxsw_core *mlxsw_core)
अणु
	वापस mlxsw_core->driver_priv;
पूर्ण
EXPORT_SYMBOL(mlxsw_core_driver_priv);

bool mlxsw_core_res_query_enabled(स्थिर काष्ठा mlxsw_core *mlxsw_core)
अणु
	वापस mlxsw_core->driver->res_query_enabled;
पूर्ण
EXPORT_SYMBOL(mlxsw_core_res_query_enabled);

bool mlxsw_core_temp_warn_enabled(स्थिर काष्ठा mlxsw_core *mlxsw_core)
अणु
	वापस mlxsw_core->driver->temp_warn_enabled;
पूर्ण

bool
mlxsw_core_fw_rev_minor_subminor_validate(स्थिर काष्ठा mlxsw_fw_rev *rev,
					  स्थिर काष्ठा mlxsw_fw_rev *req_rev)
अणु
	वापस rev->minor > req_rev->minor ||
	       (rev->minor == req_rev->minor &&
		rev->subminor >= req_rev->subminor);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_fw_rev_minor_subminor_validate);

काष्ठा mlxsw_rx_listener_item अणु
	काष्ठा list_head list;
	काष्ठा mlxsw_rx_listener rxl;
	व्योम *priv;
	bool enabled;
पूर्ण;

काष्ठा mlxsw_event_listener_item अणु
	काष्ठा list_head list;
	काष्ठा mlxsw_core *mlxsw_core;
	काष्ठा mlxsw_event_listener el;
	व्योम *priv;
पूर्ण;

/******************
 * EMAD processing
 ******************/

/* emad_eth_hdr_dmac
 * Destination MAC in EMAD's Ethernet header.
 * Must be set to 01:02:c9:00:00:01
 */
MLXSW_ITEM_BUF(emad, eth_hdr, dmac, 0x00, 6);

/* emad_eth_hdr_smac
 * Source MAC in EMAD's Ethernet header.
 * Must be set to 00:02:c9:01:02:03
 */
MLXSW_ITEM_BUF(emad, eth_hdr, smac, 0x06, 6);

/* emad_eth_hdr_ethertype
 * Ethertype in EMAD's Ethernet header.
 * Must be set to 0x8932
 */
MLXSW_ITEM32(emad, eth_hdr, ethertype, 0x0C, 16, 16);

/* emad_eth_hdr_mlx_proto
 * Mellanox protocol.
 * Must be set to 0x0.
 */
MLXSW_ITEM32(emad, eth_hdr, mlx_proto, 0x0C, 8, 8);

/* emad_eth_hdr_ver
 * Mellanox protocol version.
 * Must be set to 0x0.
 */
MLXSW_ITEM32(emad, eth_hdr, ver, 0x0C, 4, 4);

/* emad_op_tlv_type
 * Type of the TLV.
 * Must be set to 0x1 (operation TLV).
 */
MLXSW_ITEM32(emad, op_tlv, type, 0x00, 27, 5);

/* emad_op_tlv_len
 * Length of the operation TLV in u32.
 * Must be set to 0x4.
 */
MLXSW_ITEM32(emad, op_tlv, len, 0x00, 16, 11);

/* emad_op_tlv_dr
 * Direct route bit. Setting to 1 indicates the EMAD is a direct route
 * EMAD. DR TLV must follow.
 *
 * Note: Currently not supported and must not be set.
 */
MLXSW_ITEM32(emad, op_tlv, dr, 0x00, 15, 1);

/* emad_op_tlv_status
 * Returned status in हाल of EMAD response. Must be set to 0 in हाल
 * of EMAD request.
 * 0x0 - success
 * 0x1 - device is busy. Requester should retry
 * 0x2 - Mellanox protocol version not supported
 * 0x3 - unknown TLV
 * 0x4 - रेजिस्टर not supported
 * 0x5 - operation class not supported
 * 0x6 - EMAD method not supported
 * 0x7 - bad parameter (e.g. port out of range)
 * 0x8 - resource not available
 * 0x9 - message receipt acknowledgment. Requester should retry
 * 0x70 - पूर्णांकernal error
 */
MLXSW_ITEM32(emad, op_tlv, status, 0x00, 8, 7);

/* emad_op_tlv_रेजिस्टर_id
 * Register ID of रेजिस्टर within रेजिस्टर TLV.
 */
MLXSW_ITEM32(emad, op_tlv, रेजिस्टर_id, 0x04, 16, 16);

/* emad_op_tlv_r
 * Response bit. Setting to 1 indicates Response, otherwise request.
 */
MLXSW_ITEM32(emad, op_tlv, r, 0x04, 15, 1);

/* emad_op_tlv_method
 * EMAD method type.
 * 0x1 - query
 * 0x2 - ग_लिखो
 * 0x3 - send (currently not supported)
 * 0x4 - event
 */
MLXSW_ITEM32(emad, op_tlv, method, 0x04, 8, 7);

/* emad_op_tlv_class
 * EMAD operation class. Must be set to 0x1 (REG_ACCESS).
 */
MLXSW_ITEM32(emad, op_tlv, class, 0x04, 0, 8);

/* emad_op_tlv_tid
 * EMAD transaction ID. Used क्रम pairing request and response EMADs.
 */
MLXSW_ITEM64(emad, op_tlv, tid, 0x08, 0, 64);

/* emad_string_tlv_type
 * Type of the TLV.
 * Must be set to 0x2 (string TLV).
 */
MLXSW_ITEM32(emad, string_tlv, type, 0x00, 27, 5);

/* emad_string_tlv_len
 * Length of the string TLV in u32.
 */
MLXSW_ITEM32(emad, string_tlv, len, 0x00, 16, 11);

#घोषणा MLXSW_EMAD_STRING_TLV_STRING_LEN 128

/* emad_string_tlv_string
 * String provided by the device's firmware in हाल of erroneous रेजिस्टर access
 */
MLXSW_ITEM_BUF(emad, string_tlv, string, 0x04,
	       MLXSW_EMAD_STRING_TLV_STRING_LEN);

/* emad_reg_tlv_type
 * Type of the TLV.
 * Must be set to 0x3 (रेजिस्टर TLV).
 */
MLXSW_ITEM32(emad, reg_tlv, type, 0x00, 27, 5);

/* emad_reg_tlv_len
 * Length of the operation TLV in u32.
 */
MLXSW_ITEM32(emad, reg_tlv, len, 0x00, 16, 11);

/* emad_end_tlv_type
 * Type of the TLV.
 * Must be set to 0x0 (end TLV).
 */
MLXSW_ITEM32(emad, end_tlv, type, 0x00, 27, 5);

/* emad_end_tlv_len
 * Length of the end TLV in u32.
 * Must be set to 1.
 */
MLXSW_ITEM32(emad, end_tlv, len, 0x00, 16, 11);

क्रमागत mlxsw_core_reg_access_type अणु
	MLXSW_CORE_REG_ACCESS_TYPE_QUERY,
	MLXSW_CORE_REG_ACCESS_TYPE_WRITE,
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *
mlxsw_core_reg_access_type_str(क्रमागत mlxsw_core_reg_access_type type)
अणु
	चयन (type) अणु
	हाल MLXSW_CORE_REG_ACCESS_TYPE_QUERY:
		वापस "query";
	हाल MLXSW_CORE_REG_ACCESS_TYPE_WRITE:
		वापस "write";
	पूर्ण
	BUG();
पूर्ण

अटल व्योम mlxsw_emad_pack_end_tlv(अक्षर *end_tlv)
अणु
	mlxsw_emad_end_tlv_type_set(end_tlv, MLXSW_EMAD_TLV_TYPE_END);
	mlxsw_emad_end_tlv_len_set(end_tlv, MLXSW_EMAD_END_TLV_LEN);
पूर्ण

अटल व्योम mlxsw_emad_pack_reg_tlv(अक्षर *reg_tlv,
				    स्थिर काष्ठा mlxsw_reg_info *reg,
				    अक्षर *payload)
अणु
	mlxsw_emad_reg_tlv_type_set(reg_tlv, MLXSW_EMAD_TLV_TYPE_REG);
	mlxsw_emad_reg_tlv_len_set(reg_tlv, reg->len / माप(u32) + 1);
	स_नकल(reg_tlv + माप(u32), payload, reg->len);
पूर्ण

अटल व्योम mlxsw_emad_pack_string_tlv(अक्षर *string_tlv)
अणु
	mlxsw_emad_string_tlv_type_set(string_tlv, MLXSW_EMAD_TLV_TYPE_STRING);
	mlxsw_emad_string_tlv_len_set(string_tlv, MLXSW_EMAD_STRING_TLV_LEN);
पूर्ण

अटल व्योम mlxsw_emad_pack_op_tlv(अक्षर *op_tlv,
				   स्थिर काष्ठा mlxsw_reg_info *reg,
				   क्रमागत mlxsw_core_reg_access_type type,
				   u64 tid)
अणु
	mlxsw_emad_op_tlv_type_set(op_tlv, MLXSW_EMAD_TLV_TYPE_OP);
	mlxsw_emad_op_tlv_len_set(op_tlv, MLXSW_EMAD_OP_TLV_LEN);
	mlxsw_emad_op_tlv_dr_set(op_tlv, 0);
	mlxsw_emad_op_tlv_status_set(op_tlv, 0);
	mlxsw_emad_op_tlv_रेजिस्टर_id_set(op_tlv, reg->id);
	mlxsw_emad_op_tlv_r_set(op_tlv, MLXSW_EMAD_OP_TLV_REQUEST);
	अगर (type == MLXSW_CORE_REG_ACCESS_TYPE_QUERY)
		mlxsw_emad_op_tlv_method_set(op_tlv,
					     MLXSW_EMAD_OP_TLV_METHOD_QUERY);
	अन्यथा
		mlxsw_emad_op_tlv_method_set(op_tlv,
					     MLXSW_EMAD_OP_TLV_METHOD_WRITE);
	mlxsw_emad_op_tlv_class_set(op_tlv,
				    MLXSW_EMAD_OP_TLV_CLASS_REG_ACCESS);
	mlxsw_emad_op_tlv_tid_set(op_tlv, tid);
पूर्ण

अटल पूर्णांक mlxsw_emad_स्थिरruct_eth_hdr(काष्ठा sk_buff *skb)
अणु
	अक्षर *eth_hdr = skb_push(skb, MLXSW_EMAD_ETH_HDR_LEN);

	mlxsw_emad_eth_hdr_dmac_स_नकल_to(eth_hdr, MLXSW_EMAD_EH_DMAC);
	mlxsw_emad_eth_hdr_smac_स_नकल_to(eth_hdr, MLXSW_EMAD_EH_SMAC);
	mlxsw_emad_eth_hdr_ethertype_set(eth_hdr, MLXSW_EMAD_EH_ETHERTYPE);
	mlxsw_emad_eth_hdr_mlx_proto_set(eth_hdr, MLXSW_EMAD_EH_MLX_PROTO);
	mlxsw_emad_eth_hdr_ver_set(eth_hdr, MLXSW_EMAD_EH_PROTO_VERSION);

	skb_reset_mac_header(skb);

	वापस 0;
पूर्ण

अटल व्योम mlxsw_emad_स्थिरruct(काष्ठा sk_buff *skb,
				 स्थिर काष्ठा mlxsw_reg_info *reg,
				 अक्षर *payload,
				 क्रमागत mlxsw_core_reg_access_type type,
				 u64 tid, bool enable_string_tlv)
अणु
	अक्षर *buf;

	buf = skb_push(skb, MLXSW_EMAD_END_TLV_LEN * माप(u32));
	mlxsw_emad_pack_end_tlv(buf);

	buf = skb_push(skb, reg->len + माप(u32));
	mlxsw_emad_pack_reg_tlv(buf, reg, payload);

	अगर (enable_string_tlv) अणु
		buf = skb_push(skb, MLXSW_EMAD_STRING_TLV_LEN * माप(u32));
		mlxsw_emad_pack_string_tlv(buf);
	पूर्ण

	buf = skb_push(skb, MLXSW_EMAD_OP_TLV_LEN * माप(u32));
	mlxsw_emad_pack_op_tlv(buf, reg, type, tid);

	mlxsw_emad_स्थिरruct_eth_hdr(skb);
पूर्ण

काष्ठा mlxsw_emad_tlv_offsets अणु
	u16 op_tlv;
	u16 string_tlv;
	u16 reg_tlv;
पूर्ण;

अटल bool mlxsw_emad_tlv_is_string_tlv(स्थिर अक्षर *tlv)
अणु
	u8 tlv_type = mlxsw_emad_string_tlv_type_get(tlv);

	वापस tlv_type == MLXSW_EMAD_TLV_TYPE_STRING;
पूर्ण

अटल व्योम mlxsw_emad_tlv_parse(काष्ठा sk_buff *skb)
अणु
	काष्ठा mlxsw_emad_tlv_offsets *offsets =
		(काष्ठा mlxsw_emad_tlv_offsets *) skb->cb;

	offsets->op_tlv = MLXSW_EMAD_ETH_HDR_LEN;
	offsets->string_tlv = 0;
	offsets->reg_tlv = MLXSW_EMAD_ETH_HDR_LEN +
			   MLXSW_EMAD_OP_TLV_LEN * माप(u32);

	/* If string TLV is present, it must come after the operation TLV. */
	अगर (mlxsw_emad_tlv_is_string_tlv(skb->data + offsets->reg_tlv)) अणु
		offsets->string_tlv = offsets->reg_tlv;
		offsets->reg_tlv += MLXSW_EMAD_STRING_TLV_LEN * माप(u32);
	पूर्ण
पूर्ण

अटल अक्षर *mlxsw_emad_op_tlv(स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा mlxsw_emad_tlv_offsets *offsets =
		(काष्ठा mlxsw_emad_tlv_offsets *) skb->cb;

	वापस ((अक्षर *) (skb->data + offsets->op_tlv));
पूर्ण

अटल अक्षर *mlxsw_emad_string_tlv(स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा mlxsw_emad_tlv_offsets *offsets =
		(काष्ठा mlxsw_emad_tlv_offsets *) skb->cb;

	अगर (!offsets->string_tlv)
		वापस शून्य;

	वापस ((अक्षर *) (skb->data + offsets->string_tlv));
पूर्ण

अटल अक्षर *mlxsw_emad_reg_tlv(स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा mlxsw_emad_tlv_offsets *offsets =
		(काष्ठा mlxsw_emad_tlv_offsets *) skb->cb;

	वापस ((अक्षर *) (skb->data + offsets->reg_tlv));
पूर्ण

अटल अक्षर *mlxsw_emad_reg_payload(स्थिर अक्षर *reg_tlv)
अणु
	वापस ((अक्षर *) (reg_tlv + माप(u32)));
पूर्ण

अटल अक्षर *mlxsw_emad_reg_payload_cmd(स्थिर अक्षर *mbox)
अणु
	वापस ((अक्षर *) (mbox + (MLXSW_EMAD_OP_TLV_LEN + 1) * माप(u32)));
पूर्ण

अटल u64 mlxsw_emad_get_tid(स्थिर काष्ठा sk_buff *skb)
अणु
	अक्षर *op_tlv;

	op_tlv = mlxsw_emad_op_tlv(skb);
	वापस mlxsw_emad_op_tlv_tid_get(op_tlv);
पूर्ण

अटल bool mlxsw_emad_is_resp(स्थिर काष्ठा sk_buff *skb)
अणु
	अक्षर *op_tlv;

	op_tlv = mlxsw_emad_op_tlv(skb);
	वापस (mlxsw_emad_op_tlv_r_get(op_tlv) == MLXSW_EMAD_OP_TLV_RESPONSE);
पूर्ण

अटल पूर्णांक mlxsw_emad_process_status(अक्षर *op_tlv,
				     क्रमागत mlxsw_emad_op_tlv_status *p_status)
अणु
	*p_status = mlxsw_emad_op_tlv_status_get(op_tlv);

	चयन (*p_status) अणु
	हाल MLXSW_EMAD_OP_TLV_STATUS_SUCCESS:
		वापस 0;
	हाल MLXSW_EMAD_OP_TLV_STATUS_BUSY:
	हाल MLXSW_EMAD_OP_TLV_STATUS_MESSAGE_RECEIPT_ACK:
		वापस -EAGAIN;
	हाल MLXSW_EMAD_OP_TLV_STATUS_VERSION_NOT_SUPPORTED:
	हाल MLXSW_EMAD_OP_TLV_STATUS_UNKNOWN_TLV:
	हाल MLXSW_EMAD_OP_TLV_STATUS_REGISTER_NOT_SUPPORTED:
	हाल MLXSW_EMAD_OP_TLV_STATUS_CLASS_NOT_SUPPORTED:
	हाल MLXSW_EMAD_OP_TLV_STATUS_METHOD_NOT_SUPPORTED:
	हाल MLXSW_EMAD_OP_TLV_STATUS_BAD_PARAMETER:
	हाल MLXSW_EMAD_OP_TLV_STATUS_RESOURCE_NOT_AVAILABLE:
	हाल MLXSW_EMAD_OP_TLV_STATUS_INTERNAL_ERROR:
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल पूर्णांक
mlxsw_emad_process_status_skb(काष्ठा sk_buff *skb,
			      क्रमागत mlxsw_emad_op_tlv_status *p_status)
अणु
	वापस mlxsw_emad_process_status(mlxsw_emad_op_tlv(skb), p_status);
पूर्ण

काष्ठा mlxsw_reg_trans अणु
	काष्ठा list_head list;
	काष्ठा list_head bulk_list;
	काष्ठा mlxsw_core *core;
	काष्ठा sk_buff *tx_skb;
	काष्ठा mlxsw_tx_info tx_info;
	काष्ठा delayed_work समयout_dw;
	अचिन्हित पूर्णांक retries;
	u64 tid;
	काष्ठा completion completion;
	atomic_t active;
	mlxsw_reg_trans_cb_t *cb;
	अचिन्हित दीर्घ cb_priv;
	स्थिर काष्ठा mlxsw_reg_info *reg;
	क्रमागत mlxsw_core_reg_access_type type;
	पूर्णांक err;
	अक्षर *emad_err_string;
	क्रमागत mlxsw_emad_op_tlv_status emad_status;
	काष्ठा rcu_head rcu;
पूर्ण;

अटल व्योम mlxsw_emad_process_string_tlv(स्थिर काष्ठा sk_buff *skb,
					  काष्ठा mlxsw_reg_trans *trans)
अणु
	अक्षर *string_tlv;
	अक्षर *string;

	string_tlv = mlxsw_emad_string_tlv(skb);
	अगर (!string_tlv)
		वापस;

	trans->emad_err_string = kzalloc(MLXSW_EMAD_STRING_TLV_STRING_LEN,
					 GFP_ATOMIC);
	अगर (!trans->emad_err_string)
		वापस;

	string = mlxsw_emad_string_tlv_string_data(string_tlv);
	strlcpy(trans->emad_err_string, string,
		MLXSW_EMAD_STRING_TLV_STRING_LEN);
पूर्ण

#घोषणा MLXSW_EMAD_TIMEOUT_DURING_FW_FLASH_MS	3000
#घोषणा MLXSW_EMAD_TIMEOUT_MS			200

अटल व्योम mlxsw_emad_trans_समयout_schedule(काष्ठा mlxsw_reg_trans *trans)
अणु
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(MLXSW_EMAD_TIMEOUT_MS);

	अगर (trans->core->fw_flash_in_progress)
		समयout = msecs_to_jअगरfies(MLXSW_EMAD_TIMEOUT_DURING_FW_FLASH_MS);

	queue_delayed_work(trans->core->emad_wq, &trans->समयout_dw,
			   समयout << trans->retries);
पूर्ण

अटल पूर्णांक mlxsw_emad_transmit(काष्ठा mlxsw_core *mlxsw_core,
			       काष्ठा mlxsw_reg_trans *trans)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	skb = skb_copy(trans->tx_skb, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	trace_devlink_hwmsg(priv_to_devlink(mlxsw_core), false, 0,
			    skb->data + mlxsw_core->driver->txhdr_len,
			    skb->len - mlxsw_core->driver->txhdr_len);

	atomic_set(&trans->active, 1);
	err = mlxsw_core_skb_transmit(mlxsw_core, skb, &trans->tx_info);
	अगर (err) अणु
		dev_kमुक्त_skb(skb);
		वापस err;
	पूर्ण
	mlxsw_emad_trans_समयout_schedule(trans);
	वापस 0;
पूर्ण

अटल व्योम mlxsw_emad_trans_finish(काष्ठा mlxsw_reg_trans *trans, पूर्णांक err)
अणु
	काष्ठा mlxsw_core *mlxsw_core = trans->core;

	dev_kमुक्त_skb(trans->tx_skb);
	spin_lock_bh(&mlxsw_core->emad.trans_list_lock);
	list_del_rcu(&trans->list);
	spin_unlock_bh(&mlxsw_core->emad.trans_list_lock);
	trans->err = err;
	complete(&trans->completion);
पूर्ण

अटल व्योम mlxsw_emad_transmit_retry(काष्ठा mlxsw_core *mlxsw_core,
				      काष्ठा mlxsw_reg_trans *trans)
अणु
	पूर्णांक err;

	अगर (trans->retries < MLXSW_EMAD_MAX_RETRY) अणु
		trans->retries++;
		err = mlxsw_emad_transmit(trans->core, trans);
		अगर (err == 0)
			वापस;

		अगर (!atomic_dec_and_test(&trans->active))
			वापस;
	पूर्ण अन्यथा अणु
		err = -EIO;
	पूर्ण
	mlxsw_emad_trans_finish(trans, err);
पूर्ण

अटल व्योम mlxsw_emad_trans_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxsw_reg_trans *trans = container_of(work,
						     काष्ठा mlxsw_reg_trans,
						     समयout_dw.work);

	अगर (!atomic_dec_and_test(&trans->active))
		वापस;

	mlxsw_emad_transmit_retry(trans->core, trans);
पूर्ण

अटल व्योम mlxsw_emad_process_response(काष्ठा mlxsw_core *mlxsw_core,
					काष्ठा mlxsw_reg_trans *trans,
					काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	अगर (!atomic_dec_and_test(&trans->active))
		वापस;

	err = mlxsw_emad_process_status_skb(skb, &trans->emad_status);
	अगर (err == -EAGAIN) अणु
		mlxsw_emad_transmit_retry(mlxsw_core, trans);
	पूर्ण अन्यथा अणु
		अगर (err == 0) अणु
			अक्षर *reg_tlv = mlxsw_emad_reg_tlv(skb);

			अगर (trans->cb)
				trans->cb(mlxsw_core,
					  mlxsw_emad_reg_payload(reg_tlv),
					  trans->reg->len, trans->cb_priv);
		पूर्ण अन्यथा अणु
			mlxsw_emad_process_string_tlv(skb, trans);
		पूर्ण
		mlxsw_emad_trans_finish(trans, err);
	पूर्ण
पूर्ण

/* called with rcu पढ़ो lock held */
अटल व्योम mlxsw_emad_rx_listener_func(काष्ठा sk_buff *skb, u8 local_port,
					व्योम *priv)
अणु
	काष्ठा mlxsw_core *mlxsw_core = priv;
	काष्ठा mlxsw_reg_trans *trans;

	trace_devlink_hwmsg(priv_to_devlink(mlxsw_core), true, 0,
			    skb->data, skb->len);

	mlxsw_emad_tlv_parse(skb);

	अगर (!mlxsw_emad_is_resp(skb))
		जाओ मुक्त_skb;

	list_क्रम_each_entry_rcu(trans, &mlxsw_core->emad.trans_list, list) अणु
		अगर (mlxsw_emad_get_tid(skb) == trans->tid) अणु
			mlxsw_emad_process_response(mlxsw_core, trans, skb);
			अवरोध;
		पूर्ण
	पूर्ण

मुक्त_skb:
	dev_kमुक्त_skb(skb);
पूर्ण

अटल स्थिर काष्ठा mlxsw_listener mlxsw_emad_rx_listener =
	MLXSW_RXL(mlxsw_emad_rx_listener_func, ETHEMAD, TRAP_TO_CPU, false,
		  EMAD, DISCARD);

अटल पूर्णांक mlxsw_emad_init(काष्ठा mlxsw_core *mlxsw_core)
अणु
	काष्ठा workqueue_काष्ठा *emad_wq;
	u64 tid;
	पूर्णांक err;

	अगर (!(mlxsw_core->bus->features & MLXSW_BUS_F_TXRX))
		वापस 0;

	emad_wq = alloc_workqueue("mlxsw_core_emad", 0, 0);
	अगर (!emad_wq)
		वापस -ENOMEM;
	mlxsw_core->emad_wq = emad_wq;

	/* Set the upper 32 bits of the transaction ID field to a अक्रमom
	 * number. This allows us to discard EMADs addressed to other
	 * devices.
	 */
	get_अक्रमom_bytes(&tid, 4);
	tid <<= 32;
	atomic64_set(&mlxsw_core->emad.tid, tid);

	INIT_LIST_HEAD(&mlxsw_core->emad.trans_list);
	spin_lock_init(&mlxsw_core->emad.trans_list_lock);

	err = mlxsw_core_trap_रेजिस्टर(mlxsw_core, &mlxsw_emad_rx_listener,
				       mlxsw_core);
	अगर (err)
		जाओ err_trap_रेजिस्टर;

	err = mlxsw_core->driver->basic_trap_groups_set(mlxsw_core);
	अगर (err)
		जाओ err_emad_trap_set;
	mlxsw_core->emad.use_emad = true;

	वापस 0;

err_emad_trap_set:
	mlxsw_core_trap_unरेजिस्टर(mlxsw_core, &mlxsw_emad_rx_listener,
				   mlxsw_core);
err_trap_रेजिस्टर:
	destroy_workqueue(mlxsw_core->emad_wq);
	वापस err;
पूर्ण

अटल व्योम mlxsw_emad_fini(काष्ठा mlxsw_core *mlxsw_core)
अणु

	अगर (!(mlxsw_core->bus->features & MLXSW_BUS_F_TXRX))
		वापस;

	mlxsw_core->emad.use_emad = false;
	mlxsw_core_trap_unरेजिस्टर(mlxsw_core, &mlxsw_emad_rx_listener,
				   mlxsw_core);
	destroy_workqueue(mlxsw_core->emad_wq);
पूर्ण

अटल काष्ठा sk_buff *mlxsw_emad_alloc(स्थिर काष्ठा mlxsw_core *mlxsw_core,
					u16 reg_len, bool enable_string_tlv)
अणु
	काष्ठा sk_buff *skb;
	u16 emad_len;

	emad_len = (reg_len + माप(u32) + MLXSW_EMAD_ETH_HDR_LEN +
		    (MLXSW_EMAD_OP_TLV_LEN + MLXSW_EMAD_END_TLV_LEN) *
		    माप(u32) + mlxsw_core->driver->txhdr_len);
	अगर (enable_string_tlv)
		emad_len += MLXSW_EMAD_STRING_TLV_LEN * माप(u32);
	अगर (emad_len > MLXSW_EMAD_MAX_FRAME_LEN)
		वापस शून्य;

	skb = netdev_alloc_skb(शून्य, emad_len);
	अगर (!skb)
		वापस शून्य;
	स_रखो(skb->data, 0, emad_len);
	skb_reserve(skb, emad_len);

	वापस skb;
पूर्ण

अटल पूर्णांक mlxsw_emad_reg_access(काष्ठा mlxsw_core *mlxsw_core,
				 स्थिर काष्ठा mlxsw_reg_info *reg,
				 अक्षर *payload,
				 क्रमागत mlxsw_core_reg_access_type type,
				 काष्ठा mlxsw_reg_trans *trans,
				 काष्ठा list_head *bulk_list,
				 mlxsw_reg_trans_cb_t *cb,
				 अचिन्हित दीर्घ cb_priv, u64 tid)
अणु
	bool enable_string_tlv;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	dev_dbg(mlxsw_core->bus_info->dev, "EMAD reg access (tid=%llx,reg_id=%x(%s),type=%s)\n",
		tid, reg->id, mlxsw_reg_id_str(reg->id),
		mlxsw_core_reg_access_type_str(type));

	/* Since this can be changed during emad_reg_access, पढ़ो it once and
	 * use the value all the way.
	 */
	enable_string_tlv = mlxsw_core->emad.enable_string_tlv;

	skb = mlxsw_emad_alloc(mlxsw_core, reg->len, enable_string_tlv);
	अगर (!skb)
		वापस -ENOMEM;

	list_add_tail(&trans->bulk_list, bulk_list);
	trans->core = mlxsw_core;
	trans->tx_skb = skb;
	trans->tx_info.local_port = MLXSW_PORT_CPU_PORT;
	trans->tx_info.is_emad = true;
	INIT_DELAYED_WORK(&trans->समयout_dw, mlxsw_emad_trans_समयout_work);
	trans->tid = tid;
	init_completion(&trans->completion);
	trans->cb = cb;
	trans->cb_priv = cb_priv;
	trans->reg = reg;
	trans->type = type;

	mlxsw_emad_स्थिरruct(skb, reg, payload, type, trans->tid,
			     enable_string_tlv);
	mlxsw_core->driver->txhdr_स्थिरruct(skb, &trans->tx_info);

	spin_lock_bh(&mlxsw_core->emad.trans_list_lock);
	list_add_tail_rcu(&trans->list, &mlxsw_core->emad.trans_list);
	spin_unlock_bh(&mlxsw_core->emad.trans_list_lock);
	err = mlxsw_emad_transmit(mlxsw_core, trans);
	अगर (err)
		जाओ err_out;
	वापस 0;

err_out:
	spin_lock_bh(&mlxsw_core->emad.trans_list_lock);
	list_del_rcu(&trans->list);
	spin_unlock_bh(&mlxsw_core->emad.trans_list_lock);
	list_del(&trans->bulk_list);
	dev_kमुक्त_skb(trans->tx_skb);
	वापस err;
पूर्ण

/*****************
 * Core functions
 *****************/

पूर्णांक mlxsw_core_driver_रेजिस्टर(काष्ठा mlxsw_driver *mlxsw_driver)
अणु
	spin_lock(&mlxsw_core_driver_list_lock);
	list_add_tail(&mlxsw_driver->list, &mlxsw_core_driver_list);
	spin_unlock(&mlxsw_core_driver_list_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlxsw_core_driver_रेजिस्टर);

व्योम mlxsw_core_driver_unरेजिस्टर(काष्ठा mlxsw_driver *mlxsw_driver)
अणु
	spin_lock(&mlxsw_core_driver_list_lock);
	list_del(&mlxsw_driver->list);
	spin_unlock(&mlxsw_core_driver_list_lock);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_driver_unरेजिस्टर);

अटल काष्ठा mlxsw_driver *__driver_find(स्थिर अक्षर *kind)
अणु
	काष्ठा mlxsw_driver *mlxsw_driver;

	list_क्रम_each_entry(mlxsw_driver, &mlxsw_core_driver_list, list) अणु
		अगर (म_भेद(mlxsw_driver->kind, kind) == 0)
			वापस mlxsw_driver;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा mlxsw_driver *mlxsw_core_driver_get(स्थिर अक्षर *kind)
अणु
	काष्ठा mlxsw_driver *mlxsw_driver;

	spin_lock(&mlxsw_core_driver_list_lock);
	mlxsw_driver = __driver_find(kind);
	spin_unlock(&mlxsw_core_driver_list_lock);
	वापस mlxsw_driver;
पूर्ण

काष्ठा mlxsw_core_fw_info अणु
	काष्ठा mlxfw_dev mlxfw_dev;
	काष्ठा mlxsw_core *mlxsw_core;
पूर्ण;

अटल पूर्णांक mlxsw_core_fw_component_query(काष्ठा mlxfw_dev *mlxfw_dev,
					 u16 component_index, u32 *p_max_size,
					 u8 *p_align_bits, u16 *p_max_ग_लिखो_size)
अणु
	काष्ठा mlxsw_core_fw_info *mlxsw_core_fw_info =
		container_of(mlxfw_dev, काष्ठा mlxsw_core_fw_info, mlxfw_dev);
	काष्ठा mlxsw_core *mlxsw_core = mlxsw_core_fw_info->mlxsw_core;
	अक्षर mcqi_pl[MLXSW_REG_MCQI_LEN];
	पूर्णांक err;

	mlxsw_reg_mcqi_pack(mcqi_pl, component_index);
	err = mlxsw_reg_query(mlxsw_core, MLXSW_REG(mcqi), mcqi_pl);
	अगर (err)
		वापस err;
	mlxsw_reg_mcqi_unpack(mcqi_pl, p_max_size, p_align_bits, p_max_ग_लिखो_size);

	*p_align_bits = max_t(u8, *p_align_bits, 2);
	*p_max_ग_लिखो_size = min_t(u16, *p_max_ग_लिखो_size, MLXSW_REG_MCDA_MAX_DATA_LEN);
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_core_fw_fsm_lock(काष्ठा mlxfw_dev *mlxfw_dev, u32 *fwhandle)
अणु
	काष्ठा mlxsw_core_fw_info *mlxsw_core_fw_info =
		container_of(mlxfw_dev, काष्ठा mlxsw_core_fw_info, mlxfw_dev);
	काष्ठा mlxsw_core *mlxsw_core = mlxsw_core_fw_info->mlxsw_core;
	अक्षर mcc_pl[MLXSW_REG_MCC_LEN];
	u8 control_state;
	पूर्णांक err;

	mlxsw_reg_mcc_pack(mcc_pl, 0, 0, 0, 0);
	err = mlxsw_reg_query(mlxsw_core, MLXSW_REG(mcc), mcc_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_mcc_unpack(mcc_pl, fwhandle, शून्य, &control_state);
	अगर (control_state != MLXFW_FSM_STATE_IDLE)
		वापस -EBUSY;

	mlxsw_reg_mcc_pack(mcc_pl, MLXSW_REG_MCC_INSTRUCTION_LOCK_UPDATE_HANDLE, 0, *fwhandle, 0);
	वापस mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(mcc), mcc_pl);
पूर्ण

अटल पूर्णांक mlxsw_core_fw_fsm_component_update(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle,
					      u16 component_index, u32 component_size)
अणु
	काष्ठा mlxsw_core_fw_info *mlxsw_core_fw_info =
		container_of(mlxfw_dev, काष्ठा mlxsw_core_fw_info, mlxfw_dev);
	काष्ठा mlxsw_core *mlxsw_core = mlxsw_core_fw_info->mlxsw_core;
	अक्षर mcc_pl[MLXSW_REG_MCC_LEN];

	mlxsw_reg_mcc_pack(mcc_pl, MLXSW_REG_MCC_INSTRUCTION_UPDATE_COMPONENT,
			   component_index, fwhandle, component_size);
	वापस mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(mcc), mcc_pl);
पूर्ण

अटल पूर्णांक mlxsw_core_fw_fsm_block_करोwnload(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle,
					    u8 *data, u16 size, u32 offset)
अणु
	काष्ठा mlxsw_core_fw_info *mlxsw_core_fw_info =
		container_of(mlxfw_dev, काष्ठा mlxsw_core_fw_info, mlxfw_dev);
	काष्ठा mlxsw_core *mlxsw_core = mlxsw_core_fw_info->mlxsw_core;
	अक्षर mcda_pl[MLXSW_REG_MCDA_LEN];

	mlxsw_reg_mcda_pack(mcda_pl, fwhandle, offset, size, data);
	वापस mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(mcda), mcda_pl);
पूर्ण

अटल पूर्णांक mlxsw_core_fw_fsm_component_verअगरy(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle,
					      u16 component_index)
अणु
	काष्ठा mlxsw_core_fw_info *mlxsw_core_fw_info =
		container_of(mlxfw_dev, काष्ठा mlxsw_core_fw_info, mlxfw_dev);
	काष्ठा mlxsw_core *mlxsw_core = mlxsw_core_fw_info->mlxsw_core;
	अक्षर mcc_pl[MLXSW_REG_MCC_LEN];

	mlxsw_reg_mcc_pack(mcc_pl, MLXSW_REG_MCC_INSTRUCTION_VERIFY_COMPONENT,
			   component_index, fwhandle, 0);
	वापस mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(mcc), mcc_pl);
पूर्ण

अटल पूर्णांक mlxsw_core_fw_fsm_activate(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle)
अणु
	काष्ठा mlxsw_core_fw_info *mlxsw_core_fw_info =
		container_of(mlxfw_dev, काष्ठा mlxsw_core_fw_info, mlxfw_dev);
	काष्ठा mlxsw_core *mlxsw_core = mlxsw_core_fw_info->mlxsw_core;
	अक्षर mcc_pl[MLXSW_REG_MCC_LEN];

	mlxsw_reg_mcc_pack(mcc_pl, MLXSW_REG_MCC_INSTRUCTION_ACTIVATE, 0, fwhandle, 0);
	वापस mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(mcc), mcc_pl);
पूर्ण

अटल पूर्णांक mlxsw_core_fw_fsm_query_state(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle,
					 क्रमागत mlxfw_fsm_state *fsm_state,
					 क्रमागत mlxfw_fsm_state_err *fsm_state_err)
अणु
	काष्ठा mlxsw_core_fw_info *mlxsw_core_fw_info =
		container_of(mlxfw_dev, काष्ठा mlxsw_core_fw_info, mlxfw_dev);
	काष्ठा mlxsw_core *mlxsw_core = mlxsw_core_fw_info->mlxsw_core;
	अक्षर mcc_pl[MLXSW_REG_MCC_LEN];
	u8 control_state;
	u8 error_code;
	पूर्णांक err;

	mlxsw_reg_mcc_pack(mcc_pl, 0, 0, fwhandle, 0);
	err = mlxsw_reg_query(mlxsw_core, MLXSW_REG(mcc), mcc_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_mcc_unpack(mcc_pl, शून्य, &error_code, &control_state);
	*fsm_state = control_state;
	*fsm_state_err = min_t(क्रमागत mlxfw_fsm_state_err, error_code, MLXFW_FSM_STATE_ERR_MAX);
	वापस 0;
पूर्ण

अटल व्योम mlxsw_core_fw_fsm_cancel(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle)
अणु
	काष्ठा mlxsw_core_fw_info *mlxsw_core_fw_info =
		container_of(mlxfw_dev, काष्ठा mlxsw_core_fw_info, mlxfw_dev);
	काष्ठा mlxsw_core *mlxsw_core = mlxsw_core_fw_info->mlxsw_core;
	अक्षर mcc_pl[MLXSW_REG_MCC_LEN];

	mlxsw_reg_mcc_pack(mcc_pl, MLXSW_REG_MCC_INSTRUCTION_CANCEL, 0, fwhandle, 0);
	mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(mcc), mcc_pl);
पूर्ण

अटल व्योम mlxsw_core_fw_fsm_release(काष्ठा mlxfw_dev *mlxfw_dev, u32 fwhandle)
अणु
	काष्ठा mlxsw_core_fw_info *mlxsw_core_fw_info =
		container_of(mlxfw_dev, काष्ठा mlxsw_core_fw_info, mlxfw_dev);
	काष्ठा mlxsw_core *mlxsw_core = mlxsw_core_fw_info->mlxsw_core;
	अक्षर mcc_pl[MLXSW_REG_MCC_LEN];

	mlxsw_reg_mcc_pack(mcc_pl, MLXSW_REG_MCC_INSTRUCTION_RELEASE_UPDATE_HANDLE, 0, fwhandle, 0);
	mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(mcc), mcc_pl);
पूर्ण

अटल स्थिर काष्ठा mlxfw_dev_ops mlxsw_core_fw_mlxsw_dev_ops = अणु
	.component_query	= mlxsw_core_fw_component_query,
	.fsm_lock		= mlxsw_core_fw_fsm_lock,
	.fsm_component_update	= mlxsw_core_fw_fsm_component_update,
	.fsm_block_करोwnload	= mlxsw_core_fw_fsm_block_करोwnload,
	.fsm_component_verअगरy	= mlxsw_core_fw_fsm_component_verअगरy,
	.fsm_activate		= mlxsw_core_fw_fsm_activate,
	.fsm_query_state	= mlxsw_core_fw_fsm_query_state,
	.fsm_cancel		= mlxsw_core_fw_fsm_cancel,
	.fsm_release		= mlxsw_core_fw_fsm_release,
पूर्ण;

अटल पूर्णांक mlxsw_core_fw_flash(काष्ठा mlxsw_core *mlxsw_core, स्थिर काष्ठा firmware *firmware,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_core_fw_info mlxsw_core_fw_info = अणु
		.mlxfw_dev = अणु
			.ops = &mlxsw_core_fw_mlxsw_dev_ops,
			.psid = mlxsw_core->bus_info->psid,
			.psid_size = म_माप(mlxsw_core->bus_info->psid),
			.devlink = priv_to_devlink(mlxsw_core),
		पूर्ण,
		.mlxsw_core = mlxsw_core
	पूर्ण;
	पूर्णांक err;

	mlxsw_core->fw_flash_in_progress = true;
	err = mlxfw_firmware_flash(&mlxsw_core_fw_info.mlxfw_dev, firmware, extack);
	mlxsw_core->fw_flash_in_progress = false;

	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_core_fw_rev_validate(काष्ठा mlxsw_core *mlxsw_core,
				      स्थिर काष्ठा mlxsw_bus_info *mlxsw_bus_info,
				      स्थिर काष्ठा mlxsw_fw_rev *req_rev,
				      स्थिर अक्षर *filename)
अणु
	स्थिर काष्ठा mlxsw_fw_rev *rev = &mlxsw_bus_info->fw_rev;
	जोड़ devlink_param_value value;
	स्थिर काष्ठा firmware *firmware;
	पूर्णांक err;

	/* Don't check अगर driver करोes not require it */
	अगर (!req_rev || !filename)
		वापस 0;

	/* Don't check if devlink 'fw_load_policy' param is 'flash' */
	err = devlink_param_driverinit_value_get(priv_to_devlink(mlxsw_core),
						 DEVLINK_PARAM_GENERIC_ID_FW_LOAD_POLICY,
						 &value);
	अगर (err)
		वापस err;
	अगर (value.vu8 == DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_FLASH)
		वापस 0;

	/* Validate driver & FW are compatible */
	अगर (rev->major != req_rev->major) अणु
		WARN(1, "Mismatch in major FW version [%d:%d] is never expected; Please contact support\n",
		     rev->major, req_rev->major);
		वापस -EINVAL;
	पूर्ण
	अगर (mlxsw_core_fw_rev_minor_subminor_validate(rev, req_rev))
		वापस 0;

	dev_err(mlxsw_bus_info->dev, "The firmware version %d.%d.%d is incompatible with the driver (required >= %d.%d.%d)\n",
		rev->major, rev->minor, rev->subminor, req_rev->major,
		req_rev->minor, req_rev->subminor);
	dev_info(mlxsw_bus_info->dev, "Flashing firmware using file %s\n", filename);

	err = request_firmware_direct(&firmware, filename, mlxsw_bus_info->dev);
	अगर (err) अणु
		dev_err(mlxsw_bus_info->dev, "Could not request firmware file %s\n", filename);
		वापस err;
	पूर्ण

	err = mlxsw_core_fw_flash(mlxsw_core, firmware, शून्य);
	release_firmware(firmware);
	अगर (err)
		dev_err(mlxsw_bus_info->dev, "Could not upgrade firmware\n");

	/* On FW flash success, tell the caller FW reset is needed
	 * अगर current FW supports it.
	 */
	अगर (rev->minor >= req_rev->can_reset_minor)
		वापस err ? err : -EAGAIN;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_core_fw_flash_update(काष्ठा mlxsw_core *mlxsw_core,
				      काष्ठा devlink_flash_update_params *params,
				      काष्ठा netlink_ext_ack *extack)
अणु
	वापस mlxsw_core_fw_flash(mlxsw_core, params->fw, extack);
पूर्ण

अटल पूर्णांक mlxsw_core_devlink_param_fw_load_policy_validate(काष्ठा devlink *devlink, u32 id,
							    जोड़ devlink_param_value val,
							    काष्ठा netlink_ext_ack *extack)
अणु
	अगर (val.vu8 != DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_DRIVER &&
	    val.vu8 != DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_FLASH) अणु
		NL_SET_ERR_MSG_MOD(extack, "'fw_load_policy' must be 'driver' or 'flash'");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा devlink_param mlxsw_core_fw_devlink_params[] = अणु
	DEVLINK_PARAM_GENERIC(FW_LOAD_POLICY, BIT(DEVLINK_PARAM_CMODE_DRIVERINIT), शून्य, शून्य,
			      mlxsw_core_devlink_param_fw_load_policy_validate),
पूर्ण;

अटल पूर्णांक mlxsw_core_fw_params_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_core);
	जोड़ devlink_param_value value;
	पूर्णांक err;

	err = devlink_params_रेजिस्टर(devlink, mlxsw_core_fw_devlink_params,
				      ARRAY_SIZE(mlxsw_core_fw_devlink_params));
	अगर (err)
		वापस err;

	value.vu8 = DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_DRIVER;
	devlink_param_driverinit_value_set(devlink, DEVLINK_PARAM_GENERIC_ID_FW_LOAD_POLICY, value);
	वापस 0;
पूर्ण

अटल व्योम mlxsw_core_fw_params_unरेजिस्टर(काष्ठा mlxsw_core *mlxsw_core)
अणु
	devlink_params_unरेजिस्टर(priv_to_devlink(mlxsw_core), mlxsw_core_fw_devlink_params,
				  ARRAY_SIZE(mlxsw_core_fw_devlink_params));
पूर्ण

अटल पूर्णांक mlxsw_devlink_port_split(काष्ठा devlink *devlink,
				    अचिन्हित पूर्णांक port_index,
				    अचिन्हित पूर्णांक count,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink);

	अगर (port_index >= mlxsw_core->max_ports) अणु
		NL_SET_ERR_MSG_MOD(extack, "Port index exceeds maximum number of ports");
		वापस -EINVAL;
	पूर्ण
	अगर (!mlxsw_core->driver->port_split)
		वापस -EOPNOTSUPP;
	वापस mlxsw_core->driver->port_split(mlxsw_core, port_index, count,
					      extack);
पूर्ण

अटल पूर्णांक mlxsw_devlink_port_unsplit(काष्ठा devlink *devlink,
				      अचिन्हित पूर्णांक port_index,
				      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink);

	अगर (port_index >= mlxsw_core->max_ports) अणु
		NL_SET_ERR_MSG_MOD(extack, "Port index exceeds maximum number of ports");
		वापस -EINVAL;
	पूर्ण
	अगर (!mlxsw_core->driver->port_unsplit)
		वापस -EOPNOTSUPP;
	वापस mlxsw_core->driver->port_unsplit(mlxsw_core, port_index,
						extack);
पूर्ण

अटल पूर्णांक
mlxsw_devlink_sb_pool_get(काष्ठा devlink *devlink,
			  अचिन्हित पूर्णांक sb_index, u16 pool_index,
			  काष्ठा devlink_sb_pool_info *pool_info)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink);
	काष्ठा mlxsw_driver *mlxsw_driver = mlxsw_core->driver;

	अगर (!mlxsw_driver->sb_pool_get)
		वापस -EOPNOTSUPP;
	वापस mlxsw_driver->sb_pool_get(mlxsw_core, sb_index,
					 pool_index, pool_info);
पूर्ण

अटल पूर्णांक
mlxsw_devlink_sb_pool_set(काष्ठा devlink *devlink,
			  अचिन्हित पूर्णांक sb_index, u16 pool_index, u32 size,
			  क्रमागत devlink_sb_threshold_type threshold_type,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink);
	काष्ठा mlxsw_driver *mlxsw_driver = mlxsw_core->driver;

	अगर (!mlxsw_driver->sb_pool_set)
		वापस -EOPNOTSUPP;
	वापस mlxsw_driver->sb_pool_set(mlxsw_core, sb_index,
					 pool_index, size, threshold_type,
					 extack);
पूर्ण

अटल व्योम *__dl_port(काष्ठा devlink_port *devlink_port)
अणु
	वापस container_of(devlink_port, काष्ठा mlxsw_core_port, devlink_port);
पूर्ण

अटल पूर्णांक mlxsw_devlink_port_type_set(काष्ठा devlink_port *devlink_port,
				       क्रमागत devlink_port_type port_type)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink_port->devlink);
	काष्ठा mlxsw_driver *mlxsw_driver = mlxsw_core->driver;
	काष्ठा mlxsw_core_port *mlxsw_core_port = __dl_port(devlink_port);

	अगर (!mlxsw_driver->port_type_set)
		वापस -EOPNOTSUPP;

	वापस mlxsw_driver->port_type_set(mlxsw_core,
					   mlxsw_core_port->local_port,
					   port_type);
पूर्ण

अटल पूर्णांक mlxsw_devlink_sb_port_pool_get(काष्ठा devlink_port *devlink_port,
					  अचिन्हित पूर्णांक sb_index, u16 pool_index,
					  u32 *p_threshold)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink_port->devlink);
	काष्ठा mlxsw_driver *mlxsw_driver = mlxsw_core->driver;
	काष्ठा mlxsw_core_port *mlxsw_core_port = __dl_port(devlink_port);

	अगर (!mlxsw_driver->sb_port_pool_get ||
	    !mlxsw_core_port_check(mlxsw_core_port))
		वापस -EOPNOTSUPP;
	वापस mlxsw_driver->sb_port_pool_get(mlxsw_core_port, sb_index,
					      pool_index, p_threshold);
पूर्ण

अटल पूर्णांक mlxsw_devlink_sb_port_pool_set(काष्ठा devlink_port *devlink_port,
					  अचिन्हित पूर्णांक sb_index, u16 pool_index,
					  u32 threshold,
					  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink_port->devlink);
	काष्ठा mlxsw_driver *mlxsw_driver = mlxsw_core->driver;
	काष्ठा mlxsw_core_port *mlxsw_core_port = __dl_port(devlink_port);

	अगर (!mlxsw_driver->sb_port_pool_set ||
	    !mlxsw_core_port_check(mlxsw_core_port))
		वापस -EOPNOTSUPP;
	वापस mlxsw_driver->sb_port_pool_set(mlxsw_core_port, sb_index,
					      pool_index, threshold, extack);
पूर्ण

अटल पूर्णांक
mlxsw_devlink_sb_tc_pool_bind_get(काष्ठा devlink_port *devlink_port,
				  अचिन्हित पूर्णांक sb_index, u16 tc_index,
				  क्रमागत devlink_sb_pool_type pool_type,
				  u16 *p_pool_index, u32 *p_threshold)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink_port->devlink);
	काष्ठा mlxsw_driver *mlxsw_driver = mlxsw_core->driver;
	काष्ठा mlxsw_core_port *mlxsw_core_port = __dl_port(devlink_port);

	अगर (!mlxsw_driver->sb_tc_pool_bind_get ||
	    !mlxsw_core_port_check(mlxsw_core_port))
		वापस -EOPNOTSUPP;
	वापस mlxsw_driver->sb_tc_pool_bind_get(mlxsw_core_port, sb_index,
						 tc_index, pool_type,
						 p_pool_index, p_threshold);
पूर्ण

अटल पूर्णांक
mlxsw_devlink_sb_tc_pool_bind_set(काष्ठा devlink_port *devlink_port,
				  अचिन्हित पूर्णांक sb_index, u16 tc_index,
				  क्रमागत devlink_sb_pool_type pool_type,
				  u16 pool_index, u32 threshold,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink_port->devlink);
	काष्ठा mlxsw_driver *mlxsw_driver = mlxsw_core->driver;
	काष्ठा mlxsw_core_port *mlxsw_core_port = __dl_port(devlink_port);

	अगर (!mlxsw_driver->sb_tc_pool_bind_set ||
	    !mlxsw_core_port_check(mlxsw_core_port))
		वापस -EOPNOTSUPP;
	वापस mlxsw_driver->sb_tc_pool_bind_set(mlxsw_core_port, sb_index,
						 tc_index, pool_type,
						 pool_index, threshold, extack);
पूर्ण

अटल पूर्णांक mlxsw_devlink_sb_occ_snapshot(काष्ठा devlink *devlink,
					 अचिन्हित पूर्णांक sb_index)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink);
	काष्ठा mlxsw_driver *mlxsw_driver = mlxsw_core->driver;

	अगर (!mlxsw_driver->sb_occ_snapshot)
		वापस -EOPNOTSUPP;
	वापस mlxsw_driver->sb_occ_snapshot(mlxsw_core, sb_index);
पूर्ण

अटल पूर्णांक mlxsw_devlink_sb_occ_max_clear(काष्ठा devlink *devlink,
					  अचिन्हित पूर्णांक sb_index)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink);
	काष्ठा mlxsw_driver *mlxsw_driver = mlxsw_core->driver;

	अगर (!mlxsw_driver->sb_occ_max_clear)
		वापस -EOPNOTSUPP;
	वापस mlxsw_driver->sb_occ_max_clear(mlxsw_core, sb_index);
पूर्ण

अटल पूर्णांक
mlxsw_devlink_sb_occ_port_pool_get(काष्ठा devlink_port *devlink_port,
				   अचिन्हित पूर्णांक sb_index, u16 pool_index,
				   u32 *p_cur, u32 *p_max)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink_port->devlink);
	काष्ठा mlxsw_driver *mlxsw_driver = mlxsw_core->driver;
	काष्ठा mlxsw_core_port *mlxsw_core_port = __dl_port(devlink_port);

	अगर (!mlxsw_driver->sb_occ_port_pool_get ||
	    !mlxsw_core_port_check(mlxsw_core_port))
		वापस -EOPNOTSUPP;
	वापस mlxsw_driver->sb_occ_port_pool_get(mlxsw_core_port, sb_index,
						  pool_index, p_cur, p_max);
पूर्ण

अटल पूर्णांक
mlxsw_devlink_sb_occ_tc_port_bind_get(काष्ठा devlink_port *devlink_port,
				      अचिन्हित पूर्णांक sb_index, u16 tc_index,
				      क्रमागत devlink_sb_pool_type pool_type,
				      u32 *p_cur, u32 *p_max)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink_port->devlink);
	काष्ठा mlxsw_driver *mlxsw_driver = mlxsw_core->driver;
	काष्ठा mlxsw_core_port *mlxsw_core_port = __dl_port(devlink_port);

	अगर (!mlxsw_driver->sb_occ_tc_port_bind_get ||
	    !mlxsw_core_port_check(mlxsw_core_port))
		वापस -EOPNOTSUPP;
	वापस mlxsw_driver->sb_occ_tc_port_bind_get(mlxsw_core_port,
						     sb_index, tc_index,
						     pool_type, p_cur, p_max);
पूर्ण

अटल पूर्णांक
mlxsw_devlink_info_get(काष्ठा devlink *devlink, काष्ठा devlink_info_req *req,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink);
	अक्षर fw_info_psid[MLXSW_REG_MGIR_FW_INFO_PSID_SIZE];
	u32 hw_rev, fw_major, fw_minor, fw_sub_minor;
	अक्षर mgir_pl[MLXSW_REG_MGIR_LEN];
	अक्षर buf[32];
	पूर्णांक err;

	err = devlink_info_driver_name_put(req,
					   mlxsw_core->bus_info->device_kind);
	अगर (err)
		वापस err;

	mlxsw_reg_mgir_pack(mgir_pl);
	err = mlxsw_reg_query(mlxsw_core, MLXSW_REG(mgir), mgir_pl);
	अगर (err)
		वापस err;
	mlxsw_reg_mgir_unpack(mgir_pl, &hw_rev, fw_info_psid, &fw_major,
			      &fw_minor, &fw_sub_minor);

	प्र_लिखो(buf, "%X", hw_rev);
	err = devlink_info_version_fixed_put(req, "hw.revision", buf);
	अगर (err)
		वापस err;

	err = devlink_info_version_fixed_put(req, "fw.psid", fw_info_psid);
	अगर (err)
		वापस err;

	प्र_लिखो(buf, "%d.%d.%d", fw_major, fw_minor, fw_sub_minor);
	err = devlink_info_version_running_put(req, "fw.version", buf);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_devlink_core_bus_device_reload_करोwn(काष्ठा devlink *devlink,
					  bool netns_change, क्रमागत devlink_reload_action action,
					  क्रमागत devlink_reload_limit limit,
					  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink);

	अगर (!(mlxsw_core->bus->features & MLXSW_BUS_F_RESET))
		वापस -EOPNOTSUPP;

	mlxsw_core_bus_device_unरेजिस्टर(mlxsw_core, true);
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_devlink_core_bus_device_reload_up(काष्ठा devlink *devlink, क्रमागत devlink_reload_action action,
					क्रमागत devlink_reload_limit limit, u32 *actions_perक्रमmed,
					काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink);

	*actions_perक्रमmed = BIT(DEVLINK_RELOAD_ACTION_DRIVER_REINIT) |
			     BIT(DEVLINK_RELOAD_ACTION_FW_ACTIVATE);
	वापस mlxsw_core_bus_device_रेजिस्टर(mlxsw_core->bus_info,
					      mlxsw_core->bus,
					      mlxsw_core->bus_priv, true,
					      devlink, extack);
पूर्ण

अटल पूर्णांक mlxsw_devlink_flash_update(काष्ठा devlink *devlink,
				      काष्ठा devlink_flash_update_params *params,
				      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink);

	वापस mlxsw_core_fw_flash_update(mlxsw_core, params, extack);
पूर्ण

अटल पूर्णांक mlxsw_devlink_trap_init(काष्ठा devlink *devlink,
				   स्थिर काष्ठा devlink_trap *trap,
				   व्योम *trap_ctx)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink);
	काष्ठा mlxsw_driver *mlxsw_driver = mlxsw_core->driver;

	अगर (!mlxsw_driver->trap_init)
		वापस -EOPNOTSUPP;
	वापस mlxsw_driver->trap_init(mlxsw_core, trap, trap_ctx);
पूर्ण

अटल व्योम mlxsw_devlink_trap_fini(काष्ठा devlink *devlink,
				    स्थिर काष्ठा devlink_trap *trap,
				    व्योम *trap_ctx)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink);
	काष्ठा mlxsw_driver *mlxsw_driver = mlxsw_core->driver;

	अगर (!mlxsw_driver->trap_fini)
		वापस;
	mlxsw_driver->trap_fini(mlxsw_core, trap, trap_ctx);
पूर्ण

अटल पूर्णांक mlxsw_devlink_trap_action_set(काष्ठा devlink *devlink,
					 स्थिर काष्ठा devlink_trap *trap,
					 क्रमागत devlink_trap_action action,
					 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink);
	काष्ठा mlxsw_driver *mlxsw_driver = mlxsw_core->driver;

	अगर (!mlxsw_driver->trap_action_set)
		वापस -EOPNOTSUPP;
	वापस mlxsw_driver->trap_action_set(mlxsw_core, trap, action, extack);
पूर्ण

अटल पूर्णांक
mlxsw_devlink_trap_group_init(काष्ठा devlink *devlink,
			      स्थिर काष्ठा devlink_trap_group *group)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink);
	काष्ठा mlxsw_driver *mlxsw_driver = mlxsw_core->driver;

	अगर (!mlxsw_driver->trap_group_init)
		वापस -EOPNOTSUPP;
	वापस mlxsw_driver->trap_group_init(mlxsw_core, group);
पूर्ण

अटल पूर्णांक
mlxsw_devlink_trap_group_set(काष्ठा devlink *devlink,
			     स्थिर काष्ठा devlink_trap_group *group,
			     स्थिर काष्ठा devlink_trap_policer *policer,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink);
	काष्ठा mlxsw_driver *mlxsw_driver = mlxsw_core->driver;

	अगर (!mlxsw_driver->trap_group_set)
		वापस -EOPNOTSUPP;
	वापस mlxsw_driver->trap_group_set(mlxsw_core, group, policer, extack);
पूर्ण

अटल पूर्णांक
mlxsw_devlink_trap_policer_init(काष्ठा devlink *devlink,
				स्थिर काष्ठा devlink_trap_policer *policer)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink);
	काष्ठा mlxsw_driver *mlxsw_driver = mlxsw_core->driver;

	अगर (!mlxsw_driver->trap_policer_init)
		वापस -EOPNOTSUPP;
	वापस mlxsw_driver->trap_policer_init(mlxsw_core, policer);
पूर्ण

अटल व्योम
mlxsw_devlink_trap_policer_fini(काष्ठा devlink *devlink,
				स्थिर काष्ठा devlink_trap_policer *policer)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink);
	काष्ठा mlxsw_driver *mlxsw_driver = mlxsw_core->driver;

	अगर (!mlxsw_driver->trap_policer_fini)
		वापस;
	mlxsw_driver->trap_policer_fini(mlxsw_core, policer);
पूर्ण

अटल पूर्णांक
mlxsw_devlink_trap_policer_set(काष्ठा devlink *devlink,
			       स्थिर काष्ठा devlink_trap_policer *policer,
			       u64 rate, u64 burst,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink);
	काष्ठा mlxsw_driver *mlxsw_driver = mlxsw_core->driver;

	अगर (!mlxsw_driver->trap_policer_set)
		वापस -EOPNOTSUPP;
	वापस mlxsw_driver->trap_policer_set(mlxsw_core, policer, rate, burst,
					      extack);
पूर्ण

अटल पूर्णांक
mlxsw_devlink_trap_policer_counter_get(काष्ठा devlink *devlink,
				       स्थिर काष्ठा devlink_trap_policer *policer,
				       u64 *p_drops)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_priv(devlink);
	काष्ठा mlxsw_driver *mlxsw_driver = mlxsw_core->driver;

	अगर (!mlxsw_driver->trap_policer_counter_get)
		वापस -EOPNOTSUPP;
	वापस mlxsw_driver->trap_policer_counter_get(mlxsw_core, policer,
						      p_drops);
पूर्ण

अटल स्थिर काष्ठा devlink_ops mlxsw_devlink_ops = अणु
	.reload_actions		= BIT(DEVLINK_RELOAD_ACTION_DRIVER_REINIT) |
				  BIT(DEVLINK_RELOAD_ACTION_FW_ACTIVATE),
	.reload_करोwn		= mlxsw_devlink_core_bus_device_reload_करोwn,
	.reload_up		= mlxsw_devlink_core_bus_device_reload_up,
	.port_type_set			= mlxsw_devlink_port_type_set,
	.port_split			= mlxsw_devlink_port_split,
	.port_unsplit			= mlxsw_devlink_port_unsplit,
	.sb_pool_get			= mlxsw_devlink_sb_pool_get,
	.sb_pool_set			= mlxsw_devlink_sb_pool_set,
	.sb_port_pool_get		= mlxsw_devlink_sb_port_pool_get,
	.sb_port_pool_set		= mlxsw_devlink_sb_port_pool_set,
	.sb_tc_pool_bind_get		= mlxsw_devlink_sb_tc_pool_bind_get,
	.sb_tc_pool_bind_set		= mlxsw_devlink_sb_tc_pool_bind_set,
	.sb_occ_snapshot		= mlxsw_devlink_sb_occ_snapshot,
	.sb_occ_max_clear		= mlxsw_devlink_sb_occ_max_clear,
	.sb_occ_port_pool_get		= mlxsw_devlink_sb_occ_port_pool_get,
	.sb_occ_tc_port_bind_get	= mlxsw_devlink_sb_occ_tc_port_bind_get,
	.info_get			= mlxsw_devlink_info_get,
	.flash_update			= mlxsw_devlink_flash_update,
	.trap_init			= mlxsw_devlink_trap_init,
	.trap_fini			= mlxsw_devlink_trap_fini,
	.trap_action_set		= mlxsw_devlink_trap_action_set,
	.trap_group_init		= mlxsw_devlink_trap_group_init,
	.trap_group_set			= mlxsw_devlink_trap_group_set,
	.trap_policer_init		= mlxsw_devlink_trap_policer_init,
	.trap_policer_fini		= mlxsw_devlink_trap_policer_fini,
	.trap_policer_set		= mlxsw_devlink_trap_policer_set,
	.trap_policer_counter_get	= mlxsw_devlink_trap_policer_counter_get,
पूर्ण;

अटल पूर्णांक mlxsw_core_params_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core)
अणु
	पूर्णांक err;

	err = mlxsw_core_fw_params_रेजिस्टर(mlxsw_core);
	अगर (err)
		वापस err;

	अगर (mlxsw_core->driver->params_रेजिस्टर) अणु
		err = mlxsw_core->driver->params_रेजिस्टर(mlxsw_core);
		अगर (err)
			जाओ err_params_रेजिस्टर;
	पूर्ण
	वापस 0;

err_params_रेजिस्टर:
	mlxsw_core_fw_params_unरेजिस्टर(mlxsw_core);
	वापस err;
पूर्ण

अटल व्योम mlxsw_core_params_unरेजिस्टर(काष्ठा mlxsw_core *mlxsw_core)
अणु
	mlxsw_core_fw_params_unरेजिस्टर(mlxsw_core);
	अगर (mlxsw_core->driver->params_रेजिस्टर)
		mlxsw_core->driver->params_unरेजिस्टर(mlxsw_core);
पूर्ण

काष्ठा mlxsw_core_health_event अणु
	काष्ठा mlxsw_core *mlxsw_core;
	अक्षर mfde_pl[MLXSW_REG_MFDE_LEN];
	काष्ठा work_काष्ठा work;
पूर्ण;

अटल व्योम mlxsw_core_health_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxsw_core_health_event *event;
	काष्ठा mlxsw_core *mlxsw_core;

	event = container_of(work, काष्ठा mlxsw_core_health_event, work);
	mlxsw_core = event->mlxsw_core;
	devlink_health_report(mlxsw_core->health.fw_fatal, "FW fatal event occurred",
			      event->mfde_pl);
	kमुक्त(event);
पूर्ण

अटल व्योम mlxsw_core_health_listener_func(स्थिर काष्ठा mlxsw_reg_info *reg,
					    अक्षर *mfde_pl, व्योम *priv)
अणु
	काष्ठा mlxsw_core_health_event *event;
	काष्ठा mlxsw_core *mlxsw_core = priv;

	event = kदो_स्मृति(माप(*event), GFP_ATOMIC);
	अगर (!event)
		वापस;
	event->mlxsw_core = mlxsw_core;
	स_नकल(event->mfde_pl, mfde_pl, माप(event->mfde_pl));
	INIT_WORK(&event->work, mlxsw_core_health_event_work);
	mlxsw_core_schedule_work(&event->work);
पूर्ण

अटल स्थिर काष्ठा mlxsw_listener mlxsw_core_health_listener =
	MLXSW_EVENTL(mlxsw_core_health_listener_func, MFDE, MFDE);

अटल पूर्णांक mlxsw_core_health_fw_fatal_dump(काष्ठा devlink_health_reporter *reporter,
					   काष्ठा devlink_fmsg *fmsg, व्योम *priv_ctx,
					   काष्ठा netlink_ext_ack *extack)
अणु
	अक्षर *mfde_pl = priv_ctx;
	अक्षर *val_str;
	u8 event_id;
	u32 val;
	पूर्णांक err;

	अगर (!priv_ctx)
		/* User-triggered dumps are not possible */
		वापस -EOPNOTSUPP;

	val = mlxsw_reg_mfde_irisc_id_get(mfde_pl);
	err = devlink_fmsg_u8_pair_put(fmsg, "irisc_id", val);
	अगर (err)
		वापस err;
	err = devlink_fmsg_arr_pair_nest_start(fmsg, "event");
	अगर (err)
		वापस err;

	event_id = mlxsw_reg_mfde_event_id_get(mfde_pl);
	err = devlink_fmsg_u32_pair_put(fmsg, "id", event_id);
	अगर (err)
		वापस err;
	चयन (event_id) अणु
	हाल MLXSW_REG_MFDE_EVENT_ID_CRSPACE_TO:
		val_str = "CR space timeout";
		अवरोध;
	हाल MLXSW_REG_MFDE_EVENT_ID_KVD_IM_STOP:
		val_str = "KVD insertion machine stopped";
		अवरोध;
	शेष:
		val_str = शून्य;
	पूर्ण
	अगर (val_str) अणु
		err = devlink_fmsg_string_pair_put(fmsg, "desc", val_str);
		अगर (err)
			वापस err;
	पूर्ण
	err = devlink_fmsg_arr_pair_nest_end(fmsg);
	अगर (err)
		वापस err;

	val = mlxsw_reg_mfde_method_get(mfde_pl);
	चयन (val) अणु
	हाल MLXSW_REG_MFDE_METHOD_QUERY:
		val_str = "query";
		अवरोध;
	हाल MLXSW_REG_MFDE_METHOD_WRITE:
		val_str = "write";
		अवरोध;
	शेष:
		val_str = शून्य;
	पूर्ण
	अगर (val_str) अणु
		err = devlink_fmsg_string_pair_put(fmsg, "method", val_str);
		अगर (err)
			वापस err;
	पूर्ण

	val = mlxsw_reg_mfde_दीर्घ_process_get(mfde_pl);
	err = devlink_fmsg_bool_pair_put(fmsg, "long_process", val);
	अगर (err)
		वापस err;

	val = mlxsw_reg_mfde_command_type_get(mfde_pl);
	चयन (val) अणु
	हाल MLXSW_REG_MFDE_COMMAND_TYPE_MAD:
		val_str = "mad";
		अवरोध;
	हाल MLXSW_REG_MFDE_COMMAND_TYPE_EMAD:
		val_str = "emad";
		अवरोध;
	हाल MLXSW_REG_MFDE_COMMAND_TYPE_CMDIF:
		val_str = "cmdif";
		अवरोध;
	शेष:
		val_str = शून्य;
	पूर्ण
	अगर (val_str) अणु
		err = devlink_fmsg_string_pair_put(fmsg, "command_type", val_str);
		अगर (err)
			वापस err;
	पूर्ण

	val = mlxsw_reg_mfde_reg_attr_id_get(mfde_pl);
	err = devlink_fmsg_u32_pair_put(fmsg, "reg_attr_id", val);
	अगर (err)
		वापस err;

	अगर (event_id == MLXSW_REG_MFDE_EVENT_ID_CRSPACE_TO) अणु
		val = mlxsw_reg_mfde_log_address_get(mfde_pl);
		err = devlink_fmsg_u32_pair_put(fmsg, "log_address", val);
		अगर (err)
			वापस err;
		val = mlxsw_reg_mfde_log_id_get(mfde_pl);
		err = devlink_fmsg_u8_pair_put(fmsg, "log_irisc_id", val);
		अगर (err)
			वापस err;
		val = mlxsw_reg_mfde_log_ip_get(mfde_pl);
		err = devlink_fmsg_u64_pair_put(fmsg, "log_ip", val);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (event_id == MLXSW_REG_MFDE_EVENT_ID_KVD_IM_STOP) अणु
		val = mlxsw_reg_mfde_pipes_mask_get(mfde_pl);
		err = devlink_fmsg_u32_pair_put(fmsg, "pipes_mask", val);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_core_health_fw_fatal_test(काष्ठा devlink_health_reporter *reporter,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_core *mlxsw_core = devlink_health_reporter_priv(reporter);
	अक्षर mfgd_pl[MLXSW_REG_MFGD_LEN];
	पूर्णांक err;

	/* Read the रेजिस्टर first to make sure no other bits are changed. */
	err = mlxsw_reg_query(mlxsw_core, MLXSW_REG(mfgd), mfgd_pl);
	अगर (err)
		वापस err;
	mlxsw_reg_mfgd_trigger_test_set(mfgd_pl, true);
	वापस mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(mfgd), mfgd_pl);
पूर्ण

अटल स्थिर काष्ठा devlink_health_reporter_ops
mlxsw_core_health_fw_fatal_ops = अणु
	.name = "fw_fatal",
	.dump = mlxsw_core_health_fw_fatal_dump,
	.test = mlxsw_core_health_fw_fatal_test,
पूर्ण;

अटल पूर्णांक mlxsw_core_health_fw_fatal_config(काष्ठा mlxsw_core *mlxsw_core,
					     bool enable)
अणु
	अक्षर mfgd_pl[MLXSW_REG_MFGD_LEN];
	पूर्णांक err;

	/* Read the रेजिस्टर first to make sure no other bits are changed. */
	err = mlxsw_reg_query(mlxsw_core, MLXSW_REG(mfgd), mfgd_pl);
	अगर (err)
		वापस err;
	mlxsw_reg_mfgd_fatal_event_mode_set(mfgd_pl, enable);
	वापस mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(mfgd), mfgd_pl);
पूर्ण

अटल पूर्णांक mlxsw_core_health_init(काष्ठा mlxsw_core *mlxsw_core)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_core);
	काष्ठा devlink_health_reporter *fw_fatal;
	पूर्णांक err;

	अगर (!mlxsw_core->driver->fw_fatal_enabled)
		वापस 0;

	fw_fatal = devlink_health_reporter_create(devlink, &mlxsw_core_health_fw_fatal_ops,
						  0, mlxsw_core);
	अगर (IS_ERR(fw_fatal)) अणु
		dev_err(mlxsw_core->bus_info->dev, "Failed to create fw fatal reporter");
		वापस PTR_ERR(fw_fatal);
	पूर्ण
	mlxsw_core->health.fw_fatal = fw_fatal;

	err = mlxsw_core_trap_रेजिस्टर(mlxsw_core, &mlxsw_core_health_listener, mlxsw_core);
	अगर (err)
		जाओ err_trap_रेजिस्टर;

	err = mlxsw_core_health_fw_fatal_config(mlxsw_core, true);
	अगर (err)
		जाओ err_fw_fatal_config;

	वापस 0;

err_fw_fatal_config:
	mlxsw_core_trap_unरेजिस्टर(mlxsw_core, &mlxsw_core_health_listener, mlxsw_core);
err_trap_रेजिस्टर:
	devlink_health_reporter_destroy(mlxsw_core->health.fw_fatal);
	वापस err;
पूर्ण

अटल व्योम mlxsw_core_health_fini(काष्ठा mlxsw_core *mlxsw_core)
अणु
	अगर (!mlxsw_core->driver->fw_fatal_enabled)
		वापस;

	mlxsw_core_health_fw_fatal_config(mlxsw_core, false);
	mlxsw_core_trap_unरेजिस्टर(mlxsw_core, &mlxsw_core_health_listener, mlxsw_core);
	/* Make sure there is no more event work scheduled */
	mlxsw_core_flush_owq();
	devlink_health_reporter_destroy(mlxsw_core->health.fw_fatal);
पूर्ण

अटल पूर्णांक
__mlxsw_core_bus_device_रेजिस्टर(स्थिर काष्ठा mlxsw_bus_info *mlxsw_bus_info,
				 स्थिर काष्ठा mlxsw_bus *mlxsw_bus,
				 व्योम *bus_priv, bool reload,
				 काष्ठा devlink *devlink,
				 काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर अक्षर *device_kind = mlxsw_bus_info->device_kind;
	काष्ठा mlxsw_core *mlxsw_core;
	काष्ठा mlxsw_driver *mlxsw_driver;
	काष्ठा mlxsw_res *res;
	माप_प्रकार alloc_size;
	पूर्णांक err;

	mlxsw_driver = mlxsw_core_driver_get(device_kind);
	अगर (!mlxsw_driver)
		वापस -EINVAL;

	अगर (!reload) अणु
		alloc_size = माप(*mlxsw_core) + mlxsw_driver->priv_size;
		devlink = devlink_alloc(&mlxsw_devlink_ops, alloc_size);
		अगर (!devlink) अणु
			err = -ENOMEM;
			जाओ err_devlink_alloc;
		पूर्ण
	पूर्ण

	mlxsw_core = devlink_priv(devlink);
	INIT_LIST_HEAD(&mlxsw_core->rx_listener_list);
	INIT_LIST_HEAD(&mlxsw_core->event_listener_list);
	mlxsw_core->driver = mlxsw_driver;
	mlxsw_core->bus = mlxsw_bus;
	mlxsw_core->bus_priv = bus_priv;
	mlxsw_core->bus_info = mlxsw_bus_info;

	res = mlxsw_driver->res_query_enabled ? &mlxsw_core->res : शून्य;
	err = mlxsw_bus->init(bus_priv, mlxsw_core, mlxsw_driver->profile, res);
	अगर (err)
		जाओ err_bus_init;

	अगर (mlxsw_driver->resources_रेजिस्टर && !reload) अणु
		err = mlxsw_driver->resources_रेजिस्टर(mlxsw_core);
		अगर (err)
			जाओ err_रेजिस्टर_resources;
	पूर्ण

	err = mlxsw_ports_init(mlxsw_core, reload);
	अगर (err)
		जाओ err_ports_init;

	अगर (MLXSW_CORE_RES_VALID(mlxsw_core, MAX_LAG) &&
	    MLXSW_CORE_RES_VALID(mlxsw_core, MAX_LAG_MEMBERS)) अणु
		alloc_size = माप(u8) *
			MLXSW_CORE_RES_GET(mlxsw_core, MAX_LAG) *
			MLXSW_CORE_RES_GET(mlxsw_core, MAX_LAG_MEMBERS);
		mlxsw_core->lag.mapping = kzalloc(alloc_size, GFP_KERNEL);
		अगर (!mlxsw_core->lag.mapping) अणु
			err = -ENOMEM;
			जाओ err_alloc_lag_mapping;
		पूर्ण
	पूर्ण

	err = mlxsw_emad_init(mlxsw_core);
	अगर (err)
		जाओ err_emad_init;

	अगर (!reload) अणु
		err = devlink_रेजिस्टर(devlink, mlxsw_bus_info->dev);
		अगर (err)
			जाओ err_devlink_रेजिस्टर;
	पूर्ण

	अगर (!reload) अणु
		err = mlxsw_core_params_रेजिस्टर(mlxsw_core);
		अगर (err)
			जाओ err_रेजिस्टर_params;
	पूर्ण

	err = mlxsw_core_fw_rev_validate(mlxsw_core, mlxsw_bus_info, mlxsw_driver->fw_req_rev,
					 mlxsw_driver->fw_filename);
	अगर (err)
		जाओ err_fw_rev_validate;

	err = mlxsw_core_health_init(mlxsw_core);
	अगर (err)
		जाओ err_health_init;

	अगर (mlxsw_driver->init) अणु
		err = mlxsw_driver->init(mlxsw_core, mlxsw_bus_info, extack);
		अगर (err)
			जाओ err_driver_init;
	पूर्ण

	err = mlxsw_hwmon_init(mlxsw_core, mlxsw_bus_info, &mlxsw_core->hwmon);
	अगर (err)
		जाओ err_hwmon_init;

	err = mlxsw_thermal_init(mlxsw_core, mlxsw_bus_info,
				 &mlxsw_core->thermal);
	अगर (err)
		जाओ err_thermal_init;

	err = mlxsw_env_init(mlxsw_core, &mlxsw_core->env);
	अगर (err)
		जाओ err_env_init;

	mlxsw_core->is_initialized = true;
	devlink_params_publish(devlink);

	अगर (!reload)
		devlink_reload_enable(devlink);

	वापस 0;

err_env_init:
	mlxsw_thermal_fini(mlxsw_core->thermal);
err_thermal_init:
	mlxsw_hwmon_fini(mlxsw_core->hwmon);
err_hwmon_init:
	अगर (mlxsw_core->driver->fini)
		mlxsw_core->driver->fini(mlxsw_core);
err_driver_init:
	mlxsw_core_health_fini(mlxsw_core);
err_health_init:
err_fw_rev_validate:
	अगर (!reload)
		mlxsw_core_params_unरेजिस्टर(mlxsw_core);
err_रेजिस्टर_params:
	अगर (!reload)
		devlink_unरेजिस्टर(devlink);
err_devlink_रेजिस्टर:
	mlxsw_emad_fini(mlxsw_core);
err_emad_init:
	kमुक्त(mlxsw_core->lag.mapping);
err_alloc_lag_mapping:
	mlxsw_ports_fini(mlxsw_core, reload);
err_ports_init:
	अगर (!reload)
		devlink_resources_unरेजिस्टर(devlink, शून्य);
err_रेजिस्टर_resources:
	mlxsw_bus->fini(bus_priv);
err_bus_init:
	अगर (!reload)
		devlink_मुक्त(devlink);
err_devlink_alloc:
	वापस err;
पूर्ण

पूर्णांक mlxsw_core_bus_device_रेजिस्टर(स्थिर काष्ठा mlxsw_bus_info *mlxsw_bus_info,
				   स्थिर काष्ठा mlxsw_bus *mlxsw_bus,
				   व्योम *bus_priv, bool reload,
				   काष्ठा devlink *devlink,
				   काष्ठा netlink_ext_ack *extack)
अणु
	bool called_again = false;
	पूर्णांक err;

again:
	err = __mlxsw_core_bus_device_रेजिस्टर(mlxsw_bus_info, mlxsw_bus,
					       bus_priv, reload,
					       devlink, extack);
	/* -EAGAIN is वापसed in हाल the FW was updated. FW needs
	 * a reset, so lets try to call __mlxsw_core_bus_device_रेजिस्टर()
	 * again.
	 */
	अगर (err == -EAGAIN && !called_again) अणु
		called_again = true;
		जाओ again;
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL(mlxsw_core_bus_device_रेजिस्टर);

व्योम mlxsw_core_bus_device_unरेजिस्टर(काष्ठा mlxsw_core *mlxsw_core,
				      bool reload)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_core);

	अगर (!reload)
		devlink_reload_disable(devlink);
	अगर (devlink_is_reload_failed(devlink)) अणु
		अगर (!reload)
			/* Only the parts that were not de-initialized in the
			 * failed reload attempt need to be de-initialized.
			 */
			जाओ reload_fail_deinit;
		अन्यथा
			वापस;
	पूर्ण

	devlink_params_unpublish(devlink);
	mlxsw_core->is_initialized = false;
	mlxsw_env_fini(mlxsw_core->env);
	mlxsw_thermal_fini(mlxsw_core->thermal);
	mlxsw_hwmon_fini(mlxsw_core->hwmon);
	अगर (mlxsw_core->driver->fini)
		mlxsw_core->driver->fini(mlxsw_core);
	mlxsw_core_health_fini(mlxsw_core);
	अगर (!reload)
		mlxsw_core_params_unरेजिस्टर(mlxsw_core);
	अगर (!reload)
		devlink_unरेजिस्टर(devlink);
	mlxsw_emad_fini(mlxsw_core);
	kमुक्त(mlxsw_core->lag.mapping);
	mlxsw_ports_fini(mlxsw_core, reload);
	अगर (!reload)
		devlink_resources_unरेजिस्टर(devlink, शून्य);
	mlxsw_core->bus->fini(mlxsw_core->bus_priv);
	अगर (!reload)
		devlink_मुक्त(devlink);

	वापस;

reload_fail_deinit:
	mlxsw_core_params_unरेजिस्टर(mlxsw_core);
	devlink_unरेजिस्टर(devlink);
	devlink_resources_unरेजिस्टर(devlink, शून्य);
	devlink_मुक्त(devlink);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_bus_device_unरेजिस्टर);

bool mlxsw_core_skb_transmit_busy(काष्ठा mlxsw_core *mlxsw_core,
				  स्थिर काष्ठा mlxsw_tx_info *tx_info)
अणु
	वापस mlxsw_core->bus->skb_transmit_busy(mlxsw_core->bus_priv,
						  tx_info);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_skb_transmit_busy);

पूर्णांक mlxsw_core_skb_transmit(काष्ठा mlxsw_core *mlxsw_core, काष्ठा sk_buff *skb,
			    स्थिर काष्ठा mlxsw_tx_info *tx_info)
अणु
	वापस mlxsw_core->bus->skb_transmit(mlxsw_core->bus_priv, skb,
					     tx_info);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_skb_transmit);

व्योम mlxsw_core_ptp_transmitted(काष्ठा mlxsw_core *mlxsw_core,
				काष्ठा sk_buff *skb, u8 local_port)
अणु
	अगर (mlxsw_core->driver->ptp_transmitted)
		mlxsw_core->driver->ptp_transmitted(mlxsw_core, skb,
						    local_port);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_ptp_transmitted);

अटल bool __is_rx_listener_equal(स्थिर काष्ठा mlxsw_rx_listener *rxl_a,
				   स्थिर काष्ठा mlxsw_rx_listener *rxl_b)
अणु
	वापस (rxl_a->func == rxl_b->func &&
		rxl_a->local_port == rxl_b->local_port &&
		rxl_a->trap_id == rxl_b->trap_id &&
		rxl_a->mirror_reason == rxl_b->mirror_reason);
पूर्ण

अटल काष्ठा mlxsw_rx_listener_item *
__find_rx_listener_item(काष्ठा mlxsw_core *mlxsw_core,
			स्थिर काष्ठा mlxsw_rx_listener *rxl)
अणु
	काष्ठा mlxsw_rx_listener_item *rxl_item;

	list_क्रम_each_entry(rxl_item, &mlxsw_core->rx_listener_list, list) अणु
		अगर (__is_rx_listener_equal(&rxl_item->rxl, rxl))
			वापस rxl_item;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक mlxsw_core_rx_listener_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core,
				    स्थिर काष्ठा mlxsw_rx_listener *rxl,
				    व्योम *priv, bool enabled)
अणु
	काष्ठा mlxsw_rx_listener_item *rxl_item;

	rxl_item = __find_rx_listener_item(mlxsw_core, rxl);
	अगर (rxl_item)
		वापस -EEXIST;
	rxl_item = kदो_स्मृति(माप(*rxl_item), GFP_KERNEL);
	अगर (!rxl_item)
		वापस -ENOMEM;
	rxl_item->rxl = *rxl;
	rxl_item->priv = priv;
	rxl_item->enabled = enabled;

	list_add_rcu(&rxl_item->list, &mlxsw_core->rx_listener_list);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlxsw_core_rx_listener_रेजिस्टर);

व्योम mlxsw_core_rx_listener_unरेजिस्टर(काष्ठा mlxsw_core *mlxsw_core,
				       स्थिर काष्ठा mlxsw_rx_listener *rxl)
अणु
	काष्ठा mlxsw_rx_listener_item *rxl_item;

	rxl_item = __find_rx_listener_item(mlxsw_core, rxl);
	अगर (!rxl_item)
		वापस;
	list_del_rcu(&rxl_item->list);
	synchronize_rcu();
	kमुक्त(rxl_item);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_rx_listener_unरेजिस्टर);

अटल व्योम
mlxsw_core_rx_listener_state_set(काष्ठा mlxsw_core *mlxsw_core,
				 स्थिर काष्ठा mlxsw_rx_listener *rxl,
				 bool enabled)
अणु
	काष्ठा mlxsw_rx_listener_item *rxl_item;

	rxl_item = __find_rx_listener_item(mlxsw_core, rxl);
	अगर (WARN_ON(!rxl_item))
		वापस;
	rxl_item->enabled = enabled;
पूर्ण

अटल व्योम mlxsw_core_event_listener_func(काष्ठा sk_buff *skb, u8 local_port,
					   व्योम *priv)
अणु
	काष्ठा mlxsw_event_listener_item *event_listener_item = priv;
	काष्ठा mlxsw_core *mlxsw_core;
	काष्ठा mlxsw_reg_info reg;
	अक्षर *payload;
	अक्षर *reg_tlv;
	अक्षर *op_tlv;

	mlxsw_core = event_listener_item->mlxsw_core;
	trace_devlink_hwmsg(priv_to_devlink(mlxsw_core), true, 0,
			    skb->data, skb->len);

	mlxsw_emad_tlv_parse(skb);
	op_tlv = mlxsw_emad_op_tlv(skb);
	reg_tlv = mlxsw_emad_reg_tlv(skb);

	reg.id = mlxsw_emad_op_tlv_रेजिस्टर_id_get(op_tlv);
	reg.len = (mlxsw_emad_reg_tlv_len_get(reg_tlv) - 1) * माप(u32);
	payload = mlxsw_emad_reg_payload(reg_tlv);
	event_listener_item->el.func(&reg, payload, event_listener_item->priv);
	dev_kमुक्त_skb(skb);
पूर्ण

अटल bool __is_event_listener_equal(स्थिर काष्ठा mlxsw_event_listener *el_a,
				      स्थिर काष्ठा mlxsw_event_listener *el_b)
अणु
	वापस (el_a->func == el_b->func &&
		el_a->trap_id == el_b->trap_id);
पूर्ण

अटल काष्ठा mlxsw_event_listener_item *
__find_event_listener_item(काष्ठा mlxsw_core *mlxsw_core,
			   स्थिर काष्ठा mlxsw_event_listener *el)
अणु
	काष्ठा mlxsw_event_listener_item *el_item;

	list_क्रम_each_entry(el_item, &mlxsw_core->event_listener_list, list) अणु
		अगर (__is_event_listener_equal(&el_item->el, el))
			वापस el_item;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक mlxsw_core_event_listener_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core,
				       स्थिर काष्ठा mlxsw_event_listener *el,
				       व्योम *priv)
अणु
	पूर्णांक err;
	काष्ठा mlxsw_event_listener_item *el_item;
	स्थिर काष्ठा mlxsw_rx_listener rxl = अणु
		.func = mlxsw_core_event_listener_func,
		.local_port = MLXSW_PORT_DONT_CARE,
		.trap_id = el->trap_id,
	पूर्ण;

	el_item = __find_event_listener_item(mlxsw_core, el);
	अगर (el_item)
		वापस -EEXIST;
	el_item = kदो_स्मृति(माप(*el_item), GFP_KERNEL);
	अगर (!el_item)
		वापस -ENOMEM;
	el_item->mlxsw_core = mlxsw_core;
	el_item->el = *el;
	el_item->priv = priv;

	err = mlxsw_core_rx_listener_रेजिस्टर(mlxsw_core, &rxl, el_item, true);
	अगर (err)
		जाओ err_rx_listener_रेजिस्टर;

	/* No reason to save item अगर we did not manage to रेजिस्टर an RX
	 * listener क्रम it.
	 */
	list_add_rcu(&el_item->list, &mlxsw_core->event_listener_list);

	वापस 0;

err_rx_listener_रेजिस्टर:
	kमुक्त(el_item);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlxsw_core_event_listener_रेजिस्टर);

व्योम mlxsw_core_event_listener_unरेजिस्टर(काष्ठा mlxsw_core *mlxsw_core,
					  स्थिर काष्ठा mlxsw_event_listener *el)
अणु
	काष्ठा mlxsw_event_listener_item *el_item;
	स्थिर काष्ठा mlxsw_rx_listener rxl = अणु
		.func = mlxsw_core_event_listener_func,
		.local_port = MLXSW_PORT_DONT_CARE,
		.trap_id = el->trap_id,
	पूर्ण;

	el_item = __find_event_listener_item(mlxsw_core, el);
	अगर (!el_item)
		वापस;
	mlxsw_core_rx_listener_unरेजिस्टर(mlxsw_core, &rxl);
	list_del(&el_item->list);
	kमुक्त(el_item);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_event_listener_unरेजिस्टर);

अटल पूर्णांक mlxsw_core_listener_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core,
					स्थिर काष्ठा mlxsw_listener *listener,
					व्योम *priv, bool enabled)
अणु
	अगर (listener->is_event) अणु
		WARN_ON(!enabled);
		वापस mlxsw_core_event_listener_रेजिस्टर(mlxsw_core,
						&listener->event_listener,
						priv);
	पूर्ण अन्यथा अणु
		वापस mlxsw_core_rx_listener_रेजिस्टर(mlxsw_core,
						&listener->rx_listener,
						priv, enabled);
	पूर्ण
पूर्ण

अटल व्योम mlxsw_core_listener_unरेजिस्टर(काष्ठा mlxsw_core *mlxsw_core,
				      स्थिर काष्ठा mlxsw_listener *listener,
				      व्योम *priv)
अणु
	अगर (listener->is_event)
		mlxsw_core_event_listener_unरेजिस्टर(mlxsw_core,
						     &listener->event_listener);
	अन्यथा
		mlxsw_core_rx_listener_unरेजिस्टर(mlxsw_core,
						  &listener->rx_listener);
पूर्ण

पूर्णांक mlxsw_core_trap_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core,
			     स्थिर काष्ठा mlxsw_listener *listener, व्योम *priv)
अणु
	क्रमागत mlxsw_reg_htgt_trap_group trap_group;
	क्रमागत mlxsw_reg_hpkt_action action;
	अक्षर hpkt_pl[MLXSW_REG_HPKT_LEN];
	पूर्णांक err;

	err = mlxsw_core_listener_रेजिस्टर(mlxsw_core, listener, priv,
					   listener->enabled_on_रेजिस्टर);
	अगर (err)
		वापस err;

	action = listener->enabled_on_रेजिस्टर ? listener->en_action :
						 listener->dis_action;
	trap_group = listener->enabled_on_रेजिस्टर ? listener->en_trap_group :
						     listener->dis_trap_group;
	mlxsw_reg_hpkt_pack(hpkt_pl, action, listener->trap_id,
			    trap_group, listener->is_ctrl);
	err = mlxsw_reg_ग_लिखो(mlxsw_core,  MLXSW_REG(hpkt), hpkt_pl);
	अगर (err)
		जाओ err_trap_set;

	वापस 0;

err_trap_set:
	mlxsw_core_listener_unरेजिस्टर(mlxsw_core, listener, priv);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlxsw_core_trap_रेजिस्टर);

व्योम mlxsw_core_trap_unरेजिस्टर(काष्ठा mlxsw_core *mlxsw_core,
				स्थिर काष्ठा mlxsw_listener *listener,
				व्योम *priv)
अणु
	अक्षर hpkt_pl[MLXSW_REG_HPKT_LEN];

	अगर (!listener->is_event) अणु
		mlxsw_reg_hpkt_pack(hpkt_pl, listener->dis_action,
				    listener->trap_id, listener->dis_trap_group,
				    listener->is_ctrl);
		mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(hpkt), hpkt_pl);
	पूर्ण

	mlxsw_core_listener_unरेजिस्टर(mlxsw_core, listener, priv);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_trap_unरेजिस्टर);

पूर्णांक mlxsw_core_trap_state_set(काष्ठा mlxsw_core *mlxsw_core,
			      स्थिर काष्ठा mlxsw_listener *listener,
			      bool enabled)
अणु
	क्रमागत mlxsw_reg_htgt_trap_group trap_group;
	क्रमागत mlxsw_reg_hpkt_action action;
	अक्षर hpkt_pl[MLXSW_REG_HPKT_LEN];
	पूर्णांक err;

	/* Not supported क्रम event listener */
	अगर (WARN_ON(listener->is_event))
		वापस -EINVAL;

	action = enabled ? listener->en_action : listener->dis_action;
	trap_group = enabled ? listener->en_trap_group :
			       listener->dis_trap_group;
	mlxsw_reg_hpkt_pack(hpkt_pl, action, listener->trap_id,
			    trap_group, listener->is_ctrl);
	err = mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(hpkt), hpkt_pl);
	अगर (err)
		वापस err;

	mlxsw_core_rx_listener_state_set(mlxsw_core, &listener->rx_listener,
					 enabled);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlxsw_core_trap_state_set);

अटल u64 mlxsw_core_tid_get(काष्ठा mlxsw_core *mlxsw_core)
अणु
	वापस atomic64_inc_वापस(&mlxsw_core->emad.tid);
पूर्ण

अटल पूर्णांक mlxsw_core_reg_access_emad(काष्ठा mlxsw_core *mlxsw_core,
				      स्थिर काष्ठा mlxsw_reg_info *reg,
				      अक्षर *payload,
				      क्रमागत mlxsw_core_reg_access_type type,
				      काष्ठा list_head *bulk_list,
				      mlxsw_reg_trans_cb_t *cb,
				      अचिन्हित दीर्घ cb_priv)
अणु
	u64 tid = mlxsw_core_tid_get(mlxsw_core);
	काष्ठा mlxsw_reg_trans *trans;
	पूर्णांक err;

	trans = kzalloc(माप(*trans), GFP_KERNEL);
	अगर (!trans)
		वापस -ENOMEM;

	err = mlxsw_emad_reg_access(mlxsw_core, reg, payload, type, trans,
				    bulk_list, cb, cb_priv, tid);
	अगर (err) अणु
		kमुक्त_rcu(trans, rcu);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक mlxsw_reg_trans_query(काष्ठा mlxsw_core *mlxsw_core,
			  स्थिर काष्ठा mlxsw_reg_info *reg, अक्षर *payload,
			  काष्ठा list_head *bulk_list,
			  mlxsw_reg_trans_cb_t *cb, अचिन्हित दीर्घ cb_priv)
अणु
	वापस mlxsw_core_reg_access_emad(mlxsw_core, reg, payload,
					  MLXSW_CORE_REG_ACCESS_TYPE_QUERY,
					  bulk_list, cb, cb_priv);
पूर्ण
EXPORT_SYMBOL(mlxsw_reg_trans_query);

पूर्णांक mlxsw_reg_trans_ग_लिखो(काष्ठा mlxsw_core *mlxsw_core,
			  स्थिर काष्ठा mlxsw_reg_info *reg, अक्षर *payload,
			  काष्ठा list_head *bulk_list,
			  mlxsw_reg_trans_cb_t *cb, अचिन्हित दीर्घ cb_priv)
अणु
	वापस mlxsw_core_reg_access_emad(mlxsw_core, reg, payload,
					  MLXSW_CORE_REG_ACCESS_TYPE_WRITE,
					  bulk_list, cb, cb_priv);
पूर्ण
EXPORT_SYMBOL(mlxsw_reg_trans_ग_लिखो);

#घोषणा MLXSW_REG_TRANS_ERR_STRING_SIZE	256

अटल पूर्णांक mlxsw_reg_trans_रुको(काष्ठा mlxsw_reg_trans *trans)
अणु
	अक्षर err_string[MLXSW_REG_TRANS_ERR_STRING_SIZE];
	काष्ठा mlxsw_core *mlxsw_core = trans->core;
	पूर्णांक err;

	रुको_क्रम_completion(&trans->completion);
	cancel_delayed_work_sync(&trans->समयout_dw);
	err = trans->err;

	अगर (trans->retries)
		dev_warn(mlxsw_core->bus_info->dev, "EMAD retries (%d/%d) (tid=%llx)\n",
			 trans->retries, MLXSW_EMAD_MAX_RETRY, trans->tid);
	अगर (err) अणु
		dev_err(mlxsw_core->bus_info->dev, "EMAD reg access failed (tid=%llx,reg_id=%x(%s),type=%s,status=%x(%s))\n",
			trans->tid, trans->reg->id,
			mlxsw_reg_id_str(trans->reg->id),
			mlxsw_core_reg_access_type_str(trans->type),
			trans->emad_status,
			mlxsw_emad_op_tlv_status_str(trans->emad_status));

		snम_लिखो(err_string, MLXSW_REG_TRANS_ERR_STRING_SIZE,
			 "(tid=%llx,reg_id=%x(%s)) %s (%s)\n", trans->tid,
			 trans->reg->id, mlxsw_reg_id_str(trans->reg->id),
			 mlxsw_emad_op_tlv_status_str(trans->emad_status),
			 trans->emad_err_string ? trans->emad_err_string : "");

		trace_devlink_hwerr(priv_to_devlink(mlxsw_core),
				    trans->emad_status, err_string);

		kमुक्त(trans->emad_err_string);
	पूर्ण

	list_del(&trans->bulk_list);
	kमुक्त_rcu(trans, rcu);
	वापस err;
पूर्ण

पूर्णांक mlxsw_reg_trans_bulk_रुको(काष्ठा list_head *bulk_list)
अणु
	काष्ठा mlxsw_reg_trans *trans;
	काष्ठा mlxsw_reg_trans *पंचांगp;
	पूर्णांक sum_err = 0;
	पूर्णांक err;

	list_क्रम_each_entry_safe(trans, पंचांगp, bulk_list, bulk_list) अणु
		err = mlxsw_reg_trans_रुको(trans);
		अगर (err && sum_err == 0)
			sum_err = err; /* first error to be वापसed */
	पूर्ण
	वापस sum_err;
पूर्ण
EXPORT_SYMBOL(mlxsw_reg_trans_bulk_रुको);

अटल पूर्णांक mlxsw_core_reg_access_cmd(काष्ठा mlxsw_core *mlxsw_core,
				     स्थिर काष्ठा mlxsw_reg_info *reg,
				     अक्षर *payload,
				     क्रमागत mlxsw_core_reg_access_type type)
अणु
	क्रमागत mlxsw_emad_op_tlv_status status;
	पूर्णांक err, n_retry;
	bool reset_ok;
	अक्षर *in_mbox, *out_mbox, *पंचांगp;

	dev_dbg(mlxsw_core->bus_info->dev, "Reg cmd access (reg_id=%x(%s),type=%s)\n",
		reg->id, mlxsw_reg_id_str(reg->id),
		mlxsw_core_reg_access_type_str(type));

	in_mbox = mlxsw_cmd_mbox_alloc();
	अगर (!in_mbox)
		वापस -ENOMEM;

	out_mbox = mlxsw_cmd_mbox_alloc();
	अगर (!out_mbox) अणु
		err = -ENOMEM;
		जाओ मुक्त_in_mbox;
	पूर्ण

	mlxsw_emad_pack_op_tlv(in_mbox, reg, type,
			       mlxsw_core_tid_get(mlxsw_core));
	पंचांगp = in_mbox + MLXSW_EMAD_OP_TLV_LEN * माप(u32);
	mlxsw_emad_pack_reg_tlv(पंचांगp, reg, payload);

	/* There is a special treaपंचांगent needed क्रम MRSR (reset) रेजिस्टर.
	 * The command पूर्णांकerface will वापस error after the command
	 * is executed, so tell the lower layer to expect it
	 * and cope accordingly.
	 */
	reset_ok = reg->id == MLXSW_REG_MRSR_ID;

	n_retry = 0;
retry:
	err = mlxsw_cmd_access_reg(mlxsw_core, reset_ok, in_mbox, out_mbox);
	अगर (!err) अणु
		err = mlxsw_emad_process_status(out_mbox, &status);
		अगर (err) अणु
			अगर (err == -EAGAIN && n_retry++ < MLXSW_EMAD_MAX_RETRY)
				जाओ retry;
			dev_err(mlxsw_core->bus_info->dev, "Reg cmd access status failed (status=%x(%s))\n",
				status, mlxsw_emad_op_tlv_status_str(status));
		पूर्ण
	पूर्ण

	अगर (!err)
		स_नकल(payload, mlxsw_emad_reg_payload_cmd(out_mbox),
		       reg->len);

	mlxsw_cmd_mbox_मुक्त(out_mbox);
मुक्त_in_mbox:
	mlxsw_cmd_mbox_मुक्त(in_mbox);
	अगर (err)
		dev_err(mlxsw_core->bus_info->dev, "Reg cmd access failed (reg_id=%x(%s),type=%s)\n",
			reg->id, mlxsw_reg_id_str(reg->id),
			mlxsw_core_reg_access_type_str(type));
	वापस err;
पूर्ण

अटल व्योम mlxsw_core_reg_access_cb(काष्ठा mlxsw_core *mlxsw_core,
				     अक्षर *payload, माप_प्रकार payload_len,
				     अचिन्हित दीर्घ cb_priv)
अणु
	अक्षर *orig_payload = (अक्षर *) cb_priv;

	स_नकल(orig_payload, payload, payload_len);
पूर्ण

अटल पूर्णांक mlxsw_core_reg_access(काष्ठा mlxsw_core *mlxsw_core,
				 स्थिर काष्ठा mlxsw_reg_info *reg,
				 अक्षर *payload,
				 क्रमागत mlxsw_core_reg_access_type type)
अणु
	LIST_HEAD(bulk_list);
	पूर्णांक err;

	/* During initialization EMAD पूर्णांकerface is not available to us,
	 * so we शेष to command पूर्णांकerface. We चयन to EMAD पूर्णांकerface
	 * after setting the appropriate traps.
	 */
	अगर (!mlxsw_core->emad.use_emad)
		वापस mlxsw_core_reg_access_cmd(mlxsw_core, reg,
						 payload, type);

	err = mlxsw_core_reg_access_emad(mlxsw_core, reg,
					 payload, type, &bulk_list,
					 mlxsw_core_reg_access_cb,
					 (अचिन्हित दीर्घ) payload);
	अगर (err)
		वापस err;
	वापस mlxsw_reg_trans_bulk_रुको(&bulk_list);
पूर्ण

पूर्णांक mlxsw_reg_query(काष्ठा mlxsw_core *mlxsw_core,
		    स्थिर काष्ठा mlxsw_reg_info *reg, अक्षर *payload)
अणु
	वापस mlxsw_core_reg_access(mlxsw_core, reg, payload,
				     MLXSW_CORE_REG_ACCESS_TYPE_QUERY);
पूर्ण
EXPORT_SYMBOL(mlxsw_reg_query);

पूर्णांक mlxsw_reg_ग_लिखो(काष्ठा mlxsw_core *mlxsw_core,
		    स्थिर काष्ठा mlxsw_reg_info *reg, अक्षर *payload)
अणु
	वापस mlxsw_core_reg_access(mlxsw_core, reg, payload,
				     MLXSW_CORE_REG_ACCESS_TYPE_WRITE);
पूर्ण
EXPORT_SYMBOL(mlxsw_reg_ग_लिखो);

व्योम mlxsw_core_skb_receive(काष्ठा mlxsw_core *mlxsw_core, काष्ठा sk_buff *skb,
			    काष्ठा mlxsw_rx_info *rx_info)
अणु
	काष्ठा mlxsw_rx_listener_item *rxl_item;
	स्थिर काष्ठा mlxsw_rx_listener *rxl;
	u8 local_port;
	bool found = false;

	अगर (rx_info->is_lag) अणु
		dev_dbg_ratelimited(mlxsw_core->bus_info->dev, "%s: lag_id = %d, lag_port_index = 0x%x\n",
				    __func__, rx_info->u.lag_id,
				    rx_info->trap_id);
		/* Upper layer करोes not care अगर the skb came from LAG or not,
		 * so just get the local_port क्रम the lag port and push it up.
		 */
		local_port = mlxsw_core_lag_mapping_get(mlxsw_core,
							rx_info->u.lag_id,
							rx_info->lag_port_index);
	पूर्ण अन्यथा अणु
		local_port = rx_info->u.sys_port;
	पूर्ण

	dev_dbg_ratelimited(mlxsw_core->bus_info->dev, "%s: local_port = %d, trap_id = 0x%x\n",
			    __func__, local_port, rx_info->trap_id);

	अगर ((rx_info->trap_id >= MLXSW_TRAP_ID_MAX) ||
	    (local_port >= mlxsw_core->max_ports))
		जाओ drop;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(rxl_item, &mlxsw_core->rx_listener_list, list) अणु
		rxl = &rxl_item->rxl;
		अगर ((rxl->local_port == MLXSW_PORT_DONT_CARE ||
		     rxl->local_port == local_port) &&
		    rxl->trap_id == rx_info->trap_id &&
		    rxl->mirror_reason == rx_info->mirror_reason) अणु
			अगर (rxl_item->enabled)
				found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found) अणु
		rcu_पढ़ो_unlock();
		जाओ drop;
	पूर्ण

	rxl->func(skb, local_port, rxl_item->priv);
	rcu_पढ़ो_unlock();
	वापस;

drop:
	dev_kमुक्त_skb(skb);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_skb_receive);

अटल पूर्णांक mlxsw_core_lag_mapping_index(काष्ठा mlxsw_core *mlxsw_core,
					u16 lag_id, u8 port_index)
अणु
	वापस MLXSW_CORE_RES_GET(mlxsw_core, MAX_LAG_MEMBERS) * lag_id +
	       port_index;
पूर्ण

व्योम mlxsw_core_lag_mapping_set(काष्ठा mlxsw_core *mlxsw_core,
				u16 lag_id, u8 port_index, u8 local_port)
अणु
	पूर्णांक index = mlxsw_core_lag_mapping_index(mlxsw_core,
						 lag_id, port_index);

	mlxsw_core->lag.mapping[index] = local_port;
पूर्ण
EXPORT_SYMBOL(mlxsw_core_lag_mapping_set);

u8 mlxsw_core_lag_mapping_get(काष्ठा mlxsw_core *mlxsw_core,
			      u16 lag_id, u8 port_index)
अणु
	पूर्णांक index = mlxsw_core_lag_mapping_index(mlxsw_core,
						 lag_id, port_index);

	वापस mlxsw_core->lag.mapping[index];
पूर्ण
EXPORT_SYMBOL(mlxsw_core_lag_mapping_get);

व्योम mlxsw_core_lag_mapping_clear(काष्ठा mlxsw_core *mlxsw_core,
				  u16 lag_id, u8 local_port)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_CORE_RES_GET(mlxsw_core, MAX_LAG_MEMBERS); i++) अणु
		पूर्णांक index = mlxsw_core_lag_mapping_index(mlxsw_core,
							 lag_id, i);

		अगर (mlxsw_core->lag.mapping[index] == local_port)
			mlxsw_core->lag.mapping[index] = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mlxsw_core_lag_mapping_clear);

bool mlxsw_core_res_valid(काष्ठा mlxsw_core *mlxsw_core,
			  क्रमागत mlxsw_res_id res_id)
अणु
	वापस mlxsw_res_valid(&mlxsw_core->res, res_id);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_res_valid);

u64 mlxsw_core_res_get(काष्ठा mlxsw_core *mlxsw_core,
		       क्रमागत mlxsw_res_id res_id)
अणु
	वापस mlxsw_res_get(&mlxsw_core->res, res_id);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_res_get);

अटल पूर्णांक __mlxsw_core_port_init(काष्ठा mlxsw_core *mlxsw_core, u8 local_port,
				  क्रमागत devlink_port_flavour flavour,
				  u32 port_number, bool split,
				  u32 split_port_subnumber,
				  bool splittable, u32 lanes,
				  स्थिर अचिन्हित अक्षर *चयन_id,
				  अचिन्हित अक्षर चयन_id_len)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_core);
	काष्ठा mlxsw_core_port *mlxsw_core_port =
					&mlxsw_core->ports[local_port];
	काष्ठा devlink_port *devlink_port = &mlxsw_core_port->devlink_port;
	काष्ठा devlink_port_attrs attrs = अणुपूर्ण;
	पूर्णांक err;

	attrs.split = split;
	attrs.lanes = lanes;
	attrs.splittable = splittable;
	attrs.flavour = flavour;
	attrs.phys.port_number = port_number;
	attrs.phys.split_subport_number = split_port_subnumber;
	स_नकल(attrs.चयन_id.id, चयन_id, चयन_id_len);
	attrs.चयन_id.id_len = चयन_id_len;
	mlxsw_core_port->local_port = local_port;
	devlink_port_attrs_set(devlink_port, &attrs);
	err = devlink_port_रेजिस्टर(devlink, devlink_port, local_port);
	अगर (err)
		स_रखो(mlxsw_core_port, 0, माप(*mlxsw_core_port));
	वापस err;
पूर्ण

अटल व्योम __mlxsw_core_port_fini(काष्ठा mlxsw_core *mlxsw_core, u8 local_port)
अणु
	काष्ठा mlxsw_core_port *mlxsw_core_port =
					&mlxsw_core->ports[local_port];
	काष्ठा devlink_port *devlink_port = &mlxsw_core_port->devlink_port;

	devlink_port_unरेजिस्टर(devlink_port);
	स_रखो(mlxsw_core_port, 0, माप(*mlxsw_core_port));
पूर्ण

पूर्णांक mlxsw_core_port_init(काष्ठा mlxsw_core *mlxsw_core, u8 local_port,
			 u32 port_number, bool split,
			 u32 split_port_subnumber,
			 bool splittable, u32 lanes,
			 स्थिर अचिन्हित अक्षर *चयन_id,
			 अचिन्हित अक्षर चयन_id_len)
अणु
	पूर्णांक err;

	err = __mlxsw_core_port_init(mlxsw_core, local_port,
				     DEVLINK_PORT_FLAVOUR_PHYSICAL,
				     port_number, split, split_port_subnumber,
				     splittable, lanes,
				     चयन_id, चयन_id_len);
	अगर (err)
		वापस err;

	atomic_inc(&mlxsw_core->active_ports_count);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlxsw_core_port_init);

व्योम mlxsw_core_port_fini(काष्ठा mlxsw_core *mlxsw_core, u8 local_port)
अणु
	atomic_dec(&mlxsw_core->active_ports_count);

	__mlxsw_core_port_fini(mlxsw_core, local_port);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_port_fini);

पूर्णांक mlxsw_core_cpu_port_init(काष्ठा mlxsw_core *mlxsw_core,
			     व्योम *port_driver_priv,
			     स्थिर अचिन्हित अक्षर *चयन_id,
			     अचिन्हित अक्षर चयन_id_len)
अणु
	काष्ठा mlxsw_core_port *mlxsw_core_port =
				&mlxsw_core->ports[MLXSW_PORT_CPU_PORT];
	पूर्णांक err;

	err = __mlxsw_core_port_init(mlxsw_core, MLXSW_PORT_CPU_PORT,
				     DEVLINK_PORT_FLAVOUR_CPU,
				     0, false, 0, false, 0,
				     चयन_id, चयन_id_len);
	अगर (err)
		वापस err;

	mlxsw_core_port->port_driver_priv = port_driver_priv;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlxsw_core_cpu_port_init);

व्योम mlxsw_core_cpu_port_fini(काष्ठा mlxsw_core *mlxsw_core)
अणु
	__mlxsw_core_port_fini(mlxsw_core, MLXSW_PORT_CPU_PORT);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_cpu_port_fini);

व्योम mlxsw_core_port_eth_set(काष्ठा mlxsw_core *mlxsw_core, u8 local_port,
			     व्योम *port_driver_priv, काष्ठा net_device *dev)
अणु
	काष्ठा mlxsw_core_port *mlxsw_core_port =
					&mlxsw_core->ports[local_port];
	काष्ठा devlink_port *devlink_port = &mlxsw_core_port->devlink_port;

	mlxsw_core_port->port_driver_priv = port_driver_priv;
	devlink_port_type_eth_set(devlink_port, dev);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_port_eth_set);

व्योम mlxsw_core_port_ib_set(काष्ठा mlxsw_core *mlxsw_core, u8 local_port,
			    व्योम *port_driver_priv)
अणु
	काष्ठा mlxsw_core_port *mlxsw_core_port =
					&mlxsw_core->ports[local_port];
	काष्ठा devlink_port *devlink_port = &mlxsw_core_port->devlink_port;

	mlxsw_core_port->port_driver_priv = port_driver_priv;
	devlink_port_type_ib_set(devlink_port, शून्य);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_port_ib_set);

व्योम mlxsw_core_port_clear(काष्ठा mlxsw_core *mlxsw_core, u8 local_port,
			   व्योम *port_driver_priv)
अणु
	काष्ठा mlxsw_core_port *mlxsw_core_port =
					&mlxsw_core->ports[local_port];
	काष्ठा devlink_port *devlink_port = &mlxsw_core_port->devlink_port;

	mlxsw_core_port->port_driver_priv = port_driver_priv;
	devlink_port_type_clear(devlink_port);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_port_clear);

क्रमागत devlink_port_type mlxsw_core_port_type_get(काष्ठा mlxsw_core *mlxsw_core,
						u8 local_port)
अणु
	काष्ठा mlxsw_core_port *mlxsw_core_port =
					&mlxsw_core->ports[local_port];
	काष्ठा devlink_port *devlink_port = &mlxsw_core_port->devlink_port;

	वापस devlink_port->type;
पूर्ण
EXPORT_SYMBOL(mlxsw_core_port_type_get);


काष्ठा devlink_port *
mlxsw_core_port_devlink_port_get(काष्ठा mlxsw_core *mlxsw_core,
				 u8 local_port)
अणु
	काष्ठा mlxsw_core_port *mlxsw_core_port =
					&mlxsw_core->ports[local_port];
	काष्ठा devlink_port *devlink_port = &mlxsw_core_port->devlink_port;

	वापस devlink_port;
पूर्ण
EXPORT_SYMBOL(mlxsw_core_port_devlink_port_get);

bool mlxsw_core_port_is_xm(स्थिर काष्ठा mlxsw_core *mlxsw_core, u8 local_port)
अणु
	स्थिर काष्ठा mlxsw_bus_info *bus_info = mlxsw_core->bus_info;
	पूर्णांक i;

	क्रम (i = 0; i < bus_info->xm_local_ports_count; i++)
		अगर (bus_info->xm_local_ports[i] == local_port)
			वापस true;
	वापस false;
पूर्ण
EXPORT_SYMBOL(mlxsw_core_port_is_xm);

काष्ठा mlxsw_env *mlxsw_core_env(स्थिर काष्ठा mlxsw_core *mlxsw_core)
अणु
	वापस mlxsw_core->env;
पूर्ण

bool mlxsw_core_is_initialized(स्थिर काष्ठा mlxsw_core *mlxsw_core)
अणु
	वापस mlxsw_core->is_initialized;
पूर्ण

पूर्णांक mlxsw_core_module_max_width(काष्ठा mlxsw_core *mlxsw_core, u8 module)
अणु
	क्रमागत mlxsw_reg_pmपंचांग_module_type module_type;
	अक्षर pmपंचांग_pl[MLXSW_REG_PMTM_LEN];
	पूर्णांक err;

	mlxsw_reg_pmपंचांग_pack(pmपंचांग_pl, module);
	err = mlxsw_reg_query(mlxsw_core, MLXSW_REG(pmपंचांग), pmपंचांग_pl);
	अगर (err)
		वापस err;
	mlxsw_reg_pmपंचांग_unpack(pmपंचांग_pl, &module_type);

	/* Here we need to get the module width according to the module type. */

	चयन (module_type) अणु
	हाल MLXSW_REG_PMTM_MODULE_TYPE_C2C8X:
	हाल MLXSW_REG_PMTM_MODULE_TYPE_QSFP_DD:
	हाल MLXSW_REG_PMTM_MODULE_TYPE_OSFP:
		वापस 8;
	हाल MLXSW_REG_PMTM_MODULE_TYPE_C2C4X:
	हाल MLXSW_REG_PMTM_MODULE_TYPE_BP_4X:
	हाल MLXSW_REG_PMTM_MODULE_TYPE_QSFP:
		वापस 4;
	हाल MLXSW_REG_PMTM_MODULE_TYPE_C2C2X:
	हाल MLXSW_REG_PMTM_MODULE_TYPE_BP_2X:
	हाल MLXSW_REG_PMTM_MODULE_TYPE_SFP_DD:
	हाल MLXSW_REG_PMTM_MODULE_TYPE_DSFP:
		वापस 2;
	हाल MLXSW_REG_PMTM_MODULE_TYPE_C2C1X:
	हाल MLXSW_REG_PMTM_MODULE_TYPE_BP_1X:
	हाल MLXSW_REG_PMTM_MODULE_TYPE_SFP:
		वापस 1;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mlxsw_core_module_max_width);

अटल व्योम mlxsw_core_buf_dump_dbg(काष्ठा mlxsw_core *mlxsw_core,
				    स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	__be32 *m = (__be32 *) buf;
	पूर्णांक i;
	पूर्णांक count = size / माप(__be32);

	क्रम (i = count - 1; i >= 0; i--)
		अगर (m[i])
			अवरोध;
	i++;
	count = i ? i : 1;
	क्रम (i = 0; i < count; i += 4)
		dev_dbg(mlxsw_core->bus_info->dev, "%04x - %08x %08x %08x %08x\n",
			i * 4, be32_to_cpu(m[i]), be32_to_cpu(m[i + 1]),
			be32_to_cpu(m[i + 2]), be32_to_cpu(m[i + 3]));
पूर्ण

पूर्णांक mlxsw_cmd_exec(काष्ठा mlxsw_core *mlxsw_core, u16 opcode, u8 opcode_mod,
		   u32 in_mod, bool out_mbox_direct, bool reset_ok,
		   अक्षर *in_mbox, माप_प्रकार in_mbox_size,
		   अक्षर *out_mbox, माप_प्रकार out_mbox_size)
अणु
	u8 status;
	पूर्णांक err;

	BUG_ON(in_mbox_size % माप(u32) || out_mbox_size % माप(u32));
	अगर (!mlxsw_core->bus->cmd_exec)
		वापस -EOPNOTSUPP;

	dev_dbg(mlxsw_core->bus_info->dev, "Cmd exec (opcode=%x(%s),opcode_mod=%x,in_mod=%x)\n",
		opcode, mlxsw_cmd_opcode_str(opcode), opcode_mod, in_mod);
	अगर (in_mbox) अणु
		dev_dbg(mlxsw_core->bus_info->dev, "Input mailbox:\n");
		mlxsw_core_buf_dump_dbg(mlxsw_core, in_mbox, in_mbox_size);
	पूर्ण

	err = mlxsw_core->bus->cmd_exec(mlxsw_core->bus_priv, opcode,
					opcode_mod, in_mod, out_mbox_direct,
					in_mbox, in_mbox_size,
					out_mbox, out_mbox_size, &status);

	अगर (!err && out_mbox) अणु
		dev_dbg(mlxsw_core->bus_info->dev, "Output mailbox:\n");
		mlxsw_core_buf_dump_dbg(mlxsw_core, out_mbox, out_mbox_size);
	पूर्ण

	अगर (reset_ok && err == -EIO &&
	    status == MLXSW_CMD_STATUS_RUNNING_RESET) अणु
		err = 0;
	पूर्ण अन्यथा अगर (err == -EIO && status != MLXSW_CMD_STATUS_OK) अणु
		dev_err(mlxsw_core->bus_info->dev, "Cmd exec failed (opcode=%x(%s),opcode_mod=%x,in_mod=%x,status=%x(%s))\n",
			opcode, mlxsw_cmd_opcode_str(opcode), opcode_mod,
			in_mod, status, mlxsw_cmd_status_str(status));
	पूर्ण अन्यथा अगर (err == -ETIMEDOUT) अणु
		dev_err(mlxsw_core->bus_info->dev, "Cmd exec timed-out (opcode=%x(%s),opcode_mod=%x,in_mod=%x)\n",
			opcode, mlxsw_cmd_opcode_str(opcode), opcode_mod,
			in_mod);
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL(mlxsw_cmd_exec);

पूर्णांक mlxsw_core_schedule_dw(काष्ठा delayed_work *dwork, अचिन्हित दीर्घ delay)
अणु
	वापस queue_delayed_work(mlxsw_wq, dwork, delay);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_schedule_dw);

bool mlxsw_core_schedule_work(काष्ठा work_काष्ठा *work)
अणु
	वापस queue_work(mlxsw_owq, work);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_schedule_work);

व्योम mlxsw_core_flush_owq(व्योम)
अणु
	flush_workqueue(mlxsw_owq);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_flush_owq);

पूर्णांक mlxsw_core_kvd_sizes_get(काष्ठा mlxsw_core *mlxsw_core,
			     स्थिर काष्ठा mlxsw_config_profile *profile,
			     u64 *p_single_size, u64 *p_द्विगुन_size,
			     u64 *p_linear_size)
अणु
	काष्ठा mlxsw_driver *driver = mlxsw_core->driver;

	अगर (!driver->kvd_sizes_get)
		वापस -EINVAL;

	वापस driver->kvd_sizes_get(mlxsw_core, profile,
				     p_single_size, p_द्विगुन_size,
				     p_linear_size);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_kvd_sizes_get);

पूर्णांक mlxsw_core_resources_query(काष्ठा mlxsw_core *mlxsw_core, अक्षर *mbox,
			       काष्ठा mlxsw_res *res)
अणु
	पूर्णांक index, i;
	u64 data;
	u16 id;
	पूर्णांक err;

	अगर (!res)
		वापस 0;

	mlxsw_cmd_mbox_zero(mbox);

	क्रम (index = 0; index < MLXSW_CMD_QUERY_RESOURCES_MAX_QUERIES;
	     index++) अणु
		err = mlxsw_cmd_query_resources(mlxsw_core, mbox, index);
		अगर (err)
			वापस err;

		क्रम (i = 0; i < MLXSW_CMD_QUERY_RESOURCES_PER_QUERY; i++) अणु
			id = mlxsw_cmd_mbox_query_resource_id_get(mbox, i);
			data = mlxsw_cmd_mbox_query_resource_data_get(mbox, i);

			अगर (id == MLXSW_CMD_QUERY_RESOURCES_TABLE_END_ID)
				वापस 0;

			mlxsw_res_parse(res, id, data);
		पूर्ण
	पूर्ण

	/* If after MLXSW_RESOURCES_QUERY_MAX_QUERIES we still didn't get
	 * MLXSW_RESOURCES_TABLE_END_ID, something went bad in the FW.
	 */
	वापस -EIO;
पूर्ण
EXPORT_SYMBOL(mlxsw_core_resources_query);

u32 mlxsw_core_पढ़ो_frc_h(काष्ठा mlxsw_core *mlxsw_core)
अणु
	वापस mlxsw_core->bus->पढ़ो_frc_h(mlxsw_core->bus_priv);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_पढ़ो_frc_h);

u32 mlxsw_core_पढ़ो_frc_l(काष्ठा mlxsw_core *mlxsw_core)
अणु
	वापस mlxsw_core->bus->पढ़ो_frc_l(mlxsw_core->bus_priv);
पूर्ण
EXPORT_SYMBOL(mlxsw_core_पढ़ो_frc_l);

व्योम mlxsw_core_emad_string_tlv_enable(काष्ठा mlxsw_core *mlxsw_core)
अणु
	mlxsw_core->emad.enable_string_tlv = true;
पूर्ण
EXPORT_SYMBOL(mlxsw_core_emad_string_tlv_enable);

अटल पूर्णांक __init mlxsw_core_module_init(व्योम)
अणु
	पूर्णांक err;

	mlxsw_wq = alloc_workqueue(mlxsw_core_driver_name, 0, 0);
	अगर (!mlxsw_wq)
		वापस -ENOMEM;
	mlxsw_owq = alloc_ordered_workqueue("%s_ordered", 0,
					    mlxsw_core_driver_name);
	अगर (!mlxsw_owq) अणु
		err = -ENOMEM;
		जाओ err_alloc_ordered_workqueue;
	पूर्ण
	वापस 0;

err_alloc_ordered_workqueue:
	destroy_workqueue(mlxsw_wq);
	वापस err;
पूर्ण

अटल व्योम __निकास mlxsw_core_module_निकास(व्योम)
अणु
	destroy_workqueue(mlxsw_owq);
	destroy_workqueue(mlxsw_wq);
पूर्ण

module_init(mlxsw_core_module_init);
module_निकास(mlxsw_core_module_निकास);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Jiri Pirko <jiri@mellanox.com>");
MODULE_DESCRIPTION("Mellanox switch device core driver");
