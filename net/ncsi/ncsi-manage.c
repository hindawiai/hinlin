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
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <net/ncsi.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <net/addrconf.h>
#समावेश <net/ipv6.h>
#समावेश <net/genetlink.h>

#समावेश "internal.h"
#समावेश "ncsi-pkt.h"
#समावेश "ncsi-netlink.h"

LIST_HEAD(ncsi_dev_list);
DEFINE_SPINLOCK(ncsi_dev_lock);

bool ncsi_channel_has_link(काष्ठा ncsi_channel *channel)
अणु
	वापस !!(channel->modes[NCSI_MODE_LINK].data[2] & 0x1);
पूर्ण

bool ncsi_channel_is_last(काष्ठा ncsi_dev_priv *ndp,
			  काष्ठा ncsi_channel *channel)
अणु
	काष्ठा ncsi_package *np;
	काष्ठा ncsi_channel *nc;

	NCSI_FOR_EACH_PACKAGE(ndp, np)
		NCSI_FOR_EACH_CHANNEL(np, nc) अणु
			अगर (nc == channel)
				जारी;
			अगर (nc->state == NCSI_CHANNEL_ACTIVE &&
			    ncsi_channel_has_link(nc))
				वापस false;
		पूर्ण

	वापस true;
पूर्ण

अटल व्योम ncsi_report_link(काष्ठा ncsi_dev_priv *ndp, bool क्रमce_करोwn)
अणु
	काष्ठा ncsi_dev *nd = &ndp->ndev;
	काष्ठा ncsi_package *np;
	काष्ठा ncsi_channel *nc;
	अचिन्हित दीर्घ flags;

	nd->state = ncsi_dev_state_functional;
	अगर (क्रमce_करोwn) अणु
		nd->link_up = 0;
		जाओ report;
	पूर्ण

	nd->link_up = 0;
	NCSI_FOR_EACH_PACKAGE(ndp, np) अणु
		NCSI_FOR_EACH_CHANNEL(np, nc) अणु
			spin_lock_irqsave(&nc->lock, flags);

			अगर (!list_empty(&nc->link) ||
			    nc->state != NCSI_CHANNEL_ACTIVE) अणु
				spin_unlock_irqrestore(&nc->lock, flags);
				जारी;
			पूर्ण

			अगर (ncsi_channel_has_link(nc)) अणु
				spin_unlock_irqrestore(&nc->lock, flags);
				nd->link_up = 1;
				जाओ report;
			पूर्ण

			spin_unlock_irqrestore(&nc->lock, flags);
		पूर्ण
	पूर्ण

report:
	nd->handler(nd);
पूर्ण

अटल व्योम ncsi_channel_monitor(काष्ठा समयr_list *t)
अणु
	काष्ठा ncsi_channel *nc = from_समयr(nc, t, monitor.समयr);
	काष्ठा ncsi_package *np = nc->package;
	काष्ठा ncsi_dev_priv *ndp = np->ndp;
	काष्ठा ncsi_channel_mode *ncm;
	काष्ठा ncsi_cmd_arg nca;
	bool enabled, chained;
	अचिन्हित पूर्णांक monitor_state;
	अचिन्हित दीर्घ flags;
	पूर्णांक state, ret;

	spin_lock_irqsave(&nc->lock, flags);
	state = nc->state;
	chained = !list_empty(&nc->link);
	enabled = nc->monitor.enabled;
	monitor_state = nc->monitor.state;
	spin_unlock_irqrestore(&nc->lock, flags);

	अगर (!enabled)
		वापस;		/* expected race disabling समयr */
	अगर (WARN_ON_ONCE(chained))
		जाओ bad_state;

	अगर (state != NCSI_CHANNEL_INACTIVE &&
	    state != NCSI_CHANNEL_ACTIVE) अणु
bad_state:
		netdev_warn(ndp->ndev.dev,
			    "Bad NCSI monitor state channel %d 0x%x %s queue\n",
			    nc->id, state, chained ? "on" : "off");
		spin_lock_irqsave(&nc->lock, flags);
		nc->monitor.enabled = false;
		spin_unlock_irqrestore(&nc->lock, flags);
		वापस;
	पूर्ण

	चयन (monitor_state) अणु
	हाल NCSI_CHANNEL_MONITOR_START:
	हाल NCSI_CHANNEL_MONITOR_RETRY:
		nca.ndp = ndp;
		nca.package = np->id;
		nca.channel = nc->id;
		nca.type = NCSI_PKT_CMD_GLS;
		nca.req_flags = 0;
		ret = ncsi_xmit_cmd(&nca);
		अगर (ret)
			netdev_err(ndp->ndev.dev, "Error %d sending GLS\n",
				   ret);
		अवरोध;
	हाल NCSI_CHANNEL_MONITOR_WAIT ... NCSI_CHANNEL_MONITOR_WAIT_MAX:
		अवरोध;
	शेष:
		netdev_err(ndp->ndev.dev, "NCSI Channel %d timed out!\n",
			   nc->id);
		ncsi_report_link(ndp, true);
		ndp->flags |= NCSI_DEV_RESHUFFLE;

		ncm = &nc->modes[NCSI_MODE_LINK];
		spin_lock_irqsave(&nc->lock, flags);
		nc->monitor.enabled = false;
		nc->state = NCSI_CHANNEL_INVISIBLE;
		ncm->data[2] &= ~0x1;
		spin_unlock_irqrestore(&nc->lock, flags);

		spin_lock_irqsave(&ndp->lock, flags);
		nc->state = NCSI_CHANNEL_ACTIVE;
		list_add_tail_rcu(&nc->link, &ndp->channel_queue);
		spin_unlock_irqrestore(&ndp->lock, flags);
		ncsi_process_next_channel(ndp);
		वापस;
	पूर्ण

	spin_lock_irqsave(&nc->lock, flags);
	nc->monitor.state++;
	spin_unlock_irqrestore(&nc->lock, flags);
	mod_समयr(&nc->monitor.समयr, jअगरfies + HZ);
पूर्ण

व्योम ncsi_start_channel_monitor(काष्ठा ncsi_channel *nc)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&nc->lock, flags);
	WARN_ON_ONCE(nc->monitor.enabled);
	nc->monitor.enabled = true;
	nc->monitor.state = NCSI_CHANNEL_MONITOR_START;
	spin_unlock_irqrestore(&nc->lock, flags);

	mod_समयr(&nc->monitor.समयr, jअगरfies + HZ);
पूर्ण

व्योम ncsi_stop_channel_monitor(काष्ठा ncsi_channel *nc)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&nc->lock, flags);
	अगर (!nc->monitor.enabled) अणु
		spin_unlock_irqrestore(&nc->lock, flags);
		वापस;
	पूर्ण
	nc->monitor.enabled = false;
	spin_unlock_irqrestore(&nc->lock, flags);

	del_समयr_sync(&nc->monitor.समयr);
पूर्ण

काष्ठा ncsi_channel *ncsi_find_channel(काष्ठा ncsi_package *np,
				       अचिन्हित अक्षर id)
अणु
	काष्ठा ncsi_channel *nc;

	NCSI_FOR_EACH_CHANNEL(np, nc) अणु
		अगर (nc->id == id)
			वापस nc;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा ncsi_channel *ncsi_add_channel(काष्ठा ncsi_package *np, अचिन्हित अक्षर id)
अणु
	काष्ठा ncsi_channel *nc, *पंचांगp;
	पूर्णांक index;
	अचिन्हित दीर्घ flags;

	nc = kzalloc(माप(*nc), GFP_ATOMIC);
	अगर (!nc)
		वापस शून्य;

	nc->id = id;
	nc->package = np;
	nc->state = NCSI_CHANNEL_INACTIVE;
	nc->monitor.enabled = false;
	समयr_setup(&nc->monitor.समयr, ncsi_channel_monitor, 0);
	spin_lock_init(&nc->lock);
	INIT_LIST_HEAD(&nc->link);
	क्रम (index = 0; index < NCSI_CAP_MAX; index++)
		nc->caps[index].index = index;
	क्रम (index = 0; index < NCSI_MODE_MAX; index++)
		nc->modes[index].index = index;

	spin_lock_irqsave(&np->lock, flags);
	पंचांगp = ncsi_find_channel(np, id);
	अगर (पंचांगp) अणु
		spin_unlock_irqrestore(&np->lock, flags);
		kमुक्त(nc);
		वापस पंचांगp;
	पूर्ण

	list_add_tail_rcu(&nc->node, &np->channels);
	np->channel_num++;
	spin_unlock_irqrestore(&np->lock, flags);

	वापस nc;
पूर्ण

