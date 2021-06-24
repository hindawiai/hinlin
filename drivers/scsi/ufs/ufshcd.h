<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Universal Flash Storage Host controller driver
 * Copyright (C) 2011-2013 Samsung India Software Operations
 * Copyright (c) 2013-2016, The Linux Foundation. All rights reserved.
 *
 * Authors:
 *	Santosh Yaraganavi <santosh.sy@samsung.com>
 *	Vinayak Holikatti <h.vinayak@samsung.com>
 */

#अगर_अघोषित _UFSHCD_H
#घोषणा _UFSHCD_H

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>
#समावेश <linux/bitops.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/devfreq.h>
#समावेश <linux/keyslot-manager.h>
#समावेश "unipro.h"

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_eh.h>

#समावेश "ufs.h"
#समावेश "ufs_quirks.h"
#समावेश "ufshci.h"

#घोषणा UFSHCD "ufshcd"
#घोषणा UFSHCD_DRIVER_VERSION "0.2"

काष्ठा ufs_hba;

क्रमागत dev_cmd_type अणु
	DEV_CMD_TYPE_NOP		= 0x0,
	DEV_CMD_TYPE_QUERY		= 0x1,
पूर्ण;

क्रमागत ufs_event_type अणु
	/* uic specअगरic errors */
	UFS_EVT_PA_ERR = 0,
	UFS_EVT_DL_ERR,
	UFS_EVT_NL_ERR,
	UFS_EVT_TL_ERR,
	UFS_EVT_DME_ERR,

	/* fatal errors */
	UFS_EVT_AUTO_HIBERN8_ERR,
	UFS_EVT_FATAL_ERR,
	UFS_EVT_LINK_STARTUP_FAIL,
	UFS_EVT_RESUME_ERR,
	UFS_EVT_SUSPEND_ERR,

	/* abnormal events */
	UFS_EVT_DEV_RESET,
	UFS_EVT_HOST_RESET,
	UFS_EVT_ABORT,

	UFS_EVT_CNT,
पूर्ण;

/**
 * काष्ठा uic_command - UIC command काष्ठाure
 * @command: UIC command
 * @argument1: UIC command argument 1
 * @argument2: UIC command argument 2
 * @argument3: UIC command argument 3
 * @cmd_active: Indicate अगर UIC command is outstanding
 * @करोne: UIC command completion
 */
काष्ठा uic_command अणु
	u32 command;
	u32 argument1;
	u32 argument2;
	u32 argument3;
	पूर्णांक cmd_active;
	काष्ठा completion करोne;
पूर्ण;

/* Used to dअगरferentiate the घातer management options */
क्रमागत ufs_pm_op अणु
	UFS_RUNTIME_PM,
	UFS_SYSTEM_PM,
	UFS_SHUTDOWN_PM,
पूर्ण;

#घोषणा ufshcd_is_runसमय_pm(op) ((op) == UFS_RUNTIME_PM)
#घोषणा ufshcd_is_प्रणाली_pm(op) ((op) == UFS_SYSTEM_PM)
#घोषणा ufshcd_is_shutकरोwn_pm(op) ((op) == UFS_SHUTDOWN_PM)

/* Host <-> Device UniPro Link state */
क्रमागत uic_link_state अणु
	UIC_LINK_OFF_STATE	= 0, /* Link घातered करोwn or disabled */
	UIC_LINK_ACTIVE_STATE	= 1, /* Link is in Fast/Slow/Sleep state */
	UIC_LINK_HIBERN8_STATE	= 2, /* Link is in Hibernate state */
	UIC_LINK_BROKEN_STATE	= 3, /* Link is in broken state */
पूर्ण;

#घोषणा ufshcd_is_link_off(hba) ((hba)->uic_link_state == UIC_LINK_OFF_STATE)
#घोषणा ufshcd_is_link_active(hba) ((hba)->uic_link_state == \
				    UIC_LINK_ACTIVE_STATE)
#घोषणा ufshcd_is_link_hibern8(hba) ((hba)->uic_link_state == \
				    UIC_LINK_HIBERN8_STATE)
#घोषणा ufshcd_is_link_broken(hba) ((hba)->uic_link_state == \
				   UIC_LINK_BROKEN_STATE)
#घोषणा ufshcd_set_link_off(hba) ((hba)->uic_link_state = UIC_LINK_OFF_STATE)
#घोषणा ufshcd_set_link_active(hba) ((hba)->uic_link_state = \
				    UIC_LINK_ACTIVE_STATE)
#घोषणा ufshcd_set_link_hibern8(hba) ((hba)->uic_link_state = \
				    UIC_LINK_HIBERN8_STATE)
#घोषणा ufshcd_set_link_broken(hba) ((hba)->uic_link_state = \
				    UIC_LINK_BROKEN_STATE)

#घोषणा ufshcd_set_ufs_dev_active(h) \
	((h)->curr_dev_pwr_mode = UFS_ACTIVE_PWR_MODE)
#घोषणा ufshcd_set_ufs_dev_sleep(h) \
	((h)->curr_dev_pwr_mode = UFS_SLEEP_PWR_MODE)
#घोषणा ufshcd_set_ufs_dev_घातeroff(h) \
	((h)->curr_dev_pwr_mode = UFS_POWERDOWN_PWR_MODE)
#घोषणा ufshcd_set_ufs_dev_deepsleep(h) \
	((h)->curr_dev_pwr_mode = UFS_DEEPSLEEP_PWR_MODE)
#घोषणा ufshcd_is_ufs_dev_active(h) \
	((h)->curr_dev_pwr_mode == UFS_ACTIVE_PWR_MODE)
#घोषणा ufshcd_is_ufs_dev_sleep(h) \
	((h)->curr_dev_pwr_mode == UFS_SLEEP_PWR_MODE)
#घोषणा ufshcd_is_ufs_dev_घातeroff(h) \
	((h)->curr_dev_pwr_mode == UFS_POWERDOWN_PWR_MODE)
#घोषणा ufshcd_is_ufs_dev_deepsleep(h) \
	((h)->curr_dev_pwr_mode == UFS_DEEPSLEEP_PWR_MODE)

/*
 * UFS Power management levels.
 * Each level is in increasing order of घातer savings, except DeepSleep
 * which is lower than PowerDown with घातer on but not PowerDown with
 * घातer off.
 */
क्रमागत ufs_pm_level अणु
	UFS_PM_LVL_0, /* UFS_ACTIVE_PWR_MODE, UIC_LINK_ACTIVE_STATE */
	UFS_PM_LVL_1, /* UFS_ACTIVE_PWR_MODE, UIC_LINK_HIBERN8_STATE */
	UFS_PM_LVL_2, /* UFS_SLEEP_PWR_MODE, UIC_LINK_ACTIVE_STATE */
	UFS_PM_LVL_3, /* UFS_SLEEP_PWR_MODE, UIC_LINK_HIBERN8_STATE */
	UFS_PM_LVL_4, /* UFS_POWERDOWN_PWR_MODE, UIC_LINK_HIBERN8_STATE */
	UFS_PM_LVL_5, /* UFS_POWERDOWN_PWR_MODE, UIC_LINK_OFF_STATE */
	UFS_PM_LVL_6, /* UFS_DEEPSLEEP_PWR_MODE, UIC_LINK_OFF_STATE */
	UFS_PM_LVL_MAX
पूर्ण;

काष्ठा ufs_pm_lvl_states अणु
	क्रमागत ufs_dev_pwr_mode dev_state;
	क्रमागत uic_link_state link_state;
