<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2011-2017, The Linux Foundation. All rights reserved.
// Copyright (c) 2018, Linaro Limited

#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/slimbus.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/remoteproc/qcom_rproc.h>
#समावेश <linux/of.h>
#समावेश <linux/पन.स>
#समावेश <linux/soc/qcom/qmi.h>
#समावेश <linux/soc/qcom/pdr.h>
#समावेश <net/sock.h>
#समावेश "slimbus.h"

/* NGD (Non-ported Generic Device) रेजिस्टरs */
#घोषणा	NGD_CFG			0x0
#घोषणा	NGD_CFG_ENABLE		BIT(0)
#घोषणा	NGD_CFG_RX_MSGQ_EN	BIT(1)
#घोषणा	NGD_CFG_TX_MSGQ_EN	BIT(2)
#घोषणा	NGD_STATUS		0x4
#घोषणा NGD_LADDR		BIT(1)
#घोषणा	NGD_RX_MSGQ_CFG		0x8
#घोषणा	NGD_INT_EN		0x10
#घोषणा	NGD_INT_RECFG_DONE	BIT(24)
#घोषणा	NGD_INT_TX_NACKED_2	BIT(25)
#घोषणा	NGD_INT_MSG_BUF_CONTE	BIT(26)
#घोषणा	NGD_INT_MSG_TX_INVAL	BIT(27)
#घोषणा	NGD_INT_IE_VE_CHG	BIT(28)
#घोषणा	NGD_INT_DEV_ERR		BIT(29)
#घोषणा	NGD_INT_RX_MSG_RCVD	BIT(30)
#घोषणा	NGD_INT_TX_MSG_SENT	BIT(31)
#घोषणा	NGD_INT_STAT		0x14
#घोषणा	NGD_INT_CLR		0x18
#घोषणा DEF_NGD_INT_MASK (NGD_INT_TX_NACKED_2 | NGD_INT_MSG_BUF_CONTE | \
				NGD_INT_MSG_TX_INVAL | NGD_INT_IE_VE_CHG | \
				NGD_INT_DEV_ERR | NGD_INT_TX_MSG_SENT | \
				NGD_INT_RX_MSG_RCVD)

/* Slimbus QMI service */
#घोषणा SLIMBUS_QMI_SVC_ID	0x0301
#घोषणा SLIMBUS_QMI_SVC_V1	1
#घोषणा SLIMBUS_QMI_INS_ID	0
#घोषणा SLIMBUS_QMI_SELECT_INSTANCE_REQ_V01	0x0020
#घोषणा SLIMBUS_QMI_SELECT_INSTANCE_RESP_V01	0x0020
#घोषणा SLIMBUS_QMI_POWER_REQ_V01		0x0021
#घोषणा SLIMBUS_QMI_POWER_RESP_V01		0x0021
#घोषणा SLIMBUS_QMI_CHECK_FRAMER_STATUS_REQ	0x0022
#घोषणा SLIMBUS_QMI_CHECK_FRAMER_STATUS_RESP	0x0022
#घोषणा SLIMBUS_QMI_POWER_REQ_MAX_MSG_LEN	14
#घोषणा SLIMBUS_QMI_POWER_RESP_MAX_MSG_LEN	7
#घोषणा SLIMBUS_QMI_SELECT_INSTANCE_REQ_MAX_MSG_LEN	14
#घोषणा SLIMBUS_QMI_SELECT_INSTANCE_RESP_MAX_MSG_LEN	7
#घोषणा SLIMBUS_QMI_CHECK_FRAMER_STAT_RESP_MAX_MSG_LEN	7
/* QMI response समयout of 500ms */
#घोषणा SLIMBUS_QMI_RESP_TOUT	1000

/* User defined commands */
#घोषणा SLIM_USR_MC_GENERIC_ACK	0x25
#घोषणा SLIM_USR_MC_MASTER_CAPABILITY	0x0
#घोषणा SLIM_USR_MC_REPORT_SATELLITE	0x1
#घोषणा SLIM_USR_MC_ADDR_QUERY		0xD
#घोषणा SLIM_USR_MC_ADDR_REPLY		0xE
#घोषणा SLIM_USR_MC_DEFINE_CHAN		0x20
#घोषणा SLIM_USR_MC_DEF_ACT_CHAN	0x21
#घोषणा SLIM_USR_MC_CHAN_CTRL		0x23
#घोषणा SLIM_USR_MC_RECONFIG_NOW	0x24
#घोषणा SLIM_USR_MC_REQ_BW		0x28
#घोषणा SLIM_USR_MC_CONNECT_SRC		0x2C
#घोषणा SLIM_USR_MC_CONNECT_SINK	0x2D
#घोषणा SLIM_USR_MC_DISCONNECT_PORT	0x2E
#घोषणा SLIM_USR_MC_REPEAT_CHANGE_VALUE	0x0

#घोषणा QCOM_SLIM_NGD_AUTOSUSPEND	MSEC_PER_SEC
#घोषणा SLIM_RX_MSGQ_TIMEOUT_VAL	0x10000

#घोषणा SLIM_LA_MGR	0xFF
#घोषणा SLIM_ROOT_FREQ	24576000
#घोषणा LADDR_RETRY	5

/* Per spec.max 40 bytes per received message */
#घोषणा SLIM_MSGQ_BUF_LEN	40
#घोषणा QCOM_SLIM_NGD_DESC_NUM	32

#घोषणा SLIM_MSG_ASM_FIRST_WORD(l, mt, mc, dt, ad) \
		((l) | ((mt) << 5) | ((mc) << 8) | ((dt) << 15) | ((ad) << 16))

#घोषणा INIT_MX_RETRIES 10
#घोषणा DEF_RETRY_MS	10
#घोषणा SAT_MAGIC_LSB	0xD9
#घोषणा SAT_MAGIC_MSB	0xC5
#घोषणा SAT_MSG_VER	0x1
#घोषणा SAT_MSG_PROT	0x1
#घोषणा to_ngd(d)	container_of(d, काष्ठा qcom_slim_ngd, dev)

काष्ठा ngd_reg_offset_data अणु
	u32 offset, size;
पूर्ण;

अटल स्थिर काष्ठा ngd_reg_offset_data ngd_v1_5_offset_info = अणु
	.offset = 0x1000,
	.size = 0x1000,
पूर्ण;

क्रमागत qcom_slim_ngd_state अणु
	QCOM_SLIM_NGD_CTRL_AWAKE,
	QCOM_SLIM_NGD_CTRL_IDLE,
	QCOM_SLIM_NGD_CTRL_ASLEEP,
	QCOM_SLIM_NGD_CTRL_DOWN,
पूर्ण;

काष्ठा qcom_slim_ngd_qmi अणु
	काष्ठा qmi_handle qmi;
	काष्ठा sockaddr_qrtr svc_info;
	काष्ठा qmi_handle svc_event_hdl;
	काष्ठा qmi_response_type_v01 resp;
	काष्ठा qmi_handle *handle;
	काष्ठा completion qmi_comp;
पूर्ण;

काष्ठा qcom_slim_ngd_ctrl;
काष्ठा qcom_slim_ngd;

काष्ठा qcom_slim_ngd_dma_desc अणु
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा qcom_slim_ngd_ctrl *ctrl;
	काष्ठा completion *comp;
	dma_cookie_t cookie;
	dma_addr_t phys;
	व्योम *base;
पूर्ण;

काष्ठा qcom_slim_ngd अणु
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem *base;
	पूर्णांक id;
पूर्ण;

काष्ठा qcom_slim_ngd_ctrl अणु
	काष्ठा slim_framer framer;
	काष्ठा slim_controller ctrl;
	काष्ठा qcom_slim_ngd_qmi qmi;
	काष्ठा qcom_slim_ngd *ngd;
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा dma_chan *dma_rx_channel;
	काष्ठा dma_chan	*dma_tx_channel;
	काष्ठा qcom_slim_ngd_dma_desc rx_desc[QCOM_SLIM_NGD_DESC_NUM];
	काष्ठा qcom_slim_ngd_dma_desc txdesc[QCOM_SLIM_NGD_DESC_NUM];
	काष्ठा completion reconf;
	काष्ठा work_काष्ठा m_work;
	काष्ठा work_काष्ठा ngd_up_work;
	काष्ठा workqueue_काष्ठा *mwq;
	काष्ठा completion qmi_up;
	spinlock_t tx_buf_lock;
	काष्ठा mutex tx_lock;
	काष्ठा mutex ssr_lock;
	काष्ठा notअगरier_block nb;
	व्योम *notअगरier;
	काष्ठा pdr_handle *pdr;
	क्रमागत qcom_slim_ngd_state state;
	dma_addr_t rx_phys_base;
	dma_addr_t tx_phys_base;
	व्योम *rx_base;
	व्योम *tx_base;
	पूर्णांक tx_tail;
	पूर्णांक tx_head;
	u32 ver;
