<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner
 */

#समावेश "gateway_common.h"
#समावेश "main.h"

#समावेश <linux/atomic.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/math64.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <uapi/linux/batadv_packet.h>
#समावेश <uapi/linux/baपंचांगan_adv.h>

#समावेश "gateway_client.h"
#समावेश "log.h"
#समावेश "tvlv.h"

/**
 * batadv_parse_throughput() - parse supplied string buffer to extract
 *  throughput inक्रमmation
 * @net_dev: the soft पूर्णांकerface net device
 * @buff: string buffer to parse
 * @description: text shown when throughput string cannot be parsed
 * @throughput: poपूर्णांकer holding the वापसed throughput inक्रमmation
 *
 * Return: false on parse error and true otherwise.
 */
bool batadv_parse_throughput(काष्ठा net_device *net_dev, अक्षर *buff,
			     स्थिर अक्षर *description, u32 *throughput)
अणु
	क्रमागत batadv_bandwidth_units bw_unit_type = BATADV_BW_UNIT_KBIT;
	u64 lthroughput;
	अक्षर *पंचांगp_ptr;
	पूर्णांक ret;

	अगर (म_माप(buff) > 4) अणु
		पंचांगp_ptr = buff + म_माप(buff) - 4;

		अगर (strnहालcmp(पंचांगp_ptr, "mbit", 4) == 0)
			bw_unit_type = BATADV_BW_UNIT_MBIT;

		अगर (strnहालcmp(पंचांगp_ptr, "kbit", 4) == 0 ||
		    bw_unit_type == BATADV_BW_UNIT_MBIT)
			*पंचांगp_ptr = '\0';
	पूर्ण

	ret = kstrtou64(buff, 10, &lthroughput);
	अगर (ret) अणु
		batadv_err(net_dev,
			   "Invalid throughput speed for %s: %s\n",
			   description, buff);
		वापस false;
	पूर्ण

	चयन (bw_unit_type) अणु
	हाल BATADV_BW_UNIT_MBIT:
		/* prevent overflow */
		अगर (U64_MAX / 10 < lthroughput) अणु
			batadv_err(net_dev,
				   "Throughput speed for %s too large: %s\n",
				   description, buff);
			वापस false;
		पूर्ण

		lthroughput *= 10;
		अवरोध;
	हाल BATADV_BW_UNIT_KBIT:
	शेष:
		lthroughput = भाग_u64(lthroughput, 100);
		अवरोध;
	पूर्ण

	अगर (lthroughput > U32_MAX) अणु
		batadv_err(net_dev,
			   "Throughput speed for %s too large: %s\n",
			   description, buff);
		वापस false;
	पूर्ण

	*throughput = lthroughput;

	वापस true;
पूर्ण

/**
 * batadv_parse_gw_bandwidth() - parse supplied string buffer to extract
 *  करोwnload and upload bandwidth inक्रमmation
 * @net_dev: the soft पूर्णांकerface net device
 * @buff: string buffer to parse
 * @करोwn: poपूर्णांकer holding the वापसed करोwnload bandwidth inक्रमmation
 * @up: poपूर्णांकer holding the वापसed upload bandwidth inक्रमmation
 *
 * Return: false on parse error and true otherwise.
 */
अटल bool batadv_parse_gw_bandwidth(काष्ठा net_device *net_dev, अक्षर *buff,
				      u32 *करोwn, u32 *up)
