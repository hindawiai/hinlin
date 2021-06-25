<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2011-2017, The Linux Foundation. All rights reserved.
// Copyright (c) 2018, Linaro Limited

#समावेश <linux/device.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/qcom/apr.h>
#समावेश <linux/रुको.h>
#समावेश <sound/asound.h>
#समावेश "q6adm.h"
#समावेश "q6afe.h"
#समावेश "q6core.h"
#समावेश "q6dsp-common.h"
#समावेश "q6dsp-errno.h"

#घोषणा ADM_CMD_DEVICE_OPEN_V5		0x00010326
#घोषणा ADM_CMDRSP_DEVICE_OPEN_V5	0x00010329
#घोषणा ADM_CMD_DEVICE_CLOSE_V5		0x00010327
#घोषणा ADM_CMD_MATRIX_MAP_ROUTINGS_V5	0x00010325

#घोषणा TIMEOUT_MS 1000
#घोषणा RESET_COPP_ID 99
#घोषणा INVALID_COPP_ID 0xFF
/* Definition क्रम a legacy device session. */
#घोषणा ADM_LEGACY_DEVICE_SESSION	0
#घोषणा ADM_MATRIX_ID_AUDIO_RX		0
#घोषणा ADM_MATRIX_ID_AUDIO_TX		1

काष्ठा q6copp अणु
	पूर्णांक afe_port;
	पूर्णांक copp_idx;
	पूर्णांक id;
	पूर्णांक topology;
	पूर्णांक mode;
	पूर्णांक rate;
	पूर्णांक bit_width;
	पूर्णांक channels;
	पूर्णांक app_type;
	पूर्णांक acdb_id;

	काष्ठा aprv2_ibasic_rsp_result_t result;
	काष्ठा kref refcount;
	रुको_queue_head_t रुको;
	काष्ठा list_head node;
	काष्ठा q6adm *adm;
पूर्ण;

काष्ठा q6adm अणु
	काष्ठा apr_device *apr;
	काष्ठा device *dev;
	काष्ठा q6core_svc_api_info ainfo;
	अचिन्हित दीर्घ copp_biपंचांगap[AFE_MAX_PORTS];
	काष्ठा list_head copps_list;
	spinlock_t copps_list_lock;
	काष्ठा aprv2_ibasic_rsp_result_t result;
	काष्ठा mutex lock;
	रुको_queue_head_t matrix_map_रुको;
पूर्ण;

काष्ठा q6adm_cmd_device_खोलो_v5 अणु
	u16 flags;
	u16 mode_of_operation;
	u16 endpoपूर्णांक_id_1;
	u16 endpoपूर्णांक_id_2;
	u32 topology_id;
	u16 dev_num_channel;
	u16 bit_width;
	u32 sample_rate;
	u8 dev_channel_mapping[8];
पूर्ण __packed;

काष्ठा q6adm_cmd_matrix_map_routings_v5 अणु
	u32 matrix_id;
	u32 num_sessions;
पूर्ण __packed;

काष्ठा q6adm_session_map_node_v5 अणु
	u16 session_id;
	u16 num_copps;
पूर्ण __packed;

अटल काष्ठा q6copp *q6adm_find_copp(काष्ठा q6adm *adm, पूर्णांक port_idx,
				  पूर्णांक copp_idx)
अणु
	काष्ठा q6copp *c = शून्य;
	काष्ठा q6copp *ret = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adm->copps_list_lock, flags);
	list_क्रम_each_entry(c, &adm->copps_list, node) अणु
		अगर ((port_idx == c->afe_port) && (copp_idx == c->copp_idx)) अणु
			ret = c;
			kref_get(&c->refcount);
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&adm->copps_list_lock, flags);

	वापस ret;

पूर्ण

अटल व्योम q6adm_मुक्त_copp(काष्ठा kref *ref)
अणु
	काष्ठा q6copp *c = container_of(ref, काष्ठा q6copp, refcount);
	काष्ठा q6adm *adm = c->adm;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adm->copps_list_lock, flags);
	clear_bit(c->copp_idx, &adm->copp_biपंचांगap[c->afe_port]);
	list_del(&c->node);
	spin_unlock_irqrestore(&adm->copps_list_lock, flags);
	kमुक्त(c);
पूर्ण