अटल व्योम ncsi_हटाओ_channel(काष्ठा ncsi_channel *nc)
अणु
	काष्ठा ncsi_package *np = nc->package;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&nc->lock, flags);

	/* Release filters */
	kमुक्त(nc->mac_filter.addrs);
	kमुक्त(nc->vlan_filter.vids);

	nc->state = NCSI_CHANNEL_INACTIVE;
	spin_unlock_irqrestore(&nc->lock, flags);
	ncsi_stop_channel_monitor(nc);

	/* Remove and मुक्त channel */
	spin_lock_irqsave(&np->lock, flags);
	list_del_rcu(&nc->node);
	np->channel_num--;
	spin_unlock_irqrestore(&np->lock, flags);

	kमुक्त(nc);
पूर्ण

काष्ठा ncsi_package *ncsi_find_package(काष्ठा ncsi_dev_priv *ndp,
				       अचिन्हित अक्षर id)
अणु
	काष्ठा ncsi_package *np;

	NCSI_FOR_EACH_PACKAGE(ndp, np) अणु
		अगर (np->id == id)
			वापस np;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा ncsi_package *ncsi_add_package(काष्ठा ncsi_dev_priv *ndp,
				      अचिन्हित अक्षर id)
अणु
	काष्ठा ncsi_package *np, *पंचांगp;
	अचिन्हित दीर्घ flags;

	np = kzalloc(माप(*np), GFP_ATOMIC);
	अगर (!np)
		वापस शून्य;

	np->id = id;
	np->ndp = ndp;
	spin_lock_init(&np->lock);
	INIT_LIST_HEAD(&np->channels);
	np->channel_whitelist = अच_पूर्णांक_उच्च;

	spin_lock_irqsave(&ndp->lock, flags);
	पंचांगp = ncsi_find_package(ndp, id);
	अगर (पंचांगp) अणु
		spin_unlock_irqrestore(&ndp->lock, flags);
		kमुक्त(np);
		वापस पंचांगp;
	पूर्ण

	list_add_tail_rcu(&np->node, &ndp->packages);
	ndp->package_num++;
	spin_unlock_irqrestore(&ndp->lock, flags);

	वापस np;
पूर्ण

व्योम ncsi_हटाओ_package(काष्ठा ncsi_package *np)
अणु
	काष्ठा ncsi_dev_priv *ndp = np->ndp;
	काष्ठा ncsi_channel *nc, *पंचांगp;
	अचिन्हित दीर्घ flags;

	/* Release all child channels */
	list_क्रम_each_entry_safe(nc, पंचांगp, &np->channels, node)
		ncsi_हटाओ_channel(nc);

	/* Remove and मुक्त package */
	spin_lock_irqsave(&ndp->lock, flags);
	list_del_rcu(&np->node);
	ndp->package_num--;
	spin_unlock_irqrestore(&ndp->lock, flags);

	kमुक्त(np);
पूर्ण

व्योम ncsi_find_package_and_channel(काष्ठा ncsi_dev_priv *ndp,
				   अचिन्हित अक्षर id,
				   काष्ठा ncsi_package **np,
				   काष्ठा ncsi_channel **nc)
अणु
	काष्ठा ncsi_package *p;
	काष्ठा ncsi_channel *c;

	p = ncsi_find_package(ndp, NCSI_PACKAGE_INDEX(id));
	c = p ? ncsi_find_channel(p, NCSI_CHANNEL_INDEX(id)) : शून्य;

	अगर (np)
		*np = p;
	अगर (nc)
		*nc = c;
पूर्ण

/* For two consecutive NCSI commands, the packet IDs shouldn't
 * be same. Otherwise, the bogus response might be replied. So
 * the available IDs are allocated in round-robin fashion.
 */
काष्ठा ncsi_request *ncsi_alloc_request(काष्ठा ncsi_dev_priv *ndp,
					अचिन्हित पूर्णांक req_flags)
अणु
	काष्ठा ncsi_request *nr = शून्य;
	पूर्णांक i, limit = ARRAY_SIZE(ndp->requests);
	अचिन्हित दीर्घ flags;

	/* Check अगर there is one available request until the उच्चमानing */
	spin_lock_irqsave(&ndp->lock, flags);
	क्रम (i = ndp->request_id; i < limit; i++) अणु
		अगर (ndp->requests[i].used)
			जारी;

		nr = &ndp->requests[i];
		nr->used = true;
		nr->flags = req_flags;
		ndp->request_id = i + 1;
		जाओ found;
	पूर्ण

	/* Fail back to check from the starting cursor */
	क्रम (i = NCSI_REQ_START_IDX; i < ndp->request_id; i++) अणु
		अगर (ndp->requests[i].used)
			जारी;

		nr = &ndp->requests[i];
		nr->used = true;
		nr->flags = req_flags;
		ndp->request_id = i + 1;
		जाओ found;
	पूर्ण

found:
	spin_unlock_irqrestore(&ndp->lock, flags);
	वापस nr;
पूर्ण

