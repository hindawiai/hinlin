<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * WSM host पूर्णांकerface (HI) implementation क्रम
 * ST-Ericsson CW1200 mac80211 drivers.
 *
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 */

#समावेश <linux/skbuff.h>
#समावेश <linux/रुको.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/अक्रमom.h>

#समावेश "cw1200.h"
#समावेश "wsm.h"
#समावेश "bh.h"
#समावेश "sta.h"
#समावेश "debug.h"

#घोषणा WSM_CMD_TIMEOUT		(2 * HZ) /* With respect to पूर्णांकerrupt loss */
#घोषणा WSM_CMD_START_TIMEOUT	(7 * HZ)
#घोषणा WSM_CMD_RESET_TIMEOUT	(3 * HZ) /* 2 sec. समयout was observed.   */
#घोषणा WSM_CMD_MAX_TIMEOUT	(3 * HZ)

#घोषणा WSM_SKIP(buf, size)						\
	करो अणु								\
		अगर ((buf)->data + size > (buf)->end)			\
			जाओ underflow;					\
		(buf)->data += size;					\
	पूर्ण जबतक (0)

#घोषणा WSM_GET(buf, ptr, size)						\
	करो अणु								\
		अगर ((buf)->data + size > (buf)->end)			\
			जाओ underflow;					\
		स_नकल(ptr, (buf)->data, size);				\
		(buf)->data += size;					\
	पूर्ण जबतक (0)

#घोषणा __WSM_GET(buf, type, type2, cvt)				\
	(अणु								\
		type val;						\
		अगर ((buf)->data + माप(type) > (buf)->end)		\
			जाओ underflow;					\
		val = cvt(*(type2 *)(buf)->data);			\
		(buf)->data += माप(type);				\
		val;							\
	पूर्ण)

#घोषणा WSM_GET8(buf)  __WSM_GET(buf, u8, u8, (u8))
#घोषणा WSM_GET16(buf) __WSM_GET(buf, u16, __le16, __le16_to_cpu)
#घोषणा WSM_GET32(buf) __WSM_GET(buf, u32, __le32, __le32_to_cpu)

#घोषणा WSM_PUT(buf, ptr, size)						\
	करो अणु								\
		अगर ((buf)->data + size > (buf)->end)		\
			अगर (wsm_buf_reserve((buf), size))	\
				जाओ nomem;				\
		स_नकल((buf)->data, ptr, size);				\
		(buf)->data += size;					\
	पूर्ण जबतक (0)

#घोषणा __WSM_PUT(buf, val, type, type2, cvt)				\
	करो अणु								\
		अगर ((buf)->data + माप(type) > (buf)->end)		\
			अगर (wsm_buf_reserve((buf), माप(type))) \
				जाओ nomem;				\
		*(type2 *)(buf)->data = cvt(val);			\
		(buf)->data += माप(type);				\
	पूर्ण जबतक (0)

#घोषणा WSM_PUT8(buf, val)  __WSM_PUT(buf, val, u8, u8, (u8))
#घोषणा WSM_PUT16(buf, val) __WSM_PUT(buf, val, u16, __le16, __cpu_to_le16)
#घोषणा WSM_PUT32(buf, val) __WSM_PUT(buf, val, u32, __le32, __cpu_to_le32)

अटल व्योम wsm_buf_reset(काष्ठा wsm_buf *buf);
अटल पूर्णांक wsm_buf_reserve(काष्ठा wsm_buf *buf, माप_प्रकार extra_size);

अटल पूर्णांक wsm_cmd_send(काष्ठा cw1200_common *priv,
			काष्ठा wsm_buf *buf,
			व्योम *arg, u16 cmd, दीर्घ पंचांगo);

#घोषणा wsm_cmd_lock(__priv) mutex_lock(&((__priv)->wsm_cmd_mux))
#घोषणा wsm_cmd_unlock(__priv) mutex_unlock(&((__priv)->wsm_cmd_mux))

/* ******************************************************************** */
/* WSM API implementation						*/

अटल पूर्णांक wsm_generic_confirm(काष्ठा cw1200_common *priv,
			     व्योम *arg,
			     काष्ठा wsm_buf *buf)
अणु
	u32 status = WSM_GET32(buf);
	अगर (status != WSM_STATUS_SUCCESS)
		वापस -EINVAL;
	वापस 0;

underflow:
	WARN_ON(1);
	वापस -EINVAL;
पूर्ण

पूर्णांक wsm_configuration(काष्ठा cw1200_common *priv, काष्ठा wsm_configuration *arg)
अणु
	पूर्णांक ret;
	काष्ठा wsm_buf *buf = &priv->wsm_cmd_buf;

	wsm_cmd_lock(priv);

	WSM_PUT32(buf, arg->करोt11MaxTransmitMsduLअगरeTime);
	WSM_PUT32(buf, arg->करोt11MaxReceiveLअगरeTime);
	WSM_PUT32(buf, arg->करोt11RtsThreshold);

	/* DPD block. */
	WSM_PUT16(buf, arg->dpdData_size + 12);
	WSM_PUT16(buf, 1); /* DPD version */
	WSM_PUT(buf, arg->करोt11StationId, ETH_ALEN);
	WSM_PUT16(buf, 5); /* DPD flags */
	WSM_PUT(buf, arg->dpdData, arg->dpdData_size);

	ret = wsm_cmd_send(priv, buf, arg,
			   WSM_CONFIGURATION_REQ_ID, WSM_CMD_TIMEOUT);

	wsm_cmd_unlock(priv);
	वापस ret;

nomem:
	wsm_cmd_unlock(priv);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक wsm_configuration_confirm(काष्ठा cw1200_common *priv,
				     काष्ठा wsm_configuration *arg,
				     काष्ठा wsm_buf *buf)
अणु
	पूर्णांक i;
	पूर्णांक status;

	status = WSM_GET32(buf);
	अगर (WARN_ON(status != WSM_STATUS_SUCCESS))
		वापस -EINVAL;

	WSM_GET(buf, arg->करोt11StationId, ETH_ALEN);
	arg->करोt11FrequencyBandsSupported = WSM_GET8(buf);
	WSM_SKIP(buf, 1);
	arg->supportedRateMask = WSM_GET32(buf);
	क्रम (i = 0; i < 2; ++i) अणु
		arg->txPowerRange[i].min_घातer_level = WSM_GET32(buf);
		arg->txPowerRange[i].max_घातer_level = WSM_GET32(buf);
		arg->txPowerRange[i].stepping = WSM_GET32(buf);
	पूर्ण
	वापस 0;

underflow:
	WARN_ON(1);
	वापस -EINVAL;
पूर्ण

/* ******************************************************************** */

पूर्णांक wsm_reset(काष्ठा cw1200_common *priv, स्थिर काष्ठा wsm_reset *arg)
अणु
	पूर्णांक ret;
	काष्ठा wsm_buf *buf = &priv->wsm_cmd_buf;
	u16 cmd = WSM_RESET_REQ_ID | WSM_TX_LINK_ID(arg->link_id);

	wsm_cmd_lock(priv);

	WSM_PUT32(buf, arg->reset_statistics ? 0 : 1);
	ret = wsm_cmd_send(priv, buf, शून्य, cmd, WSM_CMD_RESET_TIMEOUT);
	wsm_cmd_unlock(priv);
	वापस ret;

nomem:
	wsm_cmd_unlock(priv);
	वापस -ENOMEM;
पूर्ण

/* ******************************************************************** */

काष्ठा wsm_mib अणु
	u16 mib_id;
	व्योम *buf;
	माप_प्रकार buf_size;
पूर्ण;

पूर्णांक wsm_पढ़ो_mib(काष्ठा cw1200_common *priv, u16 mib_id, व्योम *_buf,
			माप_प्रकार buf_size)
अणु
	पूर्णांक ret;
	काष्ठा wsm_buf *buf = &priv->wsm_cmd_buf;
	काष्ठा wsm_mib mib_buf = अणु
		.mib_id = mib_id,
		.buf = _buf,
		.buf_size = buf_size,
	पूर्ण;
	wsm_cmd_lock(priv);

	WSM_PUT16(buf, mib_id);
	WSM_PUT16(buf, 0);

	ret = wsm_cmd_send(priv, buf, &mib_buf,
			   WSM_READ_MIB_REQ_ID, WSM_CMD_TIMEOUT);
	wsm_cmd_unlock(priv);
	वापस ret;

nomem:
	wsm_cmd_unlock(priv);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक wsm_पढ़ो_mib_confirm(काष्ठा cw1200_common *priv,
				काष्ठा wsm_mib *arg,
				काष्ठा wsm_buf *buf)
