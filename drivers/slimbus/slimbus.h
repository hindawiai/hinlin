<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2011-2017, The Linux Foundation
 */

#अगर_अघोषित _DRIVERS_SLIMBUS_H
#घोषणा _DRIVERS_SLIMBUS_H
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/completion.h>
#समावेश <linux/slimbus.h>

/* Standard values per SLIMbus spec needed by controllers and devices */
#घोषणा SLIM_CL_PER_SUPERFRAME		6144
#घोषणा SLIM_CL_PER_SUPERFRAME_DIV8	(SLIM_CL_PER_SUPERFRAME >> 3)

/* SLIMbus message types. Related to पूर्णांकerpretation of message code. */
#घोषणा SLIM_MSG_MT_CORE			0x0
#घोषणा SLIM_MSG_MT_DEST_REFERRED_USER		0x2
#घोषणा SLIM_MSG_MT_SRC_REFERRED_USER		0x6

/*
 * SLIM Broadcast header क्रमmat
 * BYTE 0: MT[7:5] RL[4:0]
 * BYTE 1: RSVD[7] MC[6:0]
 * BYTE 2: RSVD[7:6] DT[5:4] PI[3:0]
 */
#घोषणा SLIM_MSG_MT_MASK	GENMASK(2, 0)
#घोषणा SLIM_MSG_MT_SHIFT	5
#घोषणा SLIM_MSG_RL_MASK	GENMASK(4, 0)
#घोषणा SLIM_MSG_RL_SHIFT	0
#घोषणा SLIM_MSG_MC_MASK	GENMASK(6, 0)
#घोषणा SLIM_MSG_MC_SHIFT	0
#घोषणा SLIM_MSG_DT_MASK	GENMASK(1, 0)
#घोषणा SLIM_MSG_DT_SHIFT	4

#घोषणा SLIM_HEADER_GET_MT(b)	((b >> SLIM_MSG_MT_SHIFT) & SLIM_MSG_MT_MASK)
#घोषणा SLIM_HEADER_GET_RL(b)	((b >> SLIM_MSG_RL_SHIFT) & SLIM_MSG_RL_MASK)
#घोषणा SLIM_HEADER_GET_MC(b)	((b >> SLIM_MSG_MC_SHIFT) & SLIM_MSG_MC_MASK)
#घोषणा SLIM_HEADER_GET_DT(b)	((b >> SLIM_MSG_DT_SHIFT) & SLIM_MSG_DT_MASK)

/* Device management messages used by this framework */
#घोषणा SLIM_MSG_MC_REPORT_PRESENT               0x1
#घोषणा SLIM_MSG_MC_ASSIGN_LOGICAL_ADDRESS       0x2
#घोषणा SLIM_MSG_MC_REPORT_ABSENT                0xF

/* Data channel management messages */
#घोषणा SLIM_MSG_MC_CONNECT_SOURCE		0x10
#घोषणा SLIM_MSG_MC_CONNECT_SINK		0x11
#घोषणा SLIM_MSG_MC_DISCONNECT_PORT		0x14
#घोषणा SLIM_MSG_MC_CHANGE_CONTENT		0x18

/* Clock छोड़ो Reconfiguration messages */
#घोषणा SLIM_MSG_MC_BEGIN_RECONFIGURATION        0x40
#घोषणा SLIM_MSG_MC_NEXT_PAUSE_CLOCK             0x4A
#घोषणा SLIM_MSG_MC_NEXT_DEFINE_CHANNEL          0x50
#घोषणा SLIM_MSG_MC_NEXT_DEFINE_CONTENT          0x51
#घोषणा SLIM_MSG_MC_NEXT_ACTIVATE_CHANNEL        0x54
#घोषणा SLIM_MSG_MC_NEXT_DEACTIVATE_CHANNEL      0x55
#घोषणा SLIM_MSG_MC_NEXT_REMOVE_CHANNEL          0x58
#घोषणा SLIM_MSG_MC_RECONFIGURE_NOW              0x5F

/* Clock छोड़ो values per SLIMbus spec */
#घोषणा SLIM_CLK_FAST				0
#घोषणा SLIM_CLK_CONST_PHASE			1
#घोषणा SLIM_CLK_UNSPECIFIED			2

