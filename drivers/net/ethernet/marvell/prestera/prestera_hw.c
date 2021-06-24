<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2019-2020 Marvell International Ltd. All rights reserved */

#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/list.h>

#समावेश "prestera.h"
#समावेश "prestera_hw.h"

#घोषणा PRESTERA_SWITCH_INIT_TIMEOUT_MS (30 * 1000)

#घोषणा PRESTERA_MIN_MTU 64

क्रमागत prestera_cmd_type_t अणु
	PRESTERA_CMD_TYPE_SWITCH_INIT = 0x1,
	PRESTERA_CMD_TYPE_SWITCH_ATTR_SET = 0x2,

	PRESTERA_CMD_TYPE_PORT_ATTR_SET = 0x100,
	PRESTERA_CMD_TYPE_PORT_ATTR_GET = 0x101,
	PRESTERA_CMD_TYPE_PORT_INFO_GET = 0x110,

	PRESTERA_CMD_TYPE_VLAN_CREATE = 0x200,
	PRESTERA_CMD_TYPE_VLAN_DELETE = 0x201,
	PRESTERA_CMD_TYPE_VLAN_PORT_SET = 0x202,
	PRESTERA_CMD_TYPE_VLAN_PVID_SET = 0x203,

	PRESTERA_CMD_TYPE_FDB_ADD = 0x300,
	PRESTERA_CMD_TYPE_FDB_DELETE = 0x301,
	PRESTERA_CMD_TYPE_FDB_FLUSH_PORT = 0x310,
	PRESTERA_CMD_TYPE_FDB_FLUSH_VLAN = 0x311,
	PRESTERA_CMD_TYPE_FDB_FLUSH_PORT_VLAN = 0x312,

	PRESTERA_CMD_TYPE_BRIDGE_CREATE = 0x400,
	PRESTERA_CMD_TYPE_BRIDGE_DELETE = 0x401,
	PRESTERA_CMD_TYPE_BRIDGE_PORT_ADD = 0x402,
	PRESTERA_CMD_TYPE_BRIDGE_PORT_DELETE = 0x403,

	PRESTERA_CMD_TYPE_RXTX_INIT = 0x800,
	PRESTERA_CMD_TYPE_RXTX_PORT_INIT = 0x801,

	PRESTERA_CMD_TYPE_STP_PORT_SET = 0x1000,

	PRESTERA_CMD_TYPE_ACK = 0x10000,
	PRESTERA_CMD_TYPE_MAX
पूर्ण;

क्रमागत अणु
	PRESTERA_CMD_PORT_ATTR_ADMIN_STATE = 1,
	PRESTERA_CMD_PORT_ATTR_MTU = 3,
	PRESTERA_CMD_PORT_ATTR_MAC = 4,
	PRESTERA_CMD_PORT_ATTR_SPEED = 5,
	PRESTERA_CMD_PORT_ATTR_ACCEPT_FRAME_TYPE = 6,
	PRESTERA_CMD_PORT_ATTR_LEARNING = 7,
	PRESTERA_CMD_PORT_ATTR_FLOOD = 8,
	PRESTERA_CMD_PORT_ATTR_CAPABILITY = 9,
	PRESTERA_CMD_PORT_ATTR_REMOTE_CAPABILITY = 10,
	PRESTERA_CMD_PORT_ATTR_REMOTE_FC = 11,
	PRESTERA_CMD_PORT_ATTR_LINK_MODE = 12,
	PRESTERA_CMD_PORT_ATTR_TYPE = 13,
	PRESTERA_CMD_PORT_ATTR_FEC = 14,
	PRESTERA_CMD_PORT_ATTR_AUTONEG = 15,
	PRESTERA_CMD_PORT_ATTR_DUPLEX = 16,
	PRESTERA_CMD_PORT_ATTR_STATS = 17,
	PRESTERA_CMD_PORT_ATTR_MDIX = 18,
	PRESTERA_CMD_PORT_ATTR_AUTONEG_RESTART = 19,
पूर्ण;

क्रमागत अणु
	PRESTERA_CMD_SWITCH_ATTR_MAC = 1,
	PRESTERA_CMD_SWITCH_ATTR_AGEING = 2,
पूर्ण;

क्रमागत अणु
	PRESTERA_CMD_ACK_OK,
	PRESTERA_CMD_ACK_FAILED,

	PRESTERA_CMD_ACK_MAX
पूर्ण;

क्रमागत अणु
	PRESTERA_PORT_TP_NA,
	PRESTERA_PORT_TP_MDI,
	PRESTERA_PORT_TP_MDIX,
	PRESTERA_PORT_TP_AUTO,
पूर्ण;

क्रमागत अणु
	PRESTERA_PORT_GOOD_OCTETS_RCV_CNT,
	PRESTERA_PORT_BAD_OCTETS_RCV_CNT,
	PRESTERA_PORT_MAC_TRANSMIT_ERR_CNT,
	PRESTERA_PORT_BRDC_PKTS_RCV_CNT,
	PRESTERA_PORT_MC_PKTS_RCV_CNT,
	PRESTERA_PORT_PKTS_64L_CNT,
	PRESTERA_PORT_PKTS_65TO127L_CNT,
	PRESTERA_PORT_PKTS_128TO255L_CNT,
	PRESTERA_PORT_PKTS_256TO511L_CNT,
	PRESTERA_PORT_PKTS_512TO1023L_CNT,
	PRESTERA_PORT_PKTS_1024TOMAXL_CNT,
	PRESTERA_PORT_EXCESSIVE_COLLISIONS_CNT,
	PRESTERA_PORT_MC_PKTS_SENT_CNT,
	PRESTERA_PORT_BRDC_PKTS_SENT_CNT,
	PRESTERA_PORT_FC_SENT_CNT,
	PRESTERA_PORT_GOOD_FC_RCV_CNT,
	PRESTERA_PORT_DROP_EVENTS_CNT,
	PRESTERA_PORT_UNDERSIZE_PKTS_CNT,
	PRESTERA_PORT_FRAGMENTS_PKTS_CNT,
	PRESTERA_PORT_OVERSIZE_PKTS_CNT,
	PRESTERA_PORT_JABBER_PKTS_CNT,
	PRESTERA_PORT_MAC_RCV_ERROR_CNT,
	PRESTERA_PORT_BAD_CRC_CNT,
	PRESTERA_PORT_COLLISIONS_CNT,
	PRESTERA_PORT_LATE_COLLISIONS_CNT,
	PRESTERA_PORT_GOOD_UC_PKTS_RCV_CNT,
	PRESTERA_PORT_GOOD_UC_PKTS_SENT_CNT,
	PRESTERA_PORT_MULTIPLE_PKTS_SENT_CNT,
	PRESTERA_PORT_DEFERRED_PKTS_SENT_CNT,
	PRESTERA_PORT_GOOD_OCTETS_SENT_CNT,

	PRESTERA_PORT_CNT_MAX
