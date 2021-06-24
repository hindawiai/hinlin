<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause) */
/* Copyright(c) 2015-17 Intel Corporation. */

#अगर_अघोषित __SOUNDWIRE_H
#घोषणा __SOUNDWIRE_H

#समावेश <linux/mod_devicetable.h>
#समावेश <linux/bitfield.h>

काष्ठा sdw_bus;
काष्ठा sdw_slave;

/* SDW spec defines and क्रमागतs, as defined by MIPI 1.1. Spec */

/* SDW Broadcast Device Number */
#घोषणा SDW_BROADCAST_DEV_NUM		15

/* SDW Enumeration Device Number */
#घोषणा SDW_ENUM_DEV_NUM		0

/* SDW Group Device Numbers */
#घोषणा SDW_GROUP12_DEV_NUM		12
#घोषणा SDW_GROUP13_DEV_NUM		13

/* SDW Master Device Number, not supported yet */
#घोषणा SDW_MASTER_DEV_NUM		14

#घोषणा SDW_NUM_DEV_ID_REGISTERS	6
/* frame shape defines */

/*
 * Note: The maximum row define in SoundWire spec 1.1 is 23. In order to
 * fill hole with 0, one more dummy entry is added
 */
#घोषणा SDW_FRAME_ROWS		24
#घोषणा SDW_FRAME_COLS		8
#घोषणा SDW_FRAME_ROW_COLS		(SDW_FRAME_ROWS * SDW_FRAME_COLS)

#घोषणा SDW_FRAME_CTRL_BITS		48
#घोषणा SDW_MAX_DEVICES			11

#घोषणा SDW_MAX_PORTS			15
#घोषणा SDW_VALID_PORT_RANGE(n)		((n) < SDW_MAX_PORTS && (n) >= 1)

क्रमागत अणु
	SDW_PORT_सूचीN_SINK = 0,
	SDW_PORT_सूचीN_SOURCE,
	SDW_PORT_सूचीN_MAX,
पूर्ण;

/*
 * स्थिरants क्रम flow control, ports and transport
 *
 * these are bit masks as devices can have multiple capabilities
 */

/*
 * flow modes क्रम SDW port. These can be isochronous, tx controlled,
 * rx controlled or async
 */
#घोषणा SDW_PORT_FLOW_MODE_ISOCH	0
#घोषणा SDW_PORT_FLOW_MODE_TX_CNTRL	BIT(0)
#घोषणा SDW_PORT_FLOW_MODE_RX_CNTRL	BIT(1)
#घोषणा SDW_PORT_FLOW_MODE_ASYNC	GENMASK(1, 0)

/* sample packaging क्रम block. It can be per port or per channel */
#घोषणा SDW_BLOCK_PACKG_PER_PORT	BIT(0)
#घोषणा SDW_BLOCK_PACKG_PER_CH		BIT(1)

/**
 * क्रमागत sdw_slave_status - Slave status
 * @SDW_SLAVE_UNATTACHED: Slave is not attached with the bus.
 * @SDW_SLAVE_ATTACHED: Slave is attached with bus.
 * @SDW_SLAVE_ALERT: Some alert condition on the Slave
 * @SDW_SLAVE_RESERVED: Reserved क्रम future use
 */
क्रमागत sdw_slave_status अणु
	SDW_SLAVE_UNATTACHED = 0,
	SDW_SLAVE_ATTACHED = 1,
	SDW_SLAVE_ALERT = 2,
	SDW_SLAVE_RESERVED = 3,
पूर्ण;

/**
 * क्रमागत sdw_clk_stop_type: घड़ी stop operations
 *
 * @SDW_CLK_PRE_PREPARE: pre घड़ी stop prepare
 * @SDW_CLK_POST_PREPARE: post घड़ी stop prepare
 * @SDW_CLK_PRE_DEPREPARE: pre घड़ी stop de-prepare
 * @SDW_CLK_POST_DEPREPARE: post घड़ी stop de-prepare
 */
क्रमागत sdw_clk_stop_type अणु
	SDW_CLK_PRE_PREPARE = 0,
	SDW_CLK_POST_PREPARE,
	SDW_CLK_PRE_DEPREPARE,
	SDW_CLK_POST_DEPREPARE,
पूर्ण;

/**
 * क्रमागत sdw_command_response - Command response as defined by SDW spec
 * @SDW_CMD_OK: cmd was successful
 * @SDW_CMD_IGNORED: cmd was ignored
 * @SDW_CMD_FAIL: cmd was NACKed
 * @SDW_CMD_TIMEOUT: cmd समयकरोut
 * @SDW_CMD_FAIL_OTHER: cmd failed due to other reason than above
 *
 * NOTE: The क्रमागत is dअगरferent than actual Spec as response in the Spec is
 * combination of ACK/NAK bits
 *
 * SDW_CMD_TIMEOUT/FAIL_OTHER is defined क्रम SW use, not in spec
 */
क्रमागत sdw_command_response अणु
	SDW_CMD_OK = 0,
	SDW_CMD_IGNORED = 1,
	SDW_CMD_FAIL = 2,
	SDW_CMD_TIMEOUT = 3,
	SDW_CMD_FAIL_OTHER = 4,
पूर्ण;

/* block group count क्रमागत */
क्रमागत sdw_dpn_grouping अणु
	SDW_BLK_GRP_CNT_1 = 0,
	SDW_BLK_GRP_CNT_2 = 1,
	SDW_BLK_GRP_CNT_3 = 2,
	SDW_BLK_GRP_CNT_4 = 3,
पूर्ण;

/* block packing mode क्रमागत */
क्रमागत sdw_dpn_pkg_mode अणु
	SDW_BLK_PKG_PER_PORT = 0,
	SDW_BLK_PKG_PER_CHANNEL = 1
पूर्ण;

/**
 * क्रमागत sdw_stream_type: data stream type
 *
 * @SDW_STREAM_PCM: PCM data stream
 * @SDW_STREAM_PDM: PDM data stream
 *
 * spec करोesn't define this, but is used in implementation
 */
