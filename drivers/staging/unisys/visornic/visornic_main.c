<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2012 - 2015 UNISYS CORPORATION
 * All rights reserved.
 */

/* This driver lives in a spar partition, and रेजिस्टरs to ethernet io
 * channels from the visorbus driver. It creates netdev devices and
 * क्रमwards transmit to the IO channel and accepts rcvs from the IO
 * Partition via the IO channel.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/visorbus.h>

#समावेश "iochannel.h"

#घोषणा VISORNIC_INFINITE_RSP_WAIT 0

/* MAX_BUF = 64 lines x 32 MAXVNIC x 80 अक्षरacters
 *         = 163840 bytes
 */
#घोषणा MAX_BUF 163840
#घोषणा NAPI_WEIGHT 64

/* GUIDS क्रम director channel type supported by this driver.  */
/* अणु8cd5994d-c58e-11da-95a9-00e08161165fपूर्ण */
#घोषणा VISOR_VNIC_CHANNEL_GUID \
	GUID_INIT(0x8cd5994d, 0xc58e, 0x11da, \
		0x95, 0xa9, 0x0, 0xe0, 0x81, 0x61, 0x16, 0x5f)
#घोषणा VISOR_VNIC_CHANNEL_GUID_STR \
	"8cd5994d-c58e-11da-95a9-00e08161165f"

अटल काष्ठा visor_channeltype_descriptor visornic_channel_types[] = अणु
	/* Note that the only channel type we expect to be reported by the
	 * bus driver is the VISOR_VNIC channel.
	 */
	अणु VISOR_VNIC_CHANNEL_GUID, "ultravnic", माप(काष्ठा channel_header),
	  VISOR_VNIC_CHANNEL_VERSIONID पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(visorbus, visornic_channel_types);
/* FIXME XXX: This next line of code must be fixed and हटाओd beक्रमe
 * acceptance पूर्णांकo the 'normal' part of the kernel.  It is only here as a place
 * holder to get module स्वतःloading functionality working क्रम visorbus.  Code
 * must be added to scripts/mode/file2alias.c, etc., to get this working
 * properly.
 */
MODULE_ALIAS("visorbus:" VISOR_VNIC_CHANNEL_GUID_STR);

काष्ठा chanstat अणु
	अचिन्हित दीर्घ got_rcv;
	अचिन्हित दीर्घ got_enbdisack;
	अचिन्हित दीर्घ got_xmit_करोne;
	अचिन्हित दीर्घ xmit_fail;
	अचिन्हित दीर्घ sent_enbdis;
	अचिन्हित दीर्घ sent_promisc;
	अचिन्हित दीर्घ sent_post;
	अचिन्हित दीर्घ sent_post_failed;
	अचिन्हित दीर्घ sent_xmit;
	अचिन्हित दीर्घ reject_count;
	अचिन्हित दीर्घ extra_rcvbufs_sent;
पूर्ण;

/* काष्ठा visornic_devdata
 * @enabled:                        0 disabled 1 enabled to receive.
 * @enab_dis_acked:                 NET_RCV_ENABLE/DISABLE acked by IOPART.
 * @काष्ठा *dev:
 * @काष्ठा *netdev:
 * @काष्ठा net_stats:
 * @पूर्णांकerrupt_rcvd:
 * @rsp_queue:
 * @काष्ठा **rcvbuf:
 * @incarnation_id:                 incarnation_id lets IOPART know about
 *                                  re-birth.
 * @old_flags:                      flags as they were prior to
 *                                  set_multicast_list.
 * @usage:                          count of users.
 * @num_rcv_bufs:                   number of rcv buffers the vnic will post.
 * @num_rcv_bufs_could_not_alloc:
 * @num_rcvbuf_in_iovm:
 * @alloc_failed_in_अगर_needed_cnt:
 * @alloc_failed_in_repost_rtn_cnt:
 * @max_outstanding_net_xmits:      असलolute max number of outstanding xmits
 *                                  - should never hit this.
 * @upper_threshold_net_xmits:      high water mark क्रम calling
 *                                  netअगर_stop_queue().
 * @lower_threshold_net_xmits:      high water mark क्रम calling
 *                                  netअगर_wake_queue().
 * @काष्ठा xmitbufhead:             xmitbufhead - head of the xmit buffer list
 *                                  sent to the IOPART end.
 * @server_करोwn_complete_func:
 * @काष्ठा समयout_reset:
 * @काष्ठा *cmdrsp_rcv:             cmdrsp_rcv is used क्रम posting/unposting rcv
 *                                  buffers.
 * @काष्ठा *xmit_cmdrsp:            xmit_cmdrsp - issues NET_XMIT - only one
 *                                  active xmit at a समय.
 * @server_करोwn:                    IOPART is करोwn.
 * @server_change_state:            Processing SERVER_CHANGESTATE msg.
 * @going_away:                     device is being torn करोwn.
 * @काष्ठा *eth_debugfs_dir:
 * @पूर्णांकerrupts_rcvd:
 * @पूर्णांकerrupts_noपंचांगe:
 * @पूर्णांकerrupts_disabled:
 * @busy_cnt:
 * @priv_lock:                      spinlock to access devdata काष्ठाures.
 * @flow_control_upper_hits:
 * @flow_control_lower_hits:
 * @n_rcv0:                         # rcvs of 0 buffers.
 * @n_rcv1:                         # rcvs of 1 buffers.
 * @n_rcv2:                         # rcvs of 2 buffers.
 * @n_rcvx:                         # rcvs of >2 buffers.
 * @found_repost_rcvbuf_cnt:        # repost_rcvbuf_cnt.
 * @repost_found_skb_cnt:           # of found the skb.
 * @n_repost_deficit:               # of lost rcv buffers.
 * @bad_rcv_buf:                    # of unknown rcv skb not मुक्तd.
 * @n_rcv_packets_not_accepted:     # bogs rcv packets.
 * @queuefullmsg_logged:
 * @काष्ठा chstat:
 * @काष्ठा napi:
 * @काष्ठा cmdrsp:
 */
काष्ठा visornic_devdata अणु
	अचिन्हित लघु enabled;
	अचिन्हित लघु enab_dis_acked;

	काष्ठा visor_device *dev;
	काष्ठा net_device *netdev;
	काष्ठा net_device_stats net_stats;
	atomic_t पूर्णांकerrupt_rcvd;
	रुको_queue_head_t rsp_queue;
	काष्ठा sk_buff **rcvbuf;
	u64 incarnation_id;
	अचिन्हित लघु old_flags;
	atomic_t usage;

	पूर्णांक num_rcv_bufs;
	पूर्णांक num_rcv_bufs_could_not_alloc;
	atomic_t num_rcvbuf_in_iovm;
	अचिन्हित दीर्घ alloc_failed_in_अगर_needed_cnt;
	अचिन्हित दीर्घ alloc_failed_in_repost_rtn_cnt;

	अचिन्हित दीर्घ max_outstanding_net_xmits;
	अचिन्हित दीर्घ upper_threshold_net_xmits;
	अचिन्हित दीर्घ lower_threshold_net_xmits;
	काष्ठा sk_buff_head xmitbufhead;

	visorbus_state_complete_func server_करोwn_complete_func;
	काष्ठा work_काष्ठा समयout_reset;
	काष्ठा uiscmdrsp *cmdrsp_rcv;
	काष्ठा uiscmdrsp *xmit_cmdrsp;
	bool server_करोwn;
	bool server_change_state;
	bool going_away;
	काष्ठा dentry *eth_debugfs_dir;
	u64 पूर्णांकerrupts_rcvd;
	u64 पूर्णांकerrupts_noपंचांगe;
	u64 पूर्णांकerrupts_disabled;
	u64 busy_cnt;
	/* spinlock to access devdata काष्ठाures. */
	spinlock_t priv_lock;

	/* flow control counter */
	u64 flow_control_upper_hits;
	u64 flow_control_lower_hits;

	/* debug counters */
	अचिन्हित दीर्घ n_rcv0;
	अचिन्हित दीर्घ n_rcv1;
	अचिन्हित दीर्घ n_rcv2;
	अचिन्हित दीर्घ n_rcvx;
	अचिन्हित दीर्घ found_repost_rcvbuf_cnt;
	अचिन्हित दीर्घ repost_found_skb_cnt;
	अचिन्हित दीर्घ n_repost_deficit;
	अचिन्हित दीर्घ bad_rcv_buf;
	अचिन्हित दीर्घ n_rcv_packets_not_accepted;

	पूर्णांक queuefullmsg_logged;
	काष्ठा chanstat chstat;
	काष्ठा napi_काष्ठा napi;
	काष्ठा uiscmdrsp cmdrsp[SIZखातापूर्ण_CMDRSP];
पूर्ण;

/* Returns next non-zero index on success or 0 on failure (i.e. out of room). */
अटल u16 add_physinfo_entries(u64 inp_pfn, u16 inp_off, u16 inp_len,
				u16 index, u16 max_pi_arr_entries,
				काष्ठा phys_info pi_arr[])
अणु
	u16 i, len, firstlen;

	firstlen = PI_PAGE_SIZE - inp_off;
	अगर (inp_len <= firstlen) अणु
		/* The input entry spans only one page - add as is. */
		अगर (index >= max_pi_arr_entries)
			वापस 0;
		pi_arr[index].pi_pfn = inp_pfn;
		pi_arr[index].pi_off = (u16)inp_off;
		pi_arr[index].pi_len = (u16)inp_len;
		वापस index + 1;
	पूर्ण

	/* This entry spans multiple pages. */
	क्रम (len = inp_len, i = 0; len;
		len -= pi_arr[index + i].pi_len, i++) अणु
		अगर (index + i >= max_pi_arr_entries)
			वापस 0;
		pi_arr[index + i].pi_pfn = inp_pfn + i;
		अगर (i == 0) अणु
			pi_arr[index].pi_off = inp_off;
			pi_arr[index].pi_len = firstlen;
		पूर्ण अन्यथा अणु
			pi_arr[index + i].pi_off = 0;
			pi_arr[index + i].pi_len = min_t(u16, len,
							 PI_PAGE_SIZE);
		पूर्ण
	पूर्ण
	वापस index + i;
पूर्ण

/* visor_copy_fragsinfo_from_skb - copy fragment list in the SKB to a phys_info
 *				   array that the IOPART understands
 * @skb:	  Skbuff that we are pulling the frags from.
 * @firstfraglen: Length of first fragment in skb.
 * @frags_max:	  Max len of frags array.
 * @frags:	  Frags array filled in on output.
 *
 * Return: Positive पूर्णांकeger indicating number of entries filled in frags on
 *         success, negative पूर्णांकeger on error.
 */
