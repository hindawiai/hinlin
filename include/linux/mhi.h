<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2018-2020, The Linux Foundation. All rights reserved.
 *
 */
#अगर_अघोषित _MHI_H_
#घोषणा _MHI_H_

#समावेश <linux/device.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/mutex.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>

#घोषणा MHI_MAX_OEM_PK_HASH_SEGMENTS 16

काष्ठा mhi_chan;
काष्ठा mhi_event;
काष्ठा mhi_ctxt;
काष्ठा mhi_cmd;
काष्ठा mhi_buf_info;

/**
 * क्रमागत mhi_callback - MHI callback
 * @MHI_CB_IDLE: MHI entered idle state
 * @MHI_CB_PENDING_DATA: New data available क्रम client to process
 * @MHI_CB_LPM_ENTER: MHI host entered low घातer mode
 * @MHI_CB_LPM_EXIT: MHI host about to निकास low घातer mode
 * @MHI_CB_EE_RDDM: MHI device entered RDDM exec env
 * @MHI_CB_EE_MISSION_MODE: MHI device entered Mission Mode exec env
 * @MHI_CB_SYS_ERROR: MHI device entered error state (may recover)
 * @MHI_CB_FATAL_ERROR: MHI device entered fatal error state
 * @MHI_CB_BW_REQ: Received a bandwidth चयन request from device
 */
क्रमागत mhi_callback अणु
	MHI_CB_IDLE,
	MHI_CB_PENDING_DATA,
	MHI_CB_LPM_ENTER,
	MHI_CB_LPM_EXIT,
	MHI_CB_EE_RDDM,
	MHI_CB_EE_MISSION_MODE,
	MHI_CB_SYS_ERROR,
	MHI_CB_FATAL_ERROR,
	MHI_CB_BW_REQ,
पूर्ण;

/**
 * क्रमागत mhi_flags - Transfer flags
 * @MHI_EOB: End of buffer क्रम bulk transfer
 * @MHI_EOT: End of transfer
 * @MHI_CHAIN: Linked transfer
 */
क्रमागत mhi_flags अणु
	MHI_EOB = BIT(0),
	MHI_EOT = BIT(1),
	MHI_CHAIN = BIT(2),
पूर्ण;

/**
 * क्रमागत mhi_device_type - Device types
 * @MHI_DEVICE_XFER: Handles data transfer
 * @MHI_DEVICE_CONTROLLER: Control device
 */
क्रमागत mhi_device_type अणु
	MHI_DEVICE_XFER,
	MHI_DEVICE_CONTROLLER,
पूर्ण;

/**
 * क्रमागत mhi_ch_type - Channel types
 * @MHI_CH_TYPE_INVALID: Invalid channel type
 * @MHI_CH_TYPE_OUTBOUND: Outbound channel to the device
 * @MHI_CH_TYPE_INBOUND: Inbound channel from the device
 * @MHI_CH_TYPE_INBOUND_COALESCED: Coalesced channel क्रम the device to combine
 *				   multiple packets and send them as a single
 *				   large packet to reduce CPU consumption
 */
क्रमागत mhi_ch_type अणु
	MHI_CH_TYPE_INVALID = 0,
	MHI_CH_TYPE_OUTBOUND = DMA_TO_DEVICE,
	MHI_CH_TYPE_INBOUND = DMA_FROM_DEVICE,
	MHI_CH_TYPE_INBOUND_COALESCED = 3,
पूर्ण;

/**
 * काष्ठा image_info - Firmware and RDDM table
 * @mhi_buf: Buffer क्रम firmware and RDDM table
 * @entries: # of entries in table
 */
काष्ठा image_info अणु
	काष्ठा mhi_buf *mhi_buf;
	/* निजी: from पूर्णांकernal.h */
	काष्ठा bhi_vec_entry *bhi_vec;
	/* खुला: */
	u32 entries;
पूर्ण;

/**
 * काष्ठा mhi_link_info - BW requirement
 * target_link_speed - Link speed as defined by TLS bits in LinkControl reg
 * target_link_width - Link width as defined by NLW bits in LinkStatus reg
 */
काष्ठा mhi_link_info अणु
	अचिन्हित पूर्णांक target_link_speed;
	अचिन्हित पूर्णांक target_link_width;
पूर्ण;