क्रमागत sdw_stream_type अणु
	SDW_STREAM_PCM = 0,
	SDW_STREAM_PDM = 1,
पूर्ण;

/**
 * क्रमागत sdw_data_direction: Data direction
 *
 * @SDW_DATA_सूची_RX: Data पूर्णांकo Port
 * @SDW_DATA_सूची_TX: Data out of Port
 */
क्रमागत sdw_data_direction अणु
	SDW_DATA_सूची_RX = 0,
	SDW_DATA_सूची_TX = 1,
पूर्ण;

/**
 * क्रमागत sdw_port_data_mode: Data Port mode
 *
 * @SDW_PORT_DATA_MODE_NORMAL: Normal data mode where audio data is received
 * and transmitted.
 * @SDW_PORT_DATA_MODE_PRBS: Test mode which uses a PRBS generator to produce
 * a pseuकरो अक्रमom data pattern that is transferred
 * @SDW_PORT_DATA_MODE_STATIC_0: Simple test mode which uses अटल value of
 * logic 0. The encoding will result in no संकेत transitions
 * @SDW_PORT_DATA_MODE_STATIC_1: Simple test mode which uses अटल value of
 * logic 1. The encoding will result in संकेत transitions at every bitslot
 * owned by this Port
 */
क्रमागत sdw_port_data_mode अणु
	SDW_PORT_DATA_MODE_NORMAL = 0,
	SDW_PORT_DATA_MODE_PRBS = 1,
	SDW_PORT_DATA_MODE_STATIC_0 = 2,
	SDW_PORT_DATA_MODE_STATIC_1 = 3,
पूर्ण;

/*
 * SDW properties, defined in MIPI DisCo spec v1.0
 */
क्रमागत sdw_clk_stop_reset_behave अणु
	SDW_CLK_STOP_KEEP_STATUS = 1,
पूर्ण;

/**
 * क्रमागत sdw_p15_behave - Slave Port 15 behaviour when the Master attempts a
 * पढ़ो
 * @SDW_P15_READ_IGNORED: Read is ignored
 * @SDW_P15_CMD_OK: Command is ok
 */
क्रमागत sdw_p15_behave अणु
	SDW_P15_READ_IGNORED = 0,
	SDW_P15_CMD_OK = 1,
पूर्ण;

/**
 * क्रमागत sdw_dpn_type - Data port types
 * @SDW_DPN_FULL: Full Data Port is supported
 * @SDW_DPN_SIMPLE: Simplअगरied Data Port as defined in spec.
 * DPN_SampleCtrl2, DPN_OffsetCtrl2, DPN_HCtrl and DPN_BlockCtrl3
 * are not implemented.
 * @SDW_DPN_REDUCED: Reduced Data Port as defined in spec.
 * DPN_SampleCtrl2, DPN_HCtrl are not implemented.
 */
क्रमागत sdw_dpn_type अणु
	SDW_DPN_FULL = 0,
	SDW_DPN_SIMPLE = 1,
	SDW_DPN_REDUCED = 2,
पूर्ण;

/**
 * क्रमागत sdw_clk_stop_mode - Clock Stop modes
 * @SDW_CLK_STOP_MODE0: Slave can जारी operation seamlessly on घड़ी
 * restart
 * @SDW_CLK_STOP_MODE1: Slave may have entered a deeper घातer-saving mode,
 * not capable of continuing operation seamlessly when the घड़ी restarts
 */
क्रमागत sdw_clk_stop_mode अणु
	SDW_CLK_STOP_MODE0 = 0,
	SDW_CLK_STOP_MODE1 = 1,
पूर्ण;

/**
 * काष्ठा sdw_dp0_prop - DP0 properties
 * @max_word: Maximum number of bits in a Payload Channel Sample, 1 to 64
 * (inclusive)
 * @min_word: Minimum number of bits in a Payload Channel Sample, 1 to 64
 * (inclusive)
 * @num_words: number of wordlengths supported
 * @words: wordlengths supported
 * @BRA_flow_controlled: Slave implementation results in an OK_NotReady
 * response
 * @simple_ch_prep_sm: If channel prepare sequence is required
 * @imp_def_पूर्णांकerrupts: If set, each bit corresponds to support क्रम
 * implementation-defined पूर्णांकerrupts
 *
 * The wordlengths are specअगरied by Spec as max, min AND number of
 * discrete values, implementation can define based on the wordlengths they
 * support
 */
काष्ठा sdw_dp0_prop अणु
	u32 max_word;
	u32 min_word;
	u32 num_words;
	u32 *words;
	bool BRA_flow_controlled;
	bool simple_ch_prep_sm;
	bool imp_def_पूर्णांकerrupts;
पूर्ण;

/**
 * काष्ठा sdw_dpn_audio_mode - Audio mode properties क्रम DPn
 * @bus_min_freq: Minimum bus frequency, in Hz
 * @bus_max_freq: Maximum bus frequency, in Hz
 * @bus_num_freq: Number of discrete frequencies supported
 * @bus_freq: Discrete bus frequencies, in Hz
 * @min_freq: Minimum sampling frequency, in Hz
 * @max_freq: Maximum sampling bus frequency, in Hz
 * @num_freq: Number of discrete sampling frequency supported
 * @freq: Discrete sampling frequencies, in Hz
 * @prep_ch_behave: Specअगरies the dependencies between Channel Prepare
 * sequence and bus घड़ी configuration
 * If 0, Channel Prepare can happen at any Bus घड़ी rate
 * If 1, Channel Prepare sequence shall happen only after Bus घड़ी is
 * changed to a frequency supported by this mode or compatible modes
 * described by the next field
 * @glitchless: Biपंचांगap describing possible glitchless transitions from this
 * Audio Mode to other Audio Modes
 */
