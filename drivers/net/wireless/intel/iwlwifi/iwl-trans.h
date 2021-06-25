<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2005-2014, 2018-2021 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_trans_h__
#घोषणा __iwl_trans_h__

#समावेश <linux/ieee80211.h>
#समावेश <linux/mm.h> /* क्रम page_address */
#समावेश <linux/lockdep.h>
#समावेश <linux/kernel.h>

#समावेश "iwl-debug.h"
#समावेश "iwl-config.h"
#समावेश "fw/img.h"
#समावेश "iwl-op-mode.h"
#समावेश <linux/firmware.h>
#समावेश "fw/api/cmdhdr.h"
#समावेश "fw/api/txq.h"
#समावेश "fw/api/dbg-tlv.h"
#समावेश "iwl-dbg-tlv.h"

/**
 * DOC: Transport layer - what is it ?
 *
 * The transport layer is the layer that deals with the HW directly. It provides
 * an असलtraction of the underlying HW to the upper layer. The transport layer
 * करोesn't provide any policy, algorithm or anything of this kind, but only
 * mechanisms to make the HW करो something. It is not completely stateless but
 * बंद to it.
 * We will have an implementation क्रम each dअगरferent supported bus.
 */

/**
 * DOC: Lअगरe cycle of the transport layer
 *
 * The transport layer has a very precise lअगरe cycle.
 *
 *	1) A helper function is called during the module initialization and
 *	   रेजिस्टरs the bus driver's ops with the transport's alloc function.
 *	2) Bus's probe calls to the transport layer's allocation functions.
 *	   Of course this function is bus specअगरic.
 *	3) This allocation functions will spawn the upper layer which will
 *	   रेजिस्टर mac80211.
 *
 *	4) At some poपूर्णांक (i.e. mac80211's start call), the op_mode will call
 *	   the following sequence:
 *	   start_hw
 *	   start_fw
 *
 *	5) Then when finished (or reset):
 *	   stop_device
 *
 *	6) Eventually, the मुक्त function will be called.
 */

#घोषणा IWL_TRANS_FW_DBG_DOMAIN(trans)	IWL_FW_INI_DOMAIN_ALWAYS_ON

#घोषणा FH_RSCSR_FRAME_SIZE_MSK		0x00003FFF	/* bits 0-13 */
#घोषणा FH_RSCSR_FRAME_INVALID		0x55550000
#घोषणा FH_RSCSR_FRAME_ALIGN		0x40
#घोषणा FH_RSCSR_RPA_EN			BIT(25)
#घोषणा FH_RSCSR_RADA_EN		BIT(26)
#घोषणा FH_RSCSR_RXQ_POS		16
#घोषणा FH_RSCSR_RXQ_MASK		0x3F0000

काष्ठा iwl_rx_packet अणु
	/*
	 * The first 4 bytes of the RX frame header contain both the RX frame
	 * size and some flags.
	 * Bit fields:
	 * 31:    flag flush RB request
	 * 30:    flag ignore TC (terminal counter) request
	 * 29:    flag fast IRQ request
	 * 28-27: Reserved
	 * 26:    RADA enabled
	 * 25:    Offload enabled
	 * 24:    RPF enabled
	 * 23:    RSS enabled
	 * 22:    Checksum enabled
	 * 21-16: RX queue
	 * 15-14: Reserved
	 * 13-00: RX frame size
	 */
	__le32 len_n_flags;
	काष्ठा iwl_cmd_header hdr;
	u8 data[];
पूर्ण __packed;

अटल अंतरभूत u32 iwl_rx_packet_len(स्थिर काष्ठा iwl_rx_packet *pkt)
अणु
	वापस le32_to_cpu(pkt->len_n_flags) & FH_RSCSR_FRAME_SIZE_MSK;
पूर्ण

अटल अंतरभूत u32 iwl_rx_packet_payload_len(स्थिर काष्ठा iwl_rx_packet *pkt)
अणु
	वापस iwl_rx_packet_len(pkt) - माप(pkt->hdr);
पूर्ण

/**
 * क्रमागत CMD_MODE - how to send the host commands ?
 *
 * @CMD_ASYNC: Return right away and करोn't रुको क्रम the response
 * @CMD_WANT_SKB: Not valid with CMD_ASYNC. The caller needs the buffer of
 *	the response. The caller needs to call iwl_मुक्त_resp when करोne.
 * @CMD_WANT_ASYNC_CALLBACK: the op_mode's async callback function must be
 *	called after this command completes. Valid only with CMD_ASYNC.
 * @CMD_SEND_IN_D3: Allow the command to be sent in D3 mode, relevant to
 *	SUSPEND and RESUME commands. We are in D3 mode when we set
 *	trans->प्रणाली_pm_mode to IWL_PLAT_PM_MODE_D3.
 */
क्रमागत CMD_MODE अणु
	CMD_ASYNC		= BIT(0),
	CMD_WANT_SKB		= BIT(1),
	CMD_SEND_IN_RFKILL	= BIT(2),
	CMD_WANT_ASYNC_CALLBACK	= BIT(3),
	CMD_SEND_IN_D3          = BIT(4),
पूर्ण;

#घोषणा DEF_CMD_PAYLOAD_SIZE 320

/**
 * काष्ठा iwl_device_cmd
 *
 * For allocation of the command and tx queues, this establishes the overall
 * size of the largest command we send to uCode, except क्रम commands that
 * aren't fully copied and use other TFD space.
 */
काष्ठा iwl_device_cmd अणु
	जोड़ अणु
		काष्ठा अणु
			काष्ठा iwl_cmd_header hdr;	/* uCode API */
			u8 payload[DEF_CMD_PAYLOAD_SIZE];
		पूर्ण;
		काष्ठा अणु
			काष्ठा iwl_cmd_header_wide hdr_wide;
			u8 payload_wide[DEF_CMD_PAYLOAD_SIZE -
					माप(काष्ठा iwl_cmd_header_wide) +
					माप(काष्ठा iwl_cmd_header)];
		पूर्ण;
	पूर्ण;
पूर्ण __packed;

/**
 * काष्ठा iwl_device_tx_cmd - buffer क्रम TX command
 * @hdr: the header
 * @payload: the payload placeholder
 *
 * The actual काष्ठाure is sized dynamically according to need.
 */
काष्ठा iwl_device_tx_cmd अणु
	काष्ठा iwl_cmd_header hdr;
	u8 payload[];
पूर्ण __packed;

#घोषणा TFD_MAX_PAYLOAD_SIZE (माप(काष्ठा iwl_device_cmd))

/*
 * number of transfer buffers (fragments) per transmit frame descriptor;
 * this is just the driver's idea, the hardware supports 20
 */
#घोषणा IWL_MAX_CMD_TBS_PER_TFD	2

/* We need 2 entries क्रम the TX command and header, and another one might
 * be needed क्रम potential data in the SKB's head. The reमुख्यing ones can
 * be used क्रम frags.
 */
#घोषणा IWL_TRANS_MAX_FRAGS(trans) ((trans)->txqs.tfd.max_tbs - 3)

/**
 * क्रमागत iwl_hcmd_dataflag - flag क्रम each one of the chunks of the command
 *
 * @IWL_HCMD_DFL_NOCOPY: By शेष, the command is copied to the host command's
 *	ring. The transport layer करोesn't map the command's buffer to DMA, but
 *	rather copies it to a previously allocated DMA buffer. This flag tells
 *	the transport layer not to copy the command, but to map the existing
 *	buffer (that is passed in) instead. This saves the स_नकल and allows
 *	commands that are bigger than the fixed buffer to be submitted.
 *	Note that a TFD entry after a NOCOPY one cannot be a normal copied one.
 * @IWL_HCMD_DFL_DUP: Only valid without NOCOPY, duplicate the memory क्रम this
 *	chunk पूर्णांकernally and मुक्त it again after the command completes. This
 *	can (currently) be used only once per command.
 *	Note that a TFD entry after a DUP one cannot be a normal copied one.
 */
क्रमागत iwl_hcmd_dataflag अणु
	IWL_HCMD_DFL_NOCOPY	= BIT(0),
	IWL_HCMD_DFL_DUP	= BIT(1),
पूर्ण;

क्रमागत iwl_error_event_table_status अणु
	IWL_ERROR_EVENT_TABLE_LMAC1 = BIT(0),
	IWL_ERROR_EVENT_TABLE_LMAC2 = BIT(1),
	IWL_ERROR_EVENT_TABLE_UMAC = BIT(2),