/**
 * क्रमागत mhi_ee_type - Execution environment types
 * @MHI_EE_PBL: Primary Bootloader
 * @MHI_EE_SBL: Secondary Bootloader
 * @MHI_EE_AMSS: Modem, aka the primary runसमय EE
 * @MHI_EE_RDDM: Ram dump करोwnload mode
 * @MHI_EE_WFW: WLAN firmware mode
 * @MHI_EE_PTHRU: Passthrough
 * @MHI_EE_EDL: Embedded करोwnloader
 * @MHI_EE_FP: Flash Programmer Environment
 */
क्रमागत mhi_ee_type अणु
	MHI_EE_PBL,
	MHI_EE_SBL,
	MHI_EE_AMSS,
	MHI_EE_RDDM,
	MHI_EE_WFW,
	MHI_EE_PTHRU,
	MHI_EE_EDL,
	MHI_EE_FP,
	MHI_EE_MAX_SUPPORTED = MHI_EE_FP,
	MHI_EE_DISABLE_TRANSITION, /* local EE, not related to mhi spec */
	MHI_EE_NOT_SUPPORTED,
	MHI_EE_MAX,
पूर्ण;

/**
 * क्रमागत mhi_state - MHI states
 * @MHI_STATE_RESET: Reset state
 * @MHI_STATE_READY: Ready state
 * @MHI_STATE_M0: M0 state
 * @MHI_STATE_M1: M1 state
 * @MHI_STATE_M2: M2 state
 * @MHI_STATE_M3: M3 state
 * @MHI_STATE_M3_FAST: M3 Fast state
 * @MHI_STATE_BHI: BHI state
 * @MHI_STATE_SYS_ERR: System Error state
 */
क्रमागत mhi_state अणु
	MHI_STATE_RESET = 0x0,
	MHI_STATE_READY = 0x1,
	MHI_STATE_M0 = 0x2,
	MHI_STATE_M1 = 0x3,
	MHI_STATE_M2 = 0x4,
	MHI_STATE_M3 = 0x5,
	MHI_STATE_M3_FAST = 0x6,
	MHI_STATE_BHI = 0x7,
	MHI_STATE_SYS_ERR = 0xFF,
	MHI_STATE_MAX,
पूर्ण;

/**
 * क्रमागत mhi_ch_ee_mask - Execution environment mask क्रम channel
 * @MHI_CH_EE_PBL: Allow channel to be used in PBL EE
 * @MHI_CH_EE_SBL: Allow channel to be used in SBL EE
 * @MHI_CH_EE_AMSS: Allow channel to be used in AMSS EE
 * @MHI_CH_EE_RDDM: Allow channel to be used in RDDM EE
 * @MHI_CH_EE_PTHRU: Allow channel to be used in PTHRU EE
 * @MHI_CH_EE_WFW: Allow channel to be used in WFW EE
 * @MHI_CH_EE_EDL: Allow channel to be used in EDL EE
 */
क्रमागत mhi_ch_ee_mask अणु
	MHI_CH_EE_PBL = BIT(MHI_EE_PBL),
	MHI_CH_EE_SBL = BIT(MHI_EE_SBL),
	MHI_CH_EE_AMSS = BIT(MHI_EE_AMSS),
	MHI_CH_EE_RDDM = BIT(MHI_EE_RDDM),
	MHI_CH_EE_PTHRU = BIT(MHI_EE_PTHRU),
	MHI_CH_EE_WFW = BIT(MHI_EE_WFW),
	MHI_CH_EE_EDL = BIT(MHI_EE_EDL),
पूर्ण;

/**
 * क्रमागत mhi_er_data_type - Event ring data types
 * @MHI_ER_DATA: Only client data over this ring
 * @MHI_ER_CTRL: MHI control data and client data
 */
क्रमागत mhi_er_data_type अणु
	MHI_ER_DATA,
	MHI_ER_CTRL,
पूर्ण;

/**
 * क्रमागत mhi_db_brst_mode - Doorbell mode
 * @MHI_DB_BRST_DISABLE: Burst mode disable
 * @MHI_DB_BRST_ENABLE: Burst mode enable
 */
क्रमागत mhi_db_brst_mode अणु
	MHI_DB_BRST_DISABLE = 0x2,
	MHI_DB_BRST_ENABLE = 0x3,
पूर्ण;