अणु
	अक्षर *slash_ptr;
	bool ret;

	slash_ptr = म_अक्षर(buff, '/');
	अगर (slash_ptr)
		*slash_ptr = 0;

	ret = batadv_parse_throughput(net_dev, buff, "download gateway speed",
				      करोwn);
	अगर (!ret)
		वापस false;

	/* we also got some upload info */
	अगर (slash_ptr) अणु
		ret = batadv_parse_throughput(net_dev, slash_ptr + 1,
					      "upload gateway speed", up);
		अगर (!ret)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * batadv_gw_tvlv_container_update() - update the gw tvlv container after
 *  gateway setting change
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
व्योम batadv_gw_tvlv_container_update(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_tvlv_gateway_data gw;
	u32 करोwn, up;
	अक्षर gw_mode;

	gw_mode = atomic_पढ़ो(&bat_priv->gw.mode);

	चयन (gw_mode) अणु
	हाल BATADV_GW_MODE_OFF:
	हाल BATADV_GW_MODE_CLIENT:
		batadv_tvlv_container_unरेजिस्टर(bat_priv, BATADV_TVLV_GW, 1);
		अवरोध;
	हाल BATADV_GW_MODE_SERVER:
		करोwn = atomic_पढ़ो(&bat_priv->gw.bandwidth_करोwn);
		up = atomic_पढ़ो(&bat_priv->gw.bandwidth_up);
		gw.bandwidth_करोwn = htonl(करोwn);
		gw.bandwidth_up = htonl(up);
		batadv_tvlv_container_रेजिस्टर(bat_priv, BATADV_TVLV_GW, 1,
					       &gw, माप(gw));
		अवरोध;
	पूर्ण
पूर्ण

/**
 * batadv_gw_bandwidth_set() - Parse and set करोwnload/upload gateway bandwidth
 *  from supplied string buffer
 * @net_dev: netdev काष्ठा of the soft पूर्णांकerface
 * @buff: the buffer containing the user data
 * @count: number of bytes in the buffer
 *
 * Return: 'count' on success or a negative error code in हाल of failure
 */
sमाप_प्रकार batadv_gw_bandwidth_set(काष्ठा net_device *net_dev, अक्षर *buff,
				माप_प्रकार count)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(net_dev);
	u32 करोwn_curr;
	u32 up_curr;
	u32 करोwn_new = 0;
	u32 up_new = 0;
	bool ret;

	करोwn_curr = (अचिन्हित पूर्णांक)atomic_पढ़ो(&bat_priv->gw.bandwidth_करोwn);
	up_curr = (अचिन्हित पूर्णांक)atomic_पढ़ो(&bat_priv->gw.bandwidth_up);

	ret = batadv_parse_gw_bandwidth(net_dev, buff, &करोwn_new, &up_new);
	अगर (!ret)
		वापस -EINVAL;

	अगर (!करोwn_new)
		करोwn_new = 1;

	अगर (!up_new)
		up_new = करोwn_new / 5;

	अगर (!up_new)
		up_new = 1;

	अगर (करोwn_curr == करोwn_new && up_curr == up_new)
		वापस count;

	batadv_gw_reselect(bat_priv);
	batadv_info(net_dev,
		    "Changing gateway bandwidth from: '%u.%u/%u.%u MBit' to: '%u.%u/%u.%u MBit'\n",
		    करोwn_curr / 10, करोwn_curr % 10, up_curr / 10, up_curr % 10,
		    करोwn_new / 10, करोwn_new % 10, up_new / 10, up_new % 10);

	atomic_set(&bat_priv->gw.bandwidth_करोwn, करोwn_new);
	atomic_set(&bat_priv->gw.bandwidth_up, up_new);
	batadv_gw_tvlv_container_update(bat_priv);

	वापस count;
पूर्ण

/**
 * batadv_gw_tvlv_ogm_handler_v1() - process incoming gateway tvlv container
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig: the orig_node of the ogm
 * @flags: flags indicating the tvlv state (see batadv_tvlv_handler_flags)
 * @tvlv_value: tvlv buffer containing the gateway data
 * @tvlv_value_len: tvlv buffer length
 */
अटल व्योम batadv_gw_tvlv_ogm_handler_v1(काष्ठा batadv_priv *bat_priv,
					  काष्ठा batadv_orig_node *orig,
					  u8 flags,
					  व्योम *tvlv_value, u16 tvlv_value_len)
अणु
	काष्ठा batadv_tvlv_gateway_data gateway, *gateway_ptr;

	/* only fetch the tvlv value अगर the handler wasn't called via the
	 * CIFNOTFND flag and अगर there is data to fetch
	 */
	अगर (flags & BATADV_TVLV_HANDLER_OGM_CIFNOTFND ||
	    tvlv_value_len < माप(gateway)) अणु
		gateway.bandwidth_करोwn = 0;
		gateway.bandwidth_up = 0;
	पूर्ण अन्यथा अणु
		gateway_ptr = tvlv_value;
		gateway.bandwidth_करोwn = gateway_ptr->bandwidth_करोwn;
		gateway.bandwidth_up = gateway_ptr->bandwidth_up;
		अगर (gateway.bandwidth_करोwn == 0 ||
		    gateway.bandwidth_up == 0) अणु
			gateway.bandwidth_करोwn = 0;
			gateway.bandwidth_up = 0;
		पूर्ण
	पूर्ण

	batadv_gw_node_update(bat_priv, orig, &gateway);

	/* restart gateway selection */
	अगर (gateway.bandwidth_करोwn != 0 &&
	    atomic_पढ़ो(&bat_priv->gw.mode) == BATADV_GW_MODE_CLIENT)
		batadv_gw_check_election(bat_priv, orig);
पूर्ण

/**
 * batadv_gw_init() - initialise the gateway handling पूर्णांकernals
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
व्योम batadv_gw_init(काष्ठा batadv_priv *bat_priv)
अणु
	अगर (bat_priv->algo_ops->gw.init_sel_class)
		bat_priv->algo_ops->gw.init_sel_class(bat_priv);
	अन्यथा
		atomic_set(&bat_priv->gw.sel_class, 1);

	batadv_tvlv_handler_रेजिस्टर(bat_priv, batadv_gw_tvlv_ogm_handler_v1,
				     शून्य, BATADV_TVLV_GW, 1,
				     BATADV_TVLV_HANDLER_OGM_CIFNOTFND);
पूर्ण

/**
 * batadv_gw_मुक्त() - मुक्त the gateway handling पूर्णांकernals
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
व्योम batadv_gw_मुक्त(काष्ठा batadv_priv *bat_priv)
अणु
	batadv_tvlv_container_unरेजिस्टर(bat_priv, BATADV_TVLV_GW, 1);
	batadv_tvlv_handler_unरेजिस्टर(bat_priv, BATADV_TVLV_GW, 1);
पूर्ण