पूर्ण;

/**
 * काष्ठा iwl_host_cmd - Host command to the uCode
 *
 * @data: array of chunks that composes the data of the host command
 * @resp_pkt: response packet, अगर %CMD_WANT_SKB was set
 * @_rx_page_order: (पूर्णांकernally used to मुक्त response packet)
 * @_rx_page_addr: (पूर्णांकernally used to मुक्त response packet)
 * @flags: can be CMD_*
 * @len: array of the lengths of the chunks in data
 * @dataflags: IWL_HCMD_DFL_*
 * @id: command id of the host command, क्रम wide commands encoding the
 *	version and group as well
 */
काष्ठा iwl_host_cmd अणु
	स्थिर व्योम *data[IWL_MAX_CMD_TBS_PER_TFD];
	काष्ठा iwl_rx_packet *resp_pkt;
	अचिन्हित दीर्घ _rx_page_addr;
	u32 _rx_page_order;

	u32 flags;
	u32 id;
	u16 len[IWL_MAX_CMD_TBS_PER_TFD];
	u8 dataflags[IWL_MAX_CMD_TBS_PER_TFD];
पूर्ण;

अटल अंतरभूत व्योम iwl_मुक्त_resp(काष्ठा iwl_host_cmd *cmd)
अणु
	मुक्त_pages(cmd->_rx_page_addr, cmd->_rx_page_order);
पूर्ण

काष्ठा iwl_rx_cmd_buffer अणु
	काष्ठा page *_page;
	पूर्णांक _offset;
	bool _page_stolen;
	u32 _rx_page_order;
	अचिन्हित पूर्णांक truesize;
पूर्ण;

अटल अंतरभूत व्योम *rxb_addr(काष्ठा iwl_rx_cmd_buffer *r)
अणु
	वापस (व्योम *)((अचिन्हित दीर्घ)page_address(r->_page) + r->_offset);
पूर्ण

अटल अंतरभूत पूर्णांक rxb_offset(काष्ठा iwl_rx_cmd_buffer *r)
अणु
	वापस r->_offset;
पूर्ण

अटल अंतरभूत काष्ठा page *rxb_steal_page(काष्ठा iwl_rx_cmd_buffer *r)
अणु
	r->_page_stolen = true;
	get_page(r->_page);
	वापस r->_page;
पूर्ण

अटल अंतरभूत व्योम iwl_मुक्त_rxb(काष्ठा iwl_rx_cmd_buffer *r)
अणु
	__मुक्त_pages(r->_page, r->_rx_page_order);
पूर्ण

#घोषणा MAX_NO_RECLAIM_CMDS	6

#घोषणा IWL_MASK(lo, hi) ((1 << (hi)) | ((1 << (hi)) - (1 << (lo))))

/*
 * Maximum number of HW queues the transport layer
 * currently supports
 */
#घोषणा IWL_MAX_HW_QUEUES		32
#घोषणा IWL_MAX_TVQM_QUEUES		512

#घोषणा IWL_MAX_TID_COUNT	8
#घोषणा IWL_MGMT_TID		15
#घोषणा IWL_FRAME_LIMIT	64
#घोषणा IWL_MAX_RX_HW_QUEUES	16
#घोषणा IWL_9000_MAX_RX_HW_QUEUES	6

/**
 * क्रमागत iwl_wowlan_status - WoWLAN image/device status
 * @IWL_D3_STATUS_ALIVE: firmware is still running after resume
 * @IWL_D3_STATUS_RESET: device was reset जबतक suspended
 */
क्रमागत iwl_d3_status अणु
	IWL_D3_STATUS_ALIVE,
	IWL_D3_STATUS_RESET,
पूर्ण;

/**
 * क्रमागत iwl_trans_status: transport status flags
 * @STATUS_SYNC_HCMD_ACTIVE: a SYNC command is being processed
 * @STATUS_DEVICE_ENABLED: APM is enabled
 * @STATUS_TPOWER_PMI: the device might be asleep (need to wake it up)
 * @STATUS_INT_ENABLED: पूर्णांकerrupts are enabled
 * @STATUS_RFKILL_HW: the actual HW state of the RF-समाप्त चयन
 * @STATUS_RFKILL_OPMODE: RF-समाप्त state reported to opmode
 * @STATUS_FW_ERROR: the fw is in error state
 * @STATUS_TRANS_GOING_IDLE: shutting करोwn the trans, only special commands
 *	are sent
 * @STATUS_TRANS_IDLE: the trans is idle - general commands are not to be sent
 * @STATUS_TRANS_DEAD: trans is dead - aव्योम any पढ़ो/ग_लिखो operation
 */
क्रमागत iwl_trans_status अणु
	STATUS_SYNC_HCMD_ACTIVE,
	STATUS_DEVICE_ENABLED,
	STATUS_TPOWER_PMI,
	STATUS_INT_ENABLED,
	STATUS_RFKILL_HW,
	STATUS_RFKILL_OPMODE,
	STATUS_FW_ERROR,
	STATUS_TRANS_GOING_IDLE,
	STATUS_TRANS_IDLE,
	STATUS_TRANS_DEAD,
पूर्ण;

अटल अंतरभूत पूर्णांक
iwl_trans_get_rb_size_order(क्रमागत iwl_amsdu_size rb_size)
अणु
	चयन (rb_size) अणु
	हाल IWL_AMSDU_2K:
		वापस get_order(2 * 1024);
	हाल IWL_AMSDU_4K:
		वापस get_order(4 * 1024);
	हाल IWL_AMSDU_8K:
		वापस get_order(8 * 1024);
	हाल IWL_AMSDU_12K:
		वापस get_order(16 * 1024);
	शेष:
		WARN_ON(1);
		वापस -1;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
iwl_trans_get_rb_size(क्रमागत iwl_amsdu_size rb_size)
अणु
	चयन (rb_size) अणु
	हाल IWL_AMSDU_2K:
		वापस 2 * 1024;
	हाल IWL_AMSDU_4K:
		वापस 4 * 1024;
	हाल IWL_AMSDU_8K:
		वापस 8 * 1024;
	हाल IWL_AMSDU_12K:
		वापस 16 * 1024;
	शेष:
		WARN_ON(1);
		वापस 0;
	पूर्ण
पूर्ण

काष्ठा iwl_hcmd_names अणु
	u8 cmd_id;
	स्थिर अक्षर *स्थिर cmd_name;
पूर्ण;

#घोषणा HCMD_NAME(x)	\
	अणु .cmd_id = x, .cmd_name = #x पूर्ण

काष्ठा iwl_hcmd_arr अणु
	स्थिर काष्ठा iwl_hcmd_names *arr;
	पूर्णांक size;
पूर्ण;

#घोषणा HCMD_ARR(x)	\
	अणु .arr = x, .size = ARRAY_SIZE(x) पूर्ण

/**
 * काष्ठा iwl_trans_config - transport configuration
 *
 * @op_mode: poपूर्णांकer to the upper layer.
 * @cmd_queue: the index of the command queue.
 *	Must be set beक्रमe start_fw.
 * @cmd_fअगरo: the fअगरo क्रम host commands
 * @cmd_q_wdg_समयout: the समयout of the watchकरोg समयr क्रम the command queue.
 * @no_reclaim_cmds: Some devices erroneously करोn't set the
 *	SEQ_RX_FRAME bit on some notअगरications, this is the
 *	list of such notअगरications to filter. Max length is
 *	%MAX_NO_RECLAIM_CMDS.
 * @n_no_reclaim_cmds: # of commands in list
 * @rx_buf_size: RX buffer size needed क्रम A-MSDUs
 *	अगर unset 4k will be the RX buffer size
 * @bc_table_dword: set to true अगर the BC table expects the byte count to be
 *	in DWORD (as opposed to bytes)
 * @scd_set_active: should the transport configure the SCD क्रम HCMD queue
 * @command_groups: array of command groups, each member is an array of the
 *	commands in the group; क्रम debugging only
 * @command_groups_size: number of command groups, to aव्योम illegal access
 * @cb_data_offs: offset inside skb->cb to store transport data at, must have
 *	space क्रम at least two poपूर्णांकers
 * @fw_reset_handshake: firmware supports reset flow handshake
 */