/**
 * काष्ठा mhi_channel_config - Channel configuration काष्ठाure क्रम controller
 * @name: The name of this channel
 * @num: The number asचिन्हित to this channel
 * @num_elements: The number of elements that can be queued to this channel
 * @local_elements: The local ring length of the channel
 * @event_ring: The event ring index that services this channel
 * @dir: Direction that data may flow on this channel
 * @type: Channel type
 * @ee_mask: Execution Environment mask क्रम this channel
 * @pollcfg: Polling configuration क्रम burst mode.  0 is शेष.  milliseconds
	     क्रम UL channels, multiple of 8 ring elements क्रम DL channels
 * @करोorbell: Doorbell mode
 * @lpm_notअगरy: The channel master requires low घातer mode notअगरications
 * @offload_channel: The client manages the channel completely
 * @करोorbell_mode_चयन: Channel चयनes to करोorbell mode on M0 transition
 * @स्वतः_queue: Framework will स्वतःmatically queue buffers क्रम DL traffic
 * @wake-capable: Channel capable of waking up the प्रणाली
 */
काष्ठा mhi_channel_config अणु
	अक्षर *name;
	u32 num;
	u32 num_elements;
	u32 local_elements;
	u32 event_ring;
	क्रमागत dma_data_direction dir;
	क्रमागत mhi_ch_type type;
	u32 ee_mask;
	u32 pollcfg;
	क्रमागत mhi_db_brst_mode करोorbell;
	bool lpm_notअगरy;
	bool offload_channel;
	bool करोorbell_mode_चयन;
	bool स्वतः_queue;
	bool wake_capable;
पूर्ण;

/**
 * काष्ठा mhi_event_config - Event ring configuration काष्ठाure क्रम controller
 * @num_elements: The number of elements that can be queued to this ring
 * @irq_moderation_ms: Delay irq क्रम additional events to be aggregated
 * @irq: IRQ associated with this ring
 * @channel: Dedicated channel number. U32_MAX indicates a non-dedicated ring
 * @priority: Priority of this ring. Use 1 क्रम now
 * @mode: Doorbell mode
 * @data_type: Type of data this ring will process
 * @hardware_event: This ring is associated with hardware channels
 * @client_managed: This ring is client managed
 * @offload_channel: This ring is associated with an offloaded channel
 */
काष्ठा mhi_event_config अणु
	u32 num_elements;
	u32 irq_moderation_ms;
	u32 irq;
	u32 channel;
	u32 priority;
	क्रमागत mhi_db_brst_mode mode;
	क्रमागत mhi_er_data_type data_type;
	bool hardware_event;
	bool client_managed;
	bool offload_channel;
पूर्ण;

/**
 * काष्ठा mhi_controller_config - Root MHI controller configuration
 * @max_channels: Maximum number of channels supported
 * @समयout_ms: Timeout value क्रम operations. 0 means use शेष
 * @buf_len: Size of स्वतःmatically allocated buffers. 0 means use शेष
 * @num_channels: Number of channels defined in @ch_cfg
 * @ch_cfg: Array of defined channels
 * @num_events: Number of event rings defined in @event_cfg
 * @event_cfg: Array of defined event rings
 * @use_bounce_buf: Use a bounce buffer pool due to limited DDR access
 * @m2_no_db: Host is not allowed to ring DB in M2 state
 */
काष्ठा mhi_controller_config अणु
	u32 max_channels;
	u32 समयout_ms;
	u32 buf_len;
	u32 num_channels;
	स्थिर काष्ठा mhi_channel_config *ch_cfg;
	u32 num_events;
	काष्ठा mhi_event_config *event_cfg;
	bool use_bounce_buf;
	bool m2_no_db;
पूर्ण;