अटल पूर्णांक visor_copy_fragsinfo_from_skb(काष्ठा sk_buff *skb,
					 अचिन्हित पूर्णांक firstfraglen,
					 अचिन्हित पूर्णांक frags_max,
					 काष्ठा phys_info frags[])
अणु
	अचिन्हित पूर्णांक count = 0, frag, size, offset = 0, numfrags;
	अचिन्हित पूर्णांक total_count;

	numfrags = skb_shinfo(skb)->nr_frags;

	/* Compute the number of fragments this skb has, and अगर its more than
	 * frag array can hold, linearize the skb
	 */
	total_count = numfrags + (firstfraglen / PI_PAGE_SIZE);
	अगर (firstfraglen % PI_PAGE_SIZE)
		total_count++;

	अगर (total_count > frags_max) अणु
		अगर (skb_linearize(skb))
			वापस -EINVAL;
		numfrags = skb_shinfo(skb)->nr_frags;
		firstfraglen = 0;
	पूर्ण

	जबतक (firstfraglen) अणु
		अगर (count == frags_max)
			वापस -EINVAL;

		frags[count].pi_pfn =
			page_to_pfn(virt_to_page(skb->data + offset));
		frags[count].pi_off =
			(अचिन्हित दीर्घ)(skb->data + offset) & PI_PAGE_MASK;
		size = min_t(अचिन्हित पूर्णांक, firstfraglen,
			     PI_PAGE_SIZE - frags[count].pi_off);

		/* can take smallest of firstfraglen (what's left) OR
		 * bytes left in the page
		 */
		frags[count].pi_len = size;
		firstfraglen -= size;
		offset += size;
		count++;
	पूर्ण
	अगर (numfrags) अणु
		अगर ((count + numfrags) > frags_max)
			वापस -EINVAL;

		क्रम (frag = 0; frag < numfrags; frag++) अणु
			count = add_physinfo_entries(page_to_pfn(
				  skb_frag_page(&skb_shinfo(skb)->frags[frag])),
				  skb_frag_off(&skb_shinfo(skb)->frags[frag]),
				  skb_frag_size(&skb_shinfo(skb)->frags[frag]),
				  count, frags_max, frags);
			/* add_physinfo_entries only वापसs
			 * zero अगर the frags array is out of room
			 * That should never happen because we
			 * fail above, अगर count+numfrags > frags_max.
			 */
			अगर (!count)
				वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (skb_shinfo(skb)->frag_list) अणु
		काष्ठा sk_buff *skbinlist;
		पूर्णांक c;

		क्रम (skbinlist = skb_shinfo(skb)->frag_list; skbinlist;
		     skbinlist = skbinlist->next) अणु
			c = visor_copy_fragsinfo_from_skb(skbinlist,
							  skbinlist->len -
							  skbinlist->data_len,
							  frags_max - count,
							  &frags[count]);
			अगर (c < 0)
				वापस c;
			count += c;
		पूर्ण
	पूर्ण
	वापस count;
पूर्ण

अटल sमाप_प्रकार enable_पूर्णांकs_ग_लिखो(काष्ठा file *file,
				 स्थिर अक्षर __user *buffer,
				 माप_प्रकार count, loff_t *ppos)
अणु
	/* Don't want to अवरोध ABI here by having a debugfs
	 * file that no दीर्घer exists or is writable, so
	 * lets just make this a vestigual function
	 */
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_enable_पूर्णांकs_fops = अणु
	.ग_लिखो = enable_पूर्णांकs_ग_लिखो,
पूर्ण;

/* visornic_serverकरोwn_complete - छोड़ो device following IOPART going करोwn
 * @devdata: Device managed by IOPART.
 *
 * The IO partition has gone करोwn, and we need to करो some cleanup क्रम when it
 * comes back. Treat the IO partition as the link being करोwn.
 */
अटल व्योम visornic_serverकरोwn_complete(काष्ठा visornic_devdata *devdata)
अणु
	काष्ठा net_device *netdev = devdata->netdev;

	/* Stop polling क्रम पूर्णांकerrupts */
	visorbus_disable_channel_पूर्णांकerrupts(devdata->dev);

	rtnl_lock();
	dev_बंद(netdev);
	rtnl_unlock();

	atomic_set(&devdata->num_rcvbuf_in_iovm, 0);
	devdata->chstat.sent_xmit = 0;
	devdata->chstat.got_xmit_करोne = 0;

	अगर (devdata->server_करोwn_complete_func)
		(*devdata->server_करोwn_complete_func)(devdata->dev, 0);

	devdata->server_करोwn = true;
	devdata->server_change_state = false;
	devdata->server_करोwn_complete_func = शून्य;
पूर्ण

/* visornic_serverकरोwn - Command has notअगरied us that IOPART is करोwn
 * @devdata:	   Device managed by IOPART.
 * @complete_func: Function to call when finished.
 *
 * Schedule the work needed to handle the server करोwn request. Make sure we
 * haven't alपढ़ोy handled the server change state event.
 *
 * Return: 0 अगर we scheduled the work, negative पूर्णांकeger on error.
 */
अटल पूर्णांक visornic_serverकरोwn(काष्ठा visornic_devdata *devdata,
			       visorbus_state_complete_func complete_func)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&devdata->priv_lock, flags);
	अगर (devdata->server_change_state) अणु
		dev_dbg(&devdata->dev->device, "%s changing state\n",
			__func__);
		err = -EINVAL;
		जाओ err_unlock;
	पूर्ण
	अगर (devdata->server_करोwn) अणु
		dev_dbg(&devdata->dev->device, "%s already down\n",
			__func__);
		err = -EINVAL;
		जाओ err_unlock;
	पूर्ण
	अगर (devdata->going_away) अणु
		dev_dbg(&devdata->dev->device,
			"%s aborting because device removal pending\n",
			__func__);
		err = -ENODEV;
		जाओ err_unlock;
	पूर्ण
	devdata->server_change_state = true;
	devdata->server_करोwn_complete_func = complete_func;
	spin_unlock_irqrestore(&devdata->priv_lock, flags);

	visornic_serverकरोwn_complete(devdata);
	वापस 0;

err_unlock:
	spin_unlock_irqrestore(&devdata->priv_lock, flags);
	वापस err;
पूर्ण

/* alloc_rcv_buf - alloc rcv buffer to be given to the IO Partition
 * @netdev: Network adapter the rcv bufs are attached too.
 *
 * Create an sk_buff (rcv_buf) that will be passed to the IO Partition
 * so that it can ग_लिखो rcv data पूर्णांकo our memory space.
 *
 * Return: Poपूर्णांकer to sk_buff.
 */
अटल काष्ठा sk_buff *alloc_rcv_buf(काष्ठा net_device *netdev)
अणु
	काष्ठा sk_buff *skb;

	/* NOTE: the first fragment in each rcv buffer is poपूर्णांकed to by
	 * rcvskb->data. For now all rcv buffers will be RCVPOST_BUF_SIZE
	 * in length, so the first frag is large enough to hold 1514.
	 */
	skb = alloc_skb(RCVPOST_BUF_SIZE, GFP_ATOMIC);
	अगर (!skb)
		वापस शून्य;
	skb->dev = netdev;
	/* current value of mtu करोesn't come पूर्णांकo play here; large
	 * packets will just end up using multiple rcv buffers all of
	 * same size.
	 */
	skb->len = RCVPOST_BUF_SIZE;
	/* alloc_skb alपढ़ोy zeroes it out क्रम clarअगरication. */
	skb->data_len = 0;
	वापस skb;
पूर्ण

/* post_skb - post a skb to the IO Partition
 * @cmdrsp:  Cmdrsp packet to be send to the IO Partition.
 * @devdata: visornic_devdata to post the skb to.
 * @skb:     Skb to give to the IO partition.
 *
 * Return: 0 on success, negative पूर्णांकeger on error.
 */