पूर्ण;

/**
 * काष्ठा ufshcd_lrb - local reference block
 * @utr_descriptor_ptr: UTRD address of the command
 * @ucd_req_ptr: UCD address of the command
 * @ucd_rsp_ptr: Response UPIU address क्रम this command
 * @ucd_prdt_ptr: PRDT address of the command
 * @utrd_dma_addr: UTRD dma address क्रम debug
 * @ucd_prdt_dma_addr: PRDT dma address क्रम debug
 * @ucd_rsp_dma_addr: UPIU response dma address क्रम debug
 * @ucd_req_dma_addr: UPIU request dma address क्रम debug
 * @cmd: poपूर्णांकer to SCSI command
 * @sense_buffer: poपूर्णांकer to sense buffer address of the SCSI command
 * @sense_bufflen: Length of the sense buffer
 * @scsi_status: SCSI status of the command
 * @command_type: SCSI, UFS, Query.
 * @task_tag: Task tag of the command
 * @lun: LUN of the command
 * @पूर्णांकr_cmd: Interrupt command (करोesn't participate in पूर्णांकerrupt aggregation)
 * @issue_समय_stamp: समय stamp क्रम debug purposes
 * @compl_समय_stamp: समय stamp क्रम statistics
 * @crypto_key_slot: the key slot to use क्रम अंतरभूत crypto (-1 अगर none)
 * @data_unit_num: the data unit number क्रम the first block क्रम अंतरभूत crypto
 * @req_पात_skip: skip request पात task flag
 * @in_use: indicates that this lrb is still in use
 */
काष्ठा ufshcd_lrb अणु
	काष्ठा utp_transfer_req_desc *utr_descriptor_ptr;
	काष्ठा utp_upiu_req *ucd_req_ptr;
	काष्ठा utp_upiu_rsp *ucd_rsp_ptr;
	काष्ठा ufshcd_sg_entry *ucd_prdt_ptr;

	dma_addr_t utrd_dma_addr;
	dma_addr_t ucd_req_dma_addr;
	dma_addr_t ucd_rsp_dma_addr;
	dma_addr_t ucd_prdt_dma_addr;

	काष्ठा scsi_cmnd *cmd;
	u8 *sense_buffer;
	अचिन्हित पूर्णांक sense_bufflen;
	पूर्णांक scsi_status;

	पूर्णांक command_type;
	पूर्णांक task_tag;
	u8 lun; /* UPIU LUN id field is only 8-bit wide */
	bool पूर्णांकr_cmd;
	kसमय_प्रकार issue_समय_stamp;
	kसमय_प्रकार compl_समय_stamp;
#अगर_घोषित CONFIG_SCSI_UFS_CRYPTO
	पूर्णांक crypto_key_slot;
	u64 data_unit_num;
#पूर्ण_अगर

	bool req_पात_skip;
	bool in_use;
पूर्ण;

/**
 * काष्ठा ufs_query - holds relevant data काष्ठाures क्रम query request
 * @request: request upiu and function
 * @descriptor: buffer क्रम sending/receiving descriptor
 * @response: response upiu and response
 */
काष्ठा ufs_query अणु
	काष्ठा ufs_query_req request;
	u8 *descriptor;
	काष्ठा ufs_query_res response;
पूर्ण;

/**
 * काष्ठा ufs_dev_cmd - all assosiated fields with device management commands
 * @type: device management command type - Query, NOP OUT
 * @lock: lock to allow one command at a समय
 * @complete: पूर्णांकernal commands completion
 */
काष्ठा ufs_dev_cmd अणु
	क्रमागत dev_cmd_type type;
	काष्ठा mutex lock;
	काष्ठा completion *complete;
	काष्ठा ufs_query query;
पूर्ण;

/**
 * काष्ठा ufs_clk_info - UFS घड़ी related info
 * @list: list headed by hba->clk_list_head
 * @clk: घड़ी node
 * @name: घड़ी name
 * @max_freq: maximum frequency supported by the घड़ी
 * @min_freq: min frequency that can be used क्रम घड़ी scaling
 * @curr_freq: indicates the current frequency that it is set to
 * @keep_link_active: indicates that the clk should not be disabled अगर
		      link is active
 * @enabled: variable to check against multiple enable/disable
 */
काष्ठा ufs_clk_info अणु
	काष्ठा list_head list;
	काष्ठा clk *clk;
	स्थिर अक्षर *name;
	u32 max_freq;
	u32 min_freq;
	u32 curr_freq;
	bool keep_link_active;
	bool enabled;
पूर्ण;

क्रमागत ufs_notअगरy_change_status अणु
	PRE_CHANGE,
	POST_CHANGE,
पूर्ण;

काष्ठा ufs_pa_layer_attr अणु
	u32 gear_rx;
	u32 gear_tx;
	u32 lane_rx;
	u32 lane_tx;
	u32 pwr_rx;
	u32 pwr_tx;
	u32 hs_rate;
पूर्ण;

काष्ठा ufs_pwr_mode_info अणु
	bool is_valid;
	काष्ठा ufs_pa_layer_attr info;
पूर्ण;

/**
 * काष्ठा ufs_hba_variant_ops - variant specअगरic callbacks
 * @name: variant name
 * @init: called when the driver is initialized
 * @निकास: called to cleanup everything करोne in init
 * @get_ufs_hci_version: called to get UFS HCI version
 * @clk_scale_notअगरy: notअगरies that clks are scaled up/करोwn
 * @setup_घड़ीs: called beक्रमe touching any of the controller रेजिस्टरs
 * @hce_enable_notअगरy: called beक्रमe and after HCE enable bit is set to allow
 *                     variant specअगरic Uni-Pro initialization.
 * @link_startup_notअगरy: called beक्रमe and after Link startup is carried out
 *                       to allow variant specअगरic Uni-Pro initialization.
 * @pwr_change_notअगरy: called beक्रमe and after a घातer mode change
 *			is carried out to allow venकरोr spesअगरic capabilities
 *			to be set.
 * @setup_xfer_req: called beक्रमe any transfer request is issued
 *                  to set some things
 * @setup_task_mgmt: called beक्रमe any task management request is issued
 *                  to set some things
 * @hibern8_notअगरy: called around hibern8 enter/निकास
 * @apply_dev_quirks: called to apply device specअगरic quirks
 * @suspend: called during host controller PM callback
 * @resume: called during host controller PM callback
 * @dbg_रेजिस्टर_dump: used to dump controller debug inक्रमmation
 * @phy_initialization: used to initialize phys
 * @device_reset: called to issue a reset pulse on the UFS device
 * @program_key: program or evict an अंतरभूत encryption key
 * @event_notअगरy: called to notअगरy important events
 */