काष्ठा sdw_dpn_audio_mode अणु
	u32 bus_min_freq;
	u32 bus_max_freq;
	u32 bus_num_freq;
	u32 *bus_freq;
	u32 max_freq;
	u32 min_freq;
	u32 num_freq;
	u32 *freq;
	u32 prep_ch_behave;
	u32 glitchless;
पूर्ण;

/**
 * काष्ठा sdw_dpn_prop - Data Port DPn properties
 * @num: port number
 * @max_word: Maximum number of bits in a Payload Channel Sample, 1 to 64
 * (inclusive)
 * @min_word: Minimum number of bits in a Payload Channel Sample, 1 to 64
 * (inclusive)
 * @num_words: Number of discrete supported wordlengths
 * @words: Discrete supported wordlength
 * @type: Data port type. Full, Simplअगरied or Reduced
 * @max_grouping: Maximum number of samples that can be grouped together क्रम
 * a full data port
 * @simple_ch_prep_sm: If the port supports simplअगरied channel prepare state
 * machine
 * @ch_prep_समयout: Port-specअगरic समयout value, in milliseconds
 * @imp_def_पूर्णांकerrupts: If set, each bit corresponds to support क्रम
 * implementation-defined पूर्णांकerrupts
 * @max_ch: Maximum channels supported
 * @min_ch: Minimum channels supported
 * @num_channels: Number of discrete channels supported
 * @channels: Discrete channels supported
 * @num_ch_combinations: Number of channel combinations supported
 * @ch_combinations: Channel combinations supported
 * @modes: SDW mode supported
 * @max_async_buffer: Number of samples that this port can buffer in
 * asynchronous modes
 * @block_pack_mode: Type of block port mode supported
 * @पढ़ो_only_wordlength: Read Only wordlength field in DPN_BlockCtrl1 रेजिस्टर
 * @port_encoding: Payload Channel Sample encoding schemes supported
 * @audio_modes: Audio modes supported
 */
काष्ठा sdw_dpn_prop अणु
	u32 num;
	u32 max_word;
	u32 min_word;
	u32 num_words;
	u32 *words;
	क्रमागत sdw_dpn_type type;
	u32 max_grouping;
	bool simple_ch_prep_sm;
	u32 ch_prep_समयout;
	u32 imp_def_पूर्णांकerrupts;
	u32 max_ch;
	u32 min_ch;
	u32 num_channels;
	u32 *channels;
	u32 num_ch_combinations;
	u32 *ch_combinations;
	u32 modes;
	u32 max_async_buffer;
	bool block_pack_mode;
	bool पढ़ो_only_wordlength;
	u32 port_encoding;
	काष्ठा sdw_dpn_audio_mode *audio_modes;
पूर्ण;

/**
 * काष्ठा sdw_slave_prop - SoundWire Slave properties
 * @mipi_revision: Spec version of the implementation
 * @wake_capable: Wake-up events are supported
 * @test_mode_capable: If test mode is supported
 * @clk_stop_mode1: Clock-Stop Mode 1 is supported
 * @simple_clk_stop_capable: Simple घड़ी mode is supported
 * @clk_stop_समयout: Worst-हाल latency of the Clock Stop Prepare State
 * Machine transitions, in milliseconds
 * @ch_prep_समयout: Worst-हाल latency of the Channel Prepare State Machine
 * transitions, in milliseconds
 * @reset_behave: Slave keeps the status of the SlaveStopClockPrepare
 * state machine (P=1 SCSP_SM) after निकास from घड़ी-stop mode1
 * @high_PHY_capable: Slave is HighPHY capable
 * @paging_support: Slave implements paging रेजिस्टरs SCP_AddrPage1 and
 * SCP_AddrPage2
 * @bank_delay_support: Slave implements bank delay/bridge support रेजिस्टरs
 * SCP_BankDelay and SCP_NextFrame
 * @p15_behave: Slave behavior when the Master attempts a पढ़ो to the Port15
 * alias
 * @lane_control_support: Slave supports lane control
 * @master_count: Number of Masters present on this Slave
 * @source_ports: Biपंचांगap identअगरying source ports
 * @sink_ports: Biपंचांगap identअगरying sink ports
 * @dp0_prop: Data Port 0 properties
 * @src_dpn_prop: Source Data Port N properties
 * @sink_dpn_prop: Sink Data Port N properties
 * @scp_पूर्णांक1_mask: SCP_INT1_MASK desired settings
 * @quirks: biपंचांगask identअगरying deltas from the MIPI specअगरication
 * @is_sdca: the Slave supports the SDCA specअगरication
 */
काष्ठा sdw_slave_prop अणु
	u32 mipi_revision;
	bool wake_capable;
	bool test_mode_capable;
	bool clk_stop_mode1;
	bool simple_clk_stop_capable;
	u32 clk_stop_समयout;
	u32 ch_prep_समयout;
	क्रमागत sdw_clk_stop_reset_behave reset_behave;
	bool high_PHY_capable;
	bool paging_support;
	bool bank_delay_support;
	क्रमागत sdw_p15_behave p15_behave;
	bool lane_control_support;
	u32 master_count;
	u32 source_ports;
	u32 sink_ports;
	काष्ठा sdw_dp0_prop *dp0_prop;
	काष्ठा sdw_dpn_prop *src_dpn_prop;
	काष्ठा sdw_dpn_prop *sink_dpn_prop;
	u8 scp_पूर्णांक1_mask;
	u32 quirks;
	bool is_sdca;
पूर्ण;

#घोषणा SDW_SLAVE_QUIRKS_INVALID_INITIAL_PARITY	BIT(0)