अटल पूर्णांक post_skb(काष्ठा uiscmdrsp *cmdrsp, काष्ठा visornic_devdata *devdata,
		    काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	cmdrsp->net.buf = skb;
	cmdrsp->net.rcvpost.frag.pi_pfn = page_to_pfn(virt_to_page(skb->data));
	cmdrsp->net.rcvpost.frag.pi_off =
		(अचिन्हित दीर्घ)skb->data & PI_PAGE_MASK;
	cmdrsp->net.rcvpost.frag.pi_len = skb->len;
	cmdrsp->net.rcvpost.unique_num = devdata->incarnation_id;

	अगर ((cmdrsp->net.rcvpost.frag.pi_off + skb->len) > PI_PAGE_SIZE)
		वापस -EINVAL;

	cmdrsp->net.type = NET_RCV_POST;
	cmdrsp->cmdtype = CMD_NET_TYPE;
	err = visorchannel_संकेतinsert(devdata->dev->visorchannel,
					IOCHAN_TO_IOPART,
					cmdrsp);
	अगर (err) अणु
		devdata->chstat.sent_post_failed++;
		वापस err;
	पूर्ण

	atomic_inc(&devdata->num_rcvbuf_in_iovm);
	devdata->chstat.sent_post++;
	वापस 0;
पूर्ण

/* send_enbdis - Send NET_RCV_ENBDIS to IO Partition
 * @netdev:  Netdevice we are enabling/disabling, used as context वापस value.
 * @state:   Enable = 1/disable = 0.
 * @devdata: Visornic device we are enabling/disabling.
 *
 * Send the enable/disable message to the IO Partition.
 *
 * Return: 0 on success, negative पूर्णांकeger on error.
 */
अटल पूर्णांक send_enbdis(काष्ठा net_device *netdev, पूर्णांक state,
		       काष्ठा visornic_devdata *devdata)
अणु
	पूर्णांक err;

	devdata->cmdrsp_rcv->net.enbdis.enable = state;
	devdata->cmdrsp_rcv->net.enbdis.context = netdev;
	devdata->cmdrsp_rcv->net.type = NET_RCV_ENBDIS;
	devdata->cmdrsp_rcv->cmdtype = CMD_NET_TYPE;
	err = visorchannel_संकेतinsert(devdata->dev->visorchannel,
					IOCHAN_TO_IOPART,
					devdata->cmdrsp_rcv);
	अगर (err)
		वापस err;
	devdata->chstat.sent_enbdis++;
	वापस 0;
पूर्ण

/* visornic_disable_with_समयout - disable network adapter
 * @netdev:  netdevice to disable.
 * @समयout: Timeout to रुको क्रम disable.
 *
 * Disable the network adapter and inक्रमm the IO Partition that we are disabled.
 * Reclaim memory from rcv bufs.
 *
 * Return: 0 on success, negative पूर्णांकeger on failure of IO Partition responding.
 */
अटल पूर्णांक visornic_disable_with_समयout(काष्ठा net_device *netdev,
					 स्थिर पूर्णांक समयout)
अणु
	काष्ठा visornic_devdata *devdata = netdev_priv(netdev);
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	पूर्णांक रुको = 0;
	पूर्णांक err;

	/* send a msg telling the other end we are stopping incoming pkts */
	spin_lock_irqsave(&devdata->priv_lock, flags);
	devdata->enabled = 0;
	/* must रुको क्रम ack */
	devdata->enab_dis_acked = 0;
	spin_unlock_irqrestore(&devdata->priv_lock, flags);

	/* send disable and रुको क्रम ack -- करोn't hold lock when sending
	 * disable because अगर the queue is full, insert might sleep.
	 * If an error occurs, करोn't रुको क्रम the समयout.
	 */
	err = send_enbdis(netdev, 0, devdata);
	अगर (err)
		वापस err;

	/* रुको क्रम ack to arrive beक्रमe we try to मुक्त rcv buffers
	 * NOTE: the other end स्वतःmatically unposts the rcv buffers
	 * when it माला_लो a disable.
	 */
	spin_lock_irqsave(&devdata->priv_lock, flags);
	जबतक ((समयout == VISORNIC_INFINITE_RSP_WAIT) ||
	       (रुको < समयout)) अणु
		अगर (devdata->enab_dis_acked)
			अवरोध;
		अगर (devdata->server_करोwn || devdata->server_change_state) अणु
			dev_dbg(&netdev->dev, "%s server went away\n",
				__func__);
			अवरोध;
		पूर्ण
		set_current_state(TASK_INTERRUPTIBLE);
		spin_unlock_irqrestore(&devdata->priv_lock, flags);
		रुको += schedule_समयout(msecs_to_jअगरfies(10));
		spin_lock_irqsave(&devdata->priv_lock, flags);
	पूर्ण

	/* Wait क्रम usage to go to 1 (no other users) beक्रमe मुक्तing
	 * rcv buffers
	 */
	अगर (atomic_पढ़ो(&devdata->usage) > 1) अणु
		जबतक (1) अणु
			set_current_state(TASK_INTERRUPTIBLE);
			spin_unlock_irqrestore(&devdata->priv_lock, flags);
			schedule_समयout(msecs_to_jअगरfies(10));
			spin_lock_irqsave(&devdata->priv_lock, flags);
			अगर (atomic_पढ़ो(&devdata->usage))
				अवरोध;
		पूर्ण
	पूर्ण
	/* we've set enabled to 0, so we can give up the lock. */
	spin_unlock_irqrestore(&devdata->priv_lock, flags);

	/* stop the transmit queue so nothing more can be transmitted */
	netअगर_stop_queue(netdev);

	napi_disable(&devdata->napi);

	skb_queue_purge(&devdata->xmitbufhead);

	/* Free rcv buffers - other end has स्वतःmatically unposed them on
	 * disable
	 */
	क्रम (i = 0; i < devdata->num_rcv_bufs; i++) अणु
		अगर (devdata->rcvbuf[i]) अणु
			kमुक्त_skb(devdata->rcvbuf[i]);
			devdata->rcvbuf[i] = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* init_rcv_bufs - initialize receive buffs and send them to the IO Partition
 * @netdev:  काष्ठा netdevice.
 * @devdata: visornic_devdata.
 *
 * Allocate rcv buffers and post them to the IO Partition.
 *
 * Return: 0 on success, negative पूर्णांकeger on failure.
 */
अटल पूर्णांक init_rcv_bufs(काष्ठा net_device *netdev,
			 काष्ठा visornic_devdata *devdata)
अणु
	पूर्णांक i, j, count, err;

	/* allocate fixed number of receive buffers to post to uisnic
	 * post receive buffers after we've allocated a required amount
	 */
	क्रम (i = 0; i < devdata->num_rcv_bufs; i++) अणु
		devdata->rcvbuf[i] = alloc_rcv_buf(netdev);
		/* अगर we failed to allocate one let us stop */
		अगर (!devdata->rcvbuf[i])
			अवरोध;
	पूर्ण
	/* couldn't even allocate one -- bail out */
	अगर (i == 0)
		वापस -ENOMEM;
	count = i;

	/* Ensure we can alloc 2/3rd of the requested number of buffers.
	 * 2/3 is an arbitrary choice; used also in ndis init.c
	 */
	अगर (count < ((2 * devdata->num_rcv_bufs) / 3)) अणु
		/* मुक्त receive buffers we did alloc and then bail out */
		क्रम (i = 0; i < count; i++) अणु
			kमुक्त_skb(devdata->rcvbuf[i]);
			devdata->rcvbuf[i] = शून्य;
		पूर्ण
		वापस -ENOMEM;
	पूर्ण

	/* post receive buffers to receive incoming input - without holding
	 * lock - we've not enabled nor started the queue so there shouldn't
	 * be any rcv or xmit activity
	 */
	क्रम (i = 0; i < count; i++) अणु
		err = post_skb(devdata->cmdrsp_rcv, devdata,
			       devdata->rcvbuf[i]);
		अगर (!err)
			जारी;

		/* Error handling -
		 * If we posted at least one skb, we should वापस success,
		 * but need to मुक्त the resources that we have not successfully
		 * posted.
		 */
		क्रम (j = i; j < count; j++) अणु
			kमुक्त_skb(devdata->rcvbuf[j]);
			devdata->rcvbuf[j] = शून्य;
		पूर्ण
		अगर (i == 0)
			वापस err;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* visornic_enable_with_समयout	- send enable to IO Partition
 * @netdev:  काष्ठा net_device.
 * @समयout: Time to रुको क्रम the ACK from the enable.
 *
 * Sends enable to IOVM and inits, and posts receive buffers to IOVM. Timeout is
 * defined in msecs (समयout of 0 specअगरies infinite रुको).
 *
 * Return: 0 on success, negative पूर्णांकeger on failure.
 */
अटल पूर्णांक visornic_enable_with_समयout(काष्ठा net_device *netdev,
					स्थिर पूर्णांक समयout)
अणु
	पूर्णांक err = 0;
	काष्ठा visornic_devdata *devdata = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;
	पूर्णांक रुको = 0;

	napi_enable(&devdata->napi);

	/* NOTE: the other end स्वतःmatically unposts the rcv buffers when it
	 * माला_लो a disable.
	 */
	err = init_rcv_bufs(netdev, devdata);
	अगर (err < 0) अणु
		dev_err(&netdev->dev,
			"%s failed to init rcv bufs\n", __func__);
		वापस err;
	पूर्ण

	spin_lock_irqsave(&devdata->priv_lock, flags);
	devdata->enabled = 1;
	devdata->enab_dis_acked = 0;

	/* now we're ready, let's send an ENB to uisnic but until we get
	 * an ACK back from uisnic, we'll drop the packets
	 */
	devdata->n_rcv_packets_not_accepted = 0;
	spin_unlock_irqrestore(&devdata->priv_lock, flags);

	/* send enable and रुको क्रम ack -- करोn't hold lock when sending enable
	 * because अगर the queue is full, insert might sleep. If an error
	 * occurs error out.
	 */
	err = send_enbdis(netdev, 1, devdata);
	अगर (err)
		वापस err;

	spin_lock_irqsave(&devdata->priv_lock, flags);
	जबतक ((समयout == VISORNIC_INFINITE_RSP_WAIT) ||
	       (रुको < समयout)) अणु
		अगर (devdata->enab_dis_acked)
			अवरोध;
		अगर (devdata->server_करोwn || devdata->server_change_state) अणु
			dev_dbg(&netdev->dev, "%s server went away\n",
				__func__);
			अवरोध;
		पूर्ण
		set_current_state(TASK_INTERRUPTIBLE);
		spin_unlock_irqrestore(&devdata->priv_lock, flags);
		रुको += schedule_समयout(msecs_to_jअगरfies(10));
		spin_lock_irqsave(&devdata->priv_lock, flags);
	पूर्ण

	spin_unlock_irqrestore(&devdata->priv_lock, flags);

	अगर (!devdata->enab_dis_acked) अणु
		dev_err(&netdev->dev, "%s missing ACK\n", __func__);
		वापस -EIO;
	पूर्ण

	netअगर_start_queue(netdev);
	वापस 0;
पूर्ण

/* visornic_समयout_reset - handle xmit समयout resets
 * @work: Work item that scheduled the work.
 *
 * Transmit समयouts are typically handled by resetting the device क्रम our
 * भव NIC; we will send a disable and enable to the IOVM. If it करोesn't
 * respond, we will trigger a serverकरोwn.
 */
अटल व्योम visornic_समयout_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा visornic_devdata *devdata;
	काष्ठा net_device *netdev;
	पूर्णांक response = 0;

	devdata = container_of(work, काष्ठा visornic_devdata, समयout_reset);
	netdev = devdata->netdev;

	rtnl_lock();
	अगर (!netअगर_running(netdev)) अणु
		rtnl_unlock();
		वापस;
	पूर्ण

	response = visornic_disable_with_समयout(netdev,
						 VISORNIC_INFINITE_RSP_WAIT);
	अगर (response)
		जाओ call_serverकरोwn;

	response = visornic_enable_with_समयout(netdev,
						VISORNIC_INFINITE_RSP_WAIT);
	अगर (response)
		जाओ call_serverकरोwn;

	rtnl_unlock();

	वापस;

call_serverकरोwn:
	visornic_serverकरोwn(devdata, शून्य);
	rtnl_unlock();
पूर्ण

/* visornic_खोलो - enable the visornic device and mark the queue started
 * @netdev: netdevice to start.
 *
 * Enable the device and start the transmit queue.
 *
 * Return: 0 on success.
 */
अटल पूर्णांक visornic_खोलो(काष्ठा net_device *netdev)
अणु
	visornic_enable_with_समयout(netdev, VISORNIC_INFINITE_RSP_WAIT);
	वापस 0;
पूर्ण

/* visornic_बंद - disables the visornic device and stops the queues
 * @netdev: netdevice to stop.
 *
 * Disable the device and stop the transmit queue.
 *
 * Return 0 on success.
 */
अटल पूर्णांक visornic_बंद(काष्ठा net_device *netdev)
अणु
	visornic_disable_with_समयout(netdev, VISORNIC_INFINITE_RSP_WAIT);
	वापस 0;
पूर्ण

/* devdata_xmits_outstanding - compute outstanding xmits
 * @devdata: visornic_devdata क्रम device
 *
 * Return: Long पूर्णांकeger representing the number of outstanding xmits.
 */
अटल अचिन्हित दीर्घ devdata_xmits_outstanding(काष्ठा visornic_devdata *devdata)
अणु
	अगर (devdata->chstat.sent_xmit >= devdata->chstat.got_xmit_करोne)
		वापस devdata->chstat.sent_xmit -
			devdata->chstat.got_xmit_करोne;
	वापस (अच_दीर्घ_उच्च - devdata->chstat.got_xmit_करोne
		+ devdata->chstat.sent_xmit + 1);
पूर्ण

/* vnic_hit_high_watermark
 * @devdata:	    Indicates visornic device we are checking.
 * @high_watermark: Max num of unacked xmits we will tolerate beक्रमe we will
 *		    start throttling.
 *
 * Return: True अगरf the number of unacked xmits sent to the IO Partition is >=
 *	   high_watermark. False otherwise.
 */
अटल bool vnic_hit_high_watermark(काष्ठा visornic_devdata *devdata,
				    uदीर्घ high_watermark)
अणु
	वापस (devdata_xmits_outstanding(devdata) >= high_watermark);
पूर्ण

/* vnic_hit_low_watermark
 * @devdata:	   Indicates visornic device we are checking.
 * @low_watermark: We will रुको until the num of unacked xmits drops to this
 *		   value or lower beक्रमe we start transmitting again.
 *
 * Return: True अगरf the number of unacked xmits sent to the IO Partition is <=
 *	   low_watermark.
 */
अटल bool vnic_hit_low_watermark(काष्ठा visornic_devdata *devdata,
				   uदीर्घ low_watermark)
अणु
	वापस (devdata_xmits_outstanding(devdata) <= low_watermark);
पूर्ण

/* visornic_xmit - send a packet to the IO Partition
 * @skb:    Packet to be sent.
 * @netdev: Net device the packet is being sent from.
 *
 * Convert the skb to a cmdrsp so the IO Partition can understand it, and send
 * the XMIT command to the IO Partition क्रम processing. This function is
 * रक्षित from concurrent calls by a spinlock xmit_lock in the net_device
 * काष्ठा. As soon as the function वापसs, it can be called again.
 *
 * Return: NETDEV_TX_OK.
 */
अटल netdev_tx_t visornic_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा visornic_devdata *devdata;
	पूर्णांक len, firstfraglen, padlen;
	काष्ठा uiscmdrsp *cmdrsp = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	devdata = netdev_priv(netdev);
	spin_lock_irqsave(&devdata->priv_lock, flags);

	अगर (netअगर_queue_stopped(netdev) || devdata->server_करोwn ||
	    devdata->server_change_state) अणु
		spin_unlock_irqrestore(&devdata->priv_lock, flags);
		devdata->busy_cnt++;
		dev_dbg(&netdev->dev,
			"%s busy - queue stopped\n", __func__);
		kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* sk_buff काष्ठा is used to host network data throughout all the
	 * linux network subप्रणालीs
	 */
	len = skb->len;

	/* skb->len is the FULL length of data (including fragmentary portion)
	 * skb->data_len is the length of the fragment portion in frags
	 * skb->len - skb->data_len is size of the 1st fragment in skb->data
	 * calculate the length of the first fragment that skb->data is
	 * poपूर्णांकing to
	 */
	firstfraglen = skb->len - skb->data_len;
	अगर (firstfraglen < ETH_HLEN) अणु
		spin_unlock_irqrestore(&devdata->priv_lock, flags);
		devdata->busy_cnt++;
		dev_err(&netdev->dev,
			"%s busy - first frag too small (%d)\n",
			__func__, firstfraglen);
		kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (len < ETH_MIN_PACKET_SIZE &&
	    ((skb_end_poपूर्णांकer(skb) - skb->data) >= ETH_MIN_PACKET_SIZE)) अणु
		/* pad the packet out to minimum size */
		padlen = ETH_MIN_PACKET_SIZE - len;
		skb_put_zero(skb, padlen);
		len += padlen;
		firstfraglen += padlen;
	पूर्ण

	cmdrsp = devdata->xmit_cmdrsp;
	/* clear cmdrsp */
	स_रखो(cmdrsp, 0, SIZखातापूर्ण_CMDRSP);
	cmdrsp->net.type = NET_XMIT;
	cmdrsp->cmdtype = CMD_NET_TYPE;

	/* save the poपूर्णांकer to skb -- we'll need it क्रम completion */
	cmdrsp->net.buf = skb;

	अगर (vnic_hit_high_watermark(devdata,
				    devdata->max_outstanding_net_xmits)) अणु
		/* extra NET_XMITs queued over to IOVM - need to रुको */
		devdata->chstat.reject_count++;
		अगर (!devdata->queuefullmsg_logged &&
		    ((devdata->chstat.reject_count & 0x3ff) == 1))
			devdata->queuefullmsg_logged = 1;
		netअगर_stop_queue(netdev);
		spin_unlock_irqrestore(&devdata->priv_lock, flags);
		devdata->busy_cnt++;
		dev_dbg(&netdev->dev,
			"%s busy - waiting for iovm to catch up\n",
			__func__);
		kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण
	अगर (devdata->queuefullmsg_logged)
		devdata->queuefullmsg_logged = 0;

	अगर (skb->ip_summed == CHECKSUM_UNNECESSARY) अणु
		cmdrsp->net.xmt.lincsum.valid = 1;
		cmdrsp->net.xmt.lincsum.protocol = skb->protocol;
		अगर (skb_transport_header(skb) > skb->data) अणु
			cmdrsp->net.xmt.lincsum.hrawoff =
				skb_transport_header(skb) - skb->data;
			cmdrsp->net.xmt.lincsum.hrawoff = 1;
		पूर्ण
		अगर (skb_network_header(skb) > skb->data) अणु
			cmdrsp->net.xmt.lincsum.nhrawoff =
				skb_network_header(skb) - skb->data;
			cmdrsp->net.xmt.lincsum.nhrawoffv = 1;
		पूर्ण
		cmdrsp->net.xmt.lincsum.csum = skb->csum;
	पूर्ण अन्यथा अणु
		cmdrsp->net.xmt.lincsum.valid = 0;
	पूर्ण

	/* save off the length of the entire data packet */
	cmdrsp->net.xmt.len = len;

	/* copy ethernet header from first frag पूर्णांकo ocmdrsp
	 * - everything अन्यथा will be pass in frags & DMA'ed
	 */
	स_नकल(cmdrsp->net.xmt.ethhdr, skb->data, ETH_HLEN);

	/* copy frags info - from skb->data we need to only provide access
	 * beyond eth header
	 */
	cmdrsp->net.xmt.num_frags =
		visor_copy_fragsinfo_from_skb(skb, firstfraglen,
					      MAX_PHYS_INFO,
					      cmdrsp->net.xmt.frags);
	अगर (cmdrsp->net.xmt.num_frags < 0) अणु
		spin_unlock_irqrestore(&devdata->priv_lock, flags);
		devdata->busy_cnt++;
		dev_err(&netdev->dev,
			"%s busy - copy frags failed\n", __func__);
		kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	err = visorchannel_संकेतinsert(devdata->dev->visorchannel,
					IOCHAN_TO_IOPART, cmdrsp);
	अगर (err) अणु
		netअगर_stop_queue(netdev);
		spin_unlock_irqrestore(&devdata->priv_lock, flags);
		devdata->busy_cnt++;
		dev_dbg(&netdev->dev,
			"%s busy - signalinsert failed\n", __func__);
		kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* Track the skbs that have been sent to the IOVM क्रम XMIT */
	skb_queue_head(&devdata->xmitbufhead, skb);

	/* update xmt stats */
	devdata->net_stats.tx_packets++;
	devdata->net_stats.tx_bytes += skb->len;
	devdata->chstat.sent_xmit++;

	/* check अगर we have hit the high watermark क्रम netअगर_stop_queue() */
	अगर (vnic_hit_high_watermark(devdata,
				    devdata->upper_threshold_net_xmits)) अणु
		/* extra NET_XMITs queued over to IOVM - need to रुको */
		/* stop queue - call netअगर_wake_queue() after lower threshold */
		netअगर_stop_queue(netdev);
		dev_dbg(&netdev->dev,
			"%s busy - invoking iovm flow control\n",
			__func__);
		devdata->flow_control_upper_hits++;
	पूर्ण
	spin_unlock_irqrestore(&devdata->priv_lock, flags);

	/* skb will be मुक्तd when we get back NET_XMIT_DONE */
	वापस NETDEV_TX_OK;
पूर्ण

/* visornic_get_stats - वापसs net_stats of the visornic device
 * @netdev: netdevice.
 *
 * Return: Poपूर्णांकer to the net_device_stats काष्ठा क्रम the device.
 */
अटल काष्ठा net_device_stats *visornic_get_stats(काष्ठा net_device *netdev)
अणु
	काष्ठा visornic_devdata *devdata = netdev_priv(netdev);

	वापस &devdata->net_stats;
पूर्ण

/* visornic_change_mtu - changes mtu of device
 * @netdev: netdevice.
 * @new_mtu: Value of new mtu.
 *
 * The device's MTU cannot be changed by प्रणाली; it must be changed via a
 * CONTROLVM message. All vnics and pnics in a चयन have to have the same MTU
 * क्रम everything to work. Currently not supported.
 *
 * Return: -EINVAL.
 */
अटल पूर्णांक visornic_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	वापस -EINVAL;
पूर्ण

/* visornic_set_multi - set visornic device flags
 * @netdev: netdevice.
 *
 * The only flag we currently support is IFF_PROMISC.
 */
अटल व्योम visornic_set_multi(काष्ठा net_device *netdev)
अणु
	काष्ठा uiscmdrsp *cmdrsp;
	काष्ठा visornic_devdata *devdata = netdev_priv(netdev);
	पूर्णांक err = 0;

	अगर (devdata->old_flags == netdev->flags)
		वापस;

	अगर ((netdev->flags & IFF_PROMISC) ==
	    (devdata->old_flags & IFF_PROMISC))
		जाओ out_save_flags;

	cmdrsp = kदो_स्मृति(SIZखातापूर्ण_CMDRSP, GFP_ATOMIC);
	अगर (!cmdrsp)
		वापस;
	cmdrsp->cmdtype = CMD_NET_TYPE;
	cmdrsp->net.type = NET_RCV_PROMISC;
	cmdrsp->net.enbdis.context = netdev;
	cmdrsp->net.enbdis.enable =
		netdev->flags & IFF_PROMISC;
	err = visorchannel_संकेतinsert(devdata->dev->visorchannel,
					IOCHAN_TO_IOPART,
					cmdrsp);
	kमुक्त(cmdrsp);
	अगर (err)
		वापस;

out_save_flags:
	devdata->old_flags = netdev->flags;
पूर्ण

/* visornic_xmit_समयout - request to समयout the xmit
 * @netdev: netdevice.
 *
 * Queue the work and वापस. Make sure we have not alपढ़ोy been inक्रमmed that
 * the IO Partition is gone; अगर so, we will have alपढ़ोy समयd-out the xmits.
 */
अटल व्योम visornic_xmit_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा visornic_devdata *devdata = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&devdata->priv_lock, flags);
	अगर (devdata->going_away) अणु
		spin_unlock_irqrestore(&devdata->priv_lock, flags);
		dev_dbg(&devdata->dev->device,
			"%s aborting because device removal pending\n",
			__func__);
		वापस;
	पूर्ण

	/* Ensure that a ServerDown message hasn't been received */
	अगर (!devdata->enabled ||
	    (devdata->server_करोwn && !devdata->server_change_state)) अणु
		dev_dbg(&netdev->dev, "%s no processing\n",
			__func__);
		spin_unlock_irqrestore(&devdata->priv_lock, flags);
		वापस;
	पूर्ण
	schedule_work(&devdata->समयout_reset);
	spin_unlock_irqrestore(&devdata->priv_lock, flags);