काष्ठा iwl_trans_config अणु
	काष्ठा iwl_op_mode *op_mode;

	u8 cmd_queue;
	u8 cmd_fअगरo;
	अचिन्हित पूर्णांक cmd_q_wdg_समयout;
	स्थिर u8 *no_reclaim_cmds;
	अचिन्हित पूर्णांक n_no_reclaim_cmds;

	क्रमागत iwl_amsdu_size rx_buf_size;
	bool bc_table_dword;
	bool scd_set_active;
	स्थिर काष्ठा iwl_hcmd_arr *command_groups;
	पूर्णांक command_groups_size;

	u8 cb_data_offs;
	bool fw_reset_handshake;
पूर्ण;

काष्ठा iwl_trans_dump_data अणु
	u32 len;
	u8 data[];
पूर्ण;

काष्ठा iwl_trans;

काष्ठा iwl_trans_txq_scd_cfg अणु
	u8 fअगरo;
	u8 sta_id;
	u8 tid;
	bool aggregate;
	पूर्णांक frame_limit;
पूर्ण;

/**
 * काष्ठा iwl_trans_rxq_dma_data - RX queue DMA data
 * @fr_bd_cb: DMA address of मुक्त BD cyclic buffer
 * @fr_bd_wid: Initial ग_लिखो index of the मुक्त BD cyclic buffer
 * @urbd_stts_wrptr: DMA address of urbd_stts_wrptr
 * @ur_bd_cb: DMA address of used BD cyclic buffer
 */
काष्ठा iwl_trans_rxq_dma_data अणु
	u64 fr_bd_cb;
	u32 fr_bd_wid;
	u64 urbd_stts_wrptr;
	u64 ur_bd_cb;
पूर्ण;

/**
 * काष्ठा iwl_trans_ops - transport specअगरic operations
 *
 * All the handlers MUST be implemented
 *
 * @start_hw: starts the HW. From that poपूर्णांक on, the HW can send पूर्णांकerrupts.
 *	May sleep.
 * @op_mode_leave: Turn off the HW RF समाप्त indication अगर on
 *	May sleep
 * @start_fw: allocates and inits all the resources क्रम the transport
 *	layer. Also kick a fw image.
 *	May sleep
 * @fw_alive: called when the fw sends alive notअगरication. If the fw provides
 *	the SCD base address in SRAM, then provide it here, or 0 otherwise.
 *	May sleep
 * @stop_device: stops the whole device (embedded CPU put to reset) and stops
 *	the HW. From that poपूर्णांक on, the HW will be stopped but will still issue
 *	an पूर्णांकerrupt अगर the HW RF समाप्त चयन is triggered.
 *	This callback must करो the right thing and not crash even अगर %start_hw()
 *	was called but not &start_fw(). May sleep.
 * @d3_suspend: put the device पूर्णांकo the correct mode क्रम WoWLAN during
 *	suspend. This is optional, अगर not implemented WoWLAN will not be
 *	supported. This callback may sleep.
 * @d3_resume: resume the device after WoWLAN, enabling the opmode to
 *	talk to the WoWLAN image to get its status. This is optional, अगर not
 *	implemented WoWLAN will not be supported. This callback may sleep.
 * @send_cmd:send a host command. Must वापस -ERFKILL अगर RFसमाप्त is निश्चितed.
 *	If RFसमाप्त is निश्चितed in the middle of a SYNC host command, it must
 *	वापस -ERFKILL straight away.
 *	May sleep only अगर CMD_ASYNC is not set
 * @tx: send an skb. The transport relies on the op_mode to zero the
 *	the ieee80211_tx_info->driver_data. If the MPDU is an A-MSDU, all
 *	the CSUM will be taken care of (TCP CSUM and IP header in हाल of
 *	IPv4). If the MPDU is a single MSDU, the op_mode must compute the IP
 *	header अगर it is IPv4.
 *	Must be atomic
 * @reclaim: मुक्त packet until ssn. Returns a list of मुक्तd packets.
 *	Must be atomic
 * @txq_enable: setup a queue. To setup an AC queue, use the
 *	iwl_trans_ac_txq_enable wrapper. fw_alive must have been called beक्रमe
 *	this one. The op_mode must not configure the HCMD queue. The scheduler
 *	configuration may be %शून्य, in which हाल the hardware will not be
 *	configured. If true is वापसed, the operation mode needs to increment
 *	the sequence number of the packets routed to this queue because of a
 *	hardware scheduler bug. May sleep.
 * @txq_disable: de-configure a Tx queue to send AMPDUs
 *	Must be atomic
 * @txq_set_shared_mode: change Tx queue shared/unshared marking
 * @रुको_tx_queues_empty: रुको until tx queues are empty. May sleep.
 * @रुको_txq_empty: रुको until specअगरic tx queue is empty. May sleep.
 * @मुक्तze_txq_समयr: prevents the समयr of the queue from firing until the
 *	queue is set to awake. Must be atomic.
 * @block_txq_ptrs: stop updating the ग_लिखो poपूर्णांकers of the Tx queues. Note
 *	that the transport needs to refcount the calls since this function
 *	will be called several बार with block = true, and then the queues
 *	need to be unblocked only after the same number of calls with
 *	block = false.
 * @ग_लिखो8: ग_लिखो a u8 to a रेजिस्टर at offset ofs from the BAR
 * @ग_लिखो32: ग_लिखो a u32 to a रेजिस्टर at offset ofs from the BAR
 * @पढ़ो32: पढ़ो a u32 रेजिस्टर at offset ofs from the BAR
 * @पढ़ो_prph: पढ़ो a DWORD from a periphery रेजिस्टर
 * @ग_लिखो_prph: ग_लिखो a DWORD to a periphery रेजिस्टर
 * @पढ़ो_mem: पढ़ो device's SRAM in DWORD
 * @ग_लिखो_mem: ग_लिखो device's SRAM in DWORD. If %buf is %शून्य, then the memory
 *	will be zeroed.
 * @पढ़ो_config32: पढ़ो a u32 value from the device's config space at
 *	the given offset.
 * @configure: configure parameters required by the transport layer from
 *	the op_mode. May be called several बार beक्रमe start_fw, can't be
 *	called after that.
 * @set_pmi: set the घातer pmi state
 * @grab_nic_access: wake the NIC to be able to access non-HBUS regs.
 *	Sleeping is not allowed between grab_nic_access and
 *	release_nic_access.
 * @release_nic_access: let the NIC go to sleep. The "flags" parameter
 *	must be the same one that was sent beक्रमe to the grab_nic_access.
 * @set_bits_mask - set SRAM रेजिस्टर according to value and mask.
 * @dump_data: वापस a vदो_स्मृति'ed buffer with debug data, maybe containing last
 *	TX'ed commands and similar. The buffer will be vfree'd by the caller.
 *	Note that the transport must fill in the proper file headers.
 * @debugfs_cleanup: used in the driver unload flow to make a proper cleanup
 *	of the trans debugfs
 * @set_pnvm: set the pnvm data in the prph scratch buffer, inside the
 *	context info.
 * @पूर्णांकerrupts: disable/enable पूर्णांकerrupts to transport
 */