अणु
	u16 size;
	अगर (WARN_ON(WSM_GET32(buf) != WSM_STATUS_SUCCESS))
		वापस -EINVAL;

	अगर (WARN_ON(WSM_GET16(buf) != arg->mib_id))
		वापस -EINVAL;

	size = WSM_GET16(buf);
	अगर (size > arg->buf_size)
		size = arg->buf_size;

	WSM_GET(buf, arg->buf, size);
	arg->buf_size = size;
	वापस 0;

underflow:
	WARN_ON(1);
	वापस -EINVAL;
पूर्ण

/* ******************************************************************** */

पूर्णांक wsm_ग_लिखो_mib(काष्ठा cw1200_common *priv, u16 mib_id, व्योम *_buf,
			माप_प्रकार buf_size)
अणु
	पूर्णांक ret;
	काष्ठा wsm_buf *buf = &priv->wsm_cmd_buf;
	काष्ठा wsm_mib mib_buf = अणु
		.mib_id = mib_id,
		.buf = _buf,
		.buf_size = buf_size,
	पूर्ण;

	wsm_cmd_lock(priv);

	WSM_PUT16(buf, mib_id);
	WSM_PUT16(buf, buf_size);
	WSM_PUT(buf, _buf, buf_size);

	ret = wsm_cmd_send(priv, buf, &mib_buf,
			   WSM_WRITE_MIB_REQ_ID, WSM_CMD_TIMEOUT);
	wsm_cmd_unlock(priv);
	वापस ret;

nomem:
	wsm_cmd_unlock(priv);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक wsm_ग_लिखो_mib_confirm(काष्ठा cw1200_common *priv,
				काष्ठा wsm_mib *arg,
				काष्ठा wsm_buf *buf)
अणु
	पूर्णांक ret;

	ret = wsm_generic_confirm(priv, arg, buf);
	अगर (ret)
		वापस ret;

	अगर (arg->mib_id == WSM_MIB_ID_OPERATIONAL_POWER_MODE) अणु
		/* OperationalMode: update PM status. */
		स्थिर अक्षर *p = arg->buf;
		cw1200_enable_घातersave(priv, (p[0] & 0x0F) ? true : false);
	पूर्ण
	वापस 0;
पूर्ण

/* ******************************************************************** */

पूर्णांक wsm_scan(काष्ठा cw1200_common *priv, स्थिर काष्ठा wsm_scan *arg)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	काष्ठा wsm_buf *buf = &priv->wsm_cmd_buf;

	अगर (arg->num_channels > 48)
		वापस -EINVAL;

	अगर (arg->num_ssids > 2)
		वापस -EINVAL;

	अगर (arg->band > 1)
		वापस -EINVAL;

	wsm_cmd_lock(priv);

	WSM_PUT8(buf, arg->band);
	WSM_PUT8(buf, arg->type);
	WSM_PUT8(buf, arg->flags);
	WSM_PUT8(buf, arg->max_tx_rate);
	WSM_PUT32(buf, arg->स्वतः_scan_पूर्णांकerval);
	WSM_PUT8(buf, arg->num_probes);
	WSM_PUT8(buf, arg->num_channels);
	WSM_PUT8(buf, arg->num_ssids);
	WSM_PUT8(buf, arg->probe_delay);

	क्रम (i = 0; i < arg->num_channels; ++i) अणु
		WSM_PUT16(buf, arg->ch[i].number);
		WSM_PUT16(buf, 0);
		WSM_PUT32(buf, arg->ch[i].min_chan_समय);
		WSM_PUT32(buf, arg->ch[i].max_chan_समय);
		WSM_PUT32(buf, 0);
	पूर्ण

	क्रम (i = 0; i < arg->num_ssids; ++i) अणु
		WSM_PUT32(buf, arg->ssids[i].length);
		WSM_PUT(buf, &arg->ssids[i].ssid[0],
			माप(arg->ssids[i].ssid));
	पूर्ण

	ret = wsm_cmd_send(priv, buf, शून्य,
			   WSM_START_SCAN_REQ_ID, WSM_CMD_TIMEOUT);
	wsm_cmd_unlock(priv);
	वापस ret;

nomem:
	wsm_cmd_unlock(priv);
	वापस -ENOMEM;
पूर्ण

/* ******************************************************************** */

पूर्णांक wsm_stop_scan(काष्ठा cw1200_common *priv)
अणु
	पूर्णांक ret;
	काष्ठा wsm_buf *buf = &priv->wsm_cmd_buf;
	wsm_cmd_lock(priv);
	ret = wsm_cmd_send(priv, buf, शून्य,
			   WSM_STOP_SCAN_REQ_ID, WSM_CMD_TIMEOUT);
	wsm_cmd_unlock(priv);
	वापस ret;
पूर्ण


अटल पूर्णांक wsm_tx_confirm(काष्ठा cw1200_common *priv,
			  काष्ठा wsm_buf *buf,
			  पूर्णांक link_id)
अणु
	काष्ठा wsm_tx_confirm tx_confirm;

	tx_confirm.packet_id = WSM_GET32(buf);
	tx_confirm.status = WSM_GET32(buf);
	tx_confirm.tx_rate = WSM_GET8(buf);
	tx_confirm.ack_failures = WSM_GET8(buf);
	tx_confirm.flags = WSM_GET16(buf);
	tx_confirm.media_delay = WSM_GET32(buf);
	tx_confirm.tx_queue_delay = WSM_GET32(buf);

	cw1200_tx_confirm_cb(priv, link_id, &tx_confirm);
	वापस 0;

underflow:
	WARN_ON(1);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wsm_multi_tx_confirm(काष्ठा cw1200_common *priv,
				काष्ठा wsm_buf *buf, पूर्णांक link_id)
अणु
	पूर्णांक ret;
	पूर्णांक count;

	count = WSM_GET32(buf);
	अगर (WARN_ON(count <= 0))
		वापस -EINVAL;

	अगर (count > 1) अणु
		/* We alपढ़ोy released one buffer, now क्रम the rest */
		ret = wsm_release_tx_buffer(priv, count - 1);
		अगर (ret < 0)
			वापस ret;
		अन्यथा अगर (ret > 0)
			cw1200_bh_wakeup(priv);
	पूर्ण

	cw1200_debug_txed_multi(priv, count);
	करो अणु
		ret = wsm_tx_confirm(priv, buf, link_id);
	पूर्ण जबतक (!ret && --count);

	वापस ret;

underflow:
	WARN_ON(1);
	वापस -EINVAL;
पूर्ण

/* ******************************************************************** */

अटल पूर्णांक wsm_join_confirm(काष्ठा cw1200_common *priv,
			    काष्ठा wsm_join_cnf *arg,
			    काष्ठा wsm_buf *buf)
अणु
	arg->status = WSM_GET32(buf);
	अगर (WARN_ON(arg->status) != WSM_STATUS_SUCCESS)
		वापस -EINVAL;

	arg->min_घातer_level = WSM_GET32(buf);
	arg->max_घातer_level = WSM_GET32(buf);

	वापस 0;

underflow:
	WARN_ON(1);
	वापस -EINVAL;
पूर्ण

पूर्णांक wsm_join(काष्ठा cw1200_common *priv, काष्ठा wsm_join *arg)
अणु
	पूर्णांक ret;
	काष्ठा wsm_buf *buf = &priv->wsm_cmd_buf;
	काष्ठा wsm_join_cnf resp;
	wsm_cmd_lock(priv);

	WSM_PUT8(buf, arg->mode);
	WSM_PUT8(buf, arg->band);
	WSM_PUT16(buf, arg->channel_number);
	WSM_PUT(buf, &arg->bssid[0], माप(arg->bssid));
	WSM_PUT16(buf, arg->atim_winकरोw);
	WSM_PUT8(buf, arg->preamble_type);
	WSM_PUT8(buf, arg->probe_क्रम_join);
	WSM_PUT8(buf, arg->dtim_period);
	WSM_PUT8(buf, arg->flags);
	WSM_PUT32(buf, arg->ssid_len);
	WSM_PUT(buf, &arg->ssid[0], माप(arg->ssid));
	WSM_PUT32(buf, arg->beacon_पूर्णांकerval);
	WSM_PUT32(buf, arg->basic_rate_set);

	priv->tx_burst_idx = -1;
	ret = wsm_cmd_send(priv, buf, &resp,
			   WSM_JOIN_REQ_ID, WSM_CMD_TIMEOUT);
	/* TODO:  Update state based on resp.min|max_घातer_level */

	priv->join_complete_status = resp.status;

	wsm_cmd_unlock(priv);
	वापस ret;

nomem:
	wsm_cmd_unlock(priv);
	वापस -ENOMEM;
पूर्ण

/* ******************************************************************** */