/* Destination type Values */
#घोषणा SLIM_MSG_DEST_LOGICALADDR	0
#घोषणा SLIM_MSG_DEST_ENUMADDR		1
#घोषणा	SLIM_MSG_DEST_BROADCAST		3

/* Standard values per SLIMbus spec needed by controllers and devices */
#घोषणा SLIM_MAX_CLK_GEAR		10
#घोषणा SLIM_MIN_CLK_GEAR		1
#घोषणा SLIM_SLOT_LEN_BITS		4

/* Indicate that the frequency of the flow and the bus frequency are locked */
#घोषणा SLIM_CHANNEL_CONTENT_FL		BIT(7)

/* Standard values per SLIMbus spec needed by controllers and devices */
#घोषणा SLIM_CL_PER_SUPERFRAME		6144
#घोषणा SLIM_SLOTS_PER_SUPERFRAME	(SLIM_CL_PER_SUPERFRAME >> 2)
#घोषणा SLIM_SL_PER_SUPERFRAME		(SLIM_CL_PER_SUPERFRAME >> 2)
/* Manager's logical address is set to 0xFF per spec */
#घोषणा SLIM_LA_MANAGER 0xFF

#घोषणा SLIM_MAX_TIDS			256
/**
 * काष्ठा slim_framer - Represents SLIMbus framer.
 * Every controller may have multiple framers. There is 1 active framer device
 * responsible क्रम घड़ीing the bus.
 * Manager is responsible क्रम framer hand-over.
 * @dev: Driver model representation of the device.
 * @e_addr: Enumeration address of the framer.
 * @rootfreq: Root Frequency at which the framer can run. This is maximum
 *	frequency ('clock gear 10') at which the bus can operate.
 * @superfreq: Superframes per root frequency. Every frame is 6144 bits.
 */
काष्ठा slim_framer अणु
	काष्ठा device		dev;
	काष्ठा slim_eaddr	e_addr;
	पूर्णांक			rootfreq;
	पूर्णांक			superfreq;
पूर्ण;

#घोषणा to_slim_framer(d) container_of(d, काष्ठा slim_framer, dev)

/**
 * काष्ठा slim_msg_txn - Message to be sent by the controller.
 *			This काष्ठाure has packet header,
 *			payload and buffer to be filled (अगर any)
 * @rl: Header field. reमुख्यing length.
 * @mt: Header field. Message type.
 * @mc: Header field. LSB is message code क्रम type mt.
 * @dt: Header field. Destination type.
 * @ec: Element code. Used क्रम elemental access APIs.
 * @tid: Transaction ID. Used क्रम messages expecting response.
 *	(relevant क्रम message-codes involving पढ़ो operation)
 * @la: Logical address of the device this message is going to.
 *	(Not used when destination type is broadcast.)
 * @msg: Elemental access message to be पढ़ो/written
 * @comp: completion अगर पढ़ो/ग_लिखो is synchronous, used पूर्णांकernally
 *	क्रम tid based transactions.
 */
काष्ठा slim_msg_txn अणु
	u8			rl;
	u8			mt;
	u8			mc;
	u8			dt;
	u16			ec;
	u8			tid;
	u8			la;
	काष्ठा slim_val_inf	*msg;
	काष्ठा	completion	*comp;
पूर्ण;

/* Frequently used message transaction काष्ठाures */
#घोषणा DEFINE_SLIM_LDEST_TXN(name, mc, rl, la, msg) \
	काष्ठा slim_msg_txn name = अणु rl, 0, mc, SLIM_MSG_DEST_LOGICALADDR, 0,\
					0, la, msg, पूर्ण

#घोषणा DEFINE_SLIM_BCAST_TXN(name, mc, rl, la, msg) \
	काष्ठा slim_msg_txn name = अणु rl, 0, mc, SLIM_MSG_DEST_BROADCAST, 0,\
					0, la, msg, पूर्ण

#घोषणा DEFINE_SLIM_EDEST_TXN(name, mc, rl, la, msg) \
	काष्ठा slim_msg_txn name = अणु rl, 0, mc, SLIM_MSG_DEST_ENUMADDR, 0,\
					0, la, msg, पूर्ण
