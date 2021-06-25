<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2005-2014, 2018-2019 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2015-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_dbg_h__
#घोषणा __iwl_fw_dbg_h__
#समावेश <linux/workqueue.h>
#समावेश <net/cfg80211.h>
#समावेश "runtime.h"
#समावेश "iwl-prph.h"
#समावेश "iwl-io.h"
#समावेश "file.h"
#समावेश "error-dump.h"
#समावेश "api/commands.h"
#समावेश "api/dbg-tlv.h"
#समावेश "api/alive.h"

/**
 * काष्ठा iwl_fw_dump_desc - describes the dump
 * @len: length of trig_desc->data
 * @trig_desc: the description of the dump
 */
काष्ठा iwl_fw_dump_desc अणु
	माप_प्रकार len;
	/* must be last */
	काष्ठा iwl_fw_error_dump_trigger_desc trig_desc;
पूर्ण;

/**
 * काष्ठा iwl_fw_dbg_params - रेजिस्टर values to restore
 * @in_sample: DBGC_IN_SAMPLE value
 * @out_ctrl: DBGC_OUT_CTRL value
 */
काष्ठा iwl_fw_dbg_params अणु
	u32 in_sample;
	u32 out_ctrl;
पूर्ण;

बाह्य स्थिर काष्ठा iwl_fw_dump_desc iwl_dump_desc_निश्चित;

पूर्णांक iwl_fw_dbg_collect_desc(काष्ठा iwl_fw_runसमय *fwrt,
			    स्थिर काष्ठा iwl_fw_dump_desc *desc,
			    bool monitor_only, अचिन्हित पूर्णांक delay);
पूर्णांक iwl_fw_dbg_error_collect(काष्ठा iwl_fw_runसमय *fwrt,
			     क्रमागत iwl_fw_dbg_trigger trig_type);
पूर्णांक iwl_fw_dbg_ini_collect(काष्ठा iwl_fw_runसमय *fwrt,
			   काष्ठा iwl_fwrt_dump_data *dump_data);
पूर्णांक iwl_fw_dbg_collect(काष्ठा iwl_fw_runसमय *fwrt,
		       क्रमागत iwl_fw_dbg_trigger trig, स्थिर अक्षर *str,
		       माप_प्रकार len, काष्ठा iwl_fw_dbg_trigger_tlv *trigger);
पूर्णांक iwl_fw_dbg_collect_trig(काष्ठा iwl_fw_runसमय *fwrt,
			    काष्ठा iwl_fw_dbg_trigger_tlv *trigger,
			    स्थिर अक्षर *fmt, ...) __म_लिखो(3, 4);
पूर्णांक iwl_fw_start_dbg_conf(काष्ठा iwl_fw_runसमय *fwrt, u8 id);

#घोषणा iwl_fw_dbg_trigger_enabled(fw, id) (अणु			\
	व्योम *__dbg_trigger = (fw)->dbg.trigger_tlv[(id)];	\
	unlikely(__dbg_trigger);				\
पूर्ण)

अटल अंतरभूत काष्ठा iwl_fw_dbg_trigger_tlv*
_iwl_fw_dbg_get_trigger(स्थिर काष्ठा iwl_fw *fw, क्रमागत iwl_fw_dbg_trigger id)
अणु
	वापस fw->dbg.trigger_tlv[id];
पूर्ण

#घोषणा iwl_fw_dbg_get_trigger(fw, id) (अणु			\
	BUILD_BUG_ON(!__builtin_स्थिरant_p(id));		\
	BUILD_BUG_ON((id) >= FW_DBG_TRIGGER_MAX);		\
	_iwl_fw_dbg_get_trigger((fw), (id));			\
पूर्ण)

अटल अंतरभूत bool
iwl_fw_dbg_trigger_vअगर_match(काष्ठा iwl_fw_dbg_trigger_tlv *trig,
			     काष्ठा wireless_dev *wdev)