पूर्णांक wsm_set_bss_params(काष्ठा cw1200_common *priv,
		       स्थिर काष्ठा wsm_set_bss_params *arg)
अणु
	पूर्णांक ret;
	काष्ठा wsm_buf *buf = &priv->wsm_cmd_buf;

	wsm_cmd_lock(priv);

	WSM_PUT8(buf, (arg->reset_beacon_loss ?  0x1 : 0));
	WSM_PUT8(buf, arg->beacon_lost_count);
	WSM_PUT16(buf, arg->aid);
	WSM_PUT32(buf, arg->operational_rate_set);

	ret = wsm_cmd_send(priv, buf, शून्य,
			   WSM_SET_BSS_PARAMS_REQ_ID, WSM_CMD_TIMEOUT);

	wsm_cmd_unlock(priv);
	वापस ret;

nomem:
	wsm_cmd_unlock(priv);
	वापस -ENOMEM;
पूर्ण

/* ******************************************************************** */

पूर्णांक wsm_add_key(काष्ठा cw1200_common *priv, स्थिर काष्ठा wsm_add_key *arg)
अणु
	पूर्णांक ret;
	काष्ठा wsm_buf *buf = &priv->wsm_cmd_buf;

	wsm_cmd_lock(priv);

	WSM_PUT(buf, arg, माप(*arg));

	ret = wsm_cmd_send(priv, buf, शून्य,
			   WSM_ADD_KEY_REQ_ID, WSM_CMD_TIMEOUT);

	wsm_cmd_unlock(priv);
	वापस ret;

nomem:
	wsm_cmd_unlock(priv);
	वापस -ENOMEM;
पूर्ण

/* ******************************************************************** */

पूर्णांक wsm_हटाओ_key(काष्ठा cw1200_common *priv, स्थिर काष्ठा wsm_हटाओ_key *arg)
अणु
	पूर्णांक ret;
	काष्ठा wsm_buf *buf = &priv->wsm_cmd_buf;

	wsm_cmd_lock(priv);

	WSM_PUT8(buf, arg->index);
	WSM_PUT8(buf, 0);
	WSM_PUT16(buf, 0);

	ret = wsm_cmd_send(priv, buf, शून्य,
			   WSM_REMOVE_KEY_REQ_ID, WSM_CMD_TIMEOUT);

	wsm_cmd_unlock(priv);
	वापस ret;

nomem:
	wsm_cmd_unlock(priv);
	वापस -ENOMEM;
पूर्ण

/* ******************************************************************** */

पूर्णांक wsm_set_tx_queue_params(काष्ठा cw1200_common *priv,
		स्थिर काष्ठा wsm_set_tx_queue_params *arg, u8 id)
अणु
	पूर्णांक ret;
	काष्ठा wsm_buf *buf = &priv->wsm_cmd_buf;
	u8 queue_id_to_wmm_aci[] = अणु3, 2, 0, 1पूर्ण;

	wsm_cmd_lock(priv);

	WSM_PUT8(buf, queue_id_to_wmm_aci[id]);
	WSM_PUT8(buf, 0);
	WSM_PUT8(buf, arg->ackPolicy);
	WSM_PUT8(buf, 0);
	WSM_PUT32(buf, arg->maxTransmitLअगरeसमय);
	WSM_PUT16(buf, arg->allowedMediumTime);
	WSM_PUT16(buf, 0);

	ret = wsm_cmd_send(priv, buf, शून्य, 0x0012, WSM_CMD_TIMEOUT);

	wsm_cmd_unlock(priv);
	वापस ret;

nomem:
	wsm_cmd_unlock(priv);
	वापस -ENOMEM;
पूर्ण

/* ******************************************************************** */

पूर्णांक wsm_set_edca_params(काष्ठा cw1200_common *priv,
				स्थिर काष्ठा wsm_edca_params *arg)
अणु
	पूर्णांक ret;
	काष्ठा wsm_buf *buf = &priv->wsm_cmd_buf;

	wsm_cmd_lock(priv);

	/* Implemented according to specअगरication. */

	WSM_PUT16(buf, arg->params[3].cwmin);
	WSM_PUT16(buf, arg->params[2].cwmin);
	WSM_PUT16(buf, arg->params[1].cwmin);
	WSM_PUT16(buf, arg->params[0].cwmin);

	WSM_PUT16(buf, arg->params[3].cwmax);
	WSM_PUT16(buf, arg->params[2].cwmax);
	WSM_PUT16(buf, arg->params[1].cwmax);
	WSM_PUT16(buf, arg->params[0].cwmax);

	WSM_PUT8(buf, arg->params[3].aअगरns);
	WSM_PUT8(buf, arg->params[2].aअगरns);
	WSM_PUT8(buf, arg->params[1].aअगरns);
	WSM_PUT8(buf, arg->params[0].aअगरns);

	WSM_PUT16(buf, arg->params[3].txop_limit);
	WSM_PUT16(buf, arg->params[2].txop_limit);
	WSM_PUT16(buf, arg->params[1].txop_limit);
	WSM_PUT16(buf, arg->params[0].txop_limit);

	WSM_PUT32(buf, arg->params[3].max_rx_lअगरeसमय);
	WSM_PUT32(buf, arg->params[2].max_rx_lअगरeसमय);
	WSM_PUT32(buf, arg->params[1].max_rx_lअगरeसमय);
	WSM_PUT32(buf, arg->params[0].max_rx_lअगरeसमय);

	ret = wsm_cmd_send(priv, buf, शून्य,
			   WSM_EDCA_PARAMS_REQ_ID, WSM_CMD_TIMEOUT);
	wsm_cmd_unlock(priv);
	वापस ret;

nomem:
	wsm_cmd_unlock(priv);
	वापस -ENOMEM;
पूर्ण

/* ******************************************************************** */

पूर्णांक wsm_चयन_channel(काष्ठा cw1200_common *priv,
			स्थिर काष्ठा wsm_चयन_channel *arg)
अणु
	पूर्णांक ret;
	काष्ठा wsm_buf *buf = &priv->wsm_cmd_buf;

	wsm_cmd_lock(priv);

	WSM_PUT8(buf, arg->mode);
	WSM_PUT8(buf, arg->चयन_count);
	WSM_PUT16(buf, arg->channel_number);

	priv->channel_चयन_in_progress = 1;

	ret = wsm_cmd_send(priv, buf, शून्य,
			   WSM_SWITCH_CHANNEL_REQ_ID, WSM_CMD_TIMEOUT);
	अगर (ret)
		priv->channel_चयन_in_progress = 0;

	wsm_cmd_unlock(priv);
	वापस ret;

nomem:
	wsm_cmd_unlock(priv);
	वापस -ENOMEM;
पूर्ण

/* ******************************************************************** */

पूर्णांक wsm_set_pm(काष्ठा cw1200_common *priv, स्थिर काष्ठा wsm_set_pm *arg)
अणु
	पूर्णांक ret;
	काष्ठा wsm_buf *buf = &priv->wsm_cmd_buf;
	priv->ps_mode_चयन_in_progress = 1;

	wsm_cmd_lock(priv);

	WSM_PUT8(buf, arg->mode);
	WSM_PUT8(buf, arg->fast_psm_idle_period);
	WSM_PUT8(buf, arg->ap_psm_change_period);
	WSM_PUT8(buf, arg->min_स्वतः_pspoll_period);

	ret = wsm_cmd_send(priv, buf, शून्य,
			   WSM_SET_PM_REQ_ID, WSM_CMD_TIMEOUT);

	wsm_cmd_unlock(priv);
	वापस ret;

nomem:
	wsm_cmd_unlock(priv);
	वापस -ENOMEM;
पूर्ण

/* ******************************************************************** */

पूर्णांक wsm_start(काष्ठा cw1200_common *priv, स्थिर काष्ठा wsm_start *arg)
अणु
	पूर्णांक ret;
	काष्ठा wsm_buf *buf = &priv->wsm_cmd_buf;

	wsm_cmd_lock(priv);

	WSM_PUT8(buf, arg->mode);
	WSM_PUT8(buf, arg->band);
	WSM_PUT16(buf, arg->channel_number);
	WSM_PUT32(buf, arg->ct_winकरोw);
	WSM_PUT32(buf, arg->beacon_पूर्णांकerval);
	WSM_PUT8(buf, arg->dtim_period);
	WSM_PUT8(buf, arg->preamble);
	WSM_PUT8(buf, arg->probe_delay);
	WSM_PUT8(buf, arg->ssid_len);
	WSM_PUT(buf, arg->ssid, माप(arg->ssid));
	WSM_PUT32(buf, arg->basic_rate_set);

	priv->tx_burst_idx = -1;
	ret = wsm_cmd_send(priv, buf, शून्य,
			   WSM_START_REQ_ID, WSM_CMD_START_TIMEOUT);

	wsm_cmd_unlock(priv);
	वापस ret;