/**
 * काष्ठा mhi_controller - Master MHI controller काष्ठाure
 * @cntrl_dev: Poपूर्णांकer to the काष्ठा device of physical bus acting as the MHI
 *            controller (required)
 * @mhi_dev: MHI device instance क्रम the controller
 * @debugfs_dentry: MHI controller debugfs directory
 * @regs: Base address of MHI MMIO रेजिस्टर space (required)
 * @bhi: Poपूर्णांकs to base of MHI BHI रेजिस्टर space
 * @bhie: Poपूर्णांकs to base of MHI BHIe रेजिस्टर space
 * @wake_db: MHI WAKE करोorbell रेजिस्टर address
 * @ioबहु_शुरू: IOMMU starting address क्रम data (required)
 * @iova_stop: IOMMU stop address क्रम data (required)
 * @fw_image: Firmware image name क्रम normal booting (optional)
 * @edl_image: Firmware image name क्रम emergency करोwnload mode (optional)
 * @rddm_size: RAM dump size that host should allocate क्रम debugging purpose
 * @sbl_size: SBL image size करोwnloaded through BHIe (optional)
 * @seg_len: BHIe vector size (optional)
 * @fbc_image: Poपूर्णांकs to firmware image buffer
 * @rddm_image: Poपूर्णांकs to RAM dump buffer
 * @mhi_chan: Poपूर्णांकs to the channel configuration table
 * @lpm_chans: List of channels that require LPM notअगरications
 * @irq: base irq # to request (required)
 * @max_chan: Maximum number of channels the controller supports
 * @total_ev_rings: Total # of event rings allocated
 * @hw_ev_rings: Number of hardware event rings
 * @sw_ev_rings: Number of software event rings
 * @nr_irqs: Number of IRQ allocated by bus master (required)
 * @family_number: MHI controller family number
 * @device_number: MHI controller device number
 * @major_version: MHI controller major revision number
 * @minor_version: MHI controller minor revision number
 * @serial_number: MHI controller serial number obtained from BHI
 * @oem_pk_hash: MHI controller OEM PK Hash obtained from BHI
 * @mhi_event: MHI event ring configurations table
 * @mhi_cmd: MHI command ring configurations table
 * @mhi_ctxt: MHI device context, shared memory between host and device
 * @pm_mutex: Mutex क्रम suspend/resume operation
 * @pm_lock: Lock क्रम protecting MHI घातer management state
 * @समयout_ms: Timeout in ms क्रम state transitions
 * @pm_state: MHI घातer management state
 * @db_access: DB access states
 * @ee: MHI device execution environment
 * @dev_state: MHI device state
 * @dev_wake: Device wakeup count
 * @pending_pkts: Pending packets क्रम the controller
 * @M0, M2, M3: Counters to track number of device MHI state changes
 * @transition_list: List of MHI state transitions
 * @transition_lock: Lock क्रम protecting MHI state transition list
 * @wlock: Lock क्रम protecting device wakeup
 * @mhi_link_info: Device bandwidth info
 * @st_worker: State transition worker
 * @hiprio_wq: High priority workqueue क्रम MHI work such as state transitions
 * @state_event: State change event
 * @status_cb: CB function to notअगरy घातer states of the device (required)
 * @wake_get: CB function to निश्चित device wake (optional)
 * @wake_put: CB function to de-निश्चित device wake (optional)
 * @wake_toggle: CB function to निश्चित and de-निश्चित device wake (optional)
 * @runसमय_get: CB function to controller runसमय resume (required)
 * @runसमय_put: CB function to decrement pm usage (required)
 * @map_single: CB function to create TRE buffer
 * @unmap_single: CB function to destroy TRE buffer
 * @पढ़ो_reg: Read a MHI रेजिस्टर via the physical link (required)
 * @ग_लिखो_reg: Write a MHI रेजिस्टर via the physical link (required)
 * @reset: Controller specअगरic reset function (optional)
 * @buffer_len: Bounce buffer length
 * @index: Index of the MHI controller instance
 * @bounce_buf: Use of bounce buffer
 * @fbc_करोwnload: MHI host needs to करो complete image transfer (optional)
 * @wake_set: Device wakeup set flag
 * @irq_flags: irq flags passed to request_irq (optional)
 *
 * Fields marked as (required) need to be populated by the controller driver
 * beक्रमe calling mhi_रेजिस्टर_controller(). For the fields marked as (optional)
 * they can be populated depending on the useहाल.
 *
 * The following fields are present क्रम the purpose of implementing any device
 * specअगरic quirks or customizations क्रम specअगरic MHI revisions used in device
 * by the controller drivers. The MHI stack will just populate these fields
 * during mhi_रेजिस्टर_controller():
 *  family_number
 *  device_number
 *  major_version
 *  minor_version
 */