काष्ठा ufs_hba_variant_ops अणु
	स्थिर अक्षर *name;
	पूर्णांक	(*init)(काष्ठा ufs_hba *);
	व्योम    (*निकास)(काष्ठा ufs_hba *);
	u32	(*get_ufs_hci_version)(काष्ठा ufs_hba *);
	पूर्णांक	(*clk_scale_notअगरy)(काष्ठा ufs_hba *, bool,
				    क्रमागत ufs_notअगरy_change_status);
	पूर्णांक	(*setup_घड़ीs)(काष्ठा ufs_hba *, bool,
				क्रमागत ufs_notअगरy_change_status);
	पूर्णांक	(*hce_enable_notअगरy)(काष्ठा ufs_hba *,
				     क्रमागत ufs_notअगरy_change_status);
	पूर्णांक	(*link_startup_notअगरy)(काष्ठा ufs_hba *,
				       क्रमागत ufs_notअगरy_change_status);
	पूर्णांक	(*pwr_change_notअगरy)(काष्ठा ufs_hba *,
					क्रमागत ufs_notअगरy_change_status status,
					काष्ठा ufs_pa_layer_attr *,
					काष्ठा ufs_pa_layer_attr *);
	व्योम	(*setup_xfer_req)(काष्ठा ufs_hba *, पूर्णांक, bool);
	व्योम	(*setup_task_mgmt)(काष्ठा ufs_hba *, पूर्णांक, u8);
	व्योम    (*hibern8_notअगरy)(काष्ठा ufs_hba *, क्रमागत uic_cmd_dme,
					क्रमागत ufs_notअगरy_change_status);
	पूर्णांक	(*apply_dev_quirks)(काष्ठा ufs_hba *hba);
	व्योम	(*fixup_dev_quirks)(काष्ठा ufs_hba *hba);
	पूर्णांक     (*suspend)(काष्ठा ufs_hba *, क्रमागत ufs_pm_op);
	पूर्णांक     (*resume)(काष्ठा ufs_hba *, क्रमागत ufs_pm_op);
	व्योम	(*dbg_रेजिस्टर_dump)(काष्ठा ufs_hba *hba);
	पूर्णांक	(*phy_initialization)(काष्ठा ufs_hba *);
	पूर्णांक	(*device_reset)(काष्ठा ufs_hba *hba);
	व्योम	(*config_scaling_param)(काष्ठा ufs_hba *hba,
					काष्ठा devfreq_dev_profile *profile,
					व्योम *data);
	पूर्णांक	(*program_key)(काष्ठा ufs_hba *hba,
			       स्थिर जोड़ ufs_crypto_cfg_entry *cfg, पूर्णांक slot);
	व्योम	(*event_notअगरy)(काष्ठा ufs_hba *hba,
				क्रमागत ufs_event_type evt, व्योम *data);
पूर्ण;

/* घड़ी gating state  */
क्रमागत clk_gating_state अणु
	CLKS_OFF,
	CLKS_ON,
	REQ_CLKS_OFF,
	REQ_CLKS_ON,
पूर्ण;

/**
 * काष्ठा ufs_clk_gating - UFS घड़ी gating related info
 * @gate_work: worker to turn off घड़ीs after some delay as specअगरied in
 * delay_ms
 * @ungate_work: worker to turn on घड़ीs that will be used in हाल of
 * पूर्णांकerrupt context
 * @state: the current घड़ीs state
 * @delay_ms: gating delay in ms
 * @is_suspended: clk gating is suspended when set to 1 which can be used
 * during suspend/resume
 * @delay_attr: sysfs attribute to control delay_attr
 * @enable_attr: sysfs attribute to enable/disable घड़ी gating
 * @is_enabled: Indicates the current status of घड़ी gating
 * @is_initialized: Indicates whether घड़ी gating is initialized or not
 * @active_reqs: number of requests that are pending and should be रुकोed क्रम
 * completion beक्रमe gating घड़ीs.
 */
काष्ठा ufs_clk_gating अणु
	काष्ठा delayed_work gate_work;
	काष्ठा work_काष्ठा ungate_work;
	क्रमागत clk_gating_state state;
	अचिन्हित दीर्घ delay_ms;
	bool is_suspended;
	काष्ठा device_attribute delay_attr;
	काष्ठा device_attribute enable_attr;
	bool is_enabled;
	bool is_initialized;
	पूर्णांक active_reqs;
	काष्ठा workqueue_काष्ठा *clk_gating_workq;
पूर्ण;

काष्ठा ufs_saved_pwr_info अणु
	काष्ठा ufs_pa_layer_attr info;
	bool is_valid;
पूर्ण;

/**
 * काष्ठा ufs_clk_scaling - UFS घड़ी scaling related data
 * @active_reqs: number of requests that are pending. If this is zero when
 * devfreq ->target() function is called then schedule "suspend_work" to
 * suspend devfreq.
 * @tot_busy_t: Total busy समय in current polling winकरोw
 * @winकरोw_start_t: Start समय (in jअगरfies) of the current polling winकरोw
 * @busy_start_t: Start समय of current busy period
 * @enable_attr: sysfs attribute to enable/disable घड़ी scaling
 * @saved_pwr_info: UFS घातer mode may also be changed during scaling and this
 * one keeps track of previous घातer mode.
 * @workq: workqueue to schedule devfreq suspend/resume work
 * @suspend_work: worker to suspend devfreq
 * @resume_work: worker to resume devfreq
 * @min_gear: lowest HS gear to scale करोwn to
 * @is_enabled: tracks अगर scaling is currently enabled or not, controlled by
		clkscale_enable sysfs node
 * @is_allowed: tracks अगर scaling is currently allowed or not, used to block
		घड़ी scaling which is not invoked from devfreq governor
 * @is_initialized: Indicates whether घड़ी scaling is initialized or not
 * @is_busy_started: tracks अगर busy period has started or not
 * @is_suspended: tracks अगर devfreq is suspended or not
 */
काष्ठा ufs_clk_scaling अणु
	पूर्णांक active_reqs;
	अचिन्हित दीर्घ tot_busy_t;
	kसमय_प्रकार winकरोw_start_t;
	kसमय_प्रकार busy_start_t;
	काष्ठा device_attribute enable_attr;
	काष्ठा ufs_saved_pwr_info saved_pwr_info;
	काष्ठा workqueue_काष्ठा *workq;
	काष्ठा work_काष्ठा suspend_work;
	काष्ठा work_काष्ठा resume_work;
	u32 min_gear;
	bool is_enabled;
	bool is_allowed;
	bool is_initialized;
	bool is_busy_started;
	bool is_suspended;
पूर्ण;

#घोषणा UFS_EVENT_HIST_LENGTH 8
/**
 * काष्ठा ufs_event_hist - keeps history of errors
 * @pos: index to indicate cyclic buffer position
 * @reg: cyclic buffer क्रम रेजिस्टरs value
 * @tstamp: cyclic buffer क्रम समय stamp
 * @cnt: error counter
 */
काष्ठा ufs_event_hist अणु
	पूर्णांक pos;
	u32 val[UFS_EVENT_HIST_LENGTH];
	kसमय_प्रकार tstamp[UFS_EVENT_HIST_LENGTH];
	अचिन्हित दीर्घ दीर्घ cnt;
पूर्ण;

/**
 * काष्ठा ufs_stats - keeps usage/err statistics
 * @last_पूर्णांकr_status: record the last पूर्णांकerrupt status.
 * @last_पूर्णांकr_ts: record the last पूर्णांकerrupt बारtamp.
 * @hibern8_निकास_cnt: Counter to keep track of number of निकासs,
 *		reset this after link-startup.
 * @last_hibern8_निकास_tstamp: Set समय after the hibern8 निकास.
 *		Clear after the first successful command completion.
 */
काष्ठा ufs_stats अणु
	u32 last_पूर्णांकr_status;
	kसमय_प्रकार last_पूर्णांकr_ts;

	u32 hibern8_निकास_cnt;
	kसमय_प्रकार last_hibern8_निकास_tstamp;
	काष्ठा ufs_event_hist event[UFS_EVT_CNT];
पूर्ण;

