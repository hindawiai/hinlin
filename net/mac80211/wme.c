<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2004, Instant802 Networks, Inc.
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/module.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/types.h>
#समावेश <net/ip.h>
#समावेश <net/pkt_sched.h>

#समावेश <net/mac80211.h>
#समावेश "ieee80211_i.h"
#समावेश "wme.h"

/* Default mapping in classअगरier to work with शेष
 * queue setup.
 */
स्थिर पूर्णांक ieee802_1d_to_ac[8] = अणु
	IEEE80211_AC_BE,
	IEEE80211_AC_BK,
	IEEE80211_AC_BK,
	IEEE80211_AC_BE,
	IEEE80211_AC_VI,
	IEEE80211_AC_VI,
	IEEE80211_AC_VO,
	IEEE80211_AC_VO
पूर्ण;

अटल पूर्णांक wme_करोwngrade_ac(काष्ठा sk_buff *skb)
अणु
	चयन (skb->priority) अणु
	हाल 6:
	हाल 7:
		skb->priority = 5; /* VO -> VI */
		वापस 0;
	हाल 4:
	हाल 5:
		skb->priority = 3; /* VI -> BE */
		वापस 0;
	हाल 0:
	हाल 3:
		skb->priority = 2; /* BE -> BK */
		वापस 0;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

/**
 * ieee80211_fix_reserved_tid - वापस the TID to use अगर this one is reserved
 * @tid: the assumed-reserved TID
 *
 * Returns: the alternative TID to use, or 0 on error
 */
अटल अंतरभूत u8 ieee80211_fix_reserved_tid(u8 tid)
अणु
	चयन (tid) अणु
	हाल 0:
		वापस 3;
	हाल 1:
		वापस 2;
	हाल 2:
		वापस 1;
	हाल 3:
		वापस 0;
	हाल 4:
		वापस 5;
	हाल 5:
		वापस 4;
	हाल 6:
		वापस 7;
	हाल 7:
		वापस 6;
	पूर्ण

	वापस 0;
पूर्ण