पूर्ण

/* repost_वापस - repost rcv bufs that have come back
 * @cmdrsp: IO channel command काष्ठा to post.
 * @devdata: Visornic devdata क्रम the device.
 * @skb: Socket buffer.
 * @netdev: netdevice.
 *
 * Repost rcv buffers that have been वापसed to us when we are finished
 * with them.
 *
 * Return: 0 क्रम success, negative पूर्णांकeger on error.
 */
अटल पूर्णांक repost_वापस(काष्ठा uiscmdrsp *cmdrsp,
			 काष्ठा visornic_devdata *devdata,
			 काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा net_pkt_rcv copy;
	पूर्णांक i = 0, cc, numreposted;
	पूर्णांक found_skb = 0;
	पूर्णांक status = 0;

	copy = cmdrsp->net.rcv;
	चयन (copy.numrcvbufs) अणु
	हाल 0:
		devdata->n_rcv0++;
		अवरोध;
	हाल 1:
		devdata->n_rcv1++;
		अवरोध;
	हाल 2:
		devdata->n_rcv2++;
		अवरोध;
	शेष:
		devdata->n_rcvx++;
		अवरोध;
	पूर्ण
	क्रम (cc = 0, numreposted = 0; cc < copy.numrcvbufs; cc++) अणु
		क्रम (i = 0; i < devdata->num_rcv_bufs; i++) अणु
			अगर (devdata->rcvbuf[i] != copy.rcvbuf[cc])
				जारी;

			अगर ((skb) && devdata->rcvbuf[i] == skb) अणु
				devdata->found_repost_rcvbuf_cnt++;
				found_skb = 1;
				devdata->repost_found_skb_cnt++;
			पूर्ण
			devdata->rcvbuf[i] = alloc_rcv_buf(netdev);
			अगर (!devdata->rcvbuf[i]) अणु
				devdata->num_rcv_bufs_could_not_alloc++;
				devdata->alloc_failed_in_repost_rtn_cnt++;
				status = -ENOMEM;
				अवरोध;
			पूर्ण
			status = post_skb(cmdrsp, devdata, devdata->rcvbuf[i]);
			अगर (status) अणु
				kमुक्त_skb(devdata->rcvbuf[i]);
				devdata->rcvbuf[i] = शून्य;
				अवरोध;
			पूर्ण
			numreposted++;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (numreposted != copy.numrcvbufs) अणु
		devdata->n_repost_deficit++;
		status = -EINVAL;
	पूर्ण
	अगर (skb) अणु
		अगर (found_skb) अणु
			kमुक्त_skb(skb);
		पूर्ण अन्यथा अणु
			status = -EINVAL;
			devdata->bad_rcv_buf++;
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

/* visornic_rx - handle receive packets coming back from IO Partition
 * @cmdrsp: Receive packet वापसed from IO Partition.
 *
 * Got a receive packet back from the IO Partition; handle it and send it up
 * the stack.

 * Return: 1 अगरf an skb was received, otherwise 0.
 */
अटल पूर्णांक visornic_rx(काष्ठा uiscmdrsp *cmdrsp)
अणु
	काष्ठा visornic_devdata *devdata;
	काष्ठा sk_buff *skb, *prev, *curr;
	काष्ठा net_device *netdev;
	पूर्णांक cc, currsize, off;
	काष्ठा ethhdr *eth;
	अचिन्हित दीर्घ flags;

	/* post new rcv buf to the other end using the cmdrsp we have at hand
	 * post it without holding lock - but we'll use the संकेत lock to
	 * synchronize the queue insert the cmdrsp that contains the net.rcv
	 * is the one we are using to repost, so copy the info we need from it.
	 */
	skb = cmdrsp->net.buf;
	netdev = skb->dev;

	devdata = netdev_priv(netdev);

	spin_lock_irqsave(&devdata->priv_lock, flags);
	atomic_dec(&devdata->num_rcvbuf_in_iovm);

	/* set length to how much was ACTUALLY received -
	 * NOTE: rcv_करोne_len includes actual length of data rcvd
	 * including ethhdr
	 */
	skb->len = cmdrsp->net.rcv.rcv_करोne_len;

	/* update rcv stats - call it with priv_lock held */
	devdata->net_stats.rx_packets++;
	devdata->net_stats.rx_bytes += skb->len;

	/* test enabled जबतक holding lock */
	अगर (!(devdata->enabled && devdata->enab_dis_acked)) अणु
		/* करोn't process it unless we're in enable mode and until
		 * we've gotten an ACK saying the other end got our RCV enable
		 */
		spin_unlock_irqrestore(&devdata->priv_lock, flags);
		repost_वापस(cmdrsp, devdata, skb, netdev);
		वापस 0;
	पूर्ण

	spin_unlock_irqrestore(&devdata->priv_lock, flags);

	/* when skb was allocated, skb->dev, skb->data, skb->len and
	 * skb->data_len were setup. AND, data has alपढ़ोy put पूर्णांकo the
	 * skb (both first frag and in frags pages)
	 * NOTE: firstfragslen is the amount of data in skb->data and that
	 * which is not in nr_frags or frag_list. This is now simply
	 * RCVPOST_BUF_SIZE. bump tail to show how much data is in
	 * firstfrag & set data_len to show rest see अगर we have to chain
	 * frag_list.
	 */
	/* करो PRECAUTIONARY check */
	अगर (skb->len > RCVPOST_BUF_SIZE) अणु
		अगर (cmdrsp->net.rcv.numrcvbufs < 2) अणु
			अगर (repost_वापस(cmdrsp, devdata, skb, netdev) < 0)
				dev_err(&devdata->netdev->dev,
					"repost_return failed");
			वापस 0;
		पूर्ण
		/* length rcvd is greater than firstfrag in this skb rcv buf  */
		/* amount in skb->data */
		skb->tail += RCVPOST_BUF_SIZE;
		/* amount that will be in frag_list */
		skb->data_len = skb->len - RCVPOST_BUF_SIZE;
	पूर्ण अन्यथा अणु
		/* data fits in this skb - no chaining - करो
		 * PRECAUTIONARY check
		 */
		/* should be 1 */
		अगर (cmdrsp->net.rcv.numrcvbufs != 1) अणु
			अगर (repost_वापस(cmdrsp, devdata, skb, netdev) < 0)
				dev_err(&devdata->netdev->dev,
					"repost_return failed");
			वापस 0;
		पूर्ण
		skb->tail += skb->len;
		/* nothing rcvd in frag_list */
		skb->data_len = 0;
	पूर्ण
	off = skb_tail_poपूर्णांकer(skb) - skb->data;

	/* amount we bumped tail by in the head skb
	 * it is used to calculate the size of each chained skb below
	 * it is also used to index पूर्णांकo bufline to जारी the copy
	 * (क्रम chansocktwopc)
	 * अगर necessary chain the rcv skbs together.
	 * NOTE: index 0 has the same as cmdrsp->net.rcv.skb; we need to
	 * chain the rest to that one.
	 * - करो PRECAUTIONARY check
	 */
	अगर (cmdrsp->net.rcv.rcvbuf[0] != skb) अणु
		अगर (repost_वापस(cmdrsp, devdata, skb, netdev) < 0)
			dev_err(&devdata->netdev->dev, "repost_return failed");
		वापस 0;
	पूर्ण

	अगर (cmdrsp->net.rcv.numrcvbufs > 1) अणु
		/* chain the various rcv buffers पूर्णांकo the skb's frag_list. */
		/* Note: off was initialized above  */
		क्रम (cc = 1, prev = शून्य;
		     cc < cmdrsp->net.rcv.numrcvbufs; cc++) अणु
			curr = (काष्ठा sk_buff *)cmdrsp->net.rcv.rcvbuf[cc];
			curr->next = शून्य;
			/* start of list- set head */
			अगर (!prev)
				skb_shinfo(skb)->frag_list = curr;
			अन्यथा
				prev->next = curr;
			prev = curr;

			/* should we set skb->len and skb->data_len क्रम each
			 * buffer being chained??? can't hurt!
			 */
			currsize = min(skb->len - off,
				       (अचिन्हित पूर्णांक)RCVPOST_BUF_SIZE);
			curr->len = currsize;
			curr->tail += currsize;
			curr->data_len = 0;
			off += currsize;
		पूर्ण
		/* निश्चित skb->len == off */
		अगर (skb->len != off) अणु
			netdev_err(devdata->netdev,
				   "something wrong; skb->len:%d != off:%d\n",
				   skb->len, off);
		पूर्ण
	पूर्ण

	/* set up packet's protocol type using ethernet header - this
	 * sets up skb->pkt_type & it also PULLS out the eth header
	 */
	skb->protocol = eth_type_trans(skb, netdev);
	eth = eth_hdr(skb);
	skb->csum = 0;
	skb->ip_summed = CHECKSUM_NONE;

	करो अणु
		/* accept all packets */
		अगर (netdev->flags & IFF_PROMISC)
			अवरोध;
		अगर (skb->pkt_type == PACKET_BROADCAST) अणु
			/* accept all broadcast packets */
			अगर (netdev->flags & IFF_BROADCAST)
				अवरोध;
		पूर्ण अन्यथा अगर (skb->pkt_type == PACKET_MULTICAST) अणु
			अगर ((netdev->flags & IFF_MULTICAST) &&
			    (netdev_mc_count(netdev))) अणु
				काष्ठा netdev_hw_addr *ha;
				पूर्णांक found_mc = 0;

				/* only accept multicast packets that we can
				 * find in our multicast address list
				 */
				netdev_क्रम_each_mc_addr(ha, netdev) अणु
					अगर (ether_addr_equal(eth->h_dest,
							     ha->addr)) अणु
						found_mc = 1;
						अवरोध;
					पूर्ण
				पूर्ण
				/* accept pkt, dest matches a multicast addr */
				अगर (found_mc)
					अवरोध;
			पूर्ण
		/* accept packet, h_dest must match vnic  mac address */
		पूर्ण अन्यथा अगर (skb->pkt_type == PACKET_HOST) अणु
			अवरोध;
		पूर्ण अन्यथा अगर (skb->pkt_type == PACKET_OTHERHOST) अणु
			/* something is not right */
			dev_err(&devdata->netdev->dev,
				"**** FAILED to deliver rcv packet to OS; name:%s Dest:%pM VNIC:%pM\n",
				netdev->name, eth->h_dest, netdev->dev_addr);
		पूर्ण
		/* drop packet - करोn't क्रमward it up to OS */
		devdata->n_rcv_packets_not_accepted++;
		repost_वापस(cmdrsp, devdata, skb, netdev);
		वापस 0;
	पूर्ण जबतक (0);

	netअगर_receive_skb(skb);
	/* netअगर_rx वापसs various values, but "in practice most drivers
	 * ignore the वापस value
	 */

	skb = शून्य;
	/* whether the packet got dropped or handled, the skb is मुक्तd by
	 * kernel code, so we shouldn't मुक्त it. but we should repost a
	 * new rcv buffer.
	 */
	repost_वापस(cmdrsp, devdata, skb, netdev);
	वापस 1;
पूर्ण

/* devdata_initialize - initialize devdata काष्ठाure
 * @devdata: visornic_devdata काष्ठाure to initialize.
 * @dev:     visorbus_device it beदीर्घs to.
 *
 * Setup initial values क्रम the visornic, based on channel and शेष values.
 *
 * Return: A poपूर्णांकer to the devdata काष्ठाure.
 */
अटल काष्ठा visornic_devdata *devdata_initialize(
					काष्ठा visornic_devdata *devdata,
					काष्ठा visor_device *dev)
अणु
	devdata->dev = dev;
	devdata->incarnation_id = get_jअगरfies_64();
	वापस devdata;
पूर्ण

/* devdata_release - मुक्त up references in devdata
 * @devdata: Struct to clean up.
 */
अटल व्योम devdata_release(काष्ठा visornic_devdata *devdata)
अणु
	kमुक्त(devdata->rcvbuf);
	kमुक्त(devdata->cmdrsp_rcv);
	kमुक्त(devdata->xmit_cmdrsp);
पूर्ण

अटल स्थिर काष्ठा net_device_ops visornic_dev_ops = अणु
	.nकरो_खोलो = visornic_खोलो,
	.nकरो_stop = visornic_बंद,
	.nकरो_start_xmit = visornic_xmit,
	.nकरो_get_stats = visornic_get_stats,
	.nकरो_change_mtu = visornic_change_mtu,
	.nकरो_tx_समयout = visornic_xmit_समयout,
	.nकरो_set_rx_mode = visornic_set_multi,
पूर्ण;

/* DebugFS code */
अटल sमाप_प्रकार info_debugfs_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				 माप_प्रकार len, loff_t *offset)
अणु
	sमाप_प्रकार bytes_पढ़ो = 0;
	पूर्णांक str_pos = 0;
	काष्ठा visornic_devdata *devdata;
	काष्ठा net_device *dev;
	अक्षर *vbuf;

	अगर (len > MAX_BUF)
		len = MAX_BUF;
	vbuf = kzalloc(len, GFP_KERNEL);
	अगर (!vbuf)
		वापस -ENOMEM;

	/* क्रम each vnic channel dump out channel specअगरic data */
	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(current->nsproxy->net_ns, dev) अणु
		/* Only consider netdevs that are visornic, and are खोलो */
		अगर (dev->netdev_ops != &visornic_dev_ops ||
		    (!netअगर_queue_stopped(dev)))
			जारी;

		devdata = netdev_priv(dev);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     "netdev = %s (0x%p), MAC Addr %pM\n",
				     dev->name,
				     dev,
				     dev->dev_addr);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     "VisorNic Dev Info = 0x%p\n", devdata);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " num_rcv_bufs = %d\n",
				     devdata->num_rcv_bufs);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " max_outstanding_next_xmits = %lu\n",
				    devdata->max_outstanding_net_xmits);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " upper_threshold_net_xmits = %lu\n",
				     devdata->upper_threshold_net_xmits);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " lower_threshold_net_xmits = %lu\n",
				     devdata->lower_threshold_net_xmits);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " queuefullmsg_logged = %d\n",
				     devdata->queuefullmsg_logged);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " chstat.got_rcv = %lu\n",
				     devdata->chstat.got_rcv);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " chstat.got_enbdisack = %lu\n",
				     devdata->chstat.got_enbdisack);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " chstat.got_xmit_done = %lu\n",
				     devdata->chstat.got_xmit_करोne);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " chstat.xmit_fail = %lu\n",
				     devdata->chstat.xmit_fail);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " chstat.sent_enbdis = %lu\n",
				     devdata->chstat.sent_enbdis);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " chstat.sent_promisc = %lu\n",
				     devdata->chstat.sent_promisc);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " chstat.sent_post = %lu\n",
				     devdata->chstat.sent_post);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " chstat.sent_post_failed = %lu\n",
				     devdata->chstat.sent_post_failed);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " chstat.sent_xmit = %lu\n",
				     devdata->chstat.sent_xmit);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " chstat.reject_count = %lu\n",
				     devdata->chstat.reject_count);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " chstat.extra_rcvbufs_sent = %lu\n",
				     devdata->chstat.extra_rcvbufs_sent);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " n_rcv0 = %lu\n", devdata->n_rcv0);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " n_rcv1 = %lu\n", devdata->n_rcv1);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " n_rcv2 = %lu\n", devdata->n_rcv2);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " n_rcvx = %lu\n", devdata->n_rcvx);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " num_rcvbuf_in_iovm = %d\n",
				     atomic_पढ़ो(&devdata->num_rcvbuf_in_iovm));
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " alloc_failed_in_if_needed_cnt = %lu\n",
				     devdata->alloc_failed_in_अगर_needed_cnt);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " alloc_failed_in_repost_rtn_cnt = %lu\n",
				     devdata->alloc_failed_in_repost_rtn_cnt);
		/* str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
		 *		     " inner_loop_limit_reached_cnt = %lu\n",
		 *		     devdata->inner_loop_limit_reached_cnt);
		 */
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " found_repost_rcvbuf_cnt = %lu\n",
				     devdata->found_repost_rcvbuf_cnt);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " repost_found_skb_cnt = %lu\n",
				     devdata->repost_found_skb_cnt);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " n_repost_deficit = %lu\n",
				     devdata->n_repost_deficit);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " bad_rcv_buf = %lu\n",
				     devdata->bad_rcv_buf);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " n_rcv_packets_not_accepted = %lu\n",
				     devdata->n_rcv_packets_not_accepted);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " interrupts_rcvd = %llu\n",
				     devdata->पूर्णांकerrupts_rcvd);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " interrupts_notme = %llu\n",
				     devdata->पूर्णांकerrupts_noपंचांगe);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " interrupts_disabled = %llu\n",
				     devdata->पूर्णांकerrupts_disabled);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " busy_cnt = %llu\n",
				     devdata->busy_cnt);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " flow_control_upper_hits = %llu\n",
				     devdata->flow_control_upper_hits);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " flow_control_lower_hits = %llu\n",
				     devdata->flow_control_lower_hits);
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " netif_queue = %s\n",
				     netअगर_queue_stopped(devdata->netdev) ?
				     "stopped" : "running");
		str_pos += scnम_लिखो(vbuf + str_pos, len - str_pos,
				     " xmits_outstanding = %lu\n",
				     devdata_xmits_outstanding(devdata));
	पूर्ण
	rcu_पढ़ो_unlock();
	bytes_पढ़ो = simple_पढ़ो_from_buffer(buf, len, offset, vbuf, str_pos);
	kमुक्त(vbuf);
	वापस bytes_पढ़ो;