क्रमागत ufshcd_quirks अणु
	/* Interrupt aggregation support is broken */
	UFSHCD_QUIRK_BROKEN_INTR_AGGR			= 1 << 0,

	/*
	 * delay beक्रमe each dme command is required as the unipro
	 * layer has shown instabilities
	 */
	UFSHCD_QUIRK_DELAY_BEFORE_DME_CMDS		= 1 << 1,

	/*
	 * If UFS host controller is having issue in processing LCC (Line
	 * Control Command) coming from device then enable this quirk.
	 * When this quirk is enabled, host controller driver should disable
	 * the LCC transmission on UFS device (by clearing TX_LCC_ENABLE
	 * attribute of device to 0).
	 */
	UFSHCD_QUIRK_BROKEN_LCC				= 1 << 2,

	/*
	 * The attribute PA_RXHSUNTERMCAP specअगरies whether or not the
	 * inbound Link supports unterminated line in HS mode. Setting this
	 * attribute to 1 fixes moving to HS gear.
	 */
	UFSHCD_QUIRK_BROKEN_PA_RXHSUNTERMCAP		= 1 << 3,

	/*
	 * This quirk needs to be enabled अगर the host controller only allows
	 * accessing the peer dme attributes in AUTO mode (FAST AUTO or
	 * SLOW AUTO).
	 */
	UFSHCD_QUIRK_DME_PEER_ACCESS_AUTO_MODE		= 1 << 4,

	/*
	 * This quirk needs to be enabled अगर the host controller करोesn't
	 * advertise the correct version in UFS_VER रेजिस्टर. If this quirk
	 * is enabled, standard UFS host driver will call the venकरोr specअगरic
	 * ops (get_ufs_hci_version) to get the correct version.
	 */
	UFSHCD_QUIRK_BROKEN_UFS_HCI_VERSION		= 1 << 5,

	/*
	 * Clear handling क्रम transfer/task request list is just opposite.
	 */
	UFSHCI_QUIRK_BROKEN_REQ_LIST_CLR		= 1 << 6,

	/*
	 * This quirk needs to be enabled अगर host controller करोesn't allow
	 * that the पूर्णांकerrupt aggregation समयr and counter are reset by s/w.
	 */
	UFSHCI_QUIRK_SKIP_RESET_INTR_AGGR		= 1 << 7,

	/*
	 * This quirks needs to be enabled अगर host controller cannot be
	 * enabled via HCE रेजिस्टर.
	 */
	UFSHCI_QUIRK_BROKEN_HCE				= 1 << 8,

	/*
	 * This quirk needs to be enabled अगर the host controller regards
	 * resolution of the values of PRDTO and PRDTL in UTRD as byte.
	 */
	UFSHCD_QUIRK_PRDT_BYTE_GRAN			= 1 << 9,

	/*
	 * This quirk needs to be enabled अगर the host controller reports
	 * OCS FATAL ERROR with device error through sense data
	 */
	UFSHCD_QUIRK_BROKEN_OCS_FATAL_ERROR		= 1 << 10,

	/*
	 * This quirk needs to be enabled अगर the host controller has
	 * स्वतः-hibernate capability but it करोesn't work.
	 */
	UFSHCD_QUIRK_BROKEN_AUTO_HIBERN8		= 1 << 11,

	/*
	 * This quirk needs to disable manual flush क्रम ग_लिखो booster
	 */
	UFSHCI_QUIRK_SKIP_MANUAL_WB_FLUSH_CTRL		= 1 << 12,

	/*
	 * This quirk needs to disable unipro समयout values
	 * beक्रमe घातer mode change
	 */
	UFSHCD_QUIRK_SKIP_DEF_UNIPRO_TIMEOUT_SETTING = 1 << 13,

	/*
	 * This quirk allows only sg entries aligned with page size.
	 */
	UFSHCD_QUIRK_ALIGN_SG_WITH_PAGE_SIZE		= 1 << 14,
पूर्ण;

क्रमागत ufshcd_caps अणु
	/* Allow dynamic clk gating */
	UFSHCD_CAP_CLK_GATING				= 1 << 0,

	/* Allow hiberb8 with clk gating */
	UFSHCD_CAP_HIBERN8_WITH_CLK_GATING		= 1 << 1,

	/* Allow dynamic clk scaling */
	UFSHCD_CAP_CLK_SCALING				= 1 << 2,

	/* Allow स्वतः bkops to enabled during runसमय suspend */
	UFSHCD_CAP_AUTO_BKOPS_SUSPEND			= 1 << 3,

	/*
	 * This capability allows host controller driver to use the UFS HCI's
	 * पूर्णांकerrupt aggregation capability.
	 * CAUTION: Enabling this might reduce overall UFS throughput.
	 */
	UFSHCD_CAP_INTR_AGGR				= 1 << 4,

	/*
	 * This capability allows the device स्वतः-bkops to be always enabled
	 * except during suspend (both runसमय and suspend).
	 * Enabling this capability means that device will always be allowed
	 * to करो background operation when it's active but it might degrade
	 * the perक्रमmance of ongoing पढ़ो/ग_लिखो operations.
	 */
	UFSHCD_CAP_KEEP_AUTO_BKOPS_ENABLED_EXCEPT_SUSPEND = 1 << 5,

	/*
	 * This capability allows host controller driver to स्वतःmatically
	 * enable runसमय घातer management by itself instead of रुकोing
	 * क्रम userspace to control the घातer management.
	 */
	UFSHCD_CAP_RPM_AUTOSUSPEND			= 1 << 6,

	/*
	 * This capability allows the host controller driver to turn-on
	 * WriteBooster, अगर the underlying device supports it and is
	 * provisioned to be used. This would increase the ग_लिखो perक्रमmance.
	 */
	UFSHCD_CAP_WB_EN				= 1 << 7,

	/*
	 * This capability allows the host controller driver to use the
	 * अंतरभूत crypto engine, अगर it is present
	 */
	UFSHCD_CAP_CRYPTO				= 1 << 8,

	/*
	 * This capability allows the controller regulators to be put पूर्णांकo
	 * lpm mode aggressively during घड़ी gating.
	 * This would increase घातer savings.
	 */
	UFSHCD_CAP_AGGR_POWER_COLLAPSE			= 1 << 9,

	/*
	 * This capability allows the host controller driver to use DeepSleep,
	 * अगर it is supported by the UFS device. The host controller driver must
	 * support device hardware reset via the hba->device_reset() callback,
	 * in order to निकास DeepSleep state.
	 */
	UFSHCD_CAP_DEEPSLEEP				= 1 << 10,
पूर्ण;

काष्ठा ufs_hba_variant_params अणु
	काष्ठा devfreq_dev_profile devfreq_profile;
	काष्ठा devfreq_simple_ondemand_data ondemand_data;
	u16 hba_enable_delay_us;
	u32 wb_flush_threshold;
पूर्ण;