/**
 * क्रमागत slim_clk_state: SLIMbus controller's घड़ी state used पूर्णांकernally क्रम
 *	मुख्यtaining current घड़ी state.
 * @SLIM_CLK_ACTIVE: SLIMbus घड़ी is active
 * @SLIM_CLK_ENTERING_PAUSE: SLIMbus घड़ी छोड़ो sequence is being sent on the
 *	bus. If this succeeds, state changes to SLIM_CLK_PAUSED. If the
 *	transition fails, state changes back to SLIM_CLK_ACTIVE
 * @SLIM_CLK_PAUSED: SLIMbus controller घड़ी has छोड़ोd.
 */
क्रमागत slim_clk_state अणु
	SLIM_CLK_ACTIVE,
	SLIM_CLK_ENTERING_PAUSE,
	SLIM_CLK_PAUSED,
पूर्ण;

/**
 * काष्ठा slim_sched: Framework uses this काष्ठाure पूर्णांकernally क्रम scheduling.
 * @clk_state: Controller's घड़ी state from क्रमागत slim_clk_state
 * @छोड़ो_comp: Signals completion of घड़ी छोड़ो sequence. This is useful when
 *	client tries to call SLIMbus transaction when controller is entering
 *	घड़ी छोड़ो.
 * @m_reconf: This mutex is held until current reconfiguration (data channel
 *	scheduling, message bandwidth reservation) is करोne. Message APIs can
 *	use the bus concurrently when this mutex is held since elemental access
 *	messages can be sent on the bus when reconfiguration is in progress.
 */
काष्ठा slim_sched अणु
	क्रमागत slim_clk_state	clk_state;
	काष्ठा completion	छोड़ो_comp;
	काष्ठा mutex		m_reconf;
पूर्ण;

/**
 * क्रमागत slim_port_direction: SLIMbus port direction
 *
 * @SLIM_PORT_SINK: SLIMbus port is a sink
 * @SLIM_PORT_SOURCE: SLIMbus port is a source
 */
क्रमागत slim_port_direction अणु
	SLIM_PORT_SINK = 0,
	SLIM_PORT_SOURCE,
पूर्ण;
/**
 * क्रमागत slim_port_state: SLIMbus Port/Endpoपूर्णांक state machine
 *	according to SLIMbus Spec 2.0
 * @SLIM_PORT_DISCONNECTED: SLIMbus port is disconnected
 *	entered from Unconfigure/configured state after
 *	DISCONNECT_PORT or REMOVE_CHANNEL core command
 * @SLIM_PORT_UNCONFIGURED: SLIMbus port is in unconfigured state.
 *	entered from disconnect state after CONNECT_SOURCE/SINK core command
 * @SLIM_PORT_CONFIGURED: SLIMbus port is in configured state.
 *	entered from unconfigured state after DEFINE_CHANNEL, DEFINE_CONTENT
 *	and ACTIVATE_CHANNEL core commands. Ready क्रम data transmission.
 */
क्रमागत slim_port_state अणु
	SLIM_PORT_DISCONNECTED = 0,
	SLIM_PORT_UNCONFIGURED,
	SLIM_PORT_CONFIGURED,
पूर्ण;

/**
 * क्रमागत slim_channel_state: SLIMbus channel state machine used by core.
 * @SLIM_CH_STATE_DISCONNECTED: SLIMbus channel is disconnected
 * @SLIM_CH_STATE_ALLOCATED: SLIMbus channel is allocated
 * @SLIM_CH_STATE_ASSOCIATED: SLIMbus channel is associated with port
 * @SLIM_CH_STATE_DEFINED: SLIMbus channel parameters are defined
 * @SLIM_CH_STATE_CONTENT_DEFINED: SLIMbus channel content is defined
 * @SLIM_CH_STATE_ACTIVE: SLIMbus channel is active and पढ़ोy क्रम data
 * @SLIM_CH_STATE_REMOVED: SLIMbus channel is inactive and हटाओd
 */