पूर्ण;

क्रमागत अणु
	PRESTERA_FC_NONE,
	PRESTERA_FC_SYMMETRIC,
	PRESTERA_FC_ASYMMETRIC,
	PRESTERA_FC_SYMM_ASYMM,
पूर्ण;

काष्ठा prestera_fw_event_handler अणु
	काष्ठा list_head list;
	काष्ठा rcu_head rcu;
	क्रमागत prestera_event_type type;
	prestera_event_cb_t func;
	व्योम *arg;
पूर्ण;

काष्ठा prestera_msg_cmd अणु
	u32 type;
पूर्ण;

काष्ठा prestera_msg_ret अणु
	काष्ठा prestera_msg_cmd cmd;
	u32 status;
पूर्ण;

काष्ठा prestera_msg_common_req अणु
	काष्ठा prestera_msg_cmd cmd;
पूर्ण;

काष्ठा prestera_msg_common_resp अणु
	काष्ठा prestera_msg_ret ret;
पूर्ण;

जोड़ prestera_msg_चयन_param अणु
	u8 mac[ETH_ALEN];
	u32 ageing_समयout_ms;
पूर्ण;

काष्ठा prestera_msg_चयन_attr_req अणु
	काष्ठा prestera_msg_cmd cmd;
	u32 attr;
	जोड़ prestera_msg_चयन_param param;
पूर्ण;

काष्ठा prestera_msg_चयन_init_resp अणु
	काष्ठा prestera_msg_ret ret;
	u32 port_count;
	u32 mtu_max;
	u8  चयन_id;
पूर्ण;

काष्ठा prestera_msg_port_स्वतःneg_param अणु
	u64 link_mode;
	u8  enable;
	u8  fec;
पूर्ण;

काष्ठा prestera_msg_port_cap_param अणु
	u64 link_mode;
	u8  type;
	u8  fec;
	u8  transceiver;
पूर्ण;

काष्ठा prestera_msg_port_mdix_param अणु
	u8 status;
	u8 admin_mode;
पूर्ण;

जोड़ prestera_msg_port_param अणु
	u8  admin_state;
	u8  oper_state;
	u32 mtu;
	u8  mac[ETH_ALEN];
	u8  accept_frm_type;
	u32 speed;
	u8 learning;
	u8 flood;
	u32 link_mode;
	u8  type;
	u8  duplex;
	u8  fec;
	u8  fc;
	काष्ठा prestera_msg_port_mdix_param mdix;
	काष्ठा prestera_msg_port_स्वतःneg_param स्वतःneg;
	काष्ठा prestera_msg_port_cap_param cap;
पूर्ण;

काष्ठा prestera_msg_port_attr_req अणु
	काष्ठा prestera_msg_cmd cmd;
	u32 attr;
	u32 port;
	u32 dev;
	जोड़ prestera_msg_port_param param;
पूर्ण;

काष्ठा prestera_msg_port_attr_resp अणु
	काष्ठा prestera_msg_ret ret;
	जोड़ prestera_msg_port_param param;
पूर्ण;

काष्ठा prestera_msg_port_stats_resp अणु
	काष्ठा prestera_msg_ret ret;
	u64 stats[PRESTERA_PORT_CNT_MAX];
पूर्ण;

काष्ठा prestera_msg_port_info_req अणु
	काष्ठा prestera_msg_cmd cmd;
	u32 port;
पूर्ण;

काष्ठा prestera_msg_port_info_resp अणु
	काष्ठा prestera_msg_ret ret;
	u32 hw_id;
	u32 dev_id;
	u16 fp_id;
पूर्ण;

काष्ठा prestera_msg_vlan_req अणु
	काष्ठा prestera_msg_cmd cmd;
	u32 port;
	u32 dev;
	u16 vid;
	u8  is_member;
	u8  is_tagged;
पूर्ण;

काष्ठा prestera_msg_fdb_req अणु
	काष्ठा prestera_msg_cmd cmd;
	u8 dest_type;
	u32 port;
	u32 dev;
	u8  mac[ETH_ALEN];
	u16 vid;
	u8  dynamic;
	u32 flush_mode;
पूर्ण;

काष्ठा prestera_msg_bridge_req अणु
	काष्ठा prestera_msg_cmd cmd;
	u32 port;
	u32 dev;
	u16 bridge;
पूर्ण;

काष्ठा prestera_msg_bridge_resp अणु
	काष्ठा prestera_msg_ret ret;
	u16 bridge;
पूर्ण;

काष्ठा prestera_msg_stp_req अणु
	काष्ठा prestera_msg_cmd cmd;
	u32 port;
	u32 dev;
	u16 vid;
	u8  state;
पूर्ण;

काष्ठा prestera_msg_rxtx_req अणु
	काष्ठा prestera_msg_cmd cmd;
	u8 use_sdma;
पूर्ण;

काष्ठा prestera_msg_rxtx_resp अणु
	काष्ठा prestera_msg_ret ret;
	u32 map_addr;
पूर्ण;

काष्ठा prestera_msg_rxtx_port_req अणु
	काष्ठा prestera_msg_cmd cmd;
	u32 port;
	u32 dev;
पूर्ण;

काष्ठा prestera_msg_event अणु
	u16 type;
	u16 id;