/**
 * काष्ठा ufs_hba - per adapter निजी काष्ठाure
 * @mmio_base: UFSHCI base रेजिस्टर address
 * @ucdl_base_addr: UFS Command Descriptor base address
 * @utrdl_base_addr: UTP Transfer Request Descriptor base address
 * @uपंचांगrdl_base_addr: UTP Task Management Descriptor base address
 * @ucdl_dma_addr: UFS Command Descriptor DMA address
 * @utrdl_dma_addr: UTRDL DMA address
 * @uपंचांगrdl_dma_addr: UTMRDL DMA address
 * @host: Scsi_Host instance of the driver
 * @dev: device handle
 * @lrb: local reference block
 * @cmd_queue: Used to allocate command tags from hba->host->tag_set.
 * @outstanding_tasks: Bits representing outstanding task requests
 * @outstanding_reqs: Bits representing outstanding transfer requests
 * @capabilities: UFS Controller Capabilities
 * @nutrs: Transfer Request Queue depth supported by controller
 * @nuपंचांगrs: Task Management Queue depth supported by controller
 * @ufs_version: UFS Version to which controller complies
 * @vops: poपूर्णांकer to variant specअगरic operations
 * @priv: poपूर्णांकer to variant specअगरic निजी data
 * @irq: Irq number of the controller
 * @active_uic_cmd: handle of active UIC command
 * @uic_cmd_mutex: mutex क्रम uic command
 * @पंचांगf_tag_set: TMF tag set.
 * @पंचांगf_queue: Used to allocate TMF tags.
 * @pwr_करोne: completion क्रम घातer mode change
 * @ufshcd_state: UFSHCD states
 * @eh_flags: Error handling flags
 * @पूर्णांकr_mask: Interrupt Mask Bits
 * @ee_ctrl_mask: Exception event control mask
 * @is_घातered: flag to check अगर HBA is घातered
 * @shutting_करोwn: flag to check अगर shutकरोwn has been invoked
 * @host_sem: semaphore used to serialize concurrent contexts
 * @eh_wq: Workqueue that eh_work works on
 * @eh_work: Worker to handle UFS errors that require s/w attention
 * @eeh_work: Worker to handle exception events
 * @errors: HBA errors
 * @uic_error: UFS पूर्णांकerconnect layer error status
 * @saved_err: sticky error mask
 * @saved_uic_err: sticky UIC error mask
 * @क्रमce_reset: flag to क्रमce eh_work perक्रमm a full reset
 * @क्रमce_pmc: flag to क्रमce a घातer mode change
 * @silence_err_logs: flag to silence error logs
 * @dev_cmd: ufs device management command inक्रमmation
 * @last_dme_cmd_tstamp: समय stamp of the last completed DME command
 * @स्वतः_bkops_enabled: to track whether bkops is enabled in device
 * @vreg_info: UFS device voltage regulator inक्रमmation
 * @clk_list_head: UFS host controller घड़ीs list node head
 * @pwr_info: holds current घातer mode
 * @max_pwr_info: keeps the device max valid pwm
 * @desc_size: descriptor sizes reported by device
 * @urgent_bkops_lvl: keeps track of urgent bkops level क्रम device
 * @is_urgent_bkops_lvl_checked: keeps track अगर the urgent bkops level क्रम
 *  device is known or not.
 * @scsi_block_reqs_cnt: reference counting क्रम scsi block requests
 * @crypto_capabilities: Content of crypto capabilities रेजिस्टर (0x100)
 * @crypto_cap_array: Array of crypto capabilities
 * @crypto_cfg_रेजिस्टर: Start of the crypto cfg array
 * @ksm: the keyslot manager tied to this hba
 */
काष्ठा ufs_hba अणु
	व्योम __iomem *mmio_base;

	/* Virtual memory reference */
	काष्ठा utp_transfer_cmd_desc *ucdl_base_addr;
	काष्ठा utp_transfer_req_desc *utrdl_base_addr;
	काष्ठा utp_task_req_desc *uपंचांगrdl_base_addr;

	/* DMA memory reference */
	dma_addr_t ucdl_dma_addr;
	dma_addr_t utrdl_dma_addr;
	dma_addr_t uपंचांगrdl_dma_addr;

	काष्ठा Scsi_Host *host;
	काष्ठा device *dev;
	काष्ठा request_queue *cmd_queue;
	/*
	 * This field is to keep a reference to "scsi_device" corresponding to
	 * "UFS device" W-LU.
	 */
	काष्ठा scsi_device *sdev_ufs_device;
	काष्ठा scsi_device *sdev_rpmb;

	क्रमागत ufs_dev_pwr_mode curr_dev_pwr_mode;
	क्रमागत uic_link_state uic_link_state;
	/* Desired UFS घातer management level during runसमय PM */
	क्रमागत ufs_pm_level rpm_lvl;
	/* Desired UFS घातer management level during प्रणाली PM */
	क्रमागत ufs_pm_level spm_lvl;
	काष्ठा device_attribute rpm_lvl_attr;
	काष्ठा device_attribute spm_lvl_attr;
	पूर्णांक pm_op_in_progress;

	/* Auto-Hibernate Idle Timer रेजिस्टर value */
	u32 ahit;

	काष्ठा ufshcd_lrb *lrb;

	अचिन्हित दीर्घ outstanding_tasks;
	अचिन्हित दीर्घ outstanding_reqs;

	u32 capabilities;
	पूर्णांक nutrs;
	पूर्णांक nuपंचांगrs;
	u32 ufs_version;
	स्थिर काष्ठा ufs_hba_variant_ops *vops;
	काष्ठा ufs_hba_variant_params *vps;
	व्योम *priv;
	अचिन्हित पूर्णांक irq;
	bool is_irq_enabled;
	क्रमागत ufs_ref_clk_freq dev_ref_clk_freq;

	अचिन्हित पूर्णांक quirks;	/* Deviations from standard UFSHCI spec. */

	/* Device deviations from standard UFS device spec. */
	अचिन्हित पूर्णांक dev_quirks;

	काष्ठा blk_mq_tag_set पंचांगf_tag_set;
	काष्ठा request_queue *पंचांगf_queue;

	काष्ठा uic_command *active_uic_cmd;
	काष्ठा mutex uic_cmd_mutex;
	काष्ठा completion *uic_async_करोne;

	u32 ufshcd_state;
	u32 eh_flags;
	u32 पूर्णांकr_mask;
	u16 ee_ctrl_mask; /* Exception event mask */
	u16 ee_drv_mask;  /* Exception event mask क्रम driver */
	u16 ee_usr_mask;  /* Exception event mask क्रम user (via debugfs) */
	काष्ठा mutex ee_ctrl_mutex;
	bool is_घातered;
	bool shutting_करोwn;
	काष्ठा semaphore host_sem;

	/* Work Queues */
	काष्ठा workqueue_काष्ठा *eh_wq;
	काष्ठा work_काष्ठा eh_work;
	काष्ठा work_काष्ठा eeh_work;

	/* HBA Errors */
	u32 errors;
	u32 uic_error;
	u32 saved_err;
	u32 saved_uic_err;
	काष्ठा ufs_stats ufs_stats;
	bool क्रमce_reset;
	bool क्रमce_pmc;
	bool silence_err_logs;

	/* Device management request data */
	काष्ठा ufs_dev_cmd dev_cmd;
	kसमय_प्रकार last_dme_cmd_tstamp;

	/* Keeps inक्रमmation of the UFS device connected to this host */
	काष्ठा ufs_dev_info dev_info;
	bool स्वतः_bkops_enabled;
	काष्ठा ufs_vreg_info vreg_info;
	काष्ठा list_head clk_list_head;

	bool wlun_dev_clr_ua;

	/* Number of requests पातs */
	पूर्णांक req_पात_count;

	/* Number of lanes available (1 or 2) क्रम Rx/Tx */
	u32 lanes_per_direction;
	काष्ठा ufs_pa_layer_attr pwr_info;
	काष्ठा ufs_pwr_mode_info max_pwr_info;

	काष्ठा ufs_clk_gating clk_gating;
	/* Control to enable/disable host capabilities */
	u32 caps;

	काष्ठा devfreq *devfreq;
	काष्ठा ufs_clk_scaling clk_scaling;
	bool is_sys_suspended;

	क्रमागत bkops_status urgent_bkops_lvl;
	bool is_urgent_bkops_lvl_checked;

	काष्ठा rw_semaphore clk_scaling_lock;
	अचिन्हित अक्षर desc_size[QUERY_DESC_IDN_MAX];
	atomic_t scsi_block_reqs_cnt;

	काष्ठा device		bsg_dev;
	काष्ठा request_queue	*bsg_queue;
	काष्ठा delayed_work rpm_dev_flush_recheck_work;