व्योम ncsi_मुक्त_request(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा sk_buff *cmd, *rsp;
	अचिन्हित दीर्घ flags;
	bool driven;

	अगर (nr->enabled) अणु
		nr->enabled = false;
		del_समयr_sync(&nr->समयr);
	पूर्ण

	spin_lock_irqsave(&ndp->lock, flags);
	cmd = nr->cmd;
	rsp = nr->rsp;
	nr->cmd = शून्य;
	nr->rsp = शून्य;
	nr->used = false;
	driven = !!(nr->flags & NCSI_REQ_FLAG_EVENT_DRIVEN);
	spin_unlock_irqrestore(&ndp->lock, flags);

	अगर (driven && cmd && --ndp->pending_req_num == 0)
		schedule_work(&ndp->work);

	/* Release command and response */
	consume_skb(cmd);
	consume_skb(rsp);
पूर्ण

काष्ठा ncsi_dev *ncsi_find_dev(काष्ठा net_device *dev)
अणु
	काष्ठा ncsi_dev_priv *ndp;

	NCSI_FOR_EACH_DEV(ndp) अणु
		अगर (ndp->ndev.dev == dev)
			वापस &ndp->ndev;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम ncsi_request_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा ncsi_request *nr = from_समयr(nr, t, समयr);
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_cmd_pkt *cmd;
	काष्ठा ncsi_package *np;
	काष्ठा ncsi_channel *nc;
	अचिन्हित दीर्घ flags;

	/* If the request alपढ़ोy had associated response,
	 * let the response handler to release it.
	 */
	spin_lock_irqsave(&ndp->lock, flags);
	nr->enabled = false;
	अगर (nr->rsp || !nr->cmd) अणु
		spin_unlock_irqrestore(&ndp->lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&ndp->lock, flags);

	अगर (nr->flags == NCSI_REQ_FLAG_NETLINK_DRIVEN) अणु
		अगर (nr->cmd) अणु
			/* Find the package */
			cmd = (काष्ठा ncsi_cmd_pkt *)
			      skb_network_header(nr->cmd);
			ncsi_find_package_and_channel(ndp,
						      cmd->cmd.common.channel,
						      &np, &nc);
			ncsi_send_netlink_समयout(nr, np, nc);
		पूर्ण
	पूर्ण

	/* Release the request */
	ncsi_मुक्त_request(nr);
पूर्ण

अटल व्योम ncsi_suspend_channel(काष्ठा ncsi_dev_priv *ndp)
अणु
	काष्ठा ncsi_dev *nd = &ndp->ndev;
	काष्ठा ncsi_package *np;
	काष्ठा ncsi_channel *nc, *पंचांगp;
	काष्ठा ncsi_cmd_arg nca;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	np = ndp->active_package;
	nc = ndp->active_channel;
	nca.ndp = ndp;
	nca.req_flags = NCSI_REQ_FLAG_EVENT_DRIVEN;
	चयन (nd->state) अणु
	हाल ncsi_dev_state_suspend:
		nd->state = ncsi_dev_state_suspend_select;
		fallthrough;
	हाल ncsi_dev_state_suspend_select:
		ndp->pending_req_num = 1;

		nca.type = NCSI_PKT_CMD_SP;
		nca.package = np->id;
		nca.channel = NCSI_RESERVED_CHANNEL;
		अगर (ndp->flags & NCSI_DEV_HWA)
			nca.bytes[0] = 0;
		अन्यथा
			nca.bytes[0] = 1;

		/* To retrieve the last link states of channels in current
		 * package when current active channel needs fail over to
		 * another one. It means we will possibly select another
		 * channel as next active one. The link states of channels
		 * are most important factor of the selection. So we need
		 * accurate link states. Unक्रमtunately, the link states on
		 * inactive channels can't be updated with LSC AEN in समय.
		 */
		अगर (ndp->flags & NCSI_DEV_RESHUFFLE)
			nd->state = ncsi_dev_state_suspend_gls;
		अन्यथा
			nd->state = ncsi_dev_state_suspend_dcnt;
		ret = ncsi_xmit_cmd(&nca);
		अगर (ret)
			जाओ error;

		अवरोध;
	हाल ncsi_dev_state_suspend_gls:
		ndp->pending_req_num = np->channel_num;

		nca.type = NCSI_PKT_CMD_GLS;
		nca.package = np->id;

		nd->state = ncsi_dev_state_suspend_dcnt;
		NCSI_FOR_EACH_CHANNEL(np, nc) अणु
			nca.channel = nc->id;
			ret = ncsi_xmit_cmd(&nca);
			अगर (ret)
				जाओ error;
		पूर्ण

		अवरोध;
	हाल ncsi_dev_state_suspend_dcnt:
		ndp->pending_req_num = 1;

		nca.type = NCSI_PKT_CMD_DCNT;
		nca.package = np->id;
		nca.channel = nc->id;

		nd->state = ncsi_dev_state_suspend_dc;
		ret = ncsi_xmit_cmd(&nca);
		अगर (ret)
			जाओ error;

		अवरोध;
	हाल ncsi_dev_state_suspend_dc:
		ndp->pending_req_num = 1;

		nca.type = NCSI_PKT_CMD_DC;
		nca.package = np->id;
		nca.channel = nc->id;
		nca.bytes[0] = 1;

		nd->state = ncsi_dev_state_suspend_deselect;
		ret = ncsi_xmit_cmd(&nca);
		अगर (ret)
			जाओ error;

		NCSI_FOR_EACH_CHANNEL(np, पंचांगp) अणु
			/* If there is another channel active on this package
			 * करो not deselect the package.
			 */
			अगर (पंचांगp != nc && पंचांगp->state == NCSI_CHANNEL_ACTIVE) अणु
				nd->state = ncsi_dev_state_suspend_करोne;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल ncsi_dev_state_suspend_deselect:
		ndp->pending_req_num = 1;

		nca.type = NCSI_PKT_CMD_DP;
		nca.package = np->id;
		nca.channel = NCSI_RESERVED_CHANNEL;

		nd->state = ncsi_dev_state_suspend_करोne;
		ret = ncsi_xmit_cmd(&nca);
		अगर (ret)
			जाओ error;

		अवरोध;
	हाल ncsi_dev_state_suspend_करोne:
		spin_lock_irqsave(&nc->lock, flags);
		nc->state = NCSI_CHANNEL_INACTIVE;
		spin_unlock_irqrestore(&nc->lock, flags);
		अगर (ndp->flags & NCSI_DEV_RESET)
			ncsi_reset_dev(nd);
		अन्यथा
			ncsi_process_next_channel(ndp);
		अवरोध;
	शेष:
		netdev_warn(nd->dev, "Wrong NCSI state 0x%x in suspend\n",
			    nd->state);
	पूर्ण

	वापस;
error:
	nd->state = ncsi_dev_state_functional;
पूर्ण

/* Check the VLAN filter biपंचांगap क्रम a set filter, and स्थिरruct a
 * "Set VLAN Filter - Disable" packet अगर found.
 */
अटल पूर्णांक clear_one_vid(काष्ठा ncsi_dev_priv *ndp, काष्ठा ncsi_channel *nc,
			 काष्ठा ncsi_cmd_arg *nca)
अणु
	काष्ठा ncsi_channel_vlan_filter *ncf;
	अचिन्हित दीर्घ flags;
	व्योम *biपंचांगap;
	पूर्णांक index;
	u16 vid;

	ncf = &nc->vlan_filter;
	biपंचांगap = &ncf->biपंचांगap;

	spin_lock_irqsave(&nc->lock, flags);
	index = find_next_bit(biपंचांगap, ncf->n_vids, 0);
	अगर (index >= ncf->n_vids) अणु
		spin_unlock_irqrestore(&nc->lock, flags);
		वापस -1;
	पूर्ण
	vid = ncf->vids[index];

	clear_bit(index, biपंचांगap);
	ncf->vids[index] = 0;
	spin_unlock_irqrestore(&nc->lock, flags);

	nca->type = NCSI_PKT_CMD_SVF;
	nca->words[1] = vid;
	/* HW filter index starts at 1 */
	nca->bytes[6] = index + 1;
	nca->bytes[7] = 0x00;
	वापस 0;
पूर्ण

/* Find an outstanding VLAN tag and स्थिरuct a "Set VLAN Filter - Enable"
 * packet.
 */
अटल पूर्णांक set_one_vid(काष्ठा ncsi_dev_priv *ndp, काष्ठा ncsi_channel *nc,
		       काष्ठा ncsi_cmd_arg *nca)
अणु
	काष्ठा ncsi_channel_vlan_filter *ncf;
	काष्ठा vlan_vid *vlan = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, index;
	व्योम *biपंचांगap;
	u16 vid;

	अगर (list_empty(&ndp->vlan_vids))
		वापस -1;

	ncf = &nc->vlan_filter;
	biपंचांगap = &ncf->biपंचांगap;

	spin_lock_irqsave(&nc->lock, flags);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(vlan, &ndp->vlan_vids, list) अणु
		vid = vlan->vid;
		क्रम (i = 0; i < ncf->n_vids; i++)
			अगर (ncf->vids[i] == vid) अणु
				vid = 0;
				अवरोध;
			पूर्ण
		अगर (vid)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (!vid) अणु
		/* No VLAN ID is not set */
		spin_unlock_irqrestore(&nc->lock, flags);
		वापस -1;
	पूर्ण

	index = find_next_zero_bit(biपंचांगap, ncf->n_vids, 0);
	अगर (index < 0 || index >= ncf->n_vids) अणु
		netdev_err(ndp->ndev.dev,
			   "Channel %u already has all VLAN filters set\n",
			   nc->id);
		spin_unlock_irqrestore(&nc->lock, flags);
		वापस -1;
	पूर्ण

	ncf->vids[index] = vid;
	set_bit(index, biपंचांगap);
	spin_unlock_irqrestore(&nc->lock, flags);

	nca->type = NCSI_PKT_CMD_SVF;
	nca->words[1] = vid;
	/* HW filter index starts at 1 */
	nca->bytes[6] = index + 1;
	nca->bytes[7] = 0x01;

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_NCSI_OEM_CMD_GET_MAC)

/* NCSI OEM Command APIs */
अटल पूर्णांक ncsi_oem_gma_handler_bcm(काष्ठा ncsi_cmd_arg *nca)
अणु
	अचिन्हित अक्षर data[NCSI_OEM_BCM_CMD_GMA_LEN];
	पूर्णांक ret = 0;

	nca->payload = NCSI_OEM_BCM_CMD_GMA_LEN;

	स_रखो(data, 0, NCSI_OEM_BCM_CMD_GMA_LEN);
	*(अचिन्हित पूर्णांक *)data = ntohl(NCSI_OEM_MFR_BCM_ID);
	data[5] = NCSI_OEM_BCM_CMD_GMA;

	nca->data = data;

	ret = ncsi_xmit_cmd(nca);
	अगर (ret)
		netdev_err(nca->ndp->ndev.dev,
			   "NCSI: Failed to transmit cmd 0x%x during configure\n",
			   nca->type);
	वापस ret;
पूर्ण

अटल पूर्णांक ncsi_oem_gma_handler_mlx(काष्ठा ncsi_cmd_arg *nca)
अणु
	जोड़ अणु
		u8 data_u8[NCSI_OEM_MLX_CMD_GMA_LEN];
		u32 data_u32[NCSI_OEM_MLX_CMD_GMA_LEN / माप(u32)];
	पूर्ण u;
	पूर्णांक ret = 0;

	nca->payload = NCSI_OEM_MLX_CMD_GMA_LEN;

	स_रखो(&u, 0, माप(u));
	u.data_u32[0] = ntohl(NCSI_OEM_MFR_MLX_ID);
	u.data_u8[5] = NCSI_OEM_MLX_CMD_GMA;
	u.data_u8[6] = NCSI_OEM_MLX_CMD_GMA_PARAM;

	nca->data = u.data_u8;

	ret = ncsi_xmit_cmd(nca);
	अगर (ret)
		netdev_err(nca->ndp->ndev.dev,
			   "NCSI: Failed to transmit cmd 0x%x during configure\n",
			   nca->type);
	वापस ret;
पूर्ण

अटल पूर्णांक ncsi_oem_smaf_mlx(काष्ठा ncsi_cmd_arg *nca)
अणु
	जोड़ अणु
		u8 data_u8[NCSI_OEM_MLX_CMD_SMAF_LEN];
		u32 data_u32[NCSI_OEM_MLX_CMD_SMAF_LEN / माप(u32)];
	पूर्ण u;
	पूर्णांक ret = 0;

	स_रखो(&u, 0, माप(u));
	u.data_u32[0] = ntohl(NCSI_OEM_MFR_MLX_ID);
	u.data_u8[5] = NCSI_OEM_MLX_CMD_SMAF;
	u.data_u8[6] = NCSI_OEM_MLX_CMD_SMAF_PARAM;
	स_नकल(&u.data_u8[MLX_SMAF_MAC_ADDR_OFFSET],
	       nca->ndp->ndev.dev->dev_addr,	ETH_ALEN);
	u.data_u8[MLX_SMAF_MED_SUPPORT_OFFSET] =
		(MLX_MC_RBT_AVL | MLX_MC_RBT_SUPPORT);

	nca->payload = NCSI_OEM_MLX_CMD_SMAF_LEN;
	nca->data = u.data_u8;

	ret = ncsi_xmit_cmd(nca);
	अगर (ret)
		netdev_err(nca->ndp->ndev.dev,
			   "NCSI: Failed to transmit cmd 0x%x during probe\n",
			   nca->type);
	वापस ret;