काष्ठा iwl_trans_ops अणु

	पूर्णांक (*start_hw)(काष्ठा iwl_trans *iwl_trans);
	व्योम (*op_mode_leave)(काष्ठा iwl_trans *iwl_trans);
	पूर्णांक (*start_fw)(काष्ठा iwl_trans *trans, स्थिर काष्ठा fw_img *fw,
			bool run_in_rfसमाप्त);
	व्योम (*fw_alive)(काष्ठा iwl_trans *trans, u32 scd_addr);
	व्योम (*stop_device)(काष्ठा iwl_trans *trans);

	पूर्णांक (*d3_suspend)(काष्ठा iwl_trans *trans, bool test, bool reset);
	पूर्णांक (*d3_resume)(काष्ठा iwl_trans *trans, क्रमागत iwl_d3_status *status,
			 bool test, bool reset);

	पूर्णांक (*send_cmd)(काष्ठा iwl_trans *trans, काष्ठा iwl_host_cmd *cmd);

	पूर्णांक (*tx)(काष्ठा iwl_trans *trans, काष्ठा sk_buff *skb,
		  काष्ठा iwl_device_tx_cmd *dev_cmd, पूर्णांक queue);
	व्योम (*reclaim)(काष्ठा iwl_trans *trans, पूर्णांक queue, पूर्णांक ssn,
			काष्ठा sk_buff_head *skbs);

	व्योम (*set_q_ptrs)(काष्ठा iwl_trans *trans, पूर्णांक queue, पूर्णांक ptr);

	bool (*txq_enable)(काष्ठा iwl_trans *trans, पूर्णांक queue, u16 ssn,
			   स्थिर काष्ठा iwl_trans_txq_scd_cfg *cfg,
			   अचिन्हित पूर्णांक queue_wdg_समयout);
	व्योम (*txq_disable)(काष्ठा iwl_trans *trans, पूर्णांक queue,
			    bool configure_scd);
	/* 22000 functions */
	पूर्णांक (*txq_alloc)(काष्ठा iwl_trans *trans,
			 __le16 flags, u8 sta_id, u8 tid,
			 पूर्णांक cmd_id, पूर्णांक size,
			 अचिन्हित पूर्णांक queue_wdg_समयout);
	व्योम (*txq_मुक्त)(काष्ठा iwl_trans *trans, पूर्णांक queue);
	पूर्णांक (*rxq_dma_data)(काष्ठा iwl_trans *trans, पूर्णांक queue,
			    काष्ठा iwl_trans_rxq_dma_data *data);

	व्योम (*txq_set_shared_mode)(काष्ठा iwl_trans *trans, u32 txq_id,
				    bool shared);

	पूर्णांक (*रुको_tx_queues_empty)(काष्ठा iwl_trans *trans, u32 txq_bm);
	पूर्णांक (*रुको_txq_empty)(काष्ठा iwl_trans *trans, पूर्णांक queue);
	व्योम (*मुक्तze_txq_समयr)(काष्ठा iwl_trans *trans, अचिन्हित दीर्घ txqs,
				 bool मुक्तze);
	व्योम (*block_txq_ptrs)(काष्ठा iwl_trans *trans, bool block);

	व्योम (*ग_लिखो8)(काष्ठा iwl_trans *trans, u32 ofs, u8 val);
	व्योम (*ग_लिखो32)(काष्ठा iwl_trans *trans, u32 ofs, u32 val);
	u32 (*पढ़ो32)(काष्ठा iwl_trans *trans, u32 ofs);
	u32 (*पढ़ो_prph)(काष्ठा iwl_trans *trans, u32 ofs);
	व्योम (*ग_लिखो_prph)(काष्ठा iwl_trans *trans, u32 ofs, u32 val);
	पूर्णांक (*पढ़ो_mem)(काष्ठा iwl_trans *trans, u32 addr,
			व्योम *buf, पूर्णांक dwords);
	पूर्णांक (*ग_लिखो_mem)(काष्ठा iwl_trans *trans, u32 addr,
			 स्थिर व्योम *buf, पूर्णांक dwords);
	पूर्णांक (*पढ़ो_config32)(काष्ठा iwl_trans *trans, u32 ofs, u32 *val);
	व्योम (*configure)(काष्ठा iwl_trans *trans,
			  स्थिर काष्ठा iwl_trans_config *trans_cfg);
	व्योम (*set_pmi)(काष्ठा iwl_trans *trans, bool state);
	व्योम (*sw_reset)(काष्ठा iwl_trans *trans);
	bool (*grab_nic_access)(काष्ठा iwl_trans *trans);
	व्योम (*release_nic_access)(काष्ठा iwl_trans *trans);
	व्योम (*set_bits_mask)(काष्ठा iwl_trans *trans, u32 reg, u32 mask,
			      u32 value);

	काष्ठा iwl_trans_dump_data *(*dump_data)(काष्ठा iwl_trans *trans,
						 u32 dump_mask);
	व्योम (*debugfs_cleanup)(काष्ठा iwl_trans *trans);
	व्योम (*sync_nmi)(काष्ठा iwl_trans *trans);
	पूर्णांक (*set_pnvm)(काष्ठा iwl_trans *trans, स्थिर व्योम *data, u32 len);
	व्योम (*पूर्णांकerrupts)(काष्ठा iwl_trans *trans, bool enable);
पूर्ण;

/**
 * क्रमागत iwl_trans_state - state of the transport layer
 *
 * @IWL_TRANS_NO_FW: firmware wasn't started yet, or crashed
 * @IWL_TRANS_FW_STARTED: FW was started, but not alive yet
 * @IWL_TRANS_FW_ALIVE: FW has sent an alive response
 */
क्रमागत iwl_trans_state अणु
	IWL_TRANS_NO_FW,
	IWL_TRANS_FW_STARTED,
	IWL_TRANS_FW_ALIVE,
पूर्ण;

/**
 * DOC: Platक्रमm घातer management
 *
 * In प्रणाली-wide घातer management the entire platक्रमm goes पूर्णांकo a low
 * घातer state (e.g. idle or suspend to RAM) at the same समय and the
 * device is configured as a wakeup source क्रम the entire platक्रमm.
 * This is usually triggered by userspace activity (e.g. the user
 * presses the suspend button or a घातer management daemon decides to
 * put the platक्रमm in low घातer mode).  The device's behavior in this
 * mode is dictated by the wake-on-WLAN configuration.
 *
 * The terms used क्रम the device's behavior are as follows:
 *
 *	- D0: the device is fully घातered and the host is awake;
 *	- D3: the device is in low घातer mode and only reacts to
 *		specअगरic events (e.g. magic-packet received or scan
 *		results found);
 *
 * These terms reflect the घातer modes in the firmware and are not to
 * be confused with the physical device घातer state.
 */

/**
 * क्रमागत iwl_plat_pm_mode - platक्रमm घातer management mode
 *
 * This क्रमागतeration describes the device's platक्रमm घातer management
 * behavior when in प्रणाली-wide suspend (i.e WoWLAN).
 *
 * @IWL_PLAT_PM_MODE_DISABLED: घातer management is disabled क्रम this
 *	device.  In प्रणाली-wide suspend mode, it means that the all
 *	connections will be बंदd स्वतःmatically by mac80211 beक्रमe
 *	the platक्रमm is suspended.
 * @IWL_PLAT_PM_MODE_D3: the device goes पूर्णांकo D3 mode (i.e. WoWLAN).
 */
क्रमागत iwl_plat_pm_mode अणु
	IWL_PLAT_PM_MODE_DISABLED,
	IWL_PLAT_PM_MODE_D3,
पूर्ण;

/**
 * क्रमागत iwl_ini_cfg_state
 * @IWL_INI_CFG_STATE_NOT_LOADED: no debug cfg was given
 * @IWL_INI_CFG_STATE_LOADED: debug cfg was found and loaded
 * @IWL_INI_CFG_STATE_CORRUPTED: debug cfg was found and some of the TLVs
 *	are corrupted. The rest of the debug TLVs will still be used
 */
क्रमागत iwl_ini_cfg_state अणु
	IWL_INI_CFG_STATE_NOT_LOADED,
	IWL_INI_CFG_STATE_LOADED,
	IWL_INI_CFG_STATE_CORRUPTED,
पूर्ण;

/* Max समय to रुको क्रम nmi पूर्णांकerrupt */
#घोषणा IWL_TRANS_NMI_TIMEOUT (HZ / 4)

/**
 * काष्ठा iwl_dram_data
 * @physical: page phy poपूर्णांकer
 * @block: poपूर्णांकer to the allocated block/page
 * @size: size of the block/page
 */
काष्ठा iwl_dram_data अणु
	dma_addr_t physical;
	व्योम *block;
	पूर्णांक size;
पूर्ण;

/**
 * काष्ठा iwl_fw_mon - fw monitor per allocation id
 * @num_frags: number of fragments
 * @frags: an array of DRAM buffer fragments
 */
काष्ठा iwl_fw_mon अणु
	u32 num_frags;
	काष्ठा iwl_dram_data *frags;
पूर्ण;

/**
 * काष्ठा iwl_self_init_dram - dram data used by self init process
 * @fw: lmac and umac dram data
 * @fw_cnt: total number of items in array
 * @paging: paging dram data
 * @paging_cnt: total number of items in array
 */
काष्ठा iwl_self_init_dram अणु
	काष्ठा iwl_dram_data *fw;
	पूर्णांक fw_cnt;
	काष्ठा iwl_dram_data *paging;
	पूर्णांक paging_cnt;
पूर्ण;