अणु
	u32 trig_vअगर = le32_to_cpu(trig->vअगर_type);

	वापस trig_vअगर == IWL_FW_DBG_CONF_VIF_ANY ||
	       wdev->अगरtype == trig_vअगर;
पूर्ण

अटल अंतरभूत bool
iwl_fw_dbg_trigger_stop_conf_match(काष्ठा iwl_fw_runसमय *fwrt,
				   काष्ठा iwl_fw_dbg_trigger_tlv *trig)
अणु
	वापस ((trig->mode & IWL_FW_DBG_TRIGGER_STOP) &&
		(fwrt->dump.conf == FW_DBG_INVALID ||
		(BIT(fwrt->dump.conf) & le32_to_cpu(trig->stop_conf_ids))));
पूर्ण

अटल अंतरभूत bool
iwl_fw_dbg_no_trig_winकरोw(काष्ठा iwl_fw_runसमय *fwrt, u32 id, u32 dis_usec)
अणु
	अचिन्हित दीर्घ wind_jअगरf = usecs_to_jअगरfies(dis_usec);

	/* If this is the first event checked, jump to update start ts */
	अगर (fwrt->dump.non_collect_ts_start[id] &&
	    (समय_after(fwrt->dump.non_collect_ts_start[id] + wind_jअगरf,
			jअगरfies)))
		वापस true;

	fwrt->dump.non_collect_ts_start[id] = jअगरfies;
	वापस false;
पूर्ण

अटल अंतरभूत bool
iwl_fw_dbg_trigger_check_stop(काष्ठा iwl_fw_runसमय *fwrt,
			      काष्ठा wireless_dev *wdev,
			      काष्ठा iwl_fw_dbg_trigger_tlv *trig)
अणु
	u32 usec = le16_to_cpu(trig->trig_dis_ms) * USEC_PER_MSEC;

	अगर (wdev && !iwl_fw_dbg_trigger_vअगर_match(trig, wdev))
		वापस false;

	अगर (iwl_fw_dbg_no_trig_winकरोw(fwrt, le32_to_cpu(trig->id), usec)) अणु
		IWL_WARN(fwrt, "Trigger %d occurred while no-collect window.\n",
			 trig->id);
		वापस false;
	पूर्ण

	वापस iwl_fw_dbg_trigger_stop_conf_match(fwrt, trig);
पूर्ण

अटल अंतरभूत काष्ठा iwl_fw_dbg_trigger_tlv*
_iwl_fw_dbg_trigger_on(काष्ठा iwl_fw_runसमय *fwrt,
		       काष्ठा wireless_dev *wdev,
		       स्थिर क्रमागत iwl_fw_dbg_trigger id)
अणु
	काष्ठा iwl_fw_dbg_trigger_tlv *trig;

	अगर (iwl_trans_dbg_ini_valid(fwrt->trans))
		वापस शून्य;

	अगर (!iwl_fw_dbg_trigger_enabled(fwrt->fw, id))
		वापस शून्य;

	trig = _iwl_fw_dbg_get_trigger(fwrt->fw, id);

	अगर (!iwl_fw_dbg_trigger_check_stop(fwrt, wdev, trig))
		वापस शून्य;

	वापस trig;
पूर्ण

#घोषणा iwl_fw_dbg_trigger_on(fwrt, wdev, id) (अणु		\
	BUILD_BUG_ON(!__builtin_स्थिरant_p(id));		\
	BUILD_BUG_ON((id) >= FW_DBG_TRIGGER_MAX);		\
	_iwl_fw_dbg_trigger_on((fwrt), (wdev), (id));		\
पूर्ण)

अटल अंतरभूत व्योम
_iwl_fw_dbg_trigger_simple_stop(काष्ठा iwl_fw_runसमय *fwrt,
				काष्ठा wireless_dev *wdev,
				काष्ठा iwl_fw_dbg_trigger_tlv *trigger)