nomem:
	wsm_cmd_unlock(priv);
	वापस -ENOMEM;
पूर्ण

/* ******************************************************************** */

पूर्णांक wsm_beacon_transmit(काष्ठा cw1200_common *priv,
			स्थिर काष्ठा wsm_beacon_transmit *arg)
अणु
	पूर्णांक ret;
	काष्ठा wsm_buf *buf = &priv->wsm_cmd_buf;

	wsm_cmd_lock(priv);

	WSM_PUT32(buf, arg->enable_beaconing ? 1 : 0);

	ret = wsm_cmd_send(priv, buf, शून्य,
			   WSM_BEACON_TRANSMIT_REQ_ID, WSM_CMD_TIMEOUT);

	wsm_cmd_unlock(priv);
	वापस ret;

nomem:
	wsm_cmd_unlock(priv);
	वापस -ENOMEM;
पूर्ण

/* ******************************************************************** */

पूर्णांक wsm_start_find(काष्ठा cw1200_common *priv)
अणु
	पूर्णांक ret;
	काष्ठा wsm_buf *buf = &priv->wsm_cmd_buf;

	wsm_cmd_lock(priv);
	ret = wsm_cmd_send(priv, buf, शून्य, 0x0019, WSM_CMD_TIMEOUT);
	wsm_cmd_unlock(priv);
	वापस ret;
पूर्ण

/* ******************************************************************** */

पूर्णांक wsm_stop_find(काष्ठा cw1200_common *priv)
अणु
	पूर्णांक ret;
	काष्ठा wsm_buf *buf = &priv->wsm_cmd_buf;

	wsm_cmd_lock(priv);
	ret = wsm_cmd_send(priv, buf, शून्य, 0x001A, WSM_CMD_TIMEOUT);
	wsm_cmd_unlock(priv);
	वापस ret;
पूर्ण

/* ******************************************************************** */

पूर्णांक wsm_map_link(काष्ठा cw1200_common *priv, स्थिर काष्ठा wsm_map_link *arg)
अणु
	पूर्णांक ret;
	काष्ठा wsm_buf *buf = &priv->wsm_cmd_buf;
	u16 cmd = 0x001C | WSM_TX_LINK_ID(arg->link_id);

	wsm_cmd_lock(priv);

	WSM_PUT(buf, &arg->mac_addr[0], माप(arg->mac_addr));
	WSM_PUT16(buf, 0);

	ret = wsm_cmd_send(priv, buf, शून्य, cmd, WSM_CMD_TIMEOUT);

	wsm_cmd_unlock(priv);
	वापस ret;

nomem:
	wsm_cmd_unlock(priv);
	वापस -ENOMEM;
पूर्ण

/* ******************************************************************** */

पूर्णांक wsm_update_ie(काष्ठा cw1200_common *priv,
		  स्थिर काष्ठा wsm_update_ie *arg)
अणु
	पूर्णांक ret;
	काष्ठा wsm_buf *buf = &priv->wsm_cmd_buf;

	wsm_cmd_lock(priv);

	WSM_PUT16(buf, arg->what);
	WSM_PUT16(buf, arg->count);
	WSM_PUT(buf, arg->ies, arg->length);

	ret = wsm_cmd_send(priv, buf, शून्य, 0x001B, WSM_CMD_TIMEOUT);

	wsm_cmd_unlock(priv);
	वापस ret;

nomem:
	wsm_cmd_unlock(priv);
	वापस -ENOMEM;
पूर्ण

/* ******************************************************************** */
पूर्णांक wsm_set_probe_responder(काष्ठा cw1200_common *priv, bool enable)
अणु
	priv->rx_filter.probeResponder = enable;
	वापस wsm_set_rx_filter(priv, &priv->rx_filter);
पूर्ण

/* ******************************************************************** */
/* WSM indication events implementation					*/
स्थिर अक्षर * स्थिर cw1200_fw_types[] = अणु
	"ETF",
	"WFM",
	"WSM",
	"HI test",
	"Platform test"
पूर्ण;

अटल पूर्णांक wsm_startup_indication(काष्ठा cw1200_common *priv,
					काष्ठा wsm_buf *buf)
अणु
	priv->wsm_caps.input_buffers     = WSM_GET16(buf);
	priv->wsm_caps.input_buffer_size = WSM_GET16(buf);
	priv->wsm_caps.hw_id	  = WSM_GET16(buf);
	priv->wsm_caps.hw_subid	  = WSM_GET16(buf);
	priv->wsm_caps.status	  = WSM_GET16(buf);
	priv->wsm_caps.fw_cap	  = WSM_GET16(buf);
	priv->wsm_caps.fw_type	  = WSM_GET16(buf);
	priv->wsm_caps.fw_api	  = WSM_GET16(buf);
	priv->wsm_caps.fw_build   = WSM_GET16(buf);
	priv->wsm_caps.fw_ver     = WSM_GET16(buf);
	WSM_GET(buf, priv->wsm_caps.fw_label, माप(priv->wsm_caps.fw_label));
	priv->wsm_caps.fw_label[माप(priv->wsm_caps.fw_label) - 1] = 0; /* Do not trust FW too much... */

	अगर (WARN_ON(priv->wsm_caps.status))
		वापस -EINVAL;

	अगर (WARN_ON(priv->wsm_caps.fw_type > 4))
		वापस -EINVAL;

	pr_info("CW1200 WSM init done.\n"
		"   Input buffers: %d x %d bytes\n"
		"   Hardware: %d.%d\n"
		"   %s firmware [%s], ver: %d, build: %d,"
		"   api: %d, cap: 0x%.4X\n",
		priv->wsm_caps.input_buffers,
		priv->wsm_caps.input_buffer_size,
		priv->wsm_caps.hw_id, priv->wsm_caps.hw_subid,
		cw1200_fw_types[priv->wsm_caps.fw_type],
		priv->wsm_caps.fw_label, priv->wsm_caps.fw_ver,
		priv->wsm_caps.fw_build,
		priv->wsm_caps.fw_api, priv->wsm_caps.fw_cap);

	/* Disable unsupported frequency bands */
	अगर (!(priv->wsm_caps.fw_cap & 0x1))
		priv->hw->wiphy->bands[NL80211_BAND_2GHZ] = शून्य;
	अगर (!(priv->wsm_caps.fw_cap & 0x2))
		priv->hw->wiphy->bands[NL80211_BAND_5GHZ] = शून्य;

	priv->firmware_पढ़ोy = 1;
	wake_up(&priv->wsm_startup_करोne);
	वापस 0;

underflow:
	WARN_ON(1);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wsm_receive_indication(काष्ठा cw1200_common *priv,
				  पूर्णांक link_id,
				  काष्ठा wsm_buf *buf,
				  काष्ठा sk_buff **skb_p)
अणु
	काष्ठा wsm_rx rx;
	काष्ठा ieee80211_hdr *hdr;
	माप_प्रकार hdr_len;
	__le16 fctl;

	rx.status = WSM_GET32(buf);
	rx.channel_number = WSM_GET16(buf);
	rx.rx_rate = WSM_GET8(buf);
	rx.rcpi_rssi = WSM_GET8(buf);
	rx.flags = WSM_GET32(buf);

	/* FW Workaround: Drop probe resp or
	   beacon when RSSI is 0
	*/
	hdr = (काष्ठा ieee80211_hdr *)(*skb_p)->data;

	अगर (!rx.rcpi_rssi &&
	    (ieee80211_is_probe_resp(hdr->frame_control) ||
	     ieee80211_is_beacon(hdr->frame_control)))
		वापस 0;

	/* If no RSSI subscription has been made,
	 * convert RCPI to RSSI here
	 */
	अगर (!priv->cqm_use_rssi)
		rx.rcpi_rssi = rx.rcpi_rssi / 2 - 110;

	fctl = *(__le16 *)buf->data;
	hdr_len = buf->data - buf->begin;
	skb_pull(*skb_p, hdr_len);
	अगर (!rx.status && ieee80211_is_deauth(fctl)) अणु
		अगर (priv->join_status == CW1200_JOIN_STATUS_STA) अणु
			/* Shedule unjoin work */
			pr_debug("[WSM] Issue unjoin command (RX).\n");
			wsm_lock_tx_async(priv);
			अगर (queue_work(priv->workqueue,
				       &priv->unjoin_work) <= 0)
				wsm_unlock_tx(priv);
		पूर्ण
	पूर्ण
	cw1200_rx_cb(priv, &rx, link_id, skb_p);
	अगर (*skb_p)
		skb_push(*skb_p, hdr_len);

	वापस 0;