पूर्ण;

क्रमागत slimbus_mode_क्रमागत_type_v01 अणु
	/* To क्रमce a 32 bit चिन्हित क्रमागत. Do not change or use*/
	SLIMBUS_MODE_ENUM_TYPE_MIN_ENUM_VAL_V01 = पूर्णांक_न्यून,
	SLIMBUS_MODE_SATELLITE_V01 = 1,
	SLIMBUS_MODE_MASTER_V01 = 2,
	SLIMBUS_MODE_ENUM_TYPE_MAX_ENUM_VAL_V01 = पूर्णांक_उच्च,
पूर्ण;

क्रमागत slimbus_pm_क्रमागत_type_v01 अणु
	/* To क्रमce a 32 bit चिन्हित क्रमागत. Do not change or use*/
	SLIMBUS_PM_ENUM_TYPE_MIN_ENUM_VAL_V01 = पूर्णांक_न्यून,
	SLIMBUS_PM_INACTIVE_V01 = 1,
	SLIMBUS_PM_ACTIVE_V01 = 2,
	SLIMBUS_PM_ENUM_TYPE_MAX_ENUM_VAL_V01 = पूर्णांक_उच्च,
पूर्ण;

क्रमागत slimbus_resp_क्रमागत_type_v01 अणु
	SLIMBUS_RESP_ENUM_TYPE_MIN_VAL_V01 = पूर्णांक_न्यून,
	SLIMBUS_RESP_SYNCHRONOUS_V01 = 1,
	SLIMBUS_RESP_ENUM_TYPE_MAX_VAL_V01 = पूर्णांक_उच्च,
पूर्ण;

काष्ठा slimbus_select_inst_req_msg_v01 अणु
	uपूर्णांक32_t instance;
	uपूर्णांक8_t mode_valid;
	क्रमागत slimbus_mode_क्रमागत_type_v01 mode;
पूर्ण;

काष्ठा slimbus_select_inst_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

काष्ठा slimbus_घातer_req_msg_v01 अणु
	क्रमागत slimbus_pm_क्रमागत_type_v01 pm_req;
	uपूर्णांक8_t resp_type_valid;
	क्रमागत slimbus_resp_क्रमागत_type_v01 resp_type;
पूर्ण;

काष्ठा slimbus_घातer_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

अटल काष्ठा qmi_elem_info slimbus_select_inst_req_msg_v01_ei[] = अणु
	अणु
		.data_type  = QMI_UNSIGNED_4_BYTE,
		.elem_len   = 1,
		.elem_size  = माप(uपूर्णांक32_t),
		.array_type = NO_ARRAY,
		.tlv_type   = 0x01,
		.offset     = दुरत्व(काष्ठा slimbus_select_inst_req_msg_v01,
				       instance),
		.ei_array   = शून्य,
	पूर्ण,
	अणु
		.data_type  = QMI_OPT_FLAG,
		.elem_len   = 1,
		.elem_size  = माप(uपूर्णांक8_t),
		.array_type = NO_ARRAY,
		.tlv_type   = 0x10,
		.offset     = दुरत्व(काष्ठा slimbus_select_inst_req_msg_v01,
				       mode_valid),
		.ei_array   = शून्य,
	पूर्ण,
	अणु
		.data_type  = QMI_UNSIGNED_4_BYTE,
		.elem_len   = 1,
		.elem_size  = माप(क्रमागत slimbus_mode_क्रमागत_type_v01),
		.array_type = NO_ARRAY,
		.tlv_type   = 0x10,
		.offset     = दुरत्व(काष्ठा slimbus_select_inst_req_msg_v01,
				       mode),
		.ei_array   = शून्य,
	पूर्ण,
	अणु
		.data_type  = QMI_EOTI,
		.elem_len   = 0,
		.elem_size  = 0,
		.array_type = NO_ARRAY,
		.tlv_type   = 0x00,
		.offset     = 0,
		.ei_array   = शून्य,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info slimbus_select_inst_resp_msg_v01_ei[] = अणु
	अणु
		.data_type  = QMI_STRUCT,
		.elem_len   = 1,
		.elem_size  = माप(काष्ठा qmi_response_type_v01),
		.array_type = NO_ARRAY,
		.tlv_type   = 0x02,
		.offset     = दुरत्व(काष्ठा slimbus_select_inst_resp_msg_v01,
				       resp),
		.ei_array   = qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type  = QMI_EOTI,
		.elem_len   = 0,
		.elem_size  = 0,
		.array_type = NO_ARRAY,
		.tlv_type   = 0x00,
		.offset     = 0,
		.ei_array   = शून्य,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info slimbus_घातer_req_msg_v01_ei[] = अणु
	अणु
		.data_type  = QMI_UNSIGNED_4_BYTE,
		.elem_len   = 1,
		.elem_size  = माप(क्रमागत slimbus_pm_क्रमागत_type_v01),
		.array_type = NO_ARRAY,
		.tlv_type   = 0x01,
		.offset     = दुरत्व(काष्ठा slimbus_घातer_req_msg_v01,
				       pm_req),
		.ei_array   = शून्य,
	पूर्ण,
	अणु
		.data_type  = QMI_OPT_FLAG,
		.elem_len   = 1,
		.elem_size  = माप(uपूर्णांक8_t),
		.array_type = NO_ARRAY,
		.tlv_type   = 0x10,
		.offset     = दुरत्व(काष्ठा slimbus_घातer_req_msg_v01,
				       resp_type_valid),
	पूर्ण,
	अणु
		.data_type  = QMI_SIGNED_4_BYTE_ENUM,
		.elem_len   = 1,
		.elem_size  = माप(क्रमागत slimbus_resp_क्रमागत_type_v01),
		.array_type = NO_ARRAY,
		.tlv_type   = 0x10,
		.offset     = दुरत्व(काष्ठा slimbus_घातer_req_msg_v01,
				       resp_type),
	पूर्ण,
	अणु
		.data_type  = QMI_EOTI,
		.elem_len   = 0,
		.elem_size  = 0,
		.array_type = NO_ARRAY,
		.tlv_type   = 0x00,
		.offset     = 0,
		.ei_array   = शून्य,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info slimbus_घातer_resp_msg_v01_ei[] = अणु
	अणु
		.data_type  = QMI_STRUCT,
		.elem_len   = 1,
		.elem_size  = माप(काष्ठा qmi_response_type_v01),
		.array_type = NO_ARRAY,
		.tlv_type   = 0x02,
		.offset     = दुरत्व(काष्ठा slimbus_घातer_resp_msg_v01, resp),
		.ei_array   = qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type  = QMI_EOTI,
		.elem_len   = 0,
		.elem_size  = 0,
		.array_type = NO_ARRAY,
		.tlv_type   = 0x00,
		.offset     = 0,
		.ei_array   = शून्य,
	पूर्ण,
पूर्ण;

अटल पूर्णांक qcom_slim_qmi_send_select_inst_req(काष्ठा qcom_slim_ngd_ctrl *ctrl,
				काष्ठा slimbus_select_inst_req_msg_v01 *req)
अणु
	काष्ठा slimbus_select_inst_resp_msg_v01 resp = अणु अणु 0, 0 पूर्ण पूर्ण;
	काष्ठा qmi_txn txn;
	पूर्णांक rc;

	rc = qmi_txn_init(ctrl->qmi.handle, &txn,
				slimbus_select_inst_resp_msg_v01_ei, &resp);
	अगर (rc < 0) अणु
		dev_err(ctrl->dev, "QMI TXN init fail: %d\n", rc);
		वापस rc;
	पूर्ण

	rc = qmi_send_request(ctrl->qmi.handle, शून्य, &txn,
				SLIMBUS_QMI_SELECT_INSTANCE_REQ_V01,
				SLIMBUS_QMI_SELECT_INSTANCE_REQ_MAX_MSG_LEN,
				slimbus_select_inst_req_msg_v01_ei, req);
	अगर (rc < 0) अणु
		dev_err(ctrl->dev, "QMI send req fail %d\n", rc);
		qmi_txn_cancel(&txn);
		वापस rc;
	पूर्ण

	rc = qmi_txn_रुको(&txn, SLIMBUS_QMI_RESP_TOUT);
	अगर (rc < 0) अणु
		dev_err(ctrl->dev, "QMI TXN wait fail: %d\n", rc);
		वापस rc;
	पूर्ण
	/* Check the response */
	अगर (resp.resp.result != QMI_RESULT_SUCCESS_V01) अणु
		dev_err(ctrl->dev, "QMI request failed 0x%x\n",
			resp.resp.result);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qcom_slim_qmi_घातer_resp_cb(काष्ठा qmi_handle *handle,
					काष्ठा sockaddr_qrtr *sq,
					काष्ठा qmi_txn *txn, स्थिर व्योम *data)