/**
 * काष्ठा iwl_trans_debug - transport debug related data
 *
 * @n_dest_reg: num of reg_ops in %dbg_dest_tlv
 * @rec_on: true अगरf there is a fw debug recording currently active
 * @dest_tlv: poपूर्णांकs to the destination TLV क्रम debug
 * @conf_tlv: array of poपूर्णांकers to configuration TLVs क्रम debug
 * @trigger_tlv: array of poपूर्णांकers to triggers TLVs क्रम debug
 * @lmac_error_event_table: addrs of lmacs error tables
 * @umac_error_event_table: addr of umac error table
 * @error_event_table_tlv_status: biपंचांगap that indicates what error table
 *	poपूर्णांकers was recevied via TLV. uses क्रमागत &iwl_error_event_table_status
 * @पूर्णांकernal_ini_cfg: पूर्णांकernal debug cfg state. Uses &क्रमागत iwl_ini_cfg_state
 * @बाह्यal_ini_cfg: बाह्यal debug cfg state. Uses &क्रमागत iwl_ini_cfg_state
 * @fw_mon_cfg: debug buffer allocation configuration
 * @fw_mon_ini: DRAM buffer fragments per allocation id
 * @fw_mon: DRAM buffer क्रम firmware monitor
 * @hw_error: equals true अगर hw error पूर्णांकerrupt was received from the FW
 * @ini_dest: debug monitor destination uses &क्रमागत iwl_fw_ini_buffer_location
 * @active_regions: active regions
 * @debug_info_tlv_list: list of debug info TLVs
 * @समय_poपूर्णांक: array of debug समय poपूर्णांकs
 * @periodic_trig_list: periodic triggers list
 * @करोमुख्यs_biपंचांगap: biपंचांगap of active करोमुख्यs other than
 *	&IWL_FW_INI_DOMAIN_ALWAYS_ON
 */
काष्ठा iwl_trans_debug अणु
	u8 n_dest_reg;
	bool rec_on;

	स्थिर काष्ठा iwl_fw_dbg_dest_tlv_v1 *dest_tlv;
	स्थिर काष्ठा iwl_fw_dbg_conf_tlv *conf_tlv[FW_DBG_CONF_MAX];
	काष्ठा iwl_fw_dbg_trigger_tlv * स्थिर *trigger_tlv;

	u32 lmac_error_event_table[2];
	u32 umac_error_event_table;
	अचिन्हित पूर्णांक error_event_table_tlv_status;

	क्रमागत iwl_ini_cfg_state पूर्णांकernal_ini_cfg;
	क्रमागत iwl_ini_cfg_state बाह्यal_ini_cfg;

	काष्ठा iwl_fw_ini_allocation_tlv fw_mon_cfg[IWL_FW_INI_ALLOCATION_NUM];
	काष्ठा iwl_fw_mon fw_mon_ini[IWL_FW_INI_ALLOCATION_NUM];

	काष्ठा iwl_dram_data fw_mon;

	bool hw_error;
	क्रमागत iwl_fw_ini_buffer_location ini_dest;

	u64 unsupported_region_msk;
	काष्ठा iwl_ucode_tlv *active_regions[IWL_FW_INI_MAX_REGION_ID];
	काष्ठा list_head debug_info_tlv_list;
	काष्ठा iwl_dbg_tlv_समय_poपूर्णांक_data
		समय_poपूर्णांक[IWL_FW_INI_TIME_POINT_NUM];
	काष्ठा list_head periodic_trig_list;

	u32 करोमुख्यs_biपंचांगap;
पूर्ण;

काष्ठा iwl_dma_ptr अणु
	dma_addr_t dma;
	व्योम *addr;
	माप_प्रकार size;
पूर्ण;

काष्ठा iwl_cmd_meta अणु
	/* only क्रम SYNC commands, अगरf the reply skb is wanted */
	काष्ठा iwl_host_cmd *source;
	u32 flags;
	u32 tbs;
पूर्ण;

/*
 * The FH will ग_लिखो back to the first TB only, so we need to copy some data
 * पूर्णांकo the buffer regardless of whether it should be mapped or not.
 * This indicates how big the first TB must be to include the scratch buffer
 * and the asचिन्हित PN.
 * Since PN location is 8 bytes at offset 12, it's 20 now.
 * If we make it bigger then allocations will be bigger and copy slower, so
 * that's probably not useful.
 */
#घोषणा IWL_FIRST_TB_SIZE	20
#घोषणा IWL_FIRST_TB_SIZE_ALIGN ALIGN(IWL_FIRST_TB_SIZE, 64)

काष्ठा iwl_pcie_txq_entry अणु
	व्योम *cmd;
	काष्ठा sk_buff *skb;
	/* buffer to मुक्त after command completes */
	स्थिर व्योम *मुक्त_buf;
	काष्ठा iwl_cmd_meta meta;
पूर्ण;

काष्ठा iwl_pcie_first_tb_buf अणु
	u8 buf[IWL_FIRST_TB_SIZE_ALIGN];
पूर्ण;

/**
 * काष्ठा iwl_txq - Tx Queue क्रम DMA
 * @q: generic Rx/Tx queue descriptor
 * @tfds: transmit frame descriptors (DMA memory)
 * @first_tb_bufs: start of command headers, including scratch buffers, क्रम
 *	the ग_लिखोback -- this is DMA memory and an array holding one buffer
 *	क्रम each command on the queue
 * @first_tb_dma: DMA address क्रम the first_tb_bufs start
 * @entries: transmit entries (driver state)
 * @lock: queue lock
 * @stuck_समयr: समयr that fires अगर queue माला_लो stuck
 * @trans: poपूर्णांकer back to transport (क्रम समयr)
 * @need_update: indicates need to update पढ़ो/ग_लिखो index
 * @ampdu: true अगर this queue is an ampdu queue क्रम an specअगरic RA/TID
 * @wd_समयout: queue watchकरोg समयout (jअगरfies) - per queue
 * @frozen: tx stuck queue समयr is frozen
 * @frozen_expiry_reमुख्यder: remember how दीर्घ until the समयr fires
 * @bc_tbl: byte count table of the queue (relevant only क्रम gen2 transport)
 * @ग_लिखो_ptr: 1-st empty entry (index) host_w
 * @पढ़ो_ptr: last used entry (index) host_r
 * @dma_addr:  physical addr क्रम BD's
 * @n_winकरोw: safe queue winकरोw
 * @id: queue id
 * @low_mark: low watermark, resume queue अगर मुक्त space more than this
 * @high_mark: high watermark, stop queue अगर मुक्त space less than this
 *
 * A Tx queue consists of circular buffer of BDs (a.k.a. TFDs, transmit frame
 * descriptors) and required locking काष्ठाures.
 *
 * Note the dअगरference between TFD_QUEUE_SIZE_MAX and n_winकरोw: the hardware
 * always assumes 256 descriptors, so TFD_QUEUE_SIZE_MAX is always 256 (unless
 * there might be HW changes in the future). For the normal TX
 * queues, n_winकरोw, which is the size of the software queue data
 * is also 256; however, क्रम the command queue, n_winकरोw is only
 * 32 since we करोn't need so many commands pending. Since the HW
 * still uses 256 BDs क्रम DMA though, TFD_QUEUE_SIZE_MAX stays 256.
 * This means that we end up with the following:
 *  HW entries: | 0 | ... | N * 32 | ... | N * 32 + 31 | ... | 255 |
 *  SW entries:           | 0      | ... | 31          |
 * where N is a number between 0 and 7. This means that the SW
 * data is a winकरोw overlayed over the HW queue.
 */
काष्ठा iwl_txq अणु
	व्योम *tfds;
	काष्ठा iwl_pcie_first_tb_buf *first_tb_bufs;
	dma_addr_t first_tb_dma;
	काष्ठा iwl_pcie_txq_entry *entries;
	/* lock क्रम syncing changes on the queue */
	spinlock_t lock;
	अचिन्हित दीर्घ frozen_expiry_reमुख्यder;
	काष्ठा समयr_list stuck_समयr;
	काष्ठा iwl_trans *trans;
	bool need_update;
	bool frozen;
	bool ampdu;
	पूर्णांक block;
	अचिन्हित दीर्घ wd_समयout;
	काष्ठा sk_buff_head overflow_q;
	काष्ठा iwl_dma_ptr bc_tbl;

	पूर्णांक ग_लिखो_ptr;
	पूर्णांक पढ़ो_ptr;
	dma_addr_t dma_addr;
	पूर्णांक n_winकरोw;
	u32 id;
	पूर्णांक low_mark;
	पूर्णांक high_mark;

	bool overflow_tx;
पूर्ण;