पूर्ण;

जोड़ prestera_msg_event_port_param अणु
	u32 oper_state;
पूर्ण;

काष्ठा prestera_msg_event_port अणु
	काष्ठा prestera_msg_event id;
	u32 port_id;
	जोड़ prestera_msg_event_port_param param;
पूर्ण;

जोड़ prestera_msg_event_fdb_param अणु
	u8 mac[ETH_ALEN];
पूर्ण;

काष्ठा prestera_msg_event_fdb अणु
	काष्ठा prestera_msg_event id;
	u8 dest_type;
	u32 port_id;
	u32 vid;
	जोड़ prestera_msg_event_fdb_param param;
पूर्ण;

अटल पूर्णांक __prestera_cmd_ret(काष्ठा prestera_चयन *sw,
			      क्रमागत prestera_cmd_type_t type,
			      काष्ठा prestera_msg_cmd *cmd, माप_प्रकार clen,
			      काष्ठा prestera_msg_ret *ret, माप_प्रकार rlen,
			      पूर्णांक रुकोms)
अणु
	काष्ठा prestera_device *dev = sw->dev;
	पूर्णांक err;

	cmd->type = type;

	err = dev->send_req(dev, cmd, clen, ret, rlen, रुकोms);
	अगर (err)
		वापस err;

	अगर (ret->cmd.type != PRESTERA_CMD_TYPE_ACK)
		वापस -EBADE;
	अगर (ret->status != PRESTERA_CMD_ACK_OK)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक prestera_cmd_ret(काष्ठा prestera_चयन *sw,
			    क्रमागत prestera_cmd_type_t type,
			    काष्ठा prestera_msg_cmd *cmd, माप_प्रकार clen,
			    काष्ठा prestera_msg_ret *ret, माप_प्रकार rlen)
अणु
	वापस __prestera_cmd_ret(sw, type, cmd, clen, ret, rlen, 0);
पूर्ण

अटल पूर्णांक prestera_cmd_ret_रुको(काष्ठा prestera_चयन *sw,
				 क्रमागत prestera_cmd_type_t type,
				 काष्ठा prestera_msg_cmd *cmd, माप_प्रकार clen,
				 काष्ठा prestera_msg_ret *ret, माप_प्रकार rlen,
				 पूर्णांक रुकोms)
अणु
	वापस __prestera_cmd_ret(sw, type, cmd, clen, ret, rlen, रुकोms);
पूर्ण

अटल पूर्णांक prestera_cmd(काष्ठा prestera_चयन *sw,
			क्रमागत prestera_cmd_type_t type,
			काष्ठा prestera_msg_cmd *cmd, माप_प्रकार clen)
अणु
	काष्ठा prestera_msg_common_resp resp;

	वापस prestera_cmd_ret(sw, type, cmd, clen, &resp.ret, माप(resp));
पूर्ण

अटल पूर्णांक prestera_fw_parse_port_evt(व्योम *msg, काष्ठा prestera_event *evt)
अणु
	काष्ठा prestera_msg_event_port *hw_evt = msg;

	अगर (evt->id != PRESTERA_PORT_EVENT_STATE_CHANGED)
		वापस -EINVAL;

	evt->port_evt.data.oper_state = hw_evt->param.oper_state;
	evt->port_evt.port_id = hw_evt->port_id;

	वापस 0;
पूर्ण

अटल पूर्णांक prestera_fw_parse_fdb_evt(व्योम *msg, काष्ठा prestera_event *evt)
अणु
	काष्ठा prestera_msg_event_fdb *hw_evt = msg;

	evt->fdb_evt.port_id = hw_evt->port_id;
	evt->fdb_evt.vid = hw_evt->vid;

	ether_addr_copy(evt->fdb_evt.data.mac, hw_evt->param.mac);

	वापस 0;
पूर्ण

अटल काष्ठा prestera_fw_evt_parser अणु
	पूर्णांक (*func)(व्योम *msg, काष्ठा prestera_event *evt);
पूर्ण fw_event_parsers[PRESTERA_EVENT_TYPE_MAX] = अणु
	[PRESTERA_EVENT_TYPE_PORT] = अणु .func = prestera_fw_parse_port_evt पूर्ण,
	[PRESTERA_EVENT_TYPE_FDB] = अणु .func = prestera_fw_parse_fdb_evt पूर्ण,
पूर्ण;

अटल काष्ठा prestera_fw_event_handler *
__find_event_handler(स्थिर काष्ठा prestera_चयन *sw,
		     क्रमागत prestera_event_type type)
अणु
	काष्ठा prestera_fw_event_handler *eh;

	list_क्रम_each_entry_rcu(eh, &sw->event_handlers, list) अणु
		अगर (eh->type == type)
			वापस eh;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक prestera_find_event_handler(स्थिर काष्ठा prestera_चयन *sw,
				       क्रमागत prestera_event_type type,
				       काष्ठा prestera_fw_event_handler *eh)
अणु
	काष्ठा prestera_fw_event_handler *पंचांगp;
	पूर्णांक err = 0;

	rcu_पढ़ो_lock();
	पंचांगp = __find_event_handler(sw, type);
	अगर (पंचांगp)
		*eh = *पंचांगp;
	अन्यथा
		err = -ENOENT;
	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

अटल पूर्णांक prestera_evt_recv(काष्ठा prestera_device *dev, व्योम *buf, माप_प्रकार size)
अणु
	काष्ठा prestera_चयन *sw = dev->priv;
	काष्ठा prestera_msg_event *msg = buf;
	काष्ठा prestera_fw_event_handler eh;
	काष्ठा prestera_event evt;
	पूर्णांक err;

	अगर (msg->type >= PRESTERA_EVENT_TYPE_MAX)
		वापस -EINVAL;
	अगर (!fw_event_parsers[msg->type].func)
		वापस -ENOENT;

	err = prestera_find_event_handler(sw, msg->type, &eh);
	अगर (err)
		वापस err;

	evt.id = msg->id;

	err = fw_event_parsers[msg->type].func(buf, &evt);
	अगर (err)
		वापस err;

	eh.func(sw, &evt, eh.arg);

	वापस 0;