underflow:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wsm_event_indication(काष्ठा cw1200_common *priv, काष्ठा wsm_buf *buf)
अणु
	पूर्णांक first;
	काष्ठा cw1200_wsm_event *event;

	अगर (priv->mode == NL80211_IFTYPE_UNSPECIFIED) अणु
		/* STA is stopped. */
		वापस 0;
	पूर्ण

	event = kzalloc(माप(काष्ठा cw1200_wsm_event), GFP_KERNEL);
	अगर (!event)
		वापस -ENOMEM;

	event->evt.id = WSM_GET32(buf);
	event->evt.data = WSM_GET32(buf);

	pr_debug("[WSM] Event: %d(%d)\n",
		 event->evt.id, event->evt.data);

	spin_lock(&priv->event_queue_lock);
	first = list_empty(&priv->event_queue);
	list_add_tail(&event->link, &priv->event_queue);
	spin_unlock(&priv->event_queue_lock);

	अगर (first)
		queue_work(priv->workqueue, &priv->event_handler);

	वापस 0;

underflow:
	kमुक्त(event);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wsm_channel_चयन_indication(काष्ठा cw1200_common *priv,
					 काष्ठा wsm_buf *buf)
अणु
	WARN_ON(WSM_GET32(buf));

	priv->channel_चयन_in_progress = 0;
	wake_up(&priv->channel_चयन_करोne);

	wsm_unlock_tx(priv);

	वापस 0;

underflow:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wsm_set_pm_indication(काष्ठा cw1200_common *priv,
				 काष्ठा wsm_buf *buf)
अणु
	/* TODO:  Check buf (काष्ठा wsm_set_pm_complete) क्रम validity */
	अगर (priv->ps_mode_चयन_in_progress) अणु
		priv->ps_mode_चयन_in_progress = 0;
		wake_up(&priv->ps_mode_चयन_करोne);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wsm_scan_started(काष्ठा cw1200_common *priv, व्योम *arg,
			    काष्ठा wsm_buf *buf)
अणु
	u32 status = WSM_GET32(buf);
	अगर (status != WSM_STATUS_SUCCESS) अणु
		cw1200_scan_failed_cb(priv);
		वापस -EINVAL;
	पूर्ण
	वापस 0;

underflow:
	WARN_ON(1);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wsm_scan_complete_indication(काष्ठा cw1200_common *priv,
					काष्ठा wsm_buf *buf)
अणु
	काष्ठा wsm_scan_complete arg;
	arg.status = WSM_GET32(buf);
	arg.psm = WSM_GET8(buf);
	arg.num_channels = WSM_GET8(buf);
	cw1200_scan_complete_cb(priv, &arg);

	वापस 0;

underflow:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wsm_join_complete_indication(काष्ठा cw1200_common *priv,
					काष्ठा wsm_buf *buf)
अणु
	काष्ठा wsm_join_complete arg;
	arg.status = WSM_GET32(buf);
	pr_debug("[WSM] Join complete indication, status: %d\n", arg.status);
	cw1200_join_complete_cb(priv, &arg);

	वापस 0;

underflow:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wsm_find_complete_indication(काष्ठा cw1200_common *priv,
					काष्ठा wsm_buf *buf)
अणु
	pr_warn("Implement find_complete_indication\n");
	वापस 0;
पूर्ण

अटल पूर्णांक wsm_ba_समयout_indication(काष्ठा cw1200_common *priv,
				     काष्ठा wsm_buf *buf)
अणु
	u8 tid;
	u8 addr[ETH_ALEN];

	WSM_GET32(buf);
	tid = WSM_GET8(buf);
	WSM_GET8(buf);
	WSM_GET(buf, addr, ETH_ALEN);

	pr_info("BlockACK timeout, tid %d, addr %pM\n",
		tid, addr);

	वापस 0;

underflow:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wsm_suspend_resume_indication(काष्ठा cw1200_common *priv,
					 पूर्णांक link_id, काष्ठा wsm_buf *buf)
अणु
	u32 flags;
	काष्ठा wsm_suspend_resume arg;

	flags = WSM_GET32(buf);
	arg.link_id = link_id;
	arg.stop = !(flags & 1);
	arg.multicast = !!(flags & 8);
	arg.queue = (flags >> 1) & 3;

	cw1200_suspend_resume(priv, &arg);

	वापस 0;

underflow:
	वापस -EINVAL;
पूर्ण


/* ******************************************************************** */
/* WSM TX								*/

अटल पूर्णांक wsm_cmd_send(काष्ठा cw1200_common *priv,
			काष्ठा wsm_buf *buf,
			व्योम *arg, u16 cmd, दीर्घ पंचांगo)
अणु
	माप_प्रकार buf_len = buf->data - buf->begin;
	पूर्णांक ret;

	/* Don't bother if we're dead. */
	अगर (priv->bh_error) अणु
		ret = 0;
		जाओ करोne;
	पूर्ण

	/* Block until the cmd buffer is completed.  Tortuous. */
	spin_lock(&priv->wsm_cmd.lock);
	जबतक (!priv->wsm_cmd.करोne) अणु
		spin_unlock(&priv->wsm_cmd.lock);
		spin_lock(&priv->wsm_cmd.lock);
	पूर्ण
	priv->wsm_cmd.करोne = 0;
	spin_unlock(&priv->wsm_cmd.lock);

	अगर (cmd == WSM_WRITE_MIB_REQ_ID ||
	    cmd == WSM_READ_MIB_REQ_ID)
		pr_debug("[WSM] >>> 0x%.4X [MIB: 0x%.4X] (%zu)\n",
			 cmd, __le16_to_cpu(((__le16 *)buf->begin)[2]),
			 buf_len);
	अन्यथा
		pr_debug("[WSM] >>> 0x%.4X (%zu)\n", cmd, buf_len);

	/* Due to buggy SPI on CW1200, we need to
	 * pad the message by a few bytes to ensure
	 * that it's completely received.
	 */
	buf_len += 4;

	/* Fill HI message header */
	/* BH will add sequence number */
	((__le16 *)buf->begin)[0] = __cpu_to_le16(buf_len);
	((__le16 *)buf->begin)[1] = __cpu_to_le16(cmd);

	spin_lock(&priv->wsm_cmd.lock);
	BUG_ON(priv->wsm_cmd.ptr);
	priv->wsm_cmd.ptr = buf->begin;
	priv->wsm_cmd.len = buf_len;
	priv->wsm_cmd.arg = arg;
	priv->wsm_cmd.cmd = cmd;
	spin_unlock(&priv->wsm_cmd.lock);

	cw1200_bh_wakeup(priv);

	/* Wait क्रम command completion */
	ret = रुको_event_समयout(priv->wsm_cmd_wq,
				 priv->wsm_cmd.करोne, पंचांगo);

	अगर (!ret && !priv->wsm_cmd.करोne) अणु
		spin_lock(&priv->wsm_cmd.lock);
		priv->wsm_cmd.करोne = 1;
		priv->wsm_cmd.ptr = शून्य;
		spin_unlock(&priv->wsm_cmd.lock);
		अगर (priv->bh_error) अणु
			/* Return ok to help प्रणाली cleanup */
			ret = 0;
		पूर्ण अन्यथा अणु
			pr_err("CMD req (0x%04x) stuck in firmware, killing BH\n", priv->wsm_cmd.cmd);
			prपूर्णांक_hex_dump_bytes("REQDUMP: ", DUMP_PREFIX_NONE,
					     buf->begin, buf_len);
			pr_err("Outstanding outgoing frames:  %d\n", priv->hw_bufs_used);

			/* Kill BH thपढ़ो to report the error to the top layer. */
			atomic_inc(&priv->bh_term);
			wake_up(&priv->bh_wq);
			ret = -ETIMEDOUT;
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_lock(&priv->wsm_cmd.lock);
		BUG_ON(!priv->wsm_cmd.करोne);
		ret = priv->wsm_cmd.ret;
		spin_unlock(&priv->wsm_cmd.lock);
	पूर्ण
करोne:
	wsm_buf_reset(buf);
	वापस ret;
पूर्ण

/* ******************************************************************** */
/* WSM TX port control							*/

व्योम wsm_lock_tx(काष्ठा cw1200_common *priv)
अणु
	wsm_cmd_lock(priv);
	अगर (atomic_inc_वापस(&priv->tx_lock) == 1) अणु
		अगर (wsm_flush_tx(priv))
			pr_debug("[WSM] TX is locked.\n");
	पूर्ण
	wsm_cmd_unlock(priv);
पूर्ण