/**
 * काष्ठा iwl_trans_txqs - transport tx queues data
 *
 * @bc_table_dword: true अगर the BC table expects DWORD (as opposed to bytes)
 * @page_offs: offset from skb->cb to mac header page poपूर्णांकer
 * @dev_cmd_offs: offset from skb->cb to iwl_device_tx_cmd poपूर्णांकer
 * @queue_used - bit mask of used queues
 * @queue_stopped - bit mask of stopped queues
 * @scd_bc_tbls: gen1 poपूर्णांकer to the byte count table of the scheduler
 */
काष्ठा iwl_trans_txqs अणु
	अचिन्हित दीर्घ queue_used[BITS_TO_LONGS(IWL_MAX_TVQM_QUEUES)];
	अचिन्हित दीर्घ queue_stopped[BITS_TO_LONGS(IWL_MAX_TVQM_QUEUES)];
	काष्ठा iwl_txq *txq[IWL_MAX_TVQM_QUEUES];
	काष्ठा dma_pool *bc_pool;
	माप_प्रकार bc_tbl_size;
	bool bc_table_dword;
	u8 page_offs;
	u8 dev_cmd_offs;
	काष्ठा __percpu iwl_tso_hdr_page * tso_hdr_page;

	काष्ठा अणु
		u8 fअगरo;
		u8 q_id;
		अचिन्हित पूर्णांक wdg_समयout;
	पूर्ण cmd;

	काष्ठा अणु
		u8 max_tbs;
		u16 size;
		u8 addr_size;
	पूर्ण tfd;

	काष्ठा iwl_dma_ptr scd_bc_tbls;
पूर्ण;

/**
 * काष्ठा iwl_trans - transport common data
 *
 * @ops - poपूर्णांकer to iwl_trans_ops
 * @op_mode - poपूर्णांकer to the op_mode
 * @trans_cfg: the trans-specअगरic configuration part
 * @cfg - poपूर्णांकer to the configuration
 * @drv - poपूर्णांकer to iwl_drv
 * @status: a bit-mask of transport status flags
 * @dev - poपूर्णांकer to काष्ठा device * that represents the device
 * @max_skb_frags: maximum number of fragments an SKB can have when transmitted.
 *	0 indicates that frag SKBs (NETIF_F_SG) aren't supported.
 * @hw_rf_id a u32 with the device RF ID
 * @hw_id: a u32 with the ID of the device / sub-device.
 *	Set during transport allocation.
 * @hw_id_str: a string with info about HW ID. Set during transport allocation.
 * @pm_support: set to true in start_hw अगर link pm is supported
 * @ltr_enabled: set to true अगर the LTR is enabled
 * @wide_cmd_header: true when ucode supports wide command header क्रमmat
 * @रुको_command_queue: रुको queue क्रम sync commands
 * @num_rx_queues: number of RX queues allocated by the transport;
 *	the transport must set this beक्रमe calling iwl_drv_start()
 * @iml_len: the length of the image loader
 * @iml: a poपूर्णांकer to the image loader itself
 * @dev_cmd_pool: pool क्रम Tx cmd allocation - क्रम पूर्णांकernal use only.
 *	The user should use iwl_trans_अणुalloc,मुक्तपूर्ण_tx_cmd.
 * @rx_mpdu_cmd: MPDU RX command ID, must be asचिन्हित by opmode beक्रमe
 *	starting the firmware, used क्रम tracing
 * @rx_mpdu_cmd_hdr_size: used क्रम tracing, amount of data beक्रमe the
 *	start of the 802.11 header in the @rx_mpdu_cmd
 * @dflt_pwr_limit: शेष घातer limit fetched from the platक्रमm (ACPI)
 * @प्रणाली_pm_mode: the प्रणाली-wide घातer management mode in use.
 *	This mode is set dynamically, depending on the WoWLAN values
 *	configured from the userspace at runसमय.
 * @iwl_trans_txqs: transport tx queues data.
 */
काष्ठा iwl_trans अणु
	स्थिर काष्ठा iwl_trans_ops *ops;
	काष्ठा iwl_op_mode *op_mode;
	स्थिर काष्ठा iwl_cfg_trans_params *trans_cfg;
	स्थिर काष्ठा iwl_cfg *cfg;
	काष्ठा iwl_drv *drv;
	क्रमागत iwl_trans_state state;
	अचिन्हित दीर्घ status;

	काष्ठा device *dev;
	u32 max_skb_frags;
	u32 hw_rev;
	u32 hw_rf_id;
	u32 hw_id;
	अक्षर hw_id_str[52];
	u32 sku_id[3];

	u8 rx_mpdu_cmd, rx_mpdu_cmd_hdr_size;

	bool pm_support;
	bool ltr_enabled;
	u8 pnvm_loaded:1;

	स्थिर काष्ठा iwl_hcmd_arr *command_groups;
	पूर्णांक command_groups_size;
	bool wide_cmd_header;

	रुको_queue_head_t रुको_command_queue;
	u8 num_rx_queues;

	माप_प्रकार iml_len;
	u8 *iml;

	/* The following fields are पूर्णांकernal only */
	काष्ठा kmem_cache *dev_cmd_pool;
	अक्षर dev_cmd_pool_name[50];

	काष्ठा dentry *dbgfs_dir;

#अगर_घोषित CONFIG_LOCKDEP
	काष्ठा lockdep_map sync_cmd_lockdep_map;
#पूर्ण_अगर

	काष्ठा iwl_trans_debug dbg;
	काष्ठा iwl_self_init_dram init_dram;

	क्रमागत iwl_plat_pm_mode प्रणाली_pm_mode;

	स्थिर अक्षर *name;
	काष्ठा iwl_trans_txqs txqs;

	/* poपूर्णांकer to trans specअगरic काष्ठा */
	/*Ensure that this poपूर्णांकer will always be aligned to माप poपूर्णांकer */
	अक्षर trans_specअगरic[] __aligned(माप(व्योम *));
पूर्ण;

स्थिर अक्षर *iwl_get_cmd_string(काष्ठा iwl_trans *trans, u32 id);
पूर्णांक iwl_cmd_groups_verअगरy_sorted(स्थिर काष्ठा iwl_trans_config *trans);

अटल अंतरभूत व्योम iwl_trans_configure(काष्ठा iwl_trans *trans,
				       स्थिर काष्ठा iwl_trans_config *trans_cfg)
अणु
	trans->op_mode = trans_cfg->op_mode;

	trans->ops->configure(trans, trans_cfg);
	WARN_ON(iwl_cmd_groups_verअगरy_sorted(trans_cfg));
पूर्ण

अटल अंतरभूत पूर्णांक iwl_trans_start_hw(काष्ठा iwl_trans *trans)
अणु
	might_sleep();

	वापस trans->ops->start_hw(trans);
पूर्ण

अटल अंतरभूत व्योम iwl_trans_op_mode_leave(काष्ठा iwl_trans *trans)
अणु
	might_sleep();

	अगर (trans->ops->op_mode_leave)
		trans->ops->op_mode_leave(trans);

	trans->op_mode = शून्य;

	trans->state = IWL_TRANS_NO_FW;
पूर्ण

अटल अंतरभूत व्योम iwl_trans_fw_alive(काष्ठा iwl_trans *trans, u32 scd_addr)
अणु
	might_sleep();

	trans->state = IWL_TRANS_FW_ALIVE;

	trans->ops->fw_alive(trans, scd_addr);
पूर्ण

अटल अंतरभूत पूर्णांक iwl_trans_start_fw(काष्ठा iwl_trans *trans,
				     स्थिर काष्ठा fw_img *fw,
				     bool run_in_rfसमाप्त)
अणु
	पूर्णांक ret;

	might_sleep();

	WARN_ON_ONCE(!trans->rx_mpdu_cmd);

	clear_bit(STATUS_FW_ERROR, &trans->status);
	ret = trans->ops->start_fw(trans, fw, run_in_rfसमाप्त);
	अगर (ret == 0)
		trans->state = IWL_TRANS_FW_STARTED;

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम iwl_trans_stop_device(काष्ठा iwl_trans *trans)
अणु
	might_sleep();

	trans->ops->stop_device(trans);

	trans->state = IWL_TRANS_NO_FW;
पूर्ण

अटल अंतरभूत पूर्णांक iwl_trans_d3_suspend(काष्ठा iwl_trans *trans, bool test,
				       bool reset)
अणु
	might_sleep();
	अगर (!trans->ops->d3_suspend)
		वापस 0;

	वापस trans->ops->d3_suspend(trans, test, reset);
पूर्ण

अटल अंतरभूत पूर्णांक iwl_trans_d3_resume(काष्ठा iwl_trans *trans,
				      क्रमागत iwl_d3_status *status,
				      bool test, bool reset)