अटल पूर्णांक q6adm_callback(काष्ठा apr_device *adev, काष्ठा apr_resp_pkt *data)
अणु
	काष्ठा aprv2_ibasic_rsp_result_t *result = data->payload;
	पूर्णांक port_idx, copp_idx;
	काष्ठा apr_hdr *hdr = &data->hdr;
	काष्ठा q6copp *copp;
	काष्ठा q6adm *adm = dev_get_drvdata(&adev->dev);

	अगर (!data->payload_size)
		वापस 0;

	copp_idx = (hdr->token) & 0XFF;
	port_idx = ((hdr->token) >> 16) & 0xFF;
	अगर (port_idx < 0 || port_idx >= AFE_MAX_PORTS) अणु
		dev_err(&adev->dev, "Invalid port idx %d token %d\n",
		       port_idx, hdr->token);
		वापस 0;
	पूर्ण
	अगर (copp_idx < 0 || copp_idx >= MAX_COPPS_PER_PORT) अणु
		dev_err(&adev->dev, "Invalid copp idx %d token %d\n",
			copp_idx, hdr->token);
		वापस 0;
	पूर्ण

	चयन (hdr->opcode) अणु
	हाल APR_BASIC_RSP_RESULT: अणु
		अगर (result->status != 0) अणु
			dev_err(&adev->dev, "cmd = 0x%x return error = 0x%x\n",
				result->opcode, result->status);
		पूर्ण
		चयन (result->opcode) अणु
		हाल ADM_CMD_DEVICE_OPEN_V5:
		हाल ADM_CMD_DEVICE_CLOSE_V5:
			copp = q6adm_find_copp(adm, port_idx, copp_idx);
			अगर (!copp)
				वापस 0;

			copp->result = *result;
			wake_up(&copp->रुको);
			kref_put(&copp->refcount, q6adm_मुक्त_copp);
			अवरोध;
		हाल ADM_CMD_MATRIX_MAP_ROUTINGS_V5:
			adm->result = *result;
			wake_up(&adm->matrix_map_रुको);
			अवरोध;

		शेष:
			dev_err(&adev->dev, "Unknown Cmd: 0x%x\n",
				result->opcode);
			अवरोध;
		पूर्ण
		वापस 0;
	पूर्ण
	हाल ADM_CMDRSP_DEVICE_OPEN_V5: अणु
		काष्ठा adm_cmd_rsp_device_खोलो_v5 अणु
			u32 status;
			u16 copp_id;
			u16 reserved;
		पूर्ण __packed * खोलो = data->payload;

		copp = q6adm_find_copp(adm, port_idx, copp_idx);
		अगर (!copp)
			वापस 0;

		अगर (खोलो->copp_id == INVALID_COPP_ID) अणु
			dev_err(&adev->dev, "Invalid coppid rxed %d\n",
				खोलो->copp_id);
			copp->result.status = ADSP_EBADPARAM;
			wake_up(&copp->रुको);
			kref_put(&copp->refcount, q6adm_मुक्त_copp);
			अवरोध;
		पूर्ण
		copp->result.opcode = hdr->opcode;
		copp->id = खोलो->copp_id;
		wake_up(&copp->रुको);
		kref_put(&copp->refcount, q6adm_मुक्त_copp);
	पूर्ण
	अवरोध;
	शेष:
		dev_err(&adev->dev, "Unknown cmd:0x%x\n",
		       hdr->opcode);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा q6copp *q6adm_alloc_copp(काष्ठा q6adm *adm, पूर्णांक port_idx)
अणु
	काष्ठा q6copp *c;
	पूर्णांक idx;

	idx = find_first_zero_bit(&adm->copp_biपंचांगap[port_idx],
				  MAX_COPPS_PER_PORT);

	अगर (idx > MAX_COPPS_PER_PORT)
		वापस ERR_PTR(-EBUSY);

	c = kzalloc(माप(*c), GFP_ATOMIC);
	अगर (!c)
		वापस ERR_PTR(-ENOMEM);

	set_bit(idx, &adm->copp_biपंचांगap[port_idx]);
	c->copp_idx = idx;
	c->afe_port = port_idx;
	c->adm = adm;

	init_रुकोqueue_head(&c->रुको);

	वापस c;
पूर्ण

अटल पूर्णांक q6adm_apr_send_copp_pkt(काष्ठा q6adm *adm, काष्ठा q6copp *copp,
				   काष्ठा apr_pkt *pkt, uपूर्णांक32_t rsp_opcode)