/**
 * काष्ठा sdw_master_prop - Master properties
 * @revision: MIPI spec version of the implementation
 * @clk_stop_modes: Biपंचांगap, bit N set when घड़ी-stop-modeN supported
 * @max_clk_freq: Maximum Bus घड़ी frequency, in Hz
 * @num_clk_gears: Number of घड़ी gears supported
 * @clk_gears: Clock gears supported
 * @num_clk_freq: Number of घड़ी frequencies supported, in Hz
 * @clk_freq: Clock frequencies supported, in Hz
 * @शेष_frame_rate: Controller शेष Frame rate, in Hz
 * @शेष_row: Number of rows
 * @शेष_col: Number of columns
 * @dynamic_frame: Dynamic frame shape supported
 * @err_threshold: Number of बार that software may retry sending a single
 * command
 * @mclk_freq: घड़ी reference passed to SoundWire Master, in Hz.
 * @hw_disabled: अगर true, the Master is not functional, typically due to pin-mux
 * @quirks: biपंचांगask identअगरying optional behavior beyond the scope of the MIPI specअगरication
 */
काष्ठा sdw_master_prop अणु
	u32 revision;
	u32 clk_stop_modes;
	u32 max_clk_freq;
	u32 num_clk_gears;
	u32 *clk_gears;
	u32 num_clk_freq;
	u32 *clk_freq;
	u32 शेष_frame_rate;
	u32 शेष_row;
	u32 शेष_col;
	bool dynamic_frame;
	u32 err_threshold;
	u32 mclk_freq;
	bool hw_disabled;
	u64 quirks;
पूर्ण;

/* Definitions क्रम Master quirks */

/*
 * In a number of platक्रमms bus clashes are reported after a hardware
 * reset but without any explanations or evidence of a real problem.
 * The following quirk will discard all initial bus clash पूर्णांकerrupts
 * but will leave the detection on should real bus clashes happen
 */
#घोषणा SDW_MASTER_QUIRKS_CLEAR_INITIAL_CLASH	BIT(0)

/*
 * Some Slave devices have known issues with incorrect parity errors
 * reported after a hardware reset. However during पूर्णांकegration unexplained
 * parity errors can be reported by Slave devices, possibly due to electrical
 * issues at the Master level.
 * The following quirk will discard all initial parity errors but will leave
 * the detection on should real parity errors happen.
 */
#घोषणा SDW_MASTER_QUIRKS_CLEAR_INITIAL_PARITY	BIT(1)

पूर्णांक sdw_master_पढ़ो_prop(काष्ठा sdw_bus *bus);
पूर्णांक sdw_slave_पढ़ो_prop(काष्ठा sdw_slave *slave);

/*
 * SDW Slave Structures and APIs
 */

#घोषणा SDW_IGNORED_UNIQUE_ID 0xFF

/**
 * काष्ठा sdw_slave_id - Slave ID
 * @mfg_id: MIPI Manufacturer ID
 * @part_id: Device Part ID
 * @class_id: MIPI Class ID (defined starting with SoundWire 1.2 spec)
 * @unique_id: Device unique ID
 * @sdw_version: SDW version implemented
 *
 * The order of the IDs here करोes not follow the DisCo spec definitions
 */
काष्ठा sdw_slave_id अणु
	__u16 mfg_id;
	__u16 part_id;
	__u8 class_id;
	__u8 unique_id;
	__u8 sdw_version:4;
पूर्ण;

/*
 * Helper macros to extract the MIPI-defined IDs
 *
 * Spec definition
 *   Register		Bit	Contents
 *   DevId_0 [7:4]	47:44	sdw_version
 *   DevId_0 [3:0]	43:40	unique_id
 *   DevId_1		39:32	mfg_id [15:8]
 *   DevId_2		31:24	mfg_id [7:0]
 *   DevId_3		23:16	part_id [15:8]
 *   DevId_4		15:08	part_id [7:0]
 *   DevId_5		07:00	class_id
 *
 * The MIPI DisCo क्रम SoundWire defines in addition the link_id as bits 51:48
 */
#घोषणा SDW_DISCO_LINK_ID_MASK	GENMASK_ULL(51, 48)
#घोषणा SDW_VERSION_MASK	GENMASK_ULL(47, 44)
#घोषणा SDW_UNIQUE_ID_MASK	GENMASK_ULL(43, 40)
#घोषणा SDW_MFG_ID_MASK		GENMASK_ULL(39, 24)
#घोषणा SDW_PART_ID_MASK	GENMASK_ULL(23, 8)
#घोषणा SDW_CLASS_ID_MASK	GENMASK_ULL(7, 0)

#घोषणा SDW_DISCO_LINK_ID(addr)	FIELD_GET(SDW_DISCO_LINK_ID_MASK, addr)
#घोषणा SDW_VERSION(addr)	FIELD_GET(SDW_VERSION_MASK, addr)
#घोषणा SDW_UNIQUE_ID(addr)	FIELD_GET(SDW_UNIQUE_ID_MASK, addr)
#घोषणा SDW_MFG_ID(addr)	FIELD_GET(SDW_MFG_ID_MASK, addr)
#घोषणा SDW_PART_ID(addr)	FIELD_GET(SDW_PART_ID_MASK, addr)
#घोषणा SDW_CLASS_ID(addr)	FIELD_GET(SDW_CLASS_ID_MASK, addr)

/**
 * काष्ठा sdw_slave_पूर्णांकr_status - Slave पूर्णांकerrupt status
 * @sdca_cascade: set अगर the Slave device reports an SDCA पूर्णांकerrupt
 * @control_port: control port status
 * @port: data port status
 */
काष्ठा sdw_slave_पूर्णांकr_status अणु
	bool sdca_cascade;
	u8 control_port;
	u8 port[15];
पूर्ण;

/**
 * sdw_reg_bank - SoundWire रेजिस्टर banks
 * @SDW_BANK0: Soundwire रेजिस्टर bank 0
 * @SDW_BANK1: Soundwire रेजिस्टर bank 1
 */
क्रमागत sdw_reg_bank अणु
	SDW_BANK0,
	SDW_BANK1,
पूर्ण;

/**
 * काष्ठा sdw_bus_conf: Bus configuration
 *
 * @clk_freq: Clock frequency, in Hz
 * @num_rows: Number of rows in frame
 * @num_cols: Number of columns in frame
 * @bank: Next रेजिस्टर bank
 */
