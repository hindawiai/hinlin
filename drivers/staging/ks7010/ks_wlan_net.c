<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *   Driver क्रम KeyStream 11b/g wireless LAN
 *
 *   Copyright (C) 2005-2008 KeyStream Corp.
 *   Copyright (C) 2009 Renesas Technology Corp.
 */

#समावेश <linux/atomic.h>
#समावेश <linux/completion.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/समयr.h>
#समावेश <linux/uaccess.h>

अटल पूर्णांक wep_on_off;
#घोषणा	WEP_OFF		0
#घोषणा	WEP_ON_64BIT	1
#घोषणा	WEP_ON_128BIT	2

#समावेश "ks_wlan.h"
#समावेश "ks_hostif.h"
#समावेश "ks_wlan_ioctl.h"

/* Include Wireless Extension definition and check version */
#समावेश <linux/wireless.h>
#घोषणा WIRELESS_SPY	/* enable iwspy support */
#समावेश <net/iw_handler.h>	/* New driver API */

/* Frequency list (map channels to frequencies) */
अटल स्थिर दीर्घ frequency_list[] = अणु
	2412, 2417, 2422, 2427, 2432, 2437, 2442,
	2447, 2452, 2457, 2462, 2467, 2472, 2484
पूर्ण;

/* A few details needed क्रम WEP (Wireless Equivalent Privacy) */
#घोषणा MAX_KEY_SIZE 13	/* 128 (?) bits */
#घोषणा MIN_KEY_SIZE  5	/* 40 bits RC4 - WEP */
काष्ठा wep_key अणु
	u16 len;
	u8 key[16];	/* 40-bit and 104-bit keys */
पूर्ण;

/*
 *	function prototypes
 */
अटल पूर्णांक ks_wlan_खोलो(काष्ठा net_device *dev);
अटल व्योम ks_wlan_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल netdev_tx_t ks_wlan_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल पूर्णांक ks_wlan_बंद(काष्ठा net_device *dev);
अटल व्योम ks_wlan_set_rx_mode(काष्ठा net_device *dev);
अटल काष्ठा net_device_stats *ks_wlan_get_stats(काष्ठा net_device *dev);
अटल पूर्णांक ks_wlan_set_mac_address(काष्ठा net_device *dev, व्योम *addr);
अटल पूर्णांक ks_wlan_netdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq,
				पूर्णांक cmd);

अटल atomic_t update_phyinfo;
अटल काष्ठा समयr_list update_phyinfo_समयr;
अटल
पूर्णांक ks_wlan_update_phy_inक्रमmation(काष्ठा ks_wlan_निजी *priv)
अणु
	काष्ठा iw_statistics *wstats = &priv->wstats;

	netdev_dbg(priv->net_dev, "in_interrupt = %ld\n", in_पूर्णांकerrupt());

	अगर (priv->dev_state < DEVICE_STATE_READY)
		वापस -EBUSY;	/* not finished initialize */

	अगर (atomic_पढ़ो(&update_phyinfo))
		वापस -EPERM;

	/* The status */
	wstats->status = priv->reg.operation_mode;	/* Operation mode */

	/* Signal quality and co. But where is the noise level ??? */
	hostअगर_sme_enqueue(priv, SME_PHY_INFO_REQUEST);

	/* पूर्णांकerruptible_sleep_on_समयout(&priv->confirm_रुको, HZ/2); */
	अगर (!रुको_क्रम_completion_पूर्णांकerruptible_समयout
	    (&priv->confirm_रुको, HZ / 2)) अणु
		netdev_dbg(priv->net_dev, "wait time out!!\n");
	पूर्ण

	atomic_inc(&update_phyinfo);
	update_phyinfo_समयr.expires = jअगरfies + HZ;	/* 1sec */
	add_समयr(&update_phyinfo_समयr);

	वापस 0;
पूर्ण

अटल
व्योम ks_wlan_update_phyinfo_समयout(काष्ठा समयr_list *unused)
अणु
	pr_debug("in_interrupt = %ld\n", in_पूर्णांकerrupt());
	atomic_set(&update_phyinfo, 0);
पूर्ण

पूर्णांक ks_wlan_setup_parameter(काष्ठा ks_wlan_निजी *priv,
			    अचिन्हित पूर्णांक commit_flag)
अणु
	hostअगर_sme_enqueue(priv, SME_STOP_REQUEST);

	अगर (commit_flag & SME_RTS)
		hostअगर_sme_enqueue(priv, SME_RTS_THRESHOLD_REQUEST);
	अगर (commit_flag & SME_FRAG)
		hostअगर_sme_enqueue(priv, SME_FRAGMENTATION_THRESHOLD_REQUEST);

	अगर (commit_flag & SME_WEP_INDEX)
		hostअगर_sme_enqueue(priv, SME_WEP_INDEX_REQUEST);
	अगर (commit_flag & SME_WEP_VAL1)
		hostअगर_sme_enqueue(priv, SME_WEP_KEY1_REQUEST);
	अगर (commit_flag & SME_WEP_VAL2)
		hostअगर_sme_enqueue(priv, SME_WEP_KEY2_REQUEST);
	अगर (commit_flag & SME_WEP_VAL3)
		hostअगर_sme_enqueue(priv, SME_WEP_KEY3_REQUEST);
	अगर (commit_flag & SME_WEP_VAL4)
		hostअगर_sme_enqueue(priv, SME_WEP_KEY4_REQUEST);
	अगर (commit_flag & SME_WEP_FLAG)
		hostअगर_sme_enqueue(priv, SME_WEP_FLAG_REQUEST);

	अगर (commit_flag & SME_RSN) अणु
		hostअगर_sme_enqueue(priv, SME_RSN_ENABLED_REQUEST);
		hostअगर_sme_enqueue(priv, SME_RSN_MODE_REQUEST);
	पूर्ण
	अगर (commit_flag & SME_RSN_MULTICAST)
		hostअगर_sme_enqueue(priv, SME_RSN_MCAST_REQUEST);
	अगर (commit_flag & SME_RSN_UNICAST)
		hostअगर_sme_enqueue(priv, SME_RSN_UCAST_REQUEST);
	अगर (commit_flag & SME_RSN_AUTH)
		hostअगर_sme_enqueue(priv, SME_RSN_AUTH_REQUEST);

	hostअगर_sme_enqueue(priv, SME_MODE_SET_REQUEST);

	hostअगर_sme_enqueue(priv, SME_START_REQUEST);

	वापस 0;
पूर्ण

/*
 * Initial Wireless Extension code क्रम Ks_Wlannet driver by :
 *	Jean Tourrilhes <jt@hpl.hp.com> - HPL - 17 November 00
 * Conversion to new driver API by :
 *	Jean Tourrilhes <jt@hpl.hp.com> - HPL - 26 March 02
 * Javier also did a good amount of work here, adding some new extensions
 * and fixing my code. Let's just say that without him this code just
 * would not work at all... - Jean II
 */