अणु
	काष्ठा device *dev = adm->dev;
	uपूर्णांक32_t opcode = pkt->hdr.opcode;
	पूर्णांक ret;

	mutex_lock(&adm->lock);
	copp->result.opcode = 0;
	copp->result.status = 0;
	ret = apr_send_pkt(adm->apr, pkt);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to send APR packet\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* Wait क्रम the callback with copp id */
	अगर (rsp_opcode)
		ret = रुको_event_समयout(copp->रुको,
					 (copp->result.opcode == opcode) ||
					 (copp->result.opcode == rsp_opcode),
					 msecs_to_jअगरfies(TIMEOUT_MS));
	अन्यथा
		ret = रुको_event_समयout(copp->रुको,
					 (copp->result.opcode == opcode),
					 msecs_to_jअगरfies(TIMEOUT_MS));

	अगर (!ret) अणु
		dev_err(dev, "ADM copp cmd timedout\n");
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अगर (copp->result.status > 0) अणु
		dev_err(dev, "DSP returned error[%d]\n",
			copp->result.status);
		ret = -EINVAL;
	पूर्ण

err:
	mutex_unlock(&adm->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक q6adm_device_बंद(काष्ठा q6adm *adm, काष्ठा q6copp *copp,
			      पूर्णांक port_id, पूर्णांक copp_idx)
अणु
	काष्ठा apr_pkt बंद;

	बंद.hdr.hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_SEQ_CMD,
					APR_HDR_LEN(APR_HDR_SIZE),
					APR_PKT_VER);
	बंद.hdr.pkt_size = माप(बंद);
	बंद.hdr.src_port = port_id;
	बंद.hdr.dest_port = copp->id;
	बंद.hdr.token = port_id << 16 | copp_idx;
	बंद.hdr.opcode = ADM_CMD_DEVICE_CLOSE_V5;

	वापस q6adm_apr_send_copp_pkt(adm, copp, &बंद, 0);
पूर्ण

अटल काष्ठा q6copp *q6adm_find_matching_copp(काष्ठा q6adm *adm,
					       पूर्णांक port_id, पूर्णांक topology,
					       पूर्णांक mode, पूर्णांक rate,
					       पूर्णांक channel_mode, पूर्णांक bit_width,
					       पूर्णांक app_type)
अणु
	काष्ठा q6copp *c = शून्य;
	काष्ठा q6copp *ret = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adm->copps_list_lock, flags);

	list_क्रम_each_entry(c, &adm->copps_list, node) अणु
		अगर ((port_id == c->afe_port) && (topology == c->topology) &&
		    (mode == c->mode) && (rate == c->rate) &&
		    (bit_width == c->bit_width) && (app_type == c->app_type)) अणु
			ret = c;
			kref_get(&c->refcount);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&adm->copps_list_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक q6adm_device_खोलो(काष्ठा q6adm *adm, काष्ठा q6copp *copp,
			     पूर्णांक port_id, पूर्णांक path, पूर्णांक topology,
			     पूर्णांक channel_mode, पूर्णांक bit_width, पूर्णांक rate)
अणु
	काष्ठा q6adm_cmd_device_खोलो_v5 *खोलो;
	पूर्णांक afe_port = q6afe_get_port_id(port_id);
	काष्ठा apr_pkt *pkt;
	व्योम *p;
	पूर्णांक ret, pkt_size;

	pkt_size = APR_HDR_SIZE + माप(*खोलो);
	p = kzalloc(pkt_size, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	खोलो = p + APR_HDR_SIZE;
	pkt->hdr.hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_SEQ_CMD,
					   APR_HDR_LEN(APR_HDR_SIZE),
					   APR_PKT_VER);
	pkt->hdr.pkt_size = pkt_size;
	pkt->hdr.src_port = afe_port;
	pkt->hdr.dest_port = afe_port;
	pkt->hdr.token = port_id << 16 | copp->copp_idx;
	pkt->hdr.opcode = ADM_CMD_DEVICE_OPEN_V5;
	खोलो->flags = ADM_LEGACY_DEVICE_SESSION;
	खोलो->mode_of_operation = path;
	खोलो->endpoपूर्णांक_id_1 = afe_port;
	खोलो->topology_id = topology;
	खोलो->dev_num_channel = channel_mode & 0x00FF;
	खोलो->bit_width = bit_width;
	खोलो->sample_rate = rate;

	ret = q6dsp_map_channels(&खोलो->dev_channel_mapping[0],
				 channel_mode);
	अगर (ret)
		जाओ err;

	ret = q6adm_apr_send_copp_pkt(adm, copp, pkt,
				      ADM_CMDRSP_DEVICE_OPEN_V5);

err:
	kमुक्त(pkt);
	वापस ret;
पूर्ण

/**
 * q6adm_खोलो() - खोलो adm and grab a मुक्त copp
 *
 * @dev: Poपूर्णांकer to adm child device.
 * @port_id: port id
 * @path: playback or capture path.
 * @rate: rate at which copp is required.
 * @channel_mode: channel mode
 * @topology: adm topology id
 * @perf_mode: perक्रमmace mode.
 * @bit_width: audio sample bit width
 * @app_type: Application type.
 * @acdb_id: ACDB id
 *
 * Return: Will be an negative on error or a valid copp poपूर्णांकer on success.
 */
