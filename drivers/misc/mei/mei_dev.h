<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2003-2019, Intel Corporation. All rights reserved.
 * Intel Management Engine Interface (Intel MEI) Linux driver
 */

#अगर_अघोषित _MEI_DEV_H_
#घोषणा _MEI_DEV_H_

#समावेश <linux/types.h>
#समावेश <linux/cdev.h>
#समावेश <linux/poll.h>
#समावेश <linux/mei.h>
#समावेश <linux/mei_cl_bus.h>

#समावेश "hw.h"
#समावेश "hbm.h"

#घोषणा MEI_SLOT_SIZE             माप(u32)
#घोषणा MEI_RD_MSG_BUF_SIZE       (128 * MEI_SLOT_SIZE)

/*
 * Number of Maximum MEI Clients
 */
#घोषणा MEI_CLIENTS_MAX 256

/*
 * maximum number of consecutive resets
 */
#घोषणा MEI_MAX_CONSEC_RESET  3

/*
 * Number of File descriptors/handles
 * that can be खोलोed to the driver.
 *
 * Limit to 255: 256 Total Clients
 * minus पूर्णांकernal client क्रम MEI Bus Messages
 */
#घोषणा  MEI_MAX_OPEN_HANDLE_COUNT (MEI_CLIENTS_MAX - 1)

/* File state */
क्रमागत file_state अणु
	MEI_खाता_UNINITIALIZED = 0,
	MEI_खाता_INITIALIZING,
	MEI_खाता_CONNECTING,
	MEI_खाता_CONNECTED,
	MEI_खाता_DISCONNECTING,
	MEI_खाता_DISCONNECT_REPLY,
	MEI_खाता_DISCONNECT_REQUIRED,
	MEI_खाता_DISCONNECTED,
पूर्ण;

/* MEI device states */
क्रमागत mei_dev_state अणु
	MEI_DEV_INITIALIZING = 0,
	MEI_DEV_INIT_CLIENTS,
	MEI_DEV_ENABLED,
	MEI_DEV_RESETTING,
	MEI_DEV_DISABLED,
	MEI_DEV_POWERING_DOWN,
	MEI_DEV_POWER_DOWN,
	MEI_DEV_POWER_UP
पूर्ण;

स्थिर अक्षर *mei_dev_state_str(पूर्णांक state);

क्रमागत mei_file_transaction_states अणु
	MEI_IDLE,
	MEI_WRITING,
	MEI_WRITE_COMPLETE,
पूर्ण;

/**
 * क्रमागत mei_cb_file_ops  - file operation associated with the callback
 * @MEI_FOP_READ:       पढ़ो
 * @MEI_FOP_WRITE:      ग_लिखो
 * @MEI_FOP_CONNECT:    connect
 * @MEI_FOP_DISCONNECT: disconnect
 * @MEI_FOP_DISCONNECT_RSP: disconnect response
 * @MEI_FOP_NOTIFY_START:   start notअगरication
 * @MEI_FOP_NOTIFY_STOP:    stop notअगरication
 * @MEI_FOP_DMA_MAP:   request client dma map
 * @MEI_FOP_DMA_UNMAP: request client dma unmap
 */
क्रमागत mei_cb_file_ops अणु
	MEI_FOP_READ = 0,
	MEI_FOP_WRITE,
	MEI_FOP_CONNECT,
	MEI_FOP_DISCONNECT,
	MEI_FOP_DISCONNECT_RSP,
	MEI_FOP_NOTIFY_START,
	MEI_FOP_NOTIFY_STOP,
	MEI_FOP_DMA_MAP,
	MEI_FOP_DMA_UNMAP,
पूर्ण;

/**
 * क्रमागत mei_cl_io_mode - io mode between driver and fw
 *
 * @MEI_CL_IO_TX_BLOCKING: send is blocking
 * @MEI_CL_IO_TX_INTERNAL: पूर्णांकernal communication between driver and FW
 *
 * @MEI_CL_IO_RX_NONBLOCK: recv is non-blocking
 */
क्रमागत mei_cl_io_mode अणु
	MEI_CL_IO_TX_BLOCKING = BIT(0),
	MEI_CL_IO_TX_INTERNAL = BIT(1),

	MEI_CL_IO_RX_NONBLOCK = BIT(2),
पूर्ण;

/*
 * Intel MEI message data काष्ठा
 */