अणु
	काष्ठा slimbus_घातer_resp_msg_v01 *resp;

	resp = (काष्ठा slimbus_घातer_resp_msg_v01 *)data;
	अगर (resp->resp.result != QMI_RESULT_SUCCESS_V01)
		pr_err("QMI power request failed 0x%x\n",
				resp->resp.result);

	complete(&txn->completion);
पूर्ण

अटल पूर्णांक qcom_slim_qmi_send_घातer_request(काष्ठा qcom_slim_ngd_ctrl *ctrl,
					काष्ठा slimbus_घातer_req_msg_v01 *req)
अणु
	काष्ठा slimbus_घातer_resp_msg_v01 resp = अणु अणु 0, 0 पूर्ण पूर्ण;
	काष्ठा qmi_txn txn;
	पूर्णांक rc;

	rc = qmi_txn_init(ctrl->qmi.handle, &txn,
				slimbus_घातer_resp_msg_v01_ei, &resp);

	rc = qmi_send_request(ctrl->qmi.handle, शून्य, &txn,
				SLIMBUS_QMI_POWER_REQ_V01,
				SLIMBUS_QMI_POWER_REQ_MAX_MSG_LEN,
				slimbus_घातer_req_msg_v01_ei, req);
	अगर (rc < 0) अणु
		dev_err(ctrl->dev, "QMI send req fail %d\n", rc);
		qmi_txn_cancel(&txn);
		वापस rc;
	पूर्ण

	rc = qmi_txn_रुको(&txn, SLIMBUS_QMI_RESP_TOUT);
	अगर (rc < 0) अणु
		dev_err(ctrl->dev, "QMI TXN wait fail: %d\n", rc);
		वापस rc;
	पूर्ण

	/* Check the response */
	अगर (resp.resp.result != QMI_RESULT_SUCCESS_V01) अणु
		dev_err(ctrl->dev, "QMI request failed 0x%x\n",
			resp.resp.result);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा qmi_msg_handler qcom_slim_qmi_msg_handlers[] = अणु
	अणु
		.type = QMI_RESPONSE,
		.msg_id = SLIMBUS_QMI_POWER_RESP_V01,
		.ei = slimbus_घातer_resp_msg_v01_ei,
		.decoded_size = माप(काष्ठा slimbus_घातer_resp_msg_v01),
		.fn = qcom_slim_qmi_घातer_resp_cb,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक qcom_slim_qmi_init(काष्ठा qcom_slim_ngd_ctrl *ctrl,
			      bool apps_is_master)
अणु
	काष्ठा slimbus_select_inst_req_msg_v01 req;
	काष्ठा qmi_handle *handle;
	पूर्णांक rc;

	handle = devm_kzalloc(ctrl->dev, माप(*handle), GFP_KERNEL);
	अगर (!handle)
		वापस -ENOMEM;

	rc = qmi_handle_init(handle, SLIMBUS_QMI_POWER_REQ_MAX_MSG_LEN,
				शून्य, qcom_slim_qmi_msg_handlers);
	अगर (rc < 0) अणु
		dev_err(ctrl->dev, "QMI client init failed: %d\n", rc);
		जाओ qmi_handle_init_failed;
	पूर्ण

	rc = kernel_connect(handle->sock,
				(काष्ठा sockaddr *)&ctrl->qmi.svc_info,
				माप(ctrl->qmi.svc_info), 0);
	अगर (rc < 0) अणु
		dev_err(ctrl->dev, "Remote Service connect failed: %d\n", rc);
		जाओ qmi_connect_to_service_failed;
	पूर्ण

	/* Instance is 0 based */
	req.instance = (ctrl->ngd->id >> 1);
	req.mode_valid = 1;

	/* Mode indicates the role of the ADSP */
	अगर (apps_is_master)
		req.mode = SLIMBUS_MODE_SATELLITE_V01;
	अन्यथा
		req.mode = SLIMBUS_MODE_MASTER_V01;

	ctrl->qmi.handle = handle;

	rc = qcom_slim_qmi_send_select_inst_req(ctrl, &req);
	अगर (rc) अणु
		dev_err(ctrl->dev, "failed to select h/w instance\n");
		जाओ qmi_select_instance_failed;
	पूर्ण

	वापस 0;

qmi_select_instance_failed:
	ctrl->qmi.handle = शून्य;
qmi_connect_to_service_failed:
	qmi_handle_release(handle);
qmi_handle_init_failed:
	devm_kमुक्त(ctrl->dev, handle);
	वापस rc;
पूर्ण

अटल व्योम qcom_slim_qmi_निकास(काष्ठा qcom_slim_ngd_ctrl *ctrl)
अणु
	अगर (!ctrl->qmi.handle)
		वापस;

	qmi_handle_release(ctrl->qmi.handle);
	devm_kमुक्त(ctrl->dev, ctrl->qmi.handle);
	ctrl->qmi.handle = शून्य;
पूर्ण

अटल पूर्णांक qcom_slim_qmi_घातer_request(काष्ठा qcom_slim_ngd_ctrl *ctrl,
				       bool active)
अणु
	काष्ठा slimbus_घातer_req_msg_v01 req;

	अगर (active)
		req.pm_req = SLIMBUS_PM_ACTIVE_V01;
	अन्यथा
		req.pm_req = SLIMBUS_PM_INACTIVE_V01;

	req.resp_type_valid = 0;

	वापस qcom_slim_qmi_send_घातer_request(ctrl, &req);
पूर्ण

अटल u32 *qcom_slim_ngd_tx_msg_get(काष्ठा qcom_slim_ngd_ctrl *ctrl, पूर्णांक len,
				     काष्ठा completion *comp)
अणु
	काष्ठा qcom_slim_ngd_dma_desc *desc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctrl->tx_buf_lock, flags);

	अगर ((ctrl->tx_tail + 1) % QCOM_SLIM_NGD_DESC_NUM == ctrl->tx_head) अणु
		spin_unlock_irqrestore(&ctrl->tx_buf_lock, flags);
		वापस शून्य;
	पूर्ण
	desc  = &ctrl->txdesc[ctrl->tx_tail];
	desc->base = ctrl->tx_base + ctrl->tx_tail * SLIM_MSGQ_BUF_LEN;
	desc->comp = comp;
	ctrl->tx_tail = (ctrl->tx_tail + 1) % QCOM_SLIM_NGD_DESC_NUM;

	spin_unlock_irqrestore(&ctrl->tx_buf_lock, flags);

	वापस desc->base;
पूर्ण

अटल व्योम qcom_slim_ngd_tx_msg_dma_cb(व्योम *args)
अणु
	काष्ठा qcom_slim_ngd_dma_desc *desc = args;
	काष्ठा qcom_slim_ngd_ctrl *ctrl = desc->ctrl;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctrl->tx_buf_lock, flags);

	अगर (desc->comp) अणु
		complete(desc->comp);
		desc->comp = शून्य;
	पूर्ण

	ctrl->tx_head = (ctrl->tx_head + 1) % QCOM_SLIM_NGD_DESC_NUM;
	spin_unlock_irqrestore(&ctrl->tx_buf_lock, flags);
पूर्ण

अटल पूर्णांक qcom_slim_ngd_tx_msg_post(काष्ठा qcom_slim_ngd_ctrl *ctrl,
				     व्योम *buf, पूर्णांक len)