क्रमागत slim_channel_state अणु
	SLIM_CH_STATE_DISCONNECTED = 0,
	SLIM_CH_STATE_ALLOCATED,
	SLIM_CH_STATE_ASSOCIATED,
	SLIM_CH_STATE_DEFINED,
	SLIM_CH_STATE_CONTENT_DEFINED,
	SLIM_CH_STATE_ACTIVE,
	SLIM_CH_STATE_REMOVED,
पूर्ण;

/**
 * क्रमागत slim_ch_data_fmt: SLIMbus channel data Type identअगरiers according to
 *	Table 60 of SLIMbus Spec 1.01.01
 * @SLIM_CH_DATA_FMT_NOT_DEFINED: Undefined
 * @SLIM_CH_DATA_FMT_LPCM_AUDIO: LPCM audio
 * @SLIM_CH_DATA_FMT_IEC61937_COMP_AUDIO: IEC61937 Compressed audio
 * @SLIM_CH_DATA_FMT_PACKED_PDM_AUDIO: Packed PDM audio
 */
क्रमागत slim_ch_data_fmt अणु
	SLIM_CH_DATA_FMT_NOT_DEFINED = 0,
	SLIM_CH_DATA_FMT_LPCM_AUDIO = 1,
	SLIM_CH_DATA_FMT_IEC61937_COMP_AUDIO = 2,
	SLIM_CH_DATA_FMT_PACKED_PDM_AUDIO = 3,
पूर्ण;

/**
 * क्रमागत slim_ch_aux_bit_fmt: SLIMbus channel Aux Field क्रमmat IDs according to
 *	Table 63 of SLIMbus Spec 2.0
 * @SLIM_CH_AUX_FMT_NOT_APPLICABLE: Undefined
 * @SLIM_CH_AUX_FMT_ZCUV_TUNNEL_IEC60958: ZCUV क्रम tunneling IEC60958
 * @SLIM_CH_AUX_FMT_USER_DEFINED: User defined
 */
क्रमागत slim_ch_aux_bit_fmt अणु
	SLIM_CH_AUX_FMT_NOT_APPLICABLE = 0,
	SLIM_CH_AUX_FMT_ZCUV_TUNNEL_IEC60958 = 1,
	SLIM_CH_AUX_FMT_USER_DEFINED = 0xF,
पूर्ण;

/**
 * काष्ठा slim_channel  - SLIMbus channel, used क्रम state machine
 *
 * @id: ID of channel
 * @prrate: Presense rate of channel from Table 66 of SLIMbus 2.0 Specs
 * @seg_dist: segment distribution code from Table 20 of SLIMbus 2.0 Specs
 * @data_fmt: Data क्रमmat of channel.
 * @aux_fmt: Aux क्रमmat क्रम this channel.
 * @state: channel state machine
 */
काष्ठा slim_channel अणु
	पूर्णांक id;
	पूर्णांक prrate;
	पूर्णांक seg_dist;
	क्रमागत slim_ch_data_fmt data_fmt;
	क्रमागत slim_ch_aux_bit_fmt aux_fmt;
	क्रमागत slim_channel_state state;
पूर्ण;

/**
 * काष्ठा slim_port  - SLIMbus port
 *
 * @id: Port id
 * @direction: Port direction, Source or Sink.
 * @state: state machine of port.
 * @ch: channel associated with this port.
 */
काष्ठा slim_port अणु
	पूर्णांक id;
	क्रमागत slim_port_direction direction;
	क्रमागत slim_port_state state;
	काष्ठा slim_channel ch;
पूर्ण;

/**
 * क्रमागत slim_transport_protocol: SLIMbus Transport protocol list from
 *	Table 47 of SLIMbus 2.0 specs.
 * @SLIM_PROTO_ISO: Isochronous Protocol, no flow control as data rate match
 *		channel rate flow control embedded in the data.
 * @SLIM_PROTO_PUSH: Pushed Protocol, includes flow control, Used to carry
 *		data whose rate	is equal to, or lower than the channel rate.
 * @SLIM_PROTO_PULL: Pulled Protocol, similar usage as pushed protocol
 *		but pull is a unicast.
 * @SLIM_PROTO_LOCKED: Locked Protocol
 * @SLIM_PROTO_ASYNC_SMPLX: Asynchronous Protocol-Simplex
 * @SLIM_PROTO_ASYNC_HALF_DUP: Asynchronous Protocol-Half-duplex
 * @SLIM_PROTO_EXT_SMPLX: Extended Asynchronous Protocol-Simplex
 * @SLIM_PROTO_EXT_HALF_DUP: Extended Asynchronous Protocol-Half-duplex
 */