काष्ठा mei_msg_data अणु
	माप_प्रकार size;
	अचिन्हित अक्षर *data;
पूर्ण;

काष्ठा mei_dma_data अणु
	u8 buffer_id;
	व्योम *vaddr;
	dma_addr_t daddr;
	माप_प्रकार size;
पूर्ण;

/**
 * काष्ठा mei_dma_dscr - dma address descriptor
 *
 * @vaddr: dma buffer भव address
 * @daddr: dma buffer physical address
 * @size : dma buffer size
 */
काष्ठा mei_dma_dscr अणु
	व्योम *vaddr;
	dma_addr_t daddr;
	माप_प्रकार size;
पूर्ण;

/* Maximum number of processed FW status रेजिस्टरs */
#घोषणा MEI_FW_STATUS_MAX 6
/* Minimal  buffer क्रम FW status string (8 bytes in dw + space or '\0') */
#घोषणा MEI_FW_STATUS_STR_SZ (MEI_FW_STATUS_MAX * (8 + 1))


/*
 * काष्ठा mei_fw_status - storage of FW status data
 *
 * @count: number of actually available elements in array
 * @status: FW status रेजिस्टरs
 */
काष्ठा mei_fw_status अणु
	पूर्णांक count;
	u32 status[MEI_FW_STATUS_MAX];
पूर्ण;

/**
 * काष्ठा mei_me_client - representation of me (fw) client
 *
 * @list: link in me client list
 * @refcnt: काष्ठा reference count
 * @props: client properties
 * @client_id: me client id
 * @tx_flow_ctrl_creds: flow control credits
 * @connect_count: number connections to this client
 * @bus_added: added to bus
 */
काष्ठा mei_me_client अणु
	काष्ठा list_head list;
	काष्ठा kref refcnt;
	काष्ठा mei_client_properties props;
	u8 client_id;
	u8 tx_flow_ctrl_creds;
	u8 connect_count;
	u8 bus_added;
पूर्ण;


काष्ठा mei_cl;

/**
 * काष्ठा mei_cl_cb - file operation callback काष्ठाure
 *
 * @list: link in callback queue
 * @cl: file client who is running this operation
 * @fop_type: file operation type
 * @buf: buffer क्रम data associated with the callback
 * @buf_idx: last पढ़ो index
 * @vtag: भव tag
 * @fp: poपूर्णांकer to file काष्ठाure
 * @status: io status of the cb
 * @पूर्णांकernal: communication between driver and FW flag
 * @blocking: transmission blocking mode
 */
काष्ठा mei_cl_cb अणु
	काष्ठा list_head list;
	काष्ठा mei_cl *cl;
	क्रमागत mei_cb_file_ops fop_type;
	काष्ठा mei_msg_data buf;
	माप_प्रकार buf_idx;
	u8 vtag;
	स्थिर काष्ठा file *fp;
	पूर्णांक status;
	u32 पूर्णांकernal:1;
	u32 blocking:1;
पूर्ण;

/**
 * काष्ठा mei_cl_vtag - file poपूर्णांकer to vtag mapping काष्ठाure
 *
 * @list: link in map queue
 * @fp: file poपूर्णांकer
 * @vtag: corresponding vtag
 * @pending_पढ़ो: the पढ़ो is pending on this file
 */
काष्ठा mei_cl_vtag अणु
	काष्ठा list_head list;
	स्थिर काष्ठा file *fp;
	u8 vtag;
	u8 pending_पढ़ो:1;
पूर्ण;

/**
 * काष्ठा mei_cl - me client host representation
 *    carried in file->निजी_data
 *
 * @link: link in the clients list
 * @dev: mei parent device
 * @state: file operation state
 * @tx_रुको: रुको queue क्रम tx completion
 * @rx_रुको: रुको queue क्रम rx completion
 * @रुको:  रुको queue क्रम management operation
 * @ev_रुको: notअगरication रुको queue
 * @ev_async: event async notअगरication
 * @status: connection status
 * @me_cl: fw client connected
 * @fp: file associated with client
 * @host_client_id: host id
 * @vtag_map: vtag map
 * @tx_flow_ctrl_creds: transmit flow credentials
 * @rx_flow_ctrl_creds: receive flow credentials
 * @समयr_count:  watchकरोg समयr क्रम operation completion
 * @notअगरy_en: notअगरication - enabled/disabled
 * @notअगरy_ev: pending notअगरication event
 * @tx_cb_queued: number of tx callbacks in queue
 * @writing_state: state of the tx
 * @rd_pending: pending पढ़ो credits
 * @rd_completed_lock: protects rd_completed queue
 * @rd_completed: completed पढ़ो
 * @dma: dma settings
 * @dma_mapped: dma buffer is currently mapped.
 *
 * @cldev: device on the mei client bus
 */
