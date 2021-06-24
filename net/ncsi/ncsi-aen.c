<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright Gavin Shan, IBM Corporation 2016.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>

#समावेश <net/ncsi.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>

#समावेश "internal.h"
#समावेश "ncsi-pkt.h"

अटल पूर्णांक ncsi_validate_aen_pkt(काष्ठा ncsi_aen_pkt_hdr *h,
				 स्थिर अचिन्हित लघु payload)
अणु
	u32 checksum;
	__be32 *pchecksum;

	अगर (h->common.revision != NCSI_PKT_REVISION)
		वापस -EINVAL;
	अगर (ntohs(h->common.length) != payload)
		वापस -EINVAL;

	/* Validate checksum, which might be zeroes अगर the
	 * sender करोesn't support checksum according to NCSI
	 * specअगरication.
	 */
	pchecksum = (__be32 *)((व्योम *)(h + 1) + payload - 4);
	अगर (ntohl(*pchecksum) == 0)
		वापस 0;

	checksum = ncsi_calculate_checksum((अचिन्हित अक्षर *)h,
					   माप(*h) + payload - 4);
	अगर (*pchecksum != htonl(checksum))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_aen_handler_lsc(काष्ठा ncsi_dev_priv *ndp,
				काष्ठा ncsi_aen_pkt_hdr *h)