व्योम wsm_lock_tx_async(काष्ठा cw1200_common *priv)
अणु
	अगर (atomic_inc_वापस(&priv->tx_lock) == 1)
		pr_debug("[WSM] TX is locked (async).\n");
पूर्ण

bool wsm_flush_tx(काष्ठा cw1200_common *priv)
अणु
	अचिन्हित दीर्घ बारtamp = jअगरfies;
	bool pending = false;
	दीर्घ समयout;
	पूर्णांक i;

	/* Flush must be called with TX lock held. */
	BUG_ON(!atomic_पढ़ो(&priv->tx_lock));

	/* First check अगर we really need to करो something.
	 * It is safe to use unरक्षित access, as hw_bufs_used
	 * can only decrements.
	 */
	अगर (!priv->hw_bufs_used)
		वापस true;

	अगर (priv->bh_error) अणु
		/* In हाल of failure करो not रुको क्रम magic. */
		pr_err("[WSM] Fatal error occurred, will not flush TX.\n");
		वापस false;
	पूर्ण अन्यथा अणु
		/* Get a बारtamp of "oldest" frame */
		क्रम (i = 0; i < 4; ++i)
			pending |= cw1200_queue_get_xmit_बारtamp(
					&priv->tx_queue[i],
					&बारtamp, 0xffffffff);
		/* If there's nothing pending, we're good */
		अगर (!pending)
			वापस true;

		समयout = बारtamp + WSM_CMD_LAST_CHANCE_TIMEOUT - jअगरfies;
		अगर (समयout < 0 || रुको_event_समयout(priv->bh_evt_wq,
						      !priv->hw_bufs_used,
						      समयout) <= 0) अणु
			/* Hmmm... Not good. Frame had stuck in firmware. */
			priv->bh_error = 1;
			wiphy_err(priv->hw->wiphy, "[WSM] TX Frames (%d) stuck in firmware, killing BH\n", priv->hw_bufs_used);
			wake_up(&priv->bh_wq);
			वापस false;
		पूर्ण

		/* Ok, everything is flushed. */
		वापस true;
	पूर्ण
पूर्ण

व्योम wsm_unlock_tx(काष्ठा cw1200_common *priv)
अणु
	पूर्णांक tx_lock;
	tx_lock = atomic_dec_वापस(&priv->tx_lock);
	BUG_ON(tx_lock < 0);

	अगर (tx_lock == 0) अणु
		अगर (!priv->bh_error)
			cw1200_bh_wakeup(priv);
		pr_debug("[WSM] TX is unlocked.\n");
	पूर्ण
पूर्ण

/* ******************************************************************** */
/* WSM RX								*/

पूर्णांक wsm_handle_exception(काष्ठा cw1200_common *priv, u8 *data, माप_प्रकार len)
अणु
	काष्ठा wsm_buf buf;
	u32 reason;
	u32 reg[18];
	अक्षर fname[48];
	अचिन्हित पूर्णांक i;

	अटल स्थिर अक्षर * स्थिर reason_str[] = अणु
		"undefined instruction",
		"prefetch abort",
		"data abort",
		"unknown error",
	पूर्ण;

	buf.begin = buf.data = data;
	buf.end = &buf.begin[len];

	reason = WSM_GET32(&buf);
	क्रम (i = 0; i < ARRAY_SIZE(reg); ++i)
		reg[i] = WSM_GET32(&buf);
	WSM_GET(&buf, fname, माप(fname));

	अगर (reason < 4)
		wiphy_err(priv->hw->wiphy,
			  "Firmware exception: %s.\n",
			  reason_str[reason]);
	अन्यथा
		wiphy_err(priv->hw->wiphy,
			  "Firmware assert at %.*s, line %d\n",
			  (पूर्णांक) माप(fname), fname, reg[1]);

	क्रम (i = 0; i < 12; i += 4)
		wiphy_err(priv->hw->wiphy,
			  "R%d: 0x%.8X, R%d: 0x%.8X, R%d: 0x%.8X, R%d: 0x%.8X,\n",
			  i + 0, reg[i + 0], i + 1, reg[i + 1],
			  i + 2, reg[i + 2], i + 3, reg[i + 3]);
	wiphy_err(priv->hw->wiphy,
		  "R12: 0x%.8X, SP: 0x%.8X, LR: 0x%.8X, PC: 0x%.8X,\n",
		  reg[i + 0], reg[i + 1], reg[i + 2], reg[i + 3]);
	i += 4;
	wiphy_err(priv->hw->wiphy,
		  "CPSR: 0x%.8X, SPSR: 0x%.8X\n",
		  reg[i + 0], reg[i + 1]);

	prपूर्णांक_hex_dump_bytes("R1: ", DUMP_PREFIX_NONE,
			     fname, माप(fname));
	वापस 0;

underflow:
	wiphy_err(priv->hw->wiphy, "Firmware exception.\n");
	prपूर्णांक_hex_dump_bytes("Exception: ", DUMP_PREFIX_NONE,
			     data, len);
	वापस -EINVAL;
पूर्ण

पूर्णांक wsm_handle_rx(काष्ठा cw1200_common *priv, u16 id,
		  काष्ठा wsm_hdr *wsm, काष्ठा sk_buff **skb_p)
अणु
	पूर्णांक ret = 0;
	काष्ठा wsm_buf wsm_buf;
	पूर्णांक link_id = (id >> 6) & 0x0F;

	/* Strip link id. */
	id &= ~WSM_TX_LINK_ID(WSM_TX_LINK_ID_MAX);

	wsm_buf.begin = (u8 *)&wsm[0];
	wsm_buf.data = (u8 *)&wsm[1];
	wsm_buf.end = &wsm_buf.begin[__le16_to_cpu(wsm->len)];

	pr_debug("[WSM] <<< 0x%.4X (%td)\n", id,
		 wsm_buf.end - wsm_buf.begin);

	अगर (id == WSM_TX_CONFIRM_IND_ID) अणु
		ret = wsm_tx_confirm(priv, &wsm_buf, link_id);
	पूर्ण अन्यथा अगर (id == WSM_MULTI_TX_CONFIRM_ID) अणु
		ret = wsm_multi_tx_confirm(priv, &wsm_buf, link_id);
	पूर्ण अन्यथा अगर (id & 0x0400) अणु
		व्योम *wsm_arg;
		u16 wsm_cmd;

		/* Do not trust FW too much. Protection against repeated
		 * response and race condition removal (see above).
		 */
		spin_lock(&priv->wsm_cmd.lock);
		wsm_arg = priv->wsm_cmd.arg;
		wsm_cmd = priv->wsm_cmd.cmd &
				~WSM_TX_LINK_ID(WSM_TX_LINK_ID_MAX);
		priv->wsm_cmd.cmd = 0xFFFF;
		spin_unlock(&priv->wsm_cmd.lock);

		अगर (WARN_ON((id & ~0x0400) != wsm_cmd)) अणु
			/* Note that any non-zero is a fatal retcode. */
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		/* Note that wsm_arg can be शून्य in हाल of समयout in
		 * wsm_cmd_send().
		 */

		चयन (id) अणु
		हाल WSM_READ_MIB_RESP_ID:
			अगर (wsm_arg)
				ret = wsm_पढ़ो_mib_confirm(priv, wsm_arg,
								&wsm_buf);
			अवरोध;
		हाल WSM_WRITE_MIB_RESP_ID:
			अगर (wsm_arg)
				ret = wsm_ग_लिखो_mib_confirm(priv, wsm_arg,
							    &wsm_buf);
			अवरोध;
		हाल WSM_START_SCAN_RESP_ID:
			अगर (wsm_arg)
				ret = wsm_scan_started(priv, wsm_arg, &wsm_buf);
			अवरोध;
		हाल WSM_CONFIGURATION_RESP_ID:
			अगर (wsm_arg)
				ret = wsm_configuration_confirm(priv, wsm_arg,
								&wsm_buf);
			अवरोध;
		हाल WSM_JOIN_RESP_ID:
			अगर (wsm_arg)
				ret = wsm_join_confirm(priv, wsm_arg, &wsm_buf);
			अवरोध;
		हाल WSM_STOP_SCAN_RESP_ID:
		हाल WSM_RESET_RESP_ID:
		हाल WSM_ADD_KEY_RESP_ID:
		हाल WSM_REMOVE_KEY_RESP_ID:
		हाल WSM_SET_PM_RESP_ID:
		हाल WSM_SET_BSS_PARAMS_RESP_ID:
		हाल 0x0412: /* set_tx_queue_params */
		हाल WSM_EDCA_PARAMS_RESP_ID:
		हाल WSM_SWITCH_CHANNEL_RESP_ID:
		हाल WSM_START_RESP_ID:
		हाल WSM_BEACON_TRANSMIT_RESP_ID:
		हाल 0x0419: /* start_find */
		हाल 0x041A: /* stop_find */
		हाल 0x041B: /* update_ie */
		हाल 0x041C: /* map_link */
			WARN_ON(wsm_arg != शून्य);
			ret = wsm_generic_confirm(priv, wsm_arg, &wsm_buf);
			अगर (ret) अणु
				wiphy_warn(priv->hw->wiphy,
					   "wsm_generic_confirm failed for request 0x%04x.\n",
					   id & ~0x0400);

				/* often 0x407 and 0x410 occur, this means we're dead.. */
				अगर (priv->join_status >= CW1200_JOIN_STATUS_JOINING) अणु
					wsm_lock_tx(priv);
					अगर (queue_work(priv->workqueue, &priv->unjoin_work) <= 0)
						wsm_unlock_tx(priv);
				पूर्ण
			पूर्ण
			अवरोध;
		शेष:
			wiphy_warn(priv->hw->wiphy,
				   "Unrecognized confirmation 0x%04x\n",
				   id & ~0x0400);
		पूर्ण

		spin_lock(&priv->wsm_cmd.lock);
		priv->wsm_cmd.ret = ret;
		priv->wsm_cmd.करोne = 1;
		spin_unlock(&priv->wsm_cmd.lock);

		ret = 0; /* Error response from device should ne stop BH. */

		wake_up(&priv->wsm_cmd_wq);
	पूर्ण अन्यथा अगर (id & 0x0800) अणु
		चयन (id) अणु
		हाल WSM_STARTUP_IND_ID:
			ret = wsm_startup_indication(priv, &wsm_buf);
			अवरोध;
		हाल WSM_RECEIVE_IND_ID:
			ret = wsm_receive_indication(priv, link_id,
						     &wsm_buf, skb_p);
			अवरोध;
		हाल 0x0805:
			ret = wsm_event_indication(priv, &wsm_buf);
			अवरोध;
		हाल WSM_SCAN_COMPLETE_IND_ID:
			ret = wsm_scan_complete_indication(priv, &wsm_buf);
			अवरोध;
		हाल 0x0808:
			ret = wsm_ba_समयout_indication(priv, &wsm_buf);
			अवरोध;
		हाल 0x0809:
			ret = wsm_set_pm_indication(priv, &wsm_buf);
			अवरोध;
		हाल 0x080A:
			ret = wsm_channel_चयन_indication(priv, &wsm_buf);
			अवरोध;
		हाल 0x080B:
			ret = wsm_find_complete_indication(priv, &wsm_buf);
			अवरोध;
		हाल 0x080C:
			ret = wsm_suspend_resume_indication(priv,
					link_id, &wsm_buf);
			अवरोध;
		हाल 0x080F:
			ret = wsm_join_complete_indication(priv, &wsm_buf);
			अवरोध;
		शेष:
			pr_warn("Unrecognised WSM ID %04x\n", id);
		पूर्ण
	पूर्ण अन्यथा अणु
		WARN_ON(1);
		ret = -EINVAL;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल bool wsm_handle_tx_data(काष्ठा cw1200_common *priv,
			       काष्ठा wsm_tx *wsm,
			       स्थिर काष्ठा ieee80211_tx_info *tx_info,
			       स्थिर काष्ठा cw1200_txpriv *txpriv,
			       काष्ठा cw1200_queue *queue)
