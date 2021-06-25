<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright Gavin Shan, IBM Corporation 2016.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>

#समावेश <net/ncsi.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <net/genetlink.h>

#समावेश "internal.h"
#समावेश "ncsi-pkt.h"

u32 ncsi_calculate_checksum(अचिन्हित अक्षर *data, पूर्णांक len)
अणु
	u32 checksum = 0;
	पूर्णांक i;

	क्रम (i = 0; i < len; i += 2)
		checksum += (((u32)data[i] << 8) | data[i + 1]);

	checksum = (~checksum + 1);
	वापस checksum;
पूर्ण

/* This function should be called after the data area has been
 * populated completely.
 */
अटल व्योम ncsi_cmd_build_header(काष्ठा ncsi_pkt_hdr *h,
				  काष्ठा ncsi_cmd_arg *nca)
अणु
	u32 checksum;
	__be32 *pchecksum;

	h->mc_id        = 0;
	h->revision     = NCSI_PKT_REVISION;
	h->reserved     = 0;
	h->id           = nca->id;
	h->type         = nca->type;
	h->channel      = NCSI_TO_CHANNEL(nca->package,
					  nca->channel);
	h->length       = htons(nca->payload);
	h->reserved1[0] = 0;
	h->reserved1[1] = 0;

	/* Fill with calculated checksum */
	checksum = ncsi_calculate_checksum((अचिन्हित अक्षर *)h,
					   माप(*h) + nca->payload);
	pchecksum = (__be32 *)((व्योम *)h + माप(काष्ठा ncsi_pkt_hdr) +
		    ALIGN(nca->payload, 4));
	*pchecksum = htonl(checksum);
पूर्ण

अटल पूर्णांक ncsi_cmd_handler_शेष(काष्ठा sk_buff *skb,
				    काष्ठा ncsi_cmd_arg *nca)
अणु
	काष्ठा ncsi_cmd_pkt *cmd;

	cmd = skb_put_zero(skb, माप(*cmd));
	ncsi_cmd_build_header(&cmd->cmd.common, nca);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_cmd_handler_sp(काष्ठा sk_buff *skb,
			       काष्ठा ncsi_cmd_arg *nca)
अणु
	काष्ठा ncsi_cmd_sp_pkt *cmd;

	cmd = skb_put_zero(skb, माप(*cmd));
	cmd->hw_arbitration = nca->bytes[0];
	ncsi_cmd_build_header(&cmd->cmd.common, nca);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_cmd_handler_dc(काष्ठा sk_buff *skb,
			       काष्ठा ncsi_cmd_arg *nca)
अणु
	काष्ठा ncsi_cmd_dc_pkt *cmd;

	cmd = skb_put_zero(skb, माप(*cmd));
	cmd->ald = nca->bytes[0];
	ncsi_cmd_build_header(&cmd->cmd.common, nca);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_cmd_handler_rc(काष्ठा sk_buff *skb,
			       काष्ठा ncsi_cmd_arg *nca)
अणु
	काष्ठा ncsi_cmd_rc_pkt *cmd;

	cmd = skb_put_zero(skb, माप(*cmd));
	ncsi_cmd_build_header(&cmd->cmd.common, nca);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_cmd_handler_ae(काष्ठा sk_buff *skb,
			       काष्ठा ncsi_cmd_arg *nca)
अणु
	काष्ठा ncsi_cmd_ae_pkt *cmd;

	cmd = skb_put_zero(skb, माप(*cmd));
	cmd->mc_id = nca->bytes[0];
	cmd->mode = htonl(nca->dwords[1]);
	ncsi_cmd_build_header(&cmd->cmd.common, nca);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_cmd_handler_sl(काष्ठा sk_buff *skb,
			       काष्ठा ncsi_cmd_arg *nca)
अणु
	काष्ठा ncsi_cmd_sl_pkt *cmd;

	cmd = skb_put_zero(skb, माप(*cmd));
	cmd->mode = htonl(nca->dwords[0]);
	cmd->oem_mode = htonl(nca->dwords[1]);
	ncsi_cmd_build_header(&cmd->cmd.common, nca);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_cmd_handler_svf(काष्ठा sk_buff *skb,
				काष्ठा ncsi_cmd_arg *nca)