क्रमागत slim_transport_protocol अणु
	SLIM_PROTO_ISO = 0,
	SLIM_PROTO_PUSH,
	SLIM_PROTO_PULL,
	SLIM_PROTO_LOCKED,
	SLIM_PROTO_ASYNC_SMPLX,
	SLIM_PROTO_ASYNC_HALF_DUP,
	SLIM_PROTO_EXT_SMPLX,
	SLIM_PROTO_EXT_HALF_DUP,
पूर्ण;

/**
 * काष्ठा slim_stream_runसमय  - SLIMbus stream runसमय instance
 *
 * @name: Name of the stream
 * @dev: SLIM Device instance associated with this stream
 * @direction: direction of stream
 * @prot: Transport protocol used in this stream
 * @rate: Data rate of samples *
 * @bps: bits per sample
 * @ratem: rate multipler which is super frame rate/data rate
 * @num_ports: number of ports
 * @ports: poपूर्णांकer to instance of ports
 * @node: list head क्रम stream associated with slim device.
 */
काष्ठा slim_stream_runसमय अणु
	स्थिर अक्षर *name;
	काष्ठा slim_device *dev;
	पूर्णांक direction;
	क्रमागत slim_transport_protocol prot;
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक bps;
	अचिन्हित पूर्णांक ratem;
	पूर्णांक num_ports;
	काष्ठा slim_port *ports;
	काष्ठा list_head node;
पूर्ण;

/**
 * काष्ठा slim_controller  - Controls every instance of SLIMbus
 *				(similar to 'master' on SPI)
 * @dev: Device पूर्णांकerface to this driver
 * @id: Board-specअगरic number identअगरier क्रम this controller/bus
 * @name: Name क्रम this controller
 * @min_cg: Minimum घड़ी gear supported by this controller (शेष value: 1)
 * @max_cg: Maximum घड़ी gear supported by this controller (शेष value: 10)
 * @clkgear: Current घड़ी gear in which this bus is running
 * @laddr_ida: logical address id allocator
 * @a_framer: Active framer which is घड़ीing the bus managed by this controller
 * @lock: Mutex protecting controller data काष्ठाures
 * @devices: Slim device list
 * @tid_idr: tid id allocator
 * @txn_lock: Lock to protect table of transactions
 * @sched: scheduler काष्ठाure used by the controller
 * @xfer_msg: Transfer a message on this controller (this can be a broadcast
 *	control/status message like data channel setup, or a unicast message
 *	like value element पढ़ो/ग_लिखो.
 * @set_laddr: Setup logical address at laddr क्रम the slave with elemental
 *	address e_addr. Drivers implementing controller will be expected to
 *	send unicast message to this device with its logical address.
 * @get_laddr: It is possible that controller needs to set fixed logical
 *	address table and get_laddr can be used in that हाल so that controller
 *	can करो this assignment. Use हाल is when the master is on the remote
 *	processor side, who is resposible क्रम allocating laddr.
 * @wakeup: This function poपूर्णांकer implements controller-specअगरic procedure
 *	to wake it up from घड़ी-छोड़ो. Framework will call this to bring
 *	the controller out of घड़ी छोड़ो.
 * @enable_stream: This function poपूर्णांकer implements controller-specअगरic procedure
 *	to enable a stream.
 * @disable_stream: This function poपूर्णांकer implements controller-specअगरic procedure
 *	to disable stream.
 *
 *	'Manager device' is responsible क्रम  device management, bandwidth
 *	allocation, channel setup, and port associations per channel.
 *	Device management means Logical address assignment/removal based on
 *	क्रमागतeration (report-present, report-असलent) of a device.
 *	Bandwidth allocation is करोne dynamically by the manager based on active
 *	channels on the bus, message-bandwidth requests made by SLIMbus devices.
 *	Based on current bandwidth usage, manager chooses a frequency to run
 *	the bus at (in steps of 'clock-gear', 1 through 10, each घड़ी gear
 *	representing twice the frequency than the previous gear).
 *	Manager is also responsible क्रम entering (and निकासing) low-घातer-mode
 *	(known as 'clock pause').
 *	Manager can करो hanकरोver of framer अगर there are multiple framers on the
 *	bus and a certain useहाल warrants using certain framer to aव्योम keeping
 *	previous framer being घातered-on.
 *
 *	Controller here perक्रमms duties of the manager device, and 'पूर्णांकerface
 *	device'. Interface device is responsible क्रम monitoring the bus and
 *	reporting inक्रमmation such as loss-of-synchronization, data
 *	slot-collision.
 */