अणु
	bool handled = false;
	स्थिर काष्ठा ieee80211_hdr *frame =
		(काष्ठा ieee80211_hdr *)&((u8 *)wsm)[txpriv->offset];
	__le16 fctl = frame->frame_control;
	क्रमागत अणु
		करो_probe,
		करो_drop,
		करो_wep,
		करो_tx,
	पूर्ण action = करो_tx;

	चयन (priv->mode) अणु
	हाल NL80211_IFTYPE_STATION:
		अगर (priv->join_status == CW1200_JOIN_STATUS_MONITOR)
			action = करो_tx;
		अन्यथा अगर (priv->join_status < CW1200_JOIN_STATUS_PRE_STA)
			action = करो_drop;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		अगर (!priv->join_status) अणु
			action = करो_drop;
		पूर्ण अन्यथा अगर (!(BIT(txpriv->raw_link_id) &
			     (BIT(0) | priv->link_id_map))) अणु
			wiphy_warn(priv->hw->wiphy,
				   "A frame with expired link id is dropped.\n");
			action = करो_drop;
		पूर्ण
		अगर (cw1200_queue_get_generation(wsm->packet_id) >
				CW1200_MAX_REQUEUE_ATTEMPTS) अणु
			/* HACK!!! WSM324 firmware has tendency to requeue
			 * multicast frames in a loop, causing perक्रमmance
			 * drop and high घातer consumption of the driver.
			 * In this situation it is better just to drop
			 * the problematic frame.
			 */
			wiphy_warn(priv->hw->wiphy,
				   "Too many attempts to requeue a frame; dropped.\n");
			action = करो_drop;
		पूर्ण
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		अगर (priv->join_status != CW1200_JOIN_STATUS_IBSS)
			action = करो_drop;
		अवरोध;
	हाल NL80211_IFTYPE_MESH_POINT:
		action = करो_tx; /* TODO:  Test me! */
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
	शेष:
		action = करो_drop;
		अवरोध;
	पूर्ण

	अगर (action == करो_tx) अणु
		अगर (ieee80211_is_nullfunc(fctl)) अणु
			spin_lock(&priv->bss_loss_lock);
			अगर (priv->bss_loss_state) अणु
				priv->bss_loss_confirm_id = wsm->packet_id;
				wsm->queue_id = WSM_QUEUE_VOICE;
			पूर्ण
			spin_unlock(&priv->bss_loss_lock);
		पूर्ण अन्यथा अगर (ieee80211_is_probe_req(fctl)) अणु
			action = करो_probe;
		पूर्ण अन्यथा अगर (ieee80211_is_deauth(fctl) &&
			   priv->mode != NL80211_IFTYPE_AP) अणु
			pr_debug("[WSM] Issue unjoin command due to tx deauth.\n");
			wsm_lock_tx_async(priv);
			अगर (queue_work(priv->workqueue,
				       &priv->unjoin_work) <= 0)
				wsm_unlock_tx(priv);
		पूर्ण अन्यथा अगर (ieee80211_has_रक्षित(fctl) &&
			   tx_info->control.hw_key &&
			   tx_info->control.hw_key->keyidx != priv->wep_शेष_key_id &&
			   (tx_info->control.hw_key->cipher == WLAN_CIPHER_SUITE_WEP40 ||
			    tx_info->control.hw_key->cipher == WLAN_CIPHER_SUITE_WEP104)) अणु
			action = करो_wep;
		पूर्ण
	पूर्ण

	चयन (action) अणु
	हाल करो_probe:
		/* An पूर्णांकeresting FW "feature". Device filters probe responses.
		 * The easiest way to get it back is to convert
		 * probe request पूर्णांकo WSM start_scan command.
		 */
		pr_debug("[WSM] Convert probe request to scan.\n");
		wsm_lock_tx_async(priv);
		priv->pending_frame_id = wsm->packet_id;
		अगर (queue_delayed_work(priv->workqueue,
				       &priv->scan.probe_work, 0) <= 0)
			wsm_unlock_tx(priv);
		handled = true;
		अवरोध;
	हाल करो_drop:
		pr_debug("[WSM] Drop frame (0x%.4X).\n", fctl);
		BUG_ON(cw1200_queue_हटाओ(queue, wsm->packet_id));
		handled = true;
		अवरोध;
	हाल करो_wep:
		pr_debug("[WSM] Issue set_default_wep_key.\n");
		wsm_lock_tx_async(priv);
		priv->wep_शेष_key_id = tx_info->control.hw_key->keyidx;
		priv->pending_frame_id = wsm->packet_id;
		अगर (queue_work(priv->workqueue, &priv->wep_key_work) <= 0)
			wsm_unlock_tx(priv);
		handled = true;
		अवरोध;
	हाल करो_tx:
		pr_debug("[WSM] Transmit frame.\n");
		अवरोध;
	शेष:
		/* Do nothing */
		अवरोध;
	पूर्ण
	वापस handled;
पूर्ण

अटल पूर्णांक cw1200_get_prio_queue(काष्ठा cw1200_common *priv,
				 u32 link_id_map, पूर्णांक *total)