काष्ठा sdw_bus_conf अणु
	अचिन्हित पूर्णांक clk_freq;
	अचिन्हित पूर्णांक num_rows;
	अचिन्हित पूर्णांक num_cols;
	अचिन्हित पूर्णांक bank;
पूर्ण;

/**
 * काष्ठा sdw_prepare_ch: Prepare/De-prepare Data Port channel
 *
 * @num: Port number
 * @ch_mask: Active channel mask
 * @prepare: Prepare (true) /de-prepare (false) channel
 * @bank: Register bank, which bank Slave/Master driver should program क्रम
 * implementation defined रेजिस्टरs. This is always updated to next_bank
 * value पढ़ो from bus params.
 *
 */
काष्ठा sdw_prepare_ch अणु
	अचिन्हित पूर्णांक num;
	अचिन्हित पूर्णांक ch_mask;
	bool prepare;
	अचिन्हित पूर्णांक bank;
पूर्ण;

/**
 * क्रमागत sdw_port_prep_ops: Prepare operations क्रम Data Port
 *
 * @SDW_OPS_PORT_PRE_PREP: Pre prepare operation क्रम the Port
 * @SDW_OPS_PORT_PREP: Prepare operation क्रम the Port
 * @SDW_OPS_PORT_POST_PREP: Post prepare operation क्रम the Port
 */
क्रमागत sdw_port_prep_ops अणु
	SDW_OPS_PORT_PRE_PREP = 0,
	SDW_OPS_PORT_PREP = 1,
	SDW_OPS_PORT_POST_PREP = 2,
पूर्ण;

/**
 * काष्ठा sdw_bus_params: Structure holding bus configuration
 *
 * @curr_bank: Current bank in use (BANK0/BANK1)
 * @next_bank: Next bank to use (BANK0/BANK1). next_bank will always be
 * set to !curr_bank
 * @max_dr_freq: Maximum द्विगुन rate घड़ी frequency supported, in Hz
 * @curr_dr_freq: Current द्विगुन rate घड़ी frequency, in Hz
 * @bandwidth: Current bandwidth
 * @col: Active columns
 * @row: Active rows
 * @s_data_mode: NORMAL, STATIC or PRBS mode क्रम all Slave ports
 * @m_data_mode: NORMAL, STATIC or PRBS mode क्रम all Master ports. The value
 * should be the same to detect transmission issues, but can be dअगरferent to
 * test the पूर्णांकerrupt reports
 */
काष्ठा sdw_bus_params अणु
	क्रमागत sdw_reg_bank curr_bank;
	क्रमागत sdw_reg_bank next_bank;
	अचिन्हित पूर्णांक max_dr_freq;
	अचिन्हित पूर्णांक curr_dr_freq;
	अचिन्हित पूर्णांक bandwidth;
	अचिन्हित पूर्णांक col;
	अचिन्हित पूर्णांक row;
	पूर्णांक s_data_mode;
	पूर्णांक m_data_mode;
पूर्ण;

/**
 * काष्ठा sdw_slave_ops: Slave driver callback ops
 *
 * @पढ़ो_prop: Read Slave properties
 * @पूर्णांकerrupt_callback: Device पूर्णांकerrupt notअगरication (invoked in thपढ़ो
 * context)
 * @update_status: Update Slave status
 * @bus_config: Update the bus config क्रम Slave
 * @port_prep: Prepare the port with parameters
 */
काष्ठा sdw_slave_ops अणु
	पूर्णांक (*पढ़ो_prop)(काष्ठा sdw_slave *sdw);
	पूर्णांक (*पूर्णांकerrupt_callback)(काष्ठा sdw_slave *slave,
				  काष्ठा sdw_slave_पूर्णांकr_status *status);
	पूर्णांक (*update_status)(काष्ठा sdw_slave *slave,
			     क्रमागत sdw_slave_status status);
	पूर्णांक (*bus_config)(काष्ठा sdw_slave *slave,
			  काष्ठा sdw_bus_params *params);
	पूर्णांक (*port_prep)(काष्ठा sdw_slave *slave,
			 काष्ठा sdw_prepare_ch *prepare_ch,
			 क्रमागत sdw_port_prep_ops pre_ops);
	पूर्णांक (*get_clk_stop_mode)(काष्ठा sdw_slave *slave);
	पूर्णांक (*clk_stop)(काष्ठा sdw_slave *slave,
			क्रमागत sdw_clk_stop_mode mode,
			क्रमागत sdw_clk_stop_type type);

पूर्ण;

/**
 * काष्ठा sdw_slave - SoundWire Slave
 * @id: MIPI device ID
 * @dev: Linux device
 * @status: Status reported by the Slave
 * @bus: Bus handle
 * @ops: Slave callback ops
 * @prop: Slave properties
 * @debugfs: Slave debugfs
 * @node: node क्रम bus list
 * @port_पढ़ोy: Port पढ़ोy completion flag क्रम each Slave port
 * @m_port_map: अटल Master port map क्रम each Slave port
 * @dev_num: Current Device Number, values can be 0 or dev_num_sticky
 * @dev_num_sticky: one-समय अटल Device Number asचिन्हित by Bus
 * @probed: boolean tracking driver state
 * @probe_complete: completion utility to control potential races
 * on startup between driver probe/initialization and SoundWire
 * Slave state changes/implementation-defined पूर्णांकerrupts
 * @क्रमागतeration_complete: completion utility to control potential races
 * on startup between device क्रमागतeration and पढ़ो/ग_लिखो access to the
 * Slave device
 * @initialization_complete: completion utility to control potential races
 * on startup between device क्रमागतeration and settings being restored
 * @unattach_request: mask field to keep track why the Slave re-attached and
 * was re-initialized. This is useful to deal with potential race conditions
 * between the Master suspending and the codec resuming, and make sure that
 * when the Master triggered a reset the Slave is properly क्रमागतerated and
 * initialized
 * @first_पूर्णांकerrupt_करोne: status flag tracking अगर the पूर्णांकerrupt handling
 * क्रम a Slave happens क्रम the first समय after क्रमागतeration
 */