अटल पूर्णांक ks_wlan_get_name(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *cwrq,
			    अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	अगर (priv->dev_state < DEVICE_STATE_READY)
		म_नकल(cwrq->name, "NOT READY!");
	अन्यथा अगर (priv->reg.phy_type == D_11B_ONLY_MODE)
		म_नकल(cwrq->name, "IEEE 802.11b");
	अन्यथा अगर (priv->reg.phy_type == D_11G_ONLY_MODE)
		म_नकल(cwrq->name, "IEEE 802.11g");
	अन्यथा
		म_नकल(cwrq->name, "IEEE 802.11b/g");

	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_freq(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *fwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);
	पूर्णांक channel;

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	/* If setting by frequency, convert to a channel */
	अगर ((fwrq->freq.e == 1) &&
	    (fwrq->freq.m >= 241200000) && (fwrq->freq.m <= 248700000)) अणु
		पूर्णांक f = fwrq->freq.m / 100000;
		पूर्णांक c = 0;

		जबतक ((c < 14) && (f != frequency_list[c]))
			c++;
		/* Hack to fall through... */
		fwrq->freq.e = 0;
		fwrq->freq.m = c + 1;
	पूर्ण
	/* Setting by channel number */
	अगर ((fwrq->freq.m > 1000) || (fwrq->freq.e > 0))
		वापस -EOPNOTSUPP;

	channel = fwrq->freq.m;
	/* We should करो a better check than that,
	 * based on the card capability !!!
	 */
	अगर ((channel < 1) || (channel > 14)) अणु
		netdev_dbg(dev, "%s: New channel value of %d is invalid!\n",
			   dev->name, fwrq->freq.m);
		वापस -EINVAL;
	पूर्ण

	/* Yes ! We can set it !!! */
	priv->reg.channel = (u8)(channel);
	priv->need_commit |= SME_MODE_SET;

	वापस -EINPROGRESS;	/* Call commit handler */
पूर्ण

अटल पूर्णांक ks_wlan_get_freq(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *fwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);
	पूर्णांक f;

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	अगर (is_connect_status(priv->connect_status))
		f = (पूर्णांक)priv->current_ap.channel;
	अन्यथा
		f = (पूर्णांक)priv->reg.channel;

	fwrq->freq.m = frequency_list[f - 1] * 100000;
	fwrq->freq.e = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_essid(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *dwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);
	माप_प्रकार len;

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	/* Check अगर we asked क्रम `any' */
	अगर (!dwrq->essid.flags) अणु
		/* Just send an empty SSID list */
		स_रखो(priv->reg.ssid.body, 0, माप(priv->reg.ssid.body));
		priv->reg.ssid.size = 0;
	पूर्ण अन्यथा अणु
		len = dwrq->essid.length;
		/* iwconfig uses nul termination in SSID.. */
		अगर (len > 0 && extra[len - 1] == '\0')
			len--;

		/* Check the size of the string */
		अगर (len > IW_ESSID_MAX_SIZE)
			वापस -EINVAL;

		/* Set the SSID */
		स_रखो(priv->reg.ssid.body, 0, माप(priv->reg.ssid.body));
		स_नकल(priv->reg.ssid.body, extra, len);
		priv->reg.ssid.size = len;
	पूर्ण
	/* Write it to the card */
	priv->need_commit |= SME_MODE_SET;

	ks_wlan_setup_parameter(priv, priv->need_commit);
	priv->need_commit = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_get_essid(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *dwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	/* Note : अगर dwrq->flags != 0, we should
	 * get the relevant SSID from the SSID list...
	 */
	अगर (priv->reg.ssid.size != 0) अणु
		/* Get the current SSID */
		स_नकल(extra, priv->reg.ssid.body, priv->reg.ssid.size);

		/* If none, we may want to get the one that was set */

		/* Push it out ! */
		dwrq->essid.length = priv->reg.ssid.size;
		dwrq->essid.flags = 1;	/* active */
	पूर्ण अन्यथा अणु
		dwrq->essid.length = 0;
		dwrq->essid.flags = 0;	/* ANY */
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_wap(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *awrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	अगर (priv->reg.operation_mode != MODE_ADHOC &&
	    priv->reg.operation_mode != MODE_INFRASTRUCTURE) अणु
		eth_zero_addr(priv->reg.bssid);
		वापस -EOPNOTSUPP;
	पूर्ण

	ether_addr_copy(priv->reg.bssid, awrq->ap_addr.sa_data);
	अगर (is_valid_ether_addr((u8 *)priv->reg.bssid))
		priv->need_commit |= SME_MODE_SET;

	netdev_dbg(dev, "bssid = %pM\n", priv->reg.bssid);

	/* Write it to the card */
	अगर (priv->need_commit) अणु
		priv->need_commit |= SME_MODE_SET;
		वापस -EINPROGRESS;	/* Call commit handler */
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_get_wap(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *awrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	अगर (is_connect_status(priv->connect_status))
		ether_addr_copy(awrq->ap_addr.sa_data, priv->current_ap.bssid);
	अन्यथा
		eth_zero_addr(awrq->ap_addr.sa_data);

	awrq->ap_addr.sa_family = ARPHRD_ETHER;

	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_nick(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *dwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	/* Check the size of the string */
	अगर (dwrq->data.length > 16 + 1)
		वापस -E2BIG;

	स_रखो(priv->nick, 0, माप(priv->nick));
	स_नकल(priv->nick, extra, dwrq->data.length);

	वापस -EINPROGRESS;	/* Call commit handler */
पूर्ण

अटल पूर्णांक ks_wlan_get_nick(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *dwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	म_नकलन(extra, priv->nick, 16);
	extra[16] = '\0';
	dwrq->data.length = म_माप(extra) + 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_rate(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *vwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);
	पूर्णांक i = 0;

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	अगर (priv->reg.phy_type == D_11B_ONLY_MODE) अणु
		अगर (vwrq->bitrate.fixed == 1) अणु
			चयन (vwrq->bitrate.value) अणु
			हाल 11000000:
			हाल 5500000:
				priv->reg.rate_set.body[0] =
				    (u8)(vwrq->bitrate.value / 500000);
				अवरोध;
			हाल 2000000:
			हाल 1000000:
				priv->reg.rate_set.body[0] =
				    ((u8)(vwrq->bitrate.value / 500000)) |
				    BASIC_RATE;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
			priv->reg.tx_rate = TX_RATE_FIXED;
			priv->reg.rate_set.size = 1;
		पूर्ण अन्यथा अणु	/* vwrq->fixed == 0 */
			अगर (vwrq->bitrate.value > 0) अणु
				चयन (vwrq->bitrate.value) अणु
				हाल 11000000:
					priv->reg.rate_set.body[3] =
					    TX_RATE_11M;
					i++;
					fallthrough;
				हाल 5500000:
					priv->reg.rate_set.body[2] = TX_RATE_5M;
					i++;
					fallthrough;
				हाल 2000000:
					priv->reg.rate_set.body[1] =
					    TX_RATE_2M | BASIC_RATE;
					i++;
					fallthrough;
				हाल 1000000:
					priv->reg.rate_set.body[0] =
					    TX_RATE_1M | BASIC_RATE;
					i++;
					अवरोध;
				शेष:
					वापस -EINVAL;
				पूर्ण
				priv->reg.tx_rate = TX_RATE_MANUAL_AUTO;
				priv->reg.rate_set.size = i;
			पूर्ण अन्यथा अणु
				priv->reg.rate_set.body[3] = TX_RATE_11M;
				priv->reg.rate_set.body[2] = TX_RATE_5M;
				priv->reg.rate_set.body[1] =
				    TX_RATE_2M | BASIC_RATE;
				priv->reg.rate_set.body[0] =
				    TX_RATE_1M | BASIC_RATE;
				priv->reg.tx_rate = TX_RATE_FULL_AUTO;
				priv->reg.rate_set.size = 4;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु	/* D_11B_ONLY_MODE or  D_11BG_COMPATIBLE_MODE */
		अगर (vwrq->bitrate.fixed == 1) अणु
			चयन (vwrq->bitrate.value) अणु
			हाल 54000000:
			हाल 48000000:
			हाल 36000000:
			हाल 18000000:
			हाल 9000000:
				priv->reg.rate_set.body[0] =
				    (u8)(vwrq->bitrate.value / 500000);
				अवरोध;
			हाल 24000000:
			हाल 12000000:
			हाल 11000000:
			हाल 6000000:
			हाल 5500000:
			हाल 2000000:
			हाल 1000000:
				priv->reg.rate_set.body[0] =
				    ((u8)(vwrq->bitrate.value / 500000)) |
				    BASIC_RATE;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
			priv->reg.tx_rate = TX_RATE_FIXED;
			priv->reg.rate_set.size = 1;
		पूर्ण अन्यथा अणु	/* vwrq->fixed == 0 */
			अगर (vwrq->bitrate.value > 0) अणु
				चयन (vwrq->bitrate.value) अणु
				हाल 54000000:
					priv->reg.rate_set.body[11] =
					    TX_RATE_54M;
					i++;
					fallthrough;
				हाल 48000000:
					priv->reg.rate_set.body[10] =
					    TX_RATE_48M;
					i++;
					fallthrough;
				हाल 36000000:
					priv->reg.rate_set.body[9] =
					    TX_RATE_36M;
					i++;
					fallthrough;
				हाल 24000000:
				हाल 18000000:
				हाल 12000000:
				हाल 11000000:
				हाल 9000000:
				हाल 6000000:
					अगर (vwrq->bitrate.value == 24000000) अणु
						priv->reg.rate_set.body[8] =
						    TX_RATE_18M;
						i++;
						priv->reg.rate_set.body[7] =
						    TX_RATE_9M;
						i++;
						priv->reg.rate_set.body[6] =
						    TX_RATE_24M | BASIC_RATE;
						i++;
						priv->reg.rate_set.body[5] =
						    TX_RATE_12M | BASIC_RATE;
						i++;
						priv->reg.rate_set.body[4] =
						    TX_RATE_6M | BASIC_RATE;
						i++;
						priv->reg.rate_set.body[3] =
						    TX_RATE_11M | BASIC_RATE;
						i++;
					पूर्ण अन्यथा अगर (vwrq->bitrate.value == 18000000) अणु
						priv->reg.rate_set.body[7] =
						    TX_RATE_18M;
						i++;
						priv->reg.rate_set.body[6] =
						    TX_RATE_9M;
						i++;
						priv->reg.rate_set.body[5] =
						    TX_RATE_12M | BASIC_RATE;
						i++;
						priv->reg.rate_set.body[4] =
						    TX_RATE_6M | BASIC_RATE;
						i++;
						priv->reg.rate_set.body[3] =
						    TX_RATE_11M | BASIC_RATE;
						i++;
					पूर्ण अन्यथा अगर (vwrq->bitrate.value == 12000000) अणु
						priv->reg.rate_set.body[6] =
						    TX_RATE_9M;
						i++;
						priv->reg.rate_set.body[5] =
						    TX_RATE_12M | BASIC_RATE;
						i++;
						priv->reg.rate_set.body[4] =
						    TX_RATE_6M | BASIC_RATE;
						i++;
						priv->reg.rate_set.body[3] =
						    TX_RATE_11M | BASIC_RATE;
						i++;
					पूर्ण अन्यथा अगर (vwrq->bitrate.value == 11000000) अणु
						priv->reg.rate_set.body[5] =
						    TX_RATE_9M;
						i++;
						priv->reg.rate_set.body[4] =
						    TX_RATE_6M | BASIC_RATE;
						i++;
						priv->reg.rate_set.body[3] =
						    TX_RATE_11M | BASIC_RATE;
						i++;
					पूर्ण अन्यथा अगर (vwrq->bitrate.value == 9000000) अणु
						priv->reg.rate_set.body[4] =
						    TX_RATE_9M;
						i++;
						priv->reg.rate_set.body[3] =
						    TX_RATE_6M | BASIC_RATE;
						i++;
					पूर्ण अन्यथा अणु	/* vwrq->value == 6000000 */
						priv->reg.rate_set.body[3] =
						    TX_RATE_6M | BASIC_RATE;
						i++;
					पूर्ण
					fallthrough;
				हाल 5500000:
					priv->reg.rate_set.body[2] =
					    TX_RATE_5M | BASIC_RATE;
					i++;
					fallthrough;
				हाल 2000000:
					priv->reg.rate_set.body[1] =
					    TX_RATE_2M | BASIC_RATE;
					i++;
					fallthrough;
				हाल 1000000:
					priv->reg.rate_set.body[0] =
					    TX_RATE_1M | BASIC_RATE;
					i++;
					अवरोध;
				शेष:
					वापस -EINVAL;
				पूर्ण
				priv->reg.tx_rate = TX_RATE_MANUAL_AUTO;
				priv->reg.rate_set.size = i;
			पूर्ण अन्यथा अणु
				priv->reg.rate_set.body[11] = TX_RATE_54M;
				priv->reg.rate_set.body[10] = TX_RATE_48M;
				priv->reg.rate_set.body[9] = TX_RATE_36M;
				priv->reg.rate_set.body[8] = TX_RATE_18M;
				priv->reg.rate_set.body[7] = TX_RATE_9M;
				priv->reg.rate_set.body[6] =
				    TX_RATE_24M | BASIC_RATE;
				priv->reg.rate_set.body[5] =
				    TX_RATE_12M | BASIC_RATE;
				priv->reg.rate_set.body[4] =
				    TX_RATE_6M | BASIC_RATE;
				priv->reg.rate_set.body[3] =
				    TX_RATE_11M | BASIC_RATE;
				priv->reg.rate_set.body[2] =
				    TX_RATE_5M | BASIC_RATE;
				priv->reg.rate_set.body[1] =
				    TX_RATE_2M | BASIC_RATE;
				priv->reg.rate_set.body[0] =
				    TX_RATE_1M | BASIC_RATE;
				priv->reg.tx_rate = TX_RATE_FULL_AUTO;
				priv->reg.rate_set.size = 12;
			पूर्ण
		पूर्ण
	पूर्ण

	priv->need_commit |= SME_MODE_SET;

	वापस -EINPROGRESS;	/* Call commit handler */
पूर्ण

अटल पूर्णांक ks_wlan_get_rate(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *vwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	netdev_dbg(dev, "in_interrupt = %ld update_phyinfo = %d\n",
		   in_पूर्णांकerrupt(), atomic_पढ़ो(&update_phyinfo));

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	अगर (!atomic_पढ़ो(&update_phyinfo))
		ks_wlan_update_phy_inक्रमmation(priv);

	vwrq->bitrate.value = ((priv->current_rate) & RATE_MASK) * 500000;
	vwrq->bitrate.fixed = (priv->reg.tx_rate == TX_RATE_FIXED) ? 1 : 0;

	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_rts(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *vwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);
	पूर्णांक rthr = vwrq->rts.value;

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	अगर (vwrq->rts.disabled)
		rthr = 2347;
	अगर ((rthr < 0) || (rthr > 2347))
		वापस -EINVAL;

	priv->reg.rts = rthr;
	priv->need_commit |= SME_RTS;

	वापस -EINPROGRESS;	/* Call commit handler */
पूर्ण

अटल पूर्णांक ks_wlan_get_rts(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *vwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	vwrq->rts.value = priv->reg.rts;
	vwrq->rts.disabled = (vwrq->rts.value >= 2347);
	vwrq->rts.fixed = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_frag(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *vwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);
	पूर्णांक fthr = vwrq->frag.value;

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	अगर (vwrq->frag.disabled)
		fthr = 2346;
	अगर ((fthr < 256) || (fthr > 2346))
		वापस -EINVAL;

	fthr &= ~0x1;	/* Get an even value - is it really needed ??? */
	priv->reg.fragment = fthr;
	priv->need_commit |= SME_FRAG;

	वापस -EINPROGRESS;	/* Call commit handler */
पूर्ण

अटल पूर्णांक ks_wlan_get_frag(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *vwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	vwrq->frag.value = priv->reg.fragment;
	vwrq->frag.disabled = (vwrq->frag.value >= 2346);
	vwrq->frag.fixed = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_mode(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *uwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	अगर (uwrq->mode != IW_MODE_ADHOC &&
	    uwrq->mode != IW_MODE_INFRA)
		वापस -EINVAL;

	priv->reg.operation_mode = (uwrq->mode == IW_MODE_ADHOC) ?
				    MODE_ADHOC : MODE_INFRASTRUCTURE;
	priv->need_commit |= SME_MODE_SET;

	वापस -EINPROGRESS;	/* Call commit handler */
पूर्ण

अटल पूर्णांक ks_wlan_get_mode(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *uwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* If not managed, assume it's ad-hoc */
	uwrq->mode = (priv->reg.operation_mode == MODE_INFRASTRUCTURE) ?
		      IW_MODE_INFRA : IW_MODE_ADHOC;

	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_encode(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *dwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);
	काष्ठा iw_poपूर्णांक *enc = &dwrq->encoding;
	काष्ठा wep_key key;
	पूर्णांक index = (enc->flags & IW_ENCODE_INDEX);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	अगर (enc->length > MAX_KEY_SIZE)
		वापस -EINVAL;

	/* क्रम SLEEP MODE */
	अगर ((index < 0) || (index > 4))
		वापस -EINVAL;

	index = (index == 0) ? priv->reg.wep_index : (index - 1);

	/* Is WEP supported ? */
	/* Basic checking: करो we have a key to set ? */
	अगर (enc->length > 0) अणु
		key.len = (enc->length > MIN_KEY_SIZE) ?
			   MAX_KEY_SIZE : MIN_KEY_SIZE;
		priv->reg.privacy_invoked = 0x01;
		priv->need_commit |= SME_WEP_FLAG;
		wep_on_off = (enc->length > MIN_KEY_SIZE) ?
			      WEP_ON_128BIT : WEP_ON_64BIT;
		/* Check अगर the key is not marked as invalid */
		अगर (enc->flags & IW_ENCODE_NOKEY)
			वापस 0;

		/* Cleanup */
		स_रखो(key.key, 0, MAX_KEY_SIZE);
		/* Copy the key in the driver */
		अगर (copy_from_user(key.key, enc->poपूर्णांकer, enc->length)) अणु
			key.len = 0;
			वापस -EFAULT;
		पूर्ण
		/* Send the key to the card */
		priv->reg.wep_key[index].size = key.len;
		स_नकल(&priv->reg.wep_key[index].val[0], &key.key[0],
		       priv->reg.wep_key[index].size);
		priv->need_commit |= (SME_WEP_VAL1 << index);
		priv->reg.wep_index = index;
		priv->need_commit |= SME_WEP_INDEX;
	पूर्ण अन्यथा अणु
		अगर (enc->flags & IW_ENCODE_DISABLED) अणु
			priv->reg.wep_key[0].size = 0;
			priv->reg.wep_key[1].size = 0;
			priv->reg.wep_key[2].size = 0;
			priv->reg.wep_key[3].size = 0;
			priv->reg.privacy_invoked = 0x00;
			अगर (priv->reg.authenticate_type == AUTH_TYPE_SHARED_KEY)
				priv->need_commit |= SME_MODE_SET;

			priv->reg.authenticate_type = AUTH_TYPE_OPEN_SYSTEM;
			wep_on_off = WEP_OFF;
			priv->need_commit |= SME_WEP_FLAG;
		पूर्ण अन्यथा अणु
			/* set_wep_key(priv, index, 0, 0, 1);   xxx */
			अगर (priv->reg.wep_key[index].size == 0)
				वापस -EINVAL;
			priv->reg.wep_index = index;
			priv->need_commit |= SME_WEP_INDEX;
		पूर्ण
	पूर्ण

	/* Commit the changes अगर needed */
	अगर (enc->flags & IW_ENCODE_MODE)
		priv->need_commit |= SME_WEP_FLAG;

	अगर (enc->flags & IW_ENCODE_OPEN) अणु
		अगर (priv->reg.authenticate_type == AUTH_TYPE_SHARED_KEY)
			priv->need_commit |= SME_MODE_SET;

		priv->reg.authenticate_type = AUTH_TYPE_OPEN_SYSTEM;
	पूर्ण अन्यथा अगर (enc->flags & IW_ENCODE_RESTRICTED) अणु
		अगर (priv->reg.authenticate_type == AUTH_TYPE_OPEN_SYSTEM)
			priv->need_commit |= SME_MODE_SET;

		priv->reg.authenticate_type = AUTH_TYPE_SHARED_KEY;
	पूर्ण
	अगर (priv->need_commit) अणु
		ks_wlan_setup_parameter(priv, priv->need_commit);
		priv->need_commit = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_get_encode(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *dwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);
	काष्ठा iw_poपूर्णांक *enc = &dwrq->encoding;
	पूर्णांक index = (enc->flags & IW_ENCODE_INDEX) - 1;

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	enc->flags = IW_ENCODE_DISABLED;

	/* Check encryption mode */
	चयन (priv->reg.authenticate_type) अणु
	हाल AUTH_TYPE_OPEN_SYSTEM:
		enc->flags = IW_ENCODE_OPEN;
		अवरोध;
	हाल AUTH_TYPE_SHARED_KEY:
		enc->flags = IW_ENCODE_RESTRICTED;
		अवरोध;
	पूर्ण

	/* Which key करो we want ? -1 -> tx index */
	अगर ((index < 0) || (index >= 4))
		index = priv->reg.wep_index;
	अगर (priv->reg.privacy_invoked) अणु
		enc->flags &= ~IW_ENCODE_DISABLED;
		/* dwrq->flags |= IW_ENCODE_NOKEY; */
	पूर्ण
	enc->flags |= index + 1;
	/* Copy the key to the user buffer */
	अगर (index >= 0 && index < 4) अणु
		enc->length = (priv->reg.wep_key[index].size <= 16) ?
				priv->reg.wep_key[index].size : 0;
		स_नकल(extra, priv->reg.wep_key[index].val, enc->length);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_get_range(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *dwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);
	काष्ठा iw_range *range = (काष्ठा iw_range *)extra;
	पूर्णांक i, k;

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	dwrq->data.length = माप(काष्ठा iw_range);
	स_रखो(range, 0, माप(*range));
	range->min_nwid = 0x0000;
	range->max_nwid = 0x0000;
	range->num_channels = 14;
	/* Should be based on cap_rid.country to give only
	 * what the current card support
	 */
	k = 0;
	क्रम (i = 0; i < 13; i++) अणु	/* channel 1 -- 13 */
		range->freq[k].i = i + 1;	/* List index */
		range->freq[k].m = frequency_list[i] * 100000;
		range->freq[k++].e = 1;	/* Values in table in MHz -> * 10^5 * 10 */
	पूर्ण
	range->num_frequency = k;
	अगर (priv->reg.phy_type == D_11B_ONLY_MODE ||
	    priv->reg.phy_type == D_11BG_COMPATIBLE_MODE) अणु	/* channel 14 */
		range->freq[13].i = 14;	/* List index */
		range->freq[13].m = frequency_list[13] * 100000;
		range->freq[13].e = 1;	/* Values in table in MHz -> * 10^5 * 10 */
		range->num_frequency = 14;
	पूर्ण

	/* Hum... Should put the right values there */
	range->max_qual.qual = 100;
	range->max_qual.level = 256 - 128;	/* 0 dBm? */
	range->max_qual.noise = 256 - 128;
	range->sensitivity = 1;

	अगर (priv->reg.phy_type == D_11B_ONLY_MODE) अणु
		range->bitrate[0] = 1e6;
		range->bitrate[1] = 2e6;
		range->bitrate[2] = 5.5e6;
		range->bitrate[3] = 11e6;
		range->num_bitrates = 4;
	पूर्ण अन्यथा अणु	/* D_11G_ONLY_MODE or D_11BG_COMPATIBLE_MODE */
		range->bitrate[0] = 1e6;
		range->bitrate[1] = 2e6;
		range->bitrate[2] = 5.5e6;
		range->bitrate[3] = 11e6;

		range->bitrate[4] = 6e6;
		range->bitrate[5] = 9e6;
		range->bitrate[6] = 12e6;
		अगर (IW_MAX_BITRATES < 9) अणु
			range->bitrate[7] = 54e6;
			range->num_bitrates = 8;
		पूर्ण अन्यथा अणु
			range->bitrate[7] = 18e6;
			range->bitrate[8] = 24e6;
			range->bitrate[9] = 36e6;
			range->bitrate[10] = 48e6;
			range->bitrate[11] = 54e6;

			range->num_bitrates = 12;
		पूर्ण
	पूर्ण

	/* Set an indication of the max TCP throughput
	 * in bit/s that we can expect using this पूर्णांकerface.
	 * May be use क्रम QoS stuff... Jean II
	 */
	अगर (i > 2)
		range->throughput = 5000 * 1000;
	अन्यथा
		range->throughput = 1500 * 1000;

	range->min_rts = 0;
	range->max_rts = 2347;
	range->min_frag = 256;
	range->max_frag = 2346;

	range->encoding_size[0] = 5;	/* WEP: RC4 40 bits */
	range->encoding_size[1] = 13;	/* WEP: RC4 ~128 bits */
	range->num_encoding_sizes = 2;
	range->max_encoding_tokens = 4;

	/* घातer management not support */
	range->pmp_flags = IW_POWER_ON;
	range->pmt_flags = IW_POWER_ON;
	range->pm_capa = 0;

	/* Transmit Power - values are in dBm( or mW) */
	range->txघातer[0] = -256;
	range->num_txघातer = 1;
	range->txघातer_capa = IW_TXPOW_DBM;
	/* range->txघातer_capa = IW_TXPOW_MWATT; */

	range->we_version_source = 21;
	range->we_version_compiled = WIRELESS_EXT;

	range->retry_capa = IW_RETRY_ON;
	range->retry_flags = IW_RETRY_ON;
	range->r_समय_flags = IW_RETRY_ON;

	/* Experimental measurements - boundary 11/5.5 Mb/s
	 *
	 * Note : with or without the (local->rssi), results
	 * are somewhat dअगरferent. - Jean II
	 */
	range->avg_qual.qual = 50;
	range->avg_qual.level = 186;	/* -70 dBm */
	range->avg_qual.noise = 0;

	/* Event capability (kernel + driver) */
	range->event_capa[0] = (IW_EVENT_CAPA_K_0 |
				IW_EVENT_CAPA_MASK(SIOCGIWAP) |
				IW_EVENT_CAPA_MASK(SIOCGIWSCAN));
	range->event_capa[1] = IW_EVENT_CAPA_K_1;
	range->event_capa[4] = (IW_EVENT_CAPA_MASK(IWEVCUSTOM) |
				IW_EVENT_CAPA_MASK(IWEVMICHAELMICFAILURE));

	/* encode extension (WPA) capability */
	range->enc_capa = (IW_ENC_CAPA_WPA |
			   IW_ENC_CAPA_WPA2 |
			   IW_ENC_CAPA_CIPHER_TKIP | IW_ENC_CAPA_CIPHER_CCMP);
	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_घातer(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *vwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	अगर (vwrq->घातer.disabled) अणु
		priv->reg.घातer_mgmt = POWER_MGMT_ACTIVE;
	पूर्ण अन्यथा अणु
		अगर (priv->reg.operation_mode != MODE_INFRASTRUCTURE)
			वापस -EINVAL;
		priv->reg.घातer_mgmt = POWER_MGMT_SAVE1;
	पूर्ण

	hostअगर_sme_enqueue(priv, SME_POW_MNGMT_REQUEST);

	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_get_घातer(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *vwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;
	/* क्रम SLEEP MODE */
	vwrq->घातer.disabled = (priv->reg.घातer_mgmt <= 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_get_iwstats(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *vwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;
	/* क्रम SLEEP MODE */
	vwrq->qual.qual = 0;	/* not supported */
	vwrq->qual.level = priv->wstats.qual.level;
	vwrq->qual.noise = 0;	/* not supported */
	vwrq->qual.updated = 0;

	वापस 0;
पूर्ण

/* Note : this is deprecated in favor of IWSCAN */
अटल पूर्णांक ks_wlan_get_aplist(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *dwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);
	काष्ठा sockaddr *address = (काष्ठा sockaddr *)extra;
	काष्ठा iw_quality qual[LOCAL_APLIST_MAX];
	पूर्णांक i;

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;
	/* क्रम SLEEP MODE */
	क्रम (i = 0; i < priv->aplist.size; i++) अणु
		ether_addr_copy(address[i].sa_data, priv->aplist.ap[i].bssid);
		address[i].sa_family = ARPHRD_ETHER;
		qual[i].level = 256 - priv->aplist.ap[i].rssi;
		qual[i].qual = priv->aplist.ap[i].sq;
		qual[i].noise = 0;	/* invalid noise value */
		qual[i].updated = 7;
	पूर्ण
	अगर (i) अणु
		dwrq->data.flags = 1;	/* Should be define'd */
		स_नकल(extra + माप(काष्ठा sockaddr) * i,
		       &qual, माप(काष्ठा iw_quality) * i);
	पूर्ण
	dwrq->data.length = i;

	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_scan(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);
	काष्ठा iw_scan_req *req = शून्य;
	पूर्णांक len;

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	/* specअगरied SSID SCAN */
	अगर (wrqu->data.length == माप(काष्ठा iw_scan_req) &&
	    wrqu->data.flags & IW_SCAN_THIS_ESSID) अणु
		req = (काष्ठा iw_scan_req *)extra;
		len = min_t(पूर्णांक, req->essid_len, IW_ESSID_MAX_SIZE);
		priv->scan_ssid_len = len;
		स_नकल(priv->scan_ssid, req->essid, len);
	पूर्ण अन्यथा अणु
		priv->scan_ssid_len = 0;
	पूर्ण

	priv->sme_i.sme_flag |= SME_AP_SCAN;
	hostअगर_sme_enqueue(priv, SME_BSS_SCAN_REQUEST);

	/* At this poपूर्णांक, just वापस to the user. */

	वापस 0;
पूर्ण

अटल अक्षर *ks_wlan_add_leader_event(स्थिर अक्षर *rsn_leader, अक्षर *end_buf,
				      अक्षर *current_ev, काष्ठा rsn_ie *rsn,
				      काष्ठा iw_event *iwe,
				      काष्ठा iw_request_info *info)
अणु
	अक्षर buffer[RSN_IE_BODY_MAX * 2 + 30];
	अक्षर *pbuf;
	पूर्णांक i;

	pbuf = &buffer[0];
	स_रखो(iwe, 0, माप(*iwe));
	iwe->cmd = IWEVCUSTOM;
	स_नकल(buffer, rsn_leader, माप(rsn_leader) - 1);
	iwe->u.data.length += माप(rsn_leader) - 1;
	pbuf += माप(rsn_leader) - 1;
	pbuf += प्र_लिखो(pbuf, "%02x", rsn->id);
	pbuf += प्र_लिखो(pbuf, "%02x", rsn->size);
	iwe->u.data.length += 4;

	क्रम (i = 0; i < rsn->size; i++)
		pbuf += प्र_लिखो(pbuf, "%02x", rsn->body[i]);

	iwe->u.data.length += rsn->size * 2;

	वापस iwe_stream_add_poपूर्णांक(info, current_ev, end_buf, iwe, &buffer[0]);
पूर्ण

/*
 * Translate scan data वापसed from the card to a card independent
 * क्रमmat that the Wireless Tools will understand - Jean II
 */
अटल अंतरभूत अक्षर *ks_wlan_translate_scan(काष्ठा net_device *dev,
					   काष्ठा iw_request_info *info,
					   अक्षर *current_ev, अक्षर *end_buf,
					   काष्ठा local_ap *ap)
अणु
	/* काष्ठा ks_wlan_निजी *priv = (काष्ठा ks_wlan_निजी *)dev->priv; */
	अटल स्थिर अक्षर rsn_leader[] = "rsn_ie=";
	अटल स्थिर अक्षर wpa_leader[] = "wpa_ie=";
	काष्ठा iw_event iwe;	/* Temporary buffer */
	u16 capabilities;
	अक्षर *current_val;	/* For rates */
	पूर्णांक i;

	/* First entry *MUST* be the AP MAC address */
	iwe.cmd = SIOCGIWAP;
	iwe.u.ap_addr.sa_family = ARPHRD_ETHER;
	ether_addr_copy(iwe.u.ap_addr.sa_data, ap->bssid);
	current_ev = iwe_stream_add_event(info, current_ev,
					  end_buf, &iwe, IW_EV_ADDR_LEN);

	/* Other entries will be displayed in the order we give them */

	/* Add the ESSID */
	iwe.u.data.length = ap->ssid.size;
	अगर (iwe.u.data.length > 32)
		iwe.u.data.length = 32;
	iwe.cmd = SIOCGIWESSID;
	iwe.u.data.flags = 1;
	current_ev = iwe_stream_add_poपूर्णांक(info, current_ev,
					  end_buf, &iwe, ap->ssid.body);

	/* Add mode */
	iwe.cmd = SIOCGIWMODE;
	capabilities = ap->capability;
	अगर (capabilities & (WLAN_CAPABILITY_ESS | WLAN_CAPABILITY_IBSS)) अणु
		iwe.u.mode = (capabilities & WLAN_CAPABILITY_ESS) ?
			      IW_MODE_INFRA : IW_MODE_ADHOC;
		current_ev = iwe_stream_add_event(info, current_ev,
						  end_buf, &iwe, IW_EV_UINT_LEN);
	पूर्ण

	/* Add frequency */
	iwe.cmd = SIOCGIWFREQ;
	iwe.u.freq.m = ap->channel;
	iwe.u.freq.m = frequency_list[iwe.u.freq.m - 1] * 100000;
	iwe.u.freq.e = 1;
	current_ev = iwe_stream_add_event(info, current_ev,
					  end_buf, &iwe, IW_EV_FREQ_LEN);

	/* Add quality statistics */
	iwe.cmd = IWEVQUAL;
	iwe.u.qual.level = 256 - ap->rssi;
	iwe.u.qual.qual = ap->sq;
	iwe.u.qual.noise = 0;	/* invalid noise value */
	current_ev = iwe_stream_add_event(info, current_ev, end_buf,
					  &iwe, IW_EV_QUAL_LEN);

	/* Add encryption capability */
	iwe.cmd = SIOCGIWENCODE;
	iwe.u.data.flags = (capabilities & WLAN_CAPABILITY_PRIVACY) ?
			    (IW_ENCODE_ENABLED | IW_ENCODE_NOKEY) :
			     IW_ENCODE_DISABLED;
	iwe.u.data.length = 0;
	current_ev = iwe_stream_add_poपूर्णांक(info, current_ev, end_buf,
					  &iwe, ap->ssid.body);

	/*
	 * Rate : stuffing multiple values in a single event
	 * require a bit more of magic - Jean II
	 */
	current_val = current_ev + IW_EV_LCP_LEN;

	iwe.cmd = SIOCGIWRATE;

	/* These two flags are ignored... */
	iwe.u.bitrate.fixed = 0;
	iwe.u.bitrate.disabled = 0;

	/* Max 16 values */
	क्रम (i = 0; i < 16; i++) अणु
		/* शून्य terminated */
		अगर (i >= ap->rate_set.size)
			अवरोध;
		/* Bit rate given in 500 kb/s units (+ 0x80) */
		iwe.u.bitrate.value = ((ap->rate_set.body[i] & 0x7f) * 500000);
		/* Add new value to event */
		current_val = iwe_stream_add_value(info, current_ev,
						   current_val, end_buf, &iwe,
						   IW_EV_PARAM_LEN);
	पूर्ण
	/* Check अगर we added any event */
	अगर ((current_val - current_ev) > IW_EV_LCP_LEN)
		current_ev = current_val;

	अगर (ap->rsn_ie.id == RSN_INFO_ELEM_ID && ap->rsn_ie.size != 0)
		current_ev = ks_wlan_add_leader_event(rsn_leader, end_buf,
						      current_ev, &ap->rsn_ie,
						      &iwe, info);

	अगर (ap->wpa_ie.id == WPA_INFO_ELEM_ID && ap->wpa_ie.size != 0)
		current_ev = ks_wlan_add_leader_event(wpa_leader, end_buf,
						      current_ev, &ap->wpa_ie,
						      &iwe, info);

	/*
	 * The other data in the scan result are not really
	 * पूर्णांकeresting, so क्रम now drop it - Jean II
	 */
	वापस current_ev;
पूर्ण

अटल पूर्णांक ks_wlan_get_scan(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *dwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);
	पूर्णांक i;
	अक्षर *current_ev = extra;

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;
	/* क्रम SLEEP MODE */
	अगर (priv->sme_i.sme_flag & SME_AP_SCAN)
		वापस -EAGAIN;

	अगर (priv->aplist.size == 0) अणु
		/* Client error, no scan results...
		 * The caller need to restart the scan.
		 */
		वापस -ENODATA;
	पूर्ण

	/* Read and parse all entries */
	क्रम (i = 0; i < priv->aplist.size; i++) अणु
		अगर ((extra + dwrq->data.length) - current_ev <= IW_EV_ADDR_LEN) अणु
			dwrq->data.length = 0;
			वापस -E2BIG;
		पूर्ण
		/* Translate to WE क्रमmat this entry */
		current_ev = ks_wlan_translate_scan(dev, info, current_ev,
						    extra + dwrq->data.length,
						    &priv->aplist.ap[i]);
	पूर्ण
	/* Length of data */
	dwrq->data.length = (current_ev - extra);
	dwrq->data.flags = 0;

	वापस 0;
पूर्ण

/* called after a bunch of SET operations */
अटल पूर्णांक ks_wlan_config_commit(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 जोड़ iwreq_data *zwrq,
				 अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (!priv->need_commit)
		वापस 0;

	ks_wlan_setup_parameter(priv, priv->need_commit);
	priv->need_commit = 0;
	वापस 0;
पूर्ण

/* set association ie params */
अटल पूर्णांक ks_wlan_set_genie(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *dwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;
	/* क्रम SLEEP MODE */
	वापस 0;
//      वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक ks_wlan_set_auth_mode(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 जोड़ iwreq_data *vwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);
	काष्ठा iw_param *param = &vwrq->param;
	पूर्णांक index = (param->flags & IW_AUTH_INDEX);
	पूर्णांक value = param->value;

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;
	/* क्रम SLEEP MODE */
	चयन (index) अणु
	हाल IW_AUTH_WPA_VERSION:	/* 0 */
		चयन (value) अणु
		हाल IW_AUTH_WPA_VERSION_DISABLED:
			priv->wpa.version = value;
			अगर (priv->wpa.rsn_enabled)
				priv->wpa.rsn_enabled = false;
			priv->need_commit |= SME_RSN;
			अवरोध;
		हाल IW_AUTH_WPA_VERSION_WPA:
		हाल IW_AUTH_WPA_VERSION_WPA2:
			priv->wpa.version = value;
			अगर (!(priv->wpa.rsn_enabled))
				priv->wpa.rsn_enabled = true;
			priv->need_commit |= SME_RSN;
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल IW_AUTH_CIPHER_PAIRWISE:	/* 1 */
		चयन (value) अणु
		हाल IW_AUTH_CIPHER_NONE:
			अगर (priv->reg.privacy_invoked) अणु
				priv->reg.privacy_invoked = 0x00;
				priv->need_commit |= SME_WEP_FLAG;
			पूर्ण
			अवरोध;
		हाल IW_AUTH_CIPHER_WEP40:
		हाल IW_AUTH_CIPHER_TKIP:
		हाल IW_AUTH_CIPHER_CCMP:
		हाल IW_AUTH_CIPHER_WEP104:
			अगर (!priv->reg.privacy_invoked) अणु
				priv->reg.privacy_invoked = 0x01;
				priv->need_commit |= SME_WEP_FLAG;
			पूर्ण
			priv->wpa.pairwise_suite = value;
			priv->need_commit |= SME_RSN_UNICAST;
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल IW_AUTH_CIPHER_GROUP:	/* 2 */
		चयन (value) अणु
		हाल IW_AUTH_CIPHER_NONE:
			अगर (priv->reg.privacy_invoked) अणु
				priv->reg.privacy_invoked = 0x00;
				priv->need_commit |= SME_WEP_FLAG;
			पूर्ण
			अवरोध;
		हाल IW_AUTH_CIPHER_WEP40:
		हाल IW_AUTH_CIPHER_TKIP:
		हाल IW_AUTH_CIPHER_CCMP:
		हाल IW_AUTH_CIPHER_WEP104:
			अगर (!priv->reg.privacy_invoked) अणु
				priv->reg.privacy_invoked = 0x01;
				priv->need_commit |= SME_WEP_FLAG;
			पूर्ण
			priv->wpa.group_suite = value;
			priv->need_commit |= SME_RSN_MULTICAST;
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल IW_AUTH_KEY_MGMT:	/* 3 */
		चयन (value) अणु
		हाल IW_AUTH_KEY_MGMT_802_1X:
		हाल IW_AUTH_KEY_MGMT_PSK:
		हाल 0:	/* NONE or 802_1X_NO_WPA */
		हाल 4:	/* WPA_NONE */
			priv->wpa.key_mgmt_suite = value;
			priv->need_commit |= SME_RSN_AUTH;
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल IW_AUTH_80211_AUTH_ALG:	/* 6 */
		चयन (value) अणु
		हाल IW_AUTH_ALG_OPEN_SYSTEM:
			priv->wpa.auth_alg = value;
			priv->reg.authenticate_type = AUTH_TYPE_OPEN_SYSTEM;
			अवरोध;
		हाल IW_AUTH_ALG_SHARED_KEY:
			priv->wpa.auth_alg = value;
			priv->reg.authenticate_type = AUTH_TYPE_SHARED_KEY;
			अवरोध;
		हाल IW_AUTH_ALG_LEAP:
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		priv->need_commit |= SME_MODE_SET;
		अवरोध;
	हाल IW_AUTH_WPA_ENABLED:	/* 7 */
		priv->wpa.wpa_enabled = value;
		अवरोध;
	हाल IW_AUTH_PRIVACY_INVOKED:	/* 10 */
		अगर ((value && !priv->reg.privacy_invoked) ||
		    (!value && priv->reg.privacy_invoked)) अणु
			priv->reg.privacy_invoked = value ? 0x01 : 0x00;
			priv->need_commit |= SME_WEP_FLAG;
		पूर्ण
		अवरोध;
	हाल IW_AUTH_RX_UNENCRYPTED_EAPOL:	/* 4 */
	हाल IW_AUTH_TKIP_COUNTERMEASURES:	/* 5 */
	हाल IW_AUTH_DROP_UNENCRYPTED:	/* 8 */
	हाल IW_AUTH_ROAMING_CONTROL:	/* 9 */
	शेष:
		अवरोध;
	पूर्ण

	/* वापस -EINPROGRESS; */
	अगर (priv->need_commit) अणु
		ks_wlan_setup_parameter(priv, priv->need_commit);
		priv->need_commit = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_get_auth_mode(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 जोड़ iwreq_data *vwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);
	काष्ठा iw_param *param = &vwrq->param;
	पूर्णांक index = (param->flags & IW_AUTH_INDEX);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	/*  WPA (not used ?? wpa_supplicant) */
	चयन (index) अणु
	हाल IW_AUTH_WPA_VERSION:
		param->value = priv->wpa.version;
		अवरोध;
	हाल IW_AUTH_CIPHER_PAIRWISE:
		param->value = priv->wpa.pairwise_suite;
		अवरोध;
	हाल IW_AUTH_CIPHER_GROUP:
		param->value = priv->wpa.group_suite;
		अवरोध;
	हाल IW_AUTH_KEY_MGMT:
		param->value = priv->wpa.key_mgmt_suite;
		अवरोध;
	हाल IW_AUTH_80211_AUTH_ALG:
		param->value = priv->wpa.auth_alg;
		अवरोध;
	हाल IW_AUTH_WPA_ENABLED:
		param->value = priv->wpa.rsn_enabled;
		अवरोध;
	हाल IW_AUTH_RX_UNENCRYPTED_EAPOL:	/* OK??? */
	हाल IW_AUTH_TKIP_COUNTERMEASURES:
	हाल IW_AUTH_DROP_UNENCRYPTED:
	शेष:
		/* वापस -EOPNOTSUPP; */
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* set encoding token & mode (WPA)*/
अटल पूर्णांक ks_wlan_set_encode_ext(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  जोड़ iwreq_data *dwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);
	काष्ठा iw_encode_ext *enc;
	पूर्णांक index = dwrq->encoding.flags & IW_ENCODE_INDEX;
	अचिन्हित पूर्णांक commit = 0;
	काष्ठा wpa_key *key;

	enc = (काष्ठा iw_encode_ext *)extra;
	अगर (!enc)
		वापस -EINVAL;

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	अगर (index < 1 || index > 4)
		वापस -EINVAL;
	index--;
	key = &priv->wpa.key[index];

	अगर (dwrq->encoding.flags & IW_ENCODE_DISABLED)
		key->key_len = 0;

	key->ext_flags = enc->ext_flags;
	अगर (enc->ext_flags & IW_ENCODE_EXT_SET_TX_KEY) अणु
		priv->wpa.txkey = index;
		commit |= SME_WEP_INDEX;
	पूर्ण अन्यथा अगर (enc->ext_flags & IW_ENCODE_EXT_RX_SEQ_VALID) अणु
		स_नकल(&key->rx_seq[0], &enc->rx_seq[0], IW_ENCODE_SEQ_MAX_SIZE);
	पूर्ण

	ether_addr_copy(&key->addr.sa_data[0], &enc->addr.sa_data[0]);

	चयन (enc->alg) अणु
	हाल IW_ENCODE_ALG_NONE:
		अगर (priv->reg.privacy_invoked) अणु
			priv->reg.privacy_invoked = 0x00;
			commit |= SME_WEP_FLAG;
		पूर्ण
		key->key_len = 0;

		अवरोध;
	हाल IW_ENCODE_ALG_WEP:
	हाल IW_ENCODE_ALG_CCMP:
		अगर (!priv->reg.privacy_invoked) अणु
			priv->reg.privacy_invoked = 0x01;
			commit |= SME_WEP_FLAG;
		पूर्ण
		अगर (enc->key_len) अणु
			स_नकल(&key->key_val[0], &enc->key[0], enc->key_len);
			key->key_len = enc->key_len;
			commit |= (SME_WEP_VAL1 << index);
		पूर्ण
		अवरोध;
	हाल IW_ENCODE_ALG_TKIP:
		अगर (!priv->reg.privacy_invoked) अणु
			priv->reg.privacy_invoked = 0x01;
			commit |= SME_WEP_FLAG;
		पूर्ण
		अगर (enc->key_len == 32) अणु
			स_नकल(&key->key_val[0], &enc->key[0], enc->key_len - 16);
			key->key_len = enc->key_len - 16;
			अगर (priv->wpa.key_mgmt_suite == 4) अणु	/* WPA_NONE */
				स_नकल(&key->tx_mic_key[0], &enc->key[16], 8);
				स_नकल(&key->rx_mic_key[0], &enc->key[16], 8);
			पूर्ण अन्यथा अणु
				स_नकल(&key->tx_mic_key[0], &enc->key[16], 8);
				स_नकल(&key->rx_mic_key[0], &enc->key[24], 8);
			पूर्ण
			commit |= (SME_WEP_VAL1 << index);
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	key->alg = enc->alg;

	अगर (commit) अणु
		अगर (commit & SME_WEP_INDEX)
			hostअगर_sme_enqueue(priv, SME_SET_TXKEY);
		अगर (commit & SME_WEP_VAL_MASK)
			hostअगर_sme_enqueue(priv, SME_SET_KEY1 + index);
		अगर (commit & SME_WEP_FLAG)
			hostअगर_sme_enqueue(priv, SME_WEP_FLAG_REQUEST);
	पूर्ण

	वापस 0;
पूर्ण

/* get encoding token & mode (WPA)*/
अटल पूर्णांक ks_wlan_get_encode_ext(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  जोड़ iwreq_data *dwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	/* WPA (not used ?? wpa_supplicant)
	 * काष्ठा ks_wlan_निजी *priv = (काष्ठा ks_wlan_निजी *)dev->priv;
	 * काष्ठा iw_encode_ext *enc;
	 * enc = (काष्ठा iw_encode_ext *)extra;
	 * पूर्णांक index = dwrq->flags & IW_ENCODE_INDEX;
	 * WPA (not used ?? wpa_supplicant)
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_pmksa(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *dwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);
	काष्ठा iw_pmksa *pmksa;
	पूर्णांक i;
	काष्ठा pmk *pmk;
	काष्ठा list_head *ptr;

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	अगर (!extra)
		वापस -EINVAL;

	pmksa = (काष्ठा iw_pmksa *)extra;

	चयन (pmksa->cmd) अणु
	हाल IW_PMKSA_ADD:
		अगर (list_empty(&priv->pmklist.head)) अणु
			क्रम (i = 0; i < PMK_LIST_MAX; i++) अणु
				pmk = &priv->pmklist.pmk[i];
				अगर (is_zero_ether_addr(pmk->bssid))
					अवरोध;
			पूर्ण
			ether_addr_copy(pmk->bssid, pmksa->bssid.sa_data);
			स_नकल(pmk->pmkid, pmksa->pmkid, IW_PMKID_LEN);
			list_add(&pmk->list, &priv->pmklist.head);
			priv->pmklist.size++;
			अवरोध;
		पूर्ण
		/* search cache data */
		list_क्रम_each(ptr, &priv->pmklist.head) अणु
			pmk = list_entry(ptr, काष्ठा pmk, list);
			अगर (ether_addr_equal(pmksa->bssid.sa_data, pmk->bssid)) अणु
				स_नकल(pmk->pmkid, pmksa->pmkid, IW_PMKID_LEN);
				list_move(&pmk->list, &priv->pmklist.head);
				अवरोध;
			पूर्ण
		पूर्ण
		/* not find address. */
		अगर (ptr != &priv->pmklist.head)
			अवरोध;
		/* new cache data */
		अगर (priv->pmklist.size < PMK_LIST_MAX) अणु
			क्रम (i = 0; i < PMK_LIST_MAX; i++) अणु
				pmk = &priv->pmklist.pmk[i];
				अगर (is_zero_ether_addr(pmk->bssid))
					अवरोध;
			पूर्ण
			ether_addr_copy(pmk->bssid, pmksa->bssid.sa_data);
			स_नकल(pmk->pmkid, pmksa->pmkid, IW_PMKID_LEN);
			list_add(&pmk->list, &priv->pmklist.head);
			priv->pmklist.size++;
		पूर्ण अन्यथा अणु /* overग_लिखो old cache data */
			pmk = list_entry(priv->pmklist.head.prev, काष्ठा pmk,
					 list);
			ether_addr_copy(pmk->bssid, pmksa->bssid.sa_data);
			स_नकल(pmk->pmkid, pmksa->pmkid, IW_PMKID_LEN);
			list_move(&pmk->list, &priv->pmklist.head);
		पूर्ण
		अवरोध;
	हाल IW_PMKSA_REMOVE:
		अगर (list_empty(&priv->pmklist.head))
			वापस -EINVAL;
		/* search cache data */
		list_क्रम_each(ptr, &priv->pmklist.head) अणु
			pmk = list_entry(ptr, काष्ठा pmk, list);
			अगर (ether_addr_equal(pmksa->bssid.sa_data, pmk->bssid)) अणु
				eth_zero_addr(pmk->bssid);
				स_रखो(pmk->pmkid, 0, IW_PMKID_LEN);
				list_del_init(&pmk->list);
				अवरोध;
			पूर्ण
		पूर्ण
		/* not find address. */
		अगर (ptr == &priv->pmklist.head)
			वापस 0;
		अवरोध;
	हाल IW_PMKSA_FLUSH:
		स_रखो(&priv->pmklist, 0, माप(priv->pmklist));
		INIT_LIST_HEAD(&priv->pmklist.head);
		क्रम (i = 0; i < PMK_LIST_MAX; i++)
			INIT_LIST_HEAD(&priv->pmklist.pmk[i].list);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	hostअगर_sme_enqueue(priv, SME_SET_PMKSA);
	वापस 0;
पूर्ण

अटल काष्ठा iw_statistics *ks_get_wireless_stats(काष्ठा net_device *dev)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);
	काष्ठा iw_statistics *wstats = &priv->wstats;

	अगर (!atomic_पढ़ो(&update_phyinfo))
		वापस (priv->dev_state < DEVICE_STATE_READY) ? शून्य : wstats;

	/*
	 * Packets discarded in the wireless adapter due to wireless
	 * specअगरic problems
	 */
	wstats->discard.nwid = 0;	/* Rx invalid nwid      */
	wstats->discard.code = 0;	/* Rx invalid crypt     */
	wstats->discard.fragment = 0;	/* Rx invalid frag      */
	wstats->discard.retries = 0;	/* Tx excessive retries */
	wstats->discard.misc = 0;	/* Invalid misc         */
	wstats->miss.beacon = 0;	/* Missed beacon        */

	वापस wstats;
पूर्ण

अटल पूर्णांक ks_wlan_set_stop_request(काष्ठा net_device *dev,
				    काष्ठा iw_request_info *info, __u32 *uwrq,
				    अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	अगर (!(*uwrq))
		वापस -EINVAL;

	hostअगर_sme_enqueue(priv, SME_STOP_REQUEST);
	वापस 0;
पूर्ण

#समावेश <linux/ieee80211.h>
अटल पूर्णांक ks_wlan_set_mlme(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *dwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);
	काष्ठा iw_mlme *mlme = (काष्ठा iw_mlme *)extra;
	__u32 mode = 1;

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	अगर (mlme->cmd != IW_MLME_DEAUTH &&
	    mlme->cmd != IW_MLME_DISASSOC)
		वापस -EOPNOTSUPP;

	अगर (mlme->cmd == IW_MLME_DEAUTH &&
	    mlme->reason_code == WLAN_REASON_MIC_FAILURE)
		वापस 0;

	वापस ks_wlan_set_stop_request(dev, शून्य, &mode, शून्य);
पूर्ण

अटल पूर्णांक ks_wlan_get_firmware_version(काष्ठा net_device *dev,
					काष्ठा iw_request_info *info,
					काष्ठा iw_poपूर्णांक *dwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	म_नकल(extra, priv->firmware_version);
	dwrq->length = priv->version_size + 1;
	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_preamble(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info, __u32 *uwrq,
				अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	अगर (*uwrq != LONG_PREAMBLE && *uwrq != SHORT_PREAMBLE)
		वापस -EINVAL;

	priv->reg.preamble = *uwrq;
	priv->need_commit |= SME_MODE_SET;
	वापस -EINPROGRESS;	/* Call commit handler */
पूर्ण

अटल पूर्णांक ks_wlan_get_preamble(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info, __u32 *uwrq,
				अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	*uwrq = priv->reg.preamble;
	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_घातer_mgmt(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info, __u32 *uwrq,
				  अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	अगर (*uwrq != POWER_MGMT_ACTIVE &&
	    *uwrq != POWER_MGMT_SAVE1 &&
	    *uwrq != POWER_MGMT_SAVE2)
		वापस -EINVAL;

	अगर ((*uwrq == POWER_MGMT_SAVE1 || *uwrq == POWER_MGMT_SAVE2) &&
	    (priv->reg.operation_mode != MODE_INFRASTRUCTURE))
		वापस -EINVAL;

	priv->reg.घातer_mgmt = *uwrq;
	hostअगर_sme_enqueue(priv, SME_POW_MNGMT_REQUEST);

	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_get_घातer_mgmt(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info, __u32 *uwrq,
				  अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* क्रम SLEEP MODE */
	*uwrq = priv->reg.घातer_mgmt;
	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_scan_type(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info, __u32 *uwrq,
				 अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;
	/* क्रम SLEEP MODE */

	अगर (*uwrq != ACTIVE_SCAN && *uwrq != PASSIVE_SCAN)
		वापस -EINVAL;

	priv->reg.scan_type = *uwrq;
	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_get_scan_type(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info, __u32 *uwrq,
				 अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;
	/* क्रम SLEEP MODE */
	*uwrq = priv->reg.scan_type;
	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_beacon_lost(काष्ठा net_device *dev,
				   काष्ठा iw_request_info *info, __u32 *uwrq,
				   अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;
	/* क्रम SLEEP MODE */
	अगर (*uwrq > BEACON_LOST_COUNT_MAX)
		वापस -EINVAL;

	priv->reg.beacon_lost_count = *uwrq;

	अगर (priv->reg.operation_mode == MODE_INFRASTRUCTURE) अणु
		priv->need_commit |= SME_MODE_SET;
		वापस -EINPROGRESS;	/* Call commit handler */
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_get_beacon_lost(काष्ठा net_device *dev,
				   काष्ठा iw_request_info *info, __u32 *uwrq,
				   अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;
	/* क्रम SLEEP MODE */
	*uwrq = priv->reg.beacon_lost_count;
	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_phy_type(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info, __u32 *uwrq,
				अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	अगर (*uwrq != D_11B_ONLY_MODE &&
	    *uwrq != D_11G_ONLY_MODE &&
	    *uwrq != D_11BG_COMPATIBLE_MODE)
		वापस -EINVAL;

	/* क्रम SLEEP MODE */
	priv->reg.phy_type = *uwrq;
	priv->need_commit |= SME_MODE_SET;
	वापस -EINPROGRESS;	/* Call commit handler */
पूर्ण

अटल पूर्णांक ks_wlan_get_phy_type(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info, __u32 *uwrq,
				अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;
	/* क्रम SLEEP MODE */
	*uwrq = priv->reg.phy_type;
	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_cts_mode(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info, __u32 *uwrq,
				अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;
	/* क्रम SLEEP MODE */
	अगर (*uwrq != CTS_MODE_FALSE && *uwrq != CTS_MODE_TRUE)
		वापस -EINVAL;

	priv->reg.cts_mode = (*uwrq == CTS_MODE_FALSE) ? *uwrq :
			      (priv->reg.phy_type == D_11G_ONLY_MODE ||
			       priv->reg.phy_type == D_11BG_COMPATIBLE_MODE) ?
			       *uwrq : !*uwrq;

	priv->need_commit |= SME_MODE_SET;
	वापस -EINPROGRESS;	/* Call commit handler */
पूर्ण

अटल पूर्णांक ks_wlan_get_cts_mode(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info, __u32 *uwrq,
				अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;
	/* क्रम SLEEP MODE */
	*uwrq = priv->reg.cts_mode;
	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_sleep_mode(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  __u32 *uwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (*uwrq != SLP_SLEEP &&
	    *uwrq != SLP_ACTIVE) अणु
		netdev_err(dev, "SET_SLEEP_MODE %d error\n", *uwrq);
		वापस -EINVAL;
	पूर्ण

	priv->sleep_mode = *uwrq;
	netdev_info(dev, "SET_SLEEP_MODE %d\n", priv->sleep_mode);

	अगर (*uwrq == SLP_SLEEP)
		hostअगर_sme_enqueue(priv, SME_STOP_REQUEST);

	hostअगर_sme_enqueue(priv, SME_SLEEP_REQUEST);

	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_get_sleep_mode(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  __u32 *uwrq, अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	*uwrq = priv->sleep_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_wps_enable(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info, __u32 *uwrq,
				  अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;
	/* क्रम SLEEP MODE */
	अगर (*uwrq != 0 && *uwrq != 1)
		वापस -EINVAL;

	priv->wps.wps_enabled = *uwrq;
	hostअगर_sme_enqueue(priv, SME_WPS_ENABLE_REQUEST);

	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_get_wps_enable(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info, __u32 *uwrq,
				  अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;
	/* क्रम SLEEP MODE */
	*uwrq = priv->wps.wps_enabled;
	netdev_info(dev, "return=%d\n", *uwrq);

	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_wps_probe_req(काष्ठा net_device *dev,
				     काष्ठा iw_request_info *info,
				     काष्ठा iw_poपूर्णांक *dwrq, अक्षर *extra)
अणु
	u8 *p = extra;
	अचिन्हित अक्षर len;
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;

	/* length check */
	अगर (p[1] + 2 != dwrq->length || dwrq->length > 256)
		वापस -EINVAL;

	priv->wps.ielen = p[1] + 2 + 1;	/* IE header + IE + माप(len) */
	len = p[1] + 2;	/* IE header + IE */

	स_नकल(priv->wps.ie, &len, माप(len));
	p = स_नकल(priv->wps.ie + 1, p, len);

	netdev_dbg(dev, "%d(%#x): %02X %02X %02X %02X ... %02X %02X %02X\n",
		   priv->wps.ielen, priv->wps.ielen, p[0], p[1], p[2], p[3],
		   p[priv->wps.ielen - 3], p[priv->wps.ielen - 2],
		   p[priv->wps.ielen - 1]);

	hostअगर_sme_enqueue(priv, SME_WPS_PROBE_REQUEST);

	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_tx_gain(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info, __u32 *uwrq,
			       अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;
	/* क्रम SLEEP MODE */
	अगर (*uwrq > 0xFF)
		वापस -EINVAL;

	priv->gain.tx_gain = (u8)*uwrq;
	priv->gain.tx_mode = (priv->gain.tx_gain < 0xFF) ? 1 : 0;
	hostअगर_sme_enqueue(priv, SME_SET_GAIN);
	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_get_tx_gain(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info, __u32 *uwrq,
			       अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;
	/* क्रम SLEEP MODE */
	*uwrq = priv->gain.tx_gain;
	hostअगर_sme_enqueue(priv, SME_GET_GAIN);
	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_set_rx_gain(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info, __u32 *uwrq,
			       अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;
	/* क्रम SLEEP MODE */
	अगर (*uwrq > 0xFF)
		वापस -EINVAL;

	priv->gain.rx_gain = (u8)*uwrq;
	priv->gain.rx_mode = (priv->gain.rx_gain < 0xFF) ? 1 : 0;
	hostअगर_sme_enqueue(priv, SME_SET_GAIN);
	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_get_rx_gain(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info, __u32 *uwrq,
			       अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->sleep_mode == SLP_SLEEP)
		वापस -EPERM;
	/* क्रम SLEEP MODE */
	*uwrq = priv->gain.rx_gain;
	hostअगर_sme_enqueue(priv, SME_GET_GAIN);
	वापस 0;
पूर्ण

अटल पूर्णांक ks_wlan_get_eeprom_cksum(काष्ठा net_device *dev,
				    काष्ठा iw_request_info *info, __u32 *uwrq,
				    अक्षर *extra)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	*uwrq = priv->eeprom_checksum;
	वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_hअगर_event(काष्ठा net_device *dev, पूर्णांक event)
अणु
	चयन (event) अणु
	हाल HIF_DATA_REQ:
		netdev_info(dev, "HIF_DATA_REQ\n");
		अवरोध;
	हाल HIF_DATA_IND:
		netdev_info(dev, "HIF_DATA_IND\n");
		अवरोध;
	हाल HIF_MIB_GET_REQ:
		netdev_info(dev, "HIF_MIB_GET_REQ\n");
		अवरोध;
	हाल HIF_MIB_GET_CONF:
		netdev_info(dev, "HIF_MIB_GET_CONF\n");
		अवरोध;
	हाल HIF_MIB_SET_REQ:
		netdev_info(dev, "HIF_MIB_SET_REQ\n");
		अवरोध;
	हाल HIF_MIB_SET_CONF:
		netdev_info(dev, "HIF_MIB_SET_CONF\n");
		अवरोध;
	हाल HIF_POWER_MGMT_REQ:
		netdev_info(dev, "HIF_POWER_MGMT_REQ\n");
		अवरोध;
	हाल HIF_POWER_MGMT_CONF:
		netdev_info(dev, "HIF_POWER_MGMT_CONF\n");
		अवरोध;
	हाल HIF_START_REQ:
		netdev_info(dev, "HIF_START_REQ\n");
		अवरोध;
	हाल HIF_START_CONF:
		netdev_info(dev, "HIF_START_CONF\n");
		अवरोध;
	हाल HIF_CONNECT_IND:
		netdev_info(dev, "HIF_CONNECT_IND\n");
		अवरोध;
	हाल HIF_STOP_REQ:
		netdev_info(dev, "HIF_STOP_REQ\n");
		अवरोध;
	हाल HIF_STOP_CONF:
		netdev_info(dev, "HIF_STOP_CONF\n");
		अवरोध;
	हाल HIF_PS_ADH_SET_REQ:
		netdev_info(dev, "HIF_PS_ADH_SET_REQ\n");
		अवरोध;
	हाल HIF_PS_ADH_SET_CONF:
		netdev_info(dev, "HIF_PS_ADH_SET_CONF\n");
		अवरोध;
	हाल HIF_INFRA_SET_REQ:
		netdev_info(dev, "HIF_INFRA_SET_REQ\n");
		अवरोध;
	हाल HIF_INFRA_SET_CONF:
		netdev_info(dev, "HIF_INFRA_SET_CONF\n");
		अवरोध;
	हाल HIF_ADH_SET_REQ:
		netdev_info(dev, "HIF_ADH_SET_REQ\n");
		अवरोध;
	हाल HIF_ADH_SET_CONF:
		netdev_info(dev, "HIF_ADH_SET_CONF\n");
		अवरोध;
	हाल HIF_AP_SET_REQ:
		netdev_info(dev, "HIF_AP_SET_REQ\n");
		अवरोध;
	हाल HIF_AP_SET_CONF:
		netdev_info(dev, "HIF_AP_SET_CONF\n");
		अवरोध;
	हाल HIF_ASSOC_INFO_IND:
		netdev_info(dev, "HIF_ASSOC_INFO_IND\n");
		अवरोध;
	हाल HIF_MIC_FAILURE_REQ:
		netdev_info(dev, "HIF_MIC_FAILURE_REQ\n");
		अवरोध;
	हाल HIF_MIC_FAILURE_CONF:
		netdev_info(dev, "HIF_MIC_FAILURE_CONF\n");
		अवरोध;
	हाल HIF_SCAN_REQ:
		netdev_info(dev, "HIF_SCAN_REQ\n");
		अवरोध;
	हाल HIF_SCAN_CONF:
		netdev_info(dev, "HIF_SCAN_CONF\n");
		अवरोध;
	हाल HIF_PHY_INFO_REQ:
		netdev_info(dev, "HIF_PHY_INFO_REQ\n");
		अवरोध;
	हाल HIF_PHY_INFO_CONF:
		netdev_info(dev, "HIF_PHY_INFO_CONF\n");
		अवरोध;
	हाल HIF_SLEEP_REQ:
		netdev_info(dev, "HIF_SLEEP_REQ\n");
		अवरोध;
	हाल HIF_SLEEP_CONF:
		netdev_info(dev, "HIF_SLEEP_CONF\n");
		अवरोध;
	हाल HIF_PHY_INFO_IND:
		netdev_info(dev, "HIF_PHY_INFO_IND\n");
		अवरोध;
	हाल HIF_SCAN_IND:
		netdev_info(dev, "HIF_SCAN_IND\n");
		अवरोध;
	हाल HIF_INFRA_SET2_REQ:
		netdev_info(dev, "HIF_INFRA_SET2_REQ\n");
		अवरोध;
	हाल HIF_INFRA_SET2_CONF:
		netdev_info(dev, "HIF_INFRA_SET2_CONF\n");
		अवरोध;
	हाल HIF_ADH_SET2_REQ:
		netdev_info(dev, "HIF_ADH_SET2_REQ\n");
		अवरोध;
	हाल HIF_ADH_SET2_CONF:
		netdev_info(dev, "HIF_ADH_SET2_CONF\n");
	पूर्ण
पूर्ण

/* get host command history */
अटल पूर्णांक ks_wlan_hostt(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			 __u32 *uwrq, अक्षर *extra)
अणु
	पूर्णांक i, event;
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	क्रम (i = 63; i >= 0; i--) अणु
		event =
		    priv->hostt.buff[(priv->hostt.qtail - 1 - i) %
				     SME_EVENT_BUFF_SIZE];
		prपूर्णांक_hअगर_event(dev, event);
	पूर्ण
	वापस 0;
पूर्ण

/* Structures to export the Wireless Handlers */

अटल स्थिर काष्ठा iw_priv_args ks_wlan_निजी_args[] = अणु
/*अणु cmd, set_args, get_args, name[16] पूर्ण */
	अणुKS_WLAN_GET_FIRM_VERSION, IW_PRIV_TYPE_NONE,
	 IW_PRIV_TYPE_CHAR | (128 + 1), "GetFirmwareVer"पूर्ण,
	अणुKS_WLAN_SET_WPS_ENABLE, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	 IW_PRIV_TYPE_NONE, "SetWPSEnable"पूर्ण,
	अणुKS_WLAN_GET_WPS_ENABLE, IW_PRIV_TYPE_NONE,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "GetW"पूर्ण,
	अणुKS_WLAN_SET_WPS_PROBE_REQ, IW_PRIV_TYPE_BYTE | 2047, IW_PRIV_TYPE_NONE,
	 "SetWPSProbeReq"पूर्ण,
	अणुKS_WLAN_SET_PREAMBLE, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	 IW_PRIV_TYPE_NONE, "SetPreamble"पूर्ण,
	अणुKS_WLAN_GET_PREAMBLE, IW_PRIV_TYPE_NONE,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "GetPreamble"पूर्ण,
	अणुKS_WLAN_SET_POWER_SAVE, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	 IW_PRIV_TYPE_NONE, "SetPowerSave"पूर्ण,
	अणुKS_WLAN_GET_POWER_SAVE, IW_PRIV_TYPE_NONE,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "GetPowerSave"पूर्ण,
	अणुKS_WLAN_SET_SCAN_TYPE, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	 IW_PRIV_TYPE_NONE, "SetScanType"पूर्ण,
	अणुKS_WLAN_GET_SCAN_TYPE, IW_PRIV_TYPE_NONE,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "GetScanType"पूर्ण,
	अणुKS_WLAN_SET_RX_GAIN, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	 IW_PRIV_TYPE_NONE, "SetRxGain"पूर्ण,
	अणुKS_WLAN_GET_RX_GAIN, IW_PRIV_TYPE_NONE,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "GetRxGain"पूर्ण,
	अणुKS_WLAN_HOSTT, IW_PRIV_TYPE_NONE, IW_PRIV_TYPE_CHAR | (128 + 1),
	 "hostt"पूर्ण,
	अणुKS_WLAN_SET_BEACON_LOST, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	 IW_PRIV_TYPE_NONE, "SetBeaconLost"पूर्ण,
	अणुKS_WLAN_GET_BEACON_LOST, IW_PRIV_TYPE_NONE,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "GetBeaconLost"पूर्ण,
	अणुKS_WLAN_SET_SLEEP_MODE, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	 IW_PRIV_TYPE_NONE, "SetSleepMode"पूर्ण,
	अणुKS_WLAN_GET_SLEEP_MODE, IW_PRIV_TYPE_NONE,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "GetSleepMode"पूर्ण,
	अणुKS_WLAN_SET_TX_GAIN, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	 IW_PRIV_TYPE_NONE, "SetTxGain"पूर्ण,
	अणुKS_WLAN_GET_TX_GAIN, IW_PRIV_TYPE_NONE,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "GetTxGain"पूर्ण,
	अणुKS_WLAN_SET_PHY_TYPE, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	 IW_PRIV_TYPE_NONE, "SetPhyType"पूर्ण,
	अणुKS_WLAN_GET_PHY_TYPE, IW_PRIV_TYPE_NONE,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "GetPhyType"पूर्ण,
	अणुKS_WLAN_SET_CTS_MODE, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	 IW_PRIV_TYPE_NONE, "SetCtsMode"पूर्ण,
	अणुKS_WLAN_GET_CTS_MODE, IW_PRIV_TYPE_NONE,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "GetCtsMode"पूर्ण,
	अणुKS_WLAN_GET_EEPROM_CKSUM, IW_PRIV_TYPE_NONE,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "GetChecksum"पूर्ण,
पूर्ण;

अटल स्थिर iw_handler ks_wlan_handler[] = अणु
	IW_HANDLER(SIOCSIWCOMMIT, ks_wlan_config_commit),
	IW_HANDLER(SIOCGIWNAME, ks_wlan_get_name),
	IW_HANDLER(SIOCSIWFREQ, ks_wlan_set_freq),
	IW_HANDLER(SIOCGIWFREQ, ks_wlan_get_freq),
	IW_HANDLER(SIOCSIWMODE, ks_wlan_set_mode),
	IW_HANDLER(SIOCGIWMODE, ks_wlan_get_mode),
	IW_HANDLER(SIOCGIWRANGE, ks_wlan_get_range),
	IW_HANDLER(SIOCGIWSTATS, ks_wlan_get_iwstats),
	IW_HANDLER(SIOCSIWAP, ks_wlan_set_wap),
	IW_HANDLER(SIOCGIWAP, ks_wlan_get_wap),
	IW_HANDLER(SIOCSIWMLME, ks_wlan_set_mlme),
	IW_HANDLER(SIOCGIWAPLIST, ks_wlan_get_aplist),
	IW_HANDLER(SIOCSIWSCAN, ks_wlan_set_scan),
	IW_HANDLER(SIOCGIWSCAN, ks_wlan_get_scan),
	IW_HANDLER(SIOCSIWESSID, ks_wlan_set_essid),
	IW_HANDLER(SIOCGIWESSID, ks_wlan_get_essid),
	IW_HANDLER(SIOCSIWNICKN, ks_wlan_set_nick),
	IW_HANDLER(SIOCGIWNICKN, ks_wlan_get_nick),
	IW_HANDLER(SIOCSIWRATE, ks_wlan_set_rate),
	IW_HANDLER(SIOCGIWRATE, ks_wlan_get_rate),
	IW_HANDLER(SIOCSIWRTS, ks_wlan_set_rts),
	IW_HANDLER(SIOCGIWRTS, ks_wlan_get_rts),
	IW_HANDLER(SIOCSIWFRAG, ks_wlan_set_frag),
	IW_HANDLER(SIOCGIWFRAG, ks_wlan_get_frag),
	IW_HANDLER(SIOCSIWENCODE, ks_wlan_set_encode),
	IW_HANDLER(SIOCGIWENCODE, ks_wlan_get_encode),
	IW_HANDLER(SIOCSIWPOWER, ks_wlan_set_घातer),
	IW_HANDLER(SIOCGIWPOWER, ks_wlan_get_घातer),
	IW_HANDLER(SIOCSIWGENIE, ks_wlan_set_genie),
	IW_HANDLER(SIOCSIWAUTH, ks_wlan_set_auth_mode),
	IW_HANDLER(SIOCGIWAUTH, ks_wlan_get_auth_mode),
	IW_HANDLER(SIOCSIWENCODEEXT, ks_wlan_set_encode_ext),
	IW_HANDLER(SIOCGIWENCODEEXT, ks_wlan_get_encode_ext),
	IW_HANDLER(SIOCSIWPMKSA, ks_wlan_set_pmksa),
पूर्ण;

/* निजी_handler */
अटल स्थिर iw_handler ks_wlan_निजी_handler[] = अणु
	(iw_handler)शून्य,			/* 0 */
	(iw_handler)शून्य,			/* 1, KS_WLAN_GET_DRIVER_VERSION */
	(iw_handler)शून्य,			/* 2 */
	(iw_handler)ks_wlan_get_firmware_version,/* 3 KS_WLAN_GET_FIRM_VERSION */
	(iw_handler)ks_wlan_set_wps_enable,	/* 4 KS_WLAN_SET_WPS_ENABLE */
	(iw_handler)ks_wlan_get_wps_enable,	/* 5 KS_WLAN_GET_WPS_ENABLE */
	(iw_handler)ks_wlan_set_wps_probe_req,	/* 6 KS_WLAN_SET_WPS_PROBE_REQ */
	(iw_handler)ks_wlan_get_eeprom_cksum,	/* 7 KS_WLAN_GET_CONNECT */
	(iw_handler)ks_wlan_set_preamble,	/* 8 KS_WLAN_SET_PREAMBLE */
	(iw_handler)ks_wlan_get_preamble,	/* 9 KS_WLAN_GET_PREAMBLE */
	(iw_handler)ks_wlan_set_घातer_mgmt,	/* 10 KS_WLAN_SET_POWER_SAVE */
	(iw_handler)ks_wlan_get_घातer_mgmt,	/* 11 KS_WLAN_GET_POWER_SAVE */
	(iw_handler)ks_wlan_set_scan_type,	/* 12 KS_WLAN_SET_SCAN_TYPE */
	(iw_handler)ks_wlan_get_scan_type,	/* 13 KS_WLAN_GET_SCAN_TYPE */
	(iw_handler)ks_wlan_set_rx_gain,	/* 14 KS_WLAN_SET_RX_GAIN */
	(iw_handler)ks_wlan_get_rx_gain,	/* 15 KS_WLAN_GET_RX_GAIN */
	(iw_handler)ks_wlan_hostt,		/* 16 KS_WLAN_HOSTT */
	(iw_handler)शून्य,			/* 17 */
	(iw_handler)ks_wlan_set_beacon_lost,	/* 18 KS_WLAN_SET_BECAN_LOST */
	(iw_handler)ks_wlan_get_beacon_lost,	/* 19 KS_WLAN_GET_BECAN_LOST */
	(iw_handler)ks_wlan_set_tx_gain,	/* 20 KS_WLAN_SET_TX_GAIN */
	(iw_handler)ks_wlan_get_tx_gain,	/* 21 KS_WLAN_GET_TX_GAIN */
	(iw_handler)ks_wlan_set_phy_type,	/* 22 KS_WLAN_SET_PHY_TYPE */
	(iw_handler)ks_wlan_get_phy_type,	/* 23 KS_WLAN_GET_PHY_TYPE */
	(iw_handler)ks_wlan_set_cts_mode,	/* 24 KS_WLAN_SET_CTS_MODE */
	(iw_handler)ks_wlan_get_cts_mode,	/* 25 KS_WLAN_GET_CTS_MODE */
	(iw_handler)शून्य,			/* 26 */
	(iw_handler)शून्य,			/* 27 */
	(iw_handler)ks_wlan_set_sleep_mode,	/* 28 KS_WLAN_SET_SLEEP_MODE */
	(iw_handler)ks_wlan_get_sleep_mode,	/* 29 KS_WLAN_GET_SLEEP_MODE */
	(iw_handler)शून्य,			/* 30 */
	(iw_handler)शून्य,			/* 31 */
पूर्ण;

अटल स्थिर काष्ठा iw_handler_def ks_wlan_handler_def = अणु
	.num_standard = ARRAY_SIZE(ks_wlan_handler),
	.num_निजी = ARRAY_SIZE(ks_wlan_निजी_handler),
	.num_निजी_args = ARRAY_SIZE(ks_wlan_निजी_args),
	.standard = ks_wlan_handler,
	.निजी = ks_wlan_निजी_handler,
	.निजी_args = ks_wlan_निजी_args,
	.get_wireless_stats = ks_get_wireless_stats,
पूर्ण;

अटल पूर्णांक ks_wlan_netdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq,
				पूर्णांक cmd)
अणु
	पूर्णांक ret;
	काष्ठा iwreq *wrq = (काष्ठा iwreq *)rq;

	चयन (cmd) अणु
	हाल SIOCIWFIRSTPRIV + 20:	/* KS_WLAN_SET_STOP_REQ */
		ret = ks_wlan_set_stop_request(dev, शून्य, &wrq->u.mode, शून्य);
		अवरोध;
		// All other calls are currently unsupported
	शेष:
		ret = -EOPNOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल
काष्ठा net_device_stats *ks_wlan_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->dev_state < DEVICE_STATE_READY)
		वापस शून्य;	/* not finished initialize */

	वापस &priv->nstats;
पूर्ण

अटल
पूर्णांक ks_wlan_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);
	काष्ठा sockaddr *mac_addr = (काष्ठा sockaddr *)addr;

	अगर (netअगर_running(dev))
		वापस -EBUSY;
	स_नकल(dev->dev_addr, mac_addr->sa_data, dev->addr_len);
	ether_addr_copy(priv->eth_addr, mac_addr->sa_data);

	priv->mac_address_valid = false;
	hostअगर_sme_enqueue(priv, SME_MACADDRESS_SET_REQUEST);
	netdev_info(dev, "ks_wlan:  MAC ADDRESS = %pM\n", priv->eth_addr);
	वापस 0;
पूर्ण

अटल
व्योम ks_wlan_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	netdev_dbg(dev, "head(%d) tail(%d)!!\n", priv->tx_dev.qhead,
		   priv->tx_dev.qtail);
	अगर (!netअगर_queue_stopped(dev))
		netअगर_stop_queue(dev);
	priv->nstats.tx_errors++;
	netअगर_wake_queue(dev);
पूर्ण

अटल
netdev_tx_t ks_wlan_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);
	पूर्णांक ret;

	netdev_dbg(dev, "in_interrupt()=%ld\n", in_पूर्णांकerrupt());

	अगर (!skb) अणु
		netdev_err(dev, "ks_wlan:  skb == NULL!!!\n");
		वापस 0;
	पूर्ण
	अगर (priv->dev_state < DEVICE_STATE_READY) अणु
		dev_kमुक्त_skb(skb);
		वापस 0;	/* not finished initialize */
	पूर्ण

	अगर (netअगर_running(dev))
		netअगर_stop_queue(dev);

	ret = hostअगर_data_request(priv, skb);
	netअगर_trans_update(dev);

	अगर (ret)
		netdev_err(dev, "hostif_data_request error: =%d\n", ret);

	वापस 0;
पूर्ण

व्योम send_packet_complete(काष्ठा ks_wlan_निजी *priv, काष्ठा sk_buff *skb)
अणु
	priv->nstats.tx_packets++;

	अगर (netअगर_queue_stopped(priv->net_dev))
		netअगर_wake_queue(priv->net_dev);

	अगर (skb) अणु
		priv->nstats.tx_bytes += skb->len;
		dev_kमुक्त_skb(skb);
	पूर्ण
पूर्ण

/*
 * Set or clear the multicast filter क्रम this adaptor.
 * This routine is not state sensitive and need not be SMP locked.
 */
अटल
व्योम ks_wlan_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	अगर (priv->dev_state < DEVICE_STATE_READY)
		वापस;	/* not finished initialize */
	hostअगर_sme_enqueue(priv, SME_MULTICAST_REQUEST);
पूर्ण

अटल
पूर्णांक ks_wlan_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	priv->cur_rx = 0;

	अगर (!priv->mac_address_valid) अणु
		netdev_err(dev, "ks_wlan : %s Not READY !!\n", dev->name);
		वापस -EBUSY;
	पूर्ण
	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

अटल
पूर्णांक ks_wlan_बंद(काष्ठा net_device *dev)
अणु
	netअगर_stop_queue(dev);

	वापस 0;
पूर्ण

/* Operational parameters that usually are not changed. */
/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT  (3 * HZ)
अटल स्थिर अचिन्हित अक्षर dummy_addr[] = अणु
	0x00, 0x0b, 0xe3, 0x00, 0x00, 0x00
पूर्ण;

अटल स्थिर काष्ठा net_device_ops ks_wlan_netdev_ops = अणु
	.nकरो_start_xmit = ks_wlan_start_xmit,
	.nकरो_खोलो = ks_wlan_खोलो,
	.nकरो_stop = ks_wlan_बंद,
	.nकरो_करो_ioctl = ks_wlan_netdev_ioctl,
	.nकरो_set_mac_address = ks_wlan_set_mac_address,
	.nकरो_get_stats = ks_wlan_get_stats,
	.nकरो_tx_समयout = ks_wlan_tx_समयout,
	.nकरो_set_rx_mode = ks_wlan_set_rx_mode,
पूर्ण;

पूर्णांक ks_wlan_net_start(काष्ठा net_device *dev)
अणु
	काष्ठा ks_wlan_निजी *priv;
	/* पूर्णांक rc; */

	priv = netdev_priv(dev);
	priv->mac_address_valid = false;
	priv->is_device_खोलो = true;
	priv->need_commit = 0;
	/* phy inक्रमmation update समयr */
	atomic_set(&update_phyinfo, 0);
	समयr_setup(&update_phyinfo_समयr, ks_wlan_update_phyinfo_समयout, 0);

	/* dummy address set */
	ether_addr_copy(priv->eth_addr, dummy_addr);
	ether_addr_copy(dev->dev_addr, priv->eth_addr);

	/* The ks_wlan-specअगरic entries in the device काष्ठाure. */
	dev->netdev_ops = &ks_wlan_netdev_ops;
	dev->wireless_handlers = &ks_wlan_handler_def;
	dev->watchकरोg_समयo = TX_TIMEOUT;

	netअगर_carrier_off(dev);

	वापस 0;
पूर्ण

पूर्णांक ks_wlan_net_stop(काष्ठा net_device *dev)
अणु
	काष्ठा ks_wlan_निजी *priv = netdev_priv(dev);

	priv->is_device_खोलो = false;
	del_समयr_sync(&update_phyinfo_समयr);

	अगर (netअगर_running(dev))
		netअगर_stop_queue(dev);

	वापस 0;
पूर्ण

/**
 * is_connect_status() - वापस true अगर status is 'connected'
 * @status: high bit is used as FORCE_DISCONNECT, low bits used क्रम
 *	connect status.
 */
bool is_connect_status(u32 status)
अणु
	वापस (status & CONNECT_STATUS_MASK) == CONNECT_STATUS;
पूर्ण

/**
 * is_disconnect_status() - वापस true अगर status is 'disconnected'
 * @status: high bit is used as FORCE_DISCONNECT, low bits used क्रम
 *	disconnect status.
 */
bool is_disconnect_status(u32 status)
अणु
	वापस (status & CONNECT_STATUS_MASK) == DISCONNECT_STATUS;
पूर्ण