पूर्ण

/* OEM Command handlers initialization */
अटल काष्ठा ncsi_oem_gma_handler अणु
	अचिन्हित पूर्णांक	mfr_id;
	पूर्णांक		(*handler)(काष्ठा ncsi_cmd_arg *nca);
पूर्ण ncsi_oem_gma_handlers[] = अणु
	अणु NCSI_OEM_MFR_BCM_ID, ncsi_oem_gma_handler_bcm पूर्ण,
	अणु NCSI_OEM_MFR_MLX_ID, ncsi_oem_gma_handler_mlx पूर्ण
पूर्ण;

अटल पूर्णांक ncsi_gma_handler(काष्ठा ncsi_cmd_arg *nca, अचिन्हित पूर्णांक mf_id)
अणु
	काष्ठा ncsi_oem_gma_handler *nch = शून्य;
	पूर्णांक i;

	/* This function should only be called once, वापस अगर flag set */
	अगर (nca->ndp->gma_flag == 1)
		वापस -1;

	/* Find gma handler क्रम given manufacturer id */
	क्रम (i = 0; i < ARRAY_SIZE(ncsi_oem_gma_handlers); i++) अणु
		अगर (ncsi_oem_gma_handlers[i].mfr_id == mf_id) अणु
			अगर (ncsi_oem_gma_handlers[i].handler)
				nch = &ncsi_oem_gma_handlers[i];
			अवरोध;
			पूर्ण
	पूर्ण

	अगर (!nch) अणु
		netdev_err(nca->ndp->ndev.dev,
			   "NCSI: No GMA handler available for MFR-ID (0x%x)\n",
			   mf_id);
		वापस -1;
	पूर्ण

	/* Get Mac address from NCSI device */
	वापस nch->handler(nca);
पूर्ण

#पूर्ण_अगर /* CONFIG_NCSI_OEM_CMD_GET_MAC */

/* Determine अगर a given channel from the channel_queue should be used क्रम Tx */
अटल bool ncsi_channel_is_tx(काष्ठा ncsi_dev_priv *ndp,
			       काष्ठा ncsi_channel *nc)
अणु
	काष्ठा ncsi_channel_mode *ncm;
	काष्ठा ncsi_channel *channel;
	काष्ठा ncsi_package *np;

	/* Check अगर any other channel has Tx enabled; a channel may have alपढ़ोy
	 * been configured and हटाओd from the channel queue.
	 */
	NCSI_FOR_EACH_PACKAGE(ndp, np) अणु
		अगर (!ndp->multi_package && np != nc->package)
			जारी;
		NCSI_FOR_EACH_CHANNEL(np, channel) अणु
			ncm = &channel->modes[NCSI_MODE_TX_ENABLE];
			अगर (ncm->enable)
				वापस false;
		पूर्ण
	पूर्ण

	/* This channel is the preferred channel and has link */
	list_क्रम_each_entry_rcu(channel, &ndp->channel_queue, link) अणु
		np = channel->package;
		अगर (np->preferred_channel &&
		    ncsi_channel_has_link(np->preferred_channel)) अणु
			वापस np->preferred_channel == nc;
		पूर्ण
	पूर्ण

	/* This channel has link */
	अगर (ncsi_channel_has_link(nc))
		वापस true;

	list_क्रम_each_entry_rcu(channel, &ndp->channel_queue, link)
		अगर (ncsi_channel_has_link(channel))
			वापस false;

	/* No other channel has link; शेष to this one */
	वापस true;
पूर्ण

/* Change the active Tx channel in a multi-channel setup */
पूर्णांक ncsi_update_tx_channel(काष्ठा ncsi_dev_priv *ndp,
			   काष्ठा ncsi_package *package,
			   काष्ठा ncsi_channel *disable,
			   काष्ठा ncsi_channel *enable)
अणु
	काष्ठा ncsi_cmd_arg nca;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_package *np;
	पूर्णांक ret = 0;

	अगर (!package->multi_channel && !ndp->multi_package)
		netdev_warn(ndp->ndev.dev,
			    "NCSI: Trying to update Tx channel in single-channel mode\n");
	nca.ndp = ndp;
	nca.req_flags = 0;

	/* Find current channel with Tx enabled */
	NCSI_FOR_EACH_PACKAGE(ndp, np) अणु
		अगर (disable)
			अवरोध;
		अगर (!ndp->multi_package && np != package)
			जारी;

		NCSI_FOR_EACH_CHANNEL(np, nc)
			अगर (nc->modes[NCSI_MODE_TX_ENABLE].enable) अणु
				disable = nc;
				अवरोध;
			पूर्ण
	पूर्ण

	/* Find a suitable channel क्रम Tx */
	NCSI_FOR_EACH_PACKAGE(ndp, np) अणु
		अगर (enable)
			अवरोध;
		अगर (!ndp->multi_package && np != package)
			जारी;
		अगर (!(ndp->package_whitelist & (0x1 << np->id)))
			जारी;

		अगर (np->preferred_channel &&
		    ncsi_channel_has_link(np->preferred_channel)) अणु
			enable = np->preferred_channel;
			अवरोध;
		पूर्ण

		NCSI_FOR_EACH_CHANNEL(np, nc) अणु
			अगर (!(np->channel_whitelist & 0x1 << nc->id))
				जारी;
			अगर (nc->state != NCSI_CHANNEL_ACTIVE)
				जारी;
			अगर (ncsi_channel_has_link(nc)) अणु
				enable = nc;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (disable == enable)
		वापस -1;

	अगर (!enable)
		वापस -1;

	अगर (disable) अणु
		nca.channel = disable->id;
		nca.package = disable->package->id;
		nca.type = NCSI_PKT_CMD_DCNT;
		ret = ncsi_xmit_cmd(&nca);
		अगर (ret)
			netdev_err(ndp->ndev.dev,
				   "Error %d sending DCNT\n",
				   ret);
	पूर्ण

	netdev_info(ndp->ndev.dev, "NCSI: channel %u enables Tx\n", enable->id);

	nca.channel = enable->id;
	nca.package = enable->package->id;
	nca.type = NCSI_PKT_CMD_ECNT;
	ret = ncsi_xmit_cmd(&nca);
	अगर (ret)
		netdev_err(ndp->ndev.dev,
			   "Error %d sending ECNT\n",
			   ret);

	वापस ret;
पूर्ण

अटल व्योम ncsi_configure_channel(काष्ठा ncsi_dev_priv *ndp)
अणु
	काष्ठा ncsi_package *np = ndp->active_package;
	काष्ठा ncsi_channel *nc = ndp->active_channel;
	काष्ठा ncsi_channel *hot_nc = शून्य;
	काष्ठा ncsi_dev *nd = &ndp->ndev;
	काष्ठा net_device *dev = nd->dev;
	काष्ठा ncsi_cmd_arg nca;
	अचिन्हित अक्षर index;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	nca.ndp = ndp;
	nca.req_flags = NCSI_REQ_FLAG_EVENT_DRIVEN;
	चयन (nd->state) अणु
	हाल ncsi_dev_state_config:
	हाल ncsi_dev_state_config_sp:
		ndp->pending_req_num = 1;

		/* Select the specअगरic package */
		nca.type = NCSI_PKT_CMD_SP;
		अगर (ndp->flags & NCSI_DEV_HWA)
			nca.bytes[0] = 0;
		अन्यथा
			nca.bytes[0] = 1;
		nca.package = np->id;
		nca.channel = NCSI_RESERVED_CHANNEL;
		ret = ncsi_xmit_cmd(&nca);
		अगर (ret) अणु
			netdev_err(ndp->ndev.dev,
				   "NCSI: Failed to transmit CMD_SP\n");
			जाओ error;
		पूर्ण

		nd->state = ncsi_dev_state_config_cis;
		अवरोध;
	हाल ncsi_dev_state_config_cis:
		ndp->pending_req_num = 1;

		/* Clear initial state */
		nca.type = NCSI_PKT_CMD_CIS;
		nca.package = np->id;
		nca.channel = nc->id;
		ret = ncsi_xmit_cmd(&nca);
		अगर (ret) अणु
			netdev_err(ndp->ndev.dev,
				   "NCSI: Failed to transmit CMD_CIS\n");
			जाओ error;
		पूर्ण

		nd->state = ncsi_dev_state_config_oem_gma;
		अवरोध;
	हाल ncsi_dev_state_config_oem_gma:
		nd->state = ncsi_dev_state_config_clear_vids;
		ret = -1;