काष्ठा sdw_slave अणु
	काष्ठा sdw_slave_id id;
	काष्ठा device dev;
	क्रमागत sdw_slave_status status;
	काष्ठा sdw_bus *bus;
	स्थिर काष्ठा sdw_slave_ops *ops;
	काष्ठा sdw_slave_prop prop;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs;
#पूर्ण_अगर
	काष्ठा list_head node;
	काष्ठा completion port_पढ़ोy[SDW_MAX_PORTS];
	अचिन्हित पूर्णांक m_port_map[SDW_MAX_PORTS];
	क्रमागत sdw_clk_stop_mode curr_clk_stop_mode;
	u16 dev_num;
	u16 dev_num_sticky;
	bool probed;
	काष्ठा completion probe_complete;
	काष्ठा completion क्रमागतeration_complete;
	काष्ठा completion initialization_complete;
	u32 unattach_request;
	bool first_पूर्णांकerrupt_करोne;
पूर्ण;

#घोषणा dev_to_sdw_dev(_dev) container_of(_dev, काष्ठा sdw_slave, dev)

/**
 * काष्ठा sdw_master_device - SoundWire 'Master Device' representation
 * @dev: Linux device क्रम this Master
 * @bus: Bus handle लघुcut
 */
काष्ठा sdw_master_device अणु
	काष्ठा device dev;
	काष्ठा sdw_bus *bus;
पूर्ण;

#घोषणा dev_to_sdw_master_device(d)	\
	container_of(d, काष्ठा sdw_master_device, dev)

काष्ठा sdw_driver अणु
	स्थिर अक्षर *name;

	पूर्णांक (*probe)(काष्ठा sdw_slave *sdw,
			स्थिर काष्ठा sdw_device_id *id);
	पूर्णांक (*हटाओ)(काष्ठा sdw_slave *sdw);
	व्योम (*shutकरोwn)(काष्ठा sdw_slave *sdw);

	स्थिर काष्ठा sdw_device_id *id_table;
	स्थिर काष्ठा sdw_slave_ops *ops;

	काष्ठा device_driver driver;
पूर्ण;

#घोषणा SDW_SLAVE_ENTRY_EXT(_mfg_id, _part_id, _version, _c_id, _drv_data) \
	अणु .mfg_id = (_mfg_id), .part_id = (_part_id),		\
	  .sdw_version = (_version), .class_id = (_c_id),	\
	  .driver_data = (अचिन्हित दीर्घ)(_drv_data) पूर्ण

#घोषणा SDW_SLAVE_ENTRY(_mfg_id, _part_id, _drv_data)	\
	SDW_SLAVE_ENTRY_EXT((_mfg_id), (_part_id), 0, 0, (_drv_data))

पूर्णांक sdw_handle_slave_status(काष्ठा sdw_bus *bus,
			क्रमागत sdw_slave_status status[]);

/*
 * SDW master काष्ठाures and APIs
 */

/**
 * काष्ठा sdw_port_params: Data Port parameters
 *
 * @num: Port number
 * @bps: Word length of the Port
 * @flow_mode: Port Data flow mode
 * @data_mode: Test modes or normal mode
 *
 * This is used to program the Data Port based on Data Port stream
 * parameters.
 */
काष्ठा sdw_port_params अणु
	अचिन्हित पूर्णांक num;
	अचिन्हित पूर्णांक bps;
	अचिन्हित पूर्णांक flow_mode;
	अचिन्हित पूर्णांक data_mode;
पूर्ण;

/**
 * काष्ठा sdw_transport_params: Data Port Transport Parameters
 *
 * @blk_grp_ctrl_valid: Port implements block group control
 * @num: Port number
 * @blk_grp_ctrl: Block group control value
 * @sample_पूर्णांकerval: Sample पूर्णांकerval
 * @offset1: Blockoffset of the payload data
 * @offset2: Blockoffset of the payload data
 * @hstart: Horizontal start of the payload data
 * @hstop: Horizontal stop of the payload data
 * @blk_pkg_mode: Block per channel or block per port
 * @lane_ctrl: Data lane Port uses क्रम Data transfer. Currently only single
 * data lane is supported in bus
 *
 * This is used to program the Data Port based on Data Port transport
 * parameters. All these parameters are banked and can be modअगरied
 * during a bank चयन without any artअगरacts in audio stream.
 */
काष्ठा sdw_transport_params अणु
	bool blk_grp_ctrl_valid;
	अचिन्हित पूर्णांक port_num;
	अचिन्हित पूर्णांक blk_grp_ctrl;
	अचिन्हित पूर्णांक sample_पूर्णांकerval;
	अचिन्हित पूर्णांक offset1;
	अचिन्हित पूर्णांक offset2;
	अचिन्हित पूर्णांक hstart;
	अचिन्हित पूर्णांक hstop;
	अचिन्हित पूर्णांक blk_pkg_mode;
	अचिन्हित पूर्णांक lane_ctrl;
पूर्ण;

/**
 * काष्ठा sdw_enable_ch: Enable/disable Data Port channel
 *
 * @num: Port number
 * @ch_mask: Active channel mask
 * @enable: Enable (true) /disable (false) channel
 */
काष्ठा sdw_enable_ch अणु
	अचिन्हित पूर्णांक port_num;
	अचिन्हित पूर्णांक ch_mask;
	bool enable;
पूर्ण;

/**
 * काष्ठा sdw_master_port_ops: Callback functions from bus to Master
 * driver to set Master Data ports.
 *
 * @dpn_set_port_params: Set the Port parameters क्रम the Master Port.
 * Mandatory callback
 * @dpn_set_port_transport_params: Set transport parameters क्रम the Master
 * Port. Mandatory callback
 * @dpn_port_prep: Port prepare operations क्रम the Master Data Port.
 * @dpn_port_enable_ch: Enable the channels of Master Port.
 */