काष्ठा mhi_controller अणु
	काष्ठा device *cntrl_dev;
	काष्ठा mhi_device *mhi_dev;
	काष्ठा dentry *debugfs_dentry;
	व्योम __iomem *regs;
	व्योम __iomem *bhi;
	व्योम __iomem *bhie;
	व्योम __iomem *wake_db;

	dma_addr_t ioबहु_शुरू;
	dma_addr_t iova_stop;
	स्थिर अक्षर *fw_image;
	स्थिर अक्षर *edl_image;
	माप_प्रकार rddm_size;
	माप_प्रकार sbl_size;
	माप_प्रकार seg_len;
	काष्ठा image_info *fbc_image;
	काष्ठा image_info *rddm_image;
	काष्ठा mhi_chan *mhi_chan;
	काष्ठा list_head lpm_chans;
	पूर्णांक *irq;
	u32 max_chan;
	u32 total_ev_rings;
	u32 hw_ev_rings;
	u32 sw_ev_rings;
	u32 nr_irqs;
	u32 family_number;
	u32 device_number;
	u32 major_version;
	u32 minor_version;
	u32 serial_number;
	u32 oem_pk_hash[MHI_MAX_OEM_PK_HASH_SEGMENTS];

	काष्ठा mhi_event *mhi_event;
	काष्ठा mhi_cmd *mhi_cmd;
	काष्ठा mhi_ctxt *mhi_ctxt;

	काष्ठा mutex pm_mutex;
	rwlock_t pm_lock;
	u32 समयout_ms;
	u32 pm_state;
	u32 db_access;
	क्रमागत mhi_ee_type ee;
	क्रमागत mhi_state dev_state;
	atomic_t dev_wake;
	atomic_t pending_pkts;
	u32 M0, M2, M3;
	काष्ठा list_head transition_list;
	spinlock_t transition_lock;
	spinlock_t wlock;
	काष्ठा mhi_link_info mhi_link_info;
	काष्ठा work_काष्ठा st_worker;
	काष्ठा workqueue_काष्ठा *hiprio_wq;
	रुको_queue_head_t state_event;

	व्योम (*status_cb)(काष्ठा mhi_controller *mhi_cntrl,
			  क्रमागत mhi_callback cb);
	व्योम (*wake_get)(काष्ठा mhi_controller *mhi_cntrl, bool override);
	व्योम (*wake_put)(काष्ठा mhi_controller *mhi_cntrl, bool override);
	व्योम (*wake_toggle)(काष्ठा mhi_controller *mhi_cntrl);
	पूर्णांक (*runसमय_get)(काष्ठा mhi_controller *mhi_cntrl);
	व्योम (*runसमय_put)(काष्ठा mhi_controller *mhi_cntrl);
	पूर्णांक (*map_single)(काष्ठा mhi_controller *mhi_cntrl,
			  काष्ठा mhi_buf_info *buf);
	व्योम (*unmap_single)(काष्ठा mhi_controller *mhi_cntrl,
			     काष्ठा mhi_buf_info *buf);
	पूर्णांक (*पढ़ो_reg)(काष्ठा mhi_controller *mhi_cntrl, व्योम __iomem *addr,
			u32 *out);
	व्योम (*ग_लिखो_reg)(काष्ठा mhi_controller *mhi_cntrl, व्योम __iomem *addr,
			  u32 val);
	व्योम (*reset)(काष्ठा mhi_controller *mhi_cntrl);

	माप_प्रकार buffer_len;
	पूर्णांक index;
	bool bounce_buf;
	bool fbc_करोwnload;
	bool wake_set;
	अचिन्हित दीर्घ irq_flags;
पूर्ण;

/**
 * काष्ठा mhi_device - Structure representing an MHI device which binds
 *                     to channels or is associated with controllers
 * @id: Poपूर्णांकer to MHI device ID काष्ठा
 * @name: Name of the associated MHI device
 * @mhi_cntrl: Controller the device beदीर्घs to
 * @ul_chan: UL channel क्रम the device
 * @dl_chan: DL channel क्रम the device
 * @dev: Driver model device node क्रम the MHI device
 * @dev_type: MHI device type
 * @ul_chan_id: MHI channel id क्रम UL transfer
 * @dl_chan_id: MHI channel id क्रम DL transfer
 * @dev_wake: Device wakeup counter
 */
काष्ठा mhi_device अणु
	स्थिर काष्ठा mhi_device_id *id;
	स्थिर अक्षर *name;
	काष्ठा mhi_controller *mhi_cntrl;
	काष्ठा mhi_chan *ul_chan;
	काष्ठा mhi_chan *dl_chan;
	काष्ठा device dev;
	क्रमागत mhi_device_type dev_type;
	पूर्णांक ul_chan_id;
	पूर्णांक dl_chan_id;
	u32 dev_wake;
पूर्ण;

/**
 * काष्ठा mhi_result - Completed buffer inक्रमmation
 * @buf_addr: Address of data buffer
 * @bytes_xferd: # of bytes transferred
 * @dir: Channel direction
 * @transaction_status: Status of last transaction
 */