#अगर IS_ENABLED(CONFIG_NCSI_OEM_CMD_GET_MAC)
		nca.type = NCSI_PKT_CMD_OEM;
		nca.package = np->id;
		nca.channel = nc->id;
		ndp->pending_req_num = 1;
		ret = ncsi_gma_handler(&nca, nc->version.mf_id);
#पूर्ण_अगर /* CONFIG_NCSI_OEM_CMD_GET_MAC */

		अगर (ret < 0)
			schedule_work(&ndp->work);

		अवरोध;
	हाल ncsi_dev_state_config_clear_vids:
	हाल ncsi_dev_state_config_svf:
	हाल ncsi_dev_state_config_ev:
	हाल ncsi_dev_state_config_sma:
	हाल ncsi_dev_state_config_ebf:
	हाल ncsi_dev_state_config_dgmf:
	हाल ncsi_dev_state_config_ecnt:
	हाल ncsi_dev_state_config_ec:
	हाल ncsi_dev_state_config_ae:
	हाल ncsi_dev_state_config_gls:
		ndp->pending_req_num = 1;

		nca.package = np->id;
		nca.channel = nc->id;

		/* Clear any active filters on the channel beक्रमe setting */
		अगर (nd->state == ncsi_dev_state_config_clear_vids) अणु
			ret = clear_one_vid(ndp, nc, &nca);
			अगर (ret) अणु
				nd->state = ncsi_dev_state_config_svf;
				schedule_work(&ndp->work);
				अवरोध;
			पूर्ण
			/* Repeat */
			nd->state = ncsi_dev_state_config_clear_vids;
		/* Add known VLAN tags to the filter */
		पूर्ण अन्यथा अगर (nd->state == ncsi_dev_state_config_svf) अणु
			ret = set_one_vid(ndp, nc, &nca);
			अगर (ret) अणु
				nd->state = ncsi_dev_state_config_ev;
				schedule_work(&ndp->work);
				अवरोध;
			पूर्ण
			/* Repeat */
			nd->state = ncsi_dev_state_config_svf;
		/* Enable/Disable the VLAN filter */
		पूर्ण अन्यथा अगर (nd->state == ncsi_dev_state_config_ev) अणु
			अगर (list_empty(&ndp->vlan_vids)) अणु
				nca.type = NCSI_PKT_CMD_DV;
			पूर्ण अन्यथा अणु
				nca.type = NCSI_PKT_CMD_EV;
				nca.bytes[3] = NCSI_CAP_VLAN_NO;
			पूर्ण
			nd->state = ncsi_dev_state_config_sma;
		पूर्ण अन्यथा अगर (nd->state == ncsi_dev_state_config_sma) अणु
		/* Use first entry in unicast filter table. Note that
		 * the MAC filter table starts from entry 1 instead of
		 * 0.
		 */
			nca.type = NCSI_PKT_CMD_SMA;
			क्रम (index = 0; index < 6; index++)
				nca.bytes[index] = dev->dev_addr[index];
			nca.bytes[6] = 0x1;
			nca.bytes[7] = 0x1;
			nd->state = ncsi_dev_state_config_ebf;
		पूर्ण अन्यथा अगर (nd->state == ncsi_dev_state_config_ebf) अणु
			nca.type = NCSI_PKT_CMD_EBF;
			nca.dwords[0] = nc->caps[NCSI_CAP_BC].cap;
			/* अगर multicast global filtering is supported then
			 * disable it so that all multicast packet will be
			 * क्रमwarded to management controller
			 */
			अगर (nc->caps[NCSI_CAP_GENERIC].cap &
			    NCSI_CAP_GENERIC_MC)
				nd->state = ncsi_dev_state_config_dgmf;
			अन्यथा अगर (ncsi_channel_is_tx(ndp, nc))
				nd->state = ncsi_dev_state_config_ecnt;
			अन्यथा
				nd->state = ncsi_dev_state_config_ec;
		पूर्ण अन्यथा अगर (nd->state == ncsi_dev_state_config_dgmf) अणु
			nca.type = NCSI_PKT_CMD_DGMF;
			अगर (ncsi_channel_is_tx(ndp, nc))
				nd->state = ncsi_dev_state_config_ecnt;
			अन्यथा
				nd->state = ncsi_dev_state_config_ec;
		पूर्ण अन्यथा अगर (nd->state == ncsi_dev_state_config_ecnt) अणु
			अगर (np->preferred_channel &&
			    nc != np->preferred_channel)
				netdev_info(ndp->ndev.dev,
					    "NCSI: Tx failed over to channel %u\n",
					    nc->id);
			nca.type = NCSI_PKT_CMD_ECNT;
			nd->state = ncsi_dev_state_config_ec;
		पूर्ण अन्यथा अगर (nd->state == ncsi_dev_state_config_ec) अणु
			/* Enable AEN अगर it's supported */
			nca.type = NCSI_PKT_CMD_EC;
			nd->state = ncsi_dev_state_config_ae;
			अगर (!(nc->caps[NCSI_CAP_AEN].cap & NCSI_CAP_AEN_MASK))
				nd->state = ncsi_dev_state_config_gls;
		पूर्ण अन्यथा अगर (nd->state == ncsi_dev_state_config_ae) अणु
			nca.type = NCSI_PKT_CMD_AE;
			nca.bytes[0] = 0;
			nca.dwords[1] = nc->caps[NCSI_CAP_AEN].cap;
			nd->state = ncsi_dev_state_config_gls;
		पूर्ण अन्यथा अगर (nd->state == ncsi_dev_state_config_gls) अणु
			nca.type = NCSI_PKT_CMD_GLS;
			nd->state = ncsi_dev_state_config_करोne;
		पूर्ण

		ret = ncsi_xmit_cmd(&nca);
		अगर (ret) अणु
			netdev_err(ndp->ndev.dev,
				   "NCSI: Failed to transmit CMD %x\n",
				   nca.type);
			जाओ error;
		पूर्ण
		अवरोध;
	हाल ncsi_dev_state_config_करोne:
		netdev_dbg(ndp->ndev.dev, "NCSI: channel %u config done\n",
			   nc->id);
		spin_lock_irqsave(&nc->lock, flags);
		nc->state = NCSI_CHANNEL_ACTIVE;

		अगर (ndp->flags & NCSI_DEV_RESET) अणु
			/* A reset event happened during config, start it now */
			nc->reconfigure_needed = false;
			spin_unlock_irqrestore(&nc->lock, flags);
			ncsi_reset_dev(nd);
			अवरोध;
		पूर्ण

		अगर (nc->reconfigure_needed) अणु
			/* This channel's configuration has been updated
			 * part-way during the config state - start the
			 * channel configuration over
			 */
			nc->reconfigure_needed = false;
			nc->state = NCSI_CHANNEL_INACTIVE;
			spin_unlock_irqrestore(&nc->lock, flags);

			spin_lock_irqsave(&ndp->lock, flags);
			list_add_tail_rcu(&nc->link, &ndp->channel_queue);
			spin_unlock_irqrestore(&ndp->lock, flags);

			netdev_dbg(dev, "Dirty NCSI channel state reset\n");
			ncsi_process_next_channel(ndp);
			अवरोध;
		पूर्ण

		अगर (nc->modes[NCSI_MODE_LINK].data[2] & 0x1) अणु
			hot_nc = nc;
		पूर्ण अन्यथा अणु
			hot_nc = शून्य;
			netdev_dbg(ndp->ndev.dev,
				   "NCSI: channel %u link down after config\n",
				   nc->id);
		पूर्ण
		spin_unlock_irqrestore(&nc->lock, flags);

		/* Update the hot channel */
		spin_lock_irqsave(&ndp->lock, flags);
		ndp->hot_channel = hot_nc;
		spin_unlock_irqrestore(&ndp->lock, flags);

		ncsi_start_channel_monitor(nc);
		ncsi_process_next_channel(ndp);
		अवरोध;
	शेष:
		netdev_alert(dev, "Wrong NCSI state 0x%x in config\n",
			     nd->state);
	पूर्ण

	वापस;

error:
	ncsi_report_link(ndp, true);
पूर्ण