काष्ठा q6copp *q6adm_खोलो(काष्ठा device *dev, पूर्णांक port_id, पूर्णांक path, पूर्णांक rate,
	       पूर्णांक channel_mode, पूर्णांक topology, पूर्णांक perf_mode,
	       uपूर्णांक16_t bit_width, पूर्णांक app_type, पूर्णांक acdb_id)
अणु
	काष्ठा q6adm *adm = dev_get_drvdata(dev->parent);
	काष्ठा q6copp *copp;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (port_id < 0) अणु
		dev_err(dev, "Invalid port_id 0x%x\n", port_id);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	copp = q6adm_find_matching_copp(adm, port_id, topology, perf_mode,
				      rate, channel_mode, bit_width, app_type);
	अगर (copp) अणु
		dev_err(dev, "Found Matching Copp 0x%x\n", copp->copp_idx);
		वापस copp;
	पूर्ण

	spin_lock_irqsave(&adm->copps_list_lock, flags);
	copp = q6adm_alloc_copp(adm, port_id);
	अगर (IS_ERR(copp)) अणु
		spin_unlock_irqrestore(&adm->copps_list_lock, flags);
		वापस ERR_CAST(copp);
	पूर्ण

	list_add_tail(&copp->node, &adm->copps_list);
	spin_unlock_irqrestore(&adm->copps_list_lock, flags);

	kref_init(&copp->refcount);
	copp->topology = topology;
	copp->mode = perf_mode;
	copp->rate = rate;
	copp->channels = channel_mode;
	copp->bit_width = bit_width;
	copp->app_type = app_type;

	ret = q6adm_device_खोलो(adm, copp, port_id, path, topology,
				channel_mode, bit_width, rate);
	अगर (ret < 0) अणु
		kref_put(&copp->refcount, q6adm_मुक्त_copp);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस copp;
पूर्ण
EXPORT_SYMBOL_GPL(q6adm_खोलो);

/**
 * q6adm_get_copp_id() - get copp index
 *
 * @copp: Poपूर्णांकer to valid copp
 *
 * Return: Will be an negative on error or a valid copp index on success.
 **/
पूर्णांक q6adm_get_copp_id(काष्ठा q6copp *copp)
अणु
	अगर (!copp)
		वापस -EINVAL;

	वापस copp->copp_idx;
पूर्ण
EXPORT_SYMBOL_GPL(q6adm_get_copp_id);

/**
 * q6adm_matrix_map() - Map यंत्र streams and afe ports using payload
 *
 * @dev: Poपूर्णांकer to adm child device.
 * @path: playback or capture path.
 * @payload_map: map between session id and afe ports.
 * @perf_mode: Perक्रमmace mode.
 *
 * Return: Will be an negative on error or a zero on success.
 */
पूर्णांक q6adm_matrix_map(काष्ठा device *dev, पूर्णांक path,
		     काष्ठा route_payload payload_map, पूर्णांक perf_mode)