पूर्ण

अटल काष्ठा dentry *visornic_debugfs_dir;
अटल स्थिर काष्ठा file_operations debugfs_info_fops = अणु
	.पढ़ो = info_debugfs_पढ़ो,
पूर्ण;

/* send_rcv_posts_अगर_needed - send receive buffers to the IO Partition.
 * @devdata: Visornic device.
 */
अटल व्योम send_rcv_posts_अगर_needed(काष्ठा visornic_devdata *devdata)
अणु
	पूर्णांक i;
	काष्ठा net_device *netdev;
	काष्ठा uiscmdrsp *cmdrsp = devdata->cmdrsp_rcv;
	पूर्णांक cur_num_rcv_bufs_to_alloc, rcv_bufs_allocated;
	पूर्णांक err;

	/* करोn't करो this until vnic is marked पढ़ोy */
	अगर (!(devdata->enabled && devdata->enab_dis_acked))
		वापस;

	netdev = devdata->netdev;
	rcv_bufs_allocated = 0;
	/* this code is trying to prevent getting stuck here क्रमever,
	 * but still retry it अगर you cant allocate them all this समय.
	 */
	cur_num_rcv_bufs_to_alloc = devdata->num_rcv_bufs_could_not_alloc;
	जबतक (cur_num_rcv_bufs_to_alloc > 0) अणु
		cur_num_rcv_bufs_to_alloc--;
		क्रम (i = 0; i < devdata->num_rcv_bufs; i++) अणु
			अगर (devdata->rcvbuf[i])
				जारी;
			devdata->rcvbuf[i] = alloc_rcv_buf(netdev);
			अगर (!devdata->rcvbuf[i]) अणु
				devdata->alloc_failed_in_अगर_needed_cnt++;
				अवरोध;
			पूर्ण
			rcv_bufs_allocated++;
			err = post_skb(cmdrsp, devdata, devdata->rcvbuf[i]);
			अगर (err) अणु
				kमुक्त_skb(devdata->rcvbuf[i]);
				devdata->rcvbuf[i] = शून्य;
				अवरोध;
			पूर्ण
			devdata->chstat.extra_rcvbufs_sent++;
		पूर्ण
	पूर्ण
	devdata->num_rcv_bufs_could_not_alloc -= rcv_bufs_allocated;