अटल पूर्णांक ncsi_choose_active_channel(काष्ठा ncsi_dev_priv *ndp)
अणु
	काष्ठा ncsi_channel *nc, *found, *hot_nc;
	काष्ठा ncsi_channel_mode *ncm;
	अचिन्हित दीर्घ flags, cflags;
	काष्ठा ncsi_package *np;
	bool with_link;

	spin_lock_irqsave(&ndp->lock, flags);
	hot_nc = ndp->hot_channel;
	spin_unlock_irqrestore(&ndp->lock, flags);

	/* By शेष the search is करोne once an inactive channel with up
	 * link is found, unless a preferred channel is set.
	 * If multi_package or multi_channel are configured all channels in the
	 * whitelist are added to the channel queue.
	 */
	found = शून्य;
	with_link = false;
	NCSI_FOR_EACH_PACKAGE(ndp, np) अणु
		अगर (!(ndp->package_whitelist & (0x1 << np->id)))
			जारी;
		NCSI_FOR_EACH_CHANNEL(np, nc) अणु
			अगर (!(np->channel_whitelist & (0x1 << nc->id)))
				जारी;

			spin_lock_irqsave(&nc->lock, cflags);

			अगर (!list_empty(&nc->link) ||
			    nc->state != NCSI_CHANNEL_INACTIVE) अणु
				spin_unlock_irqrestore(&nc->lock, cflags);
				जारी;
			पूर्ण

			अगर (!found)
				found = nc;

			अगर (nc == hot_nc)
				found = nc;

			ncm = &nc->modes[NCSI_MODE_LINK];
			अगर (ncm->data[2] & 0x1) अणु
				found = nc;
				with_link = true;
			पूर्ण

			/* If multi_channel is enabled configure all valid
			 * channels whether or not they currently have link
			 * so they will have AENs enabled.
			 */
			अगर (with_link || np->multi_channel) अणु
				spin_lock_irqsave(&ndp->lock, flags);
				list_add_tail_rcu(&nc->link,
						  &ndp->channel_queue);
				spin_unlock_irqrestore(&ndp->lock, flags);

				netdev_dbg(ndp->ndev.dev,
					   "NCSI: Channel %u added to queue (link %s)\n",
					   nc->id,
					   ncm->data[2] & 0x1 ? "up" : "down");
			पूर्ण

			spin_unlock_irqrestore(&nc->lock, cflags);

			अगर (with_link && !np->multi_channel)
				अवरोध;
		पूर्ण
		अगर (with_link && !ndp->multi_package)
			अवरोध;
	पूर्ण

	अगर (list_empty(&ndp->channel_queue) && found) अणु
		netdev_info(ndp->ndev.dev,
			    "NCSI: No channel with link found, configuring channel %u\n",
			    found->id);
		spin_lock_irqsave(&ndp->lock, flags);
		list_add_tail_rcu(&found->link, &ndp->channel_queue);
		spin_unlock_irqrestore(&ndp->lock, flags);
	पूर्ण अन्यथा अगर (!found) अणु
		netdev_warn(ndp->ndev.dev,
			    "NCSI: No channel found to configure!\n");
		ncsi_report_link(ndp, true);
		वापस -ENODEV;
	पूर्ण

	वापस ncsi_process_next_channel(ndp);
पूर्ण

अटल bool ncsi_check_hwa(काष्ठा ncsi_dev_priv *ndp)
अणु
	काष्ठा ncsi_package *np;
	काष्ठा ncsi_channel *nc;
	अचिन्हित पूर्णांक cap;
	bool has_channel = false;

	/* The hardware arbitration is disabled अगर any one channel
	 * करोesn't support explicitly.
	 */
	NCSI_FOR_EACH_PACKAGE(ndp, np) अणु
		NCSI_FOR_EACH_CHANNEL(np, nc) अणु
			has_channel = true;

			cap = nc->caps[NCSI_CAP_GENERIC].cap;
			अगर (!(cap & NCSI_CAP_GENERIC_HWA) ||
			    (cap & NCSI_CAP_GENERIC_HWA_MASK) !=
			    NCSI_CAP_GENERIC_HWA_SUPPORT) अणु
				ndp->flags &= ~NCSI_DEV_HWA;
				वापस false;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (has_channel) अणु
		ndp->flags |= NCSI_DEV_HWA;
		वापस true;
	पूर्ण

	ndp->flags &= ~NCSI_DEV_HWA;
	वापस false;
पूर्ण

अटल व्योम ncsi_probe_channel(काष्ठा ncsi_dev_priv *ndp)
अणु
	काष्ठा ncsi_dev *nd = &ndp->ndev;
	काष्ठा ncsi_package *np;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_cmd_arg nca;
	अचिन्हित अक्षर index;
	पूर्णांक ret;

	nca.ndp = ndp;
	nca.req_flags = NCSI_REQ_FLAG_EVENT_DRIVEN;
	चयन (nd->state) अणु
	हाल ncsi_dev_state_probe:
		nd->state = ncsi_dev_state_probe_deselect;
		fallthrough;
	हाल ncsi_dev_state_probe_deselect:
		ndp->pending_req_num = 8;

		/* Deselect all possible packages */
		nca.type = NCSI_PKT_CMD_DP;
		nca.channel = NCSI_RESERVED_CHANNEL;
		क्रम (index = 0; index < 8; index++) अणु
			nca.package = index;
			ret = ncsi_xmit_cmd(&nca);
			अगर (ret)
				जाओ error;
		पूर्ण

		nd->state = ncsi_dev_state_probe_package;
		अवरोध;
	हाल ncsi_dev_state_probe_package:
		ndp->pending_req_num = 1;

		nca.type = NCSI_PKT_CMD_SP;
		nca.bytes[0] = 1;
		nca.package = ndp->package_probe_id;
		nca.channel = NCSI_RESERVED_CHANNEL;
		ret = ncsi_xmit_cmd(&nca);
		अगर (ret)
			जाओ error;
		nd->state = ncsi_dev_state_probe_channel;
		अवरोध;
	हाल ncsi_dev_state_probe_channel:
		ndp->active_package = ncsi_find_package(ndp,
							ndp->package_probe_id);
		अगर (!ndp->active_package) अणु
			/* No response */
			nd->state = ncsi_dev_state_probe_dp;
			schedule_work(&ndp->work);
			अवरोध;
		पूर्ण
		nd->state = ncsi_dev_state_probe_cis;
		अगर (IS_ENABLED(CONFIG_NCSI_OEM_CMD_GET_MAC) &&
		    ndp->mlx_multi_host)
			nd->state = ncsi_dev_state_probe_mlx_gma;

		schedule_work(&ndp->work);
		अवरोध;
#अगर IS_ENABLED(CONFIG_NCSI_OEM_CMD_GET_MAC)
	हाल ncsi_dev_state_probe_mlx_gma:
		ndp->pending_req_num = 1;

		nca.type = NCSI_PKT_CMD_OEM;
		nca.package = ndp->active_package->id;
		nca.channel = 0;
		ret = ncsi_oem_gma_handler_mlx(&nca);
		अगर (ret)
			जाओ error;

		nd->state = ncsi_dev_state_probe_mlx_smaf;
		अवरोध;
	हाल ncsi_dev_state_probe_mlx_smaf:
		ndp->pending_req_num = 1;

		nca.type = NCSI_PKT_CMD_OEM;
		nca.package = ndp->active_package->id;
		nca.channel = 0;
		ret = ncsi_oem_smaf_mlx(&nca);
		अगर (ret)
			जाओ error;

		nd->state = ncsi_dev_state_probe_cis;
		अवरोध;
#पूर्ण_अगर /* CONFIG_NCSI_OEM_CMD_GET_MAC */
	हाल ncsi_dev_state_probe_cis:
		ndp->pending_req_num = NCSI_RESERVED_CHANNEL;

		/* Clear initial state */
		nca.type = NCSI_PKT_CMD_CIS;
		nca.package = ndp->active_package->id;
		क्रम (index = 0; index < NCSI_RESERVED_CHANNEL; index++) अणु
			nca.channel = index;
			ret = ncsi_xmit_cmd(&nca);
			अगर (ret)
				जाओ error;
		पूर्ण

		nd->state = ncsi_dev_state_probe_gvi;
		अवरोध;
	हाल ncsi_dev_state_probe_gvi:
	हाल ncsi_dev_state_probe_gc:
	हाल ncsi_dev_state_probe_gls:
		np = ndp->active_package;
		ndp->pending_req_num = np->channel_num;

		/* Retrieve version, capability or link status */
		अगर (nd->state == ncsi_dev_state_probe_gvi)
			nca.type = NCSI_PKT_CMD_GVI;
		अन्यथा अगर (nd->state == ncsi_dev_state_probe_gc)
			nca.type = NCSI_PKT_CMD_GC;
		अन्यथा
			nca.type = NCSI_PKT_CMD_GLS;

		nca.package = np->id;
		NCSI_FOR_EACH_CHANNEL(np, nc) अणु
			nca.channel = nc->id;
			ret = ncsi_xmit_cmd(&nca);
			अगर (ret)
				जाओ error;
		पूर्ण

		अगर (nd->state == ncsi_dev_state_probe_gvi)
			nd->state = ncsi_dev_state_probe_gc;
		अन्यथा अगर (nd->state == ncsi_dev_state_probe_gc)
			nd->state = ncsi_dev_state_probe_gls;
		अन्यथा
			nd->state = ncsi_dev_state_probe_dp;
		अवरोध;
	हाल ncsi_dev_state_probe_dp:
		ndp->pending_req_num = 1;

		/* Deselect the current package */
		nca.type = NCSI_PKT_CMD_DP;
		nca.package = ndp->package_probe_id;
		nca.channel = NCSI_RESERVED_CHANNEL;
		ret = ncsi_xmit_cmd(&nca);
		अगर (ret)
			जाओ error;

		/* Probe next package */
		ndp->package_probe_id++;
		अगर (ndp->package_probe_id >= 8) अणु
			/* Probe finished */
			ndp->flags |= NCSI_DEV_PROBED;
			अवरोध;
		पूर्ण
		nd->state = ncsi_dev_state_probe_package;
		ndp->active_package = शून्य;
		अवरोध;
	शेष:
		netdev_warn(nd->dev, "Wrong NCSI state 0x%0x in enumeration\n",
			    nd->state);
	पूर्ण

	अगर (ndp->flags & NCSI_DEV_PROBED) अणु
		/* Check अगर all packages have HWA support */
		ncsi_check_hwa(ndp);
		ncsi_choose_active_channel(ndp);
	पूर्ण

	वापस;