पूर्ण

अटल व्योम prestera_pkt_recv(काष्ठा prestera_device *dev)
अणु
	काष्ठा prestera_चयन *sw = dev->priv;
	काष्ठा prestera_fw_event_handler eh;
	काष्ठा prestera_event ev;
	पूर्णांक err;

	ev.id = PRESTERA_RXTX_EVENT_RCV_PKT;

	err = prestera_find_event_handler(sw, PRESTERA_EVENT_TYPE_RXTX, &eh);
	अगर (err)
		वापस;

	eh.func(sw, &ev, eh.arg);
पूर्ण

पूर्णांक prestera_hw_port_info_get(स्थिर काष्ठा prestera_port *port,
			      u32 *dev_id, u32 *hw_id, u16 *fp_id)
अणु
	काष्ठा prestera_msg_port_info_req req = अणु
		.port = port->id,
	पूर्ण;
	काष्ठा prestera_msg_port_info_resp resp;
	पूर्णांक err;

	err = prestera_cmd_ret(port->sw, PRESTERA_CMD_TYPE_PORT_INFO_GET,
			       &req.cmd, माप(req), &resp.ret, माप(resp));
	अगर (err)
		वापस err;

	*dev_id = resp.dev_id;
	*hw_id = resp.hw_id;
	*fp_id = resp.fp_id;

	वापस 0;
पूर्ण

