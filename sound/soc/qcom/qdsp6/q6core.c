<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2011-2017, The Linux Foundation. All rights reserved.
// Copyright (c) 2018, Linaro Limited

#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/soc/qcom/apr.h>
#समावेश "q6core.h"
#समावेश "q6dsp-errno.h"

#घोषणा ADSP_STATE_READY_TIMEOUT_MS    3000
#घोषणा Q6_READY_TIMEOUT_MS 100
#घोषणा AVCS_CMD_ADSP_EVENT_GET_STATE		0x0001290C
#घोषणा AVCS_CMDRSP_ADSP_EVENT_GET_STATE	0x0001290D
#घोषणा AVCS_GET_VERSIONS       0x00012905
#घोषणा AVCS_GET_VERSIONS_RSP   0x00012906
#घोषणा AVCS_CMD_GET_FWK_VERSION	0x001292c
#घोषणा AVCS_CMDRSP_GET_FWK_VERSION	0x001292d

काष्ठा avcs_svc_info अणु
	uपूर्णांक32_t service_id;
	uपूर्णांक32_t version;
पूर्ण __packed;

काष्ठा avcs_cmdrsp_get_version अणु
	uपूर्णांक32_t build_id;
	uपूर्णांक32_t num_services;
	काष्ठा avcs_svc_info svc_api_info[];
पूर्ण __packed;

/* क्रम ADSP2.8 and above */
काष्ठा avcs_svc_api_info अणु
	uपूर्णांक32_t service_id;
	uपूर्णांक32_t api_version;
	uपूर्णांक32_t api_branch_version;
पूर्ण __packed;

काष्ठा avcs_cmdrsp_get_fwk_version अणु
	uपूर्णांक32_t build_major_version;
	uपूर्णांक32_t build_minor_version;
	uपूर्णांक32_t build_branch_version;
	uपूर्णांक32_t build_subbranch_version;
	uपूर्णांक32_t num_services;
	काष्ठा avcs_svc_api_info svc_api_info[];
पूर्ण __packed;

काष्ठा q6core अणु
	काष्ठा apr_device *adev;
	रुको_queue_head_t रुको;
	uपूर्णांक32_t avcs_state;
	काष्ठा mutex lock;
	bool resp_received;
	uपूर्णांक32_t num_services;
	काष्ठा avcs_cmdrsp_get_fwk_version *fwk_version;
	काष्ठा avcs_cmdrsp_get_version *svc_version;
	bool fwk_version_supported;
	bool get_state_supported;
	bool get_version_supported;
	bool is_version_requested;
पूर्ण;

अटल काष्ठा q6core *g_core;

अटल पूर्णांक q6core_callback(काष्ठा apr_device *adev, काष्ठा apr_resp_pkt *data)
अणु
	काष्ठा q6core *core = dev_get_drvdata(&adev->dev);
	काष्ठा aprv2_ibasic_rsp_result_t *result;
	काष्ठा apr_hdr *hdr = &data->hdr;

	result = data->payload;
	चयन (hdr->opcode) अणु
	हाल APR_BASIC_RSP_RESULT:अणु
		result = data->payload;
		चयन (result->opcode) अणु
		हाल AVCS_GET_VERSIONS:
			अगर (result->status == ADSP_EUNSUPPORTED)
				core->get_version_supported = false;
			core->resp_received = true;
			अवरोध;
		हाल AVCS_CMD_GET_FWK_VERSION:
			अगर (result->status == ADSP_EUNSUPPORTED)
				core->fwk_version_supported = false;
			core->resp_received = true;
			अवरोध;
		हाल AVCS_CMD_ADSP_EVENT_GET_STATE:
			अगर (result->status == ADSP_EUNSUPPORTED)
				core->get_state_supported = false;
			core->resp_received = true;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल AVCS_CMDRSP_GET_FWK_VERSION: अणु
		काष्ठा avcs_cmdrsp_get_fwk_version *fwk;

		fwk = data->payload;

		core->fwk_version = kmemdup(data->payload,
					    काष्ठा_size(fwk, svc_api_info,
							fwk->num_services),
					    GFP_ATOMIC);
		अगर (!core->fwk_version)
			वापस -ENOMEM;

		core->fwk_version_supported = true;
		core->resp_received = true;

		अवरोध;
	पूर्ण
	हाल AVCS_GET_VERSIONS_RSP: अणु
		काष्ठा avcs_cmdrsp_get_version *v;

		v = data->payload;

		core->svc_version = kmemdup(data->payload,
					    काष्ठा_size(v, svc_api_info,
							v->num_services),
					    GFP_ATOMIC);
		अगर (!core->svc_version)
			वापस -ENOMEM;

		core->get_version_supported = true;
		core->resp_received = true;

		अवरोध;
	पूर्ण
	हाल AVCS_CMDRSP_ADSP_EVENT_GET_STATE:
		core->get_state_supported = true;
		core->avcs_state = result->opcode;

		core->resp_received = true;
		अवरोध;
	शेष:
		dev_err(&adev->dev, "Message id from adsp core svc: 0x%x\n",
			hdr->opcode);
		अवरोध;
	पूर्ण

	अगर (core->resp_received)
		wake_up(&core->रुको);

	वापस 0;