काष्ठा mhi_result अणु
	व्योम *buf_addr;
	माप_प्रकार bytes_xferd;
	क्रमागत dma_data_direction dir;
	पूर्णांक transaction_status;
पूर्ण;

/**
 * काष्ठा mhi_buf - MHI Buffer description
 * @buf: Virtual address of the buffer
 * @name: Buffer label. For offload channel, configurations name must be:
 *        ECA - Event context array data
 *        CCA - Channel context array data
 * @dma_addr: IOMMU address of the buffer
 * @len: # of bytes
 */
काष्ठा mhi_buf अणु
	व्योम *buf;
	स्थिर अक्षर *name;
	dma_addr_t dma_addr;
	माप_प्रकार len;
पूर्ण;

/**
 * काष्ठा mhi_driver - Structure representing a MHI client driver
 * @probe: CB function क्रम client driver probe function
 * @हटाओ: CB function क्रम client driver हटाओ function
 * @ul_xfer_cb: CB function क्रम UL data transfer
 * @dl_xfer_cb: CB function क्रम DL data transfer
 * @status_cb: CB functions क्रम asynchronous status
 * @driver: Device driver model driver
 */
काष्ठा mhi_driver अणु
	स्थिर काष्ठा mhi_device_id *id_table;
	पूर्णांक (*probe)(काष्ठा mhi_device *mhi_dev,
		     स्थिर काष्ठा mhi_device_id *id);
	व्योम (*हटाओ)(काष्ठा mhi_device *mhi_dev);
	व्योम (*ul_xfer_cb)(काष्ठा mhi_device *mhi_dev,
			   काष्ठा mhi_result *result);
	व्योम (*dl_xfer_cb)(काष्ठा mhi_device *mhi_dev,
			   काष्ठा mhi_result *result);
	व्योम (*status_cb)(काष्ठा mhi_device *mhi_dev, क्रमागत mhi_callback mhi_cb);
	काष्ठा device_driver driver;
पूर्ण;

#घोषणा to_mhi_driver(drv) container_of(drv, काष्ठा mhi_driver, driver)
#घोषणा to_mhi_device(dev) container_of(dev, काष्ठा mhi_device, dev)

/**
 * mhi_alloc_controller - Allocate the MHI Controller काष्ठाure
 * Allocate the mhi_controller काष्ठाure using zero initialized memory
 */
काष्ठा mhi_controller *mhi_alloc_controller(व्योम);

/**
 * mhi_मुक्त_controller - Free the MHI Controller काष्ठाure
 * Free the mhi_controller काष्ठाure which was previously allocated
 */
व्योम mhi_मुक्त_controller(काष्ठा mhi_controller *mhi_cntrl);

/**
 * mhi_रेजिस्टर_controller - Register MHI controller
 * @mhi_cntrl: MHI controller to रेजिस्टर
 * @config: Configuration to use क्रम the controller
 */
पूर्णांक mhi_रेजिस्टर_controller(काष्ठा mhi_controller *mhi_cntrl,
			स्थिर काष्ठा mhi_controller_config *config);

/**
 * mhi_unरेजिस्टर_controller - Unरेजिस्टर MHI controller
 * @mhi_cntrl: MHI controller to unरेजिस्टर
 */
व्योम mhi_unरेजिस्टर_controller(काष्ठा mhi_controller *mhi_cntrl);

/*
 * module_mhi_driver() - Helper macro क्रम drivers that करोn't करो
 * anything special other than using शेष mhi_driver_रेजिस्टर() and
 * mhi_driver_unरेजिस्टर().  This eliminates a lot of boilerplate.
 * Each module may only use this macro once.
 */
#घोषणा module_mhi_driver(mhi_drv) \
	module_driver(mhi_drv, mhi_driver_रेजिस्टर, \
		      mhi_driver_unरेजिस्टर)

/*
 * Macro to aव्योम include chaining to get THIS_MODULE
 */
#घोषणा mhi_driver_रेजिस्टर(mhi_drv) \
	__mhi_driver_रेजिस्टर(mhi_drv, THIS_MODULE)

/**
 * __mhi_driver_रेजिस्टर - Register driver with MHI framework
 * @mhi_drv: Driver associated with the device
 * @owner: The module owner
 */
पूर्णांक __mhi_driver_रेजिस्टर(काष्ठा mhi_driver *mhi_drv, काष्ठा module *owner);