पूर्ण

/* drain_resp_queue - drains and ignores all messages from the resp queue
 * @cmdrsp:  IO channel command response message.
 * @devdata: Visornic device to drain.
 */
अटल व्योम drain_resp_queue(काष्ठा uiscmdrsp *cmdrsp,
			     काष्ठा visornic_devdata *devdata)
अणु
	जबतक (!visorchannel_संकेतहटाओ(devdata->dev->visorchannel,
					  IOCHAN_FROM_IOPART,
					  cmdrsp))
		;
पूर्ण

/* service_resp_queue - drain the response queue
 * @cmdrsp:  IO channel command response message.
 * @devdata: Visornic device to drain.
 * @rx_work_करोne:
 * @budget:
 *
 * Drain the response queue of any responses from the IO Partition. Process the
 * responses as we get them.
 */
अटल व्योम service_resp_queue(काष्ठा uiscmdrsp *cmdrsp,
			       काष्ठा visornic_devdata *devdata,
			       पूर्णांक *rx_work_करोne, पूर्णांक budget)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा net_device *netdev;

	जबतक (*rx_work_करोne < budget) अणु
		/* TODO: CLIENT ACQUIRE -- Don't really need this at the
		 * moment
		 */
		/* queue empty */
		अगर (visorchannel_संकेतहटाओ(devdata->dev->visorchannel,
					      IOCHAN_FROM_IOPART,
					      cmdrsp))
			अवरोध;

		चयन (cmdrsp->net.type) अणु
		हाल NET_RCV:
			devdata->chstat.got_rcv++;
			/* process incoming packet */
			*rx_work_करोne += visornic_rx(cmdrsp);
			अवरोध;
		हाल NET_XMIT_DONE:
			spin_lock_irqsave(&devdata->priv_lock, flags);
			devdata->chstat.got_xmit_करोne++;
			अगर (cmdrsp->net.xmtकरोne.xmt_करोne_result)
				devdata->chstat.xmit_fail++;
			/* only call queue wake अगर we stopped it */
			netdev = ((काष्ठा sk_buff *)cmdrsp->net.buf)->dev;
			/* ASSERT netdev == vnicinfo->netdev; */
			अगर (netdev == devdata->netdev &&
			    netअगर_queue_stopped(netdev)) अणु
				/* check अगर we have crossed the lower watermark
				 * क्रम netअगर_wake_queue()
				 */
				अगर (vnic_hit_low_watermark
				    (devdata,
				     devdata->lower_threshold_net_xmits)) अणु
					/* enough NET_XMITs completed
					 * so can restart netअगर queue
					 */
					netअगर_wake_queue(netdev);
					devdata->flow_control_lower_hits++;
				पूर्ण
			पूर्ण
			skb_unlink(cmdrsp->net.buf, &devdata->xmitbufhead);
			spin_unlock_irqrestore(&devdata->priv_lock, flags);
			kमुक्त_skb(cmdrsp->net.buf);
			अवरोध;
		हाल NET_RCV_ENBDIS_ACK:
			devdata->chstat.got_enbdisack++;
			netdev = (काष्ठा net_device *)
			cmdrsp->net.enbdis.context;
			spin_lock_irqsave(&devdata->priv_lock, flags);
			devdata->enab_dis_acked = 1;
			spin_unlock_irqrestore(&devdata->priv_lock, flags);

			अगर (devdata->server_करोwn &&
			    devdata->server_change_state) अणु
				/* Inक्रमm Linux that the link is up */
				devdata->server_करोwn = false;
				devdata->server_change_state = false;
				netअगर_wake_queue(netdev);
				netअगर_carrier_on(netdev);
			पूर्ण
			अवरोध;
		हाल NET_CONNECT_STATUS:
			netdev = devdata->netdev;
			अगर (cmdrsp->net.enbdis.enable == 1) अणु
				spin_lock_irqsave(&devdata->priv_lock, flags);
				devdata->enabled = cmdrsp->net.enbdis.enable;
				spin_unlock_irqrestore(&devdata->priv_lock,
						       flags);
				netअगर_wake_queue(netdev);
				netअगर_carrier_on(netdev);
			पूर्ण अन्यथा अणु
				netअगर_stop_queue(netdev);
				netअगर_carrier_off(netdev);
				spin_lock_irqsave(&devdata->priv_lock, flags);
				devdata->enabled = cmdrsp->net.enbdis.enable;
				spin_unlock_irqrestore(&devdata->priv_lock,
						       flags);
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		/* cmdrsp is now available क्रम reuse  */
	पूर्ण