पूर्ण

अटल पूर्णांक q6core_get_fwk_versions(काष्ठा q6core *core)
अणु
	काष्ठा apr_device *adev = core->adev;
	काष्ठा apr_pkt pkt;
	पूर्णांक rc;

	pkt.hdr.hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_SEQ_CMD,
				      APR_HDR_LEN(APR_HDR_SIZE), APR_PKT_VER);
	pkt.hdr.pkt_size = APR_HDR_SIZE;
	pkt.hdr.opcode = AVCS_CMD_GET_FWK_VERSION;

	rc = apr_send_pkt(adev, &pkt);
	अगर (rc < 0)
		वापस rc;

	rc = रुको_event_समयout(core->रुको, (core->resp_received),
				msecs_to_jअगरfies(Q6_READY_TIMEOUT_MS));
	अगर (rc > 0 && core->resp_received) अणु
		core->resp_received = false;

		अगर (!core->fwk_version_supported)
			वापस -ENOTSUPP;
		अन्यथा
			वापस 0;
	पूर्ण


	वापस rc;
पूर्ण

अटल पूर्णांक q6core_get_svc_versions(काष्ठा q6core *core)
अणु
	काष्ठा apr_device *adev = core->adev;
	काष्ठा apr_pkt pkt;
	पूर्णांक rc;

	pkt.hdr.hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_SEQ_CMD,
				      APR_HDR_LEN(APR_HDR_SIZE), APR_PKT_VER);
	pkt.hdr.pkt_size = APR_HDR_SIZE;
	pkt.hdr.opcode = AVCS_GET_VERSIONS;

	rc = apr_send_pkt(adev, &pkt);
	अगर (rc < 0)
		वापस rc;

	rc = रुको_event_समयout(core->रुको, (core->resp_received),
				msecs_to_jअगरfies(Q6_READY_TIMEOUT_MS));
	अगर (rc > 0 && core->resp_received) अणु
		core->resp_received = false;
		वापस 0;
	पूर्ण

	वापस rc;
पूर्ण

अटल bool __q6core_is_adsp_पढ़ोy(काष्ठा q6core *core)
अणु
	काष्ठा apr_device *adev = core->adev;
	काष्ठा apr_pkt pkt;
	पूर्णांक rc;

	core->get_state_supported = false;

	pkt.hdr.hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_SEQ_CMD,
				      APR_HDR_LEN(APR_HDR_SIZE), APR_PKT_VER);
	pkt.hdr.pkt_size = APR_HDR_SIZE;
	pkt.hdr.opcode = AVCS_CMD_ADSP_EVENT_GET_STATE;

	rc = apr_send_pkt(adev, &pkt);
	अगर (rc < 0)
		वापस false;

	rc = रुको_event_समयout(core->रुको, (core->resp_received),
				msecs_to_jअगरfies(Q6_READY_TIMEOUT_MS));
	अगर (rc > 0 && core->resp_received) अणु
		core->resp_received = false;

		अगर (core->avcs_state)
			वापस true;
	पूर्ण

	/* assume that the adsp is up अगर we not support this command */
	अगर (!core->get_state_supported)
		वापस true;

	वापस false;