अटल u16 ieee80211_करोwngrade_queue(काष्ठा ieee80211_sub_अगर_data *sdata,
				     काष्ठा sta_info *sta, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;

	/* in हाल we are a client verअगरy acm is not set क्रम this ac */
	जबतक (sdata->wmm_acm & BIT(skb->priority)) अणु
		पूर्णांक ac = ieee802_1d_to_ac[skb->priority];

		अगर (अगरmgd->tx_tspec[ac].admitted_समय &&
		    skb->priority == अगरmgd->tx_tspec[ac].up)
			वापस ac;

		अगर (wme_करोwngrade_ac(skb)) अणु
			/*
			 * This should not really happen. The AP has marked all
			 * lower ACs to require admission control which is not
			 * a reasonable configuration. Allow the frame to be
			 * transmitted using AC_BK as a workaround.
			 */
			अवरोध;
		पूर्ण
	पूर्ण

	/* Check to see अगर this is a reserved TID */
	अगर (sta && sta->reserved_tid == skb->priority)
		skb->priority = ieee80211_fix_reserved_tid(skb->priority);

	/* look up which queue to use क्रम frames with this 1d tag */
	वापस ieee802_1d_to_ac[skb->priority];
पूर्ण

/* Indicate which queue to use क्रम this fully क्रमmed 802.11 frame */
u16 ieee80211_select_queue_80211(काष्ठा ieee80211_sub_अगर_data *sdata,
				 काष्ठा sk_buff *skb,
				 काष्ठा ieee80211_hdr *hdr)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	u8 *p;

	अगर ((info->control.flags & IEEE80211_TX_CTRL_DONT_REORDER) ||
	    local->hw.queues < IEEE80211_NUM_ACS)
		वापस 0;

	अगर (!ieee80211_is_data(hdr->frame_control)) अणु
		skb->priority = 7;
		वापस ieee802_1d_to_ac[skb->priority];
	पूर्ण
	अगर (!ieee80211_is_data_qos(hdr->frame_control)) अणु
		skb->priority = 0;
		वापस ieee802_1d_to_ac[skb->priority];
	पूर्ण

	p = ieee80211_get_qos_ctl(hdr);
	skb->priority = *p & IEEE80211_QOS_CTL_TAG1D_MASK;

	वापस ieee80211_करोwngrade_queue(sdata, शून्य, skb);
पूर्ण

u16 __ieee80211_select_queue(काष्ठा ieee80211_sub_अगर_data *sdata,
			     काष्ठा sta_info *sta, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा mac80211_qos_map *qos_map;
	bool qos;

	/* all mesh/ocb stations are required to support WME */
	अगर (sdata->vअगर.type == NL80211_IFTYPE_MESH_POINT ||
	    sdata->vअगर.type == NL80211_IFTYPE_OCB)
		qos = true;
	अन्यथा अगर (sta)
		qos = sta->sta.wme;
	अन्यथा
		qos = false;

	अगर (!qos || (info->control.flags & IEEE80211_TX_CTRL_DONT_REORDER)) अणु
		skb->priority = 0; /* required क्रम correct WPA/11i MIC */
		वापस IEEE80211_AC_BE;
	पूर्ण

	अगर (skb->protocol == sdata->control_port_protocol) अणु
		skb->priority = 7;
		जाओ करोwngrade;
	पूर्ण

	/* use the data classअगरier to determine what 802.1d tag the
	 * data frame has */
	qos_map = rcu_dereference(sdata->qos_map);
	skb->priority = cfg80211_classअगरy8021d(skb, qos_map ?
					       &qos_map->qos_map : शून्य);

 करोwngrade:
	वापस ieee80211_करोwngrade_queue(sdata, sta, skb);
पूर्ण


/* Indicate which queue to use. */
u16 ieee80211_select_queue(काष्ठा ieee80211_sub_अगर_data *sdata,
			   काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta = शून्य;
	स्थिर u8 *ra = शून्य;
	u16 ret;

	/* when using iTXQ, we can करो this later */
	अगर (local->ops->wake_tx_queue)
		वापस 0;

	अगर (local->hw.queues < IEEE80211_NUM_ACS || skb->len < 6) अणु
		skb->priority = 0; /* required क्रम correct WPA/11i MIC */
		वापस 0;
	पूर्ण

	rcu_पढ़ो_lock();
	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_AP_VLAN:
		sta = rcu_dereference(sdata->u.vlan.sta);
		अगर (sta)
			अवरोध;
		fallthrough;
	हाल NL80211_IFTYPE_AP:
		ra = skb->data;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		/* might be a TDLS station */
		sta = sta_info_get(sdata, skb->data);
		अगर (sta)
			अवरोध;

		ra = sdata->u.mgd.bssid;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		ra = skb->data;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!sta && ra && !is_multicast_ether_addr(ra))
		sta = sta_info_get(sdata, ra);

	ret = __ieee80211_select_queue(sdata, sta, skb);

	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/**
 * ieee80211_set_qos_hdr - Fill in the QoS header अगर there is one.
 *
 * @sdata: local subअगर
 * @skb: packet to be updated
 */
व्योम ieee80211_set_qos_hdr(काष्ठा ieee80211_sub_अगर_data *sdata,
			   काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	u8 tid = skb->priority & IEEE80211_QOS_CTL_TAG1D_MASK;
	u8 flags;
	u8 *p;

	अगर (!ieee80211_is_data_qos(hdr->frame_control))
		वापस;

	p = ieee80211_get_qos_ctl(hdr);

	/* करोn't overग_लिखो the QoS field of injected frames */
	अगर (info->flags & IEEE80211_TX_CTL_INJECTED) अणु
		/* करो take पूर्णांकo account Ack policy of injected frames */
		अगर (*p & IEEE80211_QOS_CTL_ACK_POLICY_NOACK)
			info->flags |= IEEE80211_TX_CTL_NO_ACK;
		वापस;
	पूर्ण

	/* set up the first byte */

	/*
	 * preserve everything but the TID and ACK policy
	 * (which we both ग_लिखो here)
	 */
	flags = *p & ~(IEEE80211_QOS_CTL_TID_MASK |
		       IEEE80211_QOS_CTL_ACK_POLICY_MASK);

	अगर (is_multicast_ether_addr(hdr->addr1) ||
	    sdata->noack_map & BIT(tid)) अणु
		flags |= IEEE80211_QOS_CTL_ACK_POLICY_NOACK;
		info->flags |= IEEE80211_TX_CTL_NO_ACK;
	पूर्ण

	*p = flags | tid;

	/* set up the second byte */
	p++;

	अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर)) अणु
		/* preserve RSPI and Mesh PS Level bit */
		*p &= ((IEEE80211_QOS_CTL_RSPI |
			IEEE80211_QOS_CTL_MESH_PS_LEVEL) >> 8);

		/* Nulls करोn't have a mesh header (frame body) */
		अगर (!ieee80211_is_qos_nullfunc(hdr->frame_control))
			*p |= (IEEE80211_QOS_CTL_MESH_CONTROL_PRESENT >> 8);
	पूर्ण अन्यथा अणु
		*p = 0;
	पूर्ण
पूर्ण