काष्ठा mei_cl अणु
	काष्ठा list_head link;
	काष्ठा mei_device *dev;
	क्रमागत file_state state;
	रुको_queue_head_t tx_रुको;
	रुको_queue_head_t rx_रुको;
	रुको_queue_head_t रुको;
	रुको_queue_head_t ev_रुको;
	काष्ठा fasync_काष्ठा *ev_async;
	पूर्णांक status;
	काष्ठा mei_me_client *me_cl;
	स्थिर काष्ठा file *fp;
	u8 host_client_id;
	काष्ठा list_head vtag_map;
	u8 tx_flow_ctrl_creds;
	u8 rx_flow_ctrl_creds;
	u8 समयr_count;
	u8 notअगरy_en;
	u8 notअगरy_ev;
	u8 tx_cb_queued;
	क्रमागत mei_file_transaction_states writing_state;
	काष्ठा list_head rd_pending;
	spinlock_t rd_completed_lock; /* protects rd_completed queue */
	काष्ठा list_head rd_completed;
	काष्ठा mei_dma_data dma;
	u8 dma_mapped;

	काष्ठा mei_cl_device *cldev;
पूर्ण;

#घोषणा MEI_TX_QUEUE_LIMIT_DEFAULT 50
#घोषणा MEI_TX_QUEUE_LIMIT_MAX 255
#घोषणा MEI_TX_QUEUE_LIMIT_MIN 30

/**
 * काष्ठा mei_hw_ops - hw specअगरic ops
 *
 * @host_is_पढ़ोy    : query क्रम host पढ़ोiness
 *
 * @hw_is_पढ़ोy      : query अगर hw is पढ़ोy
 * @hw_reset         : reset hw
 * @hw_start         : start hw after reset
 * @hw_config        : configure hw
 *
 * @fw_status        : get fw status रेजिस्टरs
 * @trc_status       : get trc status रेजिस्टर
 * @pg_state         : घातer gating state of the device
 * @pg_in_transition : is device now in pg transition
 * @pg_is_enabled    : is घातer gating enabled
 *
 * @पूर्णांकr_clear       : clear pending पूर्णांकerrupts
 * @पूर्णांकr_enable      : enable पूर्णांकerrupts
 * @पूर्णांकr_disable     : disable पूर्णांकerrupts
 * @synchronize_irq  : synchronize irqs
 *
 * @hbuf_मुक्त_slots  : query क्रम ग_लिखो buffer empty slots
 * @hbuf_is_पढ़ोy    : query अगर ग_लिखो buffer is empty
 * @hbuf_depth       : query क्रम ग_लिखो buffer depth
 *
 * @ग_लिखो            : ग_लिखो a message to FW
 *
 * @rdbuf_full_slots : query how many slots are filled
 *
 * @पढ़ो_hdr         : get first 4 bytes (header)
 * @पढ़ो             : पढ़ो a buffer from the FW
 */