अणु
	काष्ठा ncsi_cmd_svf_pkt *cmd;

	cmd = skb_put_zero(skb, माप(*cmd));
	cmd->vlan = htons(nca->words[1]);
	cmd->index = nca->bytes[6];
	cmd->enable = nca->bytes[7];
	ncsi_cmd_build_header(&cmd->cmd.common, nca);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_cmd_handler_ev(काष्ठा sk_buff *skb,
			       काष्ठा ncsi_cmd_arg *nca)
अणु
	काष्ठा ncsi_cmd_ev_pkt *cmd;

	cmd = skb_put_zero(skb, माप(*cmd));
	cmd->mode = nca->bytes[3];
	ncsi_cmd_build_header(&cmd->cmd.common, nca);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_cmd_handler_sma(काष्ठा sk_buff *skb,
				काष्ठा ncsi_cmd_arg *nca)
अणु
	काष्ठा ncsi_cmd_sma_pkt *cmd;
	पूर्णांक i;

	cmd = skb_put_zero(skb, माप(*cmd));
	क्रम (i = 0; i < 6; i++)
		cmd->mac[i] = nca->bytes[i];
	cmd->index = nca->bytes[6];
	cmd->at_e = nca->bytes[7];
	ncsi_cmd_build_header(&cmd->cmd.common, nca);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_cmd_handler_ebf(काष्ठा sk_buff *skb,
				काष्ठा ncsi_cmd_arg *nca)
अणु
	काष्ठा ncsi_cmd_ebf_pkt *cmd;

	cmd = skb_put_zero(skb, माप(*cmd));
	cmd->mode = htonl(nca->dwords[0]);
	ncsi_cmd_build_header(&cmd->cmd.common, nca);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_cmd_handler_egmf(काष्ठा sk_buff *skb,
				 काष्ठा ncsi_cmd_arg *nca)
अणु
	काष्ठा ncsi_cmd_egmf_pkt *cmd;

	cmd = skb_put_zero(skb, माप(*cmd));
	cmd->mode = htonl(nca->dwords[0]);
	ncsi_cmd_build_header(&cmd->cmd.common, nca);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_cmd_handler_snfc(काष्ठा sk_buff *skb,
				 काष्ठा ncsi_cmd_arg *nca)
अणु
	काष्ठा ncsi_cmd_snfc_pkt *cmd;

	cmd = skb_put_zero(skb, माप(*cmd));
	cmd->mode = nca->bytes[0];
	ncsi_cmd_build_header(&cmd->cmd.common, nca);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_cmd_handler_oem(काष्ठा sk_buff *skb,
				काष्ठा ncsi_cmd_arg *nca)
अणु
	काष्ठा ncsi_cmd_oem_pkt *cmd;
	अचिन्हित पूर्णांक len;

	len = माप(काष्ठा ncsi_cmd_pkt_hdr) + 4;
	अगर (nca->payload < 26)
		len += 26;
	अन्यथा
		len += nca->payload;

	cmd = skb_put_zero(skb, len);
	स_नकल(&cmd->mfr_id, nca->data, nca->payload);
	ncsi_cmd_build_header(&cmd->cmd.common, nca);

	वापस 0;
पूर्ण

अटल काष्ठा ncsi_cmd_handler अणु
	अचिन्हित अक्षर type;
	पूर्णांक           payload;
	पूर्णांक           (*handler)(काष्ठा sk_buff *skb,
				 काष्ठा ncsi_cmd_arg *nca);