/**
 * mhi_driver_unरेजिस्टर - Unरेजिस्टर a driver क्रम mhi_devices
 * @mhi_drv: Driver associated with the device
 */
व्योम mhi_driver_unरेजिस्टर(काष्ठा mhi_driver *mhi_drv);

/**
 * mhi_set_mhi_state - Set MHI device state
 * @mhi_cntrl: MHI controller
 * @state: State to set
 */
व्योम mhi_set_mhi_state(काष्ठा mhi_controller *mhi_cntrl,
		       क्रमागत mhi_state state);

/**
 * mhi_notअगरy - Notअगरy the MHI client driver about client device status
 * @mhi_dev: MHI device instance
 * @cb_reason: MHI callback reason
 */
व्योम mhi_notअगरy(काष्ठा mhi_device *mhi_dev, क्रमागत mhi_callback cb_reason);

/**
 * mhi_get_मुक्त_desc_count - Get transfer ring length
 * Get # of TD available to queue buffers
 * @mhi_dev: Device associated with the channels
 * @dir: Direction of the channel
 */
पूर्णांक mhi_get_मुक्त_desc_count(काष्ठा mhi_device *mhi_dev,
				क्रमागत dma_data_direction dir);

/**
 * mhi_prepare_क्रम_घातer_up - Do pre-initialization beक्रमe घातer up.
 *                            This is optional, call this beक्रमe घातer up अगर
 *                            the controller करोes not want bus framework to
 *                            स्वतःmatically मुक्त any allocated memory during
 *                            shutकरोwn process.
 * @mhi_cntrl: MHI controller
 */
पूर्णांक mhi_prepare_क्रम_घातer_up(काष्ठा mhi_controller *mhi_cntrl);

/**
 * mhi_async_घातer_up - Start MHI घातer up sequence
 * @mhi_cntrl: MHI controller
 */
पूर्णांक mhi_async_घातer_up(काष्ठा mhi_controller *mhi_cntrl);

/**
 * mhi_sync_घातer_up - Start MHI घातer up sequence and रुको till the device
 *                     enters valid EE state
 * @mhi_cntrl: MHI controller
 */
पूर्णांक mhi_sync_घातer_up(काष्ठा mhi_controller *mhi_cntrl);

/**
 * mhi_घातer_करोwn - Start MHI घातer करोwn sequence
 * @mhi_cntrl: MHI controller
 * @graceful: Link is still accessible, so करो a graceful shutकरोwn process
 */
व्योम mhi_घातer_करोwn(काष्ठा mhi_controller *mhi_cntrl, bool graceful);

/**
 * mhi_unprepare_after_घातer_करोwn - Free any allocated memory after घातer करोwn
 * @mhi_cntrl: MHI controller
 */
व्योम mhi_unprepare_after_घातer_करोwn(काष्ठा mhi_controller *mhi_cntrl);

/**
 * mhi_pm_suspend - Move MHI पूर्णांकo a suspended state
 * @mhi_cntrl: MHI controller
 */
पूर्णांक mhi_pm_suspend(काष्ठा mhi_controller *mhi_cntrl);

/**
 * mhi_pm_resume - Resume MHI from suspended state
 * @mhi_cntrl: MHI controller
 */
पूर्णांक mhi_pm_resume(काष्ठा mhi_controller *mhi_cntrl);

/**
 * mhi_करोwnload_rddm_image - Download ramdump image from device क्रम
 *                           debugging purpose.
 * @mhi_cntrl: MHI controller
 * @in_panic: Download rddm image during kernel panic
 */
पूर्णांक mhi_करोwnload_rddm_image(काष्ठा mhi_controller *mhi_cntrl, bool in_panic);

/**
 * mhi_क्रमce_rddm_mode - Force device पूर्णांकo rddm mode
 * @mhi_cntrl: MHI controller
 */
पूर्णांक mhi_क्रमce_rddm_mode(काष्ठा mhi_controller *mhi_cntrl);

/**
 * mhi_get_exec_env - Get BHI execution environment of the device
 * @mhi_cntrl: MHI controller
 */
क्रमागत mhi_ee_type mhi_get_exec_env(काष्ठा mhi_controller *mhi_cntrl);

/**
 * mhi_get_mhi_state - Get MHI state of the device
 * @mhi_cntrl: MHI controller
 */
क्रमागत mhi_state mhi_get_mhi_state(काष्ठा mhi_controller *mhi_cntrl);