काष्ठा mei_hw_ops अणु

	bool (*host_is_पढ़ोy)(काष्ठा mei_device *dev);

	bool (*hw_is_पढ़ोy)(काष्ठा mei_device *dev);
	पूर्णांक (*hw_reset)(काष्ठा mei_device *dev, bool enable);
	पूर्णांक (*hw_start)(काष्ठा mei_device *dev);
	पूर्णांक (*hw_config)(काष्ठा mei_device *dev);

	पूर्णांक (*fw_status)(काष्ठा mei_device *dev, काष्ठा mei_fw_status *fw_sts);
	पूर्णांक (*trc_status)(काष्ठा mei_device *dev, u32 *trc);

	क्रमागत mei_pg_state (*pg_state)(काष्ठा mei_device *dev);
	bool (*pg_in_transition)(काष्ठा mei_device *dev);
	bool (*pg_is_enabled)(काष्ठा mei_device *dev);

	व्योम (*पूर्णांकr_clear)(काष्ठा mei_device *dev);
	व्योम (*पूर्णांकr_enable)(काष्ठा mei_device *dev);
	व्योम (*पूर्णांकr_disable)(काष्ठा mei_device *dev);
	व्योम (*synchronize_irq)(काष्ठा mei_device *dev);

	पूर्णांक (*hbuf_मुक्त_slots)(काष्ठा mei_device *dev);
	bool (*hbuf_is_पढ़ोy)(काष्ठा mei_device *dev);
	u32 (*hbuf_depth)(स्थिर काष्ठा mei_device *dev);
	पूर्णांक (*ग_लिखो)(काष्ठा mei_device *dev,
		     स्थिर व्योम *hdr, माप_प्रकार hdr_len,
		     स्थिर व्योम *data, माप_प्रकार data_len);

	पूर्णांक (*rdbuf_full_slots)(काष्ठा mei_device *dev);

	u32 (*पढ़ो_hdr)(स्थिर काष्ठा mei_device *dev);
	पूर्णांक (*पढ़ो)(काष्ठा mei_device *dev,
		     अचिन्हित अक्षर *buf, अचिन्हित दीर्घ len);
पूर्ण;

/* MEI bus API*/
व्योम mei_cl_bus_rescan_work(काष्ठा work_काष्ठा *work);
व्योम mei_cl_bus_dev_fixup(काष्ठा mei_cl_device *dev);
sमाप_प्रकार __mei_cl_send(काष्ठा mei_cl *cl, u8 *buf, माप_प्रकार length, u8 vtag,
		      अचिन्हित पूर्णांक mode);
sमाप_प्रकार __mei_cl_recv(काष्ठा mei_cl *cl, u8 *buf, माप_प्रकार length, u8 *vtag,
		      अचिन्हित पूर्णांक mode, अचिन्हित दीर्घ समयout);
bool mei_cl_bus_rx_event(काष्ठा mei_cl *cl);
bool mei_cl_bus_notअगरy_event(काष्ठा mei_cl *cl);
व्योम mei_cl_bus_हटाओ_devices(काष्ठा mei_device *bus);
पूर्णांक mei_cl_bus_init(व्योम);
व्योम mei_cl_bus_निकास(व्योम);

/**
 * क्रमागत mei_pg_event - घातer gating transition events
 *
 * @MEI_PG_EVENT_IDLE: the driver is not in घातer gating transition
 * @MEI_PG_EVENT_WAIT: the driver is रुकोing क्रम a pg event to complete
 * @MEI_PG_EVENT_RECEIVED: the driver received pg event
 * @MEI_PG_EVENT_INTR_WAIT: the driver is रुकोing क्रम a pg event पूर्णांकerrupt
 * @MEI_PG_EVENT_INTR_RECEIVED: the driver received pg event पूर्णांकerrupt
 */
क्रमागत mei_pg_event अणु
	MEI_PG_EVENT_IDLE,
	MEI_PG_EVENT_WAIT,
	MEI_PG_EVENT_RECEIVED,
	MEI_PG_EVENT_INTR_WAIT,
	MEI_PG_EVENT_INTR_RECEIVED,
पूर्ण;

/**
 * क्रमागत mei_pg_state - device पूर्णांकernal घातer gating state
 *
 * @MEI_PG_OFF: device is not घातer gated - it is active
 * @MEI_PG_ON:  device is घातer gated - it is in lower घातer state
 */
क्रमागत mei_pg_state अणु
	MEI_PG_OFF = 0,
	MEI_PG_ON =  1,
पूर्ण;

स्थिर अक्षर *mei_pg_state_str(क्रमागत mei_pg_state state);

/**
 * काष्ठा mei_fw_version - MEI FW version काष्ठा
 *
 * @platक्रमm: platक्रमm identअगरier
 * @major: major version field
 * @minor: minor version field
 * @buildno: build number version field
 * @hotfix: hotfix number version field
 */
काष्ठा mei_fw_version अणु
	u8 platक्रमm;
	u8 major;
	u16 minor;
	u16 buildno;
	u16 hotfix;
पूर्ण;

#घोषणा MEI_MAX_FW_VER_BLOCKS 3