अणु
	काष्ठा ncsi_channel *nc, *पंचांगp;
	काष्ठा ncsi_channel_mode *ncm;
	अचिन्हित दीर्घ old_data, data;
	काष्ठा ncsi_aen_lsc_pkt *lsc;
	काष्ठा ncsi_package *np;
	bool had_link, has_link;
	अचिन्हित दीर्घ flags;
	bool chained;
	पूर्णांक state;

	/* Find the NCSI channel */
	ncsi_find_package_and_channel(ndp, h->common.channel, शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	/* Update the link status */
	lsc = (काष्ठा ncsi_aen_lsc_pkt *)h;

	spin_lock_irqsave(&nc->lock, flags);
	ncm = &nc->modes[NCSI_MODE_LINK];
	old_data = ncm->data[2];
	data = ntohl(lsc->status);
	ncm->data[2] = data;
	ncm->data[4] = ntohl(lsc->oem_status);

	had_link = !!(old_data & 0x1);
	has_link = !!(data & 0x1);

	netdev_dbg(ndp->ndev.dev, "NCSI: LSC AEN - channel %u state %s\n",
		   nc->id, data & 0x1 ? "up" : "down");

	chained = !list_empty(&nc->link);
	state = nc->state;
	spin_unlock_irqrestore(&nc->lock, flags);

	अगर (state == NCSI_CHANNEL_INACTIVE)
		netdev_warn(ndp->ndev.dev,
			    "NCSI: Inactive channel %u received AEN!\n",
			    nc->id);

	अगर ((had_link == has_link) || chained)
		वापस 0;

	अगर (!ndp->multi_package && !nc->package->multi_channel) अणु
		अगर (had_link) अणु
			ndp->flags |= NCSI_DEV_RESHUFFLE;
			ncsi_stop_channel_monitor(nc);
			spin_lock_irqsave(&ndp->lock, flags);
			list_add_tail_rcu(&nc->link, &ndp->channel_queue);
			spin_unlock_irqrestore(&ndp->lock, flags);
			वापस ncsi_process_next_channel(ndp);
		पूर्ण
		/* Configured channel came up */
		वापस 0;
	पूर्ण

	अगर (had_link) अणु
		ncm = &nc->modes[NCSI_MODE_TX_ENABLE];
		अगर (ncsi_channel_is_last(ndp, nc)) अणु
			/* No channels left, reconfigure */
			वापस ncsi_reset_dev(&ndp->ndev);
		पूर्ण अन्यथा अगर (ncm->enable) अणु
			/* Need to failover Tx channel */
			ncsi_update_tx_channel(ndp, nc->package, nc, शून्य);
		पूर्ण
	पूर्ण अन्यथा अगर (has_link && nc->package->preferred_channel == nc) अणु
		/* Return Tx to preferred channel */
		ncsi_update_tx_channel(ndp, nc->package, शून्य, nc);
	पूर्ण अन्यथा अगर (has_link) अणु
		NCSI_FOR_EACH_PACKAGE(ndp, np) अणु
			NCSI_FOR_EACH_CHANNEL(np, पंचांगp) अणु
				/* Enable Tx on this channel अगर the current Tx
				 * channel is करोwn.
				 */
				ncm = &पंचांगp->modes[NCSI_MODE_TX_ENABLE];
				अगर (ncm->enable &&
				    !ncsi_channel_has_link(पंचांगp)) अणु
					ncsi_update_tx_channel(ndp, nc->package,
							       पंचांगp, nc);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* Leave configured channels active in a multi-channel scenario so
	 * AEN events are still received.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_aen_handler_cr(काष्ठा ncsi_dev_priv *ndp,
			       काष्ठा ncsi_aen_pkt_hdr *h)
अणु
	काष्ठा ncsi_channel *nc;
	अचिन्हित दीर्घ flags;

	/* Find the NCSI channel */
	ncsi_find_package_and_channel(ndp, h->common.channel, शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	spin_lock_irqsave(&nc->lock, flags);
	अगर (!list_empty(&nc->link) ||
	    nc->state != NCSI_CHANNEL_ACTIVE) अणु
		spin_unlock_irqrestore(&nc->lock, flags);
		वापस 0;
	पूर्ण
	spin_unlock_irqrestore(&nc->lock, flags);

	ncsi_stop_channel_monitor(nc);
	spin_lock_irqsave(&nc->lock, flags);
	nc->state = NCSI_CHANNEL_INVISIBLE;
	spin_unlock_irqrestore(&nc->lock, flags);

	spin_lock_irqsave(&ndp->lock, flags);
	nc->state = NCSI_CHANNEL_INACTIVE;
	list_add_tail_rcu(&nc->link, &ndp->channel_queue);
	spin_unlock_irqrestore(&ndp->lock, flags);

	वापस ncsi_process_next_channel(ndp);
पूर्ण

अटल पूर्णांक ncsi_aen_handler_hncdsc(काष्ठा ncsi_dev_priv *ndp,
				   काष्ठा ncsi_aen_pkt_hdr *h)
अणु
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_channel_mode *ncm;
	काष्ठा ncsi_aen_hncdsc_pkt *hncdsc;
	अचिन्हित दीर्घ flags;

	/* Find the NCSI channel */
	ncsi_find_package_and_channel(ndp, h->common.channel, शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	spin_lock_irqsave(&nc->lock, flags);
	ncm = &nc->modes[NCSI_MODE_LINK];
	hncdsc = (काष्ठा ncsi_aen_hncdsc_pkt *)h;
	ncm->data[3] = ntohl(hncdsc->status);
	spin_unlock_irqrestore(&nc->lock, flags);
	netdev_dbg(ndp->ndev.dev,
		   "NCSI: host driver %srunning on channel %u\n",
		   ncm->data[3] & 0x1 ? "" : "not ", nc->id);

	वापस 0;
पूर्ण

अटल काष्ठा ncsi_aen_handler अणु
	अचिन्हित अक्षर type;
	पूर्णांक           payload;
	पूर्णांक           (*handler)(काष्ठा ncsi_dev_priv *ndp,
				 काष्ठा ncsi_aen_pkt_hdr *h);
पूर्ण ncsi_aen_handlers[] = अणु
	अणु NCSI_PKT_AEN_LSC,    12, ncsi_aen_handler_lsc    पूर्ण,
	अणु NCSI_PKT_AEN_CR,      4, ncsi_aen_handler_cr     पूर्ण,
	अणु NCSI_PKT_AEN_HNCDSC,  8, ncsi_aen_handler_hncdsc पूर्ण
पूर्ण;

पूर्णांक ncsi_aen_handler(काष्ठा ncsi_dev_priv *ndp, काष्ठा sk_buff *skb)
अणु
	काष्ठा ncsi_aen_pkt_hdr *h;
	काष्ठा ncsi_aen_handler *nah = शून्य;
	पूर्णांक i, ret;

	/* Find the handler */
	h = (काष्ठा ncsi_aen_pkt_hdr *)skb_network_header(skb);
	क्रम (i = 0; i < ARRAY_SIZE(ncsi_aen_handlers); i++) अणु
		अगर (ncsi_aen_handlers[i].type == h->type) अणु
			nah = &ncsi_aen_handlers[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!nah) अणु
		netdev_warn(ndp->ndev.dev, "Invalid AEN (0x%x) received\n",
			    h->type);
		वापस -ENOENT;
	पूर्ण

	ret = ncsi_validate_aen_pkt(h, nah->payload);
	अगर (ret) अणु
		netdev_warn(ndp->ndev.dev,
			    "NCSI: 'bad' packet ignored for AEN type 0x%x\n",
			    h->type);
		जाओ out;
	पूर्ण

	ret = nah->handler(ndp, h);
	अगर (ret)
		netdev_err(ndp->ndev.dev,
			   "NCSI: Handler for AEN type 0x%x returned %d\n",
			   h->type, ret);
out:
	consume_skb(skb);
	वापस ret;
पूर्ण