अणु
	काष्ठा qcom_slim_ngd_dma_desc *desc;
	अचिन्हित दीर्घ flags;
	पूर्णांक index, offset;

	spin_lock_irqsave(&ctrl->tx_buf_lock, flags);
	offset = buf - ctrl->tx_base;
	index = offset/SLIM_MSGQ_BUF_LEN;

	desc = &ctrl->txdesc[index];
	desc->phys = ctrl->tx_phys_base + offset;
	desc->base = ctrl->tx_base + offset;
	desc->ctrl = ctrl;
	len = (len + 3) & 0xfc;

	desc->desc = dmaengine_prep_slave_single(ctrl->dma_tx_channel,
						desc->phys, len,
						DMA_MEM_TO_DEV,
						DMA_PREP_INTERRUPT);
	अगर (!desc->desc) अणु
		dev_err(ctrl->dev, "unable to prepare channel\n");
		spin_unlock_irqrestore(&ctrl->tx_buf_lock, flags);
		वापस -EINVAL;
	पूर्ण

	desc->desc->callback = qcom_slim_ngd_tx_msg_dma_cb;
	desc->desc->callback_param = desc;
	desc->desc->cookie = dmaengine_submit(desc->desc);
	dma_async_issue_pending(ctrl->dma_tx_channel);
	spin_unlock_irqrestore(&ctrl->tx_buf_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम qcom_slim_ngd_rx(काष्ठा qcom_slim_ngd_ctrl *ctrl, u8 *buf)
अणु
	u8 mc, mt, len;

	mt = SLIM_HEADER_GET_MT(buf[0]);
	len = SLIM_HEADER_GET_RL(buf[0]);
	mc = SLIM_HEADER_GET_MC(buf[1]);

	अगर (mc == SLIM_USR_MC_MASTER_CAPABILITY &&
		mt == SLIM_MSG_MT_SRC_REFERRED_USER)
		queue_work(ctrl->mwq, &ctrl->m_work);

	अगर (mc == SLIM_MSG_MC_REPLY_INFORMATION ||
	    mc == SLIM_MSG_MC_REPLY_VALUE || (mc == SLIM_USR_MC_ADDR_REPLY &&
	    mt == SLIM_MSG_MT_SRC_REFERRED_USER) ||
		(mc == SLIM_USR_MC_GENERIC_ACK &&
		 mt == SLIM_MSG_MT_SRC_REFERRED_USER)) अणु
		slim_msg_response(&ctrl->ctrl, &buf[4], buf[3], len - 4);
		pm_runसमय_mark_last_busy(ctrl->dev);
	पूर्ण
पूर्ण

अटल व्योम qcom_slim_ngd_rx_msgq_cb(व्योम *args)
अणु
	काष्ठा qcom_slim_ngd_dma_desc *desc = args;
	काष्ठा qcom_slim_ngd_ctrl *ctrl = desc->ctrl;

	qcom_slim_ngd_rx(ctrl, (u8 *)desc->base);
	/* Add descriptor back to the queue */
	desc->desc = dmaengine_prep_slave_single(ctrl->dma_rx_channel,
					desc->phys, SLIM_MSGQ_BUF_LEN,
					DMA_DEV_TO_MEM,
					DMA_PREP_INTERRUPT);
	अगर (!desc->desc) अणु
		dev_err(ctrl->dev, "Unable to prepare rx channel\n");
		वापस;
	पूर्ण

	desc->desc->callback = qcom_slim_ngd_rx_msgq_cb;
	desc->desc->callback_param = desc;
	desc->desc->cookie = dmaengine_submit(desc->desc);
	dma_async_issue_pending(ctrl->dma_rx_channel);
पूर्ण

अटल पूर्णांक qcom_slim_ngd_post_rx_msgq(काष्ठा qcom_slim_ngd_ctrl *ctrl)
अणु
	काष्ठा qcom_slim_ngd_dma_desc *desc;
	पूर्णांक i;

	क्रम (i = 0; i < QCOM_SLIM_NGD_DESC_NUM; i++) अणु
		desc = &ctrl->rx_desc[i];
		desc->phys = ctrl->rx_phys_base + i * SLIM_MSGQ_BUF_LEN;
		desc->ctrl = ctrl;
		desc->base = ctrl->rx_base + i * SLIM_MSGQ_BUF_LEN;
		desc->desc = dmaengine_prep_slave_single(ctrl->dma_rx_channel,
						desc->phys, SLIM_MSGQ_BUF_LEN,
						DMA_DEV_TO_MEM,
						DMA_PREP_INTERRUPT);
		अगर (!desc->desc) अणु
			dev_err(ctrl->dev, "Unable to prepare rx channel\n");
			वापस -EINVAL;
		पूर्ण

		desc->desc->callback = qcom_slim_ngd_rx_msgq_cb;
		desc->desc->callback_param = desc;
		desc->desc->cookie = dmaengine_submit(desc->desc);
	पूर्ण
	dma_async_issue_pending(ctrl->dma_rx_channel);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_slim_ngd_init_rx_msgq(काष्ठा qcom_slim_ngd_ctrl *ctrl)
अणु
	काष्ठा device *dev = ctrl->dev;
	पूर्णांक ret, size;

	ctrl->dma_rx_channel = dma_request_chan(dev, "rx");
	अगर (IS_ERR(ctrl->dma_rx_channel)) अणु
		dev_err(dev, "Failed to request RX dma channel");
		ret = PTR_ERR(ctrl->dma_rx_channel);
		ctrl->dma_rx_channel = शून्य;
		वापस ret;
	पूर्ण

	size = QCOM_SLIM_NGD_DESC_NUM * SLIM_MSGQ_BUF_LEN;
	ctrl->rx_base = dma_alloc_coherent(dev, size, &ctrl->rx_phys_base,
					   GFP_KERNEL);
	अगर (!ctrl->rx_base) अणु
		ret = -ENOMEM;
		जाओ rel_rx;
	पूर्ण

	ret = qcom_slim_ngd_post_rx_msgq(ctrl);
	अगर (ret) अणु
		dev_err(dev, "post_rx_msgq() failed 0x%x\n", ret);
		जाओ rx_post_err;
	पूर्ण

	वापस 0;

rx_post_err:
	dma_मुक्त_coherent(dev, size, ctrl->rx_base, ctrl->rx_phys_base);
rel_rx:
	dma_release_channel(ctrl->dma_rx_channel);
	वापस ret;
पूर्ण

अटल पूर्णांक qcom_slim_ngd_init_tx_msgq(काष्ठा qcom_slim_ngd_ctrl *ctrl)
अणु
	काष्ठा device *dev = ctrl->dev;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	पूर्णांक size;

	ctrl->dma_tx_channel = dma_request_chan(dev, "tx");
	अगर (IS_ERR(ctrl->dma_tx_channel)) अणु
		dev_err(dev, "Failed to request TX dma channel");
		ret = PTR_ERR(ctrl->dma_tx_channel);
		ctrl->dma_tx_channel = शून्य;
		वापस ret;
	पूर्ण

	size = ((QCOM_SLIM_NGD_DESC_NUM + 1) * SLIM_MSGQ_BUF_LEN);
	ctrl->tx_base = dma_alloc_coherent(dev, size, &ctrl->tx_phys_base,
					   GFP_KERNEL);
	अगर (!ctrl->tx_base) अणु
		ret = -EINVAL;
		जाओ rel_tx;
	पूर्ण

	spin_lock_irqsave(&ctrl->tx_buf_lock, flags);
	ctrl->tx_tail = 0;
	ctrl->tx_head = 0;
	spin_unlock_irqrestore(&ctrl->tx_buf_lock, flags);

	वापस 0;
rel_tx:
	dma_release_channel(ctrl->dma_tx_channel);
	वापस ret;
पूर्ण

अटल पूर्णांक qcom_slim_ngd_init_dma(काष्ठा qcom_slim_ngd_ctrl *ctrl)
अणु
	पूर्णांक ret = 0;

	ret = qcom_slim_ngd_init_rx_msgq(ctrl);
	अगर (ret) अणु
		dev_err(ctrl->dev, "rx dma init failed\n");
		वापस ret;
	पूर्ण

	ret = qcom_slim_ngd_init_tx_msgq(ctrl);
	अगर (ret)
		dev_err(ctrl->dev, "tx dma init failed\n");

	वापस ret;
पूर्ण

अटल irqवापस_t qcom_slim_ngd_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा qcom_slim_ngd_ctrl *ctrl = d;
	व्योम __iomem *base = ctrl->ngd->base;
	u32 stat = पढ़ोl(base + NGD_INT_STAT);

	अगर ((stat & NGD_INT_MSG_BUF_CONTE) ||
		(stat & NGD_INT_MSG_TX_INVAL) || (stat & NGD_INT_DEV_ERR) ||
		(stat & NGD_INT_TX_NACKED_2)) अणु
		dev_err(ctrl->dev, "Error Interrupt received 0x%x\n", stat);
	पूर्ण

	ग_लिखोl(stat, base + NGD_INT_CLR);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक qcom_slim_ngd_xfer_msg(काष्ठा slim_controller *sctrl,
				  काष्ठा slim_msg_txn *txn)
अणु
	काष्ठा qcom_slim_ngd_ctrl *ctrl = dev_get_drvdata(sctrl->dev);
	DECLARE_COMPLETION_ONSTACK(tx_sent);
	DECLARE_COMPLETION_ONSTACK(करोne);
	पूर्णांक ret, समयout, i;
	u8 wbuf[SLIM_MSGQ_BUF_LEN];
	u8 rbuf[SLIM_MSGQ_BUF_LEN];
	u32 *pbuf;
	u8 *puc;
	u8 la = txn->la;
	bool usr_msg = false;

	अगर (txn->mt == SLIM_MSG_MT_CORE &&
		(txn->mc >= SLIM_MSG_MC_BEGIN_RECONFIGURATION &&
		 txn->mc <= SLIM_MSG_MC_RECONFIGURE_NOW))
		वापस 0;

	अगर (txn->dt == SLIM_MSG_DEST_ENUMADDR)
		वापस -EPROTONOSUPPORT;

	अगर (txn->msg->num_bytes > SLIM_MSGQ_BUF_LEN ||
			txn->rl > SLIM_MSGQ_BUF_LEN) अणु
		dev_err(ctrl->dev, "msg exceeds HW limit\n");
		वापस -EINVAL;
	पूर्ण

	pbuf = qcom_slim_ngd_tx_msg_get(ctrl, txn->rl, &tx_sent);
	अगर (!pbuf) अणु
		dev_err(ctrl->dev, "Message buffer unavailable\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (txn->mt == SLIM_MSG_MT_CORE &&
		(txn->mc == SLIM_MSG_MC_CONNECT_SOURCE ||
		txn->mc == SLIM_MSG_MC_CONNECT_SINK ||
		txn->mc == SLIM_MSG_MC_DISCONNECT_PORT)) अणु
		txn->mt = SLIM_MSG_MT_DEST_REFERRED_USER;
		चयन (txn->mc) अणु
		हाल SLIM_MSG_MC_CONNECT_SOURCE:
			txn->mc = SLIM_USR_MC_CONNECT_SRC;
			अवरोध;
		हाल SLIM_MSG_MC_CONNECT_SINK:
			txn->mc = SLIM_USR_MC_CONNECT_SINK;
			अवरोध;
		हाल SLIM_MSG_MC_DISCONNECT_PORT:
			txn->mc = SLIM_USR_MC_DISCONNECT_PORT;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		usr_msg = true;
		i = 0;
		wbuf[i++] = txn->la;
		la = SLIM_LA_MGR;
		wbuf[i++] = txn->msg->wbuf[0];
		अगर (txn->mc != SLIM_USR_MC_DISCONNECT_PORT)
			wbuf[i++] = txn->msg->wbuf[1];

		txn->comp = &करोne;
		ret = slim_alloc_txn_tid(sctrl, txn);
		अगर (ret) अणु
			dev_err(ctrl->dev, "Unable to allocate TID\n");
			वापस ret;
		पूर्ण

		wbuf[i++] = txn->tid;

		txn->msg->num_bytes = i;
		txn->msg->wbuf = wbuf;
		txn->msg->rbuf = rbuf;
		txn->rl = txn->msg->num_bytes + 4;
	पूर्ण

	/* HW expects length field to be excluded */
	txn->rl--;
	puc = (u8 *)pbuf;
	*pbuf = 0;
	अगर (txn->dt == SLIM_MSG_DEST_LOGICALADDR) अणु
		*pbuf = SLIM_MSG_ASM_FIRST_WORD(txn->rl, txn->mt, txn->mc, 0,
				la);
		puc += 3;
	पूर्ण अन्यथा अणु
		*pbuf = SLIM_MSG_ASM_FIRST_WORD(txn->rl, txn->mt, txn->mc, 1,
				la);
		puc += 2;
	पूर्ण

	अगर (slim_tid_txn(txn->mt, txn->mc))
		*(puc++) = txn->tid;

	अगर (slim_ec_txn(txn->mt, txn->mc)) अणु
		*(puc++) = (txn->ec & 0xFF);
		*(puc++) = (txn->ec >> 8) & 0xFF;
	पूर्ण

	अगर (txn->msg && txn->msg->wbuf)
		स_नकल(puc, txn->msg->wbuf, txn->msg->num_bytes);

	mutex_lock(&ctrl->tx_lock);
	ret = qcom_slim_ngd_tx_msg_post(ctrl, pbuf, txn->rl);
	अगर (ret) अणु
		mutex_unlock(&ctrl->tx_lock);
		वापस ret;
	पूर्ण

	समयout = रुको_क्रम_completion_समयout(&tx_sent, HZ);
	अगर (!समयout) अणु
		dev_err(sctrl->dev, "TX timed out:MC:0x%x,mt:0x%x", txn->mc,
					txn->mt);
		mutex_unlock(&ctrl->tx_lock);
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (usr_msg) अणु
		समयout = रुको_क्रम_completion_समयout(&करोne, HZ);
		अगर (!समयout) अणु
			dev_err(sctrl->dev, "TX timed out:MC:0x%x,mt:0x%x",
				txn->mc, txn->mt);
			mutex_unlock(&ctrl->tx_lock);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	mutex_unlock(&ctrl->tx_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक qcom_slim_ngd_xfer_msg_sync(काष्ठा slim_controller *ctrl,
				       काष्ठा slim_msg_txn *txn)
अणु
	DECLARE_COMPLETION_ONSTACK(करोne);
	पूर्णांक ret, समयout;

	pm_runसमय_get_sync(ctrl->dev);

	txn->comp = &करोne;

	ret = qcom_slim_ngd_xfer_msg(ctrl, txn);
	अगर (ret)
		वापस ret;

	समयout = रुको_क्रम_completion_समयout(&करोne, HZ);
	अगर (!समयout) अणु
		dev_err(ctrl->dev, "TX timed out:MC:0x%x,mt:0x%x", txn->mc,
				txn->mt);
		वापस -ETIMEDOUT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qcom_slim_ngd_enable_stream(काष्ठा slim_stream_runसमय *rt)
अणु
	काष्ठा slim_device *sdev = rt->dev;
	काष्ठा slim_controller *ctrl = sdev->ctrl;
	काष्ठा slim_val_inf msg =  अणु0पूर्ण;
	u8 wbuf[SLIM_MSGQ_BUF_LEN];
	u8 rbuf[SLIM_MSGQ_BUF_LEN];
	काष्ठा slim_msg_txn txn = अणु0,पूर्ण;
	पूर्णांक i, ret;

	txn.mt = SLIM_MSG_MT_DEST_REFERRED_USER;
	txn.dt = SLIM_MSG_DEST_LOGICALADDR;
	txn.la = SLIM_LA_MGR;
	txn.ec = 0;
	txn.msg = &msg;
	txn.msg->num_bytes = 0;
	txn.msg->wbuf = wbuf;
	txn.msg->rbuf = rbuf;

	क्रम (i = 0; i < rt->num_ports; i++) अणु
		काष्ठा slim_port *port = &rt->ports[i];

		अगर (txn.msg->num_bytes == 0) अणु
			पूर्णांक seg_पूर्णांकerval = SLIM_SLOTS_PER_SUPERFRAME/rt->ratem;
			पूर्णांक exp;

			wbuf[txn.msg->num_bytes++] = sdev->laddr;
			wbuf[txn.msg->num_bytes] = rt->bps >> 2 |
						   (port->ch.aux_fmt << 6);

			/* Data channel segment पूर्णांकerval not multiple of 3 */
			exp = seg_पूर्णांकerval % 3;
			अगर (exp)
				wbuf[txn.msg->num_bytes] |= BIT(5);

			txn.msg->num_bytes++;
			wbuf[txn.msg->num_bytes++] = exp << 4 | rt->prot;

			अगर (rt->prot == SLIM_PROTO_ISO)
				wbuf[txn.msg->num_bytes++] =
						port->ch.prrate |
						SLIM_CHANNEL_CONTENT_FL;
			अन्यथा
				wbuf[txn.msg->num_bytes++] =  port->ch.prrate;

			ret = slim_alloc_txn_tid(ctrl, &txn);
			अगर (ret) अणु
				dev_err(&sdev->dev, "Fail to allocate TID\n");
				वापस -ENXIO;
			पूर्ण
			wbuf[txn.msg->num_bytes++] = txn.tid;
		पूर्ण
		wbuf[txn.msg->num_bytes++] = port->ch.id;
	पूर्ण

	txn.mc = SLIM_USR_MC_DEF_ACT_CHAN;
	txn.rl = txn.msg->num_bytes + 4;
	ret = qcom_slim_ngd_xfer_msg_sync(ctrl, &txn);
	अगर (ret) अणु
		slim_मुक्त_txn_tid(ctrl, &txn);
		dev_err(&sdev->dev, "TX timed out:MC:0x%x,mt:0x%x", txn.mc,
				txn.mt);
		वापस ret;
	पूर्ण

	txn.mc = SLIM_USR_MC_RECONFIG_NOW;
	txn.msg->num_bytes = 2;
	wbuf[1] = sdev->laddr;
	txn.rl = txn.msg->num_bytes + 4;

	ret = slim_alloc_txn_tid(ctrl, &txn);
	अगर (ret) अणु
		dev_err(ctrl->dev, "Fail to allocate TID\n");
		वापस ret;
	पूर्ण

	wbuf[0] = txn.tid;
	ret = qcom_slim_ngd_xfer_msg_sync(ctrl, &txn);
	अगर (ret) अणु
		slim_मुक्त_txn_tid(ctrl, &txn);
		dev_err(&sdev->dev, "TX timed out:MC:0x%x,mt:0x%x", txn.mc,
				txn.mt);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_slim_ngd_get_laddr(काष्ठा slim_controller *ctrl,
				   काष्ठा slim_eaddr *ea, u8 *laddr)
अणु
	काष्ठा slim_val_inf msg =  अणु0पूर्ण;
	u8 failed_ea[6] = अणु0, 0, 0, 0, 0, 0पूर्ण;
	काष्ठा slim_msg_txn txn;
	u8 wbuf[10] = अणु0पूर्ण;
	u8 rbuf[10] = अणु0पूर्ण;
	पूर्णांक ret;

	txn.mt = SLIM_MSG_MT_DEST_REFERRED_USER;
	txn.dt = SLIM_MSG_DEST_LOGICALADDR;
	txn.la = SLIM_LA_MGR;
	txn.ec = 0;

	txn.mc = SLIM_USR_MC_ADDR_QUERY;
	txn.rl = 11;
	txn.msg = &msg;
	txn.msg->num_bytes = 7;
	txn.msg->wbuf = wbuf;
	txn.msg->rbuf = rbuf;

	ret = slim_alloc_txn_tid(ctrl, &txn);
	अगर (ret < 0)
		वापस ret;

	wbuf[0] = (u8)txn.tid;
	स_नकल(&wbuf[1], ea, माप(*ea));

	ret = qcom_slim_ngd_xfer_msg_sync(ctrl, &txn);
	अगर (ret) अणु
		slim_मुक्त_txn_tid(ctrl, &txn);
		वापस ret;
	पूर्ण

	अगर (!स_भेद(rbuf, failed_ea, 6))
		वापस -ENXIO;

	*laddr = rbuf[6];

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_slim_ngd_निकास_dma(काष्ठा qcom_slim_ngd_ctrl *ctrl)
अणु
	अगर (ctrl->dma_rx_channel) अणु
		dmaengine_terminate_sync(ctrl->dma_rx_channel);
		dma_release_channel(ctrl->dma_rx_channel);
	पूर्ण

	अगर (ctrl->dma_tx_channel) अणु
		dmaengine_terminate_sync(ctrl->dma_tx_channel);
		dma_release_channel(ctrl->dma_tx_channel);
	पूर्ण

	ctrl->dma_tx_channel = ctrl->dma_rx_channel = शून्य;

	वापस 0;
पूर्ण

अटल व्योम qcom_slim_ngd_setup(काष्ठा qcom_slim_ngd_ctrl *ctrl)
अणु
	u32 cfg = पढ़ोl_relaxed(ctrl->ngd->base);

	अगर (ctrl->state == QCOM_SLIM_NGD_CTRL_DOWN)
		qcom_slim_ngd_init_dma(ctrl);

	/* By शेष enable message queues */
	cfg |= NGD_CFG_RX_MSGQ_EN;
	cfg |= NGD_CFG_TX_MSGQ_EN;

	/* Enable NGD अगर it's not alपढ़ोy enabled*/
	अगर (!(cfg & NGD_CFG_ENABLE))
		cfg |= NGD_CFG_ENABLE;

	ग_लिखोl_relaxed(cfg, ctrl->ngd->base);
पूर्ण

अटल पूर्णांक qcom_slim_ngd_घातer_up(काष्ठा qcom_slim_ngd_ctrl *ctrl)
अणु
	क्रमागत qcom_slim_ngd_state cur_state = ctrl->state;
	काष्ठा qcom_slim_ngd *ngd = ctrl->ngd;
	u32 laddr, rx_msgq;
	पूर्णांक समयout, ret = 0;

	अगर (ctrl->state == QCOM_SLIM_NGD_CTRL_DOWN) अणु
		समयout = रुको_क्रम_completion_समयout(&ctrl->qmi.qmi_comp, HZ);
		अगर (!समयout)
			वापस -EREMOTEIO;
	पूर्ण

	अगर (ctrl->state == QCOM_SLIM_NGD_CTRL_ASLEEP ||
		ctrl->state == QCOM_SLIM_NGD_CTRL_DOWN) अणु
		ret = qcom_slim_qmi_घातer_request(ctrl, true);
		अगर (ret) अणु
			dev_err(ctrl->dev, "SLIM QMI power request failed:%d\n",
					ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ctrl->ver = पढ़ोl_relaxed(ctrl->base);
	/* Version info in 16 MSbits */
	ctrl->ver >>= 16;

	laddr = पढ़ोl_relaxed(ngd->base + NGD_STATUS);
	अगर (laddr & NGD_LADDR) अणु
		/*
		 * बाह्यal MDM restart हाल where ADSP itself was active framer
		 * For example, modem restarted when playback was active
		 */
		अगर (cur_state == QCOM_SLIM_NGD_CTRL_AWAKE) अणु
			dev_info(ctrl->dev, "Subsys restart: ADSP active framer\n");
			वापस 0;
		पूर्ण
		वापस 0;
	पूर्ण

	ग_लिखोl_relaxed(DEF_NGD_INT_MASK, ngd->base + NGD_INT_EN);
	rx_msgq = पढ़ोl_relaxed(ngd->base + NGD_RX_MSGQ_CFG);

	ग_लिखोl_relaxed(rx_msgq|SLIM_RX_MSGQ_TIMEOUT_VAL,
				ngd->base + NGD_RX_MSGQ_CFG);
	qcom_slim_ngd_setup(ctrl);

	समयout = रुको_क्रम_completion_समयout(&ctrl->reconf, HZ);
	अगर (!समयout) अणु
		dev_err(ctrl->dev, "capability exchange timed-out\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qcom_slim_ngd_notअगरy_slaves(काष्ठा qcom_slim_ngd_ctrl *ctrl)
अणु
	काष्ठा slim_device *sbdev;
	काष्ठा device_node *node;

	क्रम_each_child_of_node(ctrl->ngd->pdev->dev.of_node, node) अणु
		sbdev = of_slim_get_device(&ctrl->ctrl, node);
		अगर (!sbdev)
			जारी;

		अगर (slim_get_logical_addr(sbdev))
			dev_err(ctrl->dev, "Failed to get logical address\n");
	पूर्ण
पूर्ण

अटल व्योम qcom_slim_ngd_master_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qcom_slim_ngd_ctrl *ctrl;
	काष्ठा slim_msg_txn txn;
	काष्ठा slim_val_inf msg = अणु0पूर्ण;
	पूर्णांक retries = 0;
	u8 wbuf[8];
	पूर्णांक ret = 0;

	ctrl = container_of(work, काष्ठा qcom_slim_ngd_ctrl, m_work);
	txn.dt = SLIM_MSG_DEST_LOGICALADDR;
	txn.ec = 0;
	txn.mc = SLIM_USR_MC_REPORT_SATELLITE;
	txn.mt = SLIM_MSG_MT_SRC_REFERRED_USER;
	txn.la = SLIM_LA_MGR;
	wbuf[0] = SAT_MAGIC_LSB;
	wbuf[1] = SAT_MAGIC_MSB;
	wbuf[2] = SAT_MSG_VER;
	wbuf[3] = SAT_MSG_PROT;
	txn.msg = &msg;
	txn.msg->wbuf = wbuf;
	txn.msg->num_bytes = 4;
	txn.rl = 8;

	dev_info(ctrl->dev, "SLIM SAT: Rcvd master capability\n");

capability_retry:
	ret = qcom_slim_ngd_xfer_msg(&ctrl->ctrl, &txn);
	अगर (!ret) अणु
		अगर (ctrl->state >= QCOM_SLIM_NGD_CTRL_ASLEEP)
			complete(&ctrl->reconf);
		अन्यथा
			dev_err(ctrl->dev, "unexpected state:%d\n",
						ctrl->state);

		अगर (ctrl->state == QCOM_SLIM_NGD_CTRL_DOWN)
			qcom_slim_ngd_notअगरy_slaves(ctrl);

	पूर्ण अन्यथा अगर (ret == -EIO) अणु
		dev_err(ctrl->dev, "capability message NACKed, retrying\n");
		अगर (retries < INIT_MX_RETRIES) अणु
			msleep(DEF_RETRY_MS);
			retries++;
			जाओ capability_retry;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(ctrl->dev, "SLIM: capability TX failed:%d\n", ret);
	पूर्ण
पूर्ण

अटल पूर्णांक qcom_slim_ngd_update_device_status(काष्ठा device *dev, व्योम *null)
अणु
	slim_report_असलent(to_slim_device(dev));

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_slim_ngd_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा qcom_slim_ngd_ctrl *ctrl = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (!ctrl->qmi.handle)
		वापस 0;

	अगर (ctrl->state >= QCOM_SLIM_NGD_CTRL_ASLEEP)
		ret = qcom_slim_ngd_घातer_up(ctrl);
	अगर (ret) अणु
		/* Did SSR cause this घातer up failure */
		अगर (ctrl->state != QCOM_SLIM_NGD_CTRL_DOWN)
			ctrl->state = QCOM_SLIM_NGD_CTRL_ASLEEP;
		अन्यथा
			dev_err(ctrl->dev, "HW wakeup attempt during SSR\n");
	पूर्ण अन्यथा अणु
		ctrl->state = QCOM_SLIM_NGD_CTRL_AWAKE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_slim_ngd_enable(काष्ठा qcom_slim_ngd_ctrl *ctrl, bool enable)
अणु
	अगर (enable) अणु
		पूर्णांक ret = qcom_slim_qmi_init(ctrl, false);

		अगर (ret) अणु
			dev_err(ctrl->dev, "qmi init fail, ret:%d, state:%d\n",
				ret, ctrl->state);
			वापस ret;
		पूर्ण
		/* controller state should be in sync with framework state */
		complete(&ctrl->qmi.qmi_comp);
		अगर (!pm_runसमय_enabled(ctrl->dev) ||
				!pm_runसमय_suspended(ctrl->dev))
			qcom_slim_ngd_runसमय_resume(ctrl->dev);
		अन्यथा
			pm_runसमय_resume(ctrl->dev);
		pm_runसमय_mark_last_busy(ctrl->dev);
		pm_runसमय_put(ctrl->dev);

		ret = slim_रेजिस्टर_controller(&ctrl->ctrl);
		अगर (ret) अणु
			dev_err(ctrl->dev, "error adding slim controller\n");
			वापस ret;
		पूर्ण

		dev_info(ctrl->dev, "SLIM controller Registered\n");
	पूर्ण अन्यथा अणु
		qcom_slim_qmi_निकास(ctrl);
		slim_unरेजिस्टर_controller(&ctrl->ctrl);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_slim_ngd_qmi_new_server(काष्ठा qmi_handle *hdl,
					काष्ठा qmi_service *service)
अणु
	काष्ठा qcom_slim_ngd_qmi *qmi =
		container_of(hdl, काष्ठा qcom_slim_ngd_qmi, svc_event_hdl);
	काष्ठा qcom_slim_ngd_ctrl *ctrl =
		container_of(qmi, काष्ठा qcom_slim_ngd_ctrl, qmi);

	qmi->svc_info.sq_family = AF_QIPCRTR;
	qmi->svc_info.sq_node = service->node;
	qmi->svc_info.sq_port = service->port;

	complete(&ctrl->qmi_up);

	वापस 0;
पूर्ण

अटल व्योम qcom_slim_ngd_qmi_del_server(काष्ठा qmi_handle *hdl,
					 काष्ठा qmi_service *service)
अणु
	काष्ठा qcom_slim_ngd_qmi *qmi =
		container_of(hdl, काष्ठा qcom_slim_ngd_qmi, svc_event_hdl);
	काष्ठा qcom_slim_ngd_ctrl *ctrl =
		container_of(qmi, काष्ठा qcom_slim_ngd_ctrl, qmi);

	reinit_completion(&ctrl->qmi_up);
	qmi->svc_info.sq_node = 0;
	qmi->svc_info.sq_port = 0;
पूर्ण

अटल स्थिर काष्ठा qmi_ops qcom_slim_ngd_qmi_svc_event_ops = अणु
	.new_server = qcom_slim_ngd_qmi_new_server,
	.del_server = qcom_slim_ngd_qmi_del_server,
पूर्ण;

अटल पूर्णांक qcom_slim_ngd_qmi_svc_event_init(काष्ठा qcom_slim_ngd_ctrl *ctrl)
अणु
	काष्ठा qcom_slim_ngd_qmi *qmi = &ctrl->qmi;
	पूर्णांक ret;

	ret = qmi_handle_init(&qmi->svc_event_hdl, 0,
				&qcom_slim_ngd_qmi_svc_event_ops, शून्य);
	अगर (ret < 0) अणु
		dev_err(ctrl->dev, "qmi_handle_init failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = qmi_add_lookup(&qmi->svc_event_hdl, SLIMBUS_QMI_SVC_ID,
			SLIMBUS_QMI_SVC_V1, SLIMBUS_QMI_INS_ID);
	अगर (ret < 0) अणु
		dev_err(ctrl->dev, "qmi_add_lookup failed: %d\n", ret);
		qmi_handle_release(&qmi->svc_event_hdl);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम qcom_slim_ngd_qmi_svc_event_deinit(काष्ठा qcom_slim_ngd_qmi *qmi)
अणु
	qmi_handle_release(&qmi->svc_event_hdl);
पूर्ण

अटल काष्ठा platक्रमm_driver qcom_slim_ngd_driver;
#घोषणा QCOM_SLIM_NGD_DRV_NAME	"qcom,slim-ngd"

अटल स्थिर काष्ठा of_device_id qcom_slim_ngd_dt_match[] = अणु
	अणु
		.compatible = "qcom,slim-ngd-v1.5.0",
		.data = &ngd_v1_5_offset_info,
	पूर्ण,अणु
		.compatible = "qcom,slim-ngd-v2.1.0",
		.data = &ngd_v1_5_offset_info,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, qcom_slim_ngd_dt_match);

अटल व्योम qcom_slim_ngd_करोwn(काष्ठा qcom_slim_ngd_ctrl *ctrl)
अणु
	mutex_lock(&ctrl->ssr_lock);
	device_क्रम_each_child(ctrl->ctrl.dev, शून्य,
			      qcom_slim_ngd_update_device_status);
	qcom_slim_ngd_enable(ctrl, false);
	mutex_unlock(&ctrl->ssr_lock);
पूर्ण

अटल व्योम qcom_slim_ngd_up_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qcom_slim_ngd_ctrl *ctrl;

	ctrl = container_of(work, काष्ठा qcom_slim_ngd_ctrl, ngd_up_work);

	/* Make sure qmi service is up beक्रमe continuing */
	रुको_क्रम_completion_पूर्णांकerruptible(&ctrl->qmi_up);

	mutex_lock(&ctrl->ssr_lock);
	qcom_slim_ngd_enable(ctrl, true);
	mutex_unlock(&ctrl->ssr_lock);
पूर्ण

अटल पूर्णांक qcom_slim_ngd_ssr_pdr_notअगरy(काष्ठा qcom_slim_ngd_ctrl *ctrl,
					अचिन्हित दीर्घ action)
अणु
	चयन (action) अणु
	हाल QCOM_SSR_BEFORE_SHUTDOWN:
	हाल SERVREG_SERVICE_STATE_DOWN:
		/* Make sure the last dma xfer is finished */
		mutex_lock(&ctrl->tx_lock);
		अगर (ctrl->state != QCOM_SLIM_NGD_CTRL_DOWN) अणु
			pm_runसमय_get_noresume(ctrl->dev);
			ctrl->state = QCOM_SLIM_NGD_CTRL_DOWN;
			qcom_slim_ngd_करोwn(ctrl);
			qcom_slim_ngd_निकास_dma(ctrl);
		पूर्ण
		mutex_unlock(&ctrl->tx_lock);
		अवरोध;
	हाल QCOM_SSR_AFTER_POWERUP:
	हाल SERVREG_SERVICE_STATE_UP:
		schedule_work(&ctrl->ngd_up_work);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक qcom_slim_ngd_ssr_notअगरy(काष्ठा notअगरier_block *nb,
				    अचिन्हित दीर्घ action,
				    व्योम *data)
अणु
	काष्ठा qcom_slim_ngd_ctrl *ctrl = container_of(nb,
					       काष्ठा qcom_slim_ngd_ctrl, nb);

	वापस qcom_slim_ngd_ssr_pdr_notअगरy(ctrl, action);
पूर्ण

अटल व्योम slim_pd_status(पूर्णांक state, अक्षर *svc_path, व्योम *priv)
अणु
	काष्ठा qcom_slim_ngd_ctrl *ctrl = (काष्ठा qcom_slim_ngd_ctrl *)priv;

	qcom_slim_ngd_ssr_pdr_notअगरy(ctrl, state);
पूर्ण
अटल पूर्णांक of_qcom_slim_ngd_रेजिस्टर(काष्ठा device *parent,
				     काष्ठा qcom_slim_ngd_ctrl *ctrl)
अणु
	स्थिर काष्ठा ngd_reg_offset_data *data;
	काष्ठा qcom_slim_ngd *ngd;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *node;
	u32 id;

	match = of_match_node(qcom_slim_ngd_dt_match, parent->of_node);
	data = match->data;
	क्रम_each_available_child_of_node(parent->of_node, node) अणु
		अगर (of_property_पढ़ो_u32(node, "reg", &id))
			जारी;

		ngd = kzalloc(माप(*ngd), GFP_KERNEL);
		अगर (!ngd) अणु
			of_node_put(node);
			वापस -ENOMEM;
		पूर्ण

		ngd->pdev = platक्रमm_device_alloc(QCOM_SLIM_NGD_DRV_NAME, id);
		अगर (!ngd->pdev) अणु
			kमुक्त(ngd);
			of_node_put(node);
			वापस -ENOMEM;
		पूर्ण
		ngd->id = id;
		ngd->pdev->dev.parent = parent;
		ngd->pdev->driver_override = QCOM_SLIM_NGD_DRV_NAME;
		ngd->pdev->dev.of_node = node;
		ctrl->ngd = ngd;

		platक्रमm_device_add(ngd->pdev);
		ngd->base = ctrl->base + ngd->id * data->offset +
					(ngd->id - 1) * data->size;

		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक qcom_slim_ngd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा qcom_slim_ngd_ctrl *ctrl = dev_get_drvdata(dev->parent);
	पूर्णांक ret;

	ctrl->ctrl.dev = dev;

	platक्रमm_set_drvdata(pdev, ctrl);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, QCOM_SLIM_NGD_AUTOSUSPEND);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_get_noresume(dev);
	ret = qcom_slim_ngd_qmi_svc_event_init(ctrl);
	अगर (ret) अणु
		dev_err(&pdev->dev, "QMI service registration failed:%d", ret);
		वापस ret;
	पूर्ण

	INIT_WORK(&ctrl->m_work, qcom_slim_ngd_master_worker);
	INIT_WORK(&ctrl->ngd_up_work, qcom_slim_ngd_up_worker);
	ctrl->mwq = create_singlethपढ़ो_workqueue("ngd_master");
	अगर (!ctrl->mwq) अणु
		dev_err(&pdev->dev, "Failed to start master worker\n");
		ret = -ENOMEM;
		जाओ wq_err;
	पूर्ण

	वापस 0;
wq_err:
	qcom_slim_ngd_qmi_svc_event_deinit(&ctrl->qmi);
	अगर (ctrl->mwq)
		destroy_workqueue(ctrl->mwq);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_slim_ngd_ctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा qcom_slim_ngd_ctrl *ctrl;
	काष्ठा resource *res;
	पूर्णांक ret;
	काष्ठा pdr_service *pds;

	ctrl = devm_kzalloc(dev, माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl)
		वापस -ENOMEM;

	dev_set_drvdata(dev, ctrl);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ctrl->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ctrl->base))
		वापस PTR_ERR(ctrl->base);

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "no slimbus IRQ resource\n");
		वापस -ENODEV;
	पूर्ण

	ret = devm_request_irq(dev, res->start, qcom_slim_ngd_पूर्णांकerrupt,
			       IRQF_TRIGGER_HIGH, "slim-ngd", ctrl);
	अगर (ret) अणु
		dev_err(&pdev->dev, "request IRQ failed\n");
		वापस ret;
	पूर्ण

	ctrl->nb.notअगरier_call = qcom_slim_ngd_ssr_notअगरy;
	ctrl->notअगरier = qcom_रेजिस्टर_ssr_notअगरier("lpass", &ctrl->nb);
	अगर (IS_ERR(ctrl->notअगरier))
		वापस PTR_ERR(ctrl->notअगरier);

	ctrl->dev = dev;
	ctrl->framer.rootfreq = SLIM_ROOT_FREQ >> 3;
	ctrl->framer.superfreq =
		ctrl->framer.rootfreq / SLIM_CL_PER_SUPERFRAME_DIV8;

	ctrl->ctrl.a_framer = &ctrl->framer;
	ctrl->ctrl.clkgear = SLIM_MAX_CLK_GEAR;
	ctrl->ctrl.get_laddr = qcom_slim_ngd_get_laddr;
	ctrl->ctrl.enable_stream = qcom_slim_ngd_enable_stream;
	ctrl->ctrl.xfer_msg = qcom_slim_ngd_xfer_msg;
	ctrl->ctrl.wakeup = शून्य;
	ctrl->state = QCOM_SLIM_NGD_CTRL_DOWN;

	mutex_init(&ctrl->tx_lock);
	mutex_init(&ctrl->ssr_lock);
	spin_lock_init(&ctrl->tx_buf_lock);
	init_completion(&ctrl->reconf);
	init_completion(&ctrl->qmi.qmi_comp);
	init_completion(&ctrl->qmi_up);

	ctrl->pdr = pdr_handle_alloc(slim_pd_status, ctrl);
	अगर (IS_ERR(ctrl->pdr)) अणु
		dev_err(dev, "Failed to init PDR handle\n");
		वापस PTR_ERR(ctrl->pdr);
	पूर्ण

	pds = pdr_add_lookup(ctrl->pdr, "avs/audio", "msm/adsp/audio_pd");
	अगर (IS_ERR(pds) && PTR_ERR(pds) != -EALREADY) अणु
		dev_err(dev, "pdr add lookup failed: %d\n", ret);
		वापस PTR_ERR(pds);
	पूर्ण

	platक्रमm_driver_रेजिस्टर(&qcom_slim_ngd_driver);
	वापस of_qcom_slim_ngd_रेजिस्टर(dev, ctrl);