/**
 * काष्ठा mei_device -  MEI निजी device काष्ठा
 *
 * @dev         : device on a bus
 * @cdev        : अक्षरacter device
 * @minor       : minor number allocated क्रम device
 *
 * @ग_लिखो_list  : ग_लिखो pending list
 * @ग_लिखो_रुकोing_list : ग_लिखो completion list
 * @ctrl_wr_list : pending control ग_लिखो list
 * @ctrl_rd_list : pending control पढ़ो list
 * @tx_queue_limit: tx queues per client linit
 *
 * @file_list   : list of खोलोed handles
 * @खोलो_handle_count: number of खोलोed handles
 *
 * @device_lock : big device lock
 * @समयr_work  : MEI समयr delayed work (समयouts)
 *
 * @recvd_hw_पढ़ोy : hw पढ़ोy message received flag
 *
 * @रुको_hw_पढ़ोy : रुको queue क्रम receive HW पढ़ोy message क्रमm FW
 * @रुको_pg     : रुको queue क्रम receive PG message from FW
 * @रुको_hbm_start : रुको queue क्रम receive HBM start message from FW
 *
 * @reset_count : number of consecutive resets
 * @dev_state   : device state
 * @hbm_state   : state of host bus message protocol
 * @init_clients_समयr : HBM init handshake समयout
 *
 * @pg_event    : घातer gating event
 * @pg_करोमुख्य   : runसमय PM करोमुख्य
 *
 * @rd_msg_buf  : control messages buffer
 * @rd_msg_hdr  : पढ़ो message header storage
 * @rd_msg_hdr_count : how many dwords were alपढ़ोy पढ़ो from header
 *
 * @hbuf_is_पढ़ोy : query अगर the host host/ग_लिखो buffer is पढ़ोy
 * @dr_dscr: DMA ring descriptors: TX, RX, and CTRL
 *
 * @version     : HBM protocol version in use
 * @hbm_f_pg_supported  : hbm feature pgi protocol
 * @hbm_f_dc_supported  : hbm feature dynamic clients
 * @hbm_f_करोt_supported : hbm feature disconnect on समयout
 * @hbm_f_ev_supported  : hbm feature event notअगरication
 * @hbm_f_fa_supported  : hbm feature fixed address client
 * @hbm_f_ie_supported  : hbm feature immediate reply to क्रमागत request
 * @hbm_f_os_supported  : hbm feature support OS ver message
 * @hbm_f_dr_supported  : hbm feature dma ring supported
 * @hbm_f_vt_supported  : hbm feature vtag supported
 * @hbm_f_cap_supported : hbm feature capabilities message supported
 * @hbm_f_cd_supported  : hbm feature client dma supported
 *
 * @fw_ver : FW versions
 *
 * @fw_f_fw_ver_supported : fw feature: fw version supported
 *
 * @me_clients_rwsem: rw lock over me_clients list
 * @me_clients  : list of FW clients
 * @me_clients_map : FW clients bit map
 * @host_clients_map : host clients id pool
 *
 * @allow_fixed_address: allow user space to connect a fixed client
 * @override_fixed_address: क्रमce allow fixed address behavior
 *
 * @reset_work  : work item क्रम the device reset
 * @bus_rescan_work : work item क्रम the bus rescan
 *
 * @device_list : mei client bus list
 * @cl_bus_lock : client bus list lock
 *
 * @kind        : kind of mei device
 *
 * @dbgfs_dir   : debugfs mei root directory
 *
 * @ops:        : hw specअगरic operations
 * @hw          : hw specअगरic data
 */
काष्ठा mei_device अणु
	काष्ठा device *dev;
	काष्ठा cdev cdev;
	पूर्णांक minor;

	काष्ठा list_head ग_लिखो_list;
	काष्ठा list_head ग_लिखो_रुकोing_list;
	काष्ठा list_head ctrl_wr_list;
	काष्ठा list_head ctrl_rd_list;
	u8 tx_queue_limit;

	काष्ठा list_head file_list;
	दीर्घ खोलो_handle_count;

	काष्ठा mutex device_lock;
	काष्ठा delayed_work समयr_work;

	bool recvd_hw_पढ़ोy;
	/*
	 * रुकोing queue क्रम receive message from FW
	 */
	रुको_queue_head_t रुको_hw_पढ़ोy;
	रुको_queue_head_t रुको_pg;
	रुको_queue_head_t रुको_hbm_start;

	/*
	 * mei device  states
	 */
	अचिन्हित दीर्घ reset_count;
	क्रमागत mei_dev_state dev_state;
	क्रमागत mei_hbm_state hbm_state;
	u16 init_clients_समयr;

	/*
	 * Power Gating support
	 */
	क्रमागत mei_pg_event pg_event;