पूर्ण ncsi_cmd_handlers[] = अणु
	अणु NCSI_PKT_CMD_CIS,    0, ncsi_cmd_handler_शेष पूर्ण,
	अणु NCSI_PKT_CMD_SP,     4, ncsi_cmd_handler_sp      पूर्ण,
	अणु NCSI_PKT_CMD_DP,     0, ncsi_cmd_handler_शेष पूर्ण,
	अणु NCSI_PKT_CMD_EC,     0, ncsi_cmd_handler_शेष पूर्ण,
	अणु NCSI_PKT_CMD_DC,     4, ncsi_cmd_handler_dc      पूर्ण,
	अणु NCSI_PKT_CMD_RC,     4, ncsi_cmd_handler_rc      पूर्ण,
	अणु NCSI_PKT_CMD_ECNT,   0, ncsi_cmd_handler_शेष पूर्ण,
	अणु NCSI_PKT_CMD_DCNT,   0, ncsi_cmd_handler_शेष पूर्ण,
	अणु NCSI_PKT_CMD_AE,     8, ncsi_cmd_handler_ae      पूर्ण,
	अणु NCSI_PKT_CMD_SL,     8, ncsi_cmd_handler_sl      पूर्ण,
	अणु NCSI_PKT_CMD_GLS,    0, ncsi_cmd_handler_शेष पूर्ण,
	अणु NCSI_PKT_CMD_SVF,    8, ncsi_cmd_handler_svf     पूर्ण,
	अणु NCSI_PKT_CMD_EV,     4, ncsi_cmd_handler_ev      पूर्ण,
	अणु NCSI_PKT_CMD_DV,     0, ncsi_cmd_handler_शेष पूर्ण,
	अणु NCSI_PKT_CMD_SMA,    8, ncsi_cmd_handler_sma     पूर्ण,
	अणु NCSI_PKT_CMD_EBF,    4, ncsi_cmd_handler_ebf     पूर्ण,
	अणु NCSI_PKT_CMD_DBF,    0, ncsi_cmd_handler_शेष पूर्ण,
	अणु NCSI_PKT_CMD_EGMF,   4, ncsi_cmd_handler_egmf    पूर्ण,
	अणु NCSI_PKT_CMD_DGMF,   0, ncsi_cmd_handler_शेष पूर्ण,
	अणु NCSI_PKT_CMD_SNFC,   4, ncsi_cmd_handler_snfc    पूर्ण,
	अणु NCSI_PKT_CMD_GVI,    0, ncsi_cmd_handler_शेष पूर्ण,
	अणु NCSI_PKT_CMD_GC,     0, ncsi_cmd_handler_शेष पूर्ण,
	अणु NCSI_PKT_CMD_GP,     0, ncsi_cmd_handler_शेष पूर्ण,
	अणु NCSI_PKT_CMD_GCPS,   0, ncsi_cmd_handler_शेष पूर्ण,
	अणु NCSI_PKT_CMD_GNS,    0, ncsi_cmd_handler_शेष पूर्ण,
	अणु NCSI_PKT_CMD_GNPTS,  0, ncsi_cmd_handler_शेष पूर्ण,
	अणु NCSI_PKT_CMD_GPS,    0, ncsi_cmd_handler_शेष पूर्ण,
	अणु NCSI_PKT_CMD_OEM,   -1, ncsi_cmd_handler_oem     पूर्ण,
	अणु NCSI_PKT_CMD_PLDM,   0, शून्य                     पूर्ण,
	अणु NCSI_PKT_CMD_GPUUID, 0, ncsi_cmd_handler_शेष पूर्ण
पूर्ण;