error:
	netdev_err(ndp->ndev.dev,
		   "NCSI: Failed to transmit cmd 0x%x during probe\n",
		   nca.type);
	ncsi_report_link(ndp, true);
पूर्ण

अटल व्योम ncsi_dev_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ncsi_dev_priv *ndp = container_of(work,
			काष्ठा ncsi_dev_priv, work);
	काष्ठा ncsi_dev *nd = &ndp->ndev;

	चयन (nd->state & ncsi_dev_state_major) अणु
	हाल ncsi_dev_state_probe:
		ncsi_probe_channel(ndp);
		अवरोध;
	हाल ncsi_dev_state_suspend:
		ncsi_suspend_channel(ndp);
		अवरोध;
	हाल ncsi_dev_state_config:
		ncsi_configure_channel(ndp);
		अवरोध;
	शेष:
		netdev_warn(nd->dev, "Wrong NCSI state 0x%x in workqueue\n",
			    nd->state);
	पूर्ण
पूर्ण

पूर्णांक ncsi_process_next_channel(काष्ठा ncsi_dev_priv *ndp)
अणु
	काष्ठा ncsi_channel *nc;
	पूर्णांक old_state;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ndp->lock, flags);
	nc = list_first_or_null_rcu(&ndp->channel_queue,
				    काष्ठा ncsi_channel, link);
	अगर (!nc) अणु
		spin_unlock_irqrestore(&ndp->lock, flags);
		जाओ out;
	पूर्ण

	list_del_init(&nc->link);
	spin_unlock_irqrestore(&ndp->lock, flags);

	spin_lock_irqsave(&nc->lock, flags);
	old_state = nc->state;
	nc->state = NCSI_CHANNEL_INVISIBLE;
	spin_unlock_irqrestore(&nc->lock, flags);

	ndp->active_channel = nc;
	ndp->active_package = nc->package;

	चयन (old_state) अणु
	हाल NCSI_CHANNEL_INACTIVE:
		ndp->ndev.state = ncsi_dev_state_config;
		netdev_dbg(ndp->ndev.dev, "NCSI: configuring channel %u\n",
	                   nc->id);
		ncsi_configure_channel(ndp);
		अवरोध;
	हाल NCSI_CHANNEL_ACTIVE:
		ndp->ndev.state = ncsi_dev_state_suspend;
		netdev_dbg(ndp->ndev.dev, "NCSI: suspending channel %u\n",
			   nc->id);
		ncsi_suspend_channel(ndp);
		अवरोध;
	शेष:
		netdev_err(ndp->ndev.dev, "Invalid state 0x%x on %d:%d\n",
			   old_state, nc->package->id, nc->id);
		ncsi_report_link(ndp, false);
		वापस -EINVAL;
	पूर्ण

	वापस 0;

out:
	ndp->active_channel = शून्य;
	ndp->active_package = शून्य;
	अगर (ndp->flags & NCSI_DEV_RESHUFFLE) अणु
		ndp->flags &= ~NCSI_DEV_RESHUFFLE;
		वापस ncsi_choose_active_channel(ndp);
	पूर्ण

	ncsi_report_link(ndp, false);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक ncsi_kick_channels(काष्ठा ncsi_dev_priv *ndp)
अणु
	काष्ठा ncsi_dev *nd = &ndp->ndev;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_package *np;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक n = 0;

	NCSI_FOR_EACH_PACKAGE(ndp, np) अणु
		NCSI_FOR_EACH_CHANNEL(np, nc) अणु
			spin_lock_irqsave(&nc->lock, flags);

			/* Channels may be busy, mark dirty instead of
			 * kicking अगर;
			 * a) not ACTIVE (configured)
			 * b) in the channel_queue (to be configured)
			 * c) it's ndev is in the config state
			 */
			अगर (nc->state != NCSI_CHANNEL_ACTIVE) अणु
				अगर ((ndp->ndev.state & 0xff00) ==
						ncsi_dev_state_config ||
						!list_empty(&nc->link)) अणु
					netdev_dbg(nd->dev,
						   "NCSI: channel %p marked dirty\n",
						   nc);
					nc->reconfigure_needed = true;
				पूर्ण
				spin_unlock_irqrestore(&nc->lock, flags);
				जारी;
			पूर्ण

			spin_unlock_irqrestore(&nc->lock, flags);

			ncsi_stop_channel_monitor(nc);
			spin_lock_irqsave(&nc->lock, flags);
			nc->state = NCSI_CHANNEL_INACTIVE;
			spin_unlock_irqrestore(&nc->lock, flags);

			spin_lock_irqsave(&ndp->lock, flags);
			list_add_tail_rcu(&nc->link, &ndp->channel_queue);
			spin_unlock_irqrestore(&ndp->lock, flags);

			netdev_dbg(nd->dev, "NCSI: kicked channel %p\n", nc);
			n++;
		पूर्ण
	पूर्ण

	वापस n;
पूर्ण