पूर्ण

अटल पूर्णांक visornic_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा visornic_devdata *devdata = container_of(napi,
							काष्ठा visornic_devdata,
							napi);
	पूर्णांक rx_count = 0;

	send_rcv_posts_अगर_needed(devdata);
	service_resp_queue(devdata->cmdrsp, devdata, &rx_count, budget);

	/* If there aren't any more packets to receive stop the poll */
	अगर (rx_count < budget)
		napi_complete_करोne(napi, rx_count);

	वापस rx_count;
पूर्ण

/* visornic_channel_पूर्णांकerrupt	- checks the status of the response queue
 *
 * Main function of the vnic_incoming thपढ़ो. Periodically check the response
 * queue and drain it अगर needed.
 */
अटल व्योम visornic_channel_पूर्णांकerrupt(काष्ठा visor_device *dev)
अणु
	काष्ठा visornic_devdata *devdata = dev_get_drvdata(&dev->device);

	अगर (!devdata)
		वापस;

	अगर (!visorchannel_संकेतempty(
				   devdata->dev->visorchannel,
				   IOCHAN_FROM_IOPART))
		napi_schedule(&devdata->napi);

	atomic_set(&devdata->पूर्णांकerrupt_rcvd, 0);

पूर्ण

/* visornic_probe - probe function क्रम visornic devices
 * @dev: The visor device discovered.
 *
 * Called when visorbus discovers a visornic device on its bus. It creates a new
 * visornic ethernet adapter.
 *
 * Return: 0 on success, or negative पूर्णांकeger on error.
 */