#अगर_घोषित CONFIG_SCSI_UFS_CRYPTO
	जोड़ ufs_crypto_capabilities crypto_capabilities;
	जोड़ ufs_crypto_cap_entry *crypto_cap_array;
	u32 crypto_cfg_रेजिस्टर;
	काष्ठा blk_keyslot_manager ksm;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs_root;
	काष्ठा delayed_work debugfs_ee_work;
	u32 debugfs_ee_rate_limit_ms;
#पूर्ण_अगर
पूर्ण;

/* Returns true अगर घड़ीs can be gated. Otherwise false */
अटल अंतरभूत bool ufshcd_is_clkgating_allowed(काष्ठा ufs_hba *hba)
अणु
	वापस hba->caps & UFSHCD_CAP_CLK_GATING;
पूर्ण
अटल अंतरभूत bool ufshcd_can_hibern8_during_gating(काष्ठा ufs_hba *hba)
अणु
	वापस hba->caps & UFSHCD_CAP_HIBERN8_WITH_CLK_GATING;
पूर्ण
अटल अंतरभूत पूर्णांक ufshcd_is_clkscaling_supported(काष्ठा ufs_hba *hba)
अणु
	वापस hba->caps & UFSHCD_CAP_CLK_SCALING;
पूर्ण
अटल अंतरभूत bool ufshcd_can_स्वतःbkops_during_suspend(काष्ठा ufs_hba *hba)
अणु
	वापस hba->caps & UFSHCD_CAP_AUTO_BKOPS_SUSPEND;
पूर्ण
अटल अंतरभूत bool ufshcd_is_rpm_स्वतःsuspend_allowed(काष्ठा ufs_hba *hba)
अणु
	वापस hba->caps & UFSHCD_CAP_RPM_AUTOSUSPEND;
पूर्ण

अटल अंतरभूत bool ufshcd_is_पूर्णांकr_aggr_allowed(काष्ठा ufs_hba *hba)
अणु
/* DWC UFS Core has the Interrupt aggregation feature but is not detectable*/
#अगर_अघोषित CONFIG_SCSI_UFS_DWC
	अगर ((hba->caps & UFSHCD_CAP_INTR_AGGR) &&
	    !(hba->quirks & UFSHCD_QUIRK_BROKEN_INTR_AGGR))
		वापस true;
	अन्यथा
		वापस false;
#अन्यथा
वापस true;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool ufshcd_can_aggressive_pc(काष्ठा ufs_hba *hba)
अणु
	वापस !!(ufshcd_is_link_hibern8(hba) &&
		  (hba->caps & UFSHCD_CAP_AGGR_POWER_COLLAPSE));
पूर्ण

अटल अंतरभूत bool ufshcd_is_स्वतः_hibern8_supported(काष्ठा ufs_hba *hba)
अणु
	वापस (hba->capabilities & MASK_AUTO_HIBERN8_SUPPORT) &&
		!(hba->quirks & UFSHCD_QUIRK_BROKEN_AUTO_HIBERN8);
पूर्ण

अटल अंतरभूत bool ufshcd_is_स्वतः_hibern8_enabled(काष्ठा ufs_hba *hba)
अणु
	वापस FIELD_GET(UFSHCI_AHIBERN8_TIMER_MASK, hba->ahit) ? true : false;
पूर्ण

अटल अंतरभूत bool ufshcd_is_wb_allowed(काष्ठा ufs_hba *hba)
अणु
	वापस hba->caps & UFSHCD_CAP_WB_EN;
पूर्ण

अटल अंतरभूत bool ufshcd_is_user_access_allowed(काष्ठा ufs_hba *hba)
अणु
	वापस !hba->shutting_करोwn;
पूर्ण

#घोषणा ufshcd_ग_लिखोl(hba, val, reg)	\
	ग_लिखोl((val), (hba)->mmio_base + (reg))
#घोषणा ufshcd_पढ़ोl(hba, reg)	\
	पढ़ोl((hba)->mmio_base + (reg))

/**
 * ufshcd_rmwl - पढ़ो modअगरy ग_लिखो पूर्णांकo a रेजिस्टर
 * @hba - per adapter instance
 * @mask - mask to apply on पढ़ो value
 * @val - actual value to ग_लिखो
 * @reg - रेजिस्टर address
 */
अटल अंतरभूत व्योम ufshcd_rmwl(काष्ठा ufs_hba *hba, u32 mask, u32 val, u32 reg)
अणु
	u32 पंचांगp;

	पंचांगp = ufshcd_पढ़ोl(hba, reg);
	पंचांगp &= ~mask;
	पंचांगp |= (val & mask);
	ufshcd_ग_लिखोl(hba, पंचांगp, reg);
पूर्ण

पूर्णांक ufshcd_alloc_host(काष्ठा device *, काष्ठा ufs_hba **);
व्योम ufshcd_dealloc_host(काष्ठा ufs_hba *);
पूर्णांक ufshcd_hba_enable(काष्ठा ufs_hba *hba);
पूर्णांक ufshcd_init(काष्ठा ufs_hba * , व्योम __iomem * , अचिन्हित पूर्णांक);
पूर्णांक ufshcd_link_recovery(काष्ठा ufs_hba *hba);
पूर्णांक ufshcd_make_hba_operational(काष्ठा ufs_hba *hba);
व्योम ufshcd_हटाओ(काष्ठा ufs_hba *);
पूर्णांक ufshcd_uic_hibern8_निकास(काष्ठा ufs_hba *hba);
व्योम ufshcd_delay_us(अचिन्हित दीर्घ us, अचिन्हित दीर्घ tolerance);
पूर्णांक ufshcd_रुको_क्रम_रेजिस्टर(काष्ठा ufs_hba *hba, u32 reg, u32 mask,
				u32 val, अचिन्हित दीर्घ पूर्णांकerval_us,
				अचिन्हित दीर्घ समयout_ms);
व्योम ufshcd_parse_dev_ref_clk_freq(काष्ठा ufs_hba *hba, काष्ठा clk *refclk);
व्योम ufshcd_update_evt_hist(काष्ठा ufs_hba *hba, u32 id, u32 val);

अटल अंतरभूत व्योम check_upiu_size(व्योम)
अणु
	BUILD_BUG_ON(ALIGNED_UPIU_SIZE <
		GENERAL_UPIU_REQUEST_SIZE + QUERY_DESC_MAX_SIZE);
पूर्ण

/**
 * ufshcd_set_variant - set variant specअगरic data to the hba
 * @hba - per adapter instance
 * @variant - poपूर्णांकer to variant specअगरic data
 */
अटल अंतरभूत व्योम ufshcd_set_variant(काष्ठा ufs_hba *hba, व्योम *variant)
अणु
	BUG_ON(!hba);
	hba->priv = variant;
पूर्ण

/**
 * ufshcd_get_variant - get variant specअगरic data from the hba
 * @hba - per adapter instance
 */
अटल अंतरभूत व्योम *ufshcd_get_variant(काष्ठा ufs_hba *hba)
अणु
	BUG_ON(!hba);
	वापस hba->priv;