अणु
	काष्ठा q6adm *adm = dev_get_drvdata(dev->parent);
	काष्ठा q6adm_cmd_matrix_map_routings_v5 *route;
	काष्ठा q6adm_session_map_node_v5 *node;
	काष्ठा apr_pkt *pkt;
	uपूर्णांक16_t *copps_list;
	पूर्णांक pkt_size, ret, i, copp_idx;
	व्योम *matrix_map = शून्य;
	काष्ठा q6copp *copp;

	/* Assumes port_ids have alपढ़ोy been validated during adm_खोलो */
	pkt_size = (APR_HDR_SIZE + माप(*route) +  माप(*node) +
		    (माप(uपूर्णांक32_t) * payload_map.num_copps));

	matrix_map = kzalloc(pkt_size, GFP_KERNEL);
	अगर (!matrix_map)
		वापस -ENOMEM;

	pkt = matrix_map;
	route = matrix_map + APR_HDR_SIZE;
	node = matrix_map + APR_HDR_SIZE + माप(*route);
	copps_list = matrix_map + APR_HDR_SIZE + माप(*route) + माप(*node);

	pkt->hdr.hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_SEQ_CMD,
					   APR_HDR_LEN(APR_HDR_SIZE),
					   APR_PKT_VER);
	pkt->hdr.pkt_size = pkt_size;
	pkt->hdr.token = 0;
	pkt->hdr.opcode = ADM_CMD_MATRIX_MAP_ROUTINGS_V5;
	route->num_sessions = 1;

	चयन (path) अणु
	हाल ADM_PATH_PLAYBACK:
		route->matrix_id = ADM_MATRIX_ID_AUDIO_RX;
		अवरोध;
	हाल ADM_PATH_LIVE_REC:
		route->matrix_id = ADM_MATRIX_ID_AUDIO_TX;
		अवरोध;
	शेष:
		dev_err(dev, "Wrong path set[%d]\n", path);
		अवरोध;
	पूर्ण

	node->session_id = payload_map.session_id;
	node->num_copps = payload_map.num_copps;

	क्रम (i = 0; i < payload_map.num_copps; i++) अणु
		पूर्णांक port_idx = payload_map.port_id[i];

		अगर (port_idx < 0) अणु
			dev_err(dev, "Invalid port_id 0x%x\n",
				payload_map.port_id[i]);
			kमुक्त(pkt);
			वापस -EINVAL;
		पूर्ण
		copp_idx = payload_map.copp_idx[i];

		copp = q6adm_find_copp(adm, port_idx, copp_idx);
		अगर (!copp) अणु
			kमुक्त(pkt);
			वापस -EINVAL;
		पूर्ण

		copps_list[i] = copp->id;
		kref_put(&copp->refcount, q6adm_मुक्त_copp);
	पूर्ण

	mutex_lock(&adm->lock);
	adm->result.status = 0;
	adm->result.opcode = 0;

	ret = apr_send_pkt(adm->apr, pkt);
	अगर (ret < 0) अणु
		dev_err(dev, "routing for stream %d failed ret %d\n",
		       payload_map.session_id, ret);
		जाओ fail_cmd;
	पूर्ण
	ret = रुको_event_समयout(adm->matrix_map_रुको,
				 adm->result.opcode == pkt->hdr.opcode,
				 msecs_to_jअगरfies(TIMEOUT_MS));
	अगर (!ret) अणु
		dev_err(dev, "routing for stream %d failed\n",
		       payload_map.session_id);
		ret = -ETIMEDOUT;
		जाओ fail_cmd;
	पूर्ण अन्यथा अगर (adm->result.status > 0) अणु
		dev_err(dev, "DSP returned error[%d]\n",
			adm->result.status);
		ret = -EINVAL;
		जाओ fail_cmd;
	पूर्ण

fail_cmd:
	mutex_unlock(&adm->lock);
	kमुक्त(pkt);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(q6adm_matrix_map);

/**
 * q6adm_बंद() - Close adm copp
 *
 * @dev: Poपूर्णांकer to adm child device.
 * @copp: poपूर्णांकer to previously खोलोed copp
 *
 * Return: Will be an negative on error or a zero on success.
 */
पूर्णांक q6adm_बंद(काष्ठा device *dev, काष्ठा q6copp *copp)
अणु
	काष्ठा q6adm *adm = dev_get_drvdata(dev->parent);
	पूर्णांक ret = 0;

	ret = q6adm_device_बंद(adm, copp, copp->afe_port, copp->copp_idx);
	अगर (ret < 0) अणु
		dev_err(adm->dev, "Failed to close copp %d\n", ret);
		वापस ret;
	पूर्ण

	kref_put(&copp->refcount, q6adm_मुक्त_copp);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(q6adm_बंद);

अटल पूर्णांक q6adm_probe(काष्ठा apr_device *adev)
अणु
	काष्ठा device *dev = &adev->dev;
	काष्ठा q6adm *adm;

	adm = devm_kzalloc(dev, माप(*adm), GFP_KERNEL);
	अगर (!adm)
		वापस -ENOMEM;

	adm->apr = adev;
	dev_set_drvdata(dev, adm);
	adm->dev = dev;
	q6core_get_svc_api_info(adev->svc_id, &adm->ainfo);
	mutex_init(&adm->lock);
	init_रुकोqueue_head(&adm->matrix_map_रुको);

	INIT_LIST_HEAD(&adm->copps_list);
	spin_lock_init(&adm->copps_list_lock);

	वापस devm_of_platक्रमm_populate(dev);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id q6adm_device_id[]  = अणु
	अणु .compatible = "qcom,q6adm" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, q6adm_device_id);
#पूर्ण_अगर

अटल काष्ठा apr_driver qcom_q6adm_driver = अणु
	.probe = q6adm_probe,
	.callback = q6adm_callback,
	.driver = अणु
		.name = "qcom-q6adm",
		.of_match_table = of_match_ptr(q6adm_device_id),
	पूर्ण,
पूर्ण;

module_apr_driver(qcom_q6adm_driver);
MODULE_DESCRIPTION("Q6 Audio Device Manager");
MODULE_LICENSE("GPL v2");