अणु
	अटल स्थिर पूर्णांक urgent = BIT(CW1200_LINK_ID_AFTER_DTIM) |
		BIT(CW1200_LINK_ID_UAPSD);
	काष्ठा wsm_edca_queue_params *edca;
	अचिन्हित score, best = -1;
	पूर्णांक winner = -1;
	पूर्णांक queued;
	पूर्णांक i;

	/* search क्रम a winner using edca params */
	क्रम (i = 0; i < 4; ++i) अणु
		queued = cw1200_queue_get_num_queued(&priv->tx_queue[i],
				link_id_map);
		अगर (!queued)
			जारी;
		*total += queued;
		edca = &priv->edca.params[i];
		score = ((edca->aअगरns + edca->cwmin) << 16) +
			((edca->cwmax - edca->cwmin) *
			 (get_अक्रमom_पूर्णांक() & 0xFFFF));
		अगर (score < best && (winner < 0 || i != 3)) अणु
			best = score;
			winner = i;
		पूर्ण
	पूर्ण

	/* override winner अगर bursting */
	अगर (winner >= 0 && priv->tx_burst_idx >= 0 &&
	    winner != priv->tx_burst_idx &&
	    !cw1200_queue_get_num_queued(
		    &priv->tx_queue[winner],
		    link_id_map & urgent) &&
	    cw1200_queue_get_num_queued(
		    &priv->tx_queue[priv->tx_burst_idx],
		    link_id_map))
		winner = priv->tx_burst_idx;

	वापस winner;
पूर्ण

अटल पूर्णांक wsm_get_tx_queue_and_mask(काष्ठा cw1200_common *priv,
				     काष्ठा cw1200_queue **queue_p,
				     u32 *tx_allowed_mask_p,
				     bool *more)
अणु
	पूर्णांक idx;
	u32 tx_allowed_mask;
	पूर्णांक total = 0;

	/* Search क्रम a queue with multicast frames buffered */
	अगर (priv->tx_multicast) अणु
		tx_allowed_mask = BIT(CW1200_LINK_ID_AFTER_DTIM);
		idx = cw1200_get_prio_queue(priv,
				tx_allowed_mask, &total);
		अगर (idx >= 0) अणु
			*more = total > 1;
			जाओ found;
		पूर्ण
	पूर्ण

	/* Search क्रम unicast traffic */
	tx_allowed_mask = ~priv->sta_asleep_mask;
	tx_allowed_mask |= BIT(CW1200_LINK_ID_UAPSD);
	अगर (priv->sta_asleep_mask) अणु
		tx_allowed_mask |= priv->pspoll_mask;
		tx_allowed_mask &= ~BIT(CW1200_LINK_ID_AFTER_DTIM);
	पूर्ण अन्यथा अणु
		tx_allowed_mask |= BIT(CW1200_LINK_ID_AFTER_DTIM);
	पूर्ण
	idx = cw1200_get_prio_queue(priv,
			tx_allowed_mask, &total);
	अगर (idx < 0)
		वापस -ENOENT;

found:
	*queue_p = &priv->tx_queue[idx];
	*tx_allowed_mask_p = tx_allowed_mask;
	वापस 0;
पूर्ण

पूर्णांक wsm_get_tx(काष्ठा cw1200_common *priv, u8 **data,
	       माप_प्रकार *tx_len, पूर्णांक *burst)
अणु
	काष्ठा wsm_tx *wsm = शून्य;
	काष्ठा ieee80211_tx_info *tx_info;
	काष्ठा cw1200_queue *queue = शून्य;
	पूर्णांक queue_num;
	u32 tx_allowed_mask = 0;
	स्थिर काष्ठा cw1200_txpriv *txpriv = शून्य;
	पूर्णांक count = 0;

	/* More is used only क्रम broadcasts. */
	bool more = false;

	अगर (priv->wsm_cmd.ptr) अणु /* CMD request */
		++count;
		spin_lock(&priv->wsm_cmd.lock);
		BUG_ON(!priv->wsm_cmd.ptr);
		*data = priv->wsm_cmd.ptr;
		*tx_len = priv->wsm_cmd.len;
		*burst = 1;
		spin_unlock(&priv->wsm_cmd.lock);
	पूर्ण अन्यथा अणु
		क्रम (;;) अणु
			पूर्णांक ret;

			अगर (atomic_add_वापस(0, &priv->tx_lock))
				अवरोध;

			spin_lock_bh(&priv->ps_state_lock);

			ret = wsm_get_tx_queue_and_mask(priv, &queue,
							&tx_allowed_mask, &more);
			queue_num = queue - priv->tx_queue;

			अगर (priv->buffered_multicasts &&
			    (ret || !more) &&
			    (priv->tx_multicast || !priv->sta_asleep_mask)) अणु
				priv->buffered_multicasts = false;
				अगर (priv->tx_multicast) अणु
					priv->tx_multicast = false;
					queue_work(priv->workqueue,
						   &priv->multicast_stop_work);
				पूर्ण
			पूर्ण

			spin_unlock_bh(&priv->ps_state_lock);

			अगर (ret)
				अवरोध;

			अगर (cw1200_queue_get(queue,
					     tx_allowed_mask,
					     &wsm, &tx_info, &txpriv))
				जारी;

			अगर (wsm_handle_tx_data(priv, wsm,
					       tx_info, txpriv, queue))
				जारी;  /* Handled by WSM */

			wsm->hdr.id &= __cpu_to_le16(
				~WSM_TX_LINK_ID(WSM_TX_LINK_ID_MAX));
			wsm->hdr.id |= cpu_to_le16(
				WSM_TX_LINK_ID(txpriv->raw_link_id));
			priv->pspoll_mask &= ~BIT(txpriv->raw_link_id);

			*data = (u8 *)wsm;
			*tx_len = __le16_to_cpu(wsm->hdr.len);

			/* allow bursting अगर txop is set */
			अगर (priv->edca.params[queue_num].txop_limit)
				*burst = min(*burst,
					     (पूर्णांक)cw1200_queue_get_num_queued(queue, tx_allowed_mask) + 1);
			अन्यथा
				*burst = 1;

			/* store index of bursting queue */
			अगर (*burst > 1)
				priv->tx_burst_idx = queue_num;
			अन्यथा
				priv->tx_burst_idx = -1;

			अगर (more) अणु
				काष्ठा ieee80211_hdr *hdr =
					(काष्ठा ieee80211_hdr *)
					&((u8 *)wsm)[txpriv->offset];
				/* more buffered multicast/broadcast frames
				 *  ==> set MoreData flag in IEEE 802.11 header
				 *  to inक्रमm PS STAs
				 */
				hdr->frame_control |=
					cpu_to_le16(IEEE80211_FCTL_MOREDATA);
			पूर्ण

			pr_debug("[WSM] >>> 0x%.4X (%zu) %p %c\n",
				 0x0004, *tx_len, *data,
				 wsm->more ? 'M' : ' ');
			++count;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

व्योम wsm_txed(काष्ठा cw1200_common *priv, u8 *data)
अणु
	अगर (data == priv->wsm_cmd.ptr) अणु
		spin_lock(&priv->wsm_cmd.lock);
		priv->wsm_cmd.ptr = शून्य;
		spin_unlock(&priv->wsm_cmd.lock);
	पूर्ण
पूर्ण

/* ******************************************************************** */
/* WSM buffer								*/

व्योम wsm_buf_init(काष्ठा wsm_buf *buf)
अणु
	BUG_ON(buf->begin);
	buf->begin = kदो_स्मृति(FWLOAD_BLOCK_SIZE, GFP_KERNEL | GFP_DMA);
	buf->end = buf->begin ? &buf->begin[FWLOAD_BLOCK_SIZE] : buf->begin;
	wsm_buf_reset(buf);
पूर्ण

व्योम wsm_buf_deinit(काष्ठा wsm_buf *buf)
अणु
	kमुक्त(buf->begin);
	buf->begin = buf->data = buf->end = शून्य;
पूर्ण

अटल व्योम wsm_buf_reset(काष्ठा wsm_buf *buf)
अणु
	अगर (buf->begin) अणु
		buf->data = &buf->begin[4];
		*(u32 *)buf->begin = 0;
	पूर्ण अन्यथा अणु
		buf->data = buf->begin;
	पूर्ण
पूर्ण

अटल पूर्णांक wsm_buf_reserve(काष्ठा wsm_buf *buf, माप_प्रकार extra_size)
अणु
	माप_प्रकार pos = buf->data - buf->begin;
	माप_प्रकार size = pos + extra_size;
	u8 *पंचांगp;

	size = round_up(size, FWLOAD_BLOCK_SIZE);

	पंचांगp = kपुनः_स्मृति(buf->begin, size, GFP_KERNEL | GFP_DMA);
	अगर (!पंचांगp) अणु
		wsm_buf_deinit(buf);
		वापस -ENOMEM;
	पूर्ण

	buf->begin = पंचांगp;
	buf->data = &buf->begin[pos];
	buf->end = &buf->begin[size];
	वापस 0;
पूर्ण