पूर्ण
अटल अंतरभूत bool ufshcd_keep_स्वतःbkops_enabled_except_suspend(
							काष्ठा ufs_hba *hba)
अणु
	वापस hba->caps & UFSHCD_CAP_KEEP_AUTO_BKOPS_ENABLED_EXCEPT_SUSPEND;
पूर्ण

अटल अंतरभूत u8 ufshcd_wb_get_query_index(काष्ठा ufs_hba *hba)
अणु
	अगर (hba->dev_info.wb_buffer_type == WB_BUF_MODE_LU_DEDICATED)
		वापस hba->dev_info.wb_dedicated_lu;
	वापस 0;
पूर्ण

बाह्य पूर्णांक ufshcd_runसमय_suspend(काष्ठा ufs_hba *hba);
बाह्य पूर्णांक ufshcd_runसमय_resume(काष्ठा ufs_hba *hba);
बाह्य पूर्णांक ufshcd_runसमय_idle(काष्ठा ufs_hba *hba);
बाह्य पूर्णांक ufshcd_प्रणाली_suspend(काष्ठा ufs_hba *hba);
बाह्य पूर्णांक ufshcd_प्रणाली_resume(काष्ठा ufs_hba *hba);
बाह्य पूर्णांक ufshcd_shutकरोwn(काष्ठा ufs_hba *hba);
बाह्य पूर्णांक ufshcd_dme_configure_adapt(काष्ठा ufs_hba *hba,
				      पूर्णांक agreed_gear,
				      पूर्णांक adapt_val);
बाह्य पूर्णांक ufshcd_dme_set_attr(काष्ठा ufs_hba *hba, u32 attr_sel,
			       u8 attr_set, u32 mib_val, u8 peer);
बाह्य पूर्णांक ufshcd_dme_get_attr(काष्ठा ufs_hba *hba, u32 attr_sel,
			       u32 *mib_val, u8 peer);
बाह्य पूर्णांक ufshcd_config_pwr_mode(काष्ठा ufs_hba *hba,
			काष्ठा ufs_pa_layer_attr *desired_pwr_mode);

/* UIC command पूर्णांकerfaces क्रम DME primitives */
#घोषणा DME_LOCAL	0
#घोषणा DME_PEER	1
#घोषणा ATTR_SET_NOR	0	/* NORMAL */
#घोषणा ATTR_SET_ST	1	/* STATIC */

अटल अंतरभूत पूर्णांक ufshcd_dme_set(काष्ठा ufs_hba *hba, u32 attr_sel,
				 u32 mib_val)
अणु
	वापस ufshcd_dme_set_attr(hba, attr_sel, ATTR_SET_NOR,
				   mib_val, DME_LOCAL);
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_dme_st_set(काष्ठा ufs_hba *hba, u32 attr_sel,
				    u32 mib_val)
अणु
	वापस ufshcd_dme_set_attr(hba, attr_sel, ATTR_SET_ST,
				   mib_val, DME_LOCAL);
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_dme_peer_set(काष्ठा ufs_hba *hba, u32 attr_sel,
				      u32 mib_val)
अणु
	वापस ufshcd_dme_set_attr(hba, attr_sel, ATTR_SET_NOR,
				   mib_val, DME_PEER);
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_dme_peer_st_set(काष्ठा ufs_hba *hba, u32 attr_sel,
					 u32 mib_val)
अणु
	वापस ufshcd_dme_set_attr(hba, attr_sel, ATTR_SET_ST,
				   mib_val, DME_PEER);
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_dme_get(काष्ठा ufs_hba *hba,
				 u32 attr_sel, u32 *mib_val)
अणु
	वापस ufshcd_dme_get_attr(hba, attr_sel, mib_val, DME_LOCAL);
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_dme_peer_get(काष्ठा ufs_hba *hba,
				      u32 attr_sel, u32 *mib_val)
अणु
	वापस ufshcd_dme_get_attr(hba, attr_sel, mib_val, DME_PEER);
पूर्ण

अटल अंतरभूत bool ufshcd_is_hs_mode(काष्ठा ufs_pa_layer_attr *pwr_info)
अणु
	वापस (pwr_info->pwr_rx == FAST_MODE ||
		pwr_info->pwr_rx == FASTAUTO_MODE) &&
		(pwr_info->pwr_tx == FAST_MODE ||
		pwr_info->pwr_tx == FASTAUTO_MODE);
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_disable_host_tx_lcc(काष्ठा ufs_hba *hba)
अणु
	वापस ufshcd_dme_set(hba, UIC_ARG_MIB(PA_LOCAL_TX_LCC_ENABLE), 0);
पूर्ण

/* Expose Query-Request API */
पूर्णांक ufshcd_query_descriptor_retry(काष्ठा ufs_hba *hba,
				  क्रमागत query_opcode opcode,
				  क्रमागत desc_idn idn, u8 index,
				  u8 selector,
				  u8 *desc_buf, पूर्णांक *buf_len);
पूर्णांक ufshcd_पढ़ो_desc_param(काष्ठा ufs_hba *hba,
			   क्रमागत desc_idn desc_id,
			   पूर्णांक desc_index,
			   u8 param_offset,
			   u8 *param_पढ़ो_buf,
			   u8 param_size);
पूर्णांक ufshcd_query_attr(काष्ठा ufs_hba *hba, क्रमागत query_opcode opcode,
		      क्रमागत attr_idn idn, u8 index, u8 selector, u32 *attr_val);
पूर्णांक ufshcd_query_flag(काष्ठा ufs_hba *hba, क्रमागत query_opcode opcode,
	क्रमागत flag_idn idn, u8 index, bool *flag_res);

व्योम ufshcd_स्वतः_hibern8_enable(काष्ठा ufs_hba *hba);
व्योम ufshcd_स्वतः_hibern8_update(काष्ठा ufs_hba *hba, u32 ahit);
व्योम ufshcd_fixup_dev_quirks(काष्ठा ufs_hba *hba, काष्ठा ufs_dev_fix *fixups);
#घोषणा SD_ASCII_STD true
#घोषणा SD_RAW false
पूर्णांक ufshcd_पढ़ो_string_desc(काष्ठा ufs_hba *hba, u8 desc_index,
			    u8 **buf, bool ascii);

पूर्णांक ufshcd_hold(काष्ठा ufs_hba *hba, bool async);
व्योम ufshcd_release(काष्ठा ufs_hba *hba);

व्योम ufshcd_map_desc_id_to_length(काष्ठा ufs_hba *hba, क्रमागत desc_idn desc_id,
				  पूर्णांक *desc_length);

u32 ufshcd_get_local_unipro_ver(काष्ठा ufs_hba *hba);

पूर्णांक ufshcd_send_uic_cmd(काष्ठा ufs_hba *hba, काष्ठा uic_command *uic_cmd);

पूर्णांक ufshcd_exec_raw_upiu_cmd(काष्ठा ufs_hba *hba,
			     काष्ठा utp_upiu_req *req_upiu,
			     काष्ठा utp_upiu_req *rsp_upiu,
			     पूर्णांक msgcode,
			     u8 *desc_buff, पूर्णांक *buff_len,
			     क्रमागत query_opcode desc_op);

पूर्णांक ufshcd_wb_toggle(काष्ठा ufs_hba *hba, bool enable);

/* Wrapper functions क्रम safely calling variant operations */
अटल अंतरभूत स्थिर अक्षर *ufshcd_get_var_name(काष्ठा ufs_hba *hba)
अणु
	अगर (hba->vops)
		वापस hba->vops->name;
	वापस "";
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_vops_init(काष्ठा ufs_hba *hba)
अणु
	अगर (hba->vops && hba->vops->init)
		वापस hba->vops->init(hba);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ufshcd_vops_निकास(काष्ठा ufs_hba *hba)