अणु
	might_sleep();
	अगर (!trans->ops->d3_resume)
		वापस 0;

	वापस trans->ops->d3_resume(trans, status, test, reset);
पूर्ण

अटल अंतरभूत काष्ठा iwl_trans_dump_data *
iwl_trans_dump_data(काष्ठा iwl_trans *trans, u32 dump_mask)
अणु
	अगर (!trans->ops->dump_data)
		वापस शून्य;
	वापस trans->ops->dump_data(trans, dump_mask);
पूर्ण

अटल अंतरभूत काष्ठा iwl_device_tx_cmd *
iwl_trans_alloc_tx_cmd(काष्ठा iwl_trans *trans)
अणु
	वापस kmem_cache_zalloc(trans->dev_cmd_pool, GFP_ATOMIC);
पूर्ण

पूर्णांक iwl_trans_send_cmd(काष्ठा iwl_trans *trans, काष्ठा iwl_host_cmd *cmd);

अटल अंतरभूत व्योम iwl_trans_मुक्त_tx_cmd(काष्ठा iwl_trans *trans,
					 काष्ठा iwl_device_tx_cmd *dev_cmd)
अणु
	kmem_cache_मुक्त(trans->dev_cmd_pool, dev_cmd);
पूर्ण

अटल अंतरभूत पूर्णांक iwl_trans_tx(काष्ठा iwl_trans *trans, काष्ठा sk_buff *skb,
			       काष्ठा iwl_device_tx_cmd *dev_cmd, पूर्णांक queue)
अणु
	अगर (unlikely(test_bit(STATUS_FW_ERROR, &trans->status)))
		वापस -EIO;

	अगर (WARN_ON_ONCE(trans->state != IWL_TRANS_FW_ALIVE)) अणु
		IWL_ERR(trans, "%s bad state = %d\n", __func__, trans->state);
		वापस -EIO;
	पूर्ण

	वापस trans->ops->tx(trans, skb, dev_cmd, queue);
पूर्ण

अटल अंतरभूत व्योम iwl_trans_reclaim(काष्ठा iwl_trans *trans, पूर्णांक queue,
				     पूर्णांक ssn, काष्ठा sk_buff_head *skbs)
अणु
	अगर (WARN_ON_ONCE(trans->state != IWL_TRANS_FW_ALIVE)) अणु
		IWL_ERR(trans, "%s bad state = %d\n", __func__, trans->state);
		वापस;
	पूर्ण

	trans->ops->reclaim(trans, queue, ssn, skbs);
पूर्ण

अटल अंतरभूत व्योम iwl_trans_set_q_ptrs(काष्ठा iwl_trans *trans, पूर्णांक queue,
					पूर्णांक ptr)
अणु
	अगर (WARN_ON_ONCE(trans->state != IWL_TRANS_FW_ALIVE)) अणु
		IWL_ERR(trans, "%s bad state = %d\n", __func__, trans->state);
		वापस;
	पूर्ण

	trans->ops->set_q_ptrs(trans, queue, ptr);
पूर्ण

अटल अंतरभूत व्योम iwl_trans_txq_disable(काष्ठा iwl_trans *trans, पूर्णांक queue,
					 bool configure_scd)
अणु
	trans->ops->txq_disable(trans, queue, configure_scd);
पूर्ण

अटल अंतरभूत bool
iwl_trans_txq_enable_cfg(काष्ठा iwl_trans *trans, पूर्णांक queue, u16 ssn,
			 स्थिर काष्ठा iwl_trans_txq_scd_cfg *cfg,
			 अचिन्हित पूर्णांक queue_wdg_समयout)
अणु
	might_sleep();

	अगर (WARN_ON_ONCE(trans->state != IWL_TRANS_FW_ALIVE)) अणु
		IWL_ERR(trans, "%s bad state = %d\n", __func__, trans->state);
		वापस false;
	पूर्ण

	वापस trans->ops->txq_enable(trans, queue, ssn,
				      cfg, queue_wdg_समयout);
पूर्ण

अटल अंतरभूत पूर्णांक
iwl_trans_get_rxq_dma_data(काष्ठा iwl_trans *trans, पूर्णांक queue,
			   काष्ठा iwl_trans_rxq_dma_data *data)
अणु
	अगर (WARN_ON_ONCE(!trans->ops->rxq_dma_data))
		वापस -ENOTSUPP;

	वापस trans->ops->rxq_dma_data(trans, queue, data);
पूर्ण

अटल अंतरभूत व्योम
iwl_trans_txq_मुक्त(काष्ठा iwl_trans *trans, पूर्णांक queue)
अणु
	अगर (WARN_ON_ONCE(!trans->ops->txq_मुक्त))
		वापस;

	trans->ops->txq_मुक्त(trans, queue);
पूर्ण

अटल अंतरभूत पूर्णांक
iwl_trans_txq_alloc(काष्ठा iwl_trans *trans,
		    __le16 flags, u8 sta_id, u8 tid,
		    पूर्णांक cmd_id, पूर्णांक size,
		    अचिन्हित पूर्णांक wdg_समयout)
अणु
	might_sleep();

	अगर (WARN_ON_ONCE(!trans->ops->txq_alloc))
		वापस -ENOTSUPP;

	अगर (WARN_ON_ONCE(trans->state != IWL_TRANS_FW_ALIVE)) अणु
		IWL_ERR(trans, "%s bad state = %d\n", __func__, trans->state);
		वापस -EIO;
	पूर्ण

	वापस trans->ops->txq_alloc(trans, flags, sta_id, tid,
				     cmd_id, size, wdg_समयout);
पूर्ण

अटल अंतरभूत व्योम iwl_trans_txq_set_shared_mode(काष्ठा iwl_trans *trans,
						 पूर्णांक queue, bool shared_mode)
अणु
	अगर (trans->ops->txq_set_shared_mode)
		trans->ops->txq_set_shared_mode(trans, queue, shared_mode);
पूर्ण

अटल अंतरभूत व्योम iwl_trans_txq_enable(काष्ठा iwl_trans *trans, पूर्णांक queue,
					पूर्णांक fअगरo, पूर्णांक sta_id, पूर्णांक tid,
					पूर्णांक frame_limit, u16 ssn,
					अचिन्हित पूर्णांक queue_wdg_समयout)
अणु
	काष्ठा iwl_trans_txq_scd_cfg cfg = अणु
		.fअगरo = fअगरo,
		.sta_id = sta_id,
		.tid = tid,
		.frame_limit = frame_limit,
		.aggregate = sta_id >= 0,
	पूर्ण;

	iwl_trans_txq_enable_cfg(trans, queue, ssn, &cfg, queue_wdg_समयout);
पूर्ण

अटल अंतरभूत
व्योम iwl_trans_ac_txq_enable(काष्ठा iwl_trans *trans, पूर्णांक queue, पूर्णांक fअगरo,
			     अचिन्हित पूर्णांक queue_wdg_समयout)
अणु
	काष्ठा iwl_trans_txq_scd_cfg cfg = अणु
		.fअगरo = fअगरo,
		.sta_id = -1,
		.tid = IWL_MAX_TID_COUNT,
		.frame_limit = IWL_FRAME_LIMIT,
		.aggregate = false,
	पूर्ण;

	iwl_trans_txq_enable_cfg(trans, queue, 0, &cfg, queue_wdg_समयout);
पूर्ण

अटल अंतरभूत व्योम iwl_trans_मुक्तze_txq_समयr(काष्ठा iwl_trans *trans,
					      अचिन्हित दीर्घ txqs,
					      bool मुक्तze)
अणु
	अगर (WARN_ON_ONCE(trans->state != IWL_TRANS_FW_ALIVE)) अणु
		IWL_ERR(trans, "%s bad state = %d\n", __func__, trans->state);
		वापस;
	पूर्ण

	अगर (trans->ops->मुक्तze_txq_समयr)
		trans->ops->मुक्तze_txq_समयr(trans, txqs, मुक्तze);
पूर्ण

अटल अंतरभूत व्योम iwl_trans_block_txq_ptrs(काष्ठा iwl_trans *trans,
					    bool block)
अणु
	अगर (WARN_ON_ONCE(trans->state != IWL_TRANS_FW_ALIVE)) अणु
		IWL_ERR(trans, "%s bad state = %d\n", __func__, trans->state);
		वापस;
	पूर्ण

	अगर (trans->ops->block_txq_ptrs)
		trans->ops->block_txq_ptrs(trans, block);
