<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016, Linaro Ltd.
 * Copyright (c) 2015, Sony Mobile Communications Inc.
 */
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rpmsg.h>
#समावेश <linux/soc/qcom/wcnss_ctrl.h>

#घोषणा WCNSS_REQUEST_TIMEOUT	(5 * HZ)
#घोषणा WCNSS_CBC_TIMEOUT	(10 * HZ)

#घोषणा WCNSS_ACK_DONE_BOOTING	1
#घोषणा WCNSS_ACK_COLD_BOOTING	2

#घोषणा NV_FRAGMENT_SIZE	3072
#घोषणा NVBIN_खाता		"wlan/prima/WCNSS_qcom_wlan_nv.bin"

/**
 * काष्ठा wcnss_ctrl - driver context
 * @dev:	device handle
 * @channel:	SMD channel handle
 * @ack:	completion क्रम outstanding requests
 * @cbc:	completion क्रम cbc complete indication
 * @ack_status:	status of the outstanding request
 * @probe_work: worker क्रम uploading nv binary
 */
काष्ठा wcnss_ctrl अणु
	काष्ठा device *dev;
	काष्ठा rpmsg_endpoपूर्णांक *channel;

	काष्ठा completion ack;
	काष्ठा completion cbc;
	पूर्णांक ack_status;

	काष्ठा work_काष्ठा probe_work;
पूर्ण;

/* message types */
क्रमागत अणु
	WCNSS_VERSION_REQ = 0x01000000,
	WCNSS_VERSION_RESP,
	WCNSS_DOWNLOAD_NV_REQ,
	WCNSS_DOWNLOAD_NV_RESP,
	WCNSS_UPLOAD_CAL_REQ,
	WCNSS_UPLOAD_CAL_RESP,
	WCNSS_DOWNLOAD_CAL_REQ,
	WCNSS_DOWNLOAD_CAL_RESP,
	WCNSS_VBAT_LEVEL_IND,
	WCNSS_BUILD_VERSION_REQ,
	WCNSS_BUILD_VERSION_RESP,
	WCNSS_PM_CONFIG_REQ,
	WCNSS_CBC_COMPLETE_IND,
पूर्ण;

/**
 * काष्ठा wcnss_msg_hdr - common packet header क्रम requests and responses
 * @type:	packet message type
 * @len:	total length of the packet, including this header
 */
काष्ठा wcnss_msg_hdr अणु
	u32 type;
	u32 len;
पूर्ण __packed;

/*
 * काष्ठा wcnss_version_resp - version request response
 */
काष्ठा wcnss_version_resp अणु
	काष्ठा wcnss_msg_hdr hdr;
	u8 major;
	u8 minor;
	u8 version;
	u8 revision;
पूर्ण __packed;

/**
 * काष्ठा wcnss_करोwnload_nv_req - firmware fragment request
 * @hdr:	common packet wcnss_msg_hdr header
 * @seq:	sequence number of this fragment
 * @last:	boolean indicator of this being the last fragment of the binary
 * @frag_size:	length of this fragment
 * @fragment:	fragment data
 */
काष्ठा wcnss_करोwnload_nv_req अणु
	काष्ठा wcnss_msg_hdr hdr;
	u16 seq;
	u16 last;
	u32 frag_size;
	u8 fragment[];
पूर्ण __packed;

/**
 * काष्ठा wcnss_करोwnload_nv_resp - firmware करोwnload response
 * @hdr:	common packet wcnss_msg_hdr header
 * @status:	boolean to indicate success of the करोwnload
 */
काष्ठा wcnss_करोwnload_nv_resp अणु
	काष्ठा wcnss_msg_hdr hdr;
	u8 status;
पूर्ण __packed;

/**
 * wcnss_ctrl_smd_callback() - handler from SMD responses
 * @rpdev:	remote processor message device poपूर्णांकer
 * @data:	poपूर्णांकer to the incoming data packet
 * @count:	size of the incoming data packet
 * @priv:	unused
 * @addr:	unused
 *
 * Handles any incoming packets from the remote WCNSS_CTRL service.
 */
अटल पूर्णांक wcnss_ctrl_smd_callback(काष्ठा rpmsg_device *rpdev,
				   व्योम *data,
				   पूर्णांक count,
				   व्योम *priv,
				   u32 addr)
