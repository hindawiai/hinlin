<शैली गुरु>
/*
 * This file implement the Wireless Extensions core API.
 *
 * Authors :	Jean Tourrilhes - HPL - <jt@hpl.hp.com>
 * Copyright (c) 1997-2007 Jean Tourrilhes, All Rights Reserved.
 * Copyright	2009 Johannes Berg <johannes@sipsolutions.net>
 *
 * (As all part of the Linux kernel, this file is GPL)
 */
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>
#समावेश <linux/wireless.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/export.h>
#समावेश <net/cfg80211.h>
#समावेश <net/iw_handler.h>
#समावेश <net/netlink.h>
#समावेश <net/wext.h>
#समावेश <net/net_namespace.h>

प्रकार पूर्णांक (*wext_ioctl_func)(काष्ठा net_device *, काष्ठा iwreq *,
			       अचिन्हित पूर्णांक, काष्ठा iw_request_info *,
			       iw_handler);


/*
 * Meta-data about all the standard Wireless Extension request we
 * know about.
 */
अटल स्थिर काष्ठा iw_ioctl_description standard_ioctl[] = अणु
	[IW_IOCTL_IDX(SIOCSIWCOMMIT)] = अणु
		.header_type	= IW_HEADER_TYPE_शून्य,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWNAME)] = अणु
		.header_type	= IW_HEADER_TYPE_CHAR,
		.flags		= IW_DESCR_FLAG_DUMP,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWNWID)] = अणु
		.header_type	= IW_HEADER_TYPE_PARAM,
		.flags		= IW_DESCR_FLAG_EVENT,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWNWID)] = अणु
		.header_type	= IW_HEADER_TYPE_PARAM,
		.flags		= IW_DESCR_FLAG_DUMP,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWFREQ)] = अणु
		.header_type	= IW_HEADER_TYPE_FREQ,
		.flags		= IW_DESCR_FLAG_EVENT,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWFREQ)] = अणु
		.header_type	= IW_HEADER_TYPE_FREQ,
		.flags		= IW_DESCR_FLAG_DUMP,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWMODE)] = अणु
		.header_type	= IW_HEADER_TYPE_UINT,
		.flags		= IW_DESCR_FLAG_EVENT,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWMODE)] = अणु
		.header_type	= IW_HEADER_TYPE_UINT,
		.flags		= IW_DESCR_FLAG_DUMP,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWSENS)] = अणु
		.header_type	= IW_HEADER_TYPE_PARAM,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWSENS)] = अणु
		.header_type	= IW_HEADER_TYPE_PARAM,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWRANGE)] = अणु
		.header_type	= IW_HEADER_TYPE_शून्य,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWRANGE)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= माप(काष्ठा iw_range),
		.flags		= IW_DESCR_FLAG_DUMP,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWPRIV)] = अणु
		.header_type	= IW_HEADER_TYPE_शून्य,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWPRIV)] = अणु /* (handled directly by us) */
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= माप(काष्ठा iw_priv_args),
		.max_tokens	= 16,
		.flags		= IW_DESCR_FLAG_NOMAX,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWSTATS)] = अणु
		.header_type	= IW_HEADER_TYPE_शून्य,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWSTATS)] = अणु /* (handled directly by us) */
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= माप(काष्ठा iw_statistics),
		.flags		= IW_DESCR_FLAG_DUMP,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWSPY)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= माप(काष्ठा sockaddr),
		.max_tokens	= IW_MAX_SPY,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWSPY)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= माप(काष्ठा sockaddr) +
				  माप(काष्ठा iw_quality),
		.max_tokens	= IW_MAX_SPY,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWTHRSPY)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= माप(काष्ठा iw_thrspy),
		.min_tokens	= 1,
		.max_tokens	= 1,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWTHRSPY)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= माप(काष्ठा iw_thrspy),
		.min_tokens	= 1,
		.max_tokens	= 1,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWAP)] = अणु
		.header_type	= IW_HEADER_TYPE_ADDR,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWAP)] = अणु
		.header_type	= IW_HEADER_TYPE_ADDR,
		.flags		= IW_DESCR_FLAG_DUMP,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWMLME)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.min_tokens	= माप(काष्ठा iw_mlme),
		.max_tokens	= माप(काष्ठा iw_mlme),
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWAPLIST)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= माप(काष्ठा sockaddr) +
				  माप(काष्ठा iw_quality),
		.max_tokens	= IW_MAX_AP,
		.flags		= IW_DESCR_FLAG_NOMAX,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWSCAN)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.min_tokens	= 0,
		.max_tokens	= माप(काष्ठा iw_scan_req),
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWSCAN)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_SCAN_MAX_DATA,
		.flags		= IW_DESCR_FLAG_NOMAX,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWESSID)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_ESSID_MAX_SIZE,
		.flags		= IW_DESCR_FLAG_EVENT,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWESSID)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_ESSID_MAX_SIZE,
		.flags		= IW_DESCR_FLAG_DUMP,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWNICKN)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_ESSID_MAX_SIZE,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWNICKN)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_ESSID_MAX_SIZE,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWRATE)] = अणु
		.header_type	= IW_HEADER_TYPE_PARAM,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWRATE)] = अणु
		.header_type	= IW_HEADER_TYPE_PARAM,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWRTS)] = अणु
		.header_type	= IW_HEADER_TYPE_PARAM,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWRTS)] = अणु
		.header_type	= IW_HEADER_TYPE_PARAM,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWFRAG)] = अणु
		.header_type	= IW_HEADER_TYPE_PARAM,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWFRAG)] = अणु
		.header_type	= IW_HEADER_TYPE_PARAM,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWTXPOW)] = अणु
		.header_type	= IW_HEADER_TYPE_PARAM,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWTXPOW)] = अणु
		.header_type	= IW_HEADER_TYPE_PARAM,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWRETRY)] = अणु
		.header_type	= IW_HEADER_TYPE_PARAM,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWRETRY)] = अणु
		.header_type	= IW_HEADER_TYPE_PARAM,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWENCODE)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_ENCODING_TOKEN_MAX,
		.flags		= IW_DESCR_FLAG_EVENT | IW_DESCR_FLAG_RESTRICT,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWENCODE)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_ENCODING_TOKEN_MAX,
		.flags		= IW_DESCR_FLAG_DUMP | IW_DESCR_FLAG_RESTRICT,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWPOWER)] = अणु
		.header_type	= IW_HEADER_TYPE_PARAM,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWPOWER)] = अणु
		.header_type	= IW_HEADER_TYPE_PARAM,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWGENIE)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_GENERIC_IE_MAX,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWGENIE)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_GENERIC_IE_MAX,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWAUTH)] = अणु
		.header_type	= IW_HEADER_TYPE_PARAM,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWAUTH)] = अणु
		.header_type	= IW_HEADER_TYPE_PARAM,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWENCODEEXT)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.min_tokens	= माप(काष्ठा iw_encode_ext),
		.max_tokens	= माप(काष्ठा iw_encode_ext) +
				  IW_ENCODING_TOKEN_MAX,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCGIWENCODEEXT)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.min_tokens	= माप(काष्ठा iw_encode_ext),
		.max_tokens	= माप(काष्ठा iw_encode_ext) +
				  IW_ENCODING_TOKEN_MAX,
	पूर्ण,
	[IW_IOCTL_IDX(SIOCSIWPMKSA)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.min_tokens	= माप(काष्ठा iw_pmksa),
		.max_tokens	= माप(काष्ठा iw_pmksa),
	पूर्ण,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक standard_ioctl_num = ARRAY_SIZE(standard_ioctl);

/*
 * Meta-data about all the additional standard Wireless Extension events
 * we know about.
 */
अटल स्थिर काष्ठा iw_ioctl_description standard_event[] = अणु
	[IW_EVENT_IDX(IWEVTXDROP)] = अणु
		.header_type	= IW_HEADER_TYPE_ADDR,
	पूर्ण,
	[IW_EVENT_IDX(IWEVQUAL)] = अणु
		.header_type	= IW_HEADER_TYPE_QUAL,
	पूर्ण,
	[IW_EVENT_IDX(IWEVCUSTOM)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_CUSTOM_MAX,
	पूर्ण,
	[IW_EVENT_IDX(IWEVREGISTERED)] = अणु
		.header_type	= IW_HEADER_TYPE_ADDR,
	पूर्ण,
	[IW_EVENT_IDX(IWEVEXPIRED)] = अणु
		.header_type	= IW_HEADER_TYPE_ADDR,
	पूर्ण,
	[IW_EVENT_IDX(IWEVGENIE)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_GENERIC_IE_MAX,
	पूर्ण,
	[IW_EVENT_IDX(IWEVMICHAELMICFAILURE)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= माप(काष्ठा iw_michaelmicfailure),
	पूर्ण,
	[IW_EVENT_IDX(IWEVASSOCREQIE)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_GENERIC_IE_MAX,
	पूर्ण,
	[IW_EVENT_IDX(IWEVASSOCRESPIE)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_GENERIC_IE_MAX,
	पूर्ण,
	[IW_EVENT_IDX(IWEVPMKIDCAND)] = अणु
		.header_type	= IW_HEADER_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= माप(काष्ठा iw_pmkid_cand),
	पूर्ण,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक standard_event_num = ARRAY_SIZE(standard_event);

/* Size (in bytes) of various events */
अटल स्थिर पूर्णांक event_type_size[] = अणु
	IW_EV_LCP_LEN,			/* IW_HEADER_TYPE_शून्य */
	0,
	IW_EV_CHAR_LEN,			/* IW_HEADER_TYPE_CHAR */
	0,
	IW_EV_UINT_LEN,			/* IW_HEADER_TYPE_UINT */
	IW_EV_FREQ_LEN,			/* IW_HEADER_TYPE_FREQ */
	IW_EV_ADDR_LEN,			/* IW_HEADER_TYPE_ADDR */
	0,
	IW_EV_POINT_LEN,		/* Without variable payload */
	IW_EV_PARAM_LEN,		/* IW_HEADER_TYPE_PARAM */
	IW_EV_QUAL_LEN,			/* IW_HEADER_TYPE_QUAL */
पूर्ण;

#अगर_घोषित CONFIG_COMPAT
अटल स्थिर पूर्णांक compat_event_type_size[] = अणु
	IW_EV_COMPAT_LCP_LEN,		/* IW_HEADER_TYPE_शून्य */
	0,
	IW_EV_COMPAT_CHAR_LEN,		/* IW_HEADER_TYPE_CHAR */
	0,
	IW_EV_COMPAT_UINT_LEN,		/* IW_HEADER_TYPE_UINT */
	IW_EV_COMPAT_FREQ_LEN,		/* IW_HEADER_TYPE_FREQ */
	IW_EV_COMPAT_ADDR_LEN,		/* IW_HEADER_TYPE_ADDR */
	0,
	IW_EV_COMPAT_POINT_LEN,		/* Without variable payload */
	IW_EV_COMPAT_PARAM_LEN,		/* IW_HEADER_TYPE_PARAM */
	IW_EV_COMPAT_QUAL_LEN,		/* IW_HEADER_TYPE_QUAL */
पूर्ण;
#पूर्ण_अगर


/* IW event code */

व्योम wireless_nlevent_flush(व्योम)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा net *net;

	करोwn_पढ़ो(&net_rwsem);
	क्रम_each_net(net) अणु
		जबतक ((skb = skb_dequeue(&net->wext_nlevents)))
			rtnl_notअगरy(skb, net, 0, RTNLGRP_LINK, शून्य,
				    GFP_KERNEL);
	पूर्ण
	up_पढ़ो(&net_rwsem);
पूर्ण
EXPORT_SYMBOL_GPL(wireless_nlevent_flush);

अटल पूर्णांक wext_netdev_notअगरier_call(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ state, व्योम *ptr)
अणु
	/*
	 * When a netdev changes state in any way, flush all pending messages
	 * to aव्योम them going out in a strange order, e.g. RTM_NEWLINK after
	 * RTM_DELLINK, or with IFF_UP after without IFF_UP during dev_बंद()
	 * or similar - all of which could otherwise happen due to delays from
	 * schedule_work().
	 */
	wireless_nlevent_flush();

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block wext_netdev_notअगरier = अणु
	.notअगरier_call = wext_netdev_notअगरier_call,
पूर्ण;

अटल पूर्णांक __net_init wext_pernet_init(काष्ठा net *net)
अणु
	skb_queue_head_init(&net->wext_nlevents);
	वापस 0;
पूर्ण

अटल व्योम __net_निकास wext_pernet_निकास(काष्ठा net *net)
अणु
	skb_queue_purge(&net->wext_nlevents);
पूर्ण

अटल काष्ठा pernet_operations wext_pernet_ops = अणु
	.init = wext_pernet_init,
	.निकास = wext_pernet_निकास,
पूर्ण;

अटल पूर्णांक __init wireless_nlevent_init(व्योम)
अणु
	पूर्णांक err = रेजिस्टर_pernet_subsys(&wext_pernet_ops);

	अगर (err)
		वापस err;

	err = रेजिस्टर_netdevice_notअगरier(&wext_netdev_notअगरier);
	अगर (err)
		unरेजिस्टर_pernet_subsys(&wext_pernet_ops);
	वापस err;
पूर्ण

subsys_initcall(wireless_nlevent_init);

/* Process events generated by the wireless layer or the driver. */
अटल व्योम wireless_nlevent_process(काष्ठा work_काष्ठा *work)
अणु
	wireless_nlevent_flush();
पूर्ण

अटल DECLARE_WORK(wireless_nlevent_work, wireless_nlevent_process);

अटल काष्ठा nlmsghdr *rtnetlink_अगरinfo_prep(काष्ठा net_device *dev,
					      काष्ठा sk_buff *skb)
अणु
	काष्ठा अगरinfomsg *r;
	काष्ठा nlmsghdr  *nlh;

	nlh = nlmsg_put(skb, 0, 0, RTM_NEWLINK, माप(*r), 0);
	अगर (!nlh)
		वापस शून्य;

	r = nlmsg_data(nlh);
	r->अगरi_family = AF_UNSPEC;
	r->__अगरi_pad = 0;
	r->अगरi_type = dev->type;
	r->अगरi_index = dev->अगरindex;
	r->अगरi_flags = dev_get_flags(dev);
	r->अगरi_change = 0;	/* Wireless changes करोn't affect those flags */

	अगर (nla_put_string(skb, IFLA_IFNAME, dev->name))
		जाओ nla_put_failure;

	वापस nlh;
 nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस शून्य;
पूर्ण


/*
 * Main event dispatcher. Called from other parts and drivers.
 * Send the event on the appropriate channels.
 * May be called from पूर्णांकerrupt context.
 */
व्योम wireless_send_event(काष्ठा net_device *	dev,
			 अचिन्हित पूर्णांक		cmd,
			 जोड़ iwreq_data *	wrqu,
			 स्थिर अक्षर *		extra)
अणु
	स्थिर काष्ठा iw_ioctl_description *	descr = शून्य;
	पूर्णांक extra_len = 0;
	काष्ठा iw_event  *event;		/* Mallocated whole event */
	पूर्णांक event_len;				/* Its size */
	पूर्णांक hdr_len;				/* Size of the event header */
	पूर्णांक wrqu_off = 0;			/* Offset in wrqu */
	/* Don't "optimise" the following variable, it will crash */
	अचिन्हित पूर्णांक	cmd_index;		/* *MUST* be अचिन्हित */
	काष्ठा sk_buff *skb;
	काष्ठा nlmsghdr *nlh;
	काष्ठा nlattr *nla;
#अगर_घोषित CONFIG_COMPAT
	काष्ठा __compat_iw_event *compat_event;
	काष्ठा compat_iw_poपूर्णांक compat_wrqu;
	काष्ठा sk_buff *compskb;
#पूर्ण_अगर

	/*
	 * Nothing in the kernel sends scan events with data, be safe.
	 * This is necessary because we cannot fix up scan event data
	 * क्रम compat, due to being contained in 'extra', but normally
	 * applications are required to retrieve the scan data anyway
	 * and no data is included in the event, this codअगरies that
	 * practice.
	 */
	अगर (WARN_ON(cmd == SIOCGIWSCAN && extra))
		extra = शून्य;

	/* Get the description of the Event */
	अगर (cmd <= SIOCIWLAST) अणु
		cmd_index = IW_IOCTL_IDX(cmd);
		अगर (cmd_index < standard_ioctl_num)
			descr = &(standard_ioctl[cmd_index]);
	पूर्ण अन्यथा अणु
		cmd_index = IW_EVENT_IDX(cmd);
		अगर (cmd_index < standard_event_num)
			descr = &(standard_event[cmd_index]);
	पूर्ण
	/* Don't accept unknown events */
	अगर (descr == शून्य) अणु
		/* Note : we करोn't वापस an error to the driver, because
		 * the driver would not know what to करो about it. It can't
		 * वापस an error to the user, because the event is not
		 * initiated by a user request.
		 * The best the driver could करो is to log an error message.
		 * We will करो it ourselves instead...
		 */
		netdev_err(dev, "(WE) : Invalid/Unknown Wireless Event (0x%04X)\n",
			   cmd);
		वापस;
	पूर्ण

	/* Check extra parameters and set extra_len */
	अगर (descr->header_type == IW_HEADER_TYPE_POINT) अणु
		/* Check अगर number of token fits within bounds */
		अगर (wrqu->data.length > descr->max_tokens) अणु
			netdev_err(dev, "(WE) : Wireless Event (cmd=0x%04X) too big (%d)\n",
				   cmd, wrqu->data.length);
			वापस;
		पूर्ण
		अगर (wrqu->data.length < descr->min_tokens) अणु
			netdev_err(dev, "(WE) : Wireless Event (cmd=0x%04X) too small (%d)\n",
				   cmd, wrqu->data.length);
			वापस;
		पूर्ण
		/* Calculate extra_len - extra is शून्य क्रम restricted events */
		अगर (extra != शून्य)
			extra_len = wrqu->data.length * descr->token_size;
		/* Always at an offset in wrqu */
		wrqu_off = IW_EV_POINT_OFF;
	पूर्ण

	/* Total length of the event */
	hdr_len = event_type_size[descr->header_type];
	event_len = hdr_len + extra_len;

	/*
	 * The problem क्रम 64/32 bit.
	 *
	 * On 64-bit, a regular event is laid out as follows:
	 *      |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
	 *      | event.len | event.cmd |     p a d d i n g     |
	 *      | wrqu data ... (with the correct size)         |
	 *
	 * This padding exists because we manipulate event->u,
	 * and 'event' is not packed.
	 *
	 * An iw_poपूर्णांक event is laid out like this instead:
	 *      |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
	 *      | event.len | event.cmd |     p a d d i n g     |
	 *      | iwpnt.len | iwpnt.flg |     p a d d i n g     |
	 *      | extra data  ...
	 *
	 * The second padding exists because काष्ठा iw_poपूर्णांक is extended,
	 * but this depends on the platक्रमm...
	 *
	 * On 32-bit, all the padding shouldn't be there.
	 */

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	अगर (!skb)
		वापस;

	/* Send via the RtNetlink event channel */
	nlh = rtnetlink_अगरinfo_prep(dev, skb);
	अगर (WARN_ON(!nlh)) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	/* Add the wireless events in the netlink packet */
	nla = nla_reserve(skb, IFLA_WIRELESS, event_len);
	अगर (!nla) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण
	event = nla_data(nla);

	/* Fill event - first clear to aव्योम data leaking */
	स_रखो(event, 0, hdr_len);
	event->len = event_len;
	event->cmd = cmd;
	स_नकल(&event->u, ((अक्षर *) wrqu) + wrqu_off, hdr_len - IW_EV_LCP_LEN);
	अगर (extra_len)
		स_नकल(((अक्षर *) event) + hdr_len, extra, extra_len);

	nlmsg_end(skb, nlh);
#अगर_घोषित CONFIG_COMPAT
	hdr_len = compat_event_type_size[descr->header_type];
	event_len = hdr_len + extra_len;

	compskb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	अगर (!compskb) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	/* Send via the RtNetlink event channel */
	nlh = rtnetlink_अगरinfo_prep(dev, compskb);
	अगर (WARN_ON(!nlh)) अणु
		kमुक्त_skb(skb);
		kमुक्त_skb(compskb);
		वापस;
	पूर्ण

	/* Add the wireless events in the netlink packet */
	nla = nla_reserve(compskb, IFLA_WIRELESS, event_len);
	अगर (!nla) अणु
		kमुक्त_skb(skb);
		kमुक्त_skb(compskb);
		वापस;
	पूर्ण
	compat_event = nla_data(nla);

	compat_event->len = event_len;
	compat_event->cmd = cmd;
	अगर (descr->header_type == IW_HEADER_TYPE_POINT) अणु
		compat_wrqu.length = wrqu->data.length;
		compat_wrqu.flags = wrqu->data.flags;
		स_नकल(&compat_event->poपूर्णांकer,
			((अक्षर *) &compat_wrqu) + IW_EV_COMPAT_POINT_OFF,
			hdr_len - IW_EV_COMPAT_LCP_LEN);
		अगर (extra_len)
			स_नकल(((अक्षर *) compat_event) + hdr_len,
				extra, extra_len);
	पूर्ण अन्यथा अणु
		/* extra_len must be zero, so no अगर (extra) needed */
		स_नकल(&compat_event->poपूर्णांकer, wrqu,
			hdr_len - IW_EV_COMPAT_LCP_LEN);
	पूर्ण

	nlmsg_end(compskb, nlh);

	skb_shinfo(skb)->frag_list = compskb;
#पूर्ण_अगर
	skb_queue_tail(&dev_net(dev)->wext_nlevents, skb);
	schedule_work(&wireless_nlevent_work);
पूर्ण
EXPORT_SYMBOL(wireless_send_event);



/* IW handlers */

काष्ठा iw_statistics *get_wireless_stats(काष्ठा net_device *dev)
अणु
#अगर_घोषित CONFIG_WIRELESS_EXT
	अगर ((dev->wireless_handlers != शून्य) &&
	   (dev->wireless_handlers->get_wireless_stats != शून्य))
		वापस dev->wireless_handlers->get_wireless_stats(dev);
#पूर्ण_अगर

#अगर_घोषित CONFIG_CFG80211_WEXT
	अगर (dev->ieee80211_ptr &&
	    dev->ieee80211_ptr->wiphy &&
	    dev->ieee80211_ptr->wiphy->wext &&
	    dev->ieee80211_ptr->wiphy->wext->get_wireless_stats)
		वापस dev->ieee80211_ptr->wiphy->wext->get_wireless_stats(dev);
#पूर्ण_अगर

	/* not found */
	वापस शून्य;
पूर्ण

/* noअंतरभूत to aव्योम a bogus warning with -O3 */
अटल noअंतरभूत पूर्णांक iw_handler_get_iwstats(काष्ठा net_device *	dev,
				  काष्ठा iw_request_info *	info,
				  जोड़ iwreq_data *		wrqu,
				  अक्षर *			extra)
अणु
	/* Get stats from the driver */
	काष्ठा iw_statistics *stats;

	stats = get_wireless_stats(dev);
	अगर (stats) अणु
		/* Copy statistics to extra */
		स_नकल(extra, stats, माप(काष्ठा iw_statistics));
		wrqu->data.length = माप(काष्ठा iw_statistics);

		/* Check अगर we need to clear the updated flag */
		अगर (wrqu->data.flags != 0)
			stats->qual.updated &= ~IW_QUAL_ALL_UPDATED;
		वापस 0;
	पूर्ण अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण

अटल iw_handler get_handler(काष्ठा net_device *dev, अचिन्हित पूर्णांक cmd)
अणु
	/* Don't "optimise" the following variable, it will crash */
	अचिन्हित पूर्णांक	index;		/* *MUST* be अचिन्हित */
	स्थिर काष्ठा iw_handler_def *handlers = शून्य;

#अगर_घोषित CONFIG_CFG80211_WEXT
	अगर (dev->ieee80211_ptr && dev->ieee80211_ptr->wiphy)
		handlers = dev->ieee80211_ptr->wiphy->wext;
#पूर्ण_अगर
#अगर_घोषित CONFIG_WIRELESS_EXT
	अगर (dev->wireless_handlers)
		handlers = dev->wireless_handlers;
#पूर्ण_अगर

	अगर (!handlers)
		वापस शून्य;

	/* Try as a standard command */
	index = IW_IOCTL_IDX(cmd);
	अगर (index < handlers->num_standard)
		वापस handlers->standard[index];

#अगर_घोषित CONFIG_WEXT_PRIV
	/* Try as a निजी command */
	index = cmd - SIOCIWFIRSTPRIV;
	अगर (index < handlers->num_निजी)
		वापस handlers->निजी[index];
#पूर्ण_अगर

	/* Not found */
	वापस शून्य;
पूर्ण

अटल पूर्णांक ioctl_standard_iw_poपूर्णांक(काष्ठा iw_poपूर्णांक *iwp, अचिन्हित पूर्णांक cmd,
				   स्थिर काष्ठा iw_ioctl_description *descr,
				   iw_handler handler, काष्ठा net_device *dev,
				   काष्ठा iw_request_info *info)
अणु
	पूर्णांक err, extra_size, user_length = 0, essid_compat = 0;
	अक्षर *extra;

	/* Calculate space needed by arguments. Always allocate
	 * क्रम max space.
	 */
	extra_size = descr->max_tokens * descr->token_size;

	/* Check need क्रम ESSID compatibility क्रम WE < 21 */
	चयन (cmd) अणु
	हाल SIOCSIWESSID:
	हाल SIOCGIWESSID:
	हाल SIOCSIWNICKN:
	हाल SIOCGIWNICKN:
		अगर (iwp->length == descr->max_tokens + 1)
			essid_compat = 1;
		अन्यथा अगर (IW_IS_SET(cmd) && (iwp->length != 0)) अणु
			अक्षर essid[IW_ESSID_MAX_SIZE + 1];
			अचिन्हित पूर्णांक len;
			len = iwp->length * descr->token_size;

			अगर (len > IW_ESSID_MAX_SIZE)
				वापस -EFAULT;

			err = copy_from_user(essid, iwp->poपूर्णांकer, len);
			अगर (err)
				वापस -EFAULT;

			अगर (essid[iwp->length - 1] == '\0')
				essid_compat = 1;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	iwp->length -= essid_compat;

	/* Check what user space is giving us */
	अगर (IW_IS_SET(cmd)) अणु
		/* Check शून्य poपूर्णांकer */
		अगर (!iwp->poपूर्णांकer && iwp->length != 0)
			वापस -EFAULT;
		/* Check अगर number of token fits within bounds */
		अगर (iwp->length > descr->max_tokens)
			वापस -E2BIG;
		अगर (iwp->length < descr->min_tokens)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* Check शून्य poपूर्णांकer */
		अगर (!iwp->poपूर्णांकer)
			वापस -EFAULT;
		/* Save user space buffer size क्रम checking */
		user_length = iwp->length;

		/* Don't check अगर user_length > max to allow क्रमward
		 * compatibility. The test user_length < min is
		 * implied by the test at the end.
		 */

		/* Support क्रम very large requests */
		अगर ((descr->flags & IW_DESCR_FLAG_NOMAX) &&
		    (user_length > descr->max_tokens)) अणु
			/* Allow userspace to GET more than max so
			 * we can support any size GET requests.
			 * There is still a limit : -ENOMEM.
			 */
			extra_size = user_length * descr->token_size;

			/* Note : user_length is originally a __u16,
			 * and token_size is controlled by us,
			 * so extra_size won't get negative and
			 * won't overflow...
			 */
		पूर्ण
	पूर्ण

	/* kzalloc() ensures शून्य-termination क्रम essid_compat. */
	extra = kzalloc(extra_size, GFP_KERNEL);
	अगर (!extra)
		वापस -ENOMEM;

	/* If it is a SET, get all the extra data in here */
	अगर (IW_IS_SET(cmd) && (iwp->length != 0)) अणु
		अगर (copy_from_user(extra, iwp->poपूर्णांकer,
				   iwp->length *
				   descr->token_size)) अणु
			err = -EFAULT;
			जाओ out;
		पूर्ण

		अगर (cmd == SIOCSIWENCODEEXT) अणु
			काष्ठा iw_encode_ext *ee = (व्योम *) extra;

			अगर (iwp->length < माप(*ee) + ee->key_len) अणु
				err = -EFAULT;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (IW_IS_GET(cmd) && !(descr->flags & IW_DESCR_FLAG_NOMAX)) अणु
		/*
		 * If this is a GET, but not NOMAX, it means that the extra
		 * data is not bounded by userspace, but by max_tokens. Thus
		 * set the length to max_tokens. This matches the extra data
		 * allocation.
		 * The driver should fill it with the number of tokens it
		 * provided, and it may check iwp->length rather than having
		 * knowledge of max_tokens. If the driver करोesn't change the
		 * iwp->length, this ioctl just copies back max_token tokens
		 * filled with zeroes. Hopefully the driver isn't claiming
		 * them to be valid data.
		 */
		iwp->length = descr->max_tokens;
	पूर्ण

	err = handler(dev, info, (जोड़ iwreq_data *) iwp, extra);

	iwp->length += essid_compat;

	/* If we have something to वापस to the user */
	अगर (!err && IW_IS_GET(cmd)) अणु
		/* Check अगर there is enough buffer up there */
		अगर (user_length < iwp->length) अणु
			err = -E2BIG;
			जाओ out;
		पूर्ण

		अगर (copy_to_user(iwp->poपूर्णांकer, extra,
				 iwp->length *
				 descr->token_size)) अणु
			err = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Generate an event to notअगरy listeners of the change */
	अगर ((descr->flags & IW_DESCR_FLAG_EVENT) &&
	    ((err == 0) || (err == -EIWCOMMIT))) अणु
		जोड़ iwreq_data *data = (जोड़ iwreq_data *) iwp;

		अगर (descr->flags & IW_DESCR_FLAG_RESTRICT)
			/* If the event is restricted, करोn't
			 * export the payload.
			 */
			wireless_send_event(dev, cmd, data, शून्य);
		अन्यथा
			wireless_send_event(dev, cmd, data, extra);
	पूर्ण

out:
	kमुक्त(extra);
	वापस err;
पूर्ण

/*
 * Call the commit handler in the driver
 * (अगर exist and अगर conditions are right)
 *
 * Note : our current commit strategy is currently pretty dumb,
 * but we will be able to improve on that...
 * The goal is to try to agreagate as many changes as possible
 * beक्रमe करोing the commit. Drivers that will define a commit handler
 * are usually those that need a reset after changing parameters, so
 * we want to minimise the number of reset.
 * A cool idea is to use a समयr : at each "set" command, we re-set the
 * समयr, when the समयr eventually fires, we call the driver.
 * Hopefully, more on that later.
 *
 * Also, I'm रुकोing to see how many people will complain about the
 * netअगर_running(dev) test. I'm खोलो on that one...
 * Hopefully, the driver will remember to करो a commit in "open()" ;-)
 */
पूर्णांक call_commit_handler(काष्ठा net_device *dev)
अणु
#अगर_घोषित CONFIG_WIRELESS_EXT
	अगर (netअगर_running(dev) &&
	    dev->wireless_handlers &&
	    dev->wireless_handlers->standard[0])
		/* Call the commit handler on the driver */
		वापस dev->wireless_handlers->standard[0](dev, शून्य,
							   शून्य, शून्य);
	अन्यथा
		वापस 0;		/* Command completed successfully */
#अन्यथा
	/* cfg80211 has no commit */
	वापस 0;
#पूर्ण_अगर
पूर्ण

/*
 * Main IOCTl dispatcher.
 * Check the type of IOCTL and call the appropriate wrapper...
 */
अटल पूर्णांक wireless_process_ioctl(काष्ठा net *net, काष्ठा iwreq *iwr,
				  अचिन्हित पूर्णांक cmd,
				  काष्ठा iw_request_info *info,
				  wext_ioctl_func standard,
				  wext_ioctl_func निजी)
अणु
	काष्ठा net_device *dev;
	iw_handler	handler;

	/* Permissions are alपढ़ोy checked in dev_ioctl() beक्रमe calling us.
	 * The copy_to/from_user() of अगरr is also dealt with in there */

	/* Make sure the device exist */
	अगर ((dev = __dev_get_by_name(net, iwr->अगरr_name)) == शून्य)
		वापस -ENODEV;

	/* A bunch of special हालs, then the generic हाल...
	 * Note that 'cmd' is alपढ़ोy filtered in dev_ioctl() with
	 * (cmd >= SIOCIWFIRST && cmd <= SIOCIWLAST) */
	अगर (cmd == SIOCGIWSTATS)
		वापस standard(dev, iwr, cmd, info,
				&iw_handler_get_iwstats);

#अगर_घोषित CONFIG_WEXT_PRIV
	अगर (cmd == SIOCGIWPRIV && dev->wireless_handlers)
		वापस standard(dev, iwr, cmd, info,
				iw_handler_get_निजी);
#पूर्ण_अगर

	/* Basic check */
	अगर (!netअगर_device_present(dev))
		वापस -ENODEV;

	/* New driver API : try to find the handler */
	handler = get_handler(dev, cmd);
	अगर (handler) अणु
		/* Standard and निजी are not the same */
		अगर (cmd < SIOCIWFIRSTPRIV)
			वापस standard(dev, iwr, cmd, info, handler);
		अन्यथा अगर (निजी)
			वापस निजी(dev, iwr, cmd, info, handler);
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

/* If command is `set a parameter', or `get the encoding parameters',
 * check अगर the user has the right to करो it.
 */
अटल पूर्णांक wext_permission_check(अचिन्हित पूर्णांक cmd)
अणु
	अगर ((IW_IS_SET(cmd) || cmd == SIOCGIWENCODE ||
	     cmd == SIOCGIWENCODEEXT) &&
	    !capable(CAP_NET_ADMIN))
		वापस -EPERM;

	वापस 0;
पूर्ण

/* entry poपूर्णांक from dev ioctl */
अटल पूर्णांक wext_ioctl_dispatch(काष्ठा net *net, काष्ठा iwreq *iwr,
			       अचिन्हित पूर्णांक cmd, काष्ठा iw_request_info *info,
			       wext_ioctl_func standard,
			       wext_ioctl_func निजी)
अणु
	पूर्णांक ret = wext_permission_check(cmd);

	अगर (ret)
		वापस ret;

	dev_load(net, iwr->अगरr_name);
	rtnl_lock();
	ret = wireless_process_ioctl(net, iwr, cmd, info, standard, निजी);
	rtnl_unlock();

	वापस ret;
पूर्ण

/*
 * Wrapper to call a standard Wireless Extension handler.
 * We करो various checks and also take care of moving data between
 * user space and kernel space.
 */
अटल पूर्णांक ioctl_standard_call(काष्ठा net_device *	dev,
			       काष्ठा iwreq		*iwr,
			       अचिन्हित पूर्णांक		cmd,
			       काष्ठा iw_request_info	*info,
			       iw_handler		handler)
अणु
	स्थिर काष्ठा iw_ioctl_description *	descr;
	पूर्णांक					ret = -EINVAL;

	/* Get the description of the IOCTL */
	अगर (IW_IOCTL_IDX(cmd) >= standard_ioctl_num)
		वापस -EOPNOTSUPP;
	descr = &(standard_ioctl[IW_IOCTL_IDX(cmd)]);

	/* Check अगर we have a poपूर्णांकer to user space data or not */
	अगर (descr->header_type != IW_HEADER_TYPE_POINT) अणु

		/* No extra arguments. Trivial to handle */
		ret = handler(dev, info, &(iwr->u), शून्य);

		/* Generate an event to notअगरy listeners of the change */
		अगर ((descr->flags & IW_DESCR_FLAG_EVENT) &&
		   ((ret == 0) || (ret == -EIWCOMMIT)))
			wireless_send_event(dev, cmd, &(iwr->u), शून्य);
	पूर्ण अन्यथा अणु
		ret = ioctl_standard_iw_poपूर्णांक(&iwr->u.data, cmd, descr,
					      handler, dev, info);
	पूर्ण

	/* Call commit handler अगर needed and defined */
	अगर (ret == -EIWCOMMIT)
		ret = call_commit_handler(dev);

	/* Here, we will generate the appropriate event अगर needed */

	वापस ret;
पूर्ण


पूर्णांक wext_handle_ioctl(काष्ठा net *net, अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	काष्ठा iw_request_info info = अणु .cmd = cmd, .flags = 0 पूर्ण;
	काष्ठा iwreq iwr;
	पूर्णांक ret;

	अगर (copy_from_user(&iwr, arg, माप(iwr)))
		वापस -EFAULT;

	iwr.अगरr_name[माप(iwr.अगरr_name) - 1] = 0;

	ret = wext_ioctl_dispatch(net, &iwr, cmd, &info,
				  ioctl_standard_call,
				  ioctl_निजी_call);
	अगर (ret >= 0 &&
	    IW_IS_GET(cmd) &&
	    copy_to_user(arg, &iwr, माप(काष्ठा iwreq)))
		वापस -EFAULT;

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक compat_standard_call(काष्ठा net_device	*dev,
				काष्ठा iwreq		*iwr,
				अचिन्हित पूर्णांक		cmd,
				काष्ठा iw_request_info	*info,
				iw_handler		handler)
अणु
	स्थिर काष्ठा iw_ioctl_description *descr;
	काष्ठा compat_iw_poपूर्णांक *iwp_compat;
	काष्ठा iw_poपूर्णांक iwp;
	पूर्णांक err;

	descr = standard_ioctl + IW_IOCTL_IDX(cmd);

	अगर (descr->header_type != IW_HEADER_TYPE_POINT)
		वापस ioctl_standard_call(dev, iwr, cmd, info, handler);

	iwp_compat = (काष्ठा compat_iw_poपूर्णांक *) &iwr->u.data;
	iwp.poपूर्णांकer = compat_ptr(iwp_compat->poपूर्णांकer);
	iwp.length = iwp_compat->length;
	iwp.flags = iwp_compat->flags;

	err = ioctl_standard_iw_poपूर्णांक(&iwp, cmd, descr, handler, dev, info);

	iwp_compat->poपूर्णांकer = ptr_to_compat(iwp.poपूर्णांकer);
	iwp_compat->length = iwp.length;
	iwp_compat->flags = iwp.flags;

	वापस err;
पूर्ण

पूर्णांक compat_wext_handle_ioctl(काष्ठा net *net, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा iw_request_info info;
	काष्ठा iwreq iwr;
	अक्षर *colon;
	पूर्णांक ret;

	अगर (copy_from_user(&iwr, argp, माप(काष्ठा iwreq)))
		वापस -EFAULT;

	iwr.अगरr_name[IFNAMSIZ-1] = 0;
	colon = म_अक्षर(iwr.अगरr_name, ':');
	अगर (colon)
		*colon = 0;

	info.cmd = cmd;
	info.flags = IW_REQUEST_FLAG_COMPAT;

	ret = wext_ioctl_dispatch(net, &iwr, cmd, &info,
				  compat_standard_call,
				  compat_निजी_call);

	अगर (ret >= 0 &&
	    IW_IS_GET(cmd) &&
	    copy_to_user(argp, &iwr, माप(काष्ठा iwreq)))
		वापस -EFAULT;

	वापस ret;
पूर्ण
#पूर्ण_अगर

अक्षर *iwe_stream_add_event(काष्ठा iw_request_info *info, अक्षर *stream,
			   अक्षर *ends, काष्ठा iw_event *iwe, पूर्णांक event_len)
अणु
	पूर्णांक lcp_len = iwe_stream_lcp_len(info);

	event_len = iwe_stream_event_len_adjust(info, event_len);

	/* Check अगर it's possible */
	अगर (likely((stream + event_len) < ends)) अणु
		iwe->len = event_len;
		/* Beware of alignement issues on 64 bits */
		स_नकल(stream, (अक्षर *) iwe, IW_EV_LCP_PK_LEN);
		स_नकल(stream + lcp_len, &iwe->u,
		       event_len - lcp_len);
		stream += event_len;
	पूर्ण

	वापस stream;
पूर्ण
EXPORT_SYMBOL(iwe_stream_add_event);

अक्षर *iwe_stream_add_poपूर्णांक(काष्ठा iw_request_info *info, अक्षर *stream,
			   अक्षर *ends, काष्ठा iw_event *iwe, अक्षर *extra)
अणु
	पूर्णांक event_len = iwe_stream_poपूर्णांक_len(info) + iwe->u.data.length;
	पूर्णांक poपूर्णांक_len = iwe_stream_poपूर्णांक_len(info);
	पूर्णांक lcp_len   = iwe_stream_lcp_len(info);

	/* Check अगर it's possible */
	अगर (likely((stream + event_len) < ends)) अणु
		iwe->len = event_len;
		स_नकल(stream, (अक्षर *) iwe, IW_EV_LCP_PK_LEN);
		स_नकल(stream + lcp_len,
		       ((अक्षर *) &iwe->u) + IW_EV_POINT_OFF,
		       IW_EV_POINT_PK_LEN - IW_EV_LCP_PK_LEN);
		अगर (iwe->u.data.length && extra)
			स_नकल(stream + poपूर्णांक_len, extra, iwe->u.data.length);
		stream += event_len;
	पूर्ण

	वापस stream;
पूर्ण
EXPORT_SYMBOL(iwe_stream_add_poपूर्णांक);

अक्षर *iwe_stream_add_value(काष्ठा iw_request_info *info, अक्षर *event,
			   अक्षर *value, अक्षर *ends, काष्ठा iw_event *iwe,
			   पूर्णांक event_len)
अणु
	पूर्णांक lcp_len = iwe_stream_lcp_len(info);

	/* Don't duplicate LCP */
	event_len -= IW_EV_LCP_LEN;

	/* Check अगर it's possible */
	अगर (likely((value + event_len) < ends)) अणु
		/* Add new value */
		स_नकल(value, &iwe->u, event_len);
		value += event_len;
		/* Patch LCP */
		iwe->len = value - event;
		स_नकल(event, (अक्षर *) iwe, lcp_len);
	पूर्ण

	वापस value;
पूर्ण
EXPORT_SYMBOL(iwe_stream_add_value);