पूर्णांक ncsi_vlan_rx_add_vid(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	काष्ठा ncsi_dev_priv *ndp;
	अचिन्हित पूर्णांक n_vids = 0;
	काष्ठा vlan_vid *vlan;
	काष्ठा ncsi_dev *nd;
	bool found = false;

	अगर (vid == 0)
		वापस 0;

	nd = ncsi_find_dev(dev);
	अगर (!nd) अणु
		netdev_warn(dev, "NCSI: No net_device?\n");
		वापस 0;
	पूर्ण

	ndp = TO_NCSI_DEV_PRIV(nd);

	/* Add the VLAN id to our पूर्णांकernal list */
	list_क्रम_each_entry_rcu(vlan, &ndp->vlan_vids, list) अणु
		n_vids++;
		अगर (vlan->vid == vid) अणु
			netdev_dbg(dev, "NCSI: vid %u already registered\n",
				   vid);
			वापस 0;
		पूर्ण
	पूर्ण
	अगर (n_vids >= NCSI_MAX_VLAN_VIDS) अणु
		netdev_warn(dev,
			    "tried to add vlan id %u but NCSI max already registered (%u)\n",
			    vid, NCSI_MAX_VLAN_VIDS);
		वापस -ENOSPC;
	पूर्ण

	vlan = kzalloc(माप(*vlan), GFP_KERNEL);
	अगर (!vlan)
		वापस -ENOMEM;

	vlan->proto = proto;
	vlan->vid = vid;
	list_add_rcu(&vlan->list, &ndp->vlan_vids);

	netdev_dbg(dev, "NCSI: Added new vid %u\n", vid);

	found = ncsi_kick_channels(ndp) != 0;

	वापस found ? ncsi_process_next_channel(ndp) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(ncsi_vlan_rx_add_vid);

पूर्णांक ncsi_vlan_rx_समाप्त_vid(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	काष्ठा vlan_vid *vlan, *पंचांगp;
	काष्ठा ncsi_dev_priv *ndp;
	काष्ठा ncsi_dev *nd;
	bool found = false;

	अगर (vid == 0)
		वापस 0;

	nd = ncsi_find_dev(dev);
	अगर (!nd) अणु
		netdev_warn(dev, "NCSI: no net_device?\n");
		वापस 0;
	पूर्ण

	ndp = TO_NCSI_DEV_PRIV(nd);

	/* Remove the VLAN id from our पूर्णांकernal list */
	list_क्रम_each_entry_safe(vlan, पंचांगp, &ndp->vlan_vids, list)
		अगर (vlan->vid == vid) अणु
			netdev_dbg(dev, "NCSI: vid %u found, removing\n", vid);
			list_del_rcu(&vlan->list);
			found = true;
			kमुक्त(vlan);
		पूर्ण

	अगर (!found) अणु
		netdev_err(dev, "NCSI: vid %u wasn't registered!\n", vid);
		वापस -EINVAL;
	पूर्ण

	found = ncsi_kick_channels(ndp) != 0;

	वापस found ? ncsi_process_next_channel(ndp) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(ncsi_vlan_rx_समाप्त_vid);

काष्ठा ncsi_dev *ncsi_रेजिस्टर_dev(काष्ठा net_device *dev,
				   व्योम (*handler)(काष्ठा ncsi_dev *ndev))
अणु
	काष्ठा ncsi_dev_priv *ndp;
	काष्ठा ncsi_dev *nd;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device_node *np;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/* Check अगर the device has been रेजिस्टरed or not */
	nd = ncsi_find_dev(dev);
	अगर (nd)
		वापस nd;

	/* Create NCSI device */
	ndp = kzalloc(माप(*ndp), GFP_ATOMIC);
	अगर (!ndp)
		वापस शून्य;

	nd = &ndp->ndev;
	nd->state = ncsi_dev_state_रेजिस्टरed;
	nd->dev = dev;
	nd->handler = handler;
	ndp->pending_req_num = 0;
	INIT_LIST_HEAD(&ndp->channel_queue);
	INIT_LIST_HEAD(&ndp->vlan_vids);
	INIT_WORK(&ndp->work, ncsi_dev_work);
	ndp->package_whitelist = अच_पूर्णांक_उच्च;

	/* Initialize निजी NCSI device */
	spin_lock_init(&ndp->lock);
	INIT_LIST_HEAD(&ndp->packages);
	ndp->request_id = NCSI_REQ_START_IDX;
	क्रम (i = 0; i < ARRAY_SIZE(ndp->requests); i++) अणु
		ndp->requests[i].id = i;
		ndp->requests[i].ndp = ndp;
		समयr_setup(&ndp->requests[i].समयr, ncsi_request_समयout, 0);
	पूर्ण

	spin_lock_irqsave(&ncsi_dev_lock, flags);
	list_add_tail_rcu(&ndp->node, &ncsi_dev_list);
	spin_unlock_irqrestore(&ncsi_dev_lock, flags);

	/* Register NCSI packet Rx handler */
	ndp->ptype.type = cpu_to_be16(ETH_P_NCSI);
	ndp->ptype.func = ncsi_rcv_rsp;
	ndp->ptype.dev = dev;
	dev_add_pack(&ndp->ptype);

	pdev = to_platक्रमm_device(dev->dev.parent);
	अगर (pdev) अणु
		np = pdev->dev.of_node;
		अगर (np && of_get_property(np, "mlx,multi-host", शून्य))
			ndp->mlx_multi_host = true;
	पूर्ण

	वापस nd;
पूर्ण
EXPORT_SYMBOL_GPL(ncsi_रेजिस्टर_dev);

पूर्णांक ncsi_start_dev(काष्ठा ncsi_dev *nd)
अणु
	काष्ठा ncsi_dev_priv *ndp = TO_NCSI_DEV_PRIV(nd);

	अगर (nd->state != ncsi_dev_state_रेजिस्टरed &&
	    nd->state != ncsi_dev_state_functional)
		वापस -ENOTTY;

	अगर (!(ndp->flags & NCSI_DEV_PROBED)) अणु
		ndp->package_probe_id = 0;
		nd->state = ncsi_dev_state_probe;
		schedule_work(&ndp->work);
		वापस 0;
	पूर्ण

	वापस ncsi_reset_dev(nd);
पूर्ण
EXPORT_SYMBOL_GPL(ncsi_start_dev);

व्योम ncsi_stop_dev(काष्ठा ncsi_dev *nd)
अणु
	काष्ठा ncsi_dev_priv *ndp = TO_NCSI_DEV_PRIV(nd);
	काष्ठा ncsi_package *np;
	काष्ठा ncsi_channel *nc;
	bool chained;
	पूर्णांक old_state;
	अचिन्हित दीर्घ flags;

	/* Stop the channel monitor on any active channels. Don't reset the
	 * channel state so we know which were active when ncsi_start_dev()
	 * is next called.
	 */
	NCSI_FOR_EACH_PACKAGE(ndp, np) अणु
		NCSI_FOR_EACH_CHANNEL(np, nc) अणु
			ncsi_stop_channel_monitor(nc);

			spin_lock_irqsave(&nc->lock, flags);
			chained = !list_empty(&nc->link);
			old_state = nc->state;
			spin_unlock_irqrestore(&nc->lock, flags);

			WARN_ON_ONCE(chained ||
				     old_state == NCSI_CHANNEL_INVISIBLE);
		पूर्ण
	पूर्ण

	netdev_dbg(ndp->ndev.dev, "NCSI: Stopping device\n");
	ncsi_report_link(ndp, true);
पूर्ण
EXPORT_SYMBOL_GPL(ncsi_stop_dev);

पूर्णांक ncsi_reset_dev(काष्ठा ncsi_dev *nd)
अणु
	काष्ठा ncsi_dev_priv *ndp = TO_NCSI_DEV_PRIV(nd);
	काष्ठा ncsi_channel *nc, *active, *पंचांगp;
	काष्ठा ncsi_package *np;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ndp->lock, flags);

	अगर (!(ndp->flags & NCSI_DEV_RESET)) अणु
		/* Haven't been called yet, check states */
		चयन (nd->state & ncsi_dev_state_major) अणु
		हाल ncsi_dev_state_रेजिस्टरed:
		हाल ncsi_dev_state_probe:
			/* Not even probed yet - करो nothing */
			spin_unlock_irqrestore(&ndp->lock, flags);
			वापस 0;
		हाल ncsi_dev_state_suspend:
		हाल ncsi_dev_state_config:
			/* Wait क्रम the channel to finish its suspend/config
			 * operation; once it finishes it will check क्रम
			 * NCSI_DEV_RESET and reset the state.
			 */
			ndp->flags |= NCSI_DEV_RESET;
			spin_unlock_irqrestore(&ndp->lock, flags);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (nd->state) अणु
		हाल ncsi_dev_state_suspend_करोne:
		हाल ncsi_dev_state_config_करोne:
		हाल ncsi_dev_state_functional:
			/* Ok */
			अवरोध;
		शेष:
			/* Current reset operation happening */
			spin_unlock_irqrestore(&ndp->lock, flags);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (!list_empty(&ndp->channel_queue)) अणु
		/* Clear any channel queue we may have पूर्णांकerrupted */
		list_क्रम_each_entry_safe(nc, पंचांगp, &ndp->channel_queue, link)
			list_del_init(&nc->link);
	पूर्ण
	spin_unlock_irqrestore(&ndp->lock, flags);

	active = शून्य;
	NCSI_FOR_EACH_PACKAGE(ndp, np) अणु
		NCSI_FOR_EACH_CHANNEL(np, nc) अणु
			spin_lock_irqsave(&nc->lock, flags);

			अगर (nc->state == NCSI_CHANNEL_ACTIVE) अणु
				active = nc;
				nc->state = NCSI_CHANNEL_INVISIBLE;
				spin_unlock_irqrestore(&nc->lock, flags);
				ncsi_stop_channel_monitor(nc);
				अवरोध;
			पूर्ण

			spin_unlock_irqrestore(&nc->lock, flags);
		पूर्ण
		अगर (active)
			अवरोध;
	पूर्ण

	अगर (!active) अणु
		/* Done */
		spin_lock_irqsave(&ndp->lock, flags);
		ndp->flags &= ~NCSI_DEV_RESET;
		spin_unlock_irqrestore(&ndp->lock, flags);
		वापस ncsi_choose_active_channel(ndp);
	पूर्ण

	spin_lock_irqsave(&ndp->lock, flags);
	ndp->flags |= NCSI_DEV_RESET;
	ndp->active_channel = active;
	ndp->active_package = active->package;
	spin_unlock_irqrestore(&ndp->lock, flags);

	nd->state = ncsi_dev_state_suspend;
	schedule_work(&ndp->work);
	वापस 0;
पूर्ण

व्योम ncsi_unरेजिस्टर_dev(काष्ठा ncsi_dev *nd)
अणु
	काष्ठा ncsi_dev_priv *ndp = TO_NCSI_DEV_PRIV(nd);
	काष्ठा ncsi_package *np, *पंचांगp;
	अचिन्हित दीर्घ flags;

	dev_हटाओ_pack(&ndp->ptype);

	list_क्रम_each_entry_safe(np, पंचांगp, &ndp->packages, node)
		ncsi_हटाओ_package(np);

	spin_lock_irqsave(&ncsi_dev_lock, flags);
	list_del_rcu(&ndp->node);
	spin_unlock_irqrestore(&ncsi_dev_lock, flags);

	kमुक्त(ndp);
पूर्ण
EXPORT_SYMBOL_GPL(ncsi_unरेजिस्टर_dev);
