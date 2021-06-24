<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright Gavin Shan, IBM Corporation 2016.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>

#समावेश <net/ncsi.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <net/genetlink.h>

#समावेश "internal.h"
#समावेश "ncsi-pkt.h"
#समावेश "ncsi-netlink.h"

अटल पूर्णांक ncsi_validate_rsp_pkt(काष्ठा ncsi_request *nr,
				 अचिन्हित लघु payload)
अणु
	काष्ठा ncsi_rsp_pkt_hdr *h;
	u32 checksum;
	__be32 *pchecksum;

	/* Check NCSI packet header. We करोn't need validate
	 * the packet type, which should have been checked
	 * beक्रमe calling this function.
	 */
	h = (काष्ठा ncsi_rsp_pkt_hdr *)skb_network_header(nr->rsp);

	अगर (h->common.revision != NCSI_PKT_REVISION) अणु
		netdev_dbg(nr->ndp->ndev.dev,
			   "NCSI: unsupported header revision\n");
		वापस -EINVAL;
	पूर्ण
	अगर (ntohs(h->common.length) != payload) अणु
		netdev_dbg(nr->ndp->ndev.dev,
			   "NCSI: payload length mismatched\n");
		वापस -EINVAL;
	पूर्ण

	/* Check on code and reason */
	अगर (ntohs(h->code) != NCSI_PKT_RSP_C_COMPLETED ||
	    ntohs(h->reason) != NCSI_PKT_RSP_R_NO_ERROR) अणु
		netdev_dbg(nr->ndp->ndev.dev,
			   "NCSI: non zero response/reason code %04xh, %04xh\n",
			    ntohs(h->code), ntohs(h->reason));
		वापस -EPERM;
	पूर्ण

	/* Validate checksum, which might be zeroes अगर the
	 * sender करोesn't support checksum according to NCSI
	 * specअगरication.
	 */
	pchecksum = (__be32 *)((व्योम *)(h + 1) + ALIGN(payload, 4) - 4);
	अगर (ntohl(*pchecksum) == 0)
		वापस 0;

	checksum = ncsi_calculate_checksum((अचिन्हित अक्षर *)h,
					   माप(*h) + payload - 4);

	अगर (*pchecksum != htonl(checksum)) अणु
		netdev_dbg(nr->ndp->ndev.dev,
			   "NCSI: checksum mismatched; recd: %08x calc: %08x\n",
			   *pchecksum, htonl(checksum));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_cis(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_package *np;
	काष्ठा ncsi_channel *nc;
	अचिन्हित अक्षर id;

	rsp = (काष्ठा ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel, &np, &nc);
	अगर (!nc) अणु
		अगर (ndp->flags & NCSI_DEV_PROBED)
			वापस -ENXIO;

		id = NCSI_CHANNEL_INDEX(rsp->rsp.common.channel);
		nc = ncsi_add_channel(np, id);
	पूर्ण

	वापस nc ? 0 : -ENODEV;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_sp(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_package *np;
	अचिन्हित अक्षर id;

	/* Add the package अगर it's not existing. Otherwise,
	 * to change the state of its child channels.
	 */
	rsp = (काष्ठा ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      &np, शून्य);
	अगर (!np) अणु
		अगर (ndp->flags & NCSI_DEV_PROBED)
			वापस -ENXIO;

		id = NCSI_PACKAGE_INDEX(rsp->rsp.common.channel);
		np = ncsi_add_package(ndp, id);
		अगर (!np)
			वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_dp(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_package *np;
	काष्ठा ncsi_channel *nc;
	अचिन्हित दीर्घ flags;

	/* Find the package */
	rsp = (काष्ठा ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      &np, शून्य);
	अगर (!np)
		वापस -ENODEV;

	/* Change state of all channels attached to the package */
	NCSI_FOR_EACH_CHANNEL(np, nc) अणु
		spin_lock_irqsave(&nc->lock, flags);
		nc->state = NCSI_CHANNEL_INACTIVE;
		spin_unlock_irqrestore(&nc->lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_ec(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_channel_mode *ncm;

	/* Find the package and channel */
	rsp = (काष्ठा ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	ncm = &nc->modes[NCSI_MODE_ENABLE];
	अगर (ncm->enable)
		वापस 0;

	ncm->enable = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_dc(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_channel_mode *ncm;
	पूर्णांक ret;

	ret = ncsi_validate_rsp_pkt(nr, 4);
	अगर (ret)
		वापस ret;

	/* Find the package and channel */
	rsp = (काष्ठा ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	ncm = &nc->modes[NCSI_MODE_ENABLE];
	अगर (!ncm->enable)
		वापस 0;

	ncm->enable = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_rc(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	अचिन्हित दीर्घ flags;

	/* Find the package and channel */
	rsp = (काष्ठा ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	/* Update state क्रम the specअगरied channel */
	spin_lock_irqsave(&nc->lock, flags);
	nc->state = NCSI_CHANNEL_INACTIVE;
	spin_unlock_irqrestore(&nc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_ecnt(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_channel_mode *ncm;

	/* Find the package and channel */
	rsp = (काष्ठा ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	ncm = &nc->modes[NCSI_MODE_TX_ENABLE];
	अगर (ncm->enable)
		वापस 0;

	ncm->enable = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_dcnt(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_channel_mode *ncm;

	/* Find the package and channel */
	rsp = (काष्ठा ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	ncm = &nc->modes[NCSI_MODE_TX_ENABLE];
	अगर (!ncm->enable)
		वापस 0;

	ncm->enable = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_ae(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_cmd_ae_pkt *cmd;
	काष्ठा ncsi_rsp_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_channel_mode *ncm;

	/* Find the package and channel */
	rsp = (काष्ठा ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	/* Check अगर the AEN has been enabled */
	ncm = &nc->modes[NCSI_MODE_AEN];
	अगर (ncm->enable)
		वापस 0;

	/* Update to AEN configuration */
	cmd = (काष्ठा ncsi_cmd_ae_pkt *)skb_network_header(nr->cmd);
	ncm->enable = 1;
	ncm->data[0] = cmd->mc_id;
	ncm->data[1] = ntohl(cmd->mode);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_sl(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_cmd_sl_pkt *cmd;
	काष्ठा ncsi_rsp_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_channel_mode *ncm;

	/* Find the package and channel */
	rsp = (काष्ठा ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	cmd = (काष्ठा ncsi_cmd_sl_pkt *)skb_network_header(nr->cmd);
	ncm = &nc->modes[NCSI_MODE_LINK];
	ncm->data[0] = ntohl(cmd->mode);
	ncm->data[1] = ntohl(cmd->oem_mode);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_gls(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_gls_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_channel_mode *ncm;
	अचिन्हित दीर्घ flags;

	/* Find the package and channel */
	rsp = (काष्ठा ncsi_rsp_gls_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	ncm = &nc->modes[NCSI_MODE_LINK];
	ncm->data[2] = ntohl(rsp->status);
	ncm->data[3] = ntohl(rsp->other);
	ncm->data[4] = ntohl(rsp->oem_status);

	अगर (nr->flags & NCSI_REQ_FLAG_EVENT_DRIVEN)
		वापस 0;

	/* Reset the channel monitor अगर it has been enabled */
	spin_lock_irqsave(&nc->lock, flags);
	nc->monitor.state = NCSI_CHANNEL_MONITOR_START;
	spin_unlock_irqrestore(&nc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_svf(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_cmd_svf_pkt *cmd;
	काष्ठा ncsi_rsp_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_channel_vlan_filter *ncf;
	अचिन्हित दीर्घ flags;
	व्योम *biपंचांगap;

	/* Find the package and channel */
	rsp = (काष्ठा ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	cmd = (काष्ठा ncsi_cmd_svf_pkt *)skb_network_header(nr->cmd);
	ncf = &nc->vlan_filter;
	अगर (cmd->index == 0 || cmd->index > ncf->n_vids)
		वापस -दुस्फल;

	/* Add or हटाओ the VLAN filter. Remember HW indexes from 1 */
	spin_lock_irqsave(&nc->lock, flags);
	biपंचांगap = &ncf->biपंचांगap;
	अगर (!(cmd->enable & 0x1)) अणु
		अगर (test_and_clear_bit(cmd->index - 1, biपंचांगap))
			ncf->vids[cmd->index - 1] = 0;
	पूर्ण अन्यथा अणु
		set_bit(cmd->index - 1, biपंचांगap);
		ncf->vids[cmd->index - 1] = ntohs(cmd->vlan);
	पूर्ण
	spin_unlock_irqrestore(&nc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_ev(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_cmd_ev_pkt *cmd;
	काष्ठा ncsi_rsp_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_channel_mode *ncm;

	/* Find the package and channel */
	rsp = (काष्ठा ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	/* Check अगर VLAN mode has been enabled */
	ncm = &nc->modes[NCSI_MODE_VLAN];
	अगर (ncm->enable)
		वापस 0;

	/* Update to VLAN mode */
	cmd = (काष्ठा ncsi_cmd_ev_pkt *)skb_network_header(nr->cmd);
	ncm->enable = 1;
	ncm->data[0] = ntohl(cmd->mode);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_dv(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_channel_mode *ncm;

	/* Find the package and channel */
	rsp = (काष्ठा ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	/* Check अगर VLAN mode has been enabled */
	ncm = &nc->modes[NCSI_MODE_VLAN];
	अगर (!ncm->enable)
		वापस 0;

	/* Update to VLAN mode */
	ncm->enable = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_sma(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_cmd_sma_pkt *cmd;
	काष्ठा ncsi_rsp_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_channel_mac_filter *ncf;
	अचिन्हित दीर्घ flags;
	व्योम *biपंचांगap;
	bool enabled;
	पूर्णांक index;


	/* Find the package and channel */
	rsp = (काष्ठा ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	/* According to NCSI spec 1.01, the mixed filter table
	 * isn't supported yet.
	 */
	cmd = (काष्ठा ncsi_cmd_sma_pkt *)skb_network_header(nr->cmd);
	enabled = cmd->at_e & 0x1;
	ncf = &nc->mac_filter;
	biपंचांगap = &ncf->biपंचांगap;

	अगर (cmd->index == 0 ||
	    cmd->index > ncf->n_uc + ncf->n_mc + ncf->n_mixed)
		वापस -दुस्फल;

	index = (cmd->index - 1) * ETH_ALEN;
	spin_lock_irqsave(&nc->lock, flags);
	अगर (enabled) अणु
		set_bit(cmd->index - 1, biपंचांगap);
		स_नकल(&ncf->addrs[index], cmd->mac, ETH_ALEN);
	पूर्ण अन्यथा अणु
		clear_bit(cmd->index - 1, biपंचांगap);
		eth_zero_addr(&ncf->addrs[index]);
	पूर्ण
	spin_unlock_irqrestore(&nc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_ebf(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_cmd_ebf_pkt *cmd;
	काष्ठा ncsi_rsp_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_channel_mode *ncm;

	/* Find the package and channel */
	rsp = (काष्ठा ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel, शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	/* Check अगर broadcast filter has been enabled */
	ncm = &nc->modes[NCSI_MODE_BC];
	अगर (ncm->enable)
		वापस 0;

	/* Update to broadcast filter mode */
	cmd = (काष्ठा ncsi_cmd_ebf_pkt *)skb_network_header(nr->cmd);
	ncm->enable = 1;
	ncm->data[0] = ntohl(cmd->mode);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_dbf(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_channel_mode *ncm;

	rsp = (काष्ठा ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	/* Check अगर broadcast filter isn't enabled */
	ncm = &nc->modes[NCSI_MODE_BC];
	अगर (!ncm->enable)
		वापस 0;

	/* Update to broadcast filter mode */
	ncm->enable = 0;
	ncm->data[0] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_egmf(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_cmd_egmf_pkt *cmd;
	काष्ठा ncsi_rsp_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_channel_mode *ncm;

	/* Find the channel */
	rsp = (काष्ठा ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	/* Check अगर multicast filter has been enabled */
	ncm = &nc->modes[NCSI_MODE_MC];
	अगर (ncm->enable)
		वापस 0;

	/* Update to multicast filter mode */
	cmd = (काष्ठा ncsi_cmd_egmf_pkt *)skb_network_header(nr->cmd);
	ncm->enable = 1;
	ncm->data[0] = ntohl(cmd->mode);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_dgmf(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_channel_mode *ncm;

	rsp = (काष्ठा ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	/* Check अगर multicast filter has been enabled */
	ncm = &nc->modes[NCSI_MODE_MC];
	अगर (!ncm->enable)
		वापस 0;

	/* Update to multicast filter mode */
	ncm->enable = 0;
	ncm->data[0] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_snfc(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_cmd_snfc_pkt *cmd;
	काष्ठा ncsi_rsp_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_channel_mode *ncm;

	/* Find the channel */
	rsp = (काष्ठा ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	/* Check अगर flow control has been enabled */
	ncm = &nc->modes[NCSI_MODE_FC];
	अगर (ncm->enable)
		वापस 0;

	/* Update to flow control mode */
	cmd = (काष्ठा ncsi_cmd_snfc_pkt *)skb_network_header(nr->cmd);
	ncm->enable = 1;
	ncm->data[0] = cmd->mode;

	वापस 0;
पूर्ण

/* Response handler क्रम Mellanox command Get Mac Address */
अटल पूर्णांक ncsi_rsp_handler_oem_mlx_gma(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा net_device *ndev = ndp->ndev.dev;
	स्थिर काष्ठा net_device_ops *ops = ndev->netdev_ops;
	काष्ठा ncsi_rsp_oem_pkt *rsp;
	काष्ठा sockaddr saddr;
	पूर्णांक ret = 0;

	/* Get the response header */
	rsp = (काष्ठा ncsi_rsp_oem_pkt *)skb_network_header(nr->rsp);

	saddr.sa_family = ndev->type;
	ndev->priv_flags |= IFF_LIVE_ADDR_CHANGE;
	स_नकल(saddr.sa_data, &rsp->data[MLX_MAC_ADDR_OFFSET], ETH_ALEN);
	/* Set the flag क्रम GMA command which should only be called once */
	ndp->gma_flag = 1;

	ret = ops->nकरो_set_mac_address(ndev, &saddr);
	अगर (ret < 0)
		netdev_warn(ndev, "NCSI: 'Writing mac address to device failed\n");

	वापस ret;
पूर्ण

/* Response handler क्रम Mellanox card */
अटल पूर्णांक ncsi_rsp_handler_oem_mlx(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_oem_mlx_pkt *mlx;
	काष्ठा ncsi_rsp_oem_pkt *rsp;

	/* Get the response header */
	rsp = (काष्ठा ncsi_rsp_oem_pkt *)skb_network_header(nr->rsp);
	mlx = (काष्ठा ncsi_rsp_oem_mlx_pkt *)(rsp->data);

	अगर (mlx->cmd == NCSI_OEM_MLX_CMD_GMA &&
	    mlx->param == NCSI_OEM_MLX_CMD_GMA_PARAM)
		वापस ncsi_rsp_handler_oem_mlx_gma(nr);
	वापस 0;
पूर्ण

/* Response handler क्रम Broadcom command Get Mac Address */
अटल पूर्णांक ncsi_rsp_handler_oem_bcm_gma(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा net_device *ndev = ndp->ndev.dev;
	स्थिर काष्ठा net_device_ops *ops = ndev->netdev_ops;
	काष्ठा ncsi_rsp_oem_pkt *rsp;
	काष्ठा sockaddr saddr;
	पूर्णांक ret = 0;

	/* Get the response header */
	rsp = (काष्ठा ncsi_rsp_oem_pkt *)skb_network_header(nr->rsp);

	saddr.sa_family = ndev->type;
	ndev->priv_flags |= IFF_LIVE_ADDR_CHANGE;
	स_नकल(saddr.sa_data, &rsp->data[BCM_MAC_ADDR_OFFSET], ETH_ALEN);
	/* Increase mac address by 1 क्रम BMC's address */
	eth_addr_inc((u8 *)saddr.sa_data);
	अगर (!is_valid_ether_addr((स्थिर u8 *)saddr.sa_data))
		वापस -ENXIO;

	/* Set the flag क्रम GMA command which should only be called once */
	ndp->gma_flag = 1;

	ret = ops->nकरो_set_mac_address(ndev, &saddr);
	अगर (ret < 0)
		netdev_warn(ndev, "NCSI: 'Writing mac address to device failed\n");

	वापस ret;
पूर्ण

/* Response handler क्रम Broadcom card */
अटल पूर्णांक ncsi_rsp_handler_oem_bcm(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_oem_bcm_pkt *bcm;
	काष्ठा ncsi_rsp_oem_pkt *rsp;

	/* Get the response header */
	rsp = (काष्ठा ncsi_rsp_oem_pkt *)skb_network_header(nr->rsp);
	bcm = (काष्ठा ncsi_rsp_oem_bcm_pkt *)(rsp->data);

	अगर (bcm->type == NCSI_OEM_BCM_CMD_GMA)
		वापस ncsi_rsp_handler_oem_bcm_gma(nr);
	वापस 0;
पूर्ण

अटल काष्ठा ncsi_rsp_oem_handler अणु
	अचिन्हित पूर्णांक	mfr_id;
	पूर्णांक		(*handler)(काष्ठा ncsi_request *nr);
पूर्ण ncsi_rsp_oem_handlers[] = अणु
	अणु NCSI_OEM_MFR_MLX_ID, ncsi_rsp_handler_oem_mlx पूर्ण,
	अणु NCSI_OEM_MFR_BCM_ID, ncsi_rsp_handler_oem_bcm पूर्ण
पूर्ण;

/* Response handler क्रम OEM command */
अटल पूर्णांक ncsi_rsp_handler_oem(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_oem_handler *nrh = शून्य;
	काष्ठा ncsi_rsp_oem_pkt *rsp;
	अचिन्हित पूर्णांक mfr_id, i;

	/* Get the response header */
	rsp = (काष्ठा ncsi_rsp_oem_pkt *)skb_network_header(nr->rsp);
	mfr_id = ntohl(rsp->mfr_id);

	/* Check क्रम manufacturer id and Find the handler */
	क्रम (i = 0; i < ARRAY_SIZE(ncsi_rsp_oem_handlers); i++) अणु
		अगर (ncsi_rsp_oem_handlers[i].mfr_id == mfr_id) अणु
			अगर (ncsi_rsp_oem_handlers[i].handler)
				nrh = &ncsi_rsp_oem_handlers[i];
			अन्यथा
				nrh = शून्य;

			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!nrh) अणु
		netdev_err(nr->ndp->ndev.dev, "Received unrecognized OEM packet with MFR-ID (0x%x)\n",
			   mfr_id);
		वापस -ENOENT;
	पूर्ण

	/* Process the packet */
	वापस nrh->handler(nr);
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_gvi(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_gvi_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_channel_version *ncv;
	पूर्णांक i;

	/* Find the channel */
	rsp = (काष्ठा ncsi_rsp_gvi_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	/* Update to channel's version info */
	ncv = &nc->version;
	ncv->version = ntohl(rsp->ncsi_version);
	ncv->alpha2 = rsp->alpha2;
	स_नकल(ncv->fw_name, rsp->fw_name, 12);
	ncv->fw_version = ntohl(rsp->fw_version);
	क्रम (i = 0; i < ARRAY_SIZE(ncv->pci_ids); i++)
		ncv->pci_ids[i] = ntohs(rsp->pci_ids[i]);
	ncv->mf_id = ntohl(rsp->mf_id);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_gc(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_gc_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	माप_प्रकार size;

	/* Find the channel */
	rsp = (काष्ठा ncsi_rsp_gc_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	/* Update channel's capabilities */
	nc->caps[NCSI_CAP_GENERIC].cap = ntohl(rsp->cap) &
					 NCSI_CAP_GENERIC_MASK;
	nc->caps[NCSI_CAP_BC].cap = ntohl(rsp->bc_cap) &
				    NCSI_CAP_BC_MASK;
	nc->caps[NCSI_CAP_MC].cap = ntohl(rsp->mc_cap) &
				    NCSI_CAP_MC_MASK;
	nc->caps[NCSI_CAP_BUFFER].cap = ntohl(rsp->buf_cap);
	nc->caps[NCSI_CAP_AEN].cap = ntohl(rsp->aen_cap) &
				     NCSI_CAP_AEN_MASK;
	nc->caps[NCSI_CAP_VLAN].cap = rsp->vlan_mode &
				      NCSI_CAP_VLAN_MASK;

	size = (rsp->uc_cnt + rsp->mc_cnt + rsp->mixed_cnt) * ETH_ALEN;
	nc->mac_filter.addrs = kzalloc(size, GFP_ATOMIC);
	अगर (!nc->mac_filter.addrs)
		वापस -ENOMEM;
	nc->mac_filter.n_uc = rsp->uc_cnt;
	nc->mac_filter.n_mc = rsp->mc_cnt;
	nc->mac_filter.n_mixed = rsp->mixed_cnt;

	nc->vlan_filter.vids = kसुस्मृति(rsp->vlan_cnt,
				       माप(*nc->vlan_filter.vids),
				       GFP_ATOMIC);
	अगर (!nc->vlan_filter.vids)
		वापस -ENOMEM;
	/* Set VLAN filters active so they are cleared in the first
	 * configuration state
	 */
	nc->vlan_filter.biपंचांगap = U64_MAX;
	nc->vlan_filter.n_vids = rsp->vlan_cnt;

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_gp(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_channel_vlan_filter *ncvf;
	काष्ठा ncsi_channel_mac_filter *ncmf;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_rsp_gp_pkt *rsp;
	काष्ठा ncsi_channel *nc;
	अचिन्हित लघु enable;
	अचिन्हित अक्षर *pdata;
	अचिन्हित दीर्घ flags;
	व्योम *biपंचांगap;
	पूर्णांक i;

	/* Find the channel */
	rsp = (काष्ठा ncsi_rsp_gp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	/* Modes with explicit enabled indications */
	अगर (ntohl(rsp->valid_modes) & 0x1) अणु	/* BC filter mode */
		nc->modes[NCSI_MODE_BC].enable = 1;
		nc->modes[NCSI_MODE_BC].data[0] = ntohl(rsp->bc_mode);
	पूर्ण
	अगर (ntohl(rsp->valid_modes) & 0x2)	/* Channel enabled */
		nc->modes[NCSI_MODE_ENABLE].enable = 1;
	अगर (ntohl(rsp->valid_modes) & 0x4)	/* Channel Tx enabled */
		nc->modes[NCSI_MODE_TX_ENABLE].enable = 1;
	अगर (ntohl(rsp->valid_modes) & 0x8)	/* MC filter mode */
		nc->modes[NCSI_MODE_MC].enable = 1;

	/* Modes without explicit enabled indications */
	nc->modes[NCSI_MODE_LINK].enable = 1;
	nc->modes[NCSI_MODE_LINK].data[0] = ntohl(rsp->link_mode);
	nc->modes[NCSI_MODE_VLAN].enable = 1;
	nc->modes[NCSI_MODE_VLAN].data[0] = rsp->vlan_mode;
	nc->modes[NCSI_MODE_FC].enable = 1;
	nc->modes[NCSI_MODE_FC].data[0] = rsp->fc_mode;
	nc->modes[NCSI_MODE_AEN].enable = 1;
	nc->modes[NCSI_MODE_AEN].data[0] = ntohl(rsp->aen_mode);

	/* MAC addresses filter table */
	pdata = (अचिन्हित अक्षर *)rsp + 48;
	enable = rsp->mac_enable;
	ncmf = &nc->mac_filter;
	spin_lock_irqsave(&nc->lock, flags);
	biपंचांगap = &ncmf->biपंचांगap;
	क्रम (i = 0; i < rsp->mac_cnt; i++, pdata += 6) अणु
		अगर (!(enable & (0x1 << i)))
			clear_bit(i, biपंचांगap);
		अन्यथा
			set_bit(i, biपंचांगap);

		स_नकल(&ncmf->addrs[i * ETH_ALEN], pdata, ETH_ALEN);
	पूर्ण
	spin_unlock_irqrestore(&nc->lock, flags);

	/* VLAN filter table */
	enable = ntohs(rsp->vlan_enable);
	ncvf = &nc->vlan_filter;
	biपंचांगap = &ncvf->biपंचांगap;
	spin_lock_irqsave(&nc->lock, flags);
	क्रम (i = 0; i < rsp->vlan_cnt; i++, pdata += 2) अणु
		अगर (!(enable & (0x1 << i)))
			clear_bit(i, biपंचांगap);
		अन्यथा
			set_bit(i, biपंचांगap);

		ncvf->vids[i] = ntohs(*(__be16 *)pdata);
	पूर्ण
	spin_unlock_irqrestore(&nc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_gcps(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_gcps_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_channel_stats *ncs;

	/* Find the channel */
	rsp = (काष्ठा ncsi_rsp_gcps_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	/* Update HNC's statistics */
	ncs = &nc->stats;
	ncs->hnc_cnt_hi         = ntohl(rsp->cnt_hi);
	ncs->hnc_cnt_lo         = ntohl(rsp->cnt_lo);
	ncs->hnc_rx_bytes       = ntohl(rsp->rx_bytes);
	ncs->hnc_tx_bytes       = ntohl(rsp->tx_bytes);
	ncs->hnc_rx_uc_pkts     = ntohl(rsp->rx_uc_pkts);
	ncs->hnc_rx_mc_pkts     = ntohl(rsp->rx_mc_pkts);
	ncs->hnc_rx_bc_pkts     = ntohl(rsp->rx_bc_pkts);
	ncs->hnc_tx_uc_pkts     = ntohl(rsp->tx_uc_pkts);
	ncs->hnc_tx_mc_pkts     = ntohl(rsp->tx_mc_pkts);
	ncs->hnc_tx_bc_pkts     = ntohl(rsp->tx_bc_pkts);
	ncs->hnc_fcs_err        = ntohl(rsp->fcs_err);
	ncs->hnc_align_err      = ntohl(rsp->align_err);
	ncs->hnc_false_carrier  = ntohl(rsp->false_carrier);
	ncs->hnc_runt_pkts      = ntohl(rsp->runt_pkts);
	ncs->hnc_jabber_pkts    = ntohl(rsp->jabber_pkts);
	ncs->hnc_rx_छोड़ो_xon   = ntohl(rsp->rx_छोड़ो_xon);
	ncs->hnc_rx_छोड़ो_xoff  = ntohl(rsp->rx_छोड़ो_xoff);
	ncs->hnc_tx_छोड़ो_xon   = ntohl(rsp->tx_छोड़ो_xon);
	ncs->hnc_tx_छोड़ो_xoff  = ntohl(rsp->tx_छोड़ो_xoff);
	ncs->hnc_tx_s_collision = ntohl(rsp->tx_s_collision);
	ncs->hnc_tx_m_collision = ntohl(rsp->tx_m_collision);
	ncs->hnc_l_collision    = ntohl(rsp->l_collision);
	ncs->hnc_e_collision    = ntohl(rsp->e_collision);
	ncs->hnc_rx_ctl_frames  = ntohl(rsp->rx_ctl_frames);
	ncs->hnc_rx_64_frames   = ntohl(rsp->rx_64_frames);
	ncs->hnc_rx_127_frames  = ntohl(rsp->rx_127_frames);
	ncs->hnc_rx_255_frames  = ntohl(rsp->rx_255_frames);
	ncs->hnc_rx_511_frames  = ntohl(rsp->rx_511_frames);
	ncs->hnc_rx_1023_frames = ntohl(rsp->rx_1023_frames);
	ncs->hnc_rx_1522_frames = ntohl(rsp->rx_1522_frames);
	ncs->hnc_rx_9022_frames = ntohl(rsp->rx_9022_frames);
	ncs->hnc_tx_64_frames   = ntohl(rsp->tx_64_frames);
	ncs->hnc_tx_127_frames  = ntohl(rsp->tx_127_frames);
	ncs->hnc_tx_255_frames  = ntohl(rsp->tx_255_frames);
	ncs->hnc_tx_511_frames  = ntohl(rsp->tx_511_frames);
	ncs->hnc_tx_1023_frames = ntohl(rsp->tx_1023_frames);
	ncs->hnc_tx_1522_frames = ntohl(rsp->tx_1522_frames);
	ncs->hnc_tx_9022_frames = ntohl(rsp->tx_9022_frames);
	ncs->hnc_rx_valid_bytes = ntohl(rsp->rx_valid_bytes);
	ncs->hnc_rx_runt_pkts   = ntohl(rsp->rx_runt_pkts);
	ncs->hnc_rx_jabber_pkts = ntohl(rsp->rx_jabber_pkts);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_gns(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_gns_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_channel_stats *ncs;

	/* Find the channel */
	rsp = (काष्ठा ncsi_rsp_gns_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	/* Update HNC's statistics */
	ncs = &nc->stats;
	ncs->ncsi_rx_cmds       = ntohl(rsp->rx_cmds);
	ncs->ncsi_dropped_cmds  = ntohl(rsp->dropped_cmds);
	ncs->ncsi_cmd_type_errs = ntohl(rsp->cmd_type_errs);
	ncs->ncsi_cmd_csum_errs = ntohl(rsp->cmd_csum_errs);
	ncs->ncsi_rx_pkts       = ntohl(rsp->rx_pkts);
	ncs->ncsi_tx_pkts       = ntohl(rsp->tx_pkts);
	ncs->ncsi_tx_aen_pkts   = ntohl(rsp->tx_aen_pkts);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_gnpts(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_gnpts_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_channel *nc;
	काष्ठा ncsi_channel_stats *ncs;

	/* Find the channel */
	rsp = (काष्ठा ncsi_rsp_gnpts_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      शून्य, &nc);
	अगर (!nc)
		वापस -ENODEV;

	/* Update HNC's statistics */
	ncs = &nc->stats;
	ncs->pt_tx_pkts        = ntohl(rsp->tx_pkts);
	ncs->pt_tx_dropped     = ntohl(rsp->tx_dropped);
	ncs->pt_tx_channel_err = ntohl(rsp->tx_channel_err);
	ncs->pt_tx_us_err      = ntohl(rsp->tx_us_err);
	ncs->pt_rx_pkts        = ntohl(rsp->rx_pkts);
	ncs->pt_rx_dropped     = ntohl(rsp->rx_dropped);
	ncs->pt_rx_channel_err = ntohl(rsp->rx_channel_err);
	ncs->pt_rx_us_err      = ntohl(rsp->rx_us_err);
	ncs->pt_rx_os_err      = ntohl(rsp->rx_os_err);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_gps(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_gps_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_package *np;

	/* Find the package */
	rsp = (काष्ठा ncsi_rsp_gps_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      &np, शून्य);
	अगर (!np)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_gpuuid(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_rsp_gpuuid_pkt *rsp;
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_package *np;

	/* Find the package */
	rsp = (काष्ठा ncsi_rsp_gpuuid_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      &np, शून्य);
	अगर (!np)
		वापस -ENODEV;

	स_नकल(np->uuid, rsp->uuid, माप(rsp->uuid));

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_pldm(काष्ठा ncsi_request *nr)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_rsp_handler_netlink(काष्ठा ncsi_request *nr)
अणु
	काष्ठा ncsi_dev_priv *ndp = nr->ndp;
	काष्ठा ncsi_rsp_pkt *rsp;
	काष्ठा ncsi_package *np;
	काष्ठा ncsi_channel *nc;
	पूर्णांक ret;

	/* Find the package */
	rsp = (काष्ठा ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      &np, &nc);
	अगर (!np)
		वापस -ENODEV;

	ret = ncsi_send_netlink_rsp(nr, np, nc);

	वापस ret;
पूर्ण

अटल काष्ठा ncsi_rsp_handler अणु
	अचिन्हित अक्षर	type;
	पूर्णांक             payload;
	पूर्णांक		(*handler)(काष्ठा ncsi_request *nr);
पूर्ण ncsi_rsp_handlers[] = अणु
	अणु NCSI_PKT_RSP_CIS,     4, ncsi_rsp_handler_cis     पूर्ण,
	अणु NCSI_PKT_RSP_SP,      4, ncsi_rsp_handler_sp      पूर्ण,
	अणु NCSI_PKT_RSP_DP,      4, ncsi_rsp_handler_dp      पूर्ण,
	अणु NCSI_PKT_RSP_EC,      4, ncsi_rsp_handler_ec      पूर्ण,
	अणु NCSI_PKT_RSP_DC,      4, ncsi_rsp_handler_dc      पूर्ण,
	अणु NCSI_PKT_RSP_RC,      4, ncsi_rsp_handler_rc      पूर्ण,
	अणु NCSI_PKT_RSP_ECNT,    4, ncsi_rsp_handler_ecnt    पूर्ण,
	अणु NCSI_PKT_RSP_DCNT,    4, ncsi_rsp_handler_dcnt    पूर्ण,
	अणु NCSI_PKT_RSP_AE,      4, ncsi_rsp_handler_ae      पूर्ण,
	अणु NCSI_PKT_RSP_SL,      4, ncsi_rsp_handler_sl      पूर्ण,
	अणु NCSI_PKT_RSP_GLS,    16, ncsi_rsp_handler_gls     पूर्ण,
	अणु NCSI_PKT_RSP_SVF,     4, ncsi_rsp_handler_svf     पूर्ण,
	अणु NCSI_PKT_RSP_EV,      4, ncsi_rsp_handler_ev      पूर्ण,
	अणु NCSI_PKT_RSP_DV,      4, ncsi_rsp_handler_dv      पूर्ण,
	अणु NCSI_PKT_RSP_SMA,     4, ncsi_rsp_handler_sma     पूर्ण,
	अणु NCSI_PKT_RSP_EBF,     4, ncsi_rsp_handler_ebf     पूर्ण,
	अणु NCSI_PKT_RSP_DBF,     4, ncsi_rsp_handler_dbf     पूर्ण,
	अणु NCSI_PKT_RSP_EGMF,    4, ncsi_rsp_handler_egmf    पूर्ण,
	अणु NCSI_PKT_RSP_DGMF,    4, ncsi_rsp_handler_dgmf    पूर्ण,
	अणु NCSI_PKT_RSP_SNFC,    4, ncsi_rsp_handler_snfc    पूर्ण,
	अणु NCSI_PKT_RSP_GVI,    40, ncsi_rsp_handler_gvi     पूर्ण,
	अणु NCSI_PKT_RSP_GC,     32, ncsi_rsp_handler_gc      पूर्ण,
	अणु NCSI_PKT_RSP_GP,     -1, ncsi_rsp_handler_gp      पूर्ण,
	अणु NCSI_PKT_RSP_GCPS,  204, ncsi_rsp_handler_gcps    पूर्ण,
	अणु NCSI_PKT_RSP_GNS,    32, ncsi_rsp_handler_gns     पूर्ण,
	अणु NCSI_PKT_RSP_GNPTS,  48, ncsi_rsp_handler_gnpts   पूर्ण,
	अणु NCSI_PKT_RSP_GPS,     8, ncsi_rsp_handler_gps     पूर्ण,
	अणु NCSI_PKT_RSP_OEM,    -1, ncsi_rsp_handler_oem     पूर्ण,
	अणु NCSI_PKT_RSP_PLDM,   -1, ncsi_rsp_handler_pldm    पूर्ण,
	अणु NCSI_PKT_RSP_GPUUID, 20, ncsi_rsp_handler_gpuuid  पूर्ण,
	अणु NCSI_PKT_RSP_QPNPR,  -1, ncsi_rsp_handler_pldm    पूर्ण,
	अणु NCSI_PKT_RSP_SNPR,   -1, ncsi_rsp_handler_pldm    पूर्ण
पूर्ण;

पूर्णांक ncsi_rcv_rsp(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		 काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	काष्ठा ncsi_rsp_handler *nrh = शून्य;
	काष्ठा ncsi_dev *nd;
	काष्ठा ncsi_dev_priv *ndp;
	काष्ठा ncsi_request *nr;
	काष्ठा ncsi_pkt_hdr *hdr;
	अचिन्हित दीर्घ flags;
	पूर्णांक payload, i, ret;

	/* Find the NCSI device */
	nd = ncsi_find_dev(orig_dev);
	ndp = nd ? TO_NCSI_DEV_PRIV(nd) : शून्य;
	अगर (!ndp)
		वापस -ENODEV;

	/* Check अगर it is AEN packet */
	hdr = (काष्ठा ncsi_pkt_hdr *)skb_network_header(skb);
	अगर (hdr->type == NCSI_PKT_AEN)
		वापस ncsi_aen_handler(ndp, skb);

	/* Find the handler */
	क्रम (i = 0; i < ARRAY_SIZE(ncsi_rsp_handlers); i++) अणु
		अगर (ncsi_rsp_handlers[i].type == hdr->type) अणु
			अगर (ncsi_rsp_handlers[i].handler)
				nrh = &ncsi_rsp_handlers[i];
			अन्यथा
				nrh = शून्य;

			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!nrh) अणु
		netdev_err(nd->dev, "Received unrecognized packet (0x%x)\n",
			   hdr->type);
		वापस -ENOENT;
	पूर्ण

	/* Associate with the request */
	spin_lock_irqsave(&ndp->lock, flags);
	nr = &ndp->requests[hdr->id];
	अगर (!nr->used) अणु
		spin_unlock_irqrestore(&ndp->lock, flags);
		वापस -ENODEV;
	पूर्ण

	nr->rsp = skb;
	अगर (!nr->enabled) अणु
		spin_unlock_irqrestore(&ndp->lock, flags);
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	/* Validate the packet */
	spin_unlock_irqrestore(&ndp->lock, flags);
	payload = nrh->payload;
	अगर (payload < 0)
		payload = ntohs(hdr->length);
	ret = ncsi_validate_rsp_pkt(nr, payload);
	अगर (ret) अणु
		netdev_warn(ndp->ndev.dev,
			    "NCSI: 'bad' packet ignored for type 0x%x\n",
			    hdr->type);

		अगर (nr->flags == NCSI_REQ_FLAG_NETLINK_DRIVEN) अणु
			अगर (ret == -EPERM)
				जाओ out_netlink;
			अन्यथा
				ncsi_send_netlink_err(ndp->ndev.dev,
						      nr->snd_seq,
						      nr->snd_portid,
						      &nr->nlhdr,
						      ret);
		पूर्ण
		जाओ out;
	पूर्ण

	/* Process the packet */
	ret = nrh->handler(nr);
	अगर (ret)
		netdev_err(ndp->ndev.dev,
			   "NCSI: Handler for packet type 0x%x returned %d\n",
			   hdr->type, ret);

out_netlink:
	अगर (nr->flags == NCSI_REQ_FLAG_NETLINK_DRIVEN) अणु
		ret = ncsi_rsp_handler_netlink(nr);
		अगर (ret) अणु
			netdev_err(ndp->ndev.dev,
				   "NCSI: Netlink handler for packet type 0x%x returned %d\n",
				   hdr->type, ret);
		पूर्ण
	पूर्ण

out:
	ncsi_मुक्त_request(nr);
	वापस ret;
पूर्ण