#अगर_घोषित CONFIG_PM
	काष्ठा dev_pm_करोमुख्य pg_करोमुख्य;
#पूर्ण_अगर /* CONFIG_PM */

	अचिन्हित अक्षर rd_msg_buf[MEI_RD_MSG_BUF_SIZE];
	u32 rd_msg_hdr[MEI_RD_MSG_BUF_SIZE];
	पूर्णांक rd_msg_hdr_count;

	/* ग_लिखो buffer */
	bool hbuf_is_पढ़ोy;

	काष्ठा mei_dma_dscr dr_dscr[DMA_DSCR_NUM];

	काष्ठा hbm_version version;
	अचिन्हित पूर्णांक hbm_f_pg_supported:1;
	अचिन्हित पूर्णांक hbm_f_dc_supported:1;
	अचिन्हित पूर्णांक hbm_f_करोt_supported:1;
	अचिन्हित पूर्णांक hbm_f_ev_supported:1;
	अचिन्हित पूर्णांक hbm_f_fa_supported:1;
	अचिन्हित पूर्णांक hbm_f_ie_supported:1;
	अचिन्हित पूर्णांक hbm_f_os_supported:1;
	अचिन्हित पूर्णांक hbm_f_dr_supported:1;
	अचिन्हित पूर्णांक hbm_f_vt_supported:1;
	अचिन्हित पूर्णांक hbm_f_cap_supported:1;
	अचिन्हित पूर्णांक hbm_f_cd_supported:1;

	काष्ठा mei_fw_version fw_ver[MEI_MAX_FW_VER_BLOCKS];

	अचिन्हित पूर्णांक fw_f_fw_ver_supported:1;

	काष्ठा rw_semaphore me_clients_rwsem;
	काष्ठा list_head me_clients;
	DECLARE_BITMAP(me_clients_map, MEI_CLIENTS_MAX);
	DECLARE_BITMAP(host_clients_map, MEI_CLIENTS_MAX);

	bool allow_fixed_address;
	bool override_fixed_address;

	काष्ठा work_काष्ठा reset_work;
	काष्ठा work_काष्ठा bus_rescan_work;

	/* List of bus devices */
	काष्ठा list_head device_list;
	काष्ठा mutex cl_bus_lock;

	स्थिर अक्षर *kind;

#अगर IS_ENABLED(CONFIG_DEBUG_FS)
	काष्ठा dentry *dbgfs_dir;
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

	स्थिर काष्ठा mei_hw_ops *ops;
	अक्षर hw[] __aligned(माप(व्योम *));
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ mei_secs_to_jअगरfies(अचिन्हित दीर्घ sec)
अणु
	वापस msecs_to_jअगरfies(sec * MSEC_PER_SEC);
पूर्ण

/**
 * mei_data2slots - get slots number from a message length
 *
 * @length: size of the messages in bytes
 *
 * Return: number of slots
 */
अटल अंतरभूत u32 mei_data2slots(माप_प्रकार length)
अणु
	वापस DIV_ROUND_UP(length, MEI_SLOT_SIZE);
पूर्ण

/**
 * mei_hbm2slots - get slots number from a hbm message length
 *                 length + size of the mei message header
 *
 * @length: size of the messages in bytes
 *
 * Return: number of slots
 */
अटल अंतरभूत u32 mei_hbm2slots(माप_प्रकार length)
अणु
	वापस DIV_ROUND_UP(माप(काष्ठा mei_msg_hdr) + length, MEI_SLOT_SIZE);
पूर्ण

/**
 * mei_slots2data - get data in slots - bytes from slots
 *
 * @slots: number of available slots
 *
 * Return: number of bytes in slots
 */
अटल अंतरभूत u32 mei_slots2data(पूर्णांक slots)
अणु
	वापस slots * MEI_SLOT_SIZE;
पूर्ण

/*
 * mei init function prototypes
 */
व्योम mei_device_init(काष्ठा mei_device *dev,
		     काष्ठा device *device,
		     स्थिर काष्ठा mei_hw_ops *hw_ops);
