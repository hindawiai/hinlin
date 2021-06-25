<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Marvell/Qlogic FastLinQ NIC driver
 *
 * Copyright (C) 2020 Marvell International Ltd.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/qed/qed_अगर.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "qed.h"
#समावेश "qed_devlink.h"

क्रमागत qed_devlink_param_id अणु
	QED_DEVLINK_PARAM_ID_BASE = DEVLINK_PARAM_GENERIC_ID_MAX,
	QED_DEVLINK_PARAM_ID_IWARP_CMT,
पूर्ण;

काष्ठा qed_fw_fatal_ctx अणु
	क्रमागत qed_hw_err_type err_type;
पूर्ण;

पूर्णांक qed_report_fatal_error(काष्ठा devlink *devlink, क्रमागत qed_hw_err_type err_type)
अणु
	काष्ठा qed_devlink *qdl = devlink_priv(devlink);
	काष्ठा qed_fw_fatal_ctx fw_fatal_ctx = अणु
		.err_type = err_type,
	पूर्ण;

	अगर (qdl->fw_reporter)
		devlink_health_report(qdl->fw_reporter,
				      "Fatal error occurred", &fw_fatal_ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक
qed_fw_fatal_reporter_dump(काष्ठा devlink_health_reporter *reporter,
			   काष्ठा devlink_fmsg *fmsg, व्योम *priv_ctx,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा qed_devlink *qdl = devlink_health_reporter_priv(reporter);
	काष्ठा qed_fw_fatal_ctx *fw_fatal_ctx = priv_ctx;
	काष्ठा qed_dev *cdev = qdl->cdev;
	u32 dbg_data_buf_size;
	u8 *p_dbg_data_buf;
	पूर्णांक err;

	/* Having context means that was a dump request after fatal,
	 * so we enable extra debugging जबतक gathering the dump,
	 * just in हाल
	 */
	cdev->prपूर्णांक_dbg_data = fw_fatal_ctx ? true : false;

	dbg_data_buf_size = qed_dbg_all_data_size(cdev);
	p_dbg_data_buf = vzalloc(dbg_data_buf_size);
	अगर (!p_dbg_data_buf) अणु
		DP_NOTICE(cdev,
			  "Failed to allocate memory for a debug data buffer\n");
		वापस -ENOMEM;
	पूर्ण

	err = qed_dbg_all_data(cdev, p_dbg_data_buf);
	अगर (err) अणु
		DP_NOTICE(cdev, "Failed to obtain debug data\n");
		vमुक्त(p_dbg_data_buf);
		वापस err;
	पूर्ण

	err = devlink_fmsg_binary_pair_put(fmsg, "dump_data",
					   p_dbg_data_buf, dbg_data_buf_size);

	vमुक्त(p_dbg_data_buf);

	वापस err;
पूर्ण

अटल पूर्णांक
qed_fw_fatal_reporter_recover(काष्ठा devlink_health_reporter *reporter,
			      व्योम *priv_ctx,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा qed_devlink *qdl = devlink_health_reporter_priv(reporter);
	काष्ठा qed_dev *cdev = qdl->cdev;

	qed_recovery_process(cdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा devlink_health_reporter_ops qed_fw_fatal_reporter_ops = अणु
		.name = "fw_fatal",
		.recover = qed_fw_fatal_reporter_recover,
		.dump = qed_fw_fatal_reporter_dump,
पूर्ण;

#घोषणा QED_REPORTER_FW_GRACEFUL_PERIOD 1200000

व्योम qed_fw_reporters_create(काष्ठा devlink *devlink)
अणु
	काष्ठा qed_devlink *dl = devlink_priv(devlink);

	dl->fw_reporter = devlink_health_reporter_create(devlink, &qed_fw_fatal_reporter_ops,
							 QED_REPORTER_FW_GRACEFUL_PERIOD, dl);
	अगर (IS_ERR(dl->fw_reporter)) अणु
		DP_NOTICE(dl->cdev, "Failed to create fw reporter, err = %ld\n",
			  PTR_ERR(dl->fw_reporter));
		dl->fw_reporter = शून्य;
	पूर्ण
पूर्ण

व्योम qed_fw_reporters_destroy(काष्ठा devlink *devlink)
अणु
	काष्ठा qed_devlink *dl = devlink_priv(devlink);
	काष्ठा devlink_health_reporter *rep;

	rep = dl->fw_reporter;

	अगर (!IS_ERR_OR_शून्य(rep))
		devlink_health_reporter_destroy(rep);
पूर्ण

अटल पूर्णांक qed_dl_param_get(काष्ठा devlink *dl, u32 id,
			    काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा qed_devlink *qed_dl = devlink_priv(dl);
	काष्ठा qed_dev *cdev;

	cdev = qed_dl->cdev;
	ctx->val.vbool = cdev->iwarp_cmt;

	वापस 0;
पूर्ण

अटल पूर्णांक qed_dl_param_set(काष्ठा devlink *dl, u32 id,
			    काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा qed_devlink *qed_dl = devlink_priv(dl);
	काष्ठा qed_dev *cdev;

	cdev = qed_dl->cdev;
	cdev->iwarp_cmt = ctx->val.vbool;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा devlink_param qed_devlink_params[] = अणु
	DEVLINK_PARAM_DRIVER(QED_DEVLINK_PARAM_ID_IWARP_CMT,
			     "iwarp_cmt", DEVLINK_PARAM_TYPE_BOOL,
			     BIT(DEVLINK_PARAM_CMODE_RUNTIME),
			     qed_dl_param_get, qed_dl_param_set, शून्य),
पूर्ण;

अटल पूर्णांक qed_devlink_info_get(काष्ठा devlink *devlink,
				काष्ठा devlink_info_req *req,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा qed_devlink *qed_dl = devlink_priv(devlink);
	काष्ठा qed_dev *cdev = qed_dl->cdev;
	काष्ठा qed_dev_info *dev_info;
	अक्षर buf[100];
	पूर्णांक err;

	dev_info = &cdev->common_dev_info;

	err = devlink_info_driver_name_put(req, KBUILD_MODNAME);
	अगर (err)
		वापस err;

	स_नकल(buf, cdev->hwfns[0].hw_info.part_num, माप(cdev->hwfns[0].hw_info.part_num));
	buf[माप(cdev->hwfns[0].hw_info.part_num)] = 0;

	अगर (buf[0]) अणु
		err = devlink_info_board_serial_number_put(req, buf);
		अगर (err)
			वापस err;
	पूर्ण

	snम_लिखो(buf, माप(buf), "%d.%d.%d.%d",
		 GET_MFW_FIELD(dev_info->mfw_rev, QED_MFW_VERSION_3),
		 GET_MFW_FIELD(dev_info->mfw_rev, QED_MFW_VERSION_2),
		 GET_MFW_FIELD(dev_info->mfw_rev, QED_MFW_VERSION_1),
		 GET_MFW_FIELD(dev_info->mfw_rev, QED_MFW_VERSION_0));

	err = devlink_info_version_stored_put(req,
					      DEVLINK_INFO_VERSION_GENERIC_FW_MGMT, buf);
	अगर (err)
		वापस err;

	snम_लिखो(buf, माप(buf), "%d.%d.%d.%d",
		 dev_info->fw_major,
		 dev_info->fw_minor,
		 dev_info->fw_rev,
		 dev_info->fw_eng);

	वापस devlink_info_version_running_put(req,
						DEVLINK_INFO_VERSION_GENERIC_FW_APP, buf);
पूर्ण

अटल स्थिर काष्ठा devlink_ops qed_dl_ops = अणु
	.info_get = qed_devlink_info_get,
पूर्ण;

काष्ठा devlink *qed_devlink_रेजिस्टर(काष्ठा qed_dev *cdev)
अणु
	जोड़ devlink_param_value value;
	काष्ठा qed_devlink *qdevlink;
	काष्ठा devlink *dl;
	पूर्णांक rc;

	dl = devlink_alloc(&qed_dl_ops, माप(काष्ठा qed_devlink));
	अगर (!dl)
		वापस ERR_PTR(-ENOMEM);

	qdevlink = devlink_priv(dl);
	qdevlink->cdev = cdev;

	rc = devlink_रेजिस्टर(dl, &cdev->pdev->dev);
	अगर (rc)
		जाओ err_मुक्त;

	rc = devlink_params_रेजिस्टर(dl, qed_devlink_params,
				     ARRAY_SIZE(qed_devlink_params));
	अगर (rc)
		जाओ err_unरेजिस्टर;

	value.vbool = false;
	devlink_param_driverinit_value_set(dl,
					   QED_DEVLINK_PARAM_ID_IWARP_CMT,
					   value);

	devlink_params_publish(dl);
	cdev->iwarp_cmt = false;

	qed_fw_reporters_create(dl);

	वापस dl;

err_unरेजिस्टर:
	devlink_unरेजिस्टर(dl);

err_मुक्त:
	devlink_मुक्त(dl);

	वापस ERR_PTR(rc);
पूर्ण

व्योम qed_devlink_unरेजिस्टर(काष्ठा devlink *devlink)
अणु
	अगर (!devlink)
		वापस;

	qed_fw_reporters_destroy(devlink);

	devlink_params_unरेजिस्टर(devlink, qed_devlink_params,
				  ARRAY_SIZE(qed_devlink_params));

	devlink_unरेजिस्टर(devlink);
	devlink_मुक्त(devlink);
पूर्ण