काष्ठा sdw_master_port_ops अणु
	पूर्णांक (*dpn_set_port_params)(काष्ठा sdw_bus *bus,
			काष्ठा sdw_port_params *port_params,
			अचिन्हित पूर्णांक bank);
	पूर्णांक (*dpn_set_port_transport_params)(काष्ठा sdw_bus *bus,
			काष्ठा sdw_transport_params *transport_params,
			क्रमागत sdw_reg_bank bank);
	पूर्णांक (*dpn_port_prep)(काष्ठा sdw_bus *bus,
			काष्ठा sdw_prepare_ch *prepare_ch);
	पूर्णांक (*dpn_port_enable_ch)(काष्ठा sdw_bus *bus,
			काष्ठा sdw_enable_ch *enable_ch, अचिन्हित पूर्णांक bank);
पूर्ण;

काष्ठा sdw_msg;

/**
 * काष्ठा sdw_defer - SDW deffered message
 * @length: message length
 * @complete: message completion
 * @msg: SDW message
 */
काष्ठा sdw_defer अणु
	पूर्णांक length;
	काष्ठा completion complete;
	काष्ठा sdw_msg *msg;
पूर्ण;

/**
 * काष्ठा sdw_master_ops - Master driver ops
 * @पढ़ो_prop: Read Master properties
 * @override_adr: Override value पढ़ो from firmware (quirk क्रम buggy firmware)
 * @xfer_msg: Transfer message callback
 * @xfer_msg_defer: Defer version of transfer message callback
 * @reset_page_addr: Reset the SCP page address रेजिस्टरs
 * @set_bus_conf: Set the bus configuration
 * @pre_bank_चयन: Callback क्रम pre bank चयन
 * @post_bank_चयन: Callback क्रम post bank चयन
 */
काष्ठा sdw_master_ops अणु
	पूर्णांक (*पढ़ो_prop)(काष्ठा sdw_bus *bus);
	u64 (*override_adr)
			(काष्ठा sdw_bus *bus, u64 addr);
	क्रमागत sdw_command_response (*xfer_msg)
			(काष्ठा sdw_bus *bus, काष्ठा sdw_msg *msg);
	क्रमागत sdw_command_response (*xfer_msg_defer)
			(काष्ठा sdw_bus *bus, काष्ठा sdw_msg *msg,
			काष्ठा sdw_defer *defer);
	क्रमागत sdw_command_response (*reset_page_addr)
			(काष्ठा sdw_bus *bus, अचिन्हित पूर्णांक dev_num);
	पूर्णांक (*set_bus_conf)(काष्ठा sdw_bus *bus,
			काष्ठा sdw_bus_params *params);
	पूर्णांक (*pre_bank_चयन)(काष्ठा sdw_bus *bus);
	पूर्णांक (*post_bank_चयन)(काष्ठा sdw_bus *bus);

पूर्ण;

/**
 * काष्ठा sdw_bus - SoundWire bus
 * @dev: Shortcut to &bus->md->dev to aव्योम changing the entire code.
 * @md: Master device
 * @link_id: Link id number, can be 0 to N, unique क्रम each Master
 * @id: bus प्रणाली-wide unique id
 * @slaves: list of Slaves on this bus
 * @asचिन्हित: Biपंचांगap क्रम Slave device numbers.
 * Bit set implies used number, bit clear implies unused number.
 * @bus_lock: bus lock
 * @msg_lock: message lock
 * @compute_params: poपूर्णांकs to Bus resource management implementation
 * @ops: Master callback ops
 * @port_ops: Master port callback ops
 * @params: Current bus parameters
 * @prop: Master properties
 * @m_rt_list: List of Master instance of all stream(s) running on Bus. This
 * is used to compute and program bus bandwidth, घड़ी, frame shape,
 * transport and port parameters
 * @debugfs: Bus debugfs
 * @defer_msg: Defer message
 * @clk_stop_समयout: Clock stop समयout computed
 * @bank_चयन_समयout: Bank चयन समयout computed
 * @multi_link: Store bus property that indicates अगर multi links
 * are supported. This flag is populated by drivers after पढ़ोing
 * appropriate firmware (ACPI/DT).
 * @hw_sync_min_links: Number of links used by a stream above which
 * hardware-based synchronization is required. This value is only
 * meaningful अगर multi_link is set. If set to 1, hardware-based
 * synchronization will be used even अगर a stream only uses a single
 * SoundWire segment.
 */
काष्ठा sdw_bus अणु
	काष्ठा device *dev;
	काष्ठा sdw_master_device *md;
	अचिन्हित पूर्णांक link_id;
	पूर्णांक id;
	काष्ठा list_head slaves;
	DECLARE_BITMAP(asचिन्हित, SDW_MAX_DEVICES);
	काष्ठा mutex bus_lock;
	काष्ठा mutex msg_lock;
	पूर्णांक (*compute_params)(काष्ठा sdw_bus *bus);
	स्थिर काष्ठा sdw_master_ops *ops;
	स्थिर काष्ठा sdw_master_port_ops *port_ops;
	काष्ठा sdw_bus_params params;
	काष्ठा sdw_master_prop prop;
	काष्ठा list_head m_rt_list;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs;
#पूर्ण_अगर
	काष्ठा sdw_defer defer_msg;
	अचिन्हित पूर्णांक clk_stop_समयout;
	u32 bank_चयन_समयout;
	bool multi_link;
	पूर्णांक hw_sync_min_links;
पूर्ण;

पूर्णांक sdw_bus_master_add(काष्ठा sdw_bus *bus, काष्ठा device *parent,
		       काष्ठा fwnode_handle *fwnode);
व्योम sdw_bus_master_delete(काष्ठा sdw_bus *bus);

/**
 * sdw_port_config: Master or Slave Port configuration
 *
 * @num: Port number
 * @ch_mask: channels mask क्रम port
 */