पूर्णांक mei_reset(काष्ठा mei_device *dev);
पूर्णांक mei_start(काष्ठा mei_device *dev);
पूर्णांक mei_restart(काष्ठा mei_device *dev);
व्योम mei_stop(काष्ठा mei_device *dev);
व्योम mei_cancel_work(काष्ठा mei_device *dev);

व्योम mei_set_devstate(काष्ठा mei_device *dev, क्रमागत mei_dev_state state);

पूर्णांक mei_dmam_ring_alloc(काष्ठा mei_device *dev);
व्योम mei_dmam_ring_मुक्त(काष्ठा mei_device *dev);
bool mei_dma_ring_is_allocated(काष्ठा mei_device *dev);
व्योम mei_dma_ring_reset(काष्ठा mei_device *dev);
व्योम mei_dma_ring_पढ़ो(काष्ठा mei_device *dev, अचिन्हित अक्षर *buf, u32 len);
व्योम mei_dma_ring_ग_लिखो(काष्ठा mei_device *dev, अचिन्हित अक्षर *buf, u32 len);
u32 mei_dma_ring_empty_slots(काष्ठा mei_device *dev);

/*
 *  MEI पूर्णांकerrupt functions prototype
 */

व्योम mei_समयr(काष्ठा work_काष्ठा *work);
व्योम mei_schedule_stall_समयr(काष्ठा mei_device *dev);
पूर्णांक mei_irq_पढ़ो_handler(काष्ठा mei_device *dev,
			 काष्ठा list_head *cmpl_list, s32 *slots);

पूर्णांक mei_irq_ग_लिखो_handler(काष्ठा mei_device *dev, काष्ठा list_head *cmpl_list);
व्योम mei_irq_compl_handler(काष्ठा mei_device *dev, काष्ठा list_head *cmpl_list);

/*
 * Register Access Function
 */


अटल अंतरभूत पूर्णांक mei_hw_config(काष्ठा mei_device *dev)
अणु
	वापस dev->ops->hw_config(dev);
पूर्ण

अटल अंतरभूत क्रमागत mei_pg_state mei_pg_state(काष्ठा mei_device *dev)
अणु
	वापस dev->ops->pg_state(dev);
पूर्ण

अटल अंतरभूत bool mei_pg_in_transition(काष्ठा mei_device *dev)
अणु
	वापस dev->ops->pg_in_transition(dev);
पूर्ण

अटल अंतरभूत bool mei_pg_is_enabled(काष्ठा mei_device *dev)
अणु
	वापस dev->ops->pg_is_enabled(dev);
पूर्ण

अटल अंतरभूत पूर्णांक mei_hw_reset(काष्ठा mei_device *dev, bool enable)
अणु
	वापस dev->ops->hw_reset(dev, enable);
पूर्ण

अटल अंतरभूत पूर्णांक mei_hw_start(काष्ठा mei_device *dev)
अणु
	वापस dev->ops->hw_start(dev);
पूर्ण

अटल अंतरभूत व्योम mei_clear_पूर्णांकerrupts(काष्ठा mei_device *dev)
अणु
	dev->ops->पूर्णांकr_clear(dev);
पूर्ण

अटल अंतरभूत व्योम mei_enable_पूर्णांकerrupts(काष्ठा mei_device *dev)
अणु
	dev->ops->पूर्णांकr_enable(dev);
पूर्ण

अटल अंतरभूत व्योम mei_disable_पूर्णांकerrupts(काष्ठा mei_device *dev)
अणु
	dev->ops->पूर्णांकr_disable(dev);
पूर्ण

अटल अंतरभूत व्योम mei_synchronize_irq(काष्ठा mei_device *dev)
अणु
	dev->ops->synchronize_irq(dev);
पूर्ण

अटल अंतरभूत bool mei_host_is_पढ़ोy(काष्ठा mei_device *dev)
अणु
	वापस dev->ops->host_is_पढ़ोy(dev);
पूर्ण
अटल अंतरभूत bool mei_hw_is_पढ़ोy(काष्ठा mei_device *dev)
अणु
	वापस dev->ops->hw_is_पढ़ोy(dev);
पूर्ण

अटल अंतरभूत bool mei_hbuf_is_पढ़ोy(काष्ठा mei_device *dev)
अणु
	वापस dev->ops->hbuf_is_पढ़ोy(dev);
पूर्ण