अणु
	अगर (hba->vops && hba->vops->निकास)
		वापस hba->vops->निकास(hba);
पूर्ण

अटल अंतरभूत u32 ufshcd_vops_get_ufs_hci_version(काष्ठा ufs_hba *hba)
अणु
	अगर (hba->vops && hba->vops->get_ufs_hci_version)
		वापस hba->vops->get_ufs_hci_version(hba);

	वापस ufshcd_पढ़ोl(hba, REG_UFS_VERSION);
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_vops_clk_scale_notअगरy(काष्ठा ufs_hba *hba,
			bool up, क्रमागत ufs_notअगरy_change_status status)
अणु
	अगर (hba->vops && hba->vops->clk_scale_notअगरy)
		वापस hba->vops->clk_scale_notअगरy(hba, up, status);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ufshcd_vops_event_notअगरy(काष्ठा ufs_hba *hba,
					    क्रमागत ufs_event_type evt,
					    व्योम *data)
अणु
	अगर (hba->vops && hba->vops->event_notअगरy)
		hba->vops->event_notअगरy(hba, evt, data);
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_vops_setup_घड़ीs(काष्ठा ufs_hba *hba, bool on,
					क्रमागत ufs_notअगरy_change_status status)
अणु
	अगर (hba->vops && hba->vops->setup_घड़ीs)
		वापस hba->vops->setup_घड़ीs(hba, on, status);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_vops_hce_enable_notअगरy(काष्ठा ufs_hba *hba,
						bool status)
अणु
	अगर (hba->vops && hba->vops->hce_enable_notअगरy)
		वापस hba->vops->hce_enable_notअगरy(hba, status);

	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक ufshcd_vops_link_startup_notअगरy(काष्ठा ufs_hba *hba,
						bool status)
अणु
	अगर (hba->vops && hba->vops->link_startup_notअगरy)
		वापस hba->vops->link_startup_notअगरy(hba, status);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_vops_phy_initialization(काष्ठा ufs_hba *hba)
अणु
	अगर (hba->vops && hba->vops->phy_initialization)
		वापस hba->vops->phy_initialization(hba);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_vops_pwr_change_notअगरy(काष्ठा ufs_hba *hba,
				  क्रमागत ufs_notअगरy_change_status status,
				  काष्ठा ufs_pa_layer_attr *dev_max_params,
				  काष्ठा ufs_pa_layer_attr *dev_req_params)
अणु
	अगर (hba->vops && hba->vops->pwr_change_notअगरy)
		वापस hba->vops->pwr_change_notअगरy(hba, status,
					dev_max_params, dev_req_params);

	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत व्योम ufshcd_vops_setup_xfer_req(काष्ठा ufs_hba *hba, पूर्णांक tag,
					bool is_scsi_cmd)
अणु
	अगर (hba->vops && hba->vops->setup_xfer_req)
		वापस hba->vops->setup_xfer_req(hba, tag, is_scsi_cmd);
पूर्ण

अटल अंतरभूत व्योम ufshcd_vops_setup_task_mgmt(काष्ठा ufs_hba *hba,
					पूर्णांक tag, u8 पंचांग_function)
अणु
	अगर (hba->vops && hba->vops->setup_task_mgmt)
		वापस hba->vops->setup_task_mgmt(hba, tag, पंचांग_function);
पूर्ण

अटल अंतरभूत व्योम ufshcd_vops_hibern8_notअगरy(काष्ठा ufs_hba *hba,
					क्रमागत uic_cmd_dme cmd,
					क्रमागत ufs_notअगरy_change_status status)
अणु
	अगर (hba->vops && hba->vops->hibern8_notअगरy)
		वापस hba->vops->hibern8_notअगरy(hba, cmd, status);
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_vops_apply_dev_quirks(काष्ठा ufs_hba *hba)
अणु
	अगर (hba->vops && hba->vops->apply_dev_quirks)
		वापस hba->vops->apply_dev_quirks(hba);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ufshcd_vops_fixup_dev_quirks(काष्ठा ufs_hba *hba)
अणु
	अगर (hba->vops && hba->vops->fixup_dev_quirks)
		hba->vops->fixup_dev_quirks(hba);
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_vops_suspend(काष्ठा ufs_hba *hba, क्रमागत ufs_pm_op op)
अणु
	अगर (hba->vops && hba->vops->suspend)
		वापस hba->vops->suspend(hba, op);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_vops_resume(काष्ठा ufs_hba *hba, क्रमागत ufs_pm_op op)
अणु
	अगर (hba->vops && hba->vops->resume)
		वापस hba->vops->resume(hba, op);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ufshcd_vops_dbg_रेजिस्टर_dump(काष्ठा ufs_hba *hba)
अणु
	अगर (hba->vops && hba->vops->dbg_रेजिस्टर_dump)
		hba->vops->dbg_रेजिस्टर_dump(hba);
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_vops_device_reset(काष्ठा ufs_hba *hba)
अणु
	अगर (hba->vops && hba->vops->device_reset)
		वापस hba->vops->device_reset(hba);

	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम ufshcd_vops_config_scaling_param(काष्ठा ufs_hba *hba,
						    काष्ठा devfreq_dev_profile
						    *profile, व्योम *data)
अणु
	अगर (hba->vops && hba->vops->config_scaling_param)
		hba->vops->config_scaling_param(hba, profile, data);
पूर्ण

बाह्य काष्ठा ufs_pm_lvl_states ufs_pm_lvl_states[];

/*
 * ufshcd_scsi_to_upiu_lun - maps scsi LUN to UPIU LUN
 * @scsi_lun: scsi LUN id
 *
 * Returns UPIU LUN id
 */
अटल अंतरभूत u8 ufshcd_scsi_to_upiu_lun(अचिन्हित पूर्णांक scsi_lun)
अणु
	अगर (scsi_is_wlun(scsi_lun))
		वापस (scsi_lun & UFS_UPIU_MAX_UNIT_NUM_ID)
			| UFS_UPIU_WLUN_ID;
	अन्यथा
		वापस scsi_lun & UFS_UPIU_MAX_UNIT_NUM_ID;
पूर्ण

पूर्णांक ufshcd_dump_regs(काष्ठा ufs_hba *hba, माप_प्रकार offset, माप_प्रकार len,
		     स्थिर अक्षर *prefix);

पूर्णांक __ufshcd_ग_लिखो_ee_control(काष्ठा ufs_hba *hba, u32 ee_ctrl_mask);
पूर्णांक ufshcd_ग_लिखो_ee_control(काष्ठा ufs_hba *hba);
पूर्णांक ufshcd_update_ee_control(काष्ठा ufs_hba *hba, u16 *mask, u16 *other_mask,
			     u16 set, u16 clr);

अटल अंतरभूत पूर्णांक ufshcd_update_ee_drv_mask(काष्ठा ufs_hba *hba,
					    u16 set, u16 clr)
अणु
	वापस ufshcd_update_ee_control(hba, &hba->ee_drv_mask,
					&hba->ee_usr_mask, set, clr);
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_update_ee_usr_mask(काष्ठा ufs_hba *hba,
					    u16 set, u16 clr)
अणु
	वापस ufshcd_update_ee_control(hba, &hba->ee_usr_mask,
					&hba->ee_drv_mask, set, clr);
पूर्ण

#पूर्ण_अगर /* End of Header */