पूर्णांक prestera_hw_चयन_mac_set(काष्ठा prestera_चयन *sw, स्थिर अक्षर *mac)
अणु
	काष्ठा prestera_msg_चयन_attr_req req = अणु
		.attr = PRESTERA_CMD_SWITCH_ATTR_MAC,
	पूर्ण;

	ether_addr_copy(req.param.mac, mac);

	वापस prestera_cmd(sw, PRESTERA_CMD_TYPE_SWITCH_ATTR_SET,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_चयन_init(काष्ठा prestera_चयन *sw)
अणु
	काष्ठा prestera_msg_चयन_init_resp resp;
	काष्ठा prestera_msg_common_req req;
	पूर्णांक err;

	INIT_LIST_HEAD(&sw->event_handlers);

	err = prestera_cmd_ret_रुको(sw, PRESTERA_CMD_TYPE_SWITCH_INIT,
				    &req.cmd, माप(req),
				    &resp.ret, माप(resp),
				    PRESTERA_SWITCH_INIT_TIMEOUT_MS);
	अगर (err)
		वापस err;

	sw->dev->recv_msg = prestera_evt_recv;
	sw->dev->recv_pkt = prestera_pkt_recv;
	sw->port_count = resp.port_count;
	sw->mtu_min = PRESTERA_MIN_MTU;
	sw->mtu_max = resp.mtu_max;
	sw->id = resp.चयन_id;

	वापस 0;
पूर्ण

व्योम prestera_hw_चयन_fini(काष्ठा prestera_चयन *sw)
अणु
	WARN_ON(!list_empty(&sw->event_handlers));
पूर्ण

पूर्णांक prestera_hw_चयन_ageing_set(काष्ठा prestera_चयन *sw, u32 ageing_ms)
अणु
	काष्ठा prestera_msg_चयन_attr_req req = अणु
		.attr = PRESTERA_CMD_SWITCH_ATTR_AGEING,
		.param = अणु
			.ageing_समयout_ms = ageing_ms,
		पूर्ण,
	पूर्ण;

	वापस prestera_cmd(sw, PRESTERA_CMD_TYPE_SWITCH_ATTR_SET,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_port_state_set(स्थिर काष्ठा prestera_port *port,
			       bool admin_state)
अणु
	काष्ठा prestera_msg_port_attr_req req = अणु
		.attr = PRESTERA_CMD_PORT_ATTR_ADMIN_STATE,
		.port = port->hw_id,
		.dev = port->dev_id,
		.param = अणु
			.admin_state = admin_state,
		पूर्ण
	पूर्ण;

	वापस prestera_cmd(port->sw, PRESTERA_CMD_TYPE_PORT_ATTR_SET,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_port_mtu_set(स्थिर काष्ठा prestera_port *port, u32 mtu)
अणु
	काष्ठा prestera_msg_port_attr_req req = अणु
		.attr = PRESTERA_CMD_PORT_ATTR_MTU,
		.port = port->hw_id,
		.dev = port->dev_id,
		.param = अणु
			.mtu = mtu,
		पूर्ण
	पूर्ण;

	वापस prestera_cmd(port->sw, PRESTERA_CMD_TYPE_PORT_ATTR_SET,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_port_mac_set(स्थिर काष्ठा prestera_port *port, स्थिर अक्षर *mac)
अणु
	काष्ठा prestera_msg_port_attr_req req = अणु
		.attr = PRESTERA_CMD_PORT_ATTR_MAC,
		.port = port->hw_id,
		.dev = port->dev_id,
	पूर्ण;

	ether_addr_copy(req.param.mac, mac);

	वापस prestera_cmd(port->sw, PRESTERA_CMD_TYPE_PORT_ATTR_SET,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_port_accept_frm_type(काष्ठा prestera_port *port,
				     क्रमागत prestera_accept_frm_type type)
अणु
	काष्ठा prestera_msg_port_attr_req req = अणु
		.attr = PRESTERA_CMD_PORT_ATTR_ACCEPT_FRAME_TYPE,
		.port = port->hw_id,
		.dev = port->dev_id,
		.param = अणु
			.accept_frm_type = type,
		पूर्ण
	पूर्ण;

	वापस prestera_cmd(port->sw, PRESTERA_CMD_TYPE_PORT_ATTR_SET,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_port_cap_get(स्थिर काष्ठा prestera_port *port,
			     काष्ठा prestera_port_caps *caps)
अणु
	काष्ठा prestera_msg_port_attr_req req = अणु
		.attr = PRESTERA_CMD_PORT_ATTR_CAPABILITY,
		.port = port->hw_id,
		.dev = port->dev_id,
	पूर्ण;
	काष्ठा prestera_msg_port_attr_resp resp;
	पूर्णांक err;

	err = prestera_cmd_ret(port->sw, PRESTERA_CMD_TYPE_PORT_ATTR_GET,
			       &req.cmd, माप(req), &resp.ret, माप(resp));
	अगर (err)
		वापस err;

	caps->supp_link_modes = resp.param.cap.link_mode;
	caps->transceiver = resp.param.cap.transceiver;
	caps->supp_fec = resp.param.cap.fec;
	caps->type = resp.param.cap.type;

	वापस err;
पूर्ण

पूर्णांक prestera_hw_port_remote_cap_get(स्थिर काष्ठा prestera_port *port,
				    u64 *link_mode_biपंचांगap)
अणु
	काष्ठा prestera_msg_port_attr_req req = अणु
		.attr = PRESTERA_CMD_PORT_ATTR_REMOTE_CAPABILITY,
		.port = port->hw_id,
		.dev = port->dev_id,
	पूर्ण;
	काष्ठा prestera_msg_port_attr_resp resp;
	पूर्णांक err;

	err = prestera_cmd_ret(port->sw, PRESTERA_CMD_TYPE_PORT_ATTR_GET,
			       &req.cmd, माप(req), &resp.ret, माप(resp));
	अगर (err)
		वापस err;

	*link_mode_biपंचांगap = resp.param.cap.link_mode;

	वापस 0;
पूर्ण

पूर्णांक prestera_hw_port_remote_fc_get(स्थिर काष्ठा prestera_port *port,
				   bool *छोड़ो, bool *asym_छोड़ो)
अणु
	काष्ठा prestera_msg_port_attr_req req = अणु
		.attr = PRESTERA_CMD_PORT_ATTR_REMOTE_FC,
		.port = port->hw_id,
		.dev = port->dev_id,
	पूर्ण;
	काष्ठा prestera_msg_port_attr_resp resp;
	पूर्णांक err;

	err = prestera_cmd_ret(port->sw, PRESTERA_CMD_TYPE_PORT_ATTR_GET,
			       &req.cmd, माप(req), &resp.ret, माप(resp));
	अगर (err)
		वापस err;

	चयन (resp.param.fc) अणु
	हाल PRESTERA_FC_SYMMETRIC:
		*छोड़ो = true;
		*asym_छोड़ो = false;
		अवरोध;
	हाल PRESTERA_FC_ASYMMETRIC:
		*छोड़ो = false;
		*asym_छोड़ो = true;
		अवरोध;
	हाल PRESTERA_FC_SYMM_ASYMM:
		*छोड़ो = true;
		*asym_छोड़ो = true;
		अवरोध;
	शेष:
		*छोड़ो = false;
		*asym_छोड़ो = false;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक prestera_hw_port_type_get(स्थिर काष्ठा prestera_port *port, u8 *type)
अणु
	काष्ठा prestera_msg_port_attr_req req = अणु
		.attr = PRESTERA_CMD_PORT_ATTR_TYPE,
		.port = port->hw_id,
		.dev = port->dev_id,
	पूर्ण;
	काष्ठा prestera_msg_port_attr_resp resp;
	पूर्णांक err;

	err = prestera_cmd_ret(port->sw, PRESTERA_CMD_TYPE_PORT_ATTR_GET,
			       &req.cmd, माप(req), &resp.ret, माप(resp));
	अगर (err)
		वापस err;

	*type = resp.param.type;

	वापस 0;
पूर्ण

पूर्णांक prestera_hw_port_fec_get(स्थिर काष्ठा prestera_port *port, u8 *fec)
अणु
	काष्ठा prestera_msg_port_attr_req req = अणु
		.attr = PRESTERA_CMD_PORT_ATTR_FEC,
		.port = port->hw_id,
		.dev = port->dev_id,
	पूर्ण;
	काष्ठा prestera_msg_port_attr_resp resp;
	पूर्णांक err;

	err = prestera_cmd_ret(port->sw, PRESTERA_CMD_TYPE_PORT_ATTR_GET,
			       &req.cmd, माप(req), &resp.ret, माप(resp));
	अगर (err)
		वापस err;

	*fec = resp.param.fec;

	वापस 0;
पूर्ण

पूर्णांक prestera_hw_port_fec_set(स्थिर काष्ठा prestera_port *port, u8 fec)
अणु
	काष्ठा prestera_msg_port_attr_req req = अणु
		.attr = PRESTERA_CMD_PORT_ATTR_FEC,
		.port = port->hw_id,
		.dev = port->dev_id,
		.param = अणु
			.fec = fec,
		पूर्ण
	पूर्ण;

	वापस prestera_cmd(port->sw, PRESTERA_CMD_TYPE_PORT_ATTR_SET,
			    &req.cmd, माप(req));
पूर्ण

अटल u8 prestera_hw_mdix_to_eth(u8 mode)
अणु
	चयन (mode) अणु
	हाल PRESTERA_PORT_TP_MDI:
		वापस ETH_TP_MDI;
	हाल PRESTERA_PORT_TP_MDIX:
		वापस ETH_TP_MDI_X;
	हाल PRESTERA_PORT_TP_AUTO:
		वापस ETH_TP_MDI_AUTO;
	शेष:
		वापस ETH_TP_MDI_INVALID;
	पूर्ण
पूर्ण

अटल u8 prestera_hw_mdix_from_eth(u8 mode)
अणु
	चयन (mode) अणु
	हाल ETH_TP_MDI:
		वापस PRESTERA_PORT_TP_MDI;
	हाल ETH_TP_MDI_X:
		वापस PRESTERA_PORT_TP_MDIX;
	हाल ETH_TP_MDI_AUTO:
		वापस PRESTERA_PORT_TP_AUTO;
	शेष:
		वापस PRESTERA_PORT_TP_NA;
	पूर्ण
पूर्ण

पूर्णांक prestera_hw_port_mdix_get(स्थिर काष्ठा prestera_port *port, u8 *status,
			      u8 *admin_mode)
अणु
	काष्ठा prestera_msg_port_attr_req req = अणु
		.attr = PRESTERA_CMD_PORT_ATTR_MDIX,
		.port = port->hw_id,
		.dev = port->dev_id,
	पूर्ण;
	काष्ठा prestera_msg_port_attr_resp resp;
	पूर्णांक err;

	err = prestera_cmd_ret(port->sw, PRESTERA_CMD_TYPE_PORT_ATTR_GET,
			       &req.cmd, माप(req), &resp.ret, माप(resp));
	अगर (err)
		वापस err;

	*status = prestera_hw_mdix_to_eth(resp.param.mdix.status);
	*admin_mode = prestera_hw_mdix_to_eth(resp.param.mdix.admin_mode);

	वापस 0;
पूर्ण

पूर्णांक prestera_hw_port_mdix_set(स्थिर काष्ठा prestera_port *port, u8 mode)
अणु
	काष्ठा prestera_msg_port_attr_req req = अणु
		.attr = PRESTERA_CMD_PORT_ATTR_MDIX,
		.port = port->hw_id,
		.dev = port->dev_id,
	पूर्ण;

	req.param.mdix.admin_mode = prestera_hw_mdix_from_eth(mode);

	वापस prestera_cmd(port->sw, PRESTERA_CMD_TYPE_PORT_ATTR_SET,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_port_link_mode_set(स्थिर काष्ठा prestera_port *port, u32 mode)
अणु
	काष्ठा prestera_msg_port_attr_req req = अणु
		.attr = PRESTERA_CMD_PORT_ATTR_LINK_MODE,
		.port = port->hw_id,
		.dev = port->dev_id,
		.param = अणु
			.link_mode = mode,
		पूर्ण
	पूर्ण;

	वापस prestera_cmd(port->sw, PRESTERA_CMD_TYPE_PORT_ATTR_SET,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_port_link_mode_get(स्थिर काष्ठा prestera_port *port, u32 *mode)
अणु
	काष्ठा prestera_msg_port_attr_req req = अणु
		.attr = PRESTERA_CMD_PORT_ATTR_LINK_MODE,
		.port = port->hw_id,
		.dev = port->dev_id,
	पूर्ण;
	काष्ठा prestera_msg_port_attr_resp resp;
	पूर्णांक err;

	err = prestera_cmd_ret(port->sw, PRESTERA_CMD_TYPE_PORT_ATTR_GET,
			       &req.cmd, माप(req), &resp.ret, माप(resp));
	अगर (err)
		वापस err;

	*mode = resp.param.link_mode;

	वापस 0;
पूर्ण

पूर्णांक prestera_hw_port_speed_get(स्थिर काष्ठा prestera_port *port, u32 *speed)
अणु
	काष्ठा prestera_msg_port_attr_req req = अणु
		.attr = PRESTERA_CMD_PORT_ATTR_SPEED,
		.port = port->hw_id,
		.dev = port->dev_id,
	पूर्ण;
	काष्ठा prestera_msg_port_attr_resp resp;
	पूर्णांक err;

	err = prestera_cmd_ret(port->sw, PRESTERA_CMD_TYPE_PORT_ATTR_GET,
			       &req.cmd, माप(req), &resp.ret, माप(resp));
	अगर (err)
		वापस err;

	*speed = resp.param.speed;

	वापस 0;
पूर्ण

पूर्णांक prestera_hw_port_स्वतःneg_set(स्थिर काष्ठा prestera_port *port,
				 bool स्वतःneg, u64 link_modes, u8 fec)
अणु
	काष्ठा prestera_msg_port_attr_req req = अणु
		.attr = PRESTERA_CMD_PORT_ATTR_AUTONEG,
		.port = port->hw_id,
		.dev = port->dev_id,
		.param = अणु
			.स्वतःneg = अणु
				.link_mode = link_modes,
				.enable = स्वतःneg,
				.fec = fec,
			पूर्ण
		पूर्ण
	पूर्ण;

	वापस prestera_cmd(port->sw, PRESTERA_CMD_TYPE_PORT_ATTR_SET,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_port_स्वतःneg_restart(काष्ठा prestera_port *port)
अणु
	काष्ठा prestera_msg_port_attr_req req = अणु
		.attr = PRESTERA_CMD_PORT_ATTR_AUTONEG_RESTART,
		.port = port->hw_id,
		.dev = port->dev_id,
	पूर्ण;

	वापस prestera_cmd(port->sw, PRESTERA_CMD_TYPE_PORT_ATTR_SET,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_port_duplex_get(स्थिर काष्ठा prestera_port *port, u8 *duplex)
अणु
	काष्ठा prestera_msg_port_attr_req req = अणु
		.attr = PRESTERA_CMD_PORT_ATTR_DUPLEX,
		.port = port->hw_id,
		.dev = port->dev_id,
	पूर्ण;
	काष्ठा prestera_msg_port_attr_resp resp;
	पूर्णांक err;

	err = prestera_cmd_ret(port->sw, PRESTERA_CMD_TYPE_PORT_ATTR_GET,
			       &req.cmd, माप(req), &resp.ret, माप(resp));
	अगर (err)
		वापस err;

	*duplex = resp.param.duplex;

	वापस 0;
पूर्ण

पूर्णांक prestera_hw_port_stats_get(स्थिर काष्ठा prestera_port *port,
			       काष्ठा prestera_port_stats *st)
अणु
	काष्ठा prestera_msg_port_attr_req req = अणु
		.attr = PRESTERA_CMD_PORT_ATTR_STATS,
		.port = port->hw_id,
		.dev = port->dev_id,
	पूर्ण;
	काष्ठा prestera_msg_port_stats_resp resp;
	u64 *hw = resp.stats;
	पूर्णांक err;

	err = prestera_cmd_ret(port->sw, PRESTERA_CMD_TYPE_PORT_ATTR_GET,
			       &req.cmd, माप(req), &resp.ret, माप(resp));
	अगर (err)
		वापस err;

	st->good_octets_received = hw[PRESTERA_PORT_GOOD_OCTETS_RCV_CNT];
	st->bad_octets_received = hw[PRESTERA_PORT_BAD_OCTETS_RCV_CNT];
	st->mac_trans_error = hw[PRESTERA_PORT_MAC_TRANSMIT_ERR_CNT];
	st->broadcast_frames_received = hw[PRESTERA_PORT_BRDC_PKTS_RCV_CNT];
	st->multicast_frames_received = hw[PRESTERA_PORT_MC_PKTS_RCV_CNT];
	st->frames_64_octets = hw[PRESTERA_PORT_PKTS_64L_CNT];
	st->frames_65_to_127_octets = hw[PRESTERA_PORT_PKTS_65TO127L_CNT];
	st->frames_128_to_255_octets = hw[PRESTERA_PORT_PKTS_128TO255L_CNT];
	st->frames_256_to_511_octets = hw[PRESTERA_PORT_PKTS_256TO511L_CNT];
	st->frames_512_to_1023_octets = hw[PRESTERA_PORT_PKTS_512TO1023L_CNT];
	st->frames_1024_to_max_octets = hw[PRESTERA_PORT_PKTS_1024TOMAXL_CNT];
	st->excessive_collision = hw[PRESTERA_PORT_EXCESSIVE_COLLISIONS_CNT];
	st->multicast_frames_sent = hw[PRESTERA_PORT_MC_PKTS_SENT_CNT];
	st->broadcast_frames_sent = hw[PRESTERA_PORT_BRDC_PKTS_SENT_CNT];
	st->fc_sent = hw[PRESTERA_PORT_FC_SENT_CNT];
	st->fc_received = hw[PRESTERA_PORT_GOOD_FC_RCV_CNT];
	st->buffer_overrun = hw[PRESTERA_PORT_DROP_EVENTS_CNT];
	st->undersize = hw[PRESTERA_PORT_UNDERSIZE_PKTS_CNT];
	st->fragments = hw[PRESTERA_PORT_FRAGMENTS_PKTS_CNT];
	st->oversize = hw[PRESTERA_PORT_OVERSIZE_PKTS_CNT];
	st->jabber = hw[PRESTERA_PORT_JABBER_PKTS_CNT];
	st->rx_error_frame_received = hw[PRESTERA_PORT_MAC_RCV_ERROR_CNT];
	st->bad_crc = hw[PRESTERA_PORT_BAD_CRC_CNT];
	st->collisions = hw[PRESTERA_PORT_COLLISIONS_CNT];
	st->late_collision = hw[PRESTERA_PORT_LATE_COLLISIONS_CNT];
	st->unicast_frames_received = hw[PRESTERA_PORT_GOOD_UC_PKTS_RCV_CNT];
	st->unicast_frames_sent = hw[PRESTERA_PORT_GOOD_UC_PKTS_SENT_CNT];
	st->sent_multiple = hw[PRESTERA_PORT_MULTIPLE_PKTS_SENT_CNT];
	st->sent_deferred = hw[PRESTERA_PORT_DEFERRED_PKTS_SENT_CNT];
	st->good_octets_sent = hw[PRESTERA_PORT_GOOD_OCTETS_SENT_CNT];

	वापस 0;
पूर्ण

पूर्णांक prestera_hw_port_learning_set(काष्ठा prestera_port *port, bool enable)
अणु
	काष्ठा prestera_msg_port_attr_req req = अणु
		.attr = PRESTERA_CMD_PORT_ATTR_LEARNING,
		.port = port->hw_id,
		.dev = port->dev_id,
		.param = अणु
			.learning = enable,
		पूर्ण
	पूर्ण;

	वापस prestera_cmd(port->sw, PRESTERA_CMD_TYPE_PORT_ATTR_SET,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_port_flood_set(काष्ठा prestera_port *port, bool flood)
अणु
	काष्ठा prestera_msg_port_attr_req req = अणु
		.attr = PRESTERA_CMD_PORT_ATTR_FLOOD,
		.port = port->hw_id,
		.dev = port->dev_id,
		.param = अणु
			.flood = flood,
		पूर्ण
	पूर्ण;

	वापस prestera_cmd(port->sw, PRESTERA_CMD_TYPE_PORT_ATTR_SET,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_vlan_create(काष्ठा prestera_चयन *sw, u16 vid)
अणु
	काष्ठा prestera_msg_vlan_req req = अणु
		.vid = vid,
	पूर्ण;

	वापस prestera_cmd(sw, PRESTERA_CMD_TYPE_VLAN_CREATE,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_vlan_delete(काष्ठा prestera_चयन *sw, u16 vid)
अणु
	काष्ठा prestera_msg_vlan_req req = अणु
		.vid = vid,
	पूर्ण;

	वापस prestera_cmd(sw, PRESTERA_CMD_TYPE_VLAN_DELETE,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_vlan_port_set(काष्ठा prestera_port *port, u16 vid,
			      bool is_member, bool untagged)
अणु
	काष्ठा prestera_msg_vlan_req req = अणु
		.port = port->hw_id,
		.dev = port->dev_id,
		.vid = vid,
		.is_member = is_member,
		.is_tagged = !untagged,
	पूर्ण;

	वापस prestera_cmd(port->sw, PRESTERA_CMD_TYPE_VLAN_PORT_SET,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_vlan_port_vid_set(काष्ठा prestera_port *port, u16 vid)
अणु
	काष्ठा prestera_msg_vlan_req req = अणु
		.port = port->hw_id,
		.dev = port->dev_id,
		.vid = vid,
	पूर्ण;

	वापस prestera_cmd(port->sw, PRESTERA_CMD_TYPE_VLAN_PVID_SET,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_vlan_port_stp_set(काष्ठा prestera_port *port, u16 vid, u8 state)
अणु
	काष्ठा prestera_msg_stp_req req = अणु
		.port = port->hw_id,
		.dev = port->dev_id,
		.vid = vid,
		.state = state,
	पूर्ण;

	वापस prestera_cmd(port->sw, PRESTERA_CMD_TYPE_STP_PORT_SET,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_fdb_add(काष्ठा prestera_port *port, स्थिर अचिन्हित अक्षर *mac,
			u16 vid, bool dynamic)
अणु
	काष्ठा prestera_msg_fdb_req req = अणु
		.port = port->hw_id,
		.dev = port->dev_id,
		.vid = vid,
		.dynamic = dynamic,
	पूर्ण;

	ether_addr_copy(req.mac, mac);

	वापस prestera_cmd(port->sw, PRESTERA_CMD_TYPE_FDB_ADD,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_fdb_del(काष्ठा prestera_port *port, स्थिर अचिन्हित अक्षर *mac,
			u16 vid)
अणु
	काष्ठा prestera_msg_fdb_req req = अणु
		.port = port->hw_id,
		.dev = port->dev_id,
		.vid = vid,
	पूर्ण;

	ether_addr_copy(req.mac, mac);

	वापस prestera_cmd(port->sw, PRESTERA_CMD_TYPE_FDB_DELETE,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_fdb_flush_port(काष्ठा prestera_port *port, u32 mode)
अणु
	काष्ठा prestera_msg_fdb_req req = अणु
		.port = port->hw_id,
		.dev = port->dev_id,
		.flush_mode = mode,
	पूर्ण;

	वापस prestera_cmd(port->sw, PRESTERA_CMD_TYPE_FDB_FLUSH_PORT,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_fdb_flush_vlan(काष्ठा prestera_चयन *sw, u16 vid, u32 mode)
अणु
	काष्ठा prestera_msg_fdb_req req = अणु
		.vid = vid,
		.flush_mode = mode,
	पूर्ण;

	वापस prestera_cmd(sw, PRESTERA_CMD_TYPE_FDB_FLUSH_VLAN,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_fdb_flush_port_vlan(काष्ठा prestera_port *port, u16 vid,
				    u32 mode)
अणु
	काष्ठा prestera_msg_fdb_req req = अणु
		.port = port->hw_id,
		.dev = port->dev_id,
		.vid = vid,
		.flush_mode = mode,
	पूर्ण;

	वापस prestera_cmd(port->sw, PRESTERA_CMD_TYPE_FDB_FLUSH_PORT_VLAN,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_bridge_create(काष्ठा prestera_चयन *sw, u16 *bridge_id)
अणु
	काष्ठा prestera_msg_bridge_resp resp;
	काष्ठा prestera_msg_bridge_req req;
	पूर्णांक err;

	err = prestera_cmd_ret(sw, PRESTERA_CMD_TYPE_BRIDGE_CREATE,
			       &req.cmd, माप(req),
			       &resp.ret, माप(resp));
	अगर (err)
		वापस err;

	*bridge_id = resp.bridge;

	वापस 0;
पूर्ण

पूर्णांक prestera_hw_bridge_delete(काष्ठा prestera_चयन *sw, u16 bridge_id)
अणु
	काष्ठा prestera_msg_bridge_req req = अणु
		.bridge = bridge_id,
	पूर्ण;

	वापस prestera_cmd(sw, PRESTERA_CMD_TYPE_BRIDGE_DELETE,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_bridge_port_add(काष्ठा prestera_port *port, u16 bridge_id)
अणु
	काष्ठा prestera_msg_bridge_req req = अणु
		.bridge = bridge_id,
		.port = port->hw_id,
		.dev = port->dev_id,
	पूर्ण;

	वापस prestera_cmd(port->sw, PRESTERA_CMD_TYPE_BRIDGE_PORT_ADD,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_bridge_port_delete(काष्ठा prestera_port *port, u16 bridge_id)
अणु
	काष्ठा prestera_msg_bridge_req req = अणु
		.bridge = bridge_id,
		.port = port->hw_id,
		.dev = port->dev_id,
	पूर्ण;

	वापस prestera_cmd(port->sw, PRESTERA_CMD_TYPE_BRIDGE_PORT_DELETE,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_rxtx_init(काष्ठा prestera_चयन *sw,
			  काष्ठा prestera_rxtx_params *params)
अणु
	काष्ठा prestera_msg_rxtx_resp resp;
	काष्ठा prestera_msg_rxtx_req req;
	पूर्णांक err;

	req.use_sdma = params->use_sdma;

	err = prestera_cmd_ret(sw, PRESTERA_CMD_TYPE_RXTX_INIT,
			       &req.cmd, माप(req), &resp.ret, माप(resp));
	अगर (err)
		वापस err;

	params->map_addr = resp.map_addr;

	वापस 0;
पूर्ण

पूर्णांक prestera_hw_rxtx_port_init(काष्ठा prestera_port *port)
अणु
	काष्ठा prestera_msg_rxtx_port_req req = अणु
		.port = port->hw_id,
		.dev = port->dev_id,
	पूर्ण;

	वापस prestera_cmd(port->sw, PRESTERA_CMD_TYPE_RXTX_PORT_INIT,
			    &req.cmd, माप(req));
पूर्ण

पूर्णांक prestera_hw_event_handler_रेजिस्टर(काष्ठा prestera_चयन *sw,
				       क्रमागत prestera_event_type type,
				       prestera_event_cb_t fn,
				       व्योम *arg)
अणु
	काष्ठा prestera_fw_event_handler *eh;

	eh = __find_event_handler(sw, type);
	अगर (eh)
		वापस -EEXIST;

	eh = kदो_स्मृति(माप(*eh), GFP_KERNEL);
	अगर (!eh)
		वापस -ENOMEM;

	eh->type = type;
	eh->func = fn;
	eh->arg = arg;

	INIT_LIST_HEAD(&eh->list);

	list_add_rcu(&eh->list, &sw->event_handlers);

	वापस 0;
पूर्ण

व्योम prestera_hw_event_handler_unरेजिस्टर(काष्ठा prestera_चयन *sw,
					  क्रमागत prestera_event_type type,
					  prestera_event_cb_t fn)
अणु
	काष्ठा prestera_fw_event_handler *eh;

	eh = __find_event_handler(sw, type);
	अगर (!eh)
		वापस;

	list_del_rcu(&eh->list);
	kमुक्त_rcu(eh, rcu);
पूर्ण