अटल पूर्णांक visornic_probe(काष्ठा visor_device *dev)
अणु
	काष्ठा visornic_devdata *devdata = शून्य;
	काष्ठा net_device *netdev = शून्य;
	पूर्णांक err;
	पूर्णांक channel_offset = 0;
	u64 features;

	netdev = alloc_etherdev(माप(काष्ठा visornic_devdata));
	अगर (!netdev) अणु
		dev_err(&dev->device,
			"%s alloc_etherdev failed\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	netdev->netdev_ops = &visornic_dev_ops;
	netdev->watchकरोg_समयo = 5 * HZ;
	SET_NETDEV_DEV(netdev, &dev->device);

	/* Get MAC address from channel and पढ़ो it पूर्णांकo the device. */
	netdev->addr_len = ETH_ALEN;
	channel_offset = दुरत्व(काष्ठा visor_io_channel, vnic.macaddr);
	err = visorbus_पढ़ो_channel(dev, channel_offset, netdev->dev_addr,
				    ETH_ALEN);
	अगर (err < 0) अणु
		dev_err(&dev->device,
			"%s failed to get mac addr from chan (%d)\n",
			__func__, err);
		जाओ cleanup_netdev;
	पूर्ण

	devdata = devdata_initialize(netdev_priv(netdev), dev);
	अगर (!devdata) अणु
		dev_err(&dev->device,
			"%s devdata_initialize failed\n", __func__);
		err = -ENOMEM;
		जाओ cleanup_netdev;
	पूर्ण
	/* करोn't trust messages laying around in the channel */
	drain_resp_queue(devdata->cmdrsp, devdata);

	devdata->netdev = netdev;
	dev_set_drvdata(&dev->device, devdata);
	init_रुकोqueue_head(&devdata->rsp_queue);
	spin_lock_init(&devdata->priv_lock);
	/* not yet */
	devdata->enabled = 0;
	atomic_set(&devdata->usage, 1);

	/* Setup rcv bufs */
	channel_offset = दुरत्व(काष्ठा visor_io_channel, vnic.num_rcv_bufs);
	err = visorbus_पढ़ो_channel(dev, channel_offset,
				    &devdata->num_rcv_bufs, 4);
	अगर (err) अणु
		dev_err(&dev->device,
			"%s failed to get #rcv bufs from chan (%d)\n",
			__func__, err);
		जाओ cleanup_netdev;
	पूर्ण

	devdata->rcvbuf = kसुस्मृति(devdata->num_rcv_bufs,
				  माप(काष्ठा sk_buff *), GFP_KERNEL);
	अगर (!devdata->rcvbuf) अणु
		err = -ENOMEM;
		जाओ cleanup_netdev;
	पूर्ण

	/* set the net_xmit outstanding threshold
	 * always leave two slots खोलो but you should have 3 at a minimum
	 * note that max_outstanding_net_xmits must be > 0
	 */
	devdata->max_outstanding_net_xmits =
		max_t(अचिन्हित दीर्घ, 3, ((devdata->num_rcv_bufs / 3) - 2));
	devdata->upper_threshold_net_xmits =
		max_t(अचिन्हित दीर्घ,
		      2, (devdata->max_outstanding_net_xmits - 1));
	devdata->lower_threshold_net_xmits =
		max_t(अचिन्हित दीर्घ,
		      1, (devdata->max_outstanding_net_xmits / 2));

	skb_queue_head_init(&devdata->xmitbufhead);

	/* create a cmdrsp we can use to post and unpost rcv buffers */
	devdata->cmdrsp_rcv = kदो_स्मृति(SIZखातापूर्ण_CMDRSP, GFP_KERNEL);
	अगर (!devdata->cmdrsp_rcv) अणु
		err = -ENOMEM;
		जाओ cleanup_rcvbuf;
	पूर्ण
	devdata->xmit_cmdrsp = kदो_स्मृति(SIZखातापूर्ण_CMDRSP, GFP_KERNEL);
	अगर (!devdata->xmit_cmdrsp) अणु
		err = -ENOMEM;
		जाओ cleanup_cmdrsp_rcv;
	पूर्ण
	INIT_WORK(&devdata->समयout_reset, visornic_समयout_reset);
	devdata->server_करोwn = false;
	devdata->server_change_state = false;

	/*set the शेष mtu */
	channel_offset = दुरत्व(काष्ठा visor_io_channel, vnic.mtu);
	err = visorbus_पढ़ो_channel(dev, channel_offset, &netdev->mtu, 4);
	अगर (err) अणु
		dev_err(&dev->device,
			"%s failed to get mtu from chan (%d)\n",
			__func__, err);
		जाओ cleanup_xmit_cmdrsp;
	पूर्ण

	/* TODO: Setup Interrupt inक्रमmation */
	/* Let's start our thपढ़ोs to get responses */
	netअगर_napi_add(netdev, &devdata->napi, visornic_poll, NAPI_WEIGHT);

	channel_offset = दुरत्व(काष्ठा visor_io_channel,
				  channel_header.features);
	err = visorbus_पढ़ो_channel(dev, channel_offset, &features, 8);
	अगर (err) अणु
		dev_err(&dev->device,
			"%s failed to get features from chan (%d)\n",
			__func__, err);
		जाओ cleanup_napi_add;
	पूर्ण

	features |= VISOR_CHANNEL_IS_POLLING;
	features |= VISOR_DRIVER_ENHANCED_RCVBUF_CHECKING;
	err = visorbus_ग_लिखो_channel(dev, channel_offset, &features, 8);
	अगर (err) अणु
		dev_err(&dev->device,
			"%s failed to set features in chan (%d)\n",
			__func__, err);
		जाओ cleanup_napi_add;
	पूर्ण

	/* Note: Interrupts have to be enable beक्रमe the जबतक
	 * loop below because the napi routine is responsible क्रम
	 * setting enab_dis_acked
	 */
	visorbus_enable_channel_पूर्णांकerrupts(dev);

	err = रेजिस्टर_netdev(netdev);
	अगर (err) अणु
		dev_err(&dev->device,
			"%s register_netdev failed (%d)\n", __func__, err);
		जाओ cleanup_napi_add;
	पूर्ण

	/* create debug/sysfs directories */
	devdata->eth_debugfs_dir = debugfs_create_dir(netdev->name,
						      visornic_debugfs_dir);
	अगर (!devdata->eth_debugfs_dir) अणु
		dev_err(&dev->device,
			"%s debugfs_create_dir %s failed\n",
			__func__, netdev->name);
		err = -ENOMEM;
		जाओ cleanup_रेजिस्टर_netdev;
	पूर्ण

	dev_info(&dev->device, "%s success netdev=%s\n",
		 __func__, netdev->name);
	वापस 0;

cleanup_रेजिस्टर_netdev:
	unरेजिस्टर_netdev(netdev);

cleanup_napi_add:
	visorbus_disable_channel_पूर्णांकerrupts(dev);
	netअगर_napi_del(&devdata->napi);

cleanup_xmit_cmdrsp:
	kमुक्त(devdata->xmit_cmdrsp);

cleanup_cmdrsp_rcv:
	kमुक्त(devdata->cmdrsp_rcv);

cleanup_rcvbuf:
	kमुक्त(devdata->rcvbuf);

cleanup_netdev:
	मुक्त_netdev(netdev);
	वापस err;
पूर्ण

/* host_side_disappeared - IO Partition is gone
 * @devdata: Device object.
 *
 * IO partition servicing this device is gone; करो cleanup.
 */
अटल व्योम host_side_disappeared(काष्ठा visornic_devdata *devdata)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&devdata->priv_lock, flags);
	/* indicate device destroyed */
	devdata->dev = शून्य;
	spin_unlock_irqrestore(&devdata->priv_lock, flags);
पूर्ण

/* visornic_हटाओ - called when visornic dev goes away
 * @dev: Visornic device that is being हटाओd.
 *
 * Called when DEVICE_DESTROY माला_लो called to हटाओ device.
 */
अटल व्योम visornic_हटाओ(काष्ठा visor_device *dev)
अणु
	काष्ठा visornic_devdata *devdata = dev_get_drvdata(&dev->device);
	काष्ठा net_device *netdev;
	अचिन्हित दीर्घ flags;

	अगर (!devdata) अणु
		dev_err(&dev->device, "%s no devdata\n", __func__);
		वापस;
	पूर्ण
	spin_lock_irqsave(&devdata->priv_lock, flags);
	अगर (devdata->going_away) अणु
		spin_unlock_irqrestore(&devdata->priv_lock, flags);
		dev_err(&dev->device, "%s already being removed\n", __func__);
		वापस;
	पूर्ण
	devdata->going_away = true;
	spin_unlock_irqrestore(&devdata->priv_lock, flags);
	netdev = devdata->netdev;
	अगर (!netdev) अणु
		dev_err(&dev->device, "%s not net device\n", __func__);
		वापस;
	पूर्ण

	/* going_away prevents new items being added to the workqueues */
	cancel_work_sync(&devdata->समयout_reset);

	debugfs_हटाओ_recursive(devdata->eth_debugfs_dir);
	/* this will call visornic_बंद() */
	unरेजिस्टर_netdev(netdev);

	visorbus_disable_channel_पूर्णांकerrupts(devdata->dev);
	netअगर_napi_del(&devdata->napi);

	dev_set_drvdata(&dev->device, शून्य);
	host_side_disappeared(devdata);
	devdata_release(devdata);
	मुक्त_netdev(netdev);
पूर्ण

/* visornic_छोड़ो - called when IO Part disappears
 * @dev:	   Visornic device that is being serviced.
 * @complete_func: Call when finished.
 *
 * Called when the IO Partition has gone करोwn. Need to मुक्त up resources and
 * रुको क्रम IO partition to come back. Mark link as करोwn and करोn't attempt any
 * DMA. When we have मुक्तd memory, call the complete_func so that Command knows
 * we are करोne. If we करोn't call complete_func, the IO Partition will never
 * come back.
 *
 * Return: 0 on success.
 */
अटल पूर्णांक visornic_छोड़ो(काष्ठा visor_device *dev,
			  visorbus_state_complete_func complete_func)
अणु
	काष्ठा visornic_devdata *devdata = dev_get_drvdata(&dev->device);

	visornic_serverकरोwn(devdata, complete_func);
	वापस 0;
पूर्ण

/* visornic_resume - called when IO Partition has recovered
 * @dev:	   Visornic device that is being serviced.
 * @compelte_func: Call when finished.
 *
 * Called when the IO partition has recovered. Re-establish connection to the IO
 * Partition and set the link up. Okay to करो DMA again.
 *
 * Returns 0 क्रम success, negative पूर्णांकeger on error.
 */
अटल पूर्णांक visornic_resume(काष्ठा visor_device *dev,
			   visorbus_state_complete_func complete_func)
अणु
	काष्ठा visornic_devdata *devdata;
	काष्ठा net_device *netdev;
	अचिन्हित दीर्घ flags;

	devdata = dev_get_drvdata(&dev->device);
	अगर (!devdata) अणु
		dev_err(&dev->device, "%s no devdata\n", __func__);
		वापस -EINVAL;
	पूर्ण

	netdev = devdata->netdev;

	spin_lock_irqsave(&devdata->priv_lock, flags);
	अगर (devdata->server_change_state) अणु
		spin_unlock_irqrestore(&devdata->priv_lock, flags);
		dev_err(&dev->device, "%s server already changing state\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	अगर (!devdata->server_करोwn) अणु
		spin_unlock_irqrestore(&devdata->priv_lock, flags);
		dev_err(&dev->device, "%s server not down\n", __func__);
		complete_func(dev, 0);
		वापस 0;
	पूर्ण
	devdata->server_change_state = true;
	spin_unlock_irqrestore(&devdata->priv_lock, flags);

	/* Must transition channel to ATTACHED state BEFORE
	 * we can start using the device again.
	 * TODO: State transitions
	 */
	visorbus_enable_channel_पूर्णांकerrupts(dev);

	rtnl_lock();
	dev_खोलो(netdev, शून्य);
	rtnl_unlock();

	complete_func(dev, 0);
	वापस 0;
पूर्ण

/* This is used to tell the visorbus driver which types of visor devices
 * we support, and what functions to call when a visor device that we support
 * is attached or हटाओd.
 */
अटल काष्ठा visor_driver visornic_driver = अणु
	.name = "visornic",
	.owner = THIS_MODULE,
	.channel_types = visornic_channel_types,
	.probe = visornic_probe,
	.हटाओ = visornic_हटाओ,
	.छोड़ो = visornic_छोड़ो,
	.resume = visornic_resume,
	.channel_पूर्णांकerrupt = visornic_channel_पूर्णांकerrupt,
पूर्ण;

/* visornic_init - init function
 *
 * Init function क्रम the visornic driver. Do initial driver setup and रुको
 * क्रम devices.
 *
 * Return: 0 on success, negative पूर्णांकeger on error.
 */
अटल पूर्णांक visornic_init(व्योम)
अणु
	पूर्णांक err;

	visornic_debugfs_dir = debugfs_create_dir("visornic", शून्य);

	debugfs_create_file("info", 0400, visornic_debugfs_dir, शून्य,
			    &debugfs_info_fops);
	debugfs_create_file("enable_ints", 0200, visornic_debugfs_dir, शून्य,
			    &debugfs_enable_पूर्णांकs_fops);

	err = visorbus_रेजिस्टर_visor_driver(&visornic_driver);
	अगर (err)
		debugfs_हटाओ_recursive(visornic_debugfs_dir);

	वापस err;
पूर्ण

/* visornic_cleanup - driver निकास routine
 *
 * Unरेजिस्टर driver from the bus and मुक्त up memory.
 */
अटल व्योम visornic_cleanup(व्योम)
अणु
	visorbus_unरेजिस्टर_visor_driver(&visornic_driver);
	debugfs_हटाओ_recursive(visornic_debugfs_dir);
पूर्ण

module_init(visornic_init);
module_निकास(visornic_cleanup);

MODULE_AUTHOR("Unisys");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("s-Par NIC driver for virtual network devices");