अणु
	काष्ठा wcnss_ctrl *wcnss = dev_get_drvdata(&rpdev->dev);
	स्थिर काष्ठा wcnss_करोwnload_nv_resp *nvresp;
	स्थिर काष्ठा wcnss_version_resp *version;
	स्थिर काष्ठा wcnss_msg_hdr *hdr = data;

	चयन (hdr->type) अणु
	हाल WCNSS_VERSION_RESP:
		अगर (count != माप(*version)) अणु
			dev_err(wcnss->dev,
				"invalid size of version response\n");
			अवरोध;
		पूर्ण

		version = data;
		dev_info(wcnss->dev, "WCNSS Version %d.%d %d.%d\n",
			 version->major, version->minor,
			 version->version, version->revision);

		complete(&wcnss->ack);
		अवरोध;
	हाल WCNSS_DOWNLOAD_NV_RESP:
		अगर (count != माप(*nvresp)) अणु
			dev_err(wcnss->dev,
				"invalid size of download response\n");
			अवरोध;
		पूर्ण

		nvresp = data;
		wcnss->ack_status = nvresp->status;
		complete(&wcnss->ack);
		अवरोध;
	हाल WCNSS_CBC_COMPLETE_IND:
		dev_dbg(wcnss->dev, "cold boot complete\n");
		complete(&wcnss->cbc);
		अवरोध;
	शेष:
		dev_info(wcnss->dev, "unknown message type %d\n", hdr->type);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * wcnss_request_version() - send a version request to WCNSS
 * @wcnss:	wcnss ctrl driver context
 */
