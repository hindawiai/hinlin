<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Universal Flash Storage Host controller driver Core
 * Copyright (C) 2011-2013 Samsung India Software Operations
 * Copyright (c) 2013-2016, The Linux Foundation. All rights reserved.
 *
 * Authors:
 *	Santosh Yaraganavi <santosh.sy@samsung.com>
 *	Vinayak Holikatti <h.vinayak@samsung.com>
 */

#समावेश <linux/async.h>
#समावेश <linux/devfreq.h>
#समावेश <linux/nls.h>
#समावेश <linux/of.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/blk-pm.h>
#समावेश <linux/blkdev.h>
#समावेश "ufshcd.h"
#समावेश "ufs_quirks.h"
#समावेश "unipro.h"
#समावेश "ufs-sysfs.h"
#समावेश "ufs-debugfs.h"
#समावेश "ufs_bsg.h"
#समावेश "ufshcd-crypto.h"
#समावेश <यंत्र/unaligned.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/ufs.h>

#घोषणा UFSHCD_ENABLE_INTRS	(UTP_TRANSFER_REQ_COMPL |\
				 UTP_TASK_REQ_COMPL |\
				 UFSHCD_ERROR_MASK)
/* UIC command समयout, unit: ms */
#घोषणा UIC_CMD_TIMEOUT	500

/* NOP OUT retries रुकोing क्रम NOP IN response */
#घोषणा NOP_OUT_RETRIES    10
/* Timeout after 50 msecs अगर NOP OUT hangs without response */
#घोषणा NOP_OUT_TIMEOUT    50 /* msecs */

/* Query request retries */
#घोषणा QUERY_REQ_RETRIES 3
/* Query request समयout */
#घोषणा QUERY_REQ_TIMEOUT 1500 /* 1.5 seconds */

/* Task management command समयout */
#घोषणा TM_CMD_TIMEOUT	100 /* msecs */

/* maximum number of retries क्रम a general UIC command  */
#घोषणा UFS_UIC_COMMAND_RETRIES 3

/* maximum number of link-startup retries */
#घोषणा DME_LINKSTARTUP_RETRIES 3

/* Maximum retries क्रम Hibern8 enter */
#घोषणा UIC_HIBERN8_ENTER_RETRIES 3

/* maximum number of reset retries beक्रमe giving up */
#घोषणा MAX_HOST_RESET_RETRIES 5

/* Expose the flag value from utp_upiu_query.value */
#घोषणा MASK_QUERY_UPIU_FLAG_LOC 0xFF

/* Interrupt aggregation शेष समयout, unit: 40us */
#घोषणा INT_AGGR_DEF_TO	0x02

/* शेष delay of स्वतःsuspend: 2000 ms */
#घोषणा RPM_AUTOSUSPEND_DELAY_MS 2000

/* Default delay of RPM device flush delayed work */
#घोषणा RPM_DEV_FLUSH_RECHECK_WORK_DELAY_MS 5000

/* Default value of रुको समय beक्रमe gating device ref घड़ी */
#घोषणा UFSHCD_REF_CLK_GATING_WAIT_US 0xFF /* microsecs */

/* Polling समय to रुको क्रम fDeviceInit */
#घोषणा FDEVICEINIT_COMPL_TIMEOUT 1500 /* millisecs */

#घोषणा ufshcd_toggle_vreg(_dev, _vreg, _on)				\
	(अणु                                                              \
		पूर्णांक _ret;                                               \
		अगर (_on)                                                \
			_ret = ufshcd_enable_vreg(_dev, _vreg);         \
		अन्यथा                                                    \
			_ret = ufshcd_disable_vreg(_dev, _vreg);        \
		_ret;                                                   \
	पूर्ण)

#घोषणा ufshcd_hex_dump(prefix_str, buf, len) करो अणु                       \
	माप_प्रकार __len = (len);                                            \
	prपूर्णांक_hex_dump(KERN_ERR, prefix_str,                             \
		       __len > 4 ? DUMP_PREFIX_OFFSET : DUMP_PREFIX_NONE,\
		       16, 4, buf, __len, false);                        \
पूर्ण जबतक (0)

पूर्णांक ufshcd_dump_regs(काष्ठा ufs_hba *hba, माप_प्रकार offset, माप_प्रकार len,
		     स्थिर अक्षर *prefix)
अणु
	u32 *regs;
	माप_प्रकार pos;

	अगर (offset % 4 != 0 || len % 4 != 0) /* keep पढ़ोl happy */
		वापस -EINVAL;

	regs = kzalloc(len, GFP_ATOMIC);
	अगर (!regs)
		वापस -ENOMEM;

	क्रम (pos = 0; pos < len; pos += 4)
		regs[pos / 4] = ufshcd_पढ़ोl(hba, offset + pos);

	ufshcd_hex_dump(prefix, regs, len);
	kमुक्त(regs);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_dump_regs);

क्रमागत अणु
	UFSHCD_MAX_CHANNEL	= 0,
	UFSHCD_MAX_ID		= 1,
	UFSHCD_CMD_PER_LUN	= 32,
	UFSHCD_CAN_QUEUE	= 32,
पूर्ण;

/* UFSHCD states */
क्रमागत अणु
	UFSHCD_STATE_RESET,
	UFSHCD_STATE_ERROR,
	UFSHCD_STATE_OPERATIONAL,
	UFSHCD_STATE_EH_SCHEDULED_FATAL,
	UFSHCD_STATE_EH_SCHEDULED_NON_FATAL,
पूर्ण;

/* UFSHCD error handling flags */
क्रमागत अणु
	UFSHCD_EH_IN_PROGRESS = (1 << 0),
पूर्ण;

/* UFSHCD UIC layer error flags */
क्रमागत अणु
	UFSHCD_UIC_DL_PA_INIT_ERROR = (1 << 0), /* Data link layer error */
	UFSHCD_UIC_DL_NAC_RECEIVED_ERROR = (1 << 1), /* Data link layer error */
	UFSHCD_UIC_DL_TCx_REPLAY_ERROR = (1 << 2), /* Data link layer error */
	UFSHCD_UIC_NL_ERROR = (1 << 3), /* Network layer error */
	UFSHCD_UIC_TL_ERROR = (1 << 4), /* Transport Layer error */
	UFSHCD_UIC_DME_ERROR = (1 << 5), /* DME error */
	UFSHCD_UIC_PA_GENERIC_ERROR = (1 << 6), /* Generic PA error */
पूर्ण;

#घोषणा ufshcd_set_eh_in_progress(h) \
	((h)->eh_flags |= UFSHCD_EH_IN_PROGRESS)
#घोषणा ufshcd_eh_in_progress(h) \
	((h)->eh_flags & UFSHCD_EH_IN_PROGRESS)
#घोषणा ufshcd_clear_eh_in_progress(h) \
	((h)->eh_flags &= ~UFSHCD_EH_IN_PROGRESS)

काष्ठा ufs_pm_lvl_states ufs_pm_lvl_states[] = अणु
	अणुUFS_ACTIVE_PWR_MODE, UIC_LINK_ACTIVE_STATEपूर्ण,
	अणुUFS_ACTIVE_PWR_MODE, UIC_LINK_HIBERN8_STATEपूर्ण,
	अणुUFS_SLEEP_PWR_MODE, UIC_LINK_ACTIVE_STATEपूर्ण,
	अणुUFS_SLEEP_PWR_MODE, UIC_LINK_HIBERN8_STATEपूर्ण,
	अणुUFS_POWERDOWN_PWR_MODE, UIC_LINK_HIBERN8_STATEपूर्ण,
	अणुUFS_POWERDOWN_PWR_MODE, UIC_LINK_OFF_STATEपूर्ण,
	/*
	 * For DeepSleep, the link is first put in hibern8 and then off.
	 * Leaving the link in hibern8 is not supported.
	 */
	अणुUFS_DEEPSLEEP_PWR_MODE, UIC_LINK_OFF_STATEपूर्ण,
पूर्ण;

अटल अंतरभूत क्रमागत ufs_dev_pwr_mode
ufs_get_pm_lvl_to_dev_pwr_mode(क्रमागत ufs_pm_level lvl)
अणु
	वापस ufs_pm_lvl_states[lvl].dev_state;
पूर्ण

अटल अंतरभूत क्रमागत uic_link_state
ufs_get_pm_lvl_to_link_pwr_state(क्रमागत ufs_pm_level lvl)
अणु
	वापस ufs_pm_lvl_states[lvl].link_state;
पूर्ण

अटल अंतरभूत क्रमागत ufs_pm_level
ufs_get_desired_pm_lvl_क्रम_dev_link_state(क्रमागत ufs_dev_pwr_mode dev_state,
					क्रमागत uic_link_state link_state)
अणु
	क्रमागत ufs_pm_level lvl;

	क्रम (lvl = UFS_PM_LVL_0; lvl < UFS_PM_LVL_MAX; lvl++) अणु
		अगर ((ufs_pm_lvl_states[lvl].dev_state == dev_state) &&
			(ufs_pm_lvl_states[lvl].link_state == link_state))
			वापस lvl;
	पूर्ण

	/* अगर no match found, वापस the level 0 */
	वापस UFS_PM_LVL_0;
पूर्ण

अटल काष्ठा ufs_dev_fix ufs_fixups[] = अणु
	/* UFS cards deviations table */
	UFS_FIX(UFS_VENDOR_MICRON, UFS_ANY_MODEL,
		UFS_DEVICE_QUIRK_DELAY_BEFORE_LPM),
	UFS_FIX(UFS_VENDOR_SAMSUNG, UFS_ANY_MODEL,
		UFS_DEVICE_QUIRK_DELAY_BEFORE_LPM |
		UFS_DEVICE_QUIRK_HOST_PA_TACTIVATE |
		UFS_DEVICE_QUIRK_RECOVERY_FROM_DL_NAC_ERRORS),
	UFS_FIX(UFS_VENDOR_SKHYNIX, UFS_ANY_MODEL,
		UFS_DEVICE_QUIRK_HOST_PA_SAVECONFIGTIME),
	UFS_FIX(UFS_VENDOR_SKHYNIX, "hB8aL1" /*H28U62301AMR*/,
		UFS_DEVICE_QUIRK_HOST_VS_DEBUGSAVECONFIGTIME),
	UFS_FIX(UFS_VENDOR_TOSHIBA, UFS_ANY_MODEL,
		UFS_DEVICE_QUIRK_DELAY_BEFORE_LPM),
	UFS_FIX(UFS_VENDOR_TOSHIBA, "THGLF2G9C8KBADG",
		UFS_DEVICE_QUIRK_PA_TACTIVATE),
	UFS_FIX(UFS_VENDOR_TOSHIBA, "THGLF2G9D8KBADG",
		UFS_DEVICE_QUIRK_PA_TACTIVATE),
	END_FIX
पूर्ण;

अटल irqवापस_t ufshcd_पंचांगc_handler(काष्ठा ufs_hba *hba);
अटल व्योम ufshcd_async_scan(व्योम *data, async_cookie_t cookie);
अटल पूर्णांक ufshcd_reset_and_restore(काष्ठा ufs_hba *hba);
अटल पूर्णांक ufshcd_eh_host_reset_handler(काष्ठा scsi_cmnd *cmd);
अटल पूर्णांक ufshcd_clear_पंचांग_cmd(काष्ठा ufs_hba *hba, पूर्णांक tag);
अटल व्योम ufshcd_hba_निकास(काष्ठा ufs_hba *hba);
अटल पूर्णांक ufshcd_clear_ua_wluns(काष्ठा ufs_hba *hba);
अटल पूर्णांक ufshcd_probe_hba(काष्ठा ufs_hba *hba, bool async);
अटल पूर्णांक ufshcd_setup_घड़ीs(काष्ठा ufs_hba *hba, bool on);
अटल पूर्णांक ufshcd_uic_hibern8_enter(काष्ठा ufs_hba *hba);
अटल अंतरभूत व्योम ufshcd_add_delay_beक्रमe_dme_cmd(काष्ठा ufs_hba *hba);
अटल पूर्णांक ufshcd_host_reset_and_restore(काष्ठा ufs_hba *hba);
अटल व्योम ufshcd_resume_clkscaling(काष्ठा ufs_hba *hba);
अटल व्योम ufshcd_suspend_clkscaling(काष्ठा ufs_hba *hba);
अटल व्योम __ufshcd_suspend_clkscaling(काष्ठा ufs_hba *hba);
अटल पूर्णांक ufshcd_scale_clks(काष्ठा ufs_hba *hba, bool scale_up);
अटल irqवापस_t ufshcd_पूर्णांकr(पूर्णांक irq, व्योम *__hba);
अटल पूर्णांक ufshcd_change_घातer_mode(काष्ठा ufs_hba *hba,
			     काष्ठा ufs_pa_layer_attr *pwr_mode);
अटल व्योम ufshcd_schedule_eh_work(काष्ठा ufs_hba *hba);
अटल पूर्णांक ufshcd_setup_hba_vreg(काष्ठा ufs_hba *hba, bool on);
अटल पूर्णांक ufshcd_setup_vreg(काष्ठा ufs_hba *hba, bool on);
अटल अंतरभूत पूर्णांक ufshcd_config_vreg_hpm(काष्ठा ufs_hba *hba,
					 काष्ठा ufs_vreg *vreg);
अटल पूर्णांक ufshcd_try_to_पात_task(काष्ठा ufs_hba *hba, पूर्णांक tag);
अटल व्योम ufshcd_wb_toggle_flush_during_h8(काष्ठा ufs_hba *hba, bool set);
अटल अंतरभूत व्योम ufshcd_wb_toggle_flush(काष्ठा ufs_hba *hba, bool enable);
अटल व्योम ufshcd_hba_vreg_set_lpm(काष्ठा ufs_hba *hba);
अटल व्योम ufshcd_hba_vreg_set_hpm(काष्ठा ufs_hba *hba);

अटल अंतरभूत bool ufshcd_valid_tag(काष्ठा ufs_hba *hba, पूर्णांक tag)
अणु
	वापस tag >= 0 && tag < hba->nutrs;
पूर्ण

अटल अंतरभूत व्योम ufshcd_enable_irq(काष्ठा ufs_hba *hba)
अणु
	अगर (!hba->is_irq_enabled) अणु
		enable_irq(hba->irq);
		hba->is_irq_enabled = true;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ufshcd_disable_irq(काष्ठा ufs_hba *hba)
अणु
	अगर (hba->is_irq_enabled) अणु
		disable_irq(hba->irq);
		hba->is_irq_enabled = false;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ufshcd_wb_config(काष्ठा ufs_hba *hba)
अणु
	अगर (!ufshcd_is_wb_allowed(hba))
		वापस;

	ufshcd_wb_toggle(hba, true);

	ufshcd_wb_toggle_flush_during_h8(hba, true);
	अगर (!(hba->quirks & UFSHCI_QUIRK_SKIP_MANUAL_WB_FLUSH_CTRL))
		ufshcd_wb_toggle_flush(hba, true);
पूर्ण

अटल व्योम ufshcd_scsi_unblock_requests(काष्ठा ufs_hba *hba)
अणु
	अगर (atomic_dec_and_test(&hba->scsi_block_reqs_cnt))
		scsi_unblock_requests(hba->host);
पूर्ण

अटल व्योम ufshcd_scsi_block_requests(काष्ठा ufs_hba *hba)
अणु
	अगर (atomic_inc_वापस(&hba->scsi_block_reqs_cnt) == 1)
		scsi_block_requests(hba->host);
पूर्ण

अटल व्योम ufshcd_add_cmd_upiu_trace(काष्ठा ufs_hba *hba, अचिन्हित पूर्णांक tag,
				      क्रमागत ufs_trace_str_t str_t)
अणु
	काष्ठा utp_upiu_req *rq = hba->lrb[tag].ucd_req_ptr;

	अगर (!trace_ufshcd_upiu_enabled())
		वापस;

	trace_ufshcd_upiu(dev_name(hba->dev), str_t, &rq->header, &rq->sc.cdb,
			  UFS_TSF_CDB);
पूर्ण

अटल व्योम ufshcd_add_query_upiu_trace(काष्ठा ufs_hba *hba,
					क्रमागत ufs_trace_str_t str_t,
					काष्ठा utp_upiu_req *rq_rsp)
अणु
	अगर (!trace_ufshcd_upiu_enabled())
		वापस;

	trace_ufshcd_upiu(dev_name(hba->dev), str_t, &rq_rsp->header,
			  &rq_rsp->qr, UFS_TSF_OSF);
पूर्ण

अटल व्योम ufshcd_add_पंचांग_upiu_trace(काष्ठा ufs_hba *hba, अचिन्हित पूर्णांक tag,
				     क्रमागत ufs_trace_str_t str_t)
अणु
	पूर्णांक off = (पूर्णांक)tag - hba->nutrs;
	काष्ठा utp_task_req_desc *descp = &hba->uपंचांगrdl_base_addr[off];

	अगर (!trace_ufshcd_upiu_enabled())
		वापस;

	अगर (str_t == UFS_TM_SEND)
		trace_ufshcd_upiu(dev_name(hba->dev), str_t,
				  &descp->upiu_req.req_header,
				  &descp->upiu_req.input_param1,
				  UFS_TSF_TM_INPUT);
	अन्यथा
		trace_ufshcd_upiu(dev_name(hba->dev), str_t,
				  &descp->upiu_rsp.rsp_header,
				  &descp->upiu_rsp.output_param1,
				  UFS_TSF_TM_OUTPUT);
पूर्ण

अटल व्योम ufshcd_add_uic_command_trace(काष्ठा ufs_hba *hba,
					 काष्ठा uic_command *ucmd,
					 क्रमागत ufs_trace_str_t str_t)
अणु
	u32 cmd;

	अगर (!trace_ufshcd_uic_command_enabled())
		वापस;

	अगर (str_t == UFS_CMD_SEND)
		cmd = ucmd->command;
	अन्यथा
		cmd = ufshcd_पढ़ोl(hba, REG_UIC_COMMAND);

	trace_ufshcd_uic_command(dev_name(hba->dev), str_t, cmd,
				 ufshcd_पढ़ोl(hba, REG_UIC_COMMAND_ARG_1),
				 ufshcd_पढ़ोl(hba, REG_UIC_COMMAND_ARG_2),
				 ufshcd_पढ़ोl(hba, REG_UIC_COMMAND_ARG_3));
पूर्ण

अटल व्योम ufshcd_add_command_trace(काष्ठा ufs_hba *hba, अचिन्हित पूर्णांक tag,
				     क्रमागत ufs_trace_str_t str_t)
अणु
	sector_t lba = -1;
	u8 opcode = 0, group_id = 0;
	u32 पूर्णांकr, करोorbell;
	काष्ठा ufshcd_lrb *lrbp = &hba->lrb[tag];
	काष्ठा scsi_cmnd *cmd = lrbp->cmd;
	पूर्णांक transfer_len = -1;

	अगर (!trace_ufshcd_command_enabled()) अणु
		/* trace UPIU W/O tracing command */
		अगर (cmd)
			ufshcd_add_cmd_upiu_trace(hba, tag, str_t);
		वापस;
	पूर्ण

	अगर (cmd) अणु /* data phase exists */
		/* trace UPIU also */
		ufshcd_add_cmd_upiu_trace(hba, tag, str_t);
		opcode = cmd->cmnd[0];
		अगर ((opcode == READ_10) || (opcode == WRITE_10)) अणु
			/*
			 * Currently we only fully trace पढ़ो(10) and ग_लिखो(10)
			 * commands
			 */
			अगर (cmd->request && cmd->request->bio)
				lba = cmd->request->bio->bi_iter.bi_sector;
			transfer_len = be32_to_cpu(
				lrbp->ucd_req_ptr->sc.exp_data_transfer_len);
			अगर (opcode == WRITE_10)
				group_id = lrbp->cmd->cmnd[6];
		पूर्ण अन्यथा अगर (opcode == UNMAP) अणु
			अगर (cmd->request) अणु
				lba = scsi_get_lba(cmd);
				transfer_len = blk_rq_bytes(cmd->request);
			पूर्ण
		पूर्ण
	पूर्ण

	पूर्णांकr = ufshcd_पढ़ोl(hba, REG_INTERRUPT_STATUS);
	करोorbell = ufshcd_पढ़ोl(hba, REG_UTP_TRANSFER_REQ_DOOR_BELL);
	trace_ufshcd_command(dev_name(hba->dev), str_t, tag,
			करोorbell, transfer_len, पूर्णांकr, lba, opcode, group_id);
पूर्ण

अटल व्योम ufshcd_prपूर्णांक_clk_freqs(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_clk_info *clki;
	काष्ठा list_head *head = &hba->clk_list_head;

	अगर (list_empty(head))
		वापस;

	list_क्रम_each_entry(clki, head, list) अणु
		अगर (!IS_ERR_OR_शून्य(clki->clk) && clki->min_freq &&
				clki->max_freq)
			dev_err(hba->dev, "clk: %s, rate: %u\n",
					clki->name, clki->curr_freq);
	पूर्ण
पूर्ण

अटल व्योम ufshcd_prपूर्णांक_evt(काष्ठा ufs_hba *hba, u32 id,
			     अक्षर *err_name)
अणु
	पूर्णांक i;
	bool found = false;
	काष्ठा ufs_event_hist *e;

	अगर (id >= UFS_EVT_CNT)
		वापस;

	e = &hba->ufs_stats.event[id];

	क्रम (i = 0; i < UFS_EVENT_HIST_LENGTH; i++) अणु
		पूर्णांक p = (i + e->pos) % UFS_EVENT_HIST_LENGTH;

		अगर (e->tstamp[p] == 0)
			जारी;
		dev_err(hba->dev, "%s[%d] = 0x%x at %lld us\n", err_name, p,
			e->val[p], kसमय_प्रकारo_us(e->tstamp[p]));
		found = true;
	पूर्ण

	अगर (!found)
		dev_err(hba->dev, "No record of %s\n", err_name);
	अन्यथा
		dev_err(hba->dev, "%s: total cnt=%llu\n", err_name, e->cnt);
पूर्ण

अटल व्योम ufshcd_prपूर्णांक_evt_hist(काष्ठा ufs_hba *hba)
अणु
	ufshcd_dump_regs(hba, 0, UFSHCI_REG_SPACE_SIZE, "host_regs: ");

	ufshcd_prपूर्णांक_evt(hba, UFS_EVT_PA_ERR, "pa_err");
	ufshcd_prपूर्णांक_evt(hba, UFS_EVT_DL_ERR, "dl_err");
	ufshcd_prपूर्णांक_evt(hba, UFS_EVT_NL_ERR, "nl_err");
	ufshcd_prपूर्णांक_evt(hba, UFS_EVT_TL_ERR, "tl_err");
	ufshcd_prपूर्णांक_evt(hba, UFS_EVT_DME_ERR, "dme_err");
	ufshcd_prपूर्णांक_evt(hba, UFS_EVT_AUTO_HIBERN8_ERR,
			 "auto_hibern8_err");
	ufshcd_prपूर्णांक_evt(hba, UFS_EVT_FATAL_ERR, "fatal_err");
	ufshcd_prपूर्णांक_evt(hba, UFS_EVT_LINK_STARTUP_FAIL,
			 "link_startup_fail");
	ufshcd_prपूर्णांक_evt(hba, UFS_EVT_RESUME_ERR, "resume_fail");
	ufshcd_prपूर्णांक_evt(hba, UFS_EVT_SUSPEND_ERR,
			 "suspend_fail");
	ufshcd_prपूर्णांक_evt(hba, UFS_EVT_DEV_RESET, "dev_reset");
	ufshcd_prपूर्णांक_evt(hba, UFS_EVT_HOST_RESET, "host_reset");
	ufshcd_prपूर्णांक_evt(hba, UFS_EVT_ABORT, "task_abort");

	ufshcd_vops_dbg_रेजिस्टर_dump(hba);
पूर्ण

अटल
व्योम ufshcd_prपूर्णांक_trs(काष्ठा ufs_hba *hba, अचिन्हित दीर्घ biपंचांगap, bool pr_prdt)
अणु
	काष्ठा ufshcd_lrb *lrbp;
	पूर्णांक prdt_length;
	पूर्णांक tag;

	क्रम_each_set_bit(tag, &biपंचांगap, hba->nutrs) अणु
		lrbp = &hba->lrb[tag];

		dev_err(hba->dev, "UPIU[%d] - issue time %lld us\n",
				tag, kसमय_प्रकारo_us(lrbp->issue_समय_stamp));
		dev_err(hba->dev, "UPIU[%d] - complete time %lld us\n",
				tag, kसमय_प्रकारo_us(lrbp->compl_समय_stamp));
		dev_err(hba->dev,
			"UPIU[%d] - Transfer Request Descriptor phys@0x%llx\n",
			tag, (u64)lrbp->utrd_dma_addr);

		ufshcd_hex_dump("UPIU TRD: ", lrbp->utr_descriptor_ptr,
				माप(काष्ठा utp_transfer_req_desc));
		dev_err(hba->dev, "UPIU[%d] - Request UPIU phys@0x%llx\n", tag,
			(u64)lrbp->ucd_req_dma_addr);
		ufshcd_hex_dump("UPIU REQ: ", lrbp->ucd_req_ptr,
				माप(काष्ठा utp_upiu_req));
		dev_err(hba->dev, "UPIU[%d] - Response UPIU phys@0x%llx\n", tag,
			(u64)lrbp->ucd_rsp_dma_addr);
		ufshcd_hex_dump("UPIU RSP: ", lrbp->ucd_rsp_ptr,
				माप(काष्ठा utp_upiu_rsp));

		prdt_length = le16_to_cpu(
			lrbp->utr_descriptor_ptr->prd_table_length);
		अगर (hba->quirks & UFSHCD_QUIRK_PRDT_BYTE_GRAN)
			prdt_length /= माप(काष्ठा ufshcd_sg_entry);

		dev_err(hba->dev,
			"UPIU[%d] - PRDT - %d entries  phys@0x%llx\n",
			tag, prdt_length,
			(u64)lrbp->ucd_prdt_dma_addr);

		अगर (pr_prdt)
			ufshcd_hex_dump("UPIU PRDT: ", lrbp->ucd_prdt_ptr,
				माप(काष्ठा ufshcd_sg_entry) * prdt_length);
	पूर्ण
पूर्ण

अटल व्योम ufshcd_prपूर्णांक_पंचांगrs(काष्ठा ufs_hba *hba, अचिन्हित दीर्घ biपंचांगap)
अणु
	पूर्णांक tag;

	क्रम_each_set_bit(tag, &biपंचांगap, hba->nuपंचांगrs) अणु
		काष्ठा utp_task_req_desc *पंचांगrdp = &hba->uपंचांगrdl_base_addr[tag];

		dev_err(hba->dev, "TM[%d] - Task Management Header\n", tag);
		ufshcd_hex_dump("", पंचांगrdp, माप(*पंचांगrdp));
	पूर्ण
पूर्ण

अटल व्योम ufshcd_prपूर्णांक_host_state(काष्ठा ufs_hba *hba)
अणु
	काष्ठा scsi_device *sdev_ufs = hba->sdev_ufs_device;

	dev_err(hba->dev, "UFS Host state=%d\n", hba->ufshcd_state);
	dev_err(hba->dev, "outstanding reqs=0x%lx tasks=0x%lx\n",
		hba->outstanding_reqs, hba->outstanding_tasks);
	dev_err(hba->dev, "saved_err=0x%x, saved_uic_err=0x%x\n",
		hba->saved_err, hba->saved_uic_err);
	dev_err(hba->dev, "Device power mode=%d, UIC link state=%d\n",
		hba->curr_dev_pwr_mode, hba->uic_link_state);
	dev_err(hba->dev, "PM in progress=%d, sys. suspended=%d\n",
		hba->pm_op_in_progress, hba->is_sys_suspended);
	dev_err(hba->dev, "Auto BKOPS=%d, Host self-block=%d\n",
		hba->स्वतः_bkops_enabled, hba->host->host_self_blocked);
	dev_err(hba->dev, "Clk gate=%d\n", hba->clk_gating.state);
	dev_err(hba->dev,
		"last_hibern8_exit_tstamp at %lld us, hibern8_exit_cnt=%d\n",
		kसमय_प्रकारo_us(hba->ufs_stats.last_hibern8_निकास_tstamp),
		hba->ufs_stats.hibern8_निकास_cnt);
	dev_err(hba->dev, "last intr at %lld us, last intr status=0x%x\n",
		kसमय_प्रकारo_us(hba->ufs_stats.last_पूर्णांकr_ts),
		hba->ufs_stats.last_पूर्णांकr_status);
	dev_err(hba->dev, "error handling flags=0x%x, req. abort count=%d\n",
		hba->eh_flags, hba->req_पात_count);
	dev_err(hba->dev, "hba->ufs_version=0x%x, Host capabilities=0x%x, caps=0x%x\n",
		hba->ufs_version, hba->capabilities, hba->caps);
	dev_err(hba->dev, "quirks=0x%x, dev. quirks=0x%x\n", hba->quirks,
		hba->dev_quirks);
	अगर (sdev_ufs)
		dev_err(hba->dev, "UFS dev info: %.8s %.16s rev %.4s\n",
			sdev_ufs->venकरोr, sdev_ufs->model, sdev_ufs->rev);

	ufshcd_prपूर्णांक_clk_freqs(hba);
पूर्ण

/**
 * ufshcd_prपूर्णांक_pwr_info - prपूर्णांक घातer params as saved in hba
 * घातer info
 * @hba: per-adapter instance
 */
अटल व्योम ufshcd_prपूर्णांक_pwr_info(काष्ठा ufs_hba *hba)
अणु
	अटल स्थिर अक्षर * स्थिर names[] = अणु
		"INVALID MODE",
		"FAST MODE",
		"SLOW_MODE",
		"INVALID MODE",
		"FASTAUTO_MODE",
		"SLOWAUTO_MODE",
		"INVALID MODE",
	पूर्ण;

	dev_err(hba->dev, "%s:[RX, TX]: gear=[%d, %d], lane[%d, %d], pwr[%s, %s], rate = %d\n",
		 __func__,
		 hba->pwr_info.gear_rx, hba->pwr_info.gear_tx,
		 hba->pwr_info.lane_rx, hba->pwr_info.lane_tx,
		 names[hba->pwr_info.pwr_rx],
		 names[hba->pwr_info.pwr_tx],
		 hba->pwr_info.hs_rate);
पूर्ण

अटल व्योम ufshcd_device_reset(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err;

	err = ufshcd_vops_device_reset(hba);

	अगर (!err) अणु
		ufshcd_set_ufs_dev_active(hba);
		अगर (ufshcd_is_wb_allowed(hba)) अणु
			hba->dev_info.wb_enabled = false;
			hba->dev_info.wb_buf_flush_enabled = false;
		पूर्ण
	पूर्ण
	अगर (err != -EOPNOTSUPP)
		ufshcd_update_evt_hist(hba, UFS_EVT_DEV_RESET, err);
पूर्ण

व्योम ufshcd_delay_us(अचिन्हित दीर्घ us, अचिन्हित दीर्घ tolerance)
अणु
	अगर (!us)
		वापस;

	अगर (us < 10)
		udelay(us);
	अन्यथा
		usleep_range(us, us + tolerance);
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_delay_us);

/**
 * ufshcd_रुको_क्रम_रेजिस्टर - रुको क्रम रेजिस्टर value to change
 * @hba: per-adapter पूर्णांकerface
 * @reg: mmio रेजिस्टर offset
 * @mask: mask to apply to the पढ़ो रेजिस्टर value
 * @val: value to रुको क्रम
 * @पूर्णांकerval_us: polling पूर्णांकerval in microseconds
 * @समयout_ms: समयout in milliseconds
 *
 * Return:
 * -ETIMEDOUT on error, zero on success.
 */
पूर्णांक ufshcd_रुको_क्रम_रेजिस्टर(काष्ठा ufs_hba *hba, u32 reg, u32 mask,
				u32 val, अचिन्हित दीर्घ पूर्णांकerval_us,
				अचिन्हित दीर्घ समयout_ms)
अणु
	पूर्णांक err = 0;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(समयout_ms);

	/* ignore bits that we करोn't पूर्णांकend to रुको on */
	val = val & mask;

	जबतक ((ufshcd_पढ़ोl(hba, reg) & mask) != val) अणु
		usleep_range(पूर्णांकerval_us, पूर्णांकerval_us + 50);
		अगर (समय_after(jअगरfies, समयout)) अणु
			अगर ((ufshcd_पढ़ोl(hba, reg) & mask) != val)
				err = -ETIMEDOUT;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/**
 * ufshcd_get_पूर्णांकr_mask - Get the पूर्णांकerrupt bit mask
 * @hba: Poपूर्णांकer to adapter instance
 *
 * Returns पूर्णांकerrupt bit mask per version
 */
अटल अंतरभूत u32 ufshcd_get_पूर्णांकr_mask(काष्ठा ufs_hba *hba)
अणु
	अगर (hba->ufs_version == ufshci_version(1, 0))
		वापस INTERRUPT_MASK_ALL_VER_10;
	अगर (hba->ufs_version <= ufshci_version(2, 0))
		वापस INTERRUPT_MASK_ALL_VER_11;

	वापस INTERRUPT_MASK_ALL_VER_21;
पूर्ण

/**
 * ufshcd_get_ufs_version - Get the UFS version supported by the HBA
 * @hba: Poपूर्णांकer to adapter instance
 *
 * Returns UFSHCI version supported by the controller
 */
अटल अंतरभूत u32 ufshcd_get_ufs_version(काष्ठा ufs_hba *hba)
अणु
	u32 ufshci_ver;

	अगर (hba->quirks & UFSHCD_QUIRK_BROKEN_UFS_HCI_VERSION)
		ufshci_ver = ufshcd_vops_get_ufs_hci_version(hba);
	अन्यथा
		ufshci_ver = ufshcd_पढ़ोl(hba, REG_UFS_VERSION);

	/*
	 * UFSHCI v1.x uses a dअगरferent version scheme, in order
	 * to allow the use of comparisons with the ufshci_version
	 * function, we convert it to the same scheme as ufs 2.0+.
	 */
	अगर (ufshci_ver & 0x00010000)
		वापस ufshci_version(1, ufshci_ver & 0x00000100);

	वापस ufshci_ver;
पूर्ण

/**
 * ufshcd_is_device_present - Check अगर any device connected to
 *			      the host controller
 * @hba: poपूर्णांकer to adapter instance
 *
 * Returns true अगर device present, false अगर no device detected
 */
अटल अंतरभूत bool ufshcd_is_device_present(काष्ठा ufs_hba *hba)
अणु
	वापस (ufshcd_पढ़ोl(hba, REG_CONTROLLER_STATUS) &
						DEVICE_PRESENT) ? true : false;
पूर्ण

/**
 * ufshcd_get_tr_ocs - Get the UTRD Overall Command Status
 * @lrbp: poपूर्णांकer to local command reference block
 *
 * This function is used to get the OCS field from UTRD
 * Returns the OCS field in the UTRD
 */
अटल अंतरभूत पूर्णांक ufshcd_get_tr_ocs(काष्ठा ufshcd_lrb *lrbp)
अणु
	वापस le32_to_cpu(lrbp->utr_descriptor_ptr->header.dword_2) & MASK_OCS;
पूर्ण

/**
 * ufshcd_utrl_clear - Clear a bit in UTRLCLR रेजिस्टर
 * @hba: per adapter instance
 * @pos: position of the bit to be cleared
 */
अटल अंतरभूत व्योम ufshcd_utrl_clear(काष्ठा ufs_hba *hba, u32 pos)
अणु
	अगर (hba->quirks & UFSHCI_QUIRK_BROKEN_REQ_LIST_CLR)
		ufshcd_ग_लिखोl(hba, (1 << pos), REG_UTP_TRANSFER_REQ_LIST_CLEAR);
	अन्यथा
		ufshcd_ग_लिखोl(hba, ~(1 << pos),
				REG_UTP_TRANSFER_REQ_LIST_CLEAR);
पूर्ण

/**
 * ufshcd_uपंचांगrl_clear - Clear a bit in UTRMLCLR रेजिस्टर
 * @hba: per adapter instance
 * @pos: position of the bit to be cleared
 */
अटल अंतरभूत व्योम ufshcd_uपंचांगrl_clear(काष्ठा ufs_hba *hba, u32 pos)
अणु
	अगर (hba->quirks & UFSHCI_QUIRK_BROKEN_REQ_LIST_CLR)
		ufshcd_ग_लिखोl(hba, (1 << pos), REG_UTP_TASK_REQ_LIST_CLEAR);
	अन्यथा
		ufshcd_ग_लिखोl(hba, ~(1 << pos), REG_UTP_TASK_REQ_LIST_CLEAR);
पूर्ण

/**
 * ufshcd_outstanding_req_clear - Clear a bit in outstanding request field
 * @hba: per adapter instance
 * @tag: position of the bit to be cleared
 */
अटल अंतरभूत व्योम ufshcd_outstanding_req_clear(काष्ठा ufs_hba *hba, पूर्णांक tag)
अणु
	__clear_bit(tag, &hba->outstanding_reqs);
पूर्ण

/**
 * ufshcd_get_lists_status - Check UCRDY, UTRLRDY and UTMRLRDY
 * @reg: Register value of host controller status
 *
 * Returns पूर्णांकeger, 0 on Success and positive value अगर failed
 */
अटल अंतरभूत पूर्णांक ufshcd_get_lists_status(u32 reg)
अणु
	वापस !((reg & UFSHCD_STATUS_READY) == UFSHCD_STATUS_READY);
पूर्ण

/**
 * ufshcd_get_uic_cmd_result - Get the UIC command result
 * @hba: Poपूर्णांकer to adapter instance
 *
 * This function माला_लो the result of UIC command completion
 * Returns 0 on success, non zero value on error
 */
अटल अंतरभूत पूर्णांक ufshcd_get_uic_cmd_result(काष्ठा ufs_hba *hba)
अणु
	वापस ufshcd_पढ़ोl(hba, REG_UIC_COMMAND_ARG_2) &
	       MASK_UIC_COMMAND_RESULT;
पूर्ण

/**
 * ufshcd_get_dme_attr_val - Get the value of attribute वापसed by UIC command
 * @hba: Poपूर्णांकer to adapter instance
 *
 * This function माला_लो UIC command argument3
 * Returns 0 on success, non zero value on error
 */
अटल अंतरभूत u32 ufshcd_get_dme_attr_val(काष्ठा ufs_hba *hba)
अणु
	वापस ufshcd_पढ़ोl(hba, REG_UIC_COMMAND_ARG_3);
पूर्ण

/**
 * ufshcd_get_req_rsp - वापसs the TR response transaction type
 * @ucd_rsp_ptr: poपूर्णांकer to response UPIU
 */
अटल अंतरभूत पूर्णांक
ufshcd_get_req_rsp(काष्ठा utp_upiu_rsp *ucd_rsp_ptr)
अणु
	वापस be32_to_cpu(ucd_rsp_ptr->header.dword_0) >> 24;
पूर्ण

/**
 * ufshcd_get_rsp_upiu_result - Get the result from response UPIU
 * @ucd_rsp_ptr: poपूर्णांकer to response UPIU
 *
 * This function माला_लो the response status and scsi_status from response UPIU
 * Returns the response result code.
 */
अटल अंतरभूत पूर्णांक
ufshcd_get_rsp_upiu_result(काष्ठा utp_upiu_rsp *ucd_rsp_ptr)
अणु
	वापस be32_to_cpu(ucd_rsp_ptr->header.dword_1) & MASK_RSP_UPIU_RESULT;
पूर्ण

/*
 * ufshcd_get_rsp_upiu_data_seg_len - Get the data segment length
 *				from response UPIU
 * @ucd_rsp_ptr: poपूर्णांकer to response UPIU
 *
 * Return the data segment length.
 */
अटल अंतरभूत अचिन्हित पूर्णांक
ufshcd_get_rsp_upiu_data_seg_len(काष्ठा utp_upiu_rsp *ucd_rsp_ptr)
अणु
	वापस be32_to_cpu(ucd_rsp_ptr->header.dword_2) &
		MASK_RSP_UPIU_DATA_SEG_LEN;
पूर्ण

/**
 * ufshcd_is_exception_event - Check अगर the device उठाओd an exception event
 * @ucd_rsp_ptr: poपूर्णांकer to response UPIU
 *
 * The function checks अगर the device उठाओd an exception event indicated in
 * the Device Inक्रमmation field of response UPIU.
 *
 * Returns true अगर exception is उठाओd, false otherwise.
 */
अटल अंतरभूत bool ufshcd_is_exception_event(काष्ठा utp_upiu_rsp *ucd_rsp_ptr)
अणु
	वापस be32_to_cpu(ucd_rsp_ptr->header.dword_2) &
			MASK_RSP_EXCEPTION_EVENT ? true : false;
पूर्ण

/**
 * ufshcd_reset_पूर्णांकr_aggr - Reset पूर्णांकerrupt aggregation values.
 * @hba: per adapter instance
 */
अटल अंतरभूत व्योम
ufshcd_reset_पूर्णांकr_aggr(काष्ठा ufs_hba *hba)
अणु
	ufshcd_ग_लिखोl(hba, INT_AGGR_ENABLE |
		      INT_AGGR_COUNTER_AND_TIMER_RESET,
		      REG_UTP_TRANSFER_REQ_INT_AGG_CONTROL);
पूर्ण

/**
 * ufshcd_config_पूर्णांकr_aggr - Configure पूर्णांकerrupt aggregation values.
 * @hba: per adapter instance
 * @cnt: Interrupt aggregation counter threshold
 * @पंचांगout: Interrupt aggregation समयout value
 */
अटल अंतरभूत व्योम
ufshcd_config_पूर्णांकr_aggr(काष्ठा ufs_hba *hba, u8 cnt, u8 पंचांगout)
अणु
	ufshcd_ग_लिखोl(hba, INT_AGGR_ENABLE | INT_AGGR_PARAM_WRITE |
		      INT_AGGR_COUNTER_THLD_VAL(cnt) |
		      INT_AGGR_TIMEOUT_VAL(पंचांगout),
		      REG_UTP_TRANSFER_REQ_INT_AGG_CONTROL);
पूर्ण

/**
 * ufshcd_disable_पूर्णांकr_aggr - Disables पूर्णांकerrupt aggregation.
 * @hba: per adapter instance
 */
अटल अंतरभूत व्योम ufshcd_disable_पूर्णांकr_aggr(काष्ठा ufs_hba *hba)
अणु
	ufshcd_ग_लिखोl(hba, 0, REG_UTP_TRANSFER_REQ_INT_AGG_CONTROL);
पूर्ण

/**
 * ufshcd_enable_run_stop_reg - Enable run-stop रेजिस्टरs,
 *			When run-stop रेजिस्टरs are set to 1, it indicates the
 *			host controller that it can process the requests
 * @hba: per adapter instance
 */
अटल व्योम ufshcd_enable_run_stop_reg(काष्ठा ufs_hba *hba)
अणु
	ufshcd_ग_लिखोl(hba, UTP_TASK_REQ_LIST_RUN_STOP_BIT,
		      REG_UTP_TASK_REQ_LIST_RUN_STOP);
	ufshcd_ग_लिखोl(hba, UTP_TRANSFER_REQ_LIST_RUN_STOP_BIT,
		      REG_UTP_TRANSFER_REQ_LIST_RUN_STOP);
पूर्ण

/**
 * ufshcd_hba_start - Start controller initialization sequence
 * @hba: per adapter instance
 */
अटल अंतरभूत व्योम ufshcd_hba_start(काष्ठा ufs_hba *hba)
अणु
	u32 val = CONTROLLER_ENABLE;

	अगर (ufshcd_crypto_enable(hba))
		val |= CRYPTO_GENERAL_ENABLE;

	ufshcd_ग_लिखोl(hba, val, REG_CONTROLLER_ENABLE);
पूर्ण

/**
 * ufshcd_is_hba_active - Get controller state
 * @hba: per adapter instance
 *
 * Returns false अगर controller is active, true otherwise
 */
अटल अंतरभूत bool ufshcd_is_hba_active(काष्ठा ufs_hba *hba)
अणु
	वापस (ufshcd_पढ़ोl(hba, REG_CONTROLLER_ENABLE) & CONTROLLER_ENABLE)
		? false : true;
पूर्ण

u32 ufshcd_get_local_unipro_ver(काष्ठा ufs_hba *hba)
अणु
	/* HCI version 1.0 and 1.1 supports UniPro 1.41 */
	अगर (hba->ufs_version <= ufshci_version(1, 1))
		वापस UFS_UNIPRO_VER_1_41;
	अन्यथा
		वापस UFS_UNIPRO_VER_1_6;
पूर्ण
EXPORT_SYMBOL(ufshcd_get_local_unipro_ver);

अटल bool ufshcd_is_unipro_pa_params_tuning_req(काष्ठा ufs_hba *hba)
अणु
	/*
	 * If both host and device support UniPro ver1.6 or later, PA layer
	 * parameters tuning happens during link startup itself.
	 *
	 * We can manually tune PA layer parameters अगर either host or device
	 * करोesn't support UniPro ver 1.6 or later. But to keep manual tuning
	 * logic simple, we will only करो manual tuning अगर local unipro version
	 * करोesn't support ver1.6 or later.
	 */
	अगर (ufshcd_get_local_unipro_ver(hba) < UFS_UNIPRO_VER_1_6)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/**
 * ufshcd_set_clk_freq - set UFS controller घड़ी frequencies
 * @hba: per adapter instance
 * @scale_up: If True, set max possible frequency othewise set low frequency
 *
 * Returns 0 अगर successful
 * Returns < 0 क्रम any other errors
 */
अटल पूर्णांक ufshcd_set_clk_freq(काष्ठा ufs_hba *hba, bool scale_up)
अणु
	पूर्णांक ret = 0;
	काष्ठा ufs_clk_info *clki;
	काष्ठा list_head *head = &hba->clk_list_head;

	अगर (list_empty(head))
		जाओ out;

	list_क्रम_each_entry(clki, head, list) अणु
		अगर (!IS_ERR_OR_शून्य(clki->clk)) अणु
			अगर (scale_up && clki->max_freq) अणु
				अगर (clki->curr_freq == clki->max_freq)
					जारी;

				ret = clk_set_rate(clki->clk, clki->max_freq);
				अगर (ret) अणु
					dev_err(hba->dev, "%s: %s clk set rate(%dHz) failed, %d\n",
						__func__, clki->name,
						clki->max_freq, ret);
					अवरोध;
				पूर्ण
				trace_ufshcd_clk_scaling(dev_name(hba->dev),
						"scaled up", clki->name,
						clki->curr_freq,
						clki->max_freq);

				clki->curr_freq = clki->max_freq;

			पूर्ण अन्यथा अगर (!scale_up && clki->min_freq) अणु
				अगर (clki->curr_freq == clki->min_freq)
					जारी;

				ret = clk_set_rate(clki->clk, clki->min_freq);
				अगर (ret) अणु
					dev_err(hba->dev, "%s: %s clk set rate(%dHz) failed, %d\n",
						__func__, clki->name,
						clki->min_freq, ret);
					अवरोध;
				पूर्ण
				trace_ufshcd_clk_scaling(dev_name(hba->dev),
						"scaled down", clki->name,
						clki->curr_freq,
						clki->min_freq);
				clki->curr_freq = clki->min_freq;
			पूर्ण
		पूर्ण
		dev_dbg(hba->dev, "%s: clk: %s, rate: %lu\n", __func__,
				clki->name, clk_get_rate(clki->clk));
	पूर्ण

out:
	वापस ret;
पूर्ण

/**
 * ufshcd_scale_clks - scale up or scale करोwn UFS controller घड़ीs
 * @hba: per adapter instance
 * @scale_up: True अगर scaling up and false अगर scaling करोwn
 *
 * Returns 0 अगर successful
 * Returns < 0 क्रम any other errors
 */
अटल पूर्णांक ufshcd_scale_clks(काष्ठा ufs_hba *hba, bool scale_up)
अणु
	पूर्णांक ret = 0;
	kसमय_प्रकार start = kसमय_get();

	ret = ufshcd_vops_clk_scale_notअगरy(hba, scale_up, PRE_CHANGE);
	अगर (ret)
		जाओ out;

	ret = ufshcd_set_clk_freq(hba, scale_up);
	अगर (ret)
		जाओ out;

	ret = ufshcd_vops_clk_scale_notअगरy(hba, scale_up, POST_CHANGE);
	अगर (ret)
		ufshcd_set_clk_freq(hba, !scale_up);

out:
	trace_ufshcd_profile_clk_scaling(dev_name(hba->dev),
			(scale_up ? "up" : "down"),
			kसमय_प्रकारo_us(kसमय_sub(kसमय_get(), start)), ret);
	वापस ret;
पूर्ण

/**
 * ufshcd_is_devfreq_scaling_required - check अगर scaling is required or not
 * @hba: per adapter instance
 * @scale_up: True अगर scaling up and false अगर scaling करोwn
 *
 * Returns true अगर scaling is required, false otherwise.
 */
अटल bool ufshcd_is_devfreq_scaling_required(काष्ठा ufs_hba *hba,
					       bool scale_up)
अणु
	काष्ठा ufs_clk_info *clki;
	काष्ठा list_head *head = &hba->clk_list_head;

	अगर (list_empty(head))
		वापस false;

	list_क्रम_each_entry(clki, head, list) अणु
		अगर (!IS_ERR_OR_शून्य(clki->clk)) अणु
			अगर (scale_up && clki->max_freq) अणु
				अगर (clki->curr_freq == clki->max_freq)
					जारी;
				वापस true;
			पूर्ण अन्यथा अगर (!scale_up && clki->min_freq) अणु
				अगर (clki->curr_freq == clki->min_freq)
					जारी;
				वापस true;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक ufshcd_रुको_क्रम_करोorbell_clr(काष्ठा ufs_hba *hba,
					u64 रुको_समयout_us)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	u32 पंचांग_करोorbell;
	u32 tr_करोorbell;
	bool समयout = false, करो_last_check = false;
	kसमय_प्रकार start;

	ufshcd_hold(hba, false);
	spin_lock_irqsave(hba->host->host_lock, flags);
	/*
	 * Wait क्रम all the outstanding tasks/transfer requests.
	 * Verअगरy by checking the करोorbell रेजिस्टरs are clear.
	 */
	start = kसमय_get();
	करो अणु
		अगर (hba->ufshcd_state != UFSHCD_STATE_OPERATIONAL) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण

		पंचांग_करोorbell = ufshcd_पढ़ोl(hba, REG_UTP_TASK_REQ_DOOR_BELL);
		tr_करोorbell = ufshcd_पढ़ोl(hba, REG_UTP_TRANSFER_REQ_DOOR_BELL);
		अगर (!पंचांग_करोorbell && !tr_करोorbell) अणु
			समयout = false;
			अवरोध;
		पूर्ण अन्यथा अगर (करो_last_check) अणु
			अवरोध;
		पूर्ण

		spin_unlock_irqrestore(hba->host->host_lock, flags);
		schedule();
		अगर (kसमय_प्रकारo_us(kसमय_sub(kसमय_get(), start)) >
		    रुको_समयout_us) अणु
			समयout = true;
			/*
			 * We might have scheduled out क्रम दीर्घ समय so make
			 * sure to check अगर करोorbells are cleared by this समय
			 * or not.
			 */
			करो_last_check = true;
		पूर्ण
		spin_lock_irqsave(hba->host->host_lock, flags);
	पूर्ण जबतक (पंचांग_करोorbell || tr_करोorbell);

	अगर (समयout) अणु
		dev_err(hba->dev,
			"%s: timedout waiting for doorbell to clear (tm=0x%x, tr=0x%x)\n",
			__func__, पंचांग_करोorbell, tr_करोorbell);
		ret = -EBUSY;
	पूर्ण
out:
	spin_unlock_irqrestore(hba->host->host_lock, flags);
	ufshcd_release(hba);
	वापस ret;
पूर्ण

/**
 * ufshcd_scale_gear - scale up/करोwn UFS gear
 * @hba: per adapter instance
 * @scale_up: True क्रम scaling up gear and false क्रम scaling करोwn
 *
 * Returns 0 क्रम success,
 * Returns -EBUSY अगर scaling can't happen at this समय
 * Returns non-zero क्रम any other errors
 */
अटल पूर्णांक ufshcd_scale_gear(काष्ठा ufs_hba *hba, bool scale_up)
अणु
	पूर्णांक ret = 0;
	काष्ठा ufs_pa_layer_attr new_pwr_info;

	अगर (scale_up) अणु
		स_नकल(&new_pwr_info, &hba->clk_scaling.saved_pwr_info.info,
		       माप(काष्ठा ufs_pa_layer_attr));
	पूर्ण अन्यथा अणु
		स_नकल(&new_pwr_info, &hba->pwr_info,
		       माप(काष्ठा ufs_pa_layer_attr));

		अगर (hba->pwr_info.gear_tx > hba->clk_scaling.min_gear ||
		    hba->pwr_info.gear_rx > hba->clk_scaling.min_gear) अणु
			/* save the current घातer mode */
			स_नकल(&hba->clk_scaling.saved_pwr_info.info,
				&hba->pwr_info,
				माप(काष्ठा ufs_pa_layer_attr));

			/* scale करोwn gear */
			new_pwr_info.gear_tx = hba->clk_scaling.min_gear;
			new_pwr_info.gear_rx = hba->clk_scaling.min_gear;
		पूर्ण
	पूर्ण

	/* check अगर the घातer mode needs to be changed or not? */
	ret = ufshcd_config_pwr_mode(hba, &new_pwr_info);
	अगर (ret)
		dev_err(hba->dev, "%s: failed err %d, old gear: (tx %d rx %d), new gear: (tx %d rx %d)",
			__func__, ret,
			hba->pwr_info.gear_tx, hba->pwr_info.gear_rx,
			new_pwr_info.gear_tx, new_pwr_info.gear_rx);

	वापस ret;
पूर्ण

अटल पूर्णांक ufshcd_घड़ी_scaling_prepare(काष्ठा ufs_hba *hba)
अणु
	#घोषणा DOORBELL_CLR_TOUT_US		(1000 * 1000) /* 1 sec */
	पूर्णांक ret = 0;
	/*
	 * make sure that there are no outstanding requests when
	 * घड़ी scaling is in progress
	 */
	ufshcd_scsi_block_requests(hba);
	करोwn_ग_लिखो(&hba->clk_scaling_lock);

	अगर (!hba->clk_scaling.is_allowed ||
	    ufshcd_रुको_क्रम_करोorbell_clr(hba, DOORBELL_CLR_TOUT_US)) अणु
		ret = -EBUSY;
		up_ग_लिखो(&hba->clk_scaling_lock);
		ufshcd_scsi_unblock_requests(hba);
		जाओ out;
	पूर्ण

	/* let's not get पूर्णांकo low घातer until घड़ी scaling is completed */
	ufshcd_hold(hba, false);

out:
	वापस ret;
पूर्ण

अटल व्योम ufshcd_घड़ी_scaling_unprepare(काष्ठा ufs_hba *hba, bool ग_लिखोlock)
अणु
	अगर (ग_लिखोlock)
		up_ग_लिखो(&hba->clk_scaling_lock);
	अन्यथा
		up_पढ़ो(&hba->clk_scaling_lock);
	ufshcd_scsi_unblock_requests(hba);
	ufshcd_release(hba);
पूर्ण

/**
 * ufshcd_devfreq_scale - scale up/करोwn UFS घड़ीs and gear
 * @hba: per adapter instance
 * @scale_up: True क्रम scaling up and false क्रम scalin करोwn
 *
 * Returns 0 क्रम success,
 * Returns -EBUSY अगर scaling can't happen at this समय
 * Returns non-zero क्रम any other errors
 */
अटल पूर्णांक ufshcd_devfreq_scale(काष्ठा ufs_hba *hba, bool scale_up)
अणु
	पूर्णांक ret = 0;
	bool is_ग_लिखोlock = true;

	ret = ufshcd_घड़ी_scaling_prepare(hba);
	अगर (ret)
		वापस ret;

	/* scale करोwn the gear beक्रमe scaling करोwn घड़ीs */
	अगर (!scale_up) अणु
		ret = ufshcd_scale_gear(hba, false);
		अगर (ret)
			जाओ out_unprepare;
	पूर्ण

	ret = ufshcd_scale_clks(hba, scale_up);
	अगर (ret) अणु
		अगर (!scale_up)
			ufshcd_scale_gear(hba, true);
		जाओ out_unprepare;
	पूर्ण

	/* scale up the gear after scaling up घड़ीs */
	अगर (scale_up) अणु
		ret = ufshcd_scale_gear(hba, true);
		अगर (ret) अणु
			ufshcd_scale_clks(hba, false);
			जाओ out_unprepare;
		पूर्ण
	पूर्ण

	/* Enable Write Booster अगर we have scaled up अन्यथा disable it */
	करोwngrade_ग_लिखो(&hba->clk_scaling_lock);
	is_ग_लिखोlock = false;
	ufshcd_wb_toggle(hba, scale_up);

out_unprepare:
	ufshcd_घड़ी_scaling_unprepare(hba, is_ग_लिखोlock);
	वापस ret;
पूर्ण

अटल व्योम ufshcd_clk_scaling_suspend_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ufs_hba *hba = container_of(work, काष्ठा ufs_hba,
					   clk_scaling.suspend_work);
	अचिन्हित दीर्घ irq_flags;

	spin_lock_irqsave(hba->host->host_lock, irq_flags);
	अगर (hba->clk_scaling.active_reqs || hba->clk_scaling.is_suspended) अणु
		spin_unlock_irqrestore(hba->host->host_lock, irq_flags);
		वापस;
	पूर्ण
	hba->clk_scaling.is_suspended = true;
	spin_unlock_irqrestore(hba->host->host_lock, irq_flags);

	__ufshcd_suspend_clkscaling(hba);
पूर्ण

अटल व्योम ufshcd_clk_scaling_resume_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ufs_hba *hba = container_of(work, काष्ठा ufs_hba,
					   clk_scaling.resume_work);
	अचिन्हित दीर्घ irq_flags;

	spin_lock_irqsave(hba->host->host_lock, irq_flags);
	अगर (!hba->clk_scaling.is_suspended) अणु
		spin_unlock_irqrestore(hba->host->host_lock, irq_flags);
		वापस;
	पूर्ण
	hba->clk_scaling.is_suspended = false;
	spin_unlock_irqrestore(hba->host->host_lock, irq_flags);

	devfreq_resume_device(hba->devfreq);
पूर्ण

अटल पूर्णांक ufshcd_devfreq_target(काष्ठा device *dev,
				अचिन्हित दीर्घ *freq, u32 flags)
अणु
	पूर्णांक ret = 0;
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);
	kसमय_प्रकार start;
	bool scale_up, sched_clk_scaling_suspend_work = false;
	काष्ठा list_head *clk_list = &hba->clk_list_head;
	काष्ठा ufs_clk_info *clki;
	अचिन्हित दीर्घ irq_flags;

	अगर (!ufshcd_is_clkscaling_supported(hba))
		वापस -EINVAL;

	clki = list_first_entry(&hba->clk_list_head, काष्ठा ufs_clk_info, list);
	/* Override with the बंदst supported frequency */
	*freq = (अचिन्हित दीर्घ) clk_round_rate(clki->clk, *freq);
	spin_lock_irqsave(hba->host->host_lock, irq_flags);
	अगर (ufshcd_eh_in_progress(hba)) अणु
		spin_unlock_irqrestore(hba->host->host_lock, irq_flags);
		वापस 0;
	पूर्ण

	अगर (!hba->clk_scaling.active_reqs)
		sched_clk_scaling_suspend_work = true;

	अगर (list_empty(clk_list)) अणु
		spin_unlock_irqrestore(hba->host->host_lock, irq_flags);
		जाओ out;
	पूर्ण

	/* Decide based on the rounded-off frequency and update */
	scale_up = (*freq == clki->max_freq) ? true : false;
	अगर (!scale_up)
		*freq = clki->min_freq;
	/* Update the frequency */
	अगर (!ufshcd_is_devfreq_scaling_required(hba, scale_up)) अणु
		spin_unlock_irqrestore(hba->host->host_lock, irq_flags);
		ret = 0;
		जाओ out; /* no state change required */
	पूर्ण
	spin_unlock_irqrestore(hba->host->host_lock, irq_flags);

	start = kसमय_get();
	ret = ufshcd_devfreq_scale(hba, scale_up);

	trace_ufshcd_profile_clk_scaling(dev_name(hba->dev),
		(scale_up ? "up" : "down"),
		kसमय_प्रकारo_us(kसमय_sub(kसमय_get(), start)), ret);

out:
	अगर (sched_clk_scaling_suspend_work)
		queue_work(hba->clk_scaling.workq,
			   &hba->clk_scaling.suspend_work);

	वापस ret;
पूर्ण

अटल bool ufshcd_is_busy(काष्ठा request *req, व्योम *priv, bool reserved)
अणु
	पूर्णांक *busy = priv;

	WARN_ON_ONCE(reserved);
	(*busy)++;
	वापस false;
पूर्ण

/* Whether or not any tag is in use by a request that is in progress. */
अटल bool ufshcd_any_tag_in_use(काष्ठा ufs_hba *hba)
अणु
	काष्ठा request_queue *q = hba->cmd_queue;
	पूर्णांक busy = 0;

	blk_mq_tagset_busy_iter(q->tag_set, ufshcd_is_busy, &busy);
	वापस busy;
पूर्ण

अटल पूर्णांक ufshcd_devfreq_get_dev_status(काष्ठा device *dev,
		काष्ठा devfreq_dev_status *stat)
अणु
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);
	काष्ठा ufs_clk_scaling *scaling = &hba->clk_scaling;
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *clk_list = &hba->clk_list_head;
	काष्ठा ufs_clk_info *clki;
	kसमय_प्रकार curr_t;

	अगर (!ufshcd_is_clkscaling_supported(hba))
		वापस -EINVAL;

	स_रखो(stat, 0, माप(*stat));

	spin_lock_irqsave(hba->host->host_lock, flags);
	curr_t = kसमय_get();
	अगर (!scaling->winकरोw_start_t)
		जाओ start_winकरोw;

	clki = list_first_entry(clk_list, काष्ठा ufs_clk_info, list);
	/*
	 * If current frequency is 0, then the ondemand governor considers
	 * there's no initial frequency set. And it always requests to set
	 * to max. frequency.
	 */
	stat->current_frequency = clki->curr_freq;
	अगर (scaling->is_busy_started)
		scaling->tot_busy_t += kसमय_us_delta(curr_t,
				scaling->busy_start_t);

	stat->total_समय = kसमय_us_delta(curr_t, scaling->winकरोw_start_t);
	stat->busy_समय = scaling->tot_busy_t;
start_winकरोw:
	scaling->winकरोw_start_t = curr_t;
	scaling->tot_busy_t = 0;

	अगर (hba->outstanding_reqs) अणु
		scaling->busy_start_t = curr_t;
		scaling->is_busy_started = true;
	पूर्ण अन्यथा अणु
		scaling->busy_start_t = 0;
		scaling->is_busy_started = false;
	पूर्ण
	spin_unlock_irqrestore(hba->host->host_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक ufshcd_devfreq_init(काष्ठा ufs_hba *hba)
अणु
	काष्ठा list_head *clk_list = &hba->clk_list_head;
	काष्ठा ufs_clk_info *clki;
	काष्ठा devfreq *devfreq;
	पूर्णांक ret;

	/* Skip devfreq अगर we करोn't have any घड़ीs in the list */
	अगर (list_empty(clk_list))
		वापस 0;

	clki = list_first_entry(clk_list, काष्ठा ufs_clk_info, list);
	dev_pm_opp_add(hba->dev, clki->min_freq, 0);
	dev_pm_opp_add(hba->dev, clki->max_freq, 0);

	ufshcd_vops_config_scaling_param(hba, &hba->vps->devfreq_profile,
					 &hba->vps->ondemand_data);
	devfreq = devfreq_add_device(hba->dev,
			&hba->vps->devfreq_profile,
			DEVFREQ_GOV_SIMPLE_ONDEMAND,
			&hba->vps->ondemand_data);
	अगर (IS_ERR(devfreq)) अणु
		ret = PTR_ERR(devfreq);
		dev_err(hba->dev, "Unable to register with devfreq %d\n", ret);

		dev_pm_opp_हटाओ(hba->dev, clki->min_freq);
		dev_pm_opp_हटाओ(hba->dev, clki->max_freq);
		वापस ret;
	पूर्ण

	hba->devfreq = devfreq;

	वापस 0;
पूर्ण

अटल व्योम ufshcd_devfreq_हटाओ(काष्ठा ufs_hba *hba)
अणु
	काष्ठा list_head *clk_list = &hba->clk_list_head;
	काष्ठा ufs_clk_info *clki;

	अगर (!hba->devfreq)
		वापस;

	devfreq_हटाओ_device(hba->devfreq);
	hba->devfreq = शून्य;

	clki = list_first_entry(clk_list, काष्ठा ufs_clk_info, list);
	dev_pm_opp_हटाओ(hba->dev, clki->min_freq);
	dev_pm_opp_हटाओ(hba->dev, clki->max_freq);
पूर्ण

अटल व्योम __ufshcd_suspend_clkscaling(काष्ठा ufs_hba *hba)
अणु
	अचिन्हित दीर्घ flags;

	devfreq_suspend_device(hba->devfreq);
	spin_lock_irqsave(hba->host->host_lock, flags);
	hba->clk_scaling.winकरोw_start_t = 0;
	spin_unlock_irqrestore(hba->host->host_lock, flags);
पूर्ण

अटल व्योम ufshcd_suspend_clkscaling(काष्ठा ufs_hba *hba)
अणु
	अचिन्हित दीर्घ flags;
	bool suspend = false;

	cancel_work_sync(&hba->clk_scaling.suspend_work);
	cancel_work_sync(&hba->clk_scaling.resume_work);

	spin_lock_irqsave(hba->host->host_lock, flags);
	अगर (!hba->clk_scaling.is_suspended) अणु
		suspend = true;
		hba->clk_scaling.is_suspended = true;
	पूर्ण
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	अगर (suspend)
		__ufshcd_suspend_clkscaling(hba);
पूर्ण

अटल व्योम ufshcd_resume_clkscaling(काष्ठा ufs_hba *hba)
अणु
	अचिन्हित दीर्घ flags;
	bool resume = false;

	spin_lock_irqsave(hba->host->host_lock, flags);
	अगर (hba->clk_scaling.is_suspended) अणु
		resume = true;
		hba->clk_scaling.is_suspended = false;
	पूर्ण
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	अगर (resume)
		devfreq_resume_device(hba->devfreq);
पूर्ण

अटल sमाप_प्रकार ufshcd_clkscale_enable_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%d\n", hba->clk_scaling.is_enabled);
पूर्ण

अटल sमाप_प्रकार ufshcd_clkscale_enable_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);
	u32 value;
	पूर्णांक err = 0;

	अगर (kstrtou32(buf, 0, &value))
		वापस -EINVAL;

	करोwn(&hba->host_sem);
	अगर (!ufshcd_is_user_access_allowed(hba)) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	value = !!value;
	अगर (value == hba->clk_scaling.is_enabled)
		जाओ out;

	pm_runसमय_get_sync(hba->dev);
	ufshcd_hold(hba, false);

	hba->clk_scaling.is_enabled = value;

	अगर (value) अणु
		ufshcd_resume_clkscaling(hba);
	पूर्ण अन्यथा अणु
		ufshcd_suspend_clkscaling(hba);
		err = ufshcd_devfreq_scale(hba, true);
		अगर (err)
			dev_err(hba->dev, "%s: failed to scale clocks up %d\n",
					__func__, err);
	पूर्ण

	ufshcd_release(hba);
	pm_runसमय_put_sync(hba->dev);
out:
	up(&hba->host_sem);
	वापस err ? err : count;
पूर्ण

अटल व्योम ufshcd_init_clk_scaling_sysfs(काष्ठा ufs_hba *hba)
अणु
	hba->clk_scaling.enable_attr.show = ufshcd_clkscale_enable_show;
	hba->clk_scaling.enable_attr.store = ufshcd_clkscale_enable_store;
	sysfs_attr_init(&hba->clk_scaling.enable_attr.attr);
	hba->clk_scaling.enable_attr.attr.name = "clkscale_enable";
	hba->clk_scaling.enable_attr.attr.mode = 0644;
	अगर (device_create_file(hba->dev, &hba->clk_scaling.enable_attr))
		dev_err(hba->dev, "Failed to create sysfs for clkscale_enable\n");
पूर्ण

अटल व्योम ufshcd_हटाओ_clk_scaling_sysfs(काष्ठा ufs_hba *hba)
अणु
	अगर (hba->clk_scaling.enable_attr.attr.name)
		device_हटाओ_file(hba->dev, &hba->clk_scaling.enable_attr);
पूर्ण

अटल व्योम ufshcd_init_clk_scaling(काष्ठा ufs_hba *hba)
अणु
	अक्षर wq_name[माप("ufs_clkscaling_00")];

	अगर (!ufshcd_is_clkscaling_supported(hba))
		वापस;

	अगर (!hba->clk_scaling.min_gear)
		hba->clk_scaling.min_gear = UFS_HS_G1;

	INIT_WORK(&hba->clk_scaling.suspend_work,
		  ufshcd_clk_scaling_suspend_work);
	INIT_WORK(&hba->clk_scaling.resume_work,
		  ufshcd_clk_scaling_resume_work);

	snम_लिखो(wq_name, माप(wq_name), "ufs_clkscaling_%d",
		 hba->host->host_no);
	hba->clk_scaling.workq = create_singlethपढ़ो_workqueue(wq_name);

	hba->clk_scaling.is_initialized = true;
पूर्ण

अटल व्योम ufshcd_निकास_clk_scaling(काष्ठा ufs_hba *hba)
अणु
	अगर (!hba->clk_scaling.is_initialized)
		वापस;

	ufshcd_हटाओ_clk_scaling_sysfs(hba);
	destroy_workqueue(hba->clk_scaling.workq);
	ufshcd_devfreq_हटाओ(hba);
	hba->clk_scaling.is_initialized = false;
पूर्ण

अटल व्योम ufshcd_ungate_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	काष्ठा ufs_hba *hba = container_of(work, काष्ठा ufs_hba,
			clk_gating.ungate_work);

	cancel_delayed_work_sync(&hba->clk_gating.gate_work);

	spin_lock_irqsave(hba->host->host_lock, flags);
	अगर (hba->clk_gating.state == CLKS_ON) अणु
		spin_unlock_irqrestore(hba->host->host_lock, flags);
		जाओ unblock_reqs;
	पूर्ण

	spin_unlock_irqrestore(hba->host->host_lock, flags);
	ufshcd_hba_vreg_set_hpm(hba);
	ufshcd_setup_घड़ीs(hba, true);

	ufshcd_enable_irq(hba);

	/* Exit from hibern8 */
	अगर (ufshcd_can_hibern8_during_gating(hba)) अणु
		/* Prevent gating in this path */
		hba->clk_gating.is_suspended = true;
		अगर (ufshcd_is_link_hibern8(hba)) अणु
			ret = ufshcd_uic_hibern8_निकास(hba);
			अगर (ret)
				dev_err(hba->dev, "%s: hibern8 exit failed %d\n",
					__func__, ret);
			अन्यथा
				ufshcd_set_link_active(hba);
		पूर्ण
		hba->clk_gating.is_suspended = false;
	पूर्ण
unblock_reqs:
	ufshcd_scsi_unblock_requests(hba);
पूर्ण

/**
 * ufshcd_hold - Enable घड़ीs that were gated earlier due to ufshcd_release.
 * Also, निकास from hibern8 mode and set the link as active.
 * @hba: per adapter instance
 * @async: This indicates whether caller should ungate घड़ीs asynchronously.
 */
पूर्णांक ufshcd_hold(काष्ठा ufs_hba *hba, bool async)
अणु
	पूर्णांक rc = 0;
	bool flush_result;
	अचिन्हित दीर्घ flags;

	अगर (!ufshcd_is_clkgating_allowed(hba))
		जाओ out;
	spin_lock_irqsave(hba->host->host_lock, flags);
	hba->clk_gating.active_reqs++;

start:
	चयन (hba->clk_gating.state) अणु
	हाल CLKS_ON:
		/*
		 * Wait क्रम the ungate work to complete अगर in progress.
		 * Though the घड़ीs may be in ON state, the link could
		 * still be in hibner8 state अगर hibern8 is allowed
		 * during घड़ी gating.
		 * Make sure we निकास hibern8 state also in addition to
		 * घड़ीs being ON.
		 */
		अगर (ufshcd_can_hibern8_during_gating(hba) &&
		    ufshcd_is_link_hibern8(hba)) अणु
			अगर (async) अणु
				rc = -EAGAIN;
				hba->clk_gating.active_reqs--;
				अवरोध;
			पूर्ण
			spin_unlock_irqrestore(hba->host->host_lock, flags);
			flush_result = flush_work(&hba->clk_gating.ungate_work);
			अगर (hba->clk_gating.is_suspended && !flush_result)
				जाओ out;
			spin_lock_irqsave(hba->host->host_lock, flags);
			जाओ start;
		पूर्ण
		अवरोध;
	हाल REQ_CLKS_OFF:
		अगर (cancel_delayed_work(&hba->clk_gating.gate_work)) अणु
			hba->clk_gating.state = CLKS_ON;
			trace_ufshcd_clk_gating(dev_name(hba->dev),
						hba->clk_gating.state);
			अवरोध;
		पूर्ण
		/*
		 * If we are here, it means gating work is either करोne or
		 * currently running. Hence, fall through to cancel gating
		 * work and to enable घड़ीs.
		 */
		fallthrough;
	हाल CLKS_OFF:
		hba->clk_gating.state = REQ_CLKS_ON;
		trace_ufshcd_clk_gating(dev_name(hba->dev),
					hba->clk_gating.state);
		अगर (queue_work(hba->clk_gating.clk_gating_workq,
			       &hba->clk_gating.ungate_work))
			ufshcd_scsi_block_requests(hba);
		/*
		 * fall through to check अगर we should रुको क्रम this
		 * work to be करोne or not.
		 */
		fallthrough;
	हाल REQ_CLKS_ON:
		अगर (async) अणु
			rc = -EAGAIN;
			hba->clk_gating.active_reqs--;
			अवरोध;
		पूर्ण

		spin_unlock_irqrestore(hba->host->host_lock, flags);
		flush_work(&hba->clk_gating.ungate_work);
		/* Make sure state is CLKS_ON beक्रमe वापसing */
		spin_lock_irqsave(hba->host->host_lock, flags);
		जाओ start;
	शेष:
		dev_err(hba->dev, "%s: clk gating is in invalid state %d\n",
				__func__, hba->clk_gating.state);
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(hba->host->host_lock, flags);
out:
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_hold);

अटल व्योम ufshcd_gate_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ufs_hba *hba = container_of(work, काष्ठा ufs_hba,
			clk_gating.gate_work.work);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(hba->host->host_lock, flags);
	/*
	 * In हाल you are here to cancel this work the gating state
	 * would be marked as REQ_CLKS_ON. In this हाल save समय by
	 * skipping the gating work and निकास after changing the घड़ी
	 * state to CLKS_ON.
	 */
	अगर (hba->clk_gating.is_suspended ||
		(hba->clk_gating.state != REQ_CLKS_OFF)) अणु
		hba->clk_gating.state = CLKS_ON;
		trace_ufshcd_clk_gating(dev_name(hba->dev),
					hba->clk_gating.state);
		जाओ rel_lock;
	पूर्ण

	अगर (hba->clk_gating.active_reqs
		|| hba->ufshcd_state != UFSHCD_STATE_OPERATIONAL
		|| ufshcd_any_tag_in_use(hba) || hba->outstanding_tasks
		|| hba->active_uic_cmd || hba->uic_async_करोne)
		जाओ rel_lock;

	spin_unlock_irqrestore(hba->host->host_lock, flags);

	/* put the link पूर्णांकo hibern8 mode beक्रमe turning off घड़ीs */
	अगर (ufshcd_can_hibern8_during_gating(hba)) अणु
		ret = ufshcd_uic_hibern8_enter(hba);
		अगर (ret) अणु
			hba->clk_gating.state = CLKS_ON;
			dev_err(hba->dev, "%s: hibern8 enter failed %d\n",
					__func__, ret);
			trace_ufshcd_clk_gating(dev_name(hba->dev),
						hba->clk_gating.state);
			जाओ out;
		पूर्ण
		ufshcd_set_link_hibern8(hba);
	पूर्ण

	ufshcd_disable_irq(hba);

	ufshcd_setup_घड़ीs(hba, false);

	/* Put the host controller in low घातer mode अगर possible */
	ufshcd_hba_vreg_set_lpm(hba);
	/*
	 * In हाल you are here to cancel this work the gating state
	 * would be marked as REQ_CLKS_ON. In this हाल keep the state
	 * as REQ_CLKS_ON which would anyway imply that घड़ीs are off
	 * and a request to turn them on is pending. By करोing this way,
	 * we keep the state machine in tact and this would ultimately
	 * prevent from करोing cancel work multiple बार when there are
	 * new requests arriving beक्रमe the current cancel work is करोne.
	 */
	spin_lock_irqsave(hba->host->host_lock, flags);
	अगर (hba->clk_gating.state == REQ_CLKS_OFF) अणु
		hba->clk_gating.state = CLKS_OFF;
		trace_ufshcd_clk_gating(dev_name(hba->dev),
					hba->clk_gating.state);
	पूर्ण
rel_lock:
	spin_unlock_irqrestore(hba->host->host_lock, flags);
out:
	वापस;
पूर्ण

/* host lock must be held beक्रमe calling this variant */
अटल व्योम __ufshcd_release(काष्ठा ufs_hba *hba)
अणु
	अगर (!ufshcd_is_clkgating_allowed(hba))
		वापस;

	hba->clk_gating.active_reqs--;

	अगर (hba->clk_gating.active_reqs || hba->clk_gating.is_suspended ||
	    hba->ufshcd_state != UFSHCD_STATE_OPERATIONAL ||
	    hba->outstanding_tasks ||
	    hba->active_uic_cmd || hba->uic_async_करोne ||
	    hba->clk_gating.state == CLKS_OFF)
		वापस;

	hba->clk_gating.state = REQ_CLKS_OFF;
	trace_ufshcd_clk_gating(dev_name(hba->dev), hba->clk_gating.state);
	queue_delayed_work(hba->clk_gating.clk_gating_workq,
			   &hba->clk_gating.gate_work,
			   msecs_to_jअगरfies(hba->clk_gating.delay_ms));
पूर्ण

व्योम ufshcd_release(काष्ठा ufs_hba *hba)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(hba->host->host_lock, flags);
	__ufshcd_release(hba);
	spin_unlock_irqrestore(hba->host->host_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_release);

अटल sमाप_प्रकार ufshcd_clkgate_delay_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%lu\n", hba->clk_gating.delay_ms);
पूर्ण

अटल sमाप_प्रकार ufshcd_clkgate_delay_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags, value;

	अगर (kम_से_अदीर्घ(buf, 0, &value))
		वापस -EINVAL;

	spin_lock_irqsave(hba->host->host_lock, flags);
	hba->clk_gating.delay_ms = value;
	spin_unlock_irqrestore(hba->host->host_lock, flags);
	वापस count;
पूर्ण

अटल sमाप_प्रकार ufshcd_clkgate_enable_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%d\n", hba->clk_gating.is_enabled);
पूर्ण

अटल sमाप_प्रकार ufshcd_clkgate_enable_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	u32 value;

	अगर (kstrtou32(buf, 0, &value))
		वापस -EINVAL;

	value = !!value;

	spin_lock_irqsave(hba->host->host_lock, flags);
	अगर (value == hba->clk_gating.is_enabled)
		जाओ out;

	अगर (value)
		__ufshcd_release(hba);
	अन्यथा
		hba->clk_gating.active_reqs++;

	hba->clk_gating.is_enabled = value;
out:
	spin_unlock_irqrestore(hba->host->host_lock, flags);
	वापस count;
पूर्ण

अटल व्योम ufshcd_init_clk_gating_sysfs(काष्ठा ufs_hba *hba)
अणु
	hba->clk_gating.delay_attr.show = ufshcd_clkgate_delay_show;
	hba->clk_gating.delay_attr.store = ufshcd_clkgate_delay_store;
	sysfs_attr_init(&hba->clk_gating.delay_attr.attr);
	hba->clk_gating.delay_attr.attr.name = "clkgate_delay_ms";
	hba->clk_gating.delay_attr.attr.mode = 0644;
	अगर (device_create_file(hba->dev, &hba->clk_gating.delay_attr))
		dev_err(hba->dev, "Failed to create sysfs for clkgate_delay\n");

	hba->clk_gating.enable_attr.show = ufshcd_clkgate_enable_show;
	hba->clk_gating.enable_attr.store = ufshcd_clkgate_enable_store;
	sysfs_attr_init(&hba->clk_gating.enable_attr.attr);
	hba->clk_gating.enable_attr.attr.name = "clkgate_enable";
	hba->clk_gating.enable_attr.attr.mode = 0644;
	अगर (device_create_file(hba->dev, &hba->clk_gating.enable_attr))
		dev_err(hba->dev, "Failed to create sysfs for clkgate_enable\n");
पूर्ण

अटल व्योम ufshcd_हटाओ_clk_gating_sysfs(काष्ठा ufs_hba *hba)
अणु
	अगर (hba->clk_gating.delay_attr.attr.name)
		device_हटाओ_file(hba->dev, &hba->clk_gating.delay_attr);
	अगर (hba->clk_gating.enable_attr.attr.name)
		device_हटाओ_file(hba->dev, &hba->clk_gating.enable_attr);
पूर्ण

अटल व्योम ufshcd_init_clk_gating(काष्ठा ufs_hba *hba)
अणु
	अक्षर wq_name[माप("ufs_clk_gating_00")];

	अगर (!ufshcd_is_clkgating_allowed(hba))
		वापस;

	hba->clk_gating.state = CLKS_ON;

	hba->clk_gating.delay_ms = 150;
	INIT_DELAYED_WORK(&hba->clk_gating.gate_work, ufshcd_gate_work);
	INIT_WORK(&hba->clk_gating.ungate_work, ufshcd_ungate_work);

	snम_लिखो(wq_name, ARRAY_SIZE(wq_name), "ufs_clk_gating_%d",
		 hba->host->host_no);
	hba->clk_gating.clk_gating_workq = alloc_ordered_workqueue(wq_name,
					WQ_MEM_RECLAIM | WQ_HIGHPRI);

	ufshcd_init_clk_gating_sysfs(hba);

	hba->clk_gating.is_enabled = true;
	hba->clk_gating.is_initialized = true;
पूर्ण

अटल व्योम ufshcd_निकास_clk_gating(काष्ठा ufs_hba *hba)
अणु
	अगर (!hba->clk_gating.is_initialized)
		वापस;
	ufshcd_हटाओ_clk_gating_sysfs(hba);
	cancel_work_sync(&hba->clk_gating.ungate_work);
	cancel_delayed_work_sync(&hba->clk_gating.gate_work);
	destroy_workqueue(hba->clk_gating.clk_gating_workq);
	hba->clk_gating.is_initialized = false;
पूर्ण

/* Must be called with host lock acquired */
अटल व्योम ufshcd_clk_scaling_start_busy(काष्ठा ufs_hba *hba)
अणु
	bool queue_resume_work = false;
	kसमय_प्रकार curr_t = kसमय_get();

	अगर (!ufshcd_is_clkscaling_supported(hba))
		वापस;

	अगर (!hba->clk_scaling.active_reqs++)
		queue_resume_work = true;

	अगर (!hba->clk_scaling.is_enabled || hba->pm_op_in_progress)
		वापस;

	अगर (queue_resume_work)
		queue_work(hba->clk_scaling.workq,
			   &hba->clk_scaling.resume_work);

	अगर (!hba->clk_scaling.winकरोw_start_t) अणु
		hba->clk_scaling.winकरोw_start_t = curr_t;
		hba->clk_scaling.tot_busy_t = 0;
		hba->clk_scaling.is_busy_started = false;
	पूर्ण

	अगर (!hba->clk_scaling.is_busy_started) अणु
		hba->clk_scaling.busy_start_t = curr_t;
		hba->clk_scaling.is_busy_started = true;
	पूर्ण
पूर्ण

अटल व्योम ufshcd_clk_scaling_update_busy(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_clk_scaling *scaling = &hba->clk_scaling;

	अगर (!ufshcd_is_clkscaling_supported(hba))
		वापस;

	अगर (!hba->outstanding_reqs && scaling->is_busy_started) अणु
		scaling->tot_busy_t += kसमय_प्रकारo_us(kसमय_sub(kसमय_get(),
					scaling->busy_start_t));
		scaling->busy_start_t = 0;
		scaling->is_busy_started = false;
	पूर्ण
पूर्ण
/**
 * ufshcd_send_command - Send SCSI or device management commands
 * @hba: per adapter instance
 * @task_tag: Task tag of the command
 */
अटल अंतरभूत
व्योम ufshcd_send_command(काष्ठा ufs_hba *hba, अचिन्हित पूर्णांक task_tag)
अणु
	काष्ठा ufshcd_lrb *lrbp = &hba->lrb[task_tag];

	lrbp->issue_समय_stamp = kसमय_get();
	lrbp->compl_समय_stamp = kसमय_set(0, 0);
	ufshcd_vops_setup_xfer_req(hba, task_tag, (lrbp->cmd ? true : false));
	ufshcd_add_command_trace(hba, task_tag, UFS_CMD_SEND);
	ufshcd_clk_scaling_start_busy(hba);
	__set_bit(task_tag, &hba->outstanding_reqs);
	ufshcd_ग_लिखोl(hba, 1 << task_tag, REG_UTP_TRANSFER_REQ_DOOR_BELL);
	/* Make sure that करोorbell is committed immediately */
	wmb();
पूर्ण

/**
 * ufshcd_copy_sense_data - Copy sense data in हाल of check condition
 * @lrbp: poपूर्णांकer to local reference block
 */
अटल अंतरभूत व्योम ufshcd_copy_sense_data(काष्ठा ufshcd_lrb *lrbp)
अणु
	पूर्णांक len;
	अगर (lrbp->sense_buffer &&
	    ufshcd_get_rsp_upiu_data_seg_len(lrbp->ucd_rsp_ptr)) अणु
		पूर्णांक len_to_copy;

		len = be16_to_cpu(lrbp->ucd_rsp_ptr->sr.sense_data_len);
		len_to_copy = min_t(पूर्णांक, UFS_SENSE_SIZE, len);

		स_नकल(lrbp->sense_buffer, lrbp->ucd_rsp_ptr->sr.sense_data,
		       len_to_copy);
	पूर्ण
पूर्ण

/**
 * ufshcd_copy_query_response() - Copy the Query Response and the data
 * descriptor
 * @hba: per adapter instance
 * @lrbp: poपूर्णांकer to local reference block
 */
अटल
पूर्णांक ufshcd_copy_query_response(काष्ठा ufs_hba *hba, काष्ठा ufshcd_lrb *lrbp)
अणु
	काष्ठा ufs_query_res *query_res = &hba->dev_cmd.query.response;

	स_नकल(&query_res->upiu_res, &lrbp->ucd_rsp_ptr->qr, QUERY_OSF_SIZE);

	/* Get the descriptor */
	अगर (hba->dev_cmd.query.descriptor &&
	    lrbp->ucd_rsp_ptr->qr.opcode == UPIU_QUERY_OPCODE_READ_DESC) अणु
		u8 *descp = (u8 *)lrbp->ucd_rsp_ptr +
				GENERAL_UPIU_REQUEST_SIZE;
		u16 resp_len;
		u16 buf_len;

		/* data segment length */
		resp_len = be32_to_cpu(lrbp->ucd_rsp_ptr->header.dword_2) &
						MASK_QUERY_DATA_SEG_LEN;
		buf_len = be16_to_cpu(
				hba->dev_cmd.query.request.upiu_req.length);
		अगर (likely(buf_len >= resp_len)) अणु
			स_नकल(hba->dev_cmd.query.descriptor, descp, resp_len);
		पूर्ण अन्यथा अणु
			dev_warn(hba->dev,
				 "%s: rsp size %d is bigger than buffer size %d",
				 __func__, resp_len, buf_len);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ufshcd_hba_capabilities - Read controller capabilities
 * @hba: per adapter instance
 *
 * Return: 0 on success, negative on error.
 */
अटल अंतरभूत पूर्णांक ufshcd_hba_capabilities(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err;

	hba->capabilities = ufshcd_पढ़ोl(hba, REG_CONTROLLER_CAPABILITIES);

	/* nutrs and nuपंचांगrs are 0 based values */
	hba->nutrs = (hba->capabilities & MASK_TRANSFER_REQUESTS_SLOTS) + 1;
	hba->nuपंचांगrs =
	((hba->capabilities & MASK_TASK_MANAGEMENT_REQUEST_SLOTS) >> 16) + 1;

	/* Read crypto capabilities */
	err = ufshcd_hba_init_crypto_capabilities(hba);
	अगर (err)
		dev_err(hba->dev, "crypto setup failed\n");

	वापस err;
पूर्ण

/**
 * ufshcd_पढ़ोy_क्रम_uic_cmd - Check अगर controller is पढ़ोy
 *                            to accept UIC commands
 * @hba: per adapter instance
 * Return true on success, अन्यथा false
 */
अटल अंतरभूत bool ufshcd_पढ़ोy_क्रम_uic_cmd(काष्ठा ufs_hba *hba)
अणु
	अगर (ufshcd_पढ़ोl(hba, REG_CONTROLLER_STATUS) & UIC_COMMAND_READY)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/**
 * ufshcd_get_upmcrs - Get the घातer mode change request status
 * @hba: Poपूर्णांकer to adapter instance
 *
 * This function माला_लो the UPMCRS field of HCS रेजिस्टर
 * Returns value of UPMCRS field
 */
अटल अंतरभूत u8 ufshcd_get_upmcrs(काष्ठा ufs_hba *hba)
अणु
	वापस (ufshcd_पढ़ोl(hba, REG_CONTROLLER_STATUS) >> 8) & 0x7;
पूर्ण

/**
 * ufshcd_dispatch_uic_cmd - Dispatch UIC commands to unipro layers
 * @hba: per adapter instance
 * @uic_cmd: UIC command
 *
 * Mutex must be held.
 */
अटल अंतरभूत व्योम
ufshcd_dispatch_uic_cmd(काष्ठा ufs_hba *hba, काष्ठा uic_command *uic_cmd)
अणु
	WARN_ON(hba->active_uic_cmd);

	hba->active_uic_cmd = uic_cmd;

	/* Write Args */
	ufshcd_ग_लिखोl(hba, uic_cmd->argument1, REG_UIC_COMMAND_ARG_1);
	ufshcd_ग_लिखोl(hba, uic_cmd->argument2, REG_UIC_COMMAND_ARG_2);
	ufshcd_ग_लिखोl(hba, uic_cmd->argument3, REG_UIC_COMMAND_ARG_3);

	ufshcd_add_uic_command_trace(hba, uic_cmd, UFS_CMD_SEND);

	/* Write UIC Cmd */
	ufshcd_ग_लिखोl(hba, uic_cmd->command & COMMAND_OPCODE_MASK,
		      REG_UIC_COMMAND);
पूर्ण

/**
 * ufshcd_रुको_क्रम_uic_cmd - Wait complectioin of UIC command
 * @hba: per adapter instance
 * @uic_cmd: UIC command
 *
 * Must be called with mutex held.
 * Returns 0 only अगर success.
 */
अटल पूर्णांक
ufshcd_रुको_क्रम_uic_cmd(काष्ठा ufs_hba *hba, काष्ठा uic_command *uic_cmd)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	अगर (रुको_क्रम_completion_समयout(&uic_cmd->करोne,
					msecs_to_jअगरfies(UIC_CMD_TIMEOUT))) अणु
		ret = uic_cmd->argument2 & MASK_UIC_COMMAND_RESULT;
	पूर्ण अन्यथा अणु
		ret = -ETIMEDOUT;
		dev_err(hba->dev,
			"uic cmd 0x%x with arg3 0x%x completion timeout\n",
			uic_cmd->command, uic_cmd->argument3);

		अगर (!uic_cmd->cmd_active) अणु
			dev_err(hba->dev, "%s: UIC cmd has been completed, return the result\n",
				__func__);
			ret = uic_cmd->argument2 & MASK_UIC_COMMAND_RESULT;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(hba->host->host_lock, flags);
	hba->active_uic_cmd = शून्य;
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	वापस ret;
पूर्ण

/**
 * __ufshcd_send_uic_cmd - Send UIC commands and retrieve the result
 * @hba: per adapter instance
 * @uic_cmd: UIC command
 * @completion: initialize the completion only अगर this is set to true
 *
 * Identical to ufshcd_send_uic_cmd() expect mutex. Must be called
 * with mutex held and host_lock locked.
 * Returns 0 only अगर success.
 */
अटल पूर्णांक
__ufshcd_send_uic_cmd(काष्ठा ufs_hba *hba, काष्ठा uic_command *uic_cmd,
		      bool completion)
अणु
	अगर (!ufshcd_पढ़ोy_क्रम_uic_cmd(hba)) अणु
		dev_err(hba->dev,
			"Controller not ready to accept UIC commands\n");
		वापस -EIO;
	पूर्ण

	अगर (completion)
		init_completion(&uic_cmd->करोne);

	uic_cmd->cmd_active = 1;
	ufshcd_dispatch_uic_cmd(hba, uic_cmd);

	वापस 0;
पूर्ण

/**
 * ufshcd_send_uic_cmd - Send UIC commands and retrieve the result
 * @hba: per adapter instance
 * @uic_cmd: UIC command
 *
 * Returns 0 only अगर success.
 */
पूर्णांक ufshcd_send_uic_cmd(काष्ठा ufs_hba *hba, काष्ठा uic_command *uic_cmd)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	ufshcd_hold(hba, false);
	mutex_lock(&hba->uic_cmd_mutex);
	ufshcd_add_delay_beक्रमe_dme_cmd(hba);

	spin_lock_irqsave(hba->host->host_lock, flags);
	ret = __ufshcd_send_uic_cmd(hba, uic_cmd, true);
	spin_unlock_irqrestore(hba->host->host_lock, flags);
	अगर (!ret)
		ret = ufshcd_रुको_क्रम_uic_cmd(hba, uic_cmd);

	mutex_unlock(&hba->uic_cmd_mutex);

	ufshcd_release(hba);
	वापस ret;
पूर्ण

/**
 * ufshcd_map_sg - Map scatter-gather list to prdt
 * @hba: per adapter instance
 * @lrbp: poपूर्णांकer to local reference block
 *
 * Returns 0 in हाल of success, non-zero value in हाल of failure
 */
अटल पूर्णांक ufshcd_map_sg(काष्ठा ufs_hba *hba, काष्ठा ufshcd_lrb *lrbp)
अणु
	काष्ठा ufshcd_sg_entry *prd_table;
	काष्ठा scatterlist *sg;
	काष्ठा scsi_cmnd *cmd;
	पूर्णांक sg_segments;
	पूर्णांक i;

	cmd = lrbp->cmd;
	sg_segments = scsi_dma_map(cmd);
	अगर (sg_segments < 0)
		वापस sg_segments;

	अगर (sg_segments) अणु

		अगर (hba->quirks & UFSHCD_QUIRK_PRDT_BYTE_GRAN)
			lrbp->utr_descriptor_ptr->prd_table_length =
				cpu_to_le16((sg_segments *
					माप(काष्ठा ufshcd_sg_entry)));
		अन्यथा
			lrbp->utr_descriptor_ptr->prd_table_length =
				cpu_to_le16((u16) (sg_segments));

		prd_table = (काष्ठा ufshcd_sg_entry *)lrbp->ucd_prdt_ptr;

		scsi_क्रम_each_sg(cmd, sg, sg_segments, i) अणु
			prd_table[i].size  =
				cpu_to_le32(((u32) sg_dma_len(sg))-1);
			prd_table[i].base_addr =
				cpu_to_le32(lower_32_bits(sg->dma_address));
			prd_table[i].upper_addr =
				cpu_to_le32(upper_32_bits(sg->dma_address));
			prd_table[i].reserved = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		lrbp->utr_descriptor_ptr->prd_table_length = 0;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ufshcd_enable_पूर्णांकr - enable पूर्णांकerrupts
 * @hba: per adapter instance
 * @पूर्णांकrs: पूर्णांकerrupt bits
 */
अटल व्योम ufshcd_enable_पूर्णांकr(काष्ठा ufs_hba *hba, u32 पूर्णांकrs)
अणु
	u32 set = ufshcd_पढ़ोl(hba, REG_INTERRUPT_ENABLE);

	अगर (hba->ufs_version == ufshci_version(1, 0)) अणु
		u32 rw;
		rw = set & INTERRUPT_MASK_RW_VER_10;
		set = rw | ((set ^ पूर्णांकrs) & पूर्णांकrs);
	पूर्ण अन्यथा अणु
		set |= पूर्णांकrs;
	पूर्ण

	ufshcd_ग_लिखोl(hba, set, REG_INTERRUPT_ENABLE);
पूर्ण

/**
 * ufshcd_disable_पूर्णांकr - disable पूर्णांकerrupts
 * @hba: per adapter instance
 * @पूर्णांकrs: पूर्णांकerrupt bits
 */
अटल व्योम ufshcd_disable_पूर्णांकr(काष्ठा ufs_hba *hba, u32 पूर्णांकrs)
अणु
	u32 set = ufshcd_पढ़ोl(hba, REG_INTERRUPT_ENABLE);

	अगर (hba->ufs_version == ufshci_version(1, 0)) अणु
		u32 rw;
		rw = (set & INTERRUPT_MASK_RW_VER_10) &
			~(पूर्णांकrs & INTERRUPT_MASK_RW_VER_10);
		set = rw | ((set & पूर्णांकrs) & ~INTERRUPT_MASK_RW_VER_10);

	पूर्ण अन्यथा अणु
		set &= ~पूर्णांकrs;
	पूर्ण

	ufshcd_ग_लिखोl(hba, set, REG_INTERRUPT_ENABLE);
पूर्ण

/**
 * ufshcd_prepare_req_desc_hdr() - Fills the requests header
 * descriptor according to request
 * @lrbp: poपूर्णांकer to local reference block
 * @upiu_flags: flags required in the header
 * @cmd_dir: requests data direction
 */
अटल व्योम ufshcd_prepare_req_desc_hdr(काष्ठा ufshcd_lrb *lrbp,
			u8 *upiu_flags, क्रमागत dma_data_direction cmd_dir)
अणु
	काष्ठा utp_transfer_req_desc *req_desc = lrbp->utr_descriptor_ptr;
	u32 data_direction;
	u32 dword_0;
	u32 dword_1 = 0;
	u32 dword_3 = 0;

	अगर (cmd_dir == DMA_FROM_DEVICE) अणु
		data_direction = UTP_DEVICE_TO_HOST;
		*upiu_flags = UPIU_CMD_FLAGS_READ;
	पूर्ण अन्यथा अगर (cmd_dir == DMA_TO_DEVICE) अणु
		data_direction = UTP_HOST_TO_DEVICE;
		*upiu_flags = UPIU_CMD_FLAGS_WRITE;
	पूर्ण अन्यथा अणु
		data_direction = UTP_NO_DATA_TRANSFER;
		*upiu_flags = UPIU_CMD_FLAGS_NONE;
	पूर्ण

	dword_0 = data_direction | (lrbp->command_type
				<< UPIU_COMMAND_TYPE_OFFSET);
	अगर (lrbp->पूर्णांकr_cmd)
		dword_0 |= UTP_REQ_DESC_INT_CMD;

	/* Prepare crypto related dwords */
	ufshcd_prepare_req_desc_hdr_crypto(lrbp, &dword_0, &dword_1, &dword_3);

	/* Transfer request descriptor header fields */
	req_desc->header.dword_0 = cpu_to_le32(dword_0);
	req_desc->header.dword_1 = cpu_to_le32(dword_1);
	/*
	 * assigning invalid value क्रम command status. Controller
	 * updates OCS on command completion, with the command
	 * status
	 */
	req_desc->header.dword_2 =
		cpu_to_le32(OCS_INVALID_COMMAND_STATUS);
	req_desc->header.dword_3 = cpu_to_le32(dword_3);

	req_desc->prd_table_length = 0;
पूर्ण

/**
 * ufshcd_prepare_utp_scsi_cmd_upiu() - fills the utp_transfer_req_desc,
 * क्रम scsi commands
 * @lrbp: local reference block poपूर्णांकer
 * @upiu_flags: flags
 */
अटल
व्योम ufshcd_prepare_utp_scsi_cmd_upiu(काष्ठा ufshcd_lrb *lrbp, u8 upiu_flags)
अणु
	काष्ठा scsi_cmnd *cmd = lrbp->cmd;
	काष्ठा utp_upiu_req *ucd_req_ptr = lrbp->ucd_req_ptr;
	अचिन्हित लघु cdb_len;

	/* command descriptor fields */
	ucd_req_ptr->header.dword_0 = UPIU_HEADER_DWORD(
				UPIU_TRANSACTION_COMMAND, upiu_flags,
				lrbp->lun, lrbp->task_tag);
	ucd_req_ptr->header.dword_1 = UPIU_HEADER_DWORD(
				UPIU_COMMAND_SET_TYPE_SCSI, 0, 0, 0);

	/* Total EHS length and Data segment length will be zero */
	ucd_req_ptr->header.dword_2 = 0;

	ucd_req_ptr->sc.exp_data_transfer_len = cpu_to_be32(cmd->sdb.length);

	cdb_len = min_t(अचिन्हित लघु, cmd->cmd_len, UFS_CDB_SIZE);
	स_रखो(ucd_req_ptr->sc.cdb, 0, UFS_CDB_SIZE);
	स_नकल(ucd_req_ptr->sc.cdb, cmd->cmnd, cdb_len);

	स_रखो(lrbp->ucd_rsp_ptr, 0, माप(काष्ठा utp_upiu_rsp));
पूर्ण

/**
 * ufshcd_prepare_utp_query_req_upiu() - fills the utp_transfer_req_desc,
 * क्रम query requsts
 * @hba: UFS hba
 * @lrbp: local reference block poपूर्णांकer
 * @upiu_flags: flags
 */
अटल व्योम ufshcd_prepare_utp_query_req_upiu(काष्ठा ufs_hba *hba,
				काष्ठा ufshcd_lrb *lrbp, u8 upiu_flags)
अणु
	काष्ठा utp_upiu_req *ucd_req_ptr = lrbp->ucd_req_ptr;
	काष्ठा ufs_query *query = &hba->dev_cmd.query;
	u16 len = be16_to_cpu(query->request.upiu_req.length);

	/* Query request header */
	ucd_req_ptr->header.dword_0 = UPIU_HEADER_DWORD(
			UPIU_TRANSACTION_QUERY_REQ, upiu_flags,
			lrbp->lun, lrbp->task_tag);
	ucd_req_ptr->header.dword_1 = UPIU_HEADER_DWORD(
			0, query->request.query_func, 0, 0);

	/* Data segment length only need क्रम WRITE_DESC */
	अगर (query->request.upiu_req.opcode == UPIU_QUERY_OPCODE_WRITE_DESC)
		ucd_req_ptr->header.dword_2 =
			UPIU_HEADER_DWORD(0, 0, (len >> 8), (u8)len);
	अन्यथा
		ucd_req_ptr->header.dword_2 = 0;

	/* Copy the Query Request buffer as is */
	स_नकल(&ucd_req_ptr->qr, &query->request.upiu_req,
			QUERY_OSF_SIZE);

	/* Copy the Descriptor */
	अगर (query->request.upiu_req.opcode == UPIU_QUERY_OPCODE_WRITE_DESC)
		स_नकल(ucd_req_ptr + 1, query->descriptor, len);

	स_रखो(lrbp->ucd_rsp_ptr, 0, माप(काष्ठा utp_upiu_rsp));
पूर्ण

अटल अंतरभूत व्योम ufshcd_prepare_utp_nop_upiu(काष्ठा ufshcd_lrb *lrbp)
अणु
	काष्ठा utp_upiu_req *ucd_req_ptr = lrbp->ucd_req_ptr;

	स_रखो(ucd_req_ptr, 0, माप(काष्ठा utp_upiu_req));

	/* command descriptor fields */
	ucd_req_ptr->header.dword_0 =
		UPIU_HEADER_DWORD(
			UPIU_TRANSACTION_NOP_OUT, 0, 0, lrbp->task_tag);
	/* clear rest of the fields of basic header */
	ucd_req_ptr->header.dword_1 = 0;
	ucd_req_ptr->header.dword_2 = 0;

	स_रखो(lrbp->ucd_rsp_ptr, 0, माप(काष्ठा utp_upiu_rsp));
पूर्ण

/**
 * ufshcd_compose_devman_upiu - UFS Protocol Inक्रमmation Unit(UPIU)
 *			     क्रम Device Management Purposes
 * @hba: per adapter instance
 * @lrbp: poपूर्णांकer to local reference block
 */
अटल पूर्णांक ufshcd_compose_devman_upiu(काष्ठा ufs_hba *hba,
				      काष्ठा ufshcd_lrb *lrbp)
अणु
	u8 upiu_flags;
	पूर्णांक ret = 0;

	अगर (hba->ufs_version <= ufshci_version(1, 1))
		lrbp->command_type = UTP_CMD_TYPE_DEV_MANAGE;
	अन्यथा
		lrbp->command_type = UTP_CMD_TYPE_UFS_STORAGE;

	ufshcd_prepare_req_desc_hdr(lrbp, &upiu_flags, DMA_NONE);
	अगर (hba->dev_cmd.type == DEV_CMD_TYPE_QUERY)
		ufshcd_prepare_utp_query_req_upiu(hba, lrbp, upiu_flags);
	अन्यथा अगर (hba->dev_cmd.type == DEV_CMD_TYPE_NOP)
		ufshcd_prepare_utp_nop_upiu(lrbp);
	अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण

/**
 * ufshcd_comp_scsi_upiu - UFS Protocol Inक्रमmation Unit(UPIU)
 *			   क्रम SCSI Purposes
 * @hba: per adapter instance
 * @lrbp: poपूर्णांकer to local reference block
 */
अटल पूर्णांक ufshcd_comp_scsi_upiu(काष्ठा ufs_hba *hba, काष्ठा ufshcd_lrb *lrbp)
अणु
	u8 upiu_flags;
	पूर्णांक ret = 0;

	अगर (hba->ufs_version <= ufshci_version(1, 1))
		lrbp->command_type = UTP_CMD_TYPE_SCSI;
	अन्यथा
		lrbp->command_type = UTP_CMD_TYPE_UFS_STORAGE;

	अगर (likely(lrbp->cmd)) अणु
		ufshcd_prepare_req_desc_hdr(lrbp, &upiu_flags,
						lrbp->cmd->sc_data_direction);
		ufshcd_prepare_utp_scsi_cmd_upiu(lrbp, upiu_flags);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ufshcd_upiu_wlun_to_scsi_wlun - maps UPIU W-LUN id to SCSI W-LUN ID
 * @upiu_wlun_id: UPIU W-LUN id
 *
 * Returns SCSI W-LUN id
 */
अटल अंतरभूत u16 ufshcd_upiu_wlun_to_scsi_wlun(u8 upiu_wlun_id)
अणु
	वापस (upiu_wlun_id & ~UFS_UPIU_WLUN_ID) | SCSI_W_LUN_BASE;
पूर्ण

अटल व्योम ufshcd_init_lrb(काष्ठा ufs_hba *hba, काष्ठा ufshcd_lrb *lrb, पूर्णांक i)
अणु
	काष्ठा utp_transfer_cmd_desc *cmd_descp = hba->ucdl_base_addr;
	काष्ठा utp_transfer_req_desc *utrdlp = hba->utrdl_base_addr;
	dma_addr_t cmd_desc_element_addr = hba->ucdl_dma_addr +
		i * माप(काष्ठा utp_transfer_cmd_desc);
	u16 response_offset = दुरत्व(काष्ठा utp_transfer_cmd_desc,
				       response_upiu);
	u16 prdt_offset = दुरत्व(काष्ठा utp_transfer_cmd_desc, prd_table);

	lrb->utr_descriptor_ptr = utrdlp + i;
	lrb->utrd_dma_addr = hba->utrdl_dma_addr +
		i * माप(काष्ठा utp_transfer_req_desc);
	lrb->ucd_req_ptr = (काष्ठा utp_upiu_req *)(cmd_descp + i);
	lrb->ucd_req_dma_addr = cmd_desc_element_addr;
	lrb->ucd_rsp_ptr = (काष्ठा utp_upiu_rsp *)cmd_descp[i].response_upiu;
	lrb->ucd_rsp_dma_addr = cmd_desc_element_addr + response_offset;
	lrb->ucd_prdt_ptr = (काष्ठा ufshcd_sg_entry *)cmd_descp[i].prd_table;
	lrb->ucd_prdt_dma_addr = cmd_desc_element_addr + prdt_offset;
पूर्ण

/**
 * ufshcd_queuecommand - मुख्य entry poपूर्णांक क्रम SCSI requests
 * @host: SCSI host poपूर्णांकer
 * @cmd: command from SCSI Midlayer
 *
 * Returns 0 क्रम success, non-zero in हाल of failure
 */
अटल पूर्णांक ufshcd_queuecommand(काष्ठा Scsi_Host *host, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा ufshcd_lrb *lrbp;
	काष्ठा ufs_hba *hba;
	अचिन्हित दीर्घ flags;
	पूर्णांक tag;
	पूर्णांक err = 0;

	hba = shost_priv(host);

	tag = cmd->request->tag;
	अगर (!ufshcd_valid_tag(hba, tag)) अणु
		dev_err(hba->dev,
			"%s: invalid command tag %d: cmd=0x%p, cmd->request=0x%p",
			__func__, tag, cmd, cmd->request);
		BUG();
	पूर्ण

	अगर (!करोwn_पढ़ो_trylock(&hba->clk_scaling_lock))
		वापस SCSI_MLQUEUE_HOST_BUSY;

	hba->req_पात_count = 0;

	err = ufshcd_hold(hba, true);
	अगर (err) अणु
		err = SCSI_MLQUEUE_HOST_BUSY;
		जाओ out;
	पूर्ण
	WARN_ON(ufshcd_is_clkgating_allowed(hba) &&
		(hba->clk_gating.state != CLKS_ON));

	lrbp = &hba->lrb[tag];
	अगर (unlikely(lrbp->in_use)) अणु
		अगर (hba->pm_op_in_progress)
			set_host_byte(cmd, DID_BAD_TARGET);
		अन्यथा
			err = SCSI_MLQUEUE_HOST_BUSY;
		ufshcd_release(hba);
		जाओ out;
	पूर्ण

	WARN_ON(lrbp->cmd);
	lrbp->cmd = cmd;
	lrbp->sense_bufflen = UFS_SENSE_SIZE;
	lrbp->sense_buffer = cmd->sense_buffer;
	lrbp->task_tag = tag;
	lrbp->lun = ufshcd_scsi_to_upiu_lun(cmd->device->lun);
	lrbp->पूर्णांकr_cmd = !ufshcd_is_पूर्णांकr_aggr_allowed(hba) ? true : false;

	ufshcd_prepare_lrbp_crypto(cmd->request, lrbp);

	lrbp->req_पात_skip = false;

	ufshcd_comp_scsi_upiu(hba, lrbp);

	err = ufshcd_map_sg(hba, lrbp);
	अगर (err) अणु
		lrbp->cmd = शून्य;
		ufshcd_release(hba);
		जाओ out;
	पूर्ण
	/* Make sure descriptors are पढ़ोy beक्रमe ringing the करोorbell */
	wmb();

	spin_lock_irqsave(hba->host->host_lock, flags);
	चयन (hba->ufshcd_state) अणु
	हाल UFSHCD_STATE_OPERATIONAL:
	हाल UFSHCD_STATE_EH_SCHEDULED_NON_FATAL:
		अवरोध;
	हाल UFSHCD_STATE_EH_SCHEDULED_FATAL:
		/*
		 * pm_runसमय_get_sync() is used at error handling preparation
		 * stage. If a scsi cmd, e.g. the SSU cmd, is sent from hba's
		 * PM ops, it can never be finished अगर we let SCSI layer keep
		 * retrying it, which माला_लो err handler stuck क्रमever. Neither
		 * can we let the scsi cmd pass through, because UFS is in bad
		 * state, the scsi cmd may eventually समय out, which will get
		 * err handler blocked क्रम too दीर्घ. So, just fail the scsi cmd
		 * sent from PM ops, err handler can recover PM error anyways.
		 */
		अगर (hba->pm_op_in_progress) अणु
			hba->क्रमce_reset = true;
			set_host_byte(cmd, DID_BAD_TARGET);
			जाओ out_compl_cmd;
		पूर्ण
		fallthrough;
	हाल UFSHCD_STATE_RESET:
		err = SCSI_MLQUEUE_HOST_BUSY;
		जाओ out_compl_cmd;
	हाल UFSHCD_STATE_ERROR:
		set_host_byte(cmd, DID_ERROR);
		जाओ out_compl_cmd;
	शेष:
		dev_WARN_ONCE(hba->dev, 1, "%s: invalid state %d\n",
				__func__, hba->ufshcd_state);
		set_host_byte(cmd, DID_BAD_TARGET);
		जाओ out_compl_cmd;
	पूर्ण
	ufshcd_send_command(hba, tag);
	spin_unlock_irqrestore(hba->host->host_lock, flags);
	जाओ out;

out_compl_cmd:
	scsi_dma_unmap(lrbp->cmd);
	lrbp->cmd = शून्य;
	spin_unlock_irqrestore(hba->host->host_lock, flags);
	ufshcd_release(hba);
	अगर (!err)
		cmd->scsi_करोne(cmd);
out:
	up_पढ़ो(&hba->clk_scaling_lock);
	वापस err;
पूर्ण

अटल पूर्णांक ufshcd_compose_dev_cmd(काष्ठा ufs_hba *hba,
		काष्ठा ufshcd_lrb *lrbp, क्रमागत dev_cmd_type cmd_type, पूर्णांक tag)
अणु
	lrbp->cmd = शून्य;
	lrbp->sense_bufflen = 0;
	lrbp->sense_buffer = शून्य;
	lrbp->task_tag = tag;
	lrbp->lun = 0; /* device management cmd is not specअगरic to any LUN */
	lrbp->पूर्णांकr_cmd = true; /* No पूर्णांकerrupt aggregation */
	ufshcd_prepare_lrbp_crypto(शून्य, lrbp);
	hba->dev_cmd.type = cmd_type;

	वापस ufshcd_compose_devman_upiu(hba, lrbp);
पूर्ण

अटल पूर्णांक
ufshcd_clear_cmd(काष्ठा ufs_hba *hba, पूर्णांक tag)
अणु
	पूर्णांक err = 0;
	अचिन्हित दीर्घ flags;
	u32 mask = 1 << tag;

	/* clear outstanding transaction beक्रमe retry */
	spin_lock_irqsave(hba->host->host_lock, flags);
	ufshcd_utrl_clear(hba, tag);
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	/*
	 * रुको क्रम क्रम h/w to clear corresponding bit in करोor-bell.
	 * max. रुको is 1 sec.
	 */
	err = ufshcd_रुको_क्रम_रेजिस्टर(hba,
			REG_UTP_TRANSFER_REQ_DOOR_BELL,
			mask, ~mask, 1000, 1000);

	वापस err;
पूर्ण

अटल पूर्णांक
ufshcd_check_query_response(काष्ठा ufs_hba *hba, काष्ठा ufshcd_lrb *lrbp)
अणु
	काष्ठा ufs_query_res *query_res = &hba->dev_cmd.query.response;

	/* Get the UPIU response */
	query_res->response = ufshcd_get_rsp_upiu_result(lrbp->ucd_rsp_ptr) >>
				UPIU_RSP_CODE_OFFSET;
	वापस query_res->response;
पूर्ण

/**
 * ufshcd_dev_cmd_completion() - handles device management command responses
 * @hba: per adapter instance
 * @lrbp: poपूर्णांकer to local reference block
 */
अटल पूर्णांक
ufshcd_dev_cmd_completion(काष्ठा ufs_hba *hba, काष्ठा ufshcd_lrb *lrbp)
अणु
	पूर्णांक resp;
	पूर्णांक err = 0;

	hba->ufs_stats.last_hibern8_निकास_tstamp = kसमय_set(0, 0);
	resp = ufshcd_get_req_rsp(lrbp->ucd_rsp_ptr);

	चयन (resp) अणु
	हाल UPIU_TRANSACTION_NOP_IN:
		अगर (hba->dev_cmd.type != DEV_CMD_TYPE_NOP) अणु
			err = -EINVAL;
			dev_err(hba->dev, "%s: unexpected response %x\n",
					__func__, resp);
		पूर्ण
		अवरोध;
	हाल UPIU_TRANSACTION_QUERY_RSP:
		err = ufshcd_check_query_response(hba, lrbp);
		अगर (!err)
			err = ufshcd_copy_query_response(hba, lrbp);
		अवरोध;
	हाल UPIU_TRANSACTION_REJECT_UPIU:
		/* TODO: handle Reject UPIU Response */
		err = -EPERM;
		dev_err(hba->dev, "%s: Reject UPIU not fully implemented\n",
				__func__);
		अवरोध;
	शेष:
		err = -EINVAL;
		dev_err(hba->dev, "%s: Invalid device management cmd response: %x\n",
				__func__, resp);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ufshcd_रुको_क्रम_dev_cmd(काष्ठा ufs_hba *hba,
		काष्ठा ufshcd_lrb *lrbp, पूर्णांक max_समयout)
अणु
	पूर्णांक err = 0;
	अचिन्हित दीर्घ समय_left;
	अचिन्हित दीर्घ flags;

	समय_left = रुको_क्रम_completion_समयout(hba->dev_cmd.complete,
			msecs_to_jअगरfies(max_समयout));

	/* Make sure descriptors are पढ़ोy beक्रमe ringing the करोorbell */
	wmb();
	spin_lock_irqsave(hba->host->host_lock, flags);
	hba->dev_cmd.complete = शून्य;
	अगर (likely(समय_left)) अणु
		err = ufshcd_get_tr_ocs(lrbp);
		अगर (!err)
			err = ufshcd_dev_cmd_completion(hba, lrbp);
	पूर्ण
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	अगर (!समय_left) अणु
		err = -ETIMEDOUT;
		dev_dbg(hba->dev, "%s: dev_cmd request timedout, tag %d\n",
			__func__, lrbp->task_tag);
		अगर (!ufshcd_clear_cmd(hba, lrbp->task_tag))
			/* successfully cleared the command, retry अगर needed */
			err = -EAGAIN;
		/*
		 * in हाल of an error, after clearing the करोorbell,
		 * we also need to clear the outstanding_request
		 * field in hba
		 */
		ufshcd_outstanding_req_clear(hba, lrbp->task_tag);
	पूर्ण

	वापस err;
पूर्ण

/**
 * ufshcd_exec_dev_cmd - API क्रम sending device management requests
 * @hba: UFS hba
 * @cmd_type: specअगरies the type (NOP, Query...)
 * @समयout: समयout in milliseconds
 *
 * NOTE: Since there is only one available tag क्रम device management commands,
 * it is expected you hold the hba->dev_cmd.lock mutex.
 */
अटल पूर्णांक ufshcd_exec_dev_cmd(काष्ठा ufs_hba *hba,
		क्रमागत dev_cmd_type cmd_type, पूर्णांक समयout)
अणु
	काष्ठा request_queue *q = hba->cmd_queue;
	काष्ठा request *req;
	काष्ठा ufshcd_lrb *lrbp;
	पूर्णांक err;
	पूर्णांक tag;
	काष्ठा completion रुको;
	अचिन्हित दीर्घ flags;

	करोwn_पढ़ो(&hba->clk_scaling_lock);

	/*
	 * Get मुक्त slot, sleep अगर slots are unavailable.
	 * Even though we use रुको_event() which sleeps indefinitely,
	 * the maximum रुको समय is bounded by SCSI request समयout.
	 */
	req = blk_get_request(q, REQ_OP_DRV_OUT, 0);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ out_unlock;
	पूर्ण
	tag = req->tag;
	WARN_ON_ONCE(!ufshcd_valid_tag(hba, tag));
	/* Set the समयout such that the SCSI error handler is not activated. */
	req->समयout = msecs_to_jअगरfies(2 * समयout);
	blk_mq_start_request(req);

	init_completion(&रुको);
	lrbp = &hba->lrb[tag];
	अगर (unlikely(lrbp->in_use)) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	WARN_ON(lrbp->cmd);
	err = ufshcd_compose_dev_cmd(hba, lrbp, cmd_type, tag);
	अगर (unlikely(err))
		जाओ out_put_tag;

	hba->dev_cmd.complete = &रुको;

	ufshcd_add_query_upiu_trace(hba, UFS_QUERY_SEND, lrbp->ucd_req_ptr);
	/* Make sure descriptors are पढ़ोy beक्रमe ringing the करोorbell */
	wmb();
	spin_lock_irqsave(hba->host->host_lock, flags);
	ufshcd_send_command(hba, tag);
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	err = ufshcd_रुको_क्रम_dev_cmd(hba, lrbp, समयout);

out:
	ufshcd_add_query_upiu_trace(hba, err ? UFS_QUERY_ERR : UFS_QUERY_COMP,
				    (काष्ठा utp_upiu_req *)lrbp->ucd_rsp_ptr);

out_put_tag:
	blk_put_request(req);
out_unlock:
	up_पढ़ो(&hba->clk_scaling_lock);
	वापस err;
पूर्ण

/**
 * ufshcd_init_query() - init the query response and request parameters
 * @hba: per-adapter instance
 * @request: address of the request poपूर्णांकer to be initialized
 * @response: address of the response poपूर्णांकer to be initialized
 * @opcode: operation to perक्रमm
 * @idn: flag idn to access
 * @index: LU number to access
 * @selector: query/flag/descriptor further identअगरication
 */
अटल अंतरभूत व्योम ufshcd_init_query(काष्ठा ufs_hba *hba,
		काष्ठा ufs_query_req **request, काष्ठा ufs_query_res **response,
		क्रमागत query_opcode opcode, u8 idn, u8 index, u8 selector)
अणु
	*request = &hba->dev_cmd.query.request;
	*response = &hba->dev_cmd.query.response;
	स_रखो(*request, 0, माप(काष्ठा ufs_query_req));
	स_रखो(*response, 0, माप(काष्ठा ufs_query_res));
	(*request)->upiu_req.opcode = opcode;
	(*request)->upiu_req.idn = idn;
	(*request)->upiu_req.index = index;
	(*request)->upiu_req.selector = selector;
पूर्ण

अटल पूर्णांक ufshcd_query_flag_retry(काष्ठा ufs_hba *hba,
	क्रमागत query_opcode opcode, क्रमागत flag_idn idn, u8 index, bool *flag_res)
अणु
	पूर्णांक ret;
	पूर्णांक retries;

	क्रम (retries = 0; retries < QUERY_REQ_RETRIES; retries++) अणु
		ret = ufshcd_query_flag(hba, opcode, idn, index, flag_res);
		अगर (ret)
			dev_dbg(hba->dev,
				"%s: failed with error %d, retries %d\n",
				__func__, ret, retries);
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (ret)
		dev_err(hba->dev,
			"%s: query attribute, opcode %d, idn %d, failed with error %d after %d retires\n",
			__func__, opcode, idn, ret, retries);
	वापस ret;
पूर्ण

/**
 * ufshcd_query_flag() - API function क्रम sending flag query requests
 * @hba: per-adapter instance
 * @opcode: flag query to perक्रमm
 * @idn: flag idn to access
 * @index: flag index to access
 * @flag_res: the flag value after the query request completes
 *
 * Returns 0 क्रम success, non-zero in हाल of failure
 */
पूर्णांक ufshcd_query_flag(काष्ठा ufs_hba *hba, क्रमागत query_opcode opcode,
			क्रमागत flag_idn idn, u8 index, bool *flag_res)
अणु
	काष्ठा ufs_query_req *request = शून्य;
	काष्ठा ufs_query_res *response = शून्य;
	पूर्णांक err, selector = 0;
	पूर्णांक समयout = QUERY_REQ_TIMEOUT;

	BUG_ON(!hba);

	ufshcd_hold(hba, false);
	mutex_lock(&hba->dev_cmd.lock);
	ufshcd_init_query(hba, &request, &response, opcode, idn, index,
			selector);

	चयन (opcode) अणु
	हाल UPIU_QUERY_OPCODE_SET_FLAG:
	हाल UPIU_QUERY_OPCODE_CLEAR_FLAG:
	हाल UPIU_QUERY_OPCODE_TOGGLE_FLAG:
		request->query_func = UPIU_QUERY_FUNC_STANDARD_WRITE_REQUEST;
		अवरोध;
	हाल UPIU_QUERY_OPCODE_READ_FLAG:
		request->query_func = UPIU_QUERY_FUNC_STANDARD_READ_REQUEST;
		अगर (!flag_res) अणु
			/* No dummy पढ़ोs */
			dev_err(hba->dev, "%s: Invalid argument for read request\n",
					__func__);
			err = -EINVAL;
			जाओ out_unlock;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(hba->dev,
			"%s: Expected query flag opcode but got = %d\n",
			__func__, opcode);
		err = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	err = ufshcd_exec_dev_cmd(hba, DEV_CMD_TYPE_QUERY, समयout);

	अगर (err) अणु
		dev_err(hba->dev,
			"%s: Sending flag query for idn %d failed, err = %d\n",
			__func__, idn, err);
		जाओ out_unlock;
	पूर्ण

	अगर (flag_res)
		*flag_res = (be32_to_cpu(response->upiu_res.value) &
				MASK_QUERY_UPIU_FLAG_LOC) & 0x1;

out_unlock:
	mutex_unlock(&hba->dev_cmd.lock);
	ufshcd_release(hba);
	वापस err;
पूर्ण

/**
 * ufshcd_query_attr - API function क्रम sending attribute requests
 * @hba: per-adapter instance
 * @opcode: attribute opcode
 * @idn: attribute idn to access
 * @index: index field
 * @selector: selector field
 * @attr_val: the attribute value after the query request completes
 *
 * Returns 0 क्रम success, non-zero in हाल of failure
*/
पूर्णांक ufshcd_query_attr(काष्ठा ufs_hba *hba, क्रमागत query_opcode opcode,
		      क्रमागत attr_idn idn, u8 index, u8 selector, u32 *attr_val)
अणु
	काष्ठा ufs_query_req *request = शून्य;
	काष्ठा ufs_query_res *response = शून्य;
	पूर्णांक err;

	BUG_ON(!hba);

	अगर (!attr_val) अणु
		dev_err(hba->dev, "%s: attribute value required for opcode 0x%x\n",
				__func__, opcode);
		वापस -EINVAL;
	पूर्ण

	ufshcd_hold(hba, false);

	mutex_lock(&hba->dev_cmd.lock);
	ufshcd_init_query(hba, &request, &response, opcode, idn, index,
			selector);

	चयन (opcode) अणु
	हाल UPIU_QUERY_OPCODE_WRITE_ATTR:
		request->query_func = UPIU_QUERY_FUNC_STANDARD_WRITE_REQUEST;
		request->upiu_req.value = cpu_to_be32(*attr_val);
		अवरोध;
	हाल UPIU_QUERY_OPCODE_READ_ATTR:
		request->query_func = UPIU_QUERY_FUNC_STANDARD_READ_REQUEST;
		अवरोध;
	शेष:
		dev_err(hba->dev, "%s: Expected query attr opcode but got = 0x%.2x\n",
				__func__, opcode);
		err = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	err = ufshcd_exec_dev_cmd(hba, DEV_CMD_TYPE_QUERY, QUERY_REQ_TIMEOUT);

	अगर (err) अणु
		dev_err(hba->dev, "%s: opcode 0x%.2x for idn %d failed, index %d, err = %d\n",
				__func__, opcode, idn, index, err);
		जाओ out_unlock;
	पूर्ण

	*attr_val = be32_to_cpu(response->upiu_res.value);

out_unlock:
	mutex_unlock(&hba->dev_cmd.lock);
	ufshcd_release(hba);
	वापस err;
पूर्ण

/**
 * ufshcd_query_attr_retry() - API function क्रम sending query
 * attribute with retries
 * @hba: per-adapter instance
 * @opcode: attribute opcode
 * @idn: attribute idn to access
 * @index: index field
 * @selector: selector field
 * @attr_val: the attribute value after the query request
 * completes
 *
 * Returns 0 क्रम success, non-zero in हाल of failure
*/
अटल पूर्णांक ufshcd_query_attr_retry(काष्ठा ufs_hba *hba,
	क्रमागत query_opcode opcode, क्रमागत attr_idn idn, u8 index, u8 selector,
	u32 *attr_val)
अणु
	पूर्णांक ret = 0;
	u32 retries;

	क्रम (retries = QUERY_REQ_RETRIES; retries > 0; retries--) अणु
		ret = ufshcd_query_attr(hba, opcode, idn, index,
						selector, attr_val);
		अगर (ret)
			dev_dbg(hba->dev, "%s: failed with error %d, retries %d\n",
				__func__, ret, retries);
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (ret)
		dev_err(hba->dev,
			"%s: query attribute, idn %d, failed with error %d after %d retires\n",
			__func__, idn, ret, QUERY_REQ_RETRIES);
	वापस ret;
पूर्ण

अटल पूर्णांक __ufshcd_query_descriptor(काष्ठा ufs_hba *hba,
			क्रमागत query_opcode opcode, क्रमागत desc_idn idn, u8 index,
			u8 selector, u8 *desc_buf, पूर्णांक *buf_len)
अणु
	काष्ठा ufs_query_req *request = शून्य;
	काष्ठा ufs_query_res *response = शून्य;
	पूर्णांक err;

	BUG_ON(!hba);

	अगर (!desc_buf) अणु
		dev_err(hba->dev, "%s: descriptor buffer required for opcode 0x%x\n",
				__func__, opcode);
		वापस -EINVAL;
	पूर्ण

	अगर (*buf_len < QUERY_DESC_MIN_SIZE || *buf_len > QUERY_DESC_MAX_SIZE) अणु
		dev_err(hba->dev, "%s: descriptor buffer size (%d) is out of range\n",
				__func__, *buf_len);
		वापस -EINVAL;
	पूर्ण

	ufshcd_hold(hba, false);

	mutex_lock(&hba->dev_cmd.lock);
	ufshcd_init_query(hba, &request, &response, opcode, idn, index,
			selector);
	hba->dev_cmd.query.descriptor = desc_buf;
	request->upiu_req.length = cpu_to_be16(*buf_len);

	चयन (opcode) अणु
	हाल UPIU_QUERY_OPCODE_WRITE_DESC:
		request->query_func = UPIU_QUERY_FUNC_STANDARD_WRITE_REQUEST;
		अवरोध;
	हाल UPIU_QUERY_OPCODE_READ_DESC:
		request->query_func = UPIU_QUERY_FUNC_STANDARD_READ_REQUEST;
		अवरोध;
	शेष:
		dev_err(hba->dev,
				"%s: Expected query descriptor opcode but got = 0x%.2x\n",
				__func__, opcode);
		err = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	err = ufshcd_exec_dev_cmd(hba, DEV_CMD_TYPE_QUERY, QUERY_REQ_TIMEOUT);

	अगर (err) अणु
		dev_err(hba->dev, "%s: opcode 0x%.2x for idn %d failed, index %d, err = %d\n",
				__func__, opcode, idn, index, err);
		जाओ out_unlock;
	पूर्ण

	*buf_len = be16_to_cpu(response->upiu_res.length);

out_unlock:
	hba->dev_cmd.query.descriptor = शून्य;
	mutex_unlock(&hba->dev_cmd.lock);
	ufshcd_release(hba);
	वापस err;
पूर्ण

/**
 * ufshcd_query_descriptor_retry - API function क्रम sending descriptor requests
 * @hba: per-adapter instance
 * @opcode: attribute opcode
 * @idn: attribute idn to access
 * @index: index field
 * @selector: selector field
 * @desc_buf: the buffer that contains the descriptor
 * @buf_len: length parameter passed to the device
 *
 * Returns 0 क्रम success, non-zero in हाल of failure.
 * The buf_len parameter will contain, on वापस, the length parameter
 * received on the response.
 */
पूर्णांक ufshcd_query_descriptor_retry(काष्ठा ufs_hba *hba,
				  क्रमागत query_opcode opcode,
				  क्रमागत desc_idn idn, u8 index,
				  u8 selector,
				  u8 *desc_buf, पूर्णांक *buf_len)
अणु
	पूर्णांक err;
	पूर्णांक retries;

	क्रम (retries = QUERY_REQ_RETRIES; retries > 0; retries--) अणु
		err = __ufshcd_query_descriptor(hba, opcode, idn, index,
						selector, desc_buf, buf_len);
		अगर (!err || err == -EINVAL)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/**
 * ufshcd_map_desc_id_to_length - map descriptor IDN to its length
 * @hba: Poपूर्णांकer to adapter instance
 * @desc_id: descriptor idn value
 * @desc_len: mapped desc length (out)
 */
व्योम ufshcd_map_desc_id_to_length(काष्ठा ufs_hba *hba, क्रमागत desc_idn desc_id,
				  पूर्णांक *desc_len)
अणु
	अगर (desc_id >= QUERY_DESC_IDN_MAX || desc_id == QUERY_DESC_IDN_RFU_0 ||
	    desc_id == QUERY_DESC_IDN_RFU_1)
		*desc_len = 0;
	अन्यथा
		*desc_len = hba->desc_size[desc_id];
पूर्ण
EXPORT_SYMBOL(ufshcd_map_desc_id_to_length);

अटल व्योम ufshcd_update_desc_length(काष्ठा ufs_hba *hba,
				      क्रमागत desc_idn desc_id, पूर्णांक desc_index,
				      अचिन्हित अक्षर desc_len)
अणु
	अगर (hba->desc_size[desc_id] == QUERY_DESC_MAX_SIZE &&
	    desc_id != QUERY_DESC_IDN_STRING && desc_index != UFS_RPMB_UNIT)
		/* For UFS 3.1, the normal unit descriptor is 10 bytes larger
		 * than the RPMB unit, however, both descriptors share the same
		 * desc_idn, to cover both unit descriptors with one length, we
		 * choose the normal unit descriptor length by desc_index.
		 */
		hba->desc_size[desc_id] = desc_len;
पूर्ण

/**
 * ufshcd_पढ़ो_desc_param - पढ़ो the specअगरied descriptor parameter
 * @hba: Poपूर्णांकer to adapter instance
 * @desc_id: descriptor idn value
 * @desc_index: descriptor index
 * @param_offset: offset of the parameter to पढ़ो
 * @param_पढ़ो_buf: poपूर्णांकer to buffer where parameter would be पढ़ो
 * @param_size: माप(param_पढ़ो_buf)
 *
 * Return 0 in हाल of success, non-zero otherwise
 */
पूर्णांक ufshcd_पढ़ो_desc_param(काष्ठा ufs_hba *hba,
			   क्रमागत desc_idn desc_id,
			   पूर्णांक desc_index,
			   u8 param_offset,
			   u8 *param_पढ़ो_buf,
			   u8 param_size)
अणु
	पूर्णांक ret;
	u8 *desc_buf;
	पूर्णांक buff_len;
	bool is_kदो_स्मृति = true;

	/* Safety check */
	अगर (desc_id >= QUERY_DESC_IDN_MAX || !param_size)
		वापस -EINVAL;

	/* Get the length of descriptor */
	ufshcd_map_desc_id_to_length(hba, desc_id, &buff_len);
	अगर (!buff_len) अणु
		dev_err(hba->dev, "%s: Failed to get desc length\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (param_offset >= buff_len) अणु
		dev_err(hba->dev, "%s: Invalid offset 0x%x in descriptor IDN 0x%x, length 0x%x\n",
			__func__, param_offset, desc_id, buff_len);
		वापस -EINVAL;
	पूर्ण

	/* Check whether we need temp memory */
	अगर (param_offset != 0 || param_size < buff_len) अणु
		desc_buf = kzalloc(buff_len, GFP_KERNEL);
		अगर (!desc_buf)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		desc_buf = param_पढ़ो_buf;
		is_kदो_स्मृति = false;
	पूर्ण

	/* Request क्रम full descriptor */
	ret = ufshcd_query_descriptor_retry(hba, UPIU_QUERY_OPCODE_READ_DESC,
					desc_id, desc_index, 0,
					desc_buf, &buff_len);

	अगर (ret) अणु
		dev_err(hba->dev, "%s: Failed reading descriptor. desc_id %d, desc_index %d, param_offset %d, ret %d\n",
			__func__, desc_id, desc_index, param_offset, ret);
		जाओ out;
	पूर्ण

	/* Sanity check */
	अगर (desc_buf[QUERY_DESC_DESC_TYPE_OFFSET] != desc_id) अणु
		dev_err(hba->dev, "%s: invalid desc_id %d in descriptor header\n",
			__func__, desc_buf[QUERY_DESC_DESC_TYPE_OFFSET]);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Update descriptor length */
	buff_len = desc_buf[QUERY_DESC_LENGTH_OFFSET];
	ufshcd_update_desc_length(hba, desc_id, desc_index, buff_len);

	अगर (is_kदो_स्मृति) अणु
		/* Make sure we करोn't copy more data than available */
		अगर (param_offset + param_size > buff_len)
			param_size = buff_len - param_offset;
		स_नकल(param_पढ़ो_buf, &desc_buf[param_offset], param_size);
	पूर्ण
out:
	अगर (is_kदो_स्मृति)
		kमुक्त(desc_buf);
	वापस ret;
पूर्ण

/**
 * काष्ठा uc_string_id - unicode string
 *
 * @len: size of this descriptor inclusive
 * @type: descriptor type
 * @uc: unicode string अक्षरacter
 */
काष्ठा uc_string_id अणु
	u8 len;
	u8 type;
	ब_अक्षर_प्रकार uc[];
पूर्ण __packed;

/* replace non-prपूर्णांकable or non-ASCII अक्षरacters with spaces */
अटल अंतरभूत अक्षर ufshcd_हटाओ_non_prपूर्णांकable(u8 ch)
अणु
	वापस (ch >= 0x20 && ch <= 0x7e) ? ch : ' ';
पूर्ण

/**
 * ufshcd_पढ़ो_string_desc - पढ़ो string descriptor
 * @hba: poपूर्णांकer to adapter instance
 * @desc_index: descriptor index
 * @buf: poपूर्णांकer to buffer where descriptor would be पढ़ो,
 *       the caller should मुक्त the memory.
 * @ascii: अगर true convert from unicode to ascii अक्षरacters
 *         null terminated string.
 *
 * Return:
 * *      string size on success.
 * *      -ENOMEM: on allocation failure
 * *      -EINVAL: on a wrong parameter
 */
पूर्णांक ufshcd_पढ़ो_string_desc(काष्ठा ufs_hba *hba, u8 desc_index,
			    u8 **buf, bool ascii)
अणु
	काष्ठा uc_string_id *uc_str;
	u8 *str;
	पूर्णांक ret;

	अगर (!buf)
		वापस -EINVAL;

	uc_str = kzalloc(QUERY_DESC_MAX_SIZE, GFP_KERNEL);
	अगर (!uc_str)
		वापस -ENOMEM;

	ret = ufshcd_पढ़ो_desc_param(hba, QUERY_DESC_IDN_STRING, desc_index, 0,
				     (u8 *)uc_str, QUERY_DESC_MAX_SIZE);
	अगर (ret < 0) अणु
		dev_err(hba->dev, "Reading String Desc failed after %d retries. err = %d\n",
			QUERY_REQ_RETRIES, ret);
		str = शून्य;
		जाओ out;
	पूर्ण

	अगर (uc_str->len <= QUERY_DESC_HDR_SIZE) अणु
		dev_dbg(hba->dev, "String Desc is of zero length\n");
		str = शून्य;
		ret = 0;
		जाओ out;
	पूर्ण

	अगर (ascii) अणु
		sमाप_प्रकार ascii_len;
		पूर्णांक i;
		/* हटाओ header and भागide by 2 to move from UTF16 to UTF8 */
		ascii_len = (uc_str->len - QUERY_DESC_HDR_SIZE) / 2 + 1;
		str = kzalloc(ascii_len, GFP_KERNEL);
		अगर (!str) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		/*
		 * the descriptor contains string in UTF16 क्रमmat
		 * we need to convert to utf-8 so it can be displayed
		 */
		ret = utf16s_to_utf8s(uc_str->uc,
				      uc_str->len - QUERY_DESC_HDR_SIZE,
				      UTF16_BIG_ENDIAN, str, ascii_len);

		/* replace non-prपूर्णांकable or non-ASCII अक्षरacters with spaces */
		क्रम (i = 0; i < ret; i++)
			str[i] = ufshcd_हटाओ_non_prपूर्णांकable(str[i]);

		str[ret++] = '\0';

	पूर्ण अन्यथा अणु
		str = kmemdup(uc_str, uc_str->len, GFP_KERNEL);
		अगर (!str) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		ret = uc_str->len;
	पूर्ण
out:
	*buf = str;
	kमुक्त(uc_str);
	वापस ret;
पूर्ण

/**
 * ufshcd_पढ़ो_unit_desc_param - पढ़ो the specअगरied unit descriptor parameter
 * @hba: Poपूर्णांकer to adapter instance
 * @lun: lun id
 * @param_offset: offset of the parameter to पढ़ो
 * @param_पढ़ो_buf: poपूर्णांकer to buffer where parameter would be पढ़ो
 * @param_size: माप(param_पढ़ो_buf)
 *
 * Return 0 in हाल of success, non-zero otherwise
 */
अटल अंतरभूत पूर्णांक ufshcd_पढ़ो_unit_desc_param(काष्ठा ufs_hba *hba,
					      पूर्णांक lun,
					      क्रमागत unit_desc_param param_offset,
					      u8 *param_पढ़ो_buf,
					      u32 param_size)
अणु
	/*
	 * Unit descriptors are only available क्रम general purpose LUs (LUN id
	 * from 0 to 7) and RPMB Well known LU.
	 */
	अगर (!ufs_is_valid_unit_desc_lun(&hba->dev_info, lun, param_offset))
		वापस -EOPNOTSUPP;

	वापस ufshcd_पढ़ो_desc_param(hba, QUERY_DESC_IDN_UNIT, lun,
				      param_offset, param_पढ़ो_buf, param_size);
पूर्ण

अटल पूर्णांक ufshcd_get_ref_clk_gating_रुको(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err = 0;
	u32 gating_रुको = UFSHCD_REF_CLK_GATING_WAIT_US;

	अगर (hba->dev_info.wspecversion >= 0x300) अणु
		err = ufshcd_query_attr_retry(hba, UPIU_QUERY_OPCODE_READ_ATTR,
				QUERY_ATTR_IDN_REF_CLK_GATING_WAIT_TIME, 0, 0,
				&gating_रुको);
		अगर (err)
			dev_err(hba->dev, "Failed reading bRefClkGatingWait. err = %d, use default %uus\n",
					 err, gating_रुको);

		अगर (gating_रुको == 0) अणु
			gating_रुको = UFSHCD_REF_CLK_GATING_WAIT_US;
			dev_err(hba->dev, "Undefined ref clk gating wait time, use default %uus\n",
					 gating_रुको);
		पूर्ण

		hba->dev_info.clk_gating_रुको_us = gating_रुको;
	पूर्ण

	वापस err;
पूर्ण

/**
 * ufshcd_memory_alloc - allocate memory क्रम host memory space data काष्ठाures
 * @hba: per adapter instance
 *
 * 1. Allocate DMA memory क्रम Command Descriptor array
 *	Each command descriptor consist of Command UPIU, Response UPIU and PRDT
 * 2. Allocate DMA memory क्रम UTP Transfer Request Descriptor List (UTRDL).
 * 3. Allocate DMA memory क्रम UTP Task Management Request Descriptor List
 *	(UTMRDL)
 * 4. Allocate memory क्रम local reference block(lrb).
 *
 * Returns 0 क्रम success, non-zero in हाल of failure
 */
अटल पूर्णांक ufshcd_memory_alloc(काष्ठा ufs_hba *hba)
अणु
	माप_प्रकार uपंचांगrdl_size, utrdl_size, ucdl_size;

	/* Allocate memory क्रम UTP command descriptors */
	ucdl_size = (माप(काष्ठा utp_transfer_cmd_desc) * hba->nutrs);
	hba->ucdl_base_addr = dmam_alloc_coherent(hba->dev,
						  ucdl_size,
						  &hba->ucdl_dma_addr,
						  GFP_KERNEL);

	/*
	 * UFSHCI requires UTP command descriptor to be 128 byte aligned.
	 * make sure hba->ucdl_dma_addr is aligned to PAGE_SIZE
	 * अगर hba->ucdl_dma_addr is aligned to PAGE_SIZE, then it will
	 * be aligned to 128 bytes as well
	 */
	अगर (!hba->ucdl_base_addr ||
	    WARN_ON(hba->ucdl_dma_addr & (PAGE_SIZE - 1))) अणु
		dev_err(hba->dev,
			"Command Descriptor Memory allocation failed\n");
		जाओ out;
	पूर्ण

	/*
	 * Allocate memory क्रम UTP Transfer descriptors
	 * UFSHCI requires 1024 byte alignment of UTRD
	 */
	utrdl_size = (माप(काष्ठा utp_transfer_req_desc) * hba->nutrs);
	hba->utrdl_base_addr = dmam_alloc_coherent(hba->dev,
						   utrdl_size,
						   &hba->utrdl_dma_addr,
						   GFP_KERNEL);
	अगर (!hba->utrdl_base_addr ||
	    WARN_ON(hba->utrdl_dma_addr & (PAGE_SIZE - 1))) अणु
		dev_err(hba->dev,
			"Transfer Descriptor Memory allocation failed\n");
		जाओ out;
	पूर्ण

	/*
	 * Allocate memory क्रम UTP Task Management descriptors
	 * UFSHCI requires 1024 byte alignment of UTMRD
	 */
	uपंचांगrdl_size = माप(काष्ठा utp_task_req_desc) * hba->nuपंचांगrs;
	hba->uपंचांगrdl_base_addr = dmam_alloc_coherent(hba->dev,
						    uपंचांगrdl_size,
						    &hba->uपंचांगrdl_dma_addr,
						    GFP_KERNEL);
	अगर (!hba->uपंचांगrdl_base_addr ||
	    WARN_ON(hba->uपंचांगrdl_dma_addr & (PAGE_SIZE - 1))) अणु
		dev_err(hba->dev,
		"Task Management Descriptor Memory allocation failed\n");
		जाओ out;
	पूर्ण

	/* Allocate memory क्रम local reference block */
	hba->lrb = devm_kसुस्मृति(hba->dev,
				hba->nutrs, माप(काष्ठा ufshcd_lrb),
				GFP_KERNEL);
	अगर (!hba->lrb) अणु
		dev_err(hba->dev, "LRB Memory allocation failed\n");
		जाओ out;
	पूर्ण
	वापस 0;
out:
	वापस -ENOMEM;
पूर्ण

/**
 * ufshcd_host_memory_configure - configure local reference block with
 *				memory offsets
 * @hba: per adapter instance
 *
 * Configure Host memory space
 * 1. Update Corresponding UTRD.UCDBA and UTRD.UCDBAU with UCD DMA
 * address.
 * 2. Update each UTRD with Response UPIU offset, Response UPIU length
 * and PRDT offset.
 * 3. Save the corresponding addresses of UTRD, UCD.CMD, UCD.RSP and UCD.PRDT
 * पूर्णांकo local reference block.
 */
अटल व्योम ufshcd_host_memory_configure(काष्ठा ufs_hba *hba)
अणु
	काष्ठा utp_transfer_req_desc *utrdlp;
	dma_addr_t cmd_desc_dma_addr;
	dma_addr_t cmd_desc_element_addr;
	u16 response_offset;
	u16 prdt_offset;
	पूर्णांक cmd_desc_size;
	पूर्णांक i;

	utrdlp = hba->utrdl_base_addr;

	response_offset =
		दुरत्व(काष्ठा utp_transfer_cmd_desc, response_upiu);
	prdt_offset =
		दुरत्व(काष्ठा utp_transfer_cmd_desc, prd_table);

	cmd_desc_size = माप(काष्ठा utp_transfer_cmd_desc);
	cmd_desc_dma_addr = hba->ucdl_dma_addr;

	क्रम (i = 0; i < hba->nutrs; i++) अणु
		/* Configure UTRD with command descriptor base address */
		cmd_desc_element_addr =
				(cmd_desc_dma_addr + (cmd_desc_size * i));
		utrdlp[i].command_desc_base_addr_lo =
				cpu_to_le32(lower_32_bits(cmd_desc_element_addr));
		utrdlp[i].command_desc_base_addr_hi =
				cpu_to_le32(upper_32_bits(cmd_desc_element_addr));

		/* Response upiu and prdt offset should be in द्विगुन words */
		अगर (hba->quirks & UFSHCD_QUIRK_PRDT_BYTE_GRAN) अणु
			utrdlp[i].response_upiu_offset =
				cpu_to_le16(response_offset);
			utrdlp[i].prd_table_offset =
				cpu_to_le16(prdt_offset);
			utrdlp[i].response_upiu_length =
				cpu_to_le16(ALIGNED_UPIU_SIZE);
		पूर्ण अन्यथा अणु
			utrdlp[i].response_upiu_offset =
				cpu_to_le16(response_offset >> 2);
			utrdlp[i].prd_table_offset =
				cpu_to_le16(prdt_offset >> 2);
			utrdlp[i].response_upiu_length =
				cpu_to_le16(ALIGNED_UPIU_SIZE >> 2);
		पूर्ण

		ufshcd_init_lrb(hba, &hba->lrb[i], i);
	पूर्ण
पूर्ण

/**
 * ufshcd_dme_link_startup - Notअगरy Unipro to perक्रमm link startup
 * @hba: per adapter instance
 *
 * UIC_CMD_DME_LINK_STARTUP command must be issued to Unipro layer,
 * in order to initialize the Unipro link startup procedure.
 * Once the Unipro links are up, the device connected to the controller
 * is detected.
 *
 * Returns 0 on success, non-zero value on failure
 */
अटल पूर्णांक ufshcd_dme_link_startup(काष्ठा ufs_hba *hba)
अणु
	काष्ठा uic_command uic_cmd = अणु0पूर्ण;
	पूर्णांक ret;

	uic_cmd.command = UIC_CMD_DME_LINK_STARTUP;

	ret = ufshcd_send_uic_cmd(hba, &uic_cmd);
	अगर (ret)
		dev_dbg(hba->dev,
			"dme-link-startup: error code %d\n", ret);
	वापस ret;
पूर्ण
/**
 * ufshcd_dme_reset - UIC command क्रम DME_RESET
 * @hba: per adapter instance
 *
 * DME_RESET command is issued in order to reset UniPro stack.
 * This function now deals with cold reset.
 *
 * Returns 0 on success, non-zero value on failure
 */
अटल पूर्णांक ufshcd_dme_reset(काष्ठा ufs_hba *hba)
अणु
	काष्ठा uic_command uic_cmd = अणु0पूर्ण;
	पूर्णांक ret;

	uic_cmd.command = UIC_CMD_DME_RESET;

	ret = ufshcd_send_uic_cmd(hba, &uic_cmd);
	अगर (ret)
		dev_err(hba->dev,
			"dme-reset: error code %d\n", ret);

	वापस ret;
पूर्ण

पूर्णांक ufshcd_dme_configure_adapt(काष्ठा ufs_hba *hba,
			       पूर्णांक agreed_gear,
			       पूर्णांक adapt_val)
अणु
	पूर्णांक ret;

	अगर (agreed_gear != UFS_HS_G4)
		adapt_val = PA_NO_ADAPT;

	ret = ufshcd_dme_set(hba,
			     UIC_ARG_MIB(PA_TXHSADAPTTYPE),
			     adapt_val);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_dme_configure_adapt);

/**
 * ufshcd_dme_enable - UIC command क्रम DME_ENABLE
 * @hba: per adapter instance
 *
 * DME_ENABLE command is issued in order to enable UniPro stack.
 *
 * Returns 0 on success, non-zero value on failure
 */
अटल पूर्णांक ufshcd_dme_enable(काष्ठा ufs_hba *hba)
अणु
	काष्ठा uic_command uic_cmd = अणु0पूर्ण;
	पूर्णांक ret;

	uic_cmd.command = UIC_CMD_DME_ENABLE;

	ret = ufshcd_send_uic_cmd(hba, &uic_cmd);
	अगर (ret)
		dev_err(hba->dev,
			"dme-enable: error code %d\n", ret);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम ufshcd_add_delay_beक्रमe_dme_cmd(काष्ठा ufs_hba *hba)
अणु
	#घोषणा MIN_DELAY_BEFORE_DME_CMDS_US	1000
	अचिन्हित दीर्घ min_sleep_समय_us;

	अगर (!(hba->quirks & UFSHCD_QUIRK_DELAY_BEFORE_DME_CMDS))
		वापस;

	/*
	 * last_dme_cmd_tstamp will be 0 only क्रम 1st call to
	 * this function
	 */
	अगर (unlikely(!kसमय_प्रकारo_us(hba->last_dme_cmd_tstamp))) अणु
		min_sleep_समय_us = MIN_DELAY_BEFORE_DME_CMDS_US;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ delta =
			(अचिन्हित दीर्घ) kसमय_प्रकारo_us(
				kसमय_sub(kसमय_get(),
				hba->last_dme_cmd_tstamp));

		अगर (delta < MIN_DELAY_BEFORE_DME_CMDS_US)
			min_sleep_समय_us =
				MIN_DELAY_BEFORE_DME_CMDS_US - delta;
		अन्यथा
			वापस; /* no more delay required */
	पूर्ण

	/* allow sleep क्रम extra 50us अगर needed */
	usleep_range(min_sleep_समय_us, min_sleep_समय_us + 50);
पूर्ण

/**
 * ufshcd_dme_set_attr - UIC command क्रम DME_SET, DME_PEER_SET
 * @hba: per adapter instance
 * @attr_sel: uic command argument1
 * @attr_set: attribute set type as uic command argument2
 * @mib_val: setting value as uic command argument3
 * @peer: indicate whether peer or local
 *
 * Returns 0 on success, non-zero value on failure
 */
पूर्णांक ufshcd_dme_set_attr(काष्ठा ufs_hba *hba, u32 attr_sel,
			u8 attr_set, u32 mib_val, u8 peer)
अणु
	काष्ठा uic_command uic_cmd = अणु0पूर्ण;
	अटल स्थिर अक्षर *स्थिर action[] = अणु
		"dme-set",
		"dme-peer-set"
	पूर्ण;
	स्थिर अक्षर *set = action[!!peer];
	पूर्णांक ret;
	पूर्णांक retries = UFS_UIC_COMMAND_RETRIES;

	uic_cmd.command = peer ?
		UIC_CMD_DME_PEER_SET : UIC_CMD_DME_SET;
	uic_cmd.argument1 = attr_sel;
	uic_cmd.argument2 = UIC_ARG_ATTR_TYPE(attr_set);
	uic_cmd.argument3 = mib_val;

	करो अणु
		/* क्रम peer attributes we retry upon failure */
		ret = ufshcd_send_uic_cmd(hba, &uic_cmd);
		अगर (ret)
			dev_dbg(hba->dev, "%s: attr-id 0x%x val 0x%x error code %d\n",
				set, UIC_GET_ATTR_ID(attr_sel), mib_val, ret);
	पूर्ण जबतक (ret && peer && --retries);

	अगर (ret)
		dev_err(hba->dev, "%s: attr-id 0x%x val 0x%x failed %d retries\n",
			set, UIC_GET_ATTR_ID(attr_sel), mib_val,
			UFS_UIC_COMMAND_RETRIES - retries);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_dme_set_attr);

/**
 * ufshcd_dme_get_attr - UIC command क्रम DME_GET, DME_PEER_GET
 * @hba: per adapter instance
 * @attr_sel: uic command argument1
 * @mib_val: the value of the attribute as वापसed by the UIC command
 * @peer: indicate whether peer or local
 *
 * Returns 0 on success, non-zero value on failure
 */
पूर्णांक ufshcd_dme_get_attr(काष्ठा ufs_hba *hba, u32 attr_sel,
			u32 *mib_val, u8 peer)
अणु
	काष्ठा uic_command uic_cmd = अणु0पूर्ण;
	अटल स्थिर अक्षर *स्थिर action[] = अणु
		"dme-get",
		"dme-peer-get"
	पूर्ण;
	स्थिर अक्षर *get = action[!!peer];
	पूर्णांक ret;
	पूर्णांक retries = UFS_UIC_COMMAND_RETRIES;
	काष्ठा ufs_pa_layer_attr orig_pwr_info;
	काष्ठा ufs_pa_layer_attr temp_pwr_info;
	bool pwr_mode_change = false;

	अगर (peer && (hba->quirks & UFSHCD_QUIRK_DME_PEER_ACCESS_AUTO_MODE)) अणु
		orig_pwr_info = hba->pwr_info;
		temp_pwr_info = orig_pwr_info;

		अगर (orig_pwr_info.pwr_tx == FAST_MODE ||
		    orig_pwr_info.pwr_rx == FAST_MODE) अणु
			temp_pwr_info.pwr_tx = FASTAUTO_MODE;
			temp_pwr_info.pwr_rx = FASTAUTO_MODE;
			pwr_mode_change = true;
		पूर्ण अन्यथा अगर (orig_pwr_info.pwr_tx == SLOW_MODE ||
		    orig_pwr_info.pwr_rx == SLOW_MODE) अणु
			temp_pwr_info.pwr_tx = SLOWAUTO_MODE;
			temp_pwr_info.pwr_rx = SLOWAUTO_MODE;
			pwr_mode_change = true;
		पूर्ण
		अगर (pwr_mode_change) अणु
			ret = ufshcd_change_घातer_mode(hba, &temp_pwr_info);
			अगर (ret)
				जाओ out;
		पूर्ण
	पूर्ण

	uic_cmd.command = peer ?
		UIC_CMD_DME_PEER_GET : UIC_CMD_DME_GET;
	uic_cmd.argument1 = attr_sel;

	करो अणु
		/* क्रम peer attributes we retry upon failure */
		ret = ufshcd_send_uic_cmd(hba, &uic_cmd);
		अगर (ret)
			dev_dbg(hba->dev, "%s: attr-id 0x%x error code %d\n",
				get, UIC_GET_ATTR_ID(attr_sel), ret);
	पूर्ण जबतक (ret && peer && --retries);

	अगर (ret)
		dev_err(hba->dev, "%s: attr-id 0x%x failed %d retries\n",
			get, UIC_GET_ATTR_ID(attr_sel),
			UFS_UIC_COMMAND_RETRIES - retries);

	अगर (mib_val && !ret)
		*mib_val = uic_cmd.argument3;

	अगर (peer && (hba->quirks & UFSHCD_QUIRK_DME_PEER_ACCESS_AUTO_MODE)
	    && pwr_mode_change)
		ufshcd_change_घातer_mode(hba, &orig_pwr_info);
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_dme_get_attr);

/**
 * ufshcd_uic_pwr_ctrl - executes UIC commands (which affects the link घातer
 * state) and रुकोs क्रम it to take effect.
 *
 * @hba: per adapter instance
 * @cmd: UIC command to execute
 *
 * DME operations like DME_SET(PA_PWRMODE), DME_HIBERNATE_ENTER &
 * DME_HIBERNATE_EXIT commands take some समय to take its effect on both host
 * and device UniPro link and hence it's final completion would be indicated by
 * dedicated status bits in Interrupt Status रेजिस्टर (UPMS, UHES, UHXS) in
 * addition to normal UIC command completion Status (UCCS). This function only
 * वापसs after the relevant status bits indicate the completion.
 *
 * Returns 0 on success, non-zero value on failure
 */
अटल पूर्णांक ufshcd_uic_pwr_ctrl(काष्ठा ufs_hba *hba, काष्ठा uic_command *cmd)
अणु
	काष्ठा completion uic_async_करोne;
	अचिन्हित दीर्घ flags;
	u8 status;
	पूर्णांक ret;
	bool reenable_पूर्णांकr = false;

	mutex_lock(&hba->uic_cmd_mutex);
	init_completion(&uic_async_करोne);
	ufshcd_add_delay_beक्रमe_dme_cmd(hba);

	spin_lock_irqsave(hba->host->host_lock, flags);
	अगर (ufshcd_is_link_broken(hba)) अणु
		ret = -ENOLINK;
		जाओ out_unlock;
	पूर्ण
	hba->uic_async_करोne = &uic_async_करोne;
	अगर (ufshcd_पढ़ोl(hba, REG_INTERRUPT_ENABLE) & UIC_COMMAND_COMPL) अणु
		ufshcd_disable_पूर्णांकr(hba, UIC_COMMAND_COMPL);
		/*
		 * Make sure UIC command completion पूर्णांकerrupt is disabled beक्रमe
		 * issuing UIC command.
		 */
		wmb();
		reenable_पूर्णांकr = true;
	पूर्ण
	ret = __ufshcd_send_uic_cmd(hba, cmd, false);
	spin_unlock_irqrestore(hba->host->host_lock, flags);
	अगर (ret) अणु
		dev_err(hba->dev,
			"pwr ctrl cmd 0x%x with mode 0x%x uic error %d\n",
			cmd->command, cmd->argument3, ret);
		जाओ out;
	पूर्ण

	अगर (!रुको_क्रम_completion_समयout(hba->uic_async_करोne,
					 msecs_to_jअगरfies(UIC_CMD_TIMEOUT))) अणु
		dev_err(hba->dev,
			"pwr ctrl cmd 0x%x with mode 0x%x completion timeout\n",
			cmd->command, cmd->argument3);

		अगर (!cmd->cmd_active) अणु
			dev_err(hba->dev, "%s: Power Mode Change operation has been completed, go check UPMCRS\n",
				__func__);
			जाओ check_upmcrs;
		पूर्ण

		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

check_upmcrs:
	status = ufshcd_get_upmcrs(hba);
	अगर (status != PWR_LOCAL) अणु
		dev_err(hba->dev,
			"pwr ctrl cmd 0x%x failed, host upmcrs:0x%x\n",
			cmd->command, status);
		ret = (status != PWR_OK) ? status : -1;
	पूर्ण
out:
	अगर (ret) अणु
		ufshcd_prपूर्णांक_host_state(hba);
		ufshcd_prपूर्णांक_pwr_info(hba);
		ufshcd_prपूर्णांक_evt_hist(hba);
	पूर्ण

	spin_lock_irqsave(hba->host->host_lock, flags);
	hba->active_uic_cmd = शून्य;
	hba->uic_async_करोne = शून्य;
	अगर (reenable_पूर्णांकr)
		ufshcd_enable_पूर्णांकr(hba, UIC_COMMAND_COMPL);
	अगर (ret) अणु
		ufshcd_set_link_broken(hba);
		ufshcd_schedule_eh_work(hba);
	पूर्ण
out_unlock:
	spin_unlock_irqrestore(hba->host->host_lock, flags);
	mutex_unlock(&hba->uic_cmd_mutex);

	वापस ret;
पूर्ण

/**
 * ufshcd_uic_change_pwr_mode - Perक्रमm the UIC घातer mode chage
 *				using DME_SET primitives.
 * @hba: per adapter instance
 * @mode: घातr mode value
 *
 * Returns 0 on success, non-zero value on failure
 */
अटल पूर्णांक ufshcd_uic_change_pwr_mode(काष्ठा ufs_hba *hba, u8 mode)
अणु
	काष्ठा uic_command uic_cmd = अणु0पूर्ण;
	पूर्णांक ret;

	अगर (hba->quirks & UFSHCD_QUIRK_BROKEN_PA_RXHSUNTERMCAP) अणु
		ret = ufshcd_dme_set(hba,
				UIC_ARG_MIB_SEL(PA_RXHSUNTERMCAP, 0), 1);
		अगर (ret) अणु
			dev_err(hba->dev, "%s: failed to enable PA_RXHSUNTERMCAP ret %d\n",
						__func__, ret);
			जाओ out;
		पूर्ण
	पूर्ण

	uic_cmd.command = UIC_CMD_DME_SET;
	uic_cmd.argument1 = UIC_ARG_MIB(PA_PWRMODE);
	uic_cmd.argument3 = mode;
	ufshcd_hold(hba, false);
	ret = ufshcd_uic_pwr_ctrl(hba, &uic_cmd);
	ufshcd_release(hba);

out:
	वापस ret;
पूर्ण

पूर्णांक ufshcd_link_recovery(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(hba->host->host_lock, flags);
	hba->ufshcd_state = UFSHCD_STATE_RESET;
	ufshcd_set_eh_in_progress(hba);
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	/* Reset the attached device */
	ufshcd_device_reset(hba);

	ret = ufshcd_host_reset_and_restore(hba);

	spin_lock_irqsave(hba->host->host_lock, flags);
	अगर (ret)
		hba->ufshcd_state = UFSHCD_STATE_ERROR;
	ufshcd_clear_eh_in_progress(hba);
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	अगर (ret)
		dev_err(hba->dev, "%s: link recovery failed, err %d",
			__func__, ret);
	अन्यथा
		ufshcd_clear_ua_wluns(hba);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_link_recovery);

अटल पूर्णांक ufshcd_uic_hibern8_enter(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret;
	काष्ठा uic_command uic_cmd = अणु0पूर्ण;
	kसमय_प्रकार start = kसमय_get();

	ufshcd_vops_hibern8_notअगरy(hba, UIC_CMD_DME_HIBER_ENTER, PRE_CHANGE);

	uic_cmd.command = UIC_CMD_DME_HIBER_ENTER;
	ret = ufshcd_uic_pwr_ctrl(hba, &uic_cmd);
	trace_ufshcd_profile_hibern8(dev_name(hba->dev), "enter",
			     kसमय_प्रकारo_us(kसमय_sub(kसमय_get(), start)), ret);

	अगर (ret)
		dev_err(hba->dev, "%s: hibern8 enter failed. ret = %d\n",
			__func__, ret);
	अन्यथा
		ufshcd_vops_hibern8_notअगरy(hba, UIC_CMD_DME_HIBER_ENTER,
								POST_CHANGE);

	वापस ret;
पूर्ण

पूर्णांक ufshcd_uic_hibern8_निकास(काष्ठा ufs_hba *hba)
अणु
	काष्ठा uic_command uic_cmd = अणु0पूर्ण;
	पूर्णांक ret;
	kसमय_प्रकार start = kसमय_get();

	ufshcd_vops_hibern8_notअगरy(hba, UIC_CMD_DME_HIBER_EXIT, PRE_CHANGE);

	uic_cmd.command = UIC_CMD_DME_HIBER_EXIT;
	ret = ufshcd_uic_pwr_ctrl(hba, &uic_cmd);
	trace_ufshcd_profile_hibern8(dev_name(hba->dev), "exit",
			     kसमय_प्रकारo_us(kसमय_sub(kसमय_get(), start)), ret);

	अगर (ret) अणु
		dev_err(hba->dev, "%s: hibern8 exit failed. ret = %d\n",
			__func__, ret);
	पूर्ण अन्यथा अणु
		ufshcd_vops_hibern8_notअगरy(hba, UIC_CMD_DME_HIBER_EXIT,
								POST_CHANGE);
		hba->ufs_stats.last_hibern8_निकास_tstamp = kसमय_get();
		hba->ufs_stats.hibern8_निकास_cnt++;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_uic_hibern8_निकास);

व्योम ufshcd_स्वतः_hibern8_update(काष्ठा ufs_hba *hba, u32 ahit)
अणु
	अचिन्हित दीर्घ flags;
	bool update = false;

	अगर (!ufshcd_is_स्वतः_hibern8_supported(hba))
		वापस;

	spin_lock_irqsave(hba->host->host_lock, flags);
	अगर (hba->ahit != ahit) अणु
		hba->ahit = ahit;
		update = true;
	पूर्ण
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	अगर (update && !pm_runसमय_suspended(hba->dev)) अणु
		pm_runसमय_get_sync(hba->dev);
		ufshcd_hold(hba, false);
		ufshcd_स्वतः_hibern8_enable(hba);
		ufshcd_release(hba);
		pm_runसमय_put(hba->dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_स्वतः_hibern8_update);

व्योम ufshcd_स्वतः_hibern8_enable(काष्ठा ufs_hba *hba)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!ufshcd_is_स्वतः_hibern8_supported(hba))
		वापस;

	spin_lock_irqsave(hba->host->host_lock, flags);
	ufshcd_ग_लिखोl(hba, hba->ahit, REG_AUTO_HIBERNATE_IDLE_TIMER);
	spin_unlock_irqrestore(hba->host->host_lock, flags);
पूर्ण

 /**
 * ufshcd_init_pwr_info - setting the POR (घातer on reset)
 * values in hba घातer info
 * @hba: per-adapter instance
 */
अटल व्योम ufshcd_init_pwr_info(काष्ठा ufs_hba *hba)
अणु
	hba->pwr_info.gear_rx = UFS_PWM_G1;
	hba->pwr_info.gear_tx = UFS_PWM_G1;
	hba->pwr_info.lane_rx = 1;
	hba->pwr_info.lane_tx = 1;
	hba->pwr_info.pwr_rx = SLOWAUTO_MODE;
	hba->pwr_info.pwr_tx = SLOWAUTO_MODE;
	hba->pwr_info.hs_rate = 0;
पूर्ण

/**
 * ufshcd_get_max_pwr_mode - पढ़ोs the max घातer mode negotiated with device
 * @hba: per-adapter instance
 */
अटल पूर्णांक ufshcd_get_max_pwr_mode(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_pa_layer_attr *pwr_info = &hba->max_pwr_info.info;

	अगर (hba->max_pwr_info.is_valid)
		वापस 0;

	pwr_info->pwr_tx = FAST_MODE;
	pwr_info->pwr_rx = FAST_MODE;
	pwr_info->hs_rate = PA_HS_MODE_B;

	/* Get the connected lane count */
	ufshcd_dme_get(hba, UIC_ARG_MIB(PA_CONNECTEDRXDATALANES),
			&pwr_info->lane_rx);
	ufshcd_dme_get(hba, UIC_ARG_MIB(PA_CONNECTEDTXDATALANES),
			&pwr_info->lane_tx);

	अगर (!pwr_info->lane_rx || !pwr_info->lane_tx) अणु
		dev_err(hba->dev, "%s: invalid connected lanes value. rx=%d, tx=%d\n",
				__func__,
				pwr_info->lane_rx,
				pwr_info->lane_tx);
		वापस -EINVAL;
	पूर्ण

	/*
	 * First, get the maximum gears of HS speed.
	 * If a zero value, it means there is no HSGEAR capability.
	 * Then, get the maximum gears of PWM speed.
	 */
	ufshcd_dme_get(hba, UIC_ARG_MIB(PA_MAXRXHSGEAR), &pwr_info->gear_rx);
	अगर (!pwr_info->gear_rx) अणु
		ufshcd_dme_get(hba, UIC_ARG_MIB(PA_MAXRXPWMGEAR),
				&pwr_info->gear_rx);
		अगर (!pwr_info->gear_rx) अणु
			dev_err(hba->dev, "%s: invalid max pwm rx gear read = %d\n",
				__func__, pwr_info->gear_rx);
			वापस -EINVAL;
		पूर्ण
		pwr_info->pwr_rx = SLOW_MODE;
	पूर्ण

	ufshcd_dme_peer_get(hba, UIC_ARG_MIB(PA_MAXRXHSGEAR),
			&pwr_info->gear_tx);
	अगर (!pwr_info->gear_tx) अणु
		ufshcd_dme_peer_get(hba, UIC_ARG_MIB(PA_MAXRXPWMGEAR),
				&pwr_info->gear_tx);
		अगर (!pwr_info->gear_tx) अणु
			dev_err(hba->dev, "%s: invalid max pwm tx gear read = %d\n",
				__func__, pwr_info->gear_tx);
			वापस -EINVAL;
		पूर्ण
		pwr_info->pwr_tx = SLOW_MODE;
	पूर्ण

	hba->max_pwr_info.is_valid = true;
	वापस 0;
पूर्ण

अटल पूर्णांक ufshcd_change_घातer_mode(काष्ठा ufs_hba *hba,
			     काष्ठा ufs_pa_layer_attr *pwr_mode)
अणु
	पूर्णांक ret;

	/* अगर alपढ़ोy configured to the requested pwr_mode */
	अगर (!hba->क्रमce_pmc &&
	    pwr_mode->gear_rx == hba->pwr_info.gear_rx &&
	    pwr_mode->gear_tx == hba->pwr_info.gear_tx &&
	    pwr_mode->lane_rx == hba->pwr_info.lane_rx &&
	    pwr_mode->lane_tx == hba->pwr_info.lane_tx &&
	    pwr_mode->pwr_rx == hba->pwr_info.pwr_rx &&
	    pwr_mode->pwr_tx == hba->pwr_info.pwr_tx &&
	    pwr_mode->hs_rate == hba->pwr_info.hs_rate) अणु
		dev_dbg(hba->dev, "%s: power already configured\n", __func__);
		वापस 0;
	पूर्ण

	/*
	 * Configure attributes क्रम घातer mode change with below.
	 * - PA_RXGEAR, PA_ACTIVERXDATALANES, PA_RXTERMINATION,
	 * - PA_TXGEAR, PA_ACTIVETXDATALANES, PA_TXTERMINATION,
	 * - PA_HSSERIES
	 */
	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_RXGEAR), pwr_mode->gear_rx);
	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_ACTIVERXDATALANES),
			pwr_mode->lane_rx);
	अगर (pwr_mode->pwr_rx == FASTAUTO_MODE ||
			pwr_mode->pwr_rx == FAST_MODE)
		ufshcd_dme_set(hba, UIC_ARG_MIB(PA_RXTERMINATION), TRUE);
	अन्यथा
		ufshcd_dme_set(hba, UIC_ARG_MIB(PA_RXTERMINATION), FALSE);

	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_TXGEAR), pwr_mode->gear_tx);
	ufshcd_dme_set(hba, UIC_ARG_MIB(PA_ACTIVETXDATALANES),
			pwr_mode->lane_tx);
	अगर (pwr_mode->pwr_tx == FASTAUTO_MODE ||
			pwr_mode->pwr_tx == FAST_MODE)
		ufshcd_dme_set(hba, UIC_ARG_MIB(PA_TXTERMINATION), TRUE);
	अन्यथा
		ufshcd_dme_set(hba, UIC_ARG_MIB(PA_TXTERMINATION), FALSE);

	अगर (pwr_mode->pwr_rx == FASTAUTO_MODE ||
	    pwr_mode->pwr_tx == FASTAUTO_MODE ||
	    pwr_mode->pwr_rx == FAST_MODE ||
	    pwr_mode->pwr_tx == FAST_MODE)
		ufshcd_dme_set(hba, UIC_ARG_MIB(PA_HSSERIES),
						pwr_mode->hs_rate);

	अगर (!(hba->quirks & UFSHCD_QUIRK_SKIP_DEF_UNIPRO_TIMEOUT_SETTING)) अणु
		ufshcd_dme_set(hba, UIC_ARG_MIB(PA_PWRMODEUSERDATA0),
				DL_FC0ProtectionTimeOutVal_Default);
		ufshcd_dme_set(hba, UIC_ARG_MIB(PA_PWRMODEUSERDATA1),
				DL_TC0ReplayTimeOutVal_Default);
		ufshcd_dme_set(hba, UIC_ARG_MIB(PA_PWRMODEUSERDATA2),
				DL_AFC0ReqTimeOutVal_Default);
		ufshcd_dme_set(hba, UIC_ARG_MIB(PA_PWRMODEUSERDATA3),
				DL_FC1ProtectionTimeOutVal_Default);
		ufshcd_dme_set(hba, UIC_ARG_MIB(PA_PWRMODEUSERDATA4),
				DL_TC1ReplayTimeOutVal_Default);
		ufshcd_dme_set(hba, UIC_ARG_MIB(PA_PWRMODEUSERDATA5),
				DL_AFC1ReqTimeOutVal_Default);

		ufshcd_dme_set(hba, UIC_ARG_MIB(DME_LocalFC0ProtectionTimeOutVal),
				DL_FC0ProtectionTimeOutVal_Default);
		ufshcd_dme_set(hba, UIC_ARG_MIB(DME_LocalTC0ReplayTimeOutVal),
				DL_TC0ReplayTimeOutVal_Default);
		ufshcd_dme_set(hba, UIC_ARG_MIB(DME_LocalAFC0ReqTimeOutVal),
				DL_AFC0ReqTimeOutVal_Default);
	पूर्ण

	ret = ufshcd_uic_change_pwr_mode(hba, pwr_mode->pwr_rx << 4
			| pwr_mode->pwr_tx);

	अगर (ret) अणु
		dev_err(hba->dev,
			"%s: power mode change failed %d\n", __func__, ret);
	पूर्ण अन्यथा अणु
		ufshcd_vops_pwr_change_notअगरy(hba, POST_CHANGE, शून्य,
								pwr_mode);

		स_नकल(&hba->pwr_info, pwr_mode,
			माप(काष्ठा ufs_pa_layer_attr));
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ufshcd_config_pwr_mode - configure a new घातer mode
 * @hba: per-adapter instance
 * @desired_pwr_mode: desired घातer configuration
 */
पूर्णांक ufshcd_config_pwr_mode(काष्ठा ufs_hba *hba,
		काष्ठा ufs_pa_layer_attr *desired_pwr_mode)
अणु
	काष्ठा ufs_pa_layer_attr final_params = अणु 0 पूर्ण;
	पूर्णांक ret;

	ret = ufshcd_vops_pwr_change_notअगरy(hba, PRE_CHANGE,
					desired_pwr_mode, &final_params);

	अगर (ret)
		स_नकल(&final_params, desired_pwr_mode, माप(final_params));

	ret = ufshcd_change_घातer_mode(hba, &final_params);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_config_pwr_mode);

/**
 * ufshcd_complete_dev_init() - checks device पढ़ोiness
 * @hba: per-adapter instance
 *
 * Set fDeviceInit flag and poll until device toggles it.
 */
अटल पूर्णांक ufshcd_complete_dev_init(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err;
	bool flag_res = true;
	kसमय_प्रकार समयout;

	err = ufshcd_query_flag_retry(hba, UPIU_QUERY_OPCODE_SET_FLAG,
		QUERY_FLAG_IDN_FDEVICEINIT, 0, शून्य);
	अगर (err) अणु
		dev_err(hba->dev,
			"%s setting fDeviceInit flag failed with error %d\n",
			__func__, err);
		जाओ out;
	पूर्ण

	/* Poll fDeviceInit flag to be cleared */
	समयout = kसमय_add_ms(kसमय_get(), FDEVICEINIT_COMPL_TIMEOUT);
	करो अणु
		err = ufshcd_query_flag(hba, UPIU_QUERY_OPCODE_READ_FLAG,
					QUERY_FLAG_IDN_FDEVICEINIT, 0, &flag_res);
		अगर (!flag_res)
			अवरोध;
		usleep_range(5000, 10000);
	पूर्ण जबतक (kसमय_beक्रमe(kसमय_get(), समयout));

	अगर (err) अणु
		dev_err(hba->dev,
				"%s reading fDeviceInit flag failed with error %d\n",
				__func__, err);
	पूर्ण अन्यथा अगर (flag_res) अणु
		dev_err(hba->dev,
				"%s fDeviceInit was not cleared by the device\n",
				__func__);
		err = -EBUSY;
	पूर्ण
out:
	वापस err;
पूर्ण

/**
 * ufshcd_make_hba_operational - Make UFS controller operational
 * @hba: per adapter instance
 *
 * To bring UFS host controller to operational state,
 * 1. Enable required पूर्णांकerrupts
 * 2. Configure पूर्णांकerrupt aggregation
 * 3. Program UTRL and UTMRL base address
 * 4. Configure run-stop-रेजिस्टरs
 *
 * Returns 0 on success, non-zero value on failure
 */
पूर्णांक ufshcd_make_hba_operational(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err = 0;
	u32 reg;

	/* Enable required पूर्णांकerrupts */
	ufshcd_enable_पूर्णांकr(hba, UFSHCD_ENABLE_INTRS);

	/* Configure पूर्णांकerrupt aggregation */
	अगर (ufshcd_is_पूर्णांकr_aggr_allowed(hba))
		ufshcd_config_पूर्णांकr_aggr(hba, hba->nutrs - 1, INT_AGGR_DEF_TO);
	अन्यथा
		ufshcd_disable_पूर्णांकr_aggr(hba);

	/* Configure UTRL and UTMRL base address रेजिस्टरs */
	ufshcd_ग_लिखोl(hba, lower_32_bits(hba->utrdl_dma_addr),
			REG_UTP_TRANSFER_REQ_LIST_BASE_L);
	ufshcd_ग_लिखोl(hba, upper_32_bits(hba->utrdl_dma_addr),
			REG_UTP_TRANSFER_REQ_LIST_BASE_H);
	ufshcd_ग_लिखोl(hba, lower_32_bits(hba->uपंचांगrdl_dma_addr),
			REG_UTP_TASK_REQ_LIST_BASE_L);
	ufshcd_ग_लिखोl(hba, upper_32_bits(hba->uपंचांगrdl_dma_addr),
			REG_UTP_TASK_REQ_LIST_BASE_H);

	/*
	 * Make sure base address and पूर्णांकerrupt setup are updated beक्रमe
	 * enabling the run/stop रेजिस्टरs below.
	 */
	wmb();

	/*
	 * UCRDY, UTMRLDY and UTRLRDY bits must be 1
	 */
	reg = ufshcd_पढ़ोl(hba, REG_CONTROLLER_STATUS);
	अगर (!(ufshcd_get_lists_status(reg))) अणु
		ufshcd_enable_run_stop_reg(hba);
	पूर्ण अन्यथा अणु
		dev_err(hba->dev,
			"Host controller not ready to process requests");
		err = -EIO;
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_make_hba_operational);

/**
 * ufshcd_hba_stop - Send controller to reset state
 * @hba: per adapter instance
 */
अटल अंतरभूत व्योम ufshcd_hba_stop(काष्ठा ufs_hba *hba)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	/*
	 * Obtain the host lock to prevent that the controller is disabled
	 * जबतक the UFS पूर्णांकerrupt handler is active on another CPU.
	 */
	spin_lock_irqsave(hba->host->host_lock, flags);
	ufshcd_ग_लिखोl(hba, CONTROLLER_DISABLE,  REG_CONTROLLER_ENABLE);
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	err = ufshcd_रुको_क्रम_रेजिस्टर(hba, REG_CONTROLLER_ENABLE,
					CONTROLLER_ENABLE, CONTROLLER_DISABLE,
					10, 1);
	अगर (err)
		dev_err(hba->dev, "%s: Controller disable failed\n", __func__);
पूर्ण

/**
 * ufshcd_hba_execute_hce - initialize the controller
 * @hba: per adapter instance
 *
 * The controller resets itself and controller firmware initialization
 * sequence kicks off. When controller is पढ़ोy it will set
 * the Host Controller Enable bit to 1.
 *
 * Returns 0 on success, non-zero value on failure
 */
अटल पूर्णांक ufshcd_hba_execute_hce(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक retry_outer = 3;
	पूर्णांक retry_inner;

start:
	अगर (!ufshcd_is_hba_active(hba))
		/* change controller state to "reset state" */
		ufshcd_hba_stop(hba);

	/* UniPro link is disabled at this poपूर्णांक */
	ufshcd_set_link_off(hba);

	ufshcd_vops_hce_enable_notअगरy(hba, PRE_CHANGE);

	/* start controller initialization sequence */
	ufshcd_hba_start(hba);

	/*
	 * To initialize a UFS host controller HCE bit must be set to 1.
	 * During initialization the HCE bit value changes from 1->0->1.
	 * When the host controller completes initialization sequence
	 * it sets the value of HCE bit to 1. The same HCE bit is पढ़ो back
	 * to check अगर the controller has completed initialization sequence.
	 * So without this delay the value HCE = 1, set in the previous
	 * inकाष्ठाion might be पढ़ो back.
	 * This delay can be changed based on the controller.
	 */
	ufshcd_delay_us(hba->vps->hba_enable_delay_us, 100);

	/* रुको क्रम the host controller to complete initialization */
	retry_inner = 50;
	जबतक (ufshcd_is_hba_active(hba)) अणु
		अगर (retry_inner) अणु
			retry_inner--;
		पूर्ण अन्यथा अणु
			dev_err(hba->dev,
				"Controller enable failed\n");
			अगर (retry_outer) अणु
				retry_outer--;
				जाओ start;
			पूर्ण
			वापस -EIO;
		पूर्ण
		usleep_range(1000, 1100);
	पूर्ण

	/* enable UIC related पूर्णांकerrupts */
	ufshcd_enable_पूर्णांकr(hba, UFSHCD_UIC_MASK);

	ufshcd_vops_hce_enable_notअगरy(hba, POST_CHANGE);

	वापस 0;
पूर्ण

पूर्णांक ufshcd_hba_enable(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret;

	अगर (hba->quirks & UFSHCI_QUIRK_BROKEN_HCE) अणु
		ufshcd_set_link_off(hba);
		ufshcd_vops_hce_enable_notअगरy(hba, PRE_CHANGE);

		/* enable UIC related पूर्णांकerrupts */
		ufshcd_enable_पूर्णांकr(hba, UFSHCD_UIC_MASK);
		ret = ufshcd_dme_reset(hba);
		अगर (!ret) अणु
			ret = ufshcd_dme_enable(hba);
			अगर (!ret)
				ufshcd_vops_hce_enable_notअगरy(hba, POST_CHANGE);
			अगर (ret)
				dev_err(hba->dev,
					"Host controller enable failed with non-hce\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = ufshcd_hba_execute_hce(hba);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_hba_enable);

अटल पूर्णांक ufshcd_disable_tx_lcc(काष्ठा ufs_hba *hba, bool peer)
अणु
	पूर्णांक tx_lanes = 0, i, err = 0;

	अगर (!peer)
		ufshcd_dme_get(hba, UIC_ARG_MIB(PA_CONNECTEDTXDATALANES),
			       &tx_lanes);
	अन्यथा
		ufshcd_dme_peer_get(hba, UIC_ARG_MIB(PA_CONNECTEDTXDATALANES),
				    &tx_lanes);
	क्रम (i = 0; i < tx_lanes; i++) अणु
		अगर (!peer)
			err = ufshcd_dme_set(hba,
				UIC_ARG_MIB_SEL(TX_LCC_ENABLE,
					UIC_ARG_MPHY_TX_GEN_SEL_INDEX(i)),
					0);
		अन्यथा
			err = ufshcd_dme_peer_set(hba,
				UIC_ARG_MIB_SEL(TX_LCC_ENABLE,
					UIC_ARG_MPHY_TX_GEN_SEL_INDEX(i)),
					0);
		अगर (err) अणु
			dev_err(hba->dev, "%s: TX LCC Disable failed, peer = %d, lane = %d, err = %d",
				__func__, peer, i, err);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_disable_device_tx_lcc(काष्ठा ufs_hba *hba)
अणु
	वापस ufshcd_disable_tx_lcc(hba, true);
पूर्ण

व्योम ufshcd_update_evt_hist(काष्ठा ufs_hba *hba, u32 id, u32 val)
अणु
	काष्ठा ufs_event_hist *e;

	अगर (id >= UFS_EVT_CNT)
		वापस;

	e = &hba->ufs_stats.event[id];
	e->val[e->pos] = val;
	e->tstamp[e->pos] = kसमय_get();
	e->cnt += 1;
	e->pos = (e->pos + 1) % UFS_EVENT_HIST_LENGTH;

	ufshcd_vops_event_notअगरy(hba, id, &val);
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_update_evt_hist);

/**
 * ufshcd_link_startup - Initialize unipro link startup
 * @hba: per adapter instance
 *
 * Returns 0 क्रम success, non-zero in हाल of failure
 */
अटल पूर्णांक ufshcd_link_startup(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret;
	पूर्णांक retries = DME_LINKSTARTUP_RETRIES;
	bool link_startup_again = false;

	/*
	 * If UFS device isn't active then we will have to issue link startup
	 * 2 बार to make sure the device state move to active.
	 */
	अगर (!ufshcd_is_ufs_dev_active(hba))
		link_startup_again = true;

link_startup:
	करो अणु
		ufshcd_vops_link_startup_notअगरy(hba, PRE_CHANGE);

		ret = ufshcd_dme_link_startup(hba);

		/* check अगर device is detected by पूर्णांकer-connect layer */
		अगर (!ret && !ufshcd_is_device_present(hba)) अणु
			ufshcd_update_evt_hist(hba,
					       UFS_EVT_LINK_STARTUP_FAIL,
					       0);
			dev_err(hba->dev, "%s: Device not present\n", __func__);
			ret = -ENXIO;
			जाओ out;
		पूर्ण

		/*
		 * DME link lost indication is only received when link is up,
		 * but we can't be sure अगर the link is up until link startup
		 * succeeds. So reset the local Uni-Pro and try again.
		 */
		अगर (ret && ufshcd_hba_enable(hba)) अणु
			ufshcd_update_evt_hist(hba,
					       UFS_EVT_LINK_STARTUP_FAIL,
					       (u32)ret);
			जाओ out;
		पूर्ण
	पूर्ण जबतक (ret && retries--);

	अगर (ret) अणु
		/* failed to get the link up... retire */
		ufshcd_update_evt_hist(hba,
				       UFS_EVT_LINK_STARTUP_FAIL,
				       (u32)ret);
		जाओ out;
	पूर्ण

	अगर (link_startup_again) अणु
		link_startup_again = false;
		retries = DME_LINKSTARTUP_RETRIES;
		जाओ link_startup;
	पूर्ण

	/* Mark that link is up in PWM-G1, 1-lane, SLOW-AUTO mode */
	ufshcd_init_pwr_info(hba);
	ufshcd_prपूर्णांक_pwr_info(hba);

	अगर (hba->quirks & UFSHCD_QUIRK_BROKEN_LCC) अणु
		ret = ufshcd_disable_device_tx_lcc(hba);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* Include any host controller configuration via UIC commands */
	ret = ufshcd_vops_link_startup_notअगरy(hba, POST_CHANGE);
	अगर (ret)
		जाओ out;

	/* Clear UECPA once due to LINERESET has happened during LINK_STARTUP */
	ufshcd_पढ़ोl(hba, REG_UIC_ERROR_CODE_PHY_ADAPTER_LAYER);
	ret = ufshcd_make_hba_operational(hba);
out:
	अगर (ret) अणु
		dev_err(hba->dev, "link startup failed %d\n", ret);
		ufshcd_prपूर्णांक_host_state(hba);
		ufshcd_prपूर्णांक_pwr_info(hba);
		ufshcd_prपूर्णांक_evt_hist(hba);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * ufshcd_verअगरy_dev_init() - Verअगरy device initialization
 * @hba: per-adapter instance
 *
 * Send NOP OUT UPIU and रुको क्रम NOP IN response to check whether the
 * device Transport Protocol (UTP) layer is पढ़ोy after a reset.
 * If the UTP layer at the device side is not initialized, it may
 * not respond with NOP IN UPIU within समयout of %NOP_OUT_TIMEOUT
 * and we retry sending NOP OUT क्रम %NOP_OUT_RETRIES iterations.
 */
अटल पूर्णांक ufshcd_verअगरy_dev_init(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err = 0;
	पूर्णांक retries;

	ufshcd_hold(hba, false);
	mutex_lock(&hba->dev_cmd.lock);
	क्रम (retries = NOP_OUT_RETRIES; retries > 0; retries--) अणु
		err = ufshcd_exec_dev_cmd(hba, DEV_CMD_TYPE_NOP,
					       NOP_OUT_TIMEOUT);

		अगर (!err || err == -ETIMEDOUT)
			अवरोध;

		dev_dbg(hba->dev, "%s: error %d retrying\n", __func__, err);
	पूर्ण
	mutex_unlock(&hba->dev_cmd.lock);
	ufshcd_release(hba);

	अगर (err)
		dev_err(hba->dev, "%s: NOP OUT failed %d\n", __func__, err);
	वापस err;
पूर्ण

/**
 * ufshcd_set_queue_depth - set lun queue depth
 * @sdev: poपूर्णांकer to SCSI device
 *
 * Read bLUQueueDepth value and activate scsi tagged command
 * queueing. For WLUN, queue depth is set to 1. For best-efक्रमt
 * हालs (bLUQueueDepth = 0) the queue depth is set to a maximum
 * value that host can queue.
 */
अटल व्योम ufshcd_set_queue_depth(काष्ठा scsi_device *sdev)
अणु
	पूर्णांक ret = 0;
	u8 lun_qdepth;
	काष्ठा ufs_hba *hba;

	hba = shost_priv(sdev->host);

	lun_qdepth = hba->nutrs;
	ret = ufshcd_पढ़ो_unit_desc_param(hba,
					  ufshcd_scsi_to_upiu_lun(sdev->lun),
					  UNIT_DESC_PARAM_LU_Q_DEPTH,
					  &lun_qdepth,
					  माप(lun_qdepth));

	/* Some WLUN करोesn't support unit descriptor */
	अगर (ret == -EOPNOTSUPP)
		lun_qdepth = 1;
	अन्यथा अगर (!lun_qdepth)
		/* eventually, we can figure out the real queue depth */
		lun_qdepth = hba->nutrs;
	अन्यथा
		lun_qdepth = min_t(पूर्णांक, lun_qdepth, hba->nutrs);

	dev_dbg(hba->dev, "%s: activate tcq with queue depth %d\n",
			__func__, lun_qdepth);
	scsi_change_queue_depth(sdev, lun_qdepth);
पूर्ण

/*
 * ufshcd_get_lu_wp - वापसs the "b_lu_write_protect" from UNIT DESCRIPTOR
 * @hba: per-adapter instance
 * @lun: UFS device lun id
 * @b_lu_ग_लिखो_protect: poपूर्णांकer to buffer to hold the LU's ग_लिखो protect info
 *
 * Returns 0 in हाल of success and b_lu_ग_लिखो_protect status would be वापसed
 * @b_lu_ग_लिखो_protect parameter.
 * Returns -ENOTSUPP अगर पढ़ोing b_lu_ग_लिखो_protect is not supported.
 * Returns -EINVAL in हाल of invalid parameters passed to this function.
 */
अटल पूर्णांक ufshcd_get_lu_wp(काष्ठा ufs_hba *hba,
			    u8 lun,
			    u8 *b_lu_ग_लिखो_protect)
अणु
	पूर्णांक ret;

	अगर (!b_lu_ग_लिखो_protect)
		ret = -EINVAL;
	/*
	 * According to UFS device spec, RPMB LU can't be ग_लिखो
	 * रक्षित so skip पढ़ोing bLUWriteProtect parameter क्रम
	 * it. For other W-LUs, UNIT DESCRIPTOR is not available.
	 */
	अन्यथा अगर (lun >= hba->dev_info.max_lu_supported)
		ret = -ENOTSUPP;
	अन्यथा
		ret = ufshcd_पढ़ो_unit_desc_param(hba,
					  lun,
					  UNIT_DESC_PARAM_LU_WR_PROTECT,
					  b_lu_ग_लिखो_protect,
					  माप(*b_lu_ग_लिखो_protect));
	वापस ret;
पूर्ण

/**
 * ufshcd_get_lu_घातer_on_wp_status - get LU's घातer on ग_लिखो protect
 * status
 * @hba: per-adapter instance
 * @sdev: poपूर्णांकer to SCSI device
 *
 */
अटल अंतरभूत व्योम ufshcd_get_lu_घातer_on_wp_status(काष्ठा ufs_hba *hba,
						    काष्ठा scsi_device *sdev)
अणु
	अगर (hba->dev_info.f_घातer_on_wp_en &&
	    !hba->dev_info.is_lu_घातer_on_wp) अणु
		u8 b_lu_ग_लिखो_protect;

		अगर (!ufshcd_get_lu_wp(hba, ufshcd_scsi_to_upiu_lun(sdev->lun),
				      &b_lu_ग_लिखो_protect) &&
		    (b_lu_ग_लिखो_protect == UFS_LU_POWER_ON_WP))
			hba->dev_info.is_lu_घातer_on_wp = true;
	पूर्ण
पूर्ण

/**
 * ufshcd_slave_alloc - handle initial SCSI device configurations
 * @sdev: poपूर्णांकer to SCSI device
 *
 * Returns success
 */
अटल पूर्णांक ufshcd_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा ufs_hba *hba;

	hba = shost_priv(sdev->host);

	/* Mode sense(6) is not supported by UFS, so use Mode sense(10) */
	sdev->use_10_क्रम_ms = 1;

	/* DBD field should be set to 1 in mode sense(10) */
	sdev->set_dbd_क्रम_ms = 1;

	/* allow SCSI layer to restart the device in हाल of errors */
	sdev->allow_restart = 1;

	/* REPORT SUPPORTED OPERATION CODES is not supported */
	sdev->no_report_opcodes = 1;

	/* WRITE_SAME command is not supported */
	sdev->no_ग_लिखो_same = 1;

	ufshcd_set_queue_depth(sdev);

	ufshcd_get_lu_घातer_on_wp_status(hba, sdev);

	वापस 0;
पूर्ण

/**
 * ufshcd_change_queue_depth - change queue depth
 * @sdev: poपूर्णांकer to SCSI device
 * @depth: required depth to set
 *
 * Change queue depth and make sure the max. limits are not crossed.
 */
अटल पूर्णांक ufshcd_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक depth)
अणु
	काष्ठा ufs_hba *hba = shost_priv(sdev->host);

	अगर (depth > hba->nutrs)
		depth = hba->nutrs;
	वापस scsi_change_queue_depth(sdev, depth);
पूर्ण

/**
 * ufshcd_slave_configure - adjust SCSI device configurations
 * @sdev: poपूर्णांकer to SCSI device
 */
अटल पूर्णांक ufshcd_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा ufs_hba *hba = shost_priv(sdev->host);
	काष्ठा request_queue *q = sdev->request_queue;

	blk_queue_update_dma_pad(q, PRDT_DATA_BYTE_COUNT_PAD - 1);
	अगर (hba->quirks & UFSHCD_QUIRK_ALIGN_SG_WITH_PAGE_SIZE)
		blk_queue_update_dma_alignment(q, PAGE_SIZE - 1);

	अगर (ufshcd_is_rpm_स्वतःsuspend_allowed(hba))
		sdev->rpm_स्वतःsuspend = 1;

	ufshcd_crypto_setup_rq_keyslot_manager(hba, q);

	वापस 0;
पूर्ण

/**
 * ufshcd_slave_destroy - हटाओ SCSI device configurations
 * @sdev: poपूर्णांकer to SCSI device
 */
अटल व्योम ufshcd_slave_destroy(काष्ठा scsi_device *sdev)
अणु
	काष्ठा ufs_hba *hba;

	hba = shost_priv(sdev->host);
	/* Drop the reference as it won't be needed anymore */
	अगर (ufshcd_scsi_to_upiu_lun(sdev->lun) == UFS_UPIU_UFS_DEVICE_WLUN) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(hba->host->host_lock, flags);
		hba->sdev_ufs_device = शून्य;
		spin_unlock_irqrestore(hba->host->host_lock, flags);
	पूर्ण
पूर्ण

/**
 * ufshcd_scsi_cmd_status - Update SCSI command result based on SCSI status
 * @lrbp: poपूर्णांकer to local reference block of completed command
 * @scsi_status: SCSI command status
 *
 * Returns value base on SCSI command status
 */
अटल अंतरभूत पूर्णांक
ufshcd_scsi_cmd_status(काष्ठा ufshcd_lrb *lrbp, पूर्णांक scsi_status)
अणु
	पूर्णांक result = 0;

	चयन (scsi_status) अणु
	हाल SAM_STAT_CHECK_CONDITION:
		ufshcd_copy_sense_data(lrbp);
		fallthrough;
	हाल SAM_STAT_GOOD:
		result |= DID_OK << 16 | scsi_status;
		अवरोध;
	हाल SAM_STAT_TASK_SET_FULL:
	हाल SAM_STAT_BUSY:
	हाल SAM_STAT_TASK_ABORTED:
		ufshcd_copy_sense_data(lrbp);
		result |= scsi_status;
		अवरोध;
	शेष:
		result |= DID_ERROR << 16;
		अवरोध;
	पूर्ण /* end of चयन */

	वापस result;
पूर्ण

/**
 * ufshcd_transfer_rsp_status - Get overall status of the response
 * @hba: per adapter instance
 * @lrbp: poपूर्णांकer to local reference block of completed command
 *
 * Returns result of the command to notअगरy SCSI midlayer
 */
अटल अंतरभूत पूर्णांक
ufshcd_transfer_rsp_status(काष्ठा ufs_hba *hba, काष्ठा ufshcd_lrb *lrbp)
अणु
	पूर्णांक result = 0;
	पूर्णांक scsi_status;
	पूर्णांक ocs;

	/* overall command status of utrd */
	ocs = ufshcd_get_tr_ocs(lrbp);

	अगर (hba->quirks & UFSHCD_QUIRK_BROKEN_OCS_FATAL_ERROR) अणु
		अगर (be32_to_cpu(lrbp->ucd_rsp_ptr->header.dword_1) &
					MASK_RSP_UPIU_RESULT)
			ocs = OCS_SUCCESS;
	पूर्ण

	चयन (ocs) अणु
	हाल OCS_SUCCESS:
		result = ufshcd_get_req_rsp(lrbp->ucd_rsp_ptr);
		hba->ufs_stats.last_hibern8_निकास_tstamp = kसमय_set(0, 0);
		चयन (result) अणु
		हाल UPIU_TRANSACTION_RESPONSE:
			/*
			 * get the response UPIU result to extract
			 * the SCSI command status
			 */
			result = ufshcd_get_rsp_upiu_result(lrbp->ucd_rsp_ptr);

			/*
			 * get the result based on SCSI status response
			 * to notअगरy the SCSI midlayer of the command status
			 */
			scsi_status = result & MASK_SCSI_STATUS;
			result = ufshcd_scsi_cmd_status(lrbp, scsi_status);

			/*
			 * Currently we are only supporting BKOPs exception
			 * events hence we can ignore BKOPs exception event
			 * during घातer management callbacks. BKOPs exception
			 * event is not expected to be उठाओd in runसमय suspend
			 * callback as it allows the urgent bkops.
			 * During प्रणाली suspend, we are anyway क्रमcefully
			 * disabling the bkops and अगर urgent bkops is needed
			 * it will be enabled on प्रणाली resume. Long term
			 * solution could be to पात the प्रणाली suspend अगर
			 * UFS device needs urgent BKOPs.
			 */
			अगर (!hba->pm_op_in_progress &&
			    !ufshcd_eh_in_progress(hba) &&
			    ufshcd_is_exception_event(lrbp->ucd_rsp_ptr) &&
			    schedule_work(&hba->eeh_work)) अणु
				/*
				 * Prevent suspend once eeh_work is scheduled
				 * to aव्योम deadlock between ufshcd_suspend
				 * and exception event handler.
				 */
				pm_runसमय_get_noresume(hba->dev);
			पूर्ण
			अवरोध;
		हाल UPIU_TRANSACTION_REJECT_UPIU:
			/* TODO: handle Reject UPIU Response */
			result = DID_ERROR << 16;
			dev_err(hba->dev,
				"Reject UPIU not fully implemented\n");
			अवरोध;
		शेष:
			dev_err(hba->dev,
				"Unexpected request response code = %x\n",
				result);
			result = DID_ERROR << 16;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल OCS_ABORTED:
		result |= DID_ABORT << 16;
		अवरोध;
	हाल OCS_INVALID_COMMAND_STATUS:
		result |= DID_REQUEUE << 16;
		अवरोध;
	हाल OCS_INVALID_CMD_TABLE_ATTR:
	हाल OCS_INVALID_PRDT_ATTR:
	हाल OCS_MISMATCH_DATA_BUF_SIZE:
	हाल OCS_MISMATCH_RESP_UPIU_SIZE:
	हाल OCS_PEER_COMM_FAILURE:
	हाल OCS_FATAL_ERROR:
	हाल OCS_DEVICE_FATAL_ERROR:
	हाल OCS_INVALID_CRYPTO_CONFIG:
	हाल OCS_GENERAL_CRYPTO_ERROR:
	शेष:
		result |= DID_ERROR << 16;
		dev_err(hba->dev,
				"OCS error from controller = %x for tag %d\n",
				ocs, lrbp->task_tag);
		ufshcd_prपूर्णांक_evt_hist(hba);
		ufshcd_prपूर्णांक_host_state(hba);
		अवरोध;
	पूर्ण /* end of चयन */

	अगर ((host_byte(result) != DID_OK) &&
	    (host_byte(result) != DID_REQUEUE) && !hba->silence_err_logs)
		ufshcd_prपूर्णांक_trs(hba, 1 << lrbp->task_tag, true);
	वापस result;
पूर्ण

/**
 * ufshcd_uic_cmd_compl - handle completion of uic command
 * @hba: per adapter instance
 * @पूर्णांकr_status: पूर्णांकerrupt status generated by the controller
 *
 * Returns
 *  IRQ_HANDLED - If पूर्णांकerrupt is valid
 *  IRQ_NONE    - If invalid पूर्णांकerrupt
 */
अटल irqवापस_t ufshcd_uic_cmd_compl(काष्ठा ufs_hba *hba, u32 पूर्णांकr_status)
अणु
	irqवापस_t retval = IRQ_NONE;

	अगर ((पूर्णांकr_status & UIC_COMMAND_COMPL) && hba->active_uic_cmd) अणु
		hba->active_uic_cmd->argument2 |=
			ufshcd_get_uic_cmd_result(hba);
		hba->active_uic_cmd->argument3 =
			ufshcd_get_dme_attr_val(hba);
		अगर (!hba->uic_async_करोne)
			hba->active_uic_cmd->cmd_active = 0;
		complete(&hba->active_uic_cmd->करोne);
		retval = IRQ_HANDLED;
	पूर्ण

	अगर ((पूर्णांकr_status & UFSHCD_UIC_PWR_MASK) && hba->uic_async_करोne) अणु
		hba->active_uic_cmd->cmd_active = 0;
		complete(hba->uic_async_करोne);
		retval = IRQ_HANDLED;
	पूर्ण

	अगर (retval == IRQ_HANDLED)
		ufshcd_add_uic_command_trace(hba, hba->active_uic_cmd,
					     UFS_CMD_COMP);
	वापस retval;
पूर्ण

/**
 * __ufshcd_transfer_req_compl - handle SCSI and query command completion
 * @hba: per adapter instance
 * @completed_reqs: requests to complete
 */
अटल व्योम __ufshcd_transfer_req_compl(काष्ठा ufs_hba *hba,
					अचिन्हित दीर्घ completed_reqs)
अणु
	काष्ठा ufshcd_lrb *lrbp;
	काष्ठा scsi_cmnd *cmd;
	पूर्णांक result;
	पूर्णांक index;
	bool update_scaling = false;

	क्रम_each_set_bit(index, &completed_reqs, hba->nutrs) अणु
		lrbp = &hba->lrb[index];
		lrbp->in_use = false;
		lrbp->compl_समय_stamp = kसमय_get();
		cmd = lrbp->cmd;
		अगर (cmd) अणु
			ufshcd_add_command_trace(hba, index, UFS_CMD_COMP);
			result = ufshcd_transfer_rsp_status(hba, lrbp);
			scsi_dma_unmap(cmd);
			cmd->result = result;
			/* Mark completed command as शून्य in LRB */
			lrbp->cmd = शून्य;
			/* Do not touch lrbp after scsi करोne */
			cmd->scsi_करोne(cmd);
			__ufshcd_release(hba);
			update_scaling = true;
		पूर्ण अन्यथा अगर (lrbp->command_type == UTP_CMD_TYPE_DEV_MANAGE ||
			lrbp->command_type == UTP_CMD_TYPE_UFS_STORAGE) अणु
			अगर (hba->dev_cmd.complete) अणु
				ufshcd_add_command_trace(hba, index,
							 UFS_DEV_COMP);
				complete(hba->dev_cmd.complete);
				update_scaling = true;
			पूर्ण
		पूर्ण
		अगर (ufshcd_is_clkscaling_supported(hba) && update_scaling)
			hba->clk_scaling.active_reqs--;
	पूर्ण

	/* clear corresponding bits of completed commands */
	hba->outstanding_reqs ^= completed_reqs;

	ufshcd_clk_scaling_update_busy(hba);
पूर्ण

/**
 * ufshcd_transfer_req_compl - handle SCSI and query command completion
 * @hba: per adapter instance
 *
 * Returns
 *  IRQ_HANDLED - If पूर्णांकerrupt is valid
 *  IRQ_NONE    - If invalid पूर्णांकerrupt
 */
अटल irqवापस_t ufshcd_transfer_req_compl(काष्ठा ufs_hba *hba)
अणु
	अचिन्हित दीर्घ completed_reqs;
	u32 tr_करोorbell;

	/* Resetting पूर्णांकerrupt aggregation counters first and पढ़ोing the
	 * DOOR_BELL afterward allows us to handle all the completed requests.
	 * In order to prevent other पूर्णांकerrupts starvation the DB is पढ़ो once
	 * after reset. The करोwn side of this solution is the possibility of
	 * false पूर्णांकerrupt अगर device completes another request after resetting
	 * aggregation and beक्रमe पढ़ोing the DB.
	 */
	अगर (ufshcd_is_पूर्णांकr_aggr_allowed(hba) &&
	    !(hba->quirks & UFSHCI_QUIRK_SKIP_RESET_INTR_AGGR))
		ufshcd_reset_पूर्णांकr_aggr(hba);

	tr_करोorbell = ufshcd_पढ़ोl(hba, REG_UTP_TRANSFER_REQ_DOOR_BELL);
	completed_reqs = tr_करोorbell ^ hba->outstanding_reqs;

	अगर (completed_reqs) अणु
		__ufshcd_transfer_req_compl(hba, completed_reqs);
		वापस IRQ_HANDLED;
	पूर्ण अन्यथा अणु
		वापस IRQ_NONE;
	पूर्ण
पूर्ण

पूर्णांक __ufshcd_ग_लिखो_ee_control(काष्ठा ufs_hba *hba, u32 ee_ctrl_mask)
अणु
	वापस ufshcd_query_attr_retry(hba, UPIU_QUERY_OPCODE_WRITE_ATTR,
				       QUERY_ATTR_IDN_EE_CONTROL, 0, 0,
				       &ee_ctrl_mask);
पूर्ण

पूर्णांक ufshcd_ग_लिखो_ee_control(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err;

	mutex_lock(&hba->ee_ctrl_mutex);
	err = __ufshcd_ग_लिखो_ee_control(hba, hba->ee_ctrl_mask);
	mutex_unlock(&hba->ee_ctrl_mutex);
	अगर (err)
		dev_err(hba->dev, "%s: failed to write ee control %d\n",
			__func__, err);
	वापस err;
पूर्ण

पूर्णांक ufshcd_update_ee_control(काष्ठा ufs_hba *hba, u16 *mask, u16 *other_mask,
			     u16 set, u16 clr)
अणु
	u16 new_mask, ee_ctrl_mask;
	पूर्णांक err = 0;

	mutex_lock(&hba->ee_ctrl_mutex);
	new_mask = (*mask & ~clr) | set;
	ee_ctrl_mask = new_mask | *other_mask;
	अगर (ee_ctrl_mask != hba->ee_ctrl_mask)
		err = __ufshcd_ग_लिखो_ee_control(hba, ee_ctrl_mask);
	/* Still need to update 'mask' even if 'ee_ctrl_mask' was unchanged */
	अगर (!err) अणु
		hba->ee_ctrl_mask = ee_ctrl_mask;
		*mask = new_mask;
	पूर्ण
	mutex_unlock(&hba->ee_ctrl_mutex);
	वापस err;
पूर्ण

/**
 * ufshcd_disable_ee - disable exception event
 * @hba: per-adapter instance
 * @mask: exception event to disable
 *
 * Disables exception event in the device so that the EVENT_ALERT
 * bit is not set.
 *
 * Returns zero on success, non-zero error value on failure.
 */
अटल अंतरभूत पूर्णांक ufshcd_disable_ee(काष्ठा ufs_hba *hba, u16 mask)
अणु
	वापस ufshcd_update_ee_drv_mask(hba, 0, mask);
पूर्ण

/**
 * ufshcd_enable_ee - enable exception event
 * @hba: per-adapter instance
 * @mask: exception event to enable
 *
 * Enable corresponding exception event in the device to allow
 * device to alert host in critical scenarios.
 *
 * Returns zero on success, non-zero error value on failure.
 */
अटल अंतरभूत पूर्णांक ufshcd_enable_ee(काष्ठा ufs_hba *hba, u16 mask)
अणु
	वापस ufshcd_update_ee_drv_mask(hba, mask, 0);
पूर्ण

/**
 * ufshcd_enable_स्वतः_bkops - Allow device managed BKOPS
 * @hba: per-adapter instance
 *
 * Allow device to manage background operations on its own. Enabling
 * this might lead to inconsistent latencies during normal data transfers
 * as the device is allowed to manage its own way of handling background
 * operations.
 *
 * Returns zero on success, non-zero on failure.
 */
अटल पूर्णांक ufshcd_enable_स्वतः_bkops(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err = 0;

	अगर (hba->स्वतः_bkops_enabled)
		जाओ out;

	err = ufshcd_query_flag_retry(hba, UPIU_QUERY_OPCODE_SET_FLAG,
			QUERY_FLAG_IDN_BKOPS_EN, 0, शून्य);
	अगर (err) अणु
		dev_err(hba->dev, "%s: failed to enable bkops %d\n",
				__func__, err);
		जाओ out;
	पूर्ण

	hba->स्वतः_bkops_enabled = true;
	trace_ufshcd_स्वतः_bkops_state(dev_name(hba->dev), "Enabled");

	/* No need of URGENT_BKOPS exception from the device */
	err = ufshcd_disable_ee(hba, MASK_EE_URGENT_BKOPS);
	अगर (err)
		dev_err(hba->dev, "%s: failed to disable exception event %d\n",
				__func__, err);
out:
	वापस err;
पूर्ण

/**
 * ufshcd_disable_स्वतः_bkops - block device in करोing background operations
 * @hba: per-adapter instance
 *
 * Disabling background operations improves command response latency but
 * has drawback of device moving पूर्णांकo critical state where the device is
 * not-operable. Make sure to call ufshcd_enable_स्वतः_bkops() whenever the
 * host is idle so that BKOPS are managed effectively without any negative
 * impacts.
 *
 * Returns zero on success, non-zero on failure.
 */
अटल पूर्णांक ufshcd_disable_स्वतः_bkops(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err = 0;

	अगर (!hba->स्वतः_bkops_enabled)
		जाओ out;

	/*
	 * If host assisted BKOPs is to be enabled, make sure
	 * urgent bkops exception is allowed.
	 */
	err = ufshcd_enable_ee(hba, MASK_EE_URGENT_BKOPS);
	अगर (err) अणु
		dev_err(hba->dev, "%s: failed to enable exception event %d\n",
				__func__, err);
		जाओ out;
	पूर्ण

	err = ufshcd_query_flag_retry(hba, UPIU_QUERY_OPCODE_CLEAR_FLAG,
			QUERY_FLAG_IDN_BKOPS_EN, 0, शून्य);
	अगर (err) अणु
		dev_err(hba->dev, "%s: failed to disable bkops %d\n",
				__func__, err);
		ufshcd_disable_ee(hba, MASK_EE_URGENT_BKOPS);
		जाओ out;
	पूर्ण

	hba->स्वतः_bkops_enabled = false;
	trace_ufshcd_स्वतः_bkops_state(dev_name(hba->dev), "Disabled");
	hba->is_urgent_bkops_lvl_checked = false;
out:
	वापस err;
पूर्ण

/**
 * ufshcd_क्रमce_reset_स्वतः_bkops - क्रमce reset स्वतः bkops state
 * @hba: per adapter instance
 *
 * After a device reset the device may toggle the BKOPS_EN flag
 * to शेष value. The s/w tracking variables should be updated
 * as well. This function would change the स्वतः-bkops state based on
 * UFSHCD_CAP_KEEP_AUTO_BKOPS_ENABLED_EXCEPT_SUSPEND.
 */
अटल व्योम ufshcd_क्रमce_reset_स्वतः_bkops(काष्ठा ufs_hba *hba)
अणु
	अगर (ufshcd_keep_स्वतःbkops_enabled_except_suspend(hba)) अणु
		hba->स्वतः_bkops_enabled = false;
		hba->ee_ctrl_mask |= MASK_EE_URGENT_BKOPS;
		ufshcd_enable_स्वतः_bkops(hba);
	पूर्ण अन्यथा अणु
		hba->स्वतः_bkops_enabled = true;
		hba->ee_ctrl_mask &= ~MASK_EE_URGENT_BKOPS;
		ufshcd_disable_स्वतः_bkops(hba);
	पूर्ण
	hba->urgent_bkops_lvl = BKOPS_STATUS_PERF_IMPACT;
	hba->is_urgent_bkops_lvl_checked = false;
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_get_bkops_status(काष्ठा ufs_hba *hba, u32 *status)
अणु
	वापस ufshcd_query_attr_retry(hba, UPIU_QUERY_OPCODE_READ_ATTR,
			QUERY_ATTR_IDN_BKOPS_STATUS, 0, 0, status);
पूर्ण

/**
 * ufshcd_bkops_ctrl - control the स्वतः bkops based on current bkops status
 * @hba: per-adapter instance
 * @status: bkops_status value
 *
 * Read the bkops_status from the UFS device and Enable fBackgroundOpsEn
 * flag in the device to permit background operations अगर the device
 * bkops_status is greater than or equal to "status" argument passed to
 * this function, disable otherwise.
 *
 * Returns 0 क्रम success, non-zero in हाल of failure.
 *
 * NOTE: Caller of this function can check the "hba->auto_bkops_enabled" flag
 * to know whether स्वतः bkops is enabled or disabled after this function
 * वापसs control to it.
 */
अटल पूर्णांक ufshcd_bkops_ctrl(काष्ठा ufs_hba *hba,
			     क्रमागत bkops_status status)
अणु
	पूर्णांक err;
	u32 curr_status = 0;

	err = ufshcd_get_bkops_status(hba, &curr_status);
	अगर (err) अणु
		dev_err(hba->dev, "%s: failed to get BKOPS status %d\n",
				__func__, err);
		जाओ out;
	पूर्ण अन्यथा अगर (curr_status > BKOPS_STATUS_MAX) अणु
		dev_err(hba->dev, "%s: invalid BKOPS status %d\n",
				__func__, curr_status);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (curr_status >= status)
		err = ufshcd_enable_स्वतः_bkops(hba);
	अन्यथा
		err = ufshcd_disable_स्वतः_bkops(hba);
out:
	वापस err;
पूर्ण

/**
 * ufshcd_urgent_bkops - handle urgent bkops exception event
 * @hba: per-adapter instance
 *
 * Enable fBackgroundOpsEn flag in the device to permit background
 * operations.
 *
 * If BKOPs is enabled, this function वापसs 0, 1 अगर the bkops in not enabled
 * and negative error value क्रम any other failure.
 */
अटल पूर्णांक ufshcd_urgent_bkops(काष्ठा ufs_hba *hba)
अणु
	वापस ufshcd_bkops_ctrl(hba, hba->urgent_bkops_lvl);
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_get_ee_status(काष्ठा ufs_hba *hba, u32 *status)
अणु
	वापस ufshcd_query_attr_retry(hba, UPIU_QUERY_OPCODE_READ_ATTR,
			QUERY_ATTR_IDN_EE_STATUS, 0, 0, status);
पूर्ण

अटल व्योम ufshcd_bkops_exception_event_handler(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err;
	u32 curr_status = 0;

	अगर (hba->is_urgent_bkops_lvl_checked)
		जाओ enable_स्वतः_bkops;

	err = ufshcd_get_bkops_status(hba, &curr_status);
	अगर (err) अणु
		dev_err(hba->dev, "%s: failed to get BKOPS status %d\n",
				__func__, err);
		जाओ out;
	पूर्ण

	/*
	 * We are seeing that some devices are raising the urgent bkops
	 * exception events even when BKOPS status करोesn't indicate perक्रमmace
	 * impacted or critical. Handle these device by determining their urgent
	 * bkops status at runसमय.
	 */
	अगर (curr_status < BKOPS_STATUS_PERF_IMPACT) अणु
		dev_err(hba->dev, "%s: device raised urgent BKOPS exception for bkops status %d\n",
				__func__, curr_status);
		/* update the current status as the urgent bkops level */
		hba->urgent_bkops_lvl = curr_status;
		hba->is_urgent_bkops_lvl_checked = true;
	पूर्ण

enable_स्वतः_bkops:
	err = ufshcd_enable_स्वतः_bkops(hba);
out:
	अगर (err < 0)
		dev_err(hba->dev, "%s: failed to handle urgent bkops %d\n",
				__func__, err);
पूर्ण

अटल पूर्णांक __ufshcd_wb_toggle(काष्ठा ufs_hba *hba, bool set, क्रमागत flag_idn idn)
अणु
	u8 index;
	क्रमागत query_opcode opcode = set ? UPIU_QUERY_OPCODE_SET_FLAG :
				   UPIU_QUERY_OPCODE_CLEAR_FLAG;

	index = ufshcd_wb_get_query_index(hba);
	वापस ufshcd_query_flag_retry(hba, opcode, idn, index, शून्य);
पूर्ण

पूर्णांक ufshcd_wb_toggle(काष्ठा ufs_hba *hba, bool enable)
अणु
	पूर्णांक ret;

	अगर (!ufshcd_is_wb_allowed(hba))
		वापस 0;

	अगर (!(enable ^ hba->dev_info.wb_enabled))
		वापस 0;

	ret = __ufshcd_wb_toggle(hba, enable, QUERY_FLAG_IDN_WB_EN);
	अगर (ret) अणु
		dev_err(hba->dev, "%s Write Booster %s failed %d\n",
			__func__, enable ? "enable" : "disable", ret);
		वापस ret;
	पूर्ण

	hba->dev_info.wb_enabled = enable;
	dev_info(hba->dev, "%s Write Booster %s\n",
			__func__, enable ? "enabled" : "disabled");

	वापस ret;
पूर्ण

अटल व्योम ufshcd_wb_toggle_flush_during_h8(काष्ठा ufs_hba *hba, bool set)
अणु
	पूर्णांक ret;

	ret = __ufshcd_wb_toggle(hba, set,
			QUERY_FLAG_IDN_WB_BUFF_FLUSH_DURING_HIBERN8);
	अगर (ret) अणु
		dev_err(hba->dev, "%s: WB-Buf Flush during H8 %s failed: %d\n",
			__func__, set ? "enable" : "disable", ret);
		वापस;
	पूर्ण
	dev_dbg(hba->dev, "%s WB-Buf Flush during H8 %s\n",
			__func__, set ? "enabled" : "disabled");
पूर्ण

अटल अंतरभूत व्योम ufshcd_wb_toggle_flush(काष्ठा ufs_hba *hba, bool enable)
अणु
	पूर्णांक ret;

	अगर (!ufshcd_is_wb_allowed(hba) ||
	    hba->dev_info.wb_buf_flush_enabled == enable)
		वापस;

	ret = __ufshcd_wb_toggle(hba, enable, QUERY_FLAG_IDN_WB_BUFF_FLUSH_EN);
	अगर (ret) अणु
		dev_err(hba->dev, "%s WB-Buf Flush %s failed %d\n", __func__,
			enable ? "enable" : "disable", ret);
		वापस;
	पूर्ण

	hba->dev_info.wb_buf_flush_enabled = enable;

	dev_dbg(hba->dev, "%s WB-Buf Flush %s\n",
			__func__, enable ? "enabled" : "disabled");
पूर्ण

अटल bool ufshcd_wb_presrv_usrspc_keep_vcc_on(काष्ठा ufs_hba *hba,
						u32 avail_buf)
अणु
	u32 cur_buf;
	पूर्णांक ret;
	u8 index;

	index = ufshcd_wb_get_query_index(hba);
	ret = ufshcd_query_attr_retry(hba, UPIU_QUERY_OPCODE_READ_ATTR,
					      QUERY_ATTR_IDN_CURR_WB_BUFF_SIZE,
					      index, 0, &cur_buf);
	अगर (ret) अणु
		dev_err(hba->dev, "%s dCurWriteBoosterBufferSize read failed %d\n",
			__func__, ret);
		वापस false;
	पूर्ण

	अगर (!cur_buf) अणु
		dev_info(hba->dev, "dCurWBBuf: %d WB disabled until free-space is available\n",
			 cur_buf);
		वापस false;
	पूर्ण
	/* Let it जारी to flush when available buffer exceeds threshold */
	अगर (avail_buf < hba->vps->wb_flush_threshold)
		वापस true;

	वापस false;
पूर्ण

अटल bool ufshcd_wb_need_flush(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret;
	u32 avail_buf;
	u8 index;

	अगर (!ufshcd_is_wb_allowed(hba))
		वापस false;
	/*
	 * The ufs device needs the vcc to be ON to flush.
	 * With user-space reduction enabled, it's enough to enable flush
	 * by checking only the available buffer. The threshold
	 * defined here is > 90% full.
	 * With user-space preserved enabled, the current-buffer
	 * should be checked too because the wb buffer size can reduce
	 * when disk tends to be full. This info is provided by current
	 * buffer (dCurrentWriteBoosterBufferSize). There's no poपूर्णांक in
	 * keeping vcc on when current buffer is empty.
	 */
	index = ufshcd_wb_get_query_index(hba);
	ret = ufshcd_query_attr_retry(hba, UPIU_QUERY_OPCODE_READ_ATTR,
				      QUERY_ATTR_IDN_AVAIL_WB_BUFF_SIZE,
				      index, 0, &avail_buf);
	अगर (ret) अणु
		dev_warn(hba->dev, "%s dAvailableWriteBoosterBufferSize read failed %d\n",
			 __func__, ret);
		वापस false;
	पूर्ण

	अगर (!hba->dev_info.b_presrv_uspc_en) अणु
		अगर (avail_buf <= UFS_WB_BUF_REMAIN_PERCENT(10))
			वापस true;
		वापस false;
	पूर्ण

	वापस ufshcd_wb_presrv_usrspc_keep_vcc_on(hba, avail_buf);
पूर्ण

अटल व्योम ufshcd_rpm_dev_flush_recheck_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ufs_hba *hba = container_of(to_delayed_work(work),
					   काष्ठा ufs_hba,
					   rpm_dev_flush_recheck_work);
	/*
	 * To prevent unnecessary VCC घातer drain after device finishes
	 * WriteBooster buffer flush or Auto BKOPs, क्रमce runसमय resume
	 * after a certain delay to recheck the threshold by next runसमय
	 * suspend.
	 */
	pm_runसमय_get_sync(hba->dev);
	pm_runसमय_put_sync(hba->dev);
पूर्ण

/**
 * ufshcd_exception_event_handler - handle exceptions उठाओd by device
 * @work: poपूर्णांकer to work data
 *
 * Read bExceptionEventStatus attribute from the device and handle the
 * exception event accordingly.
 */
अटल व्योम ufshcd_exception_event_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ufs_hba *hba;
	पूर्णांक err;
	u32 status = 0;
	hba = container_of(work, काष्ठा ufs_hba, eeh_work);

	pm_runसमय_get_sync(hba->dev);
	ufshcd_scsi_block_requests(hba);
	err = ufshcd_get_ee_status(hba, &status);
	अगर (err) अणु
		dev_err(hba->dev, "%s: failed to get exception status %d\n",
				__func__, err);
		जाओ out;
	पूर्ण

	trace_ufshcd_exception_event(dev_name(hba->dev), status);

	अगर (status & hba->ee_drv_mask & MASK_EE_URGENT_BKOPS)
		ufshcd_bkops_exception_event_handler(hba);

	ufs_debugfs_exception_event(hba, status);
out:
	ufshcd_scsi_unblock_requests(hba);
	/*
	 * pm_runसमय_get_noresume is called जबतक scheduling
	 * eeh_work to aव्योम suspend racing with exception work.
	 * Hence decrement usage counter using pm_runसमय_put_noidle
	 * to allow suspend on completion of exception event handler.
	 */
	pm_runसमय_put_noidle(hba->dev);
	pm_runसमय_put(hba->dev);
	वापस;
पूर्ण

/* Complete requests that have करोor-bell cleared */
अटल व्योम ufshcd_complete_requests(काष्ठा ufs_hba *hba)
अणु
	ufshcd_transfer_req_compl(hba);
	ufshcd_पंचांगc_handler(hba);
पूर्ण

/**
 * ufshcd_quirk_dl_nac_errors - This function checks अगर error handling is
 *				to recover from the DL NAC errors or not.
 * @hba: per-adapter instance
 *
 * Returns true अगर error handling is required, false otherwise
 */
अटल bool ufshcd_quirk_dl_nac_errors(काष्ठा ufs_hba *hba)
अणु
	अचिन्हित दीर्घ flags;
	bool err_handling = true;

	spin_lock_irqsave(hba->host->host_lock, flags);
	/*
	 * UFS_DEVICE_QUIRK_RECOVERY_FROM_DL_NAC_ERRORS only workaround the
	 * device fatal error and/or DL NAC & REPLAY समयout errors.
	 */
	अगर (hba->saved_err & (CONTROLLER_FATAL_ERROR | SYSTEM_BUS_FATAL_ERROR))
		जाओ out;

	अगर ((hba->saved_err & DEVICE_FATAL_ERROR) ||
	    ((hba->saved_err & UIC_ERROR) &&
	     (hba->saved_uic_err & UFSHCD_UIC_DL_TCx_REPLAY_ERROR)))
		जाओ out;

	अगर ((hba->saved_err & UIC_ERROR) &&
	    (hba->saved_uic_err & UFSHCD_UIC_DL_NAC_RECEIVED_ERROR)) अणु
		पूर्णांक err;
		/*
		 * रुको क्रम 50ms to see अगर we can get any other errors or not.
		 */
		spin_unlock_irqrestore(hba->host->host_lock, flags);
		msleep(50);
		spin_lock_irqsave(hba->host->host_lock, flags);

		/*
		 * now check अगर we have got any other severe errors other than
		 * DL NAC error?
		 */
		अगर ((hba->saved_err & INT_FATAL_ERRORS) ||
		    ((hba->saved_err & UIC_ERROR) &&
		    (hba->saved_uic_err & ~UFSHCD_UIC_DL_NAC_RECEIVED_ERROR)))
			जाओ out;

		/*
		 * As DL NAC is the only error received so far, send out NOP
		 * command to confirm अगर link is still active or not.
		 *   - If we करोn't get any response then करो error recovery.
		 *   - If we get response then clear the DL NAC error bit.
		 */

		spin_unlock_irqrestore(hba->host->host_lock, flags);
		err = ufshcd_verअगरy_dev_init(hba);
		spin_lock_irqsave(hba->host->host_lock, flags);

		अगर (err)
			जाओ out;

		/* Link seems to be alive hence ignore the DL NAC errors */
		अगर (hba->saved_uic_err == UFSHCD_UIC_DL_NAC_RECEIVED_ERROR)
			hba->saved_err &= ~UIC_ERROR;
		/* clear NAC error */
		hba->saved_uic_err &= ~UFSHCD_UIC_DL_NAC_RECEIVED_ERROR;
		अगर (!hba->saved_uic_err)
			err_handling = false;
	पूर्ण
out:
	spin_unlock_irqrestore(hba->host->host_lock, flags);
	वापस err_handling;
पूर्ण

/* host lock must be held beक्रमe calling this func */
अटल अंतरभूत bool ufshcd_is_saved_err_fatal(काष्ठा ufs_hba *hba)
अणु
	वापस (hba->saved_uic_err & UFSHCD_UIC_DL_PA_INIT_ERROR) ||
	       (hba->saved_err & (INT_FATAL_ERRORS | UFSHCD_UIC_HIBERN8_MASK));
पूर्ण

/* host lock must be held beक्रमe calling this func */
अटल अंतरभूत व्योम ufshcd_schedule_eh_work(काष्ठा ufs_hba *hba)
अणु
	/* handle fatal errors only when link is not in error state */
	अगर (hba->ufshcd_state != UFSHCD_STATE_ERROR) अणु
		अगर (hba->क्रमce_reset || ufshcd_is_link_broken(hba) ||
		    ufshcd_is_saved_err_fatal(hba))
			hba->ufshcd_state = UFSHCD_STATE_EH_SCHEDULED_FATAL;
		अन्यथा
			hba->ufshcd_state = UFSHCD_STATE_EH_SCHEDULED_NON_FATAL;
		queue_work(hba->eh_wq, &hba->eh_work);
	पूर्ण
पूर्ण

अटल व्योम ufshcd_clk_scaling_allow(काष्ठा ufs_hba *hba, bool allow)
अणु
	करोwn_ग_लिखो(&hba->clk_scaling_lock);
	hba->clk_scaling.is_allowed = allow;
	up_ग_लिखो(&hba->clk_scaling_lock);
पूर्ण

अटल व्योम ufshcd_clk_scaling_suspend(काष्ठा ufs_hba *hba, bool suspend)
अणु
	अगर (suspend) अणु
		अगर (hba->clk_scaling.is_enabled)
			ufshcd_suspend_clkscaling(hba);
		ufshcd_clk_scaling_allow(hba, false);
	पूर्ण अन्यथा अणु
		ufshcd_clk_scaling_allow(hba, true);
		अगर (hba->clk_scaling.is_enabled)
			ufshcd_resume_clkscaling(hba);
	पूर्ण
पूर्ण

अटल व्योम ufshcd_err_handling_prepare(काष्ठा ufs_hba *hba)
अणु
	pm_runसमय_get_sync(hba->dev);
	अगर (pm_runसमय_status_suspended(hba->dev) || hba->is_sys_suspended) अणु
		क्रमागत ufs_pm_op pm_op;

		/*
		 * Don't assume anything of pm_runसमय_get_sync(), अगर
		 * resume fails, irq and घड़ीs can be OFF, and घातers
		 * can be OFF or in LPM.
		 */
		ufshcd_setup_hba_vreg(hba, true);
		ufshcd_enable_irq(hba);
		ufshcd_setup_vreg(hba, true);
		ufshcd_config_vreg_hpm(hba, hba->vreg_info.vccq);
		ufshcd_config_vreg_hpm(hba, hba->vreg_info.vccq2);
		ufshcd_hold(hba, false);
		अगर (!ufshcd_is_clkgating_allowed(hba))
			ufshcd_setup_घड़ीs(hba, true);
		ufshcd_release(hba);
		pm_op = hba->is_sys_suspended ? UFS_SYSTEM_PM : UFS_RUNTIME_PM;
		ufshcd_vops_resume(hba, pm_op);
	पूर्ण अन्यथा अणु
		ufshcd_hold(hba, false);
		अगर (ufshcd_is_clkscaling_supported(hba) &&
		    hba->clk_scaling.is_enabled)
			ufshcd_suspend_clkscaling(hba);
		ufshcd_clk_scaling_allow(hba, false);
	पूर्ण
	ufshcd_scsi_block_requests(hba);
	/* Drain ufshcd_queuecommand() */
	करोwn_ग_लिखो(&hba->clk_scaling_lock);
	up_ग_लिखो(&hba->clk_scaling_lock);
	cancel_work_sync(&hba->eeh_work);
पूर्ण

अटल व्योम ufshcd_err_handling_unprepare(काष्ठा ufs_hba *hba)
अणु
	ufshcd_scsi_unblock_requests(hba);
	ufshcd_release(hba);
	अगर (ufshcd_is_clkscaling_supported(hba))
		ufshcd_clk_scaling_suspend(hba, false);
	ufshcd_clear_ua_wluns(hba);
	pm_runसमय_put(hba->dev);
पूर्ण

अटल अंतरभूत bool ufshcd_err_handling_should_stop(काष्ठा ufs_hba *hba)
अणु
	वापस (!hba->is_घातered || hba->shutting_करोwn ||
		hba->ufshcd_state == UFSHCD_STATE_ERROR ||
		(!(hba->saved_err || hba->saved_uic_err || hba->क्रमce_reset ||
		   ufshcd_is_link_broken(hba))));
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम ufshcd_recover_pm_error(काष्ठा ufs_hba *hba)
अणु
	काष्ठा Scsi_Host *shost = hba->host;
	काष्ठा scsi_device *sdev;
	काष्ठा request_queue *q;
	पूर्णांक ret;

	hba->is_sys_suspended = false;
	/*
	 * Set RPM status of hba device to RPM_ACTIVE,
	 * this also clears its runसमय error.
	 */
	ret = pm_runसमय_set_active(hba->dev);
	/*
	 * If hba device had runसमय error, we also need to resume those
	 * scsi devices under hba in हाल any of them has failed to be
	 * resumed due to hba runसमय resume failure. This is to unblock
	 * blk_queue_enter in हाल there are bios रुकोing inside it.
	 */
	अगर (!ret) अणु
		shost_क्रम_each_device(sdev, shost) अणु
			q = sdev->request_queue;
			अगर (q->dev && (q->rpm_status == RPM_SUSPENDED ||
				       q->rpm_status == RPM_SUSPENDING))
				pm_request_resume(q->dev);
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम ufshcd_recover_pm_error(काष्ठा ufs_hba *hba)
अणु
पूर्ण
#पूर्ण_अगर

अटल bool ufshcd_is_pwr_mode_restore_needed(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_pa_layer_attr *pwr_info = &hba->pwr_info;
	u32 mode;

	ufshcd_dme_get(hba, UIC_ARG_MIB(PA_PWRMODE), &mode);

	अगर (pwr_info->pwr_rx != ((mode >> PWRMODE_RX_OFFSET) & PWRMODE_MASK))
		वापस true;

	अगर (pwr_info->pwr_tx != (mode & PWRMODE_MASK))
		वापस true;

	वापस false;
पूर्ण

/**
 * ufshcd_err_handler - handle UFS errors that require s/w attention
 * @work: poपूर्णांकer to work काष्ठाure
 */
अटल व्योम ufshcd_err_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ufs_hba *hba;
	अचिन्हित दीर्घ flags;
	bool err_xfer = false;
	bool err_पंचांग = false;
	पूर्णांक err = 0, pmc_err;
	पूर्णांक tag;
	bool needs_reset = false, needs_restore = false;

	hba = container_of(work, काष्ठा ufs_hba, eh_work);

	करोwn(&hba->host_sem);
	spin_lock_irqsave(hba->host->host_lock, flags);
	अगर (ufshcd_err_handling_should_stop(hba)) अणु
		अगर (hba->ufshcd_state != UFSHCD_STATE_ERROR)
			hba->ufshcd_state = UFSHCD_STATE_OPERATIONAL;
		spin_unlock_irqrestore(hba->host->host_lock, flags);
		up(&hba->host_sem);
		वापस;
	पूर्ण
	ufshcd_set_eh_in_progress(hba);
	spin_unlock_irqrestore(hba->host->host_lock, flags);
	ufshcd_err_handling_prepare(hba);
	spin_lock_irqsave(hba->host->host_lock, flags);
	अगर (hba->ufshcd_state != UFSHCD_STATE_ERROR)
		hba->ufshcd_state = UFSHCD_STATE_RESET;

	/* Complete requests that have करोor-bell cleared by h/w */
	ufshcd_complete_requests(hba);

	/*
	 * A full reset and restore might have happened after preparation
	 * is finished, द्विगुन check whether we should stop.
	 */
	अगर (ufshcd_err_handling_should_stop(hba))
		जाओ skip_err_handling;

	अगर (hba->dev_quirks & UFS_DEVICE_QUIRK_RECOVERY_FROM_DL_NAC_ERRORS) अणु
		bool ret;

		spin_unlock_irqrestore(hba->host->host_lock, flags);
		/* release the lock as ufshcd_quirk_dl_nac_errors() may sleep */
		ret = ufshcd_quirk_dl_nac_errors(hba);
		spin_lock_irqsave(hba->host->host_lock, flags);
		अगर (!ret && ufshcd_err_handling_should_stop(hba))
			जाओ skip_err_handling;
	पूर्ण

	अगर ((hba->saved_err & (INT_FATAL_ERRORS | UFSHCD_UIC_HIBERN8_MASK)) ||
	    (hba->saved_uic_err &&
	     (hba->saved_uic_err != UFSHCD_UIC_PA_GENERIC_ERROR))) अणु
		bool pr_prdt = !!(hba->saved_err & SYSTEM_BUS_FATAL_ERROR);

		spin_unlock_irqrestore(hba->host->host_lock, flags);
		ufshcd_prपूर्णांक_host_state(hba);
		ufshcd_prपूर्णांक_pwr_info(hba);
		ufshcd_prपूर्णांक_evt_hist(hba);
		ufshcd_prपूर्णांक_पंचांगrs(hba, hba->outstanding_tasks);
		ufshcd_prपूर्णांक_trs(hba, hba->outstanding_reqs, pr_prdt);
		spin_lock_irqsave(hba->host->host_lock, flags);
	पूर्ण

	/*
	 * अगर host reset is required then skip clearing the pending
	 * transfers क्रमcefully because they will get cleared during
	 * host reset and restore
	 */
	अगर (hba->क्रमce_reset || ufshcd_is_link_broken(hba) ||
	    ufshcd_is_saved_err_fatal(hba) ||
	    ((hba->saved_err & UIC_ERROR) &&
	     (hba->saved_uic_err & (UFSHCD_UIC_DL_NAC_RECEIVED_ERROR |
				    UFSHCD_UIC_DL_TCx_REPLAY_ERROR)))) अणु
		needs_reset = true;
		जाओ करो_reset;
	पूर्ण

	/*
	 * If LINERESET was caught, UFS might have been put to PWM mode,
	 * check अगर घातer mode restore is needed.
	 */
	अगर (hba->saved_uic_err & UFSHCD_UIC_PA_GENERIC_ERROR) अणु
		hba->saved_uic_err &= ~UFSHCD_UIC_PA_GENERIC_ERROR;
		अगर (!hba->saved_uic_err)
			hba->saved_err &= ~UIC_ERROR;
		spin_unlock_irqrestore(hba->host->host_lock, flags);
		अगर (ufshcd_is_pwr_mode_restore_needed(hba))
			needs_restore = true;
		spin_lock_irqsave(hba->host->host_lock, flags);
		अगर (!hba->saved_err && !needs_restore)
			जाओ skip_err_handling;
	पूर्ण

	hba->silence_err_logs = true;
	/* release lock as clear command might sleep */
	spin_unlock_irqrestore(hba->host->host_lock, flags);
	/* Clear pending transfer requests */
	क्रम_each_set_bit(tag, &hba->outstanding_reqs, hba->nutrs) अणु
		अगर (ufshcd_try_to_पात_task(hba, tag)) अणु
			err_xfer = true;
			जाओ lock_skip_pending_xfer_clear;
		पूर्ण
	पूर्ण

	/* Clear pending task management requests */
	क्रम_each_set_bit(tag, &hba->outstanding_tasks, hba->nuपंचांगrs) अणु
		अगर (ufshcd_clear_पंचांग_cmd(hba, tag)) अणु
			err_पंचांग = true;
			जाओ lock_skip_pending_xfer_clear;
		पूर्ण
	पूर्ण

lock_skip_pending_xfer_clear:
	spin_lock_irqsave(hba->host->host_lock, flags);

	/* Complete the requests that are cleared by s/w */
	ufshcd_complete_requests(hba);
	hba->silence_err_logs = false;

	अगर (err_xfer || err_पंचांग) अणु
		needs_reset = true;
		जाओ करो_reset;
	पूर्ण

	/*
	 * After all reqs and tasks are cleared from करोorbell,
	 * now it is safe to retore घातer mode.
	 */
	अगर (needs_restore) अणु
		spin_unlock_irqrestore(hba->host->host_lock, flags);
		/*
		 * Hold the scaling lock just in हाल dev cmds
		 * are sent via bsg and/or sysfs.
		 */
		करोwn_ग_लिखो(&hba->clk_scaling_lock);
		hba->क्रमce_pmc = true;
		pmc_err = ufshcd_config_pwr_mode(hba, &(hba->pwr_info));
		अगर (pmc_err) अणु
			needs_reset = true;
			dev_err(hba->dev, "%s: Failed to restore power mode, err = %d\n",
					__func__, pmc_err);
		पूर्ण
		hba->क्रमce_pmc = false;
		ufshcd_prपूर्णांक_pwr_info(hba);
		up_ग_लिखो(&hba->clk_scaling_lock);
		spin_lock_irqsave(hba->host->host_lock, flags);
	पूर्ण

करो_reset:
	/* Fatal errors need reset */
	अगर (needs_reset) अणु
		अचिन्हित दीर्घ max_करोorbells = (1UL << hba->nutrs) - 1;

		/*
		 * ufshcd_reset_and_restore() करोes the link reinitialization
		 * which will need atleast one empty करोorbell slot to send the
		 * device management commands (NOP and query commands).
		 * If there is no slot empty at this moment then मुक्त up last
		 * slot क्रमcefully.
		 */
		अगर (hba->outstanding_reqs == max_करोorbells)
			__ufshcd_transfer_req_compl(hba,
						    (1UL << (hba->nutrs - 1)));

		hba->क्रमce_reset = false;
		spin_unlock_irqrestore(hba->host->host_lock, flags);
		err = ufshcd_reset_and_restore(hba);
		अगर (err)
			dev_err(hba->dev, "%s: reset and restore failed with err %d\n",
					__func__, err);
		अन्यथा
			ufshcd_recover_pm_error(hba);
		spin_lock_irqsave(hba->host->host_lock, flags);
	पूर्ण

skip_err_handling:
	अगर (!needs_reset) अणु
		अगर (hba->ufshcd_state == UFSHCD_STATE_RESET)
			hba->ufshcd_state = UFSHCD_STATE_OPERATIONAL;
		अगर (hba->saved_err || hba->saved_uic_err)
			dev_err_ratelimited(hba->dev, "%s: exit: saved_err 0x%x saved_uic_err 0x%x",
			    __func__, hba->saved_err, hba->saved_uic_err);
	पूर्ण
	ufshcd_clear_eh_in_progress(hba);
	spin_unlock_irqrestore(hba->host->host_lock, flags);
	ufshcd_err_handling_unprepare(hba);
	up(&hba->host_sem);
पूर्ण

/**
 * ufshcd_update_uic_error - check and set fatal UIC error flags.
 * @hba: per-adapter instance
 *
 * Returns
 *  IRQ_HANDLED - If पूर्णांकerrupt is valid
 *  IRQ_NONE    - If invalid पूर्णांकerrupt
 */
अटल irqवापस_t ufshcd_update_uic_error(काष्ठा ufs_hba *hba)
अणु
	u32 reg;
	irqवापस_t retval = IRQ_NONE;

	/* PHY layer error */
	reg = ufshcd_पढ़ोl(hba, REG_UIC_ERROR_CODE_PHY_ADAPTER_LAYER);
	अगर ((reg & UIC_PHY_ADAPTER_LAYER_ERROR) &&
	    (reg & UIC_PHY_ADAPTER_LAYER_ERROR_CODE_MASK)) अणु
		ufshcd_update_evt_hist(hba, UFS_EVT_PA_ERR, reg);
		/*
		 * To know whether this error is fatal or not, DB समयout
		 * must be checked but this error is handled separately.
		 */
		अगर (reg & UIC_PHY_ADAPTER_LAYER_LANE_ERR_MASK)
			dev_dbg(hba->dev, "%s: UIC Lane error reported\n",
					__func__);

		/* Got a LINERESET indication. */
		अगर (reg & UIC_PHY_ADAPTER_LAYER_GENERIC_ERROR) अणु
			काष्ठा uic_command *cmd = शून्य;

			hba->uic_error |= UFSHCD_UIC_PA_GENERIC_ERROR;
			अगर (hba->uic_async_करोne && hba->active_uic_cmd)
				cmd = hba->active_uic_cmd;
			/*
			 * Ignore the LINERESET during घातer mode change
			 * operation via DME_SET command.
			 */
			अगर (cmd && (cmd->command == UIC_CMD_DME_SET))
				hba->uic_error &= ~UFSHCD_UIC_PA_GENERIC_ERROR;
		पूर्ण
		retval |= IRQ_HANDLED;
	पूर्ण

	/* PA_INIT_ERROR is fatal and needs UIC reset */
	reg = ufshcd_पढ़ोl(hba, REG_UIC_ERROR_CODE_DATA_LINK_LAYER);
	अगर ((reg & UIC_DATA_LINK_LAYER_ERROR) &&
	    (reg & UIC_DATA_LINK_LAYER_ERROR_CODE_MASK)) अणु
		ufshcd_update_evt_hist(hba, UFS_EVT_DL_ERR, reg);

		अगर (reg & UIC_DATA_LINK_LAYER_ERROR_PA_INIT)
			hba->uic_error |= UFSHCD_UIC_DL_PA_INIT_ERROR;
		अन्यथा अगर (hba->dev_quirks &
				UFS_DEVICE_QUIRK_RECOVERY_FROM_DL_NAC_ERRORS) अणु
			अगर (reg & UIC_DATA_LINK_LAYER_ERROR_NAC_RECEIVED)
				hba->uic_error |=
					UFSHCD_UIC_DL_NAC_RECEIVED_ERROR;
			अन्यथा अगर (reg & UIC_DATA_LINK_LAYER_ERROR_TCx_REPLAY_TIMEOUT)
				hba->uic_error |= UFSHCD_UIC_DL_TCx_REPLAY_ERROR;
		पूर्ण
		retval |= IRQ_HANDLED;
	पूर्ण

	/* UIC NL/TL/DME errors needs software retry */
	reg = ufshcd_पढ़ोl(hba, REG_UIC_ERROR_CODE_NETWORK_LAYER);
	अगर ((reg & UIC_NETWORK_LAYER_ERROR) &&
	    (reg & UIC_NETWORK_LAYER_ERROR_CODE_MASK)) अणु
		ufshcd_update_evt_hist(hba, UFS_EVT_NL_ERR, reg);
		hba->uic_error |= UFSHCD_UIC_NL_ERROR;
		retval |= IRQ_HANDLED;
	पूर्ण

	reg = ufshcd_पढ़ोl(hba, REG_UIC_ERROR_CODE_TRANSPORT_LAYER);
	अगर ((reg & UIC_TRANSPORT_LAYER_ERROR) &&
	    (reg & UIC_TRANSPORT_LAYER_ERROR_CODE_MASK)) अणु
		ufshcd_update_evt_hist(hba, UFS_EVT_TL_ERR, reg);
		hba->uic_error |= UFSHCD_UIC_TL_ERROR;
		retval |= IRQ_HANDLED;
	पूर्ण

	reg = ufshcd_पढ़ोl(hba, REG_UIC_ERROR_CODE_DME);
	अगर ((reg & UIC_DME_ERROR) &&
	    (reg & UIC_DME_ERROR_CODE_MASK)) अणु
		ufshcd_update_evt_hist(hba, UFS_EVT_DME_ERR, reg);
		hba->uic_error |= UFSHCD_UIC_DME_ERROR;
		retval |= IRQ_HANDLED;
	पूर्ण

	dev_dbg(hba->dev, "%s: UIC error flags = 0x%08x\n",
			__func__, hba->uic_error);
	वापस retval;
पूर्ण

अटल bool ufshcd_is_स्वतः_hibern8_error(काष्ठा ufs_hba *hba,
					 u32 पूर्णांकr_mask)
अणु
	अगर (!ufshcd_is_स्वतः_hibern8_supported(hba) ||
	    !ufshcd_is_स्वतः_hibern8_enabled(hba))
		वापस false;

	अगर (!(पूर्णांकr_mask & UFSHCD_UIC_HIBERN8_MASK))
		वापस false;

	अगर (hba->active_uic_cmd &&
	    (hba->active_uic_cmd->command == UIC_CMD_DME_HIBER_ENTER ||
	    hba->active_uic_cmd->command == UIC_CMD_DME_HIBER_EXIT))
		वापस false;

	वापस true;
पूर्ण

/**
 * ufshcd_check_errors - Check क्रम errors that need s/w attention
 * @hba: per-adapter instance
 *
 * Returns
 *  IRQ_HANDLED - If पूर्णांकerrupt is valid
 *  IRQ_NONE    - If invalid पूर्णांकerrupt
 */
अटल irqवापस_t ufshcd_check_errors(काष्ठा ufs_hba *hba)
अणु
	bool queue_eh_work = false;
	irqवापस_t retval = IRQ_NONE;

	अगर (hba->errors & INT_FATAL_ERRORS) अणु
		ufshcd_update_evt_hist(hba, UFS_EVT_FATAL_ERR,
				       hba->errors);
		queue_eh_work = true;
	पूर्ण

	अगर (hba->errors & UIC_ERROR) अणु
		hba->uic_error = 0;
		retval = ufshcd_update_uic_error(hba);
		अगर (hba->uic_error)
			queue_eh_work = true;
	पूर्ण

	अगर (hba->errors & UFSHCD_UIC_HIBERN8_MASK) अणु
		dev_err(hba->dev,
			"%s: Auto Hibern8 %s failed - status: 0x%08x, upmcrs: 0x%08x\n",
			__func__, (hba->errors & UIC_HIBERNATE_ENTER) ?
			"Enter" : "Exit",
			hba->errors, ufshcd_get_upmcrs(hba));
		ufshcd_update_evt_hist(hba, UFS_EVT_AUTO_HIBERN8_ERR,
				       hba->errors);
		ufshcd_set_link_broken(hba);
		queue_eh_work = true;
	पूर्ण

	अगर (queue_eh_work) अणु
		/*
		 * update the transfer error masks to sticky bits, let's करो this
		 * irrespective of current ufshcd_state.
		 */
		hba->saved_err |= hba->errors;
		hba->saved_uic_err |= hba->uic_error;

		/* dump controller state beक्रमe resetting */
		अगर ((hba->saved_err &
		     (INT_FATAL_ERRORS | UFSHCD_UIC_HIBERN8_MASK)) ||
		    (hba->saved_uic_err &&
		     (hba->saved_uic_err != UFSHCD_UIC_PA_GENERIC_ERROR))) अणु
			dev_err(hba->dev, "%s: saved_err 0x%x saved_uic_err 0x%x\n",
					__func__, hba->saved_err,
					hba->saved_uic_err);
			ufshcd_dump_regs(hba, 0, UFSHCI_REG_SPACE_SIZE,
					 "host_regs: ");
			ufshcd_prपूर्णांक_pwr_info(hba);
		पूर्ण
		ufshcd_schedule_eh_work(hba);
		retval |= IRQ_HANDLED;
	पूर्ण
	/*
	 * अगर (!queue_eh_work) -
	 * Other errors are either non-fatal where host recovers
	 * itself without s/w पूर्णांकervention or errors that will be
	 * handled by the SCSI core layer.
	 */
	वापस retval;
पूर्ण

काष्ठा cपंचांग_info अणु
	काष्ठा ufs_hba	*hba;
	अचिन्हित दीर्घ	pending;
	अचिन्हित पूर्णांक	ncpl;
पूर्ण;

अटल bool ufshcd_compl_पंचांग(काष्ठा request *req, व्योम *priv, bool reserved)
अणु
	काष्ठा cपंचांग_info *स्थिर ci = priv;
	काष्ठा completion *c;

	WARN_ON_ONCE(reserved);
	अगर (test_bit(req->tag, &ci->pending))
		वापस true;
	ci->ncpl++;
	c = req->end_io_data;
	अगर (c)
		complete(c);
	वापस true;
पूर्ण

/**
 * ufshcd_पंचांगc_handler - handle task management function completion
 * @hba: per adapter instance
 *
 * Returns
 *  IRQ_HANDLED - If पूर्णांकerrupt is valid
 *  IRQ_NONE    - If invalid पूर्णांकerrupt
 */
अटल irqवापस_t ufshcd_पंचांगc_handler(काष्ठा ufs_hba *hba)
अणु
	काष्ठा request_queue *q = hba->पंचांगf_queue;
	काष्ठा cपंचांग_info ci = अणु
		.hba	 = hba,
		.pending = ufshcd_पढ़ोl(hba, REG_UTP_TASK_REQ_DOOR_BELL),
	पूर्ण;

	blk_mq_tagset_busy_iter(q->tag_set, ufshcd_compl_पंचांग, &ci);
	वापस ci.ncpl ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

/**
 * ufshcd_sl_पूर्णांकr - Interrupt service routine
 * @hba: per adapter instance
 * @पूर्णांकr_status: contains पूर्णांकerrupts generated by the controller
 *
 * Returns
 *  IRQ_HANDLED - If पूर्णांकerrupt is valid
 *  IRQ_NONE    - If invalid पूर्णांकerrupt
 */
अटल irqवापस_t ufshcd_sl_पूर्णांकr(काष्ठा ufs_hba *hba, u32 पूर्णांकr_status)
अणु
	irqवापस_t retval = IRQ_NONE;

	hba->errors = UFSHCD_ERROR_MASK & पूर्णांकr_status;

	अगर (ufshcd_is_स्वतः_hibern8_error(hba, पूर्णांकr_status))
		hba->errors |= (UFSHCD_UIC_HIBERN8_MASK & पूर्णांकr_status);

	अगर (hba->errors)
		retval |= ufshcd_check_errors(hba);

	अगर (पूर्णांकr_status & UFSHCD_UIC_MASK)
		retval |= ufshcd_uic_cmd_compl(hba, पूर्णांकr_status);

	अगर (पूर्णांकr_status & UTP_TASK_REQ_COMPL)
		retval |= ufshcd_पंचांगc_handler(hba);

	अगर (पूर्णांकr_status & UTP_TRANSFER_REQ_COMPL)
		retval |= ufshcd_transfer_req_compl(hba);

	वापस retval;
पूर्ण

/**
 * ufshcd_पूर्णांकr - Main पूर्णांकerrupt service routine
 * @irq: irq number
 * @__hba: poपूर्णांकer to adapter instance
 *
 * Returns
 *  IRQ_HANDLED - If पूर्णांकerrupt is valid
 *  IRQ_NONE    - If invalid पूर्णांकerrupt
 */
अटल irqवापस_t ufshcd_पूर्णांकr(पूर्णांक irq, व्योम *__hba)
अणु
	u32 पूर्णांकr_status, enabled_पूर्णांकr_status = 0;
	irqवापस_t retval = IRQ_NONE;
	काष्ठा ufs_hba *hba = __hba;
	पूर्णांक retries = hba->nutrs;

	spin_lock(hba->host->host_lock);
	पूर्णांकr_status = ufshcd_पढ़ोl(hba, REG_INTERRUPT_STATUS);
	hba->ufs_stats.last_पूर्णांकr_status = पूर्णांकr_status;
	hba->ufs_stats.last_पूर्णांकr_ts = kसमय_get();

	/*
	 * There could be max of hba->nutrs reqs in flight and in worst हाल
	 * अगर the reqs get finished 1 by 1 after the पूर्णांकerrupt status is
	 * पढ़ो, make sure we handle them by checking the पूर्णांकerrupt status
	 * again in a loop until we process all of the reqs beक्रमe वापसing.
	 */
	जबतक (पूर्णांकr_status && retries--) अणु
		enabled_पूर्णांकr_status =
			पूर्णांकr_status & ufshcd_पढ़ोl(hba, REG_INTERRUPT_ENABLE);
		ufshcd_ग_लिखोl(hba, पूर्णांकr_status, REG_INTERRUPT_STATUS);
		अगर (enabled_पूर्णांकr_status)
			retval |= ufshcd_sl_पूर्णांकr(hba, enabled_पूर्णांकr_status);

		पूर्णांकr_status = ufshcd_पढ़ोl(hba, REG_INTERRUPT_STATUS);
	पूर्ण

	अगर (enabled_पूर्णांकr_status && retval == IRQ_NONE &&
				!ufshcd_eh_in_progress(hba)) अणु
		dev_err(hba->dev, "%s: Unhandled interrupt 0x%08x (0x%08x, 0x%08x)\n",
					__func__,
					पूर्णांकr_status,
					hba->ufs_stats.last_पूर्णांकr_status,
					enabled_पूर्णांकr_status);
		ufshcd_dump_regs(hba, 0, UFSHCI_REG_SPACE_SIZE, "host_regs: ");
	पूर्ण

	spin_unlock(hba->host->host_lock);
	वापस retval;
पूर्ण

अटल पूर्णांक ufshcd_clear_पंचांग_cmd(काष्ठा ufs_hba *hba, पूर्णांक tag)
अणु
	पूर्णांक err = 0;
	u32 mask = 1 << tag;
	अचिन्हित दीर्घ flags;

	अगर (!test_bit(tag, &hba->outstanding_tasks))
		जाओ out;

	spin_lock_irqsave(hba->host->host_lock, flags);
	ufshcd_uपंचांगrl_clear(hba, tag);
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	/* poll क्रम max. 1 sec to clear करोor bell रेजिस्टर by h/w */
	err = ufshcd_रुको_क्रम_रेजिस्टर(hba,
			REG_UTP_TASK_REQ_DOOR_BELL,
			mask, 0, 1000, 1000);
out:
	वापस err;
पूर्ण

अटल पूर्णांक __ufshcd_issue_पंचांग_cmd(काष्ठा ufs_hba *hba,
		काष्ठा utp_task_req_desc *treq, u8 पंचांग_function)
अणु
	काष्ठा request_queue *q = hba->पंचांगf_queue;
	काष्ठा Scsi_Host *host = hba->host;
	DECLARE_COMPLETION_ONSTACK(रुको);
	काष्ठा request *req;
	अचिन्हित दीर्घ flags;
	पूर्णांक task_tag, err;

	/*
	 * blk_get_request() is used here only to get a मुक्त tag.
	 */
	req = blk_get_request(q, REQ_OP_DRV_OUT, 0);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	req->end_io_data = &रुको;
	ufshcd_hold(hba, false);

	spin_lock_irqsave(host->host_lock, flags);
	blk_mq_start_request(req);

	task_tag = req->tag;
	treq->upiu_req.req_header.dword_0 |= cpu_to_be32(task_tag);

	स_नकल(hba->uपंचांगrdl_base_addr + task_tag, treq, माप(*treq));
	ufshcd_vops_setup_task_mgmt(hba, task_tag, पंचांग_function);

	/* send command to the controller */
	__set_bit(task_tag, &hba->outstanding_tasks);

	/* Make sure descriptors are पढ़ोy beक्रमe ringing the task करोorbell */
	wmb();

	ufshcd_ग_लिखोl(hba, 1 << task_tag, REG_UTP_TASK_REQ_DOOR_BELL);
	/* Make sure that करोorbell is committed immediately */
	wmb();

	spin_unlock_irqrestore(host->host_lock, flags);

	ufshcd_add_पंचांग_upiu_trace(hba, task_tag, UFS_TM_SEND);

	/* रुको until the task management command is completed */
	err = रुको_क्रम_completion_io_समयout(&रुको,
			msecs_to_jअगरfies(TM_CMD_TIMEOUT));
	अगर (!err) अणु
		/*
		 * Make sure that ufshcd_compl_पंचांग() करोes not trigger a
		 * use-after-मुक्त.
		 */
		req->end_io_data = शून्य;
		ufshcd_add_पंचांग_upiu_trace(hba, task_tag, UFS_TM_ERR);
		dev_err(hba->dev, "%s: task management cmd 0x%.2x timed-out\n",
				__func__, पंचांग_function);
		अगर (ufshcd_clear_पंचांग_cmd(hba, task_tag))
			dev_WARN(hba->dev, "%s: unable to clear tm cmd (slot %d) after timeout\n",
					__func__, task_tag);
		err = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		err = 0;
		स_नकल(treq, hba->uपंचांगrdl_base_addr + task_tag, माप(*treq));

		ufshcd_add_पंचांग_upiu_trace(hba, task_tag, UFS_TM_COMP);
	पूर्ण

	spin_lock_irqsave(hba->host->host_lock, flags);
	__clear_bit(task_tag, &hba->outstanding_tasks);
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	ufshcd_release(hba);
	blk_put_request(req);

	वापस err;
पूर्ण

/**
 * ufshcd_issue_पंचांग_cmd - issues task management commands to controller
 * @hba: per adapter instance
 * @lun_id: LUN ID to which TM command is sent
 * @task_id: task ID to which the TM command is applicable
 * @पंचांग_function: task management function opcode
 * @पंचांग_response: task management service response वापस value
 *
 * Returns non-zero value on error, zero on success.
 */
अटल पूर्णांक ufshcd_issue_पंचांग_cmd(काष्ठा ufs_hba *hba, पूर्णांक lun_id, पूर्णांक task_id,
		u8 पंचांग_function, u8 *पंचांग_response)
अणु
	काष्ठा utp_task_req_desc treq = अणु अणु 0 पूर्ण, पूर्ण;
	पूर्णांक ocs_value, err;

	/* Configure task request descriptor */
	treq.header.dword_0 = cpu_to_le32(UTP_REQ_DESC_INT_CMD);
	treq.header.dword_2 = cpu_to_le32(OCS_INVALID_COMMAND_STATUS);

	/* Configure task request UPIU */
	treq.upiu_req.req_header.dword_0 = cpu_to_be32(lun_id << 8) |
				  cpu_to_be32(UPIU_TRANSACTION_TASK_REQ << 24);
	treq.upiu_req.req_header.dword_1 = cpu_to_be32(पंचांग_function << 16);

	/*
	 * The host shall provide the same value क्रम LUN field in the basic
	 * header and क्रम Input Parameter.
	 */
	treq.upiu_req.input_param1 = cpu_to_be32(lun_id);
	treq.upiu_req.input_param2 = cpu_to_be32(task_id);

	err = __ufshcd_issue_पंचांग_cmd(hba, &treq, पंचांग_function);
	अगर (err == -ETIMEDOUT)
		वापस err;

	ocs_value = le32_to_cpu(treq.header.dword_2) & MASK_OCS;
	अगर (ocs_value != OCS_SUCCESS)
		dev_err(hba->dev, "%s: failed, ocs = 0x%x\n",
				__func__, ocs_value);
	अन्यथा अगर (पंचांग_response)
		*पंचांग_response = be32_to_cpu(treq.upiu_rsp.output_param1) &
				MASK_TM_SERVICE_RESP;
	वापस err;
पूर्ण

/**
 * ufshcd_issue_devman_upiu_cmd - API क्रम sending "utrd" type requests
 * @hba:	per-adapter instance
 * @req_upiu:	upiu request
 * @rsp_upiu:	upiu reply
 * @desc_buff:	poपूर्णांकer to descriptor buffer, शून्य अगर NA
 * @buff_len:	descriptor size, 0 अगर NA
 * @cmd_type:	specअगरies the type (NOP, Query...)
 * @desc_op:	descriptor operation
 *
 * Those type of requests uses UTP Transfer Request Descriptor - utrd.
 * Thereक्रमe, it "rides" the device management infraकाष्ठाure: uses its tag and
 * tasks work queues.
 *
 * Since there is only one available tag क्रम device management commands,
 * the caller is expected to hold the hba->dev_cmd.lock mutex.
 */
अटल पूर्णांक ufshcd_issue_devman_upiu_cmd(काष्ठा ufs_hba *hba,
					काष्ठा utp_upiu_req *req_upiu,
					काष्ठा utp_upiu_req *rsp_upiu,
					u8 *desc_buff, पूर्णांक *buff_len,
					क्रमागत dev_cmd_type cmd_type,
					क्रमागत query_opcode desc_op)
अणु
	काष्ठा request_queue *q = hba->cmd_queue;
	काष्ठा request *req;
	काष्ठा ufshcd_lrb *lrbp;
	पूर्णांक err = 0;
	पूर्णांक tag;
	काष्ठा completion रुको;
	अचिन्हित दीर्घ flags;
	u8 upiu_flags;

	करोwn_पढ़ो(&hba->clk_scaling_lock);

	req = blk_get_request(q, REQ_OP_DRV_OUT, 0);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ out_unlock;
	पूर्ण
	tag = req->tag;
	WARN_ON_ONCE(!ufshcd_valid_tag(hba, tag));

	init_completion(&रुको);
	lrbp = &hba->lrb[tag];
	अगर (unlikely(lrbp->in_use)) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	WARN_ON(lrbp->cmd);
	lrbp->cmd = शून्य;
	lrbp->sense_bufflen = 0;
	lrbp->sense_buffer = शून्य;
	lrbp->task_tag = tag;
	lrbp->lun = 0;
	lrbp->पूर्णांकr_cmd = true;
	ufshcd_prepare_lrbp_crypto(शून्य, lrbp);
	hba->dev_cmd.type = cmd_type;

	अगर (hba->ufs_version <= ufshci_version(1, 1))
		lrbp->command_type = UTP_CMD_TYPE_DEV_MANAGE;
	अन्यथा
		lrbp->command_type = UTP_CMD_TYPE_UFS_STORAGE;

	/* update the task tag in the request upiu */
	req_upiu->header.dword_0 |= cpu_to_be32(tag);

	ufshcd_prepare_req_desc_hdr(lrbp, &upiu_flags, DMA_NONE);

	/* just copy the upiu request as it is */
	स_नकल(lrbp->ucd_req_ptr, req_upiu, माप(*lrbp->ucd_req_ptr));
	अगर (desc_buff && desc_op == UPIU_QUERY_OPCODE_WRITE_DESC) अणु
		/* The Data Segment Area is optional depending upon the query
		 * function value. क्रम WRITE DESCRIPTOR, the data segment
		 * follows right after the tsf.
		 */
		स_नकल(lrbp->ucd_req_ptr + 1, desc_buff, *buff_len);
		*buff_len = 0;
	पूर्ण

	स_रखो(lrbp->ucd_rsp_ptr, 0, माप(काष्ठा utp_upiu_rsp));

	hba->dev_cmd.complete = &रुको;

	/* Make sure descriptors are पढ़ोy beक्रमe ringing the करोorbell */
	wmb();
	spin_lock_irqsave(hba->host->host_lock, flags);
	ufshcd_send_command(hba, tag);
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	/*
	 * ignore the वापसing value here - ufshcd_check_query_response is
	 * bound to fail since dev_cmd.query and dev_cmd.type were left empty.
	 * पढ़ो the response directly ignoring all errors.
	 */
	ufshcd_रुको_क्रम_dev_cmd(hba, lrbp, QUERY_REQ_TIMEOUT);

	/* just copy the upiu response as it is */
	स_नकल(rsp_upiu, lrbp->ucd_rsp_ptr, माप(*rsp_upiu));
	अगर (desc_buff && desc_op == UPIU_QUERY_OPCODE_READ_DESC) अणु
		u8 *descp = (u8 *)lrbp->ucd_rsp_ptr + माप(*rsp_upiu);
		u16 resp_len = be32_to_cpu(lrbp->ucd_rsp_ptr->header.dword_2) &
			       MASK_QUERY_DATA_SEG_LEN;

		अगर (*buff_len >= resp_len) अणु
			स_नकल(desc_buff, descp, resp_len);
			*buff_len = resp_len;
		पूर्ण अन्यथा अणु
			dev_warn(hba->dev,
				 "%s: rsp size %d is bigger than buffer size %d",
				 __func__, resp_len, *buff_len);
			*buff_len = 0;
			err = -EINVAL;
		पूर्ण
	पूर्ण

out:
	blk_put_request(req);
out_unlock:
	up_पढ़ो(&hba->clk_scaling_lock);
	वापस err;
पूर्ण

/**
 * ufshcd_exec_raw_upiu_cmd - API function क्रम sending raw upiu commands
 * @hba:	per-adapter instance
 * @req_upiu:	upiu request
 * @rsp_upiu:	upiu reply - only 8 DW as we करो not support scsi commands
 * @msgcode:	message code, one of UPIU Transaction Codes Initiator to Target
 * @desc_buff:	poपूर्णांकer to descriptor buffer, शून्य अगर NA
 * @buff_len:	descriptor size, 0 अगर NA
 * @desc_op:	descriptor operation
 *
 * Supports UTP Transfer requests (nop and query), and UTP Task
 * Management requests.
 * It is up to the caller to fill the upiu conent properly, as it will
 * be copied without any further input validations.
 */
पूर्णांक ufshcd_exec_raw_upiu_cmd(काष्ठा ufs_hba *hba,
			     काष्ठा utp_upiu_req *req_upiu,
			     काष्ठा utp_upiu_req *rsp_upiu,
			     पूर्णांक msgcode,
			     u8 *desc_buff, पूर्णांक *buff_len,
			     क्रमागत query_opcode desc_op)
अणु
	पूर्णांक err;
	क्रमागत dev_cmd_type cmd_type = DEV_CMD_TYPE_QUERY;
	काष्ठा utp_task_req_desc treq = अणु अणु 0 पूर्ण, पूर्ण;
	पूर्णांक ocs_value;
	u8 पंचांग_f = be32_to_cpu(req_upiu->header.dword_1) >> 16 & MASK_TM_FUNC;

	चयन (msgcode) अणु
	हाल UPIU_TRANSACTION_NOP_OUT:
		cmd_type = DEV_CMD_TYPE_NOP;
		fallthrough;
	हाल UPIU_TRANSACTION_QUERY_REQ:
		ufshcd_hold(hba, false);
		mutex_lock(&hba->dev_cmd.lock);
		err = ufshcd_issue_devman_upiu_cmd(hba, req_upiu, rsp_upiu,
						   desc_buff, buff_len,
						   cmd_type, desc_op);
		mutex_unlock(&hba->dev_cmd.lock);
		ufshcd_release(hba);

		अवरोध;
	हाल UPIU_TRANSACTION_TASK_REQ:
		treq.header.dword_0 = cpu_to_le32(UTP_REQ_DESC_INT_CMD);
		treq.header.dword_2 = cpu_to_le32(OCS_INVALID_COMMAND_STATUS);

		स_नकल(&treq.upiu_req, req_upiu, माप(*req_upiu));

		err = __ufshcd_issue_पंचांग_cmd(hba, &treq, पंचांग_f);
		अगर (err == -ETIMEDOUT)
			अवरोध;

		ocs_value = le32_to_cpu(treq.header.dword_2) & MASK_OCS;
		अगर (ocs_value != OCS_SUCCESS) अणु
			dev_err(hba->dev, "%s: failed, ocs = 0x%x\n", __func__,
				ocs_value);
			अवरोध;
		पूर्ण

		स_नकल(rsp_upiu, &treq.upiu_rsp, माप(*rsp_upiu));

		अवरोध;
	शेष:
		err = -EINVAL;

		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/**
 * ufshcd_eh_device_reset_handler - device reset handler रेजिस्टरed to
 *                                    scsi layer.
 * @cmd: SCSI command poपूर्णांकer
 *
 * Returns SUCCESS/FAILED
 */
अटल पूर्णांक ufshcd_eh_device_reset_handler(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा Scsi_Host *host;
	काष्ठा ufs_hba *hba;
	u32 pos;
	पूर्णांक err;
	u8 resp = 0xF, lun;
	अचिन्हित दीर्घ flags;

	host = cmd->device->host;
	hba = shost_priv(host);

	lun = ufshcd_scsi_to_upiu_lun(cmd->device->lun);
	err = ufshcd_issue_पंचांग_cmd(hba, lun, 0, UFS_LOGICAL_RESET, &resp);
	अगर (err || resp != UPIU_TASK_MANAGEMENT_FUNC_COMPL) अणु
		अगर (!err)
			err = resp;
		जाओ out;
	पूर्ण

	/* clear the commands that were pending क्रम corresponding LUN */
	क्रम_each_set_bit(pos, &hba->outstanding_reqs, hba->nutrs) अणु
		अगर (hba->lrb[pos].lun == lun) अणु
			err = ufshcd_clear_cmd(hba, pos);
			अगर (err)
				अवरोध;
		पूर्ण
	पूर्ण
	spin_lock_irqsave(host->host_lock, flags);
	ufshcd_transfer_req_compl(hba);
	spin_unlock_irqrestore(host->host_lock, flags);

out:
	hba->req_पात_count = 0;
	ufshcd_update_evt_hist(hba, UFS_EVT_DEV_RESET, (u32)err);
	अगर (!err) अणु
		err = SUCCESS;
	पूर्ण अन्यथा अणु
		dev_err(hba->dev, "%s: failed with err %d\n", __func__, err);
		err = FAILED;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम ufshcd_set_req_पात_skip(काष्ठा ufs_hba *hba, अचिन्हित दीर्घ biपंचांगap)
अणु
	काष्ठा ufshcd_lrb *lrbp;
	पूर्णांक tag;

	क्रम_each_set_bit(tag, &biपंचांगap, hba->nutrs) अणु
		lrbp = &hba->lrb[tag];
		lrbp->req_पात_skip = true;
	पूर्ण
पूर्ण

/**
 * ufshcd_try_to_पात_task - पात a specअगरic task
 * @hba: Poपूर्णांकer to adapter instance
 * @tag: Task tag/index to be पातed
 *
 * Abort the pending command in device by sending UFS_ABORT_TASK task management
 * command, and in host controller by clearing the करोor-bell रेजिस्टर. There can
 * be race between controller sending the command to the device जबतक पात is
 * issued. To aव्योम that, first issue UFS_QUERY_TASK to check अगर the command is
 * really issued and then try to पात it.
 *
 * Returns zero on success, non-zero on failure
 */
अटल पूर्णांक ufshcd_try_to_पात_task(काष्ठा ufs_hba *hba, पूर्णांक tag)
अणु
	काष्ठा ufshcd_lrb *lrbp = &hba->lrb[tag];
	पूर्णांक err = 0;
	पूर्णांक poll_cnt;
	u8 resp = 0xF;
	u32 reg;

	क्रम (poll_cnt = 100; poll_cnt; poll_cnt--) अणु
		err = ufshcd_issue_पंचांग_cmd(hba, lrbp->lun, lrbp->task_tag,
				UFS_QUERY_TASK, &resp);
		अगर (!err && resp == UPIU_TASK_MANAGEMENT_FUNC_SUCCEEDED) अणु
			/* cmd pending in the device */
			dev_err(hba->dev, "%s: cmd pending in the device. tag = %d\n",
				__func__, tag);
			अवरोध;
		पूर्ण अन्यथा अगर (!err && resp == UPIU_TASK_MANAGEMENT_FUNC_COMPL) अणु
			/*
			 * cmd not pending in the device, check अगर it is
			 * in transition.
			 */
			dev_err(hba->dev, "%s: cmd at tag %d not pending in the device.\n",
				__func__, tag);
			reg = ufshcd_पढ़ोl(hba, REG_UTP_TRANSFER_REQ_DOOR_BELL);
			अगर (reg & (1 << tag)) अणु
				/* sleep क्रम max. 200us to stabilize */
				usleep_range(100, 200);
				जारी;
			पूर्ण
			/* command completed alपढ़ोy */
			dev_err(hba->dev, "%s: cmd at tag %d successfully cleared from DB.\n",
				__func__, tag);
			जाओ out;
		पूर्ण अन्यथा अणु
			dev_err(hba->dev,
				"%s: no response from device. tag = %d, err %d\n",
				__func__, tag, err);
			अगर (!err)
				err = resp; /* service response error */
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!poll_cnt) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	err = ufshcd_issue_पंचांग_cmd(hba, lrbp->lun, lrbp->task_tag,
			UFS_ABORT_TASK, &resp);
	अगर (err || resp != UPIU_TASK_MANAGEMENT_FUNC_COMPL) अणु
		अगर (!err) अणु
			err = resp; /* service response error */
			dev_err(hba->dev, "%s: issued. tag = %d, err %d\n",
				__func__, tag, err);
		पूर्ण
		जाओ out;
	पूर्ण

	err = ufshcd_clear_cmd(hba, tag);
	अगर (err)
		dev_err(hba->dev, "%s: Failed clearing cmd at tag %d, err %d\n",
			__func__, tag, err);

out:
	वापस err;
पूर्ण

/**
 * ufshcd_पात - scsi host ढाँचा eh_पात_handler callback
 * @cmd: SCSI command poपूर्णांकer
 *
 * Returns SUCCESS/FAILED
 */
अटल पूर्णांक ufshcd_पात(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा Scsi_Host *host;
	काष्ठा ufs_hba *hba;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक tag;
	पूर्णांक err = 0;
	काष्ठा ufshcd_lrb *lrbp;
	u32 reg;

	host = cmd->device->host;
	hba = shost_priv(host);
	tag = cmd->request->tag;
	lrbp = &hba->lrb[tag];
	अगर (!ufshcd_valid_tag(hba, tag)) अणु
		dev_err(hba->dev,
			"%s: invalid command tag %d: cmd=0x%p, cmd->request=0x%p",
			__func__, tag, cmd, cmd->request);
		BUG();
	पूर्ण

	ufshcd_hold(hba, false);
	reg = ufshcd_पढ़ोl(hba, REG_UTP_TRANSFER_REQ_DOOR_BELL);
	/* If command is alपढ़ोy पातed/completed, वापस SUCCESS */
	अगर (!(test_bit(tag, &hba->outstanding_reqs))) अणु
		dev_err(hba->dev,
			"%s: cmd at tag %d already completed, outstanding=0x%lx, doorbell=0x%x\n",
			__func__, tag, hba->outstanding_reqs, reg);
		जाओ out;
	पूर्ण

	/* Prपूर्णांक Transfer Request of पातed task */
	dev_info(hba->dev, "%s: Device abort task at tag %d\n", __func__, tag);

	/*
	 * Prपूर्णांक detailed info about पातed request.
	 * As more than one request might get पातed at the same समय,
	 * prपूर्णांक full inक्रमmation only क्रम the first पातed request in order
	 * to reduce repeated prपूर्णांकouts. For other पातed requests only prपूर्णांक
	 * basic details.
	 */
	scsi_prपूर्णांक_command(cmd);
	अगर (!hba->req_पात_count) अणु
		ufshcd_update_evt_hist(hba, UFS_EVT_ABORT, tag);
		ufshcd_prपूर्णांक_evt_hist(hba);
		ufshcd_prपूर्णांक_host_state(hba);
		ufshcd_prपूर्णांक_pwr_info(hba);
		ufshcd_prपूर्णांक_trs(hba, 1 << tag, true);
	पूर्ण अन्यथा अणु
		ufshcd_prपूर्णांक_trs(hba, 1 << tag, false);
	पूर्ण
	hba->req_पात_count++;

	अगर (!(reg & (1 << tag))) अणु
		dev_err(hba->dev,
		"%s: cmd was completed, but without a notifying intr, tag = %d",
		__func__, tag);
		जाओ cleanup;
	पूर्ण

	/*
	 * Task पात to the device W-LUN is illegal. When this command
	 * will fail, due to spec violation, scsi err handling next step
	 * will be to send LU reset which, again, is a spec violation.
	 * To aव्योम these unnecessary/illegal steps, first we clean up
	 * the lrb taken by this cmd and mark the lrb as in_use, then
	 * queue the eh_work and bail.
	 */
	अगर (lrbp->lun == UFS_UPIU_UFS_DEVICE_WLUN) अणु
		ufshcd_update_evt_hist(hba, UFS_EVT_ABORT, lrbp->lun);
		spin_lock_irqsave(host->host_lock, flags);
		अगर (lrbp->cmd) अणु
			__ufshcd_transfer_req_compl(hba, (1UL << tag));
			__set_bit(tag, &hba->outstanding_reqs);
			lrbp->in_use = true;
			hba->क्रमce_reset = true;
			ufshcd_schedule_eh_work(hba);
		पूर्ण

		spin_unlock_irqrestore(host->host_lock, flags);
		जाओ out;
	पूर्ण

	/* Skip task पात in हाल previous पातs failed and report failure */
	अगर (lrbp->req_पात_skip)
		err = -EIO;
	अन्यथा
		err = ufshcd_try_to_पात_task(hba, tag);

	अगर (!err) अणु
cleanup:
		spin_lock_irqsave(host->host_lock, flags);
		__ufshcd_transfer_req_compl(hba, (1UL << tag));
		spin_unlock_irqrestore(host->host_lock, flags);
out:
		err = SUCCESS;
	पूर्ण अन्यथा अणु
		dev_err(hba->dev, "%s: failed with err %d\n", __func__, err);
		ufshcd_set_req_पात_skip(hba, hba->outstanding_reqs);
		err = FAILED;
	पूर्ण

	/*
	 * This ufshcd_release() corresponds to the original scsi cmd that got
	 * पातed here (as we won't get any IRQ क्रम it).
	 */
	ufshcd_release(hba);
	वापस err;
पूर्ण

/**
 * ufshcd_host_reset_and_restore - reset and restore host controller
 * @hba: per-adapter instance
 *
 * Note that host controller reset may issue DME_RESET to
 * local and remote (device) Uni-Pro stack and the attributes
 * are reset to शेष state.
 *
 * Returns zero on success, non-zero on failure
 */
अटल पूर्णांक ufshcd_host_reset_and_restore(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ flags;

	/*
	 * Stop the host controller and complete the requests
	 * cleared by h/w
	 */
	ufshcd_hba_stop(hba);

	spin_lock_irqsave(hba->host->host_lock, flags);
	hba->silence_err_logs = true;
	ufshcd_complete_requests(hba);
	hba->silence_err_logs = false;
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	/* scale up घड़ीs to max frequency beक्रमe full reinitialization */
	ufshcd_set_clk_freq(hba, true);

	err = ufshcd_hba_enable(hba);

	/* Establish the link again and restore the device */
	अगर (!err)
		err = ufshcd_probe_hba(hba, false);

	अगर (err)
		dev_err(hba->dev, "%s: Host init failed %d\n", __func__, err);
	ufshcd_update_evt_hist(hba, UFS_EVT_HOST_RESET, (u32)err);
	वापस err;
पूर्ण

/**
 * ufshcd_reset_and_restore - reset and re-initialize host/device
 * @hba: per-adapter instance
 *
 * Reset and recover device, host and re-establish link. This
 * is helpful to recover the communication in fatal error conditions.
 *
 * Returns zero on success, non-zero on failure
 */
अटल पूर्णांक ufshcd_reset_and_restore(काष्ठा ufs_hba *hba)
अणु
	u32 saved_err;
	u32 saved_uic_err;
	पूर्णांक err = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक retries = MAX_HOST_RESET_RETRIES;

	/*
	 * This is a fresh start, cache and clear saved error first,
	 * in हाल new error generated during reset and restore.
	 */
	spin_lock_irqsave(hba->host->host_lock, flags);
	saved_err = hba->saved_err;
	saved_uic_err = hba->saved_uic_err;
	hba->saved_err = 0;
	hba->saved_uic_err = 0;
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	करो अणु
		/* Reset the attached device */
		ufshcd_device_reset(hba);

		err = ufshcd_host_reset_and_restore(hba);
	पूर्ण जबतक (err && --retries);

	spin_lock_irqsave(hba->host->host_lock, flags);
	/*
	 * Inक्रमm scsi mid-layer that we did reset and allow to handle
	 * Unit Attention properly.
	 */
	scsi_report_bus_reset(hba->host, 0);
	अगर (err) अणु
		hba->ufshcd_state = UFSHCD_STATE_ERROR;
		hba->saved_err |= saved_err;
		hba->saved_uic_err |= saved_uic_err;
	पूर्ण
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	वापस err;
पूर्ण

/**
 * ufshcd_eh_host_reset_handler - host reset handler रेजिस्टरed to scsi layer
 * @cmd: SCSI command poपूर्णांकer
 *
 * Returns SUCCESS/FAILED
 */
अटल पूर्णांक ufshcd_eh_host_reset_handler(काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक err = SUCCESS;
	अचिन्हित दीर्घ flags;
	काष्ठा ufs_hba *hba;

	hba = shost_priv(cmd->device->host);

	spin_lock_irqsave(hba->host->host_lock, flags);
	hba->क्रमce_reset = true;
	ufshcd_schedule_eh_work(hba);
	dev_err(hba->dev, "%s: reset in progress - 1\n", __func__);
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	flush_work(&hba->eh_work);

	spin_lock_irqsave(hba->host->host_lock, flags);
	अगर (hba->ufshcd_state == UFSHCD_STATE_ERROR)
		err = FAILED;
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	वापस err;
पूर्ण

/**
 * ufshcd_get_max_icc_level - calculate the ICC level
 * @sup_curr_uA: max. current supported by the regulator
 * @start_scan: row at the desc table to start scan from
 * @buff: घातer descriptor buffer
 *
 * Returns calculated max ICC level क्रम specअगरic regulator
 */
अटल u32 ufshcd_get_max_icc_level(पूर्णांक sup_curr_uA, u32 start_scan, अक्षर *buff)
अणु
	पूर्णांक i;
	पूर्णांक curr_uA;
	u16 data;
	u16 unit;

	क्रम (i = start_scan; i >= 0; i--) अणु
		data = be16_to_cpup((__be16 *)&buff[2 * i]);
		unit = (data & ATTR_ICC_LVL_UNIT_MASK) >>
						ATTR_ICC_LVL_UNIT_OFFSET;
		curr_uA = data & ATTR_ICC_LVL_VALUE_MASK;
		चयन (unit) अणु
		हाल UFSHCD_न_अंकO_AMP:
			curr_uA = curr_uA / 1000;
			अवरोध;
		हाल UFSHCD_MILI_AMP:
			curr_uA = curr_uA * 1000;
			अवरोध;
		हाल UFSHCD_AMP:
			curr_uA = curr_uA * 1000 * 1000;
			अवरोध;
		हाल UFSHCD_MICRO_AMP:
		शेष:
			अवरोध;
		पूर्ण
		अगर (sup_curr_uA >= curr_uA)
			अवरोध;
	पूर्ण
	अगर (i < 0) अणु
		i = 0;
		pr_err("%s: Couldn't find valid icc_level = %d", __func__, i);
	पूर्ण

	वापस (u32)i;
पूर्ण

/**
 * ufshcd_find_max_sup_active_icc_level - calculate the max ICC level
 * In हाल regulators are not initialized we'll वापस 0
 * @hba: per-adapter instance
 * @desc_buf: घातer descriptor buffer to extract ICC levels from.
 * @len: length of desc_buff
 *
 * Returns calculated ICC level
 */
अटल u32 ufshcd_find_max_sup_active_icc_level(काष्ठा ufs_hba *hba,
							u8 *desc_buf, पूर्णांक len)
अणु
	u32 icc_level = 0;

	अगर (!hba->vreg_info.vcc || !hba->vreg_info.vccq ||
						!hba->vreg_info.vccq2) अणु
		dev_err(hba->dev,
			"%s: Regulator capability was not set, actvIccLevel=%d",
							__func__, icc_level);
		जाओ out;
	पूर्ण

	अगर (hba->vreg_info.vcc->max_uA)
		icc_level = ufshcd_get_max_icc_level(
				hba->vreg_info.vcc->max_uA,
				POWER_DESC_MAX_ACTV_ICC_LVLS - 1,
				&desc_buf[PWR_DESC_ACTIVE_LVLS_VCC_0]);

	अगर (hba->vreg_info.vccq->max_uA)
		icc_level = ufshcd_get_max_icc_level(
				hba->vreg_info.vccq->max_uA,
				icc_level,
				&desc_buf[PWR_DESC_ACTIVE_LVLS_VCCQ_0]);

	अगर (hba->vreg_info.vccq2->max_uA)
		icc_level = ufshcd_get_max_icc_level(
				hba->vreg_info.vccq2->max_uA,
				icc_level,
				&desc_buf[PWR_DESC_ACTIVE_LVLS_VCCQ2_0]);
out:
	वापस icc_level;
पूर्ण

अटल व्योम ufshcd_set_active_icc_lvl(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret;
	पूर्णांक buff_len = hba->desc_size[QUERY_DESC_IDN_POWER];
	u8 *desc_buf;
	u32 icc_level;

	desc_buf = kदो_स्मृति(buff_len, GFP_KERNEL);
	अगर (!desc_buf)
		वापस;

	ret = ufshcd_पढ़ो_desc_param(hba, QUERY_DESC_IDN_POWER, 0, 0,
				     desc_buf, buff_len);
	अगर (ret) अणु
		dev_err(hba->dev,
			"%s: Failed reading power descriptor.len = %d ret = %d",
			__func__, buff_len, ret);
		जाओ out;
	पूर्ण

	icc_level = ufshcd_find_max_sup_active_icc_level(hba, desc_buf,
							 buff_len);
	dev_dbg(hba->dev, "%s: setting icc_level 0x%x", __func__, icc_level);

	ret = ufshcd_query_attr_retry(hba, UPIU_QUERY_OPCODE_WRITE_ATTR,
		QUERY_ATTR_IDN_ACTIVE_ICC_LVL, 0, 0, &icc_level);

	अगर (ret)
		dev_err(hba->dev,
			"%s: Failed configuring bActiveICCLevel = %d ret = %d",
			__func__, icc_level, ret);

out:
	kमुक्त(desc_buf);
पूर्ण

अटल अंतरभूत व्योम ufshcd_blk_pm_runसमय_init(काष्ठा scsi_device *sdev)
अणु
	scsi_स्वतःpm_get_device(sdev);
	blk_pm_runसमय_init(sdev->request_queue, &sdev->sdev_gendev);
	अगर (sdev->rpm_स्वतःsuspend)
		pm_runसमय_set_स्वतःsuspend_delay(&sdev->sdev_gendev,
						 RPM_AUTOSUSPEND_DELAY_MS);
	scsi_स्वतःpm_put_device(sdev);
पूर्ण

/**
 * ufshcd_scsi_add_wlus - Adds required W-LUs
 * @hba: per-adapter instance
 *
 * UFS device specअगरication requires the UFS devices to support 4 well known
 * logical units:
 *	"REPORT_LUNS" (address: 01h)
 *	"UFS Device" (address: 50h)
 *	"RPMB" (address: 44h)
 *	"BOOT" (address: 30h)
 * UFS device's घातer management needs to be controlled by "POWER CONDITION"
 * field of SSU (START STOP UNIT) command. But this "power condition" field
 * will take effect only when its sent to "UFS device" well known logical unit
 * hence we require the scsi_device instance to represent this logical unit in
 * order क्रम the UFS host driver to send the SSU command क्रम घातer management.
 *
 * We also require the scsi_device instance क्रम "RPMB" (Replay Protected Memory
 * Block) LU so user space process can control this LU. User space may also
 * want to have access to BOOT LU.
 *
 * This function adds scsi device instances क्रम each of all well known LUs
 * (except "REPORT LUNS" LU).
 *
 * Returns zero on success (all required W-LUs are added successfully),
 * non-zero error value on failure (अगर failed to add any of the required W-LU).
 */
अटल पूर्णांक ufshcd_scsi_add_wlus(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret = 0;
	काष्ठा scsi_device *sdev_boot;

	hba->sdev_ufs_device = __scsi_add_device(hba->host, 0, 0,
		ufshcd_upiu_wlun_to_scsi_wlun(UFS_UPIU_UFS_DEVICE_WLUN), शून्य);
	अगर (IS_ERR(hba->sdev_ufs_device)) अणु
		ret = PTR_ERR(hba->sdev_ufs_device);
		hba->sdev_ufs_device = शून्य;
		जाओ out;
	पूर्ण
	ufshcd_blk_pm_runसमय_init(hba->sdev_ufs_device);
	scsi_device_put(hba->sdev_ufs_device);

	hba->sdev_rpmb = __scsi_add_device(hba->host, 0, 0,
		ufshcd_upiu_wlun_to_scsi_wlun(UFS_UPIU_RPMB_WLUN), शून्य);
	अगर (IS_ERR(hba->sdev_rpmb)) अणु
		ret = PTR_ERR(hba->sdev_rpmb);
		जाओ हटाओ_sdev_ufs_device;
	पूर्ण
	ufshcd_blk_pm_runसमय_init(hba->sdev_rpmb);
	scsi_device_put(hba->sdev_rpmb);

	sdev_boot = __scsi_add_device(hba->host, 0, 0,
		ufshcd_upiu_wlun_to_scsi_wlun(UFS_UPIU_BOOT_WLUN), शून्य);
	अगर (IS_ERR(sdev_boot)) अणु
		dev_err(hba->dev, "%s: BOOT WLUN not found\n", __func__);
	पूर्ण अन्यथा अणु
		ufshcd_blk_pm_runसमय_init(sdev_boot);
		scsi_device_put(sdev_boot);
	पूर्ण
	जाओ out;

हटाओ_sdev_ufs_device:
	scsi_हटाओ_device(hba->sdev_ufs_device);
out:
	वापस ret;
पूर्ण

अटल व्योम ufshcd_wb_probe(काष्ठा ufs_hba *hba, u8 *desc_buf)
अणु
	काष्ठा ufs_dev_info *dev_info = &hba->dev_info;
	u8 lun;
	u32 d_lu_wb_buf_alloc;
	u32 ext_ufs_feature;

	अगर (!ufshcd_is_wb_allowed(hba))
		वापस;
	/*
	 * Probe WB only क्रम UFS-2.2 and UFS-3.1 (and later) devices or
	 * UFS devices with quirk UFS_DEVICE_QUIRK_SUPPORT_EXTENDED_FEATURES
	 * enabled
	 */
	अगर (!(dev_info->wspecversion >= 0x310 ||
	      dev_info->wspecversion == 0x220 ||
	     (hba->dev_quirks & UFS_DEVICE_QUIRK_SUPPORT_EXTENDED_FEATURES)))
		जाओ wb_disabled;

	अगर (hba->desc_size[QUERY_DESC_IDN_DEVICE] <
	    DEVICE_DESC_PARAM_EXT_UFS_FEATURE_SUP + 4)
		जाओ wb_disabled;

	ext_ufs_feature = get_unaligned_be32(desc_buf +
					DEVICE_DESC_PARAM_EXT_UFS_FEATURE_SUP);

	अगर (!(ext_ufs_feature & UFS_DEV_WRITE_BOOSTER_SUP))
		जाओ wb_disabled;

	/*
	 * WB may be supported but not configured जबतक provisioning. The spec
	 * says, in dedicated wb buffer mode, a max of 1 lun would have wb
	 * buffer configured.
	 */
	dev_info->wb_buffer_type = desc_buf[DEVICE_DESC_PARAM_WB_TYPE];

	dev_info->b_presrv_uspc_en =
		desc_buf[DEVICE_DESC_PARAM_WB_PRESRV_USRSPC_EN];

	अगर (dev_info->wb_buffer_type == WB_BUF_MODE_SHARED) अणु
		अगर (!get_unaligned_be32(desc_buf +
				   DEVICE_DESC_PARAM_WB_SHARED_ALLOC_UNITS))
			जाओ wb_disabled;
	पूर्ण अन्यथा अणु
		क्रम (lun = 0; lun < UFS_UPIU_MAX_WB_LUN_ID; lun++) अणु
			d_lu_wb_buf_alloc = 0;
			ufshcd_पढ़ो_unit_desc_param(hba,
					lun,
					UNIT_DESC_PARAM_WB_BUF_ALLOC_UNITS,
					(u8 *)&d_lu_wb_buf_alloc,
					माप(d_lu_wb_buf_alloc));
			अगर (d_lu_wb_buf_alloc) अणु
				dev_info->wb_dedicated_lu = lun;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!d_lu_wb_buf_alloc)
			जाओ wb_disabled;
	पूर्ण
	वापस;

wb_disabled:
	hba->caps &= ~UFSHCD_CAP_WB_EN;
पूर्ण

व्योम ufshcd_fixup_dev_quirks(काष्ठा ufs_hba *hba, काष्ठा ufs_dev_fix *fixups)
अणु
	काष्ठा ufs_dev_fix *f;
	काष्ठा ufs_dev_info *dev_info = &hba->dev_info;

	अगर (!fixups)
		वापस;

	क्रम (f = fixups; f->quirk; f++) अणु
		अगर ((f->wmanufacturerid == dev_info->wmanufacturerid ||
		     f->wmanufacturerid == UFS_ANY_VENDOR) &&
		     ((dev_info->model &&
		       STR_PRFX_EQUAL(f->model, dev_info->model)) ||
		      !म_भेद(f->model, UFS_ANY_MODEL)))
			hba->dev_quirks |= f->quirk;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_fixup_dev_quirks);

अटल व्योम ufs_fixup_device_setup(काष्ठा ufs_hba *hba)
अणु
	/* fix by general quirk table */
	ufshcd_fixup_dev_quirks(hba, ufs_fixups);

	/* allow venकरोrs to fix quirks */
	ufshcd_vops_fixup_dev_quirks(hba);
पूर्ण

अटल पूर्णांक ufs_get_device_desc(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err;
	u8 model_index;
	u8 *desc_buf;
	काष्ठा ufs_dev_info *dev_info = &hba->dev_info;

	desc_buf = kदो_स्मृति(QUERY_DESC_MAX_SIZE, GFP_KERNEL);
	अगर (!desc_buf) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	err = ufshcd_पढ़ो_desc_param(hba, QUERY_DESC_IDN_DEVICE, 0, 0, desc_buf,
				     hba->desc_size[QUERY_DESC_IDN_DEVICE]);
	अगर (err) अणु
		dev_err(hba->dev, "%s: Failed reading Device Desc. err = %d\n",
			__func__, err);
		जाओ out;
	पूर्ण

	/*
	 * getting venकरोr (manufacturerID) and Bank Index in big endian
	 * क्रमmat
	 */
	dev_info->wmanufacturerid = desc_buf[DEVICE_DESC_PARAM_MANF_ID] << 8 |
				     desc_buf[DEVICE_DESC_PARAM_MANF_ID + 1];

	/* getting Specअगरication Version in big endian क्रमmat */
	dev_info->wspecversion = desc_buf[DEVICE_DESC_PARAM_SPEC_VER] << 8 |
				      desc_buf[DEVICE_DESC_PARAM_SPEC_VER + 1];

	model_index = desc_buf[DEVICE_DESC_PARAM_PRDCT_NAME];

	err = ufshcd_पढ़ो_string_desc(hba, model_index,
				      &dev_info->model, SD_ASCII_STD);
	अगर (err < 0) अणु
		dev_err(hba->dev, "%s: Failed reading Product Name. err = %d\n",
			__func__, err);
		जाओ out;
	पूर्ण

	ufs_fixup_device_setup(hba);

	ufshcd_wb_probe(hba, desc_buf);

	/*
	 * ufshcd_पढ़ो_string_desc वापसs size of the string
	 * reset the error value
	 */
	err = 0;

out:
	kमुक्त(desc_buf);
	वापस err;
पूर्ण

अटल व्योम ufs_put_device_desc(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_dev_info *dev_info = &hba->dev_info;

	kमुक्त(dev_info->model);
	dev_info->model = शून्य;
पूर्ण

/**
 * ufshcd_tune_pa_tactivate - Tunes PA_TActivate of local UniPro
 * @hba: per-adapter instance
 *
 * PA_TActivate parameter can be tuned manually अगर UniPro version is less than
 * 1.61. PA_TActivate needs to be greater than or equal to peerM-PHY's
 * RX_MIN_ACTIVATETIME_CAPABILITY attribute. This optimal value can help reduce
 * the hibern8 निकास latency.
 *
 * Returns zero on success, non-zero error value on failure.
 */
अटल पूर्णांक ufshcd_tune_pa_tactivate(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret = 0;
	u32 peer_rx_min_activateसमय = 0, tuned_pa_tactivate;

	ret = ufshcd_dme_peer_get(hba,
				  UIC_ARG_MIB_SEL(
					RX_MIN_ACTIVATETIME_CAPABILITY,
					UIC_ARG_MPHY_RX_GEN_SEL_INDEX(0)),
				  &peer_rx_min_activateसमय);
	अगर (ret)
		जाओ out;

	/* make sure proper unit conversion is applied */
	tuned_pa_tactivate =
		((peer_rx_min_activateसमय * RX_MIN_ACTIVATETIME_UNIT_US)
		 / PA_TACTIVATE_TIME_UNIT_US);
	ret = ufshcd_dme_set(hba, UIC_ARG_MIB(PA_TACTIVATE),
			     tuned_pa_tactivate);

out:
	वापस ret;
पूर्ण

/**
 * ufshcd_tune_pa_hibern8समय - Tunes PA_Hibern8Time of local UniPro
 * @hba: per-adapter instance
 *
 * PA_Hibern8Time parameter can be tuned manually अगर UniPro version is less than
 * 1.61. PA_Hibern8Time needs to be maximum of local M-PHY's
 * TX_HIBERN8TIME_CAPABILITY & peer M-PHY's RX_HIBERN8TIME_CAPABILITY.
 * This optimal value can help reduce the hibern8 निकास latency.
 *
 * Returns zero on success, non-zero error value on failure.
 */
अटल पूर्णांक ufshcd_tune_pa_hibern8समय(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret = 0;
	u32 local_tx_hibern8_समय_cap = 0, peer_rx_hibern8_समय_cap = 0;
	u32 max_hibern8_समय, tuned_pa_hibern8समय;

	ret = ufshcd_dme_get(hba,
			     UIC_ARG_MIB_SEL(TX_HIBERN8TIME_CAPABILITY,
					UIC_ARG_MPHY_TX_GEN_SEL_INDEX(0)),
				  &local_tx_hibern8_समय_cap);
	अगर (ret)
		जाओ out;

	ret = ufshcd_dme_peer_get(hba,
				  UIC_ARG_MIB_SEL(RX_HIBERN8TIME_CAPABILITY,
					UIC_ARG_MPHY_RX_GEN_SEL_INDEX(0)),
				  &peer_rx_hibern8_समय_cap);
	अगर (ret)
		जाओ out;

	max_hibern8_समय = max(local_tx_hibern8_समय_cap,
			       peer_rx_hibern8_समय_cap);
	/* make sure proper unit conversion is applied */
	tuned_pa_hibern8समय = ((max_hibern8_समय * HIBERN8TIME_UNIT_US)
				/ PA_HIBERN8_TIME_UNIT_US);
	ret = ufshcd_dme_set(hba, UIC_ARG_MIB(PA_HIBERN8TIME),
			     tuned_pa_hibern8समय);
out:
	वापस ret;
पूर्ण

/**
 * ufshcd_quirk_tune_host_pa_tactivate - Ensures that host PA_TACTIVATE is
 * less than device PA_TACTIVATE समय.
 * @hba: per-adapter instance
 *
 * Some UFS devices require host PA_TACTIVATE to be lower than device
 * PA_TACTIVATE, we need to enable UFS_DEVICE_QUIRK_HOST_PA_TACTIVATE quirk
 * क्रम such devices.
 *
 * Returns zero on success, non-zero error value on failure.
 */
अटल पूर्णांक ufshcd_quirk_tune_host_pa_tactivate(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret = 0;
	u32 granularity, peer_granularity;
	u32 pa_tactivate, peer_pa_tactivate;
	u32 pa_tactivate_us, peer_pa_tactivate_us;
	u8 gran_to_us_table[] = अणु1, 4, 8, 16, 32, 100पूर्ण;

	ret = ufshcd_dme_get(hba, UIC_ARG_MIB(PA_GRANULARITY),
				  &granularity);
	अगर (ret)
		जाओ out;

	ret = ufshcd_dme_peer_get(hba, UIC_ARG_MIB(PA_GRANULARITY),
				  &peer_granularity);
	अगर (ret)
		जाओ out;

	अगर ((granularity < PA_GRANULARITY_MIN_VAL) ||
	    (granularity > PA_GRANULARITY_MAX_VAL)) अणु
		dev_err(hba->dev, "%s: invalid host PA_GRANULARITY %d",
			__func__, granularity);
		वापस -EINVAL;
	पूर्ण

	अगर ((peer_granularity < PA_GRANULARITY_MIN_VAL) ||
	    (peer_granularity > PA_GRANULARITY_MAX_VAL)) अणु
		dev_err(hba->dev, "%s: invalid device PA_GRANULARITY %d",
			__func__, peer_granularity);
		वापस -EINVAL;
	पूर्ण

	ret = ufshcd_dme_get(hba, UIC_ARG_MIB(PA_TACTIVATE), &pa_tactivate);
	अगर (ret)
		जाओ out;

	ret = ufshcd_dme_peer_get(hba, UIC_ARG_MIB(PA_TACTIVATE),
				  &peer_pa_tactivate);
	अगर (ret)
		जाओ out;

	pa_tactivate_us = pa_tactivate * gran_to_us_table[granularity - 1];
	peer_pa_tactivate_us = peer_pa_tactivate *
			     gran_to_us_table[peer_granularity - 1];

	अगर (pa_tactivate_us > peer_pa_tactivate_us) अणु
		u32 new_peer_pa_tactivate;

		new_peer_pa_tactivate = pa_tactivate_us /
				      gran_to_us_table[peer_granularity - 1];
		new_peer_pa_tactivate++;
		ret = ufshcd_dme_peer_set(hba, UIC_ARG_MIB(PA_TACTIVATE),
					  new_peer_pa_tactivate);
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल व्योम ufshcd_tune_unipro_params(काष्ठा ufs_hba *hba)
अणु
	अगर (ufshcd_is_unipro_pa_params_tuning_req(hba)) अणु
		ufshcd_tune_pa_tactivate(hba);
		ufshcd_tune_pa_hibern8समय(hba);
	पूर्ण

	ufshcd_vops_apply_dev_quirks(hba);

	अगर (hba->dev_quirks & UFS_DEVICE_QUIRK_PA_TACTIVATE)
		/* set 1ms समयout क्रम PA_TACTIVATE */
		ufshcd_dme_set(hba, UIC_ARG_MIB(PA_TACTIVATE), 10);

	अगर (hba->dev_quirks & UFS_DEVICE_QUIRK_HOST_PA_TACTIVATE)
		ufshcd_quirk_tune_host_pa_tactivate(hba);
पूर्ण

अटल व्योम ufshcd_clear_dbg_ufs_stats(काष्ठा ufs_hba *hba)
अणु
	hba->ufs_stats.hibern8_निकास_cnt = 0;
	hba->ufs_stats.last_hibern8_निकास_tstamp = kसमय_set(0, 0);
	hba->req_पात_count = 0;
पूर्ण

अटल पूर्णांक ufshcd_device_geo_params_init(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err;
	माप_प्रकार buff_len;
	u8 *desc_buf;

	buff_len = hba->desc_size[QUERY_DESC_IDN_GEOMETRY];
	desc_buf = kदो_स्मृति(buff_len, GFP_KERNEL);
	अगर (!desc_buf) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	err = ufshcd_पढ़ो_desc_param(hba, QUERY_DESC_IDN_GEOMETRY, 0, 0,
				     desc_buf, buff_len);
	अगर (err) अणु
		dev_err(hba->dev, "%s: Failed reading Geometry Desc. err = %d\n",
				__func__, err);
		जाओ out;
	पूर्ण

	अगर (desc_buf[GEOMETRY_DESC_PARAM_MAX_NUM_LUN] == 1)
		hba->dev_info.max_lu_supported = 32;
	अन्यथा अगर (desc_buf[GEOMETRY_DESC_PARAM_MAX_NUM_LUN] == 0)
		hba->dev_info.max_lu_supported = 8;

out:
	kमुक्त(desc_buf);
	वापस err;
पूर्ण

अटल काष्ठा ufs_ref_clk ufs_ref_clk_freqs[] = अणु
	अणु19200000, REF_CLK_FREQ_19_2_MHZपूर्ण,
	अणु26000000, REF_CLK_FREQ_26_MHZपूर्ण,
	अणु38400000, REF_CLK_FREQ_38_4_MHZपूर्ण,
	अणु52000000, REF_CLK_FREQ_52_MHZपूर्ण,
	अणु0, REF_CLK_FREQ_INVALपूर्ण,
पूर्ण;

अटल क्रमागत ufs_ref_clk_freq
ufs_get_bref_clk_from_hz(अचिन्हित दीर्घ freq)
अणु
	पूर्णांक i;

	क्रम (i = 0; ufs_ref_clk_freqs[i].freq_hz; i++)
		अगर (ufs_ref_clk_freqs[i].freq_hz == freq)
			वापस ufs_ref_clk_freqs[i].val;

	वापस REF_CLK_FREQ_INVAL;
पूर्ण

व्योम ufshcd_parse_dev_ref_clk_freq(काष्ठा ufs_hba *hba, काष्ठा clk *refclk)
अणु
	अचिन्हित दीर्घ freq;

	freq = clk_get_rate(refclk);

	hba->dev_ref_clk_freq =
		ufs_get_bref_clk_from_hz(freq);

	अगर (hba->dev_ref_clk_freq == REF_CLK_FREQ_INVAL)
		dev_err(hba->dev,
		"invalid ref_clk setting = %ld\n", freq);
पूर्ण

अटल पूर्णांक ufshcd_set_dev_ref_clk(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err;
	u32 ref_clk;
	u32 freq = hba->dev_ref_clk_freq;

	err = ufshcd_query_attr_retry(hba, UPIU_QUERY_OPCODE_READ_ATTR,
			QUERY_ATTR_IDN_REF_CLK_FREQ, 0, 0, &ref_clk);

	अगर (err) अणु
		dev_err(hba->dev, "failed reading bRefClkFreq. err = %d\n",
			err);
		जाओ out;
	पूर्ण

	अगर (ref_clk == freq)
		जाओ out; /* nothing to update */

	err = ufshcd_query_attr_retry(hba, UPIU_QUERY_OPCODE_WRITE_ATTR,
			QUERY_ATTR_IDN_REF_CLK_FREQ, 0, 0, &freq);

	अगर (err) अणु
		dev_err(hba->dev, "bRefClkFreq setting to %lu Hz failed\n",
			ufs_ref_clk_freqs[freq].freq_hz);
		जाओ out;
	पूर्ण

	dev_dbg(hba->dev, "bRefClkFreq setting to %lu Hz succeeded\n",
			ufs_ref_clk_freqs[freq].freq_hz);

out:
	वापस err;
पूर्ण

अटल पूर्णांक ufshcd_device_params_init(काष्ठा ufs_hba *hba)
अणु
	bool flag;
	पूर्णांक ret, i;

	 /* Init device descriptor sizes */
	क्रम (i = 0; i < QUERY_DESC_IDN_MAX; i++)
		hba->desc_size[i] = QUERY_DESC_MAX_SIZE;

	/* Init UFS geometry descriptor related parameters */
	ret = ufshcd_device_geo_params_init(hba);
	अगर (ret)
		जाओ out;

	/* Check and apply UFS device quirks */
	ret = ufs_get_device_desc(hba);
	अगर (ret) अणु
		dev_err(hba->dev, "%s: Failed getting device info. err = %d\n",
			__func__, ret);
		जाओ out;
	पूर्ण

	ufshcd_get_ref_clk_gating_रुको(hba);

	अगर (!ufshcd_query_flag_retry(hba, UPIU_QUERY_OPCODE_READ_FLAG,
			QUERY_FLAG_IDN_PWR_ON_WPE, 0, &flag))
		hba->dev_info.f_घातer_on_wp_en = flag;

	/* Probe maximum घातer mode co-supported by both UFS host and device */
	अगर (ufshcd_get_max_pwr_mode(hba))
		dev_err(hba->dev,
			"%s: Failed getting max supported power mode\n",
			__func__);
out:
	वापस ret;
पूर्ण

/**
 * ufshcd_add_lus - probe and add UFS logical units
 * @hba: per-adapter instance
 */
अटल पूर्णांक ufshcd_add_lus(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret;

	/* Add required well known logical units to scsi mid layer */
	ret = ufshcd_scsi_add_wlus(hba);
	अगर (ret)
		जाओ out;

	ufshcd_clear_ua_wluns(hba);

	/* Initialize devfreq after UFS device is detected */
	अगर (ufshcd_is_clkscaling_supported(hba)) अणु
		स_नकल(&hba->clk_scaling.saved_pwr_info.info,
			&hba->pwr_info,
			माप(काष्ठा ufs_pa_layer_attr));
		hba->clk_scaling.saved_pwr_info.is_valid = true;
		hba->clk_scaling.is_allowed = true;

		ret = ufshcd_devfreq_init(hba);
		अगर (ret)
			जाओ out;

		hba->clk_scaling.is_enabled = true;
		ufshcd_init_clk_scaling_sysfs(hba);
	पूर्ण

	ufs_bsg_probe(hba);
	scsi_scan_host(hba->host);
	pm_runसमय_put_sync(hba->dev);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक
ufshcd_send_request_sense(काष्ठा ufs_hba *hba, काष्ठा scsi_device *sdp);

अटल पूर्णांक ufshcd_clear_ua_wlun(काष्ठा ufs_hba *hba, u8 wlun)
अणु
	काष्ठा scsi_device *sdp;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(hba->host->host_lock, flags);
	अगर (wlun == UFS_UPIU_UFS_DEVICE_WLUN)
		sdp = hba->sdev_ufs_device;
	अन्यथा अगर (wlun == UFS_UPIU_RPMB_WLUN)
		sdp = hba->sdev_rpmb;
	अन्यथा
		BUG();
	अगर (sdp) अणु
		ret = scsi_device_get(sdp);
		अगर (!ret && !scsi_device_online(sdp)) अणु
			ret = -ENODEV;
			scsi_device_put(sdp);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -ENODEV;
	पूर्ण
	spin_unlock_irqrestore(hba->host->host_lock, flags);
	अगर (ret)
		जाओ out_err;

	ret = ufshcd_send_request_sense(hba, sdp);
	scsi_device_put(sdp);
out_err:
	अगर (ret)
		dev_err(hba->dev, "%s: UAC clear LU=%x ret = %d\n",
				__func__, wlun, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक ufshcd_clear_ua_wluns(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret = 0;

	अगर (!hba->wlun_dev_clr_ua)
		जाओ out;

	ret = ufshcd_clear_ua_wlun(hba, UFS_UPIU_UFS_DEVICE_WLUN);
	अगर (!ret)
		ret = ufshcd_clear_ua_wlun(hba, UFS_UPIU_RPMB_WLUN);
	अगर (!ret)
		hba->wlun_dev_clr_ua = false;
out:
	अगर (ret)
		dev_err(hba->dev, "%s: Failed to clear UAC WLUNS ret = %d\n",
				__func__, ret);
	वापस ret;
पूर्ण

/**
 * ufshcd_probe_hba - probe hba to detect device and initialize
 * @hba: per-adapter instance
 * @async: asynchronous execution or not
 *
 * Execute link-startup and verअगरy device initialization
 */
अटल पूर्णांक ufshcd_probe_hba(काष्ठा ufs_hba *hba, bool async)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	kसमय_प्रकार start = kसमय_get();

	hba->ufshcd_state = UFSHCD_STATE_RESET;

	ret = ufshcd_link_startup(hba);
	अगर (ret)
		जाओ out;

	/* Debug counters initialization */
	ufshcd_clear_dbg_ufs_stats(hba);

	/* UniPro link is active now */
	ufshcd_set_link_active(hba);

	/* Verअगरy device initialization by sending NOP OUT UPIU */
	ret = ufshcd_verअगरy_dev_init(hba);
	अगर (ret)
		जाओ out;

	/* Initiate UFS initialization, and रुकोing until completion */
	ret = ufshcd_complete_dev_init(hba);
	अगर (ret)
		जाओ out;

	/*
	 * Initialize UFS device parameters used by driver, these
	 * parameters are associated with UFS descriptors.
	 */
	अगर (async) अणु
		ret = ufshcd_device_params_init(hba);
		अगर (ret)
			जाओ out;
	पूर्ण

	ufshcd_tune_unipro_params(hba);

	/* UFS device is also active now */
	ufshcd_set_ufs_dev_active(hba);
	ufshcd_क्रमce_reset_स्वतः_bkops(hba);
	hba->wlun_dev_clr_ua = true;

	/* Gear up to HS gear अगर supported */
	अगर (hba->max_pwr_info.is_valid) अणु
		/*
		 * Set the right value to bRefClkFreq beक्रमe attempting to
		 * चयन to HS gears.
		 */
		अगर (hba->dev_ref_clk_freq != REF_CLK_FREQ_INVAL)
			ufshcd_set_dev_ref_clk(hba);
		ret = ufshcd_config_pwr_mode(hba, &hba->max_pwr_info.info);
		अगर (ret) अणु
			dev_err(hba->dev, "%s: Failed setting power mode, err = %d\n",
					__func__, ret);
			जाओ out;
		पूर्ण
		ufshcd_prपूर्णांक_pwr_info(hba);
	पूर्ण

	/*
	 * bActiveICCLevel is अस्थिर क्रम UFS device (as per latest v2.1 spec)
	 * and क्रम removable UFS card as well, hence always set the parameter.
	 * Note: Error handler may issue the device reset hence resetting
	 * bActiveICCLevel as well so it is always safe to set this here.
	 */
	ufshcd_set_active_icc_lvl(hba);

	ufshcd_wb_config(hba);
	अगर (hba->ee_usr_mask)
		ufshcd_ग_लिखो_ee_control(hba);
	/* Enable Auto-Hibernate अगर configured */
	ufshcd_स्वतः_hibern8_enable(hba);

out:
	spin_lock_irqsave(hba->host->host_lock, flags);
	अगर (ret)
		hba->ufshcd_state = UFSHCD_STATE_ERROR;
	अन्यथा अगर (hba->ufshcd_state == UFSHCD_STATE_RESET)
		hba->ufshcd_state = UFSHCD_STATE_OPERATIONAL;
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	trace_ufshcd_init(dev_name(hba->dev), ret,
		kसमय_प्रकारo_us(kसमय_sub(kसमय_get(), start)),
		hba->curr_dev_pwr_mode, hba->uic_link_state);
	वापस ret;
पूर्ण

/**
 * ufshcd_async_scan - asynchronous execution क्रम probing hba
 * @data: data poपूर्णांकer to pass to this function
 * @cookie: cookie data
 */
अटल व्योम ufshcd_async_scan(व्योम *data, async_cookie_t cookie)
अणु
	काष्ठा ufs_hba *hba = (काष्ठा ufs_hba *)data;
	पूर्णांक ret;

	करोwn(&hba->host_sem);
	/* Initialize hba, detect and initialize UFS device */
	ret = ufshcd_probe_hba(hba, true);
	up(&hba->host_sem);
	अगर (ret)
		जाओ out;

	/* Probe and add UFS logical units  */
	ret = ufshcd_add_lus(hba);
out:
	/*
	 * If we failed to initialize the device or the device is not
	 * present, turn off the घातer/घड़ीs etc.
	 */
	अगर (ret) अणु
		pm_runसमय_put_sync(hba->dev);
		ufshcd_hba_निकास(hba);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा attribute_group *ufshcd_driver_groups[] = अणु
	&ufs_sysfs_unit_descriptor_group,
	&ufs_sysfs_lun_attributes_group,
	शून्य,
पूर्ण;

अटल काष्ठा ufs_hba_variant_params ufs_hba_vps = अणु
	.hba_enable_delay_us		= 1000,
	.wb_flush_threshold		= UFS_WB_BUF_REMAIN_PERCENT(40),
	.devfreq_profile.polling_ms	= 100,
	.devfreq_profile.target		= ufshcd_devfreq_target,
	.devfreq_profile.get_dev_status	= ufshcd_devfreq_get_dev_status,
	.ondemand_data.upthreshold	= 70,
	.ondemand_data.करोwndअगरferential	= 5,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा ufshcd_driver_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= UFSHCD,
	.proc_name		= UFSHCD,
	.queuecommand		= ufshcd_queuecommand,
	.slave_alloc		= ufshcd_slave_alloc,
	.slave_configure	= ufshcd_slave_configure,
	.slave_destroy		= ufshcd_slave_destroy,
	.change_queue_depth	= ufshcd_change_queue_depth,
	.eh_पात_handler	= ufshcd_पात,
	.eh_device_reset_handler = ufshcd_eh_device_reset_handler,
	.eh_host_reset_handler   = ufshcd_eh_host_reset_handler,
	.this_id		= -1,
	.sg_tablesize		= SG_ALL,
	.cmd_per_lun		= UFSHCD_CMD_PER_LUN,
	.can_queue		= UFSHCD_CAN_QUEUE,
	.max_segment_size	= PRDT_DATA_BYTE_COUNT_MAX,
	.max_host_blocked	= 1,
	.track_queue_depth	= 1,
	.sdev_groups		= ufshcd_driver_groups,
	.dma_boundary		= PAGE_SIZE - 1,
	.rpm_स्वतःsuspend_delay	= RPM_AUTOSUSPEND_DELAY_MS,
पूर्ण;

अटल पूर्णांक ufshcd_config_vreg_load(काष्ठा device *dev, काष्ठा ufs_vreg *vreg,
				   पूर्णांक ua)
अणु
	पूर्णांक ret;

	अगर (!vreg)
		वापस 0;

	/*
	 * "set_load" operation shall be required on those regulators
	 * which specअगरically configured current limitation. Otherwise
	 * zero max_uA may cause unexpected behavior when regulator is
	 * enabled or set as high घातer mode.
	 */
	अगर (!vreg->max_uA)
		वापस 0;

	ret = regulator_set_load(vreg->reg, ua);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: %s set load (ua=%d) failed, err=%d\n",
				__func__, vreg->name, ua, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_config_vreg_lpm(काष्ठा ufs_hba *hba,
					 काष्ठा ufs_vreg *vreg)
अणु
	वापस ufshcd_config_vreg_load(hba->dev, vreg, UFS_VREG_LPM_LOAD_UA);
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_config_vreg_hpm(काष्ठा ufs_hba *hba,
					 काष्ठा ufs_vreg *vreg)
अणु
	अगर (!vreg)
		वापस 0;

	वापस ufshcd_config_vreg_load(hba->dev, vreg, vreg->max_uA);
पूर्ण

अटल पूर्णांक ufshcd_config_vreg(काष्ठा device *dev,
		काष्ठा ufs_vreg *vreg, bool on)
अणु
	पूर्णांक ret = 0;
	काष्ठा regulator *reg;
	स्थिर अक्षर *name;
	पूर्णांक min_uV, uA_load;

	BUG_ON(!vreg);

	reg = vreg->reg;
	name = vreg->name;

	अगर (regulator_count_voltages(reg) > 0) अणु
		uA_load = on ? vreg->max_uA : 0;
		ret = ufshcd_config_vreg_load(dev, vreg, uA_load);
		अगर (ret)
			जाओ out;

		अगर (vreg->min_uV && vreg->max_uV) अणु
			min_uV = on ? vreg->min_uV : 0;
			ret = regulator_set_voltage(reg, min_uV, vreg->max_uV);
			अगर (ret)
				dev_err(dev,
					"%s: %s set voltage failed, err=%d\n",
					__func__, name, ret);
		पूर्ण
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ufshcd_enable_vreg(काष्ठा device *dev, काष्ठा ufs_vreg *vreg)
अणु
	पूर्णांक ret = 0;

	अगर (!vreg || vreg->enabled)
		जाओ out;

	ret = ufshcd_config_vreg(dev, vreg, true);
	अगर (!ret)
		ret = regulator_enable(vreg->reg);

	अगर (!ret)
		vreg->enabled = true;
	अन्यथा
		dev_err(dev, "%s: %s enable failed, err=%d\n",
				__func__, vreg->name, ret);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ufshcd_disable_vreg(काष्ठा device *dev, काष्ठा ufs_vreg *vreg)
अणु
	पूर्णांक ret = 0;

	अगर (!vreg || !vreg->enabled || vreg->always_on)
		जाओ out;

	ret = regulator_disable(vreg->reg);

	अगर (!ret) अणु
		/* ignore errors on applying disable config */
		ufshcd_config_vreg(dev, vreg, false);
		vreg->enabled = false;
	पूर्ण अन्यथा अणु
		dev_err(dev, "%s: %s disable failed, err=%d\n",
				__func__, vreg->name, ret);
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ufshcd_setup_vreg(काष्ठा ufs_hba *hba, bool on)
अणु
	पूर्णांक ret = 0;
	काष्ठा device *dev = hba->dev;
	काष्ठा ufs_vreg_info *info = &hba->vreg_info;

	ret = ufshcd_toggle_vreg(dev, info->vcc, on);
	अगर (ret)
		जाओ out;

	ret = ufshcd_toggle_vreg(dev, info->vccq, on);
	अगर (ret)
		जाओ out;

	ret = ufshcd_toggle_vreg(dev, info->vccq2, on);

out:
	अगर (ret) अणु
		ufshcd_toggle_vreg(dev, info->vccq2, false);
		ufshcd_toggle_vreg(dev, info->vccq, false);
		ufshcd_toggle_vreg(dev, info->vcc, false);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ufshcd_setup_hba_vreg(काष्ठा ufs_hba *hba, bool on)
अणु
	काष्ठा ufs_vreg_info *info = &hba->vreg_info;

	वापस ufshcd_toggle_vreg(hba->dev, info->vdd_hba, on);
पूर्ण

अटल पूर्णांक ufshcd_get_vreg(काष्ठा device *dev, काष्ठा ufs_vreg *vreg)
अणु
	पूर्णांक ret = 0;

	अगर (!vreg)
		जाओ out;

	vreg->reg = devm_regulator_get(dev, vreg->name);
	अगर (IS_ERR(vreg->reg)) अणु
		ret = PTR_ERR(vreg->reg);
		dev_err(dev, "%s: %s get failed, err=%d\n",
				__func__, vreg->name, ret);
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ufshcd_init_vreg(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret = 0;
	काष्ठा device *dev = hba->dev;
	काष्ठा ufs_vreg_info *info = &hba->vreg_info;

	ret = ufshcd_get_vreg(dev, info->vcc);
	अगर (ret)
		जाओ out;

	ret = ufshcd_get_vreg(dev, info->vccq);
	अगर (!ret)
		ret = ufshcd_get_vreg(dev, info->vccq2);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ufshcd_init_hba_vreg(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_vreg_info *info = &hba->vreg_info;

	अगर (info)
		वापस ufshcd_get_vreg(hba->dev, info->vdd_hba);

	वापस 0;
पूर्ण

अटल पूर्णांक ufshcd_setup_घड़ीs(काष्ठा ufs_hba *hba, bool on)
अणु
	पूर्णांक ret = 0;
	काष्ठा ufs_clk_info *clki;
	काष्ठा list_head *head = &hba->clk_list_head;
	अचिन्हित दीर्घ flags;
	kसमय_प्रकार start = kसमय_get();
	bool clk_state_changed = false;

	अगर (list_empty(head))
		जाओ out;

	ret = ufshcd_vops_setup_घड़ीs(hba, on, PRE_CHANGE);
	अगर (ret)
		वापस ret;

	list_क्रम_each_entry(clki, head, list) अणु
		अगर (!IS_ERR_OR_शून्य(clki->clk)) अणु
			/*
			 * Don't disable घड़ीs which are needed
			 * to keep the link active.
			 */
			अगर (ufshcd_is_link_active(hba) &&
			    clki->keep_link_active)
				जारी;

			clk_state_changed = on ^ clki->enabled;
			अगर (on && !clki->enabled) अणु
				ret = clk_prepare_enable(clki->clk);
				अगर (ret) अणु
					dev_err(hba->dev, "%s: %s prepare enable failed, %d\n",
						__func__, clki->name, ret);
					जाओ out;
				पूर्ण
			पूर्ण अन्यथा अगर (!on && clki->enabled) अणु
				clk_disable_unprepare(clki->clk);
			पूर्ण
			clki->enabled = on;
			dev_dbg(hba->dev, "%s: clk: %s %sabled\n", __func__,
					clki->name, on ? "en" : "dis");
		पूर्ण
	पूर्ण

	ret = ufshcd_vops_setup_घड़ीs(hba, on, POST_CHANGE);
	अगर (ret)
		वापस ret;

out:
	अगर (ret) अणु
		list_क्रम_each_entry(clki, head, list) अणु
			अगर (!IS_ERR_OR_शून्य(clki->clk) && clki->enabled)
				clk_disable_unprepare(clki->clk);
		पूर्ण
	पूर्ण अन्यथा अगर (!ret && on) अणु
		spin_lock_irqsave(hba->host->host_lock, flags);
		hba->clk_gating.state = CLKS_ON;
		trace_ufshcd_clk_gating(dev_name(hba->dev),
					hba->clk_gating.state);
		spin_unlock_irqrestore(hba->host->host_lock, flags);
	पूर्ण

	अगर (clk_state_changed)
		trace_ufshcd_profile_clk_gating(dev_name(hba->dev),
			(on ? "on" : "off"),
			kसमय_प्रकारo_us(kसमय_sub(kसमय_get(), start)), ret);
	वापस ret;
पूर्ण

अटल पूर्णांक ufshcd_init_घड़ीs(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret = 0;
	काष्ठा ufs_clk_info *clki;
	काष्ठा device *dev = hba->dev;
	काष्ठा list_head *head = &hba->clk_list_head;

	अगर (list_empty(head))
		जाओ out;

	list_क्रम_each_entry(clki, head, list) अणु
		अगर (!clki->name)
			जारी;

		clki->clk = devm_clk_get(dev, clki->name);
		अगर (IS_ERR(clki->clk)) अणु
			ret = PTR_ERR(clki->clk);
			dev_err(dev, "%s: %s clk get failed, %d\n",
					__func__, clki->name, ret);
			जाओ out;
		पूर्ण

		/*
		 * Parse device ref clk freq as per device tree "ref_clk".
		 * Default dev_ref_clk_freq is set to REF_CLK_FREQ_INVAL
		 * in ufshcd_alloc_host().
		 */
		अगर (!म_भेद(clki->name, "ref_clk"))
			ufshcd_parse_dev_ref_clk_freq(hba, clki->clk);

		अगर (clki->max_freq) अणु
			ret = clk_set_rate(clki->clk, clki->max_freq);
			अगर (ret) अणु
				dev_err(hba->dev, "%s: %s clk set rate(%dHz) failed, %d\n",
					__func__, clki->name,
					clki->max_freq, ret);
				जाओ out;
			पूर्ण
			clki->curr_freq = clki->max_freq;
		पूर्ण
		dev_dbg(dev, "%s: clk: %s, rate: %lu\n", __func__,
				clki->name, clk_get_rate(clki->clk));
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ufshcd_variant_hba_init(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err = 0;

	अगर (!hba->vops)
		जाओ out;

	err = ufshcd_vops_init(hba);
	अगर (err)
		dev_err(hba->dev, "%s: variant %s init failed err %d\n",
			__func__, ufshcd_get_var_name(hba), err);
out:
	वापस err;
पूर्ण

अटल व्योम ufshcd_variant_hba_निकास(काष्ठा ufs_hba *hba)
अणु
	अगर (!hba->vops)
		वापस;

	ufshcd_vops_निकास(hba);
पूर्ण

अटल पूर्णांक ufshcd_hba_init(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err;

	/*
	 * Handle host controller घातer separately from the UFS device घातer
	 * rails as it will help controlling the UFS host controller घातer
	 * collapse easily which is dअगरferent than UFS device घातer collapse.
	 * Also, enable the host controller घातer beक्रमe we go ahead with rest
	 * of the initialization here.
	 */
	err = ufshcd_init_hba_vreg(hba);
	अगर (err)
		जाओ out;

	err = ufshcd_setup_hba_vreg(hba, true);
	अगर (err)
		जाओ out;

	err = ufshcd_init_घड़ीs(hba);
	अगर (err)
		जाओ out_disable_hba_vreg;

	err = ufshcd_setup_घड़ीs(hba, true);
	अगर (err)
		जाओ out_disable_hba_vreg;

	err = ufshcd_init_vreg(hba);
	अगर (err)
		जाओ out_disable_clks;

	err = ufshcd_setup_vreg(hba, true);
	अगर (err)
		जाओ out_disable_clks;

	err = ufshcd_variant_hba_init(hba);
	अगर (err)
		जाओ out_disable_vreg;

	ufs_debugfs_hba_init(hba);

	hba->is_घातered = true;
	जाओ out;

out_disable_vreg:
	ufshcd_setup_vreg(hba, false);
out_disable_clks:
	ufshcd_setup_घड़ीs(hba, false);
out_disable_hba_vreg:
	ufshcd_setup_hba_vreg(hba, false);
out:
	वापस err;
पूर्ण

अटल व्योम ufshcd_hba_निकास(काष्ठा ufs_hba *hba)
अणु
	अगर (hba->is_घातered) अणु
		ufshcd_निकास_clk_scaling(hba);
		ufshcd_निकास_clk_gating(hba);
		अगर (hba->eh_wq)
			destroy_workqueue(hba->eh_wq);
		ufs_debugfs_hba_निकास(hba);
		ufshcd_variant_hba_निकास(hba);
		ufshcd_setup_vreg(hba, false);
		ufshcd_setup_घड़ीs(hba, false);
		ufshcd_setup_hba_vreg(hba, false);
		hba->is_घातered = false;
		ufs_put_device_desc(hba);
	पूर्ण
पूर्ण

अटल पूर्णांक
ufshcd_send_request_sense(काष्ठा ufs_hba *hba, काष्ठा scsi_device *sdp)
अणु
	अचिन्हित अक्षर cmd[6] = अणुREQUEST_SENSE,
				0,
				0,
				0,
				UFS_SENSE_SIZE,
				0पूर्ण;
	अक्षर *buffer;
	पूर्णांक ret;

	buffer = kzalloc(UFS_SENSE_SIZE, GFP_KERNEL);
	अगर (!buffer) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = scsi_execute(sdp, cmd, DMA_FROM_DEVICE, buffer,
			UFS_SENSE_SIZE, शून्य, शून्य,
			msecs_to_jअगरfies(1000), 3, 0, RQF_PM, शून्य);
	अगर (ret)
		pr_err("%s: failed with err %d\n", __func__, ret);

	kमुक्त(buffer);
out:
	वापस ret;
पूर्ण

/**
 * ufshcd_set_dev_pwr_mode - sends START STOP UNIT command to set device
 *			     घातer mode
 * @hba: per adapter instance
 * @pwr_mode: device घातer mode to set
 *
 * Returns 0 अगर requested घातer mode is set successfully
 * Returns non-zero अगर failed to set the requested घातer mode
 */
अटल पूर्णांक ufshcd_set_dev_pwr_mode(काष्ठा ufs_hba *hba,
				     क्रमागत ufs_dev_pwr_mode pwr_mode)
अणु
	अचिन्हित अक्षर cmd[6] = अणु START_STOP पूर्ण;
	काष्ठा scsi_sense_hdr sshdr;
	काष्ठा scsi_device *sdp;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(hba->host->host_lock, flags);
	sdp = hba->sdev_ufs_device;
	अगर (sdp) अणु
		ret = scsi_device_get(sdp);
		अगर (!ret && !scsi_device_online(sdp)) अणु
			ret = -ENODEV;
			scsi_device_put(sdp);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -ENODEV;
	पूर्ण
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	अगर (ret)
		वापस ret;

	/*
	 * If scsi commands fail, the scsi mid-layer schedules scsi error-
	 * handling, which would रुको क्रम host to be resumed. Since we know
	 * we are functional जबतक we are here, skip host resume in error
	 * handling context.
	 */
	hba->host->eh_noresume = 1;
	ufshcd_clear_ua_wluns(hba);

	cmd[4] = pwr_mode << 4;

	/*
	 * Current function would be generally called from the घातer management
	 * callbacks hence set the RQF_PM flag so that it करोesn't resume the
	 * alपढ़ोy suspended childs.
	 */
	ret = scsi_execute(sdp, cmd, DMA_NONE, शून्य, 0, शून्य, &sshdr,
			START_STOP_TIMEOUT, 0, 0, RQF_PM, शून्य);
	अगर (ret) अणु
		sdev_prपूर्णांकk(KERN_WARNING, sdp,
			    "START_STOP failed for power mode: %d, result %x\n",
			    pwr_mode, ret);
		अगर (driver_byte(ret) == DRIVER_SENSE)
			scsi_prपूर्णांक_sense_hdr(sdp, शून्य, &sshdr);
	पूर्ण

	अगर (!ret)
		hba->curr_dev_pwr_mode = pwr_mode;

	scsi_device_put(sdp);
	hba->host->eh_noresume = 0;
	वापस ret;
पूर्ण

अटल पूर्णांक ufshcd_link_state_transition(काष्ठा ufs_hba *hba,
					क्रमागत uic_link_state req_link_state,
					पूर्णांक check_क्रम_bkops)
अणु
	पूर्णांक ret = 0;

	अगर (req_link_state == hba->uic_link_state)
		वापस 0;

	अगर (req_link_state == UIC_LINK_HIBERN8_STATE) अणु
		ret = ufshcd_uic_hibern8_enter(hba);
		अगर (!ret) अणु
			ufshcd_set_link_hibern8(hba);
		पूर्ण अन्यथा अणु
			dev_err(hba->dev, "%s: hibern8 enter failed %d\n",
					__func__, ret);
			जाओ out;
		पूर्ण
	पूर्ण
	/*
	 * If स्वतःbkops is enabled, link can't be turned off because
	 * turning off the link would also turn off the device, except in the
	 * हाल of DeepSleep where the device is expected to reमुख्य घातered.
	 */
	अन्यथा अगर ((req_link_state == UIC_LINK_OFF_STATE) &&
		 (!check_क्रम_bkops || !hba->स्वतः_bkops_enabled)) अणु
		/*
		 * Let's make sure that link is in low घातer mode, we are करोing
		 * this currently by putting the link in Hibern8. Otherway to
		 * put the link in low घातer mode is to send the DME end poपूर्णांक
		 * to device and then send the DME reset command to local
		 * unipro. But putting the link in hibern8 is much faster.
		 *
		 * Note also that putting the link in Hibern8 is a requirement
		 * क्रम entering DeepSleep.
		 */
		ret = ufshcd_uic_hibern8_enter(hba);
		अगर (ret) अणु
			dev_err(hba->dev, "%s: hibern8 enter failed %d\n",
					__func__, ret);
			जाओ out;
		पूर्ण
		/*
		 * Change controller state to "reset state" which
		 * should also put the link in off/reset state
		 */
		ufshcd_hba_stop(hba);
		/*
		 * TODO: Check अगर we need any delay to make sure that
		 * controller is reset
		 */
		ufshcd_set_link_off(hba);
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल व्योम ufshcd_vreg_set_lpm(काष्ठा ufs_hba *hba)
अणु
	bool vcc_off = false;

	/*
	 * It seems some UFS devices may keep drawing more than sleep current
	 * (atleast क्रम 500us) from UFS rails (especially from VCCQ rail).
	 * To aव्योम this situation, add 2ms delay beक्रमe putting these UFS
	 * rails in LPM mode.
	 */
	अगर (!ufshcd_is_link_active(hba) &&
	    hba->dev_quirks & UFS_DEVICE_QUIRK_DELAY_BEFORE_LPM)
		usleep_range(2000, 2100);

	/*
	 * If UFS device is either in UFS_Sleep turn off VCC rail to save some
	 * घातer.
	 *
	 * If UFS device and link is in OFF state, all घातer supplies (VCC,
	 * VCCQ, VCCQ2) can be turned off अगर घातer on ग_लिखो protect is not
	 * required. If UFS link is inactive (Hibern8 or OFF state) and device
	 * is in sleep state, put VCCQ & VCCQ2 rails in LPM mode.
	 *
	 * Ignore the error वापसed by ufshcd_toggle_vreg() as device is anyway
	 * in low घातer state which would save some घातer.
	 *
	 * If Write Booster is enabled and the device needs to flush the WB
	 * buffer OR अगर bkops status is urgent क्रम WB, keep Vcc on.
	 */
	अगर (ufshcd_is_ufs_dev_घातeroff(hba) && ufshcd_is_link_off(hba) &&
	    !hba->dev_info.is_lu_घातer_on_wp) अणु
		ufshcd_setup_vreg(hba, false);
		vcc_off = true;
	पूर्ण अन्यथा अगर (!ufshcd_is_ufs_dev_active(hba)) अणु
		ufshcd_toggle_vreg(hba->dev, hba->vreg_info.vcc, false);
		vcc_off = true;
		अगर (ufshcd_is_link_hibern8(hba) || ufshcd_is_link_off(hba)) अणु
			ufshcd_config_vreg_lpm(hba, hba->vreg_info.vccq);
			ufshcd_config_vreg_lpm(hba, hba->vreg_info.vccq2);
		पूर्ण
	पूर्ण

	/*
	 * Some UFS devices require delay after VCC घातer rail is turned-off.
	 */
	अगर (vcc_off && hba->vreg_info.vcc &&
		hba->dev_quirks & UFS_DEVICE_QUIRK_DELAY_AFTER_LPM)
		usleep_range(5000, 5100);
पूर्ण

अटल पूर्णांक ufshcd_vreg_set_hpm(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret = 0;

	अगर (ufshcd_is_ufs_dev_घातeroff(hba) && ufshcd_is_link_off(hba) &&
	    !hba->dev_info.is_lu_घातer_on_wp) अणु
		ret = ufshcd_setup_vreg(hba, true);
	पूर्ण अन्यथा अगर (!ufshcd_is_ufs_dev_active(hba)) अणु
		अगर (!ufshcd_is_link_active(hba)) अणु
			ret = ufshcd_config_vreg_hpm(hba, hba->vreg_info.vccq);
			अगर (ret)
				जाओ vcc_disable;
			ret = ufshcd_config_vreg_hpm(hba, hba->vreg_info.vccq2);
			अगर (ret)
				जाओ vccq_lpm;
		पूर्ण
		ret = ufshcd_toggle_vreg(hba->dev, hba->vreg_info.vcc, true);
	पूर्ण
	जाओ out;

vccq_lpm:
	ufshcd_config_vreg_lpm(hba, hba->vreg_info.vccq);
vcc_disable:
	ufshcd_toggle_vreg(hba->dev, hba->vreg_info.vcc, false);
out:
	वापस ret;
पूर्ण

अटल व्योम ufshcd_hba_vreg_set_lpm(काष्ठा ufs_hba *hba)
अणु
	अगर (ufshcd_is_link_off(hba) || ufshcd_can_aggressive_pc(hba))
		ufshcd_setup_hba_vreg(hba, false);
पूर्ण

अटल व्योम ufshcd_hba_vreg_set_hpm(काष्ठा ufs_hba *hba)
अणु
	अगर (ufshcd_is_link_off(hba) || ufshcd_can_aggressive_pc(hba))
		ufshcd_setup_hba_vreg(hba, true);
पूर्ण

/**
 * ufshcd_suspend - helper function क्रम suspend operations
 * @hba: per adapter instance
 * @pm_op: desired low घातer operation type
 *
 * This function will try to put the UFS device and link पूर्णांकo low घातer
 * mode based on the "rpm_lvl" (Runसमय PM level) or "spm_lvl"
 * (System PM level).
 *
 * If this function is called during shutकरोwn, it will make sure that
 * both UFS device and UFS link is घातered off.
 *
 * NOTE: UFS device & link must be active beक्रमe we enter in this function.
 *
 * Returns 0 क्रम success and non-zero क्रम failure
 */
अटल पूर्णांक ufshcd_suspend(काष्ठा ufs_hba *hba, क्रमागत ufs_pm_op pm_op)
अणु
	पूर्णांक ret = 0;
	पूर्णांक check_क्रम_bkops;
	क्रमागत ufs_pm_level pm_lvl;
	क्रमागत ufs_dev_pwr_mode req_dev_pwr_mode;
	क्रमागत uic_link_state req_link_state;

	hba->pm_op_in_progress = 1;
	अगर (!ufshcd_is_shutकरोwn_pm(pm_op)) अणु
		pm_lvl = ufshcd_is_runसमय_pm(pm_op) ?
			 hba->rpm_lvl : hba->spm_lvl;
		req_dev_pwr_mode = ufs_get_pm_lvl_to_dev_pwr_mode(pm_lvl);
		req_link_state = ufs_get_pm_lvl_to_link_pwr_state(pm_lvl);
	पूर्ण अन्यथा अणु
		req_dev_pwr_mode = UFS_POWERDOWN_PWR_MODE;
		req_link_state = UIC_LINK_OFF_STATE;
	पूर्ण

	/*
	 * If we can't transition पूर्णांकo any of the low घातer modes
	 * just gate the घड़ीs.
	 */
	ufshcd_hold(hba, false);
	hba->clk_gating.is_suspended = true;

	अगर (ufshcd_is_clkscaling_supported(hba))
		ufshcd_clk_scaling_suspend(hba, true);

	अगर (req_dev_pwr_mode == UFS_ACTIVE_PWR_MODE &&
			req_link_state == UIC_LINK_ACTIVE_STATE) अणु
		जाओ disable_clks;
	पूर्ण

	अगर ((req_dev_pwr_mode == hba->curr_dev_pwr_mode) &&
	    (req_link_state == hba->uic_link_state))
		जाओ enable_gating;

	/* UFS device & link must be active beक्रमe we enter in this function */
	अगर (!ufshcd_is_ufs_dev_active(hba) || !ufshcd_is_link_active(hba)) अणु
		ret = -EINVAL;
		जाओ enable_gating;
	पूर्ण

	अगर (ufshcd_is_runसमय_pm(pm_op)) अणु
		अगर (ufshcd_can_स्वतःbkops_during_suspend(hba)) अणु
			/*
			 * The device is idle with no requests in the queue,
			 * allow background operations अगर bkops status shows
			 * that perक्रमmance might be impacted.
			 */
			ret = ufshcd_urgent_bkops(hba);
			अगर (ret)
				जाओ enable_gating;
		पूर्ण अन्यथा अणु
			/* make sure that स्वतः bkops is disabled */
			ufshcd_disable_स्वतः_bkops(hba);
		पूर्ण
		/*
		 * If device needs to करो BKOP or WB buffer flush during
		 * Hibern8, keep device घातer mode as "active power mode"
		 * and VCC supply.
		 */
		hba->dev_info.b_rpm_dev_flush_capable =
			hba->स्वतः_bkops_enabled ||
			(((req_link_state == UIC_LINK_HIBERN8_STATE) ||
			((req_link_state == UIC_LINK_ACTIVE_STATE) &&
			ufshcd_is_स्वतः_hibern8_enabled(hba))) &&
			ufshcd_wb_need_flush(hba));
	पूर्ण

	flush_work(&hba->eeh_work);

	अगर (req_dev_pwr_mode != hba->curr_dev_pwr_mode) अणु
		अगर (!ufshcd_is_runसमय_pm(pm_op))
			/* ensure that bkops is disabled */
			ufshcd_disable_स्वतः_bkops(hba);

		अगर (!hba->dev_info.b_rpm_dev_flush_capable) अणु
			ret = ufshcd_set_dev_pwr_mode(hba, req_dev_pwr_mode);
			अगर (ret)
				जाओ enable_gating;
		पूर्ण
	पूर्ण

	/*
	 * In the हाल of DeepSleep, the device is expected to reमुख्य घातered
	 * with the link off, so करो not check क्रम bkops.
	 */
	check_क्रम_bkops = !ufshcd_is_ufs_dev_deepsleep(hba);
	ret = ufshcd_link_state_transition(hba, req_link_state, check_क्रम_bkops);
	अगर (ret)
		जाओ set_dev_active;

disable_clks:
	/*
	 * Call venकरोr specअगरic suspend callback. As these callbacks may access
	 * venकरोr specअगरic host controller रेजिस्टर space call them beक्रमe the
	 * host घड़ीs are ON.
	 */
	ret = ufshcd_vops_suspend(hba, pm_op);
	अगर (ret)
		जाओ set_link_active;
	/*
	 * Disable the host irq as host controller as there won't be any
	 * host controller transaction expected till resume.
	 */
	ufshcd_disable_irq(hba);

	ufshcd_setup_घड़ीs(hba, false);

	अगर (ufshcd_is_clkgating_allowed(hba)) अणु
		hba->clk_gating.state = CLKS_OFF;
		trace_ufshcd_clk_gating(dev_name(hba->dev),
					hba->clk_gating.state);
	पूर्ण

	ufshcd_vreg_set_lpm(hba);

	/* Put the host controller in low घातer mode अगर possible */
	ufshcd_hba_vreg_set_lpm(hba);
	जाओ out;

set_link_active:
	ufshcd_vreg_set_hpm(hba);
	/*
	 * Device hardware reset is required to निकास DeepSleep. Also, क्रम
	 * DeepSleep, the link is off so host reset and restore will be करोne
	 * further below.
	 */
	अगर (ufshcd_is_ufs_dev_deepsleep(hba)) अणु
		ufshcd_device_reset(hba);
		WARN_ON(!ufshcd_is_link_off(hba));
	पूर्ण
	अगर (ufshcd_is_link_hibern8(hba) && !ufshcd_uic_hibern8_निकास(hba))
		ufshcd_set_link_active(hba);
	अन्यथा अगर (ufshcd_is_link_off(hba))
		ufshcd_host_reset_and_restore(hba);
set_dev_active:
	/* Can also get here needing to निकास DeepSleep */
	अगर (ufshcd_is_ufs_dev_deepsleep(hba)) अणु
		ufshcd_device_reset(hba);
		ufshcd_host_reset_and_restore(hba);
	पूर्ण
	अगर (!ufshcd_set_dev_pwr_mode(hba, UFS_ACTIVE_PWR_MODE))
		ufshcd_disable_स्वतः_bkops(hba);
enable_gating:
	अगर (ufshcd_is_clkscaling_supported(hba))
		ufshcd_clk_scaling_suspend(hba, false);

	hba->clk_gating.is_suspended = false;
	hba->dev_info.b_rpm_dev_flush_capable = false;
	ufshcd_clear_ua_wluns(hba);
	ufshcd_release(hba);
out:
	अगर (hba->dev_info.b_rpm_dev_flush_capable) अणु
		schedule_delayed_work(&hba->rpm_dev_flush_recheck_work,
			msecs_to_jअगरfies(RPM_DEV_FLUSH_RECHECK_WORK_DELAY_MS));
	पूर्ण

	hba->pm_op_in_progress = 0;

	अगर (ret)
		ufshcd_update_evt_hist(hba, UFS_EVT_SUSPEND_ERR, (u32)ret);
	वापस ret;
पूर्ण

/**
 * ufshcd_resume - helper function क्रम resume operations
 * @hba: per adapter instance
 * @pm_op: runसमय PM or प्रणाली PM
 *
 * This function basically brings the UFS device, UniPro link and controller
 * to active state.
 *
 * Returns 0 क्रम success and non-zero क्रम failure
 */
अटल पूर्णांक ufshcd_resume(काष्ठा ufs_hba *hba, क्रमागत ufs_pm_op pm_op)
अणु
	पूर्णांक ret;
	क्रमागत uic_link_state old_link_state;

	hba->pm_op_in_progress = 1;
	old_link_state = hba->uic_link_state;

	ufshcd_hba_vreg_set_hpm(hba);
	ret = ufshcd_vreg_set_hpm(hba);
	अगर (ret)
		जाओ out;

	/* Make sure घड़ीs are enabled beक्रमe accessing controller */
	ret = ufshcd_setup_घड़ीs(hba, true);
	अगर (ret)
		जाओ disable_vreg;

	/* enable the host irq as host controller would be active soon */
	ufshcd_enable_irq(hba);

	/*
	 * Call venकरोr specअगरic resume callback. As these callbacks may access
	 * venकरोr specअगरic host controller रेजिस्टर space call them when the
	 * host घड़ीs are ON.
	 */
	ret = ufshcd_vops_resume(hba, pm_op);
	अगर (ret)
		जाओ disable_irq_and_vops_clks;

	/* For DeepSleep, the only supported option is to have the link off */
	WARN_ON(ufshcd_is_ufs_dev_deepsleep(hba) && !ufshcd_is_link_off(hba));

	अगर (ufshcd_is_link_hibern8(hba)) अणु
		ret = ufshcd_uic_hibern8_निकास(hba);
		अगर (!ret) अणु
			ufshcd_set_link_active(hba);
		पूर्ण अन्यथा अणु
			dev_err(hba->dev, "%s: hibern8 exit failed %d\n",
					__func__, ret);
			जाओ venकरोr_suspend;
		पूर्ण
	पूर्ण अन्यथा अगर (ufshcd_is_link_off(hba)) अणु
		/*
		 * A full initialization of the host and the device is
		 * required since the link was put to off during suspend.
		 * Note, in the हाल of DeepSleep, the device will निकास
		 * DeepSleep due to device reset.
		 */
		ret = ufshcd_reset_and_restore(hba);
		/*
		 * ufshcd_reset_and_restore() should have alपढ़ोy
		 * set the link state as active
		 */
		अगर (ret || !ufshcd_is_link_active(hba))
			जाओ venकरोr_suspend;
	पूर्ण

	अगर (!ufshcd_is_ufs_dev_active(hba)) अणु
		ret = ufshcd_set_dev_pwr_mode(hba, UFS_ACTIVE_PWR_MODE);
		अगर (ret)
			जाओ set_old_link_state;
	पूर्ण

	अगर (ufshcd_keep_स्वतःbkops_enabled_except_suspend(hba))
		ufshcd_enable_स्वतः_bkops(hba);
	अन्यथा
		/*
		 * If BKOPs operations are urgently needed at this moment then
		 * keep स्वतः-bkops enabled or अन्यथा disable it.
		 */
		ufshcd_urgent_bkops(hba);

	अगर (hba->ee_usr_mask)
		ufshcd_ग_लिखो_ee_control(hba);

	hba->clk_gating.is_suspended = false;

	अगर (ufshcd_is_clkscaling_supported(hba))
		ufshcd_clk_scaling_suspend(hba, false);

	/* Enable Auto-Hibernate अगर configured */
	ufshcd_स्वतः_hibern8_enable(hba);

	अगर (hba->dev_info.b_rpm_dev_flush_capable) अणु
		hba->dev_info.b_rpm_dev_flush_capable = false;
		cancel_delayed_work(&hba->rpm_dev_flush_recheck_work);
	पूर्ण

	ufshcd_clear_ua_wluns(hba);

	/* Schedule घड़ी gating in हाल of no access to UFS device yet */
	ufshcd_release(hba);

	जाओ out;

set_old_link_state:
	ufshcd_link_state_transition(hba, old_link_state, 0);
venकरोr_suspend:
	ufshcd_vops_suspend(hba, pm_op);
disable_irq_and_vops_clks:
	ufshcd_disable_irq(hba);
	ufshcd_setup_घड़ीs(hba, false);
	अगर (ufshcd_is_clkgating_allowed(hba)) अणु
		hba->clk_gating.state = CLKS_OFF;
		trace_ufshcd_clk_gating(dev_name(hba->dev),
					hba->clk_gating.state);
	पूर्ण
disable_vreg:
	ufshcd_vreg_set_lpm(hba);
out:
	hba->pm_op_in_progress = 0;
	अगर (ret)
		ufshcd_update_evt_hist(hba, UFS_EVT_RESUME_ERR, (u32)ret);
	वापस ret;
पूर्ण

/**
 * ufshcd_प्रणाली_suspend - प्रणाली suspend routine
 * @hba: per adapter instance
 *
 * Check the description of ufshcd_suspend() function क्रम more details.
 *
 * Returns 0 क्रम success and non-zero क्रम failure
 */
पूर्णांक ufshcd_प्रणाली_suspend(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret = 0;
	kसमय_प्रकार start = kसमय_get();

	करोwn(&hba->host_sem);

	अगर (!hba->is_घातered)
		वापस 0;

	cancel_delayed_work_sync(&hba->rpm_dev_flush_recheck_work);

	अगर ((ufs_get_pm_lvl_to_dev_pwr_mode(hba->spm_lvl) ==
	     hba->curr_dev_pwr_mode) &&
	    (ufs_get_pm_lvl_to_link_pwr_state(hba->spm_lvl) ==
	     hba->uic_link_state) &&
	     pm_runसमय_suspended(hba->dev) &&
	     !hba->dev_info.b_rpm_dev_flush_capable)
		जाओ out;

	अगर (pm_runसमय_suspended(hba->dev)) अणु
		/*
		 * UFS device and/or UFS link low घातer states during runसमय
		 * suspend seems to be dअगरferent than what is expected during
		 * प्रणाली suspend. Hence runसमय resume the devic & link and
		 * let the प्रणाली suspend low घातer states to take effect.
		 * TODO: If resume takes दीर्घer समय, we might have optimize
		 * it in future by not resuming everything अगर possible.
		 */
		ret = ufshcd_runसमय_resume(hba);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = ufshcd_suspend(hba, UFS_SYSTEM_PM);
out:
	trace_ufshcd_प्रणाली_suspend(dev_name(hba->dev), ret,
		kसमय_प्रकारo_us(kसमय_sub(kसमय_get(), start)),
		hba->curr_dev_pwr_mode, hba->uic_link_state);
	अगर (!ret)
		hba->is_sys_suspended = true;
	अन्यथा
		up(&hba->host_sem);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ufshcd_प्रणाली_suspend);

/**
 * ufshcd_प्रणाली_resume - प्रणाली resume routine
 * @hba: per adapter instance
 *
 * Returns 0 क्रम success and non-zero क्रम failure
 */

पूर्णांक ufshcd_प्रणाली_resume(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret = 0;
	kसमय_प्रकार start = kसमय_get();

	अगर (!hba->is_घातered || pm_runसमय_suspended(hba->dev))
		/*
		 * Let the runसमय resume take care of resuming
		 * अगर runसमय suspended.
		 */
		जाओ out;
	अन्यथा
		ret = ufshcd_resume(hba, UFS_SYSTEM_PM);
out:
	trace_ufshcd_प्रणाली_resume(dev_name(hba->dev), ret,
		kसमय_प्रकारo_us(kसमय_sub(kसमय_get(), start)),
		hba->curr_dev_pwr_mode, hba->uic_link_state);
	अगर (!ret)
		hba->is_sys_suspended = false;
	up(&hba->host_sem);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ufshcd_प्रणाली_resume);

/**
 * ufshcd_runसमय_suspend - runसमय suspend routine
 * @hba: per adapter instance
 *
 * Check the description of ufshcd_suspend() function क्रम more details.
 *
 * Returns 0 क्रम success and non-zero क्रम failure
 */
पूर्णांक ufshcd_runसमय_suspend(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret = 0;
	kसमय_प्रकार start = kसमय_get();

	अगर (!hba->is_घातered)
		जाओ out;
	अन्यथा
		ret = ufshcd_suspend(hba, UFS_RUNTIME_PM);
out:
	trace_ufshcd_runसमय_suspend(dev_name(hba->dev), ret,
		kसमय_प्रकारo_us(kसमय_sub(kसमय_get(), start)),
		hba->curr_dev_pwr_mode, hba->uic_link_state);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ufshcd_runसमय_suspend);

/**
 * ufshcd_runसमय_resume - runसमय resume routine
 * @hba: per adapter instance
 *
 * This function basically brings the UFS device, UniPro link and controller
 * to active state. Following operations are करोne in this function:
 *
 * 1. Turn on all the controller related घड़ीs
 * 2. Bring the UniPro link out of Hibernate state
 * 3. If UFS device is in sleep state, turn ON VCC rail and bring the UFS device
 *    to active state.
 * 4. If स्वतः-bkops is enabled on the device, disable it.
 *
 * So following would be the possible घातer state after this function वापस
 * successfully:
 *	S1: UFS device in Active state with VCC rail ON
 *	    UniPro link in Active state
 *	    All the UFS/UniPro controller घड़ीs are ON
 *
 * Returns 0 क्रम success and non-zero क्रम failure
 */
पूर्णांक ufshcd_runसमय_resume(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret = 0;
	kसमय_प्रकार start = kसमय_get();

	अगर (!hba->is_घातered)
		जाओ out;
	अन्यथा
		ret = ufshcd_resume(hba, UFS_RUNTIME_PM);
out:
	trace_ufshcd_runसमय_resume(dev_name(hba->dev), ret,
		kसमय_प्रकारo_us(kसमय_sub(kसमय_get(), start)),
		hba->curr_dev_pwr_mode, hba->uic_link_state);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ufshcd_runसमय_resume);

पूर्णांक ufshcd_runसमय_idle(काष्ठा ufs_hba *hba)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ufshcd_runसमय_idle);

/**
 * ufshcd_shutकरोwn - shutकरोwn routine
 * @hba: per adapter instance
 *
 * This function would घातer off both UFS device and UFS link.
 *
 * Returns 0 always to allow क्रमce shutकरोwn even in हाल of errors.
 */
पूर्णांक ufshcd_shutकरोwn(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret = 0;

	करोwn(&hba->host_sem);
	hba->shutting_करोwn = true;
	up(&hba->host_sem);

	अगर (!hba->is_घातered)
		जाओ out;

	अगर (ufshcd_is_ufs_dev_घातeroff(hba) && ufshcd_is_link_off(hba))
		जाओ out;

	pm_runसमय_get_sync(hba->dev);

	ret = ufshcd_suspend(hba, UFS_SHUTDOWN_PM);
out:
	अगर (ret)
		dev_err(hba->dev, "%s failed, err %d\n", __func__, ret);
	hba->is_घातered = false;
	/* allow क्रमce shutकरोwn even in हाल of errors */
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ufshcd_shutकरोwn);

/**
 * ufshcd_हटाओ - de-allocate SCSI host and host memory space
 *		data काष्ठाure memory
 * @hba: per adapter instance
 */
व्योम ufshcd_हटाओ(काष्ठा ufs_hba *hba)
अणु
	ufs_bsg_हटाओ(hba);
	ufs_sysfs_हटाओ_nodes(hba->dev);
	blk_cleanup_queue(hba->पंचांगf_queue);
	blk_mq_मुक्त_tag_set(&hba->पंचांगf_tag_set);
	blk_cleanup_queue(hba->cmd_queue);
	scsi_हटाओ_host(hba->host);
	/* disable पूर्णांकerrupts */
	ufshcd_disable_पूर्णांकr(hba, hba->पूर्णांकr_mask);
	ufshcd_hba_stop(hba);
	ufshcd_hba_निकास(hba);
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_हटाओ);

/**
 * ufshcd_dealloc_host - deallocate Host Bus Adapter (HBA)
 * @hba: poपूर्णांकer to Host Bus Adapter (HBA)
 */
व्योम ufshcd_dealloc_host(काष्ठा ufs_hba *hba)
अणु
	scsi_host_put(hba->host);
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_dealloc_host);

/**
 * ufshcd_set_dma_mask - Set dma mask based on the controller
 *			 addressing capability
 * @hba: per adapter instance
 *
 * Returns 0 क्रम success, non-zero क्रम failure
 */
अटल पूर्णांक ufshcd_set_dma_mask(काष्ठा ufs_hba *hba)
अणु
	अगर (hba->capabilities & MASK_64_ADDRESSING_SUPPORT) अणु
		अगर (!dma_set_mask_and_coherent(hba->dev, DMA_BIT_MASK(64)))
			वापस 0;
	पूर्ण
	वापस dma_set_mask_and_coherent(hba->dev, DMA_BIT_MASK(32));
पूर्ण

/**
 * ufshcd_alloc_host - allocate Host Bus Adapter (HBA)
 * @dev: poपूर्णांकer to device handle
 * @hba_handle: driver निजी handle
 * Returns 0 on success, non-zero value on failure
 */
पूर्णांक ufshcd_alloc_host(काष्ठा device *dev, काष्ठा ufs_hba **hba_handle)
अणु
	काष्ठा Scsi_Host *host;
	काष्ठा ufs_hba *hba;
	पूर्णांक err = 0;

	अगर (!dev) अणु
		dev_err(dev,
		"Invalid memory reference for dev is NULL\n");
		err = -ENODEV;
		जाओ out_error;
	पूर्ण

	host = scsi_host_alloc(&ufshcd_driver_ढाँचा,
				माप(काष्ठा ufs_hba));
	अगर (!host) अणु
		dev_err(dev, "scsi_host_alloc failed\n");
		err = -ENOMEM;
		जाओ out_error;
	पूर्ण
	hba = shost_priv(host);
	hba->host = host;
	hba->dev = dev;
	*hba_handle = hba;
	hba->dev_ref_clk_freq = REF_CLK_FREQ_INVAL;

	INIT_LIST_HEAD(&hba->clk_list_head);

out_error:
	वापस err;
पूर्ण
EXPORT_SYMBOL(ufshcd_alloc_host);

/* This function exists because blk_mq_alloc_tag_set() requires this. */
अटल blk_status_t ufshcd_queue_पंचांगf(काष्ठा blk_mq_hw_ctx *hctx,
				     स्थिर काष्ठा blk_mq_queue_data *qd)
अणु
	WARN_ON_ONCE(true);
	वापस BLK_STS_NOTSUPP;
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops ufshcd_पंचांगf_ops = अणु
	.queue_rq = ufshcd_queue_पंचांगf,
पूर्ण;

/**
 * ufshcd_init - Driver initialization routine
 * @hba: per-adapter instance
 * @mmio_base: base रेजिस्टर address
 * @irq: Interrupt line of device
 * Returns 0 on success, non-zero value on failure
 */
पूर्णांक ufshcd_init(काष्ठा ufs_hba *hba, व्योम __iomem *mmio_base, अचिन्हित पूर्णांक irq)
अणु
	पूर्णांक err;
	काष्ठा Scsi_Host *host = hba->host;
	काष्ठा device *dev = hba->dev;
	अक्षर eh_wq_name[माप("ufs_eh_wq_00")];

	अगर (!mmio_base) अणु
		dev_err(hba->dev,
		"Invalid memory reference for mmio_base is NULL\n");
		err = -ENODEV;
		जाओ out_error;
	पूर्ण

	hba->mmio_base = mmio_base;
	hba->irq = irq;
	hba->vps = &ufs_hba_vps;

	err = ufshcd_hba_init(hba);
	अगर (err)
		जाओ out_error;

	/* Read capabilities रेजिस्टरs */
	err = ufshcd_hba_capabilities(hba);
	अगर (err)
		जाओ out_disable;

	/* Get UFS version supported by the controller */
	hba->ufs_version = ufshcd_get_ufs_version(hba);

	/* Get Interrupt bit mask per version */
	hba->पूर्णांकr_mask = ufshcd_get_पूर्णांकr_mask(hba);

	err = ufshcd_set_dma_mask(hba);
	अगर (err) अणु
		dev_err(hba->dev, "set dma mask failed\n");
		जाओ out_disable;
	पूर्ण

	/* Allocate memory क्रम host memory space */
	err = ufshcd_memory_alloc(hba);
	अगर (err) अणु
		dev_err(hba->dev, "Memory allocation failed\n");
		जाओ out_disable;
	पूर्ण

	/* Configure LRB */
	ufshcd_host_memory_configure(hba);

	host->can_queue = hba->nutrs;
	host->cmd_per_lun = hba->nutrs;
	host->max_id = UFSHCD_MAX_ID;
	host->max_lun = UFS_MAX_LUNS;
	host->max_channel = UFSHCD_MAX_CHANNEL;
	host->unique_id = host->host_no;
	host->max_cmd_len = UFS_CDB_SIZE;

	hba->max_pwr_info.is_valid = false;

	/* Initialize work queues */
	snम_लिखो(eh_wq_name, माप(eh_wq_name), "ufs_eh_wq_%d",
		 hba->host->host_no);
	hba->eh_wq = create_singlethपढ़ो_workqueue(eh_wq_name);
	अगर (!hba->eh_wq) अणु
		dev_err(hba->dev, "%s: failed to create eh workqueue\n",
				__func__);
		err = -ENOMEM;
		जाओ out_disable;
	पूर्ण
	INIT_WORK(&hba->eh_work, ufshcd_err_handler);
	INIT_WORK(&hba->eeh_work, ufshcd_exception_event_handler);

	sema_init(&hba->host_sem, 1);

	/* Initialize UIC command mutex */
	mutex_init(&hba->uic_cmd_mutex);

	/* Initialize mutex क्रम device management commands */
	mutex_init(&hba->dev_cmd.lock);

	/* Initialize mutex क्रम exception event control */
	mutex_init(&hba->ee_ctrl_mutex);

	init_rwsem(&hba->clk_scaling_lock);

	ufshcd_init_clk_gating(hba);

	ufshcd_init_clk_scaling(hba);

	/*
	 * In order to aव्योम any spurious पूर्णांकerrupt immediately after
	 * रेजिस्टरing UFS controller पूर्णांकerrupt handler, clear any pending UFS
	 * पूर्णांकerrupt status and disable all the UFS पूर्णांकerrupts.
	 */
	ufshcd_ग_लिखोl(hba, ufshcd_पढ़ोl(hba, REG_INTERRUPT_STATUS),
		      REG_INTERRUPT_STATUS);
	ufshcd_ग_लिखोl(hba, 0, REG_INTERRUPT_ENABLE);
	/*
	 * Make sure that UFS पूर्णांकerrupts are disabled and any pending पूर्णांकerrupt
	 * status is cleared beक्रमe रेजिस्टरing UFS पूर्णांकerrupt handler.
	 */
	mb();

	/* IRQ registration */
	err = devm_request_irq(dev, irq, ufshcd_पूर्णांकr, IRQF_SHARED, UFSHCD, hba);
	अगर (err) अणु
		dev_err(hba->dev, "request irq failed\n");
		जाओ out_disable;
	पूर्ण अन्यथा अणु
		hba->is_irq_enabled = true;
	पूर्ण

	err = scsi_add_host(host, hba->dev);
	अगर (err) अणु
		dev_err(hba->dev, "scsi_add_host failed\n");
		जाओ out_disable;
	पूर्ण

	hba->cmd_queue = blk_mq_init_queue(&hba->host->tag_set);
	अगर (IS_ERR(hba->cmd_queue)) अणु
		err = PTR_ERR(hba->cmd_queue);
		जाओ out_हटाओ_scsi_host;
	पूर्ण

	hba->पंचांगf_tag_set = (काष्ठा blk_mq_tag_set) अणु
		.nr_hw_queues	= 1,
		.queue_depth	= hba->nuपंचांगrs,
		.ops		= &ufshcd_पंचांगf_ops,
		.flags		= BLK_MQ_F_NO_SCHED,
	पूर्ण;
	err = blk_mq_alloc_tag_set(&hba->पंचांगf_tag_set);
	अगर (err < 0)
		जाओ मुक्त_cmd_queue;
	hba->पंचांगf_queue = blk_mq_init_queue(&hba->पंचांगf_tag_set);
	अगर (IS_ERR(hba->पंचांगf_queue)) अणु
		err = PTR_ERR(hba->पंचांगf_queue);
		जाओ मुक्त_पंचांगf_tag_set;
	पूर्ण

	/* Reset the attached device */
	ufshcd_device_reset(hba);

	ufshcd_init_crypto(hba);

	/* Host controller enable */
	err = ufshcd_hba_enable(hba);
	अगर (err) अणु
		dev_err(hba->dev, "Host controller enable failed\n");
		ufshcd_prपूर्णांक_evt_hist(hba);
		ufshcd_prपूर्णांक_host_state(hba);
		जाओ मुक्त_पंचांगf_queue;
	पूर्ण

	/*
	 * Set the शेष घातer management level क्रम runसमय and प्रणाली PM.
	 * Default घातer saving mode is to keep UFS link in Hibern8 state
	 * and UFS device in sleep state.
	 */
	hba->rpm_lvl = ufs_get_desired_pm_lvl_क्रम_dev_link_state(
						UFS_SLEEP_PWR_MODE,
						UIC_LINK_HIBERN8_STATE);
	hba->spm_lvl = ufs_get_desired_pm_lvl_क्रम_dev_link_state(
						UFS_SLEEP_PWR_MODE,
						UIC_LINK_HIBERN8_STATE);

	INIT_DELAYED_WORK(&hba->rpm_dev_flush_recheck_work,
			  ufshcd_rpm_dev_flush_recheck_work);

	/* Set the शेष स्वतः-hiberate idle समयr value to 150 ms */
	अगर (ufshcd_is_स्वतः_hibern8_supported(hba) && !hba->ahit) अणु
		hba->ahit = FIELD_PREP(UFSHCI_AHIBERN8_TIMER_MASK, 150) |
			    FIELD_PREP(UFSHCI_AHIBERN8_SCALE_MASK, 3);
	पूर्ण

	/* Hold स्वतः suspend until async scan completes */
	pm_runसमय_get_sync(dev);
	atomic_set(&hba->scsi_block_reqs_cnt, 0);
	/*
	 * We are assuming that device wasn't put in sleep/घातer-करोwn
	 * state exclusively during the boot stage beक्रमe kernel.
	 * This assumption helps aव्योम करोing link startup twice during
	 * ufshcd_probe_hba().
	 */
	ufshcd_set_ufs_dev_active(hba);

	async_schedule(ufshcd_async_scan, hba);
	ufs_sysfs_add_nodes(hba->dev);

	वापस 0;

मुक्त_पंचांगf_queue:
	blk_cleanup_queue(hba->पंचांगf_queue);
मुक्त_पंचांगf_tag_set:
	blk_mq_मुक्त_tag_set(&hba->पंचांगf_tag_set);
मुक्त_cmd_queue:
	blk_cleanup_queue(hba->cmd_queue);
out_हटाओ_scsi_host:
	scsi_हटाओ_host(hba->host);
out_disable:
	hba->is_irq_enabled = false;
	ufshcd_hba_निकास(hba);
out_error:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_init);

अटल पूर्णांक __init ufshcd_core_init(व्योम)
अणु
	ufs_debugfs_init();
	वापस 0;
पूर्ण

अटल व्योम __निकास ufshcd_core_निकास(व्योम)
अणु
	ufs_debugfs_निकास();
पूर्ण

module_init(ufshcd_core_init);
module_निकास(ufshcd_core_निकास);

MODULE_AUTHOR("Santosh Yaragnavi <santosh.sy@samsung.com>");
MODULE_AUTHOR("Vinayak Holikatti <h.vinayak@samsung.com>");
MODULE_DESCRIPTION("Generic UFS host controller driver Core");
MODULE_LICENSE("GPL");
MODULE_VERSION(UFSHCD_DRIVER_VERSION);