काष्ठा slim_controller अणु
	काष्ठा device		*dev;
	अचिन्हित पूर्णांक		id;
	अक्षर			name[SLIMBUS_NAME_SIZE];
	पूर्णांक			min_cg;
	पूर्णांक			max_cg;
	पूर्णांक			clkgear;
	काष्ठा ida		laddr_ida;
	काष्ठा slim_framer	*a_framer;
	काष्ठा mutex		lock;
	काष्ठा list_head	devices;
	काष्ठा idr		tid_idr;
	spinlock_t		txn_lock;
	काष्ठा slim_sched	sched;
	पूर्णांक			(*xfer_msg)(काष्ठा slim_controller *ctrl,
					    काष्ठा slim_msg_txn *tx);
	पूर्णांक			(*set_laddr)(काष्ठा slim_controller *ctrl,
					     काष्ठा slim_eaddr *ea, u8 laddr);
	पूर्णांक			(*get_laddr)(काष्ठा slim_controller *ctrl,
					     काष्ठा slim_eaddr *ea, u8 *laddr);
	पूर्णांक		(*enable_stream)(काष्ठा slim_stream_runसमय *rt);
	पूर्णांक		(*disable_stream)(काष्ठा slim_stream_runसमय *rt);
	पूर्णांक			(*wakeup)(काष्ठा slim_controller *ctrl);
पूर्ण;

पूर्णांक slim_device_report_present(काष्ठा slim_controller *ctrl,
			       काष्ठा slim_eaddr *e_addr, u8 *laddr);
व्योम slim_report_असलent(काष्ठा slim_device *sbdev);
पूर्णांक slim_रेजिस्टर_controller(काष्ठा slim_controller *ctrl);
पूर्णांक slim_unरेजिस्टर_controller(काष्ठा slim_controller *ctrl);
व्योम slim_msg_response(काष्ठा slim_controller *ctrl, u8 *reply, u8 tid, u8 l);
पूर्णांक slim_करो_transfer(काष्ठा slim_controller *ctrl, काष्ठा slim_msg_txn *txn);
पूर्णांक slim_ctrl_clk_छोड़ो(काष्ठा slim_controller *ctrl, bool wakeup, u8 restart);
पूर्णांक slim_alloc_txn_tid(काष्ठा slim_controller *ctrl, काष्ठा slim_msg_txn *txn);
व्योम slim_मुक्त_txn_tid(काष्ठा slim_controller *ctrl, काष्ठा slim_msg_txn *txn);

अटल अंतरभूत bool slim_tid_txn(u8 mt, u8 mc)
अणु
	वापस (mt == SLIM_MSG_MT_CORE &&
		(mc == SLIM_MSG_MC_REQUEST_INFORMATION ||
		 mc == SLIM_MSG_MC_REQUEST_CLEAR_INFORMATION ||
		 mc == SLIM_MSG_MC_REQUEST_VALUE ||
		 mc == SLIM_MSG_MC_REQUEST_CHANGE_VALUE));
पूर्ण

अटल अंतरभूत bool slim_ec_txn(u8 mt, u8 mc)
अणु
	वापस (mt == SLIM_MSG_MT_CORE &&
		((mc >= SLIM_MSG_MC_REQUEST_INFORMATION &&
		  mc <= SLIM_MSG_MC_REPORT_INFORMATION) ||
		 (mc >= SLIM_MSG_MC_REQUEST_VALUE &&
		  mc <= SLIM_MSG_MC_CHANGE_VALUE)));
पूर्ण
#पूर्ण_अगर /* _LINUX_SLIMBUS_H */