अटल पूर्णांक wcnss_request_version(काष्ठा wcnss_ctrl *wcnss)
अणु
	काष्ठा wcnss_msg_hdr msg;
	पूर्णांक ret;

	msg.type = WCNSS_VERSION_REQ;
	msg.len = माप(msg);
	ret = rpmsg_send(wcnss->channel, &msg, माप(msg));
	अगर (ret < 0)
		वापस ret;

	ret = रुको_क्रम_completion_समयout(&wcnss->ack, WCNSS_CBC_TIMEOUT);
	अगर (!ret) अणु
		dev_err(wcnss->dev, "timeout waiting for version response\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * wcnss_करोwnload_nv() - send nv binary to WCNSS
 * @wcnss:	wcnss_ctrl state handle
 * @expect_cbc:	indicator to caller that an cbc event is expected
 *
 * Returns 0 on success. Negative त्रुटि_सं on failure.
 */
अटल पूर्णांक wcnss_करोwnload_nv(काष्ठा wcnss_ctrl *wcnss, bool *expect_cbc)
अणु
	काष्ठा wcnss_करोwnload_nv_req *req;
	स्थिर काष्ठा firmware *fw;
	काष्ठा device *dev = wcnss->dev;
	स्थिर अक्षर *nvbin = NVBIN_खाता;
	स्थिर व्योम *data;
	sमाप_प्रकार left;
	पूर्णांक ret;

	req = kzalloc(माप(*req) + NV_FRAGMENT_SIZE, GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	ret = of_property_पढ़ो_string(dev->of_node, "firmware-name", &nvbin);
	अगर (ret < 0 && ret != -EINVAL)
		जाओ मुक्त_req;

	ret = request_firmware(&fw, nvbin, dev);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to load nv file %s: %d\n", nvbin, ret);
		जाओ मुक्त_req;
	पूर्ण

	data = fw->data;
	left = fw->size;

	req->hdr.type = WCNSS_DOWNLOAD_NV_REQ;
	req->hdr.len = माप(*req) + NV_FRAGMENT_SIZE;

	req->last = 0;
	req->frag_size = NV_FRAGMENT_SIZE;

	req->seq = 0;
	करो अणु
		अगर (left <= NV_FRAGMENT_SIZE) अणु
			req->last = 1;
			req->frag_size = left;
			req->hdr.len = माप(*req) + left;
		पूर्ण

		स_नकल(req->fragment, data, req->frag_size);

		ret = rpmsg_send(wcnss->channel, req, req->hdr.len);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to send smd packet\n");
			जाओ release_fw;
		पूर्ण

		/* Increment क्रम next fragment */
		req->seq++;

		data += NV_FRAGMENT_SIZE;
		left -= NV_FRAGMENT_SIZE;
	पूर्ण जबतक (left > 0);

	ret = रुको_क्रम_completion_समयout(&wcnss->ack, WCNSS_REQUEST_TIMEOUT);
	अगर (!ret) अणु
		dev_err(dev, "timeout waiting for nv upload ack\n");
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		*expect_cbc = wcnss->ack_status == WCNSS_ACK_COLD_BOOTING;
		ret = 0;
	पूर्ण

release_fw:
	release_firmware(fw);
मुक्त_req:
	kमुक्त(req);

	वापस ret;
पूर्ण

/**
 * qcom_wcnss_खोलो_channel() - खोलो additional SMD channel to WCNSS
 * @wcnss:	wcnss handle, retrieved from drvdata
 * @name:	SMD channel name
 * @cb:		callback to handle incoming data on the channel
 * @priv:	निजी data क्रम use in the call-back
 */
काष्ठा rpmsg_endpoपूर्णांक *qcom_wcnss_खोलो_channel(व्योम *wcnss, स्थिर अक्षर *name, rpmsg_rx_cb_t cb, व्योम *priv)
अणु
	काष्ठा rpmsg_channel_info chinfo;
	काष्ठा wcnss_ctrl *_wcnss = wcnss;

	strscpy(chinfo.name, name, माप(chinfo.name));
	chinfo.src = RPMSG_ADDR_ANY;
	chinfo.dst = RPMSG_ADDR_ANY;

	वापस rpmsg_create_ept(_wcnss->channel->rpdev, cb, priv, chinfo);
पूर्ण
EXPORT_SYMBOL(qcom_wcnss_खोलो_channel);

अटल व्योम wcnss_async_probe(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wcnss_ctrl *wcnss = container_of(work, काष्ठा wcnss_ctrl, probe_work);
	bool expect_cbc;
	पूर्णांक ret;

	ret = wcnss_request_version(wcnss);
	अगर (ret < 0)
		वापस;

	ret = wcnss_करोwnload_nv(wcnss, &expect_cbc);
	अगर (ret < 0)
		वापस;

	/* Wait क्रम pending cold boot completion अगर indicated by the nv करोwnloader */
	अगर (expect_cbc) अणु
		ret = रुको_क्रम_completion_समयout(&wcnss->cbc, WCNSS_REQUEST_TIMEOUT);
		अगर (!ret)
			dev_err(wcnss->dev, "expected cold boot completion\n");
	पूर्ण

	of_platक्रमm_populate(wcnss->dev->of_node, शून्य, शून्य, wcnss->dev);
पूर्ण

अटल पूर्णांक wcnss_ctrl_probe(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा wcnss_ctrl *wcnss;

	wcnss = devm_kzalloc(&rpdev->dev, माप(*wcnss), GFP_KERNEL);
	अगर (!wcnss)
		वापस -ENOMEM;

	wcnss->dev = &rpdev->dev;
	wcnss->channel = rpdev->ept;

	init_completion(&wcnss->ack);
	init_completion(&wcnss->cbc);
	INIT_WORK(&wcnss->probe_work, wcnss_async_probe);

	dev_set_drvdata(&rpdev->dev, wcnss);

	schedule_work(&wcnss->probe_work);

	वापस 0;
पूर्ण

अटल व्योम wcnss_ctrl_हटाओ(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा wcnss_ctrl *wcnss = dev_get_drvdata(&rpdev->dev);

	cancel_work_sync(&wcnss->probe_work);
	of_platक्रमm_depopulate(&rpdev->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id wcnss_ctrl_of_match[] = अणु
	अणु .compatible = "qcom,wcnss", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wcnss_ctrl_of_match);

अटल काष्ठा rpmsg_driver wcnss_ctrl_driver = अणु
	.probe = wcnss_ctrl_probe,
	.हटाओ = wcnss_ctrl_हटाओ,
	.callback = wcnss_ctrl_smd_callback,
	.drv  = अणु
		.name  = "qcom_wcnss_ctrl",
		.owner = THIS_MODULE,
		.of_match_table = wcnss_ctrl_of_match,
	पूर्ण,
पूर्ण;

module_rpmsg_driver(wcnss_ctrl_driver);

MODULE_DESCRIPTION("Qualcomm WCNSS control driver");
MODULE_LICENSE("GPL v2");