अटल काष्ठा ncsi_request *ncsi_alloc_command(काष्ठा ncsi_cmd_arg *nca)
अणु
	काष्ठा ncsi_dev_priv *ndp = nca->ndp;
	काष्ठा ncsi_dev *nd = &ndp->ndev;
	काष्ठा net_device *dev = nd->dev;
	पूर्णांक hlen = LL_RESERVED_SPACE(dev);
	पूर्णांक tlen = dev->needed_tailroom;
	पूर्णांक len = hlen + tlen;
	काष्ठा sk_buff *skb;
	काष्ठा ncsi_request *nr;

	nr = ncsi_alloc_request(ndp, nca->req_flags);
	अगर (!nr)
		वापस शून्य;

	/* NCSI command packet has 16-bytes header, payload, 4 bytes checksum.
	 * The packet needs padding अगर its payload is less than 26 bytes to
	 * meet 64 bytes minimal ethernet frame length.
	 */
	len += माप(काष्ठा ncsi_cmd_pkt_hdr) + 4;
	अगर (nca->payload < 26)
		len += 26;
	अन्यथा
		len += nca->payload;

	/* Allocate skb */
	skb = alloc_skb(len, GFP_ATOMIC);
	अगर (!skb) अणु
		ncsi_मुक्त_request(nr);
		वापस शून्य;
	पूर्ण

	nr->cmd = skb;
	skb_reserve(skb, hlen);
	skb_reset_network_header(skb);

	skb->dev = dev;
	skb->protocol = htons(ETH_P_NCSI);

	वापस nr;
पूर्ण

पूर्णांक ncsi_xmit_cmd(काष्ठा ncsi_cmd_arg *nca)
अणु
	काष्ठा ncsi_cmd_handler *nch = शून्य;
	काष्ठा ncsi_request *nr;
	अचिन्हित अक्षर type;
	काष्ठा ethhdr *eh;
	पूर्णांक i, ret;

	/* Use OEM generic handler क्रम Netlink request */
	अगर (nca->req_flags == NCSI_REQ_FLAG_NETLINK_DRIVEN)
		type = NCSI_PKT_CMD_OEM;
	अन्यथा
		type = nca->type;

	/* Search क्रम the handler */
	क्रम (i = 0; i < ARRAY_SIZE(ncsi_cmd_handlers); i++) अणु
		अगर (ncsi_cmd_handlers[i].type == type) अणु
			अगर (ncsi_cmd_handlers[i].handler)
				nch = &ncsi_cmd_handlers[i];
			अन्यथा
				nch = शून्य;

			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!nch) अणु
		netdev_err(nca->ndp->ndev.dev,
			   "Cannot send packet with type 0x%02x\n", nca->type);
		वापस -ENOENT;
	पूर्ण

	/* Get packet payload length and allocate the request
	 * It is expected that अगर length set as negative in
	 * handler काष्ठाure means caller is initializing it
	 * and setting length in nca beक्रमe calling xmit function
	 */
	अगर (nch->payload >= 0)
		nca->payload = nch->payload;
	nr = ncsi_alloc_command(nca);
	अगर (!nr)
		वापस -ENOMEM;

	/* track netlink inक्रमmation */
	अगर (nca->req_flags == NCSI_REQ_FLAG_NETLINK_DRIVEN) अणु
		nr->snd_seq = nca->info->snd_seq;
		nr->snd_portid = nca->info->snd_portid;
		nr->nlhdr = *nca->info->nlhdr;
	पूर्ण

	/* Prepare the packet */
	nca->id = nr->id;
	ret = nch->handler(nr->cmd, nca);
	अगर (ret) अणु
		ncsi_मुक्त_request(nr);
		वापस ret;
	पूर्ण

	/* Fill the ethernet header */
	eh = skb_push(nr->cmd, माप(*eh));
	eh->h_proto = htons(ETH_P_NCSI);
	eth_broadcast_addr(eh->h_dest);

	/* If mac address received from device then use it क्रम
	 * source address as unicast address अन्यथा use broadcast
	 * address as source address
	 */
	अगर (nca->ndp->gma_flag == 1)
		स_नकल(eh->h_source, nca->ndp->ndev.dev->dev_addr, ETH_ALEN);
	अन्यथा
		eth_broadcast_addr(eh->h_source);

	/* Start the समयr क्रम the request that might not have
	 * corresponding response. Given NCSI is an पूर्णांकernal
	 * connection a 1 second delay should be sufficient.
	 */
	nr->enabled = true;
	mod_समयr(&nr->समयr, jअगरfies + 1 * HZ);

	/* Send NCSI packet */
	skb_get(nr->cmd);
	ret = dev_queue_xmit(nr->cmd);
	अगर (ret < 0) अणु
		ncsi_मुक्त_request(nr);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