काष्ठा sdw_port_config अणु
	अचिन्हित पूर्णांक num;
	अचिन्हित पूर्णांक ch_mask;
पूर्ण;

/**
 * sdw_stream_config: Master or Slave stream configuration
 *
 * @frame_rate: Audio frame rate of the stream, in Hz
 * @ch_count: Channel count of the stream
 * @bps: Number of bits per audio sample
 * @direction: Data direction
 * @type: Stream type PCM or PDM
 */
काष्ठा sdw_stream_config अणु
	अचिन्हित पूर्णांक frame_rate;
	अचिन्हित पूर्णांक ch_count;
	अचिन्हित पूर्णांक bps;
	क्रमागत sdw_data_direction direction;
	क्रमागत sdw_stream_type type;
पूर्ण;

/**
 * sdw_stream_state: Stream states
 *
 * @SDW_STREAM_ALLOCATED: New stream allocated.
 * @SDW_STREAM_CONFIGURED: Stream configured
 * @SDW_STREAM_PREPARED: Stream prepared
 * @SDW_STREAM_ENABLED: Stream enabled
 * @SDW_STREAM_DISABLED: Stream disabled
 * @SDW_STREAM_DEPREPARED: Stream de-prepared
 * @SDW_STREAM_RELEASED: Stream released
 */
क्रमागत sdw_stream_state अणु
	SDW_STREAM_ALLOCATED = 0,
	SDW_STREAM_CONFIGURED = 1,
	SDW_STREAM_PREPARED = 2,
	SDW_STREAM_ENABLED = 3,
	SDW_STREAM_DISABLED = 4,
	SDW_STREAM_DEPREPARED = 5,
	SDW_STREAM_RELEASED = 6,
पूर्ण;

/**
 * sdw_stream_params: Stream parameters
 *
 * @rate: Sampling frequency, in Hz
 * @ch_count: Number of channels
 * @bps: bits per channel sample
 */
काष्ठा sdw_stream_params अणु
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक ch_count;
	अचिन्हित पूर्णांक bps;
पूर्ण;

/**
 * sdw_stream_runसमय: Runसमय stream parameters
 *
 * @name: SoundWire stream name
 * @params: Stream parameters
 * @state: Current state of the stream
 * @type: Stream type PCM or PDM
 * @master_list: List of Master runसमय(s) in this stream.
 * master_list can contain only one m_rt per Master instance
 * क्रम a stream
 * @m_rt_count: Count of Master runसमय(s) in this stream
 */
काष्ठा sdw_stream_runसमय अणु
	स्थिर अक्षर *name;
	काष्ठा sdw_stream_params params;
	क्रमागत sdw_stream_state state;
	क्रमागत sdw_stream_type type;
	काष्ठा list_head master_list;
	पूर्णांक m_rt_count;
पूर्ण;

काष्ठा sdw_stream_runसमय *sdw_alloc_stream(स्थिर अक्षर *stream_name);
व्योम sdw_release_stream(काष्ठा sdw_stream_runसमय *stream);

पूर्णांक sdw_compute_params(काष्ठा sdw_bus *bus);

पूर्णांक sdw_stream_add_master(काष्ठा sdw_bus *bus,
		काष्ठा sdw_stream_config *stream_config,
		काष्ठा sdw_port_config *port_config,
		अचिन्हित पूर्णांक num_ports,
		काष्ठा sdw_stream_runसमय *stream);
पूर्णांक sdw_stream_add_slave(काष्ठा sdw_slave *slave,
		काष्ठा sdw_stream_config *stream_config,
		काष्ठा sdw_port_config *port_config,
		अचिन्हित पूर्णांक num_ports,
		काष्ठा sdw_stream_runसमय *stream);
पूर्णांक sdw_stream_हटाओ_master(काष्ठा sdw_bus *bus,
		काष्ठा sdw_stream_runसमय *stream);
पूर्णांक sdw_stream_हटाओ_slave(काष्ठा sdw_slave *slave,
		काष्ठा sdw_stream_runसमय *stream);
पूर्णांक sdw_startup_stream(व्योम *sdw_substream);
पूर्णांक sdw_prepare_stream(काष्ठा sdw_stream_runसमय *stream);
पूर्णांक sdw_enable_stream(काष्ठा sdw_stream_runसमय *stream);
पूर्णांक sdw_disable_stream(काष्ठा sdw_stream_runसमय *stream);
पूर्णांक sdw_deprepare_stream(काष्ठा sdw_stream_runसमय *stream);
व्योम sdw_shutकरोwn_stream(व्योम *sdw_substream);
पूर्णांक sdw_bus_prep_clk_stop(काष्ठा sdw_bus *bus);
पूर्णांक sdw_bus_clk_stop(काष्ठा sdw_bus *bus);
पूर्णांक sdw_bus_निकास_clk_stop(काष्ठा sdw_bus *bus);

/* messaging and data APIs */

पूर्णांक sdw_पढ़ो(काष्ठा sdw_slave *slave, u32 addr);
पूर्णांक sdw_ग_लिखो(काष्ठा sdw_slave *slave, u32 addr, u8 value);
पूर्णांक sdw_ग_लिखो_no_pm(काष्ठा sdw_slave *slave, u32 addr, u8 value);
पूर्णांक sdw_पढ़ो_no_pm(काष्ठा sdw_slave *slave, u32 addr);
पूर्णांक sdw_nपढ़ो(काष्ठा sdw_slave *slave, u32 addr, माप_प्रकार count, u8 *val);
पूर्णांक sdw_nग_लिखो(काष्ठा sdw_slave *slave, u32 addr, माप_प्रकार count, u8 *val);
पूर्णांक sdw_compare_devid(काष्ठा sdw_slave *slave, काष्ठा sdw_slave_id id);
व्योम sdw_extract_slave_id(काष्ठा sdw_bus *bus, u64 addr, काष्ठा sdw_slave_id *id);

#पूर्ण_अगर /* __SOUNDWIRE_H */
