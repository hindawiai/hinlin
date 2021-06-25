<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************
 *
 * Copyright(c) 2009 - 2014 Intel Corporation. All rights reserved.
 * Copyright(C) 2016        Intel Deutschland GmbH
 * Copyright(c) 2018        Intel Corporation
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#अगर_अघोषित __IWLWIFI_DEVICE_TRACE
#समावेश <linux/skbuff.h>
#समावेश <linux/ieee80211.h>
#समावेश <net/cfg80211.h>
#समावेश "iwl-trans.h"
#अगर !defined(__IWLWIFI_DEVICE_TRACE)
अटल अंतरभूत bool iwl_trace_data(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	__le16 fc = hdr->frame_control;
	पूर्णांक offs = 24; /* start with normal header length */

	अगर (!ieee80211_is_data(fc))
		वापस false;

	/* Try to determine अगर the frame is EAPOL. This might have false
	 * positives (अगर there's no RFC 1042 header and we compare to some
	 * payload instead) but since we're only doing tracing that's not
	 * a problem.
	 */

	अगर (ieee80211_has_a4(fc))
		offs += 6;
	अगर (ieee80211_is_data_qos(fc))
		offs += 2;
	/* करोn't account क्रम crypto - these are unencrypted */

	/* also account क्रम the RFC 1042 header, of course */
	offs += 6;

	वापस skb->len <= offs + 2 ||
		*(__be16 *)(skb->data + offs) != cpu_to_be16(ETH_P_PAE);
पूर्ण

अटल अंतरभूत माप_प्रकार iwl_rx_trace_len(स्थिर काष्ठा iwl_trans *trans,
				      व्योम *rxbuf, माप_प्रकार len,
				      माप_प्रकार *out_hdr_offset)
अणु
	काष्ठा iwl_cmd_header *cmd = (व्योम *)((u8 *)rxbuf + माप(__le32));
	काष्ठा ieee80211_hdr *hdr = शून्य;
	माप_प्रकार hdr_offset;

	अगर (cmd->cmd != trans->rx_mpdu_cmd)
		वापस len;

	hdr_offset = माप(काष्ठा iwl_cmd_header) +
		     trans->rx_mpdu_cmd_hdr_size;

	अगर (out_hdr_offset)
		*out_hdr_offset = hdr_offset;

	hdr = (व्योम *)((u8 *)cmd + hdr_offset);
	अगर (!ieee80211_is_data(hdr->frame_control))
		वापस len;
	/* maybe try to identअगरy EAPOL frames? */
	वापस माप(__le32) + माप(*cmd) + trans->rx_mpdu_cmd_hdr_size +
		ieee80211_hdrlen(hdr->frame_control);
पूर्ण
#पूर्ण_अगर

#घोषणा __IWLWIFI_DEVICE_TRACE

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/device.h>


#अगर !defined(CONFIG_IWLWIFI_DEVICE_TRACING) || defined(__CHECKER__)
#अघोषित TRACE_EVENT
#घोषणा TRACE_EVENT(name, proto, ...) \
अटल अंतरभूत व्योम trace_ ## name(proto) अणुपूर्ण
#अघोषित DECLARE_EVENT_CLASS
#घोषणा DECLARE_EVENT_CLASS(...)
#अघोषित DEFINE_EVENT
#घोषणा DEFINE_EVENT(evt_class, name, proto, ...) \
अटल अंतरभूत व्योम trace_ ## name(proto) अणुपूर्ण
#पूर्ण_अगर

#घोषणा DEV_ENTRY	__string(dev, dev_name(dev))
#घोषणा DEV_ASSIGN	__assign_str(dev, dev_name(dev))

#समावेश "iwl-devtrace-io.h"
#समावेश "iwl-devtrace-ucode.h"
#समावेश "iwl-devtrace-msg.h"
#समावेश "iwl-devtrace-data.h"
#समावेश "iwl-devtrace-iwlwifi.h"

#पूर्ण_अगर /* __IWLWIFI_DEVICE_TRACE */