पूर्ण

अटल अंतरभूत पूर्णांक iwl_trans_रुको_tx_queues_empty(काष्ठा iwl_trans *trans,
						 u32 txqs)
अणु
	अगर (WARN_ON_ONCE(!trans->ops->रुको_tx_queues_empty))
		वापस -ENOTSUPP;

	/* No need to रुको अगर the firmware is not alive */
	अगर (trans->state != IWL_TRANS_FW_ALIVE) अणु
		IWL_ERR(trans, "%s bad state = %d\n", __func__, trans->state);
		वापस -EIO;
	पूर्ण

	वापस trans->ops->रुको_tx_queues_empty(trans, txqs);
पूर्ण

अटल अंतरभूत पूर्णांक iwl_trans_रुको_txq_empty(काष्ठा iwl_trans *trans, पूर्णांक queue)
अणु
	अगर (WARN_ON_ONCE(!trans->ops->रुको_txq_empty))
		वापस -ENOTSUPP;

	अगर (WARN_ON_ONCE(trans->state != IWL_TRANS_FW_ALIVE)) अणु
		IWL_ERR(trans, "%s bad state = %d\n", __func__, trans->state);
		वापस -EIO;
	पूर्ण

	वापस trans->ops->रुको_txq_empty(trans, queue);
पूर्ण

अटल अंतरभूत व्योम iwl_trans_ग_लिखो8(काष्ठा iwl_trans *trans, u32 ofs, u8 val)
अणु
	trans->ops->ग_लिखो8(trans, ofs, val);
पूर्ण

अटल अंतरभूत व्योम iwl_trans_ग_लिखो32(काष्ठा iwl_trans *trans, u32 ofs, u32 val)
अणु
	trans->ops->ग_लिखो32(trans, ofs, val);
पूर्ण

अटल अंतरभूत u32 iwl_trans_पढ़ो32(काष्ठा iwl_trans *trans, u32 ofs)
अणु
	वापस trans->ops->पढ़ो32(trans, ofs);
पूर्ण

अटल अंतरभूत u32 iwl_trans_पढ़ो_prph(काष्ठा iwl_trans *trans, u32 ofs)
अणु
	वापस trans->ops->पढ़ो_prph(trans, ofs);
पूर्ण

अटल अंतरभूत व्योम iwl_trans_ग_लिखो_prph(काष्ठा iwl_trans *trans, u32 ofs,
					u32 val)
अणु
	वापस trans->ops->ग_लिखो_prph(trans, ofs, val);
पूर्ण

अटल अंतरभूत पूर्णांक iwl_trans_पढ़ो_mem(काष्ठा iwl_trans *trans, u32 addr,
				     व्योम *buf, पूर्णांक dwords)
अणु
	वापस trans->ops->पढ़ो_mem(trans, addr, buf, dwords);
पूर्ण

#घोषणा iwl_trans_पढ़ो_mem_bytes(trans, addr, buf, bufsize)		      \
	करो अणु								      \
		अगर (__builtin_स्थिरant_p(bufsize))			      \
			BUILD_BUG_ON((bufsize) % माप(u32));		      \
		iwl_trans_पढ़ो_mem(trans, addr, buf, (bufsize) / माप(u32));\
	पूर्ण जबतक (0)

अटल अंतरभूत u32 iwl_trans_पढ़ो_mem32(काष्ठा iwl_trans *trans, u32 addr)
अणु
	u32 value;

	अगर (WARN_ON(iwl_trans_पढ़ो_mem(trans, addr, &value, 1)))
		वापस 0xa5a5a5a5;

	वापस value;
पूर्ण

अटल अंतरभूत पूर्णांक iwl_trans_ग_लिखो_mem(काष्ठा iwl_trans *trans, u32 addr,
				      स्थिर व्योम *buf, पूर्णांक dwords)
अणु
	वापस trans->ops->ग_लिखो_mem(trans, addr, buf, dwords);
पूर्ण

अटल अंतरभूत u32 iwl_trans_ग_लिखो_mem32(काष्ठा iwl_trans *trans, u32 addr,
					u32 val)
अणु
	वापस iwl_trans_ग_लिखो_mem(trans, addr, &val, 1);
पूर्ण

अटल अंतरभूत व्योम iwl_trans_set_pmi(काष्ठा iwl_trans *trans, bool state)
अणु
	अगर (trans->ops->set_pmi)
		trans->ops->set_pmi(trans, state);
पूर्ण

अटल अंतरभूत व्योम iwl_trans_sw_reset(काष्ठा iwl_trans *trans)
अणु
	अगर (trans->ops->sw_reset)
		trans->ops->sw_reset(trans);
पूर्ण

अटल अंतरभूत व्योम
iwl_trans_set_bits_mask(काष्ठा iwl_trans *trans, u32 reg, u32 mask, u32 value)
अणु
	trans->ops->set_bits_mask(trans, reg, mask, value);
पूर्ण

#घोषणा iwl_trans_grab_nic_access(trans)		\
	__cond_lock(nic_access,				\
		    likely((trans)->ops->grab_nic_access(trans)))

अटल अंतरभूत व्योम __releases(nic_access)
iwl_trans_release_nic_access(काष्ठा iwl_trans *trans)
अणु
	trans->ops->release_nic_access(trans);
	__release(nic_access);
पूर्ण

अटल अंतरभूत व्योम iwl_trans_fw_error(काष्ठा iwl_trans *trans)
अणु
	अगर (WARN_ON_ONCE(!trans->op_mode))
		वापस;

	/* prevent द्विगुन restarts due to the same erroneous FW */
	अगर (!test_and_set_bit(STATUS_FW_ERROR, &trans->status)) अणु
		iwl_op_mode_nic_error(trans->op_mode);
		trans->state = IWL_TRANS_NO_FW;
	पूर्ण
पूर्ण

अटल अंतरभूत bool iwl_trans_fw_running(काष्ठा iwl_trans *trans)
अणु
	वापस trans->state == IWL_TRANS_FW_ALIVE;
पूर्ण

अटल अंतरभूत व्योम iwl_trans_sync_nmi(काष्ठा iwl_trans *trans)
अणु
	अगर (trans->ops->sync_nmi)
		trans->ops->sync_nmi(trans);
पूर्ण

व्योम iwl_trans_sync_nmi_with_addr(काष्ठा iwl_trans *trans, u32 पूर्णांकa_addr,
				  u32 sw_err_bit);

अटल अंतरभूत पूर्णांक iwl_trans_set_pnvm(काष्ठा iwl_trans *trans,
				     स्थिर व्योम *data, u32 len)
अणु
	अगर (trans->ops->set_pnvm) अणु
		पूर्णांक ret = trans->ops->set_pnvm(trans, data, len);

		अगर (ret)
			वापस ret;
	पूर्ण

	trans->pnvm_loaded = true;

	वापस 0;
पूर्ण

अटल अंतरभूत bool iwl_trans_dbg_ini_valid(काष्ठा iwl_trans *trans)
अणु
	वापस trans->dbg.पूर्णांकernal_ini_cfg != IWL_INI_CFG_STATE_NOT_LOADED ||
		trans->dbg.बाह्यal_ini_cfg != IWL_INI_CFG_STATE_NOT_LOADED;
पूर्ण

अटल अंतरभूत व्योम iwl_trans_पूर्णांकerrupts(काष्ठा iwl_trans *trans, bool enable)
अणु
	अगर (trans->ops->पूर्णांकerrupts)
		trans->ops->पूर्णांकerrupts(trans, enable);
पूर्ण

/*****************************************************
 * transport helper functions
 *****************************************************/
काष्ठा iwl_trans *iwl_trans_alloc(अचिन्हित पूर्णांक priv_size,
			  काष्ठा device *dev,
			  स्थिर काष्ठा iwl_trans_ops *ops,
			  स्थिर काष्ठा iwl_cfg_trans_params *cfg_trans);
पूर्णांक iwl_trans_init(काष्ठा iwl_trans *trans);
व्योम iwl_trans_मुक्त(काष्ठा iwl_trans *trans);

/*****************************************************
* driver (transport) रेजिस्टर/unरेजिस्टर functions
******************************************************/
पूर्णांक __must_check iwl_pci_रेजिस्टर_driver(व्योम);
व्योम iwl_pci_unरेजिस्टर_driver(व्योम);

#पूर्ण_अगर /* __iwl_trans_h__ */