पूर्ण

/**
 * q6core_get_svc_api_info() - Get version number of a service.
 *
 * @svc_id: service id of the service.
 * @ainfo: Valid काष्ठा poपूर्णांकer to fill svc api inक्रमmation.
 *
 * Return: zero on success and error code on failure or unsupported
 */
पूर्णांक q6core_get_svc_api_info(पूर्णांक svc_id, काष्ठा q6core_svc_api_info *ainfo)
अणु
	पूर्णांक i;
	पूर्णांक ret = -ENOTSUPP;

	अगर (!g_core || !ainfo)
		वापस 0;

	mutex_lock(&g_core->lock);
	अगर (!g_core->is_version_requested) अणु
		अगर (q6core_get_fwk_versions(g_core) == -ENOTSUPP)
			q6core_get_svc_versions(g_core);
		g_core->is_version_requested = true;
	पूर्ण

	अगर (g_core->fwk_version_supported) अणु
		क्रम (i = 0; i < g_core->fwk_version->num_services; i++) अणु
			काष्ठा avcs_svc_api_info *info;

			info = &g_core->fwk_version->svc_api_info[i];
			अगर (svc_id != info->service_id)
				जारी;

			ainfo->api_version = info->api_version;
			ainfo->api_branch_version = info->api_branch_version;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (g_core->get_version_supported) अणु
		क्रम (i = 0; i < g_core->svc_version->num_services; i++) अणु
			काष्ठा avcs_svc_info *info;

			info = &g_core->svc_version->svc_api_info[i];
			अगर (svc_id != info->service_id)
				जारी;

			ainfo->api_version = info->version;
			ainfo->api_branch_version = 0;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&g_core->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(q6core_get_svc_api_info);

/**
 * q6core_is_adsp_पढ़ोy() - Get status of adsp
 *
 * Return: Will be an true अगर adsp is पढ़ोy and false अगर not.
 */
bool q6core_is_adsp_पढ़ोy(व्योम)
अणु
	अचिन्हित दीर्घ  समयout;
	bool ret = false;

	अगर (!g_core)
		वापस false;

	mutex_lock(&g_core->lock);
	समयout = jअगरfies + msecs_to_jअगरfies(ADSP_STATE_READY_TIMEOUT_MS);
	क्रम (;;) अणु
		अगर (__q6core_is_adsp_पढ़ोy(g_core)) अणु
			ret = true;
			अवरोध;
		पूर्ण

		अगर (!समय_after(समयout, jअगरfies)) अणु
			ret = false;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&g_core->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(q6core_is_adsp_पढ़ोy);

अटल पूर्णांक q6core_probe(काष्ठा apr_device *adev)
अणु
	g_core = kzalloc(माप(*g_core), GFP_KERNEL);
	अगर (!g_core)
		वापस -ENOMEM;

	dev_set_drvdata(&adev->dev, g_core);

	mutex_init(&g_core->lock);
	g_core->adev = adev;
	init_रुकोqueue_head(&g_core->रुको);
	वापस 0;
पूर्ण

अटल पूर्णांक q6core_निकास(काष्ठा apr_device *adev)
अणु
	काष्ठा q6core *core = dev_get_drvdata(&adev->dev);

	अगर (core->fwk_version_supported)
		kमुक्त(core->fwk_version);
	अगर (core->get_version_supported)
		kमुक्त(core->svc_version);

	g_core = शून्य;
	kमुक्त(core);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id q6core_device_id[]  = अणु
	अणु .compatible = "qcom,q6core" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, q6core_device_id);
#पूर्ण_अगर

अटल काष्ठा apr_driver qcom_q6core_driver = अणु
	.probe = q6core_probe,
	.हटाओ = q6core_निकास,
	.callback = q6core_callback,
	.driver = अणु
		.name = "qcom-q6core",
		.of_match_table = of_match_ptr(q6core_device_id),
	पूर्ण,
पूर्ण;

module_apr_driver(qcom_q6core_driver);
MODULE_DESCRIPTION("q6 core");
MODULE_LICENSE("GPL v2");