अटल अंतरभूत पूर्णांक mei_hbuf_empty_slots(काष्ठा mei_device *dev)
अणु
	वापस dev->ops->hbuf_मुक्त_slots(dev);
पूर्ण

अटल अंतरभूत u32 mei_hbuf_depth(स्थिर काष्ठा mei_device *dev)
अणु
	वापस dev->ops->hbuf_depth(dev);
पूर्ण

अटल अंतरभूत पूर्णांक mei_ग_लिखो_message(काष्ठा mei_device *dev,
				    स्थिर व्योम *hdr, माप_प्रकार hdr_len,
				    स्थिर व्योम *data, माप_प्रकार data_len)
अणु
	वापस dev->ops->ग_लिखो(dev, hdr, hdr_len, data, data_len);
पूर्ण

अटल अंतरभूत u32 mei_पढ़ो_hdr(स्थिर काष्ठा mei_device *dev)
अणु
	वापस dev->ops->पढ़ो_hdr(dev);
पूर्ण

अटल अंतरभूत व्योम mei_पढ़ो_slots(काष्ठा mei_device *dev,
		     अचिन्हित अक्षर *buf, अचिन्हित दीर्घ len)
अणु
	dev->ops->पढ़ो(dev, buf, len);
पूर्ण

अटल अंतरभूत पूर्णांक mei_count_full_पढ़ो_slots(काष्ठा mei_device *dev)
अणु
	वापस dev->ops->rdbuf_full_slots(dev);
पूर्ण

अटल अंतरभूत पूर्णांक mei_trc_status(काष्ठा mei_device *dev, u32 *trc)
अणु
	अगर (dev->ops->trc_status)
		वापस dev->ops->trc_status(dev, trc);
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक mei_fw_status(काष्ठा mei_device *dev,
				काष्ठा mei_fw_status *fw_status)
अणु
	वापस dev->ops->fw_status(dev, fw_status);
पूर्ण

bool mei_hbuf_acquire(काष्ठा mei_device *dev);

bool mei_ग_लिखो_is_idle(काष्ठा mei_device *dev);

#अगर IS_ENABLED(CONFIG_DEBUG_FS)
व्योम mei_dbgfs_रेजिस्टर(काष्ठा mei_device *dev, स्थिर अक्षर *name);
व्योम mei_dbgfs_deरेजिस्टर(काष्ठा mei_device *dev);
#अन्यथा
अटल अंतरभूत व्योम mei_dbgfs_रेजिस्टर(काष्ठा mei_device *dev, स्थिर अक्षर *name) अणुपूर्ण
अटल अंतरभूत व्योम mei_dbgfs_deरेजिस्टर(काष्ठा mei_device *dev) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

पूर्णांक mei_रेजिस्टर(काष्ठा mei_device *dev, काष्ठा device *parent);
व्योम mei_deरेजिस्टर(काष्ठा mei_device *dev);

#घोषणा MEI_HDR_FMT "hdr:host=%02d me=%02d len=%d dma=%1d ext=%1d internal=%1d comp=%1d"
#घोषणा MEI_HDR_PRM(hdr)                  \
	(hdr)->host_addr, (hdr)->me_addr, \
	(hdr)->length, (hdr)->dma_ring, (hdr)->extended, \
	(hdr)->पूर्णांकernal, (hdr)->msg_complete

sमाप_प्रकार mei_fw_status2str(काष्ठा mei_fw_status *fw_sts, अक्षर *buf, माप_प्रकार len);
/**
 * mei_fw_status_str - fetch and convert fw status रेजिस्टरs to prपूर्णांकable string
 *
 * @dev: the device काष्ठाure
 * @buf: string buffer at minimal size MEI_FW_STATUS_STR_SZ
 * @len: buffer len must be >= MEI_FW_STATUS_STR_SZ
 *
 * Return: number of bytes written or < 0 on failure
 */
अटल अंतरभूत sमाप_प्रकार mei_fw_status_str(काष्ठा mei_device *dev,
					अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा mei_fw_status fw_status;
	पूर्णांक ret;

	buf[0] = '\0';

	ret = mei_fw_status(dev, &fw_status);
	अगर (ret)
		वापस ret;

	ret = mei_fw_status2str(&fw_status, buf, MEI_FW_STATUS_STR_SZ);

	वापस ret;
पूर्ण


#पूर्ण_अगर