/**
 * mhi_soc_reset - Trigger a device reset. This can be used as a last resort
 *		   to reset and recover a device.
 * @mhi_cntrl: MHI controller
 */
व्योम mhi_soc_reset(काष्ठा mhi_controller *mhi_cntrl);

/**
 * mhi_device_get - Disable device low घातer mode
 * @mhi_dev: Device associated with the channel
 */
व्योम mhi_device_get(काष्ठा mhi_device *mhi_dev);

/**
 * mhi_device_get_sync - Disable device low घातer mode. Synchronously
 *                       take the controller out of suspended state
 * @mhi_dev: Device associated with the channel
 */
पूर्णांक mhi_device_get_sync(काष्ठा mhi_device *mhi_dev);

/**
 * mhi_device_put - Re-enable device low घातer mode
 * @mhi_dev: Device associated with the channel
 */
व्योम mhi_device_put(काष्ठा mhi_device *mhi_dev);

/**
 * mhi_prepare_क्रम_transfer - Setup UL and DL channels क्रम data transfer.
 *                            Allocate and initialize the channel context and
 *                            also issue the START channel command to both
 *                            channels. Channels can be started only अगर both
 *                            host and device execution environments match and
 *                            channels are in a DISABLED state.
 * @mhi_dev: Device associated with the channels
 */
पूर्णांक mhi_prepare_क्रम_transfer(काष्ठा mhi_device *mhi_dev);

/**
 * mhi_unprepare_from_transfer - Reset UL and DL channels क्रम data transfer.
 *                               Issue the RESET channel command and let the
 *                               device clean-up the context so no incoming
 *                               transfers are seen on the host. Free memory
 *                               associated with the context on host. If device
 *                               is unresponsive, only perक्रमm a host side
 *                               clean-up. Channels can be reset only अगर both
 *                               host and device execution environments match
 *                               and channels are in an ENABLED, STOPPED or
 *                               SUSPENDED state.
 * @mhi_dev: Device associated with the channels
 */
व्योम mhi_unprepare_from_transfer(काष्ठा mhi_device *mhi_dev);

/**
 * mhi_poll - Poll क्रम any available data in DL direction
 * @mhi_dev: Device associated with the channels
 * @budget: # of events to process
 */
पूर्णांक mhi_poll(काष्ठा mhi_device *mhi_dev, u32 budget);

/**
 * mhi_queue_dma - Send or receive DMA mapped buffers from client device
 *                 over MHI channel
 * @mhi_dev: Device associated with the channels
 * @dir: DMA direction क्रम the channel
 * @mhi_buf: Buffer क्रम holding the DMA mapped data
 * @len: Buffer length
 * @mflags: MHI transfer flags used क्रम the transfer
 */
पूर्णांक mhi_queue_dma(काष्ठा mhi_device *mhi_dev, क्रमागत dma_data_direction dir,
		  काष्ठा mhi_buf *mhi_buf, माप_प्रकार len, क्रमागत mhi_flags mflags);

/**
 * mhi_queue_buf - Send or receive raw buffers from client device over MHI
 *                 channel
 * @mhi_dev: Device associated with the channels
 * @dir: DMA direction क्रम the channel
 * @buf: Buffer क्रम holding the data
 * @len: Buffer length
 * @mflags: MHI transfer flags used क्रम the transfer
 */
पूर्णांक mhi_queue_buf(काष्ठा mhi_device *mhi_dev, क्रमागत dma_data_direction dir,
		  व्योम *buf, माप_प्रकार len, क्रमागत mhi_flags mflags);

/**
 * mhi_queue_skb - Send or receive SKBs from client device over MHI channel
 * @mhi_dev: Device associated with the channels
 * @dir: DMA direction क्रम the channel
 * @skb: Buffer क्रम holding SKBs
 * @len: Buffer length
 * @mflags: MHI transfer flags used क्रम the transfer
 */
पूर्णांक mhi_queue_skb(काष्ठा mhi_device *mhi_dev, क्रमागत dma_data_direction dir,
		  काष्ठा sk_buff *skb, माप_प्रकार len, क्रमागत mhi_flags mflags);

/**
 * mhi_queue_is_full - Determine whether queueing new elements is possible
 * @mhi_dev: Device associated with the channels
 * @dir: DMA direction क्रम the channel
 */
bool mhi_queue_is_full(काष्ठा mhi_device *mhi_dev, क्रमागत dma_data_direction dir);

#पूर्ण_अगर /* _MHI_H_ */