पूर्ण

अटल पूर्णांक qcom_slim_ngd_ctrl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	platक्रमm_driver_unरेजिस्टर(&qcom_slim_ngd_driver);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_slim_ngd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_slim_ngd_ctrl *ctrl = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);
	pdr_handle_release(ctrl->pdr);
	qcom_unरेजिस्टर_ssr_notअगरier(ctrl->notअगरier, &ctrl->nb);
	qcom_slim_ngd_enable(ctrl, false);
	qcom_slim_ngd_निकास_dma(ctrl);
	qcom_slim_ngd_qmi_svc_event_deinit(&ctrl->qmi);
	अगर (ctrl->mwq)
		destroy_workqueue(ctrl->mwq);

	kमुक्त(ctrl->ngd);
	ctrl->ngd = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused qcom_slim_ngd_runसमय_idle(काष्ठा device *dev)
अणु
	काष्ठा qcom_slim_ngd_ctrl *ctrl = dev_get_drvdata(dev);

	अगर (ctrl->state == QCOM_SLIM_NGD_CTRL_AWAKE)
		ctrl->state = QCOM_SLIM_NGD_CTRL_IDLE;
	pm_request_स्वतःsuspend(dev);
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक __maybe_unused qcom_slim_ngd_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा qcom_slim_ngd_ctrl *ctrl = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (!ctrl->qmi.handle)
		वापस 0;

	ret = qcom_slim_qmi_घातer_request(ctrl, false);
	अगर (ret && ret != -EBUSY)
		dev_info(ctrl->dev, "slim resource not idle:%d\n", ret);
	अगर (!ret || ret == -ETIMEDOUT)
		ctrl->state = QCOM_SLIM_NGD_CTRL_ASLEEP;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops qcom_slim_ngd_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(
		qcom_slim_ngd_runसमय_suspend,
		qcom_slim_ngd_runसमय_resume,
		qcom_slim_ngd_runसमय_idle
	)
पूर्ण;

अटल काष्ठा platक्रमm_driver qcom_slim_ngd_ctrl_driver = अणु
	.probe = qcom_slim_ngd_ctrl_probe,
	.हटाओ = qcom_slim_ngd_ctrl_हटाओ,
	.driver	= अणु
		.name = "qcom,slim-ngd-ctrl",
		.of_match_table = qcom_slim_ngd_dt_match,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver qcom_slim_ngd_driver = अणु
	.probe = qcom_slim_ngd_probe,
	.हटाओ = qcom_slim_ngd_हटाओ,
	.driver	= अणु
		.name = QCOM_SLIM_NGD_DRV_NAME,
		.pm = &qcom_slim_ngd_dev_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(qcom_slim_ngd_ctrl_driver);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Qualcomm SLIMBus NGD controller");