अणु
	अगर (!trigger)
		वापस;

	अगर (!iwl_fw_dbg_trigger_check_stop(fwrt, wdev, trigger))
		वापस;

	iwl_fw_dbg_collect_trig(fwrt, trigger, शून्य);
पूर्ण

#घोषणा iwl_fw_dbg_trigger_simple_stop(fwrt, wdev, trig)	\
	_iwl_fw_dbg_trigger_simple_stop((fwrt), (wdev),		\
					iwl_fw_dbg_get_trigger((fwrt)->fw,\
							       (trig)))
व्योम iwl_fw_dbg_stop_restart_recording(काष्ठा iwl_fw_runसमय *fwrt,
				       काष्ठा iwl_fw_dbg_params *params,
				       bool stop);

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
अटल अंतरभूत व्योम iwl_fw_set_dbg_rec_on(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	अगर (fwrt->cur_fw_img == IWL_UCODE_REGULAR &&
	    (fwrt->fw->dbg.dest_tlv ||
	     fwrt->trans->dbg.ini_dest != IWL_FW_INI_LOCATION_INVALID))
		fwrt->trans->dbg.rec_on = true;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम iwl_fw_dump_conf_clear(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	fwrt->dump.conf = FW_DBG_INVALID;
पूर्ण

व्योम iwl_fw_error_dump_wk(काष्ठा work_काष्ठा *work);

अटल अंतरभूत bool iwl_fw_dbg_type_on(काष्ठा iwl_fw_runसमय *fwrt, u32 type)
अणु
	वापस (fwrt->fw->dbg.dump_mask & BIT(type));
पूर्ण

अटल अंतरभूत bool iwl_fw_dbg_is_d3_debug_enabled(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	वापस fw_has_capa(&fwrt->fw->ucode_capa,
			   IWL_UCODE_TLV_CAPA_D3_DEBUG) &&
		fwrt->trans->cfg->d3_debug_data_length && fwrt->ops &&
		fwrt->ops->d3_debug_enable &&
		fwrt->ops->d3_debug_enable(fwrt->ops_ctx) &&
		iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_D3_DEBUG_DATA);
पूर्ण

अटल अंतरभूत bool iwl_fw_dbg_is_paging_enabled(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	वापस iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_PAGING) &&
		!fwrt->trans->trans_cfg->gen2 &&
		fwrt->cur_fw_img < IWL_UCODE_TYPE_MAX &&
		fwrt->fw->img[fwrt->cur_fw_img].paging_mem_size &&
		fwrt->fw_paging_db[0].fw_paging_block;
पूर्ण

व्योम iwl_fw_dbg_पढ़ो_d3_debug_data(काष्ठा iwl_fw_runसमय *fwrt);

अटल अंतरभूत व्योम iwl_fw_flush_dumps(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	पूर्णांक i;

	iwl_dbg_tlv_del_समयrs(fwrt->trans);
	क्रम (i = 0; i < IWL_FW_RUNTIME_DUMP_WK_NUM; i++)
		flush_delayed_work(&fwrt->dump.wks[i].wk);
पूर्ण

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
अटल अंतरभूत व्योम iwl_fw_cancel_बारtamp(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	fwrt->बारtamp.delay = 0;
	cancel_delayed_work_sync(&fwrt->बारtamp.wk);
पूर्ण

व्योम iwl_fw_trigger_बारtamp(काष्ठा iwl_fw_runसमय *fwrt, u32 delay);

अटल अंतरभूत व्योम iwl_fw_suspend_बारtamp(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	cancel_delayed_work_sync(&fwrt->बारtamp.wk);
पूर्ण

अटल अंतरभूत व्योम iwl_fw_resume_बारtamp(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	अगर (!fwrt->बारtamp.delay)
		वापस;

	schedule_delayed_work(&fwrt->बारtamp.wk,
			      round_jअगरfies_relative(fwrt->बारtamp.delay));
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम iwl_fw_cancel_बारtamp(काष्ठा iwl_fw_runसमय *fwrt) अणुपूर्ण

अटल अंतरभूत व्योम iwl_fw_trigger_बारtamp(काष्ठा iwl_fw_runसमय *fwrt,
					    u32 delay) अणुपूर्ण

अटल अंतरभूत व्योम iwl_fw_suspend_बारtamp(काष्ठा iwl_fw_runसमय *fwrt) अणुपूर्ण

अटल अंतरभूत व्योम iwl_fw_resume_बारtamp(काष्ठा iwl_fw_runसमय *fwrt) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_IWLWIFI_DEBUGFS */

व्योम iwl_fw_dbg_stop_sync(काष्ठा iwl_fw_runसमय *fwrt);

अटल अंतरभूत व्योम iwl_fw_lmac1_set_alive_err_table(काष्ठा iwl_trans *trans,
						    u32 lmac_error_event_table)
अणु
	अगर (!(trans->dbg.error_event_table_tlv_status &
	      IWL_ERROR_EVENT_TABLE_LMAC1) ||
	    WARN_ON(trans->dbg.lmac_error_event_table[0] !=
		    lmac_error_event_table))
		trans->dbg.lmac_error_event_table[0] = lmac_error_event_table;
पूर्ण

अटल अंतरभूत व्योम iwl_fw_umac_set_alive_err_table(काष्ठा iwl_trans *trans,
						   u32 umac_error_event_table)
अणु
	अगर (!(trans->dbg.error_event_table_tlv_status &
	      IWL_ERROR_EVENT_TABLE_UMAC) ||
	    WARN_ON(trans->dbg.umac_error_event_table !=
		    umac_error_event_table))
		trans->dbg.umac_error_event_table = umac_error_event_table;
पूर्ण

अटल अंतरभूत व्योम iwl_fw_error_collect(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	क्रमागत iwl_fw_ini_समय_poपूर्णांक tp_id;

	अगर (!iwl_trans_dbg_ini_valid(fwrt->trans)) अणु
		iwl_fw_dbg_collect_desc(fwrt, &iwl_dump_desc_निश्चित, false, 0);
		वापस;
	पूर्ण

	अगर (fwrt->trans->dbg.hw_error) अणु
		tp_id = IWL_FW_INI_TIME_POINT_FW_HW_ERROR;
		fwrt->trans->dbg.hw_error = false;
	पूर्ण अन्यथा अणु
		tp_id = IWL_FW_INI_TIME_POINT_FW_ASSERT;
	पूर्ण

	iwl_dbg_tlv_समय_poपूर्णांक(fwrt, tp_id, शून्य);
पूर्ण

व्योम iwl_fw_error_prपूर्णांक_fseq_regs(काष्ठा iwl_fw_runसमय *fwrt);

अटल अंतरभूत व्योम iwl_fwrt_update_fw_versions(काष्ठा iwl_fw_runसमय *fwrt,
					       काष्ठा iwl_lmac_alive *lmac,
					       काष्ठा iwl_umac_alive *umac)
अणु
	अगर (lmac) अणु
		fwrt->dump.fw_ver.type = lmac->ver_type;
		fwrt->dump.fw_ver.subtype = lmac->ver_subtype;
		fwrt->dump.fw_ver.lmac_major = le32_to_cpu(lmac->ucode_major);
		fwrt->dump.fw_ver.lmac_minor = le32_to_cpu(lmac->ucode_minor);
	पूर्ण

	अगर (umac) अणु
		fwrt->dump.fw_ver.umac_major = le32_to_cpu(umac->umac_major);
		fwrt->dump.fw_ver.umac_minor = le32_to_cpu(umac->umac_minor);
	पूर्ण
पूर्ण
#पूर्ण_अगर  /* __iwl_fw_dbg_h__ */
