<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2017 Broadcom Limited
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <net/devlink.h>
#समावेश "bnxt_hsi.h"
#समावेश "bnxt.h"
#समावेश "bnxt_vfr.h"
#समावेश "bnxt_devlink.h"
#समावेश "bnxt_ethtool.h"

अटल पूर्णांक
bnxt_dl_flash_update(काष्ठा devlink *dl,
		     काष्ठा devlink_flash_update_params *params,
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा bnxt *bp = bnxt_get_bp_from_dl(dl);
	पूर्णांक rc;

	अगर (!BNXT_PF(bp)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "flash update not supported from a VF");
		वापस -EPERM;
	पूर्ण

	devlink_flash_update_status_notअगरy(dl, "Preparing to flash", शून्य, 0, 0);
	rc = bnxt_flash_package_from_fw_obj(bp->dev, params->fw, 0);
	अगर (!rc)
		devlink_flash_update_status_notअगरy(dl, "Flashing done", शून्य, 0, 0);
	अन्यथा
		devlink_flash_update_status_notअगरy(dl, "Flashing failed", शून्य, 0, 0);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_fw_reporter_diagnose(काष्ठा devlink_health_reporter *reporter,
				     काष्ठा devlink_fmsg *fmsg,
				     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा bnxt *bp = devlink_health_reporter_priv(reporter);
	u32 val;
	पूर्णांक rc;

	अगर (test_bit(BNXT_STATE_IN_FW_RESET, &bp->state))
		वापस 0;

	val = bnxt_fw_health_पढ़ोl(bp, BNXT_FW_HEALTH_REG);

	अगर (BNXT_FW_IS_BOOTING(val)) अणु
		rc = devlink_fmsg_string_pair_put(fmsg, "Description",
						  "Not yet completed initialization");
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अगर (BNXT_FW_IS_ERR(val)) अणु
		rc = devlink_fmsg_string_pair_put(fmsg, "Description",
						  "Encountered fatal error and cannot recover");
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (val >> 16) अणु
		rc = devlink_fmsg_u32_pair_put(fmsg, "Error code", val >> 16);
		अगर (rc)
			वापस rc;
	पूर्ण

	val = bnxt_fw_health_पढ़ोl(bp, BNXT_FW_RESET_CNT_REG);
	rc = devlink_fmsg_u32_pair_put(fmsg, "Reset count", val);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा devlink_health_reporter_ops bnxt_dl_fw_reporter_ops = अणु
	.name = "fw",
	.diagnose = bnxt_fw_reporter_diagnose,
पूर्ण;

अटल पूर्णांक bnxt_fw_reset_recover(काष्ठा devlink_health_reporter *reporter,
				 व्योम *priv_ctx,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा bnxt *bp = devlink_health_reporter_priv(reporter);

	अगर (!priv_ctx)
		वापस -EOPNOTSUPP;

	bnxt_fw_reset(bp);
	वापस -EINPROGRESS;
पूर्ण

अटल स्थिर
काष्ठा devlink_health_reporter_ops bnxt_dl_fw_reset_reporter_ops = अणु
	.name = "fw_reset",
	.recover = bnxt_fw_reset_recover,
पूर्ण;

अटल पूर्णांक bnxt_fw_fatal_recover(काष्ठा devlink_health_reporter *reporter,
				 व्योम *priv_ctx,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा bnxt *bp = devlink_health_reporter_priv(reporter);
	काष्ठा bnxt_fw_reporter_ctx *fw_reporter_ctx = priv_ctx;
	अचिन्हित दीर्घ event;

	अगर (!priv_ctx)
		वापस -EOPNOTSUPP;

	bp->fw_health->fatal = true;
	event = fw_reporter_ctx->sp_event;
	अगर (event == BNXT_FW_RESET_NOTIFY_SP_EVENT)
		bnxt_fw_reset(bp);
	अन्यथा अगर (event == BNXT_FW_EXCEPTION_SP_EVENT)
		bnxt_fw_exception(bp);

	वापस -EINPROGRESS;
पूर्ण

अटल स्थिर
काष्ठा devlink_health_reporter_ops bnxt_dl_fw_fatal_reporter_ops = अणु
	.name = "fw_fatal",
	.recover = bnxt_fw_fatal_recover,
पूर्ण;

व्योम bnxt_dl_fw_reporters_create(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_fw_health *health = bp->fw_health;

	अगर (!bp->dl || !health)
		वापस;

	अगर (!(bp->fw_cap & BNXT_FW_CAP_HOT_RESET) || health->fw_reset_reporter)
		जाओ err_recovery;

	health->fw_reset_reporter =
		devlink_health_reporter_create(bp->dl,
					       &bnxt_dl_fw_reset_reporter_ops,
					       0, bp);
	अगर (IS_ERR(health->fw_reset_reporter)) अणु
		netdev_warn(bp->dev, "Failed to create FW fatal health reporter, rc = %ld\n",
			    PTR_ERR(health->fw_reset_reporter));
		health->fw_reset_reporter = शून्य;
		bp->fw_cap &= ~BNXT_FW_CAP_HOT_RESET;
	पूर्ण

err_recovery:
	अगर (!(bp->fw_cap & BNXT_FW_CAP_ERROR_RECOVERY))
		वापस;

	अगर (!health->fw_reporter) अणु
		health->fw_reporter =
			devlink_health_reporter_create(bp->dl,
						       &bnxt_dl_fw_reporter_ops,
						       0, bp);
		अगर (IS_ERR(health->fw_reporter)) अणु
			netdev_warn(bp->dev, "Failed to create FW health reporter, rc = %ld\n",
				    PTR_ERR(health->fw_reporter));
			health->fw_reporter = शून्य;
			bp->fw_cap &= ~BNXT_FW_CAP_ERROR_RECOVERY;
			वापस;
		पूर्ण
	पूर्ण

	अगर (health->fw_fatal_reporter)
		वापस;

	health->fw_fatal_reporter =
		devlink_health_reporter_create(bp->dl,
					       &bnxt_dl_fw_fatal_reporter_ops,
					       0, bp);
	अगर (IS_ERR(health->fw_fatal_reporter)) अणु
		netdev_warn(bp->dev, "Failed to create FW fatal health reporter, rc = %ld\n",
			    PTR_ERR(health->fw_fatal_reporter));
		health->fw_fatal_reporter = शून्य;
		bp->fw_cap &= ~BNXT_FW_CAP_ERROR_RECOVERY;
	पूर्ण
पूर्ण

व्योम bnxt_dl_fw_reporters_destroy(काष्ठा bnxt *bp, bool all)
अणु
	काष्ठा bnxt_fw_health *health = bp->fw_health;

	अगर (!bp->dl || !health)
		वापस;

	अगर ((all || !(bp->fw_cap & BNXT_FW_CAP_HOT_RESET)) &&
	    health->fw_reset_reporter) अणु
		devlink_health_reporter_destroy(health->fw_reset_reporter);
		health->fw_reset_reporter = शून्य;
	पूर्ण

	अगर ((bp->fw_cap & BNXT_FW_CAP_ERROR_RECOVERY) && !all)
		वापस;

	अगर (health->fw_reporter) अणु
		devlink_health_reporter_destroy(health->fw_reporter);
		health->fw_reporter = शून्य;
	पूर्ण

	अगर (health->fw_fatal_reporter) अणु
		devlink_health_reporter_destroy(health->fw_fatal_reporter);
		health->fw_fatal_reporter = शून्य;
	पूर्ण
पूर्ण

व्योम bnxt_devlink_health_report(काष्ठा bnxt *bp, अचिन्हित दीर्घ event)
अणु
	काष्ठा bnxt_fw_health *fw_health = bp->fw_health;
	काष्ठा bnxt_fw_reporter_ctx fw_reporter_ctx;

	fw_reporter_ctx.sp_event = event;
	चयन (event) अणु
	हाल BNXT_FW_RESET_NOTIFY_SP_EVENT:
		अगर (test_bit(BNXT_STATE_FW_FATAL_COND, &bp->state)) अणु
			अगर (!fw_health->fw_fatal_reporter)
				वापस;

			devlink_health_report(fw_health->fw_fatal_reporter,
					      "FW fatal async event received",
					      &fw_reporter_ctx);
			वापस;
		पूर्ण
		अगर (!fw_health->fw_reset_reporter)
			वापस;

		devlink_health_report(fw_health->fw_reset_reporter,
				      "FW non-fatal reset event received",
				      &fw_reporter_ctx);
		वापस;

	हाल BNXT_FW_EXCEPTION_SP_EVENT:
		अगर (!fw_health->fw_fatal_reporter)
			वापस;

		devlink_health_report(fw_health->fw_fatal_reporter,
				      "FW fatal error reported",
				      &fw_reporter_ctx);
		वापस;
	पूर्ण
पूर्ण

व्योम bnxt_dl_health_status_update(काष्ठा bnxt *bp, bool healthy)
अणु
	काष्ठा bnxt_fw_health *health = bp->fw_health;
	u8 state;

	अगर (healthy)
		state = DEVLINK_HEALTH_REPORTER_STATE_HEALTHY;
	अन्यथा
		state = DEVLINK_HEALTH_REPORTER_STATE_ERROR;

	अगर (health->fatal)
		devlink_health_reporter_state_update(health->fw_fatal_reporter,
						     state);
	अन्यथा
		devlink_health_reporter_state_update(health->fw_reset_reporter,
						     state);

	health->fatal = false;
पूर्ण

व्योम bnxt_dl_health_recovery_करोne(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_fw_health *hlth = bp->fw_health;

	अगर (hlth->fatal)
		devlink_health_reporter_recovery_करोne(hlth->fw_fatal_reporter);
	अन्यथा
		devlink_health_reporter_recovery_करोne(hlth->fw_reset_reporter);
पूर्ण

अटल पूर्णांक bnxt_dl_info_get(काष्ठा devlink *dl, काष्ठा devlink_info_req *req,
			    काष्ठा netlink_ext_ack *extack);

अटल स्थिर काष्ठा devlink_ops bnxt_dl_ops = अणु
#अगर_घोषित CONFIG_BNXT_SRIOV
	.eचयन_mode_set = bnxt_dl_eचयन_mode_set,
	.eचयन_mode_get = bnxt_dl_eचयन_mode_get,
#पूर्ण_अगर /* CONFIG_BNXT_SRIOV */
	.info_get	  = bnxt_dl_info_get,
	.flash_update	  = bnxt_dl_flash_update,
पूर्ण;

अटल स्थिर काष्ठा devlink_ops bnxt_vf_dl_ops;

क्रमागत bnxt_dl_param_id अणु
	BNXT_DEVLINK_PARAM_ID_BASE = DEVLINK_PARAM_GENERIC_ID_MAX,
	BNXT_DEVLINK_PARAM_ID_GRE_VER_CHECK,
पूर्ण;

अटल स्थिर काष्ठा bnxt_dl_nvm_param nvm_params[] = अणु
	अणुDEVLINK_PARAM_GENERIC_ID_ENABLE_SRIOV, NVM_OFF_ENABLE_SRIOV,
	 BNXT_NVM_SHARED_CFG, 1, 1पूर्ण,
	अणुDEVLINK_PARAM_GENERIC_ID_IGNORE_ARI, NVM_OFF_IGNORE_ARI,
	 BNXT_NVM_SHARED_CFG, 1, 1पूर्ण,
	अणुDEVLINK_PARAM_GENERIC_ID_MSIX_VEC_PER_PF_MAX,
	 NVM_OFF_MSIX_VEC_PER_PF_MAX, BNXT_NVM_SHARED_CFG, 10, 4पूर्ण,
	अणुDEVLINK_PARAM_GENERIC_ID_MSIX_VEC_PER_PF_MIN,
	 NVM_OFF_MSIX_VEC_PER_PF_MIN, BNXT_NVM_SHARED_CFG, 7, 4पूर्ण,
	अणुBNXT_DEVLINK_PARAM_ID_GRE_VER_CHECK, NVM_OFF_DIS_GRE_VER_CHECK,
	 BNXT_NVM_SHARED_CFG, 1, 1पूर्ण,
पूर्ण;

जोड़ bnxt_nvm_data अणु
	u8	val8;
	__le32	val32;
पूर्ण;

अटल व्योम bnxt_copy_to_nvm_data(जोड़ bnxt_nvm_data *dst,
				  जोड़ devlink_param_value *src,
				  पूर्णांक nvm_num_bits, पूर्णांक dl_num_bytes)
अणु
	u32 val32 = 0;

	अगर (nvm_num_bits == 1) अणु
		dst->val8 = src->vbool;
		वापस;
	पूर्ण
	अगर (dl_num_bytes == 4)
		val32 = src->vu32;
	अन्यथा अगर (dl_num_bytes == 2)
		val32 = (u32)src->vu16;
	अन्यथा अगर (dl_num_bytes == 1)
		val32 = (u32)src->vu8;
	dst->val32 = cpu_to_le32(val32);
पूर्ण

अटल व्योम bnxt_copy_from_nvm_data(जोड़ devlink_param_value *dst,
				    जोड़ bnxt_nvm_data *src,
				    पूर्णांक nvm_num_bits, पूर्णांक dl_num_bytes)
अणु
	u32 val32;

	अगर (nvm_num_bits == 1) अणु
		dst->vbool = src->val8;
		वापस;
	पूर्ण
	val32 = le32_to_cpu(src->val32);
	अगर (dl_num_bytes == 4)
		dst->vu32 = val32;
	अन्यथा अगर (dl_num_bytes == 2)
		dst->vu16 = (u16)val32;
	अन्यथा अगर (dl_num_bytes == 1)
		dst->vu8 = (u8)val32;
पूर्ण

अटल पूर्णांक bnxt_hwrm_get_nvm_cfg_ver(काष्ठा bnxt *bp,
				     जोड़ devlink_param_value *nvm_cfg_ver)
अणु
	काष्ठा hwrm_nvm_get_variable_input req = अणु0पूर्ण;
	जोड़ bnxt_nvm_data *data;
	dma_addr_t data_dma_addr;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_NVM_GET_VARIABLE, -1, -1);
	data = dma_alloc_coherent(&bp->pdev->dev, माप(*data),
				  &data_dma_addr, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	req.dest_data_addr = cpu_to_le64(data_dma_addr);
	req.data_len = cpu_to_le16(BNXT_NVM_CFG_VER_BITS);
	req.option_num = cpu_to_le16(NVM_OFF_NVM_CFG_VER);

	rc = hwrm_send_message_silent(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc)
		bnxt_copy_from_nvm_data(nvm_cfg_ver, data,
					BNXT_NVM_CFG_VER_BITS,
					BNXT_NVM_CFG_VER_BYTES);

	dma_मुक्त_coherent(&bp->pdev->dev, माप(*data), data, data_dma_addr);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_dl_info_put(काष्ठा bnxt *bp, काष्ठा devlink_info_req *req,
			    क्रमागत bnxt_dl_version_type type, स्थिर अक्षर *key,
			    अक्षर *buf)
अणु
	अगर (!म_माप(buf))
		वापस 0;

	अगर ((bp->flags & BNXT_FLAG_CHIP_P5) &&
	    (!म_भेद(key, DEVLINK_INFO_VERSION_GENERIC_FW_NCSI) ||
	     !म_भेद(key, DEVLINK_INFO_VERSION_GENERIC_FW_ROCE)))
		वापस 0;

	चयन (type) अणु
	हाल BNXT_VERSION_FIXED:
		वापस devlink_info_version_fixed_put(req, key, buf);
	हाल BNXT_VERSION_RUNNING:
		वापस devlink_info_version_running_put(req, key, buf);
	हाल BNXT_VERSION_STORED:
		वापस devlink_info_version_stored_put(req, key, buf);
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा HWRM_FW_VER_STR_LEN	16

अटल पूर्णांक bnxt_dl_info_get(काष्ठा devlink *dl, काष्ठा devlink_info_req *req,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा hwrm_nvm_get_dev_info_output nvm_dev_info;
	काष्ठा bnxt *bp = bnxt_get_bp_from_dl(dl);
	जोड़ devlink_param_value nvm_cfg_ver;
	काष्ठा hwrm_ver_get_output *ver_resp;
	अक्षर mgmt_ver[FW_VER_STR_LEN];
	अक्षर roce_ver[FW_VER_STR_LEN];
	अक्षर ncsi_ver[FW_VER_STR_LEN];
	अक्षर buf[32];
	पूर्णांक rc;

	rc = devlink_info_driver_name_put(req, DRV_MODULE_NAME);
	अगर (rc)
		वापस rc;

	अगर (BNXT_PF(bp) && (bp->flags & BNXT_FLAG_DSN_VALID)) अणु
		प्र_लिखो(buf, "%02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X",
			bp->dsn[7], bp->dsn[6], bp->dsn[5], bp->dsn[4],
			bp->dsn[3], bp->dsn[2], bp->dsn[1], bp->dsn[0]);
		rc = devlink_info_serial_number_put(req, buf);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (म_माप(bp->board_serialno)) अणु
		rc = devlink_info_board_serial_number_put(req, bp->board_serialno);
		अगर (rc)
			वापस rc;
	पूर्ण

	rc = bnxt_dl_info_put(bp, req, BNXT_VERSION_FIXED,
			      DEVLINK_INFO_VERSION_GENERIC_BOARD_ID,
			      bp->board_partno);
	अगर (rc)
		वापस rc;

	प्र_लिखो(buf, "%X", bp->chip_num);
	rc = bnxt_dl_info_put(bp, req, BNXT_VERSION_FIXED,
			      DEVLINK_INFO_VERSION_GENERIC_ASIC_ID, buf);
	अगर (rc)
		वापस rc;

	ver_resp = &bp->ver_resp;
	प्र_लिखो(buf, "%X", ver_resp->chip_rev);
	rc = bnxt_dl_info_put(bp, req, BNXT_VERSION_FIXED,
			      DEVLINK_INFO_VERSION_GENERIC_ASIC_REV, buf);
	अगर (rc)
		वापस rc;

	rc = bnxt_dl_info_put(bp, req, BNXT_VERSION_RUNNING,
			      DEVLINK_INFO_VERSION_GENERIC_FW_PSID,
			      bp->nvm_cfg_ver);
	अगर (rc)
		वापस rc;

	buf[0] = 0;
	म_जोड़न(buf, ver_resp->active_pkg_name, HWRM_FW_VER_STR_LEN);
	rc = bnxt_dl_info_put(bp, req, BNXT_VERSION_RUNNING,
			      DEVLINK_INFO_VERSION_GENERIC_FW, buf);
	अगर (rc)
		वापस rc;

	अगर (BNXT_PF(bp) && !bnxt_hwrm_get_nvm_cfg_ver(bp, &nvm_cfg_ver)) अणु
		u32 ver = nvm_cfg_ver.vu32;

		प्र_लिखो(buf, "%d.%d.%d", (ver >> 16) & 0xf, (ver >> 8) & 0xf,
			ver & 0xf);
		rc = bnxt_dl_info_put(bp, req, BNXT_VERSION_STORED,
				      DEVLINK_INFO_VERSION_GENERIC_FW_PSID,
				      buf);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (ver_resp->flags & VER_GET_RESP_FLAGS_EXT_VER_AVAIL) अणु
		snम_लिखो(mgmt_ver, FW_VER_STR_LEN, "%d.%d.%d.%d",
			 ver_resp->hwrm_fw_major, ver_resp->hwrm_fw_minor,
			 ver_resp->hwrm_fw_build, ver_resp->hwrm_fw_patch);

		snम_लिखो(ncsi_ver, FW_VER_STR_LEN, "%d.%d.%d.%d",
			 ver_resp->mgmt_fw_major, ver_resp->mgmt_fw_minor,
			 ver_resp->mgmt_fw_build, ver_resp->mgmt_fw_patch);

		snम_लिखो(roce_ver, FW_VER_STR_LEN, "%d.%d.%d.%d",
			 ver_resp->roce_fw_major, ver_resp->roce_fw_minor,
			 ver_resp->roce_fw_build, ver_resp->roce_fw_patch);
	पूर्ण अन्यथा अणु
		snम_लिखो(mgmt_ver, FW_VER_STR_LEN, "%d.%d.%d.%d",
			 ver_resp->hwrm_fw_maj_8b, ver_resp->hwrm_fw_min_8b,
			 ver_resp->hwrm_fw_bld_8b, ver_resp->hwrm_fw_rsvd_8b);

		snम_लिखो(ncsi_ver, FW_VER_STR_LEN, "%d.%d.%d.%d",
			 ver_resp->mgmt_fw_maj_8b, ver_resp->mgmt_fw_min_8b,
			 ver_resp->mgmt_fw_bld_8b, ver_resp->mgmt_fw_rsvd_8b);

		snम_लिखो(roce_ver, FW_VER_STR_LEN, "%d.%d.%d.%d",
			 ver_resp->roce_fw_maj_8b, ver_resp->roce_fw_min_8b,
			 ver_resp->roce_fw_bld_8b, ver_resp->roce_fw_rsvd_8b);
	पूर्ण
	rc = bnxt_dl_info_put(bp, req, BNXT_VERSION_RUNNING,
			      DEVLINK_INFO_VERSION_GENERIC_FW_MGMT, mgmt_ver);
	अगर (rc)
		वापस rc;

	rc = bnxt_dl_info_put(bp, req, BNXT_VERSION_RUNNING,
			      DEVLINK_INFO_VERSION_GENERIC_FW_MGMT_API,
			      bp->hwrm_ver_supp);
	अगर (rc)
		वापस rc;

	rc = bnxt_dl_info_put(bp, req, BNXT_VERSION_RUNNING,
			      DEVLINK_INFO_VERSION_GENERIC_FW_NCSI, ncsi_ver);
	अगर (rc)
		वापस rc;

	rc = bnxt_dl_info_put(bp, req, BNXT_VERSION_RUNNING,
			      DEVLINK_INFO_VERSION_GENERIC_FW_ROCE, roce_ver);
	अगर (rc)
		वापस rc;

	rc = bnxt_hwrm_nvm_get_dev_info(bp, &nvm_dev_info);
	अगर (rc ||
	    !(nvm_dev_info.flags & NVM_GET_DEV_INFO_RESP_FLAGS_FW_VER_VALID))
		वापस 0;

	buf[0] = 0;
	म_जोड़न(buf, nvm_dev_info.pkg_name, HWRM_FW_VER_STR_LEN);
	rc = bnxt_dl_info_put(bp, req, BNXT_VERSION_STORED,
			      DEVLINK_INFO_VERSION_GENERIC_FW, buf);
	अगर (rc)
		वापस rc;

	snम_लिखो(mgmt_ver, FW_VER_STR_LEN, "%d.%d.%d.%d",
		 nvm_dev_info.hwrm_fw_major, nvm_dev_info.hwrm_fw_minor,
		 nvm_dev_info.hwrm_fw_build, nvm_dev_info.hwrm_fw_patch);
	rc = bnxt_dl_info_put(bp, req, BNXT_VERSION_STORED,
			      DEVLINK_INFO_VERSION_GENERIC_FW_MGMT, mgmt_ver);
	अगर (rc)
		वापस rc;

	snम_लिखो(ncsi_ver, FW_VER_STR_LEN, "%d.%d.%d.%d",
		 nvm_dev_info.mgmt_fw_major, nvm_dev_info.mgmt_fw_minor,
		 nvm_dev_info.mgmt_fw_build, nvm_dev_info.mgmt_fw_patch);
	rc = bnxt_dl_info_put(bp, req, BNXT_VERSION_STORED,
			      DEVLINK_INFO_VERSION_GENERIC_FW_NCSI, ncsi_ver);
	अगर (rc)
		वापस rc;

	snम_लिखो(roce_ver, FW_VER_STR_LEN, "%d.%d.%d.%d",
		 nvm_dev_info.roce_fw_major, nvm_dev_info.roce_fw_minor,
		 nvm_dev_info.roce_fw_build, nvm_dev_info.roce_fw_patch);
	वापस bnxt_dl_info_put(bp, req, BNXT_VERSION_STORED,
				DEVLINK_INFO_VERSION_GENERIC_FW_ROCE, roce_ver);
पूर्ण

अटल पूर्णांक bnxt_hwrm_nvm_req(काष्ठा bnxt *bp, u32 param_id, व्योम *msg,
			     पूर्णांक msg_len, जोड़ devlink_param_value *val)
अणु
	काष्ठा hwrm_nvm_get_variable_input *req = msg;
	काष्ठा bnxt_dl_nvm_param nvm_param;
	जोड़ bnxt_nvm_data *data;
	dma_addr_t data_dma_addr;
	पूर्णांक idx = 0, rc, i;

	/* Get/Set NVM CFG parameter is supported only on PFs */
	अगर (BNXT_VF(bp))
		वापस -EPERM;

	क्रम (i = 0; i < ARRAY_SIZE(nvm_params); i++) अणु
		अगर (nvm_params[i].id == param_id) अणु
			nvm_param = nvm_params[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ARRAY_SIZE(nvm_params))
		वापस -EOPNOTSUPP;

	अगर (nvm_param.dir_type == BNXT_NVM_PORT_CFG)
		idx = bp->pf.port_id;
	अन्यथा अगर (nvm_param.dir_type == BNXT_NVM_FUNC_CFG)
		idx = bp->pf.fw_fid - BNXT_FIRST_PF_FID;

	data = dma_alloc_coherent(&bp->pdev->dev, माप(*data),
				  &data_dma_addr, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	req->dest_data_addr = cpu_to_le64(data_dma_addr);
	req->data_len = cpu_to_le16(nvm_param.nvm_num_bits);
	req->option_num = cpu_to_le16(nvm_param.offset);
	req->index_0 = cpu_to_le16(idx);
	अगर (idx)
		req->dimensions = cpu_to_le16(1);

	अगर (req->req_type == cpu_to_le16(HWRM_NVM_SET_VARIABLE)) अणु
		bnxt_copy_to_nvm_data(data, val, nvm_param.nvm_num_bits,
				      nvm_param.dl_num_bytes);
		rc = hwrm_send_message(bp, msg, msg_len, HWRM_CMD_TIMEOUT);
	पूर्ण अन्यथा अणु
		rc = hwrm_send_message_silent(bp, msg, msg_len,
					      HWRM_CMD_TIMEOUT);
		अगर (!rc) अणु
			bnxt_copy_from_nvm_data(val, data,
						nvm_param.nvm_num_bits,
						nvm_param.dl_num_bytes);
		पूर्ण अन्यथा अणु
			काष्ठा hwrm_err_output *resp = bp->hwrm_cmd_resp_addr;

			अगर (resp->cmd_err ==
				NVM_GET_VARIABLE_CMD_ERR_CODE_VAR_NOT_EXIST)
				rc = -EOPNOTSUPP;
		पूर्ण
	पूर्ण
	dma_मुक्त_coherent(&bp->pdev->dev, माप(*data), data, data_dma_addr);
	अगर (rc == -EACCES)
		netdev_err(bp->dev, "PF does not have admin privileges to modify NVM config\n");
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_dl_nvm_param_get(काष्ठा devlink *dl, u32 id,
				 काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा hwrm_nvm_get_variable_input req = अणु0पूर्ण;
	काष्ठा bnxt *bp = bnxt_get_bp_from_dl(dl);
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_NVM_GET_VARIABLE, -1, -1);
	rc = bnxt_hwrm_nvm_req(bp, id, &req, माप(req), &ctx->val);
	अगर (!rc)
		अगर (id == BNXT_DEVLINK_PARAM_ID_GRE_VER_CHECK)
			ctx->val.vbool = !ctx->val.vbool;

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_dl_nvm_param_set(काष्ठा devlink *dl, u32 id,
				 काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा hwrm_nvm_set_variable_input req = अणु0पूर्ण;
	काष्ठा bnxt *bp = bnxt_get_bp_from_dl(dl);

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_NVM_SET_VARIABLE, -1, -1);

	अगर (id == BNXT_DEVLINK_PARAM_ID_GRE_VER_CHECK)
		ctx->val.vbool = !ctx->val.vbool;

	वापस bnxt_hwrm_nvm_req(bp, id, &req, माप(req), &ctx->val);
पूर्ण

अटल पूर्णांक bnxt_dl_msix_validate(काष्ठा devlink *dl, u32 id,
				 जोड़ devlink_param_value val,
				 काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक max_val = -1;

	अगर (id == DEVLINK_PARAM_GENERIC_ID_MSIX_VEC_PER_PF_MAX)
		max_val = BNXT_MSIX_VEC_MAX;

	अगर (id == DEVLINK_PARAM_GENERIC_ID_MSIX_VEC_PER_PF_MIN)
		max_val = BNXT_MSIX_VEC_MIN_MAX;

	अगर (val.vu32 > max_val) अणु
		NL_SET_ERR_MSG_MOD(extack, "MSIX value is exceeding the range");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा devlink_param bnxt_dl_params[] = अणु
	DEVLINK_PARAM_GENERIC(ENABLE_SRIOV,
			      BIT(DEVLINK_PARAM_CMODE_PERMANENT),
			      bnxt_dl_nvm_param_get, bnxt_dl_nvm_param_set,
			      शून्य),
	DEVLINK_PARAM_GENERIC(IGNORE_ARI,
			      BIT(DEVLINK_PARAM_CMODE_PERMANENT),
			      bnxt_dl_nvm_param_get, bnxt_dl_nvm_param_set,
			      शून्य),
	DEVLINK_PARAM_GENERIC(MSIX_VEC_PER_PF_MAX,
			      BIT(DEVLINK_PARAM_CMODE_PERMANENT),
			      bnxt_dl_nvm_param_get, bnxt_dl_nvm_param_set,
			      bnxt_dl_msix_validate),
	DEVLINK_PARAM_GENERIC(MSIX_VEC_PER_PF_MIN,
			      BIT(DEVLINK_PARAM_CMODE_PERMANENT),
			      bnxt_dl_nvm_param_get, bnxt_dl_nvm_param_set,
			      bnxt_dl_msix_validate),
	DEVLINK_PARAM_DRIVER(BNXT_DEVLINK_PARAM_ID_GRE_VER_CHECK,
			     "gre_ver_check", DEVLINK_PARAM_TYPE_BOOL,
			     BIT(DEVLINK_PARAM_CMODE_PERMANENT),
			     bnxt_dl_nvm_param_get, bnxt_dl_nvm_param_set,
			     शून्य),
पूर्ण;

अटल स्थिर काष्ठा devlink_param bnxt_dl_port_params[] = अणु
पूर्ण;

अटल पूर्णांक bnxt_dl_params_रेजिस्टर(काष्ठा bnxt *bp)
अणु
	पूर्णांक rc;

	अगर (bp->hwrm_spec_code < 0x10600)
		वापस 0;

	rc = devlink_params_रेजिस्टर(bp->dl, bnxt_dl_params,
				     ARRAY_SIZE(bnxt_dl_params));
	अगर (rc) अणु
		netdev_warn(bp->dev, "devlink_params_register failed. rc=%d\n",
			    rc);
		वापस rc;
	पूर्ण
	rc = devlink_port_params_रेजिस्टर(&bp->dl_port, bnxt_dl_port_params,
					  ARRAY_SIZE(bnxt_dl_port_params));
	अगर (rc) अणु
		netdev_err(bp->dev, "devlink_port_params_register failed\n");
		devlink_params_unरेजिस्टर(bp->dl, bnxt_dl_params,
					  ARRAY_SIZE(bnxt_dl_params));
		वापस rc;
	पूर्ण
	devlink_params_publish(bp->dl);

	वापस 0;
पूर्ण

अटल व्योम bnxt_dl_params_unरेजिस्टर(काष्ठा bnxt *bp)
अणु
	अगर (bp->hwrm_spec_code < 0x10600)
		वापस;

	devlink_params_unरेजिस्टर(bp->dl, bnxt_dl_params,
				  ARRAY_SIZE(bnxt_dl_params));
	devlink_port_params_unरेजिस्टर(&bp->dl_port, bnxt_dl_port_params,
				       ARRAY_SIZE(bnxt_dl_port_params));
पूर्ण

पूर्णांक bnxt_dl_रेजिस्टर(काष्ठा bnxt *bp)
अणु
	काष्ठा devlink_port_attrs attrs = अणुपूर्ण;
	काष्ठा devlink *dl;
	पूर्णांक rc;

	अगर (BNXT_PF(bp))
		dl = devlink_alloc(&bnxt_dl_ops, माप(काष्ठा bnxt_dl));
	अन्यथा
		dl = devlink_alloc(&bnxt_vf_dl_ops, माप(काष्ठा bnxt_dl));
	अगर (!dl) अणु
		netdev_warn(bp->dev, "devlink_alloc failed\n");
		वापस -ENOMEM;
	पूर्ण

	bnxt_link_bp_to_dl(bp, dl);

	/* Add चयनdev eचयन mode setting, अगर SRIOV supported */
	अगर (pci_find_ext_capability(bp->pdev, PCI_EXT_CAP_ID_SRIOV) &&
	    bp->hwrm_spec_code > 0x10803)
		bp->eचयन_mode = DEVLINK_ESWITCH_MODE_LEGACY;

	rc = devlink_रेजिस्टर(dl, &bp->pdev->dev);
	अगर (rc) अणु
		netdev_warn(bp->dev, "devlink_register failed. rc=%d\n", rc);
		जाओ err_dl_मुक्त;
	पूर्ण

	अगर (!BNXT_PF(bp))
		वापस 0;

	attrs.flavour = DEVLINK_PORT_FLAVOUR_PHYSICAL;
	attrs.phys.port_number = bp->pf.port_id;
	स_नकल(attrs.चयन_id.id, bp->dsn, माप(bp->dsn));
	attrs.चयन_id.id_len = माप(bp->dsn);
	devlink_port_attrs_set(&bp->dl_port, &attrs);
	rc = devlink_port_रेजिस्टर(dl, &bp->dl_port, bp->pf.port_id);
	अगर (rc) अणु
		netdev_err(bp->dev, "devlink_port_register failed\n");
		जाओ err_dl_unreg;
	पूर्ण

	rc = bnxt_dl_params_रेजिस्टर(bp);
	अगर (rc)
		जाओ err_dl_port_unreg;

	वापस 0;

err_dl_port_unreg:
	devlink_port_unरेजिस्टर(&bp->dl_port);
err_dl_unreg:
	devlink_unरेजिस्टर(dl);
err_dl_मुक्त:
	bnxt_link_bp_to_dl(bp, शून्य);
	devlink_मुक्त(dl);
	वापस rc;
पूर्ण

व्योम bnxt_dl_unरेजिस्टर(काष्ठा bnxt *bp)
अणु
	काष्ठा devlink *dl = bp->dl;

	अगर (!dl)
		वापस;

	अगर (BNXT_PF(bp)) अणु
		bnxt_dl_params_unरेजिस्टर(bp);
		devlink_port_unरेजिस्टर(&bp->dl_port);
	पूर्ण
	devlink_unरेजिस्टर(dl);
	devlink_मुक्त(dl);
पूर्ण
